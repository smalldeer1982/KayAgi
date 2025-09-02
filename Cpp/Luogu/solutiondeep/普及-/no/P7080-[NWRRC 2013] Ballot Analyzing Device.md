# 题目信息

# [NWRRC 2013] Ballot Analyzing Device

## 题目描述



Election committee of Flatland is preparing for presidential elections. To minimize human factor in ballot counting they decided to develop an automated Ballot Analyzing Device $(BAD).$

There are $n$ candidates running for president. The ballot contains one square field for each candidate. The voter must mark exactly one of the fields. If no field is marked or there are two or more marked fields, the ballot is invalid. Each voter puts $his/her$ ballot to a special scanner in BAD. The scanner analyzes marks on the ballot and creates a special voting string of $n$ characters: $‘X'$ for marked field and $‘. '$ for unmarked one. Now voting strings must be analyzed to get the report. Your task is to develop a report generator for BAD.

Given voting strings for all ballots, your program must print the voting report. Candidates in the report must be arranged in order of decreasing number of votes. If two candidates have the same number of votes, they must have the same order as in a voting ballot. For each candidate calculate $his/her$ result in percent (if the candidate received $p$ votes, the result in percent is $100p/m)$ . The last line of the report must indicate the percentage of the invalid ballots.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4 7
Loudy
Apples
Dogman
Miller
.X..
X...
....
..X.
..XX
..X.
..X.
```

### 输出

```
Dogman 42.86%
Loudy 14.29%
Apples 14.29%
Miller 0.00%
Invalid 28.57%
```

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
题目要求处理投票数据，统计每个候选人的得票数，计算得票率，并按照得票率排序输出。难点在于如何处理无效票、四舍五入以及排序时的稳定性（相同得票率按输入顺序排序）。

各题解的核心思路相似，均通过模拟投票过程，统计得票数，计算得票率，并排序输出。主要区别在于四舍五入的实现方式、排序方法以及代码结构。

### 所选题解
1. **作者：JeffWang2019**  
   - **星级：4**  
   - **关键亮点**：使用结构体存储候选人信息，排序时考虑得票率和输入顺序，四舍五入处理清晰。  
   - **个人心得**：强调了四舍五入的重要性，并提供了详细的实现方法。  
   - **核心代码**：
     ```cpp
     struct dalao {
         string name;
         int t=0,pl;
         double p;
     }lwn[11];
     bool cmp(dalao x,dalao y) {
         if(x.p==y.p) return x.pl<y.pl;
         return x.p>y.p;
     }
     ```

2. **作者：D2T1**  
   - **星级：4**  
   - **关键亮点**：使用 `STL sort` 进行排序，四舍五入使用 `round` 函数，代码简洁。  
   - **核心代码**：
     ```cpp
     struct people{string name;int id,tic;double ans;} a[maxn];
     bool cmp(people a,people b){return a.ans!=b.ans?a.ans>b.ans:a.id<b.id;}
     ```

3. **作者：honey_**  
   - **星级：4**  
   - **关键亮点**：使用结构体和自定义排序函数，四舍五入处理清晰，代码结构合理。  
   - **核心代码**：
     ```cpp
     struct node {
         string name;
         int t=0,id;
         double p;
         bool operator < (const node k) const {
             if(p==k.p) return id<k.id;
             return p>k.p;
         }
     }d[11];
     ```

### 最优关键思路或技巧
1. **结构体存储信息**：使用结构体存储候选人的名字、得票数、输入顺序和得票率，方便后续排序和输出。
2. **四舍五入处理**：通过 `round` 函数或手动实现四舍五入，确保得票率计算的准确性。
3. **排序稳定性**：在排序时，除了比较得票率，还需考虑输入顺序，确保相同得票率的候选人按输入顺序排列。

### 可拓展之处
类似问题可以扩展到其他需要统计和排序的场景，如学生成绩排名、商品销量统计等。关键在于如何处理数据、计算比例以及排序时的稳定性。

### 推荐题目
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
2. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)
3. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)

---
处理用时：23.45秒