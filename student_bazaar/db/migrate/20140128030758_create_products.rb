class CreateProducts < ActiveRecord::Migration
  def change
    create_table :products, as_relation_superclass: true do |t|
      t.string :name, null: false

      t.timestamps
    end
  end
end
