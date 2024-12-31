#pragma once

#include "util/define.h"

using namespace godot;

enum CompressionMode
{
    COMPRESSION_LZ4 = 0,
};
VARIANT_ENUM_CAST(CompressionMode);

class MoreCompression : public Object
{
    GDCLASS(MoreCompression, Object);
    DECLARE_SINGLETON(MoreCompression);

  protected:
    static void _bind_methods();

  public:
    static void initialize();
    static void terminate();

    static PackedByteArray compress(const PackedByteArray &bytes, CompressionMode mode);
    static PackedByteArray decompress(const PackedByteArray &bytes, int64_t buffer_size, CompressionMode mode);
    // TODO: add open_compressed

  private:
    static int get_max_compressed_size(int64_t src_size, CompressionMode mode);
};
