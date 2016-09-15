class ManyToManyRelationBetweenProductsAndCategories < ActiveRecord::Migration
  def change
    create_table :categories_products do |t|
      t.integer :category_id, null: false
      t.integer :product_id, null: false

      t.timestamps
    end

    add_index :categories_products, [:category_id, :product_id], unique: true
    add_index :categories_products, [:product_id, :category_id], unique: true
  end
end
