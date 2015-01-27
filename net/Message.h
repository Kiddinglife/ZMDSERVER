﻿#ifndef Message_H_
#define Message_H_

#include "ace\pre.h"
#include "ace\Null_Mutex.h"
#include "net_common.h"
#include "FixedMessages.h"

ACE_KBE_BEGIN_VERSIONED_NAMESPACE_DECL
class KBE_MD5;
NETWORK_NAMESPACE_BEGIN_DECL

struct Messages;
extern std::vector<Messages*>* gPtrMsgsPtrContainer;
extern FixedMessages* gPtrFixedMsgs;

struct Channel;
struct Packet;

struct ExposedMessageInfo
{
	std::string name;
	MessageID id;
	// 对外消息不会超过1500 the outgoing msg will not exceed 15000
	MessageLength msgLen;
	ACE_INT8 argsType;
	std::vector<ACE_UINT8> argsTypes;
};

/**
 * struct MessageArgs
 * @brief
 * this struct is the abstraction of the msg args for a single msg
 * 一个消息的参数抽象结构
 */
struct MessageArgs
{
	enum MESSAGE_ARGS_TYPE
	{
		//可变参数长度 variable-arg
		MESSAGE_ARGS_TYPE_VARIABLE = -1,
		//固定参数长度 fixed-arg	
		MESSAGE_ARGS_TYPE_FIXED = 0
	};
	std::vector<std::string> strArgsTypes;

	MessageArgs() :strArgsTypes() { };
	virtual ~MessageArgs() { };
	virtual void fetch_args_from(Packet* p) = 0;
	virtual void add_args_to(Packet* p) = 0;
	virtual ACE_INT32 args_bytes_count(void) = 0;
	virtual MESSAGE_ARGS_TYPE type(void) { return MESSAGE_ARGS_TYPE_FIXED; }
};

struct Message
{
	std::string        name_;
	MessageID      msgID_;
	MessageArgs* pMsgArgs_;
	/* -1则为非固定长度消息 : -1 = variable-len msg */
	ACE_INT8        msgType_;
	ACE_UINT8      msgArgsBytesCount_;
	bool                exposed_;

	// stats
	ACE_UINT32 send_size_;
	ACE_UINT32 send_count_;
	ACE_UINT32 recv_size_;
	ACE_UINT32 recv_count_;

	Message() :
		name_("None"),
		msgID_(0),
		pMsgArgs_(NULL),
		msgType_(0),
		msgArgsBytesCount_(0),
		exposed_(false),
		send_size_(0),
		send_count_(0),
		recv_size_(0),
		recv_count_(0)
	{
	}

	virtual ~Message()
	{
		SAFE_RELEASE(pMsgArgs_);
	}

	ACE_UINT32 sendavgsize()const { return ( send_count_ <= 0 ) ? 0 : send_size_ / send_count_; }
	ACE_UINT32 recvavgsize()const { return ( recv_count_ <= 0 ) ? 0 : recv_size_ / recv_count_; }

	/// 默认返回类别为组件消息 default returned type is NETWORK_MESSAGE_TYPE_COMPONENT
	virtual const MESSAGE_CATEGORY category() const
	{
		return MESSAGE_CATEGORY_COMPONENT;
	}

	virtual ACE_INT32 msglenMax() { return NETWORK_MESSAGE_MAX_SIZE; }

	const char* c_str()
	{
		static char buf[MAX_BUF];
		kbe_snprintf(buf, MAX_BUF,
			"msgname_ = %s, msgID_ = %u, len = %s, exposed_ = %d",
			name_, msgID_, msgType_ == NETWORK_FIXED_MESSAGE ?
			"FIXED_MESSAGE" : "VARIABLE_MESSAGE", exposed_);
		return buf;
	}

	/// 当这个handler被正是安装到MessageHandlers后被调用
	virtual void onAdded2Msgs() { }


	virtual void handle(Channel* pChannel, Packet* s)
	{
		pMsgArgs_->fetch_args_from(s);
		// 将参数传给最终的接口
	};
};

struct Messages
{
	static Messages* staticMsgsPtr;
	MessageID msgID_;
	std::vector< std::string > exposedMessages_;
	typedef std::map<MessageID, Message*> MessageMap;
	MessageMap msgs_;

	Messages() :
		msgID_(1),
		exposedMessages_(),
		msgs_()
	{
		/// 获取 FixedMessages的单粒
		gPtrFixedMsgs = ACE_Singleton<FixedMessages, ACE_Null_Mutex>::instance();
		/// 从xml文档中读取固定消息配置
		gPtrFixedMsgs->loadConfig("server/messages_fixed.xml");
		///将该msgs添加到g_pMessagesContainer中去
		gPtrMsgsPtrContainer->push_back(this);

	}

	/**
	 * release all message stored in msgs_
	 * 析构函数将负责删除所有的message*指针
	 */
	~Messages()
	{
		MessageMap::iterator iter = msgs_.begin();
		for( ; iter != msgs_.end(); ++iter )
		{
			if( iter->second )
				delete iter->second;
		};
	}

	Message* add_msg(const std::string&  ihName, MessageArgs* args,
		ACE_INT8 msgType, Message* msg);

	void add_exposed_msg(std::string msgname) { exposedMessages_.push_back(msgname); }

	Message* find(MessageID msgID);

	MessageID lastMsgID() { return msgID_ - 1; }

	bool initializeWatcher();

	static inline void finalise(void);

	static std::string getDigestStr();
};
NETWORK_NAMESPACE_END_DECL
ACE_KBE_END_VERSIONED_NAMESPACE_DECL
#include "ace\post.h"
#endif