class ShoppingCart < Cart

  class << self

    def get_cart(session_id, shopper = nil)
      cart = ShoppingCart.where(state: 'active', session_id: session_id).last            

      unless cart
        cart = self.new
        cart.shopper = shopper
        cart.session_id = session_id
        cart.save!
      end

      cart
    end

  end  

  # @override 
  def add_item(new_item)    
    return nil unless new_item.auctioning?

    item = cart_items.where(cartable_type: UsersProduct.to_s, cartable_id: new_item.id).first
    item = super(new_item) unless item

    item
  end

  def remove_item(item)
    item = cart_items.where(cartable_type: UsersProduct.to_s, cartable_id: item.id).first
    item.destroy if item

    item
  end

end