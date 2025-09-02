# 题目信息

# Xenia and Bit Operations

## 题目描述

Xenia the beginner programmer has a sequence $ a $ , consisting of $ 2^{n} $ non-negative integers: $ a_{1},a_{2},...,a_{2^{n}} $ . Xenia is currently studying bit operations. To better understand how they work, Xenia decided to calculate some value $ v $ for $ a $ .

Namely, it takes several iterations to calculate value $ v $ . At the first iteration, Xenia writes a new sequence $ a_{1} or a_{2},a_{3} or a_{4},...,a_{2^{n}-1} or a_{2^{n}} $ , consisting of $ 2^{n-1} $ elements. In other words, she writes down the bit-wise OR of adjacent elements of sequence $ a $ . At the second iteration, Xenia writes the bitwise exclusive OR of adjacent elements of the sequence obtained after the first iteration. At the third iteration Xenia writes the bitwise OR of the adjacent elements of the sequence obtained after the second iteration. And so on; the operations of bitwise exclusive OR and bitwise OR alternate. In the end, she obtains a sequence consisting of one element, and that element is $ v $ .

Let's consider an example. Suppose that sequence $ a=(1,2,3,4) $ . Then let's write down all the transformations $ (1,2,3,4) $ $ → $ $ (1 or 2=3,3 or 4=7) $ $ → $ $ (3 xor 7=4) $ . The result is $ v=4 $ .

You are given Xenia's initial sequence. But to calculate value $ v $ for a given sequence would be too easy, so you are given additional $ m $ queries. Each query is a pair of integers $ p,b $ . Query $ p,b $ means that you need to perform the assignment $ a_{p}=b $ . After each query, you need to print the new value $ v $ for the new sequence $ a $ .

## 说明/提示

For more information on the bit operations, you can follow this link: http://en.wikipedia.org/wiki/Bitwise\_operation

## 样例 #1

### 输入

```
2 4
1 6 3 5
1 4
3 4
1 2
1 2
```

### 输出

```
1
3
3
3
```

# AI分析结果

### 题目内容
# Xenia和位运算

## 题目描述
新手程序员Xenia有一个由$2^{n}$个非负整数组成的序列$a$：$a_{1},a_{2},\cdots,a_{2^{n}}$。Xenia目前正在学习位运算。为了更好地理解它们是如何工作的，Xenia决定为$a$计算某个值$v$。

具体来说，计算值$v$需要进行几次迭代。在第一次迭代中，Xenia写出一个新序列$a_{1}\text{ or }a_{2},a_{3}\text{ or }a_{4},\cdots,a_{2^{n}-1}\text{ or }a_{2^{n}}$，该序列由$2^{n - 1}$个元素组成。换句话说，她写下序列$a$中相邻元素的按位或。在第二次迭代中，Xenia写出第一次迭代后得到的序列中相邻元素的按位异或。在第三次迭代中，Xenia写出第二次迭代后得到的序列中相邻元素的按位或。依此类推；按位异或和按位或操作交替进行。最后，她得到一个由一个元素组成的序列，这个元素就是$v$。

让我们考虑一个例子。假设序列$a = (1,2,3,4)$。那么让我们写下所有的变换：$(1,2,3,4)\to(1\text{ or }2 = 3,3\text{ or }4 = 7)\to(3\text{ xor }7 = 4)$。结果是$v = 4$。

你会得到Xenia的初始序列。但是为给定序列计算值$v$太容易了，所以会给你额外的$m$个查询。每个查询是一对整数$p,b$。查询$p,b$意味着你需要执行赋值$a_{p}=b$。每次查询后，你需要输出新序列$a$的新值$v$。

## 说明/提示
有关位运算的更多信息，你可以访问此链接：http://en.wikipedia.org/wiki/Bitwise_operation

## 样例 #1
### 输入
```
2 4
1 6 3 5
1 4
3 4
1 2
1 2
```
### 输出
```
1
3
3
3
```

### 算法分类
树状数组（线段树本质是一种特殊的树状数组，这里主要通过线段树维护数据结构解决问题）

### 综合分析与结论
这些题解的核心思路都是利用线段树来解决问题。题目要求对长度为$2^n$的序列进行交替的按位或和按位异或操作，并处理多次单点修改后的结果查询。各题解的算法要点在于构建线段树，在树的节点中保存相关信息（如深度、运算标记等），在更新节点时根据节点的特定属性（如深度的奇偶性、二进制位数等）决定使用按位或还是按位异或操作。解决的难点在于如何准确地根据题目中的交替运算规则更新线段树节点的值，以及如何高效地处理单点修改和查询操作。

### 所选的题解
- **作者：Priori_Incantatem（5星）**
  - **关键亮点**：思路清晰，不仅提到直接模拟的方法，还详细阐述了树形DP/dfs的思路，将操作过程转化为满二叉树，预处理树结构，利用树的性质优化查询操作，时间复杂度分析到位。
  - **个人心得**：无
  ```cpp
  void dfs(long long x) // dfs 预处理
  {
      if(x>=(1<<(n+1)))return; 
      d[x]=d[x>>1]+1; 
      dfs(x<<1);
      dfs(x<<1|1);
      if(a[x]!=-1)return; 
      if((n-d[x]) & 1)a[x]=(a[x<<1]^a[x<<1|1]); 
      else a[x]=(a[x<<1]|a[x<<1|1]);
  }
  int main()
  {
      scanf("%lld%lld",&n,&m);
      for(long long i=1;i<(1<<(n+1));++i)
      a[i]=-1;
      for(long long i=(1<<(n+1))-(1<<n);i<(1<<(n+1));++i)
      scanf("%lld",a+i); 
      dfs(1);
      while(m--)
      {
          long long x,val;
          scanf("%lld%lld",&x,&val);
          x=(1<<(n+1))-(1<<n)+x-1; 
          a[x]=val;
          while(x>1) 
          {
              x>>=1;
              if((n-d[x]) & 1)a[x]=(a[x<<1]^a[x<<1|1]);
              else a[x]=(a[x<<1]|a[x<<1|1]);
          }
          printf("%lld\n",a[1]);
      }
      return 0;
  }
  ```
  核心实现思想：通过dfs预处理满二叉树节点深度，在修改节点值后，沿着修改节点到根节点的路径，根据深度奇偶性更新节点值。
- **作者：Cylete（4星）**
  - **关键亮点**：简洁明了地指出题目实质是线段树问题，代码实现规范，利用线段树的常规操作（建树、更新）解决问题，注释清晰。
  - **个人心得**：无
  ```cpp
  inline void build(int o, int l, int r)
  {
      if(l == r)
      {
          tree[o] = a[l];
          return;
      }
      build(lson, l, mid);
      build(rson, mid + 1, r);
      deep[o] = deep[lson] + 1;
      if(deep[o] & 1) tree[o] = tree[lson] | tree[rson];
      else tree[o] = tree[lson] ^ tree[rson];
  }

  inline void update(int o, int l, int r, int pos, int k)
  {
      if(l == r)
      {
          tree[o] = k;
          return;
      }
      if(pos <= mid) update(lson, l, mid, pos, k);
      else update(rson, mid + 1, r, pos, k);
      if(deep[o] & 1) tree[o] = tree[lson] | tree[rson];
      else tree[o] = tree[lson] ^ tree[rson];
  }
  ```
  核心实现思想：在建树函数中，根据节点深度奇偶性确定节点值的运算方式；在更新函数中，根据修改位置递归更新节点，并重新计算节点值。
- **作者：MVP_Harry（4星）**
  - **关键亮点**：通过画图辅助理解，找到利用节点二进制位数判断运算方式的规律，代码实现较为完整，逻辑清晰。
  - **个人心得**：无
  ```cpp
  int convert(int x) { 
      int digit = 0;
      for (digit = 0; x > 0; x >>= 1) digit++;
      return digit;
  }

  void build(int s, int t, int p) { 
      if (s == t) { 
          d[p] = a[s];
          return ;
      }
      int m = (s + t) >> 1;
      build(s, m, p << 1), build(m + 1, t, p << 1 | 1);
      int num = convert(p);
      if ((N + 1 - num) & 1) d[p] = d[p << 1] | d[p << 1 | 1];
      else d[p] = d[p << 1] ^ d[p << 1 | 1]; 
  }

  void update(int c, int x, int s, int t, int p) { 
      if (s == t) {
          d[p] = x;
          return ;
      }
      int m = (s + t) >> 1;
      if (c <= m) update(c, x, s, m, p << 1);
      else update(c, x, m + 1, t, p << 1 | 1);
      int num = convert(p);
      if ((N + 1 - num) & 1) d[p] = d[p << 1] | d[p << 1 | 1];
      else d[p] = d[p << 1] ^ d[p << 1 | 1];
  }
  ```
  核心实现思想：通过convert函数获取节点二进制位数，在建树和更新函数中，依据二进制位数与N的关系确定运算方式并更新节点值。

### 最优关键思路或技巧
利用线段树（或类似树形结构）来维护数据，通过记录节点的深度、二进制位数等信息，根据题目给定的交替运算规则，在节点更新时准确选择按位或或按位异或操作。这种方法能够高效地处理多次单点修改和查询操作，避免了每次都从头模拟整个运算过程的时间消耗。

### 可拓展之处
同类型题通常涉及对序列进行特定规则的区间操作（如区间求和、区间最值、区间位运算等）并处理多次查询和修改。类似算法套路是构建合适的数据结构（如线段树、树状数组等），利用数据结构的性质高效地处理这些操作。例如，对于更复杂的区间操作，可以在节点中保存更多信息，在更新和查询时进行相应的处理。

### 洛谷题目推荐
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：线段树模板题，涉及区间修改和单点查询，可巩固线段树基本操作。
- [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：树状数组模板题，涉及区间修改和区间查询，与本题利用数据结构处理序列操作类似。
- [P1501 积木城堡](https://www.luogu.com.cn/problem/P1501)：可使用线段树优化动态规划，在一定程度上结合了数据结构与动态规划思想，锻炼综合运用能力。

### 个人心得摘录与总结
无。

---
处理用时：77.82秒