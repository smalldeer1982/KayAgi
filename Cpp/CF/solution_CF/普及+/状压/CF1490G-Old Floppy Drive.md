# Old Floppy Drive

## 题目描述

Polycarp was dismantling his attic and found an old floppy drive on it. A round disc was inserted into the drive with $ n $ integers written on it.

Polycarp wrote the numbers from the disk into the $ a $ array. It turned out that the drive works according to the following algorithm:

- the drive takes one positive number $ x $ as input and puts a pointer to the first element of the $ a $ array;
- after that, the drive starts rotating the disk, every second moving the pointer to the next element, counting the sum of all the elements that have been under the pointer. Since the disk is round, in the $ a $ array, the last element is again followed by the first one;
- as soon as the sum is at least $ x $ , the drive will shut down.

Polycarp wants to learn more about the operation of the drive, but he has absolutely no free time. So he asked you $ m $ questions. To answer the $ i $ -th of them, you need to find how many seconds the drive will work if you give it $ x_i $ as input. Please note that in some cases the drive can work infinitely.

For example, if $ n=3, m=3 $ , $ a=[1, -3, 4] $ and $ x=[1, 5, 2] $ , then the answers to the questions are as follows:

- the answer to the first query is $ 0 $ because the drive initially points to the first item and the initial sum is $ 1 $ .
- the answer to the second query is $ 6 $ , the drive will spin the disk completely twice and the amount becomes $ 1+(-3)+4+1+(-3)+4+1=5 $ .
- the answer to the third query is $ 2 $ , the amount is $ 1+(-3)+4=2 $ .

## 样例 #1

### 输入

```
3
3 3
1 -3 4
1 5 2
2 2
-2 0
1 2
2 2
0 1
1 2```

### 输出

```
0 6 2 
-1 -1 
1 3```

# 题解

## 作者：henrytb (赞：8)

题目用蜗牛爬井解释更好理解一点。

---

### 题目大意

有一只蜗牛在从一个井里往上爬。初始时它所在高度为 $0$。

他按照序列 $a$ 不停的爬着（序列 $a$ 长度为 $n$），每次爬的时候，他所在高度都 $+a_i$（$a_i$ 可能为负）。爬完 $n$ 次之后又从 $a_1$ 继续爬。

有 $m$ 次询问，每次问蜗牛爬到高度 $x$ 最少需要爬多少次，如果蜗牛会一直爬下去不停下，输出 `-1`。

---

### 题解

考虑把蜗牛在一次循环内能到达的正数所需的最短时间扔进一个 `map` 内。换句话说，我们想知道蜗牛在一次循环中到达 $x$ 最少需要爬多少次，只需在这个 `map` 上 `lower_bound` 一下 $x$ 就可以了。

然后显然还需要存一次循环总共蜗牛会移动多少，记为 $k$。

那么我们对于每个询问，先在 `map` 中找一下第一轮能不能到。

能就直接输出，不能的话分两种情况：

1. 如果 $k\le0$，那么蜗牛一定会永无停息地爬，输出 `-1`。

1. 如果 $k>0$，我们可以找到一个循环的次数 $w$ 使得 `map` 中最高的 `key` $+w\times k\ge x$ 。这个时候就是 $x$ 第一次被达到的时候。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,m;
int a[200005];
map<int,int> tim;
signed main() {
    for(scanf("%lld",&_);_;--_) {
        tim.clear();
        scanf("%lld%lld",&n,&m);
        int row=0,mx=0,mxid=0;
        rep(i,1,n) {
            scanf("%lld",&a[i]);
            row+=a[i];
            if(row>mx) mx=row,mxid=i,tim[mx]=i;
        }
        rep(i,1,m) {
            int x;
            scanf("%lld",&x);
            map<int,int>::iterator ii=tim.lower_bound(x);
            if(ii==tim.end()&&row<=0) {printf("-1 ");continue;}
            else if(ii==tim.end()){
                map<int,int>::iterator lst=tim.end();--lst;
                int ned=(x-lst->first+row-1)/row;
                ii=tim.lower_bound(x-ned*row);
                printf("%lld ",ii->second+ned*n-1);
            } else {
                printf("%lld ",ii->second-1);
            }
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先我们可以定义一个 $maxx$ 数组，表示前 $i$ 个数字中前缀和的最大值，以便于后续二分。若第一轮搞不定，而且一轮的总和还是非正，说明永远不会再长进了，无解了。否则，就类似蜗牛爬井，可以计算它需要在第几轮里成功满足条件，然后二分一下即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m;
ll a[200005], sum, x, s;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		sum = 0;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], a[i] = max (a[i - 1], sum += a[i]);
		while (m --) {
			cin >> x;
			if (x <= a[n])
				s = 0;
			else if (sum > 0)
				s = (x - a[n] + sum - 1) / sum;
			else {
				cout << "-1 ";
				continue ;
			}
			x -= s * sum;
			cout << lower_bound (a + 1, a + 1 + n, x) - a - 1 + s * n << ' ';
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：1)

显然每走一圈贡献是一定的，计算一下前缀和即可。

记前缀和为 $sum[i]$，$maxn[i]$ 为 $a[1]\sim a[i]$ 的起点为 1 的子串权值最大值，显然有 $maxn[i]=\max(maxn[i-1],sum[i])$。

第一圈就满足要求的（$maxn[n]\geq x$）可以特殊处理一下，这样特判的时候不容易出错。

然后特判无解，充要条件 $sum[n]\leq0$ 且 $x>0$。

剩下来的就是走了不止 1 圈的情况。我们可以二分圈数，每次 check 走 $mid+1$ 圈后能否满足条件，即 $sum[n]\times mid+maxn[n]\geq x$（因为第 $mid+1$ 圈可能走到图中就满足条件所以最后一圈贡献并不是 $sum[n]$ 而是 $maxn[n]$）。

然后二分得到圈数 $ans+1$，那么显然前 $ans$ 圈是走完整的，而最后一圈不一定，于是在 $maxn[]$ 数组上二分就好了，答案为$ans\times n+lower\_bound(maxn+1,maxn+n+1,x-ans\times sum[n])-maxn-1$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int t,n,m,a[200001],sum[200001],maxn[200001];
signed main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&m);
        maxn[0]=-1e18;
        sum[0]=0;
        for(register int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            sum[i]=sum[i-1]+a[i];
            maxn[i]=-1e18;
            maxn[i]=max(maxn[i-1],sum[i]);
        }
        while(m--)
        {
            int x;
            scanf("%lld",&x);
            if(maxn[n]>=x)
            {
                printf("%lld ",(long long)(lower_bound(maxn+1,maxn+n+1,x)-maxn-1));
                continue;
            }
            if(sum[n]<=0&&x>0)
            {
                printf("-1 ");
                continue;
            }
            int l=0,r=1e9,mid,ans=1e9;
            while(l<r)
            {
                mid=(l+r)>>1;
                if(mid*sum[n]+maxn[n]>=x)
                {
                    r=mid;
                    ans=mid;
                }
                else
                    l=mid+1;
            }
            printf("%lld ",(long long)(ans*n+(long long)(lower_bound(maxn+1,maxn+n+1,x-ans*sum[n])-maxn-1)));
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：1)

因为这场题貌似比较送？？？所以就给一道 $G$ 的题解。        

大致题意就是一个可循环数组 $a$ 现在查询 $m$ 个数 $x$ 要求你找到第一个位置 $idx$ 使得 $x \leq sum_{idx}$ 。      

很显然的就是我们可以暴力先看能不能在 $a$ 数组里面找，如果不行我们就直接暴力把 $a$ 数组当成一个数循环然后一直缩小 $x$ 最后再找一次。     

于是首先特判一下当前能不能找到这个数，接着我们看当前可不可以在第一轮里面就找到这个数，否则的话就暴力减直到 $x$ 可以在原数组里面被找到为止。         

很明显，我们可以通过不等式优化暴力减的过程，这样我们就可以在 $O(tmlog_n)$ 的时间内搞定。         

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define int long long
const int Len = 2e5 + 5;
int n,m,maxn[Len],a[Len],sum,x,Print;
signed main()
{
	int t;scanf("%lld",&t);
	while(t --)
	{
		sum = 0;
		scanf("%lld %lld",&n,&m);
		for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
		for(int i = 1 ; i <= n ; i ++)
		{
			sum += a[i];
			maxn[i] = max(maxn[i - 1] , sum);
		}
		while(m --)
		{
			Print = 0;
			scanf("%lld",&x);
			if(maxn[n] < x && sum <= 0)//
			{
				printf("-1 ");
				continue;
			}
			if(maxn[n] < x)
			{
				int Round = ((x - maxn[n]) % sum) ? (x - maxn[n]) / sum + 1 : (x - maxn[n]) / sum;
				Print = Round * n;
				x -= Round * sum;
			}
			int l = 1 , r = n;
			while(l < r)
			{
				int mid = (l + r) >> 1;
				if(maxn[mid] >= x) r = mid;
				else l = mid + 1; 
			}
			printf("%lld ",Print + l - 1);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Meickol (赞：0)

不难想到本题一定程度上和循环节挂钩。

你可以统计一个周期内的一段前缀极大和（局部），以及一个周期内的整段前缀和。

然后先看局部前缀极大和是否能 $\ge x$。

如果不能的话，那么必须选中一个完整周期的前缀和，然后再在结尾处拼接一段局部前缀极大和，然后再判断尝试。

但是如果直接这样模拟，时间复杂度巨大。

但是你会发现，如果将局部前缀极大和记为 $pTw$，一个完整周期的前缀和记为 $Tw$。那么形式化表示即：

- 先判断 $pTw$ 是否可以，如果可以，从 $1$ 开始直接到 $pTw$ 对应下标进行模拟。
- 如果不行，则寻找第一个满足 $k \times Tw+pTw \ge x$ 的 $k$。这个过程可以使用二分优化。






然后你发现似乎其实可以直接寻找第一个满足 $k \times Tw+pTw \ge x$ 的 $k$ 即可，因为只用 $pTw$ 的情况恰好是 $k=0$ 的情况。

那么我们直接对这个 $k$ 进行二分答案。

假如 $k$ 完成二分。假如 $pTw$ 对应的长度为 $pTw\_idx$，我们接下来要进行遍历的区间就是 $[nk,nk+pTw\_idx]$。



但是并不能直接处理二分，因为直接二分并不一定具备单调性。

因为当 $prefix_n \lt 0$，随 $mid$ 增大而单调递减；当 $prefix_n \gt 0$，随 $mid$ 增大而单调递增。

所以你需要先讨论好 $prefix_n$ 的情况。

分析一下不难发现，若 $prefix_n \lt 0$，则没必要再进行二分答案了（因为要求满足条件的最小的下标），且如果有解则答案一定在第一个循环节内，否则不存在答案。



为了更快的求解，考虑二分查找，用一个 $prefix\_max_{i}$ 数组保存前 $i$ 个数的前缀和最大值。

基于上述思路便可实现下方代码。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=2e5+5;
int n,q;
int a[N];
LL prefix[N],prefix_max[N];
void solve(){
	cin>>n>>q;
	rep(i,1,n) cin>>a[i];
	LL INF;
	memset(&INF,0x3f,sizeof INF);
	rep(i,1,n){
		prefix[i]=prefix[i-1]+a[i];
		prefix_max[i]=-INF;
		prefix_max[i]=max(prefix_max[i-1],prefix[i]);
	}
	auto check = [&] (int x,LL need){
		return x*prefix[n]+prefix_max[n]>=need;
	};
	while(q--){
		int x;
		cin>>x;
		if(prefix_max[n]>=x){
			int pos=lower_bound(prefix_max+1,prefix_max+1+n,x)-prefix_max;
			cout<<pos-1<<" ";
			continue;
		}
		if(prefix[n]<=0){
			cout<<-1<<" ";
			continue;
		}
		int l=0,r=1e9;
		while(l<r){
			int mid=(l+r)>>1;
			if(check(mid,x)) r=mid;
			else l=mid+1;
		}
		LL rest=x-l*prefix[n];
		int pos=lower_bound(prefix_max+1,prefix_max+1+n,rest)-prefix_max;
		cout<<(LL)l*n+pos-1<<" ";
	}
}
```

---

## 作者：Starmoon_dhw (赞：0)

# 前言
一道比较有意思的题目，思维含量不低。

# 题意

给你一个序列，你可以将他复制无数次，问从头开始累加，什么时候累加的和至少达到 $x$。

有 $T$ 组询问，每组询问包含 $n,m$ 表示这个序列的长度 $n$ 和问题个数 $m$。

# 思路

题目的翻译里提到了前缀和，由此我们可以先对原序列做一个前缀和的操作，当然不是普通的前缀和，由于数列中有负数，如果是普通的前缀和则无法保证前缀和数字为单调递增，不利于后面查找 $x$。所以我们可以将前缀和数组中保存的数改为前 $i$ 个数字中前缀和的最大值，有利于我们后面进行二分查找。

做好这个处理之后，我们可以先判断前缀和数组中的最大值是否为正数，如果不是可以输出 $-1$ 结束了。如果不是可以先将 $x$ 除以一下前缀和数组中的最大值，并将商记录为 $t$，余数记录为 $v$，然后只需要在前缀和数组中查询不小于 $v$ 的第一个数将其下标记为 $w$，那么答案就是
$ w-1+s\times n $ 了。

细节需要注意（初始化，位置处理等）。

[AC记录](https://codeforces.com/problemset/submission/1490/286461452)

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1490G)
## 思路
感觉其它题解讲的比较复杂，我这里简单地讲一下。

首先我们肯定要求一个前缀和，因为问题中有前缀和，并且我们要对这个前缀和数组求一个前缀 $\max$，因为可以发现，若 $sum_i<sum_{i-1}$，这个 $sum_i$ 是没用的，因为在我们查找的时候一定找到 $i-1$，所以我们不妨把 $sum_i$ 覆盖掉。

接下来我们就直接在前缀和数组上二分，先让 $x$ 对原序列的总和取余，但是这里有一个坑点，不一定一定要循环 $x/sum_{a_i}$ 次，有可能中途就退出了。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=2e5+10;
int a[N],qsum[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;cin>>T;
    while (T--){
    	int n,m,sum=0;cin>>n>>m;
    	for (int i=1;i<=n;++i){
    		cin>>a[i],sum+=a[i];
	    	qsum[i]=qsum[i-1]+a[i];
	    }
	    for (int i=2;i<=n;++i) qsum[i]=max(qsum[i],qsum[i-1]);
	    while (m--){
	    	int x;cin>>x;
            if (qsum[n]>=x){
	    		cout<<lower_bound(qsum+1,qsum+n+1,x)-qsum-1<<' ';
			}else if (sum<=0) cout<<"-1 ";
            else{
				int xun=x/sum;
				xun*=n;--xun;
				x%=sum;
                if (xun<0) cout<<"-1 ";
                else if (!x){
                    int delta=qsum[n]-x;
                    delta/=sum;
                    xun-=(delta*n);
                    x+=(delta*sum);
                    cout<<lower_bound(qsum+1,qsum+n+1,x)-qsum+xun<<' ';
                    //cout<<xun-n+lower_bound(qsum+1,qsum+n+1,sum)-qsum<<' ';
				}else if (qsum[n]<x) cout<<"-1 ";
			    else{
                    int delta=qsum[n]-x;
                    delta/=sum;
                    xun-=(delta*n);
                    x+=(delta*sum);
                    cout<<lower_bound(qsum+1,qsum+n+1,x)-qsum+xun<<' ';
                }
            }
		}
        cout<<'\n';
	}
    return 0;
}
```


---

## 作者：little_sun (赞：0)

### 题目大意

有一个长为 $n$ 的数组 $a_i$，把 $a_i$ 复制成一个无限序列。

给 $m$ 个询问，每次询问给定一个整数 $x$ ，问这个序列第一个前缀和 $ \geq x$ 的下标是什么。

$ 1 \leq n, m \leq 2 \times 10 ^ 5, -10^9 \leq a_i \leq 10^9, 1 \leq x \leq 10 ^ 9$

### 题目分析

首先先判断一下有没可能在一次循环之内结束，这可以用一次双指针解决。

接下来对于还没有求出答案的 $x$ ，如果全部 $n$ 个数的和 $s_n \leq 0$ ，则显然不可能使前缀和达到 $x$。

否则我们将 $x$ 反复减去 $s_n$ 使得 $x' \leq \max s_i$ ，之后就可以通过一次二分求出第一个前缀和 $ \geq x'$ 的下标。

时间复杂度 $ \Theta((n + m) \log n)$ 。

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define pair std::pair<ll, ll>
#define mp(i, j) std::make_pair(i, j)
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const ll MaxN = 2e5 + 10;

pair q[MaxN];
std::map<ll, ll> mp;
std::vector<pair> v;
ll n, m, now, a[MaxN], s[MaxN], ans[MaxN];

void init()
{
    v.clear(), mp.clear(), now = 0;
    for(ll i = 0; i < m + 10; i++)
        ans[i] = -1;
    for(ll i = 0; i < n + 10; i++)
        a[i] = s[i] = 0;
}

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch > '9' || ch < '0')
    {
        if(ch == '-')
            f = 0;
        ch = getchar();
    }
    while(ch <= '9' && ch >= '0') 
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? x : (-x);
}

signed main()
{   
    ll T = read();
    while(T--)
    {
        n = read(), m = read(), init();
        for(ll i = 1; i <= n; i++)
        {
            a[i] = read(), s[i] = a[i] + s[i - 1];
            if(s[i] > 0 && !mp[s[i]]) 
                mp[s[i]] = i, v.push_back(mp(s[i], i));
        }
        for(ll i = 1; i <= m; i++)
            q[i].first = read(), q[i].second = i;
        std::sort(q + 1, q + m + 1), std::sort(v.begin(), v.end());
        if(v.size() >= 2)
        {
            for(ll i = v.size() - 2; i >= 0; i--)
            {
                ll x = mp[v[i].first];
                x = std::min(x, mp.upper_bound(v[i].first)->second);
                mp[v[i].first] = x, v[i].second = x;
            }
        }
        // for(auto x : mp)
        //     meow("# %lld %lld\n", x.first, x.second);
        for(ll i = 0; i < v.size(); i++)
        {
            while(now < m && q[now + 1].first <= v[i].first)
                ++now, ans[q[now].second] = v[i].second - 1;
        }
        // meow("ok");
        for(ll i = now + 1; i <= m; i++)
        {
            if(s[n] <= 0) continue;
            ans[q[i].second] = n * ((q[i].first - v.back().first + s[n] - 1) / s[n]);
            q[i].first -= s[n] *((q[i].first - v.back().first + s[n] - 1) / s[n]), 
            ans[q[i].second] += mp.lower_bound(q[i].first)->second - 1;
            // meow("$ %lld %lld %lld\n", ans[q[i].second], q[i].first, s[n]);
        }
        for(ll i = 1; i <= m; i++)
            printf("%lld%c", ans[i], " \n"[i == m]);
    }
    return 0;
}
```



---

## 作者：清烛 (赞：0)

挂一下 [My Blog](https://imyangty.com/oi/1309)
## 题意
有一个光盘上面依次记录了一些数，有一个驱动器按照如下算法运行：

- 接受输入 $x$ 并开一个变量 $s$
- 从光盘的第一个数考虑起（此时运行时间为 $0$），如果这个数小于 $x$ 则把这个数加到 $s$ 中去，如果大于等于 $x$ 就返回运行时间 $t$。每一秒考虑下一个数，循环。

给定光盘上的数，并给定 $m$ 个 $x$，对于每个 $x$ 求运行时间 $t$。

## 题解
**光盘上的数有正有负**，这是本题的一个重难点。

首先处理一下这些数的前缀和，记为 $s_i$，不难发现如下性质：如果 $x < \max_{1\le i\le n}\lbrace s_i\rbrace$，说明光盘要被循环不止一次，如果 $s_n \le 0$ 那么累加的和一辈子都达不到 $x$，直接输出 $-1$。

对于需要循环多次的，处理出循环的次数，即为

$$
r = \left\lceil\frac{x - \max_{1\le i\le n}\lbrace s_i\rbrace}{s_n}\right\rceil
$$

怎么来的呢？我们必然有 $r\times s_n + \max_{1\le i\le n}\lbrace s_i\rbrace \ge x$，化简便知要向上取整。代码中即为 `r = (x - val[tot] + sum[n] - 1) / sum[n];`

把循环的这些次数去掉，即 $x:=x - r\times s_n$，现在问题就变为**找到最小的满足 $s_i \ge x$ 的 $i$**。

赛时我就是在这里卡住了。因为 $s_i$ 是不满足单调性的，所以没办法使用二分查找，于是就 GG 了。

怎么办呢？注意到我们要的是**最小下标**，所以不满足单调性的部分我们可以**直接舍弃**。即把 $s_i$ 单调递增的部分取出来，就可以使用二分了。

**开 `long long`**

```cpp
int sum[maxn], val[maxn], id[maxn];

signed main()
{
    int T = read();
    while (T--)
    {
        int n = read(), m = read();
        FOR(i, 1, n) sum[i] = sum[i - 1] + read();
        int tot = 0;
        FOR(i, 1, n)
        {
            if (!tot || sum[i] > val[tot])
                val[++tot] = sum[i], id[tot] = i;//处理出那些单调递增的前缀和以及对应的下标
        }
        while (m--)
        {
            int x = read();
            if (x > val[tot] && sum[n] <= 0)
                printf("-1 ");
            else
            {
                int r = 0;
                if (val[tot] < x)
                    r = (x - val[tot] + sum[n] - 1) / sum[n];//处理出要转多圈的情况
                x -= r * sum[n];
                printf("%lld ", r * n + id[std::lower_bound(val + 1, val + tot +1, x) - val] - 1);
            }
        }
        puts("");
    }
    return 0;
}
```

---

