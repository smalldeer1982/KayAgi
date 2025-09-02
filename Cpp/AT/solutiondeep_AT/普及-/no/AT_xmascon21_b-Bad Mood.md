# 题目信息

# Bad Mood

## 题目描述

给定两个正整数 $M$ 和 $N$。有一个 $M$ 行 $N$ 列的正方形格子。

现在，要在每个格子里画上其中一条对角线。在此基础上，考虑一个无向图，该图的顶点对应于格子的角（共有 $(M + 1) \times (N + 1)$ 个顶点），画上的对角线对应于图的边。定义通过这种方式能形成的连通分量的数量为得分。

请计算可能的最小得分和最大得分。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_xmascon21_b/0651d892dadc631ce7f050fce6b1391d1aef7999.png)示例中得分为 $10$ 的情况

## 说明/提示

### 限制

- $1 \le M \le 10^9$。
- $1 \le N \le 10^9$。

### 样例解释 #1

得分为 $6$ 和得分为 $7$ 的示例分别如下图所示：

![得分为 6 的示例](https://img.atcoder.jp/xmascon21/105091090192bc5be451863d86ff441c.png)

![得分为 7 的示例](https://img.atcoder.jp/xmascon21/b293f4f8d17c9c01555ac5bc4d9c3b72.png)

## 样例 #1

### 输入

```
2 3```

### 输出

```
6 7```

# AI分析结果

### 题目内容
# 坏心情

## 题目描述

给定两个正整数 $M$ 和 $N$。有一个 $M$ 行 $N$ 列的正方形格子。

现在，要在每个格子里画上其中一条对角线。在此基础上，考虑一个无向图，该图的顶点对应于格子的角（共有 $(M + 1) \times (N + 1)$ 个顶点），画上的对角线对应于图的边。定义通过这种方式能形成的连通分量的数量为得分。

请计算可能的最小得分和最大得分。

### 说明/提示

#### 限制

- $1 \le M \le 10^9$。
- $1 \le N \le 10^9$。

### 样例解释 #1

得分为 $6$ 和得分为 $7$ 的示例分别如下图所示：

![得分为 6 的示例](https://img.atcoder.jp/xmascon21/105091090192bc5be451863d86ff441c.png)

![得分为 7 的示例](https://img.atcoder.jp/xmascon21/b293f4f8d17c9c01555ac5bc4d9c3b72.png)

### 样例 #1

#### 输入

```
2 3```

#### 输出

```
6 7```

### 算法分类
数学

### 题解分析与结论
这道题的核心是通过数学推导找到最小和最大得分的公式。所有题解都通过观察和化简得出了相同的结论：
- 最小得分为 $M + N + 1$
- 最大得分为 $\frac{M \times N + M + N}{2} + 2$

由于数据范围较大，所有题解都强调了需要使用 `long long` 类型来避免溢出。

### 评分较高的题解
1. **作者：Nightsky_Stars (赞：8)**
   - **星级：5**
   - **关键亮点**：简洁明了地给出了公式推导和代码实现，代码可读性高。
   - **代码核心思想**：直接计算最小和最大得分并输出。
   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int main(){
       long long n,m;
       cin>>n>>m;
       cout<<n+m+1<<" "<<(n*m+n+m)/2+2<<"\n";
       return 0;
   }
   ```

2. **作者：zyc_bot (赞：3)**
   - **星级：4**
   - **关键亮点**：详细解释了公式的推导过程，代码实现也较为简洁。
   - **代码核心思想**：通过公式计算最小和最大得分并输出。
   ```cpp
   #include <iostream>
   #include <cstdio>
   #include <cstring>
   using namespace std;
   long long a, b;
   int main()
   {
       a = read(), b = read();
       long long ans = (a + b + 1), ans1 = a + b + 2 + (a * b - a - b) / 2;
       printf("%lld %lld\n", ans, ans1); 
   }
   ```

3. **作者：dulinfan2023 (赞：1)**
   - **星级：4**
   - **关键亮点**：提供了详细的公式化简过程，代码实现简洁。
   - **代码核心思想**：通过公式计算最小和最大得分并输出。
   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   #define int long long
   signed main(){
       int n,m;
       cin>>n>>m;
       int ans1=n+m+1,ans2=(n*m+n+m)/2+2;
       cout<<ans1<<" "<<ans2; 
       return 0;
   }
   ```

### 最优关键思路或技巧
- **数学推导**：通过观察和化简，找到最小和最大得分的公式。
- **数据类型**：使用 `long long` 类型来避免数据溢出。

### 可拓展之处
类似的问题可以通过数学推导来解决，尤其是在涉及大范围数据时，找到规律和公式是关键。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

---
处理用时：25.19秒