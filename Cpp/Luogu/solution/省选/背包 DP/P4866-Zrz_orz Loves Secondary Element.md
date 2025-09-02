# Zrz_orz Loves Secondary Element

## 题目背景

zrz_orz赘喜欢二次元辣！！

## 题目描述

众所周知的是，zrz_orz是全机房最强的死宅。~~他甚至使用嘴遁使得Samcompu不得不在自己的网站上挂上时崎狂三~~。(话说Samcompu好像醒悟了又把狂三给去掉了。)作为新一代死宅的一员，从电脑壁纸到输入法皮肤，到处都是二次元的痕迹。所以，他经常在梦里梦见一些二次元的角色。

zrz_orz的梦，是由$n$个点和$n-1$条边构成的连通图。其中有$m$个节点上有一个二次元的角色。对于zrz_orz来说，每一个二次元的角色都有一个对应的$pos_i$和$val_i$表示这个角色在图上的哪一个节点以及与之聊天对zrz_orz来说会增加多少愉悦值。(由于某种原因，聊天的过程可以不用计入时间。)可惜的是，zrz_orz每一次做梦都只会做$tim_i$个单位时间。现在请你告诉他，他每一次做梦最多能获得多少愉悦值。

注：

1.zrz_orz每一次做梦都只会从1号节点开始走！

2.每一次做梦后zrz_orz梦境中的图都不会改变！

**3.每一次做完梦之后zrz_orz就必须要回到1号节点，否则他就会迷失在梦境里！**

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/25600.png)

第一天哪里都去不了。

第二天1->3->6->7->6->3->1获得最大愉悦值为7。

第三天所有的地方都可以走一遍。

Subtask 1(20 pts): 

$ 1 \leqslant T \leqslant 10 \qquad 1 \leqslant N \leqslant 1000 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 1000$

Subtask 2(40 pts):

$ 1 \leqslant T \leqslant 10^5 \qquad 1 \leqslant N \leqslant 10^5 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 10^5$

Subtask 3(40 pts):

$ 1 \leqslant T \leqslant 5*10^4 \qquad 1 \leqslant N \leqslant 5000 \qquad 1 \leqslant M \leqslant 100 \qquad 1 \leqslant  tim_k \leqslant 100 \qquad 1 \leqslant w_i \leqslant 5$

For all test points:

$ 1 \leqslant pos_j,u_i,v_i \leqslant N \qquad 1 \leqslant \sum val_j \leqslant 2e9 \qquad 1 \leqslant w_i \leqslant 20 \qquad 1 \leqslant tim_k \leqslant 10^5 $

注意: 标记的分数就是这个Subtask的分数，每一个Subtask必须全对才能得分。Subtask 2的时限为1.5s。

$$ \color{white} \text{NOIP 2合1} $$

## 样例 #1

### 输入

```
7 3 3
1 2 2
1 3 1
2 4 1
2 5 10
3 6 1
6 7 2
4 5
5 50
7 7
1
10
100
```

### 输出

```
0
7
62```

# 题解

## 作者：CQ_Bob (赞：3)

题解摘自[做题记录](https://www.luogu.com.cn/article/xbpjecpf)。

## 分析

不难发现，只有最多 $2m$ 个点是有用的。考虑先对这 $m$ 个点建立虚树。

对于一种行走方案，因为每条经过过的边都走了 $2$ 遍，所以就相当于将每条边的边权乘 $2$ 之后的边权和。下面任何表示的距离都是原树上距离的 $2$ 倍。

发现 $m$ 十分小，考虑暴力 DP。定义状态函数 $f_{i,j}$ 表示 $i$ 为根的子树中，花费 $j$ 的时间最多能得到的价值。因为我们是路径，所以需要保证我们选择的点形成连通块。那么对于 $u$ 来说，它就是必选的了。那么对于选择 $u$ 的一个儿子 $v$ 的子树，$u\to v$ 这条边也是必须经过的。有：$f_{u,x}=\max\limits_{y=0}^{x-w} f_{u,y}+f_{v,x-y-w}$。这个直接树上背包的时间复杂度是 $O(mV)$ 的。

然后对于询问，预处理前缀 $\max$ 可以做到 $O(1)$。算上建虚树的复杂度，就是 $O(m\log m+mV)$。

## 代码

```cpp
il void dfs1(int u,int fa){
	dfn[u]=++cnt;
	f[u][0]=fa,dep[u]=dep[fa]+1;
	for(re int i=1;i<22;++i) f[u][i]=f[f[u][i-1]][i-1];
	for(auto v:e[u])
	if(v.x!=fa){
		dis[v.x]=dis[u]+2*v.y;
		dfs1(v.x,u);
	}
	return ;
} 
il int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re int i=21;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re int i=21;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
il void build(){
	len=m;
	b[++len]=1;
	int len_=len;
	sort(b+1,b+len+1,[](int x,int y){
		return dfn[x]<dfn[y];
	});
	for(re int i=2;i<=len_;++i) b[++len]=lca(b[i],b[i-1]);
	sort(b+1,b+len+1,[](int x,int y){
		return dfn[x]<dfn[y];
	});
	len=unique(b+1,b+len+1)-(b+1);
	for(re int i=1;i<=len;++i) id[b[i]]=i,rev[i]=b[i];
	for(re int i=1;i< len;++i) E[id[lca(b[i],b[i+1])]].push_back({i+1,dis[b[i+1]]-dis[lca(b[i],b[i+1])]});
	return ;
}
il void dfs2(int u,int s){
	siz[u]=0;
	if(s==0){
		dp1[u][0]=val[rev[u]];
		for(auto v:E[u]){
			dfs2(v.x,s);
			for(re int w=min(M,siz[u]+v.y+siz[v.x]);w>=0;--w)
			for(re int x=0;x<=min(w-v.y,siz[u]);++x)
				dp1[u][w]=max(dp1[u][w],dp1[u][x]+dp1[v.x][w-v.y-x]);
			siz[u]+=v.y+siz[v.x];
		}
		for(re int i=1;i<=M;++i)
			dp1[u][i]=max(dp1[u][i],dp1[u][i-1]);
	}
	else{
		dp2[u][0]=val[rev[u]];
		for(auto v:E[u]){
			dfs2(v.x,s);
			for(re int w=min(M,siz[u]+v.y+siz[v.x]);w>=0;--w)
			for(re int x=0;x<=min(w-v.y,siz[u]);++x)
				dp2[u][w]=max(dp2[u][w],dp2[u][x]+dp2[v.x][w-v.y-x]);
			siz[u]+=v.y+siz[v.x];
		}	
		for(re int i=1;i<=M;++i)
			dp2[u][i]=max(dp2[u][i],dp2[u][i-1]);
	}
	return ;
}

il void solve(){
	n=rd,m=rd,t=rd;
	if(m<=20) M=100000;
	else M=100;
	for(re int i=1;i< n;++i){
		int u=rd,v=rd,w=rd;
		e[u].push_back({v,w}),
		e[v].push_back({u,w});
	}
	for(re int i=1;i<=m;++i){
		int x=rd;
		b[i]=x,val[x]=rd;
	}
	dfs1(1,0),build(),dfs2(1,(M==100));
	while(t--){
		int x=rd;
		if(M==100) printf("%lld\n",dp2[1][x]);
		else printf("%lld\n",dp1[1][x]);
	}
    return ;
}
```

---

## 作者：mrsrz (赞：3)

要走回1，只要把所有走过的边的边权乘2即可。

Subtask 1和2，观察到$m$比较小，可以考虑枚举所有的状态（取或不取该点的点权）。

然后题解说“直接暴力算出需要走多久”，但这样时间复杂度不对啊，是$O(2^mn)$，给一条链就挂了啊。

我的做法是重新建一棵树。建法如下：

> 遍历原树，如果一个节点有点权，则该点加入新树中。  
> 如果一个节点的儿子中有超过1个在新树中且“存在”，则该节点也加入新树。  
> 每在新树中添加一个节点，则把该节点的所有儿子标记为“不存在”（原来都是“存在”，标记时只要标记儿子中在新树中的节点即可）。

新树的边权为两点在原树中的距离。

这样建树，原来有$m$个节点，对于两个“存在”的点，至多产生一个没有点权且加入新树中的点，产生后这两个点都“不存在”，所以产生的新点不超过$m$个。树的总大小不超过$2m$。

然后在新树中暴力即可。

之后对状态按需要的路程排序，然后离线询问扫即可。

时间复杂度$O(2^mm)$。

Subtask 3，就是树形dp。

设$dp[i][j]$表示以$i$为根的子树，走的边权总和不超过$j$的最大价值。

然后就是个背包。

对于每个儿子，枚举$k$，然后$dp[i][j]=max(dp[i][j],dp[son][k]+dp[i][j-k-dis_{i,son}])$。

由于读入的$tim$最多100，且路程要乘2，所以算到$50$即可。

时间复杂度$O(50n)$，如果用上面建新树的方法，可以优化到$O(n+50m)$。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#include<algorithm>
int n,m,T;
inline int readint(){
    int c=getchar(),d=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())
    d=(d<<3)+(d<<1)+(c^'0');
    return d;
}
struct edge{
    int to,nxt,dis;
}e[200005];
int head[100005],cnt=0;
namespace Task1{
    using VI=std::vector<int>;
    const int N=100005;
    int num[N],val[22],pos[22],to[N],ans[N],dis[N];
    std::pair<int,int>q[N];
    struct NewGraph{
        edge e[666];
        int n,cnt,fa[666],col[666],tot,head[666],pos[666],dis[666];
        inline void addedge(int u,int v,int t){
            e[++cnt]=(edge){v,head[u],t};
            head[u]=cnt;
            e[++cnt]=(edge){u,head[v],t};
            head[v]=cnt;
        }
        inline NewGraph():n(0),cnt(0),tot(0){memset(num,0,sizeof num);memset(fa,0,sizeof fa);memset(dis,0,sizeof dis);}
        inline int newnode(){return ++n;}
        inline void dfs(int now,int pre){
            for(int i=head[now];i;i=e[i].nxt)
            if(e[i].to!=pre){
                fa[e[i].to]=now;
                dis[e[i].to]=dis[now]+e[i].dis;
                dfs(e[i].to,now);
            }
        }
        inline int color(int x){
            int ret=0;
            for(;x&&col[x]!=tot;x=fa[x])
            col[x]=tot,ret+=dis[x]-dis[fa[x]];
            return ret;
        }
    }G;
    struct zzt{
        int val,tim;
        inline bool operator<(const zzt&rhs)const{return tim<rhs.tim;}
    }p[1<<20|2];
    VI rebuild(int now,int pre){
        VI v;
        for(int i=head[now];i;i=e[i].nxt)
        if(e[i].to!=pre){
            dis[e[i].to]=dis[now]+e[i].dis;
            VI ret=rebuild(e[i].to,now);
            for(int i:ret)v.push_back(i);
        }
        if(~num[now]||v.size()>1||now==1){
            int id=G.newnode();
            to[id]=now;
            for(int i:v){
                G.addedge(i,id,dis[to[i]]-dis[now]);
            }
            v.clear();
            v.push_back(id);
            if(~num[now])G.pos[num[now]]=id;
        }
        return v;
    }
    void dfs(int now,int zt,int value){
        if(now==m){
            ++G.tot;
            int tim=0;
            for(int i=zt,nx;i;i^=1<<nx){
                nx=__builtin_ctz(i);
                tim+=G.color(G.pos[nx]);
            }
            p[zt]=(zzt){value,tim<<1};
        }else{
            dfs(now+1,zt,value);
            dfs(now+1,zt|(1<<now),value+val[now]);
        }
    }
    void main(){
        memset(pos,0,sizeof pos);
        memset(num,-1,sizeof num);
        for(int i=0;i<m;++i){
            pos[i]=readint();
            val[i]=readint();
            num[pos[i]]=i;
        }
        memset(dis,0,sizeof dis);
        VI I=rebuild(1,0);
        G.dfs(I[0],0);
        dfs(0,0,0);
        const int C=1<<m;
        std::sort(p,p+C);
        for(int i=1;i<=T;++i)q[i].first=readint(),q[i].second=i;
        std::sort(q+1,q+T+1);
        int maxval=0;
        for(int i=1,zz=0;i<=T;++i){
            while(zz<C&&p[zz].tim<=q[i].first){
                maxval=std::max(maxval,p[zz].val);
                ++zz;
            }
            ans[q[i].second]=maxval;
        }
        for(int i=1;i<=T;++i)
        printf("%d\n",ans[i]);
    }
}
namespace Task2{
    const int N=5005;
    int val[N];
    int dp[N][52];
    void dfs(int now,int pre){
        for(int i=head[now];i;i=e[i].nxt)
        if(e[i].to!=pre){
            dfs(e[i].to,now);
            for(int j=50;j>=e[i].dis;--j)
            for(int k=0;k+e[i].dis<=j;++k){
                dp[now][j]=std::max(dp[now][j],dp[e[i].to][k]+dp[now][j-k-e[i].dis]);
            }
        }
        for(int i=0;i<=50;++i)
        dp[now][i]+=val[now];
    }
    void main(){
        memset(val,0,sizeof val);
        while(m--){
            int pos=readint();
            val[pos]=readint();
        }
        memset(dp,0,sizeof dp);
        dfs(1,0);
        for(;T--;){
            int tim=readint()>>1;
            printf("%d\n",dp[1][tim]);
        }
    }
}
int main(){
    n=readint(),m=readint(),T=readint();
    for(int i=1,u,v,t;i<n;++i){
        u=readint(),v=readint(),t=readint();
        e[++cnt]=(edge){v,head[u],t};
        head[u]=cnt;
        e[++cnt]=(edge){u,head[v],t};
        head[v]=cnt;
    }
    if(m<=20)Task1::main();
    else Task2::main();
    return 0;
}
```

---

## 作者：CYJian (赞：3)

其实题目并不难,只是相当于做了两道题而已..

首先需要了解的一点是:我们最终需要回到1号点,所以每一条边肯定都会走至少2次,并且对于一棵树,一条边允许走两次的话存在一笔画的方案.所以我们直接把走的所需时间*2就好了.这样就不需要考虑回到1号点的问题了.

然后对于Subtask 0..

实际上就是Subtask 1的做法..

直接dfs暴力枚举和不和第$i$个角色对话并且记录愉悦值,然后直接暴力算出需要走多久.

然后把上面的东西按照走的时间排个序,然后对于每一个询问选择最大的愉悦值就好了..

Subtask 2的话..

树形DP..

我们可以定义状态$f[i][j]$表示在$i$的子树中走最多$j$的单位时间所能获得的最大愉悦值.

这个转移方程应该比较显然吧..如果不太清楚直接看代码部分就好了..(其实只是懒而已..)

[代码](https://www.luogu.org/paste/9ysudvv6)

---

## 作者：ztlh (赞：1)

题外话：联合省选结束后一直在摆，但是快期中考了，所以康复训练，OI 复兴（雾

## Solution

先考虑 Subtask 3。注意到 $1 \le tim_k \le 100$，考虑树形 DP，并将询问的时间限制写进状态里。

不难发现转移是个分组背包的形式。询问可以 $\mathcal{O}(1)$ 回答。该部分时间复杂度 $\mathcal{O}(10000 N)$。

再考虑 Subtask 1&2。看到 $M \le 20$ 容易想到状压。枚举所有可能的特殊点（即对答案有贡献的点）组合，转移时把其中一个点加进其余点组成的状态（已知）中。

加点时，我们需要找到新点与每个已有点的 LCA 中，深度最大的那个。新点到这个 LCA 的距离的两倍就是加入这个点的最小时间。

我们可以预处理出 dfn 序，将所有特殊点按 dfn 序排序。每枚举到一个状态 $s$ 时（$s$ 为 $M$ 位 $01$ 串），取 $\text{lowbit}(s)$ 作为要加入的新点。由于祖先节点的 dfn 一定在子节点之前，容易发现和新点的 LCA 深度最大的已有点一定是 $\text{lowbit}(s-\text{lowbit}(s))$，即 $s$ 右数第二位。

该部分时间复杂度 $\mathcal{O}(2^M\log N)$。

## Code


```cpp
#include<bits/stdc++.h>
#define N 100005
#define M 5005
#define lb(xx) ((xx)&-(xx))
using namespace std;
int n,m,t;
int val[N];
int sp[105];
int tim[N];
int idx[N],dfn[N];
inline bool cmp(int u,int v) {return dfn[u]<dfn[v];}
struct Edge{
	int u,v,w,nxt;
}e[N<<1];
int head[N],tot=2;
inline void add(int u,int v,int w){
	e[tot].u=u; e[tot].v=v; e[tot].w=w;
	e[tot].nxt=head[u]; head[u]=tot++;
}
int fa[N][25],dis[N][25];
int dep[N],dfn_=0;
void dfs(int u,int f,int de,int w){
	fa[u][0]=f; dis[u][0]=w; dep[u]=de;
	dfn[u]=++dfn_; idx[dfn_]=u;
	for(int i=head[u];i;i=e[i].nxt)
		if(!dfn[e[i].v]) dfs(e[i].v,u,de+1,e[i].w);
}
inline int GetLca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=20;i>=0;i--)
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	for(int i=20;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	if(u!=v) u=fa[u][0];
	return u;
}
inline int GetDis(int u,int v){
	int res=0;
	for(int i=20;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v]){
			res+=dis[u][i];
			u=fa[u][i];
		}
	}
	return res;
}
struct Ans1{
	int ans;
	int t;
}ans[N<<4];
inline bool cmp2(Ans1 x,Ans1 y) {return x.t<y.t;}
int dp[M][105];
void Solve(int u,int f){
	bool lf=1;
	for(int i=head[u],v,w;i;i=e[i].nxt){
		v=e[i].v; w=e[i].w;
		if(v==f) continue;
		lf=0; Solve(v,u);
		for(int j=100;j>=0;j--)
			for(int k=0;k<=100;k++)
				if(j-k-w*2>=0) dp[u][j]=max(dp[u][j],dp[u][j-k-w*2]+dp[v][k]);
	}
	for(int i=0;i<=100;i++) dp[u][i]+=val[u];
}
int maxt=0;
int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		val[u]=v; sp[i]=u;
	}
	for(int i=1;i<=t;i++)
		scanf("%d",&tim[i]),maxt=max(maxt,tim[i]);
	if(t<=50000&&n<=5000&&maxt<=100){
		Solve(1,0);
		for(int i=1;i<=t;i++)
			printf("%d\n",dp[1][tim[i]]);
	}
	else{
		dfs(1,1,1,0);
		for(int j=1;j<=20;j++)
			for(int i=1;i<=n;i++){
				fa[i][j]=fa[fa[i][j-1]][j-1];
				dis[i][j]=dis[i][j-1]+dis[fa[i][j-1]][j-1];
			}
		sort(sp+1,sp+m+1,cmp);
		ans[0].ans=0; ans[0].t=0;
		for(int s=1,s_,a_,a,b_,b,lca;s<(1<<m);s++){
			s_=s; s_-=(a_=lb(s_)); a=0;
			while(a_) {a_>>=1; a++;} a=sp[a];
			if(!s_){
				ans[s].ans=val[a];
				ans[s].t=2*GetDis(a,1);
				continue;
			}
			b_=lb(s_);
			b=0;
			while(b_) {b_>>=1; b++;} b=sp[b];
			lca=GetLca(a,b); ans[s].t=ans[s_].t+2*GetDis(a,lca);
			ans[s].ans=ans[s_].ans+val[a];
		}
		sort(ans,ans+(1<<m),cmp2);
		for(int i=1;i<(1<<m);i++)
			ans[i].ans=max(ans[i].ans,ans[i-1].ans);
		for(int i=1,l_,r_,m_;i<=t;i++){
			l_=0; r_=(1<<m)-1;
			while(l_<r_){
				m_=(l_+r_+1)>>1;
				if(ans[m_].t<=tim[i]) l_=m_;
				else r_=m_-1;
			}
			printf("%d\n",ans[l_].ans);
		}
	}
	return 0;
}
```

---

