# Post Lamps

## 题目描述

Adilbek 的家位于一个可以被表示为 OX 轴的街道上，这条街真的很黑，所以 Adilbek 想要安装一些柱灯来照亮它。街道上有 $n$ 个可以安装柱灯的位置，这些位置在 OX 轴上对应 $0,\dots,n-1$。但是有一些位置上有障碍物，不能放置安装柱灯。

有若干种不同的柱灯，它们有且仅有功率不同。当一个功率为 $l$ 的柱灯被安装在位置 $x$ 上时，这个柱灯可以照亮区间 $[x,x+l]$，所有柱灯的功率都是正整数。

柱灯店提供功率从 $1$ 到 $k$ 的柱灯，每种柱灯有无限个。然而，每个顾客只能购买一种功率的柱灯，一个功率为 $l$ 的柱灯的价格为 $a_l$。

现在，Adibek 想要知道，他购买一种柱灯来照亮整个 $[0,n]$ 的街道的最低花费是多少。Adibek 并不在乎这些灯是否会照亮街道的任何其他部分，例如，他可能在位置 $n-1$ 上安装一个功率为 $3$ 的柱灯（即使它的照明区域并不完全属于 $[0,n]$）。

## 样例 #1

### 输入

```
6 2 3
1 3
1 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 3 4
1 2 3
1 10 100 1000
```

### 输出

```
1000
```

## 样例 #3

### 输入

```
5 1 5
0
3 3 3 3 3
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
7 4 3
2 4 5 6
3 14 15
```

### 输出

```
-1
```

# 题解

## 作者：_gjm2005_ (赞：7)

题意：

现在有$k$个路灯，第$i$个路灯一个的花费是$a_i$ 同时如果他放在$j$位置可以覆盖区间$[j,j + i]$

同时有$m$个障碍，这些障碍的位置不能放灯

现在要让你覆盖$[1,n]$求最小花费

思路：
我们先考虑没有障碍的情况，如果没有障碍我们可以枚举选哪一种灯，然后对于第$i$栈灯我们可以每次跳$i$步，复杂度为$O(n+n/2+n/3+n/4+...)$即$O(n)$

如果有障碍那么我们预处理出$pre_i$表示$i$及之前第一个没障碍的点,如果我们要跳到的点为障碍那么就跳到他前面第一个没障碍的点上

复杂度为什么还是正确的呢，因为每次最往回退$m$步所以仍然能过

```
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

#define int long long
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define _FOR(i,a,b) for(int i = a; i >= b; --i)

template<typename T> void read(T &x)
{
    x = 0;int f = 1;
    char c = getchar();
    for(;!isdigit(c);c = getchar()) if(c == '-') f = -1;
    for(;isdigit(c);c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n,m,k; 
int s[N],a[N],pre[N];
bool flag[N];//是否有障碍 
signed main()
{
	read(n),read(m),read(k);
	FOR(i,1,m)
		read(s[i]),flag[s[i]] = 1;
	FOR(i,1,k)
		read(a[i]);
	if(flag[0]) {puts("-1"); return 0;}
	int maxx = 0;
	FOR(i,1,n)
	{
		if(flag[i]) pre[i] = pre[i - 1];
		else pre[i] = i;
		maxx = max(maxx,i - pre[i]);
		if(i - pre[i] >= k) {puts("-1"); return 0;}
	}
	int ans = 1e18;
	FOR(i,maxx + 1,k)
	{
		//printf("!!!%lld\n",i);
		int pos = 0,tmp = 0;
		while(pos <= n)
		{
			tmp++;
			if(pos + i >= n) break;
			pos = pre[pos + i];
			//printf("%lld\n",pos);
		}
		ans = min(ans,tmp * a[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：dengzengxiao (赞：2)

# 题目概述

在一条从 $0$ 到 $n - 1$ 的数轴上，安装若干个路灯。

可以从 $1$ 到 $K$ 中选择路灯的功率 $k$。若路灯放置在 $x$ 位置，路灯可以照亮从 $x$ 到 $x + k - 1$ 的所有位置。如果选择功率为 $k$ 的路灯，每个路灯需要用 $a_k$ 的费用。

同时，数轴上还有 $m$ 个障碍，为 $s_i(1 \le i \le m)$。

求使所有 $0$ 到 $n - 1$ 位置都被点亮的最小花费。如果无法全部照亮，输出 $-1$。

# 思路

考虑枚举每个功率需要的花费。

设功率为 $k$，那么路灯从 $0$ 开始放置，每个间隔 $k$（贪心，使费用最小）。如果当前位置上有障碍，那么就在这个障碍前第一个不是障碍的位置放置路灯。如果可以照亮这一块的障碍，那么就继续往后放置。否则这个功率 $k$ 无解。

预处理一个数组 $len$，表示如果 $i$ 位置上是障碍，那么 $len_i$ 表示 $i$ 这个位置与这个位置前最后一个没有障碍的格子之间的距离。这样优化上述的枚举，就可以过了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 5;

int n, m, k, s[N], a[N];
int ans = 1e18, len[N]; // len 为预处理数组
bool mp[N]; // 这个位置有没有障碍

int calc(int x) { // 枚举功率 x
    int pos = 0, res = 0;
    while(pos < n) {
        if(res > ans) return -1;
        if(mp[pos] == false) { // 没有障碍
            pos += x;
            res += a[x]; // 向前跳
        } else {
            if(len[pos] < x && pos - len[pos] >= 0) { // 判断能否照亮这个障碍块
                pos = pos - len[pos] + x;
                res += a[x];
            } else return -1; // 无解
        }
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> k;
    for(int i = 1; i <= m; ++i) {
        cin >> s[i];
        mp[s[i]] = true;
    }
    for(int i = 1; i <= k; ++i) cin >> a[i];

    // 预处理
    if(mp[0] == true) len[0] = 1; 
    for(int i = 1; i < n; ++i)
        if(mp[i] == true)
            len[i] = len[i - 1] + 1;
        else
            len[i] = 0;

    //枚举
    for(int i = 1; i <= k; ++i) {
        int t = calc(i);
        if(t != -1)
            ans = min(ans, t);
    }
    
    if(ans == 1e18) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}

```

---

## 作者：cosf (赞：0)

## [CF990C](https://www.luogu.com.cn/problem/CF990E)

题目读了半天才读懂。如果不是看了比赛的公告，还真做不出来。

题目要求要让灯照亮的范围包括 $[0, n]$ 的**所有**点，**不仅仅**是**整**点。这就解释了，样例 $1$ 需要用强度为 $2$ 的灯覆盖 $[0, 2], [2, 4], [4, 6]$ 这三个区间（而不是强度为 $1$ 的覆盖 $[0, 1], [2, 3], [4, 5], [5, 6]$）。

那么，转化一下题意，可以得到一个只用覆盖整点的题目：

强度为 $l$ 的灯可以覆盖 $[x, x + l - 1]$。要用恰好一种强度的灯覆盖 $[1, n]$ 中的整点。问最小费用。

注意到，$O(\sum_{i = 1}^n\lfloor\frac{n}{i}\rfloor) = O(n\ln n)$，也就是说，很可能有时间去计算每一种灯泡需要多少个。

那么，计算一个强度为 $l$ 的灯泡需要几个为什么是 $O(\lfloor\frac{n}{l}\rfloor)$ 的呢？事实上还真不一定。因为对于特定的 $l$，即使它比 $n$ 小得多，计算它还是能卡成 $O(n)$ 的（常数较小），但是，你会发现，假如你用贪心去计算的话，你根本无法构造出把算法卡成 $O(n^2)$ 的数据。

贪心的策略：第一步，肯定得从 $0$ 开始；第二步，确保左端点是点亮的或者是某个点亮的点的右边一格；接下来每一步，都试图让点亮的格子数变得最多，而又不破坏它的连续性。

我目前能构造出的尽量卡贪心的是形如 $0011\dots110011\dots1100\dots11$ 的数据，卡的效果非常差。

虽然无法完全确保（~~至少我证不出来~~）时间复杂度就是 $O(n\ln n)$ 的，但~~官解也是这么写的~~跑的非常快，所以就当作正解吧。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 1000006

ll a[MAXN];
bool p[MAXN];
int las[MAXN];

int n, m, k;

int calc(int l)
{
    int r = 0, la = -1;
    int res = 0;
    while (r < n)
    {
        if (las[r] <= la)
        {
            return 0x3ffff3ff;
        }
        la = las[r];
        r = las[r] + l;
        res++;
    }
    return res;
}

int main()
{
    n = read();
    m = read();
    k = read();
    for (int i = 0; i < n; i++)
    {
        p[i] = true;
    }
    for (int i = 1; i <= m; i++)
    {
        int s;
        s = read();
        p[s] = false;
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i])
        {
            las[i] = i;
        }
        else if (i)
        {
            las[i] = las[i - 1];
        }
        else
        {
            las[i] = -1;
        }
    }
    for (int i = 0; i < k; i++)
    {
        a[i] = read();
    }
    ll res = 0x3ffff3fff3fff3ff;
    for (int i = 0; i < k; i++)
    {
        ll t = calc(i + 1);
        // cout << i << ' ' << t << endl;
        if (t != 0x3ffff3ffll)
        {
            res = min(res, t * a[i]);
        }
    }
    if (res == 0x3ffff3fff3fff3ff)
    {
        puts("-1");
        return 0;
    }
    printf("%lld\n", res);
}

```


---

## 作者：Crazyouth (赞：0)

## 分析

坑点：![image](https://cdn.luogu.com.cn/upload/image_hosting/k5vszaro.png)
（你需要覆盖整个区间，而非只覆盖整数点，例如 $n=3$，$[0,1],[2,3]$ 是不够的。）

翻译没把这个写上去，搞得我思考了很久样例。看到这个之后，题目可以转化为每个灯可以覆盖 $[x,x+l)$，你需要覆盖区间 $[0,n)$ 中的整数点。

如果没有障碍物，我们直接枚举每个灯放哪，复杂度 $O(\displaystyle\sum_{i=1}^k\frac{n}{i})=O(n \log n)$。现在有障碍，考虑开一个数组 $pre_i$ 表示下标小于 $i$ 下标最大的非障碍物坐标。每次如果是障碍就跳到 $pre_i$，最多跳 $m$ 次，复杂度可以保证，不过常数有点大，要用快读。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000010],n,m,k,s[1000010],pre[1000010],mp[1000010];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x / 10);
	putchar(x%10+'0');
	return;
}
int add(int l)
{
	int ret=0;
	for(int i=0;i<n;i+=l)
	{
		ret++;
		if(mp[i]) i=pre[i];
	}
	return ret;
}
signed main()
{
	n=read();m=read();k=read();
	if(n==m)
	{
		puts("-1");
		return 0;
	}
	s[0]=-1e18;
	for(int i=1;i<=m;i++)
	{
		s[i]=read();
		mp[s[i]]=1;
		if(!s[i])
		{
			puts("-1");
			return 0;
		}
	}
	for(int i=1;i<=k;i++) a[i]=read();
	for(int i=1;i<=n;i++) pre[i]=(mp[i-1]?pre[i-1]:i-1);
	int tp=1,maxt=0;
	for(int i=1;i<=m;i++)
	{
		if(s[i]!=s[i-1]+1) tp=1;
		else tp++;
		maxt=max(maxt,tp);
	}
	if(maxt+1>k)
	{
		puts("-1");
		return 0;
	}
	int ans=1e18;
	for(int i=maxt+1;i<=k;i++) ans=min(ans,add(i)*a[i]);
	write(ans);
	return 0;
}

---

## 作者：_edge_ (赞：0)

首先，说一下题意，给定一条数轴从 $0$ 到 $n-1$，然后要放置路灯，有些地方不能放，路灯具有功率设为 $l$，如果把一盏功率为 $l$ 的路灯放到 $x$ 位置，他能照亮 $[x,x+l-1]$，然后我们需要找到一种功率，也只能放这种功率的路灯，使得他能照亮这条数轴，放置一次的贡献是 $a_l$，最小成本。

看到这种题目，第一反应肯定是枚举功率，然后再大力枚举哪里要放的，根据贪心的原则，我们放尽可能放右边。

然后会发现这东西暴力做事 $O(n^2)$ 的，是不是有很多都想到这一步就放弃了呢？

但是，事实上，考虑极限点的情况是每次都放置 $l$ 个，会发现这东西类似于 $n+\dfrac{n}{2}+\dfrac{n}{3}+ \dots + \dfrac{n}{k}$，这是调和级数，是 $n \log n$ 级别的。

当然，还有某些地方不能放，那么我们这时候就需要一个 `pre` 数组，记录前面第一个能放的地方，跳回到那里，这样每一段的贡献也只有 $2$，因此复杂度依旧是 $O(n \log n)$ 的。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=1e6+5;
int n,m,k,s[INF],vis[INF],pre[INF],a[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	for (int i=1;i<=m;i++) cin>>s[i],vis[s[i]]=1;
	for (int i=0;i<n;i++)
		if (!vis[i]) pre[i]=i;
		else pre[i]=pre[i-1];
	int Max=0,res=0;
	for (int i=0;i<n;i++) {
		if (vis[i]) Max++;
		else Max=0;
		res=max(res,Max);
	}
	for (int i=1;i<=k;i++) cin>>a[i];
	if (vis[0]) {cout<<"-1\n";return 0;}
	int ans=1e18;
	for (int i=1;i<=k;i++) {
		if (i<=res) continue;
		int r=pre[0],sum=0;
		while (r<n) {
			sum++;
			r+=i;
//			cout<<r<<" yiw\n";
			if (r>=n) break;
			r=pre[r];
		}
//		cout<<sum<<" "<<i<<" qpweko\n";
		ans=min(ans,sum*a[i]);
	}
	if (ans>1e17) cout<<"-1\n";
	else cout<<ans<<"\n";
	return 0;
}
```


---

