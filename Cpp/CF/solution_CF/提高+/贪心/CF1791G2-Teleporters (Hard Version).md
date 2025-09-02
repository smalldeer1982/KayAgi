# Teleporters (Hard Version)

## 题目描述

The only difference between the easy and hard versions are the locations you can teleport to.

Consider the points $ 0,1,\dots,n+1 $ on the number line. There is a teleporter located on each of the points $ 1,2,\dots,n $ . At point $ i $ , you can do the following:

- Move left one unit: it costs $ 1 $ coin.
- Move right one unit: it costs $ 1 $ coin.
- Use a teleporter at point $ i $ , if it exists: it costs $ a_i $ coins. As a result, you can choose whether to teleport to point $ 0 $ or point $ n+1 $ . Once you use a teleporter, you can't use it again.

You have $ c $ coins, and you start at point $ 0 $ . What's the most number of teleporters you can use?

## 说明/提示

In the first test case, you can move one unit to the right, use the teleporter at index $ 1 $ and teleport to point $ n+1 $ , move one unit to the left and use the teleporter at index $ 5 $ . You are left with $ 6-1-1-1-1 = 2 $ coins, and wherever you teleport, you won't have enough coins to use another teleporter. You have used two teleporters, so the answer is two.

In the second test case, you go four units to the right and use the teleporter to go to $ n+1 $ , then go three units left and use the teleporter at index $ 6 $ to go to $ n+1 $ , and finally, you go left four times and use the teleporter. The total cost will be $ 4+6+3+4+4+9 = 30 $ , and you used three teleporters.

In the third test case, you don't have enough coins to use any teleporter, so the answer is zero.

## 样例 #1

### 输入

```
10
5 6
1 1 1 1 1
8 32
100 52 13 6 9 4 100 35
1 1
5
4 5
4 3 2 1
5 9
2 3 1 4 1
5 8
2 3 1 4 1
4 3
2 3 4 1
4 9
5 4 3 3
2 14
7 5
5 600000000
500000000 400000000 300000000 200000000 100000000```

### 输出

```
2
3
0
1
3
2
1
1
2
2```

# 题解

## 作者：yingkeqian9217 (赞：15)

## 前言

做法和楼上大佬差不多，但是我可能会稍微讲得详细一些。

## 题目描述

一条直线上有 $n+2$ 个点 $0,1,2,...,n+1$，其中 $1,2,...,n$ 号点上有传送点，你刚开始在 $0$ 号点，有 $c$ 枚金币。如果你现在在 $i$ 号点，你可以：

- 当 $i\neq0$ 时，向左走一步，花费 $1$ 金币。
- 当 $i\neq n+1$ 时，向右走一步，花费 $1$ 金币。
- 当 $i$ 号点有传送点时，花费 $a_i$ 个金币传送到 $0$ 号点或者 $n+1$ 号点（你可以选择传送到哪儿），同时 $i$ 号点的传送点消失。

求你最多能使用几个传送点。

## 分析

考虑每一次使用传送点，必定会重置到 $0$ 或 $n+1$，而下一次走到传送点必定是从 $0$ 和 $n+1$ 开始的。于是我们得出一个显然的结论，我们只需要统计每个传送点从 $0$ 与 $n+1$ 开始走所要花费的金币即可。

也就是对于传送点 $i$，从 $0$ 开始所需即为 $i+a_i$ 金币，从 $n+1$ 开始即为 $(n-i+1)+a_i$。

再一想，每一次是从 $0$ 还是从 $n+1$ 是由我们自己决定的，所以我们不妨只计算当前传送点最优走法所需金币，具体来说，就是所需金币 $s_i=\min(i+a_i,(n-i+1)+a_i)$。

但是上面我们都没有考虑初始点是 $0$ 这个因素，也就是说我们必定要有一个传送点我们取它的从 $0$ 开始的路径。我们可以枚举这个传送点。于是，问题变成了在取了这个传送点之后，最多能取多少个其他传送点。

显然贪心，可以预先对 $s_i$ 排序，再在枚举时取最小的（即从 $s_1$ 开始的）一段数。既然是一段，我们就可以使用前缀和。依据前缀和的单调性，直接在 $s$ 上二分即可，找最长的所需金币数 $\le a_i+i$ 的区间右端点（左端点为 $1$）。其中 $i$ 表示枚举的那个从 $0$ 开始的传送点。

当然，我们在二分的时候要注意去掉枚举的 $i$ 造成的影响，可以预先记录位置，特判即可，详见代码。

## Code:
```cpp
#include<bits/stdc++.h>
#define maxn 2900001
#define int long long
using namespace std;
int T,n,m,ans,a[maxn],s[maxn];
int check(int c,int x,int id){//二分最长的合法前缀区间
	int l=1,r=n,sum=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(s[mid]-(mid>=id?x:0)<=c)
        	 sum=mid+(mid>=id?-1:0),l=mid+1;//不要忘记特判x的影响
		else r=mid-1;
	}
	return sum==-1?0:sum;//注意可能无解
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans=0;
		map<int,int>mp;//记录位置
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=min(a[i]+(n-i+1),a[i]+i);//取最小花费
		sort(s+1,s+n+1);
		for(int i=1;i<=n;i++) mp[s[i]]=i,s[i]+=s[i-1];//前缀和
		for(int i=1;i<=n;i++){
			if(m-a[i]-i<0) continue;//可能不合法
			ans=max(ans,check(m-a[i]-i,min(a[i]+(n-i+1),a[i]+i),mp[min(a[i]+(n-i+1),a[i]+i)])+1);//注意要加上当前点i
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

欢迎评论区指出问题！

---

## 作者：_Supernova (赞：11)

# 一、题意

略。

# 二、思路与解法

考虑贪心。
对于每个位置，都有特定的传送消耗。
**注意到各个点互不影响**。

故贪心正确。

每个点的消耗在二者间取最小值：$a_i + i$ 与 $a_i + n - i$。

本质是在两种传送点做选择。

**注意到出发点确定。**

所以枚举第一步所到位置，再进行贪心。

注意此时复杂度过高。

所以使用前缀和数组表示消耗数组，再通过二分快速确定位置。

# 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 2;
ll t;
ll n, c, a[N]; 
vector <pair <ll, ll> > q;
ll br[N];
void solve(void) {
	q.clear();
	memset(br, 0, sizeof br);
	cin >> n >> c;
	for (ll i = 1; i <= n; ++i) {
		cin >> a[i];
		q.push_back(make_pair(a[i] + min(i, n - i + 1),i));
	}
	sort(q.begin(), q.end());
	for (ll i = 0; i < n; ++i) {
		br[i + 1] = br[i] + q[i].first;
	}
	ll ans = 0;
	for (ll i = 1; i <= n; ++i) {
		ll c1 = c;
		ll res = 0;
		if (c1 >= q[i - 1].second + a[q[i - 1].second]) {
			c1 -= (q[i - 1].second + a[q[i - 1].second]);
			++res;
			ll it = upper_bound(br + 1, br + i, c1) - br - 1;
			res += it;
			c1 -= br[it];
			it = upper_bound(br + i + 1, br + n + 1, c1 + br[i]) - br - 1;
			res += (it - i);
		}
		ans = max(ans, res);
	}
	cout << ans << '\n';
	return ;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：mlvx (赞：5)

### 题意

给你一条直线，从 $0$ 出发，$1$ 至 $n$ 每个点都有一个值，可以花费这个值传送到 $0$ 或 $n+1$，每个点只能传送一次，并且向左或向右移动 $1$ 步都会花费 $1$ 的代价，问最多可以传送几次。

### 分析

如果没有从 $0$ 出发的限制，可以自选从 $0$ 或 $n+1$ 出发，那我们就可以把每个数的权值改成 $b_i\gets a_i+\min(i,n-i+1)$。

即把每个点的权值加上走到该点所需的花费，从 $0$ 走和从 $n+1$ 走取小者即可。

然后从小到大排序就行了。

但是现在是从 $0$ 出发，我们可以去掉第一个到的传送门。

暴力枚举第一个，然后暴力计算，复杂度 $O(n^2)$，显然超时。

考虑暴力枚举第一个传送门，然后维护 $b_i$ 前缀和，然后二分即可，复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,c,ans,x;long long s[200001];pair<int,int>a[200001];
int solve(int x){
	int l=0,r=n,mid,ret;
	while(l<=r)(s[mid=l+r>>1]+a[x].first-(mid>=x?min(a[x].first,a[x].second):0)<=c)?(l=mid+1,ret=mid):r=mid-1;
	return ret>=x?ret-1:ret;
}int main(){
	cin>>T;
	while(T--){
		ans=0,cin>>n>>c;
		for(int i=1;i<=n;i++)cin>>x,a[i]={x+i,x+n-i+1};
		sort(a+1,a+n+1,[](pair<int,int>x,pair<int,int>y){return min(x.first,x.second)<min(y.first,y.second);});
		for(int i=1;i<=n;i++)s[i]=s[i-1]+min(a[i].first,a[i].second);
		for(int i=1,l,r,mid;i<=n;i++)if(a[i].first<=c)ans=max(ans,solve(i)+1);
		cout<<ans<<'\n';
	}return 0;
}
```

---

## 作者：2huk (赞：5)

# G2. [Teleporters (Hard Version)](https://codeforces.com/contest/1791/problem/G2)

## Description

一条直线上有 $n+2$ 个点 $0,1,2,...,n+1$，其中 $1,2,...,n$ 号点上有传送器。

在点 $i$，可以执行如下操作：

- 向左移动一个单位，花费 $1$ 硬币。

- 向右移动一个单位，花费 $1$ 硬币。
- 在点 $i$ 使用传送器，传送回到 $0$ 点或者 $n + 1$ 点，花费 $a_i$ 个硬币，**注意每个传送器只能使用一次**。

你有 $c$ 个硬币，求出从 $0$ 点出发，最多可以使用多少个传送器。

## Solution

前面的与 Easy Version 类似。对于第 $i$ 个传送器，首先需要花 $i$ 硬币从 $0$ 到达它，也可以花 $n - i + 1$ 硬币从 $n + 1$ 到达它，然后花 $a_i$ 硬币传送回 $0$，那么如果想使用这个传送器总共需要 $\min(i, n - i + 1) + a_i$ 枚硬币。

此时如果直接排序就会产生错误，由于第 $1$ 个使用的传送器一定是从 $0$ 走过来的的，但是上面的步骤中并没有体现出这一点，所以可能导致每个点都是从 $n + 1$ 来的而产生错误。因此我们需要单独处理第 $1$ 个使用的传送器。

如果只维护 $\min(i + a_i)$，然后其它的再按上面的方法取，也是不可行的。样例 $9$（`7 5`）很好的解释了这一点。

因此我们需要枚举第 $1$ 个使用传送器。在这之前需要让所有的传送器按 $\min(i, n - i + 1) + a_i$ 从小到大排序。

对于第 $i$ 个传送器，首先使用它需要 $i + a_i$ 枚硬币。然后对于其它的传送器而言，需要在 $c - (i + a_i)$ 枚硬币中选择尽量多的。此时就不需要讨论是从前面还是后面走来的了。

这里可以用到前缀和 + 二分。维护 $s_i = \sum\limits_{j = 1}^i (\min(j, n - j + 1) + a_j)$（注意此时这个值已经从小到大排序了），然后我们需要做的就是找到最后一个 $x$ 使得 $s_x \le c - (i + a_i)$。

这里计算 $s_x$ 时还需要注意，由于统计前缀和时可能把 $i$ 计算进去了，因此如果 $x \ge i$ 则 $s_x = s_x - (\min(i, i + n - 1) + a_i)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second

using namespace std;

const int N = 200010;

int T, n, c;
pair<int, int> a[N];
int s[N];

int calc(int x)
{
	int l = 0, r = n, res = -10;
	int left = c - a[x].fi;
	
	while (l <= r)
	{
		int mid = l + r >> 1;
		int val = s[mid];
		if (mid >= x) val -= min(a[x].fi, a[x].se);
		
		if (val + a[x].fi <= c)
			l = mid + 1, res = mid;
		else 
			r = mid - 1;
	}
	
	if (res >= x) -- res;
	return res;
}

bool cmp(pair<int, int> x, pair<int, int> y)
{
	return min(x.fi, x.se) < min(y.fi, y.se);
}

int Solve()
{
	cin >> n >> c;
	for (int i = 1; i <= n; ++ i )
	{
		int x;
		cin >> x;
		a[i] = {x + i, x + n - i + 1};
	}
	
	sort(a + 1, a + n + 1, cmp);
	
	for (int i = 1; i <= n; ++ i )
		s[i] = s[i - 1] + min(a[i].fi, a[i].se);
	
	int res = 0;
	for (int i = 1; i <= n; ++ i )
		if (a[i].fi <= c)
			res = max(res, calc(i) + 1);
	
	return res;
}

main()
{
	cin >> T;
	
	while (T -- )
		cout << Solve() << '\n';
	
	return 0;
}
```

---

## 作者：残阳如血 (赞：4)

### $\textbf{Description}$

一条直线上有 $n+2$ 个点 $0,1,2,...,n+1$，其中 $1,2,...,n$ 号点上有传送点，你刚开始在 $0$ 号点，有 $c$ 枚金币。如果你现在在 $i$ 号点，你可以：

- 当 $i\neq0$ 时，向左走一步，花费 $1$ 金币。
- 当 $i\neq n+1$ 时，向右走一步，花费 $1$ 金币。
- 当 $i$ 号点有传送点时，花费 $a_i$ 个金币传送到 $0$ 号点或者 $n+1$ 号点（你可以选择传送到哪儿），同时 $i$ 号点的传送点消失。

求你最多能使用几个传送点。

### $\textbf{Soluton}$

每个点的位置是固定的，而且起点只有 $0,n+1$，所以可以将花费与每个点绑定。

例如对于点 $i$：

- 从 $0$ 出发到 $i$ 传送：$0\to i$ 花费 $i$，传送花费 $a_i$，所有总共花费 $i+a_i$。
- 从 $n+1$ 出发到 $i$ 传送：$n+1\to i$ 花费 $n+1-i$，传送花费 $a_i$，所以总共花费 $n+1-i+a_i$。

由于前一次传送可以传送到 $0$ 或 $n+1$，所以点 $i$ 的花费即为
$$
\text{cost}_i=\min\{i,n+1-i\}+a_i
$$
显然，我们要尽量选取花费小的点进行传送，所以可以对于 $\rm cost$ 数组从小到大排序，然后从前往后取。

---

但是，这个做法是有问题的。

由于初始在 $0$ 点出发，所以第一次到达的点花费可能不是 $\text{cost}_i$，而是 $i+a_i$。

#### $\textbf{Bruteforce}$

暴力做法是 $O(n^2)$ 的。

先枚举第一次到达的点 $i$，然后对于 $\text{cost}$ 数组，从前向后取花费，直到花费到达 $c$。

当然要跳过 $i$。

#### $\textbf{Binary Search}$

由于 $n\le2\times10^5$，由数据范围反推算法，我们需要一个 $O(n\log n)$ 的做法。

容易发现 $\text{cost}$ 数组中的每一个元素是非负的，所以对于 $i,j\,(1\le i<j\le n)$，有
$$
\sum\limits_{p=1}^i \text{cost}_i<\sum\limits_{q=1}^j \text{cost}_j
$$
所以 $\text{cost}$ 数组满足单调性，可以二分。

---

同样先枚举第一次到达的点 $i$，然后二分还可以传送的次数 $k$。

`check()` 时要分情况讨论：

- $i\le k$ 时：

  传送了 $1\sim k+1$ 的点，花费是 $\sum\limits_{p=1}^{k+1}\text{cost}_p$ 吗？

  并不是。由于点 $i$ 是从 $0$ 出发的，所以点 $i$ 的花费是 $i+a_i$。

  所以花费是
  $$
  \sum\limits_{p=1}^{k+1}\text{cost}_p-\text{cost}_i+i+a_i
  $$
  

- $i>k$ 时，$i$ 对于 $\text{cost}_{1\sim k}$ 没有影响，所以还需要的花费即为 $\text{cost}_k$​。

为了加速计算，可以预处理 $\rm cost$ 的前缀和数组。

### $\textbf{Code}$

```cpp
#include <iostream>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using lint = long long;
const int N = 2e5 + 10;

struct Data {
	int a, t, st;
  // t：从任意两边出发的花费
  // st：从 0 出发的花费
} arr[N];

lint s[N]; // 花费的前缀和
int T, ans, n, c;

bool check(int k, int i, int lim) {
	// 还要传送 k 次，第一次传送是在 i，剩余的钱数为 lim
	return (i > k ? s[k] : s[k + 1] - arr[i].t) <= lim;
}

void binary_search(int i) {
  int l = -1, r = n;
  // 最少可以传送 0 次，最多还可以传送 n-1 次，故将 l,r 向外移动一个
	while (l + 1 != r) {
		int mid = l + r >> 1;
		if (check(mid, i, c - arr[i].st)) l = mid; // 总花费减去 0->i 的花费
		else r = mid;
	}
  ans = max(ans, l + 1); // l 是还可以的，初始还从 i 传送了，故 +1
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (std::cin >> T; T; --T) {
		std::cin >> n >> c, ans = 0;
		for (int i = 1; i <= n; ++i) {
			std::cin >> arr[i].a;
			arr[i].st = i + arr[i].a;
			arr[i].t = min(i, n + 1 - i) + arr[i].a;
		}
		std::sort(arr + 1, arr + n + 1, [](const Data &p, const Data &q){
			return p.t < q.t;
		});
		for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + arr[i].t;
		for (int i = 1; i <= n; ++i) { // 枚举第一个前往的位置
			if (arr[i].st <= c) binary_search(i); // 二分还可以传送的次数
		}
		std::cout << ans << '\n';
	}
	std::cout.flush();
	return 0;
}
```

---

## 作者：fp0cy1tz6mn4rd_ (赞：3)

### 题意
在一条直线上，从表示 $0$ 的点出发，每向左或向右移动一步都要花费 $1$ 的代价，从 $1$ 到 $n$ 间每个点传送到表示 $0$ 或 $n+1$ 的点都有一个代价 $a_i$，问在 $c$ 的代价内能传送多少次。

### 思路
与 Easy Version 差不多。除第一个点外，可以自由选择出发点。从第 $i$ 个点传送所花的代价为 $\min(i,n-i+1)+a_i$。

因为第一个点的出发点只能为 $0$，考虑枚举第一个到达的点，再贪心选择最小的。

从小到大排序后维护一个前缀和，二分求出去掉这个点后能达到的点的数量。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#define int long long
using namespace std;
typedef struct Node{
	int idx,val,cost;
	Node(){}
	Node(int _i,int _x,int _y){ idx=_i,val=_x,cost=_y; }
	bool operator<(const Node& x){ return cost<x.cost; }
} node;
const int N=2e5+5;
int t,n,c,s[N];
node a[N];
signed main(){
//	freopen("CF1791G2.in","r",stdin);
//	freopen("CF1791G2.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>c;
        for(int i=1;i<=n;i++){
            cin>>a[i].val;
			a[i].idx=i;
            a[i].cost=a[i].val+min(a[i].idx,n-a[i].idx+1);
        }
        sort(a+1,a+n+1);	//从小到大排序
        for(int i=1;i<=n;i++)	//前缀和
        	s[i]=s[i-1]+a[i].cost;
        int ans=0;
        for(int i=1;i<=n;i++){
        	int l=0,r=n,x=a[i].val+a[i].idx;
        	if(x>c) continue;	//无法到达第一个点
        	while(l<r){
        		int m=(l+r+1)>>1;
        		if(s[m]-(m>=i?a[i].cost:0)+x<=c) l=m;	//要注意计算时去掉第一个点
        		else r=m-1;
			}
			ans=max(ans,l-(l>=i)+1);	//更新答案，同样要注意去掉第一个点
		}
		cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：3)

考虑类似 G1 的思路，仍然可以算出每个点距离两端的代价，然后取较小值，对代价排序之后贪心即可。

但是这里出现了一个问题：我们必须保证到达的第一个点是从 $ 0 $ 出发的。

于是我们枚举到达的第一个点，维护一个前缀和，然后二分求出去掉这个点之后能够到达的最多点数即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int cnt[26],p[26];
vector<int>v;
int check(int val,int idx,int cost,int n)
{
    int l = 0,r = n-1,ans=-1;
    while(l<=r)
    {
        int mid = (l+r)>>1;
        int bad = 0,minuss = 0;
        if(idx <= mid)
        {
            bad = val;
            minuss = -1;
        }
        if(v[mid] - bad <= cost)
        {
            ans = mid + minuss;
            l = mid + 1;
        }
        else 
            r = mid - 1;
    }
    return ans + 1;
}
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n,i,x,ans=0,c;
    cin >> n >> c;
    map <int,int> mp;
    int arr[n+5];
    v.clear();
    for(i=1; i<=n; i++)
    {
        cin >> x;
        arr[i] = x;
        v.push_back(x + min(i , n - i + 1));
    }
    sort(v.begin(),v.end());
    for(i=n-1; i>=0; i--)
        mp[v[i]] = i;
    for(i=1; i<n; i++)
        v[i] += v[i-1];
    for(i=1; i<=n; i++)
        if(arr[i] + i <= c)
        {
            int val = arr[i] + min(i , n - i + 1);
            int res = check(val , mp[val] , c - (arr[i] + i) , n);
            ans = max(ans , res + 1);
        }
    cout << ans << '\n';
}
}
```


---

## 作者：Meteor_ (赞：2)

# CF1791G2 Teleporters (Hard Version) 题解

## 题目大意

题意挺清楚的，给个[传送门](https://www.luogu.com.cn/problem/CF1791G2)吧。

## 分析

比较简单的贪心题，很容易就能看出来是贪心，也很容易就能看出来贪什么。

我没做[简单版（Teleporters (Easy Version)）](https://www.luogu.com.cn/problem/CF1791G1)，但是我去看了一眼。那个也非常简单，不过提供了一点点思路。虽然提供的东西不多，我还是顺便讲一下吧。

那道题和这道题基本一样，不过传送门只能传到起点，即 $0$ 号点。所以很容易想到，对于每个点算一下使用当前点的传送器所需要的代价 $b_i$，$b_i = a_i + $ 该点到 $0$ 号点的距离，然后贪心用最小的即可。

对于这道题，我们不能这么做，因为对于离 $0$ 号点远但离 $n + 1$ 号点近的点，明显跳到 $n + 1$ 号点再过去更优。

但是我们很容易想到，既然每次（除了第一次）可以从 $0$ 号点开始，也可以从 $n + 1$ 号点开始，那么我们可以把使用这个传送器的代价 $b_i$ 设为 $a_i + \min((i - 0), (n + 1 - i))$，然后贪心。

所以我们主要考虑的是，怎么排除掉第一次的硬性规定（即必须从 $0$ 号点开始走）。

## 题解

我们发现，第一次必须从 $0$ 号点开始，而且只有这一次有限制。所以我们可以枚举这个点，即枚举第一次使用的传送器。

接着去想怎么找最多能用多少个传送器。

我们发现，即使求出了每一个传送器的代价，并排了序，也不好直接求从头用能用多少个（从头指的是排完序从代价最少的开始用）。

于是前缀和优化一下，$qian_i$ 表示我用了代价最少的 $i$ 个传送器所需要的代价，即 $\displaystyle qian_i = \sum_{j = 1}^i b_j$。

我们现在的问题就转化成了对于一个 $c$，怎么去找满足 $qian_i < c$ 的最大的 $i$。

分析到这了，很容易想到二分了吧。

或者你再看看范围 $2 \times 10^5$，大抵是 $O(n \log n)$，枚举需要 $O(n)$，那么我们需要一个 $O(\log n)$ 左右的算法，而且还是要在序列上找一个位置，也很容易想到二分吧。

但是我懒得写二分，写了个 $\operatorname{upper\_bound}$。

但是和二分基本是一样的，都还需要考虑怎么把当前枚举的点对 $qian$ 数组的影响排除掉。

假设我们当前枚举到了传送器 $i$。

我们直接 $\operatorname{upper\_bound}$ 肯定是不行的，因为我们可能会一个传送器算两次，即枚举到 $i$，$i$ 已经用过了，但是 $\operatorname{upper\_bound}$ 时也有可能包含了 $i$。

所以我们先让 $c$ 减去 $a_i - i$（即这个传送器本身的代价与它到 $0$ 号点的距离之和）再加上 $b_i$。这个数的含义就是我们去过第 $i$ 个传送器后，剩下的金币。用这个数 $\operatorname{upper\_bound}$ 一次，如果包含了我们枚举的数 $i$，那么我们就可以直接用这个结果作为当前的答案，与最终的答案 $ans$ 取个 $\max$，但是如果没有包含，那么我们用 $c$ 减去 $a_i - i$ 再 $\operatorname{upper\_bound}$ 一次作为当前的答案，与最终答案 $ans$ 取 $\max$。

最后这一小部分属于代码实现了，建议自己静下来想想。代码实现你不看代码光听我口述，听不明白是正常的，我尽力了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define M 200005
#define P pair<int, int>
#define MP make_pair

using namespace std;

inline int read() {
    int x = 0, s = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            s = -s;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * s;
}

void write(int x) {
    if(x < 0)  {
        x = ~(x - 1);
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

int n, T, a[M], c, qian[M], ans, cnt;
P pa[M];

signed main() {
    T = read();
    for(int t = 1; t <= T; ++ t) {
        ans = 0;
        n = read();
        c = read();
        for(int i = 1; i <= n; ++ i) {
            a[i] = read();
            pa[i] = MP(a[i] + min(i, n + 1 - i), a[i] + i);
        }
        stable_sort(pa + 1, pa + 1 + n);
        for(int i = 1; i <= n; ++ i)
            qian[i] = pa[i].first + qian[i - 1];
        for(int i = 1; i <= n; ++ i) {
            if(c < pa[i].second)
                continue;
            cnt = upper_bound(qian + 1, qian + 1 + n, c - pa[i].second + pa[i].first) - qian - 1;
            if(cnt < i)
                cnt = upper_bound(qian + 1, qian + 1 + n, c - pa[i].second) - qian;
            ans = max(ans, cnt);
        }
        write(ans);
        putchar('\n');
    }
}
```

---

## 作者：Melo_DDD (赞：1)

你说得对，但是这个人因为把 ``first`` 写成了 ``second`` 导致调了一个小时。
# 题目大意
一共 $n+2$ 个点，有 $n$ 有传送点，而且**每个传送点用完之后不能再用**，询问至多能传送几次。
# 题目分析
看数据范围发现复杂度大约 $\mathcal{O}(n\log n)$，在这里我们可以构造出这么一个方法：暴力枚举 $1$ 到 $n$ 的每个点，内层套二分求答案。

那么我们去想如何实现。

首先根据题意，对于当前传送点，我们一定是从 $0$ 或者 $n+1$ 号点走过来的。所以这个点的最少花费就是：
$$\min(i,n+1-i)+a_i$$
当然注意我们的出发点是给定的，必须从 $0$ 走过来。那么对于第一个传送点我们的花费是一定的：
$$i+a_i$$
所以我们要储存这两个信息，我用的是 vector。
显然花费越小我们当然要优先选，所以我们可以排序，同时这个答案具有单调性，所以可以二分。
求多个传送点总花费暴力加肯定会炸，所以用前缀和维护。

那么怎么解决传送点消失的问题？

设我们二分的次数是 $x$，第一个出发点是 $i$（我们已经排好序），那么如果 $x<i$，直接选 $i$ 前面的点就行了，它会不会消失并没有影响，这个时候花费是 $sum_x$。

但是若 $i\le x$ 他消失就会有影响，因为我们不能再使用这个点。所以我们可以选前 $x+1$ 个，再把 $i$ 踢出去，那就是 $sum_{k+1}-cost_i$。

代码（注意 vector 的下标）：

```cpp
#include <bits/stdc++.h>
#define int long long
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 2e5 + 7 ;
int t ,n ,a[N] ,c ,c_ ,sum[N] ,res ;
vector < pair < int ,int > > v ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
inline bool check (int cur ,int rest ,int lim) {
	return (cur + 1 > rest ? sum[rest] : sum[rest + 1] - v[cur].first) <= lim ; // cur 的下标从 0 开始，但是 rest 是从 1 开始，所以 cur 要加 1 再和 rest 比较
}
signed main () {
	read (t) ;
	do { 
		res = 0 ;
		memset (sum ,0 ,sizeof sum) ;
		v.clear () ;
		read (n) ,read (c) ;
		f (i ,1 ,n ,1) {
			read (a[i]) ;
			v.push_back (make_pair (min (i ,n + 1 - i) + a[i] ,i + a[i])) ; 
		}
		sort (v.begin () ,v.end ()); // 自动以 first 为第一关键字排序
		f (i ,0 ,n - 1 ,1) {
			sum[i + 1] = sum[i] + v[i].first ;
		}
		f (i ,0 ,n - 1 ,1) {
			c_ = c ;
			if (c_ >= v[i].second ) {
				c_ -= v[i].second ;
				int l = -1 ,r = n - 1 ,ans = -1 ; // 仔细思考这个取值
				while (l <= r) {
					int mid = l + r >> 1 ;
					if (check (i ,mid ,c_)) {
						ans = mid ;
						l = mid + 1 ;
					}
					else r = mid - 1 ;
				}
				res = max (res ,ans + 1) ; // 没有算上出发点那次，所以加 1
			}
		} 
		cout << res << '\n' ;
	} while (t -- != 1) ;
	return 0 ;
}
```

---

## 作者：Kun_is_Me (赞：0)

# CF1791G2 Teleporters (Hard Version) 题解

### 首先审题。

一条直线上有 $n+2$ 个点，编号分别为 $0,1,2,\dots,n+1$。其中除了 $0$ 号点和 $n+1$ 号点外，每一个点都具有一个神奇的~~妙妙屋~~传送器。

你现在位于点 $i$，可以有如下操作：

- 向左移动一个单位（$i\neq0$）。此操作需要耗费 $1$ 个金币。
- 向右移动一个单位（$i\neq n+1$）。此操作需要耗费 $1$ 个金币。
- 使用 $i$ 号点的传送器，回到 $0$ 号点或 $n+1$ 号点，需要耗费 $a_i$ 个金币作为费用（~~电费啊，机械修理费啊什么的。~~）。

你非常贫穷，手上只有 $c$ 个金币。你想知道你可以使用多少次传送器。

### 写代码前你需要注意。

1. 本题有多测。
1. 每个传送器只能使用一次。

### 解题思路第一部分。（分析）

前期和 Easy Version 类似。

考虑到每次使用传送器都会传送到 $0$ 号点或 $n+1$ 号点，而下一次来到传送点必定是从 $0$ 号点或 $n+1$ 号点过来的。于是有一个明显的结论：我们只需要分别统计每一个传送点从 $0$ 与 $n+1$ 号点开始走所需要的金币即可。

也就是说，对于传送点 $i$，我们可以算出从 $0$ 号点出发所需要的金币为 $i+a_i$，从 $n+1$ 号点出发所需要 $(n-i+1)+a_i$。

我们可以发现，传送到 $0$ 还是 $n+1$ 是由我们自己决定的。所以，我们只需计算当前传送点最优走法所需金币即可。（所需金币 $s_i$ 就相当于上面的两个算式取 $\min$ 值）。

然而，不出意外的话就要出意外了。

并没有考虑初始点是 $0$ 这个因素！

也就是说我们必定要有一个传送点取它的从 $0$ 开始的路径。我们可以~~开一个大膜你~~枚举这个传送点。

于是，问题变成了在取了已经被拎出来的这一个必须要从 $0$ 开始的幸运传送点之后，最多能从其他传送点中取多少个。

### 解题思路第二部分。（算法）

上手鉴定~~大膜你~~贪心。

我们预先对每一个 $s_i$ 进行排序，再取最小的（从 $s_1$ 开始）一段数。

既然是**一段数**，那么正解就是

**贪心+前缀和。**

依据前缀和的单调性，我们可以对 $s$ 直接二分。找最长的所需金币数 $\leq a_i+i$ 区间的右端点（左端点一定为 $1$）。其中 $i$ 表示前文中的幸运传送点。

关于多测，我们可以使用多测函数，其余内容见代码。

### 上代码！（复制者爆零！）

```cpp
#include<bits/stdc++.h>
#define maxn 2900001
#define int long long
using namespace std;
int t,n,m,ans,a[maxn],s[maxn];
int check(int c,int x,int id)
{
	int l=1,r=n,sum=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(s[mid]-(mid>=id?x:0)<=c)sum=mid+(mid>=id?-1:0),l=mid+1; //特判x的影响
		else r=mid-1;
	}
	return sum==-1?0:sum; //注意无解
}
void solve() //多测函数好！
{
	ans=0;
	map<int,int>mp; 
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=min(a[i]+(n-i+1),a[i]+i); //看到min，你想到了什么？
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++) mp[s[i]]=i,s[i]+=s[i-1]; //很明显的前缀和，对吧？
	for(int i=1;i<=n;i++)
	{
		if(m-a[i]-i<0) continue;
		ans=max(ans,check(m-a[i]-i,min(a[i]+(n-i+1),a[i]+i),mp[min(a[i]+(n-i+1),a[i]+i)])+1); //记得加i！
	}
	cout<<ans<<endl;
}
int main() //简短的主函数
{
	ios::sync_with_stdio(false); //装X，请忽略（具体作用请自行bdfs）
	cin>>t;
	for(int i=1;i<=t;i++)solve();//调用多测
	return 0;
}
```

然而当你把代码复制上交时，你会发现一个事实：

喜提 $\text{CE}$。[附上 CE 记录。](https://www.luogu.com.cn/record/158557255)其他关于 CE 的内容请忽略。

这一份代码其实有一个潜在的问题。所以下面，我们就

### 开始 debug 。

注意到原代码的这一个部分：

```cpp
.
.
.
#define int long long
.
.
.
int main()
{
.
.
.
  return 0;
}
```

也就是说，当我们使用 ```int``` 类型对 ```main``` 函数赋值（实际上为 ```long long```）时，我们得到的是 ```long long main```！

这肯定是不行的，对吧？那么我们可以怎样做呢？

1. 将源代码的第三行去掉（感觉会炸精度欸）
1. 在第一项的基础上，再将除了 ```int main``` 以外的 ```int``` 改成 ```long long```（感觉很烦欸）
1. 将 ```int main``` 换成 ```signed main```

这里我们使用了第三种方法。AC 代码见下。
### 真正的代码。（复制者不会爆零！）
```cpp
#include<bits/stdc++.h>
#define maxn 2900001
#define int long long
using namespace std;
int t,n,m,ans,a[maxn],s[maxn];
int check(int c,int x,int id)
{
	int l=1,r=n,sum=-1;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(s[mid]-(mid>=id?x:0)<=c)sum=mid+(mid>=id?-1:0),l=mid+1;
		else r=mid-1;
	}
	return sum==-1?0:sum;
}
void solve()
{
	ans=0;
	map<int,int>mp; 
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=min(a[i]+(n-i+1),a[i]+i);
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++) mp[s[i]]=i,s[i]+=s[i-1];
	for(int i=1;i<=n;i++)
	{
		if(m-a[i]-i<0) continue;
		ans=max(ans,check(m-a[i]-i,min(a[i]+(n-i+1),a[i]+i),mp[min(a[i]+(n-i+1),a[i]+i)])+1);
	}
	cout<<ans<<endl;
}
int mian()
{
	ios::sync_with_stdio(false);
	cin>>t;
	for(int i=1;i<=t;i++) solve();
	return 0;
}
signed main()
{
  mian();
  return 0;
}
```

[另附 AC 记录。](https://www.luogu.com.cn/record/158680251)

今天的题解（应该是这一周的题解）就到这里。我们下次见！

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
题目中要求最大化传送次数，每一次传送贡献为 $1$，所以我们要尽可能使代价更小，很容易想到贪心。

先来分析一种最容易想的情况，假如初始位置可以在 $0$ 和 $n+1$ 两个位置，那么运用贪心，每一个位置的代价就是其权值加上 $\min(i,n-i+1)$。将这些代价从小到大排序取即可。

题目中初始位置只为 $0$，所以考虑枚举最开始传送的位置，之后的初始位置就可以由自己控制了，就回到了上一种情况。

那么枚举之后如何计算呢，考虑用前缀和的思想处理第一种情况的代价，因为我们排序过后是有序的，一定是从左往右依次取，则可以前缀处理。想到这就可以发现此前缀数组有单调性，考虑二分优化我们取的过程，最后再处理一个小细节，因为我们之前已经枚举过了一个位置，所以二分时要除去该位置的值。

排序，一层枚举和二分，所以总时间复杂度为：$O(n \log n)$。
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200010
using namespace std;
int T,n,c,s[N],ans=0;
struct node{
	int a,b;
}q[N];
bool cmp(node x,node y){
	return min(x.a,x.b)<min(y.a,y.b);
}
int solve(int x){
	int l=0,r=n,ret=-10;
	int st=c-q[x].a;
	while(l<=r){
		int mid=l+r>>1;
		int val=s[mid];
		if(mid>=x) val-=min(q[x].a,q[x].b);
		if(val+q[x].a<=c){
			l=mid+1,ret=mid;
		}
		else r=mid-1;
	}
	if(ret>=x) ret--;
	return ret; 
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>c;
		for(int i=1,x;i<=n;i++){
			cin>>x;
			q[i].a=x+i;
			q[i].b=x+n-i+1;
		} 
		sort(q+1,q+n+1,cmp);
		for(int i=1;i<=n;i++){
			s[i]=s[i-1]+min(q[i].a,q[i].b);
		} 
		ans=0;
		for(int i=1;i<=n;i++){
			if(q[i].a<=c){
				ans=max(ans,solve(i)+1);
			}
		}
		cout<<ans<<'\n'; 
	}
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF1791G2 Teleporters (Hard Version)](https://www.luogu.com.cn/problem/CF1791G2)

最劣解选手报道。

首先贪心走最小的花费是不对的，但是一定对了一大半了。

我们把走到某个传送门并进入称为一次操作。

观察到在进行第一次操作以后，以后的每一次操作，都是相对独立的。

也就是在第一次以后，我们可以自由的选择出发点。

如果可以自由选择出发点的话，那么对于一个点，代价就是 $a_i+\min(i,n-i+1)$。

我们考虑每次钦定了第一次操作要的点 $x$，在剩下的点里面，贪心选最小即可。

考虑快速解决这个问题，我们每个点的代价求出来并进行排序，排到线段树上维护和，然后选了点 $x$ 就相当于直接把他改为 $0$ 即可。

然后因为我们排序了，所以放心做二分即可。也就是二分我们当前剩余的钱能取到的最远位置。

时间复杂度为 $O(n \log^2 n)$，就比较逆天。

一套思路下来还是很清晰的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
struct node{
	int id,val;
}c[N];
bool cmp(node a,node b){
	return a.val<b.val;
}
int minn=1e18,n,m,a[N],d[N],ans,pre;
void build(int s,int t,int p){
	if(s==t){
		d[p]=c[s].val; return ;
	}
	int mid=(s+t)>>1;
	build(s,mid,p<<1),build(mid+1,t,p<<1|1);
	d[p]=d[p<<1]+d[p<<1|1];
}
void update(int l,int r,int s,int t,int p,int change){
	if(l<=s&&t<=r)	{d[p]=change;return ;}
	int mid=(s+t)>>1;
	if(l<=mid)	update(l,r,s,mid,p<<1,change);
	if(r>mid)	update(l,r,mid+1,t,p<<1|1,change);
	d[p]=d[p<<1]+d[p<<1|1]; return ;
}
int Query(int l,int r,int s,int t,int p){
	if(l<=s&&t<=r)	return d[p];
	int mid=(s+t)>>1,ans=0;
	if(l<=mid)	ans+=Query(l,r,s,mid,p<<1);
	if(r>mid) ans+=Query(l,r,mid+1,t,p<<1|1);
	return ans;
}
void Slove(int lst,int x){
	int l=0,r=n+1;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(Query(1,mid,1,n,1)>lst)	r=mid;
		else	l=mid;
	}
	if(l>=x)	ans=max(ans,l);
	else	ans=max(ans,l+1);	
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)	scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)	c[i].val=(a[i]+min(i,n+1-i)),c[i].id=i;
		sort(c+1,c+n+1,cmp),build(1,n,1);
		for(int i=1;i<=n;i++){
			int now=a[c[i].id]+c[i].id;
			if(m>=now)
				update(i,i,1,n,1,0),Slove(m-now,i),update(i,i,1,n,1,c[i].val);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：liuenyin (赞：0)

## 题意

一条直线上有 $n$ 个传送点，第 $i$ 个点可以花费 $a_i$ 的代价传送到 $0$ 或者 $n+1$，初始时在 $0$ 点，移动 $1$ 步有 $1$ 的代价，每个点只能传送一次，求在 $c$ 的代价内最多能传送多少次。

## 思路

这道题乍一看和简化版非常相似，唯一的差别就是可以选择传送到 $n+1$，那么选择沿用贪心思路，记录在每个点传送的代价和从两个端点到这个点所用代价的更小值的和作为总代价，从小到大进行排序。

注意到有一个限制条件是第一次传送必须从 $0$ 过去，那么枚举第一次使用的点，并且在计算最多能使用的传送点的时候将从 $0$ 到第一个点的代价记录。具体的，使用前缀和记录前 $i$ 个（排序后）传送点的总代价，二分最多次数 $mid$，比较前缀和第 $mid$ 项和 $c$，如果第一个传送点不在前 $mid$ 个传送点内便将其加入，并记录花费。如果第一个点在前 $mid$ 个传送点内，则更新其花费，更改为从 $0$ 到这个点的花费，时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
#define int ll
int t,n,c,a[N];
struct node{
    int val,id;
    bool operator<(const node &A)const{
        return this->val<A.val;
    }
}v[N];
int s[N],wz[N];
bool check(int mid,int i){
    int t=max(0ll,i-n-1+i);
    if(wz[i]<=mid)return (s[mid]+t<=c);
    else return (s[mid-1]+a[i]+i<=c);
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>c;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            v[i].id=i;
            v[i].val=a[i]+min(i,n+1-i);
        }
        sort(v+1,v+1+n);
        for(int i=1;i<=n;i++){
            s[i]=s[i-1]+v[i].val;
            wz[v[i].id]=i;
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            int l=0,r=n,mid;
            while(l<=r){
                mid=(l+r)/2;
                if(check(mid,i))l=mid+1;
                else r=mid-1;
            }
            ans=max(ans,r);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

