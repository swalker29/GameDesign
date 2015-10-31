#ifndef CAMPAIGNSTATE_HPP
#define CAMPAIGNSTATE_HPP

#include "AppState.hpp"

class CampaignState : public AppState {
    public:
        CampaignState();
        void handle(GameApp& gameApp);
};

#endif
