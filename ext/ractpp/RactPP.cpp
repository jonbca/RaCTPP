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
#ifdef __cplusplus
#include "FaCTReasoner.h"
#include <iostream>

extern "C" {
#endif
#include "ruby.h"

#define RACT_RB_BOOL(val) \
			val ? Qtrue : Qfalse;

/* the Ruby class */
VALUE cFactPP;

void free_reasoner(FaCTReasoner *reasoner) {
	delete reasoner;
}

static VALUE t_getVersion(VALUE self) {
	const char* version = FaCTReasoner::getReasonerVersion();
	return rb_str_new2(version);
}

static VALUE t_isKBPreprocessed(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	return RACT_RB_BOOL(reasoner->isKBPreprocessed());
}

static VALUE t_isKBClassified(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	return RACT_RB_BOOL(reasoner->isKBClassified());
}

static VALUE t_isKBRealised(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	return RACT_RB_BOOL(reasoner->isKBRealised());
}

static VALUE t_clearKB(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	return RACT_RB_BOOL(reasoner->clearKB());
}

//TODO raises exception
static VALUE t_classify(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	
	return Qnil;
}

//TODO raises exception
static VALUE t_realise(VALUE self) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	
	return Qnil;
}

static VALUE t_setTopBottomPropertyNames(VALUE self, VALUE rTopObjectName, VALUE rBotObjectName, VALUE rTopDataName, VALUE rBotDataName) {
	FaCTReasoner *reasoner;
	Data_Get_Struct(self, FaCTReasoner, reasoner);
	char* topObjectName = RSTRING_PTR(StringValue(rTopObjectName));
	char* botObjectName = RSTRING_PTR(StringValue(rBotObjectName));
	char* topDataName = RSTRING_PTR(StringValue(rTopDataName));
	char* botDataName = RSTRING_PTR(StringValue(rBotDataName));
	
	reasoner->setTopBottomPropertyNames(topObjectName, botObjectName, topDataName, botDataName);
	return Qnil;
}

static VALUE ractpp_alloc(VALUE klass) {
	VALUE obj;
	FaCTReasoner *reasoner = new FaCTReasoner;
	
	obj = Data_Wrap_Struct(klass, 0, free_reasoner, reasoner);
	return obj;
}

void Init_core() {
	cFactPP = rb_define_class("RactPP", rb_cObject);
	rb_define_alloc_func(cFactPP, ractpp_alloc);
	rb_define_method(cFactPP, "get_version", (VALUE (*)(...)) t_getVersion, 0);
	rb_define_method(cFactPP, "kb_preprocessed?", (VALUE (*)(...)) t_isKBPreprocessed, 0);
	rb_define_method(cFactPP, "kb_realised?", (VALUE (*)(...)) t_isKBRealised, 0);
	rb_define_method(cFactPP, "kb_classified?", (VALUE(*)(...)) t_isKBClassified, 0);
	rb_define_method(cFactPP, "clear_kb!", (VALUE(*)(...)) t_clearKB, 0);
	rb_define_method(cFactPP, "classify", (VALUE(*)(...)) t_classify, 0);
	rb_define_method(cFactPP, "realise", (VALUE(*)(...)) t_realise, 0);
	rb_define_method(cFactPP, "set_top_bottom_property_names", (VALUE(*)(...)) t_setTopBottomPropertyNames, 4);
}

#ifdef __cplusplus
}
#endif