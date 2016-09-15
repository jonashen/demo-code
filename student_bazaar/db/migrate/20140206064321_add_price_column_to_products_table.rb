class AddPriceColumnToProductsTable < ActiveRecord::Migration
  def change
    change_table :products, bulk: true do |t|
      t.money :price
    end
  end
end
