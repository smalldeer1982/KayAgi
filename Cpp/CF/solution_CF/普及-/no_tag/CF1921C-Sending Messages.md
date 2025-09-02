# Sending Messages

## 题目描述

Stepan是一个busy的人。今天，他需要在 $m_1,m_2,\dots m_n$ 时刻发送 $n$ 条信息。很惨的是，到 $0$ 时刻，他的手机只剩 $f$ 个单位电量。此时手机已开机。

手机每开机一时刻就会损失 $a$ 个单位电量。此外，Stepan可以随时关闭手机，稍后再开机，每次共消耗 $b$ 个单位的能量。开关机不花费任何时间，这样就可以在 $x$ 时刻打开它，同时发送信息，反之，在 $x$ 时刻发送信息同时关闭手机也是可以的。

如果在任何时候电量降至 $0$ 以下，则手机自动关机，无法发送消息。Stepan想知道是否可以在不给手机充电的情况下发送所有信息。

## 样例 #1

### 输入

```
6
1 3 1 5
3
7 21 1 3
4 6 10 13 17 20 26
5 10 1 2
1 2 3 4 5
1 1000000000 1000000000 1000000000
1000000000
3 11 9 6
6 8 10
12 621526648 2585904 3566299
51789 61859 71998 73401 247675 298086 606959 663464 735972 806043 806459 919683```

### 输出

```
NO
YES
YES
NO
NO
YES```

# 题解

## 作者：tbdsh (赞：1)

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/CF1921C)

[CodeForces 原题面](http://codeforces.com/problemset/problem/1921/C)

你有一部手机，初始电量为 $f$。在 $n$ 个时刻 $m_1,m_2,\dots,m_n$，你必须保证手机是开机的。手机开机 $1$ 个单位时间会消耗 $a$ 点电量。你也可以在一瞬间开机然后关机，消耗电量 $b$。

在时刻 $0$ 时，手机为开机状态。

请问能否保证 $n$ 个时刻手机电量 $f>0$。能输出 `YES`，否则输出 `NO`。

有 $t$ 组数据。

# 分析

注意到在每个时刻期间，你要么一直开机，要么等到要开机的时候再瞬时开机并关机。令 $m_0=0$，那么第 $i$ 操作的最少耗费电量为 $\min((m_i-m_{i-1})\times a, b)$。累加起来判断是否小于 $f$ 即可。

时间复杂度：$O(n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, f, a, b, m[MAXN];
void Solve(){
  cin >> n >> f >> a >> b;
  m[0] = 0;
  for (int i = 1; i <= n; i++){
    cin >> m[i];
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++){
    cnt += min((m[i] - m[i - 1]) * a, b);
  }
  cout << (cnt < f ? "YES\n" : "NO\n");
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：飘然归隐 (赞：1)

我们可以分段来考虑，在相邻时间点，要么就是不关机等着到下个时间点，要么关机开机。所以只要每次找这两种方式里耗电少的就行。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		ll n,f,a,b;
		ll temp=0;
		cin>>n>>f>>a>>b;
		ll l=0,r=0;
		for(ll i=0;i<n;i++)
		{
			
			cin>>r;
			
			temp+=min((r-l)*a,b);//r-l是这段时间间隔
			l=r;
		}
		
		if(temp<f)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
 } 
```


---

## 作者：Eternity_Yoke (赞：1)

## 题目大意
初始有 $f$ 格电，待机 $1$ 单位时间消耗 $a$ 格电，关机再开机需要 $b$ 格电。

现在有 $n$ 条消息，分别要在 $m_i$ 时刻发出。

问是否能将所有消息发出。
## 解题思路
考虑贪心。

比较待机所消耗的电量和关开机消耗的电量，哪个方式消耗得少就选。

注意如果 $m_i$ 时刻时恰好电为 $0$ 则无法发出消息。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int t,n,f,a,b,d,bj;
int m[N];
int main()
{	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{	cin>>n>>f>>a>>b;
		for(int i=1;i<=n;i++)
		cin>>m[i];
		bj=0;
		for(int i=1;i<=n;i++)
		{	d=m[i]-m[i-1];
			if(1ll*d*a<=b)f-=d*a;//注意爆int
			else f-=b;
			if(f<=0)//只要在循环里f小于等于0则无法发送完消息
			{	bj=1;
				break;
			}
		}
		if(bj==1)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：1)

### 题目大意

有一个人的手机还剩 $f$ 格电，他的手机开机一个单位时间会用掉 $a$ 格电，关机在开机则需要用掉 $b$ 格电，现在这个人要发送 $N$ 条消息，每条消息在 $a_i$ 时刻发出，问他能不能在不给手机充电的情况下发完这 $N$ 条消息。

### 思路

这道题就是一个贪心，看我当前两个时间点之间是一直开机用掉的电少还是，关机在开机用的电少就可以了。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define ll long long
#define ex exit(0)
#define _endl_ puts("");
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
ll s[200005];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll n, f, a, b;
		cin >> n >> f >> a >> b;
		for (int i = 1; i <= n; i++) {
			cin >> s[i];
		}
		for (int i = 1; i <= n; i++) {
			ll cnt = s[i] - s[i - 1];
			if (cnt * a < b) {
				f -= cnt * a;
			} else {
				f -= b;
			}
		}
		if (f <= 0) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
	return 0;
}
~~~

---

## 作者：tallnut (赞：0)

DP 题。
# 思路
设 $f_i$ 为打完第 $i$ 个电话后最少需要的电量。

此时有两种方案：
- 在上一次结束后立刻关机，需要多耗费 $b$ 点电量。
- 上一次结束后不关机，则有 $x_i-x_{i-1}$ 这么长的时间处于挂机状态。多耗费 $(x_i-x_{i-1})\times a$ 点电量。

于是得到方程：
$$f_i=\min(f_{i-1}+b,f_{i-1}+(x_i-x_{i-1})\times a)$$
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/143362507)。
```
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
int t,n,f,a,b;
long long x[N],f1[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> f >> a >> b;
		for (int i = 1;i <= n;i++)
			cin >> x[i];
		for (int i = 1;i <= n;i++)
			f1[i] = min(f1[i - 1] + (x[i] - x[i - 1]) * a,f1[i - 1] + b);
		if (f1[n] >= f) cout << "NO\n";
		else cout << "YES\n";
	}
}
```

---

## 作者：Vct14 (赞：0)

贪心每次发消息前关机是否更优，找到最优的情况。如果此时还无法发送所有消息的话输出 `NO`。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--){
		long long n,f,a,b;
		cin>>n>>f>>a>>b;
		long long t=0;bool ok=true;
		for(int i=0; i<n; i++){
			long long m;
			cin>>m;
			if(a*(m-t)>b) f-=b;
			else f-=a*(m-t);
			t=m;
		}
		if(ok) puts("YES");
		else puts("NO");
	} 
	return 0;
}

```

---

## 作者：kczw (赞：0)

# 题意简述
着乐有一部芒果手机，他需要在 $n$ 个时刻 $(m_1,m_2,m_3...m_n(m_i<m_{i+1}))$ 发送信息。在时刻 $0$ 时，他的手机开机并且电量为 $f$，开机时每一时刻消耗 $a$ 的电量，每次关机消耗 $b$ 的电量。如果手机电量为 $0$ 则无法发送信息。

共 $t$ 组数据，每组数据给定 $n,f,a,b$ 和 $m$ 序列，问能否发送完 $n$ 条消息。
# 思路
每次要发消息贪心地看在从上次发消息到现在的时间是选择关机再开机更优还是保持开机更优。如果在最优策略下发完所有消息之前电量小于等于 $0$ 了，就输出 `NO`，否则输出 `YES`。

因为 $\sum n\le2\times10^5$，所以效率上能过。
# 代码
```cpp

#include<iostream>
using namespace std;
const int N=2e5+5;
long long t,n,f,a,b,m;
int main(){
    scanf("%lld",&t);
    while(t--){
        long long now=0,k=1;
        scanf("%lld%lld%lld%lld",&n,&f,&a,&b);
        for(int i=1;i<=n;i++){
            scanf("%lld",&m);
            f-=min(b,a*(m-now));
            if(f<=0)k=0;
            now=m;
        }
        printf(k?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：ThySecret (赞：0)

## 解题思路

很显然的贪心题，只需要判断每一个路程耗电量的大小进行选择即可，但是这道题同样可以用 DP 做（其实思路是一样的）。

我们定义一个数组 $dp$ 表示到第 $w_i$ 时候所耗费的最小电量，由于 $dp_i$ 只可以通过 $dp_{i - 1}$ 转移而来，并且分为两种情况：一直打开或者先关机后打开。可以得到：
$$
dp_i = \min(dp_i - 1 + (w_i - w_{i - 1}) \times a, dp_{i - 1} + b)
$$
这时候便可以愉快的写代码了。

## AC Code

```c++
// Problem: C. Sending Messages
// Contest: Codeforces - Codeforces Round 920 (Div. 3)
// URL: https://codeforces.com/contest/1921/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;

int w[N], dp[N];	// 第 i 个表示在w[i]时刻所用的电量的最小值

void solve()
{
	memset(dp, 0x3f, sizeof dp);
	int n, f, a, b; cin >> n >> f >> a >> b;
	for (int i = 1; i <= n; i ++) cin >> w[i];
	for (int i = 1; i <= n; i ++)
		dp[i] = min(dp[i - 1] + b, dp[i - 1] + a * (w[i] - w[i - 1]));
	if (dp[n] >= f) cout << "NO\n";
	else cout << "YES\n";
}

signed main()
{
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T --) solve();
	return 0;
}
```

---

