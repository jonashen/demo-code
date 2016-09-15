class HomepageTopic < ActiveRecord::Base

  # Validations
  validates_presence_of :main_topic, :main_topic_content, :sub_topic_on_left, :sub_topic_on_right,
    :sub_topic_content_on_left, :sub_topic_content_on_right

  validates_length_of :main_topic, :sub_topic_on_left, :sub_topic_on_right, within: 1..255
  validates_length_of :main_topic_content, :sub_topic_content_on_left, :sub_topic_content_on_right, within: 10..255


  class << self

    def get_topic
      self.first || self.new
    end

  end

end
