const request = require('request');
const appConf = require('../config/appConf')

const WeixinAPI = {};

WeixinAPI.getOpenId = async (ctx) => {
    let {js_code} = ctx.query;

    var params = 'appid=' + appConf.app_id + 
               '&secret=' + appConf.app_secret + 
              '&js_code=' + js_code + 
              '&grant_type=authorization_code';

    var url = 'https://api.weixin.qq.com/sns/jscode2session?' + params;
    
    
    request(url, function (error, response, data) {
        if (!error && response.statusCode == 200) {
            ctx.body = data;
        }
        else {
            ctx.body = {
                errcode: 404,
                errmsg: "request weixin api failed",
            };
        }
    });
}

module.exports = WeixinAPI;