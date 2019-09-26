# InterfaceServer
## 更新

### 2019.9.25
**更新日志**

新增服务错误码及对应错误情况

### 2019.9.12
**更新日志**

修复若干bug

**更新接口**
* [/getActivityParticipate](#interface-getactivityparticipate)

### 2019.9.11
**新增接口**
* [/getManagerClubList](#interface-getmanagerclublist)
* [/updateActivityInfo](#interface-updateactivityinfo)
* [/getActivityParticipate](#interface-getactivityparticipate)
* [/deleteActivityParticipate](#interface-deleteactivityparticipate)

### 2019.9.10
**更新接口**
* [/getClubList](#interface-getclublist)
* [/postMessage](#interface-postmessage)

**新增接口**
* [/getClubMembers](#interface-getclubmembers)
* [/getClubApplications](#interface-getclubapplications)
* [/getUserApplications](#interface-getuserapplications)
* [/approveApplication](#interface-approveapplication)
* [/deleteApplication](#interface-deleteapplication)
* [/getUserActivityList](#interface-getuseractivitylist)
* [/getClubActivityList](#interface-getclubactivitylist)
* [/deleteActivity](#interface-deleteactivity)

## 接口列表

**[测试接口](#chapter-test)**
- [/test](#interface-test)

**[WeixinAPI](#chapter-weixinapi)**
- [/getOpenId](#interface-getopenid)

**[用户服务接口](#chapter-userinfo)**
- [/signIn](#interface-signin)
- [/getGroupList](#interface-getgrouplist)
- [/isClubManager](#interface-isclubmanager)
- [/isInClub](#interface-isInClub)
- [/isAppliedActivity](#interface-isappliedactivity)
- [/signUp](#interface-signup)

**[社团活动服务接口](#chapter-clubservice)**
- [/createClubManager](#interface-createclubmanager)
- [/createClub](#interface-createclub)
- [/getClubList](#interface-getclublist)
- [/getManagerClubList](#interface-getmanagerclublist)
- [/applyForClub](#interface-applyforclub)
- [/getClubMembers](#interface-getclubmembers)
- [/getClubApplications](#interface-getclubapplications)
- [/getUserApplications](#interface-getuserapplications)
- [/approveApplication](#interface-approveapplication)
- [/deleteApplication](#interface-deleteapplication)
- [/getUserActivityList](#interface-getuseractivitylist)
- [/getClubActivityList](#interface-getclubactivitylist)
- [/deleteActivity](#interface-deleteactivity)
- [/createActivity](#interface-createactivity)
- [/getActivityList](#interface-getactivitylist)
- [/updateActivityInfo](#interface-updateactivityinfo)
- [/getActivityDetail](#interface-getactivitydetail)
- [/getActivityParticipate](#interface-getactivityparticipate)
- [/applyForActivity](#interface-applyforactivity)
- [/deleteActivityParticipate](#interface-deleteactivityparticipate)

**[表白墙服务接口](#chapter-messageservice)**
- [/postMessage](#interface-postmessage)
- [/getMessageList](#interface-getmessagelist)
- [/addLike](#interface-addlike)
- [/getLike](#interface-getlike)

## 状态码
服务返回状态码及可能的错误信息
|**错误码**|**错误信息**|
|-|-|
|200|服务调用成功|
|301001|用户已存在|
|301002|号码已存在|
|301003|社团已存在|
|301004|管理员已存在|
|301005|用户已申请社团|
|301006|活动已存在|
|301007|已报名活动|
|404001|用户不存在|
|404002|社团不存在|
|404003|管理员不存在|
|404004|活动不存在|
|404005|申请不存在|
|404006|报名记录不存在|
|500|服务内部错误|


## 接口详情
##  <a id="chapter-test">测试</a>
### <a id="interface-test"></a>/test
GET

## <a id="chapter-weixinapi">微信API</a>
### <a id="interface-getopenid"></a>/getOpenId
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|js_code|string|小程序前端获取的code|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|openid|string|用户唯一标识|
|session_key|string|会话密钥|
|unionid|string|用户在开放平台的唯一标识符，在满足 UnionID 下发条件的情况下会返回，详见 [UnionID 机制说明](https://developers.weixin.qq.com/miniprogram/dev/framework/open-ability/union-id.html)。|
|errcode|number|错误码|
|errmsg|string|错误信息|

## <a id="chapter-userinfo">用户服务接口</a>
### <a id="interface-signin"></a>/signIn
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|用户基本信息|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|name|string|名字|
|phone|string|手机号|
|gender|string|性别|
|avatar_url|string|头像url|
|registration_time|string|注册时间|
|group|number|用户组id|

### <a id="interface-getgrouplist"></a>/getGroupList
GET
#### 参数
无
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|list<json\>|用户组数据[{group_id, user_type}]|

### <a id="interface-isclubmanager"></a>/isClubManager
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|club_id|string|社团id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|isClubManager|bool|是否为社团管理员|

### <a id="interface-isinclub"></a>/isInClub
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|club_id|string|社团id|
|just_in_club|bool|为true时判断用户是否在社团中;否则判断用户是否申请了该社团，即包括审核中用户
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|isInClub|bool|是否在社团|

### <a id="interface-isappliedactivity"></a>/isAppliedActivity
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|activity_id|string|活动id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|isApplied|bool|是否申请了活动|

### <a id="interface-signup"></a>/signUp
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|name|string|活动id|
|phone|string|手机号|
|gender|string|性别|
|avatar_url|string|头像url|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

## <a id="chapter-clubservice">社团活动服务接口</a>
### <a id="interface-createclubmanager"></a>/createClubManager
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|club_id|string|社团id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-createclub"></a>/createClub
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|name|string|社团名字|
|chairman|string|创建人openid|
|introduction|string|社团简介|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getclublist"></a>/getClubList
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid, 为空表示不筛选社团|
|index|string|索引|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|list|社团列表
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id
|name|string|社团名字
|chairman|string|社团会长openid
|create_time|string|创建时间
|introduction|string|社团简介

### <a id="interface-getmanagerclublist"></a>/getManagerClubList
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid, 为空表示不筛选社团|
|index|string|索引|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|list|社团列表
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id
|name|string|社团名字
|chairman|string|社团会长openid
|create_time|string|创建时间
|introduction|string|社团简介

### <a id="interface-applyforclub"></a>/applyForClub
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|club_id|string|社团id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getclubmembers"></a>/getClubMembers
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id
|index|number|索引, 为0时获取最新数据; 使用上一次调用返回的next_index获取下一页数据
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引|
|member_list|list|成员列表|

### <a id="interface-getclubapplications"></a>/getClubApplications
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id
|index|number|索引
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引
|application_list|list|申请列表

### <a id="interface-getuserapplications"></a>/getUserApplications
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid
|index|number|索引
|apply_status|number|申请状态
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引
|application_list|list|申请列表

### <a id="interface-approveapplication"></a>/approveApplication
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|club_id|string|社团id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-deleteapplication"></a>/deleteApplication
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid
|club_id|string|社团id
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getuseractivitylist"></a>/getUserActivityList
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid
|index|number|索引
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引
|activity_list|list|活动列表

### <a id="interface-getclubactivitylist"></a>/getClubActivityList
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id
|index|number|索引
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引
|activity_list|list|活动列表

### <a id="interface-deleteactivity"></a>/deleteActivity
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|


### <a id="interface-createactivity"></a>/createActivity
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|name|string|活动名
|sponsor|string|发起人openid
|club_id|string|所属社团id
|start_time|string|活动开始时间
|stop_time|string|活动结束时间
|registry_start_time|string|开始报名时间
|registry_stop_time|string|结束报名时间
|content|string|活动内容
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getactivitylist"></a>/getActivityList
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|index|number|为0表示获取最新活动信息|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页开始index，用于获取下一页内容|
|activity_list|list|活动列表

### <a id="interface-updateactivityinfo"></a> /updateActivityInfo
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|
|name|string|活动名称
|start_time|string|开始时间(YYYY-MM-DD hh:mm:ss)
|stop_time|string|结束时间(YYYY-MM-DD hh:mm:ss)
|registry_start_time|string|报名开始时间(YYYY-MM-DD hh:mm:ss)
|registry_stop_time|string|报名结束时间(YYYY-MM-DD hh:mm:ss)
|content|string|活动内容
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getactivitydetail"></a>/getActivityDetail
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id
|name|string|活动名
|sponsor|string|发起人id
|club_id|string|社团id
|target_id|string|目标人群id
|create_time|string|创建时间
|start_time|string|开始时间
|stop_time|string|结束时间
|registry_start_time|string|开始报名时间
|registry_stop_time|string|结束报名时间
|content|string|活动内容

### <a id="interface-getactivityparticipate"></a> /getActivityParticipate
GET
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|
|index|number|为0表示获取最新活动信息|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页开始index，用于获取下一页内容|
|participate_list|list|参加用户列表

### <a id="interface-applyforactivity"></a>/applyForActivity
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户openid|
|activity_id|string|活动id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-deleteactivityparticipate"></a> /deleteActivityParticipate
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|
|wx_id|string|用户id
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

## <a id="chapter-messageservice">表白墙服务接口</a>
### <a id="interface-postmessage"></a>/postMessage
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|user_id|string|用户openid|
|receiver|string|接收方(仅字符串, 无通知功能)|
|content|string|内容|
anonymous|bool|是否匿名|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getmessagelist"></a>/getMessageList
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|index|number|为0表示获取第一页内容|
|date|string|日期, 为空表示不进行筛选|
|wx_id|string|用户openid, 为空表示不进行筛选|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|next_index|number|下一页索引, -1表示没有更多结果|
|message_list|list|表白留言列表|

### <a id="interface-addlike"></a>/addLike
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|message_id|string|留言id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|

### <a id="interface-getlike"></a>/getLike
POST
#### 参数
|**属性**|**类型**|**说明**|
|-|-|-|
|message_id|string|留言id|
#### 返回值
|**属性**|**类型**|**说明**|
|-|-|-|
|status|number|状态码|
|errmsg|string|错误信息|
|data|json|
#### Data
|**属性**|**类型**|**说明**|
|-|-|-|
|like_count|number|点赞数|