# [ABC376C] Prepare Another Box

## 题目描述

有 $N$ 个玩具，编号从 $1$ 到 $N$ ，以及 $N-1$个箱子，编号从 $1$ 到 $N-1$。玩具 $i$ 的大小为$A_i$，箱子 $i$ 的大小为$B_i$。高桥君想把所有玩具分别放入不同的箱子中。他计划按以下步骤操作：

- 选择任意正整数 $x$，购买一个大小为 $x$ 的箱子。

- 将 $N$ 个玩具分别放入 $N$ 个箱子（包括原有的箱子和新购买的箱子）中，但每个玩具只能放入大小不小于该玩具的箱子，且每个箱子只能放一个玩具。

高桥君想通过购买合适大小的箱子来完成第 $2$ 步，但箱子越大价格越高，因此他想尽可能购买小箱子。请判断是否存在能满足条件的 $x$ 值，如果存在，请输出最小值；如果不存在，请输出 $-1$。

## 样例 #1

### 输入

```
4
5 2 3 7
6 2 8```

### 输出

```
3```

## 样例 #2

### 输入

```
4
3 7 2 5
8 1 6```

### 输出

```
-1```

## 样例 #3

### 输入

```
8
2 28 17 39 57 56 37 32
34 27 73 28 76 61 27```

### 输出

```
37```

# 题解

## 作者：huangrenheluogu (赞：3)

贪心。

因为最后拿的盒子尽量小，所以把尽量大的玩具放到当前最大的盒子里面，如果放不了就是需要加盒子。最后扫一遍判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, a[N], b[N], ans;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) scanf("%d", &b[i]);
	sort(a + 1, a + n + 1), sort(b + 1, b + n);
	reverse(a + 1, a + n + 1), reverse(b + 1, b + n);
	ans = a[n];
	for(int i = 1; i <= n; i++){
		if(a[i] > b[i]){
			ans = a[i];
			for(int j = i + 1, k = i; j <= n; j++, k++){
				if(a[j] > b[k]){
					puts("-1");
					return 0;
				}
			}
			printf("%d\n", ans);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：MLE_Automaton (赞：3)

感觉这次 C 比 D 难。

# 题目分析

给你 $n$ 个玩具的体积和 $n - 1$ 个箱子的容积，一个箱子能装下一个玩具当且仅当箱子的容积大于等于玩具的体积，问你再买一个容积最小为多少的箱子，能使所有的箱子能装下所有的玩具。

首先，不难看出答案有可二分性，即为：如果你买了容积为 $w$ 的箱子，那么你也能买容积为 $w + x$（$x$ 为正整数）的箱子。

然后，如果体积为 $w$ 的玩具要装进买的箱子里，肯定会买容积为 $w$ 的箱子。

# Talk is cheap, show me your code.

我这里使用的并不是二分答案，而是二分答案在 $a$ 中的下标。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define pre(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
#define bigpq(type) priority_queue<type>
#define smpq(type) priority_queue<type,vector<type>,greater<type>>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n, a[200005], b[200005];
bool check(int x)
{
	rep(i, 1, n)
	{
		if (i == x) continue;
		if (a[i] > b[i - (i > x)]) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n - 1) scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n);
	int l = 1, r = n;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d", check(l) ? a[l] : -1);
    return 0;
}

```

---

## 作者：Cosine_Func (赞：2)

据说 CSP 考前写题解会 RP++，我也写几篇！

观察题面。“尽可能小”是二分的常见标志，并且 $X$ 的存在具有明显的单调性，考虑二分答案 $X$。先对数组 $A,B$ 排序再二分。`check` 函数内部，在数组 $B$ 中试图找到一个大于等于 $X$ 且最小的数，并试图匹配每一个 $A_i$。时间复杂度 $O(N\times \log N \times \max A_i)$。

核心代码如下：
```cpp
int n,x;
vector<int> a,b;
bool check(itn x){
	int j=upper_bound(b.begin(),b.end(),x)-b.begin();
	for(int i=0;i<n;i++){
		int u;
		if(i<j)u=b[i];
		else if(i==j)u=x;
		else u=b[i-1];
		if(u<a[i])return 0;
	}
	return 1;
}
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x,a.pb(x);
	for(int i=1;i<n;i++)
		cin>>x,b.pb(x);
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	int l=1,r=1e12,ans=-1; 
	while(l<=r){
		int mid=l+(r-l)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
}
```
[参考代码](https://atcoder.jp/contests/abc376/submissions/58966461)

---

## 作者：xzz_0611 (赞：1)

[洛谷传送门](/problem/AT_abc376_c)
[AtCoder 传送门](https://atcoder.jp/contests/abc376/tasks/abc376_c)
### 思路分析
由于有 $N$ 个玩具，$N-1$ 个箱子，所以只能有一个玩具无法放。同时，为了防止空间浪费，那么就需要小箱子装小玩具，大箱子装大玩具。

此时，可以将玩具和箱子的重量和容量**从小到大**排序，**从后往前**依次判断容量第 $i$ 大的箱子能否装下重量第 $i$ 大的玩具，找到**第一个**装不下的组合（设其 $A$ 数组下标为 $j$）。由于只能有一个玩具放不下，所以可以判断重量最轻的 $j-1$ 个玩具是否**都能**依次放入容量最小的 $j-1$ 个箱子中，如果可以则输出 $A_j$，否则无解。
### Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
signed main() {
	ios::sync_with_stdio(false), cin.tie(), cout.tie();
	int n, a[200001], b[200001];
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i < n; ++i) cin >> b[i];
	sort(a + 1, a + n + 1);//从小到大排序
	sort(b + 1, b + n);//从小到大排序
	while (a[n] <= b[n - 1]) --n;//从后向前判断每一对箱子和玩具
	for (int i = 1; i < n; ++i) if (a[i] > b[i]) return cout << -1, 0;//如果还有放不了的则输出 -1
	cout << a[n];
	return 0;
}
```

---

## 作者：minVan (赞：1)

**题目大意**

给定一个长度为 $n$ 的数列 $a$ 和长度为 $n-1$ 的数列 $b$。求最小的 $x$ 使得数列 $b$ 与 $x$ 构成的一种排列方式 $c_1,c_2,\dots,c_n$ 使得任意 $1\le i\le n$ 满足 $c_i\ge a_i$。

**解题思路**

首先将 $a$ 和 $b$ 都从小到大排序，为了方便计算，$b$ 数组从 $2$ 开始计算。

对于每个 $b_i$，我们设 $c_i$ 为 $a$ 中第一个大于它的数所在的位置。

下面用样例三来解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/qlu9a4fn.png)

$x$ 初始时为 $a_1$。

不难发现，从后往前扫，当发现第一个 $c_i<i$ 时（图中即 $c_5=4<5$），那么所对应的 $a_i$ 就需要一个 $x$，$x$ 最小时取 $a_i$，接下来条件改为 $c_i<i-1$。如果接下来还存在这样的数，那么不可能找到满足条件的 $x$，输出 $-1$。

**AC 代码，请勿抄袭。**

赛时代码，写的有点丑。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], b[N], c[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for(int i = 2; i <= n; i++) {
    cin >> b[i];
  }
  sort(b + 2, b + n + 1);
  int ans = a[1];
  for(int i = n; i > 1; i--) {
    c[i] = upper_bound(a + 1, a + n + 1, b[i]) - a - 1;
    if(c[i] < i - (ans != a[1])) {
      if(ans == a[1]) {
        ans = a[c[i] + 1];
      } else {
        cout << "-1";
        return 0;
      }
    }
  }
  if(b[2] < a[1]) {
    cout << "-1";
    return 0;
  }
  cout << ans;
  return 0;
}
```

Update：貌似并不需要 `upper_bound`，只需判断 $b_i<a_{i}$ 即可。

---

## 作者：Anins (赞：1)

## [[ABC376C] Prepare Another Box](https://www.luogu.com.cn/problem/AT_abc376_c)

### 题意：

给定 $N$ 个物品，第 $i$ 个的体积为 $a_i$，以及 $N-1$ 个箱子，第 $i$ 个的体积为 $b_i$，让我们添加一个箱子，使得每个物品都能找到一个不小于它的箱子，求添加箱子的体积的最小值，无解输出 $-1$。

### 思路：

每次给当前体积最大的物品分配当前体积最大的箱子，如果该箱子体积小于当前物品，则添加一个与物品体积相同的箱子，若需要添加两个及以上箱子，则无解。

#### 正确性证明：

- 为什么用最大箱子？

  若可以用非最大箱子，那么最大箱子就留给了其他物品用，这是等价的，并不会对后面的箱子选择产生影响。

- 为什么最大箱子不满足时创建一个箱子？

  若当前最大箱子不满足当前最大物品，那么可以取之前的比当前大的箱子来满足当前物品，但这样就没有箱子满足之前箱子对应的物品，需要为那个物品创建箱子，显然不如为当前物品创建箱子更优。

关于正确性的其他问题读者可以自行思考。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n, a[200005], b[200005];
bool cmp(ll x, ll y) {
	return x>y;
}
int main() {
	scanf("%lld", &n);
	for(int i=1; i<=n; i++) scanf("%lld", &a[i]);
	for(int i=1; i<n; i++) scanf("%lld", &b[i]);
	sort(a+1, a+n+1, cmp);
	sort(b+1, b+n, cmp);
	ll ans=0;
	for(int ai=1, bi=1; ai<=n&&bi<n; ai++) {
		if(b[bi]<a[ai]) { 
			if(ans>0) { //之前已经创建过箱子，无解 
				ans=-1;
				break;
			} else ans=a[ai]; //存储箱子体积 
		} else bi++;
	}
	if(ans==0) ans=a[n]; //前n-1个都满足，那么就为第n个创建箱子
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：zhengyi0402 (赞：0)

# ABC376 C题题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc376_c)

数据范围里重要的数字会被标成亮蓝色。

## 数据范围

$2 \le n \le 2 \times 10^5$

$1 \le a_i \le \color{aqua} 10^9$

$1 \le b_i \le \color{aqua} 10^9$

## 核心思路

在我尝试了多种方法后，我决定使用二分答案的方法。

肯定有人要问：答案也能二分吗？

能！

这题的纸箱子最大是 $10^9$，所以我们二分所有可能的答案，再代入数组中判断，不会超时。

如果可以，尝试更小的答案；如果不行，尝试更大的答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[222222],b[222222];
int ans = -1;
int a2[222222],b2[222222];
bool check(int x){
	for(int i = 1;i <= n;i++)a2[i]=a[i];
	for(int i = 1;i < n;i++)b2[i]=b[i];
	b2[n]=x;
	sort(a2+1,a2+n+1);
	sort(b2+1,b2+n+1);
	for(int i = 1;i <= n;i++){
		if(b2[i]<a2[i])return 0;
	}return 1;
}
void efans(int mx){
	int l = 1,r = mx;
	while(l<=r){
		int mid = (l+r)/2;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
}
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	int mx = -LONG_LONG_MAX; 
	for(int i = 1;i <= n;i++){
		cin>>a[i];mx=max(mx,a[i]);
	}
	for(int i = 1;i < n;i++){
		cin>>b[i];
		mx=max(mx,b[i]);
	}
	efans(mx);
	cout<<ans<<endl;
	return 0;
	//十年OI一场空，define int 见祖宗。
	//十年OI一场空，不开long long见祖宗。
}

```
时间复杂度：$O(n\log{n})$。

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc376_c)

### 思路

这题显然不能直接暴力，我们需要优化它。

我的思路是二分答案。就是说从 $1$ 到 $10^9$ 去找 $x$ 的值，每一次把二分出的 $x$ 的值放入 $b$ 数组中，成为新的箱子，如果我们要最优情况的话肯定希望 $a$ 和 $b$ 的每一个位置的值都尽量接近，那么每次把 $a$ 和 $b$ 从小到大排序就行。

那么二分的条件是什么呢？其实我们可以发现，只有所有的箱子都装得下与它最接近的玩具才行，也就是有一个不行就整个都不行了。

接下来，我们需要思考什么时候动 $l$，什么时候动 $r$。那么很显然，当箱子装不下时，说明 $x$ 小了，要扩大，也就是动 $l$，当装得下时，题目中说要“尽可能购买小箱子”，所以还是要动 $r$，看看能不能再小一点。

至此，二分代码就出来了。

但要注意以下两个细节：

- 需要一个数组 $c$ 来存原来的 $b$，因为 $b$ 在每一次排序中都有可能发生**变化**，而每次我们都是需要他原来的箱子的。

- 记得判无解的情况，如果 $r$ 没动过，说明没有符合的 $x$，此时输出 $-1$。
### CODE


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200005],b[200005],sum,x,l=-1,r,mid,xn,flag,c[200005];//初始化l
int main() {
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<n;i++)
	{
		cin>>b[i];
		c[i]=b[i];//存原来的b[i]
	}	
	sort(a+1,a+n+1);//排序
    sort(b+1,b+n);//排序
	r=1e9+1;//初始r
	while(l+1<r)
	{
		mid=(l+r)/2;
		for(int i=1;i<n;i++)
		{
			c[i]=b[i];
		}
		c[n]=mid;
		sort(c+1,c+n+1);//每次都排序
		flag=1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>c[i])//如果装不了，就不行
			{
				flag=0;
				break;
			}
		}
		if(flag==1)  r=mid;//可以，动r
		else  l=mid;//不行，动l
	}
	if(r!=1e9+1)  cout<<r;
	else  cout<<-1;//注意判无解
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

典题。

对于盒子 $x$，如果 $x$ 成立，$x+1$ 显然成立，因此答案满足单调性，考虑二分答案转判定。

因为有 $n$ 个球与 $n$ 个盒子，所以球与盒子**一一对应**。如果有一个盒子装不下球，那么这个方案必定不合法。

因此，将所有的球与盒子排序，如果有一个盒子装不了当前球，就报告无解。

代码：
```
// Problem: C - Prepare Another Box
// Contest: AtCoder - AtCoder Beginner Contest 376
// URL: https://atcoder.jp/contests/abc376/tasks/abc376_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5;
//#define int long long
int n;
int a[N],b[N],c[N];

bool check(int x)
{
	for(int i=1;i<n;i++) c[i]=b[i];
	c[n]=x;
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++) if(a[i]>c[i]) return 0;
	return 1;
}

signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++) cin>>b[i];
	int l=0,r=1000000000,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[at原题面](https://atcoder.jp/contests/abc376/tasks/abc376_c)
## 题目分析：
理解题意后可以发现是个模拟题。  
我们贪心的想，将玩具和盒子都从大到小排序，线性枚举玩具，单独开个指针枚举盒子，能装则装，不能装则记录下玩具，指针偏移等于 $2$ 时直接跳出即可。
## Code：
```cpp
#include<bits/stdc++.h>
#define starrail main
#define lowbit(x)  (x&(-x))
#define re registe
#define il inline
#define fi first
#define se second
using namespace std;
typedef long long ll;
il int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int N=2e5+10;
int n,a[N],b[N],ans,tot=1;
int ot=0;
bool cmp(int a,int b){
	return a>b;
}
signed starrail(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++)
		b[i]=read();
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+n,cmp);
	for(int i=1;i<=n;i++){
		if(b[tot]>=a[i]){
			tot++;
			continue;
		}
		else{
			ot++;
			if(ot==2){
				cout<<-1<<"\n";
				return 0;
			}
			ans=a[i];
		}
		if(tot==n){
			cout<<a[n]<<"\n";
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路
考虑贪心。

显然，如果有解，则恰好会有一个物品多出来。

考虑大的物品放在尽量大的盒子中一定更优，所以先将盒子和物品分别排序，能放则尽量放，最后放不下的物品需要单独开盒。

因为如果有小的物品放在一个本该大的物品放的盒子中，则要么答案一样，都放不下或都放的下，要么原来小的能放下的地方大的放不下。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
int a[N],b[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n);
	int r=n-1,id=0;
	for(int i=n;i>=1;i--)
	{
		if(a[i]>b[r])
		{
			if(id)//已有一个无法放置的物品
			{
				cout<<"-1\n";
				return 0;
			}
			id=i;//无法放置的物品
			continue;
		}
		r--;
		if(r<0)
		{
			cout<<"-1\n";
				return 0;
		}
	}
	cout<<a[id]<<'\n';
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
显然，若想要让新买的盒子较小，则要尽可能利用原先的盒子——让最大的盒子装最大的货物，次大的盒子装次大的货物……如果出现某个盒子装不下某个货物，则就得买一个盒子了。然后判断一下剩下的盒子能不能装剩下的货物就行了。

[代码](https://atcoder.jp/contests/abc376/submissions/58944972)。

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
用贪心的思路，每次用最大的箱子装最大的物品，接下来判断：

- 若装的下，则配对成功，标记掉物品和箱子。
- 否则，则记录下物品，并标记它。

最后判断，如果有 $2$ 个及以上的物品没配对成功，则输出 $-1$，否则输出物品大小。 


具体实现，我们可以用优先队列来存储物品和箱子，用 `vector` 来记录配对失败的物品。 

## CODE：

```cpp
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
int n, a, b;
priority_queue <int> qp1, qp2;
vector <int> v;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) 
    {
        cin >> a;
        qp1.push(a);
    }
    for (int i = 1; i < n; i++) 
    {
        cin >> b;
        qp2.push(b);
    }
    while (!qp1.empty() && !qp2.empty())
    {
        int u1 = qp1.top(), u2 = qp2.top();
        if (u1 <= u2)
        {
            qp1.pop();
            qp2.pop();
        }
        else
        {
            v.push_back(u1);
            qp1.pop();
        }
    }
    if (v.size() == 0) v.push_back(qp1.top());
    if (v.size() > 1) cout << -1;
    else cout << v[0];
    return 0;
}
```

---

## 作者：Noah2022 (赞：0)

### 题目大意
给你 $ a,b $ 两个数组， $ b $ 的长度为 $ N - 1 $ 。求一个数 $ X $ ，将这个数加进 $ b $ 数组内，使得 $ a , b $ 两个数组匹配的情况下， $ X $ 最小，若不行，则输出 $ -1 $ 。

##### 匹配是什么？
> 匹配指在不重复配对的情况下， $ a $ 数组上的数配对一个 $ b $ 数组的一个数，且 $ a $ 数组选的数小于等于 $ b $ 数组选的数。

##### 匹配的例子：
$ a : 1 , 2 , 3 , 4 $

$ b : 2 , 3 , 4 , 5 $

$ a $ 与 $ b $ 两两相配对，且 $ 2>1 , 3>2 , 4>3 , 5>4 $ 所以匹配成功。

### 思路
先提前将 $ a $ 数组排好序，再使用二分选数的方式 $ X $ 。判断方式：将 $ c $ 数组赋值成 $ b $ ，再加入 $ X $ 后排序，枚举 $ 1 $ 至 $ N $ 中的 $ a_i $ 是否 $ \le c_i $ 即可。**二分的上界要定大一点，别像我定成 1e9+7 WA 了一个点**。

### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],b[200005],c[200005],bj[200005],sum,sum1;
inline bool check(int k) // 判断是否成立
{
	for(register int i(1);i<n;i=-~i) c[i]=b[i];
	c[n]=k;
	sort(c+1,c+1+n);
	for(register int i(1);i<=n;i=-~i)
	{
		if(c[i]<a[i]) return false;
	} 
	return true;
}
signed main()
{
	cin>>n;
	for(register int i(1);i<=n;i=-~i) cin>>a[i];
	for(register int j(1);j<n;j=-~j) cin>>b[j];
	sort(a+1,a+1+n);
	int l=0,r=3e9; // 二分查找
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	if(l==3e9) cout<<-1; // 记住：找到上界时输出 -1 !!!
	else cout<<l;
}
```

---

## 作者：Pollococido (赞：0)

#### 题目大意
给定长度为 $N$ 的数组 $A$，和长度为 $N - 1$ 的数组 $B$。找到最小的 $x$，使得在 $B$ 中插入 $x$ 后，对于任何的 $i$ 使得 每个 $A_i$ 都可以找到一个不大于 $A_i$ 的 $B_i$。
#### 约定
- $\operatorname{Range(A)}$ 表示 $A$ 数组的极差。
#### 思路
较为暴力的方法。

首先，可以枚举来找到最小满足条件 $x$，时间复杂度 $O(N \left(\operatorname{Range(A)}\right))$。无法通过。

发现当 $x$ 满足条件且最小时，$1 \sim x-1$ 均不满足条件，大于 $x$ 的均满足条件。于是二分 $x$，即可解决。我写的垃圾代码时间复杂度**应该是** $O\left(N \log^2 N\right)$。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ps, l = 0x3f3f3f3f, r = -0x3f3f3f3f;
int a[200010], b[200010], ax[200010], bx[200010];
bool check(int x) {
    for (int i = 1; i <= n; i++) ax[i] = a[i];
    for (int i = 1; i < n; i++) bx[i] = b[i];
    bx[n] = x;
    sort(ax + 1, ax + n + 1);
    sort(bx + 1, bx + n + 1);
    for (int i = 1; i <= n; i++) {
        if (ax[i] > bx[i]) return false;
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], r = max(r, a[i]), l = min(l, a[i]), ax[i] = a[i];
    for (int i = 1; i < n; i++) cin >> b[i], bx[i] = b[i];
    sort(ax + 1, ax + n + 1);
    sort(bx + 1, bx + n);
    for (int i = 1; i < n; i++) {
        if (ax[i] > bx[i]) {
            cout << -1 << endl;
            return 0;
        }
    }
    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    cout << r + 1;
    return 0;
}
```
#### AC记录
<https://atcoder.jp/contests/abc376/submissions/58960194>
#### 最后叭叭两句

本人是个大蒟蒻，如果有 dalao 能够 hack 掉我的代码并 @ 我，感激不尽。

---

## 作者：CuteForces (赞：0)

## 思路：
考虑贪心。

首先，先将 $A,B$ 从小到大排序。然后从**前往后**对比，当 $A_i>B_i$ 时，说明装不下，直接判无解。

接着，我们从**后往前**，让 $B_i$ 去装 $A_{i+1}$，如果装得下，显然是更优的。当发现 $B_i$ 装不下 $A_{i+1}$，而又知道 $A_i\le B_i$，那么就去让 $B_i$ 装 $A_i$，而 $A_{i+1}$ 就是答案。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=500010;
int n,a[N],b[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n);
	for(int i=1;i<n;i++){
		if(a[i]>b[i]){
            cout<<-1;
            return 0;
        }
	}
	for(int i=n-1;i;i--){
		if(b[i]<a[i+1]){
			cout<<a[i+1];
			return 0;
		}
	}
	cout<<a[1];
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

想要满足再买一个盒子就能装下所有礼物，肯定需要满足在买第 $n$ 个盒子之前，只有一个礼物无法被装进盒子里。

进而，想要买盒子的钱最少，就需要让多出来的这个礼物的尺寸尽可能的小。所以将礼物尺寸和盒子尺寸都按照从大到小排序，在每个盒子里装下能装的最大的礼物。最后遍历一遍所有礼物，找到唯一没装下的礼物，输出它的大小即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],b[1000005],flag[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+(n-1));
	int k=n;
	for(int i=n-1;i>=1;i--){
		while(a[k]>b[i]&&k>0) k--;
		if(k==0) break;
		flag[k]=1,k--;//能装下的最大的礼物
	}
	int maxn=0,sum=0;
	for(int i=1;i<=n;i++) if(!flag[i]) sum++,maxn=a[i];
	if(sum>1) cout<<-1;
	else cout<<maxn;//只有一个礼物未装下的时候输出其尺寸
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

首先猜测需要将 $a$ 和 $b$ 排序。

假设 $a_i$ 放进了新买的袋子中。

对于任意的 $j<i$，贪心得 $a_j$ 对应 $b_j$ 是最合适的。

对于任意的 $j>i$，贪心得 $a_j$ 对应 $b_{j-1}$ 是最合适的。

对于 $i$，需要再买一个大小为 $a_i$ 的袋子。

得到无解的条件：假设存在 $1\leq i\leq n-1$，有 $a_i>b_i$，那么无解。

理由：这种判断对应着买一个大小为 $a_n$ 的袋子。买一个大小大于 $a_n$ 的袋子，最多也只能装 $a_n$。由于大小为 $a_n$ 的袋子不满足条件，买一个价值小于 $a_n$ 的袋子同样无解。

接下来从大到小枚举每一个 $i$，如果发现 $a_i>b_{i-1}$，说明 $a_i$ 不能对应 $b_{j-1}$，买一个大小为 $a_i$ 的袋子，跳出循环即可。如果任意一个 $i$ 都满足 $a_i>b_{i-1}$，需要买一个大小为 $a_1$ 的袋子。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int a[200005];
int b[200005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n);
	for(int i=1;i<n;i++){
		if(a[i]>b[i]){
			cout<<-1<<endl;
			return 0;
		}
	}
	for(int i=n;i>=2;i--){
		if(a[i]>b[i-1]){
			cout<<a[i]<<endl;
			return 0;
		}
	}
	cout<<a[1]<<endl;
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长度为 $N$ 的序列 $A$ 和长度为 $N-1$ 的序列 $B$，需要给 $B$ 添加一个数 $x$，使得对于每个 $A_i$ 都有一个 $B_j$ 与之对应（条件为 $A_i\le B_j$），且 $j$ 不重复，需求出 $x_{\min}$，若不存在则输出 $-1$。

## 解题思路

首先我们可以考虑不加 $x$ 的情况，可以对 $A,B$ 分别从小到大排序，这样对于每个 $1\le i<N$ 都有 $A_i\le B_i$（如果有一个不满足则说明不加 $x$ 都无法满足条件，因为 $A$ 是非严格单调递增的，输出 $-1$ 即可）。然后如果在 $B_i$ 和 $B_{i+1}$ 中间插入一个 $x$，则对于每个 $i<j\le N$ 都需要满足 $A_j\le B_{j-1}$，从后往前枚举即可，时间复杂度 $O(N)$。

注意：如果 TLE 一个点，把快排改成 `sort` 即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,a[200001],b[200001];

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i) a[i]=read();
    for(R int i=1; i<n; ++i) b[i]=read();
    sort(a+1,a+n+1); sort(b+1,b+n);

    for(R int i=1; i<n; ++i)
    {
        if(a[i]>b[i])
        write(-1), exit(0);
    }

    for(R int i=n; i; --i)
    {
        if(a[i]>b[i-1])
        write(a[i]), exit(0);
    }

    return 0;
}
```

---

## 作者：yegengghost (赞：0)

考录到最大值最小，直接用二分。

我们对于此题的最优策略就是排序，然后使得每一个物品都正好能够放进箱子里。这样就可以使尽可能多的箱子被利用。对于每次二分，所要的 ```mid``` 就是答案。将它放入第二个数组中排好序，查找是否有玩具的大小比所对应箱子大即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
const int mod=1;
int n;
int a[N],b[N],temp[N];
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
bool check(int x)
{
	temp[n]=x;
	memcpy(b,temp,sizeof(b));
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	//通过排序检查当前是否有某些物品的大小大于当前对应的箱子大小。
	//因为为了满足题意，我们需要让尽可能多的物品及箱子配对，则剩下不能成功配对的就是我们所需的答案。
	for(int i=1;i<=n;i++)
		if(a[i]>b[i])
			return 0;
	return 1;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++)
		temp[i]=read();
	//根据题意，发现求最大值的最小值，故用二分
	int l=1,r=1e9+5;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))//小核心
			r=mid;
		else
			l=mid+1;
	}
	if(l==1e9+5)
		puts("-1");
	else
		cout<<l<<'\n';
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[C - Prepare Another Box](https://atcoder.jp/contests/abc376/tasks/abc376_c)

考虑二分答案，将二分出的值加进 $b$ 序列，这样 $a$ 序列和 $b$ 序列的长度都为 $n$。

将 $a$ 序列和 $b$ 序列都从小到大排序，可以证明将物品 $a_i$ 放进盒子 $b_i$ 一定不劣，判断是否可行即可。

最后再 check 一下二分出的值，如果不可行，输出 `-1`。

时间复杂度 $\mathcal O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, a[N], b[N], tmp[N];
bool check (int x) {
    for (int i = 1; i < n; i++)
        tmp[i] = b[i];
    tmp[n] = x;
    sort (tmp + 1, tmp + n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] > tmp[i])
            return 0;
    }
    return 1;
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) cin >> b[i];
    sort (a + 1, a + n + 1);
    
    int l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check (mid)) r = mid;
        else l = mid + 1;
    }
    if (check (l)) cout << l;
    else cout << -1;
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

这道题要求把 $a$ 数组和 $b$ 数组一一匹配，且要求无法匹配的数量最多为一，并且这个无法匹配的元素最小。

可以注意到我们把两个数组排序以后一一对应以后如果出现一个无法匹配的元素，那么这一定就是答案。

但是如果我们从小到大枚举，会发现最后剩下的元素不一定最小，所以我们选择从大到小遍历。

具体的，如果我们遇到一个不能满足的元素，那么我们就让 $a$ 数组的匹配位置前移继续匹配，并标记此元素为答案。如果后面再遇到一个无法匹配的元素，那么一定无解。

[提交记录](https://atcoder.jp/contests/abc376/submissions/58944809)

---

## 作者：wangif424 (赞：0)

假如我们已经选好了合适的盒子，那么把盒子和物品分别从小到大排序，如果 $\exist i,a_i>b_i$ 那么不难证明这种情况不合法。

我们可以较快的判断一个答案是否合法，同时答案具有单调性，于是考虑二分答案，每次二分放的盒子的大小，并如上判断即可，时间复杂度 $O(n\log n\log V)$。

考虑到加入的盒子大小一定是其中一个 $a_i$，那么我们可以二分一个下标将其对应的 $a$ 作为盒子大小，时间复杂度 $O(n \log ^2 n)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define R(x) x = read()
#define int long long
#define double long double
#define pii pair<int,int>
#define iax INT_MAX
#define iin INT_MIN
#define lax LLONG_MAX
#define lin LLONG_MIN
#define sqrt sqrtl
bool Mbe;
using namespace std;
char pbuf[1<<20], *pp=pbuf;
inline void push(const char &c){(pp-pbuf==1<<20)?fwrite(pbuf,1,1<<20,stdout),pp=pbuf,*pp++=c:*pp++=c;}
class io {public:~io() {fwrite(pbuf, 1, pp - pbuf, stdout);}} _;
inline void write(int x) {
	x<0&&(push('-'),x=-x);
	static int sta[60]={},top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)push(sta[--top]^'0');
}
#ifndef LOCAL
	char buf[1<<23],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){ch=='-'&&(f=-1);ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
constexpr int N=2e5+100;
int n;
int a[N],b[N],c[N],ck,ans;
bool Med;
signed main(){
#ifndef LOCAL
#else
	cerr << (&Med-&Mbe)/1024.0/1024 << "MB\n";
#endif
	R(n);
	for(int i=1;i<=n;i++)R(a[i]);
	for(int i=1;i^n;i++)R(b[i]);
	sort(a+1,a+1+n);
	ans=-1;
	int l=a[1],r=a[n];
	while(l<=r){
		int mid=(l+r)>>1;
		for(int i=1;i^n;i++)c[i]=b[i];
		c[n]=mid;
		sort(c+1,c+1+n);
		ck=1;
		for(int i=1;i<=n;i++){
			if(a[i]>c[i])ck=0;
		}
		if(ck)r=mid-1,ans=mid;
		else l=mid+1;
	}
	write(ans);
    return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc376_c)
## 思路
一眼二分。首先我们会发现对于那剩下的一个物体，若要最小化价钱，则买盒子的时候应该刚好买这一个物体的重量所需的容量。

将 $a$ 有序化，如果买容量为 $a_x$ 的盒子可以满足题意，则买容量 $>a_x$ 的盒子也一定满足题意。这样满足了二分的单调性，就可以二分了。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int a[N], b[N];
bool vis[N];

bool check(int x)
{
	for (int i = 1, j = 1; j <= n; i++)
	{
		if (i == x) continue;
		if (a[i] > b[j]) return 0; // 剩下的 n - 1 个物体和盒子，应该都可以装下
		j++;
	}
	return 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; i++)
		scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n);
	int l = 0, r = n;
	while (l + 1 < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid; // 能不能买容量为 a[mid] 的盒子
		else l = mid;
	}
	if (!check(r)) printf("-1\n");
	else printf("%d\n", a[r]);
	return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 题意

有一个长度为 $n$ 的序列 $a$ 和长度为 $n-1$ 的 $b$ 序列，要求找到最小的数 $x$ 使得每一个 $a_i$ 都可以分配到一个大于等于它的 $b_j$，求最小的 $x$。

### 思路

考虑降序排序。

然后，用两个双指针 $i,j$ 来扫一遍序列，如果 $a_i\le b_j$ 则 $j$ 继续往后走，否则就说明这个点不可以，然后就会记录一下这个点，如果这样的点有两个及以上，输出 ```-1```，否则输出记录的值。

时间复杂度：$\Theta(n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int a[N],b[N];
int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	for (int i = 1; i < n; i ++ ){
		cin >> b[i];
	}
	sort(a + 1,a + 1 + n);
	reverse(a + 1,a + 1 + n);
	sort(b + 1,b + n);
	reverse(b + 1,b + n);
	int i = 1,j = 1;
	int mx = 0;
	int cnt = 0;
	while (i <= n && j < n){
		if (a[i] <= b[j]){
			 ++ j;
		}
		else{
			cnt ++ ;
			mx = max(mx,a[i]);
		}
		i ++ ;
	}
	while (i <= n){
		cnt ++ ;
		mx = max(mx,a[i]);
		i ++ ;
	}
	if (cnt > 1){
		cout << -1;
		return 0;
	}
	cout << mx;
	return 0;
}
```

---

