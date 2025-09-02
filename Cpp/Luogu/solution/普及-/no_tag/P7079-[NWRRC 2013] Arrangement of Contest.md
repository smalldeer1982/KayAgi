# [NWRRC 2013] Arrangement of Contest

## 题目描述

小D和小P想要举行比赛。

他们收到了许多建议书，现在他们想要从这些报名书中挑选一些好的建议。

他们采纳的建议符合以下标准：第一个建议的开头为A，第二个建议的开头为B，以此类推。

请你帮助他们，确定他们所能采纳的建议的最大数量。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n \leq 100$

## 样例 #1

### 输入

```
12
Arrangement_of_Contest
Ballot_Analyzing_Device
Correcting_Curiosity
Dwarf_Tower
Energy_Tycoon
Flight_Boarding_Optimization
Garage
Heavy_Chain_Clusterization
Intellectual_Property
J
Kids_in_a_Friendly_Class
Lonely_Mountain
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3
Snow_White_and_the_7_Dwarfs
A_Problem
Another_Problem
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
Good_Problem
Better_Problem
```

### 输出

```
0
```

# 题解

## 作者：Sora1336 (赞：11)

英 语 阅 读

题意翻译：给你一堆字符串，问这些字符串的首字母从 A 开始最长连接到哪个字符。

直接模拟即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int num, ans;
char s[114514];
bool vis[30];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%s", s);
        vis[s[0] - 'A'] = true;
    } for(int i = 0; i < 27; i ++) if(!vis[i]) return printf("%d\n", i) & 0;
}
```

---

