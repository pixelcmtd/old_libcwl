/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" H�u�ler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.

This piece of software uses the library "libdeflate" by Eric Biggers.
Here you can see a section from its license agreement:

***QUOTE***
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
***QUOTE END***
*/

#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define LIBDEFLATE_DLL
#endif
#include <string>
#include <wchar.h>
#include <vector>
#include "libdeflate.h"
#include "unicode/ucnv.h"

using namespace std;

typedef long error;
typedef unsigned char byte;
typedef unsigned long ulong;

namespace libcwlcpp
{
	//the last exception thrown by libcwl
	error last_exception = 0;

	#define deflate_error 0x1000000000000000 //error in libdeflate
	#define unicode_error 0x2000000000000000 //error in unicode library
	#define lzma_7z_error 0x3000000000000000 //error in lzma sdk
	#define badhead_error 0x4000000000000000 //header not valid
	#define badvern_error 0x5000000000000000 //version too new (or old)
	#define iposibl_error 0x6000000000000000 //theoretical possibility
											 //that's not possible w/o
											 //memory corruption

	//#define mem_mod_ipos 1

	static inline bool is_error(error val, error err)
	{
		return val & err == err;
	}

	//the unnamed constant
	const wchar_t *unnamed_item = L"/[unnamed item]\\";
	//the tinyurl constant
	const wchar_t *tinyurl = L"http://tinyurl.com/";
	const std::wstring wnull = std::wstring(L"");
	const size_t wclen = sizeof(wchar_t);

	//one item in a cwl
	struct item
	{
	public:
		//the name of the item (HAS to be zero-terminated)
		std::wstring name;
		//the url of the item, usually a tinyurl (HAS to be zero-terminated)
		std::wstring url;

		//constructs a new item with null name and url
		item();
		//constructs a new item with the given name and url
		item(std::wstring name, std::wstring url);

		//returns the name if it is set, else unnamed_item
		const wchar_t *to_string() const noexcept;

		//returns true if name and url are wcscmp equal, else false
		bool equals(item &itm) const noexcept;
		//casts obj to an item ptr and compares with it, can lead to
		//segmentation faults and other errors if obj is no item
		bool equals(void *obj) const noexcept;

		//compares the items, returns 1 if they are equal, 0 if not
		bool operator==(item &itm) const noexcept;
		//compares the items, returns 0 if they are equal, 1 if not
		bool operator!=(item &itm) const noexcept;
		
		//returns the added len of the name and url
		ulong length() const noexcept;

		//returns bytes of this item encoded in the given format
		//formats: D1, D2; soon: L1
		byte *to_bytes(char *format);
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
		bool operator==(wl *wl) const noexcept;
		//compares the wls and returns 0 if they are and 1 if not
		bool operator!=(wl *wl) const noexcept;
		//appends the wls and returns the new one
		wl operator&(wl *wl) const noexcept;

		//returns the number of elements in this wl
		//(without the null at the end of items)
		ulong length() const noexcept;
		ulong hlen() const noexcept;
	};

	//Compares the two given byte arrays and returns 1 if they
	//are equal and 0 if not
	bool arrequ(byte *arr1, byte *arr2);

	namespace io
	{
		//the header of cwld files
		byte cwld_header[8] = {'C','W','L','D','\r','\n','\x1a','\n'};
		byte cwll_header[4] = {'C','W','L','L'};

		//tries to load the cwll from the file
		//(returns 0 and saves the excpetion
		//into last_exception if one occurs)
		wl *load_cwll(char *file);

		//tries to load the cwld from the file
		//(returns 0 and saves the exception
		//into last_exception if one occurs)
		wl *load_cwld(char *file);
	}
}
