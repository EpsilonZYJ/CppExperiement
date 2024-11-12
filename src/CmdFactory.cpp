#include "CmdFactory.hpp"

namespace adas {
    CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept{
        CmderList cmders;
        for(const auto& cmd : commands){
            auto it = cmderMap.find(cmd);   //
            cmders.push_back(it->second);   
        }
        return cmders;
    }
}