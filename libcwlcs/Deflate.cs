/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.
*/

using System.IO;
using System.IO.Compression;

namespace libcwlcs
{
    public static class Deflate
    {
        public static byte[] compress(byte[] b)
        {
            MemoryStream s = new MemoryStream(b, false);
            MemoryStream d = new MemoryStream();
            DeflateStream ds = new DeflateStream(d, CompressionMode.Compress);
            s.CopyTo(ds, 32767); //short.MaxValue / 32KiB
            ds.Close();
            s.Close();
            d.Close();
            return d.ToArray();
        }

        public static byte[] decompress(byte[] b)
        {
            MemoryStream s = new MemoryStream(b, false);
            MemoryStream d = new MemoryStream();
            DeflateStream ds = new DeflateStream(s, CompressionMode.Decompress);
            ds.CopyTo(d, 32767); //short.MaxValue
            ds.Close();
            s.Close();
            d.Close();
            return d.ToArray();
        }
    }
}
