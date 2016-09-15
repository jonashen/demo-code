module ApplicationHelper

  #
  # 網頁 Title
  #
  def title(page_title)
    content_for(:title) { page_title || "首頁" }
  end

  #
  # 網頁 表頭(head)
  #
  def javascript(*script_filename)
    #content_for(:head) { javascript_include_tag script_filename}
    script_filename.map { |source|
      content_for(:js) { javascript_include_tag source}
    }
  end

  def render_notification
    script = ""
    flash.each do |name, msg|
      if msg.is_a?(String)
        script += "notification(\"#{msg}\", \"#{name == :notice ? 'success' : name}\");"
      end
      flash["#{name}".to_sym] = nil
    end
    script.html_safe
  end

  def validation_of(klass)
    rules = {}
    klass.validators.each do |v|
      #name = v.attributes[0]
      name = "#{klass.to_s.underscore}[#{v.attributes[0]}]"
      if v.class.to_s =~ /ConfirmationValidator/
        rules.merge!(confirm_validator_to_json(name, v))
      else
        rules[name] = {} unless rules.has_key?(name)
        validator_to_json(rules[name], v.options)
      end
    end
    
    Rails.logger.debug "rule json:#{rules.to_json}"
    return rules.to_json
  end

  private
  
  def confirm_validator_to_json(name, validator)
    {'confirm_' + name.to_s => [{:eqTo => name}, validator.options[:message]]}
  end

  def validator_to_json(rule, options)
     Rails.logger.debug "1 rule:#{rule}, options: #{options}"
    rule[:required] = !options[:allow_blank] if options.has_key?(:allow_blank)
    #rule << {:required => !options[:allow_blank]} if options.has_key?(:allow_blank)
    #rule << {:min => options[:minimum]} if options.has_key?(:minimum)
    #rule << {:max => options[:maximum]} if options.has_key?(:maximum)
    #rule << {:regex => options[:with].source} if options.has_key?(:with)
    #rule << {:digits => true} if options.has_key?(:only_integer)
    #rule << {:binc => [options[:in].begin, options[:in].end]} if options.has_key?(:in)
    #rule << options[:message] 
    

    #rule.compact!
    Rails.logger.debug "2 rule:#{rule}"
  end  
end
