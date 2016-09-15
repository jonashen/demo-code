class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  #layout :layout
  protect_from_forgery with: :exception

  before_filter :set_mailer_url_options

  rescue_from CanCan::AccessDenied do |exception|
    if current_user
      redirect_to main_app.root_url, :alert => "Sorry, you have no ability to access this page."
    else
      redirect_to new_user_session_path, :alert => "Please sign in first."
    end
  end

  def index
    @products = Product.random_products
  end

  def set_mailer_url_options
    ActionMailer::Base.default_url_options[:host] = with_relative_url(ActionController::Base.config.relative_url_root)
  end

  private

  def layout
    # only turn it off for login/register pages
    devise_controller? ? 'default' : 'application'
  end


  def with_relative_url(relative_url)
    relative_url ||= ''
    host = request.host_with_port
    [host, relative_url].join
  end

  def after_sign_in_path_for(resource)
    unless params[:command].blank?
      case params[:command]
      when 'sell-now'
        return user_users_products_path(current_user)
      end
    end

    Rails.logger.debug "after sign_in redirect_to = #{params[:redirect_to]}"
    unless params[:redirect_to].blank?
      return params[:redirect_to]
    else
      return root_path
    end
  end
end
