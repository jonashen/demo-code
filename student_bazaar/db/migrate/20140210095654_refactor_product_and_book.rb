class RefactorProductAndBook < ActiveRecord::Migration
  def change
    change_table :products, bulk: true do |t|
      t.remove :price_cents
      t.remove :price_currency
      t.remove :user_id
    end

    remove_attachment :products, :image
    add_attachment :books, :cover_image

    change_table :users_products, bulk: true do |t|
      t.string :aasm_state, null: false, default: 'draft'
    end    
  end
end
