FactoryGirl.define do

  factory :book do
     
    trait :english do
      name 'english'
      isbn '9000000001'
    end

    trait :math do
      name 'math'
      isbn '9000000002'
    end

    trait :chinese do
      name 'chinses'
      isbn '9000000003'
    end

    trait :chemistry do
      name 'chemistry'
      isbn '9000000004'
    end

  end
  
end