# Unusual Minesweeper

## 题目描述

Polycarp 非常喜欢玩扫雷游戏。最近，他发现了一个类似的游戏，也有这样的规则。

场地上有一些地雷，每个地雷的坐标 $(x_i,y_i)$ 都是已知的，每个坐标都有以秒为单位的倒计时，之后地雷就会爆炸。爆炸后，地雷会引爆所有与地雷垂直和水平距离在 $k$ 之内的地雷，结果就是我们得到了形状为"+"的爆炸。而一次爆炸可以引起新的爆炸，每次都是这样。

此外，从 $0$ 秒开始，Polycarp 可以每秒引爆任意一个地雷，连锁反应随之发生。需要注意的是，地雷会立刻爆炸并立刻引爆其它地雷。

Polycarp 想创造一个新纪录，请你帮他计算一下，他最快能在多少秒内引爆所有地雷？

## 样例 #1

### 输入

```
3

5 0
0 0 1
0 1 4
1 0 2
1 1 3
2 2 9

5 2
0 0 1
0 1 4
1 0 2
1 1 3
2 2 9

6 1
1 -1 3
0 -1 9
0 1 7
-1 0 1
-1 1 9
-1 -1 7```

### 输出

```
2
1
0```

# 题解

## 作者：_mi_ka_ (赞：7)

## 题意简述

给定 $n$ 个地雷的坐标及其自动引爆的时间。每个地雷引爆时都会使它的横纵坐标距离的 $k$ 的形状为"+"的范围内 $(x\pm k,y\pm k)$ 的地雷引爆。同时，自 $0$ 秒开始的每秒都可以任意引爆一颗地雷，求所有地雷都引爆的最小时间（即求最后一个地雷引爆的时间）。

## 思路分析

按照贪心的思想，引爆较晚爆炸的地雷会使最后一个地雷引爆的时间提前，对答案有贡献。但是后引爆的地雷可能会被先引爆的地雷引爆，所以不能按时间从后往前引爆。那该用什么方法处理？

同时引爆的几个地雷可以看做一个地雷引爆，那怎么把多个地雷合并成一个地雷呢？

并查集！

于是我们需要将互相能够引爆的几个地雷整到一个集合中，~~两两判断是否在一个集合然后合并即可，和 [P3958 [NOIP2017 提高组] 奶酪](https://www.luogu.com.cn/problem/P3958) 思路大致相同。~~

>$1\le n\le2\times10^5$

$O(n^2)$ 合并显然过不去，合并反而成了个问题。

于是我们发现，当我们以单个坐标为第一关键字，另一个坐标为第二个关键字将这些地雷排序后，只需判断相邻的两个地雷是否能够合并即可。若相邻的两个地雷在此方向不能合并，则与它不相邻的下一个地雷一定也无法合并，因为距离是越来越远的，只有此方向的距离在 $k$ 之内的地雷才能合并。

于是就有了两个方向的合并，$O(n\log n)$ 排序，$O(n)$ 合并。

```cpp
struct coordinate//地雷 
{
	int x,y,t,id;//坐标，引爆时间，地雷编号 
}c[N];

sort(c+1,c+n+1,cmp_x);//以x为第一关键字，y为第二关键字排序 
for(int i=1;i<n;i++)
	if(c[i].x==c[i+1].x&&c[i+1].y-c[i].y<=k)//y方向能够引爆 
		merge(c[i].id,c[i+1].id);
sort(c+1,c+n+1,cmp_y);//以y为第一关键字，x为第二关键字排序 
for(int i=1;i<n;i++)
	if(c[i].y==c[i+1].y&&c[i+1].x-c[i].x<=k)//x方向能够引爆 
		merge(c[i].id,c[i+1].id);
```

在合并地雷之后按照新的地雷引爆时间从大到小开始引爆，直到全部引爆为止时间最小。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int T,n,k,cnt;//cnt是新的地雷数组的计数器 
int fa[N],newc[N];//并查集数组，合并后的新地雷数组，此时地雷互不影响，坐标已没有任何用处，只需一个数组存引爆时间 
map<int,int>vis;//vis的map数组存此集合内的所有地雷在新的地雷数组中的临时编号，若vis值为0则此集合还未加入新的地雷数组 
struct coordinate//地雷 
{
	int x,y,t,id;//坐标，引爆时间，地雷编号 
}c[N];
int re()//朴素的快读 
{
	int x=0,p=1;
	char y=getchar();
	for(;y>'9'||y<'0';y=getchar())
		if(y=='-')
			p=-p;
	for(;y>='0'&&y<='9';y=getchar())
		x=x*10+y-'0';
	return x*p;
}
void wr(int x)//朴素的快写 
{
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		wr(x/10);
	putchar(x%10+'0');
}
int find(int x)//朴素的路径压缩并查集查找操作 
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);//路径压缩 
}
void merge(int x,int y)//朴素的合并操作 
{
	int f1=find(x),f2=find(y);
	if(f1==f2)
		return;
	fa[f1]=f2;
}
bool cmp_x(const coordinate &a,const coordinate &b) 
{
	return (a.x<b.x)||(a.x==b.x&&a.y<b.y);
}
bool cmp_y(const coordinate &a,const coordinate &b)
{
	return (a.y<b.y)||(a.y==b.y&&a.x<b.x);
}
signed main()
{
	T=re();
	while(T--)
	{
		n=re(),k=re();
		cnt=0,vis.clear();//初始化 
		for(int i=1;i<=n;i++)
			fa[i]=i,newc[i]=0x7fffffff;//由于newc存的是最早引爆时间，初始值设为最大值 
		for(int i=1;i<=n;i++)
			c[i].x=re(),c[i].y=re(),c[i].t=re(),c[i].id=i;
		sort(c+1,c+n+1,cmp_x);//以x为第一关键字，y为第二关键字排序 
		for(int i=1;i<n;i++)
			if(c[i].x==c[i+1].x&&c[i+1].y-c[i].y<=k)//y方向能够引爆 
				merge(c[i].id,c[i+1].id);
		sort(c+1,c+n+1,cmp_y);//以y为第一关键字，x为第二关键字排序 
		for(int i=1;i<n;i++)
			if(c[i].y==c[i+1].y&&c[i+1].x-c[i].x<=k)//x方向能够引爆 
				merge(c[i].id,c[i+1].id);
		for(int i=1;i<=n;i++)
		{
			int f=find(c[i].id);//所在集合编号 
			if(!vis[f])//此集合没在新地雷数组中出现过 
				cnt++,vis[f]=cnt;//将此集合所在新地雷数组的编号记录下来 
			newc[vis[f]]=min(newc[vis[f]],c[i].t);//更新最早引爆时间 
		}
		sort(newc+1,newc+cnt+1);//引爆时间排序 
		for(int i=0;i<=cnt;i++)//0时刻开始 
			if(newc[cnt-(i+1)]<=i)//不被手动引爆的最晚引爆的时间比当前时间小 
			{
				wr(i),putchar('\n');
				break;
			}
	}
	return 0;
}
```

---

## 作者：小薛小薛 (赞：2)

## 题意
给定n颗炸弹，每颗炸弹有一个左边x，y以及一个爆炸时间，一个炸弹爆炸会牵引不超过k距离的其它炸弹爆炸（如下图k=2时），每秒可以点燃一个炸弹，问最少多少秒所有炸弹爆炸。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2366128eba8d430da83bf50167633c9e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAVGhYZQ==,size_20,color_FFFFFF,t_70,g_se,x_16)

## 题解
假如没有牵连爆炸这个限制，这道题就变成一个简单的贪心问题，排序每次选择爆炸时间最长的一个点燃，当时间已经比下一个时间长时就是答案，那么有了牵连爆炸的限制后该怎么做呢？其实我们可以把会一起爆炸的炸弹看成一个炸弹，也就可以用并查集来维护，然后它们爆炸的时间就是集合中爆炸时间最短的那个。再之后就变成那个简单的贪心问题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fr first
#define sc second
#define ll long long 
const long long inf = 1e18;
long long n, d, nn, a[200069], dsu[200069], ex[200069];
pair<pair<long long, long long>, long long> as[200069];//存储每颗雷的信息
long long fd(long long x)//并查集
{
	if (dsu[x] != x)
	{
		dsu[x] = fd(dsu[x]);
	}
	return dsu[x];
}
int main()
{
	long long t, rr, i, ii, l, y, x, p, z;

	scanf("%lld", &t);//组数
	for (rr = 0; rr < t; rr++)
	{
		scanf("%lld%lld", &n, &d);//n颗雷 半径为d的地雷会爆炸
		for (i = 1; i <= n; i++)
		{
			scanf("%lld%lld%lld", &x, &y, &a[i]);//a存储下班为i的爆炸时间为i
			as[i] = { {x,y},i };//雷的信息,y,x,第i颗雷
			dsu[i] = i;//并查集初始化
		}
		for (ii = 0; ii < 2; ii++)//两次,一次跑x一次跑y
		{
			sort(as + 1, as + n + 1);//根据第一坐标优先其次第二坐标优先在者编号优先从小到大排序

			for (i = 1; i <= n; i++)
			{
				y = as[i].fr.fr;//x/y
				x = as[i].fr.sc;//y/x
				p = as[i].sc;//当前 编号

				if (i > 1 && y == as[i - 1].fr.fr && x - as[i - 1].fr.sc <= d)//一个坐标相同,另外一个坐标相差为d就为一个集合的雷
				{
					l = as[i - 1].sc;
					a[fd(p)] = min(a[fd(p)], a[fd(l)]);//爆炸时间为较小的那个
					dsu[fd(l)] = fd(p);//合并成一个集合p
				}
			}
			for (i = 1; i <= n; i++)//交换x,y坐标再跑一次
			{
				swap(as[i].fr.fr, as[i].fr.sc);
			}
		}
		//接下来的问题就变成了有nn个爆炸时间不同的雷,每秒可以点爆一个,最快几秒可以点爆完成,贪心的去做,每次都点爆离当前时间最小的一颗雷即可
		nn = 0;
		for (i = 1; i <= n; i++)
		{
			if (fd(i) == i)
			{
				nn++;
				ex[nn] = a[i];
			}
		}
		sort(ex + 1, ex + nn + 1, greater<long long>());
		ex[nn + 1] = -inf;
		for (i = 1; i <= nn; i++)
		{
			if (ex[i + 1] <= i - 1)break;
		}
		printf("%lld\n", i-1);
	}
}

```


---

## 作者：__KevinMZ__ (赞：1)

# 并查集好题
## 并查集
对地雷的 $x,y$ 分别排一次序，相邻两个是否在同一个联通块中。
最短时间从大到小排个序，从大到小引爆即可。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct node{
    int x,y,t,id;
}a[maxn];
int f[maxn],coor[maxn];
bool cmpx(const node&Node,const node&nd){return Node.x==nd.x?Node.y<nd.y:Node.x<nd.x;}
bool cmpy(const node&Node,const node&nd){return Node.y==nd.y?Node.x<nd.x:Node.y<nd.y;}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void merge(int x,int y){x=find(x),y=find(y);f[x]=y;}
int n,k,t,cnt;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        cnt=0;
        for(int i=1;i<=n;i++){
            cin>>a[i].x>>a[i].y>>a[i].t;
            f[i]=a[i].id=i;
            coor[i]=0x7fffffff;
        }
        sort(a+1,a+1+n,cmpx);
        for(int i=1;i<n;i++){
            if(a[i].x==a[i+1].x&&a[i+1].y-a[i].y<=k){
                merge(a[i].id,a[i+1].id);
            }
        }
        sort(a+1,a+1+n,cmpy);
        for(int i=1;i<n;i++){
            if(a[i].y==a[i+1].y&&a[i+1].x-a[i].x<=k){
                merge(a[i].id,a[i+1].id);
            }
        }
        for(int i=1;i<=n;i++){
            // cout<<find(a[i].id)<<" "<<a[i].t<<" ";
            if(coor[find(a[i].id)]==0x7fffffff)cnt++;
            coor[find(a[i].id)]=min(coor[find(a[i].id)],a[i].t);
        }
        sort(coor+1,coor+1+n);
        for(int i=0;i<=cnt;i++){
            if(coor[cnt-(i+1)]<=i)
			{
				cout<<i<<"\n";
				break;
			}
        }
    }
    return 0;
}

```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$
---
### 解题思路：

仅有十字的话处理起来还是非常方便的。考虑将所有的可以相互引爆的雷并成一个雷，引爆的时间就是最早的那一个雷的引爆时间。

然后问题也就转化为了有若干个互不干扰的雷，每一秒可以引爆一个，雷也会在一定的时间之后自动爆炸，求最短的引爆时间。对于转化之后的问题可以直接使用贪心，将所有的雷按照时间排序，从后往前依次手动引爆即可。

---
具体处理雷的合并的时候分横纵坐标分别处理。以横坐标为例，先将所有的雷按照纵坐标第一关键字，横坐标为第二关键字排序，先取出所有的纵坐标相同的雷，维护一个向右的最大可引爆位置，然后顺推即可。可以使用并查集处理合并操作。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct str{
	int x,y,t,id;
	bool operator <(str a){
		if(x==a.x)return y<a.y;
		return x<a.x;
	}
}p[200005],p2[200005];
bool cmd(str a,str b){
	if(a.y==b.y)return a.x<b.x;
	return a.y<b.y;
}
int T,n,k,fa[200005],ri,ti[200005],l,r,now;
vector <int> v;
int find(int now){
	if(fa[now]==now)return now;
	return fa[now]=find(fa[now]);
}
void merge(int x,int y){
	fa[find(x)]=find(y);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			fa[i]=i;p[i].id=i;
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].t);
		}
		sort(p+1,p+n+1);
		ri=-2147483647;
		for(int i=1;i<=n;i++){
			if(p[i].x!=p[i-1].x)ri=-2147483647;
			if(ri>=p[i].y)merge(p[i].id,p[i-1].id);
			ri=max(ri,p[i].y+k);
		}
		sort(p+1,p+n+1,cmd);
		ri=-2147483647;
		for(int i=1;i<=n;i++){
			if(p[i].y!=p[i-1].y)ri=-2147483647;
			if(ri>=p[i].x)merge(p[i].id,p[i-1].id);
			ri=max(ri,p[i].x+k);
		}
		for(int i=1;i<=n;i++)ti[i]=2147483647;
		for(int i=1;i<=n;i++)ti[find(p[i].id)]=min(ti[find(p[i].id)],p[i].t);
		for(int i=1;i<=n;i++){
			if(ti[i]!=2147483647)
			v.push_back(ti[i]);
		}
		l=0;r=v.size()-1;now=0;
		sort(v.begin(),v.end());
		while(l<=r){
			r--;
			while(l<=r&&now>=v[l])l++;
			if(l>r)break;
			now++;
		}
		printf("%d\n",now);
		v.clear();
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/unusual-minesweeper-ti-jie/)
# 题目大意
给你 $n$ 个炸弹，第 $i$ 个炸弹在 $(x_i,y_i)$ 的位置，可以将这一行与这一列的距离小于 $k$ 的其他所有炸弹引爆，而且连锁的引爆不需要时间。每一秒你可以引爆一个炸弹，其中第 $0$ 秒也可以引爆，并且第 $i$ 个炸弹在第 $timer_i$ 的时候会自己爆炸。要求输出引爆所有炸弹的最小时间。

其中 $1\le n \le 2\times 10^5,0\le k \le 10^9,-10^9\le x,y\le 10^9$。

# 思路
因为炸弹爆炸的距离是一样的，所有对于任意的 $x$ 可以引爆 $y$，那么在 $y$ 被引爆时 $x$ 也会被引爆。

对于这个性质，在输入时可以将所有可以相互引爆的炸弹先预处理出来作为一个集合，同时计算出每个集合自己爆炸所需要的时间，这个操作可以通过并查集进行处理。

对于任意的 $x\le y$：如果时间为 $x$ 时可以全部引爆，那么在 $y$ 这一时刻也一定可以。如果时间为 $y$ 时不可以全部引爆，那么在 $x$ 时刻也绝对不可能将炸弹全部引爆。

根据这个规律，我们可以发现时间与全部引爆的关系是有单调性的，所以这个题目可以使用二分进行求解。

假设二分的时间为 $mid$。如果这一组炸弹自己爆炸的时间 $\le mid$，那么在规定时间到达前就会自己爆炸，所以并不需要人为的引爆。反之，如果这一组爆炸的时间 $> mid$，那么就需要将这一组进行人为的引爆。

因为在时间为 $0$ 时也可以引爆炸弹，所以如果时间为 $mid$，那么实际上是可以手动引爆 $mid+1$ 组炸弹的。

二分的复杂度为 $O(\log n)$，$check$ 函数的复杂度为 $O(n)$，总时间复杂度为 $O(n\log n)$。
# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,fa[N],s[N],x[N],y[N];
struct node{
	int x,y,id;
}a[N];
bool vis[N];
bool cmp1(node a,node b){
	if(a.x==b.x){
		return a.y<b.y;
	}
	return a.x<b.x;
}
bool cmp2(node a,node b){
	if(a.y==b.y){
		return a.x<b.x;
	}
	return a.y<b.y;
}
int find_root(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find_root(fa[x]);
}
bool ck(int mid){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(s[find_root(i)]>mid){
			vis[find_root(i)]=1;
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=vis[i];
	}
	return sum<=mid+1;
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>s[i];
		a[i].id=i;
		fa[i]=i;
	}
	sort(a+1,a+1+n,cmp1);
	a[0].x=a[0].y=-1e9-1;
	for(int i=1,p=0;i<=n;i++){
		if(a[i].x==a[i-1].x&&abs(a[i].y-a[i-1].y)<=m){
			int x=find_root(a[i].id),y=find_root(a[i-1].id);
			if(x!=y){
				fa[y]=x;
				s[x]=min(s[x],s[y]);
			} 
		}
	}
	sort(a+1,a+1+n,cmp2);
	for(int i=1,p=0;i<=n;i++){
		if(a[i].y==a[i-1].y&&abs(a[i].x-a[i-1].x)<=m){
			int x=find_root(a[i].id),y=find_root(a[i-1].id);
			if(x!=y){
				fa[y]=x;
				s[x]=min(s[x],s[y]);
			} 
		}
	}
	int l=0,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)/2;
		if(ck(mid)){
			r=mid-1;
			ans=mid;
		}
		else{
			l=mid+1;
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--){
		solve();
	}return 0;
} 
```

---

## 作者：Hhy140516 (赞：0)

[CF1619G](https://www.luogu.com.cn/problem/CF1619G)
# 题意
给定 $n$ 个地雷的坐标和自然引爆的时间。每个地雷引爆时都会使它的横纵坐标距离 $k$ 的地雷一起引爆，形状为 `+`。同时，从 0 秒开始的每秒都可以任意引爆一颗地雷，求所有地雷都引爆的时间。
# 分析
把能同时引爆的地雷合并，再找出每个合并的集合自然引爆的时间，再进行贪心就行了。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std ;
const int kMaxN = 2e5 + 5 ;
int n , k , fa[kMaxN] , f[kMaxN] , cnt , minn[kMaxN] ;
struct node
{
    int x , y , time , id ;
}a[kMaxN] ;
bool cmp1(node x , node y)
{
    if(x.x == y.x) return x.y < y.y ;
    else return x.x < y.x ;
}
bool cmp2(node x , node y)
{
    if(x.y == y.y) return x.x < y.x ;
    else return x.y < y.y ;
}
int find(int x)
{
    if(x == fa[x]) return x ;
    fa[x] = find(fa[x]) ;
    return fa[x] ;
}
void unionn(int x , int y)
{
    x = find(x) , y = find(y) ;
    if(x != y) fa[y] = x ;
}
signed main()
{
    int t ;
    cin >> t ;
    while(t--)
    {
        cin >> n >> k ;
        for( int i = 1 ; i <= n ; i++ )
        {
            cin >> a[i].x >> a[i].y >> a[i].time ;
            a[i].id = i ;
        }
        for( int i = 1 ; i <= n ; i++ ) fa[i] = i ;
        sort(a + 1 , a + n + 1 , cmp1) ;
        for( int i = 1 ; i < n ; i++ )
        {
            if(a[i].x == a[i + 1].x)
            {
                if(abs(a[i].y - a[i + 1].y) <= k)
                {
                    unionn(a[i].id , a[i + 1].id) ;
                }
            }
        }
        sort(a + 1 , a + n + 1 , cmp2) ;
        for( int i = 1 ; i < n ; i++ )
        {
            if(a[i].y == a[i + 1].y)
            {
                if(abs(a[i].x - a[i + 1].x) <= k)
                {
                    unionn(a[i].id , a[i + 1].id) ;
                }
            }
        }
        memset(minn , 0x3f , sizeof minn) ;
        memset(f , 0 , sizeof f) ;
        cnt = 0 ;
        for( int i = 1 ; i <= n ; i++ )
        {
            if(f[find(a[i].id)] == 0) f[find(a[i].id)] = ++cnt ;
            minn[f[find(a[i].id)]] = min(minn[f[find(a[i].id)]] , a[i].time) ;
        }
        sort(minn + 1 , minn + cnt + 1) ;
        minn[0] = 0 ;
        for( int i = 0 ; i <= cnt ; i++ )
        {
            if(minn[cnt - (i + 1)] <= i)
            {
                cout << i << "\n" ;
                break ;
            }
        }
    }
    return 0 ;
}
```

---

## 作者：_Weslie_ (赞：0)

喜报：调试 $1$ 天发现我 $x$ 和 $y$ 写反了。大家千万要注意 $x$ 和 $y$ 的顺序！

## Solution CF1619G

### Idea

我们发现地雷之间是可以双向影响的，这意味着如果 $u$ 可以引爆 $v$，则 $v$ 也可以引爆 $u$。

因此我们可以使用并查集，将相互可以引爆的地雷缩到一个集合里。

这意味着我们只需要引爆集合中的一个地雷，就能将这个集合中的地雷全部引爆。

我们可以维护这个集合中最早自己爆炸的地雷的爆炸时间 $t$，也就是我们最晚手动操纵这个集合爆炸的时间。原因显然，如果我们维护的不是最小的时间，那么如果我们手动引爆的时间在 $t$ 时刻之后，这个集合就已经不存在了。

至于答案统计，我们将每个集合的地雷最早爆炸时间存储在 $minn$ 数组内并从小到大排序（设有 $cnt$ 个集合）。我们枚举答案 $i$，显然我们后 $i$ 时刻引爆了 $i$ 个地雷，那么我们在 $i$ 时刻手动操纵爆炸的地雷就是第 $cnt-i$ 个，原因显然。当然从 $0$ 时刻我们就可以引爆地雷，所以 $i$ 从 $0$ 开始枚举。如果我们发现 $minn_{cnt-(i+1)}\le i$，说明在 $i$ 时刻，所有的地雷都已经自己爆炸，答案就是 $i$。

二分法也可以把答案求出来，其他人题解里有，这里不再赘述。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    int x,y,t,id;
}a[N];
bool cmpx(node _,node __){
    if(_.x<__.x)return 1;
    if(_.x==__.x&&_.y<__.y)return 1;
    return 0;
}
bool cmpy(node _,node __){
    if(_.y<__.y)return 1;
    if(_.y==__.y&&_.x<__.x)return 1;
    return 0;
}
int fa[N];
int findd(int now){
    if(fa[now]==now)return now;
    return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
    u=findd(u);v=findd(v);
    if(u==v)return;
    fa[u]=v;
}
int n,k,minn[N],vis[N];
int cnt;
void solve(){
    cnt=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].t);
        a[i].id=i;
        fa[i]=i;minn[i]=0x3f3f3f3f;vis[i]=0;
    }
    sort(a+1,a+n+1,cmpy);
    for(int i=2;i<=n;i++){
        if(a[i].y==a[i-1].y&&(a[i].x-a[i-1].x)<=k)vnion(a[i-1].id,a[i].id);
    }
    sort(a+1,a+n+1,cmpx);
    for(int i=2;i<=n;i++){
        if(a[i].x==a[i-1].x&&(a[i].y-a[i-1].y)<=k)vnion(a[i-1].id,a[i].id);
    }
    for(int i=1;i<=n;i++){
        int x=findd(a[i].id);
        if(!vis[x]){
            cnt++;
            vis[x]=cnt;
        }
        minn[vis[x]]=min(minn[vis[x]],a[i].t);
    }
    sort(minn+1,minn+cnt+1);
    for(int i=0;i<=cnt;i++){
        if(minn[cnt-(i+1)]<=i){
            printf("%d\n",i);
            return;
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--)solve();
}
```

---

## 作者：Tiffake (赞：0)

~~绝对看得懂~~
## 题意
给你 $n$ 个炸弹，每个炸弹有一个坐标（$x_i,y_i$）和自爆时间 $t_i$。当一个炸弹爆炸时，会**同时**引爆它爆炸范围 $k$ 中的其他炸弹（爆炸范围形如 `+`）。求所有炸弹引爆的最短时间。
## 思路
按照贪心思想，如果不会互相引爆，那么每次引爆自爆时间最晚的炸弹最优。

考虑对于一个炸弹 $i$，如果它可以引爆炸弹 $j$，那么先引爆炸弹 $j$ 也可以同时引爆炸弹 $i$。这说明了只要有一个炸弹可以引爆另外的炸弹，那么这些炸弹中引爆另一个炸弹也能同时引爆。

然后就可以把所有炸弹分成**一堆堆**可以同时引爆的炸弹。既然分成了一堆堆是不是想到了**并查集**？我们可以用并查集记录这一堆堆炸弹的成员，同时记录这一堆炸弹最先爆炸的时间。这样就可以按照贪心思想引爆炸弹了。

但是似乎对每个炸弹跑一遍 $k$ 的爆炸范围不太现实，$O(nk)$ 显然过不去。

考虑优化。每次可以不用遍历 $k$ 爆炸范围，遍历较小的 $n$ 的炸弹数量。优化为 $O(n^2)$。~~虽然还是过不了。~~

继续优化。发现其实可以二次排序优化。对于这些炸弹，我们可以先以横坐标 $x_i$ 为第一关键字，纵坐标 $y_i$ 为第二关键字排序，这样可以尽量保证这些炸弹在同一列，同时判断 $y_i - y_{i-1}$ 是不是在 $k$ 的范围之内，是就合并，不是就下一个；接着再以纵坐标 $y_i$ 为第一关键字，横坐标 $x_i$ 为第二关键字排序，再进行和上面类似的操作即可。  
时间复杂度为：$O(n \log n)$。

最后，按照贪心思想每次引爆自爆时间最晚的一堆同时爆炸的炸弹，发现当前炸弹的后一个炸弹（因为时间 $0$ 时也可以引爆，故第一个不算）的自爆时间 $\le$ 引爆的时间时，直接输出当前时间即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,t,id;//分别记录炸弹的横坐标，纵坐标，自爆时间，编号
}a[200002];
int f[200002],tim[200002];//f数组是并查集，tim数组记录每个元素在集合中的最先爆炸时间
bool vis[200002];//记录这个集合的炸弹有没有访问过
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int x,int y){
	int rx=find(x),ry=find(y);
	if(rx==ry)return;
	tim[ry]=min(tim[rx],tim[ry]),f[rx]=ry;//合并最早时间和元素
}
//朴素的并查集（路径压缩）
vector<int>v;//记录每个集合的爆炸时间
bool cmp1(node a,node b){return a.x<b.x||a.x==b.x&&a.y<b.y;}//x为第一关键字，y为第二关键字
bool cmp2(node a,node b){return a.y<b.y||a.y==b.y&&a.x<b.x;}//y为第一关键字，x为第二关键字
int main(){
	int T,n,m,i;
	cin>>T;
	while(T--){//多测
		cin>>n>>m,v.clear();
		memset(vis,0,sizeof vis);//多测不清空，爆0两行泪
		for(i=1;i<=n;i++)cin>>a[i].x>>a[i].y>>a[i].t,a[i].id=i;
		for(i=1;i<=n;i++)f[i]=i,tim[i]=a[i].t;//并查集初始化
		sort(a+1,a+n+1,cmp1);//第一次排序
		for(i=2;i<=n;i++)
			if(a[i].x==a[i-1].x&&a[i].y-a[i-1].y<=m)//判断能否同时引爆
				merge(a[i-1].id,a[i].id);
		sort(a+1,a+n+1,cmp2);//第二次排序
		for(i=2;i<=n;i++)
			if(a[i].y==a[i-1].y&&a[i].x-a[i-1].x<=m)//同上
				merge(a[i-1].id,a[i].id);
		for(i=1;i<=n;i++){
			int now=find(a[i].id);
			if(!vis[now])vis[now]=1,v.push_back(tim[now]);//找一个集合中的最早爆炸时间
		}
		sort(v.begin(),v.end(),greater<int>());//从大到小贪心排序
		v.push_back(INT_MIN);//防止出现所有炸弹都在自爆之前被引爆导致的误判
		for(i=0;i<v.size();i++)if(v[i+1]<=i)break;//注意在第0秒也可以引爆炸弹，因此i+1
		cout<<i<<endl;
	}
	return 0;
}
```

---

