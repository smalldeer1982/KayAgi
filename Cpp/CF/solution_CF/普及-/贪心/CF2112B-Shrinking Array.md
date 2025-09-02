# Shrinking Array

## 题目描述

序列 $b$ 是美丽的，当且仅当 $b$ 的长度至少为 $2$ 且存在一个位置 $i$ 使得 $\vert b_i-b_{i+1}\vert\le 1$。 

给你一个序列 $a$，你可以执行以下操作直到其长度少于 $2$。
- 选择 $a$ 中两个相邻的位置 $i$ 和 $i+1$。
- 选择一个整数 $x$ 使得 $\min(a_i,a_{i+1})\le x\le \max(a_i,a_{i+1})$。
- 删除 $a_i$ 和 $a_{i+1}$，并在它们的位置插入一个 $x$。这会使得 $a$ 的长度减少 $1$。

计算最少需要多少次操作使得 $a$ 变得美丽，或报告这是不可能的。

## 说明/提示

**样例解释**

对于第一组数据，$\vert a_2-a_3\vert=\vert 3-3\vert=0$，因此 $a$ 是美丽的。

对于第二组数据，执行操作会让 $a$ 的长度小于 $2$，所以不可能使得 $a$ 美丽。

对于第三组数据，选择 $a_1,a_2$ 和 $x=2$，操作后的序列 $[2,3,7]$ 是美丽的。

对于第四组数据，选择 $a_2,a_3$ 和 $x=3$，操作后的序列 $[1,3,2]$ 是美丽的。


## 样例 #1

### 输入

```
4
4
1 3 3 7
2
6 9
4
3 1 3 7
4
1 3 5 2```

### 输出

```
0
-1
1
1```

# 题解

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18962372)

很妙的一道题。

发现修改操作只能修改成两数的中间值，考虑把它画在一个**折线图**上考虑。

在折线图上，显然如果我们找到了一个**单峰 / 单谷**，那么一定可以在一步内把数组变美丽，因为将单峰 / 单谷的一侧直接变得与另一侧相等即可。

如果一张折线图上没有单峰 / 单谷，就证明这个函数是**单调的**，此时如果原来就不是美丽数组，那么此时也不可能变成美丽数组，因为折线图上只能将两个点合并为一个中间点。

就此判断即可，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=1005,inf=0x3f3f3f3f;
int n,a[N],ans;
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    ans=inf;
    for(int i=1;i<n;i++)
    {
        if(a[i]==a[i+1]||abs(a[i+1]-a[i])==1)ans=min(ans,0);
        if(i>1&&a[i]>a[i-1]&&a[i]>a[i+1])ans=min(ans,1);
        if(i>1&&a[i]<a[i-1]&&a[i]<a[i+1])ans=min(ans,1);
    }
    if(ans>=inf)cout<<-1<<'\n';
    else cout<<ans<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
你得到了一个长度为 $n$ 的数组，你要按以下方法使得这个数组长度至少为 $2$ 且有两个相邻的数的差小于 $2$：

* 选择一个数 $i(1\le i<n)$，删掉 $a_i$ 和 $a_{i+1}$，在原来的位置上添加一个比 $\min(a_i,a_{i+1})$ 大，比 $\max(a_i,a_{i+1})$ 小的数。
## 题目思路
我们可以先判断原数组是否是满足要求，如果是答案为 $0$。

我们发现如果有三个相邻的数 $x,y,z$，满足 $x<y,y>z$ 或 $x>y,y<z$ 则可以通过一次操作删掉 $y$ 并把 $x,z$ 中的一个数变为与另一个相等的数。

反之如果不满足这一个条件，原数组为一个递减或递增的数组，则不能满足要求。所以按上面判断，如果有输出 $1$ 否则输出 $-1$。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1010;

int a[kMaxN], t, n, ans;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--;) {
    cin >> n, ans = -1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
      ans = (abs(a[i] - a[i + 1]) <= 1 ? 0 : ans);
    }
    for (int i = 2; i < n; i++) {
      ans &= (a[i - 1] < a[i] && a[i] > a[i + 1]) || (a[i - 1] > a[i] && a[i] < a[i + 1]) ? 1 : -1;
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

我们发现，操作之后的数一定在两个数中的最小值与最大值之间，又因为我们只能对相邻的进行操作，多次操作相当于对一个连续子序列操作。

因此我们可以将原题意转化为：选取一个最短的区间 $[l,r]$，设 $A = \min _ {i = l} ^ {r} a _ i,B = \max _ {i = l} ^ {r} a _ i$，满足 $a _ {l - 1} \in [A - 1,B + 1]$ 或 $a _ {r + 1} \in [A - 1,B + 1]$，我喜欢 DS 力大砖飞所以用 ST 表维护区间最小与区间最大值，答案就是 $r - l$。

管理说要代码就贴个代码吧。

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 1e3 + 5;
int T;
int n,a[MAXN],stMin[12][MAXN],stMax[12][MAXN];
inline int lg(int x)
{return 63 ^ __builtin_clzll(x);}
inline void initST()
{
    for(int i = 1;i <= lg(n);i++)
    {
        for(int j = 1;j + (1 << i) - 1 <= n;j++)
            stMin[i][j] = min(stMin[i - 1][j],stMin[i - 1][j + (1 << (i - 1))]),stMax[i][j] = max(stMax[i - 1][j],stMax[i - 1][j + (1 << (i - 1))]);
    }
}
inline int queryMin(int l,int r)
{
    int T = lg(r - l + 1);
    return min(stMin[T][l],stMin[T][r - (1 << T) + 1]);
}
inline int queryMax(int l,int r)
{
    int T = lg(r - l + 1);
    return min(stMax[T][l],stMax[T][r - (1 << T) + 1]);
}
inline bool belong(int x,int l,int r)
{return (x >= l && x <= r);}
inline void Solve()
{
    cin >> n;
    for(int i = 1;i <= n;i++)
        cin >> a[i],stMin[0][i] = stMax[0][i] = a[i];
    initST();
    int ans = 0x3f3f3f3f3f3f3f3f;
    for(int l = 1;l <= n;l++)
    {
        for(int r = l;r <= n;r++)
        {
            if(l - 1 >= 1 && (belong(a[l - 1] + 1,queryMin(l,r),queryMax(l,r)) || belong(a[l - 1],queryMin(l,r),queryMax(l,r)) || belong(a[l - 1] - 1,queryMin(l,r),queryMax(l,r))))
                ans = min(ans,r - l + 1);
            if(r + 1 <= n && (belong(a[r + 1] + 1,queryMin(l,r),queryMax(l,r)) || belong(a[r + 1],queryMin(l,r),queryMax(l,r)) || belong(a[r + 1] - 1,queryMin(l,r),queryMax(l,r))))
                ans = min(ans,r - l + 1);
        }
    }
    cout << ((ans == 0x3f3f3f3f3f3f3f3f) ? -1 : (ans - 1)) << '\n';
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
        Solve();
}
```

---

