

#### Categories
## main categories
book_category = Category.find_or_create_by name: 'Book'
other_category =  Category.find_or_create_by name: 'Others'

## sub categories of book
Category.find_or_create_by name: 'Humanities', parent: book_category
Category.find_or_create_by name: 'Mathematics', parent: book_category
Category.find_or_create_by name: 'Language', parent: book_category
Category.find_or_create_by name: 'The Arts', parent: book_category
Category.find_or_create_by name: 'Science', parent: book_category
Category.find_or_create_by name: 'TEST PREP', parent: book_category

## Home page topic
HomepageTopic.create! do |t|
  t.main_topic = 'Welcome to student bazaar !'
  t.main_topic_content = 'Student bazaar is a free paltform, you can purchase/sell used products here. All for free'
  t.sub_topic_on_left = 'How to sell'
  t.sub_topic_content_on_left = '....................................'
  t.sub_topic_on_right = 'How to buy'
  t.sub_topic_content_on_right = '...................................'
end if HomepageTopic.count == 0
