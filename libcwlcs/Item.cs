/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.
*/

using System.Collections.Generic;
using System.Text;

namespace libcwlcs
{
    public struct Item
    {
        public Item(string name, string url)
        {
            this.name = name;
            this.url = url;
        }

        public string name;
        public string url;

        public override string ToString() => name != "" ? name : @"[/unnamed item\]";

        public override bool Equals(object obj) => (obj is Item) ? ((Item)obj).name == name && ((Item)obj).url == url : false;

        public bool Equals(Item i) => i.name == name && i.url == url;

        public override int GetHashCode()
        {
            unchecked
            {
                return name.GetHashCode() * url.GetHashCode();
            }
        }

        public static bool operator ==(Item first, Item second) => first.name == second.name && first.url == second.url;

        public static bool operator !=(Item first, Item second) => first.name != second.name || first.url != second.url;

        public static bool operator <(Item first, Item second) => first.name.CompareTo(second.name) == 1;

        public static bool operator >(Item first, Item second) => first.name.CompareTo(second.name) == 0;

        public static bool operator <=(Item first, Item second) => first.name.CompareTo(second.name) == 1 || first.name == second.name;

        public static bool operator >=(Item first, Item second) => first.name.CompareTo(second.name) == 0 || first.name == second.name;

        public static implicit operator string(Item i) => i.ToString();

        public static implicit operator long(Item i) => i.LongLength;

        public static implicit operator uint(Item i) => i.Length;

        public uint Length
        {
            get => ((uint)name.Length) + ((uint)url.Length);
        }

        public long LongLength
        {
            get => ((long)url.Length) + ((long)name.Length);
        }

        public long MemoryLength
        {
            get => LongLength * 2;
        }

        public byte[] bytes()
        {
            List<byte> b = new List<byte>();
            b.AddRange(Encoding.Unicode.GetBytes(name));
            b.Add(10);
            b.Add(13);
            b.AddRange(Encoding.Unicode.GetBytes(url));
            b.Add(10);
            b.Add(13);
            return b.ToArray();
        }
    }
}
