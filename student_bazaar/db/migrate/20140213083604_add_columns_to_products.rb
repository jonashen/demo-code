class AddColumnsToProducts < ActiveRecord::Migration
  def change
  
    Product.transaction do 
      remove_attachment :books, :cover_image
      add_attachment :products, :image

      change_table :products, bulk: true do |t|
        t.text :description
      end
    end

  end
end
