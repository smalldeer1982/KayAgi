# Garlands

## 题目描述

Like all children, Alesha loves New Year celebration. During the celebration he and his whole family dress up the fir-tree. Like all children, Alesha likes to play with garlands — chains consisting of a lightbulbs.

Alesha uses a grid field sized $ n×m $ for playing. The rows of the field are numbered from $ 1 $ to $ n $ from the top to the bottom and columns are numbered from $ 1 $ to $ m $ from the left to the right.

Alesha has $ k $ garlands which he places at the field. He does so in the way such that each lightbulb of each garland lies in the center of some cell in the field, and each cell contains at most one lightbulb. Of course lightbulbs, which are neighbours in some garland, appears in cells neighbouring by a side.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707E/3d944d29acd479b81853444b6813c350313a6711.png)

The example of garland placing.

Each garland is turned off or turned on at any moment. If some garland is turned on then each of its lightbulbs is turned on, the same applies for garland turned off. Each lightbulb in the whole garland set is unique, and thus, being turned on, brings Alesha some pleasure, described by an integer value. Turned off lightbulbs don't bring Alesha any pleasure.

Alesha can turn garlands on and off and wants to know the sum of pleasure value which the lightbulbs, placed in the centers of the cells in some rectangular part of the field, bring him. Initially all the garlands are turned on.

Alesha is still very little and can't add big numbers. He extremely asks you to help him.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707E/59774fd8bd70ea840f4a3c4bb4b95e2f490588f0.png)

This image illustrates the first sample case.

## 样例 #1

### 输入

```
4 4 3
5
1 1 2
1 2 3
2 2 1
2 1 4
3 1 7
4
1 3 1
2 3 3
2 4 3
1 4 1
7
4 1 1
4 2 9
3 2 8
3 3 3
4 3 4
4 4 1
3 4 1
2
ASK 2 2 3 3
ASK 1 1 4 4
```

### 输出

```
15
52
```

## 样例 #2

### 输入

```
4 4 1
8
4 1 1
3 1 2
2 1 1
1 1 7
1 2 5
2 2 4
2 3 1
1 3 1
3
ASK 1 1 3 2
SWITCH 1
ASK 1 1 3 2
```

### 输出

```
19
0
```

# 题解

## 作者：蒟酱 (赞：2)

简要题意：在一个 $n\times m$ 的矩阵（$n,m\le2000$）中，每个点都有个灯，刚开始所有灯都是亮的，每个灯都有一个颜色（$k\le2000$）和一个权值，保证所有颜色相同的点是联通块。  
现在操作 $q$ 次
- 操作 `SWITCH x`：把所有颜色为 $x$ 的灯状态取反，开的变关，关的变开。
- 操作 `ASK x1 y1 x2 y2`：问这个子矩阵所有开着的灯的权值之和，本操作数量小于 $2000$ 次。

据说这题大暴力都能过去，但是我这个复杂度是 $\mathcal O((nm+kq_2)\log n\log m)$ （$q_2$ 表示 ASK 操作的数量）。  
发现这题有个优秀的性质：$q_2\le2000$，由于 $k\le2000$，可以对每条链对每个询问矩阵的贡献，开个 $q_2\times k$ 的 `bool` 数组去记录，再开个 $v$ 数组表示每个链有没有被关掉。每次如果是 SWITCH 就把 $v$ 数组那条链的状态取反，如果是 ASK 操作就把 $v$ 数组复制到那个 $q_2\times k$ 的数组里。  
然后就去想如何计算贡献，可以开个二维树状数组，对于每一条链上的每一个点执行一次二维树状数组上单点修，对于每次询问的贡献就相当于再这个二维树状数组上进行一次区间询问，二维树状数组差分就可以满足。注意每一条链清空贡献时不能直接 `memset`，而要添加一次负的贡献否则复杂度是错的。

代码：（删掉了用不到的缺省源，[原始代码](https://codeforces.com/contest/707/submission/181251484)）
```cpp
//不向焦虑与抑郁投降，这个世界终会有我们存在的地方。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<tuple>
#include<random>
#define siz(x) int((x).size())
using std::cin;using std::cout;
using loli=long long;
using tiii=std::tuple<int,int,int>;
using tiiii=std::tuple<int,int,int,int>;
using bsc=std::string;
constexpr int N=2001;
int n,m,l,q;
loli ans[N];
bool v[N],w[N][N];
std::vector<tiii>a[N];
std::vector<tiiii>b;
bsc s;
loli d[N][N];
void add(int x,int y,int k){
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=m;j+=j&-j)
			d[i][j]+=k;
}
loli ask(int x,int y){
	loli k=0;
	for(int i=x;i;i-=i&-i)
		for(int j=y;j;j-=j&-j)
			k+=d[i][j];
	return k;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m>>l;
	for(int i=1,z;i<=l;i++){
		cin>>z;a[i].resize(z);
		for(auto&[x,y,c]:a[i])cin>>x>>y>>c;
	}
	std::fill(v+1,v+1+l,true);
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>s;
		if(s.front()=='A'){
			memcpy(w[siz(b)]+1,v+1,sizeof(bool)*l);
			auto&[x1,y1,x2,y2]=b.emplace_back();
			cin>>x1>>y1>>x2>>y2;
		}else{
			int p;cin>>p;
			v[p]=!v[p];
		}
	}
	for(int i=1;i<=l;i++){
		for(auto[x,y,c]:a[i])add(x,y,c);
		for(int j=0;j<siz(b);j++)
			if(auto[x1,y1,x2,y2]=b[j];w[j][i])
				ans[j]+=ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
		for(auto[x,y,c]:a[i])add(x,y,-c);
	}
	for(int j=0;j<siz(b);j++)cout<<ans[j]<<'\n';
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF707E)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf707e)内食用可能也许大概更佳。

~~duel 到的但是没切出来，后面补的。~~
## 题意分析
这个翻译我真的不想吐槽了，建议大家用油猴脚本中的 codeforces better 直接在原站翻译看题。

题目描述读懂了很明显这个可以用二维树状数组来维护。因为观察到询问次数很少，所以考虑记录每个灯条的状态是否改变，如果未变则不操作，变了就改变总的值，总体而言难度还是不大的。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&-x)
using namespace std;
struct node
{int x,y,w;};
int n,m,k,q;
vector<node>a[2010];
int t[2010][2010];
bool syg[2010],zt[2010];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
void add(int x,int y,int w)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			t[i][j]+=w;
}
int query(int x,int y)
{
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))
		for(int j=y;j>=1;j-=lowbit(j))
			res+=t[i][j];
	return res;
}
signed main()
{
	n=read(),m=read(),k=read();
	for(int i=1,tot;i<=k;i++)
	{
		tot=read();
		for(int l=1,x,y,w;l<=tot;l++)
		{
			x=read(),y=read(),w=read();
			a[i].push_back((node){x,y,w});
			add(x,y,w);
		}
	}q=read();
	while(q--)
	{
		char op=getchar();
		if(op=='A')
		{
			for(int i=1;i<=k;i++)
				if(zt[i]!=syg[i])
				{
					int f=1;if(!syg[i]) f=-1;
					for(int j=0;j<(int)a[i].size();j++) add(a[i][j].x,a[i][j].y,a[i][j].w*f);
					syg[i]=zt[i];
				}
			int x=read(),y=read(),x2=read(),y2=read();
			printf("%lld\n",query(x2,y2)-query(x-1,y2)-query(x2,y-1)+query(x-1,y-1));
		}
		else zt[read()]^=1;
	}
	return 0;
}
```


---

## 作者：流水行船CCD (赞：1)

本篇题解可通过全部数据，为暴力的改进，但时间复杂度并不正确。

前置知识：二维树状数组单修区查。

## 思路

看到矩阵问题，有区间修改/查询操作，可以想到二维树状数组，毕竟二维线段树常数太大，远远没有二维树状数组轻便。

## 暴力

由于修改的是一个个奇形怪状的链，询问却是长方形，很难处理。

因此，考虑在每次修改时暴力去修改该链上每一个点的状态，在树状数组上更新权值。

查询矩形中所有节点值的和。

然而无法通过。

```cpp

// TLE on #17

#include<bits/stdc++.h>

#define rd register
#define int long long
#define mp make_pair
#define pb emplace_back

using namespace std;

namespace fast_IO {
//省略快读
} using namespace fast_IO; 	

namespace mmp{
	const int N=2048;
	int n,m,k,q;
	int ft[N][N];
	inline void modify(rd int x,rd int y,rd int op){
		for(rd int i=x;i<=n;i+=i&-i)
			for(rd int j=y;j<=m;j+=j&-j)
				ft[i][j]+=op;
		return;
	}
	inline int query(rd int x,rd int y){
		rd int res=0;
		for(rd int i=x;i;i-=i&-i)
			for(rd int j=y;j;j-=j&-j)
					res+=ft[i][j];
		return res;
	}
	struct nmm{int x,y,w,light;};
	struct Flow{vector<nmm>dot;}se[N];
	string opd;
	int x,y,xx,yy,md;
	nmm tmp;
	signed main(){
		io>>n>>m>>k;
		for(rd int i=1,len;i<=k;++i){
			io>>len;
			for(rd int j=1,x,y,w;j<=len;++j){
				io>>x>>y>>w;
				se[i].dot.pb((nmm){x,y,w,1});
				modify(x,y,w);
			}
		}
		io>>q;
		for(rd int i=1;i<=q;++i){
			io>>opd>>x;
			if(opd=="ASK"){
				io>>y>>xx>>yy;--x,--y;
				io<<(query(xx,yy)-query(x,yy)-query(xx,y)+query(x,y))<<'\n';
			}else{
				tmp=se[x].dot[0];
				md=tmp.light^1;
				// io<<x<<" "<<tmp.light<<' '<<md<<'\n';
				for(rd int j=0;j<se[x].dot.size();++j){
					tmp=se[x].dot[j];
					se[x].dot[j].light=md;
					if(md) modify(tmp.x,tmp.y,tmp.w);
					else   modify(tmp.x,tmp.y,-tmp.w);
				}
			}
		}
		return 0;
	}
}
signed main(){
	mmp::main();
	return 0;
}

```

## 优化

看到题目中保证查询操作不超过 $2000$ 次，而且可以想到在连续操作同一根链时，产生了很多不需要更改的多余时间复杂度。

因此先记录每一条链是开启还是关闭，在查询之时再去修改每一条链的值，注意这里要看一下这几条链的状态是否发生更改，以节约复杂度。

由于本题数据水，思考到这里即可通过。

```cpp

//Accepted

#include<bits/stdc++.h>

#define rd register
#define int long long
#define mp make_pair
#define pb emplace_back

using namespace std;

namespace fast_IO {
//省略快读
} using namespace fast_IO; 	

namespace mmp{
	const int N=2048;
	int n,m,k,q;
	int ft[N][N],ne[N],bj[N];
	inline void modify(rd int x,rd int y,rd int op){
		for(rd int i=x;i<=n;i+=i&-i)
			for(rd int j=y;j<=m;j+=j&-j)
				ft[i][j]+=op;
		return;
	}
	inline int query(rd int x,rd int y){
		rd int res=0;
		for(rd int i=x;i;i-=i&-i)
			for(rd int j=y;j;j-=j&-j)
					res+=ft[i][j];
		return res;
	}
	struct nmm{int x,y,w,light;};
	struct Flow{vector<nmm>dot;}se[N];
	string opd;
	int x,y,xx,yy;
	signed main(){
		io>>n>>m>>k;
		for(rd int i=1,len;i<=k;++i){
			io>>len;ne[i]=bj[i]=1;
			for(rd int j=1,x,y,w;j<=len;++j){
				io>>x>>y>>w;
				se[i].dot.pb((nmm){x,y,w,1});
				modify(x,y,w);
			}
		}
		io>>q;
		for(rd int i=1;i<=q;++i){
			io>>opd>>x;
			if(opd=="ASK"){
				io>>y>>xx>>yy;--x,--y;
				for(rd int j=1;j<=k;++j){
					if(ne[j]==bj[j])continue;
					ne[j]=bj[j];
					for(rd int k=0;k<se[j].dot.size();++k){
						if(ne[j]) modify(se[j].dot[k].x,se[j].dot[k].y,se[j].dot[k].w);
						else      modify(se[j].dot[k].x,se[j].dot[k].y,-se[j].dot[k].w);
					}
				}
				io<<(query(xx,yy)-query(x,yy)-query(xx,y)+query(x,y))<<'\n';
			}else{
				bj[x]^=1;
				
			}
		}
		return 0;
	}
}
signed main(){
	mmp::main();
	return 0;
}
```

## 毒瘤数据构造

虽然查找操作顶多只有 $2000$ 次，还是可以构造数据。

只需要把整个矩阵串成一条链，然后反复 (查+改) ,时间复杂度会被卡成 $O(q nm)$。

构造代码如下，保证数据满足题目要求，且实测正解 `1.900 ms` 左右，但大部分题解通过不了。

```cpp
#include<bits/stdc++.h>

using namespace std;	

namespace hack{
	int n,m,k,q;
	
	random_device R;
	mt19937 G(R());
	int rd(int l,int r){return uniform_int_distribution<int>(l,r)(G);}
	
	signed main(){
		freopen("hack.in","w",stdout);
		n=2000,m=2000,k=1;
		cout<<n<<' '<<m<<" "<<k<<'\n';
		cout<<n*m<<'\n';
		for(int i=1;i<=n;++i){
			if(i&1)for(int j=1;j<=m;++j)cout<<i<<' '<<j<<' '<<rd(1,1e9)<<'\n';
			else   for(int j=m;j>=1;--j)cout<<i<<' '<<j<<' '<<rd(1,1e9)<<'\n';
		}
		q=2000;
		cout<<2*q<<'\n';
		for(int i=1;i<=q;++i){
			cout<<"SWITCH 1\n";
			cout<<"ASK 3 6 "<<rd(3,n)<<' '<<rd(6,m)<<'\n';
		}
		return 0;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	hack::main();
	return 0;
}
``

---

## 作者：ifffer_2137 (赞：0)

大家好在线求问询问次数 $\le10^6$ 怎么做。
### 题意
网格图上给定若干联通块，每个格子有权值，单次点亮/熄灭一个联通块，求子矩形点亮格子权值和。
### 分析
哇询问次数 $\le 2000$。

于是直接考虑对每次询问求出每个联通块的贡献即可，动态修改联通块求当前状态平凡。

于是再二维差分一下变成四个 2-side 数点，挂到每个联通块上用 BIT 维护扫描线即可。时间复杂度 $O(qk+kn\log m)$。

哇然后交上去 MLE 啦。

把一些询问的参数存成 `short` 就轻松卡过了。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937 rnd(time(NULL));
const int maxn=2e3+5;
const int maxm=1e6+5;
int n,m,k,q;short tot;
struct node{short x,y;int w;}a[maxn][maxn];
struct ask{short id,x,y,op;};
vector<ask> Q[maxn];
int cnt[maxn],vis[maxn];
ll ans[maxn];
vector<pii> Ax[maxn];
vector<ask> Aq[maxn];
class Fenwick_Tree{
public:
	ll c[maxn];
	#define lb(x) (x&(-x));
	void clear(){memset(c,0,sizeof(c));}
	void update(int x,int k){while(x<=m)c[x]+=k,x+=lb(x);}
	ll query(int x){ll s=0;while(x)s+=c[x],x-=lb(x);return s;}
}tr;
void solve(int T){
	for(int i=1;i<=n;i++) Ax[i].clear(),Aq[i].clear();tr.clear();
	for(int i=1;i<=cnt[T];i++) Ax[a[T][i].x].eb(mkpr(a[T][i].y,a[T][i].w));
	for(ask i:Q[T]) Aq[i.x].eb(i);
	for(int i=1;i<=n;i++){
		for(pii x:Ax[i]) tr.update(x.fir,x.sec);
		for(ask x:Aq[i]) ans[x.id]+=x.op*tr.query(x.y); 
	}
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;i++){
		cnt[i]=read();
		for(int j=1;j<=cnt[i];j++){
			short x=read(),y=read();int w=read();
			a[i][j]=(node){x,y,w};
		}
	}
	for(int i=1;i<=k;i++) vis[i]=1;
	q=read();
	while(q--){
		string op;cin>>op;
		if(op[0]=='S'){
			int x=read();
			vis[x]^=1;
		}else{
			short sx=read(),sy=read(),fx=read(),fy=read();
			tot++;
			for(int i=1;i<=k;i++){
				if(vis[i]){
					Q[i].eb((ask){tot,fx,fy,1});
					Q[i].eb((ask){tot,sx-1,fy,-1});
					Q[i].eb((ask){tot,fx,sy-1,-1});
					Q[i].eb((ask){tot,sx-1,sy-1,1});
				}
			}
		}
	}
	for(int i=1;i<=k;i++) solve(i);
	for(int i=1;i<=tot;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：wosile (赞：0)

非常 trivial 的数据结构题，为什么是紫呢。

只有 2000 个 garland 和 2000 个询问，所以我们处理一下每次询问的时候这些 garland 是不是亮的，然后再算一下每一对 （garland，询问）的交集的权值和就行。

具体来讲，交集的权值和可以直接差分然后树状数组二维数点。

就没了，记 $r$ 为询问次数，时间复杂度 $O(q+kr\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,Q; 
int len[2005];
typedef long long ll;
struct bulb{
	int x,y,w;
	bulb(){}
	bulb(int x,int y,int w):x(x),y(y),w(w){} 
	bool operator <(const bulb &o)const{
		if(x!=o.x)return x<o.x;
		return y<o.y;
	}
}a[2005][2005],qr[8005];
int on[2005];
int cnt=0;
int o[2005][2005];
ll c[2005],ans[2005];
void add(int x,int val){
	for(;x<=m;x+=(x&-x))c[x]+=val;
}
ll query(int x){
	ll ans=0;
	for(;x;x-=(x&-x))ans+=c[x];
	return ans;
} 
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&len[i]);
		for(int j=1;j<=len[i];j++)scanf("%d%d%d",&a[i][j].x,&a[i][j].y,&a[i][j].w);
		sort(a[i]+1,a[i]+len[i]+1);
		on[i]=1;
	}
	scanf("%d",&Q);
	while(Q--){
		char tmp[10];
		scanf("%s",tmp);
		if(tmp[0]=='S'){
			int x;
			scanf("%d",&x);
			on[x]^=1;
		}
		else{
			++cnt;
			int xl,yl,xr,yr;
			scanf("%d%d%d%d",&xl,&yl,&xr,&yr);
			qr[cnt*4-3]=bulb(xr,yr,cnt);
			qr[cnt*4-2]=bulb(xr,yl-1,-cnt);
			qr[cnt*4-1]=bulb(xl-1,yr,-cnt);
			qr[cnt*4-0]=bulb(xl-1,yl-1,cnt);
			for(int i=1;i<=k;i++)o[cnt][i]=on[i];
		}
	}
	sort(qr+1,qr+cnt*4+1);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=m;j++)c[j]=0;
		int pos=1;
		for(int j=1;j<=cnt*4;j++){
			while(pos<=len[i] && a[i][pos].x<=qr[j].x){
				add(a[i][pos].y,a[i][pos].w);
				pos++; 
			}
			int id=abs(qr[j].w);
			int k=o[id][i]*(qr[j].w<0?-1:1);
			ans[id]+=query(qr[j].y)*k;
		}
	}
	for(int i=1;i<=cnt;i++)printf("%lld\n",ans[i]);
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：sodalyghat (赞：0)

### 分析
此题中 $q$ 比较大，直接暴力修改肯定超时，但是注意到英文题面中有一句很重要的话，询问次数不多于 $2000$ 次。我们就可以把所有的操作先用类似于懒标记合并的形式存起来，到了询问操作的时候再统一更新，这样复杂度就对了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ac{
	const int MAXN = 2005;
	int n, m, k;
	long long ft[MAXN][MAXN];
	int lowbit(int x){
		return x & -x;
	}
	long long query(int x, int y){
		long long ans = 0;
		for(int i = x;i;i -= lowbit(i)){
			for(int j = y;j;j -= lowbit(j)){
				ans += ft[i][j];
			}
		}
		return ans; 
	}
	void change(int x, int y, int v){
		for(int i = x;i <= n;i += lowbit(i)){
			for(int j = y;j <= m;j += lowbit(j)){
				ft[i][j] += v;
			}
		}
	}
	long long ask(int x1, int y1, int x2, int y2){
		return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
	}
	struct node{
		int x, y, val;
	};
	vector<node> line[MAXN];
	int num[MAXN], now[MAXN], last[MAXN];
	int main(){
		int x, y, val;
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1;i <= k;i++){
			scanf("%d", &num[i]);
			now[i] = last[i] = 1;
			for(int j = 1;j <= num[i];j++){
				scanf("%d%d%d", &x, &y, &val);
				change(x, y, val);
				line[i].push_back((node){x, y, val});
			}
		}
		int q;
		char ch[10];
		scanf("%d", &q);
		for(int i = 1;i <= q;i++){
			scanf("%s", ch);
			if(ch[0] == 'A'){
				for(int j = 1;j <= k;j++){
					if(now[j] * last[j] == 1) continue;
					for(int kk = 0;kk < num[j];kk++){
						change(line[j][kk].x, line[j][kk].y, line[j][kk].val * now[j]);
					}
					last[j] = now[j];
				}
				int x1, y1, x2, y2;
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				printf("%lld\n", ask(x1, y1, x2, y2));
			}
			else{
				scanf("%d", &x);
				now[x] *= -1;
			}
		}
		return 0;
	}
} 
int main(){
	return ac::main();
}
```


---

## 作者：幻影星坚强 (赞：0)

一种很显然的想法就是运用数据结构对每次的操作在矩阵里进行修改，之后快速求和，可以通过二维树状数组进行求和

但是我们发现询问很大，所以不能每一次修改灯泡都进行修改

我们发现每一条链只有亮或不亮两种情况，所以可能两次询问之间我们可能进行了许多次多余的操作（如$+v-v+v-v$……）

所以因为询问次数较少，我们考虑在询问时再看每个灯的状态并将其加入图中或删去。

之后用二维树状数组求和即可

```
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
long long tree[2010][2010];
int n, m, k;
int pd[2010], b[2010];
void add(int x, int y, long long w)
{
	for (int i = x; i <= n; i += (i & (-i)))
	{
		for (int j = y; j <= m; j += (j & (-j)))
		{
			tree[i][j] += w;
		}
	}
}
struct qq
{
	int x, y;
	long long w;
};
vector<qq>v[2010];
long long que(int x, int y)
{
	long long ans = 0;
	for (int i = x; i > 0; i -= (i & (-i)))
	{
		for (int j = y; j > 0; j -= (j & (-j)))
		{
			ans += tree[i][j];
		}
	}
	return ans;
}
long long que1(int x1, int y1, int x2, int y2)
{
	return que(x2, y2) - que(x1 - 1, y2) - que(x2, y1 - 1) + que(x1 - 1, y1 - 1);
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; ++ i)
	{
		int x;
		scanf("%d", &x);
		for (int j = 1; j <= x; ++ j)
		{
			int x, y;
			long long w;
			qq gu;
			scanf("%d%d%lld", &x, &y, &w);
			gu.x = x;
			gu.y = y;
			gu.w = w;
			v[i].push_back(gu);
			add(x, y, w);
		}
	}
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++ i)
	{
		char c[10];
		scanf("%s", c);
		if(c[0] == 'A')
		{
			for (int i = 1; i <= k; ++ i)
			{
				if(pd[i] != b[i])
				{
					int s = v[i].size();
					for (int j = 0; j < s; ++ j)
					{
						int x = v[i][j].x, y = v[i][j].y, w = v[i][j].w;
						if(b[i] == 0)
						w *= -1;
						add(x, y, w);
					}
				}
				b[i] = pd[i];
			}
			int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			printf("%lld\n", que1(x1, y1, x2, y2));
		}
		else
		{
			int s;
			scanf("%d", &s);
			pd[s] ^= 1;
		}
	}
	
}
```


---

