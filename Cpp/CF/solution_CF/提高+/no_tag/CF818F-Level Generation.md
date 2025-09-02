# Level Generation

## 题目描述

Ivan is developing his own computer game. Now he tries to create some levels for his game. But firstly for each level he needs to draw a graph representing the structure of the level.

Ivan decided that there should be exactly $ n_{i} $ vertices in the graph representing level $ i $ , and the edges have to be bidirectional. When constructing the graph, Ivan is interested in special edges called bridges. An edge between two vertices $ u $ and $ v $ is called a bridge if this edge belongs to every path between $ u $ and $ v $ (and these vertices will belong to different connected components if we delete this edge). For each level Ivan wants to construct a graph where at least half of the edges are bridges. He also wants to maximize the number of edges in each constructed graph.

So the task Ivan gave you is: given $ q $ numbers $ n_{1},n_{2},...,n_{q} $ , for each $ i $ tell the maximum number of edges in a graph with $ n_{i} $ vertices, if at least half of the edges are bridges. Note that the graphs cannot contain multiple edges or self-loops.

## 说明/提示

In the first example it is possible to construct these graphs:

1. $ 1-2 $ , $ 1-3 $ ;
2. $ 1-2 $ , $ 1-3 $ , $ 2-4 $ ;
3. $ 1-2 $ , $ 1-3 $ , $ 2-3 $ , $ 1-4 $ , $ 2-5 $ , $ 3-6 $ .

## 样例 #1

### 输入

```
3
3
4
6
```

### 输出

```
2
3
6
```

# 题解

## 作者：Maureen0124 (赞：3)

## 题意
对于一个 $n$ 个点 $m$ 条边的简单无向图，在满足至少 $\lceil \frac{m}2 \rceil$ 条边是桥的这个条件下，求 $m$ 的最大值。
## 思路
(注：该题解思路与[官方题解](https://codeforces.com/blog/entry/52991)思路大致相同，但会进行翻译和补充，希望能帮助到~~不想读英文题解的~~大家)。

- 首先~~容易~~想到最优解是先构建一个 2 - 边连通分量（以最大化边数），设该分量由 $k$ 个点组成。则还剩下 $n - k$ 个点，将这 $n - k$ 个点分别用一条边连接到分量上，这 $n - k$ 条边就是这个图的所有桥（因为 2 - 边连通分量中没有桥）。
- 又因为题目要求至少 $\lceil \frac{m}2 \rceil$ 条边是桥，所以总边数 $\le 2 \times (n - k)$ 。又因为 2 - 边连通分量中的边数的最大值 $= \frac{k(k - 1)}2$ 。因此，总边数 $f(k) = n - k + \min(n - k, \frac{k(k - 1)}2)$ 。
- 进一步分析 $f(k)$ 的单调性：易发现当 $k$ 增大时， $\frac{k(k - 1)}2$ 单增， $n - k$单减。所以存在一个 $k_0$ ，使得，当 $k \le k_0$ 时: $\frac{k(k - 1)}2 \le n - k$ ； 当 $k > k_0$ 时， $\frac{k(k - 1)}2 > n - k$。
- 得出结论： $f(k)$ 在 $[1, k_0]$ 上严格递增，在 $[k_0 + 1, n]$ 上严格递减。
- 三分 2 - 边连通分量的点数 $k$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;

ll cal(ll x){   //n-x个桥的图最多多少条边
    return min(n - x, x * (x - 1) / 2) + n - x;
}

ll int_ter(ll l, ll r){
	while(r - l > 3){   //三分2-边连通分量的点数
		ll lmid = l + (r - l) / 3;
		ll rmid = r - (r - l) / 3;
		if(cal(lmid) < cal(rmid)) l = lmid;
		else r = rmid;
	}
	ll res = l;
	for(ll i = l; i <= r; i++)
		if(cal(res) < cal(i)) res = i;
	return res;
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    for( ; T-- && cin >> n; )
        printf("%lld\n", max(n - 1, cal(int_ter(1, n - 1))));
    return 0;
}
```

---

## 作者：ARIS2_0 (赞：1)

### 思路

首先连通图肯定优于不连通，证明显然。

于是我们可以在一条长度为 $n$ 的链上加边，考虑如何加边可以使少掉的桥最小。

首先加第一条边时至少会少两座桥，加第二条边时至少会少一座桥。

我们设链上的 $n-1$ 条边为 $(i,i+1)(1\le i<n)$，加的第一条边为 $(1,3)$，第二条边为 $(1,4)$。

发现加完 $(1,4)$ 后，有 $(2,4)$ 这条加了不会减少桥个数的边；

同理，加完 $(1,5)$ 后，有 $(2,5),(3,5)$ 两条加了不会减少桥个数的边。

以此类推，我们可以做出一个表格：



|加的边数|（相比加边之前）少的桥的个数|
|:-:|:-:|
|1|2|
|2|1|
|3|0|
|4|1|
|5|0|
|6|0|
|7|1|
|8|0|
|9|0|
|10|0|

可以证明这是最优的加边方案。

那么，如果我们少了 $d+2$ 座桥，则我们加的边数在 $[\frac{d(d+1)}{2}+1,\frac{(d+1)(d+2)}{2}]$ 之间，则 $d$ 需要满足式子：

$$2(n-d-3)\ge n+\frac{d(d+1)}{2}$$

拆开移项，可得：

$$d^2+5d+(12-2n)\le 0$$

根据求根公式可得 $d$ 的最大解为 $\lfloor\frac{\sqrt{8n-23}-5}{2}\rfloor$。

求出 $d$ 后，可得最大的边数为 $\min(2\times (n-d-3),n-1+\frac{(d+1)(d+2)}{2})$（分别是因为桥个数的限制，和少 $d+2$ 座桥最多能加的边的限制），直接输出这个式子即可。

时间复杂度 $O(T)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;cin>>T;
    while(T--){
        int n;cin>>n;
        if(n<=5)cout<<n-1<<"\n";
        else{
            int d=(sqrtl(8*n-23)-5)/2,maxs=n-1+(d+1)*(d+2)/2;
            cout<<min(maxs,2*(n-d-3))<<"\n";
        }
    }
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

一个单调性是显然的：如果边数为 $x$ 可以满足条件，则边数为 $x-1$ 也可以满足条件。就把边数为 $x$ 的时候随便去掉一条边就可以了。

二分这个边数 $m$，可以知道桥的数量。不妨把割边去掉，就是 $cnt=\left\lceil\dfrac m2\right\rceil+1$ 个连通块。如果第 $i$ 个连通块的点的数量为 $a_i$，则 $\sum\limits_{i=1}^{cnt}a_i=x$，要求 $\sum\limits_{i=1}^{cnt}\dfrac{a_i(a_i-1)}2\ge m-cnt-1$。构造是 $a_1=x-cnt+1$，$a_2=a_3=\cdots=a_{cnt}=1$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)
using namespace std;
int l, r, n, T, ans;
inline bool check(int m){
    int bri = m + 1 >> 1;
    int res = n - bri;
    return res * (res - 1) / 2 >= m - bri;
}
signed main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%lld", &T);
    while(T--){
        scanf("%lld", &n);
        l = 1, r = (n - 1) * 2, ans = 0;
        while(l <= r){
            if(check(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### Description.
略

### Solution.
首先有一个显然的结论，答案构成肯定是一棵树，其中一个节点替换成一个不完全的团。  
这样肯定最优，至于为什么不完全，因为还有割边数的限制。  

所以，我们设不完全团有 $x$ 个节点（总节点数为 $n$。  
那答案就是 $\min(\frac{x(x-1)}2,n-x)+n-x$。  
$n-x$ 表示树边数量，$\frac{x(x-1)}2$ 表示团边数。  
相当于我们要最大化这个式子。  

化简一下就是 $n+\min(\frac{x^2-3x}2,n-2x)$。  
当 $x$ 较小时直接暴力处理，否则在 $x$ 较大时，前式递增后式递减。  
这样形式的式子肯定在相交处取最大值。  
就有 $\frac{x(x-1)}2=n-x$，有 $x^2+x-2n=0$。  
直接解一下方程就行了。  
因为 $x\in \mathbb N$，就直接带 $[x]$ 和 $[x]+1$ 算一下就行了。  
复杂度 $O(T)$

### Coding.
```cpp
if(n<=10)
{
	for(ll i=1;i<=n;i++) rs=max(rs,min(i*(i-1)/2,n-i)+n-i);
	printf("%lld\n",rs);return;
}
ll x=(-1+sqrt(1+8*n))/2;
printf("%lld\n",max(min(x*(x-1)/2,n-x)+n-x,min(x*(x+1)/2,n-x-1)+n-x-1));
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意简述：给定 $n$ 个点，求最多的边数，使得桥的数量大于等于 $\left\lceil\dfrac{m}{2}\right\rceil$。

明显这个的询问与点数太大，模拟什么的算法复杂度过高，所以我们大胆猜测这是一道结论题。考虑构造。
## 分析。
提供一个可能比较巧妙的思路。

首先，考虑到整张图一共**只有一个**双连通分量，所以如果有两个双连通分量，完全可以通过同构结合成一个双连通分量。而从双连通分量延伸的所有边都是桥，看到连通，所以不妨假设它就是一条链。那么对于这条链来说，有 $n-x$ 条边，其右边的 $x$ 个点这样的连接情况，对于所有边，它不是桥，而是单纯的一条边。这样不是桥的个数最多有 $\dfrac{x\left(x-1\right)}{2}$ 个。因为要求桥的数量是边数量的一半以上，所以最多有 $n-x$ 条边。

所以我们考虑构造一个这么个图。现在假设我们选 $x$ 个点，则其最优边数必定是 $n-i+\min\left(n-i,\dfrac{i\left(i-1\right)}{2}\right)$ 个，即选择当前是否建边，否则建桥。

看到这个式子，我们不难想到转化，将 $n-i$ 移进去，则得到 $\min\left(\left(n-i\right)+\left(n-i\right),\dfrac{i\left(i-1\right)}{2}+\left(n-i\right)\right)=\min\left(2n-2i,\dfrac{i^2-i}{2}+n-i\right)$ 的形式。

显然其中 $n$ 不变，故左侧是个减函数，而右侧显然当 $i\geq 1$ 时 $i^2$ 的增速比 $i$ 快，所以左边的分数值越来越大，而后边没有办法跟上增速，所以可以近似地看成是增函数。发现该式子有单调性的。此时显然可以二分，然后有一个三分，就可以解决。

但是我们不着急下手，我们看到最大值，那我们就去考虑这个近似于增函数的式子的最大值。所以令 $n-i=\dfrac{n\left(n-1\right)}{2}$ 解方程即可。考虑到答案必然大于零，所以保留一个即可。这个方程并不难解，读者可以化成一元二次方程然后套公式求解。

找到的最大值即为答案。但是我们考虑到其中开根号的情况，其真正的的解也可能直接是 $x-1$ 所以特判一下即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int t,n,m;
long long sum,ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		sum=(long long)n*8+1;
	    sum=(sqrt(sum)-1)/2+1;
		for(int i=max(1ll,sum-1);i<=min((long long)n,sum);i++){
			long long cd=min((long long)n-i,1ll*i*(i-1)/2);
			ans=max(ans,n-i+cd);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问。可以在评论区提出，我会尽力解答的。

---

## 作者：xzggzh1 (赞：0)

题意：

对于 $n$ 个点 $m $ 条边的简单无向图，如果有至少 $ \lceil\frac{m}{2}\rceil$ 条边是桥，则这个图是 “绝妙的” 。$q \ \ (q\le 10^5)$ 次询问，求出 $x \ \ (x\le 2\times 10^9)$ 个点的 “绝妙的” 图中，最多有多少条边。

---

由于边双连通分量中不存在桥，然而我们又想让桥相对于所有边最多。所以我们可以直接贪心的考虑就在一条链上只搞一个边双联通分量。

设边双联通分量里面有 $x$ 条边，那么答案将会是 

$$\min ( \frac {x(x-1)} {2} +n-x, 2(n-x))$$ 

最后输出所有 $x$ 里面答案最大的，化简之后可知左边的东西单调增，右边的东西单调减，所以可以二分交点，算出最值。

注意：也许交点不是整数所以要在二分值附近多试一个点。

核心代码：(式子以化简)

```cpp
#define int long long 
signed main(){
	int Q=read();
	while( Q--){
		int n = read(), mid,ans = n-1,L = 2, R = n-1;
		while(L<=R){
			mid=(L+R)>>1;
			if(mid*(mid-1ll)/2+(n-mid)<=2ll*(n-mid))L = mid+1;
			else R = mid-1;
		}
		mid=L-1;
		ans=max(ans,min(mid*(mid-1ll)/2+(n-mid),2ll*(n-mid)));
		mid=L;
		ans=max(ans,min(mid*(mid-1ll)/2+(n-mid),2ll*(n-mid)));
		printf("%lld\n",ans);
	}
}
```

---

