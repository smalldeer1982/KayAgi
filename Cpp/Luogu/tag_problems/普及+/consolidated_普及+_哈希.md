---
title: "[蓝桥杯 2024 省 A] 团建"
layout: "post"
diff: 普及+/提高
pid: P10388
tag: ['2024', '哈希 hashing', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 A] 团建
## 题目描述

小蓝正在和朋友们团建，有一个游戏项目需要两人合作，两个人分别拿到一棵大小为 $n$ 和 $m$ 的树，树上的每个结点上有一个正整数权值。  
两个人需要从各自树的根结点 $1$ 出发走向某个叶结点，从根到这个叶结点的路径上经过的所有结点上的权值构成了一个正整数序列，两人的序列的最长公共前缀即为他们的得分。给出两棵树，请计算两个人最多的得分是多少。
## 输入格式

输入的第一行包含两个正整数 $n, m $，用一个空格分隔。  
第二行包含 $n$ 个正整数 $c_1, c_2,\cdots , c_n $，相邻整数之间使用一个空格分隔，其中 $c_i$ 表示第一棵树结点 $i$ 上的权值。  
第三行包含 $m$ 个正整数 $d_1, d_2,\cdots, d_m$，相邻整数之间使用一个空格分隔，其中 $d_i$ 表示第二棵树结点 $i$ 上的权值。  
接下来 $n - 1$ 行，每行包含两个正整数 $u_i
, v_i$ 表示第一棵树中包含一条 $u_i$ 和
$v_i$ 之间的边。  
接下来 $m - 1$ 行，每行包含两个正整数 $p_i
, q_i$ 表示第二棵树中包含一条 $p_i$
和 $q_i$ 之间的边。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
2 2
10 20
10 30
1 2
2 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
5 4
10 20 30 40 50
10 40 20 30
1 2
1 3
2 4
3 5
1 2
1 3
3 4
```
### 样例输出 #2
```
2
```
## 提示

对于 $20\%$ 的评测用例，$1 ≤ n, m ≤ 500 $；  
对于所有评测用例，$1 ≤ n, m ≤ 2 × 10^5，1 ≤ c_i
, d_i ≤ 10^8 ，1 ≤ u_i
, v_i ≤ n ，
1 ≤ p_i
, q_i ≤ m $，对于任意结点，其儿子结点的权重互不相同。


---

---
title: "后缀数组"
layout: "post"
diff: 普及+/提高
pid: P10469
tag: ['二分', '排序', '哈希 hashing']
---
# 后缀数组
## 题目描述

后缀数组 (SA) 是一种重要的数据结构，通常使用倍增或者 DC3 算法实现，这超出了我们的讨论范围。

在本题中，我们希望使用快排、Hash 与二分实现一个简单的 $O(n\log^2n)$ 的后缀数组求法。

详细地说，给定一个长度为 $n$ 的字符串 $S$（下标 $0 \sim n-1$），我们可以用整数 $k(0 \le k < n)$ 表示字符串 $S$ 的后缀 $S(k \sim n-1)$。

把字符串 $S$ 的所有后缀按照字典序排列，排名为 $i$ 的后缀记为 SA[i]。

额外地，我们考虑排名为 $i$ 的后缀与排名为 $i-1$ 的后缀，把二者的最长公共前缀的长度记为 Height[i]。

我们的任务就是求出 SA 与 Height 这两个数组。
## 输入格式

输入一个字符串，其长度不超过 $30$ 万。

字符串由小写字母构成。
## 输出格式

第一行为数组 SA，相邻两个整数用 $1$ 个空格隔开。

第二行为数组 Height，相邻两个整数用 $1$ 个空格隔开，我们规定 Height[1]=0。
## 样例

### 样例输入 #1
```
ponoiiipoi
```
### 样例输出 #1
```
9 4 5 6 2 8 3 1 7 0
0 1 2 1 0 0 2 1 0 2
```


---

---
title: "[BeiJing2011] Matrix 矩阵哈希"
layout: "post"
diff: 普及+/提高
pid: P10474
tag: ['北京', '哈希 hashing']
---
# [BeiJing2011] Matrix 矩阵哈希
## 题目描述

给定一个 $M$ 行 $N$ 列的 $01$ 矩阵，以及 $Q$ 个 $A$ 行 $B$ 列的 $01$ 矩阵，你需要求出这 $Q$ 个矩阵哪些在原矩阵中出现过。 

所谓 $01$ 矩阵，就是矩阵中所有元素不是 $0$ 就是 $1$。
## 输入格式

输入文件的第一行为 $M,N,A,B$，参见题目描述。 

接下来 $M$ 行，每行 $N$ 个字符，非 $0$ 即 $1$ ，描述原矩阵。 

接下来一行为你要处理的询问数 $Q$。

接下来 $Q$ 个矩阵，一共 $Q\times A$ 行，每行 $B$ 个字符，描述 $Q$ 个 $01$ 矩阵。
## 输出格式

你需要输出 $Q$ 行，每行为 $0$ 或者 $1$，表示这个矩阵是否出现过，$0$ 表示没有出现过，$1$ 表示出现过。
## 样例

### 样例输入 #1
```
3 3 2 2
111
000
111
3
11
00
11
11
00
11
```
### 样例输出 #1
```
1
0
1
```
## 提示

对于 $100\%$ 的实际测试数据，$1\leq M,N \leq 1000$，$Q = 1000$。 

对于 $40\%$ 的数据，$A = 1$。

对于 $80\%$ 的数据，$A \leq 10$。

对于 $100\%$ 的数据，$A \leq 100$。


---

---
title: "[USACO03FALL] Milking Grid（数据加强版）"
layout: "post"
diff: 普及+/提高
pid: P10475
tag: ['USACO', '哈希 hashing', 'KMP 算法']
---
# [USACO03FALL] Milking Grid（数据加强版）
## 题目描述

Every morning when they are milked, the Farmer John's cows form a rectangular grid that is $R (1 \leq R \leq 10,000)$ rows by $C (1 \leq C \leq 75)$ columns. As we all know, Farmer John is quite the expert on cow behavior, and is currently writing a book about feeding behavior in cows. He notices that if each cow is labeled with an uppercase letter indicating its breed, the two-dimensional pattern formed by his cows during milking sometimes seems to be made from smaller repeating rectangular patterns.

Help FJ find the rectangular unit of smallest area that can be repetitively tiled to make up the entire milking grid. Note that the dimensions of the small rectangular unit do not necessarily need to divide evenly the dimensions of the entire milking grid, as indicated in the sample input below.
## 输入格式

- Line $1$: Two space-separated integers: $R$ and $C$

- Lines $2\dots R+1$: The grid that the cows form, with an uppercase letter denoting each cow's breed. Each of the $R$ input lines has $C$ characters with no space or other intervening character.
## 输出格式

- Line 1: The area of the smallest unit from which the grid is formed
## 样例

### 样例输入 #1
```
2 5 
ABABA 
ABABA

```
### 样例输出 #1
```
2
```
## 提示

The entire milking grid can be constructed from repetitions of the pattern `AB`.
## 题目翻译

**【题目描述】**

每天早上挤奶时，农夫约翰的奶牛们排成一个 $R (1 \leq R \leq 10,000)$ 行乘 $C (1 \leq C \leq 75)$ 列的矩形网格。众所周知，约翰农夫是一个相当擅长牛行为的专家，目前正在撰写一本关于奶牛饲养行为的书。他注意到，如果每头奶牛都标有一个表示其品种的大写字母，那么奶牛在挤奶时形成的二维图案有时似乎是由更小的重复矩形图案组成的。

帮助约翰农夫找到可以重复铺设以组成整个挤奶网格的最小面积的矩形单元。请注意，小矩形单元的尺寸不一定需要完全整除整个挤奶网格的尺寸，如下面的示例输入所示。

**【输入格式】**

- 第一行：两个用空格分隔的整数：$R$ 和 $C$
- 第 $2\dots R+1$ 行：奶牛形成的网格，每个奶牛的品种用大写字母表示。每个 $R$ 输入行有 $C$ 个字符，没有空格或其他间隔字符。

**【输出格式】**

第一行：形成网格的最小单位的面积

**【提示说明】**

整个挤奶网格可以由图案 AB 的重复构建。

翻译来自于：ChatGPT。


---

---
title: "数组的划分"
layout: "post"
diff: 普及+/提高
pid: P11901
tag: ['线段树', '后缀自动机 SAM', '动态树 LCT', '哈希 hashing', '分块']
---
# 数组的划分
## 题目背景

本来这里应该有一段一脉相承的背景故事。但是因为福尔魔斯验题的时候写吐了，所以背景故事没了。
## 题目描述

给出 $m$ 个数组 $s_1, s_2, \cdots s_m$ 和一个长为 $n$ 的数组 $t$。

定义 $f(l,r)$ 表示在所有 "把 $t_l...t_r$ 分成若干段，要求每一段都是 $s$ 中某个数组的子段" 的方式中，划分段数的最小值。

有以下操作：

1. 强制限定 $p,p+1$ 处必须划分，如果已经有了则取消。

2. 将 $t$ 的区间 $[l, r]$ 改成数组 $a$，会给出 $a$，每次的 $a$ 可能不一样。

3. 询问 $f(l,r)$，保证有解。

请你完成这些操作。

## 输入格式

第一行四个数，$n,m,q,id$，表示 $t$ 的长度，总共有多少个文本数组 $s$，操作数，以及数据类型（参见说明）。

接下来 $m$ 行，每行先给出一个数 $k$，代表 $s_i$ 的长度，然后 $k$ 个数给出 $s_i$ 这个数组的元素。

下一行，给出 $n$ 个数，表示 $t$ 中的元素。

接下来 $q$ 行，每行表示一个操作，分别如下：

1. $1\ x$，表示若 $x,x+1$ 处不必须划分，则标为必须划分，否则取消。

2. $2\ l\ r\ a_1\ a_2 \cdots a_{r-l+1}$，表示令 $\forall l \le i \le r，t_i = a_{i-l+1}$。

3. $3\ l\ r$，表示询问 $f(l,r)$。
## 输出格式

对于每次询问，输出一个数表示答案。每个答案占一行。
## 样例

### 样例输入 #1
```
5 3 7 0
3 1 2 3 
4 3 2 2 2 
3 3 2 2 
2 3 3 2 1 
3 1 5
1 3
3 1 5
2 2 4 1 3 2
3 1 5
1 3
3 1 5
```
### 样例输出 #1
```
3
4
5
4
```
### 样例输入 #2
```
10 5 20 0
3 1 2 3 
5 3 3 1 1 3 
10 1 2 1 1 2 3 2 1 1 3 
2 1 1 
2 1 3 
1 3 2 3 3 1 3 3 2 3 
1 4
2 7 7 3 
3 3 9
1 4
1 2
2 5 5 2 
1 2
2 7 7 2 
1 1
3 5 8
2 4 4 1 
3 3 8
1 1
1 3
2 6 6 1 
2 1 1 1 
2 4 4 2 
1 7
3 1 5
3 1 9
```
### 样例输出 #2
```
4
2
3
4
6
```
## 提示

## 样例解释

对于第一组样例，初始数组为 $[2,3,3,2,1]$ ，段数最小分割的方式为 $[2,3|3,2|1]$ ，故输出 $3$ 。然后限制了 $3,4$ 之间必须分割，故最小的分割方式为 $[2,3|3|2|1]$ ，输出为 $4$ 。之后数组被修改为 $[2,1,3,2,1]$ ，段数最小的分割方式为 $[2|1|3|2|1]$ ，故输出 $5$ 。最后取消了 $3,4$ 之间必须分割的限制，最小分割方式为 $[2|1|3,2|1]$ ，输出 $4$ 。

-----

## 数据范围

记 $\sum\limits_{i=1}^m |s_i|= M$ ，对于所有操作 2， $\sum\limits_{i=1}^t |r_i-l_i+1| = T$ ，其中 $t$ 是操作 2 的出现次数， $V$ 为数组中和修改后的数组中的元素的最大值，则各数据点的限制如下：

| 测试点 | $n, M, q \leq$ | $T\leq$ | $V\leq$ | $id=$ | 特殊性质|
| :-----------: | :-----------: |  :-----------: | :-----------: | :-----------: | :-----------: |
| $1\sim3$ | $50$ | $10^5$ | $10^9$ | $1$ | 无 |
| $4$ | $1000$ | $1000$ | $10^9$ | $2$ | 无 |
| $5$ | $1000$ | $0$ | $4$ | $3$ | 保证没有操作 1, 2 |
| $6\sim7$ | $1000$ | $0$ | $4$ | $4$ | 保证没有操作 2 |
| $8\sim11$ | $1000$ | $1000$ | $4$| $5$ | 无 |
| $12$ | $10^5$ | $10^5$ | $10^9$| $6$ | 无 |
| $13\sim14$ | $10^5$ | $0$ | $4$| $7$ | 保证没有操作 1, 2 |
| $15\sim17$ | $10^5$ | $0$ | $4$| $8$ | 保证没有操作 2 |
| $18\sim25$ | $10^5$ | $10^5$ | $4$| $9$ | 无 |

对于所有数据，保证 $1\le n,M,q\le10^5, 0\le T\le 10^5,1\le V\le10^9, 1\le id\le9, l\le r$ 。$a,t$ 中的所有数都在 $s$ 中出现。

**保证给出的数组随机，但是询问的区间与询问的操作并不随机**。具体而言，初始给出的 $s,t$ 以及询问时可能给出的 $a$ 在符合上文所述限制之下的所有可能情况中等概率选取。而其他数据则不是随机的。


---

---
title: "Hash Killer I"
layout: "post"
diff: 普及+/提高
pid: P12197
tag: ['Special Judge', '哈希 hashing', '构造']
---
# Hash Killer I
## 题目描述

这天天气不错，hzhwcmhf 神犇给 VFleaKing 出了一道题：

给你一个长度为 $n$ 的字符串 $s$，求有多少个不同的长度为 $l$ 的连续子串。

两个字符串被认为是不同的当且仅当某个位置上的字符不同。

VFleaKing 一看觉得这不是 Hash 的裸题么！于是果断写了哈希 + 排序。

而 hzhwcmhf 神犇心里自然知道，这题就是后缀数组的 height 中 $< l$ 的个数 +1，就是后缀自动机上代表的长度区间包含 $l$ 的结点个数，就是后缀树深度为 $l$ 的结点的数量。

但是 hzhwcmhf 神犇看了看 VFleaKing 的做法表示非常汗。于是想卡掉他。

VFleaKing 使用的是字典序哈希，其代码大致如下：

```cpp
u64 val = 0;
for (int i = 0; i < l; i++)
    val = val * base + s[i] - 'a';
```

u64 是无符号 int64，范围是 $[0, 2^{64})$。VFleaKing 让 val 自然溢出。

base 是一个常量，VFleaKing 会根据心情决定其值。

VFleaKing 还求出来了 $base^l$，即 base 的 $l$ 次方，这样就能方便地求出所有长度为 $l$ 的子串的哈希值。

然后 VFleaKing 给哈希值排序，去重，求出有多少个不同的哈希值，把这个数作为结果。

其算法的 C++ 代码如下:

```cpp
typedef unsigned long long u64;
const int MaxN = 100000;
inline int hash_handle(const char *s, const int &n, const int &l, const int &base)
{
    u64 hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l *= base;
    int li_n = 0;
    static u64 li[MaxN];
    u64 val = 0;
    for (int i = 0; i < l; i++)
        val = val * base + s[i] - 'a';
    li[li_n++] = val;
    for (int i = l; i < n; i++)
    {
        val = val * base + s[i] - 'a';
        val -= (s[i - l] - 'a') * hash_pow_l;
        li[li_n++] = val;
    }
    sort(li, li + li_n);
    li_n = unique(li, li + li_n) - li;
    return li_n;
}
```

hzhwcmhf 当然知道怎么卡啦！但是他想考考你。
## 输出格式

你需要输出一组数据使得 VFleaKing 的代码 WA 掉。我们会使用 Special Judge 检查你的结果的正确性。

输出文件共两行。

第一行两个用空格隔开的数 $n, l$。

第二行是一个长度为 $n$ 的字符串。只能包含小写字母。

需要保证 $1 \le n \le 10^5, 1 \le l \le n$，不符合以上格式会 WA。不要有多余字符，很可能导致你 WA。
## 提示

本题的评分为：在 SPJ 中预设了 10 个 base 用作测试，每让一个 base 出现哈希冲突记 10 分，满分为 100 分。


---

---
title: "Hash Killer II"
layout: "post"
diff: 普及+/提高
pid: P12198
tag: ['Special Judge', '哈希 hashing', '概率论']
---
# Hash Killer II
## 题目描述

这天天气不错，hzhwcmhf 神犇给 VFleaKing 出了一道题：

给你一个长度为 $n$ 的字符串 $s$，求有多少个不同的长度为 $l$ 的连续子串。

两个字符串被认为是不同的当且仅当某个位置上的字符不同。

VFleaKing 一看觉得这不是 Hash 的裸题么！于是果断写了哈希 + 排序。

而 hzhwcmhf 神犇心里自然知道，这题就是后缀数组的 height 中 $< l$ 的个数 +1，就是后缀自动机上代表的长度区间包含 $l$ 的结点个数，就是后缀树深度为 $l$ 的结点的数量。

但是 hzhwcmhf 神犇看了看 VFleaKing 的做法表示非常汗。于是想卡掉他。

VFleaKing 使用的是字典序哈希，其代码大致如下：

```cpp
u64 val = 0;
for (int i = 0; i < l; i++)
    val = (val * base + s[i] - 'a') % MOD;
```

u64 是无符号 int64，范围是 $[0, 2^{64})$。VFleaKing 让 val 自然溢出。

base 是一个常量，VFleaKing 会根据心情决定其值。

$\text{MOD}=10^9+7$

VFleaKing 还求出来了 $base^l \bmod \text{MOD}$，即 base 的 $l$ 次方除以 $\text{MOD}$ 的余数，这样就能方便地求出所有长度为 $l$ 的子串的哈希值。

然后 VFleaKing 给哈希值排序，去重，求出有多少个不同的哈希值，把这个数作为结果。

其算法的 C++ 代码如下:

```cpp
typedef unsigned long long u64;
const int MaxN = 100000;
inline int hash_handle(const char *s, const int &n, const int &l, const int &base)
{
    const int Mod = 1000000007;
    u64 hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l = (hash_pow_l * base) % Mod;
    int li_n = 0;
    static int li[MaxN];
    u64 val = 0;
    for (int i = 0; i < l; i++)
        val = (val * base + s[i] - 'a') % Mod;
    li[li_n++] = val;
    for (int i = l; i < n; i++)
    {
        val = (val * base + s[i] - 'a') % Mod;
        val = (val + Mod - ((s[i - l] - 'a') * hash_pow_l) % Mod) % Mod;
        li[li_n++] = val;
    }
    sort(li, li + li_n);
    li_n = unique(li, li + li_n) - li;
    return li_n;
}

```

hzhwcmhf 当然知道怎么卡啦！但是他想考考你。
## 输出格式

你需要输出一组数据使得 VFleaKing 的代码 WA 掉。我们会使用 Special Judge 检查你的结果的正确性。

输出文件共两行。

第一行两个用空格隔开的数 $n, l$。

第二行是一个长度为 $n$ 的字符串。只能包含小写字母。

需要保证 $1 \le n \le 10^5, 1 \le l \le n$，不符合以上格式会 WA。不要有多余字符，很可能导致你 WA。
## 提示

本题的评分为：在 SPJ 中预设了 10 个 base 用作测试，每让一个 base 出现哈希冲突记 10 分，满分为 100 分。


---

---
title: "[GCPC 2024] Copycat Catcher"
layout: "post"
diff: 普及+/提高
pid: P13718
tag: ['2024', 'ICPC', '哈希表']
---
# [GCPC 2024] Copycat Catcher
## 题目描述

Your university recently established the Graduate Code Plagiarism Control (GCPC) initiative to get hold of the ever-increasing load on the graders for the computer science assignments.
Currently, the graders need to check the code of assignments manually for plagiarism.
The GCPC aims to simplify this part of the graders' jobs by performing the plagiarism checks automatically.

![](https://cdn.luogu.com.cn/upload/image_hosting/dmrh1qay.png)

:::align{center}
A Plagiarism Keyboard
:::

Code consists of tokens separated by spaces. Tokens are strings of alphabetical letters, numerals, and brackets. If a token consists of only a single alphabetical letter (upper or lowercase), it is a variable in the code.

The GCPC wants the plagiarism checker to compare query pieces of code to a reference code.
Specifically, it should check whether each query could have been obtained by selecting a contiguous
string of tokens from the reference and consistently renaming variables.

Variables are consistently renamed if no two occurrences of the same variable are renamed to different variables,
and if no two different variables are renamed to the same variable.

The GCPC has asked you to develop the plagiarism checker.
## 输入格式

The input consists of:
- A description of the reference, consisting of:
  - One line containing an integer $n$ ($1\leq n \leq 2\,000$), the number of tokens in the reference.
  - One line containing $n$ tokens, each consisting only of the characters '$\texttt{a}$'-'$\texttt{z}$', '$\texttt{A}$'-'$\texttt{Z}$', '$\texttt{0}$'-'$\texttt{9}$', '$\texttt{(}$' and '$\texttt{)}$'.
- An integer $q$ ($1 \leq q \leq 2\,000$), the number of queries.
- $2\cdot q$ lines, each two lines in the same format as the reference.

It is guaranteed that each query as well as the reference consist of at most $2\,000$ characters (excluding spaces). Tokens are separated by single spaces.
## 输出格式

For each query, output "$\texttt{yes}$" if the query could have been obtained from the reference, and "$\texttt{no}$" otherwise.
## 样例

### 样例输入 #1
```
9
for i in range(10) do print i j end
4
3
print j i
2
do print
6
k in range(10) do print k
6
k in range(10) do print j
```
### 样例输出 #1
```
yes
yes
yes
no

```
### 样例输入 #2
```
5
i is i times j
7
5
i is i times j
5
a is a times b
5
j is j times c
5
a is i times j
5
j is i times j
5
0 is 0 times j
5
i is i times i

```
### 样例输出 #2
```
yes
yes
yes
no
no
no
no

```
### 样例输入 #3
```
5
A 1 ( ) b
4
2
b 2
2
b 1
3
1 ) (
5
a 1 ( ) F

```
### 样例输出 #3
```
no
yes
no
yes

```


---

---
title: "八数码难题"
layout: "post"
diff: 普及+/提高
pid: P1379
tag: ['搜索', '福建省历届夏令营', '枚举', '哈希 hashing', 'A*  算法']
---
# 八数码难题
## 题目描述

在 $3\times 3$ 的棋盘上，摆有八个棋子，每个棋子上标有 $1$ 至 $8$ 的某一数字。棋盘中留有一个空格，空格用 $0$ 来表示。空格周围的棋子可以移到空格中。要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为 $123804765$），找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。

## 输入格式

输入初始状态，一行九个数字，空格用 $0$ 表示。

## 输出格式

只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数。保证测试数据中无特殊无法到达目标状态数据。
## 样例

### 样例输入 #1
```
283104765

```
### 样例输出 #1
```
4

```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/7rhxbnup.png)

图中标有 $0$ 的是空格。绿色格子是空格所在位置，橙色格子是下一步可以移动到空格的位置。如图所示，用四步可以达到目标状态。

并且可以证明，不存在更优的策略。


---

---
title: "「CZOI-R6」Border"
layout: "post"
diff: 普及+/提高
pid: P13790
tag: ['倍增', '二分', 'O2优化', '哈希 hashing', 'KMP 算法']
---
# 「CZOI-R6」Border
## 题目描述

给定一个仅包含小写字母的字符串 $s$（下标从 $1$ 开始），你可以将 **不超过 $\boldsymbol{1}$ 个位置** 修改为任意小写字母，使得最大化其最长 border 长度。你只需输出这个最大化的长度即可。

字符串 $b$ 是字符串 $a$ 的 border，当且仅当 $\lvert b\rvert < \lvert a\rvert$，且 $b$ 既是 $a$ 的前缀又是 $a$ 的后缀。
## 输入格式

第一行输入 $1$ 个字符串，表示 $s$。
## 输出格式

第一行输出 $1$ 个整数，表示答案。
## 样例

### 样例输入 #1
```
abaa
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
qwqqaq
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
iakioi
```
### 样例输出 #3
```
1
```
### 样例输入 #4
```
ababaaab

```
### 样例输出 #4
```
6

```
### 样例输入 #5
```
r
```
### 样例输出 #5
```
0

```
### 样例输入 #6
```
onion

```
### 样例输出 #6
```
2

```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask #1（$10\ \text{pts}$）：$|s|\le 20$。
- Subtask #2（$20\ \text{pts}$）：$s_i\in\{\texttt a,\texttt b\}$。
- Subtask #3（$30\ \text{pts}$）：$|s|\le 1000$。
- Subtask #4（$40\ \text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le |s|\le 10^6$，$s$ 仅包含小写字母。


---

---
title: "单词背诵"
layout: "post"
diff: 普及+/提高
pid: P1381
tag: ['模拟', '字符串', '二分', '福建省历届夏令营', '哈希 hashing', '双指针 two-pointer']
---
# 单词背诵
## 题目描述

灵梦有 $n$ 个单词想要背，但她想通过一篇文章中的一段来记住这些单词。

文章由 $m$ 个单词构成，她想在文章中找出连续的一段，其中包含最多的她想要背的单词（重复的只算一个）。并且在背诵的单词量尽量多的情况下，还要使选出的文章段落尽量短，这样她就可以用尽量短的时间学习尽可能多的单词了。
## 输入格式

第 $1$ 行一个数 $n$，接下来 $n$ 行每行是一个长度不超过 $10$ 的字符串，表示一个要背的单词。

接着是一个数 $m$，然后是 $m$ 行长度不超过 $10$ 的字符串，每个表示文章中的一个单词。
## 输出格式

输出文件共 $2$ 行。第 $1$ 行为文章中最多包含的要背的单词数，第 $2$ 行表示在文章中包含最多要背单词的最短的连续段的长度。
## 样例

### 样例输入 #1
```
3

hot

dog

milk

5

hot

dog

dog

milk

hot


```
### 样例输出 #1
```
3

3


```
## 提示

### 数据规模与约定

- 对于 $30\%$ 的数据，$n \le 50$，$m \le 500$；
- 对于 $60\%$ 的数据，$n \le 300$，$m \le 5000$；
- 对于 $100\%$ 的数据，$n \le 1000$，$m \le 10^5$。


---

---
title: "[NOI2015] 程序自动分析"
layout: "post"
diff: 普及+/提高
pid: P1955
tag: ['2015', '并查集', 'NOI', '离散化', '哈希 hashing']
---
# [NOI2015] 程序自动分析
## 题目描述

在实现程序自动分析的过程中，常常需要判定一些约束条件是否能被同时满足。

考虑一个约束满足问题的简化版本：假设 $x_1,x_2,x_3,\cdots$ 代表程序中出现的变量，给定 $n$ 个形如 $x_i=x_j$ 或 $x_i\neq x_j$ 的变量相等/不等的约束条件，请判定是否可以分别为每一个变量赋予恰当的值，使得上述所有约束条件同时被满足。例如，一个问题中的约束条件为：$x_1=x_2,x_2=x_3,x_3=x_4,x_4\neq x_1$，这些约束条件显然是不可能同时被满足的，因此这个问题应判定为不可被满足。

现在给出一些约束满足问题，请分别对它们进行判定。
## 输入格式

输入的第一行包含一个正整数 $t$，表示需要判定的问题个数。注意这些问题之间是相互独立的。

对于每个问题，包含若干行：

第一行包含一个正整数 $n$，表示该问题中需要被满足的约束条件个数。接下来 $n$ 行，每行包括三个整数 $i,j,e$，描述一个相等/不等的约束条件，相邻整数之间用单个空格隔开。若 $e=1$，则该约束条件为 $x_i=x_j$。若$e=0$，则该约束条件为 $x_i\neq x_j$。
## 输出格式

输出包括 $t$ 行。

输出文件的第 $k$ 行输出一个字符串 `YES` 或者 `NO`（字母全部大写），`YES` 表示输入中的第 $k$ 个问题判定为可以被满足，`NO` 表示不可被满足。
## 样例

### 样例输入 #1
```
2
2
1 2 1
1 2 0
2
1 2 1
2 1 1
```
### 样例输出 #1
```
NO
YES

```
### 样例输入 #2
```
2
3
1 2 1
2 3 1
3 1 1
4
1 2 1
2 3 1
3 4 1
1 4 0

```
### 样例输出 #2
```
YES
NO
```
## 提示

【样例解释1】

在第一个问题中，约束条件为：$x_1=x_2,x_1\neq x_2$。这两个约束条件互相矛盾，因此不可被同时满足。

在第二个问题中，约束条件为：$x_1=x_2,x_1 = x_2$。这两个约束条件是等价的，可以被同时满足。

【样例说明2】

在第一个问题中，约束条件有三个：$x_1=x_2,x_2= x_3,x_3=x_1$。只需赋值使得 $x_1=x_2=x_3$，即可同时满足所有的约束条件。

在第二个问题中，约束条件有四个：$x_1=x_2,x_2= x_3,x_3=x_4,x_4\neq x_1$。由前三个约束条件可以推出 $x_1=x_2=x_3=x_4$，然而最后一个约束条件却要求 $x_1\neq x_4$，因此不可被满足。

【数据范围】

所有测试数据的范围和特点如下表所示：

### 勘误：测试点 $8 \sim 10$ 的 $i, j$ 约束为 $1 \leq i, j \leq 10^9$，而不是下图中的 $10^{10}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/aq6f4ym8.png)


---

---
title: "[HNOI2005] 虚拟内存"
layout: "post"
diff: 普及+/提高
pid: P2318
tag: ['模拟', '2005', '各省省选', '离散化', '湖南', '哈希 hashing']
---
# [HNOI2005] 虚拟内存
## 题目描述

操作系统中一种重要的存储管理技术就是虚拟内存技术。操作系统中允许进程同时运行，也就是并行。每个进程都有其相对独立的数据块（进程运行的过程中将对其进行读写操作）。理想的情况下，这些数据块都应该存放在内存中，这样才能实现高效的读写操作。但事实上，内存的容量有限，每个进程只能把一部分数据放在内存中，为了解决这个矛盾，提出了虚拟内存技术。

虚拟内存技术的基本原理是：对进程而言，内存空间是无限大的，进程可以随意地读写数据，而对操作系统内部而言，利用外存来模拟扩充的内存空间，进程要求访问某个内存单元时，交由操作系统处理，操作系统首先在内存中查找该单元是否存在，如果存在，查找成功，否则转入外存查找（一定存在于外存中）。

就存储介质的物理性质而言，内存的访问速度相对于外存要快得多，因此对于每个进程来说操作系统应该把那些访问次数较多的数据存放在内存中，而把那些访问次数很少的数据放在外存中。如何选择内存中暂留的数据是一个很值得研究的问题，下面介绍一个内存管理中比较常用的算法：

内存中的数据以页为基本存储单位，进程的读写操作都针对页来进行。实际内存空间被分割成n页，虚拟内存空间的页数往往要多得多。某一时刻，进程需要访问虚存编号为P的页，该算法的执行步骤如下：

a.    首先在内存中查找，如果该页位于内存中，查找成功，转d，否则继续下面的操作；

b.    寻找内存中是否存在空页（即没有装载任何数据页的页面），若有，则从外存中读入要查找页，并将该页送至内存中的空页进行存储，然后转d，否则继续下面的操作；

c.    在内存中寻找一个访问次数最少的页面（如果存在多个页面的访问次数同时为最少，则选取最早读入数据进入内存的那个页面），从外存中读入要查找页，替换该页。

d.    结束

所谓访问次数是指从当前页面进入内存到该时刻被访问的次数，如果该页面以前进入过内存并被其它页面替换，那么前面的访问次数不应计入这个时刻的访问次数中。

你的任务是设计一个程序实现上述算法。

测试数据将会提供 $m$ 条读写内存的命令，每条命题提供要求访问的虚拟内存页的编号 $P$ 。你的程序要求能够模拟整个 $m$ 条命令的全部执行过程，所有的命令是按照输入的先后执行的，最开始的时候内存中的 $n$ 页全为空。


## 输入格式

输入共 $m + 1$ 行，第 $1$ 行为 $n (n \le 10000)$ 和 $m (m \le 1000000)$ ，分别表示内存页数和读写内存命令条数。接下来有 $m$ 行，其中第 $i+1$ 行有一个正整数 $P_i (P_i \le 10^9)$ ，表示第i条读写内存命令需要访问的虚拟内存页的编号。

## 输出格式

输出中仅包含一个正整数，表示在整个模拟过程中，在内存中直接查找成功的次数（即上面的算法只执行步骤 a 的次数）。

## 样例

### 样例输入 #1
```
3 8 

1

1

2

3

4

2

5

4


```
### 样例输出 #1
```
1
```


---

---
title: "[USACO06DEC] Milk Patterns G"
layout: "post"
diff: 普及+/提高
pid: P2852
tag: ['2006', '二分', 'USACO', '哈希 hashing', '后缀数组 SA']
---
# [USACO06DEC] Milk Patterns G
## 题目描述

Farmer John has noticed that the quality of milk given by his cows varies from day to day. On further investigation, he discovered that although he can't predict the quality of milk from one day to the next, there are some regular patterns in the daily milk quality.

To perform a rigorous study, he has invented a complex classification scheme by which each milk sample is recorded as an integer between 0 and 1,000,000 inclusive, and has recorded data from a single cow over N (1 ≤ N ≤ 20,000) days. He wishes to find the longest pattern of samples which repeats identically at least K (2 ≤ K ≤ N) times. This may include overlapping patterns -- 1 2 3 2 3 2 3 1 repeats 2 3 2 3 twice, for example.

Help Farmer John by finding the longest repeating subsequence in the sequence of samples. It is guaranteed that at least one subsequence is repeated at least K times.

## 输入格式

Line 1: Two space-separated integers: N and K


Lines 2..N+1: N integers, one per line, the quality of the milk on day i appears on the ith line.

## 输出格式

Line 1: One integer, the length of the longest pattern which occurs at least K times

## 样例

### 样例输入 #1
```
8 2
1
2
3
2
3
2
3
1
```
### 样例输出 #1
```
4
```
## 题目翻译

农夫 John 发现他的奶牛产奶的质量一直在变动。经过细致的调查，他发现：虽然他不能预见明天产奶的质量，但连续的若干天的质量有很多重叠。我们称之为一个“模式”。 John 的牛奶按质量可以被赋予一个 $0$ 到 $1000000$ 之间的数。并且 John 记录了 $N$（$1 \le N \le 2 \times 10 ^ 4$）天的牛奶质量值。他想知道最长的出现了至少 $K$（$2 \le K \le N$）次的模式的长度。比如 `1 2 3 2 3 2 3 1` 中 `2 3 2 3` 出现了两次。当 $K = 2$ 时，这个长度为 $4$。


---

---
title: "[USACO07JAN] Tallest Cow S"
layout: "post"
diff: 普及+/提高
pid: P2879
tag: ['模拟', '2007', 'USACO', '哈希 hashing', '前缀和']
---
# [USACO07JAN] Tallest Cow S
## 题目描述

FJ's N (1 ≤ N ≤ 10,000) cows conveniently indexed 1..N are standing in a line. Each cow has a positive integer height (which is a bit of secret). You are told only the height H (1 ≤ H ≤ 1,000,000) of the tallest cow along with the index I of that cow.

FJ has made a list of R (0 ≤ R ≤ 10,000) lines of the form "cow 17 sees cow 34". This means that cow 34 is at least as tall as cow 17, and that every cow between 17 and 34 has a height that is strictly smaller than that of cow 17.

For each cow from 1..N, determine its maximum possible height, such that all of the information given is still correct. It is guaranteed that it is possible to satisfy all the constraints.


## 输入格式

Line 1: Four space-separated integers: N, I, H and R


Lines 2..R+1: Two distinct space-separated integers A and B (1 ≤ A, B ≤ N), indicating that cow A can see cow B.

## 输出格式

Lines 1..N: Line i contains the maximum possible height of cow i.

## 样例

### 样例输入 #1
```
9 3 5 5
1 3
5 3
4 3
3 7
9 8
```
### 样例输出 #1
```
5
4
5
3
4
4
5
5
5
```
## 题目翻译

**【题目描述】**

FarmerJohn 有n头牛，它们按顺序排成一列。FarmerJohn 只知道其中最高的奶牛的序号及它的高度，其他奶牛的高度都是未知的。现在 FarmerJohn 手上有 $R$ 条信息，每条信息上有两头奶牛的序号（$a$ 和 $b$），其中 $b$ 奶牛的高度一定大于等于 $a$ 奶牛的高度，且 $a, b$之间的所有奶牛的高度都比 $a$ 小。现在 FarmerJohn 想让你根据这些信息求出每一头奶牛的可能的最大的高度。（数据保证有解）

**【输入格式】**

第一行：四个以空格分隔的整数：$n, i, h, R$（$n$ 和 $R$ 意义见题面；$i$ 和 $h$ 表示第 $i$ 头牛的高度为 $h$，他是最高的奶牛）

接下来 $R$ 行：两个不同的整数 $a$ 和 $b$（$1 \le a, b \le n$）

**【输出格式】**

一共 $n$ 行，表示每头奶牛的最大可能高度.

**【数据范围】**

$1 \le n \le 10000$，$1 \le h \le 1000000$，$0 \le R \le 10000$

Translate provided by @酥皮


---

---
title: "[USACO16JAN] Lights Out G"
layout: "post"
diff: 普及+/提高
pid: P3134
tag: ['2016', 'USACO', '哈希 hashing']
---
# [USACO16JAN] Lights Out G
## 题目描述

Farmer John has installed a fancy new milking machine in his barn, but it draws so much power that it occasionally causes the power to go out! This happens so often that Bessie has memorized a map of the barn, making it easier for her to find the exit of the barn in the dark. She is curious though about the impact of power loss on her ability to exit the barn quickly. For example, she wonders how much farther she might need to walk find the exit in the dark.


The barn is described by a simple (non self-intersecting) polygon with integer  vertices $(x_1, y_1) \ldots (x_n, y_n)$ listed in clockwise order.  Its edges alternate between horizontal (parallel to the x-axis) and vertical (parallel to the y-axis); the first edge can be of either type. The exit is located at

$(x_1, y_1)$.  Bessie starts inside the barn located at some vertex  $(x_i, y_i)$ for $i > 1$.  She can walk only around the perimeter of the barn, either clockwise or counterclockwise, Her goal is to travel a minimum distance to reach the exit. This is relatively easy to do with the lights on, of course, since she will travel either  clockwise or counterclockwise from her current location to the  exit -- whichever direction is shorter.


One day, the lights go out, causing Bessie to panic and forget which vertex she is standing at.  Fortunately, she still remembers the exact map of the barn, so she can possibly figure out her position by walking around and using her sense of touch.  Whenever she is standing at a vertex (including at her initial vertex), she can feel the exact interior angle at that vertex, and she can tell if that vertex is the exit.  When she walks along an edge of the barn, she can determine the exact length of the edge after walking along the entire edge.  Bessie decides on the following strategy: she will move clockwise around the perimeter of the barn until she has felt enough angles and edges to deduce the vertex at which she is currently located.  At that point, she can easily figure out how to get to the exit by traveling a minimum amount of remaining distance, either by continuing to move clockwise or by switching direction and moving counter-clockwise.


Please help Bessie determine the largest amount by which her travel distance will increase in the worst case (over all possibilities for her starting vertex) for travel in the dark versus in a lit barn.

## 输入格式

The first line of the input contains $N$ ($4 \leq N \leq 200$).  Each of the next $N$ lines contains two integers, describing the points $(x_i, y_i)$ in clockwise order around the barn.  These integers are in the range $-100,000 \ldots 100,000$.

## 输出格式

Output the largest amount that Bessie's travel distance will increase in the

worst case starting position using the strategy in the problem statement.

## 样例

### 样例输入 #1
```
4
0 0
0 10
1 10
1 0
```
### 样例输出 #1
```
2
```
## 提示

In this example, Bessie can feel that she is initially standing at a 90-degree angle, but she cannot tell if she is initially standing at vertex 2, 3, or 4.

After taking a step along one edge in the clockwise direction, Bessie either reaches the exit or can uniquely determine her location based on the length of this edge. The distances she obtains are:

If starting at vertex 2: she travels 12 units in the dark (1 unit to reach vertex 3, then 11 units to continue to the exit). She only needs to travel 10 units in a lit barn. This is an extra distance of 2 for this vertex.

If starting at vertex 3: she travels 11 units in both cases.

If starting at vertex 4: she travels 1 unit in both cases.

The worst-case difference over all starting points is therefore 12 - 10 = 2.  That is, Bessie can guarantee that using her strategy, no matter where she starts, she will travel at most 2 extra units of distance farther in the dark than in the light.

## 题目翻译

### 题目描述

Farmer John 在他的谷仓里安装了一个非常不错的新挤奶机，但是这台挤奶机耗电太多了，有时候会让谷仓直接停电！这种事发生的太频繁了，以至于 Bessie 直接把谷仓的地图背过了，以便于可以在黑暗中找到谷仓的出口。她对于停电对于她快速离开谷仓的能力的影响非常好奇。比如说，她想知道她在黑暗中需要走多远来找到谷仓的出口。

谷仓里的路可以被描述为是一个简单的用几个顶点来表示的多边形，这些顶点可以按照顺时针被表示为 $(x_1, y_1) \cdots (x_n, y_n)$（保证这些顶点连成的线没有交叉的情况）。这些点构成的边在水平轴（平行于 $x$ 轴）和竖直轴（平行于 $y$ 轴）之间交替出现。第一条边可以是任意一种类型。谷仓出口在坐标 $(x_1, y_1)$ 。Bessie 从谷仓内任意一个点 $(x_i, y_i)$ 开始走。她只可以沿着这些边走，要不然是顺时针，要不然就是逆时针，她的目标就是以最短距离抵达出口。当然，如果灯亮着的话这个事还算相对简单，因为她要不然顺时针要不然逆时针走，无所谓哪个方向的路程更短一点。

一天，谷仓突然停电了，导致 Bessie 受到惊吓、忘记了她站在哪个顶点。幸亏她还记得谷仓的准确地图，所以她可以四处走走，用她的触觉来弄清楚她的位置。不管什么时候，只要她站在一个顶点，那么她就可以感受到她在这个点的朝向角度，弄清楚这个点是不是出口。当她沿着谷仓的一个边走完的时候，她可以算出精确的边长。Bessie 决定用这么一个策略：她会顺时针沿着谷仓周围的边走，直到她知道了足够的角度和边、可以推断出她目前在的是哪个顶点。在那个顶点，她就可以轻易地弄清楚怎样以最短距离到达出口（要不然继续沿着顺时针走，要不然倒回去沿着逆时针走）。

请帮助 Bessie 算出在起点可以是任何一个顶点情况下，在最坏的情况下，她在黑暗中和亮着灯的时候到达出口的距离的差值（即找到差值的最大值）。

### 输入格式

第一行包括一个数字 $N (4 \leqslant N \leqslant 200)$ ，接下来 $N$ 行，每行包括两个数字，沿着顺时针表示顶点 $(x_i, y_i)$，$x_i, y_i \in [-10^5, 10^5]$ 。

### 输出格式

输出 Bessie 在最坏的情况下，她在黑暗中和亮着灯的时候到达出口的距离的差值（即找到差值的最大值）。

### 说明/提示

在这个样例中，Bessie 开始可以感觉到她沿着 $90 \degree$ 角站着，但是她辨别不出来她是在 $2, 3, 4$ 中的哪一个顶点。

在走了一条边以后，Bessie 要不然到了出口要不然就可以根据她走过的距离推断出她的位置。情况如下：

如果她从 $2$ 号点开始走，她需要在黑暗中走 $12$ 个单位，包括一个单位到达第三个点、十一个单位离开谷仓。同时，如果亮着灯，她可以只走 $10$ 个单位就离开谷仓。差值是 $2$ 。

如果从 $3$ 号点开始，她两种情况都要走 $11$ 个单位。

如果从 $4$ 号点开始，她两种情况都要走 $1$ 个单位。

所以最坏情况差值是 $2$ 。


---

---
title: "[COCI 2017/2018 #1] Lozinke"
layout: "post"
diff: 普及+/提高
pid: P4421
tag: ['字符串', '2017', '哈希 hashing', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #1] Lozinke
## 题目描述

Recently, there has been a breach of user information from the mega-popular social network Secret Network. Among the confidential information are the passwords of all users.

Mihael, a young student who has been exploring computer security lately, found the whole thing really interesting. While experimenting with the social network, he found another security breach! When you input any string of characters that contains a substring equal to the actual password, the login will be successful. For example, if the user whose password is abc inputs one of the strings abc, abcd or imaabcnema, the system will successfully log him in, whereas the login will fail for axbc.

Mihael wants to know how many ordered pairs of different users exist such that the first user, using their own password, can login as the second user.
## 输入格式

The first line of input contains the positive integer N (1 ≤ N ≤ 20 000), the number of users.

Each of the following N lines contains the user passwords. The passwords consist of at least one and at most 10 lowercase letters of the English alphabet.
## 输出格式

The first and only line of output must contains the number of ordered pairs from the task.
## 样例

### 样例输入 #1
```
3
aaa
aa
abb

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
x
x
xy

```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
5
mir
mirta
ta
ir
t

```
### 样例输出 #3
```
6
```
## 提示

Clarification​ ​of​ ​the​ ​second​ ​test​ ​case:

The first user can login as the second user, the second user can login as the first, and the third user can login as both the first and the second user.
## 题目翻译

【题目描述】

最近，某社交网络平台出现了用户信息的泄露。

Mihal 是一个喜欢探索计算机安全的学生，他发现整个事情非常有趣。在经过一段时间的研究，他发现了一个安全漏洞。当你输入任何字符串时，如果用户的密码在这个字符串中出现， 那么你就可以通过这个字符串成功登录。 例如，如果密码为 abc 的用户输入了一个字符串为 abc 或 abcdde 或 imaabcnema，他将会成功登录，而 axbc 则会登录失败。

现在 Mihal 想知道会出现多少次用户可以用自己的密码成功登录其他用户的情况。

【输入】

输入第一行为正整数 N，表示用户数量。（N<=20000）

接下来 N 行包含 N 个用户的密码，每个密码小写字母组成，长度不超过 10。

【输出】

输出共一行，输出出现用户可以用自己的密码成功登录其他用户的总次数。

【样例3解释】

第一个用户可以成功登录第二个用户，第二个用户可以成功登录第一个用户，第三个用户可以登录第一个用户和第二个用户，总共出现 4 次本用户成功登录其他用户的情况。



---

---
title: "[NOIP 2018 普及组] 对称二叉树"
layout: "post"
diff: 普及+/提高
pid: P5018
tag: ['树形数据结构', '2018', 'NOIP 普及组', '哈希 hashing']
---
# [NOIP 2018 普及组] 对称二叉树
## 题目背景

NOIP2018 普及组 T4
## 题目描述

一棵有点权的有根树如果满足以下条件，则被轩轩称为对称二叉树： 

1.  二叉树； 
2.  将这棵树所有节点的左右子树交换，新树和原树对应位置的结构相同且点权相等。   

下图中节点内的数字为权值，节点外的 $id$ 表示节点编号。  

![](https://cdn.luogu.com.cn/upload/image_hosting/nkln7z1l.png)

现在给出一棵二叉树，希望你找出它的一棵子树，该子树为对称二叉树，且节点数最多。请输出这棵子树的节点数。   

注意：只有树根的树也是对称二叉树。本题中约定，以节点 $T$ 为子树根的一棵“子 树”指的是：节点$T$ 和它的全部后代节点构成的二叉树。 
## 输入格式

第一行一个正整数 $n$，表示给定的树的节点的数目，规定节点编号 $1 \sim n$，其中节点 $1$ 是树根。 

第二行 $n$ 个正整数，用一个空格分隔，第 $i$ 个正整数 $v_i$ 代表节点 $i$ 的权值。 

接下来 $n$ 行，每行两个正整数 $l_i, r_i$，分别表示节点 $i$ 的左右孩子的编号。如果不存在左 / 右孩子，则以 $-1$ 表示。两个数之间用一个空格隔开。 
## 输出格式

输出文件共一行，包含一个整数，表示给定的树的最大对称二叉子树的节点数。 
## 样例

### 样例输入 #1
```
2 
1 3 
2 -1 
-1 -1 

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10 
2 2 5 5 5 5 4 4 2 3 
9 10 
-1 -1 
-1 -1 
-1 -1 
-1 -1 
-1 2 
3 4 
5 6 
-1 -1 
7 8
```
### 样例输出 #2
```
3
```
## 提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/4lfen5aa.png)    
最大的对称二叉子树为以节点 $2$ 为树根的子树，节点数为 $1$。   

**样例 2 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/vhzzc587.png)

最大的对称二叉子树为以节点 $7$ 为树根的子树，节点数为 $3$。 

**数据规模与约定**

共 $25$ 个测试点。    

$v_i ≤ 1000$。 

- 测试点 $1 \sim 3, n ≤ 10$，保证根结点的左子树的所有节点都没有右孩子，根结点的右 子树的所有节点都没有左孩子。 
- 测试点 $4 \sim 8, n ≤ 10$。
- 测试点 $9 \sim 12, n ≤ 10^5$，保证输入是一棵“满二叉树” 。 
- 测试点 $13 \sim 16, n ≤ 10^5$，保证输入是一棵“完全二叉树”。
- 测试点 $17 \sim 20, n ≤ 10^5$，保证输入的树的点权均为 $1$。
- 测试点 $21 \sim 25, n ≤ 10^6$。

本题约定： 

层次：节点的层次从根开始定义起，根为第一层，根的孩子为第二层。树中任一节 点的层次等于其父亲节点的层次加 $1$。 
 
 树的深度：树中节点的最大层次称为树的深度。 
 
 满二叉树：设二叉树的深度为 $h$，且二叉树有 $2^h-1$ 个节点，这就是满二叉树。  

![](https://cdn.luogu.com.cn/upload/image_hosting/8tof1fxx.png)

完全二叉树：设二叉树的深度为 $h$，除第 $h$ 层外，其它各层的结点数都达到最大 个数，第 $h$ 层所有的结点都连续集中在最左边，这就是完全二叉树。  

![](https://cdn.luogu.com.cn/upload/image_hosting/ibo7js1f.png)


---

---
title: "「Wdsr-1」小铃的书"
layout: "post"
diff: 普及+/提高
pid: P6306
tag: ['2020', '哈希 hashing', '进制']
---
# 「Wdsr-1」小铃的书
## 题目背景

本居小铃在人间之里经营着一家名为“铃奈庵”的书店。店里井井有条地堆放着很多很多书。  

一天，魔理沙来铃奈庵借书，搞得店里十分混乱，魔理沙随身携带的魔导书与铃奈庵的书籍全都混在了一起。
## 题目描述

小铃一共有 $n-1$ 本书，每本书有一个编号 $a_i$，两本书属于同一种类当且仅当两本书的编号相同。  

由于小铃平时将这些书整理得井井有条，因此在小铃的 $n-1$ 本书中，每个种类的书的数量都恰好是 $k$ 的倍数，其中 $k$ 是一给出的常数。
 
现在，魔理沙的一本编号未知的魔导书与小铃的 $n-1$ 本书混在了一起，而魔理沙只有知道魔导书的编号才能将其找回。  

由于书的数量实在太多，魔理沙找到了你来帮忙，希望聪明的你能帮她求出混入的魔导书的编号。

**注意：魔理沙的魔导书可能与小铃的某本书有着相同的编号。**
## 输入格式

第一行是两个整数 $n,k$，含义与题目描述一致。

保证 $n\equiv 1 \pmod k$ 。

第二行共 $n$ 个整数，表示混在一起的 $n$ 本书的编号 $a_i$ 。
## 输出格式

共一行一个整数，表示魔理沙的魔导书的编号。
## 样例

### 样例输入 #1
```
10 3
1 1 2 2 3 5 3 2 1 3
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
13 4
1 1 4 5 1 4 1 4 4 5 5 5 1
```
### 样例输出 #2
```
1
```
## 提示

#### 样例说明

样例 $1$ 中，小铃的书的编号为 $1,2,3$，分别有 $3$ 本。因此魔导书的编号为 $5$。

样例 $2$ 中，小铃的书的编号为 $1,4,5$，分别有 $4$ 本。因此魔导书的编号为 $1$。

------------------------

#### 数据范围及约定

**本题采取捆绑测试。**

$$
\def{\arraystretch}{1.5}
\def\cuteran{https://www.luogu.com.cn/paste/iyzwht7l}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{分值} \cr\hline
1 & 10^5 & 50 \cr\hline
2 & 10^6 & 25 \cr\hline
3 & 10^7 & 25 \cr\hline
\end{array}
$$

对于全部数据，保证 $1 \le n \le 10^7$  ，$2 \le k \le 10^3$  ，$1 \le a_i \le 10^{18}$。保证数据合法，即有且只有一本混入的魔导书。   

-----------------

#### 提示

**请注意时空限制。**

**使用 $\texttt{cin}$ / $\texttt{cout}$ 可能超时，这里给出一个快速读入模板：**

```cpp
long long qread(){
    long long w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
```

**或者使用这份模板：**

```cpp
typedef long long LL;
#define gc pa==pb&&(pb=(pa=buf)+fread(buf,1,100000,stdin),pa==pb)?EOF:*pa++
static char buf[100000],*pa(buf),*pb(buf);
inline LL readint() {
	LL x=0;char c=gc;
	while(c<'0'||c>'9')c=gc;
	for(;c>='0'&&c<='9';c=gc)x=x*10+(c&15);
	return x;
}
```

**其中，在开启 O2 开关的前提下，前者在极限数据下的读入要 $500\texttt{ms}$，而后者需要 $300\texttt{ms}$。也就是说，你的程序至少有 $500\sim 700\texttt{ms}$ 的时间执行主要算法。**


---

---
title: "[BalticOI 2014] Three Friends (Day1)"
layout: "post"
diff: 普及+/提高
pid: P6739
tag: ['2014', '哈希 hashing', 'BalticOI（波罗的海）']
---
# [BalticOI 2014] Three Friends (Day1)
## 题目描述

有一个字符串 $S$，对他进行操作：

1. 将 $S$ 复制为两份，存在字符串 $T$ 中
2. 在 $T$ 的某一位置上插入一个字符，得到字符串 $U$

现在给定 $U$，求 $S$。
## 输入格式

第一行一个整数 $N$ 代表 $U$ 的长度。   
第二行 $N$ 个字符代表字符串 $U$。
## 输出格式

- 如果不能通过上述的步骤从 $S$ 推到 $U$，输出 `NOT POSSIBLE`。
- 如果从 $U$ 得到的 $S$ 不是唯一的，输出 `NOT UNIQUE`。
- 否则，输出一个字符串 $S$。
## 样例

### 样例输入 #1
```
7
ABXCABC
```
### 样例输出 #1
```
ABC
```
### 样例输入 #2
```
6
ABCDEF
```
### 样例输出 #2
```
NOT POSSIBLE
```
### 样例输入 #3
```
9
ABABABABA
```
### 样例输出 #3
```
NOT UNIQUE
```
## 提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（35 pts）：$N \le 2001$。
- Subtask 2（65 pts）：无特殊限制。

对于 $100\%$ 的数据，$2 \le N \le 2 \times 10^6+1$，保证 $U$ 中只包含大写字母。

#### 说明

翻译自 [BalticOI 2014 Day1 B Three Friends](https://boi.cses.fi/files/boi2014_day1.pdf)。


---

---
title: "[NOI Online 2021 提高组] 积木小赛"
layout: "post"
diff: 普及+/提高
pid: P7469
tag: ['字符串', '2021', '哈希 hashing', 'NOI Online']
---
# [NOI Online 2021 提高组] 积木小赛
## 题目描述

Alice 和 Bob 最近热衷于玩一个游戏——积木小赛。

Alice 和 Bob 初始时各有 $n$ 块积木从左至右排成一排，每块积木都被标上了一个英文小写字母。

Alice 可以从自己的积木中丢掉任意多块（也可以不丢）；Bob 可以从自己的积木中丢掉最左边的一段连续的积木和最右边的一段连续的积木（也可以有一边不丢或者两边都不丢）。两人都不能丢掉自己所有的积木。然后 Alice 和 Bob 会分别将自己剩下的积木按原来的顺序重新排成一排。

Alice 和 Bob 都忙着去玩游戏了，于是想请你帮他们算一下，有多少种不同的情况下他们最后剩下的两排积木是相同的。

两排积木相同，当且仅当这两排积木块数相同且每一个位置上的字母都对应相同。

两种情况不同，当且仅当 Alice（或者 Bob）剩下的积木在两种情况中不同。
## 输入格式

第一行一个正整数 $n$，表示积木的块数。

第二行一个长度为 $n$ 的小写字母串 $s$，表示 Alice 初始的那一排积木，其中第 $i$ 个字母 $s_i$ 表示第 $i$ 块积木上的字母。

第三行一个长度为 $n$ 的小写字母串 $t$，表示 Bob 初始的那一排积木，其中第 $i$ 个字母 $t_i$ 表示第 $i$ 块积木上的字母。
## 输出格式

一行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
5
bcabc
bbcca
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef
```
### 样例输出 #2
```
34
```
## 提示

对于所有测试点：$1\le n \le 3000$，$s$ 与 $t$ 中只包含英文小写字母。

测试点 $1$ 满足：$n\le3000$，$s$ 与 $t$ 中只包含同一种字母。

测试点 $2,3,4$ 满足：$n\le100$。

测试点 $5,6,7$ 满足：$n\le500$。

测试点 $8,9,10$ 满足：$n\le3000$。

感谢 [w33z8kqrqk8zzzx33](https://www.luogu.com.cn/user/220037) 提供测试数据。


---

---
title: "[CERC2019] ABB"
layout: "post"
diff: 普及+/提高
pid: P9606
tag: ['字符串', '2019', '哈希 hashing', 'KMP 算法', 'Manacher 算法', 'ICPC']
---
# [CERC2019] ABB
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[ABB](https://contest.felk.cvut.cz/19cerc/solved/abb.pdf)」**
## 题目描述

Fernando 受雇于滑铁卢大学，负责完成该大学不久前开始的一个开发项目。在校园外，该大学希望为重要的外国游客和合作者建造具有代表性的平房街。

目前，这条街只建了一部分，它从湖岸开始，一直延伸到森林尽头。Fernando 的任务是通过在森林尽头建造更多的平房来完成这条街。所有现有的平房都坐落在街道的一侧，新的平房应该建在同一侧。这些平房有各种各样的类型，漆成各种各样的颜色。

在 Fernando 看来，整条街的布局有点混乱。他担心增加新平房后，它会看起来更加混乱。所以他想通过为新平房选择合适的颜色来增加一些排列顺序。当项目完成时，平房的整个颜色序列将是对称的，也就是说，从街道的两端观察时，颜色序列是相同的。

在其他问题中，Fernando 想知道，在满足平房颜色限制的情况下，他最少需要用来建造和适当染色才能完成项目的新平房数量。

### 简要题意

求使给定小写字母字符串成为回文串需在字符串末尾加入字母的最少数量。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 4\times 10^5)$，代表街道上现有平房的数量。

第二行包含一个由 $N$ 个小写字母（从 `a` 到 `z`）组成的字符串，代表从湖岸开始的街道现有的平房颜色顺序，其中不同的字母表示不同的颜色。
## 输出格式

输出一个整数，代表满足 Fernando 要求的新平房的最少数量。
## 样例

### 样例输入 #1
```
3
abb

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
12
recakjenecep

```
### 样例输出 #2
```
11

```
### 样例输入 #3
```
15
murderforajarof

```
### 样例输出 #3
```
6

```


---

---
title: "[USACO23DEC] Minimum Longest Trip G"
layout: "post"
diff: 普及+/提高
pid: P9981
tag: ['动态规划 DP', '倍增', 'USACO', '2023', 'O2优化', '拓扑排序', '哈希 hashing']
---
# [USACO23DEC] Minimum Longest Trip G
## 题目描述

Bessie 正在奶牛大陆上旅行。奶牛大陆由从 $1$ 到 $N$ 编号的 $N$（$2 \le N \le 2\cdot 10^5$）座城市和 $M$（$1 \le M \le 4\cdot 10^5$）条单向道路组成。第 $i$ 条路从城市 $a_i$ 通向城市 $b_i$，标签为 $l_i$。

由城市 $x_0$ 开始的长度为 $k$ 的旅程被定义为一个城市序列 $x_0,x_1,\ldots,x_k$，对于所有的 $0 \le i < k$，存在由城市 $x_i$ 到 $x_{i+1}$ 的路。保证在奶牛大路上不存在长度无限的旅程，不存在两条路连接一对相同的城市。

对于每座城市，Bessie 想知道从它开始的最长旅程。对于一些城市，从它们开始的最长旅程不唯一，Bessie 将选择其中道路标签序列字典序更小的旅程。一个序列比等长的另一个序列字典序更小，当且仅当在它们不同的第一个位置，前者比后者的元素更小。

输出 Bessie 在每座城市选择的旅途的长度和道路标签之和。
## 输入格式

第一行包含 $N$ 和 $M$。

接下来 $M$ 行，每行三个整数 $a_i,b_i,l_i$，代表一条由 $a_i$ 到 $b_i$，标签为 $l_i$ 的单向道路。
## 输出格式

输出 $N$ 行，第 $i$ 行包含由空格分隔的两个整数，表示 Bessie 选择的从城市 $i$ 开始的旅程的长度和道路标签之和。
## 样例

### 样例输入 #1
```
4 5
4 3 10
4 2 10
3 1 10
2 1 10
4 1 10
```
### 样例输出 #1
```
0 0
1 10
1 10
2 20
```
### 样例输入 #2
```
4 5
4 3 4
4 2 2
3 1 5
2 1 10
4 1 1
```
### 样例输出 #2
```
0 0
1 10
1 5
2 12
```
### 样例输入 #3
```
4 5
4 3 2
4 2 2
3 1 5
2 1 10
4 1 1
```
### 样例输出 #3
```
0 0
1 10
1 5
2 7
```
### 样例输入 #4
```
4 5
4 3 2
4 2 2
3 1 10
2 1 5
4 1 1
```
### 样例输出 #4
```
0 0
1 5
1 10
2 7
```
## 提示

### 样例解释 2

在下面的解释中，我们用 $a_i\xrightarrow{l_i} b_i$ 表示由城市 $a_i$ 通往 $b_i$，标签为 $l_i$ 的单向道路。

从城市 $4$ 出发有多条旅程，包含 $4\xrightarrow{4} 3\xrightarrow 5 1$，$4\xrightarrow 1 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$。在这些旅程中，$4\xrightarrow{4} 3\xrightarrow 5 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$ 是最长的。它们的长度均为 $2$，道路标签序列分别为 $[4,5]$ 和 $[2,10]$。$[2,10]$ 是字典序更小的那一个，它的和为 $12$。

### 测试点性质

- 测试点 $5-6$ 满足所有道路的标签相同。
- 测试点 $7-8$ 满足所有道路的标签不相同。
- 测试点 $9-10$ 满足 $N,M \le 5000$。
- 测试点 $11-20$ 没有额外限制。


---

