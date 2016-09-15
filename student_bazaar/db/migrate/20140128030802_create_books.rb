class CreateBooks < ActiveRecord::Migration
  def change
    create_table :books do |t|
      #t.string :author
      t.string :isbn, null: false

      t.timestamps
    end

    add_index :books, :isbn
  end
end
