const apiConf = require('./routerConf');
const Router = require('koa-router');

//获取路由
const getRouter = (router, routerConf) => {
    routerConf.forEach(function (conf) {
            var [method, url, controller] = conf;

            //业务逻辑控制器
            router[method](url, async (ctx, next) => {
                    await controller.call({}, ctx);
                    await next();
            });

    });
};

const apiRouter = new Router();
getRouter(apiRouter, apiConf);

module.exports = apiRouter;