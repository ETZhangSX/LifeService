// **********************************************************************
// Parsed By TarsParser(1.1.0), Generated By tars2node(20190529)
// TarsParser Maintained By <TARS> and tars2node Maintained By <superzheng>
// Generated from "UserInfoService.tars" by Client Mode
// **********************************************************************

/* eslint-disable */

"use strict";

var TarsStream = require("@tars/stream");
var TarsError  = require("@tars/rpc").error;
var _TARS_MODULE_A_ = require("./DataServiceTars.js");
var _TARS_MODULE_B_ = require("./ServerStatusTars.js");

var _makeError = function (data, message, type) {
    var error = new Error(message || "");
    error.request = data.request;
    error.response = {
        "costtime" : data.request.costtime
    };
    if (type === TarsError.CLIENT.DECODE_ERROR) {
        error.name = "DECODE_ERROR";
        error.response.error = {
            "code" : type,
            "message" : message
        };
    } else {
        error.name = "RPC_ERROR";
        error.response.error = data.error;
    }
    return error;
};

var LifeService = LifeService || {};
module.exports.LifeService = LifeService;

LifeService.UserInfoServiceProxy = function () {
    this._name    = undefined;
    this._worker  = undefined;
};

LifeService.UserInfoServiceProxy.prototype.setTimeout = function (iTimeout) {
    this._worker.timeout = iTimeout;
};

LifeService.UserInfoServiceProxy.prototype.getTimeout = function () {
    return this._worker.timeout;
};

LifeService.UserInfoServiceProxy.prototype.setVersion = function (iVersion) {
    this._worker.version = iVersion;
};

LifeService.UserInfoServiceProxy.prototype.getVersion = function () {
    return this._worker.version;
};

var __LifeService_UserInfoService$GetGroupList$IF = {
    "name" : "GetGroupList",
    "return" : "int32",
    "arguments" : [{
        "name" : "groupInfo",
        "class" : "map(int32, string)",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$GetGroupList$IE = function () {
    var os = new TarsStream.TarsOutputStream();
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$GetGroupList$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "groupInfo" : is.readMap(1, true, TarsStream.Map(TarsStream.Int32, TarsStream.String))
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$GetGroupList$PE = function (__$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    return tup;
};

var __LifeService_UserInfoService$GetGroupList$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "groupInfo" : tup.readMap("groupInfo", TarsStream.Map(TarsStream.Int32, TarsStream.String))
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$GetGroupList$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::GetGroupList failed");
};

LifeService.UserInfoServiceProxy.prototype.GetGroupList = function () {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("GetGroupList", __LifeService_UserInfoService$GetGroupList$PE(version), arguments[arguments.length - 1], __LifeService_UserInfoService$GetGroupList$IF).then(__LifeService_UserInfoService$GetGroupList$PD, __LifeService_UserInfoService$GetGroupList$ER);
    } else {
        return this._worker.tars_invoke("GetGroupList", __LifeService_UserInfoService$GetGroupList$IE(), arguments[arguments.length - 1], __LifeService_UserInfoService$GetGroupList$IF).then(__LifeService_UserInfoService$GetGroupList$ID, __LifeService_UserInfoService$GetGroupList$ER);
    }
};
LifeService.UserInfoServiceProxy.GetGroupList = __LifeService_UserInfoService$GetGroupList$IF;

var __LifeService_UserInfoService$HasPhone$IF = {
    "name" : "HasPhone",
    "return" : "int32",
    "arguments" : [{
        "name" : "phone",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "phoneExist",
        "class" : "bool",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$HasPhone$IE = function (phone) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, phone);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$HasPhone$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "phoneExist" : is.readBoolean(2, true, true)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$HasPhone$PE = function (phone, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("phone", phone);
    return tup;
};

var __LifeService_UserInfoService$HasPhone$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "phoneExist" : tup.readBoolean("phoneExist")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$HasPhone$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::HasPhone failed");
};

LifeService.UserInfoServiceProxy.prototype.HasPhone = function (phone) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("HasPhone", __LifeService_UserInfoService$HasPhone$PE(phone, version), arguments[arguments.length - 1], __LifeService_UserInfoService$HasPhone$IF).then(__LifeService_UserInfoService$HasPhone$PD, __LifeService_UserInfoService$HasPhone$ER);
    } else {
        return this._worker.tars_invoke("HasPhone", __LifeService_UserInfoService$HasPhone$IE(phone), arguments[arguments.length - 1], __LifeService_UserInfoService$HasPhone$IF).then(__LifeService_UserInfoService$HasPhone$ID, __LifeService_UserInfoService$HasPhone$ER);
    }
};
LifeService.UserInfoServiceProxy.HasPhone = __LifeService_UserInfoService$HasPhone$IF;

var __LifeService_UserInfoService$IsAppliedActivity$IF = {
    "name" : "IsAppliedActivity",
    "return" : "int32",
    "arguments" : [{
        "name" : "wxId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "activityId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "isApplied",
        "class" : "bool",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$IsAppliedActivity$IE = function (wxId, activityId) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, wxId);
    os.writeString(2, activityId);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$IsAppliedActivity$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "isApplied" : is.readBoolean(3, true, true)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsAppliedActivity$PE = function (wxId, activityId, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("wxId", wxId);
    tup.writeString("activityId", activityId);
    return tup;
};

var __LifeService_UserInfoService$IsAppliedActivity$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "isApplied" : tup.readBoolean("isApplied")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsAppliedActivity$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::IsAppliedActivity failed");
};

LifeService.UserInfoServiceProxy.prototype.IsAppliedActivity = function (wxId, activityId) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("IsAppliedActivity", __LifeService_UserInfoService$IsAppliedActivity$PE(wxId, activityId, version), arguments[arguments.length - 1], __LifeService_UserInfoService$IsAppliedActivity$IF).then(__LifeService_UserInfoService$IsAppliedActivity$PD, __LifeService_UserInfoService$IsAppliedActivity$ER);
    } else {
        return this._worker.tars_invoke("IsAppliedActivity", __LifeService_UserInfoService$IsAppliedActivity$IE(wxId, activityId), arguments[arguments.length - 1], __LifeService_UserInfoService$IsAppliedActivity$IF).then(__LifeService_UserInfoService$IsAppliedActivity$ID, __LifeService_UserInfoService$IsAppliedActivity$ER);
    }
};
LifeService.UserInfoServiceProxy.IsAppliedActivity = __LifeService_UserInfoService$IsAppliedActivity$IF;

var __LifeService_UserInfoService$IsClubManager$IF = {
    "name" : "IsClubManager",
    "return" : "int32",
    "arguments" : [{
        "name" : "wxId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "clubId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "isClubManager",
        "class" : "bool",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$IsClubManager$IE = function (wxId, clubId) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, wxId);
    os.writeString(2, clubId);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$IsClubManager$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "isClubManager" : is.readBoolean(3, true, true)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsClubManager$PE = function (wxId, clubId, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("wxId", wxId);
    tup.writeString("clubId", clubId);
    return tup;
};

var __LifeService_UserInfoService$IsClubManager$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "isClubManager" : tup.readBoolean("isClubManager")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsClubManager$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::IsClubManager failed");
};

LifeService.UserInfoServiceProxy.prototype.IsClubManager = function (wxId, clubId) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("IsClubManager", __LifeService_UserInfoService$IsClubManager$PE(wxId, clubId, version), arguments[arguments.length - 1], __LifeService_UserInfoService$IsClubManager$IF).then(__LifeService_UserInfoService$IsClubManager$PD, __LifeService_UserInfoService$IsClubManager$ER);
    } else {
        return this._worker.tars_invoke("IsClubManager", __LifeService_UserInfoService$IsClubManager$IE(wxId, clubId), arguments[arguments.length - 1], __LifeService_UserInfoService$IsClubManager$IF).then(__LifeService_UserInfoService$IsClubManager$ID, __LifeService_UserInfoService$IsClubManager$ER);
    }
};
LifeService.UserInfoServiceProxy.IsClubManager = __LifeService_UserInfoService$IsClubManager$IF;

var __LifeService_UserInfoService$IsInClub$IF = {
    "name" : "IsInClub",
    "return" : "int32",
    "arguments" : [{
        "name" : "wxId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "clubId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "justInClub",
        "class" : "bool",
        "direction" : "in"
    }, {
        "name" : "isIn",
        "class" : "bool",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$IsInClub$IE = function (wxId, clubId, justInClub) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, wxId);
    os.writeString(2, clubId);
    os.writeBoolean(3, justInClub);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$IsInClub$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "isIn" : is.readBoolean(4, true, true)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsInClub$PE = function (wxId, clubId, justInClub, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("wxId", wxId);
    tup.writeString("clubId", clubId);
    tup.writeBoolean("justInClub", justInClub);
    return tup;
};

var __LifeService_UserInfoService$IsInClub$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "isIn" : tup.readBoolean("isIn")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$IsInClub$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::IsInClub failed");
};

LifeService.UserInfoServiceProxy.prototype.IsInClub = function (wxId, clubId, justInClub) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("IsInClub", __LifeService_UserInfoService$IsInClub$PE(wxId, clubId, justInClub, version), arguments[arguments.length - 1], __LifeService_UserInfoService$IsInClub$IF).then(__LifeService_UserInfoService$IsInClub$PD, __LifeService_UserInfoService$IsInClub$ER);
    } else {
        return this._worker.tars_invoke("IsInClub", __LifeService_UserInfoService$IsInClub$IE(wxId, clubId, justInClub), arguments[arguments.length - 1], __LifeService_UserInfoService$IsInClub$IF).then(__LifeService_UserInfoService$IsInClub$ID, __LifeService_UserInfoService$IsInClub$ER);
    }
};
LifeService.UserInfoServiceProxy.IsInClub = __LifeService_UserInfoService$IsInClub$IF;

var __LifeService_UserInfoService$SignIn$IF = {
    "name" : "SignIn",
    "return" : "int32",
    "arguments" : [{
        "name" : "wxId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "userInfo",
        "class" : "LifeService.UserInfo",
        "direction" : "out"
    }, {
        "name" : "errCode",
        "class" : "int32",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$SignIn$IE = function (wxId) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, wxId);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$SignIn$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "userInfo" : is.readStruct(2, true, _TARS_MODULE_A_.LifeService.UserInfo),
                    "errCode" : is.readInt32(3, true, _TARS_MODULE_B_.LifeService.ErrorCode.SUCCESS)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$SignIn$PE = function (wxId, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("wxId", wxId);
    return tup;
};

var __LifeService_UserInfoService$SignIn$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "userInfo" : tup.readStruct("userInfo", _TARS_MODULE_A_.LifeService.UserInfo),
                    "errCode" : tup.readInt32("errCode")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$SignIn$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::SignIn failed");
};

LifeService.UserInfoServiceProxy.prototype.SignIn = function (wxId) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("SignIn", __LifeService_UserInfoService$SignIn$PE(wxId, version), arguments[arguments.length - 1], __LifeService_UserInfoService$SignIn$IF).then(__LifeService_UserInfoService$SignIn$PD, __LifeService_UserInfoService$SignIn$ER);
    } else {
        return this._worker.tars_invoke("SignIn", __LifeService_UserInfoService$SignIn$IE(wxId), arguments[arguments.length - 1], __LifeService_UserInfoService$SignIn$IF).then(__LifeService_UserInfoService$SignIn$ID, __LifeService_UserInfoService$SignIn$ER);
    }
};
LifeService.UserInfoServiceProxy.SignIn = __LifeService_UserInfoService$SignIn$IF;

var __LifeService_UserInfoService$SignUp$IF = {
    "name" : "SignUp",
    "return" : "int32",
    "arguments" : [{
        "name" : "wxId",
        "class" : "string",
        "direction" : "in"
    }, {
        "name" : "userInfo",
        "class" : "LifeService.UserInfo",
        "direction" : "in"
    }, {
        "name" : "errCode",
        "class" : "int32",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$SignUp$IE = function (wxId, userInfo) {
    var os = new TarsStream.TarsOutputStream();
    os.writeString(1, wxId);
    os.writeStruct(2, userInfo);
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$SignUp$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "errCode" : is.readInt32(3, true, _TARS_MODULE_B_.LifeService.ErrorCode.SUCCESS)
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$SignUp$PE = function (wxId, userInfo, __$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    tup.writeString("wxId", wxId);
    tup.writeStruct("userInfo", userInfo);
    return tup;
};

var __LifeService_UserInfoService$SignUp$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "errCode" : tup.readInt32("errCode")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$SignUp$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::SignUp failed");
};

LifeService.UserInfoServiceProxy.prototype.SignUp = function (wxId, userInfo) {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("SignUp", __LifeService_UserInfoService$SignUp$PE(wxId, userInfo, version), arguments[arguments.length - 1], __LifeService_UserInfoService$SignUp$IF).then(__LifeService_UserInfoService$SignUp$PD, __LifeService_UserInfoService$SignUp$ER);
    } else {
        return this._worker.tars_invoke("SignUp", __LifeService_UserInfoService$SignUp$IE(wxId, userInfo), arguments[arguments.length - 1], __LifeService_UserInfoService$SignUp$IF).then(__LifeService_UserInfoService$SignUp$ID, __LifeService_UserInfoService$SignUp$ER);
    }
};
LifeService.UserInfoServiceProxy.SignUp = __LifeService_UserInfoService$SignUp$IF;

var __LifeService_UserInfoService$Test$IF = {
    "name" : "Test",
    "return" : "int32",
    "arguments" : [{
        "name" : "testStr",
        "class" : "string",
        "direction" : "out"
    }]
};

var __LifeService_UserInfoService$Test$IE = function () {
    var os = new TarsStream.TarsOutputStream();
    return os.getBinBuffer();
};

var __LifeService_UserInfoService$Test$ID = function (data) {
    try {
        var is = new TarsStream.TarsInputStream(data.response.sBuffer);
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : is.readInt32(0, true, 0),
                "arguments" : {
                    "testStr" : is.readString(1, true, "")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$Test$PE = function (__$PROTOCOL$VERSION) {
    var tup = new TarsStream.UniAttribute();
    tup.tupVersion = __$PROTOCOL$VERSION;
    return tup;
};

var __LifeService_UserInfoService$Test$PD = function (data) {
    try {
        var tup = data.response.tup;
        return {
            "request" : data.request,
            "response" : {
                "costtime" : data.request.costtime,
                "return" : tup.readInt32("", 0),
                "arguments" : {
                    "testStr" : tup.readString("testStr")
                }
            }
        };
    } catch (e) {
        throw _makeError(data, e.message, TarsError.CLIENT.DECODE_ERROR);
    }
};

var __LifeService_UserInfoService$Test$ER = function (data) {
    throw _makeError(data, "Call UserInfoService::Test failed");
};

LifeService.UserInfoServiceProxy.prototype.Test = function () {
    var version = this._worker.version;
    if (version === TarsStream.Tup.TUP_SIMPLE || version === TarsStream.Tup.TUP_COMPLEX) {
        return this._worker.tup_invoke("Test", __LifeService_UserInfoService$Test$PE(version), arguments[arguments.length - 1], __LifeService_UserInfoService$Test$IF).then(__LifeService_UserInfoService$Test$PD, __LifeService_UserInfoService$Test$ER);
    } else {
        return this._worker.tars_invoke("Test", __LifeService_UserInfoService$Test$IE(), arguments[arguments.length - 1], __LifeService_UserInfoService$Test$IF).then(__LifeService_UserInfoService$Test$ID, __LifeService_UserInfoService$Test$ER);
    }
};
LifeService.UserInfoServiceProxy.Test = __LifeService_UserInfoService$Test$IF;



