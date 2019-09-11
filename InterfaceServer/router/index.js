const apiConf = require('./routerConf');
const Router = require('koa-router');

//获取路由
const getRouter = (router, routerConf) => {
    routerConf.forEach(function (conf) {
            var [method, url, server] = conf;

            //业务逻辑控制器
            router[method](url, async (ctx, next) => {
                    await server.call({}, ctx);
                    await next();
            });

    });
};
//创建路由对象
const apiRouter = new Router();
//加载所有API路由
getRouter(apiRouter, apiConf);

module.exports = apiRouter;