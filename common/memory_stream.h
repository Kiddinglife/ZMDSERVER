#ifndef KBE_MEMORYSTREAM_H_
#define KBE_MEMORYSTREAM_H_
#include "ace/pre.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "common.h"
#include "ace_object_pool.h"
#include "memorystream_converter.hpp"

ACE_KBE_BEGIN_VERSIONED_NAMESPACE_DECL

class MemoryStreamException
{
	public:
	MemoryStreamException(bool _add, size_t _pos, size_t _esize, size_t _size)
		: _m_add(_add), _m_pos(_pos), _m_esize(_esize), _m_size(_size)
	{
		PrintPosError();
	}

	void PrintPosError() const
	{
		//ERROR_MSG(fmt::format("Attempted to {} in MemoryStream (pos:{}  size: {}).\n",
		//	( _m_add ? "put" : "get" ), _m_pos, _m_size));
		ACE_DEBUG((
			LM_ERROR,
			"Attempted to { %s } in MemoryStream (pos:{ %d }  size: { %d }).\n",
			( _m_add ? "put" : "get" ),
			_m_pos,
			_m_size
			));
	}
	private:
	bool 		_m_add;
	size_t 		_m_pos;
	size_t 		_m_esize;
	size_t 		_m_size;
};

union PackFloatXType
{
	float	            fv;
	ACE_UINT32	uv;
	int		            iv;
};
/*
resize()£¬ÉèÖÃ´óÐ¡£¨size£©;
reserve()£¬ÉèÖÃÈÝÁ¿£¨capacity£©;
size()ÊÇ·ÖÅäÈÝÆ÷µÄÄÚ´æ´óÐ¡£¬¶øcapacity()Ö»ÊÇÉèÖÃÈÝÆ÷ÈÝÁ¿´óÐ¡£¬µ«²¢Ã»ÓÐÕæÕý·ÖÅäÄÚ´æ¡£
´ò¸ö±È·½£ºÕýÔÚ½¨ÔìµÄÒ»Á¾¹«½»³µ£¬³µÀïÃæ¿ÉÒÔÉèÖÃ40¸ö×ùÒÎ£¨reserve(40);£©£¬
ÕâÊÇËüµÄÈÝÁ¿£¬µ«²¢²»ÊÇËµËüÀïÃæ¾ÍÓÐÁË40¸ö×ùÒÎ£¬Ö»ÄÜËµÃ÷Õâ²¿³µÄÚ²¿¿Õ¼ä´óÐ¡¿ÉÒÔ·ÅµÃÏÂ40ÕÅ×ùÒÎ¶øÒÑ¡£
¶ø³µÀïÃæ°²×°ÁË40¸ö×ùÒÎ(resize(40);)£¬Õâ¸öÊ±ºò³µÀïÃæ²ÅÕæÕýÓÐÁË40¸ö×ùÒÎ£¬ÕâÐ©×ùÒÎ¾Í¿ÉÒÔÊ¹ÓÃÁË¡£
*/
class MemoryStream
{
	protected:
	mutable size_t rpos_, wpos_;
	std::vector<ACE_UINT8> data_;

	public:
	const static size_t DEFAULT_SIZE = 0x100;

	MemoryStream() :
		rpos_(0),
		wpos_(0)
	{
		data_.reserve(DEFAULT_SIZE);
	}

	explicit MemoryStream(size_t res) :
		rpos_(0),
		wpos_(0)
	{
		if( res <= 0 )
			res = DEFAULT_SIZE;
		data_.reserve(res);
	}

	MemoryStream(const MemoryStream& memstream) :
		rpos_(memstream.rpos_),
		wpos_(memstream.wpos_),
		data_(memstream.data_)
	{
	}

	virtual ~MemoryStream()
	{
		clear(true);
	}

	void clear(bool clearData)
	{
		//clear will call dtor if existing but will not release the mem
		if( clearData )
			data_.clear();
		rpos_ = wpos_ = 0;
	}

	template <typename T> void append(T value)
	{
		EndianConvert(value);
		//
	}

	void append(const ACE_Byte* src, size_t cnt)
	{
		if( !cnt )
			return;
		ACE_ASSERT(size() < 10000000);
		//µ±Ç°·ÖÅäÄÚ´æ´óÐ¡²»×ã
		if( data_.size() < wpos_ + cnt )
			data_.resize(wpos_ + cnt); //À©³äÄÚ´æ
		//copyÔ­Öµ
		ACE_OS::memcpy(&data_[wpos_], src, cnt);
		wpos_ += cnt;
	}

	virtual size_t size() const { return data_.size(); }

	template <typename T> void put(size_t pos, T value)
	{
		EndianConvert(value);
		put(pos, (ACE_Byte *) &value, sizeof(value));
	}

	void put(size_t pos, const ACE_Byte* src, size_t cnt)
	{
		if( size() < pos + cnt )
			throw MemoryStreamException(true, pos, cnt, size());
		memcpy(&data_[pos], src, cnt);
	}

	void swap(MemoryStream& s)
	{
		size_t rpos = s.rpos_, wpos = s.wpos_;
		std::swap(data_, s.data_);
		s.rpos(rpos_);
		s.wpos(wpos_);
		rpos_ = rpos;
		wpos_ = wpos;
	}

	size_t rpos(int rpos)
	{
		if( rpos < 0 )
			rpos = 0;

		rpos_ = rpos;
		return rpos_;
	}

	size_t wpos() const { return wpos_; }

	size_t wpos(int wpos)
	{
		if( wpos < 0 )
			wpos = 0;

		wpos_ = wpos;
		return wpos_;
	}
};

ACE_KBE_END_VERSIONED_NAMESPACE_DECL
#endif