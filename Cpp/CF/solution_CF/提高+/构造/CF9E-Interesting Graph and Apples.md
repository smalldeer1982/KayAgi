# Interesting Graph and Apples

## 题目描述

Hexadecimal likes drawing. She has drawn many graphs already, both directed and not. Recently she has started to work on a still-life «interesting graph and apples». An undirected graph is called interesting, if each of its vertices belongs to one cycle only — a funny ring — and does not belong to any other cycles. A funny ring is a cycle that goes through all the vertices just once. Moreover, loops are funny rings too.

She has already drawn the apples and some of the graph edges. But now it is not clear, how to connect the rest of the vertices to get an interesting graph as a result. The answer should contain the minimal amount of added edges. And furthermore, the answer should be the lexicographically smallest one. The set of edges $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{n},y_{n}) $ , where $ x_{i}<=y_{i} $ , is lexicographically smaller than the set $ (u_{1},v_{1}),(u_{2},v_{2}),...,(u_{n},v_{n}) $ , where $ u_{i}<=v_{i} $ , provided that the sequence of integers $ x_{1},y_{1},x_{2},y_{2},...,x_{n},y_{n} $ is lexicographically smaller than the sequence $ u_{1},v_{1},u_{2},v_{2},...,u_{n},v_{n} $ . If you do not cope, Hexadecimal will eat you. ...eat you alive.

## 样例 #1

### 输入

```
3 2
1 2
2 3
```

### 输出

```
YES
1
1 3
```

# 题解

## 作者：AquaRio (赞：7)

蒟蒻第二次发题解 如果有问题可以私信我 Yosoro~  
~~之前一个大佬的题解似乎出了问题，会T掉。。。并且一个地方似乎也打错了~~  
###### ~~话说这题根本没有蓝题吧~~

------------
# 题目分析
一道挺水的模拟题，似乎用到一点贪心的思想。  
用getfather判环大家应该都会吧，  
注意一下开始时候的初始条件判定，这题还是挺好做的。  
解释什么的都在注释里，直接贴代码吧。
# 温馨提示
num=0;  
a[num++]=1;  
运行的结果是a[0]=1，然后num再+1。  
细节问题一定要注意！
# ~~邪教~~ 代码
```cpp
//ラブライブ！サンシャイン！ //提交前先祈祷一下
//CF9E
#include<bits/stdc++.h>
using namespace std;
int n,m;
int fa[55],e[55][55];//fa用于判断环，e表示有没有边 
int deg[55];//表示度数 
pair<int,int> ans[55];//用ans表示连起来的边，pair储存更方便
int findfather(int x){//找爸爸（雾）
	return fa[x]==x?x:fa[x]=findfather(fa[x]);
}
int main(){
	ios::sync_with_stdio(false);//优化加速 
	cin>>n>>m;
	if(n<m){
		cout<<"NO"<<endl;//如果m比n大显然不行 
		return 0;
	}
	for(int i=1;i<=n;i++) fa[i]=i;//更新父节点
	
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		e[a][b]=e[b][a]=1;
		deg[a]++;
		deg[b]++;
		if(deg[a]>2||deg[b]>2){
			cout<<"NO"<<endl;//输入的时候就判断 
            				 //如果度超过了2，肯定不能成一个大环
			return 0;
		}
		fa[findfather(a)]=fa[findfather(b)];
	}
	int num=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(findfather(i)!=findfather(j)&&deg[i]<2&&deg[j]<2){
				num++;//注意num
				ans[num]=make_pair(i,j);
				deg[i]++;
				deg[j]++;
				fa[findfather(i)]=findfather(j);
			}
		} 
	}
	if(m+num==n-1){//最后一个点可能没有和第一个点连起来 
		num++;
		for(int i=1;i<=n;i++){
			while(deg[i]<2) { //这里要写while 如果只有俩个点 会被hack掉 
				deg[i]++;
				if(!ans[num].first) ans[num].first=i;
				else ans[num].second=i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(findfather(i)!=findfather(1)){
			cout<<"NO"<<endl;
			return 0;
		}
	} 
	cout<<"YES"<<endl<<num<<endl;
	for(int i=1;i<=num;i++){
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}
```


---

## 作者：0xFF (赞：5)

#### 题目简述


------------
给一个存在 $n$ 个点和 $m$ 条边的无向图，问能不能再添加几条边使得整个图刚好形成一个环。

#### 题目分析


------------
本题唯一的难点在于如何判断此图是否是一个环。

考虑使用并查集维护每一个点的父节点，只要该图上每一个点的父节点都是一个点就可以判定此图为一个环。

同时还需要考虑输出 ```NO``` 的情况

- 有一个点的度大于 $2$。
- 不能形成一个环

解决了以上问题，本题就迎刃而解了。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long 
using namespace std;
const int N = 55;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
int n,m;
int fa[N],edge[N][N];
int du[N];
pair<int,int> ans[N];
int find(int x){
	if(fa[x] == x)
		return x;
	else 
		return fa[x] = find(fa[x]);
}
signed main(){
	n = read() , m = read();
	if(n < m){
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		fa[i] = i;
	}
	for(int i=1;i<=m;i++){
		int a = read() , b = read();
		edge[a][b] = 1 , edge[b][a] = 1;
		du[a]++ , du[b]++;
		if(du[a] > 2 || du[b] > 2){
			printf("NO\n");
			return 0;
		}
		fa[find(a)] = fa[find(b)];
	}
	int num = 0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(find(i) != find(j) && du[i] < 2 && du[j] < 2){
				ans[++num] = make_pair(i,j);
				du[i]++;
				du[j]++;
				fa[find(i)] = find(j);
			}
		}
	}
	if(m + num == n-1){
		num++;
		for(int i=1;i<=n;i++){
			while(du[i] < 2){
				du[i]++;
				if(!ans[num].first)
					ans[num].first = i;
				else ans[num].second = i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(find(i) != find(1)){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n%lld\n",num);
	for(int i=1;i<=num;i++){
		printf("%lld %lld\n",ans[i].first,ans[i].second);
	}
	return 0;
}
```


---

## 作者：Tiankun2010 (赞：3)

# 题意

给出一个含 $n$ 个点，$m$ 条边的图，问是否能通过加一些边使整个图变成**一个 $n$ 元环**。

 $n$ 元环：由 $n$ 个点，$n$ 条边组成的环。

# 分析

### 如何判断图是否是一个 $n$ 元环？

-  $n$ 个点，$n$ 条边 

在最后判断即可。

- 每个点度数均为 $2$

动态维护每个点的度数，保证计算过程中每个点的度数均 $\le 2$。

- 图联通（不然可能是多个环）

在加边时用并查集维护连通性，最后判断。

所以，在计算过程中，我们只需要保证以上 $3$ 点满足，就能保证有解；若出现矛盾，说明无解。

### 如何加边？

如果两个点不属于同一联通块且两点度数均不足 $2$，就一定会在这两点间加边。

**注意，由于 $n-1$ 条边已经足够将 $n$ 个点联通，所以第 $n$ 条边需要特殊处理。**

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace AC{
    const int maxn=55;
    int n,m;
    
    int in[maxn];
    //统计度数
    
    int fa[maxn];
    int getfa(int u){
        if(fa[u]==u)return u;
        return fa[u]=getfa(fa[u]);
    }
    //并查集
    
    int num=0;
    pair <int ,int> ans[maxn];
    //记录答案
    
    int main(){
        int u,v;
        scanf("%d%d",&n,&m);
        if(n<m){
            cout<<"NO";
            return 0;
        }//图中边数已超过n，无解
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            
            fa[getfa(u)]=getfa(v);
            //维护并查集
            in[u]++;
            in[v]++;
            //维护度数
        }
        
        for(int i=1;i<=n;i++)
            if(in[i]>2){
                cout<<"NO";
                return 0;
            }//有度数超过2的，无解
        
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++)
                if(getfa(i)!=getfa(j)&&in[i]<2&&in[j]<2){
                    fa[getfa(i)]=getfa(j);
                    //维护并查集
                    in[i]++;
                    in[j]++;
                    //维护度数
                    ans[++num]=make_pair(i,j);
                    //记录答案
                }
        
        if(m+num==n-1){
            int x,y;
            for(int i=1;i<=n;i++)
                if(in[i]<=1){
                    x=i;
                    in[i]++;
                    break;
                }
            for(int j=x;j<=n;j++)
                if(in[j]<=1){
                    y=j;
                    in[j]++;
                    break;
                }
            ans[++num]=make_pair(x,y);
        }
        //处理第n条边
        
        for(int i=2;i<=n;i++)
            if(getfa(i)!=getfa(1)){
                cout<<"NO";
                return 0;
            }//如果不联通，无解
        
        cout<<"YES\n";
        cout<<num<<'\n';
        for(int i=1;i<=num;i++)
            cout<<ans[i].first<<' '<<ans[i].second<<'\n';
        return 0;
    }
}
int main(){return AC::main();}
```


---

## 作者：封禁用户 (赞：2)

一个图为简单环，当且仅当该图联通，所有点的度数为 $2$。显然，当原图中已经具有度数大于 $2$ 的点时，是没有解的。

什么时候需要加边操作呢？首先要满足 $m \le n-1$ 且原图中没有环。添加的边数为 $n - m$。对于加边，加边之后两端点的度数一个小于 $2$，强制两端点原先属于不同的连通块，构造了一条链，两端点相连即可。按字典序输出即可。

---

## 作者：LawrenceSivan (赞：2)

# CF9E Interesting Graph and Apples

[说点无关的话](https://www.luogu.com.cn/paste/cn2vws3y)

## 题目大意

给 $n$ 个点，$m$ 条边。问是否存在一种方案使得加几条边能构成仅有 $n$ 个点 $n$ 条边的单个简单环。如果可以，输出字典序最小的方案。

$n\le50,m\le2500$

## 做法

考虑什么样的情况是可能的。

不难发现可能的情况一定是若干链或者是单个的点，我们只需要把他们顺次连接起来即可。

对于存在许多点同时存在，不允许出现自环。

对于一个连三条及以上的“菊花点”，一定是不可能的。

原因就在于在一个仅存在 $n$ 个点 $n$ 条边的单个简单环上每个点度数一定都是 $2$。

于是我们可以首先把所有链都合起来，之后只去考虑链首和链尾。

这个操作可以通过并查集轻松实现。

我们每次从小到大挑选两个不同链的端点进行链接，这样可以保证字典序最小。

由于我神志不太清醒，所以我使用了 `std::set`

最后如果把所有点连成了一个大链，我们只需要再连接一下大链的链首和链尾。

最后我们检查一下是否所有的点都已链接完成即可。

复杂度，大概是 $\mathcal{O(n^2 \text{log}n)}$ 的吧。

~~由于退役太久所以如果什么地方说错了请千万指出。~~

[代码](https://www.luogu.com.cn/paste/0oqo3q1i)

---

## 作者：OIer_ACMer (赞：1)

~~从未见过这么简单的蓝题。~~

------------
## 大致思路：

题意是给你了一个图，让你加入一些边使得成为一个由 $n$ 个点构成有且仅有 $n$ 条边的单个环（说白了就是所有点的入度为 $2$，且一开始所有点的入度小于等于 $2$），问你能否做到。这道题由于出现了**环**的条件，所以并查集是少不了的。同时，我们可以像一种情况：假如一个点的度**已经大于** $2$，那么很显然，你怎么加边都不能满足环的要求，因为环上的点度只为 $2$，且你只能做加边操作，因此可以特判为 ```No```，后面的就简单了，你只用找出度为 $1$ 的点，将其建边，并将边两边的节点存入 $ans$ 数组，最终，在输出的时候，如果一个点没有被连上，则直接输出 ```No```，否则就输出 ```Yes```，并依次输出 $ans$ 数组中的答案。


------------
## 具体步骤：
1. 输入数据，将边上的两个点用并查集合并起来，保存好边。

2. 特判：如果点的度大于等于 $3$ 则输出 ```No```（前面已经讲的很清楚了）。

3. 加边，将入度为 $1$ 的点加上一条边，注意，加边的另外一个节点度**也一定要为** $1$ **或** $0$，不然的话又要重现特判的场景了。

4. 连边完成后，将并查集首尾相连，成环。

5. 输出答案，如果有的点没边，则 ```No```，否则照常输出。



------------
## 警钟敲烂：
记住记住！！！一定要预处理 $fa$ 数组，否则就会像我一样调试 $30$ 分钟！！！！

------------
## 代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 51, M = 2501;
int fa[N], in[N], n, m;
struct node
{
    int u, v;
    node(int i, int j) : u(i), v(j) {}
};
vector<int> g[M];
vector<node> ans;
inline int find(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    return fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
    int xx = find(x), yy = find(y);
    if (xx == yy)
    {
        return;
    }
    fa[xx] = yy;
}
inline void init()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
}
bool cmp(node a, node b)
{
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}
int main()
{
    n = read();
    m = read();
    memset(in, 0, sizeof(in));
    init();
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        u = read();
        v = read();
        merge(u, v);
        in[v]++;
        in[u]++;
    }
    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        if (in[i] >= 3)
        {
            flag = false;
            break;
        }
    }
    if (!flag)
    {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (find(i) != find(j) && in[i] != 2 && in[j] != 2)
            {
                ans.push_back(node(j, i));
                merge(i, j);
                in[i]++, in[j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 2)
        {
            continue;
        }
        for (int j = 1; j < i; j++)
        {
            if (in[j] == 1)
            {
                ans.push_back(node(j, i));
                merge(i, j);
                in[i]++;
                in[j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0)
        {
            ans.push_back(node(i, i));
        }
    }
    int root = find(1);
    for (int i = 1; i <= n; i++)
    {
        if (find(i) != root)
        {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    sort(ans.begin(), ans.end(), cmp);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].u << " " << ans[i].v << endl;
    }
    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/120783073)

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
---
### 解题思路：

一个可能满足条件的图是一些链或者一个环。

直接将所有的链链接到一起去，然后判断即可。实现的时候可以使用并查集来做合并操作。

注意这个方法不能链接自环，需要对于 $n=1$，$m=0$ 的情况特判。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=10000;
int n,m,fa[MAXN],x,y,d[MAXN],cnt,ansx[MAXN],ansy[MAXN],flag;
int find(int x){
	if(fa[x]==x)return x;
	return find(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	if(n==1&&m==0){
		printf("YES\n1\n1 1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		fa[find(x)]=find(y);
		d[x]++;d[y]++;
	}
	for(int i=1;i<=n;i++)
	if(d[i]>=3){
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(find(i)!=find(j)&&d[i]<2&&d[j]<2){
				d[i]++;d[j]++;
				fa[find(i)]=find(j);
				ansx[++cnt]=i;
				ansy[cnt]=j;
			}
		}
	}
	x=find(1);
	for(int i=1;i<=n;i++){
		if(find(i)!=x){
			printf("NO\n");
			return 0;
		}
	}
	flag=0;
	for(int i=1;i<=n;i++){
		if(d[i]==1){
			if(flag==0){
				d[i]++;flag=1;
				ansx[++cnt]=i;
			}
			else{
				d[i]++;
				ansy[cnt]=i;
			}
		}
	}
	printf("YES\n%d\n",cnt);
	for(int i=1;i<=cnt;i++)
	printf("%d %d\n",ansx[i],ansy[i]);
	return 0;
}
```


---

## 作者：kczno1 (赞：1)

贪心。  
一开始就不合法或已经成环的情况特判一下。  
然后按字典序从小到大枚举每条边，  
如果加了之后不成环就加，   
相当于连接了两条链，  
最后加入一条边把最后一条链的两端连起来。

```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc

const int N=50+5;
int fa[N],du[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
pii ans[N];

int main()
{
	freopen("1.in","r",stdin);//freopen("1.out","r",stdin);
	int n=read(),m=read();
	rep(i,1,n)fa[i]=i;
	rep(i,1,m)
	{
		int x=read(),y=read();
		++du[x];++du[y];
		fa[find(x)]=find(y);
	}
	rep(i,1,n)
	if(du[i]>2)
	{
		puts("NO");
		return 0;
	}
	int top=0;
	rep(i,1,n)
	rep(j,i,n)
	if(find(i)!=find(j)&&du[i]<2&&du[j]<2)
	{
		ans[++top]=mp(i,j);
		++du[i];++du[j];
		fa[find(i)]=find(j);
	}
	if(m+top==n-1)	
	{	
		++top;
		rep(i,1,n)
		while(du[i]<2)
		{
			++du[i];
			if(!ans[top].first)ans[top].first=i;
			else ans[top].second=i;
		}
	}
	rep(i,1,n)
	if(find(i)!=find(1))
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	printf("%d\n",top);
	rep(i,1,top)printf("%d %d\n",ans[i].first,ans[i].second);
}
	
```

---

## 作者：叶枫 (赞：0)

这道题，用**并查集**啊
### 题意 $+Idea$
大致就是给你$n$个点,这$n$个点之间有$m$条边相连,问能不能再添加几条边，使这$n$个点刚好能围成一个圈.

因为是无向图，判断能否成一个圈，也就是一个$father$，所以用了并查集。

### $Code$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#define ll long long
#define maxn 105
#define inf 2147483647
#define mod 10003
#define eps 1e-6
#define pi acos(-1.0)
#define de(x) ((x)*(x))
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int deep[maxn],fa[maxn];//deep[]记录度数 
int n,m,ans;
struct Node{//记录加边情况 
	int u,v;
}e[1100];
inline void init(){for(int i=1;i<=n;i++) fa[i]=i;}
inline int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
inline void Union(int x,int y){
	int xx=find(x),yy=find(y);
	if(xx!=yy) fa[xx]=yy;
}
inline bool check(){
    for(int i=1;i<=n;i++)
    if(deep[i]<2){
        for(int j=i+1;j<=n;j++)
        if(deep[j]<2&&find(i)!=find(j)){
            Union(i,j);
            e[ans].u=i; e[ans].v=j;
            ans++;
            deep[i]++; deep[j]++;
            break;
        }
        if(deep[i]<2)
        for(int j=i+1;j<=n;j++)
        if(deep[j]<2&&find(i)!=find(j)){
            Union(i,j);
            e[ans].u=i; e[ans].v=j;
            ans++;
            deep[i]++; deep[j]++;
            break;
        }
    }
    int cot=0;
    for(int i=1;i<=n;i++){
        if(deep[i]!=1&&deep[i]!=2) return false;
        if(deep[i]==1) cot++;
    }
    if(cot==2) return true;
    else return false;
}
bool flag,sign;
signed main(){
	n=read(); m=read();
	if(n==1&&m==0) return printf("YES\n1\n1 1"),0;//特判，只有一个点和0条边； 
	int tmp=0; flag=sign=false;
	init(); ans=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		deep[x]++; deep[y]++;
		if(find(x)==find(y)) flag=true;//如果为环，标记为一 
		Union(x,y);
	}
	for(int i=1;i<=n;i++) tmp=max(tmp,deep[i]);
	if(tmp>2) return puts("NO"),0;//如果度数>2 ，肯定为0； 
	if(flag){/若原图有环 
		int t=find(1);
		for(int i=2;i<=n;i++)
		if(t==find(i)&&deep[i]==2) continue;
		else{sign=true; break;}
		if(!sign) return printf("YES\n0"),0;
		else return puts("NO");
	}
	if(check()){
		int p[2],cnt=0;
		for(int i=1;i<=n;i++) if(deep[i]==1) p[cnt++]=i;
		e[ans].u=p[0]; e[ans++].v=p[1];
		puts("YES"); printf("%d\n",ans);
		for(int i=0;i<ans;i++) printf("%d %d\n",e[i].u,e[i].v);
	}
	else return puts("NO"),0;
    return 0;
}
```
$\sout{bu~yao~chao~xi}$

---

