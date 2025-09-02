# Embassy Queue

## 题目描述

In an embassy of a well-known kingdom an electronic queue is organised. Every person who comes to the embassy, needs to make the following three actions: show the ID, pay money to the cashier and be fingerprinted. Besides, the actions should be performed in the given order.

For each action several separate windows are singled out: $ k_{1} $ separate windows for the first action (the first type windows), $ k_{2} $ windows for the second one (the second type windows), and $ k_{3} $ for the third one (the third type windows). The service time for one person in any of the first type window equals to $ t_{1} $ . Similarly, it takes $ t_{2} $ time to serve a person in any of the second type windows. And it takes $ t_{3} $ to serve one person in any of the third type windows. Thus, the service time depends only on the window type and is independent from the person who is applying for visa.

At some moment $ n $ people come to the embassy, the $ i $ -th person comes at the moment of time $ c_{i} $ . The person is registered under some number. After that he sits in the hall and waits for his number to be shown on a special board. Besides the person's number the board shows the number of the window where one should go and the person goes there immediately. Let's consider that the time needed to approach the window is negligible. The table can show information for no more than one person at a time. The electronic queue works so as to immediately start working with the person who has approached the window, as there are no other people in front of the window.

The Client Service Quality inspectors noticed that several people spend too much time in the embassy (this is particularly tiresome as the embassy has no mobile phone reception and 3G). It was decided to organise the system so that the largest time a person spends in the embassy were minimum. Help the inspectors organise the queue. Consider that all actions except for being served in at the window, happen instantly.

## 说明/提示

In the first test 5 people come simultaneously at the moment of time equal to 1. There is one window of every type, it takes 1 unit of time to be served at each window. That's why the maximal time a person spends in the embassy is the time needed to be served at the windows (3 units of time) plus the time the last person who comes to the first window waits (4 units of time).

 Windows in the second test work like this:

The first window of the first type: $ [1,6) $ — the first person, $ [6,11) $ — third person, $ [11,16) $ — fifth person

The second window of the first type: $ [2,7) $ — the second person,  $ [7,12) $  — the fourth person

The only second type window: $ [6,7) $ — first, $ [7,8) $ — second, $ [11,12) $ — third, $ [12,13) $ — fourth, $ [16,17) $ — fifth

The only third type window: $ [7,8) $ — first, $ [8,9) $ — second, $ [12,13) $ — third, $ [13,14) $ — fourth, $ [17,18) $ — fifth

We can see that it takes most time to serve the fifth person.

## 样例 #1

### 输入

```
1 1 1
1 1 1
5
1 1 1 1 1
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 1 1
5 1 1
5
1 2 3 3 5
```

### 输出

```
13
```

# 题解

## 作者：X_SpiderMan (赞：4)

## 思路：
  
本题好像用不到算法，要是硬要说算法，倒是有一点点的贪心。

---

每来一个人，窗口有空就进去；否则等待窗口变空后进去。

我们算出当前完成的最优时间，当前完成的最优时间最优时间与开始时间相减，就可以得到每次的停留时间 $(t-x)$。而最后的答案就是 $ \max ((t-x)_1...(t-x)_n)$。

## Code:

```cpp:
#include<bits/stdc++.h>
using namespace std;
long long a[5][100005],n,x,t,mx=-1e9,a1[5],a2[5];
int main(){
	cin>>a1[1]>>a1[2]>>a1[3]>>a2[1]>>a2[2]>>a2[3]>>n;
	for(int i=1;i<=n;i++){
		cin>>x; t=x;
		for(int j=1;j<=3;j++){
		    if(a[j][i%a1[j]]>t) a[j][i%a1[j]]=a2[j]+a[j][i%a1[j]];
	    	else a[j][i%a1[j]]=a2[j]+t;
	    	t=a[j][i%a1[j]];
		}
		mx=max(mx,t-x);
	}
	cout<<mx;
	return 0;
}

---

## 作者：N_z_ (赞：3)

## 思路
对于一个新来的人，如果窗口空着就去，否则就等到窗口空了再去。

我们可以算出完成后是什么时候，与开始时间相减，就可以得到停留时间。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k[4],t[4],a[4][100001];
signed main(){
	int n;
	cin>>k[1]>>k[2]>>k[3]>>t[1]>>t[2]>>t[3]>>n;
	int ans=0;
	for(int x=1;x<=n;x++){
		int y,z;
		cin>>y;
		z=y;
		for(int o=1;o<=3;o++)
		a[o][x%k[o]]=max(a[o][x%k[o]],z)+t[o],z=a[o][x%k[o]];
		ans=max(ans,z-y);
	}
	cout<<ans<<endl;
}
```

---

## 作者：sun_qy (赞：2)

# CF85B Embassy Queue 题解
[原题](https://www.luogu.com.cn/problem/CF85B)

## 题意简述

三个固定的窗口，有 $n$ 个人分别在 $c _ {i}$ 的时刻来。一个窗口在同一个时间只能处理一个人的事情，且每个人处理事情的时间也是固定的。求最优分配情况下停留时间最长的人的最短停留时间。

## 思路


对于每一个窗口，我们可以用一个小根堆来维护每个人来的时刻的单调性，这样三个窗口的处理方式将会出奇的一致。

然后用打擂台的方式就能求出答案。

## 解释

#### Step 1: 

首先初始化，往堆里塞入恰好足够的 $0$，便于处理时直接比较时间，省去判断队列是否为空等的麻烦。

```cpp
for(int x = 1; x <= 3; x ++) {
	for(int i = 1; i <= min(n, k[x]); i ++) {
		q[x].push(0ll);
	}
}

```
#### Step 2:
对于 $n$ 个人中的每一个人，读入 $c$ 之后一个一个队列地放入，通过不断更新最小时刻寻找最优解。

```cpp
cin >> c;
top = c;
for(int x = 1; x <= 3; x ++) {
	tmp = q[x].top();
	q[x].pop();
	tmp = max(top, tmp);
	top = tmp + t[x];
	q[x].push(top);
}
```
#### Step 3:
已经求出了最小值，打擂台寻找最大时刻即可。注意这里堆中存放的是完成时刻，若要求解停留时间需要减去对应初始时间 $c _ {i} $。

```cpp
ans = max(top - c, ans);
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
priority_queue <int, vector <int>, greater <int> > q[4];
int n, k[4], t[4], ans = -114514;
inline void input() {
	ios :: sync_with_stdio(0), cin.tie(0);
	for(int i = 1; i <= 3; i ++) cin >> k[i];
	for(int i = 1; i <= 3; i ++) cin >> t[i];
	cin >> n;
}
inline void init() {
	for(int x = 1; x <= 3; x ++) {
		for(int i = 1; i <= min(n, k[x]); i ++) {
			q[x].push(0ll);
		}
	}
}
inline void solve() {
	int c, tmp, top;
	for(int i = 1; i <= n; i ++) {
		cin >> c;
		top = c;
		for(int x = 1; x <= 3; x ++) {
			tmp = q[x].top();
			q[x].pop();
			tmp = max(top, tmp);
			top = tmp + t[x];
			q[x].push(top);
		}
		ans = max(top - c, ans);
	}
	printf("%lld\n", ans);
}
signed main() {
	input();
	init();
	solve();
	return 0;
}
```

---

## 作者：EntimE (赞：1)

## 思路
对于新来的人，只要有空的窗口就去。

按照这个思路，我们算出当前完成的最优时间，当前完成的最优时间最优时间与开始时间相减，就可以得到每次的停留时间 $ \left ( t- x \right ) $，然后最终的答案就是所有 $ \left ( t- x \right ) $ 的最大值。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,s,k[4],t[4],a[4][100001];
int main()
{
	cin>>k[1]>>k[2]>>k[3]>>t[1]>>t[2]>>t[3]>>n;
	for(long long i=1;i<=n;i++)
	{
		long long b,c;
		cin>>b;
		c=b;
		for(long long j=1;j<=3;j++)
		{ 
		    a[j][i%k[j]]=max(a[j][i%k[j]],c)+t[j];
		    c=a[j][i%k[j]];
		}
		s=max(s,c-b);
	}
	cout<<s;
}

```


---

## 作者：yhx0322 (赞：1)

## 题目简述
有 $n$ 个人分别在 $c_i$ 的时刻来，他们都要在 $k_1$，$k_2$ 和 $k_3$ 窗口干不同的事，当有后面一人也排在在同一窗口时，必须等待前面的人办完事才能轮到他。

问怎么在最优分配情况下，使停留时间最长的人停留时间最短。
## 思路
这道题的话，涉及到的算法为：贪心。
### 贪心策略：
设当前时刻来的人为 $x$，如果发现 $k_1$，$k_2$ 和 $k_3$ 其中有一个窗口空了，就进到空窗口。

否则等待窗口空了之后再进去。
### 计算最优时间

我们可以算出当前最优时间，与开始时间相减，**就可以得到停留时间**。

设开始时间为 $st$，当前最优时间为 $x$，则停留时间为 $(st - x)$。

最终的答案为：$\max((st-x)_1,(st-x)_2\dots(st-x)_n)$。

## 代码
```c++
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 10, M = 100010;
ll k[N],t[N],a[N][M];

int main(){
	ll n;
	for (int i = 1; i <= 3; i++)
    	scanf("%lld", &k[i]);
    for (int i = 1; i <= 3; i++)
    	scanf("%lld", &t[i]);
    scanf("%lld", &n);
	ll ans = 0;
	for(ll x = 1; x <= n; x++){
		ll y,z;
		scanf("%lld", &y);
		z=y;
		for(ll e = 1; e <= 3; e++)
		a[e][x % k[e]] = max(a[e][x % k[e]], z) + t[e], z = a[e][x % k[e]];
		ans = max(ans, z - y);
	}
	printf("%lld", ans); 
    return 0;
}
```

---

## 作者：cloud2764scallop_eve (赞：0)

好久没水题解了，来水一道。

题目传送门：[Luogu](https://www.luogu.com.cn/problem/CF85B) && [Codeforces](https://codeforces.com/problemset/problem/85/B)

## 题意

有 $n$ 个人在 $c_i$ 个时刻来办事，共 $3$ 个窗口，每个人到每个窗口办事分别需要不同的事件，每个窗口只能同时处理一个人，问在最优安排下，办事时间最长的人最少需要多少时间。（实际上翻译说得已经很清楚了）

## 思路

一眼贪心。

对于每个新来的人而言，如果有空的窗口就直接选择这个窗口；如果没有，就等有空窗口时再进入。

用当前最有时间减去开始时间，即为停留时间。

## 代码

注意要开 `long long`。

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 100005
using namespace std;
namespace cyxyc {
	int n, ans, c, rem;
	int k[10], t[10], a[10][maxn];
	void solve() {
		ios::sync_with_stdio();
		cin.tie(0);
		for (int i = 1; i <= 3; i++) cin >> k[i];
		for (int i = 1; i <= 3; i++) cin >> t[i];
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> c;
			rem = c;
			for (int j = 1; j <= 3; j++) {
				a[j][i % k[j]] = t[j] + max(a[j][i % k[j]], rem);
				rem = a[j][i % k[j]];
			}
			ans = max(ans, rem - c);
		}
		cout << ans << '\n';
	}
}
signed main() {
	cyxyc::solve();
	return 0;
}
```


---

## 作者：Kano_zyc (赞：0)

## 题意简述

模拟大使馆中的三个窗口服务过程，最小化人们在大使馆的最长停留时间。每个人需要按顺序完成三个任务，每个窗口处理任务的时间是固定的。

## 思路分析

使用优先队列模拟窗口的工作过程，每次选择最早结束的窗口进行服务。记录每个人的停留时间，最后输出最长的停留时间即可。

## AC code


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
ll a[N],b[N],k[4],t[4],n;
priority_queue<ll,vector<ll>,greater<ll> > q[4];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for(int i=1;i<=3;i++) cin>>k[i];
    for(int i=1;i<=3;i++) cin>>t[i];
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        b[i]=a[i];
        for(int j=1;j<=3;j++){
            while(!q[j].empty()&&q[j].top()<b[i]) q[j].pop();
            if(q[j].size()<k[j]) q[j].push(b[i]+t[j]);
            else{
                b[i]=max(b[i],q[j].top());
                q[j].pop();
                q[j].push(b[i]+t[j]);
            }
        }
    }
    sort(b+1,b+n+1);
    cout<<b[n]+t[1]+t[2]+t[3]-a[n]<<'\n';
    return 0;
}
```

---

## 作者：xudiyao (赞：0)

# 洛谷CF85B题解
[题目传送门](https://www.luogu.com.cn/problem/CF85B)

## 题目大意

有 $n$ 个人在 $c[i]$ 的时刻来干事，他们都要在 $k[1]\sim k[3]$ 窗口干事，并且在同一窗口时，必须等前面的人办完事才能轮到下一个。当某个人做完了事后就会离开。

给定 $k[1]\sim k[3]$ 窗口的数量以及一个人到某窗口干的事的时间 $t[1]\sim t[3]$，问在最优分配情况下，停留时间最长的人停留时间是多少。

## 思路引导

对于每一个人，先不把他放到某一个窗口，而是根据先后顺序，当某一个窗口空着了再去。

我们可以算出当前最快完成是什么时候，与开始时间相减，就可以得到停留时间，再用变量不断更新最大值。

## AC代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long a[10][100010],f1[10],f2[10];
int main()
{
	long long n,x,t,maxx=-1;
	cin>>f1[1]>>f1[2]>>f1[3]>>f2[1]>>f2[2]>>f2[3]>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>x;//开始时间 。 
		t=x;
		for(long long j=1;j<=3;j++)
		{
			if(a[j][i%f1[j]]>t) a[j][i%f1[j]]=f2[j]+a[j][i%f1[j]];//没空位。 
			else a[j][i%f1[j]]=f2[j]+t;//有空位 。 
			t=a[j][i%f1[j]];//结束时间 。 
		}
		maxx=max(maxx,t-x);//更新最大值 。 
	}
	cout<<maxx;
}//AC撒花。 
//禁止抄题解！。
//不开longlong见祖宗（呜呜呜，前面WA了）。 
~~~

---

## 作者：FarmarJohn (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF85B)
### 分析
首先，这道题是求最短时间，而众所周知，只要一看到求最值，第一时间想到的只能是贪心或动态规划。所以这道题考虑使用贪心。

那怎么**贪**呢？

对于每一个新来的人来说，要想最快处理完所有事务，肯定是一有空窗口便去该空窗口。

按照该思路，我们可以计算出当前的最优时间，再将其与开始时间相减。而答案便是所有最优时间与开始时间相减的差的最大值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,x,y;
long long k[10],t[10],a[10][100001];//别忘了开long long
inline long long max(long long a,long long b)
{
	return (a > b) ? a : b;
}
int main()
{
	for(int i=1;i<=3;++i)cin >> k[i];
	for(int i=1;i<=3;++i)cin >> t[i];
	cin >> n;
	for(long long i=1;i<=n;++i)
	{
		cin >> x;
		y=x;
		for(long long j=1;j<=3;++j)
		{
		    a[j][i%k[j]]=t[j]+max(a[j][i%k[j]],y);
		    y=a[j][i%k[j]];
		}
		ans=max(ans,y-x);
	}
	cout << ans << endl;
	return 0;
}
```

---

