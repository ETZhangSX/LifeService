const Tars = require("@tars/rpc").client;

const MessageWallPrx = require("../proxy/MessageWallProxy").LifeService.MessageWallProxy;
const DataServiceTars = require("../proxy/DataServiceTars");
const ErrorCode       = require("../proxy/ServerStatusTars").LifeService.ErrorCode;

const messageWallObjName = "LifeService.MessageWallServer.MessageWallObj";
const DataHandle = require("../tools/util").DataHandle;

const MessageWallServer = {};

MessageWallServer.postMessage = async (ctx) => {
    const {
        user_id,
        receiver,
        content,
        anonymous,
    } = ctx.request.body;

    const message = new DataServiceTars.LifeService.Message();
    message.readFromObject({
        user_id,
        receiver,
        content,
        anonymous,
    });

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);
        await prx.PostMessage(message);
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS);
    }
    catch(e){
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
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
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            'next_index': result.response.arguments.NextIndex,
            'message_list': result.response.arguments.MsgList.toObject(),
        });
    }
    catch(e) {
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

MessageWallServer.addLike = async (ctx) => {
    const {message_id} = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);
        await prx.AddLike(message_id);
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS);
    }
    catch(e) {
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

MessageWallServer.getLike = async (ctx) => {
    const {message_id} = ctx.request.body;

    try {
        const prx = Tars.stringToProxy(MessageWallPrx, messageWallObjName);
        let result = await prx.GetLike(message_id);
        ctx.body = DataHandle.returnData(ErrorCode.SUCCESS, {
            'like_count': result.response.arguments.LikeCount,
        });
    }
    catch(e) {
        ctx.body = DataHandle.returnError(ErrorCode.SERVERERROR, e.message);
    }
};

module.exports = MessageWallServer;