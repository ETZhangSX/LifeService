// Tars工具
const Tars = require("@tars/rpc").client;
// 引入tars代理
const ClubActivityManagerPrx = require("../proxy/ClubActivityManagerProxy").LifeService.ClubActivityManagerProxy;
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
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.CreateClubManager(wx_id, club_id);
        
        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
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
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.CreateClub(clubInfo);
        
        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取社团列表
ClubActivityServer.getClubList = async (ctx) => {
    let {
        wx_id,
        index,
    } = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetClubList(index, wx_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'club_list' : result.response.arguments.clubInfoList.toObject(),
        });
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
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.ApplyForClub(wx_id, club_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取社团成员
ClubActivityServer.getClubMembers = async (ctx) => {
    let {
        club_id,
        index,
    } = ctx.query;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetClubApply(club_id, index, 1);
        
        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'member_list': result.response.arguments.applyList.toObject(),
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取社团申请
ClubActivityServer.getClubApplications = async (ctx) => {
    let {
        club_id,
        index,
    } = ctx.query;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetClubApply(club_id, index, 0);
        
        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'application_list': result.response.arguments.applyList.toObject(),
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取用户参加的社团
ClubActivityServer.getUserApplications = async (ctx) => {
    let {
        wx_id,
        index,
        apply_status,
    } = ctx.query;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetUserApply(wx_id, index, apply_status);

        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'application_list': result.response.arguments.applyList.toObject(),
        });
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 通过申请
ClubActivityServer.approveApplication = async (ctx) => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.ModifyApplyStatus(wx_id, club_id, 1);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 删除申请
ClubActivityServer.deleteApplication = async (ctx) => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.DeleteApply(wx_id, club_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success)
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
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
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.CreateActivity(sponsor, activityInfo);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
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
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetActivityList(index, "", "");

        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'activity_list' : result.response.arguments.activityList.toObject(),
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 更新活动信息
ClubActivityServer.updateActivity = async (ctx) => {
    const {
        activity_id,
        name,
        start_time,
        stop_time,
        registry_start_time,
        registry_stop_time,
        content,
    } = ctx.request.body;

    const activity_info = new DataServiceTars.LifeService.ActivityInfo();
    activity_info.readFromObject({
        activity_id,
        name,
        start_time,
        stop_time,
        registry_start_time,
        registry_stop_time,
        content,
    });
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.UpdateActivity(activity_info);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
}

// 获取用户报名的活动
ClubActivityServer.getUserActivityList = async (ctx) => {
    let {
        wx_id,
        index,
    } = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetActivityList(index, wx_id, "");

        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'activity_list' : result.response.arguments.activityList.toObject(),
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取社团活动列表
ClubActivityServer.getClubActivityList = async (ctx) => {
    let {
        club_id,
        index,
    } = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetActivityList(index, "", club_id);

        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            'next_index': result.response.arguments.nextIndex,
            'activity_list' : result.response.arguments.activityList.toObject(),
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 删除活动
ClubActivityServer.deleteActivity = async (ctx) => {
    const {activity_id} = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.DeleteActivity(activity_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
}

// 获取活动详情
ClubActivityServer.getActivityDetail = async (ctx) => {
    let {activity_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetActivityDetail(activity_id);

        ctx.body = DataHandle.returnData(200, DataHandle.Success, result.response.arguments.activityInfo.toObject());
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

// 获取活动参与人列表
ClubActivityServer.getActivityParticipate = async (ctx) => {
    let {activity_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.GetActivityParticipate(activity_id);

        ctx.body = DataHandle.returnData(200, DataHandle.Success, {
            "participate_list": result.response.arguments.participateList,
        })
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
}

// 申请活动
ClubActivityServer.applyForActivity = async (ctx) => {
    const {
        wx_id,
        activity_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = await prx.ApplyForActivity(wx_id, activity_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

ClubActivityServer.deleteActivityParticipate = async (ctx) => {
    const {
        activity_id,
        wx_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(ClubActivityManagerPrx, clubActivityObjName);
        let result = prx.DeleteActivityParticipate(activity_id, wx_id);

        ctx.body = DataHandle.returnData(result.response.arguments.RetCode, DataHandle.Success);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e.message);
    }
}

module.exports = ClubActivityServer;