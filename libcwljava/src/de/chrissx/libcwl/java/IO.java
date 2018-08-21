package de.chrissx.libcwl.java;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.DeflaterOutputStream;

public class IO {

	public static void writeCwld(WL wl, File f) throws IOException
	{
		if(f.exists())
			f.delete();
		f.createNewFile();
		FileOutputStream s = new FileOutputStream(f);
		s.write(InternalConsts.cwld_header);
		s.write(4);
		s.write(2);
		DeflaterOutputStream d = new DeflaterOutputStream(s);
		for(Item i : wl)
			i.writeBytes(d, "D2");
		s.close();
	}
	
	public static WL readCwld(File f)
	{
		
	}
}
