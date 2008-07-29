using System;
using System.Collections.Generic;
using System.Text;

namespace Etch.Transport
{
    /// <summary>
    /// Out-of-band query, control, and notification interface for sessions.
    /// </summary>
    public interface Session
    {
        /// <summary>
        /// Gets a configuration or operational value from the handler. The
        /// request is passed up the chain of sessions until some session
        /// recognises the query, whereupon it returns the requested value.
        /// </summary>
        /// <param name="query">an object representing a query, which could be as
        /// simple as a string, integer, or enum, or more complex such as
        /// a class with instance variables for query terms.</param>
        /// <returns>the requested value, or null if not defined.</returns>
        /// Exception:
        ///     throws Exception if the query is not recognised
        ///     by any session (which is to say, if the last session in the session
        ///     chain does not recognise it, it should throw this exception). Typically
        ///     this would be a service's client or server implementation.
        ///     
        Object SessionQuery( Object query );

        /// <summary>
        /// Sets a configuration or operational value in the session. The
        /// request is passed up the chain of sessions until some session
        /// recognises the control, whereupon it stores the specified value
        /// and returns.
        /// </summary>
        /// <param name="control">an object representing a control, which could be as
        /// simple as a string, integer, or enum, or more complex such as
        /// a class with instance variables for control terms.</param>
        /// <param name="value">the value to set</param>
        /// Exception:
        /// 
        ///     throws ArgumentException if the value is not the right
        ///     type or if the value is inappropriate.
        /// 
        ///     throws Exception if the query is not recognised
        ///     by any session (which is to say, if the last session in the session
        ///     chain does not recognise it, it should throw this exception). Typically
        ///     this would be a service's client or server implementation.
        ///     
        void SessionControl( Object control, Object value );

        /// <summary>
        /// Notifies the chain of sessions of the specified event. Unlike query
        /// and control operations above, events are always passed up to the
        /// top to allow all sessions to notice them.
        /// </summary>
        /// <param name="eventObj">a class which represents the event, possibly with
        /// parameters. The simplest event could be a string, integer,
        /// or enum, but any class instance will do (as long as some session
        /// in the chain expects it).</param>
        /// 
        void SessionNotify( Object eventObj );

    }
}
