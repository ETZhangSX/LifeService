const WeixinAPI          = require('../servers/WeixinAPI');
const UserInfoServer     = require('../servers/UserInfoServer');
const ClubActivityServer = require('../servers/ClubActivityServer');
const MessageWallServer  = require('../servers/MessageWallServer');

const apiConf = [
    //WeixinAPI
    ['get' , '/getOpenId'        , WeixinAPI.getOpenId],
    //用户服务接口
    ['get' , '/test'             , UserInfoServer.test],
    ['get' , '/signIn'           , UserInfoServer.signIn],
    ['get' , '/getGroupList'     , UserInfoServer.getGroupList],
    ['post', '/isClubManager'    , UserInfoServer.isClubManager],
    ['post', '/isInClub'         , UserInfoServer.isInClub],
    ['post', '/isAppliedActivity', UserInfoServer.isAppliedActivity],
    ['post', '/signUp'           , UserInfoServer.signUp],
    //社团活动服务接口
    ['post', '/createClubManager', ClubActivityServer.createClubManager],
    ['post', '/createClub'       , ClubActivityServer.createClub],
    ['get' , '/getClubList'      , ClubActivityServer.getClubList],
    ['post', '/applyForClub'     , ClubActivityServer.applyForClub],
    ['post', '/createActivity'   , ClubActivityServer.createActivity],
    ['get' , '/getActivityList'  , ClubActivityServer.getActivityList],
    ['get' , '/getActivityDetail', ClubActivityServer.getActivityDetail],
    ['post', '/applyForActivity' , ClubActivityServer.applyForActivity],
    //表白墙服务接口
    ['post', '/postMessage'      , MessageWallServer.postMessage],
    ['post', '/getMessageList'   , MessageWallServer.getMessageList],
    ['post', '/addLike'          , MessageWallServer.addLike],
    ['post', '/getLike'          , MessageWallServer.getLike],
];

module.exports = apiConf;