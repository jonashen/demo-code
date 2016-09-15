class CreateHomepageTopicsTable < ActiveRecord::Migration
  def change
    create_table :homepage_topics do |t|
      t.string :main_topic
      t.text :main_topic_content
      t.string :sub_topic_on_left
      t.text :sub_topic_content_on_left
      t.string :sub_topic_on_right
      t.text :sub_topic_content_on_right
      t.timestamps
    end
  end
end
