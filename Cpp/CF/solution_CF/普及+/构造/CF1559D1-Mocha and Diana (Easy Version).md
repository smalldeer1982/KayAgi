# Mocha and Diana (Easy Version)

## 题目描述

给你两棵森林，节点数均为 $n$。

允许你进行加边操作，但是有两个要求：

- 如果在第一个森林加一条 $(u,v)$ 的边，第二个森林也要进行同样的操作。反之同理。
- 加边后两个森林依旧是森林。（一棵树也是森林）

求最多能加几条边，并输出加边方案。

## 样例 #1

### 输入

```
3 2 2
1 2
2 3
1 2
1 3```

### 输出

```
0```

## 样例 #2

### 输入

```
5 3 2
5 4
2 1
4 3
4 3
1 4```

### 输出

```
1
2 4```

## 样例 #3

### 输入

```
8 1 2
1 7
2 6
1 5```

### 输出

```
5
5 2
2 3
3 4
4 7
6 8```

# 题解

## 作者：KaisuoShutong (赞：10)

## CF1559D1 Mocha and Diana (Easy Version)
[加强版题解](https://www.luogu.com.cn/blog/Criticism/solution-cf1559d2)

### 题意
两片森林，都有一些初始边。求以下操作的最多次数，使得图中无环，并输出方案。  
操作：选择 $x,y$，在两片森林中分别连边。  
$n\leq1000$。

### 题解
算法：枚举 $\forall i,j$，判断是否能够合并，最后输出答案。  
用并查集实现的时间复杂度是 $O(n^2\times\alpha)$ 的。

正确性证明：  
从过程态考虑或许会有些麻烦，我们直接考虑最终态。

> lemma. 最终态的两片森林中一定有至少一片是一颗树。

> 证明：  
若第一片森林中只有一棵树，原命题得证。  
故不妨设第一片森林有至少两颗树，设为 $A$ 和 $B$。考虑其中任意两个点 $a\in A$，$b\in B$。  
若 $a$ 与 $b$ 在第二片森林中不属于同一棵树，那么可以再连边 $(a,b)$，与最终态定义矛盾。  
故对于 $a\in A$，其与 $B$ 中所有点皆属于同一棵树。由此可得，$A$ 与 $B$ 在第二片森林中属于同一棵树。  
同理可得，$A$ 中所有点在 $B$ 中皆属一棵树，原命题得证。

由此可知，无论使用什么样的顺序，最终状态的加边数都是一样的。

点个赞吧。

```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 100010;
int n,m1,m2,ans,a[maxn],f[maxn],g[maxn];vector<pair<int,int> >q;
int GF(int x) {return f[x]==x?x:f[x]=GF(f[x]);}
int gf(int x) {return g[x]==x?x:g[x]=gf(g[x]);}
signed main() {
	n=read(),m1=read(),m2=read();
	for(int i=1;i<=n;i++) f[i]=g[i]=i;
	for(int i=1;i<=m1;i++) f[GF(read())]=GF(read());
	for(int i=1;i<=m2;i++) g[gf(read())]=gf(read());
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) if(GF(i)^GF(j)&&gf(i)^gf(j)) {
			f[f[i]]=f[j],g[g[i]]=g[j],q.push_back(make_pair(i,j));
		}
	cout<<q.size()<<'\n';
	for(auto y:q) cout<<y.first<<' '<<y.second<<'\n';
	return 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
给定两个森林，每次可以选定 $u$ 和 $v$，使得在两个森林中连上 $u$ 和 $v$ 后仍是森林，连上这条边，问最多能连多少边，并输出一种方案。这里是 Easy Version，唯一的区别就是 $1\le n\le 1000$。
# 题目分析
贪心，枚举每条边，能连就连。首先这样肯定是合法且复杂度正确的，需要证明正确性。如果存在一种方案使得答案比这种方案大，那么一定是因为这种贪心连某条边时使本来对应两条边或更多的可能没有了。形式化地描述，存在四个点 $a,b,c,d$，$a$ 和 $b$ 连边导致本来 $a$ 和 $c$、$b$ 和 $d$ 连边行不通。由于贪心有边就连，这样一定是因为 $a$ 和 $c$ 直接或间接连过边，于是 $a$ 和 $c$ 便不能连边，$b$ 和 $d$ 同理，正确性得到证明。这里便可以使用并查集暴力维护。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,m[2],x,y,father[2][100001],ans;
pii res[100001];
I int find(int op,int x)
{
	return x==father[op][x]?x:father[op][x]=find(op,father[op][x]);
}
int main()
{
	n=read();
	m[0]=read();
	m[1]=read();
	for(R int i=1;i<=n;++i)
		father[0][i]=father[1][i]=i;
	for(R int i=1;i<=m[0];++i)
	{
		x=read();
		y=read();
		father[0][find(0,y)]=father[0][find(0,x)];
	} 
	for(R int i=1;i<=m[1];++i)
	{
		x=read();
		y=read();
		father[1][find(1,y)]=father[1][find(1,x)];
	} 
	for(R int i=1;i<n;++i)
		for(R int j=i+1;j<=n;++j)
		{
			int xf=find(0,i),xs=find(1,i),yf=find(0,j),ys=find(1,j);
			if(xf!=yf&&xs!=ys)
			{
				father[0][yf]=xf;
				father[1][ys]=xs;
				++ans;
				res[ans]=mp(i,j);
			}
		}
	putint(ans);
	for(R int i=1;i<=ans;++i)
		printf("%d %d\n",res[i].first,res[i].second);
	return 0;
}
```


---

## 作者：Interstellar_Zhou (赞：1)

本题我们可以考虑 O($n^2$) 地枚举两个结点，然后尝试将其连接。但我们如何说明不同的顺序遍历出的树的边数相同？验证如下：
![](https://img-blog.csdnimg.cn/216d7b65dce841acb59b795bb71ee6f9.png)
假设红框和蓝框代表某个森林中的某两颗树，那么易知两个红色结点连通、两个蓝色结点连通（树的基本性质）。此时，我们若连黄边，则其它连接两棵树的边一定连不上，否则将产生环。同样的，如果连绿边的话其它边也自然连不上（包括黄边），所以到头来只能连一条边，故顺序不影响最终结果。

那我们便可以放心大胆地去枚举了。但是怎么判环？我们可以用两个并查集来维护两个森林就行了。

代码实现：
```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e3 + 100;
int n, m1, m2, fa1[MAXN], fa2[MAXN], cnt, Print[MAXN][2];

void init() { for(int i=1; i<=n; i++) fa1[i] = fa2[i] = i; }
int find1(int x) { return x==fa1[x]?x:fa1[x]=find1(fa1[x]); }
void unite1(int x, int y) { x = find1(x), y = find1(y); if(x == y) return; fa1[y] = x; }
bool same1(int x, int y) { return find1(x) == find1(y); }
int find2(int x) { return x==fa2[x]?x:fa2[x]=find2(fa2[x]); }
void unite2(int x, int y) { x = find2(x), y = find2(y); if(x == y) return; fa2[y] = x; }
bool same2(int x, int y) { return find2(x) == find2(y); }

int main() {
    cin >> n >> m1 >> m2;
    init();
    for(int i=1, u, v; i<=m1; i++) {
        cin >> u >> v;
        unite1(u, v);
    }
    for(int i=1, u, v; i<=m2; i++) {
        cin >> u >> v;
        unite2(u, v);
    }
    for(int i=1; i<=n; i++) {
        for(int j=i+1; j<=n; j++) {
            if(!same1(i, j) && !same2(i,  j)) {
                cnt ++;
                unite1(i, j), unite2(i, j);
                Print[cnt][0] = i, Print[cnt][1] = j;
            }
        }
    }
    cout << cnt << endl;
    for(int i=1; i<=cnt; i++) {
        cout << Print[i][0] << " " << Print[i][1] << endl;
    }
    return 0;
}
```


---

## 作者：sunzz3183 (赞：1)

# CF1559D1 Mocha and Diana (Easy Version)

## 题意

给定两个有相同点的森林，你要在两个森林里尽量多的加入端点相同的边，并使得还是两个森林还是森林（即不能出现环）。

## 思路

看题： $n\leq1000$ ，我们发现  $O(n^2\log n)$ 就可以过。

所以，加边时只需要 $O(n^2)$ 暴力枚举两个端点即可。

那加边时如何 $O(\log n)$ 判断不会形成环呢？这就用到了并查集。因为我们可以发现，他就是给了你一个没有完全生成完的最小生成树，然后你要继续生成树。我们自然而然的就想到了 Kruskal  中的并查集。

我们把同一棵树上的点并入一个并查集，然后每次加边判断两点是否在一个并查集中，在的话就在并入一个并查集，并输出这两点。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int f1[N],f2[N],a[N*10],b[N*10];
int n,m1,m2,sum;
int find1(int v){
	if(f1[v]==v)
		return v;
	return f1[v]=find1(f1[v]);
}
void merge1(int a,int b){
	f1[find1(a)]=find1(b);
}
int find2(int v){
	if(f2[v]==v)
		return v;
	return f2[v]=find2(f2[v]);
}
void merge2(int a,int b){
	f2[find2(a)]=find2(b);
}
int main(){
	sum=0;
	cin>>n>>m1>>m2;
	for(int i=1;i<=n;i++)
		f1[i]=f2[i]=i;
	while(m1--){ 
		int a,b;
		cin>>a>>b;
		merge1(a,b);
	}
	while(m2--){ 
		int a,b;
		cin>>a>>b;
		merge2(a,b);
	}
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(find1(i)!=find1(j)&&find2(i)!=find2(j))
				a[++sum]=i,b[sum]=j,merge1(i,j),merge2(i,j);
	cout<<sum<<"\n";
	for(int i=1;i<=sum;i++)
		cout<<a[i]<<" "<<b[i]<<"\n";
	return 0;
}
```



---

## 作者：HerikoDeltana (赞：1)

# CF1559D1 Mocha and Diana (EZ Ver)

作为 EZ 还是挺简单的。

## 题意简述

现有两个森林，问你在保证存在两个森林的情况下，最多还能连接哪些点。

EZ 的数据范围为 $n \le 1000$。

## 思路简述

题目的最终要求就是让我们在保证仍存在两个连通块的情况下，尽可能多的连边。

因为 EZ 的数据范围比较小，于是我们可以直接 $O(n^2)$ 的去枚举两点去判断可不可以连接，考虑使用并查集来维护连通块。

## Code

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
using namespace std;

template<typename J>
I void fr(J &x)
{
    short f(1);
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    x=(x<0?putchar('-'),-x:x);
    static short stak[35];
    short top(0);
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    if(k) putchar('\n');
    else putchar(' ');
}

CI MXX=1005;

int n;

struct UFS
{
    int fa[MXX];

    I void Pre() {for(R int i(1);i<=n;++i) fa[i]=i;}

    I int Find(int x)
    {
        if(x!=fa[x]) fa[x]=Find(fa[x]);
        Heriko fa[x];
    }

    I void Uni(int x,int y){fa[x]=y;}
}

u1,u2;

int m1,m2,x,y;

vector< pair< int , int > > ans;

S main()
{
    fr(n),fr(m1),fr(m2);
    u1.Pre(),u2.Pre();
    for(R int i(1);i<=m1;++i) fr(x),fr(y),u1.Uni(u1.Find(x),u1.Find(y));
    for(R int i(1);i<=m2;++i) fr(x),fr(y),u2.Uni(u2.Find(x),u2.Find(y));
    for(R int i(1);i<=n;++i)
        for(R int j(1);j<=n;++j)
        {
            int fx1(u1.Find(i)),fx2(u2.Find(i)),fy1(u1.Find(j)),fy2(u2.Find(j));
            if(fx1!=fy1 and fx2!=fy2) u1.Uni(fx1,fy1),u2.Uni(fx2,fy2),ans.push_back(make_pair(i,j));
        }
    fw(ans.size(),1);
    for(R int i(0);i<(int)ans.size();++i) fw(ans[i].first,0),fw(ans[i].second,1);
    Heriko Deltana;
}
```

审核的管理员辛苦了（

---

## 作者：Z1qqurat (赞：0)

先考虑答案上界。如果只有一个森林，那么答案就是 $n - 1 - m$，两棵的话应该是 $\min(n - 1 - m_1, n - 1 - m_1)$。考虑如何达到答案上界，首先不难想到枚举 $i, j$，如果 $i, j$ 在两个森林里面都不联通，那么连 $i, j$，一定可以达到上界（感觉感性理解下比较显然不证了）。复杂度 $\mathcal{O} (n^2 \alpha)$。

考虑怎么优化。选择一个中心点 $s$，将可以和 $s$ 连边的点都连上，那么剩下的有用点只有两种：在森林 $a$ 中与 $s$ 不联通但是在 $b$ 中与 $s$ 联通的点；在森林 $b$ 中与 $s$ 不联通但是在 $a$ 中与 $s$ 联通的点，将这两个集合分别设为 $L, R$。那么 $L, R$ 内的任选各一个点组成的点对一定可以连，取出 $\min(|L|, |R|)$ 个点对即可。注意将一个点加入 $L$ 或 $R$ 是要将这个点在 $a$ 或 $b$ 中与 $s$ 连上边。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 5;
int n, m1, m2;
vector <int> L, R;

struct DSU{
    int fa[N];
    void init() {
        for (int i = 1; i <= n; ++i) fa[i] = i;
    }
    int getfa(int x) {
        return fa[x] == x ? x : fa[x] = getfa(fa[x]);
    }
    void merge(int x, int y) {
        fa[getfa(x)] = getfa(y);
    }
} a, b;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m1 >> m2; a.init(), b.init();
    for (int i = 1, u, v; i <= m1; ++i) {
        cin >> u >> v, a.merge(u, v);
    }
    for (int i = 1, u, v; i <= m2; ++i) {
        cin >> u >> v, b.merge(u, v);
    }
    cout << n - 1 - max(m1, m2) << "\n";
    for (int i = 2; i <= n; ++i) {
        if(a.getfa(i) != a.getfa(1) && b.getfa(i) != b.getfa(1)) {
            cout << 1 << ' ' << i << "\n";
            a.merge(1, i), b.merge(1, i);
        }
    }
    for (int i = 2; i <= n; ++i) {
        if(a.getfa(i) != a.getfa(1)) L.emplace_back(i), a.merge(1, i);
        else if(b.getfa(i) != b.getfa(1)) R.emplace_back(i), b.merge(1, i);
    }
    for (int i = 0; i < min(L.size(), R.size()); ++i) cout << L[i] << ' ' << R[i] << "\n";
    return 0;
}

---

## 作者：wyl13479387613 (赞：0)

题意：给你两个相互 **独立** 的图，两个图之间的关系是：包含相同顶点个数（顶点的个数和编号均相同），边数不同（数量，关系均不同）

然后让你在两幅图里面同时连边，连的边需要满足的条件是：

1、在两幅图里面的编号一致

2、连完之后两幅图中均无环

问你最大能连多少条边。

题意很明确，图中的限制就是每次连边要在两幅图里面连**相同**的边，而且连完之后不能成环。

不能成环的限制其实就是，如果原本两点之间有能够直接或者间接到达的边的话，那就不能连这两个点，否则就会成环。换句话说就是，不能把同一个连通块里的边连起来，否则就会成环。

所以我们可以建立两个并查集，分别维护两个图内的点的连通性。

由于数据范围比较小，可以考虑暴力枚举任意两点。

在枚举的时候，分别判断一下这两点在两个图中的连通性（就是用上述的并查集），如果二者原来在两个图中均不连通，那就满足条件，否则不满足条件。

核心代码：

```cpp
for(int i=1;i<=n;i++)
 for(int j=i+1;j<=n;j++)
 {
	 int a1=find1(i),b1=find1(j),a2=find2(i),b2=find2(j);
	  	
	 if(a1!=b1&&a2!=b2)
	 {
	  	temp[++cnt]={i,j};
	  		
	  	p1[a1]=b1;
	  	p2[a2]=b2;
	 }
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
#define out1(x) printf("%d\n",x);
#define out2(x,y) printf("%d %d\n",x,y);
#define out3(x,y,z) printf("%d %d %d\n",x,y,z);
#define out4(x,y,z,k) printf("%d %d %d %d\n",x,y,z,k);
#ifdef LOCAL
FILE*FP=freopen("input.txt","r",stdin);
#endif
using namespace std;
typedef long long LL;
typedef pair<int,int>PII;
typedef pair<double,double>PDD;

const int N=2e5+10,M=2*N,mod=1e9+7,INF=1e9,esp=1e-8;

int p1[N],p2[N];

int n,m1,m2;

int find1(int x)
{
	if(x!=p1[x])p1[x]=find1(p1[x]);
	
	return p1[x];
}

int find2(int x)
{
	if(x!=p2[x])p2[x]=find2(p2[x]);
	
	return p2[x];
}

int main() 
{
	scanf("%d%d%d",&n,&m1,&m2);
	
	for(int i=1;i<=n;i++)p1[i]=p2[i]=i;
	
	PII temp[N];
	int cnt=0;
	
	for(int i=1;i<=m1;i++)
	{
		int a,b;
		
		scanf("%d%d",&a,&b);
		
		a=find1(a),b=find1(b);
		
		if(a!=b)
		{
			p1[a]=b;
		}
	}
	
	for(int i=1;i<=m2;i++)
	{
		int a,b;
		
		scanf("%d%d",&a,&b);
		
		a=find2(a),b=find2(b);
		
		if(a!=b)
		{
			p2[a]=b;
		}
	}
	
	for(int i=1;i<=n;i++)
	  for(int j=i+1;j<=n;j++)
	  {
	  	int a1=find1(i),b1=find1(j),a2=find2(i),b2=find2(j);
	  	
	  	if(a1!=b1&&a2!=b2)
	  	{
	  		temp[++cnt]={i,j};
	  		
	  		p1[a1]=b1;
	  		p2[a2]=b2;
		}
	  }
	printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)printf("%d %d\n",temp[i].first,temp[i].second);
	
	return 0;

}
```
~~蒟蒻第一篇洛谷题解~~


---

## 作者：云浅知处 (赞：0)

> 给定两个森林 $G_1=(V,E_1)$ 和 $G_2=(V,E_2)$，点数均为 $n$，边数分别为 $m_1,m_2$。
>
> 每次可以选择两个点 $u,v\in V$，如果：
>
> -  $(u,v)\not\in E_1$ 且 $(u,v)\not\in E_2$
> - 连上边 $(u,v)$ 后， $G_1,G_2$ 均仍为森林
>
> 那么就可以把它们连上，求能连上的边数的最大值。要求输出方案。
>
> $m_1,m_2\le n\le 1000$

注意到如果此时能连上一条边 $(u,v)$ ，那么把它们连上必然不会使答案变差。

因此对于这个 Easy ver. 我们就只需要暴力 $O(n^2)$ 枚举 $u$ 和 $v$，不断加边加边加边，然后加边的时候并查集查询就可以了。

这个复杂度是 $O(n^2\log n)$ 的，$\log $ 来自并查集。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>

#define int long long
const int MN=1e6;

using namespace std;

int _;

vector<int>G1[MN];
vector<int>G2[MN];

int fa[MN],fb[MN];

vector<pair<int,int> >ans;

int finda(int x){return (x==fa[x])?x:(fa[x]=finda(fa[x]));}
int findb(int x){return (x==fb[x])?x:(fb[x]=findb(fb[x]));}

int n,ma,mb;

signed main(void){

    cin>>n>>ma>>mb;
    for(int i=1;i<=n;i++)fa[i]=fb[i]=i;

    for(int i=1;i<=ma;i++){
        int u,v;cin>>u>>v;
        int uu=finda(u),vv=finda(v);
        if(uu!=vv)fa[uu]=vv;
    }
    for(int i=1;i<=mb;i++){
        int u,v;cin>>u>>v;
        int uu=findb(u),vv=findb(v);
        if(uu!=vv)fb[uu]=vv;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int ii=finda(i),jj=finda(j),iii=findb(i),jjj=findb(j);
            if(ii==jj||iii==jjj)continue;
            fa[ii]=jj,fb[iii]=jjj,ans.push_back(make_pair(i,j));
        }
    }

    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++)cout<<ans[i].first<<" "<<ans[i].second<<endl;

    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

观察数据可以发现，输出的第 $1$ 个数字是：

$$\operatorname{min}(n-m_1-1,n-m_2-1)$$

其实，这是因为，根据数的性质，$n=m+1$，所以，$n-m_1-1$ 是摩卡最多连边数，$n-m_2-1$ 是戴安娜最多连边数。

然后，维护 $2$ 个并查集，存储顶点之间的关系，用双层循环暴力搜一遍，即可得到所有答案。

时间复杂度略大，但是可以过简单版本。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 1000
int n;
int ma;
int mb;
int faa[max_n+2];
int fab[max_n+2];
inline int mi(int a,int b){
	return a<b?a:b;
}
int finda(int a){
	if(a==faa[a])return a;
	return faa[a]=finda(faa[a]);
}
int findb(int a){
	if(a==fab[a])return a;
	return fab[a]=findb(fab[a]);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1559D1_1.in","r",stdin);
	freopen("CF1559D1_1.out","w",stdout);
	#endif
	scanf("%d%d%d",&n,&ma,&mb);
	printf("%d\n",mi(n-ma-1,n-mb-1));
	for(int i=1;i<=n;++i){
		faa[i]=fab[i]=i;
	}
	for(int i=1;i<=ma;++i){
		int u;
		int v;
		scanf("%d%d",&u,&v);
		faa[finda(u)]=finda(v);
	}
	for(int i=1;i<=mb;++i){
		int u;
		int v;
		scanf("%d%d",&u,&v);
		fab[findb(u)]=findb(v);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int ifa=finda(i);
			int jfa=finda(j);
			int ifb=findb(i);
			int jfb=findb(j);
			if(ifa!=jfa&&ifb!=jfb){
				faa[ifa]=jfa;
				fab[ifb]=jfb;
				printf("%d %d\n",i,j);
			}
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56080911)

By **dengziyue**

---

## 作者：pomelo_nene (赞：0)

注意到添加的最大边数唯一。于是枚举每一对边，用两个并查集维护两个图中的连通块，能加就加。最后输出方案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct unionFindSet{
	int fa[1005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	void unionSet(int x,int y)
	{
		int xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return ;
		fa[xx]=yy;
	}
}ufs1,ufs2;
#define mp make_pair
int n,m1,m2;
int main(){
	scanf("%d %d %d",&n,&m1,&m2);
	ufs1.makeSet(n);
	ufs2.makeSet(n);
	for(int i=1;i<=m1;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		ufs1.unionSet(u,v);
	}
	for(int i=1;i<=m2;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		ufs2.unionSet(u,v);
	}
	vector<pair<int,int>> Ans;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if(ufs1.findSet(i)!=ufs1.findSet(j) && ufs2.findSet(i)!=ufs2.findSet(j))
			{
				ufs1.unionSet(i,j);
				ufs2.unionSet(i,j);
				Ans.push_back(mp(i,j));
			}
		}
	}
	printf("%d\n",int(Ans.size()));
	for(auto st:Ans)	printf("%d %d\n",st.first,st.second);
	return 0;
}
```

---

