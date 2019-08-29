// const https = require('https');
const Koa     = require('koa');
const koaBody = require('koa-bodyparser');

// 创建KOA实例
const app = new Koa();

// 拉取配置IP和端口
const hostname = process.env.IP || '127.0.0.1';
const port = process.env.PORT || 8888;

app.use(koaBody({
    extendTypes: {
        json: ['text/xml']
    }
}));

// 加载api路由
apiRouter = require('./router')
app.use(apiRouter.routes());

// 启动服务
app.host = hostname;
app.port = port;

const server = app.listen(app.port, app.host, () => {
    console.log('Koa server listening on %s %d', server.address().address, server.address().port);
});
