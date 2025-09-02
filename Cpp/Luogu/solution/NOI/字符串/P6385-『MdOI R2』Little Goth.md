# 『MdOI R2』Little Goth

## 题目背景

小 M 和小 B 是一对好朋友，她们很喜欢爬山。

## 题目描述

山可以抽象为一个长为 $n$ 的字符串 $S$，串中仅包含小写字母。

对于一个字符串 $S$，我们定义 $|S|$ 表示串的长度，$S_{L\ldots R}$ 表示由 $S$ 中从左往右数，第 $L$ 个字符到第 $R$ 个字符依次连接形成的字符串。

小 M 一开始的位置是 $i$，她想要到达位置在 $k$ 处的山顶，而小 B 则要帮助她。为此，她们需要进行一系列操作。

她们**必须**在所有操作之前使用**一次**位于 $p$ 处的传送法阵，通过施展法术，可以使小 B 的位置变为任意满足 $j \geq i$ 且 $S_{i \ldots j} = S_{p \ldots p + (j-i)}$ 的 $j$。但同时，她们需要付出 $n-j$ 的代价。保证这样的 $j$ 存在。

之后，假设小 M ，小 B 的位置分别为 $i$ 和 $j$，她们可以任意次进行下列操作中的一种：

- 让小 M 爬，即令 $i=i+1$ 或 $i = i-1$。如果这一步操作之后 $i>j$，则 令 $j=i$。

- 让小 B 爬，即令 $j=j+1$ 或 $j=j-1$。如果这一步操作之后 $i>j$，则令 $i=j$。

- 使用螺旋升天，具体而言，选择两个下标 $l$ 和 $r$，满足 $S_{l \ldots r} = S_{i \ldots j}$，然后令 $i=l,j=r$。

出于某些原因，任何一次操作结束后，需要保证 $1 \leq i , j \leq n$。进行一次上述任意一种操作，都需要付出 $1$ 的代价。

爬山是很累的，因此她们想知道，至少需要付出多少代价才能让小 M 到达山顶，也就是让 $i=k$。又因为她们很喜欢爬山，她们有很多组询问要问你。

## 说明/提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。

[样例输入](https://www.luogu.com.cn/paste/j7u8z9ir) [样例输出](https://www.luogu.com.cn/paste/fh19p0a4)

--------
【样例解释】

对于样例的第一组询问，使用传送法术时，只能令 $j=5$，付出 $8-5=3$ 的代价。之后，首先使用一次第三种操作，选择 $l=2,r=2$，令 $i=l,j=r$，然后使用一次第一种操作，令 $i-1$，即可使 $i=k$，一共付出 $5$ 的代价。

对于第二组询问，可以选择 $j=2$，付出 $8-2=6$ 的代价，然后使用一次第三种操作，选取 $l=4,r=5$ 并使 $i=l,j=r$，然后进行一次第一种操作，令 $i+1$ 即可使 $i=k$。一共付出 $8$ 的代价。

---

【数据范围】

**本题采用捆绑测试。**

对于全部数据，保证 $1 \leq n,q \leq 3\times 10^4$，$S$ 中仅包含小写字母。

| 子任务编号 |      $n\leq$      |     $q \leq$      |      特殊性质       | 分值 | 时间限制 |
| :--------: | :---------------: | :---------------: | :-----------------: | :--: | :------: |
| Subtask 1  |       $15$        |       $15$        |         无          | $3$  |    1s    |
| Subtask 2  |       $80$        |       $80$        |         无          | $14$ |    1s    |
| Subtask 3  |  $2 \times 10^4$  |  $2 \times 10^4$  |   $S$ 中仅包含`a`   | $8$  |    3s    |
| Subtask 4  |  $2 \times 10^4$  |  $2 \times 10^4$  |        $S_1$        | $7$ |    3s    |
| Subtask 5  |       $400$       |       $400$       |         无          | $9$  |    1s    |
| Subtask 6  |  $2\times 10^4$   |  $2 \times 10^4$  | 所有询问的 $k$ 相同 | $10$ |    3s    |
| Subtask 7  |      $10^3$       |      $10^3$       |         无          | $10$ |    2s    |
| Subtask 8  | $1.5 \times 10^4$ | $1.5 \times 10^4$ |         无          | $11$ |    3s    |
| Subtask 9  |  $3 \times 10^4$  |  $3 \times 10^4$  |         无          | $28$ |    3s    |



性质 $S_1$ 是，对于给定的 $p$，满足条件的 $j$ 唯一。



## 样例 #1

### 输入

```
8 2
dacdaaaa
5 8 1
1 4 5```

### 输出

```
5
8```

# 题解

## 作者：EternalAlexander (赞：16)

终于有一个不是 Ynoi 的月赛 F 题了，是不是很感动

---

若无特别说明，$i$，$j$ 和 $k$ 表示小 M 的位置，小 B 的位置和山顶的位置。操作串表示进行操作三时的 $S_{i \cdots j}$。

过于显然的结论不说明了，~~需要详细题解请报讲评~~

#### 结论 -1
在所有合法的 $j$ 中，选取最大的作为小 B 的初始位置一定不劣。

#### 结论 0
任何时候，假如满足 $i=j$，在接下来的过程中保持 $i=j$ 一定不劣。

#### 结论 1

假如存在一种方案，使得在进行第一次操作三时，操作串不是给定的 $S_{i \cdots j}$ 的子串，且优于一切不是这样的方案，那么这个方案一定不优于先使 $i=j$，然后再进行操作。

#### 证明 1

注意到，在这种方案中，你一定在第一次操作三之前使用了 $i-1$ 或者 $j+1$。

假如你使用了上述操作，并且在第一次操作三时的 $i,j$ 与给定的 $i,j$ 有交，那么你把上述操作移动到这次操作三之后同样合法，可以变为不是这样的方案。

因为这样进行操作三时的操作串是原来的操作串的子串，因此这个操作三也合法，然后位置的差别可以通过在之后进行同样的操作来修正。

假如操作串与输入的 $S_{i \cdots j}$ 没有交，但多于一个字符，撤销掉若干个上述操作一定可以让它变成一个字符，然后把撤销掉的这些操作移动到最后一定也合法。

这个结论可以归纳地推广到任意一次操作三。

---

至此，我们可以先处理两种情况：不使用操作三，以及先通过某些操作使得 $i=j$ 然后保持这样。

不使用操作三时，答案为 $|i-k|$。

考虑单字符的情况：记 $dis_{i,j}$ 表示从 $j$ 到任意一个 $x$ 使得 $S_x = i$ 的最小代价。考虑如何计算，枚举字符 $i$ ，然后将所有字符为 $i$ 的位置加入队列，进行多源 bfs 即可。暴力实现会建出 $O(n^2)$ 条边，可以使用一个优化建图技巧：对每个字符建一个虚点，每个位置向对应字符连 $1$ 边，字符向位置连 $0$ 边，跑 01-bfs。也有等价的不需要显式地优化建图的方法。

然后，枚举第一次操作三时的字符 $c$。第一种情况是，$c$ 在 $S_{i \cdots j}$ 中出现过，可以用 $j-i+dis_{c,k}+1$ 更新答案。

第二种情况是 $c$ 没有出现过，此时用 $j-i+ \min(dis_{c,i},dis_{c,j})+dis_{c,k}+1$ 更新答案。

---

在后面，我们只考虑，进行操作三时的操作串是 $S_{i \cdots j}$ 的子串的情况。其他情况已经处理过了。

### 结论 2

一定存在一种最优解的方案是，先进行若干次操作一和操作二，然后进行一次操作三，然后再进行若干次操作一。

简要说明一下：考虑假如你在两次操作三之间进行了一次其他操作，将这个操作移到所有操作三的前面也是合法的。

这样的话，所有操作三是连续的一段，显然可以只进行一次。

因此：这种情况是，先收缩成一段，然后进行一次操作三，然后归位。

---

我们考虑操作三之后 $i$ 与 $k$ 的位置关系。

第一种情况是 $i<k$。发现这样一定不优于让 $i=k$。

因为，这样操作之后需要进行若干次操作使 $i+1$，而如果将这些操作放在操作三之前完成，也是合法的。

第二种情况是 $i \geq k$。

把答案写出来，然后去掉常数，发现我们要做的其实是，对于所有在 $k$ 之后出现过的 $[L,R]$ ，满足 $S_{L \cdots R}$ 在 $S_{i \cdots j}$ 中出现过，最小化 $2L-R$。

### 暴力1

固定 $L$ 时，显然 $R$ 应该尽量大。考虑枚举 $L$，就是求最大的 $R$ 使得 $S_{L \cdots R}$ 在 $S_{i \cdots j}$ 中出现过。这个有很多种 SAM，SA，后缀树的处理方式，下面给出一种。

二分 $R$，即判断 $S_{L \cdots R}$ 是否存在于 $S_{i \cdots j}$ 中。对 $S$ 建后缀树，倍增定位出 $S_{L \cdots R}$，然后求对应节点的子树中是否存在在 $[i+R-L,j]$ 中的后缀即可。这一步可以可持久化线段树合并。

算上枚举 $L$，总复杂度 $O(nq\log^2n)$。然而标算使用的是略为复杂的 $O(nq\log n)$ 的离线 LCT 做法。

### 暴力2

固定长度，则 $L$ 应尽量小。

首先考虑 $k$ 固定的情况，发现求出的 $j$ 是两个后缀的 LCP，也就是说，$S_{i \cdots j}$ 是后缀树上一个节点，是 SAM 上的一个等价类。

对每个点维护子树中的所有在 $k$ 之后最左的后缀。我们在后缀树上 dp，设 $f_i$ 为节点 $i$ 代表的子串的所有子串的 $2L-R$ 的最小值，$g_i$ 表示节点 $i$ 的子树中的 $k$ 之后的最左的后缀的位置，$len_i$ 表示节点 $i$ 代表的串的长度。

有 $f_i = \min(f_{fa_i},f_{link_i},g_i - len_i -1)$ ，其中 $fa_i$ 表示节点 $i$ 的父节点，$link_i$ 表示节点 $i$ 的后缀链接指向的节点。在后缀树上倍增定位出 $S_{i \cdots j}$ 查询 dp 值即可。

注意到这样只能找到一个等价类内最长串的答案，易知这不劣。

对每个 $k$ 做一次的复杂度为 $O(n)$。直接做复杂度为 复杂度 $O(nq)$。

### 不暴力了

相信各位经验丰富的选手看到这里时，正解已经呼之欲出了。

考虑用上述两个暴力来摊平查询的复杂度。考虑按 $k$ 从后往前扫，每隔 $B$ 个位置重新 dp 一次，然后对于到上一次重构中间的小块部分用第一个暴力处理。

根据第一个暴力的复杂度，取适当的 $B$ 可以得到 $O(n\sqrt{n \log n}) \sim O(n\sqrt n \log n)$ 的做法。可以通过所有测试点。

std 写的是 $O(n\sqrt{n \log n} + n \Sigma)$ 的做法。

---

下面是 std，需要可以自取

```cpp
#include <bits/stdc++.h>
#define maxn 30005
const int B=40;
const int inf=1e8;
int n,q,ch[maxn<<1][2],anc[maxn<<1][17]={0},
depth[maxn<<1]={0},rank[maxn],tail=0,rk[maxn<<1],dp[maxn<<1],min[maxn<<1],tl,
ans[maxn],d[maxn<<1],vis[30],dis[27][maxn],pre[maxn<<1],fa[maxn<<1],max[maxn<<1],tag[maxn<<1],
cnt[26][maxn];
std::vector<int>rc[27];
char s[maxn];
struct Q{int i,j,p,id;}qr[maxn];
int cmp1(Q a,Q b){return a.p>b.p;}
int cmp(int a,int b){
	if (depth[a]!=depth[b])return depth[a]<depth[b];
	return d[a]<d[b];
}struct Q2{
	int l,r,p,id,k;
}q1[maxn*B];
int cmp2(Q2 a,Q2 b){return a.l>b.l;}
void cover(int x,int y){tag[x]=std::min(tag[x],y);max[x]=std::min(max[x],y);}
void pushdown(int x){
	if(ch[x][0])cover(ch[x][0],tag[x]);
	if(ch[x][1])cover(ch[x][1],tag[x]);
	tag[x]=inf;
}
int not_root(int x) {return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void rotate(int x) {
    int f=fa[x],g=fa[f],l=ch[f][1]==x,c=ch[x][l^1];
    if (not_root(f)) ch[g][ch[g][1]==f]=x;
    ch[x][l^1]=f;ch[f][l]=c;
    if (c) fa[c]=f;
    fa[f]=x;fa[x]=g;
}
void spaly(int x) {
	std::stack<int>stk;
	int u=x;stk.push(u);while(not_root(u)){stk.push(fa[u]);u=fa[u];}
	while(!stk.empty()){pushdown(stk.top());stk.pop();}
    while(not_root(x)){
    	rotate(x); 
		if (not_root(fa[x])&&not_root(x))
			rotate((ch[fa[x]][1]==x)!=(ch[fa[fa[x]]][1]==fa[x])?fa[x]:x);
    }
}
struct suffixTree {
	int link[maxn<<1],len[maxn<<1],start[maxn<<1],s[maxn<<1],tail,n,rem,now,ch[maxn<<1][27];
	suffixTree ():tail(1),n(0),rem(0),now(1) {len[0]=inf;}
	int newnode(int st,int le){
		link[++tail]=1;start[tail]=st;len[tail]=le;return tail;
	}
	void extend(int x){
		s[++n]=x;rem++;
		for (int last=1;rem;){
			while (rem>len[ch[now][s[n-rem+1]]]) rem-=len[now=ch[now][s[n-rem+1]]];
			int &v=ch[now][s[n-rem+1]];int c=s[start[v]+rem-1];
			if (!v||x==c){
				link[last]=now;last=now;
				if (!v) v=newnode(n-rem+1,inf);
				else break;
			}else{
				int u=newnode(start[v],rem-1);
				ch[u][c]=v;ch[u][x]=newnode(n,inf);
				start[v]+=rem-1;len[v]-=rem-1;
				link[last]=v=u;last=u;
			} if (now==1) rem--;else now=link[now];
		}
	}
}sft;

void dfs(int u,int f){
	anc[u][0]=f;
	for (int i=1;i<=15;++i)anc[u][i]=anc[anc[u][i-1]][i-1];
	int len=std::min(sft.len[u],n-sft.start[u]+1),isleaf=1;
	pre[u]=fa[u]=f;max[u]=tag[u]=inf;
	depth[u]=depth[f]+len;d[u]=d[f]+1;
	for (int i=0;i<=26;++i)
		if (sft.ch[u][i])dfs(sft.ch[u][i],u),isleaf=0;
	if (isleaf)
		rank[n-depth[u]+1]=u;
	rk[++tl]=u;
}

void access(int x,int w) {
	for (int y=0;x;x=fa[y=x])spaly(x),ch[x][1]=y,cover(x,w);
}

int query(int x,int r){
	if(!x)return 0;
	pushdown(x);
	if(max[x]<r-depth[pre[x]]+1){
		int d=query(ch[x][1],r);
		if(d)return d;else return std::min(depth[x],r-max[x]+1);
	}return query(ch[x][0],r);
}

int find(int x,int r){
	for(int y=0;x!=1&&x;x=fa[y=x]){
		spaly(x);ch[x][1]=0;
		int u=x;while(ch[u][0]){pushdown(u);u=ch[u][0];}
		if(max[u]<r-depth[pre[u]]+1)
			return query(x,r);
		ch[x][1]=y;
	}return 0;
}

void rebuild(int l){
	std::memset(dp,63,sizeof(dp));
	for(int i=l;i<=n;++i)min[rank[i]]=i;
	for(int i=tl;i>=1;i--)min[anc[rk[i]][0]]=std::min(min[rk[i]],min[anc[rk[i]][0]]);
	for(int j=2;j<=tl;++j){
		int i=rk[j];
		dp[i]=min[i]-depth[i]+1;
		dp[i]=std::min(dp[i],std::min(dp[anc[i][0]],sft.link[i]!=1?dp[sft.link[i]]:inf));
	}
} 
int locate(int l,int r){
	int u=rank[l];
	for (int i=15;i>=0;i--)
		if (depth[anc[u][i]]>=(r-l+1))u=anc[u][i];
	return u;
}int lca(int u,int v){
	if (d[u]<d[v])std::swap(u,v);
	for(int i=15;i>=0;i--)if(d[anc[u][i]]>=d[v])u=anc[u][i];
	if (u==v)return u;
	for(int i=15;i>=0;i--)if(anc[u][i]!=anc[v][i])u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}	
void bfs(int c){
	std::queue<int>q;
	std::memset(vis,0,sizeof(vis));
	std::memset(dis[c],63,sizeof(dis[c]));
	for(int v:rc[c]){q.push(v);dis[c][v]=0;}
	vis[c]=1;
	while(!q.empty()){
		int x=q.front();int d=s[x]-'a';q.pop();
		if(!vis[d]){
			vis[d]=1;
			for(int v:rc[d])
				if(dis[c][v]>n){dis[c][v]=dis[c][x]+1;q.push(v);}
		}if (x>1&&dis[c][x-1]>n){dis[c][x-1]=dis[c][x]+1;q.push(x-1);}
		if(x<n&&dis[c][x+1]>n){dis[c][x+1]=dis[c][x]+1;q.push(x+1);}
	}
}
void prework(){
	std::memset(min,63,sizeof(min));
	sft.link[1]=1;dfs(1,0);std::sort(rk+1,rk+tl+1,cmp);
	for(int i=1;i<n;++i)sft.link[rank[i]]=rank[i+1];
	for(int i=1;i<=n;++i)rc[s[i]-'a'].push_back(i);
	for(int i=0;i<26;++i)bfs(i);
}
int corner_cases(int i,int j,int p){
	int ans=abs(i-p);
	for(int c=0;c<26;++c){
		ans=std::min(ans,j-i+dis[c][i]+dis[c][p]+1);
		ans=std::min(ans,j-i+dis[c][j]+dis[c][p]+1);
		if(cnt[c][j]-cnt[c][i-1])ans=std::min(ans,j-i+dis[c][p]+1);
	}return ans;
}
int main(){
	scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	for (int i=1;i<=n;++i){
		sft.extend(s[i]-'a');
		for(int c=0;c<26;++c)cnt[c][i]=cnt[c][i-1];
		cnt[s[i]-'a'][i]++;
	}
	sft.extend(26);prework();
	for(int i=1;i<=q;++i){
		scanf("%d%d%d",&qr[i].i,&qr[i].j,&qr[i].p);qr[i].id=i;
		int len=depth[lca(rank[qr[i].i],rank[qr[i].j])];
		qr[i].j=qr[i].i+len-1;
	}std::sort(qr+1,qr+q+1,cmp1);
	int cnt=0,last=n,p=0;
	rebuild(n);
	for(int i=n;i>=1;--i){
		cnt++;
		if (cnt>B){rebuild(i);last=i;cnt=0;}
		while(p<q&&qr[p+1].p==i){
			++p;
			ans[qr[p].id]=
			std::min(qr[p].j-qr[p].i+1+dp[locate(qr[p].i,qr[p].j)]-qr[p].p,
			corner_cases(qr[p].i,qr[p].j,qr[p].p));
			for(int j=i;j<last;++j){
				q1[++tail].l=qr[p].i;q1[tail].r=qr[p].j;q1[tail].p=j;
				q1[tail].id=qr[p].id;
				q1[tail].k=j-i+qr[p].j-qr[p].i+2;
			}
		}
	}std::sort(q1+1,q1+tail+1,cmp2);
	p=0;
	for(int i=n;i>=1;--i){
		access(rank[i],i);
		while(p<tail&&q1[p+1].l==i){
            ++p;int d=find(rank[q1[p].p],q1[p].r);
			if(d)ans[q1[p].id]=std::min(ans[q1[p].id],q1[p].k-d);
        }
	}
	for(int i=1;i<=q;++i)ans[qr[i].id]+=n-qr[i].j; 
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```





---

## 作者：Soulist (赞：10)

为了纪念我逝去的一上午 & 一晚上当然要水题解啦～

~~EA 鸽鸽的神仙题，下面的题解基本上抄自官方题解。~~

设 $r$ 为题设中满足条件的最大的 $r$，首先 $j$ 必然取 $r$ 处，这是因为取 $j'$ 处那么存在一个方案为从 $r$ 不断操作 $2$ 得到 $(i,j')$，容易发现两者代价相同。其次，我们知道答案的下界为 $L-j+|k-i|$

我们称操作 $3$ 为传送，那么可以证明：

- 性质 $1$ ：若当前有 $i=j$，那么我们会保持 $i=j$

注意到 $i=j$ 时操作 $3$ 的限制最松，其次，我们发现使得 $i\ne j$ 的操作可以被使得 $i=j$ 的操作替换掉（请注意我们时刻保持 $i\le j$）

- 性质 $2$ ：若当前有 $|i-j|=t$，那么我们不会扩大 $|i-j|$ 后进行传送。

注意到扩大后传送一定不会优于先传送后扩大（请注意字符串相等意味着子串也相同）

- 性质 $3$ ：最优解法有两种：一是先操作成 $i=j$ 的情况，然后不断的通过操作 $1/2$ 加部分传送到达终点；另一种是先操作成 $l\le i<j\le r$，然后通过一次传送到达某个点，然后直接移动 $i$ 走到 $x$

我们先证明：

1. 若某个操作方案中途使得 $i=j$，那么这个操作方案可以替换为初始通过操作使得 $i=j$ 然后再执行本方案。

设 $t=i-j$，那么使得 $i=j$ 等价于通过操作走完了 $t$ 的长度，我们将这 $t$ 步放在开头做对于答案没有影响。

所以如果操作方案中出现了 $i=j$ 的情况，那么等价于性质 $3$ 中的第一类最优解。

2. 若某个操作方案始终没有使得 $i=j$，那么其至多传送一次。

根据性质 $2$，最优解法一定不会扩大 $|i-j|$，所以长度只能缩小无法增大。

现在考虑当前的 $(i,j)$，假设先移动后再次进行传送，那么假设当前走到了 $(i',j')$ 且 $|i'-j'|>1$ 然后进行传送，我们可以证明这类情况不会发生。

先假设有 $i'>j$，那么我们肯定可以通过更少的操作次数（即只操作 $i$ ）得到 $(j',j')$ 这个二元组，容易发现这样更优，同时违背了前提，会被归类到 1 中。对于 $j'<i$ 类似。

然后我们假设 $i'<j<j'$，那么容易注意到这样的传送等价于先操作成 $(i',j)$ 然后传送后再移动，容易发现等价。

于是我们假设 $i<i'<j'<j$，那么这意味着传送的前提是不断的缩小初始字符区间的，从最初的字符集开始我们得到某个 $(i',j')$ 并传送，那么此后肯定有字符串仍然是最初的字符串的子串，如果此后还进行传送，那么我们不如在初始状态缩小到足够小再传送，这样可以节约传送次数。

那么这样也至多传送一次，至此，如果中途出现了 $i=j$ 那么性质 $3$ 的第一部分即为最优解，否则性质 $3$ 的第二部分为最优解。

---

### 求解

现在考虑对于两部分分别求解。

对于第一部分，问题等价于选择初始 $[i,j]$ 中一个位置 $t$，然后询问 $t\to k$ 的最短路。其他的贡献为常数。

我们发现问题等价于：$t$ 可以左移，右移，每个位置有颜色，颜色相同可传送。

那么统计 $f_{i,j}$ 表示颜色 $i$ 走到位置 $j$ 的最短路即可，可以通过 01 - BFS 在 $\mathcal O(\Sigma \cdot n)$ 的复杂度求解。

对于转移我们枚举这个**第一次经过**“传送”的颜色，假定最优解中途经过了颜色 $c$，那么考虑 $(j-i)+f_{c,x}[x\in [i,j]]+f_{c,k}+1$ 即为答案。

假定 $c$ 在 $[i,j]$ 中出现过，那么答案为 $f_{c,x}[x\in [i,j]]=1$，否则答案取 $\min(f_{c,i},f_{c,j})$ 即可


----

对于第二部分，问题等价于对于 $(i,j)$ 选择一个字串传送到一个 $[i',j']$ 然后从 $i'$ 走到 $x$ 并统计答案。

忽略掉常数，此时的代价为 $2i'-j'$

- 观察：$i'\ge k$

易知，我们需要使得 $j'\ge k$，否则等同于第一部分的情况，所以使得 $i'=k$ 一定不劣。

我们有两类思路：

- 枚举 $i'$，则 $j'$ 应尽可能大。

我们可以二分 $j'$ 并考虑判断 $[i',j']$ 是否在 $[i,j]$ 中出现过。

建立串 $S$ 的后缀树，通过线段树合并维护 endpos 集，我们只需要定位 $[i',j']$ 对应的节点，只需要判定 endpos 中是否存在区间 $[i,j-(j'-i')]$ 内的数即可。

对于单个 $i'$ 进行确定的复杂度为 $\mathcal O(\log^2 n)$

- 当区间长度被确定时，$i'$ 应尽可能小。

此时答案可以被描述为 $i'-\textrm{len}+1$

建立原串 $S$ 的后缀树，考虑树上每个节点，我们应该有此节点对应的字符串固定，此时我们希望求解其所有字串对应的最小的 $2L-R$

为此我们维护每个节点，对应的最小的 $i'$ 即可（可以考虑相同的边对应的 endpos 集是相同的）

我们考虑所有大于 $k$ 的位置对应的字符串，我们希望维护仅考虑这些字符串，后缀树上每个字串对应的答案

我们先维护出节点 $u$ 上对应的在 $k$ 之后最小的 $i'$，然后在后缀树上根据节点深度进行 dp，考虑 $f_i=\min(f_{\textrm{father}_i},f_{\textrm{link}_i},i'-\textrm{len}_i+1)$

此时我们可以 $\mathcal O(n)$ 确定后缀树上每个节点对应的答案。

最后，我们使用两类算法来均摊复杂度以通过此题，离线所有查询，考虑每间隔 $B$ 个位置就重新做一次上述 dp，对于查询的 $k$，设上一次 dp 点为 $L$，我们暴力枚举 $[k,L]$ 中的所有 $i'$ 并采取 $\mathcal O(\log^2 n)$ 的暴力来处理。

于是我们得到了一个 $\mathcal O(\frac{n^2}{B}+nB\log^2 n)$（设 $n,q$ 同阶）的算法。

选取合适的 $B$ 可以做到 $\mathcal O(n\sqrt{n}\log n)$

如果对于第一部分有更高明的解决办法，可以做到 $\mathcal O(n\sqrt{n\log n})$

~~不过我挺好奇为啥理论上 $\log^2$ 的部分怎么跑得这么快。。。$\mathcal O(n)$ 的部分反而常数大一点？...~~


$Code:$

```cpp
const int B = 80 ; 
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ; 
const int H = 2333 ; 
const int N = 6e4 + 50 ; 
const int inf = 1e9 ; 
const int Inf = 1e8 ; 
int n, m, tnt, head[N], vis[N], f[30][N], dis[N] ; 
int bef[30][N], qAns[N] ; 
long long fac[N], pre[N] ; 
struct E {
	int to, next, w ; 
} e[N << 1] ;
void add(int x, int y, int z) { 
	e[++ tnt] = (E){ y, head[x], z }, head[x] = tnt ; 
}
char s[N] ; 
deque<int> q ; 
void BFS(int x) {
	rep( i, 1, n + 30 ) vis[i] = 0, dis[i] = inf ; 
	dis[x] = 0, q.push_back(x) ; int z = x - n ; 
	while(!q.empty()) {
		int u = q.front() ; q.pop_front() ; 
		if(vis[u]) continue ; vis[u] = 1 ; 
		Next( i, u ) {
			int v = e[i].to ; 
			if(dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w ; 
				if(dis[v] == dis[u]) q.push_front(v) ;
				else q.push_back(v) ; 
			}
		}
	} rep( i, 1, n ) f[z][i] = dis[i] ; 
}
int Get(int l, int r) { return (pre[r] - 1ll * pre[l - 1] * fac[r - l + 1] % P + P) % P ; }
struct node {
	int l, r, id, cost, bef, wi, ans ; 
} ; vector<node> p[N] ;  
namespace S1 {
	struct Suffix {
		int ch[30] ;
		int lef, lk, len ; 
	} t[N << 1] ; 
	struct Tr {	int l, r, w ; } tr[N * 100] ;
	vector<int> Go[N << 1] ; 
	int rem, bef = 1, cnt = 1, m, num, rt[N] ; 
	int fa[N][20], dep[N], Idnex[N] ; 
	int node( int l, int len ) {
		t[++ cnt].lef = l, t[cnt].len = len, t[cnt].lk = 1 ;
		return cnt ; 
	}
	void insert( int x ) {
		++ m, ++ rem ; int u = s[x], lst = 1 ; 
		while( rem ) {
			while( rem > t[t[bef].ch[(int)s[m - rem + 1]]].len ) 
			rem -= t[bef = t[bef].ch[(int)s[m - rem + 1]]].len ;
			int &d = t[bef].ch[(int)s[m - rem + 1]], c = s[t[d].lef + rem - 1] ;
			if( !d || u == c ) {
				t[lst].lk = bef, lst = bef ; 
				if( !d ) d = node( m - rem + 1, inf ) ;
				else break ;
			}
			else {
				int np = node( t[d].lef, rem - 1 ) ;
				t[np].ch[c] = d, t[np].ch[u] = node(m, inf) ;
				t[d].lef += (rem - 1), t[d].len -= (rem - 1) ;
				t[lst].lk = d = np, lst = np ;
			} (bef == 1) ? -- rem : bef = t[bef].lk ;
		}
	}
	void insert(int &x, int l, int r, int k) {
		if(!x) x = ++ num ; 
		if(l == r) return ++ tr[x].w, void() ; 
		int mid = (l + r) >> 1 ;
		if(k <= mid) insert(ls(x), l, mid, k) ;
		else insert(rs(x), mid + 1, r, k) ; 
		tr[x].w = tr[ls(x)].w + tr[rs(x)].w ; 
	}
	int Kth(int x, int l, int r, int k) {
		if(!x || !k) return 0 ; 
		if(l == r) return tr[x].w ;  
		int mid = (l + r) >> 1 ; 
		if(k <= mid) return Kth(ls(x), l, mid, k) ;
		else return Kth(rs(x), mid + 1, r, k) + tr[ls(x)].w ; 
	}
	int qry(int x, int l, int r, int k) {
		if(l == r) return l ; 
		int mid = (l + r) >> 1 ; 
		if(k <= tr[ls(x)].w) return qry(ls(x), l, mid, k) ;
		else return qry(rs(x), mid + 1, r, k - tr[ls(x)].w) ; 
	}
	int merge(int x, int u, int isr) {
		int nw = (isr) ? x : ++ num ; 
		if(ls(x) && ls(u)) ls(nw) = merge(ls(x), ls(u), 0) ; 
		else ls(nw) = ls(x) + ls(u) ; 
		if(rs(x) && rs(u)) rs(nw) = merge(rs(x), rs(u), 0) ; 
		else rs(nw) = rs(x) + rs(u) ; 
		tr[nw].w = tr[ls(nw)].w + tr[rs(nw)].w ; 
		return nw ; 
	} 
	void dfs( int x, int Fa, int l ) {
		if( t[x].len >= Inf ) t[x].len = n + 1 - t[x].lef ; 
		dep[x] = l + t[x].len, fa[x][0] = Fa ; int fl = 0 ; 
		rep( i, 1, 18 ) fa[x][i] = fa[fa[x][i - 1]][i - 1] ; 
		rep( i, 1, 27 ) if( t[x].ch[i] ) 
		dfs( t[x].ch[i], x, l + t[x].len ), fl = 1, 
		Go[x].pb(t[x].ch[i]), merge(rt[x], rt[t[x].ch[i]], 1) ; 
		if( !fl ) {
			int d = n - dep[x] + 1 ; 
			if(d <= n) Idnex[d] = x, insert(rt[x], 1, n, d) ; 
		} 
	} 
	int Get(int l, int r) {
		int u = Idnex[l], le = r - l + 1 ; 
		drep( i, 0, 17 ) if(dep[fa[u][i]] >= le) u = fa[u][i] ;
		return u ; 
	}
	int Id[N], g[N], F[N], D[N] ; 
	bool cmp(int x, int y) { return dep[x] < dep[y] ; }
	void Dfs(int x) {
		for(int v : Go[x]) 
		Dfs(v), g[x] = min(g[x], g[v]) ; 
	}
	void build(int p) {
		rep( i, 1, cnt ) D[i] = F[i] = g[i] = inf ; 
		rep( i, p, n ) g[Idnex[i]] = i ; 
		Dfs(1), D[0] = F[0] = inf ; int u ;
		rep( i, 3, cnt ) 
			u = Id[i], 
			F[u] = min(D[t[u].lk], D[fa[u][0]]),
			D[u] = min(F[u], g[u] - dep[u] + 1) ; 
	}
	bool check(int l1, int r1, int l2, int r2) {
		if(r1 - l1 > r2 - l2) return 0 ; 
		int len = r1 - l1, ed = r2 - len, u = Get(l1, r1) ; 
		int l = Kth(rt[u], 1, n, l2 - 1), sz = tr[rt[u]].w ; 
		if(l == sz) return 0 ; 
		return (qry(rt[u], 1, n, l + 1) <= ed) ; 
	}
	int Get(int p, int L, int R) {
		int l = p, r = n, ans = inf ; 
		while(l <= r) {
			int mid = (l + r) >> 1 ; 
			if(check(p, mid, L, R)) ans = min(ans, 2 * p - mid), l = mid + 1 ;
			else r = mid - 1 ; 
		} return ans ; 
	}
	void solve() {
		s[++ n] = 27, t[0].len = inf ; 
		rep( i, 1, n ) insert(i) ; -- n ;
		rep( i, 1, cnt ) rt[i] = ++ num ; 
		dfs(1, 1, 0) ; rep( i, 1, cnt ) Id[i] = i ; 
		rep( i, 1, n ) t[Idnex[i]].lk = Idnex[i + 1] ; 
		sort(Id + 1, Id + cnt + 1, cmp) ; 
		int last = n ; build(n) ; 
		for(re int i = n; i >= 1; -- i) {
			if(i % B == 0) last = i, build(i) ; 
			for(auto &v : p[i]) {
				int u = Get(v.l, v.r), len = v.r - v.l + 1 ; 
				v.ans = min(v.ans, min(F[u], g[u] - len + 1)) ; 
			} 
			for(re int j = i; j <= last; ++ j) 
			for(auto &v : p[i]) v.ans = min(v.ans, Get(j, v.l, v.r)) ; 
		}
		rep( i, 1, n ) for(auto &v : p[i]) 
		v.ans += v.wi, qAns[v.id] = v.cost + min(v.ans, v.bef) ; 
	}
}
signed main()
{
	n = gi(), m = gi(), scanf("%s", s + 1) ; 
	rep( i, 1, n ) s[i] -= ('a' - 1), add(i, s[i] + n, 1), add(s[i] + n, i, 0) ; 
	rep( i, 1, n - 1 ) add(i, i + 1, 1), add(i + 1, i, 1) ; 
	rep( i, 1, 26 ) BFS(i + n) ; fac[0] = 1 ; 
	rep( i, 1, n ) pre[i] = (1ll * pre[i - 1] * H + s[i]) % P ; 
	rep( i, 1, n ) fac[i] = 1ll * fac[i - 1] * H % P ; 
	rep( i, 1, n ) {
		rep( j, 1, 26 ) bef[j][i] = bef[j][i - 1] ; 
		++ bef[(int)s[i]][i] ; 
	}
	rep( j, 1, m ) {
		int x = gi(), y = gi(), k = gi() ; 
		int len = n - max(x, y) ; 
		int l = 0, r = len, ans = 0 ; 
		while(l <= r) {
			int mid = (l + r) >> 1 ;
			if(Get(x, x + mid) == Get(y, y + mid)) ans = mid, l = mid + 1 ;
			else r = mid - 1 ; 
		}
		int L = x, R = x + ans, Ans = abs(L - k) ; 
		rep( i, 1, 26 ) 
			if(bef[i][R] - bef[i][L - 1]) Ans = min(Ans, R - L + f[i][k] + 1) ; 
			else Ans = min(Ans, R - L + min(f[i][L], f[i][R]) + f[i][k] + 1) ; 
		p[k].pb((node){ L, R, j, n - R, Ans, R - L - k + 1, inf }) ; 
	}
	S1::solve() ; 
	rep( i, 1, m ) printf("%d\n", qAns[i] ) ; 
	return 0 ;
}
```

---

