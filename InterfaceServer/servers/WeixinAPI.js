const request    = require('request');
const util       = require('util');
const DataHandle = require('../tools/util').DataHandle;
const appConf    = require('../config/appConf');

const WeixinAPI = {};

// Promise化, 使request能够同步调用
const getPromise = util.promisify(request.get);

WeixinAPI.getOpenId = async (ctx) => {
    let {js_code} = ctx.query;

    let params = 'appid=' + appConf.app_id +
               '&secret=' + appConf.app_secret + 
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
        ctx.body = DataHandle.returnError('400', e.message);
    }
};

module.exports = WeixinAPI;