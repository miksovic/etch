﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.832
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------



[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
[System.ServiceModel.ServiceContractAttribute(ConfigurationName="BenchmarkService")]
public interface BenchmarkService
{
    
    [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/BenchmarkService/add", ReplyAction="http://tempuri.org/BenchmarkService/addResponse")]
    System.Nullable<int> add(System.Nullable<int> x, System.Nullable<int> y);
    
    [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/BenchmarkService/sum", ReplyAction="http://tempuri.org/BenchmarkService/sumResponse")]
    System.Nullable<int> sum(int[] values);
    
    [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/BenchmarkService/report", ReplyAction="http://tempuri.org/BenchmarkService/reportResponse")]
    void report(System.Nullable<int> code, string msg);
}

[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
public interface BenchmarkServiceChannel : BenchmarkService, System.ServiceModel.IClientChannel
{
}

[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
public partial class BenchmarkServiceClient : System.ServiceModel.ClientBase<BenchmarkService>, BenchmarkService
{
    
    public BenchmarkServiceClient()
    {
    }
    
    public BenchmarkServiceClient(string endpointConfigurationName) : 
            base(endpointConfigurationName)
    {
    }
    
    public BenchmarkServiceClient(string endpointConfigurationName, string remoteAddress) : 
            base(endpointConfigurationName, remoteAddress)
    {
    }
    
    public BenchmarkServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
            base(endpointConfigurationName, remoteAddress)
    {
    }
    
    public BenchmarkServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
            base(binding, remoteAddress)
    {
    }
    
    public System.Nullable<int> add(System.Nullable<int> x, System.Nullable<int> y)
    {
        return base.Channel.add(x, y);
    }
    
    public System.Nullable<int> sum(int[] values)
    {
        return base.Channel.sum(values);
    }
    
    public void report(System.Nullable<int> code, string msg)
    {
        base.Channel.report(code, msg);
    }
}
