# Water the Trees

## 题目描述

有一个长 $n$ 的数列 $h_1,h_2,\ldots,h_n$，对于每次操作，你有两种方法：
- 选择一个数，如果这是第奇数次操作，给它加 $1$，否则，给它加 $2$。
- 什么也不做（但也算一次操作）。

注：每次操作最多只能选一个数。

求至少要经过多少次操作，使得数列中所有数均相等。

## 说明/提示

$1 \le t \le 2 \cdot 10^4$；

$1 \le n \le 3 \cdot 10^5$；

$1 \le h_i \le 10^9$；

此外，保证 $t$ 组数据输入的所有 $n$ 之和不大于 $3\cdot 10^5$。

## 样例 #1

### 输入

```
3
3
1 2 4
5
4 4 3 5 5
7
2 5 4 8 3 7 4```

### 输出

```
4
3
16```

# 题解

## 作者：Exber (赞：4)

赛时被家长强制睡眠没做出来 /kk

## 做法

二分答案。

首先观察到答案有单调性，因为能在 $n$ 天内完成的话在 $n+1$ 天内肯定能完成，只要最后一天跳过即可。那么容易想到二分答案。

考虑判定在 $n$ 天内是否可以让树都恰好长到 $val$。显然让树长高 $2$ 的天数为 $\left\lfloor\dfrac{n}{2}\right\rfloor$，让树长高 $1$ 的天数则是 $\left\lceil\dfrac{n}{2}\right\rceil$。枚举每一棵树 $i$，尽可能的让树长高 $2$，实在不行再让树长高 $1$ 即可。最后若所有树都满足了条件那么就可行，否则不可行。

接下来考虑 $val$ 的取值。注意到因为有让树长高 $2$ 的日子，所以 $val$ 不能只取所有树高的最大值 $mx$，$val=mx+1$ 的情况也要判一下。而 $val\ge mx+2$ 的情况就可以忽略了，因为次高的树一次长高后高度最高为 $mx+1$。

## AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <cstring>

using namespace std;

struct node
{
};

int n;
long long a[1919810];

inline bool check(long long days,int val)
{
	long long cnt1=(days+1)/2,cnt2=days/2;
	for(int i=1;i<=n;i++)
	{
		long long ned=min((long long)(val-a[i])/2,cnt2);
		cnt2-=ned;
		cnt1-=val-a[i]-ned*2;
	}
	return cnt2>=0&&cnt1>=0;
}

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	long long l=0,r=1e17,ans=0;
	while(l<=r)
	{
		long long mid=l+r>>1;
		if(check(mid,a[n])||check(mid,a[n]+1))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	printf("%lld\n",ans);
}

int main()
{
	int _=1;
	scanf("%d",&_);
	while(_--)
	{
		slove();
	}
	return 0;
}
```

---

## 作者：glorious_dream (赞：3)

### 题意描述：

给定 $n$ 棵树的高度，奇数次操作让树长 $1$ 米，偶数次操作让树长 $2$ 米，求最少步数使树高相同。

### 算法分析：

我们发现，只有两种情况，奇数次和偶数次。那么，可以贪心来考虑。

可以发现，设定一个目标高度，显然每棵树有两种情况，要么差是偶数，要么差是奇数。

这时，偶数我们就可以在偶数次操作，奇数可以在奇数次操作。但最后肯定会剩余某些树，要么是全差奇数次，要么是全差偶数次。

所以说，如果需要 $+2$ 的次数多，就尽可能把 $+2$ 分给 $+1$。

我们可以 $3$ 个 $+2$ 为一组，为什么呢？可以发现，等于 $2$ 个 $+1$ 和 $2$ 个 $+2$，这时再去贪心求解，答案就出来了。

### 总代码：

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
	return x*f;
}
inline void print(int x){
	if(x/10) print(x/10);
	putchar(x%10+'0');
}
const int M = 3e5+10;
int t,n;
int a[M];
inline int work(int maxn){
	int cnt1=0,cnt2=0;
	for(re int i(1) ; i<=n ; ++i){
		cnt1 += (maxn-a[i])%2;
		cnt2 += (maxn-a[i])/2; //贪心求解
	}
	int tmp = cnt2 - cnt1;
	if(tmp >= 2) cnt1+=(tmp+1)/3*2,cnt2-=(tmp+1)/3;
	if(cnt1 > cnt2) return cnt1*2-1;
	else return cnt2*2;
}
signed main(){
	t=read();
	while(t--){
		int maxn=0;
		n=read();
		for(re int i(1) ; i<=n ; ++i){
			a[i] = read();
			maxn = max(maxn,a[i]);
		}
		printf("%lld\n",min(work(maxn),work(maxn+1)));
      //解释一下为什么要两次
      //要么是奇数多一个，要么就是相同，求最小的，肯定是最优解
	}
	return 0;
}
```


---

## 作者：Hovery (赞：2)

## Problem

[Water the Trees](https://www.luogu.com.cn/problem/CF1661C)

## Sol

让所有数相同，首先就是让它们的奇偶性相同。

先让整个序列都变成奇数/偶数。

然后找到整个序列的最大值，然后枚举每个数，求它改变后和最大值差多少再除以 $2$ 即可。

你就可以写出如下代码（下面讲的任何东西都是针对偶数，奇数自己举一反三一下即可）。

```cpp
for (int i = 1;i <= n;i++)
{
    if (a[i] & 1)
    {
        x++;//x表示+1要多少次。
        Max = max(Max, a[i] + 1);
    }
    else Max = max(Max, a[i]);
}
for (int i = 1;i <= n;i++)
{
    y += (Max - a[i]) / 2;//y表示+2要多少次。
}
```

$x\times2-1$ 是加一加到 $x$ 次的时间。

$y\times2$ 是加二加到 $y$ 次数的时间。

然后答案就是 $\max(x\times2-1, y\times2)$ 了吗？

这样显然是错的，因为两次加一相当于一次加二。

那么 $x$ 每加上一次 $2$，$y$ 就能减少 $1$。

这样的话 $y\times2$ 和 $x\times2-1$ 之间的差会减少 $6$。

那肯定是越这两个值越接近越好。

设 $D = y\times2-(x\times2-1)$。

那么差值最小只会在下列这两种情况。

$1.x=x+2\times D,y=y-D$。

$2.x=x+2\times (D+1),y=y-D-1$。

然后判断一下哪个小即可，最后再在奇数和偶数之间取个最小值即为答案。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int> 
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

int n, a[300010];

int calc1()
{
    int _1 = 0, _2 = 0, Max = 0;
    for (int i = 1;i <= n;i++)
    {
        if (a[i] & 1)
        {
            _1++;
            Max = max(Max, a[i] + 1);
        }
        else Max = max(Max, a[i]);
    }
    for (int i = 1;i <= n;i++)
    {
        _2 += (Max - a[i]) / 2;
    }
    if (2 * _1 - 1 >= _2 * 2)
    return 2 * _1 - 1;
    _1 = _1 * 2 - 1;
    _2 = _2 * 2;
    int delta = _2 - _1;
    delta /= 6;
    return min(_1 + 4 * (delta + 1), max(_2 - 2 * delta, _1 + 4 * delta));
}

int calc2()
{
    int _1 = 0, _2 = 0, Max = 0;
    for (int i = 1;i <= n;i++)
    {
        if (!(a[i] & 1))
        {
            _1++;
            Max = max(Max, a[i] + 1);
        }
        else Max = max(Max, a[i]);
    }
    for (int i = 1;i <= n;i++)
    {
        _2 += (Max - a[i]) / 2;
    }
    if (2 * _1 - 1 >= _2 * 2)
    return 2 * _1 - 1;
    _1 = _1 * 2 - 1;
    _2 = _2 * 2;
    int delta = _2 - _1;
    delta /= 6;
    return min(_1 + 4 * (delta + 1), max(_2 - 2 * delta, _1 + 4 * delta));
}

void solve()
{
    cin >> n;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
    }
    cout << min(calc1(), calc2()) << '\n';
}

signed main()
{
    IOS;
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
```

---

## 作者：MiniLong (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1661C)

## 题意

给定 $n$ 个数，每次操作可以把其中 $1$ 个数加 $1$ 或加 $2$，或者什么都不做（也算一次），求最少的操作次数，使得 $n$ 个数都相同。

## 思路

首先找到一个数 $k$，使得最后的数列中每个数都为 $k$，至于 $k$ 的值是多少详见后面。

然后统计出来这个数列中对于每个 $i$ 的 $g_i = k - h_i $。

因为当要加 $2$ 时，可以先什么都不做，然后加 $2$，或者先加 $1$，间隔一次，再加 $1$。

显然，前者比后者优。

所以，我们统计出来每个 $g_i$ 与 $k$ 奇偶性不同的个数 $cnt1$，再统计 $cnt2 = \sum_{i=1}^n{\dfrac{g_i}{2}}$。

然后分类讨论。

1. $cnt1 = cnt2$

显而易见，答案为 $cnt1 \times 2$。

2. $cnt1 > cnt2$

那么因为 $cnt1$ 代表的是**只能加一**的个数，所以在加二的时候要跳过一次。

所以答案为 $cnt1 \times 2 - 1$（最后一次不用跳）。

3. $cnt1 < cnt2$

这种情况稍有些复杂。

因为在对一个数加二的同时，为了不浪费操作次数，我们也可以对其他数进行加一的操作。

所以可以以三次操作为一组（一次加二，两次加一），算出最少的操作次数，剩下的如果为 $1$，那么 $ans$ 加一就行；如果是 $2$，那么 $ans$ 加二（间隔一次，再加二）。

具体见代码。

**注意：**

$k$ 可以是这个这个数列中的**最大值**或**最大值加一**

最大值这个很好理解，那为什么也可以是最大值加一呢？

因为加一后可能能**减少操作中的间隔**，所以计算两次上述过程就好了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
};
using namespace fastio;
const int N = 3e5 + 5;
int T, n;
int a[N], g[N];
int f(int maxn){
    int cnt1 = 0, cnt2 = 0;
    for(int i = 1; i <= n; ++i){
        g[i] = maxn - a[i];
        if(g[i] % 2) cnt1++;
        cnt2 += g[i] / 2; 
    }
    if(cnt1 == cnt2) return cnt1 * 2;
    else if(cnt1 < cnt2){
        int t = (cnt2 - cnt1) * 2, k = t - t / 3 * 3;
        int ans = cnt1 * 2 + t / 3 * 2;
        if(k == 2) ans += 2;
        if(k == 1) ans++;
        return ans;
    }
    else return cnt1 * 2 - 1;
}
signed main(){
    read(T);
    while(T--){
        int maxn = 0, ans = 0;
        read(n);
        for(int i = 1; i <= n; ++i) read(a[i]), maxn = max(maxn, a[i]);
        ans = f(maxn);
        ans = min(ans, f(maxn + 1));
        writeln(ans);
    }
    return 0;
}
```



---

## 作者：Polaris_Australis_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1661C)

## 题意
给定 $n$ 棵树的高度，奇数时间让一棵树树长高 $1m$ ，偶数时间可以让一棵树长高 $2m$ ，求让所有树一样高的最少所需时间。
## 题解
我们一次可以让树长高 $1m$ 或 $2m$ ，也就是说，如果设定一个目标高度，可以把每棵树跟目标高度的差值分成 $1m$ 和 $2m$ 的部分。那么我们怎么分呢？

经过一番仔细思考，我们发现，如果让 $1m$ 的部分分的尽可能多的话，我们需要两个 $1m$ 能够合成一个 $2m$ ，那么这些所有的树我们还要分奇偶考虑，这很不好维护。所以我们把这些高度分成尽可能多的 $2m$ 。之后如果发现 $1m$ 的部分比 $2m$ 少，我们可以把一些 $2m$ 拆成 $1m$ ，实现尽可能多的配对。设 $1m$ 个数为 $num_1$ ，$2m$ 个数为 $num_2$ ，分为两种情况：

1： $num_1 > num_2$ ，答案是 $num_1 \times 2\text{ }+\text{ }1$ ；

2： $num_1 \leq num_2$ ，答案是将 $2m$ 分配部分给 $1m$ 后的答案（细节比较多，不做过多赘述，详见代码）。


------------


还有一个问题：如何设置目标高度呢？

初步的想法可能是这样的：让它们都长到跟最高的树一样高不就好了吗？嘿嘿，那你可大错特错了！

我们构造一组数据：有 $7$ 棵树，树的高度为 $1,1,1,1,1,1,2$ ，如果按照第二段的分法并把目标高度设置为 $2$ ，容易发现，有 $6$ 个 $1m$ ，没有 $2m$ 的，时间为 $11$ （符合上面的第一种情况）。如果把目标高度设置为 $3m$ ，就变成了 $6$ 个 $2m$ ， $1$ 个 $1m$ ，符合第二种情况，我们把 $2m$ 分出一部分给 $1m$ 后变成 $5$ 个 $1m$ ， $4$ 个 $2m$ ，答案也变成了 $9$ 。

那这是为什么呢？

我们考虑把目标高度设置为最高高度的漏洞：有可能有很多个 $1m$ 但几乎没有 $2m$ ，最终导致很多时间被浪费了。但有没有可能把目标高度设置成 最高高度 $+\text{ }2$ 呢？答案是不需要，证明如下：

我们按照上面所说的两种情况分开证明： **第一种情况：** 由于 $1m$ 比较多，如果把目标高度提升 $2m$ ，这些 $2m$ 会先和 $1m$ 配对，也就是补充之前的空白，而再多出来的部分只会增加时间。并没有实现更优。 **第二种情况：** 这种情况更简单，原来的那些已经完全配好对了，再加进来的只能是累赘。证明完毕。

所以我们只需要考虑把目标高度设为 最高高度 和 最高高度 $+\text{ }1$ 这两种情况比较哪种答案更小即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c&15);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>
    void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)|48);
    }
    int t,n,height[300001],tptp[300001];
    int main()
    {
        read(t);
        while(t--)
        {
            read(n);
            int maxn=0;
            for(int i=1;i<=n;++i)
            {
                read(height[i]);
                maxn=max(maxn,height[i]);
            }
            int ans=0x3f3f3f3f3f3f3f3f;
            for(int k=0;k<2;++k)
            {
                for(int i=1;i<=n;++i)
                {
                    tptp[i]=maxn-height[i];
                }
                int cmp1=0,cmp2=0;
                for(int i=1;i<=n;++i)
                {
                    cmp2+=tptp[i]/2;
                    cmp1+=tptp[i]%2;
                }
                if(cmp2>cmp1)
                {
                    int tmp=cmp2-cmp1;
                    int tp=tmp/3;
                    int tmp1,tmp2;
                    if(tmp%3==0)
                    {
                        tmp1=tp*2;
                        tmp2=tp*2;
                    }
                    else if(tmp*2%3==1)
                    {
                        tmp1=tp*2+2;
                        tmp2=tp*2+1;
                    }
                    else
                    {
                        tmp1=tp*2;
                        tmp2=tp*2+1;
                    }
                    cmp1+=tmp1;
                    cmp2-=tmp-tmp2;
                }
                ++maxn;
                ans=min(ans,max(2*cmp1-1,2*cmp2));
            }
            write(ans);
            puts("");
        }
        return 0;
    }
}
#undef int
int main()
{
    return Std::main();
}
```


---

## 作者：yeshubo_qwq (赞：0)

题外话：我们老师造的数据居然放过了[这个代码](https://www.luogu.com.cn/paste/xeeasq1v)……

思路：贪心。

答案一定是让所有树的高度都到达树中最高的高度的最优解和让所有树的高度都到达树中最高的高度 $+1$ 的最优解。

为什么？

因为到达树中最高的高度 $+2$ 相当于在到达树中最高的高度的基础上给每棵树又加了 $2$；到达树中最高的高度 $+3$ 相当于在到达树中最高的高度 $+1$ 的基础上给每棵树又加了 $2$……依此类推，都有浪费。

然后就是考虑如何求出最优解。

首先，对于每一棵树，我们最贪心的想法是不断用 $+2$，最后如果有余数 $1$ 再用 $+1$ 来补足。

但是，受到题目的限制 $+1$ 和 $+2$ 必须交替，否则只能不操作，因此，$+1$ 和 $+2$ 的差尽可能的小，答案才是最优的。

由此，求出 $+1$ 和 $+2$ 用的次数以后，如果 $+2$ 有多，就尽可能的将 $+2$ 的一部分分配给 $+1$，最优化答案。

考虑将 $3$ 个 $+2$ 视为一组（总共加六，算上不操作的天数为 $6$ 天），将他们换成 $2$ 个 $+1$ 和 $2$ 个 $+2$（总共同样加六，但天数仅为 $4$ 天）。

最后计算答案就很简单了，如果 $+1$ 用的多，因为先执行的是 $+1$ 操作，答案就是 $+1$ 用的次数 $\times 2-1$，否则就是 $+2$ 用的次数 $\times 2$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,max_,a[300005]; 
int solve(int h){
	int b[3]={0},x;
	for (int i=1;i<=n;i++)
		x=h-a[i],b[1]+=x%2,b[2]+=x/2;
	if (b[2]-b[1]>1)
		x=b[2]-b[1]+1,b[1]+=x/3*2,b[2]-=x/3;
	return (b[1]>b[2]?b[1]*2-1:b[2]*2);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>n;
		for (int i=1;i<=n;i++)
			cin>>a[i],max_=(i==1?a[i]:max(max_,a[i]));
		cout<<min(solve(max_),solve(max_+1))<<'\n';
	}
	return 0;
}
```

The end.

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1661C)

## 题意

有一个 $n$ 个数的整数序列 $h_{1\sim n}$，你可以花总共 $k$ 天时间，在第 $x$ 天进行如下操作之一：

- 若 $x$ 为奇数，将任意一个 $h_i$ 增加 $1$。
- 若 $x$ 为偶数，将任意一个 $h_i$ 增加 $2$。
- 啥也不干。

求 $k$ 最小为多少时存在一种操作方法可以使所有 $h_i$ 相等。

## 分析

设 $mx=\max_{i=1}^nh_i$，那么答案的方案中所有 $h_i$ 最后都会变成 $mx$ 或 $mx+1$ 之一，显然更大的 $mx$ 都不如这两个优。

设最后所有的 $h_i$ 都变成了 $m\in\{mx,mx+1\}$，那么问题就转化为了求最小的 $k$，每天按照规则将 $d_i=m-h_i$ 减少使得最后所有的 $d_i$ 都等于 $0$。

显然 $k$ 满足单调性，即 $k$ 小于答案时无法使所有 $d_i=0$，大于等于时则可以，因此我们可以二分答案转求解为判定，而判定相当容易，设二分到 $x$，那么我们就有 $\left\lfloor\dfrac{x+1}{2}\right\rfloor$ 个 $1$ 和 $\left\lfloor\dfrac{x}{2}\right\rfloor$ 个 $2$ 进行操作，根据贪心的想法，能用 $2$ 就用 $2$，实在不行再用 $1$，如果走投无路了则说明无法满足要求。

值得注意的是，二分的 $r$ 不要开太小，至少要到 $1+2\times \sum_{i=1}^n d_i$，不然会 WA；而且每次二分时要重置 $d$ 数组。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=3e5+10;
int t,n;
ll h[N],d[N],ans,mx,l,r;
ll od,ed;//奇偶 
bool check(ll x){
	od=(x+1)>>1;
	ed=x>>1;
	for(int i=1;i<=n;i++){
		d[i]=mx-h[i];
		if(ed*2>=d[i]){
			ed-=d[i]/2;
			d[i]=d[i]%2;
		}
		else{
			d[i]-=ed*2;
			ed=0;
		}
		if(d[i]>od)
			return 0;
		od-=d[i];
	}
	return 1;
}
int main(){
	t=read();
	while(t--){
		n=read();
		mx=0;
		for(int i=1;i<=n;i++){
			h[i]=read();
			mx=max(mx,h[i]);
		}
		//第一次二分 m=mx 
		l=0;r=0;
		for(int i=1;i<=n;i++)
			r+=mx-h[i];
		r*=2;r++;
		while(l<r){
			ll mid=(l+r)>>1;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
		ans=l;
		//第二次二分 m=mx+1 
		mx++;
		l=0;r=0;
		for(int i=1;i<=n;i++)
			r+=mx-h[i];
		r*=2;r++;
		while(l<r){
			ll mid=(l+r)>>1;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
		printf("%lld\n",min(ans,l));
	}
	return 0;
}
```


---

## 作者：Dedaka (赞：0)

## 题意简述

------------
- 给定 $t$ 组数据，每组数据包括 $n$ 和 $n$ 个数。

- 每天可以使任意一个数加 $1$（天数为奇数时）或加 $2$（天数为偶数时），或者跳过这一天。

- 求最少使所有数都一样的天数，并输出。

- $1 \leq t \leq 2 \times 10^4$，$1 \leq n \leq 3 \times 10^5$，$1 \leq h_i \leq 10^9$。

## 题目分析

------------
本题可以用 **二分** 或者 **贪心** 来做，我选择了贪心。

### 思路

------------
首先观察，所需的目标高度为最大数或最大数加 $1$（如果考虑最大数加 $2$ 或以上，我们肯定有多余的操作）。而如果需加 $1$ 的次数比需加 $2$ 的次数多很多，我们就需要使目标高度为最大高度加 $1$（这样可以使需加 $1$ 的次数比需加 $2$ 的次数少（易证）），这就是程序最后的 取两种情况 的原因。

接着，先用两个变量分别保存加 $1$ 的次数和加 $2$ 的次数，然后可以考虑一个明显的贪心：肯定每次加 $2$ 能最快使数都趋向于最大的数，当该数与最大数差 $1$ 时用 $1$ 来解决。然而根据题意，只有偶数日能加 $2$，如果太贪心（加 $2$ 次数比加 $1$ 的次数多超过 $1$）会使奇数日跳过，肯定是浪费的。所以我们加上第二层贪心：使加 $1$ 的次数和加 $2$ 的次数趋于相同（使两个变量之差不超过 $1$），可以减少跳过日的浪费。

## 代码

------------
```cpp
#include<bits/stdc++.h>
#define int long long
#define mx 300010
using namespace std;
int t,n,maxx,a[mx];
int wk(int x){
	int ct1=0,ct2=0;
	for(int i=1;i<=n;i++){
		ct1+=(x-a[i])%2;//所需 1 的个数 
		ct2+=(x-a[i])/2;//2 的个数 
	}
	int tmp=ct2-ct1;
	if(tmp>=2){//如果差值过多 
		ct1+=(tmp+1)/3*2;
		ct2-=(tmp+1)/3;
	}
	if(ct1>ct2){//次数
		return ct1*2-1;
	}else{
		return ct2*2;
	}
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		maxx=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]>maxx){
				maxx=a[i];
			}
		}
		cout<<min(wk(maxx),wk(maxx+1))<<endl;
	}
	return 0;
}
```


### 其他的话
------------
没加优化会一头冲进最劣解 awa

---

