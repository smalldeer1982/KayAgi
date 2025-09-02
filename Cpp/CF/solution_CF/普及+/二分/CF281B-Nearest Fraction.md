# Nearest Fraction

## 题目描述

You are given three positive integers $ x,y,n $ . Your task is to find the nearest fraction to fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) whose denominator is no more than $ n $ .

Formally, you should find such pair of integers $ a,b $ $ (1<=b<=n; 0<=a) $ that the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/c829c21e70460346cb0c98e0e40815418eed87ca.png) is as minimal as possible.

If there are multiple "nearest" fractions, choose the one with the minimum denominator. If there are multiple "nearest" fractions with the minimum denominator, choose the one with the minimum numerator.

## 样例 #1

### 输入

```
3 7 6
```

### 输出

```
2/5
```

## 样例 #2

### 输入

```
7 2 4
```

### 输出

```
7/2
```

# 题解

## 作者：loser_seele (赞：0)

我们考虑暴力思路，枚举所有合法的分数并找出其中和目标分数距离最小的。

但不难发现这样难以通过，因为很多不可能成为答案的分数也被考虑进来了。

于是我们考虑对暴力进行优化，根据经验我们令 $ \frac{a}{b}=\frac{x}{c} $ ，那么有 $ x=\frac{ac}{b} $，但是此时 $ x $ 可能不为整数，因此我们枚举 $ x $ 周围的 $ 20 $ 个整数，之后与 $ \frac{a}{b} $ 作差之后取绝对值差最小的即可。这个思路本质上是一种搜索剪枝。

至于要保证分母最小和分子最小，枚举的时候从较小的数先枚举即可。

于是总时间复杂度 $ \mathcal{O}(kn) $，其中 $ k=20 $ 为我们选取的周围的数字个数，可以通过。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
bool comp(int a,int b,int c,int d)
{
return a*d<b*c;
}
//1/3<1/2
pair<int,int> dis(int a,int b,int c,int d)
{
int newx=a*d-b*c;
int newy=b*d;
newx=abs(newx);
int gcder=__gcd(newx,newy);
newx/=gcder,newy/=gcder;
return make_pair(newx,newy);
}
main()
{
    int a,b,c,nowx=0,nowy=1;
    cin>>a>>b>>c;
    for(int i=1;i<=c;i++)
    {
    int tmpx=a*i/b,tmpy=i;
    for(int xx=max(0ll,tmpx-10);xx<=tmpx+10;xx++)
    if(comp(dis(xx,tmpy,a,b).first,dis(xx,tmpy,a,b).second,dis(nowx,nowy,a,b).first,dis(nowx,nowy,a,b).second))
    nowx=xx,nowy=tmpy;
    }
    int gcder=__gcd(nowx,nowy);
    nowx/=gcder,nowy/=gcder;
    cout<<nowx<<'/'<<nowy<<'\n';
}
```

---

## 作者：_5t0_0r2_ (赞：0)

# 分析：

可以使用公式，推出在分母为 $i$ 的情况下与 $\frac{x}{y}$ 最接近的数。

设这个数为 $\frac{x_0}{i}$，先将两个分数通分，将 $\frac{x}{y}$ 变为 $\frac{x \times [y,i] \div y}{[y,i]}$，要想使 $\frac{x_0}{i}$ 与其最接近，那么 $\frac{x \times [y,i] \div y}{[y,i]}$ 的分子应变为最近的 $[y,i] \div i$ 的倍数。特别的，当 $[y,i] = 2$ 时，最近的倍数被定义为较小的一个。

下面给出部分代码，其余请自行补齐：


```cpp
int GCD(int a,int b){
	return b ? GCD(b,a % b) : a;
}
struct frac{
	int x,y;
	void simplify(){//化简
		int tmp = GCD(x,y);
		x /= tmp;
		y /= tmp;
	}
	void print(){
		printf("%lld/%lld\n",x,y);
	}
} f,ans,sub;
bool operator<(frac f1,frac f2){
	return (double)f1.x / f1.y < (double)f2.x / f2.y;
}
bool operator<=(frac f1,frac f2){
	int LCM = f1.y * f2.y / GCD(f1.y,f2.y);
	return (double)f1.x / f1.y <= (double)f2.x / f2.y;
}
frac operator-(frac f1,frac f2){
	int LCM = f1.y * f2.y / GCD(f1.y,f2.y);
	return (frac){f1.x * LCM / f1.y - f2.x * LCM / f2.y,LCM};
}
frac Max(frac f1,frac f2){
	return f2 < f1 ? f1 : f2;
}
frac Abs(frac fr){
	return (frac){abs(fr.x),fr.y};
}
```


---

## 作者：SlyCharlotte (赞：0)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/613991705)

# 题意描述

给你一个分数，你需要给出你个分数满足你所给出的分数与题目所给的分数的差最小。

然后分母满足小于等于某一个数，若有多个输出最小。

# 简要分析

设题目所给分数为 $\frac x y$，分母不超过 $n$，若 $y \leq n$ 则答案为 $\frac x y$。

否则考虑枚举分母的取值，随后二分分子。

这里找到最大的小于等于 $\frac{x} {y}$ 的分数。

为了方便这里钦定 $x < y$，若 $x \ge y$ 则先转化为 $x \le y$ 求出分子后再加上 $k \times y$ 即可。 

但不要忘记考虑 $\frac{x+1} y$ 对答案的贡献。

时间复杂度 $O(n \log n)$

# 代码实现

```cpp
ll y, n;

bool check(ll b, ll a, ll x) {
    if (1LL * b * x >= 1LL * a * y)
        return true;
    return false;
}

pair<ll, ll> fun(ll x1) {
    long double min = float(x1) / y;
    ll num = 0;
    ll denom = 1;
    for (ll i = 1; i <= n; i++) {
        ll l = 0, r = i - 1;
        ll ans = 0;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (check(i, mid, x1))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        ll tnum = ans;
        ll tdenom = i;
        ldb tmin = abs((double(x1) / y) - (double(tnum) / tdenom));
        ldb temp = abs((double(x1) / y) - ((double(tnum + 1)) / tdenom));
        if (temp < tmin)
            tmin = temp, tnum = ans + 1;
        if (tmin < min)
            min = tmin, denom = tdenom, num = tnum;
    }
    return {num, denom};
}

signed main() {
    ll x;
    cin >> x >> y >> n;
    if (n >= y) {
        ll g = gcd(x, y);
        cout << x / g << "/" << y / g;
    } else {
        ll i = x / y, x1 = x - y * i;
        pair<ll, ll> f = fun(x1);
        ll num, denom = f.second;
        num = denom * i + f.first;
        ll g = gcd(num, denom);
        cout << num / g << "/" << denom / g;
    }
    return 0;
}
```



---

