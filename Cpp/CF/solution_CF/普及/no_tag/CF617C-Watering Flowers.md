# Watering Flowers

## 题目描述

A flowerbed has many flowers and two fountains.

You can adjust the water pressure and set any values $ r_{1}(r_{1}>=0) $ and $ r_{2}(r_{2}>=0) $ , giving the distances at which the water is spread from the first and second fountain respectively. You have to set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered, that is, for each flower, the distance between the flower and the first fountain doesn't exceed $ r_{1} $ , or the distance to the second fountain doesn't exceed $ r_{2} $ . It's OK if some flowers are watered by both fountains.

You need to decrease the amount of water you need, that is set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered and the $ r_{1}^{2}+r_{2}^{2} $ is minimum possible. Find this minimum value.

## 说明/提示

The first sample is ( $ r_{1}^{2}=5 $ , $ r_{2}^{2}=1 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/2d8d9a04106e184829b587a5ec1ff5859c519f17.png) The second sample is ( $ r_{1}^{2}=1 $ , $ r_{2}^{2}=32 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/3a67f8e9001d1413dc94db849ab2167229f3fb78.png)

## 样例 #1

### 输入

```
2 -1 0 5 3
0 2
5 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 0 0 5 0
9 4
8 3
-1 0
1 4
```

### 输出

```
33
```

# 题解

## 作者：jch123 (赞：4)

## 思路
枚举第一个喷泉覆盖到哪个点，按每个点到第一个喷泉的距离排序，然后再开一个数组 $dis_i$ 记录第个 $i$ 点和后面所有的点到第二个喷泉的最长距离即可。然后开始枚举第一个喷泉覆盖到第 $i$ 个点，当前答案为排序后的数组的第 $i$ 个点到第一个喷泉的距离加上 $dis_{i+1}$ 即可，最后取最大值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dis[2010];
struct node
{
	ll x,y,d;
}a[2010];
ll d(ll x1,ll y1,ll x2,ll y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
bool cmp(node q,node w)
{
	return q.d<w.d;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	ll x1,y1,x2,y2;
	cin>>n>>x1>>y1>>x2>>y2;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y,a[i].d=d(x1,y1,a[i].x,a[i].y);
	sort(a+1,a+1+n,cmp);//按到第一个喷泉的距离排序 
	for(int i=n;i>=1;i--) 
		dis[i]=max(dis[i+1],d(x2,y2,a[i].x,a[i].y));//处理每个点和后面所有的点到第二个喷泉的最长距离 
	ll ans=1e18;
	for(int i=0;i<=n;i++)
		ans=min(ans,a[i].d+dis[i+1]);//枚举 
	cout<<ans;
	return 0;
}
```

---

## 作者：清小秋ovo (赞：3)

# CF617C 

[洛谷链接](https://www.luogu.com.cn/problem/CF617C)

[原题传送门](https://codeforces.com/problemset/problem/617/C)

来一篇 C++的题解。

## 题意
两个喷泉，喷泉附近有很多花，每个喷泉有一个圆形的覆盖范围，分别为$r_1$,$r_2$，要使所有花再两个圆之内，求 $r_1 \times r_1 + r_2 \times r_2$ 的最小值。

## 解题思路
其实这道题用到了一点点的贪心策略 ~~（更多还是暴力）~~

首先按照每一朵花到第一个喷泉的距离的排序。然后根据这个顺序确定 $r_1$ 的值，然后再求出未被 $r_1$ 覆盖的所有花中距离第二个喷泉最远的那个为 $r_2$。求出最小的 $r_1 + r_2$ 就好了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
#define PB push_back

struct nodes{ //存每个花和到两个喷泉的距离
    ll x,y;
    ll dist1,dist2;
};

ll calc(ll a,ll b,ll a1,ll b1){ //计算距离
    return((a-a1)*(a-a1)+(b-b1)*(b-b1));
}

bool cmp(nodes a,nodes b){ //根据第一个喷泉排序
    return a.dist1>b.dist1;
}

nodes a[3000];
int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   int n,f1x,f1y,f2x,f2y;
   cin>>n>>f1x>>f1y>>f2x>>f2y;
   for(int i=0;i<n;i++){
       cin>>a[i].x>>a[i].y;
       a[i].dist1=calc(f1x,f1y,a[i].x,a[i].y);
       a[i].dist2=calc(f2x,f2y,a[i].x,a[i].y);
   }
   sort(a,a+n,cmp); //排序
   ll ans=a[0].dist1;
   ll r2=0;
   for(int i=0;i<n;i++){ //依次枚举r1, r2的值
       ans=min(ans,a[i].dist1+r2);
       r2=max(r2,a[i].dist2);
   }
   ans=min(ans,r2);
   cout<<ans<<endl;
}

```


---

## 作者：jiangruibo (赞：1)

### 思路：
这题涉及到了一点**贪心策略**，就是首先你去把每一个到第一个喷泉和第二个喷泉的**距离**分别算出来，按到第一个喷泉的距离排序，然后你去枚举，对于每一个到喷泉一的距离，找出离第二个喷泉最远，分别作为 $r_{1}$ 和 $r_{2}$，最后找出最小的 $r_{1}+r_{2}$ 即可，这里计算距离有一个小技巧，因为要求的是平方后的，所以你最开始就不用开根了。

### 代码：
```
#include<bits/stdc++.h>
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
using namespace std;

struct node
{
    int x,y;
    int dis1,dis2;
};
int dis(int sx,int sy,int qx,int qy)
{
    return((sx-qx)*(sx-qx)+(sy-qy)*(sy-qy));
}
bool cmp(node x,node y)
{ 
    return x.dis1>y.dis1;
}
node p[3010];

signed main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   int n,x1,y1,x2,y2;
   cin>>n>>x1>>y1>>x2>>y2;
   for(int i=1;i<=n;i++)
   {
       cin>>p[i].x>>p[i].y;
       p[i].dis1=dis(x1,y1,p[i].x,p[i].y);
       p[i].dis2=dis(x2,y2,p[i].x,p[i].y);
   }
   sort(p+1,p+n+1,cmp);
   int k=0;
   int ans=p[1].dis1;
   for(int i=1;i<=n;i++)
   {
       ans=min(ans,p[i].dis1+k);
       k=max(k,p[i].dis2);
   }
   cout<<min(ans,k)<<endl;
   return 0;
}




```

---

## 作者：QWQ_SenLin (赞：1)

很容易想到，**枚举**。

考虑枚举第一个喷泉覆盖几个点，然后算出第二个点的可以覆盖到其他花的最小半径，然后更新答案。

我们按照花到第一个喷泉的距离排序，这样枚举时，第一个喷泉的可以覆盖到前 $i$ 朵花的最小半径就是第 $i$ 个花到第一个喷泉的距离。而 $i+1$ 多花到第二个喷泉的距离就是第二个喷泉的最小半径。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
long long ans = 0x7ffffffffffffff;
struct Point{
	long long x , y;
}flower[2005] , qwq1 , qwq2;

long long dis(Point a , Point b){
	return 1LL * (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(Point a , Point b){
	long long da = dis(a , qwq1);
	long long db = dis(b , qwq1);
	return da <= db;
}

int main(void){
	scanf("%d%lld%lld%lld%lld" , &n , &qwq1.x , &qwq1.y , &qwq2.x , &qwq2.y);
	for(int i = 1;i <= n;i++)
		scanf("%lld%lld" , &flower[i].x , &flower[i].y);
	sort(flower + 1 , flower + 1 + n , cmp);
	for(int i = 1;i <= n;i++)
		printf("x%lld y%lld\n" , flower[i].x , flower[i].y);
	for(int i = 1;i < n;i++){
		long long r1 = dis(flower[i] , qwq1);
		long long r2 = dis(flower[i + 1] , qwq2);
		ans = min(ans , r1 + r2);
		printf("%lld %lld %lld\n" , r1 , r2 , r1 + r2);
	}
	ans = min(ans , dis(flower[n] , qwq1));
	ans = min(ans , dis(flower[1] , qwq2));
	printf("%lld\n" , ans);
}
```
然而，这是错的。看这组数据。

in
```
5 -6 -4 0 10
-7 6
-9 7
-5 -1
-2 1
-8 10
```
out
```
100
```
如图所示，以上面那个程序来说：点 $C$ 是距离 $P_1$ 最近的点，而点 $D$ 是距离第二近的，如果直接以它到 $P_2$ 的距离为半径，就无法完全覆盖到除 $C$ 以外的所有点，即 $B$ 无法覆盖到。
![](https://cdn.luogu.com.cn/upload/image_hosting/bvohqzs2.png)

如何解决呢，显然第二个喷泉的半径是除 $P_1$ 覆盖的点以外，距离第二个喷泉最远的点到第二个喷泉的距离。很容易想到：预处理出 $i$ 到 $n$ 中离第二个喷泉最远的点，然后在枚举时，就可以 $\mathcal O(1)$ 计算出第二个喷泉的距离了。

所以，时间复杂度 $\mathcal O(n \log_2 n+n)$

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
long long ans = 0x7ffffffffffffff;
struct Point{
	long long x , y;
}flower[2005] , qwq1 , qwq2;
int maxi[2005]; //maxi[i]为 i~n 中离 2 最远的。 

long long dis(Point a , Point b){
	return 1LL * (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(Point a , Point b){
	long long da = dis(a , qwq1);
	long long db = dis(b , qwq1);
	return da <= db;
}

int main(void){
	scanf("%d%lld%lld%lld%lld" , &n , &qwq1.x , &qwq1.y , &qwq2.x , &qwq2.y);
	for(int i = 1;i <= n;i++)
		scanf("%lld%lld" , &flower[i].x , &flower[i].y);
	sort(flower + 1 , flower + 1 + n , cmp);
	long long maxn = -1;
	for(int i = n;i >= 1;i--){
		maxi[i] = maxi[i + 1];
		if(dis(flower[i] , qwq2) >= maxn || i == n){
			maxn = dis(flower[i] , qwq2);
			maxi[i] = i;
		}
	}	
	for(int i = 1;i < n;i++){
		long long r1 = dis(flower[i] , qwq1);
		long long r2 = dis(flower[maxi[i + 1]] , qwq2);
		ans = min(ans , r1 + r2);
	}
	ans = min(ans , dis(flower[n] , qwq1));
	ans = min(ans , dis(flower[maxi[1]] , qwq2));
	printf("%lld\n" , ans);
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路

这道题是道贪心题，首先计算每一个点到第一个喷泉和第二个喷泉的距离算出来，按照第一个点的距离从小到大排序。

对于每一个点，枚举找出离第二个喷泉最远的确定 $r1$ 和 $r2$，再全局取最小的 $r1+r2$，输出答案即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x1,yy1,x2,y2;
int minn;
struct st{
	int x,y,j,jj;
}a[2005];
int dis(int x1,int yy1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(yy1-y2)*(yy1-y2);
}
bool cmp(st a,st b)
{
	return a.j<b.j;
}
int rr2,xx,yy;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>x1>>yy1>>x2>>y2;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].j=dis(x1,yy1,a[i].x,a[i].y);
		a[i].jj=dis(x2,y2,a[i].x,a[i].y);
		xx=max(xx,a[i].j);
		yy=max(yy,a[i].jj);
	}
	sort(a+1,a+n+1,cmp);
	minn=xx+yy;
	for(int i=0;i<=n;i++)
	{
		int rr2=0;
		for(int j=i+1;j<=n;j++)
		{
			rr2=max(rr2,a[j].jj);
//			cout<<xx<<"\n";
		} 
//		cout<<rr1<<" "<<rr2<<"\n";
		minn=min(minn,a[i].j+rr2);
	}
	cout<<minn<<"\n"; 
	return 0;
}//aaa
```

---

## 作者：Problem1613end (赞：0)

首先只有两个喷泉，那每朵花至少被一个喷到。

先按第一个喷泉喷花代价从低到高排序，而后利用贪心暴枚。（暴枚爽）

根据贪心，当我确定喷 $k$ 朵花时，一定是喷代价前 $k$ 小的，否则多喷，浪费水和钱。

带着一点小贪心，让 $hz_i$ 代表第二个喷泉喷第 $i$ 到 $n$ 朵花代价。

紧接着暴枚处理方案（详见注释），此时定能得到最优解。（贪心）

```
#include<bits/stdc++.h>
using namespace std;
long long x11,x22,y11,y22,n,hz[100100],minn=1000000000000000000;//这个大小葬了我两发 
struct loc{
	long long x,y,q;
}pxy[100100];
bool cmp(loc i,loc j){
	if(i.q<j.q)  return 1;
	return 0;
}
int main(){
	cin>>n;
    cin>>x11>>y11>>x22>>y22;
    for(int a=1;a<=n;a++){
    	cin>>pxy[a].x>>pxy[a].y;
    	pxy[a].q=(pxy[a].x-x11)*(pxy[a].x-x11)+(pxy[a].y-y11)*(pxy[a].y-y11);
	}
	sort(pxy+1,pxy+n+1,cmp);
	for(int a=n;a>=1;a--){
        hz[a]=max(hz[a+1],(pxy[a].x-x22)*(pxy[a].x-x22)+(pxy[a].y-y22)*(pxy[a].y-y22));
	}
	for(int a=0;a<=n;a++){//暴枚，处理所有贪心解，记得只有第一个喷和只有第二个喷
		minn=min(minn,hz[a+1]+pxy[a].q);
	}
	cout<<minn;
	return 0;
}

---

## 作者：fish_shit (赞：0)

这道题可以考虑直接枚举。我们可以先处理出每个点到两个瀑布的距离的平方，按照每朵花到第一个瀑布的距离进行排序、枚举。再去算不能被以枚举到的这个距离为半径的瀑布所覆盖到的花到另外一个瀑布的距离的最大值，这样就可以确定出两个瀑布的半径。

要注意的是，需要考虑所有花只被第二个瀑布所覆盖的情况。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5000;
#define int long long
struct f{
	int x,y,num1,num2;
}b[maxn];
bool cmp(f q,f w){
	return q.num1<w.num1;
}
int n,penx,peny,penxx,penyy,ans;
signed main(){
	cin>>n>>penx>>peny>>penxx>>penyy;
	for(int i=1;i<=n;i++){
		cin>>b[i].x>>b[i].y;
		b[i].num1=(penx-b[i].x)*(penx-b[i].x)+(peny-b[i].y)*(peny-b[i].y);
		b[i].num2=(penxx-b[i].x)*(penxx-b[i].x)+(penyy-b[i].y)*(penyy-b[i].y);
	}
	sort(b+1,b+n+1,cmp);
	int ans1=b[n].num1;
	for(int i=1;i<=n-1;i++){//枚举，找到平方和最小的r1,r2 
		ans=0;
		for(int j=i+1;j<=n;j++){
			if(b[j].num2>ans){
				ans=b[j].num2;
			}
		}
		if(ans1>ans+b[i].num1){
			ans1=ans+b[i].num1;
		}
	}
	int ans2=0;
	for(int i=1;i<=n;i++){//全都被第二个喷泉覆盖的情况 
		if(b[i].num2>ans2){
			ans2=b[i].num2;
		}
	}
	cout<<min(ans1,ans2);
	return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

题目够简洁了吧？不给。

# 解法分析

其实是水题一道。我们可以按照这些花到第一个喷泉的距离排序，然后枚举第一个喷泉覆盖到哪里，剩下的可以暴力枚举离第二个喷泉的距离最远的花在哪里并计算 $O(n^2)$ 或者用倒序的前缀和数组优化为 $O(n)$。总复杂度为 $O(n\log{n})$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int raed(){
	register int r=0,s=1; register char c=getchar();
	while(c < '0' || c > '9') {if(c == '-') s = -1;c = getchar();}
	while(c>='0' && c<='9') r=(r<<3)+(r<<1)+(c^48),c=getchar();
	return r*s;
}
inline void writen(int x){
	if(x>9) writen(x/10);
	putchar(x%10+'0');
	return;
}
inline void read(){
	return;
}
template<typename... Args>
inline void read(int& val,Args&... args){
	val=raed(); read(args...);
}
struct pnt{
	int x,y;
	pnt(int xi=0,int yi=0){
		x=xi,y=yi;
	}
}p1,p2;
int n; pnt p[2005]; int di[2005];
inline int dis(pnt l,pnt r){
	return (l.x-r.x)*(l.x-r.x)+(l.y-r.y)*(l.y-r.y);
}
inline bool cmp(pnt l,pnt r){
	return dis(l,p1)<dis(r,p1);
}
signed main(){
	read(n,p1.x,p1.y,p2.x,p2.y);
	for(int i=1;i<=n;++i) read(p[i].x,p[i].y);
	sort(p+1,p+n+1,cmp);
	for(int i=n;i;i--) di[i]=max(di[i+1],dis(p[i],p2));
	int ans=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=n;++i) 
		ans=min(ans,dis(p[i],p1)+di[i+1]);
	ans=min(ans,di[1]); cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF617C)

# First 题意

~~呃，感觉题目讲的很清楚了。~~

题意是说，平面上有 $n$ 个点和两个园，其中圆的圆心和 $n$ 个点的坐标由题目给定，要求圆要覆盖住所有的点，求 $r_1^2+r_2^2$的最小值（$r_1,r_2$ 是圆的半径）。

# Second 暴力

暴力没什么好说的，就是 ```dfs``` 枚举每个点被哪个圆覆盖，时间复杂度，呃，也就 $O(2^n)$ 而已啦，也只是 TLE 而已啦。

# Third 思路

但其实，这道题还是需要一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/salbqp8v.png)

好的，让我们再看一下这道题（图中蓝点是圆心，绿点是花）。

很显然，圆一定会穿过某个绿点，否则的话就会浪费距离，并且应该离圆心 1 近的就被圆 1 覆盖，否则被圆 2 覆盖。

于是，我们可以按照每个绿点到圆心 1 的距离排序，然后枚举前 $i$ 个点被圆 1 覆盖，否则被圆 2 覆盖，然后计算圆的半径，求 $ans$ 的值，总时间复杂度是 $O(nlog(n)+n^2)$ 的，其中 $O(nlog(n))$ 是排序，另外 $O(n^2)$ 是枚举。

# Fourth 优化

虽然这个时间复杂度可以过，但是我们还能再优化，也不难，就是把原来求半径的 $O(n^2)$ 利用递推优化成 $O(n)$ 的，这样就可以优化成 $O(nlog(n)+n)$ 的了。

# Fifth Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
struct Point{
	ll x, y;
	ll dis1, dis2;
}e[2005], p1, p2;
ll n, ans = 1000000000, r;
il bool cmp(Point a, Point b){
	return a.dis1 > b.dis1;
}
il ll diss(Point a, Point b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int main(){
	scanf ("%lld %lld %lld %lld %lld", &n, &p1.x, &p1.y, &p2.x, &p2.y);
	for (int i = 1; i <= n; i++){
		cin >> e[i].x >> e[i].y;
		e[i].dis1 = diss(e[i], p1);
		e[i].dis2 = diss(e[i], p2);
	}
	sort (e + 1, e + n + 1, cmp);
	ans = e[1].dis1;
	for (int i = 1; i <= n; i++){
		ans = min(ans, e[i].dis1 + r);
		r = max(r, e[i].dis2);
	}
	printf ("%lld", min(ans, r));
	return 0;
}

```

---

## 作者：LOLchn0 (赞：0)

## 题目大意：

有若干盆花和 $2$ 个喷泉，它们都在不同的位置，喷泉的浇灌覆盖半径分别为 $ r_{1} $ 和 $ r_{2} $，输入花和喷泉的位置，求出**最小**的 $ r_{1}^{2}+r_{2}^{2} $ 能够保证所有的花都被喷泉覆盖。

## 思路：
先求每朵花到水源 $1$ 的距离，再求出每朵花到水源 $2$ 的距离，用结构体储存，将花到水源 $2$ 的距离从大到小排序，枚举水源 $1$ 的 $ r_{1} $，求 $ r_{2} $，记录最小值。



## 100pts代码：

```c
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
#define ll __int64
ll x1, y1, x2, y2;
ll dis[2010];
ll x, y;
struct node{
	int id;
	ll len;
	friend bool operator < (const node n1, const node n2)
	{
		return n1.len>n2.len;
	}
}ds[2010];
int main()
{
	int n; 
	scanf("%d", &n);
	scanf("%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2);
	for(int i=1; i<=n; i++)
	{
		scanf("%I64d%I64d", &x, &y);
		dis[i] = (x1-x)*(x1-x)+(y1-y)*(y1-y);
		ds[i].len = (x2-x)*(x2-x)+(y2-y)*(y2-y);
		ds[i].id=i;
	}
	ll minx=1e16;
 
	sort(ds+1, ds+n+1);
	for(int i=0; i<=n; i++)
	{
		int flag=0; 
		for(int j=1; j<=n; j++)
		{
			if(dis[ds[j].id]>dis[i])
			{
				flag=1;
				minx = min(minx, dis[i]+ds[j].len);
				break;
			}		
		}
		if(!flag) minx = min(minx, dis[i]); 
	}
	printf("%I64d\n", minx);
	return 0;
}
```





---

## 作者：jr_zch (赞：0)

# [Watering Flowers](https://www.luogu.com.cn/problem/CF617C)
## by [jr_zch](https://www.luogu.com.cn/blog/jr-zch-code-garden/) 博客食用更佳喵~
## Part 1: 题目大意 
给你 $n$ 个点的坐标以及 $2$ 个圆心坐标 试求出 $\min(r1^2 + r2^2)$ 使得这两个圆可以覆盖**所有的点**。

## Part 2: 解题思路
### $O(n^2 + n\log_2n):$ 正解如下
观察到 $n \leq 2 \times 10^3$ 所以考虑 $n^2$ 做法。

先统计出**每一个**点到两个喷泉的距离 然后采用**贪心思想** 按到任意一个喷泉的距离**升序排序**。

接下来**枚举**前 $i$ 个点被喷泉 $1$ 所覆盖 剩下的被喷泉 $2$ 所覆盖 ~~暴力~~找出**覆盖所需最远半径**即可。
#### tips:
* 最后输出的答案要求是**整数**所以要强转成 `int`。
* 为了防止开方**精度丢失** 在算距离时**不用开方** 最后**直接相加**即可。

## Part 3: Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e3+7,inf=1e18;
int n,l,r,ans=inf;
double x,_x,y,_y,len1,len2;
double dx[maxn],dy[maxn];
double d1,d2;
struct node{
	double f,s;
}dis[maxn];

bool cmp(node x,node y){
	return x.f<y.f;
}

signed main(){
	scanf("%lld%lf%lf%lf%lf",&n,&x,&y,&_x,&_y),d1=d2=inf;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&dx[i],&dy[i]);
		len=abs(x-dx[i])*abs(x-dx[i])+abs(y-dy[i])*abs(y-dy[i]);
		_len=abs(_x-dx[i])*abs(_x-dx[i])+abs(_y-dy[i])*abs(_y-dy[i]);
		dis[i].f=len,dis[i].s=_len;
	}
	sort(dis+1,dis+1+n,cmp);
	for(int i=0;i<=n;i++){
		double maxx=-inf;
		for(int j=i+1;j<=n;j++) maxx=max(maxx,dis[j].s); 
		d=dis[i].f,_d=maxx;
		if(i==n) _d=0;
		ans=min(ans,(int)(d)+(int)(_d));
	}
	printf("%lld",ans);
	return 0;
}
```
## $\text Thanks~for~your~reading$

---

## 作者：Keroshi (赞：0)

# 题目分析
看数据范围： $n\le 2000$, $O(n^2)$ 可以过, 直接暴力。   
可以先枚举第一个喷泉最远到达的花，再让没浇到的给第二个喷泉。  
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e3+5;
const ll INF=9e18;
ll n;
ll ans;
struct node{
    ll x,y;
}a[N];
ll dist(ll x,ll y,ll x3,ll y3){
    return (x-x3)*(x-x3)+(y-y3)*(y-y3);
}
int main(){
    ans=INF;
    ll x1,y1,x2,y2;
    scanf("%lld%lld%lld%lld%lld",&n,&x1,&y1,&x2,&y2);
    for(ll i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
    ll res=0;
    for(ll i=1;i<=n;i++){
        res=max(res, dist(a[i].x,a[i].y,x2,y2));
    }
    ans=min(ans, res);
    for(ll i=1;i<=n;i++){
        res=0;
        ll len=dist(a[i].x,a[i].y,x1,y1);
        for(ll j=1;j<=n;j++){
            if(dist(a[j].x,a[j].y,x1,y1)>len){
                res=max(res, dist(a[j].x,a[j].y,x2,y2));
            }
        }
        ans=min(ans,res+len);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：皮卡丘最萌 (赞：0)

(大年三十写篇题解纪念一下，还是此题第一个题解呢。)

因为此题中喷泉只有$2$个，所以我们可以直接求出每朵花到$2$个喷泉的距离$p,q$。

接下来对$p,q$进行双关键字排序($p$从大到小，$q$从大到小)。

为什么要排序呢？

因为排序后，我们可以利用贪心。

先假设第一个喷泉浇所有的花，值就是$p[1]$。

接下来假设第一个喷泉浇$1$~$n-1$朵花，第二个喷泉浇第$n$朵花，值就是$p[2]+max$。

当第一个喷泉浇$1$~$i$朵花时，$max$就是$q[i+1]$~$q[n]$的最大值。

那么结果就是这些数中的最小值。

$1$个要注意的地方：

求距离时$p,q$的值可能会达到$10$的$14$次方，所以要用$int64/longlong$。

代码：
```pascal
var n,x,y,max,max1,x1,y1,x2,y2:int64; i:longint;
a,b:array[0..1000001] of int64;
procedure sort(l,r: int64);
      var i,j,x,y,xx: int64;
      begin
         i:=l; j:=r;
         x:=a[(l+r) div 2];
         xx:=b[(l+r) div 2];
         repeat
           while (a[i]>x)or(a[i]=x)and(b[i]>xx) do inc(i);
           while (x>a[j])or(a[j]=x)and(b[j]<xx) do dec(j);                      //双关键字排序，从大到小
           if not(i>j) then
             begin
             y:=a[i];a[i]:=a[j];a[j]:=y;
             y:=b[i];b[i]:=b[j];b[j]:=y;
             inc(i); j:=j-1;
             end;
         until i>j;
         if l<j then sort(l,j);
         if i<r then sort(i,r);
      end;
begin
readln(n,x1,y1,x2,y2);
for i:=1 to n do
  begin
  readln(x,y);
  a[i]:=sqr(x1-x)+sqr(y1-y);
  b[i]:=sqr(x2-x)+sqr(y2-y);
  end;                       //求距离
sort(1,n);                  //排序
a[n+1]:=0; max1:=a[1];     //浇所有花的情况
max:=0;
for i:=1 to n do
  begin
  if b[i]>max then max:=b[i];   //求出最大值
  if max+a[i+1]<max1 then max1:=max+a[i+1];
                                 //更新答案
  end;                         
writeln(max1);
end.
```



---

