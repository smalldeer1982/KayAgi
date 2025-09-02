# [PA 2017] 摆砖 / Carcassonne

## 题目背景

译自 [Potyczki Algorytmiczne 2017](https://sio2.mimuw.edu.pl/c/pa-2017-1/p/) R5 Carcassonne [B] (CAR)。$\texttt{5s,256M}$。


## 题目描述


给定一块 $n\times n$ 的棋盘，上面可能已经放了若干块 $1\times 1$ 的砖。

现在要再放置 $k$ 块 $1\times 1$ 砖。如果放置的砖不是这个棋盘上的第一块砖，则要求放置的这块砖必须和之前棋盘上有的砖至少有一条公共边。

求方案数对 $(10^9+7)$ 取模后的结果。

称两个方案是不同的，当且仅当存在一个格子，仅在一个方案中放了砖。

## 说明/提示


- $2\le n\le 3\times 10^3$；
- $1\le k\le 4$。


## 样例 #1

### 输入

```
3 2
.#.
##.
#..```

### 输出

```
8```

# 题解

## 作者：D2T1 (赞：1)

不太像题。

关键想法是枚举新增的 $k$ 个点距离最近 $\texttt{\#}$ 点的曼哈顿距离（设为 $dis_{i,j}$）。

### $k=1$。

任意一个 $dis=1$ 的点都可以。

### $k=2$。

两种情况：两个 $dis=1$ 的点，一个 $dis=1$ 的点和与之相邻的一个 $dis=2$ 的点。

### $k=3$。

$dis$ 集合有四种情况：

1. $\{1,1,1\}$：任选三个 $dis=1$ 的点。
2. $\{1,1,2\}$：枚举这个 $dis=2$ 的点，分类讨论那两个 $dis=1$ 是否都与这个点相邻。
3. $\{1,2,2\}$：枚举这个 $dis=1$ 的点，任选两个与之相邻的 $dis=2$ 的点。
4. $\{1,2,3\}$：枚举这个 $dis=2$ 的点，任选与之相邻的一个 $dis=1,dis=3$ 的点。

### $k=4$。

$dis$ 集合有八种情况：

1. $\{1,1,1,1\}$：任选四个 $dis=1$ 的点。
2. $\{1,1,1,2\}$：枚举这个 $dis=2$ 的点，分类讨论那三个 $dis=1$ 的点有几个与这个点相邻。
3. $\{1,1,2,2\}$：最难的一种情况。有两种子情况：首先，两个 $2$ 都与选择的 $1$ 有相邻，对于大部分情况，可以选择的 $2$ 集合大小等于两个 $1$ 的 $2$ 邻域大小之和，特例是两个 $1$ 点距离为 $2$，特判一下就可以；其次，存在一个 $2$ 不与选择的那两个 $1$ 相邻，那么枚举另一个 $2$，选择它旁边的一个 $1$ 一个 $2$ 后，计算与前者 $2$ 不相邻的 $1$ 个数即可。
4. $\{1,1,2,3\}$：枚举这个 $dis=2$ 的点，分类讨论那两个 $dis=1$ 是否都与这个点相邻，因为 $dis=3$ 的点一定与它相邻。
5. $\{1,*,*,*\}$： 这里实际上可以列出四种情况，但是它们可以一起处理，因为此时有性质：这四个点**一定形成一个四连通块**。那么枚举所有 $19$ 种四连块，判断它们的 $dis$ 集合是否合法即可。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11808)

**题目大意**

>给定 $n\times n$ 网格，有一些格子是黑色的，每次操作可以选择一个和黑色格子相邻的白格染黑，求 $k$ 此操作能生成多少种本质不同的图案。
>
>数据范围：$n\le 3000,k\le 4$。

**思路分析**

把所有格子按距离初始黑格的最短路分类，然后分讨染黑的格子的距离，容易解决 $k\le 3$ 的情况。

对于 $k=4$ 的情况，大部分都是平凡的，比较特殊的只有 $1122,1222,1223$ 三种情况，需要一定的特殊处理。

$1222$ 和 $1223$ 两种情况类似，我们分讨构成的树形态即可处理，注意特判 $\begin{bmatrix}1&2\\2&2\end{bmatrix}$ 和 $\begin{bmatrix}1&2\\2&3\end{bmatrix}$，只有这两种图形会会重复计数。

然后是 $1122$，我们先考虑两个 $2$ 分别和某个 $1$ 相邻的情况：

此时可以容斥，钦定零个或一个 $2$ 不与 $1$ 相邻可以简单计数，但钦定两个 $2$ 都不和 $1$ 相邻的问题有点困难。

设每个 $2$ 邻域中 $1$ 的集合为 $s_1\sim s_k$，$1$ 的总数为 $c$，那么所求即为 $\sum_{i<j}\binom{c-|s_i\cup s_j|}{2}$。

枚举 $i$，注意到大部分 $|s_i\cup s_j|=|s_i|+|s_j|$，又因为 $|s_i|\le 4$，因此对于每个可能的 $v\in[0,4]$，预处理 $\sum_i\binom{c-v-|s_i|}2$。

然后我们特殊处理掉 $j=i$ 以及 $s_i\cap s_j$ 非空的情况，注意到后者对应的两个点的曼哈顿距离一定 $=2$，可以直接枚举出来。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005,MAXS=1e7+5,MOD=1e9+7,i2=(MOD+1)/2,dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char mp[MAXN][MAXN],ds[MAXN][MAXN],w[MAXN][MAXN][5];
int n,ty,m,ct[5];
vector <array<short,2>> f[5];
ll C(int x,int y) {
	if(x<0||y<0||y>x) return 0;
	__int128 p=1;
	for(int i=0;i<y;++i) p*=x-i;
	for(int i=0;i<y;++i) p/=i+1;
	return p%MOD;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>ty,memset(ds,-1,sizeof(ds));
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) {
		cin>>mp[i][j],ds[i][j]=(mp[i][j]=='#'?0:5);
	}
	for(int z=1;z<=4;++z) {
		for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) if(ds[i][j]>z) {
			for(int k:{0,1,2,3}) {
				int x=i+dx[k],y=j+dy[k];
				if(x<1||x>n||y<1||y>n) continue;
				if(ds[x][y]==z-1) { ds[i][j]=z; break; }
			}
			if(ds[i][j]==z) {
				++ct[z],f[z].push_back({short(i),short(j)});
				for(int k:{0,1,2,3}) {
					int x=i+dx[k],y=j+dy[k];
					if(x<1||x>n||y<1||y>n) continue;
					++w[x][y][z];
				}
				
			}
		}
	}
	if(ty==1) {
		cout<<ct[1]<<"\n";
		return 0;
	}
	if(ty==2) {
		ll ans=C(ct[1],2);
		for(auto o:f[1]) ans+=w[o[0]][o[1]][2];
		cout<<ans%MOD<<"\n";
		return 0;
	}
	if(ty==3) {
		ll ans=C(ct[1],3); //111
		for(auto o:f[2]) { //112
			ans+=C(ct[1],2)-C(ct[1]-w[o[0]][o[1]][1],2);
		}
		for(auto o:f[1]) { //122 & 123
			int i=o[0],j=o[1];
			ans+=C(w[i][j][2],2);
			for(int k:{0,1,2,3}) {
				int x=i+dx[k],y=j+dy[k];
				if(x<1||x>n||y<1||y>n) continue;
				if(ds[x][y]==2) ans+=w[x][y][2]+w[x][y][3];
			}
		}
		cout<<(ans%MOD+MOD)%MOD<<"\n";
		return 0;
	}
	ll ans=C(ct[1],4); //1111
	for(auto o:f[2]) {
		int i=o[0],j=o[1];
		ans+=C(ct[1],3)-C(ct[1]-w[i][j][1],3); //1112
		ans+=(C(ct[1],2)-C(ct[1]-w[i][j][1],2))*w[i][j][3]; //1123
		//1234 & 1233
		ans+=w[i][j][1]*C(w[i][j][3],2);
		for(int k:{0,1,2,3}) {
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>n) continue;
			if(ds[x][y]==3) ans+=(w[x][y][3]+w[x][y][4])*w[i][j][1];
		}
	}
	for(auto o:f[1]) { //1222 & 1223
		int i=o[0],j=o[1],z=w[i][j][2];
		ans+=C(z,3);
		for(int k:{0,1,2,3}) {
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>n||ds[x][y]!=2) continue;
			ans+=(w[x][y][2]+w[x][y][3])*(z-1);
			ans+=C(w[x][y][2],2)+w[x][y][2]*w[x][y][3];
			for(int q:{0,1,2,3}) {
				int s=x+dx[q],t=y+dy[q];
				if(s<1||s>n||t<1||t>n) continue;
				if(ds[s][t]==2) ans+=w[s][t][2]-1+w[s][t][3];
				if(ds[s][t]==3) ans+=w[s][t][2]-1;
			}
		}
		for(int x:{i-1,i+1}) for(int y:{j-1,j+1}) if(ds[x][j]==2&&ds[i][y]==2) {
			if(ds[x][y]==2||ds[x][y]==3) ans-=3;
		}
	}
	//1122
	//link 1-2 1-2
	ans+=C(ct[1],2)*C(ct[2],2);
	ll sum[5]={0,0,0,0};
	for(int z:{0,1,2,3,4}) {
		for(auto o:f[2]) {
			int i=o[0],j=o[1];
			sum[z]+=C(ct[1]-z-w[i][j][1],2);
		}
	}
	for(auto o:f[2]) {
		int i=o[0],j=o[1],z=w[i][j][1];
		ans-=C(ct[1]-w[i][j][1],2)*(ct[2]-1);
		ll res=sum[z]-C(ct[1]-z-w[i][j][1],2);
		for(int k:{0,1,2,3}) {
			int x=i+2*dx[k],y=j+2*dy[k];
			if(x<1||x>n||y<1||y>n||ds[x][y]!=2) continue;
			if(ds[i+dx[k]][j+dy[k]]==1) {
				res-=C(ct[1]-z-w[x][y][1],2);
				res+=C(ct[1]-z-w[x][y][1]+1,2);
			}
		}
		for(int x:{i-1,i+1}) for(int y:{j-1,j+1}) if(ds[x][y]==2) {
			res-=C(ct[1]-z-w[x][y][1],2);
			res+=C(ct[1]-z-w[x][y][1]+(ds[x][j]==1)+(ds[i][y]==1),2);
		}
		ans=(ans+res%MOD*i2)%MOD;
	}
	for(auto o:f[2]) {
		//only link 2-2
		int i=o[0],j=o[1];
		for(int k:{0,1,2,3}) {
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>n||ds[x][y]!=2) continue;
			int a=w[i][j][1],b=w[x][y][1],c=ct[1]-a-b;
			ans+=C(c+a,2)-C(c,2);
		}
	}
	cout<<(ans%MOD+MOD)%MOD<<"\n";
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

水个题解。

我是的代码是真摆砖了。

大模拟题。

把空位分成两类：

- $A$ 类：初始时紧挨着至少一块砖。
- $B$ 类：初始时旁边没有砖。

emm 然后就是大模拟了。

- $k=1$

那就是 $A$ 类砖的个数。

- $k=2$

要么两个都是 $A$ 类，要么是一个 $A$ 类和它旁边的一个 $B$ 类。

- $k=3$

选的是 $AAA$ 就组合数一下。

$AAB$，只需在 $B$ 处计数。

$ABB$，只需在 $A$ 处计数。

- $k=4$

$AAAA$，依旧组合数。

$AAAB$，在 $B$ 处计数。

$AABB$，唯一比较有技术含量的部分。我是这样做的：

先算两组 $AB$ 内部匹配（即 $B$ 在 $A$ 旁边）的方案数，直接两组分开计数再乘法原理（保证两个 $A$ 不同），这样会算重，一种是一个 $B$ 同时匹配了两个 $A$，这和 $k=3$ 中 $AAB$ 的计数一样，还有是类似一个对角矩阵：

$$AB\\BA$$

这个直接扫一遍就剪掉了。然后就没有重了。

还有是两个 $B$ 同时依赖一个 $A$，这个再单独计数即可。

$ABBB$，这个很简单，可以暴搜，但模拟赛的时候时限没那么长，我怕卡常就把所有可能的组合手写了！


```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define pb push_back
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=3e3+5,mod=1e9+7;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,k,ans,iv2=INV(2),iv6=INV(6);
string s[N];
const int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
inline bool Che(int X,int Y){
	return X>0&&Y>0&&X<=n&&Y<=n;
}
inline void subtask1(){
	repn(x)repn(y)if(s[x][y]=='.'){
		int fl=0;
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			fl|=Che(X,Y)&&s[X][Y]=='#';
		}
		add(ans,fl);
	}
	cout <<ans;
}
inline int C2(int x){
	return mul(x,mul(x-1,iv2));
}
inline int C3(int x){
	return mul(mul(x,x-1),mul(x-2,iv6));
}
bool v[N][N];
inline int getRound(int x,int y){
	int ans=0;
	rep(i,0,3){
		int X=x+dx[i],Y=y+dy[i];
		ans+=Che(X,Y)&&v[X][Y];
	}
	return ans;
}
inline int getRound0(int x,int y){
	int ans=0;
	rep(i,0,3){
		int X=x+dx[i],Y=y+dy[i];
		ans+=Che(X,Y)&&!v[X][Y]&&s[X][Y]=='.';
	}
	return ans;
}
inline void subtask2(){
	int c=0;
	repn(x)repn(y)if(s[x][y]=='.'){
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			v[x][y]|=Che(X,Y)&&s[X][Y]=='#';
		}
		add(c,v[x][y]);
	}
	ans=mul(c,mul(c-1,INV(2)));
	repn(x)repn(y)if(v[x][y]){
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			if(Che(X,Y)&&s[X][Y]=='.'&&!v[X][Y])add(ans,1);
		}
	}
	cout <<ans;
}
int Ct[N][N],CT[N][N];
inline void subtask3(){
	int c=0;
	repn(x)repn(y)if(s[x][y]=='.'){
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			v[x][y]|=Che(X,Y)&&s[X][Y]=='#';
		}
		add(c,v[x][y]);
	}
	ans=C3(c);
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y])Ct[x][y]=getRound(x,y);
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y]){
		int ct=Ct[x][y];
		add(ans,C2(ct));
		add(ans,mul(ct,c-ct));
	}
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y]){
		rep(i,0,1){
			int X=x+dx[i],Y=y+dy[i];
			if(Che(X,Y)&&!v[X][Y]&&s[X][Y]=='.'){
				add(ans,Ct[x][y]+Ct[X][Y]);
			}
		}
	}else if(v[x][y]){
		int c=getRound0(x,y);
		add(ans,C2(c));
	}
	cout <<ans;
}
int iv24=INV(24);
inline int C4(int x){
	return mul(mul(mul(x,x-1),x-2),mul(x-3,iv24));
}
const int Dx[4]={1,1,-1,-1},Dy[4]={1,-1,1,-1};
inline int Ty(int x,int y){
	if(!Che(x,y))return 3;
	if(s[x][y]=='#')return 2;
	return v[x][y];
}
inline void subtask4(){
	int c=0;
	repn(x)repn(y)if(s[x][y]=='.'){
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			v[x][y]|=Che(X,Y)&&s[X][Y]=='#';
		}
		add(c,v[x][y]);
	}
	ans=C4(c);
	int tot=0;
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y])Ct[x][y]=getRound(x,y);
	else if(v[x][y])CT[x][y]=getRound0(x,y),tot+=CT[x][y];
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y]){
		int ct=Ct[x][y];
		add(ans,C3(ct));
		add(ans,mul(C2(ct),c-ct));
		add(ans,mul(ct,C2(c-ct)));
	}
	int S=0;
	repn(x)repn(y)if(v[x][y]){
		int ct=CT[x][y];
		add(S,mul(ct,tot-ct));
	}
	Mul(S,iv2),add(ans,S);
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y]){
		int ct=Ct[x][y];
		red(ans,C2(ct));
	}
	rep(x,1,n-1)rep(y,1,n-1){
		int A=Ty(x,y),B=Ty(x,y+1),C=Ty(x+1,y),D=Ty(x+1,y+1);
		if(A==D&&B==C&&A!=B&&A+B==1)red(ans,1);
	}
	repn(x)repn(y)if(s[x][y]=='.'&&!v[x][y]){
		rep(i,0,1){
			int X=x+dx[i],Y=y+dy[i];
			if(Che(X,Y)&&!v[X][Y]&&s[X][Y]=='.'){
				int ct=Ct[x][y]+Ct[X][Y];
				add(ans,mul(ct,c-ct));
				add(ans,C2(Ct[x][y])),add(ans,C2(Ct[X][Y]));
			}
		}
	}
	repn(x)repn(y)if(!Ty(x,y)){
		if(!Ty(x+1,y+1)){
			int Cc=(Ty(x+1,y)==1)+(Ty(x,y+1)==1),Tt=Ct[x][y]+Ct[x+1][y+1]-Cc;
			add(ans,mul(Cc,c-Tt));
		}
		if(!Ty(x+1,y-1)){
			int Cc=(Ty(x+1,y)==1)+(Ty(x,y-1)==1),Tt=Ct[x][y]+Ct[x+1][y-1]-Cc;
			add(ans,mul(Cc,c-Tt));
		}
		if(!Ty(x,y+2)){
			int Cc=(Ty(x,y+1)==1),Tt=Ct[x][y]+Ct[x][y+2]-Cc;
			add(ans,mul(Cc,c-Tt));
		}
		if(!Ty(x+2,y)){
			int Cc=(Ty(x+1,y)==1),Tt=Ct[x][y]+Ct[x+2][y]-Cc;
			add(ans,mul(Cc,c-Tt));
		}
	}
	repn(x)repn(y)if(!Ty(x,y)){
		int A,B,ct=Ct[x][y];
		A=Ty(x+1,y),B=Ty(x+2,y);
		if(!A&&!B)add(ans,ct+Ct[x+1][y]+Ct[x+2][y]);
		if(!A&&B==1)add(ans,CT[x+2][y]-1);
		A=Ty(x,y+1),B=Ty(x,y+2);
		if(!A&&!B)add(ans,ct+Ct[x][y+1]+Ct[x][y+2]);
		if(!A&&B==1)add(ans,CT[x][y+2]-1);
		A=Ty(x+1,y),B=Ty(x+1,y+1);
		if(!A&&!B)add(ans,ct+Ct[x+1][y]+Ct[x+1][y+1]-(Ty(x,y+1)==1));
		if(!A&&B==1)add(ans,CT[x+1][y+1]-1-(Ty(x,y+1)==0));
		B=Ty(x,y+1);
		if(!A&&!B)add(ans,ct+Ct[x+1][y]+Ct[x][y+1]-(Ty(x+1,y+1)==1));
		if(!A&&B==1)add(ans,CT[x][y+1]-1-(Ty(x+1,y+1)==0));
		if(!B&&A==1)add(ans,CT[x+1][y]-1-(Ty(x+1,y+1)==0));
		A=Ty(x+1,y+1);
		if(!A&&!B)add(ans,ct+Ct[x][y+1]+Ct[x+1][y+1]-(Ty(x+1,y)==1));
		if(!B&&A==1)add(ans,CT[x+1][y+1]-1-(Ty(x+1,y)==0));
		A=Ty(x-1,y+1);
		if(!A&&!B)add(ans,ct+Ct[x-1][y+1]+Ct[x][y+1]-(Ty(x-1,y)==1));
		if(!B&&A==1)add(ans,CT[x-1][y+1]-1-(Ty(x-1,y)==0));
		A=Ty(x-1,y),B=Ty(x-2,y);
		if(!A&&B==1)add(ans,CT[x-2][y]-1);
		A=Ty(x,y-1),B=Ty(x,y-2);
		if(!A&&B==1)add(ans,CT[x][y-2]-1);
		A=Ty(x-1,y),B=Ty(x,y-1);
		if(!A&&B==1)add(ans,CT[x][y-1]-1-(Ty(x-1,y-1)==0));
		A=Ty(x+1,y);
		if(!A&&B==1)add(ans,CT[x][y-1]-1-(Ty(x+1,y-1)==0));
		A=Ty(x-1,y),B=Ty(x,y+1);
		if(A==1&&!B)add(ans,CT[x-1][y]-1-(Ty(x-1,y+1)==0));
	}
	repn(x)repn(y)if(v[x][y])add(ans,C3(CT[x][y]));
	cout <<ans;
}
inline void Main(){
	n=read(),k=read();
	repn(i)cin>>s[i],s[i]='*'+s[i];
	if(k==1)return subtask1();
	if(k==2)return subtask2();
	if(k==3)return subtask3();
	if(k==4)return subtask4();
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

