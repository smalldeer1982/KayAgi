# Package Delivery

## 题目描述

Johnny drives a truck and must deliver a package from his hometown to the district center. His hometown is located at point $ 0 $ on a number line, and the district center is located at the point $ d $ .

Johnny's truck has a gas tank that holds exactly $ n $ liters, and his tank is initially full. As he drives, the truck consumes exactly one liter per unit distance traveled. Moreover, there are $ m $ gas stations located at various points along the way to the district center. The $ i $ -th station is located at the point $ x_{i} $ on the number line and sells an unlimited amount of fuel at a price of $ p_{i} $ dollars per liter. Find the minimum cost Johnny must pay for fuel to successfully complete the delivery.

## 说明/提示

In the first sample, Johnny's truck holds $ 4 $ liters. He can drive $ 3 $ units to the first gas station, buy $ 2 $ liters of gas there (bringing the tank to $ 3 $ liters total), drive $ 3 $ more units to the third gas station, buy $ 4 $ liters there to fill up his tank, and then drive straight to the district center. His total cost is $ 2·5+4·3=22 $ dollars.

In the second sample, there is no way for Johnny to make it to the district center, as his tank cannot hold enough gas to take him from the latest gas station to the district center.

## 样例 #1

### 输入

```
10 4 4
3 5
5 8
6 3
8 4
```

### 输出

```
22
```

## 样例 #2

### 输入

```
16 5 2
8 2
5 1
```

### 输出

```
-1
```

# 题解

## 作者：jdsb (赞：12)

## 题意
- 你要开车到一个城市，到这个城市的距离为 $d$ 个单位长度，你的车子有一个油箱，最多装 $n$ 升油，每开一个单位长度要用一升油，路途中有 $m$ 个加油站，第 $i$ 个加油站距离为 $x_i$，油价为 $p_i$ 元，求最少花多少钱才能到终点。
- $1\le m \le 2\times10^5,1\le n \le d\le10^9$
## 分析
- 考虑贪心求出最小代价，我们先将加油站按照距离从小到大排序，对于每个加油站，我们用单调栈预处理出它之后的加油站中，油价比它小的最近的加油站，我们称这个加油站为目标加油站。对于这个加油站，如果它能走到它的目标加油站，则直接加油加到恰好能走到目标加油站，否则就把油加满。

证明：设我们当前的加油站为 $i$，它的目标加油站为 $j$。
1. 当前油量够走到 $j$ 时，因为 $\forall k\in(i,j)\ p_k>p_i$ ，所以只加 $p_i$ 价格的油最优，且走到 $j$ 后可以加更优的价格 $p_j$ 的油，所以只加恰好到 $j$ 的油。

2. 当前油量走不到 $j$ 时，同样 $\forall k\in(i,j)\ p_k>p_i$，所以只加 $p_i$ 价格的油最优，且越多越好，所以加满油。

证毕。

- 所以总的时间复杂度就为排序的复杂度 $O(m\ log \ m)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=2e5+5;
int d,n,m;
struct node{
	int x,p;
}a[N];
inline int cmp(node x,node y) { return x.x<y.x; }
int st[N],top;
int nxt[N];
ll ans;
int main()
{
	d=read(),n=read(),m=read();
	for(int i=1;i<=m;i++) a[i]=(node){read(),read()};
	sort(a+1,a+m+1,cmp);
	//将终点记为第m+1个加油站，方便实现
	a[m+1]=(node){d,-1};
	st[++top]=m+1;
	for(int i=m;i>=0;i--)
	{
		while(top&&a[st[top]].p>a[i].p) top--;
		nxt[i]=st[top];
		st[++top]=i;
	}
	int res=n;//res为剩余油量
	for(int i=0;i<=m;i++)
	{
		//dis为需要加的油，
		int dis=max(0,min(a[nxt[i]].x-a[i].x,n)-res);
		ans+=1ll*dis*a[i].p;
		res-=a[i+1].x-a[i].x-dis;
		if(res<0) return puts("-1"),0;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF627C)

题目很清晰：汽车油箱的大小为 $N$ 升，要去距离 $D$ 单位的城区，中间有 $M$ 个加油站，第 $i$ 个加油站在 $x_i$ 的位置，加一升油需要花 $p_i$ 美元，一升可以前进一个单位长度，初始油箱是满的。问最少要花费多少美元。

做这道题想到的是优先队列做法。在一个单位长度中，找到在之前 $n$ 单位的距离中油价最便宜的加油站，它的油价单位花费就是这个单位长度的花费。如果再往前，那么就会没有油用。一步步走，是肯定能通过的。

注意数据范围：$N \le D \le 10^9$。显然这个大小不支持一个单位的循环。可以换一种思路：先对加油站的位置排序，然后逐一遍历加油站。对于当前遍历的加油站与前面一个加油站的所有单位长度可以直接用优先队列一把算出。为了特判最优解只覆盖了这个区间一半的情况，可以就将这一段拆成两份，一份由最优解算出；剩下一份再用优先队列，直至队列空或者没有这种情况为止。剩下的一段，因为最优解都覆盖的到，所以直接算出距离后乘上单位油价即可。

初始的油装满可以看成原点有一个加油站，并且油价为 $0$。当我们算到终点 $D$ 的时候，最优解就出来了。

怎么判断无解呢？当队列为空的时候，就说明没有一个加油站与该遍历点的距离相差 $\le N$。之前无论加多少油，都无济于事，因为油箱太小。这个时候直接输出 $-1$ 代表无解。

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;
int n,d,m,ans;
struct nod
{
    int x,p;
}a[200005];
bool cmp(nod e,nod f)
{
    return e.x < f.x;
}
struct node //按油价从小往大排序
{
	int x,p;
	bool operator < (const node &e)const
	{
		return p > e.p;
	}
};
priority_queue<node>q;
signed main()
{
    cin >> d >> n >> m;
    for(int i = 1;i <= m;i ++)
        cin >> a[i].x >> a[i].p;
    sort(a + 1,a + m + 1,cmp);//按距离排序
    a[m + 1].x = d;//终点位置为d
    q.push({0,0});
    for(int i = 1;i <= m + 1;i ++)
    {
    	int maxx = a[i - 1].x;
        while(!q.empty() && a[i].x - q.top().x > n)
		{
			ans += max(q.top().x + n - maxx,0LL) * q.top().p;//算最优解能够覆盖到的一半
			maxx = max(maxx,q.top().x + n);//更新临界点
			q.pop();//弹出，后面用不到
		}
        if(q.empty())//队列为空，输出-1
        {
        	cout << -1;
        	return 0;
		}
		ans += (a[i].x - maxx) * q.top().p;//剩下的一半可直接算出
		q.push({a[i].x,a[i].p});//入队
    }
    cout << ans;//输出
    return 0;
}
```

[评测结果](https://codeforces.com/problemset/submission/627/275710588)

---

## 作者：run_away (赞：1)

## 题意

需要驾驶一辆汽车行驶 $d$ 单位的距离，汽车的油箱最多装 $n$ 个单位的油，出发时邮箱装满了油。路上有 $m$ 个加油站，第 $i$ 个加油站在距离起点 $x_i$ 的位置，每个单位的油价值 $p_i$。

求到达终点的最小花费，如果无法到达输出 `-1`。

## 分析

这题和 [CSP-J2023 T2](https://www.luogu.com.cn/problem/P9749) 很像，只加了油箱容量的限制，但大体思路是差不多的。

$nxt_i$ 表示第 $i$ 个加油站后第一个比它价格低的站。

因为当前价格较高，所以应尽量到 $nxt_i$ 再加油，若无法直接到达 $nxt_i$，就在 $i$ 加油，然后跑到 $i+1$。

用单调栈预处理 $nxt_i$，因为对加油站按 $x_i$ 排序，总时间复杂度 $O(m\log m)$(应该没有 dalao 用桶排)。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=200005;
ll d,n,m,nxt[maxn],now,sum;
struct node{ll x,p;inline bool operator<(const node&b)const{return x<b.x;}}a[maxn];
stack<ll>st;
signed main(){
    d=read(),n=read(),m=read();
    for(ll i=1;i<=m;++i){
        a[i].x=read(),a[i].p=read();
    }
    sort(a+1,a+m+1);
    a[m+1]=(node){d,-1};
    st.push(m+1);
    for(ll i=m;i>=0;--i){
        while(!st.empty()&&a[st.top()].p>a[i].p)st.pop();
        nxt[i]=st.top(),st.push(i);
    }
    now=n;
    for(ll i=0;i<=m;++i){
        ll num=max(0ll,min(a[nxt[i]].x-a[i].x,n)-now);
        sum+=num*a[i].p,now-=a[i+1].x-a[i].x-num;
        if(now<0)puts("-1"),exit(0);
    }
    printf("%lld",sum);
    return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

[P1016 [NOIP1999 提高组] 旅行家的预算](https://www.luogu.com.cn/problem/P1016)的弱化版。

考虑**贪心**。

假设你在某个加油站，你在斟酌要不要加油。

此时，精明的你想到了一句很废话但是正确的话：油价越低越好。你开始从油价来**贪心**地思考这两种可能：
- 在这里加油。
- 忍一忍**去别的价格更低的加油站加油**：若不用加油也可以到达油价低的加油站加油，岂不美哉？

聪明的你希望能**到下一个比当前加油站油价更低的加油站去加油**。

于是善用**数据结构**的你，想到用**单调栈**来处理**每个加油站的下一个油价更低的加油站**（可能有点绕口）。

接下来你开始考虑**油箱容量**的限制：
- 加一定的油（可以不加），使得能到下一个油价低的加油站；显然在满足条件的情况下，加得越少越好。
- **若加满了也不能到达下一个加油站，那么无解。**

~~然后你就快乐地完成了旅途并且 AC 了这道题。~~

**注意，给出的加油站的坐标是乱序的，本题要开 long long。**

代码：

~~自认为码风优良。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 5;
struct node {
    int x, p;
    bool operator < (const node &ert) const { return x < ert.x; }
} a[_];
int d, n, m;
int stk[_], top;
int t[_];
long long ans;
signed main() {
    scanf("%d%d%d", &d, &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &a[i].x, &a[i].p);
    sort(a + 1, a + m + 1);
    a[m + 1].x = d, a[m + 1].p = -1;
    stk[++top] = m + 1;
    for (int i = m; i; i--) {
        while (top && a[stk[top]].p > a[i].p) top--;
        t[i] = stk[top];
        stk[++top] = i;
    }
    int now = n;
    for (int i = 0; i <= m; i++) {
        int dist = max(0, min(a[t[i]].x - a[i].x, n) - now);
        ans += 1ll * dist * a[i].p;
        now -= a[i + 1].x - a[i].x - dist;
        if (now < 0) return puts("-1"), 0;
    }
    printf("%lld\n", ans);
}
```

~~闲话：写题解是很累的，给个赞再走吧。~~

---

