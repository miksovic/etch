﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System.Xml.Serialization;

// 
// This source code was auto-generated by xsd, Version=2.0.50727.42.
// 


/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
[System.Xml.Serialization.XmlRootAttribute(Namespace="", IsNullable=false)]
public partial class field {
    
    private string descriptionField;
    
    private string nameField;
    
    private string fieldIdField;
    
    private string fieldNameField;
    
    private string typeField;
    
    private string isArrayField;
    
    private string dimensionField;
    
    private string isPrimitiveTypeField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string fieldId {
        get {
            return this.fieldIdField;
        }
        set {
            this.fieldIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string fieldName {
        get {
            return this.fieldNameField;
        }
        set {
            this.fieldNameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string type {
        get {
            return this.typeField;
        }
        set {
            this.typeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string isArray {
        get {
            return this.isArrayField;
        }
        set {
            this.isArrayField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string dimension {
        get {
            return this.dimensionField;
        }
        set {
            this.dimensionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string isPrimitiveType {
        get {
            return this.isPrimitiveTypeField;
        }
        set {
            this.isPrimitiveTypeField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
[System.Xml.Serialization.XmlRootAttribute(Namespace="", IsNullable=false)]
public partial class exception {
    
    private string descriptionField;
    
    private field[] fieldField;
    
    private string nameField;
    
    private string isUncheckedField;
    
    private string typeIdField;
    
    private string typeNameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("field")]
    public field[] field {
        get {
            return this.fieldField;
        }
        set {
            this.fieldField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string isUnchecked {
        get {
            return this.isUncheckedField;
        }
        set {
            this.isUncheckedField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeId {
        get {
            return this.typeIdField;
        }
        set {
            this.typeIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeName {
        get {
            return this.typeNameField;
        }
        set {
            this.typeNameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
[System.Xml.Serialization.XmlRootAttribute(Namespace="", IsNullable=false)]
public partial class module {
    
    private string descriptionField;
    
    private moduleService[] serviceField;
    
    private string nameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("service", Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public moduleService[] service {
        get {
            return this.serviceField;
        }
        set {
            this.serviceField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleService {
    
    private string descriptionField;
    
    private moduleServiceConstsConst[] constsField;
    
    private moduleServiceExternsExtern[] externsField;
    
    private moduleServiceEnumsEnum[] enumsField;
    
    private moduleServiceStructsStruct[] structsField;
    
    private exception[] exceptionsField;
    
    private moduleServiceMethodsMethod[] methodsField;
    
    private string nameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("const", typeof(moduleServiceConstsConst), Form=System.Xml.Schema.XmlSchemaForm.Unqualified, IsNullable=false)]
    public moduleServiceConstsConst[] consts {
        get {
            return this.constsField;
        }
        set {
            this.constsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("extern", typeof(moduleServiceExternsExtern), Form=System.Xml.Schema.XmlSchemaForm.Unqualified, IsNullable=false)]
    public moduleServiceExternsExtern[] externs {
        get {
            return this.externsField;
        }
        set {
            this.externsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("enum", typeof(moduleServiceEnumsEnum), Form=System.Xml.Schema.XmlSchemaForm.Unqualified, IsNullable=false)]
    public moduleServiceEnumsEnum[] enums {
        get {
            return this.enumsField;
        }
        set {
            this.enumsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("struct", typeof(moduleServiceStructsStruct), Form=System.Xml.Schema.XmlSchemaForm.Unqualified, IsNullable=false)]
    public moduleServiceStructsStruct[] structs {
        get {
            return this.structsField;
        }
        set {
            this.structsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("exception", typeof(exception), IsNullable=false)]
    public exception[] exceptions {
        get {
            return this.exceptionsField;
        }
        set {
            this.exceptionsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    [System.Xml.Serialization.XmlArrayItemAttribute("method", typeof(moduleServiceMethodsMethod), Form=System.Xml.Schema.XmlSchemaForm.Unqualified, IsNullable=false)]
    public moduleServiceMethodsMethod[] methods {
        get {
            return this.methodsField;
        }
        set {
            this.methodsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceConstsConst {
    
    private string descriptionField;
    
    private string nameField;
    
    private string typeField;
    
    private string valueField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string type {
        get {
            return this.typeField;
        }
        set {
            this.typeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string value {
        get {
            return this.valueField;
        }
        set {
            this.valueField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceExternsExtern {
    
    private moduleServiceExternsExternExternmap[] externmapField;
    
    private string nameField;
    
    private string typeIdField;
    
    private string typeNameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("externmap", Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public moduleServiceExternsExternExternmap[] externmap {
        get {
            return this.externmapField;
        }
        set {
            this.externmapField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeId {
        get {
            return this.typeIdField;
        }
        set {
            this.typeIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeName {
        get {
            return this.typeNameField;
        }
        set {
            this.typeNameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceExternsExternExternmap {
    
    private string languageField;
    
    private string nameField;
    
    private string nImportField;
    
    private string serializerField;
    
    private string sImportField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string language {
        get {
            return this.languageField;
        }
        set {
            this.languageField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string nImport {
        get {
            return this.nImportField;
        }
        set {
            this.nImportField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string serializer {
        get {
            return this.serializerField;
        }
        set {
            this.serializerField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string sImport {
        get {
            return this.sImportField;
        }
        set {
            this.sImportField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceEnumsEnum {
    
    private string descriptionField;
    
    private moduleServiceEnumsEnumEntry[] entryField;
    
    private string nameField;
    
    private string typeIdField;
    
    private string typeNameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("entry", Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public moduleServiceEnumsEnumEntry[] entry {
        get {
            return this.entryField;
        }
        set {
            this.entryField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeId {
        get {
            return this.typeIdField;
        }
        set {
            this.typeIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeName {
        get {
            return this.typeNameField;
        }
        set {
            this.typeNameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceEnumsEnumEntry {
    
    private string valueField;
    
    private string entryIdField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string value {
        get {
            return this.valueField;
        }
        set {
            this.valueField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string entryId {
        get {
            return this.entryIdField;
        }
        set {
            this.entryIdField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceStructsStruct {
    
    private string descriptionField;
    
    private field[] fieldField;
    
    private string nameField;
    
    private string typeIdField;
    
    private string typeNameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("field")]
    public field[] field {
        get {
            return this.fieldField;
        }
        set {
            this.fieldField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeId {
        get {
            return this.typeIdField;
        }
        set {
            this.typeIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeName {
        get {
            return this.typeNameField;
        }
        set {
            this.typeNameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceMethodsMethod {
    
    private string descriptionField;
    
    private exception[] exceptionField;
    
    private moduleServiceMethodsMethodAuthorize[] authorizeField;
    
    private field[] fieldField;
    
    private moduleServiceMethodsMethodResult[] resultField;
    
    private string nameField;
    
    private string typeIdField;
    
    private string typeNameField;
    
    private string asyncReceiverModeField;
    
    private string isOnewayField;
    
    private string messageDirectionField;
    
    private string timeoutField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("exception")]
    public exception[] exception {
        get {
            return this.exceptionField;
        }
        set {
            this.exceptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("authorize", Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public moduleServiceMethodsMethodAuthorize[] authorize {
        get {
            return this.authorizeField;
        }
        set {
            this.authorizeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("field")]
    public field[] field {
        get {
            return this.fieldField;
        }
        set {
            this.fieldField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("result", Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public moduleServiceMethodsMethodResult[] result {
        get {
            return this.resultField;
        }
        set {
            this.resultField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeId {
        get {
            return this.typeIdField;
        }
        set {
            this.typeIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string typeName {
        get {
            return this.typeNameField;
        }
        set {
            this.typeNameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string asyncReceiverMode {
        get {
            return this.asyncReceiverModeField;
        }
        set {
            this.asyncReceiverModeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string isOneway {
        get {
            return this.isOnewayField;
        }
        set {
            this.isOnewayField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string messageDirection {
        get {
            return this.messageDirectionField;
        }
        set {
            this.messageDirectionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string timeout {
        get {
            return this.timeoutField;
        }
        set {
            this.timeoutField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceMethodsMethodAuthorize {
    
    private string methodNameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string methodName {
        get {
            return this.methodNameField;
        }
        set {
            this.methodNameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public partial class moduleServiceMethodsMethodResult {
    
    private string descriptionField;
    
    private string fieldIdField;
    
    private string fieldNameField;
    
    private string typeField;
    
    private string isArrayField;
    
    private string dimensionField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(Form=System.Xml.Schema.XmlSchemaForm.Unqualified)]
    public string description {
        get {
            return this.descriptionField;
        }
        set {
            this.descriptionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string fieldId {
        get {
            return this.fieldIdField;
        }
        set {
            this.fieldIdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string fieldName {
        get {
            return this.fieldNameField;
        }
        set {
            this.fieldNameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string type {
        get {
            return this.typeField;
        }
        set {
            this.typeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string isArray {
        get {
            return this.isArrayField;
        }
        set {
            this.isArrayField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string dimension {
        get {
            return this.dimensionField;
        }
        set {
            this.dimensionField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
[System.Xml.Serialization.XmlRootAttribute(Namespace="", IsNullable=false)]
public partial class NewDataSet {
    
    private object[] itemsField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("exception", typeof(exception))]
    [System.Xml.Serialization.XmlElementAttribute("field", typeof(field))]
    [System.Xml.Serialization.XmlElementAttribute("module", typeof(module))]
    public object[] Items {
        get {
            return this.itemsField;
        }
        set {
            this.itemsField = value;
        }
    }
}