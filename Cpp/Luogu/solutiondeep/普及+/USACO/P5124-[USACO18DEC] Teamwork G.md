# 题目信息

# [USACO18DEC] Teamwork G

## 题目描述

在 Farmer John 最喜欢的节日里，他想要给他的朋友们赠送一些礼物。由于他并不擅长包装礼物，他想要获得他的奶牛们的帮助。你可能能够想到，奶牛们本身也不是很擅长包装礼物，而 Farmer John 即将得到这一教训。

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^4$）排成一行，方便起见依次编号为 $1\dots N$。奶牛 $i$ 的包装礼物的技能水平为 $s_i$。她们的技能水平可能参差不齐，所以 FJ 决定把她的奶牛们分成小组。每一组可以包含任意不超过 $K$ 头的连续的奶牛（$1\le K\le 10^3$），并且一头奶牛不能属于多于一个小组。由于奶牛们会互相学习，这一组中每一头奶牛的技能水平会变成这一组中水平最高的奶牛的技能水平。

请帮助 FJ 求出，在他合理地安排分组的情况下，可以达到的技能水平之和的最大值。

## 说明/提示

在这个例子中，最优的方案是将前三头奶牛和后三头奶牛分别分为一组，中间的奶牛单独成为一组（注意一组的奶牛数量可以小于 $K$）。这样能够有效地将 $7$ 头奶牛的技能水平提高至 $15$、$15$、$15$、$9$、$10$、$10$、$10$，和为 $84$。

## 样例 #1

### 输入

```
7 3
1
15
7
9
2
5
10```

### 输出

```
84```

# AI分析结果

### 综合分析与结论
这些题解主要围绕动态规划（DP）来解决将奶牛分组以获取最大技能水平和的问题。核心思路是通过定义状态数组，枚举分组情况并不断更新状态值。不同题解在实现细节上有所差异，如求区间最大值的方式，有的直接暴力枚举，有的使用线段树、ST 表等数据结构优化。整体来看，大部分题解思路清晰，但在代码可读性、优化程度等方面存在差异。

### 所选题解
- **作者：linyinuo2008（5 星）**
    - **关键亮点**：思路详细，从题意理解到动态规划分析，再到复杂度优化都有清晰阐述，代码注释丰富，便于理解。
    - **个人心得**：最初代码因求区间最大值复杂度高导致 TLE，后通过倒序枚举顺便求最大值优化复杂度。
- **作者：欢黎明陌（4 星）**
    - **关键亮点**：强调实时更新最大值的重要性，思路清晰，使用快读优化输入，代码简洁。
    - **个人心得**：一开始没看到“连续的奶牛”条件，做成贪心导致错误。
- **作者：Rhodoks（4 星）**
    - **关键亮点**：代码简洁，直接展示了动态规划的核心实现，思路明确。

### 重点代码及核心实现思想
#### linyinuo2008 的 AC 代码
```cpp
#include <iostream>
using namespace std;
const int N=10005;
int n,k,s[N];
int f[N];
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    f[1]=s[1];
    for(int i=2;i<=n;i++)
    {
        int mx=-1;
        for(int j=i;j>=max(i-k+1,1);j--)
        {
            mx=max(mx,s[j]);
            f[i]=max(f[i],f[j-1]+mx*(i-j+1));
        }
    }
    cout<<f[n];
    return 0;
}
```
**核心实现思想**：定义 `f[i]` 表示前 `i` 头奶牛最大水平和，通过倒序枚举 `j` 从 `i` 到 `max(i - k + 1, 1)`，在枚举过程中更新区间 `[j, i]` 的最大值 `mx`，并更新 `f[i]` 的值。

#### 欢黎明陌的代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int a[1001000] , ans[1001000];

inline int read(){
    int x = 0 , f = 1;
    char ch = getchar();
    while( ch < '0' || ch > '9' ){
        if( ch == '-' ) f = -1;
        ch = getchar();
    }
    while( ch >= '0' && ch <= '9' ){
         x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 );
         ch = getchar();
    }
    return x * f;
}

int main(int argc , char *argv[])
{
    int n , k;
    cin >> n >> k;
    for(int i = 1;i <= n;i ++) a[i] = read();
    for(int i = 1;i <= n;i ++){
        int maxn = 0;
        for(int j = i;j < min(i+k,n+1);j ++){
            maxn = max( maxn , a[j] );
            ans[j] = max( ans[j] , ans[i-1] + maxn * (j-i+1) );
        }
    }
    cout << ans[n] << endl;
    return 0;
}
```
**核心实现思想**：定义 `ans[i]` 表示前 `i` 头奶牛的最大技能水平和，通过枚举 `j` 从 `i` 到 `min(i + k, n + 1)`，更新区间 `[i, j]` 的最大值 `maxn`，并更新 `ans[j]` 的值。

#### Rhodoks 的代码
```cpp
#include <bits/stdc++.h>
#define LL long long
#define _ 0
using namespace std;

int dp[10010];
int a[10010];
int n,k;

int main()
{
    cin>>n>>k;
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
    {
        int maxa=0;
        for (int j=i;j<min(i+k,n+1);j++)
        {
            if (a[j]>maxa)
                maxa=a[j];
            if (dp[i-1]+(j-i+1)*maxa>dp[j])
                dp[j]=dp[i-1]+(j-i+1)*maxa;
        }
    }
    cout<<dp[n];
    return ~~(0^_^0);
}
```
**核心实现思想**：定义 `dp[i]` 表示对前 `i` 只奶牛分组得到的最大技能水平，通过枚举 `j` 从 `i` 到 `min(i + k, n + 1)`，更新区间 `[i, j]` 的最大值 `maxa`，并更新 `dp[j]` 的值。

### 最优关键思路或技巧
- **动态规划状态定义**：定义 `f[i]` 或类似数组表示前 `i` 头奶牛的最大技能水平和，通过枚举分组情况进行状态转移。
- **区间最大值优化**：在枚举分组时，倒序枚举顺便更新区间最大值，避免单独求区间最大值的 $O(n)$ 复杂度，将总复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 可拓展之处
同类型题或类似算法套路：
- 区间划分问题，如将一个序列划分为若干段，每段有一定的限制条件，求某种最优值。
- 动态规划与区间操作结合的问题，如区间合并、区间修改等。

### 推荐题目
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P2679 [NOIP2015 提高组] 子串](https://www.luogu.com.cn/problem/P2679)

### 个人心得总结
- **欢黎明陌**：做题时要仔细读题，注意题目中的关键条件，否则可能会导致思路错误。
- **linyinuo2008**：在编写代码时要注意复杂度分析，对于复杂度高的部分要及时优化，避免超时。

---
处理用时：46.79秒