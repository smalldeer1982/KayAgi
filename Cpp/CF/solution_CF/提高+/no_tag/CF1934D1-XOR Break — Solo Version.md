# XOR Break — Solo Version

## 题目描述

This is the solo version of the problem. Note that the solution of this problem may or may not share ideas with the solution of the game version. You can solve and get points for both versions independently.

You can make hacks only if both versions of the problem are solved.

Given an integer variable $ x $ with the initial value of $ n $ . A single break operation consists of the following steps:

- Choose a value $ y $ such that $ 0 \lt y \lt x $ and $ 0 \lt (x \oplus y) \lt x $ .
- Update $ x $ by either setting $ x = y $ or setting $ x = x \oplus y $ .

 Determine whether it is possible to transform $ x $ into $ m $ using a maximum of $ 63 $ break operations. If it is, provide the sequence of operations required to achieve $ x = m $ .You don't need to minimize the number of operations.

Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

In the first test case $ n = 7 $ , for the first operation $ x = 7 $ if we choose $ y = 3 $ then $ (7 \oplus 3) \lt 7 $ , hence we can update $ x $ with $ 3 $ which is equal to $ m $ .

In the second test case $ n = 4 $ , for the first operation $ x = 4 $ .

If we choose:

- $ y = 1 $ then $ (4 \oplus 1) \gt 4 $
- $ y = 2 $ then $ (4 \oplus 2) \gt 4 $
- $ y = 3 $ then $ (4 \oplus 3) \gt 4 $

Hence we can't do the first operation and it is impossible to make $ x = 2 $ .

## 样例 #1

### 输入

```
3
7 3
4 2
481885160128643072 45035996273704960```

### 输出

```
1
7 3
-1
3
481885160128643072 337769972052787200 49539595901075456 45035996273704960```

# 题解

## 作者：Alex_Wei (赞：7)

### [CF1934D1 XOR Break — Solo Version](https://www.luogu.com.cn/problem/CF1934D1)

首先注意到如果 $m$ 已经是 $n$ 的子集则可以一次操作使得 $n\to m$。

设 $x$ 的最高位为 $h_x$。因为 $y$ 和 $x\oplus y$ 等价（若 $y$ 合法，则 $y\gets x\oplus y$ 同样合法），所以不妨钦定 $x\to y$，考虑 $y$ 的最高位 $d\leq h_x$。

如果 $d < h_x$，那么 $y < x$。为了满足 $x\oplus y < x$ 的限制，$x$ 的第 $d$ 位一定是 $1$，且条件充要。此时贪心地令 $y$ 的第 $0\sim d$ 位均为 $1$，即 $y = 2 ^ {d + 1} - 1$，因为若 $m$ 的最高位大于 $d$ 则一定无解，否则这样做就可以使 $m$ 变成 $x$ 的子集。根据贪心思想，设 $n$ 在二进制下等于 $1$ 的次高位为 $h'_n$，则取 $d = h'_n$ 最优。

如果 $d = h_x$，那么 $x\oplus y < x$。此时为了满足 $y < x$ 的限制，考虑 $x\oplus y$ 的最高位 $d' < d$，则 $x$ 的第 $d'$ 位一定是 $1$，且条件充要。此时贪心地令 $y$ 的第 $0\sim d' - 1$ 位均为 $1$。根据贪心思想，取 $d'$ 为最小的 $b\geq c$ 最优，其中 $c$ 是 $x\oplus y$ 的最高位且 $n$ 的第 $b$ 位为 $1$。也可以枚举 $n$ 的每个等于 $1$ 且不为最高位的位。

如果第一步操作无法使得 $m$ 变为 $n$ 的子集，则容易证明无解。证明过程比较繁琐，就不赘述了。

时间复杂度 $\mathcal{O}(1)$。[代码](https://codeforces.com/contest/1934/submission/251216061)。

---

## 作者：ax_by_c (赞：2)

容易发现若某一位要从 1 变成 0 可以直接变，难点在于 0 变成 1 时前提条件的处理。

1.要求异或上的数不大于原数，所以在原数的更高位中应当存在 1 且不在本次操作中发生改变。

2.要求结果不大于原数，所以在本次操作中更高位应当发生从 1 变成 0 的改变。

所以对于每一个需要从 0 变成 1 的位，更高位中必须存在至少两个 1，且存在需要变成 0 的 1。

然后找出最靠前的需要变成 0 的 1，然后将后面所有的 0 变成 1 都和这个合起来作为第一次操作。因为合法所以原数中必然还存在另一个 1。

然后只需要将其余所有要变成 0 的 1 合起来作为第二次操作即可完成。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void slv(){
	ll a,b;
	scanf("%lld %lld",&a,&b);
	int c10=0,c1=0;
	ll hb=-1;
	for(ll i=60;i>=0;i--){
		if((a&(1LL<<i))){
			c1++;
		}
		if((a&(1LL<<i))&&!(b&(1LL<<i))){
			c10++;
			if(hb==-1){
				hb=(1LL<<i);
			}
		}
		if(!(a&(1LL<<i))&&(b&(1LL<<i))){
			if(!(c1>=2&&c10)){
				puts("-1");
				return ;
			}
		}
	}
	vector<ll>ans;
	ans.push_back(a);
	ll xval=hb;
	for(ll i=60;i>=0;i--){
		if(!(a&(1LL<<i))&&(b&(1LL<<i))){
			xval^=(1LL<<i);
		}
	}
	a^=xval;
	ans.push_back(a);
	if(a!=b){
		ans.push_back(b);
	}
	printf("%d\n",(int)ans.size()-1);
	for(auto x:ans){
		printf("%lld ",x);
	}
	putchar('\n');
}
int main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

模拟赛的时候这道题放在 T4，然而 T3 比这一道高 800 分。/cf

## 解题思路

不难注意到如果 $m\leq n$ 并且 $m\oplus n \leq n$ 一次操作即可完成。

否则，一次操作后得到 $k$，如果无法得到 $k$ 包含 $m$（即对于 $m$ 二进制表示中的每一个 $1$，$k$ 的对应位也为 $1$），那么一定无解（因为每一次 $k\leq n$）。

考虑构造：首先我们使 $k=m$，然后考虑到最小化 $n \oplus k$，可以使得 $k$ 包含 $n$ 的二进制位最高的 $1$，那么我们就一定能保证 $n \oplus k \leq n$，接下来判断 $k$ 是否小于 $n$ 即可。

正确性显然。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void work()
{
	long long n,m,ta,tb,tc,t,k;
	scanf("%lld%lld",&n,&m);
	if(m<=n&&(n^m)<=n)
	{
		printf("1\n%lld %lld\n",n,m);
		return;
	}
	if(m>n)
	{
		printf("-1\n");
		return;
	}
	ta=m;
	tb=(n^m)&m;
	k=n;
	t=1;
	while(k>1)
	{
		k/=2;
		t*=2;
	}
	tc=ta|t;
	ta=tc;
	if(ta<=n&&(n^ta)<=n)
	{
		if((m&ta)!=m)
		{
			ta^=n;
		}
		printf("2\n%lld %lld %lld\n",n,ta,m);
	}
	else
	{
		printf("-1\n");
		return;
	}
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：Engulf (赞：0)

若 $n$ 是 $2$ 的整数次幂，无论 $n$ 异或上小于 $n$ 的任何数都会大于 $n$，所以无解。

否则，记 $a$ 为 $n$ 的**最高有效位**，$b$ 为 $n$ 的次高有效位，$mb$ 为 $m$ 的最高有效位，$a, b, mb$ 都是存在的。

先说结论：若 $mb \in (b, a)$，无解，否则一定有解。

为什么？若 $n$ 要改变 $(b, a)$ 中的第 $mb$ 位，只能选择一个第 $mb$ 位是 $1$ 的 $y$，然后令 $n$ 成为 $n \oplus y$，但 $n \oplus y > n$，非法，所以无解。

否则构造一组方案：
- 若 $mb = a$，此时 $m \oplus n < n$，所以 $1$ 步操作即可。$n \to m$。
- 若 $mb \le b$，不妨令 $y = 2^{b + 1} - 1$，二进制下表示就是 $b$ 个 $1$，这样，$n \oplus y$ 的第 $b$ 位就是 $0$，一定小于 $n$，所以可以将 $n$ 变为 $2^{b + 1} - 1$。又因为操作可以将 $1$ 随便去掉，所以只要遍历 $0$ 到 $b$，看看 $m$ 这一位是什么，如果是 $0$ 就把这一位的 $1$ 去掉。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        ll n, m;
        cin >> n >> m;

        if ((1ll << __lg(n)) == n) {cout << "-1\n"; continue;}

        auto getmsb = [](ll x) {for (int i = 59; ~i; i--) if (x >> i & 1) return i;};

        int a = getmsb(n), b = getmsb(n - (1ll << a)), mb = getmsb(m);

        if (b < mb && mb < a) {cout << "-1\n"; continue;}

        if (mb <= b) {
            vector<ll> ans;
            ans.emplace_back((1ll << b + 1) - 1);
            for (int i = b; ~i; i--)
                if ((ans.back() >> i & 1) && !(m >> i & 1))
                    ans.emplace_back(ans.back() - (1ll << i));

            cout << ans.size() << "\n" << n << " ";
            for (auto i: ans) cout << i << " ";
            cout << "\n";
        } else if (mb == a) {
            cout << "1\n" << n << " " << m << "\n";
        }
    }
    return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

# Part 1 前言

被机房同学 @hujiasheng1234 嘲讽，说我只会 ctj 才刷蓝题，~~大家给我狠狠怼回去！~~ 今天用 1.8 hr 不看题解自己调出了这道题……

# Part 2 思路

一道分类讨论题。

- 当 $m<x$ 且 $m \oplus x<x$ 时，直接选择 $m$。

- 当 $x=m$ 时，不用操作。

- 当 $\log_2 x=\log_2 m$ 时，只要将 $x \oplus m$ 即可。

- 当 $m>x$ 且 $\log_2 x \neq \log_2 m$ 时，不可以总司令。

- 当 $x=2^k$ 时，不可以总司令。

- 否则令 $x$ 在 $2$ 进制下的位数为 $k$，暴力枚举 $x$ 的后 $i(1 \le i \le k)$ 位。

    - 当 $x$ 的后 $k-1$ 位 $< m$ 时，不可以总司令。
    - 当 $x$ 的后 $k-1$ 位 $\ge m$ 时，取使式子成立的最小的 $i$，输出 $x \oplus (x$ 的后 $i$ 位 $)\oplus m$。


# Part 3 代码

温馨提示：
- 请不要用 STL 自带函数，不然后果自负！
- 一定要开 `long long`！
- 不要复制代码，有惊喜！


```cpp
#include<bits/hhyakioi.h>
#define int long long
using namespace std;
int x,m,pre[64];
int func2(int x){
	int ans,l=0,r=63;
	while(l<=r){
		int mid=(l+r)>>1;
		if(pre[mid]<=x){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}
void solve(){
	scanf("%lld%lld",&x,&m);
	if(x==m){
		puts("0");
		return ;
	}
	if(x>m&&(x^m)<x){
		puts("1");
		printf("%lld %lld\n",x,m);
		return ;
	}
	signed lgx=func2(x),lgm=func2(m);
	if(x<m){
		if(lgx!=lgm){
			puts("-1");
			return ;
		}
		puts("1");
		printf("%lld %lld\n",x,(m^x));
		return ;
	}
	if(lgx==lgm){
		puts("1");
		printf("%lld %lld\n",x,(m^x));
		return ;
	}
	if(pre[lgx]==x){
		puts("-1");
		return;
	}
	signed pos=0;
	while((x&(pre[pos]-1))<m)pos++;
	if(pos>lgx){
		puts("-1");
		return ;
	}
	puts("2");
	printf("%lld %lld %lld\n",x,x^(x&((pre[pos]-1))^m),m);
	return ;
}
signed main(){
	pre[0]=1;
	for(int i=1;i<63;i++) pre[i]=pre[i-1]*2;
	signed t;
	cin>>t;
	while(t--) solve();
	return 0;
}
祝：CSP 考试上岸！
坐标：ZJNB
/*
1
822981260158260525 559372470403133003
*/

```

---

