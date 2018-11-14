#ifndef __SURF_BWT_H__
#define __SURF_BWT_H__


#include <string>

namespace surf {
namespace bwt {

class Bwt {
public:
    static std::string Transform(std::string source);
    static std::string Revert(std::string target);

//private:
    static std::string Rotate(std::string source, int chars);
    static std::vector<int> SuffixArray(std::string source);
};

} // end namespace bwt
} // end namespace surf

#endif
