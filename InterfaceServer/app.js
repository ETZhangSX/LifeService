// const https = require('https');
const Koa = require('koa');
const router = require('koa-router')();
const koaBody = require('koa-bodyparser');
const TarsStream = require("@tars/stream");
// Tars工具
const Tars = require("@tars/rpc").client;
// 引入tars
const LifeService = require("./UserInfoServiceProxy").LifeService;
const app = new Koa();
const objName = "LifeService.UserInfoServer.UserInfoServiceObj";
const hostname = '0.0.0.0';
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
        const prx = Tars.stringToProxy(LifeService.UserInfoServiceProxy, objName);
        
        let result = await prx.signIn(wx_id);
        let info = result.response.arguments.sRsp;
        ctx.body = info;

    } catch(e) {
        console.log(e);
        ctx.body = 'error';
    }
})

// 测试
.get('/test', async ctx => {
    var m = new TarsStream.Map(TarsStream.String, TarsStream.String);
    m.put("a1", "value1");
    m.put("a2", "value2");
    ctx.body = m.value;
})

// 获取用户权限组列表
.get('/getGroupList', async ctx => {
    try {
        const prx = Tars.stringToProxy(LifeService.UserInfoServiceProxy, objName);

        let result = await prx.getGroupList();
        let groupinfo = result.response.arguments.groupInfo;
        let info = JSON.stringify(groupInfo.value);
        ctx.body = info;
    }
    catch(e) {
        console.log(e);
        ctx.body = 'error';
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

    const userInfo = new LifeService.UserInfo();

    userInfo.readFromObject({
        name,
        phone,
        gender,
        avatar_url
    })

    try {
        const prx = Tars.stringToProxy(LifeService.UserInfoServiceProxy, objName);
        let result = await prx.signUp(wx_id, userInfo);
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