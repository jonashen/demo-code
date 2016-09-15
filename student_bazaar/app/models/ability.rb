class Ability
  include CanCan::Ability

  def initialize(user)

    #user ||= User.new # guest user (not logged in)
    if user.nil?
      anonymous_user_ability
    else
      anonymous_user_ability
      logged_user_ability(user)
    end

  end

  private

  def anonymous_user_ability
    can :newest, Product
    can :read, Category
    can :sub_categories, Category
    can :read, Book
    can :read, Other
    can :read, Product
    can :read, User
    can :show_detail, Book
    can :show_detail, Other
    can :show_profile, User
  end

  def logged_user_ability(user)
    can :manage, User, id: user.id
    can :manage, Book
    can :manage, Other

    can :manage, UsersProduct, user_id: user.id
    can :finish_order, UsersProduct, user_id: user.id
    can :reject_all, UsersProduct, user_id: user.id

    # profile
    #can :edit_profile, User, id: user.id
    #can :update_profile, User, id: user.id
    can :change_name, User, id: user.id
    can :change_password, User, id: user.id

    # shopping histories
    can :show_shopping_histories, User, id: user.id

    # shopping cart
    can :add_to_cart, User, id: user.id
    can :remove_from_cart, User, id: user.id
    can :show_cart, User, id: user.id
  end
end
