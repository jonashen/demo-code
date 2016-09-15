class AddAasmStateColumnToProductsTable < ActiveRecord::Migration
  def change
    change_table :products, bulk: true do |t|
      t.string :aasm_state, null: false, default: 'draft'
    end

    remove_index :products, [:user_id]
    add_index :products, [:user_id, :aasm_state]
  end
end
