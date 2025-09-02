# Delivery Club

## 题目描述

Petya and Vasya got employed as couriers. During the working day they are to deliver packages to $ n $ different points on the line. According to the company's internal rules, the delivery of packages must be carried out strictly in a certain order. Initially, Petya is at the point with the coordinate $ s_{1} $ , Vasya is at the point with the coordinate $ s_{2} $ , and the clients are at the points $ x_{1},x_{2},...,x_{n} $ in the order of the required visit.

The guys agree in advance who of them will deliver the package to which of the customers, and then they act as follows. When the package for the $ i $ -th client is delivered, the one who delivers the package to the $ (i+1) $ -st client is sent to the path (it can be the same person who went to the point $ x_{i} $ , or the other). The friend who is not busy in delivering the current package, is standing still.

To communicate with each other, the guys have got walkie-talkies. The walkie-talkies work rather poorly at great distances, so Petya and Vasya want to distribute the orders so that the maximum distance between them during the day is as low as possible. Help Petya and Vasya to minimize the maximum distance between them, observing all delivery rules.

## 说明/提示

In the first test case the initial distance between the couriers is $ 10 $ . This value will be the answer, for example, Petya can perform both deliveries, and Vasya will remain at the starting point.

In the second test case you can optimally act, for example, like this: Vasya delivers the package to the first customer, Petya to the second and, finally, Vasya delivers the package to the third client. With this order of delivery, the distance between the couriers will never exceed $ 1 $ .

In the third test case only two variants are possible: if the delivery of a single package is carried out by Petya, the maximum distance between them will be $ 5-2=3 $ . If Vasya will deliver the package, the maximum distance is $ 4-2=2 $ . The latter method is optimal.

## 样例 #1

### 输入

```
2 0 10
5 6
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 2 1
3 4 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 4 5
2
```

### 输出

```
2
```

# 题解

## 作者：5k_sync_closer (赞：15)

提供一个代码短，常数小的二分 + `set` 写法。
# 思路
>最长距离最短

二分最长距离。考虑如何 `check`。

根据题意，完成任务 $x_i$ 时，一定有一个快递员在 $x_i$。

则另一个快递员一定在 $[x_i-mid,x_i+mid]$ 之间，否则 `check` 失败。

用 `set` 维护另一个快递员的可能位置，依次考虑 $x_i$，删除 $[x_i-mid,x_i+mid]$ 之外的元素。

若此时 `set` 为空，则 `check` 失败，否则将 $x_i$ 加入 `set`，继续考虑 $x_{i+1}$。
# 代码
考虑怎样删除 $[x_i-mid,x_i+mid]$ 之外的元素。现有题解都是直接暴力扫 `set`，比较麻烦。

我们知道，`set` 自带 `lower_bound` 和 `upper_bound` 函数。

我们还知道，`set` 的 `erase` 函数可以删除一段左闭右开的区间。

所以 
```cpp
s.erase(s.begin(), s.lower_bound(a[i] - m));
s.erase(s.upper_bound(a[i] + m), s.end());
```
即可完成删除操作。
```cpp
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, x, y, l, r = 1e9, m, q, a[100050];
bool C(int m)
{
	set<int> s{x, y};for(int i = 1;i <= n;++i)
	{
		s.erase(s.begin(), s.lower_bound(a[i] - m));
		s.erase(s.upper_bound(a[i] + m), s.end());
		if(s.empty()) return 0;s.insert(a[i]);
	}
	return 1;
}
int main()
{
	scanf("%d%d%d", &n, &x, &y);l = abs(x - y);
	for(int i = 1;i <= n;++i) scanf("%d", a + i);
	while(l <= r) if(C(m = l + r >> 1)) r = m - 1,
	q = m;else l = m + 1;return printf("%d", q), 0;
}
```


---

## 作者：pufanyi (赞：14)

CF如此多的二分+贪心，但我就是想不出来……

首先二分答案。

难点是在如何判断答案合法。

显然正着做是不行的，所以我们考虑倒着做。

我们考虑现在二分的距离为$L$，枚举到第$i$步，如果两个快递员中至少有一个的起点出现在$[l_i,r_i]$的范围内，且两个快递员相距不超过$L$，那么是合法的。

现在考虑从$[l_{i+1},r_{i+1}]$向$[l_{i},r_{i}]$转移。

显然，两个快递员中只有一个快递员动，而不动的那个快递员必须已经在$[x_i-L,x_i+L]$。

我们考虑下面两种情况：

如果$x_i\in[l_i,r_i]$，那么只要有一个快递员已经在$[x_i-L,x_i+L]$里即可，我们让另一个快递员走到$x_i$，而因为$x_i\in[l_i,r_i]$，所以这位快递员在$[l_i,r_i]$里了，且两个快递员相距不超过$L$。所以$l_i=x_i-L, r_i=x_i+L$。

如果$x_i\not\in [l_i,r_i]$，考虑不动的快递员，首先必须在$[x_i-L,x_i+L]$里，又由于$x_i\not\in[l_i,r_i]$，故他也必须在$[l_i,r_i]$里，而到$x_i$的那个快递员没有什么特殊的要求了。所以$l_i=\max(l_{i+1},x_i-L),r_i=\min(r_{i+1},x_i+L)$。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;

int n, s1, s2;
int aa[maxn];

inline bool check(int x)
{
    int l = -inf, r = inf;
    for(int i = n; i; --i)
    {
        if(l <= aa[i] && aa[i] <= r)
            l = aa[i] - x, r = aa[i] + x;
        else
            l = max(l, aa[i] - x), r = min(r, aa[i] + x);
    }
    return (l <= s1 && s1 <= r) || (l <= s2 && s2 <= r);
}

int main()
{
    scanf("%d%d%d", &n, &s1, &s2);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &aa[i]);
    int l = abs(s1 - s2), r = inf;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
```

---

## 作者：NinT_W (赞：4)

# CF875E Delivery Club 

## 杂项

[传送门](https://www.luogu.com.cn/problem/CF875E)

## 题意

> 有两个人，初始位置给出，在n个位置上有n个任务，他俩去一个人就行，要求最小化两者之间的产生的最大距离

## 分析
一眼二分答案，然后check假了，正推无法寻求到正解，所以我们只能倒推

我们用区间 $ [l,r] $ 表示两人中一人在 $ x_i $ 的位置，另一人所在位置的合法范围，然后开始从区间 $ i+1 $ 向区间 $ i $ 倒推，最后 $ s1 $ 或 $ s2 $ 中的一处在区间内即可（另一个人在 $x_1$ 处）

存在两种情况

1. $ x_i $ 位于现在的区间（区间 $ i+1 $ ）内，差不多是这个样子

![](https://cdn.luogu.com.cn/upload/image_hosting/4ri2lzmh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


直接让蓝点位置的人过去就行，$ x_i+1 $ 就在区间 $ [x_i-mid,x_i+mid] $ 内，区间 $ i $ 直接就可以变为 $ [x_i-mid,x_i+mid] $

2. $ x_i $ 不在现在的区间内，那应该满足这个样子

![](https://cdn.luogu.com.cn/upload/image_hosting/6o0me3wv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

让 $ x_{i+1} $ 位置的人去 $ x_i $ ，然后另一个人在两个区间的交集即可，新区间就是两区间的交集

然后就这样更新出原始区间，判断 $ s1 $、$ s2 $ 与区间的关系即可

AC code

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<climits>
#include<algorithm>

using namespace std;

const int INF=1e9;

const int maxn=100010;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

int n,s1,s2;
int x[maxn];

bool check(int k)
{
	int l=-INF,r=INF;
	for(int i=n;i>=1;i--)
	{
		if(l<=x[i] && x[i]<=r)
		{
			l=x[i]-k,r=x[i]+k;
		}
		else
		{
			l=max(l,x[i]-k);
			r=min(r,x[i]+k);
		}
	}
	return ((l<=s1 && s1<=r) || (l<=s2 && s2<=r));
}

int main()
{
	n=read(),s1=read(),s2=read();
	for(int i=1;i<=n;i++) x[i]=read();
	
	int l=abs(s1-s2),r=INF;
	
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	
	cout<<l;
	
	return 0;
}
```

---

## 作者：Alkaid_Star (赞：3)

本文同步发表在[我的WordPress博客](https://www.encounter.cool/index.php/2021/01/06/cf875e-solution/)。

[题面(Luogu)](https://www.luogu.com.cn/problem/CF875E)

### 题目大意：

> 两个快递员初始在 $s1$ , $s2$ 位置，给定 $n$ 个位置，每次从两人中选择一人移动到给定位置，求两人最大距离最小值。
数据范围： $ 1\le n \le 10^5 $

### 解题思路：
从最大距离最小我们显然可以看出这是 **二分** （ $O(n^2)$ 的 $dp$ 我就不说啦，相信来做紫题的各位都会）。

我们外层二分答案，对于每次 $check$ 考虑用 $f[i][j]$ 表示前 $i$ 个订单，另外一个人在 $j$ 的方法是否可行（邮递员问题，通常保存不同邮递员的位置，都是经验），也就是说 $f[i][j]$ 是一个为 $0$ 或 $1$ 的值。

那么我们就有：$dp[i+1][j]=dp[i+1][j] or dp[i][j]$ (满足 $|a[i]-a[i+1]| \le mid $)，$dp[i+1][i]=dp[i+1][i] or dp[i][j] $ (满足 $|a[j]-a[i+1]| \le mid $)  。

我们考虑如何优化它。一种可行的方法是利用 $set$ 减少状态数。当然，这道题用线段树也可以，在这里就不讲了，有兴趣的同学可以自己思考。

由于上面转移方程的限制，我们可以在 $set$ 中维护满足条件的状态，每次递推 $a[i]$ 时判断是否有满足的状态可以转移过来（即 $set$ 为不为空）。这样因为每次 $check$ 每个值只会进出 $set$ 一次，一次 $check$ 的均摊复杂度为 $O(n log n)$，算上二分的 $O(log w)$ (w 为值域） ，总复杂度为 $O(n log n log w)$ 。
### Code（带注释）：
```C++
#include<bits/stdc++.h>
using namespace std;
const int inf=1000000005;
const int N=100005;

int n,Startx,Starty,ans;
int a[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline bool check(int mid){
	set <int> s;
	s.insert(Startx);		//插入初始的值
	s.insert(Starty);
	for (int i=1;i<=n;i++){
		while ((!s.empty()) && (abs(*s.begin()-a[i])>mid))		//从左侧删去 set 中的不合法状态
			s.erase(s.begin());
		while ((!s.empty()) && (abs(*(--s.end())-a[i])>mid))	//从右侧删去 set 中的不合法状态
			s.erase((--s.end()));		//注意此处 set 最右端的值为 *(--s.end()) 而不是 *s.end() 
		if (s.empty()) return false;
		s.insert(a[i]);		//此时把 a[i] 这个点塞入 set 中，等待下一轮的判断（如果 a[i] 不合法会被删除掉）
	}
	return true;
}

int main(){
	//freopen("CF875E.in","r",stdin);
	//freopen("CF875E.out","w",stdout);
	n=read(),Startx=read(),Starty=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	int l=abs(Startx-Starty),r=inf;		//注意这里 l 值的设定为满足初始距离的 (Startx-Starty)
	while (l<=r){
		int mid=(l+r)>>1;
		if (check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```
##### 这么详细的博客，不点个赞吗（小声）。

---

## 作者：lgswdn_SA (赞：2)

感觉这道题稍微想想就能得到一个很简单的线段树维护 DP 的解（当然由于其操作，用 set 也是可以维护的）。

首先 Binary Search.

然后 $f_i(j)$ 表示前 $i$ 个用户，然后一个在 $x_i$ 另一个在 $j$ 是否可行。

考虑如何转移。设二分的答案为 $k$。

如果 $|x_i-x_{i+1}|\le k$，则有 $f_i(j)\to f_{i+1}(x_i)$。

如果 $|j-x_{i+1}|\le k$，则有 $f_i(j)\to f_{i+1}(j)$。

考虑用线段树维护 $f$，则需支持：全局的 $f$ 的 or 和，区间清零（第二种转移时 $[0,x_{i+1}-k-1],[x_{i+1}+k+1,M]$ 需要清零，其中 $M$ 为最大的和），然后单点更新（第一种转移）。

此时你可以用动态开点线段树动态维护了。但是实际上还可以做的更加简便，更好。

考虑每一层 $f$ 的更新，最多只会多出一个 $0$，于是线段树更新的时候，我们最多只会有均摊 $O(1)$ 总计 $O(n)$ 个点需要被清零，于是区间更新的时候我们暴力下放，如果区间中全是 $0$ 就直接退出，这样一次区间清零的均摊复杂度是 $O(\log M)$ 的。

加上二分，我们有总复杂度为 $O(n\log^2 M)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
typedef pair<int,int> pii;
typedef vector<int> vi;

long long read() {
	long long res=0, w=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) {res=res*10+c-48, c=getchar();}
	return res*w;
}

const int N=1e5+9;

int n,s1,s2,x[N],mx;

namespace SegT {
	int tot=1,root=1,f[N*128],ls[N*128],rs[N*128];
	void clear() {
		rep(i,1,tot) f[i]=0, ls[i]=0, rs[i]=0; tot=1;
	}
	void mdf(int &p,int l,int r,int x,int z) {
		if(!p) p=++tot; if(l==r) {f[p]=z; return;} int mid=l+r>>1;
		if(x<=mid) mdf(ls[p],l,mid,x,z); else mdf(rs[p],mid+1,r,x,z);
		f[p]=f[ls[p]]|f[rs[p]];
	}
	void cl(int p,int l,int r,int x,int y) {
		if(x>y||(!p)||(!f[p])) return; if(l==r) {f[p]=0; return;} int mid=l+r>>1;
		if(y<=mid) cl(ls[p],l,mid,x,y); else if(x>mid) cl(rs[p],mid+1,r,x,y);
		else cl(ls[p],l,mid,x,mid), cl(rs[p],mid+1,r,mid+1,y);
		f[p]=f[ls[p]]|f[rs[p]];
	}
}
using SegT::root; using SegT::clear; using SegT::mdf; using SegT::cl; using SegT::f;

bool calc(int k) {
	clear();
	mdf(root,0,mx,s1,1); mdf(root,0,mx,s2,1);
	rep(i,0,n-1) {
		int l=-k+x[i+1], r=k+x[i+1]; l=max(l,0), r=min(r,mx);
		int rs=f[root];
		cl(root,0,mx,0,l-1), cl(root,0,mx,r+1,mx);
		if(i&&abs(x[i]-x[i+1])<=k&&rs) mdf(root,0,mx,x[i],1); 
	}
	return f[root];
}

signed main() {
	n=read(), s1=read(), s2=read(); mx=max(s1,s2);
	rep(i,1,n) x[i]=read(),mx=max(mx,x[i]);
	int l=abs(s1-s2),r=mx,ans=-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(calc(mid)) r=mid-1, ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：decoqwq (赞：2)

先二分答案，考虑每次新加入一个位置，将一个人移动到这个位置，一定需要另一个人上次结束的位置到这里的距离小于这个答案，用 $set$ 维护一下可以存在的位置集合，每次加入一个新的位置，就弹出所有距离这个点距离大于这个答案的位置，如果 $set$ 空了就不行，因为每次每个点最多出入 $set$ 一次，所以单次 $check$ 复杂度 $O(nlogn)$ ，总时间复杂度 $O(nlog^2n)$

```cpp
/*  Never Island  */
/*deco loves Chino*/
#include <bits/stdc++.h>
using namespace std;
int n,a[100010],s1,s2;
int check(int num)
{
	set<int> st;
	st.insert(s1),st.insert(s2);
	for(int i=1;i<=n;i++)
	{
		while(!st.empty()&&abs(a[i]-*st.begin())>num)//最小的位置
		{
			st.erase(st.begin());
		}
		while(!st.empty()&&abs(a[i]-*prev(st.end()))>num)//最大的位置
		{
			st.erase(prev(st.end()));
		}
		if(st.empty())
		{
			return 0;
		}
		st.insert(a[i]);
	}
	return 1;
}
int main()
{
	cin>>n>>s1>>s2;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=abs(s1-s2),r=1e9+5,ans;//注意下界，不然初始可能会gg
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1,ans=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Luzhuoyuan (赞：1)

因为这道题秒了 CSP-S 2024 T3，感恩。遂写题解以记之。

---

首先，看到题容易想出一种 $O(n^2)$ 的 DP。设 $f_{i,j}$ 表示两个人送完了前 $i$ 个快递，其中一个人在位置 $x_i$，另一个人在 $x_j$ 的答案。转移：

- 在 $i$ 的那个人走到 $i+1$：$f_{i+1,j}\gets\max(f_{i,j},|x_{i+1}-x_j|)$；
- 在 $j$ 的那个人走到 $i+1$：$f_{i+1,i}\gets\max(f_{i,j},|x_{i+1}-x_i|)$。

这里假设 $x_0=s_1,x_1=s_2$，其他位置都右移一位。答案为 $\min_{i=0}^{n-1}\{f_{n,i}\}$，不妨令 $x_{n+1}=x_n$，则答案为 $f_{n+1,n}$。

考虑优化。首先容易发现答案满足单调性，可以二分变成可行性问题。二分之后就是要判断 $f_{1,0}$ 能否转移到 $f_{n+1,n}$。

考虑转移的形式，如果把 $f$ 看作一个矩阵，那么第一种转移相当于从当前格子向下走一格，第二种转移则是直接跳到下一行的末尾（第 $i$ 行有 $i-1$ 列，类似一个三角形）。

于是得到下述做法。首先二分答案，接着倒着枚举 $i$，记录最近的一个可以走到终点（$f_{n+1,n}$）的 $f_{j,j-1}$，之后就是判断 $f_{i,i-1}$ 能否走到 $f_{j,j-1}$，因为每个位置走的步数越少限制条件就越少，就越有可能合法。判断这个东西相当于判断 $f_{i+1,i-1},f_{i+2,i-1},\dots$ 是否都合法，那么就又相当于判断 $i\sim j-1$ 这些点与 $i-1$ 的距离是否都不超过二分的值。这可以用 ST 表维护每个区间中位置最大值和最小值来判断。

复杂度 $O(n(\log n+\log V))$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=1e5+5;
int n,a[N],mx[20][N],mn[20][N];
inline int qmx(int l,int r){int k=__lg(r-l+1);return max(mx[k][l],mx[k][r-(1<<k)+1]);}
inline int qmn(int l,int r){int k=__lg(r-l+1);return min(mn[k][l],mn[k][r-(1<<k)+1]);}
inline bool chk(int x){
	int p=n+1;
	for(int i=n;i;i--)if(max(qmx(i,p-1)-a[i-1],a[i-1]-qmn(i,p-1))<=x)p=i;
	return p==1;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>a[0]>>a[1];n++;
	for(int i=2;i<=n;i++)cin>>a[i];
	for(int i=0;i<=n;i++)mx[0][i]=mn[0][i]=a[i];
	for(int i=1;i<17;i++)for(int j=1;j<=n-(1<<i)+1;j++)
		mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]),
		mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
	int l=abs(a[0]-a[1]),r=1e9;
	while(l<r){int mid=(l+r)>>1;chk(mid)?r=mid:l=mid+1;}
	cout<<l<<'\n';
	return 0;
}
```

（逃

---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF875E)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf875e-delivery-club)）

$\Large\mathscr{P}\mathit{art}\,\,1\;\;\text{基本思路}$

看到求最大间距的最小值，首先想到二分答案。因为可能出现的情况多变（ $2^n$ 种），所以直接考虑最终状态。

由于题目中已经告诉我们快递员是按输入顺序依次送货的，所以肯定有一位 $a_1$ 最终停在 $x_n$ 上。设目标间距为 $d$，则另一位快递员 $a_2$ 在倒数第一个任务时一定在 $[x_n-d,\ x_n+d]$ 的范围内。

但是到了倒数第二个任务时，如果 $x_{n-1}$ 在 $[x_n-d,\ x_n+d]$ 内，则 $a_1$ 一定能到这个点，且无论是谁到了这个点，此时另一人的坐标范围就变成了 $[x_{n-1}-d,\ x_{n-1}+d]$。

如果 $x_{n-1}$ 不在 $[x_n-d,\ x_n+d]$ 内，则只能是 $a_1$ 到达这个点，所以 $a_2$ 的坐标必在 $[x_{n-1}-d,\ x_{n-1}+d]$ 内，同时，因为 $a_2$ 之前有 $[x_n-d,\ x_n+d]$ 的限制，所以此时 $a_2$ 的坐标范围为 $[x_n-d,\ x_n+d]\ \cap\ [x_{n-1}-d,\ x_{n-1}+d]$。

现在把此结论拓展。若现在已知在第 $i+1$ 个任务时，某个快递员的坐标范围为 $[l_{i+1},\ r_{i+1}]$，那么在第 $i$ 个任务时，首先定有某人的坐标在 $[x_i-d,\ x_i+d]$ 内，且如果 $x_i\notin[l_{i+1},\ r_{i+1}]$，则这个快递员还必定是上述有坐标限制的快递员，即此时 $[l_i,\ r_i]=[l_{i+1},\ r_{i+1}]\ \cap\ [x_i-d,\ x_i+d]$。

最终得到某快递员的坐标范围 $[l_1,\ r_1]$，判断 $s_1$ 和 $s_2$ 是否在其中即可。

$\Large\mathscr{P}\mathit{art}\,\,2\;\;\text{Code}$

```cpp
#include <cstdio>
const int N=1e5+5,V=1e9+5;
int n,s1,s2,x[N];
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
bool inord(int x,int y,int z){return x<=y&&y<=z;}
bool ck(int d){
	int l=x[n]-d,r=x[n]+d;
	for(int i=n-1; i>=1&&l<=r; i--){
		if(inord(l,x[i],r)) l=x[i]-d,r=x[i]+d;
		else l=max(l,x[i]-d),r=min(r,x[i]+d);
	}
	return inord(l,s1,r)||inord(l,s2,r);
}
int bs(int lf,int rt){
	int md=(lf+rt)>>1,res=-1;
	while(lf<=rt){
		if(ck(md)) res=md,rt=md-1;
		else lf=md+1;
		md=(lf+rt)>>1;
	}
	return res;
}
int main(){
	scanf("%d%d%d",&n,&s1,&s2);
	for(int i=1; i<=n; i++) scanf("%d",x+i);
	printf("%d\n",bs(max(s1,s2)-min(s1,s2),V));
	return 0;
}
```

时间复杂度 $\Theta(n\log V)$，其中 $V$ 为值域。

---

## 作者：SFlyer (赞：0)

duel 到的一个还不错的题目。这里给出一个比较顺但是代码长度不是特别短的做法。

首先考虑二分。设 $dp_{i,j}$ 为一个人在 $s_i$，一个人在 $s_{j<i}$，操作到了 $i$，可不可行。发现我们所做的事情就是：$j$ 固定，$i$ 在晃荡。对于同一个 $j$ 来说，可以的 $i$ 是一个区间。那么我们把所有区间画出来，$dp_{i,*}$ 可以的就是对于所有触碰到 $i$ 的区间的 $j$。而一旦 $dp_{i}$ 被碰到，我们就可以变成 $i$ 来延申区间（即交换移动的人），又贡献一个区间。维护现在覆盖到的最右端点。

因此，我们只要看看区间可不可以一直覆盖到 $n$ 就行了！现在要算的是对于一个 $i$，求出最大的 $r_i$ 使得 $i+1\sim r_i$ 中和 $i$ 位置之差 $\le mid$。这个只要保证区间最大值，区间最小值可行就可以了。可以 ST 表。

这样就有了一个 $\mathcal{O}(n\log n\log V)$ 的做法了！

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+10;

ll n,s1,s2,x[N],mn[20][N],mx[20][N],lg[N];

ll qymx(int l,int r){
	int t=lg[r-l+1];
	return max(mx[t][l],mx[t][r-(1<<t)+1]);
}

ll qymn(int l,int r){
	int t=lg[r-l+1];
	return min(mn[t][l],mn[t][r-(1<<t)+1]);
}

int rb[N];

void init(ll md){
	for (int i=1; i<=n+2; i++){
		int l=i-1,r=n+3;
		while (l+1<r){
			int mid=l+r>>1;
			if (abs(qymx(i,mid)-x[i])<=md && abs(qymn(i,mid)-x[i])<=md) l=mid;
			else r=mid;
		}
		rb[i]=l;
	}
}
bool chk(ll mid){
	int r=2;
	init(mid);
	for (int i=1; i<=n+2; i++){
		if (r>=i){
			r=max(r,rb[i]);
		}
	}
	return r>=n+2; 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>s1>>s2;
	for (int i=3; i<=n+2; i++){
		cin>>x[i];
	}
	x[1]=s1;
	x[2]=s2;
	for (int i=1; i<=n+2; i++){
		mn[0][i]=mx[0][i]=x[i];
	}
	for (int i=2; i<N; i++) lg[i]=lg[i/2]+1;
	for (int i=1; i<20; i++){
		for (int j=1; j+(1<<i)-1<=n+2; j++){
			mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
			mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
		}
	}
	ll l=abs(s1-s2)-1,r=2e9;
	while (l+1<r){
		ll mid=l+r>>1;
		if (chk(mid)) r=mid;
		else l=mid;
	}
	cout<<r<<"\n";
	return 0;
}
```

---

