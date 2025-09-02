# [USACO20OPEN] Social Distancing S

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们的健康。

为了限制疾病的传播，Farmer John 的 $N$ 头奶牛（$2\le N\le 10^5$）决定践行“社交距离”，分散到农场的各处。农场的形状如一维数轴，上有 $M$ 个互不相交的区间（$1\le M\le 10^5$），其中有可用来放牧的青草。奶牛们想要使她们位于不同的整数位置，每个位置上均有草，并且最大化 $D$ 的值，其中 $D$ 为最近的两头奶牛之间的距离。请帮助奶牛们求出 $D$ 的最大可能值。

## 说明/提示

### 样例解释
取到 $D=2$ 的一种方式是令奶牛们处在位置 $0$、$2$、$4$、$6$ 和 $9$。

### 子任务
- 测试点 $2$-$3$ 满足 $b\le 10^5$。
- 测试点 $4$-$10$ 没有额外限制。

## 样例 #1

### 输入

```
5 3
0 2
4 7
9 9```

### 输出

```
2```

# 题解

## 作者：PersistentLife (赞：17)

[博客阅读体验更佳](https://www.luogu.com.cn/blog/302837/solution-p6281)

### 题目分析

本题用二分去做，我们二分 $D$ 的值，然后再 $\Theta(N+M)$ 贪心扫一遍，如果可以放得下就往大的找，否则往小的找。

我们二分的范围是从 $0$ 到 $\max b_i$，因为最坏的情况是每头牛都紧紧挨着一起，最优的情况是一头牛在数轴原点，另一头牛在数轴的最大值处。

虽然数轴是无限长的，但是在本题中，小于 $0$ 的部分对答案没有贡献，大于 $\max b_i$ 的部分也对答案没有贡献，所以我们假设数轴是从 $0$ 到 $\max b_i$ 的。 

二分的复杂度为 $\Theta(\log(\max b_i))$，判断是否满足条件的复杂度为 $\Theta(N+M)$。

### 代码实现

回顾一下二分的模板:

```
while(l<r)
{
	mid=(l+r)/2+1;
	if(check()) l=mid;
	else r=mid-1;
}
```
复杂度为 $\Theta(\log(\max b_i)) $。

下面是 $check$ 函数，因为要遍历每头牛和每一段草坪，所以复杂度为 $\Theta(N+M)$。

实现方法见注释：

```cpp
bool check()
{
	int cur=a[1],cnt=1;//分别表示上一次放奶牛的位置和目前在用哪一块草坪 
	for(int i=2;i<=n;i++)//遍历每头牛，因为1号牛一定要放在a[1]的位置，所以可以在预处理里面解决 
	{
		if(cur+mid<=b[cnt]) cur+=mid;//如果这块草坪够放，就放在这块草坪上 
		else//否则 
		{
			while(cnt<m&&cur+mid>b[cnt]) cnt++;//找到下一个放牛的草坪 
			if(cur+mid>b[cnt]) return 0;//如果不够放，那么直接return 0 
			if(cur+mid<=a[cnt]) cur=a[cnt];  
			else cur+=mid;//同第一个if语句，放置这头牛 
		}
	}
	return 1;//若能放下就return 1 
}
```
完整代码：

```
#include<bits/stdc++.h>
#define int long long//懒得区分了
using namespace std;
int n,m,l,r,mid;
int a[123456],b[123456];
bool check()
{
	int cur=a[1],cnt=1;//分别表示上一次放奶牛的位置和目前在用哪一块草坪 
	for(int i=2;i<=n;i++)//遍历每头牛，因为1号牛一定要放在a[1]的位置，所以可以在预处理里面解决 
	{
		if(cur+mid<=b[cnt]) cur+=mid;//如果这块草坪够放，就放在这块草坪上 
		else//否则 
		{
			while(cnt<m&&cur+mid>b[cnt]) cnt++;//找到下一个放牛的草坪 
			if(cur+mid>b[cnt]) return 0;//如果不够放，那么直接return 0 
			if(cur+mid<=a[cnt]) cur=a[cnt];  
			else cur+=mid;//同第一个if语句，放置这头牛 
		}
	}
	return 1;//若能放下就return 1 
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i];//读入
	sort(a+1,a+m+1);
	sort(b+1,b+m+1);//排好序，方便贪心
	l=0;r=b[m];//确定边界
	while(l<r)//二分
	{
		mid=(l+r)/2+1;
		if(check()) l=mid;
		else r=mid-1;
	}
	cout<<l;//输出
	return 0;//完结撒花
}
```



---

## 作者：_zy_ (赞：11)

## [题目传送门](https://www.luogu.com.cn/problem/P6281)

### 题目大意：

求两只奶牛满足每个位置上均有草距离最小值中的最大值。

很显然，最大值最小我们一般运用二分的算法。

- 关于单调性的证明：

当两牛之间的距离较小时，所容纳的牛更多。

当两牛之间的距离较大时，所容纳的牛更少。


------
**关于二分：**

上界:$1。$

下界：最左端到最右端的距离。

$Judge$：我们贪心的找到在x下的满足条件最多可容纳的牛。

**关于处理**

我们先将各个区间从左到右$sort$结构体排序。

定义$pos$为此时放的点的坐标.

- 从第一个点开始放，如果还在区间里，就放到该区间$pos+x$。

- 如果不在就将区间向右移动.

- 如果正好在空区间，就贪心的放到下一个区间的起点。

- 如果在下面的区间里（不一定是下一个），就放在这个位置。

### 代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long 
#define N 100010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n,m,ans,num;
struct zy {
	int l;
	int r;
}e[N];
bool cmp(zy x,zy y) {
	return x.l<y.l;
}
bool Judge(int x) {
	bool flag=0;
	int cnt=1; num=0;
	int sta,lst;
	sta=e[++num].l; lst=e[num].r;
	int pos=e[1].l;
	while(lst<=e[m].r&&!flag)
	{
		int p=pos+x;
		if(p<=lst) {
			pos=p;
			cnt++;
			continue;
		}
		while(p>lst) {
			num++;
			if(num>m) {flag=1;break;}
			sta=e[num].l;
			lst=e[num].r;
			if(p<sta)	pos=sta;
			else pos=p;
		}
		cnt++;
		if(cnt>n)	return true;
	}
	return false;
}
signed main()
{
	n=re(); m=re();
	for(int i=1;i<=m;i++) {
		e[i].l=re();
		e[i].r=re();
	}
	sort(e+1,e+m+1,cmp);
	int L=0; int R=e[m].r-e[1].l;
	while(L<=R) {
		int mid=(L+R)>>1;
		if(Judge(mid)) {
			ans=mid;
			L=mid+1;
		}
		else R=mid-1;
	}
	cout<<ans<<endl;
	return 0;
} 
```
如有不妥，请不要吝啬您的评论。


---

## 作者：kradcigam (赞：5)

这道题是一个二分的模板，先讲一下二分。

二分是确定一个答案然后对其分析，而答案常常有这样一种情况：

![](https://i.loli.net/2020/02/23/1ogLUr7OITxSV8R.png)

或

![](https://i.loli.net/2020/02/23/y1FNhUaTKIAQBCo.png)

题目通常会让我们找符合条件的最大值或最小值。

以这道题为例，就是要在可行的社交距离中找到最大值。

我们发现，社交距离比最优解大的都可以，不最优解小的都不可以。

这个我们叫左闭右开。

二分顾名思义，就是二分。

```cpp
int l=0,r=INT_MAX/2;
while(l+1<r){
    int mid=(l+r)>>1;
    if(check(mid))l=mid;//这里不同
    else r=mid;//这里不同
}
```

我们可以去写一下 `check`:

```cpp
bool check(ll x){
	ll l=0,ans=0;
	for(int i=1;i<=m;i++){
		l=max(l,a[i].a);//左端点
		if(a[i].b>=l){//a[i].r是右端点
			ll X=(a[i].b-l)/x+1;//站的牛的数量
			ans=ans+X;//奶牛数量+X
			l=l+X*x;//更新左端点
		}
	}
	return ans>=n;//是否可行
}
```

总代码：

```cpp
#include <bits/stdc++.h>
#define int long long//注意开long long
using namespace std;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int MAXM=1e5+10;
struct node{
	int a,b;
}a[MAXM];
int n,m;
bool check(int x){
	int l=0,ans=0;
	for(int i=1;i<=m;i++){
		l=max(l,a[i].a);
		if(a[i].b>=l){
			int X=(a[i].b-l)/x+1;
			ans=ans+X;
			l=l+X*x;
		}
	}
	return ans>=n;
}
bool cmp(node a,node b){
	return a.a<b.a;
}
signed main(){
	read(n);read(m);
	for(int i=1;i<=m;i++)read(a[i].a),read(a[i].b);
	sort(a+1,a+m+1,cmp);//排序
	int l=1,r=INT_MAX;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid;
		else r=mid;
	}cout<<l;
	return 0;
}
```

---

## 作者：wylt (赞：4)

USACO 2020 US Open 白银组T1 Social Distancing

原题面（英文）：[http://www.usaco.org/index.php?page=viewproblem2&cpid=1038](http://www.usaco.org/index.php?page=viewproblem2&cpid=1038)

官方题解（英文）：[http://www.usaco.org/current/data/sol_socdist_silver_open20.html](http://www.usaco.org/current/data/sol_socdist_silver_open20.html)



------------
### 题意简述

有 $N$ 头奶牛，$M$ 个互不相交的区间，奶牛只能在区间中且奶牛之间的最小间隔为 $D$，你需要最大化 $D$ 。

### 题目分析

要求最大化最小值，很快可以看出是道二分答案的模板题。

那我们思路就是：

①因为题目未保证输入区间有序，以防万一先排个序，由于互不相交，只要给 $a_{i}$ 排序就行了。

②用标准的二分模板，计算当前的 $mid$ 并用 $check$ 函数检验当 $D=mid$ 时是否有解。

③在 $check$ 函数中分别记录当前已经安放好的奶牛数和上一头奶牛的位置，有个优化是可以直接计算一段草地能够安放的奶牛数

$$cnt=ceil((float)(g[i].r-g[i].l+1)/D)$$

$g[i].r,g[i].l$ 分别为区间的右边，左边位置， $ceil$ 为上取整。

④既然我们可以快速求出一个区间内最多安放的奶牛数，则只要通过前一个区间最后一个奶牛的位置加 $D$ 就可以求出这个区间第一个可安放奶牛的位置。只要把 $g[i].l$ 替换为 $next+D$ 即可算出当前区间的最多安放奶牛数。

注意当 $next+D\le g[i].l$ 时不用替换。

⑤以此类推若此时已安放奶牛数大于 $N$ 就代表此时 $mid$ 可选，返回 $true$ 即可。

⑥回到主函数中，若返回 $true$ ，则 $l=mid+1$，否则 $r=mid-1$ 。

⑦当 $l>r$ 时，输出答案。



------------
### 代码

```cpp
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<set>
using namespace std;
int n,m;
struct node{
	long long l,r;
}g[100005];

bool cmp(node i,node j){
	return i.l<j.l;
}

bool check(long long d){
	long long cnt=ceil((float)(g[1].r-g[1].l+1)/d);
	long long next=g[1].l+d*(cnt-1);
	if(cnt>=n){
		return true;
	}
	for(int i=2;i<=m;i++){
		if(next+d>g[i].l){
			long long tcnt=ceil((float)(g[i].r-next-d+1)/d);
			next=next+d+d*(tcnt-1);
			cnt+=tcnt;
			if(cnt>=n){
				return true;
			}
		} else {
			long long tcnt=ceil((float)(g[i].r-g[i].l+1)/d);
			next=g[i].l+d*(tcnt-1);
			cnt+=tcnt;
			if(cnt>=n){
				return true;
			}
		}
	}
	return false;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>g[i].l>>g[i].r;
	}
	sort(g+1,g+m+1,cmp);
	long long l=0,r=g[m].r,ans;
	while(l<=r){
		long long mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Parat_rooper (赞：2)

**解题思路：**

首先，第一眼看到这个最优性问题我就想到了要把它转换成可信性问题，显然，二分答案是这题最简单，直接的方法。

那我们直接二分 $D$，然后再配上一个 $O(N)$ 的校验，就完美解决这道题啦

详见代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 1e5 + 2;

int n, m;
long long l = 1, r;

struct qu {
  long long l, r;
}q[kMaxN];

bool cmp(qu a, qu b) {
  return a.l < b.l;
}

long long jy(long long jg) {//校验
  long long d = 0;
  long long ans = 0;  // 初始化数量、下一个可以放置的位置
  for (int i = 1; i <= m; i++) {
    d = max(d, q[i].l);			// 当前区间可放
    if (d <= q[i].r) {						// 当前区间可放
      long long v = (q[i].r - d) / jg + 1; // 可以放的数量
      ans += v;			// 累加数量
      d += v * jg;    // 计算下一个可放的位置
    }
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r;
  }
  sort (q + 1, q + m + 1, cmp);
  for (r = q[m].r - q[1].l; l <= r; ) { // 二分答案
    long long d = (l + r) >> 1, k = jy(d);
    if (k < n) {
      r = d - 1;
    } else {
      l = d + 1;
    }
  }
  cout << r;
  return 0;
}
```


---

## 作者：hhhyyyfff (赞：2)

- 题意简述：  
  有 $N\ (1 \le N \le 10^5)$ 头牛，$M\ (1 \le M \le 10^5)$ 段草地 $[l_i,r_i]$ （互不相交），将牛放在草地上，求放入后最近的两头牛的距离最远是多少，保证有解。

- 前置知识：二分答案

- 算法 $O((N+M) \log N)$：  
  将草地从左到右排序，二分答案。
  判定时线性扫描，当前在草地 $i$，前一头牛在坐标 $x$，若 $r_i-x$ 小于答案，则 $i \gets i+1$；否则 $x \gets \max\{x+ans,l_i\}$。

- 代码：

``` cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
long long l, r, mid, a[100010], b[100010];

bool check(long long D) {
    long long last = a[1], now = 1;
    for (int i = 2; i <= N; ++i)
        if (last + D <= b[now])
            last += D; else {
            while (now < M && last + D > b[now]) ++now;
            if (last + D > b[now]) return 0;
            last = last + D <= a[now] ? a[now] : last + D;
        }
    return 1;
}

int main() {
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) scanf("%lld%lld", &a[i], &b[i]);
    sort(a + 1, a + M + 1);
    sort(b + 1, b + M + 1);
    r = b[M];
    while (l < r) {
        mid = (l + r) / 2 + 1;
        if (check(mid))
            l = mid; else
            r = mid - 1;
    }
    printf("%lld\n", l);
    return 0;
}
```

---

## 作者：Hongse_Fox (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P6281)
# 零.前记
第一次尝试的时候对距离的定义有点误解

以为是 $D(i,j)=j-i-1$ 

重点是还过样例了就离谱（捂脸.jpg）

# 一.大体思路
看到题目范围是 $10^5$ 毫不犹豫 $n\log n$ 或者 $n \sqrt n$ 

又看到这道题是要求最值的，

嗯 毫不犹豫二分答案。

# 二.具体做法
那我们就二分一下最短的距离，

注意题目中的区间并没有说从小到大给你，

因此要先排个序。

用一个变量 $h$ 记录目前为止最近的一头牛的位置，

用贪心的思想 每一头牛都是尽可能往前面放，

每枚举一个区间就要结合 $h$ 判断一开始可不可以放：

如果不可以放就从 $h+d$ 的位置放起，

如果 $h+d$ 已经超出区间了就不放了，

再算还能放几头牛 最后再更新 $h$ 。

**code**
```cpp
inline bool check(long long d){
	long long h=0;
	long long ans=0;
	ans+=(a[1].r-a[1].l)/d+1;
	h=a[1].l+d*(ans-1);//第一种情况拿出来分析 
	for(register int i=2;i<=m;i++){
		long long l=a[i].l;//l是可以放的最近的位置 
		if(a[i].l-h<d) l=h+d;//如果h+d>l就把第一头牛放在h+d 
		if(a[i].r<l) continue;//如果第一头牛不再区间里就下一个 
		long long res=(a[i].r-l)/d+1;//还能塞这么多头牛 
		ans+=res;//统计答案 
		h=l+d*(res-1);//更新h 
	}
	if(ans>=n) return 1;
	return 0;
}
```
**注意**
#### 1.记得先排序
#### 2.题目中的距离是位置为 $i$ 和 $j$ 的点之间距离为 $j-i$ 

# 三.代码
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=100005;
inline long long R(){
	long long r=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return r;
}
long long n,m,head,tail,mid;
struct node{
	long long l,r;
}a[maxn];
inline bool comp(node a,node b){
	return a.l<b.l;
}
inline bool check(long long d){
	long long h=0;
	long long ans=0;
	ans+=(a[1].r-a[1].l)/d+1;
	h=a[1].l+d*(ans-1);//第一种情况拿出来分析 
	for(register int i=2;i<=m;i++){
		long long l=a[i].l;//l是可以放的最近的位置 
		if(a[i].l-h<d) l=h+d;//如果h+d>l就把第一头牛放在h+d 
		if(a[i].r<l) continue;//如果第一头牛不再区间里就下一个 
		long long res=(a[i].r-l)/d+1;//还能塞这么多头牛 
		ans+=res;//统计答案 
		h=l+d*(res-1);//更新h 
	}
	if(ans>=n) return 1;
	return 0;
}
int main(){
	n=R();m=R();
	for(register int i=1;i<=m;i++){
		a[i].l=R();a[i].r=R();
		tail=max(tail,a[i].r/(n-1)+5);//最大的情况就是整个区间随机分配 
	}
	sort(a+1,a+m+1,comp);//记得排序 
	head=1;
	while(head<tail){
		mid=(head+tail)/2+1;
		if(check(mid)) head=mid;
		else tail=mid-1;
	}
	printf("%lld\n",head);
	return 0;
}
```
# 四.后记
这道题就是二分的模板，

只要注意题目中的文字游戏即可过掉这道题。

Finally，谢谢大家

[更好的阅读体验](https://www.luogu.com.cn/blog/HongseFox/solution-p6281)

---

## 作者：Masna_Kimoyo (赞：1)

[题目传送门](luogu.com.cn/problem/P6281)

## 思路

### 1. 

首先看到这题孤零零的样例输出，再想想 $USACO$ 的出题套路，嘿嘿……

仔细斟酌一番，我们发现此题满足单调性，于是我们果断决定使用二分

### 2.

在写二分之前，我们先要给混乱分布的开头和结尾排序，由于这道题的参数有两个，所以我们要用特殊顺序排序，这里我索性按照区间结尾从小到大的顺序排了序， $cmp$  代码：

```cpp
inline bool cmp(const node &a,const node &b)
{
	return a.e<b.e;
}
```

这里讲一个优化， $cmp$ 里的两个参数，我们不直接写 $node$ $a$ 和 $node$ $b$ ，按照现在这样的方法写效率会更高，虽然我也不知道为什么，听别人的博客说是因为有 $const$ ……

### 3.

二分的模板非常好写，这里不再赘述，我们现在来考虑二分的 $check$ 函数该怎么写     

$x$ ：这次二分给的参数 

我们在这里先给一个最开始的数： $now$ ，用来记录每次循环开始时上一次最后到了哪个位置，如果它在开始和结尾之间，说明可以继续下去，并在这里将统计的数量加一， $now$ 到下一个位置去，具体位置是 $x+now$，代码具体是这样：

```cpp
while(dis[i].s<=now && dis[i].e>=now)	now+=x,++sum;
```

在这里，我们还会发现另一个问题，如果上次加的时候 $now$ 没有进入这个区间呢？我们再在这里加一个判断，如果是这样，那我们就让 $now$ 变成这次循环的开始,代码如下：

```cpp
if(now<dis[i].s)   now=dis[i].s;
```

## 代码

有了上面的分析，我们有了这样一段代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m;
struct node{
	int e,s;
}dis[N];
inline int read()
{
	int x=0;
	bool w=0;
	char c=getchar();
	while(!isdigit(c))
		w|=c=='-',c=getchar();
	while(isdigit(c))
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}
inline bool cmp(const node &a,const node &b)
{
	return a.e<b.e;
}
inline bool check(int x)
{
	int now=dis[1].s,sum=0;
	for(register int i=1;i<=m;++i)
	{
		if(now<dis[i].s)
			now=dis[i].s;	
		while(dis[i].s<=now && dis[i].e>=now)
				now+=x,++sum;
		if(sum>=n)	return 1;
	}
	return 0;
}
signed main()
{
	n=read(),m=read();
	for(register int i=1;i<=m;++i)
		dis[i].s=read(),dis[i].e=read();
	sort(dis+1,dis+m+1,cmp);
	int l=1,r=dis[m].e;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else	r=mid-1;
	}
	printf("%d",l-1);
	return 0;
}

```
 
完结撒花


---

## 作者：ConvaChen (赞：1)

//社交距离I（美国奥林匹克计算机//公开组 银牌赛#1）

//第二篇题解啦啦啦啦啦啦啦，JAVA人上人上人

这道题目是铜组的加强版，可以回忆一下铜组的那道题目，比较一下两道题目，可以发现银牌赛的这道题目给放牛的put()这个boolean增加的设定。所以，还是采用老二分模版：
```
int LB = 0; int RB = GrassB[m-1];
		while(LB<=RB) {
			int mid = (LB+RB)/2;
			if(Put(mid)) {
				LB = mid+1;
			}
			else {
				RB = mid-1;
			}
		}
```
我们需要做的就是去调整Put（）放牛函数的设定。怎么去调整呢。
1.首先，对草A和草B两个数组排序，可以分成二维数组直接排，代码如下：
```
Arrays.sort(GrassA, new Comparator<int[]>() {
public int compare(int[] o1, int[] o2) {
if (o1[0]==o2[0]) return o1[1]-o2[1];
return o1[0]-o2[0];
}
});
```
但是呢，为了方便JAVA的放牛，我们采用分开成草B和草A两个一维数组进行排序。
2.模拟题目过程，设定CurrentPosition & Cownumber，具体过程见代码Put（）函数，变量名称设的非常清楚，可以供不会C++的JAVA同学传阅
具体代码如下：
```
//2020USACO Open B 1
import java.util.*;
import java.io.*;

public class SocialDistancingI {
	static int n;
	static int m;
	static int[] GrassA;
	static int[] GrassB;
	public static void main(String[] args)throws IOException {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		m = in.nextInt();
		GrassA=new int[m];
		GrassB=new int[m];
		for(int i=0;i<m;i++) {
			GrassA[i]=in.nextInt();
			GrassB[i]=in.nextInt();
		}
		Arrays.sort(GrassA);
		Arrays.sort(GrassB);
		int LB = 0; int RB = GrassB[m-1];
		while(LB<=RB) {
			int mid = (LB+RB)/2;
			if(Put(mid)) {
				LB = mid+1;
			}
			else {
				RB = mid-1;
			}
		}
		System.out.print(RB);
		
	}
	static boolean Put(int mid) {
		int CurrentPosition = GrassA[0];
		int CowNumber = 1;
		for(int i=1;i<n;i++) {
//模拟放牛过程，mid是两头牛之间的具体
if(CurrentPosition+mid<=GrassB[CowNumber-1]) {
				CurrentPosition += mid;
			}
			else {
            //依然模拟
				while(CowNumber<m 
					&&
					CurrentPosition+mid>GrassB[CowNumber-1]) {
					CowNumber++;
				}
				if(CurrentPosition+mid>GrassB[CowNumber-1]) {
					return false;
				}
				if(CurrentPosition+mid<=GrassA[CowNumber-1]) {
					CurrentPosition = GrassA[CowNumber-1];
				}
				else {
					CurrentPosition += mid;
				}
			}
		}
		return true;
	}
	

}

```



---

## 作者：Jayun (赞：1)

# 题目大意：

有 $n$ 头牛和 $m$ 个区间，要求每头牛都在区间内且每相邻的牛之间的间隔都不小于 $d$，求 $d$ 的最大可能值。

# 正文：

说到最大化最小值，一般情况下会想到用二分来解决这些问题。二分最关键的是 `check` 函数，在 `check` 函数中，我们可以通过枚举牛牛的位置来判断当前二分到的 $d$ 是否符合题目中的条件：

1. 在一个区间内，如果上一头牛可以和本牛的间隔达到 $d$ 那么这一头牛就在这一区间。

1. 在一个区间内，如果上一头牛不能和本牛的间隔达到 $d$，那么这一头牛就要找一个可以和上一头牛达到 $d$ 间隔的区间。

如果不符合条件即 $d$ 不可能是答案。

# 代码：

```cpp
inline bool check(int x)
{
	int ans = L[1], now = 1;
	for (int i = 2; i <= n; i++)
	{
		if(ans + x <= R[now])
		{
			ans += x;
		}
		else
		{
			while(ans + x > R[now] && now <= m)
				++now;
			if(ans + x > R[now]) return 0;
			if(ans + x <= L[now])
				ans = L[now];
			else
				ans += x;
		}
	}
	return 1;
}
```

---

## 作者：jiang_cheng (赞：0)

## 解题思路：
这道题用二分答案是比较简单的，首先要对区间排序，因为区间是混乱的。

接着二分答案，二分的左边界就是第一个区间的左边界，右边界就是最后一个区间的右边界。然后写一个函数检验能放多少个，如果个数大于有的奶牛数，就将左边界更新，否则就将右边界更新。

最后，记得要判左边界小于右边界，不然会死循环。答案就是最后的左边界减一。
## 附上代码：
```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kMaxN = 1e5 + 1;

struct E {
  LL l, r;
  bool operator<(const E &e) const {  // 按照左边界排序
    return l < e.l;
  }
} e[kMaxN];
int n, m;
LL l, r;

bool C(LL d) {      // 检验距离为d的合法性
  LL c = 0, p = 0;  // 初始化数量、下一个可以放置的位置
  for (int i = 1; i <= m; i++) {
    p = max(p, e[i].l);             // 更新可以放置的位置
    if (p <= e[i].r) {              // 当前区间可放
      LL v = (e[i].r - p) / d + 1;  // 可以放的数量
      c += v;                       // 累加数量
      p += v * d;                   // 计算下一个可放的位置
    }
  }
  return c >= n;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].l >> e[i].r;
  }
  sort(e + 1, e + 1 + m);
  for (l = 1, r = e[m].r - e[1].l; l <= r;) {  // 二分答案
    LL mid = (l + r) >> 1;
    if (C(mid)) {
      l = mid + 1;  //更新左边界
    } else {
      r = mid - 1;  //更新右边界
    }
  }
  cout << l - 1;
  return 0;
}
```


---

