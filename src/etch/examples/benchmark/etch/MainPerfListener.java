// Generated by:
// @EtchVersion@ (@EtchBuildTag@) / java @EtchVersion@ (@EtchBuildTag@)
// Thu May 01 09:15:13 CDT 2008

package etch.examples.benchmark.etch;

import etch.util.Log;
import etch.util.core.io.Transport;

/**
 * Main program for PerfServer. This program makes a listener to accept
 * connections from MainPerfClient.
 */
public class MainPerfListener implements PerfHelper.PerfServerFactory
{
	/**
	 * Main program for PerfServer.
	 * 
	 * @param args
	 * @throws Exception
	 */
	public static void main( String[] args ) throws Exception
	{
		Log.addSink( null );
		Log.report( "MainPerfListener" );
		
		String uri = "tcp://0.0.0.0:4004";
		
		Transport<?> listener = PerfHelper.newListener( uri, null,
			new MainPerfListener() );

		listener.transportControl( Transport.START_AND_WAIT_UP, 4000 );
	}

	public PerfServer newPerfServer( RemotePerfClient client )
	{
		return new ImplPerfServer( client );
	}
}
