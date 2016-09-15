
module Users


  class RegistrationsController < Devise::RegistrationsController

    before_filter :update_sanitized_params, if: :devise_controller?

    def update_sanitized_params
      devise_parameter_sanitizer.for(:sign_up) {|u| u.permit(:email, :second_email, :password, :password_confirmation, :name)}
    end

    def after_inactive_sign_up_path_for(resource)
      Rails.logger.debug "after inactive_sign_in redirect_to = #{params[:redirect_to]}"
      unless params[:redirect_to].blank?
        return params[:redirect_to]
      else
        return root_path
      end
    end

  end

end