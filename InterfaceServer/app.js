// const https = require('https');
const Koa     = require('koa');
const router  = require('koa-router')();
const koaBody = require('koa-bodyparser');

// Tars工具
const Tars = require("@tars/rpc").client;

// 引入tars
const UserInfoServicePrx = require("./UserInfoServiceProxy");
const DataServicePrx     = require("./DataServiceProxy");
const DataServiceTars    = require("./DataServiceTars");

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
        const prx = Tars.stringToProxy(UserInfoServicePrx.LifeService.UserInfoServiceProxy, userInfoObjName);
        
        let result = await prx.SignIn(wx_id);
        let info = result.response.arguments.sRsp;
        ctx.body = info;

    } catch(e) {
        console.log(e);
        ctx.body = 'error';
    }
})

// 测试
.get('/test', async ctx => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx.LifeService.UserInfoServiceProxy, userInfoObjName);

        const result = await prx.Test();
        let testStr = result.response.arguments.TestStr;

        ctx.body = testStr;
    }
    catch(e) {
        console.log(e);
        ctx.body = "Error: \n" + e;
    }
})

// 获取用户权限组列表
.get('/getGroupList', async ctx => {
    try {
        const prx = Tars.stringToProxy(UserInfoServicePrx.LifeService.UserInfoServiceProxy, userInfoObjName);

        const result = await prx.GetGroupList();
        let groupInfo = result.response.arguments.groupInfo;
        let info = JSON.stringify(groupInfo.value);
        ctx.body = info;
    }
    catch(e) {
        console.log(e);
        ctx.body = 'Error: \n' + e;
    }
})

// 测试数据层接口
.get('/hasUser', async ctx => {
    let {wx_id} = ctx.query;
    try {
        const prx = Tars.stringToProxy(DataServicePrx.LifeService.DataServiceProxy, dataServiceObjName);

        let result = await prx.hasUser(wx_id);
        let userExist = result.response.arguments.sRsp;
        var info = {};
        info["hasUser"] = userExist;
        ctx.body = info;
    } catch(e) {
        console.log(e);
        ctx.body = "Error: \n" + e;
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
        const prx = Tars.stringToProxy(UserInfoServicePrx.LifeService.UserInfoServiceProxy, userInfoObjName);
        
        let result = await prx.SignUp(wx_id, userInfo);
        let info = result.response.arguments.retCode;
        ctx.body = info;
    }
    catch(e) {
        console.log(e);
        ctx.body = 'error';
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
