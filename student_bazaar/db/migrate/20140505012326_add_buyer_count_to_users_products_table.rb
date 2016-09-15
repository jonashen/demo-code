class AddBuyerCountToUsersProductsTable < ActiveRecord::Migration
  def change

    change_table :users_products, bluk: true do |t|

      t.integer :buyer_count, null: false, default: 0

    end

  end
end
