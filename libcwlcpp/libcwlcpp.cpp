/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
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

#include "libcwlcpp.h"

libcwlcpp::item::item()
{
	name = url = 0;
}

libcwlcpp::item::item(wchar_t *name, wchar_t *url)
{
	this->name = name;
	this->url = url;
}

wchar_t *libcwlcpp::item::to_string()
{
	return name && wcslen(name) ? name : const_cast<wchar_t*>(L"/[unnamed item]\\");
}

bool_t libcwlcpp::item::equals(item *itm)
{
	return wcscmp(name, itm->name) && wcscmp(url, itm->url);
}

bool_t libcwlcpp::item::equals(void *obj)
{
	item *i = (item*)obj;
	return wcscmp(name, i->name) && wcscmp(url, i->url);
}

intmax_t libcwlcpp::item::hash_code()
{
	size_t nl = wcslen(name);
	size_t ul = wcslen(url);
	intmax_t ns = 0;
	intmax_t us = 0;
	for (size_t i = 0; i < nl; i++)
		ns += name[i];
	for (size_t i = 0; i < ul; i++)
		us += url[i];
	return nl * ul * ns * us;
}

bool_t libcwlcpp::item::operator==(item *itm)
{
	return equals(itm);
}

bool_t libcwlcpp::item::operator!=(item *itm)
{
	return !equals(itm);
}

uint64_t libcwlcpp::item::length()
{
	return sizeof(name) + sizeof(url);
}

uint64_t libcwlcpp::item::memsize()
{
	return length() * sizeof(wchar_t);
}

uint8_t* libcwlcpp::item::to_bytes()
{
	wchar_t *s = (wchar_t*)malloc((wcslen(name) + 1) * sizeof(wchar_t));
	wcscpy(s, name);
	wcscat(s, L"\u0A0D");
	wcscat(s, url);
	wcscat(s, L"\u0A0D\u0000");
	return reinterpret_cast<uint8_t*>(&s[0]);
}

libcwlcpp::wl::wl()
{
	items = 0;
}

libcwlcpp::wl::wl(item **items)
{
	this->items = items;
}

bool_t libcwlcpp::wl::operator==(wl *wl)
{
	return arrequ((uint8_t*)&items[0], (uint8_t*)&(wl->items[0]));
}

bool_t libcwlcpp::wl::operator!=(wl *wl)
{
	return !(this == wl);
}

libcwlcpp::wl libcwlcpp::wl::operator&(wl *wl)
{
	vector<item*> *i = new vector<item*>();
	for (item **p = items; *p; ++p)
	{
		i->push_back(*p);
	}
	i->push_back(0);
	return &(*i)[0];
}

bool_t libcwlcpp::arrequ(uint8_t *one, uint8_t *two)
{
	size_t so = sizeof(one);
	size_t st = sizeof(two);
	if (so != st)
	{
		return 0;
	}
	for (size_t i = 0; i < so; i++)
	{
		if (one[i] != two[i])
		{
			return 0;
		}
	}
	return 1;
}
