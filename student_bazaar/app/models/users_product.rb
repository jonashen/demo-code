
class UsersProduct < ActiveRecord::Base
  include AASM

  acts_as_cartable
  acts_as_taggable

  aasm do
    state :draft, initial: true
    state :auctioning
    state :auctioned
    state :wait_for_reply
    state :closed
    state :finished
    state :rejected

    event :on_shelf do
      transitions from: :draft, to: :auctioning
    end

    event :stop_auctioning do
      transitions from: :auctioning, to: :closed
    end

    event :sold do
      transitions from: :auctioning, to: :auctioned
    end

    event :pre_sold do
      transitions from: :auctioning, to: :wait_for_reply
    end

    event :close do
      transitions from: :wait_for_reply, to: :closed
    end

    event :cancel_order do
      transitions from: :wait_for_reply, to: :auctioning
    end

    event :finish_order do
      transitions from: :wait_for_reply, to: :finished
    end    

    event :reject_order do
      transitions from: :wait_for_reply, to: :rejected
    end        
  end

  monetize :price_cents

  default_scope { includes(:product, :user) }
  scope :auctioning, -> { where(aasm_state: 'auctioning') }

  belongs_to :product
  belongs_to :user

  accepts_nested_attributes_for :product

  ## Associations
  has_many :cart_items,
    foreign_key: :cartable_id



  class << self

    def expire_neglected_products

      self.where("aasm_state = ? AND buyer_count = ? AND updated_at < ?", "auctioning", 0, Time.now - Settings.user.expired_days_if_no_buyer.days).find_each do |users_product|

        users_product.transaction do
          users_product.lock!
          users_product.stop_auctioning
          users_product.save!
        end

      end

    end

  end

  ## Virtual Attributes
  def name
    product.name
  end

  def finished?
    !! finished_at
  end

  def rejected?
    !! rejected_at
  end

  ## Instance Methods
  def finish_order!(cart_item)
    if wait_for_reply?
      self.transaction do

        cart_items.each do |ci|
          ci.owner = user
          ci == cart_item ? ci.succeeded : ci.failed
          ci.save!
        end

        self.finish_order
        self.finished_at = Time.now
        self.save!
      end
    else
      false
    end
  end

  def stop_auctioning!
    if auctioning?
      self.transaction do
        self.lock!
        buyer_count > 0 ? pre_sold : stop_auctioning
        save!
      end
    else
      false
    end
  end

  def reject_all!
    if wait_for_reply?
      self.transaction do
        self.lock!
        cart_items = CartItem.joins(:cart).where(carts: {state: 'success'}, cartable_id: self.id).readonly(false).find_each do |ci|
          ci.failed
          ci.save!
        end
        close
        save!
      end
    else
      false
    end
  end

end
