# 题目信息

# Make Array Good

## 题目描述

我们称一个长度为 $m$ 序列 $b$ 是好的，当且仅当对于每一个二元组 $i,j \in [1,m]$，都有 $\min(b_i,b_j) | \max(b_i,b_j)$。

其中 $|$ 表示整除，即 $a|b$ 表示 $a$ 被 $b$ 整除。

接下来给定一个长度为 $n$ 的序列 $a$。

你可以对他进行以下操作：

- 选择 $i(1 \le i \le n)$ 和一个非负整数 $x(0 \le x \le a_i)$，将 $a_i$ 变成 $a_i+x$。

- 你应该保证在操作后 $a_i \le 10^{18}$。

你需要使用最多 $n$ 个操作，使得 $a$ 序列成为一个好的序列，可以证明一定是可以构造出来的。

请输出构造方案。

## 样例 #1

### 输入

```
4
4
2 3 5 5
2
4 8
5
3 4 343 5 6
3
31 5 17```

### 输出

```
4
1 2
1 1
2 2
3 0
0
5
1 3
1 4
2 1
5 4
3 7
3
1 29
2 5
3 3```

# AI分析结果

### 题目内容
# 使数组变好

## 题目描述
我们称一个长度为 $m$ 的序列 $b$ 是好的，当且仅当对于每一个二元组 $i, j \in [1, m]$，都有 $\min(b_i, b_j) | \max(b_i, b_j)$。其中 $|$ 表示整除，即 $a|b$ 表示 $a$ 能整除 $b$。

接下来给定一个长度为 $n$ 的序列 $a$。你可以对它进行以下操作：
- 选择 $i(1 \le i \le n)$ 和一个非负整数 $x(0 \le x \le a_i)$，将 $a_i$ 变成 $a_i + x$。
- 你应该保证在操作后 $a_i \le 10^{18}$。

你需要使用最多 $n$ 个操作，使得 $a$ 序列成为一个好的序列，可以证明一定是可以构造出来的。请输出构造方案。

## 样例 #1
### 输入
```
4
4
2 3 5 5
2
4 8
5
3 4 343 5 6
3
31 5 17
```
### 输出
```
4
1 2
1 1
2 2
3 0
0
5
1 3
1 4
2 1
5 4
3 7
3
1 29
2 5
3 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于“对于任意正整数 $x$，在 $x$ 到 $2x$ 中一定有一个 $2$ 的整数次幂”这一性质，将数组中的每个数 $a_i$ 变为大于等于它的最小的 $2$ 的整数次幂，以此保证数组中任意两个数成倍数关系，且操作次数最多为 $n$ 次符合要求。不同之处主要在于寻找大于等于 $a_i$ 的最小的 $2$ 的整数次幂的实现方式。

### 所选的题解
- **作者：cjh20090318（5星）**
    - **关键亮点**：使用数学公式 $2^{\lceil \log_2 a_i \rceil}$ 直接计算结果，代码简洁高效，思路清晰明了。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
int n,a[100001];
int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        printf("%d\n",n);
        for(int i=1;i<=n;i++) printf("%d %d\n",i,(1<<((int)ceil(log2(a[i]))))-a[i]);
    }
    return 0;
}
```
    - **核心思想**：通过 `ceil(log2(a[i]))` 计算出大于等于 $\log_2 a_i$ 的最小整数，再通过左移操作 `(1<<((int)ceil(log2(a[i]))))` 得到大于等于 $a_i$ 的最小的 $2$ 的整数次幂，最后减去 $a_i$ 得到要增加的值。
- **作者：FQR_ （4星）**
    - **关键亮点**：代码逻辑简单易懂，通过循环直接找到大于 $a_i$ 的最小的 $2$ 的整数次幂。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;cin>>n;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)
    {
        int x;cin>>x;
        int k=1;
        while(k<=x) k*=2;
        cout<<i<<" "<<k-x<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--) solve();
    return 0; 
}
```
    - **核心思想**：从 $k = 1$ 开始，通过循环不断将 $k$ 乘以 $2$，直到 $k$ 大于 $x$，此时的 $k$ 即为大于 $a_i$ 的最小的 $2$ 的整数次幂，$k - x$ 就是要增加的值。
- **作者：郑朝曦zzx（4星）**
    - **关键亮点**：先给出引理及证明，逻辑严谨，代码利用对数运算和位运算快速得到结果。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pf printf
#define test int T = rd(); while (T--)
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define fr freopen("input.txt", "r", stdin);
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define yes printf("YES\n");
#define no printf("NO\n");
#define int long long
inline int rd()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
signed main()
{
    test
    {
        int n = rd(); printf("%lld\n", n);
        F(i, 1, n)
        {
            int x = rd(); int k = log2(x) + 1;
            printf("%lld %lld\n", i, (1 << k) - x);
        }
    }
    return 0;
}
```
    - **核心思想**：通过 `log2(x) + 1` 得到大于等于 $\log_2 x$ 的最小整数 $k$，再通过 `(1 << k)` 得到大于等于 $x$ 的最小的 $2$ 的整数次幂，`(1 << k) - x` 即为要增加的值。

### 最优关键思路或技巧
利用“在 $x$ 到 $2x$ 中一定有一个 $2$ 的整数次幂”这一数学性质，将每个数转化为大于等于它的最小的 $2$ 的整数次幂，从而满足数组中任意两数成倍数关系的要求。实现方式上，使用数学公式 $2^{\lceil \log_2 a_i \rceil}$ 计算结果较为简洁高效。

### 拓展
同类型题通常围绕构造满足特定条件的数组或序列，类似的算法套路是寻找关键的数学性质或规律，利用这些性质来指导构造过程。

### 洛谷题目推荐
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217) 

---
处理用时：51.90秒