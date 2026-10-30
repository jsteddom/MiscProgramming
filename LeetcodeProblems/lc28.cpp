#include <iostream>
#include <string>
int strStr(std::string haystack, std::string needle) {
        int stringIDX { 0 };
        int indexNeedle { 0 };
        for (auto index { 0 }; index < haystack.size(); index++) {
            //std:: cout << "Needle size: " << needle.size() << " stringIDX: " << stringIDX;
            std::cout << "haystack idx: " << haystack[index] << " needle index: " << needle[stringIDX] << "\n";
            if (needle.size() == stringIDX) {
                return indexNeedle;
            }
            if (haystack[index] == needle[stringIDX]) {
                //std:: cout << "\nIn check: Index: " << haystack[index] << " NeedleIndex: " << needle[stringIDX] << " Needle size: " << needle.size() << " stringIDX: " << stringIDX;
                stringIDX++;
                if (needle.size() == 1 || needle.size() == stringIDX) {
                    return indexNeedle;
                }
                continue;
            }
            stringIDX = 0;
            index = indexNeedle;
            indexNeedle = index + 1;
        }

        return -1;
    }


int main() {
    std::cout << strStr("mississippi", "issip");

}