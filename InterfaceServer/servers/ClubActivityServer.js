// Tars工具
const Tars = require("@tars/rpc").client;
// 引入tars代理
const ClubActivityManangerPrx = require("../proxy/ClubActivityManagerProxy").LifeService.ClubActivityManagerProxy;
const DataServiceTars         = require("../proxy/DataServiceTars");
// 服务对象名
const clubActivityObjName = "LifeService.ClubActivityServer.ClubActivityManagerObj";
// 引入util工具
const DataHandle = require('../tools/util').DataHandle;


const ClubActivityServer = {};


// 创建社团管理员
ClubActivityServer.createClubManager = async (ctx) => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.CreateClubManager(wx_id, club_id);
        
        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success');
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 创建社团
ClubActivityServer.createClub = async (ctx) => {
    const {
        name,
        chairman,
        introduction,
    } = ctx.request.body;

    const clubInfo = new DataServiceTars.LifeService.ClubInfo();

    clubInfo.readFromObject({
        name,
        chairman,
        introduction,
    });

    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.CreateClub(clubInfo);
        
        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success');
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取社团列表
ClubActivityServer.getClubList = async (ctx) => {
    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.GetClubList();

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success', result.response.arguments.clubInfoList.toObject());
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 申请社团
ClubActivityServer.applyForClub = async (ctx) => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.ApplyForClub(wx_id, club_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success');
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 创建活动
ClubActivityServer.createActivity = async (ctx) => {
    const {
        name,
        sponsor,
        club_id,
        start_time,
        stop_time,
        registry_start_time,
        registry_stop_time,
        content,
    } = ctx.request.body;
    
    const activityInfo = new DataServiceTars.LifeService.ActivityInfo();
    activityInfo.readFromObject({
        name,
        sponsor,
        club_id,
        start_time,
        stop_time,
        registry_start_time,
        registry_stop_time,
        content,
    });

    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.CreateActivity(sponsor, activityInfo);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success');
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取活动列表
ClubActivityServer.getActivityList = async (ctx) => {
    let {index} = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);
        
        let result = await prx.GetActivityList(index);

        ctx.body = DataHandle.returnData(200, 'success', {
            'next_index': result.response.arguments.nextIndex,
            'activity_list' : result.response.arguments.activityList,
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取活动详情
ClubActivityServer.getActivityDetail = async (ctx) => {
    let {activity_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.GetActivityDetail(activity_id);

        ctx.body = DataHandle.returnData(200, 'success', result.response.arguments.activityInfo.toObject());
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 申请活动
ClubActivityServer.applyForActivity = async (ctx) => {
    const {
        wx_id,
        activity_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManangerPrx, clubActivityObjName);

        let result = await prx.ApplyForActivity(wx_id, activity_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, 'success');
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

module.exports = ClubActivityServer;