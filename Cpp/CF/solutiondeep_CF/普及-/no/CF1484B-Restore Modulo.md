# 题目信息

# Restore Modulo

## 题目描述

For the first place at the competition, Alex won many arrays of integers and was assured that these arrays are very expensive. After the award ceremony Alex decided to sell them. There is a rule in arrays pawnshop: you can sell array only if it can be compressed to a generator.

This generator takes four non-negative numbers $ n $ , $ m $ , $ c $ , $ s $ . $ n $ and $ m $ must be positive, $ s $ non-negative and for $ c $ it must be true that $ 0 \leq c < m $ . The array $ a $ of length $ n $ is created according to the following rules:

- $ a_1 = s \bmod m $ , here $ x \bmod y $ denotes remainder of the division of $ x $ by $ y $ ;
- $ a_i = (a_{i-1} + c) \bmod m $ for all $ i $ such that $ 1 < i \le n $ .

For example, if $ n = 5 $ , $ m = 7 $ , $ c = 4 $ , and $ s = 10 $ , then $ a = [3, 0, 4, 1, 5] $ .

Price of such an array is the value of $ m $ in this generator.

Alex has a question: how much money he can get for each of the arrays. Please, help him to understand for every array whether there exist four numbers $ n $ , $ m $ , $ c $ , $ s $ that generate this array. If yes, then maximize $ m $ .

## 样例 #1

### 输入

```
6
6
1 9 17 6 14 3
3
4 2 2
3
7 3 4
3
2 2 4
5
0 1000000000 0 1000000000 0
2
1 1```

### 输出

```
19 8
-1
-1
-1
2000000000 1000000000
0```

# AI分析结果

### 题目内容
# 恢复模运算

## 题目描述
在竞赛中，亚历克斯赢得了许多整数数组，并确信这些数组非常昂贵。颁奖典礼结束后，亚历克斯决定卖掉它们。数组当铺有一个规则：只有当数组可以压缩成一个生成器时，才能出售该数组。

这个生成器需要四个非负整数 $n$、$m$、$c$、$s$。其中，$n$ 和 $m$ 必须为正数，$s$ 为非负数，并且对于 $c$ 需满足 $0 \leq c < m$。长度为 $n$ 的数组 $a$ 是根据以下规则创建的：
- $a_1 = s \bmod m$，这里 $x \bmod y$ 表示 $x$ 除以 $y$ 的余数；
- 对于所有满足 $1 < i \leq n$ 的 $i$，有 $a_i = (a_{i - 1} + c) \bmod m$。

例如，如果 $n = 5$，$m = 7$，$c = 4$，$s = 10$，那么 $a = [3, 0, 4, 1, 5]$。

这样一个数组的价格就是这个生成器中的 $m$ 值。

亚历克斯有一个问题：他能从每个数组中得到多少钱。请帮助他判断对于每个数组，是否存在四个数 $n$、$m$、$c$、$s$ 来生成这个数组。如果存在，那么最大化 $m$。

## 样例 #1
### 输入
```
6
6
1 9 17 6 14 3
3
4 2 2
3
7 3 4
3
2 2 4
5
0 1000000000 0 1000000000 0
2
1 1
```
### 输出
```
19 8
-1
-1
-1
2000000000 1000000000
0
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是围绕给定数组在模运算下的性质展开。由于 $a_i$ 由 $a_{i - 1}$ 通过 $a_i = (a_{i - 1} + c) \bmod m$ 得到，且 $0 \leq c < m$，所以 $a_i$ 与 $a_{i - 1}$ 的关系只有 $a_i = a_{i - 1} + c$ （当 $a_{i - 1} + c < m$ ）和 $a_i = a_{i - 1} + c - m$ （当 $a_{i - 1} + c \geq m$ ）两种情况。由此，不同题解通过分析数组相邻元素差值的规律来判断是否存在符合条件的 $m$ 和 $c$，并求解最大的 $m$。各题解的主要区别在于具体的实现方式和细节处理，如有些通过构造差分序列，有些通过直接遍历数组判断相邻元素关系等。

### 所选的题解
- **作者：Priori_Incantatem（5星）**
  - **关键亮点**：思路清晰，分多种情况详细讨论，代码实现逻辑紧密结合思路，注释详细。
  - **个人心得**：无
  ```cpp
  bool check()
  {
      if(n==1)return 1;
      bool flag=1;
      for(int i=1;i<n;++i)
      if(a[i]>a[i+1] || a[i]+m!=a[i+1])
      {flag=0;break;}
      if(flag)return 1;
      flag=1;
      for(int i=1;i<n;++i)
      if(a[i]<=a[i+1]){flag=0;break;}
      if(flag)
      {
          int tmp=a[1]-a[2];
          for(int i=2;i<n;++i)
          if(a[i]-a[i+1]!=tmp){flag=0;break;}
          if(flag)return 1;
      }
      return 0;
  }
  int calc()
  {
      int tmp;
      for(int i=1;i<n;++i)
      {
          if(a[i]<=a[i+1] && a[i]+m!=a[i+1])
          return 0;
          if(a[i]<=a[i+1])continue;
          if((a[i]+m)-a[i+1]<=val)return 0;
          tmp=(a[i]+m)-a[i+1];
      }
      for(int i=1;i<n;++i)
      {
          if(a[i]<=a[i+1])continue;
          if(a[i]+m-a[i+1]!=tmp)return 0;
      }
      return tmp;
  }
  ```
  核心实现思想：`check` 函数用于判断数组是否为单调递增且相邻元素差值相等（无需取模情况），或者单调递减且相邻元素差值相等（可通过调整 $m$ 实现）；`calc` 函数用于在既有递增又有递减的情况下，根据递减部分求出 $m$，并检查其是否统一且满足条件。
- **作者：feicheng（4星）**
  - **关键亮点**：通过构造差分序列，并利用差分序列最多只有两个不同数字这一结论简化判断过程，代码简洁高效。
  - **个人心得**：无
  ```cpp
  inline void Solve() {
      vis.clear(),num=ans=ans_=0;        
      int mx = -1,tmp[3];
      read(n);
      memset(a,0,sizeof a),memset(b,0,sizeof b);
      for(int i = 1;i <= n;++i) read(a[i]),mx=max(a[i],mx);
      if(n == 1)  return ans = 0,void();
      for(int i = 2;i <= n;++i) b[i-1] = a[i] - a[i-1];//差分
      int num = 0;
      for(int i = 1;i <= n-1;++i) {
           if(!vis[b[i]]) tmp[++num] = b[i],vis[b[i]] = 1;
           if(num == 3) return ans = -1,void();//如果有三个不同的数
      }
      if(num == 1) return ans = 0,void();
      if(tmp[1] < 0 and tmp[2] < 0) return ans = -1,void();
      ans = abs(tmp[1]) + abs(tmp[2]),ans_ = max(tmp[1],tmp[2]);
      if(ans < mx) return ans = -1,void();
  }
  ```
  核心实现思想：先对数组进行差分，统计差分序列中不同数字的个数，若超过两个则无解；若只有一个则 $m$ 可任意大；若有两个不同数字，根据其计算 $m$ 和 $c$，并检查 $m$ 是否大于数组中的最大值。
- **作者：Acfboy（4星）**
  - **关键亮点**：思路直接，通过分别判断数组递增、递减部分的差值是否一致来确定是否有解，同时考虑了各种特殊情况，代码逻辑清晰。
  - **个人心得**：赛时 WA 了两次，一次是未判断数是否小于 $m$，一次是判断只上升情况出错，强调了边界条件和特殊情况判断的重要性。
  ```cpp
  signed main() {
      scanf("%lld", &T);
      while(T--) {
          scanf("%lld", &n);
          c = -1, rec = -1, m = -1;
          for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
          bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
          for(int i = 2; i <= n; i++) {
              if(c == -1 && a[i] >= a[i-1]) c = a[i] - a[i-1];
              else if(a[i] >= a[i-1] && a[i] - a[i-1]!= c) {flag1 = true; break;}
              if(rec == -1 && a[i] < a[i-1])  rec = a[i-1] - a[i];
              else if(a[i] < a[i-1] && a[i-1] - a[i]!= rec) flag2 = true;
          }
          if(flag1 || flag2) { puts("-1"); continue; }
          if(c == -1 &&!flag2 || rec == -1 &&!flag1) {puts("0"); continue; }
          for(int i = 2; i <= n; i++) 
              if(m == -1 && a[i] < a[i-1]) m = a[i-1] + c - a[i];
              else if(a[i] < a[i-1] && a[i-1] + c - a[i]!= m) { flag3 = true; break;}
          if(flag3) { puts("-1"); continue; }
          for(int i = 1; i <= n; i++) 
              if(a[i] >= m) flag4 = true;
          if(flag4) puts("-1");
          else printf("%lld %lld\n", m, c);
      }
  }
  ```
  核心实现思想：遍历数组，分别记录递增部分的差值 $c$ 和递减部分的差值 $rec$，判断其是否一致，若不一致则无解；若只有递增或只有递减且差值一致则 $m$ 可任意大；否则根据递减部分计算 $m$，并检查 $m$ 是否冲突以及数组中的数是否小于 $m$。

### 最优关键思路或技巧
利用数组相邻元素在模运算下的关系，通过分析相邻元素差值的规律来解决问题。如构造差分序列，根据差分序列中不同数字的个数和取值来快速判断是否有解以及求解 $m$ 和 $c$，这种方法简洁高效，能有效简化问题的处理过程。

### 可拓展思路
同类型题通常围绕数论中的模运算、等差数列性质等知识点进行变化，例如改变生成数组的规则，或者在判断条件上增加更多限制等。类似算法套路是通过分析序列在特定运算下相邻元素的关系，利用这些关系总结出判断条件或求解公式。

### 推荐题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的同余方程求解，与本题都涉及数论知识和相关运算。
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：同样是数论相关，关于有理数在模运算下的取余问题，锻炼对模运算的理解和应用。
- [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)：数论中乘法逆元的求解，与本题类似，需要对数论概念和运算有清晰的理解和运用。

### 个人心得摘录与总结
Acfboy 在赛时遇到两次 WA，一次是未判断数小于 $m$ 的情况，一次是判断只上升情况出错。这强调了在处理这类问题时，边界条件和特殊情况判断的重要性，在编码过程中需要全面考虑各种可能情况，避免遗漏关键条件导致错误。 

---
处理用时：92.37秒