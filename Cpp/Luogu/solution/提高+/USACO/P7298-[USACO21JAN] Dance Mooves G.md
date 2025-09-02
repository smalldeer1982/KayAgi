# [USACO21JAN] Dance Mooves G

## 题目描述

Farmer John 的奶牛们正在炫耀她们的最新舞步！

最初，所有的 $N$ 头奶牛（$2≤N≤10^5$）站成一行，奶牛 $i$ 排在其中第 $i$ 位。舞步序列给定为 $K$ （$1≤K≤2\times10^5$）个位置对 $(a_1,b_1),(a_2,b_2),…,(a_K,b_K)$。在舞蹈的第 $i=1…K$ 分钟，位置 $a_i$ 与 $b_i$ 上的奶牛交换位置。同样的 $K$ 次交换在第 $K+1…2K$ 分钟发生，在第 $2K+1…3K$ 分钟再次发生，以此类推，周期性地持续共 $M$ 分钟（$1≤M≤10^{18}$）。换言之， 

 - 在第 $1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - ……
 - 在第 $K$ 分钟，位置 $a_K$ 与 $b_K$ 上的奶牛交换位置。
 - 在第 $K+1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $K+2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - 以此类推……

对于每头奶牛，求她在队伍中会占据的不同的位置数量。

注意：本题每个测试点的时间限制为默认限制的两倍。 

## 说明/提示

$7$ 分钟之后，各个位置上的奶牛为 $[3,4,5,2,1,6]$。

 - 奶牛 $1$ 可以到达位置 $\{1,2,3,4,5\}$。
 - 奶牛 $2$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $3$ 可以到达位置 $\{1,2,3\}$。
 - 奶牛 $4$ 可以到达位置 $\{2,3,4\}$。
 - 奶牛 $5$ 可以到达位置 $\{3,4,5\}$。
 - 奶牛 $6$ 从未移动，所以她没有离开过位置 $6$。
 
#### 测试点性质：

 - 测试点 1-5 满足 $N≤100,K≤200$。
 - 测试点 6-10 满足 $M=10^{18}$。
 - 测试点 11-20 没有额外限制。

Problem credits: Chris Zhang 

## 样例 #1

### 输入

```
6 4 7
1 2
2 3
3 4
4 5```

### 输出

```
5
4
3
3
3
1```

# 题解

## 作者：zyc2003 (赞：20)

### [题目链接 : [USACO21JAN] Dance Mooves G](https://www.luogu.com.cn/problem/P7298)

### 前置知识

推荐先写出**银组**的本题的弱化版 : [[USACO21JAN] Dance Mooves : Silver](https://www.luogu.com.cn/problem/P7299) , 这样对理解本题会有更大帮助 . 或者你也可以选择直接看本篇题解 .  

### 总体思路

这里不再简述题意 , 因为题面比较清晰明了 . 

当进行完**一轮置换** , 也就是 $K$ 个**交换**之后 , 我们设 $\mathrm{next}_i$ 是执行完**一轮置换**之后 , 第 $i$ 头奶牛会到达的位置 . 就拿样例来说 , 原来的奶牛序列是 :  

$$1,2,3,4,5,6$$

那么经过 $K=4$ 次的**交换**后 , 序列变成 : 

$$2,3,4,5,1,6$$

$1$ 号奶牛去到了位置 $5$ , $2$ 号奶牛去到了位置 $1$ ... 等等 . 

现在我说 : 如果把每一个位置看做一个**点** , 点 $i$ 向 $\mathrm{next}_i$ 连边 , 那么我们会得到一堆**简单环**构成的**森林** . 对于样例来说 , 我们形成了两个环 : 

![](https://cdn.luogu.com.cn/upload/image_hosting/0q5aq1cl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

证明也很简单 . 我们知道 , 在**一轮置换**之后 , $i$ 位置上的奶牛一定到达了 $\mathrm{next}_i$ 位置 , 而必然存在另一个位置 $j$ , **一轮置换**后到达了 $\mathrm{next}_j=i$ 位置 . 理由是 $i$ 位置不可能是没有奶牛的 , 所以 $j$ 的存在性显然 . 

至于 $\mathrm{next}_i=i$ 的情况 , 那就显然是一个**自环** . 此时不可能存在 $j\neq i$ , 使得 $\mathrm{next}_j=i$ . 

这也就是说 , 这 $n$ 个**结点**的入度和出度均为 $1$ , 且一共 $n$ 条边 . 那么就形成了一堆**简单环**构成的**森林** . 现在 , 我们就把**序列**问题转化到了**图上** . 

我们知道 , 如果没有 $M$ 的限制 , 而是可以**无限**走 : 那么一个环上的点最终都可以**彼此到达** . 这也是本题**测试点** $6-10$ 的情况 , 或者说是**银组**本题弱化版的情况 . 那么在这种情况下 , 我们开 $n$ 个 $\rm vector$ , 令 $\mathrm{pass}_i$ 表示 $i$ 在**一轮置换**中 , 一共经过了**哪些位置** , 比如还是样例中 , $\mathrm{pass}_1=\{1,2,3,4,5\}$ . 

对于一个环上的所有点 , 由于是无限置换 , 所以它们能到达的**位置集合**必然相同 . 只需要对每一个环上每一个点的 $\mathrm{pass}_i$ 进行遍历 , **位置集合**大小即为这一个环的答案 . 由于一个 $\mathrm{pass}_i$ 只会被统计 $1$ 次 , 而 $\mathrm{pass}_i$ 的总大小约为 $2K$ , 所以统计答案的时间复杂度为 $\mathcal O(K)$ 的 . 

那么现在回到有限制的情况 . 我们知道 , 在 $M$ 分钟内 , 我们进行了 :

$$\mathrm{times}=\lfloor\frac{M}{K} \rfloor$$

轮**置换** , 进行完这 $\mathrm{times}$ 轮置换后 , 又按照操作序列执行了 : 

$$\mathrm{rest\_opt}=M-\mathrm{times}*K$$

次**交换** (注意 , $K$ 次交换称为**一次置换**)

那么对于大小 $\leq \rm times$ 的环而言 , 这 $\rm times$ 次置换已经足以让一个点跑回自己 : 这个环的上所有点的**答案**还是像刚才讨论的**无限置换**一样 . 

那么大小 $> \rm times$ 的环呢 ? 观察环上的一个点 $x$ , 经过 $\rm times$ 轮置换后 , 它会到达的点是确定的 , 设为 $y$ . 而还要再从 $y$ 位置出发 , 又经过了 $\rm rest\_opt$ 次**交换** . 在这个过程中经过的**位置集合** , 就是点 $x$ 的答案 . 

所以我们现在需要另外 $n$ 个 $\rm vector$ , 来统计剩下的 $\rm rest\_opt$ 次交换中 , 每一个点经过了哪些位置 . 不妨使用 $\mathrm{rest}_i$ 表示剩下的 $\rm rest\_opt$ 次交换中 , 点 $i$ 经过的位置 . 

那么这样 , 可以 $\mathcal O(NK)$ 地求出每一个点的答案 . 不过这样有什么用 ? 还不如打暴力来得快 ...

别急 , 有一个很显然的优化方法 . 考虑已经求出了某个环上 $x$ 点的答案 , 那么对于他所指向的点 $\mathrm{next}_x$ ,  $\mathrm{next}_x$相比 $x$ 而言 , **不会遍历** $\mathrm{pass}_x$ , 以及 $\mathrm{rest}_y$ . (这里 $y$ 的意思和上面讨论时相同 , $x$ 虽然置换到了 $y$ , 但是并不能再从 $y$ 开始进行完整的**一轮置换**) . 但是 , 他多**遍历**了 $\mathrm{pass_y}$ , 和 $\mathrm{rest}_{\mathrm{next}_y}$ . 


所以我们破环成链 ,复制一遍增添在末尾 , 使用**双指针**移动 , 并且用一个桶 $\mathrm {buf}$ 记录**每个位置**的经过次数 , 从 $0$ 变成 $1$ 时答案增加 , 从 $1$ 变成 $0$ 时答案减少 . 这样就可以显然 $\mathcal O(K)$ 地统计答案 , 因为一个 $\mathrm {pass}_i$ 只会被**加入贡献**一次 , **消除贡献**一次 . $\mathrm{rest}_i$ 同理 . 

### 注意细节

由于本题题目较难 , 作者水平有限只能提供总体思路 , 实现细节方面只能提供一些参考 . 如下 : 

$1.$ 我在计算完 $\mathrm{pass}_i$ 集合后 , 会弹出**最后一个元素** . 因为最后一个元素就是 $\mathrm{next}_i$ , 在扫描 $\mathrm {pass}_{i}$ 和 $\mathrm{pass}_{\mathrm{next}_i} $ 时 , 可能会导致 $\mathrm{next}_i$ 被重复统计 . 所以需要弹出 . (没有被交换过的位置除外 , 不用弹出) **(不弹出也没事 , 只是不严谨 , 不会影响计数)**

$2.$ 记得消除贡献要消除完整 , 从一个环里出来后 , 要把桶清空 . 不要使用 $\rm memset$ , 可能会超时呢 . **(实际上好像没有超时 ? 但是不推荐这样做 .)**

$3.$ 特别注意 $\mathrm{times}=0$ 的情况 . 此时一轮置换都无法完成 . 我在代码中是使用 $\rm l \leq r$ 特判(因为如果为 $0$ , 必然出现双指针移动时时刻 $\rm l > r$)

$4.$ 注意 $M\leq 10^{18}$ , 一些变量需要使用 $\rm long \ long$ 存储 . 

### 代码部分

代码只有关键部分的注释 , 不推荐仔细浏览 (因为实现细节还是自己调为好) . 头文件 , 快读 , 快写就不放上来了 . 

跑得挺快的 , 总时间 $1s$ 左右 . (废话 , $\mathcal O(N+K)$ 的算法还能慢 ?) 

```cpp
int n;LL times,m,k;
int A[N],B[N],pos[N],nxt[N];
vector <int> pass[N],rest[N];
vector <int> cir[N];int cnt,len[N];bool vis[N];
int ans[N];
int buf[N],sum;

void GetCir(int x) {
	int to=x;
	do {
		vis[to]=1;
		cir[cnt].push_back(to);
		to=nxt[to];
	} while(to != x);
	len[cnt]=cir[cnt].size();
}
void Solve(int now) {
	if((LL)len[now] <= times) {
		//Add Contribution
		for(int i=0;i<len[now];++i) {
			int x=cir[now][i];
			for(int j=0;j<pass[x].size();++j) {
				int y=pass[x][j];
				buf[y] == 0 ? sum++,buf[y]++ : buf[y]++;
			}
		}
		for(int i=0;i<len[now];++i) {
			int x=cir[now][i];
			ans[x]=sum;
		}
		//Delete contribution
		for(int i=0;i<len[now];++i) {
			int x=cir[now][i];
			for(int j=0;j<pass[x].size();++j) {
				int y=pass[x][j];
				buf[y]=0;
			}
		}
		sum=0;
		return ;
	}
	for(int i=0;i<len[now]-1;++i)
		cir[now].push_back(cir[now][i]);
	//Previous Treatment , Add Contribution : l -> r
	int l=0,r=times-1;
	for(int i=l;i<=r;++i) {
		int x=cir[now][i];
		for(int j=0;j<pass[x].size();++j) {
			int y=pass[x][j];
			buf[y] == 0 ? sum++,buf[y]++ : buf[y]++;
		}
	}
	for(int i=0;i<rest[cir[now][r+1]].size();++i) {
		int y=rest[cir[now][r+1]][i];
		buf[y] == 0 ? sum++,buf[y]++ : buf[y]++;
	}
	ans[cir[now][l]]=sum;
	//Now Let's Get Each Answer
	while(l < len[now]-1) {
		int x=cir[now][l];
		if(l <= r) {
			for(int i=0;i<pass[x].size();++i) {
				int y=pass[x][i];
				buf[y] == 1 ? sum--,buf[y]-- : buf[y]--;
			}
		}
		x=cir[now][r+1];
		for(int i=0;i<rest[x].size();++i) {
			int y=rest[x][i];
			buf[y] == 1 ? sum--,buf[y]-- : buf[y]--;
		}
		++l,++r;
		x=cir[now][r];
		if(l <= r) {
			for(int i=0;i<pass[x].size();++i) {
				int y=pass[x][i];
				buf[y] == 0 ? sum++,buf[y]++ : buf[y]++;
			}
		}
		x=cir[now][r+1];
		for(int i=0;i<rest[x].size();++i) {
			int y=rest[x][i];
			buf[y] == 0 ? sum++,buf[y]++ : buf[y]++;
		}
		ans[cir[now][l]]=sum;
	}
	//Remember to Delete Contribution
	for(int i=l;i<=r;++i) {
		int x=cir[now][i];
		for(int j=0;j<pass[x].size();++j) {
			int y=pass[x][j];
			buf[y]=0;
		}
	}
	for(int i=0;i<rest[cir[now][r+1]].size();++i) {
		int y=rest[cir[now][r+1]][i];
		buf[y]=0;
	}
	memset(buf,0,sizeof buf);
	sum=0;
}

int main() {
	n=read(),k=read(),m=read();times=m/k;
	for(int i=1;i<=k;++i) 
		A[i]=read(),B[i]=read();
	for(int i=1;i<=n;++i)
		pass[i].push_back(i),rest[i].push_back(i),pos[i]=i;
	for(LL i=1;i<=k;++i) {
		pass[pos[A[i]]].push_back(B[i]),
		pass[pos[B[i]]].push_back(A[i]);
		if(i <= m-k*times)
			rest[pos[A[i]]].push_back(B[i]),
			rest[pos[B[i]]].push_back(A[i]);
		swap(pos[A[i]],pos[B[i]]);
	}
	for(int i=1;i<=n;++i) {
		nxt[pos[i]]=i;
		if(pass[i].size() != 1)
			pass[i].pop_back();
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])	++cnt,GetCir(i);
	for(int i=1;i<=cnt;++i)
		Solve(i);
	for(int i=1;i<=n;++i)
		Writes(ans[i]);
	return 0;
}
```

---

## 作者：UltiMadow (赞：15)

~~感觉是这次金组最好的题了吧（~~

~~T1 T2 都挺板子的~~

首先先看银组的弱化版（少了时间限制 $m$）

考虑每 $k$ 轮每个点都到哪里了

设 $k$ 轮后 $i$ 到达了 $p_i$，经过点的集合为 $s_i$

发现所有 $i\to p_i$ 的边组成了若干个环（每个店入度出度均为 1）

而一个点 $i$ 能到达的点集即为 $i$ 所在的环上所有 $s_i$ 的并集，于是遍历每个环，然后暴力合并即可

由于一共交换 $k$ 次，所以 $\sum\limits_{i=1}^n|s_i|=2k+n$

所以总时间复杂度 $\mathcal O(n+k)$

金组题比银组题增加了一个时间限制 $m$

记 $t=\lfloor \frac{m}{k}\rfloor$ 表示从一个点开始会完整走 $t$ 轮；$w=m-kt$ 表示走完 $t$ 轮还要走 $w$ 步

于是类似滑动窗口维护，每次暴力加入 $w$ 步，计算答案，再删除当前点，把加入 $w$ 步的节点剩下的都加进去

和银组题的复杂度分析一样，总复杂度 $\mathcal O(n+k)$

细节：注意 $t=0$ 的情况并且特判环大小 $\le t$ 的情况

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 200010
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define pii pair<int,int>
#define iter vector<pii>::iterator
using namespace std;
int n,K,m,vis[MAXN],ans[MAXN];
vector<pii>s[MAXN];
int cnt[MAXN],res;
int pos[MAXN],p[MAXN];
int q[MAXN],l,r;
void add(int x,int ti){
	for(iter it=s[x].begin();it!=s[x].end();it++){
		if(it->fi>ti)return;
		cnt[it->se]++;if(cnt[it->se]==1)res++;
	}
}
void del(int x,int ti){
	for(iter it=s[x].begin();it!=s[x].end();it++){
		if(it->fi>ti)return;
		cnt[it->se]--;if(!cnt[it->se])res--;
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&K,&m);
	for(int i=1;i<=n;i++)pos[i]=i,s[i].pb(mp(0,i));
	for(int i=1;i<=K;i++){
		int a,b;scanf("%lld%lld",&a,&b);
		s[pos[a]].pb(mp(i,b));s[pos[b]].pb(mp(i,a));
		swap(pos[a],pos[b]);
	}
	for(int i=1;i<=n;i++)p[pos[i]]=i;
	int t=m/K,w=m%K;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;l=1,r=0;bool fl=0;
		for(int u=i,tim=1;tim<=t;u=p[u],tim++){
			if(u==i&&tim!=1){fl=1;break;}
			add(u,K);q[++r]=u;
		}
		if(fl){
			ans[i]=res;vis[i]=1;del(i,K);
			for(int u=p[i];u!=i;u=p[u])
				ans[u]=ans[i],del(u,K),vis[u]=1;
			continue;
		}p[0]=i;
		for(int u=i,tim=1;u!=i||tim==1;u=p[u],tim++){
			int nxt=p[q[r]];add(nxt,w);
			ans[u]=res;del(nxt,w);
			add(nxt,K);del(u,K);
			l++;q[++r]=nxt;vis[u]=1;
		}
		for(int j=l;j<=r;j++)del(q[j],K);
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：10)

第一档部分分直接暴力，我们来从第二档部分分入手。

$M=10^{18}$ ，~~也就是说 M 没用~~，所有奶牛会把能到达的点全部到达一遍。

这些交换操作的循环节是 $K$ ，那就先预处理出每个位置的奶牛在 $K$ 次操作后经过哪些位置。

记 $K$ 次操作前在 $i$ 位置的奶牛经过了 $f_i$ 个位置 $s_{i,1\sim f_i}$。

显然 $K$ 次操作后原来在 $i$ 位置的奶牛到了 $s_{i,1\sim f_i}$ 位置，那就 $i$ 向 $s_{i,1\sim f_i}$ 连边。

这个时候就会出现一些环，然后 $M=10^{18 } $ 所以环上所有奶牛就会把所有环上点遍历，

这些奶牛的答案都是环上点 $s$ 的并集。这部分部分分就能做了，均摊复杂度 $\mathcal O(N+K)$。

发现 $M$ 没有限制的时候也差不多，假设要算一个 $x$ 点的答案，那么就相当要维护环上 $x$ “向前 $M$ 步”的答案。

假设现在找到的这个环有 $T$ 个点，那么 $P=\lfloor \dfrac MT \rfloor,Q=M \bmod T$，

那么 $x$ 的答案就是 从 $x$ 加上往前 $P-1$ 个点的所有 $s$ 和往前第 $P$ 个点“走” $Q$ 步的并集。

发现这个直接像滑动窗口一样维护就好了。。。均摊复杂度 $\mathcal O(N+K)$。

$\texttt{Code}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
#define pb push_back
#define MP std::make_pair
const int MaxN=2e5+50;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
#define fi first
#define se second
std::vector<std::pair<int,int> > S[MaxN];
std::vector<int> now;
int from[MaxN],vis[MaxN],cnt[MaxN],magius;
int ans[MaxN];
int n,K,m;
inline void add(int x){magius+=!(cnt[x]++);}
inline void del(int x){magius-=!(--cnt[x]);}
inline void count(int u)
{
	if(vis[u])
		return;
	vis[u]=1,now.pb(u);
	if((int)S[u].size())
		count(S[u].rbegin()->fi);
}
signed main(void)
{
	read(n,K,m);
	for(int i=1;i<=n;++i)
		from[i]=i,S[i].pb(MP(i,0));
	reg int x,y;
	for(int i=1;i<=K;++i)
		read(x,y),S[from[x]].pb(MP(y,i)),S[from[y]].pb(MP(x,i)),
		std::swap(from[x],from[y]);
	for(int i=1;i<=n;++i)
	{
		if(vis[i])
			continue;
		now.clear(),count(i);
		reg int P=m/K,Q=m%K;
		if(P>=(int)now.size())
			P=(int)now.size(),Q=0;
		reg int posR=P-1;
		for(int j=0;j<=posR;++j)
			for(int k=0;k<(int)S[now[j]].size()&&S[now[j]][k].se<=K;++k)
				add(S[now[j]][k].fi);
		for(int j=0;j<(int)now.size();++j)
		{
			posR=(posR+1)%(int)now.size();
			for(int k=0;k<(int)S[now[posR]].size()&&S[now[posR]][k].se<=Q;++k)
				add(S[now[posR]][k].fi);
			ans[now[j]]=magius;
			for(int k=0;k<(int)S[now[posR]].size()&&S[now[posR]][k].se<=Q;++k)
				del(S[now[posR]][k].fi);
			for(int k=0;k<(int)S[now[j]].size()&&S[now[j]][k].se<=K;++k)
				del(S[now[j]][k].fi);
			for(int k=0;k<(int)S[now[posR]].size()&&S[now[posR]][k].se<=K;++k)
				add(S[now[posR]][k].fi);
		}
		for(int j=0;j<(int)now.size();++j)
			for(int k=0;k<(int)S[now[j]].size()&&S[now[j]][k].se<=K;++k)
				cnt[S[now[j]][k].fi]=0;
		magius=0;
	}
	for(int i=1;i<=n;++i)
		write(ans[i]),ln;
	return 0;
}
```



---

## 作者：Eibon (赞：3)

先考虑[简单版](https://www.luogu.com.cn/problem/P7299)，经过在纸上的一些模拟，我们不难发现，奶牛们的移动轨迹将会变成一个个环，一个环可能由一个或多个奶牛构成。

具体表现为，一头奶牛在经过一轮 $k$ 次交换后，将会到达一个新位置，然后将会并上新位置在一轮中所能产生的贡献。

所以，我们不妨将每一固定位置在一轮中经过的位置加入一个 vector 中。然后将其与下一轮的开始位置既其这一轮的结束位置用并查集进行合并。

最后，用 set 统计每一个并查集的元素数量即可，每个并查集内的答案是相同的，因为时间无限。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
const int mod=1e9+7;
int T=1,n,k,m;
int s[maxn],fa[maxn];
vector<int>v[maxn];
set<int>ans[maxn];
int get_fa(int x)
{
	return fa[x]==x?x:fa[x]=get_fa(fa[x]);
}
void solve()
{
//	cout<<((double)(sizeof(a)+sizeof(b))/1024/1024);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		s[i]=i;
		fa[i]=i;
		v[i].push_back(i);
	}
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		v[s[x]].push_back(y);
		v[s[y]].push_back(x);
		swap(s[x],s[y]);
	}
	for(int i=1;i<=n;i++){
		int uu=get_fa(i);
		int vv=get_fa(s[i]);
		fa[uu]=vv;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<v[i].size();j++){
			int uu=get_fa(i);
			ans[uu].insert(v[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		int uu=get_fa(i);
		printf("%d\n",ans[uu].size());
	}
}
signed main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```
接下来考虑当前的问题，因为时间有限，有一些环将不能走完。

设 $t1$ 表示能走的完整循环的个数，$t2$ 表示最后走的不满一个循环的个数。

循环每一个点，同时开一个桶，记录颜色出现几次，维护两个函数，用于处理加上或减去 vector 中一段元素后的当前位置总数。

如果没有标记，说明是新环，并进行处理。

考虑先判断一个环能否在 $t1$ 时间内走完，如果能，就将环内所有答案都更新，打上标记。

不然，在判断过程中，我们将维护出当前点所经历的环上区间左右端点 $l$ 与 $r$。

类似于滑动窗口，只不过滑动距离由跳舞指令而定，在环上移动，同时打上标记。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
const int mod=1e9+7;
int T=1,n,k,m,tot,t1,t2,num,r;
int s[maxn],nxt[maxn],cnt[maxn],vis[maxn],ans[maxn],Q[maxn];
vector<pair<int,int>>v[maxn];
void ins(int p,int x)
{
	for(int i=0;i<v[p].size();i++){
		if(v[p][i].first>x){
			return;
		}
		int &col=cnt[v[p][i].second];
		col++;
		if(col==1){
			num++;
		}
	}
}
void del(int p,int x)
{
	for(int i=0;i<v[p].size();i++){
		if(v[p][i].first>x){
			break;
		}
		int &col=cnt[v[p][i].second];
		col--;
		if(!col){
			num--;
		}
	}
}
void solve()
{
//	cout<<((double)(sizeof(a)+sizeof(b))/1024/1024);
	scanf("%lld%lld%lld",&n,&k,&m);
	t1=m/k,t2=m%k;
	for(int i=1;i<=n;i++){
		s[i]=i;
		v[i].push_back({0,i});
	}
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		v[s[x]].push_back({i,y});
		v[s[y]].push_back({i,x});
		swap(s[x],s[y]);
	}
	for(int i=1;i<=n;i++){
		nxt[s[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}
		bool flag=0;
		int l=1,r=0;
		for(int p=i,t=1;t<=t1;p=nxt[p],t++){//p:当前位置,t:时间/第几步
			if(p==i&&t>1){
				flag=1;
				break;
			}
			ins(p,k);//都加进去
			Q[++r]=p;
		}
		if(flag){//走完一个循环
			ans[i]=num;vis[i]=1;del(i,k);
			for(int p=nxt[i];p!=i;p=nxt[p]){
				del(p,k);
				ans[p]=ans[i];
				vis[p]=1;
			}
			continue;
		}
		nxt[0]=i;
		for(int p=i,t=1;p!=i||t==1;p=nxt[p],t++){
			ins(nxt[Q[r]],t2);//时限之前加进去
			ans[p]=num;vis[p]=1;
			del(nxt[Q[r]],t2);
			ins(nxt[Q[r]],k);
			del(p,k);
			l++;r++;Q[r]=nxt[Q[r-1]];
		}
		for(int j=l;j<=r;j++){
			del(Q[j],k);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld\n",ans[i]);
	}
}
signed main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：vicissitudes (赞：2)

## 暴力
暴力就是去跑周期，然后记录下第 $i$ 个位置跑一个周期能到达的位置集合为 $s_i$。发现跑完周期后还有一部分剩余。

我们不关心还剩多少时间，只用存下在剩余时间内能到达的位置集合为 $rest_i$。

一个周期一个周期的枚举，将得到的位置集合放进一个桶中，同时维护个数即可。

虽然说的是集合，但是开数组时间会优一些。

## 性质1
我们将 $i$ 号节点经过一个周期后的位置记为 $pos_i$，容易得到，如果将 $i$ 连一条指向 $pos_i$ 的边，则原图会形成若干个简单环。

~~做多了就熟悉了。~~
>证明：
>
>首先，对于每个点，他只有一个出度，也就是指向 $pos_i$ 的边。所以总共有 $n$ 个点， $n$ 条边。成若干颗基环树。
>
>其次，对于每个节点，他一定有一个入度，也就是一个周期后他的位置上一定有数。所以这些基环树无叶子节点。所以成一个环状。证毕。

## 优化
所以我们考虑在环上优化暴力的过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/tfy7ov03.png)

如果是暴力，我们会把红箭头之间的 $s_i$ 全部放进桶中。清空桶，然后又把蓝箭头之间的 $s_i$ 放进来。我们发现区间长是定值，所以从红色到蓝色时， 只用删掉左边的红箭头的 $s_i$，加入右边蓝箭头的 $s_i$ 即可。

当然，上面忽略了 $rest$ 的情况。在统计答案前加入，统计答案后删掉即可。

注意，这是个**环**。

## 性质2
我们一直忽略了**维护桶的时间复杂度**，也许你在实现时可能发现一个一个的加数或减数，会不会有点暴力。其实时间复杂度是对的。

>证明：
对于一个操作 $a$ 和 $b$，我们会让 $a$ 和 $b$ 的位置集合的元素都加一。所以总的位置集合的元素个数为 $2 \times k$。所以我们在暴力维护桶时，最多会加 $2 \times k$ 次。

也就是总的时间复杂度为 $O(n + k)$。

丑陋的实现。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int n, k;
ll m;
vector<int> s[N], rest[N], ss[N];
int pos[N];
int pos2[N];

int cnt;
int cir[N];
vector<int> cc[N];

int w[N];
void add(vector<int> vec, int &res) {
	for(int v : vec) {
		if(!w[v]) res ++;
		w[v] ++;
	}
}

void del(vector<int> vec, int &res) {
	for(int v : vec) {
		w[v] --;
		if(!w[v]) res --;
	}
}

void dfs(int u, int now) {
	if(cir[u]) return ;
	cir[u] = now;
	for(int v : s[u]) ss[now].push_back(v);
	cc[now].push_back(u);
	dfs(pos2[u], now);
}

int ans[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 1; i <= n; i ++) {
		s[i].push_back(i);
		pos[i] = i;
	}
	for(int i = 1; i <= k; i ++) {
		int a, b;
		cin >> a >> b;
		s[pos[a]].push_back(b);
		s[pos[b]].push_back(a);
		swap(pos[a], pos[b]);
		if(i == m % k) {
			for(int j = 1; j <= n; j ++) {
				rest[j] = s[j];
			}
		}
	}
	for(int j = 1; j <= n; j ++) {
		pos2[pos[j]] = j;
	}
	for(int i = 1; i <= n; i ++) {
		if(!cir[i]) {
			cnt ++;
			dfs(i, cnt);
		}
	}//找环 
	ll t = m / k;
	for(int i = 1; i <= cnt; i ++) {
		int res = 0;
		memset(w, 0, sizeof w);
		if(t >= cc[i].size()) {//可以走完整个圈 
			add(ss[i], res);
			for(int j = 0; j < cc[i].size(); j ++) {
				int num = cc[i][j];
				add(rest[num], res);
				ans[num] = res;
				del(rest[num], res);
			}
		} else if(t == 0) {//只能走剩下的 
			for(int j = 0; j < cc[i].size(); j ++) {
				int num = cc[i][j];
				add(rest[num], res);
				ans[num] = res;
				del(rest[num], res);
			}
		} else {//先走圈再走剩下的 
			for(int j = 0; j < t - 1; j ++) {
				int num = cc[i][j];
				add(s[num], res);
			}
			for(int j = 0; j < cc[i].size(); j ++) {
				int nxt = cc[i][(j + t) % cc[i].size()];
				int now = cc[i][(j + t - 1) % cc[i].size()];
				int num = cc[i][j];	
				add(s[now], res);
				add(rest[nxt], res);
				ans[num] = res;
				del(rest[nxt], res);
				del(s[num], res);
			}
		}
	}
	for(int i = 1; i <= n; i ++) {
		cout << ans[i] << "\n";
	}
	return 0;
}
```

---

## 作者：Diaоsi (赞：2)

[[USACO21JAN] Dance Mooves G](https://www.luogu.com.cn/problem/P7298)

质量非常高的一道题，在此题中我们认为 $N$ 与 $K$ 同阶。

规定 $K$ 次交换为一轮置换，经过一轮置换之后，每头牛都会到达下一个位置（也有可能是原地不动）。

不妨将每个位置看成一个点，记点 $i$ 的前驱点为 $\text{pre}(i)$，后继点为 $\text{nxt}(i)$。

若将每头牛所在的当前位置和经过一轮置换之后的位置之间连上一条有向边，就会得到一个由若干个环构成的森林（可能存在自环），该部分的证明可以参考鸽巢原理。

这样每轮置换都可以看成每头牛从当前点沿着出边到达下一个点，不难发现在 $M$ 轮交换中，总共完成了 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 轮置换，经过 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 轮置换之后又进行了 $M-K\cdot\left\lfloor \dfrac{M}{K}\right\rfloor$ 次交换。

对于每一个点，我们可以整理出两个不可重集合 $T_i$ 和 $S_i$，$T_i$ 表示点 $i$ 在 $K$ 次交换中经过的点构成的集合，$S_i$ 表示点 $i$ 在 $M-K\cdot\left\lfloor \dfrac{M}{K}\right\rfloor$ 次交换中经过的点构成的集合。

特别地，$i \in S_i \subseteq T_i$ 且 $\sum\limits_{i=1}^n\left|T_i\right|$ 的大小是 $\mathcal{O}(N)$ 的。

接下来我们对 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 进行分类讨论。



------------



**第一种情况：** $\left\lfloor \dfrac{M}{K}\right\rfloor=0$

此时一轮置换都无法完成，显然每个点的答案即为 $\left|S_i\right|$，可以开一个桶进行快速统计。


------------
接下来我们需要对每个环单独统计答案，设当前环所含的点构成的集合为 $C$ 


**第二种情况：** $\left\lfloor \dfrac{M}{K}\right\rfloor>0$ 且 $\left\lfloor \dfrac{M}{K}\right\rfloor\geq\left|C\right|$ 

此时该环上的所有点都可以在 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 轮置换中到达，且环上每个点对应的点集 $T_j\ (j\in C)$ 中的点都会被环上的每个点到达。

于是该环上所有点的答案均为

$$\left|\bigcup_{j\in C}T_j\right|$$

求并集时可以使用一个桶进行判重。


------------

**第三种情况：** $\left\lfloor \dfrac{M}{K}\right\rfloor>0$ 且 $\left\lfloor \dfrac{M}{K}\right\rfloor < \left|C\right|$ 

此时对于环上的每一个点，不失一般性，记出发点为 $l$，经过 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 轮置换后到达的节点为 $r$。

将路径分为两部分，对于路径 $l\rightarrow \text{pre}(r)$，沿途点中所有的 $T_j\ (j\in\{l\rightarrow \text{pre}(r)\})$ 中的点都是会被到达的。

接下来单独考虑点 $r$，在经过 $\left\lfloor \dfrac{M}{K}\right\rfloor$ 轮置换后将从 $r$ 出发再进行 $M-K\cdot\left\lfloor \dfrac{M}{K}\right\rfloor$ 次交换，也就是说从 $r$ 出发还会到达点集 $S_r$ 中的所有点。

于是点 $l$ 的答案即为

$$\left|\left(\bigcup_{j\in\{l\rightarrow \text{pre}(r)\}}T_j\right)\bigcup S_r\right|$$

接下来考虑怎么通过 $l$ 的答案计算 $\text{nxt}(l)$ 的答案，容易发现 $\text{nxt}(l)$ 对应的答案为

$$\left|\left(\bigcup_{j\in\{\text{nxt}(l)\rightarrow r\}}T_j\right)\bigcup S_{\text{nxt}(r)}\right|$$

换句话说，我们只需要在 $l$ 的答案中去掉 $T_l\ ,\ S_r$ 的贡献，再加上 $T_r$ 和 $S_{\text{nxt}(r)}$ 的贡献，就可以计算出 $\text{nxt}(l)$ 的答案。

发现这个东西可以很轻松地用双指针维护。具体地说，先将断环成链并将一部分前缀复制至链尾，然后用双指针依次扫描。

开一个桶记录每个点出现了多少次，每次当右指针移向下一个点时，扫描下一个点的 $T,S$ 点集，对于点集中的每一个点，都在对应的桶上加一。若某个桶从空桶变成了含值的状态，则该点对答案的贡献为一。

同理，在左指针移向下一个点之前，应当移除这个点对应的点集当中的点对答案的贡献，操作与维护时右指针类似，若某个桶从含值状态变成了空桶，则应该扣除这个点对答案的贡献。



------------


**时间复杂度：**

由于我们只需要依次遍历每个点的 $T,S$ 点集，所以时间复杂度是均摊 $\mathcal{O}(N)$ 的。

既然你能找到这题，我相信你能瞬间做出来的。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N=200010,M=2000010,INF=0x3f3f3f3f;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline void swap(ll &x,ll &y){x^=y^=x^=y;}
ll n,K,m,tms,opt,ls[N],rs[N],p[N],t[N],ans[N],vis[N],nxt[N];
vector<ll> v[N],s[N],q;
int main(){
	scanf("%lld%lld%lld",&n,&K,&m);
	for(ll i=1;i<=n;i++)
		p[i]=i,v[i].push_back(i);
	for(ll i=1;i<=K;i++){
		scanf("%lld%lld",&ls[i],&rs[i]);
		v[p[ls[i]]].push_back(rs[i]);
		v[p[rs[i]]].push_back(ls[i]);
		swap(p[ls[i]],p[rs[i]]); 
	}
	for(ll i=1;i<=n;i++)nxt[p[i]]=i;
	for(ll i=1;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		for(ll j=nxt[i];j;j=nxt[j]){
			if(j==i)break;
			vis[j]=1;
		}
	}
	tms=m/K,opt=m%K;
	for(ll i=1;i<=n;i++)p[i]=i,s[i].push_back(i);
	for(ll i=1;i<=opt;i++){
		s[p[ls[i]]].push_back(rs[i]);
		s[p[rs[i]]].push_back(ls[i]);
		swap(p[ls[i]],p[rs[i]]);
	}
	memset(vis,0,sizeof(vis));
	if(!tms){
		for(ll i=1;i<=n;i++){
			ll sum=0;
			for(ll j=0;j<(ll)s[i].size();j++)
				!t[s[i][j]]?++sum,++t[s[i][j]]:++t[s[i][j]];
			printf("%lld\n",sum);
			for(ll j=0;j<(ll)s[i].size();j++)
				--t[s[i][j]];
		}
		return 0;
	}
	for(ll i=1;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;q.push_back(i);
		for(ll j=nxt[i];j;j=nxt[j]){
			if(j==i)break;
			vis[j]=1;q.push_back(j);
		}
		ll sum=0;
		if((ll)q.size()<=tms){
			for(ll j=0;j<(ll)q.size();j++)
				for(ll k=0;k<(ll)v[q[j]].size();k++)
					!t[v[q[j]][k]]?++sum,++t[v[q[j]][k]]:++t[v[q[j]][k]];
			for(ll j=0;j<(ll)q.size();j++){
				for(ll k=0;k<(ll)v[q[j]].size();k++)
					--t[v[q[j]][k]];
				ans[q[j]]=sum;
			}
		}
		else{
			for(ll j=0;j<tms;j++)
				q.push_back(q[j]);
			ll l=0,r=0;
			for(r=0;r<tms;r++)//r=tms
				for(ll k=0;k<(ll)v[q[r]].size();k++)
					!t[v[q[r]][k]]?++sum,++t[v[q[r]][k]]:++t[v[q[r]][k]];
			for(ll k=0;k<(ll)s[q[r]].size();k++)
				!t[s[q[r]][k]]?++sum,++t[s[q[r]][k]]:++t[s[q[r]][k]];
			ans[q[l]]=sum;
			while(l<=r){

				for(ll k=0;k<(ll)s[q[r]].size();k++)
					t[s[q[r]][k]]==1?--sum,--t[s[q[r]][k]]:--t[s[q[r]][k]];
				for(ll k=0;k<(ll)v[q[r]].size();k++)
					!t[v[q[r]][k]]?++sum,++t[v[q[r]][k]]:++t[v[q[r]][k]];
				++r;
				if(r==(ll)q.size())break;
				for(ll k=0;k<(ll)s[q[r]].size();k++)
					!t[s[q[r]][k]]?++sum,++t[s[q[r]][k]]:++t[s[q[r]][k]];
				for(ll k=0;k<(ll)v[q[l]].size();k++)
					t[v[q[l]][k]]==1?--sum,--t[v[q[l]][k]]:--t[v[q[l]][k]];
				++l;
				ans[q[l]]=sum;
			}
			for(;l<(ll)q.size();l++)
				for(ll k=0;k<(ll)v[q[l]].size();k++)
					--t[v[q[l]][k]];
		}
		q.clear();
	}
	for(ll i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：ClearluvXL (赞：1)

# Dance Mooves
## 思路
   将 $x,y$ 交换后，$x$ 上的点到了 $y$，$y$ 上的点到了 $x$。那么如果我们将 $k$ 次交换全部处理完，能得到最开始从每个点出发，中间经过了哪些点，最后停在哪个点。那么我们再进行**一轮交换**(一轮交换表示 $k$ 次交换)，现在在 $i$ 的点会经历上一轮在 $i$ 的点相同的步骤。所以我们从这里得到启示：**先预处理出一轮交换后从每个点出发，经过的点和最后停留的点，然后这些信息我们可以重复利用**，从 $i$ 出发我们记最后停留的点为 $nxt[i]$。
   
   而且我们可以大胆猜测，从 $i$ 跑到 $nxt[i]$，再从 $nxt[i]$ 跑到 $nxt[ntx[i]]$，一直延续下去，一定会形成若干个环。与其说是猜测，不如说这是一个显然的结论，这种题的套路。此处环上的点只包括一轮交换后的起点和终点，中间到过的点我们不妨将他理解为 $i$ 到 $nxt[i]$ 的路径。
   
   现在我引入一些变量：
   $T$ 为在 $M$ 分钟内能进行多少轮交换。
   $rest$ 表示经过 $T$ 轮交换后还需要进行**几次**交换。
   ***
   好。在我们找出每个环后，记录环的大小，此处我用 $siz$ 表示。
   
   如果 $siz\leq T$，那么环上每个 $i$ 到 $nxt[i]$ 路径上的点，环上其他点都能经过。所以此时只需要统计环上点以及路径上点集合的大小即可。
   
   如果 $siz>T$，说明从 $i$ 出发只能依次经过环上 $T$ 个点。处理环上问题，我们破环成链，复制一倍在后面。那么我们可以维护一个大小为 $T$ 的区间，向后移动就加点，并删去离开区间的点，类似于滑动窗口。**注意：我们可能还有 $rest$ ,所以我们要将 $rest$ 分钟内能到的点也加入集合**
   
   综上：我们需要预处理出 $i$ 到 $nxt[i]$ 上的点，甚至可以预处理出 $rest$ 分钟内从 $i$ 出发能到达的点。找出每个环，记录环的长度。破环成链，维护一个滑动的窗口，以及点的集合。
## 代码
```c++
#include<bits/stdc++.h>
#define endl '\n'
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=2e5+10;
const int INF=0x3f3f3f3f;

vector<int> res[N],pos[N];

pii a[N];
int p[N];//p[i]表示当前i这个位置这一轮是从p[i]出发的
int nxt[N];
int n;
ll k,m,rest,T;
bool v[N];

vector<int> cir[N];
int siz[N];

int cnt;

//找环，类似于tarjan
void Find(int x){
	int y=x;
	++cnt;
	do{
		v[y]=1;
		cir[cnt].push_back(y);
		y=nxt[y];
	}while(x!=y);
	siz[cnt]=cir[cnt].size();
}//end

int ans[N];
int t[N];//桶

int tot=0;//点的个数

//opt==1表示的是一轮交换
//opt==2表示的是rest次交换
//del同理
void add(int x,int opt){
	if(opt==1){
		for(int y:pos[x]){
			if(t[y]==0) tot++;
			t[y]++;
		}
	}
	else{
		for(int y:res[x]){
			if(t[y]==0) tot++;
			t[y]++;
		}
	}
}//end

void del(int x,int opt){
	if(opt==1){
		for(int y:pos[x]){
			if(t[y]==1) tot--;
			t[y]--;
		}
	}
	else{
		for(int y:res[x]){
			if(t[y]==1) tot--;
			t[y]--;
		}
	}
}//end

void solve(int id){
	if(siz[id]<=T){
		for(int x:cir[id]) add(x,1);
		for(int x:cir[id]) ans[x]=tot;
		for(int x:cir[id]) del(x,1);
		return;
	}
	else{
		for(int i=0;i<siz[id];i++){
			cir[id].push_back(cir[id][i]);
		}
		int l=0,r=T-1;
		
		for(int i=l;i<=r;i++) add(cir[id][i],1);
		add(cir[id][T],2);
		
		ans[cir[id][l]]=tot;
		while(l<siz[id]-1){
			if(l<=r) del(cir[id][l],1);
			del(cir[id][r+1],2);
			l++,r++;
			if(l<=r) add(cir[id][r],1);
			add(cir[id][r+1],2);
			ans[cir[id][l]]=tot;
		}
		for(int i=l;i<=r;i++) del(cir[id][i],1);	
		del(cir[id][r+1],2);
	}
}//end

int main(){
	
//	freopen("mooves.in","r",stdin);
//	freopen("mooves.out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin>>n>>k>>m;
	T=m/k;
	rest=m-k*T;
	
	for(int i=1;i<=k;i++){
		cin>>a[i].fi>>a[i].se;
	}
	
	for(int i=1;i<=n;i++){
		pos[i].push_back(i);
		res[i].push_back(i);
		p[i]=i;
	}
	
	for(int i=1;i<=k;i++){
		auto [x,y]=a[i];
		pos[p[x]].push_back(y);
		pos[p[y]].push_back(x);
		if(i<=rest){
			res[p[x]].push_back(y);
			res[p[y]].push_back(x);
		}
		swap(p[x],p[y]);
	}
	
	for(int i=1;i<=n;i++) nxt[p[i]]=i;
	for(int i=1;i<=n;i++){
		if(!v[i]){
			Find(i);//找环
			solve(cnt);
		}	
	}
	
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
	
	return 0;
}//end
```

---

## 作者：Binah_cyc (赞：1)

模拟赛出了这道题，结果写挂了。

为了方便，我们称 $k$ 次操作为 **一个周期**。

那么，可以发现，一共有 $\lfloor {m \over  k} \rfloor $ 个完整的周期与一个不完整的周期。现在分别对其进行讨论。

首先看完整的周期。手模一下样例可以发现，这个序列在进行一个周期的操作之后，会变成另一个序列，~~这不是废话吗~~，并且将起点与终点连边之后边之间会形成若干个 **环**。同时，每一个点只会有一个入度与一个出度。这就代表着从一个点一直向前走会走回自身。

同时，我们记录下来每一个位置上进行一个周期的操作之后能到达的点的集合。

那么，一个点进行 $k$ 个周期的操作后能够到达的点集就是在环上走 $k$ 步，并将沿途的点集取并之后的点集。

但是暴力的时间复杂度是 $O(nk)$ 的，我们需要考虑优化。

假设有两个点 $x$ 与 $y$，$y$ 是 $x$ 的后继。那么 $x$ 与 $y$ 的点集之间只相差了两个点。因此，我们可以维护一个类似于窗口的东西，快速的推出下一个点的答案。

还有一种情况，就是周期数大于等于环的大小。这样，每一个点都能走到另一个点。那么每一个点的答案就是一样的。

接下来，考虑不完整的周期的答案。

我们可以使用和完整的周期一样的处理方法，同步维护两个点，直接 $O(n)$ 的计算出一个点在走若干轮之后的终点。

在得到每一个点的终点之后，我们就可以暴力的处理最后的那一个周期了。

但是！我们并不知道每一个点能到达的具体点，只能知道它能到达的点数。

为了解决这个问题，我们可以先计算不完整的周期并将其存下来，在计算完整的周期时与之比对即可。

写的可能有点抽象，代码里的注释很多，可以看代码帮助理解。注释里一些叫法可能与题解里面不一样，但应该能看懂。

这个题目十分复杂，建议先多看几遍理解理解，然后尝试自己写，而不是对着正确代码抄。这样码力才会有进步。

最后附上[我的恶臭代码](https://www.luogu.com.cn/paste/oasojtcx)。

鸣谢：@[oyrzk](https://www.luogu.com.cn/user/708403) 帮助我修改代码中的注释与一些小细节。

---

## 作者：Thunder_S (赞：1)

[不一样的体验~~](https://www.cnblogs.com/Livingston/p/15159055.html)

## Solution

首先建议去做一下银组的弱化版：[P7299 [USACO21JAN] Dance Mooves S](https://www.luogu.com.cn/problem/P7299)。

- 银组的做法是

- 记录 $K$​ 次交换后每个点的位置，初末位置连边，则会形成一些环。

- 由于时间无限，则环上的每个点的答案是一样的，因此可以开个 $\text{vector}$ 记录每个点走过的位置，最后开个 $\text{set}$ 维护即可。

这两道题的区别在于金组的这道题目增加了时间的限制，这就意味着有些环是无法走完的。

先求出在时间限制下 $K$ 次换位完整的进行了多少轮，记为 $times$，同时求出还剩下多少次换位 $other$。

按照银组的做法先将环弄出来，记录每个环上有哪些点。

对于环的大小小于等于 $times$ 的，做法同银组，因为这些环是能够在 $times$ 轮 $K$ 次换位后，每个点至少回到原点一次，所以这个环上的答案都是一样的。（可能有点绕）

那么现在就思考那些环的大小大于 $times$ 的。

思考在这些环上的点是怎么移动的。

对于一个点 $i$，它在 $K$ 次换位后到达的点记为 $nxt_i$，那么这次换位中 $i$ 所经过的点可以用个 $\text{vector}$ 记录下来，然后对于 $times$ 轮 $K$，每次就可以记录下从 $i$ 到 $nxt_i$ 中经过的点，然后再从 $times$ 轮后的位置再往下走 $other$​ 次换位，最后统计答案就好。

但是这个方法的时间复杂度十分的高，达到了 $\mathcal O(NK)$。​

那么优化就可以考虑破环成链，将环复制一次，开个双指针，每次移动前删除当前 $l$​​ 的贡献和 $r+1$​​  的剩下贡献。然后移动，加入新的 $r$​​ 的贡献和 $r+1$​​ 的剩下贡献。（注意贡献和剩下贡献是不一样的）（其实就是滑动窗口维护）。

最后把贡献挂在 $l$ 上就可以了。

## Code

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#define ll long long
#define N 200005
using namespace std;
vector<int> spot[N],rest[N],ring[N];
int n,num,a[N],b[N],pos[N],fro[N],ans[N],buck[N],len[N];
ll m,k,times,other;
bool isin[N];
void getring(int x)
{
	int now=x;
	do
	{
		isin[now]=true;
		ring[num].push_back(now);
		now=fro[now];
	}while (now!=x);
	len[num]=ring[num].size();
}
void calcring(int now)
{
	int res=0;
	if ((ll)len[now]<=times)
	{
		for (int i=0;i<len[now];++i)
		{
			int x=ring[now][i];
			for (int j=0;j<spot[x].size();++j)
			{
				int y=spot[x][j];
				if (!buck[y]++) ++res;
			}
		}
		for (int i=0;i<len[now];++i)
			ans[ring[now][i]]=res;
		for (int i=0;i<len[now];++i)
		{
			int x=ring[now][i];
			for (int j=0;j<spot[x].size();++j)
			{
				int y=spot[x][j];
				buck[y]=0;
			}
		}
		return;
	}
	for (int i=0;i<len[now];++i)
		ring[now].push_back(ring[now][i]);
	for (int i=0;i<times;++i)
	{
		int x=ring[now][i];
		for (int j=0;j<spot[x].size();++j)
		{
			int y=spot[x][j];
			if (!buck[y]++) ++res;
		}
	}
	for (int i=0;i<rest[ring[now][times]].size();++i)
	{
		int x=rest[ring[now][times]][i]; 
		if (!buck[x]) ++res;
		++buck[x];
	}
	ans[ring[now][0]]=res;
	int l=0,r=times-1;
	while (l<len[now]-1)
	{
		int x=ring[now][l];
		if (l<=r)
		{
			for (int i=0;i<spot[x].size();++i)
			{
				int y=spot[x][i];
				if (buck[y]==1) --res;
				--buck[y];
			}
		}
		x=ring[now][r+1];
		for (int i=0;i<rest[x].size();++i)
		{
			int y=rest[x][i];
			if (buck[y]==1) --res;
			--buck[y];
		}
		++l;++r;
		x=ring[now][r];
		if (l<=r)
		{
			for (int i=0;i<spot[x].size();++i)
			{
				int y=spot[x][i];
				if (!buck[y]++) ++res;
			}
		}
		x=ring[now][r+1];
		for (int i=0;i<rest[x].size();++i)
		{
			int y=rest[x][i];
			if (!buck[y]++) ++res;
		}
		ans[ring[now][l]]=res;
	}
	for (int i=l;i<=r;++i)
	{
		int x=ring[now][i];
		for (int j=0;j<spot[x].size();++j)
			buck[spot[x][j]]=0;
	}
	for (int i=0;i<rest[ring[now][r+1]].size();++i)
	{
		int x=rest[ring[now][r+1]][i];
		buck[x]=0;
	}
	memset(buck,0,sizeof(buck));
}
int main()
{
	scanf("%d%lld%lld",&n,&k,&m);
	times=m/k;other=m%k;
	for (int i=1;i<=k;++i)
		scanf("%d%d",&a[i],&b[i]);
	for (int i=1;i<=n;++i)
		spot[i].push_back(i),rest[i].push_back(i),pos[i]=i;
	for (int i=1;i<=k;++i)
	{
		spot[pos[a[i]]].push_back(b[i]);
		spot[pos[b[i]]].push_back(a[i]);
		if (i<=other)
		{
			rest[pos[a[i]]].push_back(b[i]);
			rest[pos[b[i]]].push_back(a[i]);
		}
		swap(pos[a[i]],pos[b[i]]);
	}
	for (int i=1;i<=n;++i)
	{
		fro[pos[i]]=i;
		if (spot[i].size()!=1)	spot[i].pop_back();
	}
	for (int i=1;i<=n;++i)
		if (!isin[i]) ++num,getring(i);
	for (int i=1;i<=num;++i)
		calcring(i);
	for (int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

