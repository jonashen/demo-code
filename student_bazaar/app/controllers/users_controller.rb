


class UsersController < ApplicationController
  before_action :find_user, except: [:index, :show, :edit, :update, :destroy]
  load_and_authorize_resource  

  def index
  end

  def show
  end
  
  def show_profile
    authorize! :show_profile, User
  end

  def change_name
    authorize! :change_name, User
  end

  def update_name
    authorize! :change_name, User

    if @user.update_attributes params.require(:user).permit(:name)
      redirect_to user_show_profile_path(current_user)
    else
      render 'change_name'
    end    
  end

  def change_password
    authorize! :change_password, User
  end

  def update_password
    authorize! :change_password, User

    if @user.update_attributes params.require(:user).permit(:password, :password_confirmation)
      redirect_to new_user_session_path
    else
      render 'change_password'
    end    
  end

  def show_cart
    authorize! :show_cart, current_user

    @cart = ShoppingCart.get_cart session[:session_id]
    @cart_items = @cart.cart_items.page(params[:page])
  end

  def add_to_cart
    authorize! :add_to_cart, current_user

    cart = ShoppingCart.get_cart session[:session_id]    
    @user_product = UsersProduct.find(params[:users_product_id])

    unless @user_product
      flash[:alert] = "Cannot add the product to cart because the product was not found"
      return 
    end

    if @user_product.auctioning? and @user_product.user != current_user
      @user_product.transaction do
        @user_product.lock!

        # make sure no duplicated purchase
        if @user_product.buyer_count >= Settings.user.max_buyers_per_product
          flash[:alert] = "Cannot add to cart because the product has reached #{Settings.user.max_buyers_per_product} buyers"
          return
        end

        # make sure purchase quota is not reached
        unless current_user.purchasable_today?(cart)
          flash[:alert] = "You cannot purchase over #{Settings.user.max_purchase_count_per_day} products per day"
          return
        end

        result = cart.add_item @user_product
        Rails.logger.debug "add to cart result: #{result}"
        if result
          flash[:notice] = "Added #{@user_product.product.name} to cart"
        else
          flash[:alert] = "Failed to add #{@user_product.product.name} to cart"
        end
      end
    else
      flash[:alert] = "Failed to add #{@user_product.product.name} to cart"
    end
  end

  def show_shopping_histories
    authorize! :show_shopping_histories, current_user

    @shopping_histories = @user.shopping_histories.order('created_at DESC').page(params[:page])
  end

  def remove_from_cart
    authorize! :remove_from_cart, current_user

    cart = ShoppingCart.get_cart session[:session_id]
    @user_product = UsersProduct.find(params[:users_product_id])

    unless @user_product
      flash[:alert] = "Cannot remove from cart because the product not found."
      return
    end
    
    if @user_product.auctioning?
      cart.transaction do
        @user_product.lock!
        result = cart.remove_item @user_product
        Rails.logger.debug "remove from cart result: #{result}"
        if result
          flash[:notice] = "Removed #{@user_product.product.name} from cart"
        else
          flash[:alert] = "Failed to remove #{@user_product.product.name} from cart"
        end
      end
    else
      flash[:alert] = "Failed to remove #{@user_product.product.name} from cart"
    end    
  end

  def checkout
    authorize! :checkout, current_user

    cart = ShoppingCart.get_cart session[:session_id]
    User.checkout(current_user.id, cart.id, request.host)
    
    flash[:notice] = "Checkout success, please wait for the seller's reply!"

    redirect_to user_show_shopping_histories_path(current_user)
  end

  private 

  def find_user
    params[:id] = params[:user_id] if params[:user_id] and params[:id].nil?
  end

end

