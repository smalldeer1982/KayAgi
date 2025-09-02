# [USACO23FEB] Cow-libi S

## 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

有人在 Farmer John 的 $G(1 \leq G \leq 10^5)$ 个私人花园里偷吃了庄稼！通过他的专业法医知识，Farmer John 确定了每个花园被偷吃的具体时间。他还发现，这些事件的罪魁祸首是一头单独的奶牛。

为了回应这些犯罪行为，Farmer John 的 $N(1 \leq N \leq 10^5)$ 头奶牛每头都提供了一个不在作案现场的证明（即“不在场证明”），表明奶牛在特定时间出现在特定位置。请帮助 Farmer John 判断这些“不在场证明”中哪些能够证明奶牛的清白。

如果一头奶牛无法在她的“不在场证明”位置与所有被偷吃地点之间往返，则可以确定这头奶牛是清白的。奶牛的移动速度为每单位时间 $1$ 单位距离。本题中提到的距离均为欧几里得距离。

## 样例 #1

### 输入

```
2 4
0 0 100
50 0 200
0 50 50
1000 1000 0
50 0 200
10 0 170```

### 输出

```
2```

# 题解

## 作者：快斗游鹿 (赞：8)

## 思路：

题目中有提到，一头牛总是有可能在所有牧场之间穿梭，也就是说一头牛从任意一个放牧地点出发，都能在所有牧场之间穿梭。

那么考虑将每次吃草事件按 $t$ 从小到大排序。一头牛的不在场证明成立，仅当它无法在所有牧场与自己的不在场证明地点之间穿梭。假设某头牛在第 $t_i$ 时刻有不在场证明，离 $t_i$ 最近且早于 $t_i$ 的吃草事件的时刻为 $k_1$，离 $t_i$ 最近且晚于 $t_i$ 的吃草事件的时刻为 $k_2$。分析一下会发现，只要它不可能在 $(t_i-k_1)$ 的时间内从上一次吃草事件发生地点赶到不在场证明地点，或不可能在 $(k_2-t_i)$ 的时间内从不在场证明地点赶到下一次吃草事件发生地点，它的不在场证明就成立。

那么问题就变成了，找到比不在场证明时间早的最晚发生的吃草事件。因为吃草事件已经按发生顺序排序，所以这次吃草事件的下一次吃草事件就是比不在场证明时间晚的最早发生的吃草事件。该如何找到这次吃草事件呢？可以很容易地想到**二分**。那么问题也就迎刃而解了。

## 一些需要注意的：

$1.$ 题目中的距离指的是**欧几里得距离**，而非曼哈顿距离。

$2.$ 本题对精度要求很高。

$3.$ 如果某个不在场证明时间比所有吃草事件都早或都晚，那么需要特判。

## 代码：

```
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=1e5+5;
struct edge{
	int x,y,t;
}e[N];
int g,n,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(edge XXX,edge YYY){
	return XXX.t<YYY.t;
}
signed main(){
	g=read();n=read();
	for(int i=1;i<=g;i++){
		e[i].x=read();e[i].y=read();e[i].t=read();
	}
	sort(e+1,e+1+g,cmp);//排序
	while(n--){
		double xxx,yyy,ttt;cin>>xxx>>yyy>>ttt;
		int l=1,r=g,I=0;
		while(l<=r){//二分
			int mid=(l+r)>>1;
			if(e[mid].t<=ttt)I=mid,l=mid+1;
			else r=mid-1;
		}
		double total;
		if(!I){
			total=sqrt((double)(xxx-e[I+1].x)*(xxx-e[I+1].x)+(yyy-e[I+1].y)*(yyy-e[I+1].y));
			//cout<<total<<endl;
            if(total>(e[I+1].t-ttt))ans++;
		}
		else if(I==g){
			total=sqrt((double)(xxx-e[I].x)*(xxx-e[I].x)+(yyy-e[I].y)*(yyy-e[I].y));
			//cout<<total<<endl;
            if(total>(ttt-e[I].t))ans++;
		}
		else{
			int cnt=0;
			total=sqrt((double)(xxx-e[I+1].x)*(xxx-e[I+1].x)+(yyy-e[I+1].y)*(yyy-e[I+1].y));
			//cout<<total<<endl;
            if(total>(e[I+1].t-ttt))cnt++;
			total=sqrt((double)(xxx-e[I].x)*(xxx-e[I].x)+(yyy-e[I].y)*(yyy-e[I].y));
			//cout<<total<<endl;
            if(total>(ttt-e[I].t))cnt++;
			if(cnt)ans++;
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Xy_top (赞：5)

银组里的超级水题。

一头奶牛如果有犯罪的嫌疑，那么一定是先把不在场证明之前的罪犯了。然后走到不在场证明点，时间一到，再去犯罪。

首先需要特判一下犯罪地点是否互相矛盾，因为这些罪是同一个牛犯的，所以如果犯完罪后如果没有足够的时间赶往下一个犯罪现场，那么直接输出 $n$ 即可。

至于如何找到不在场证明之前的犯罪和之后的，相信大家都能想到二分吧。

但是其实可以做到 $O(n)$，我们将所有不在场证明排序之后再用指针即可。（排序使用 unordered_map 可以做到 $O(n)$ ）。

至于很多人说的爆精度，你们难道就不会平方吗？

代码很短，不放了。

---

## 作者：_3Zinc_ (赞：4)

在做这道题时，需要注意这句话：**separated by a space describing the location and time of the grazing. It will always be possible for a single cow to travel between all grazings**（题目中没有这句话的翻译，希望能够加上）。

翻译为“数据保证一定存在一头牛可以满足所有抓握”。那么我们可以得到结论：如果一头奶牛能够在 $t_i$ 时刻到达 $(x_i,y_i)$，那么它一定能够满足所有抓握，即这头奶牛有嫌疑。

所以我们考虑可以先按照 $t$ 进行排序。对于每次询问，某头奶牛是否可以到达与其证词时间最相近的两个抓握。对于这一查询，可以使用二分查找加速。

代码丑陋，仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int g,n,ans;
struct point {
	ll x,y,t;
	friend bool operator <(const point tmp1,const point tmp2) {
		return tmp1.t<tmp2.t;
	}
};
point p[100005];
ll tim[100005];
bool check(int i,ll t,ll x,ll y) {
	return (x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)<=(t-p[i].t)*(t-p[i].t);
}
int main() {
	scanf("%d%d",&n,&g);
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].t);
	sort(p+1,p+1+n);
	for(int i=1;i<=n;i++) tim[i]=p[i].t;
	for(int i=1;i<=g;i++) {
		ll x,y,t;
		scanf("%lld%lld%lld",&x,&y,&t);
		int pos=lower_bound(tim+1,tim+1+n,t)-tim;
		if(pos==1) ans+=check(pos,t,x,y)?1:0;
		else if(pos-1==n) ans+=check(pos-1,t,x,y)?1:0;
		else ans+=(check(pos,t,x,y)&&check(pos-1,t,x,y))?1:0;
	}
	printf("%d\n",g-ans);
	return 0;
}
```

---

## 作者：cff_0102 (赞：3)

好抽象的翻译啊，我都差点没看懂。还是引用英文原文吧。

注意到原文中提到“He has also determined that there was a single cow that was responsible for every grazing incident.”，即保证了所有点之间在规定的时间内互相可达。又注意到原文“A cow can be determined to be innocent if it is impossible for her to have travelled between **all** of the grazings and her alibi.”，即一头牛有罪，当且仅当它可以同时到达所有点。因此，实际上我们只需要找到时间在它之前的最后一个点，和时间在它之后的第一个点，判断这头牛是否可以同时到达这两个点就行了。`lower_bound` 秒了。

注意本题需要用 `long double`。

```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
const int N=1e5+5;
tuple<int,int,int>gs[N];
bool chk(tuple<int,int,int>b,int xa,int ya,int ta){
	int tb=get<0>(b),xb=get<1>(b),yb=get<2>(b);
	double dt=abs(ta-tb),dx=xa-xb,dy=ya-yb;
	double dis=sqrt(dx*dx+dy*dy);
	return dis<=dt;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int g,n;cin>>g>>n;
	for(int i=1;i<=g;i++){
		int x,y,t;cin>>x>>y>>t;
		gs[i]=make_tuple(t,x,y);
	}
	sort(gs+1,gs+1+g);
	int ans=0;
	for(int i=1;i<=n;i++){
		int x,y,t;cin>>x>>y>>t;
		int p=lower_bound(gs+1,gs+1+g,make_tuple(t,x,y))-gs-1;
		ans+=(p==0||chk(gs[p],x,y,t))&&(p==g||chk(gs[p+1],x,y,t));
	}
	cout<<n-ans;
	return 0;
}
```

---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门：](https://www.luogu.com.cn/problem/P9125)

二分。

如果一头奶牛能在 $t_i$ 时刻到达（$x_i$，$y_i$），那么它一定能满足所有“抓握”，即这头奶牛有嫌疑。

先将 $t$ 进行排序，每头奶牛是否能到达与证词时间最接近的“抓握”，可以使用二分查找。

二分查找为了方便，**通常**可以使用 `lower_bound` 或 `upper_bound`。

---

## 作者：Y_QWQ_Y (赞：1)

嘤嘤嘤我真的太菜了，这么简单的题没想明白导致我做了一个月。
### 前置芝士
[双指针](https://blog.csdn.net/qq_73201597/article/details/136312898)。

[二分](https://blog.csdn.net/MLJYHP/article/details/128756743)。


### 题目大意
给定一些时间节点以及坐标表示一次犯罪，以及另一部分时间节点和坐标表示一个不在场证明。

显然，如果一头牛可以从它不在场证明之前时间最近的犯罪地点走到不在场证明的地方，再从不在场证明的地点走到下一个时间最接近的犯罪地点（时间足够到达的情况下），就说明他有犯罪的嫌疑。

需要求没有犯罪嫌疑的牛的数量。

### 解题思路
对于这种找离一个数最近的数的问题，我们考虑使用双指针（或二分）。

我们可以先把不在场证明和每一次犯罪按照时间顺序从小到大排序，再做双指针，推动指针，找到每次距离不在场证明时间最近的一次犯罪。当这次犯罪在不在场证明之前，那么不在场证明之后最近的犯罪一定是下一次犯罪。（犯罪已经按照时间从小到大排好了）因为在不在场证明前离不在场证明时间最近的犯罪是当前这一次犯罪，不会有比这一次犯罪更近且在不在场证明之前的了。同理，若犯罪时间在不在场证明之后，那么在不在场证明之前时间最接近的犯罪一定是上一次犯罪。

对于二分做法，只需将记录犯罪的数组排序，然后找到时间离这头牛的不在场证明时间最近的一次犯罪，剩下的部分同双指针。

接下来，我们需要计算他是否同时满足：既可以从时间最近的前一次犯罪到达不在场证明的地点，又能从不在场证明的地点到达下一次犯罪的地点，并且时间足够。

### 代码实现

注意了，题目中没有说明，奶牛们都是走直线的，也就是曼哈顿距离，可以用取平方来解决精度的问题，因为同时开方后，相对大小不变，所以开方后相对大小也不变，不会影响比较。

那么我们可以写出以下距离函数：
```cpp
int dis (int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    //本来应该再开方一次，但是考虑精度问题，并且题目只需要比较，所以可以用原式的平方代替。
}
```
时间也要开平方。

那么我们就可以写出一个 `check` 函数表示从犯罪地点 $a_i$ 是否能到达不在场证明的地点 $b_j$。
```cpp
bool check (int i, int j)
{
	int dis1 = dis (a[i].x, a[i].y, b[j].x, b[j].y), dis2 = (a[i].t - b[j].t) * (a[i].t - b[j].t);
    //时间取平方，就不用加绝对值了。
	return dis1 <= dis2;
}
```

下面给出双指针部分，剩下的输入和排序，随便搞搞就可以了。
```cpp
int i = 1, j = 1;
while (j <= n)
{
	while (abs (a[i].t - b[j].t) > abs (a[i + 1].t - b[j].t) && i < n)++ i;
	int k = 0;
	if (b[j].t > a[i].t)k = i + 1;
	else k = i - 1;
	//k 表示在 i 的相反方向的犯罪。
	bool f = check (i, j);
	if (k)f &= check (k, j);
	if (! f)++ cnt;
	++ j;
	//都满足就说明它有嫌疑，题目要求清白的牛的数量，所以不是都满足的才算入答案。
}
```
完结撒花！

---

## 作者：Genius_Star (赞：1)

### 思路：

发现只要奶牛对于离证词的时间最近的抓握，奶牛都可以走到，那么它就有嫌疑。

于是先对抓握按照**时间**升序排序，对于每只奶牛，可以二分找到证词最近的抓握，如果都可能到达，那么有它就有嫌疑，记录答案。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y,t;
	bool operator<(const Node&rhs)const{
		return t<rhs.t;
	}
}a[N],b[N];
ll n,m,ans;
bool check(ll x1,ll y1,ll x2,ll y2,ll t1,ll t2){
	return (((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<=((t1-t2)*(t1-t2)));
}
int main(){
	n=read(),m=ans=read();
	for(int i=1;i<=n;i++)
	  a[i]={read(),read(),read()};
	for(int i=1;i<=m;i++)
	  b[i]={read(),read(),read()};
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++){
		auto it=lower_bound(a+1,a+n+1,b[i])-a;
		if(it==1)
		  ans-=check(a[it].x,a[it].y,b[i].x,b[i].y,a[it].t,b[i].t);
		else if(it==n+1)
		  ans-=check(a[it-1].x,a[it-1].y,b[i].x,b[i].y,a[it-1].t,b[i].t);
		else
		  ans-=(check(a[it].x,a[it].y,b[i].x,b[i].y,a[it].t,b[i].t)&&check(a[it-1].x,a[it-1].y,b[i].x,b[i].y,a[it-1].t,b[i].t));
	}
	write(ans);
	return 0;
}
```


---

## 作者：0x282e202e2029 (赞：0)

# P9125 [USACO23FEB] Cow-libi S 题解

[题目传送门](https://www.luogu.com.cn/problem/P9125)

## 前置知识

请大佬直接跳转至思路篇。

### `upper_bound` 与 `lower_bound`

`template ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& val)` 指向 $[first,last)$ 中第一个 $> val$ 的元素。

`template ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& val)` 指向 $[first,last)$ 中第一个 $≥ val$ 的元素。如果所有元素都 $< value$，则返回 $last$ 的位置。

### `iterator -> first` 是什么?

`map<X, Y>` 实际储存了一串 `pair<const X, Y>`。

现在有一个 `map<X, Y>::iterator it`。

现在可以接收 `pair` 的两个元素：

`(*it).first` 会得到 $key$，

`(*it).second` 会得到 $value$。

这等同于 `it -> first` 和 `it -> second`。

### `pair`

需要 `pair` 头文件。

`pair` 将 $2$ 个数据组合成一个数据，当需要这样的需求时就可以使用 `pair`。

（1）STL 中的 `map` 就是将 $key$ 和 $value$ 放在一起来保存。

（2）另一个应用是，当一个函数需要返回 $2$ 个数据的时候，可以选择 `pair`。

`make_pair` 函数可将 $2$ 个数据组合成一个 `pair`。

`pair.first` 与 `pair.second` 分别返回 `pair` 中的第 $1$，$2$ 个数据。

## 思路

首先，为了使后面思路变得更简便，使用 `sort` 对所有抓握**按时间顺序**进行排序。

题目中说，对于一头牛，它可以在牧场中**随意穿梭**。

那么，仔细想一想，其实，只要它**不可能在足够的时间内从上一次抓握处赶到证明地点，或不可能在足够的时间内从证明地点赶到下一次抓握处**，那么它一定不可能到达任意一个抓握处，**它的不在场证明就成立**。

因为抓握已经按时间顺序排序，所以这次抓握的下一次抓握就是比不在场证明时间晚的最早发生的抓握。

那么，对于寻找上一次抓握和下一次抓握容易想到二分的方法。

代码稍微用了一点~~奇技淫巧~~ STL 大法：（STL 大法好）

①二分用 STL 函数 `lower_bound` 和 `upper_bound` 就可以完美解决。

②使用 `pair<int, int>` 代替坐标。

③并且在求距离时使用 $dis^2$ 代替 $dis$，从而省去使用 `sqrt` 函数造成精度丢失。（因为 $dis^2_{max} = 2 \times (2 \times 10^9)^2 = 8 \times 10^{18}$ 所以记得开 `long long`）

下面直接看代码，不作过多解释。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
map< int, pair<int, int> > mp;
long long dis(pair<int, int> a, pair<int, int> b)//利用pair<int, int>存储坐标
{
	return 1ll * (a.first - b.first) * (a.first - b.first) + 1ll * (a.second - b.second) * (a.second - b.second);
}//使用dis的平方代替dis
int m, n, x, y, t, ans;
bool flag;
map< int, pair<int, int> >::iterator it;//map的iterator迭代器
struct Node
{
	int x, y, t;
}nd[100005];//抓握
bool cmp(Node a, Node b)
{
	return a.t < b.t;
}
int main()
{
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &x, &y, &t);
		mp[t] = make_pair(x, y);//坐标
		nd[i] = {x, y, t};//结构体赋值简便写法
	}//输入
	sort(nd + 1, nd + m + 1, cmp);//保证有序
	for(int i = 1; i < m; i++)
	{
		if(dis(make_pair(nd[i].x, nd[i].y), make_pair(nd[i + 1].x, nd[i + 1].y)) > 1ll * (nd[i + 1].t - nd[i].t) * (nd[i + 1].t - nd[i].t))//优化，如果存在两相邻抓握点时间不足以让奶牛在规定时间到达
		{
			printf("%d", n);//所有奶牛都是清白的
			return 0;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &x, &y, &t);
		it = mp.lower_bound(t);
		flag = false;
        	//如果下面两种情况中有一种成立就将ans加1
		if(it != mp.end())//不是所有元素都 <t
		{
			if(dis(it -> second, make_pair(x, y)) > 1ll * (it -> first - t) * (it -> first - t))//写法详见前置知识篇
			{
				flag = true;
			}
		}
		it = mp.upper_bound(t);
		if(it != mp.begin())
		{
			it = prev(it);
			if(dis(it -> second, make_pair(x, y)) > 1ll * (t - it -> first) * (t - it -> first))
			{
				flag = true;
			}
		}
     		//寻找上一次抓握和下一次抓握
		ans += (int) flag;
	}
	printf("%d", ans);//输出
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/110802263)

---

