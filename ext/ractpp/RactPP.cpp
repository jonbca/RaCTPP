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
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Module.hpp"
#include "rice/Exception.hpp"
#include "rice/Enum.hpp"
#include "rice/Symbol.hpp"

using namespace Rice;

namespace {
Rice::Enum<EntityType> entity_enum_type;
Rice::Data_Type<FaCTReasoner> rb_cRactPP;
Rice::Data_Type<Entity> rb_cEntity;

/* Ruby symbols to represent the concept types in an ontology */
Rice::Symbol rb_sClassType;
Rice::Symbol rb_sIndividualType;
Rice::Symbol rb_sUnknownType;
Rice::Symbol rb_sObjectPropertyType;

/**
* Map the EntityType enum to a Ruby symbol
*/
Symbol entityTypeSymbol(EntityType t) {
	switch(t) {
		case Class: return rb_sClassType;
		case Individual: return rb_sIndividualType;
		case ObjectProperty: return rb_sObjectPropertyType;
	}
	return rb_sUnknownType;
}
}; // namespace

extern "C"
void Init_core() {
	/* top level module */
	Module rb_mRactPP = define_module("RaCTPP");
	
	/* define the concept type symbols */
	rb_sClassType = Symbol(":class");
	rb_sIndividualType = Symbol(":individual");
	rb_sUnknownType = Symbol(":unknown");
	rb_sObjectPropertyType = Symbol(":object_property");
	
	rb_cEntity = define_class_under<Entity>(rb_mRactPP, "Entity");
	
	/* define the reasoner class */
	rb_cRactPP = 
		define_class_under<FaCTReasoner>(rb_mRactPP, "RaCTPP")
		.define_constructor(Constructor<FaCTReasoner>())
		.define_method("get_version", &FaCTReasoner::getReasonerVersion)
		.define_method("kb_preprocessed?", &FaCTReasoner::isKBPreprocessed)
		.define_method("kb_classified?", &FaCTReasoner::isKBClassified)
		.define_method("kb_realised?", &FaCTReasoner::isKBRealised)
		.define_method("clear_kb!", &FaCTReasoner::clearKB)
		.define_method("set_top_bottom_property_names", &FaCTReasoner::setTopBottomPropertyNames)
		.define_method("classify", &FaCTReasoner::classify)
		.define_method("realise", &FaCTReasoner::realise);
}
