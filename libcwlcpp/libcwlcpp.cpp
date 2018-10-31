/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
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

#include "libcwlcpp.h"

using namespace libcwlcpp;

libcwlcpp::item::item()
{
	name = url = wnull;
}

libcwlcpp::item::item(wstring name, wstring url)
{
	this->name = name;
	this->url = url;
}

const wchar_t *libcwlcpp::item::to_string()
{
	return name != wnull && name.length() ? name.c_str() : unnamed_item;
}

bool libcwlcpp::item::equals(item &itm)
{
	return !name.compare(itm.name) && !url.compare(itm.url);
}

bool libcwlcpp::item::equals(void *obj)
{
	return equals(*(item*)obj);
}

intmax_t libcwlcpp::item::hash_code()
{
	size_t nl = name.length();
	size_t ul = url.length();
	intmax_t ns = 0;
	intmax_t us = 0;
	for (size_t i = 0; i < nl; i++)
		ns += name[i];
	for (size_t i = 0; i < ul; i++)
		us += url[i];
	return nl * ul * ns * us;
}

bool libcwlcpp::item::operator==(item &itm)
{
	return equals(itm);
}

bool libcwlcpp::item::operator!=(item &itm)
{
	return !equals(itm);
}

ulong libcwlcpp::item::length()
{
	return name.length() + url.length();
}

byte* libcwlcpp::item::to_bytes(char *format)
{
	if(!strcmp(format, "D1"))
	{
		wchar_t *s = (wchar_t*)malloc((name.length() + 4 + url.length()) * sizeof(wchar_t));
		wcscpy(s, name.c_str());
		wcscat(s, L"\u0A0D");
		wcscat(s, url.c_str());
		wcscat(s, L"\u0A0D");
		return (uint8_t*)s;
	}
	else if(!strcmp(format, "D2"))
	{
		size_t l = name.length() * sizeof(wchar_t);
		char *s = (char*)malloc(l + (3 + url.length()) * sizeof(wchar_t));
		wcscpy((wchar_t*)s, name.c_str());
		s[l] = 11;
		if(!wcsncmp(url.c_str(), tinyurl, 19))
		{
			s[l + 1] = 1;
			strcat(s, 0/*url.substr(19) to string c_str*/);
			s[l + 10] = 11;
		}
		else
		{
			s[l + 1] = 0;
			wcscat((wchar_t*)s, url.c_str());
			s[l + 1 + url.length() * sizeof(wchar_t)] = 11;
		}
		l = sizeof(s);
		char *t = (char*)malloc(l);
		memcpy(t, s, l);
		return (byte*)t;
	}
	else if (!strcmp(format, "L1"))
	{
		UErrorCode err = U_ZERO_ERROR;
		UConverter *conv = ucnv_open("utf-8", &err);
		if (!U_SUCCESS(err))
		{
			last_exception = err | unicode_error;
			return 0;
		}
		_____PLZ_COMPLETE_THIS_IN_THE_FUTURE_____
		//encode utf8 for name to bfr;
		//if (!wcsncmp(url.c_str(), tinyurl, 19))
		//{
		//	write 11 to bfr;
		//	write b64 decode url.substr(19) to bfr;
		//}
		//else
		//{
		//	write 8 to bfr;
		//	write utf8 of url to bfr;
		//	write 11 to bfr;
		//}
		ucnv_close(conv);
	}
	return 0;
}

libcwlcpp::wl::wl()
{
	items = 0;
}

libcwlcpp::wl::wl(item **items)
{
	this->items = items;
}

bool libcwlcpp::wl::operator==(wl *wl)
{
	return arrequ((uint8_t*)&items[0], (uint8_t*)&(wl->items[0]));
}

bool libcwlcpp::wl::operator!=(wl *wl)
{
	return !arrequ((byte*)&items[0], (byte*)&(wl->items[0]));
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

ulong libcwlcpp::wl::length()
{
	//we can do this because while items have variable
	//size ptrs are 8 bytes on AMD64/x86_64 and 4 on x86
	return sizeof(items) / sizeof(item*) - 1;
}

ulong libcwlcpp::wl::hlen()
{
	ulong i = length() * sizeof(item);
	for (ulong j = 0; j < length(); j++)
	{
		item *k = items[j];
		i += (k->name.length() + k->url.length()) * wclen + 2;
	}
	i += sizeof(items);
	return i;
}

bool libcwlcpp::arrequ(byte *arr1, byte *arr2)
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

wl *libcwlcpp::io::load_cwld(char *file)
{
	FILE *f = fopen(file, "r");
	long b = ftell(f);
	fseek(f, 0, SEEK_END);
	long e = ftell(f);
	fseek(f, 0, SEEK_SET);
	long l = e - b - 10;
	uint8_t h[8];
	fread(h, 1, 8, f);
	uint8_t v[2];
	fread(v, 1, 2, f);
	uint8_t major = v[0];
	uint8_t minor = v[1];
	uint8_t *c = (uint8_t*)malloc(l);
	fread(c, 1, l, f);
	libdeflate_decompressor *d = libdeflate_alloc_decompressor();
	size_t ul = 0;
	size_t ubfrlen = l * 10;
	uint8_t *ubfr = (uint8_t*)malloc(ubfrlen);
	libdeflate_result res = libdeflate_deflate_decompress(d, c, l, ubfr, ubfrlen, &ul);
	libdeflate_free_decompressor(d);
	free(c);
	if (res)
	{
		free(ubfr);
		last_exception = deflate_error | res;
		return 0;
	}
	uint8_t *u = (uint8_t*)malloc(ul);
	memcpy(u, ubfr, ul);
	free(ubfr);
	fclose(f);
	if (major != 4)
	{
		last_exception = 0x20 | 1;
		return 0;
	}
	else if (minor > 2)
	{
		last_exception = 0x20 | 2;
		return 0;
	}
	else if (minor == 1)
	{
		vector<item*> items;
		wchar_t *s = (wchar_t*)malloc(ul);
		uint8_t tmp1;
		uint8_t tmp2;
		wchar_t *n;
		size_t i;
		size_t j;
		while (i < ul)
		{
			if ((tmp1 = u[i++]) == 10 && (tmp2 = u[i++]) == 13)
			{
				if (n)
				{
					wchar_t *url = (wchar_t*)malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(url, s);
					memset(s, 0, ul);
					j = 0;
					items.push_back(new item(n, url));
					n = 0;
				}
				else
				{
					n = (wchar_t*)malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(n, s);
					memset(s, 0, ul);
					j = 0;
				}
			}
			else
			{
				uint8_t *mb = (uint8_t*)malloc(2);
				mb[0] = tmp1;
				mb[1] = tmp2;
				wchar_t *wc = (wchar_t*)malloc(sizeof(wchar_t));
				mbtowc(wc, (const char*)mb, 2);
				s[j++] = *wc;
				free(mb);
				free(wc);
			}
		}
		free(s);
		free(u);
		size_t il = items.size() * sizeof(items[0]);
		item **itms = (item**)malloc(il);
		memcpy(itms, items[0], il);
		if (n) //this btw means a broken cwld but lets be safe
		{
			free(n);
		}
		return new wl(itms);
	}
	else
	{
		vector<item*> items;
		wchar_t *s = (wchar_t*)malloc(ul);
		wchar_t *n;
		uint8_t i;
		size_t ui;
		size_t si;
		while (ui < ul)
		{
			if ((i = u[ui++]) == 11)
			{
				if (n)
				{
					wchar_t *url = (wchar_t*)malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(url, s);
					memset(s, 0, ul);
					si = 0;
					items.push_back(new item(n, url));
					n = 0;
				}
				else
				{
					n = (wchar_t*)malloc(wcslen(s) * sizeof(wchar_t));
					wcscpy(n, s);
					memset(s, 0, ul);
					if (u[ui++])
					{
						wcscpy(s, L"http://tinyurl.com/");
						si = 19;
					}
					else
					{
						si = 0;
					}
				}
			}
			else
			{
				uint8_t *mb = (uint8_t*)malloc(2);
				mb[0] = i;
				mb[1] = u[ui++];
				wchar_t *wc = (wchar_t*)malloc(sizeof(wchar_t));
				mbtowc(wc, (const char*)mb, 2);
				s[si++] = *wc;
				free(mb);
				free(wc);
			}
		}
		free(s);
		free(u);
		size_t il = items.size() * sizeof(items[0]); //the elements are pointers so all elements have the same size
		item **itms = (item**)malloc(il);
		memcpy(itms, items[0], il);
		if (n) //this btw means a broken cwld but lets be safe
		{
			free(n);
		}
		return new wl(itms);
	}
}

wl *libcwlcpp::io::load_cwll(char *file) {}
wl *libcwlcpp::io::load_cwlu(char *file) {}
