class AddLastPurchaseSellInfoToUsersTable < ActiveRecord::Migration
  def change

    change_table :users, bluk: true do |t|
      t.integer :purchase_count_on_last_purchase_day, null: false, default: 0
      t.date :last_purchase_date
      t.integer :sell_count_on_last_sell_day, null: false, default: 0
      t.date :last_sell_date
    end

  end
end
