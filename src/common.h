#ifndef __HISS__COMMON_H__
#define __HISS__COMMON_H__

namespace hiss {

namespace internal_assert 
{
	template<bool x> 
	struct SASSERT_F;
	template<> 
	struct SASSERT_F <true> {};
	template<int x> 
	struct SASSERT_P {};
#define STATIC_ASSERT(B)            \
	typedef \
	internal_assert::SASSERT_P <( \
		sizeof (internal_assert::SASSERT_F <(((B)? true : false))>) \
	)> StaticAssert##__LINE__()
}

typedef unsigned long index;

};

#endif
