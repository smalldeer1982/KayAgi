# 题目信息

# [ABC154D] Dice in Line

## 题目描述

给出 $N$ 个骰子，我们同时投掷 $K$ 个连续骰子。求出可能的最大数学期望值。

## 说明/提示

本题使用**Special Judge**，你的答案和数据误差小于等于$10^{-6}$就会被评判对

## 样例 #1

### 输入

```
5 3

1 2 2 4 5```

### 输出

```
7.000000000000```

## 样例 #2

### 输入

```
4 1

6 6 6 6```

### 输出

```
3.500000000000```

## 样例 #3

### 输入

```
10 4

17 13 13 12 15 20 10 13 17 11```

### 输出

```
32.000000000000```

# AI分析结果

### 题目内容重写
# [ABC154D] Dice in Line

## 题目描述

给出 $N$ 个骰子，我们同时投掷 $K$ 个连续骰子。求出可能的最大数学期望值。

## 说明/提示

本题使用**Special Judge**，你的答案和数据误差小于等于$10^{-6}$就会被评判对

## 样例 #1

### 输入

```
5 3

1 2 2 4 5```

### 输出

```
7.000000000000```

## 样例 #2

### 输入

```
4 1

6 6 6 6```

### 输出

```
3.500000000000```

## 样例 #3

### 输入

```
10 4

17 13 13 12 15 20 10 13 17 11```

### 输出

```
32.000000000000```

### 算法分类
前缀和、数学

### 题解分析与结论
本题的核心在于计算每个骰子的期望值，并通过前缀和快速求解连续 $K$ 个骰子的期望和的最大值。所有题解都采用了类似的前缀和思路，但在代码实现和细节处理上有所不同。

### 所选高星题解

#### 题解1：Blikewsr (5星)
- **关键亮点**：思路清晰，代码简洁，直接使用前缀和数组存储每个骰子的期望值，并通过滑动窗口求最大值。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  #define N 200001
  #define int long long
  using namespace std;
  int n, k;
  double prefix[N], p[N], maxn;
  signed main() {
      cin >> n >> k;
      for(int i = 1; i <= n; i++) {
          cin >> p[i];
          p[i] = (1 + p[i]) / 2;
          prefix[i] = prefix[i - 1] + p[i];
      }
      for(int i = k; i <= n; i++) {
          maxn = max(maxn, prefix[i] - prefix[i - k]);
      }
      printf("%0.12lf\n", maxn);
      return 0;
  }
  ```

#### 题解2：Texas_the_Omertosa (4星)
- **关键亮点**：使用了01背包的思想来解释最大期望值的求解过程，代码同样简洁，但解释略显冗余。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  #define int long long 
  using namespace std;
  double a[200005];
  double sum[200005];//前缀和数组
  inline double maxx(double x,double y) {
      if(x>y) return x;
      return y;
  }
  signed main() {
      ios::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);//加速
      int n,k;
      cin>>n>>k;
      double max=0;
      for(int i=1;i<=n;i++) {
          cin>>a[i];
          a[i]=(a[i]+1)/2;//套期望值公式
          sum[i]=sum[i-1]+a[i];//前缀和存储
      }
      for(int i=k;i<=n;i++) {
          max=maxx(max,sum[i]-sum[i-k]);
      }
      printf("%.12lf\n",max);
      return 0;
  }
  ```

#### 题解3：Binary_Lee (4星)
- **关键亮点**：提前预处理了骰子的期望值，代码结构清晰，但预处理部分略显多余。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  #define IOS ios::sync_with_stdio(false)
  #define TIE cin.tie(0),cout.tie(0)
  using namespace std;
  double f[1005],s[200005],now,ans;
  int n,k,a;
  signed main(){
      IOS;TIE;
      cin>>n>>k;
      for(int i=1;i<=1000;i++) now+=(double)i,f[i]=now/(double)i;
      for(int i=1;i<=n;i++) cin>>a,s[i]=s[i-1]+f[a];
      for(int i=k;i<=n;i++) ans=max(ans,s[i]-s[i-k]);
      cout<<fixed<<setprecision(16)<<ans<<endl;
      return 0;
  }
  ```

### 最优关键思路
1. **期望值计算**：每个骰子的期望值为 $(1 + \text{面数}) / 2$。
2. **前缀和优化**：通过前缀和数组快速计算任意连续 $K$ 个骰子的期望和。
3. **滑动窗口**：使用滑动窗口技巧在 $O(N)$ 时间内找到最大值。

### 可拓展之处
类似的问题可以扩展到其他需要快速求解连续子区间和的场景，如最大子数组和、最小子数组和等。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

---
处理用时：33.08秒