class RemoveUserColumnFromCartsTable < ActiveRecord::Migration
  def change

    ActiveRecord::Base.transaction do
      remove_index :carts, [:user_id]
      remove_column :carts, :user_id      
    end

  end
end
