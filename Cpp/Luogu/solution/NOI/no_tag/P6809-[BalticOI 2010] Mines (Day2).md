# [BalticOI 2010] Mines (Day2)

## 题目背景

**本题为提交答案题，输入公开，请见题目附件。**

## 题目描述

给定一个 $H\times W$ 的矩阵 A，矩阵 A 中的每个数都等于矩阵 B 中相同位置四周八个方向的 `X` 加上该位置的 `X` 的个数。

请构造任意一种由 `.` 和 `X` 组成的满足题意的 $H\times W$ 的矩阵 B.

## 说明/提示

对于 $100\%$ 的数据，保证 $1\le H,W\le 600$，始终有方案存在。

**题目译自 [BalticOI 2010](https://www.luogu.com.cn/problem/U126003) [Day2](https://boi.cses.fi/files/boi2010_day2.pdf) *T3 Mines***。

## 样例 #1

### 输入

```
3 5
24531
46631
34310```

### 输出

```
.XXX.
.XX..
XX...
```

# 题解

## 作者：Judgelight (赞：6)

假设没有雷为 $0$，有雷为 $1$。

我们首先去枚举 $(1,1)$ 这个位置的值，我们设它是 $z$，套用主元法，设第一列的所有位置 $(i,1)$ 的值为 $a_{i-1}$，第一行的所有位置 $(1,i)$ 的值为 $b_{i-1}$，忽略所有常数，以 $4\times 4$ 的网格为例，我们可以得到下面这张表：



|$z$|$b_1$|$b_2$|$b_3$|
|:-:|:-:|:-:|:-:|
|$a_1$|$-a_1-b_1$|$-b_2$|$a_1-b_3$|
|$a_2$|$-a_2$|$0$|$a_2$|
|$a_3$|$-a_3+b_1$|$b_2$|$a_3+b_3$|

打表可以发现每个位置只与它所在行列对应的 $a,b$ 有关，且系数绝对值不超过 $1$，所以我们的限制本质上是 $a_i\pm b_i\in [l,r]$。我们还有一个限制就是 $a_i,b_i\in [0,1]$。这启示我们把这个东西拿来跑 2-SAT。

还有一个问题是关于最后一行和最后一列的限制我们是没有用到的，这个地方单独处理，算出来一些 $a_i,b_i$，把它们当做常数即可，时间复杂度为严格的 $O(nm)$，但是带大概 $8$ 的常数。

代码（仅供参考）：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define mk make_pair
#define N 2009
#define Abs(x) ((x)>0?x:-x)
#define _2 0x3f3f3f3f
using namespace std;
inline char nc(){ static char buf[1000000],*p=buf,*q=buf; return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++; } inline int rd(){ int res = 0; char c = nc(); while(c<'0'||c>'9')c=nc(); while(c<='9'&&c>='0')res=res*10+c-'0',c=nc(); return res; } char obuf[1<<21],*p3=obuf; inline void pc(char c){ p3-obuf<=(1<<20)?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c); } inline void wt(int x){ if(x<0) pc('-'),x=-x; if(x>9) wt(x/10); pc(x%10+'0'); }
const int dx[9]={-1,-1,-1,0,0,0,1,1,1},dy[9]={-1,0,1,-1,0,1,-1,0,1};
int n,m,a[N][N];char c[N][N];
pair<int,int>p[N][N];int r[N][N];
int va[N],vb[N];
vector<int>aa[N<<1],bb[N<<1];int X[N<<1];int idx;bool del[N<<1];
struct sat2{
	#undef N
	#define N 8009
	#define M 10000009
	#define g(a,b) (a+(b?0:n))
	int n,m;bitset<N>e[N];
	inline void add(int u,int v){e[u][v]=1;}
	int stk[N],top,instk[N],dfn[N],low[N],timestamps,id[N],scnt;
	void tarjan(int u){
		stk[++top]=u,instk[u]=1,dfn[u]=low[u]=++timestamps;
		for(int v=e[u]._Find_first();v!=e[u].size();v=e[u]._Find_next(v)){
			if(!dfn[v]){
				tarjan(v),low[u]=min(low[u],low[v]);
			}
			else if(instk[v])low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			int v;scnt++;
			do{
				v=stk[top--],instk[v]=0;
				id[v]=scnt;
			}
			while(v!=u);
		}
	}
	inline void add(int p,int a,int q,int b){add(g(p,a),g(q,b));}
	int c[N];
	bool solve(int n){
		for(int i=1;i<=(n<<1);i++)if(!dfn[i])tarjan(i);
		for(int i=1;i<=n;i++)if(id[g(i,0)]==id[g(i,1)])return 0;
		for(int i=1;i<=n;i++)c[i]=id[g(i,1)]<id[g(i,0)];
		return 1;
	}
	void clean(){
		for(int i=1;i<=(n<<1);i++)e[i].reset();
		memset(stk,0,sizeof(stk)),top=0,memset(instk,0,sizeof(instk)),memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low)),timestamps=0,memset(id,0,sizeof(id)),scnt=0;
	}
}T;
signed main(){
	//freopen("ex_minesweeper5.in","r",stdin);
	//freopen("Misaka.txt","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<=n;i++)va[i]=_2;for(int i=1;i<=m;i++)vb[i]=_2;
	for(int i=1;i<=n;i++){
		char ch=nc();
		while(ch<'0'||ch>'9')ch=nc();
		int nw=0;
		while(ch>='0'&&ch<='9'){
			c[i][++nw]=ch,ch=nc();
		}
		for(int j=1;j<=m;j++)a[i][j]=c[i][j]-'0';
	}
	r[1][1]=0;
	for(int i=2;i<=n;i++)p[i][1]=mk(i-1,0);
	for(int i=2;i<=m;i++)p[1][i]=mk(0,i-1);
	for(int i=2;i<=n;i++){
		for(int j=2;j<=m;j++){
			int x=a[i-1][j-1];
			for(int t=0;t<9;t++){
				int ii=i-1+dx[t],jj=j-1+dy[t];
				if(ii<=0||jj<=0||ii>n||jj>m||(ii==i&&jj==j))continue;
				p[i][j].first-=p[ii][jj].first,p[i][j].second-=p[ii][jj].second;
				x-=r[ii][jj];
			}
			r[i][j]=x;
		}
	}
	for(int i=1;i<=n;i++){
		map<int,int>ma,mb;idx++;X[idx]=a[i][m];
		for(int t=0;t<9;t++){
			int ii=i+dx[t],jj=m+dy[t];
			if(ii<=0||jj<=0||ii>n||jj>m)continue;
			ma[Abs(p[ii][jj].first)]+=p[ii][jj].first,mb[Abs(p[ii][jj].second)]+=p[ii][jj].second;
			X[idx]-=r[ii][jj];
		}
		for(auto x:ma){
			if(x.second!=0)aa[idx].eb(x.second);
		}
		for(auto x:mb){
			if(x.second!=0)bb[idx].eb(x.second);
		}
	}
	for(int i=1;i<=m;i++){
		map<int,int>ma,mb;idx++;X[idx]=a[n][i];
		for(int t=0;t<9;t++){
			int ii=n+dx[t],jj=i+dy[t];
			if(ii<=0||jj<=0||ii>n||jj>m)continue;
			ma[Abs(p[ii][jj].first)]+=p[ii][jj].first,mb[Abs(p[ii][jj].second)]+=p[ii][jj].second;
			X[idx]-=r[ii][jj];
		}
		for(auto x:ma){
			if(x.second!=0)aa[idx].eb(x.second);
		}
		for(auto x:mb){
			if(x.second!=0)bb[idx].eb(x.second);
		}
	}
	for(int t=1;;t++){
		bool flag=0;
		for(int i=1;i<=idx;i++){
			if(del[i])continue;
			vector<int>a,b;int Y=X[i];
			for(auto x:aa[i]){
				if(va[Abs(x)]!=_2)Y-=(x/Abs(x))*va[Abs(x)];
				else a.eb(x);
			}
			for(auto x:bb[i]){
				if(vb[Abs(x)]!=_2)Y-=(x/(Abs(x)))*vb[Abs(x)];
				else b.eb(x);
			}
			if(a.size()==1&&b.size()==0){
				flag=1;
				del[i]=1;va[Abs(a[0])]=(a[0]/Abs(a[0]))*Y;
				aa[i]=a,bb[i]=b,X[i]=Y;
				continue;
			}
			if(b.size()==1&&a.size()==0){
				flag=1;
				del[i]=1;vb[Abs(b[0])]=(b[0]/Abs(b[0]))*Y;
				aa[i]=a,bb[i]=b,X[i]=Y;
				continue;
			}
			aa[i]=a,bb[i]=b,X[i]=Y;
		}
		if(!flag)break;
	}
	bool flag=0;
	for(int i=1;i<n;i++)if(va[i]!=_2&&va[i]!=0&&va[i]!=1){flag=1;break;}
	for(int i=1;i<m;i++)if(vb[i]!=_2&&vb[i]!=0&&vb[i]!=1){flag=1;break;}
	if(!flag){
		T.n=n+m-2;
		for(int i=1;i<n;i++)if(va[i]!=_2)T.add(i,va[i]^1,i,va[i]);
		for(int i=1;i<m;i++)if(vb[i]!=_2)T.add(i+n-1,vb[i]^1,i,vb[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(p[i][j].first!=0&&va[Abs(p[i][j].first)]!=_2){
					r[i][j]+=(p[i][j].first/Abs(p[i][j].first))*va[Abs(p[i][j].first)],p[i][j].first=0;
				}
				if(p[i][j].second!=0&&vb[Abs(p[i][j].second)]!=_2){
					r[i][j]+=(p[i][j].second/Abs(p[i][j].second))*vb[Abs(p[i][j].second)],p[i][j].second=0;
				}
				if(p[i][j].first==0&&p[i][j].second==0)continue;
				if(p[i][j].second==0){
					int L=0-r[i][j],R=1-r[i][j];if(p[i][j].first<0)L=-L,R=-R,swap(L,R);
					int x=Abs(p[i][j].first);
					if(L==1)T.add(x,0,x,1);
					if(R==0)T.add(x,1,x,0);
				}
				else if(p[i][j].first==0){
					int L=0-r[i][j],R=1-r[i][j];if(p[i][j].second<0)L=-L,R=-R,swap(L,R);
					int x=Abs(p[i][j].second)+n-1;
					if(L==1)T.add(x,0,x,1);
					if(R==0)T.add(x,1,x,0);
				}
				else{
					int x=Abs(p[i][j].first),y=Abs(p[i][j].second)+n-1;int L=0-r[i][j],R=1-r[i][j];
					if(p[i][j].first>0&&p[i][j].second>0){
						if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,x+y!=0
						if(1<L||1>R)T.add(x,0,y,0);//x=0,y!=1,x+y!=1
						if(1<L||1>R)T.add(x,1,y,1);//x=1,y!=0,x+y!=1
						if(2<L||2>R)T.add(x,1,y,0);//x=1,y!=1,x+y!=2
						//
						if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,x+y!=0
						if(1<L||1>R)T.add(y,0,x,0);//y=0,x!=1,x+y!=1
						if(1<L||1>R)T.add(y,1,x,1);//y=1,x!=0,x+y!=1
						if(2<L||2>R)T.add(y,1,x,0);//y=1,x!=1,x+y!=2
					}
					else if(p[i][j].first>0&&p[i][j].second<0){
						if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,x-y!=0
						if(-1<L||-1>R)T.add(x,0,y,0);//x=0,y!=1,x-y!=-1
						if(1<L||1>R)T.add(x,1,y,1);//x=1,y!=0,x-y!=1
						if(0<L||0>R)T.add(x,1,y,0);//x=1,y!=1,x-y!=0
						//
						if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,x-y!=0
						if(1<L||1>R)T.add(y,0,x,0);//y=0,x!=1,x-y!=1
						if(-1<L||-1>R)T.add(y,1,x,1);//y=1,x!=0,x-y!=-1
						if(0<L||0>R)T.add(y,1,x,0);//y=1,x!=1,x-y!=0
					}
					else if(p[i][j].first<0&&p[i][j].second>0){
						if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,y-x!=0
						if(-1<L||-1>R)T.add(y,0,x,0);//y=0,x!=1,y-x!=-1
						if(1<L||1>R)T.add(y,1,x,1);//y=1,x!=0,y-x!=1
						if(0<L||0>R)T.add(y,1,x,0);//y=1,x!=1,y-x!=0
						//
						if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,y-x!=0
						if(1<L||1>R)T.add(x,0,y,0);//x=0,y!=1,y-x!=1
						if(-1<L||-1>R)T.add(x,1,y,1);//x=1,y!=0,y-x!=-1
						if(0<L||0>R)T.add(x,1,y,0);//x=1,y!=1,y-x!=0
					}
					else{
						if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,-x-y!=0
						if(-1<L||-1>R)T.add(x,0,y,0);//x=0,y!=1,-x-y!=-1
						if(-1<L||-1>R)T.add(x,1,y,1);//x=1,y!=0,-x-y!=-1
						if(-2<L||-2>R)T.add(x,1,y,0);//x=1,y!=1,-x-y!=-2
						//
						if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,-x-y!=0
						if(-1<L||-1>R)T.add(y,0,x,0);//y=0,x!=1,-x-y!=-1
						if(-1<L||-1>R)T.add(y,1,x,1);//y=1,x!=0,-x-y!=-1
						if(-2<L||-2>R)T.add(y,1,x,0);//y=1,x!=1,-x-y!=-2
					}
				}
			}
		}
		if(T.solve(n+m-2)){
			for(int i=1;i<n;i++)va[i]=T.c[i];
			for(int i=1;i<m;i++)vb[i]=T.c[i+n-1];
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					int x=r[i][j];
					if(p[i][j].first)x+=va[Abs(p[i][j].first)]*(p[i][j].first/Abs(p[i][j].first));
					if(p[i][j].second)x+=vb[Abs(p[i][j].second)]*(p[i][j].second/(Abs(p[i][j].second)));
					x==0?pc('0'):pc('1');
				}
				pc('\n');
			}
			fwrite(obuf,p3-obuf,1,stdout);
			return 0;
		}
	}
	/////////////////////////////////////////////////////////////////
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)p[i][j]=mk(0,0);for(int i=1;i<=n+m;i++)aa[i].clear(),bb[i].clear(),X[i]=0,del[i]=0;idx=0;
	T.clean();
	memset(r,0,sizeof(r)),memset(va,0,sizeof(va)),memset(vb,0,sizeof(vb));
	for(int i=1;i<=n;i++)va[i]=_2;for(int i=1;i<=m;i++)vb[i]=_2;
	r[1][1]=1;
	for(int i=2;i<=n;i++)p[i][1]=mk(i-1,0);
	for(int i=2;i<=m;i++)p[1][i]=mk(0,i-1);
	for(int i=2;i<=n;i++){
		for(int j=2;j<=m;j++){
			int x=a[i-1][j-1];
			for(int t=0;t<9;t++){
				int ii=i-1+dx[t],jj=j-1+dy[t];
				if(ii<=0||jj<=0||ii>n||jj>m||(ii==i&&jj==j))continue;
				p[i][j].first-=p[ii][jj].first,p[i][j].second-=p[ii][jj].second;
				x-=r[ii][jj];
			}
			r[i][j]=x;
		}
	}
	for(int i=1;i<=n;i++){
		map<int,int>ma,mb;idx++;X[idx]=a[i][m];
		for(int t=0;t<9;t++){
			int ii=i+dx[t],jj=m+dy[t];
			if(ii<=0||jj<=0||ii>n||jj>m)continue;
			ma[Abs(p[ii][jj].first)]+=p[ii][jj].first,mb[Abs(p[ii][jj].second)]+=p[ii][jj].second;
			X[idx]-=r[ii][jj];
		}
		for(auto x:ma){
			if(x.second!=0)aa[idx].eb(x.second);
		}
		for(auto x:mb){
			if(x.second!=0)bb[idx].eb(x.second);
		}
	}
	for(int i=1;i<=m;i++){
		map<int,int>ma,mb;idx++;X[idx]=a[n][i];
		for(int t=0;t<9;t++){
			int ii=n+dx[t],jj=i+dy[t];
			if(ii<=0||jj<=0||ii>n||jj>m)continue;
			ma[Abs(p[ii][jj].first)]+=p[ii][jj].first,mb[Abs(p[ii][jj].second)]+=p[ii][jj].second;
			X[idx]-=r[ii][jj];
		}
		for(auto x:ma){
			if(x.second!=0)aa[idx].eb(x.second);
		}
		for(auto x:mb){
			if(x.second!=0)bb[idx].eb(x.second);
		}
	}
	for(int t=1;;t++){
		bool flag=0;
		for(int i=1;i<=idx;i++){
			if(del[i])continue;
			vector<int>a,b;int Y=X[i];
			for(auto x:aa[i]){
				if(va[Abs(x)]!=_2)Y-=(x/Abs(x))*va[Abs(x)];
				else a.eb(x);
			}
			for(auto x:bb[i]){
				if(vb[Abs(x)]!=_2)Y-=(x/(Abs(x)))*vb[Abs(x)];
				else b.eb(x);
			}
			if(a.size()==1&&b.size()==0){
				flag=1;
				del[i]=1;va[Abs(a[0])]=(a[0]/Abs(a[0]))*Y;
				aa[i]=a,bb[i]=b,X[i]=Y;
				continue;
			}
			if(b.size()==1&&a.size()==0){
				flag=1;
				del[i]=1;vb[Abs(b[0])]=(b[0]/Abs(b[0]))*Y;
				aa[i]=a,bb[i]=b,X[i]=Y;
				continue;
			}
			aa[i]=a,bb[i]=b,X[i]=Y;
		}
		if(!flag)break;
	}
	T.n=n+m-2;
	for(int i=1;i<n;i++)if(va[i]!=_2)T.add(i,va[i]^1,i,va[i]);
	for(int i=1;i<m;i++)if(vb[i]!=_2)T.add(i+n-1,vb[i]^1,i,vb[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(p[i][j].first!=0&&va[Abs(p[i][j].first)]!=_2){
				r[i][j]+=(p[i][j].first/Abs(p[i][j].first))*va[Abs(p[i][j].first)],p[i][j].first=0;
			}
			if(p[i][j].second!=0&&vb[Abs(p[i][j].second)]!=_2){
				r[i][j]+=(p[i][j].second/Abs(p[i][j].second))*vb[Abs(p[i][j].second)],p[i][j].second=0;
			}
			if(p[i][j].first==0&&p[i][j].second==0)continue;
			if(p[i][j].second==0){
				int L=0-r[i][j],R=1-r[i][j];if(p[i][j].first<0)L=-L,R=-R,swap(L,R);
				int x=Abs(p[i][j].first);
				if(L==1)T.add(x,0,x,1);
				if(R==0)T.add(x,1,x,0);
			}
			else if(p[i][j].first==0){
				int L=0-r[i][j],R=1-r[i][j];if(p[i][j].second<0)L=-L,R=-R,swap(L,R);
				int x=Abs(p[i][j].second)+n-1;
				if(L==1)T.add(x,0,x,1);
				if(R==0)T.add(x,1,x,0);
			}
			else{
				int x=Abs(p[i][j].first),y=Abs(p[i][j].second)+n-1;int L=0-r[i][j],R=1-r[i][j];
				if(p[i][j].first>0&&p[i][j].second>0){
					if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,x+y!=0
					if(1<L||1>R)T.add(x,0,y,0);//x=0,y!=1,x+y!=1
					if(1<L||1>R)T.add(x,1,y,1);//x=1,y!=0,x+y!=1
					if(2<L||2>R)T.add(x,1,y,0);//x=1,y!=1,x+y!=2
					//
					if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,x+y!=0
					if(1<L||1>R)T.add(y,0,x,0);//y=0,x!=1,x+y!=1
					if(1<L||1>R)T.add(y,1,x,1);//y=1,x!=0,x+y!=1
					if(2<L||2>R)T.add(y,1,x,0);//y=1,x!=1,x+y!=2
				}
				else if(p[i][j].first>0&&p[i][j].second<0){
					if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,x-y!=0
					if(-1<L||-1>R)T.add(x,0,y,0);//x=0,y!=1,x-y!=-1
					if(1<L||1>R)T.add(x,1,y,1);//x=1,y!=0,x-y!=1
					if(0<L||0>R)T.add(x,1,y,0);//x=1,y!=1,x-y!=0
					//
					if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,x-y!=0
					if(1<L||1>R)T.add(y,0,x,0);//y=0,x!=1,x-y!=1
					if(-1<L||-1>R)T.add(y,1,x,1);//y=1,x!=0,x-y!=-1
					if(0<L||0>R)T.add(y,1,x,0);//y=1,x!=1,x-y!=0
				}
				else if(p[i][j].first<0&&p[i][j].second>0){
					if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,y-x!=0
					if(-1<L||-1>R)T.add(y,0,x,0);//y=0,x!=1,y-x!=-1
					if(1<L||1>R)T.add(y,1,x,1);//y=1,x!=0,y-x!=1
					if(0<L||0>R)T.add(y,1,x,0);//y=1,x!=1,y-x!=0
					//
					if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,y-x!=0
					if(1<L||1>R)T.add(x,0,y,0);//x=0,y!=1,y-x!=1
					if(-1<L||-1>R)T.add(x,1,y,1);//x=1,y!=0,y-x!=-1
					if(0<L||0>R)T.add(x,1,y,0);//x=1,y!=1,y-x!=0
				}
				else{
					if(0<L||0>R)T.add(x,0,y,1);//x=0,y!=0,-x-y!=0
					if(-1<L||-1>R)T.add(x,0,y,0);//x=0,y!=1,-x-y!=-1
					if(-1<L||-1>R)T.add(x,1,y,1);//x=1,y!=0,-x-y!=-1
					if(-2<L||-2>R)T.add(x,1,y,0);//x=1,y!=1,-x-y!=-2
					//
					if(0<L||0>R)T.add(y,0,x,1);//y=0,x!=0,-x-y!=0
					if(-1<L||-1>R)T.add(y,0,x,0);//y=0,x!=1,-x-y!=-1
					if(-1<L||-1>R)T.add(y,1,x,1);//y=1,x!=0,-x-y!=-1
					if(-2<L||-2>R)T.add(y,1,x,0);//y=1,x!=1,-x-y!=-2
				}
			}
		}
	}
	if(T.solve(n+m-2)){
		for(int i=1;i<n;i++)va[i]=T.c[i];
		for(int i=1;i<m;i++)vb[i]=T.c[i+n-1];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x=r[i][j];
				if(p[i][j].first)x+=va[Abs(p[i][j].first)]*(p[i][j].first/Abs(p[i][j].first));
				if(p[i][j].second)x+=vb[Abs(p[i][j].second)]*(p[i][j].second/(Abs(p[i][j].second)));
				x==0?pc('0'):pc('1');
			}
			pc('\n');
		}
		fwrite(obuf,p3-obuf,1,stdout);
		return 0;
	}
	return 0;
}
```

---

## 作者：老莽莽穿一切 (赞：4)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16777418.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/P6809)

[**loj link**](https://loj.ac/p/2681)

提供一种时间复杂度正确的高妙做法。

首先题目有一条隐藏条件是保证 $n\not\equiv2\pmod3$ 或 $m\not\equiv2\pmod3$，需要通过观察数据得到。

我们钦定 $n\not\equiv2\pmod3$，如果不满足则沿主对角线翻转使其满足。

接下来我们令 $a_{i,j}$ 表示原给定数字表格上第 $i$ 行第 $j$ 列的值，$(i,j)$ 表示第 $i$ 行第 $j$ 列是否有雷。

首先考虑一种特殊情况，$a_{x,y}+a_{x+1,y+1}-a_{x,y+1}-a_{x+1,y}=(x-1,y-1)+(x+2,y+2)-(x-1,y+2)-(x+2,y-1)$，即对于一个 $2\times2$ 的方格，若我们已知其三个角，我们可以直接求得另外一个角。

思路非常巧妙，首先确定第 $3$ 行。

利用前面的特殊情况可以递推求出所有 $(3,3k)$，接下来求别的，需要对 $m$ 分类讨论。

若 $m\not\equiv2\pmod3$，我们将整个图水平翻转，再做一遍，则第三行任意三个相邻的位置只有一个未知，可以直接求。

若 $m\equiv2\pmod3$，此时我们将第三行中所有未知的位置取出来排成一列，任意两个相邻位置的和都是已知的，若有 $2$ 或 $0$，两个就都确定了，若全都是 $1$，则我们发现任意两个相邻的位置里只要有一个雷就好了，所以直接任意确定一组没有关系。

以此类推，当第 $3$ 行已知后，将第 $3$ 行对全图的影响消去，第 $6$ 行的情况就等价于原来的第三行，以此类推求得所有第 $3k$ 行。

因为保证了 $n\not\equiv2\pmod3$，竖直翻转后重新求一遍则所有未知行两两之间隔了两行，不会互相影响，即可以独立求。

求一个 $1\times m$ 的矩阵非常简单，直接和上面求第 $3$ 行类似做就好了。

最佳实现时间复杂度是 $\mathcal O\left(nm\right)$。

实现上因为全图翻转是 $\mathcal O\left(nm\right)$ 的，所以上面讲到做第 $3$ 行时翻转，实际上不能做一次翻一次，时间复杂度会退化，因为上面讲到特殊情况中有影响的实际上只有四个顶点，那么只要全部一起做就可以只反翻转一次。

细节较多，一个比较好的实现是每确定一个雷就将它在图中的影响消去，写起来会相对简单。

[c++代码](https://www.cnblogs.com/LaoMang-no-blog/p/16777418.html)

---

## 作者：WrongAnswer_90 (赞：1)

# [My Blogs](https://wronganswer90.github.io/2024/10/24/P6809-BalticOI-2010-Day2-Mines)

### [P6809 [BalticOI 2010 Day2] Mines](https://www.luogu.com.cn/problem/P6809)

17k 的含金量。

设 $c_{i,j}$ 表示答案，$a_{i,j}$ 表示输入数据。

首先可以确定 $c_{3,3}=a_{2,2}-a_{2,1}-a_{1,2}+a_{1,1}$，

用二维差分可以知道 $c_{i,j},c_{i-3,j},c_{i,j-3},c_{i-3,j-3}$ 的关系，这样就能推出来 $c_{a,b}$，其中 $a,b\equiv 0\pmod 3$。

这样利用了左上角的东西，然后右上右下左下也是一样的，所以可以确定出来 $i\equiv 0/n-2\pmod 3$，$j\equiv 0/m-2\pmod 3$ 的所有格子 $c_{i,j}$。

然后如果 $n-2,m-2$ 都不是 $3$ 的倍数，这样就知道了整个矩阵：

![image.png](https://s2.loli.net/2024/10/12/ht2IxNgw8bKSDP7.png)

黑色格子是上面知道的。知道了所有黑色格子之后深灰色的格子也是可以求出来的（依靠同一条边边上两个相邻 $a$ 的差分可以知道相邻两个格子的和，如 C2 和 C1 的和就是 $a_{1,2}-a_{1,1}$，然后 C1 因为已经知道了，所以也能知道 C2）。最后在填浅灰色的格子，没填的直接给他填上就行了。

对于 $n-2$ 不是 $3$ 的倍数但是 $m-2$ 是的情况，首先画出来能直接确定的格子：

![image.png](https://s2.loli.net/2024/10/12/yAJeGUq5phxKPIl.png)

还是用二维差分，观察能确定那些格子：

![image.png](https://s2.loli.net/2024/10/12/dt7H2rahc9LQB6F.png)

容易发现这样信息已经“满了”，即不可能再确定任何一个格子。但是这样可以用一维差分知道相邻两个数的和，也能知道跨过一条黑线的相邻两个数的和（如 $c_{3,1}+c_{3,2}+c_{3,3}=a_{2,2}-a_{1,2}$，然后 $c_{3,3}$ 已经确定，这样就能知道 $c_{3,1}+c_{3,2}$。然后 $c_{6,1}+c_{6,2}+c_{6,3}-c_{3,1}-c_{3,2}-c_{3,3}=a_{5,2}-a_{4,2}$，$c_{3}$ 的和也知道了，所以就能知道 $c_{6,1}$ 和 $c_{6,2}$ 的和......依此类推）。

然后显然只保留相邻两个数的和的限制就能满足原限制。所以如果和是 $0$ 或者 $2$ 就直接填，这样图上会剩若干条链，链上满足相邻的都是 $01,10$ 即可。

对于 $n-2,m-2\equiv 0\pmod 3$：

![image.png](https://s2.loli.net/2024/10/12/UTPWz3laCLEc4vs.png)

十分不牛，只能确定一些单点的确切值。但是相邻两个浅灰色格子的和以及跨过一个黑色格子的两个相邻浅灰色格子的和都是知道的，所以可以用和第二种情况类似的方法确定出灰色格子的和的。

![image.png](https://s2.loli.net/2024/10/12/wtkbY5eKlc8vSjm.png)

然后这样只能知道相邻四个的一个田字格的数的和了，忽然发现这个是经典问题[矩阵游戏](https://www.luogu.com.cn/problem/P7515)的弱化版，直接粘个 spfa 上来就过了。

---

## 作者：7KByte (赞：1)

> 给定一个 $N\times M$ 的矩阵 $A$，你需要构造一个 $0/1$ 矩阵 $B$，满足 $A_{i,j}$ 恰好等于它自己和相邻 $8$ 个位置的 $B$ 的和。

很适合比赛的一道提交答案题。

我们发现非常类似扫雷游戏，那么我们考虑从一个方向递推过去。

首先枚举左上角四个格子中的数，最多有 $16$ 种情况，然后枚举第一行和第一列的数，那么剩下的位置可以被我们 $N\times M$ 递推出来。

直接枚举是 $2^{N+M}$ 的，$N,M$ 非常大，这辈子都跑不完，同时这是提交答案题，我们可以考虑各种复杂度是不那么优秀的算法。

我们先写成搜索的构架，然后考虑慢慢优化。包括优化搜索顺序，我们按搜一行然后搜一列的方式交替搜索行和列。对于当前位置不合法及时返回。以及在枚举左上角后，预处理每一行和每一列的起始。

直接跑还是很慢，我们发现将地图旋转或翻转后答案本质不变，所以我们可以将地图转化为 $8$ 个本质相同的地图，开多个程序同时跑即可。同时观察数据点，可以预处理下哪些行的 $1$ 多，哪些列的 $1$ 多。时间最长的点 $6$ 号点也就跑了 $5$ 分钟。个人认为 $6$ 号点时间长是因为 $N,M$ 的差比较大，并且 $N,M$ 都 $\ge 100$。

以下是参考代码，但只用这一份代码是无法跑出所有测试点的。

```cpp
#define N 605
int n, m, a[N][N], u[N][N], f[N][N]; char ch[N];
int r[N], c[N];
inline bool check(int x,int y,int op){
	if(y > m || (x <= n && x <= y)){
		u[x][1] = op, u[x][2] = r[x] - op;
		if(u[x][2] < 0 || u[x][2] > 1)return false;
		rep(i, 3, y - 1){
			u[x][i] = a[x - 1][i - 1] - f[x - 1][i - 1] - u[x][i - 2] - u[x][i - 1] - u[x - 1][i] - u[x - 2][i];
			if(u[x][i] < 0 || u[x][i] > 1)return false;
			f[x][i] = u[x][i] + u[x][i - 1] + u[x - 1][i] + u[x - 1][i - 1];
			if(x == n && f[x][i] + u[x][i - 2] + u[x - 1][i - 2] != a[x][i - 1])return false;
		}
		if(y > m && f[x][m] + u[x - 2][m] + u[x - 2][m - 1] != a[x - 1][m])return false;
	}
	else{
		u[1][y] = op, u[2][y] = c[y] - op;
		if(u[2][y] < 0 || u[2][y] > 1)return false;
		rep(i, 3, x - 1){
			u[i][y] = a[i - 1][y - 1] - f[i - 1][y - 1] - u[i - 2][y] - u[i - 1][y] - u[i][y - 1] - u[i][y - 2];
			if(u[i][y] < 0 || u[i][y] > 1)return false;
			f[i][y] = u[i][y] + u[i][y - 1] + u[i - 1][y] + u[i - 1][y - 1];
			if(y == m && f[i][y] + u[i - 2][y] + u[i - 2][y - 1] != a[i - 1][y])return false;
		}
		if(x > n && f[n][y] + u[n][y - 2] + u[n - 1][y - 2] != a[n][y - 1])return false;
	}
	return true;
}
void dfs(int x,int y){
	if(x > n && y > m){
		if(f[n][m] == a[n][m]){
			rp(i, n){rp(j, m)if(u[i][j])pc('X'); else pc('.'); el;}
			exit(0);
		}return ;
	}
	if(y > m || (x <= n && x <= y)){
		if(check(x, y, 0))dfs(x + 1, y);
		if(check(x, y, 1))dfs(x + 1, y);
	}
	else{
		if(check(x, y, 0))dfs(x, y + 1);
		if(check(x, y, 1))dfs(x, y + 1);
	}
}
int main() {
	read(n, m);
	rp(i, n){
		scanf("%s", ch + 1);
		rp(j, m)a[i][j] = ch[j] - '0';
	}
	rep(s, 0, 15)if(a[1][1] == __builtin_popcount(s)){
		u[1][1] = s & 1, u[1][2] = (s >> 1) & 1, 
		u[2][1] = (s >> 2) & 1, u[2][2] = (s >> 3) & 1;
		r[1] = u[1][1] + u[1][2], r[2] = u[2][1] + u[2][2];
		c[1] = u[1][1] + u[2][1], c[2] = u[1][2] + u[2][2];
		bool flag = true;
		rep(i, 3, n)r[i] = a[i - 1][1] - (a[i - 2][1] - r[i - 3]), flag &= r[i] >= 0 && r[i] <= 2;
		rep(i, 3, m)c[i] = a[1][i - 1] - (a[1][i - 2] - c[i - 3]), flag &= c[i] >= 0 && c[i] <= 2;
		if(!flag)continue;
		rep(i, 2, n)f[i][2] = r[i] + r[i - 1];
		rep(i, 2, m)f[2][i] = c[i] + c[i - 1];
		if(a[n][1] == f[n][2] && a[1][m] == f[2][m])dfs(3, 3);
	}
	return 0;
}
/*
4 4
2332
3442
3331
3320
1 1 1 0
0 0 0 1
0 1 0 0
1 1 0 0
*/
```



---

