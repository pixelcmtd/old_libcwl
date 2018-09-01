package de.chrissx.libcwl.java;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.function.Predicate;

public class WL implements Iterable<Item> {

	public WL(Item... items)
	{
		this.items = Arrays.asList(items);
	}

	public WL(List<Item> items)
	{
		this.items = items;
	}
	
	public List<Item> items;

	@Override
	public boolean equals(Object o)
	{
		return o instanceof WL ? equals((WL)o) : false;
	}

	public boolean equals(WL wl)
	{
		if(wl.length() != length())
			return false;
		for(int i = 0; i < wl.length(); i++)
			if(!wl.get(i).equals(get(i)))
				return false;
		return true;
	}

	public int length()
	{
		return items.size();
	}

	public Item get(int idx)
	{
		return items.get(idx);
	}

	@Override
	public int hashCode()
	{
		int hc = items.get(0).hashCode();
		for(int i = 1; i < items.size(); i++)
			hc *= items.get(i).hashCode();
		return hc;
	}

	public Item[] searchItems(Predicate<Item> predicate)
	{
		Item i = null;
		List<Item> j = new ArrayList<Item>();
		for(int k = 0; k < items.size(); k++)
			if(predicate.test(i = items.get(k)))
				j.add(i);
		return j.toArray(new Item[j.size()]);
	}

	public int getFirstIndex(Predicate<Item> predicate)
	{
		for(int i = 0; i < items.size(); i++)
			if(predicate.test(items.get(i)))
				return i;
		return -1;
	}

	@Override
	public Iterator<Item> iterator() {
		return items.iterator();
	}
}
