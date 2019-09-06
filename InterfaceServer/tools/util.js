/* eslint-disable */

var DataHandle = DataHandle || {};
module.exports.DataHandle = DataHandle;

DataHandle.returnData = function(status, errmsg, data = "") {
    return {
        'status': status,
        'errmsg': errmsg,
          'data':   data,
    }
};

DataHandle.returnError = function(status, errmsg) {
    return {
        'status': status,
        'errmsg': errmsg,
    }
};