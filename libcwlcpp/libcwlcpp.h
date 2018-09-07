/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" H‰uﬂler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.

This piece of software uses the library "libdeflate" by Eric Biggers.
Here you can see a section from its "COPYING"/license agreement:

***BEGIN OF COPYING***
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
***END OF COPYING***
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#if defined(WIN32) && 1 //change to 0 if you want to use the static lib
#define LIBDEFLATE_DLL
#endif
#include <string>
#include <stdint.h>
#include <wchar.h>
#include <vector>
#include "libdeflate.h"

using namespace std;

//bool is ansi c++, but if you are using internet explorer to compile you
//might want to change this
typedef bool bool_t;

namespace libcwlcpp
{
	//the string constant L"/[unnamed item]\\"
	wchar_t *unnamed_item = L"/[unnamed item]\\";

	//one item in a cwl
	struct item
	{
	public:
		//the name of the item (HAS to be zero-terminated)
		wchar_t *name;
		//the url of the item, usually a tinyurl (HAS to be zero-terminated)
		wchar_t *url;

		//constructs a new item with null name and url
		item();
		//constructs a new item with the given name and url
		item(wchar_t *name, wchar_t *url);

		//returns the name if name && wcslen(name), else unnamed_item
		wchar_t *to_string();

		//returns 1 if name and url are wcscmp equal, else 0
		bool_t equals(item *itm);
		//casts obj to an item ptr and compares with it, can lead to
		//segmentation faults and other errors if obj is no item
		bool_t equals(void *obj);

		//returns a pretty unique checksum/hash, can be used for
		//maps or smth like that
		intmax_t hash_code();

		//compares the items, returns 1 if they are equal, 0 if not
		bool_t operator==(item *itm);
		//compares the items, returns 0 if they are equal, 1 if not
		bool_t operator!=(item *itm);
		
		//returns the added wcslen of the name and url
		uint64_t length();
		//returns length() * sizeof(wchar_t), which is a rough
		//estimate of the size this uses in memory
		uint64_t memlen();

		//returns bytes of this item encoded in the given format
		//formats: D1, D2; soon: L1
		uint8_t *to_bytes(char *format);
	};

	//a cwl
	struct wl
	{
	public:
		//the actual array of items (HAS to be zero-terminated)
		item **items;

		//constructs a new wl with items = null
		wl();
		//constructs a new wl with the given items
		wl(item **items);

		//compares the wls and returns 1 if they are and 0 if not
		bool_t operator==(wl *wl);
		//compares the wls and returns 0 if they are and 1 if not
		bool_t operator!=(wl *wl);
		//appends the wls and returns the new one
		wl operator&(wl *wl);

		//returns the number of elements in this wl
		//(without the null at the end of items)
		uint64_t length();
		//sums up the byte size of the pointer array
		//and the memlen() of the individual items
		uint64_t memlen();
	};

	//Compares the two given byte arrays and returns 1 if they
	//are equal and 0 if not
	bool_t arrequ(uint8_t *arr1, uint8_t *arr2);

	namespace io
	{
		//the last exception thrown by cwl io
		uint8_t last_exception = 0;

		//the header of cwld files
		//(C W L D CR LF EOF LF)
		uint8_t cwld_header[8] = { 67, 87, 76, 68, 13, 10, 26, 10 };

		//tries to load the cwld from the file
		//(returns 0 and saves the exception
		//into last_exception if one occures)
		wl *load_cwld(char *file);
	}
}
