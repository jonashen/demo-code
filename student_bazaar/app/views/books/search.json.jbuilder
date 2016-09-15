json.array! @books do |book|
  json.id book.id
  json.label book.name_with_second_class_categories
  json.value book.name
end