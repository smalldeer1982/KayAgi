# Minimal Diameter Forest

## 题目描述

给定一片森林——一个有 $n$ 个顶点的无向图，保证其每个连通分量都是一棵树。

一个连通无向图的直径（即“最长最短路”）定义为任意两点之间最短路径中的最大边数。

你的任务是向该图中添加一些边（可以为零），使得整个图变成一棵树，并且该树的直径尽可能小。

如果有多种方案，输出任意一种即可。

## 说明/提示

在第一个样例中，添加边 $(1, 4)$ 或 $(3, 4)$，最终直径为 $3$。但如果添加边 $(2, 4)$，直径可以变为 $2$。

第二个样例中，唯一可选的边是 $(1, 2)$，直径为 $1$。

第三个样例中，不能再添加边，直径已经是 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 2
2 3
```

### 输出

```
2
4 2
```

## 样例 #2

### 输入

```
2 0
```

### 输出

```
1
1 2
```

## 样例 #3

### 输入

```
3 2
1 3
2 3
```

### 输出

```
2
```

# 题解

## 作者：daifucong (赞：5)

打CF虚拟比赛的时候一个同学怂恿我倒着切题

然后我就卡在了这道题上，并且成功掉到了5000名以外

看到这道题第一反应直接菊花图就可以了

想了一会儿发现这道题和CF455C Civilization有点像，每次随便找两个连通块连接它们直径的中点即可

Wrong Answer on test 18

直到吃晚饭的时候才发现只要暴力枚举菊花图的根即可

枚举出菊花图的根后，从根向所有连通块直径的中点连一条边

因为连通块会和其他连通块一起经过根对直径产生贡献，而一个连通块的贡献为连通块中与根连边的节点到它的直径两端中的较远点的距离，不难发现这个距离在根节点向直径的中点连边时最小

大力两次DFS求直径，当直径比当前答案小时更新答案

费劲一番周折后终于A了这个题

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1100;
int head[maxn],nxt[maxn<<1],ver[maxn<<1],tot;
inline void addedge(int a,int b)
{
	nxt[++tot]=head[a];ver[tot]=b;head[a]=tot;
	nxt[++tot]=head[b];ver[tot]=a;head[b]=tot;
}
int n,m;
int fa[maxn],mxdis,getv;
inline void dfs(int x,int fat,int nowdep)
{
	if(nowdep>mxdis) mxdis=nowdep,getv=x;fa[x]=fat;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];if(y==fat) continue;
		dfs(y,x,nowdep+1);
	}
}
inline pair<int,int> getcenter(int x)
{
	mxdis=0;dfs(x,0,1);
	int get1=getv;
	mxdis=0;dfs(get1,0,1);
	int getlen=mxdis-1;
	int now=getv;
	for(int i=1;i<=((getlen+1)>>1);i++) now=fa[now];
	return make_pair(getlen,now);
}
//first为直径，second为直径的中点
int Fa[maxn];
inline int find(int x){return x==Fa[x]?x:Fa[x]=find(Fa[x]);}
vector<pair<int,int> > V;
int tmp[maxn],tmpnxt[maxn<<1],tmpver[maxn<<1];
inline int check(int x)
{
	tmp[0]=tot;for(int i=1;i<maxn;i++) tmp[i]=head[i];
	for(int i=1;i<(maxn<<1);i++) tmpnxt[i]=nxt[i],tmpver[i]=ver[i];
	for(int i=0;i<(int)V.size();i++) if(find(x)!=find(V[i].second)) addedge(x,V[i].second);
	int ans=getcenter(x).first;
	tot=tmp[0];for(int i=1;i<maxn;i++) head[i]=tmp[i];
	for(int i=1;i<(maxn<<1);i++) nxt[i]=tmpnxt[i],ver[i]=tmpver[i];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) Fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int a,b;scanf("%d%d",&a,&b);
		addedge(a,b);
		Fa[find(a)]=find(b);
	}
	for(int i=1;i<=n;i++) if(find(i)==i) V.push_back(getcenter(i));
	int mn=check(1),mnv=1;
	for(int i=2;i<=n;i++)
	{
		int x=check(i);
		if(x<mn) mn=x,mnv=i;
	}
	cout<<mn<<endl;
	for(int i=0;i<(int)V.size();i++) if(find(mnv)!=find(V[i].second)) printf("%d %d\n",mnv,V[i].second);
}
```

---

## 作者：syk666 (赞：4)

首先我们需要知道两个结论：

**结论 1 ：两个树相连使直径最短，必然连接两棵树直径的中点。**

不那么严谨的证明：

连接两棵树，那么新树的直径可能来自：

树 $1$ 的最长链+次长链，树 $2$ 的最长链+次长链，树 $1$ 中的最长链+树 $2$ 中的最长链。

前面两部分显然无法改变，但第三部分我们可以使其尽量小。

则显然选取直径的中点可以满足如上需求。

**结论 $2$ ：最后连接一定呈菊花图状。**


反证法：

假设下图是最优的

![](https://cdn.luogu.com.cn/upload/image_hosting/i59z2h28.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其中三角形代表每一棵树，圆形代表我们之前选出的直径中点。

那么一定可以做到如图 $2$ 更优。


![图极草](https://cdn.luogu.com.cn/upload/image_hosting/y6lwjhq6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

则定呈现菊花图状。

那么问题来了，怎么确定菊花图的根呢？

然后发现 $n$ 才 $1000$ ，所以直接枚举即可。

时间复杂度 $O(n^2)$。

代价如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2008;
const int M=2e5;
int n,m;
int d[N];
int now[M],to[M],pre[M],tot=0;
int id[N],num=0,Mid[N];
int a[N];
bool pd=0;
int X[M],Y[M];
int now2[M],to2[M],pre2[M],tot2=0;
int lst=INT_MAX,lst_mid=0;
void add2(int x,int y) {
    tot2++;
    to2[tot2]=y;
    pre2[tot2]=now2[x];
    now2[x]=tot2;
}
void add(int x,int y) {
    tot++;
    to[tot]=y;
    pre[tot]=now[x];
    now[x]=tot;
}
void dfs(int x,int f,int dep,int ID) {
    if(ID!=-1) id[x]=ID;
    d[x]=dep;
    for(int i=now[x]; i; i=pre[i]) {
        int node=to[i];
        if(node==f) continue;
        dfs(node,x,dep+1,ID);
    }
}

void dfs2(int x,int f,int dep) {
    d[x]=dep;
    for(int i=now2[x]; i; i=pre2[i]) {
        int node=to2[i];
        if(node==f) continue;
        dfs2(node,x,dep+1);
    }
}
void get_mid(int x,int f,int dep,int y,int wh) {
    a[dep]=x;
    if(x==y) {
        Mid[wh]=a[(dep+1)/2];
        return ;
    }
    for(int i=now[x]; i; i=pre[i]) {
        int node=to[i];
        if(node==f) continue;
        get_mid(node,x,dep+1,y,wh);
    }
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m; i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
        X[i]=x,Y[i]=y;
    }
    for(int i=1; i<=n; i++) {
        if(id[i]) continue;
        num++;
        if(!id[i]) {
            memset(d,0,sizeof(d));
            dfs(i,0,0,num);
            int tmp=i;
            for(int j=1; j<=n; j++)
                if(d[j]>d[tmp])
                    tmp=j;
            memset(d,0,sizeof(d));
            dfs(tmp,0,0,-1);
            int tmp2=i;
            for(int j=1; j<=n; j++)
                if(d[j]>d[tmp2])
                    tmp2=j;
            get_mid(tmp,0,1,tmp2,num);
        }
    }
    for(int i=1; i<=num; i++) {
        tot2=0;
        memset(now2,0,sizeof(now2));
        for(int j=1; j<=m; j++) {
            add2(X[j],Y[j]);
            add2(Y[j],X[j]);
        }
        for(int j=1; j<=num; j++) {
            if(i==j) continue;
            add2(Mid[i],Mid[j]);
            add2(Mid[j],Mid[i]);
        }
        memset(d,0,sizeof(d));
        dfs2(Mid[i],0,0);
        int tmp=Mid[i];
        for(int j=1; j<=n; j++)
            if(d[j]>d[tmp])
                tmp=j;
        memset(d,0,sizeof(d));
        dfs2(tmp,0,0);
        int ans=0;
        for(int j=1; j<=n; j++) 
            ans=max(ans,d[j]);
        if(ans<lst) {
            lst=ans;
            lst_mid=i;
        }
    }
    cout<<lst<<endl;
    for(int i=1; i<=num; i++) {
        if(i==lst_mid) continue;
        cout<<Mid[i]<<" "<<Mid[lst_mid]<<endl;
    }
    return 0;
}

```












---

## 作者：YFF1 (赞：2)

## 思路：
首先根据贪心策略，我们知道最后的结果是由每棵树的直径共同决定的。因此，我们把每棵树的直径的重点当作它的根，然后再次贪心，把选择一棵直径最长的树，把它的根和其他树的根项链，最后再求一边全部树的直径即可。
## 难点分析：
贪心策略；树的直径的求法；菊花图。
## 代码：
树的直径模板：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,y,pos=1,d[200005];
vector<int>g[200005];
void dfs(int u,int fa){
	d[u]=d[fa]+1;
	if(d[u]>d[pos])pos=u;
	for(int i:g[u]){
		if(i!=fa)dfs(i,u);
	}
}
signed main () {
	cin>>n;
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	dfs(pos,0);
	cout<<d[pos]-1;
	return 0;
}
```
本题代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
int t,n,m,x,y,fa[1005],d[1005],pos,len[1005],cen[1005],cnt,s,maxa=-1e9;
vector<int>g[200005];
vector<pii>ans;
bool vis[200005];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}//每棵树的分类 
void dfs(int u,int fa){
	d[u]=d[fa]+1;
	if(d[u]>d[pos])pos=u;
	for(int i:g[u]){
		if(i!=fa)dfs(i,u);
	}
}//求直径 
void get(int u,int fa,int halflen){
	if(d[u]-1==halflen){
		cnt=u;
		return ;
	}
	for(int i:g[u]){
		if(i!=fa)get(i,u,halflen);
	}
}//求中点 
signed main () {
	cin>>n>>m; 
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
		fa[find(x)]=find(y);
	}
	for(int i=1;i<=n;i++){
		if(!vis[find(i)]){
			vis[find(i)]=1;
			pos=find(i);
			dfs(find(i),0);
			dfs(pos,0);
			len[find(i)]=d[pos]-1;//len是每棵树的直径 
			cnt=find(i);
			get(pos,0,len[find(i)]/2);
			cen[find(i)]=cnt;//每棵树的直径的中点 
			if(len[find(i)]%2==0)x=len[find(i)]/2;
			else x=len[find(i)]/2+1;//直径长度的奇偶性需要分类讨论，但是长度为奇数时选择两个点作为根都是一样的 
			if(x>maxa){
				maxa=x;
				s=cen[find(i)];
			} 
		} 
	} //找每棵树直径的中点 ,s是所有树的根集中的那一点 
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[find(i)]){
			vis[find(i)]=1;
			if(cen[find(i)]!=s){
				g[cen[find(i)]].push_back(s);
				g[s].push_back(cen[find(i)]);
				ans.push_back({s,cen[find(i)]});//连每棵树的根，并记录答案 
			}
		}
	} 
	pos=1;
	dfs(1,0);
	dfs(pos,0);//再次求直径 
	cout<<d[pos]-1<<endl;
	for(pii i:ans)cout<<i.first<<" "<<i.second<<endl;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1092E)
## 思路
这题非常简单，但也非常烦，调了我 $\verb!1h!$。

首先，我们需要知道一个显然的结论：我们连接的是每颗树直径的中点。这个结论非常好证，不再展开。

接下来，我们不妨设每棵树的直径被分成了 $x_i$ 和 $y_i$ 两部分，显然这两部分要尽可能接近。接下来又有一个问题：我们从哪棵树的直径中点开始连。

另一个显然的贪心思路是：从 $\max(x_i,y_i)$ 最大的那个 $i$ 开始连。

因为从那个点开始连，只有它本身的 $x_i,y_i$ 是不变的，另外树的 $x_i,y_i$ 都变成了 $x_i+1,y_i+1$。

然后建出图，再跑一遍直径即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e3+10;
int maxx1[N],maxx2[N],dep[N],vs[N],cnt,flag[N],pre[N],vis[N];
vector<int>a[N];vector< pair<int,int> >answer;
inline void dfs(int x,int fa){
    vis[x]=1;
    for (auto v:a[x]){
        if (v==fa) continue;
        pre[v]=x;dep[v]=dep[x]+1;
        dfs(v,x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    int nowm=-1,nowmi;
    while (m--){
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i=1;i<=n;++i){
        if (vis[i]) continue;
        for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
        dfs(i,-1);vector<int>now,now1;
        int maxn=0,maxni=i;
        for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
        int x=maxni;
        for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
        dfs(maxni,-1);
        maxn=0,maxni=i;
        for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
        x=maxni;
        while (x) now1.push_back(x),x=pre[x];
        reverse(now1.begin(),now1.end());
        for (auto i:now1) now.push_back(i);
        maxx1[++cnt]=(now.size()-1)/2;
        maxx2[cnt]=(now.size()-1)-((now.size()-1)/2);
        flag[cnt]=now[(ceil(now.size()/2.0))-1];
        if (max(maxx1[cnt],maxx2[cnt])>nowm) nowm=max(maxx1[cnt],maxx2[cnt]),nowmi=cnt;
    }
    for (int i=1;i<=cnt;++i){
        if (i==nowmi) continue;
        a[flag[nowmi]].push_back(flag[i]);
        a[flag[i]].push_back(flag[nowmi]);
        answer.push_back({flag[nowmi],flag[i]});
    }
    for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
    dfs(1,-1);vector<int>now,now1;
    int maxn=0,maxni=1;
    for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
    int x=maxni;
    for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
    dfs(maxni,-1);
    maxn=0,maxni=1;
    for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
    cout<<maxn<<'\n';
    for (auto i:answer) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}
```


---

## 作者：Yang_YL (赞：0)

### 扯淡

这里看到很多题解是 $O(n^2)$ 的，所以为什么要枚举生成树的根。其实可以不用枚举，$O(n)$ 通过这道题。

## 思路

题目中要求将每一个树连接起来，为了最终生成树的直径最小，肯定是将**每一个树直径的中点**按照**菊花图**的形状连接。

证明：

- 如果和其他树进行连接的节点不是这个树的直径的中点（直径是奇数就取中间两个节点中的任意一个），这个节点到直径端点的最大距离一定会更大。

- 如果树的形状不是菊花图，一定可以将其压缩为菊花图使法案更优。

最后，可以发现，如果想让最终生成树直径最短，一定会选择初始直径最大的树作为菊花图的根，然后统计答案就可以了。

### 只有萌新才会看的代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,maa=-1,ans[N],kk;
vector<int> v[N],vv;
int d[N],ma,k,vis[N],fa[N];
void dfs(int x,int f){
    if(d[x]>ma){
        ma=d[x];
        k=x;
	}
	fa[x]=f;
    vis[x]=1;
    for(auto y:v[x]){
        if(y==f) continue;
        d[y]=d[x]+1;
        dfs(y,x);
    }	
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			ma=-1;d[i]=0;dfs(i,0);
			ma=-1;d[k]=0;dfs(k,0);
			for(int i=1;i<=ma/2;i++) k=fa[k];
			if(maa<ma) maa=ma,kk=k;
			ans[k]=(ma+1)/2;
			vv.push_back(k);
			// cout<<i<<" "<<ma<<" "<<k<<endl;
		}
	}
	int ma1=0,ma2=0;
	for(auto x: vv){
		if(x!=kk) ans[x]++;
		if(ans[x]>ma1) ma2=ma1,ma1=ans[x];
		else if(ans[x]>ma2) ma2=ans[x];
	}
	printf("%d\n",max(maa,ma1+ma2));
	for(auto x: vv){
		if(x!=kk) printf("%d %d\n",x,kk);
	}
    return 0;
}
//什么，你居然看代码了？看来你真的是萌新
```

---

## 作者：subcrip (赞：0)

不懂为啥 $n\leqslant 1000$，反正本题解 $O(n\log n)$ 过了（雾

首先观察到对于每个连通块，新加入的边应当只与它的一个结点相连，否则是不优的。那么应当选择哪个结点？显然是到其他点的最大距离最小的那个，也就是树的直径中点。

选出了每个连通块的直径中点之后，需要考虑如何将它们连成一棵树。菊花图是最优的，所以枚举菊花图的根，看看哪个的直径最小即可。

Code:

```cpp
void solve() {
    read(int, n, m);
    adj(ch, n);
    for (int i = 0; i < m; ++i) {
        read(int, u, v);
        edge(ch, u, v);
    }
    vector<int> sz(n + 1);
    vector<int> root(n + 1);
    vector<int> roots;
    vector<int> d(n + 1);
    vector<int> head(n + 1);
    auto dfs = [&] (auto dfs, int v, int pa, int rt) -> void {
        sz[v] = 1;
        root[v] = rt;
        for (auto&& u : ch[v]) {
            if (u == pa) continue;
            dfs(dfs, u, v, rt);
            sz[v] += sz[u];
        }
    };
    int far, far_depth;
    auto dfs2 = [&] (auto dfs2, int v, int pa, int depth) -> void {
        if (depth >= far_depth) {
            far_depth = depth;
            far = v;
        }
        for (auto&& u : ch[v]) {
            if (u == pa) continue;
            dfs2(dfs2, u, v, depth + 1);
        }
    };
    int target;
    auto dfs3 = [&] (auto dfs3, int v, int pa, int depth) -> bool {
        bool f = v == far;
        for (auto&& u : ch[v]) {
            if (u == pa) continue;
            f |= dfs3(dfs3, u, v, depth + 1);
        }
        if (f and depth == d[root[v]]) {
            target = v;
        }
        return f;
    };
    multiset<int> ds;
    int x = 0;
    for (int i = 1; i <= n; ++i) {
        if (not root[i]) {
            roots.emplace_back(i);
            dfs(dfs, i, 0, i);
            far = far_depth = 0;
            dfs2(dfs2, i, 0, 0);
            int u = far;
            far = far_depth = 0;
            dfs2(dfs2, u, 0, 0);
            int v = far;
            d[i] = (far_depth + 1) / 2;
            chmax(x, far_depth);
            target = -1;
            dfs3(dfs3, u, 0, 0);
            head[i] = target;
            ds.emplace(d[i]);
        }
    }
    int mn = INF, var_mn = 0;
    for (auto&& i : roots) {
        ds.erase(ds.lower_bound(d[i]));
        int curr = max(x, d[i] + (ds.empty() ? 0 : 1 + *ds.rbegin()));
        if (ds.size() >= 2) {
            chmax(curr, 2 + *ds.rbegin() + *next(ds.rbegin()));
        }
        if (curr < mn) {
            mn = curr;
            var_mn = i;
        }
        ds.emplace(d[i]);
    }
    cout << mn << '\n';
    for (auto&& i : roots) {
        if (i == var_mn) continue;
        cout << head[var_mn] << ' ' << head[i] << '\n';
    }
}
```

---

## 作者：XioasDog (赞：0)

# CF1092E

首先要确定的一点是一定要连每棵树直径的中点，这样可以保证这棵树对其他树的“贡献”最小。

进一步贪心可以发现，应该是以一棵树作为“根”，连接了其他所有的树

再进一步，就会发现这个“根”应该是直径最长的那一棵树（这样才能保证最长的那一条直径最多只会吃到一次连边的贡献）

所以，这个图的连边应该长成这样

![](https://cdn.luogu.com.cn/upload/image_hosting/wdo9ujdv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e3+9;

int n,m,fa[N];
vector <int> G[N];
bool used[N];

int temp,MAX;
void dfs1(int s,int f,int dis=0){
    used[s]=true;
    if(dis>MAX){
        MAX=dis;
        temp=s;
    }
    for(int &v:G[s]){
        if(v==f)continue;
        dfs1(v,s,dis+1);
    }
}
void dfs2(int s,int f=0,int dis=0){
    if(dis>MAX){
        MAX=dis;
        temp=s;
    }
    fa[s]=f;
    for(int &v:G[s]){
        if(v==f)continue;
        dfs2(v,s,dis+1);
    }
}
int mid[N],pmid,root,pe,dia[N];
pair <int,int> e[N];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dia[0]=-1;
    for(int i=1;i<=n;i++){
        if(!used[i]){
            MAX=-1; dfs1(i,0);
            // printf("sta: %d\n",temp);
            int _temp=temp,dis=0;
            MAX=-1; dfs2(temp);
            // printf("end: %d\n",temp);
            if(dis==MAX/2)mid[++pmid]=temp;
            else while(temp!=_temp){
                temp=fa[temp];
                if(++dis==MAX/2){
                    mid[++pmid]=temp;
                    break;
                }
            }
            // printf("MAX: %d\n",MAX);
            dia[pmid]=MAX;
            if(dia[pmid]>dia[root])root=pmid;
        }
    }
    int ans=dia[root];
    for(int i=1;i<=pmid;i++){
        // printf("%d\n",mid[i]);
        if(i==root)continue;
        e[++pe]=make_pair(mid[i],mid[root]);
        for(int j=1;j<=pmid;j++){
            if(i==j||j==root)continue;
            ans=max(ans,((dia[i]+1)>>1)+((dia[j]+1)>>1)+2);
        }
        ans=max(ans,((dia[root]+1)>>1)+((dia[i]+1)>>1)+1);
    }
    printf("%d\n",ans);
    for(int i=1;i<=pe;i++)printf("%d %d\n",e[i].first,e[i].second);
    return 0;
}
// 5 3
// 3 2
// 1 3
// 5 4
```


---

