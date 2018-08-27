package de.chrissx.libcwl.java;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.DeflaterInputStream;
import java.util.zip.DeflaterOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class IO {

	public static WL read(File f) throws IOException
	{
		String s = f.toString().toLowerCase();
		if(s.endsWith(".cwlu"))
			return readCwlu(f);
		else if(s.endsWith(".cwld"))
			return readCwld(f);
		else
			throw new IOException("Only CWLU and CWLD loading are supported at the moment.");
	}

	public static void writeCwld(WL wl, File f) throws IOException
	{
		if(f.exists())
			f.delete();
		f.createNewFile();
		FileOutputStream s = new FileOutputStream(f);
		s.write(InternalConstsNUtils.cwld_header);
		s.write(4);
		s.write(2);
		DeflaterOutputStream d = new DeflaterOutputStream(s);
		for(Item i : wl)
			i.writeBytes(d, "D2");
		d.close();
	}

	public static WL readCwld(File f) throws IOException
	{
		FileInputStream s = new FileInputStream(f);
		byte[] bfr = new byte[8];
		s.read(bfr);
		if(!clibj.arrequ(bfr, InternalConstsNUtils.cwld_header))
		{
			s.close();
			throw new IOException("CWLD header does not match!");
		}
		int v;
		if(s.read() != 4 || (v = s.read()) > 2)
		{
			s.close();
			throw new IOException("This file is either not a CWLD file or too new for this version of libcwljava.");
		}
		DeflaterInputStream d = new DeflaterInputStream(s);
		if(v == 1)
		{
			List<Item> items = new ArrayList<Item>();
			StringBuilder b = new StringBuilder();
			boolean nus = false;
			Item i = new Item();
			char c;
			int j = -1;
			while((j = d.read()) != -1)
			{
				if((c = InternalConstsNUtils.leunicode((byte)j, (byte)d.read())) == '\u0d0a')
				{
					if(nus)
					{
						i.url = b.toString();
						items.add(i);
						i = new Item();
					}
					else
					{
						i.name = b.toString();
					}
					b = new StringBuilder();
					nus = !nus;
				}
				else
				{
					b.append(c);
				}
			}
			d.close();
			return new WL(items);
		}
		else
		{
			List<Item> li = new ArrayList<Item>();
			StringBuilder b = new StringBuilder();
			boolean cs = false;
			boolean nus = false;
			boolean tu = false;
			Item i = new Item();
			int j = -1;
			byte c = 0;
			while((j = d.read()) != -1)
			{
				if(j == 11 && !cs)
				{
					tu = false;
					if(!nus)
					{
						i.name = b.toString();
						nus = true;
						tu = d.read() == 1;
					}
					else
					{
						i.url = b.toString();
						li.add(i);
						i = new Item();
						nus = false;
					}
					b = new StringBuilder();
					if(tu)
						b.append("http://tinyurl.com/");
				}
				else if(tu)
				{
					b.append(InternalConstsNUtils.ascii((byte)j));
				}
				else if(!cs)
				{
					c = (byte)j;
					cs = true;
				}
				else
				{
					b.append(InternalConstsNUtils.leunicode(c, (byte)j));
					cs = false;
				}
			}
			d.close();
			return new WL(li);
		}
	}
	
	public static WL readCwlu(File f) throws IOException
	{
		ZipFile zip = new ZipFile(f);
		if(readSingleByteEntry(zip, "F") != 3)
			throw new IOException("The file format is not 3, so you tried to load a .cwlu file that isn't actually a file encoded in the CWLU format.");
		if(readSingleByteEntry(zip, "V") != 1)
			throw new IOException("The format version is not 1, but there is no other CWLU than CWLUv1, so this appears to be broken.");
		List<Item> items = new ArrayList<Item>();
		parseXml(InternalConstsNUtils.leunicode(readEntry(zip, "W")), "i", "n", "u");
		return new WL(items);
	}
	
	static List<Item> parseXml(String xml, String itemTag, String nameAttribute, String urlAttribute)
	{
		List<Item> items = new ArrayList<Item>();
		for(String tag : xml.replaceAll("\r", "").replaceAll("\n", "").replaceAll("/>", "").replaceAll(">", "")
				.replaceAll(nameAttribute + "=", nameAttribute).replaceAll(urlAttribute + "=", urlAttribute).split("<"))
		{
			if(!tag.startsWith(itemTag))
				continue;
			CharStream s = new CharStream(tag);
			StringBuilder b = new StringBuilder(); //used to build name and url
			Item i = new Item(); //the item we're reading
			boolean nu = false; //name url
			boolean is = false; //in string
			while(s.isOpen())
			{
				char c = s.read();
				if(is)
				{
					if(c != '"')
						b.append(c);
					else if(c == '"')
					{
						if(nu)
							i.name = b.toString();
						else
							i.url = b.toString();
						is = false;
						b = new StringBuilder();
					}
				}
				else if(c == 'n')
					nu = true;
				else if(c == 'u')
					nu = false;
				else if(c == '"')
					is = true;
			}
			items.add(i);
		}
		return items;
	}
	
	static byte[] readEntry(ZipFile zip, String entryName) throws IOException
	{
		ZipEntry e = zip.getEntry(entryName);
		InputStream is = zip.getInputStream(e);
		byte[] b = new byte[(int) e.getSize()];
		is.read(b);
		is.close();
		return b;
	}
	
	static int readSingleByteEntry(ZipFile zip, String entryName) throws IOException
	{
		ZipEntry e = zip.getEntry(entryName);
		InputStream is = zip.getInputStream(e);
		int i = is.read();
		is.close();
		return i;
	}
}
