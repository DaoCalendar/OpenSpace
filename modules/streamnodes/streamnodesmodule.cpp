/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2020                                                               *
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

#include <modules/streamnodes/streamnodesmodule.h>
#include <modules/streamnodes/rendering/renderablestreamnodes.h>
#include <modules/streamnodes/rendering/renderablelighttravel.h>
#include <modules/streamnodes/rendering/renderabletimevaryingplaneimagelocal.h>
#include <modules/streamnodes/rendering/renderabletimevaryingsphere.h>
#include <openspace/util/factorymanager.h>
#include <ghoul/filesystem/filesystem.h>
#include <ghoul/misc/assert.h>
#include <ghoul/misc/templatefactory.h>
#include <fstream>

namespace {
    constexpr const char* DefaultTransferfunctionSource =
R"(
width 5
lower 0.0
upper 1.0
mappingkey 0.0   0    0    0    255
mappingkey 0.25  255  0    0    255
mappingkey 0.5   255  140  0    255
mappingkey 0.75  255  255  0    255
mappingkey 1.0   255  255  255  255
)";
} // namespace

namespace openspace {

std::string StreamNodesModule::DefaultTransferFunctionFile = "";

StreamNodesModule::StreamNodesModule() : OpenSpaceModule(Name) {
    DefaultTransferFunctionFile = absPath("${TEMPORARY}/default_transfer_function.txt");

    std::ofstream file(DefaultTransferFunctionFile);
    file << DefaultTransferfunctionSource;
}

void StreamNodesModule::internalInitialize(const ghoul::Dictionary&) {
    auto factory = FactoryManager::ref().factory<Renderable>();
    ghoul_assert(factory, "No renderable factory existed");

    factory->registerClass<RenderableStreamNodes>("RenderableStreamNodes");
    factory->registerClass<RenderableLightTravel>("RenderableLightTravel");
    factory->registerClass<RenderableTimeVaryingPlaneImageLocal>("RenderableTimeVaryingPlaneImageLocal");
    factory->registerClass<RenderableTimeVaryingSphere>("RenderableTimeVaryingSphere");
}

} // namespace openspace