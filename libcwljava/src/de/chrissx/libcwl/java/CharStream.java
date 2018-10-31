package de.chrissx.libcwl.java;

public class CharStream {

	String s;
	int i;

	public CharStream(String s)
	{
		this.s = s;
		i = 0;
	}

	public void skip(int count)
	{
		i += count;
	}

	public char read()
	{
		char c = s.charAt(i);
		i++;
		return c;
	}

	public int read(char[] c)
	{
		if(c.length <= s.length() - i)
		{
			s.getChars(i, i + c.length, c, 0);
			i += c.length;
			return c.length;
		}
		else
		{
			int readlen = s.length() - i;
			s.getChars(i, s.length(), c, 0);
			i += readlen;
			return readlen;
		}
	}

	public char[] read(int length)
	{
		if(length <= s.length() - i)
		{
			char[] c = new char[length];
			s.getChars(i, i + length, c, 0);
			i += length;
			return c;
		}
		else
		{
			length = s.length() - i;
			char[] c = new char[length];
			s.getChars(i, s.length(), c, 0);
			i += length;
			return c;
		}
	}

	public String readStr(int length)
	{
		return new String(read(length));
	}

	public boolean isOpen()
	{
		return i + 1 < s.length();
	}

	public void close()
	{
		i = s.length();
	}
}
