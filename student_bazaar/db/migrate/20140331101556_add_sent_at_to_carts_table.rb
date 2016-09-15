class AddSentAtToCartsTable < ActiveRecord::Migration
  def change
    change_table :carts do |t|
      t.datetime :sent_at
    end

    add_index :carts, [:sent_at]
  end
end
