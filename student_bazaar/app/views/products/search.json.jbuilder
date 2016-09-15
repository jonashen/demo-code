json.array! @products do |product|
  json.id product.id
  json.label product.name_with_second_class_categories
  json.value product.name
end