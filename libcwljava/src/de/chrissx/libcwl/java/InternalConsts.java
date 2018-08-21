package de.chrissx.libcwl.java;

import java.nio.charset.CharsetEncoder;

public class InternalConsts {
	public static final byte[] d1_separator = new byte[] {10, 13};
	public static final byte[] d2_separator = new byte[] {11};
	public static final byte[] d2_is_tu = new byte[] {1};
	public static final byte[] d2_is_no_tu = new byte[] {0};
	public static final CharsetEncoder unicode = java.nio.charset.StandardCharsets.UTF_16LE.newEncoder();
	public static final CharsetEncoder ascii = java.nio.charset.StandardCharsets.US_ASCII.newEncoder();
	public static final byte[] cwld_header = new byte[] {67, 87, 76, 68, 13, 10, 26, 10};
}
