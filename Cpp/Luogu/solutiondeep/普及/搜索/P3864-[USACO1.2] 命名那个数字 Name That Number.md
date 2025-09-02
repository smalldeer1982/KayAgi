# 题目信息

# [USACO1.2] 命名那个数字 Name That Number

## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。


## 样例 #1

### 输入

```
4734
NMSL
GREG
LSDC
....(太多了不写了)```

### 输出

```
GREG
```

# AI分析结果

### 综合分析与结论

该题目要求将给定的数字编号转换为可能的字母组合，并在字典中查找有效的名字。题解主要集中在以下思路：
1. **字母转数字匹配**：将字典中的名字转换为对应的数字序列，与输入的数字进行匹配。
2. **数字转字母生成**：通过DFS或BFS生成所有可能的字母组合，再与字典匹配。
3. **优化与剪枝**：通过长度剪枝、二分查找、哈希表等方式优化查找效率。

大部分题解采用了暴力枚举或简单的优化策略，整体思路较为直接，但部分题解在代码实现和优化上有亮点。以下是对各题解的简要评分与总结：

### 所选高星题解

#### 1. 作者：bjrjk (★★★★☆)
**关键亮点**：
- 使用`str_trans`数组将字母映射为数字，简化了匹配逻辑。
- 通过长度剪枝优化了匹配效率。
- 代码简洁且可读性高，适合初学者学习。

**核心代码**：
```cpp
for (int i = 0; i < Dict.size(); i++) {
    if (len != Dict[i].length()) continue; // 长度剪枝
    bool flag = true;
    for (int j = 0; j < len; j++) {
        if (str_trans[Dict[i][j] - 'A'] != str[j]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << Dict[i] << endl;
        global_flag = true;
    }
}
```

#### 2. 作者：cellur925 (★★★★☆)
**关键亮点**：
- 使用`map`存储字母到数字的映射，简化了匹配逻辑。
- 通过`check`函数进行逐字符匹配，逻辑清晰。
- 代码简洁且易于理解，适合初学者。

**核心代码**：
```cpp
bool check() {
    int lenw = strlen(word);
    if (lenw != len) return 0;
    for (int i = 0; i < len; i++)
        if (m[word[i]] != (int)(num[i] - '0')) return 0;
    return 1;
}
```

#### 3. 作者：zzqDeco (★★★★☆)
**关键亮点**：
- 通过预处理数组`X`将字母转换为数字，简化了匹配逻辑。
- 使用`vector`存储字典，代码结构清晰。
- 通过长度剪枝和逐字符匹配优化了效率。

**核心代码**：
```cpp
for (int i = 0; i <= 4616; i++) {
    d[i] = s[i];
    for (int j = 0; j <= s[i].size() - 1; j++) {
        s[i][j] = X[s[i][j] - 'A' + 1]; // 字母转数字
    }
}
```

### 最优关键思路与技巧
1. **字母到数字的映射**：通过预处理数组或`map`将字母映射为数字，简化匹配逻辑。
2. **长度剪枝**：在匹配前先比较长度，减少不必要的字符匹配。
3. **二分查找优化**：对字典进行排序后使用二分查找，提高查找效率。

### 可拓展之处
- **字典树（Trie）**：可以用于更高效地匹配字符串，尤其适用于大规模字典。
- **哈希表**：通过哈希表存储字典中的名字，进一步优化查找效率。

### 推荐相似题目
1. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019) - 考察字符串匹配与DFS。
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 考察组合生成与剪枝。
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040) - 考察树结构与动态规划。

### 个人心得摘录
- **bjrjk**：提到“剪枝”是优化匹配效率的关键，强调了长度剪枝的重要性。
- **cellur925**：提到“map”的使用简化了字母到数字的映射，代码更加简洁。
- **zzqDeco**：提到“预处理数组”的使用，减少了重复计算，提高了代码效率。

### 通用建议与扩展思路
对于此类题目，建议优先考虑字母到数字的映射，并结合剪枝、二分查找等优化策略。对于大规模数据，可以考虑使用字典树或哈希表进一步优化。

---
处理用时：40.22秒