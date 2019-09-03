const Koa     = require('koa');
const koaBody = require('koa-bodyparser');
const https   = require('https');
const fs      = require('fs');
const appConf = require('./config/appConf');

// 证书密钥路径
var crt_path = appConf.crt_path;
var key_path = appConf.key_path;

// 读取证书密钥
var crt = fs.readFileSync(crt_path, 'utf-8');
var key = fs.readFileSync(key_path, 'utf-8');
const options = {key: key, cert: crt};

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

// const server = app.listen(app.port, app.host, () => {
//     console.log('Koa server listening on %s %d', server.address().address, server.address().port);
// });

const https_server = https.createServer(options, app.callback()).listen(app.port, app.host, () => {
    console.log('Koa server listening on %s %d', https_server.address().address, https_server.address().port);
});