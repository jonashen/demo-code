

class CategoriesController < ApplicationController
  load_and_authorize_resource

  def sub_categories
    #authorize! :sub_categories, :categoires

    @category = Category.find(params[:category_id])

    render json: @category.children.to_json
  end

end

