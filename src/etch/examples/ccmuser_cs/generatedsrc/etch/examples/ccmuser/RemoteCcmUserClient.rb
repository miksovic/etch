# This file automatically generated by:
#   Etch Version 0.95/ruby backend 0.95
#   Wed Aug 15 18:39:49 CDT 2007

require 'etch/bindings/ruby/msg/message'
require 'etch/bindings/ruby/support/delivery_service'
require 'etch/bindings/ruby/support/mailbox'
require 'etch/bindings/ruby/idl/test/Test'

require 'etch/bindings/ruby/idl/test/RemoteTest'
require 'etch/bindings/ruby/idl/test/CcmUserClient'

#
# Call to message translator for CcmUserClient.
#
class RemoteCcmUserClient < RemoteCcmUser 
	include CcmUserClient

	#
	# Constructs the RemoteCcmUserClient.
	#
	# @param svc
	#
	# first param should be delivery service
	# second param should be the value factory (optional)
	def initialize( *args )
		
		if ( args[1] == nil)
			super( args[0], ValueFactoryCcmUser.new )
		else
			super( args[0], args[1] )
		end	
	end

	def DoINeedThis()
	
 _end_DoINeedThis( _begin_DoINeedThis(	) )
	end
	
	def _begin_DoINeedThis( 	)
	
		_msg = _newMessage( ValueFactoryCcmUser::MT_etch_examples_ccmuser_CcmUserClient_DoINeedThis )
		return _svc.begincall( _msg )
	end
	
	def _end_DoINeedThis( _mb )
	
		begin
		
 _svc.endvoidcall( _mb,ValueFactoryCcmUser::MT_etch_examples_ccmuser_CcmUserServer__result_DoINeedThis,ValueFactoryCcmUser::MF_result, 0 ) 		
		rescue Exception =>_e 
		
			raise _e, "unexpected"
		end
	end

end
