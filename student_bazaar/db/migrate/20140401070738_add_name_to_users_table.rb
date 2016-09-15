class AddNameToUsersTable < ActiveRecord::Migration
  def change
    change_table :users do |t|
      t.string :name, null: false
    end

    User.find_each do |user|
      user.name = user.email.split('@')[0]
      user.save!
    end

    add_index :users, [:name], unique: true
  end
end
