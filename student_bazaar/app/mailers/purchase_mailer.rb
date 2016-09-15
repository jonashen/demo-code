
class PurchaseMailer < ActionMailer::Base
  default from: 'system@studentbazaar.io'

  def purchase_email(buyer, seller, users_product, host)
    @buyer = buyer
    @seller = seller
    @users_product = users_product
    @host = host

    mail to: seller.email, subject: 'Purchase Notification From Student Bazaar'
  end

end