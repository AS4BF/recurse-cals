#include <variant>


using std::get;
using dT  = std::variant<int, double, char>;


inline bool is_lbkt(dT& token) {
	return get<char>(token) == '(';
};

inline bool is_rbkt(dT& token) {
	return get<char>(token) == ')';
};

inline bool is_char(dT& token) {
	return token.index() == 2;	
};

inline bool is_add(dT& token) {
	return get<char>(token) == '+';
};

inline bool is_sub(dT& token) {
	return get<char>(token) == '-';
};

inline bool is_mul(dT& token) {
	return get<char>(token) == '*';
};

inline bool is_div(dT& token) {
	return get<char>(token) == '/';
};

