/* $Id$
 *
 * Created by sccomer on March 28, 2007.
 *
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 */

package etch.compiler.ast;

import etch.bindings.java.msg.IdName;
import etch.compiler.Backend;
import etch.compiler.ParseException;

/**
 * An enumeration item declaration from the etch idl.
 */
public class Item extends Named<Enumx>
{
	/**
	 * Constructs the Item.
	 *
	 * @param enumx
	 * @param name
	 */
	public Item( Enumx enumx, Name name )
	{
		super( enumx, name, null );
		
		vname = name.name;
		id = IdName.hash( name.name );
	}
	
	private final String vname;
	
	private final Integer id;
	
	@Override
	public String vname( Backend helper )
	{
		return helper.mfvname( vname );
	}
	
	@Override
	public String fqname()
	{
		return null;
	}
	
	@Override
	public Integer id()
	{
		return id;
	}
	
	@Override
	public String toString()
	{
		return name().toString();
	}

	@Override
	public void dump( String indent )
	{
		System.out.printf( "%sitem %s\n", indent, name().name );
		
		String sIndent = indent+"  ";
		
		for (String s: descr())
			System.out.printf( "%sdescr %s\n", sIndent, s );
	}

	@Override
	public void check()
	{
		// nothing to do.
	}

	@Override
	public void treewalk( TreeWalker walker ) throws ParseException
	{
		walker.doItem( this );
	}
}
