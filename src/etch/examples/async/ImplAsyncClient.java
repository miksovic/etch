// Generated by:
// @EtchVersion@ (@EtchBuildTag@) / java @EtchVersion@ (@EtchBuildTag@)
// Fri Apr 11 08:49:05 CDT 2008

package etch.examples.async;


/**
 * Your custom implementation of BaseAsyncClient. Add methods here to provide
 * implementations of messages from the server.
 */
public class ImplAsyncClient extends BaseAsyncClient
{
	/**
	 * Constructs the ImplAsyncClient.
	 *
	 * @param server a connection to the server session. Use this to send a
	 * message to the server.
	 */
	public ImplAsyncClient( RemoteAsyncServer server )
	{
		this.server = server;
	}
	
	private final RemoteAsyncServer server;

	public Integer sync( Integer count )
	{
		return count > 0 ? server.sync( count - 1 ) + 1 : 0;
	}

	public Integer async_queued( Integer count )
	{
		return count > 0 ? server.async_queued( count - 1 ) + 1 : 0;
	}

	public Integer async_free( Integer count )
	{
		return count > 0 ? server.async_free( count - 1 ) + 1 : 0;
	}
}