# [USACO25JAN] Farmer John's Favorite Operation S

## 题目描述

又是 Farmer John 的农场上寒冷而无聊的一天。为了打发时间，Farmer John 发明了一种关于在整数数组上进行操作的有趣的休闲活动。

Farmer John 有一个包含 $N$（$1 \leq N \leq 2 \cdot 10^5$）个非负整数的数组 $a$ 和一个整数 $M$（$1 \leq M \leq 10^9$）。然后，FJ 会请 Bessie 给出一个整数 $x$。在一次操作中，FJ 可以选择一个索引 $i$，并对 $a_i$ 加 $1$ 或减 $1$。FJ 的无聊值是他必须执行的最小操作次数，以使得对于所有的 $1 \leq i \leq N$，$a_i-x$ 均可被 $M$ 整除。

对于所有可能的 $x$，输出 FJ 的最小无聊值。

## 说明/提示

### 样例解释

在第一个测试用例中，$x$ 的一个最优选择是 $3$。FJ 可以执行 $10$ 次操作使得 $a = [12, 12, 21, 3, 12]$。

### 子任务

- 测试点 2：$N \le 1000$ 以及 $M \le 1000$。
- 测试点 3：$N\le 1000$。
- 测试点 4-5：$M\le 10^5$。
- 测试点 6-16：没有额外限制。

## 样例 #1

### 输入

```
2
5 9
15 12 18 3 8
3 69
1 988244353 998244853```

### 输出

```
10
21```

# 题解

## 作者：fanminghao000 (赞：9)

## 题解

简单分析一下题目，发现 $x$ 是什么并不重要，或者说 $x$ 就是我们要去探究的东西。 $x$ 告诉我们，只要满足所有的数关于 $M$ 同余即可（余数就是 $x$ ）。于是想到将所有数直接放到模 $M$ 意义下处理，将“操作为同余”转化为“操作为同一个数”。

将所有数随意转化为同一个数（下称转化数，即 $x$ ），求花费和最小，其实就是[货仓选址问题](https://www.luogu.com.cn/problem/P10452)。结论是直接选中位数（若有偶数个元素，则最中间两个元素间任意一个数都可以）作为转化数，证明如下：

先讨论元素个数为奇数情况。设选定的转化数左边有 $a$ 个元素，右边有 $b$ 个，当转化数为中位数时，有 $a=b$  。

若向左移动一个数，则 $b>a$ 。同时所有转化数左边的元素贡献减一，右边的贡献加一，即总贡献加上了 $b-a>0$  ，不如放在中位数。往右同理。所以选择中位数是最佳方案。

对于元素个数为偶数情况，因为转化数放在任意两元素间，两元素创造的贡献和恒定，即两元素距离。所以可以将中间两元素看做一个点，转化为奇数情况。在具体处理时，直接选取两元素的任意一个作为转化数即可。

然而本题稍微特殊一些，因为在模 $M$ 意义下讨论，一个数既可以变小也可以变大，都能到达同余值，即所有元素都在一个环上，每个数都可以做中位数。所以要断环成链处理，统计可以用前缀和优化。具体实现可以看代码（虽然写的有点抽象）。



## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
int n,m;
int a[200010],b[400010],pre[400010];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T; 
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i]%m;
		int ans=1e18;
		sort(b+1,b+n+1);
		for(int i=1;i<=n;i++) b[i+n]=b[i]+m;//断环成链处理 
		for(int i=1;i<=2*n;i++) pre[i]=pre[i-1]+b[i];//前缀和优化 
		for(int i=1;i<=n;i++){
			int pos=(n/2)+(n%2==1)+i-1;//找中位数位置，分类讨论奇偶 
			int qian=(pos-i)*b[pos]-(pre[pos-1]-pre[i-1]);
			int hou=(pre[i+n-1]-pre[pos])-(i+n-pos-1)*b[pos];
			ans=min(ans,qian+hou);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：XGTD (赞：4)

# P11671 [USACO25JAN] Farmer John's Favorite Operation S 题解

## Preface

这场太难了。前两题做出来之后本来以为进金稳了，结果剩 45 分钟第三题愣是第一个点都没拿到。700 分数线也太高了吧。

这题主要是二分查找和前缀和断环为链两种思路，**但是**我有第三种 = 差分斜率。

好吧可能是因为我 USACO 最近刷的实在太多了~~而且还没过~~，但是真的没人发现和[这](https://www.luogu.com.cn/problem/P4264)几乎做法一样吗？

## Problem Statement

[p11671](https://www.luogu.com.cn/problem/P11671)。

## Solution

首先发现因为要取模 $x$ 显然只能在 0 和 $m$ 之间。

因此问题就是求最优的 $x$ 使得 $n$ 个对于 $x$ 的分段函数的和最小。

然后看到要求一个函数最值我直接开始~~乱搞~~三分，喜提零分。因为显然不但总函数不是单峰的，单个数的函数都不是，因为一个数既可以加又可以减只要最后余数是零。

此时玩几组数据突然发现似乎每一个函数 $i$ 只有两个断点，当 $x$ 等于 $a_i$ 模 $m$ 时，和当加到余数为零比减到余数为零（或者反过来）更快时。

这时候在画几个函数出来发现真是这样，只不过断点虽然固定，但是函数最后的形状还是要分讨，主要看 $m$ 的奇偶性和 $a_i$ 模 $m$ 相比于 $\dfrac{m}2$ 的大小。

再进一步，发现对于全部 $i$ 个子函数的和组成的 $sum$ 函数，我们其实可以用差分维护它的斜率，因为它最多变化 $2 \cdot n$ 次。因此把每一个断点记作一个 $event$ 放入一个数组，并按 $x$ 从小到大扫，记录当前斜率，用它出（和上个断点的位置及函数值）算当前的函数值。对于全部 $2n$ 个断点上的值求 $\min$ 就是答案。

代码里有很多注释。

## Code


```cpp
/*
differenciating slope??? not sure if it's an actual thing
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, a[200005], ans, sum, slo;
vector< pair<int, pair<int, int> > > event;
//at most 3 each
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		//when, and by how much
		sum = 0;
		slo = 0;
		ans = INT_MAX;
		while(event.size())event.pop_back();
		for(int i = 1; i <= n; i++){
			cin>>a[i];
		}
		for(int i = 1; i <= n; i++){
			int re = a[i] % m;
			int b1 = re;
			int b2;
			if(m % 2 == 0){
				if(re <= (m / 2))b2 = re + (m / 2);
				else b2 = re - (m / 2);	
			}else{
				if(re <= (m / 2))b2 = re + (m / 2);
				else b2 = re - (m / 2 + 1); 
			}
			//b1 and b2 are the two break points
			sum += min(re, m - re);
			//sum = the answer when x == 0 
			if(b1 > b2)slo += 1;
			else slo -= 1;
			//determines the inital slope, upwards or downwards
			if(m % 2 == 1){
				event.push_back({b2, {-1, i}});
				//reach b2, stay
				event.push_back({b2 + 1, {-1, i}});
				//start decreasing				
			}else{
				event.push_back({b2, {-2, i}});
				//start decreasing right away
			}
			event.push_back({b1, {2, i}});
			//reach the remainder itself, start growing again
		}
		sort(event.begin(), event.end());
		int la = 0;
		ans = sum;
		for(int i = 0; i < event.size(); i++){
			int tim = event[i].first;
			int val = event[i].second.first;
			int id = event[i].second.second;
			//tim = time of this event
			//val = how much is changed
			//id = who's changed. not really necessary
			sum += (tim - la) * slo;
			//find current sum
			la = tim;
			ans = min(sum, ans);
			//compare with answer
			slo += val;
			//change slope
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

## After thought

真的和 2018 银组的 [Teleportation](https://www.luogu.com.cn/problem/P4264) 好像呀！唉，提刷多了就是这样。建议大家都去看一下那道题。

求赞。

---

## 作者：Su777 (赞：3)

来一发神奇二分做法。

我的整体思路是 $O(n)$ 枚举 $x$（经过证明，只有 $n$ 种情况），然后 $O(\log n)$ 求出每一种 $x$ 对应的答案。

首先将 $a$ 数组全部对 $m$ 取模，**并排序**。这样就得到了一个值域为 $[0,m-1]$ 的数组。容易发现，$x$ 一定等于某个 $a_i$。这样，$x$ 的值域也确定为 $[0,m-1]$。于是，$a_i-x$ 的值域也确定了：$[0-(m-1),(m-1)-0]$ 即 $[-(m-1), m-1]$。

我们的目标是把 $a_i$ 变成 $m$ 的倍数，不妨看它的几何意义，即把数轴上移动到最靠近它的 $m$ 倍数点上。又由 $a_i-x$ 的值域可知，最后移动到的 $m$ 倍数点只有三个：$-m$，$0$ 和 $m$。这样，我们可以把**减去 $x$ 之后**，数组中的所有数字**从小到大**分为五类：

1. $-m < a_i-x < 0$，且到 $-m$ 的距离更近，此时有 $|(a_i-x) - (-m)| < |(a_i-x) - 0|$，解得 $a_i<\cfrac{2x-m}{2}$。
2. $-m < a_i-x < 0$，且到 $0$ 的距离更近，此时有 $|(a_i-x) - (-m)| \geq |(a_i-x) - 0|$，解得 $a_i\geq \cfrac{2x-m}{2}$。
3. $a_i-x=0$。
4. $0<a_i-x<m$，且到 $0$ 的距离更近，此时有 $|(a_i - x) - 0| < |(a_i - x) - m|$，解得 $a_i<\cfrac{2x+m}{2}$。
5. $0<a_i-x<m$，且到 $m$ 的距离更近，此时有 $|(a_i - x) - 0| \geq |(a_i - x) - m|$，解得 $a_i\geq \cfrac{2x+m}{2}$。

然后就可以通过 `lower_bound` 和 `upper_bound` 确定这五类数的区间（由于数组 $a$ 单调递增，这五种数一定对应着数组上五个连续的区间，这五个区间无重叠、无遗漏地从左到右组成了数组 $a$）。然后分别统计答案：

1. 答案为 $|(a_i-x)-(-m)|=a_i-x+m$，三项拆贡献分别计算。
2. 答案为 $|(a_i-x)-0|=x-a_i$，两项拆贡献分别计算。
3. 答案为 $0$。
4. 答案为 $|(a_i-x)-0|=a_i-x$，两项拆贡献分别计算。
5. 答案为 $|(a_i-x)-(-m)|=m - a_i + x$，三项拆贡献分别计算。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5 + 10;
ll T, n, m, a[2 * N], s[2 * N];
inline ll calc(ll x) {
    return min(x % m, m - x % m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) {
            cin >> a[i];
            a[i] = (a[i] % m);
        }
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i ++) {
            s[i] = s[i - 1] + a[i];
        }
        ll ans = 1e18;
        for (int i = 1; i <= n; i ++) {
            if (i != 1 && a[i] == a[i - 1]) continue;
            ll x = a[i], tmp = 0;
            ll idx = upper_bound(a + 1, a + n + 1
            , floor((2.0 * x - 1.0 * m) / 2.0)) - a - 1;
            if (idx > 0) {
                tmp += s[idx] - idx * x + idx * m;
            }
            if (idx + 1 <= i - 1) {
                tmp += abs(s[i - 1] - s[idx] - (i - 1 - idx - 1 + 1) * x);
            }
            ll idx2 = upper_bound(a + 1, a + n + 1, x) - a;
            ll idx3 = upper_bound(a + 1, a + n + 1
            , floor((2.0 * x + 1.0 * m) / 2.0)) - a - 1;
            if (idx2 <= idx3) {
                tmp += s[idx3] - s[idx2 - 1] - (idx3 - idx2 + 1) * x;
            }
            if (idx3 + 1 <= n) {
                tmp += m * (n - idx3) - (s[n] - s[idx3] - x * (n - idx3));
            }
            ans = min(ans, tmp);
        }
        cout << ans << "\n";
    }
    return 0;
}

```

---

## 作者：ThisIsLu (赞：2)

神金做法。

考虑每一个 $a_i$ 的贡献 $\max\{(a_i-x)\bmod M,M-(a_i-x)\bmod M\}$，显然可以对 $a_i$ 模 $M$，并限制 $0\le x <M$。

仔细观察可以发现，当 $0 \le x,a_i <M$ 时， $\max\{(a_i-x)\bmod M,M-(a_i-x)\bmod M\}=M-|x-(a_i-M/2)|+|x-a|-|x-(a_i+M/2)|$。

然后就转化成了绝对值最值问题，就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int N=2e5;
struct node{
    int val,k;
    friend bool operator<(node x,node y){
        return x.val<y.val;
    }
} b[N*3+5];
void solve(){
    cin>>n>>m;
    int cnt=0;
    long long sum=0;
    for(int i=1;i<=n;i++){
        int ai;
        cin>>ai;
        ai%=m;
        sum-=(ai<<1);
        cnt++;
        b[cnt].k=-1;
        b[cnt].val=(ai<<1)-m;
        cnt++;
        b[cnt].k=1;
        b[cnt].val=(ai<<1);
        cnt++;
        b[cnt].k=-1;
        b[cnt].val=(ai<<1)+m;
    }
    sort(b+1,b+cnt+1);
    int num=n;
    long long ans=LONG_LONG_MAX;
    for(int i=1;i<=cnt;i++){
        sum-=2ll*b[i].k*b[i].val;
        num+=2*b[i].k;
        int l,r;
        if(b[i].val>=0) l=max(0ll,(((b[i].val+1)>>1)<<1));
        else l=max(0ll,b[i].val/2*2);
        if(b[i+1].val>=0) r=min((m<<1)-2,(b[i+1].val>>1)<<1);
        else r=min((m<<1)-2,-(((1-b[i+1].val)>>1)<<1));
        if(l<=r){
            if(num>=0){
                ans=min(ans,num*l+sum);
            }
            else{
                ans=min(ans,num*r+sum);
            }
        }
    }
    cout<<(ans>>1)+n*m<<"\n";
}
signed main(){
    int T=1;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：littlebug (赞：2)

## Solution

题意显然可以转化为求一个 $x$ 使得 $a_i \pm b_i \equiv x \pmod m$ 且 $\sum b_i$ 最小。

于是先给 $a_i$ 都模上一个 $m$，然后 $x$ 显然取中位数时最小。

但是发现这样没过样例，原因是有可能把左边的数加上 $m$ 放到右边（即小的数加上 $m$ 变成大的数），答案可能会更小，也就是说构成了一个环。

于是先倍长，那么首先可以想到一个 $O(n^2)$ 的暴力求 $n-1$ 种方案每种方案的答案，最后取最小值。

发现这个做法没问题，然后优化是简单的，因为每次将最左边元素移到最右边，答案的变化是有规律的。

考虑将原序列划分为 $4$ 个部分，最左边 $1$ 个元素和其移动到最右边之后的新元素是 $2$ 个部分，还有中间以两次中位数中间位置为分割线划分为 $2$ 个部分，就像这样：

```
n = 5
1 | 2 3 | 4 5 | 6 7
      ^-->^（中位数由 3 变为 4
```

分这 $4$ 块维护答案即可，这个就简单了。

```cpp
dt=a[(n+1>>1)+i]-a[(n+1>>1)+i-1]; // 中位数变化量
now+=((n-1)>>1)*dt; // 第二部分，考虑有几个数跟中位数的距离增加了
now-=(n>>1)*dt; // 第三部分，考虑有几个数跟中位数的距离减少了
now-=a[(n+1>>1)+i-1]-a[i]; // 第一部分，这个元素被删除（或者说被移动到第四部分了）
now+=a[i+n]-a[(n+1>>1)+i]; // 第四部分，从第一部分移过来的那个元素
```

## Code

```cpp
int n,m,a[MAXN<<1];

il void solve(int __Ti)
{
    read(n,m),_::r(a,n);
    rep(i,1,n) a[i]%=m;
    sort(a+1,a+n+1);
    rep(i,1,n) a[i+n]=a[i]+m;

    int ans=9e18;
    int x=a[n+1>>1],now=0;
    rep(i,1,n) now+=abs(x-a[i]);
    ans=min(ans,now);

    int dt;
    rep(i,1,n)
    {
        dt=a[(n+1>>1)+i]-a[(n+1>>1)+i-1];
        now+=((n-1)>>1)*dt; // mid left
        now-=(n>>1)*dt; // mid right
        now-=a[(n+1>>1)+i-1]-a[i]; // left
        now+=a[i+n]-a[(n+1>>1)+i]; // right

        ans=min(ans,now);
    }

    write(ans,'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：ohjun (赞：1)

## 思路分析
因为题目中涉及的参数过多，首先考虑简化题意。因为 $x$ 可以为任意整数，显然可以把题目转化为使所有数对 $m$ 同余。这样我们就不需要再考虑 $x$ 了。但此时写出来的方程中带有取模，难以求解，可以直接将所有数对 $m$ 取模后存到新的数组，问题转化为使这个新数组在一定操作后的所有数相等。

那么问题就转化成了绝对值最值问题，设那个相等数为 $x$，则 $x$ 就是数组中所有数的中位数（证明可以看看我的这篇题解的 [Part 2](https://www.luogu.com.cn/article/i23e4h4b)）。但这题并没有那么简单，因为新数组的一个数是对 $m$ 取模的结果，所以往反方向走也可以到达 $x$。也就是说这些点在一个圆上，而对于一个圆，我们无法找到中位数。尝试将圆转化成长度为 $n$ 的数轴，将新数组排序后往后面添加 $n$ 个数，其中 $A_{n + i} = A_i + m$（取到这些点表示走他们对应原点的反方向）。接下来枚举数轴的起点，不难通过前缀和在常数时间内求出当前数轴的总花费。总时间复杂度为排序复杂度。
## Code
```cpp
#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 2e5+ 5;
int t, n, m;
int A[maxn << 1];
ll sum[maxn << 1];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cin >> t;
	while(t--)
	{
		std::cin >> n >> m;
		int num;
		for(int i = 1; i <= n; i++)
		{
			std::cin >> num;
			A[i] = num % m;
		}
		std::sort(A + 1, A + n + 1);
		for(int i = 1; i <= n; i++)
			A[n + i] = A[i] + m;
		memset(sum, 0, sizeof(ll) * (n + 1));
		for(int i = 1; i <= (n << 1); i++)
			sum[i] = sum[i - 1] + A[i];
		ll ans = LONG_LONG_MAX;
		for(int i = 1; i <= n; i++)
		{
			int mid = i + (n >> 1);
			ll l = ll(mid - i) * A[mid] - sum[mid - 1] + sum[i - 1];
			ll r = sum[i + n - 1] - sum[mid] - ll(i + n - 1 - mid) * A[mid];
			ans = std::min(ans, l + r);
		}
		std::cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：w150432 (赞：1)

题意是对与数组 $a$ 进行一些修改，修改后让所有元素   $m \mid a_i - x$，修改的次数就是无聊值，我们想要知道最小的修改次数。

我觉得我写的应该就是最简单的题解了

输入 $a$ 数组然后把他全部模 $m$ 放到一个 $dif$ 数组里面，进行排序，然后 $dif$ 数组下标为 $i + n$ 的元素等于 $a_i + m$ 。然后再创建一个 $dif$ 数组的前缀和数组。

创建完了以后直接遍历所有可能的答案区间并且二分出无聊值最小的然后选择无聊值最小的区间。为什么要二分吗，首先想一下暴力，我们需要的遍历 $N$ 个区间，然后暴力区间内可能的 $N$ 个答案得位置，注意到 $N$ 最坏可能是 $2 \times 10^5$ ，而 $O(n^2)$ 的时间复杂度显然是不行的，



### AC 代码

```
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 10;

int t, n, m;
int a[N], dif[2 * N];
int sum[2 * N];

signed main()
{
    scanf("%lld", &t);

    while (t --)
    {
        scanf("%lld%lld", &n, &m);

        for (int i = 1 ; i <= n ; i ++ )
        {
            scanf("%lld", &a[i]);
            dif[i] = a[i] % m;
        }

        sort(dif + 1, dif + n + 1);

        for (int i = 1 ; i <= n ; i ++ ) dif[n + i] = dif[i] + m;

        for (int i = 1 ; i <= 2 * n ; i ++ )
            sum[i] = sum[i - 1] + dif[i];

        int ans = 1e18, l, r, pos;
        for (int i = 1 ; i <= n ; i ++ )
        {
            l = i, r = n + i - 1, pos = i;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (dif[mid] - dif[i] <= dif[i] + m - dif[mid])
                {
                    pos = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }
            ans = min(ans, (sum[pos] - sum[i]) - (pos - i) * dif[i] + (n + i - 1 - pos) * (dif[i] + m) - (sum[n + i - 1] - sum[pos]));
        }

        printf("%lld\n", ans);
    }

    return 0;
}
```

---

## 作者：Inv_day_in_R (赞：0)

这道题首先将所有数对 $m$ 取模，接下来考虑简化版，如果都变成一样的数，那么根据我们初一就学过的直线上货舱选址，中位数是最优的。但实际上本题中一个数等于 $m$ 后又会重新返回 $0$，这里的货舱选址是在环上的，一般的方法行不通。

既然在环上的话，不难想到破环成链。取模后排序，之后将原数组复制一倍，但是这一倍每个数都要加上 $m$，用来模拟圆周上再转一圈。接下来枚举每一种圆的断开，也就是现在每一个连续 $n$ 个数的一组，直接套公式即可。为了方便计算，还需要使用前缀和优化。

具体实现看代码：


```cpp
void solve(){
	int n,m;
	cin>>n>>m;
	vector<int>v(n),sum(2*n+1);
	cin>>v;
	for(int i=0;i<n;i++)v[i]%=m;
	sort(all(v));
	for(int i=0;i<n;i++)v.push_back(v[i]+m);
	for(int i=0;i<2*n;i++)sum[i+1]=sum[i]+v[i];
	int mn=1e18;
	for(int l=1,r=n;r<=2*n;l++,r++){
		int x=l+r>>1;
		int a=(x-l+1)*v[x-1]-sum[x]+sum[l-1];
		int b=sum[r]-sum[x]-(r-x)*v[x-1];
		mn=min(mn,a+b);
	}
	cout<<mn<<'\n';
}
```

---

## 作者：TZR087_42_Chaser (赞：0)

[P11671 [USACO25JAN] Farmer John's Favorite Operation S](https://www.luogu.com.cn/problem/P11671)

upd 2025.2.7：更正一些笔误，增加一些补充。

蒟蒻第一篇题解，求过。

## $\text{Part}.0$ 闲话

这题我的思路非常离谱，与官方题解出入比较大。官方题解用二分，我用前缀和。

## $\text{Part}.1$ 思路

注意这一句：

以使得对于所有的 $1 \le i \le N$，$a_i−x$ 均可被 $M$ 整除。

意思就是：

$\forall i\in [1,N]\cap \mathbb{N},a_i \equiv x\pmod M $（其中 $x$ 为任意整数）

因此先对 $a_i$ 进行取模操作。现在，$\forall i\in [1,N]\cap \mathbb{N},0 \le a_i < M$。

显然，原来的每一个 $a_i$，减去 $M$ 或加上 $M$，模 $M$ 同余。如果要把所有数变成 $k$，同时无聊值最少，那么对于 $a_i$，自然是取：

$$\min(|a_i-M-k|,|a_i-k|,|a_i+M-k|)$$

注意：将 $a_i$ 变成 $a_i \pm pM$（$p \in (1,+\infty)\cap \mathbb{N}$）再变成 $k$ 没有意义，只会增大无聊值。

所以，我们可以新建一个数组，记为 $b$，大小为 $3 \times N$，存放所有的 $a_i-M,a_i$ 与 $a_i+M$。

最后从小到大排序。

以样例 $1$ 为例，执行完上述操作后：

$$b=[-9,-6,-6,-3,-1,0,3,3,6,8,9,12,12,15,17]$$

然后对 $b$ 数组做一次差分操作，差分的结果存入 $d$ 数组，其中 $d_i=b_{i+1}-b_i$。

则对于样例 $1$，

$$d=[3,0,3,2,1,3,0,3,2,1,3,0,3,2]$$

接下来枚举最终统一变为的数，用绝对值的几何意义可知，对于第 $i$ 个数作中间数时，当 $n$ 为偶数时，可变为 $\forall k \in[b_i,b_{i+1}]$，不妨就变为 $b_i$；当 $n$ 为奇数时，仅能变为 $b_i$。因此，枚举 $b_i$ 为中间数即可。

以上述 $b_3=-6$ 为例，将 $b_1$ 变为 $b_3$，需要 $d_1+d_2$ 点无聊值，将 $b_2$ 变为 $b_3$，需要 $d_2$ 点无聊值，将 $b_4$ 变为 $b_3$，需要 $d_3$ 点无聊值，将 $b_5$ 变为 $b_3$，需要 $d_3+d_4$ 点无聊值。

所以，$b_3=-6$ 作中间数时，答案为 $b_1+2b_2+2b_3+b_4$。只看各项系数，为 $1,2,2,1$。

同理，对于上述 $b$，任取一个数作中间数，答案为 $b_{n-2}+2b_{n-1}+2b_n+b_{n+1}$。

观察下表：（表格中数为系数）

|中间数 \ $i$|$1$|$2$|$3$|$4$|$5$|$6$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$b_3$|$1$|$2$|$2$|$1$|||
|$b_4$||$1$|$2$|$2$|$1$||
|$b_5$|||$1$|$2$|$2$|$1$|

可以发现，中间数从 $b_3$ 变为 $b_4$，$d_1$ 和 $d_2$ 的系数减 $1$，$d_4$ 和 $d_5$ 的系数加 $1$。类似的，中间数从 $b_4$ 变为 $b_5$，$d_2$ 和 $d_3$ 的系数减 $1$，$d_5$ 和 $d_6$ 的系数加 $1$。

归纳得到：对于上述 $b$，中间数从 $b_i$ 变为 $b_{i+1}$，$d_{i-2}$ 和 $d_{i-1}$ 的系数减 $1$，$d_{i+1}$ 和 $d_{i+2}$ 的系数加 $1$。

那么，**对于任意奇数，都有：中间数从 $b_i$ 变为 $b_{i+1}$，$d_{i-\lfloor \frac{n}{2} \rfloor}$ 到 $d_{i-1}$ 的系数减 $1$，$d_{i+1}$ 到 $d_{i+\lfloor \frac{n}{2} \rfloor}$ 的系数加 $1$。**

类似的，$n=6$ 时得到下表：

|中间数 \ $i$|$1$|$2$|$3$|$4$|$5$|$6$|$7$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$b_3$|$1$|$2$|$3$|$2$|$1$|||
|$b_4$||$1$|$2$|$3$|$2$|$1$||
|$b_5$|||$1$|$2$|$3$|$2$|$1$|

得到结论：

**对于任意偶数，都有：中间数从 $b_i$ 变为 $b_{i+1}$，$d_{i-\frac{n}{2}}$ 到 $d_{i}$ 的系数减 $1$，$d_{i+1}$ 到 $d_{i+\frac{n}{2}}$ 的系数加 $1$。**

区间求值，用前缀和维护即可。每次区间加减的时间复杂度为 $\text{O}(1)$，每组数据的复杂度为 $\text{O}(n+3n+n \log n+n+n)=\text{O}(n \log n)$，总复杂度为 $\text{O}(\sum n \log n)$，常数较小，可通过本题。

## $\text{Part}.2$ 代码

[AC 记录](https://www.luogu.com.cn/record/201434641)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,sum,ans,a[600005],d[600005];
void solve(){
	sum=0;
	ans=1e18;
	scanf("%lld%lld",&n,&m);
	for(int i=n+1;i<=2*n;i++){
		scanf("%lld",&a[i]);
		a[i]%=m;
		a[i-n]=a[i]-m;
		a[i+n]=a[i]+m;
	}
	sort(a+1,a+3*n+1);
	for(int i=1;i<3*n;i++){
		d[i]=a[i+1]-a[i];
	}
	for(int i=1;i<n;i++){
		sum+=d[i]*min(i,n-i);
	}
	ans=min(ans,sum);
	for(int i=2;i<=2*n+1;i++){
		sum-=a[i+n/2-1]-a[i-1];
		sum+=a[i+n-1]-a[i+n-1-n/2];
		ans=min(ans,sum);
	}
	printf("%lld\n",ans);
}
main(){
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```

如果各位有意见或 hack 的话，欢迎批评指正。

---

## 作者：I_will_AKIOI (赞：0)

不难发现最优解一定是 $x\le m$，否则 $(a_i-x) \bmod m$ 会出现循环。因此可以枚举 $x$，统计操作次数，时间复杂度为 $O(nm)$，可以通过测试点 $2$。

接着发现我们并不需要枚举所有的 $x\le m$。我们令 $f(x)$ 为对 $x$ 进行加 $1$ 或 $-1$，使 $x\bmod m=0$ 的最小操作数，$g(x)$ 为仅对 $x$ 进行加 $1$ 使 $x\equiv y\pmod m$ 的最小操作数。容易发现 $f(x)=\min(x,m-x)$，假设其定义域为 $x\in[0,m)$，则当 $x\in [0,\frac{m}{2}]$（向下取整），则 $f(x)$ 随着 $x$ 的增大而增大，当 $x\in[\frac{m}{2}+1,m)$ 时，其值随 $x$ 的增大而减小，也就是存在单调性，所以在函数的两个顶点肯定能取到最大值。因此我们只需要枚举 $x=g(a_i,0)$ 和 $g(a_i,\frac{m}{2})$ 即可，时间复杂度为 $O(n^2)$，可以通过测试点 $2$ 和 $3$。

发现每次枚举 $x$ 后都需要重复计算一遍贡献，开销很大，先给暴力做法需要枚举的 $x$ 从小到大排序，接着快速计算相邻两个 $x$ 对答案的影响。考虑把 $f(x)$ 拆成两部分，维护 $x\in [0,\frac{m}{2}]$ 和 $x\in[\frac{m}{2}+1,m)$ 的数量，记作 $cnt1$ 和 $cnt2$。由于相邻两个 $x$ 之间 $cnt1$ 和 $cnt2$ 的数量不变，当 $x\leftarrow x+1$ 时，所有 $x\in [0,\frac{m}{2}]$ 的 $f(x)$ 都会加 $1$，否则都会 $-1$。因此对答案会增加 $(cnt1-cnt2)(x_{cur}-x_{last})$，接着更新 $cnt1$ 和 $cnt2$ 就好了。

但是注意到 $m$ 为奇数时，$f(\frac{m}{2})=f(\frac{m+1}{2})$，所以记得特判。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n,m,mid,ans,sum,cnt1,cnt2,last,a[N];
map<int,int>v0,v1;
vector<int>v;
int dis(int x,int y)//g(x)
{
	if(x<=y) return y-x;
	return (y-x+m)%m;
}
void solve()
{
	v0.clear(),v1.clear(),v.clear();
	cnt1=cnt2=last=sum=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]%=m,sum+=min(a[i],m-a[i]);
	ans=sum;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<(m+1)/2) cnt1++;
		else cnt2++;
	}
	for(int i=1;i<=n;i++)
	{
		int d1=dis(a[i],(m+1)/2),d2=dis(a[i],0);
		v0[d1]++,v1[d2]++;
		v.push_back(d1),v.push_back(d2);
	}
	sort(v.begin(),v.end());
	v.resize(unique(v.begin(),v.end())-v.begin());
	if(v[0]==0) v.erase(v.begin());
	for(int now:v)
	{
		sum+=(cnt1-cnt2)*(now-last-1);
		if(m&1) sum+=cnt1-v0[now]-cnt2;
		else sum+=cnt1-cnt2;
		ans=min(ans,sum);
		cnt1-=v0[now]-v1[now],cnt2+=v0[now]-v1[now];
		last=now;
	}
	cout<<ans<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

我居然这个题上还想了一会，可能是数据结构题做多导致思维钝化了？

由于模意义下数轴是个环，因此问题几何意义如下：

> 在长度为 $m$ 的环上给定 $n$ 个点，选出点 $x$ 使得每个点离 $x$ 的距离和最小。

这个问题在链上可以直接取中位下标，在环上先枚举断一条边就转化为链上问题了。前缀和拆贡献。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int T, n, m;
long long pr_a[N * 2], a[N * 2];
inline void sol()
{
	cin >> n >> m; long long res = 1e18;
	for(int i = 1; i <= n; ++i) cin >> a[i], a[i] %= m;
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) a[i + n] = a[i] + m;
	for(int i = 1; i <= 2 * n; ++i) pr_a[i] = pr_a[i - 1] + a[i];
	for(int l = 1; l <= n; ++l)
	{
		int r = l + n - 1, mid = (l + r) >> 1;
		res = min(res, (mid - l + 1) * a[mid] - (pr_a[mid] - pr_a[l - 1]) + (pr_a[r] - pr_a[mid]) - (r - mid) * a[mid]);
	}
	cout << res << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
/*

*/
```

---

