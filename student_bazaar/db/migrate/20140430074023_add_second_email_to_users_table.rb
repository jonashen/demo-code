class AddSecondEmailToUsersTable < ActiveRecord::Migration
  def change

    change_table :users, bulk: true do |t|
      t.string :second_email
    end

  end
end
