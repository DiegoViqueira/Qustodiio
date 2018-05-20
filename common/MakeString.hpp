//============================================================================
// Name        : MakeString.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Description : Helper to build Strings
//============================================================================

#ifndef MAKE_STRING_HPP_
#define MAKE_STRING_HPP_

#include <sstream>
#include <cstdint>



namespace str {


    struct UIntAsNum{};
    struct UIntAsChar{};

	template<class CharT = char, class Traits = std::char_traits<CharT> >
	class MakeStr {
		/// ostringstream que se usa para construir el string.
		mutable std::basic_ostringstream<CharT,Traits>	m_oOss;
		/// \typedef manip1 Manipulador estandar.
		typedef	std::ios_base& (*manip1)(std::ios_base&);
		/// \typedef manip2 Manipulador estandar.
		typedef	std::basic_ios<CharT,Traits>& (*manip2)(std::basic_ios<CharT,Traits>&);
		/// \typedef manip3 Manipulador estandar.
		typedef	std::basic_ostream<CharT,Traits>& (*manip3)(std::basic_ostream<CharT,Traits>&);
    public:
        enum HowToInsertUints { AS_NUMBER, AS_CHAR };
    private:
        /// Miembro de clase: especifica cómo deben escribirse los UInt.
        static HowToInsertUints m_eHowToInsertUints;
	public:
		/// conversión implícita a string.
		operator std::basic_string<CharT,Traits>() const {
			return m_oOss.str();
		}
		/// Insertor para un tipo T genérico.
		template<class T> const MakeStr& operator<< (const T& t) const {
			m_oOss << t;
			return *this;
		}
		
		/// Especialización para los UInt.
		const MakeStr& operator<< (const uint8_t ui8) const {
			if (m_eHowToInsertUints == AS_NUMBER) {
                m_oOss <<  static_cast<unsigned int>(ui8);
            } else {
                m_oOss << ui8;
            }
			return *this;
		}
		/// Manipulador para que imprima los uint_t como número.
		const MakeStr& operator<< (const UIntAsNum) const {
			m_eHowToInsertUints = AS_NUMBER;
			return *this;
		}
		/// Manipulador para que imprima los uint_t como chars.
		const MakeStr& operator<< (const UIntAsChar) const {
			m_eHowToInsertUints = AS_CHAR;
			return *this;
		}
		/// Insertor para un manipulador estandar.
		const MakeStr& operator<<(manip1 manip) const {
			m_oOss << manip;
			return *this;
		}
		/// Insertor para un manipulador estandar.
		const MakeStr& operator<<(manip2 manip) const {
			m_oOss << manip;
			return *this;
		}
		/// Insertor para un manipulador estandar.
		const MakeStr& operator<<(manip3 manip) const {
			m_oOss << manip;
			return *this;
		}
	};

    template<class T, class U>
    typename MakeStr<T,U>::HowToInsertUints MakeStr<T,U>::m_eHowToInsertUints = MakeStr<T,U>::AS_CHAR;

	/// \typedef MakeString Para evitar usar '<>'
	typedef MakeStr<char,std::char_traits<char> >		MakeString;

	/// \typedef MakeWString Para evitar usar '<>'
	typedef MakeStr<wchar_t,std::char_traits<wchar_t> >	MakeWString;



}	// str namespace


#endif		/*	MAKE_STRING_HPP_	*/




