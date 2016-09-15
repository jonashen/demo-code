
class OthersController < ApplicationController

  before_action :set_other_params, only: [:create, :update]

  load_and_authorize_resource :other, except: [:index, :search]

  def search
    search_word = params[:term].blank? ? params[:search_other] : params[:term]
    Rails.logger.debug "search: #{search_word}"

    @others_from_solr = Other.search do
      fulltext search_word do
        phrase_fields name: 2.0, description: 0.5
        query_phrase_slop 2
      end
      paginate page: params[:page]
    end.results

    # REFACTOR: search do not filter books that has no users_products
    @others = Other.joins(product: [:categories, :users_products]).
                where(id: @others_from_solr).
                where('aasm_state = ?', 'auctioning')

    unless params[:tag_id].blank?
      @others = @others.joins('LEFT JOIN taggings ON taggings.taggable_id = users_products.id AND taggable_type = "UsersProduct"').
          joins('LEFT JOIN tags ON taggings.tag_id = tags.id')
      @others = @others.where('tag_id = ?', params[:tag_id])
    end

    @others = @others.page params[:page]

    respond_to do |format|
      format.html { render action: "index" }
      format.json { render action: "search" }
    end
  end

  def index
    @others = Other.joins(product: [:users_products]).
                where('aasm_state = ?', 'auctioning')

    unless params[:tag_id].blank?
      @others = @others.joins('LEFT JOIN taggings ON taggings.taggable_id = users_products.id AND taggable_type = "UsersProduct"').
                  joins('LEFT JOIN tags ON taggings.tag_id = tags.id')
      @others = @others.where('tag_id = ?', params[:tag_id])
    end

    @others = @others.page params[:page]
  end

  def new
    @users_product = current_user.users_products.build
  end

  def show_detail
    authorize! :show_detail, Other
    @other = Other.find(params[:id])
  end

  def create
    @other = Other.new(params[:other])
    @users_product = UsersProduct.new params[:users_product] do |up|
      up.product = @other.product
      up.user = current_user
    end

    if params[:users_product][:aasm_state] == 'auctioning' && ! current_user.sellable_today?
      flash[:alert] = "You cannot sell over #{Settings.user.max_sell_count_per_day} products per day"
      return render "new"
    end

    begin
      @other.save!
      @users_product.save!
      current_user.succ_sell_count_today! if @users_product.auctioning?

      #flash[:notice] = "product #{@other.name} uploaded, please be patient to wait buyers"
      flash[:notice] = "Your product '#{@other.name}' has been uploaded, you will be notified when someone is interested!"

      redirect_to user_users_product_path(current_user, @users_product)
    rescue Exception => e
      flash[:alert] = "Failed to upload book: #{@other.name}"
      Rails.logger.debug "error: #{e.to_s}"
      Rails.logger.debug e.backtrace.join("\n")
      render 'new'
    end
  end

  private

  def set_other_params
    params[:other] = params.require(:other).permit(:name, :image, :description, category_ids: [])

    if params[:users_product]
      params[:users_product] = params.require(:users_product).permit(:price, :aasm_state, :tag_list)
    end

    Rails.logger.debug "set_other_params: #{params.inspect}"
  end

end

