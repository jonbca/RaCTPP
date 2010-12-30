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
    @rpp.get_version.should == "1.5.0"
  end
  # 
  # it "should not be pre-processed when no ontology is present" do
  #   @rpp.kb_preprocessed?.should == false
  # end
  # 
  # it "should not be classified when no ontology is present" do
  #   @rpp.kb_classified?.should == false
  # end
  # 
  # it "should not be realised when no ontology is present" do
  #   @rpp.kb_realised?.should == false
  # end
  # 
  # it "should clear the knowledge base" do
  #   @rpp.clear_kb!.should == true
  # end
  # 
  # it "should set the top and bottom object and data names" do
  #   @rpp.set_top_bottom_property_names("topObject", "botObject", "topData", "botData").should == nil
  # end
  # 
  # it "should classify an empty kb without raising an exception" do
  #   @rpp.classify.should == nil
  # end
  # 
  # it "should realise an empty kb without raising an exception" do
  #   @rpp.realise.should == nil
  # end
end