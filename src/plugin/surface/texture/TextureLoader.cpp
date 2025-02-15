/*
** EPITECH PROJECT, 2024
** TextureLoader
** File description:
** file for TextureLoader functions
*/

#include "plugin/surface/texture/TextureLoader.hpp"

#include <fstream>
#include <png.h>
#include <format>

namespace RayTracer
{
    std::shared_ptr<Texture> TextureLoader::loadTexture()
    {
        std::ifstream stream = std::ifstream(_path);
        if (!stream.is_open())
            throw std::runtime_error("Could not open file: " + _path);

        ::uint8_t pngSig[8];
        stream.read(reinterpret_cast<char *>(pngSig), sizeof(pngSig) / sizeof(*pngSig));
        if (::png_sig_cmp(pngSig, 0, sizeof(pngSig) / sizeof(*pngSig)) != 0)
            throw std::runtime_error("Invalid PNG stream signature");

        ::png_structp pngPtr = ::png_create_read_struct(
                PNG_LIBPNG_VER_STRING, nullptr,
                [](::png_structp, ::png_const_charp msg) {
                    throw std::runtime_error(std::format("Bad PNG stream: {}", msg));
                },
                nullptr
        );
        if (!pngPtr)
            throw std::runtime_error("Failed to initiate PNG stream read structure");

        ::png_infop pngInfoPtr = ::png_create_info_struct(pngPtr);
        ::png_infop pngEndInfoPtr = ::png_create_info_struct(pngPtr);
        if (!pngInfoPtr || !pngEndInfoPtr) {
            ::png_destroy_read_struct(&pngPtr, &pngInfoPtr, &pngEndInfoPtr);
            throw std::runtime_error("Failed to initiate PNG stream info structures");
        }

        ::png_set_read_fn(pngPtr, &stream,
            [](::png_structp pngPtr, ::png_bytep rawData, ::png_size_t readLength) {
              std::istream *stream = static_cast<std::istream *>(::png_get_io_ptr(pngPtr));
              stream->read(reinterpret_cast<char *>(rawData), readLength);
            }
        );

        ::png_set_sig_bytes(pngPtr, sizeof(pngSig) / sizeof(*pngSig));

        ::png_read_info(pngPtr, pngInfoPtr);

        ::uint32_t pngWidth, pngHeight;
        int pngColorDepth, pngColorType;
        ::png_get_IHDR(pngPtr, pngInfoPtr, &pngWidth, &pngHeight, &pngColorDepth, &pngColorType, nullptr, nullptr, nullptr);

        ::png_set_add_alpha(pngPtr, 0xff, PNG_FILLER_AFTER);
        if (pngColorType == PNG_COLOR_TYPE_PALETTE)
            ::png_set_palette_to_rgb(pngPtr);
        if (pngColorType == PNG_COLOR_TYPE_GRAY && pngColorDepth < 8)
            ::png_set_expand_gray_1_2_4_to_8(pngPtr);
        if (png_get_valid(pngPtr, pngInfoPtr, PNG_INFO_tRNS))
            ::png_set_tRNS_to_alpha(pngPtr);

        std::shared_ptr<Texture> pngTexture = std::make_shared<Texture>(pngWidth, pngHeight);
        ::png_bytep pngRowPointers[pngHeight];
        pngTexture->access([&pngRowPointers, &pngWidth, &pngHeight](uint32_t *contents) {
            for (::size_t y = 0; y < pngHeight; y++)
                pngRowPointers[y] = reinterpret_cast<::png_bytep>(&contents[y * pngWidth]);
        });

        ::png_read_image(pngPtr, pngRowPointers);
        ::png_read_end(pngPtr, pngEndInfoPtr);

        ::png_destroy_read_struct(&pngPtr, &pngInfoPtr, &pngEndInfoPtr);

        return pngTexture;
    }
} // RayTracer
