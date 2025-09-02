# 合鍵

## 题目描述

## JOISC2015 Day2T2 锁


在 JOI 公司内共有 $N$ 个员工。在时刻 $0$ ，每一个员工均在公司内。公司只有一个大门用于进出公司，这个大门可以上锁。在公司内的人可以任意开锁或锁门，但在公司外只有拥有备用钥匙的人可以任意开锁或锁门。因为 JOI 公司的规定，在公司内的人除非要从公司出去，是不允许开门锁的。

现在员工 $i$ 会在 $S_i$ 时刻从公司出外出差，在 $T_i$ 时刻回到公司，保证在同一时刻没有两个或以上的员工同时进出大门，且在 $M$ 时刻所有员工均回到了公司，即 $T_i < M$ 。你可以让 $K$ 个员工拿到备用钥匙，为了不让钥匙丢失，备用钥匙不能给其他员工借用。

现在 JOI 公司的社长需要你求出：在所有员工到达公司时都能进入公司（即门没有上锁或者这个员工有备用钥匙）、拥有备用钥匙的员工不超过 $K$ 的情况下，在这 $M$ 个单位时间内门最多锁住多长时间。

## 说明/提示

$1 \leq K \leq N \leq 2000$

$1 \leq M \leq 10^9$

$0 < S_i < T_i < M$，$S_i,T_i$ 两两不同

## 样例 #1

### 输入

```
4 20 2
3 11
5 15
6 10
12 18```

### 输出

```
13```

# 题解

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2015_f)。

## 思路

我们称一个员工的进出为一个事件。

我们不妨将所有事件按照事件发生的时间点排序，我们假设 $i$ 为触发一个事件的员工，$j$ 为下一个时间点触发事件的员工，考虑每种情况对答案（也就是大门锁的时间）什么时候有贡献，我们可以分成 $4$ 类来讨论：

- $i$ 进来，$j$ 出去，那么 $i$ 绝对会关门，我们将区间贡献直接加到答案上。

- $i$ 进来，$j$ 进来，$i$ 关门时当且仅当 $j$ 有钥匙，我们将贡献加到 $j$ 员工上。

- $i$ 出去，$j$ 出去，$i$ 关门时当且仅当 $i$ 有钥匙，我们将贡献加到 $i$ 员工上。 

- $i$ 出去，$j$ 进来，这段区间有贡献当且仅当 $i,j$ 都有钥匙，如果 $i,j$ 是同一个人，将贡献直接加到 $i$ 上，否则将 $i,j$ 连一条有向边，将贡献加到 $i\to j$ 的边上面。

这样我们就转换成了一个图上问题，不难发现这个图是由若干条链组成的（因为每个员工只有两种状态），我们不妨将这些链组成一个大链，对这个链式序列 DP 即可。

记 $val_i$ 表示 $i$ 点权，$val1_i$ 表示 $i$ 到连接到的那个点的边权。

我们设 $f_{i,j,0/1}$ 表示当前链的前面 $i$ 个人，共有 $j$ 把钥匙，第 $i$ 个人是否有钥匙的最大贡献。

若第 $i$ 个人没有钥匙，那么有 $f_{i,j,0}=\max\{f_{i,j,0},f_{i-1,j,1},f_{i-1,j,0}\}$。

若第 $i$ 个人有钥匙，那么有 $f_{i,j+1,1}=\max\{f_{i,j+1,1},f_{i-1,j,0}+val_i,f_{i-1,j,1}+val_i+val1_i\}$

（这个边两端点都有 $1$，因此两点之间有边，所以要加上边权）

$f$ 第一维显然能被滚动数组优化掉，时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxn=2010;
int f[2][Maxn][2];
struct node{
	int pos,id;
	bool flg;
}a[Maxn<<2];
int n,m,k,tot,nxt[Maxn],val[Maxn],val1[Maxn];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,l,r;i<=n;i++){
		scanf("%d%d",&l,&r);
		a[++tot]=(node){l,i,0};
		a[++tot]=(node){r,i,1};
	}
	sort(a+1,a+tot+1,[](const node x,const node y){return x.pos<y.pos;});
	f[0][0][0]=(a[1].pos+m-a[tot].pos);
	for(int i=1;i<tot;i++){
		int w=a[i+1].pos-a[i].pos;
		if(a[i].flg&&!a[i+1].flg) f[0][0][0]+=w;
		if(a[i].flg&&a[i+1].flg) val[a[i+1].id]+=w;
		if(!a[i].flg&&!a[i+1].flg) val[a[i].id]+=w;
		if(!a[i].flg&&a[i+1].flg){
			if(a[i+1].id==a[i].id) val[a[i].id]+=w;
			else nxt[a[i+1].id]=a[i].id,val1[a[i].id]+=w;
		}
	}
	int pre=0;
	for(int i=1;i<=n;i++)
		if(!val1[i]){
			nxt[pre]=i;
			while(nxt[pre]) pre=nxt[pre];
		}
	int tp=0;
	for(int i=nxt[0];i;i=nxt[i]){
		tp^=1;
		for(int j=0;j<=k;j++){
			for(int h=0;h<=1;h++){
				if(!f[tp^1][j][h]) continue;
				f[tp][j][0]=max(f[tp][j][0],f[tp^1][j][h]);
				f[tp][j+1][1]=max(f[tp][j+1][1],f[tp^1][j][h]+val1[i]*h+val[i]);
				f[tp^1][j][h]=0;
			}
		}
	}
	printf("%d\n",max(f[tp][k][0],f[tp][k][1]));
	return 0;
}


```


---

## 作者：daniEl_lElE (赞：0)

考虑将所有出入时间排序。设离开公司为操作 $1$，回公司为操作 $2$。

如果有两个相邻的操作 $(2,1)$，那么这一段时间一定是可以锁门的。

如果有两个相邻的操作 $(1,1)$，那么这一段时间能锁门当且仅当前面一个人有钥匙。

如果有两个相邻的操作 $(2,2)$，那么这一段时间能锁门当且仅当后面一个人有钥匙。

如果有两个相邻的操作 $(1,2)$，那么这一段时间能锁门当且仅当两个人都有钥匙。

不妨给 $(1,2)$ 的两个人连一条边（同一个人就不需要连了），不难发现连出来的边形成若干条链。对于每条链，考虑树形 $dp_{i,j,0/1}$ 表示看到 $i$ 子树，选了 $j$ 个人给钥匙，最大的锁门时间。将所有链合并起来即可。利用树上依赖背包的证明可知总复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int lsh[5005],s[2005],t[2005],bel[5005],v[5005];
int f[2005],g[2005][2005],deg[2005],siz[2005],tmp[2005][2],vis[2005],dp[2005][2005][2],tot[2005];
vector<int> vc[2005];
void dfs(int now,int fa){
	vis[now]=1;
	siz[now]=1,dp[now][0][0]=0,dp[now][1][1]=f[now],dp[now][0][1]=-1e18;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		for(int i=0;i<=siz[now]+siz[v];i++) tmp[i][0]=tmp[i][1]=-1e18;
		for(int j=0;j<=siz[now];j++){
			for(int k=0;k<=siz[v];k++){
				for(int x=0;x<=1;x++){
					for(int y=0;y<=1;y++){
						tmp[j+k][x]=max(tmp[j+k][x],dp[now][j][x]+dp[v][k][y]+g[now][v]*(x&y));
					}
				}
			}
		}
		siz[now]+=siz[v];
		for(int j=0;j<=siz[now];j++) dp[now][j][0]=tmp[j][0],dp[now][j][1]=tmp[j][1];
	}
}
signed main(){
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>s[i]>>t[i];
		lsh[2*i-1]=s[i],lsh[2*i]=t[i];
	}
	lsh[2*n+1]=0,lsh[2*n+2]=m;
	sort(lsh+1,lsh+2*n+3); int l=2*n+2;
	for(int i=1;i<=n;i++){
		int sp=lower_bound(lsh+1,lsh+l+1,s[i])-lsh;
		bel[sp]=i,v[sp]=1;
		int tp=lower_bound(lsh+1,lsh+l+1,t[i])-lsh;
		bel[tp]=i,v[tp]=2;
	}
	int fr=lsh[2]-lsh[1]+lsh[l]-lsh[l-1];
	for(int i=2;i<l-1;i++){
		if(v[i]==1&&v[i+1]==1) f[bel[i]]+=lsh[i+1]-lsh[i];
		if(v[i]==2&&v[i+1]==2) f[bel[i+1]]+=lsh[i+1]-lsh[i];
		if(v[i]==1&&v[i+1]==2){
			if(bel[i]!=bel[i+1]){
				g[bel[i]][bel[i+1]]=g[bel[i+1]][bel[i]]=lsh[i+1]-lsh[i];
				vc[bel[i]].push_back(bel[i+1]);
				vc[bel[i+1]].push_back(bel[i]);
				deg[bel[i]]++,deg[bel[i+1]]++;
			}
			else f[bel[i]]+=lsh[i+1]-lsh[i];
		}
		if(v[i]==2&&v[i+1]==1) fr+=lsh[i+1]-lsh[i];
	}
	int totsum=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]&&deg[i]<=1){
			dfs(i,0);
			memset(tmp,0,sizeof(tmp));
			for(int j=0;j<=totsum;j++){
				for(int l=0;l<=siz[i];l++){
					tmp[j+l][0]=max(tmp[j+l][0],tot[j]+max(dp[i][l][0],dp[i][l][1]));
				}
			}
			totsum+=siz[i];
			for(int j=0;j<=totsum;j++) tot[j]=tmp[j][0];
		}
	}
	cout<<tot[k]+fr<<"\n";
	return 0;
}
```

---

