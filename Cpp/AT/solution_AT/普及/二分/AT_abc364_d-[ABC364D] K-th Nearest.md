# [ABC364D] K-th Nearest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc364/tasks/abc364_d

数直線上に $ N+Q $ 個の点 $ A_1,\dots,A_N,B_1,\dots,B_Q $ があり、点 $ A_i $ の座標は $ a_i $、点 $ B_j $ の座標は $ b_j $ です。

$ j=1,2,\dots,Q $ それぞれについて、以下の問題に答えてください。

- 点 $ A_1,A_2,\dots,A_N $ のうち点 $ B_j $ との距離が $ k_j $ 番目に近い点を $ X $ としたとき、点 $ X $ と点 $ B_j $ との距離を求めよ。 より厳密には、点 $ A_i $ と点 $ B_j $ との距離を $ d_i $ として、$ (d_1,d_2,\dots,d_N) $ を昇順に並び替えてできる列を $ (d_1',d_2',\dots,d_N') $ としたとき、$ d_{k_j}' $ を求めよ。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\ \leq\ 10^5 $
- $ -10^8\leq\ a_i,b_j\ \leq\ 10^8 $
- $ 1\leq\ k_j\leq\ N $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のクエリについて説明します。 点 $ A_1,A_2,A_3,A_4 $ と点 $ B_1 $ との距離は順に $ 1,1,7,8 $ なので、点 $ B_1 $ との距離が $ 3 $ 番目に近いのは点 $ A_3 $ です。 よって、点 $ A_3 $ と点 $ B_1 $ との距離である $ 7 $ を出力します。

### Sample Explanation 2

同じ座標に複数の点がある可能性もあります。

## 样例 #1

### 输入

```
4 3
-3 -1 5 6
-2 3
2 1
10 4```

### 输出

```
7
3
13```

## 样例 #2

### 输入

```
2 2
0 0
0 1
0 2```

### 输出

```
0
0```

## 样例 #3

### 输入

```
10 5
-84 -60 -41 -100 8 -8 -52 -62 -61 -76
-52 5
14 4
-2 6
46 2
26 7```

### 输出

```
11
66
59
54
88```

# 题解

## 作者：ikunTLE (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_d)

### 思路

这道题用**二分答案**。题目中的 $A_i$ 表示的是数轴上的第 $i$ 个点，不保证其升序，所以要先将数组 $A$ 排序。

设每一次二分的点为 $mid$，分别求出与 $b-mid$ 和 $b+mid$ 距离最近的点，并判断其差是否 $\ge k$。

**注意事项**

- 二分的右边界要开大，建议 $2\times10^8$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10,R=2e8;
int n,q,a[N];
int check(int x,int b,int k){
	int l=lower_bound(a+1,a+n+1,b-x)-a;
	int r=upper_bound(a+1,a+n+1,b+x)-a;
	return r-l>=k;
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	while(q--){
		int b=read(),k=read(),l=0,r=R;
		while(l<=r){
			int mid=(l+r)>>1;
			if(!check(mid,b,k))
				l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
```

---

## 作者：Guoguo2013 (赞：5)

这题还算正常，没有关于吃的内容。

### 题意简介：
看着题挺复杂的，但简单来说题目就几句话。

在一条数轴上，给你 $N$ 个数，第 $i(1 \leq i \leq N)$ 个数是 $a_i$，然后给出 $Q$ 次询问。
- 每次询问给出两个数 $b$ 和 $k$，让我们求出在 $a$ 数组中离 $b$ 第 $k$ 近的数和 $b$ 的距离是多少。形式化的说，创建一个 $c$ 数组，令 $c_i \gets |a_i - b|$，把 $c_i$ 排序之后输出第 $k$ 个。

### 思路：
实际上，每一次询问都用一次二分就可以了，那么有人就要问了，这怎么二分？事实上，二分里面还要再套二分。

二分直接二分答案，假如 $mid$ 表示当前 $a$ 数组不知道第多少项和 $b$ 的距离。  
$check$ 函数就是 $[b - mid, b + mid]$ 中有多少个 $a$ 数组中的数，如果大于等于 $k$，就说明距离太长了，让 $r\gets mid$，否则就是 $l \gets mid - 1$。

这个数量的求法也很简单，两个二分，一个 `lower_bound` 求第一个大于等于 $b - mid$ 的是 $a$ 数组中的第几个，一个 `upper_bound` 求第一个大于 $b + mid$ 的是 $a$ 数组的第几个，后面减前面，不就是数量了吗？

所以这道题写两重二分就行了。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair< int, int >
#define MII map< int, int >
#define MIB map< int, bool >

using namespace std;

const int N = 1e5 + 5, mod = 998244353;
int n, q, a[N];

template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
int ksm(int a, int b, int p){
    int ans = 1;
    while(b){
        if(b & 1)ans =(ans*a)%p;
        b >>= 1;
        a = (a*a) % p;
    }
    return ans;
}
signed main(){
//	freopen("a.in", "r", stdin);
//	freopen("a.out","w",stdout);
	scanf("%lld %lld", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	while (q--){
		int b, k;
		scanf("%lld %lld", &b, &k);
		int l = 0, r = 1e18;
		while (l < r){
			int mid = l + r >> 1;
			auto r1 = upper_bound(a + 1, a + n + 1, b + mid), l1 = lower_bound(a + 1, a + n + 1, b - mid); // 本来我是极其不喜欢用 STL 的（仅限二分），但手写又太麻烦，只能这样了（短短几十个字符能让我调一个小时！！！）。
			if (r1 - l1 >= k) r = mid;
			else l = mid + 1;
		}
		printf("%lld\n", l);
	}
	return 0;
}

```

---

## 作者：saixingzhe (赞：2)

# 分析
求离某个点第 $k$ 远的点的距离，很容易想到对距离的长度进行二分，我们将点按位置排序，再次使用二分查找在此点的范围内是否存在超过 $k$ 个点即可，共使用两次二分。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[100005],b,k;
bool check(int l,int r){
	int le=lower_bound(a+1,a+n+1,l)-a,ri=upper_bound(a+1,a+n+1,r)-a-1;
	if(ri-le+1>=k)	return 1;
	else	return 0;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&b,&k);
		int l=0,r=200000000,ans=-1;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(b-mid,b+mid))	r=mid-1,ans=mid;
			else	l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

由于数据范围很大，可以考虑二分。

使用二分答案，得出距离。

每次判断一个距离是否可行，使用二分，得到往左距离不超过这个距离的最远点，再用二分得到往右距离不超过这个距离的最远点，计算中间点的数量。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N],n;
bool ok(int u,int c,int x,int k)//计算是否可行
{
	int l=1,r=u,mid,sum=0;
	while(l<r)//用两遍二分得到左右边界
	{
		mid=(l+r)>>1;
		if(c-a[mid]>x)l=mid+1;
		else r=mid;
	}
	sum=u-l;
	l=u-1;
	r=n;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(a[mid]-c>x)r=mid-1;
		else l=mid;
	}
	sum+=l-u+1;
	return sum>=k;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,x,k;
	cin>>n>>T;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	while(T--)
	{
		cin>>x>>k;
		int l=1,r=n,mid;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(a[mid]<=x)l=mid+1;
			else r=mid;
		}
		int u=l;//得到近似位置，也可以不用
		l=0;
		r=2e8;//二分距离
		while(l<r)
		{
			mid=(l+r)>>1;
			if(ok(u,x,mid,k))r=mid;
			else l=mid+1;
		}
		cout<<l<<'\n';
	}
	return 0;
}
```

---

## 作者：SkyLines (赞：2)

## Solution

求一维数轴上第 $k$ 小距离。

将 $a$ 数组排序后进行二分，设二分到 $m$，则当前点数为大于 $b+m$ 的第一个下标减去大于等于 $b-m$ 的第一个下标，与 $k$ 判断即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int N = 1e5 + 5;
int n, q, a[N], b, k, l, r, mid;
int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= q; i++){
		scanf("%d %d", &b, &k);
		l = 0;
		r = 2e8;
		while(l <= r){
			mid = (l + r) >> 1;
			if(upper_bound(a + 1, a + n + 1, b + mid) - lower_bound(a + 1, a + n + 1, b - mid) < k){
				l = mid + 1;
			}else{
				r = mid - 1;
			}
		}
		printf("%d\n", l);
	}
	return 0;
}
```

---

## 作者：HeiCat0725 (赞：1)

# [ABC364D] K-th Nearest

## 题意简述

给定数轴上 $N$ 个点的坐标和 $Q$ 个查询，查找距离点 $B_i$ 第 $K$近的点离 $B_i$ 的距离。

## 题目分析

由于数据范围是 $1 \leq N, Q \leq 10^5$ ，出于时间复杂度和题目查询要求，考虑二分。再看题目要求：求**距离**而非下标，可以想到二分答案求到 $B_i$ 的距离小于等于 $mid$ 的点的个数。如果这个个数大于 $K$ 个，则说明当前距离下点排在第 $K$ 近的点之后，缩小右边界。反之缩小左边界。

求个数仍然可以使用二分，这里使用库函数 `lower_bound` 与 `upper_bound` 较为简易。

上代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1e5+5;
int n,q;
int arr[N];
int b,k;
bool check(int d){
	int la=lower_bound(arr+1,arr+n+1,b-d)-arr;
	int ra=upper_bound(arr+1,arr+n+1,b+d)-arr-1;
	int res=ra-la+1;
	if(res>=k) return 1;//若个数大于等于k，说明当前数位置大于kth
	else return 0;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
	sort(arr+1,arr+n+1);
	
	for(int i=1;i<=q;i++){
		scanf("%d%d",&b,&k);
		int l=0,r=2e8+1,ans;//右边界为题目给出的可能最大距离
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				r=mid-1;
				ans=mid;
			}
			else{
				l=mid+1;
			}
		}
		//求得kth的距离x
		printf("%d\n",ans);
	}
	return 0;
}
/*

*/
```

---

## 作者：JOKER_chu (赞：1)

## 题意

给出一个数组 $a_1 \dots a_n$，再给出 $q$ 组询问，对于每组询问，输出距离 $B_i$ 第 $q_i$ 近的 $a_i$ 的位置。

## 解法

二分距离这个点第 $k$ 大的**位置**在 $[B_j - x, B_j + x]$ 这个区间里，并判断区间内数的数量是否 $\leq k_j$，是的话答案 $\leq x$，否则答案 $> x$。有单调性，二分里面套一个 `lower_bound` 寻找 $B_j - x$ 也就是向右偏移在 $a$ 的哪个地方。再套一个 `upper_bound` 寻找 $B_j + x$ 也就是向左偏移在 $a$ 的哪个地方，相减就是包含在这个区间内的数的数量。

## 代码

```cpp
#include <iostream>

#include <algorithm>

#include <climits>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;

int n, q, ll, p, a[N];

bool function1(int y, int x){
  int u = lower_bound(a + 1, a + n + 1, y - x) - a, v = upper_bound(a + 1, a + n + 1, y + x) - a;
  return v - u >= p;
}

int main(){
  cin >> n >> q;
  for(int i = 1; i <= n; cin >> a[i++]);
  sort(a + 1, a + n + 1);
  while(q--){
    cin >> ll >> p;
    int l = 0, r = INT_MAX >> 1;
    while(l < r){
      int mid = (l + r) >> 1;
      if(function1(ll, mid) == 1){
        r = mid;
      }else{
        l = mid + 1;
      }
    }
    cout << l << endl;
  }
  return 0;
}

```

---

## 作者：Heldivis (赞：1)

## [ABC364D] K-th Nearest

提供一个时间复杂度 $O(q\log n)$ 的做法。

每次询问，二分一个左端点，判断最终区间是否包含这个左端点。得到左端点后，计算右端点，输出距离较大的那一个即可。

细节看代码：

```cpp
bool Ck(int l) {
  int r = l + k - 1;
  if (a[r + 1] - x < x - a[l]) return true;
// 这里的意思是如果当前右端点比左端点更优，一定不选当前左端点
  return false;
}
// 以下在主函数
n = read(), q = read();
for (int i = 1; i <= n; i++) a[i] = read();
sort(a + 1, a + 1 + n);
a[0] = -Inf, a[n + 1] = Inf;
while (q--) {
  x = read(), k = read();
  int l = 1, r = n - k + 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (Ck(mid))
      l = mid + 1;
    else
      r = mid;
  }
  printf("%lld\n", max(x - a[l], a[l + k - 1] - x));
}

````

---

## 作者：Redamancy_Lydic (赞：1)

## 分析

首先想到答案一定有单调性，结合每次询问需要在低于 $O(n)$ 的时间内求出答案，不难想到二分。

容易想到，我们可以二分从起点 $x$ 开始的范围 $d$，即需要统计 $[x-d,x+d]$ 区间中有多少个点。

那么这个就好维护了，什么数据结构都行，但是这个用内置的两个二分函数就可以了。

具体的，如果我们要判断数列 $a$ 在区间 $[x-d,x+d]$ 中的元素个数是否不少于 $k$，可以用以下代码实现：

```cpp
bool ch(int d,int x,int k)
{
	int r=upper_bound(a+1,a+n+1,x+d)-a-1;
	int l=lower_bound(a+1,a+n+1,x-d)-a;
	return r-l+1>=k;
}
```

然后就做完了。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
using namespace std;
using namespace  __gnu_pbds;
//gp_hash_table<string,int>mp2;
//__gnu_pbds::priority_queue<int,less<int>,pairing_heap_tag> q;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n,Q;
int a[maxn];
int mi=1e17,ma=-1e17;
bool ch(int x,int b,int k)
{
	int r=upper_bound(a+1,a+n+1,b+x)-a-1;
	int l=lower_bound(a+1,a+n+1,b-x)-a;
	return r-l+1>=k;
}
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)a[i]=read(),mi=min(mi,a[i]),ma=max(ma,a[i]);
	sort(a+1,a+n+1);a[0]=-1e9-7;a[n+1]=1e9+7;
	while(Q--)
	{
		int b=read(),k=read();
		int l=0,r=3e8;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(ch(mid,b,k))r=mid;
			else l=mid+1;
		}
		printf("%lld\n",r);
	}
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：1)

题目的描述方法疑似有点别扭了，把 $B$ 序列看成 $m$ 次询问即可。

题目只让我们输出 $A$ 中距离给定点第 $k$ 远的点的距离，那么我们就枚举距离，找到刚好满足 $A$ 中给定点左右两侧恰好共有 $k$ 个点的位置即可。直接枚举肯定会超时的，所以我们采用二分。

接下来要解决的问题是计算到给定点在给定距离内的点的个数。我们也可以二分。首先找到给定点在序列内的位置。接下来先找到给定点以左在距离内的第一个点，再找到给定点以右在距离内的最后一个点，计算这俩之间的距离即可得到距离范围内点的总个数。

注意二分的细节即可。枚举距离的初始区间要够大。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],b,x;
int f1(int x){
	int l=1,r=n,mid,k=1;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid]<=b) l=mid+1,k=mid;
		else r=mid-1;
	}
	return k;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++){
		cin>>b>>x;
		if(b<=a[1]) cout<<a[x]-b<<"\n";
		else if(b>=a[n]) cout<<b-a[n-x+1]<<"\n";//在序列两端外的直接特判掉
		else{
			int f=f1(b);//找到位置
			int l=0,r=3e8,mid,k=0;
			while(l<=r){
				mid=(l+r)>>1;//二分距离
				int fl=1,fr=n,midd,ll=1;
				while(fl<=fr){
					midd=(fl+fr)>>1;
					if(a[midd]>=b-mid) fr=midd-1,ll=midd;
					else fl=midd+1;
				}//向左查找
				int rr=n;
				fl=1,fr=n;
				while(fl<=fr){
					midd=(fl+fr)>>1;
					if(a[midd]<=b+mid) fl=midd+1,rr=midd;
					else fr=midd-1;
				}//向右查找
				if(rr-ll+1>=x) r=mid-1,k=mid;
				else l=mid+1;
			}
			cout<<k<<"\n";//输出答案
		}
	}
	return 0;
}
```

---

## 作者：zhangxiaohan007 (赞：1)

这道题我们可以从当前 $b_{j}$ 的位置向两边拓展，直到找到距离第 $k$ 远的 $a_{i}$。可是经过分析，$a$ 数组的最大和最小值都很极端，跑一次都挺悬的，别说有 $q$ 次询问了。那有什么方法可以呢？这里我们就可以考虑二分。每一次二分离 $b_{j}$ 的距离是多远。只要找到一个长度使得这个范围内刚好有 $k$ 个 $a$ 数组中的数，那这个距离就是答案了。

下面给出参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
int n,q,a[100005];
bool check(int b,int mid,int k)
{
	auto l=lower_bound(a+1,a+n+1,b-mid);
	auto r=upper_bound(a+1,a+n+1,b+mid);
	return r-l>=k;
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=q;i++)
	{
		int b,k;
		cin>>b>>k;
		int l=-1,r=(int)2e8+5,mid,ans;
		while(r>=l)
		{
			mid=(l+r)/2;
			if(check(b,mid,k))
			{
				r=mid-1;
				ans=mid;
			}
			else l=mid+1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：Hughpig (赞：1)

提供一种不太一样的二分做法。

记某组询问中的 $b_j$ 为 $b$，$k_j$ 为 $k$。

对于 $b$，用二分求出在 $b$ 左边（包括和它重合的）共有多少个点，然后二分左边取多少个点，记 $b$ 到左边取的点中最左的点的距离为 $d$，再在右边二分找出最远距离不超过 $d$ 共可以取多少个点，判断可以取的总数是否大于等于 $k$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)

void ios_optimize(){ios::sync_with_stdio(0);cin.tie(0);}

constexpr int N=2e5+9;

ll n,q,a[N*2],b,k,cnt;

ll check(ll x){
	ll l=cnt+1,r=n+1,mid,ret=cnt;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid]-b>x)r=mid-1;//不可以哦
		else l=mid+1,ret=mid; 
	}
	return ret;
}

int main()
{
	ios_optimize();
    cin>>n>>q;
    up(1,n,i)cin>>a[i];sort(a+1,a+n+1);
    a[0]=-1e9;
    up(n+1,n*2+1,i)a[i]=1e9;
    while(q--){
    	cin>>b>>k;
    	ll ans;
    	cnt=upper_bound(a+1,a+n+1,b)-a-1;//左边的点数 
    	ll l=max(cnt-k+1,0ll),r=cnt,mid,d;
    	while(l<=r){
    		mid=(l+r)>>1;
    		d=b-a[mid];
    		ll right=check(d);
    		if(right-mid+1>=k){
    			l=mid+1;
    			//右边要取k-mid个点 
    			ans=min(d,a[k+mid]-b);
			}
			else r=mid-1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：DengStar (赞：1)

[在博客园中查看](https://www.cnblogs.com/dengstar/p/18329016) | [题目链接](https://atcoder.jp/contests/abc364/tasks/abc364_d)

本题最关键的一点是要转换思路：与其考虑“离某个点第 $k$ 近的点在哪”，不如考虑“离某个点距离不超过 $x$ 的点有多少个”。想到这一步转换，这道题就完成 $80\%$ 了，因为之后的想法都非常顺理成章。

设 $f_i(x)$ 表示在 $A_1, A_2, \cdots, A_n$ 中，离 $B_i$ 距离不超过 $x$ 的点的数量。不难看出，只要找到最小的满足 $f_i(x) \ge k_i$ 的 $x$，那么 $x$ 就是答案。而 $f_i(x)$ 显然是单调递增的，所以可以二分。

最后，如何计算 $f_i(x)$ 呢？可以将 $A_1, A_2, \cdots, A_n$ 从小到大排序，然后我们要做的就是计算落在 $[B_i - x, B_i + x]$ 中的点数。因为 $A$ 已经有序了，可以简单地使用 `lower_bound` 和 `upper_bound` 来查找。

[AC 记录](https://atcoder.jp/contests/abc364/submissions/56075701)

---

## 作者：Daniel_yao (赞：0)

# Solve

很好想的题目。

首先可以考虑到答案具有单调性，所以对于每一次询问用二分处理即可。

然后考虑如何判合法。我们需要找到所有 $a_i-b$ 中 $\le x$ 且 $\ge -x$ 的个数。可以现将 $a_i$ 排好序，最后用两个二分统计个数看是否 $\ge k$ 即可。

时间复杂度 $O(q \log^2 n)$。

# Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)

using namespace std;

const int N = 2e5 + 10;

int n, q, a[N], k, b;

bool check(int x) {
  int L = n+1, R = 0;
  int l = 1, r = n;
  while(l <= r) {
    int mid = l + r >> 1;
    if(a[mid] - b <= x) {
      R = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  l = 1, r = n;
  while(l <= r) {
    int mid = l + r >> 1;
    if(a[mid] - b >= -x) {
      L = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return (R-L+1) >= k;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> q;
  For(i,1,n) cin >> a[i];
  sort(a + 1, a + n + 1);
  while(q--) {
    int l = 0, r = 2e8, ans = 0;
    cin >> b >> k;
    while(l <= r) {
      int mid = l + r >> 1;
      if(check(mid)) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[atcoder原题面](https://atcoder.jp/contests/abc364/tasks/abc364_d)  
先交题解，后等翻译。
## 题目分析：
注意到题目对于每次查询要求距它第 $k$ 近的点之间的距离。  
所以对于 $n$ 个点，我们可以先升序排序，之后二分点之间的距离进行判断，取端点即可。  
## 代码如下：

```cpp
#include<bits/stdc++.h>
#define mihoyo freopen
#define starrail main
#define int long long
#define lowbit(x)  (x&(-x))
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
int n,m,a[N],b,k,p;
inline bool check(int x){
	int r=upper_bound(a+1,a+1+n,b+x)-a-1;
	int l=lower_bound(a+1,a+1+n,b-x)-a;
	return r-l+1>=k;
}
signed starrail()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)	a[i]=read();
	sort(a+1,a+1+n);
	while(m--){
		b=read();k=read();
		int l=0,r=2e8;
		while(l<r){
			int mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=-~mid;
		}
		printf("%lld\n",r);
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## 思路

令 $\omega$ 为 $a$ 的值域（即 $4\times 10^8$），我们可以在 $\operatorname{O}(n\log\omega\log n)$ 的时间复杂度内解决这个问题。

首先我们要对 $a$ 和 $b$ 排序，这是接下来二分的基础。

接下来我们二分我们要输出的答案。我们要在 $[0,4\times 10^8]$ 区间内二分，显然这一步是 $\operatorname{O}(\log(\omega))$ 的。

一个细节是值域是 $-10^8\le a_i\le10^8$，所以至少 $r=2\times 10^8$，但是如果 $r=2\times 10^8$ 会 WA 掉极大数据。令 $r=4\times 10^8$ 即可。

在我们二分完答案 $mid$ 之后，我们要考虑的就是如何快速求出一共有多少数在 $a$ 序列中满足要求。

自然我们不能枚举。不难发现对于 $b_i$，满足条件的 $a_j$ 都符合要求 $b_i-mid\le a_j\le b_i+mid$。

我们可以在 $a$ 序列中二分找出第一个大于等于 $b_i-mid$ 的数和第一个小于等于 $b_i+mid$ 的数，这样我们就找到了 $a$ 序列符合条件的区间，即在这个区间内的数都符合条件。

接下来就可以求出区间长度，即当最远距离为 $mid$ 时，我们有多少点符合要求。如果符合条件的个数大于等于 $k$ 个，就说明我们区间取大了，往小取。但是有可能这是符合要求点数大于等于 $k$ 的最小距离，所以我们把答案记录下来。如果点数少于 $k$ 个，即距离小了，我们就往大取。

时间复杂度 $\operatorname{O}(n\log\omega\log n)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],m;
struct node{
	int id,x,k,ans;
}b[200005];
int cmp(node _,node __){
	return _.x<__.x;
}
int cmp2(node _,node __){
	return _.id<__.id;
}
int main(){
//	freopen("data.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&b[i].x,&b[i].k);
		b[i].id=i;
	}
	n++;
	a[n]=2147483647;
	sort(a+1,a+n+1);
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=m;i++){
		long long l=0,r=400000000,mid,ans=0;
//		cout<<i<<endl;
		while(l<r){
			mid=(l+r)>>1;
			int ll=lower_bound(a+1,a+n+1,b[i].x-mid)-a;
			int rr=lower_bound(a+1,a+n+1,b[i].x+mid+1)-a;
			rr--;
//			cout<<mid<<' '<<ll<<' '<<rr<<endl;
			int len=(rr-ll+1);
			if(len>=b[i].k){
				ans=mid;
				r=mid;
			}
			else l=mid+1;
		}
		b[i].ans=ans;
//		cout<<endl;
	}
	sort(b+1,b+m+1,cmp2);
	for(int i=1;i<=m;i++){
		printf("%d\n",b[i].ans);
	}
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

看到“第 $k$ 近的点的距离”，想到了二分，二分这个距离，查询在这个距离中是否有 $k$ 个点。    
形式化地说，查询操作可以表述为：设当前询问的点的坐标为 $x$，距离为 $s$，那么我们就要查询在 $[x-s,x+s]$ 中的点的数量。如果 $< k$，那么距离就要扩大一点，否则距离缩小一点。         
由于 $-10^8 \le a_i,b_i \le 10^8$，坐标范围过大，又要查询到精确区间，可以使用动态开点线段树。
```cpp
#include<stdio.h>
struct sss{long long sum,ch[2];}tree[1600005];
long long n,q,s[100005],b,k,root,tot;
void insert(long long &rt,int l,int r,int whe)
{
    if(!rt) rt=++tot;
    if(l==r) {tree[rt].sum++;return;}
    int mid=(l+r)>>1;
    if(whe<=mid) insert(tree[rt].ch[0],l,mid,whe);
    else insert(tree[rt].ch[1],mid+1,r,whe);
    tree[rt].sum=tree[tree[rt].ch[0]].sum+tree[tree[rt].ch[1]].sum;
}
long long ask(long long rt,long long l,long long r,long long ll,long long rr)
{
    if(!rt) return 0;
    if(ll<1) ll=1;if(rr>200000005) rr=200000005;
    if(ll<=l&&r<=rr) return tree[rt].sum;
    if(r<ll||rr<l) return 0;
    return ask(tree[rt].ch[0],l,(l+r)>>1,ll,rr)+ask(tree[rt].ch[1],((l+r)>>1)+1,r,ll,rr);
}
int main()
{
    scanf("%lld%lld",&n,&q);
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]),insert(root,1,200000005,s[i]+100000001);
    while(q--)
    {
        scanf("%lld%lld",&b,&k);
        long long l=0,r=200000005,ans;
        while(l<=r)
        {
            long long mid=(l+r)>>1;
            if(ask(root,1,200000005,b-mid+100000001,b+mid+100000001)<k) l=mid+1;
            else r=mid-1,ans=mid;
        }
        printf("%lld\n",ans);
    }
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

发现要求在距离某个点第 $k$ 小的数，很明显与某个点距离 $k$ 以内的数的个数一定不小于距离 $k - 1$ 以内的数的个数。即答案具有单调性，想到二分。

于是，直接二分。找到个数的左右端点，判断个数是否大于等于 $k$ 即可。

```
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a[100005], b[100005], k[100005];

int main() {
   cin >> n >> m;
   for(int i = 1; i <= n; i++) cin >> a[i];
   sort(a + 1, a + n + 1);
   for(int i = 1; i <= m; i++) {
     int x, y;
     cin >> x >> y;
     int l = 0, r = 200000000;
     while(l < r) {
       int mid = (l + r) >> 1;
       int t = upper_bound(a + 1, a + n + 1, x + mid) - a - (lower_bound(a + 1, a + n + 1, x - mid) - a);
       if(t >= y) r = mid;
       else l = mid + 1;
     }
     cout << l << endl;
   }
}
```

---

## 作者：Wei_Han (赞：0)

简单题，注意到对于一个 $b_i$，假如我们枚举他可以到达的距离，那么对于一个更大的距离，$b_i$ 可以达到的 $a_i$ 的数量一定单调不减，换句话说，距离是有单调性的，我们可以二分这个东西。现在我们有了 $b_i$ 能达到的前后范围，只需要找到这个范围内有多少点了，这个东西还能二分，在序列上两遍二分找到对应 $a$ 的区间就行了。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define fi first
#define se second
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
const int N=2e6+5,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll x,y,n,m,c,d,e,f,g,a[N],b[N];
string s,t;
inline ll check(ll x,ll mid){
	ll L=x-mid,R=x+mid;
	if(L>a[n]||R<a[1]) return 0;
	ll l=1,r=n;
	while(l<r){
		ll mid=l+r>>1;
		if(a[mid]>=L) r=mid;
		else l=mid+1;
 	}
 	ll Lop=r;
 	l=1,r=n;
 	while(l<r){
 		ll mid=l+r+1>>1;
 		if(a[mid]<=R) l=mid;
 		else r=mid-1;
	 }
	ll Rop=l;
	return Rop-Lop+1;
}

signed main(){
	read(n);read(m);fo(1,i,n) read(a[i]);
	sort(a+1,a+1+n);
	fo(1,i,m){
		ll x,k;read(x);read(k);
		ll l=0,r=1e9;
		while(l<r){
			ll mid=l+r>>1,ans=check(x,mid);
			if(ans>=k) r=mid;
			else l=mid+1;
		}
		wr(r);pr;
	}
	return 0;
}	
``````

---

## 作者：IronMen (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc364_d)

[AtCoder链接](https://atcoder.jp/contests/abc364/tasks/abc364_d)

---
## 题目
在一条数轴上有 $N+Q$ 个点 $A_1, \ldots, A_N,B_1, \ldots ,B_Q$，其中点 $A_i$ 的坐标为 $a_i$，点 $B_j$ 的坐标为 $b_j$。

就每个 $j=1,2, \ldots ,Q$ 回答下面的问题：
> 设 $X$ 是 $A_1,A_2, \ldots ,A_N$ 中离点 $B_j$ 最近的第 $k_j$ 个点。求点 $X$ 与 $B_j$ 之间的距离。更具体地说，设 $d_i$ 是点 $A_i$ 与 $B_j$ 之间的距离。将 $(d_1,d_2, \ldots ,d_N)$ 按升序排序，得到序列 $(d_1',d_2', \ldots ,d_N')$。求 $d_{k_j}'$。

---
## 思路
二分答案，答案所求即为最小的 $d$，满足区间 $[b_i-d,b_i+d]$ 当中，$a_j$ 的数量 $\ge k$。

于是可以把 $a$ 按照坐标排序，每次需要对一个 $d$ 计算区间 $L=b_i-d,R=b_i+d$ 内点数时，只需要再用一层二分答案计算出第一个 $a_j \ge L$ 的位置和第一个 $a_j>R$ 的位置，然后将两个位置做差即为答案。

时间复杂度 $O(n \log^2 n)$。

---
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, q, a[100010], b, k, lb, rb, mid;

int cnt(int l, int r)
{
	return upper_bound(a + 1, a + n + 1, r) - lower_bound(a + 1, a + n + 1, l);
}

int main()
{
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= q; i ++ )
	{
		scanf("%d %d", &b, &k);
		lb = 0;
		rb = 1e9;
		while (lb < rb)
		{
			mid = (lb + rb) / 2;
			if (cnt(b - mid, b + mid) >= k)
				rb = mid;
			else
				lb = mid + 1;
		}
		cout << rb << '\n';
	}
	return 0;
}

---

## 作者：Liyunze123 (赞：0)

这道题给我们 $n$ 个点和 $q$ 个询问，每个询问给出 $b_i,k_i$，让我们求离 $b_i$ 第 $k_i$ 近的点的距离。

我们可以二分求离那个点的距离。然后求出有多少点离 $b_i$ 的距离 $\le mid$。如果点数 $\ge k_i$，距离应该缩小，可以取到 $mid$，所以把 $r$ 的值变成 $mid$。点数 $<k_i$，说明距离应该变大，取不到 $mid$，把 $l$ 的值变成 $mid+1$。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,q,k,a[100010],b;
int main(){
	scanf("%d%d",&n,&q);
	for(int w=1;w<=n;w++)scanf("%d",&a[w]);
	sort(a+1,a+n+1);
	for(int w=1;w<=q;w++){
		scanf("%d%d",&b,&k);
		int l=0,r=2e8;
		while(l<r){
			int m=(l+r)/2;
			int t=lower_bound(a+1,a+n+1,b-m)-a,p=upper_bound(a+1,a+n+1,b+m)-a;
			if(p-t<k)l=m+1;
			else r=m;
		}
		printf("%d\n",l);
	}
    return 0;
}
```

---

## 作者：Moya_Rao (赞：0)

# 题目大意
给定 $n$ 个点，有 $Q$ 次询问，每次询问有两个参数 $b$ 和 $k$，要求出离 $b$ 点第 $k$ 近的点距 $b$ 点的距离（听上去有些绕口？请看[原题](https://atcoder.jp/contests/abc364/tasks/abc364_d)）。

# 思路
首先我们把给定的这 $n$ 个点排一次序。

然后我们要找出，对于 $b$ 点来说，哪些点在它左边，哪些点在它右边，找出它右边的第一个点。可以用一个函数 `lower_bound` 来实现，也可以手写。

接着我们来二分，二分这离它近的 $k$ 个点有多少个在右边。我二分的是在右边的最远的那个点的下标。

我们来算出最后一个被选进的正数和第一个没被选进的正数。如果左端点越界了，那么执行 `l=mid+1`。如果左端点不在它应该在的位置，也就是说左边的既不在 $b$ 点的左边，也不是离 $b$ 点最近的在它右边的点，那么要把右端点调小，从而使左端点变小，也就是执行  `r=mid-1` 的操作。

对于其他的情况，我们先算出最后一个被选进的负数和第一个没被选进的负数，并取出端点最大值。如果区间满足条件，则存下 $ans$ 并退出，因为有且只有一个满足条件的。否则正数大了，把右端点调大；否则负数大了，就把右端点调小。

最后输出 $ans$ 即可。

交上去吧！[AC](https://atcoder.jp/contests/abc364/submissions/56180169) 咯！

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n,Q,a[N],b,k;
int Find(int x){
    //此函数用来寻找大于等于 x 的最小数编号（也可以用 lower_bound 代替）
    //如果找到了返回 1 到 n ，否则返回 n+1
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(a[mid]>=x)ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    a[0]=-0x3f3f3f3f,a[n+1]=0x3f3f3f3f;//初始化极大值
    while(Q--){
        cin>>b>>k;
        int B=Find(b);//得到下标
        int l=B-1,r=n,ans=-1;
        while(l<=r){
            int mid=(l+r)/2;
            int zs=abs(a[mid]-b);//最后一个被选进的正数
            int zs2=abs(a[mid+1]-b);//第一个没被选进的正数
            if(mid-k+1<1)l=mid+1;//左端点越界了
            else if(mid-k+1>B)r=mid-1;//如果左端点根本不在负数域也不在第一个正数
            else{
                int fs=abs(a[mid-k+1]-b);//最后一个被选进的负数
                int fs2=abs(a[mid-k]-b);//第一个没被选进的负数
                int ms=max(zs,fs);//端点最大值
                if(ms<=zs2&&ms<=fs2){ans=ms;break;}//区间满足条件，存下 ans 并退出
                else if(ms>zs2)l=mid+1;//否则正数大了
                else if(ms>fs2)r=mid-1;//否则负数大了
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
请不要抄袭哦！  
也请你们给个赞，好吧？

---

## 作者：__O_v_O__ (赞：0)

定义 $f_j(x)$ 表示所有点中与 $b_j$ 距离不超过 $x$ 的点个数，问题就简化为找到与 $f_j(x)\ge k$ 最小的 $x$，显然可以使用二分。

考虑如何对二分出的 $x$ 来 `check`。我们只需要计算出 $f_j(x)$ 的值，再与 $k$ 比较大小即可。计算 $f_j(x)$，就是要计算 $b_j-x$ 和 $b_j+x$ 之间范围内的 $a$ 的个数，可以先对 $a$ 进行排序，然后再二分即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,a[200001],b,k,l,r;
int ch(int b,int x){
	int L=lower_bound(a+1,a+n+1,b-x)-a;
	int R=upper_bound(a+1,a+n+1,b+x)-a;
	return R-L;
}signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	while(q--){
		cin>>b>>k;
		l=-1,r=0x3f3f3f3f;
		while(l+1<r){
			int mi=l+r>>1;
			if(ch(b,mi)>=k)r=mi;
			else l=mi;
		}
		cout<<r<<'\n';
	}
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc364_d [ABC364D] K-th Nearest
---
### 题目大意
给定 $N$ 个点的位置 $a_1,\dots,a_n$，要求对位于 $b_1,\dots,b_Q$ 的 $Q$ 个点的分别找到距离它们第 $k_1,\dots,k_Q$ 近的点，输出它们的距离 $d_1,\dots,d_Q$。

数据范围：$1 \le N,Q \le 10^5$，$-10^8 \le a_i,b_j \le 10^8$

---
### 题解
对每个 $B_i$ 来说，它们的问题是互相独立的。由于 $N,Q \le 10^5$，它们的复杂度最大在 $\mathcal{O}(\log N)$ 左右，保证总复杂度在 $\mathcal{O}(Q \log N)$ 左右。由此我们可以想到二分它们的距离，排名大于等于 $k_i$ 时缩小，排名小时扩大。其中，用一次 `lower_bound` 和一次 `upper_bound` 分别查找第一个大于等于 $b_i - d_i$ 的点和第一个大于 $B_i + d_i$ 的点，它们编号的差即为点 $B_i$ 附近 $d_i$ 个单位长度中所包含的点的个数，也就是当前 $d_i$ 所对应的 $k_i$。

### 代码
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

int a[100010];
int l, r;
int n, q;
int b, k;

bool check(int mid) {
	int lelen = lower_bound(a + 1, a + 1 + n, b - mid) - a;//第一个在范围中的点 
	int rilen = upper_bound(a + 1, a + 1 + n, b + mid) - a;//第一个不在范围中的点 
	if (rilen - lelen >= k) {//计算排名编号 
		return 1;
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &b, &k);
		l = 0, r = 2e8 + 1;
		while (l < r) {//二分 
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", l);
	}
	return 0;
}

```

---

## 作者：Down_syndrome (赞：0)

## 题意

给出数轴上的 $n$ 个点，第 $i$ 个点代表的数字为 $a_i$。现在给出 $q$ 组询问，每次询问距离 $x_i$ 第 $k_i$ 近的点离 $x_i$ 的距离。

## 思路

二分大法好！

考虑二分答案 $ans$，每次判断 $[x_i-ans,x_i+ans]$ 之间有没有 $k_i$ 个点。容易发现这是单调的。如何判断 $[x_i-ans,x_i+ans]$ 之间点的个数？也可以二分。给 $a$ 数组排序，二分找到第一个大于 $x_i+ans$ 的点的编号减去第一个大于等于 $x_i-ans$ 的编号就是之间的点的数量。时间复杂度 $O(q\log V\log n)$，$V$ 表示 $a$ 的值域。

[code](https://atcoder.jp/contests/abc364/submissions/56021162)

---

## 作者：Gapple (赞：0)

对于每个询问 $(b, k)$，我们考虑二分。

我们二分查找最大的 $d$ 满足，离点 $b$ 有 $\le d$ 的距离的点的个数不大于 $k$。

更详细的说：设 $c_b(d)$ 表示离点 $b$ 有 $\le d$ 的距离的点的个数，则我们要二分查找最大的 $d$ 满足 $c_b(d) \le k$。

函数 $c$ 的值也可以二分查找出来，故总时间复杂度为 $O(n \log n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

constexpr int PT = 1e8;

inline int cnt(int pt, int dist, const vector<int>& pts)
{
    return upper_bound(pts.begin(), pts.end(), pt + dist) - lower_bound(pts.begin(), pts.end(), pt - dist);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    vector<int> pts;

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        int pt;
        cin >> pt;
        pts.emplace_back(pt);
    }

    sort(pts.begin(), pts.end());

    while (q-- > 0) {
        int pt, rank;
        cin >> pt >> rank;

        int l = 0, r = (PT << 1) + 5;

        while (l < r) {
            int mid = (l + r) >> 1;

            if (cnt(pt, mid, pts) >= rank)
                r = mid;
            else
                l = mid + 1;
        }

        cout << l << '\n';
    }

    return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

简单题。

答案具有单调性，考虑二分距离。

对于距离 $x$，可以用 `lower_bound` 和 `upper_bound` 求出 $b-x\sim b+x$ 中 $a_i$ 的数量。如果数量大于等于 $k$，将 $r$ 更新为 $x$，否则将 $l$ 更新为 $x+1$。

二分的复杂度为 $\mathcal O(\log V)$，其中 $V$ 为值域，check 的复杂度为 $\mathcal O(\log n)$，总时间复杂度 $\mathcal O(q\log n\log V)$。

同学赛时写出了 $\mathcal O(q\log n)$ 的解法，膜拜。

check 代码：
```cpp
bool check (int x) {
	int pos1 = lower_bound (a + 1, a + n + 1, b - x) - a - 1;
	int pos2 = upper_bound (a + 1, a + n + 1, b + x) - a - 1;
	return pos2 - pos1 >= k;
}
```

---

