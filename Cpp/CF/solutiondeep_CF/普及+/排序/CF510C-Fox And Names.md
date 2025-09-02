# 题目信息

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 样例 #1

### 输入

```
3
rivest
shamir
adleman
```

### 输出

```
bcdefghijklmnopqrsatuvwxyz
```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz
```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
```

### 输出

```
acbdefhijklmnogpqrstuvwxyz
```

# AI分析结果



# Fox And Names

## 题目描述

狐狸 Ciel 将要发表一篇关于 FOCS（狐狸操作计算机系统，发音为"Fox"）的论文。她听说论文的作者列表总是按字典序排序的。

在检查了一些例子后，她发现有时情况并非如此。在某些论文中，作者姓名并没有按照通常意义的字典序排序。但经过对字母表中字母顺序的某种修改后，作者的顺序总能变成字典序！

她想知道，是否存在一种拉丁字母表的顺序，使得她提交的论文中的作者姓名按字典序排列。如果存在，你需要找出任意一种这样的顺序。

字典序的定义如下：当比较字符串 $s$ 和 $t$ 时，首先找到最左边不同字符的位置 $i$（即 $s_i \neq t_i$）。如果没有这样的位置（即一个是另一个的前缀），则较短的字符串较小。否则，根据字母表中字符的顺序比较 $s_i$ 和 $t_i$。

## 样例 #1

### 输入

```
3
rivest
shamir
adleman
```

### 输出

```
bcdefghijklmnopqrsatuvwxyz
```

---

# 题解分析与结论

## 核心思路总结
**拓扑排序**是解决该问题的核心算法，关键步骤如下：

1. **构建字符顺序约束**  
   - 比较相邻字符串，找到首个不同字符建立有向边（前字符→后字符）
   - 特判：若后串是前串的真前缀且更短，直接输出`Impossible`

2. **拓扑排序检测环**  
   - 通过BFS/DFS进行拓扑排序，结果需包含26个字母
   - 若存在环或无法包含全部字母，则无解

3. **处理独立字符**  
   - 未参与约束的字母按常规顺序填充

## 精选题解（评分≥4⭐）

### 1. 杨誉yy（5⭐）
**亮点**：
- 完整处理前缀特判（`j <= len`循环巧妙处理包含关系）
- 使用邻接表+BFS拓扑，逻辑清晰
- 代码包含详细注释和边界处理

**核心代码**：
```cpp
for(i=2;i<=n;i++) {
    cin>>now;
    int len = min(pas.length(), now.length());
    for(j=0; j<=len; j++) { // 关键：j<=len处理前缀情况
        if(j == len) {
            if(pas.length() > now.length()) { // 后串是前串的真前缀
                printf("Impossible");
                return 0;
            }
            break;
        }
        if(pas[j] != now[j]) {
            int up = pas[j]-'a', down = now[j]-'a';
            l[up][++cnt[up]] = down; // 邻接表建图
            num[down]++;
            break;
        }
    }
    pas = now;
}
```

### 2. Juanzhang（4⭐）
**亮点**：
- DFS递归拓扑排序，代码简洁
- 三色标记法（vis数组）巧妙判环
- 逆序输出结果实现字典序最小

**核心代码**：
```cpp
bool dfs(int u) {
    if(vis[u]) return vis[u] > 1; // 1: 环, 2: 已处理
    vis[u] = 1;
    for(int v : e[u]) 
        if(!dfs(v)) return false;
    a[++now] = u; // 递归结束时记录拓扑序
    vis[u] = 2;
    return true;
}
```

### 3. kdy20100729（4⭐）
**教训总结**：
- 最初未处理前缀特判导致WA
- 补充特判后AC，强调边界条件的重要性

**修正代码**：
```cpp
if(j == min(s[i-1].size(), s[i].size()) 
   && s[i-1].size() > s[i].size()) {
    cout << "Impossible";
    return 0;
}
```

---

## 关键技巧与优化
1. **相邻比较优化**  
   只需比较相邻字符串而非全部组合，时间复杂度从O(n²)降为O(n)

2. **三色标记法**  
   在DFS拓扑中，使用0/1/2标记状态，同时完成环检测和拓扑排序

3. **字符顺序填充**  
   拓扑序外的字母按常规顺序追加，确保结果完整性

---

## 类似题目推荐
1. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)  
   （拓扑排序+DP计算最长路径）

2. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)  
   （拓扑排序构建层级关系）

3. [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)  
   （拓扑排序+动态规划统计路径）

---
处理用时：54.29秒