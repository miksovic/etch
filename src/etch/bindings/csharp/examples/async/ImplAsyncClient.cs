// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / csharp @EtchVersion@ (@EtchBuildTag@)
//   Tue Apr 15 15:02:10 CDT 2008


using System;

/**
 * Call to message translator for AsyncClient.
 */
namespace etch.bindings.csharp.examples.async
{

	public class ImplAsyncClient : BaseAsyncClient
	{

		/// 
		/// <summary>Constructs the ImplAsyncClient.</summary>
		///
 		/// <param name=server></param>
 		///
		public ImplAsyncClient(RemoteAsyncServer server )
		{
		    this.server = server;
            _delegate_sync = my_sync;
            _delegate_async_free = my_async_free;
            _delegate_async_queued = my_async_queued;

		}

	    private readonly RemoteAsyncServer server;

        ///
        /// <summary>Begins the call to sync.</summary>
        ///
        public int? my_sync(
                int? count
            )
        {
            return count > 0 ? server.sync(count - 1) + 1 : 0;
        }
        ///
        /// <summary>Begins the call to async_queued.</summary>
        ///
        public int? my_async_queued(
                int? count
            )
        {
            return count > 0 ? server.async_queued(count - 1) + 1 : 0;
        }
        ///
        /// <summary>Begins the call to async_free.</summary>
        ///
        public int? my_async_free(
                int? count
            )
        {
            return count > 0 ? server.async_free(count - 1) + 1 : 0;
        }

		
	}
}