StudentBazaar::Application.routes.draw do
  devise_for :users, controllers: {registrations: "users/registrations"}

  root 'application#index'

  #namespace :user do 
  #  resources :products
  #end

  resources :users do 
    get "/show_profile", to: "users#show_profile"
    #get "/edit_profile", to: "users#edit_profile"
    get "change_name", to: "users#change_name"
    patch "/update_name", to: "users#update_name"
    get "change_password", to: "users#change_password"
    patch "/update_password", to: "users#update_password"
    #patch "/update_profile", to: "users#update_profile"
    get "/show_shopping_histories", to: "users#show_shopping_histories"
    post "/add_to_cart", to: "users#add_to_cart"
    post "/remove_from_cart", to: "users#remove_from_cart"
    get "/show_cart", to: "users#show_cart"
    get "/checkout", to: "users#checkout"

    resources :users_products do
      post "/finish_order", to: "users_products#finish_order"
      #post "/reject_order", to: "users_products#reject_order"
      post "/stop_auctioning", to: "users_products#stop_auctioning"
      post "/reject_all", to: "users_products#reject_all"
    end  
  end

  resources :categories do
    get "/sub_categories", to: "categories#sub_categories"
  end

  resources :products
  get "/newest_products", to: 'products#newest'
  get "/products_search", to: 'products#search'
  

  resources :books
  get "/books/find_book_from_aws/:isbn", to: 'books#find_book_from_aws'
  get "/books/show_detail/:isbn", to: 'books#show_detail', as: 'book_detail'
  get "/books_search", to: 'books#search'

  resources :others
  get "/others_search", to: 'others#search'
  get "/others/:id/show_detail", to: 'others#show_detail', as: 'other_detail'

end
