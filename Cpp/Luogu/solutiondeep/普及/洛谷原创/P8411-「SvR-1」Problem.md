# 题目信息

# 「SvR-1」Problem

## 题目背景

小 L 打颓被 nodgd 发现，于是他开始做题了。

## 题目描述

他的 DS 非常菜，于是他把一共 $n$ 道 DS 题加到了自己的计划题单里，其中第 $i$ 道题的有趣程度为 $a_i$。

由于他并不精通 DS，他发现他在做一些题目之前需要先做另一些题目。这样的关系共有 $n - 1$ 组，他还发现每道题都出现在了这些关系中且没有重复。

他发现 $\forall 2 \leq i \leq n$，第 $i$ 题和第 $fa_i$ 题间存在上文所述的关系，且 $1 \leq fa_i < i$。**他必须先做第 $fa_i$ 题后才能做第 $i$ 题**。

他发现，如果他在做一道题之前高兴程度为 $k$，则他做完第 $i$ 题后，他的高兴程度便会变为 $\min(k, a_i)$。**他做题前的高兴程度为无穷大**。

他想问你**在必须先做第 $1$ 题且不能重复做某一道题**的情况下，他在做题的全过程中每做完一道题后**高兴程度之和的最大值**。

## 说明/提示

#### 样例 #1 解释
在该组样例中 $a = [3398922311, 3077554952, 2933028207, 4018360144, 1263042788, 835814542]$，$fa_2 = fa_3 = fa_4 = 1$，$fa_5 = fa_6 = 2$。

最优方案之一：依次做第 $1, 4, 2, 3, 5, 6$ 题，最大值为 $3398922311 + 3398922311 + 3077554952 + 2933028207 + 1263042788 + 835814542 = 14907285111$。
#### 伪代码参考
$$
\def{\b}#1{ \textbf{ #1 } }\def{\t}#1{\text{ #1 }}\def{\s}{\quad}\def{\f}#1{\textsf{ #1 }}
\def{\l}{\underline{\kern{300pt}}\\[-10pt]} 
\def{\r}{\overline{\underline{\kern{300pt}}}}
\begin{aligned}
&\r\\&\b{Algorithm:}\t{Get }a_i,fa_i\\[-13pt]&\l\\
&\begin{aligned}
    \f{1.}&\b{function} \b{\color{red}unsigned int} \t{getnext}(\b{\color{red}unsigned int}\&seed): \\
    \f{2.}&\s seed=seed\oplus\t{left}(seed,13)\\
    \f{3.}&\s seed=seed\oplus\t{right}(seed,17)\\
    \f{4.}&\s seed=seed\oplus\t{left}(seed,5) \\
    \f{5.}&\s \b{return} seed\\
    \f{6.}&\b{function} \t{main}(n):\\
    \f{7.}&\s \b{for} i \b{from} 1 \b{to} n \b{step}1\\
    \f{8.}&\s\s a_i=\t{getnext}(seed)\\
    \f{9.}&\s \b{end for} \\
    \f{10.}&\s \b{for} i \b{from} 2 \b{to} n \b{step}1\\
    \f{11.}&\s\s fa_i=\t{getnext}(seed)\bmod(i-1)+1\\
    \f{12.}&\s \b{end for} \\
    \end{aligned}\\[-12pt]
&\r
\end{aligned}
$$

其中 $\text{left}(x,d)$ 和 $\text{right}(x,d)$ 分别表示将 $x$ 左移或右移 $d$ 位。
#### 数据规模与约定
**本题自动开启捆绑测试和 O2 优化。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c}\hline\hline
\textbf{Subtask} & \bm{n \leq} & \textbf{分值} \\\hline
\textsf{1} & 10 & 10 \\\hline
\textsf{2} & 10^4 & 20 \\\hline
\textsf{3} & 10^6 & 20 \\\hline
\textsf{4} & \text{无特殊限制} & 50 \\\hline\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 10^7$，$0 \leq seed < 2^{32}$。

## 样例 #1

### 输入

```
6 114514```

### 输出

```
14907285111```

# AI分析结果

• 综合分析与结论：
    - 本题围绕树形结构展开，核心是在满足题目依赖关系下求做完题后高兴程度之和的最大值。多数题解先从暴力或部分分思路入手，再优化至线性时间复杂度。
    - 思路方面，常见的有搜索、拓扑排序、贪心结合优先队列等，但因数据规模限制，需利用题目中 \(1 \leq fa_i < i\) 这一关键条件优化。优化后的核心思路是直接顺序遍历，利用递推式 \(f_i = \min(a_i, f_{fa_i})\) 计算每个节点贡献值并累加。
    - 算法要点在于理解题目条件构建树形关系，明确节点间依赖和贡献值计算方式。解决难点在于突破常规搜索或优先队列思路，借助特殊条件简化计算，避免高复杂度操作。

• 所选的题解：
  - 作者liangbowen (5星)
    - 关键亮点：思路清晰，从10分暴力深搜思路开始，逐步介绍50分拓扑排序结合优先队列做法，最后给出正解。正解利用题目条件直接顺序遍历，推导转移方程，时间复杂度 \(O(n)\)，代码简洁明了，对不同解法分析全面。
    - 个人心得：无
    - 重点代码 - 正解核心代码片段：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define N 10000005
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;
inline UI get_next(UI &seed)
{
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
UI a[N], fa[N];
int main()
{
    int n;
    UI seed;
    scanf("%d%u", &n, &seed);
    for (int i = 1; i <= n; i++) a[i] = get_next(seed);
    for (int i = 2; i <= n; i++) fa[i] = get_next(seed) % (i - 1) + 1;
    ULL sum = a[1];
    for (int i = 2; i <= n; i++) a[i] = min(a[i], a[ fa[i] ]), sum += a[i];
    printf("%llu", sum);
    return 0;
}
```
核心实现思想：先按题目要求生成数据，利用 \(1 \leq fa_i < i\) 条件，从第二个节点开始顺序遍历，每次更新当前节点值为其与父节点值的最小值，并累加到总和中。

  - 作者Hisaishi_Kanade (4星)
    - 关键亮点：直接点明题意理解后思路，先指出易想到的 \(n \log n\) 优先队列做法及局限性，再利用树的特殊性质得出节点贡献仅取决于父节点，进而给出线性时间复杂度代码，简洁高效。
    - 个人心得：提到用链式前向星做时TLE的调试经历。
    - 重点代码 - 核心代码片段：
```cpp
#include <stdio.h>
unsigned int seed;
inline void get_next(){
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return;
}
long long ans;
unsigned int a[10000005],fa[10000005];
int n,i;
#define min(a,b) a<b?a:b
int main(){
    scanf("%d %u",&n,&seed);
    for(i=1;i<=n;i++){
        get_next();
        a[i]=seed;
    }
    for(i=2;i<=n;++i){
        get_next();
        fa[i]=seed%(i - 1)+1;
    }
    ans=a[1];
    for(i=2;i<=n;++i)
        ans+=a[i]=min(a[i],a[fa[i]]);
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：生成数据后，根据节点贡献取决于父节点的性质，从第二个节点遍历更新节点值并累加。

  - 作者stntn (4星)
    - 关键亮点：先阐述优先队列和类似DP（实际为搜索）的思路及复杂度，指出因节点 \(i\) 的父亲 \(fa_i\) 满足 \(fa_i < i\)，可省略建树和搜索直接在 \(fa\) 数组上跑DP，对思路转变阐述清晰。
    - 个人心得：无
    - 重点代码 - 满分核心代码片段：
```cpp
#include<bits/stdc++.h>
#define N 10000010
#define LL long long 
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f3f3f3f
int n;LL ans;
unsigned int seed,a[N];
inline unsigned int min(unsigned int a,unsigned int b){return a>b? b:a;}
inline unsigned int get_next(unsigned int &seed)
{
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}
signed main()
{
    scanf("%d%d",&n,&seed);
    rep(i,1,n) a[i]=get_next(seed);ans=a[1];
    rep(i,2,n) a[i]=min(a[i],a[get_next(seed)%(i - 1)+1]),ans+=a[i];
    printf("%lld\n",ans);
    return 0;
}
```
核心实现思想：生成数据后，利用 \(fa_i < i\) 的条件，在遍历过程中直接更新节点值并累加计算答案。

• 最优的关键思路或技巧：
    - **思维方式**：抓住 \(1 \leq fa_i < i\) 这一特殊条件，突破常规树形结构处理思路，意识到顺序遍历即可满足题目依赖关系，从而简化问题。
    - **算法优化**：避免使用高复杂度的搜索、优先队列等方法，通过直接顺序遍历数组，利用递推关系 \(f_i = \min(a_i, f_{fa_i})\) 计算每个节点对答案的贡献，将时间复杂度从 \(O(n \log n)\) 或 \(O(n!)\) 优化到 \(O(n)\)。

• 可拓展之处：
同类型题常围绕树形结构展开，给定节点间依赖关系和节点权值，求满足一定条件下的最优值。类似算法套路为分析题目给定的节点关系特点，若存在类似本题的顺序依赖关系，可尝试直接顺序遍历结合递推关系求解，避免复杂的图或树的遍历结构。

• 推荐题目：
    - [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树形DP经典题目，节点间存在上下级关系，通过分析节点选择与不选择的情况进行状态转移，与本题分析节点贡献值思路类似。
    - [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：在二叉树上进行操作，根据题目条件对树进行遍历和状态转移，与本题处理树形结构问题思路有相似之处。
    - [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)：虽然重点在于求最近公共祖先，但涉及到对树结构的理解和遍历操作，有助于巩固树形结构相关知识，与本题基于树结构分析问题基础相同。

• 个人心得摘录与总结：
  - 作者Hisaishi_Kanade提到用链式前向星做时TLE，总结出在处理大规模数据时，复杂的数据结构或实现方式可能导致超时，需根据题目特点优化数据结构和算法。 

---
处理用时：51.22秒