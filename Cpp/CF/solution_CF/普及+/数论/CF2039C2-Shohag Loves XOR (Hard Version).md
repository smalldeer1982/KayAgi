# Shohag Loves XOR (Hard Version)

## 题目描述

题为困难版本，简单版本和复杂版本之间的区别以粗体标出。

给定两个整数 $x$ 和 $m$，请找出满足以下条件的整数 $y$ 的个数：
- $1⩽y⩽m$。
- $x\oplus y$ 是 $x,y$ 两个数中至少一个数的**倍数**，其中 $\oplus$ 代表异或运算。

## 说明/提示

在第一个测试用例中，对于 $ x = 7 $，在 $ 1 $ 到 $ m = 10 $ 的整数范围内，有 $ 3 $ 个符合条件的 $ y $ 值，分别是 $ 1 $、$ 7 $ 和 $ 9 $。  

- **$ y = 1 $**  符合条件，因为 $ x \oplus y = 7 \oplus 1 = 6 $，而 $ 6 $ 能被 $ y = 1 $ 整除。  
- **$ y = 7 $**  符合条件，因为 $ x \oplus y = 7 \oplus 7 = 0 $，且 $ 0 $ 同时能被 $ x = 7 $ 和 $ y = 7 $ 整除。  
- **$ y = 9 $**  符合条件，因为 $ x \oplus y = 7 \oplus 9 = 14 $，而 $ 14 $ 能被 $ x = 7 $ 整除。  


 
 ---
 对于 $100\%$ 的数据，$1⩽t⩽10^4$，$ 1 \le x \le 10^6 $，$ 1 \le m \le 10^{18} $。
 
保证所有测试用例中 $ x $ 的总和不超过 $ 10^7 $。

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1```

### 输出

```
3
2
2
6
1```

# 题解

## 作者：littlebug (赞：9)

## Solution

设 $t$ 为 $x$ 的最高二进制位的上一位为 $1$，其它位为 $0$ 所组成的数。然后发现若 $y \ge t$，则不可能存在 $y ~|~ x \oplus y$，于是可以先把 $< t$ 的部分枚举出来。对于 $\ge t$ 的部分由于只有 $x \oplus y$ 为 $x$ 的倍数时才可以。

显然暴力枚举是不行的，那这个 $y$ 如何统计呢？

通过写了一个暴力，我们发现满足条件的 $y$ 看起来**好像**有单调性（合法性形如 $1,1,1,\ldots,0,0,0$，但中间可能出现一些前 $0$ 后 $1$ 的情况）！所以可以二分，然鹅这个单调性并不怎么优秀，得到结果后判一下前十个后十个数即可。

然后就这样二分乱搞过了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>

#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

int x,m;

il int gm(int x)
{
    int ans=0;
    while(x) ++ans,x>>=1;
    return (1ll<<ans)-1;
}

il bool check(int mid)
{
    return (x^mid)<=m;
}

il void solve(int __Ti)
{
    cin>>x>>m;

    if(m<=x*2)
    {
        int cnt=0;
        rep(i,1,m) ((x^i)%x==0 || (x^i)%i==0) && (++cnt,1);
        return cout<<cnt<<'\n',void();
    }

    int t=gm(x);

    int cnt=0;
    rep(i,1,t) ((x^i)%x==0 || (x^i)%i==0) && (++cnt,1);

    int l=1,r=m/x+100,mid=-1;
    while(l<r)
    {
        mid=l+r+1>>1;
        check(x*mid) ? (l=mid) : (r=mid-1);
    }
    
    cnt+=l-1;
    rpe(i,l,max(l-10,1ll)) !check(x*i) && (--cnt,1);
    rep(i,l+1,l+10) check(x*i) && (++cnt,1);

    cout<<cnt<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int __T; cin>>__T; rep(__Ti,1,__T) solve(__Ti);
    return 0;
}
```

---

## 作者：Enoch006 (赞：4)

这个题考察了我们对异或的理解。

在文章的开头，我们需要知道本题的重点：

异或的本质是**不进位加法、不借位减法**。

形式化的说：$|x-y| \le x\oplus y\le x+y$。

----

对于此题，可以将答案拆成 $x|x\oplus y+y|x\oplus y-[x,y]|x\oplus y$。

1. 处理 $x|x\oplus y$。

   $x\oplus y=2x,3x,4x\dots kx $。

   $x\oplus 2x=y,x\oplus 3x=y,x\oplus 4x=y\dots x\oplus kx=y$。

   求所有式子中 $y\le m$ 的个数，根据异或的性质：
   
   - 因为 $x\oplus kx\le x+kx$，所以当 $k\le\left\lfloor\frac{m-x}{x}\right\rfloor$ 时，$y$ 一定合法。
   - 因为 $kx-x\le x\oplus kx$，所以当 $k>\left\lfloor\frac{m+x}{x}\right\rfloor$ 时，$y$ 一定不合法。
   - 注意到还剩 $\left\lfloor\frac{m-x}{x}\right\rfloor<k\le \left\lfloor\frac{m+x}{x}\right\rfloor$，这其中的 $k$ 最多只有两个，直接暴力判断即可。
2. 处理 $y|x\oplus y$。

   $x\oplus y=2y,3y,4y\dots ky $。

   $y\oplus 2y=x,y\oplus 3y=x,y\oplus 4y=x\dots y\oplus ky=x$。
   
    根据异或的性质：

    $y\oplus ky\ge ky-y\ge y$

   因此，当 $y>x$ 时，一定不合法，所以直接暴力枚举 $y$ 判断即可。
3. 处理 $[x,y]|x\oplus y$。
    注意到我们可以在处理 $2$ 情况时，顺便判断 $x$ 是否整除 $x\oplus y$ 即可。

最后，如果你理解了异或的本质，这题的代码就很容易了。

---

## 作者：Limerency (赞：4)

### Solution

我们考虑记 $p = x\oplus y$，求 $y$ 的个数可以直接等价为求 $p$ 的个数。做一个小分讨：

- 若 $y < x$，没有好的统计方法，暴力枚举。
- 若 $x = y$，一定可以。答案加 $1$。
- 若 $x > y$，此时显然地，所有 $x$ 的倍数都可以作为合法的 $p$，至少 $\lfloor\frac{m-x}{x}\rfloor$ 个 $p$。特别地，特判下边界情况，因为 $p$ 最大可能取到 $m + x$。

时间复杂度 $\mathcal{O}(x)$，可以通过测试。做完了。

### Code

```cpp
namespace Solve {
    void solve() {
        i64 x, m; cin >> x >> m;
        i64 maxp = m - m % x;
        i64 ans = maxp / x - (x < maxp);
        if (1 <= (maxp ^ x) && (maxp ^ x) <= m) ans ++;
        if (1 <= ((maxp + x) ^ x) && ((maxp + x) ^ x) <= m) ans ++;
        for (int i = 1; i <= min(x, m); i ++) if ((x ^ i) % i == 0) ans ++;
        cout << ans - (x <= m) << '\n';
    }
}
```

---

## 作者：LiJoQiao (赞：3)

仅以此题纪念我赛时会但是写挂了一万年的 C2。  

### 题意翻译  
$t$ 组数据。  
求 $y\in \left[1,m\right]$ 中满足 $x\bigoplus y \mid x$ 或 $x\bigoplus y \mid y$ 的 $y$ 的数量。  
### sol  
分类讨论两种情况。  
当 $x\bigoplus y \mid x$ 时，令 $x\bigoplus y= i\times x$，$y=(i\times x)\bigoplus x$，得 $y\in \left[(i-1)\times x,(i+1)\times x\right]$。  
令 $j=\left\lfloor\dfrac{m}{x}\right\rfloor$，得 $j\times x\le m<(j+1)\times x$。  
因此当 $i+1\le j$ 时，$y$ 一定满足 $y\le m$，由异或运算后非负的性质可得 $y\ge 1$ 或 $y=0$，我们需要排除后者 $y=0$，即 $i=1$ 时，因此我们把 $i\in[0,j-1],i\neq1$ 中 $i$ 的数量统计起来。  
$i=j$ 或 $i=j+1$ 时由值域得可能满足答案，需要特判。  

当 $x\bigoplus y \mid y$ 时，若 $y<x$，我们可以用枚举的方式统计。  
当 $y\ge x$ 时，令 $x\bigoplus y=i\times y\in\left[y-x,x+y\right]$，$x+y\le2\times y$ 当且仅当 $y=x$ 时等号成立。  
令 $i=0$，得 $x=y$。  
令 $i=1$，得 $x=0$，舍去。  
令 $i=2$，得 $2\times y\le x+y$，所以 $y=x$，不符合题意，舍去。  

至此我们已处理完所有情况，但是我们可能有重复的情况，我们需要去重。  

前者中 $i\in[0,j+1],i\neq 1$，$i=0$ 时 $y=x$。  其他情况下由 $y\in \left[(i-1)\times x,(i+1)\times x\right]$ 得 $y\ge x$，但 $y=x$ 时 $i=0$ 故 $y>x$。  
后者由前面的讨论得 $y\le x$，两者的交为 $y=x$，不要重复统计此情况即可。  

空间复杂度为 $O(1)$。  
时间复杂度的开销主要在枚举，复杂度为 $O(\sum x)$。  

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int x;
ll m,ans;
template<typename T>
T read(){
	T f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return f*x;
}
namespace sol{
	void solve(){
		ans=0;
		x=read<int>();m=read<ll>();
		ll j=m/x;
		ans+=j;
		if(1<=((j*x)^x)&&((j*x)^x)<=m)++ans;
		if(1<=(((j+1)*x)^x)&&(((j+1)*x)^x)<=m)++ans;
		if(j-1>=1)--ans;//排除y=0的情况 
		for(int y=1;y<=min((ll)(x-1),m);++y){
			if((x^y)%y==0){
				++ans;
			}
		}
		printf("%lld\n",ans);
	}
}
int main(){
	int T=read<int>();
	while(T--)sol::solve();
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

首先看到题目是没有任何思路的，肯定是先把暴力写出来，枚举出每一个合法的 $y$，会发现从 $y=x$ 开始，相邻的两个 $y$ 之间的差总是会出现循环，且长度为 $2^{\lfloor\log_2 x\rfloor}$。因此就可以的出一个思路：先暴力枚举 $y<x$ 的部分，判断是否合法，这一部分的时间复杂度为 $O(x)$，可以接受，而对于循环的部分，我们显然可以用 $m-x$ 去除以循环节内 $x\oplus y$ 增加的值，时间复杂度为 $O(1)$，但是最后可能循环节不完整，所以还需要找到剩余的部分，所以还需要再枚举一次，时间复杂度为 $O(x)$，这个程序的时间复杂度为 $O(x)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("O3")
using namespace std;
void solve()
{
	int x,m,now,maxx=0,cnt=0;
	cin>>x>>m;
	now=1ll<<((int)log2(x)+1);
	for(int y=1;y<=min(m,x);y++) if((x^y)%x==0||(x^y)%y==0) cnt++;
	for(int z=x+x;z<=now*x+x;z+=x) maxx=max(maxx,x^z);
	if(m<x) cout<<cnt<<"\n";
	else
	{
		cnt+=now*((m-x)/(maxx-x));
		m=(m-x)%(maxx-x)+x;
		for(int z=x+x;z<=now*x+x;z+=x) if((x^z)<=m) cnt++; 
		cout<<cnt<<"\n";
	}
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

## 作者：OIer_Hhy (赞：0)

挺有意思的一道小题。

看到数据范围可知，本题时间复杂度应该是 $O(n)$。

我们把条件拆成两个：

- $x \mid x \oplus y $。打表尝试可得 $x \le y \le x \times (2^k+1)(k=\lceil\log_2 x\rceil)$。于是我们直接枚举 $ix(1\le i \le 2^k+1)$，把能被 $x$ 整除的 $ix \oplus x$ 的个数算出来。
- $y \mid x \oplus y$。打表尝试可得 $ 1 \le y < x$，直接枚举即可。

[my code](https://codeforces.com/contest/2039/submission/298950435)

---

## 作者：wfc284 (赞：0)

对于正整数 $x,y$，不妨令 $x \leq y$。  
分成如下两类：

1. $y|x \oplus y$：而 $x \oplus y \leq x+y < 2y$，注意第二个等号是取不到的，因为取等条件。于是 $x \oplus y = 1 \cdot y$，得 $x = 0$，舍。
2. $x|x\oplus y$：设 $x \oplus y = kx$。同上有 $kx \leq x+y$，则 $(k-1)x \leq y \leq m$，故 $k$ 满足的必要条件是 $k \leq \lfloor \frac{m}{x} \rfloor + 1$。

故将可能的 $y$ 分成两部分，一种是小于等于 $x$ 的，一种是大于 $x$ 的。  
小于等于 $x$ 的直接枚举判定就好。  
大于 $x$ 的，发现 $k$ 与解一一对应，故只要数 $k$ 的个数。我们考虑所有小于等于 $\lfloor \frac{m}{x} \rfloor+1$ 的 $k$，不能直接统计，因为 $k$ 可能是断断续续的（即 $k=\lfloor \frac{m}{x} \rfloor$ 时成立，但 $k = \lfloor \frac{m}{x} \rfloor$ 时不成立）。我们看不清，但猜断断续续的情况不会很多，于是直接枚举判定最后 $10^4$ 个，其他默认成立。  

做完了，代码很短，只有 8 行。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define int long long
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	
	int x, m;
	
	void main() {
		scanf("%lld%lld", &x, &m);
		int ans = 0;
		for(int i = 1; i <= min(x, m); ++i)
			if((x ^ i) % i == 0) ++ans;
		int k = m / x + 1;
		for(int c = max(k - (int)1e4, 2ll); c <= k; ++c)
			if((c * x ^ x) <= m) ++ans;
		printf("%lld\n", ans + max(k - (int)1e4 - 2, 0ll));
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：Dangerise (赞：0)

~没觉得和 C1 有什么联系啊~

这题与 C1 很不一样，不过既然是异或操作，我们还是从二进制的角度去分析。

设 $x$ 的二进制位数为 $k$ 。

与 C1 类似的是，我们可以发现，当 $y\ge 2^k$ , $x \oplus y$ 不可能是 $y$ 的倍数 。

当 $y \ge 2^k$ 。

对于 $x \oplus y$  的结果, 相较于 $y$ ，变化的肯定只有后 $k$ 位，即 $y$ 的最高位是不变的。

那么很显然 $x \oplus y < 2y$ , 即 $x \oplus y $ 不可能是 $y$ 的倍数 ($x \not= 0$)。

异或有一个很显然的性质，对于 $y \in [0,2^k-1]$, 则 $x \oplus y \in [0,2^k-1]$ 。

理解一下，对于每一个二进制位，我们可以通过操作 $y$ 的值，使得这一位上既可以取 $0$ 也可以取 $1$ 。

进行一步推广，对于 $y \in [a \cdot 2^k,a \cdot 2^k + 2^k-1]$ ， 即 $y$ 的后 $k$ 位可以任取，前面的位数固定，也有 $x \oplus y \in [a \cdot 2^k,a \cdot 2^k + 2^k-1]$ 。

通过这个性质，我们可以对 $y$ 分段处理。

更具体一点，我们设 $m=110100$ 。

- $y=1100??$

- $y=10????$

- $y=0?????$

其中 $?$ 代表这一位可以任取 $0$ 或 $1$ 。

我们可以把 $y$ 分成这三段，每一段分别求解其对答案的贡献。

有点类似于数位 DP ，对于 $y$ 的每一个 1 的二进制位，我们固定左边的位，使右边的位任取，然后统计它的贡献。

最后用一点小小的容斥处理 $x$ 与 $y$ 的答案交集。

```cpp
int lowbit(int x) { return x & (-x); }
int highbit(int x) {
    int l = 0;
    while (x) {
        l = lowbit(x);
        x -= l;
    }
    return l;
}
 
signed main() {
    int T = qread();
    while (T--) {
        int x = qread(), m = qread();
        int f = highbit(x) * 2;
        int b = min(f, m);
        int cx = 0, cy = 0, both = 0;
        L(i, 1, b) {
            int v = i ^ x;
            if (v % i == 0 && v % x == 0) {
                both++;
            }
            if (v % i == 0) {
                cy++;
            }
            if (v % x == 0) {
                cx++;
            }
        }
        if (m > f) {
            cx = 0;
            int gt = m / f * f;
            int e = m;
            while (e > gt) {
                int l = lowbit(e);
                e -= l;
                L(i, 1, l) {
                    int v = (e + i) ^ x;
                    if (v % x == 0) {
                        cx++;
                    }
                }
            }
            while (gt) {
                int l = lowbit(gt);
                gt -= l;
                cx += (gt + l) / x - gt / x;
            }
        }
        int ans = cx + cy - both;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

给定 $x,m$，求有多少 $y$ 满足 $y \in [1,m]$ 使得 $x \oplus y$ 可以被 $x$ 或 $y$ 整除。

设 $p = x \oplus y$，分三种情况讨论：

1. $x | p$。设 $p = kx$，则 $y = x \oplus p \le p + x \le m$，也就是 $kx \le m - x$，进一步化简可知 $k \le \lfloor \frac{m - x}{x} \rfloor$。由于我们还有 $(m - x,m]$ 区间未检测，但可以充分利用 $x \oplus y \le x + y$ 这个性质，我们循环判断 $(m - x,m + x]$ 区间即可（当然，官方解答的做法更加简洁，但是没看懂）。

2. $y | p$。当 $0 < x < y$ 时，$p \le x + y < y + y = 2y$，因此 $p = ky(k \ge 2)$ 不存在解。因此只需要考虑 $y \le x$ 的情况。

3. $x | p$ 且 $y | p$。当 $x \neq y$ 时，$\rm{lcm(x,y)} \ge 2 \max (x,y)$，然而 $p < 2 \max (x,y)$，因此只有 $x = y$ 时才能成立。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline ll read ();
ll t;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		ll x = read (),n = read (),cnt = (n - x) / x + (n < 2 * x && x <= n);
		for (ll i = (n - x) / x * x + 1;i <= n + x;++i) //枚举 x ^ y 
			if (1 <= (i ^ x) && (i ^ x) <= n && i % x == 0) ++cnt;
		for (ll i = 1;i <= min (n,x);++i) // 枚举 y 
			if ((x ^ i) % i == 0) ++cnt;
		printf ("%lld\n",cnt - (n >= x));
	}
	return 0;
}
inline ll read ()
{
    ll s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：sbno333 (赞：0)

考虑对于 $y>2x$，$x\oplus y$ 二进制最高位和 $y$ 的一样，因此不为 $y$ 的倍数，枚举 $y\le 2x$ 后，考虑枚举 $x\oplus y$ 的所有合法结果，问题变成多少个 $k$，满足 $kx\oplus x\le m$，然后做一些细节处理，考虑将 $kx$ 拆成两份，变为 $(\lfloor\frac{k}{2^{\lceil\log_2 x\rceil}}\rfloor\times {2^{\lceil\log_2 x\rceil}}+k\bmod {2^{\lceil\log_2 x\rceil}})x$，两份互不影响，第一份异或后不变，考虑第一份的取值范围为 $0\sim \lfloor\frac{m}{2^{\lceil\log_2 x\rceil}}\rfloor\times {2^{\lceil\log_2 x\rceil}}$，只要不是最后一个取值，第二份怎么取都不会超，但如果是最后一个，就要枚举，但复杂度是对的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int query(int x,int m){//how many k*x<=m
	int g;
	g=__lg(x)+1;
	int p;
	p=(1ll<<g)*x;
	int z;
	z=m/p;
	int ans;
	ans=0;
	ans+=z*p/x;
	if(ans){
		ans--;
	}
	z*=p;
	for(int i=0;i<=2*p/x;i++){
		int cc;
		cc=z+i*x;
		if(cc==x){
			ans--;
		}
		if((cc^x)<=m){
			ans++;
		}
	}
	return ans-(x<=m);
}
void _main(){
	int x,m;
	cin>>x>>m;
	int ans;
	ans=0;
	for(int o=0;o<=2*x;o++){
		if((o%x==0||o%(o^x)==0)&&(o^x)<=m&&(o^x)){
			ans++;
		}
	}
	ans+=query(x,m);
	if((x^(2*x))<=m){
		ans--;
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

