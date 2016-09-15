class AddAasmColumnToUsersProducts < ActiveRecord::Migration
  def change
    UsersProduct.transaction do 

      # change_table :users_products, bulk: true do |t|
      #   t.string :aasm_state, null: false, default: 'draft'
      # end

      remove_index :users_products, [:user_id, :product_id]
      add_index :users_products, [:user_id, :product_id, :aasm_state]
    end
  end
end
