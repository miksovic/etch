///$Id$
///
///Created by Champakesan, Badri Narayanan on Jun 13, 2007.
///
///Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.


using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;

namespace Etch.Msg.Test
{
    [TestFixture]
    public class TestMessage
    {

        [TestFixtureSetUp]
        public void First()
        {
            Console.WriteLine();
            Console.Write( "TestMessage" );
        }
        private MyValueFactory vf = new MyValueFactory(); 
        private XType mt1 = new XType(1, "mt"); 
        private XType rmt = new XType(2, "rmt");
        private Field mf1 = new Field(3, "x");
        private Field mf2 = new Field(4, "y");

        public TestMessage()
        {
            mt1.PutValidator( mf1, Validator_int.Get( 0 ) );
            mt1.PutValidator( mf2, Validator_int.Get( 0 ) );
            mt1.PutValidator( vf.mf_messageId, Validator_long.Get( 0 ) );

            rmt.PutValidator( vf.mf_messageId, Validator_long.Get( 0 ) );
            rmt.PutValidator( vf.mf_inReplyTo, Validator_long.Get( 0 ) );

        }

        [Test]
        public void GetVf()
        {
            Message msg = new Message( mt1, vf );
            Assert.AreSame( vf, msg._vf );
        }

        //[Test]
        //public void TestArrayIterator()
        //{
        //    ArrayIterator<int?> fooBar = new ArrayIterator<int?>(new int?[] { 1, 2, 3, 4, 5 });
        //    Assert.IsTrue(fooBar.MoveNext());
        //    Assert.AreEqual(1, fooBar.Current);
        //    Assert.IsTrue(fooBar.MoveNext());
        //    Assert.AreEqual(2, fooBar.Current);
        //    Assert.IsTrue(fooBar.MoveNext());
        //    Assert.AreEqual(3, fooBar.Current);
        //    Assert.IsTrue(fooBar.MoveNext());
        //    Assert.AreEqual(4, fooBar.Current);
        //    Assert.IsTrue(fooBar.MoveNext());
        //    Assert.AreEqual(5, fooBar.Current);
        //    Assert.IsFalse(fooBar.MoveNext());
        //}

        //[Test]
        //public void WriteMessage()
        //{
        //    Message msg = new Message( mt1 , vf );
        //    WriteHelper(msg);

        //    msg[mf1] = 123;
        //    WriteHelper(msg);

        //    msg[mf2] = 234 ;
        //    WriteHelper(msg);
        //}

        //private void WriteHelper(Message msg)
        //{
        //    TaggedDataOutput tdo = new FakeTdo(msg);
        //    msg.WriteMessage(tdo);
        //    //tdo.Close();
        //}

        [Test]
        public void Reply()
        {
            Message msg = new Message(mt1, vf);
            msg.MessageId = 12345L;

            Message rmsg = msg.Reply(rmt);
            Assert.AreSame(rmt, rmsg.GetXType);
            Assert.AreSame(vf, rmsg._vf);
            Assert.AreEqual(12345L, rmsg.InReplyTo);
        }

        [Test]
        public void MessageId()
        {
            Message msg = new Message(mt1, vf);
            Assert.IsNull(msg.MessageId);
            msg.MessageId = 234L;
            Assert.AreEqual(234L, msg.MessageId);
            msg.MessageId = 345L;
            Assert.AreEqual(345L, msg.MessageId);
        }

        [Test]
        public void InReplyTo()
        {
            Message msg = new Message(rmt, vf);
            Assert.IsNull(msg.InReplyTo);
            msg.InReplyTo = 234L;
            Assert.AreEqual(234L, msg.InReplyTo);
            msg.InReplyTo = 345L;
            Assert.AreEqual(345L, msg.InReplyTo);
        }

        //public class FakeTdo : TaggedDataOutput 
        //{
        //    public FakeTdo(Message msg)
        //    {
        //        this.xmsg = msg;
        //    }

        //    private Message xmsg; 

        //    public void StartMessage(Message msg)
        //    {
        //        Assert.AreSame(xmsg, msg);
        //        Assert.IsFalse(started);
        //        Assert.IsFalse(ended);

        //        started = true;
        //    }

        //    private bool started;

        //    private bool ended;

        //    public void WriteStructElement(Field key, Object value)
        //    {
        //        Assert.IsTrue(started);
        //        Assert.IsFalse(ended);
        //        items[key] = value;
        //    }

        //    private Dictionary<Field, Object> items = new Dictionary<Field, Object>();

        //    public void EndMessage(Message msg)
        //    {
        //        Assert.AreSame(xmsg, msg);
        //        Assert.IsTrue(started);
        //        Assert.IsFalse(ended);

        //        ended = true;
        //    }

        //    public void Close()
        //    {
        //        Assert.IsTrue(started);
        //        Assert.IsTrue(ended);

        //        Assert.AreEqual(xmsg.Count, items.Count);
        //        Assert.AreEqual(xmsg, items); //entrySet() deleted
        //    }

        //    public void EndArray(ArrayValue array)
        //    {
        //        throw new NotSupportedException("not implemented");
        //    }

        //    public void EndStruct(StructValue struc)
        //    {
        //        throw new NotSupportedException("not implemented");
        //    }

        //    public void StartArray(ArrayValue array)
        //    {
        //        throw new NotSupportedException("not implemented");
        //    }

        //    public void StartStruct(StructValue struc)
        //    {
        //        throw new NotSupportedException("not implemented");
        //    }

        //    public void WriteArrayElement(Object value)
        //    {
        //        throw new NotSupportedException("not implemented");
        //    }

        //    #region TaggedDataOutput Members


        //    public void SetBuffer( Etch.Transport.FlexBuffer msgBuf )
        //    {
        //        // ignore
        //    }

        //    #endregion
        //}

        public class MyValueFactory : ValueFactory
	    {
		    ///////////////
		    // MESSAGEID //
		    ///////////////
    		
		    public long? GetMessageId( Message msg )
		    {
			    return (long?) msg.Get( mf_messageId );
		    }

		    public void SetMessageId( Message msg, long? msgid )
		    {
			    msg[mf_messageId] = msgid;
		    }
    		
		    public Field mf_messageId = new Field( "_messageId" );

		    ///////////////
		    // INREPLYTO //
		    ///////////////
    		
		    public long? GetInReplyTo( Message msg )
		    {
			     return (long?) msg.Get( mf_inReplyTo );
		    }

		    public void SetInReplyTo( Message msg, long? msgid )
		    {
			    msg[mf_inReplyTo] = msgid ;
		    }
    		
		    public  Field mf_inReplyTo = new Field( "_inReplyTo" );

		    ////////////
		    // UNUSED //
		    ////////////
    		

		    public StructValue ExportCustomValue( Object value )
		    {
                throw new NotSupportedException("not implemented");
		    }

		 

		    public Encoding GetStringEncoding()
		    {
                throw new NotSupportedException("not implemented");
		    }

		    public XType GetType( int id )
		    {
                throw new NotSupportedException("not implemented");
		    }

		    public XType GetType( String name )
		    {
                throw new NotSupportedException("not implemented");
		    }

		    public ICollection<XType> GetTypes()
		    {
                throw new NotSupportedException("not implemented");
		    }

		    public Object ImportCustomValue( StructValue sv )
		    {
                throw new NotSupportedException("not implemented");
		    }

            public XType GetCustomStructType( Type c )
		    {
                throw new NotSupportedException("not implemented");
		    }

            public XType Get_mt__Etch_AuthException()
            {
                throw new NotSupportedException("not implemented");
            }

            public XType Get_mt__Etch_RuntimeException()
            {
                throw new NotSupportedException("not implemented");
            }

            public XType get_mt__exception()
            {
                throw new NotSupportedException("not implemented");
            }

            #region ValueFactory Members

            public XType GetType( int? id )
            {
                throw new Exception( "The method or operation is not implemented." );
            }

            public Field GetField( int? id )
            {
                throw new Exception( "The method or operation is not implemented." );
            }

            #endregion
        }

        
    }
}