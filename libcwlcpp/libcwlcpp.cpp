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
	return name && wcslen(name) ? name : unnamed_item;
}

bool_t libcwlcpp::item::equals(item *itm)
{
	return !wcscmp(name, itm->name) && !wcscmp(url, itm->url);
}

bool_t libcwlcpp::item::equals(void *obj)
{
	item *i = (item*)obj;
	return !wcscmp(name, i->name) && !wcscmp(url, i->url);
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

uint64_t libcwlcpp::item::memlen()
{
	return length() * sizeof(wchar_t);
}

uint8_t* libcwlcpp::item::to_bytes(char *format)
{
	if(!strcmp(format, "D1"))
	{
		wchar_t *s = malloc((wcslen(name) + 3 + wcslen(url)) * sizeof(wchar_t));
		wcscpy(s, name);
		wcscat(s, L"\u0A0D");
		wcscat(s, url);
		wcscat(s, L"\u0A0D\u0000");
		return reinterpret_cast<uint8_t*>(&s[0]);
	}
	else if(!strcmp(format, "D2"))
	{
		size_t l = wcslen(name) * sizeof(wchar_t);
		void *s = malloc((l + 3 + wcslen(url)) * sizeof(wchar_t));
		wcscpy(s, name);
		s[l] = 11;
		if(!strncmp(url, "http://tinyurl.com/", 19))
		{
			s[l + 1] = 1;
			//copy tinyurl id as str
			s[l + 10] = 11;
		}
		else
		{
			s[l + 1] = 0;
			wcscat(s, url);
			s[l + 1 + wcslen(url) * sizeof(wchar_t)] = 11;
		}
		l = wcslen(s) + 1;
		wchar_t *t = malloc(l);
		memcpy(t, s, l);
	}
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

uint64_t libcwlcpp::wl::length()
{
	//we can do this because while items have variable
	//size ptrs are 8 bytes on AMD64/x86_64 and 4 on x86
	return sizeof(items) / sizeof(items[0]) - 1;
}

uint64_t libcwlcpp::wl::memlen()
{
	uint64_t i = sizeof(items);
	for(item **p; *p; ++p)
	{
		i += (*p)->memlen();
	}
	return i;
}

bool_t libcwlcpp::arrequ(uint8_t *arr1, uint8_t *arr2)
{
	size_t so = sizeof(arr1);
	size_t st = sizeof(arr2);
	if (so != st)
	{
		return 0;
	}
	for (size_t i = 0; i < so; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

wl *load_cwld(char *file);
{
	FILE *f = fopen(file, "r");
	long int b = ftell(f);
	fseek(f, SEEK_END);
	long int e = ftell(f);
	fseek(f, SEEK_SET);
	long int l = e - b - 10;
	uint8_t *h = malloc(8);
	fread(h, 1, 8, f);
	free(h);
	uint8_t *v = malloc(2);
	fread(v, 1, 2, f);
	uint8_t major = v[0];
	uint8_t minor = v[1];
	free(v);
	uint8_t *c = malloc(l);
	fread(c, 1, l, f);
	libdeflate_decompressor *d = libdeflate_alloc_decompressor();
	size_t *ub = malloc(sizeof(size_t));
	size_t ubfrlen = l * 10;
	uint8_t *ubfr = malloc(ubfrlen);
	libdeflate_deflate_decompress(d, c, l, ubfr, ubfrlen, ub);
	libdeflate_free_decompressor(d);
	free(c);
	size_t ul = *ub;
	uint8_t *u = malloc(ul);
	memcpy(u, ubfr, ul);
	free(ubfr);
	free(ub);
	fclose(f);
	if(major != 4)
	{
		last_exception = 1;
		return 0;
	}
	else if(minor > 2)
	{
		last_exception = 2;
		return 0;
	}
	//TODO: DECODE
	else if(minor == 1)
	{
		vector<item*> items;
		wchar_t *s = malloc(ul);
		uint8_t tmp1;
		uint8_t tmp2;
		wchar_t *n = 0;
		size_t i = 0;
		size_t j = 0;
		while(i < ul)
		{
			if ((tmp1 = u[i++]) == 10 && (tmp2 = u[i++]) == 13)
			{
				if (n != 0)
				{
					wchar_t *url = malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(url, s);
					memset(s, 0, ul);
					j = 0;
					items.push_back(new item(n, url));
					n = 0;
				}
				else
				{
					n = malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(n, s);
					memset(s, 0, ul);
					j = 0;
				}
			}
			else
			{
				uint8_t *mb = malloc(2);
				mb[0] = tmp1;
				mb[1] = tmp2;
				wchar_t *wc = malloc(sizeof(wchar_t));
				mbtowc(wc, mb, 2);
				s[j++] = *wc;
				free(mb);
				free(wc);
			}
		}
		free(s);
		free(u);
		size_t il = items.size() * sizeof(items[0]);
		item **itms = malloc(il);
		memcpy(itms, items[0], il);
		free(items);
		if (n != 0)
		{
			free(n);
		}
		return new wl(itms);
	}
	else
	{

	}
}
