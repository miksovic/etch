// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / csharp @EtchVersion@ (@EtchBuildTag@)
//   Tue Apr 15 15:02:11 CDT 2008
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;
using Etch.Util;
using Etch.Msg;
using Etch.Support;
using Etch.Transport;

namespace etch.bindings.csharp.examples.inheritance
{

///
///<summary> Main implementation for InheritanceListener. </summary>
///
public class MainInheritanceListener : InheritanceHelper.InheritanceServerFactory
{ 
	///
 	/// <summary>Main for InheritanceListener.</summary>
	/// <param name="args"></param>
	///
	public static void Main(String[] args)
	{
		string uri = "tcp://localhost:4001";
		if (args.Length > 0)
			uri = args[0];

		MainInheritanceListener implFactory = new MainInheritanceListener();
		Transport<SessionListener> listener = InheritanceHelper.NewListener( uri, null, implFactory );

		listener.TransportControl( TransportConsts.START_AND_WAIT_UP, 4000 );
	}

	///
	/// <summary>Constructs the MainInheritanceListener.</summary>
	///
	public MainInheritanceListener()
	{
		// Nothing to do.
	}

	///
	/// <summary>Return a new instance of InheritanceServer.</summary>
	/// @param client
	///
	public InheritanceServer NewInheritanceServer( RemoteInheritanceClient client )
	{
		return new ImplInheritanceServer( client );
	}
}

}