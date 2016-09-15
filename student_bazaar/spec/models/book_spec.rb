require 'spec_helper'

describe Book do
  
  context "attributes" do

    let(:book) { Book.new }

    it 'has name' do
      expect(book.respond_to? :name).to be_true
    end

    it 'has isbn' do
      expect(book.respond_to? :isbn).to be_true
    end

    it 'has cover_image' do
      expect(book.respond_to? :cover_image).to be_true
    end

  end

  context "validations" do

  end

end