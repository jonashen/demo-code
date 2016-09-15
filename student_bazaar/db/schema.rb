# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20140507073050) do

  create_table "books", force: true do |t|
    t.string   "isbn",       null: false
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "books", ["isbn"], name: "index_books_on_isbn", unique: true, using: :btree

  create_table "cart_items", force: true do |t|
    t.string   "name"
    t.string   "state"
    t.integer  "cartable_id"
    t.string   "cartable_type"
    t.integer  "owner_id"
    t.string   "owner_type"
    t.integer  "cart_id"
    t.float    "price",         default: 0.0
    t.integer  "quantity"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "cart_items", ["cart_id"], name: "index_cart_items_on_cart_id", using: :btree
  add_index "cart_items", ["cartable_id"], name: "index_cart_items_on_cartable_id", using: :btree
  add_index "cart_items", ["cartable_type"], name: "index_cart_items_on_cartable_type", using: :btree
  add_index "cart_items", ["name"], name: "index_cart_items_on_name", using: :btree
  add_index "cart_items", ["owner_id"], name: "index_cart_items_on_owner_id", using: :btree
  add_index "cart_items", ["owner_type"], name: "index_cart_items_on_owner_type", using: :btree
  add_index "cart_items", ["state"], name: "index_cart_items_on_state", using: :btree

  create_table "carts", force: true do |t|
    t.string   "session_id"
    t.string   "state"
    t.integer  "shopper_id"
    t.string   "shopper_type"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.datetime "sent_at"
  end

  add_index "carts", ["sent_at"], name: "index_carts_on_sent_at", using: :btree
  add_index "carts", ["shopper_id"], name: "index_carts_on_shopper_id", using: :btree
  add_index "carts", ["shopper_type"], name: "index_carts_on_shopper_type", using: :btree
  add_index "carts", ["state"], name: "index_carts_on_state", using: :btree

  create_table "categories", force: true do |t|
    t.string   "name",       null: false
    t.integer  "parent_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "categories", ["parent_id"], name: "index_categories_on_parent_id", using: :btree

  create_table "categories_products", force: true do |t|
    t.integer  "category_id", null: false
    t.integer  "product_id",  null: false
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "categories_products", ["category_id", "product_id"], name: "index_categories_products_on_category_id_and_product_id", unique: true, using: :btree
  add_index "categories_products", ["product_id", "category_id"], name: "index_categories_products_on_product_id_and_category_id", unique: true, using: :btree

  create_table "delayed_jobs", force: true do |t|
    t.integer  "priority",   default: 0, null: false
    t.integer  "attempts",   default: 0, null: false
    t.text     "handler",                null: false
    t.text     "last_error"
    t.datetime "run_at"
    t.datetime "locked_at"
    t.datetime "failed_at"
    t.string   "locked_by"
    t.string   "queue"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "delayed_jobs", ["priority", "run_at"], name: "delayed_jobs_priority", using: :btree

  create_table "homepage_topics", force: true do |t|
    t.string "main_topic"
    t.text   "main_topic_content"
    t.string "sub_topic_on_left"
    t.text   "sub_topic_content_on_left"
    t.string "sub_topic_on_right"
    t.text   "sub_topic_content_on_right"
  end

  create_table "others", force: true do |t|
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "products", force: true do |t|
    t.integer  "as_product_id"
    t.string   "as_product_type"
    t.string   "name",               null: false
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "image_file_name"
    t.string   "image_content_type"
    t.integer  "image_file_size"
    t.datetime "image_updated_at"
    t.text     "description"
  end

  add_index "products", ["created_at"], name: "index_products_on_created_at", using: :btree

  create_table "taggings", force: true do |t|
    t.integer  "tag_id"
    t.integer  "taggable_id"
    t.string   "taggable_type"
    t.integer  "tagger_id"
    t.string   "tagger_type"
    t.string   "context",       limit: 128
    t.datetime "created_at"
  end

  add_index "taggings", ["tag_id", "taggable_id", "taggable_type", "context", "tagger_id", "tagger_type"], name: "taggings_idx", unique: true, using: :btree

  create_table "tags", force: true do |t|
    t.string "name"
  end

  add_index "tags", ["name"], name: "index_tags_on_name", unique: true, using: :btree

  create_table "users", force: true do |t|
    t.string   "email",                               default: "", null: false
    t.string   "encrypted_password",                  default: "", null: false
    t.string   "reset_password_token"
    t.datetime "reset_password_sent_at"
    t.datetime "remember_created_at"
    t.integer  "sign_in_count",                       default: 0,  null: false
    t.datetime "current_sign_in_at"
    t.datetime "last_sign_in_at"
    t.string   "current_sign_in_ip"
    t.string   "last_sign_in_ip"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "confirmation_token"
    t.datetime "confirmed_at"
    t.datetime "confirmation_sent_at"
    t.string   "unconfirmed_email"
    t.string   "name",                                             null: false
    t.string   "second_email"
    t.integer  "purchase_count_on_last_purchase_day", default: 0,  null: false
    t.date     "last_purchase_date"
    t.integer  "sell_count_on_last_sell_day",         default: 0,  null: false
    t.date     "last_sell_date"
  end

  add_index "users", ["confirmation_token"], name: "index_users_on_confirmation_token", unique: true, using: :btree
  add_index "users", ["email"], name: "index_users_on_email", unique: true, using: :btree
  add_index "users", ["name"], name: "index_users_on_name", unique: true, using: :btree
  add_index "users", ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true, using: :btree

  create_table "users_products", force: true do |t|
    t.integer  "user_id",                              null: false
    t.integer  "product_id",                           null: false
    t.integer  "price_cents",        default: 0,       null: false
    t.string   "price_currency",     default: "USD",   null: false
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "image_file_name"
    t.string   "image_content_type"
    t.integer  "image_file_size"
    t.datetime "image_updated_at"
    t.string   "aasm_state",         default: "draft", null: false
    t.datetime "finished_at"
    t.datetime "rejected_at"
    t.integer  "buyer_count",        default: 0,       null: false
  end

  add_index "users_products", ["aasm_state", "buyer_count", "updated_at"], name: "index_for_expire_calculation", using: :btree
  add_index "users_products", ["product_id", "user_id"], name: "index_users_products_on_product_id_and_user_id", using: :btree
  add_index "users_products", ["user_id", "finished_at"], name: "index_users_products_on_user_id_and_finished_at", using: :btree
  add_index "users_products", ["user_id", "product_id", "aasm_state"], name: "index_users_products_on_user_id_and_product_id_and_aasm_state", using: :btree
  add_index "users_products", ["user_id", "rejected_at"], name: "index_users_products_on_user_id_and_rejected_at", using: :btree

end
