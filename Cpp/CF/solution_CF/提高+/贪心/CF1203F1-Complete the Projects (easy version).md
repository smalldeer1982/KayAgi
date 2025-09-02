# Complete the Projects (easy version)

## 题目描述

简单版与困难版的唯一区别在于，简单版要求你必须完成所有项目，而困难版则不要求。

Polycarp 是一位非常著名的自由职业者。他当前的评分为 $r$ 单位。

一些非常富有的客户要求他为他们的公司完成一些项目。要完成第 $i$ 个项目，Polycarp 至少需要 $a_i$ 单位的评分；完成该项目后，他的评分会变化 $b_i$（即评分会增加或减少 $b_i$，$b_i$ 可以为正也可以为负）。Polycarp 的评分不能降到零以下，否则人们就不会信任评分如此低的自由职业者。

是否存在一种完成所有项目的顺序，使得 Polycarp 在开始每个项目之前都有足够的评分，并且在完成每个项目后评分都不为负？

换句话说，你需要判断是否存在一种项目的完成顺序，使得 Polycarp 在开始每个项目前评分不少于该项目的要求，并且在完成每个项目后评分不为负。

## 说明/提示

在第一个样例中，可能的完成顺序为：$1, 2, 3$。

在第二个样例中，可能的完成顺序为：$2, 3, 1$。

在第三个样例中，可能的完成顺序为：$3, 1, 4, 2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 4
4 6
10 -2
8 -1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 5
4 -5
4 -2
1 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4 4
5 2
5 -3
2 1
4 -2
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3 10
10 0
10 -10
30 0
```

### 输出

```
NO
```

# 题解

## 作者：qcwlmqy (赞：9)

### 思路

令当前$rating = r$,有$a_{1}, a_{ 2 }, b_{ 1 }, b_{ 2 }$

#### 对于$b_{i}$大于0的情况(洛谷的latex不会用~~)

![](https://cdn.luogu.com.cn/upload/pic/72107.png)

#### 对于$b_{i}$小于0的情况

![](https://cdn.luogu.com.cn/upload/pic/72105.png)

综上，对于$b_{i}\ge 0$按$a_{i}$排序

反之，按照$a_{i}+b_{i}$排序

### 代码

** 排序依据**

```cpp
bool cmp_a(const pii& a, const pii& b) {
	return a.first < b.first;//b>0排序依据
}
bool cmp_b(const pii& a, const pii& b) {
	return a.first + a.second > b.first + b.second;//b<0排序依据
}
```

** 预处理排序**

```cpp
for (int i = 1; i <= n; i++) {
	cin >> x >> y;
	if (y >= 0)a[++ml] = pii(x, y);
	else b[++mr] = pii(x, y);
}
sort(a + 1, a + 1 + ml, cmp_a);
sort(b + 1, b + 1 + mr, cmp_b);
```

** 贪心**

```cpp
for (int i = 1; i <= ml; i++) {
	if (a[i].first > r) {
		printf("NO\n");
		return 0;
	}
	r += a[i].second;
}
for (int i = 1; i <= mr; i++) {
	if (b[i].first > r) {
		printf("NO\n");
		return 0;
	}
	r += b[i].second;
}
if (r >= 0)printf("YES\n");
else printf("NO\n");
```

** AC**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 105;
pii a[maxn], b[maxn];
bool cmp_a(const pii& a, const pii& b) {
	if (a.first == b.first) return a.second > b.second;
	return a.first < b.first;
}
bool cmp_b(const pii& a, const pii& b) {
	return a.first + a.second > b.first + b.second;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, r, x, y;
	cin >> n >> r;
	int ml = 0, mr = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		if (y >= 0)a[++ml] = pii(x, y);
		else b[++mr] = pii(x, y);
	}
	sort(a + 1, a + 1 + ml, cmp_a);
	sort(b + 1, b + 1 + mr, cmp_b);
	for (int i = 1; i <= ml; i++) {
		if (a[i].first > r) {
			printf("NO\n");
			return 0;
		}
		r += a[i].second;
	}
	for (int i = 1; i <= mr; i++) {
		if (b[i].first > r) {
			printf("NO\n");
			return 0;
		}
		r += b[i].second;
	}
	if (r >= 0)printf("YES\n");
	else printf("NO\n");
}
```




---

## 作者：lostxxx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1203F1)

# 题目大意

共有 $n$ 个项目，初始 Rating 为 $r$ 。参加每个项目所需 Rating 为 $a_i$ 参加完后 Rating 会增加 $b_i$ 。并且随时随刻 Rating 要大于等于 $0$ 。问能否完成全部项目。

# 题目分析

我们可以知道，完成项目的顺序是可以改变的，所以我们便想到了先排序后贪心。当 $b_i$ 是正数或 $0$ 时，我们可以直接按 $a_i$ 从小到大排序然后依次执行。这一类我们可以用数组 $x$ 来存储。另一类 $b_i$ 为负数的情况我们可以设 $R$ 为当前 Rating 。

由题意得，如果先做任务 $1$ 可能会导致任务 $2$ 完不成。所以：
$$R+b_1<a_2,R+b_2>a_1$$
移项得：
$$R<a_2-b_1,R>a_1-b_2$$
所以：
$$a_1-b_2<a_2-b_1$$
移项得：
$$a_1+b_1<a_2+b_2$$
所以我们将 $b_i$ 为负数的部分按以上规则排序，用数组 $y$ 存下来。

排序完后先遍历 $x$ 数组随后再遍历 $y$ 数组，记得随时判断 Rating 是否小于 $0$ ，有则立马退出。

$code$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,T;
struct node{
    ll t,b;
}x[200100],y[200100];
ll t,b,k1=1,k2=1;
bool cmp1(node a,node b){
    return a.t<b.t;
}
bool cmp2(node a,node b){
    return a.t+a.b>b.t+b.b;
}
int main(){
    k1=1,k2=1;
    cin>>n>>T;
    for (int i=1;i<=n;i++){
        cin>>t>>b;
        if (b>=0){
            x[k1].t=t;
            x[k1++].b=b;
        }else{
            y[k2].t=t;
            y[k2++].b=b;
        }
    }
    sort(x+1,x+k1,cmp1);
    sort(y+1,y+k2,cmp2);
    for (int i=1;i<k1;i++){
        if (T<x[i].t){
            cout<<"NO\n";
            return 0;
        }else{
            T+=x[i].b;
        }
    }
    for (int i=1;i<k2;i++){
        if (T<y[i].t){
            cout<<"NO\n";
            return 0;
        }else if (T<0){
            cout<<"NO\n";
            return 0;
        }else{
            T+=y[i].b;
        }
    }
    if (T<0){
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
}
```
第一篇蓝题题解。

---

## 作者：August_Light (赞：2)

# CF1203F1&F2 Complete the Projects 题解

贪心、反悔贪心。提供贪心的一个巧妙的证法。

[题目传送门](https://www.luogu.com.cn/problem/CF1203F1)

## 题意简述

小 P 在完成项目。他要完成 $n$ 个项目，初始时他的 rating 为 $r$。

- 完成第 $i$ 个项目 rating 至少需要达到 $a_i$。
- 完成第 $i$ 个项目，rating 会加 $b_i$。$b_i$ 可以为负数。
- rating 不能低于 $0$。

小 P 可以以任意顺序完成项目。

- Easy Version：他能否完成所有 $n$ 个项目？
- Hard Version：他最多完成几个项目？

$1 \le n \le 100$，$1 \le r, a_i \le 30000$，$-300 \le b_i \le 300$。

加强：$1 \le n \le 10^5$，$1 \le r, a_i, |b_i| \le 10^9$。

## 解法

### Easy Version

先贪心确定完成项目的最优顺序，然后模拟判断是否能完成全部项目。

对于 $b \ge 0$ 的项目，只要 rating 到了 $a$，那就是在白送 rating 给我们。

对于这些项目，我们直接按 $a$ 从小到大排序最先完成。

对于 $b < 0$ 的项目：经过猜测、对拍等方法，我们可以猜是按 $a + b$ 从大到小排序。

接下来我们来证明这一点。

「完成第 $i$ 个项目 rating 至少需要达到 $a_i$，rating 会加 $b_i$」可以看成「完成第 $i$ 个项目会扣除 $a_i$ 的 rating，然后 rating 加上 $a_i + b_i$」。

我们**倒序**看待这些 $b < 0$ 的项目。

对于每一个项目，我们会先吐出 $a + b$ 的 rating，然后增加 $a$ 的 rating。

由于 $a + b$ 比 $a$ 小（$b < 0$），所以此时这些项目全都变成了白送 rating 的项目。

根据上文所叙述白送 rating 的项目的贪心策略，这些项目应该按照 $a + b$ **从小到大**排序。

但是因为刚刚我们都在倒序看待，所以这些项目实际上应该按 $a + b$ **从大到小**排序。

**总结**：贪心策略具体如下。

- $b \ge 0$ 的排在 $b < 0$ 的前面。
- $b \ge 0$，按 $a$ **从小到大**排序。
- $b < 0$，按 $a + b$ **从大到小**排序。

```cpp
    sort(t+1, t+n+1, [](Node x, Node y) {
        if ((x.b >= 0) ^ (y.b >= 0))
            return x.b >= 0;
        if (x.b >= 0)
            return x.a < y.a;
        return x.a + x.b > y.a + y.b;
    });
```

时间复杂度 $O(n \log n)$。

### Hard Version

通过一样的贪心确定完成项目的最优顺序，然后通过反悔贪心确定要完成哪些项目。

若 $b \ge 0$，如果这个项目能接那必须接，如果不能接那就真的没法接。

如果 $b < 0$，此时使用反悔贪心。

如果项目能接，那就先接下，反正等会儿还能反悔。

如果项目不能接，事已至此肯定不能再多做一个项目，把前面完成的最亏的那个项目换掉，这样就能接新的这个项目。「最亏」指 $b$ 最小，可以用一个小根堆维护。（当然，如果这个项目本身就是最亏的，那么直接舍去。）

```cpp
    ll cur = r;
    int ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 1; i <= n; i++) {
        auto [id, a, b] = t[i];
        if (b >= 0) {
            if (cur >= a)
                cur += b, ans++;
        } else {
            if (cur >= a && cur + b >= 0) {
                cur += b, ans++;
                pq.push(b);
            } else if (!pq.empty() && b > pq.top()) {
                cur += b - pq.top(); pq.pop();
                pq.push(b);
            }
        }
    }
```

时间复杂度 $O(n \log n)$。

## 代码

代码为 Hard Version。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 5;

int n; ll r;
struct Node {
    int id;
    ll a, b;
} t[MAXN];

int main() { ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> r;
    for (int i = 1; i <= n; i++) {
        cin >> t[i].a >> t[i].b;
        t[i].id = i;
    }

    sort(t+1, t+n+1, [](Node x, Node y) {
        if ((x.b >= 0) ^ (y.b >= 0))
            return x.b >= 0;
        if (x.b >= 0)
            return x.a < y.a;
        return x.a + x.b > y.a + y.b;
    });

    ll cur = r;
    int ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 1; i <= n; i++) {
        auto [id, a, b] = t[i];
        if (b >= 0) {
            if (cur >= a)
                cur += b, ans++;
        } else {
            if (cur >= a && cur + b >= 0) {
                cur += b, ans++;
                pq.push(b);
            } else if (!pq.empty() && b > pq.top()) {
                cur += b - pq.top(); pq.pop();
                pq.push(b);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
```


---

## 作者：RainFestival (赞：2)

$\rm Difficulty = \color{orange}2100$

我们发现当 $b_i\ge 0$ 与 $b_i<0$ 情况不同，考虑分类讨论：

一个显然的观察得出，如果我们做任务 $x,y$，那么无论以什么顺序完成这些任务，即不论 $(x,y)$ 和 $(y,x)$，是没有对后面其他任务产生影响的。**于是我们只用关心相邻两个任务的顺序问题。**

注意到如果我们无论如何安排 $x,y$ 两个任务的顺序都只能完成其中的 $1$ 个或者 $0$ 个任务了，那么对于顺序的考虑是没有意义的。

也就是说，如果我们无论怎么调节这两个的任务的被考虑顺序，都不能找到一种两个任务都被完成的方案，那么这两个任务的被考虑的顺序是无关的。

说的通俗一些，只完成一个任务（或者不完成任务）硬着头皮完成它就行了，考虑个鬼的顺序！

于是我们思考两个任务都被完成的情况。

**显然我们先做 $b_i\ge0$ 的任务。**

**当 $b_i\ge0$ 的时候，我们对 $a_i$ 从小到大排序，然后依次考虑，如果能做就一定做。**

我们来简单说明以上结论的正确性。

注意到一个关键性质，就是说完成更多的 $b_i\ge 0$ 的问题，只会让评分上升（或保持不变），一定不会让评分下降，因此

+ 原先完成不了的任务，完成了一些其它任务之后回过头来继续完成这个任务，有可能还是完成不了，也有可能可以完成了。

+ 原先可以完成的任务，完成了一些其它任务之后回过头来继续完成这个任务，一定还可以完成。

对于一对完成顺序是相邻的两个任务 $x,y$，不妨设 $a_x\le a_y$。

我们考虑交换 $x,y$，则 $y$ 被先做。

如果原先的评分不足，是不可以完成 $y$ 的，而我们有可能通过先完成 $x$ 上涨评分后完成 $y$。这样就多完成任务 $y$。

如果原先评分连 $x$ 都不能完成，那么 $y$ 更不能完成了，评分的上涨一定是 $0$。

**当 $b_i<0$ 的时候，我们对 $a_i+b_i$ 从大到小排序，然后依次考虑。用动态规划解决问题。**

我们来简单说明以上结论的正确性。

注意到一个关键性质，就是说完成更多的 $b_i<0$ 的问题，只会让评分下降，一定不会让评分上升（或不变），因此

+ 原先完成不了的任务，完成了一些其它任务之后回过头来继续完成这个任务，还是完成不了。

+ 原先可以完成的任务，完成了一些其它任务之后回过头来继续完成这个任务，有可能还可以完成，也有可能完成不了了。

对于一对完成顺序是相邻的两个任务 $x,y$，不妨设 $a_x\ge a_y$。

最初的时候，评分一定要 $\ge a_x$，否则一定不能把两个任务都完成，也就失去了寻找他们被考虑顺序的意义。

所以，我们只需要想考虑这两个任务之前，评分 $\ge a_x$ 的情况。

因为评分 $\ge a_x$，所以也一定 $\ge a_y$ 所以我们无论先完成哪一个任务都是可以的，唯一只需要考虑在完成了第一个任务以后，另外一个任务是否可以完成。

记考虑这两个任务之前，评分为 $r$。

如果我们先完成任务 $x$，那么我们要保证 $r+b_x\ge a_y$ 才能再完成任务 $y$。

如果我们先完成任务 $y$，那么我们要保证 $r+b_y\ge a_x$ 才能再完成任务 $x$。

由于我们要完成更多的任务，于是要考虑更松的下界。

先完成 $x$，要求 $r\ge a_y-b_x$。

先完成 $y$，要求 $r\ge a_x-b_y$。

所以我们比较 $a_y+b_x$ 与 $a_x+b_y$ 的大小关系，来得出考虑 $x$ 与 $y$ 的先后顺序。

移项，可以知道当 $a_x+b_x>a_y+b_y$ 的时候，先完成 $x$ 更优秀；当 $a_x+b_x<a_y+b_y$ 的时候，先完成 $y$ 更优秀。如果 $a_x+b_x=a_y+b_y$, 那么先完成谁都可以。

这样，我们解决了任务的考虑顺序这一问题。

对于 $b_i\ge 0$，我们显然是能完成更多任务就完成更多。

对于 $b_i<0$，我们则需要使用动态规划，因为有些先被考虑的任务，可能因为 $b_i$ 太小，对评分的扣减太多，而不去完成。

如何做这个动态规划呢？

我们记 $dp_{i,j}$ 为考虑完评分为 $i$ 的任务后，当前评分为 $j$ 的最多完成多少个任务。

$dp_{i,j}$ 从哪里转移过来呢？我们只需要考虑完成 $i$ 号任务和不完成 $i$ 好任务就行了两种情况就行了。

记考虑完 $b_i\ge 0$ 的任务后积累的评分为 $r$，总共完成了 $k$ 个任务。

完成 $i$ 号任务，则完成任务前原先的评分 $j'$ 为 $j-b_i$。一定要满足 $a_i\le j'\le r$。

不完成 $i$ 号任务，则完成任务前原先的评分 $j'$ 为 $j$。$j'$ 不需要满足额外的额外的条件。

在满足条件的情况下，$dp_{i,j}=\max{dp_{i-1,j'}+1}$。

初始条件如果 $x=r$ 那么 $dp_{0,x}=k$，否则 $dp_{0,x}=0$。

完成任务的总数目 $s$，就是 $\max\limits_{x=0}^{r}dp_{n,r}$，这是因为最后剩余的评分只要大于 $0$ 一定是可以的，当然它也不可能 $>r$。

当 $s=n$ 的时候，我们可以完成所有问题，否则不可以。

于是我们就解决了这个问题。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm> 
int n,r,m,cnt,dp[105][100005],ans=0;
std::pair<int,int> p[105],s[105];
int cmp(std::pair<int,int> a,std::pair<int,int> b){return a.first+a.second>b.first+b.second;} 
int main()
{
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (y>=0) p[++m]=std::make_pair(x,y);
		else s[++cnt]=std::make_pair(x,y);
	}
	std::sort(p+1,p+m+1);
	std::sort(s+1,s+cnt+1,cmp);
	for (int i=1;i<=m;i++) if (r>=p[i].first) r=r+p[i].second,++ans;
	for (int i=0;i<=cnt;i++) for (int j=0;j<=r;j++) dp[i][j]=-1000000000;
	dp[0][r]=ans;
	for (int i=1;i<=cnt;i++)
		for (int j=0;j<=r;j++)
		{
			dp[i][j]=dp[i-1][j];
			if (j>=s[i].first+s[i].second&&r+s[i].second>=j) dp[i][j]=std::max(dp[i][j],dp[i-1][j-s[i].second]+1);
		}
	ans=0;
	for (int x=0;x<=r;x++) ans=std::max(ans,dp[cnt][x]);
//	printf("%d\n",ans);
	ans==n?puts("YES"):puts("NO");
	return 0;
}
```

时间 $\tt 90ms$ 内存 $\tt 40.04MB$ 代码长度 $\tt 971B$ 

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
题目所求是能否完成所有项目，那么就需要我们推出完成这些项目的最优顺序。先考虑 $b<0$ 的情况，我们可以假设当前有两个项目，分别为 $i$，$j$，则假设先完成 $j$ 可以再做 $i$，可如果先做 $i$ 却无法再做 $j$，比先做 $i$ 再做 $j$ 更优。那么是什么条件使得先做 $j$ 更优？如果当前的评分为 $x$，根据题设可得 $x+b_j\ge a_i$，$x+b_i<a_j$。
移项得 $x\ge a_i-b_j$，$x<a_j-b_i$，整理得 $a_j-b_i>a_i-b_j$，即 $a_j+b_j>a_i+b_i$，所以我们可以得到如果先做 $j$ 更优，那么会有 $a_j+b_j>a_i+b_i$。因此可以设计出一个排序比较顺序。那么对于 $b\ge 0$ 的项目，可以按照 $a_i$ 从小到大排序，这个很显然，并且 $b\ge0$ 的项目要先做，因为要攒够评分才能保证能够完成 $b<0$ 的项目，评分会逐渐减少。最后确定下来完成顺序，就按照拟定的顺序模拟一遍就行了。
### Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6+5;
#define int long long
#define For(i,j,k) for(int i=j;i<=k;i++)
int z,n,T;
struct Node{
  int t,b;
}a[N];
Node b[N],c[N];
int totb,totc;
bool cmp1(Node x,Node y){
  return x.t<y.t;
}
bool cmp2(Node x,Node y){
  return x.t+x.b>y.t+y.b;
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  z=1;
  while(z--){
    cin>>n>>T;
    totb=totc=0;
    For(i,1,n){
      cin>>a[i].t>>a[i].b;
      if(a[i].b<=0){
        ++totb;
        b[totb].t=a[i].t;
        b[totb].b=a[i].b;
      }else{
        ++totc;
        c[totc].t=a[i].t;
        c[totc].b=a[i].b;
      }
    }
    sort(b+1,b+totb+1,cmp2);
    sort(c+1,c+totc+1,cmp1);
    bool f=true;
    for(int i=1;i<=totc;i++){
      if(T>=c[i].t){
        T+=c[i].b;
      }else{
        f=false;
        break;
      }
    }
    if(f==false){
      cout<<"NO\n";
      return 0;
    }
    for(int i=1;i<=totb;i++){
      if(T>=b[i].t){
        T+=b[i].b;
      }else{
        f=false;
        break;
      }if(T<0){
          f=false;
          break;
      }
    }
    if(f==false){
      cout<<"NO\n";
    //   continue;
    }else{
      cout<<"YES\n";
    //   continue;
    }
  }
  return 0;
}
```

---

## 作者：This_Rrhar (赞：1)

## 题目分析

有 $n$ 个项目，初始的 $rating$ 为 $r$，第 $i$ 个项目分别有两个属性 $a_i,b_i$，表示当 $rating \ge a_i$ 时才能做此项目，完成项目后 $rating$ 提升 $b_i$（$b_i$ 可能为负数）。$rating$ 必须保持大于等于 $0$，问是否能完成所有项目。

## 解题思路

对于这道题，由于有一部分任务会增加 $rating$，一部分会减少 $rating$，考虑先完成 $b_i$ 值为正的项目让 $rating$ 达到可以达到的最大值后再完成 $b_i$ 值为负的项目，也就是将项目分成两部分：$b_i \ge 0$ 和 $b_i < 0$。

### 非负数的情况

为了让 $rating$ 达到可达到的最大值，使用贪心策略：按 $a_i$ 从小到大排序，然后顺序遍历，如果当前的 $rating \ge a_i$ ，则将 $rating \gets rating + b_i$，无法该任务无法完成，直接输出结果并退出。

### 负数的情况

当 $rating$ 达到可达到的最大值时表示无法再增加，此时开始做 $b_i$ 为负值的项目。但由于完成一个项目后会使 $rating$ 下降，导致无法完成其它项目，也就是无法按照某个标准来决定优先完成哪个项目，所以考虑使用动态规划。

#### 排序

在动态规划之前，首先要确定项目出现的顺序：设有两个项目，编号分别为 $x,y$，如果要完成 $x$ 再完成 $y$，则当前 $rating$ 需要满足

$$
rating + b_x \ge a_y
$$

如果要完成 $y$ 再完成 $x$，则要满足

$$
rating + a_x \ge b_y
$$

当其中一个被满足时，另一条不能被满足。如果要先完成 $x$ 再完成 $y$，通过移项可以得到两条需要满足的条件：

$$
\begin{cases} rating \ge a_y - b_x\\rating < b_y - a_x \end{cases}
$$

也就是

$$
b_y - a_x > rating \ge a_y - b_x
$$

当然，在排序时不需要知道 $rating$ 的确切值，所以比较 $x,y$ 的出现顺序的函数 `cmp` 可以写成 $b_y-a_x>a_y-b_x$。

当然也可以通过移项改写成 $a_x + a_y > b_x + b_y$。

#### 状态转移方程

设 $dp_j$ 为 $rating \le j$ 时最多能完成的项目数量，则对于每个 $b_i < 0$ 的项目 $i$，有如下的状态转移方程：

$$
dp_j = \begin{cases} 0&j = 0 \\ \max(dp_j,dp_{j + b_i} + 1)&j > 0 \end{cases}
$$

注意：**该方程中的所有 $b_i$ 都为负值，所以是 $dp_{j + b_i}$ 而非 $dp_{j - b_i}$**。

### 答案判定

如果 $b_i$ 为非负数和负数时的任务都可以完成，则表示可以全部完成，否则表示不能完成。

## AC代码（C++20）

```cpp
#include<bits/stdc++.h>
using namespace std;
struct prj{int a,b;}t;
int n,s,dp[1000001],ans;
vector<prj>x,y;
inline bool cmp1(prj p,prj q){return p.a<q.a;}
inline bool cmp2(prj p,prj q){return p.a+p.b<q.a+q.b;}
int main()
{
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&t.a,&t.b);
		if(t.b>=0)x.push_back(t);
		else y.push_back(t);
	}
	sort(x.begin(),x.end(),cmp1),sort(y.begin(),y.end(),cmp2);
	for(prj i:x)
	{
		if(s<i.a)return printf("NO"),0;
		s+=i.b,ans++;
	}
	for(prj i:y)for(int j=s;j>=1;j--)if(j>=i.a&&j+i.b>=0)
		dp[j]=max(dp[j],dp[j+i.b]+1);
	printf("%s",ans+dp[s]==n?"YES":"NO");
}
```

---

## 作者：hkr04 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1203F1)  

### 题意简述：
你有一个初始能力值$r$，有$n$个人找你做事，第$i$个任务有$a_i,b_i$两个参数，表示你必须拥有大于等于$a_i$的能力值才能做这件事，做完以后你的能力值会有$b_i$的变化（可正可负）。任何时刻你的能力值不能为负。  
问你是否能完成所有任务。  

一个比较显然的贪心想法是，我要先尽量做那些使我的能力值变大的事情。所以我们把这些事件根据$b_i$的正负分成两个集合$\text{pos(positive)}$和$\text{neg(negative)}$，。等于0的时候分到$\text{pos}$里去。  

接下来就要考虑怎么安排顺序才能做完（假设能做完的话）。

首先，对于$\text{pos}$集合，直观贪心就是按能力值从小到大做，这时做完每次任务的能力值单调不降，若我无法合法完成第$i$件任务，则后面的任务我也做不了，将第$i$件任务和前面的任何一个任务调换也无法完成。  
所以，这部分按照能力值要求从小到大排序去做即可。  

接着，对于$\text{neg}$集合，考虑先做第$i$件任务比先做第$j$件任务要优需要满足什么条件。  
若$i$在前，则$r\ge a_i,r+b_i\ge a_j\Rightarrow r\ge\max(a_i, a_j-b_i)$；  
若$j$在前，则$r\ge a_j,r+b_j\ge a_i\Rightarrow r\ge \max(a_j, a_i-b_j)$。  
我们希望，$i$在前面可以使$j$在前面**可能不合法**的情况变得合法。所以$\max(a_i,a_j-b_i)\le max(a_j, a_i-b_j)$
$\because b_i,b_j\le 0,\therefore a_j-b_i\ge a_j,a_i-b_j\ge a_i$  
所以为了满足以上条件，应该有$a_i\le a_j-b_i,a_j\le a_i-b_j$且$a_j-b_i\le a_i-b_j$  
整理得：$a_i+b_i\ge a_j+b_j$  
(过程：$a_i\le a_j-b_i\le a_i-b_j-b_i \Rightarrow a_i+b_i\ge a_j+b_j,a_j-b_i\le a_i-b_j \Rightarrow a_i+b_i\ge a_j+b_j$，综上所述即可得此关系)  

至此，贪心的部分已做完，按顺序判断是否合法即可。

代码：
```cpp
#include <cstdio>
#include <algorithm>
using std::sort;
const int maxn=100+10;
struct node
{
	int a,b;
	node() {}
	node(int x,int y) {a=x,b=y;}
}pos[maxn],neg[maxn];
int cnt1,cnt2;

int max(int x,int y) {return x>y?x:y;}
bool cmp1(const node &x,const node &y)
{
	return x.a<y.a;
}
bool cmp2(const node &x,const node &y)
{
	return x.a+x.b>y.a+y.b;
}
int main()
{
	int n,r;
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if (b>=0)
			pos[++cnt1]=node(a, b);
		else
			neg[++cnt2]=node(a, b);
	}
	sort(pos+1, pos+1+cnt1, cmp1);
	sort(neg+1, neg+1+cnt2, cmp2);
	for (int i=1;i<=cnt1;i++)
	{
		if (r<pos[i].a)
		{
			printf("NO\n");
			return 0;
		}
		r+=pos[i].b;
	}
	for (int i=1;i<=cnt2;i++)
	{
		if (r<max(neg[i].a, -neg[i].b))
		{
			printf("NO\n");
			return 0;
		}
		r+=neg[i].b;
	}
	printf("YES\n");
	return 0;
}
```

---

## 作者：coding_goat (赞：0)

# 思路

是一个贪心。

对于第 $i$ 个项目的 $b_i$ 进行分类讨论。

当 $b_i \ge 0$ 时，将 $a_i$ 从小到大排序，因为开始的时间越早就越容易完成。

当 $b_i < 0$ 时，假设完成项目 $x$ 会导致项目 $y$ 完不成，而完成项目 $y$ 又可以完成项目 $x$，那么一定先做 $y$ 再做 $x$。

设当前的时间为 $T$，则：

$T + x.b < y.t$ 且 $T + y.b > x.t$

整理得 $T < y.t - x.b$ 且 $T > x.t - y.b$

所以 $x.t - y.b < y.t - x.b$

因为当这种情况时，会导致完成项目 $x$ 会导致项目 $y$ 完不成，所以对他翻转符号。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxint 0x7fffffff
#define gc getchar()
#define int long long
#define maxn 100050
inline int read(){
	int x=0,f=1;
	char c=gc;
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=gc;
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=gc;
	}
	return x*f;	
}

int n,T;
struct node{
	int t,b; 
}pos[maxn],neg[maxn];
int top1,top2;
bool cmp1(node a1,node a2){
	return a1.t<a2.t;
}
bool cmp2(node a1,node a2){
	return -a1.b+a2.t<-a2.b+a1.t;
}
void work(){
	top1=0,top2=0;
	n=read(),T=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(y>=0) pos[++top1].t=x,pos[top1].b=y;
		else neg[++top2].t=x,neg[top2].b=y;
	}
	sort(pos+1,pos+top1+1,cmp1);
	sort(neg+1,neg+top2+1,cmp2);
	bool flg=0;
	for(int i=1;i<=top1;i++){
		
		if(T<pos[i].t){
			flg=1;
			break;
		}
		T+=pos[i].b;
	}
	for(int i=1;i<=top2;i++){
		//cout<<neg[i].t<<' '<<neg[i].b<<' ';
		if(T<neg[i].t){
			flg=1;
			break;
		}
		T+=neg[i].b;
		if(T<0){
			flg=1;
			break;
		}
	}
	cout<<(flg?"NO":"YES")<<'\n';
}
signed main(){
	int _=1;
	while(_--) work();
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1203F1 Complete the Projects (easy version)](https://www.luogu.com.cn/problem/CF1203F1)

### 思路

~~话说 F1 和 F2 有什么区别吗......~~

这篇题解是按照 F2 的思路讲的，倒退到 F1 就是多了个判断最大值是否等于 $n$。

显而易见的，我们把项目按照 $b_i$ 分为两组，一组满足 $b_i\ge0$，另一组满足 $b_i<0$。

我们先操作第一组，这样可以有更多的 $r$ 去操作第二组。

对于第一组，显而易见的，我们把它们按照 $a_i$ 从小到大排序，因为小的无论如何都能加，不如加进去贡献 $r$。所以在排完序后，直接按顺序做即可，直到 $r<a_i$ 结束操作。

这个时候 $r$ 显然达到了最大值，我们开始操作第二组。

第二组似乎没法直接贪心，因为无论是按 $a_i$ 排序还是按 $b_i$ 排序都会有很明显的反例。考虑这样贪心，我们要操作完之后的 $r$ 尽可能大，这样才能操作更多的项目。所以我们按 $a_i+b_i$ 也就是操作项目 $i$ 之后最小的 $r$ 从大到小排序，按顺序去做。

但是有一个问题，$a_i+b_i$ 是操作后的最小值，实际上很可能比它大，又或者无法操作，贪心不完全有道理。所以在这个基础上我们加一个动态规划，规划是否操作这个项目，来保障贪心的实施。

设 $f_{i,j,0/1}$ 表示第二组操作到第 $i$ 个，此时的 $r$ 值为 $j$，选或不选能得到的最大项目个数。

转移方程很好写，$f_{i,j,0}=\max\{f_{i-1,j,0},f_{i-1,j,1}\};f_{i,j,1}=\max\{f_{i-1,j-b_i,0},f_{i-1,j-b_i,1}\}+1(j-b_i\ge a_i)$。

初值可以把 $f_{0,r_{\max},0}=f_{0,r_{\max},1}$ 设为第一组得到的答案。

这样子最终的答案就为 $\max\{f_{m2,i,0/1}\}$，其中 $m2$ 表示第二组的元素个数。

最后不要忘记给 $f$ 数组设一个比较小的初值，防止误选。

时间复杂度 $O(n\log n+nr)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=105,M=60605,inf=1e9;
int n,r,a,b,m1,m2,f[N][M][2],cnt;
struct node{int a,b;}d1[N],d2[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>r;
    for(int i=1;i<=n;++i){
        cin>>a>>b;
        if(b>=0) d1[++m1]=(node){a,b};
        else d2[++m2]=(node){a,b};//分组
    }
    std::sort(d1+1,d1+m1+1,[](node a,node b){return a.a<b.a;});
    for(int i=1;i<=m1;++i)//第一组直接贪心
        if(r>=d1[i].a){r+=d1[i].b;++cnt;}
        else break;
    for(int i=0;i<=m2;++i)
        for(int j=0;j<=r+305;++j)//稍微越界，防止误选
            for(int k=0;k<=1;++k)
            f[i][j][k]=-inf;
    f[0][r][0]=f[0][r][1]=cnt;
    std::sort(d2+1,d2+m2+1,[](node a,node b){return a.a+a.b>b.a+b.b;});//第二组贪心结合动态规划
    for(int i=1;i<=m2;++i)
        for(int j=r;j>=0;--j){
            f[i][j][0]=std::max(f[i-1][j][0],f[i-1][j][1]);
            if(j-d2[i].b>=d2[i].a) f[i][j][1]=std::max(f[i-1][j-d2[i].b][0],f[i-1][j-d2[i].b][1])+1;//按方程转移
        }
    int ans=0;
    for(int i=0;i<=r;++i)
        for(int j=0;j<=1;++j)
            ans=std::max(ans,f[m2][i][j]);
    cout<<(ans==n?"YES":"NO");
    return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

对 $b_i$ 按照正负数分类讨论。

将 $b_i\ge 0$ 的二元组 $(a_i,b_i)$ 放在第一个数组中，$b_i<0$ 的二元组 $(a_i,b_i)$ 放在第二个数组中。

贪心。第一个数组按照 $a_i$ 从小到大排序，第二个数组按照 $a_i+b_i$ 从大到小排序。

将第一个数组和第二个数组合并，第一个数组的元素在前面。

然后考虑 dp。设 $f_{i,j}$ 表示前 $i$ 个任务中选了一部分完成，当前的 `rating` 值为 $j$，最多可以选多少个任务。显然有 $f_{i,j+b_i}=\max(f_{i,j+b_i},f_{i-1,j}+1)$ 和 $f_{i,j}=\max(f_{i,j},f_{i-1,j})$。

若 $\max_{i=0}^{6\times 10^4}f_{n,i}=n$ 那么成立，否则不成立。

时间复杂度 $O(n\times r)$。


---

## 作者：Garbage_fish (赞：0)

## 一、分析题目

 [题目链接](https://www.luogu.com.cn/problem/CF1203F1)
 
对于不同的增加的声望值 $b_i$，可以分为两种情况：

> $1$. $ b_i\ge 0 $

> $2$. $ b_i\le 0 $

第 $1$ 种情况，可以采取贪心的策略，而第 $2$ 种情况可以采用动态规划的策略。

## 二、代码实现

### 1. 分类

首先，需要将增加的 $rating$ 按正数和负数分开到两个数组中。由于后面要排序，为了方便，此处应该选用 struct 结构体来存储。

### 2. 贪心

贪心时，应该先按 $rating$ 的要求 **从小到大** 排序，让~~这个可怜的~~项目经理先完成 $rating$ 要求尽量低的来增加更多的 $rating$，从而来完成更多的项目。

若当枚举到第 $i$ 个项目时，项目经理已经无法完成这个项目，那么后面的项目肯定也无法完成，所以此时可以直接退出贪心。


### 3. 动态规划

#### ①. 排序

在动态规划之前，要先确定动态规划选择的顺序：

设当处理完正数的情况时，项目经理的 $rating$ 为 $x$，接下来有两个项目，要求的 $rating$ 数分别是 $a_1$、$a_2$，增加的 $rating$ 分别是 $b_1$、$b_2$，那么，若要想同时都能完成两个，第一个放在第二个之前就要满足：

> $x+b_1\ge a_2$，即 $x\ge a_2-b_1$

反之，就要满足：

> $x+b_2\ge a_1$，即 $x\ge a_1-b_2$

所以我们的 cmp 要返回 $a_1-b_2$ 是否小于 $a_2-b_1$，即 $a_1+b_1$ 是否大于 $a_2+b_2$。

#### ②. 状态转移方程

若用 $i$ 来表示执行的第 $i$ 个项目，用 $j$ 来表示 $rating$ 值，用 $dp_j$ 来表示最多可完成的题目，用 $a_i$ 来表示要求的 $rating$ 值，用 $b_i$ 来表示增加的 $rating$ 值，那么就可以得到状态转移方程：
$$dp_{j+b_i}=\max(dp_{j+b_i}, dp_j+1), \max(a_i,-b_i)\le j\le 6\times 10^4$$

需要注意的是，$j$ 的起点不应该只是 $a_i$ ，因为若 $j=a_i$ 且 $a_i+b_i<0$ 时，$dp_{j+b_i}$ 就会发生数组越界，从而获得一个大大的 **RE**

## 三、代码展示
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,zn,fn,s,dp[110][100010],cnt,maxx;
struct A{
	int a,b;
}z[110],f[110];
bool cmpz(A x,A y){
	return x.a<y.a;
}
bool cmpf(A x,A y){
	return x.a+x.b>y.a+y.b;
}
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(b>=0)z[++zn]=(A){a,b};
		else f[++fn]=(A){a,b};
	}
	sort(z+1,z+zn+1,cmpz);
	for(int i=1;i<=zn;i++){
		if(s>=z[i].a){
			cnt++;
			s+=z[i].b;
		}
	}
	sort(f+1,f+fn+1,cmpf);
	for(int i=1;i<=fn;i++){
        if(s>=f[i].a and s+f[i].b>=0){
            dp[i][s+f[i].b]=1;
            maxx=max(maxx,1);
            for(int j=i-1;j>=1;j--){
            	for(int k=max(-f[i].b,f[i].a);k<=60000;k++){
            		if(dp[j][k]!=0){
                        dp[i][k+f[i].b]=max(dp[i][k+f[i].b],dp[j][k]+1);    
                        maxx=max(maxx,dp[i][k+f[i].b]);
                    }
				}
			}
        }
    }
    if(cnt+maxx==n)printf("YES\n");
    else printf("NO\n");
}
}
```

---

## 作者：walk_out_study (赞：0)

### 题意
有 n 件商品，你有 $s$ 元，对于第 $i$ 件，需要有 $need_i$ 元，但只会花费 $val_i$ 元（$val_i$ 对应 $-b_i$），不能欠钱，求能否买些所有商品。

$1\leq n \leq100,1\leq s\leq30000,1\leq need_i\leq30000,-300\leq val_i\leq300$

### 思路

将原题变成以上题意，就挺有趣的。

#### 送钱！
$val_i\leq0$，意味着送钱。送钱还不要么，全收。   
根据以上奇妙理解，就可以得出本题关键：

贪心。尝试将 $val_i \leq0$ 的全部收下，这里要将 $need_i$ 从小到大排序，边买边判断，可以买到更多的商品。

---
#### 如何排序
剩下的商品需要购买。此时就要考虑一个问题：“如何保证取商品的顺序”，如考虑不周，会出现错误。

假设 $need_n$，$val_n$ 很大，从大往小取可能就有问题。应该反过来。

假设我们要购买第 $a$，第 $b$ 两个商品，并且能满足条件。那么就有两种情况：

1. 先买 $a$，再买 $b$：$s-val_a \ge need_b$

1. 先买 $b$，再买 $a$：$s-val_b \ge need_a$

两式同时移项得：
$$\begin{cases}s \ge need_b+val_a\\s \ge need_a+val_b\end{cases}$$

假设第一种更优，即 $a$ 排在前面，那么 $need_b+val_a$ 就要尽量小。就有：
$$need_b+val_a < need_a+val_b$$
将左边的 $need_b$ 与右边的 $need_a$ 分别移项：
$$val_a-need_a < val_b-need_b$$

按照这个排序就好啦，现在得到了最优的策略，按顺序购买，再输出结果就好了。
##### 小细节

输出的时候还要判断剩下的钱数，即 $s \ge 0$ 时才是合法的。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int need,val;
}a1[111],a2[111];
int l1,l2,ans1,n,s,dp[111111],ans,flag=1;
int main() {
	memset(dp,-0x3f,sizeof(dp));
	cin>>n>>s;
	for(int i=1,a,b;i<=n;i++)
	{
		cin>>a>>b;
		b=-b; 
		if(b<=0)
			a1[++l1]=Node{a,b};
		else 
			a2[++l2]=Node{a,b};
	}
	sort(a1+1,a1+l1+1,[](Node a,Node b) {return a.need<b.need;});
	sort(a2+1,a2+l2+1,[](Node a,Node b) {return a.val-a.need<b.val-b.need;});
	for(int i=1;i<=l1;i++)
		if(s>=a1[i].need) 
			s-=a1[i].val;
		else
			flag=0;
	for(int i=1;i<=l2;i++)
	{
		if(s<a2[i].need)
		{
			flag=0;
		}
		s-=a2[i].val;
	}
	if(flag&&s>=0) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```
```

---

## 作者：MiPloRAs_3316 (赞：0)

[可能更好的食用体验](/blog/560595/solution-cf1203f1) $|$ 
[题目传送门](/problem/CF1203F1)

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Meaning 题意}}}}$

给出 $n$ 个项目，初始 rating 为 $r$。

- 完成第 $i$ 个项目需要 rating 达到 $a_i$ 分（$1\leq a_i\leq 3\times 10^4$）。
- 完成第 $i$ 个项目后，rating 会增加 $b_i$ 分（$-300\leq b_i\leq 300$）。
- 任何时候，rating 不能小于 $0$。

问**能否完成所有的**项目。

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Analysis 思路}}}}$

**贪心**主要思路：
1. 将 $b_i$ 为非负数的项目与 $b_i$ 为负数的项目分别储存在 $up$ 和 $down$ 数组中。
2. 排序：$up$ 数组按 $a_i$ **升序**排列，$down$ 数组按 $a_i+b_i$ **降序**排列。
3. 如果当前 rating 值 $s>a_i$，就可以完成该项目，反之，不能完成。
 
想到贪心并不难，重要的是证明。~~（doge~~

---
以下只给出 $down$ 数组排序方式的证明（即 $b_i<0$ 时）：

首先，给出 $2$ 个项目 $A_1$ 和 $A_2$（已降序排列）。

$A=(a_1,b_1),A_2=(a_2,b_2)$

为了方便表示，不妨使 $b_i \gets \left|b_i\right|$。

所以有 $a_1 - b_1 > a_2 - b_2$，即 $a_1 + b_2 > a_2 + b_1$。

假设先处理 $A_2$，再处理 $A_1$ 是可行的（正确的）。
$$\implies\begin{cases}s\geq a_2\\s-b_2\geq a_1\\s\geq b_1+b_2\end{cases}$$

若先处理 $A_1$，再处理 $A_2$ 是可行的，则有：
$$\begin{cases}s\geq a_1\\s-b_1\geq a_2\\s\geq b_1+b_2\end{cases}$$

$$\because s-b_2\geq a_1$$

$$\therefore s\geq a_1,\ s\geq a_1+b_2 > a_2+b_1$$

$$\therefore s-b_1\geq a_2$$

所以先处理 $A_1$，再处理 $A_2$ 是正确的。即按 $a_i-b_i$ 降序排列可以通过贪心获得最优解。（此处的 $b_i$ 恢复正常，是负的）


---
$\large{\textbf{\textsf{\color{RoyalBlue}{Code 代码}}}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=6e4+10;
int n,s,f[maxn];
int cnt,cnt2;
struct stu{
	int a,b;
}up[maxn],dw[maxn];
bool cmp(stu x,stu y)
{return x.a<y.a;}
bool cmp2(stu x,stu y)
{return x.a+x.b>y.b+y.a;}
int main()
{
	scanf("%d%d",&n,&s);
	memset(f,0,sizeof f);
	f[0]=0;
	for(int i=1; i<=n; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(y>=0)
			up[++cnt]=(stu){x,y};
		else dw[++cnt2]=(stu){x,y};
	}//分开储存
	sort(up+1,up+1+cnt,cmp);
	sort(dw+1,dw+1+cnt2,cmp2);
	for(int i=1; i<=cnt; i++)
	{
		if(s>=up[i].a) s+=up[i].b;
		else {puts("NO");return 0;}
	}
	for(int i=1; i<=cnt2; i++)
	{
		if(s>=max(dw[i].a,-dw[i].b)) s+=dw[i].b;
		else {puts("NO");return 0;}
	}
	puts("YES");
	return 0;
}
```

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF1203F1) $|$ 
[题目传送门](/problem/CF1203F1) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

首先可以发现，当 $b_i\ge 0$ 时与 $b_i<0$ 时的情况明显是不同的。因此可以分类讨论这两种情况。

**对于 $b_i\ge 0$ 的情况，将项目按照 $a_i$ 从小到大排序，依次看能否全部完成。**

这个贪心的正确性很显然，因为 $b_i\ge 0$，因此做完一个项目后的评分一定不会减少。也就是说，如果一个项目原本能够完成，那么先做了几个项目后再来做这个项目仍然能够完成。所以只需要按照 $a_i$ 排序，把需要评分更小的项目放在前面做，就一定能确保更多的项目被完成。

**对于 $b_i<0$ 的情况，将项目按照 $a_i+b_i$ 从大到小排序，依次看能否全部完成。**

这个贪心我原本是猜的，居然对了。以下的证明参考了 [@RainFestival 大佬的题解](/blog/36957/solution-cf1203f1)，orz。

考虑两个项目 $1$ 和 $2$，做这两个项目之前的评分为 $s$，不妨假设 $s\ge a_1\ge a_2$。现在我们要尽可能地做完这两个项目，同时还要使得完成这两个项目之后剩下的评分最大。  
- 如果先做项目 $1$，那么做完后的评分为 $s+b_1$，这时还要完成项目 $2$，则需要满足 $s+b_1\ge a_2$。
- 同理，如果先做项目 $2$ 再做项目 $1$，则要满足 $s+b_2\ge a_1$。
- 将这两个式子移项，可以得到：$\begin{cases}s\ge a_2-b_1\\s\ge a_1-b_2\end{cases}$。
- 也就是说，只需要比较 $a_2-b_1$ 和 $a_1-b_2$ 的大小，就能确定这两个项目完成的顺序。
- 再移项一次，得 $\begin{cases}a_2+b_2\\a_1+b_1\end{cases}$。
 - 当 $a_2+b_2<a_1+b_1$ 时，先完成项目 $1$ 更优。当 $a_2+b_2>a_1+b_1$，先完成项目 $2$ 更优；当 $a_2+b_2=a_1+b_1$ 时；完成两个项目的优劣相当。

确定了完成项目的顺序，因为本题只要求能否完成所有项目，因此只需遍历一遍，看能否全部完成即可，并不需要跑一遍 dp 看能完成几个。对于需要求出能完成几个的版本，见此题的 [Hard Version](/problem/CF1203F2)。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,k1,k2,cnt;
struct stu{
	int x,y;
}a[105],b[105];
int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(y>0)a[++k1]=(stu){x,y};//将b>=0和b<0的情况分开处理
		else b[++k2]=(stu){x,y};
	}
	sort(a+1,a+1+k1,[](stu a,stu b){return a.x<b.x;});//lambda表达式，C++11及以上可用
	sort(b+1,b+1+k2,[](stu a,stu b){return a.x+a.y>b.x+b.y;});
	for(int i=1;i<=k1;i++)
		if(s>=a[i].x)s+=a[i].y,cnt++;
	for(int i=1;i<=k2;i++)
		if(s>=b[i].x&&s+b[i].y>=0)//不要忘记判断做完后的评分是否>=0
			s+=b[i].y,cnt++;
	cout<<(cnt==n?"YES":"NO");
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

有 $n$ 个项目，做第 $i$ 个项目需要能力值至少为 $a_i$，做完后能力值会增加 $b_i$（可能为负），给定初始能力值，求是否能够做完所有的项目。

**解题思路**

先将所有项目按 `a[i].x` 从小到大排序，然后将所有 `a[i].y >= 0` 的项目做完。得到新的 $r$ 值。然后将所有 `a[i].y` 为负值的项目提取出来放到一个新的数组中，专门处理，假设有 $m$ 个这样的项目用 $b_m$ 保存，我们每次检查是否有项目可以最后完成即可。如果有第i个项目可以最后完成，就相当于我们的 $r$ 值减去其它 $m-1$ 个项目的 $y$ 值后，依然有 ` r >= a[i].x && r >= abs(a[i].y)`。这样确定了最后完成的项目后，我们再找是否有项目可以倒数第 $2$ 完成即可，以此类推。最后如果完成的项目数 $sum=n$ 说明我们完成了所有项目。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, r, sum, sub;
int vis[N];
struct node {
	int x, y;
}a[N], b[N];
bool cmp(node x, node y) {
	return x.x < y.x;
}
int main() {
	cin >> n >> r;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		if(a[i].x <= r && a[i].y >= 0) {
			r += a[i].y;
			sum++;
		}
		if(a[i].y < 0) {
			b[++m] = a[i];
		}
	}
	bool flag = 0;
	while(true) {
		flag = 0;
		for(int i = 1; i <= m; i++) {
			if(vis[i]) {
				continue;
			}
			sub = 0;
			for(int j = 1; j <= m; j++) {
				if(i == j) {
					continue;
				}
				if(!vis[j]) {
					sub += abs(b[j].y);
				}
			}
			if(r - sub >= b[i].x && r - sub >= abs(b[i].y)) {
				vis[i] = 1;
				sum++;
				flag = 1;
			}
		}
		if(!flag) {
			break;
		}
	}
	if(sum == n) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}
```

---

## 作者：Victory_Defeat (赞：0)

一道很水的$F$题啊，直接见代码注释
```cpp
#include<bits/stdc++.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef double lf;
namespace IN
{
	const int Max_Input_Number=1000000;
	#define getc()(p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,Max_Input_Number),p1==p2)?EOF:*p1++)
	char buf[Max_Input_Number],*p1,*p2;
	template<typename T>inline int input(T &x)
	{
		static std::streambuf *inbuf=cin.rdbuf();
		x=0;
		register int f=0,flag=1;
		register char ch=getc();
		if(ch==EOF)return EOF;
		while(!std::isdigit(ch))
		{
			if(ch=='-')f=1;
			ch=getc();
		}
		if(std::isdigit(ch))x=x*10+(ch&15),ch=getc(),flag=true;
		while(std::isdigit(ch))
		{
			x=x*10+(ch&15);
			ch=getc();
		}
		x=f?-x:x;
		return ch==EOF?EOF:flag;
	}
	template<typename T,typename ...Args>inline int input(T& a,Args& ...args)
	{
		return input(a)&&input(args...);
	}
	inline int readc(char &ch)
	{
		static std::streambuf *inbuf=cin.rdbuf();
		return (ch=getc())==EOF?EOF:0;
	}
	inline int readst(char *st)
	{
		if(readc(*st)!=EOF&&(*st))while(readc(*(++st))!=EOF&&*st!='\n');
		else return EOF;
		return 0;
	}
}
namespace OUT
{
	template <typename T>inline void output(T x)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		static char stack[21];
		static int top=0;
		if(x<0)
		{
			outbuf->sputc('-');
			x=-x;
		}
		if(!x)
		{
			outbuf->sputc('0');
			outbuf->sputc('\n');
			return;
		}
		while(x)
		{
			stack[++top]=x%10+'0';
			x/=10;
		}
		while(top)
		{
			outbuf->sputc(stack[top]);
			--top;
		}
		outbuf->sputc('\n');
	}
	inline void putc(const char ch)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		outbuf->sputc(ch);
	}
	template<typename T>inline void output(const char ch,T x)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		static char stack[21];
		static int top=0;
		if(x<0)
		{
			outbuf->sputc('-');
			x=-x;
		}
		if(!x)
		{
			outbuf->sputc('0');
			outbuf->sputc(ch);
			return;
		}
		while(x)
		{
			stack[++top]=x%10+'0';
			x/=10;
		}
		while(top)
		{
			outbuf->sputc(stack[top]);
			--top;
		}
		outbuf->sputc(ch);
	}
	template<typename T,typename ...Args>inline void output(T a,Args ...args)
	{
		output(a);output(args...);
	}
	template<typename T,typename ...Args> inline void output(const char ch,T a,Args ...args)
	{
		output(ch,a);output(ch,args...);
	}
	inline void putst(const char *st)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		int _len=strlen(st);
		const char *p=st;
		do{outbuf->sputc(*st);st++;}while(st+1<p+_len);
	}
}
using IN::input;
using IN::readc;
using IN::readst;
using OUT::output;
using OUT::putc;
using OUT::putst;
//请自行忽略本注释以上部分
const int N=110;
struct node
{
	int a,b;
}a[N];
//定义结构体
bool cmp(node x,node y)
{
	if(x.b>=0&&y.b>=0)return x.a<y.a;
	if(x.b<0&&y.b<0)return x.a+x.b>y.a+y.b;
	return x.b>=0;
}
/*
排序，如果都为有利，则按需求值排序（越小越好）
如果都为不利，则按剩下值排序（越大越好）
否则（一个有利，一个不利），有利的在前
*/
int n,r;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input(n,r);
	for(int i=1;i<=n;++i)input(a[i].a,a[i].b);
    //读入
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;++i)
	{
		if(r<a[i].a)
		{
			putst("NO\n");
			return 0;
		}
        //如果，满足不了需求，直接输出NO
		r+=a[i].b;
	}
	if(r<0)putst("NO\n");
	else putst("YES\n");
    //判断最后是否<0，是则输出NO
	return 0;
}
//直接排序就做的原因是这种方法能确保是最优解（貌似并不存在跳过）
```

---

