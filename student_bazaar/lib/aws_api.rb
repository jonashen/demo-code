module AwsApi
  extend ASIN::Client

  def self.find_book(isbn)  
    books = Rails.cache.fetch "/aws/books/#{isbn}", expires_in: 15.minutes do
      lookup(isbn)
    end

    books.empty? ? nil : books.first
  end

end