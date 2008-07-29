// This file automatically generated by
 //  @EtchVersion@ (@EtchBuildTag@) / java @EtchVersion@ (@EtchBuildTag@)
 //  Mon Nov 12 15:38:33 CST 2007
package etch.examples.distmap;

import metreos.util.URL;
import metreos.util.Log;

import etch.bindings.java.compiler.test.Test;

/**
 * Main implementation for DistributedHashTableClient.
 */
public class MainDistributedHashTableClient implements DistributedHashTableClient
{
	/**
	 * Main for DistributedHashTableClient
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args)
		throws Exception
	{
		URL uri = new URL("tcp://0.0.0.0:4001");

		MainDistributedHashTableClient client = new MainDistributedHashTableClient();
		RemoteDistributedHashTableServer server = DistributedHashTableHelper.newDistributedHashTableServer( uri, null, client );

		server._startAndWaitUp( 4000 );

		final boolean myBool1 = Test.BOOL2;
		final byte myByte1 = Test.BYTE5;
		final short myShort1 = Test.SHORT5;
		final int myInt1 = Test.INT5;
		final long myLong1 = Test.LONG5;
		final float myFloat1 = Test.FLOAT5;
		final double myDouble1 = Test.DOUBLE5;
		final String myString1 = Test.STRING3;	
		
		Object myObj;

		// Start testing
		Log.addSink( null );
		
		// size - DHT is empty
		Log.report("DHT", "Size", server.size());
		
		// getAll - DHT is empty
		for(Entry entry: server.getAll())
			Log.report("getAll: ", entry.key, entry.value);
		
		// putObject for each constant type
		server.putObject("boolean1", myBool1);
		Log.report("putObject", "boolean value", myBool1);
		
		server.putObject("byte1", myByte1);
		Log.report("putObject", "byte value", myByte1);
		
		server.putObject("short1", myShort1);
		Log.report("putObject", "short value", myShort1);

		server.putObject("int1", myInt1);
		Log.report("putObject", "int value", myInt1);

		server.putObject("long1", myLong1);
		Log.report("putObject", "long value", myLong1);

		server.putObject("float1", myFloat1);
		Log.report("putObject", "float value", myFloat1);

		server.putObject("double1", myDouble1);
		Log.report("putObject", "double value", myDouble1);
		
		server.putObject("string1", myString1);
		Log.report("putObject", "string value", myString1);	
		
		// size - DHT has entries
		Log.report("DHT", "Size", server.size());
		
		// getAll - DHT has entries
		for(Entry entry: server.getAll())
			Log.report("getAll: ", entry.key, entry.value);
			
		// getObject for each constant type
		myObj = server.getObject("boolean1");
		Log.report("getObject", "myBool1", myObj);
		
		myObj = server.getObject("byte1");
		Log.report("getObject", "myByte1", myObj);	
		
		myObj = server.getObject("short1");
		Log.report("getObject", "myShort1", myObj);	
		
		myObj = server.getObject("int1");
		Log.report("getObject", "myInt1", myObj);	
		
		myObj = server.getObject("long1");
		Log.report("getObject", "myLong1", myObj);	
		
		myObj = server.getObject("float1");
		Log.report("getObject", "myFloat1", myObj);	
		
		myObj = server.getObject("double1");
		Log.report("getObject", "myDouble1", myObj);	
		
		myObj = server.getObject("string1");
		Log.report("getObject", "myString1", myObj);
		
		// removeObject for each constant type
		myObj = server.removeObject("boolean1");
		Log.report("removeObject", "boolean value", myObj);
		
		myObj = server.removeObject("byte1");
		Log.report("removeObject", "byte value", myObj);	
		
		myObj = server.removeObject("short1");
		Log.report("removeObject", "short value", myObj);	
		
		myObj = server.removeObject("int1");
		Log.report("removeObject", "int value", myObj);	
		
		myObj = server.removeObject("long1");
		Log.report("removeObject", "long value", myObj);	
		
		myObj = server.removeObject("float1");
		Log.report("removeObject", "float value", myObj);	
		
		myObj = server.removeObject("double1");
		Log.report("removeObject", "double value", myObj);	
				
		myObj = server.removeObject("string1");
		Log.report("removeObject", "string value", myObj);
		
		// size - Verify that DHT is empty after removing all items
		Log.report("DHT", "Size", server.size());
		
		// getAll - Verify that DHT is empty after removing all items
		for(Entry entry: server.getAll())
			Log.report("getAll: ", entry.key, entry.value);
				
		Log.report("Have a nice day!");
		
		server._stopAndWaitDown( 4000 );
	}

	/**
	 * Constructs the MainDistributedHashTableClient. 
	 */
	public MainDistributedHashTableClient()
	{
		// nothing to do.
	}

}
