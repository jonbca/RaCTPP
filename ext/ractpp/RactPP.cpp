/*
Copyright (C) 2010 Jonathan Abourbih

This file is part of RactPP, the Ruby-FaCT++ Bridge.

RactPP is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RactPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RactPP.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "FaCTReasoner.h"
#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Module.hpp"

using namespace Rice;

Object getVersion(Object /*self*/) {
	String version = FaCTReasoner::getReasonerVersion();
	return version;
}
// 
// static VALUE t_isKBPreprocessed(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	return RACT_RB_BOOL(reasoner->isKBPreprocessed());
// }
// 
// static VALUE t_isKBClassified(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	return RACT_RB_BOOL(reasoner->isKBClassified());
// }
// 
// static VALUE t_isKBRealised(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	return RACT_RB_BOOL(reasoner->isKBRealised());
// }
// 
// static VALUE t_clearKB(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	return RACT_RB_BOOL(reasoner->clearKB());
// }
// 
// static VALUE t_classify(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	
// 	try {
// 		reasoner->classify();
// 	} catch(std::exception e) {
// 		VALUE except = rb_class_new_instance(0, NULL, cRactPPException);
// 		rb_raise(except, "An error occurred doing classification.");
// 	}
// 	
// 	return Qnil;
// }
// 
// //TODO raises exception
// static VALUE t_realise(VALUE self) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	
// 	//reasoner->realise();
// 	rb_raise(cRactPPException, "%s", "An error occurred doing classification.");
// 	return Qnil;
// }
// 
// static VALUE t_setTopBottomPropertyNames(VALUE self, VALUE rTopObjectName, VALUE rBotObjectName, VALUE rTopDataName, VALUE rBotDataName) {
// 	FaCTReasoner *reasoner;
// 	Data_Get_Struct(self, FaCTReasoner, reasoner);
// 	char* topObjectName = RSTRING_PTR(StringValue(rTopObjectName));
// 	char* botObjectName = RSTRING_PTR(StringValue(rBotObjectName));
// 	char* topDataName = RSTRING_PTR(StringValue(rTopDataName));
// 	char* botDataName = RSTRING_PTR(StringValue(rBotDataName));
// 	
// 	reasoner->setTopBottomPropertyNames(topObjectName, botObjectName, topDataName, botDataName);
// 	return Qnil;
// }
// 
// static VALUE ractpp_alloc(VALUE klass) {
// 	VALUE obj;
// 	FaCTReasoner *reasoner = new FaCTReasoner;
// 	
// 	obj = Data_Wrap_Struct(klass, NULL, free_reasoner, reasoner);
// 	return obj;
// }

extern "C"
void Init_core() {
	Module rb_mRactPP = define_module("RaCTPP");
	Class rb_cRactPP =	define_class_under(rb_mRactPP, "RaCTPP")
		.define_method("get_version", &getVersion);
	
	// mRactPPModule = rb_define_module("RaCTPP");
	// 	cFactPP = rb_define_class_under(mRactPPModule, "RaCTPP", rb_cObject);
	// 	cRactPPException = rb_define_class_under(mRactPPModule, "RaCTPPException", rb_cObject);
	// 	
	// 	rb_define_alloc_func(cFactPP, ractpp_alloc);
	// 	rb_define_method(cFactPP, "get_version", (VALUE (*)(...)) t_getVersion, 0);
	// 	rb_define_method(cFactPP, "kb_preprocessed?", (VALUE (*)(...)) t_isKBPreprocessed, 0);
	// 	rb_define_method(cFactPP, "kb_realised?", (VALUE (*)(...)) t_isKBRealised, 0);
	// 	rb_define_method(cFactPP, "kb_classified?", (VALUE(*)(...)) t_isKBClassified, 0);
	// 	rb_define_method(cFactPP, "clear_kb!", (VALUE(*)(...)) t_clearKB, 0);
	// 	rb_define_method(cFactPP, "classify", (VALUE(*)(...)) t_classify, 0);
	// 	rb_define_method(cFactPP, "realise", (VALUE(*)(...)) t_realise, 0);
	// 	rb_define_method(cFactPP, "set_top_bottom_property_names", (VALUE(*)(...)) t_setTopBottomPropertyNames, 4);
	// 	
	// rb_define_method(cRactPPException, "new", (VALUE(*)(...)) t_exc_new, 1);
}
