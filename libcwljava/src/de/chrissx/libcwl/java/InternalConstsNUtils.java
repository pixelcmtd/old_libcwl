package de.chrissx.libcwl.java;

import java.nio.charset.CharacterCodingException;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.StandardCharsets;
import java.nio.ByteBuffer;

public class InternalConstsNUtils {
	public static final byte[] d1_separator = new byte[] {10, 13};
	public static final byte[] d2_separator = new byte[] {11};
	public static final byte[] d2_is_tu = new byte[] {1};
	public static final byte[] d2_is_no_tu = new byte[] {0};
	public static final CharsetEncoder leunicodeenc = StandardCharsets.UTF_16LE.newEncoder();
	public static final CharsetDecoder leunicodedec = StandardCharsets.UTF_16LE.newDecoder();
	public static final CharsetEncoder asciienc = StandardCharsets.US_ASCII.newEncoder();
	public static final CharsetDecoder asciidec = StandardCharsets.US_ASCII.newDecoder();
	public static final byte[] cwld_header = new byte[] {67, 87, 76, 68, 13, 10, 26, 10};
	
	public static char leunicode(byte one, byte two) throws CharacterCodingException
	{
		return leunicodedec.decode(ByteBuffer.wrap(new byte[] {one, two})).array()[0];
	}
}
