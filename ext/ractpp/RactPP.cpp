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

/* the Ruby class */
VALUE cFactPP;
VALUE cFactReasoner;

void free_reasoner(FaCTReasoner *reasoner) {
	delete reasoner;
}
	
static VALUE t_init(VALUE self) {
	FaCTReasoner *reasoner = new FaCTReasoner;
	VALUE r;
	
	r = Data_Wrap_Struct(cFactReasoner, NULL, free_reasoner, reasoner);
	rb_iv_set(self, "@reasoner", r);
	return self;
}

static VALUE t_getVersion(VALUE self) {
	const char* version = FaCTReasoner::getReasonerVersion();
	return rb_str_new2(version);
}

static VALUE t_isKBPreprocessed(VALUE self) {
	FaCTReasoner *reasoner;
	reasoner = (FaCTReasoner *) DATA_PTR(rb_iv_get(self, "@reasoner"));
	return reasoner->isKBPreprocessed() ? Qtrue : Qfalse;
}

static VALUE t_isKBClassified(VALUE self) {
	FaCTReasoner *reasoner;
	reasoner = (FaCTReasoner *) DATA_PTR(rb_iv_get(self, "@reasoner"));
	return reasoner->isKBClassified() ? Qtrue : Qfalse;
}

static VALUE t_isKBRealised(VALUE self) {
	FaCTReasoner *reasoner;
	reasoner = (FaCTReasoner *) DATA_PTR(rb_iv_get(self, "@reasoner"));
	return reasoner->isKBRealised() ? Qtrue : Qfalse;
}

void Init_core() {
	cFactPP = rb_define_class("RactPP", rb_cObject);
	cFactReasoner = rb_define_class("FaCTReasoner", rb_cObject);
	rb_define_method(cFactPP, "initialize", (VALUE (*)(...)) t_init, 0);
	rb_define_method(cFactPP, "get_version", (VALUE (*)(...)) t_getVersion, 0);
	rb_define_method(cFactPP, "kb_preprocessed?", (VALUE (*)(...)) t_isKBPreprocessed, 0);
	rb_define_method(cFactPP, "kb_realised?", (VALUE (*)(...)) t_isKBRealised, 0);
	rb_define_method(cFactPP, "kb_classified?", (VALUE(*)(...)) t_isKBClassified, 0);
}

#ifdef __cplusplus
}
#endif