#include "bwt.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

namespace surf {
namespace bwt {

std::string Bwt::Transform(std::string source) {
    std::string result;
#ifndef BWT_FROM_SA
    source.push_back('$');
    std::vector<std::string> rotations;
    for (int i = 1; i <= source.size(); ++i) {
        rotations.push_back(Bwt::Rotate(source, i));
    }

    std::sort(rotations.begin(), rotations.end());

    int len = source.size();
    for (auto str : rotations) {
        result.push_back(str[len - 1]);
    }
#else
    std::vector<int> sa = Bwt::SuffixArray(source);
    for (int i = 0; i <= source.size(); ++i) {
        result.push_back(sa[i] == 0 ? '$' : source[sa[i] - 1]);
    }
#endif
    return result;
}

std::string Bwt::Revert(std::string target) {
    return target;
}

std::string Bwt::Rotate(std::string source, int chars) {
    int len = source.size();
    if (len <= 1) {
        return source;
    }

    return source.substr(len - chars, chars) + source.substr(0, len - chars);
}

std::vector<int> Bwt::SuffixArray(std::string source) {
    std::vector<int> result;
    std::vector<std::pair<std::string, int>> suffixs;
    source.push_back('$');
    int len = source.size();
    for (int i = 0; i < len; ++i) {
        suffixs.push_back(std::make_pair(source.substr(i, len - i), i));
    }
    std::sort(suffixs.begin(), suffixs.end(), [](const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) {
              return left.first < right.first;}
              );

    result.resize(suffixs.size());
    std::transform(suffixs.begin(), suffixs.end(), result.begin(), [](const std::pair<std::string, int>& entry){
                   return entry.second;}
                   );
    return result;
}

} // end namespace bwt
} // end namespace surf


