package de.chrissx.libcwl.java;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.CharacterCodingException;

public class Item {

	public String name, url;

	public Item()
	{
		name = url = "";
	}

	public Item(String name, String url)
	{
		this.name = name;
		this.url = url;
	}

	@Override
	public String toString()
	{
		return name != "" ? name : "[/unnamed item\\]";
	}

	@Override
	public boolean equals(Object o)
	{
		return o instanceof Item ? equals((Item)o) : false;
	}

	public boolean equals(Item i)
	{
		return name == i.name && url == i.url;
	}

	@Override
	public int hashCode()
	{
		return name.hashCode() * url.hashCode();
	}

	/**
	 * adds name.length to url.length and returns it as the full length of this item
	 * @return the length of name plus the length of url
	 * @deprecated name.length() can be up to int.max and url.length() can also be up to int.max, so this can produce an overflow
	 */
	@Deprecated
	public int length()
	{
		return name.length() + url.length();
	}

	public long longLength()
	{
		return (long)name.length() + (long)url.length();
	}

	/**
	 * Calculates the estimated size of this Item instance.
	 * @return The number of memory bytes used by this Item.
	 */
	public long memoryLength()
	{
		return longLength() * 2;
	}

	public void writeBytes(OutputStream s, String format) throws CharacterCodingException, IOException
	{
		if(format == "D1")
		{
			s.write(InternalConstsNUtils.leunicode(name));
			s.write(InternalConstsNUtils.d1_separator);
			s.write(InternalConstsNUtils.leunicode(url));
			s.write(InternalConstsNUtils.d1_separator);
		}
		else if(format == "D2")
		{
			s.write(InternalConstsNUtils.leunicode(name));
			s.write(InternalConstsNUtils.d2_separator);
			if(url.startsWith("http://tinyurl.com/"))
			{
				s.write(InternalConstsNUtils.d2_is_tu);
				s.write(InternalConstsNUtils.ascii(url.substring(19)));
			}
			else
			{
				s.write(InternalConstsNUtils.d2_is_no_tu);
				s.write(InternalConstsNUtils.leunicode(url));
			}
			s.write(InternalConstsNUtils.d2_separator);
		}
		else if(format == "L1")
		{
			
		}
	}
}
