// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / csharp @EtchVersion@ (@EtchBuildTag@)
//   Mon Apr 28 11:23:44 CDT 2008
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Etch.Util;
using Etch.Msg;
using Etch.Support;
using Etch.Transport;

namespace etch.bindings.csharp.examples.types
{

    ///
    ///<summary> Main implementation for TypesClient. </summary>
    ///
    public class MainTypesClient : TypesHelper.TypesClientFactory
    {
        ///
        /// <summary>Main for TypesClient</summary>
        /// <param name="args"></param>
        ///
        public static void Main(String[] args)
        {
            string uri = "tcp://localhost:4001";

            MainTypesListener.Main1(null);
            MainTypesClient implFactory = new MainTypesClient();
            RemoteTypesServer server = TypesHelper.NewServer(uri, null, implFactory);

            server._TransportControl(Etch.Transport.TransportConsts.START_AND_WAIT_UP, 4000);

            Hashtable table = new Hashtable();
            table.Add("1", "Entry1");
            table.Add("2", "Entry2");

            IDictionary map1 = server.test1(table);


            ArrayList list = new ArrayList();

            list.Add("List1");
            IList list1 = server.test3(list);



            DateTime date = server.test4(DateTime.Now);


            Hashtable set = new Hashtable();
            set.Add("1", null);
            set.Add("2", null);


            Hashtable retset = server.test2(set);

            server._TransportControl(Etch.Transport.TransportConsts.STOP_AND_WAIT_DOWN, 4000);

        }

        ///
        /// <summary>Constructs the MainTypesClient.</summary>
        ///
        public MainTypesClient()
        {
            // Nothing to do.
        }

        ///
        /// <summary>Return a new instance of TypesClient.</summary>
        /// @param server
        ///
        public TypesClient NewTypesClient(RemoteTypesServer server)
        {
            return new ImplTypesClient(server);
        }

    }

}