# 题目信息

# [Kubic] Addition

## 题目背景

建议先看 B 题题目背景。

## 题目描述

有一个初始长度为 $n$ 的序列 $a$。你需要进行 $n-1$ 次操作。每一次操作先在当前序列中选出两个相邻的数 $x,y$ 并删除（原序列中 $x$ 在 $y$ 左边），再往原位置插入一个 $x+y$ 或一个 $x-y$。$n-1$ 次操作之后最终只会剩下恰好一个数，求这个剩下的数的最大值。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5,|a_i|\le 10^9$。

||分值|$n$|$\vert a_i\vert$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$10$|$\le 2$|无特殊限制|无|
|$\operatorname{Subtask}2$|$20$|$\le 100$|无特殊限制|无|
|$\operatorname{Subtask}3$|$5$|无特殊限制|无特殊限制|$a_i\ge 0$|
|$\operatorname{Subtask}4$|$30$|无特殊限制|$\le 1$|无|
|$\operatorname{Subtask}5$|$35$|无特殊限制|无特殊限制|无|

### 样例解释

一种操作过程如下：

`-1 1 1 -1 1`

`-1 1 1 -2`

`-1 1 3`

`-1 4`

`3`

可以证明没有更优的方案。

## 样例 #1

### 输入

```
5
-1 1 1 -1 1```

### 输出

```
3```

# AI分析结果

### 综合分析与结论

本题的核心目标是最大化最终剩下的一个数，通过一系列相邻数的加减操作。大多数题解都采用了贪心策略，即从左到右遍历序列，第一个数保持不变，后续每个数都加上其绝对值。这种策略的合理性在于，对于每个数，加上其绝对值可以确保贡献最大化。

#### 最优关键思路
1. **贪心策略**：从左到右遍历序列，第一个数保持不变，后续每个数都加上其绝对值。
2. **数学证明**：通过分析相邻两个数的加减操作，证明加上绝对值是局部最优解，进而全局最优。
3. **代码实现**：使用 `long long` 类型存储结果，避免溢出。

#### 可拓展之处
- **类似问题**：类似的问题可以通过贪心策略解决，如最大子序列和、最小化操作次数等。
- **优化思路**：对于更复杂的操作序列，可以考虑动态规划或分治策略。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 所选高星题解

#### 题解1：银杉水杉秃杉 (4星)
- **关键亮点**：思路清晰，代码简洁，直接应用贪心策略，且对第一个数的处理有明确说明。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  #define int long long
  using namespace std;
  const int N = 1e5 + 10;
  int n, x, ans;
  signed main()
  {
      scanf("%lld%lld", &n, &x);
      ans = x;
      for (int i = 2; i <= n; i++)
      {
          scanf("%lld", &x);
          ans += x < 0 ? -x : x;
      }
      printf("%lld\n", ans);
      return 0;
  }
  ```

#### 题解2：mzyc_jx (4星)
- **关键亮点**：详细解释了贪心策略的合理性，代码可读性强，且强调了 `long long` 的重要性。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int a[100001];
  int main()
  {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      int n,b,c;
      cin>>n;
      cin>>a[1];
      long long sum=a[1];
      for(int i=2;i<=n;i++)
      {
          cin>>a[i];
          sum+=abs(a[i]);
      }
      cout<<sum;
      return 0;
  }
  ```

#### 题解3：InterN_NOT_FOUND (4星)
- **关键亮点**：通过倒序遍历解决了顺序问题，且对最后一次操作进行了特殊处理，思路新颖。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  inline int f(int x){return x>0?x:-x;}
  int n=read(),a[114514];
  signed main()
  {
      for(int i=1;i<=n;i++)a[i]=read();
      for(int i=n;i>=2;i--){
          int x=a[i-1],y=a[i];
          if(i!=2){
              if(f(x-y)>f(x+y))a[i-1]=x-y;
              else a[i-1]=x+y;
          }
          else {
              a[i-1]=max(x-y,x+y);
          }
      }
      out(a[1],'l');
      return 0;
  }
  ```

### 个人心得摘录
- **调试经历**：多位作者提到在调试过程中发现第一个数的处理是关键，必须保持原值。
- **踩坑教训**：不开 `long long` 会导致溢出，多位作者强调了这一点。
- **顿悟感想**：通过贪心策略，局部最优解可以推导出全局最优解，这一思路在类似问题中广泛应用。

---
处理用时：33.53秒