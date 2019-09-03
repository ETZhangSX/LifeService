const TarsConfig = require('@tars/config');
// 实例化
var config = new TarsConfig();

const appConf = {
    crt_path: '',
    key_path: '',
    app_id: '',
    app_secret: '',
};

// 拉取配置
config.loadConfig("LifeService.MessageWallServer.conf", {format: config.FORMAT.JSON}).then(function(data) {
    appConf.crt_path   = data.crt_path;
    appConf.key_path   = data.key_path;
    appConf.app_id     = data.app_id;
    appConf.app_secret = data.app_secret;
}, function (err) {
    console.error("loadConfig err", err);
});

module.exports = appConf;