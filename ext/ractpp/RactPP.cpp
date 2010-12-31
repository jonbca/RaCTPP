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
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Module.hpp"
#include "rice/Exception.hpp"

using namespace Rice;

extern "C"
void Init_core() {
	Module rb_mRactPP = define_module("RaCTPP");
		
	Data_Type<FaCTReasoner> rb_cRactPP = 
		define_class_under<FaCTReasoner>(rb_mRactPP, "RaCTPP")
		.define_constructor(Constructor<FaCTReasoner>())
		.define_method("get_version", &FaCTReasoner::getReasonerVersion)
		.define_method("kb_preprocessed?", &FaCTReasoner::isKBPreprocessed)
		.define_method("kb_classified?", &FaCTReasoner::isKBClassified)
		.define_method("kb_realised?", &FaCTReasoner::isKBRealised)
		.define_method("clear_kb!", &FaCTReasoner::clearKB)
		.define_method("set_top_bottom_property_names", &FaCTReasoner::setTopBottomPropertyNames)
		.define_method("classify", &FaCTReasoner::classify)
		.define_method("realise", &FaCTReasoner::realise)
		.define_method("error", &FaCTReasoner::error);
}
