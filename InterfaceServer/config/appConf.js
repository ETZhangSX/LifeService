const TarsConfig = require('@tars/config');

const appConf = {
    crt_path: '/home/1_www.etzhang.xyz_bundle.crt',
    key_path: '/home/2_www.etzhang.xyz.key',
    app_id: '',
    app_secret: '',
    // 拉取配置
    loadConfig: function() {
        var that = this;
        // 实例化
        var config = new TarsConfig();
        
        config.loadConfig("LifeService.MessageWallServer.conf", {format: config.FORMAT.JSON})
        .then(function(data) {
            that.crt_path   = data.crt_path;
            that.key_path   = data.key_path;
            that.app_id     = data.app_id;
            that.app_secret = data.app_secret;
            console.log(data);
        }, function (err) {
            console.error("loadConfig err", err);
        });
    }
};

module.exports = appConf;