class CreateOthersTable < ActiveRecord::Migration
  def change
    create_table :others do |t|
      t.timestamps
    end
  end
end