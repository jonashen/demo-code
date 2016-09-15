class Other < ActiveRecord::Base
  is_a :product

  searchable do
    text :name
    text :description
  end

  # Validations
  validates_presence_of :name
  validates_length_of :name, within: 1..255

  # Hooks
  after_create :set_first_class_category

  def first_class_category
    Category.find_by(name: self.class.to_s.pluralize)
  end

  private

  def set_first_class_category
    Rails.logger.debug "other set first class category"
    category = Category.find_by name: self.class.to_s.pluralize
    self.categories << category
  end

end
