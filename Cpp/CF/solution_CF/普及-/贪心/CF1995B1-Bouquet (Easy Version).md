# Bouquet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, the flowers are specified by enumeration.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ flowers in the store, each of which is characterized by the number of petals, and a flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use in her bouquet should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, you can assemble a bouquet with $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the third test case, you can assemble a bouquet with only one flower of any type, so the answer is $ 610 $ . In the fourth test case, you can assemble a bouquet with $ (4, 4, 5) $ , which gives you $ 13 $ petals, and it is the maximum amount of petals that the girl can buy.

## 样例 #1

### 输入

```
5
5 10
1 1 2 2 3
8 20
4 2 7 5 6 1 1 1
8 100000
239 30 610 122 24 40 8 2
11 13
2 4 11 1 1 2 3 5 4 3 2
8 1033
206 206 206 207 207 207 207 1000```

### 输出

```
7
13
610
13
1033```

# 题解

## 作者：NEKO_Daze (赞：5)

[洛谷CF1995B1](https://www.luogu.com.cn/problem/CF1995B1) || [CodeForces 1995 B1](https://codeforces.com/contest/1995/problem/B1)

### 简要题意

> 原题意有点难表述，所以改了一下内容。

给出一个长度为 n 的序列 $a_1,a_2,\dots,a_n$，第 $i$ 个元素的大小为 $k$。现有一个容量为 $m$ 的背包，可以选定序列中大小之差不超过 $1$ 的两项放入背包。同时，希望背包中元素的数量尽可能多。能放入背包的元素总数最多是多少？

### 思路

一道双指针板子题，滑动窗口大法好。

定义两个表示窗口头尾的指针 $i,j$，初始化在序列左侧，然后移动右端点 $j$ 直至窗口内的元素不符合题目要求（即背包装满或不满足 $a_i-a_j\le 1$），再逐步右移左指针 $i$ 缩小窗口，直至窗口内元素符合题目要求，最后更新 $ans$ 的值即可。

[AC记录](https://codeforces.com/contest/1995/submission/272674365)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200001];
int main(){
	int t;cin>>t;
	while(t--){
		ll n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		ll ans=0,i=0,j=1,x=0;
		while(i<n){
			i++;
			x+=a[i];
			while(x>m||a[i]-a[j]>1) x-=a[j],j++;
			ans=max(ans,x);
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：__little__Cabbage__ (赞：4)

## Solution

首先按照花瓣数给所有花瓣分类，把花瓣数相同的设为同一种花，设第 $i$ 种花共有 $k_i$ 朵，每朵的花瓣数为 $v_i$。

因为选择的相邻两个种类的花的花瓣数之差 $\le 1$，所以只能选择 $1$ 种或 $2$ 种花，我们可以分讨一下。

对于只选 $1$ 种的情况，很显然选的个数越多越好，所以直接计算最多可以选几个，答案为 $\min( \frac{m}{v_i} ,k_i) \times v_i$。

对于选择 $2$ 种的情况，我们采取一个贪心的策略，考虑枚举一种花可以取的个数（设为 $c$），那么问题就转化为了有 $m - c \times v_i$ 枚金币，选第 $j$ 种花，最多可以选几个，我们会发现这个就是只选 $1$ 种的情况呀，所以按照只选 $1$ 种的情况做即可。

但是问题来了，我们如何保证选 $2$ 种花的复杂度正确呢？首先我们可以想到，如果要选 $2$ 种花，它们在按照花瓣数**排序后**的数组中一定是相邻的，所以对于每个 $v_i$ 只需要考虑 $v_{i-1}$ 和 $v_{i+1}$ 即可。又因为 $\sum k_i = n$，所以所有枚举 $c$ 的过程加起来是 $O(n)$ 的。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n,m,a[MAXN];
il int sol(int k1,int k2,int v1,int v2)
{
	int ans=0;
	for(int i=0;i<=k1 && i*v1<=m;++i)
		ans=max(ans,i*v1+min((m-i*v1)/v2,k2)*v2);
	swap(k1,k2),swap(v1,v2);
	for(int i=0;i<=k1 && i*v1<=m;++i)
		ans=max(ans,i*v1+min((m-i*v1)/v2,k2)*v2);
	return ans;
}
il void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1);
	int ans=0;
	int cnt=1,last=-1,now=a[1],lnow=-1;
	a[n+1]=52013140000ll; //如果直接放5201314的话是可以特意构造数据hack掉的qwq
	for(int i=2;i<=n+1;++i)
	{
		if(a[i]==now) ++cnt;
		else
		{
			ans=max(ans,min(m/a[i-1],cnt)*a[i-1]);
			if(last==-1 || now-lnow>1)
			{
				last=cnt,cnt=1,lnow=now,now=a[i];
				continue;
			}
			ans=max(ans,sol(last,cnt,lnow,now));
			last=cnt,cnt=1,lnow=now,now=a[i];
		}
	}
	cout<<ans<<'\n';
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}

```

---

## 作者：Special_Tony (赞：2)

# 思路
把所有花按照花瓣数排序，然后使用双指针，右端不断右移直到花瓣数过多（$a_r-a_l>1$）或买不起（$\sum\limits_{i=l}^r a_i>m$），然后取 $\max$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[200005], r;
ll sum, maxx, m;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m, maxx = sum = r = 0;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		sort (a, a + n);
		for (int i = 0; i < n; ++ i) {
			while (r < n && a[r] <= a[i] + 1 && sum + a[r] <= m)
				sum += a[r], ++ r;
			maxx = max (maxx, sum);
			sum -= a[i];
		}
		cout << maxx << '\n';
	}
	I AK IOI
}
```

---

## 作者：vorDeal (赞：1)

~~忘注册，10 min 耽误了。~~

首先观察到一个独特的条件：花瓣的瓣数之差不超过一。这提示我们，问题具有单调性。那如何使它具有单调性呢？

排序。

排序后，我们得到一个不降序列，又有极差和总和的限制。由于，此时购买的花，必须是一段连续的区间，所以考虑使用双指针算法。

当极差或总和过大，右移区间左端点，否则呢，更新答案，并右移区间右端点。

然后就做完了。时间复杂度为 $O(n \log n)$，瓶颈在排序。实现不难，三十行左右。

数据千万条，清空第一条。多测不清空，爆零两行泪。

**AC Code：**
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, l, r;
long long m, a[200005], res, sum;

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    l = r = res = sum = 0;
    while (r <= n)
    {
        if (a[r - 1] > a[l] + 1 || sum > m)
            sum -= a[l], l++;
        else
            res = max(res, sum), sum += a[r], r++;
    }
    cout << res << endl;
    return;
}

int main()
{
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](http://codeforces.com/problemset/problem/1995/B1)

### 题意
有 $n$ 朵花，一朵 $k$ 个花瓣的花要 $k$ 元钱，找出一种方案，使得在花费 $m$ 元内且花瓣数量最多的同时，相邻两朵花的花瓣数量差不超过 $1$。

### 思路
我们可以使用一个队列来维护这些元素。每次将元素与队头作比较，如果钱不够买下这些花朵，或者花瓣间的差值不符合条件，也就是说差值 $\gt 1$了，便出队。否则加入队列，并修改钱数以及答案，更新最大值。

到最后，最大值便为我们要的答案。

这样就可以保证在有限条件内得到最优方案了。

代码如下：
### 代码实现

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#define ll long long // 习惯了
#define MAXN 200008
using namespace std;

queue<ll> q;

ll a[MAXN];
ll t, n, m;
ll u;
ll maxn, sum;

void Clear()
{
    while (!q.empty())
        q.pop();
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        maxn = -114514, sum = 0; 

        cin >> n >> m;

        for (ll i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + 1 + n);  

        for (ll i = 1; i <= n; i++)
        {
            while (!q.empty() && (m < a[i] || a[i] - q.front() >= 2)) // 排除不符合条件的花朵
            { 
                m += q.front();
                q.pop();
                sum -= q.front();
            }

            if (m < a[i]) // 买不起
                break;
            
            q.push(a[i]); // 买得起
            m -= a[i];         
            sum += a[i];           
            maxn = max(maxn, sum); 
        }
        Clear();
        cout << maxn << '\n'; 
    }
    return 0;
}

```

---

## 作者：foryou_ (赞：0)

由题可知任意两片花瓣之差不超过一，因此所选的花要么有一种花瓣数，要么有两种花瓣数。

对于有一种的情况，考虑贪心，在价格允许的前提下尽可能多买即可。

对于有两种的情况，枚举其中一种买多少，这样就拆分为了两个情况一，依然如此贪心即可。

设每种花瓣数有 $k_i$ 个，因为 $\sum k_i=n$，所以总时间复杂度为 $\mathcal{O}(n)$。

[code](https://codeforces.com/contest/1995/submission/272715559)。

---

## 作者：tzzl3035 (赞：0)

# CF1995B1 题解
### 题目大意
有 $t$ 组数据，每组给出两个正整数 $n$ 和 $m$。接下来有 $n$ 朵花，每朵有 $a_i$ 个花瓣。购买花的花瓣总数不能超过 $m$，且购买的花瓣最多的花和花瓣最少的花的花瓣数量差不能超过 $1$。问购买的花最多共有几个花瓣。
### 思路
我们可以将花瓣数排序后设置购买花瓣的左端点和右端点，每次将右端点增加 $1$，然后根据限制条件增加左端点，最后更新答案即可。
### 核心代码
```cpp
  // 输入
  int n;
  llint m;
  std::cin >> n >> m;
  std::vector<llint> flow(n);
  for(int i = 0; i < n; ++i) 
    std::cin >> flow[i];
  std::sort(flow.begin(), flow.end()); // 排序
  // 寻找答案
  llint answ = 0, osum = 0;
  int l=0, r=0;
  while(l <= r && r < n) {
    osum += flow[r]; //更新花瓣总和
    // 处理左端点
    while(l <= r && (flow[r] - flow[l] > 1 || osum > m)) 
      osum -= flow[l++];
    // 更新答案
    if(l <= r && osum <= m && flow[r] - flow[l] <= 1)
      answ = std::max(answ, osum);
    r += 1; // 增加右端点
  }
  std::cout << answ << '\n'; // 输出
```
（注：`llint` 指 `long long`）
### [RESULT](https://www.luogu.com.cn/record/168656790)

---

## 作者：YuYuanPQ (赞：0)

这道题一眼很可做。

先用 `map` 存下每个数出现的次数，即：$c_i$ 表示 $i$ 出现的次数。

我们枚举 $i$，考虑对于每个 $a_i$ 和 $a_i-1$（可能不存在），用最优策略组合这 $2$ 个数。

定义 $k=a_i$，$q=a_i-1$。

显然，$k$ 的个数 $kgs$ 可以取到 $\min(c_k,\frac{m}{k})$。

此时剩下 $sy=m-kgs\times k$ 个金币，显然，$q$ 的个数 $qgs$ 可以取到 $\min(c_q,\frac{sy}{q})$。

我们愉快地算出花瓣的总数 $zs=kgs\times k+qgs\times q$。

然后发现没过样例......

观察发现，最后 $1$ 个数据没过。原因是选择了 $4$ 个 $207$ 之后不能再选其他的数了，程序认为 $1$ 个 $1000$ 最优。但是其实 $2$ 个 $206$ 和 $3$ 个 $207$ 才是最优。

那么我们考虑做完上面的步骤之后微调一下。

也就是：尝试着先减去 $1$ 个 $k$，即：`zs-=k`。然后算出剩下的 $sy2=m-zs$ 个金币，再选择加上 $\min(c_q,\frac{sy2}{q})$ 个 $q$。终止条件是：如果这个新的总金币数 $zs$ 不比上次的总金币数 $lst$ 更大，那么接下来是更劣解，就不用再继续了。

一定要记得都取 $\min$，否则你会像我一样失败。（$3$ 发罚时可不好玩儿呢~）

不得不说，我赛时的做法真的挺复杂的。

代码很丑，见谅。

## Code

[Link](https://codeforces.com/contest/1995/submission/272160154)

---

## 作者：_dbq_ (赞：0)

## 前言
没有读题的同学们可以点击[这里](https://www.luogu.com.cn/problem/CF1995B1)先读题。

## 题目大意
在序列中选取若干数，其中最大值与最小值之差不大于 1，求这些数之和的最大值。

## 思路
对于此题可以使用模拟，由于最大值与最小值之差不大于 1，可以对原数组进行排序后使用双指针模拟即可。

我们使用一个 $l$ 和一个 $r$ 分别指出我们所选区间的左右端点，由于要使区间和尽可能大，所以在 $l$ 不变的情况下使 $r$ 更大。区间的最大值与最小值之差不大于 1，且区间之和也要不大于 $m$，可以得到 $r$ 需要满足的条件是：$a_r-a_l \le 1$ 且 $\sum_{i=l}^r a_i \le m$，此时更新 $ans$。更新后，我们使 `l++`，继续进行下一次判断。

## 优化
我们在模拟的时候需要计算 $\sum_{i=l}^r a_i \le m$，自然想到前缀和优化，在排序之后求出前缀和。

我们定义 $S_i=\sum_{i=1}^i a_i$，则 $\sum_{i=l}^r a_i \le m$ 可以转化为 $S_r-S_{l-1} \le m$。

## 代码

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
cint N=2e5+10;
int a[N];
LL s[N];//前缀和
LL ans;//记录最大值
inline LL read(){//快读
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(LL x){//快写
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return ;
}
int main()
{
    #ifdef dbq
    freopen("CF1995B1.in","r",stdin);
    freopen("CF1995B1.out","w",stdout);
    #endif
    int T=read();
    while(T--)
    {
        cint n=read();
        LL m=read();
        int mx=-1;
        for(int i=1;i<=n;i++)
            a[i]=read();
        sort(a+1,a+1+n);//排序
        s[0]=0;
        for(int i=1;i<=n;i++)
            s[i]=s[i-1]+a[i];//求前缀和
        ans=0;//注意清空
        int l=1,r=1;//设初值
        while(l<=r&&r<=n)
        {
            while(r<=n&&s[r]-s[l-1]<=m&&a[r]-a[l]<=1) r++;
            //r<=n防止出界
            //s[r]-s[l-1]<=m判断能否购买
            //a[r]-a[l]<=1由于排序，最大值与最小值之差就是a[r]-a[l]
            ans=max(ans,s[r-1]-s[l-1]);//更新答案
            l++;
        }
        write(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
本题代码十分精悍，只有二十行。

首先将输入的 $a$ 数组排序，不然在接下来的过程中我们很难比较花瓣数的差异。

接下来用双指针 $l$ 和 $r$ 表示滑动窗口的左右边界。用 $i$ 来表示当前枚举到第几朵花，设 $l = 1,r = i$，如果 $a_r - a_l > 1$ 或者当前窗口的总和大于了 $m$（超出了预算），那么不断将 $l$ 加 $1$，缩小窗口范围，直到当前的窗口符合题目条件。

如果此时窗口的和小于 $m$，那么更新答案。

最后输出答案，本题多测。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define N 200005
int a[N],n,m,t;
signed main(){
	std::cin>>t;
	while(t--){
		std::cin>>n>>m;
		for(int i=1;i<=n;i++)std::cin>>a[i];
		std::sort(a+1,a+1+n);
		int maxn=0,cur=0;
		for(int l=1,r=1;r<=n;r++){
			cur+=a[r];
			while(a[r]-a[l]>1||cur>m)cur-=a[l++];
			if(cur<=m)maxn=std::max(maxn,cur);
		}
		std::cout<<maxn<<"\n";
	}
}
```

---

## 作者：yanlikun (赞：0)

# 题意
给有 $n$ 个物品、 $m$ 元，每个物品的价值和价格都为 $a_i$ ，同时，你所购买的物品的价值两两之间不能超过 $1$ 。求能获得的最大价值。
# 思路
~~这一题被我看成假背包 DP 了。~~
首先，我们先将价值为 $a_i$ 的物品的数量统计下来。再依次枚举价值为 $a_i$ 和 $a_i+1$ 的物品的数量，最后对总价值取 $\max$ 即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll a[200005],num[200005];
map<ll,ll> mp;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		int n,sum=1;
		ll m;
		cin>>n>>m;
		ll ans=0;
		memset(num,0,sizeof(num));//多测不清空，亲人两行泪
		mp.clear();
		for(int i=1;i<=n;i++)
			cin>>a[i],mp[a[i]]++;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			if(!num[sum]&&a[i]!=num[sum-1])
				num[sum++]=a[i];
		for(int i=1;i<sum;i++)
		{
			if(!mp[num[i]+1])
				ans=max(ans,min(mp[num[i]],m/num[i])*num[i]);
			for(int j=1;j<=mp[num[i]];j++)
			{
				if(num[i]*j<=m)
					ans=max(ans,num[i]*j+min(mp[num[i]+1],(m-num[i]*j)/(num[i]+1))*(num[i]+1));
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
一个女孩正在为她的生日买花。店里总共有 $n$ 种鲜花，一朵有 $k$ 个花瓣的花要花 $k$ 块钱。这个女孩将在花束中使用的任何两朵花之间的花瓣数量之差不超过一朵。同时，女孩想在花束里放更多的花瓣。但她只有 $m$ 块钱，问她可以在花束中可以放的最大花瓣数？

显然题目还没翻译，我来说说这个输入输出格式吧。

### 输入格式
第一行一个数字 $t$，代表 $t$ 组数据。

每一组数据中，第一行两个数 $n$ 和 $m$，题目中说了意思。第二行是这 $n$ 朵花的花瓣数，我们把他设成数组 $a$。
### 输出格式
每组一个整数 $ans$，由换行隔开，每一组的最大花瓣数。
## 大体思路
由于是 Easy Version，我们暴力考虑情况就行，定义一个队列 $q$，将花瓣的多少排序后一个一个的进队，如果超出了钱或花瓣数不只差 $1$ 了就出队，维护一下这个队列，算出队列里可能出现的最大花瓣数即可。

具体操作我们看代码，有详细注释。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
queue<int> q;
int main(){
	int t;
	cin>>t;
	while(t--){//t 组数据 
		long long n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}//我们输入花瓣
		sort(a+1,a+1+n);//正常 sort 
		long long maxx=0,sum=0;//maxx 是维护的答案，sum 是当前队里有的花瓣数 
		for(int i=1;i<=n;i++){
			while(!q.empty()&&(m-a[i]<0||a[i]-q.front()>1)){//前提是队列不为空，如果钱数在买了之后小于零了，或者队头（一定是队列里花瓣数最少的）比现在差两个及以上，就出队还钱 
				m+=q.front();
				sum-=q.front();
				q.pop();
			}
			if(m-a[i]<0){
				break ;//队空了还不够钱就不用考虑了（显然如果现在钱不够就是队空了，否则会继续出队的） 
			}
			m-=a[i];//这个花我买了 
			q.push(a[i]);//入队 
			sum+=a[i];//加花瓣数 
			maxx=max(maxx,sum);//维护答案 
		}
		cout<<maxx<<endl;//最后输出即可 
		while(!q.empty()){
			q.pop();
		}//清空队列 
	}
	return 0;
}
```

---

## 作者：Leeb (赞：0)

### 题意简述

给定 $n$，$m$ 和序列 $a_i$，$m$ 代表拥有的钱，$a_i$ 代表一朵花的价值，尽可能的多买花并且使得所买的任意两朵花的价值之差不超过 $1$。

### 解题思路

从第一朵花开始，一个指针 $p$ 指向买花的起始位置，$i$ 指向买花的终止位置，如果 $a_i-a_p\gt 1$ 则将 $p$ 一直往后移直到 $a_i-a_p\le 1$，移动过程中不断将买花的花费减去 $a_p$，最后取最大值即可。

可能讲的不是很清楚，看代码吧。

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 200005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, m, p, ans, now, sum, a[N];
inline int in() {
	int a = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = 1; ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
	if (f) return ~a + 1;
	return a;
}
inline void print(int x) {
	if (x < 0) putchar('-'), x = ~x + 1;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
	print(x);
	putchar(ch);
}
inline void init() {
	n = in(), m = in();
	for (int i = 0; i < n; ++i) a[i] = in();
	sort(a, a + n);
}
inline void work() {
	ans = now = sum = p = 0;
	for (int i = 0; i < n; ++i) {
		now += a[i], sum += a[i];
		while (now > m || (a[i] - a[p] > 1)) now -= a[p], sum -= a[p], p++;
		ans = max(ans, sum);
	}
	out(ans, endl);
}
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	int t = in();
	while (t--) {
		init();
		work();
	}
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路

记录下每个值出现的个数。对于没一个数，枚举它出现的个数，这个数加一出现的个数一定确定。

设这个数为 $a$ 出现的个数为 $k$，则 $a+1$ 出现的个数为 $\lfloor\frac{m-a\times k}{a+1}\rfloor$ 和 $a+1$ 出现个数的最小值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<int,ll>mp;//用mp记录a中每个元素出现的个数
ll a[200005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T,n,k;
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			mp[a[i]]++;//统计
		}
		sort(a+1,a+n+1);
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==a[i-1]+1)
			{
				ll c=mp[a[i-1]],d=mp[a[i]];
				for(int j=1;j<=c;j++)
				{
					if(a[i-1]*j>k)break;
					ans=max(ans,a[i-1]*j+a[i]*min(d,(k-a[i-1]*j)/a[i]));
				}
			}
			if(a[i]!=a[i-1])
				ans=max(ans,a[i]*min(mp[a[i]],k/a[i]));//这个数最多出现的个数，即a[i-1]个数为0的情况
		}
		cout<<ans<<'\n';
		mp.clear();//清空统计数组
	}
	return 0;
}
```

---

## 作者：ANDER_ (赞：0)

#### 考察：分类讨论、模拟、贪心。
## 题意
现在有 $m$ 元钱，$n$ 种花，第 $i$ 种花有 $a_i$ 个花瓣，$c_i$ 朵，买一朵需要 $a_i$ 元钱。构造一种买花方案，设 $w$ 为所买花的花瓣数集合，需要满足 $\sum w$ 最大，且 $\sum w \le m \bigwedge w_{max} - w_{min} \le 1 \equiv T$，输出 $\sum w$。

## 思路
根据题意，我们构造的买花方案只有两种情况：

1. 所买花的花瓣数都相同。
2. 所买花的花瓣数为 $s$ 或 $s + 1$。

首先讨论较为简单的情况一，不妨设所买的花为第 $i$ 种，共买 $q$ 朵，此时所花的钱数就为 $a_i \times q$。最大化 $a_i \times q$，可被转化为最大化 $\lfloor \frac{m}{a_i} \rfloor$。直接计算即可。

再来看情况二，不妨设所买花瓣数为 $s$ 的花有 $p$ 朵，$s + 1$ 的花有 $q$ 朵，当前方案 $w$ 的 $\sum w$ 为 $t$。我们可以贪心的选择花瓣数为 $s$ 的花。若花瓣数为 $s$ 的花已经买空，我们就继续选择花瓣数为 $s + 1$ 的花。若 $m - t < s$，显然可以考虑将花瓣数为 $s$ 的花替换为 $s + 1$，这样就可以使 $t$ 加一。按照上述逻辑，模拟即可。

先排序，后按照上述方法模拟即可得出答案，时间复杂度 $O(\sum n \lg n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int t;
inline void solve() {
	int n, m, ave = 0, cnt = 0, res = 0;
	vector<pair<int, int>> vec;
	map<int, int> mp; 
	cin>>n>>m;
	for(int i = 1, x ; i <= n ; i ++) {
		cin>>x;
		mp[x] ++;
	}	
	for(auto i : mp) {
		vec.push_back({i.first, i.second});
	}
	sort(vec.begin(), vec.end());
	ave = vec[0].first;
	for(auto i : vec) {
		int a = i.first, b = i.second;
		if(a - ave > 1) {
			res = max(res, a * min(m / a, b));
		} else {
			int tmp = min(cnt, m / ave), tmp1, tmp2 = m - min(cnt, m / ave) * ave;
			tmp1 = min(b, tmp2 / a), tmp2 -= tmp1 * a;
			res = max(res, m - tmp2 + min({tmp, b - tmp1, tmp2}));
		}
		ave = a, cnt = b;
	}
	cout<<res<<endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	cin>>t;
	while(t --) {
		solve();
	}
	return 0;
}
```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1995B1)
## 思路：
发现花瓣数与价格相同，所以最大花瓣数一定会小于等于 $m$。

排序后序列具有单调性，为什么？因为序列中没有负数。所以可以进行双指针处理。

如果再此时扫到的取件内的值大于 $m$，则不合法，左端点向右移动，如果少了，则可以更大，右端点向右移动，然后判断此时序列是否合法即可。
## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],p[200005];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);//排序保证单调性
		for(int i=1;i<=n;i++){
			p[i]=p[i-1]+a[i];//前缀和处理
		}
		int l=1,r=1,ans=0;
		while(l<=r && r<=n){//判边界
			//cout<<l<<" "<<r<<endl;
			if(p[r]-p[l-1]>m){//钱不够
				l++;//左端点右移，区间变小
			}else{
				if(l<=r-1 && a[r]-a[r-1]>1 || a[r]!=a[l] && a[r]!=a[r-1] && a[l]!=a[r-1]){//不合法情况
					l++;
					continue;
				}
				ans=max(ans,p[r]-p[l-1]);
				r++;//右端点右移，区间变大
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：0)

知识点：二分，前缀和，排序。

建议评黄。
### Sol
选中花束中花瓣数的差值在 $1$ 以内，想到按花瓣数排序。接着我们便可以枚举左端点，使右端点在满足要求的情况下最远来取得最多花瓣数，发现答案具有单调性，可以二分。

我们二分长度，使最远点的花瓣数到 $i$ 花瓣数的差值不超过 $1$，且总花瓣数在 $m$ 内。

复杂度 $O(Tn\log n)$。

### Code
```cpp
const int N = 2e5+5;
int a[N];
int n,m;
int sum[N];
bool check(int i,int mid)
{
	if(a[mid]-a[i] > 1) return false;
	if(sum[mid]-sum[i-1] > m) return false;
	return true;
}
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	int T = read();
	while(T--)
	{
		n = read(),m = read();
		for(int i{1};i<=n;i++) a[i] = read();
		sort(a+1,a+1+n);
		for(int i{1};i<=n;i++) sum[i] = sum[i-1]+a[i];
		int rans{};
		for(int i{1};i<=n;i++)
		{
			int ll = i,rr = n;
			int ans{};
			while(ll<=rr)
			{
				int mid = (ll+rr)>>1;
				if(check(i,mid)) ans = mid,ll = mid + 1;
				else rr = mid - 1;
			}
			if(sum[ans]-sum[i-1] <= m) rans = max(rans,sum[ans]-sum[i-1]);
		}
		writeln(rans);
	}
	return 0;

 }

```

---

