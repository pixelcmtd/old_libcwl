package de.chrissx.libcwl.java;

import java.nio.charset.CharacterCodingException;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.StandardCharsets;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.util.Base64;

public class InternalConstsNUtils {
	public static final byte[] d1_separator = new byte[] {10, 13};
	public static final byte[] d2_separator = new byte[] {11};
	public static final byte[] d2_is_tu = new byte[] {1};
	public static final byte[] d2_is_no_tu = new byte[] {0};
	public static final byte[] l1_tu_sep = new byte[] {11};
	public static final byte[] l1_non_tu_sep = new byte[] {8};
	public static final byte[] l1_url_end = new byte[] {11};
	static final CharsetEncoder _leunicodeenc = StandardCharsets.UTF_16LE.newEncoder();
	static final CharsetDecoder _leunicodedec = StandardCharsets.UTF_16LE.newDecoder();
	static final CharsetEncoder _asciienc = StandardCharsets.US_ASCII.newEncoder();
	static final CharsetDecoder _asciidec = StandardCharsets.US_ASCII.newDecoder();
	static final CharsetEncoder _utf8enc = StandardCharsets.UTF_8.newEncoder();
	static final CharsetDecoder _utf8dec = StandardCharsets.UTF_8.newDecoder();
	public static final byte[] cwld_header = new byte[] {67, 87, 76, 68, 13, 10, 26, 10};
	public static final byte[] cwll_header = new byte[] {67, 87, 76, 76};
	
	public static char leunicode(byte one, byte two) throws CharacterCodingException
	{
		return _leunicodedec.decode(ByteBuffer.wrap(new byte[] {one, two})).array()[0];
	}
	
	public static char ascii(byte b) throws CharacterCodingException
	{
		return _asciidec.decode(ByteBuffer.wrap(new byte[] {b})).array()[0];
	}
	
	public static String leunicode(byte[] b) throws CharacterCodingException
	{
		return _leunicodedec.decode(ByteBuffer.wrap(b)).toString();
	}
	
	public static String ascii(byte[] b) throws CharacterCodingException
	{
		return _asciidec.decode(ByteBuffer.wrap(b)).toString();
	}
	
	public static byte[] leunicode(String s) throws CharacterCodingException
	{
		return _leunicodeenc.encode(CharBuffer.wrap(s)).array();
	}
	
	public static byte[] ascii(String s) throws CharacterCodingException
	{
		return _asciienc.encode(CharBuffer.wrap(s)).array();
	}
	
	public static byte[] leunicode(char c) throws CharacterCodingException
	{
		return _leunicodeenc.encode(CharBuffer.wrap(new char[] {c})).array();
	}
	
	public static byte[] ascii(char c) throws CharacterCodingException
	{
		return _asciienc.encode(CharBuffer.wrap(new char[] {c})).array();
	}

	public static byte[] utf8(String s) throws CharacterCodingException
	{
		return _utf8enc.encode(CharBuffer.wrap(s)).array();
	}

	public static byte[] b64(String s)
	{
		return Base64.getDecoder().decode(s);
	}
}
