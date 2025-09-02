# Narrow Components

## 题目描述

You are given a matrix $ a $ , consisting of $ 3 $ rows and $ n $ columns. Each cell of the matrix is either free or taken.

A free cell $ y $ is reachable from a free cell $ x $ if at least one of these conditions hold:

- $ x $ and $ y $ share a side;
- there exists a free cell $ z $ such that $ z $ is reachable from $ x $ and $ y $ is reachable from $ z $ .

A connected component is a set of free cells of the matrix such that all cells in it are reachable from one another, but adding any other free cell to the set violates this rule.

You are asked $ q $ queries about the matrix. Each query is the following:

- $ l $ $ r $ — count the number of connected components of the matrix, consisting of columns from $ l $ to $ r $ of the matrix $ a $ , inclusive.

Print the answers to all queries.

## 样例 #1

### 输入

```
12
100101011101
110110010110
010001011101
8
1 12
1 1
1 2
9 9
8 11
9 12
11 12
4 6```

### 输出

```
7
1
1
2
1
3
3
3```

# 题解

## 作者：MC小萌新 (赞：9)

这里提供一种线性复杂度的做法。

首先先求出所有连通块，以及记录一下它的左右边界，然后预处理出 $sl$ 和 $sr$ 数组，分别表示从 $1$ 到 $i$ 和从 $i$ 到 $n$ 中**全部**在该范围内的连通块个数。

同时处理出 $nstl$ 与 $nstr$，分别表示当前列向右和向左第一个不为 ```101``` 组合的列编号。

![1](https://cdn.luogu.com.cn/upload/image_hosting/tspb3hvh.png)

观察一下这个例子，容易发现若不考虑切断后无法连通的块，$ans=$ 总数 $-sr[l-1]-sl[r+1]$。

但当断点列为 ```101```，且第 $1$ 行与第 $3$ 行在同一连通块中时，有可能增加一个块。从断点出发向查询区间内找到第一个不为 ```101``` 的列，只要这个列中有一个 $0$，那么这个块就必然要断开了。所以此时 ```ans++```。

特别的，如果查询区间内的列全部为 ```101```，则答案就为 $2$。

左右断点 $l$ 和 $r$ 都需要判断一遍。

综合复杂度 $O(n+q)$。

```cpp
#include <iostream>
using namespace std;
 
const int N=510000,INF=3*N-1;
int n,q;
char s[5][N];
int l,r;
int ltk[3*N][3];//0:左边界 1 右边界 
int sl[N],sr[N];
int vis[4][N],cnt=1;
int nstl[N],nstr[N];
bool state=0;
 
bool dfs(int x,int y){
	if(x==0 || y==0 || x>3 || y>n || s[x][y]=='0' || vis[x][y])
		return state;
	vis[x][y]=cnt,state=1;
	ltk[cnt][0]=min(ltk[cnt][0],y);
	ltk[cnt][1]=max(ltk[cnt][1],y);
	dfs(x+1,y);
	dfs(x,y+1);
	dfs(x-1,y);
	dfs(x,y-1);
	return state;
}
 
void solve(){
	int ans=cnt-1-sr[l-1]-sl[r+1];
	if(s[1][l]=='1' && s[2][l]=='0' && s[3][l]=='1' && vis[1][l]==vis[3][l]){
		int t=nstl[l];
		if(t>r)
			ans=2;
		else if(s[1][t]=='0' || s[3][t]=='0')
			ans++;
	}
	if(s[1][r]=='1' && s[2][r]=='0' && s[3][r]=='1' && vis[1][r]==vis[3][r]){
		int t=nstr[r];
		if(t>=l && (s[1][t]=='0'|| s[3][t]=='0'))
			ans++;
	}
	cout<<ans<<endl;
}
 
int main(){
	cin>>n;
	for(int i=0;i<=4;++i)
		for(int j=0;j<=n+1;++j)
			s[i][j]='0';
	for(int i=0;i<=3*n+1;++i)
		ltk[i][0]=INF;
	for(int i=1;i<=3;++i)
		for(int j=1;j<=n;++j)
			cin>>s[i][j];
	for(int i=1;i<=n;++i){
		state=0;
		cnt+=dfs(1,i);
		state=0;
		cnt+=dfs(2,i);
		state=0;
		cnt+=dfs(3,i);
	}
	int t=n+1;
	for(int i=n;i>=1;--i){
		if(!(s[1][i]=='1' && s[2][i]=='0' && s[3][i]=='1'))
			t=i;
		nstl[i]=t;
	}
	t=0;
	for(int i=1;i<=n;++i){
		if(!(s[1][i]=='1' && s[2][i]=='0' && s[3][i]=='1'))
			t=i;
		nstr[i]=t;
	}
	for(int i=1;i<cnt;++i){
		sl[ltk[i][0]]++;
		sr[ltk[i][1]]++;
	}
	for(int i=1;i<=n;++i)
		sr[i]+=sr[i-1];
	for(int i=n-1;i>=1;--i)
		sl[i]+=sl[i+1];
	cin>>q;
	while(q--){
		cin>>l>>r;
		solve();
	}
	return 0;
}
```


---

## 作者：optimize_2 (赞：7)

以下内容来自 yzy1：

> 赛时第一眼：这不 SB 题吗？直接莫队，一次加入或者删除一列的贡献只和它左边或者右边的一列有关，所以只需要预处理出 $64$ 中情况，然后莫队就行。
>
>打了个莫队交上去结果 WA on test 1，发现莫队做法中「一列的贡献只和它左边或者右边的一列有关」是假的，考虑这样一种情况：
>
>```
>111
>001
>111
>```
>假设我们询问 $[1,3]$，则莫队右端点扫到 $3$ 的时候，刚才的算法会计算 `101` 和 `111` 结合，新成 $0$ 个连通块。事实上，加入 $4$ 后会把上下两边的连通块合并，对答案贡献为 $−1$。

考虑为什么会有这个问题。

我们充分发扬人类智慧（本文下标均从 $1$ 开始）：

对于一段 $\begin{bmatrix}1\\0\\1\end{bmatrix}$，我们在后面接入 $\begin{bmatrix}1\\1\\1\end{bmatrix}$，统计贡献时，不能确定原来的 $\begin{bmatrix}1\\0\\1\end{bmatrix}$ 上下是否联通。所以开两个数组 $lf$ 和 $rt$，$lf_i$ 表示另第 $i$ 列的 $\begin{bmatrix}1\\0\\1\end{bmatrix}$ 上下联通，需要的 $\begin{bmatrix}
1\\1\\1\end{bmatrix}$ 最靠右的下标，若不存在，$lf_i = 0$。

拿人话讲，就是如果第 $i$ 列是 $\begin{bmatrix}1\\0\\1\end{bmatrix}$，那 $lf_i$ 就是 $i$ 左边最近的 $\begin{bmatrix}1\\1\\1\end{bmatrix}$，且 $lf_i + 1$ 列到 $i$ 列必须都是 $\begin{bmatrix}1\\0\\1\end{bmatrix}$，否则 $lf_i = 0$。

$rt$ 数组同理。

下面给出 $lf$ 与 $rt$ 的求法。

```cpp
lf[0] = 0;
for (register int i = 1; i <= n; i++) {
    if (a[1][i] && a[2][i] && a[3][i]) {
        lf[i] = i;
    } else if (a[1][i] && !a[2][i] && a[3][i]) {
        lf[i] = lf[i - 1];
    } else {
        lf[i] = 0;
    }
}
rt[n + 1] = n + 1;
for (register int i = n; i >= 1; i--) {
    if (a[1][i] && a[2][i] && a[3][i]) {
        rt[i] = i;
    } else if (a[1][i] && !a[2][i] && a[3][i]) {
        rt[i] = rt[i + 1];
    } else {
        rt[i] = n + 1;
    }
}
```

接下来，考虑如何在移动左右指针时更新答案。

通过几个例子来说明。

1. 在 $\vec{v_1} = \begin{bmatrix}1\\1\\0\end{bmatrix}$ 后加一段 $\vec{v_2} \begin{bmatrix}0\\1\\1\end{bmatrix}$，得到 $\begin{bmatrix}1 & 0  \\1 & 1 \\0 & 1 \\\end{bmatrix}$，此时联通块数量不变，对答案无贡献。

2. 在 $\vec{v_1} = \begin{bmatrix}1\\1\\0\end{bmatrix}$ 后加一段 $\vec{v_2} \begin{bmatrix}0\\0\\1\end{bmatrix}$，得到 $\begin{bmatrix}1 & 0  \\1 & 0 \\0 & 1 \\\end{bmatrix}$，此时原有联通块一个，现在有两个，答案加一。

2. 在 $\vec{v_1} = \begin{bmatrix}1\\0\\1\end{bmatrix}$ 后加一段 $\vec{v_2} \begin{bmatrix}0\\1\\1\end{bmatrix}$，得到 $\begin{bmatrix}1 & 0  \\0 & 1 \\1 & 1 \\\end{bmatrix}$，此时原有联通块两个，现在有两个，对答案无贡献。

所以，对于所有 $\vec{v_i}$，处理出它的联通块个数，记为 $con1_i$，同时对于所有矩阵$\begin{bmatrix} \vec{v_i} & \vec{v_{i+1}} \\\end{bmatrix}$，处理出它的联通块个数，记为 $con2_i$。

下面给出 $con1$ 和 $con2$ 的求法。

为了减小常数，使用打表实现。

[代码过长，放在剪贴板里](https://www.luogu.com.cn/paste/7jxrh3ns)

根据数学直觉，在不考虑 $\begin{bmatrix}1 & 1  \\0 & 1 \\1 & 1 \\\end{bmatrix}$ 的情况时，要把 $r$ 加一，答案就增加 $con2_r - con1_r$（$r$ 此时还没增加），若 $\begin{bmatrix} \vec{v_r} & \vec{v_{r+1}} \\\end{bmatrix} = \begin{bmatrix}1 & 1  \\0 & 1 \\1 & 1 \\\end{bmatrix}$，则分类讨论 $lf_r$，若 $lf_r \geq l$，则说明存在一个下标 $lf_r$，有 $\vec{v_i} = \begin{bmatrix}1\\1\\1\end{bmatrix}$，且 $lf_r$ 到 $r$ 都为 $\begin{bmatrix}1\\0\\1\end{bmatrix}$，也就是说 $\vec{r}$ 上下两边已经联通了，此时 $\vec{r + 1}$ 对答案无贡献，否则答案 $- 1$。

下面给出移动指针的代码。

```cpp
void addl() {
    if (f(l, 1, 1, 1, 1, 0, 1) && rt[l + 1] <= r) {
        // do nothing
    } else {
        cnt -= con2[l];
        cnt += con1[l + 1];
    }
    l++;
}

void addr() {
    if (f(r, 1, 0, 1, 1, 1, 1) && lf[r] >= l) {
        // do nothing
    } else {
        cnt -= con1[r];
        cnt += con2[r];
    }
    r++;
}

void minl() {
    if (f(l - 1, 1, 1, 1, 1, 0, 1) && rt[l] <= r) {
        // do nothing
    } else {
        cnt -= con1[l];
        cnt += con2[l - 1];
    }
    l--;
}

void minr() {
    if (f(r - 1, 1, 0, 1, 1, 1, 1) && lf[r - 1] >= l) {
        // do nothing
    } else {
        cnt -= con2[r - 1];
        cnt += con1[r - 1];
    }
    r--;
}
```

剩下的就是莫队的基本操作了。

由于数据范围较大，这里讲一些卡常技巧。

1. 莫队奇偶优化。

```cpp
struct Query {
    int l, r, id, ans;
    bool operator < (const Query &q) const {
        if (belong[l] != belong[q.l]) {
            return belong[l] < belong[q.l];
        } else {
            if (belong[l] & 1) return r < q.r;
            else return r > q.r;
        }
    }
} q[M];
```

2. 使用快速 IO。

3. 在莫队分块时，尽可能少地使用开方与除法。

```cpp
void init() {
    int block = sqrt(n);
    int cnt = 0;
    for (register int i = 1; i <= n; i++) {
        cnt++;
        belong[i] = belong[i - 1];
        if (cnt == block) {
            belong[i]++;
            cnt = 0;
        }
    }
}
```

4. 开火车头。

[最终代码](https://www.luogu.com.cn/paste/3rsq6py6)。

这样速度快得飞起，在 $m = 300000$ 时都以在 1809ms 内卡过。

---

## 作者：XL4453 (赞：4)

### $\text{Difficulty : 2500}$
---
### 解题思路：
考虑每一个联通块的生成树，每有一条边就可以减少一个联通块，如果可以统计出区间内生成树森林的边的数量，再结合用前缀和统计出的点的数量就能快速计算出联通块的数量。这种思路乍一看完全不可行，但由于是 $\text{Educational Round}$，被教育了一种全新的思路捏。

如果优先加入行与行之间有公共边的，然后再加入列与列之间的能够减少联通块的边，就能很好地适应对于整列到整列的查询要求了。

但是这样并不能应对从上往下为 $101$ 的情况，由于这种情况下如果之前已经被连接过，则在后面的可能的链接中就不会被计算。但是同时也可以发现这也是唯一的可能出现的错误，也就是只有最左端出现这样的情况的时候可能会出差错。那就直接对于最左边为 $101$ 的询问分情况讨论一下前面的一长串 $101$ 会额外产生多少联通块就行了。

记录下每一个位置的下一个不是 $101$ 的位置，不妨记为 $next$。那么有具体的情况：

1. $next$ 超过的最右端，也就是整个区间都是 $101$，显然整个区间上只有 $2$ 个联通块。讨论这种情况是因为下一个位置不在区间内并不方便放在下面的三种一般的情况中讨论。
2. $next$ 为 $000$ 或者 $010$，此时产生两个联通块。
3. $next$ 为 $111$，此时前面的 $101$ 完全并入后面，不产生新的联通块。
4. $next$ 为 $110$ 或者 $011$，此时产生一个额外联通块。

总复杂度 $O(n\log n)$，需要使用并查集。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=1500005;
int num[5][MAXN],fa[MAXN],sum[MAXN],H[MAXN],V[MAXN],Q,x,y,NXT[MAXN],nxt,ans,n;
int find(int now){
	if(fa[now]==now)return now;
	return fa[now]=find(fa[now]);
}
bool merge(int x,int y){
	if(find(x)!=find(y)){
		fa[find(x)]=find(y);
		return 1;
	}
	return 0;
}
int NUM(int x,int y){
	return n*(x-1)+y;
}
void READ(){
	scanf("%d",&n);
	for(int i=1;i<=3;i++)
	for(int j=1;j<=n;j++)
	scanf("%1d",&num[i][j]);
}
void INIT(){
	for(int i=1;i<=3*n;i++)fa[i]=i;
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=3;j++)
	sum[i]+=num[j][i];
	for(int i=1;i<=n;i++)
	sum[i]+=sum[i-1];
	
	for(int i=1;i<=2;i++)
	for(int j=1;j<=n;j++)
	if(num[i][j]==1&&num[i+1][j]==1)
	H[j]+=merge(NUM(i,j),NUM(i+1,j));
	for(int i=1;i<=n;i++)
	H[i]+=H[i-1];
	
	for(int i=1;i<=3;i++)
	for(int j=2;j<=n;j++)
	if(num[i][j]==1&&num[i][j-1]==1)
	V[j]+=merge(NUM(i,j),NUM(i,j-1));
	for(int i=1;i<=n;i++)
	V[i]+=V[i-1];
	
	for(int i=n;i>=1;i--){
		if(num[1][i]==1&&num[2][i]==0&&num[3][i]==1)NXT[i]=NXT[i+1]+1;
		else NXT[i]=0;
	}
}
int work(int l,int r){
	nxt=l+NXT[x];
	if(nxt>y)return 2;
	ans=sum[r]-sum[nxt-1]-H[r]+H[nxt-1]-V[r]+V[nxt];
	if(nxt!=l){
		if(num[1][nxt]==1&&num[2][nxt]==1&&num[3][nxt]==1);
		else if(num[1][nxt]==0&&num[3][nxt]==0)ans+=2;
		else ans++;
	}
	return ans;
}
int main(){
	READ();
	INIT();
	scanf("%d",&Q);
	while(Q--){
		scanf("%d%d",&x,&y);
		printf("%d\n",work(x,y));
	}
	return 0;
}
```


---

## 作者：enucai (赞：4)

## Analysis

原题 [CF811E Vladik and Entertaining Flags](https://www.luogu.com.cn/problem/CF811E)。请先阅读 [题解 CF811E 【Vladik and Entertaining Flags】
](https://www.luogu.com.cn/blog/wsyear/solution-cf811e)

两题唯一的不同点是 CF811F 不同颜色的点都有贡献，而此题只有数字 $1$ 有贡献。因此将原题 $val+1$ 的地方全部修改为 $val+a_{i,j}$ 即可。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1661/submission/153385286)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define mid (l+r)/2
int n,m,q,a[4][500010],tot=0,fa[1500010];
struct node{
	int l[4],r[4],val;
}tr[2000010];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
node add(node x,node y,int l,int r){
	node res;res.val=x.val+y.val;
	For(i,1,n) res.l[i]=x.l[i],res.r[i]=y.r[i];
	For(i,1,n) fa[x.l[i]]=x.l[i],fa[x.r[i]]=x.r[i];
	For(i,1,n) fa[y.l[i]]=y.l[i],fa[y.r[i]]=y.r[i];
	For(i,1,n) if(a[i][l]==a[i][r]){
		int fx=find(x.r[i]),fy=find(y.l[i]);
		if(fx!=fy) res.val-=a[i][l],fa[fx]=fy;
	}
	For(i,1,n) res.l[i]=find(res.l[i]),res.r[i]=find(res.r[i]);
	return res;
}
void build(int c,int l,int r){
	if(l==r){
		For(i,1,n){
			if(a[i][l]==a[i-1][l]) tr[c].l[i]=tr[c].r[i]=tr[c].l[i-1];
			else tr[c].l[i]=tr[c].r[i]=++tot,tr[c].val+=a[i][l];
		}
		return;
	}
	build(c*2,l,mid),build(c*2+1,mid+1,r);
	tr[c]=add(tr[c*2],tr[c*2+1],mid,mid+1);
}
node qry(int c,int l,int r,int x,int y){
	if(l==x&&r==y) return tr[c];
	if(y<=mid) return qry(c*2,l,mid,x,y);
	if(x>mid) return qry(c*2+1,mid+1,r,x,y);
	else return add(qry(c*2,l,mid,x,mid),qry(c*2+1,mid+1,r,mid+1,y),mid,mid+1);
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	scanf("%d",&m);n=3;
	For(i,1,n) For(j,1,m) scanf("%1d",&a[i][j]);
	build(1,1,m);
	scanf("%d",&q);
	while(q--){
		int l,r;scanf("%d%d",&l,&r);
		cout<<qry(1,1,m,l,r).val<<'\n';
	}
}
```

---

## 作者：只鹅烧烤二度 (赞：3)

题目大意：给出一个 $3$ 行 $n$ 列的 $0/1$ 矩阵， $q$ 次询问，每次询问求出 $l$ 到 $r$ 列全为1的四联通块的数量。

给出一个分治思路。

首先有一个 $qnα(n)$ 的思路即对于每一个列，用并查集合并。考虑一列一列合并的过程，可以尝试去优化成分治后整体合并的过程。

显然我们可以扫一遍求出从 $mid$ 列合并到任意一个 $i(i<=mid)$ 列的答案为 $ans_i$ 是多少，以及 $mid+1$ 合并到任意一个 $i(i>mid)$ 行的答案 $ans_i$ 是多少。

考虑一个 $l<=mid,r>mid$ 的询问答案相比 $ans_l+ans_r$ 有什么改变，可以发现我们只是省去了合并 $mid$ 列和 $mid+1$ 列的过程，又因为我们的合并只有关合并到 $l$ 时第 $mid$ 列的 $fa$ 有关，我们就可以将每次合并到 $i$ 时 $mid$ 或 $mid+1$ 列所有值的 $fa$ 记录下来，然后模拟一次合并即可，询问总的复杂度是 $qα(n)$ 的。

总的复杂度是分治的复杂度加询问即 $nlogn+qα(n)$

这种做法拓展到$n*m$的矩阵范围复杂度可以做到 $nmlogn+qnα(n)$ ，然后最初的暴力存一下所有答案的值可以做到 $m^2α(n)+q$ 。因此对于 $nm<=1e5$ 的矩阵可以根号分治一下也能求解。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1.6e6+10;
int fa[N],ans[N],f[4][N],n,L[N],R[N];char s[4][N];
struct Q
{
	int x,y,pos;
};vector<Q>g[N];
int id(int x,int y){return (x-1)*n+y;}
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int merge(int u,int v)
{
	u=find(u),v=find(v);
	if(u==v) return 0;
	return fa[u]=v,1;
}
void add(int p,int l,int r,int ll,int rr,int pos)
{
	int mid=l+r>>1;
	if(ll<=mid&&rr>mid||l==r)
	{
		g[p].push_back((Q){ll,rr,pos});
		return;
	}
	if(ll<=mid) add(p<<1,l,mid,ll,rr,pos);
	else add(p<<1|1,mid+1,r,ll,rr,pos);
}
void solve(int p,int l,int r)
{
	if(l==r)
	{
		int sum=0;
		for(int i=1;i<=3;i++)
		{
			if(s[i][l]=='1') sum++;
			if(s[i][l]=='1'&&s[i-1][l]=='1') sum--;
		}
		for(int i=0;i<g[p].size();i++)
			ans[g[p][i].pos]=sum;
		return;
	}
	int mid=l+r>>1;L[mid+1]=R[mid]=0;
	for(int i=mid;i>=l;i--)
	{
		L[i]=L[i+1];
		for(int j=1;j<=3;j++)
			if(s[j][i]=='1')
				L[i]++,fa[id(j,i)]=id(j,i);
		for(int j=1;j<=2;j++)
			if(s[j][i]=='1'&&s[j+1][i]=='1')
				L[i]-=merge(id(j,i),id(j+1,i));
		if(i<mid)
			for(int j=1;j<=3;j++)
				if(s[j][i]=='1'&&s[j][i+1]=='1')
					L[i]-=merge(id(j,i),id(j,i+1));
		for(int j=1;j<=3;j++)
			f[j][i]=find(id(j,mid));
	}
	for(int i=mid+1;i<=r;i++)
	{
		R[i]=R[i-1];
		for(int j=1;j<=3;j++)
			if(s[j][i]=='1')
				R[i]++,fa[id(j,i)]=id(j,i);
		for(int j=1;j<=2;j++)
			if(s[j][i]=='1'&&s[j+1][i]=='1')
				R[i]-=merge(id(j,i),id(j+1,i));
		if(i>mid+1)
			for(int j=1;j<=3;j++)
				if(s[j][i]=='1'&&s[j][i-1]=='1')
					R[i]-=merge(id(j,i),id(j,i-1));
		for(int j=1;j<=3;j++)
			f[j][i]=find(id(j,mid+1));
	}
	for(int i=0;i<g[p].size();i++)
	{
		int u=g[p][i].x,v=g[p][i].y;
		ans[g[p][i].pos]=L[u]+R[v];
		for(int j=1;j<=3;j++) fa[f[j][u]]=f[j][u],fa[f[j][v]]=f[j][v];
		for(int j=1;j<=3;j++)
			if(s[j][mid]=='1'&&s[j][mid+1]=='1')
				ans[g[p][i].pos]-=merge(f[j][u],f[j][v]);
	}
	solve(p<<1,l,mid);
	solve(p<<1|1,mid+1,r);
}
int main()
{
	int q;
	scanf("%d",&n);
	for(int i=1;i<=3;i++)
		scanf("%s",s[i]+1);
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d %d",&l,&r);
		add(1,1,n,l,r,i);
	}
	solve(1,1,n);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
}


---

## 作者：yzy1 (赞：3)

## 题目大意

给出一个 $n(1 \le n \le 5\times 10^5)$ 行 $3$ 列的 $01$ 矩阵，$m(1\le m \le 3\times 10^5)$ 次询问第 $l$ 列到第 $r$ 列的子矩阵中有多少个 $1$ 的连通块。

## 简要做法

赛时第一眼：这不 SB 题吗？直接莫队，一次加入或者删除一列的贡献只和它左边或者右边的一列有关，所以只需要预处理出 $64$ 中情况，然后莫队就行。

打了个莫队交上去结果 WA on test 1，发现莫队做法中「一列的贡献只和它左边或者右边的一列有关」是假的，考虑这样一种情况：

```plain
111
001
111
```

假设我们询问 $[1,3]$，则莫队右端点扫到 $3$ 的时候，刚才的算法会计算 `101` 和 `111` 结合，新成 $0$ 个连通块。事实上，加入 $4$ 后会把上下两边的连通块合并，对答案贡献为 $-1$。

考虑更换做法。看到连通块个数，想到使用并查集维护。看到区间询问，想到线段树维护。

我们可以直接让线段树里的一个节点维护对应列区间的并查集。查询的时候，合并 $O(\log n)$ 个并查集，得到连通块个数后，再将并查集的合并撤销。

发现线段树有 $O(n)$ 个节点，如果给每个节点开一个值域 $O(n)$ 的并查集则空间会爆炸。考虑同一深度的线段树节点对应的区间互相没有交集，我们可以让这些节点维护的并查集共用一个 `fa` 数组，空间复杂度下降至 $O(n\log n)$。

由于是可撤销并查集，不能有路径压缩，所以需要按秩合并来保证复杂度。

至此，我们以 $O(n\log^2 n)$ 的时间复杂度，$O(n \log n)$ 的空间复杂度解决了这道题目。

[代码参考](https://codeforces.com/contest/1661/submission/153521365)

---

## 作者：panyanppyy (赞：3)

[有点像的经验](https://www.luogu.com.cn/problem/CF811E)
## Problem
给出一个 $n\times3(n\le5\times10^5)$ 的矩阵 $a$，$q\le3\times10^5$ 次询问，每个询问为一个二元组 $l,r$ 求出矩阵 $a[1\sim3][l,r]$ 内数字 $1$ 的联通块个数。
## Solution
看见 $n$ 的范围和询问区间，就可以想到 ds。考虑线段树做法，每次合并用并查集维护即可，时间复杂度 $\mathcal O(q\log n)$。
## 实现
每个节点存区间 $\left[l,r\right]$ 中的最左列和最右列的连通情况（我顺便把 $\left[l,r\right]$ 中的数字情况也记了，方便合并）。

**注意**：连通情况只需要考虑 $1$。

- 建立叶子节点：直接将左右两行都改成这一列内上下方格的连通情况。

- **区间合并**：对于每个区间，显然只有中间部分合并会使连通块的数量减少，那么就只用考虑左儿子的右并查集和右儿子的左并查集就可以了。
	
	如图：（红色为 $1$，蓝色为 $0$）
	![](https://cdn.luogu.com.cn/upload/image_hosting/h1oqzeco.png)
	然后就有人要问了，那中间不是直接比较就可以了吗，为什么要并查集？
    
   别急，看看下面这种情况：
   ![](https://cdn.luogu.com.cn/upload/image_hosting/8zx2yqu1.png)
   这样联通块数量是不是出问题了，右边**可能**$^1$ 可以让左边不连通的联通块重新连通。


> **注意**$^1$：上图存的只有连通块颜色情况，实际情况可能图二中的左儿子中红色本来就是连通的。所以有必要在每个节点存并查集的情况。

------------
还有一些注意点：
1. 可能联通块会从整个区间左边一直连接到右边，所以左右两边的并查集的**保存**建议从 $1\sim6$ 编号而不是两个 $1\sim3$（叶子节点除外）。

2. 同理**合并**时并查集编号应从 $1\sim12$。

[**Code**](https://www.luogu.com.cn/paste/tjswxc39)

---

## 作者：绝顶我为峰 (赞：2)

离线，扫描线扫描右端点，用数据结构维护每个左端点的答案。

每行的八种状态里面，只有一种状态会让连通块数量减少，其他不会减少的情况要么是单点 $+1/+2$，要么是前缀 $+1/+2$，容易维护。

考虑唯一一种连通块数量减少的情况：

```
...1111....
...0001....
...0111....
```

这样我们在扫描线的时候会合并上下两列，连通块数量会减少 $1$。

所以应该前缀 $-1$ 吗？

考虑这种情况：

```
11111
01001
01111
```

扫描到第五列的时候，只有第 $3\sim 5$ 列连通块数量减少了 $1$，因为第一列和第二列在前面就已经连起来了。

所以需要额外记录一个变量 $lst$ 表示当前连通块上一次某一列出现 ```111``` 是什么时候（没有设置成 $0$），扫描到第 $i$ 列合并的时候给 $[lst+1,i-1]$ 这个区间连通块数量 $-1$ 即可。

数据结构操作只有区间修改单点查询，直接使用树状数组。

时间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;
string s;
int n,m,a[500001][3],lst,sum[500001],ans[500001];
vector<pair<int,int> > v[500001];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline int lowbit(int x)
{
    return x&-x;
}
inline void update(int x,int val)
{
    for(;x<=n;x+=lowbit(x))
        sum[x]+=val;
}
inline int query(int x)
{
    int res=0;
    for(;x;x-=lowbit(x))
        res+=sum[x];
    return res;
}
int main()
{
    n=read();
    for(int i=0;i<3;++i)
    {
        cin>>s;
        s=" "+s;
        for(int j=1;j<=n;++j)
            a[j][i]=s[j]-'0';
    }
    m=read();
    for(int i=1;i<=m;++i)
    {
        int l=read(),r=read();
        v[r].emplace_back(l,i);
    }
    for(int i=1;i<=n;++i)
    {
        if(!a[i][0]&&!a[i][1]&&!a[i][2])
            lst=0;
        if(a[i][0]&&!a[i][1]&&!a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][0])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(!a[i][0]&&a[i][1]&&!a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][1])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(!a[i][0]&&!a[i][1]&&a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][2])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(a[i][0]&&a[i][1]&&!a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][0]&&!a[i-1][1])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(a[i][0]&&!a[i][1]&&a[i][2])
        {
            update(i,2);
            update(i+1,-2);
            if(!a[i-1][0])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
            if(!a[i-1][2])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(!a[i][0]&&a[i][1]&&a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][1]&&!a[i-1][2])
            {
                lst=0;
                update(1,1);
                update(i,-1);
            }
        }
        if(a[i][0]&&a[i][1]&&a[i][2])
        {
            update(i,1);
            update(i+1,-1);
            if(!a[i-1][0]&&!a[i-1][1]&&!a[i-1][2])
            {
                update(1,1);
                update(i,-1);
            }
            else if(a[i-1][0]&&!a[i-1][1]&&a[i-1][2])
            {
                update(lst+1,-1);
                update(i,1);
            }
            lst=i;
        }
        for(auto j:v[i])
            ans[j.second]=query(j.first);
    }
    for(int i=1;i<=m;++i)
        cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给定 $3\times n$ 的 $\tt{0/1}$ 网格图，给定 $q$ 个询问 $[l,r]$，查询 $[l,r]$ 部分有几个 $\tt 1$ 组成的联通块。

联通是四联通。

$1\leq n\leq 5\times 10^5$，$1\leq q\leq 3\times 10^5$。

# 题目思路

可以离线的区间询问，尝试普通莫队。

考虑预处理出 $8\times 8$ 的表表示加了新列会增加多少的联通块。

但是这样有问题。

```
1111
1001
1111
```

我们把最后一列的 $\tt 111$ 加入的时候不确定是会减少一个联通块，还是联通块个数不变。

不难发现这只取决于上一个 $\tt 111$ 的位置，满足这个位置到目前位置，中间都是 $\tt 101$ 的形式。

预处理出每个位置往前往后能摸到的第 $1$ 个 $\tt 111$ 在哪里，莫队扩展 / 收缩区间的时候判一下有没有提前用 $\tt 111$ 连接起来了。

这个只和边界两侧是 $\tt 111$ 和 $\tt 101$ 的情况有关，别的情况用上面的表即可。

预处理表可以用并查集维护 $6$ 个点连通性然后状压存下来。

# 完整代码

[CF submission 280804332](https://codeforces.com/contest/1661/submission/280804332)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
struct DSU
{
    int fa[7];
    void init()
    {
        for (int i = 1; i <= 6; i++)
            fa[i] = i;
    }
    int F(int u) { return fa[u] ^ u ? fa[u] = F(fa[u]) : fa[u]; }
    void U(int u, int v) { fa[F(u)] = F(v); }
    int C(int msk)
    {
        int ans = 0;
        for (int i = 1; i <= 6; i++)
        {
            if ((msk >> (6 - i)) & 1)
            {
                if (F(i) == i)
                    ans++;
            }
        }
        return ans;
    }
} D;
int n, Q;
string s[3];
int bel[500020];
int tol[500020];
int tor[500020];
int ans[300020];
int adl[8][8];
int adr[8][8];
int val(int c) { return ((s[0][c] ^ '0') << 2) | ((s[1][c] ^ '0') << 1) | ((s[2][c] ^ '0') << 0); }
int B;
struct query
{
    int l, r, id;
} q[300020];
int main()
{
    read(n);
    B = sqrt(n);
    for (int i = 0; i < 3; i++)
    {
        s[i] += '0';
        for (int j = 1; j <= n; j++)
        {
            char c = ' ';
            while (c != '0' && c != '1')
                c = getchar();
            s[i] += c;
        }
        s[i] += '0';
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            D.init();
            if ((i >> 2 & 1) && (i >> 1 & 1))
                D.U(1, 2);
            if ((i >> 1 & 1) && (i >> 0 & 1))
                D.U(2, 3);
            int t = D.C(i << 3 | 0);
            if ((i >> 2 & 1) && (j >> 2 & 1))
                D.U(1, 4);
            if ((i >> 1 & 1) && (j >> 1 & 1))
                D.U(2, 5);
            if ((i >> 0 & 1) && (j >> 0 & 1))
                D.U(3, 6);
            if ((j >> 2 & 1) && (j >> 1 & 1))
                D.U(4, 5);
            if ((j >> 1 & 1) && (j >> 0 & 1))
                D.U(5, 6);
            adr[i][j] = D.C(i << 3 | j) - t;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            D.init();
            if ((j >> 2 & 1) && (j >> 1 & 1))
                D.U(4, 5);
            if ((j >> 1 & 1) && (j >> 0 & 1))
                D.U(5, 6);
            int t = D.C(0 << 3 | j);
            if ((i >> 2 & 1) && (j >> 2 & 1))
                D.U(1, 4);
            if ((i >> 1 & 1) && (j >> 1 & 1))
                D.U(2, 5);
            if ((i >> 0 & 1) && (j >> 0 & 1))
                D.U(3, 6);
            if ((i >> 2 & 1) && (i >> 1 & 1))
                D.U(1, 2);
            if ((i >> 1 & 1) && (i >> 0 & 1))
                D.U(2, 3);
            adl[i][j] = D.C(i << 3 | j) - t;
        }
    }
    for (int i = 1; i <= n; i++)
        bel[i] = (i + B - 1) / B;
    for (int i = 0; i <= n + 1; i++)
        tol[i] = 0, tor[i] = n + 1;
    for (int i = 0; i <= n; i++)
    {
        if (val(i) == 0b111)
            tol[i] = i;
        if (val(i) == 0b101)
            tol[i] = tol[i - 1];
    }
    for (int i = n + 1; i >= 1; i--)
    {
        if (val(i) == 0b111)
            tor[i] = i;
        if (val(i) == 0b101)
            tor[i] = tor[i + 1];
    }
    read(Q);
    for (int i = 1; i <= Q; i++)
    {
        int l, r;
        read(l, r);
        q[i] = {l, r, i};
    }
    sort(q + 1, q + Q + 1, [&](query a, query b)
         { return bel[a.l] ^ bel[b.l] ? a.l < b.l : bel[a.l] & 1 ? a.r > b.r
                                                                 : a.r < b.r; });
    int l = 1, r = 0, cnt = 0;
    for (int i = 1; i <= Q; i++)
    {
        while (l > q[i].l)
        {
            l--;
            if (val(l) == 0b111 && val(l + 1) == 0b101)
                cnt += tor[l + 1] <= r ? 0 : -1;
            else
                cnt += adl[val(l)][val(l + 1)];
        }
        while (r < q[i].r)
        {
            r++;
            if (val(r) == 0b111 && val(r - 1) == 0b101)
                cnt += tol[r - 1] >= l ? 0 : -1;
            else
                cnt += adr[val(r - 1)][val(r)];
        }
        while (l < q[i].l)
        {
            if (val(l) == 0b111 && val(l + 1) == 0b101)
                cnt -= tor[l + 1] <= r ? 0 : -1;
            else
                cnt -= adl[val(l)][val(l + 1)];
            l++;
        }
        while (r > q[i].r)
        {
            if (val(r) == 0b111 && val(r - 1) == 0b101)
                cnt -= tol[r - 1] >= l ? 0 : -1;
            else
                cnt -= adr[val(r - 1)][val(r)];
            r--;
        }
        ans[q[i].id] = cnt;
    }
    for (int i = 1; i <= Q; i++)
        write(ans[i], '\n');
    return 0;
}
```

---

## 作者：_wfx (赞：1)

我看大家的线段树做法都是线段树加并查集

我给大家带来线段树上区间合并的做法

----

我们考虑合并两个区间

$sum = sum_{ls} + sum_{rs} - max(s - 1 ,0)$

$s$ 是中间合并连通块的数量

易证 $s$ 只有 $0,1,2$ 三种情况

1. $s=0$ 都不连通

2. $s=1$ 左边一个连通块和右边一个连通块连接

3. $s=2$ 多于两个连通块联通

其中 $s=2$ 的情况中左右接触只有三种情况

1. 左右区间共有 $4$ 个连通块

2. 左区间有两个，右区间有一个且同时与左边的两个联通

3. 同上，右区间有两个

所以我们只需要维护每个区间左端点和右端点的 $1$ 的分布情况和连通块数量

其中情况 $2,3$ 还有左区间或右区间上面一排和下面一排全是 $1$ 的情况

这种情况发生时还要将左端点或右端点的连通块数量更新为 $1$

代码如下

```cpp
#include <bits/stdc++.h>
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return x * f;
}

const int N = 5e5 + 100;
const int g[] = {0, 1, 1, 1, 1, 2, 1, 1};
int f[N];

struct node {
	int sum, l, r, lsum, rsum;
	node(int sum = 0, int l = 0, int r = 0, int lsum = 0, int rsum = 0) : sum(sum), l(l), r(r), lsum(lsum), rsum(rsum) {}
	friend node operator + (const node &a, const node &b) {
		node c(a.sum + b.sum, a.l, b.r, a.lsum, b.rsum);
		if (((a.r & b.l) == a.r) && a.rsum == 2) {
			c.sum -= 2;
			if (b.lsum == 1 && a.sum == 2 && a.lsum == 2) c.lsum = 1;
		} else if (((a.r & b.l) == b.l) && b.lsum == 2) {
			c.sum -= 2;
			if (a.rsum == 1 && b.sum == 2 && b.rsum == 2) c.rsum = 1;
		} else if (a.r & b.l) c.sum -= 1;
		return c;
	}
};

struct Tree {
#define mid ((l + r) >> 1)
	node a;
	int l, r;
	Tree *ls, *rs;
	Tree(int l, int r) : l(l), r(r) {
		if (l == r) {
			a = node(g[f[l]], f[l], f[r], g[f[l]], g[f[r]]);
			return;
		}
		ls = new Tree(l, mid);
		rs = new Tree(mid + 1, r);
		a = ls->a + rs->a;
	}
	node ask(int L, int R) {
		if (L == l && r == R) return a;
		if (mid >= R) return ls->ask(L, R);
		if (mid <  L) return rs->ask(L, R);
		return ls->ask(L, mid) + rs->ask(mid + 1, R);
	}
} *rt;

int getc() {
	int c = getchar();
	while (c < '0' || c > '9') c = getchar();
	return c ^ 48;
}

int main() {
	int n = read();
	for (int j = 0; j < 3; ++ j) {
		for (int i = 1; i <= n; ++ i) f[i] = getc() << j;
	}
	rt = new Tree(1, n);
	int q = read();
	for (; q -- > 0; ) {
		int l = read(), r = read();
		printf("%d\n", rt->ask(l, r).sum);
	}
}


```



---

## 作者：daiarineko (赞：0)

## 题意

给一个 $3$ 行 $m$ 列的 $\tt{01}$ 矩阵和 $q$ 次询问，每次询问 $(1, l), (3, r)$ 这个子矩阵里 $\tt 1$ 组成的连通块数。

## 做法

每一列的状态数不多，加上每次都是区间询问，可以考虑线段树维护。

初始状态 $s_i$ 定义为将第 $i$ 列的三个数视为二进制解析的结果，因此 $s_i \in [0, 8)$。

令线段树的每一个节点存储：若经过这个节点内的列之前的状态是 $i$，则经过这个节点后有 $c_{u, i}$ 个连通块“结束”，最后的状态是 $f_{u, i}$。结束的含义是与 $f_{u, i}$ 中的所有 $\tt 1$ 均不连通。

发现有一个特殊的状态是 $7~\tt{(111)}$ 之后的 $5~\tt{(101)}$，此时这两个 $\tt 1$ 是连通的；其余情况下 $1, 2, 3, 4, 6, 7$ 均有一个连通块，$5$ 有两个。将两个 $\tt 1$ 连通的 $5$ 状态单独处理为 $8$。

这里进行一个伏笔回收：上一段里的 $f$ 在这里才有意义（很显然，如果没有分离 $5$ 状态，$f_{u, i} = s_{r_u}$）。

那么接下来考虑如何处理这两个信息。首先，信息是可以合并的：$f_{u, i} = f_{rs, f_{ls, i}}, c_{u, i} = c_{ls, i} + c_{rs, f_{ls, i}}$。考虑叶子节点的信息是什么样的：设它对应位置为 $k$，对于 $f$，$f_{u, i}$ 在大部分情况下等于 $s_k$，**除非上一个状态为 $7$ 或 $8$ 且 $s_k = 5$，此时状态 $5$ 被“同化”为 $8$**。对于 $c$，考虑得到（预处理或打表）每种状态组合 $C_{i, s_k}$ 的数据即可，可见代码。

最后只需要对每个询问的 $l, r$ 查询 $(l, r]$ 的信息合并的结果，再以 $s_l$ 为参数计算即可。需要加上末尾未“结束”的（$0$ 到 $2$ 个）连通块。

## 代码

```cpp
#include <bits/stdc++.h>
using ll = long long;

const int maxn = 500005;
int n, q;
std::string b[3];

// 000, 001, 010, 011, 100, 101, 110, 111, 101*
const int c_f[9] = { 0, 1, 1, 1, 1, 2, 1, 1, 1 };
const int cnt[9][9] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 1, 0, 1, 0, 0 },
  { 1, 1, 0, 0, 1, 1, 0, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 2, 1, 2, 1, 1, 0, 1, 0, 0 },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 0 },
};

int s[maxn];
namespace sgt {
#define ls u << 1
#define rs u << 1 | 1
#define mm int mid = l + r >> 1
  struct Node {
    int f[9], c[9];
    Node() {
      std::iota(f, f + 9, 0);
      std::fill(c, c + 9, 0);
    }
    friend Node operator+ (const Node &a, const Node &b) {
      Node c;
      for (int i = 0; i < 9; ++i) {
        c.f[i] = b.f[a.f[i]];
        c.c[i] = a.c[i] + b.c[a.f[i]];
      }
      return c;
    }
  } t[maxn << 2];
  void pushup(int u) {
    t[u] = t[ls] + t[rs];
  }
  void build(int u, int l, int r) {
    if (l == r) {
      for (int i = 0; i < 9; ++i) {
        if ((i == 7 || i == 8) && s[l] == 5) t[u].f[i] = 8;
        else t[u].f[i] = s[l];
        t[u].c[i] = cnt[i][s[l]];
      }
      return;
    }
    mm;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
  }
  Node query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return t[u];
    }
    mm; Node ans;
    if (L <= mid) ans = query(ls, l, mid, L, R);
    if (mid < R) ans = ans + query(rs, mid + 1, r, L, R);
    return ans;
  }
#undef ls
#undef rs
#undef mm
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 0; i < 3; ++i) {
    cin >> b[i];
    for (int j = 1; j <= n; ++j) {
      s[j] |= (b[i][j - 1] ^ 48) << i;
    }
  }
  for (int i = 1; i <= n; ++i) clog << s[i] << ' ';
  clog << endl;
  sgt::build(1, 1, n);
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    if (l == r) cout << c_f[s[l]] << '\n';
    else {
      auto t = sgt::query(1, 1, n, l + 1, r);
      cout << t.c[s[l]] + c_f[t.f[s[l]]] << '\n';
    }
  }

  cout.flush();
  return 0;
}
```

---

## 作者：KingPowers (赞：0)

不需要任何观察的题，直接硬做就可以。

考虑使用线段树维护区间信息，这里的区间 $[l,r]$ 表示的是第 $l$ 列到第 $r$ 列的信息，接下来的任务就是考虑要维护哪些信息以及如何合并。

显然要维护区间内的答案，也就是白色连通块个数。合并时，我们不能简单地把答案相加，因为可能会有连通块合并。发现每个区间只有左右边界的白色连通块会产生影响，所以可以对于每一行记录左右端点所在的连通块编号，合并时借用并查集处理中间新合并的白色连通块即可。

对于本题，视行数为常数的话，复杂度大概是 $O((n+q)\log n\alpha(n))$。但是实际上这种做法的扩展性极强，可以做到任意多种颜色数量且有单点修改，如果矩阵大小为 $n\times m$ 复杂度就是 $O((nm+q)\log m\alpha(nm))$。


```cpp
#include<bits/stdc++.h>
//#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
const int N = 2e6 + 5;
int n, m, fa[N], col[4][N];
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
struct node{
	int res, l[4], r[4];
}tr[N];
#define ls now << 1
#define rs now << 1 | 1
node merge(const node &a, const node &b, int pos){
	node c; c.res = a.res + b.res;
	For(i, 1, 3){
		fa[a.l[i]] = a.l[i]; fa[a.r[i]] = a.r[i];
		fa[b.l[i]] = b.l[i]; fa[b.r[i]] = b.r[i];
		c.l[i] = a.l[i]; c.r[i] = b.r[i];
	}
	For(i, 1, 3){
		if(col[i][pos] || col[i][pos + 1]) continue;
		int fx = find(a.r[i]), fy = find(b.l[i]);
		if(fx != fy) c.res--, fa[fx] = fy;
	}
	For(i, 1, 3) c.l[i] = find(c.l[i]), c.r[i] = find(c.r[i]);
	return c;
}
void build(int l, int r, int now){
	if(l == r){
		if(col[1][l] == 0) tr[now].res = 1;
		For(i, 2, 3) if(col[i - 1][l] == 1 && col[i][l] == 0) tr[now].res++;
		For(i, 1, 3){
			tr[now].l[i] = tr[now].r[i] = (i - 1) * n + l;
			if(i > 1 && col[i][l] == col[i - 1][l]) tr[now].l[i] = tr[now].r[i] = tr[now].l[i - 1];
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ls); build(mid + 1, r, rs);
	tr[now] = merge(tr[ls], tr[rs], mid);
}
node query(int x, int y, int l, int r, int now){
	if(x <= l && r <= y) return tr[now];
	int mid = (l + r) >> 1;
	if(y <= mid) return query(x, y, l, mid, ls);
	if(x > mid) return query(x, y, mid + 1, r, rs);
	return merge(query(x, y, l, mid, ls), query(x, y, mid + 1, r, rs), mid);
}
#undef ls
#undef rs
void Solve(){
	cin >> n;
	For(i, 1, 3){
		char ch;
		For(j, 1, n) cin >> ch, col[i][j] = ch - '0', col[i][j] ^= 1;
	}
	build(1, n, 1);
	cin >> m;
	while(m--){
		int l, r; cin >> l >> r;
		auto gmx = query(l, r, 1, n, 1);
		cout << gmx.res << '\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

