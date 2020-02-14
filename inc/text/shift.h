#ifndef TEXT_SHIFT_H_INCLUDED
#define TEXT_SHIFT_H_INCLUDED
#include <string>

namespace Crypt {
	namespace Text {
		class Shift {
		private:
			int m_shift;
		public:
			using StrType = std::string; //could be std::string_view in future
			Shift();
			Shift(int shift);
			Shift(const Shift& other) = default;
			~Shift();
			Shift& operator=(const Shift& other) = default;

			const int& SHIFT = m_shift;
			std::string encrypt(const StrType& s) const;
			std::string decrypt(const StrType& s) const;

			static std::string encrypt(const StrType& s, int shift);
			static std::string decrypt(const StrType& s, int shift);
		};
		namespace Driver {
			int shift(char operation, int argc, char **argv);
		};
	};
};

#endif //TEXT_SHIFT_H_INCLUDED
