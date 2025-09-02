# [ARC139B] Make N

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc139/tasks/arc139_b

整数 $ P=0 $ があります。以下の $ 3 $ 種類の操作を任意の回数選んで行うことで $ P=N $ とするとき、コストの総和の最小値を求めてください。

- $ P $ を $ 1 $ 増やす。この操作はコストが $ X $ かかる。
- $ P $ を $ A $ 増やす。この操作はコストが $ Y $ かかる。
- $ P $ を $ B $ 増やす。この操作はコストが $ Z $ かかる。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 100 $
- $ 1\ \le\ N,A,B,X,Y,Z\ \le\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 個目のテストケースでは、例えば以下のようにするとコスト $ 11 $ で $ P=10 $ とでき、これが最適です。 - $ P $ を $ 3 $ 増やす。$ P=3 $ となる。コストが $ 3 $ かかる。 - $ P $ を $ 1 $ 増やす。$ P=4 $ となる。コストが $ 2 $ かかる。 - $ P $ を $ 3 $ 増やす。$ P=7 $ となる。コストが $ 3 $ かかる。 - $ P $ を $ 3 $ 増やす。$ P=10 $ となる。コストが $ 3 $ かかる。

## 样例 #1

### 输入

```
5
10 3 5 2 3 6
10 3 5 1 1000000000 1000000000
139 2 139 1 1 1
139 1 1 1 1 1
139 7 10 3845 26982 30923```

### 输出

```
11
10
1
139
436604```

# 题解

## 作者：zhaoyp (赞：6)

[ARC139B](https://atcoder.jp/contests/arc139/tasks/arc139_b)
$\text{Difficulty : 1719}$ ：

给定一个正整数 $n$，可以执行以下三种操作之一。
- 花费 $x$ 的代价将 $n$ 减 $1$。
- 花费 $y$ 的代价将 $n$ 减 $a$。
- 花费 $z$ 的代价将 $n$ 减 $b$。

$1 \le n,a,b,x,y,z \le 10^9$。

首先可以令 $y = \min\{y,a\times x\},z = \min\{z,b\times x\}$。

如果通过任意一种方式使得 $n$ 减少了 $\operatorname{lcm}(a,b)$ 那么他就一定可以被其他方式所替代。

算出减少 $\operatorname{lcm}(a,b)$ 所需代价，令 $n = \min\{n,n \bmod \operatorname{lcm}(a,b) + \operatorname{lcm}(a,b)\}$，将答案加上 $n$ 减少的部分的代价，此时 $n$ 与 $a \times b$ 同阶。

不妨设 $a > b$。

于是我们可以枚举减 $a$ 的次数，剩下的能用减 $b$ 就用它，最后再用减 $1$ 补满。由于之前我们已经令 $y = \min\{y,a\times x\},z = \min\{z,b\times x\}$，所以这样子是正确的。

由于减 $a$ 的次数最多为 $\left\lfloor\frac{n}{a}\right\rfloor \le \sqrt{n}$，所以时间复杂度为 $O(T\sqrt{n})$。

---

## 作者：shinkuu (赞：4)

%你赛时降智了，没想到根分，于是有了这篇乱搞题解，欢迎来叉，但是好像结论和正解差不多。

首先考虑一个不那么极端的数据，它的最小值是在哪里取到。假设选 $p$ 个 $A$，$q$ 个 $B$，$pA+qB=n$。这就相当于解一个二元一次方程，花费的最小值就会在 $p$ 或 $q$ 取得最小值时取到。

进一步猜测，当 $pA+qB<n$ 时，答案也会在 $p$ 或 $q$ 取最小值的时候取到。想到经典的平面最近点对。于是设一个参数 $k$，在范围 $[0,k]$ 内枚举 $p,q$，全部算出来取最小值即可。

要注意有些时候取 $1$ 会更优。特判一下。

$k$ 取 $[10^5,10^6]$ 都可过。

code：

```cpp
ll n,a,b,x,y,z;
void solve(){
	scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&b,&x,&y,&z);
	const int mx=2e5;
	ll ans=n*x;
	for(ll i=0;i<=mx;i++){
		ll k=n-a*i,p=k/b,q=k%b;
		if(k>=0)
			ans=min(ans,min(i*y+p*z+x*q,i*y+k*x));
		k=n-b*i,p=k/a,q=k%a;
		if(k>=0)
			ans=min(ans,min(i*z+p*y+x*q,i*z+k*x));
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：zasdcn (赞：3)

发现我们按照性价比排序，根据 $1$ 的排名，有不同的贪心策略。



如果说性价比后是 $J K L$，



1.如果 $J | N$,那么一定都选 $J$：



因为无论将哪一段换成 $K$ 或 $L$,都没有 $J$ 优。



2.如果 $K = 1$：



那么一定尽可能的选 $J$，然后补 $K$，



同样无论将哪一段换成 $L$，都没有目前优。



3.如果 $L = 1$：



按照原来的贪心策略，尽可能的选 $J$，然后 $K$，再 $L$,
 



假设剩下 $P$，如果L的性价比很不好，那么就是 $P \times X$，



那么就会有少选一些 $J$，多选一些 $K$，然后少选一些 $L$。



这个问题并不等价于我们选一些 $J$,一些 $K$，然后尽可能的接近 $N$，因为也要考虑 $J$ 和 $K$ 之间性价比。



好像只能枚举……



因为数据水，所以枚举暴力 $J$,卡一下上界，就切了……


**考虑正解:**

$Jx + Ky + z = N$，最小化 $x \times Y + y \times Z + z \times X$，可以发现一个神奇的东西，如果 $y  \ge J$，$K \times y = K \times (J + y')$，显然把 $K \times J $，算成 $J$ 的贡献更优，因为性价比 $J$ 比 $K$ 优。 



所以，我们可以考虑根号分治。



如果 $J \ge \sqrt N$,那么 $x$ 的取值只有 $\sqrt N$ 种直接枚举。



如果 $J < \sqrt N$,那么 $y$ 的取值只有 $\sqrt N$ 种直接枚举。



时间复杂度 $O(T \sqrt N)$。

---

## 作者：Zimo_666 (赞：1)

# B - Make N

考虑所有的操作，考虑操作的性价比。

如果 $Y>AX$ 或 $Z>BX$，那么可以使用若干次加一操作代替（换句话说加一操作看起来是普适性最高的）。

那么我们钦定 $A$ 操作的性价比高，否则交换一下。

那么我们考虑最优情况下，执行 $A$ 操作至多 $\lfloor\frac{N}{A}\rfloor$ 次，执行 $B$ 操作至多 $A-1$ 次。

考虑根号分治。

- $A>\sqrt{n}$ 时枚举 $A$ 操作的次数。
- $A\le \sqrt n$ 时枚举 $B$ 操作的次数。

 复杂度 $O(T\sqrt{n})$。

代码很好实现，自己写的太丑了就不发了。

---

## 作者：ncwzdlsd (赞：1)

枚举。

首先，钦定 $Y\leq AX$ 且 $Z\leq BX$，否则可以通过 $A$ 或 $B$ 次加一操作得到更优解。

再钦定 $\dfrac{A}{Y}>\dfrac{B}{Z}$，即令 $A$ 的性价比更高，否则 $B$ 更优，可以交换 $A,B$ 及其两者的花费。

增加 $A$ 的操作最多进行 $\lfloor \dfrac{N}{A}\rfloor$ 次；增加 $B$ 的操作最多 $A-1$ 次，否则可以通过 $B$ 次增加 $A$ 操作得到更优解。

取两种情况的操作次数中上限较小的一个枚举，贪心求三种操作后的最优解即可。

时间复杂度约为 $O(\sqrt N)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
    ll N,A,B,X,Y,Z;
    cin>>N>>A>>B>>X>>Y>>Z;
    Y=min(Y,A*X),Z=min(Z,B*X);
    if(A*Z<B*Y) swap(A,B),swap(Y,Z);
    ll ans=LLONG_MAX,tmp=0;
    if(N/A<A-1) for(int i=0;i<=(N/A);++i) tmp=N-i*A,ans=min(ans,i*Y+tmp/B*Z+tmp%B*X);
    else for(int i=0;i<=A-1;++i)
    {
        tmp=N-i*B;
        if(tmp>=0) ans=min(ans,i*Z+tmp/A*Y+tmp%A*X);
    }
    cout<<ans<<endl;
}

int main()
{
    int T;cin>>T;
    while(T--) solve();
    return 0;
}
```

[通过记录](https://atcoder.jp/contests/arc139/submissions/46353073)

---

## 作者：5k_sync_closer (赞：1)

令 $1$ 的性价比为 $\dfrac 1x$，$a$ 的性价比为 $\dfrac ay$，$b$ 的性价比为 $\dfrac bz$。

$1$ 的性价比最高，第二高的情况平凡，钦定 $\dfrac ay\ge \dfrac bz\ge \dfrac 1x$。

若 $a>\sqrt n$，则 $a$ 被选不超过 $\sqrt n$ 次，枚举 $a$ 被选的次数即可。

若 $a\le\sqrt n$，则 $b$ 被选不超过 $a$ 次，枚举 $b$ 被选的次数即可。

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int T, n, a, b, x, y, z, q;
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld%lld%lld%lld%lld", &n, &a, &b, &x, &y, &z);
        if (a * z < b * y)
            swap(a, b), swap(y, z);
        if (a * x <= y)
            printf("%lld\n", n * x);
        else if (b * x <= z)
            printf("%lld\n", n / a * y + n % a * x);
        else
        {
            q = 1e18;
            if (a * a > n)
                for (int i = 0; a * i <= n; ++i)
                    q = min(q, y * i + (n - a * i) / b * z + (n - a * i) % b * x);
            else
                for (int i = 0; i <= a && b * i <= n; ++i)
                    q = min(q, z * i + (n - b * i) / a * y + (n - b * i) % a * x);
            printf("%lld\n", q);
        }
    }
    return 0;
}
```


---

## 作者：FLORIZ (赞：0)

首先我们第一思路就找出每个数的性价比，然后排序分情况。

如果比完大小纯暴力能取则取的贪心，很容易出现被下面这种数据 hack 的情况：

```cpp
1
10 3 4 1000000000 4 3
```

这时候拿性价比较高的两种凑出 $n$ 的性价比比拿 $1$ 去填好很多。

所以我们的思路是：如果 $1$ 的性价比最高，没有风险直接填；

如果 $1$ 的性价比排第二，我们也能拿排在第一的凑完拿1填；

但是如果 $1$ 的性价比排第三，就复杂起来了。

假设有 $\dfrac {a}{y}>\dfrac{b}{z}>\dfrac{1}{x}$ 。

先枚举买几个 $a$，剩下的先拿 $b$ 填，最后用 $1$。这样就能使每种可能的答案被考虑了。

不过这样复杂度就炸了 $O(Tn)$。

根号分治起作用了：发现买 $a$ 个 $b$ 或者 $b$ 个 $a$ 等价，但是显然后者性价比高，所以 $b$ 最多买 $a-1$ 个。这一情况恰好能处理 $a$ 比较小的情况。

所以在 $a<\sqrt{n}$ 时，我们直接枚举 $a$；在 $a>\sqrt {n}$ 时，我们可以枚举 $b$ 然后填 $a$。最后再去填 $1$。

复杂度降到了 $O(T\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
	{long long f(1),x(0);
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return f*x;
	}
void write(long long x)	
	{if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	}
#define debug(x) cout<<x<<endl

long long t;
long long ans,n,a,b,x,y,z;

double val[4];

int main()
	{t=read();
	while(t--)
		{ans=0;
		n=read(),a=read(),b=read();
		x=read(),y=read(),z=read();
		
		ans=n*x;
		double av=(double)a/(double)y;
		double bv=(double)b/(double)z;
		if(av<bv)
			{swap(a,b);
			swap(y,z);
			}
		if(a-1>(n/a))
			{for(long long i=0;i<=sqrt(n);i++)
				{if(i*a>n)
					{break;
					}
				long long ss=n;
				long long zu1=i*y;
				ss-=i*a;
				long long zu2=(ss/b)*z;
				ss-=b*(ss/b);
				ans=min(ans,zu1+zu2+ss*x);
				}
			}
		else
			{for(int i=0;i<=a-1;i++)
				{if(i*b>n)
					{break;
					}
				long long ss=n;
				long long zu1=i*z;
				ss-=i*b;
				long long zu2=(ss/a)*y;
				ss-=a*(ss/a);
				ans=min(ans,zu1+zu2+ss*x);
				}
			}
		
		write(ans),putchar('\n');
		}
	return 0;
	}
```

---

## 作者：Tastoya (赞：0)

### 题目大意
给你一个数字 $N$，现在希望你用三个数字 $1,A,B$ 拼出 $N$。

但是使用一次 $1$ 要花掉 $X$ 元，用一次 $A$ 花掉 $Y$ 元，用一次 $B$ 花掉 $Z$ 元。

请你求出最小的花费。
### 思路
我们钦定 $a$ 的性价比不低于 $b$，如果不满足就交换。

最多只能取 $\left\lfloor \dfrac{n}{a} \right\rfloor$ 个 $a$，最多只能取 $a-1$ 个 $b$。如果选 $a$ 个 $b$ 的话，我们完全可以用 $b$ 个 $a$ 来代替它，这样不是更优的，所以 $b$ 最多取 $a-1$ 个。

于是有策略：

1. 如果 $a \leq \sqrt{n}$，那么我们枚举 $b$ 的数量；
2. 如果 $a \geq \sqrt{n}$，那么就有 $\left\lfloor \frac{n}{a} \right\rfloor \leq \sqrt{n}$，就枚举 $a$ 的数量。

这两种方法枚举次数都不超过 $\sqrt{n}$，所以时间复杂度约为 $\operatorname{O}(\sqrt{n})$。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int T;

long long n,a,b,x,y,z;

long long ans,tmp;

double val1,val2,val3;

void Work() {
    ans = LLONG_MAX;

    if(a * z < y * b) {
        swap(a,b);
        swap(y,z);
    }

    if(a * x <= y) {
        ans = n * x;
        return ;
    }

    if(b * x <= z) {
        ans = n / a * y + n % a * x;
        return ;
    }

    if(n / a < a - 1) {
        for(int i = 0;i <= (n / a); i++) {
            tmp = n - i * a;
            ans = min(ans,i * y + tmp / b * z + tmp % b * x);
        }
    }
    else {
        for(int i = 0;i <= a - 1; i++) {
            tmp = n - i * b;
            if(tmp >= 0)
                ans = min(ans,i * z + tmp / a * y + tmp % a * x);
        }
    }
    return ;
}

int main() {
#ifdef ONLINE_JUDGE == 1
    freopen("cs.in","r",stdin);
    freopen("cs.out","w",stdout);
#endif
    scanf("%d",&T);

    while(T--) {
        cin >> n >> a >> b >> x >> y >> z;
        
        Work();

        cout << ans << "\n";
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：int_R (赞：0)

大力分讨。感觉绿难度虚高。

平均花费指的是 $x,\dfrac{y}{a},\dfrac{z}{b}$。

#### ① 填 $1$ 的平均花费最小：

显然填 $n$ 个 $1$ 即可。

#### ② 填 $1$ 的平均花费第二小：

假设 $\dfrac{y}{a}\leq x\leq \dfrac{z}{b}$。

这种情况下永远不会填 $b$，所以填 $\lfloor \dfrac{n}{a}\rfloor$ 个 $a$，$n\bmod a$ 个 $1$。

$\dfrac{z}{b}\leq x\leq \dfrac{y}{a}$ 时同理。


#### ③ 填 $1$ 的平均花费最大：

如果 $\max(a,b)\geq \lfloor\sqrt n\rfloor$，那么 $\max(a,b)$ 最多只会被填 $\lfloor\sqrt n\rfloor$ 次，直接枚举这个数被填了多少次即可。

否则假设 $\dfrac{y}{a}\leq \dfrac{z}{b}\leq x$。

如果一个数 $x,\gcd(a,b)\mid x$，那么由于填 $a$ 的平均花费少，所以肯定是由填 $a$ 得到的，所以填 $b$ 的个数不超过 $\dfrac{\operatorname{lcm}(a,b)}{b}$ 个，又由于 $a,b < \lfloor\sqrt n\rfloor$，则 $\operatorname{lcm}(a,b) < n,\dfrac{\operatorname{lcm}(a,b)}{b} < \lfloor\sqrt n\rfloor$。所以直接枚举填了多少个 $b$ 即可。

$\dfrac{z}{b}\leq \dfrac{y}{a}\leq x$ 同理。

单次最坏 $O(\sqrt n)$，总时间复杂度 $O(T\sqrt n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#define int long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x;
}
int T,n,a,b,x,y,z;
signed main()
{
    #ifdef ONLINE_JUDGE
    freopen("cs.in","r",stdin);
    freopen("cs.out","w",stdout);
    #endif
    T=read();
    while(T--)
    {
        n=read(),a=read(),b=read(),x=read(),y=read(),z=read();
        if(x<=y/a&&x<=z/b)
        {
            cout<<n*x<<'\n';
        }
        else if(x<=z/b)
        {
            cout<<(n/a)*y+(n%a)*x<<'\n';
        }
        else if(x<=y/a)
        {
            cout<<(n/b)*z+(n%b)*x<<'\n';
        }
        else if(a>=sqrt(n))
        {
            int ans=1e18+10;
            for(register int i=0;i<=n/a;++i)
                ans=min(ans,i*y+(n-a*i)/b*z+((n-a*i)%b)*x);
            cout<<ans<<'\n';
        }
        else if(b>=sqrt(n))
        {
            int ans=1e18+10;
            for(register int i=0;i<=n/b;++i)
                ans=min(ans,i*z+(n-b*i)/a*y+((n-b*i)%a)*x);
            cout<<ans<<'\n';
        }
        else if(a*z<=b*y)
        {
            int l=a*b/__gcd(a,b),ans=1e18+10;
            for(register int i=0;i<=l/a;++i)
                ans=min(ans,i*y+(n-a*i)/b*z+((n-a*i)%b)*x);
            cout<<ans<<'\n';
        }
        else
        {
            int l=a*b/__gcd(a,b),ans=1e18+10;
            for(register int i=0;i<=l/b;++i)
                ans=min(ans,i*z+(n-b*i)/a*y+((n-b*i)%a)*x);
            cout<<ans<<'\n';
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```


---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc139_b)
# 题目描述
存在整数 $n$，有三种拼接方式。
+ 用 $X$ 的代价填充 `1`；
+ 用 $Y$ 的代价填充 $a$；
+ 用 $Z$ 的代价填充 $b$。

求填充 $n$ 的最小代价。

# 题目分析
对于暴力枚举，~~连复杂度都不用算~~肯定超时。

### 特判
先特判 `1` 的“性价比”。如果 $X\times a<Y$，就更新 $Y=\min\{Y,a\times X\}$。

同理 $Z=\min\{Z,a\times X\}$。
### 然后
可列一个方程，即为：

$\left\{\begin{matrix} 
  n=k_{1}+a\times k_{2}+b\times k_{3}\\
  \min\{k_{1}\times X+k_{2}\times Y+k_{3}\times Z\}
\end{matrix}\right. $

其中 $k_{1}$ 要尽量小，所以方程可化为：

$\left\{\begin{matrix} 
  a\times k_{2}+b\times k_{3}\le n\\
  k_{1}=n-(a\times k_{2}+b\times k_{3})\\
  \min\{k_{1}\times X+k_{2}\times Y+k_{3}\times Z\}
\end{matrix}\right. $
### 分治
因为每一个参数的范围都太大，我们 ~~不难想到~~ 根号分治。

说是分治，其实就是分类讨论。

因为在上个方程中 $k_{2}$ 每增加 $b$，$k_{3}$ 就减少 $a$，

所以 $k_{2}$ 在 $\left [0,n\right]$ 内能取的正整数一共有 $\left\lfloor \frac{n}{b}\right\rfloor$ 个数。

同理，$k_{3}$ 在 $\left [0,n\right]$ 内能取的正整数一共有 $b$ 个数。

因为 $\left\lfloor \frac{n}{b}\right\rfloor\times b\le n$，所以其中必有一数 $\le\sqrt{n}$。
### 最后
时间复杂度：$O(T\times\sqrt{n})$，不会超时。

---

