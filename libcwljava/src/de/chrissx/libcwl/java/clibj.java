package de.chrissx.libcwl.java;

public class clibj {

	public static boolean arrequ(byte[] left, byte[] right)
	{
		if(left.length != right.length)
			return false;
		for(int i = 0; i < left.length; i++)
			if(left[i] != right[i])
				return false;
		return true;
	}
}
