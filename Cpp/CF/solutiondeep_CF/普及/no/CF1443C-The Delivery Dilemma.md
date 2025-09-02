# 题目信息

# The Delivery Dilemma

## 题目描述

Petya is preparing for his birthday. He decided that there would be $ n $ different dishes on the dinner table, numbered from $ 1 $ to $ n $ . Since Petya doesn't like to cook, he wants to order these dishes in restaurants.

Unfortunately, all dishes are prepared in different restaurants and therefore Petya needs to pick up his orders from $ n $ different places. To speed up this process, he wants to order courier delivery at some restaurants. Thus, for each dish, there are two options for Petya how he can get it:

- the dish will be delivered by a courier from the restaurant $ i $ , in this case the courier will arrive in $ a_i $ minutes,
- Petya goes to the restaurant $ i $ on his own and picks up the dish, he will spend $ b_i $ minutes on this.

Each restaurant has its own couriers and they start delivering the order at the moment Petya leaves the house. In other words, all couriers work in parallel. Petya must visit all restaurants in which he has not chosen delivery, he does this consistently.

For example, if Petya wants to order $ n = 4 $ dishes and $ a = [3, 7, 4, 5] $ , and $ b = [2, 1, 2, 4] $ , then he can order delivery from the first and the fourth restaurant, and go to the second and third on your own. Then the courier of the first restaurant will bring the order in $ 3 $ minutes, the courier of the fourth restaurant will bring the order in $ 5 $ minutes, and Petya will pick up the remaining dishes in $ 1 + 2 = 3 $ minutes. Thus, in $ 5 $ minutes all the dishes will be at Petya's house.

Find the minimum time after which all the dishes can be at Petya's home.

## 样例 #1

### 输入

```
4
4
3 7 4 5
2 1 2 4
4
1 2 3 4
3 3 3 3
2
1 2
10 10
2
10 10
1 2```

### 输出

```
5
3
2
3```

# AI分析结果

### 题目内容重写

**送货难题**

**题目描述**

Petya正在为他的生日做准备。他决定在晚餐桌上摆放$n$道不同的菜，编号从$1$到$n$。由于Petya不喜欢做饭，他打算从餐厅订购这些菜。

不幸的是，所有的菜都在不同的餐厅制作，因此Petya需要从$n$个不同的地方取餐。为了加快这一过程，他打算在一些餐厅订购快递服务。因此，对于每道菜，Petya有两种选择：

- 餐厅$i$的快递员会将菜送到家，快递员将在$a_i$分钟内到达，
- Petya自己去餐厅$i$取菜，他将花费$b_i$分钟。

每个餐厅都有自己的快递员，他们在Petya离开家时开始送餐。换句话说，所有快递员是并行工作的。Petya必须依次访问所有他没有选择快递的餐厅。

例如，如果Petya想订购$n=4$道菜，且$a=[3,7,4,5]$，$b=[2,1,2,4]$，那么他可以选择从第一家餐厅和第四家餐厅订购快递，自己去第二家和第三家餐厅取餐。那么第一家餐厅的快递员将在$3$分钟内送达，第四家餐厅的快递员将在$5$分钟内送达，而Petya将花费$1+2=3$分钟取餐。因此，所有菜将在$5$分钟内送达Petya的家。

求所有菜送达Petya家的最短时间。

### 算法分类

贪心、二分

### 题解分析与结论

本题的核心在于如何在快递和自取之间做出选择，以最小化总时间。快递是并行的，而自取是串行的，因此我们需要找到一个平衡点，使得快递和自取的总时间最小。

大多数题解采用了贪心或二分的思路。贪心策略通常基于对$a_i$和$b_i$的排序，通过逐步调整选择来优化总时间。二分法则是通过二分答案，判断在给定时间内是否能够完成所有任务。

### 评分较高的题解

1. **作者：_Pecky_ (赞：3)**
   - **星级：4**
   - **关键亮点**：通过排序$a_i$并计算$b_i$的后缀和，找到最小时间。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     sort(l + 1, l + n + 1, cmp1);
     for(int i = n; i >= 1; i--){
         sum[i] = sum[i + 1] + l[i].b;
     }
     ll ans = 1e9 + 10;
     for(int i = 0; i <= n; i++){
         ll maxx = max(l[i].a, sum[i + 1]);
         ans = min(ans, maxx);
     }
     ```

2. **作者：LeavingZzz (赞：3)**
   - **星级：4**
   - **关键亮点**：使用二分法，通过贪心策略判断在给定时间内是否能够完成任务。思路清晰，代码可读性强。
   - **代码核心**：
     ```cpp
     bool check(int p) {
         long long sum = 0;
         for(int i = 1; i <= N; i++)
             if(a[i] > p) sum += b[i];
         return sum <= p;
     }
     ```

3. **作者：Composite_Function (赞：1)**
   - **星级：4**
   - **关键亮点**：通过后缀和优化，计算最小时间。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     sort(val + 1, val + n + 1, cmp);
     for(int i = n; i >= 1; --i)
         sum[i] = sum[i + 1] + val[i].b;
     int ans = 1e18;
     for(int i = 0; i <= n; ++i) {
         int tmp = max(val[i].a, sum[i + 1]);
         ans = min(ans, tmp);
     }
     ```

### 最优关键思路

最优的思路是通过排序$a_i$并计算$b_i$的后缀和，找到最小时间。这种方法的时间复杂度为$O(n \log n)$，主要瓶颈在于排序。通过贪心策略，我们可以逐步调整选择，使得总时间最小。

### 拓展思路

类似的问题可以通过贪心或二分法来解决，尤其是在涉及到并行和串行任务的优化时。例如，任务调度问题、资源分配问题等。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得

在调试过程中，需要注意多组测试数据的初始化问题，避免因为未清空数组而导致错误。此外，二分法的边界条件需要仔细处理，确保不会出现死循环或漏解的情况。

---
处理用时：35.77秒