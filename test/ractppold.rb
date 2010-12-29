require "../src/ractpp"
require "test/unit"

class TestRaCTPP < MiniTest::Unit::TestCase
  def test_init
    rpp = RactPP.new
  end
  
  def test_get_version
    rpp = RactPP.new
    assert_equal("1.5.0", rpp.get_version)
  end
  
  def test_is_preprocessed_no_ontology
    rpp = RactPP.new
    assert_equal(false, rpp.kb_preprocessed?)
  end
  
  def test_is_classified_no_ontology
    rpp = RactPP.new
    assert_equal(false, rpp.kb_classified?)
  end
  
  def test_is_realised_no_ontology
    rpp = RactPP.new
    assert_equal(false, rpp.kb_realised?)
  end
end