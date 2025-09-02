# [USACO20JAN] Wormhole Sort S

## 题目描述

Farmer John 的奶牛们已经厌倦了他对她们每天早上排好序离开牛棚的要求。她们刚刚完成了量子物理学的博士学位，准备将这一过程搞快点。

今天早上，如同往常一样，Farmer John 的 $N$ 头编号为 $1 \ldots N$ 的奶牛（$1 \leq N \leq 10^5$），分散在牛棚中 $N$ 个编号为 $1 \ldots N$ 的不同位置，奶牛 $i$ 位于位置 $p_i$。但是今天早上还出现了 $M$ 个编号为 $1 \ldots M$ 的虫洞（$1 \leq M \leq 10^5$），其中虫洞 $i$ 双向连接了位置 $a_i$ 和 $b_i$，宽度为 $w_i$（$1\le a_i,b_i\le N, a_i\neq b_i, 1\le w_i\le 10^9$）。

在任何时刻，两头位于一个虫洞两端的奶牛可以选择通过虫洞交换位置。奶牛们需要反复进行这样的交换，直到对于 $1 \leq i \leq N$，奶牛 $i$ 位于位置 $i$。

奶牛们不想被虫洞挤坏。帮助她们最大化被她们用来排序的虫洞宽度的最小值。保证奶牛们有可能排好序。

## 说明/提示

### 样例解释 1

以下是一个仅用宽度至少为 9 的虫洞给奶牛排序的可能方案：

- 奶牛 1 和奶牛 2 使用第三个虫洞交换位置。
- 奶牛 1 和奶牛 3 使用第一个虫洞交换位置。
- 奶牛 2 和奶牛 3 使用第三个虫洞交换位置。

### 子任务

- 测试点 $3 \sim 5$ 满足 $N,M \leq 1000$。
- 测试点 $6 \sim 10$ 没有额外限制。

## 样例 #1

### 输入

```
4 4
3 2 1 4
1 2 9
1 3 7
2 3 10
2 4 3```

### 输出

```
9```

## 样例 #2

### 输入

```
4 1
1 2 3 4
4 2 13```

### 输出

```
-1```

# 题解

## 作者：houzhiyuan (赞：31)

# [USACO20JAN]Wormhole Sort S
显然就是一个模板题了。

题意就是说有n个虫洞，在两个地方传送，现在问你让所有的奶牛都到自己的地方所穿过的虫洞宽度最小的最大值是多少。

抓住关键信息：

**1.一个虫洞如果确定了要经过，那么就可以无限经过这个虫洞**

**2.当确定一个虫洞要经过之后，宽度比他大的虫洞都可以经过**

每条边都可以无限次穿过，并且要判断两个地方是否有联通性，显然就对应了一个数据结构——并查集

所以可以得到一个暴力代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[100001],a[100001];
bool ff;
inline void read(int &x){   //复古Pascal版快读
	x=0;int f=1;char s=getchar();
	for(;s<'0'||s>'9';s=getchar()) if(s=='-') f=-1;
	for(;s>='0'&&s<='9';s=getchar()) x=(x<<3)+(x<<1)+s-48;
	x*=f;
}
struct hzy{
    int x,y,z;   //x，y表示相连接的两点，z表示宽度
}cow[100005];
int zuxian(int k){//查找祖先，可以简化为return f[k]==k?k:f[k]=zuxian(f[k]);
	if(f[k]==k){
		return k;
	}
	else{
		return f[k]=zuxian(f[k]);
	}
}
bool mycmp(hzy a,hzy b){
	return a.z>b.z;//先用宽度大的边
}
int main(){
	read(n);
	read(m);
	ff=0;
	for(int i=1;i<=n;i++){
		f[i]=i;
		read(a[i]);
		if(a[i]!=i){
			ff=1;
		}
	}
	if(ff==0){//如果不需要移动
		cout<<-1<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++){//无需解释的读入
		read(cow[i].x);
		read(cow[i].y);
		read(cow[i].z);
	}
	sort(cow+1,cow+m+1,mycmp);
	for(int i=1;i<=m;i++){//并查集过程
		int x1=zuxian(cow[i].x);
		int x2=zuxian(cow[i].y);
		if(x1!=x2){
			f[x1]=f[x2];
		}
		ff=0;
		for(int j=1;j<=n;j++){//判断每个奶牛是否可以到自己的位置上
			if(zuxian(a[j])!=zuxian(j)){
				ff=1;
			}
		}
		if(ff==0){//如果都满足要求，直接输出
			cout<<cow[i].z<<endl;
			return 0;
		}
	}
	return 0;
}
```

然而。。。悲惨TLE。

![](https://cdn.luogu.com.cn/upload/image_hosting/3u6mhbxr.png)

毕竟时间复杂度是$O(nm+mlogm)$，考虑怎么优化

还可以得到一个性质：当一个点已经满足要求时，那么在加边还是满足要求，那么就不需要每次都判断一下，只需要统计一下即可，时间复杂度$O(n+m+mlogm)$

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[100001],a[100001];
bool ff;
inline void read(int &x){
	x=0;int f=1;char s=getchar();
	for(;s<'0'||s>'9';s=getchar()) if(s=='-') f=-1;
	for(;s>='0'&&s<='9';s=getchar()) x=(x<<3)+(x<<1)+s-48;
	x*=f;
}
struct hzy{
    int x,y,z;
}cow[100005];
int zuxian(int k){
	if(f[k]==k){
		return k;
	}
	else{
		return f[k]=zuxian(f[k]);
	}
}
bool mycmp(hzy a,hzy b){
	return a.z>b.z;
}
int main(){
	read(n);
	read(m);
	ff=0;
	for(int i=1;i<=n;i++){
		f[i]=i;
		read(a[i]);
		if(a[i]!=i){
			ff=1;
		}
	}
	if(ff==0){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++){
		read(cow[i].x);
		read(cow[i].y);
		read(cow[i].z);
	}
	sort(cow+1,cow+m+1,mycmp);
   int j=1;
	for(int i=1;i<=m;i++){
		int x1=zuxian(cow[i].x);
		int x2=zuxian(cow[i].y);
		if(x1!=x2){
			f[x1]=f[x2];
		}
		while(zuxian(j)==zuxian(a[j])){//唯一的不同在这里，看似while在for里面，其实是并列关系
			j++;
		}
		if(j>n){
			cout<<cow[i].z<<endl;
			return 0;
		}
	}
	return 0;
}

```
**求管理大大通过，~~蒟蒻求赞~~**

---

## 作者：FourteenObsidian (赞：12)

这题思路还是比较简单的。

注意到"**最大化**被她们用来排序的虫洞宽度的**最小值**"，

很容易想到二分答案。

又因为要使"**奶牛 i 位于位置 i**"，

所以考虑用并查集维护。

首先对所有虫洞按宽度从大到小排序，

接着二分所用的虫洞宽度的最小值，

判断函数中将可使用的虫洞连接的两个位置编号合并，

最后判断是否所有 错位的奶牛所在的编号 都与 她们自己的编号 在一个集合里就行了（可以用类似~~基础的~~冒泡排序的思想证明：对于一个覆盖了 一些错位的奶牛的编号及这些奶牛们所在地编号的集合（可将其转化为在一条链上），每次都可以通过若干次操作将一个编号为链首编号的奶牛传送到链首，再将其从集合中删去，多次这样操作就可以使这个集合里所有的奶牛回到原位）。

最后输出答案。

复杂度$O(nlogn)$ 

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Hole
{
	int a,b,w;
}h[N];
int n,m,l = 0x3f3f3f3f,r = -1,mid,ans,dtot = 0;
int p[N],disl[N],f[N];
bool flag = 0;
bool cmp(Hole x,Hole y) {return x.w > y.w;}
int getfather(int x) {return x == f[x] ? x : f[x] = getfather(f[x]);}
inline bool check(int x)
{
	for(int i = 1; i <= n; ++i)
		f[i] = i;//每次都要重新初始化
	for(int i = 1; i <= m && h[i].w >= x; ++i)
	{
		int fa = getfather(h[i].a),fb = getfather(h[i].b);
		f[fa] = fb;//将这个虫洞连接的两地合并
	}
	for(int i = 1; i <= dtot; ++i)
		if(getfather(p[disl[i]]) != getfather(disl[i]))
        	return 0;//如果仍然有无法回到原位的就返回假
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d",&p[i]);
		if(p[i] != i)//节省时间，只有错位了的奶牛才加入计算
		{
			flag = 1;//判断是否有错位的
			disl[++dtot] = i;
		}
	}
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d",&h[i].a,&h[i].b,&h[i].w);
	sort(h + 1, h + m + 1, cmp);//排序
	l = h[m].w,r = h[1].w;//二分上下界分别为最大和最小的虫洞宽度
	if(!flag)//如果没有错位的直接输出-1
	{
		puts("-1");
		return 0;
	}
	while(l <= r)//二分所用虫洞的最小宽度
	{
		mid = (l + r) >> 1;
		if(check(mid))
		{
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：PersistentLife (赞：8)

这题主要用到的算法：并查集。

### 什么是并查集

我们先来看一下什么是并查集：

#### 作用

举个例子，如果我们把球队比作集合，把球员比作集合中的元素，如果要查询两名球员是否在同一个集合里，那么就可以用并查集快速解决。

大家肯定猜到并查集的用处了，就是可以快速查询某两个元素是否在同一个集合。

#### 如何存储

最常用的存储方式就是“森林存储法”，即将每个集合存成一棵树，那么多个集合就成了一个“森林”。

#### 代码实现

并查集主要有两个函数，一个是 $find$ 函数，即找到这个节点的“树根”，其中 $f_i$ 表示 $i$ 所处于的集合，即它的“根”：

```cpp
int find(int x)
{
	if(f[x]==x) return x;
	return find(f[x]);
}
```
但是，这样的时间复杂度很高，我们怎么优化它呢？我们采用“路径压缩”技术：

```cpp
int find(int x)
{
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
```
路径压缩的 $find$ 的时间复杂度接近 $\Theta(1)$

第二个是 $union$ 函数，即将两个集合合并成一个集合：

```cpp
void _union(int x,int y)//防止撞关键字
//x y 表示要合并的两个集合中的某一个元素 
{
	int xx=find(x);
	int yy=find(y);
	//xx yy 表示 x y 的根
	if(xx==yy) return;//如果本来就处于一个集合，那么就不需要合并
	f[xx]=yy; //合并 
} 
```
我们要对它进行优化，每次将高度小的“树”合并到高度大的“树”上，可以优化 $find$ 的复杂度，我们将这种做法叫做“启发式合并”，代码中 $h_i$ 表示 $i$ 元素所在的树的高度：

```cpp
void _union2(int x,int y) 
{
	int xx=find(x);
	int yy=find(y);
	if(xx==yy) return;
	if(h[xx]>h[yy]) f[yy]=xx;//启发式合并
	else
	{
		f[xx]=yy;
		if(h[xx]==h[yy]) h[yy]++;//防止高度一样 
	} 
} 
```

$union$ 函数的时间复杂度接近 $\Theta(1)$

看到这里，大家可以做做 [P1551 亲戚](https://www.luogu.com.cn/problem/P1551) ，这题是并查集的模板。

### 本题做法

**这题不是最小生成树，不是最小生成树，不是最小生成树！！！因为题目要求“最小宽度的最大值”而不是“宽度总和的最大值”。**

本题要用到并查集和一点小小的贪心，每次加入一条最大的边，然后看看是否连通即可，因为本题数据范围较小，所以不需要启发式合并，具体做法详见代码注释。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define maxn 100020
using namespace std;
int f[maxn];
int n,m,arr[maxn];//arr 表示奶牛最初的位置
struct dong
{
	int a,b,w;//a b 为连接的两个节点，w 为宽度
};
dong h[maxn];
int find(int x)
{
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}//并查集之 find
void init()
{
	for(int i=1;i<=n;i++) f[i]=i;
}//初始化，每个节点最初的“根”是自己
bool cmp(dong x,dong y)
{
	return x.w>y.w;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>arr[i];
	for(int i=1;i<=m;i++) cin>>h[i].a>>h[i].b>>h[i].w;
	int ans=-1;
	sort(h+1,h+1+m,cmp);
	int cnt=0,xx,yy;
	init();//读入+排序+初始化
	for(int i=1;i<=m;i++)
	{
		while(find(cnt)==find(arr[cnt]))//判断是否连通 
		{
			cnt++;
			if(cnt>=n)
			{
				cout<<ans;
				return 0;
			}
		}
		xx=find(h[i].a);
		yy=find(h[i].b);	
		if(xx!=yy)//若不连通，则加入这条边 
		{
			f[xx]=yy;
			ans=h[i].w;
		}	
	}
	cout<<ans;//输出
	return 0;//完结撒花
}
```

---

## 作者：Karl_Aurora (赞：7)

#### [~~无耻地推销个人博客qwq~~](https://www.luogu.com.cn/blog/ling-XAIqwq/solution-p6004)

#### [题目传送门](https://www.luogu.com.cn/problem/P6004)

------------

$在开始正题前，先讲个笑话$

> （2021.3.2，某校4机房）
>
> yy：后两题（指USACO20JAN银组）不就是二分氵题吗？
>
> 我：（关掉T1，打开T3）？？？不是一个使最小边权最大的生成树吗？
>
> xhy：蛤？不是并查集板子吗？
>
> yzy：是啊是啊（便乘
>
> 我：？？？就我一个人没看出来是并查集吗？

~~论一个蒟蒻是如何被巨佬们碾压的~~

------------

这道题的题意为对于一个无向图，求每个奶牛从所在位置到其目标位置所经过的边的最小边权的最大值

对于一个求最大/小值的问题，很容易就能想到用二分枚举能经过的边的边权最小值，将求范围转化为求值

这里是二分模板：

```cpp
while (l < r)
{
   mid = (l + r + 1) / 2;
   if (check(mid)) l=mid;
   else r=mid-1;
}
cout << l << endl;
```

想到二分后，接下来便是考虑如何实现```check```函数了

由于我们已经枚举出了所经过边的边权最小值，那么```check```函数的作用便很自然的出来了——检查在所经过边的边权最小值一定的情况下，每个奶牛的所在位置与其目标位置是否连通

既然是求连通性问题，那么本题的另一个核心算法——并查集自然也就出来了

最后，不要忘了检查一开始所有奶牛是否已经在其目标位置上，如果在，需要输出```-1```（这个蒟蒻由于喜欢用```goto```乱跳，所以代码中这个的实现会有些奇怪，大家按照自己平时习惯的写法来即可

------------

接下来，就是你们最喜欢的代码环节qwq

（不要直接抄，会有惊喜，然后完美复刻2021.3.4集训时的我（bushi

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	register int X = 0; bool f = false; char ch = getchar();
	while (ch > '9' || ch < '0') {f |= ch == '-'; ch = getchar();}
	while (ch <= '9' && ch >= '0') {X = (X << 3) + (X << 1) + (ch ^ 48); ch = getchar();}
	return f ? -X : X;
}
inline void write(int X)
{
	if (X == 0) {putchar('0'); return;}
	if (X < 0) {putchar('-'); X = -X;}
	register int cnt = 0, num[20];
	while (X) {num[++cnt] = X % 10; X /=10;}
	while (cnt) putchar(num[cnt--] ^ 48);
	return;
}
struct wormhole
{
	int from, to, w;
}s[100010];
inline bool cmp(wormhole a, wormhole b)
{
	if (a.w != b.w) return a.w > b.w;
	if (a.from != b.from) return a.from < b.from;
	return a.to < b.to;
}
int f[100010], p[100010];
int n, m, a, b, l, r, mid, ans = -1;
int find_father(int x) {if (f[x] == x) return x; return f[x] = find_father(f[x]);}
//路径压缩并查集板子
bool check(int upp)
{
	for (register int i = 1; i <= n; ++i) f[i] = i;
	for (register int i = 1; i <= m; ++i)
	{
		if (s[i].w < upp) break;
		f[find_father(s[i].from)] = find_father(s[i].to);
	}
//	for (register int i = 1; i <= n; ++i) cerr << find_father(f[i]) << " ";
//	cerr << endl;
	for (register int i = 1; i <= n; ++i)
	{
		if (find_father(f[i]) != find_father(f[p[i]])) return false;
	}
	return true;
}
int main()
{
//	freopen("wormsort.in", "r", stdin);
//	freopen("wormsort.out", "w", stdout);
	n = read(); m = read();
	for (register int i = 1; i <= n; ++i) p[i] = read();
	for (register int i = i; i <= m; ++i) {s[i].from = read(); s[i].to = read(); s[i].w = read();}
	for (register int i = 1; i <= n; ++i) if(p[i] != i) goto ck; //检查需不需要交换，如果不需要则输出-1
	printf("-1"); return 0;
	ck:
	sort(s + 1, s + m + 1, cmp);
	l = 1; r = s[1].w;
	while (l < r)
	{
		mid = (l + r + 1) / 2;
		if (check(mid)) {l = mid; ans = mid;}
		else r = mid - 1;
	}
	write(ans);
	return 0;
}
```

------------

至此，543ms，2.12MB，愉快AC！

![](https://cdn.luogu.com.cn/upload/image_hosting/jwlk3enk.png)

最后求赞求资瓷0v0

---

## 作者：KaisuoShutong (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P6004)

# 题目大意

没什么好说的，属于看一遍就懂的那种。

# 题目分析

二分！二分！又是二分！你 $\mathcal{USACO}$ 怎么这么喜欢二分？Loan Repayment 二分完了你也来？

好的我们来看一下。

“最大化最小值”，这种字眼一开口就是老二分了。  
那么问题转化为了判定一些边，满足所有的 $p_i$ 和 $i$ 都能互相到达的个数。  
容易发现这是一个并查集可以解决的问题。  
为什么？看看这张图：  
![bcj.png](https://s1.ax1x.com/2020/08/04/aDAMkR.png)  
如果 $1$ 和 $6$ 可以互达，那么它们一定是共祖先的。  
如此可以做完这道简单题。

自认为好康的~~掐头去尾~~代码

```cpp
int GF(int x) {return f[x]==x?x:f[x]=GF(f[x]);}
bool isok(int mid)
{
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++)
		if(qw[i]>=mid) f[GF(qa[i])]=GF(qb[i]);
	for(int i=1;i<=n;i++)
		if(GF(i)^GF(p[i])) return 0;
	return 1;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=1;i<=m;i++) qa[i]=read(),qb[i]=read(),qw[i]=read();
	int l=0,r=1e9,mid,ans;
	while(l<=r)
	{
		mid=l+r>>1;
		if(isok(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans==1e9?-1:ans);
	return 0;
}
```

---

## 作者：JohnJoeZhu (赞：2)

[传送门](https://www.luogu.com.cn/problem/P6004)

## 解法思考

$1^{st}$ 读题抓题眼

帮助她们**最大化**被她们用来排序的虫洞宽度的**最小值**

- 二分 我们可以二分答案，但是观察到$1≤w_i≤10^9$,说明该方案不可行
- 排序 由于排序后二分的方法和排序后进行下一步操作是~~差不多的（可能会快一些？）~~，所以我选择直接排序



------------

$2^{nd}$ 分析样例，弄清题意

如果我们把每只奶牛视为一个点，虫洞视为边，那么会得出什么结论？
```
样例
4 4
3 2 1 4
1 2 9
1 3 7
2 3 10
2 4 3

以下是一个仅用宽度至少为 9 的虫洞给奶牛排序的可能方案：

奶牛 1 和奶牛 2 使用第三个虫洞交换位置。
奶牛 1 和奶牛 3 使用第一个虫洞交换位置。
奶牛 2 和奶牛 3 使用第三个虫洞交换位置。
```

说明，我们只需要将不在自己位置上的奶牛与目标位置上的奶牛联通即可

通过样例，我们可以得出以下结论：

$i$ 奶牛走到 $p[i]$ 的位置可以转化为 点$i$ 和  点$p[i]$ 连通

我们的目标就是 ：寻找一个方法，使得 点$i$ 和 点$p[i]$ 连通

------------

$3^{rd}$ 深入思考，探索方法

通过样例，我们可以得到

解题的维护内容：

-  $i$ 与 $p[i]$ 的联通情况
-  $p[i]$ 与 $p[j](i,j$可连边$)$的联通情况

-  $i$ 与 $j(i,j$可连边$)$的联通情况

实际上，第二项与第三项是等价的（不用解释了吧）

所以，我们要通过实现第二项或第三项达到 $i$ 与 $p[i]$ 的联通

判联通，我们就用**并查集**

那么我们就可以得出代码了

## 代码及讲解
#### ps:部分代码证明在代码下方
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct pp{
	int x,y,z;
}a[N];
int n,m,p[N],f[N],ans=-1;
bool cmp(pp a1,pp b1){return a1.z>b1.z;}
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
//inline int fine(int x){while(x!=f[x])x=f[x]=f[f[x]];return x;}另一种并查集的路径压缩
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		f[i]=i;
	}
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+1+m,cmp);
	int now=1,fx,fy;
	for(int i=1;i<=m;i++)
	{
		while(find(now)==find(p[now])) 
		{//判断是否达到目标：全部排序
			now++; 
			if(now>n) 
			{
				printf("%d",ans);
				return 0; 
			}
		}
    	if((fx=find(a[i].x))!=(fy=find(a[i].y)))
		{//如果x与y不连通，就加入这条边
      		f[fx]=fy;
      		ans=a[i].z;
		}//证明1
	}
	printf("%d",ans);
	return 0;
}
```
#### 证明1：
在排序的基础上，如果 点$x$ 与 点$y$ 连通后， 点$x$ 与 点$p[x]$ 联通 或 点$y$ 与 点$p[y]$ 联通，就说明这条边对目标有贡献

反之，如果没有贡献，那么这条边是不会计入答案的，因为我们在每一次加边之前都对目标进行了判断

即使计入答案，也证明我们的目标还未达成，所以会有更小的边需要加入，更小的答案需要统计，这条边不会对答案产生影响

------------


第一次AC代码，仅供参考，没有准确性保证（如果你有证明方法，也可以在下方评论）
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct pp{
	int x,y,z;
}a[N];
int n,m,p[N],sum=0,f[N],ans;
bool cmp(pp a1,pp b1){return a1.z>b1.z;}
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int main()
{
	scanf("%d%d",&n,&m);
	bool flag=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		f[i]=i;
		if(p[i]!=i) flag=0,sum++;
	}
	if(flag)
	{
		printf("-1");
		return 0;
	}
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
    		/*while(find(now)==find(p[now])) 
			{
				now++; 
				if(now>n) 
				{
					printf("%d",ans);
					return 0; 
				}
			}*/ //建议加上判断，但是原代码没有加入，仍AC，是否是数据的问题呢？(加入后也AC)
		int fx=find(a[i].x),fy=find(a[i].y);
		if(fx!=fy) 
		{
			if(p[a[i].x]!=a[i].x||p[a[i].y]!=a[i].y) f[fx]=fy,ans=a[i].z;
		}//证明2
	}
	printf("%d",ans);
	return 0;
}
```
##### 证明2（不保证正确，仅供参考）
反证：

在排序的基础上，

如果 奶牛$x$ 与 奶牛$y$ 都在自己的位置上

或 点$x$ 与 点$y$ 已经连通， 

就说明这条边对目标没有贡献，就不加入答案

那么剩下的边，就都对答案有贡献了

#### Update:加入了部分代码的证明

---

## 作者：信守天下 (赞：1)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6004)
## 思路
可以将每个位置看成点，交换操作看成边。

那么为了排序，每个数的当前位置与目标位置必须是连通的。

我们可以由大到小不断增加边，并检查 $N$ 对点之间的连通性，但这样做效率较低。

不难发现，⼀旦对点连通后，增加更多的边不会改变连通性。

所以可以直接⼆分答案求解。

确定了最小代价后，再根据可用的边求图中的连通块，最后再统一进行判定。

## 时空复杂度
令代价的取值范围为 $v$ 。
### 时间：
* 二分答案 $\Theta(\log v)$
* 求连通块 $\Theta(N + M)$
* 校验答案 $\Theta(N)$

总共 **$\Theta((N + M) \log v)$**
### 空间：

储存图 $\Theta(N + M)$
## $code$
~~~cpp
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {   // 边
  int y, w;  // 指向节点，宽度
};

struct V {
  int r;  // 所属连通块标记
  vector<E> p;
} v[kMaxN];

int a[kMaxN];
int n, m, x, y, w, l, r, _r, mid;

void T(int r, int x) {  // x属于连通块r
  if (v[x].r) {         // 已经到达过x
    return;
  }
  v[x].r = r;                                // 标记
  for (int i = 0; i < v[x].p.size(); i++) {  // 寻找邻点
    if (v[x].p[i].w >= mid) {                // 可以通行
      T(r, v[x].p[i].y);
    }
  }
}

bool C() {
  for (int i = 1; i <= n; i++) {  // 初始化连通块标记
    v[i].r = 0;
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].r) {  // 尚未查找的连通块
      T(i, i);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].r != v[a[i]].r) {  // 与要交换的位置不连通
      return 0;
    }
  }
  return 1;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> x >> y >> w;
    v[x].p.push_back({y, w});
    v[y].p.push_back({x, w});
    _r = max(_r, w);  // 跟新上界
  }
  for (l = 1, r = ++_r; l <= r;) {  // 二分答案，上界+1用来判无解
    mid = (l + r) >> 1;
    if (C()) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << (l > _r ? -1 : l - 1);
  return 0;
}
~~~

---

## 作者：ConvaChen (赞：1)

 $2020$  $USACO$ $JAN$ $SILVER$
 
 $WormHole$ $Sort$ 虫洞排序 by JAVA
 
 Credited by ConvaChen
 
 题解思路：
 首先，我们可以发现，如果使得所有区域都取得连通，我们便可以任意的让奶牛行走，换位置。从联通区域的角度，我们便可以想到 _**并查集**_ 这一算法。
 
 
 其次，题目要求边权最大，也就是用最大的边（最宽的worm hole）来使虫洞区域联通。这里可以联想到克鲁斯卡尔的最小生成树。因此我们先将读进来的边进行排序，使用JAVA的Comparator自定义进行排序：
 
 ```java
Arrays.sort(worm, new Comparator<int[]>() {
			@Override
			public int compare(int[] o1, int[] o2) {
			if (o1[2]==o2[2]) return o2[2]-o1[2];
			return o2[2]-o1[2];
			}
			});
```
这块我使用的JAVA二维数组排序，也可以使用class implemented 排序类进行排序。

因此，我们的目标就是使得所有奶牛能够回到其所在的区域，使得这**奶牛现在位置**和**他需要回到的位置**联通。所以，现在就非常简单了，并查集find函数的判定就可以写出来了：
```java
if(find(Fa[j])!=find(Fa[cow[j]]))
```
跟有些C++题解不同，但是这种方法是无需二分，应该是并查集里里面最快的做法。(JAVA亲测不开BufferedReader仅需要4.2s)


这块不多赘述并查集的知识，可以参考之前那几个并查集C++题解。

最后，需要特判-1的情况。上代码：

```java
import java.util.*;
public class WormHoleSort6004 {
	static int n;
	static int m;
	static int[] cow;
	static int[][] worm;
	static int[] Fa;
    //并查集查询
	static int find (int x) {
		if(Fa[x]==x) {
			return x;
		}
		else {
			return Fa[x]=find(Fa[x]);
		}
	}
	static void merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		Fa[fx]=fy;
		return;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		m = in.nextInt();
		cow = new int[n+1];
		worm = new int[m][3];
		Fa = new int[n+1];
        //读入
		for(int i=1;i<n+1;i++) {
			cow[i] = in.nextInt();
			Fa[i]=i;
		}
        //虫洞读入
		for(int i=0;i<m;i++) {
			worm[i][0] = in.nextInt();
			worm[i][1] = in.nextInt();
			worm[i][2] = in.nextInt();
		}
        //排序
		Arrays.sort(worm, new Comparator<int[]>() {
			@Override
			public int compare(int[] o1, int[] o2) {
			if (o1[2]==o2[2]) return o2[2]-o1[2];
			return o2[2]-o1[2];
			}
			});
        //特判-1的情况
		boolean a = true;
		for(int i=1;i<n;i++) {
			if(cow[i]!=i) {
				a = false;
			}
		}
        
		if(a==true) {
			System.out.print(-1);
		}
		else {
		for(int i=0;i<m;i++) {
			boolean flag = true;
			merge(worm[i][0],worm[i][1]);
			for(int j=1;j<n+1;j++) {
//查询奶牛的位置			if(find(Fa[j])!=find(Fa[cow[j]])) {
					flag = false;
					break;
				}
			}
			if(flag==true) {
				System.out.print(worm[i][2]);
				break;
			}
		}
		
		}
	}

}

```


---

## 作者：pocafup (赞：1)

这题真的是非常标准的模板题啊

看到连最少的边,第一时间会想到 $kruskal$ .这道题的难点其实就一个:你要注意到连边权最大的边使整个图联通

为什么:题意是第i个点想走到 $pos[i]$ ,也就是说点i和点 $pos[i]$ 必须要联通.

为什么想不到 $kruskal$ :因为 $kruskal$ 是最小生成树,比较难想到两条边权大的边连起来并不会影响最小权值.

~~扯远了~~进入正题:

1.怎么保证连的边的权值最大:

将边权从大到小排列,需要拿的边尽量拿(因为并不会影响最小权值).

2.怎么查两点是否连通:

这个是 $kruskal$ 算法最基本的要领.如果一个点的父亲 $fat[i]$ 等于另外一个点的父亲 $fat[j]$, 那么我们可以确定这两点连通

3.要连什么点

细心观察会发现,第i个点走到 $pos[i]$ 可以转化为点i和点 $pos[i]$ 连通.

4.怎么判断什么时候全图连通:

因为要求是一定要全部连通才行,所以如果有一个点不连通,后面怎么连通都没用.而如果有一个点连通了,就算后面再怎么连,最后这个点仍然连通.所以,我们可以做一个指针.指针从1开始,表示第一个不连通的点.每次连边之前先确定还有哪条边不连通.如果我们发现连通的点数已经大于总的点数,那么答案就是输出了

上代码:(124ms吊打目前所有解法)

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
inline int read() {
      int x=0,w=1;
      char ch;
      while(ch<'0'||ch>'9')
      {
          if(ch=='-')
              w=-1;
          ch=getchar();
     }
     while(ch>='0'&&ch<='9')
         x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
     return x*w;
 }
int n,m,pos[100005],tot = 0,fat[100005], ans = -1;
struct Edge{
  int from,to,dis;
}edge[300005];
int father(int x){
	while(x!=fat[x]) x=fat[x]=fat[fat[x]];//这个是kruskal的一个加速方法,在查自己的时候可以直接更新父亲
	return x;
}
void Union(int x, int y){
  fat[father(y)] = father(x);
}
void add(int f, int t, int d){
  edge[++tot].from = f;
  edge[tot].to = t;
  edge[tot].dis = d;
}
//不解释
bool sorted(Edge a, Edge b){
  return a.dis>b.dis;//从大到小排列
}
int main(){
  n = read();m = read();
  for (int i=1;i<=n;i++) pos[i] = read();
  for (int i=0;i<m;i++){
    int a,b,c;
    a = read();b = read(); c = read();
    add(a,b,c);//连边
  }
  sort(edge+1,edge+tot+1,sorted);//从大到小排列
  int ptr = 1;
  for (int i=1;i<=n;i++) fat[i] = i;//自己爸爸一开始就是自己
  for (int i=1;i<=tot;i++){
    while(father(ptr)==father(pos[ptr])) {ptr++; if (ptr>n) goto abcd;}//当我爸跟他爸是同一个人就增加,直到我跟他都不存在或者我爸不是他爸
    if (father(pos[edge[i].from])!=father(pos[edge[i].to])){
      Union(pos[edge[i].from],pos[edge[i].to]);//如果他爸不是我爸,那我将我爸设成他爸
      ans = edge[i].dis;//答案就是现在的边权
    }
  }
  abcd:;
  printf("%d",ans);
}

```


---

