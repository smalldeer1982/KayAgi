---
title: "New task"
layout: "post"
diff: 省选/NOI-
pid: CF788E
tag: []
---

# New task

## 题目描述

On the 228-th international Uzhlyandian Wars strategic game tournament teams from each country are called. The teams should consist of $ 5 $ participants.

The team of Uzhlyandia will consist of soldiers, because there are no gamers.

Masha is a new minister of defense and gaming. The prime duty of the minister is to calculate the efficiency of the Uzhlandian army. The army consists of $ n $ soldiers standing in a row, enumerated from $ 1 $ to $ n $ . For each soldier we know his skill in Uzhlyandian Wars: the $ i $ -th soldier's skill is $ a_{i} $ .

It was decided that the team will consist of three players and two assistants. The skills of players should be same, and the assistants' skills should not be greater than the players' skill. Moreover, it is important for Masha that one of the assistants should stand in the row to the left of the players, and the other one should stand in the row to the right of the players. Formally, a team is five soldiers with indexes $ i $ , $ j $ , $ k $ , $ l $ , $ p $ , such that $ 1<=i&lt;j&lt;k&lt;l&lt;p<=n $ and $ a_{i}<=a_{j}=a_{k}=a_{l}>=a_{p} $ .

The efficiency of the army is the number of different teams Masha can choose. Two teams are considered different if there is such $ i $ such that the $ i $ -th soldier is a member of one team, but not a member of the other team.

Initially, all players are able to be players. For some reasons, sometimes some soldiers become unable to be players. Sometimes some soldiers, that were unable to be players, become able to be players. At any time any soldier is able to be an assistant. Masha wants to control the efficiency of the army, so she asked you to tell her the number of different possible teams modulo $ 1000000007 $ ( $ 10^{9}+7 $ ) after each change.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of soldiers in Uzhlyandia.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the soldiers' skills.

The third line contains single integer $ m $ ( $ 1<=m<=10^{5} $ ) — the number of changes.

The next $ m $ lines contain the changes, each change is described with two integers $ t $ and $ x $ ( $ 1<=t<=2 $ , $ 1<=x<=n $ ) on a separate line. If $ t=1 $ , then the $ x $ -th soldier is unable to be a player after this change. If $ t=2 $ , then the $ x $ -th soldier is able to be a player after this change.

It is guaranteed that before each query of the first type the soldier is able to be a player, and before each query of the second type the soldier is unable to be a player.

## 输出格式

Print $ m $ integers — the number of distinct teams after each change.

Print the answers modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first example, after the first change the only team consists of soldiers $ [1,2,4,5,6] $ . After the second change any five soldiers can form a team.

In the first example after the first change the only team is soldiers $ [1,2,3,7,8] $ . After the second change the possible teams are: $ [1,2,3,5,7] $ , $ [1,2,3,5,8] $ , $ [1,2,3,7,8] $ , $ [1,2,5,7,8] $ , $ [1,3,5,7,8] $ , $ [2,3,5,7,8] $ . After the third change the possible teams are: $ [1,3,5,7,8] $ , $ [2,3,5,7,8] $ .

## 样例 #1

### 输入

```
6
1 1 1 1 1 1
2
1 3
2 3

```

### 输出

```
1
6

```

## 样例 #2

### 输入

```
8
3 4 4 2 4 5 4 1
3
1 5
2 5
1 2

```

### 输出

```
1
6
2

```

