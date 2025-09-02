# Playlist

## 题目描述

你有一个有 $n$ 首歌曲的播放列表，第 $i$ 首歌有 $t_i$ 和 $b_i$ 两个特征——分别是它的长度和好听程度。

听这些歌的快乐程度等于这些歌的总长度乘他们中的最小的好听程度。举个例子，听三首长度为 $[5, 7, 4]$ 而好听程度为 $[11, 14, 6]$ 的歌曲获得的快乐程度等于 $(5 + 7 + 4) \times 6 = 96$。

你需要从你的播放列表中选出最多 $k$ 首歌，使听这些歌的快乐程度尽可能的大。

## 样例 #1

### 输入

```
4 3
4 7
15 1
3 6
6 8
```

### 输出

```
78
```

## 样例 #2

### 输入

```
5 3
12 31
112 4
100 100
13 55
55 50
```

### 输出

```
10000
```

# 题解

## 作者：EricWan (赞：13)

~~这是本蒟蒻的第一篇题解，发现问题大佬可以在讨论区回复~~

题目：[CF1140C](https://www.luogu.com.cn/problem/CF1140C)

题意是这样的：选择 $k$ 首歌，使得时间和乘快乐程度最小值最大。

---
我们可以这样想：枚举 $x$，选择快乐程度大于等于 $x$ 的歌中时常较长的，枚举 $x$ 是 $O(b)$ 的，枚举时间较长的是 $O(n^{2})$，之后你会发现，时间效率是 $O(b \times n^{2})$ 的，这样是绝对不行的。

---
这里有一个优化方法：

$x$ 可以只枚举输入的 $n$ 个 $b$，这样效率就是 $O(n^{3})$ 了。

---
这里还有一个优化方法：

我们可以先对歌曲的时间进行从大到小排序，之后枚举时间较长的只需在排序后序列从前往后枚举就可以了，这样效率就是 $O(n^{2})$ 了。

---

这里，本蒟蒻再给大家推荐一个 $O(n \log n)$ 的方法，这就用到优先队列了。

思路和之前的还是大同小异：

首先，排序，注意这里是把给出的 $b$ 从小到大排序。

之后，我们从后往前枚举，插入这一项的时间，之后弹出最少的时间（操作过程中一定要维护一个 $sum$，为队列中数的和）之后更新结果就好了。

如果大家还没有明白，可以看一看代码以及注释。

贴一下 AC 代码，可以供大家参考：
```cpp
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

priority_queue<long long> q;
int n, k;
long long ans , sum;
struct node {
	long long t, b;
} a[300005];
bool cmp(node x, node y) {
	return x.b < y.b;
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i].t >> a[i].b;
	sort(a + 1, a + n + 1, cmp);
	for (int i = n; i >= 1; i--) {
		q.push(-a[i].t);
		sum += a[i].t;
        //压入新的歌曲
		if (n - i + 1 > k) {
			sum += q.top();
			q.pop();
            //如果歌曲数过大，弹出最短的，q 中存的是负数，负负得正，sum += top 就可以了
		}
		ans = max(ans, a[i].b * sum);
        //更新ans
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xht (赞：9)

题目地址：[CF1140C Playlist](https://www.luogu.org/problemnew/show/CF1140C)

按 $beauty$ 值排序

枚举到当前 $beauty$ 值时，要选择长度最长的之前枚举过的 $k$ 个歌曲

用二叉堆（优先队列）维护即可

注意要使用小根堆，可以把权值取反插入

当堆中元素超过 $k$ 个时，弹出堆顶

同时额外用一个变量存储堆中元素和

可能会出现这样一种问题：

我必须要选择当前歌曲的长度鸭，如果弹出了当前歌曲长度怎么办？

其实，如果弹出了当前歌曲长度，就意味着当前歌曲在不选时有更优解，而这个更优解会在之前被计算

因此，这样计算答案是正确的

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 6;
int n, k;
pair<int, int> a[N];
priority_queue<int> q;
ll ans, now;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].second, &a[i].first);
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        now += a[i].second;
        q.push(-a[i].second);
        if ((int)q.size() > k) {
            now += q.top();
            q.pop();
        }
        ans = max(ans, now * a[i].first);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：fengqiao17 (赞：2)

## Solution

使用小根堆（优先队列），并维护队中元素和 $sum$ 和最终答案 $ans$。

1. 按 $b_i$ 从小到大排序，注意，是**从小到大**排序。

2. **从后往前**枚举 $i$，队中插入 $b_i$，并弹出最少的时间，同时维护 $sum$ 以及 $ans$。

## Code

```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf1140c
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
struct node {  // 结构体数组
  int t, b;
};
node a[N];
bool cmp(node x, node y) {
  return x.b < y.b;
}
priority_queue<int, vector<int>, greater<int> > pq;  // 小根堆
signed main() {
  int n, k;
  int sum = 0, ans = -1e9;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].t >> a[i].b;
  }
  sort(a + 1, a + 1 + n, cmp);    // 从小到大排序
  for (int i = n; i >= 1; i--) {  // 注意倒序循环
    pq.push(a[i].t);
    sum += a[i].t;  // 维护sum
    if (k < n - i + 1) {
      sum -= pq.top();  // 维护sum
      pq.pop();
    }
    ans = max(ans, sum * a[i].b);  // 维护ans
  }
  cout << ans;
  return 0;
}
```

---

## 作者：SolIII (赞：2)

## 题目描述
你有一个有 $n$ 首歌曲的播放列表，第 $i$ 首歌有 $t_i$ 和 $b_i$ 两个特征——分别是它的长度和好听程度。

听这些歌的快乐程度等于这些歌的总长度乘他们中的最小的好听程度。举个例子，听三首长度为 $[5, 7, 4]$ 而好听程度为 $[11, 14, 6]$ 的歌曲获得的快乐程度等于 $(5 + 7 + 4) \times 6 = 9$

你需要从你的播放列表中选出最多 $k$ 首歌，使听这些歌的快乐程度尽可能的大。

## 题目分析
第一眼看到题目就想到了贪心，按照好听程度大小排序，排序完后遍历所有的歌曲，选择当前遍历到的长度最长的前 $k$ 首歌曲，算出答案后更新最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 3 * 1e5;
priority_queue<int, vector<int>, greater<int> > q;
struct Node{
	int t, b;
}a[NR + 10];
bool cmp(Node x, Node y){
	return x.b > y.b;
}

int main(){
	//读入
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;i++){
		scanf("%d%d", &a[i].t, &a[i].b);
	}
	sort(a + 1, a + 1 + n, cmp);//按照好听程度排序
   //贪心
	long long sum = 0;
	long long Max = INT_MIN;
	for(int i = 1;i <= n;i++){
		sum += 1ll * a[i].t;//选取当前歌曲
		q.push(a[i].t);
		if((int)q.size() > k){//如果超出了 k 首歌
			sum -= 1ll * q.top();//就把长度最短的从已选的里面弹出
			q.pop();
		}
		Max = max(Max, sum * a[i].b);//更新最大值
	}
	printf("%lld\n", Max);//输出
	return 0;
}
```


---

## 作者：墨宇 (赞：1)

## 题目描述
你有一个有$n$首歌曲的播放列表，第$i$首歌有$t_i$和$b_i$两个特征——分别是它的长度和好听程度。

听这些歌的快乐程度等于这些歌的总长度乘他们中的最小的好听程度。举个例子，听三首长度为$[5,7,4]$而美丽程度为$[11,14,6]$的歌曲获得的快乐程度等于$(5+7+4)*6=96$。

你需要从你的播放列表中选出最多$k$首歌，使听这些歌的快乐程度尽可能的大。

## 输入格式
第一行输入$n$和$k$（$1<=k<=n<=3 * 10^5$）两个整数——分别是播放列表中歌的数量和你最多选的歌的数量。

下面的$n$行，每行包含两个整数$t_i$和比($1<=t_i,b_i<=10^6$)——第$i$首歌的长度和好听程度。
## 输出格式
输出一个整数——最大的可能快乐程度。
|输入|输出  |
|--|--|
|$4\ 3\ 4\ 7\ 15\ 1\ 3\ 6\ 6\ 8$ | $78$ |
|$5\ 3\ 12\ 31\ 112\ 4\ 100\ 100\ 13\ 55\ 55\ 50$ | $10000$ |
## 样例解释
在第一个测试用例中，我们可以选择歌曲${1，3，4}$，因此总的乐趣是$(4+3+6)⋅6=78$
在第二个测试用例中，我们可以选择歌曲 $3$。总快乐将等于$100⋅100=10000$

这到题有一些思维难度。
## $Part\ 1$
我们看到了这句话：你需要从你的播放列表中选出最多$k$首歌，使听这些歌的快乐程度尽可能的大。
于是，我们想到了**两种**解决办法:
* 二分
因为这一道题不是某一个数值，而是在集合内选数，所以，我们不能用二分来求解问题了。
* 贪心
我们想到了以下的**贪心思路**
>1. 我们把得到的每张票**从大到小**排序
>2. 我们把每一个东西依次加入一个**优先队列**,然后判断：压入当前元素，如果元素个数$>k$，那么$sum$减去最小元素，弹出最小元素。
## $Part\ 2$
Talk is cheap,show me the code!

以下是完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e5 + 10;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (c<'0' || c>'9') { if (c == '-')f = -1; else f = 1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	return x * f;
}
inline void write(int x)
{
	if (x > 9)write(x / 10);
	putchar(x % 10 + 48);
}
int n, k, sum, ans;
struct node
{
	int t, b;
	const bool operator>(const node x)const{return b > x.b;}
}s[maxn];
priority_queue<int> q;
signed main()
{
	n = read(); k = read();
	for (int i = 0; i < n; i++)
		s[i].t = read(), s[i].b = read();
	sort(s, s + n, greater<node>());
	for (int i = 0; i < n; i++)
	{
		sum += s[i].t;
		q.push(-s[i].t);
		if (q.size() > k)	sum += q.top(),q.pop();
		ans = max(ans, sum * s[i].b);
	}
	write(ans);
}
```

---

## 作者：James_Brady (赞：1)

本人太菜了不知道什么是小根堆，但我知道什么是优先队列（大雾）

我们知道，对于一首歌i，所有好听值比他大的都对min(v[i])无影响

所以先按v从大到小排序，再从n~1依次枚举min

如果它前面的所有元素的总数小于k，直接将长度入队

如果等于k，若加入这个长度会使答案更优，则弹出最小值，这个元素入队

中间求个max就是答案

code：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define ll long long//不开long long见祖宗
using namespace std;
struct node{
	ll v;
	ll t;
	bool operator < (node x)const{
		return v<x.v;
	}
}a[300100];
priority_queue<ll,vector<ll>,greater<ll> >q;
ll n,k,sum,ans;//sum记录当前最大的∑t[i]
int main()
{
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<=n;i++)
	scanf("%lld%lld",&a[i].t,&a[i].v);
	sort(a+1,a+n+1);
	for(ll i=n;i>=1;i--)
	{
		ll f=q.size();//size返回的是unsinged，直接比较会出现玄学错误
		if(f<k)
		{
			q.push(a[i].t);
			sum+=a[i].t;
		}
		if(f>=k&&a[i].t>q.top())
		{
			sum-=q.top();
			q.pop();
			sum+=a[i].t;
			q.push(a[i].t);	
		}
		ans=max(ans,a[i].v*sum);
	}
	printf("%lld",ans);
}
```


---

