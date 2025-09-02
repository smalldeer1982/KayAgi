# マス目

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_grid

入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $

 答えを一行に出力せよ。 ```

2 2
```

```

3
```

```

5 8
```

```

950397139
```

## 说明/提示

### Constraints

 すぬけ君は、$ H $ x $ W $ のマス目を白と黒に塗り分けることにした。

- 左上のマス目と右下のマス目は黒に塗る。
- 左上のマス目から、黒いますを上下左右にたどって、右下のマス目に行くことができる。
 
 条件を満たす塗り分け方の個数を mod 1,000,000,007 で求めよ。 - - - - - -

- $ 2\ <\ =\ H\ <\ =\ 6 $
- $ 2\ <\ =\ W\ <\ =\ 100 $

# 题解

## 作者：Alex_Wei (赞：8)

> [AT695 マス目](https://www.luogu.com.cn/problem/AT695)
>
> 本题选自 [DP 优化方法大杂烩](https://www.cnblogs.com/alex-wei/p/DP_Involution.html) 状压部分。
> 
> [在 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/AT695_nb_bitmask_dp.html)。

这个题很 nb。下文记 $n=H$，$m=W$。

对于每一列，如果只记录一个格子是否为黑色，那么发现它无法处理从右边绕到左边再绕回去的路径，GG。

改变一下思路，注意到一列最多会产生三个连通块，那么我们用一个长度为 $n$ 的四进制数表示**联通状态**。某一位为 $0$ 表示白格子，为 $1$ 表示能和 $(1,1)$ 联通，为 $2$ 表示在某个不与 $(1,1)$ 联通的联通块中，为 $3$ 表示在某个不与 $(1,1)$ 和状态 $2$ 所表示的联通块联通的连通块中。一个状态合法，当且仅当两个相邻的不为 $0$ 的位相同且**至少存在一位为 $1$** 。再观察到连通块 $2,3$ 其实是等价的，即它们之间无序，所以钦定如果出现了 $3$，那么在其之前的某一位一定出现了 $2$。转移时 $2^n$ 枚举下一列的**黑白状态**，用并查集维护连通性，再更新出下一列表示**联通状态**的四进制数，判断是否合法并转移即可，时间复杂度 $m8^n$。最终答案即为 $f_{n,c}$，其中 $c$ 为所有合法且第 $n$ 位为 $1$ 的四进制数。

在上述限制下，其实满足条件的状态很少。暴力枚举可知 $n=6$ 时一列合法的状态总数只有 $S_6=196$，所以我们可以将其离散化。这样时间复杂度被优化到 $mS_n2^n\log n$，其中 $\log$ 是并查集的复杂度（其实基本上可以忽略不计了）。

注意到对于一个合法的联通状态，它根据下一列的黑白状态所能转移到的联通状态是固定的，即不随列数的变化而改变，因此可以 $S_n2^n\log n$ 预处理出来每个联通状态在知道下一列的黑白状态时所转移到的下一列联通状态，时间复杂度被再一次优化到 $mS_n2^n$，其中 $S_n$ 只有不到 $200$，是一个非常优秀的算法，同时也拿到了本题的最优解（2021.7.9）。

理论上本题的 $m$ 可以出到 $10^9$ 级别，因为矩阵快速幂可以做到 $S_n^3\log m$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x,v) memset(x,v,sizeof(x))
#define mcpy(x,y) memcpy(x,y,sizeof(y))

const int N=200;
const int mod=1e9+7;

int n,m,cnt,ans,t[N],g[N],tr[N][64],ed[N];
int c[6],buc[4],f[12],mp[4096];

void add(int &x,int y){x=(x+y)%mod;}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u!=v)f[v]=u;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<1<<(2*n);i++,mem(buc,0)){
		for(int j=0;j<n;j++)c[j]=i>>(j*2)&3,buc[c[j]]=1;
		if(!buc[1])continue;
		if(buc[3]&&!buc[2])continue;
		
		bool judge=1;
		for(int j=1;j<n;j++)if(c[j-1]&&c[j]&&c[j-1]!=c[j])judge=0;
		for(int j=0,ap=0;j<n;j++)
			if(c[j]==2)break;
			else if(buc[3]&&c[j]==3)judge=0;
		if(!judge)continue;
		
		mp[i]=++cnt;
		if((i>>(2*n-2)&3)==1)ed[cnt]=1;
		
		g[cnt]=(i&3)==1;
		for(int j=0;j<n;j++)
			for(int k=j+1;k<n;k++)
				if(c[j]==c[k]&&c[j])
					for(int l=j+1;l<k;l++)
						if(c[l]!=c[j])
							g[cnt]=0;
		
		for(int j=1;j<1<<n;j++){
			for(int k=0;k<2*n;k++)f[k]=k;
			for(int k=1;k<4;k++)
				for(int l=0,pre=-1;l<n;l++)
					if(c[l]==k){
						if(~pre)merge(l,pre);
						pre=l;
					}
			for(int k=0;k<n;k++){
				if(c[k]&&(j>>k&1))merge(k,k+n);
				if(k&&(j>>k&1)&&(j>>(k-1)&1))merge(k+n-1,k+n);
			}
			int one,legal=0,two=-1,msk=0;
			for(int k=0;k<n;k++)if(c[k]==1){one=find(k); break;}
			for(int k=0;k<n;k++)
				if(j>>k&1){
					int f=find(k+n);
					if(f==one)msk+=1<<(2*k),legal=1;
					else if(two==-1||f==two)two=f,msk+=2<<(2*k);
					else msk+=3<<(2*k);
				}
			if(legal)tr[cnt][j]=msk;
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<1<<n;j++)
			tr[i][j]=mp[tr[i][j]];
	for(int i=1;i<m;i++){
		mcpy(t,g),mem(g,0);
		for(int j=1;j<=cnt;j++)
			for(int k=1;k<1<<n;k++)
				if(tr[j][k])
					add(g[tr[j][k]],t[j]);
	}
	for(int i=1;i<=cnt;i++)if(ed[i])add(ans,g[i]);
	cout<<ans<<endl;
	return 0;
}
```

## 

---

## 作者：tzc_wk (赞：3)

[洛谷题面传送门](https://www.luogu.com.cn/problem/AT695)

介绍一个不太主流的、非常暴力的做法（

~~踩一下下面的题解，啥也没讲~~

首先注意到 $n$ 非常小，$m$ 比较大，因此显然以列为阶段，对行的状态进行状压。因此我们可以非常自然地想到一个非常 trivial 的做法：$dp_{i,mask1,mask2}$ 表示考虑到第 $i$ 列，当前列状态为 $mask1$，当前列中能从左上角到达的点集为 $mask2$，枚举下一列状态简单转移一下即可。

但是相信聪明的读者到这里一定可以发现，这个做法是错误的，因为题目规定可以朝**四个方向走**，也就是说有可能出现如下图所示的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/fiop3fx3.png)

对于下图中的情况，当我们状态转移到第四列时，我们会判定 $1,2,3,4$ 行是可以从起点到达的，而由于前一列（第 $3$ 列）的第 $6$ 行在前三行组成的子矩形中无法从起点到达，因此我们也会判断第四列第 $6$ 行无法从源点到达，也就导致了情况的漏算。

怎么处理呢？由于这种情况的存在，我们要在状态中多记录一些东西，注意到这个 $n=6$ 有点小的出奇，$\dbinom{6}{2}$ 不过 $15$，因此考虑**对每个点对 $(j,k)$** 记录当前列中这两行的格子在前 $i$ 列组成的子矩形中是否连通，即设 $dp_{i,j,k}$ 表示前 $i$ 列中两两可达性为 $j$，$k$ 中的格子可以从 $(1,1)$ 到达的方案数。这样一来我们在枚举下一列状态并 `check` 每个点是否能从 $(1,1)$ 到达时可以考虑这样的做法：对于每个 $j$，如果它左边的格子能从 $(1,1)$ 到达并且它是黑格，那么它能从 $(1,1)$ 到达，否则如果 $\exists k$ 满足 $(j,k)$ 在前 $i$ 列组成的子矩形中连通并且 $k$ 能从 $(1,1)$ 到达，那么 $j$ 能从 $(1,1)$ 到达，正确性显然。而显然如果我们知道了上一列的两两之间的可达性，是可以用传递闭包 or 并查集直接推出上一列的可达性的，因此这个做法恰好能够解决我们之前遇到的问题。

复杂度？最坏情况下该算法的复杂度可以达到 $2^{15}\times 2^6\times 2^6\times 100\times 6^3\approx 3\times 10^{12}$~~（这要是能过我就当场把这个电脑屏幕 **）~~，然鹅这个复杂度是远远达不到上界的，因为首先对于这 $2^{15}$ 个表示可达性的状态中，一个状态合法当且仅当它的传递闭包就是它本身，暴力枚举一下可知这 $2^{15}$ 个状态中总共只有 $203$ 个合法的状态，这下复杂度降到了 $203\times 2^6\times 2^6\times 100\times 6^3\approx 2\times 10^{10}$，其次在 DP 过程中很多状态是转移不到的，因此如果某个 $dp_{i,j,k}=0$ 那么我们就不用转移了，加上这个小小的优化之后速度又能快不少。此题 $\text{TL}=8\text{s}$，而我这个做法只跑了 $222\text{ms}$。当然这肯定不是最坏的版本，还有优化的空间，比方说一开始大可不必 $\mathcal O(2^{15}\times 6^3)$ 枚举所有状态，可以一遍 DFS 一遍把不合法的状态剪掉，这样程序还可以跑得更快（虽然这不是复杂度瓶颈所在），以及在转移中，由于本题的图是无向图，传递闭包可以用 dsu 来代替，这样可将 $6^3$ 变成 $6^2$，但由于本人懒癌症晚期就没有进一步优化了（

```cpp
const int MAXM=100;
const int MAXT=1<<6;
const int MAXP=1<<15;
const int MAX_ST=203;
const int MOD=1e9+7;
void add(int &x,int v){((x+=v)>=MOD)&&(x-=MOD);}
int n,m,id[MAXP+5],msk[MAXP+5],cnt=0,is[8][8],pre_is[8][8],blk[8];
int dp[MAXM+5][MAXT+5][MAX_ST+5];
int main(){
	scanf("%d%d",&n,&m);int lim=1<<(n*(n-1)/2);
	for(int i=0;i<lim;i++){
		int cur=i;bool flg=1;
		for(int j=1;j<=n;j++) for(int k=1;k<j;k++)
			is[j][k]=is[k][j]=cur&1,cur>>=1;
		for(int j=1;j<=n;j++) is[j][j]=1;
		for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) for(int l=1;l<=n;l++)
			if(is[j][k]&&is[k][l]&&!is[j][l]) flg=0;
		if(flg) msk[++cnt]=i,id[i]=cnt;
	} //printf("%d\n",cnt);
	for(int i=0;i<(1<<n);i++){
		if(~i&1) continue;
		int pre=0,msk1=0,msk2=0;memset(is,0,sizeof(is));
		for(int j=1;j<=n;j++){
			if(~i>>(j-1)&1){
				for(int k=pre+1;k<j;k++) for(int l=pre+1;l<k;l++) is[k][l]=is[l][k]=1;
				if(!pre) for(int k=pre+1;k<j;k++) msk1|=(1<<k-1);
				pre=j;
			}
		} if(!pre) msk1=(1<<n)-1;
		for(int k=pre+1;k<=n;k++) for(int l=pre+1;l<k;l++) is[k][l]=1;
		for(int k=n;k;k--) for(int l=k-1;l;l--) msk2=msk2<<1|is[k][l];
//		printf("%d %d\n",msk1,msk2);
		add(dp[1][msk1][id[msk2]],1);
	}
	for(int i=1;i<m;i++){
		for(int j=1;j<(1<<n);j++){
			for(int k=1;k<=cnt;k++){
//				printf("%d %d %d %d\n",i,j,k,dp[i][j][k]);
				if(!dp[i][j][k]) continue;int cur=msk[k];
				for(int l=1;l<=n;l++) for(int o=1;o<l;o++)
					pre_is[l][o]=pre_is[o][l]=cur&1,cur>>=1;
				for(int l=0;l<(1<<n);l++){
					for(int o=1;o<=n;o++) blk[o]=l>>(o-1)&1;
					int pre=0;memset(is,0,sizeof(is));
					for(int o=1;o<=n;o++){
						if(!blk[o]){
							for(int p=pre+1;p<o;p++) for(int q=pre+1;q<p;q++)
								is[p][q]=is[q][p]=1;
							pre=o;
						}
					}
					for(int p=pre+1;p<=n;p++) for(int q=pre+1;q<p;q++)
						is[p][q]=is[q][p]=1;
					for(int p=1;p<=n;p++) if(blk[p])
						for(int q=1;q<p;q++) if(blk[q])
							is[p][q]|=pre_is[p][q],is[q][p]|=pre_is[q][p];
					for(int p=1;p<=n;p++) if(blk[p])
						for(int q=1;q<=n;q++) if(blk[q])
							for(int r=1;r<=n;r++) if(blk[r])
								is[q][r]|=is[q][p]&is[p][r];
					int msk1=0,msk2=0;
					for(int p=1;p<=n;p++){
						bool flg=0;
						if(blk[p]&&(j>>p-1&1)) flg=1;
						else if(blk[p]){
							for(int q=1;q<=n;q++) if(is[p][q]&&(j>>q-1&1))
								flg=1;
						} msk1|=flg<<(p-1);
					}
					for(int p=n;p;p--) for(int q=p-1;q;q--)
						msk2=msk2<<1|is[p][q];
//					printf("%d %d %d -> %d %d %d(%d)\n",i,j,msk[k],i+1,msk1,msk2,id[msk2]);
					add(dp[i+1][msk1][id[msk2]],dp[i][j][k]);
				}
			}
		}
	} int ans=0;
	for(int j=1;j<(1<<n);j++) if(j>>(n-1)&1)
		for(int k=1;k<=cnt;k++) add(ans,dp[m][j][k]);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://atcoder.jp/contests/tdpc/tasks/tdpc_grid)

题意：给定一个 $H$ 行 $W$ 列全白矩阵，要求 $(1,1)$ 和 $(H,W)$ 必须涂黑，剩下的格子可以涂黑也可以不涂。求 $(1,1)$ 和 $(H,W)$ 在同一个黑色连通块的涂色方案数。 $H \le 6,W \le 100$.

入手点显然是 $H \le 6$. 容易考虑状压，即设 $f(s,t)$ 是前 $s$ 列，第 $s$ 列自上往下格子的黑白状况为 $t$ 的方案数。但很快就发现这个状态无法统计答案。

既然题目里统计的是连通块，那么容易发现，同一列的黑色格子，最多属于 $3$ 个不同的连通块。所以我们状压 $f(s,t)$，其中 $t$ 代表第 $s$ 列的连通块状况，是一个四进制数。$0$ 代表为白色格子，$1,2,3$ 代表其所属编号。

如果我们设 $(1,1)$ 所在连通块编号为 $1$. 只有编号为 $1$ 的连通块需要从 $s$ 列到 $s+1$ 列不断传递下去，编号为 $2$ 和编号为 $3$ 的连通块其实我们并不关心，只是用它们维护同一列格子的连通性而已。所以为了去重，应该从上往下依次编号 $2,3$.

所以转移就枚举 $i,j$ 然后从 $f(i,j)$ 转移到对应的 $f(i+1,k)$. 至于 $k$ 的确定，只要我们枚举第 $i+1$ 列的染色情况（二进制数）$x$. 就可以确定 $k$. 确定 $k$ 的过程中应该用并查集维护两列共 $12$ 个格子之间的连通性。

细节略多。

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=110,MAXM=2e4+10,mod=1e9+7;
int n,m;
ll f[MAXN][MAXM],vis[14],ans,lim,valid[14];
struct Set{
	int fa[13];
	Set(){rep(i,1,n*2)fa[i]=i;}
	int Find(int x){if(fa[x]==x)return x;return fa[x]=Find(fa[x]);}
	void Merge(int x,int y){if(Find(x)!=Find(y))fa[Find(y)]=Find(x);}	 
}; 
il int getbit(int x,int y){
	//x在四进制下的第y位
	return (bool)(x&(1<<(2*y-1)))*2+(bool)(x&(1<<(2*y-2)));  
}
il void update(int& x,int y,int z){
	//x在四进制下第y位修改为z
	if(x & (1<<(2*y-1)))x-=(1<<(2*y-1));
	if(x & (1<<(2*y-2)))x-=(1<<(2*y-2)); 
	if(z&2)x+=(1<<(2*y-1));
	if(z&1)x+=(1<<(2*y-2)); 
}
int main(){
	cin>>n>>m;
	rep(i,1,n){lim=lim*4+3;}
	rep(j,1,(1<<n)-1){
		if(even(j))continue;
		int state=0,cnt=0,flag=1;
		rep(x,1,n){
			if(!(j&(1<<(x-1))))continue;
			if(x==1 || !(j&(1<<(x-2)))){
				cnt++;
			}
			if(cnt==4){flag=0;break;}
			update(state,(int)x,cnt);
		} 
		if(flag){
			f[1][state]=1;
		}
	} 
	rep(i,1,m-1){
		rep(j,1,lim){
			if(!f[i][j])continue;
			//枚举第i+1列的染色方案
			rep(k,1,(1<<n)-1){
				Set s;
				int state=0;
				//合并i列中元素
				rep(x,1,n){
					if(!getbit(j,x))continue;
					rep(y,x+1,n){
						if(getbit(j,y)!=getbit(j,x))continue;
						s.Merge(x,y);
					}
				} 
				//合并i+1列中元素
				rep(x,1,n){
					if(x==1 || !(k&(1<<(x-1))))continue;
					if(k&(1<<(x-2))){
						s.Merge(x-1+n,x+n);
					}
				} 
				//合并i列和i+1列元素
				rep(x,1,n){
					if(getbit(j,x) && (k&(1<<(x-1)))){
						s.Merge(x,x+n);
					}
				} 
				memset(valid,0,sizeof valid);
				memset(vis,0,sizeof vis);
				rep(x,1,n){
					if(getbit(j,x)==1){
						valid[s.Find(x)]=1;
					}
				}
				int flag=0;
				rep(x,1,n){
					if(!(k&(1<<(x-1))))continue;
					if(s.Find(x+n)<=n){
						int pos=s.Find(x+n);
						if(valid[pos]){
							//延续1标记
							flag=1;
							update(state,x,1); 
							vis[s.Find(x+n)]=1;
						}
					}
				} 
				if(!flag)continue;
				int cnt=1;
				flag=1;
				rep(x,1,n){
					if(!(k&(1<<(x-1))))continue;
					if(getbit(state,x))continue;
					if(!vis[s.Find(x+n)]){
						vis[s.Find(x+n)]=++cnt;
						if(cnt==4){
							flag=0;break;
						}
					}
					update(state,x,vis[s.Find(x+n)]);
				}
				if(!flag)continue;
				f[i+1][state]=(f[i+1][state]+f[i][j])%mod; 
			} 
		}
	}
	rep(j,1,lim){
		if(getbit(j,n)!=1)continue;
		ans=(ans+f[m][j])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```



 

---

## 作者：Jerrywang09 (赞：0)

非常牛的状压 DP。

首先要注意到黑格子可以各种蛇形走位，因此压缩的状态一定要记录连通性有关的信息。

由于行数只有 $6$，考虑按列作为阶段，状态压缩记录当前列 $k$ 的每个格子 $a_{i,k}$ 属于的连通块编号。又考虑到行数只有 $6$，使用四进制数就可以按如下方法状压一列：

0. $a_{i,k}$ 没有涂黑；
1. $a_{i,k}$ 与 $a_{1,1}$ 同属一个连通块；
2. 所有标成 $2$ 的格子属于同一个连通块；
3. 所有标成 $3$ 的格子另属同一个连通块。

初始化：$a_{1,1}$ 一定要涂黑，其它格子任意。

转移：枚举上一列的四进制状态，二进制枚举当前列填涂的状态。然后，只考虑当前列涂黑的所有格子，使用并查集维护连通块。这一块内容细节很多，但不难写，详见代码。

统计答案：$a_{n,m}$ 一定要与 $a_{1,1}$ 连通，其它格子任意。

综上所述，这种维护连通问题的状压 DP 方法是非常重要的。

```cpp
// AT_tdpc_grid マス目
#include <cstdio>
#include <iostream>
#include <cassert>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=6, M=105, SZ=4100, mod=1e9+7;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, m, a[N], b[N]; ll f[M][SZ], pw[M], res;
int fa[N];
void init() {rep(i, 0, n-1) fa[i]=i, b[i]=0;}
int root(int u) {return fa[u]==u?u:fa[u]=root(fa[u]);}
void merge(int u, int v)
{
    u=root(u), v=root(v);
    if(u!=v) fa[u]=v;
}

void decode(int s)
{
    rep(i, 0, n-1) a[i]=s/pw[i]%4;
}
int encode()
{
    int res=0;
    rep(i, 0, n-1) res+=pw[i]*b[i];
    return res;
}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    scanf("%d%d", &n, &m);
    pw[0]=1; rep(i, 1, n) pw[i]=pw[i-1]*4;
    rep(t, 0, (1<<n)-1) if(t&1)
    {
        init();
        rep(i, 1, n-1) if(t>>i&1)
        {
            int j=i-1;
            if(t>>j&1) merge(i, j);
        }
        rep(j, 0, n-1) if(root(0)==root(j))
        {
            if(t>>j&1) b[j]=1;
        }
        int cnt=1;
        rep(i, 0, n-1) if(t>>i&1)
        {
            if(root(i)==i && !b[i]) b[i]=++cnt;
        }
        rep(i, 0, n-1) if(t>>i&1)
        {
            if(!b[i]) b[i]=b[root(i)];
        }
        int w=encode();
        f[1][w]=1;
    }
    rep(k, 2, m)
    {
        rep(s, 0, pw[n]-1) if(f[k-1][s]) // 上一列连通性状态
        {
            decode(s);
            rep(t, 0, (1<<n)-1) // 当前列的填数状态
            {
                init();
                rep(i, 0, n-1) if(t>>i&1) rep(j, 0, n-1) if(t>>j&1)
                    if(a[i] && a[i]==a[j]) merge(i, j);
                rep(i, 1, n-1) if(t>>i&1)
                {
                    int j=i-1;
                    if(t>>j&1) merge(i, j);
                }
                bool have1=0;
                rep(i, 0, n-1) if(a[i]==1) rep(j, 0, n-1) if(t>>j&1)
                    if(root(i)==root(j)) b[j]=1, have1=1;
                if(!have1) continue;
                int cnt=1;
                rep(i, 0, n-1) if(t>>i&1)
                    if(root(i)==i && !b[i]) b[i]=++cnt;
                rep(i, 0, n-1) if(t>>i&1)
                    if(!b[i]) b[i]=b[root(i)];
                int w=encode();
                f[k][w]=(f[k][w]+f[k-1][s])%mod;
            }
        }
    }
    rep(s, 0, pw[n]-1) if(f[m][s])
    {
        decode(s);
        if(a[n-1]==1) res=(res+f[m][s])%mod;
    }
    printf("%lld\n", res);

    return 0;
}
```

---

