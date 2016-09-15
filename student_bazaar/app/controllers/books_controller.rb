
class BooksController < ApplicationController
  before_action :set_book_params, only: [:create, :update]

  load_and_authorize_resource :book, except: [:index, :search]

  def search
    search_word = params[:term].blank? ? params[:search_book] : params[:term]
    Rails.logger.debug "search: #{search_word}"

    @books_from_solr = Book.search do
      fulltext search_word do
        phrase_fields isbn: 3.0, name: 2.0
        query_phrase_slop 2
      end
      paginate page: params[:page]
    end.results

    # REFACTOR: search do not filter books that has no users_products
    @books = Book.joins(product: [:categories, :users_products]).
      joins('LEFT JOIN taggings ON taggings.taggable_id = users_products.id AND taggable_type = "UsersProduct"').
      joins('LEFT JOIN tags ON taggings.tag_id = tags.id')
    @books = @books.where('tag_id = ?', params[:tag_id]) unless params[:tag_id].blank?
    if params[:category_id].blank?
      Rails.logger.debug 'category_id blank'
      @books = @books.where('category_id = ? ', Category.find_by(name: Book.to_s))
    else
      Rails.logger.debug 'category_id not blank'
      @category = Category.find(params[:category_id])
      @books = @books.where('category_id = ? ', @category.id)
    end

    Rails.logger.debug @books_from_solr
    @books = @books.where(id: @books_from_solr).
      where('aasm_state = ?', 'auctioning')

    respond_to do |format|
      format.html { render action: "index" }
      format.json { render action: "search" }
    end
  end

  def index
    @category = Category.find(params[:category_id]) unless params[:category_id].blank?

    @books = Book.joins(product: [:categories, :users_products]).
      joins('LEFT JOIN taggings ON taggings.taggable_id = users_products.id AND taggable_type = "UsersProduct"').
      joins('LEFT JOIN tags ON taggings.tag_id = tags.id')
    @books = @books.where('tag_id = ?', params[:tag_id]) unless params[:tag_id].blank?
    @books = @books.where('category_id = ? ', @category.id) if @category
    @books = @books.where('aasm_state = ?', 'auctioning')
    @books = @books.page params[:page]

    Rails.logger.debug "books controller: category is #{@category.name}" if @category
  end

  def new
    @users_product = current_user.users_products.build
  end

  def show_detail
    authorize! :show_detail, Book
    @book = Book.where(isbn: params[:isbn]).first
  end

  def create

    @book = Book.find_or_build_book(params[:book])
    @users_product = UsersProduct.new params[:users_product] do |up|
      up.product = @book.product
      up.user = current_user
    end

    if params[:users_product][:aasm_state] == 'auctioning' && ! current_user.sellable_today?
      flash[:alert] = "You cannot sell over #{Settings.user.max_sell_count_per_day} products per day"
      return render "new"
    end

    begin
      @book.transaction do
        @book.categories += Category.where(id: params[:book][:category_ids]).to_a
        @book.save!
        @users_product.save!
        current_user.succ_sell_count_today! if @users_product.auctioning?

        flash[:notice] = "Your product '#{@book.name}' has been uploaded, you will be notified when someone is interested!"

        redirect_to user_users_product_path(current_user, @users_product)
      end
    rescue Exception => e
      flash[:alert] = "Failed to upload book: #{@book.name}"
      Rails.logger.debug "error: #{e.to_s}"
      Rails.logger.debug e.backtrace.join("\n")
      render 'new'
    end
  end

  def find_book_from_aws
    result = {}
    book = AwsApi.find_book(params[:isbn])

    if book
      result[:title] = book.title
      result[:price] = book.raw.ItemAttributes.ListPrice.FormattedPrice
      result[:image_url] = book.image_url
    end

    render json: result
  end

  private

  def set_book_params
    params[:book] = params.require(:book).permit(:name, :image, :isbn, category_ids: [])

    if params[:users_product]
      params[:users_product] = params.require(:users_product).permit(:price, :aasm_state, :tag_list)
    end

    Rails.logger.debug "set_book_params: #{params.inspect}"
  end

end

