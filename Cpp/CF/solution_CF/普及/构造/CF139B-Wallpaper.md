# Wallpaper

## 题目描述

Having bought his own apartment, Boris decided to paper the walls in every room. Boris's flat has $ n $ rooms, each of which has the form of a rectangular parallelepiped. For every room we known its length, width and height of the walls in meters (different rooms can have different dimensions, including height).

Boris chose $ m $ types of wallpaper to paper the walls of the rooms with (but it is not necessary to use all the types). Each type of wallpaper is sold in rolls of a fixed length and width (the length, naturally, shows how long the unfolded roll will be). In addition, for each type we know the price of one roll of this type.

The wallpaper of each type contains strips running along the length of the roll. When gluing the strips must be located strictly vertically (so the roll cannot be rotated, even if the length is less than the width). Besides, a roll can be cut in an arbitrary manner, but the joints of glued pieces should also be vertical. In addition, each room should be papered by only one type of wallpaper. And pieces of the same roll cannot be used to paper different rooms. That is, for each room the rolls are purchased separately. Also, some rolls can be used not completely.

After buying an apartment Boris is short of cash, so he wants to spend the minimum money on wallpaper. Help him.

## 说明/提示

Note to the sample:

The total length of the walls (the perimeter) of the room is 20 m.

One roll of the first type can be cut into pieces to get three vertical 1 meter wide strips, ergo you need 7 rolls of this type, the price equals 700.

A roll of the second type can be cut into pieces to get five 2 meter wide strips, we need 2 rolls, the price is 640.

One roll of the third type can immediately paper 19 meters out of 20, but we cannot use other types and we have to buy a second roll, the price is 1000.

## 样例 #1

### 输入

```
1
5 5 3
3
10 1 100
15 2 320
3 19 500
```

### 输出

```
640
```

# 题解

## 作者：liaoxingrui (赞：3)

# [题目](https://www.luogu.com.cn/problem/CF139B)
### 思路：
可以暴力枚举每一个房间的最小消费，但还要注意一下特殊情况——墙纸长度小于房间的高，最后在累加。
### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,chang,kuan,jia_ge,ans,c,k,g[505],sum[505],cnt[505];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>chang>>kuan>>g[i];
		sum[i]=(chang+kuan)<<1;
	}
	cin>>m;
	memset(cnt,0x3f,sizeof(cnt));
	for(int i=1;i<=m;i++){
		cin>>chang>>kuan>>jia_ge;
		for(int j=1;j<=n;j++)
			if(chang>=g[j])
				cnt[j]=min(cnt[j],(((sum[j]-1)/kuan)/(chang/g[j])+1)*jia_ge);
	}
	for(int i=1;i<=n;i++)
		ans+=cnt[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：zym20249_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF139B)

## 题意
有 $n$ 个房间，$m$ 种墙纸，第 $i$ 个房间的长宽高分别是 $L_i$，$W_i$ 和 $H_i$，第 $i$ 种墙纸的价格分别是 $l_i$，$w_i$ 和 $p_i$，每个房间的四周要贴上同种墙纸，多了也不能用到别的房间，墙纸可以裁剪但不能旋转，无论 $l_i$ 和 $w_i$ 的大小，必须以 $l_i$ 作为竖直方向且首尾不能拼接，问至少需要多少钱。

## 思路
这题数据范围只有五百，可以直接暴力枚举，首先可以将整个墙体展开来看，这样就变成了一个矩形，枚举每种纸的的最小价格，但这里需要要注意一下会出现多或者少的情况。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=510;
ll n,m,l,w,q,ans,c,k,g[maxn],sum[maxn],cnt[maxn];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);//减时间
	cin>>n;
	for(int i=1;i<=n;i++)//输入
	{
		cin>>l>>w>>g[i];
		sum[i]=(l+w)<<1;
	}
	cin>>m;
	memset(cnt,0x3f,sizeof(cnt));//设置所有的为一个数
	for(int i=1;i<=m;i++)
	{
		cin>>l>>w>>q;
		for(int j=1;j<=n;j++)
			if(l>=g[j])cnt[j]=min(cnt[j],(((sum[j]-1)/w)/(l/g[j])+1)*q);//判断所有情况取最小值
	}
	for(int i=1;i<=n;i++)ans+=cnt[i];//最后答案累加
	cout<<ans;
	return 0;
}
```

---

## 作者：tuanzi_pal (赞：1)

### 思路
对于每一个输入进来的房间，我们只需要去计算它花费的最小值，然后加和输出即可，但还要注意去特判掉墙纸的长度 $l < H_i$ 的情况。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int h[1005],sum[1005],cnt[1005];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	ios_base::sync_with_stdio(false);cout.tie(0);
	memset(cnt,0x3f,sizeof cnt);
	int n;cin>>n;
	for(int i=1,x,y;i<=n;i++) cin>>x>>y>>h[i],sum[i]+=(x+y)*2;
	int m,ans=0;cin>>m;
	for(int i=1,l,w,p;i<=m;i++){
		cin>>l>>w>>p;
		for(int j=1;j<=n;j++)
			if(l>=h[j]) cnt[j]=min(cnt[j],(((sum[j]-1)/w)/(l/h[j])+1)*p);//计算它花费的最小值 
	}
	for(int i=1;i<=n;i++) ans+=cnt[i];
	cout<<ans;
	return 0;
}
```
完结撒花 ~

---

## 作者：conti123 (赞：1)

### 思路
因为 $1\le{n}\le{500}$ 且 $1\le{m}\le{500}$

所以我们直接暴力枚举每一个房间的最小花费，再累加即可。
### 分析
由于只要四周贴上同种墙纸，所以我们不妨把要贴壁纸的地方展开，形成一个长方形，则长方形的长和宽分别为：

$a=2\times(l+w)$ 和 $b=h$

然后我们就可以开始贴壁纸了，这个就不说了，计算过程很简单，看程序即可。

### Code
```cpp

#include<bits/stdc++.h>
#define inf 0x3f3f
const int N=1e3;
using namespace std;
int n,m,x,y,h[N],l[N],p[N],s[N],w[N],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&x,&y,&h[i]),s[i]=(x+y)*2;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&l[i],&w[i],&p[i]);
	for(int i=1;i<=n;i++)
	{
		int sum=1e9;
		for(int j=1;j<=m;j++)
			if(l[j]>=h[i])
			{
				int xx=l[j]/h[i];
				int yy=(s[i]-1)/w[j];
				sum=min(sum,(yy/xx+1)*p[j]);
			}
		ans+=sum;
	}
	printf("%d",ans);
}
```

---

## 作者：qingchenMC (赞：0)

## 思路

题意说的不是很明白，我来解释一下。首先给一个房间的四面墙壁贴墙纸，有每种墙纸的价格和尺寸，求贴满房间最小花费。这里“首尾不能拼接”的意思是：想要贴一张墙纸，墙纸的高度必须大于等于墙的高度。如图甲。

由于数据范围并不大，我们可以对每个房间枚举贴哪种墙纸最便宜，最后取最小值即可。时间复杂度 $O(nm)$，最大为 $\max n\cdot \max m=500\times500=250000$，可以通过此题。

对于每个房间和每个墙纸，首先判断墙纸的高是否大于等于房间的高，原因为图甲。判断可以后看看这种墙纸高出来的部分是否能裁剪，补到这张墙纸的右边。如果是的话，能补几张？把这个数求出来。这个过程如图乙。最后将横着贴墙纸的个数除以这个数，即可求出这个房间需要几张墙纸。

### 配图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1xlkb1e8.png)

## 代码

```cpp
#include<bits/stdc++.h> 

using namespace std;

int l[502],w[502],h[502];
int x[502],y[502],p[502];
int cost[502];

int main(){
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>w[i]>>h[i];
		cost[i]=2147483647;
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i]>>p[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(x[j]>=h[i]){	
				int gs=((l[i]+w[i])*2)/y[j];
				if(((l[i]+w[i])*2)%y[j]!=0){
					gs++;
				}
				int k=x[j]/h[i];
				int s=gs/k;
				if(gs%k!=0){
					s++;
				}
				s*=p[j];
				cost[i]=min(cost[i],s); 
			}
		}
	}
	long long cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=cost[i];
	}
	cout<<cnt;
	return 0;
//https://codeforces.com/contest/139/submission/304390758
}
``

---

## 作者：Peter20122012 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF139B)
## 思路
可以把第 $i$ 个房间的四面墙展开为一个长为 $2L_{i} + 2W_{i}$，宽为 $H_{i}$ 的平面。然后对于房间 $i$ 尝试所有种类的墙纸。

如果 $j$ 墙纸的长 $l_{j}$ 小于 $i$ 房间的高度 $H_{i}$，则不能使用这种墙纸（墙纸首尾不能拼接，所以不能把多个墙纸拼在同一列）。否则为了省钱，可以把这张墙纸尽可能多的的裁成高度不小于房间高度的墙纸共 $\big\lfloor\frac{l_{j}}{H_{i}}\big\rfloor$ 个，可以贴完 $\big\lfloor\frac{l_{j}}{H_{i}}\big\rfloor \cdot w_{j}$ 列，那么贴满所有墙所需的墙纸数量为 $\bigg\lceil\frac{\big\lfloor\frac{l_{j}}{H_{i}}\big\rfloor \cdot w_{j}}{2L_{i} + 2W_{i}}\bigg\rceil$。所以如果 $i$ 房间贴 $j$ 墙纸，那么花费为 $\bigg\lceil\frac{\big\lfloor\frac{l_{j}}{H_{i}}\big\rfloor \cdot w_{j}}{2L_{i} + 2W_{i}}\bigg\rceil \cdot p_{j}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)

// #define debug

typedef long long ll;
typedef double dou;
typedef pair<int, int> pii;

struct Room {
	int l, w, h;
};
struct Wallpaper {
	int h, l, p;
};

const int inf = 0x3f3f3f3f;
const int maxn = 5e2 + 10;
const int maxm = 5e2 + 10;

int n;
Room roo[maxn];
int m;
Wallpaper pap[maxm];

int mn, ans;

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {
		scanf("%i%i%i", &roo[i].l, &roo[i].w, &roo[i].h);
	}
	scanf("%i", &m);
	FOR (1, m, i) {
		scanf("%i%i%i", &pap[i].h, &pap[i].l, &pap[i].p);
	}
	
	FOR (1, n, i) {
		mn = inf;
		FOR (1, m, j) {
			if (pap[j].h < roo[i].h) {
				continue;
			}
			int x = pap[j].h/roo[i].h*pap[j].l, allx = 2*roo[i].l + 2*roo[i].w;
			mn = MIN(mn, (allx + x - 1)/x*pap[j].p);
		}
		ans += mn;
	}
	
	printf("%i\n", ans);
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：0)

## [题目在这](https://www.luogu.com.cn/problem/CF139B)
这题题意很好理解，不需要多说。
## 思路
因为此题 $1 \le n,m \le 500$，所以暴力可过（亲测）。先用小学就学过的几何知识，把墙展开成一个矩形，然后算出每个房间所需花费的最小值，再输出所有房间花费的总和。

Ps：特判墙纸的长度小于墙的高。

## Code
已 [AC](https://www.luogu.com.cn/record/168080382)，放心食用。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e2+1;
int n,m;
int zc[N],h[N]; //存房间的底面周长，高 
int ans[N]; //每间房的最小花费 
int rans; //真正的答案 
int main(){
	cin>>n;
	memset(ans,0x3f,sizeof ans); 
	for(int i=1;i<=n;i++){
		int a,b;
		cin>>a>>b>>h[i];
		zc[i]=(a+b)*2; //学过几何的都知道，长方形周长是长加宽的和的 2 倍 
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		int c,k,pr;
		cin>>c>>k>>pr;
		for(int j=1;j<=n;j++){ //更新每间房的最小花费 
			if(c>=h[j]){
				ans[j]=min(ans[j],(((zc[j]-1)/k)/(c/h[j])+1)*pr);
			}
		}
	}
	for(int i=1;i<=n;i++){
		rans+=ans[i]; 
	}
	cout<<rans;
	return 0;
}
```
~~达成成就，结束了？~~

---

## 作者：123456zmy (赞：0)

题意：  
有 $n$ 个房间，$m$ 种墙纸，第 $i$ 个房间的长宽高分别是 $L_i$ $W_i$ $H_i$，第 $i$ 种墙纸的长宽价格分别是 $l_i$ $w_i$ $p_i$，每个房间的四周要贴上同种墙纸，多了也不能用到别的房间，墙纸可以裁剪但不能旋转，且首尾不能拼接（竖直方向必须是同一张墙纸，不能底下用第一张上面用第二张），问至少需要多少钱。
___
对于每个房间分别计算花费的最小值，然后相加输出。（计算方法在代码里有）注意特判墙纸长度小于 $H_i$ 的情况。

代码：（$O(nm)$）
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,w,d[501],h[501],ans[501],anss,p;
int main()
{
	memset(ans,0x3f,sizeof(ans));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&l,&w,&h[i]),d[i]+=l+w<<1;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d%d",&l,&w,&p);
		for(int i=1;i<=n;i++)if(l>=h[i])ans[i]=min(ans[i],(((d[i]-1)/w)/(l/h[i])+1)*p);
	}
	for(int i=1;i<=n;i++)anss+=ans[i];
	printf("%d",anss);
	return 0;
}
~~~

---

