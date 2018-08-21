/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.
*/

using System;
using System.Collections;
using System.Collections.Generic;

namespace libcwlcs
{
    public struct WL : IEnumerable
    {
        public WL(params Item[] items)
        {
            this.items = items;
        }

        public WL(List<Item> items)
        {
            this.items = items.ToArray();
        }

        public Item[] items;

        public static WL NEW { get; } = new WL(new Item[0]);

        public static bool operator ==(WL first, WL second)
        {
            if (first.Length != second.Length)
                return false;
            for (int i = 0; i < first.Length; i++)
                if (first[i] != second[i])
                    return false;
            return true;
        }

        public static bool operator !=(WL first, WL second) => !(first == second);

        public Item this[ulong index] => items[index];
        public Item this[long index] => items[index];

        public static WL operator &(WL first, WL second)
        {
            Item[] items = new Item[first.Length + second.Length];
            for (int i = 0; i < first.Length; i++)
                items[i] = first[i];
            for (int i = first; i < first + second; i++)
                items[i] = second[i - first];
            return new WL(items);
        }

        public static implicit operator int(WL wl) => wl.Length;

        public static implicit operator long(WL wl) => wl.items.LongLength;

        public override bool Equals(object obj) => (obj is WL) ? ((WL)obj) == this : false;

        public bool Equals(WL wl) => wl == this;

        public override int GetHashCode()
        {
            unchecked
            {
                if(items.LongLength == 0)
                    return 0;
                int hc = items[0].GetHashCode();
                for(long i = 1; i < items.LongLength; i++)
                    hc *= items[i].GetHashCode();
                return hc;
            }
        }

        public override string ToString() => items.ToString();

        public IEnumerator GetEnumerator() => items.GetEnumerator();

        public int Length
        {
            get => items.Length;
        }

        public long LongLength
        {
            get => items.LongLength;
        }

        public Item[] SearchItems(Predicate<Item> predicate) => Array.FindAll(items, predicate);

        public int GetFirstIndex(Predicate<Item> predicate) => Array.FindIndex(items, predicate);
    }
}
