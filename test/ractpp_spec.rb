require_relative '../lib/ractpp/core'

describe RactPP do
  before(:each) do
    @rpp = RactPP.new
  end
  
  it "should create a new reasoner" do
    @rpp.should_not == nil
  end
  
  it "should have reasoner version 1.5.0" do
    @rpp.get_version.should == "1.5.0"
  end
  
  it "should not be pre-processed when no ontology is present" do
    @rpp.kb_preprocessed?.should == false
  end
  
  it "should not be classified when no ontology is present" do
    @rpp.kb_classified?.should == false
  end
  
  it "should not be realised when no ontology is present" do
    @rpp.kb_realised?.should == false
  end
  
  it "should clear the knowledge base" do
    @rpp.clear_kb! == true
  end
end