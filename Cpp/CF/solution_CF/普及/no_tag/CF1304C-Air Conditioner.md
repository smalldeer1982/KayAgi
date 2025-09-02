# Air Conditioner

## 题目描述

Gildong owns a bulgogi restaurant. The restaurant has a lot of customers, so many of them like to make a reservation before visiting it.

Gildong tries so hard to satisfy the customers that he even memorized all customers' preferred temperature ranges! Looking through the reservation list, he wants to satisfy all customers by controlling the temperature of the restaurant.

The restaurant has an air conditioner that has 3 states: off, heating, and cooling. When it's off, the restaurant's temperature remains the same. When it's heating, the temperature increases by 1 in one minute. Lastly, when it's cooling, the temperature decreases by 1 in one minute. Gildong can change the state as many times as he wants, at any integer minutes. The air conditioner is off initially.

Each customer is characterized by three values: $ t_i $ — the time (in minutes) when the $ i $ -th customer visits the restaurant, $ l_i $ — the lower bound of their preferred temperature range, and $ h_i $ — the upper bound of their preferred temperature range.

A customer is satisfied if the temperature is within the preferred range at the instant they visit the restaurant. Formally, the $ i $ -th customer is satisfied if and only if the temperature is between $ l_i $ and $ h_i $ (inclusive) in the $ t_i $ -th minute.

Given the initial temperature, the list of reserved customers' visit times and their preferred temperature ranges, you're going to help him find if it's possible to satisfy all customers.

## 说明/提示

In the first case, Gildong can control the air conditioner to satisfy all customers in the following way:

- At $ 0 $ -th minute, change the state to heating (the temperature is 0).
- At $ 2 $ -nd minute, change the state to off (the temperature is 2).
- At $ 5 $ -th minute, change the state to heating (the temperature is 2, the $ 1 $ -st customer is satisfied).
- At $ 6 $ -th minute, change the state to off (the temperature is 3).
- At $ 7 $ -th minute, change the state to cooling (the temperature is 3, the $ 2 $ -nd customer is satisfied).
- At $ 10 $ -th minute, the temperature will be 0, which satisfies the last customer.

In the third case, Gildong can change the state to heating at $ 0 $ -th minute and leave it be. Then all customers will be satisfied. Note that the $ 1 $ -st customer's visit time equals the $ 2 $ -nd customer's visit time.

In the second and the fourth case, Gildong has to make at least one customer unsatisfied.

## 样例 #1

### 输入

```
4
3 0
5 1 2
7 3 5
10 -1 0
2 12
5 7 10
10 16 20
3 -100
100 0 0
100 -50 50
200 100 100
1 100
99 -100 0```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：_ztyqwq (赞：10)

### Description

有一家餐馆，初始温度为 $ m $，你有一台空调，每分钟可以将温度上升 $ 1\degree $ 或下降 $ 1\degree $ 或不变。

现在有 $ n $ 个顾客，第 $ i $ 个顾客要求在 $ t_i $ 时刻餐馆温度处于 $ [l_i, r_i] $ 范围内（**可以取到**）。问是否能满足所有顾客的要求。

~~（$ r_i $ 就是题目中的 $ h_i $，感觉 $ l $ 和 $ r $ 更舒服些 233）~~

### Solution

我们考虑维护对于每个时刻，温度可能取到的区间 $ [L, R] $。初始状态下，$ t = 0, [L, R] = [m, m] $（因为这时只能是 $ m $）

不难发现，一个时刻时，温度区间是 $ [L, R] $，那么过了 $ d $ 时间，那么温度区间将会变成 $ [L - d, R + d] $。因为这时最大可能的温度是 $ R + d $（一直 $ +1 $），最小可能的温度是 $ L - d $（一直 $ -1 $）。

那么我们可以按顾客到达的顺序来处理。维护温度可能的区间 $ [L, R] $。从顾客 $ i - 1 $ 到 $ i $ 时，过去的时间 $ d = t_i - t_{i - 1} $，温度可能的区间 $ [L', R'] = [L - d, R + d] $。

又因为要满足第 $ i $ 个顾客的需求，所以我们将这个区间与 $ [l_i, r_i] $ 取交集即可。

取交集：$ [L, R] \cap [l_i, r_i] = [\max(L, l_i), \min(R, r_i)] $

如果此时我们发现集合为空（$ L > R $，注意是 **严格大于**），则说明不可能，直接输出 `NO`。

如果我们的程序一直处理完了 $ n $ 个顾客（跑完了循环），说明可以满足所有顾客的需求，输出 `YES`。

时间复杂度 $ O(n) $。

### Code

（其实不用 `sort` 的，题目说了输入按时间顺序）

```cpp
#include <bits/stdc++.h>
using namespace std;
struct customer
{
	int t, l, r;
	bool operator < (const customer& ano) const
	{
		return t < ano.t;
	}
}c[101];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			scanf("%d %d %d", &c[i].t, &c[i].l, &c[i].r);
		sort(c + 1, c + n + 1);
		int l = m, r = m;
		bool flag = true;
		for(int i = 1; i <= n; i++)
		{
			int d = c[i].t - c[i - 1].t;
			l -= d;
			r += d;
			l = max(l, c[i].l);
			r = min(r, c[i].r);
			if(l > r)
			{
				flag = false;
				break;
			}
		}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：dblark (赞：3)

此题 $ l_i, r_i $ 范围很大，自然不可能是 DP。

我们考虑对于每个顾客来时确定可能的 $ l, r $ 边界。

显然，每过 $ t $ min，`l -= t, r += t`。

如果这个范围不在 $ l_i, r_i $ 内，则顾客的要求无法满足，输出 `NO`。

否则，根据 $ l_i, r_i $ 调整 $ l, r $ 然后继续。

```cpp
#include <cstdio>
#include <algorithm>
#define N 105

struct node {
    int t, l, r;
} a[N];

inline bool cmp(const node &x, const node &y) { return x.t < y.t; }

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].t, &a[i].l, &a[i].r);
        std::sort(a + 1, a + n + 1, cmp); // 先根据时间排序
        int l = m, r = m;
        int fail = 0;
        for (int i = 1; i <= n; ++i) {
            l -= a[i].t - a[i - 1].t, r += a[i].t - a[i - 1].t; // 更新边界
            if (l > a[i].r || r < a[i].l) {
                fail = 1;
                break;
            }
            l = std::max(l, a[i].l); // 调整边界
            r = std::min(r, a[i].r);
        }
        if (fail) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

---

## 作者：serverkiller (赞：3)

# 题意

有$n$个人 一开始时间为$0$ 温度为$m$

$n$个人有三个数值 $t_i,l_i,r_i$

$t_i$表示第$i$个人来店的时间 $l_i$表示第$i$人要求的最低温度 $r_i$表示第$i$人要求的最高温度 即这个人的要求温度为$[l_i,r_i]$

每分钟 可以选择让温度 升高$1$度或下降$1$度或不变

# solution

考虑直接模拟，根据题意维护可以取到的最大值与最小值

如果维护得到的某时刻的最大值与最小值的区间与要求的没有交集,则不能满足

如果说有交集的话 将维护的区间变为两者的交集

这样做是严格$O(n)$的 ~~可以在读入的时候就做 但是不要忘记要把所有的数读完~~

很$Naive$的想法 看程序qwqwq:
```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,m;
 
int main()
{
	int t;
	scanf("%d",&t);
	while (t--)
	{
		int flag = 1;
		scanf("%d%d",&n,&m);
		int time = 0,maxx = m,mini = m;//其实在里面定义就不用老是担心初始化了qwq
		for (int i = 1; i <= n; i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			if (!flag) continue;//记得多组要把所有的数读完
			maxx += x - time;
			mini -= x - time;
			if (maxx < y || mini > z) flag = 0;//无交集的情况
			if (maxx > z) maxx = z;
			if (mini < y) mini = y;
        //将区间维护成两者的交集
			time = x;//保存现在的时间
 		}
 		if (flag) puts("YES");
 		else puts("NO");
	}
	return 0;
}
```

---

## 作者：lcc17 (赞：2)

维护在第i个顾客来时，餐厅温度能调到的最高温和最低温

再将它并上使顾客满意的最高温和最低温

如果没有交集，则跳出

但是需要注意，只能输出一次，所以要记一个F表示是否输出过

记得读完数据

为了保险，我都开了longlong

代码很简短，有解释
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
inline long long read(){
	long long f=1,res=0;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-'0',c=getchar();}
	return f*res;
}//快读
long long q,n,m;
long long l[101],t[101],h[101];
//t[i]表示第i个客人什么时候来
//l[i]、h[i]分别表示第i个客人满意的最低温和最高温
long long dp[101][2];
//dp[i][0]表示第i个客人来时能调到的最低温，dp[i][1]表示能调到的最高温
bool f=1;
int main(){
	q=read();
	while(q--){
		f=1;
		n=read();m=read();
		memset(dp,0,sizeof(dp));
		dp[0][0]=dp[0][1]=m;//记得初始化，第0个客人来时温度为m
		for(int i=1;i<=n;i++){
			t[i]=read();l[i]=read();h[i]=read();
			dp[i][0]=max(dp[i-1][0]-(t[i]-t[i-1]),l[i]);
			dp[i][1]=min(dp[i-1][1]+(t[i]-t[i-1]),h[i]);//转移方程，必须让第i-1和第i个客人都满意才行
			if(dp[i][0]>dp[i][1]&&f){//没有交集
				cout<<"NO"<<endl;f=0;
			} 
		} 
		if(f) cout<<"YES"<<endl;//输出
	}
	return 0;//快乐结束
}
```


---

## 作者：123456zmy (赞：2)

题意：  
给你一个初始温度 $m$ 和 $n$ 个形如在 $t_i$ 时，温度必须在 $l_i$ 到 $r_i$ 之间的限制条件，你每分钟可以使温度上升 $1$ 或下降 $1$，也可以不改变温度。问是否能满足所以限制条件。
___
能达到的温度一定是一段连续的区间，只要记录限制能达到的最高温度及最低温度的点，如果能达到的最高温度还是比最低要求高则不合法，最低同理。每次如果限制了最高或最低温度则更新限制。~~同理的时候记得改符号。~~

代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
struct abcd{int l,r,t;}a[101];
bool cmp(abcd i,abcd j){return i.t<j.t;}
int t,n,m,h,ht,l,lt;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		l=h=m,lt=ht=0;
		bool ok=1;
		for(int i=1;i<=n;i++)scanf("%lld%lld%lld",&a[i].t,&a[i].l,&a[i].r);
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)if(h+a[i].t-ht<a[i].l||l-a[i].t+lt>a[i].r)
		{
			puts("NO");
			ok=0;
			break;
		}
		else
		{
			if(a[i].l>l-a[i].t+lt)l=a[i].l,lt=a[i].t;
			if(a[i].r<h+a[i].t-ht)h=a[i].r,ht=a[i].t;
		}
		if(ok)puts("YES");
	}
	return 0;
}
```

---

## 作者：ShineEternal (赞：1)

[可能更佳的阅读效果](https://blog.csdn.net/kkkksc03/article/details/104338252)。

## description：

- 一个餐馆中有个空调，每分钟可以选择上调 $1$ 个单位的温度或下调 $1$ 个单位的温度，当然你也可以选择不变，初始的温度为 $m$ 。

- 有 $n$ 个食客，每个食客会在 $t_i$ 时间点到达，他所能适应的最低温度是 $l_i$ ，最高温度是 $h_i$ ，他只会在 $t_i$ 时刻逗留。

- 如果温度不在食客的适应范围内，他就会不舒服，请你判断，空调能否使得 $n$ 位来就餐的食客都感到舒服。

- **本题多组数据**，数据组数不大于 $500$。

- $1\le n\le 100$，$-10^9\le m,l_i,h_i\le 10^9$，$1\le t_i\le 10^9$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：

设刚开始的区间为 $[tmpl,tmpr]$。

其中 $tmpl=tmpr=m$。

那么每次我们能调节到的温度区间为 $[tmpl-\Delta t,tmpr+\Delta t]$。

其中 $\Delta t=t_i-t_{i-1}$。

这是因为我们再规定时间内能将温度调节到这个区间内的任意一点。

然而具体怎样调我们并不关心。

然后这一次我们判断 $[tmpl-\Delta t,tmpr+\Delta t]$ 与 $[l_i,h_i]$ 有无交集即可。

如果不在区间里直接一次就 `no` 了，在区间里因为我们必须要等到那个时间点游客打完酱油再调温度，所以要将温度卡到对应的舒适区间。（这里第二组样例是一个很好的解释。）

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long t[105],l[105],h[105];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		long long m;
		long long tmpT=0;
		scanf("%d%lld",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld%lld%lld",&t[i],&l[i],&h[i]); 
		}
		long long L=m,r=m;
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			L=L-(t[i]-t[i-1]);
			r=r+(t[i]-t[i-1]);
			if(L>h[i]||r<l[i])
			{
				printf("NO\n");
				flag=1;
				break;
			}
			else
			{
				L=max(L,l[i]);
				r=min(r,h[i]);
			}
		}
		if(flag==0)
		{
		printf("YES\n");
		}
	}
	return 0;
}
```

---

