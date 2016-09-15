
class Tag < ActsAsTaggableOn::Tag

  class << self

    def popular_tags(count = 10)
      self.joins(:taggings).
        select('tags.*, COUNT(*) AS count').
        group(:tag_id).
        order('count DESC').
        limit(count)
    end

    def popular_tags_from_cache(count = 10)
      newest_tag = Tag.last
      return [] unless newest_tag
      Rails.cache.fetch "tags.count-#{count}-#{newest_tag.cache_key}", expires_in: 15.minutes do
         popular_tags(count).to_a
      end
    end

  end

end