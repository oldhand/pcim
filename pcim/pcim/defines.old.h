#pragma once


namespace nim
{
#ifdef __cplusplus
extern"C"
	{
#endif
		enum BoolStatus
		{
			BS_NOT_INIT = -1,	/**< δ��ʼ�� */
			BS_FALSE = 0,	/**< false */
			BS_TRUE = 1		/**< true */
		};
		/** @enum NIMLogoutType Logout���� */
		enum NIMLogoutType
		{
			kNIMLogoutChangeAccout = 1,	/**< ע��/�л��ʺţ����ص���¼���棩*/
			kNIMLogoutKickout = 2,	/**< ���ߣ����ص���¼���棩*/
			kNIMLogoutAppExit = 3,	/**< �����˳�*/
			kNIMLogoutRelogin = 4,	/**< ����������������������ʱ��������α��¼������������Լ����ߺ�������������ʺ�δ�仯��*/
		};
		/** @enum NIMResCode ���صĴ���ţ�ֻ������Ҫ�ͻ��˴���ģ� */
		enum NIMResCode
		{
			//ͨ�ô�����
			kNIMResError = 0,		/**< ���� */
			kNIMResSuccess = 200,		/**< û�д���һ������ */
			kNIMResVersionError = 201,		/**< �ͻ��˰汾����ȷ */
			kNIMResUidPassError = 302,		/**< �û������������ */
			kNIMResForbidden = 403,		/**< ��ֹ���� */
			kNIMResNotExist = 404,		/**< �����Ŀ�꣨�û�����󣩲����� */
			kNIMResNoModify = 406,		/**< �������ϴβ�ѯ����δ�����仯�������������£� */
			kNIMResTimeoutError = 408,		/**< ������̳�ʱ */
			kNIMResParameterError = 414,		/**< �������� */
			kNIMResConnectionError = 415,		/**< �������ӳ��ִ��� */
			kNIMResFrequently = 416,		/**< ����̫��Ƶ�� */
			kNIMResExist = 417,		/**< �����Ѿ�����/�ظ����� */
			kNIMResOverrun = 419,		/**< ���� */
			kNIMResAccountBlock = 422,		/**< �ʺű����� */
			kNIMResUnknownError = 500,		/**< δ֪���󣬻��߲���������� */
			kNIMResServerDataError = 501,		/**< ���������ݴ��� */
			kNIMResTooBuzy = 503,		/**< ������̫æ */
			kNIMResExceedLimit = 508,		/**< ����������Ч�� */
			kNIMResInvalid = 509,		/**< Э����Ч, ��������ʵ�Э�� */
			//Ⱥ������
			kNIMResTeamECountLimit = 801,		/**< �Ѵﵽ�������� */
			kNIMResTeamENAccess = 802,		/**< û��Ȩ�� */
			kNIMResTeamENotExist = 803,		/**< Ⱥ������ */
			kNIMResTeamEMemberNotExist = 804,		/**< �û�������Ȥ������ */
			kNIMResTeamErrType = 805,		/**< Ⱥ���Ͳ��� */
			kNIMResTeamLimit = 806,		/**< ����Ⱥ�������� */
			kNIMResTeamUserStatusErr = 807,		/**< Ⱥ��Ա״̬���� */
			kNIMResTeamApplySuccess = 808,		/**< ����ɹ� */
			kNIMResTeamAlreadyIn = 809,		/**< �Ѿ���Ⱥ�� */
			kNIMResTeamInviteSuccess = 810,		/**< ����ɹ� */
			kNIMResForcePushCountLimit = 811,		/**< ǿ���б��˺��������� */
			kNIMResTeamMemberLimit = 813,		/**< �����ɹ��������ֳ�Ա��Ⱥ�������� */
			//���ݽ��������
			kNIMResInvalidProtocol = 997,		/**< Э����ʧЧ */
			kNIMResEUnpacket = 998,		/**< ������� */
			kNIMResEPacket = 999,		/**< ������� */
			//
			kNIMResInBlack = 7101,		/**< �����շ���������� SDK�汾����2.5.0֧��*/

			//��������������
			kNIMResRoomNotExists = 10404,	/**< ���䲻���� */
			kNIMResRoomHasExists = 10405,	/**< �����Ѵ��� */
			kNIMResRoomMemberNotExists = 10406,	/**< ���ڷ����� */
			kNIMResRoomMemberHasExists = 10407,	/**< �Ѿ��ڷ����� */
			kNIMResRoomInviteNotExists = 10408,	/**< ���벻���ڻ��ѹ��� */
			kNIMResRoomInviteHasReject = 10409,	/**< �����Ѿ��ܾ� */
			kNIMResRoomInviteHasAccept = 10410,	/**< �����Ѿ������� */
			kNIMResPeerNimOffline = 10201,	/**< �Է����Ų����� */
			kNIMResPeerPushOffline = 10202,	/**< �Է������಻�ɴ� */
			kNIMResRoomUidConflict = 10417,	/**< uid��ͻ */
			kNIMResRoomMemberExceed = 10419,	/**< ������������ */
			kNIMResRoomMemberHasExistsOtherClient = 10420,	/**< �Ѿ��ڷ����ڣ��Լ��������ˣ� */

			//�ͻ����Զ���Ĵ����
			kNIMLocalRes = 10000,		/**< ֵ���ڸô���ŵĶ��ǿͻ����Զ���Ĵ���š��������������ֵ�� */
			kNIMResRoomLocalNeedRequestAgain = 10001,	/**< �ͻ��˱��ش���ţ���Ҫ������IM��������ȡ����������Ȩ�� */
			kNIMLocalResNetworkError = 10010,	/**< �ͻ��˱��ش���ţ��������������Ҫ��鱾������ */

			//�ͻ����Զ������Ϣ�����
			kNIMLocalResMsgNosUploadCancel = 10200,		/**< (�����ļ���Ϣ����stop_upload_ex)HTTP upload to NOS�ϴ���ͣ */
			kNIMLocalResMsgNosDownloadCancel = 10206,		/**< (�յ��ļ���Ϣ����stop_download_ex)HTTP download from NOS������ͣ */
			kNIMLocalResMsgNosDownloadCheckError = 10207,	/**< �յ��ļ���Ϣ��NOS������ɺ󱾵��ļ�������һ��Ϊ���ص��ļ���С���ļ���Ϣ���� */
			kNIMLocalResMsgFileNotExist = 10404,		/**< ������Դ������ */
			kNIMLocalResParameterError = 10414,		/**< ���ش����룬��������(�յ���Ϣ����Դ���ص�ַ��Ч���޷�����) */
			kNIMLocalResExist = 10417,		/**< ���ش����룬�����Ѿ�����/�ظ�������(�յ���Ϣ��������Դ�Ѵ��ڣ�����Ҫ�ظ�����) */
			kNIMLocalResParaError = 10450,		/**< ����api������Ĳ������� */
			kNIMLocalResMsgSendNosError = 10502,		/**< ������Ϣ���ϴ�NOSʧ�� */
			kNIMLocalResExceedLimit = 10508,		/**< ���ش�����,����������Ч�ڻ���������������� */
			kNIMLocalResCheckMsgDBFailed = 10600,		/**< ������Ϣ��ʷʱ��֤��ݺͼ�����Կ��ͨ�� */
			kNIMLocalResImportMsgDBFailed = 10601,		/**< ������Ϣ��ʷʱд��¼ʧ�� */
			kNIMLocalResTMembersSyncUndone = 10602,		/**< Ⱥ��Ա��ͬ����� */
			//�ͻ����Զ����RTS�����
			kNIMLocalResRtsError = 11100,		/**< rts�Ự δ֪���� */
			kNIMLocalResRtsIdNotExist = 11101,		/**< rts�Ự id������ */
			kNIMLocalResRtsVChatExist = 11417,		/**< rts�Ự ����Ƶ�Ѵ��� */
			kNIMLocalResRtsStatusError = 11501,		/**< rts�Ự ͨ��״̬����ȷ */
			kNIMLocalResRtsChannelNotExist = 11510,		/**< rts�Ự ͨ�������� */

			kNIMResRoomLinkError = 13001,		/**< �����Ӵ��� */
			kNIMResRoomError = 13002,		/**< ������״̬�쳣 */
			kNIMResRoomBlackBeOut = 13003,		/**< �������û���ֹ���� */
			kNIMResRoomBeMuted = 13004,		/**< ������ */
			kNIMResRoomAllMuted = 13006,		/**< �����Ҵ����������״̬,ֻ�й���Ա�ܷ��� */

			//�ͻ����Զ����api��������
			kNIMLocalResAPIErrorInitUndone = 20000,		/**< ��δ��ʼ�����ʼ��δ������� */
			kNIMLocalResAPIErrorLoginUndone = 20001,		/**< ��δ��½���¼δ��� */
			kNIMLocalResAPIErrorLogined = 20002,		/**< �Ѿ���¼ */
			kNIMLocalResAPIErrorVersionError = 20003,		/**< SDK�汾���ԣ����ܻ������������� */
			kNIMLocalResAPIErrorChatroomMixError = 20004,		/**< ������ģʽ���ô��󣬲�֧��ͬʱ�Ե�½״̬������״̬��½������ */
		};
		/** @enum NIMLoginStep ��¼���� */
		enum NIMLoginStep
		{
			kNIMLoginStepLinking = 0,	/**< ��������*/
			kNIMLoginStepLink = 1,	/**< ���ӷ�����*/
			kNIMLoginStepLogining = 2,	/**< ���ڵ�¼*/
			kNIMLoginStepLogin = 3,	/**< ��¼��֤*/
		};
		/** @enum NIMClientType �ͻ������� */
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
		/** @enum NIMKickReason ����ԭ�� */
		enum NIMKickReason
		{
			kNIMKickReasonSameGeneric = 1,  /**< �������͵Ŀͻ��˻���*/
			kNIMKickReasonServerKick = 2,  /**< �������˷����߿ͻ���ָ��*/
			kNIMKickReasonKickBySelfOtherClient = 3,  /**< ���Լ����������ߵ�*/
		};
		/** @enum NIMMultiSpotNotifyType ����¼֪ͨ���� */
		enum NIMMultiSpotNotifyType
		{
			kNIMMultiSpotNotifyTypeImIn = 2,		/**< ֪ͨ�������߶��Լ���¼��*/
			kNIMMultiSpotNotifyTypeImOut = 3,		/**< ֪ͨ�������߶��Լ��˳�*/
		};
		/** @brief ��˵�½�ͻ�����Ϣ */
		struct OtherClientPres
		{
			std::string	app_account_;			/**< �������˺� */
			NIMClientType	client_type_;		/**< �ͻ�������, ��NIMClientType */
			std::string	client_os_;				/**< ��¼ϵͳ����,����ios 6.0.1 */
			std::string	mac_address_;			/**< ��¼�豸��mac��ַ */
			std::string	device_id_;				/**< �豸id��uuid */
			int64_t		login_time_;			/**< ���ε�½ʱ��, ���ȵ�ms */
			std::string custom_data_;			/**< �Զ����ֶ�/
												/** ���캯�� */
			OtherClientPres() : login_time_(0) {}
		};
		/** @brief ��¼����ص���Ϣ */
		struct LoginRes
		{
			NIMResCode res_code_;				/**< ���صĴ�����NIMResCode */
			bool relogin_;						/**< �Ƿ�Ϊ�������� */
			NIMLoginStep	login_step_;		/**< ��¼����NIMLoginStep */
			std::list<OtherClientPres> other_clients_;	/**< �����˵�����״̬�б���¼�ɹ��Ż᷵���ⲿ������ */
			bool retrying_;						/**< SDK�Ƿ������ԣ����Ϊfalse����������Ҫ����¼����ʹ����룬��ȷ���������ֶ������ӿڽ��е�¼���� */
			/** ���캯�� */
			LoginRes() : relogin_(false), retrying_(true) {}
		};
		/** @brief ���߽���ص���Ϣ */
		struct  KickoutRes
		{
			NIMClientType client_type_;			/**< int, �ͻ�������NIMClientType */
			NIMKickReason kick_reason_;			/**< ���صı���ԭ��NIMKickReason */
		};
		/** @brief ��˵�¼�ص���Ϣ */
		struct  MultiSpotLoginRes
		{
			NIMMultiSpotNotifyType	notify_type_;			/**< NIMMultiSpotNotifyType ����¼֪ͨ���� */
			std::list<OtherClientPres> other_clients_;		/**< �����˵�����״̬�б� */
		};
		/** @brief ���˽���ص���Ϣ */
		struct KickOtherRes
		{
			NIMResCode res_code_;					/**< ���صĴ�����NIMResCode */
			std::list<std::string> device_ids_;		/**< �豸id��uuid */
		};









		/** @enum NIMTeamType Ⱥ������ */
		enum NIMTeamType
		{
			kNIMTeamTypeNormal = 0,	/**< ��ͨȺ */
			kNIMTeamTypeAdvanced = 1,	/**< �߼�Ⱥ */
		};

		/** @name Ⱥ����Ϣ Json Keys
		* @{
		*/
		static const char *kNIMTeamInfoKeyID = "tid";			/**< string,Ⱥid,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyName = "name";			/**< string,Ⱥ���� */
		static const char *kNIMTeamInfoKeyType = "type";			/**< int,Ⱥ����(NIMTeamType) */
		static const char *kNIMTeamInfoKeyCreator = "creator";		/**< string Ⱥӵ����ID,ͨ���������SDKά��,��������Ϊֻ����������*/
		static const char *kNIMTeamInfoKeyLevel = "level";			/**< int,�����ѷ������� Ⱥ�ȼ�,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyMemberMaxCount = "member_max_count";			/**< int,�ڴ���Ⱥʱ������Ⱥ������Ա�������ɳ���Ӧ���趨������Ա�������򷵻�414 */
		static const char *kNIMTeamInfoKeyProperty = "prop";			/**< string,Ⱥ����,�������ƣ�6000�ַ� */
		static const char *kNIMTeamInfoKeyValidFlag = "valid";			/**< int,Ⱥ��Ч�Ա��λ,��Ч1,��Ч0,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyMemberCount = "member_count";	/**< int,Ⱥ��Ա����,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyListTime = "list_timetag";	/**< long,Ⱥ�б�ʱ���(����),ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyCreateTime = "create_timetag";	/**< long,Ⱥ����ʱ���(����),ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyUpdateTime = "update_timetag";	/**< long,Ⱥ��Ϣ�ϴθ���ʱ���(����),ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyMemberValid = "member_valid";	/**< int,Ⱥ��Ч�Ա��λ,�ͻ�����,��Ч1,��Ч0,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamInfoKeyIntro = "intro";			/**< string,Ⱥ����,�������ƣ�255�ַ� */
		static const char *kNIMTeamInfoKeyAnnouncement = "announcement";	/**< string,Ⱥ����,�������ƣ�5000�ַ� */
		static const char *kNIMTeamInfoKeyJoinMode = "join_mode";		/**< int,��Ⱥģʽ(NIMTeamJoinMode),Ĭ��ΪkNIMTeamJoinModeNoAuth(0),����Ҫ��֤ */
		static const char *kNIMTeamInfoKeyBits = "bits";			/**< long, Ⱥ����,�����������ע 20161011 by Oleg*/
		static const char *kNIMTeamInfoKeyCustom = "custom";			/**< string, ��������չ�ֶΣ�������洢��͸���� */
		static const char *kNIMTeamInfoKeyServerCustom = "server_custom";	/**< string, ��������������չ�ֶΣ���������ֻ��ͨ���������ӿ����ã��Կͻ���ֻ���� */
		static const char *kNIMTeamInfoKeyIcon = "icon";			/**< string, Ⱥͷ��,�������ƣ�1024�ַ� */
		static const char *kNIMTeamInfoKeyBeInviteMode = "be_invite_mode"; /**< int, ��������ͬ�ⷽʽ�����Ա���ֻ��Ⱥ������Ա�����޸�,Ĭ��kNIMTeamBeInviteModeNeedAgree(0)/kNIMTeamBeInviteModeNotNeedAgree(1) */
		static const char *kNIMTeamInfoKeyInviteMode = "invite_mode";	/**< int, ˭��������������Ⱥ�����Ա���ֻ��Ⱥ������Ա�����޸�,Ĭ��kNIMTeamInviteModeManager(0)/kNIMTeamInviteModeEveryone(1) */
		static const char *kNIMTeamInfoKeyUpdateInfoMode = "update_info_mode";/**< int, ˭�����޸�Ⱥ���ϣ����Ա���ֻ��Ⱥ������Ա�����޸�,Ĭ��kNIMTeamUpdateInfoModeManager(0)/kNIMTeamUpdateInfoModeEveryone(1) */
		static const char *kNIMTeamInfoKeyUpdateCustomMode = "update_custom_mode";/**< int, ˭���Ը���Ⱥ�Զ������ԣ����Ա���ֻ��Ⱥ������Ա�����޸�,Ĭ��kNIMTeamUpdateCustomModeManager(0)/kNIMTeamUpdateCustomModeEveryone(1) */
		static const char *kNIMTeamInfoKeyMuteAll = "mute_all";		/**< int, ȺȫԱ���Ա�� 0:δ���ԣ�1:����, ������ֻ�� �޷����� */
		static const char *kNIMTeamInfoKeyMuteType = "mute_type";		/**<NIMTeamMuteType, Ⱥ����0������ 1��ͨ��Ա���� 3ȫ������ ����Ⱥ�� �����߿���ͨ�����ø����Ե���Ⱥ����״̬*/
		/** @}*/ //Ⱥ����ϢJson Keys


		/** @name Ⱥ���Ա��Ϣ Json Keys
		* @{
		*/
		static const char *kNIMTeamUserKeyID = "tid";			/**< string,Ⱥid,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamUserKeyAccID = "accid";			/**< string,Ⱥ��Աid,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamUserKeyType = "type";			/**< int,Ⱥ��Ա����(NIMTeamUserType),Ĭ��kNIMTeamUserTypeNomal(0) */
		static const char *kNIMTeamUserKeyNick = "nick";			/**< string,Ⱥ��Ա�ǳ� */
		static const char *kNIMTeamUserKeyBits = "bits";			/**< long,Ⱥ��Ա����,λ����(NIMTeamBitsConfigMask) */
		static const char *kNIMTeamUserKeyValidFlag = "valid";			/**< int,Ⱥ��Ա��Ч�Ա��λ,��Ч1,��Ч0,ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamUserKeyCreateTime = "create_timetag";	/**< long,��Ⱥʱ���(����),ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamUserKeyUpdateTime = "update_timetag";	/**< long,Ⱥ��Ա��Ϣ�ϴθ���ʱ���(����),ͨ���������SDKά��,��������Ϊֻ���������� */
		static const char *kNIMTeamUserKeyCustom = "custom";			/**< string,Ⱥ��Ա�Զ�����չ�ֶ�,����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ��� */
		static const char *kNIMTeamUserKeyMute = "mute";			/**< int,�Ƿ񱻽���,0-�ǽ���(Ĭ��),1-���� */
		static const char *kNIMTeamUserKeyInvitorAccID = "invitor_accid";			/**< string,�����ߵ�accid ������Ⱥ��ʱΪ�գ���δ���й���ʼ��Ϊ" " */
		/** @}*/ //Ⱥ���Ա��ϢJson Keys

		/** @enum NIMTeamJoinMode Ⱥ����������� */
		enum NIMTeamJoinMode
		{
			kNIMTeamJoinModeNoAuth = 0,		/**< ������֤ */
			kNIMTeamJoinModeNeedAuth = 1,		/**< ��Ҫ��֤ */
			kNIMTeamJoinModeRejectAll = 2,		/**< �ܾ���������Ⱥ */
		};
		/** @enum NIMTeamBeInviteMode ��������ͬ�ⷽʽ */
		enum NIMTeamBeInviteMode
		{
			kNIMTeamBeInviteModeNeedAgree = 0,	/**< ��Ҫͬ�� */
			kNIMTeamBeInviteModeNotNeedAgree = 1,	/**< ����Ҫͬ�� */
		};

		/** @enum NIMTeamInviteMode ˭��������������Ⱥ */
		enum NIMTeamInviteMode
		{
			kNIMTeamInviteModeManager = 0,	/**< ����Ա */
			kNIMTeamInviteModeEveryone = 1,	/**< ������ */
		};

		/** @enum NIMTeamUpdateInfoMode ˭�����޸�Ⱥ���� */
		enum NIMTeamUpdateInfoMode
		{
			kNIMTeamUpdateInfoModeManager = 0,	/**< ����Ա */
			kNIMTeamUpdateInfoModeEveryone = 1,	/**< ������ */
		};

		/** @enum NIMTeamUpdateCustomMode ˭���Ը���Ⱥ�Զ������� */
		enum NIMTeamUpdateCustomMode
		{
			kNIMTeamUpdateCustomModeManager = 0,	/**< ����Ա */
			kNIMTeamUpdateCustomModeEveryone = 1,	/**< ������ */
		};
		/** @enum NIMTeamMuteType Ⱥ��ϢkNIMTeamInfoKeyMuteType�����ö��� */
		enum NIMTeamMuteType
		{
			kNIMTeamMuteTypeNone = 0,	/**< ������ */
			kNIMTeamMuteTypeNomalMute = 1,	/**< ��ͨ��Ա���� */
			kNIMTeamMuteTypeAllMute = 3,	/**< ȫ������ */
		};
		/** @enum NIMTeamBitsConfigMask Ⱥ���Ա��ϢBits����kNIMTeamUserKeyBits�����ö��� */
		enum NIMTeamBitsConfigMask
		{
			kNIMTeamBitsConfigMaskMuteNone = 0,	/**< �������� bits 0000b*/
			kNIMTeamBitsConfigMaskMuteNotify = 1,	/**< �ر����� bits 0001b*/
			kNIMTeamBitsConfigMaskOnlyAdmin = 2,	/**< ֻ���չ���Ա��Ϣ bits 0010b ����Ⱥ��ǰ��֧�ָ�ѡ��*/
		};
		/** @enum NIMTeamUserType Ⱥ��Ա���� */
		enum NIMTeamUserType
		{
			kNIMTeamUserTypeNomal = 0,		/**< ��ͨ��Ա */
			kNIMTeamUserTypeCreator = 1,		/**< ������ */
			kNIMTeamUserTypeManager = 2,		/**< ����Ա */
			kNIMTeamUserTypeApply = 3,		/**< ��������û� */
			kNIMTeamUserTypeLocalWaitAccept = 100,	/**< ���ؼ�¼�ȴ�������Ⱥ���û� */
		};

		/** @enum NIMNotificationId ֪ͨ���� */
		enum NIMNotificationId
		{
			kNIMNotificationIdTeamInvite = 0,			/**< ��ͨȺ���ˣ�{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attachΪ��ѡ�ֶΣ���ΪӦ���Զ�����չ�ֶ�,����ǰ��Ҫ�ж���û������ֶ� */
			kNIMNotificationIdTeamKick = 1,			/**< ��ͨȺ���ˣ�{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attachΪ��ѡ�ֶΣ���ΪӦ���Զ�����չ�ֶ�,����ǰ��Ҫ�ж���û������ֶ� */
			kNIMNotificationIdTeamLeave = 2,			/**< �˳�Ⱥ��{"id" : "a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamUpdate = 3,			/**< Ⱥ��Ϣ���£�{"team_info":team_info,"user_namecards":["namecard1", "namecard2"]} //Ⱥ����Ϣ(Keys SEE MORE `nim_team_def.h` ��Ⱥ����Ϣ Json Keys��)*/
			kNIMNotificationIdTeamDismiss = 4,			/**< Ⱥ��ɢ��{"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamApplyPass = 5,			/**< �߼�Ⱥ�������ɹ���{"id":"a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamOwnerTransfer = 6,			/**< �߼�Ⱥ�ƽ�Ⱥ����{"id":"a1", "leave" : bool,"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamAddManager = 7,			/**< ���ӹ���Ա��{"ids":["a1","a2"],"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamRemoveManager = 8,			/**< ɾ������Ա��{"ids":["a1","a2"],"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamInviteAccept = 9,			/**< �߼�Ⱥ���������Ⱥ��{"id":"a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdTeamMuteMember = 10,			/**< ����/���Ⱥ��Ա��{"user_namecards":["namecard1", "namecard2"],"team_info":team_info,"id":"a1","mute":1-����,0-���} */

			kNIMNotificationIdNetcallMiss = 101,			/**< δ�ӵ绰,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdNetcallBill = 102,			/**< ����,{"calltype":2,"channel":6146077129466446197,"duration":8,"ids":["id1","id2"],"time":1430995117398}*/

			//����������ͬ��Э�鷵�صĽ��
			kNIMNotificationIdTeamSyncCreate = 1000,			/**< ����Ⱥ {"team_info" : team_info} //Ⱥ����Ϣ(Keys SEE MORE `nim_team_def.h` ��Ⱥ����Ϣ Json Keys��)*/
			kNIMNotificationIdTeamMemberChanged = 1001,			/**< Ⱥ��Ա���{"team_member" : team_member_info} //Ⱥ���Ա��Ϣ���������Լ���(Keys SEE MORE `nim_team_def.h` ��Ⱥ���Ա��Ϣ Json Keys��)*/
			kNIMNotificationIdTeamSyncUpdateMemberProperty = 1002,	/**< ͬ��֪ͨ���޸�Ⱥ��Ա���ԣ��������Լ��Ļ���˵ģ�{"team_member" : team_member_info} //Ŀǰֻ��kNIMTeamUserKeyNick��kNIMTeamUserKeyBits (Keys SEE MORE `nim_team_def.h` ��Ⱥ���Ա��Ϣ Json Keys��)*/

			//���ط���Ĳ���֪ͨAPP�ϲ�
			kNIMNotificationIdLocalCreateTeam = 2000,			/**< ���ز�������Ⱥ {"ids" : ["a1", "a2"]}*/
			kNIMNotificationIdLocalApplyTeam = 2001,			/**< ���ز����������Ⱥ {}*/
			kNIMNotificationIdLocalRejectApply = 2002,			/**< ���ز����ܾ����� {"id":"a1"}*/
			kNIMNotificationIdLocalRejectInvite = 2003,			/**< ���ز����ܾ����� {"id":"a1"}*/
			kNIMNotificationIdLocalUpdateMemberProperty = 2004,		/**< ���ز�������Ⱥ��Ա����  {"team_member" : team_member_info} */
			kNIMNotificationIdLocalUpdateOtherNick = 2005,			/**< ���ز�����������nickname {}*/
			kNIMNotificationIdLocalGetTeamInfo = 2006,			/**< ���ز�����ȡȺ��Ϣ {"team_info":team_info} //Ⱥ����Ϣ(Keys SEE MORE `nim_team_def.h` ��Ⱥ����Ϣ Json Keys��)*/
			kNIMNotificationIdLocalGetTeamList = 2007,			/**< ���ز�����ȡȺ��Ա��Ϣ����*/
			kNIMNotificationIdLocalMuteMember = 2008,			/**< ���ز�����Ⱥ��Ա���� {"id":"a1", "mute":1-����,0-���} */
			kNIMNotificationIdLocalMute = 2009,			/**< ���ز�����Ⱥ���� {} */
			kNIMNotificationIdLocalGetTeamMsgUnreadCount = 2010,	/**< ��ȡȺ��Ϣδ���� {[{"client_msg_id":"", "count":int, "read_accid":"��ǰ�Ѷ���Ա��accid"},...]}*/
			kNIMNotificationIdLocalGetTeamMsgUnreadList = 2011,		/**< ��ȡȺ��Ϣδ���б� {"client_msg_id":"", "read":["id1",...], "unread":["id2",...]}*/

			//Netcall���ز���֪ͨ
			kNIMNotificationIdLocalNetcallReject = 3103,			/**< �ܾ��绰,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdLocalNetcallNoResponse = 3104,			/**< ��Ӧ��δ��ͨ�绰,{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/
			kNIMNotificationIdLocalNetcallCanceled = 3105,	/**< δ��ͨǰ���з��Ҷϣ�{"calltype":1,"channel":6146078138783760761,"from":"id1","ids":["id1","id2"],"time":1430995380471}*/

			kNIMNotificationIdSuperTeamInvite = 401,			/**< ����Ⱥ���ˣ�{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attachΪ��ѡ�ֶΣ���ΪӦ���Զ�����չ�ֶ�,����ǰ��Ҫ�ж���û������ֶ� */
			kNIMNotificationIdSuperTeamKick = 402,			/**< ����Ⱥ���ˣ�{"ids":["a1", "a2"],"user_namecards":["namecard1", "namecard2"], "attach" : ""} attachΪ��ѡ�ֶΣ���ΪӦ���Զ�����չ�ֶ�,����ǰ��Ҫ�ж���û������ֶ� */
			kNIMNotificationIdSuperTeamLeave = 403,			/**< �˳�����Ⱥ��{"id" : "a1","user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdSuperTeamUpdate = 404,			/**< ����ȺȺ��Ϣ���£�{"team_info":team_info,"user_namecards":["namecard1", "namecard2"]} //Ⱥ����Ϣ(Keys SEE MORE `nim_team_def.h` ��Ⱥ����Ϣ Json Keys��)*/
			kNIMNotificationIdSuperTeamDismiss = 405,			/**< ����Ⱥ��ɢ��{"user_namecards":["namecard1", "namecard2"]}*/
			kNIMNotificationIdSuperTeamOwnerTransfer = 406,    /**< ����Ⱥ�ƽ�Ⱥ����{"id":"a1","uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamAddManager = 407,	/**< ����Ⱥ���ӹ���Ա��{"ids":["a1","a2"],"uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamRemoveManager = 408,    /**< ����Ⱥɾ������Ա��{"ids":["a1","a2"],"uinfos":["uinfo1", "uinfo2"]}*/
			kNIMNotificationIdSuperTeamMuteMember = 409,	/**< ����Ⱥ����/���Ⱥ��Ա��{"uinfos":["uinfo1", "uinfo2"],��tinfo��:tinfo,"id":"a1","mute":1-����,0-���}*/
		};
		static const char *kNIMNotificationKeyId = "id";				/**< int, ��NIMNotificationId */
		static const char *kNIMNotificationKeyData = "data";			/**< json object ��������5�ֿ��ܵ����ݽṹ*/
		static const char *kNIMNotificationKeyDataIds = "ids";			/**< string array */
		static const char *kNIMNotificationKeyDataInvalidIds = "invalid_ids";		/**< string array */
		static const char *kNIMNotificationKeyDataId = "id";				/**< string */
		static const char *kNIMNotificationKeyDataLeave = "leave";			/**< bool */
		static const char *kNIMNotificationKeyDataMute = "mute";			/**< int */
		static const char *kNIMNotificationKeyTeamInfo = "team_info";		/**< string, team_info Ⱥ����Ϣ Json Keys*/
		static const char *kNIMNotificationKeyTeamMember = "team_member";	/**< string, team_member_property Ⱥ���Ա��Ϣ Json Keys*/
		static const char *kNIMNotificationKeyUserNameCards = "name_cards";	/**< json string array, �����ߺͱ�������˫���� �û���Ƭ Json Keys*/


		//Э�鶨��
		static const char *kNIMNameCardKeyAccid = "accid";	/**< string �ʺ�*/
		static const char *kNIMNameCardKeyName = "name";	/**< string �ǳ�*/
		static const char *kNIMNameCardKeyIcon = "icon";	/**< string ͷ��*/
		static const char *kNIMNameCardKeySign = "sign";	/**< string ǩ��*/
		static const char *kNIMNameCardKeyGender = "gender";	/**< int �Ա�*/
		static const char *kNIMNameCardKeyEmail = "email";	/**< string ����*/
		static const char *kNIMNameCardKeyBirth = "birth";	/**< string ����*/
		static const char *kNIMNameCardKeyMobile = "mobile";	/**< string �绰*/
		static const char *kNIMNameCardKeyEx = "ex";		/**< string ��չ�ֶ�, ����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ���*/
		static const char *kNIMNameCardKeyCreateTime = "create_timetag";	/**< long ����ʱ��� ����*/
		static const char *kNIMNameCardKeyUpdateTime = "update_timetag";	/**< long ����ʱ��� ����*/
		/** @}*/ //�û���Ƭ Json Keys

		//Э�鶨��
		static const char *kNIMSpecialRelationKeyAccid = "accid";			/**< string, �û��ʺ� */
		static const char *kNIMSpecialRelationKeyIsMute = "is_mute";		/**< bool, �Ǿ����ʺ� */
		static const char *kNIMSpecialRelationKeyIsBlackList = "is_black";		/**< bool, �Ǻ������ʺ� */
		static const char *kNIMSpecialRelationKeyCreateTime = "create_timetag";	/**< long, ��¼����ʱ�� */
		static const char *kNIMSpecialRelationKeyUpdateTime = "update_timetag";	/**< long, ��¼����ʱ�� */
		/** @}*/ //�û������ϵ�������������������� Json Keys




		/** @name �¼���Ϣ Json Keys
		* @{
		*/
		static const char *kNIMEventEventType = "event_type";			/**< int,�¼����� */
		static const char *kNIMEventEventValue = "event_value";		/**< int,�¼�ֵ */
		static const char *kNIMEventMsgIdClient = "msgid_client";		/**< string,�ͻ������ɵ���Ϣid */
		static const char *kNIMEventConfig = "config";				/**< string,�û��Զ����¼���չ���ԣ��4K */
		static const char *kNIMEventTTL = "ttl";				/**< long,�¼���Ч�ڣ���λ���룬ʱ�䷶Χ��60s��7�� */
		static const char *kNIMEventBroadcastType = "broadcast_type";		/**< int,�¼��㲥���ͣ�1:������ 2:���ߺ����� */
		static const char *kNIMEventSyncSelf = "sync_seft";			/**< int,0:��ͬ�����Լ��������ˣ�1��ͬ�����Լ��������� */

		static const char *kNIMEventTTLType = "ttltype";			/**< int,TtlTypeö��ֵ(�ͻ��˲���д) */
		static const char *kNIMEventDurable = "durable";			/**< int,�Ƿ���Ҫ�־û�(��ѡ�ֶ�)��Ĭ��Ϊ��Ҫ�־û�,0:����Ҫ�־û���1����Ҫ�־û�(�ͻ��˲���д) */
		static const char *kNIMEventEventTime = "event_time";			/**< long,�¼�������ʱ���������������(�ͻ��˲���д) */
		static const char *kNIMEventMsgIdServer = "msgid_server";		/**< string,��������ɵ���Ϣid(�ͻ��˲���д) */
		static const char *kNIMEventClientType = "client_type";		/**< int,���Ϳͻ�������(�ͻ��˲���д) */
		static const char *kNIMEventNimConfig = "nim_config";			/**< string,Ԥ�����¼�����չ�ֶΣ�����״̬�¼������ߵĿͻ�������Json */
		static const char *kNIMEventMultiConfig = "multi_config";		/**< string,���������Ϣ�ֶΣ�JSON��ʽ{"clent_type":"clent_config","1":"xxx","2":"xxx"} */

		static const char *kNIMEventPublisherAccid = "publisher_accid";	/**< string,�¼������ߵ�accid(�ͻ��˲���д) */
		static const char *kNIMEventConsid = "consid";				/**< string,�����豸id(�ͻ��˲���д) */
		/** @}*/ //�¼���ϢJson Keys

		/** @name �¼�������Ϣ Json Keys
		* @{
		*/
		static const char *kNIMEventSubscribeEventType = "type";				/**< int,�¼����� */
		static const char *kNIMEventSubscribeTTL = "ttl";				/**< long,������Ч�ڣ���λ���룬��Χ��60s��30�� */
		static const char *kNIMEventSubscribeSyncEvent = "syncevent";			/**< int,���ĺ��Ƿ�����ͬ�������¼� */

		static const char *kNIMEventSubscribePublisherAccid = "publisher_accid";	/**< string,�������ˣ��¼������ˣ���accid(�ͻ��˲���д) */
		static const char *kNIMEventSubscribeSubscribeAccid = "subscribe_accid";	/**< string,�����˵�accid(�ͻ��˲���д) */
		static const char *kNIMEventSubscribeSubscribeTime = "subscribe_time";		/**< long,����ʱ���(�ͻ��˲���д) */
		/** @}*/ //�¼�������ϢJson Keys

		/** @name ����״̬�¼�kNIMEventNimConfig�ֶ�Json Keys��ֻ��������״̬�¼�
		* @{
		*/
		static const char *kNIMEventNimConfigOnlineClient = "online";		/**< string,Ԥ�����¼�����չ�ֶ��е����ߵĿͻ������� */
		/** @}*/ //����״̬�¼�kNIMEventNimConfig�ֶ�Json Keys��ֻ��������״̬�¼�

		/** @enum NIMEventBroadcastType �¼��㲥���� */
		enum NIMEventBroadcastType
		{
			kNIMEventBroadcastTypeOnline = 1, /**< ������ */
			kNIMEventBroadcastTypeAll = 2, /**< ���ߺ����� */
		};

		/** @enum NIMEventSyncType �¼�ͬ������ */
		enum NIMEventSyncType
		{
			kNIMEventSyncTypeNoSelf = 0, /**< �¼���ͬ�����Լ������� */
			kNIMEventSyncTypeSelf = 1, /**< �¼�ͬ�����Լ������� */
		};

		/** @enum NIMEventSubscribeSyncEventType ���ĵ��¼���ͬ������ */
		enum NIMEventSubscribeSyncEventType
		{
			kNIMEventSubscribeSyncTypeUnSync = 0, /**< ���ĺ�ͬ�������¼� */
			kNIMEventSubscribeSyncTypeSync = 1, /**< ���ĺ�����ͬ�������¼� */
		};

		/** @enum NIMEventType ������Ԥ������¼����� */
		enum NIMEventType
		{
			kNIMEventTypeOnlineState = 1, /**< ����״̬�¼�(�ͻ��˿ɷ���) */
			kNIMEventTypeSyncEvent = 2, /**< ͬ���������¼����¼�(�ͻ��˲��ɷ���) */
			kNIMEventTypeCustom = 100000, /**< ����������1��99999���¼����ͣ��ͻ����Զ����¼����������99999 */
		};

		/** @enum NIMEventOnlineStateValue ����״̬�¼�ֵ */
		enum NIMEventOnlineStateValue
		{
			kNIMEventOnlineStateValueLogin = 1, /**< ��¼ */
			kNIMEventOnlineStateValueLogout = 2, /**< �ǳ� */
			kNIMEventOnlineStateValueDisconnect = 3, /**< �Ͽ����� */
			kNIMEventOnlineStateValueCustom = 10000, /**< ����״̬�¼�����������1��9999���¼�ֵ���ͻ����Զ����¼�ֵ�����9999 */
			kNIMEventOnlineStateValueUpdateConfig = kNIMEventOnlineStateValueCustom + 1	/**< �Լ��������˸������Լ��˵�multi_config��Ϣ */
		};


		static const char *kNIMFriendKey = "list";	/**< ���Ѽ�� json array, */

		/** @name ���Ѽ�� Json Keys
		* ���� {"list" : [{"accid" : "litianyi01","beflag" : 1,"bits" : 0,"create_timetag" : 1439871983864,"flag" : 1,"source" : 0,"update_timetag" : 1439872006079}, ...]}
		* @{
		*/
		//Э�鶨��
		static const char *kNIMFriendKeyAccid = "accid";  /**< string, �����ʺ�*/
		static const char *kNIMFriendKeyFlag = "flag";	/**< NIMFriendFlag, ���ѹ�ϵ���޸�ʱ��Ҫͬ�����·�����ѹ�ϵbeflag */
		static const char *kNIMFriendKeyBeFlag = "beflag"; /**< NIMFriendFlag, ������ѹ�ϵ */
		static const char *kNIMFriendKeySource = "source"; /**< NIMFriendSource, ������Դ */
		static const char *kNIMFriendKeyAlias = "alias";	/**< string, ��ע�� */
		static const char *kNIMFriendKeyBits = "bits";	/**< long, ��չ�ֶ�,λ������ */
		static const char *kNIMFriendKeyEx = "ex";		/**< string, ��չ�ֶ�,����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ��� */
		static const char *kNIMFriendKeyCreateTime = "create_timetag"; /**< long, ����ʱ���(ms)*/
		static const char *kNIMFriendKeyUpdateTime = "update_timetag"; /**< long, ����ʱ���(ms)*/
		static const char *kNIMFriendServerEx = "server_ex"; /**< string, �������չ�ֶΣ����ֶοͻ���sdkֻ���������api��д*/
		static const char *kNIMFriendDeleteAlias = "delete_alias"; /**< bool, ɾ������ʱ�Ƿ�ɾ����ע��Ϣ*/




		/** @enum NIMDataSyncType ����ͬ������ */
		enum NIMDataSyncType
		{
			kNIMDataSyncTypeUnreadMsg = 2,		/**< δ����Ϣͬ��*/
			kNIMDataSyncTypeTeamInfo = 3,		/**< ����Ⱥ����Ϣͬ��, json_attachmentΪͬ������team_info json array*/
			kNIMDataSyncTypeRoamMsg = 7,		/**< ������Ϣͬ��,ÿ���Ựͬ����������Ϣ���ᴥ������֪ͨ*/
			kNIMDataSyncTypeSuperTeamInfo = 22,		/**< ����Ⱥ����Ϣͬ��, json_attachmentΪͬ������team_info json array*/
			kNIMDataSyncTypeTeamUserList = 1000,		/**< Ⱥ��Ա�б�ͬ��, json_attachmentΪͬ������tid*/
			kNIMDataSyncTypeAllTeamUserList = 1001,		/**< ����Ⱥ�ĳ�Ա�б�ͬ�����, json_attachmentΪ��*/
			kNIMDataSyncTypeSuperTeamUserList = 1010,		/**< ����Ⱥ��Ա�б�ͬ��, json_attachmentΪͬ������tid*/
			kNIMDataSyncTypeAllSuperTeamUserList = 1011,		/**< ���г���Ⱥ�ĳ�Ա�б�ͬ�����, json_attachmentΪ��*/

		};

		/** @enum NIMDataSyncStatus ����ͬ��״̬ */
		enum NIMDataSyncStatus
		{
			kNIMDataSyncStatusComplete = 1,		/**< ͬ�����*/
		};

		static const char *kNIMSysMsgKeyLocalRescode = "rescode";			/**< int, ���صĴ�����,��NIMResCode */
		static const char *kNIMSysMsgKeyLocalFeature = "feature";			/**< int, ���ض������Ϣ����,��NIMMessageFeature */
		static const char *kNIMSysMsgKeyLocalUnreadCount = "unread_count";		/**< int, ÿ�δ��ص��ǵ�ǰ���ܵ�δ���� */
		static const char *kNIMSysMsgKeyLocalContent = "content";			/**< json string, Э�鶨���ϵͳ��Ϣ�ṹ */
		/** @}*/ //����ϵͳ��ϢJson Keys�����ض���

		static const char *kNIMSysMsglogQueryKeyCount = "count";				/**< int, ��ѯ�õ������� */
		static const char *kNIMSysMsglogQueryKeyUnreadCount = "unread_count";	/**< int, ÿ�β�ѯ���ص��ǵ�ǰ���ܵ�δ���� */
		static const char *kNIMSysMsglogQueryKeyContent = "content";			/**< json object array Э�鶨���ϵͳ��Ϣ�ṹ */

		/** @name ϵͳ��Ϣ/�ͻ����Զ���֪ͨ�ṹ Json Keys��Э�鶨��
		* @{
		*/
		static const char *kNIMSysMsgKeyTime = "msg_time";			/**< long,		ʱ���,ѡ�� */
		static const char *kNIMSysMsgKeyType = "msg_type";			/**< int,		֪ͨ����,NIMSysMsgType,���� */
		static const char *kNIMSysMsgKeyToAccount = "to_account";			/**< string,	������id,����Ǹ���,���ǶԷ��û�id,�����Ⱥ,����Ⱥid,���� */
		static const char *kNIMSysMsgKeyFromAccount = "from_account";		/**< string,	�Լ�id,ѡ�� */
		static const char *kNIMSysMsgKeyMsg = "msg";				/**< string,	ֻ���ֶΣ�SDK��ת�����ֶ� */
		static const char *kNIMSysMsgKeyAttach = "attach";				/**< string,	��Ϣ����,�涨�ǿ��Խ���ΪJson��ʽ���ַ���������Ϊ�Ǹ�ʽ����ʽ */
		static const char *kNIMSysMsgKeyMsgId = "msg_id";				/**< long,		��������Ϣid���Զ���֪ͨ��Ϣ,������0��,���ͷ�����Ҫ��д*/
		static const char *kNIMSysMsgKeyLocalStatus = "log_status";			/**< int,		���ض����ϵͳ��Ϣ״̬,��NIMSysMsgStatus,���ͷ�����Ҫ��д*/
		static const char *kNIMSysMsgKeyLocalClientMsgId = "client_msg_id";		/**< string,	���ض������Ϣid,���ͷ�����,����ʹ��uuid */
		static const char *kNIMSysMsgKeyCustomSaveFlag = "custom_save_flag";	/**< int,		(��ѡ)�Զ���֪ͨ��Ϣ�Ƿ������:0-���棨ֻ���������û���,1-�棨�ɷ��������û���*/
		static const char *kNIMSysMsgKeyCustomApnsText = "custom_apns_text";	/**< string,	(��ѡ)�Զ���֪ͨ��Ϣ�����ı�������������*/
		static const char *kNIMSysMsgKeyPushPayload = "push_payload";		/**< json string, (��ѡ)�������Զ�����������ԣ�����Ϊ���Խ���ΪJson�ķǸ�ʽ�����ַ���������2048 */
		static const char *kNIMSysMsgKeyPushEnable = "push_enable";		/**< int,		(��ѡ)�Ƿ���Ҫ����, 0:����Ҫ,1:��Ҫ,Ĭ��1 */
		static const char *kNIMSysMsgKeyPushNeedBadge = "push_need_badge";	/**< int,		(��ѡ)�����Ƿ�Ҫ����Ϣ����(�Ǳ�)��0:����Ҫ��1:��Ҫ��Ĭ��1 */
		static const char *kNIMSysMsgKeyPushNeedPrefix = "push_prefix";		/**< int,		(��ѡ)������Ҫǰ׺��0������Ҫ��1����Ҫ��Ĭ��0 */
		static const char *kNIMSysMsgKeyAntiSpamEnable = "anti_spam_enable";	/**< int, (������ʱ������)�Ƿ���Ҫ���׶ܷ�����, 0:����Ҫ,1:��Ҫ, Ĭ��0 */
		static const char *kNIMSysMsgKeyAntiSpamContent = "anti_spam_content";	/**< string, (������ʱ������)(��ѡ)�������Զ���ķ������ֶ� */

		/** @enum NIMSysMsgStatus ϵͳ��Ϣ״̬ */
		enum NIMSysMsgStatus
		{
			kNIMSysMsgStatusNone = 0,		/**< Ĭ��,δ�� */
			kNIMSysMsgStatusPass = 1,		/**< �յ���Ϣ,ͨ�� */
			kNIMSysMsgStatusDecline = 2,		/**< �յ���Ϣ,�ܾ� */
			kNIMSysMsgStatusRead = 3,		/**< �յ���Ϣ,�Ѷ� */
			kNIMSysMsgStatusDeleted = 4,		/**< ��ɾ */
			kNIMSysMsgStatusInvalid = 5,		/**< ��ʧЧ */
		};

		/** @enum NIMSysMsgType ϵͳ��Ϣ�������� */
		enum NIMSysMsgType
		{
			kNIMSysMsgTypeTeamApply = 0,		/**< ������Ⱥ  */
			kNIMSysMsgTypeTeamReject = 1,		/**< �ܾ���Ⱥ���� */
			kNIMSysMsgTypeTeamInvite = 2,		/**< �����Ⱥ kNIMSysMsgKeyAttach : {"team_info":team_info, "attach" : ""} attachΪ��ѡ�ֶΣ���ΪӦ���Զ�����չ�ֶ�,����ǰ��Ҫ�ж���û������ֶ�, Ⱥ����Ϣ(Keys SEE MORE `nim_team_def.h` ��Ⱥ����Ϣ Json Keys��) */
			kNIMSysMsgTypeTeamInviteReject = 3,		/**< �ܾ����� */
			kNIMSysMsgTypeFriendAdd = 5,		/**< �Ӻ���, kNIMSysMsgKeyAttach: {"vt":verifyType} */
			kNIMSysMsgTypeFriendDel = 6,		/**< ɾ������ */
			kNIMSysMsgTypeCustomP2PMsg = 100,		/**< ��Ե�͸����Ϣ��͸����Ϣ�����ݷŵ�kNIMSysMsgKeyAttach��,SDK�Ը�����Ϣ������δ����, ��ʹkNIMSysMsgKeyPushNeedBadgeΪ1 */
			kNIMSysMsgTypeCustomTeamMsg = 101,		/**< Ⱥ͸����Ϣ��͸����Ϣ�����ݷŵ�kNIMSysMsgKeyAttach��,SDK�Ը�����Ϣ������δ����, ��ʹkNIMSysMsgKeyPushNeedBadgeΪ1 */
			kNIMSysMsgTypeCustomSuperTeamMsg = 103,		/**< ����Ⱥ͸����Ϣ��͸����Ϣ�����ݷŵ�kNIMSysMsgKeyAttach��,SDK�Ը�����Ϣ������δ����, ��ʹkNIMSysMsgKeyPushNeedBadgeΪ1 */
			kNIMSysMsgTypeUnknown = 1000,		/**< δ֪���ͣ�����ʹ�ã�����ʱ��ʹ�ã���ΪĬ�� */
		};

	









		/** @name �Ự�б��Json Keys
		* @{
		*/
		static const char *kNIMSessionListCount = "count";				/**< int, �Ự�б������� */
		static const char *kNIMSessionListUnreadCount = "unread_counts";	/**< int, ��δ���� */
		static const char *kNIMSessionListContent = "content";			/**< json object (Keys as follows), �Ự�б������� */
		static const char *kNIMSessionId = "id";					/**< string, �Ựid */
		static const char *kNIMSessionType = "type";				/**< int, �Ự����(��NIMSessionType ����0 Ⱥ��1 ����Ⱥ5 etc) */
		static const char *kNIMSessionUnreadCount = "unread_count";		/**< int, ������Ϣ��ʷ�иûỰδ����Ϣ���� */
		static const char *kNIMSessionCommand = "command";			/**< int, �Ự���������NIMSessionCommand */
		static const char *kNIMSessionMsgClientID = "msg_client_id";		/**< string, ������Ϣ��ʷ�иûỰ���һ����Ϣ�Ŀͻ���IDΨһ��ʶ������Ϣuuid */
		static const char *kNIMSessionMsgFromAccount = "msg_from_account";	/**< string, ������Ϣ��ʷ�иûỰ���һ����Ϣ�ķ��ͷ��ʺ� */
		static const char *kNIMSessionMsgTime = "msg_time";			/**< long, ������Ϣ��ʷ�иûỰ���һ����Ϣ��ʱ�� */
		static const char *kNIMSessionMsgType = "msg_type";			/**< int, ������Ϣ��ʷ�иûỰ���һ����Ϣ������ ��NIMMessageType*/
		static const char *kNIMSessionMsgBody = "msg_body";			/**< string, ������Ϣ��ʷ�иûỰ���һ����Ϣ������ */
		static const char *kNIMSessionMsgAttach = "msg_attach";			/**< string, ������Ϣ��ʷ�иûỰ���һ����Ϣ��attach */
		static const char *kNIMSessionMsgStatus = "msg_status";			/**< int, ������Ϣ��ʷ�иûỰ���һ����Ϣ��״̬����NIMMsgLogStatus */
		static const char *kNIMSessionMsgSubStatus = "msg_sub_status";		/**< int, ������Ϣ��ʷ�иûỰ���һ����Ϣ����״̬����NIMMsgLogSubStatus */
		static const char *kNIMSessionLastUpdatedMsg = "last_updated_msg";	/**< bool, (����)��Ϣ���������ʱ�Ƿ������һ���������Ϣ */
		static const char *kNIMSessionOnTop = "top";				/**< bool, �Ƿ��ö� */
		static const char *kNIMSessionExtendedData = "extend_data";		/**< string, ������չ�ֶ�, ��4096 */
		static const char *kNIMSessionRobotFlag = "robot_session";		/**< bool, �Ƿ�Ϊ�����˻Ự, Ĭ��Ϊfalse */
		/** @}*/ //�Ự�б��Json Keys

		/** @enum NIMSessionType �Ự���� */
		enum NIMSessionType
		{
			kNIMSessionTypeP2P = 0,			/**< ���ˣ�����Ե� */
			kNIMSessionTypeTeam = 1,			/**< Ⱥ�� */
			kNIMSessionTypeSuperTeam = 5,			/**< ����Ⱥ�� */
		};

		/** @enum NIMSessionCommand �Ự�������� */
		enum NIMSessionCommand
		{
			kNIMSessionCommandAdd = 0,	/**< ��ӻỰ�� */
			kNIMSessionCommandRemove = 1,	/**< ɾ�������Ự�� */
			kNIMSessionCommandRemoveAll = 2,	/**< ɾ�����лỰ�� */
			kNIMSessionCommandRemoveAllP2P = 3,	/**< ɾ�����е�Ե�ĻỰ�� */
			kNIMSessionCommandRemoveAllTeam = 4,	/**< ɾ������Ⱥ�ĻỰ�� */
			kNIMSessionCommandMsgDeleted = 5,	/**< �����Ự�����Ϣ��ɾ�� */
			kNIMSessionCommandAllMsgDeleted = 6,	/**< ���лỰ�����Ϣ��ɾ�� */
			kNIMSessionCommandAllP2PMsgDeleted = 7,	/**< ���е�Ե�Ự�����Ϣ��ɾ�� */
			kNIMSessionCommandAllTeamMsgDeleted = 8,	/**< ����Ⱥ�Ự�����Ϣ��ɾ�� */
			kNIMSessionCommandUpdate = 9,	/**< ���»Ự�� */
			kNIMSessionCommandRemoveAllSuperTeam = 10,	/**< ɾ�����г���Ⱥ�ĻỰ�� */
			kNIMSessionCommandAllSuperTeamMsgDeleted = 11,	/**< ���г���Ⱥ�Ự�����Ϣ��ɾ�� */

		};

		/** @name ��Ϣ�ṹ Json Keys
		* ���� {"client_msg_id" : "c0d1167459fc754098a531482b51a1da","local_res_path" : "","log_status" : 4,"log_sub_status" : 0,"msg_attach" : "","msg_body" : "�����ı���Ϣ����", "msg_type" : 0, "resend_flag" : 0, "time" : 1437014897000, "to_accid" : "4045", "to_type" : 1}
		* @{
		*/
		//Э�鶨��
		static const char *kNIMMsgKeyToType = "to_type";			/**< int,�Ự����(NIMSessionType) */
		static const char *kNIMMsgKeyToAccount = "to_accid";			/**< string,��Ϣ���շ�id,���Լ�������Ϣʱ��д�Լ�id */
		static const char *kNIMMsgKeyFromAccount = "from_id";			/**< string,��Ϣ���ͷ�id,��������д,���ͷ�����Ҫ��д */
		static const char *kNIMMsgKeyFromClientType = "from_client_type";	/**< int,��Ϣ���ͷ��ͻ������ͣ�NIMClientType��,��������д,���ͷ�����Ҫ��д */
		static const char *kNIMMsgKeyFromDeviceId = "from_device_id";		/**< string,��Ϣ���ͷ��豸id,��������д,���ͷ�����Ҫ��д */
		static const char *kNIMMsgKeyFromNick = "from_nick";			/**< string,��Ϣ���ͷ��ǳ�,��������д,���ͷ�����Ҫ��д */
		static const char *kNIMMsgKeyTime = "time";				/**< long,��Ϣʱ���(����) */
		static const char *kNIMMsgKeyType = "msg_type";			/**< int,��Ϣ����(NIMMessageType) */
		static const char *kNIMMsgKeyBody = "msg_body";			/**< string,��Ϣ����,�������ƣ�5000�ַ� */
		static const char *kNIMMsgKeyAttach = "msg_attach";			/**< string,��Ϣ��ý����Դ����,��ͬ���Ͷ�ý�������ͬ,���ͷǶ�ý����Ϣʱ����Ҫ��д,����ʹ��json string,����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ��� */
		static const char *kNIMMsgKeyClientMsgid = "client_msg_id";		/**< string,�ͻ�����Ϣid */
		static const char *kNIMMsgKeyServerMsgid = "server_msg_id";		/**< long,����������Ϣid */
		static const char *kNIMMsgKeyResendFlag = "resend_flag";		/**< int,��Ϣ�ط����λ,��һ�η���0,�ط�1 */
		static const char *kNIMMsgKeyHistorySave = "cloud_history";		/**< int,(��ѡ)����Ϣ�Ƿ�洢�ƶ���ʷ,��ѡ��0:��֧��,1:֧��, Ĭ��1 */
		static const char *kNIMMsgKeyMsgRoaming = "roam_msg";			/**< int,(��ѡ)����Ϣ�Ƿ�֧������,��ѡ,0:��֧��,1:֧��, Ĭ��1 */
		static const char *kNIMMsgKeyMsgSync = "sync_msg";			/**< int,(��ѡ)����Ϣ�Ƿ�֧�ַ����߶��ͬ��,��ѡ,0:��֧��,1:֧��, Ĭ��1 */
		static const char *kNIMMsgKeyPushNeedBadge = "push_need_badge";	/**< int,(��ѡ)�����Ƿ�Ҫ����Ϣ����(�Ǳ�)��0:����Ҫ��1:��Ҫ��Ĭ��1 */
		static const char *kNIMMsgKeyServerExt = "server_ext";			/**< string,(��ѡ)�Զ�����չ�ֶ�,����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ���,��������1024 */
		static const char *kNIMMsgKeyPushPayload = "push_payload";		/**< string,(��ѡ)�������Զ�����������ԣ�����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ���������2048 */
		static const char *kNIMMsgKeyPushContent = "push_content";		/**< string,(��ѡ)�Զ��������İ�����������200�ֽ� */
		static const char *kNIMMsgKeyPushEnable = "push_enable";		/**< int,(��ѡ)�Ƿ���Ҫ����, 0:����Ҫ,1:��Ҫ,Ĭ��1,aos���յ�0�ǲ�Ҫģ�Ȿ������ */
		static const char *kNIMMsgKeyPushNeedPrefix = "push_prefix";		/**< int,(��ѡ)�����Ƿ���Ҫǰ׺��0:����Ҫ��1:��Ҫ��Ĭ��1 */
		static const char *kNIMMsgKeyMsgRoutable = "routable_msg";		/**< int,(��ѡ)����Ϣ�Ƿ���,0:��֧��,1:֧��,Ĭ�ϰ���app��·�ɿ��� */
		static const char *kNIMMsgKeySetMsgOffline = "offline_msg";		/**< int,(��ѡ)��Ϣ�Ƿ�Ҫ������,0:����Ҫ, 1:��Ҫ��Ĭ��1*/
		static const char *kNIMMsgKeyForcePushList = "force_push_list";			/**< string,(��ѡ)Ⱥ����Ϣǿ���б�,����ָ���˺�id string array json, �������ȫԱ����*/
		static const char *kNIMMsgKeyForcePushContent = "force_push_content";		/**< string,(��ѡ)Ⱥ����Ϣǿ���ı� */
		static const char *kNIMMsgKeyIsForcePush = "is_force_push";		/**< int,(��ѡ)Ⱥ����Ϣ�Ƿ�ǿ��,0:��ǿ��, 1:ǿ�ƣ�����ֻ���Ⱥ����Ϣǿ���б� */
		static const char *kNIMMsgKeyAntiSpamEnable = "anti_spam_enable";	/**< int, �Ƿ���Ҫ���׶ܷ�����, 0:����Ҫ,1:��Ҫ, Ĭ��0 */
		static const char *kNIMMsgKeyAntiSpamContent = "anti_spam_content";	/**< string, (��ѡ)�������Զ���ķ������ֶ�,�������ƣ�5000�ַ�, ��ʽΪjson string,{"type" : 1:�ı���2��ͼƬ��3��Ƶ, "data" : "�ı�����orͼƬ��ַor��Ƶ��ַ"}*/
		static const char *kNIMMsgKeyClientAntiSpam = "client_anti_spam_hitting";	/**< int, (��ѡ) �Ƿ����пͻ��˷�����,����:1 δ���У�0 ���߲���д*/
		static const char *kNIMMsgKeyAntiSpamBizId = "anti_spam_business_id";	/**< string,  (��ѡ)�û����õĶ�ĳЩ������Ϣ����ķ�������ҵ��ID*/
		static const char *kNIMMsgKeyAntiSpamUsingYiDun = "anti_spam_using_yidun";	/**< int,  (��ѡ) ������Ϣ�Ƿ�ʹ���׶ܷ����� 0:(�ڿ�ͨ�׶ܵ������)�����׶ܷ���������ͨ�÷����� �������ǰ���ԭ���Ĺ���*/
		static const char *kNIMMsgKeyTeamMsgAck = "team_msg_ack";		/**< (��ѡ)int, Ⱥ��Ϣ�Ƿ���Ҫ�Ѷ�ҵ��0������Ҫ��1����Ҫ*/


		//���ض���
		static const char *kNIMMsgKeyLocalKeyTeamMsgAckSent = "team_msg_ack_sent";	/**< bool �Ƿ��Ѿ�����Ⱥ��Ϣ�Ѷ���ִ */
		static const char *kNIMMsgKeyLocalKeyTeamMsgUnreadCount = "team_msg_unread_count";	/**< int, Ⱥ��Ϣδ���� */
		static const char *kNIMMsgKeyLocalFilePath = "local_res_path";		/**< string,��ý����Ϣ��Դ���ؾ���·��,SDK����ά��,���Ͷ�ý����Ϣʱ���� */
		static const char *kNIMMsgKeyLocalTalkId = "talk_id";			/**< string,�Ựid,���ͷ�ѡ��,���շ��յ�������Ϣ���ͷ�id */
		static const char *kNIMMsgKeyLocalResId = "res_id";				/**< string,��ý����Դid,���ͷ�ѡ��,���շ��յ����ǿͻ�����Ϣid */
		static const char *kNIMMsgKeyLocalLogStatus = "log_status";			/**< int,��Ϣ״̬(NIMMsgLogStatus)  */
		static const char *kNIMMsgKeyLocalLogSubStatus = "log_sub_status";		/**< int,��Ϣ����״̬(NIMMsgLogSubStatus) */
		static const char *kNIMMsgKeyLocalExt = "local_ext";			/**< string,ֻά���ڱ��ص���չ�ֶ�,����Ϊ���Խ���Ϊjson�ķǸ�ʽ�����ַ��� */
		/** @}*/ //��Ϣ�ṹ Json Keys


		/** @enum NIMMessageType Message Type */
		enum NIMMessageType
		{
			kNIMMessageTypeText = 0,			/**< �ı�������Ϣ*/
			kNIMMessageTypeImage = 1,			/**< ͼƬ������Ϣ*/
			kNIMMessageTypeAudio = 2,			/**< ����������Ϣ*/
			kNIMMessageTypeVideo = 3,			/**< ��Ƶ������Ϣ*/
			kNIMMessageTypeLocation = 4,			/**< λ��������Ϣ*/
			kNIMMessageTypeNotification = 5,		/**< ϵͳ����֪ͨ��������Ⱥ��Ⱥ֪ͨ�ȣ� NIMNotificationId*/
			kNIMMessageTypeFile = 6,			/**< �ļ�������Ϣ*/
			kNIMMessageTypeTips = 10,			/**< ����������Ϣ,Tip���ݸ��ݸ�ʽҪ��������Ϣ�ṹ�е�kNIMMsgKeyServerExt�ֶ�*/
			kNIMMessageTypeRobot = 11,			/**< ���ػ�������Ϣ*/
			kNIMMessageTypeCustom = 100,			/**< �Զ�����Ϣ*/

			kNIMMessageTypeUnknown = 1000,		/**< δ֪������Ϣ������ʹ�ã�����ʱ��ʹ�ã���ΪĬ��ֵ*/
		};

		/** @enum NIMMessageFeature ��Ϣ���� */
		enum NIMMessageFeature
		{
			kNIMMessageFeatureDefault = 0,			/**< Ĭ��*/
			kNIMMessageFeatureLeaveMsg = 1,			/**< ������Ϣ*/
			kNIMMessageFeatureRoamMsg = 2,			/**< ������Ϣ*/
			kNIMMessageFeatureSyncMsg = 3,			/**< ͬ����Ϣ*/
			kNIMMessageFeatureCustomizedMsg = 4,		/**< ͸����Ϣ*/
		};

		/** @enum NIMMsgLogStatus ��Ϣ״̬ */
		enum NIMMsgLogStatus
		{
			kNIMMsgLogStatusNone = 0,			/**< Ĭ��,���ܵ���ѯ����,����̫��*/
			kNIMMsgLogStatusUnread = 1,			/**< �յ���Ϣ,δ��*/
			kNIMMsgLogStatusRead = 2,			/**< �յ���Ϣ,�Ѷ�*/
			kNIMMsgLogStatusDeleted = 3,			/**< ��ɾ*/
			kNIMMsgLogStatusSending = 4,			/**< ������*/
			kNIMMsgLogStatusSendFailed = 5,			/**< ����ʧ��*/
			kNIMMsgLogStatusSent = 6,			/**< �ѷ���*/
			kNIMMsgLogStatusReceipt = 7,			/**< �Է��Ѷ����͵�����*/
			kNIMMsgLogStatusDraft = 8,			/**< �ݸ�*/
			kNIMMsgLogStatusSendCancel = 9,			/**< ����ȡ��*/
			kNIMMsgLogStatusRefused = 10, /**< ���Է��ܾ�,���类�Է�����������ȵ�*/
		};
		/** @enum NIMMsgLogSubStatus ��Ϣ��״̬ */
		enum NIMMsgLogSubStatus
		{
			kNIMMsgLogSubStatusNone = 0,			/**< Ĭ��״̬*/

			//�������־����������
			kNIMMsgLogSubStatusNotPlaying = 20,			/**< δ����*/
			kNIMMsgLogSubStatusPlayed = 21,			/**< �Ѳ���*/
		};


		/** @name NOS �ϴ��ļ���Nosȱʡtag���� */
		static const char *kNIMNosDefaultTagResource = "nim_default_profile_icon";		/**< string ��Դ���ļ��ϴ�tag ��ͷ��Ⱥͷ��ȣ� ����ͨ�� nim_nos_init_tags�޸���Դ�Ĺ���ʱ��*/
		static const char *kNIMNosDefaultTagIM = "nim_default_im";	/**< string im��Ϣ���ļ��ϴ�tag ��ͼƬ���ļ�������Ƶ��Ϣ�ȣ� ����ͨ�� nim_nos_init_tags�޸���Դ�Ĺ���ʱ��*/


		static const char *kNIMFileMsgKeyMd5 = "md5";			/**< string,��ԴMD5,���ͷ�ѡ�� */
		static const char *kNIMFileMsgKeySize = "size";			/**< long,��Դ��С(KB),���ͷ�ѡ�� */
		static const char *kNIMFileMsgKeyDisplayName = "name";			/**< string,������ʾ���ļ���,���ͷ�ѡ��,Ĭ���ļ��� */
		static const char *kNIMFileMsgKeyUrl = "url";			/**< string,��ԴURL, ���ͷ�����Ҫ��д */
		static const char *kNIMFileMsgKeyExt = "ext";			/**< string,��Դ��չ��,����������'.',���ͷ���ѡ����Ҫ��֤��Դ����·��������չ�� */


		static const char *kNIMMsgAttachKeyMd5 = "md5";			/**< string,��ԴMD5,���ͷ�ѡ�� */
		static const char *kNIMMsgAttachKeySize = "size";			/**< long,��Դ��С(KB),���ͷ�ѡ�� */
		static const char *kNIMMsgAttachKeyUrl = "url";			/**< long,��ԴURL, ���ͷ�����Ҫ��д */
		static const char *kNIMMsgAttachKeyExt = "ext";			/**< string,��Դ��չ��,����������'.',���ͷ���ѡ����Ҫ��֤��Դ����·��������չ�� */
		static const char *kNIMMsgAttachKeyDisplayName = "name";		/**< string,������ʾ���ļ���,���ͷ�ѡ��,Ĭ���ļ��� */
		static const char *kNIMMsgAttachKeyTag = "upload_tag";			/**< string, (��ѡ)���ͺ��и�������Ϣʱʹ�õĳ�����ǩ(�ɲμ�nosɾ������) ,Audio Image Video File ���߿��Ա�SDK�����������ļ�·�����Զ�����Ϣ*/
		/** @}*/ //attach��ý����Դ����ͨ�ü������壬�������ͬ���Ͷ�ý����ʹ�õ���ͬ�Ĳ����ļ���.


		static const char *kNIMImgMsgKeyMd5 = "md5";			/**< string,��ԴMD5,���ͷ�ѡ�� */
		static const char *kNIMImgMsgKeySize = "size";			/**< long,��Դ��С(KB),���ͷ�ѡ�� */
		static const char *kNIMImgMsgKeyWidth = "w";				/**< int,ͼƬ���,���ͷ����� */
		static const char *kNIMImgMsgKeyHeight = "h";				/**< int,ͼƬ�߶�,���ͷ����� */
		static const char *kNIMImgMsgKeyUrl = "url";			/**< string,��ԴURL, ���ͷ�����Ҫ��д */
		static const char *kNIMImgMsgKeyExt = "ext";			/**< string,��Դ��չ��,����������'.',���ͷ���ѡ����Ҫ��֤��Դ����·��������չ�� */
		static const char *kNIMImgMsgKeyDisplayName = "name";		/**< string,������ʾ���ļ���,���ͷ�ѡ��,Ĭ���ļ��� */
		/** @}*/ //attachͼƬ���Ͷ�ý����Դ������������

		/** @name attach�������Ͷ�ý����Դ������������
		* @{
		*/
		static const char *kNIMAudioMsgKeyMd5 = "md5";			/**< string,��ԴMD5,���ͷ�ѡ�� */
		static const char *kNIMAudioMsgKeySize = "size";			/**< long,��Դ��С(KB),���ͷ�ѡ�� */
		static const char *kNIMAudioMsgKeyDuration = "dur";			/**< int,������Դʱ�䳤��(����),���ͷ����� */
		static const char *kNIMAudioMsgKeyUrl = "url";			/**< string,��ԴURL, ���ͷ�����Ҫ��д */
		static const char *kNIMAudioMsgKeyExt = "ext";			/**< string,��Դ��չ��,����������'.',���ͷ���ѡ����Ҫ��֤��Դ����·��������չ�� */
		static const char *kNIMAudioMsgKeyDisplayName = "name";		/**< string,������ʾ���ļ���,���ͷ�ѡ��,Ĭ���ļ��� */
		/** @}*/ //attach�������Ͷ�ý����Դ������������

		/** @name attach����Ƶ���Ͷ�ý����Դ������������
		* @{
		*/
		static const char *kNIMVideoMsgKeyMd5 = "md5";			/**< string,��ԴMD5,���ͷ�ѡ�� */
		static const char *kNIMVideoMsgKeySize = "size";			/**< long,��Դ��С(KB),���ͷ�ѡ�� */
		static const char *kNIMVideoMsgKeyDisplayName = "name";			/**< string,������ʾ���ļ���,���ͷ�ѡ��,Ĭ���ļ��� */
		static const char *kNIMVideoMsgKeyDuration = "dur";			/**< int,����Ƶ��Դʱ�䳤��(����),���ͷ����� */
		static const char *kNIMVideoMsgKeyWidth = "w";				/**< int,����Ƶ������,���ͷ����� */
		static const char *kNIMVideoMsgKeyHeight = "h";				/**< int,����Ƶ����߶�,���ͷ����� */
		static const char *kNIMVideoMsgKeyUrl = "url";			/**< string,��ԴURL, ���ͷ�����Ҫ��д */
		static const char *kNIMVideoMsgKeyExt = "ext";			/**< string,��Դ��չ��,����������'.',���ͷ���ѡ����Ҫ��֤��Դ����·��������չ�� */
		/** @}*/ //attach����Ƶ���Ͷ�ý����Դ������������


		/** @name attachλ�����Ͷ�ý����Դ������������
		* @{
		*/
		static const char *kNIMLocationMsgKeyLatitude = "lat";			/**< double,γ�� */
		static const char *kNIMLocationMsgKeyLongitude = "lng";			/**< double,���� */
		static const char *kNIMLocationMsgKeyTitle = "title";			/**< string,λ����Ϣ */
		/** @}*/ //attachλ�����Ͷ�ý����Դ������������



		/** @name attach���ػ��������Ͷ�ý����Դ������������
		* @{
		*/
		static const char *kNIMBotRobotMsgKeyRobotID = "robotAccid";	/**< string������������ID */
		static const char *kNIMBotRobotSentMsgKeyParam = "param";		/**< json string���������˷���ʱ��Ҫ����ֶΣ��ֶ����ݶ���ɼ�DemoԴ���ο����ؿ����ĵ� */
		static const char *kNIMBotRobotReceivedMsgKeyClientMsgID = "clientMsgId";/**< string�������˻ظ�ʱ�����ֶΣ���ʾ�����ظ����������ϢID */
		static const char *kNIMBotRobotReceivedMsgKeyMsgOut = "msgOut";		/**< bool���Ƿ�Ϊ�����˻ظ���Ĭ��Ϊtrue */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsg = "robotMsg";	/**< json string�������˻ظ�ʱ�����ֶΣ����ػ�������Ϣ */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsgFlag = "flag";		/**< string�������˻ظ�ʱ�����ֶΣ���ʾ�����ظ����ͣ����Ͷ���ɼ�DemoԴ���ο����ؿ����ĵ���bot��faq */
		static const char *kNIMBotRobotReceivedMsgKeyRobotMsgMessage = "message";	/**< json object�������˻ظ�ʱ�����ֶΣ���ʾ�����ظ����ݣ��ֶ����ݶ���ɼ�DemoԴ���ο����ؿ����ĵ� */
		//static const char *kNIMBotRobotReceivedMsgKeyRobotMsgS		= "s";			/**< string��δ֪ */
		/** @}*/ //attach���ػ��������Ͷ�ý����Դ������������


		static const char *kNIMMsgKeyLocalRescode = "rescode";			/**< int,��Ϣ������(NIMResCode) */
		static const char *kNIMMsgKeyLocalMsgFeature = "feature";			/**< int,��Ϣ����(NIMMessageFeature),SDK����ά�� */
		static const char *kNIMMsgKeyLocalReceiveMsgContent = "content";			/**< json string,��Ϣ���ݣ�Э�鶨�����Ϣ�ṹ */

		static const char *kNIMMsglogStatusChangedKeyTalkID = "talk_id";/**< �ỰID */
		static const char *kNIMMsglogStatusChangedKeyMsgTimetag = "msg_timetag";/**< �ٽ����Ϣ��ʱ��� */
		static const char *kNIMMsglogStatusChangedKeyStatus = "status";/**< ������״̬ */

		static const char *kNIMMsglogQueryKeyCount = "count";			/**< int, ��ѯ�õ������� */
		static const char *kNIMMsglogQueryKeySource = "source";			/**< NIMMsglogQuerySource, ��ѯ�����Դ */
		static const char *kNIMMsglogQueryKeyContent = "content";		/**< json object array (Keys SEE MORE in `nim_talk_def.h` ����Ϣ�ṹ Json Keys��)����ѯ�õ���msglog���� */
		/** @}*/ //��ѯ��Ϣ��ʷ���Json Keys

		/** @enum NIMMsglogQuerySource ��Ϣ��ʷ��ѯ��Դ */
		enum NIMMsglogQuerySource
		{
			kNIMMsglogQuerySourceLocal = 0,			/**< ���ز�ѯ*/
			kNIMMsglogQuerySourceServer = 1,			/**< �ƶ˲�ѯ*/
		};
		/** @enum NIMMsgLogQueryRange ��Ϣ��ʷ�ļ�����Χ */
		enum NIMMsgLogQueryRange
		{
			kNIMMsgLogQueryRangeP2P = kNIMSessionTypeP2P,	/**< ָ���ĸ��ˣ���Ե�Ự����ע�⣺�ݲ�֧��ָ������˵ļ�������*/
			kNIMMsgLogQueryRangeTeam = kNIMSessionTypeTeam,	/**< ָ����Ⱥ�飨ע�⣺�ݲ�֧��ָ�����Ⱥ��ļ�������*/
			kNIMMsgLogQueryRangeSuperTeam = kNIMSessionTypeSuperTeam,	/**< ָ���ĳ���Ⱥ�飨ע�⣺�ݲ�֧��ָ�����Ⱥ��ļ�������*/

			kNIMMsgLogQueryRangeAll = 100,					/**< ȫ��*/
			kNIMMsgLogQueryRangeAllP2P = 101,					/**< ���и��˻Ự*/
			kNIMMsgLogQueryRangeAllTeam = 102,					/**< ����Ⱥ��*/
			kNIMMsgLogQueryRangeAllSuperTeam = 103,					/**< ���г���Ⱥ��*/
			kNIMMsgLogQueryRangeUnknown = 200,					/**< δ֪����ָ�����˺�Ⱥ��ļ��ϣ���ע�⣺�ݲ�֧��ָ�����˺�Ⱥ��Ļ�ϼ�������*/
		};

		/** @brief ������Ϣ��¼���ƶ˲������� */
		typedef struct
		{
			/** �Զ���Ĵ����ʽ�ص���SDK����ԭʼ�����ĺ����ÿ������Զ���Ĵ����ѹ��������
			* @param[in] file_path		ԭʼ�����ļ�·��
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return char* ���ɵĴ����ѹ�����ļ���·��
			*/
			char*(*ExportBackupToRemotePackageCallback)(const char* const file_path, void* user_data);
			/** �Զ���ļ��ܷ�ʽ�ص���SDK����ԭʼ���ݾ��������ѹ���������ÿ������Զ���ļ��ܷ���
			* @param[in] file_path		�����ѹ��������ļ�·��
			* @param[in] encrypt_key	������Կ �� encrypt_key_Ϊͬһ��ֵ
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return char* ���ܺ���ļ�·��
			*/
			char*(*ExportBackupToRemoteEncryptCallback)(const char* const  file_path, const char* const  encrypt_key, void* user_data);
			char* encrypt_key_;/**< ������Կ*/
			/**�������̵Ľ��Ȼص�
			* @param[in] op		�������� ����/����
			* @param[in] progress	���� 0-1
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return void
			*/
			void(*LogsBackupProgressCallback)(enum LogsBackupRemoteOperate op, float progress, void* user_data);
			/** ������ɺ�Ľ���ص�
			* @param[in] op		�������� ����/����
			* @param[in] state	���״̬�ο� LogsBackupRemoteState
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return void
			*/
			void(*LogsBackupCompleteCallback)(enum LogsBackupRemoteOperate op, enum LogsBackupRemoteState state, void* user_data);
			/**�������Զ���ĵ�����Ϣ�Ĺ�����
			* @param[in] msg		��Ϣ����ϸ���� json��ʽ
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return bool true:����������Ϣ;false:������������Ϣ
			*/
			bool(*ExportBackupToRemoteLogFiter)(const char* const msg, void* user_data);
			/**�ڵ������������ɵ���·�����ַ������ͷŽӿ�
			* @param[in] data_ptr	ָ��·�����ַ�����������
			* @return void
			*/
			void(*NewPathRelease)(char** data_ptr);
			void* user_data_; /**< APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ��� */
		}NIMLogsBackupExportInfo;

		/** @brief���ƶ˵�����Ϣ��¼�������� */
		typedef struct
		{
			/**�Զ���Ľ����ʽ�ص������ƶ˲��ı����ļ������ܺ��ص��������Զ���Ľ������ѹ������
			* @param[in] file_path		�����ܺ��ļ�·��
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return char* �������ļ�·��
			*/
			char*(*ImportBackupFromRemoteUnPackageCallback)(const char* const file_path, void* user_data);
			/**�Զ���Ľ��ܷ�ʽ�ص���SDK���ƶ�ͬ���걸���ļ������ÿ������Զ���Ľ��ܷ���
			* @param[in] file_path		���ƶ�ͬ�������ļ�·��
			* @param[in] encrypt_key	������Կ �뵼��ʱ������Կ��ͬ
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return char* ���ܺ���ļ�·��
			*/
			char*(*ImportBackupFromRemoteDecryptCallback)(const char* const file_path, const char* const encrypt_key, void* user_data);
			/** ������̵Ľ��Ȼص�
			* @param[in] op		�������� ����/����
			* @param[in] progress	���� 0-1
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return void
			*/
			void(*LogsBackupProgressCallback)(enum LogsBackupRemoteOperate op, float progress, void* user_data);
			/**������ɺ�Ľ���ص�
			* @param[in] op		�������� ����/����
			* @param[in] state	 ���״̬�ο� LogsBackupRemoteState
			* @param[in] user_data		APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ���
			* @return void
			*/
			void(*LogsBackupCompleteCallback)(enum LogsBackupRemoteOperate op, enum LogsBackupRemoteState state, void* user_data);
			/**�ڵ�����������ɵ���·�����ַ������ͷŽӿ�
			* @param[in] data_ptr	ָ��·�����ַ�����������
			* @return bool true:����������Ϣ;false:������������Ϣ
			*/
			void(*NewPathRelease)(char**);
			void* user_data_;/**< APP���Զ����û����ݣ�SDKֻ���𴫻ظ��ص������������κδ��� */
		}NIMLogsBackupImportInfo;
		enum LogsBackupRemoteState
		{
			LogsBackupRemoteState_Begin = -2,/**< ���忪ʼ*/
			LogsBackupRemoteState_UnDef,				/**< δ����*/
			LogsBackupRemoteState_UserCanceled = 5,		/**< ��ȡ��*/
			LogsBackupRemoteState_SDKError,			/**< SDK �ѳ���*/
			//����״̬
			LogsBackupRemoteState_IMP_NoBackup,/**<û�б����ļ�*/
			LogsBackupRemoteState_IMP_SyncFromSrvError,/**<��ѯ����ʧ��һ�����������*/
			LogsBackupRemoteState_IMP_DownloadBackupFailed,/**<���ر����ļ�����*/
			LogsBackupRemoteState_IMP_RAWError,/**<����/��ѹ������Դ�ļ���ʽ����*/
			LogsBackupRemoteState_IMP_ParseRAWError,/**<����Դ�ļ���ʽ����*/
			LogsBackupRemoteState_IMP_LocalDBFailed, /**<���뱾��DB����	*/
			//����״̬
			LogsBackupRemoteState_EXP_LocalDBFailed,/**<�򿪱���DBʧ��*/
			LogsBackupRemoteState_EXP_RAWError,/**<������Դ�ļ�ʧ��*/
			LogsBackupRemoteState_EXP_UploadBackupFailed,/**<�ϴ������ļ�����*/
			LogsBackupRemoteState_EXP_SyncToSrvError,/**<ͬ��������������һ�����������*/

			LogsBackupRemoteState_Done,				/**< ���*/
			LogsBackupRemoteState_Done_NoLogs,/**<��ɣ���δ�����κμ�¼*/
			LogsBackupRemoteState_End,/**<�������*/
			LogsBackupRemoteState_FinalState_Begin = LogsBackupRemoteState_UserCanceled,/**<�Ƿ���������״̬��һ����ʶ�������ж�state�Ƿ�Ϊ��̬(state >= LogsBackupRemoteState_FinalState_Begin)*/

		};

#ifdef __cplusplus
	};
#endif //__cplusplus
}

