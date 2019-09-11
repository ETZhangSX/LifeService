const WeixinAPI          = require('../servers/WeixinAPI');
const UserInfoServer     = require('../servers/UserInfoServer');
const ClubActivityServer = require('../servers/ClubActivityServer');
const MessageWallServer  = require('../servers/MessageWallServer');

const apiConf = [
    //WeixinAPI
    ['get' , '/getOpenId'          , WeixinAPI.getOpenId],
    //用户服务接口
    ['get' , '/test'               , UserInfoServer.test],
    ['get' , '/signIn'             , UserInfoServer.signIn],
    ['get' , '/getGroupList'       , UserInfoServer.getGroupList],
    ['post', '/isClubManager'      , UserInfoServer.isClubManager],
    ['post', '/isInClub'           , UserInfoServer.isInClub],
    ['post', '/isAppliedActivity'  , UserInfoServer.isAppliedActivity],
    ['post', '/signUp'             , UserInfoServer.signUp],
    //社团活动服务接口
    ['post', '/createClubManager'  , ClubActivityServer.createClubManager],
    ['post', '/createClub'         , ClubActivityServer.createClub],
    ['get' , '/getClubList'        , ClubActivityServer.getClubList],
    ['post', '/applyForClub'       , ClubActivityServer.applyForClub],
    ['get' , '/getClubMembers'     , ClubActivityServer.getClubMembers],
    ['get' , '/getClubApplications', ClubActivityServer.getClubApplications],
    ['get' , '/getUserApplications', ClubActivityServer.getUserApplications],
    ['post', '/approveApplication' , ClubActivityServer.approveApplication],
    ['post', '/deleteApplication'  , ClubActivityServer.deleteApplication],
    ['post', '/createActivity'     , ClubActivityServer.createActivity],
    ['get' , '/getActivityList'    , ClubActivityServer.getActivityList],
    ['post', '/updateActivityInfo' , ClubActivityServer.updateActivity],
    ['get' , '/getUserActivityList', ClubActivityServer.getUserActivityList],
    ['get' , '/getClubActivityList', ClubActivityServer.getClubActivityList],
    ['post', '/deleteActivity'     , ClubActivityServer.deleteActivity],
    ['get' , '/getActivityDetail'  , ClubActivityServer.getActivityDetail],
    ['get' , '/getActivityParticipate', ClubActivityServer.getActivityParticipate],
    ['post', '/applyForActivity'   , ClubActivityServer.applyForActivity],
    ['post', 'deleteActivityParticipate', ClubActivityServer.deleteActivityParticipate],
    //表白墙服务接口
    ['post', '/postMessage'        , MessageWallServer.postMessage],
    ['post', '/getMessageList'     , MessageWallServer.getMessageList],
    ['post', '/addLike'            , MessageWallServer.addLike],
    ['post', '/getLike'            , MessageWallServer.getLike],
];

module.exports = apiConf;