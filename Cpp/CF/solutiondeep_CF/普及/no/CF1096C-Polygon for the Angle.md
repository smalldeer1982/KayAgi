# 题目信息

# Polygon for the Angle

## 题目描述

You are given an angle $ \text{ang} $ .

The Jury asks You to find such regular $ n $ -gon (regular polygon with $ n $ vertices) that it has three vertices $ a $ , $ b $ and $ c $ (they can be non-consecutive) with $ \angle{abc} = \text{ang} $ or report that there is no such $ n $ -gon.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1096C/a07369ed7e451bdcca3873a15baacc5b09a55799.png)If there are several answers, print the minimal one. It is guarantied that if answer exists then it doesn't exceed $ 998244353 $ .

## 说明/提示

The answer for the first query is on the picture above.

The answer for the second query is reached on a regular $ 18 $ -gon. For example, $ \angle{v_2 v_1 v_6} = 50^{\circ} $ .

The example angle for the third query is $ \angle{v_{11} v_{10} v_{12}} = 2^{\circ} $ .

In the fourth query, minimal possible $ n $ is $ 180 $ (not $ 90 $ ).

## 样例 #1

### 输入

```
4
54
50
2
178
```

### 输出

```
10
18
90
180
```

# AI分析结果

【题目内容】
# 正多边形中的角度

## 题目描述

给定一个角度 $ \text{ang} $。

你需要找到一个正 $ n $ 边形（具有 $ n $ 个顶点的正多边形），使得该正多边形中存在三个顶点 $ a $、$ b $ 和 $ c $（它们可以不相邻），且满足 $ \angle{abc} = \text{ang} $，或者报告不存在这样的正 $ n $ 边形。

如果存在多个答案，输出最小的 $ n $。保证如果答案存在，则 $ n $ 不超过 $ 998244353 $。

## 说明/提示

第一个查询的答案在上图中。

第二个查询的答案可以在正 $ 18 $ 边形中找到。例如，$ \angle{v_2 v_1 v_6} = 50^{\circ} $。

第三个查询的示例角度是 $ \angle{v_{11} v_{10} v_{12}} = 2^{\circ} $。

在第四个查询中，最小的 $ n $ 是 $ 180 $（而不是 $ 90 $）。

## 样例 #1

### 输入

```
4
54
50
2
178
```

### 输出

```
10
18
90
180
```

【算法分类】
数学

【题解分析与结论】
该题的核心是通过数学推导找到满足条件的最小正多边形边数 $ n $。主要思路是利用正多边形的几何性质，特别是圆周角和圆心角的关系，以及角度与边数的数学关系。

【高星题解】
1. **作者：nydzsf_qwq (赞：7)**  
   - **星级：5**  
   - **关键亮点**：通过数学推导直接得出 $ n $ 的计算公式，避免了枚举，效率高。  
   - **核心代码**：
     ```cpp
     int gcd(int a,int b) {
         if(b==0) return a;
         return gcd(b,a%b);
     }
     int main() {
         cin>>T;
         while(T--) {
             cin>>alpha;
             tmp1=180/gcd(alpha,180);
             tmp2=(360+180-alpha-1)/(180-alpha);
             ans=(tmp2+tmp1-1)/tmp1*tmp1;
             cout<<ans<<endl;
         }
         return 0;
     }
     ```
   - **实现思想**：通过计算角度与 180 的最大公约数，结合不等式推导出最小 $ n $。

2. **作者：Heartlessly (赞：5)**  
   - **星级：4**  
   - **关键亮点**：通过枚举正多边形的边数和角度，预处理所有可能的解，查询时直接输出。  
   - **核心代码**：
     ```cpp
     for (int i = 3; i <= 360; ++i)
         for (int j = 1; j <= i - 2; ++j)
             if (180 * j % i == 0 && !theta[180 * j / i])
                 theta[180 * j / i] = i;
     ```
   - **实现思想**：枚举正多边形的边数 $ i $ 和角度 $ j $，计算可能的 $ \theta $ 并记录最小 $ n $。

3. **作者：zhangzirui66 (赞：2)**  
   - **星级：4**  
   - **关键亮点**：通过预处理所有可能的 $ n $ 和 $ j $，查询时直接输出结果。  
   - **核心代码**：
     ```cpp
     for(int i = 3; i <= 360; i ++){
         for(int j = 1; j <= i - 2; j ++){
             if(180 * j % i == 0 && !ans[180 * j / i]) ans[180 * j / i] = i;
         }
     }
     ```
   - **实现思想**：枚举正多边形的边数 $ i $ 和角度 $ j $，计算可能的 $ \theta $ 并记录最小 $ n $。

【最优关键思路】
通过数学推导和预处理，可以高效地找到满足条件的最小正多边形边数 $ n $。利用正多边形的几何性质和角度与边数的关系，避免了不必要的枚举。

【可拓展之处】
类似的问题可以通过几何性质和数学推导来解决，特别是在处理角度和边数关系时，可以借鉴本题的思路。

【推荐题目】
1. [P1357 正多边形](https://www.luogu.com.cn/problem/P1357)
2. [P1358 正多边形的对角线](https://www.luogu.com.cn/problem/P1358)
3. [P1359 正多边形的内角](https://www.luogu.com.cn/problem/P1359)

---
处理用时：33.91秒