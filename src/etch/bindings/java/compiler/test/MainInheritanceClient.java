// Generated by:
// @EtchVersion@ (@EtchBuildTag@) / java @EtchVersion@ (@EtchBuildTag@)
// Fri Apr 11 07:45:30 CDT 2008

package etch.bindings.java.compiler.test;


/**
 * Main program for InheritanceClient. This program makes a connection to the
 * listener created by MainInheritanceListener.
 */
public class MainInheritanceClient implements InheritanceHelper.InheritanceClientFactory
{
	/**
	 * Main program for InheritanceClient.
	 * 
	 * @param args
	 * @throws Exception
	 */
	public static void main( String[] args ) throws Exception
	{
		String uri = "tcp://localhost:4001";
		if (args.length > 0)
			uri = args[0];

		MainInheritanceClient implFactory = new MainInheritanceClient();
		
		RemoteInheritanceServer server = InheritanceHelper.newServer( uri, null,
			implFactory );

		server._startAndWaitUp( 4000 );

		// -------------------------------------------------------------
		// Insert Your Code Here
		// -------------------------------------------------------------

		server._stopAndWaitDown( 4000 );
	}

	public InheritanceClient newInheritanceClient( RemoteInheritanceServer server )
		throws Exception
	{
		return new ImplInheritanceClient( server );
	}
}