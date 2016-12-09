//
//  StageData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/10/06.
//
//

#ifndef StageData_h
#define StageData_h
#include "CommonData.h"

typedef struct StageData {
    const std::vector<int> enemy_ids;
    const int boss_id;
    const std::array<int, 2> normal_drop_rate;
    const std::array<int, 2> rare_drop_rate;
    const std::array<int, 2> super_rare_drop_rate;
} StageData;

extern const std::unordered_map<int, const StageData> stageDatas;

#endif /* StageData_h */
