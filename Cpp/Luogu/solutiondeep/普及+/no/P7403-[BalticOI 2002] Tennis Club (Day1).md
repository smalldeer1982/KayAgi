# 题目信息

# [BalticOI 2002] Tennis Club (Day1)

## 题目描述

有 $N$ 个人想互相交朋友，第 $i$ 个人想和 $G_i$ 个人交朋友。

求一种交朋友的分配方式。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$2 \le N \le 1000$，$1 \le G_i < N$。

**本题使用 Special
Judge。**

#### 说明

翻译自 [BalticOI 2002 Day1 B Tennis Club](https://boi.cses.fi/files/boi2002_day1.pdf)。

## 样例 #1

### 输入

```
3
1
2
1 ```

### 输出

```
SOLUTION
2
1 3
2 ```

## 样例 #2

### 输入

```
3
2
2
1 ```

### 输出

```
NO SOLUTION```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心逻辑是通过贪心算法，每次选择当前需要交朋友最多的人，优先与剩下需要交朋友最多的人交朋友，直到所有人的需求被满足或无法满足。多个题解都采用了类似的思路，但实现细节和优化程度有所不同。

### 所选题解
1. **作者：floris (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过调整法证明贪心策略的正确性，代码结构清晰，使用二维数组记录朋友关系，最后遍历输出。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++){
         sort(e+1,e+n+1,cmp);
         if(e[1].c==0) break;
         for(int j=2;j<=e[1].c+1;j++){
             if(e[j].c==0){
                 cout<<"NO SOLUTION"<<'\n';
                 return 0;
             }
             e[j].c--;
             f[e[1].id][e[j].id]=1;
             f[e[j].id][e[1].id]=1;
         }
         e[1].c=0;
     }
     ```

2. **作者：_RainCappuccino_ (赞：3)**
   - **星级：4星**
   - **关键亮点**：引入Havel-Hakimi定理进行证明，代码逻辑严谨，使用pair和vector存储数据，处理无解情况。
   - **核心代码**：
     ```cpp
     for(int t=1;t<=n;t++){
         sort(g+1,g+1+n);
         int j=n-1;
         while(g[n].first){
             g[j].first--, g[n].first--;
             if(g[j].first<0){
                 cout<<"NO SOLUTION\n";
                 return 0;
             }
             ans[g[j].second].push_back(g[n].second);
             ans[g[n].second].push_back(g[j].second);
             j--;
         }
     }
     ```

3. **作者：ys_kylin__ (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过while循环和重新排序优化贪心策略，代码结构清晰，使用vector存储朋友关系，处理无解情况。
   - **核心代码**：
     ```cpp
     while(g[1].num!=0){
         for(int i=2;i<=g[1].num+1;i++){
             if(g[i].num==0){
                 printf("NO SOLUTION");
                 return 0;
             }
             else{
                 g[i].num--;
                 ve[g[1].id].push_back(g[i].id);
                 ve[g[i].id].push_back(g[1].id);
             }
         }
         g[1].num=0;
         sort(g+1,g+n+1,cmp);
     }
     ```

### 最优关键思路或技巧
1. **贪心策略**：每次选择当前需要交朋友最多的人，优先与剩下需要交朋友最多的人交朋友。
2. **Havel-Hakimi定理**：用于证明贪心策略的正确性，确保度数序列可以简单图化。
3. **优化排序**：在每次操作后重新排序，确保贪心策略的最优性。

### 可拓展之处
类似的问题可以应用于图论中的度数序列构造问题，如判断一个度数序列是否可以构造一个简单图，或者构造一个满足特定条件的图。

### 推荐题目
1. [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)
2. [P1342 无序字母对](https://www.luogu.com.cn/problem/P1342)
3. [P1343 无序字母对](https://www.luogu.com.cn/problem/P1343)

### 个人心得摘录
- **ys_kylin__**：调试了好几天，一度以为SPJ有误，最终通过while循环和重新排序优化贪心策略，成功AC。
- **indream**：通过减少排序量，只排序有变动的部分，优化了时间复杂度，最终通过本题。

这些心得展示了在调试和优化过程中的思考与改进，对于解决类似问题具有参考价值。

---
处理用时：23.54秒