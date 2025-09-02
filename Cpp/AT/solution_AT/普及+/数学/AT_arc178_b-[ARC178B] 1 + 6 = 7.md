# [ARC178B] 1 + 6 = 7

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc178/tasks/arc178_b

正の整数 $ A_{1},\ A_{2},\ A_{3} $ が与えられます。 以下の条件を全て満たす正の整数の組 $ (X_{1},\ X_{2},\ X_{3}) $ の場合の数を $ 998244353 $ で割ったあまりを求めてください。

- $ X_{1} $ は $ 10 $ 進法で $ A_{1} $ 桁の正の整数
- $ X_{2} $ は $ 10 $ 進法で $ A_{2} $ 桁の正の整数
- $ X_{3} $ は $ 10 $ 進法で $ A_{3} $ 桁の正の整数
- $ X_{1}\ +\ X_{2}\ =\ X_{3} $
 
$ 1 $ つの入力ファイルにつき $ T $ 個のテストケースが与えられるので、それぞれについて解いてください。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 10^{5} $
- $ 1\leq\ A_{i}\leq\ 10^{9} $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ つ目のケースについて、$ (X_{1},\ X_{2},\ X_{3})\ =\ (1,\ 6,\ 7),\ (2,\ 1,\ 3) $ などが条件を満たします。 $ (X_{1},\ X_{2},\ X_{3})\ =\ (6,\ 7,\ 13),\ (3,\ 4,\ 5) $ などは条件を満たしません。 条件を満たす $ (X_{1},\ X_{2},\ X_{3}) $ の組は $ 36 $ 通りあるので $ 36 $ を出力してください。 $ 3 $ つ目のケースについて、答えを $ 998244353 $ で割ったあまりを出力することに注意してください。 $ 4 $ つ目のケースについて、条件を満たす $ (X_{1},\ X_{2},\ X_{3}) $ の組が存在しないこともあります。

## 样例 #1

### 输入

```
4
1 1 1
1 6 7
167 167 167
111 666 777```

### 输出

```
36
45
731780675
0```

# 题解

## 作者：imfbust (赞：2)

假设 $a_1\le a_2$ 。可以肯定的是 $a_1$ 位数加 $a_2$ 位数不可能的到位数小于 $a_2$ 或位数大于 $a_2+1$ ，遇到时直接输出 $0$ 。

我们令 $tmp1$ 为 $a_1$ 位数的个数，$tmp2$ 同理。

$tmp1=10^{a_1}-10^{a_1-1},tmp2=10^{a_2}-10^{a_2-1}$ 。

分类讨论：

- 当 $a_1\ne a_2,a_3=a_2+1$ 时， $X$ 可以取该位数内任意的数，而 $Y$ 仅可取 $[10^{a_3}-X,10^{a_3}-1]$ 内的数。，$ans=\sum_{i=10^{a_1-1}}^{10^{a_1}-1}i=\frac{(10^{a_1-1}+10^{a_1}-1)\times tmp1}{2}$。
- 当 $a_1\ne a_2,a_3=a_2$ 时，可通过计算补集，$ans=tmp1\times tmp2-\sum_{i=10^{a1-1}}^{10^{a1}-1}i=tmp1\times tmp2-\frac{(10^{a_1-1}+10^{a_1}-1)\times tmp1}{2}$。
- 当 $a_1=a_2,a_3=a_2+1$ 时，当 $X\in[10^{a_1-1},9\times10^{a_1-1}-1]$ 时，$Y\in[10^{a_1}-X,10^{a_1}-1]$ ， $Y$ 共有 $X$ 种取法。当 $X\in[9\times10^{a_1-1},10^{a_1}-1]$ 时，由于 $Y$ 可取的最小值为 $10^{a_1-1}$ ， $X+Y\ge10^{a_3}$ ，所以 $Y$ 的取值有 $tmp2$ 种。所以 $ans=tmp2\times10^{a_1-1}+\sum_{i=10^{a_1-1}}^{9\times10^{a_1-1}-1}i=tmp2\times10^{a_1-1}+\frac{(10^{a_1}-1)\times(8\times10^{a_1-1})}{2}$ 。
- 当 $a_1=a_2,a_3=a_2$ 时，可通过计算补集， $ans=tmp1\times tmp2-tmp2\times10^{a_1-1}+\sum_{i=10^{a_1-1}}^{9\times10^{a_1-1}-1}i=tmp1\times tmp2-tmp2\times10^{a_1-1}+\frac{(10^{a_1}-1)\times(8\times10^{a_1-1})}{2}$ 。

**code:**

````cpp
#include<bits/stdc++.h>
#define niyuan 499122177
#define mod 998244353
using namespace std;
long long ksm(long long a,long long b){
    long long res=1;
    while(b){
        if(b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        long long a1,a2,a3,ans;
        scanf("%lld%lld%lld",&a1,&a2,&a3);
        if(a1>a2) swap(a1,a2);
        if(a3<a2||a3>a2+1){
            printf("0\n");
            continue;
        }
        long long tmp1=9*ksm(10,a1-1)%mod;
        long long tmp2=9*ksm(10,a2-1)%mod;
        if(a1!=a2&&a3==a2+1) ans=(ksm(10,a1-1)+ksm(10,a1)-1)%mod*tmp1%mod*niyuan%mod;
        else if(a1!=a2&&a3==a2) ans=(tmp1*tmp2%mod-(ksm(10,a1-1)+ksm(10,a1)-1)%mod*tmp1%mod*niyuan%mod+mod)%mod;
        else if(a1==a2&&a3==a2+1) ans=(tmp2*ksm(10,a1-1)%mod+(ksm(10,a1)-1)%mod*8%mod*ksm(10,a1-1)%mod*niyuan%mod)%mod;
        else ans=(tmp1*tmp2%mod-(tmp2*ksm(10,a1-1)%mod+(ksm(10,a1)-1)%mod*8%mod*ksm(10,a1-1)%mod*niyuan%mod)%mod+mod)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
````

---

## 作者：mango2011 (赞：1)

提供一种赛时做法（稍微有一点点麻烦，但是还是很容易思考滴）。

首先，不妨令 $A_1\le A_2$，那么有两种情况使得答案不是 $0$：

1) $A_2=A_3$

2) $A_2+1=A_3$。

首先，我们考虑 $A_2+1=A_3$ 的情况（即会进位的情况）：

答案显然是下面的形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqm38cw0.png)

也就是说后面的 $A_1$ 位将发生进位：

这时候贡献有两类：

1) 右起第 $A_1$ 位如果都填 $\ge1$ 的数，那么贡献为 $10^{A_1-1}\times (5\times 10^{A_1}-(10^{A_1-1}+4))$。

这个规律最好还是打表发现。。。

2) 当 $A_1<A_2$ 时，右起第 $A_1$ 位上第二数也有可能是 $0$，那么上面必然是 $9$，则贡献为 $A_1=1$ 时显然是 $0$，否则为 $10^{A_1-2}\times(5\times10^{A_1-1}-5)$，这个规律也是打表发现的。

所以，我们就算完了所有的（也就两种）可能产生的贡献，实现的时候简单分类讨论一下即可。

当 $A_2=A_3$ 时，我们直接利用容斥，用总数减去会进位的个数，答案为 $81\times10^{A_1+A_2-2}-ans_1$，其中 $ans_1$ 表示会进位的个数。

---

## 作者：Cloote (赞：1)

## 题目大意

统计满足 $X+Y=Z$ 且 $X,Y,Z$ 在十进制下分别是 $a_1,a_2,a_3$ 位数的三元组个数，方案数对 $998244353$ 取模。

数据范围：$a_i\le 10^9$

## 分析

看到有关数位的方案数统计，或许会想到数位 dp。但是本题最大可能有 $10^9$ 位，这显然是无法用数位 dp 解决的。因此考虑推式子。

首先有个直觉是若 $X,Y$ 中有一个固定，那么另一个的取值范围会是一个区间。为了方便统计方案数，我们先令 $X\le Y$。

接下来还是一个直觉或是经验（？），假设两数相加中位数最多的那一个数有 $k$ 位，那么最后的和要么是 $k$ 位，要么是 $k+1$ 位。比较好理解，因为最高位上进的值不会超过 $1$。通过这个结论进行分类讨论。

### 1. $a_3=a_2$

此时 $X,Y$ 的取值范围分别是 $10^{a_1-1}\le X \le 10^{a_1}-1$,$10^{a_2-1}\le Y \le 10^{a_2}-1-X$。此时的方案数就是 $\sum\limits_{X=10^{a_1-1}}^{10^{a_1}-1} \max(0,10^{a_2}-1-X-10^{a_2-1}+1)=\sum\limits_{X=10^{a_1-1}}^{10^{a_1}-1} \max(0,9^{a_2-1}-X)$。把取 $0$ 的那一段去掉然后用一下等差数列求和时间复杂度就会降到 $O(\log a_2)$。

取 $0$ 的那一段也很好处理，取不到 $0$ 的 $X$ 的范围显然是 $[10^{a_1-1},\min(10^{a_1}-1,9^{a_2-1}-1)]$。分类讨论一下 $\min$ 中的取值，容易发现后者只有在 $a_1=a_2$ 的时候能取到。按照这两个式子分别化简即可。

### 2. $a_3=a_2+1$

呆呆地再推一遍式子显然很呆，由于 $X+Y$ 的和的位数不是 $a_2$ 就是 $a_2+1$，因此直接容斥一下，用总方案数 - $a_3=a_2$ 的方案数即可。

## 总结

建议评级：绿

个人感觉难点在于脑筋急转弯一下发现要么 $a_3=a_2$ 要么 $a_3=a_2+1$。只要思路清晰，推式子什么的都不算难。关键在于不能一上来就直接考虑怎么就 $X$ 或者 $Y$ 的取值范围，而是要先让一个数的范围与另一个数有关，再化简。

---

## 作者：ilibilib (赞：1)

## 分析：

这是一个很简单的数学题。

这里假设 $A_1$ 为 $x$ 位数，$A_2$ 为 $y$ 位数，$A_3$ 为 $z$ 位数，求有多少 $A_1+A_2=A_3$。

##### 什么时候答案为 $0$？

显然 $2$ 个 $x$ 位数加起来不会得到一个 $x+2$ 位数，也不会得到 $x-1$ 位数。

所以有：

```cpp
if(z>max(x,y)+1||z<max(x,y)) {cout<<0<<'\n';continue;}
```

所以 $z$ 只可能等于 $\max(x,y)$ 或 $\max(x,y)+1$。

为了方便，这里假设 $x\geq y$，即 $z$ 等于 $x$ 或 $x+1$。

##### 我们来考虑 $x\neq y$ 时，如何得到一个 $x+1$ 位数？

因为不可能得到一个 $x+2$ 位数，所以我们只用 $A_1+A_2$ 大于等于 $x+1$ 位数最小值即可，设其为 $mn$。

$$A_1\geq mn -A_2$$

$x$ 位的最大值应该位 $mn-1$，所以 $mn-A_2$ 到 $mn-1$ 这 $A_2$ 个数都是合法的。

所以方案数为 $\sum A_2$，这就是一个等差数列求和问题了。

##### 如果 $x=y$ 呢？

$mn-A_2$ 到 $mn-1$ 这 $A_2$ 个数不一定都可取，$mn-A_2$ 可能小于 $x$ 位数的最小值。$x$ 位的最小值应该为 $\frac{mn}{10}$。

$$A_2>\frac{9mn}{10}$$

这一部分可取的 $A_1$ 不再是 $mn-A_2$ 到 $mn-1$ 了，而是 $\frac{mn}{10}$ 到 $mn-1$ 了，这一部分就是常数列。

而前面一部分我们依旧用等差数列求和解决。

##### 那么要得到 $x$ 位数呢？

取补集即可。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int ksm(int a,int b)
{
    int c=1;
    while(b)
    {
        if(b&1) c=(c*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return c;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        int x,y,z,ans=0,a,b,mn1,mx1,mn2,mx2;
        cin>>x>>y>>z;
        if(z>max(x,y)+1||z<max(x,y)) {cout<<0<<'\n';continue;}
        if(y>x) swap(x,y);

        mn1=ksm(10,x-1);mx1=ksm(10,x)-1;
        a=(mx1-mn1+1)%mod;

        mn2=ksm(10,y-1);mx2=ksm(10,y)-1;
        b=(mx2-mn2+1)%mod;

        if(x!=y) ans=((((mn2+mx2)*b)%mod)*ksm(2,mod-2))%mod;
        else ans=(((mn1+b)*(b-mn1+1)%mod)*ksm(2,mod-2)+(((mn1-1)*a)%mod))%mod;
        if(x==z) ans=((a*b%mod)-ans)%mod;
        ans=((ans%mod)+mod)%mod;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：fire_and_sweets (赞：0)

提供一个官方题解没有讲到的做法。（是全网第一份吗？）

我们可以先把 $A_1,A_2,A_3$ 排序，保证 $A_1\le A_2\le A_3$。

显然，有两种情况可能满足条件：
- $A_2=A_3$
- $A_2+1=A_3$

接下来，我们分情况讨论。

首先是 $A_2=A_3$ 的情况。经过打表找规律可以发现，对于 $X=10^{A_1-1}\sim 10^{A_1}$，方案数是 $d=-1$ 的等差数列。

对于另一种情况，方案数则是一个 $d=1$ 的等差数列。

这两个等差数列的值是有上界的，到了这个上界就不再会增加了。我们很容易计算出这个 bound 的值。

于是，我们便能很快通过这道题目。

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 998244353;

int qmi(int a, int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return res;
}

void get(int& x)
{
	x = (x % mod + mod) % mod;
}

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T, a, b, c;
	cin >> T;
	while (T -- )
	{
		cin >> a >> b >> c;
		if (a > b) swap(a, b);
		if (b == c)
		{
			int ex = qmi(10, b) - qmi(10, b - 1) - qmi(10, a - 1); get(ex);
			int len = qmi(10, a) - qmi(10, a - 1); get(len);
			if (a == b) len = ex;
			int sx = ex - len + 1; get(sx);
			int res = (sx + ex) % mod * len % mod * qmi(2, mod - 2); get(res);
			cout << res << endl;
		} 
		else if (b + 1 == c)
		{
			int sx = qmi(10, a - 1), ex = qmi(10, a) - 1;
			int len = ex - sx + 1; get(len);
			int res = (sx + ex) % mod * len % mod * qmi(2, mod - 2); get(res);
			if (a == b)
			{
				int tp = qmi(10, c - 1) - qmi(10, a - 1);
				int tsx = 1, tsy = ex - tp, len = tsy - tsx + 1; get(tsy);
				int res2 = (tsx + tsy) % mod * len % mod * qmi(2, mod - 2); get(res2);
				get(res2);
				res -= res2;
				get(res);
			}
			cout << res << endl;
		}
		else cout << 0 << endl;
	}
	return 0;
}
```

---

