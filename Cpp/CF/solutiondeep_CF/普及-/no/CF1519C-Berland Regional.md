# 题目信息

# Berland Regional

## 题目描述

Polycarp is an organizer of a Berland ICPC regional event. There are $ n $ universities in Berland numbered from $ 1 $ to $ n $ . Polycarp knows all competitive programmers in the region. There are $ n $ students: the $ i $ -th student is enrolled at a university $ u_i $ and has a programming skill $ s_i $ .

Polycarp has to decide on the rules now. In particular, the number of members in the team.

Polycarp knows that if he chooses the size of the team to be some integer $ k $ , each university will send their $ k $ strongest (with the highest programming skill $ s $ ) students in the first team, the next $ k $ strongest students in the second team and so on. If there are fewer than $ k $ students left, then the team can't be formed. Note that there might be universities that send zero teams.

The strength of the region is the total skill of the members of all present teams. If there are no teams present, then the strength is $ 0 $ .

Help Polycarp to find the strength of the region for each choice of $ k $ from $ 1 $ to $ n $ .

## 说明/提示

In the first testcase the teams from each university for each $ k $ are:

- $ k=1 $ : 
  - university $ 1 $ : $ [6], [5], [5], [3] $ ;
  - university $ 2 $ : $ [8], [1], [1] $ ;
- $ k=2 $ : 
  - university $ 1 $ : $ [6, 5], [5, 3] $ ;
  - university $ 2 $ : $ [8, 1] $ ;
- $ k=3 $ : 
  - university $ 1 $ : $ [6, 5, 5] $ ;
  - university $ 2 $ : $ [8, 1, 1] $ ;
- $ k=4 $ : 
  - university $ 1 $ : $ [6, 5, 5, 3] $ ;

## 样例 #1

### 输入

```
4
7
1 2 1 2 1 2 1
6 8 3 1 5 1 5
10
1 1 1 2 2 2 2 3 3 3
3435 3014 2241 2233 2893 2102 2286 2175 1961 2567
6
3 3 3 3 3 3
5 9 6 7 9 7
1
1
3083```

### 输出

```
29 28 26 19 0 0 0 
24907 20705 22805 9514 0 0 0 0 0 0 
43 43 43 32 38 43 
3083```

# AI分析结果

### 题目内容
#### Berland地区赛
1. **题目描述**：Polycarp是Berland地区ICPC赛事的组织者。Berland有$n$所大学，编号从$1$到$n$。Polycarp了解该地区所有的竞赛程序员。总共有$n$个学生，第$i$个学生就读于大学$u_i$，编程能力为$s_i$。Polycarp现在必须决定比赛规则，特别是队伍的人数。Polycarp知道，如果他选择队伍人数为整数$k$，每所大学将派出他们编程能力最强的$k$个学生组成第一队，接下来最强的$k$个学生组成第二队，依此类推。如果剩下的学生人数少于$k$，则无法组队。注意，可能有些大学派出的队伍数为零。该地区的实力是所有参赛队伍成员的编程能力总和。如果没有队伍参赛，那么实力为$0$。请帮助Polycarp找出$k$从$1$到$n$每个取值下该地区的实力。
2. **说明/提示**：在第一个测试用例中，每所大学对于每个$k$的队伍情况如下：
    - $k = 1$：
        - 大学$1$：$[6], [5], [5], [3]$；
        - 大学$2$：$[8], [1], [1]$；
    - $k = 2$：
        - 大学$1$：$[6, 5], [5, 3]$；
        - 大学$2$：$[8, 1]$；
    - $k = 3$：
        - 大学$1$：$[6, 5, 5]$；
        - 大学$2$：$[8, 1, 1]$；
    - $k = 4$：
        - 大学$1$：$[6, 5, 5, 3]$；
3. **样例 #1**：
    - **输入**：
```
4
7
1 2 1 2 1 2 1
6 8 3 1 5 1 5
10
1 1 1 2 2 2 2 3 3 3
3435 3014 2241 2233 2893 2102 2286 2175 1961 2567
6
3 3 3 3 3 3
5 9 6 7 9 7
1
1
3083
```
    - **输出**：
```
29 28 26 19 0 0 0 
24907 20705 22805 9514 0 0 0 0 0 0 
43 43 43 32 38 43 
3083
```

### 算法分类
前缀和

### 综合分析与结论
所有题解的核心思路都是利用前缀和优化来计算不同队伍人数$k$下地区的实力。各题解首先将学生按大学分组，对每组学生的编程能力从大到小排序，再计算前缀和。之后，通过遍历每个大学和每个可能的$k$值，利用前缀和快速计算每个大学对不同$k$的贡献并累加，从而得到不同$k$下地区的总实力。各题解的主要差异在于代码实现细节和优化程度。

### 所选的题解
1. **作者：Mophie (赞：8)  星级：5星**
    - **关键亮点**：思路清晰，先指出各大学相互独立，提出朴素思路并分析复杂度，进而优化到$O(n logn)$。代码简洁，利用vector存储数据，排序和前缀和处理清晰。
    - **个人心得**：提到自己Hack别人50发后写题解。
    - **重点代码核心实现思想**：对每个大学的学生能力排序并计算前缀和，然后遍历每个大学和$k$，计算每个大学对$k$的贡献累加到答案数组。
    - **核心代码片段**：
```cpp
for(int i=1;i<=n;i++)
    if(G[i].size()!=0)
    {
        sort(G[i].begin(),G[i].end(),cmp);
        for(int j=1;j<G[i].size();j++)G[i][j]+=G[i][j-1];
    }
for(int i=1;i<=n;i++)
    if(G[i].size()!=0)
    {
        int len=G[i].size();
        for(int k=1;k<=len;k++)
            ans[k]+=G[i][len/k*k-1];    
    }
```
2. **作者：oimaster (赞：5)  星级：5星**
    - **关键亮点**：详细阐述了从$O(n^3)$到$O(n^2)$再到$O(n logn)$的复杂度优化过程，易于理解。代码简洁明了，使用vector和自定义宏，逻辑清晰。
    - **重点代码核心实现思想**：与Mophie类似，对每个大学的学生能力排序并计算前缀和，根据每个大学学生人数和$k$计算贡献累加到结果数组。
    - **核心代码片段**：
```cpp
for(int i=1;i<=n;++i){
    sort(a[i].begin(),a[i].end(),greater<int>());
    for(int j=1;j<a[i].size();++j)
        a[i][j]+=a[i][j-1];
}
for(int i=1;i<=n;++i){
    int tots=a[i].size();
    for(int j=1;j<=tots;++j)
        res[j]+=a[i][zb(tots,j)-1];
}
```
3. **作者：CodingOIer (赞：0)  星级：4星**
    - **关键亮点**：详细分析了从暴力$O(n ^ 3)$到$O(n ^ 2)$再到优化后的思路，逻辑严谨。代码结构清晰，使用vector和标准库函数，可读性较好。
    - **重点代码核心实现思想**：对每个大学的学生能力排序并计算前缀和，遍历每个大学和$k$，通过前缀和计算每个大学对$k$的贡献并累加到答案数组。
    - **核心代码片段**：
```cpp
for (int i = 1; i <= n; i++)
{
    std::sort(v[i].begin(), v[i].end(), std::greater<>());
    sum.clear();
    sum.push_back(0);
    for (auto x : v[i])
    {
        sum.push_back(*sum.rbegin() + x);
    }
    for (int j = 1; j <= int(v[i].size()); j++)
    {
        answer[j] += sum[int(v[i].size()) / j * j];
    }
}
```

### 最优关键思路或技巧
1. **数据结构选择**：使用vector存储每个大学的学生能力，方便动态存储和操作。
2. **算法优化**：通过对每个大学学生能力排序后计算前缀和，将计算每个$k$下地区实力的时间复杂度从$O(n^3)$优化到$O(n logn)$。具体优化在于利用每个大学学生人数限制$k$的取值范围，避免无效计算。

### 可拓展之处
同类型题通常围绕分组求和并通过前缀和优化来设计。类似算法套路是先对数据进行合理分组，再对组内数据排序并计算前缀和，最后根据题目要求遍历计算不同条件下的总和。

### 洛谷相似题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：通过前缀和思想解决最大子段和问题，与本题利用前缀和优化计算总和思路类似。
2. [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：二维前缀和的应用，本题是一维前缀和，可拓展思维。
3. [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：同样涉及数据分组和通过前缀和快速计算区域和的问题，锻炼前缀和应用能力。 

---
处理用时：68.94秒