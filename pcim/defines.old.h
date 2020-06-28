#pragma once


namespace nim
{
#ifdef __cplusplus
extern"C"
	{
#endif
		enum BoolStatus
		{
			BS_NOT_INIT = -1,	/**< 未初始化 */
			BS_FALSE = 0,	/**< false */
			BS_TRUE = 1		/**< true */
		};
		/** @enum NIMLogoutType Logout类型 */
		enum NIMLogoutType
		{
			kNIMLogoutChangeAccout = 1,	/**< 注销/切换帐号（返回到登录界面）*/
			kNIMLogoutKickout = 2,	/**< 被踢（返回到登录界面）*/
			kNIMLogoutAppExit = 3,	/**< 程序退出*/
			kNIMLogoutRelogin = 4,	/**< 重连操作，包括保存密码时启动程序伪登录后的重连操作以及掉线后的重连操作（帐号未变化）*/
		};
		/** @enum NIMResCode 返回的错误号（只定义需要客户端处理的） */
		enum NIMResCode
		{
			//通用错误码
			kNIMResError = 0,		/**< 错误 */
			kNIMResSuccess = 200,		/**< 没有错误，一切正常 */
			kNIMResVersionError = 201,		/**< 客户端版本不正确 */
			kNIMResUidPassError = 302,		/**< 用户名或密码错误 */
			kNIMResForbidden = 403,		/**< 禁止操作 */
			kNIMResNotExist = 404,		/**< 请求的目标（用户或对象）不存在 */
			kNIMResNoModify = 406,		/**< 数据自上次查询以来未发生变化（用于增量更新） */
			kNIMResTimeoutError = 408,		/**< 请求过程超时 */
			kNIMResParameterError = 414,		/**< 参数错误 */
			kNIMResConnectionError = 415,		/**< 网络连接出现错误 */
			kNIMResFrequently = 416,		/**< 操作太过频繁 */
			kNIMResExist = 417,		/**< 对象已经存在/重复操作 */
			kNIMResOverrun = 419,		/**< 超限 */
			kNIMResAccountBlock = 422,		/**< 帐号被禁用 */
			kNIMResUnknownError = 500,		/**< 未知错误，或者不方便告诉你 */
			kNIMResServerDataError = 501,		/**< 服务器数据错误 */
			kNIMResTooBuzy = 503,		/**< 服务器太忙 */
			kNIMResExceedLimit = 508,		/**< 超过配置有效期 */
			kNIMResInvalid = 509,		/**< 协议无效, 不允许访问的协议 */
			//群错误码
			kNIMResTeamECountLimit = 801,		/**< 已达到人数限制 */
			kNIMResTeamENAccess = 802,		/**< 没有权限 */
			kNIMResTeamENotExist = 803,		/**< 群不存在 */
			kNIMResTeamEMemberNotExist = 804,		/**< 用户不在兴趣组里面 */
			kNIMResTeamErrType = 805,		/**< 群类型不对 */
			kNIMResTeamLimit = 806,		/**< 创建群数量限制 */
			kNIMResTeamUserStatusErr = 807,		/**< 群成员状态不对 */
			kNIMResTeamApplySuccess = 808,		/**< 申请成功 */
			kNIMResTeamAlreadyIn = 809,		/**< 已经在群里 */
			kNIMResTeamInviteSuccess = 810,		/**< 邀请成功 */
			kNIMResForcePushCountLimit = 811,		/**< 强推列表账号数量超限 */
			kNIMResTeamMemberLimit = 813,		/**< 操作成功，但部分成员的群数量超限 */
			//数据解编错误代码
			kNIMResInvalidProtocol = 997,		/**< 协议已失效 */
			kNIMResEUnpacket = 998,		/**< 解包错误 */
			kNIMResEPacket = 999,		/**< 打包错误 */
			//
			kNIMResInBlack = 7101,		/**< 被接收方加入黑名单 SDK版本大于2.5.0支持*/

			//独立信令错误代码
			kNIMResRoomNotExists = 10404,	/**< 房间不存在 */
			kNIMResRoomHasExists = 10405,	/**< 房间已存在 */
			kNIMResRoomMemberNotExists = 10406,	/**< 不在房间内 */
			kNIMResRoomMemberHasExists = 10407,	/**< 已经在房间内 */
			kNIMResRoomInviteNotExists = 10408,	/**< 邀请不存在或已过期 */
			kNIMResRoomInviteHasReject = 10409,	/**< 邀请已经拒绝 */
			kNIMResRoomInviteHasAccept = 10410,	/**< 邀请已经接受了 */
			kNIMResPeerNimOffline = 10201,	/**< 对方云信不在线 */
			kNIMResPeerPushOffline = 10202,	/**< 对方推送亦不可达 */
			kNIMResRoomUidConflict = 10417,	/**< uid冲突 */
			kNIMResRoomMemberExceed = 10419,	/**< 房间人数超限 */
			kNIMResRoomMemberHasExistsOtherClient = 10420,	/**< 已经在房间内（自己的其他端） */

			//客户端自定义的错误号
			kNIMLocalRes = 10000,		/**< 值大于该错误号的都是客户端自定义的错误号。不能随意更改其值！ */
			kNIMResRoomLocalNeedRequestAgain = 10001,	/**< 客户端本地错误号，需要重新向IM服务器获取进入聊天室权限 */
			kNIMLocalResNetworkError = 10010,	/**< 客户端本地错误号，本地网络错误，需要检查本地网络 */

			//客户端自定义的消息错误号
			kNIMLocalResMsgNosUploadCancel = 10200,		/**< (发送文件消息或者stop_upload_ex)HTTP upload to NOS上传暂停 */
			kNIMLocalResMsgNosDownloadCancel = 10206,		/**< (收到文件消息或者stop_download_ex)HTTP download from NOS下载暂停 */
			kNIMLocalResMsgNosDownloadCheckError = 10207,	/**< 收到文件消息，NOS下载完成后本地文件检查错误，一般为下载的文件大小与文件信息不符 */
			kNIMLocalResMsgFileNotExist = 10404,		/**< 本地资源不存在 */
			kNIMLocalResParameterError = 10414,		/**< 本地错误码，参数错误，(收到消息，资源下载地址无效，无法下载) */
			kNIMLocalResExist = 10417,		/**< 本地错误码，对象已经存在/重复操作，(收到消息，本地资源已存在，不需要重复下载) */
			kNIMLocalResParaError = 10450,		/**< 调用api，传入的参数有误 */
			kNIMLocalResMsgSendNosError = 10502,		/**< 发送消息，上传NOS失败 */
			kNIMLocalResExceedLimit = 10508,		/**< 本地错误码,超过配置有效期或者所需参数不存在 */
			kNIMLocalResCheckMsgDBFailed = 10600,		/**< 导入消息历史时验证身份和加密密钥不通过 */
			kNIMLocalResImportMsgDBFailed = 10601,		/**< 导入消息历史时写记录失败 */
			kNIMLocalResTMembersSyncUndone = 10602,		/**< 群成员尚同步完成 */
			//客户端自定义的RTS错误号
			kNIMLocalResRtsError = 11100,		/**< rts会话 未知错误 */
			kNIMLocalResRtsIdNotExist = 11101,		/**< rts会话 id不存在 */
			kNIMLocalResRtsVChatExist = 11417,		/**< rts会话 音视频已存在 */
			kNIMLocalResRtsStatusError = 11501,		/**< rts会话 通道状态不正确 */
			kNIMLocalResRtsChannelNotExist = 11510,		/**< rts会话 通道不存在 */

			kNIMResRoomLinkError = 13001,		/**< 主链接错误 */
			kNIMResRoomError = 13002,		/**< 聊天室状态异常 */
			kNIMResRoomBlackBeOut = 13003,		/**< 黑名单用户禁止进入 */
			kNIMResRoomBeMuted = 13004,		/**< 被禁言 */
			kNIMResRoomAllMuted = 13006,		/**< 聊天室处于整体禁言状态,只有管理员能发言 */

			//客户端自定义的api调用问题
			kNIMLocalResAPIErrorInitUndone = 20000,		/**< 还未初始化或初始化未正常完成 */
			kNIMLocalResAPIErrorLoginUndone = 20001,		/**< 还未登陆或登录未完成 */
			kNIMLocalResAPIErrorLogined = 20002,		/**< 已经登录 */
			kNIMLocalResAPIErrorVersionError = 20003,		/**< SDK版本不对，可能会引发其他问题 */
			kNIMLocalResAPIErrorChatroomMixError = 20004,		/**< 聊天室模式混用错误，不支持同时以登陆状态和匿名状态登陆聊天室 */
		};
		/** @enum NIMLoginStep 登录步骤 */
		enum NIMLoginStep
		{
			kNIMLoginStepLinking = 0,	/**< 正在连接*/
			kNIMLoginStepLink = 1,	/**< 连接服务器*/
			kNIMLoginStepLogining = 2,	/**< 正在登录*/
			kNIMLoginStepLogin = 3,	/**< 登录验证*/
		};
		/** @enum NIMClientType 客户端类型 */
		enum NIMClientType
		{
			kNIMClientTypeDefault = 0,  /**< Default, unset*/
			kNIMClientTypeAndroid = 1,  /**< Android*/
			kNIMClientTypeiOS = 2,  /**< iOS*/
			kNIMClientTypePCWindows = 4,  /**< PC Windows*/
			kNIMClientTypeWeb = 16, /**< Web*/
			kNIMClientTypeRestAPI = 32, /**< RestAPI*/
			kNIMClientTypeMacOS = 64, /**< Mac*/
		};
		/** @enum NIMKickReason 被踢原因 */
		enum NIMKickReason
		{
			kNIMKickReasonSameGeneric = 1,  /**< 互斥类型的客户端互踢*/
			kNIMKickReasonServerKick = 2,  /**< 服务器端发起踢客户端指令*/
			kNIMKickReasonKickBySelfOtherClient = 3,  /**< 被自己的其他端踢掉*/
		};
		/** @enum NIMMultiSpotNotifyType 多点登录通知类型 */
		enum NIMMultiSpotNotifyType
		{
			kNIMMultiSpotNotifyTypeImIn = 2,		/**< 通知其他在线端自己登录了*/
			kNIMMultiSpotNotifyTypeImOut = 3,		/**< 通知其他在线端自己退出*/
		};
		/** @brief 多端登陆客户端信息 */
		struct OtherClientPres
		{
			std::string	app_account_;			/**< 第三方账号 */
			NIMClientType	client_type_;		/**< 客户端类型, 见NIMClientType */
			std::string	client_os_;				/**< 登录系统类型,比如ios 6.0.1 */
			std::string	mac_address_;			/**< 登录设备的mac地址 */
			std::string	device_id_;				/**< 设备id，uuid */
			int64_t		login_time_;			/**< 本次登陆时间, 精度到ms */
			std::string custom_data_;			/**< 自定义字段/
												/** 构造函数 */
			OtherClientPres() : login_time_(0) {}
		};
		/** @brief 登录结果回调信息 */
		struct LoginRes
		{
			NIMResCode res_code_;				/**< 返回的错误码NIMResCode */
			bool relogin_;						/**< 是否为重连过程 */
			NIMLoginStep	login_step_;		/**< 登录步骤NIMLoginStep */
			std::list<OtherClientPres> other_clients_;	/**< 其他端的在线状态列表，登录成功才会返回这部分内容 */
			bool retrying_;						/**< SDK是否在重试，如果为false，开发者需要检查登录步骤和错误码，明确问题后调用手动重连接口进行登录操作 */
			/** 构造函数 */
			LoginRes() : relogin_(false), retrying_(true) {}
		};
		/** @brief 被踢结果回调信息 */
		struct  KickoutRes
		{
			NIMClientType client_type_;			/**< int, 客户端类型NIMClientType */
			NIMKickReason kick_reason_;			/**< 返回的被踢原因NIMKickReason */
		};
		/** @brief 多端登录回调信息 */
		struct  MultiSpotLoginRes
		{
			NIMMultiSpotNotifyType	notify_type_;			/**< NIMMultiSpotNotifyType 多点登录通知类型 */
			std::list<OtherClientPres> other_clients_;		/**< 其他端的在线状态列表 */
		};
		/** @brief 踢人结果回调信息 */
		struct KickOtherRes
		{
			NIMResCode res_code_;					/**< 返回的错误码NIMResCode */
			std::list<std::string> device_ids_;		/**< 设备id，uuid */
		};









		/** @enum NIMTeamType 群组类型 */
		enum NIMTeamType
		{
			kNIMTeamTypeNormal = 0,	/**< 普通群 */
			kNIMTeamTypeAdvanced = 1,	/**< 高级群 */
		};

		/** @name 群组信息 Json Keys
		* @{
		*/
		static const char *kNIMTeamInfoKeyID = "tid";			/**< string,群id,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyName = "name";			/**< string,群名称 */
		static const char *kNIMTeamInfoKeyType = "type";			/**< int,群类型(NIMTeamType) */
		static const char *kNIMTeamInfoKeyCreator = "creator";		/**< string 群拥有者ID,通常情况下由SDK维护,开发者作为只读无需设置*/
		static const char *kNIMTeamInfoKeyLevel = "level";			/**< int,■■已废弃■■ 群等级,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyMemberMaxCount = "member_max_count";			/**< int,在创建群时，设置群的最大成员数，不可超过应用设定的最大成员数，否则返回414 */
		static const char *kNIMTeamInfoKeyProperty = "prop";			/**< string,群性质,长度限制：6000字符 */
		static const char *kNIMTeamInfoKeyValidFlag = "valid";			/**< int,群有效性标记位,有效1,无效0,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyMemberCount = "member_count";	/**< int,群成员数量,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyListTime = "list_timetag";	/**< long,群列表时间戳(毫秒),通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyCreateTime = "create_timetag";	/**< long,群创建时间戳(毫秒),通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyUpdateTime = "update_timetag";	/**< long,群信息上次更新时间戳(毫秒),通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyMemberValid = "member_valid";	/**< int,群有效性标记位,客户端用,有效1,无效0,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamInfoKeyIntro = "intro";			/**< string,群介绍,长度限制：255字符 */
		static const char *kNIMTeamInfoKeyAnnouncement = "announcement";	/**< string,群公告,长度限制：5000字符 */
		static const char *kNIMTeamInfoKeyJoinMode = "join_mode";		/**< int,入群模式(NIMTeamJoinMode),默认为kNIMTeamJoinModeNoAuth(0),不需要验证 */
		static const char *kNIMTeamInfoKeyBits = "bits";			/**< long, 群属性,开发者无需关注 20161011 by Oleg*/
		static const char *kNIMTeamInfoKeyCustom = "custom";			/**< string, 第三方扩展字段（仅负责存储和透传） */
		static const char *kNIMTeamInfoKeyServerCustom = "server_custom";	/**< string, 第三方服务器扩展字段（该配置项只能通过服务器接口设置，对客户端只读） */
		static const char *kNIMTeamInfoKeyIcon = "icon";			/**< string, 群头像,长度限制：1024字符 */
		static const char *kNIMTeamInfoKeyBeInviteMode = "be_invite_mode"; /**< int, 被邀请人同意方式，属性本身只有群主管理员可以修改,默认kNIMTeamBeInviteModeNeedAgree(0)/kNIMTeamBeInviteModeNotNeedAgree(1) */
		static const char *kNIMTeamInfoKeyInviteMode = "invite_mode";	/**< int, 谁可以邀请他人入群，属性本身只有群主管理员可以修改,默认kNIMTeamInviteModeManager(0)/kNIMTeamInviteModeEveryone(1) */
		static const char *kNIMTeamInfoKeyUpdateInfoMode = "update_info_mode";/**< int, 谁可以修改群资料，属性本身只有群主管理员可以修改,默认kNIMTeamUpdateInfoModeManager(0)/kNIMTeamUpdateInfoModeEveryone(1) */
		static const char *kNIMTeamInfoKeyUpdateCustomMode = "update_custom_mode";/**< int, 谁可以更新群自定义属性，属性本身只有群主管理员可以修改,默认kNIMTeamUpdateCustomModeManager(0)/kNIMTeamUpdateCustomModeEveryone(1) */
		static const char *kNIMTeamInfoKeyMuteAll = "mute_all";		/**< int, 群全员禁言标记 0:未禁言，1:禁言, 开发者只读 无法设置 */
		static const char *kNIMTeamInfoKeyMuteType = "mute_type";		/**<NIMTeamMuteType, 群禁言0不禁言 1普通成员禁言 3全部禁言 包括群主 开发者可以通过设置该属性调整群禁言状态*/
		/** @}*/ //群组信息Json Keys


		/** @name 群组成员信息 Json Keys
		* @{
		*/
		static const char *kNIMTeamUserKeyID = "tid";			/**< string,群id,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamUserKeyAccID = "accid";			/**< string,群成员id,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamUserKeyType = "type";			/**< int,群成员类型(NIMTeamUserType),默认kNIMTeamUserTypeNomal(0) */
		static const char *kNIMTeamUserKeyNick = "nick";			/**< string,群成员昵称 */
		static const char *kNIMTeamUserKeyBits = "bits";			/**< long,群成员属性,位操作(NIMTeamBitsConfigMask) */
		static const char *kNIMTeamUserKeyValidFlag = "valid";			/**< int,群成员有效性标记位,有效1,无效0,通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamUserKeyCreateTime = "create_timetag";	/**< long,入群时间戳(毫秒),通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamUserKeyUpdateTime = "update_timetag";	/**< long,群成员信息上次更新时间戳(毫秒),通常情况下由SDK维护,开发者作为只读无需设置 */
		static const char *kNIMTeamUserKeyCustom = "custom";			/**< string,群成员自定义扩展字段,必须为可以解析为json的非格式化的字符串 */
		static const char *kNIMTeamUserKeyMute = "mute";			/**< int,是否被禁言,0-非禁言(默认),1-禁言 */
		static const char *kNIMTeamUserKeyInvitorAccID = "invitor_accid";			/**< string,邀请者的accid 主动入群的时为空，尚未进行过初始化为" " */
		/** @}*/ //群组成员信息Json Keys

		/** @enum NIMTeamJoinMode 群允许加入类型 */
		enum NIMTeamJoinMode
		{
			kNIMTeamJoinModeNoAuth = 0,		/**< 不用验证 */
			kNIMTeamJoinModeNeedAuth = 1,		/**< 需要验证 */
			kNIMTeamJoinModeRejectAll = 2,		/**< 拒绝所有人入群 */
		};
		/** @enum NIMTeamBeInviteMode 被邀请人同意方式 */
		enum NIMTeamBeInviteMode
		{
			kNIMTeamBeInviteModeNeedAgree = 0,	/**< 需要同意 */
			kNIMTeamBeInviteModeNotNeedAgree = 1,	/**< 不需要同意 */
		};

		/** @enum NIMTeamInviteMode 谁可以邀请他人入群 */
		enum NIMTeamInviteMode
		{
			kNIMTeamInviteModeManager = 0,	/**< 管理员 */
			kNIMTeamInviteModeEveryone = 1,	/**< 所有人 */
		};

		/** @enum NIMTeamUpdateInfoMode 谁可以修改群资料 */
		enum NIMTeamUpdateInfoMode
		{
			kNIMTeamUpdateInfoModeManager = 0,	/**< 管理员 */
			kNIMTeamUpdateInfoModeEveryone = 1,	/**< 所有人 */
		};

		/** @enum NIMTeamUpdateCustomMode 谁可以更新群自定义属性 */
		enum NIMTeamUpdateCustomMode
		{
			kNIMTeamUpdateCustomModeManager = 0,	/**< 管理员 */
			kNIMTeamUpdateCustomModeEveryone = 1,	/**< 所有人 */
		};
		/** @enum NIMTeamMuteType 群信息kNIMTeamInfoKeyMuteType的配置定义 */
		enum NIMTeamMuteType
		{
			kNIMTeamMuteTypeNone = 0,	/**< 不禁言 */
			kNIMTeamMuteTypeNomalMute = 1,	/**< 普通成员禁言 */
			kNIMTeamMuteTypeAllMute = 3,	/**< 全部禁言 */
		};
		/** @enum NIMTeamBitsConfigMask 群组成员信息Bits属性kNIMTeamUserKeyBits的配置定义 */
		enum NIMTeamBitsConfigMask
		{
			kNIMTeamBitsConfigMaskMuteNone = 0,	/**< 开启提醒 bits 0000b*/
			kNIMTeamBitsConfigMaskMuteNotify = 1,	/**< 关闭提醒 bits 0001b*/
			kNIMTeamBitsConfigMaskOnlyAdmin = 2,	/**< 只接收管理员消息 bits 0010b 超大群当前不支持该选项*/
		};
		/** @enum NIMTeamUserType 群成员类型 */
		enum NIMTeamUserType
		{
			kNIMTeamUserTypeNomal = 0,		/**< 普通成员 */
			kNIMTeamUserTypeCreator = 1,		/**< 创建者 */
			kNIMTeamUserTypeManager = 2,		/**< 管理员 */
			kNIMTeamUserTypeApply = 3,		/**< 申请加入用户 */
			kNIMTeamUserTypeLocalWaitAccept = 100,	/**< 本地记录等待正在入群的用户 */
		};

		/** @enum NIMNotificationId 通知类型 */
		enum NIMNotificationId
		{
			kNIMNotificationIdTeamInvite = 0,			/**< 普通群拉人，{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attach为可选字段，作为应用自定义扩展字段,解析前需要判断有没有这个字段 */
			kNIMNotificationIdTeamKick = 1,			/**< 普通群踢人，{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attach为可选字段，作为应用自定义扩展字段,解析前需要判断有没有这个字段 */
			kNIMNotificationIdTeamLeave = 2,			/**< 退出群，{"id" : "a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamUpdate = 3,			/**< 群信息更新，{"team_info":team_info,"user_namecards":["namecard1", "namecard2"]} //群组信息(Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』)*/
			kNIMNotificationIdTeamDismiss = 4,			/**< 群解散，{"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamApplyPass = 5,			/**< 高级群申请加入成功，{"id":"a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamOwnerTransfer = 6,			/**< 高级群移交群主，{"id":"a1", "leave" : bool,"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamAddManager = 7,			/**< 增加管理员，{"ids":["a1","a2"],"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamRemoveManager = 8,			/**< 删除管理员，{"ids":["a1","a2"],"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamInviteAccept = 9,			/**< 高级群接受邀请进群，{"id":"a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamMuteMember = 10,			/**< 禁言/解禁群成员，{"user_namecards":["namecard1", "namecard2"],"team_info":team_info,"id":"a1","mute":1-禁言,0-解禁} */

			kNIMNotificationIdNetcallMiss = 101,			/**< 未接电话,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdNetcallBill = 102,			/**< 话单,{"calltype":2,"channel":6146077129466446197,"duration":8,"ids":["id1","id2"],"time":1430995117398}*/

			//服务器在线同步协议返回的结果
			kNIMNotificationIdTeamSyncCreate = 1000,			/**< 创建群 {"team_info" : team_info} //群组信息(Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』)*/
			kNIMNotificationIdTeamMemberChanged = 1001,			/**< 群成员变更{"team_member" : team_member_info} //群组成员信息（不包括自己）(Keys SEE MORE `nim_team_def.h` 『群组成员信息 Json Keys』)*/
			kNIMNotificationIdTeamSyncUpdateMemberProperty = 1002,	/**< 同步通知：修改群成员属性（可能是自己的或别人的）{"team_member" : team_member_info} //目前只需kNIMTeamUserKeyNick和kNIMTeamUserKeyBits (Keys SEE MORE `nim_team_def.h` 『群组成员信息 Json Keys』)*/

			//本地发起的操作通知APP上层
			kNIMNotificationIdLocalCreateTeam = 2000,			/**< 本地操作创建群 {"ids" : ["a1", "a2"]}*/
			kNIMNotificationIdLocalApplyTeam = 2001,			/**< 本地操作申请加入群 {}*/
			kNIMNotificationIdLocalRejectApply = 2002,			/**< 本地操作拒绝申请 {"id":"a1"}*/
			kNIMNotificationIdLocalRejectInvite = 2003,			/**< 本地操作拒绝邀请 {"id":"a1"}*/
			kNIMNotificationIdLocalUpdateMemberProperty = 2004,		/**< 本地操作更新群成员属性  {"team_member" : team_member_info} */
			kNIMNotificationIdLocalUpdateOtherNick = 2005,			/**< 本地操作更新他人nickname {}*/
			kNIMNotificationIdLocalGetTeamInfo = 2006,			/**< 本地操作获取群信息 {"team_info":team_info} //群组信息(Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』)*/
			kNIMNotificationIdLocalGetTeamList = 2007,			/**< 本地操作获取群成员信息结束*/
			kNIMNotificationIdLocalMuteMember = 2008,			/**< 本地操作对群成员禁言 {"id":"a1", "mute":1-禁言,0-解禁} */
			kNIMNotificationIdLocalMute = 2009,			/**< 本地操作对群禁言 {} */
			kNIMNotificationIdLocalGetTeamMsgUnreadCount = 2010,	/**< 获取群消息未读数 {[{"client_msg_id":"", "count":int, "read_accid":"当前已读成员的accid"},...]}*/
			kNIMNotificationIdLocalGetTeamMsgUnreadList = 2011,		/**< 获取群消息未读列表 {"client_msg_id":"", "read":["id1",...], "unread":["id2",...]}*/

			//Netcall本地操作通知
			kNIMNotificationIdLocalNetcallReject = 3103,			/**< 拒绝电话,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdLocalNetcallNoResponse = 3104,			/**< 无应答，未接通电话,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdLocalNetcallCanceled = 3105,	/**< 未接通前主叫方挂断，{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/

			kNIMNotificationIdSuperTeamInvite = 401,			/**< 超大群拉人，{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attach为可选字段，作为应用自定义扩展字段,解析前需要判断有没有这个字段 */
			kNIMNotificationIdSuperTeamKick = 402,			/**< 超大群踢人，{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attach为可选字段，作为应用自定义扩展字段,解析前需要判断有没有这个字段 */
			kNIMNotificationIdSuperTeamLeave = 403,			/**< 退出超大群，{"id" : "a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdSuperTeamUpdate = 404,			/**< 超大群群信息更新，{"team_info":team_info,"user_namecards":["namecard1", "namecard2"]} //群组信息(Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』)*/
			kNIMNotificationIdSuperTeamDismiss = 405,			/**< 超大群解散，{"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdSuperTeamOwnerTransfer = 406,    /**< 超大群移交群主，{"id":"a1","uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamAddManager = 407,	/**< 超大群增加管理员，{"ids":["a1","a2"],"uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamRemoveManager = 408,    /**< 超大群删除管理员，{"ids":["a1","a2"],"uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamMuteMember = 409,	/**< 超大群禁言/解禁群成员，{"uinfos":["uinfo1", "uinfo2"],“tinfo”:tinfo,"id":"a1","mute":1-禁言,0-解禁}*/
		};
		static const char *kNIMNotificationKeyId = "id";				/**< int, 见NIMNotificationId */
		static const char *kNIMNotificationKeyData = "data";			/**< json object 包含以下5种可能的数据结构*/
		static const char *kNIMNotificationKeyDataIds = "ids";			/**< string array */
		static const char *kNIMNotificationKeyDataInvalidIds = "invalid_ids";		/**< string array */
		static const char *kNIMNotificationKeyDataId = "id";				/**< string */
		static const char *kNIMNotificationKeyDataLeave = "leave";			/**< bool */
		static const char *kNIMNotificationKeyDataMute = "mute";			/**< int */
		static const char *kNIMNotificationKeyTeamInfo = "team_info";		/**< string, team_info 群组信息 Json Keys*/
		static const char *kNIMNotificationKeyTeamMember = "team_member";	/**< string, team_member_property 群组成员信息 Json Keys*/
		static const char *kNIMNotificationKeyUserNameCards = "name_cards";	/**< json string array, 操作者和被操作者双方的 用户名片 Json Keys*/


		//协议定义
		static const char *kNIMNameCardKeyAccid = "accid";	/**< string 帐号*/
		static const char *kNIMNameCardKeyName = "name";	/**< string 昵称*/
		static const char *kNIMNameCardKeyIcon = "icon";	/**< string 头像*/
		static const char *kNIMNameCardKeySign = "sign";	/**< string 签名*/
		static const char *kNIMNameCardKeyGender = "gender";	/**< int 性别*/
		static const char *kNIMNameCardKeyEmail = "email";	/**< string 邮箱*/
		static const char *kNIMNameCardKeyBirth = "birth";	/**< string 生日*/
		static const char *kNIMNameCardKeyMobile = "mobile";	/**< string 电话*/
		static const char *kNIMNameCardKeyEx = "ex";		/**< string 扩展字段, 必须为可以解析为json的非格式化的字符串*/
		static const char *kNIMNameCardKeyCreateTime = "create_timetag";	/**< long 创建时间戳 毫秒*/
		static const char *kNIMNameCardKeyUpdateTime = "update_timetag";	/**< long 更新时间戳 毫秒*/
		/** @}*/ //用户名片 Json Keys

		//协议定义
		static const char *kNIMSpecialRelationKeyAccid = "accid";			/**< string, 用户帐号 */
		static const char *kNIMSpecialRelationKeyIsMute = "is_mute";		/**< bool, 是静音帐号 */
		static const char *kNIMSpecialRelationKeyIsBlackList = "is_black";		/**< bool, 是黑名单帐号 */
		static const char *kNIMSpecialRelationKeyCreateTime = "create_timetag";	/**< long, 记录创建时间 */
		static const char *kNIMSpecialRelationKeyUpdateTime = "update_timetag";	/**< long, 记录更新时间 */
		/** @}*/ //用户特殊关系（黑名单、静音名单） Json Keys




		/** @name 事件信息 Json Keys
		* @{
		*/
		static const char *kNIMEventEventType = "event_type";			/**< int,事件类型 */
		static const char *kNIMEventEventValue = "event_value";		/**< int,事件值 */
		static const char *kNIMEventMsgIdClient = "msgid_client";		/**< string,客户端生成的消息id */
		static const char *kNIMEventConfig = "config";				/**< string,用户自定义事件扩展属性，最长4K */
		static const char *kNIMEventTTL = "ttl";				/**< long,事件有效期，单位：秒，时间范围：60s到7天 */
		static const char *kNIMEventBroadcastType = "broadcast_type";		/**< int,事件广播类型：1:仅在线 2:在线和离线 */
		static const char *kNIMEventSyncSelf = "sync_seft";			/**< int,0:不同步给自己的其他端，1：同步给自己的其他端 */

		static const char *kNIMEventTTLType = "ttltype";			/**< int,TtlType枚举值(客户端不填写) */
		static const char *kNIMEventDurable = "durable";			/**< int,是否需要持久化(可选字段)，默认为需要持久化,0:不需要持久化，1：需要持久化(客户端不填写) */
		static const char *kNIMEventEventTime = "event_time";			/**< long,事件发布的时间戳，服务器补充(客户端不填写) */
		static const char *kNIMEventMsgIdServer = "msgid_server";		/**< string,服务端生成的消息id(客户端不填写) */
		static const char *kNIMEventClientType = "client_type";		/**< int,发送客户端类型(客户端不填写) */
		static const char *kNIMEventNimConfig = "nim_config";			/**< string,预定义事件的扩展字段（在线状态事件：在线的客户端类型Json */
		static const char *kNIMEventMultiConfig = "multi_config";		/**< string,多端配置信息字段，JSON格式{"clent_type":"clent_config","1":"xxx","2":"xxx"} */

		static const char *kNIMEventPublisherAccid = "publisher_accid";	/**< string,事件发布者的accid(客户端不填写) */
		static const char *kNIMEventConsid = "consid";				/**< string,发送设备id(客户端不填写) */
		/** @}*/ //事件信息Json Keys

		/** @name 事件订阅信息 Json Keys
		* @{
		*/
		static const char *kNIMEventSubscribeEventType = "type";				/**< int,事件类型 */
		static const char *kNIMEventSubscribeTTL = "ttl";				/**< long,订阅有效期，单位：秒，范围：60s到30天 */
		static const char *kNIMEventSubscribeSyncEvent = "syncevent";			/**< int,订阅后是否立即同步最新事件 */

		static const char *kNIMEventSubscribePublisherAccid = "publisher_accid";	/**< string,被订阅人（事件发布人）的accid(客户端不填写) */
		static const char *kNIMEventSubscribeSubscribeAccid = "subscribe_accid";	/**< string,订阅人的accid(客户端不填写) */
		static const char *kNIMEventSubscribeSubscribeTime = "subscribe_time";		/**< long,订阅时间戳(客户端不填写) */
		/** @}*/ //事件订阅信息Json Keys

		/** @name 在线状态事件kNIMEventNimConfig字段Json Keys，只用于在线状态事件
		* @{
		*/
		static const char *kNIMEventNimConfigOnlineClient = "online";		/**< string,预定义事件的扩展字段中的在线的客户端类型 */
		/** @}*/ //在线状态事件kNIMEventNimConfig字段Json Keys，只用于在线状态事件

		/** @enum NIMEventBroadcastType 事件广播类型 */
		enum NIMEventBroadcastType
		{
			kNIMEventBroadcastTypeOnline = 1, /**< 仅在线 */
			kNIMEventBroadcastTypeAll = 2, /**< 在线和离线 */
		};

		/** @enum NIMEventSyncType 事件同步类型 */
		enum NIMEventSyncType
		{
			kNIMEventSyncTypeNoSelf = 0, /**< 事件不同步给自己其他端 */
			kNIMEventSyncTypeSelf = 1, /**< 事件同步给自己其他端 */
		};

		/** @enum NIMEventSubscribeSyncEventType 订阅的事件的同步类型 */
		enum NIMEventSubscribeSyncEventType
		{
			kNIMEventSubscribeSyncTypeUnSync = 0, /**< 订阅后不同步最新事件 */
			kNIMEventSubscribeSyncTypeSync = 1, /**< 订阅后立即同步最新事件 */
		};

		/** @enum NIMEventType 服务器预定义的事件类型 */
		enum NIMEventType
		{
			kNIMEventTypeOnlineState = 1, /**< 在线状态事件(客户端可发送) */
			kNIMEventTypeSyncEvent = 2, /**< 同步“订阅事件”事件(客户端不可发送) */
			kNIMEventTypeCustom = 100000, /**< 服务器保留1～99999的事件类型，客户端自定义事件类型需大于99999 */
		};

		/** @enum NIMEventOnlineStateValue 在线状态事件值 */
		enum NIMEventOnlineStateValue
		{
			kNIMEventOnlineStateValueLogin = 1, /**< 登录 */
			kNIMEventOnlineStateValueLogout = 2, /**< 登出 */
			kNIMEventOnlineStateValueDisconnect = 3, /**< 断开连接 */
			kNIMEventOnlineStateValueCustom = 10000, /**< 在线状态事件服务器保留1～9999的事件值，客户端自定义事件值需大于9999 */
			kNIMEventOnlineStateValueUpdateConfig = kNIMEventOnlineStateValueCustom + 1	/**< 自己的其他端更新了自己端的multi_config信息 */
		};


		static const char *kNIMFriendKey = "list";	/**< 好友简况 json array, */

		/** @name 好友简况 Json Keys
		* 例子 {"list" : [{"accid" : "litianyi01","beflag" : 1,"bits" : 0,"create_timetag" : 1439871983864,"flag" : 1,"source" : 0,"update_timetag" : 1439872006079}, ...]}
		* @{
		*/
		//协议定义
		static const char *kNIMFriendKeyAccid = "accid";  /**< string, 好友帐号*/
		static const char *kNIMFriendKeyFlag = "flag";	/**< NIMFriendFlag, 好友关系，修改时需要同步更新反向好友关系beflag */
		static const char *kNIMFriendKeyBeFlag = "beflag"; /**< NIMFriendFlag, 反向好友关系 */
		static const char *kNIMFriendKeySource = "source"; /**< NIMFriendSource, 好友来源 */
		static const char *kNIMFriendKeyAlias = "alias";	/**< string, 备注名 */
		static const char *kNIMFriendKeyBits = "bits";	/**< long, 扩展字段,位运算型 */
		static const char *kNIMFriendKeyEx = "ex";		/**< string, 扩展字段,必须为可以解析为json的非格式化的字符串 */
		static const char *kNIMFriendKeyCreateTime = "create_timetag"; /**< long, 创建时间戳(ms)*/
		static const char *kNIMFriendKeyUpdateTime = "update_timetag"; /**< long, 更新时间戳(ms)*/
		static const char *kNIMFriendServerEx = "server_ex"; /**< string, 服务端扩展字段，此字段客户端sdk只读，服务端api读写*/
		static const char *kNIMFriendDeleteAlias = "delete_alias"; /**< bool, 删除好友时是否删除备注信息*/




		/** @enum NIMDataSyncType 数据同步类型 */
		enum NIMDataSyncType
		{
			kNIMDataSyncTypeUnreadMsg = 2,		/**< 未读消息同步*/
			kNIMDataSyncTypeTeamInfo = 3,		/**< 所有群的信息同步, json_attachment为同步到的team_info json array*/
			kNIMDataSyncTypeRoamMsg = 7,		/**< 漫游消息同步,每个会话同步到漫游消息都会触发该类通知*/
			kNIMDataSyncTypeSuperTeamInfo = 22,		/**< 所有群的信息同步, json_attachment为同步到的team_info json array*/
			kNIMDataSyncTypeTeamUserList = 1000,		/**< 群成员列表同步, json_attachment为同步到的tid*/
			kNIMDataSyncTypeAllTeamUserList = 1001,		/**< 所有群的成员列表同步完毕, json_attachment为空*/
			kNIMDataSyncTypeSuperTeamUserList = 1010,		/**< 超大群成员列表同步, json_attachment为同步到的tid*/
			kNIMDataSyncTypeAllSuperTeamUserList = 1011,		/**< 所有超大群的成员列表同步完毕, json_attachment为空*/

		};

		/** @enum NIMDataSyncStatus 数据同步状态 */
		enum NIMDataSyncStatus
		{
			kNIMDataSyncStatusComplete = 1,		/**< 同步完成*/
		};

		static const char *kNIMSysMsgKeyLocalRescode = "rescode";			/**< int, 返回的错误码,见NIMResCode */
		static const char *kNIMSysMsgKeyLocalFeature = "feature";			/**< int, 本地定义的消息特征,见NIMMessageFeature */
		static const char *kNIMSysMsgKeyLocalUnreadCount = "unread_count";		/**< int, 每次带回的是当前的总的未读数 */
		static const char *kNIMSysMsgKeyLocalContent = "content";			/**< json string, 协议定义的系统消息结构 */
		/** @}*/ //接收系统消息Json Keys，本地定义

		static const char *kNIMSysMsglogQueryKeyCount = "count";				/**< int, 查询得到的数量 */
		static const char *kNIMSysMsglogQueryKeyUnreadCount = "unread_count";	/**< int, 每次查询带回的是当前的总的未读数 */
		static const char *kNIMSysMsglogQueryKeyContent = "content";			/**< json object array 协议定义的系统消息结构 */

		/** @name 系统消息/客户端自定义通知结构 Json Keys，协议定义
		* @{
		*/
		static const char *kNIMSysMsgKeyTime = "msg_time";			/**< long,		时间戳,选填 */
		static const char *kNIMSysMsgKeyType = "msg_type";			/**< int,		通知类型,NIMSysMsgType,必填 */
		static const char *kNIMSysMsgKeyToAccount = "to_account";			/**< string,	接收者id,如果是个人,则是对方用户id,如果是群,则是群id,必填 */
		static const char *kNIMSysMsgKeyFromAccount = "from_account";		/**< string,	自己id,选填 */
		static const char *kNIMSysMsgKeyMsg = "msg";				/**< string,	只读字段，SDK不转发该字段 */
		static const char *kNIMSysMsgKeyAttach = "attach";				/**< string,	消息内容,规定是可以解析为Json格式的字符串，必须为非格式化形式 */
		static const char *kNIMSysMsgKeyMsgId = "msg_id";				/**< long,		服务器消息id（自定义通知消息,必须填0）,发送方不需要填写*/
		static const char *kNIMSysMsgKeyLocalStatus = "log_status";			/**< int,		本地定义的系统消息状态,见NIMSysMsgStatus,发送方不需要填写*/
		static const char *kNIMSysMsgKeyLocalClientMsgId = "client_msg_id";		/**< string,	本地定义的消息id,发送方必填,建议使用uuid */
		static const char *kNIMSysMsgKeyCustomSaveFlag = "custom_save_flag";	/**< int,		(可选)自定义通知消息是否存离线:0-不存（只发给在线用户）,1-存（可发给离线用户）*/
		static const char *kNIMSysMsgKeyCustomApnsText = "custom_apns_text";	/**< string,	(可选)自定义通知消息推送文本，不填则不推送*/
		static const char *kNIMSysMsgKeyPushPayload = "push_payload";		/**< json string, (可选)第三方自定义的推送属性，必须为可以解析为Json的非格式化的字符串，长度2048 */
		static const char *kNIMSysMsgKeyPushEnable = "push_enable";		/**< int,		(可选)是否需要推送, 0:不需要,1:需要,默认1 */
		static const char *kNIMSysMsgKeyPushNeedBadge = "push_need_badge";	/**< int,		(可选)推送是否要做消息计数(角标)，0:不需要，1:需要，默认1 */
		static const char *kNIMSysMsgKeyPushNeedPrefix = "push_prefix";		/**< int,		(可选)推送需要前缀，0：不需要，1：需要，默认0 */
		static const char *kNIMSysMsgKeyAntiSpamEnable = "anti_spam_enable";	/**< int, (功能暂时不开放)是否需要过易盾反垃圾, 0:不需要,1:需要, 默认0 */
		static const char *kNIMSysMsgKeyAntiSpamContent = "anti_spam_content";	/**< string, (功能暂时不开放)(可选)开发者自定义的反垃圾字段 */

		/** @enum NIMSysMsgStatus 系统消息状态 */
		enum NIMSysMsgStatus
		{
			kNIMSysMsgStatusNone = 0,		/**< 默认,未读 */
			kNIMSysMsgStatusPass = 1,		/**< 收到消息,通过 */
			kNIMSysMsgStatusDecline = 2,		/**< 收到消息,拒绝 */
			kNIMSysMsgStatusRead = 3,		/**< 收到消息,已读 */
			kNIMSysMsgStatusDeleted = 4,		/**< 已删 */
			kNIMSysMsgStatusInvalid = 5,		/**< 已失效 */
		};

		/** @enum NIMSysMsgType 系统消息内容类型 */
		enum NIMSysMsgType
		{
			kNIMSysMsgTypeTeamApply = 0,		/**< 申请入群  */
			kNIMSysMsgTypeTeamReject = 1,		/**< 拒绝入群申请 */
			kNIMSysMsgTypeTeamInvite = 2,		/**< 邀请进群 kNIMSysMsgKeyAttach : {"team_info":team_info, "attach" : ""} attach为可选字段，作为应用自定义扩展字段,解析前需要判断有没有这个字段, 群组信息(Keys SEE MORE `nim_team_def.h` 『群组信息 Json Keys』) */
			kNIMSysMsgTypeTeamInviteReject = 3,		/**< 拒绝邀请 */
			kNIMSysMsgTypeFriendAdd = 5,		/**< 加好友, kNIMSysMsgKeyAttach: {"vt":verifyType} */
			kNIMSysMsgTypeFriendDel = 6,		/**< 删除好友 */
			kNIMSysMsgTypeCustomP2PMsg = 100,		/**< 点对点透传消息（透传消息的内容放到kNIMSysMsgKeyAttach）,SDK对该类消息不计入未读数, 即使kNIMSysMsgKeyPushNeedBadge为1 */
			kNIMSysMsgTypeCustomTeamMsg = 101,		/**< 群透传消息（透传消息的内容放到kNIMSysMsgKeyAttach）,SDK对该类消息不计入未读数, 即使kNIMSysMsgKeyPushNeedBadge为1 */
			kNIMSysMsgTypeCustomSuperTeamMsg = 103,		/**< 超大群透传消息（透传消息的内容放到kNIMSysMsgKeyAttach）,SDK对该类消息不计入未读数, 即使kNIMSysMsgKeyPushNeedBadge为1 */
			kNIMSysMsgTypeUnknown = 1000,		/**< 未知类型，本地使用，发送时勿使用，作为默认 */
		};

	









		/** @name 会话列表的Json Keys
		* @{
		*/
		static const char *kNIMSessionListCount = "count";				/**< int, 会话列表项数量 */
		static const char *kNIMSessionListUnreadCount = "unread_counts";	/**< int, 总未读数 */
		static const char *kNIMSessionListContent = "content";			/**< json object (Keys as follows), 会话列表项内容 */
		static const char *kNIMSessionId = "id";					/**< string, 会话id */
		static const char *kNIMSessionType = "type";				/**< int, 会话类型(见NIMSessionType 个人0 群组1 超大群5 etc) */
		static const char *kNIMSessionUnreadCount = "unread_count";		/**< int, 本地消息历史中该会话未读消息数量 */
		static const char *kNIMSessionCommand = "command";			/**< int, 会话项操作命令NIMSessionCommand */
		static const char *kNIMSessionMsgClientID = "msg_client_id";		/**< string, 本地消息历史中该会话最后一条消息的客户端ID唯一标识，即消息uuid */
		static const char *kNIMSessionMsgFromAccount = "msg_from_account";	/**< string, 本地消息历史中该会话最后一条消息的发送方帐号 */
		static const char *kNIMSessionMsgTime = "msg_time";			/**< long, 本地消息历史中该会话最后一条消息的时间 */
		static const char *kNIMSessionMsgType = "msg_type";			/**< int, 本地消息历史中该会话最后一条消息的类型 见NIMMessageType*/
		static const char *kNIMSessionMsgBody = "msg_body";			/**< string, 本地消息历史中该会话最后一条消息的内容 */
		static const char *kNIMSessionMsgAttach = "msg_attach";			/**< string, 本地消息历史中该会话最后一条消息的attach */
		static const char *kNIMSessionMsgStatus = "msg_status";			/**< int, 本地消息历史中该会话最后一条消息的状态，见NIMMsgLogStatus */
		static const char *kNIMSessionMsgSubStatus = "msg_sub_status";		/**< int, 本地消息历史中该会话最后一条消息的子状态，见NIMMsgLogSubStatus */
		static const char *kNIMSessionLastUpdatedMsg = "last_updated_msg";	/**< bool, (批量)消息变更或增加时是否是最后一条变更的信息 */
		static const char *kNIMSessionOnTop = "top";				/**< bool, 是否置顶 */
		static const char *kNIMSessionExtendedData = "extend_data";		/**< string, 本地扩展字段, 限4096 */
		static const char *kNIMSessionRobotFlag = "robot_session";		/**< bool, 是否为机器人会话, 默认为false */
		/** @}*/ //会话列表的Json Keys

		/** @enum NIMSessionType 会话类型 */
		enum NIMSessionType
		{
			kNIMSessionTypeP2P = 0,			/**< 个人，即点对点 */
			kNIMSessionTypeTeam = 1,			/**< 群组 */
			kNIMSessionTypeSuperTeam = 5,			/**< 超大群组 */
		};

		/** @enum NIMSessionCommand 会话操作命令 */
		enum NIMSessionCommand
		{
			kNIMSessionCommandAdd = 0,	/**< 添加会话项 */
			kNIMSessionCommandRemove = 1,	/**< 删除单个会话项 */
			kNIMSessionCommandRemoveAll = 2,	/**< 删除所有会话项 */
			kNIMSessionCommandRemoveAllP2P = 3,	/**< 删除所有点对点的会话项 */
			kNIMSessionCommandRemoveAllTeam = 4,	/**< 删除所有群的会话项 */
			kNIMSessionCommandMsgDeleted = 5,	/**< 单个会话项的消息已删除 */
			kNIMSessionCommandAllMsgDeleted = 6,	/**< 所有会话项的消息已删除 */
			kNIMSessionCommandAllP2PMsgDeleted = 7,	/**< 所有点对点会话项的消息已删除 */
			kNIMSessionCommandAllTeamMsgDeleted = 8,	/**< 所有群会话项的消息已删除 */
			kNIMSessionCommandUpdate = 9,	/**< 更新会话项 */
			kNIMSessionCommandRemoveAllSuperTeam = 10,	/**< 删除所有超大群的会话项 */
			kNIMSessionCommandAllSuperTeamMsgDeleted = 11,	/**< 所有超大群会话项的消息已删除 */

		};

		/** @name 消息结构 Json Keys
		* 例子 {"client_msg_id" : "c0d1167459fc754098a531482b51a1da","local_res_path" : "","log_status" : 4,"log_sub_status" : 0,"msg_attach" : "","msg_body" : "发送文本消息正文", "msg_type" : 0, "resend_flag" : 0, "time" : 1437014897000, "to_accid" : "4045", "to_type" : 1}
		* @{
		*/
		//协议定义
		static const char *kNIMMsgKeyToType = "to_type";			/**< int,会话类型(NIMSessionType) */
		static const char *kNIMMsgKeyToAccount = "to_accid";			/**< string,消息接收方id,给自己发送消息时填写自己id */
		static const char *kNIMMsgKeyFromAccount = "from_id";			/**< string,消息发送方id,服务器填写,发送方不需要填写 */
		static const char *kNIMMsgKeyFromClientType = "from_client_type";	/**< int,消息发送方客户端类型（NIMClientType）,服务器填写,发送方不需要填写 */
		static const char *kNIMMsgKeyFromDeviceId = "from_device_id";		/**< string,消息发送方设备id,服务器填写,发送方不需要填写 */
		static const char *kNIMMsgKeyFromNick = "from_nick";			/**< string,消息发送方昵称,服务器填写,发送方不需要填写 */
		static const char *kNIMMsgKeyTime = "time";				/**< long,消息时间戳(毫秒) */
		static const char *kNIMMsgKeyType = "msg_type";			/**< int,消息类型(NIMMessageType) */
		static const char *kNIMMsgKeyBody = "msg_body";			/**< string,消息正文,长度限制：5000字符 */
		static const char *kNIMMsgKeyAttach = "msg_attach";			/**< string,消息多媒体资源参数,不同类型多媒体参数不同,发送非多媒体消息时不需要填写,如需使用json string,必须为可以解析为json的非格式化的字符串 */
		static const char *kNIMMsgKeyClientMsgid = "client_msg_id";		/**< string,客户端消息id */
		static const char *kNIMMsgKeyServerMsgid = "server_msg_id";		/**< long,服务器端消息id */
		static const char *kNIMMsgKeyResendFlag = "resend_flag";		/**< int,消息重发标记位,第一次发送0,重发1 */
		static const char *kNIMMsgKeyHistorySave = "cloud_history";		/**< int,(可选)该消息是否存储云端历史,可选，0:不支持,1:支持, 默认1 */
		static const char *kNIMMsgKeyMsgRoaming = "roam_msg";			/**< int,(可选)该消息是否支持漫游,可选,0:不支持,1:支持, 默认1 */
		static const char *kNIMMsgKeyMsgSync = "sync_msg";			/**< int,(可选)该消息是否支持发送者多端同步,可选,0:不支持,1:支持, 默认1 */
		static const char *kNIMMsgKeyPushNeedBadge = "push_need_badge";	/**< int,(可选)推送是否要做消息计数(角标)，0:不需要，1:需要，默认1 */
		static const char *kNIMMsgKeyServerExt = "server_ext";			/**< string,(可选)自定义扩展字段,必须为可以解析为json的非格式化的字符串,长度限制1024 */
		static const char *kNIMMsgKeyPushPayload = "push_payload";		/**< string,(可选)第三方自定义的推送属性，必须为可以解析为json的非格式化的字符串，长度2048 */
		static const char *kNIMMsgKeyPushContent = "push_content";		/**< string,(可选)自定义推送文案，长度限制200字节 */
		static const char *kNIMMsgKeyPushEnable = "push_enable";		/**< int,(可选)是否需要推送, 0:不需要,1:需要,默认1,aos在收到0是不要模拟本地推送 */
		static const char *kNIMMsgKeyPushNeedPrefix = "push_prefix";		/**< int,(可选)推送是否需要前缀，0:不需要，1:需要，默认1 */
		static const char *kNIMMsgKeyMsgRoutable = "routable_msg";		/**< int,(可选)该消息是否抄送,0:不支持,1:支持,默认按照app的路由开关 */
		static const char *kNIMMsgKeySetMsgOffline = "offline_msg";		/**< int,(可选)消息是否要存离线,0:不需要, 1:需要，默认1*/
		static const char *kNIMMsgKeyForcePushList = "force_push_list";			/**< string,(可选)群组消息强推列表,推送指定账号id string array json, 如果推送全员不填*/
		static const char *kNIMMsgKeyForcePushContent = "force_push_content";		/**< string,(可选)群组消息强推文本 */
		static const char *kNIMMsgKeyIsForcePush = "is_force_push";		/**< int,(可选)群组消息是否强推,0:不强推, 1:强推，属性只针对群组消息强推列表 */
		static const char *kNIMMsgKeyAntiSpamEnable = "anti_spam_enable";	/**< int, 是否需要过易盾反垃圾, 0:不需要,1:需要, 默认0 */
		static const char *kNIMMsgKeyAntiSpamContent = "anti_spam_content";	/**< string, (可选)开发者自定义的反垃圾字段,长度限制：5000字符, 格式为json string,{"type" : 1:文本，2：图片，3视频, "data" : "文本内容or图片地址or视频地址"}*/
		static const char *kNIMMsgKeyClientAntiSpam = "client_anti_spam_hitting";	/**< int, (可选) 是否命中客户端反垃圾,命中:1 未命中：0 或者不填写*/
		static const char *kNIMMsgKeyAntiSpamBizId = "anti_spam_business_id";	/**< string,  (可选)用户配置的对某些单条消息另外的反垃圾的业务ID*/
		static const char *kNIMMsgKeyAntiSpamUsingYiDun = "anti_spam_using_yidun";	/**< int,  (可选) 单条消息是否使用易盾反垃圾 0:(在开通易盾的情况下)不过易盾反垃圾而是通用反垃圾 其他都是按照原来的规则*/
		static const char *kNIMMsgKeyTeamMsgAck = "team_msg_ack";		/**< (可选)int, 群消息是否需要已读业务，0：不需要，1：需要*/


		//本地定义
		static const char *kNIMMsgKeyLocalKeyTeamMsgAckSent = "team_msg_ack_sent";	/**< bool 是否已经发送群消息已读回执 */
		static const char *kNIMMsgKeyLocalKeyTeamMsgUnreadCount = "team_msg_unread_count";	/**< int, 群消息未读数 */
		static const char *kNIMMsgKeyLocalFilePath = "local_res_path";		/**< string,多媒体消息资源本地绝对路径,SDK本地维护,发送多媒体消息时必填 */
		static const char *kNIMMsgKeyLocalTalkId = "talk_id";			/**< string,会话id,发送方选填,接收方收到的是消息发送方id */
		static const char *kNIMMsgKeyLocalResId = "res_id";				/**< string,多媒体资源id,发送方选填,接收方收到的是客户端消息id */
		static const char *kNIMMsgKeyLocalLogStatus = "log_status";			/**< int,消息状态(NIMMsgLogStatus)  */
		static const char *kNIMMsgKeyLocalLogSubStatus = "log_sub_status";		/**< int,消息二级状态(NIMMsgLogSubStatus) */
		static const char *kNIMMsgKeyLocalExt = "local_ext";			/**< string,只维护在本地的扩展字段,必须为可以解析为json的非格式化的字符串 */
		/** @}*/ //消息结构 Json Keys


		/** @enum NIMMessageType Message Type */
		enum NIMMessageType
		{
			kNIMMessageTypeText = 0,			/**< 文本类型消息*/
			kNIMMessageTypeImage = 1,			/**< 图片类型消息*/
			kNIMMessageTypeAudio = 2,			/**< 声音类型消息*/
			kNIMMessageTypeVideo = 3,			/**< 视频类型消息*/
			kNIMMessageTypeLocation = 4,			/**< 位置类型消息*/
			kNIMMessageTypeNotification = 5,		/**< 系统类型通知（包括入群出群通知等） NIMNotificationId*/
			kNIMMessageTypeFile = 6,			/**< 文件类型消息*/
			kNIMMessageTypeTips = 10,			/**< 提醒类型消息,Tip内容根据格式要求填入消息结构中的kNIMMsgKeyServerExt字段*/
			kNIMMessageTypeRobot = 11,			/**< 波特机器人消息*/
			kNIMMessageTypeCustom = 100,			/**< 自定义消息*/

			kNIMMessageTypeUnknown = 1000,		/**< 未知类型消息，本地使用，发送时勿使用，作为默认值*/
		};

		/** @enum NIMMessageFeature 消息种类 */
		enum NIMMessageFeature
		{
			kNIMMessageFeatureDefault = 0,			/**< 默认*/
			kNIMMessageFeatureLeaveMsg = 1,			/**< 离线消息*/
			kNIMMessageFeatureRoamMsg = 2,			/**< 漫游消息*/
			kNIMMessageFeatureSyncMsg = 3,			/**< 同步消息*/
			kNIMMessageFeatureCustomizedMsg = 4,		/**< 透传消息*/
		};

		/** @enum NIMMsgLogStatus 消息状态 */
		enum NIMMsgLogStatus
		{
			kNIMMsgLogStatusNone = 0,			/**< 默认,不能当查询条件,意义太多*/
			kNIMMsgLogStatusUnread = 1,			/**< 收到消息,未读*/
			kNIMMsgLogStatusRead = 2,			/**< 收到消息,已读*/
			kNIMMsgLogStatusDeleted = 3,			/**< 已删*/
			kNIMMsgLogStatusSending = 4,			/**< 发送中*/
			kNIMMsgLogStatusSendFailed = 5,			/**< 发送失败*/
			kNIMMsgLogStatusSent = 6,			/**< 已发送*/
			kNIMMsgLogStatusReceipt = 7,			/**< 对方已读发送的内容*/
			kNIMMsgLogStatusDraft = 8,			/**< 草稿*/
			kNIMMsgLogStatusSendCancel = 9,			/**< 发送取消*/
			kNIMMsgLogStatusRefused = 10, /**< 被对方拒绝,比如被对方加入黑名单等等*/
		};
		/** @enum NIMMsgLogSubStatus 消息子状态 */
		enum NIMMsgLogSubStatus
		{
			kNIMMsgLogSubStatusNone = 0,			/**< 默认状态*/

			//这二个标志适用于所有
			kNIMMsgLogSubStatusNotPlaying = 20,			/**< 未播放*/
			kNIMMsgLogSubStatusPlayed = 21,			/**< 已播放*/
		};


		/** @name NOS 上传文件到Nos缺省tag定义 */
		static const char *kNIMNosDefaultTagResource = "nim_default_profile_icon";		/**< string 资源类文件上传tag 如头像、群头像等， 可以通过 nim_nos_init_tags修改资源的过期时间*/
		static const char *kNIMNosDefaultTagIM = "nim_default_im";	/**< string im消息类文件上传tag 如图片、文件、音视频消息等， 可以通过 nim_nos_init_tags修改资源的过期时间*/


		static const char *kNIMFileMsgKeyMd5 = "md5";			/**< string,资源MD5,发送方选填 */
		static const char *kNIMFileMsgKeySize = "size";			/**< long,资源大小(KB),发送方选填 */
		static const char *kNIMFileMsgKeyDisplayName = "name";			/**< string,用于显示的文件名,发送方选填,默认文件名 */
		static const char *kNIMFileMsgKeyUrl = "url";			/**< string,资源URL, 发送方不需要填写 */
		static const char *kNIMFileMsgKeyExt = "ext";			/**< string,资源扩展名,不包括符号'.',发送方若选填需要保证资源本地路径包含扩展名 */


		static const char *kNIMMsgAttachKeyMd5 = "md5";			/**< string,资源MD5,发送方选填 */
		static const char *kNIMMsgAttachKeySize = "size";			/**< long,资源大小(KB),发送方选填 */
		static const char *kNIMMsgAttachKeyUrl = "url";			/**< long,资源URL, 发送方不需要填写 */
		static const char *kNIMMsgAttachKeyExt = "ext";			/**< string,资源扩展名,不包括符号'.',发送方若选填需要保证资源本地路径包含扩展名 */
		static const char *kNIMMsgAttachKeyDisplayName = "name";		/**< string,用于显示的文件名,发送方选填,默认文件名 */
		static const char *kNIMMsgAttachKeyTag = "upload_tag";			/**< string, (可选)发送含有附件的消息时使用的场景标签(可参见nos删除策略) ,Audio Image Video File 或者可以被SDK解析到本地文件路径的自定义消息*/
		/** @}*/ //attach多媒体资源参数通用键名定义，可替代不同类型多媒体所使用的相同的参数的键名.


		static const char *kNIMImgMsgKeyMd5 = "md5";			/**< string,资源MD5,发送方选填 */
		static const char *kNIMImgMsgKeySize = "size";			/**< long,资源大小(KB),发送方选填 */
		static const char *kNIMImgMsgKeyWidth = "w";				/**< int,图片宽度,发送方必填 */
		static const char *kNIMImgMsgKeyHeight = "h";				/**< int,图片高度,发送方必填 */
		static const char *kNIMImgMsgKeyUrl = "url";			/**< string,资源URL, 发送方不需要填写 */
		static const char *kNIMImgMsgKeyExt = "ext";			/**< string,资源扩展名,不包括符号'.',发送方若选填需要保证资源本地路径包含扩展名 */
		static const char *kNIMImgMsgKeyDisplayName = "name";		/**< string,用于显示的文件名,发送方选填,默认文件名 */
		/** @}*/ //attach图片类型多媒体资源参数键名定义

		/** @name attach语音类型多媒体资源参数键名定义
		* @{
		*/
		static const char *kNIMAudioMsgKeyMd5 = "md5";			/**< string,资源MD5,发送方选填 */
		static const char *kNIMAudioMsgKeySize = "size";			/**< long,资源大小(KB),发送方选填 */
		static const char *kNIMAudioMsgKeyDuration = "dur";			/**< int,语音资源时间长度(毫秒),发送方必填 */
		static const char *kNIMAudioMsgKeyUrl = "url";			/**< string,资源URL, 发送方不需要填写 */
		static const char *kNIMAudioMsgKeyExt = "ext";			/**< string,资源扩展名,不包括符号'.',发送方若选填需要保证资源本地路径包含扩展名 */
		static const char *kNIMAudioMsgKeyDisplayName = "name";		/**< string,用于显示的文件名,发送方选填,默认文件名 */
		/** @}*/ //attach语音类型多媒体资源参数键名定义

		/** @name attach短视频类型多媒体资源参数键名定义
		* @{
		*/
		static const char *kNIMVideoMsgKeyMd5 = "md5";			/**< string,资源MD5,发送方选填 */
		static const char *kNIMVideoMsgKeySize = "size";			/**< long,资源大小(KB),发送方选填 */
		static const char *kNIMVideoMsgKeyDisplayName = "name";			/**< string,用于显示的文件名,发送方选填,默认文件名 */
		static const char *kNIMVideoMsgKeyDuration = "dur";			/**< int,短视频资源时间长度(毫秒),发送方必填 */
		static const char *kNIMVideoMsgKeyWidth = "w";				/**< int,短视频画面宽度,发送方必填 */
		static const char *kNIMVideoMsgKeyHeight = "h";				/**< int,短视频画面高度,发送方必填 */
		static const char *kNIMVideoMsgKeyUrl = "url";			/**< string,资源URL, 发送方不需要填写 */
		static const char *kNIMVideoMsgKeyExt = "ext";			/**< string,资源扩展名,不包括符号'.',发送方若选填需要保证资源本地路径包含扩展名 */
		/** @}*/ //attach短视频类型多媒体资源参数键名定义


		/** @name attach位置类型多媒体资源参数键名定义
		* @{
		*/
		static const char *kNIMLocationMsgKeyLatitude = "lat";			/**< double,纬度 */
		static const char *kNIMLocationMsgKeyLongitude = "lng";			/**< double,经度 */
		static const char *kNIMLocationMsgKeyTitle = "title";			/**< string,位置信息 */
		/** @}*/ //attach位置类型多媒体资源参数键名定义



		/** @name attach波特机器人类型多媒体资源参数键名定义
		* @{
		*/
		static const char *kNIMBotRobotMsgKeyRobotID = "robotAccid";	/**< string，机器人云信ID */
		static const char *kNIMBotRobotSentMsgKeyParam = "param";		/**< json string，给机器人发送时需要填的字段，字段内容定义可见Demo源码或参考波特开发文档 */
		static const char *kNIMBotRobotReceivedMsgKeyClientMsgID = "clientMsgId";/**< string，机器人回复时带的字段，表示该条回复相关联的消息ID */
		static const char *kNIMBotRobotReceivedMsgKeyMsgOut = "msgOut";		/**< bool，是否为机器人回复，默认为true */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsg = "robotMsg";	/**< json string，机器人回复时带的字段，波特机器人消息 */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsgFlag = "flag";		/**< string，机器人回复时带的字段，表示该条回复类型，类型定义可见Demo源码或参考波特开发文档，bot或faq */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsgMessage = "message";	/**< json object，机器人回复时带的字段，表示该条回复内容，字段内容定义可见Demo源码或参考波特开发文档 */
		//static const char *kNIMBotRobotReceivedMsgKeyRobotMsgS		= "s";			/**< string，未知 */
		/** @}*/ //attach波特机器人类型多媒体资源参数键名定义


		static const char *kNIMMsgKeyLocalRescode = "rescode";			/**< int,消息错误码(NIMResCode) */
		static const char *kNIMMsgKeyLocalMsgFeature = "feature";			/**< int,消息种类(NIMMessageFeature),SDK本地维护 */
		static const char *kNIMMsgKeyLocalReceiveMsgContent = "content";			/**< json string,消息内容，协议定义的消息结构 */

		static const char *kNIMMsglogStatusChangedKeyTalkID = "talk_id";/**< 会话ID */
		static const char *kNIMMsglogStatusChangedKeyMsgTimetag = "msg_timetag";/**< 临界的消息的时间戳 */
		static const char *kNIMMsglogStatusChangedKeyStatus = "status";/**< 变更后的状态 */

		static const char *kNIMMsglogQueryKeyCount = "count";			/**< int, 查询得到的数量 */
		static const char *kNIMMsglogQueryKeySource = "source";			/**< NIMMsglogQuerySource, 查询结果来源 */
		static const char *kNIMMsglogQueryKeyContent = "content";		/**< json object array (Keys SEE MORE in `nim_talk_def.h` 『消息结构 Json Keys』)，查询得到的msglog内容 */
		/** @}*/ //查询消息历史结果Json Keys

		/** @enum NIMMsglogQuerySource 消息历史查询来源 */
		enum NIMMsglogQuerySource
		{
			kNIMMsglogQuerySourceLocal = 0,			/**< 本地查询*/
			kNIMMsglogQuerySourceServer = 1,			/**< 云端查询*/
		};
		/** @enum NIMMsgLogQueryRange 消息历史的检索范围 */
		enum NIMMsgLogQueryRange
		{
			kNIMMsgLogQueryRangeP2P = kNIMSessionTypeP2P,	/**< 指定的个人（点对点会话）（注意：暂不支持指定多个人的检索！）*/
			kNIMMsgLogQueryRangeTeam = kNIMSessionTypeTeam,	/**< 指定的群组（注意：暂不支持指定多个群组的检索！）*/
			kNIMMsgLogQueryRangeSuperTeam = kNIMSessionTypeSuperTeam,	/**< 指定的超大群组（注意：暂不支持指定多个群组的检索！）*/

			kNIMMsgLogQueryRangeAll = 100,					/**< 全部*/
			kNIMMsgLogQueryRangeAllP2P = 101,					/**< 所有个人会话*/
			kNIMMsgLogQueryRangeAllTeam = 102,					/**< 所有群组*/
			kNIMMsgLogQueryRangeAllSuperTeam = 103,					/**< 所有超大群组*/
			kNIMMsgLogQueryRangeUnknown = 200,					/**< 未知（如指定个人和群组的集合）（注意：暂不支持指定个人和群组的混合检索！）*/
		};

		/** @brief 导出消息记录到云端参数定义 */
		typedef struct
		{
			/** 自定义的打包方式回调，SDK生成原始数据文后会调用开发者自定义的打包（压缩）方法
			* @param[in] file_path		原始数据文件路径
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return char* 生成的打包（压缩）文件的路径
			*/
			char*(*ExportBackupToRemotePackageCallback)(const char* const file_path, void* user_data);
			/** 自定义的加密方式回调，SDK生成原始数据经过打包（压缩）后会调用开发者自定义的加密方法
			* @param[in] file_path		打包（压缩）后的文件路径
			* @param[in] encrypt_key	加密秘钥 与 encrypt_key_为同一个值
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return char* 加密后的文件路径
			*/
			char*(*ExportBackupToRemoteEncryptCallback)(const char* const  file_path, const char* const  encrypt_key, void* user_data);
			char* encrypt_key_;/**< 加密秘钥*/
			/**导出过程的进度回调
			* @param[in] op		操作类型 导入/导出
			* @param[in] progress	进度 0-1
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return void
			*/
			void(*LogsBackupProgressCallback)(enum LogsBackupRemoteOperate op, float progress, void* user_data);
			/** 导出完成后的结果回调
			* @param[in] op		操作类型 导入/导出
			* @param[in] state	完成状态参考 LogsBackupRemoteState
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return void
			*/
			void(*LogsBackupCompleteCallback)(enum LogsBackupRemoteOperate op, enum LogsBackupRemoteState state, void* user_data);
			/**开发者自定义的导出消息的过滤器
			* @param[in] msg		消息的详细数据 json格式
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return bool true:导出这条消息;false:不导出这条消息
			*/
			bool(*ExportBackupToRemoteLogFiter)(const char* const msg, void* user_data);
			/**在导出过程中生成的新路径（字符串）释放接口
			* @param[in] data_ptr	指向路径（字符串）的引用
			* @return void
			*/
			void(*NewPathRelease)(char** data_ptr);
			void* user_data_; /**< APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！ */
		}NIMLogsBackupExportInfo;

		/** @brief从云端导入消息记录参数定义 */
		typedef struct
		{
			/**自定义的解包方式回调，从云端步的备份文件经解密后会回调开发者自定义的解包（解压）方法
			* @param[in] file_path		经解密后文件路径
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return char* 解包后的文件路径
			*/
			char*(*ImportBackupFromRemoteUnPackageCallback)(const char* const file_path, void* user_data);
			/**自定义的解密方式回调，SDK从云端同步完备份文件后会调用开发者自定义的解密方法
			* @param[in] file_path		从云端同步到的文件路径
			* @param[in] encrypt_key	解密秘钥 与导出时加密密钥相同
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return char* 解密后的文件路径
			*/
			char*(*ImportBackupFromRemoteDecryptCallback)(const char* const file_path, const char* const encrypt_key, void* user_data);
			/** 导入过程的进度回调
			* @param[in] op		操作类型 导入/导出
			* @param[in] progress	进度 0-1
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return void
			*/
			void(*LogsBackupProgressCallback)(enum LogsBackupRemoteOperate op, float progress, void* user_data);
			/**导入完成后的结果回调
			* @param[in] op		操作类型 导入/导出
			* @param[in] state	 完成状态参考 LogsBackupRemoteState
			* @param[in] user_data		APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
			* @return void
			*/
			void(*LogsBackupCompleteCallback)(enum LogsBackupRemoteOperate op, enum LogsBackupRemoteState state, void* user_data);
			/**在导入过程中生成的新路径（字符串）释放接口
			* @param[in] data_ptr	指向路径（字符串）的引用
			* @return bool true:导出这条消息;false:不导出这条消息
			*/
			void(*NewPathRelease)(char**);
			void* user_data_;/**< APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！ */
		}NIMLogsBackupImportInfo;
		enum LogsBackupRemoteState
		{
			LogsBackupRemoteState_Begin = -2,/**< 定义开始*/
			LogsBackupRemoteState_UnDef,				/**< 未定义*/
			LogsBackupRemoteState_UserCanceled = 5,		/**< 已取消*/
			LogsBackupRemoteState_SDKError,			/**< SDK 已出错*/
			//导入状态
			LogsBackupRemoteState_IMP_NoBackup,/**<没有备份文件*/
			LogsBackupRemoteState_IMP_SyncFromSrvError,/**<查询备份失败一般是网络错误*/
			LogsBackupRemoteState_IMP_DownloadBackupFailed,/**<下载备份文件出错*/
			LogsBackupRemoteState_IMP_RAWError,/**<解密/解压出来的源文件格式错误*/
			LogsBackupRemoteState_IMP_ParseRAWError,/**<解析源文件格式错误*/
			LogsBackupRemoteState_IMP_LocalDBFailed, /**<导入本地DB出错	*/
			//导出状态
			LogsBackupRemoteState_EXP_LocalDBFailed,/**<打开本地DB失败*/
			LogsBackupRemoteState_EXP_RAWError,/**<导出到源文件失败*/
			LogsBackupRemoteState_EXP_UploadBackupFailed,/**<上传备份文件出错*/
			LogsBackupRemoteState_EXP_SyncToSrvError,/**<同步到服务器出错一般是网络错误*/

			LogsBackupRemoteState_Done,				/**< 完成*/
			LogsBackupRemoteState_Done_NoLogs,/**<完成，但未导出任何记录*/
			LogsBackupRemoteState_End,/**<定义结束*/
			LogsBackupRemoteState_FinalState_Begin = LogsBackupRemoteState_UserCanceled,/**<是否已是最终状态的一个标识，可以判断state是否为终态(state >= LogsBackupRemoteState_FinalState_Begin)*/

		};

#ifdef __cplusplus
	};
#endif //__cplusplus
}

