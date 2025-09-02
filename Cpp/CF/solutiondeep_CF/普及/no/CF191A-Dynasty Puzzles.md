# 题目信息

# Dynasty Puzzles

## 题目描述

The ancient Berlanders believed that the longer the name, the more important its bearer is. Thus, Berland kings were famous for their long names. But long names are somewhat inconvenient, so the Berlanders started to abbreviate the names of their kings. They called every king by the first letters of its name. Thus, the king, whose name was Victorious Vasily Pupkin, was always called by the berlanders VVP.

In Berland over its long history many dynasties of kings replaced each other, but they were all united by common traditions. Thus, according to one Berland traditions, to maintain stability in the country, the first name of the heir should be the same as the last name his predecessor (hence, the first letter of the abbreviated name of the heir coincides with the last letter of the abbreviated name of the predecessor). Berlanders appreciate stability, so this tradition has never been broken. Also Berlanders like perfection, so another tradition requires that the first name of the first king in the dynasty coincides with the last name of the last king in this dynasty (hence, the first letter of the abbreviated name of the first king coincides with the last letter of the abbreviated name of the last king). This tradition, of course, has also been always observed.

The name of a dynasty is formed by very simple rules: we take all the short names of the kings in the order in which they ruled, and write them in one line. Thus, a dynasty of kings "ab" and "ba" is called "abba", and the dynasty, which had only the king "abca", is called "abca".

Vasya, a historian, has recently found a list of abbreviated names of all Berland kings and their relatives. Help Vasya to find the maximally long name of the dynasty that could have existed in Berland.

Note that in his list all the names are ordered by the time, that is, if name $ A $ is earlier in the list than $ B $ , then if $ A $ and $ B $ were kings, then king $ A $ ruled before king $ B $ .

## 说明/提示

In the first sample two dynasties can exist: the one called "abcca" (with the first and second kings) and the one called "abccba" (with the first and third kings).

In the second sample there aren't acceptable dynasties.

The only dynasty in the third sample consists of one king, his name is "c".

## 样例 #1

### 输入

```
3
abc
ca
cba
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
vvp
vvp
dam
vvp
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
ab
c
def
```

### 输出

```
1
```

# AI分析结果



# Dynasty Puzzles 王朝之谜

## 题目描述

古代 Berlanders 认为名字越长，其拥有者就越重要。因此，Berland 的国王以长名著称。但长名使用不便，于是 Berlanders 开始用名字的首字母缩写来称呼国王。例如，国王 Victorious Vasily Pupkin 被缩写为 VVP。

根据传统，继承人的名字首字母必须与前任的末字母相同（即前国王缩写名的末字母与继承者缩写名的首字母相同），且王朝的首位国王缩写名的首字母必须与末位国王的末字母相同。这些传统从未被打破。

历史学家 Vasya 发现了一份按时间顺序排列的国王缩写名列表。请帮助他找出可能存在的最大王朝名称长度。

## 输入输出样例

### 样例 #1
输入：
3
abc
ca
cba
输出：
6

### 样例 #2
输入：
4
vvp
vvp
dam
vvp
输出：
0

### 样例 #3
输入：
3
ab
c
def
输出：
1

---

**算法分类**: 动态规划

---

## 题解综合分析

### 核心思路对比
所有题解均采用动态规划思路，核心状态定义为：
- `dp[i][j]` 表示以字母 i 开头、j 结尾的合法王朝名称最大长度

**共性特征**：
1. 遍历每个字符串时，提取首尾字母 (l, r) 和长度 len
2. 状态转移：`dp[j][r] = max(dp[j][r], dp[j][l] + len)`（其中 j 遍历所有可能的前缀开头字母）
3. 维护自洽状态：`dp[l][r] = max(dp[l][r], len)`
4. 最终答案为所有 `dp[i][i]` 的最大值

**关键差异**：
- 珅肐的题解采用在线处理方式，内存效率最优
- complete_binary_tree 详细分析了三维降二维的空间优化过程
- baiABC 的题解强调有向图建模思路，最终回归到 DP 解法

### 最优题解推荐

#### 1. 珅肐（⭐⭐⭐⭐⭐）
**核心亮点**：
- 代码简洁高效，在线处理每个字符串
- 正确维护状态转移关系
- 使用字符直接映射的数组索引（无冗余转换）

**关键代码**：
```cpp
int f[27][27];
for(int i=1;i<=n;++i){
    scanf("%s",c);
    int len=strlen(c),l=c[0]-'a',r=c[len-1]-'a';
    for(int j=0;j<26;++j)
        if(f[j][l]) f[j][r]=max(f[j][r],f[j][l]+len);
    f[l][r]=max(f[l][r],len);
}
```

#### 2. complete_binary_tree（⭐⭐⭐⭐）
**核心贡献**：
- 详细阐述三维降二维的优化思路
- 强调状态转移的时序特性
- 通过滚动数组避免 MLE

**调试心得**：
> "如果这时你高高兴兴地打代码，上交，会发现它 MLE 了... 我们发现每个第 i 层的 dp 都是由第 i-1 层转移过来的，因此可以压缩维度"

#### 3. baiABC（⭐⭐⭐）
**思维亮点**：
- 尝试用有向图建模（首尾字母为边）
- 最终回归 DP 解法的合理性分析
- 强调时间顺序带来的无后效性

---

## 关键算法技巧

1. **状态压缩**：将问题抽象为二维状态（首字母、末字母）
2. **滚动更新**：每个字符串处理时直接覆盖原数组，避免存储历史状态
3. **在线处理**：无需存储所有字符串，逐个处理节省内存
4. **闭合检测**：通过 `dp[i][i]` 自然检测首尾闭合条件

---

## 拓展训练

1. [P1435 回文字串](https://www.luogu.com.cn/problem/P1435)  
   - 相似点：字符串首尾特性处理
2. [P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095)  
   - 相似点：状态转移的时间序列特性
3. [CF455A Boredom](https://codeforces.com/problemset/problem/455/A)  
   - 相似点：基于字符频次的动态规划

---

## 个人心得摘录

**珅肐**：  
> "注意转移时的合法性判断，只有存在前置状态时才进行转移"  
—— 确保状态转移的有效性，避免非法状态污染结果

**complete_binary_tree**：  
> "三维数组开 5e5×26×26 会 MLE，必须降维"  
—— 空间优化是处理大规模 DP 问题的关键考量

**dyc2022**：  
> "结果串的首字符和末字符必须相同，这通过遍历 dp[i][i] 自然实现"  
—— 巧用状态定义本身特性简化结果检测

---
处理用时：60.39秒