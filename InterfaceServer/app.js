// const https = require('https');
const Koa     = require('koa');
const router  = require('koa-router')();
const koaBody = require('koa-bodyparser');

// Tars工具
const Tars = require("@tars/rpc").client;

// 引入tars代理
const UserInfoServicePrx = require("./UserInfoServiceProxy").LifeService.UserInfoServiceProxy;
const DataServicePrx     = require("./DataServiceProxy").LifeService.DataServiceProxy;
const DataServiceTars    = require("./DataServiceTars");

// 引入util工具
const DataHandle = require('./util').DataHandle;

// 创建KOA实例
const app = new Koa();

// 调用的服务Obj
const dataServiceObjName = "LifeService.DataServer.DataServiceObj";
const userInfoObjName    = "LifeService.UserInfoServer.UserInfoServiceObj";

// 拉取配置IP和端口
const hostname = process.env.IP || '127.0.0.1';
const port = process.env.PORT || 8888;

app.use(koaBody({
    extendTypes: {
        json: ['text/xml']
    }
}));

// 登录，若用户不存在返回错误
router.get('/signIn', async ctx => {
    let {wx_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result = await prx.SignIn(wx_id);
        let userInfo = result.response.arguments.sRsp;
        ctx.body = DataHandle.returnData(200, 'success', userInfo.toObject());

    } catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 测试接口
.get('/test', async ctx => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);

        const result = await prx.Test();
        let testStr = result.response.arguments.testStr;

        ctx.body = DataHandle.returnData(200, 'success', testStr);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 获取用户权限组列表
.get('/getGroupList', async ctx => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);

        const result = await prx.GetGroupList();
        let groupInfo = result.response.arguments.groupInfo;
        ctx.body = DataHandle.returnData(200, 'success', groupInfo.toObject());
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 测试数据层接口
.get('/test/hasUser', async ctx => {
    let {wx_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(DataServicePrx, dataServiceObjName);

        let result = await prx.hasUser(wx_id);
        let userExist = result.response.arguments.sRsp;
        var info = {};
        info["hasUser"] = userExist;
        ctx.body = info;
    } catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 判断是否社团管理员
.post('/isClubManager', async ctx => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        let result = await prx.IsClubManager(wx_id, club_id);
        ctx.body = DataHandle.returnData(200, 'success', result.response.arguments.isClubManager);
    }
    catch(e) {
        console.log(e)
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 判断是否在社团中
// @param just_in_club 决定判断类型 just_in_club? 判断用户是否参加了社团:判断用户是否申请了社团(申请未审核通过)
.post('/isInClub', async ctx => {
    const {
        wx_id,
        club_id,
        just_in_club,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        let result = await prx.IsInClub(wx_id, club_id, just_in_club);
        ctx.body = DataHandle.returnData(200, 'success', result.response.arguments.isIn);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 判断用户是否已报名活动
.post('/isAppliedActivity', async ctx => {
    const {
        wx_id,
        club_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        let result = await prx.IsAppliedActivity(wx_id, club_id);
        ctx.body = DataHandle.returnData(200, 'success', result.response.arguments.isApplied);
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
})

// 注册用户
.post('/signUp', async ctx => {
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
    })

    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx, userInfoObjName);
        
        let result = await prx.SignUp(wx_id, userInfo);
        ctx.body = DataHandle.returnData(result.response.arguments.retCode, 'success')
    }
    catch(e) {
        console.log(e);
        ctx.body = DataHandle.returnError(400, e);
    }
});

// 加载路由
app.use(router.routes());

// 启动服务
app.host = hostname;
app.port = port;

const server = app.listen(app.port, app.host, () => {
    console.log('Koa server listening on %s %d', server.address().address, server.address().port);
});
