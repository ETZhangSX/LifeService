/* eslint-disable */
const errorCode = require('../proxy/ServerStatusTars').LifeService.ErrorCode;

var DataHandle = DataHandle || {};
module.exports.DataHandle = DataHandle;

DataHandle.returnData = function(status, data = {}) {
    if (status == errorCode.SUCCESS)
        return this.returnSuccess(status, 'success', data);
    let errmsg = this._getErrMsg(status);
    return this.returnError(status, errmsg);
};

DataHandle.returnSuccess = function(status, errmsg, data = {}) {
    return {
        'status': status,
        'errmsg': errmsg,
          'data':   data,
    };
};

DataHandle.returnError = function(status, errmsg) {
    return {
        'status': status,
        'errmsg': errmsg,
    };
};

DataHandle._getErrMsg = function(errCode) {
    switch(errCode) {
        case errorCode.USEREXIST:
            return "User exist";
        case errorCode.PHONEEXIST:
            return "Phone number exist";
        case errorCode.CLUBEXIST:
            return "Club exist";
        case errorCode.MANAGEREXIST:
            return "Manager exist";
        case errorCode.USERAPPLIED:
            return "User has applied";
        case errorCode.ACTIVITYEXIST:
            return "Activity exist";
        case errorCode.RECORDEXIST:
            return "User has already applied activity";
        case errorCode.USERNOTEXIST:
            return "User does not exist";
        case errorCode.CLUBNOTEXIST:
            return "Club does not exist";
        case errorCode.MANAGERNOTEXIST:
            return "Manager does not exist";
        case errorCode.ACTIVITYNOTEXIST:
            return "Activity does not exist";
        case errorCode.APPLYNOTEXIST:
            return "Application for club does not exist";
        case errorCode.RECORDNOTEXIST:
            return "Activity record does not exist";
        case errorCode.SERVERERROR:
            return "Server ERROR";
        default:
            return "Unknow ERROR";
    }
};