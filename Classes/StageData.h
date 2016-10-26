//
//  StageData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/10/06.
//
//

#ifndef StageData_h
#define StageData_h

typedef struct StageData {
    const std::array<int, 3> enemy_ids;
    const int hp;
    const int attack;
    const int ap;
} StageData;


#endif /* StageData_h */
