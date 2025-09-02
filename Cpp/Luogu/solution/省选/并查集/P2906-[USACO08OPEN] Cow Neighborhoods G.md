# [USACO08OPEN] Cow Neighborhoods G

## 题目描述

了解奶牛的人都知道奶牛是如何组成「奶牛社区」的。他们观察了 Farmer John 的 $N$ 头奶牛（编号为 $1 \sim N$），它们在 $X$ 和 $Y$ 坐标范围为 $1$ 的牧场上放牧，每头奶牛都在自己唯一的整数直线坐标上。

如果满足以下两个标准中的至少一个，则两头奶牛是邻居：

1. 两只奶牛的曼哈顿距离不超过 $C$，即 $|X_i - x_i| + |Y_i - y_i| \leq C$；
2. 两只奶牛有共同的邻居。即存在一只奶牛 $k$，使 $i$ 与 $k$，$j$ 与 $k$ 均同属一个群。

给定奶牛的位置和距离 $C$，确定「奶牛社区」的数量和最大的「奶牛社区」中的奶牛数量。

例如，考虑下面的牧场。 当 $C = 4$ 时，这个牧场有四个社区：左边的一个大社区，两个大小为 1 的社区，右边有一个巨大的社区，里面有 $60$ 头不同的奶牛。

```text
.....................................*.................
....*...*..*.......................***.................
......*...........................****.................
..*....*..*.......................*...*.******.*.*.....
........................*.............***...***...*....
*..*..*...*..........................*..*...*..*...*...
.....................................*..*...*..*.......
.....................................*..*...*..*.......
...*................*..................................
.*..*............................*.*.*.*.*.*.*.*.*.*.*.
.*.....*..........................*.*.*.*.*.*.*.*.*.*.*
....*..................................................
```

## 说明/提示

### 样例说明 #1

样例中有 $2$ 个社区，一个由前三头奶牛组成，另一个是最后一头奶牛。因此，最大的社区大小为 $3$。

### 数据范围与约定

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq C \leq 10^9$，$1 \leq X_i, Y_i \leq 10^9$，$X_i, Y_i$ 均为整数。

## 样例 #1

### 输入

```
4 2 
1 1 
3 3 
2 2 
10 10 
```

### 输出

```
2 3 
```

# 题解

## 作者：Siyuan (赞：21)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Luogu-2906-Cow-Neighborhoods/)

---

## Description

> 题目链接：[Luogu 2906](https://www.luogu.org/problemnew/show/P2906)

了解奶牛们的人都知道，奶牛喜欢成群结队。观察约翰的 $n$ 只奶牛，你会发现她们已经结成了几个“群”。每只奶牛在吃草的时候有一个独一无二的位置坐标 $(X_i,Y_i)$。当满足下列两个条件之一，两只奶牛 $i$ 和 $j$ 是属于同一个群的：

1. 两只奶牛的曼哈顿距离不超过 $C$，即 $|X_i-X_j|+|Y_i-Y_j|\le C$。
2. 两只奶牛有共同的邻居。即存在一只奶牛 $k$，使 $i$ 与 $k$、$j$ 与 $k$ 均同属一个群。

请计算有多少个牛群，以及最大的牛群里有多少奶牛。

数据范围：$1\le n\le 10^5$，$1\le X_i,Y_i,C\le 10^9$，$X_i,Y_i,C\in \mathbb{Z}$

------

## Solution

首先我们有一个转化：**曼哈顿距离**转**切比雪夫距离**。将一个点的坐标 $(x,y)$ 转化成 $(x+y,x-y)$，设新点的坐标为 $(x',y')$，那么原来的曼哈顿距离 $\vert x_1-x_2\vert +\vert y_1-y_2\vert$ 就等于现在的切比雪夫距离 $\max(\vert x'_1-x'_2\vert,\vert y'_1-y'_2\vert)$。可以通过分类讨论或几何法简单证明成立。

设第 $i$ 个点的新坐标为 $(X_i+Y_i,X_i-Y_i)$，记为 $(x_i,y_i)$。那么第 $1$ 个限制会变为：

- 两只奶牛的切比雪夫距离不超过 $C$，即 $\max(\vert x_1-x_2\vert,\vert y_1-y_2\vert)\le C$。

由于有 $\max$，我们可以将 $(x_i,y_i)$ 以 $x_i$ 为第一个关键字，$y_i$ 为第二关键字，从小到大排序。对于同一群的奶牛我们用并查集合并。

我们用 $\text{set}$ 维护 $y_i$（每个点）的值，我们每次在插入第 $i$ 个点时，先把 $\text{set}$ 中所有满足 $\vert x_i-x_j\vert>C$ 的点都删除，然后用 $\text{lower_bound}$ 找到第一个大于等于 $y_i$ 的点，如果满足约束条件就将这两个点合并起来。再找到最后一个小于 $y_i$ 的点，进行相同合并操作。

最后我们证明其他的点不需要和 $i$ 合并。

对于大于等于 $y_j$ 的点 $k$ 满足约束条件 $y_k-y_i\le C$，那么 $y_k-y_j\le y_k-y_i\le C$，那么在处理 $j$ 或 $k$ 时一定会把 $k$ 合并进来（这取决于 $x_j$ 和 $x_k$ 的大小），所以不必合并了。对于小于的部分证明同理。

**时间复杂度**：$O(n\cdot\alpha(n)\log n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
typedef std::pair<long long,int> pli;
typedef std::pair<long long,long long> pll;
#define mk std::make_pair

const int N=1e5+5;
int n,C,fa[N],cnt[N];
pll a[N];
std::set<pli> s;

int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y) {
	fa[find(x)]=find(y);
}
int main() {
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;++i) {
		int X,Y;
		scanf("%d%d",&X,&Y);
		a[i]=mk(X+Y,X-Y),fa[i]=i;
	}
	std::sort(a+1,a+n+1);
	s.insert(mk(-1LL<<60,0)),s.insert(mk(1LL<<60,0));
	s.insert(mk(a[1].second,1));
	for(int l=1,i=2;i<=n;++i) {
		while(a[i].first-a[l].first>C) s.erase(mk(a[l].second,l)),++l;
		std::set<pli>::iterator it=s.lower_bound(mk(a[i].second,0));
		if(it->first-a[i].second<=C) merge(i,it->second);
		--it;
		if(a[i].second-it->first<=C) merge(i,it->second);
		s.insert(mk(a[i].second,i));
	}
	int ans=0,mx=0;
	for(int i=1;i<=n;++i) ans+=(find(i)==i),mx=std::max(mx,++cnt[find(i)]);
	printf("%d %d\n",ans,mx);
	return 0;
}
```



---

## 作者：a___ (赞：9)

首先 $\mathbf O(n^2)$ 应该都会做。我们考虑将点分别按 $x$ 、 $y$ 坐标排序，仅和每个数之后 $800$ 个比较，将距离合适的点全部合并的概率很大。尤其是根据这题的性质每个点只需与几个点合并就可以保证正确性。   

AC代码：   
```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<algorithm>
#include<cstring>
const int N=100010;
//快读板子（省略）
int fa[N];
int find(const int &x){return fa[x]>0?fa[x]=find(fa[x]):x;}
inline void un(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y)return;
	if(fa[x]>fa[y])
		fa[y]+=fa[x],fa[x]=y;
	else fa[x]+=fa[y],fa[y]=x;
}
int n,m,x[N],y[N],p[N],ans,tot;
bool cmp1(const int &a,const int &b){return x[a]<x[b];}
bool cmp2(const int &a,const int &b){return y[a]<y[b];}
inline int iabs(const int x){return x<0?-x:x;}
int main()
{
	n=In::readu();m=In::readu();
	memset(fa,-1,sizeof fa);
	for(register int i=1;i<=n;i++)
	x[i]=In::readu(),y[i]=In::readu(),p[i]=i;
	std::sort(p+1,p+1+n,cmp1);
	for(register int i=1;i<=n;i++)
	for(register int j=1;j<=800;j++)
	{
		if(i+j>n)break;
		if((x[p[i+j]]-x[p[i]])+iabs(y[p[i]]-y[p[i+j]])<=m)un(p[i],p[i+j]);
	}
	std::sort(p+1,p+1+n,cmp2);
	for(register int i=1;i<=n;i++)
	for(register int j=1;j<=833;j++)
	{
		if(i+j>n)break;
		if((y[p[i+j]]-y[p[i]])+iabs(x[p[i]]-x[p[i+j]])<=m)un(p[i],p[i+j]);
	}
	for(register int i=1;i<=n;i++){tot+=(fa[i]<0);if(ans>fa[i])ans=fa[i];}
	Out::print(tot);Out::print(ans);Out::flush();
	return 0;
}
```

稍微有点卡常。。。   

如果还是不能保证正确性，甚至还可以将坐标轴旋转 $45°$ 排序之类的。

---

## 作者：dyc2022 (赞：6)

我们充分发扬人类智慧：

将所有点全部绕原点旋转同一个角度，然后按 $x^2+y^2$ 排序。

根据数学直觉，在随机旋转后，答案中的两个点在数组中肯定不会离得太远。

所以我们只取每个点前后 $600$ 个点判断能否产生答案，用带权并查集维护连通性和联通块大小即可。

但是这还不足以通过。我们可以接着按照 $x^2-y^2$ 排序，重复上述过程即可。

这样速度快得飞起，在 $n = 10^5$ 时都能 $999\text{ms}$ 内卡过。

---

## 作者：litble (赞：6)

QAQ真是神题。

我们把点对坐标转化为(x+y,x-y),那么曼哈顿距离就转化为了max(|x1-x2|,|y1-y2|);
我们把点按照x坐标排序，然后维护一个队列，队列中元素的x坐标差的绝对值是不大于C的。然后用平衡树（或者multiset），维护y坐标，每次查找y坐标前驱后继，并检验y坐标差值是否大于C，如果不大于，就可以用并查集连接当前点和其y坐标前驱后继，最后通过统计并查集数量和每个并查集大小来得到答案。

multiset几个用法：

```cpp
s.erase(s.find(x)),删除一个大小为x的元素。
s.erase(x),删除所有大小为x的元素。
s.lower_bound(x)，和lower_bound(s.begin(),s.end(),x)差不多，但是快一些。
s.insert(x)插入元素x
```
天哪这个思路太6了，%%%半个小时做出来的boshi大佬。
代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<set>
using namespace std;
#define LL long long
LL read(){//读入优化
    LL w=1,q=0;char ch=' ';
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')q=q*10+(LL)(ch-'0'),ch=getchar();
    return q*w;
}
const int N=100005;
int n,f[N],tot[N],ans,mx;LL c;
struct node{LL x,y;int id;}a[N];
multiset<node>s;
multiset<node>::iterator it;
bool cmp(node a,node b){return a.x<b.x;}
bool operator<(node a,node b){return a.y<b.y;}//重载运算符来使用multiset
int find(int x){
    if(x==f[x])return x;
    f[x]=find(f[x]);return f[x];
}
void uni(int x,int y){//并查集连接
    int r1=find(x),r2=find(y);
    if(r1!=r2)tot[r2]+=tot[r1],tot[r1]=0,f[r1]=r2,--ans;
}
void solve(){
    node kl;int i,he=1;
    sort(a+1,a+1+n,cmp);s.insert(a[1]);
    kl.x=0,kl.id=0,kl.y=1e10,s.insert(kl);//防止因为不存在前驱后继，指针爆炸
    kl.x=0,kl.id=0,kl.y=-1e10,s.insert(kl);
    for(i=2;i<=n;++i){
        while(a[i].x-a[he].x>c)s.erase(s.find(a[he])),++he;//移动队首
        it=s.lower_bound(a[i]);//查找元素
        kl=*it;
        if(kl.y-a[i].y<=c)uni(a[i].id,kl.id);
        kl=*--it;
        if(a[i].y-kl.y<=c)uni(a[i].id,kl.id);
        s.insert(a[i]);//插入元素
    }
}
int main(){
    int i,j;LL kx,ky;
    n=read(),c=read();ans=n;
    for(i=1;i<=n;++i){
        f[i]=i,tot[i]=1,kx=read(),ky=read();
        a[i].x=kx+ky,a[i].y=kx-ky,a[i].id=i;
    }
    solve();
    for(i=1;i<=n;++i)mx=max(tot[i],mx);
    printf("%d %d",ans,mx);
    return 0;
}
```

---

## 作者：Huang_Yuhan (赞：5)

# 题目描述：
一些了解奶牛的人来到了FJ的农场观察FJ的$N (1 \leqslant N \leqslant 100,000)$头奶牛，为了方便编号为$1..N$。每头牛在牧场里都有他单独的坐标$X,Y(1\leqslant X ,Y \leqslant 1,000,000,000)$。

两头牛如果满足了以下两个条件之一便是邻居：

1.如果他们的曼哈顿距离小于$C (1 \leqslant C \leqslant 1,000,000,000)$.曼哈顿距离是$|x_1-x_2| + |y_1-y_2|$。

2.如果$Z$是$A$的邻居，同时$Z$也是$B$的邻居，那么$A$就是$B$的邻居。

# 解：

我们发现这道题的曼哈顿距离很烦。

所以我们转换成切比雪夫坐标系。

不懂的戳这里 ：[坐标轴转换](https://www.luogu.org/blog/HuangYuhan-Yuzhe/zuo-biao-ji-zhuai-huan)

转换坐标系后，我们先对所有点按pair的比较函数一样排序，这样保证了$x$坐标单调不下降的。

然后我们从左往右讨论。

对于第$i$个结点,我们只需要讨论$x_j+C\leqslant x_i$的$j$。

然后我们只需要找到所有满足条件的结点中$y$离$y_i$最近的两个点就行了。

为什么呢？

因为其他点如果也能到达$i$号结点，那么他之前一定会被和那两个结点其中一个或者两个合并成一个集合。

同时集合合并问题~~显然~~用并查集。

再找最近的两个点的时候，怎么快速的找呢？

二分查找。

但是这个二分查找的东西又是动态的，需要删除和插入。

所以我们就想到了STL中的set

然后注意一下讨论是否找到没以及时候差值小于等于$C$就行了。

时间复杂度为$O(nlog_2n)$

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int maxn=100000+5;
    typedef long long ll;
    typedef pair<ll,ll> P;
    P node[maxn];
    int fa[maxn],cnt[maxn];
    int getfa(int v)
    {return fa[v]==v?v:fa[v]=getfa(fa[v]);}
    inline void merge(int x,int y)
    {
    	int fx=getfa(x);
    	int fy=getfa(y);
    	if(fx!=fy){fa[fx]=fy;cnt[fy]+=cnt[fx];}
    }
    int main()
    {
    	int n,x,y;
    	ll C;
    	scanf("%d %lld",&n,&C);
    	for(int i=1;i<=n;i++)
    	{
    		scanf("%d %d",&x,&y);
    		node[i].first=x+y;
    		node[i].second=x-y;
    		fa[i]=i;cnt[i]=1;
    	}
    	sort(node+1,node+1+n);
    	set<P> s;
    	set<P>::iterator it;
    	int j=0;
    	for(int i=1;i<=n;i++)
    	{
    		while(!s.empty()&&j+1<i&&node[j+1].first+C<node[i].first)s.erase(s.find(make_pair(node[j+1].second,j+1))),j++;
    		if(!s.empty())
    		{
    			it=s.lower_bound(make_pair(node[i].second,0));
    			if(it!=s.end())
    			{
    				if(it->first-node[i].second<=C)merge(it->second,i);

    			}
    			if(it!=s.begin())
    			{
    				it--;
    				if(node[i].second-it->first<=C)merge(it->second,i);
    			}
    		}
    		s.insert(make_pair(node[i].second,i));
    	}
    	int ans1=0,ans2=0;
    	for(int i=1;i<=n;i++)
    	if(getfa(i)==i)
    	{
    		ans1++;
    		ans2=max(ans2,cnt[i]);
    	}
    	printf("%d %d",ans1,ans2);
    	return 0;
    }
```

---

## 作者：是个汉子 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/P2906)

题外话：第一次听说曼哈顿距离转切比雪夫距离

### Solution

首先明确：因为条件 $2$ 说的非常显眼，所以可以想到拿并查集去维护每只牛之间的群和大小。

先想最朴素的方法，枚举每两只牛之间是否满足条件 $1$ 。

时间复杂度为 $O(n^2)$ 显然不行。

我们观察看到条件 $1$ 中有一个**曼哈顿距离**，如果熟悉这种套路，可以自然的想到转化；如果不熟悉，做了这个题也就熟悉了(●'◡'●)

~~（其实我也不熟，但是这真的是套路，就跟把题解砸你脸上一样）~~

考虑将曼哈顿距离转化为切比雪夫距离：

设一只牛原来的坐标为 $(x_i,y_i)$ ，现在是 $(x_i',y_i')=(x_i+y_i,x_i-y_i)$ ，那么曼哈顿距离公式
$$
|x_i-x_j|+|y_i-y_j|=\frac 12(|x_i'+y_i'-x_j'-y_j'|+|x_i'-y_i'-x_j'+y_j'|)=\max(|x_i'-x_j'|,|y_i'-y_j'|)
$$
所以我们可以将所有点的坐标化成 $(x',y')$ 的形式，然后按 $x'$ 排序，用队列维护 $|x_i'-x_j'|\leq C$ ，用 $\operatorname{set}$ 维护 $y'$ 

为什么这样可以减少复杂度呢？

因为只需要判断新的 $x'$ 的前驱和后继是否满足新条件即可，所以是 $O(n\log n)$ 的。(有二分)

答案只需要简单判断即可。

（更多细节可以看代码(\*^▽^*)）

### Code

```c++
#include<bits/stdc++.h>
#define PII pair<int,int>

using namespace std;
const int N=100010,INF=1e9;
set<PII> S;
queue<int> q;
PII a[N];
int fa[N],siz[N],n,c,cnt,maxx;

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].first,&a[i].second);
        a[i].first+=a[i].second;
        a[i].second=a[i].first-2*a[i].second;
        fa[i]=i;    //注意并查集的初始化
    }
    sort(a+1,a+n+1);
    S.insert(make_pair(-INF,0)),S.insert(make_pair(INF,0));
    q.push(1); S.insert(make_pair(a[1].second,1));
    for(int i=2;i<=n;i++){
        while(!q.empty()&&a[i].first-a[q.front()].first>c){
            int u=q.front(); q.pop();
            S.erase(make_pair(a[u].second,u));
        }
        set<PII>::iterator it=S.lower_bound(make_pair(a[i].second,0));
        if(it->second&&it->first-a[i].second<=c){
            int u=find(it->second),v=find(i);
            if(u!=v) fa[u]=v;
        }
        if((--it)->second&&a[i].second-it->first<=c){
            int u=find(it->second),v=find(i);
            if(u!=v) fa[u]=v;
        }
        q.push(i),S.insert(make_pair(a[i].second,i));
    }
    for(int i=1;i<=n;i++){
        if(find(i)==i) cnt++;
        siz[find(i)]++;
        maxx=max(maxx,siz[find(i)]);
    }
    printf("%d %d\n",cnt,maxx);
    return 0;
}
```



---

## 作者：Froggy (赞：5)

---
关于曼哈顿距离的坐标转化成$max\{|x_{i}-x_{j}|,|y_{i}-y_{j}|\}$
我在这里就不多说了,思路差不多.
#### 楼上大佬很厉害~


---
### 但...
##### set和multiset我不喜欢,因为noip不开O2
##### (~~其实我根本不会用~~)
##### 为啥不手写平衡树呢?? 
##### 用结构体写平衡树我还是第一回
关于平衡树,先把模板题做了
[P3369 【模板】普通平衡树](https://www.luogu.org/problemnew/show/P3369)

---
直接贴代码~
#### 破记录啦,187行~
---

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
#define N 100010
#define ll long long
#define inf 9999999999999//inf开大点,一开始我挂了
inline ll read(){//快读
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
	    x=(x<<3)+(x<<1)+c-'0';c=getchar();
	}
	return x;
}
ll c,tot[N],ans;
int f[N];
int n,cnt,root;
struct cow{
	ll x,y;
	int id;
	bool operator <(const cow &a)const{
		return y<a.y;
	}
	bool operator >(const cow &a)const{
		return y>a.y;
	}
	bool operator ==(const cow &a)const{
		return y==a.y;
	}
	bool operator >=(const cow &a)const{
		return y>=a.y;
	}
}a[N];
struct node{
	int l,r,val,siz;
	cow data;
}t[N<<1];
bool cmp(cow a,cow b){
	return a.x<b.x;
}
void up(int k){
	t[k].siz=t[t[k].l].siz+t[t[k].r].siz+1;
}
void zig(int &k){//右旋
	int tmp=t[k].l;
	t[k].l=t[tmp].r;
	t[tmp].r=k;
	t[tmp].siz=t[k].siz;
	up(k);
	k=tmp;
}
void zag(int &k){//左旋
	int tmp=t[k].r;
	t[k].r=t[tmp].l;
	t[tmp].l=k;
	t[tmp].siz=t[k].siz;
	up(k);
	k=tmp;
}
void insert(int &k,cow data){//插入
	if(k==0){
		k=++cnt;
		t[k].siz=1;
		t[k].data=data;
		t[k].val=rand();
		return;
	}
	t[k].siz++;
	if(data>=t[k].data){
		insert(t[k].r,data);
	}
	else{
		insert(t[k].l,data);
	}
	if(t[k].l!=0&&t[k].val>t[t[k].l].val){
		zig(k);
	}
	if(t[k].r!=0&&t[k].val>t[t[k].r].val){
		zag(k);
	}
	up(k);
}
void del(int &k,cow data){//删除
	t[k].siz--;
	if(data==t[k].data){
		if(t[k].l==0&&t[k].r==0){
			k=0;
			return;
		}
		if(t[k].l==0||t[k].r==0){
			k=t[k].l+t[k].r;
			return;
		}
		if(t[t[k].l].val<t[t[k].r].val){
			zig(k);
			del(t[k].r,data);
			return;
		}
		else{
			zag(k);
			del(t[k].l,data);
			return;
		}
	}
	if(t[k].data>=data){
		del(t[k].l,data);
	}
	else{
		del(t[k].r,data);
	}
	up(k);
}
int query_pre(int k,cow data){
	if(k==0){
		return 0;
	}
	if(t[k].data>data){
		return query_pre(t[k].l,data);
	}
	int tmp=query_pre(t[k].r,data);
	if(tmp==0){
		return k; 
	}
	return tmp;
}
int query_suf(int k,cow data){
	if(k==0){
		return 0;
	}
	if(t[k].data<data){
		return query_suf(t[k].r,data);
	}
	int tmp=query_suf(t[k].l,data);
	if(tmp==0){
		return k;
	}
	return tmp;
}
int getf(int x){
	if(f[x]==x)return x;
	return f[x]=getf(f[x]);
}
void merge(int x,int y){
	int r1,r2;
	r1=getf(x),r2=getf(y);
	if(r1!=r2){
		tot[r1]+=tot[r2];tot[r2]=0;ans--;
		f[r2]=r1;
	}
}
int main(){
	n=read();c=read();ans=n;
	for(int i=1;i<=n;i++){
		ll p=read(),q=read();
		a[i].x=p+q;a[i].y=p-q; 
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		tot[i]=1;f[i]=i;
	}
	int head=1;
	insert(root,a[1]);
	insert(root,(cow){0,-inf,0});//插入俩极限值
	insert(root,(cow){0,inf,0});
	for(int i=2;i<=n;i++){
		while(a[i].x-a[head].x>c){
			del(root,a[head]);head++;
		} 
		int pre=query_pre(root,a[i]);//查询前驱
		int suf=query_suf(root,a[i]);//查询后继
		if(t[suf].data.y-a[i].y<=c){
			merge(t[suf].data.id,a[i].id);//合并
		}
		if(a[i].y-t[pre].data.y<=c){
			merge(t[pre].data.id,a[i].id);
		}
		insert(root,a[i]);
	}
	ll maxx=0;
	for(int i=1;i<=n;i++)maxx=max(maxx,tot[i]);
	printf("%d %lld\n",ans,maxx);
	return 0;
}


```

---

## 作者：HiJ1m (赞：2)

本题需要求曼哈顿距离，并且在寻找邻居的时候只要找距离自己最近的奶牛看看与它是否属于同一个群。很容易想到使用平衡树求前驱和后继，但是求曼哈顿距离的公式|X1-X2|+|Y1-Y2|很难维护。
所以我们要对数据进行处理，讲每个点变为（x+y，x-y），这样曼哈顿距离就是max（|X1-X2|，|Y1-Y2|）。每次比较只要比较两个点的一个值就可以了。
所以我们用一个队列维护x，用一个平衡树（或者multiset）去维护y。找到合法的就用并查集将两个合在一起。


```cpp
//Bzoj1604  Luogu2906
#include<bits/stdc++.h>
#define MAXN 100005
const long long INF=(1ll<<60);
#define ll long long
using namespace std;
inline void read(ll &x){
     x=0;int t=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')t=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x=x*t;
}
ll N,father[MAXN],ans;
ll tot[MAXN],maxt,C;
struct Node{
    ll x,y;
    int id;
    bool operator <(const Node p)const{
        return y<p.y;
    }
}a[MAXN];
bool cmp(Node p,Node q){
    return p.x<q.x;
}
int find(ll p){return father[p]==p?p:father[p]=find(father[p]);}
void merge(ll p,ll q){
    int fp=find(p),fq=find(q);
    if(fp!=fq){
        tot[fp]+=tot[fq],tot[fq]=0,ans--;
        father[fq]=fp;
    }
}
multiset<Node> b;
multiset<Node>::iterator it;
int main()
{
    read(N);read(C);
    for(int i=1;i<=N;i++){
        ll p,q;read(p);read(q);
        a[i]=(Node){p+q,p-q,i};
    }
    ans=N;    for(int i=1;i<=N;i++)tot[i]=1,father[i]=i;    //init
    sort(a+1,a+N+1,cmp);
    int head=1;Node k;                                    //按x排序 - 队列
    b.insert(a[head]);    
    k=(Node){0, INF,0};b.insert(k);
    k=(Node){0,-INF,0};b.insert(k);
    for(int i=2;i<=N;i++){
        while(a[i].x-a[head].x>C)b.erase(b.find(a[head])),head++;
        it=b.lower_bound(a[i]);
        k=*it;
        if(k.y-a[i].y<=C)merge(k.id,a[i].id);
        k=*--it;
        if(a[i].y-k.y<=C)merge(k.id,a[i].id);
        b.insert(a[i]); 
    }
    for(int i=1;i<=N;i++)maxt=max(maxt,tot[i]);
    printf("%lld %lld\n",ans,maxt);
    return 0; 
}
```
给博客打广告http://www.cnblogs.com/Elfish/p/7632538.html

---

## 作者：ListenSnow (赞：1)

## 题意

给定 $n$ 只奶牛，每只奶牛都有一个**独一无二**的坐标 $(x_i,y_i)$。当满足下列条件**之一**时，两只奶牛属于同一个群：

1.两只奶牛的**曼哈顿距离**不超过 $C$，即 $|x_i-x_j|+|y_i-y_j|\leq C$。

2.两只奶牛有一个**共同的邻居**，即存在一头奶牛 $k$，使得 $i$ 和 $k$，$k$ 和 $j$ 均属于同一群。

求一共有多少个群，以及最大的群里有多少奶牛。

## 思路

注意到题目中的第二个条件。可以发现，在一个群中，每头奶牛只需存在一头奶牛与它的曼哈顿距离不超过 $C$ 即可，而不是所有奶牛之间的距离都不超过 $C$。也就是本题中的群具有**传递性**。于是就可以用**并查集**来标记每个点属于哪个群。

对于题目中的曼哈顿距离，因为有两个绝对值符号的存在，所以直接求解有些困难。于是就可以用到**曼哈顿距离转化成切比雪夫距离**的技巧，即将原坐标 $(x,y)$ 转化为 $(x+y,x-y)$，在新坐标系中的切比雪夫距离就是原坐标的曼哈顿距离。（具体证明可以看一下[这篇博客](https://www.cnblogs.com/SGCollin/p/9636955.html)）

切比雪夫距离的定义为 $\max(|x_i-x_j|,|y_i-y_j|)$，此时虽然只是将求和改成了取最大值，但是省去了不少麻烦。

在新坐标系中，对于一个点 $(x_i,y_i)$，就可以在所有满足 $|x_i-x_j| \leq C$ 的坐标中，找到与其 $y_i$ 相差最小的 $y_j$，即 $y_i$ 的**前驱和后继**，那么如果满足 $|y_i-y_j| \leq C$ ，就可以将这两个点放到同一个群中。下面简单证明一下该做法的正确性：

当 $|y_i-y_j| > C$ 时，与 $y_i$ 值相差最小的点都不满足要求，其他点就更不可能满足了。

当 $|y_i-y_{k}| \leq C$ 时（$k$ 点为 $j$ 点的前驱），也就是对于第 $i$ 个点，除了前驱和后继，还有其他点满足要求（这里举的是前驱的例子，绝对值符号其实可以拿走，后继的证明同理）。显然 $|y_j-y_{k}| \leq C$ 也是成立的，那么在此前就已经把 $j$ 和 $k$ 这两个点合并了，此时只要把第 $j$ 个点和第 $i$ 个点合并，$i$ 和 $k$ 就在同一个群中了。

当 $|y_i-y_{k}| > C$ 时。根据本题中群的**传递性**，只要满足 $|y_i-y_j| \leq C,|y_j-y_k| \leq C$，那么 $i$ 点和 $j$ 点也就属于同一个群。如果不满足第一个不等式，那么 $i$ 和 $j$ 就不会合并；如果不满足第二个不等式，那么 $j$ 就不会和 $k$ 合并。那么 $i$ 和 $j$ 就不会在一个群中了。



------------


对于快速求出所有满足 $|x_i-x_j| \leq C$ 的点。就可以先将所有点按 $x_i$ 的大小排序，然后每一次插入时把最小的不满足要求的点删去即可（有点类似于单调队列的思想）。

对于求 $y_i$ 的前缀和后继，可以用 ~~set~~ 平衡树来维护。

最终的时间复杂度就为 $O(n \log n)$。

还有一些细节见代码。

## code：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
const int N=1e5+10;
const int INF=2e9+10;//题目中的点最大为2e9 
struct tree{
	int son[2],val,cnt,f,id;//题目中可能会出现y的值相同的点 
}tr[N];
struct bot{
	int x,y,id; 
	bool operator <(const bot &t)const{
	    return x<t.x;
	}
}a[N];
int n,c,fa[N],siz[N],num,root;
int ans1,ans2;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);} //路径压缩 
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
	ans1--;
	if(siz[fx]>siz[fy]) fa[fy]=fx,siz[fx]+=siz[fy];//按秩合并 
	else fa[fx]=fy,siz[fy]+=siz[fx];
}
int newnode(int val,int id) //Treap 的基本操作 
{
	tr[++num].cnt=1;
	tr[num].val=val;
	tr[num].id=id;
	tr[num].f=rand();
	return num;
}
void rotate(int &p,int d)
{
	int q=tr[p].son[d^1];
	tr[p].son[d^1]=tr[q].son[d],tr[q].son[d]=p;
	p=q;
}
void insert(int &p,int val,int id)
{
	if(!p)
	{
		p=newnode(val,id);
		return ;
	}
	if(val<tr[p].val) //本题要求将相同的点也用不同的编号记录 
	{
		insert(tr[p].son[0],val,id);
		if(tr[p].f<tr[tr[p].son[0]].f) rotate(p,1);
	}
	else
	{
		insert(tr[p].son[1],val,id);
		if(tr[p].f<tr[tr[p].son[1]].f) rotate(p,0);
	}
}
void build_tree()
{
	newnode(-INF,0),newnode(INF,0);
	root=1;
	tr[1].son[1]=2;
	if(tr[1].f<tr[2].f) rotate(root,0);
	insert(root,a[1].y,a[1].id);//第一个点可以特判一下，因为y可能会相同 
}
void remove(int &p,int val)
{
	if(val==tr[p].val)
	{
		if(tr[p].son[0]+tr[p].son[1]==0) p=0;
		else if(tr[p].son[0]*tr[p].son[1]==0) p=tr[p].son[0]+tr[p].son[1];
		else
		{
			if(tr[tr[p].son[0]].f>=tr[tr[p].son[1]].f) rotate(p,1),remove(tr[p].son[1],val);
			else rotate(p,0),remove(tr[p].son[0],val);
		}
		return ;
	}
	if(tr[p].val<val) remove(tr[p].son[1],val);
	else if(tr[p].val>val) remove(tr[p].son[0],val);
}
int get_pre(int p,int val)//这里返回的是节点编号而不是具体的值，因为还要用到该点的编号 
{
	if(!p) return 0;
	if(tr[p].val>val) return get_pre(tr[p].son[0],val);
	int k=get_pre(tr[p].son[1],val);
	if(!k) return p;//如果没有右子树，就返回自身 
	return k;// k是在右子树中的最大值，那么显然当k存在时，tr[k].val才是val的前驱 
}
int get_nex(int p,int val) 
{
	if(!p) return 0;
	if(tr[p].val<val) return get_nex(tr[p].son[1],val);
	int k=get_nex(tr[p].son[0],val);
	if(!k) return p;
	return k;
}
int main()
{
	srand((unsigned int)time(0));
	//freopen("233.in","r",stdin);
	scanf("%d%d",&n,&c);
	for(int x,y,i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		a[i].x=(x+y),a[i].y=(x-y),a[i].id=i;//坐标转换，当前节点的编号在合并时会用到 
		fa[i]=i,siz[i]=1;
	}
	sort(a+1,a+n+1);
	build_tree();
	int pos=1;
	ans1=n;
	for(int i=2;i<=n;i++)
	{
	    while(a[i].x-a[pos].x>c) remove(root,a[pos++].y);//删去不符合要求的点 
		int pre=get_pre(root,a[i].y),nex=get_nex(root,a[i].y);
		if(a[i].y-tr[pre].val<=c) merge(a[i].id,tr[pre].id);//这里别忘了判断 
		if(tr[nex].val-a[i].y<=c) merge(a[i].id,tr[nex].id);//如果不用原来的编号来合并，就会出现错误 
		ans2=max(ans2,siz[fa[a[i].id]]);//注意 fa[a[i].id] 才是当前点所在的并查集的编号 
		insert(root,a[i].y,a[i].id);//别忘了加入当前点 
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
} 
```


---

## 作者：tommymio (赞：1)

首先将距离转化成切比雪夫距离，将点 $(x,y)$ 变为 $(x',y')$，其中 $x'=x+y,y'=x-y$。

画一画图，发现 $\max(|x_i-x_j|,|y_i-y_j|)\leq C$ 这个限制框定了一个正方形，如果枚举 $(x_i,y_i)$，则需要向这个正方形内每个点 $(x_j,y_j)$ 连一条边。但是这样会造成重复连边，无法承受。

冷静思考过后，发现它只要求连通性，所以可以去掉一些冗余的边。具体来说，将点按横坐标排序后，设当前枚举的点为 $(x,y)$，仅将点 $(x,y)$ 与 $(x_1,y_1),(x_2,y_2)$ 连边，其中 $x-C\leq x_1,x_2\leq x+C$，$y_1$ 是 $y$ 的前驱且 $y-C\leq y_1\leq y+C$，$y_2$ 是 $y$ 的后继且 $y-C\leq y_2\leq y+C$。正确性基于题中定义的群这一概念具有传递性。

```cpp

#include<cstdio>
#include<algorithm>
#include<functional>
#include<set>
#define int ll
#define mp(x,y) std::make_pair(x,y)
typedef long long ll;
typedef std::pair<ll,ll> pr;
std::multiset<pr> s;
struct node {
	int x,y;
}a[100005];
int size[100005],fa[100005],q[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();} 
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline bool cmp(const node &x,const node &y) {return x.x<y.x;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline void merge(int x,int y) {
	int fx=find(x),fy=find(y);
	if(fx!=fy) {
		size[fx]+=size[fy];
		fa[fy]=fx;
	}
}
signed main() {
	int n=read(),lim=read(),tot=0,mx=0;
	int hd=1,tl=0;
	for(register int i=1;i<=n;++i) {
		int x=read(),y=read(); 
		fa[i]=i; size[i]=1;
		a[i].x=x+y; a[i].y=x-y; 
	}
	std::sort(a+1,a+1+n,cmp);
	s.insert(mp(1ll<<52,0));
	s.insert(mp(-(1ll<<52),0));
	int cur=1;
	for(register int i=1;i<=n;++i) {
   		while(hd<=tl&&a[q[hd]].x<a[i].x-lim) {//x_j<x_i-lim x_j>=x_i-lim
			std::multiset<pr>::iterator it=s.lower_bound(mp(a[q[hd]].y,0));
			s.erase(it); ++hd;
		}
		std::multiset<pr>::iterator it=s.lower_bound(mp(a[i].y,0));
		if(it->first-a[i].y<=lim) merge(it->second,i);
		--it;
		if(a[i].y-it->first<=lim) merge(it->second,i);
		s.insert(mp(a[i].y,i)); q[++tl]=i;
	}
	for(register int i=1;i<=n;++i) {
		if(fa[i]==i) {
			++tot;
			mx=max(mx,size[i]);
		}
	}
	printf("%lld %lld\n",tot,mx);
	return 0;
}
```




---

## 作者：koukilee (赞：0)

## 题意

共 $n$ 头奶牛，分布在二维平面。

两只奶牛的曼哈顿距离不超过 $C$，即 $|X_i - x_i| + |Y_i - y_i| \leq C$。将两只奶牛合并入一个【群】。

如果两个群有同样的奶牛，那么合并两个【群】。

给定奶牛的位置和距离 $C$，确定【群】的数量和最大的【群】中的奶牛数量。

## 思路

看到这里，你们想到什么？

二维平面？最近点？最远点？很显然的思路，我们想到一种暴力数据结构 K-D Tree。

如果你不知道 K-D Tree 是什么，那么我推荐一下我的[博客](https://www.luogu.com.cn/article/pg2fiq96) /kk。

对于此题来说，具体操作如下：

1. 暴力建出 $n$ 个点的 K-D Tree。
2. 对于每一个点，我们进入树中查询，对于距离 $\le c$ 的点，我们使用并查集合并到一起。

主要部分：

```c++
void query (i64 u, i64 v) noexcept {
	if (!u) return;
	
	i64 d = Dis (u, v);
	if (d <= c) s[find (u)] = find (v);
	
	query (tree[u].ls, v), query (tree[u].rs, v);
}
```

这样的复杂度为 $O(n^2)$，并未发挥到 K-D Tree 的作用，所以我们需要加上剪枝函数。

剪枝 1：

如果左右子树内的**最小**值比 $c$ 小，说明子树内有需要更新的点，就继续递归。否则返回。

这个思路类似于[平面最近点对](https://www.luogu.com.cn/problem/P1429)。

于是，代码长这样：

```c++
inline i64 getmin (i64 x, i64 v) noexcept {
	i64 res = 0;
	if (tree[v].x < tree[x].l) res += tree[x].l - tree[v].x;
	if (tree[v].x > tree[x].r) res += tree[v].x - tree[x].r;
	if (tree[v].y < tree[x].d) res += tree[x].d - tree[v].y;
	if (tree[v].y > tree[x].u) res += tree[v].y - tree[x].u;
	return res;
}

void query (i64 u, i64 v) noexcept {
	if (!u) return;
	
	i64 d = Dis (u, v), lv = getmin (tree[u].ls, v), rv = getmin (tree[u].rs, v); /*查找的点到左右两边子树的最小值*/
	if (d <= c) s[find (u)] = find (v);
	
	if (lv <= c) query (tree[u].ls, v);
	if (rv <= c) query (tree[u].rs, v);
}
```

期望得分：86pts。

剪枝 2：

如果左右子树内的**最大**值都比 $c$ 小，那么说明整颗子树是可以合并到一起的。

直接取出子树内的点，暴力合并到一起，并打一个 Tag ，使得后面不需要再次遍历即可。

```c++
inline i64 getmin (i64 x, i64 v) noexcept {
		i64 res = 0;
		if (tree[v].x < tree[x].l) res += tree[x].l - tree[v].x;
		if (tree[v].x > tree[x].r) res += tree[v].x - tree[x].r;
		if (tree[v].y < tree[x].d) res += tree[x].d - tree[v].y;
		if (tree[v].y > tree[x].u) res += tree[v].y - tree[x].u;
		return res;
	}
	
	inline i64 getmax (i64 k, i64 v) noexcept {
		i64 l = tree[k].l, r = tree[k].r, u = tree[k].u, d = tree[k].d, x = tree[v].x, y = tree[v].y;
		return std::max ({std::abs (l - x) + std::abs (d - y), std::abs (l - x) + std::abs (u - y),
						  std::abs (r - x) + std::abs (d - y), std::abs (r - x) + std::abs (u - y)});
	}
	
	void query (i64 u, i64 v) noexcept {
		if (!u) return;
		
		i64 d = Dis (u, v), lv = getmin (tree[u].ls, v), rv = getmin (tree[u].rs, v);
		if (d <= c) s[find (u)] = find (v);
		
		if (vis[u]) return; /*子树内的点被合并到一起，没必要一个个合并*/
		
		if (getmax (u, v) /*子树内距离查找的点最远的点的距离*/ <= c) {
			num = 0; Get (u); i64 tv = find (v); /*暴力拿出来*/
			for (i32 i = 1; i <= num; i++)
				s[find (del[i])] = tv; /*直接合并*/
			vis[u] = 1; /*打上标记*/
			return;
		}
		
		if (lv <= c) query (tree[u].ls, v);
		if (rv <= c) query (tree[u].rs, v);
	}
```

期望得分：100pts。

****

最大的点跑了 $321ms$ 完全可过。

时间复杂度接近 $O(n\sqrt n)$ 但是并不是正确解法，应该可以被卡到 $O(n^2)$。

[Code](https://www.luogu.com.cn/record/194826508)

---

## 作者：Kketchup (赞：0)

### [[USACO08OPEN] Cow Neighborhoods G](https://www.luogu.com.cn/problem/P2906)

- 并查集

**Sol:** 限制一是曼哈顿距离，不方便处理，套路性地考虑转化为切比雪夫距离，则原来的点 $(x,y)$ 变成了 $(x+y,x-y)$，看做把坐标轴旋转了 $45\degree$。那么限制变为 $\max(|X_i-x_i|,|Y_i-y_i|)\le C$。

再看到限制二，邻居的关系是有传递性的，很容易想到用并查集维护联通性，那么社区数量就是联通块数量，最大社区就是最大联通块大小。

重新观察限制一的式子，我们要满足两维的条件，可以模仿**二维偏序**，通过排序处理一维，用数据结构处理另一位。具体地，将坐标以 $x_i$ 第一关键字，$y_i$ 第二关键字排序，然后数据结构处理 $y_i$。这样，我们做到 $i$ 的操作时，先把 $x_i-x_j\ge C$ 的点 $j$ 删除，由排序保证的单调性，这些被删除的点一定不满足 $i$ 之后的点的条件。朴素的想法是将数据结构中的每个点与 $y_i$ 判断，但这样做是平方的。其实只需要找到 $y_i$ 的前驱和后继。判断是否满足 $|Y-y_i|\le C$ 合并即可。

证明：先考虑 $y_i$ 的后继部分，设后继为 $a$，满足了 $y_a-y_i\le C$，考虑任意一个 $y_b\ge y_a$ 的 $b$，若 $y_b-y_i\le C$，则会在朴素做法时直接与 $y_i$ 合并，但注意到三个条件 $y_b-y_i\le C$，$y_a-y_i\le C$，$y_b\ge y_a$，所以 $y_b-y_a\le C$。也就是说，后续的操作中会将 $y_b$ 和 $y_a$ 合并，不用在本次合并。前驱部分的证明同理。

数据结构可以平衡树，使用 set 更加简洁，注意边界问题，可以加入极大值和极小值防止越界。时间复杂度 $O(n\log n\cdot\alpha(n))$。

附上双倍经验题：[[TJOI2012] 炸弹](https://www.luogu.com.cn/problem/P5193)。

**Idea:** 先套路性转化距离，然后把类比处理偏序问题处理本题的二维限制。观察到后续会进行的合并简化合并，优化复杂度。

```cpp
const int N=2e5+10,mod=998244353;
#define int ll
int n,d,tot;
struct node{
	int x,y,id;
}a[N];
bool operator<(node a,node b){return a.y<b.y;}
multiset<node> s;
int fa[N],v[N];
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy){
		v[fy]+=v[fx];
		fa[fx]=fy;
		tot--;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>d;
	tot=n;
	for(int i=1,x,y;i<=n;++i){
		cin>>x>>y;
		v[i]=1;
		a[i].x=x+y;
		a[i].y=x-y;
		a[i].id=fa[i]=i;
	}
	sort(a+1,a+1+n,[](node a,node b){return a.x<b.x;});
	int head=1;
	node p;
	p.x=0,p.y=1e10,p.id=0;
	s.insert(p);
	p.x=0,p.y=-1e10,p.id=0;
	s.insert(p);
	s.insert(a[1]);
	for(int i=2;i<=n;++i){
		while(a[i].x-a[head].x>d) s.erase(s.find(a[head])),head++;
		auto it=s.lower_bound(a[i]);
		p=*it;
		if(p.y-a[i].y<=d) merge(p.id,a[i].id);
		p=*--it;
		if(a[i].y-p.y<=d) merge(p.id,a[i].id);
		s.insert(a[i]);
	}
	cout<<tot<<" "<<*max_element(v+1,v+1+n)<<endl;
	return 0;
}
```

---

## 作者：Rain_chr (赞：0)

前言：本题解为乱搞做法，不过我感觉非常的 interesting，所以还是供后人参考。

强烈谴责双倍经验省选出题人不负责，裸的乱搞直接冲过去了，卡都不带卡的。

我们观察曼哈顿距离的式子 $|x_i-x_j|+|y_i-y_j|\le c$，按 $x_i$ 排序之后感觉只能通过直接连边连通的点对不会太远，于是暴力往后找 $1000$ 个判断是否能够连边，并查集维护连通性即可。

这个简单的暴力直接冲过了 TJOI2012，如果你是场上选手想到这个就赚飞了！即使是在特意卡了这种做法的 USACO 题目上交这份暴力，你也能够获得 86 分的好成绩！

接下来，就要有理由据的乱搞了，请卸下你的理智观看后文。

首先，凭直觉也许出题人会对着曼哈顿距离卡，于是把他转成切比雪夫距离之后再排序，虽然这样得分减少了一分，但是过的点不一样，拼起来就只剩下一个数据点，以及事实证明最远需要直接连通的点在序列中的位置相差变小了。

然后我想到了二维曼哈顿距离较优生成树的求解算法——莫队，如果出题人要卡之前的暴力，必然会把 $x_i,x_j$ 距离调近，把 $y_i,y_j$ 距离调远，在莫队的排序方法下可以很好的避免被这种数据卡爆，这个方法果然过了剩下的一个点，但是前面的又 WA 了。

这下简单了，我们把以切比雪夫距离为理论基础的乱搞和莫队乱搞拼一下，就拿到 100 分的好成绩了。

不过建议还是学习一下正解，感觉性质很厉害。

---

## 作者：cqbzlzm (赞：0)

摘抄自[我的博客](https://www.luogu.com.cn/article/ur9n70t7)

先把曼哈顿距离转换为切比雪夫距离，然后按照 $x$ 坐标排序，用指针维护一个 $x$ 坐标差小于等于 $C$ 的区间，然后用 `set` 来维护 $y$。显然每次我们合并在 $y$ 上的前驱后继即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5;
struct node {
    int x, y;
    friend bool operator < (node a, node b) {
        return a.x < b.x || a.x == b.x && a.y < b.y;
    }
}a[MAXN + 5];
int n, C;
int fa[MAXN + 5], cnt[MAXN + 5];
set<node> s;
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
bool merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return 0;
    fa[fx] = fy;
    cnt[fy] += cnt[fx];
    return 1;
}
signed main() {
	scanf("%lld%lld",&n, &C);
	for (int i = 1; i <= n; i ++) {
		int x, y;
		scanf("%lld%lld", &x, &y);
		a[i] = {x + y, x - y};
	}
    for (int i = 1; i <= n; i ++) fa[i] = i, cnt[i] = 1;
    sort(a + 1, a + 1 + n);
	s.insert((node){-(1ll<<60), 0}), s.insert((node){(1ll<<60), 114514});
	s.insert((node){a[1].y, 1});
    int L = 1;
	for (int i = 2; i <= n; i ++) {
		while (a[i].x - a[L].x > C) s.erase(s.lower_bound((node){a[L].y, L})), L ++;
		auto it = s.lower_bound((node){a[i].y, 0});
		if (it->x - a[i].y <= C) merge(i, it->y);
		-- it;
		if (a[i].y - it->x <= C) merge(i, it->y);
		s.insert((node){a[i].y, i});
	}
	int ans = 0, mx = 0;
	for (int i = 1; i <= n; i ++)
        if(find(i) == i) {
            ans ++;
            mx = max(mx, cnt[i]);
        }
	printf("%lld %lld",ans, mx);
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

### 思路

首先将曼哈顿距离换成切比雪夫距离，原来坐标系上的点 $(x,y)$，换成 $(x+y,x-y)$，距离计算公式为 $\max(x_1 - x_2,y_1 - y_2)$。

然后将所有的点按照横坐标为第一关键字，纵坐标为第二关键字排序，使用双指针，当指针 $i$ 指在某个点时，指针 $j$ 指在最左边的满足 $|x_i - x_j|\leq C$ 的点上。

记录一个 multiset 维护 $[j,i)$ 之间的所有点的纵坐标。

每次将 $i$ 与 multiset 中纵坐标比它大的最接近它的点及纵坐标比它小的最接近它的点应并查集连接。

于是就可以用并查集解决了。

### 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e5 + 10;
int p[N];

int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}

void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	p[x] = y;
}

int main() {
	int n, c;
	scanf("%d%d", &n, &c);
	vector<pair<int, int>> v;
	for (int i = 1; i <= n; i ++ ) p[i] = i;
	for (int i = 0; i < n; i ++ ) {
        int x, y;
		scanf("%d%d", &x, &y);
		v.push_back({x + y, x - y});
	}
	sort(v.begin(), v.end());
	multiset<pair<int, int>> s;
	for (int i = 0, j = 0; i < n; i ++ ) {
		while (j < i && v[i].fi - v[j].fi > c) {
			s.erase(s.find({v[j].se, j}));
			j ++ ;
		}
        if (s.size()) {
            auto it = s.lower_bound({v[i].se, i});
            if (it != s.end() && abs((*it).fi - v[i].se) <= c) merge(i + 1, (*it).se + 1);
            if (it != s.begin()) {
                -- it;
                if (abs((*it).fi - v[i].se) <= c) merge(i + 1, (*it).se + 1);
            }
        }
        s.insert({v[i].se, i});
	}
	int ans = 0, cnt = 0;
	vector<int> w(n + 1);
	for (int i = 1; i <= n; i ++ ) w[find(i)] ++ ;
	for (int i = 1; i <= n; i ++ ) {
		if (find(i) == i) {
			ans = max(ans, w[i]);
			cnt ++ ;
		}
	}
	printf("%d %d", cnt, ans);
	return 0;
}

```

---

## 作者：Sshenyyyu (赞：0)

看了前几篇题解，感觉还是有点东西没讲清楚

这题首先把曼哈顿距离转为切比雪夫距离

对于牛群的合并操作，难道要两两合并吗？那样太慢了，其实，我们对于每个点，只要把它与两个点相并就行了

然后我们将x值排序，我们对于每一个点i，我们把它与y值比它大或相等且相距不超过y的任意点合并，比它小的也找一个，那么为什么可以这样做呢？？

我们可以发现，我们选的这两个点，已经把i的右半边覆盖了，在以后的操作中，i也就没用了，由于属于同一个集合，我们可以用这两点代替i，又由于i是从左往右扫的，所以i的左半边已完成合并，可以忽略了

我们可以用set来实现上述操作

Code：
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
int n,i,c,r,f[100005],ans[100005],mx;
struct str{
	int x,y;
}a[100005];
int Find(int x)
{
	if(f[x]==0)
		return x;
	return f[x]=Find(f[x]);
}
void uniot(int u,int v)
{
	int x=Find(u),y=Find(v);
	if(x!=y)
		f[x]=y;
}
bool cmp(str a,str b)
{
	return a.x<b.x;
}
struct node{
	int a,x;
	bool operator <(const node &u)const
	{
		if(u.a==a)
			return u.x<x;
		return u.a<a;
	}
};
set<node> t;
set<node>::iterator u,v;
int main(){
	scanf("%d %d",&n,&c);
	for(i=1;i<=n;i++)
	{
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i]=(str){a[i].x+a[i].y,a[i].x-a[i].y};
	}
	sort(a+1,a+1+n,cmp);
	r=1;
	for(i=1;i<=n;i++)
	{
		while(r<=n&&a[r].x-a[i].x<=c)
		{
			t.insert((node){a[r].y,r});
			r++;
		}
		t.erase((node){a[i].y,i});
		if(t.size()==0)
			continue;
		u=t.upper_bound((node){a[i].y,0});
		v=u;
		if(u!=t.begin())
		{
			u--;
			if(abs(u->a-a[i].y)<=c)
				uniot(u->x,i);
		}
		if(v!=t.end())
			if(abs(v->a-a[i].y)<=c)
				uniot(v->x,i);
	}
	for(i=1;i<=n;i++)
	{
		ans[Find(i)]++;
		if(f[i]==0)
			mx++;
	}
	printf("%d ",mx);
	mx=0;
	for(i=1;i<=n;i++)
		mx=max(mx,ans[Find(i)]);
	printf("%d",mx);
}

```

---

