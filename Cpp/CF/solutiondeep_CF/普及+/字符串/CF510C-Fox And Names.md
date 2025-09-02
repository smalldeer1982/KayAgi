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

狐狸 Ciel 准备在 FOCS（狐狸操作计算机系统，发音为“Fox”）上发表论文。她听说论文的作者列表总是按字典序排列的。但经过检查后她发现，某些情况下这并不是真的。有些论文的作者名字并不是按正常字典序排列的，但总能通过修改字母表的顺序使得作者列表满足字典序。

你的任务是判断是否存在一种字母表的顺序，使得给定的作者列表是按该字典序排列的。如果存在，请输出任意一种可能的字母表顺序；否则输出 "Impossible"。

字典序定义如下：比较字符串 $s$ 和 $t$ 时，找到第一个不同的字符 $s_i \neq t_i$。若不存在这样的位置，则较短的字符串更小。否则，按字母表中字符的顺序比较 $s_i$ 和 $t_i$。

---

### 题解分析与结论

所有题解的核心思路均为拓扑排序，通过比较相邻字符串建立字符间的偏序关系。关键步骤如下：

1. **相邻字符串比较**：对每对相邻字符串，找到第一个不同的字符，建立从前字符指向后字符的有向边。
2. **前缀特判**：若前字符串是后字符串的前缀且更长，直接输出 "Impossible"。
3. **拓扑排序判环**：若拓扑序列包含全部 26 个字母则合法，否则存在环或矛盾。

---

### 精选题解

#### 1. 杨誉yy（★★★★★）
**亮点**：
- 代码结构清晰，处理了所有边界条件（包括前缀特判）
- 使用邻接表建图，BFS拓扑排序逻辑简明
- 注释详细，变量命名规范

**核心代码**：
```cpp
for(i=2;i<=n;i++) {
    cin>>now;
    int len=min(pas.length(),now.length());
    for(j=0;j<=len;j++) { // 注意是<=len
        if(j==len) { // 处理前缀情况
            if(pas.length()>now.length()) {
                printf("Impossible");
                return 0;
            }
            break;
        }
        if(pas[j]!=now[j]) {
            int up=pas[j]-'a', down=now[j]-'a'; 
            l[up][++cnt[up]]=down; // 建边
            num[down]++;
            break;    
        }        
    }
    pas=now;
}
```

#### 2. lym12321（★★★★☆）
**亮点**：
- 使用优先队列保证输出字典序最小解
- 独立处理每个字符的入度计算
- 模块化函数设计（如拓扑排序单独封装）

**核心片段**：
```cpp
priority_queue <int> q; // 小根堆技巧
for(int i=0;i<26;i++) 
    if(!deg[i]) q.push(-i); 
while(!q.empty()){
    int k = -q.top(); 
    ans[++cnt] = k + 'a';
    // 更新入度并处理相邻节点
}
```

#### 3. kdy20100729（★★★★☆）
**亮点**：
- 代码简洁，直接使用字符而非索引操作
- 明确处理了前缀特判的漏写问题
- 注释中给出了典型反例的调试过程

**关键修正**：
```cpp
for(int j=0; j<min(s[i-1].size(),s[i].size()); j++) {
    // ...比较字符
}
// 补丁：检查是否因前缀导致矛盾
if(j==min(...) && s[i-1].size()>s[i].size()) 
    ThrowOut();
```

---

### 关键技巧总结

1. **邻接比较建图**：仅需比较相邻字符串，无需全排列，复杂度优化至 $O(N)$。
2. **前缀特判**：当后字符串是前字符串的前缀且更短时立即判定非法。
3. **拓扑判环**：通过最终序列长度是否为26判断是否存在合法解。
4. **字符索引转换**：统一将字符映射为 `0-25` 的索引，避免越界问题。

---

### 相似题目推荐

1. [P1113 杂务](https://www.luogu.com.cn/problem/P1113) - 拓扑排序在任务调度中的应用
2. [P1347 排序](https://www.luogu.com.cn/problem/P1347) - 通过偏序关系确定顺序
3. [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017) - 拓扑排序结合动态规划

---

### 题解心得摘录

- **kdy20100729**：在调试中发现未处理前缀特判导致WA，强调测试用例的重要性。
- **Juanzhang**：通过DFS实现拓扑排序，但指出“代码简短但判环不够直观”。
- **Enterpr1se**：尝试用Floyd传递闭包判环，最终回归拓扑排序，体现算法选择过程。

---
处理用时：53.24秒