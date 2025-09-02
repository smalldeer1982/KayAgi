# 题目信息

# Scrambled Scrabble

## 题目描述

你正在参与一个字母游戏，该游戏使用标准的26个大写英文字母A到Z。在这个游戏中，元音和辅音的构成规则如下：

- A, E, I, O, U 是元音。
- Y 可以作为元音或辅音。
- 除A, E, I, O, U和Y之外的其他字母只作为辅音。
- 子串NG可以作为一个整体看作辅音。

一个音节被定义为依次连接的辅音、元音和辅音。一个由一个或多个音节组成的字符串被定义为一个单词。

现在，给你一个字符串 $S$，你需要利用这个字符串中的字母构建一个单词。你可以从 $S$ 中删除任意数量的字母，并重新排列剩下的字母。请计算出可以构建的最长单词的长度，若无法构建任何单词，则返回0。

## 样例 #1

### 输入

```
ICPCJAKARTA```

### 输出

```
9```

## 样例 #2

### 输入

```
NGENG```

### 输出

```
5```

## 样例 #3

### 输入

```
YYY```

### 输出

```
3```

## 样例 #4

### 输入

```
DANGAN```

### 输出

```
6```

## 样例 #5

### 输入

```
AEIOUY```

### 输出

```
0```

# AI分析结果



# Scrambled Scrabble

## 题目描述

你正在参与一个字母游戏，该游戏使用标准的26个大写英文字母A到Z。在这个游戏中，元音和辅音的构成规则如下：

- A, E, I, O, U 是元音。
- Y 可以作为元音或辅音。
- 除A, E, I, O, U和Y之外的其他字母只作为辅音。
- 子串NG可以作为一个整体看作辅音。

一个音节被定义为依次连接的辅音、元音和辅音。一个由一个或多个音节组成的字符串被定义为一个单词。

现在，给你一个字符串 $S$，你需要利用这个字符串中的字母构建一个单词。你可以从 $S$ 中删除任意数量的字母，并重新排列剩下的字母。请计算出可以构建的最长单词的长度，若无法构建任何单词，则返回0。

## 综合分析与结论

本题的核心在于动态规划与贪心策略的结合，需要处理两个关键点：Y的双重角色和NG组合的灵活处理。每个音节的结构要求辅音-元音-辅音，且辅音部分可以是单字母或NG组合。解题的关键在于最大化音节数量，并在每个音节中尽可能使用更长的辅音单位（如NG）以增加总长度。

### 关键思路
1. **资源统计**：统计元音、辅音、Y、N、G的数目。
2. **动态枚举**：枚举Y作为元音的数量和NG的组合数目，计算每种情况下的音节数。
3. **贪心选择**：优先使用NG组合构造更长的辅音单位，提升总长度。

### 代码实现思路
1. **统计各字母出现次数**：包括元音、Y、N、G等。
2. **枚举Y的处理方式**：Y可以作为元音或辅音，枚举所有可能的分配方式。
3. **枚举NG的组合数目**：从0到可能的NG组合最大值，计算辅音资源。
4. **计算最大音节数**：根据元音和辅音数目确定可能的音节数。
5. **构造辅音列表**：按长度降序排序，取前2s个辅音单位计算总长度。

### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    unordered_map<char, int> cnt;
    for (char c : s) cnt[c]++;
    
    int A = cnt['A'], E = cnt['E'], I = cnt['I'], O = cnt['O'], U = cnt['U'];
    int vowels = A + E + I + O + U;
    int Y = cnt['Y'];
    int N = cnt['N'], G = cnt['G'];
    int other_consonant = 0;
    for (char c : s) {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y' || c == 'N' || c == 'G') continue;
        other_consonant++;
    }
    
    int max_len = 0;
    // 枚举Y作为元音的数量y_v
    for (int y_v = 0; y_v <= Y; ++y_v) {
        int v = vowels + y_v;
        int y_c = Y - y_v;
        // 枚举NG的组合数目k
        int max_k = min(N, G);
        for (int k = 0; k <= max_k; ++k) {
            int c_units = other_consonant + y_c + (N + G - k);
            int s = min(v, c_units / 2);
            if (s == 0) continue;
            // 构造辅音单位列表
            vector<int> units;
            units.insert(units.end(), k, 2); // NG
            units.insert(units.end(), N - k, 1); // 剩余N
            units.insert(units.end(), G - k, 1); // 剩余G
            units.insert(units.end(), other_consonant, 1); // 其他辅音
            units.insert(units.end(), y_c, 1); // Y作为辅音
            sort(units.rbegin(), units.rend());
            int sum = 0;
            for (int i = 0; i < min(2*s, (int)units.size()); ++i)
                sum += units[i];
            max_len = max(max_len, sum + s);
        }
    }
    cout << max_len << endl;
    return 0;
}
```

### 拓展建议
- 类似题目可参考动态规划中的资源分配问题，如背包问题的变种。
- 练习贪心策略在多重约束条件下的最优选择，如区间调度中的最大覆盖。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 贪心排序

---
处理用时：547.74秒