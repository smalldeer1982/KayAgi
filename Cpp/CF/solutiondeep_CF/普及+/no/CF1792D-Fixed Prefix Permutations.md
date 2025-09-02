# 题目信息

# Fixed Prefix Permutations

## 题目描述

You are given $ n $ permutations $ a_1, a_2, \dots, a_n $ , each of length $ m $ . Recall that a permutation of length $ m $ is a sequence of $ m $ distinct integers from $ 1 $ to $ m $ .

Let the beauty of a permutation $ p_1, p_2, \dots, p_m $ be the largest $ k $ such that $ p_1 = 1, p_2 = 2, \dots, p_k = k $ . If $ p_1 \neq 1 $ , then the beauty is $ 0 $ .

The product of two permutations $ p \cdot q $ is a permutation $ r $ such that $ r_j = q_{p_j} $ .

For each $ i $ from $ 1 $ to $ n $ , print the largest beauty of a permutation $ a_i \cdot a_j $ over all $ j $ from $ 1 $ to $ n $ (possibly, $ i = j $ ).

## 样例 #1

### 输入

```
3
3 4
2 4 1 3
1 2 4 3
2 1 3 4
2 2
1 2
2 1
8 10
3 4 9 6 10 2 7 8 1 5
3 9 1 8 5 7 4 10 2 6
3 10 1 7 5 9 6 4 2 8
1 2 3 4 8 6 10 7 9 5
1 2 3 4 10 6 8 5 7 9
9 6 1 2 10 4 7 8 3 5
7 9 3 2 5 6 4 8 1 10
9 4 3 7 5 6 1 10 8 2```

### 输出

```
1 4 4 
2 2 
10 8 1 6 8 10 1 7```

# AI分析结果

### 题目内容重写

#### 固定前缀排列

**题目描述**

给定 $n$ 个排列 $a_1, a_2, \dots, a_n$，每个排列的长度为 $m$。回忆一下，长度为 $m$ 的排列是一个由 $1$ 到 $m$ 的 $m$ 个不同整数组成的序列。

定义一个排列 $p_1, p_2, \dots, p_m$ 的**美丽度**为最大的 $k$，使得 $p_1 = 1, p_2 = 2, \dots, p_k = k$。如果 $p_1 \neq 1$，则美丽度为 $0$。

两个排列 $p$ 和 $q$ 的乘积 $p \cdot q$ 是一个排列 $r$，满足 $r_j = q_{p_j}$。

对于每个 $i$ 从 $1$ 到 $n$，输出在所有 $j$ 从 $1$ 到 $n$（可能 $i = j$）中，排列 $a_i \cdot a_j$ 的最大美丽度。

**样例 #1**

### 输入

```
3
3 4
2 4 1 3
1 2 4 3
2 1 3 4
2 2
1 2
2 1
8 10
3 4 9 6 10 2 7 8 1 5
3 9 1 8 5 7 4 10 2 6
3 10 1 7 5 9 6 4 2 8
1 2 3 4 8 6 10 7 9 5
1 2 3 4 10 6 8 5 7 9
9 6 1 2 10 4 7 8 3 5
7 9 3 2 5 6 4 8 1 10
9 4 3 7 5 6 1 10 8 2
```

### 输出

```
1 4 4 
2 2 
10 8 1 6 8 10 1 7
```

### 算法分类
贪心、字符串

### 题解分析与结论

#### 题解对比与总结

1. **World_Creater (赞：8)**  
   - **思路**：通过计算排列的逆排列，将问题转化为在字典树中查找最长公共前缀的问题。使用字典树（Trie）来存储所有排列的逆排列，然后对每个排列进行贪心查找。
   - **难点**：如何将排列的乘积问题转化为前缀匹配问题，并利用字典树高效解决。
   - **评分**：5星  
   - **关键亮点**：利用逆排列将问题转化为前缀匹配，使用字典树进行高效查找。

2. **LKY928261 (赞：4)**  
   - **思路**：与World_Creater类似，通过逆排列将问题转化为前缀匹配问题，使用字典树进行查找。
   - **难点**：如何高效地存储和查找排列的逆排列。
   - **评分**：4星  
   - **关键亮点**：与World_Creater的思路一致，但代码实现略有不同。

3. **ningago (赞：3)**  
   - **思路**：使用bitset维护集合的交集，通过枚举每个排列的前缀，判断是否存在满足条件的排列。
   - **难点**：如何高效地维护集合的交集，并判断是否为空。
   - **评分**：3星  
   - **关键亮点**：使用bitset进行集合操作，虽然思路不同，但实现较为复杂。

#### 最优关键思路与技巧

- **逆排列转化**：将排列的乘积问题转化为前缀匹配问题，利用逆排列的性质简化问题。
- **字典树应用**：使用字典树存储所有排列的逆排列，通过贪心查找最长公共前缀，实现高效查询。

#### 可拓展之处

- **类似问题**：可以扩展到其他需要前缀匹配或排列组合的问题，如字符串匹配、序列比对等。
- **数据结构**：字典树在其他字符串匹配问题中也有广泛应用，如单词查找、前缀查询等。

#### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3808 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3808)
3. [P3796 【模板】AC自动机（加强版）](https://www.luogu.com.cn/problem/P3796)

#### 个人心得摘录

- **World_Creater**：通过逆排列将问题转化为前缀匹配问题，使用字典树进行高效查找，思路清晰，代码简洁。
- **LKY928261**：与World_Creater的思路一致，但代码实现略有不同，强调了逆排列的重要性。
- **ningago**：使用bitset进行集合操作，虽然思路不同，但实现较为复杂，适合对集合操作熟悉的选手。

### 核心代码片段

```cpp
struct trie{
    int tree[500005][13];
    int cnt;
    void reset()
    {
        for(int i=0;i<=cnt;i++) memset(tree[i],0,sizeof(tree[i]));
        cnt=0;
    }
    void insert(int a[])
    {
        int p=0;
        for(int i=1;i<=m;i++)
        {
            if(tree[p][a[i]]==0) tree[p][a[i]]=++cnt;
            p=tree[p][a[i]];
        }
    }
    int find(int a[])
    {
        int p=0,cnt=0;
        for(int i=1;i<=m;i++)
        {
            int x=a[i];
            if(tree[p][x]!=0)
            {
                cnt++;
                p=tree[p][x];
            }
            else return cnt;
        }
        return cnt;
    }
}T;
```

**核心实现思想**：通过字典树存储所有排列的逆排列，然后对每个排列进行贪心查找，找到最长公共前缀。

---
处理用时：48.20秒