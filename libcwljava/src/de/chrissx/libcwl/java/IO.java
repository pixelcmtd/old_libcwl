package de.chrissx.libcwl.java;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.Optional;
import java.util.Spliterator;
import java.util.function.BiConsumer;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.IntFunction;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.function.ToDoubleFunction;
import java.util.function.ToIntFunction;
import java.util.function.ToLongFunction;
import java.util.stream.Collector;
import java.util.stream.DoubleStream;
import java.util.stream.IntStream;
import java.util.stream.LongStream;
import java.util.stream.Stream;
import java.util.zip.DeflaterInputStream;
import java.util.zip.DeflaterOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class IO {

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
	
	public static WL loadCwlu(File f) throws IOException
	{
		ZipFile zip = new ZipFile(f);
		if(readSingleByteEntry(zip, "F") != 3)
			throw new IOException("The file format is not 3, so you tried to load a .cwlu file that isn't actually a file encoded in the CWLU format.");
		if(readSingleByteEntry(zip, "V") != 1)
			throw new IOException("The format version is not 1, there is no other CWLU than CWLUv1, so this appears to be broken.");
		List<Item> items = new ArrayList<Item>();
		String xml = InternalConstsNUtils.leunicode(readEntry(zip, "W"));
		for(String tag : xml.replaceAll("\r", "").replaceAll("\n", "").split("<"))
		{
			
			if(tag.split(" ")[0] != "i")
				continue;
			String rawArgs = tag.substring(2);
		}
		return new WL(items);
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
