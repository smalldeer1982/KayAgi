# 题目信息

# [ABC346C] Σ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_c

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ および正整数 $ K $ が与えられます。

$ 1 $ 以上 $ K $ 以下の整数のうち、$ A $ の中に一度も現れないものの総和を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ K\ \leq\ 2\times\ 10^9 $
- $ 1\leq\ A_i\ \leq\ 2\times\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ 以上 $ 5 $ 以下の整数のうち、$ A $ の中に一度も現れないものは $ 2,4,5 $ の $ 3 $ つです。 よって、それらの総和である $ 2+4+5=11 $ を出力します。

## 样例 #1

### 输入

```
4 5

1 6 3 1```

### 输出

```
11```

## 样例 #2

### 输入

```
1 3

346```

### 输出

```
6```

## 样例 #3

### 输入

```
10 158260522

877914575 24979445 623690081 262703497 24979445 1822804784 1430302156 1161735902 923078537 1189330739```

### 输出

```
12523196466007058```

# AI分析结果

### 题目内容重写
给定一个长度为 $N$ 的正整数序列 $A=(A_1,A_2,\dots,A_N)$ 和一个正整数 $K$，求在 $1$ 到 $K$ 之间的整数中，未出现在序列 $A$ 中的整数的总和。

### 样例解释
**样例1**  
输入：  
```
4 5
1 6 3 1
```
输出：  
```
11
```
解释：  
在 $1$ 到 $5$ 之间的整数中，未出现在序列 $A$ 中的数是 $2,4,5$，它们的总和为 $11$。

**样例2**  
输入：  
```
1 3
346
```
输出：  
```
6
```
解释：  
在 $1$ 到 $3$ 之间的整数中，未出现在序列 $A$ 中的数是 $1,2,3$，它们的总和为 $6$。

### 分析与结论
本题的核心思路是利用等差数列求和公式计算 $1$ 到 $K$ 的总和，然后减去序列 $A$ 中出现的数（去重后）。由于 $K$ 和 $A_i$ 的范围较大，直接枚举或使用桶标记会超时或超内存，因此需要使用 `map` 或 `set` 来去重。

### 精选题解
#### 1. 作者：_KHIN (赞：8)
**评分：5星**  
**关键亮点：**  
- 使用高斯求和公式计算 $1$ 到 $K$ 的总和，时间复杂度为 $O(1)$。
- 使用 `map` 去重，避免重复减去相同的数。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[200005],ans;
map <int,int> cnt;
signed main()
{
    cin>>n>>k;
    ans=(k+1)*k/2;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]<=k && !cnt[a[i]])
        {
            ans-=a[i];
            cnt[a[i]]=1;
        }
    }
    cout<<ans;
    return 0;
}
```

#### 2. 作者：Little_x_starTYJ (赞：4)
**评分：4星**  
**关键亮点：**  
- 同样使用高斯求和公式计算总和。
- 使用 `map` 去重，避免重复减去相同的数。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200010];
map<long long, bool> m;
int main() {
    long long n, k;
    cin >> n >> k;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= k && !m[a[i]])
            sum -= a[i], m[a[i]] = 1;
    }
    sum += (1 + k) * k / 2;
    cout << sum;
    return 0;
}
```

#### 3. 作者：Melo_DDD (赞：2)
**评分：4星**  
**关键亮点：**  
- 使用 `set` 去重，避免重复减去相同的数。
- 使用迭代器遍历 `set`，代码风格独特。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i ,m ,n) for (int i = (m) ;i <= (n) ;i ++)
using namespace std ;
int n ,k ,sum ,num ;
set <int> s ;
signed main () {
    cin >> n >> k ;
    sum = (k + 1) * k / 2 ;
    rep (i ,1 ,n) {
        int x ;
        cin >> x ;
        if (x <= k) s.insert (x) ;
    }
    set <int> :: iterator it ;
    it = s.begin () ;
    for ( ;it != s.end () ;it ++) num += *it ;
    cout << sum - num << endl ;
    return 0 ;
}
```

### 最优关键思路
1. **等差数列求和**：利用高斯求和公式 $1+2+\cdots+K = \frac{K(K+1)}{2}$ 快速计算 $1$ 到 $K$ 的总和。
2. **去重**：使用 `map` 或 `set` 来去重，避免重复减去相同的数。
3. **优化**：由于 $K$ 和 $A_i$ 的范围较大，直接枚举或使用桶标记会超时或超内存，因此需要使用 `map` 或 `set` 来去重。

### 拓展思路
类似的问题可以通过“整体减空白”的思路来解决，即先计算整体和，再减去不符合条件的部分。这种方法在统计未出现或未满足条件的元素时非常有效。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
3. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

这些题目都涉及到统计未出现或未满足条件的元素，适合练习类似的思路和技巧。

---
处理用时：51.81秒