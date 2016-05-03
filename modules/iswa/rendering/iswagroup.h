/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2015                                                               *
*                                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
* software and associated documentation files (the "Software"), to deal in the Software *
* without restriction, including without limitation the rights to use, copy, modify,    *
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to the following   *
* conditions:                                                                           *
*                                                                                       *
* The above copyright notice and this permission notice shall be included in all copies *
* or substantial portions of the Software.                                              *
*                                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
****************************************************************************************/

#ifndef __ISWAGROUP_H__
#define __ISWAGROUP_H__

#include <openspace/properties/propertyowner.h>
#include <openspace/properties/selectionproperty.h>
#include <openspace/properties/vectorproperty.h>
#include <openspace/rendering/renderengine.h>
#include <openspace/engine/openspaceengine.h>
// #include <modules/iswa/rendering/iswacygnet.h>
#include <modules/iswa/util/iswamanager.h>


namespace openspace{
class ISWACygnet;

class ISWAGroup : public properties::PropertyOwner{
public:
	ISWAGroup(int id, ISWAManager::CygnetType type);
	~ISWAGroup();
	void registerCygnet(ISWACygnet* cygnet, ISWAManager::CygnetType type);
	void unregisterCygnet(ISWACygnet* cygnet);
	void registerOptions(const std::vector<properties::SelectionProperty::Option>& options);

private:
	properties::BoolProperty _enabled;

    properties::BoolProperty _useLog;
    properties::BoolProperty _useHistogram;
    properties::Vec2Property _normValues;
    properties::Vec2Property _backgroundValues;
    properties::StringProperty _transferFunctionsFile;
	properties::SelectionProperty _dataOptions;
	// properties::SelectionProperty _dataOptions;
 //    properties::StringProperty _transferFunctionsFile;
 //    properties::Vec2Property _normValues;
 //    properties::Vec2Property _backgroundValues;
 //    properties::BoolProperty _useLog;
 //    properties::BoolProperty _useHistogram;;

	// int groupId;
	// ISWACygnet cygnet;
	std::vector<ISWACygnet* > _cygnets;
	ISWAManager::CygnetType _type;
};

} //namespace openspace
#endif