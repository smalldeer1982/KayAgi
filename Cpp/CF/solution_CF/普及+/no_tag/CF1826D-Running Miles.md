# Running Miles

## 题目描述

There is a street with $ n $ sights, with sight number $ i $ being $ i $ miles from the beginning of the street. Sight number $ i $ has beauty $ b_i $ . You want to start your morning jog $ l $ miles and end it $ r $ miles from the beginning of the street. By the time you run, you will see sights you run by (including sights at $ l $ and $ r $ miles from the start). You are interested in the $ 3 $ most beautiful sights along your jog, but every mile you run, you get more and more tired.

So choose $ l $ and $ r $ , such that there are at least $ 3 $ sights you run by, and the sum of beauties of the $ 3 $ most beautiful sights minus the distance in miles you have to run is maximized. More formally, choose $ l $ and $ r $ , such that $ b_{i_1} + b_{i_2} + b_{i_3} - (r - l) $ is maximum possible, where $ i_1, i_2, i_3 $ are the indices of the three maximum elements in range $ [l, r] $ .

## 说明/提示

In the first example, we can choose $ l $ and $ r $ to be $ 1 $ and $ 5 $ . So we visit all the sights and the three sights with the maximum beauty are the sights with indices $ 1 $ , $ 3 $ , and $ 5 $ with beauties $ 5 $ , $ 4 $ , and $ 3 $ , respectively. So the total value is $ 5 + 4 + 3 - (5 - 1) = 8 $ .

In the second example, the range $ [l, r] $ can be $ [1, 3] $ or $ [2, 4] $ , the total value is $ 1 + 1 + 1 - (3 - 1) = 1 $ .

## 样例 #1

### 输入

```
4
5
5 1 4 2 3
4
1 1 1 1
6
9 8 7 6 5 4
7
100000000 1 100000000 1 100000000 1 100000000```

### 输出

```
8
1
22
299999996```

# 题解

## 作者：hello_world_djh (赞：31)

**题目大意：**

从序列中选出一段区间 $[l, r]$，再在这个区间内选出三个数 $b_{i_1},b_{i_2},b_{i_3}$，定义这个区间的权值为 $b_{i_1} + b_{i_2} + b_{i_3} - (r - l)$，输出最大的权值。

**sol:**

首先可以注意到一个性质：选的三个数肯定是 $b_l, b_r$ 和区间内的最大值。

因为如果选的数不是左右端点，我们将区间的范围减小只会减小区间的长度而不会影响到 $b_{i_1} + b_{i_2} + b_{i_3}$ 的值，所以一定是更优的。

我们考虑将贡献拆出来，定义 $L(i) = b_i + i$，定义 $R(i) = b_i - i$。

可以发现一个区间的权值：

$$b_l + b_r + b_i - (r - l) = b_l + b_r + b_i - r + l = L(l) + b_i + R(r)$$

考虑枚举 $i$，对于每个 $i$ 的贡献为 $\max_{l < i}{L(l)} + \max_{r > i}{R(r)} + b_i$。

将 $L(i)$ 预处理前缀 $\max$，对 $R(i)$ 预处理后缀 $\max$，对于每个 $i$ 的统计贡献的复杂度就下降到 $O(1)$。

总体复杂度为 $O(n)$。

代码就不放了，大家应该都会写。

---

## 作者：Register_int (赞：5)

枚举中间的路灯，分别找到左右可以造成最大贡献的路灯。这一部分可以通过线性的递推求出，具体方法是在求前缀最大值时减去 $1$ 来对应距离的影响。之后，算出改路灯作为中心点时答案的最大值即可，总复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1e5 + 10;
 
int t, n, a[MAXN];
 
int s[MAXN], pre[MAXN], suf[MAXN], ans;
 
int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), ans = suf[n + 1] = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1] - 1, a[i]);
		for (int i = n; i; i--) suf[i] = max(suf[i + 1] - 1, a[i]);
		for (int i = 2; i < n; i++) ans = max(ans, pre[i - 1] + a[i] + suf[i + 1]);
		printf("%d\n", ans - 2); 
	}
}
```

---

## 作者：daitouzero (赞：4)

# CF1826D 题解

## 题意

对于一个序列，$b$，求出这个式子的最大值：$b_{i1}+b_{i2}+b_{i3}-(r-l)$。

其中 $i_{1},i_{2},i_{3}\in[l,r]$。

## 思路

一个单调栈的好题。

我们先看要求的这个式子 $b_{i1}+b_{i2}+b_{i3}-(r-l)$。

不妨设 $i_{1}<i_{2}<i_{3}$，为了让式子值最大，显然让 $l=i_{1},r=i_{3}$ 最好。

那么有：$b_{i1}+b_{i2}+b_{i3}-(i_{1}-i_{3})$。

移项得：$(b_{i1}-i_{1})+b_{i2}+(b_{i3}+i_{3})$。

这样就把那个恼人的区间长度解决掉了，考虑枚举中间那个 $i_{2}$ 的位置。

至于左边和右边那两项怎么取......你看这个东西在每个位置上 $i$ 的值都是确定的。

那不就是个单调栈左一遍右一遍的事嘛。

### 注意事项

栈要清空！！！

## Code
代码可能比较粪，望见谅。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
template<typename T>
inline void scan(T& x)
{
    x=0;
    T f=0;
    char c=getchar();
    while(c<'0') f|=(c=='-'),c=getchar();
 	while(c>='0') 
	{
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
   	x=f?-x:x;
}
template<typename T,typename ... args>
inline void scan(T& x, args& ... tmp)
{
	scan(x);
	scan(tmp...);
	return;
}
int T,n;
int date[300005];
int stk[300005],top;
int Lmax[300005]/*每个位置（即 i2）对应的 (bi1-i1) 最大值*/;
int Rmax[300005]/*每个位置（即 i2）对应的 (bi3+i3) 最大值*/;
int main()
{
    scan(T);
    while (T--)
    {
        scan(n);
        for (int i=1;i<=n;i++)
            scan(date[i]);
        top=0;//栈要清空！！！
        for (int i=1;i<=n;i++)
        {
            if (top) Lmax[i]=stk[1];/*想清楚，不是取栈顶*/
            while (top&&date[stk[top]]+stk[top]<date[i]+i) 
                top--;
            stk[++top]=i;
        }
        top=0;
        for (int i=n;i>=1;i--)
        {
            if (top) Rmax[i]=stk[1];/*想清楚，不是取栈顶*/
            while (top&&date[stk[top]]-stk[top]<date[i]-i)
                top--;
            stk[++top]=i;
        }
        int ans=-0x7f7f7f7f;
        for (int i=2;i<n;i++)
            ans=max(ans,(date[Lmax[i]]+Lmax[i])+
                        date[i]+
                        (date[Rmax[i]]-Rmax[i]));
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：2)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17376597.html)

## 题意

给你一个长度为 $n$ 的序列 $b$，求下面这个式子的值：

$$
\max_{1 \le l \le i \lt j \lt k \le r \le n}(b_i + b_j + b_k -(r - l))
$$
$n \le 10^5$。

## 思路

官方题解给出的做法使用了单调栈，这里给出一种不用栈的做法。

首先，把题目的柿子优化下。显然，为了尽量地减小 $r - l$ 的值，我们直接令 $i = l$，$k = r$。于是有：

$$
\begin{aligned}
\mathrm{ans} &= \max_{1 \le l \le i \lt j \lt k \le r \le n}(b_i + b_j + b_k -(r - l)) \\
&= \max_{1 \le i \lt j \lt k \le n}(b_i + b_j + b_k - (k - i)) \\
&= \max_{1 \le i \lt j \lt k \le n}(b_j + (b_i + b_k) - (k - i)) \\
&= \max_{1 \le i \lt j \lt k \le n}(b_j + (b_i - (j - i)) + (b_k - (k - j))) \\
&= \max_{1 \lt j \lt n}(b_j + \max_{1 \le i \lt j}(b_i - (j - i)) + \max_{j \lt k \le n}(b_k - (k - j)))
\end{aligned}
$$

然后做法其实就比较显然了。对于每一个 $j \in [2, n - 1]$，把 $b_i - (j - i)$ 与 $b_k - (k - j)$ 的最大值预处理出来，再扫一遍取最大值，就可以得到答案。

暴力预处理是 $O(n^2)$ 的，但其实预处理可以通过 $O(n)$ 递推实现，不妨设 $f_j = \max_{1 \le i \lt j}(b_i - (j - i))$，不难看出 $f$ 单调不减。假设已经得到了 $f_{j - 1}$，由于 $f$ 的单调性，$f_j$ 有两种可能：

1. $f_j$ 对应的 $i$ 与 $f_{j - 1}$ 对应的 $i$ 相同，再减掉一个坐标的增量，即 $f_j = f_{j - 1} - 1$；
2. $f_j$ 对应的 $i$ 为 $j - 1$，则 $f_j = b_{j - 1} - (j - (j - 1)) = b_{j - 1} - 1$。

为什么只可能是这两种决策呢？因为 **$f$ 是具有单调性的**，设 $f_{j - 1}$ 对应的 $i$ 值为 $x$，如果存在 $y \in [1, j - 1)$ 且 $x \neq y$ 使得 $y$ 为 $f_j$ 对应的 $i$ 的话，则有：

$$
\begin{aligned}
b_y - (j - y) &\ge b_x - (j - x) \\
b_y - ((j - 1) - y) &\ge b_x - ((j - 1) - x) \\
b_y - ((j - 1) - y) &\ge f_{j - 1} \\
\end{aligned}
$$

而这与 $x$ 为 $f_{j - 1}$ 对应的 $i$ 相矛盾，因为选择 $y$ 比选择 $x$ 更优。

$\max_{j \lt k \le n}(b_k - (k - j))$ 的预处理同理，同样可以做到 $O(n)$。于是总的时间复杂度为 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  std::vector f(2, std::vector<int>(n));
  for (int i = 1; i < n; i++) {
    f[0][i] = std::max(f[0][i - 1], b[i - 1]) - 1;
  }
  for (int i = n - 2; i >= 0; i--) {
    f[1][i] = std::max(f[1][i + 1], b[i + 1]) - 1;
  }

  int ans = 0;
  for (int i = 1; i < n - 1; i++) {
    ans = std::max(ans, f[0][i] + f[1][i] + b[i]);
  }

  std::cout << ans << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：falling_cloud (赞：1)

简要题意：给定一个数列 $a$，选择一个区间 $[l,r]$ 并在区间中选择 $i_1,i_2,i_3$ 三个数，求 $a_{i_1}+a_{i_2}+a_{i_3}-(r-l)$ 的最大值。 

首先假定 $i_1<i_2<i_3$，出于让 $a_{i_1}+a_{i_2}+a_{i_3}-(r-l)$ 最大的考虑，一定有 $i_1=l,i_3=r$，因为如果缩小区间就选不到这两个数了，而添加区间又会减小无意义的贡献。

这时考虑将**贡献下发**来让三个数的选择独立，那么设 $b_i=a_i+i,c_i=a_i-i$，这时的问题变为选定 $c_{i_1}+a_{i_2}+b_{i_3}$，使其值最大，这时记录前 $i$ 个数中最大的 $c_{i}$ 值，最大的 $c_{i}+b_{j}(i<j)$ 值，最大的 $c_{i}+a_{j}+b_{k}(i<j<k)$ 值，依次转移即可。时间复杂度 $O(n)$

代码中按反序转移的是为了保证不会出现同一个数被选两次的情况。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define PD if(flag)	cout<<"Yes"<<endl;  else cout<<"No"<<endl
using namespace std; 
const int N = 1e5 + 5; 
const int M = 1e9 + 7;
int a[N],b[N],c[N];
void solve()
{
	int i,j,n,m,k,la=0,r,x=0,y,w,sum=0,ans=0,Max=0,Min=1e9+5,key=0;
	bool flag=true;
	cin>>n;
	for(i=1;i<=n;i++)	cin>>a[i],b[i]=a[i]+i,c[i]=a[i]-i;
	la=b[1];
	for(i=2;i<=n;i++)
	{
		ans=max(ans,sum+c[i]);
		
		sum=max(sum,a[i]+la);
		
		la=max(la,b[i]);
	}
	cout<<ans<<endl;
} 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int Ti;
	for(cin>>Ti;Ti;Ti--)
		solve();
	return 0;
}

```

---

