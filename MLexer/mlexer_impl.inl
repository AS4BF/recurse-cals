#include <memory>
#include <deque>
#include <variant>
#include <stdexcept>

using std::string;
using std::deque;


template<typename... Types>
deque<typename Lexer<Types...>::vT> 
mlex::MLexer<Types...>::lexe(const string* expression) 
{
	this->it = expression->begin();
	this->end = expression->end();
	deque<typename Lexer<Types...>::vT> lexems;
	
	while(this->it < this->end) {

                if(std::isdigit(*(this->it))){
                        try{ lexems.push_front(parseNumber()); }
                        catch (std::out_of_range& error ) { throw error; };
                } else if(*this->it == Operation::Sub){
                        lexems.push_front(Operation::Sub);
                } else if(*this->it == Operation::Add){
                        lexems.push_front(Operation::Add);
                } else if(*this->it == Operation::Mul) {
                        lexems.push_front(Operation::Mul);
                } else if(*this->it == Operation::Div) {
                        lexems.push_front(Operation::Div);
                } else if(*this->it == Operation::Lbkt) {
                        lexems.push_front(Operation::Lbkt);
                } else if(*this->it == Operation::Rbkt) {
                        lexems.push_front(Operation::Rbkt);
                } else { throw string("Invalid syntax");
                };
                this->it++;
        };
	return lexems;
};

template<typename... Types>
typename Lexer<Types...>::vT
mlex::MLexer<Types...>::parseNumber() 
{
	bool is_float = false;
        string number = "";
        while(this->it < this->end && (std::isdigit(*this->it) || *this->it == '.' || *this->it == ',')) {
                if((*this->it == '.' || *this->it == ',') && this->it < this->end-1 && !is_float){
                        is_float = true;
                        number.push_back('.');
                } else if(std::isdigit(*this->it)) {
                        number.push_back(*this->it);
                } else { throw string("Invalid number"); }
                this->it++;
        };
        this->it--;
        try{
                if(!is_float){
                        return std::stoi(number);
                } else {
                        return std::stod(number);
                };
        } catch (std::out_of_range& error) { throw string("Out of range"); }
};


	
