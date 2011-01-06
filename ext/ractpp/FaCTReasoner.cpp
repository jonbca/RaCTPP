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

#define NEED_KERNEL_H
#include "FaCTReasoner.h"

/* quick shorthand for expression manager from Kernel member */
#define EM Kernel->getExpressionManager()

template <typename T>
static T* unpackageEntity(Entity* const e) {
	return dynamic_cast<T*>((ReasoningKernel::TExpr*)e->getEntityPointer());
}

/* Unpackage a TDL pointer from the Entity class that contains it. This method
forces the return of a const pointer. */
template <typename T>
static const T* unpackageROEntity(Entity* const e) {
	return dynamic_cast<const T*>((const ReasoningKernel::TExpr*)e->getEntityPointer());
}

FaCTReasoner::FaCTReasoner()
	: Kernel(new ReasoningKernel)
{
	// Do Nothing
}

FaCTReasoner::~FaCTReasoner() {
	delete Kernel;
}

const char* FaCTReasoner::getReasonerVersion(void) {
	return ReasoningKernel::getVersion();
}

void FaCTReasoner::setTopBottomPropertyNames(const char* topORoleName,
	const char* botORoleName, const char* topDRoleName, const char* botDRoleName) {
	Kernel->setTopBottomRoleNames(topORoleName, botORoleName, topDRoleName, botDRoleName);
}

bool FaCTReasoner::isKBPreprocessed(void) const {
	return Kernel->isKBPreprocessed();
}

bool FaCTReasoner::isKBClassified(void) const {
	return Kernel->isKBClassified();
}

bool FaCTReasoner::isKBRealised(void) const {
	return Kernel->isKBRealised();
}

bool FaCTReasoner::clearKB(void) {
	return Kernel->clearKB();
}

void FaCTReasoner::classify(void) {
	Kernel->classifyKB();
}

void FaCTReasoner::realise(void) {
	Kernel->realiseKB();
}

Entity* FaCTReasoner::getTop(void) {
	ReasoningKernel::TConceptExpr* top = EM->Top();
	
	Entity *entity = new Entity(top, "Thing", ClassType);
	
	return entity;
}

Entity* FaCTReasoner::getBottom(void) {
	ReasoningKernel::TConceptExpr* bottom = EM->Bottom();
	
	Entity *entity = new Entity(bottom, "Nothing", ClassType);
	
	return entity;
}

Entity* FaCTReasoner::getClassByName(std::string const &name) {
	ReasoningKernel::TConceptExpr* clazz = EM->Concept(name.c_str());
	
	Entity *entity = new Entity(clazz, name, ClassType);
	
	return entity;
}

Entity* FaCTReasoner::getObjectProperty(std::string const &name) {
	ReasoningKernel::TORoleExpr* orole = 
		EM->ObjectRole(name.c_str());
	
	Entity *entity = new Entity(orole, name.c_str(), ObjectPropertyType);
	return entity;
}

Entity* FaCTReasoner::getTopObjectProperty(void) {
	return getObjectProperty("http://www.w3.org/2002/07/owl#topObjectProperty");
}

Entity* FaCTReasoner::getBottomObjectProperty(void) {
	return getObjectProperty("http://www.w3.org/2002/07/owl#bottomObjectProperty");
}

Entity* FaCTReasoner::getDataProperty(std::string const &name) {
	ReasoningKernel::TDRoleExpr* drole = EM->DataRole(name.c_str());
	Entity *entity = new Entity(drole, name.c_str(), DataPropertyType);
	
	return entity;
}

Entity* FaCTReasoner::getTopDataProperty(void) {
	return getDataProperty("http://www.w3.org/2002/07/owl#topDataProperty");
}

Entity* FaCTReasoner::getBottomDataProperty(void) {
	return getDataProperty("http://www.w3.org/2002/07/owl#bottomDataProperty");
}

Entity* FaCTReasoner::getIndividual(std::string const &name) {
	ReasoningKernel::TIndividualExpr* indiv =
		EM->Individual(name);
		
	Entity *entity = new Entity(indiv, name.c_str(), IndividualType);
	return entity;
}

static Entity* const makeEntityForDataType(TExpressionManager *em, std::string const &name) {
	if(    name == "http://www.w3.org/2000/01/rdf-schema#Literal"
		|| name == "http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral"
		|| name == "http://www.w3.org/2001/XMLSchema#string"
		|| name == "http://www.w3.org/2001/XMLSchema#anyURI" ) {
			return new Entity(em->getStrDataType(), name, DataTypeType);
	} else if (	   name == "http://www.w3.org/2001/XMLSchema#integer" 
				|| name == "http://www.w3.org/2001/XMLSchema#int"
				|| name == "http://www.w3.org/2001/XMLSchema#nonNegativeInteger") {
			return new Entity(em->getIntDataType(), name, DataTypeType);
	} else if (    name == "http://www.w3.org/2001/XMLSchema#float"
				|| name == "http://www.w3.org/2001/XMLSchema#double") {
			return new Entity(em->getRealDataType(), name, DataTypeType);
	} else if (    name == "http://www.w3.org/2001/XMLSchema#boolean") {
			return new Entity(em->getBoolDataType(), name, DataTypeType);
	}
	
	std::stringstream err;
	err << "Unsupported datatype '" << name.c_str() << "'";
	
	throw RaCTPPException(err.str());
}

Entity* FaCTReasoner::getBuiltInDataType(std::string const &name) {
	return makeEntityForDataType(EM, name);
}

Entity* FaCTReasoner::getDataTop(void) {
	return new Entity(EM->DataTop(), "DataTop", DataTypeType);
}

Entity* FaCTReasoner::getDataEnumeration(void) {
	
	throw RaCTPPException("getDataEnumeration not yet implemented.");
	
	//return new Entity(EM->DataOneOf(), "DataOneOf", DataTypeExpressionType);
}

Entity* FaCTReasoner::getRestrictedDataType(Entity* datatype, Entity* facet) {
	std::stringstream name;
	
	name << "Restricted Type: " << datatype->name << " " << facet->name;
	
	return new Entity(
		EM->RestrictedType(const_cast<TDLDataTypeExpression*>(unpackageROEntity<TDLDataTypeExpression>(datatype)), unpackageROEntity<TDLFacetExpression>(facet)),
		name.str(),
		DataTypeExpressionType
	);
}

Entity* FaCTReasoner::getMinExclusiveFacet(Entity* value) {
	std::stringstream name;
	
	name << "xmin: " << value->name;
	
	return new Entity(
		EM->FacetMinExclusive(unpackageROEntity<TDLDataValue>(value)),
		name.str(),
		DataTypeFacetType);
}

Entity* FaCTReasoner::getMaxExclusiveFacet(Entity* value) {
	std::stringstream name;
	
	name << "xmax: " << value->name;
	
	return new Entity(
		EM->FacetMaxExclusive(unpackageROEntity<TDLDataValue>(value)),
		name.str(),
		DataTypeFacetType);
}

Entity* FaCTReasoner::getMinInclusiveFacet(Entity* value) {
	std::stringstream name;
	
	name << "min: " << value->name;
	
	return new Entity(
		EM->FacetMinInclusive(unpackageROEntity<TDLDataValue>(value)),
		name.str(),
		DataTypeFacetType);
}

Entity* FaCTReasoner::getMaxInclusiveFacet(Entity* value) {
	std::stringstream name;
	
	name << "max: " << value->name;
	
	return new Entity(
		EM->FacetMaxInclusive(unpackageROEntity<TDLDataValue>(value)),
		name.str(),
		DataTypeFacetType);
}

Entity* FaCTReasoner::getDataValue(std::string const &name, Entity* type) {
	/* Intentionally casting away const-ness because DataTypes aren't really const
	but they are stored as const in the Entity. The Entity stores them as const
	because almost everything else in the app is const, so this is an exception
	to the rule. */
	return new Entity(
		EM->DataValue(name.c_str(), const_cast<TDLDataTypeExpression*>(unpackageROEntity<TDLDataTypeExpression>(type))),
		name,
		DataValueType);
}

Entity* FaCTReasoner::getDataNot(Entity* value) {
	std::stringstream name;
	name << "Not " << value->name;
	
	return new Entity(
		EM->DataNot(unpackageROEntity<TDLDataExpression>(value)),
		name.str(),
		DataTypeExpressionType);
}

Entity* FaCTReasoner::getDataIntersectionOf(void) {
	return new Entity(EM->DataAnd(), "Intersection", DataTypeExpressionType);
}

Entity* FaCTReasoner::getDataUnionOf(void) {
	return new Entity(EM->DataOr(), "Intersection", DataTypeExpressionType);
}

Entity* FaCTReasoner::getConceptAnd(void) {
	
}

Entity* FaCTReasoner::getConceptOr(void) {
	
}

Entity* FaCTReasoner::getConceptNot(Entity* value) {
	
}

Entity* FaCTReasoner::getObjectSome(Entity* role, Entity* concept) {
	
}

Entity* FaCTReasoner::getObjectAll(Entity* role, Entity* concept) {
	
}
