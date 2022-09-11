// Auto-generated. Do not edit!

// (in-package pack2.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class testRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ran = null;
    }
    else {
      if (initObj.hasOwnProperty('ran')) {
        this.ran = initObj.ran
      }
      else {
        this.ran = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type testRequest
    // Serialize message field [ran]
    bufferOffset = _serializer.float32(obj.ran, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type testRequest
    let len;
    let data = new testRequest(null);
    // Deserialize message field [ran]
    data.ran = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pack2/testRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0bf7337b4741e03b661dce528144e36a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 ran
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new testRequest(null);
    if (msg.ran !== undefined) {
      resolved.ran = msg.ran;
    }
    else {
      resolved.ran = 0.0
    }

    return resolved;
    }
};

class testResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type testResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type testResponse
    let len;
    let data = new testResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'pack2/testResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new testResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: testRequest,
  Response: testResponse,
  md5sum() { return '0bf7337b4741e03b661dce528144e36a'; },
  datatype() { return 'pack2/test'; }
};
