
class ProductsController < ApplicationController  

  load_and_authorize_resource :product, except: [:index, :search]

  def search
    search_word = params[:term].blank? ? params[:search_all] : params[:term]
    Rails.logger.debug "search: #{search_word}"
    
    @products_from_solr = Product.search do
      fulltext search_word do
        phrase_fields name: 5.0, description: 1.5
        query_phrase_slop 2                
      end
      paginate page: params[:page]
    end.results unless search_word.blank?

    @products = Product.joins(:categories).
      joins('LEFT JOIN users_products ON products.id = users_products.product_id').
      where('aasm_state = ?', 'auctioning').
      select('DISTINCT products.id, products.*')

    @products = @products.where(id: @products_from_solr) unless search_word.blank?

    unless params[:tag_id].blank?
      @products = @products.joins('LEFT JOIN taggings ON taggings.taggable_id = users_products.id AND taggable_type = "UsersProduct"').
                    joins('LEFT JOIN tags ON taggings.tag_id = tags.id').
                    where('tag_id = ?', params[:tag_id])
    end

    respond_to do |format|
      format.html { render action: "index" }
      format.json { render action: "search" }
    end    
  end

  def newest
    @products = Product.newest_products_from_cache
    render 'index'
  end

  def index
    @products = Product.joins(:categories).
      joins('LEFT JOIN users_products ON products.id = users_products.product_id').
      where('aasm_state = ?', 'auctioning').
      select('DISTINCT products.id, products.*').
      page params[:page]    

    Rails.logger.debug "count: #{@products.count}"
  end

end

