// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / csharp @EtchVersion@ (@EtchBuildTag@)
//   Mon Apr 28 11:23:44 CDT 2008


using System;

/**
 * Call to message translator for TypesServer.
 */
namespace etch.bindings.csharp.examples.types
{

    public class ImplTypesServer : BaseTypesServer
    {

        /// 
        /// <summary>Constructs the ImplTypesServer.</summary>
        ///
        /// <param name=client></param>
        ///
        public ImplTypesServer(RemoteTypesClient client)
        {
            this.client = client;
            _delegate_test1 = TestMap;
            _delegate_test2 = TestSet;
            _delegate_test3 = TestList;
            _delegate_test4 = TestDateTime;
        }

        private readonly RemoteTypesClient client;

        // Implement delegates or provide implementation of client

        public System.Collections.IDictionary TestMap(System.Collections.IDictionary map)
        {
            Console.WriteLine("map = " + map);
            foreach (object key in map.Keys)
            {
                string value = (string)map[key];
                Console.WriteLine(" The key is {0} and value is {1}", key, value);
            }
            return map;
        }

        public System.Collections.IList TestList(System.Collections.IList list)
        {
            Console.WriteLine("List = " + list);
            foreach (object key in list)
            {
                Console.WriteLine(" The value in list is {0}", key);
            }
            return list;
        }

        public System.DateTime TestDateTime(System.DateTime date)
        {
            Console.WriteLine("DateTime = " + date);
            return date;
        }

        public System.Collections.Hashtable TestSet(System.Collections.Hashtable table)
        {
            foreach (object key in table.Keys)
            {
                Console.WriteLine(" The value in set is {0}", key);
            }
            return table;
        }

    }
}