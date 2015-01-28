#ifndef Channel_H_
#define Channel_H_

#include "ace\pre.h"
#include "ace\Refcounted_Auto_Ptr.h"
#include "common\ace_object_pool.h"
#include "Bundle.h"

ACE_KBE_BEGIN_VERSIONED_NAMESPACE_DECL
NETWORK_NAMESPACE_BEGIN_DECL

struct TimerHandle { };
struct PacketReader;
struct PacketReceiver;
struct PacketSender;
struct PacketFilter;
typedef ACE_Refcounted_Auto_Ptr<PacketFilter, ACE_Null_Mutex> PacketFilterPtr;

struct Channel // : public TimerHandler, public RefCountable, public PoolObject
{
	/// INTERNAL describes the properties of channel from server to server.
	/// EXTERNAL describes the properties of a channel from client to server.
	enum ChannelScope { INTERNAL, EXTERNAL };

	/// CHANNEL_NORMAL = ��ͨͨ��
	// CHANNEL_WEB = �����webͨ��
	enum ChannelType { CHANNEL_NORMAL, CHANNEL_WEB };

	enum ChannelRecvWinStatus
	{
		PROCESS,
		NOT_PROCESS,
		PACKET_IS_CORRUPT
	};

	//@TO-DO ������Ҫ�鿴apg timer�Ǹ�����
	TimerHandle					          inactivityTimerHandle_;

	/// ��ͨ�����������ӿ�
	NetworkInterface*                  pNetworkInterface_;

	/// ��ͨ����Ҫʹ��bundle��������պͷ��͵���Ϣ
	Bundle						              bundle_;

	//@TO-DO need create struct PacketReader
	PacketReader*				          pPacketReader_; //bufferedReceives_ 

	//@TO-DO maybe can use ace_handle 
	ACE_SOCK*					          pEndPoint_;

	//@TO-DO need create struct PacketReceiver
	PacketReceiver*				      pPacketReceiver_;
	PacketSender*				          pPacketSender_;
	//@TO-DO need create struct PacketFilter
	PacketFilterPtr				          pFilter_;

	/// ����ָ��ͨ��ʹ��ĳЩ�ض�����Ϣ
	/// can designate the channel to use some specific msgs
	Messages*                              pMsgs_;

	/// ���յ������а��ļ��ϣ�the container for the received packets
	typedef std::vector<Packet*> RecvPackets;
	RecvPackets                           recvPackets[2];

	ChannelScope                        channelScope_;
	ChannelType				              channelType_;
	ProtocolType				          protocolType_;
	ChannelID					          channelId_;
	bool						                  isDestroyed_;
	bool						                  sending_;

	/// ���Ϊtrue�����Ƶ���Ѿ���ò��Ϸ�
	/// if true, this channel has become unusable
	bool						                  isCondemn_;

	/// ������ⲿͨ���Ҵ�����һ��ǰ������ǰ�˴���ID
	/// if this channel is external and proxy the client, it will  binds the client id
	ENTITY_ID					              proxyID_;

	/// ��channel���ڵķ����������id
	KBE_SRV_COMPONENT_ID	  componentID_;

	/// ��չ��, for extension
	std::string					              strextra_;

	ACE_UINT64						      inactivityExceptionPeriod_;
	ACE_UINT64                           lastRecvTime_;
	ACE_UINT32                           winSize_;
	ACE_UINT8                             recvPacketIndex_; //bufferedReceivesIdx_

	// Statistics
	ACE_UINT32						      numPacketsSent_;
	ACE_UINT32						      numPacketsReceived_;
	ACE_UINT32						      numBytesSent_;
	ACE_UINT32						      numBytesReceived_;
	ACE_UINT32						      lastTickBytesReceived_;
	ACE_UINT32                           lastTickBytesSent_;

	/// Reference count.
	int ref_count_;

	static void intrusive_add_ref(Channel* channel)
	{
		++channel->ref_count_;
	}

	static void intrusive_remove_ref(Channel* channel)
	{
		--channel->ref_count_;
		ACE_ASSERT(channel->ref_count_ >= 0 && "RefCountable:ref_count_ maybe a error!");
		if( !channel->ref_count_ ) delete channel;
	}

	Channel(NetworkInterface* networkInterface = NULL,
		ACE_SOCK* endpoint = NULL,
		ChannelScope traits = EXTERNAL,
		ProtocolType pt = PROTOCOL_TCP,
		PacketFilterPtr pFilter = PacketFilterPtr(NULL),
		ChannelID id = CHANNEL_ID_NULL);

	virtual ~Channel() { }

	const char*  c_str() const;

	void clearBundle();
	bool initialize();
};
NETWORK_NAMESPACE_END_DECL
ACE_KBE_END_VERSIONED_NAMESPACE_DECL
#include "ace\post.h"
#endif
