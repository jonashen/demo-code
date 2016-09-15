class CreateUsersProducts < ActiveRecord::Migration
  def change
    create_table :users_products do |t|
      t.integer :user_id, null: false
      t.integer :product_id, null: false
      t.money :price

      t.timestamps
    end
    add_index :users_products, [:user_id, :product_id]
    add_index :users_products, [:product_id, :user_id]

    add_attachment :users_products, :image
  end
end
