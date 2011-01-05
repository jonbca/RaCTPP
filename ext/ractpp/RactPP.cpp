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

Enum<EntityType> rb_cEntityType;
Data_Type<FaCTReasoner> rb_cRactPP;
Data_Type<Entity> rb_cEntity;

/**
* Map the EntityType enum to a Ruby symbol
*/
Symbol entityTypeSymbol(EntityType t) {
	return Symbol(EntityTypes[t].c_str());
}

/* Convert the entity pointer into a long for Ruby consumption */
long getNodeId(Entity const &e) {
	return reinterpret_cast<long>(e.getEntityPointer());
}

/*
Compare equality of two Entity objects. Two Entity objects
are equal if their node IDs are the same.
*/
bool entityEquals(Object lhs, Object rhs) {
	/* handle case where RHS is nil */
	if(rhs.is_instance_of(rb_cNilClass)) {
		return false;
	}
	
	/* raise error if the RHS is not the same as the LHS */
	if(!rhs.is_instance_of(rb_cEntity)) {
		String lhs_name(lhs.class_of().name());
		String rhs_name(rhs.class_of().name());
		rb_raise(
			rb_eTypeError,
			"Cannot compare %s to %s",
			lhs_name.c_str(),
			rhs_name.c_str());
	}
	
	Data_Object<Entity> l(lhs, rb_cEntity);
	Data_Object<Entity> r(rhs, rb_cEntity);
	
	/* check the node ids are equal */
	return l->getEntityPointer() == r->getEntityPointer();
}

extern "C"
void Init_core() {

	/* top level module */
	Module rb_mRactPP = define_module("RaCTPP");
	
	rb_cEntityType = define_enum<EntityType>("EntityType")
					.define_value(EntityTypes[ClassType].c_str(), ClassType)
					.define_value(EntityTypes[IndividualType].c_str(), IndividualType)
					.define_value(EntityTypes[ObjectPropertyType].c_str(), ObjectPropertyType)
					.define_value(EntityTypes[DataPropertyType].c_str(), DataPropertyType)
					.define_value(EntityTypes[DataTypeType].c_str(), DataTypeType)
					.define_value(EntityTypes[DataTypeExpressionType].c_str(), DataTypeExpressionType)
					.define_value(EntityTypes[AxiomType].c_str(), AxiomType)
					.define_value(EntityTypes[DataTypeFacetType].c_str(), DataTypeFacetType)
					.define_value(EntityTypes[DataValueType].c_str(), DataValueType)
					.define_method("symbol", &entityTypeSymbol);
	
	rb_cEntity = define_class_under<Entity>(rb_mRactPP, "Entity")
				.define_method("name", &Entity::getName)
				.define_method("type", &Entity::getType)
				.define_method("node", &getNodeId)
				.define_method("==", &entityEquals)
				.define_method("eql?", &entityEquals)
				.define_method("inspect", &Entity::to_s)
				.define_method("to_s", &Entity::to_s);

	/* define the reasoner class */
	rb_cRactPP = 
		define_class_under<FaCTReasoner>(rb_mRactPP, "RaCTPP")
		.define_constructor(Constructor<FaCTReasoner>())
		.define_method("version", &FaCTReasoner::getReasonerVersion)
		.define_method("preprocessed?", &FaCTReasoner::isKBPreprocessed)
		.define_method("classified?", &FaCTReasoner::isKBClassified)
		.define_method("realised?", &FaCTReasoner::isKBRealised)
		.define_method("clear_kb!", &FaCTReasoner::clearKB)
		.define_method("set_top_bottom_property_names", &FaCTReasoner::setTopBottomPropertyNames)
		.define_method("classify", &FaCTReasoner::classify)
		.define_method("realise", &FaCTReasoner::realise)
		.define_method("top", &FaCTReasoner::getTop)
		.define_method("bottom", &FaCTReasoner::getBottom)
		.define_method("class_named", &FaCTReasoner::getClassByName)
		.define_method("top_object_property", &FaCTReasoner::getTopObjectProperty)
		.define_method("bottom_object_property", &FaCTReasoner::getBottomObjectProperty)
		.define_method("object_property", &FaCTReasoner::getObjectProperty)
		.define_method("top_data_property", &FaCTReasoner::getTopDataProperty)
		.define_method("bottom_data_property", &FaCTReasoner::getBottomDataProperty)
		.define_method("data_property", &FaCTReasoner::getDataProperty)
		.define_method("individual", &FaCTReasoner::getIndividual)
		.define_method("one_of", &FaCTReasoner::getDataEnumeration)
		.define_method("restriction", &FaCTReasoner::getRestrictedDataType)
		.define_method("data_type", &FaCTReasoner::getBuiltInDataType)
		.define_method("data_value", &FaCTReasoner::getDataValue)
		.define_method("min_inclusive_facet", &FaCTReasoner::getMinInclusiveFacet)
		.define_method("min_exclusive_facet", &FaCTReasoner::getMinExclusiveFacet)
		.define_method("max_inclusive_facet", &FaCTReasoner::getMaxInclusiveFacet)
		.define_method("max_exclusive_facet", &FaCTReasoner::getMaxExclusiveFacet);
}
