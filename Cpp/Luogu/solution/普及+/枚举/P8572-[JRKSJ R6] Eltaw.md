# [JRKSJ R6] Eltaw

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/at23jtmh.png?x-oss-process=image)

你在月下独自行走，不禁想起了一道简单题。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

给你 $k$ 个长为 $n$ 的序列 $a_{1\dots k,1\dots n}$，有 $q$ 次询问，每次询问给出一个区间 $[l,r]$，要求出 $\displaystyle\max_{i=1}^k\sum_{j=l}^ra_{i,j}$，即求出所有序列中区间 $[l,r]$ 的和的最大值。

## 说明/提示

Idea：cyffff，Solution：cyffff，Code：cyffff，Data：cyffff

**Eltaw - Fl00t (Insane14.4)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**
### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5\times10^3$ | $k\le 100$ | $20$ |
| $2$ | $5\times10^5$ | 保证 $l=1$ | $30$ |
| $3$ | $5\times10^5$ | 无 | $50$ |

对于 $100\%$ 的数据，$1\le n,k,q\le5\times 10^5$，$1\le n\times k\le 5\times10^5$，$1\le l\le r\le n$，$0\le a_{i,j}\le 10^9$。
### 数据更新记录
$\text{upd 2022.10.05}$：更新了两组数据，分别卡掉了两种时间复杂度错误的做法。感谢 @[二叉苹果树](https://www.luogu.com.cn/user/270854) 指出。


$\text{upd 2022.10.08}$：更新了一组数据，卡掉了记忆化不正确的做法。感谢 @[SweetOrangeOvO](https://www.luogu.com.cn/user/236862) 指出。

如果你能通过现在的所有测试点，说明你的代码复杂度极可能是正确的。如果你仍认为你的复杂度是错误的，请联系出题人。

## 样例 #1

### 输入

```
7 2 3
1 1 4 5 1 4 0
1 9 1 9 8 1 0
6 7
5 7
1 3```

### 输出

```
4
9
11```

# 题解

## 作者：cyffff (赞：10)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8572)
## 题意
给你 $k$ 个长为 $n$ 的序列 $a_{1\dots k,1\dots n}$，有 $q$ 次询问，每次询问给出一个区间 $[l,r]$，求出所有序列中区间 $[l,r]$ 的和的最大值。

$1\le n,k,q\le5\times 10^5$，$1\le n\times k\le 5\times10^5$。
## 思路
暴力题。

先给出做法，对于一次询问的区间 $[l,r]$，如果之前询问过，直接输出之前记录的答案，否则直接 $O(k)$ 求出每个序列的区间和，求最大值并记录即可。

我们来分析复杂度，令 $s=nk$。

考虑到 $n,k$ 中必然有一个小于等于 $\sqrt s$，分类讨论：

1. 当 $n\le k$ 即 $n\le \sqrt s$ 时：

	询问的区间只有 $O(n^2)$ 种，每种需要 $O(k)$ 的时间求出，则时间复杂度为 $O(n^2k)$，即为 $O(s\sqrt s)$。
2. 当 $k\le n$ 即 $k\le \sqrt s$ 时：
	
   最坏的情况是每次询问都要 $O(k)$ 回答，此时也只需 $O(qk)$ 即 $O(q\sqrt s)$ 的时间回答。

综上，我们可以在 $O(s\sqrt s+q)$ 或 $O(s+q\sqrt s)$ 的时间内解决本问题。

~~不希望被叫做根号分治。~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=5e5+10;
int n,k,q,a[N];
ll pr[N];
map<ll,ll>ans; 
int main(){
	n=read(),k=read(),q=read();
	for(int i=1;i<=k;i++){
		int p=(i-1)*n;
		for(int j=1;j<=n;j++)
			a[++p]=read();
		p=(i-1)*n+1;
		pr[p]=a[p];
		for(int j=2;j<=n;j++)
			p++,pr[p]=pr[p-1]+a[p];
	}
	while(q--){
		ll l=read(),r=read();
		if(ans.find(l*n+r)!=ans.end()) write(ans[l*n+r]),putc('\n');
		else{
			ll tmp=0;
			for(int i=1;i<=k;i++){
				int p=(i-1)*n;
				if(l!=1) tmp=max(tmp,pr[p+r]-pr[p+l-1]);
				else tmp=max(tmp,pr[p+r]);
			}
			write(ans[l*n+r]=tmp),putc('\n');
		}
	}
	flush();
}
```

再见 qwq~

---

## 作者：Jerrlee✅ (赞：3)

这次比赛蛮不错的，赛时好好写了几题，$310$ 分跑路（
## 题意
给你 $k$ 个长为 $n$ 的序列 $a_{1\dots k,1\dots n}$，$q$ 次询问，每次询问求 $k$ 个序列中区间 $[l,r]$ 的和的最大值。
## 思路
求区间最大值，一眼可以想到前缀和。~~对就是用眼睛想（雾~~

但是按照题意写完后，你会发现你只有 [$20$ 分](https://www.luogu.com.cn/record/88543516)。

观察数据范围，发现 $n \times k$ 小于 $5 \times 10^5$，但是 $q \times k$ 并不满足，所以 $O(q \times k)$ 的询问复杂度是过不去的。

有个小提示：

> $4\times 10^8$ 次运算可以在 $2$ 秒内完成。

已知 $5 \times 10^5 \times \sqrt{5 \times 10^5} \approx 3.5 \times 10^8$，说明复杂度可能含有根号。

如果预处理每次询问，可以在 $O(n^2 \times k)$ 的复杂度跑完（预处理 $O(n^2 \times k)$，回答询问 $O(1)$），而 $n \leq \sqrt{5 \times 10^5}$ 的情况下，你可以轻松（？）过去。

再加上前文 $O(q \times k)$ 的询问复杂度，两种情况分类一下，你就 AC 了这题。

具体见代码，应该还是比较好懂的。

~~甭管他叫不叫根号分治，反正思想有点像，但主要是复杂度分析~~。
## 代码
```cpp
#define int long long//__int128
int jrl[500009];
signed main(){
    int n,k,q;
    cin>>n>>k>>q;
    int a[k+1][n+1];
    int qzh[k+9][n+9];
    int Jerrlee=sqrt(500000);
    int ans[Jerrlee+9][Jerrlee+9];//这边要注意，数组开大会 MLE
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            qzh[i][j]=qzh[i][j-1]+a[i][j];//前缀和
        }
    }
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            jrl[j]=max(jrl[j],qzh[i][j]);//这段是专为 sub2 写的，同时能有效缩短一内内时间，但是不加也能过
    if(k>sqrt(500000)){
    memset(ans,0,sizeof ans);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int z=1;z<=k;z++)
                ans[i][j]=max(ans[i][j],qzh[z][j]-qzh[z][i-1]);//这是前文所说第二种方法的预处理
    }//O(n^2 k)
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x==1){cout<<jrl[y]-jrl[x-1]<<endl;continue;}//O(n k) in total
        int cnt=LLONG_MIN;
        if(k>sqrt(500000)){
            cout<<ans[x][y]<<endl;
        }//O(1)
        else{
            for(int i=1;i<=k;i++) cnt=max(cnt,qzh[i][y]-qzh[i][x-1]);
            cout<<cnt<<endl;
        }//O(q k)
    }
}
```
[AC 记录](https://www.luogu.com.cn/record/88577357)

---

## 作者：nullqtr_pwp (赞：2)

# P8572 Solution
## 题目

给你 $k$ 个长为 $n$ 的序列 $a_{1\dots k,1\dots n}$，有 $q$ 次询问，每次询问给出一个区间 $[l,r]$，要求出 $\displaystyle\max_{i=1}^k\sum_{j=l}^ra_{i,j}$，即求出所有序列中区间 $[l,r]$ 的和的最大值。

对于 $100\%$ 的数据，$1\le n,k,q\le5\times 10^5$，$1\le n\times k\le 5\times10^5$，$1\le l\le r\le n$，$0\le a_{i,j}\le 10^9$。
## 解答

很容易想到，可以用 $a_{i,j}$ 表示 第 $i$ 个数列的前 $j$ 个数的值，然后 $O(k)$ 求出最大值，因为求一段区间的和用前缀和来求是 $O(1)$ 的。不会前缀和的看[这道题](https://www.luogu.com.cn/problem/P8218)。

暴力代码 $(50pts)$：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int c[705][705];
signed main(){
	int n=read(),k=read(),q=read();
	int a[k+1][n+1];
	memset(a,0,sizeof(a));
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++){
			int x=read();
			a[i][j]=a[i][j-1]+x;
		}
	while(q--){
		int l=read(),r=read(),mx=0;
		for(int i=1;i<=k;i++)
			mx=max(mx,a[i][r]-a[i][l-1]);
		printf("%lld\n",mx);
	}
}
```

这段代码的复杂度是 $O(nk+qk)$ 的，当 $n>\sqrt{nk}$ 时有点不太合适。但是如果 $n\leq \sqrt{nk}$，有 $O(kn^2)$ 的优化解法，具体可以直接看代码，$O(1)$ 的查询，$O(kn^2)$ 的预处理，此时的复杂度优化成了 $O(nk^2)$。

再看，如果 $k\leq \sqrt{nk}$，则用原来的暴力解法的复杂度是 $O((n+q)\sqrt{nk})$。

AC code：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int c[705][705];
signed main(){
	int n=read(),k=read(),q=read();
	int a[k+1][n+1];
	memset(a,0,sizeof(a));
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++){
			int x=read();
			a[i][j]=a[i][j-1]+x;
		}
	if(n<=700){
		for(int i=1;i<=k;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					c[j][k]=max(c[j][k],a[i][k]-a[i][j-1]);
		while(q--){
			int l=read(),r=read();
			printf("%lld\n",c[l][r]);
		}
		return 0;
	}
	while(q--){
		int l=read(),r=read(),mx=0;
		for(int i=1;i<=k;i++)
			mx=max(mx,a[i][r]-a[i][l-1]);
		printf("%lld\n",mx);
	}
}
```

还有一种优化，询问时的 $l,r$ 可能有重复，用 STL 中的 map 判重也能卡过去这题。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
map<pair<int,int>,int>m;
int c[705][705];
signed main(){
	int n=read(),k=read(),q=read();
	int a[k+1][n+1];
	memset(a,0,sizeof(a));
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++){
			int x=read();
			a[i][j]=a[i][j-1]+x;
		}
	while(q--){
		int l=read(),r=read(),mx=0;
		if(m.count({l,r})){
		    printf("%lld\n",m[{l,r}]);
		    continue;
		}
		for(int i=1;i<=k;i++)
			mx=max(mx,a[i][r]-a[i][l-1]);
		m[{l,r}]=mx;
		printf("%lld\n",mx);
	}
}
```

---

## 作者：Engulf (赞：2)

注意到题目中给了一个奇怪的数据范围 $1 \le n \cdot k \le 5 \cdot 10 ^ 5$，考虑根号分治。

1. 当 $k > \sqrt{5 \cdot  10 ^ 5}$（$\sqrt{5 \cdot 10 ^ 5} \approx 707$）时，$n$ 就会比较小，所以可以预处理出 $f_{i, j}$ 来代表 $[l, r]$ 这个区间的最大值，预处理 $\mathcal{O}(nk)$，查询 $\mathcal{O}(1)$。

2. 当 $k \le 707$ 时，$n$ 较大，所以搞个前缀和来优化。查询时间复杂度 $\mathcal{O}(k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int M = 707;
int n, k, q;
int f[M][M];

signed main()
{
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n >> k >> q;
	vector<vector<int>> a(k + 1, vector<int>(n + 1));
	for (int i = 1; i <= k; i ++ )
		for (int j = 1; j <= n; j ++ )
			cin >> a[i][j], a[i][j] += a[i][j - 1];
	if (k > M)
	{
		for (int i = 1; i <= n; i ++ )
		{
			for (int j = i; j <= n; j ++ )
			{
				for (int id = 1; id <= k; id ++ )
				{
					f[i][j] = max(f[i][j], a[id][j] - a[id][i - 1]);
				}
			}
		}
	}
	while (q -- )
	{
		int l, r;
		cin >> l >> r;
		int ans = 0;
		if (k <= M)
		{
			for (int i = 1; i <= k; i ++ )
				ans = max(ans, a[i][r] - a[i][l - 1]);
			cout << ans << '\n';
		}
		else
		{
			cout << f[l][r] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

提供一种乱搞做法。

## 20pts

这道题开数组会炸，要用 vector 存。

设 $s_{i,j}=\sum_{k=1}^ja_{i,k}$，则 $\sum_{k=l}^ra_{i,k}=s_{i,r}-s_{i,l-1}$，对于每个 $i$ 取最大值即可。

太简单了，不放代码了。

## 50pts

因为有特殊情况 $l=1$，所以答案就是 $max_{i=1}^ns_{i,r}$，在处理 $s_{i,j}$ 时顺便处理答案即可，时间复杂度 $O(qk)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,k,q,maxx[N];
vector<int> v[N];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k>>q;
	for(int i=1,x;i<=k;i++)
	{
		v[i].push_back(0);
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			v[i].push_back(v[i][j-1]+x),maxx[j]=max(maxx[j],v[i][j]);
		}
	}
	while(q--)
	{
		int x,y,ans=0;
		cin>>x>>y;
		if(x==1)
			cout<<maxx[y]<<"\n";
		else
		{
			for(int i=1;i<=k;i++)
				ans=max(ans,v[i][y]-v[i][x-1]);
			cout<<ans<<"\n"; 
		}
	}
}
```

## 100pts

分析一下，如果在 $n$ 很小，但 $k$ 却很大的一般情况下，单次询问时间为 $O(k)$，直接炸掉了。可以预处理每种 $[l,r]$ 的答案，时间复杂度 $O(n^2k+q)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,M=5000;
int n,k,q,maxx[N],ans[M][M];
vector<int> v[N];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k>>q;
	for(int i=1,x;i<=k;i++)
	{
		v[i].push_back(0);
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			v[i].push_back(v[i][j-1]+x),maxx[j]=max(maxx[j],v[i][j]);
		}
	}
	if(n*n*k<=400000000)
	{
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				for(int l=1;l<=k;l++)
					ans[i][j]=max(ans[i][j],v[l][j]-v[l][i-1]);
		while(q--)
		{
			int x,y;
			cin>>x>>y;
			cout<<ans[x][y]<<"\n";
		}
	}
	else
		while(q--)
		{
			int x,y,ans=0;
			cin>>x>>y;
			if(x==1)
				cout<<maxx[y]<<"\n";
			else
			{
				for(int i=1;i<=k;i++)
					ans=max(ans,v[i][y]-v[i][x-1]);
				cout<<ans<<"\n"; 
			}
		}
}
```


---

## 作者：快斗游鹿 (赞：1)

## 思路

题目要求区间和，容易想到使用前缀和。根据题目提示与数据范围，容易想到根号分治。

### 方法一

该方法适用于 $k$ 较小的时候。

定义 $ans_{i,j}$ 表示第 $i$ 个序列里前 $j$ 个数的前缀和。每次查询只需要寻找 $\displaystyle\max_{i=1}^ks_{i,r}-s_{i,l-1}$ 即可，时间复杂度 $O(kq)$。针对 $l=1$ 的情况，定义 $ans_i$ 表示所有序列里第 $i$ 个数的前缀和的最大值。每次查询直接输出即可。

核心代码：

```
ll sum[k+5][n+5],ans[n+5];memset(sum,0,sizeof(sum));memset(ans,0,sizeof(ans));
for(int i=1;i<=k;i++){
	for(int j=1;j<=n;j++){
		ll x;x=read();sum[i][j]=sum[i][j-1]+x;ans[j]=max(ans[j],sum[i][j]);
	}
}
while(q--){
    ll l,r;l=read();r=read();ll mx=0;
	if(l==1){
			printf("%lld\n",ans[r]);
	}
	else{
		for(int i=1;i<=k;i++){
			mx=max(mx,sum[i][r]-sum[i][l-1]);
		}
		printf("%lld\n",mx);
	}
}
```

### 方法二

该方法适用于 $n$ 较小的时候。

定义 $ans_{l,r}$ 表示所有序列里第 $l$ 个数到第 $r$ 个数的和的最大值。输入时可以进行预处理，时间复杂度 $O(kn^2)$，每次都可以实现 $O(1)$ 查询。

核心代码：

```
ll sum[k+5][n+5],ans[n+5][n+5];memset(sum,0,sizeof(sum));memset(ans,0,sizeof(ans));
for(int i=1;i<=k;i++){
	for(int j=1;j<=n;j++){
		ll x;x=read();sum[i][j]=sum[i][j-1]+x;
		for(int kk=1;kk<=j;kk++){//预处理部分
			ans[kk][j]=max(ans[kk][j],sum[i][j]-sum[i][kk-1]);
		}
	}
}
while(q--){
    ll l,r;l=read();r=read();ll mx=0;
	printf("%lld\n",ans[l][r]);
}
```

两种方法合并后，即可通过本题。

---

## 作者：哈士奇憨憨 (赞：0)

## 思路
首先，我们把数组做一维前缀和，这样我们就可以把时间复杂度做到 $O(NK+QK)$，但这样还不够优。

考虑用 `map` 记录已经询问过的 $l$ 和 $r$，考虑最坏复杂度：

- 当 $n^2 > q$ 时，当每一组询问都不同时，复杂度为 $O(n^2k)$，但此时 $n \le \sqrt{nk}$，所以复杂度为 $O(nk\sqrt{nk})$，可以过。
- 当 $n^2 \le q$ 时，此时必有至少一组询问相同，复杂度最坏为 $O(qk)$，但此时 $k \le \sqrt{nk}$，所以复杂度为 $O(q\sqrt{nk})$，可以过。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, q, l, r;
map<pair<int, int>, long long>s;
int main(){
	cin.tie(0), cout.tie(0);
    cin >> n >> k >> q;
    long long a[k + 5][n + 5];
    for(int i = 1; i <= k; i++){
    	for(int j = 1; j <= n; j++){
    		cin >> a[i][j];
    		a[i][j] += a[i][j - 1];
		}
	}
	while(q--){
		cin >> l >> r;
		if(s[{l, r}]){
			cout << s[{l, r}] << "\n";
		}else{
			long long maxx = 0;
			for(int i = 1; i <= k; i++){
				maxx = max(maxx, a[i][r] - a[i][l - 1]);
			}
			cout << maxx << endl;
			s[{l, r}] = maxx;
		}
	}
    return 0;
}
```

---

## 作者：Jorisy (赞：0)

一道暴力题。

遇到这种~~玄学~~题，我们一定看清数据范围所显示出的性质。

本题中，有 $1\le n\times k\le 5\times10^5$ 这个东西。

这告诉我们，这题的正解复杂度必定大于 $O(nk)$。

我们先前缀和预处理，然后考虑两种暴力。

- 第一种：对于询问之前，先进行预处理每个区间的答案，做到 $O(1)$ 回答。时间复杂度 $O(n^2k)$（去除输入，下同）；
- 第二种：对于每次询问，直接进行暴力寻找答案。时间复杂度 $O(qk)$。

两种暴力在不同情况下都有不同的优势，我们考虑将两者合并在一起。

对于第一种暴力，我们肯定希望 $n$ 尽可能小；而对于第二种暴力，我们希望 $k$ 尽可能小（因为我们改变不了 $q$）。

我们发现，$n$ 与 $k$ 是反比例增长的。故我们可以当 $n\le k$ 时执行第一种暴力，$k\le n$ 时执行第二种暴力。

为了降低复杂度，我们在第二个暴力中可以记忆化一下每次的询问。

我们知道，$n,k$ 最大是 $\sqrt{5\times10^5}≈700$，$n^2k$ 与 $qk$ 最大约为 $3.5\times10^8$，时限两秒，可以过掉。

AC Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<int>a[500005],sum[500005];
map<pair<int,int>,int>mp;
int n,k,q;

signed main()
{
	scanf("%lld%lld%lld",&n,&k,&q);
	for(int i=1;i<=k;i++)
	{
		a[i].resize(n+1);
		sum[i].resize(n+1);
		sum[i][0]=0;
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
			sum[i][j]=sum[i][j-1]+a[i][j];//前缀和优化
		}
	}
	if(n<=k)//第一种暴力
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				int maxs=-114514;
				for(int l=1;l<=k;l++)
				{
					maxs=max(maxs,sum[l][j]-sum[l][i-1]);
				}
				mp[{i,j}]=maxs;
			}
		}
		while(q--)
		{
			int l,r;
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",mp[{l,r}]);
		}
		return 0;
	}
	while(q--)//第二种暴力
	{
		int l,r,ans=-114514;
		scanf("%lld%lld",&l,&r);
		if(!mp[{l,r}])//记忆化
		{
			for(int i=1;i<=k;i++)
			{
				ans=max(ans,sum[i][r]-sum[i][l-1]);
			}
			mp[{l,r}]=ans;
		}
		printf("%lld\n",mp[{l,r}]);
	}
 	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

最先想到一个 $O(Qk)$ 的解法：先预处理出每个序列的前缀和，然后对于每一次询问在每个序列的前缀和 $sum_r-sum_{l-1}$ 中取 $\max$。

观察数据范围：$n\times k\leq 5\times10^5$，发现 $n$ 和 $k$ 是一种“相互制约”的关系，于是想到根号分治。

当 $n\leq\sqrt{5\times10^5}$ 时，可以预处理一下每个区间 $[l,r]$ 的答案，时间复杂度 $O(n^2k)$，单次询问 $O(1)$。

其余情况直接暴力即可，时间复杂度 $O(Qk)$ 。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500005];
signed main(){
	int n,k,q,tmp=sqrt(500000);
	cin>>n>>k>>q;
	int sum[k+1][n+1],ans[tmp+10][tmp+10];
	for(int i=1;i<=k;i++){
		sum[i][0]=0;
		for(int j=1;j<=n;j++) cin>>a[j];
		for(int j=1;j<=n;j++) sum[i][j]=sum[i][j-1]+a[j];
	}//预处理前缀和
	memset(ans,0,sizeof(ans));
	if(k>sqrt(500000)){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int z=1;z<=k;z++){
					ans[i][j]=max(ans[i][j],sum[z][j]-sum[z][i-1]);
				}
			}
		}
	}//n<=sqrt(500000)时预处理所有答案
	while(q--){
		int l,r;
		cin>>l>>r;
		if(k<=sqrt(500000)){
			int ans=-0x3f3f3f3f;
			for(int i=1;i<=k;i++) ans=max(ans,sum[i][r]-sum[i][l-1]);
			cout<<ans<<'\n';
		}
		else{
			cout<<ans[l][r]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：0)

接下来默认 $q$ 与 $nk$ 同阶。

这题有两个暴力，一个是 $O(n^2k)-O(nk)$ 的，一个是 $O(nk)-O(nk^2)$ 的。

先预处理前缀和。

对于第一个暴力，令 $ans_{l,r}$ 表示所有 $k$ 个序列里 $[l,r]$ 区间和最大的一个，枚举序列编号，左端点，右端点，即可预处理所有询问答案。询问直接输出即可。

对于第二个暴力，除了前缀和不需要额外的预处理。询问直接扫描 $k$ 个序列里所有的区间和即可。

我们发现，当 $n$ 比较小的时候，暴力一更好，否则是暴力二好。那么有这样一个策略：当 $n$ 小于等于 $\sqrt{nk}$ 时我们做暴力一，反之做暴力二。

看起来不能过？令 $N=nk$，则我们做暴力一时，$n\leq \sqrt N$，复杂度最坏是 $O(N\sqrt N)$，做暴力二时，$k\lt \sqrt N$，复杂度最坏也是 $O(N\sqrt N)$。

记得开 `vector` 或指针动态申请内存。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, q;
const int N = 5e5 + 5;
int *a[N];
long long *s[N];
long long ans[705][705];
inline int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x;
}
int main() {
	ios::sync_with_stdio(false);
	cout.tie(NULL);
	n = read(), k = read(), q = read();
	for (int i = 1; i <= k; i++) {
		a[i] = (int*)calloc(n + 1, sizeof(int));
		for (int j = 1; j <= n; j++)
			a[i][j] = read();
	}
	for (int i = 1; i <= k; i++) {
		s[i] = (long long*)calloc(n + 1, sizeof(long long));
		for (int j = 1; j <= n; j++) s[i][j] = s[i][j - 1] + a[i][j];
	}
	if (n <= sqrt(n * k)) {
		memset(ans, ~0x7f, sizeof ans);
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= n; j++)
				for (int l = j; l <= n; l++) {
					ans[j][l] = max(ans[j][l], s[i][l] - s[i][j - 1]);
				}
		}
		for (int i = 1; i <= q; i++) {
			int l = read(), r = read();
			cout << ans[l][r] << '\n';
		}
	} else {
		for (int i = 1; i <= q; i++) {
			int l = read(), r = read();
			long long res = -1;
			for (int j = 1; j <= k; j++)
				res = max(res, s[j][r] - s[j][l - 1]);
			cout << res << '\n';
		}
	}
	return 0;
}
```


---

## 作者：Moeebius (赞：0)

## Preface
奇妙的暴力题……
## Analysis

### 暴力怎么做？
由于数列静态，可以 $O(nk)$ 计算每个数列前缀和，再 $O(kq)$ 处理询问，可以拿到 30 分。

### 怎么优化？
在 IOI 赛制下，如果你交了一发暴力，你会发现仅仅 $\text{TLE}$ 两个点。

这不是暴力吗？？为什么这么快？

注意到 $nk\le5\times10^5$。

我们重新分析一下复杂度，令 $S=nk$。

当 $n\le S^{0.5}$ 时，可能的询问区间只有 $O(n^2)$ 即 $O(S)$ 种，可以预处理。

当 $n\ge S^{0.5}$ 时，$k\le S^{0.5}$，暴力的复杂度是 $O(qS^{0.5})$ 的，可以通过。

实现的时候可以按照上述做法，也可以直接开个 `map` 记忆化。

**注意要开 `long long`。**

## Code
```cpp

#define int ll
int n,k,q;
const int MAXN=5e5+5;
vector<int> a[MAXN],sum[MAXN];
map<pair<int,int>,int> ans;

namespace Sol0
{
	int main()
	{
		while(q--)
		{
			int l,r; read(l,r);
			auto it=ans.find(mkp(l,r));
			if(it!=ans.end()) 
			{
				printf("%lld\n",it->second);
				continue;
			}
			int maxv=0;
			For(i,1,k) maxv=max(maxv,sum[i][r]-sum[i][l-1]);
			printf("%lld\n",maxv);
			ans[mkp(l,r)]=maxv;
		}
		return 0;
	}
}

signed main()
{
	read(n,k,q);
	For(i,1,k)
	{
		a[i].reserve(n+5);a[i].pb(0);
		sum[i].reserve(n+5);sum[i].pb(0);
		For(j,1,n)
		{
			int x; read(x);
			a[i].pb(x),sum[i].pb(sum[i][j-1]+x);
		}
	}
	return Sol0::main();
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 前言

不得不说，这道题作为备用还蛮好的，给我这种蒟蒻有了上大分的机会，难度也非常合适，好评好评！

# 思路

一种暴力思想。

题目中有这样一句话：求出所有序列中区间 $[l,r]$ 的和的最大值。

看到区间，你想到了什么？没错，就是前缀和！

前缀和是什么呢？从数组中第 $1$ 个位置加到第 $i$ 个位置的元素之和。定义一个数组 $s$，$s_i$ 代表 $a_1+a_2+...+a_i$，等同于 $s_{i-1}+a_i$ ，那么此时 $s_i$ 就代表 $a$ 数组前 $i$ 个位置元素之和。

把输入的 $k$ 个序列看成一个 $k \times n$ 的二维数组，此时就可以进行前缀和操作了。一维数组前缀和的递推公式是 $s_i = s_{i-1}+a_i$，二位公式就是在一维的基础上，再加一个纵坐标 $j$，即 $s_{i,j} = s_{i,j-1}+a_{i,j}$，有了前缀和，是 $[1,n]$ 的元素之和，那么 $[l,r]$ 的元素之和怎么求呢？是 $s_r-s_{l-1}$，大家可以自己推导一下。

现在就可以模拟求出答案了。

```cpp
for(i=1;i<=k;i++)
{
	sum = s[i][r]-s[i][l-1];
	MAX = max(MAX,s);
}
```

很显然的，一道绿题不可能就这样水过去了，我们需要优化。

可以按照记忆化搜索的思考方式，我们为什么不能用一个 $b$ 数组来存放上述代码中的最大值呢？这样当 $l$ 和 $r$ 重复时，直接调用 $b$ 数组中的值，就不用再从头循环了，剩下了大笔的时间，虽然空间会消耗许多吧（但是良心出题人没有卡！），不过可以通过此题就满足我们的需求了。

本人的语文非常差，可能只是说了一下大体的思路，没有说明白，下面就给大家放代码，在代码中讲解会容易理解的多。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开 long long 见祖宗！ 
ll a[5001][5001];
ll b[5001][5001];
int main()
{
	int n,k,q,l,r,i,j,x;
	ll ma;
	cin>>n>>k>>q;
	for(i=1;i<=k;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>x;
			a[i][j] = a[i][j-1]+x;//先处理前缀和 
		}
	}
	while(q--)
	{
		cin>>l>>r;
		if(b[l][r])//记忆化来咯，当 l 和 r 出现过了，直接输出里面的值，剩下了大笔的时间。 
		{
			cout<<b[l][r]<<endl;
			continue;
		}
		MAX = INT_MIN;//找出最大值。 
		for(i=1;i<=k;i++)
		{
			ll s = a[i][r]-a[i][l-1];//每一个序列中 l 到 r 元素之和。 
			MAX = max(MAX,s);//找出最大的。 
		}
		b[l][r] = ma;//储存 
		cout<<MAX<<endl;//输出 
	}
    return 0;
}
}
```


---

