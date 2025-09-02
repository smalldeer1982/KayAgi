# Banquet Preparations 1

## 题目描述

厨师为一次宴会准备了 $n$ 道菜品，出于某种原因，所有菜品都是由鱼肉和猪肉组成的。第 $i$ 道菜品中包含了 $a_i$ 单位的鱼肉和 $b_i$ 单位的猪肉。

晚宴的主办方定义晚会美食的平衡度为 $|\sum_{i=1}^n\ a_i\ - \ \sum_{i=1}^n\ b_i|$，并且希望这个值越小越好。为了达成这一点，主办方请来了一个吃客。此人会在每道菜中刚好吃下 $m$ 单位的食物，这会使得 $a_i,b_i$ 发生变化。

现在请你规划他在每道菜中该吃多少鱼肉，多少猪肉，使得最后的平衡值最小。

## 说明/提示

$1\le n \le 2\times 10^5,\ 0\le m\le 10^6$
保证对于 $\forall i$，满足 $m\le a_i+b_i$

## 样例 #1

### 输入

```
8

1 5
3 4

1 6
3 4

2 2
1 3
4 2

2 4
1 3
1 7

3 6
1 7
1 8
1 9

3 6
1 8
1 9
30 10

3 4
3 1
3 2
4 1

5 4
0 7
6 4
0 8
4 1
5 3```

### 输出

```
0
2 3
1
3 3
0
1 1
1 1
2
1 3
0 4
3
0 6
0 6
0 6
7
1 5
1 5
6 0
0
3 1
3 1
3 1
0
0 4
2 2
0 4
3 1
1 3```

# 题解

## 作者：HDWR (赞：9)

本题还是有点阅读理解的。

题意就是让你求一组 $n$ 个 $x_i$，使得：

$$
\left|\sum_{i = 1}^n(a_i - x_i) - \sum_{i = 1}^n(b_i - (m - x_i))\right|
$$

这个东西最小。

先化简一下式子：

$$
\left|\sum_{i = 1}^n(a_i - b_i + m) - 2\sum_{i = 1}^n x_i\right|
$$

其中每一个 $x_i$ 都有一个范围限制：

$$
\max(m - b_i, 0) \leq x_i \leq \min(a_i, m)
$$

左边是一个固定值，我们把它记为 $S$；右边是一个一堆范围求和。是不是感觉好做一些了？

注意到一个性质：假如我们把所有 $x_i$ 取到最小值的和记为 $L$，取到最大值的和记为 $R$，那么 $L \leq \sum x_i \leq R$，而且 $\sum x_i$ 可以取遍所有的 $[L, R]$。这是初中的不等式知识，很好理解。

这个性质将题目转化为了：我们要在 $[L, R]$ 中找到最接近 $\lfloor \frac{S}{2} \rfloor$ 的数。

此时这就是一道大水题了：对 $S, 2L, 2R$ 分类讨论，

- $S \leq 2L$ 时直接将所有值取到最小；
- $2R \leq S$ 时直接将所有值取到最大；
- $S \in [2L, 2R]$ 时，如果 $S$ 是偶数那么答案是 $0$，否则是 $1$（因为一个奇数减一个偶数不可能是一个偶数），此时方案可以直接贪心的去取，先将所有的 $x$ 保底取到最小值，然后将 $\lfloor \frac{S}{2} \rfloor - L$ 贪心地进行分配，如果当前能取最大值就尽量取最大值。

```cpp
const int MAXN = 2e5 + 10;

int n, m;
std::pair<lli, lli> dishes[MAXN];
std::pair<lli, lli> bounds[MAXN];
lli chosenx[MAXN];

void _main() {
    n = read(); m = read();
    lli s = 0;
    lli suml = 0, sumr = 0;
    rep (i, 1, n) {
        lli a = read(); lli b = read();
        dishes[i] = {a, b};
        s += (a - b + m);
        bounds[i].fi = std::max(m - b, 0ll);
        bounds[i].se = std::min((lli) m, a);
        suml += bounds[i].fi; sumr += bounds[i].se;
    }
    if (2ll * sumr <= s) {
        printf("%lld\n", s - 2ll * sumr);
        rep (i, 1, n) {
            lli x = bounds[i].se, y = m - x;
            printf("%lld %lld\n", x, y);
        }
    }
    else if (s <= 2ll * suml) {
        printf("%lld\n", 2ll * suml - s);
        rep (i, 1, n) {
            lli x = bounds[i].fi, y = m - x;
            printf("%lld %lld\n", x, y);
        }
    }
    else {
        printf("%lld\n", (s % 2));
        lli ns = (s >> 1) - suml;
        rep (i, 1, n) {
            chosenx[i] = bounds[i].fi;
            lli dtx = bounds[i].se - bounds[i].fi;
            if (ns >= dtx) {
                ns -= dtx; chosenx[i] += dtx;
            } else {
                chosenx[i] += ns; ns = 0;
            }
        }
        lli checksum = 0;
        rep (i, 1, n) {
            printf("%lld %lld\n", chosenx[i], m - chosenx[i]);
            checksum += chosenx[i];
        }
        assert(std::abs(checksum * 2 - s) <= 1);
    }
}

int main() {
    // freopen("gout.out", "w", stdout);
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = read();
    while (T --> 0) {
        _main();
    }
    return 0;
}
```

---

## 作者：Wuyanru (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1607G)

翻译：

现在有 $ n $ 道菜，每道菜由 $ a_i $ 克鱼肉与 $ b_i $ 克猪肉组成。现有一个评委要将每道菜吃掉 $ m $ 克，其中吃掉鱼肉与猪肉的数量都要是整数。问剩余的菜中鱼肉重量之和与猪肉重量**之差最小**是多少，并输出一种方案。多组询问。

为了方便起见，我们先设几个变量。

设 $ suma=\sum\limits_{i=1}^na_i $，$ sumb=\sum\limits_{i=1}^nb_i $。也就是 $ suma $ 表示鱼肉总重，$ sumb $ 表示猪肉总重。

设 $ maxa=\sum\limits_{i=1}^n\max(a_i,m) $，$ sumb=\sum\limits_{i=1}^n\max(b_i,m) $。也就是 $ maxa $ 表示最多能吃的鱼肉数量，$ maxb $ 表示最多能吃的猪肉数量。

上述四个变量都可以在 $ O(n) $ 时间内求出。

不妨设 $ suma\ge sumb $，$ suma<sumb $ 时是一样的。下面我们来分类讨论：

1.  $ suma-maxa\ge sumb $ 也就是说无论吃多少鱼肉，鱼肉总数都比猪肉总数多，此时能吃鱼肉就吃鱼肉，剩下的就吃猪肉。

2.  $ suma-maxa<sumb $，此时我们很容易知道当 $ suma+sumb-n\times m $ 为奇数时答案为 $ 1 $，$ suma+sumb-n\times m $ 为偶数时答案为 $ 0 $，下面我们来进行构造。

现在假设答案为 $ 0 $，答案为 $ 1 $ 时同理。

设评委会吃 $ x $ 克鱼肉，则会吃 $ (n\times m-x) $ 克猪肉，且最优情况下一定会满足 $ x<maxa $。

容易列出方程：

$$
suma-x=sumb-(n\times m-x)
$$

解得：

$$
x=\dfrac{suma-sumb+n\times m}{2}
$$

也就是说我们要吃掉 $ x=\dfrac{suma-sumb+n\times m}{2} $ 克鱼肉，直接进行构造即可。

最后，贴上 AC 代码：

```
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#define il inline
#define gc getchar
using namespace std;
il int min(int a,int b){ return a<b?a:b;}
using ll=long long;
il int read()
{
int s=0,w=1;char ch;
while((ch=gc())>'9'||ch<'0') if(ch=='-') w=-1;
	while(ch>='0'&&ch<='9'){ s=s*10+ch-'0';ch=gc();}
	return s*w;
}
il ll lread()
{
	long long s=0,w=1;char ch;
	while((ch=gc())>'9'||ch<'0') if(ch=='-') w=-1;
	while(ch>='0'&&ch<='9'){ s=s*10+ch-'0';ch=gc();}
	return s*w;
}
int a[200001];
int b[200001];
ll maxa,maxb;
ll suma,sumb;
int n,m;
ll ans;
signed main()
{
	int t=read();
	while(t--)
	{
		maxa=maxb=ans=suma=sumb=0;
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read(),b[i]=read();
			suma+=a[i],sumb+=b[i];
			maxa+=min(m,a[i]);
			maxb+=min(m,b[i]);
		}
		if(suma>=sumb)
		{
			if(suma-maxa>=sumb-((ll)m*n-maxa))
			{
				printf("%lld\n",suma-maxa-(sumb-((ll)m*n-maxa)));
				for(int i=1;i<=n;i++)
					if(a[i]<=m) printf("%d %d\n",a[i],m-a[i]);
					else printf("%d %d\n",m,0);
				continue;
			}
			ll flag=maxa-(suma-sumb+(ll)m*n)/2;
			printf("%lld\n",(suma-sumb+(ll)m*n)%2);
			for(int i=1;i<=n;i++)
			{
				int num=min(a[i],m),minn=m-min(m,b[i]);
				if(flag>num-minn) flag-=num-minn,num=minn;
				else num=num-flag,flag=0;
				printf("%d %d\n",num,m-num);
			}
		}
		else
		{
			if(sumb-maxb>=suma-((ll)m*n-maxb))
			{
				printf("%lld\n",sumb-maxb-(suma-((ll)m*n-maxb)));
				for(int i=1;i<=n;i++)
					if(b[i]<=m) printf("%d %d\n",m-b[i],b[i]);
					else printf("%d %d\n",0,m);
				continue;
			}
			ll flag=maxb-(sumb-suma+(ll)m*n)/2;
			printf("%lld\n",(sumb-suma+(ll)m*n)%2);
			for(int i=1;i<=n;i++)
			{
				int num=min(b[i],m),minn=m-min(m,a[i]);
				if(flag>num-minn) flag-=num-minn,num=minn;
				else num=num-flag,flag=0;
				printf("%d %d\n",m-num,num);
			}
		}
	}
	return 0;
}
```

感谢观看！

---

## 作者：caizhetong (赞：1)


### 我的思路
定义 $numa$ 为鱼的总数量，$suma$ 为最多吃的鱼的数量，$cnta$ 为本次所需要吃的鱼的个数。$numb$，$sumb$，$cntb$ 同理。这些都能在 $O(n)$ 的时间复杂度内求出来。

我们可以求出本次所需要吃的鱼的数量与最多吃的鱼的数量的差为 $x$。我们可以求出每个菜肴的吃的鱼肉数量的最小值和最大值。然后对于每个菜肴都通过用最大值和最小值的差来减小 $x$。最终构造出我们吃的鱼的数量 $cnta$。

### 我的代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long t,n,m,numa,numb,suma,sumb,cnta,cntb,ans,ans1;
struct tx{
    long long a,b,id;
}z[1000010];
signed main()
{
    ios::sync_with_stdio(0);

    cin>>t;
    while(t--)
    {
        numa=0,numb=0;suma=0;sumb=0;ans1=0;ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            cin>>z[i].a>>z[i].b;
            numa+=z[i].a;
            numb+=z[i].b;
            suma+=min(z[i].a,m);
            sumb+=min(z[i].b,m);
        }
        if(numa-suma>=numb-(1ll*m*n-suma))
        {
            cout<<numa-numb-suma+(1ll*m*n-suma)<<"\n";
            for(int i=1;i<=n;i++)
            {
                int a,b;
                a=min(m,z[i].a);b=m-a;
                cout<<a<<" "<<b<<"\n";
            }
            continue;
        }
        if(numb-sumb>=numa-(1ll*m*n-sumb))
        {
            cout<<numb-sumb-numa+(1ll*m*n-sumb)<<"\n";
            for(int i=1;i<=n;i++)
            {
                int a,b;
                b=min(m,z[i].b);a=m-b;
                cout<<a<<" "<<b<<"\n";
            }
            continue;
        }
        if(numa>=numb)
        {
            cnta=(m*n-(numa-numb))/2;
            cntb=m*n-cnta;
        }
        else
        {
            cntb=(m*n-(numb-numa))/2;
            cnta=m*n-cntb;
        }
        cout<<abs(numa+cnta-numb-cntb)<<"\n";
        swap(cnta,cntb);
        ans=suma-cnta;
        for(int i=1;i<=n;i++)
        {
            int e=min(z[i].a,m)-(m-min(z[i].b,m)),a,b;
            if(ans<=0)
            {
                a=min(z[i].a,m);
                b=m-a;
                cout<<a<<" "<<b<<"\n";
                continue;
            }
            if(ans>e)
            {
                b=min(z[i].b,m);
                a=m-b;
                ans-=e;
                cout<<a<<" "<<b<<"\n";
                continue;
            }
            if(ans<=e)
            {
                a=min(z[i].a,m)-ans;
                b=m-a;
                ans=0;
                cout<<a<<" "<<b<<"\n";
                continue;
            }
        }
    }

    return 0;
}

```



---

## 作者：Valhalla_Is_Calling (赞：1)

### $\operatorname{Description.}$
厨师为一次宴会准备了 $n$ 道菜品，出于某种原因，所有菜品都是由鱼肉和猪肉组成的。第 $i$ 道菜品中包含了 $a_i$ 单位的鱼肉和 $b_i$ 单位的猪肉。

晚宴的主办方定义晚会美食的平衡度为 $|\sum_{i=1}^n\ a_i\ - \ \sum_{i=1}^n\ b_i|$，并且希望这个值越小越好。为了达成这一点，主办方请来了一个吃客。此人会在每道菜中刚好吃下 $m$ 单位的食物，现在请你规划他在每道菜中该吃多少鱼肉，多少猪肉，使得最后的平衡值最小。

$1\le n \le 2\times 10^5,\ 0\le m\le 10^6$

### $\operatorname{Solution.}$

思路应该很好想，分情况讨论，如果两种肉差的值超过 $m$，那显然应该都吃多的。这种也很好实现，每道菜都尽量吃少的菜，不够了再吃另一种即可。

第二种情况，显然是先把多的削平，之后两种肉等量的往下吃，这样即可保证答案的正确性。

### $\operatorname{Code.}$

```cpp
#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 200010;

int read () {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

struct Dishes {
    int a, b;
};

Dishes my_Dishes[N];
Dishes ans[N];

int n, m;
signed main() {
    int T = read();
    while (T--) {
        n = read();
        m = read();
        for (int i = 0; i < n; i++) {
            my_Dishes[i].a = read();
            my_Dishes[i].b = read();
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            ans[i].a = min(my_Dishes[i].a, m);
            ans[i].b = m - ans[i].a;
            sum += (my_Dishes[i].a - ans[i].a - my_Dishes[i].b + ans[i].b);
        }
        if (sum >= 0) {
            printf("%lld\n", sum);
            for (int i = 0; i < n; i++) {
                printf("%lld %lld\n", ans[i].a, ans[i].b);
            }
        }
        else {
            sum = -sum;
            for (int i = 0; i < n; i++) {
                int give_max = min(ans[i].a, my_Dishes[i].b - ans[i].b);
                if ((give_max << 1) <= sum) {
                    sum -= (give_max << 1);
                    ans[i].a -= give_max;
                    ans[i].b += give_max;
                }
                else {
                    int give = (sum >> 1);
                    sum -= (give << 1);
                    ans[i].a -= give;
                    ans[i].b += give;
                }
            }
            printf("%lld\n", sum);
            for (int i = 0; i < n; i++) {
                printf("%lld %lld\n", ans[i].a, ans[i].b);
            }
        }
    }
    return 0;
}
```


---

