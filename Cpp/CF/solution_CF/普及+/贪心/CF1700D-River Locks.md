# River Locks

## 题目描述

Recently in Divanovo, a huge river locks system was built. There are now $ n $ locks, the $ i $ -th of them has the volume of $ v_i $ liters, so that it can contain any amount of water between $ 0 $ and $ v_i $ liters. Each lock has a pipe attached to it. When the pipe is open, $ 1 $ liter of water enters the lock every second.

The locks system is built in a way to immediately transfer all water exceeding the volume of the lock $ i $ to the lock $ i + 1 $ . If the lock $ i + 1 $ is also full, water will be transferred further. Water exceeding the volume of the last lock pours out to the river.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1700D/400a916b7267c9571228203513add48062776ecc.png)The picture illustrates $ 5 $ locks with two open pipes at locks $ 1 $ and $ 3 $ . Because locks $ 1 $ , $ 3 $ , and $ 4 $ are already filled, effectively the water goes to locks $ 2 $ and $ 5 $ .Note that the volume of the $ i $ -th lock may be greater than the volume of the $ i + 1 $ -th lock.

To make all locks work, you need to completely fill each one of them. The mayor of Divanovo is interested in $ q $ independent queries. For each query, suppose that initially all locks are empty and all pipes are closed. Then, some pipes are opened simultaneously. For the $ j $ -th query the mayor asks you to calculate the minimum number of pipes to open so that all locks are filled no later than after $ t_j $ seconds.

Please help the mayor to solve this tricky problem and answer his queries.

## 说明/提示

There are $ 6 $ queries in the first example test.

In the queries $ 1, 3, 4 $ the answer is $ -1 $ . We need to wait $ 4 $ seconds to fill the first lock even if we open all the pipes.

In the sixth query we can open pipes in locks $ 1 $ , $ 3 $ , and $ 4 $ . After $ 4 $ seconds the locks $ 1 $ and $ 4 $ are full. In the following $ 1 $ second $ 1 $ liter of water is transferred to the locks $ 2 $ and $ 5 $ . The lock $ 3 $ is filled by its own pipe.

Similarly, in the second query one can open pipes in locks $ 1 $ , $ 3 $ , and $ 4 $ .

In the fifth query one can open pipes $ 1, 2, 3, 4 $ .

## 样例 #1

### 输入

```
5
4 1 5 4 1
6
1
6
2
3
4
5```

### 输出

```
-1
3
-1
-1
4
3```

## 样例 #2

### 输入

```
5
4 4 4 4 4
6
1
3
6
5
2
4```

### 输出

```
-1
-1
4
4
-1
5```

# 题解

## 作者：dottle (赞：23)

## 思路

看起来答案好像是 $\lceil \frac {\sum v}{t} \rceil $。但其实这样不一定够，因为有可能前面的槽还没填满，后面的槽就已经开始漏水了！一个简单的例子：$v_1=10,v_2=1$。这样 $t< 10 $ 的时候是无解的！思考一下出现这个现象的原因：前 $i$ 个水槽有 $\sum_{j=1}^i v_i$ 的容积，又只能由前 $i$ 个水龙头提供水。也就是说，前 $i$ 个水槽至少需要 $\lceil \frac {\sum_{j=1}^i v_i}{i} \rceil $ 秒才能填满。求出这 $n$ 个值的最大值，我们就可以得到一个 $t$ 的下界了，不妨设为 $X$。如果输入的 $t$ 小于 $X$，则肯定无解。

在进行了上面的思考后，容易产生一个误解，即会漏很多水出去。其实不会，因为我们开水龙头的时候，肯定是先开第一个，再开第二个，这样依次开下去。然后可以这样想，我们把第一个水龙头开完 $t$ 秒后，再开第二个。这样看来每一个时刻水填充的肯定都是一个前缀。直到最后发现所有槽都被填完后，就不会再开水龙头了。这样看来，就只有开最后一个水龙头的时候会浪费一些水，所以答案其实就是 $\lceil \frac {\sum v}{t} \rceil $。

## 题解

设 $X=\max_i \lceil \frac {\sum_{j=1}^i v_i}{i} \rceil$，则：

- 若 $t<X$，无解;
- 否则，答案为 $\lceil \frac {\sum v}{t} \rceil $。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1005000;
using namespace std;

int n,q,a[N];
int res;

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	for(int i=1;i<=n;i++)res=max(res,(a[i]+i-1)/i);
	cin>>q;
	for(int i=1;i<=q;i++){
		int x;cin>>x;
		cout<<(x<res?-1:(a[n]+x-1)/x)<<'\n';
	}
}

main(){
	ios::sync_with_stdio(0);
	solve();
}
```


---

## 作者：lingfunny (赞：4)

题目只要判断是否全填满，没填满的时候**和哪个没填满是无关的**。

由这句话不难引发出一个思路，**水龙头全装在前面几个水槽**，会发现这样一定不会影响最后的答案。事实上，这样做是最优构造，因为水满了会往后流，所以前面的水龙头一定是比后面水龙头强的。

就只剩一种情况会非法：对于槽 $i$，在它及它前面装满水龙头（即 $i$ 个）也不能让它在指定时间内填满。抽象描述就是 $it<s_i$（$s_i$ 为前缀水槽容量）。移项得到 $t<\frac{s_i}{i}$。于是对 $\frac{s_i}{i}$ 最大的那个判断就行了。

求数量直接输出 $\lceil\frac{s_n}{t}\rceil$，不难理解。

```cpp
// Problem: D. River Locks
// From: Codeforces - Codeforces Round #802 (Div. 2)
// URL: https://codeforces.com/contest/1700/problem/D
// Time: 2022-06-19 17:05
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5+10;

int n, q, v[mxn];
LL s[mxn];
double MX;

signed main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", v+i), s[i] = s[i-1] + v[i];
	for(int i = 1; i <= n; ++i) MX = max(MX, (double)s[i]/i);
	scanf("%d", &q);
	while(q--) {
		int t; scanf("%d", &t);
		// if exist si > it
		if(MX - t > 1e-7) { puts("-1"); continue; }
		printf("%lld\n", (t-1+s[n])/t);
	}
	return 0;
}
```

---

## 作者：MeowScore (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1700D)

不会更快的做法，蒟蒻就来一篇二分的题解吧 qwq

首先有一个显然的结论：当打开水管的数目一定，打开的水管是从左侧开始连续的一段时最快装满所有水池。可以这样想：我们的任务是流满所有的水池，从左边开始开水管一定是浪费水最少的（如果打开的水管更靠右就面临着左边没装满，右边就装满开始无效放水了，这些水管此时没有作用，不如拿到左边）。

我们把问题转化成求解“打开前 $i$ 根水管需要多长时间装满水”，预处理之，询问的时候二分即可。

设 $f_i$ 表示打开前 $i$ 根水管转满水需要花费的时间，但是并不太好求。

我们再设一个辅助数组 $t$，$t_i$ 表示打开前 $i$ 根水管**装满前 $i$ 个水池**的耗时，这个数组就很好求了，设 $s_i$ 是前 $i$ 个水池的容积之和，有：$t_i=\max(t_{i-1},\left\lceil\dfrac{s_i}{i}\right\rceil$)。如何理解？如果第 $i$ 个水池都装满了开始往右边流了，前面的 $i-1$ 个水池还没装满，答案即为 $\max$ 的前一项。否则，我们一滴水都没浪费，$i$ 根水管共同装满 $s_i$ 的容积，即为 $\max$ 的后一项。

考虑根据该数组推得 $f$ 数组。我们展开分类讨论，若在这 $t_i$ 的时间内，所有的 $n$ 个水池已经装满了，显然 $f_i=t_i$，即等待前 $i$ 个水池装满，恰好所有的水池也装好了。否则，经过 $t_i$ 的时间之后，剩余的 $s_n-t_i\times i$ 的容积就由 $i$ 根水管共同完成，$f_i=t_i+\left\lceil\dfrac{s_n-t_i\times i}{i}\right\rceil$。

然后快乐二分，时间复杂度 $O(q \log{n})$。

特别的，当给出的某次询问时间小于 $f_n$，无解。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
int a[N],t[N],f[N],n,T,s[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
		t[i]=max(t[i-1],(s[i]-1)/i+1);
	for(int i=1;i<=n;i++){
		if(t[i]*i>=s[n])
			f[i]=t[i];
		else
			f[i]=(s[n]-t[i]*i-1)/i+1+t[i];
	}
	cin>>T;
	while(T--){
		int x;
		cin>>x;
		if(x<f[n]){
			cout<<-1<<endl;
			continue;
		}
		int l=1,r=n;
		while(l<r){
			int mid=(l+r)/2;
			if(f[mid]<=x)
				r=mid;
			else
				l=mid+1;
		}
		cout<<r<<endl;
	}
	return 0;
}
```

---

## 作者：StarLbright40 (赞：2)

~~本来在写比赛总结，发现这道题写了这么多好像珂以冲一发题解~~

>[D. River Locks](https://codeforces.com/contest/1700/problem/D)

>有 $n$ 个水闸，每个水闸容积为 $v_i$ 且配有一根进水水管，每根水管每秒可进水 $1$ 单位。若当前水闸已满且仍有进水，则水会顺次进入下一个水闸，若是第 $n$ 个水闸则会流入河中。

>$q$ 组询问，每组询问给出一个 $t$，询问若初始所有水闸均为空，在 $t$ 时间内注满所有水闸至少需要打开多少根水管，或不可能注满。$(1\le n,q\le 2\times10^5,1\le v_i,t\le10^9)$

靠前的水管流出的水能流进靠后的水闸，反过来却不行，所以把开启的水管放得靠前一定不劣，所以开启一定数量的水管一定是从 $1$ 开始依次打开。

注意到，如果在一定时间内、开启一定数量水管能注满水闸，那用更久的时间或更多的水管一定也珂以，从而答案具有单调性；同时如果已知开了几根水管，就珂以 $\mathcal O(n)$ 递推计算出注满水闸的用时，于是珂以考虑二分答案。

~~然而时间复杂度是 $\mathcal O(qn\log n)$ 愉快 gg~~

珂以分别预处理出开启 $1\dots n$ 根水管注满水闸的用时，从而这个用时具有单调性，珂以直接在这个答案数组上二分做到询问复杂度 $\mathcal O(q\log n)$。

~~然而直接预处理是 $\mathcal O(n^2)$ 还是会寄~~。

冷静思考珂以发现，开启 $i$ 根水管的答案珂以分为两部分，注满前 $i$ 个水闸的用时和注满后面的水闸的用时。容易想到记 $t1_i=\left\lceil\dfrac{\sum_{j=1}^nv_j}{i}\right\rceil$，思考一下它的含义：

- 若时间 $t1_i$ 时前 $i$ 个水闸已全部注满，则此时后面的水闸一定都**恰好**注满，从而 $t$ 即为答案；

- 若时间 $t1_i$ 时前 $i$ 个水闸未全部注满，则此时后面的水闸一定已都注满，再计算一下注满前面的水闸用时即可：对于 $\forall j\le i$，前 $j$ 个水闸只能流入前 $j$ 个水管的水，所以这个用时即为 $\max_{j=1}^i\left\lceil\dfrac{\sum_{k=1}^jv_k}{j}\right\rceil$。

显然这两部分都能够 $\mathcal O(n)$ 预处理，取 $\max$ 即可。时间复杂度 $\mathcal O(n+q\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+2;
int n,q;long long sum,t[N];
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i){
		scanf("%d",&x),sum+=x;
		t[i]=max(t[i-1],(sum+i-1)/i);
	}
	for(int i=1;i<n;++i)
		t[i]=max(t[i],(sum+i-1)/i);
	scanf("%d",&q);
	for(int x,l,r,mid;q--;){
		scanf("%d",&x);
		if(x<t[n]){printf("-1\n");continue;}
		l=1,r=n;
		while(l<r){
			mid=(l+r)>>1;
			x<t[mid]?l=mid+1:r=mid;
		}
		printf("%d\n",l);
	}
	return 0;
}
```
~~是不是以为要结束了？~~

记 $t1_i=\left\lceil\dfrac{\sum_{j=1}^nv_j}{i}\right\rceil$，$t2_i=\max_{j=1}^i\left\lceil\dfrac{\sum_{k=1}^jv_k}{j}\right\rceil$，$t_i=\max(t1_i,t2_i)$ 为开启 $i$ 根水管注满水闸的用时，由上面的推理可知从 $1$ 到 $n$，$t1_i$ 和 $t_i$ 都单调不升，$t2_i$ 单调不降，所以珂以得到 $t_i=\max(t1_i,t2_n)$。

回过头来分析一下询问：对于询问给出的 $t$，若 $t<t_n$，则显然输出 $-1$；否则，由于 $t\ge t_n$，有 $t\ge t2_n$，这时需要输出的是使 $t\ge t_i$ 的最小的 $i$，也就是使 $t\ge t1_i=\left\lceil\dfrac{\sum_{j=1}^nv_j}{i}\right\rceil$ 的最小的 $i$，也就是 $\left\lceil\dfrac{\sum_{j=1}^nv_j}{t}\right\rceil$。

空间复杂度 $\mathcal O(1)$，时间复杂度 $\mathcal O(n+q)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,q;long long sum,t;
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i){
		scanf("%d",&x);
		sum+=x,t=max(t,(sum+i-1)/i);
	}
	scanf("%d",&q);
	for(int x;q--;){
		scanf("%d",&x);
		printf("%d\n",x<t?-1:(sum+x-1)/x);
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：2)

### 1 视频题解

![](bilibili:BV1Fv4y137u9)

### 2 思路

设 $s[i]=\sum_{j=1}^iv[j]$。

我们可以发现，就算是打开全部的管道，将第一个装完也要 $s[1]$ 秒，将第二个装完也要 $\lceil\dfrac{s[2]}{2}\rceil$，依次类推，将第 $i$ 个装完也要 $\lceil\dfrac{s[i]}{i}\rceil$ 秒。

所以，计算出打开全部管道需要多少秒钟装完水，不满足此条件的直接输出 $-1$ 即可。

然后我们发现，尽可能打开上游的管道是最好的。并且，在不输出 $-1$ 的情况下，装满水一定需要且只需要 $\lceil\dfrac{s[n]}{t}\rceil$ 个管道。

输出即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
#define inf 2e15
int n;
int q;
long long a[max_n+2];
long long s[max_n+2];
long long need;//最少需要时间
int ans;
long long divll(long long x,long long y){
	return (x+y-1)/y;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1700D_1.in","r",stdin);
	freopen("CF1700D_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	s[0]=0;
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
	need=a[1];
	for(int i=2;i<=n;++i)need=max(need,divll(s[i],i));
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		long long x;
		scanf("%lld",&x);
		if(x<need)printf("-1\n");
		else printf("%lld\n",divll(s[n],x));
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/77692716)

By **dengziyue**

---

## 作者：清烛 (赞：2)

先讲 $O((n+q)\log n)$ 的赛时做法，后文有 $O(n+q)$ 做法。

首先我们有一个很重要的 observation：往一段前缀内的水闸注水一定是不会劣的，因为无论如何多出来的水都会向右流，所以我们明显可以使用二分进行求解。

具体地我们预处理出前缀和和后缀和，然后二分出注水的前缀 $x$，check 就看往前 $\mathrm{mid}$ 个水闸注水 $t$ 分钟后，前 $\mathrm{mid}$ 个水闸剩下的水能不能补完后面。

但是需要注意判断无解：有一些时候就算上面的限制得到了满足，水仍然无法填满，具体可以看这组数据：

```
1
4 7 1 3
1
5
```

正确答案应该是无解，因为 $v_2 = 7$ 是填不满的，所以需要提前二分出一个有解的最小的 $t$（就假设所有管子都注水），不难发现大于等于这个 $t$ 也一定会有解，具体看代码。

```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 2e5 + 5;
using ll = long long;
using namespace std;
int n, q;
ll v[maxn], pre[maxn], suf[maxn], maxv;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> v[i], maxv = max(maxv, v[i]), pre[i] = v[i] + pre[i - 1];
    DEC(i, n, 1) suf[i] = v[i] + suf[i + 1];
    cin >> q;
    int ddl = maxv, l = 1, r = maxv;
    while (l <= r) {
        int mid = (l + r) >> 1;
        ll tmp = 0; bool flg = 1;
        FOR(i, 1, n) {
            if (tmp + mid < v[i]) flg = 0;
            tmp = tmp + mid - v[i];
        }
        if (flg) ddl = mid, r = mid - 1;
        else l = mid + 1;
    }
    while (q--) {
        int x; cin >> x;
        if (x < ddl) {
            cout << "-1\n";
            continue;
        }
        int l = 1, r = n, ans = -1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (mid * x - pre[mid] >= suf[mid + 1]) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

线性做法：首先对于一个水槽，其能被填满的最小时间（就假设前面都注水）为 $e_i = \left\lceil\dfrac{s_i}{i}\right\rceil$，其中 $s_i$ 为容量的前缀和。那么处理出 $\max\{e_i\}$ 我们就知道无解的界。然后因为你总要填满所有的水槽，即水的体积一定是 $s_n$，所以对于有解的情况答案一定为 $\left\lceil\dfrac{s_n}{t} \right\rceil$。

```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 2e5 + 5;
using ll = long long;
using namespace std;
int n, q;
ll v[maxn], pre[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> v[i], pre[i] = v[i] + pre[i - 1];
    ll ddl = 0;
    FOR(i, 1, n) ddl = max(ddl, (pre[i] + i - 1) / i);
    cin >> q;
    while (q--) {
        int t; cin >> t;
        cout << (t < ddl ? -1 : (pre[n] + t - 1) / t) << '\n';
    }
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

我们发现其实灌满了前一个，就相当于把水龙头移到了后一个水池。所以把水龙头放在上面，就可以整体看成一个很大的容器。

那么，灌满前 $i$ 个容器的最短时间就是灌满 $1$ 到 $i$ 这些容器的最小时间。对于 $i$ 就相当于 $i$ 个水龙头同时灌前 $i$ 个容器。以此类推，前 $n$ 个容器需要的**最短时间**是 $\max\limits_{i=1}^{n}\left\lceil\dfrac{\sum\limits_{j=1}^{i}v_j}{i}\right\rceil$。那么 $t$ 如果小于这个就显然无解，输出 -1。

除了这个，答案就是 $\left\lceil\dfrac{\sum v_i}{t}\right\rceil$。这个应该比较显然，那么在 $t$ 的时间内装满，每个水龙头灌水的速度是 $1$ ，上面的式子就不难理解了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int n,x,sum=0,maxn=0; scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x),sum+=x,maxn=max(maxn,(sum+i-1)/i);
	int q; scanf("%lld",&q);
	while(q--)
	{
		int t; scanf("%lld",&t);
		if(t<maxn) puts("-1");
		else printf("%lld\n",(sum+t-1)/t);
	}
	return 0;
}
```

---

## 作者：Phartial (赞：0)

## 思路

当询问有解时，$ans=\left\lceil{\frac{\sum_{j=1}^na_j}{t_i}}\right\rceil$，考虑怎么快速判断是否有解。

发现无解只可能是所有的水龙头都打开还不能在 $x$ 秒内装满每个容器，接着发现 $x$ 满足单调性（有一个界 $y$ 使得 $x\le y$ 时无解，而 $x>y$ 时有解）。

二分找 $y$ 就行了。

## 代码

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n, q, a[kN];
LL l, r, s;

bool C(LL x) {  // 判断每个水龙头开 x 秒有没有解
  LL y = 0;     // 当前可以流到下一个桶的水量
  for (int i = 1; i <= n; ++i) {
    y += x;           // 把所有水龙头都打开
    if (a[i] <= y) {  // 如果可以装满
      y -= a[i];      // 减去这一部分，剩下的流到下一个桶里
    } else {          // 否则无解
      return 0;
    }
  }
  return 1;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s += a[i];
  }
  l = 0, r = 1e9;
  for (LL m; l < r;) {  // 二分 y
    m = l + r + 1 >> 1;
    if (C(m)) {
      r = m - 1;
    } else {
      l = m;
    }
  }
  cin >> q;
  for (int x; q--;) {
    cin >> x;
    cout << (x <= l ? -1 : (s + x - 1) / x) << '\n';
  }
  return 0;
}
```

---

## 作者：Mu_tr (赞：0)

## 题目大意
现在有 $n$ 个容量不同的桶，有 $q$ 个询问，每次询问问在时间 $t$ 内最少开多少个进水口（每个桶上方最多只能开一个进水口），能让所有桶在时间 $t$ 内装满水。（如果 $i$ 号桶装满水，多余的水会向下流到 $i+1$ 号桶里，如果 $i+1$ 号桶也满了，就流到 $i+2$ 号桶里，以此类推）。

## 思路
显然，如果要让所有桶装满水,令相应要开的进水口数为 $x$，那必要的一个条件为 $t\cdot x\geq \sum_{i=1}^{n}v_{i}$，那观察样例一我们还可以发现，在满足上面那个条件的情况下，前面的桶可能会出现没被装满的情况，因为后面桶接的水不能倒流回前面的桶里且每个桶上最多只能开一个进水口，所以有部分水是流出整个桶群了，此时我们要判断前面的桶是否流满了。为了尽可能防止以上情况的发生，显然我们将所有进水口往前放是最优的，那我们令 $dp[i]$ 表示开 $i$ 个进水口的情况下前 $i$ 个桶装满水需要的最少时间，显然有转移 $dp[i]=\max(dp[i-1],\lceil sum[i]/i \rceil)$，其中 $sum[x]=\sum_{i=1}^{x}v_{i}$，预处理一下就好了。最后我们回答的时候二分要开多少个进水口，判断一下之前的两个条件是否成立即可， 显然那两个条件均具有单调性，可以判断。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,v[200005],q,t[200005],sum[200005],p[200005],tot=0;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		v[i]=read();
		sum[i]=sum[i-1]+v[i];
		p[i]=(sum[i]-1)/i+1;
		tot+=v[i];
	}
	for(int i=1;i<=n;i++) p[i]=max(p[i],p[i-1]);
	q=read();
	for(int i=1;i<=q;i++){
		int s=read(),l=1,r=n,mid,res=1e9;
		while(l<=r){
			mid=(l+r)>>1;
			if(s>=p[mid]&&(mid*s)>=tot) res=min(res,mid),r=mid-1;
			else l=mid+1; 
		}
		if(res==1e9) puts("-1");
		else cout<<res<<"\n";
	}
	return 0;
}

```


---

