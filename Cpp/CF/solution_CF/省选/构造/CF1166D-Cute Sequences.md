# Cute Sequences

## 题目描述

给定一个正整数 $m$，我们称一个正整数序列 $x_1, x_2, \dots, x_n$ 是 $m$-可爱（$m$-cute）的，如果对于每一个满足 $2 \le i \le n$ 的下标 $i$，都存在一个正整数 $r_i$，使得 $1 \le r_i \le m$，并且 $x_i = x_{i-1} + x_{i-2} + \dots + x_1 + r_i$。

你将得到 $q$ 个询问，每个询问包含三个正整数 $a$、$b$ 和 $m$。对于每个询问，你需要判断是否存在一个 $m$-可爱序列，其首项为 $a$，末项为 $b$。如果存在这样的序列，你还需要给出一个示例。

## 说明/提示

考虑样例。在第一个询问中，序列 $5, 6, 13, 26$ 是合法的，因为 $6 = 5 + \mathbf{\color{blue} 1}$，$13 = 6 + 5 + \mathbf{\color{blue} 2}$，$26 = 13 + 6 + 5 + \mathbf{\color{blue} 2}$，其中加粗的值都在 $1$ 到 $2$ 之间，所以该序列是 $2$-可爱序列。其它合法的序列，如 $5, 7, 13, 26$ 也是可以接受的。

在第二个询问中，唯一可能的 $1$-可爱序列以 $3$ 开头为 $3, 4, 8, 16, \dots$，其中不包含 $9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 26 2
3 9 1
```

### 输出

```
4 5 6 13 26
-1
```

# 题解

## 作者：5ab_juruo (赞：2)

给一种不同的做法。

对序列 $x_i$ 取前缀和 $s_i$，式子转化成 $s_i=2s_{i-1}+r_i$，且 $s_1=a$，$b-m\le s_{k-1}\le b-1$。

先特判 $a=b$，然后 $p$ 从 $k-1$ 开始，维护 $s_p$ 的合法区间，如果 $a$ 不在这个区间就倒推一步操作，直到满足条件为止。

至于构造，记录下倒推时每一步的右端点，从 $a$ 开始推，尽量取较大的前缀和即可。

```cpp
typedef long long ll;

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int cas;
	ll a, b, m;
	
	cin >> cas;
	while (cas--)
	{
		cin >> a >> b >> m;
		if (a == b)
		{
			cout << "1 " << a << "\n";
			continue;
		}
		
		ll l = b - m, r = b - 1;
		vector<ll> stk, ans;
		
		while (a < l)
		{
			stk.push_back(r);
			// 2pf = [l - m, r - 1]
			
			l = (l - m + 1) / 2;
			r = (r - 1) / 2;
		}
		
		if (a > r)
			cout << "-1";
		else
		{
			ll prepf = 0;
			
			while (a < b)
			{
				ans.push_back(a - prepf);
				prepf = a;
				if (stk.empty())
					break;
				a = min(2 * a + m, stk.back());
				stk.pop_back();
			}
			ans.push_back(b);
			
			cout << ans.size();
			for (auto x : ans) cout << " " << x;
		}
		
		cout << "\n";
	}
	
	return 0;
}
```

---

## 作者：81179332_ (赞：2)

多写几项可以发现：$b=2^{k-2}\cdot a+\sum\limits_{i=2}^{k-1}2^{k-i-1}\cdot r_i+r_k$

由于 $k$ 的范围很小，我们可以枚举 $k$

我们将 $b$ 减掉 $2^{k-2}\cdot a$，然后从 $r_2$ 到 $r_{k-1}$ 贪心选可能的最大的

容易发现，这样是有问题的，因为 $r_i\ge 1$，我们前一位贪心选最大，可能导致本位 $r_i$ 只能取 $0$

所以我们将所有的 $r_i$ 都减掉 $1$，此时 $b'=b-2^{k-2}\cdot a-(\sum\limits_{i=0}^{k-3}2^i)-1=b - (a+1)\cdot2^{k-2}$

注意特判 $a=b$ 的情况

```cpp
//timeuse:20min
ll a,b,m;
ll n,r[100];
int main()
{
	int T = read();
	while(T--)
	{
		r[1] = a = read(),b = read(),m = read();
		if(a == b) { pprint(1),fprint(a);continue; }
		for(n = 2;n <= 50;n++)
		{
			ll res = b - (a + 1) * (1ll << n - 2);
			if(res < 0) { n = 51;break; }
			for(int i = 2;i < n;i++)
				r[i] = min(m - 1,res / (1ll << n - i - 1)),res -= r[i] * (1ll << n - i - 1);
			if(res < m) { r[n] = res;break; }
		}
		if(n == 51) { puts("-1");continue; }
		ll sum = a;for(int i = 2;i <= n;i++) r[i] += sum + 1,sum += r[i];
		pprint(n);for(int i = 1;i <= n;i++) pprint(r[i]);putchar('\n');
	}
}

```

---

## 作者：ywy_c_asm (赞：2)

orz当场秒切此题的 @枫林晚 神犇，这解法是从他那学的……

首先我们可以发现在让每个$x_i$都尽量小的情况下是这样的：

$a,a+1,2a+2,4a+4,8a+8…$

也就是说$x_i$最小为$2^{i-1}(a+1)$（这里的$i$从0开始，不考虑第0项）

同理$x_i$最大为$2^{i-1}(a+m)$。

那么我们可以枚举$n$，直到存在一个$n$使得$b\in[2^{n-1}(a+1),2^{n-1}(a+m)]$，显然就可以构造出$a_n=b$了。

然后我们就闻到了一股二进制拆分的气息……

我们发现，如果给每一位确定一个$r_1,r_2…r_n$的话，那么会长成这样：

$a,a+r_1,2a+r_1+r_2,4a+2r_1+r_2+r_3,8a+4r_1+2r_2+r_3+r_4$

即$x_i=2^{i-1}a+\sum_{j=1}^{i-1}2^{i-j-1}r_j+r_i$

那么我们就知道了$b=x_n=2^{n-1}a+\sum_{i=1}^{n-1}2^{n-i-1}r_i+r_n$

然后我们就有这么一个贪心的思路，我们希望确定$r_1,r_2…r_n$来凑出$b-2^{n-1}a$，并且希望使得$r_i<=m$，那么可以从前往后贪心，每次让当前的$r_i$尽量的大。

一个很自然的思路就是维护剩余的$rest_i=\sum_{j=i}^{n-1}2^{n-j-1}r_j+r_n$，然后令$r_i=\min(m,\lfloor\frac{rest_i}{2^{n-i-1}}\rfloor)$。

但是这样有个问题，因为题目要求$r_i\in[1,m]$，我们不能让$r_i=0$。

不过我们可以令$r'_i=r_i-1$，这样的话只要限制$r'_i\in[0,m-1]$就行了，那么$b=2^{n-1}a+\sum_{i=1}^{n-1}2^{n-i-1}(r'_i+1)+r'_n+1=2^{n-1}(a+1)+\sum_{i=1}^{n-1}2^{n-1-i}r'_i+r'n$，就可以使用上述方法凑了。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
namespace ywy {
	void ywymain() {
	    int q;
	    cin >> q;
	    while (q) {
	        q--;
	        int a, b, m;
	        cin >> a >> b >> m;
	        if (a == b) {
	            printf("1 %lld\n", a);
	            continue;
	        }
	        if (a > b) {
	            cout << -1 << endl;
	            continue;
	        }
	        int n = 0;
	        while (n <= 49) {
	            n++;
	            int l = (1ll << (n - 1)) * (a + 1), r = (1ll << (n - 1)) * (a + m);
	            if (l > b) {
	                n = 51;
	                break;
	            }
	            if (b <= r && b >= l)
	                break;
	        }
	        if (n >= 50) {
	            cout << -1 << endl;
	            continue;
	        }
	        printf("%lld %lld ", n + 1, a);
	        int tot = 0, sum = a;
	        for (register int i = 1; i < n; i++) {
	            int r = min((b - (1ll << (n - 1)) - (1ll << (n - 1)) * a - tot) / (1ll << (n - i - 1)), m - 1);
	            tot += (1ll << (n - i - 1)) * r;
	            printf("%lld ", sum + r + 1);
	            sum += sum;
	            sum += r + 1;
	        }
	        printf("%lld\n", b);
	    }
	}
}
signed main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：_edge_ (赞：0)

做出了 $2200$ 的构造题。

首先可以列出这些式子是：

$x_2=x_1+r_2$

$x_3=x_2+x_1+r_3$

我觉得这些东西看着不太优美，要拆成 $r_i$ 和 $x_1$ 的形式。

$x_2=x_1+r_2$

$x_3=x_1 \times 2 +r_2 + r_3$

$x_4=x_1 \times 4 +r_2 \times 2 + r_3 + r_4$

$x_5=x_1 \times 8 +r_2 \times 4+r_3 \times 2+r_4 + r_5$

发现这些项的系数均为 $2$ 的次幂，可以预处理出来。

然后 $b$ 就具有了上下界，可以 check 他是否合法。

长度可以自己枚举出来，同时注意一下溢出的问题。

然后考虑如何构造答案序列。

一种可行的想法是，全部都填上 $1$，然后从头开始，如果能填 $m$ 则填上去，还有冗余的则全部加上去。

这样可以保证是符合的，~~证明我不会。~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=55;
int t,a,b,m,aa[INF],ans[INF],ans1[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	aa[1]=1;aa[2]=1;
	for (int i=3;i<=50;i++) aa[i]=aa[i-1]*2;
	while (t--) {
		memset(ans,0,sizeof ans);
		memset(ans1,0,sizeof ans1);
		cin>>a>>b>>m;int fl=0;
		for (int k=1;k<=50;k++) {
			int L=1e18;
			if (L/aa[k]<a) break;
			int bb=a*aa[k],xx=k-1,Max=bb,Min=bb;
			for (int p=1;p<k;p++) {
				Max+=aa[xx]*m;
				Min+=aa[xx];
				ans[p]=1;xx--;
			}
			if (b>=Min && b<=Max) ;
			else continue;
			fl=1;
			cout<<k<<" "<<a<<" ";
			xx=k-1;
			int R=b-Min;
			for (int p=1;p<k;p++) {
				if (aa[xx]*(m-1)<=R) {
					R-=aa[xx]*(m-1);
					ans[p]=m;
				}
				else {
					int C=min(m-1,R/aa[xx]);
					R-=C*aa[xx];
					ans[p]+=C;
				}
				xx--;
			}
			ans1[1]=a;int sum=ans1[1];
			for (int p=2;p<=k;p++) {
				cout<<sum+ans[p-1]<<" ";
				sum=ans[p-1]+sum+sum;
			}
			cout<<"\n";
			fl=1;
			break;
		}
		if (!fl) cout<<"-1\n";
	}
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

写篇题解祭一下因为脑子短路而逝去的几个小时
# Description
给定一个正整数$m$，定义一个正整数序列$x_1,x_2,x_3,...,x_n$，满足对于$2\le i\le n$有$x_i=x_{i-1}+x_{i-2}+...+x_1+r_i$，其中$1\le r_i\le m$  
现在给出$q$个询问，每个询问给出$a,b,m$，强制要求$x_1=a$，$x_n=b$，要求构造出一个长度不超过$50$的$x$序列 
# Input
第一行一个正整数$q(1\le q\le 10^3)$表示询问数  
接下来$q$行，每行三个正整数$a,b,m(1\le a,b,m\le 10^{14},a\le b)$，意义见题面
# Output
没有合法序列输出$-1$  
有合法序列则先输出序列长度$k(k\le 50)$，然后$k$个数$x_1,x_2,...,x_k(1\le x_i\le 10^{14})$，其中$x_1=a,x_k=b$
# Sample Input
``` input
2
5 26 2
3 9 1
```
# Sample Output
```
4 5 6 13 26
-1
```
# Solution
又被sb题整弱智了.jpg  
很容易推出$b=2^{k-2}\cdot a+2^{k-3}\cdot r_2+...+2^{k-i-1}\cdot r_i+...+r_{k-1}+r_k$  
首先特殊情况是$a=b$，这时候直接输出$1\;a$  
考虑到$k$很小，先枚举长度$k$  
这时候$a$是确定的，因此可以先把$a$的部分减掉，同时把每个$r_i$都减$1$，这样来保证求出的$r_i$都是$\ge0$的，那么此时$0\le r_i\le m-1$  
定义$cha=n-2^{k-2}\cdot a-2^{k-2}$  
从$r_2$到$r_{k-1}$贪心考虑，系数大的尽量大，同时要注意不能超过$m-1$  
这样构造出来，最后剩余的$r_k=cha$如果在$m$以内，就是合法的  
具体不清楚可以看代码  
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 6e2 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll r[N];

int main(void) {
	rg int q = fast_IO::read();
	while (q--) {
		rg ll a = fast_IO::read(), b = fast_IO::read(), m = fast_IO::read();
		if (a == b) { printf("1 %I64d\n", a); continue; }
		rg bool can = false; r[1] = a; rg int len;
		for (rg int k = 2; k <= 50 && !can; ++k) {
			rg ll cha = b - a * (1ll << k - 2) - (1ll << k - 2);
			if (cha < 0)break;
			for (rg int i = 2; i < k; ++i)
				r[i] = fast_IO::min(m - 1, cha / (1ll << k - i - 1)), cha -= r[i] * (1ll << k - i - 1);
			if (cha < m) {
				can = true, len = k, r[len] = cha;
				break;
			}
		}
		if (!can)puts("-1");
		else {
			rg ll sum = a;
			for (rg int i = 2; i <= len; ++i)++r[i], r[i] += sum, sum += r[i];
			fast_IO::write(len);
			for (rg int i = 1; i <= len; ++i)putchar(' '), fast_IO::write(r[i]);
			putchar('\n');
		}
	}
	return 0;
}
```


---

