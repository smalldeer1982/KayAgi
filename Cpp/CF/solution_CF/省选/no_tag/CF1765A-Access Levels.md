# Access Levels

## 题目描述

BerSoft is the biggest IT corporation in Berland, and Monocarp is the head of its security department. This time, he faced the most difficult task ever.

Basically, there are $ n $ developers working at BerSoft, numbered from $ 1 $ to $ n $ . There are $ m $ documents shared on the internal network, numbered from $ 1 $ to $ m $ . There is a table of access requirements $ a $ such that $ a_{i,j} $ (the $ j $ -th element of the $ i $ -th row) is $ 1 $ if the $ i $ -th developer should have access to the $ j $ -th document, and $ 0 $ if they should have no access to it.

In order to restrict the access, Monocarp is going to perform the following actions:

- choose the number of access groups $ k \ge 1 $ ;
- assign each document an access group (an integer from $ 1 $ to $ k $ ) and the required access level (an integer from $ 1 $ to $ 10^9 $ );
- assign each developer $ k $ integer values (from $ 1 $ to $ 10^9 $ ) — their access levels for each of the access groups.

The developer $ i $ has access to the document $ j $ if their access level for the access group of the document is greater than or equal to the required access level of the document.

What's the smallest number of access groups Monocarp can choose so that it's possible to assign access groups and access levels in order to satisfy the table of access requirements?

## 说明/提示

In the first example, we assign the documents to different access groups. Both documents have level $ 2 $ in their access group. This way, we can assign the developers, who need the access, level $ 2 $ , and the developers, who have to have no access, level $ 1 $ .

If they had the same access group, it would be impossible to assign access levels to developers $ 1 $ and $ 3 $ . Developer $ 1 $ should've had a lower level than developer $ 3 $ in this group to not be able to access document $ 1 $ . At the same time, developer $ 3 $ should've had a lower level than developer $ 1 $ in this group to not be able to access document $ 2 $ . Since they can't both have lower level than each other, it's impossible to have only one access group.

In the second example, it's possible to assign all documents to the same access group.

## 样例 #1

### 输入

```
3 2
01
11
10```

### 输出

```
2
1 2 
2 2 
1 2 
2 2 
2 1```

## 样例 #2

### 输入

```
2 3
101
100```

### 输出

```
1
1 1 1
1 10 5
8
3```

# 题解

## 作者：Francais_Drake (赞：2)

### 题意
有 $n$ 个工作人员和 $m$ 个文件。

你需要将 $m$ 个文件分成 $k$ 组，令第 $i$ 个文件分第 $s_i$ 组。然后对第 $i$ 个文件需要定一个访问等级 $c_i$，满足 $c_i$ 为 $[1,10^9]$ 内的整数。

然后对于第 $i$ 个工作人员和第 $j$ 组文件需要定一个访问等级 $b_{i,j}$，满足 $b_{i,j}$ 为 $[1,10^9]$ 内的整数。

同时给出一个 $n\times m$ 的数组 $a$，$a_{i,j}=1$ 表示 $b_{i,s_j}\ge c_j$，$a_{i,j}=0$ 表示 $b_{i,s_j}<c_j$。

求 $k$ 的最小值，以及任意一组对应的合法 $s,c,b$。$n,m\le 500$。
### 解法
考虑两个文件 $u,v$ 能合并为一组，当且仅当能够访问 $u$ 的人的集合和能够访问 $v$ 的人的集合有包含关系。如果存在某两个人 $x,y$ 满足 $x$ 只能访问 $u$ 而 $y$ 只能访问 $v$，则 $c_v>b_{x,s_u}\ge c_u$ 且 $c_u>b_{y,s_u}\ge c_v$，互相矛盾。

所以可以把所有文件按照能访问其的人数排序，然后如果能访问 $u$ 的人是能访问 $v$ 的人的子集（且 $u$ 排在 $v$ 的前面），则从 $u$ 到 $v$ 连一条边。

此时考虑从前往后考虑每份文件，选择是否在某一组内加文件的过程。设当前组内文件中能被最多人访问的文件为 $u$，则后面一定需要选择 $u$ 连向的某份文件 $v$，显然 $v$ 满足和该组内其他文件能同在一组内。问题等价于在一张 DAG 上找尽可能少的简单路径覆盖整张图，上最小路径覆盖即可。

构造方案时，由于一条路径上的 $c$ 需要严格单增，直接在路径上顺次确定每个 $c$，例如将路径上第 $i$ 个点的 $c$ 值设为 $i+1$ 即可。$s,b$ 不难构造。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=510;
const int maxd=1010;
const int maxm=260000;
const int INF=1145141919;
int n,m,i,j,k,u,v,t,a,tp,te=1;
int pe[maxn],st[maxn],cnt[maxn];
int num[maxn],rnk[maxn],col[maxn]; 
int h[maxd],d[maxd],c[maxd],to[maxm],nxt[maxm];
char s[maxn]; bool fl[maxm],vis[maxn],ac[maxn][maxn];
queue<int> q;
inline bool cmp(const int &x,const int &y){return cnt[x]<cnt[y];}
inline void cmax(int &x,int y){if(x<y) x=y;}
inline void Add(int x,int y){
	to[++te]=y; fl[te]=1; nxt[te]=h[x]; h[x]=te;
	to[++te]=x; nxt[te]=h[y]; h[y]=te;
}
int dinic(int p,int f){
	if(p==t) return 1;
	int to,fl=0;
	for(int &lp=c[p];lp;lp=nxt[lp]){
		if(!::fl[lp]) continue;
		to=::to[lp];
		if(d[to]!=d[p]+1) continue;
		if(!dinic(to,1)) continue;
		--f; ++fl; ::fl[lp]=0; ::fl[lp^1]=1;
		if(!f) break;
	}
	if(!fl) d[p]=0; return fl;
}
int main(){
	scanf("%d%d",&n,&m); t=m<<1|1;
	for(i=1;i<=m;++i) pe[i]=i;
	for(i=1;i<=n;++i){
		scanf("%s",s+1); 
		for(j=1;j<=m;++j){
			u=(s[j]=='0');
			ac[j][i]=u; cnt[j]+=u;
		}
	}
	sort(pe+1,pe+m+1,cmp);
	for(i=1;i<m;++i){
		u=pe[i]; tp=0;
		for(k=1;k<=n;++k) if(ac[u][k]) st[++tp]=k;
		for(j=i+1;j<=m;++j){
			v=pe[j];
			for(k=1;ac[v][st[k]]&&(k<=tp);++k);
			if(k>tp) Add(i,j+m);
		}
	}
	for(i=1;i<=m;++i) Add(0,i),Add(i+m,t); a=m;
	for(d[0]=1;;){
		memset(d+1,0,t<<2);
		memcpy(c,h,(t+1)<<2);
		for(q.push(0);!q.empty();){
			u=q.front(); q.pop();
			for(i=h[u];i;i=nxt[i]){
				if(!fl[i]) continue;
				v=to[i]; if(d[v]) continue;
				d[v]=d[u]+1; q.push(v);
			}
		} 
		if(!d[t]) break;
		a-=dinic(0,INF);
	}
	printf("%d\n",a);
	for(i=1,v=0;i<=m;++i){
		if(col[pe[i]]) continue;
		col[pe[i]]=++v; num[pe[i]]=k=2;
		for(u=i;;){
			for(j=h[u];(fl[j]||!to[j])&&j;j=nxt[j]);
			if(j){
				u=to[j]-m; 
				col[pe[u]]=v;
				num[pe[u]]=++k;
			}
			else break;
		}
	}
	for(i=1;i<=m;++i) printf("%d ",col[i]); putchar('\n');
	for(i=1;i<=m;++i) printf("%d ",num[i]); putchar('\n');
	for(i=1;i<=n;++i){
		for(j=1;j<=a;++j) rnk[j]=1;
		for(j=1;j<=m;++j){
			if(ac[j][i]) continue;
			cmax(rnk[col[j]],num[j]);
		}
		for(j=1;j<=a;++j) printf("%d ",rnk[j]); putchar('\n');
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

设 $S_i$ 表示有权限查看第 $i$ 份文件的人。

探究文件 $i$ 和文件 $j$ 可在同一组的充要条件。因为权限值较大的人可查看的题目一定包含权限值较小的人可查看的题目，且若满足该条件则容易构造出权限值，所以充要条件为 $S_i$ 包含或包含于 $S_j$。

这说明放在一组的文件 $i_1, i_2, \cdots, i_k$ 满足 $S_{i_1}\supseteq S_{i_2} \supseteq \cdots\supseteq S_{i_k}$。若 $S_i\supseteq S_j$ 则 $i$ 向 $j$ 连边，注意若 $S_i = S_j$，为防止产生环，当且仅当 $i < j$ 时连边。问题转化为 DAG 最小路径覆盖，网络流解决即可。

求出最小路径覆盖后，构造方案是平凡的。建图复杂度为 $n ^ 3 / w$，网络流部分复杂度为 $n ^ {2.5}$。[代码](https://codeforces.com/contest/1765/submission/185244118)。

---

