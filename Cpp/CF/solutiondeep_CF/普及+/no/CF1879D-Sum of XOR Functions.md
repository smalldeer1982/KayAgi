# 题目信息

# Sum of XOR Functions

## 题目描述

You are given an array $ a $ of length $ n $ consisting of non-negative integers.

You have to calculate the value of $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1) $ , where $ f(l, r) $ is $ a_l \oplus a_{l+1} \oplus \dots \oplus a_{r-1} \oplus a_r $ (the character $ \oplus $ denotes bitwise XOR).

Since the answer can be very large, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, the answer is equal to $ f(1, 1) + 2 \cdot f(1, 2) + 3 \cdot f(1, 3) + f(2, 2) + 2 \cdot f(2, 3) + f(3, 3) =  $ $ = 1 + 2 \cdot 2 + 3 \cdot 0 + 3 + 2 \cdot 1 + 2 = 12 $ .

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
12```

## 样例 #2

### 输入

```
4
39 68 31 80```

### 输出

```
1337```

## 样例 #3

### 输入

```
7
313539461 779847196 221612534 488613315 633203958 394620685 761188160```

### 输出

```
257421502```

# AI分析结果

### 题目内容重写
给定一个长度为 $n$ 的数组 $a$，数组中的元素为非负整数。要求计算以下表达式的值：
$$
\sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1)
$$
其中 $f(l, r)$ 表示 $a_l \oplus a_{l+1} \oplus \dots \oplus a_{r-1} \oplus a_r$（$\oplus$ 表示按位异或）。由于答案可能非常大，输出时需要对 $998244353$ 取模。

### 算法分类
位运算、前缀和

### 题解分析与结论
本题的核心在于如何高效计算所有子区间的异或和，并乘以区间长度。大多数题解采用了以下思路：
1. **前缀异或和**：通过前缀异或和数组 $s$，将 $f(l, r)$ 转化为 $s_r \oplus s_{l-1}$，从而简化计算。
2. **拆位计算**：将问题按二进制位拆解，逐位计算贡献，最后将各位的贡献相加。
3. **动态维护**：在遍历过程中，动态维护当前位的 $0$ 和 $1$ 的个数及其下标和，从而快速计算当前位的贡献。

### 高星题解推荐

#### 题解作者：Zelotz (赞：22)
- **星级**：5星
- **关键亮点**：
  - 使用前缀异或和数组简化了 $f(l, r)$ 的计算。
  - 通过拆位计算，逐位维护 $0$ 和 $1$ 的个数及其下标和，高效计算贡献。
  - 代码简洁且优化程度高，时间复杂度为 $O(n \log V)$。
- **代码核心思想**：
  ```cpp
  const int N = 3e5 + 5, P = 998244353;
  int n, s[N], cnt[2], sum[2];
  signed main()
  {
      cin >> n;
      R(i, 1, n)
      {
          int x;
          cin >> x;
          s[i] = s[i - 1] ^ x;
      }
      int ans = 0;
      R(j, 0, 31)
      {
          cnt[0] = cnt[1] = sum[0] = sum[1] = 0;
          R(i, 0, n)
          {
              int x = s[i] >> j & 1;
              (ans += ((1ll * i * cnt[!x] % P - sum[!x]) * (1 << j) % P + P) % P) %= P;
              ++cnt[x];
              (sum[x] += i) %= P;
          }
      }
      cout << ans << '\n';
      return 0;
  }
  ```

#### 题解作者：Na2PtCl6 (赞：12)
- **星级**：4星
- **关键亮点**：
  - 通过前缀和和拆位计算，优化了问题的复杂度。
  - 动态维护 $0$ 和 $1$ 的个数及其下标和，快速计算贡献。
  - 代码结构清晰，易于理解。
- **代码核心思想**：
  ```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int maxn=300004,mod=998244353;
  char sep[maxn][34];  //to minimize memory
  int n,res,sum[34][2],cnt[34][2],a[maxn],xsum[maxn];

  signed main(){
      scanf("%lld",&n);
      for(int i=1;i<=n;i++){
          scanf("%lld",&a[i]);
          xsum[i]=xsum[i-1]^a[i];
          for(int j=32;j>=0;j--)
              sep[i][j]=((xsum[i]>>j)&1);
      }
      for(int i=32;i>=0;i--)
          cnt[i][0]=1;
      for(int i=1;i<=n;i++){
          for(int j=32;j>=0;j--)
              res=(res+(cnt[j][sep[i][j]^1]*i%mod-sum[j][sep[i][j]^1]%mod+mod*2)*(1<<j))%mod;
          for(int j=32;j>=0;j++){
              sum[j][sep[i][j]]+=i;
              cnt[j][sep[i][j]]++;
          }
      }
      printf("%lld\n",res);
      return 0;
  }
  ```

#### 题解作者：Creeper_l (赞：12)
- **星级**：4星
- **关键亮点**：
  - 通过前缀异或和和拆位计算，逐位维护 $0$ 和 $1$ 的个数及其下标和。
  - 代码结构清晰，易于理解，时间复杂度为 $O(n \log V)$。
- **代码核心思想**：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define int long long
  #define inf 0x3f
  #define inf_db 127
  #define ls id << 1
  #define rs id << 1 | 1
  #define re register
  #define endl '\n'
  typedef pair <int,int> pii;
  const int MAXN = 3e5 + 10;
  const int mod = 998244353;
  int n,a[MAXN],s[MAXN],ans; 
  signed main()
  {
      cin >> n;
      for(int i = 1;i <= n;i++) cin >> a[i];
      for(int i = 0;i <= 30;i++)
      {
          s[1] = 0;
          for(int j = 1;j <= n;j++) s[j + 1] = s[j] ^ (a[j] >> i & 1);
          vector <int> cnt(2, 0);
          vector <int> sum(2, 0);
          for(int j = 1;j <= n + 1;j++)
          {
              ans = (ans + cnt[s[j] ^ 1] * j % mod * (1ll << i)) % mod;
              ans = (ans - sum[s[j] ^ 1] * (1ll << i) + mod) % mod;
              cnt[s[j]]++;
              sum[s[j]] = (sum[s[j]] + j) % mod;
          }
          ans = ans % mod;
      } 
      cout << ans << endl;
      return 0;
  }
  ```

### 最优关键思路总结
1. **前缀异或和**：通过前缀异或和数组 $s$，将 $f(l, r)$ 转化为 $s_r \oplus s_{l-1}$，简化了计算。
2. **拆位计算**：将问题按二进制位拆解，逐位计算贡献，最后将各位的贡献相加。
3. **动态维护**：在遍历过程中，动态维护当前位的 $0$ 和 $1$ 的个数及其下标和，从而快速计算当前位的贡献。

### 拓展思路
类似的问题可以通过前缀和和拆位计算来解决，尤其是涉及到异或操作的问题。例如，计算所有子区间的异或和、统计满足某些条件的子区间等。

### 推荐题目
1. [P3917 异或序列](https://www.luogu.com.cn/problem/P3917)
2. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)
3. [P4592 [TJOI2018]异或](https://www.luogu.com.cn/problem/P4592)

---
处理用时：57.50秒