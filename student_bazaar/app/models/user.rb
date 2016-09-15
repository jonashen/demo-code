class User < ActiveRecord::Base
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :trackable, :validatable, :confirmable

  validates_presence_of :name, :email
  validates_uniqueness_of :name, :email
  validates_uniqueness_of :name, :second_email, allow_blank: true
  validates :email, uniqueness: true, format: { with: /^([0-9a-zA-Z]([-\.\w]*[0-9a-zA-Z])*@#{Settings.user.email.domain})$/, multiline: true, message: :email_format }
  validates :second_email, email: true, allow_blank: true
  validate  do
    errors.add(:second_email, 'alternative email must be different') if email == second_email
  end

  # Associations
  has_many :users_products
  has_many :products, through: :users_products
  has_many :shopping_histories,
    ->(user) { where(shopper_id: user.id, state: ['processing', 'success']) },
    class_name: ShoppingCart,
    foreign_key: :shopper_id
  has_many :shopping_carts,
    class_name: ShoppingCart,
    foreign_key: :shopper_id

  # Hook
  before_validation :set_default_name

  class << self

    def checkout(user_id, cart_id, host)
      user = User.find user_id
      cart = ShoppingCart.find cart_id

      ## log shopping cart owner
      cart.transaction do
        cart.sent_at = Time.now
        cart.checkout
        cart.shopper = user
        cart.save!

        cart.cart_items.includes(:cartable).each do |ci|
          # update buyer count
          user_product = ci.cartable
          user_product.lock!
          user_product.buyer_count += 1
          user_product.pre_sold if user_product.buyer_count >= Settings.user.max_buyers_per_product
          user_product.save!
        end

        # update purchase info on today
        if user.last_purchase_date == Date.today
          user.purchase_count_on_last_purchase_day += cart.cart_items.count
        else
          user.purchase_count_on_last_purchase_day = cart.cart_items.count
          user.last_purchase_date = Date.today
        end
        user.save!
      end

      ## send transaction mail to user
      Thread.start do
        cart.cart_items.each do |item|
          seller = item.cartable.user
          Rails.logger.debug "**** send purchase notification email to seller: #{seller.email}"
          PurchaseMailer.purchase_email(user, seller, item.cartable, host).deliver
        end
      end

      cart.succeeded
    end

  end

  def current_shopping_items_count(session_id)
    ShoppingCart.where(shopper_id: id, session_id: session_id).count
  end

  def purchased?(user_product)
    shopping_histories.
      joins(:cart_items).
      where(cart_items: {cartable_id: user_product.id}).
      first
  end

  def purchasable_quota_today
    if last_purchase_date == Date.today
      Settings.user.max_purchase_count_per_day - purchase_count_on_last_purchase_day
    else
      Settings.user.max_purchase_count_per_day
    end
  end

  def purchasable_today?(cart)
    purchasable_quota_today - cart.cart_items.count > 0
  end

  def sellable_quota_today
    if last_sell_date == Date.today
      Settings.user.max_sell_count_per_day - sell_count_on_last_sell_day
    else
      Settings.user.max_sell_count_per_day
    end
  end

  def sellable_today?
    sellable_quota_today > 0
  end

  def succ_sell_count_today!
    if last_sell_date == Date.today
      self.sell_count_on_last_sell_day += 1
    else
      self.sell_count_on_last_sell_day = 1
      self.last_sell_date = Date.today
    end

    save!
  end

  protected

  def set_default_name
    self.name = email.split('@')[0] if email
  end

end
