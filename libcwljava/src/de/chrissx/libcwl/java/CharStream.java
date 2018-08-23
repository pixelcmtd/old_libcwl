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
			int strtidx = i;
			int endindx = s.length();
			s.getChars(strtidx, endindx, c, 0);
			i += readlen;
			return readlen;
		}
	}
	
	public char[] read(int length)
	{
		if(length <= s.length() - i)
		{
			
		}
		else
		{
			
		}
	}
}
