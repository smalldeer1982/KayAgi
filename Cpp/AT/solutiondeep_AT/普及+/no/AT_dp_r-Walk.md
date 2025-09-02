# 题目信息

# Walk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_r

$ N $ 頂点の単純有向グラフ $ G $ があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。

各 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $) について、頂点 $ i $ から $ j $ への有向辺の有無が整数 $ a_{i,\ j} $ によって与えられます。 $ a_{i,\ j}\ =\ 1 $ ならば頂点 $ i $ から $ j $ への有向辺が存在し、$ a_{i,\ j}\ =\ 0 $ ならば存在しません。

$ G $ の長さ $ K $ の有向パスは何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。 ただし、同じ辺を複数回通るような有向パスも数えるものとします。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 10^{18} $
- $ a_{i,\ j} $ は $ 0 $ または $ 1 $ である。
- $ a_{i,\ i}\ =\ 0 $

### Sample Explanation 1

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_0\_muffet.png) 長さ $ 2 $ の有向パスは、次の $ 6 $ 通りです。 - $ 1 $ → $ 2 $ → $ 3 $ - $ 1 $ → $ 2 $ → $ 4 $ - $ 2 $ → $ 3 $ → $ 4 $ - $ 2 $ → $ 4 $ → $ 1 $ - $ 3 $ → $ 4 $ → $ 1 $ - $ 4 $ → $ 1 $ → $ 2 $

### Sample Explanation 2

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_1\_muffet.png) 長さ $ 3 $ の有向パスは、次の $ 3 $ 通りです。 - $ 1 $ → $ 2 $ → $ 1 $ → $ 2 $ - $ 2 $ → $ 1 $ → $ 2 $ → $ 1 $ - $ 2 $ → $ 1 $ → $ 2 $ → $ 3 $

### Sample Explanation 3

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_2\_muffet.png) 長さ $ 2 $ の有向パスは、次の $ 1 $ 通りです。 - $ 4 $ → $ 5 $ → $ 6 $

### Sample Explanation 5

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
4 2

0 1 0 0

0 0 1 1

0 0 0 1

1 0 0 0```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3

0 1 0

1 0 1

0 0 0```

### 输出

```
3```

## 样例 #3

### 输入

```
6 2

0 0 0 0 0 0

0 0 1 0 0 0

0 0 0 0 0 0

0 0 0 0 1 0

0 0 0 0 0 1

0 0 0 0 0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
1 1

0```

### 输出

```
0```

## 样例 #5

### 输入

```
10 1000000000000000000

0 0 1 1 0 0 0 1 1 0

0 0 0 0 0 1 1 1 0 0

0 1 0 0 0 1 0 1 0 1

1 1 1 0 1 1 0 1 1 0

0 1 1 1 0 1 0 1 1 1

0 0 0 1 0 0 1 0 1 0

0 0 0 1 1 0 0 1 0 1

1 0 0 0 1 0 1 0 0 0

0 0 0 0 0 1 0 0 0 0

1 0 1 1 1 0 1 1 1 0```

### 输出

```
957538352```

# AI分析结果

### 题目翻译
# Walk

## 题目描述

$ N $ 个顶点的简单有向图 $ G $。顶点编号为 $ 1,\ 2,\ \ldots,\ N $。

对于每个 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $)，顶点 $ i $ 到 $ j $ 的有向边的存在性由整数 $ a_{i,\ j} $ 给出。$ a_{i,\ j}\ =\ 1 $ 表示存在从 $ i $ 到 $ j $ 的有向边，$ a_{i,\ j}\ =\ 0 $ 表示不存在。

$ G $ 中长度为 $ K $ 的有向路径有多少条？请输出结果对 $ 10^9\ +\ 7 $ 取模后的值。注意，允许路径中多次经过同一条边。

## 说明/提示

### 约束

- 输入均为整数。
- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 10^{18} $
- $ a_{i,\ j} $ 为 $ 0 $ 或 $ 1 $。
- $ a_{i,\ i}\ =\ 0 $

### 样例解释

样例1、2、3、4、5分别对应不同的图结构，具体路径数见题目描述。

### 算法分类
图论

### 综合分析与结论
本题的核心问题是在有向图中计算长度为 $K$ 的路径数。由于 $K$ 的范围非常大（$1 \leq K \leq 10^{18}$），直接使用动态规划或暴力枚举的方法不可行。题解中普遍采用了矩阵快速幂的方法，通过将路径数问题转化为矩阵乘法问题，利用矩阵快速幂的 $O(n^3 \log K)$ 时间复杂度来高效求解。

### 精选题解

#### 题解1：作者：Legitimity (赞：16)
- **星级**：5星
- **关键亮点**：清晰地解释了矩阵快速幂与Floyd算法的结合，代码简洁且高效。
- **核心代码**：
  ```cpp
  inline mul operator*(const mul& a,const mul& b){
      mul ret; ret.siz=a.siz;
      for(rg int i=1;i<=ret.siz;++i){
          for(rg int k=1;k<=ret.siz;++k){
              for(rg int j=1;j<=ret.siz;++j){
                  ret.v[i][j]+=a.v[i][k]*b.v[k][j]%mod;
                  ret.v[i][j]%=mod;
              }
          }
      }
      return ret;
  }
  inline mul ksm(mul base,int p){
      mul ret; ret.siz=base.siz;
      for(rg int i=1;i<=base.siz;++i) ret.v[i][i]=1;
      while(p){
          if(p&1) ret=ret*base;
          base=base*base; p>>=1;
      }
      return ret;
  }
  ```
- **实现思想**：通过矩阵乘法实现路径数的计算，利用快速幂加速矩阵的幂运算。

#### 题解2：作者：Alexandra (赞：7)
- **星级**：4星
- **关键亮点**：详细分析了矩阵乘法与路径数问题的关系，代码结构清晰。
- **核心代码**：
  ```cpp
  fun operator *(fun wjl,fun jia){
      fun c;
      memset(c.a,0,sizeof(c.a));
      for(long long k=1;k<=n;k++){
          for(long long i=1;i<=n;i++){
              for(long long j=1;j<=n;j++)c.a[i][j]=(c.a[i][j]+wjl.a[i][k]*jia.a[k][j]%mod)%mod;
          }
      }
      return c;
  }
  fun ksm(fun x,long long p){
      fun res;
      memset(res.a,0,sizeof(res.a));
      for(long long i=1;i<=n;i++) res.a[i][i]=1;
      while(p){
          if(p&1) res=res*x;
          x=x*x;
          p>>=1;
      }
      return res;
  }
  ```
- **实现思想**：通过矩阵乘法实现路径数的计算，利用快速幂加速矩阵的幂运算。

#### 题解3：作者：喵仔牛奶 (赞：6)
- **星级**：4星
- **关键亮点**：简洁明了地解释了矩阵快速幂的应用，代码实现简洁。
- **核心代码**：
  ```cpp
  matrix operator * (matrix x) const {
      matrix c;
      memset(c.a, 0, sizeof c.a);
      for (int i = 1; i <= n; i ++)
          for (int k = 1; k <= n; k ++)
              for (int j = 1; j <= n; j ++)
                  c.a[i][j] += a[i][k] * x.a[k][j], c.a[i][j] %= mod;
      return c;
  }
  int main() {
      cin >> n >> k;
      for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= n; j ++)
              cin >> dis.a[i][j];
      for (int i = 1; i <= n; i ++) res.a[i][i] = 1;
      for (; k; k >>= 1, dis = dis * dis)
          if (k & 1) res = res * dis;
      for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= n; j ++)
              ans += res.a[i][j], ans %= mod;
      cout << ans << '\n';
      return 0;
  }
  ```
- **实现思想**：通过矩阵乘法实现路径数的计算，利用快速幂加速矩阵的幂运算。

### 最优关键思路
1. **矩阵快速幂**：将路径数问题转化为矩阵乘法问题，利用矩阵快速幂的 $O(n^3 \log K)$ 时间复杂度来高效求解。
2. **矩阵乘法**：通过矩阵乘法实现路径数的计算，利用矩阵的幂运算来加速计算。

### 可拓展之处
类似的问题可以扩展到其他图论问题，如最短路径、最大流等，都可以通过矩阵快速幂的方法进行优化。

### 推荐题目
1. [P1939 【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)
2. [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)
3. [P4783 【模板】矩阵求逆](https://www.luogu.com.cn/problem/P4783)

---
处理用时：47.81秒