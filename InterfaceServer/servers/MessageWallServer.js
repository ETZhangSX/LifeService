const Tars = require("@tars/rpc").client;

const MessageWallPrx = require("../proxy/MessageWallProxy").LifeService.MessageWallProxy;
const DataServiceTars = require("../proxy/DataServiceTars");

const messageWallObjName = "LifeService.MessageWallServer.MessageWallObj";

const DataHandle = require("../tools/util").DataHandle;

const MessageWallServer = {};

MessageWallServer.postMessage = async (ctx) => {
    const {
        user_id,
        content,
        anonymous,
    } = ctx.request.body;

    const message = new DataServiceTars.LifeService.Message();
    message.readFromObject({
        user_id,
        content,
        anonymous,
    });

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);

        let result = await prx.PostMessage(message);

        ctx.body = DataHandle.returnData(200, 'success');
    }
    catch(e){
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

MessageWallServer.getMessageList = async (ctx) => {
    const {
        index,
        date,
        wx_id,
    } = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);

        let result = await prx.GetMessageList(index, date, wx_id);

        ctx.body = DataHandle.returnData(200, 'success', {
            'next_index': result.response.arguments.NextIndex,
            'message_list': result.response.arguments.MsgList,
        });
    }
    catch(e) {
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

MessageWallServer.addLike = async (ctx) => {
    const {message_id} = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);

        let result = await prx.AddLike(message_id);

        ctx.body = DataHandle.returnData(result.response.return, 'success');
    }
    catch(e) {
        ctx.body = DataHandle.returnError(400, e.message);
    }
};

MessageWallServer.getLike = async (ctx) => {
    const {message_id} = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);

        let result = await prx.GetLike(message_id);

        ctx.body = DataHandle.returnData(200, 'success', {
            'like_count': result.response.arguments.LikeCount,
        });
    }
    catch {
        ctx.body = DataHandle.returnError(400, e.message);
    }
}

module.exports = MessageWallServer;