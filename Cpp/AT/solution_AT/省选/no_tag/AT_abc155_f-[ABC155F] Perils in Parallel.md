# [ABC155F] Perils in Parallel

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc155/tasks/abc155_f

AlDebaran 王国の侵攻によって、AtCoder 王国の各地に爆弾が仕掛けられてしまいました。

幸いにも AtCoder 王国 ABC 隊の健闘により制御装置の一部が手に入ったので、あなたはこれを使って解除を試みることにしました。

仕掛けられた爆弾は $ N $ 個あり、$ 1 $ から $ N $ の番号がついています。爆弾 $ i $ は座標 $ A_i $ にあり、電源は $ B_i=1 $ のときオンに、$ B_i=0 $ のときオフになっています。

制御装置には $ M $ 本のコードがあり、$ 1 $ から $ M $ の番号がついています。コード $ j $ を切ると、座標が $ L_j $ 以上 $ R_j $ 以下の全ての爆弾の電源のオン・オフが切り替わります。

切るコードをうまく選ぶことで全ての爆弾の電源をオフにできるか判定し、できるならばそのようなコードの組合せを $ 1 $ つ出力してください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $
- $ A_i $ は互いに相異なる
- $ B_i $ は $ 0 $ か $ 1 $ のいずれか $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ L_j\ \leq\ R_j\ \leq\ 10^9\ (1\ \leq\ j\ \leq\ M) $

### Sample Explanation 1

座標 $ 5,\ 10 $ に電源がオンの爆弾が、座標 $ 8 $ に電源がオフの爆弾があります。 コード $ 1 $ を切ると座標 $ 1 $ 以上 $ 10 $ 以下にある爆弾、つまり全ての爆弾の電源が切り替わります。 コード $ 4 $ を切ると座標 $ 8 $ 以上 $ 9 $ 以下にある爆弾、つまり爆弾 $ 3 $ のみの電源が切り替わります。 したがって、コード $ 1,\ 4 $ の $ 2 $ 本を切ることで全ての爆弾の電源がオフになります。

### Sample Explanation 2

切るコードをどう選んでも、全ての爆弾の電源をオフにすることは不可能です。

### Sample Explanation 3

はじめから全ての爆弾の電源がオフなので、コードを切る必要はありません。

### Sample Explanation 4

条件を満たすコードの組合せが複数あり得る場合、どれを出力しても構いません。

## 样例 #1

### 输入

```
3 4
5 1
10 1
8 0
1 10
4 5
6 7
8 9```

### 输出

```
2
1 4```

## 样例 #2

### 输入

```
4 2
2 0
3 1
5 1
7 0
1 4
4 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 2
5 0
10 0
8 0
6 9
66 99```

### 输出

```
0```

## 样例 #4

### 输入

```
12 20
536130100 1
150049660 1
79245447 1
132551741 0
89484841 1
328129089 0
623467741 0
248785745 0
421631475 0
498966877 0
43768791 1
112237273 0
21499042 142460201
58176487 384985131
88563042 144788076
120198276 497115965
134867387 563350571
211946499 458996604
233934566 297258009
335674184 555985828
414601661 520203502
101135608 501051309
90972258 300372385
255474956 630621190
436210625 517850028
145652401 192476406
377607297 520655694
244404406 304034433
112237273 359737255
392593015 463983307
150586788 504362212
54772353 83124235```

### 输出

```
5
1 7 8 9 11```

# 题解

## 作者：PNNNN (赞：11)

### 思路：
#### 1.
考虑区间取反，我们第一时间就会想到异或差分
>$diff_i=\begin{cases}
b_i \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ i=1 \\
b_i \oplus b_{i-1} \ \ \ \ i>1
\end{cases}$

易知，$\normalsize{b_i=\oplus_{j=1}^{i} diff_j}$。此时，若要将 $b_{i \in [l,r]}$ 取反，只需 $diff_l \oplus 1,diff_{r+1} \oplus 1$ 即可，我们就可以将区间修改转变为单点修改，更好维护。而最终的目标也从满足 $\forall b_i=0$ 转换为 $\forall diff_i=0$。

#### 2.
考虑要选哪些开关。在这道题中，我们考虑将每个开关的 $l$ 和 $r+1$ 连双向边。此时这些边便形成了若干张无向图，若要选某个开关，则需将此开关所代表边的两个端点 $l$ 和 $r+1$ 的 $diff \oplus =1$。接着在图上进行dfs。考虑递归来处理，若当前点的后继中有 $diff=1$ 的情况，则这条边所代表的开关要被选，要将当前边所代表开关的编号放入答案数组中，并将当前点的 $diff \oplus =1$。若将全部图都dfs了一遍以后，还是存在有某个点的 $diff=1$ 的情况，则说明无解，这只要判断当前图的起始点的 $diff$ 就行了。就像这样：
```
for(int i=1;i<=n;i++){
	if(!vis[i]){
		topu(i);
		if(diff[i]){
			cout<<"-1\n";return 0;
		}
	}
}
```
因为当跑完当前这个图时，除了起始点的 $diff$ 外，其他当前图的点的 $diff$ 已经在dfs的时候全被修改为 $0$ 了。
   
若该图有环该如何处理？知，结果与选开关的顺序无关，且若一个开关选取了多次，根据异或的性质，其实等同于没选或只取了一次，所以只需每次dfs到一个点时给它打上标记，并不往已经被标记的后继dfs。

#### ps:
因为 $l$ 和 $r$ 的值域太大，该题每个开关的 $l$ 和 $r$ 需要离散化成电灯在按 $a_i$ 来排序时的下标。而这样极有可能出现一个开关的 $r+1$ 为 $n+1$，而 $n+1$ 的 $diff$ 无论是 $1$ 还是 $0$ 都不会对答案造成影响。解决方案是单独将 $n+1$ 这个点作为它所在图的起始点跑一遍，并且不判断 $diff_n+1$ 是否为 $1$。

#### 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,diff[100005],vis[100005];

vector <int> ans;

struct line{
	int y,id;
};vector<line> to[100005];

struct node{
	int p,b,id;
	inline bool operator <(const node &A)const{
		return p<A.p;
	}
}a[100005];set<node> st;set<node>::iterator it;

inline void topu(int x){
	vis[x]=1;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i].y,id=to[x][i].id;
		if(vis[y])continue;topu(y);
		if(diff[y])diff[x]^=1,diff[y]=0,ans.push_back(id);
	}return;
}

inline int read(){
	register int x(0),t(1);
	static char ch=getchar();
	while(!isdigit(ch)){t=ch=='-'?-1:t;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*t;
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i].p=read(),a[i].b=read();
	}sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		a[i].id=i,st.insert(a[i]);
	}st.insert({(int)2e9,0,n+1});
	for(int i=1;i<=n+1;i++){
		diff[i]=a[i].b^a[i-1].b;
	}
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		it=st.lower_bound({l,0});
		if((*it).p<=r)l=(*it).id;else continue;
		it=st.upper_bound({r,0}),r=(*it).id;
		to[l].push_back({r,i}),to[r].push_back({l,i});
	}
	topu(n+1);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			topu(i);
			if(diff[i]){
				cout<<"-1\n";return 0;
			}
		}
	}
	cout<<ans.size()<<'\n';
	sort(ans.begin(),ans.end());
	for(int i:ans)cout<<i<<' ';
	return 0;
} 
```

---

## 作者：wxzzzz (赞：10)

### 思路

考虑如何区间取反。

区间取反相当于给区间异或 $1$，可以异或差分，$[l,r]\oplus 1$ 相当于差分数组 $d$ 上 $d_l\oplus 1,d_{r+1}\oplus 1$。

这种修改具有传递性，因此想到建图。

可以把操作 $[l,r]$，看作一条边，假如选了这条边，那么在差分数组上 $d_l\oplus 1,d_{r+1}\oplus 1$。

假如最终全局都为 $0$，那么必然有 $d_i=0\ (i\in[1,n])$。最终目标就是将整张图所有节点变为 $0$。

如果直接建图显然会有环，无法确定传递关系。

这里又有一个性质：不可能操作一个环上的所有边。因为如果操作了一个环，那么环上每个点都被异或了两次，相当于没有操作。

因此只需保留这张图的一个生成森林。

直接从叶子节点往上转移，如果某个 $x$ 的子节点 $y$ 的差分数组 $d_y=1$，那么必须选择 $(x,y)$ 这条边，计入答案。

最后如果某棵以 $i$ 为根的树在转移完后 $d_i=0$，那么这棵树合法。

注意节点 $n+1$ 的操作，它是什么值都合法，以它为根单独转移一遍。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, idx, d[200005], f[200005], v[200005], h[200005], e[200005], ne[200005], ans[200005];
bool vis[200005];
struct light {
    int a, b;
} p[200005];
bool cmp(light x, light y) {
    return x.a < y.a;
}
int findl(int x) {
    int l = 0, r = n, mid, ret = n + 1;

    while (l <= r) {
        mid = l + r >> 1;

        if (p[mid].a >= x)
            ret = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    return ret;
}
int findr(int x) {
    int l = 0, r = n, mid, ret = n + 1;

    while (l <= r) {
        mid = l + r >> 1;

        if (p[mid].a > x)
            ret = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    return ret;
}
int find(int x) {
    if (x == f[x])
        return x;

    return f[x] = find(f[x]);
}
void add(int x, int y, int z) {
    v[++idx] = y, e[idx] = z, ne[idx] = h[x], h[x] = idx;
}
void dfs(int x, int F) {
    vis[x] = 1;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == F)
            continue;

        dfs(y, x);

        if (d[y])
            ans[++cnt] = e[i];

        d[x] ^= d[y];
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    for (int i = 1; i <= n + 1; i++)
        f[i] = i;

    for (int i = 1; i <= n; i++)
        cin >> p[i].a >> p[i].b;

    sort(p + 1, p + n + 1, cmp);

    for (int i = n; i >= 1; i--)
        d[i] = p[i].b ^ p[i - 1].b;

    for (int i = 1, x, y, fx, fy; i <= m; i++) {
        cin >> x >> y;
        x = findl(x), y = findr(y);
        fx = find(x), fy = find(y);

        if (fx != fy)
            add(x, y, i), add(y, x, i), f[fx] = fy;
    }

    dfs(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (vis[i])
            continue;

        dfs(i, 0);

        if (d[i]) {
            cout << "-1";
            return 0;
        }
    }

    cout << cnt << '\n';
    sort(ans + 1, ans + cnt + 1);

    for (int i = 1; i <= cnt; i++)
        cout << ans[i] << ' ';

    return 0;
}
```

---

## 作者：xtx1092515503 (赞：8)

昨天ABC只做出来4题……废了废了……

这题建图方法好神仙的亚子。

首先，本题的第一个难点（？）是要想出在异或意义下进行**差分**。在差分后，原本是对一段区间的操作，就可以被转换成点对之间的操作。

在差分后，我们的问题变成了：给你一个$0/1$数列和一些点对，你可以将同一对数异或$1$，使得最终得到一个全$0$的数列。

一提到**点对**，我们立马就想到无向边。

这样，我们就将问题转换成了：在一张无向图中，选择一些边，将边的端点上的数异或上$1$，问能否得到一张全$0$图。

稍等，我们看看这个模型能否简化。比如说，它能否是一颗树呢？

显然可以。如果你选择了一个环上所有的边，就跟没有选择任何边没有区别（每个点都被异或了两次）。我们可以求出该图的任意一颗生成森林，一样可以。在代码中，运用了~~冰茶姬~~并查集来求生成森林。

是森林的话，我们就可以进行树形DP了。我们考虑一个如下的树形DP：

叶子节点的回溯值即为它自己的值。

在考虑一个非叶子节点时：

如果它的一个儿子回溯上来了$1$，就意味着它需要被异或一下，就意味着连接它和当前儿子的这条边是应该选择的。否则，就意味着不应该选择这条边。

一个非叶子节点的回溯值即为它本身的值异或上所有儿子的回溯值的异或和。因为每有一个$1$的儿子节点，不仅这个儿子会被修改，它自己也会被修改。

那么，对于根节点，如果它返回上$1$，就说明有不合法的地方，没有一组合理的解决方案。

当然，如果它返回$0$，就说明当前这棵树是合法的。

稍等，我们好像忽略了$n+1$这个节点！在差分并将区间询问转成单点询问时，是有可能出现$n+1$的！

我们就特判一下，因为$n+1$无论返回$0$还是$1$都是合法的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,head[100100],cnt,dsu[100100],pos[100100];
bool sta[100100],vis[100100];
pair<int,bool>p[100100];
struct edge{
	int to,next,id;
}edge[1001000];
void ae(int u,int v,int w){
	edge[cnt].id=w,edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;
	edge[cnt].id=w,edge[cnt].next=head[v],edge[cnt].to=u,head[v]=cnt++;
}
vector<int>v;
int fd(int x){return dsu[x]==x?x:dsu[x]=fd(dsu[x]);}
bool mg(int x,int y){
	x=fd(x),y=fd(y);
	if(x==y)return false;
	dsu[x]=y;
	return true;
}
bool dfs(int x){
	bool res=sta[x];
	vis[x]=true;
	for(int i=head[x];i!=-1;i=edge[i].next){
		if(vis[edge[i].to])continue;
		bool now=dfs(edge[i].to);
		if(now)v.push_back(edge[i].id);
		res^=now;
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head));
	for(int i=1;i<=n+1;i++)dsu[i]=i;
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)pos[i]=p[i].first,sta[i]=p[i].second;
	for(int i=n;i;i--)sta[i]^=sta[i-1];
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r),l=lower_bound(pos+1,pos+n+1,l)-pos,r=upper_bound(pos+1,pos+n+1,r)-pos;
		if(mg(l,r))ae(l,r,i);
	}
	dfs(n+1);
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		if(dfs(i)){puts("-1");return 0;}
	}
	sort(v.begin(),v.end());
	printf("%d\n",v.size());
	for(int i=0;i<v.size();i++)printf("%d ",v[i]);
	return 0;
}
```


---

## 作者：Karry5307 (赞：6)

### 题意

数轴上有 $n$ 个炸弹，第 $i$ 个炸弹在坐标 $A_i$，状态为 $B_i$（$B_i=1$ 表明激活了，反之表明没有）。

还有 $m$ 根绳子，如果割断第 $i$ 根绳子，那么坐标处于 $L_i$ 和 $R_i$ 之间的炸弹的状态会反转。

你需要回答是否有一种切断绳子的方式使得所有炸弹最终处于未激活状态，如果有，输出方案。

$\texttt{Data Range:}1\leq n\leq 10^5,1\leq m\leq 2\times 10^5,1\leq A_i\leq 10^9,1\leq L_i\leq R_i\leq 10^9$

### 题解

好题，但是场上只想出了一半，我还是太菜了。

感谢 Mital 神仙告诉我做另一半！

如果你做过[「雅礼集训 2018 Day2」操作](https://loj.ac/problem/6500) 的话，那么这个题一开始应该不会很难。

注意到记录坐标是没有用的，考虑首先对炸弹和绳子的坐标进行离散化。

现在，我们重新定义 $L_i$ 和 $R_i$：如果割断第 $i$ 根绳子，那么介于第 $L_i$ 个炸弹和第 $R_i$ 个炸弹的状态会反转。

接着，就像 $\texttt{yali}$ 集训的那道题目一样，我们考虑差分。这样子，反转状态从改变一个区间变成只需要将 $L_i$ 和 $R_i+1$ 异或一下。

然后我们连一条连接 $L_i$ 和 $R_i+1$ 的无向边。所以问题变成给一张图，使得每个点的度数满足奇偶性与 $c_i\operatorname{xor} c_{i-1}$ 相同。

但是 $R+1$ 可能等于 $n+1$，但是 $n+1$ 这个点是没有度数奇偶性限制的，所以要先搞定他，再来搞定后面的有度数奇偶性限制的其他点。

这个随便 $\texttt{dfs}$ 一遍就没了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51;
struct Node{
	ll x,y;
	inline bool operator <(const Node &rhs)const
	{
		return this->x<rhs.x;
	}
};
struct Segment{
	ll l,r,id;
};
struct Edge{
	ll to,prev,id;
};
Node nd[MAXN];
Segment seg[MAXN];
Edge ed[MAXN<<1];
ll n,m,tot,cnt,l,r,lx,rx,flg,rr;
ll last[MAXN],res[MAXN],w[MAXN],c[MAXN],diff[MAXN],vis[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline void addEdge(ll from,ll to,ll id)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	ed[tot].id=id;
	last[from]=tot;
}
inline ll discrete(ll x)
{
	ll l=1,r=n+1,res=0,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		w[mid]>=x?res=mid,r=mid-1:l=mid+1;
	}
	return res;
}
inline ll discrete2(ll x)
{
	ll l=1,r=n,res=0,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		w[mid]<=x?res=mid,l=mid+1:r=mid-1;
	}
	return res;
}
inline ll dfs(ll node,ll fa,ll x)
{
	ll t=0;
	vis[node]=1;
	for(register int i=last[node];i;i=ed[i].prev)
	{
		if(!vis[ed[i].to])
		{
			t^=dfs(ed[i].to,node,i);
		}
	}
	if(node==fa)
	{
		return t;
	}
	if(diff[node]^t)
	{
		res[++rr]=ed[x].id;
		return 1;
	}
	return 0;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		nd[i].x=read(),nd[i].y=read();
	}
	sort(nd+1,nd+n+1);
	for(register int i=1;i<=n;i++)
	{
		c[i]=nd[i].y,w[i]=nd[i].x;
	}
	for(register int i=1;i<=m;i++)
	{
		l=discrete(lx=read()),r=discrete2(rx=read());
		if(rx<lx)
		{
			continue;
		}
		seg[++cnt]=(Segment){l,r,i};
	}
	for(register int i=1;i<=n;i++)
	{
		diff[i]=c[i]^c[i-1];
	}
	for(register int i=1;i<=cnt;i++)
	{
		addEdge(seg[i].l,seg[i].r+1,seg[i].id);
		addEdge(seg[i].r+1,seg[i].l,seg[i].id);
	}
	dfs(n+1,n+1,0);
	for(register int i=1;i<=n;i++)
	{
		if(vis[i])
		{
			continue;
		}
		if(dfs(i,i,0)!=diff[i])
		{
			return puts("-1"),0;
		}
	}
	printf("%d\n",rr),sort(res+1,res+rr+1);
	for(register int i=1;i<=rr;i++)
	{
		printf("%d ",res[i]);
	}
}
```

---

## 作者：吴思诚 (赞：5)

## AT4831 [ABC155F] Perils in Parallel 题解
[题目传送门](https://www.luogu.com.cn/problem/AT4831)

### 思路
用 $a_i$ 表示炸弹位置,$b_i$ 表示炸弹状态，先对 $n$ 个炸弹离散化。然后类似前缀和的思想，做一遍前缀异或，即对 $l_i$ 到 $r_i$ 的反转被简化成了 $l_i$ 和 $r_i+1$ 的修改，我们用 $p_i$ 来表示 $p_1 \oplus p_2 \oplus p_3 \oplus \cdots \oplus p_i$。考虑直接把 $l_i$ 与 $r_i+1$ 连无向边，问题就被抽象成了一张无向图。接下来在图上做 `dfs`，如果这个点的 $p_i$ 为 $0$，就把它的下标记录下来，并把父亲异或上，如果一次 `dfs` 下来，这个点的 $p_i$ 依然是 $1$，则无解。

___
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct E{
	int u,v,id,next;
}e[400001];
struct B{
	int idx,state;
}bom[400002];
int n,m,p[400002],b[400002],en,h[400001];
bool vis[400002];
set<int>ans;
bool cmp(B a,B b){
	return a.idx<b.idx; 
}
void add(int u,int v,int id){
	e[++en].u=u;
	e[en].v=v;
	e[en].id=id;
	e[en].next=h[u];
	h[u]=en;
}
void dfs(int x){
	vis[x]=1;
	for(int i=h[x];i>0;i=e[i].next){
		int v=e[i].v;
		if(!vis[v]){
			dfs(v);
			if(p[v]==1){
				ans.insert(e[i].id);//记录答案
				p[v]=0;
				p[x]^=1;
			}	
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>bom[i].idx>>bom[i].state;
	sort(bom+1,bom+1+n,cmp);
	p[0]=0;
	for(int i=1;i<=n+1;++i){
		p[i]=bom[i].state^bom[i-1].state;
		b[i]=bom[i].idx;
	}
	for(int i=1;i<=m;++i){
		int L,R;
		cin>>L>>R;
		int l=lower_bound(b+1,b+1+n,L)-b;
		int r=upper_bound(b+1,b+1+n,R)-b;//离散化,upper_bound直接定位到右端点+1
		if(l==r)
			continue;
		add(l,r,i);
		add(r,l,i);
	}
	for(int i=1;i<=n+1;++i)
		if(!vis[i]){
			dfs(i);
			if(p[i]==1){
				cout<<-1;//无解
				return 0;
			}
		}
	cout<<ans.size()<<endl;
	for(int x:ans)
		cout<<x<<' ';
	return 0;
}
```


---

## 作者：Caiest_Oier (赞：3)

# [AT_abc155_f](https://www.luogu.com.cn/problem/AT_abc155_f)    

感觉很水啊，不知道为什么是 2700。   

原问题上一个二分就可以转化成：在给出的区间中选若干个进行 $01$ 翻转，要翻转成全零序列。对序列做一下差分，又转化成每次可以选两个点 $01$ 翻转，翻成全零序列。    

对于一个翻转对 $(x,y)$，连接 $x$ 和 $y$，则对于一个连通块，每次可以选任意两个点翻转，只需要将两点间的路径选中即可。于是有方案的充要条件就变成了每个连通块中都有偶数个需要翻转的点。对每一个连通块跑出任意一棵生成树，则转化成树上路径覆盖问题。对于一条边 $(fa_p,p)$，其需要被选中等价于 $p$ 的子树中有奇数个需要翻转的点，于是 dfs 一遍就可以了。    


代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l[500003],r[500003],lft,rgt,mid;
struct Pt{
	int wz;
	int val;
}P[500003];
bool comp(Pt X,Pt Y){
	return X.wz<Y.wz;
}
int a[500003],b[500003],sz[500003],cs[500003],vis[500003],k1,k2,k3;
vector<pair<int,int> >E[500003];
void dfs(int now){
	vis[now]=1;
	if(a[now])sz[now]++;
	for(auto i:E[now]){
		if(vis[i.first])continue;
		dfs(i.first);
		sz[now]+=sz[i.first];
		if(sz[i.first]%2!=0)cs[i.second]=1;
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>P[i].wz>>P[i].val;
	sort(P+1,P+n+1,comp);
	for(int i=1;i<=m;i++){
		cin>>l[i]>>r[i];
		lft=1;
		rgt=n;
		while(lft<rgt){
			mid=((lft+rgt)>>1);
			if(P[mid].wz>=l[i])rgt=mid;
			else lft=mid+1;
		}
		if(P[lft].wz<l[i])l[i]=n+1;
		else l[i]=lft;
		lft=1;
		rgt=n;
		while(lft<rgt){
			mid=((lft+rgt)>>1)+1;
			if(P[mid].wz<=r[i])lft=mid;
			else rgt=mid-1;
		}
		if(P[lft].wz>r[i])r[i]=0;
		else r[i]=lft;
	}
	for(int i=1;i<=n;i++)b[i]=P[i].val;
	for(int i=1;i<=n+1;i++)a[i]=(b[i]^b[i-1]);
	for(int i=1;i<=m;i++)r[i]++;
	n++;
	for(int i=1;i<=m;i++){
		if(l[i]==r[i])continue;
		E[l[i]].emplace_back(make_pair(r[i],i));
		E[r[i]].emplace_back(make_pair(l[i],i));
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		dfs(i);
		if(sz[i]%2!=0){
			cout<<"-1";
			return 0;
		}
	}
	for(int i=1;i<=m;i++)k1+=cs[i];
	cout<<k1<<endl;
	for(int i=1;i<=m;i++)if(cs[i])cout<<i<<" ";
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

模拟赛再一次玉玉了，过来看看简单题。

-----

显然可以离散化一下。假设现在这 $n$ 盏灯都是相邻的。

考虑求出灯状态的异或差分数组，那么我们实际上每次可以更改 $l$ 和 $r+1$ 处的灯的状态。

考虑建立一张图，对于所有这样的 $(l,r)$ 在 $l$ 和 $r+1$ 之间连边。现在问题在于：能否通过将某些边的两端节点取反，使得所有点都变成 $0$？

有解的一个必要条件显然是每个联通块内 $1$ 的个数是偶数。

图过于困难了，我们不妨对于每个联通块求出一棵生成树。

树上这个问题你会吗？

显然，我们随便找一个点作为根，从下向上遍历。如果某个点子树内 $1$ 的个数是奇数，他和父亲的那条边就要被操作。使用数学归纳法容易证明。

由于我们已经保证了整个联通块内 $1$ 的个数是偶数，所以这样做肯定合法。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,m,a[MAXN],vis[MAXN],frnk[MAXN],sze[MAXN],b[MAXN],lsh[MAXN],st[MAXN];
vector<pair<int,int>> G[MAXN];
void dfs(int u,int f) {
	vis[u]=1,sze[u]=st[u];
	for(auto pr:G[u]) {
		int v=pr.first,id=pr.second;
		if(vis[v]) continue ;
		frnk[v]=id;
		dfs(v,u),sze[u]^=sze[v];
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i]>>b[i],lsh[i]=a[i];
	sort(lsh+1,lsh+n+1);
	ffor(i,1,n) st[lower_bound(lsh+1,lsh+n+1,a[i])-lsh]=b[i];	
	roff(i,n+1,1) st[i]^=st[i-1];
	ffor(i,1,m) {
		int l,r;
		cin>>l>>r;
		l=lower_bound(lsh+1,lsh+n+1,l)-lsh,r=upper_bound(lsh+1,lsh+n+1,r)-lsh;
		if(l!=r) G[l].push_back({r,i}),G[r].push_back({l,i});	
	}
	ffor(i,1,n+1) if(!vis[i]) {
		dfs(i,0);	
		if(sze[i]&1) return cout<<-1,0;
	}
	vector<int> ans;
	ffor(i,1,n+1) if(sze[i]) ans.push_back(frnk[i]);
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(auto id:ans) cout<<id<<' ';
	return 0;
}
```

---

## 作者：KokiNiwa (赞：2)

## ABC 155 F - Perils in Parallel

[题目链接](https://atcoder.jp/contests/abc155/tasks/abc155_f)

## 题目叙述

给你一个01数列和$n$个区间$[l_i,r_i]$，每个区间$[l_i,r_i]$代表你可以对这个区间里的所有数异或$1$，请问最后能不能把所有数异或成$0$。

## 题解

+ 对问题进行转化，对一个区间$[l,r]$进行异或可以转化为对一个前缀异或的两个点$l$和$r+1$进行异或。
+ 给每个区间的$l,r+1$这两个点进行连边，问题再次转化为是否可以在一个图上删掉一些边使得每个点满足他应该满足的奇偶性。
+ 如何解决这个呢？可以每一个连通块搞一个生成树，每次每个点如果不符合要求就删掉父亲边，这样只会剩下根节点有可能不符合要求，如果符合要求就行，不符合要求就不行。
+ 其实如果单纯判断

## 知识点

+ 操作题，尽量把对一个区间的操作转化为对几个点的操作。比如这道题的转化方法是利用前缀异或类似的东西。
+ 两个数异或上同一个数是双向的问题，所以给这两个数连边。
+ 找不变量（虽然这道题里没什么用），但是可以发现一条边删掉可以使得两个点的度数同时减少，所以度数总和的奇偶性不变。

---

## 作者：_zexal_ (赞：1)

## 思路
首先，我们注意到 $l \leq r\leq 10^9 $ 且 $a \leq 10^9$，如果我们直接存，一定会爆空间，所以在使用之前，我们需要一个离散化。
```cpp
	F(i,1,n) {
		cin>>a[i].num>>a[i].nd;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1; i<=n; i++) p[i]=a[i].num,cf[i]=a[i].nd;
	for(int i=n; i>=1; i--) cf[i]^=cf[i-1];
```
接下来，我们步入正题。考虑到我们需要操作的是一个区间，这是一个很难搞的事情，不妨考虑使用差分，把区间操作搞到点对上，这样就稍微好操作一点了。我们会神奇的发现，这是可以放在树上的，那么，进一步延伸，我们可以放在一个图的生成树上。然后这道题其实就非常好操作了，我们直接用一个搜索进行操作，用所有和他有关系的点对和他进行修改，又由于每次操作奇偶性不变，所以如果异或值不为零则说明无解。需要注意的一点是差分后 $n+1$ 对答案是没有影响的，所以我们需要先跑一个 $n+1$ 的情况。

```cpp
#include<bits/stdc++.h>

using namespace std;
//#define int long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
void Debug() {
	cerr<<"-------------"<<endl;
}
const int Maxn=2e6+5;
struct node {
	int num;
	bool nd;
} a[Maxn];
int n,m,cf[Maxn],f[Maxn],p[Maxn],l,r,head[Maxn],tot,w[Maxn],nxt[Maxn],to[Maxn];
bool cnt[Maxn];
bool cmp(node a,node b) {
	return a.num<b.num;
}
void AddEdge(int u,int v,int w1) {
	to[++tot]=v;
	w[tot]=w1;
	nxt[tot]=head[u];
	head[u]=tot;
	return;
}
int find(int u) {
	if(u==f[u])return u;
	else  f[u]=find(f[u]);
	return f[u];
}
bool Check(int u,int v) {
	if(find(u)==find(v)) return false;
	else f[find(u)]=find(v);
	return true;
}
bool vis[Maxn];
vector<int> v;
bool Dfs(int u) {
//	Debug();
//	cout<<u<<endl;
	bool falg=cf[u];
	vis[u]=1;
	for(int i=head[u]; i; i=nxt[i]) {
		//cout<<to[i]<<" ";
		if(vis[to[i]]) continue;
		//	cout<<to[i]<<" ";
		bool Ans=Dfs(to[i]);
		if(Ans) v.push_back(w[i]);
		falg^=Ans;
		//	cout<<endl;
	}
	return falg;
}
signed main() {
	cin>>n>>m;
	F(i,1,n+1) f[i]=i;
	F(i,1,n) {
		cin>>a[i].num>>a[i].nd;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1; i<=n; i++) p[i]=a[i].num,cf[i]=a[i].nd;
	for(int i=n; i>=1; i--) cf[i]^=cf[i-1];
	F(i,1,m) {
		cin>>l>>r;
		l=lower_bound(p+1,p+n+1,l)-p,r=upper_bound(p+1,p+n+1,r)-p;
		//cout<<l<<" "<<r<<endl;
		if(Check(l,r)) AddEdge(l,r,i),AddEdge(r,l,i);
	}
	Dfs(n+1);
	//vis[n+1]=1;
	for(int i=1; i<=n; i++) {
		if(vis[i]) continue;
		else if(Dfs(i)) {
			cout<<-1;	
			return 0;
		}
	}
	sort(v.begin(),v.end());
	//cout<<v.size();
	cout<<v.size()<<endl;
	for(int i=0; i<v.size(); i++) cout<<v[i]<<" ";
	return 0;
}
```


---

## 作者：Lskkkno1 (赞：1)

- [AT4831 [ABC155F] Perils in Parallel](https://www.luogu.com.cn/problem/AT4831)

### 题目描述

平面上有 $n$ 个点，每个点有一个位置是 $p_i$ 和一个状态 0 / 1。

有 $m$ 个操作，每个操作将 $l_i \to r_i$ 的点全部翻转。

问可不可以将所有点都翻成 0，如果可行输出方案。

### 正解

一次操作将 $l \to r$ 全部翻转，翻转的点太多了，可不可以让翻转的点少一些？

考虑”做差“，令排序后第 $i$ 个点的状态为 $s_i \operatorname{xor} s_{i - 1}$，这样每次翻转只会变动两个位置 $l_i$ 和 $r_{i + 1}$。

将所有操作的 $l_i$ 和 $r_i$ 连边，发现一个联通块里面每次可以选两个状态为 1 的点进行一次消除。

那么每个联通块只要判断一下 1 的奇偶性就可以确定是否有答案了。

考虑怎么构造一组解，状态为 1 的点可以通过一条边的操作到达另一个端点，那么我就让一个联通块内状态为 1 的点都到 $dfs$ 树的根节点就好了。

从当前节点到根节点路径的边全部 + 1 操作，树差分可以解决，最后输出操作数为奇数的边即可。

$\color{DeepSkyBlue} {Code}$

```cpp
#include <bits/stdc++.h>
#define N 200005

using namespace std;

int n, m;
int head[N], nex[N << 1], to[N << 1], eid[N << 1], ecnt;
int p[N], s[N];

struct light {
	int pos, state;
}lig[N];

bool cmpLight(const light &lhs, const light &rhs) { return lhs.pos < rhs.pos; }

inline int read() {
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}
inline void addE(int u, int v, int id) {
	to[++ecnt] = v, eid[ecnt] = id;
	nex[ecnt] = head[u], head[u] = ecnt;
}

int cntOne;
int dif[N], fa[N], fe[N];
bool vis[N];

void dfs(int u) {
	if(s[u]) ++dif[u], ++cntOne;
	for(int i = head[u], v; i; i = nex[i]) {
		v = to[i];
		if(fa[v]) continue;
		fa[v] = u, fe[v] = eid[i], dfs(v);
		dif[u] += dif[v];
	}
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		lig[i].pos = read(), lig[i].state = read();
	
	sort(lig + 1, lig + n + 1, cmpLight);
	for(int i = 1; i <= n; ++i)
		p[i] = lig[i].pos, s[i] = lig[i].state;
	for(int i = n + 1; i >= 1; --i)
		s[i] = s[i] ^ s[i - 1];
		
	for(int i = 1, l, r; i <= m; ++i) {
		l = read(), r = read();
		l = lower_bound(p + 1, p + n + 1, l) - p;
		r = upper_bound(p + 1, p + n + 1, r) - p - 1;
		if(l <= r) {
			addE(l, r + 1, i), addE(r + 1, l, i);
		}
	}
	
	for(int i = 1; i <= n + 1; ++i)
		if(!fa[i]) {
			fa[i] = i;
			dfs(i);
			if(cntOne & 1) {
				puts("-1");
				return 0;
			}
		}
	
	int cnt = 0;
	for(int i = 1; i <= n + 1; ++i)
		if(dif[i] & 1)
			vis[fe[i]] = true, ++cnt;
	
	printf("%d\n", cnt);
	for(int i = 1; i <= m; ++i)
		if(vis[i])
			printf("%d ", i);
	putchar('\n');
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

很巧妙的构造题。

区间异或操作，让我们联想到差分。对于开关 $[l,r]$，将 $(l,r+1)$ 连边，构成一个图。每个点上的权值是差分数组的值。最后每个点的权值都为 $0$。

下文“按 $(u,v)$”的意思是将边 $(u,v)$ 所代表的按钮按一次。

然后发现只需要在这个图的生成树上 DP 即可。为什么呢？假如有边 $(v_1,v_2),(v_2,v_3),\cdots,(v_{n-1},v_n)$，还有一条返祖边 $(v_1,v_n)$，如果想按 $(v_1,v_n)$，其实可以把 $(v_1,v_2),(v_2,v_3),\cdots,(v_{n-1},v_n)$ 这些边全部按一次，$v_{2\sim n-1}$ 被按两次，值不变。因此返祖边都是无意义的。

DP 不难。对于点 $u$ 的所有子结点 $v$，如果 $v$ 的权值是 $1$，就要把边 $(u,v)$ 按一次。

```cpp
// Title:  Perils in Parallel
// Source: ABC155F
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define F first
#define S second
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;

int n, m, vis[N], f[N];
vector<pii> g[N]; pii a[N];
vector<int> res;
void dfs(int u)
{
	vis[u]=1;
	for(auto [v,id]:g[u]) if(!vis[v])
	{
		dfs(v);
		if(f[v]) res.push_back(id), f[u]^=1, f[v]=0;
	}
}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d%d", &a[i].F, &a[i].S);
	sort(a+1, a+n+1);
	rep(i, 1, n) f[i]=a[i].S^a[i-1].S;
	rep(i, 1, m)
	{
		int l, r; scanf("%d%d", &l, &r);
		l=lower_bound(a+1, a+n+1, pii{l, 0})-a;
		r=upper_bound(a+1, a+n+1, pii{r, 1e9})-a;
		g[l].push_back({r, i}), g[r].push_back({l, i});
	}
	dfs(n+1);
	rep(u, 1, n) if(!vis[u])
	{
		dfs(u);
		if(f[u]) return puts("-1"), 0;
	}
	sort(res.begin(), res.end());
	printf("%d\n", res.size());
	for(int x:res) printf("%d ", x);
	
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

将序列进行异或差分可以将区间操作变为单点操作，将操作的两点连边可以得到一张图 $G$。令差分数组为 $sub$，原题转化为选择图 $G$ 的一张子图 $G'$ 满足除点 $n+1$ 外，点 $u$ 的度数和 $sub_u$ 的奇偶性相同。

考虑如果选择一个环，那么环上所有点的度数必为偶数，所以环是不会对答案有贡献的，我们只需要求出 $G$ 的生成森林 $T$ 的子图 $T'$ 满足上述条件即可。

考虑经典套路，贪心将一个节点的子节点解决掉，然后通过和父亲的边解决掉自己，注意特判点 $n+1$。时间复杂度 $O(n\log n)$，瓶颈在于排序。

```cpp
#include<iostream>
#include<algorithm>
#include<numeric>
#include<map>
#include<set>
const int sz=1e5+10;
int a[sz],b[sz];
std::pair<int,int>c[sz];
std::basic_string<int>graph[sz];
std::map<std::pair<int,int>,int>id;
std::set<int>s;
bool vis[sz];
void dfs(int u,int fau){
    vis[u]=true;
    for(int v:graph[u]){
        if(v==fau)continue;
        dfs(v,u);
    }
    if(a[u]==1)a[fau]^=1,s.insert(id[std::make_pair(fau,u)]);
}
struct UFS{
    int fa[sz],ssz[sz];
    void clear(int n){
        std::iota(fa+1,fa+n+1,1);
        std::fill(ssz+1,ssz+n+1,1);
    }
    int find(int u){
        if(fa[u]==u)return u;
        return fa[u]=find(fa[u]);
    }
    void merge(int u,int v){
        int fu=find(u),fv=find(v);
        if(fu==fv)return;
        if(ssz[fu]>ssz[fv])std::swap(fu,fv);
        fa[fu]=fv,ssz[fv]+=ssz[fu];
    }
}ufs;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)std::cin>>c[i].first>>c[i].second;
    std::sort(c+1,c+n+1);
    for(int i=1;i<=n;i++)a[i]=c[i].second,b[i]=c[i].first;
    for(int i=n;i>=1;i--)a[i]^=a[i-1];
    ufs.clear(n+1);
    for(int i=1,l,r;i<=m;i++){
        std::cin>>l>>r;
        l=std::lower_bound(b+1,b+n+1,l)-b,r=std::upper_bound(b+1,b+n+1,r)-b;
        if(ufs.find(l)==ufs.find(r))continue;
        ufs.merge(l,r);
        graph[l]+=r,graph[r]+=l;
        id[std::make_pair(l,r)]=id[std::make_pair(r,l)]=i;
    }
    dfs(n+1,0);
    if(s.find(0)!=s.end())s.erase(0);
    for(int i=1;i<=n;i++)if(!vis[i])dfs(i,0);
    if(s.find(0)!=s.end())std::cout<<"-1\n",exit(0);
    std::cout<<s.size()<<"\n";
    for(int p:s)std::cout<<p<<" ";
    std::cout<<"\n";
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](https://atcoder.jp/contests/abc155/tasks/abc155_f)

[洛谷传送门](https://atcoder.jp/contests/abc155/tasks/abc155_f)

## 分析

先对原数组异或差分一下，这样区间异或转化为两次单点异或。考虑把每个开关操作的两个点连起来，构成一张图。我们的操作是选中一条边，将其两个端点的状态取反，我们的目标是将所有点点权变成 $0$。我们考虑任意一棵 dfs 树和其上的一条返祖边，这条返祖边会构成一个环。注意到我们把整个环上所有边操作一遍等于没操作，所以操作这条返祖边相当于操作一遍这条返祖边连接的两个点在 dfs 树上的路径上的所有边。于是返祖边无用，全部删掉。这样就变成了一棵树（森林），而这种情况是好处理的，只需要从叶子往上考虑，如果叶子为 $1$ 就操作叶子上面的边，然后依次向上推，如果最后根是 $0$ 则合法，否则不可能达成。最后输出方案时记得排序。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int n, m;
struct Lamp {
    int p, s;
} a[100005];
struct Switch {
    int l, r, id;
} b[1000005];
int head[1000005], nxt[2000005], to[2000005], ew[2000005], ecnt;
void add(int u, int v, int ww) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt, ew[ecnt] = ww; }
int ans[1000005], acnt;
bool vis[1000005];
void dfs(int x) {
    vis[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            dfs(v);
            if (a[v].s) {
                ans[++acnt] = ew[i];
                a[x].s ^= 1;
                a[v].s = 0;
            }
        }
    }
}
signed main() {
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].p >> a[i].s;
    sort(a + 1, a + n + 1, [](Lamp a, Lamp b) { return a.p < b.p; });
    for (int i = n + 1; i; i--) a[i].s ^= a[i - 1].s;
    for (int i = 1; i <= m; i++) cin >> b[i].l >> b[i].r, b[i].id = i;
    sort(b + 1, b + m + 1, [](Switch a, Switch b) { return a.l < b.l; });
    for (int i = 1, j = 1; i <= m; i++) {
        while (j <= n && a[j].p < b[i].l) ++j;
        b[i].l = j;
    }
    sort(b + 1, b + m + 1, [](Switch a, Switch b) { return a.r > b.r; });
    for (int i = 1, j = n; i <= m; i++) {
        while (j && a[j].p > b[i].r) --j;
        b[i].r = j;
    }
    for (int i = 1; i <= m; i++) {
        if (b[i].r >= b[i].l) {
            add(b[i].l, b[i].r + 1, b[i].id);
            add(b[i].r + 1, b[i].l, b[i].id);
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        if (!vis[i]) {
            dfs(i);
            if (a[i].s) {
                cout << -1 << "\n";
                return 0;
            }
        }
    }
    cout << acnt << "\n";
    sort(ans + 1, ans + acnt + 1);
    for (int i = 1; i <= acnt; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

首先离散化，接着进行一步差分，这样区间异或变为两次单点异或。

两个点之间的操作启发我们建图，这样形成一张无向图，每个点有 $0,1$ 点权，每次选一条边，翻转两端的权值，要求构造一组方案使得每个点权为 $0$。

容易发现只有生成森林是有用的，因为非树边都可以用对应的链凑出来，这样就变成了若干个树上问题。我们可以自底向上构造，对于叶子节点，可以确定其与父亲连边是否选择，确定后删除这个点，不断进行这个流程直到剩下一个根节点，如果为 $n+1$ 则不限定结果，否则限定结果为 $0$，需要判断无解的情况。

时间复杂度为排序的 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9;
ll n,m,fa[N],tag[N],vis[N];
pii p[N];
vector<pii>to[N];
ll find(ll x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
ll dfs(ll x,ll f){
    vis[x]=1;
    ll xt=p[x].second;
    for(pii es:to[x]){
        ll y=es.first,id=es.second;
        if(y==f)continue;
        ll q=dfs(y,x);
        if(q)xt^=1,tag[id]=1;
    }
    return xt;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,1,n)p[i].first=read(),p[i].second=read();
    sort(p+1,p+n+1);
    per(i,n,1)p[i].second^=p[i-1].second;
    iota(fa+1,fa+n+2,1);
    rep(i,1,m){
        ll tl=read(),tr=read();
        ll L=n+1,R=0,l=1,r=n;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(p[mid].first>=tl)L=mid,r=mid-1;
            else l=mid+1;
        }
        l=1,r=n;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(p[mid].first<=tr)R=mid,l=mid+1;
            else r=mid-1;
        }
        if(L>R)continue;
        if(find(L)!=find(R+1)){
            fa[find(L)]=find(R+1);
            to[L].push_back({R+1,i});
            to[R+1].push_back({L,i});
        }
    }
    per(i,n+1,1){
        if(!vis[i]){
            ll s=dfs(i,0);
            if(i<=n&&s)return puts("-1"),0;
        }
    }
    ll cnt=accumulate(tag+1,tag+m+1,0ll);
    write(cnt),putchar('\n');
    rep(i,1,m){
        if(tag[i])write(i),putchar(' ');
    }
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

建图思维题。

首先将异或操作转化为 $(x+1) \bmod 2$ 操作，这样可以和前缀和 / 差分挂上钩。

考虑原序列的差分数组 $d$，对于 $l \sim r$ 的操作，相当于是将 $d_l + 1, d_{r + 1} + 1$。很简单也很套路。

对于每个按钮，从 $l$ 向 $r + 1$ 连边，形成一张图。需要找到一张子图，使得 $d_i = 1$ 的点度为奇数，$d_i = 0$ 的点度为偶数。

考虑到如果图中出现环，将所有边都选上一次必然不是最佳选择，因为全部选上相当于不选。

因此保留原图的一棵生成森林，dfs 匹配即可。匹配方法是从叶子忘根匹配。如果当前边为 $x \rightarrow y$，$y$ 是 $1$，而且在子树里匹配了偶数次，则 $(x, y)$ 必选，否则必不选。

选择生成森林的方式可以保留 dfs 树，一遍 dfs 就可以做完。匹配时也可以用 dfs 实现。复杂度显然 $O(n \log n)$，瓶颈在于排序和离散化。

代码略微压行。

```cpp
void dfs(int u) {
    vis[u] = 1; for (auto [v, id] : E[u]) if (!vis[v])
		add2(u, v, id), fa[v] = u, dfs(v);
}
void dfs2(int u, int Id) {
	vis[u] = 1; for (auto [v, id] : E2[u]) dfs2(v, id);
	if (s[u]) s[fa[u]] ^= 1, s[u] ^= 1, ans.push_back(Id);
}
bool check() { rep(i, 1, n + 1) if (s[a[i]]) return 0; return 1; }
bool solve(int w) {
    ans.clear(); memset(s, 0, sizeof s); memset(st, 0, sizeof st); b[n + 1] = w;
    rep(i, 1, n + 1) st[a[i]] = b[i]; rep(i, 1, n) if (!vis[i]) dfs(i);
	rep(i, 1, n + 1) s[i] = st[i] ^ st[i - 1]; memset(vis, 0, sizeof vis);
	rep(i, 1, n) { if (!vis[i]) dfs2(i, 0); if (s[0]) return 0; }
	if (!check()) return 0; sort(ans.begin(), ans.end()); return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d%d", &a[i], &b[i]); a[n + 1] = V;
	rep(i, 1, n + 1) p.push_back(a[i]);
	rep(i, 1, m) scanf("%d%d", &l[i], &r[i]);
	sort(p.begin(), p.end()); p.resize(unique(p.begin(), p.end()) - p.begin());
	auto find = [&](int x) { return lower_bound(p.begin(), p.end(), x) - p.begin() + 1; };
	rep(i, 1, m) add(find(l[i]), find(r[i] + 1), i); rep(i, 1, n + 1) a[i] = find(a[i]);
	if (solve(0)) { printf("%d\n", (int)ans.size()); for (int i : ans) printf("%d ", i); return 0; }
	if (solve(0)) { printf("%d\n", (int)ans.size()); for (int i : ans) printf("%d ", i); return 0; }
	return puts("-1"), 0;
}
```

---

## 作者：TernaryTree (赞：0)

很套路也很典的题？为啥 $2700$ 啊。

题目大意可以转化为 $01$ 序列，可以按值翻转给定的区间，让最终序列全为 $0$，构造方案。

很经典的东西阿，就是模 $2$ 意义下差分一手，翻转的操作就是取反 $l$ 和 $r+1$ 上的权值了。

又是一个很经典的东西阿，我们将 $l$ 和 $r+1$ 连边，则转化为了在一个图上选择一些边，使得每个点连接的边中被选择的个数的奇偶性与差分相同。

考虑在每个连通块里跑出一棵生成树（dfs 树），dfs 从叶子往根处理，先将儿子以下的处理掉，如果当前这个点与差分奇偶性不同，就选择往父亲的这条边。

注意到 dfs 树的根节点有可能不满足条件。考虑何时会不满足条件，手摸可以发现，此时连通块中差分为 $1$ 的数的个数为奇数。反之，若个数为奇数，由于我们选择一条边，贡献两个端点，其总和的奇偶性不变，所以只要根节点不合法，就直接输出 `-1`。

代码不难，读者可以尝试自己实现。

---

