# Copyright (C) 2010 Jonathan Abourbih
# 
# This file is part of RactPP, the Ruby-FaCT++ Bridge.
# 
# RactPP is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# RactPP is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with RactPP.  If not, see <http://www.gnu.org/licenses/>.
require_relative '../lib/ractpp/core'

describe RaCTPP do
  before(:each) do
    @rpp = RaCTPP::RaCTPP.new
  end
  
  it "should create a new reasoner" do
    @rpp.should_not == nil
  end
  
  it "should have reasoner version 1.5.0" do
    @rpp.version.should == "1.5.0"
  end
  
  it "should not be pre-processed when no ontology is present" do
    @rpp.preprocessed?.should == false
  end
  
  it "should not be classified when no ontology is present" do
    @rpp.classified?.should == false
  end
  
  it "should not be realised when no ontology is present" do
    @rpp.realised?.should == false
  end
  
  it "should clear the knowledge base" do
    @rpp.clear_kb!.should == true
  end
  
  it "should set the top and bottom object and data names" do
    @rpp.set_top_bottom_property_names("topObject", "botObject", "topData", "botData").should == nil
  end
  
  it "should classify an empty kb without raising an exception" do
    @rpp.classify.should == nil
  end
  
  it "should realise an empty kb without raising an exception" do
    @rpp.realise.should == nil
  end
  
  it "should return an entity class for the top concept" do
    @rpp.top.should_not == nil
    @rpp.top.name.should == "Thing"
    @rpp.top.type.symbol.should == :class
    @rpp.top.node.should_not == 0
  end
  
  it "should return an entity class for the bottom concept" do
    @rpp.bottom.should_not == nil
    @rpp.bottom.name.should == "Nothing"
    @rpp.bottom.type.symbol.should == :class
    @rpp.bottom.node.should_not == 0
  end
  
  it "should have different top and bottom concepts" do
    @rpp.bottom.should_not == @rpp.top
  end
  
  it "should have the identical result from calling top twice" do
    @rpp.top.should == @rpp.top
  end
  
  it "should have the identical result from calling bottom twice" do
    @rpp.bottom.should == @rpp.bottom
  end
  
  it "should return identical objects for the same class name" do
    @rpp.class_named("idontexist").should == @rpp.class_named("idontexist")
    @rpp.class_named("idontexist").name.should == "idontexist"
    @rpp.class_named("idontexist").type.symbol.should == :class
  end
  
  it "should return a top object property" do
    @rpp.top_object_property.name.should == "http://www.w3.org/2002/07/owl#topObjectProperty"
    @rpp.top_object_property.type.symbol.should == :object_property
  end
  
  it "should return a bottom object property" do
    @rpp.bottom_object_property.name.should == "http://www.w3.org/2002/07/owl#bottomObjectProperty"
    @rpp.bottom_object_property.type.symbol.should == :object_property
  end
  
  it "should return an object property" do
    @rpp.object_property("test_property").name.should == "test_property"
    @rpp.object_property("test_property").type.symbol.should == :object_property
    @rpp.object_property("test_property").should == @rpp.object_property("test_property")
  end
  
  it "should return a top data property" do
    @rpp.top_data_property.name.should == "http://www.w3.org/2002/07/owl#topDataProperty"
    @rpp.top_data_property.type.symbol.should == :data_property
  end
  
  it "should return a bottom data property" do
    @rpp.bottom_data_property.name.should == "http://www.w3.org/2002/07/owl#bottomDataProperty"
    @rpp.bottom_data_property.type.symbol.should == :data_property
  end
  
  it "should return a data property" do
    @rpp.data_property("test_property").name.should == "test_property"
    @rpp.data_property("test_property").type.symbol.should == :data_property
    @rpp.data_property("test_property").should == @rpp.data_property("test_property")
  end
  
  it "should return an individual" do
    @rpp.individual("test_individual").name.should == "test_individual"
    @rpp.individual("test_individual").type.symbol.should == :individual
    @rpp.individual("test_individual").should == @rpp.individual("test_individual")
  end
  
  it "should not allow comparison between individual and data_property" do
    lambda {@rpp.individual("test_individual_2") == @rpp.data_property("test_property2")}.should raise_error
  end
  
  it "should get a data type for each string URI" do
    # test strings
    arr = ["http://www.w3.org/2000/01/rdf-schema#Literal",
           "http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral",
           "http://www.w3.org/2001/XMLSchema#string",
           "http://www.w3.org/2001/XMLSchema#anyURI"]
    arr.each do |e|
      @rpp.data_type(e).name.should == e
      @rpp.data_type(e).type.symbol.should == :data_type
      arr.each do |f|
        @rpp.data_type(e).node.should == @rpp.data_type(f).node
      end
    end
  end
  
  it "should get a data type for each digit URI" do
    # test digits
    arr = ["http://www.w3.org/2001/XMLSchema#integer",
           "http://www.w3.org/2001/XMLSchema#int",
           "http://www.w3.org/2001/XMLSchema#nonNegativeInteger"]
    arr.each do |e|
      @rpp.data_type(e).name.should == e
      @rpp.data_type(e).type.symbol.should == :data_type
      arr.each do |f|
        @rpp.data_type(e).node.should == @rpp.data_type(f).node
      end
    end
  end

  it "should get a data type for each decimal URI" do
    # test floats
    arr = ["http://www.w3.org/2001/XMLSchema#float",
           "http://www.w3.org/2001/XMLSchema#double"]
    arr.each do |e|
      @rpp.data_type(e).name.should == e
      @rpp.data_type(e).type.symbol.should == :data_type
      arr.each do |f|
        @rpp.data_type(e).node.should == @rpp.data_type(f).node
      end
    end    
  end

  it "should get a data type for the boolean" do
    # test boolean
    b = "http://www.w3.org/2001/XMLSchema#boolean"
    @rpp.data_type(b).name.should == "http://www.w3.org/2001/XMLSchema#boolean"
    @rpp.data_type(b).type.symbol.should == :data_type
  end
  
  it "should return a different data type for each type of URI" do 
    b = "http://www.w3.org/2001/XMLSchema#boolean"
    @rpp.data_type(b).should_not == @rpp.data_type("http://www.w3.org/2001/XMLSchema#float")
    @rpp.data_type(b).should_not == @rpp.data_type("http://www.w3.org/2001/XMLSchema#integer")
    @rpp.data_type(b).should_not == @rpp.data_type("http://www.w3.org/2000/01/rdf-schema#Literal")
  end
  
  it "should raise an error for an unknown data type" do
    lambda { @rpp.data_type "http://unknown.com/error/thing" }.should raise_error
  end
end