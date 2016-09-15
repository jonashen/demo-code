class RemoveAasmFromProducts < ActiveRecord::Migration
  def change
    remove_column :products, :aasm_state
  end
end
