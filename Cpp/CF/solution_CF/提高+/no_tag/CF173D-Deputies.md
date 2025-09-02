# Deputies

## 题目描述

The Trinitarian kingdom has exactly $ n=3k $ cities. All of them are located on the shores of river Trissisipi, which flows through the whole kingdom. Some of the cities are located on one side of the river, and all the rest are on the other side.

Some cities are connected by bridges built between them. Each bridge connects two cities that are located on the opposite sides of the river. Between any two cities exists no more than one bridge.

The recently inaugurated King Tristan the Third is busy distributing his deputies among cities. In total there are $ k $ deputies and the king wants to commission each of them to control exactly three cities. However, no deputy can be entrusted to manage the cities, which are connected by a bridge — the deputy can set a too high fee for travelling over the bridge to benefit his pocket, which is bad for the reputation of the king.

Help King Tristan the Third distribute the deputies between the cities, if it is possible.

## 样例 #1

### 输入

```
6 6
1 2
4 1
3 5
6 5
2 6
4 6
```

### 输出

```
YES
1 2 1 2 2 1 ```

## 样例 #2

### 输入

```
3 1
1 2
```

### 输出

```
NO```

# 题解

## 作者：xiaolilsq (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF173D)

[可能更好的阅读体验？](https://www.cnblogs.com/lsq147/p/13709181.html)

## 题意简述

给定一个 $n$ 个点 $m$ 条边的二分图，其中 $n$ 是 $3$ 的倍数，请将这些点分成 $\frac{n}{3}$ 组，满足每组都恰好有 $3$ 个点，并且两两间没有连边。

## 题目分析

这题应该是细节加分类讨论题。

首先，假如二分图中的一边的点的个数恰好是 $3$ 的倍数，那么就可以直接将两边分开分组即可。

否则，必然是一边点数模 $3$ 等于 $1$ ，另一边模 $3$ 等于 $2$ ，不妨设等于 $1$ 的为左边，另一边为右边，方便起见，如果两点没有连边，那么我们称他们间连了“反边”，考虑分类讨论。

一、如果左边可以找到一个点，它和右边点的连“反边”数量要大于等于 $2$ ，那么说明可以在右边找到两个点和它一组，然后就变成模 $3$ 等于 $0$ 的情况了。

二、如果一不满足，那么不可能在右边找到两个点，满足它们都向左边的某一个点有连“反边”，所以如果我们可以在右边找到两个点，它们和左边点的连“反边”数量都大于等于 $2$ ，说明可以把右边这两个点和左边的四个点配对形成两组，剩下的就也是模 $3$ 等于 $0$ 的情况了。

三、如果一二都不满足，那么不可能有这样的分组方案，这个比较显然，可以自己想一想。

## 参考代码

感觉细节还是比较多，建议多检查检查。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ch() getchar()
#define pc(x) putchar(x)
using namespace std;
template<typename T>void read(T&x){
	static char c;static int f;
	for(c=ch(),f=1;c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c>='0'&&c<='9';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>void write(T x){
	static char q[65];int cnt=0;
	if(x<0)pc('-'),x=-x;
	q[++cnt]=x%10,x/=10;
	while(x)
		q[++cnt]=x%10,x/=10;
	while(cnt)pc(q[cnt--]+'0');
}
const int maxn=100005,maxm=100005;
struct Edge{
	int v,nt;
	Edge(int v=0,int nt=0):
		v(v),nt(nt){}
}e[maxm*2];
int hd[maxn],num;
void qwq(int u,int v){
	e[++num]=Edge(v,hd[u]),hd[u]=num;
}
int col[maxn],st[3][maxn],cnt[3],vis[maxn];
void dfs(int u){
	int c=col[u];
	st[c][++cnt[c]]=u;
	for(int i=hd[u];i;i=e[i].nt){
		int v=e[i].v;
		if(col[v])continue;
		col[v]=3-c;dfs(v);
	}
}
int main(){
	int n,m,Spe=0;read(n),read(m);
	for(int i=1;i<=m;++i){
		int u,v;
		read(u),read(v);
		qwq(u,v);qwq(v,u);
	}
	for(int i=1;i<=n;++i){
		if(col[i])continue;
		col[i]=1;dfs(i);
	}
	int tot=1;
	if(cnt[1]%3==0){
		puts("YES");Spe=1;
		for(int i=1;i<=cnt[1];++i){
			col[st[1][i]]=tot;
			if(i%3==0)++tot;
		}
		for(int i=1;i<=cnt[2];++i){
			col[st[2][i]]=tot;
			if(i%3==0)++tot;
		}
		for(int i=1;i<=n;++i)
			write(col[i]),pc(" \n"[i==n]);
	}
	else{
		if(cnt[1]%3==2){
			swap(st[1],st[2]);
			swap(cnt[1],cnt[2]);
		}
		int s0=0;
		for(int i=1;i<=cnt[1]&&!s0;++i){
			int u=st[1][i],sum=0;
			for(int j=hd[u];j;j=e[j].nt){
				int v=e[j].v;++sum;
			}
			if(sum+2<=cnt[2])
				s0=i;
		}
		if(s0){
			for(int j=hd[st[1][s0]];j;j=e[j].nt){
				int v=e[j].v;vis[v]=true;
			}
			int s1=0,s2=0;
			for(int i=1;i<=cnt[2]&&!s2;++i){
				int u=st[2][i];
				if(vis[u])continue;
				if(s1)s2=i;else s1=i;
			}
			memset(vis,0,sizeof vis);
			int sum=0;
			for(int i=1;i<=cnt[1];++i){
				if(i==s0)continue;
				col[st[1][i]]=tot;if((++sum)==3)sum=0,++tot;
			}
			for(int i=1;i<=cnt[2];++i){
				if(i==s1||i==s2)continue;
				col[st[2][i]]=tot;if((++sum)==3)sum=0,++tot;
			}
			col[st[1][s0]]=col[st[2][s1]]=col[st[2][s2]]=tot++;
			puts("YES");Spe=2;
			for(int i=1;i<=n;++i)write(col[i]),pc(" \n"[i==n]);
		}
		else{
			int s0=0,s1=0;
			for(int i=1;i<=cnt[2]&&!s1;++i){
				int u=st[2][i],sum=0;
				for(int j=hd[u];j;j=e[j].nt){
					int v=e[j].v;++sum;
				}
				if(sum+2<=cnt[1]){
					if(s0)s1=i;else s0=i;
				}
			}
			if(!s1)return puts("NO"),0;
			else{
				int s2=0,s3=0,s4=0,s5=0;
				for(int i=hd[st[2][s0]];i;i=e[i].nt){
					int v=e[i].v;vis[v]=true;
				}
				for(int i=1;i<=cnt[1]&&!s3;++i){
					int u=st[1][i];
					if(vis[u])continue;
					if(s2)s3=i;else s2=i;
				}
				memset(vis,0,sizeof vis);
				for(int i=hd[st[2][s1]];i;i=e[i].nt){
					int v=e[i].v;vis[v]=true;
				}
				for(int i=1;i<=cnt[1]&&!s5;++i){
					int u=st[1][i];
					if(vis[u])continue;
					if(s4)s5=i;else s4=i;
				}
				memset(vis,0,sizeof vis);
				int sum=0;
				for(int i=1;i<=cnt[1];++i){
					if(i==s2||i==s3||i==s4||i==s5)continue;
					col[st[1][i]]=tot;if((++sum)==3)sum=0,++tot;
				}
				for(int i=1;i<=cnt[2];++i){
					if(i==s0||i==s1)continue;
					col[st[2][i]]=tot;if((++sum)==3)sum=0,++tot;
				}
				col[st[2][s0]]=col[st[1][s2]]=col[st[1][s3]]=tot++;
				col[st[2][s1]]=col[st[1][s4]]=col[st[1][s5]]=tot++;
				puts("YES");Spe=3;
				for(int i=1;i<=n;++i)write(col[i]),pc(" \n"[i==n]);
			}
		}
	}
	return 0;
}

```

---

