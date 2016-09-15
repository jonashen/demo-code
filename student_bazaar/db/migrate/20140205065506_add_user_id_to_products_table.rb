class AddUserIdToProductsTable < ActiveRecord::Migration
  def change
    change_table :products do |t|
      t.integer :user_id, null: false
    end

    add_index :products, [:user_id]
  end
end
