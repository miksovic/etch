using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using System.Threading;

namespace Etch.Support.Test
{
    [TestFixture]
    public class TestTodoManager
    {

        [SetUp]
        public void Setup()
        {
            MyTodo.ResetGlobalId();
        }

        [Test]
        [ExpectedException(typeof(ThreadInterruptedException))]
        public void TestManagerNotStarted()
        {
            TodoManager mgr = new TodoManager( 50, 10, 1, 5, 5000, 1 );
            mgr.Add( new MyTodo() );
        }

        [Test]
        [ExpectedException( typeof( ThreadInterruptedException ) )]
        public void TestShutDown()
        {
            TodoManager mgr = TodoManager.GetTodoManager();
            mgr.Add( new MyTodo() );

            TodoManager.ShutDown();
            
            // adding after shutting down should cause exception
            mgr.Add( new MyTodo() );
        }

        [Test]
        public void TestWorkersAndEntries()
        {
            TodoManager mgr = new TodoManager( 50, 10, 1, 5, 5000, 1 );
            mgr.Start();

            Assert.AreEqual( 0, mgr.NumEntries() );
            Assert.AreEqual( 0, mgr.NumWorkers() );
            
            mgr.Add( new MyTodo() );

            Assert.AreEqual( 1, mgr.NumEntries() );
            Assert.AreEqual( 1, mgr.NumWorkers() );
            
            // experiment with a total of 50 entries.
            for ( int i = 0; i < 49; i++ )
            {
                mgr.Add( new MyTodo() );
            }

            Assert.AreEqual( 50, MyTodo.LastIdGenerated() );
            
            WaitTillComplete( 4000 );
            //Assert.AreEqual( 5, mgr.NumWorkers() );

            
            // test if all todo's were executed. 
            Assert.AreEqual( 0, mgr.NumEntries() );
        }

        [Test]
        public void TestSeparateThreads()
        {
            TodoManager mgr = TodoManager.GetTodoManager();
            TodoManager.GetTodoManager().Add( new MyTodo() );

            // Start another thread to add items to the todomanager. 
            ( new Thread( new ThreadStart( AddUsingDifferentThread ) ) ).Start();

            // simple "lock"
            while ( simpleLock != true )
                ;

            WaitTillComplete( 4000 );
        }

        // Thread that adds independently to the queue. 
        public void AddUsingDifferentThread()
        {
            TodoManager.GetTodoManager().Add( new MyTodo() );
            
            simpleLock = true;
        }
        private bool simpleLock = false;

        /// <summary>
        /// Wait until all Todos are run. 
        /// </summary>
        /// <param name="maxWait">Max time in milliseconds 
        /// to wait</param>
        private void WaitTillComplete( long maxWait )
        {
            DateTime now = DateTime.Now;

            long nowTime = 0;
            long endTime = nowTime + maxWait;

            TimeSpan span;
            long spanTime = 0;

            while ( true && ( nowTime < endTime ) )
            {
                if ( MyTodo.TodosRemaining() == 0 )
                    return;

                span = DateTime.Now - now;
                now = DateTime.Now;
                spanTime = (long) span.TotalMilliseconds;
                nowTime += spanTime;
            }

            throw new Exception( "Time exceeded" );
        }

        /// <summary>
        /// "Todo" tasks put inside the TodoManager queue. 
        /// </summary>
        public class MyTodo : Todo
        {
            /// <summary>
            /// unique id for every "todo" created
            /// </summary>
            private static int globalId = 0;
            private static int lastRun = 0;
            private int uniqueId = 0;

            public MyTodo()
            {
                globalId++;
                uniqueId = globalId;
                lastRun++;
            }

            public static int LastIdGenerated()
            {
                return globalId;
            }

            /// <summary>
            /// Reset the global id.
            /// </summary>
            public static void ResetGlobalId()
            {
                globalId = 0;
                lastRun = 0;
            }

            /// <summary>
            /// How many todos remain to be run
            /// </summary>
            /// <returns>number of todos remaining</returns>
            public static int TodosRemaining()
            {
                return lastRun;
            }

            public void Doit( TodoManager mgr )
            {
                lastRun--;
            }

            public void Exception( TodoManager mgr, Exception e )
            {
                Console.WriteLine( "exception thrown by todo " + uniqueId );
                Console.WriteLine( e.Message );
                Console.WriteLine( e.StackTrace );
            }
        }
    }
}
