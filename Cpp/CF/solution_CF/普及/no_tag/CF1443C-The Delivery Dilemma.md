# The Delivery Dilemma

## 题目描述

Petya is preparing for his birthday. He decided that there would be $ n $ different dishes on the dinner table, numbered from $ 1 $ to $ n $ . Since Petya doesn't like to cook, he wants to order these dishes in restaurants.

Unfortunately, all dishes are prepared in different restaurants and therefore Petya needs to pick up his orders from $ n $ different places. To speed up this process, he wants to order courier delivery at some restaurants. Thus, for each dish, there are two options for Petya how he can get it:

- the dish will be delivered by a courier from the restaurant $ i $ , in this case the courier will arrive in $ a_i $ minutes,
- Petya goes to the restaurant $ i $ on his own and picks up the dish, he will spend $ b_i $ minutes on this.

Each restaurant has its own couriers and they start delivering the order at the moment Petya leaves the house. In other words, all couriers work in parallel. Petya must visit all restaurants in which he has not chosen delivery, he does this consistently.

For example, if Petya wants to order $ n = 4 $ dishes and $ a = [3, 7, 4, 5] $ , and $ b = [2, 1, 2, 4] $ , then he can order delivery from the first and the fourth restaurant, and go to the second and third on your own. Then the courier of the first restaurant will bring the order in $ 3 $ minutes, the courier of the fourth restaurant will bring the order in $ 5 $ minutes, and Petya will pick up the remaining dishes in $ 1 + 2 = 3 $ minutes. Thus, in $ 5 $ minutes all the dishes will be at Petya's house.

Find the minimum time after which all the dishes can be at Petya's home.

## 样例 #1

### 输入

```
4
4
3 7 4 5
2 1 2 4
4
1 2 3 4
3 3 3 3
2
1 2
10 10
2
10 10
1 2```

### 输出

```
5
3
2
3```

# 题解

## 作者：ChrisWangZi (赞：3)

# CF1443C The Delivery Dilemma 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1443C)

## 思路分析

每道菜，可以选择外卖（可同时送多个外卖）和自取（同时只能自取一份）。

所以，外卖的用时为时间的最大值，而自取的用时为时间的和。

答案变量（$ans$）记录**每次外卖与自取时间的最大值（实际时间）的最小值**

（以下均默认每道菜的外卖时间为 $a_i$，自取时间为 $b_i$）

先假设所有菜均由外卖送来，则外卖时间为 $\max{a_i}$，自取时间为 $0$，$ans=\max{a_i}$。

再假设外卖时间最大的菜变为自取，则外卖时间为 $a_i$ 的第二大，自取时间为外卖最大值的自取，$ans$ 为它们的和。

直到所有的菜都自取了一遍。

排序的过程，我使用了[堆(STL优先队列)](https://www.luogu.com.cn/blog/637180/priority-queue)。

代码（具体见注释）：

```cpp
#include<iostream>
#include<queue>
using namespace std;
struct node{
	long long w,j;
	int id;
	friend bool operator <(const node x,const node y){//排序方法
		return x.w<y.w;
	}
}a[200005];
priority_queue<node,vector<node>,less<node>> pq;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		//更加快速的清零
		priority_queue<node,vector<node>,less<node>> sw;
		swap(pq,sw);
      
		long long minn=2e9;
		long long maxn=0;//外卖
		long long sum=0;
		for(int i=1;i<=n;i++){
			cin>>a[i].w;
			a[i].id=i;
			maxn=max(maxn,a[i].w);
			minn=min(minn,a[i].w);
		}
		for(int i=1;i<=n;i++){
			cin>>a[i].j;
			pq.push(a[i]);//入堆
			sum+=a[i].j;
		}
		if(sum<=minn){//特判
			cout<<sum<<'\n';
			continue;
		}
		long long ans=maxn;
		long long ta=pq.top().w,zq=0;
		while(!pq.empty()){
			int c=pq.top().j;
			pq.pop();
			zq+=c;
			ta=pq.top().w;
			ans=min(ans,max(ta,zq));
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：_Pecky_ (赞：3)

# CF1443C の 解题报告

## 一.题目背景
这道题目作为 J Y 中学的复活赛题目， 被 Pecky 在考场上想到了奇怪的性质  ~~一个小优化~~ ， Pecky 进行优化之后由于代码能力不成熟导致 $100$ 变 $30$， 所以顺手来一发这道题的题解。

------------

## 二.题目分析
有 n 道菜， 每道菜有着两个 cost ， 第一个 cost 为送餐时间， 第二个 cost 为自己取餐时间。 观察题目发现， 对 a 进行排序， 则花费的时间 $T\, = $ $max(a[i], sum_b[i + 1])$。 于是我们就想到了对 b 数组求一个后缀和， 对 $a$ 数组进行排序， 然后扫一遍取 max 即可。 复杂度为 $O(n * logn)$。

------------

## 三. Coding Time
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 2 * 1e5 + 10;
struct node{
	ll a;
	ll b;
}l[maxn];
ll sum[maxn];

bool cmp1(node x, node y){
	return x.a < y.a;
}

int main(){
	int t, n;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		sum[n + 1] = 0;//初始化不要用 memset, 会 TLE 
		for(int i = 1;i <= n;i++){
			scanf("%lld", &l[i].a);
		}
		for(int i = 1;i <= n;i++){
			scanf("%lld", &l[i].b);
		}
		sort(l + 1, l + n + 1, cmp1);//对 a 进行排序 
		for(int i = n;i >= 1;i--){
			sum[i] = sum[i + 1] + l[i].b;//求 b 的后缀和 
		}
		ll ans = 1e9 + 10;
		for(int i = 0;i <= n;i++){
			ll maxx = max(l[i].a, sum[i + 1]);//计算答案 
			ans = min(ans, maxx);
		}
		printf("%lld\n", ans);
	}
	return 0;
} 
```

------------

## 四.一个小优化（常数优化）

对于 a 数组以及 sum_b 数组， 我们排序后发现 a 数组是不严格单调递增的， 而 sum_b 数组为不严格单调递减的， 则两者取 max 会令最后的 ans 为单谷的， 所以我们可以考虑进行三分， 或者取个 mid， 分别向两边扫， 这样可以对时间复杂度进行一点点小优化。

------------

## $Code$：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 2 * 1e5 + 10;
struct node{
	ll a;
	ll b;
}l[maxn];
ll sum[maxn];

bool cmp1(node x, node y){
	return x.a < y.a;
}

int main(){
	int t, n;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		sum[n + 1] = 0;
		for(int i = 1;i <= n;i++){
			scanf("%lld", &l[i].a);
		}
		for(int i = 1;i <= n;i++){
			scanf("%lld", &l[i].b);
		}
		sort(l + 1, l + n + 1, cmp1);
		for(int i = n;i >= 1;i--){
			sum[i] = sum[i + 1] + l[i].b;
		}
		ll ans = 1e18 + 10;//注意 ans 要初始化大一些, 否则可能进不了下面的循环
		//100 -> 30 の 经验教训 
		int mid = (n + 1) >> 1;
		for(int i = mid;i >= 0;i--){
			ll maxx = max(l[i].a, sum[i + 1]);
			if(maxx > ans){
				break;
			}
			ans = min(ans, maxx);
		}
		for(int i = mid + 1;i <= n;i++){
			ll maxx = max(l[i].a, sum[i + 1]);
			if(maxx > ans){
				break;
			}
			ans = min(ans, maxx);
		}
		//这样最坏情况下也只会扫 n / 2次
		//但是由于 sort 复杂度即为 n * logn
		//所以只会优化一点点(没什么卵用) 
		printf("%lld\n", ans);
	}
	return 0;
} 
``

---

## 作者：LeavingZzz (赞：3)

# $\mathsf{Solution\space To \space CF1443C}$  
## $\mathsf{Description}$  
一个人要点 $n$ 份菜，每一份菜都可以选择用快递送到家或者自己去拿，快递可以同时运送，但是自己去拿的时候只能一份一份拿。  
换句话说，自己拿菜的是串行处理的，快递是并行的。  
求把所有的菜都拿到家里的用时。
## $\mathsf{Analysis}$  
可以发现本题的答案是满足单调性，也就是说，如果在时间 $t$ 能够把所有菜拿到家里，那么大于 $t$ 的时间也都是可行的。  
所以我们可以二分答案，假设当前二分的答案为 $p$，问题转化为判定问题，能否在时间 $p$ 内把所有的菜拿到家里。  
这里就有个贪心的策略，如果一道菜送快递的时间小于等于 $p$ 的话，那么就让这道菜送快递到家，因为快递员是并行的,这样做是尽量减小自己去拿的总耗时，如果自己去拿的话答案一定不会更优。  
接下来只要检查所有送快递时间大于 $p$ 的菜自己去取的话总时间是不是小于等于 $p$ 的就可以判定了。  
多说一句，CF的题目因为比较多的时候是多测，对于 `memset` 的使用应该谨慎，因为 `memset` 的时间复杂度实际上是 $O(\texttt{数组大小})$ 的，在测试数据组数很多的时候会把一个做法卡死。  
## $\mathsf{Code}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
inline int R()
{
    int re;
    char c;
    while(!isdigit(c=getchar()));
    re=c-48;
    while(isdigit(c=getchar()))
    re=re*10+c-48;
    return re;
}
const int maxn=200007;
int T,N;
int a[maxn],b[maxn];
bool book[maxn];
bool check(int p)
{
    for(int i=1;i<=N;i++)
        book[i]=false;
    for(int i=1;i<=N;i++)
    if(b[i]<=p) book[i]=true;
    long long sum=0;
    for(int i=1;i<=N;i++)
    if(!book[i]) sum+=a[i];
    return sum<=p;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    T=R();
    while(T--)
    {
        N=R();
        for(int i=1;i<=N;i++)
            b[i]=R();
        for(int i=1;i<=N;i++)
            a[i]=R();
        int L=1,R=1e9,mid,ans;
        while(L<=R)
        {
            mid=L+R>>1;
            if(check(mid)) ans=mid,R=mid-1;
            else L=mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：PDAST (赞：1)

屑二分一道，不知道为什么能评蓝。
## 题意
有 $N$ 个外卖订单，第 $i$ 个外卖订单让外卖员送需要 $A_{i}$ 分钟，自己去需要 $B_{i}$ 分钟，外卖员可以同时出发，自己只能挨个去取，问最少需要多少分钟能取完所有外卖。
## 思路
一眼二分答案，判断外卖是否可以在这段时间内送达，若不行，则自己去取，记录自己所需要的时间，当判断完所有的单子后与前面二分的规定时间比较，若小于等于该值，则可行，否则不行。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200001],b[200001],n;
bool check(int x){
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]>x)sum+=b[i];
	}
	return sum<=x;
} 
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		int l=0,r=1e16;
		while(l<r){
			int m=(l+r)>>1;
			if(check(m))r=m;
			else l=m+1;
		}	
		cout<<r<<"\n";
	} 
}

~~~

---

## 作者：Fu_Da_Ying (赞：1)

## [原题链接](https://www.luogu.com.cn/problem/CF1443C)
## 题意：
你需要去 $n$ 个餐厅取菜，你可以选择自己去取，也可以选择叫外卖，$a_i$ 表示第 $i$ 家餐厅送到你家所需的时间，$b_i$ 表示自己去第 $i$ 家餐厅取菜所需时间，已知餐厅在你离开家时同时送餐，求取到所有菜的最短时间。
## 思路：
假设我们所有菜都让他们送过来，则 $ans = \max(a_1 \dots a_n)$，不妨开一个 $sum$ 表示当前自己去拿已经花费的时间 ， 由于自己买的时候花费时累加的，我们先将 $a_1 \dots a_n$ 从大到小排序，若有 $a_i > sum + b_i$ 则第 $i$ 个物品可以通过自己买来代替，否则直接输出答案。
## Code:
```cpp
//非洛谷题_CodeForces_CF1443C_The Delivery Dilemma
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(1)
#pragma GCC/*G++*/ optimize(2)
#pragma GCC/*G++*/ optimize(3)
using namespace std;
struct cai{
	long long a,b;
}c[200005];
long long t=0,n=0;
bool cmp(cai x,cai y){//a[i]和b[i]，由a[i]从大到小排序 
	return x.a>y.a;
}
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("CF1443C.in","r",stdin);
    //freopen("CF1443C.out","w",stdout);
    cin>>t;
    while(t--){
    	cin>>n;
    	for(int i=1;i<=n;i++){
    		cin>>c[i].a;
		}
		for(int i=1;i<=n;i++){
    		cin>>c[i].b;
		}
		sort(c+1,c+n+1,cmp);
		bool flag=0;
		long long sum=0;
		for(int i=1;i<=n;i++){
			if(c[i].a>sum+c[i].b){//有a[i]>sum+b[i]
				sum+=c[i].b;//sum加上自己取的时间
			}else{//否则直接输出答案
				cout<<max(c[i].a,sum)<<"\n";
				flag=1;
				break;
			}
		}
		if(!flag){
			cout<<sum<<"\n";
		}
	}
    return 0;
}
```

---

## 作者：Composite_Function (赞：1)

# 思路

## I. 后缀和

很简单也容易想，注意**餐厅送是可以同时进行的**~~（我开始还以为不是这样。。。蒟蒻还是蒟蒻啊）~~。

由于为了时间更少，反正同样的时间也要等，对数对组 $(a, b)$ 以 $a$ 升序排序后的：

$$
\max ^ n _ {i = 1}\left\{a _ i, \sum ^ n _ {j = i + 1} b _ i \right\}
$$

考虑到每次求出原式中的

$$
\sum ^ n _ {j = i + 1} b _ i
$$

效率较慢，时间复杂度为 $O(n)$，算上枚举 $i$ 的时间复杂度为 $O(n ^ 2)$。可以使用前缀和来优化。时间复杂度 $O(n \log n)$。实际上时间瓶颈为 `sort` 排序。

## II. 二分

**广告：不会二分戳这里 [link](https://www.luogu.com.cn/blog/fgxseven/qian-tan-er-fen)**

最近老师再教二分，也往这方面想了想。

看完后，发现这时最经典的二分答案，可行性判断就是遍历数组，贪心取得值，最后看可不可以就行了。注意二分范围是 $\left[1, \max\left\{a\right\}\right]$。

放下关键判断的伪代码：

$$
\begin{aligned}
& def~judge~(x)\\
&~~~~ num = 0\\
&~~~~ for~i~1 \to n~do\\
&~~~~~~~~ if~a _ i > x~then\\
&~~~~~~~~~~~~ num \leftarrow num + b _ i\\
&~~~~ return~num \le x
\end{aligned}
$$

------------

# 代码

由于笔者懒癌发作，就只写了**后缀和**。二分实际上也挺好写的。

```cpp
# include <bits/stdc++.h>
using namespace std;

# define int long long
const int N = 2e5 + 10;

int T, n, sum[N];
struct Node
{
    int a, b;
}val[N];

bool cmp(Node x, Node y)
{
    return x.a < y.a;
}

signed main()
{
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> val[i].a;
        for (int i = 1; i <= n; ++i)
            cin >> val[i].b;
        
        sort(val + 1, val + n + 1, cmp);
        
        sum[n + 1] = 0; \\ 多测不清空，爆零两行泪
        for (int i = n; i >= 1; --i)
            sum[i] = sum[i + 1] + val[i].b; \\ 后缀和
        int ans = 1e18; \\ ans 越大越好
        for (int i = 0; i <= n; ++i) {
            int tmp = max(val[i].a, sum[i + 1]);
            ans = min(ans, tmp);
        }

        cout << ans << endl;
    }
    
    return 0;
}
```


---

## 作者：liuhongyang123 (赞：0)

# 题目大意
给你两个长度为 $n$ 的数组 $a$ 和 $b$。对于每一个 $a_i$，$b_i$，从中选择一个。令所选择的 $a_i$ 中最小的值为 $g$，最后求最小的 $\max(g,\sum b_i)$。
# 解法
贪心。从大到小枚举，看一下是选 $a_i$ 对当前的答案更优，还是选 $b_i$ 对当前的答案更优。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int n,T,maxx,ans;
struct node{
	int a,b;
}g[MAXN];
bool cmp(node x,node y){
	return x.a>y.a;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans=maxx=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&g[i].a);
		for(int i=1;i<=n;i++) scanf("%lld",&g[i].b);
		sort(g+1,g+1+n,cmp);
		for(int i=1;i<=n;i++){
			if(ans+g[i].b<g[i].a) ans+=g[i].b;//计算选b[i]的贡献
			else maxx=g[i].a;//计算选a[i]的贡献
		}
		printf("%lld\n",max(maxx,ans));
	}
	return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意
一个人要点 $n$ 份菜，每一份菜都可以选择用外卖送到家或者自己去拿，外卖可以同时运送，但是自己去拿的时候只能一份一份拿。
# 思路
显然，我们可以贪心，因为我们可以选择 $a_i$ 或者 $b_i$，所以对于任意一个 $a_i>cost$ 的情况，我们都可以选 $b_i$，其中 $cost$ 是之前自己去拿的总时间。详见代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 2 + 7;

#define int long long

int T;

int n;

struct Node {
	int a, b;
} Num[MAXN];

bool cmp(Node A, Node B)
{
	return A.a > B.a;
 } 

signed main()
{
	cin >> T;
	
	while(T--)
	{
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> Num[i].a;
		for(int i = 1; i <= n; i++)
			cin >> Num[i].b;
		sort(Num + 1, Num + n + 1, cmp);
		int cost = 0;
		int ans = 0;
		for(int i = 1; i <= n; i++)
		{
			if(cost + Num[i].b <= Num[i].a)	
				cost += Num[i].b;
			else
				ans = max(ans, Num[i].a);
		}
		cout << max(ans, cost) << "\n";
	}
	
	return 0;
}
```

---

## 作者：czh___ (赞：0)

贪心，思维题点外卖花费的时间是时间最长的外卖时间，自取花费的时间是所有自取菜品的时间和。总时间为两者的较大值。解题关键：最大外卖花费为 $a$ 时，外卖时间小于等于 $a$ 的外卖都不需要自取。所以我们只需要对 $a_i$ 升序排序，用前缀和求外卖时间大于 $a$ 的总自取时间。得到公式：$ans=\min(ans,\max(c_{i}.a,sum_{n}-sum_{i}))$。

注意：此题由 $b_i$ 求和最大 $10^{14}$ 要开 long      long 才能过。
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=2e5+1;
using namespace std;
struct aaa{
	int a=0,b=0;
}c[N];
bool cmp(aaa x,aaa y){
	return x.a<y.a; 
}
int sum[N];
signed main() {
	int t;
	cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++)
			cin>>c[i].a;
		for(int i=1;i<=n;i++)
			cin>>c[i].b;
		stable_sort(c+1,c+1+n,cmp);	
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+c[i].b;
		int ans=sum[n];
		for(int i=1;i<=n;i++)
			ans=min(ans,max(c[i].a,sum[n]-sum[i]));
		cout<<ans<<endl;
	}
	return 0;
}
```

[出自](https://blog.csdn.net/weixin_45756956/article/details/109498101?ops_request_misc=&request_id=&biz_id=102&utm_term=The%20Delivery%20Dilemma&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-6-109498101.nonecase&spm=1018.2226.3001.4187)

---

## 作者：int_stl (赞：0)

一道二分好题，内训后来水一篇题解。

考虑使用函数 $f(x)$ 来表示所用的时间是否不大于 $x$，在二分的过程中，如果 $f(mid)$ 为 $1$，那么令 $r \gets mid-1$，否则令 $l \gets mid+1$。

同时我讲一下 $f(x)$ 如何实现：
- 准备 $m$ 和 $t$ 两个变量，分别为外卖所需时间的最大值和自取的总用时。
- 对于每个 $i$，如果 $a_i \le x$，那么我们考虑令 $m \gets \max(m,a_i)$。
- 否则，我们考虑自己去餐馆取餐，将时间 $t$ 加上 $b_i$。

最后，总用时便为 $\max(m,t)$，再判断一下总用时是否小于 $x$（即 $\max(m,t) \le x$）即可，时间复杂度 $O(n\log n)$。

代码如下：
```cpp
#include <iostream>
#define int long long
using namespace std;
int t;
int n, a[200005], b[200005];
bool f(int ti) {
	int mx = -1, mx1 = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] <= ti) {
			mx = max(mx, a[i]);
		}
		else {
			mx1 += b[i];
		}
	}
	return max(mx, mx1) <= ti;
}
signed main() {
	cin >> t;
	while (t--) {
		cin >> n;
		int r1 = 0, r2 = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			r1 += a[i];
		}
		for (int i = 1; i <= n; i++) {
			cin >> b[i];
			r2 += a[i];
		}
		int l = 1, r = r1 + r2;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (f(mid)) r = mid - 1;
			else l = mid + 1;
		}
		cout << l << '\n';
	}
}
```

---

## 作者：鹤箩芠 (赞：0)

怎么都用二分写啊 ， 雾。

放一个贪心的题解吧qwq ， 假设我们所有菜都让他们送过来 ， 则$ans = max (a_i)$ , 不妨开一个$sum$表示当前自己去拿已经花费的时间 ， 由于自己买的时候花费时累加的 ， 我们先将$a_i$从大到小排序 ， 若$a_i > sum + b_i$ 则第i个物品可以通过自己买来代替 ， 反之直接输出答案。


```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 2e5 + 3 ; 
struct K {
	long long A , B ;
}t[N] ; 

bool cmp1 (K a , K b) {
	return a.A > b.A ;
}
int main () {
	
	int ti ;
	cin >> ti ;
	
	while (ti --) {
		int n ;
		cin >> n ;
		bool have = 0 ;
		for (int i = 1 ; i <= n ; i ++) cin >> t[i].A ;
		for (int i = 1 ; i <= n ; i ++) cin >> t[i].B ;
		sort (t + 1 , t + n + 1 , cmp1) ;
		long long mius = 0 , ans = 1 ;
		for (int i = 1 ; i <= n ; i ++) {
			if (mius + t[i].B < t[i].A) mius += t[i].B ;
			else {
				cout << max (t[i].A , mius) << endl ;
				have = 1 ;
				break ;
			}
		}
		if (!have) cout << mius << endl ;
	}
	return 0 ;
}
```


---

## 作者：keep_ (赞：0)

# 题目大意

你需要去n个餐厅取菜，你可以选择自己去取，也可以选择叫外卖，ai表示第i家餐厅

送到你家所需的实际，bi表示自己去第i家餐厅取菜所需时间，已知餐厅在你离开家

时同时送餐，求取到所有菜的最短时间

# 思路分析
我们先假设所有菜都送外卖过来，按ai大小对送到的时间由大到小排序，针对当前送

到家的最大时间，如果去餐厅取比送外卖时间短，那么显然自己去取更优秀，从大到

小枚举即可，如果在某一道菜时，自己去取的总时间大于送外卖的最大时间，直接输

出即可

# 代码

```c++
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=2e5+10;
inline int read(){
	int ret=0;
	int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-f;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		ret=ret*10+(ch^'0');
		ch=getchar();
	}
	return ret*f;
}
int t;
int n;
int b[maxn];
struct node{
	int id;
	int v;
}a[maxn];
bool operator < (const node &x,const node & y){
	return x.v>y.v;
}
signed main(){
//	freopen("a.txt","r",stdin);
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i].v=read();
			a[i].id=i;	
		}
		for(int i=1;i<=n;i++){
			b[i]=read();
		}
		sort(a+1,a+1+n);
		int add=0;
		int fla=0;
		for(int i=1;i<=n;i++){
			if(add>=a[i].v){
				cout<<add<<endl;//add比上一道菜小，比当前大，最大值为add，直接输出 
				fla=1;
				break;
			}
			if(a[i].v>=b[a[i].id])
				add+=b[a[i].id];
			else{
				cout<<a[i].v<<endl;
				fla=1;
				break;
			}
			if(add>=a[i].v){
				cout<<a[i].v<<endl;
				fla=1;
				break;
			}
		}
		if(!fla){
			cout<<add<<endl;//优化失败，输出 
		}
	//	memset(b,0,sizeof(b));
	//	memset(a,0,sizeof(a));
	}
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：0)

题意有，我就不多赘述了（~~实际上是我不知道咋翻~~）

----
二分题。

首先因为 $maxa$ 必定可以满足全部拿到（因为可以每一个都是快递员送过来）。

然后因为当一个时间满足了，比它更长的时间肯定满足，所以答案就是满足与不满足的临界点（即该数前面为不满足，后面为满足）。

然后上界为`maxa`，下界为1，二分即可。

（~~打CF的时候差点二分没调过来~~）

check函数就是枚举每一个i,若 $a_i$ 大于给定的数，则取 $b_i$。

若取的 $b_i$ 之和大于给定的数则不能满足全部拿到。

Code:
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int t,n,maxb,ans;
int a[200001],b[200001];
bool check(int d){
	bool flag=true;
	int k=0;
	for(int i=1;i<=n&&flag;i++){
		if(a[i]>d) k+=b[i];
		if(k>d) flag=false;
	}
	return flag;
}
void BinarySearch(int l,int r){
	if(l>=r) {
		ans=l;return;
	}
	int m=(l+r)>>1;
	if(check(m)) BinarySearch(l,m);
	else BinarySearch(m+1,r);
	return;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		maxb=ans=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),maxb=max(maxb,a[i]);
        //别问为什么是maxb，问就是我写反了
		for(int j=1;j<=n;j++) scanf("%d",&b[j]);
		BinarySearch(1,maxb);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

