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

This piece of software uses the library "Xerces-C++" by Apache.
It is licensed under the Apache License 2.0, which is available at
http://www.apache.org/licenses/LICENSE-2.0.html.
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

//if bool is not supported by your compiler change this to int
typedef bool bool_t;

namespace libcwlcpp
{
	struct item
	{
	public:
		wchar_t *name;
		wchar_t *url;

		item();
		item(wchar_t *name, wchar_t *url);

		wchar_t *to_string();

		bool_t equals(item *itm);
		bool_t equals(void *obj);

		intmax_t hash_code();

		bool_t operator==(item *itm);
		bool_t operator!=(item *itm);
		
		uint64_t length();
		uint64_t memsize();

		uint8_t *to_bytes();
	};

	struct wl
	{
	public:
		//this HAS to be zero-terminated
		item **items;

		wl();
		wl(item **items);

		bool_t operator==(wl *wl);
		bool_t operator!=(wl *wl);
		wl operator&(wl *wl);
	};

	bool_t arrequ(uint8_t *one, uint8_t *two);

	namespace io
	{
		uint8_t cwld_header[8] = { 67, 87, 76, 68, 13, 10, 26, 10 }; //C W L D CR LF EOF LF

		wl load_cwl(char *file);
		wl load_cwlb(char *file);
		wl load_cwlu(char *file);
		wl load_cwld(char *file);
	}
}
