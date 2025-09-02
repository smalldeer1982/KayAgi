# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果

### 题目内容翻译

#### 题目描述

龙象征着智慧、力量和财富。在农历新年，人们用竹条和衣服制作龙的模型，用杆子举起它们，并通过高低摆动杆子来模仿飞龙的动作。

一个表演者如果杆子举得低，则用 $1$ 表示；如果杆子举得高，则用 $2$ 表示。因此，表演者的队列可以用一个序列 $a_{1},a_{2},...,a_{n}$ 来表示。

小Tommy也在其中。他想选择一个区间 $[l,r]$（$1 \leq l \leq r \leq n$），然后将 $a_{l},a_{l+1},...,a_{r}$ 反转，使得新序列的最长非递减子序列的长度最大化。

一个非递减子序列是指一个索引序列 $p_{1},p_{2},...,p_{k}$，满足 $p_{1} < p_{2} < ... < p_{k}$ 且 $a_{p1} \leq a_{p2} \leq ... \leq a_{pk}$。子序列的长度为 $k$。

#### 说明/提示

在第一个样例中，反转区间 $[2,3]$ 后，数组变为 $[1,1,2,2]$，此时最长非递减子序列的长度为 $4$。

在第二个样例中，反转区间 $[3,7]$ 后，数组变为 $[1,1,1,1,2,2,2,2,2,1]$，此时最长非递减子序列的长度为 $9$。

#### 样例 #1

##### 输入

```
4
1 2 1 2
```

##### 输出

```
4
```

#### 样例 #2

##### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

##### 输出

```
9
```

---

### 题解分析与结论

本题的核心在于通过反转一个区间，使得序列的最长非递减子序列的长度最大化。由于序列中只有 $1$ 和 $2$ 两种元素，因此可以通过动态规划（DP）来高效解决。

#### 关键思路与技巧

1. **状态定义**：大多数题解都采用了类似的状态定义，即 $f[i][j]$ 表示前 $i$ 个数中，第 $j$ 段的最长非递减子序列的长度。通常分为四段：$[1,1,...][2,2,...][1,1,...][2,2,...]$。

2. **状态转移**：通过判断当前元素是 $1$ 还是 $2$，分别更新不同段的状态。状态转移方程通常为：
   - $f[i][1] = f[i-1][1] + (a[i] == 1)$
   - $f[i][2] = \max(f[i][1], f[i-1][2] + (a[i] == 2))$
   - $f[i][3] = \max(f[i][2], f[i-1][3] + (a[i] == 1))$
   - $f[i][4] = \max(f[i][3], f[i-1][4] + (a[i] == 2))$

3. **优化**：由于状态转移只依赖于前一个状态，因此可以压缩空间复杂度，使用一维数组来存储状态。

#### 最优题解推荐

1. **作者：浅色调**  
   - **星级**：5星  
   - **关键亮点**：提供了两种解法，第一种使用线段树维护前缀和和后缀和，第二种使用DP，思路清晰，代码简洁。  
   - **核心代码**：
     ```cpp
     int main(){
         scanf("%d",&n); int t1,t2;
         For(i,1,n) scanf("%d",a+i),ct1[i]=ct1[i-1]+(a[i]==1);
         Bor(i,1,n) ct2[i]=ct2[i+1]+(a[i]==2);
         For(i,1,n+1) ppx[i]=ct1[i-1]+ct2[i];
         T.build(1,n+1,1);
         For(k,1,n+1) {
             t1=T.query(1,k,1,n+1,1),t2=T.query(k,n+1,1,n+1,1);
             ans=max(ans,t1+t2-ct1[k-1]-ct2[k]);
         }
         cout<<ans;
         return 0;
     }
     ```

2. **作者：_sh1kong_**  
   - **星级**：4星  
   - **关键亮点**：简洁明了地解释了状态转移方程，代码实现简洁，适合初学者理解。  
   - **核心代码**：
     ```cpp
     signed main(){
         cin >> n;
         for (int i = 1; i <= n; i ++ ) cin >> d[i];
         for (int i = 1; i <= n; i ++ ){
             f[1] += (d[i] == 1);
             f[2] = max(f[1], f[2] + (d[i] == 2));
             f[3] = max(f[2], f[3] + (d[i] == 1));
             f[4] = max(f[3], f[4] + (d[i] == 2));
         }
         cout << f[4];
     }
     ```

3. **作者：hmh100211**  
   - **星级**：4星  
   - **关键亮点**：详细解释了状态转移方程的推导过程，代码实现清晰，适合深入理解DP的应用。  
   - **核心代码**：
     ```cpp
     int main(){
         cin>>n;
         for(int i=1;i<=n;i++) cin>>a[i];
         for(int i=1;i<=n;i++){
             dp[i][0]=dp[i-1][0]+(a[i]==1);
             dp[i][1]=max(dp[i][0],dp[i-1][1]+(a[i]==2));
             dp[i][2]=max(dp[i][1],dp[i-1][2]+(a[i]==1));
             dp[i][3]=max(dp[i][2],dp[i-1][3]+(a[i]==2));
         }
         cout<<dp[n][3];
         return 0;
     }
     ```

#### 拓展思路与推荐题目

1. **拓展思路**：本题的DP思想可以推广到其他类似的序列问题，尤其是涉及区间操作和子序列优化的问题。类似的思路可以用于解决最长上升子序列、最长公共子序列等问题。

2. **推荐题目**：
   - [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：考察最长不上升子序列和最长上升子序列。
   - [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)：考察双向最长上升子序列。
   - [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：考察最长公共子序列的优化解法。

---
处理用时：51.71秒