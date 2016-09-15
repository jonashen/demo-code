
class SessionsController < Devise::SessionsController

  ## override sign_in of devise
  def create

    Rails.logger.debug "request.referer before= #{request.referer}"
    super
    Rails.logger.debug "request.referer after= #{request.referer}"

  end

end