#ifndef __LIB__
#define __LIB__

#include <cinttypes>
#include <iostream>
#include <cstdio>

#define ENVBITSIZE 64 // bit size of operational system
// check bit size of operational system
#if _WIN32 || _WIN64 || __GNUC__
	#if _WIN64 || __x86_64__ || __ppc64__
		#define ENV64BIT
	#else
		#define ENV32BIT
		#define ENVBITSIZE 32
	#endif
#endif

#define DEBUG 1

#if DEBUG
	#define DPRINTF(...) (cprintf(__VA_ARGS__))
	#define DPRINT(STR) (std::cout << STR)
	#define DPRINTLN(STR) (std::cout << STR << std::endl)
#else
	#define DPRINTF(...)
	#define DPRINT(STR)
	#define DPRINTLN(STR)
#endif

#define C_ASSERT(V) C_ASSERT_PRINTF(V, "bye!\n")

#define C_ASSERT_PRINTF(V, ...) \
{ if (bunlikely(!(V))) { \
	cprintf("sanity error!\nfile %s at line %u assertion failed!\n%s\n", __FILE__, __LINE__, #V); \
	cprintf(__VA_ARGS__); \
	exit(1); \
} }

#define GETTER(TYPE, VAR) \
	public: \
		inline TYPE get_##VAR () \
			{ \
				return this->VAR; \
			} \

#define GETTER_REF(TYPE, VAR) \
	public: \
		inline TYPE& get_##VAR () \
			{ \
				return this->VAR; \
			} \

#define SETTER(TYPE, VAR) \
	public: \
		inline void set_##VAR (TYPE VAR) \
		{ \
			this->VAR = VAR; \
		}

#define SETTER_REF(TYPE, VAR) \
	public: \
		inline void set_##VAR (const TYPE& VAR) \
		{ \
			this->VAR = VAR; \
		}

#define GETTER_SETTER(TYPE, VAR) \
	GETTER(TYPE, VAR) \
	SETTER(TYPE, VAR)

#define GETTER_SETTER_REF(TYPE, VAR) \
	GETTER_REF(TYPE, VAR) \
	SETTER_REF(TYPE, VAR)

#define OO_ENCAPSULATE(TYPE, VAR) \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR (TYPE VAR) \
		{ \
			this->VAR = VAR; \
		}

#define OO_ENCAPSULATE_REF(TYPE, VAR) \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE& get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR (const TYPE& VAR) \
		{ \
			this->VAR = VAR; \
		}

#define OO_ENCAPSULATE_REF_RO(TYPE, VAR) \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE& get_##VAR () \
		{ \
			return this->VAR; \
		}

#define OO_ENCAPSULATE_DV(TYPE, VAR, DEFAULT_VALUE) \
	private: \
		TYPE VAR = DEFAULT_VALUE; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		} \
		inline void set_##VAR (TYPE VAR) \
		{ \
			this->VAR = VAR; \
		}

#define OO_ENCAPSULATE_RO(TYPE, VAR) \
	private: \
		TYPE VAR; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		}

#define OO_ENCAPSULATE_RO_DV(TYPE, VAR, DEFAULT_VALUE) \
	private: \
		TYPE VAR = DEFAULT_VALUE; \
	public: \
		inline TYPE get_##VAR () \
		{ \
			return this->VAR; \
		}

#endif
