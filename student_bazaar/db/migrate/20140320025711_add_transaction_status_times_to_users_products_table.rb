class AddTransactionStatusTimesToUsersProductsTable < ActiveRecord::Migration
  def change
    change_table :users_products do |t|
      t.datetime :finished_at
      t.datetime :rejected_at
    end

    add_index :users_products, [:user_id, :finished_at]
    add_index :users_products, [:user_id, :rejected_at]
  end
end
