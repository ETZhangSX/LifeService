// Tars工具
const Tars = require("@tars/rpc").client;

const UserInfoServicePrx = require("../proxy/UserInfoServiceProxy").LifeService.UserInfoServiceProxy;
const DataServiceTars    = require("../proxy/DataServiceTars");
const ErrorCode          = require("../proxy/ServerStatusTars").LifeService.ErrorCode;
const userInfoObjName    = "LifeService.UserInfoServer.UserInfoServiceObj";
// 引入util工具
const DataHandle = require('../tools/util').DataHandle;

const UserInfoServer = {};

UserInfoServer.test = async ctx => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);

        const result = await prx.Test();
        let testStr = result.response.arguments.testStr;

        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {testStr});
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.signIn = async (ctx) => {
    let {wx_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result = await prx.SignIn(wx_id);
        let userInfo = result.response.arguments.userInfo;
        ctx.body = DataHandle.returnData(result.response.arguments.errCode, userInfo.toObject());

    } catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.getGroupList = async (ctx) => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);

        let result    = await prx.GetGroupList();
        let groupInfo = result.response.arguments.groupInfo;
        
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, groupInfo.toObject());
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.isClubManager = async (ctx) => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result        = await prx.IsClubManager(wx_id, club_id);
        let isClubManager = result.response.arguments.isClubManager;

        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            isClubManager,
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.isInClub = async (ctx) => {
    const {
        wx_id,
        club_id,
        just_in_club,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result   = await prx.IsInClub(wx_id, club_id, just_in_club);
        let isInClub = result.response.arguments.isIn;

        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            isInClub,
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.isAppliedActivity = async (ctx) => {
    const {
        wx_id,
        activity_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result    = await prx.IsAppliedActivity(wx_id, activity_id);
        let isApplied = result.response.arguments.isApplied;
        
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            isApplied,
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.signUp = async (ctx) => {
    const {
        wx_id,
        name,
        phone,
        gender,
        avatar_url,
    } = ctx.request.body;

    const userInfo = new DataServiceTars.LifeService.UserInfo();

    userInfo.readFromObject({
        name,
        phone,
        gender,
        avatar_url
    });

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result = await prx.SignUp(wx_id, userInfo);
        ctx.body = DataHandle.returnData(result.response.arguments.errCode)
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

UserInfoServer.hasPhone = async (ctx) => {
    let {
        phone
    } = ctx.query;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);

        let result = await prx.HasPhone(phone);
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            'phoneExist': result.response.arguments.phoneExist,
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

module.exports = UserInfoServer;