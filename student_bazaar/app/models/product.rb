class Product < ActiveRecord::Base
  include Rails.application.routes.url_helpers

  is_a_superclass

  acts_as_taggable

  searchable do
    text :name
    text :description
  end

  # Associations
  has_many :users_products
  has_and_belongs_to_many :categories
  has_attached_file :image, :styles => { :medium => "500x500>", :thumb => "150x150>" }, :default_url => "/images/black.jpg"

  # Validations
  validates_presence_of :name
  validates_length_of :name, within: 1..255
  validates_length_of :description, within: 1..2000, allow_nil: true
  validates_attachment_content_type :image, :content_type => /\Aimage\/.*\Z/


  class << self

    def newest_products(count = 10)
      Product.joins('LEFT JOIN users_products ON products.id = users_products.product_id').
        where('aasm_state = ?', 'auctioning').
        select('DISTINCT products.id, products.*').
        order('created_at DESC').
        limit(count).to_a
    end

    def newest_products_from_cache(count = 10)
      newest_product = Product.last
      return [] unless newest_product

      Rails.cache.fetch "newest-products.count-#{count}-#{newest_product.cache_key}", expires_in: 1.day do
        newest_products(count)
      end
    end

  end

  # Hooks

  def first_class_categories
    case specific
    when Book
      [Category.find_by(name: Book.to_s)]
    when Other
      [Category.find_by(name: Other.to_s.pluralize)]
    end
  end

  def name_with_second_class_categories
    "<p>#{first_class_categories.map(& :name).join(', ')}</p>#{ActionController::Base.helpers.image_tag(image, size: '40x40')}#{name}"
  end

  def link_url
    case specific
    when Book
      book_detail_path(specific.isbn)
    when Other
      other_detail_path(specific.id)
    else
      '#'
    end
  end


  class << self

    def random_products(count = 8)
      Rails.cache.fetch "products.random.#{count}", expires_in: 3.minutes do
        self.
          joins(:users_products).
          where(users_products: {aasm_state: 'auctioning'}).
          select('DISTINCT products.id, products.*').
          order('RAND()').
          limit(count).
          to_a
      end
    end

    def popular_products(count = 12)
      Rails.cache.fetch "products.popular.#{count}", expires_in: 10.minutes do
        result = ActiveRecord::Base.connection.execute("SELECT product_id, COUNT(*) AS count FROM users_products WHERE aasm_state = 'auctioning' GROUP BY product_id ORDER BY count DESC LIMIT #{count}")
        product_ids = result.each do |row|
        end

        products = self.where(id: product_ids).all.to_a
      end

    end

  end

  private

end
