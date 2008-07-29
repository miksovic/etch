// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / java @EtchVersion@ (@EtchBuildTag@)
//   Mon Mar 10 18:57:04 CDT 2008

package etch.examples.cuae;

import etch.bindings.java.msg.Field;
import etch.bindings.java.msg.ImportExportHelper;
import etch.bindings.java.msg.StructValue;
import etch.bindings.java.msg.Type;
import etch.bindings.java.support.Class2TypeMap;
import etch.bindings.java.support.DefaultValueFactory;
import etch.bindings.java.support.TypeMap;


/**
 * ValueFactory for Cuae.
 */
@SuppressWarnings("unused")
public final class MyValueFactoryCuae extends DefaultValueFactory
{
	/**
	 * Constructs ValueFactoryTest1.
	 */
	public MyValueFactoryCuae()
	{
		super( types, class2type );
	}
	
	private final static TypeMap types = new TypeMap();
	
	private final static Class2TypeMap class2type = new Class2TypeMap();

	static
	{
		DefaultValueFactory.init( types, class2type );
		initTypes();
		initResults();
		initFields();
		initParams();
	}

	/** Type for etch.examples.cuae.Cuae.Request */
	public static Type _mt_etch_examples_cuae_Cuae_Request;

	/** Type for etch.examples.cuae.Cuae.ReqWithMessage */
	public static Type _mt_etch_examples_cuae_Cuae_ReqWithMessage;

	/** Type for etch.examples.cuae.Cuae.Response */
	public static Type _mt_etch_examples_cuae_Cuae_Response;

	/** Type for etch.examples.cuae.Cuae.RespWithCode */
	public static Type _mt_etch_examples_cuae_Cuae_RespWithCode;

	/** Type for etch.examples.cuae.CuaeServer.doit1 */
	public static Type _mt_etch_examples_cuae_CuaeServer_doit1;

	/** Type for etch.examples.cuae.CuaeClient._result_doit1 */
	public static Type _mt_etch_examples_cuae_CuaeClient__result_doit1;

	/** Type for etch.examples.cuae.CuaeClient.doit2 */
	public static Type _mt_etch_examples_cuae_CuaeClient_doit2;

	/** Type for etch.examples.cuae.CuaeServer._result_doit2 */
	public static Type _mt_etch_examples_cuae_CuaeServer__result_doit2;

	/** Type for etch.examples.cuae.Cuae.doit3 */
	public static Type _mt_etch_examples_cuae_Cuae_doit3;

	/** Type for etch.examples.cuae.Cuae._result_doit3 */
	public static Type _mt_etch_examples_cuae_Cuae__result_doit3;

	/** Type for etch.examples.cuae.Cuae.doit4 */
	public static Type _mt_etch_examples_cuae_Cuae_doit4;

	/** Type for etch.examples.cuae.Cuae._result_doit4 */
	public static Type _mt_etch_examples_cuae_Cuae__result_doit4;

	/** Type for etch.examples.cuae.CuaeServer.test1 */
	public static Type _mt_etch_examples_cuae_CuaeServer_test1;

	/** Type for etch.examples.cuae.CuaeClient.test2 */
	public static Type _mt_etch_examples_cuae_CuaeClient_test2;

	/** Type for etch.examples.cuae.Cuae.test3 */
	public static Type _mt_etch_examples_cuae_Cuae_test3;

	private static void initTypes()
	{
		_mt_etch_examples_cuae_Cuae_Request = types.get( "etch.examples.cuae.Cuae.Request" );
		_mt_etch_examples_cuae_Cuae_ReqWithMessage = types.get( "etch.examples.cuae.Cuae.ReqWithMessage" );
		_mt_etch_examples_cuae_Cuae_Response = types.get( "etch.examples.cuae.Cuae.Response" );
		_mt_etch_examples_cuae_Cuae_RespWithCode = types.get( "etch.examples.cuae.Cuae.RespWithCode" );
		_mt_etch_examples_cuae_CuaeServer_doit1 = types.get( "etch.examples.cuae.CuaeServer.doit1" );
		_mt_etch_examples_cuae_CuaeClient__result_doit1 = types.get( "etch.examples.cuae.CuaeClient._result_doit1" );
		_mt_etch_examples_cuae_CuaeClient_doit2 = types.get( "etch.examples.cuae.CuaeClient.doit2" );
		_mt_etch_examples_cuae_CuaeServer__result_doit2 = types.get( "etch.examples.cuae.CuaeServer._result_doit2" );
		_mt_etch_examples_cuae_Cuae_doit3 = types.get( "etch.examples.cuae.Cuae.doit3" );
		_mt_etch_examples_cuae_Cuae__result_doit3 = types.get( "etch.examples.cuae.Cuae._result_doit3" );
		_mt_etch_examples_cuae_Cuae_doit4 = types.get( "etch.examples.cuae.Cuae.doit4" );
		_mt_etch_examples_cuae_Cuae__result_doit4 = types.get( "etch.examples.cuae.Cuae._result_doit4" );
		_mt_etch_examples_cuae_CuaeServer_test1 = types.get( "etch.examples.cuae.CuaeServer.test1" );
		_mt_etch_examples_cuae_CuaeClient_test2 = types.get( "etch.examples.cuae.CuaeClient.test2" );
		_mt_etch_examples_cuae_Cuae_test3 = types.get( "etch.examples.cuae.Cuae.test3" );
	}

	private static void initResults()
	{
		_mt_etch_examples_cuae_CuaeServer_doit1.setResult( _mt_etch_examples_cuae_CuaeClient__result_doit1 );
		_mt_etch_examples_cuae_CuaeClient__result_doit1.setTimeout( 497 );
		_mt_etch_examples_cuae_CuaeClient_doit2.setResult( _mt_etch_examples_cuae_CuaeServer__result_doit2 );
		_mt_etch_examples_cuae_CuaeServer__result_doit2.setTimeout( 497 );
		_mt_etch_examples_cuae_Cuae_doit3.setResult( _mt_etch_examples_cuae_Cuae__result_doit3 );
		_mt_etch_examples_cuae_Cuae__result_doit3.setTimeout( 497 );
		_mt_etch_examples_cuae_Cuae_doit4.setResult( _mt_etch_examples_cuae_Cuae__result_doit4 );
		_mt_etch_examples_cuae_Cuae__result_doit4.setTimeout( 497 );
	}

	private final static ImportExportHelper IMPORT_EXPORT_HELPER = new ImportExportHelper()
	{
		public final StructValue exportValue( Object value )
		{
			return (StructValue) value;
		}

		public final Object importValue( StructValue struct )
		{
			return struct;
		}
	};
	
	static
	{
		_mt_etch_examples_cuae_Cuae_Request.setImportExportHelper( IMPORT_EXPORT_HELPER );
		_mt_etch_examples_cuae_Cuae_ReqWithMessage.setImportExportHelper( IMPORT_EXPORT_HELPER );
		_mt_etch_examples_cuae_Cuae_ReqWithMessage.setSuperType( _mt_etch_examples_cuae_Cuae_Request );
		_mt_etch_examples_cuae_Cuae_Response.setImportExportHelper( IMPORT_EXPORT_HELPER );
		_mt_etch_examples_cuae_Cuae_RespWithCode.setImportExportHelper( IMPORT_EXPORT_HELPER );
		_mt_etch_examples_cuae_Cuae_RespWithCode.setSuperType( _mt_etch_examples_cuae_Cuae_Response );
	}

	/** Field for code */
	public static Field _mf_code;

	/** Field for msg */
	public static Field _mf_msg;

	/** Field for req */
	public static Field _mf_req;

	/** Field for result */
	public static Field _mf_result;

	private static void initFields()
	{
		_mf_code = new Field( "code" );
		_mf_msg = new Field( "msg" );
		_mf_req = new Field( "req" );
		_mf_result = new Field( "result" );

		_mt_etch_examples_cuae_CuaeClient__result_doit1.setResponseField( _mf_result );
		_mt_etch_examples_cuae_CuaeServer__result_doit2.setResponseField( _mf_result );
		_mt_etch_examples_cuae_Cuae__result_doit3.setResponseField( _mf_result );
		_mt_etch_examples_cuae_Cuae__result_doit4.setResponseField( _mf_result );
	}
	
	static
	{
		// initialize the extern serializers:
	}

	private static void initParams()
	{

		// params for Request
		_mt_etch_examples_cuae_Cuae_Request.putValidator( _mf_code, etch.bindings.java.support.Validator_int.get( 0 ) );

		// params for ReqWithMessage
		_mt_etch_examples_cuae_Cuae_ReqWithMessage.putValidator( _mf_code, etch.bindings.java.support.Validator_int.get( 0 ) );
		_mt_etch_examples_cuae_Cuae_ReqWithMessage.putValidator( _mf_msg, etch.bindings.java.support.Validator_string.get( 0 ) );

		// params for Response
		_mt_etch_examples_cuae_Cuae_Response.putValidator( _mf_msg, etch.bindings.java.support.Validator_string.get( 0 ) );

		// params for RespWithCode
		_mt_etch_examples_cuae_Cuae_RespWithCode.putValidator( _mf_msg, etch.bindings.java.support.Validator_string.get( 0 ) );
		_mt_etch_examples_cuae_Cuae_RespWithCode.putValidator( _mf_code, etch.bindings.java.support.Validator_int.get( 0 ) );

		// params for doit1
		_mt_etch_examples_cuae_CuaeServer_doit1.putValidator( _mf_req, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Request, 0 ) );
		_mt_etch_examples_cuae_CuaeServer_doit1.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for _result_doit1
		_mt_etch_examples_cuae_CuaeClient__result_doit1.putValidator( _mf_result, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Response, 0 ) );
		_mt_etch_examples_cuae_CuaeClient__result_doit1.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );
		_mt_etch_examples_cuae_CuaeClient__result_doit1.putValidator( _mf_result, etch.bindings.java.support.Validator_RuntimeException.get() ); // thrown RuntimeException
		_mt_etch_examples_cuae_CuaeClient__result_doit1.putValidator( _mf__inReplyTo, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for doit2
		_mt_etch_examples_cuae_CuaeClient_doit2.putValidator( _mf_req, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Request, 0 ) );
		_mt_etch_examples_cuae_CuaeClient_doit2.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for _result_doit2
		_mt_etch_examples_cuae_CuaeServer__result_doit2.putValidator( _mf_result, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Response, 0 ) );
		_mt_etch_examples_cuae_CuaeServer__result_doit2.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );
		_mt_etch_examples_cuae_CuaeServer__result_doit2.putValidator( _mf_result, etch.bindings.java.support.Validator_RuntimeException.get() ); // thrown RuntimeException
		_mt_etch_examples_cuae_CuaeServer__result_doit2.putValidator( _mf__inReplyTo, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for doit3
		_mt_etch_examples_cuae_Cuae_doit3.putValidator( _mf_req, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Request, 1 ) );
		_mt_etch_examples_cuae_Cuae_doit3.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for _result_doit3
		_mt_etch_examples_cuae_Cuae__result_doit3.putValidator( _mf_result, etch.bindings.java.support.Validator_StructValue.get( _mt_etch_examples_cuae_Cuae_Response, 1 ) );
		_mt_etch_examples_cuae_Cuae__result_doit3.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );
		_mt_etch_examples_cuae_Cuae__result_doit3.putValidator( _mf_result, etch.bindings.java.support.Validator_RuntimeException.get() ); // thrown RuntimeException
		_mt_etch_examples_cuae_Cuae__result_doit3.putValidator( _mf__inReplyTo, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for doit4
		_mt_etch_examples_cuae_Cuae_doit4.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for _result_doit4
		_mt_etch_examples_cuae_Cuae__result_doit4.putValidator( _mf_result, etch.bindings.java.support.Validator_void.get( 0 ) );
		_mt_etch_examples_cuae_Cuae__result_doit4.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );
		_mt_etch_examples_cuae_Cuae__result_doit4.putValidator( _mf_result, etch.bindings.java.support.Validator_RuntimeException.get() ); // thrown RuntimeException
		_mt_etch_examples_cuae_Cuae__result_doit4.putValidator( _mf__inReplyTo, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for test1
		_mt_etch_examples_cuae_CuaeServer_test1.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for test2
		_mt_etch_examples_cuae_CuaeClient_test2.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );

		// params for test3
		_mt_etch_examples_cuae_Cuae_test3.putValidator( _mf__messageId, etch.bindings.java.support.Validator_long.get( 0 ) );
	}
	
	static
	{
		// done updating types, and class2type: lock them.
		types.lock();
		for (Type t: types.values())
			t.lock();
		class2type.lock();
	}
}