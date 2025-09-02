# [CEOI 2005] Ticket Office

## 题目描述

售票处在出售音乐会门票，但它不销售单个座位的门票，而是销售固定数量的连续座位的成组门票。该售票处办公室已收到大量采购订单。一组座位的采购订单指定该组座位中最低的座位号。而办公室可能无法完成所有采购订单。此外，如果它只完全按照采购订单中的要求分配座位，那么大量作位可能会保持空置。因此，办公室采用以下分配和定价策略。如果采购订单被接受并且分配的座位正是所要求的座位，那么购买者支付全价（$2$ petaks）。如果采购订单被接受，但分配的座位与请求的座位不同（至少在一个位置上），则购买者支付半价（$1$ petak）。目标是使总收入最大化。  
请您编写一个程序来计算可以实现的最大收入，并将座位分配给选定的订单以实现该收入。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据， $1 \leq M \leq 3×10^4$，$1 \leq L \leq 100$，$1 \leq N \leq 10^5$，$1 \leq z \leq M-L+1$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Ticket Office。  
由 @[求学的企鹅](/user/271784) 翻译整理。  
Special Judge 感谢 @[Azazеl](/user/160701)。

## 样例 #1

### 输入

```
20 3
7
4 2 10 9 16 15 17```

### 输出

```
9
6
4 1
1 4
2 7
3 10
6 13
5 16```

# 题解

## 作者：zxh923 (赞：3)

# P7688 [CEOI2005] Ticket Office 题解

[题目传送门](https://www.luogu.com.cn/problem/P7688)。

### 思路

首先考虑尽可能多放置全价票。因为全价票和半价票占的大小相同。也就是说假设我们初始全部使用半价票，那么此时放上一个全价票最多需要去掉 $2$ 张半价票，最少去掉 $1$ 张。换句话说，换成全价票一定不劣。

所以我们尽可能多放置全价票是对的。至于放置多少张显然是好算的，能选就选即可。

但是，会发现一个问题，有可能我这个位置放了全价票，半价票就会少一张；而在另一个位置就不会少。所以能选就选的策略**能且仅能**算出全价票的数量，并不能确定在哪里放。换句话说，我们不知道最多能放多少张半价票。

于是考虑使用动态规划计算。设 $f_i$ 表示后 $i$ 个位置最多能放多少张全价票，$g_i$ 表示在 $f_i$ 最大时，后 $i$ 个位置最多能放多少张半价票，$h_i$ 表示在 $f_i,g_i$ 均最大时，最多还能剩下多少个 $i$ 开始的前缀空位。

转移有两种：

+ 当这个位置有全价票可以放置时，有转移 $f_i\leftarrow f_{i+l}+1,g_i\leftarrow g_{i+l},h_{i}\leftarrow 0$。

+ 对于所有情况，有转移 $f_i\leftarrow f_{i+1},g_i\leftarrow g_{i+1}+[h_{i+1}=l-1],h_{i}\leftarrow (h_{i+1}+1)\bmod l$。

转移的时候，用一个 $pre$ 数组记录一下方案即可知道方案。

### 代码

```
#include<bits/stdc++.h> 
#define int long long
#define N 1000005
#define pii pair<int,int>
#define x first
#define y second
#define mod 100000000000
#define pct __builtin_popcount
#define inf 2e9
using namespace std;
int T=1,n,l,q,a[N],f[N],g[N],h[N],pre[N];
bool st[N];
void solve(int cs){
	cin>>n>>l>>q;
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		if(!a[x])a[x]=i;
	}
	for(int i=n;i;i--){
		f[i]=0;
		if(i+l-1<=n&&a[i]){
			f[i]=f[i+l]+1;
			g[i]=g[i+l];
			h[i]=0;
			pre[i]=i+l;
		}
		int nf=f[i+1],ng=g[i+1]+(h[i+1]==l-1),nh=(h[i+1]+1)%l;
		if(nf>f[i]||(nf==f[i]&&ng>g[i])||(nf==f[i]&&ng==g[i]&&nh>h[i])){
			f[i]=nf;
			g[i]=ng;
			h[i]=nh;
			pre[i]=i+1;
		}
	}
	if(f[1]+g[1]>q){
		cout<<f[1]+q<<'\n'<<q<<'\n';
	}
	else{
		cout<<f[1]*2+g[1]<<'\n'<<f[1]+g[1]<<'\n';
	}
	int x=1;
	while(x<=n){
		if(pre[x]-x==l&&a[x]){
			st[a[x]]=1;//给全价票打上标记 
		}
		x=pre[x];
	}
	int las=1,nxt=1;//nxt是下一段的开头在哪 
	x=1;
	while(x<=n){
		while(st[las]&&las<=q)las++;
		if(pre[x]-x==l&&a[x]){//有全价票 
			cout<<a[x]<<' '<<x<<'\n';
			nxt=pre[x];
		}
		else if(x-nxt+1>=l&&las<=q){//已经可以再开一段，且没有全价票 
			cout<<las<<' '<<nxt<<'\n';
			st[las]=1;
			nxt=x+1;
		}
		x=pre[x];
	}
}
void solution(){
	/*
	nothing here
	*/
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//	cin>>T;
	for(int cs=1;cs<=T;cs++){
		solve(cs);
	}
	return 0;
}
```

---

## 作者：Nangu (赞：1)

有点思维的题，想了好久！

首先，贪心地让支付者付全价的数量尽可能多一定是不劣的，因为一个付了全价的支付者最多让两个付半价的支付者无法支付。 

于是我们先让采购订单按座位顺序排列，设 $f_i$ 表示以订单 $i$ 结尾，最多能获得几个全价的订单，容易看出 $f_i$ 是单调不降的，因此维护一个双指针即可。

接下来，我们应该让付半价的人尽可能多。设 $g_i$ 为以订单 $i$ 结尾，前面所能创造的最多的空位有几个。考虑转移，我们先枚举订单 $j$，满足 $f_j+1=f_i$ 且 $z_j+L\le z_i$，计算 $j$ 到 $i$ 的空位数，并转移。我们还要另设一个数组 $to_i$，表示 最终转移到 $g_i$ 的对应的 $j$，用于输出方案序列。

代码实现时，我们可以加一个订单 $z_{n+1}=M+1$，如此就能省去计算 $g_i$ 后一些繁琐的取 $\max$ 操作。

以上代码是 $O(n^2)$ 的，需要加一个单调队列。~~也有可能是我想麻烦了QwQ。~~

以下代码是不加单调队列的版本：
```cpp
#include<bits/stdc++.h>
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
using namespace std;
typedef pair<int, int> pa;
const int N=1e5+7;
int m, l, n, pos, posl, posr, f[N], g[N], to[N], q[N], hd, tl;
pa a[N];
vector<pa> ans;
bool vis[N], is_all[N];

inline int calc(int j, int i){
	return (a[i].first-a[j].first)/l-1+g[j];
}

signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    memset(g, -1, sizeof g), g[0]=0;
	cin>>m>>l>>n;
	rep(i, 1, n) cin>>a[i].first, a[i].second=i;
	sort(a+1, a+n+1);
	a[0]=pa(-l+1, 0);
	a[n+1]=pa(m+1, n+1);
	rep(i, 1, n+1){
		while(a[pos+1].first+l-1<a[i].first) ++pos;
		f[i]=f[pos]+1; 
	}
	rep(i, 1, n+1){
		while(a[posr+1].first+l-1<a[i].first) ++posr;
		while(f[posl]+1<f[i]) ++posl;
		rep(j, posl, posr){
			int tmp=calc(j, i);
			if(tmp>g[i]){
				g[i]=tmp;
				to[i]=j;
			}
		}
	}
	int A=f[n+1]-1, B=min(n-A, g[n+1]);
	cout<<A*2+B<<'\n'<<A+B<<'\n';
	for(int i=to[n+1]; i; i=to[i]){
		ans.emplace_back(a[i].first, a[i].second);
		fill(vis+a[i].first, vis+a[i].first+l, 1);
		is_all[i]=1;
	}
	pos=1;
	for(int i=1; i<=n && B; ++i) if(!is_all[i]){
		--B;
		while(vis[pos]==1 || vis[pos+l-1]==1) ++pos;
		fill(vis+pos, vis+pos+l, 1);
		ans.emplace_back(pos, a[i].second);
	}
	sort(ans.begin(), ans.end());
	for(auto x:ans) cout<<x.second<<' '<<x.first<<'\n';
}

---

## 作者：Math_rad_round (赞：1)

首先我们可以发现安排的全价票应当尽量多，因为强行放入一个全价票最多占用两个半价票，而总收益不变。

但是我们不能直接暴力能放就放，原因是可能晚放一个空格可能为前面腾出一个半价票的空间。

因此我们可以做一个 DP，设：

$f_i$ 为考虑 $i$ 往后的空间，全价票最多数量。

$g_i$ 为满足 $f_i$ 的基础上，半价票最多数量 。

$h_i$ 为考虑 $g_i$ 往后的空间，从 $i$ 开始的空位最长有多长。

转移考虑在 $i$ 位置放从 $i$ 开始的全价票还是空着。（如果空位数量足够放半价票。）

先跑一遍DP求出数量，注意全半价票只能卖 $n$ 张，多余的半价票空位只能扔掉。

时间复杂度 $O(n+m)$，空间复杂度为 $O(m)$。（和 $n$ 无关，因为同样的订单只有一个可能生效需要存。)

具体细节看代码注释吧，建议评绿。

```cpp
//代码中把fgh统一为了一个f，
//f[i]/A,f[i]%A/B,f[i]%B分别代表f[i],g[i],h[i]

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll read(){ll x=0,f=1;char a1=getchar();
	while('0'>a1||a1>'9'){if(a1=='-')f=-f;a1=getchar();}
	while('0'<=a1&&a1<='9'){x=x*10+(a1^48);a1=getchar();}
	return x*f;
}
void write(ll x,int ok=1){
	if(x==0)putchar('0');
	else{if(x<0){putchar('-');x=-x;}
		ull o=0,f=0;for(;x;x/=10,f++)o=o*10+x%10;for(;f;f--,o/=10)putchar(o%10+'0');
	}if(ok==1)putchar('\n');else if(ok==2)putchar(' ');
}
const int N=500000;
int w[N];
int fr[N];//记录f数组dp的来源 
ll f[N];
const ll A=1e8,B=1e4;
bool u[N];
int main(){
	int n=read(),le=read();
	int q=read();
	for(int i=1;i<=q;i++){
		int u=read();
		if(w[u]==0)w[u]=i;
		//同一种票需求种类显然只能达成一个，只存一个即可。 
	}
	for(int i=n;i;i--){
		f[i]=0;
		if(i+le-1<=n&&w[i]){
			ll e=(f[i+le]/B)*B;
			f[i]=e+A;
			fr[i]=i+le;
		}
		ll e=f[i+1];
		
		if(e%B==le-1){
			e/=B;e++;e*=B;
		}else e++;
		
		if(f[i]<e){
			f[i]=e;fr[i]=i+1;
		}
		
	}
	
	int full=f[1]/A;f[1]%=A;
	
	if(full+f[1]/B>q){
		write(q+full);write(q);
	}else{
		write(2*full+f[1]/B);write(full+f[1]/B);
	}
	
	//先记录哪些全价票被用到，显然在填空位时不能使用 
	int x=1;
	while(x<=n){
		if(fr[x]-x==le&&w[x]){
			u[w[x]]=1;
		}
		x=fr[x];
	}int la=1;
	x=1;int lw=1;
	
	while(x<=n){
		
		while(u[la]&&la<=q)la++;//找到最小没被用过的充当半价票的订单 
		
		if(fr[x]-x==le&&w[x]){
			write(w[x],2);write(x);lw=fr[x];
		}else if(x-lw+1>=le&&la<=q){
			write(la,2);write(lw);u[la]=1;lw=x+1;
		}
		x=fr[x];
	}
	return 0;
}

```


---

