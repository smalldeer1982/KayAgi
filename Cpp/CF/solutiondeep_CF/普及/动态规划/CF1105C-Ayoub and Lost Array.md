# 题目信息

# Ayoub and Lost Array

## 题目描述

已知有一个长度为$n$($1\leq n\leq 2 \times 10^5$)的数列，每一个数的大小在$[l,r]$($1\leq l \leq r \leq 10^9$)之间。求出有多少种方案使得这个数列的和为$3$的倍数。答案对$10^9+7$取模。当然，如果无法组成任何一个合法的数列，答案即为$0$。

## 样例 #1

### 输入

```
2 1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
9 9 99
```

### 输出

```
711426616
```

# AI分析结果

### 题目内容重写（中文）

已知有一个长度为$n$($1\leq n\leq 2 \times 10^5$)的数列，每一个数的大小在$[l,r]$($1\leq l \leq r \leq 10^9$)之间。求出有多少种方案使得这个数列的和为$3$的倍数。答案对$10^9+7$取模。当然，如果无法组成任何一个合法的数列，答案即为$0$。

### 题解分析与结论

本题的核心在于如何高效地计算满足条件的数列方案数。由于$n$和$r$的范围较大，直接枚举所有可能的数列是不可行的。因此，大多数题解都采用了动态规划（DP）的思路，通过统计区间$[l,r]$中模3余0、1、2的数的个数，并利用这些信息进行状态转移。

#### 关键思路与技巧
1. **模3统计**：首先统计区间$[l,r]$中模3余0、1、2的数的个数，记为$cnt[0]$、$cnt[1]$、$cnt[2]$。这一步可以通过数学公式快速计算，避免了逐个枚举。
2. **动态规划**：定义$dp[i][j]$表示前$i$个数的和模3余$j$的方案数。通过状态转移方程，逐步计算出$dp[n][0]$，即最终答案。
3. **滚动数组优化**：由于$dp[i]$只依赖于$dp[i-1]$，可以使用滚动数组优化空间复杂度，将空间复杂度从$O(n)$降低到$O(1)$。

### 评分较高的题解

#### 题解1：BFLSTiger (5星)
- **关键亮点**：提供了从暴力到优化的完整思路，逐步优化时间复杂度，最终通过矩阵快速幂将时间复杂度降低到$O(\log n)$。
- **代码实现**：
  ```cpp
  #include<cstdio>
  #include<iostream>
  #include<cstring>
  #include<algorithm>
  using namespace std;
  namespace Dango
  {
      const int MOD=1000000007;
      struct matrix
      {
          int x,y;
          long long num[3][3];
          matrix operator * (const matrix b)const
          {
              matrix res;
              memset(res.num,0,sizeof(res.num));
              res.x=x;res.y=b.y;
              for(int k=0;k<y;k++)
                  for(int i=0;i<x;i++)
                      for(int j=0;j<b.y;j++)
                          res.num[i][j]=(res.num[i][j]+num[i][k]*b.num[k][j]%MOD)%MOD;
              return res;
          }
      }res,ans;
      int n,l,r;
      int read()
      {
          int x=0,f=0;
          char ch=getchar();
          while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
          while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
          return f?-x:x;
      }
      matrix pow_(matrix a,long long b)
      {
          matrix res;
          memset(res.num,0,sizeof(res.num));
          res.x=res.y=a.x;
          for(int i=0;i<res.x;i++)
              res.num[i][i]=1;
          while(b)
          {
              if(b&1)res=res*a;
              a=a*a;
              b>>=1;
          }
          return res;
      }
      int work()
      {
          n=read();l=read();r=read();
          res.x=res.y=3;
          res.num[0][0]=res.num[1][1]=res.num[2][2]=(r+3)/3-(l+2)/3;
          res.num[0][1]=res.num[1][2]=res.num[2][0]=(r+2)/3-(l+1)/3;
          res.num[0][2]=res.num[1][0]=res.num[2][1]=(r+1)/3-l/3;
          ans.x=1;ans.y=3;
          ans.num[0][0]=1;
          ans=ans*pow_(res,n);
          printf("%lld",ans.num[0][0]);
          return 0;
      }
  }
  int main()
  {
      return Dango::work();
  }
  ```

#### 题解2：ModestCoder_ (4星)
- **关键亮点**：简洁明了地介绍了DP思路，并通过滚动数组优化了空间复杂度。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  #define maxn 200010
  #define LL long long
  #define qy 1000000007
  using namespace std;
  LL n, l, r, num[3], dp[2][3];

  int main(){
      scanf("%d%lld%lld", &n, &l, &r);
      num[0] = r / 3 - (l - 1) / 3;
      num[1] = (r + 2) / 3 - (l + 1) / 3;
      num[2] = (r + 1) / 3 - l / 3;
      dp[0][0] = 1;
      for (int i = 1; i <= n; ++i){
          int now = i & 1, pre = now ^ 1;
          memset(dp[now], 0, sizeof(dp[now]));
          for (int j = 0; j <= 2; ++j)
          for (int k = 0; k <= 2; ++k)
              (dp[now][(j + k) % 3] += dp[pre][j] * num[k] % qy) %= qy;    
      }
      printf("%lld\n", dp[n & 1][0]);
      return 0;
  }
  ```

#### 题解3：hsfzLZH1 (4星)
- **关键亮点**：详细解释了DP状态转移方程，并通过滚动数组优化了空间复杂度。
- **代码实现**：
  ```cpp
  #include<cstdio>
  #include<cstring>
  #include<algorithm>
  using namespace std;
  const int maxn=200010;
  typedef long long ll;
  const ll mod=1000000007;
  ll n,l,r,f[maxn][3],a[3];
  int main()
  {
      scanf("%lld%lld%lld",&n,&l,&r);
      a[0]=r/3-(l-1)/3;
      a[1]=(r+2)/3-(l+1)/3;
      a[2]=(r+1)/3-l/3;
      f[0][0]=1ll;
      for(int i=1;i<=n;i++)
      {
          for(int j=0;j<3;j++)for(int k=0;k<3;k++)
          f[i][(j+k)%3]=(f[i][(j+k)%3]+f[i-1][j]*a[k]%mod)%mod;
      }
      printf("%lld\n",f[n][0]);
      return 0; 
  }
  ```

### 最优关键思路总结
1. **模3统计**：通过数学公式快速计算区间$[l,r]$中模3余0、1、2的数的个数，避免了逐个枚举。
2. **动态规划**：利用DP状态转移方程，逐步计算出前$i$个数的和模3余$j$的方案数，最终得到$dp[n][0]$。
3. **滚动数组优化**：通过滚动数组将空间复杂度从$O(n)$降低到$O(1)$，适用于大规模数据。

### 可拓展之处
- **类似问题**：类似的模数问题可以通过统计模数的分布，并结合动态规划来解决。例如，求和为$k$的倍数的数列方案数。
- **矩阵快速幂**：对于某些递推问题，可以通过矩阵快速幂将时间复杂度从$O(n)$降低到$O(\log n)$。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095)
3. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)

### 个人心得总结
- **调试经历**：在实现DP时，初始状态的设置非常重要，确保$dp[0][0]=1$，否则会导致后续状态转移错误。
- **踩坑教训**：在计算模3余数的个数时，注意边界条件的处理，避免出现负数或超出范围的情况。
- **顿悟感想**：通过矩阵快速幂优化递推问题，不仅提高了效率，也加深了对线性代数的理解。

---
处理用时：59.92秒