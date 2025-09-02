# 题目信息

# [ICPC 2019 WF] Circular DNA

## 题目描述

You have an internship with a bioinformatics research group studying DNA. A single strand of DNA consists of many genes, which fall into different categories called gene types. Gene types are delimited by specific nucleotide sequences known as gene markers. Each gene type i has a unique start marker $\texttt s_i$ and a unique end marker $\texttt e_i$ . After many dirty jobs (growing bacteria, cell extraction, protein engineering,and so on), your research group can convert DNA into a form consisting of only the gene markers, removing all the genetic material lying between the markers.

Your research group came up with the interesting hypothesis that gene interpretation depends on whether the markers of some gene types form properly nested structures. To decide whether markers of gene type $i$ form a proper nesting in a given sequence of markers $w$, one needs to consider the subsequence of $w$ containing only the markers of gene type $i$ ($\texttt s_i$ and $\texttt e_i$), leaving none of them out. The following (and only the following) are considered to be properly nested structures:

- $\texttt s_i \texttt e_i$
- $\texttt s_i N \texttt e_i$, where $N$ is a properly nested structure
- $AB$, where $A$ and $B$ are properly nested structures

Given your computing background, you were assigned to investigate this property, but there is one further complication. Your group is studying a specific type of DNA called circular DNA, which is DNA that forms a closed loop. To study nesting in circular DNA, it is necessary to cut the loop at some location, which results in a unique sequence of markers (the direction of reading is fixed by molecular properties). Whether a gene type $i$ forms a proper nesting now also depends on where the circular DNA is cut. Your task is to find the cutting location that maximizes the number of gene types that form a properly nested structure. Figure D.1 shows an example corresponding to Sample Input 1. The indicated cut results in the markers for gene type 1 being properly nested.

![](https://cdn.luogu.com.cn/upload/image_hosting/l856fbko.png)

## 说明/提示

Source: ICPC 2019 World Finals.

## 样例 #1

### 输入

```
9
e1 e1 s1 e2 s1 s2 e42 e1 s1```

### 输出

```
3 1```

## 样例 #2

### 输入

```
8
s1 s1 e3 e1 s3 e1 e3 s3```

### 输出

```
8 2```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何解决环形DNA序列中基因类型匹配问题展开。核心思路多是将问题转化为括号匹配问题，通过不同方法优化求解。
1. **思路**：多数题解先考虑链状DNA匹配，再解决环形问题。有的通过断环为链并复制序列，枚举断点求解；有的利用递推思想，分析断点移动对匹配的影响。
2. **算法要点**：将基因标记视为括号，用权值（1或 - 1）表示，通过前缀和判断匹配情况。不同题解在维护数据结构和优化枚举断点计算上有差异。
3. **解决难点**：难点在于高效处理环形结构及断点移动对不同基因类型匹配状态的影响。部分题解用线段树、单调队列等数据结构优化，部分通过递推分析减少计算量。

### 所选的题解
1. **作者：比利♂海灵顿 (5星)**
    - **关键亮点**：思路清晰，从链状DNA匹配引入，逐步优化到环形DNA的 $O(n)$ 算法。通过递推分析断点移动对基因匹配的影响，避免重复计算，代码简洁且注释详细。
    - **个人心得**：提到考场先写高复杂度算法兜底，再优化的策略。
    - **核心代码片段**：
```cpp
for (register unsigned i(1); i <= n; ++i) {
    Sum[a[i].Number] += a[i].SE;              // 累计总和 
    Low[a[i].Number] = min(Low[a[i].Number], Sum[a[i].Number]); // 更新前缀和历史最小值 
}
for (register unsigned i(1); i <= Cnt; ++i) {// 真核生物  (枚举基因编号)
    if(Low[List[i]] == 0 && Sum[List[i]] == 0) {// 同时满足两个条件 
        ++Tmp;
    }
}
Pos = 1, Ans = Tmp;                         // 对于真核生物的运行结果
for (register unsigned i(1); i < n; ++i) {  // 枚举断点, 这里是从 i 后面切断, 所以原左端基因是 a[i] 
    if(!(Sum[a[i].Number] ^ 0)) {             // 优化常数, 等价于 if(Sum[a[i].Number] == 0) 
        if(a[i].SE ^ (-1)) {                    // 优化同上, 这是 sx 的情况 
            if(!(Low[a[i].Number] ^ 0)) {         // 原本完美, 修改后不完美了 
                --Tmp;
            }
            --Low[a[i].Number];                   // 最后修改 Low[x] 
        }
        else {                                  // 这是 ex 的情况 
            ++Low[a[i].Number];                   // 先修改 Low[x] 
            if(!(Low[a[i].Number] ^ 0)) {         // 原本不是完美匹配, 但是现在完美了 
                ++Tmp;
            }
        }
    }
    if(Tmp > Ans) {                           // 新断点严格优于原先才更新 
        Pos = i + 1;
        Ans = Tmp;
    }
}
```
    - **核心实现思想**：先计算每种基因的权值总和与前缀和最小值，判断链状DNA中完美匹配的基因类型数量。枚举环形DNA断点时，根据断点移动对特定基因前缀和最小值的影响，更新完美匹配基因类型数量，从而找到最优断点。
2. **作者：内拉组里 (4星)**
    - **关键亮点**：先给出暴力模拟思路及复杂度分析，再优化到 $O(n)$ 算法。通过对每种括号分别跑前缀和，利用断点移动时仅部分括号种类最小值变化的特点，实时维护最小值来更新合法括号种类数。
    - **核心代码片段**：
```cpp
for (int i = 1; i <= n; i++)
{
    sum[a[i].second] += a[i].first;
    mn[a[i].second] = min (mn[a[i].second], sum[a[i].second]);
}
int cnt = 0;
for (auto i : gene)
{
    if (!mn[i] &&!sum[i])
    {
        cnt++;
    }
}
int idx = 1;
int ans = cnt;
for (int i = 1; i < n; i++)
/* cut off i from the head and append */
    if (!sum[a[i].second])
    /* complete type sequence */
{
    if (a[i].first == 1)
    /* left bracket */
    {
        if (!mn[a[i].second]--)                   
        {
            cnt--;
        }
    }
    else
    /* right bracket */
    {
        if (!++mn[a[i].second])                   
        {
            cnt++;
        }
    }
    if (ans < cnt)
    {
        ans = cnt;
        idx = i + 1;
    }
}
```
    - **核心实现思想**：预处理每种基因的前缀和及最小值，统计初始合法基因种类数。枚举断点时，对权值总和为0的基因，根据断点处括号类型调整前缀和最小值，进而更新合法基因种类数，得到最优断点。
3. **作者：mrclr (4星)**
    - **关键亮点**：提出一种不同思路，单独考虑每个基因编号，通过维护前缀和及利用set实现动态判断序列合法性。在 $O(logn)$ 时间复杂度内实现删除队首、添加队尾、元素加减及查找最小值操作，统计每个断点对应的合法括号序列个数。
    - **核心代码片段**：
```cpp
In int init(int ID)
{
    s.clear();
    sum = 0, las = 1;
    for(int i = 0; i < (int)v[ID].size(); ++i) 
    {
        sum += t[v[ID][i]].flg;
        s.insert((Set){sum, v[ID][i], 0});
        if(sum < 0) las = 0;
    }
    if(sum) las = 0;
    return las;
}

int ans[maxn];
bool ha[maxn];                                                      
In void solve(int ID)
{
    int A = 0;
    for(int i = 0; i < (int)v[ID].size(); ++i)
    {
        int p = v[ID][i];
        A += t[p].flg, ha[p] = 1;
        s.insert((Set){A, p, 1});
        while(1)
        {
            sSet it = s.begin(); Set tp = *it;
            if(ha[tp.p] &&!tp.New) s.erase(it);
            else 
            {
                bool flg = (tp.val - A) >= 0;
                if(las ^ flg)
                {
                    ans[p] = las? -1 : 1;
                    las ^= 1;
                }
                break;
            }
        }
    }
}
```
    - **核心实现思想**：初始化时计算基因编号对应序列的前缀和并判断合法性。在处理每个断点时，通过更新前缀和及利用set维护最小值，判断序列合法性变化，记录每个断点的变化情况，最后统计最优断点。

### 最优关键思路或技巧
1. **递推思想**：如比利♂海灵顿的题解，分析断点移动对特定基因匹配状态的影响，仅更新受影响基因的相关数据，避免重复计算，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
2. **数据结构优化**：mrclr利用set维护前缀和最小值，在 $O(logn)$ 时间内实现动态判断序列合法性，有效处理每个基因编号在不同断点下的情况。

### 可拓展之处
此类题目属于环形数据结构与匹配问题结合的类型。相似算法套路有：处理环形问题时，常采用断环为链并复制序列或利用递推分析断点移动影响；对于匹配问题，转化为括号匹配模型，通过前缀和、栈等方式判断合法性。

### 推荐题目
1. **P1044 [NOIP2003 普及组] 栈**：通过模拟栈操作，加深对括号匹配及栈应用的理解。
2. **P2056 [ZJOI2007] 捉迷藏**：涉及动态维护数据结构（如线段树），与本题部分优化思路类似。
3. **P3373 【模板】线段树 2**：强化对线段树这一数据结构的掌握，可用于解决一些区间查询和修改问题，类似本题中对数据的动态维护。 

---
处理用时：71.15秒