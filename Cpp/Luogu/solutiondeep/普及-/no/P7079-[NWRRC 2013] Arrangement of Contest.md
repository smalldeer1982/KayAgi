# 题目信息

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

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
题目要求从一组字符串中找出首字母从A开始连续排列的最大数量。核心思路是通过记录每个首字母是否出现，然后从A开始检查连续出现的字母数量。该问题可以通过简单的模拟方法解决，无需复杂的算法。

### 所选题解
#### 题解作者：Sora1336 (赞：8)
- **星级**: 4星
- **关键亮点**: 直接模拟，思路清晰，代码简洁。
- **核心实现思想**: 使用一个布尔数组`vis`记录每个首字母是否出现，然后从A开始检查连续出现的字母数量，直到遇到未出现的字母为止。
- **代码片段**:
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

### 关键思路或技巧
- **数据结构**: 使用布尔数组记录每个首字母是否出现。
- **算法优化**: 通过从A开始检查连续出现的字母数量，避免不必要的遍历。

### 可拓展之处
- **同类型题**: 类似的问题可以扩展到检查字符串的其他属性，如长度、特定字符的出现次数等。
- **类似算法套路**: 使用数组记录状态，然后进行线性检查的模拟方法。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：17.10秒