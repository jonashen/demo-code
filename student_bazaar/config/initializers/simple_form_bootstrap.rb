# Use this setup block to configure all options available in SimpleForm.
inputs = %w[
  CollectionSelectInput
  DateTimeInput
  FileInput
  GroupedCollectionSelectInput
  NumericInput
  PasswordInput
  RangeInput
  StringInput
  TextInput
]
 
inputs.each do |input_type|
  superclass = "SimpleForm::Inputs::#{input_type}".constantize

  new_class = Class.new(superclass) do
    def input_html_classes
      super.push('form-control')
    end
  end

  Object.const_set(input_type, new_class)
end
 
# Use this setup block to configure all options available in SimpleForm.
SimpleForm.setup do |config|
  config.boolean_style = :nested

  config.wrappers :bootstrap3, tag: 'div', class: 'form-group', error_class: 'has-error',
    defaults: { input_html: { class: 'default_class' } } do |b|

    b.use :html5
    b.use :min_max
    b.use :maxlength
    b.use :placeholder

    b.optional :pattern
    b.optional :readonly

    b.use :label_input
    b.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
    b.use :error, wrap_with: { tag: 'span', class: 'has-error' }
  end

  config.wrappers :bootstrap3_horizontal, tag: 'div', class: 'form-group', error_class: 'has-error',
    defaults: { input_html: { class: 'default-class '}, wrapper_html: { class: "col-lg-10 col-md-10"} } do |b|

    b.use :html5
    b.use :min_max
    b.use :maxlength
    b.use :placeholder

    b.optional :pattern
    b.optional :readonly

    b.use :label
    b.wrapper :right_column, tag: :div do |component|
      component.use :input
      component.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
      component.use :error, wrap_with: { tag: 'span', class: 'has-error' }
    end
#     b.use :label
#     b.wrapper :right_column, tag: :div do |component|
#       component.use :input
#     end
#     b.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
#     b.use :error, wrap_with: { tag: 'span', class: 'help-block has-error' }
  end

  config.wrappers :group, tag: 'div', class: "form-group", error_class: 'has-error',
    defaults: { input_html: { class: 'default-class '} }  do |b|

    b.use :html5
    b.use :min_max
    b.use :maxlength
    b.use :placeholder

    b.optional :pattern
    b.optional :readonly

    b.use :label
    b.wrapper :right_column, tag: :div, class: 'input-group' do |ba|
      ba.use :input #, wrap_with: { class: "input-group" }
      ba.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
      ba.use :error, wrap_with: { tag: 'span', class: 'help-block has-error' }
    end
  end

  config.wrappers :prepend, tag: 'div', class: "form-group", error_class: 'has-error' do |b|
    b.use :html5
    b.use :placeholder
    b.use :label
    b.wrapper tag: 'div', class: 'controls' do |input|
      input.wrapper tag: 'div', class: 'input-prepend' do |prepend|
        prepend.use :input
      end
      input.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
      input.use :error, wrap_with: { tag: 'span', class: 'help-inline has-error' }
    end
  end

  config.wrappers :append, tag: 'div', class: "form-group", error_class: 'has-error' do |b|
    b.use :html5
    b.use :placeholder
    b.use :label
    b.wrapper tag: 'div', class: 'controls' do |input|
      input.wrapper tag: 'div', class: 'input-append' do |append|
        append.use :input
      end 
      input.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
      input.use :error, wrap_with: { tag: 'span', class: 'help-inline has-error' }
    end 
  end 

  config.wrappers :bootstrap_switch, tag: 'div', class: "form-group", error_class: 'has-error', boolean_style: :inline do |b|
    b.use :html5
    b.use :placeholder
    b.use :label

    b.wrapper :right_column, tag: :div do |ba|
      ba.wrapper :switch, tag: 'div', class: 'make-switch' do |s|
        s.use :input
      end
      ba.use :error, wrap_with: { tag: 'span', class: 'help-inline has-error' }
      ba.use :hint,  wrap_with: { tag: 'p', class: 'help-block' }
    end
  end

  config.wrappers :checkbox, tag: :div, class: "checkbox", error_class: "has-error" do |b|
    # Form extensions
    b.use :html5
    # Form components

    b.wrapper tag: :label do |ba|
      ba.use :input
      ba.use :label_text
    end
    b.use :hint,  wrap_with: { tag: :p, class: "help-block" }
    b.use :error, wrap_with: { tag: :span, class: "help-block text-danger" }
  end

  config.wrappers :select2, tag: 'div', class: 'form-group', error_class: 'has-error',
    defaults: { input_html: { class: 'default-class '}, wrapper_html: { class: "col-lg-10 col-md-10"} } do |b|

    b.use :html5
    b.use :min_max
    b.use :maxlength
    b.use :placeholder

    b.optional :pattern
    b.optional :readonly

    b.use :label
    b.wrapper :right_column, tag: :div do |component|
      component.use :input
      component.use :hint,  wrap_with: { tag: 'span', class: 'help-block' }
      component.use :error, wrap_with: { tag: 'span', class: 'help-block has-error' }
    end
  end

  config.default_wrapper = :bootstrap3
end

