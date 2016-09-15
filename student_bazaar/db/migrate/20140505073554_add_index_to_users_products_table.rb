class AddIndexToUsersProductsTable < ActiveRecord::Migration
  def change

    add_index :users_products, [:aasm_state, :buyer_count, :updated_at], name: 'index_for_expire_calculation'


  end
end
