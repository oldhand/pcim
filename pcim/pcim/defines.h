#pragma once


namespace pcim
{
#ifdef __cplusplus
extern"C"
	{
#endif
	 
		/** @enum PCIMResCode 返回的错误号（只定义需要客户端处理的） */
		enum PCIMResCode
		{
			//通用错误码
			kPCIMResError = 0,		/**< 错误 */
			kPCIMResSuccess = 200,		/**< 没有错误，一切正常 */
			kPCIMResVersionError = 201,		/**< 客户端版本不正确 */
			kPCIMResUidPassError = 302,		/**< 用户名或密码错误 */
			kPCIMResNoProfileError = 301,		/**< 用户名没有注册错误 */
			kPCIMResForbidden = 403,		/**< 禁止操作 */
			kPCIMResNotExist = 404,		/**< 请求的目标（用户或对象）不存在 */
			kPCIMResNoModify = 406,		/**< 数据自上次查询以来未发生变化（用于增量更新） */
			kPCIMResTimeoutError = 408,		/**< 请求过程超时 */
			kPCIMResParameterError = 414,		/**< 参数错误 */
			kPCIMResConnectionError = 415,		/**< 网络连接出现错误 */
			kPCIMResFrequently = 416,		/**< 操作太过频繁 */
			kPCIMResExist = 417,		/**< 对象已经存在/重复操作 */
			kPCIMResOverrun = 419,		/**< 超限 */
			kPCIMResAccountBlock = 422,		/**< 帐号被禁用 */
			kPCIMResUnknownError = 500,		/**< 未知错误，或者不方便告诉你 */
			kPCIMResServerDataError = 501,		/**< 服务器数据错误 */
			kPCIMResTooBuzy = 503,		/**< 服务器太忙 */
			kPCIMResExceedLimit = 508,		/**< 超过配置有效期 */
			kPCIMResInvalid = 509,		/**< 协议无效, 不允许访问的协议 */
			//群错误码
			kPCIMResTeamECountLimit = 801,		/**< 已达到人数限制 */
			kPCIMResTeamENAccess = 802,		/**< 没有权限 */
			kPCIMResTeamENotExist = 803,		/**< 群不存在 */
			kPCIMResTeamEMemberNotExist = 804,		/**< 用户不在兴趣组里面 */
			kPCIMResTeamErrType = 805,		/**< 群类型不对 */
			kPCIMResTeamLimit = 806,		/**< 创建群数量限制 */
			kPCIMResTeamUserStatusErr = 807,		/**< 群成员状态不对 */
			kPCIMResTeamApplySuccess = 808,		/**< 申请成功 */
			kPCIMResTeamAlreadyIn = 809,		/**< 已经在群里 */
			kPCIMResTeamInviteSuccess = 810,		/**< 邀请成功 */
			kPCIMResForcePushCountLimit = 811,		/**< 强推列表账号数量超限 */
			kPCIMResTeamMemberLimit = 813,		/**< 操作成功，但部分成员的群数量超限 */
			//数据解编错误代码
			kPCIMResInvalidProtocol = 997,		/**< 协议已失效 */
			kPCIMResEUnpacket = 998,		/**< 解包错误 */
			kPCIMResEPacket = 999,		/**< 打包错误 */
			//
			kPCIMResInBlack = 7101,		/**< 被接收方加入黑名单 SDK版本大于2.5.0支持*/

			//独立信令错误代码
			kPCIMResRoomNotExists = 10404,	/**< 房间不存在 */
			kPCIMResRoomHasExists = 10405,	/**< 房间已存在 */
			kPCIMResRoomMemberNotExists = 10406,	/**< 不在房间内 */
			kPCIMResRoomMemberHasExists = 10407,	/**< 已经在房间内 */
			kPCIMResRoomInviteNotExists = 10408,	/**< 邀请不存在或已过期 */
			kPCIMResRoomInviteHasReject = 10409,	/**< 邀请已经拒绝 */
			kPCIMResRoomInviteHasAccept = 10410,	/**< 邀请已经接受了 */
			kPCIMResPeerPCIMOffline = 10201,	/**< 对方云信不在线 */
			kPCIMResPeerPushOffline = 10202,	/**< 对方推送亦不可达 */
			kPCIMResRoomUidConflict = 10417,	/**< uid冲突 */
			kPCIMResRoomMemberExceed = 10419,	/**< 房间人数超限 */
			kPCIMResRoomMemberHasExistsOtherClient = 10420,	/**< 已经在房间内（自己的其他端） */

			//客户端自定义的错误号
			kPCIMLocalRes = 10000,		/**< 值大于该错误号的都是客户端自定义的错误号。不能随意更改其值！ */
			kPCIMResRoomLocalNeedRequestAgain = 10001,	/**< 客户端本地错误号，需要重新向IM服务器获取进入聊天室权限 */
			kPCIMLocalResNetworkError = 10010,	/**< 客户端本地错误号，本地网络错误，需要检查本地网络 */

			//客户端自定义的消息错误号
			kPCIMLocalResMsgNosUploadCancel = 10200,		/**< (发送文件消息或者stop_upload_ex)HTTP upload to NOS上传暂停 */
			kPCIMLocalResMsgNosDownloadCancel = 10206,		/**< (收到文件消息或者stop_download_ex)HTTP download from NOS下载暂停 */
			kPCIMLocalResMsgNosDownloadCheckError = 10207,	/**< 收到文件消息，NOS下载完成后本地文件检查错误，一般为下载的文件大小与文件信息不符 */
			kPCIMLocalResMsgFileNotExist = 10404,		/**< 本地资源不存在 */
			kPCIMLocalResParameterError = 10414,		/**< 本地错误码，参数错误，(收到消息，资源下载地址无效，无法下载) */
			kPCIMLocalResExist = 10417,		/**< 本地错误码，对象已经存在/重复操作，(收到消息，本地资源已存在，不需要重复下载) */
			kPCIMLocalResParaError = 10450,		/**< 调用api，传入的参数有误 */
			kPCIMLocalResMsgSendNosError = 10502,		/**< 发送消息，上传NOS失败 */
			kPCIMLocalResExceedLimit = 10508,		/**< 本地错误码,超过配置有效期或者所需参数不存在 */
			kPCIMLocalResCheckMsgDBFailed = 10600,		/**< 导入消息历史时验证身份和加密密钥不通过 */
			kPCIMLocalResImportMsgDBFailed = 10601,		/**< 导入消息历史时写记录失败 */
			kPCIMLocalResTMembersSyncUndone = 10602,		/**< 群成员尚同步完成 */
			//客户端自定义的RTS错误号
			kPCIMLocalResRtsError = 11100,		/**< rts会话 未知错误 */
			kPCIMLocalResRtsIdNotExist = 11101,		/**< rts会话 id不存在 */
			kPCIMLocalResRtsVChatExist = 11417,		/**< rts会话 音视频已存在 */
			kPCIMLocalResRtsStatusError = 11501,		/**< rts会话 通道状态不正确 */
			kPCIMLocalResRtsChannelNotExist = 11510,		/**< rts会话 通道不存在 */

			kPCIMResRoomLinkError = 13001,		/**< 主链接错误 */
			kPCIMResRoomError = 13002,		/**< 聊天室状态异常 */
			kPCIMResRoomBlackBeOut = 13003,		/**< 黑名单用户禁止进入 */
			kPCIMResRoomBeMuted = 13004,		/**< 被禁言 */
			kPCIMResRoomAllMuted = 13006,		/**< 聊天室处于整体禁言状态,只有管理员能发言 */

			//客户端自定义的api调用问题
			kPCIMLocalResAPIErrorInitUndone = 20000,		/**< 还未初始化或初始化未正常完成 */
			kPCIMLocalResAPIErrorLoginUndone = 20001,		/**< 还未登陆或登录未完成 */
			kPCIMLocalResAPIErrorLogined = 20002,		/**< 已经登录 */
			kPCIMLocalResAPIErrorVersionError = 20003,		/**< SDK版本不对，可能会引发其他问题 */
			kPCIMLocalResAPIErrorChatroomMixError = 20004,		/**< 聊天室模式混用错误，不支持同时以登陆状态和匿名状态登陆聊天室 */
		}; 
		/** @brief 登录结果回调信息 */
		struct LoginRes
		{
			PCIMResCode res_code;				/**< 返回的错误码PCIMResCode */
			bool relogin;						/**< 是否为重连过程 */
			bool times;						    /**< 重连次数 */
			std::string message;				/**< 返回错误信息 */
		};
	 

#ifdef __cplusplus
	};
#endif //__cplusplus
}

