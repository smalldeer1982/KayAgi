# 题目信息

# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2
2 1
3 5
5 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
5 6
```

### 输出

```
7
```

# AI分析结果

### 题目内容重写（中文）

你邀请了 $n$ 位客人共进晚餐！你计划安排一个或多个椅子圈。每把椅子要么被一位客人占据，要么空着。你可以安排任意数量的圈子。

你的客人有点害羞，所以第 $i$ 位客人希望在他的椅子左边至少有 $l_i$ 把空椅子，右边至少有 $r_i$ 把空椅子。"左"和"右"的方向是基于所有客人都面向圈子的中心。注意，当一位客人独自坐在一个圈子中时，他左边的 $l_i$ 把椅子和右边的 $r_i$ 把椅子可能会重叠。

你需要使用的最少椅子总数是多少？

### 说明/提示

在第二个样例中，唯一的最优解是使用两个圈子：一个圈子有 $5$ 把椅子，容纳客人 $1$ 和 $2$，另一个圈子有 $10$ 把椅子，容纳客人 $3$ 和 $4$。

在第三个样例中，你只有一个圈子，里面只有一个人。这位客人需要在他左边至少有 $5$ 把空椅子，右边至少有 $6$ 把空椅子，因此总共需要的椅子数至少为 $6+1=7$。

### 样例 #1

#### 输入

```
3
1 1
1 1
1 1
```

#### 输出

```
6
```

### 样例 #2

#### 输入

```
4
1 2
2 1
3 5
5 3
```

#### 输出

```
15
```

### 样例 #3

#### 输入

```
1
5 6
```

#### 输出

```
7
```

---

### 题解分析与结论

#### 关键思路与技巧

1. **贪心策略**：为了使椅子数最少，应该尽量让两个人的 $l_i$ 和 $r_j$ 相互匹配，从而减少重复的椅子数。具体来说，将 $l$ 和 $r$ 分别排序，然后取 $\max(l_i, r_i)$ 的和，再加上 $n$（每位客人需要一把椅子）。
  
2. **排序优化**：通过排序 $l$ 和 $r$，可以确保每次匹配的都是当前最小的 $l_i$ 和 $r_i$，从而最大化椅子的重复利用。

3. **数据类型**：由于 $l_i$ 和 $r_i$ 的最大值为 $10^9$，$n$ 的最大值为 $10^5$，答案可能会达到 $10^{14}$，因此需要使用 `long long` 类型来存储结果。

#### 最优题解推荐

1. **作者：Itst (5星)**
   - **关键亮点**：简洁明了地提出了贪心策略，代码清晰，直接对 $l$ 和 $r$ 进行排序并求和，逻辑清晰。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     #define MAXN 100010
     using namespace std;

     int numL[MAXN] , numR[MAXN];

     int main(){
         int N;
         cin >> N;
         for(int i = 1 ; i <= N ; i++)
             cin >> numL[i] >> numR[i];
         sort(numL + 1 , numL + N + 1);
         sort(numR + 1 , numR + N + 1);
         long long ans = N;
         for(int i = 1 ; i <= N ; i++)
             ans += max(numL[i] , numR[i]);
         cout << ans;
         return 0;
     }
     ```

2. **作者：king_xbz (4星)**
   - **关键亮点**：详细解释了贪心策略的推导过程，代码简洁，逻辑清晰。
   - **代码实现**：
     ```cpp
     signed main()
     {
         int n;
         cin>>n;
         for(fint i=1;i<=n;i++)
         cin>>l[i]>>r[i];
         int bas=n;//初始至少有n把椅子
         sort(l+1,l+n+1);
         sort(r+1,r+n+1);
         int ans=0;
         for(fint i=1;i<=n;i++)
         ans+=max(l[i],r[i]);
         cout<<ans+bas;
         return 0;
     }
     ```

3. **作者：chufuzhe (4星)**
   - **关键亮点**：简洁明了地提出了贪心策略，代码清晰，逻辑清晰。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     int a[100005]; //定义，a表示l，b表示r
     int b[100005];
     int main()
     {
         ios::sync_with_stdio(false);
         long long ans = 0; //注意用long long
         int n;
         cin >> n; //输入
         for(int i = 1; i <= n; i++)
             cin >> a[i] >> b[i];
         sort(a + 1, a + n + 1); //排序
         sort(b + 1, b + n + 1);
         for(int i = 1; i <= n; i++) //计算
             ans += max(a[i], b[i]) + 1; //注意要+1
         cout << ans << endl; //输出
         return 0;
     }
     ```

### 扩展思路与推荐题目

1. **扩展思路**：类似的贪心策略可以应用于其他需要最大化资源利用的问题，如任务调度、资源分配等。通过排序和匹配最小/最大值，可以有效减少资源浪费。

2. **推荐题目**：
   - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心策略，每次合并最小的两堆果子。
   - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心策略，按接水时间从小到大排序。
   - [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心策略，按结束时间排序，选择不重叠的线段。

### 个人心得摘录

- **作者：彭骐飞**：通过调整法推导出贪心策略的正确性，强调了排序和匹配的重要性。
- **作者：Itst**：直接提出贪心策略，简洁明了，代码实现清晰，易于理解。

通过这些题解，我们可以学习到如何通过排序和贪心策略来优化资源利用，解决类似的问题。

---
处理用时：45.71秒