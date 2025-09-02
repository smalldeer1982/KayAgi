# [COCI 2020/2021 #2] Odasiljaci

## 题目描述

遗憾的是，这将是 Sean 最后一次扮演 James Bond。

他的任务是在一片广阔的沙漠中组网 $n$ 个分散的天线。这片沙漠可以看作一个二维平面。Sean 会将每个天线的发射半径都设置为同一个非负实数 $r$。天线的覆盖范围被定义为：到该天线的距离不超过 $r$ 的所有点的集合。如果两个天线的覆盖范围有公共点，则这两个天线可以直接通信。此外，如果天线 $A$ 能与 $B$ 通信，$B$ 能与 $C$ 通信，那么 $A$ 也可以通过 $B$ 与 $C$ 通信。

Sean 想要让所有天线连成一个网络，即使任意两个天线都可以通信。由于 $M$ 限制了他的花费，而更大的半径意味着更高的成本，Sean 会选择尽可能小的半径 $r$。请你帮他解决这个问题！


## 说明/提示

第二个样例的示意图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/dxxoyzwk.png)

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
2
1 1
2 2```

### 输出

```
0.7071068```

## 样例 #2

### 输入

```
7
2 3
3 4
4 5
0 1
3 1
4 2
1 5```

### 输出

```
1.4142135```

## 样例 #3

### 输入

```
4
2020 20
20 2020
2020 2020
20 20```

### 输出

```
1000.0000000```

# 题解

## 作者：XSS_Worm (赞：4)

## 题意分析
在一个二维坐标系内，有 $n$ 个点，给出了它们的坐标。需要求出一个最小的覆盖半径 $r$，使得各个点能够连接在一起。
## 解法分析
我们可以将整个坐标系抽象为一张图，每一个点是图上的节点，对于任意两个点，建立一条边，边权为它们之间的几何距离。\
为了形成连通块，我们需要求出最小生成树，即让**最大的边权尽可能地小**。因此，我们应当使用 Kruskal 算法，在这张图上求出最小生成树。答案即为最小生成树中**边权最大的边的一半**。
## 代码实现
实现比较简单，细节不多。请看代码。
```cpp
#include <bits/stdc++.h>

#define int long long
using namespace std;
const int N=1005;
int x[N],y[N],fa[N];
struct edge
{
    int a,b;
    long double dst;
}
;
vector<edge> graph;
int n;

bool cmp(edge a,edge b) {
    return a.dst<b.dst;
}
// 并查集
int find(int x) {
    return ((fa[x]==x)?(x):(fa[x]=find(fa[x])));
}

void merge(int x,int y) {
    fa[find(x)]=find(y);
}

//kruskal算法（核心）
void kruskal() {
    long double ans=0;
    int cnt=0;

    for(auto i:graph) {

        if(find(i.a)!=find(i.b)) {
            merge(i.a,i.b);
            ans=max(ans,i.dst);
            cnt++;
        }
        if(cnt==n-1) break;
    }
    cout<<fixed<<setprecision(10)<<ans/2<<endl;
}

signed main() {
    cin>>n;

    for(int i=1;i<=n;i++) {
        cin>>x[i]>>y[i];
    }

    for(int i=1;i<=n;i++) {
        fa[i]=i;

        for(int j=i+1;j<=n;j++) {
            // 计算几何距离
            long long d=(x[j]-x[i])*(x[j]-x[i])+(y[j]-y[i])*(y[j]-y[i]);
            long double dst=sqrt(d);
            // 建边
            graph.push_back( {
                i,j,dst
            }
            );
        }
    }
    // 边权排序
    sort(graph.begin(),graph.end(),cmp);
    // 跑一边kruskal
    kruskal();
}
```

---

## 作者：songge888 (赞：2)

### 题意

在二维平面上给你 $n$ 个点的坐标。你需要找到一个最小的半径 $r$，为每个点都画上一个半径为 $r$ 的圆，使得这些圆都联通。

### 题解

注意到 $n \le1000$，可以支持 $O(n^2)$ 的做法。

题目其实等价于，连 $n$ 条边使得整个图联通，其中最长的边是多少。

这样就转换为了最小生成树问题。

最后的答案就是最长的边长的一半（因为一条边是两个点同时连的，半径是边长的一半时，半径的最大值最小）。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define bug cout<<"___songge888___"<<'\n';
using namespace std;
int n;
int fa[1005];
int dis[500005];
int ans;
int cnt;
struct lyl{
    int x,y;
}a[1005];

struct edge{
    int u,v;
    int d;
};
bool operator<(edge x,edge y){
    return x.d<y.d;
}
vector<edge> b; 
int Find(int x){
    if(fa[x]==x){
        return x;
    }
    return fa[x]=Find(fa[x]);
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int dx=a[i].x-a[j].x;
            int dy=a[i].y-a[j].y;
            b.push_back({i,j,dx*dx+dy*dy});
        }
    }
    sort(b.begin(),b.end());
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int tot=0;
    for(auto [u,v,d]:b){
        int fx=Find(u);
        int fy=Find(v);
        if(fx!=fy){
            fa[fx]=fy;
            ans=d;
            tot++;
            if(tot==n-1){
                break;
            }
        }
    }
    cout<<fixed<<setprecision(7)<<sqrt((double)ans)/2.0<<'\n';
    return 0;
}

```

---

## 作者：Aamumatematiikka (赞：1)

### 题目描述

平面上有 $n$ 个格点，我们要以每个格点为圆心作一个半径为 $r$ 的圆，要求在保证所有圆连为一个整体的情况下求 $r$ 的最小值。

### 思路

首先我们需要的是让所有的点互相联通，考虑建一棵树，题目要求要半径尽可能小，半径的大小需要时距离的一半，所以也就是最大距离尽可能得小，跑一遍最小生成树。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1005, M=1000005;
int n, x[N], y[N], head[N], fa[N], cnt0=0;
double ans=0;
struct Edge{
	int u, v;
	double w;
}edge[M];
bool cmp(Edge a, Edge b){
	return a.w<b.w;
}
int find(int u){
	if(fa[u]==u) return u;
	return fa[u]=find(fa[u]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			edge[++cnt0]={i,j,hypot(abs(x[i]-x[j]),abs(y[i]-y[j]))/2};
	sort(edge+1,edge+cnt0+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=cnt0;i++){
		int u=edge[i].u, v=edge[i].v;
		double w=edge[i].w;
		if(find(u)==find(v)) continue;
		fa[find(u)]=find(v), ans=max(ans,w);
	}
	return printf("%.6lf",ans)&0;
}
```

跑了一遍最小生成树，时间复杂度的瓶颈在排序，时间复杂度为 $\mathcal{O}(n\log n)$。

---

## 作者：MonKeySort_ZYczc (赞：1)

好像有原题，也是国外比赛的，记不得了。
## 思路一
### 思路流程
二分+判断联通块。  

先二分出半径 $r$，假如两台天线之间距离小于等于 $2r$（可直接通信）就连边。  
假如图是联通的这个 $r$ 就成立，继续二分。  
判断联通直接并查集又省空间又快。  
注意二分上界应该开到 $\sqrt 2\times10^9$。

时间复杂度：$O(n^2\alpha(n)\log V)$，其中 $\alpha(n)$ 是装了路径压缩并查集的复杂度（反阿克曼函数）。  
[提交记录](https://www.luogu.com.cn/record/226342548)，稍微有点慢。  
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
const db eps=1e-7;
int n,x[1145],y[1145],prt[1145];
int find(int p){return prt[p]==p?p:prt[p]=find(prt[p]);}
inline bool pd(db l)
{
	for(int i=1;i<=n;i++) prt[i]=i;
	int now=n;
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(db((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))<=l*l*4)
			{
				int a=find(i),b=find(j);
				if(a==b) continue;
				prt[a]=b;now--;
			}
		}
	}
	return now==1;
 } 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	db l=eps,r=1.5e9,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(pd(mid)) r=mid;
		else l=mid;
	}
	cout<<fixed<<setprecision(7)<<l;
}

```
## 思路二
### 思路流程
最小生成树。  

考虑与思路一一样的方式连边，边的长度为两天线之间的距离除以二。  
最后要求联通，不难想到最小生成树。  
比较板子，没啥好说的。

（最坏）时间复杂度：$O(n^2(\log n+\alpha (n)))$，明显比思路一快了不少。
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
int n,x[1145],y[1145],prt[1145],tot;db ans;
struct edge
{
	int a,b;db w;
	bool operator<(const edge &x)const{return w<x.w;}
}e[1145140];
int find(int p){return prt[p]==p?p:prt[p]=find(prt[p]);}
inline db dis(int x1,int y1,int x2,int y2)
{
	int p=x1-x2,q=y1-y2;
	return sqrt(db(p*p+q*q));
}
inline void kruskl()
{
	int sum=0;
	for(int i=1;i<=tot;i++)
	{
		int p=find(e[i].a),q=find(e[i].b);
		if(p!=q)
		{
			ans=e[i].w;sum++;
			prt[p]=q;
			if(sum==n-1) break;
		 } 
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++) prt[i]=i;
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) e[++tot].w=dis(x[i],y[i],x[j],y[j])/2,e[tot].a=i,e[tot].b=j;
	sort(e+1,e+tot+1);
	kruskl();
	cout<<fixed<<setprecision(7)<<ans;
}

```
最后提一嘴喜闻乐见的问题：两个思路都要开 ```long long``` 算距离，之前就交了一发 WA 了。  
信任一次 ```sqrt``` 函数，至少这里没爆精度。

---

## 作者：liketaem (赞：0)

# 题意
题意也是很简单，就是找一个距离 $n$，其中 $x \times 2$ 可以将每一个信号塔连接起来，并输出最小的 $n$。

**解释：**

Q：为什么是用 $x \times 2$ 的距离就可以连起来？

A：因为信号在过了两个信号塔距离的一半，就会被另一个信号塔接收到。
![](https://cdn.luogu.com.cn/upload/image_hosting/puu40ohq.png)
**注意：** 不一定要直接相连，可以 $x_1$ 连接 $x_2$，$x_2$ 连接 $x_3$。
# 思路
1. 将每一个信号塔找到离它最近的信号塔找到，将所有信号塔连成一串。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/wug2w7qc.png)
2. 再将每条线段的一半算出来，求出最大值并输出。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
struct node{
	int x, y;
}arr[N];
double dis(node a, node b){
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
struct edge{
	int u, v;
	double d;
}e[N * N];
int cnt;
bool cmp(edge a, edge b){
	return a.d < b.d;
}
int father[N];
void init(){
	for(int i = 1; i < N; i++)father[i] = i;
}
int find(int x){
	if(x != father[x])x = find(father[x]);
	return father[x];
}
bool bing(int a, int b){
	int x = find(a);
	int y = find(b);
	if(x != y){
		father[y] = father[x];
		return 1;
	}
	return 0;
}
double kruskal(int p, int s, int t){
	init();
	double sum = 0;
	int cnt = 0;
	for(int i = 0; i < t; i++){
		if(bing(e[i].u, e[i].v)){
			cnt++;
			sum = max(sum, e[i].d);
			if(cnt == p - 1){
				return sum;
			}
		}
	}
	return 0;
}
int main(){
	int s, q;
	cin >> q;
	for(int i = 1; i <= q; i++){
		cin >> arr[i].x >> arr[i].y;
	} 
	for(int i = 1; i <= q; i++){
		for(int j = i + 1; j <= q; j++){
			e[cnt++] = {i, j, dis(arr[i], arr[j])};
		}
	}
	sort(e, e + cnt, cmp);
	cout << fixed << setprecision(7) << kruskal(q, s, cnt)/2;
	return 0;
}
```

---

## 作者：b__b (赞：0)

题意：找到最短的半径 $r$，使得如果以任意一个点为圆心，半径为 $r$ 画圆，则任意一个圆都与至少一个圆相切或相交。

我们把这些点建成一个图，边的权值就是两个点的几何距离，那么这个问题就变成：找到一个最小值，使得任意两点间都存在一条所有边的权值都不超过这个值（因为如果超过那么圆与圆的关系会变成相离）。

于是我们建一棵最小生成树即可。下面使用 Kruskal 算法。

注：其实并不用建图，只需要存储边即可。
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
int set[1005];
int find(int x) {return set[x] == x ? x : set[x] = find(set[x]);}
struct {int x, y;} txs[1005];
struct p {double dis; int a, b;} bian[1000005];
long long pf(int a) {return a * 1ll * a;}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) set[i] = i;
    for (int i = 0; i < n; ++i) scanf("%d%d", &txs[i].x, &txs[i].y);
    int biannum = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j)
        bian[biannum++] = {sqrt(pf(txs[i].x - txs[j].x) + pf(txs[i].y - txs[j].y)), i, j};
    std::sort(bian, bian + biannum, [] (const p &a, const p &b) -> bool {return a.dis < b.dis;});
    double maxd = -1;
    for (int i = 0, now = 1; now < n; ++i) {
        int tmpa = find(bian[i].a), tmpb = find(bian[i].b);
        if (tmpa != tmpb) set[tmpa] = set[tmpb], maxd = std::max(maxd, bian[i].dis), ++now;
    }
    printf("%.7f", maxd / 2);
}
```
时间复杂度：图中的任意两个点都要建边，时间复杂度约为 $O(n^2)$。Kruskal 算法时间复杂度为 $O(m \log m)$，这道题里面 $m=n^2$，复杂度就是 $O(n^2 \log n^2)$，总复杂度为 $O(n^2 \log n^2)$。

空间复杂度：存储每一个点需要 $O(n)$ 的复杂度，存储每一条边需要 $O(n^2)$ 的复杂度，总复杂度为 $O(n^2)$。

---

## 作者：Restart_Justin (赞：0)

## 解法
第一眼感觉是二分，第二眼 MST 板子。

我们暴力连边，每两个点连一条边权为两点距离的边。然后跑一遍 Kruskal，计算最小生成树中最大的边权再除以 $2$（因为有两个圆可以平分距离）。

然后就做完了？

有几个要注意的点：
- 边权开 double。
- 输出注意精度（我在代码里保留了 $10$ 位小数，当然只用保留 $7$ 位就可以了）。
- 十年 OI 一场空，__________________（计算距离时开 long long）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n, m, x[maxn], y[maxn], fat[maxn];
struct node {
    int u, v;
    double w;
    bool operator<(node oth) const {
        return w < oth.w;
    }
} G[maxn * maxn];
void init() {
    for (int i = 1; i <= n; i++)
        fat[i] = i;
}
int find(int x) {
    return fat[x] == x ? x : fat[x] = find(fat[x]);
}
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y)
        fat[x] = y;
}
double dis(int ax, int ay, int bx, int by) {
    return sqrt(1LL * (ax - bx) * (ax - bx) + 1LL * (ay - by) * (ay - by));
} // 开 long long，不开 long long 只有 42pts
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    init();
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            G[++m] = {i, j, dis(x[i], y[i], x[j], y[j])};
    sort(G + 1, G + m + 1);
    double mx = 0;
    for (int i = 1; i <= m; i++)
        if (find(G[i].u) != find(G[i].v)) {
            merge(G[i].u, G[i].v);
            mx = max(mx, G[i].w);
        }
    cout << fixed << setprecision(10) << mx / 2;
}
```
[不开 long long 的评测记录](https://www.luogu.com.cn/record/226764577)

[AC 记录](https://www.luogu.com.cn/record/226768435)

---

## 作者：Xiaoshangjie (赞：0)

### 题外话
初看这道题，还以为只是一个单纯的数学题，当我看到算法标签“生成树”“二分”“并查集”“连通块”时，我承认我蒙了，不过好在写出来了。

### 题意
给定平面上 $n$ 个天线的坐标位置，需要找到一个最小的半径 $r$，使得以每个天线为中心、半径为 $r$ 的圆形区域能够形成连通的网络（即任意两个天线之间可以通过这些圆形区域的交集连通）。最终输出这个最小半径。

### 思路
首先，请您了解最基本的勾股定理：  
对于  $\text{Rt} \triangle ABC$，认为 $\angle A$ 的对边是 $a$，$\angle B$ 的对边是 $b$，$\angle C$ 的对边是 $c$。若 $\angle C=90°$，则有
$$a^2+b^2=c^2$$
或者
$$c=\sqrt{a^2+b^2}$$
由此，我们可以推出平面直角坐标系上两点 $P(x_1,y_1)$ 和 $Q(x_2,y_2)$ 之间的距离是
$$l=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$
请确认您已知晓再往下读，这很重要。

考虑使用 Prim 来进行最小生成树，这样在回答时取得的也是最小值。

**首先是定义与初始化：**
- $md$ 数组——记录各点到当前生成树的最小距离，初始设为极大值（$10^{18}$）。
- $v$ 数组——记录每个点是否已经加入了最小生成树中。
- 将最开始的索引 $0$ 的 $md$ 数组记为 $0$，即以 $0$ 号点为根生成树。

**接下来是 Prim 算法的主要部分：**（会的可以跳过）
1. 每次循环找出**未加入**生成树的点中距离最近的点 $u$；
2. 将 $u$ 标记为已加入生成树；
3. 更新当前生成树中的最大边 $m$（很重要，要考的）；
4. 用 $u$ 更新其他未加入点的最小距离，循环往复，直到 $n$ 个点均加入最小生成树停止。

总觉得少了点什么？  
没错，我们还并没有正确的方法存储每个点之间的**距离**，也就无法最小生成树。  
还记得一开始讲的公式吗？我们可以开一个结构体 $P$ 存储每个点的横纵坐标，这样就可以用公式计算距离了。

**最后输出答案：**  
我们之前在生成树时记录了最长距离 $m$，答案所需的**半径** $r$ 就是最长边 $m$ 的一半，即 $r=\dfrac{m}{2}$。  
记得保留至少 $6$ 位小数哦！这边建议保留样例中的 $7$ 位。

时间复杂度是 $O(n^2)$，不会超时。

### code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct P
{
    int x,y;
}p[1005];
double d(P a,P b)//公式
{
    double dx=a.x-b.x, dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
    
    double md[1005],m=0;
    bool v[1005]={0};
    for(int i=0;i<n;i++) md[i]=1e18;
    md[0]=0;
    for(int c=0;c<n;c++)//最小生成树模板
    {
        int u=-1;
        for(int i=0;i<n;i++)
            if(!v[i] && (u==-1 || md[i]<md[u])) u=i;
        v[u]=1;
        if(md[u]>m) m=md[u];
        for(int i=0;i<n;i++)
        {
            double t=d(p[u],p[i]);
            if(!v[i] && t<md[i]) md[i]=t;
        }
    }
    
    printf("%.7f\n",m/2);//保留小数
    return 0;
}
```

---

## 作者：Eden_star (赞：0)

## 省流
没有卫星电话版的[ P1991](https://www.luogu.com.cn/problem/P1991)。
## 思路
根据观察可以发现，两个基站发射信号的圆相切能使发射半径最小，而两个园的半径长度之和为两个基站连线的长度。
而半径最短的长度为两个基站连线的长度的一半。

所以可以将基站两两相连，把基站抽象成点，连线抽象成边，求最小生成树的最长边的一半就可以了。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int ans;
int n,m,k,cnt;
double leb;
int fa[N];
double _x[N],_y[N];
struct G{
	int u,ne;
	double w;
}pic[2*N];
int find(int );
bool cmp(G ,G );
bool fx(int ,int );
void add(int ,int ,double );
double js(double ,double ,double ,double );
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>_x[i]>>_y[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j) add(i,j,js(_x[i],_x[j],_y[i],_y[j]));
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	sort(pic+1,pic+1+cnt,cmp);
	int tot=0;
	for(int i=1;i<=cnt;i++){
		if(tot==n-1) break;
		int x=pic[i].u;
		int y=pic[i].ne;
		if(fx(x,y)){
			tot++;
			leb=pic[i].w;
		}
	}
	printf("%.10lf",leb/2);
	return 0;
}
bool cmp(G x,G y){
	return x.w<y.w;
}
void add(int u,int v,double w){
	pic[++cnt].u=u;
	pic[cnt].ne=v;
	pic[cnt].w=w;
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
bool fx(int x,int y){
	int nx=find(x);
	int ny=find(y);
	if(nx==ny) return false;
	else{
		fa[nx]=fa[ny];
		return true;
	}
}
double js(double a,double b,double c,double d){
	return sqrt(pow(a-b,2)+pow(c-d,2));
}
```

---

## 作者：yihang2011 (赞：0)

### [P13427 [COCI 2020/2021 #2] Odasiljaci](https://www.luogu.com.cn/problem/P13427)

最小生成树 Kruskal 板子题。

每个点与其他 $n - 1$ 个点分别连边就建图，边权为两点之间的距离，公式为 $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$。然后通过 Kruskal 找出最小生成树中的最大边权，这就是每个点所在圆最大半径的两倍，即这个最大边权除以 $2$ 即可。

注意开 `double`，以及由于误差不超过 $10^{-6}$，所以输出保留 $7$ 位小数。

时间复杂度瓶颈在建图，为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define seta(f, x) memset(f, x, sizeof f)
using ll = long long;
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0', ch = getchar();
    }
    return x * f;
}
#define rd read()
void write(ll x) {
    if (x < 0) {
        putchar('-'), x = -x;
    } 
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
#define wln(x) write(x); putchar('\n');
#define wt(x) write(x); putchar(' ');
#define db(x) printf(#x); putchar(':'); wln(x);

const int N = 1e3 + 10, M = 1e6 + 10;
struct node {
    int u, v;
    double w;
    node() {}
    node(int u, int v, double w) : u(u), v(v), w(w) {}
} g[M];
int n, m;
int f[N], _x[N], _y[N];
double mx;

int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

double dist(int x, int y) {
    return sqrt(1.0 * (1ll * (_x[x] - _x[y]) * (_x[x] - _x[y]) + 1ll * (_y[x] - _y[y]) * (_y[x] - _y[y])));
}

int main() {
    n = rd;
    for (int i = 1; i <= n; i++) {
        _x[i] = rd, _y[i] = rd;
        for (int j = 1; j < i; j++) {
            g[++m] = node(i, j, dist(i, j));
        }
        f[i] = i;
    }
    sort(g + 1, g + m + 1, [](node x, node y) {
        return x.w < y.w;
    }) ;
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int x = find(g[i].u), y = find(g[i].v);
        if (x != y) {
            f[x] = y;
            mx = max(mx, g[i].w);
            tot++;
        }
        if (tot == n - 1) {
            break ;
        }
    }
    printf("%.7lf", mx / 2);
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/226499859)

---

## 作者：zzhbpyy (赞：0)

容易想到二分答案。先预处理出任意两点间的距离，check 时使用 BFS 判断从 $1$ 出发是否所有点都可达。check 的复杂度为 $O(n^2)$，总复杂度 $O(n^2\log n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
int n,x[1005],y[1005];
double dis[1005][1005];
bool vis[1005];
inline bool check(double x){
	memset(vis,0,sizeof vis);
	queue<int>q;
	q.push(1);vis[1]=true;
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			if(dis[u][i]<=2*x){
				vis[i]=true;
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])return false;
	}
	return true;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j]));//*1.0转成浮点数，避免爆int
		}
	}
	double l=0,r=1000000000;
	while(r-l>1e-7){
		double mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	cout<<fixed<<setprecision(9)<<l;
}
```

---

