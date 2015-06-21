/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

namespace ExitGames
{
	namespace Common
	{
		class JString;

		class ToString
		{
		public:
			virtual ~ToString(void);
			virtual JString typeToString(void) const;
			virtual JString& toString(JString& retStr, bool withTypes=false) const = 0;
			JString toString(bool withTypes=false) const;
		protected:
			static const wchar_t* EG_STR_CHAR;
			static const wchar_t* EG_STR_SCHAR;
			static const wchar_t* EG_STR_UCHAR;
			static const wchar_t* EG_STR_SHORT;
			static const wchar_t* EG_STR_USHORT;
			static const wchar_t* EG_STR_INT;
			static const wchar_t* EG_STR_UINT;
			static const wchar_t* EG_STR_LONG;
			static const wchar_t* EG_STR_ULONG;
			static const wchar_t* EG_STR_LONGLONG;
			static const wchar_t* EG_STR_ULONGLONG;
			static const wchar_t* EG_STR_FLOAT;
			static const wchar_t* EG_STR_DOUBLE;
			static const wchar_t* EG_STR_LONGDOUBLE;
			static const wchar_t* EG_STR_BOOL;
		};
	}
}