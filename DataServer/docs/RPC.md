# 数据访问服务 RPC接口
以下类型在tars协议文件中定义，参照[tars数据类型定义文档]()
```
UserInfo            用户信息
ClubInfo            社团信息
ApplyInfo           社团申请信息
ActivityInfo        活动信息
ActivityRecord      活动报名记录信息
Message             表白留言信息
```

## 接口列表
**用户数据操作相关接口**
- [hasUser](#interface-hasuser)
- [hasPhone](#interface-hasphone)
- [createUser](#interface-createuser)
- [getUserInfo](#interface-getuserinfo)
- [getGroupInfo](#interface-getgroupinfo)

**社团数据操作相关接口**
- [createClubManager](#interface-createclubmanager)
- [createClub](#interface-createclub)
- [getClubList](#interface-getclublist)
- [getManagerClubList](#interface-getmanagerclublist)
- [getClubManagerCount](#interface-getclubmanagercount)
- [createApply](#interface-createapply)
- [getApplyListByClubId](#interface-getapplylistbyclubId)
- [getApplyListByUserId](#interface-getapplylistbyuserId)
- [setApplyStatus](#interface-setapplystatus)
- [getApplyCount](#interface-getapplycount)
- [deleteApply](#interface-deleteapply)

**活动数据操作相关接口**
- [createActivity](#interface-createactivity)
- [getActivityList](#interface-getactivitylist)
- [updateActivity](#interface-updateactivity)
- [deleteActivity](#interface-deleteactivity)
- [getActivityInfo](#interface-getactivityinfo)
- [createActivityRecord](#interface-createactivityrecord)
- [getActivityRecords](#interface-getactivityrecords)
- [getRecordCount](#interface-getrecordcount)
- [deleteActivityRecord](#interface-deleteactivityrecord)

**表白墙数据操作相关接口**
- [insertMessage](#interface-insertmessage)
- [getMsgList](#interface-getmsglist)
- [addLike](#interface-addlike)
- [getLike](#interface-getlike)

## 接口详情
### <a id="interface-hasuser"> hasUser
判断用户是否存在

**定义**
```cpp
int hasUser(string wx_id, out bool userExist)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|userExist|bool|true表示用户已经存在|

### <a id="interface-hasphone"> hasPhone
判断手机号是否存在

**定义**
```cpp
int hasPhone(string phone, out bool phoneExist)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|phone|string|手机号|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|phoneExist|bool|true表示手机号已存在|

### <a id="interface-createuser"> createUser
创建用户

**定义**
```cpp
int createUser(string wx_id, UserInfo userInfo)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|userInfo|UserInfo|用户信息|

**返回值**

无

### <a id="interface-getuserinfo"> getUserInfo
获取用户信息

**定义**
```cpp
int getUserInfo(string wx_id, out UserInfo userInfo)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|userInfo|UserInfo|用户信息|

### <a id="interface-getgroupinfo"> getGroupInfo
获取分组信息

**定义**
```cpp
int getGroupInfo(out map<int, string> groupInfo)
```

**参数**

无

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|groupInfo|map<int, string>|权限组信息|

### <a id="interface-createclubmanager"> createClubManager
创建社团管理员

**定义**
```cpp
int createClubManager(string wx_id, string club_id)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|

**返回值**

无

### <a id="interface-createclub"> createClub
创建社团

**定义**
```cpp
int createClub(ClubInfo clubInfo, out string club_id)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|clubInfo|ClubInfo|社团信息|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id|

### <a id="interface-getclublist"> getClubList
获取社团列表

**定义**
```cpp
int getClubList(int index, int batch, string wx_id, out int nextIndex, out vector<ClubInfo> clubInfoList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|index|int|索引|
|batch|int|请求数量|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一页索引, -1表示没有更多数据|
|clubInfoList|vector<ClubInfo>|社团列表|

### <a id="interface-getmanagerclublist"> getManagerClubList
获取管理员社团列表

**定义**
```cpp
int getManagerClubList(int index, int batch, string wx_id, out int nextIndex, out vector<ClubInfo> clubInfoList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|index|int|索引|
|batch|int|请求数量|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一页索引, -1表示没有更多数据|
|clubInfoList|vector<ClubInfo>|社团列表|

### <a id="interface-getclubmanagercount"> getClubManagerCount
获取社团管理者记录数

**定义**
```cpp
int getClubManagerCount(string wx_id, string club_id, out int count)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|count|int|记录数|

### <a id="interface-createapply"> createApply
创建社团申请

**定义**
```cpp
int createApply(string wx_id, string club_id)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|

**返回值**

无

### <a id="interface-getapplylistbyclubId"> getApplyListByClubId
通过club_id获取社团申请列表

**定义**
```cpp
int getApplyListByClubId(string club_id, int index, int batch, int apply_status, out int nextIndex, out vector<ApplyInfo> applyList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|club_id|string|社团id|
|index|int|索引|
|batch|int|请求数量|
|apply_status|申请状态|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一次请求的索引|
|applyList|vector<ApplyInfo>|申请列表|

### <a id="interface-getapplylistbyuserId"> getApplyListByUserId
通过用户id获取社团列表

**定义**
```cpp
int getApplyListByUserId(string wx_id, int index, int batch, int apply_status, out int nextIndex, out vector<ApplyInfo> applyList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|index|int|索引|
|batch|int|请求数量|
|apply_status|int|申请状态|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一次请求索引|
|applyList|vector<ApplyInfo>|申请列表|

### <a id="interface-setapplystatus"> setApplyStatus
设置申请状态

**定义**
```cpp
int setApplyStatus(string wx_id, string club_id, int apply_status, out int affectRows)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|
|apply_status|int|申请状态|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|affectRows|int|影响数据的行数|

### <a id="interface-getapplycount"> getApplyCount
获取社团申请数量

**定义**
```cpp
int getApplyCount(string wx_id, string club_id, int apply_status, out int count)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|
|apply_status|int|申请状态|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|count|int|申请数量|

### <a id="interface-deleteapply"> deleteApply
删除申请

**定义**
```cpp
int deleteApply(string wx_id, string club_id, out int affectRows)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|club_id|string|社团id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|affectRows|int|影响数据的行数|

### <a id="interface-createactivity"> createActivity
新建活动

**定义**
```cpp
int createActivity(ActivityInfo activityInfo)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|activityInfo|ActivityInfo|活动信息|

**返回值**

无

### <a id="interface-getactivitylist"> getActivityList
获取活动列表

**定义**
```cpp
int getActivityList(int index, int batch, string wx_id, string club_id, out int nextIndex, out vector<map<string, string>> activityList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|index|int|索引|
|batch|int|请求数量|
|wx_id|string|用户id|
|club_id|string|社团id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一次请求的索引|
|activityList|vector<map<string, string>>|活动列表|

### <a id="interface-updateactivity"> updateActivity
更新活动信息

**定义**
```cpp
int updateActivity(ActivityInfo activityInfo, out int affectRows)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|activityInfo|ActivityInfo|活动信息|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|affectRows|int|影响数据的行数|

### <a id="interface-deleteactivity"> deleteActivity
删除活动

**定义**
```cpp
int deleteActivity(string activity_id, out int affectRows)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|affectRows|int|影响数据的行数|

### <a id="interface-getactivityinfo"> getActivityInfo
获取活动详情

**定义**
```cpp
int getActivityInfo(string activity_id, out ActivityInfo activityInfo)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|activityInfo|ActivityInfo|活动信息|

### <a id="interface-createactivityrecord"> createActivityRecord
新建活动记录

**定义**
```cpp
int createActivityRecord(string wx_id, string activity_id)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
|activity_id|string|活动id|

**返回值**

无

### <a id="interface-getactivityrecords"> getActivityRecords
获取活动记录

**定义**
```cpp
int getActivityRecords(int index, int batch, string activity_id, out int nextIndex, out vector<ActivityRecord> recordList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|index|int|索引|
|batch|int|请求记录数|
|activity_id|string|活动id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一次请求索引|
|recordList|vector<ActivityRecord>|活动报名记录列表|

### <a id="interface-getrecordcount"> getRecordCount
获取活动记录数

**定义**
```cpp
int getRecordCount(string wx_id, string activity_id, out int count)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|wx_id|string|用户id|
activity_id|string|活动id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|count|int|记录数|

### <a id="interface-deleteactivityrecord"> deleteActivityRecord
删除活动记录

**定义**
```cpp
int deleteActivityRecord(string activity_id, string wx_id, out int affectRows)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|activity_id|string|活动id|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|affectRows|int|影响数据的行数|

### <a id="interface-insertmessage"> insertMessage
插入留言

**定义**
```cpp
int insertMessage(Message msg)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|msg|Message|表白留言信息|

**返回值**

无

### <a id="interface-getmsglist"> getMsgList
获取留言列表

**定义**
```cpp
int getMsgList(int index, string date, string wx_id, out int nextIndex, out vector<Message> msgList)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|index|int|索引|
|date|string|日期, 为空字符串时不筛选日期; 格式为YYYY-MM-DD hh:mm:ss|
|wx_id|string|用户id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|nextIndex|int|下一次请求索引|
|msgList|vector<Message>|留言列表|

### <a id="interface-addlike"> addLike
点赞+1

**定义**
```cpp
int addLike(string message_id)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|message_id|string|表白留言id|

**返回值**

无

### <a id="interface-getlike"> getLike
获取点赞数

**定义**
```cpp
int getLike(string message_id, out int like_count)
```

**参数**

|**属性**|**类型**|**说明**|
|-|-|-|
|message_id|string|表白留言id|

**返回值**

|**属性**|**类型**|**说明**|
|-|-|-|
|like_count|int|留言点赞数|

