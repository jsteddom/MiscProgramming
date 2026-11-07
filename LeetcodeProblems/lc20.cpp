#include <iostream>
#include <vector>
#include <string>

bool isValid(std::string s) {
        std::vector<char> stack;
        char ch;
        for (char chr : s){
            std::cout << "\n chr: " << chr;
            switch(chr) {
                case '(':
                    stack.push_back(chr);
                    break;
                case '[':
                    stack.push_back(chr);
                    break;
                case '{':
                    stack.push_back(chr);
                    break;
                case ')':
                    if (stack.size() < 1) {
                        return false;
                    }
                    ch = stack.back();
                    if (ch != '(') {
                        return false;
                    }
                    stack.pop_back();
                    break;
                case ']':
                    if (stack.size() < 1) {
                        return false;
                    }
                    ch = stack.back();
                    if (ch != '[') {
                        return false;
                    }
                    stack.pop_back();
                    break;
                case '}':
                    if (stack.size() < 1) {
                        return false;
                    }
                    ch = stack.back();
                    if (ch != '{') {
                        return false;
                    }
                    stack.pop_back();
                    break;
            }
        //  (())
        
        }
        if (stack.size() > 0) {
            return false;
        }
        return true;
    
    } 
int main() {
    std::cout << isValid("()[]");
    return 0;
}