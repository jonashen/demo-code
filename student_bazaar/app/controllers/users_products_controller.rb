
class UsersProductsController < ApplicationController
  before_action :set_users_product_params, only: [:update]

  load_and_authorize_resource :user
  load_and_authorize_resource :users_product, through: :user

  before_action :check_user!

  def index
    @users_products = @users_products.where(aasm_state: ['draft', 'auctioning', 'wait_for_reply']).
      order(:price_cents).
      page(params[:page])
  end

  def update

    # seller cannot update price if product is auctioning
    params[:users_product].delete(:price) if @users_product.auctioning?

    if ! current_user.sellable_today? && params[:users_product][:aasm_state] == 'auctioning'
      flash[:alert] = "You cannot sell over #{Settings.user.max_sell_count_per_day} products per day."
      return render "edit"
    end

    if @users_product.update_attributes(params[:users_product]) && @users_product.product.update_attributes(params[:specific])

      current_user.succ_sell_count_today! if @users_product.auctioning?

      if @users_product.auctioning?
        flash[:notice] = "Product #{@users_product.product.name} updated, please wait for buyers' replies!"
      else
        flash[:notice] = "Product #{@users_product.product.name} updated."
      end
      redirect_to user_users_product_path(current_user, @users_product)
    else
      flash[:alert] = "Failed to update product #{@users_product.product.name}."
      render 'edit'
    end
  end

  def stop_auctioning
    @users_product = current_user.users_products.where(id: params[:users_product_id]).first

    unless @users_product
      flash[:alert] = "Sorry, product not found!"
      return
    end

    @result = @users_product.stop_auctioning!
    if @result
      flash[:notice] = "Successfully moved product #{@users_product.product.name} off the shelf."

      @users_products = @users_products.where(aasm_state: ['draft', 'auctioning', 'wait_for_reply']).
          page(params[:page])

      render 'index'
    else
      flash[:alert] = "Failed to off shelf product #{@users_product.product.name}."
    end
  end

  def finish_order
    @users_product = @user.users_products.where(id: params[:users_product_id]).first
    @cart_item = @users_product.cart_items.where(id: params[:cart_item_id]).first

    if @users_product.nil? or @cart_item.nil?
      flash[:alert] = "Cannot finish order because the product was not found."
      return
    end

    authorize! :finish_order, @users_product

    result = @users_product.finish_order!(@cart_item)
    if result
      flash[:notice] = "Finished order: #{@users_product.product.name}"
    else
      flash[:alert] = "Failed to finish order: #{@users_product.product.name}"
    end
  end

  def reject_all
    @users_product = @user.users_products.where(id: params[:users_product_id]).first

    if @users_product.nil?
      flash[:alert] = "Cannot reject all buyers because the product was not found."
      return
    end

    authorize! :reject_all, @users_product

    if @users_product.reject_all!
      flash[:notice] = "Reject all buyers successfully"
    else
      flash[:alert] = "Reject all buyers failed"
    end
  end

  private

  # REFACTOR: remove check_user!
  def check_user!
    Rails.logger.debug "@user: #{@user.id}"
    Rails.logger.debug "current_user: #{current_user.id}"
    raise CanCan::AccessDenied unless @user.id == current_user.id
  end

  def set_users_product_params
    # REFACTOR: preserve specific attributes unless product is book
    unless params[:id].blank? and params[:users_product][:product_attributes]
      up = UsersProduct.find params[:id]
      if up.product.as_product_type == Other.to_s
        params[:specific] = params[:users_product][:product_attributes].require(:specific).permit(:name, :description)
      end
    end
    params[:users_product] = params.require(:users_product).permit(:price, :aasm_state, :tag_list)
  end

end

