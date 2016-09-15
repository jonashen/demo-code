class Book < ActiveRecord::Base
  is_a :product

  searchable do
    text :name
    text :isbn
    text :description
  end

  # Validations
  validates_presence_of :name, :isbn
  validates_length_of :name, within: 1..255
  validates_length_of :isbn, within: 10..13

  # Hooks
  # FIXIT: broken upload user product
  before_create :update_image
  after_create :set_first_class_category

  class << self

    def find_or_build_book(book_params)
      book = self.find_by isbn: book_params[:isbn]
      unless book
        book = self.new(book_params)
      end

      book
    end

  end

  def first_class_category
    Category.find_by name: self.class.to_s
  end

  def second_class_categories
    categories.where(parent_id: first_class_category)
  end

  def name_with_second_class_categories
    "<p>#{second_class_categories.map(& :name).join(', ')}</p>#{ActionController::Base.helpers.image_tag(image, size: '40x40')}#{name}"
  end

  private

  def update_image
    book = AwsApi.find_book isbn
    self.image = open book.image_url if book and book.image_url
  end

  def set_first_class_category
    Rails.logger.debug "book set first class category"
    book_category = Category.find_by name: self.class.to_s
    self.categories << book_category
  end

end
