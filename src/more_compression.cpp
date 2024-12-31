#include "more_compression.h"

#include <thirdparty/lz4/lz4.h>

using namespace godot;

DEFINE_SINGLETON(MoreCompression);

void MoreCompression::_bind_methods()
{
    ClassDB::bind_static_method("MoreCompression", D_METHOD("compress", "bytes", "mode"), &MoreCompression::compress);
    ClassDB::bind_static_method("MoreCompression", D_METHOD("decompress", "bytes", "buffer_size", "mode"),
                                &MoreCompression::decompress);
    BIND_ENUM_CONSTANT(COMPRESSION_LZ4);
}

void MoreCompression::initialize()
{
    initialize_singleton();
}

void MoreCompression::terminate()
{
    terminate_singleton();
}

PackedByteArray MoreCompression::compress(const PackedByteArray &bytes, CompressionMode mode)
{
    PackedByteArray compressed;

    ERR_FAIL_COND_V_MSG(bytes.size() <= 0, compressed, "Compressed buffer size must be greater than zero.");

    int max_compressed_size = get_max_compressed_size(bytes.size(), mode);
    compressed.resize(max_compressed_size);

    int compressed_size = 0;
    switch (mode)
    {
    case COMPRESSION_LZ4: {
        compressed_size = LZ4_compress_default(reinterpret_cast<const char *>(bytes.ptr()),
                                               reinterpret_cast<char *>(compressed.ptrw()),
                                               static_cast<int>(bytes.size()), max_compressed_size);
        break;
    }
    }

    compressed.resize(compressed_size >= 0 ? compressed_size : 0);

    return compressed;
}

PackedByteArray MoreCompression::decompress(const PackedByteArray &bytes, int64_t buffer_size, CompressionMode mode)
{
    PackedByteArray decompressed;

    ERR_FAIL_COND_V_MSG(buffer_size <= 0, decompressed, "Decompression buffer size must be greater than zero.");
    ERR_FAIL_COND_V_MSG(bytes.size() == 0, decompressed, "Compressed buffer size must be greater than zero.");

    decompressed.resize(buffer_size);

    int decompressed_size = 0;
    switch (mode)
    {
    case COMPRESSION_LZ4: {
        decompressed_size = LZ4_decompress_safe_partial(reinterpret_cast<const char *>(bytes.ptr()),
                                                        reinterpret_cast<char *>(decompressed.ptrw()), bytes.size(),
                                                        buffer_size, buffer_size);
        break;
    }
    }

    decompressed.resize(decompressed_size >= 0 ? decompressed_size : 0);
    return decompressed;
}

int MoreCompression::get_max_compressed_size(int64_t src_size, CompressionMode mode)
{
    switch (mode)
    {
    case COMPRESSION_LZ4:
        return LZ4_COMPRESSBOUND(src_size);
    default:
        return -1;
    }
}
