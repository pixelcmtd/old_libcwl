/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
Licensed to everybody under the terms of the GNU GPL v3, which you should
have obtained this software with.
*/

use std::error:Error;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::vec::Vec;

pub struct item
{
	name: str,
	url: str
}

pub struct wl
{
	Vec<item> items
}

impl item
{
	pub fn new(str name, str url) -> Self
	{
		item
		{
			name: name,
			url: url
		}
	}

	pub fn new() -> Self
	{
		item
		{
			name: "",
			url: ""
		}
	}

	pub fn equals(&self, i: &item) -> bool
	{
		self.name == i.name && self.url == i.url;
	}

	pub fn hash(&self) -> i128
	{
		let nl: i128 = self.name.len();
		let ul: i128 = self.url.len();
		let mut ns: i128 = 0;
		let mut us: i128 = 0;
		for i in 0..nl
		{
			ns += self.name[i];
		}
		for i in 0..ul
		{
			us += self.url[i];
		}
		nl * ul * ns * us;
	}

	pub fn str(&self) -> str
	{
		self.name != "" ? self.name : "/[unnamed item]\\";
	}
	
	pub fn len(&self) -> u64
	{
		self.name.len() + self.url.len();
	}
	
	pub fn msz(&self) -> u64
	{
		len(i) * 2;
	}
}

impl wl
{
	pub fn new(Vec<item> items) -> Self
	{
		wl
		{
			items: items
		}
	}

	pub fn new() -> Self
	{
		wl
		{
			items: Vec<item>::new()
		}
	}

	pub fn equals(&self, wl: &wl) -> bool
	{
		if self.items.len() != wl.items.len()
		{
			false;
		}
		else
		{
			for i in 0..self.items.len()
			{
				if self.items[i] != wl.items[i]
				{
					false;
				}
			}
			true;
		}
	}
}

pub fn cwld_load(file: str) -> (wl, Error)
{
	let mut f = match File::open(&Path::new(file))
	{
		Err(err) => return err,
		Ok(file) => file
	}
	//deflatedecodestream, read
}
