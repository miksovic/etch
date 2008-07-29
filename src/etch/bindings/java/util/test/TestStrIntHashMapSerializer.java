/* $Id$
 *
 * Created by wert on Jun 25, 2007.
 *
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 */

package etch.bindings.java.util.test;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import etch.bindings.java.msg.ImportExportHelper;
import etch.bindings.java.msg.StructValue;
import etch.bindings.java.msg.Type;
import etch.bindings.java.support.Class2TypeMap;
import etch.bindings.java.util.StrIntHashMap;
import etch.bindings.java.util.StrIntHashMapSerializer;

/** Tests StrIntHashMapSerializer */
public class TestStrIntHashMapSerializer
{
	/** @throws Exception */
	@Test
	public void test0() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void test1() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void test2() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		map.put( "b", 2 );
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void test3() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		map.put( "b", 2 );
		map.put( "c", 3 );
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void testNullValue() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		map.put( "b", null );
		map.put( "c", 3 );
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void testNullKey() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		map.put( null, 2 );
		map.put( "c", 3 );
		testMap( map );
	}

	/** @throws Exception */
	@Test
	public void testNullKeyValue() throws Exception
	{
		StrIntHashMap map = new StrIntHashMap();
		map.put( "a", 1 );
		map.put( null, null );
		map.put( "c", 3 );
		testMap( map );
	}
	
	private void testMap( StrIntHashMap map )
	{
//		System.out.println( "---------------------------------------------" );
//		System.out.println( "map = "+map );
		
		Type type = new Type( "map" );
		Class2TypeMap class2type = new Class2TypeMap();
		StrIntHashMapSerializer.init( type, class2type );
		ImportExportHelper helper = type.getImportExportHelper();
		
		StructValue sv = helper.exportValue( map );
//		System.out.println( "sv = "+sv );
		
		assertEquals( sv.type(), type );
		
		StrIntHashMap map2 = (StrIntHashMap) helper.importValue( sv );
//		System.out.println( "map2 = "+map2 );
		
		assertEquals( map, map2 );
	}
}
