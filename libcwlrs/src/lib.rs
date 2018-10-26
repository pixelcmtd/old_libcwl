/*
License note of the libcwl-series of libraries, which provides utilities for
the CWishlist, CWishlistBase, CWishlistUncde and CWishlistDeflate standards.
(c) 2018 by Christian E. "chrissx" Häußler
Licensed to everybody under the terms of the GNU GPLv3, which you should
have obtained this software with.
*/

use std::fs::File;
//use std::io::prelude::*;
use std::path::Path;
use std::vec::Vec;

pub struct item<'a>
{
	name: &'a str,
	url: &'a str
}

pub struct wl<'a>
{
	items: Vec<item<'a>>
}

impl<'a> item<'a>
{
	pub fn hash(&self) -> usize
	{
		let mut ns: usize = 0;
		let mut us: usize = 0;
		for c in self.name.as_bytes()
		{
			ns += *c as usize;
		}
		for c in self.url.as_bytes()
		{
			us += *c as usize;
		}
		self.name.len() * self.url.len() * ns * us
	}

	pub fn str(&self) -> &'a str
	{
		if self.name != ""
		{
			self.name
		}
		else
		{
			"/[unnamed item]\\"
		}
	}
	
	pub fn len(&self) -> usize
	{
		self.name.len() + self.url.len()
	}
	
	pub fn msz(&self) -> usize
	{
		self.len() * 2
	}

	pub fn equals(&self, other: &item<'a>) -> bool
	{
		self.name == other.name && self.url == other.url
	}
}

impl<'a> wl<'a>
{
	pub fn equals(&self, wl: &wl<'a>) -> bool
	{
		if self.items.len() != wl.items.len()
		{
			return false;
		}
		for i in 0..self.items.len()
		{
			if !self.items[i].equals(&wl.items[i])
			{
				return false;
			}
		}
		true
	}
}

pub fn cwld_load<'a>(file: &str) -> wl<'a>
{
	let mut f = match File::open(&Path::new(file))
	{
		Err(_err) => return wl{items: Vec::new()},
		Ok(file) => file
	};
	//deflatedecodestream, read
	wl{items: Vec::new()}
}
