class AddIndexToProducts < ActiveRecord::Migration
  def change

    add_index :products, [:created_at]

  end
end
