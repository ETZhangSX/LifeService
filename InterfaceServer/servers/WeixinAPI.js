const request    = require('request');
const util       = require('util');
const DataHandle = require('../tools/util').DataHandle;
const ErrorCode  = require("../proxy/ServerStatusTars").LifeService.ErrorCode;

const WeixinAPI = {};

// Promise化, 使request能够同步调用
const getPromise = util.promisify(request.get);

// 获取微信OpenId
WeixinAPI.getOpenId = async (ctx) => {
    let {
        appid,
        secret,
        js_code,
    } = ctx.query;

    let params = 'appid=' + appid +
               '&secret=' + secret + 
              '&js_code=' + js_code + 
              '&grant_type=authorization_code';

    let url = 'https://api.weixin.qq.com/sns/jscode2session?' + params;

    try {
        let result = await getPromise(url);
        console.log(result.body);
        ctx.body = result.body;
    }
    catch(e) {
        console.error(e);
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

module.exports = WeixinAPI;