/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2016                                                               *
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

#ifndef __TILE_DATASET_H__
#define __TILE_DATASET_H__

//#include <modules/globebrowsing/other/tileprovider.h>

#include <ghoul/opengl/texture.h>

#include <modules/globebrowsing/geodetics/geodetic2.h>
#include <modules/globebrowsing/other/threadpool.h>

#include "gdal_priv.h"

#include <memory>
#include <set>
#include <queue>



namespace openspace {
    using namespace ghoul::opengl;


    struct RawTileData {

        struct TextureFormat {
            Texture::Format ghoulFormat;
            GLuint glFormat;
        };


        RawTileData(void* data, glm::uvec3 dims, TextureFormat format,
            GLuint glType, const ChunkIndex& chunkIndex)
            : imageData(data)
            , dimensions(dims)
            , texFormat(format)
            , glType(glType)
            , chunkIndex(chunkIndex)
        {

        }

        void* imageData;
        glm::uvec3 dimensions;
        TextureFormat texFormat;
        GLuint glType;
        ChunkIndex chunkIndex;
    };



    struct TileIOResult {
        CPLErr error;
        std::shared_ptr<RawTileData> rawTileData;
    };



    struct TileDepthTransform {
        float depthScale;
        float depthOffset;
    };



    class TileDataset {
    public:
    
        // Default dataType = 0 means GDAL will use the same data type as the data
        // is originally in
        TileDataset(const std::string& fileName, int minimumPixelSize, GLuint dataType = 0);
        ~TileDataset();


        std::shared_ptr<TileIOResult> readTileData(ChunkIndex chunkIndex);

        int getMaximumLevel() const;

        TileDepthTransform getDepthTransform() const;


    private:


        //////////////////////////////////////////////////////////////////////////////////
        //                          HELPER STRUCTS                                      //
        //////////////////////////////////////////////////////////////////////////////////


        struct GdalDataRegion {

            GdalDataRegion(GDALDataset* dataSet, const ChunkIndex& chunkIndex,
                int tileLevelDifference);

            const ChunkIndex chunkIndex;

            glm::uvec2 pixelStart;
            glm::uvec2 pixelEnd;
            glm::uvec2 numPixels;

            size_t numRasters;

            int overview;

        };

        struct DataLayout {
            DataLayout();
            DataLayout(GDALDataset* dataSet, GLuint glType);

            GDALDataType gdalType;
            size_t bytesPerDatum;
            size_t bytesPerPixel;
        };






        //////////////////////////////////////////////////////////////////////////////////
        //                             HELPER FUNCTIONS                                 //
        //////////////////////////////////////////////////////////////////////////////////

        TileDepthTransform calculateTileDepthTransform();


        static int calculateTileLevelDifference(GDALDataset* dataset, int minimumPixelSize);

        static glm::uvec2 geodeticToPixel(GDALDataset* dataSet, const Geodetic2& geo);

        static GLuint getOpenGLDataType(GDALDataType gdalType);

        static GDALDataType getGdalDataType(GLuint glType);

        static RawTileData::TextureFormat getTextureFormat(int rasterCount, GDALDataType gdalType);

        static size_t numberOfBytes(GDALDataType gdalType);

        static size_t getMaximumValue(GDALDataType gdalType);

        static std::shared_ptr<RawTileData> createRawTileData(const GdalDataRegion& region,
            const DataLayout& dataLayout, const char* imageData);


        //////////////////////////////////////////////////////////////////////////////////
        //                              MEMBER VARIABLES                                //
        //////////////////////////////////////////////////////////////////////////////////

        static bool GdalHasBeenInitialized;

        int _minimumPixelSize;
        double _tileLevelDifference;

        TileDepthTransform _depthTransform;

        GDALDataset* _dataset;
        DataLayout _dataLayout;

    };



} // namespace openspace





#endif  // __TILE_DATASET_H__