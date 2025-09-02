# Creating Keys for StORages Has Become My Main Skill

## 题目描述

Akito 仍然无处可住，而小房间的价格却居高不下。为此，Akito 决定在银行找一份为存储设备创建密钥的工作。

在这个魔法世界中，一切都与众不同。例如，代码为 $(n, x)$ 的存储设备的密钥是一个满足以下条件的长度为 $n$ 的数组 $a$：

- $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$，其中 $a \mid b$ 表示数 $a$ 和 $b$ 的[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。
- $\text{MEX}(\{ a_1, a_2, a_3, \ldots, a_n \})$ $^{\text{∗}}$ 在所有满足条件的数组中达到最大值。

Akito 勤奋地工作了几个小时，但突然头痛发作。请代替他工作一小时：对于给定的 $n$ 和 $x$，创建任意一个满足代码为 $(n, x)$ 的存储设备的密钥。

$^{\text{∗}}$ $\text{MEX}(S)$ 是满足以下条件的最小非负整数 $z$：$z$ 不在集合 $S$ 中，且所有满足 $0 \le y < z$ 的 $y$ 都在集合 $S$ 中。

## 样例 #1

### 输入

```
9
1 69
7 7
5 7
7 3
8 7
3 52
9 11
6 15
2 3```

### 输出

```
69
6 0 3 4 1 2 5
4 1 3 0 2
0 1 2 3 2 1 0
7 0 6 1 5 2 4 3
0 52 0
0 1 8 3 0 9 11 2 10
4 0 3 8 1 2
0 3```

# 题解

## 作者：tzzl3035 (赞：4)

### CF2072C

#### 大致思路

从 $0$ 开始向后枚举，若或上这个数不会使最终的 $x$ 改变，则加上这个数，否则不枚举了。若枚举完后发现按位或的和不够 $x$，把最后一位改为 $x$ 即可。

#### 代码详解

```cpp
#include <bits/stdc++.h>

int main() {
  int t; std::cin >> t;
  for(; t; --t) {
// 准备
    int n, x; std::cin >> n >> x;
    int sum = 0; std::vector<int> ans(n, 0);
// 枚举
    for(int i = 0; i < n; ++i) {
      if((i | x) == x) { // 若不会使 x 改变
        ans[i] = i; sum |= i; // 你过关（用这个数）
      }
      else break; // 否则结束枚举
    }
    if(sum != x) ans[n-1] = x; // 不够 x，加个 x
// 输出
    for(auto num: ans) 
      std::cout << num << ' ';
    std::cout << '\n';
  }
}
```

#### [RESULT](https://codeforces.com/contest/2072/submission/309227495)

---

## 作者：Clare613 (赞：1)

## 题目大意
就是找到一个数组 $a$，使得 $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$。要求 $\text{MEX}(a)$ 最大。
## 思路
我们要先预留一个空位，用来使 $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$ 符合。\
接这样我们就从 $0$ 开始往大走。如果当前这个数的二进制数与 $x$ 的二进制数不匹配，即当前数有的，但 $x$ 没有的，那我们就终止。如果已经找到了 $n-1$ 个数了，我们同样也要终止。\
同样，最后一个数他可以是 $x$，但是如果第 $n$ 个数的二进制数有和 $x$ 的二进制数最大的一位数一样，那么就可以直接选这个数，因为前面的数**一定**把 $x$ 的前几位包含了。\
以上就是我们的贪心策略，下面是代码。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool check(int x,int y){
	while(x&&y){
		if(x%2==0&&y%2==1){
			return 0;
		}
		x/=2;
		y/=2;
	}
	return 1;
}
bool qwq(int x,int y){
	while(x&&y){
		if(x==1&&y==1) return 1;
		x/=2;
		y/=2;
	}
	return 0;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,x,i=1;
		cin>>n>>x;
		if(n==1){
			cout<<x<<"\n";
			continue;
		}
		cout<<0<<" ";
		for(i=1;i<=n-2&&i<=x;i++){
			if(check(x,i)){
				cout<<i<<" ";
			}
			else{
				break;
			}
		}
		for(int j=1;j<=n-2-i+1;j++) cout<<0<<" ";
		if(qwq(x,i)==0) cout<<x<<"\n";
		else cout<<i<<"\n";
	}
    return 0;
}
```

---

## 作者：_O_w_O_ (赞：0)

很显然，题目等价于我们需要找到一个最大的 $k$ 满足 $0|1|2|\cdots |k$ 的二进制位为 $x$ 的二进制位的子集，那么直接枚举即可。

为什么是最大的，因为这样 $\operatorname{mex}$ 才能最大。

code：<https://codeforces.com/contest/2072/submission/309456219>

---

## 作者：Pyrf_uqcat (赞：0)

构造题。构造一个数列 $a$ 满足要求：需要 $\operatorname{MEX}(a_1,a_2\dots a_n)$ 最大且所有元素按位或后结果为 $x$。

先想到当所有值为 $x$ 时符合条件，那么想让 $\operatorname{MEX}$ 更大，考虑到按位或是某一位上两数有一个为 $1$ 则这个位置就是 $1$，那么只需从 $0$ 开始输出到最大且不影响按位或答案的值即可，有多的输出就采取开始的思路全部放 $x$。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long 

using namespace std;

int n,x;

signed main()
{
    int t;cin>>t;
    while(t--)
	{
        cin>>n>>x;
        int t=0,mx;
        for(mx=0;mx<n;mx++)
		{
            if((mx&x)==mx) t|=mx;
			else break;
        }
        if(mx==n&&t!=x) mx--;
        for(int i=0;i<mx;i++) cout<<i<<' ';
        for(int i=mx+1;i<=n;i++) cout<<x<<' ';
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：songlll (赞：0)

# 形式化题面
给你两个整数 $n$ 和 $x$，你需要构造一个长度为 $n$ 的数列，使整个数列或起来的结果为 $x$，且包含尽量多的从零开始的连续的数。
# 思路
本题并没有用什么高超的算法。

我们知道，一个数或上另一个数，每一个二进制位一定不会减少。所以，从零考虑，依次或上连续的自然数，当结果有一位大于 $n$ 时，就没有办法或上任何个数的数结果为 $n$ 了。

如果将 0 到 $n-1$ 的数或起来，仍然到不了 $x$，则 MEX 值一定到不了 $n$ ,而如果我们的方案 MEX 值为 $n-1$，则是最优解。

于是可以贪心……
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,cnt=0;
		cin>>n>>x;
		for(int i=0;i<n;i++){
			cnt|=i;
			if((cnt|x)>x){//当或上这个数cnt有任意一位大于x
				for(;i<n;i++){//不要这个数了，最后输出x凑数
					cout<<x<<" ";
				}
				break;
			}
			if(i==n-1){
				if(cnt<x){//把0到n-1全或上也不够x
					cout<<x;//直接或上x不就够了吗
					break;
				}
			}
			cout<<i<<" ";
		} 
		cout<<'\n';
	}
  return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [CF2072C Creating Keys for StORages Has Become My Main Skill](https://www.luogu.com.cn/problem/CF2072C) | Codeforces [C. Creating Keys for StORages Has Become My Main Skill](https://codeforces.com/contest/2072/problem/C)

更佳的阅读体验：[CF2072C 题解](https://blog.ryanli.top/index.php/archives/253/)

---

**简要题意**：构造一个长度为 $n$ 的序列 $a$，使得 $\operatorname{or} \limits_{i = 1}^{n} a_i  = x$ 且 $\text{mex}(\{a_1, a_2, a_3, \cdots a_n\})$ 最大，其中 $a \text{ or } b$ 表示 $a$ 与 $b$ 的按位或。

如果不考虑其他条件，要使 $\text{mex}$ 最大，有一个最直接的想法是，从 $0$ 到 $n - 1$ 按顺序填一遍。但此时发现，可能出现 $\operatorname{or} \limits_{i = 1}^{n} a_i \neq x$ 的情况。

可以证明，对于 $0 \sim n - 1$ 的每一个数，贪心地将满足 $x \text{ or } i = x$ 的所有数 $i$ 填入序列中，这样填出来的序列一定是 $\text{mex}$ 最大的。

根据按位或的性质，此时一定有 $x \text{ or }(\operatorname{or} \limits_{i = 1}^{n} a_i) = x$，要想让 $\operatorname{or} \limits_{i = 1}^{n} a_i  = x$ 成立，我们只需要在后面继续填至少一个 $x$。

但如果此时序列已经填够了 $n$ 个数，却不满足 $\operatorname{or} \limits_{i = 1}^{n} a_i  = x$ 呢？只需要将最后一个数删掉，再填上一个 $x$ 即可。

```cpp
#include <iostream>
using namespace std;

int t, n, x, sum;
basic_string<int> ans;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        sum = 0;
        ans.clear();
        cin >> n >> x;
        for (int i = 0; i < n; ++i) if ((sum | i | x) == x) ans += i, sum |= i;
        if (ans.size() == n && sum != x) ans.pop_back();
        while (ans.size() < n) ans += x;
        for (int i = 0; i < n; ++i) cout << ans[i] << " \n"[i == n - 1];
    } return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 题意简述

其实原题意已经非常的简洁了，没有必要再进行简化，但还是简单写一下：

**本题多测**

你需要构造出一个长度为 $n$ 的序列，满足：

- $a_1 | a_2 | a_3 | \ldots | a_n = x$，其中 $a | b$ 表示按位与

-  $ \text{mex}(a_1, a_2, a_3, \ldots, a_n) $ 最大，其中 $ \text{mex}(a_1, a_2, a_3, \ldots, a_n) $ 表示 $a_1 \sim a_n$ 中最小的未出现过的正整数

最后输出你构造的序列。

## 开始解题！

其实是很简单的，要使 $\text{mex}$ 最大，也就是要尽可能出现较长的连续正整数，所以我们取 $[0, n - 1]$ 之间的整数，按顺序进行遍历，遇到第一个 $y \in [0, n - 1]$ 使得 $x \ | y \not= x$，也就是说再进行按位与是不可能会与 $x$ 相等的，所以直接退出遍历。

所以我们还需要记录一个前缀按位与变量 $res$，在刚刚的遍历结束之后，判断是否有 $res \not= x$，若出现该种情况，就直接把 $x$ 填在最后面，注意判断当前构造出来的序列长度是否为 $n$，若是，就覆盖最后一项，反之就把 $x$ 填在下一项中。

如果本身就有 $res = x$ 那么就不用做任何的操作。

最后是代码，如果在文章中有看不懂的可以看代码。缺省源比较长，重要代码在主函数。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

const ll maxn = 3;

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

namespace math {
    vector<ll> fac, inv;
    
    void init(ll sz) {
        fac.resize(sz + 5), inv.resize(sz + 5);
        
        fac[0] = fac[1] = inv[0] = inv[1] = 1;
        
        for (ll i = 2; i <= sz; i++) {
            fac[i] = fac[i - 1] % mod * i % mod;
            
            inv[i] = (mod - inv[mod % i] * (mod / i) % mod) % mod; 
        }
        
        for (ll i = 2; i <= sz; i++) {
            inv[i] *= inv[i - 1] % mod, inv[i] %= mod;
        }
    }
    
    ll A(ll n, ll m) {
        return fac[n] % mod * inv[n - m] % mod;
    }
    
    ll C(ll n, ll m) {
        return fac[n] % mod * inv[m] % mod * inv[n - m] % mod;
    }
}

ll qpow(ll a, ll b, ll m = 1) {
    if (b == 0) return 1 % m;
    
    ll ans = 1;
    
	while (b) {
        if (b & 1) ans = ans * a % m;
        
        a = a * a % m;
        
        b >>= 1;
    }
    
    return ans;
}

ll gcd(ll a, ll b) {
	return a == 0 || b == 0 ? max(a,b) : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a,b) * b;
}

ll lowbit(ll x) {
    return x & (-x);
}

ll popcount(ll x){
    ll res = 0;
    
    while (x) {
        x -= lowbit(x);
        
        res ++;
    }
    
    return res;
}

struct BIT {
	ll n = 0; std::vector<ll> c;
	
	BIT (ll sz) {
		n = sz, c.resize(sz + 5);
	};
	
	void add(ll x, ll y) {
		if (n == 0) {
			return ;
		} else {
			for (ll i = x; i <= n; i += lowbit(i)) {
				c[i] += y;
			}
		}
		
		return ;
	}
	
	ll sum(ll x) {
		ll res = 0;
		
		for (ll i = x; i; i -= lowbit(i)) {
			res += c[i];
		}
		
		return res;
	}
};

struct DSU { // 并查集
    ll n = 0; vector<ll> fa;
    
    DSU (ll sz) {
        n = sz, fa.resize(sz + 5);
    };
    
    void init() {
        if (n == 0) {
            return ;
        }
        
        for (ll i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    
    ll find(ll x) {
        return x == fa[x] ? x : find(fa[x]);
    }
    
    void merge(ll x, ll y) {
        x = find(x), y = find(y);
        
        if (x != y) {
            fa[x] = y;
        }
    }
};

// template<typename tp1,typename tp2,int N>
// struct Htb{
    // static constexpr int M=1e7+19;
    // int hd[M+3],to[N],ct;
    // tp1 ed[N];tp2 w[N];
    // static int hc(ul v){
        // v^=v<<13,v^=v>>7;
        // return (v^(v<<17))%M;
    // }
    // void ins(tp1 x,tp2 y){
        // int &p=hd[hc(x)];
        // ed[++ct]=x,to[ct]=p;
        // w[p=ct]=y;
    // }
    // int count(tp1 x){
        // for(int i=hd[hc(x)];i;i=to[i])
            // if(ed[i]==x)return 1;
        // return 0;
    // }
    // pair<tp2,bool>find(tp1 x){
        // for(int i=hd[hc(x)];i;i=to[i])
            // if(ed[i]==x)return mkp(w[i],true);
        // return mkp(0,false);
    // }
    // int operator[](tp1 x){
        // int &p=hd[hc(x)];
        // for(int i=p;i;i=to[i])
            // if(ed[i]==x)return i;
        // ed[++ct]=x,to[ct]=p;
        // return p=ct;
    // }
    // void clear(){while(ct)hd[hc(ed[ct--])]=0;}
// };

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    ll T = rd();
    
    while (T--) {
        n = rd(), x = rd(), res = 0; ll cnt = 0;
        
        for (i = 0; i < n; i++) {
            if ((x | i) == x) {
                a[++cnt] = i, res |= i;
            } else {
                break;
            }
        }
        
        if (res != x) {
            if (cnt == n) a[cnt] = x;
            
            else a[++cnt] = x;    
        }
        
        while (cnt <= n) a[++cnt] = 0;
        
        for (i = 1; i <= n; i++) wt(a[i]), putchar(' ');
        
        puts("");
        
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2072/submission/308026378)

---

## 作者：cwxcplh (赞：0)

前置：本篇文章将会讲述作者的辛酸史，易伤感的同学请离开。

**题目简化：** 求一个长度为 $n$ 的数组 $a$ 使得 $\operatorname{MEX}(\{a_1,a_2,a_3,\dots,a_n\})$ 最大且 $a_1\mid a_2\mid a_3\mid\dots\mid a_n=x$。（注：$\operatorname{MEX}(\{a_1,a_2,a_3,\dots,a_n\})$ 表示第一个没出现在这个数列中的非负整数）

~~众所周知，CF 的题很喜欢考这个 $\operatorname{MEX}$~~，所以这道题肯定是 CF 的。

回归正题：题目要我们求 $\operatorname{MEX}(\{a_1,a_2,a_3,\dots,a_n\})$ 的最大值时 $a$ 数组的情况，实际上就是让我们求在数列 $b$ 让 $x=b_1\mid b_2\mid\dots\mid b_m$ 的前提下，$m$ 的最大可以达到多少，这样想其实很简单，只需要从 $1$ 到 $x$ 枚举一遍然后看看每个数是否符合刚刚我们说的并把符合条件的数保存下来，最后看看最多能到多少。

这里提个特殊情况：如果 $x$ 是 $2$ 的倍数，那么 $\operatorname{MEX}$ 最多就是 $1$，所以只需要先输出个 $0$，然后一直输出它自己就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x;
signed main() {
	cin>>t;
	while(t--) {
		cin>>n>>x;
		if(!(x&1)) {
			cout<<x<<" ";
			for(int i=1; i<n; i++) {
				cout<<0<<" ";
			}
			cout<<endl;
		} else {
			vector<int>v;
			for(int i=0; i<=x; i++) {
				if((i&x)==i) {
					v.push_back(i);
				}
			}
			int t=0;
			if(n>v.size()) { //如果n比数量要大，就随便输
				for(auto i:v) {
					cout<<i<<" ";
				}
				n-=v.size();
				while(n--) { //花费完所有的机会
					cout<<x<<" ";
				}
				cout<<endl;
				continue;
			}
			for(int i=0; i<n-1; i++) {
				t|=v[i];
				cout<<v[i]<<" ";
			}
			if((t|v[n-1])==x) { //看看能不能承接上一个
				cout<<v[n-1];
			} else {
				cout<<x;
			}
			cout<<endl;
		}
	}
	return 0;
}
```

提交一看：

![](https://cdn.luogu.com.cn/upload/image_hosting/6opyrbda.png)

完美的 MLE 了……

经过我的仔细思考发现：有时候长度过长了，vector 可能存不下，于是我把第 17 行改成了这样：`for(int i=0;i<=x&&v.size()<=n;i++)`。

再次提交：

![](https://cdn.luogu.com.cn/upload/image_hosting/40eshgjz.png)

又完美的 TLE 了……

停了我同机房的人的指导，我把下面的两个循环改成了一个，但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/06i9ansh.png)

我还是 TLE 了……

最后，我才发现了一个地方：如果在枚举的过程中已经断开了，那 $\operatorname{MEX}$ 其实就已经定了，后面的已经不是那么重要了，所以只需要加一句话：

```cpp
if((i&x)!=i)
{
    break;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/aq1yi60a.png)

终于终于是 AC 了！

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x;
signed main() {
	cin>>t;
	while(t--) {
		cin>>n>>x;
		if(!(x&1)) {
			cout<<x<<" ";
			for(int i=1; i<n; i++) {
				cout<<0<<" ";
			}
			cout<<endl;
		} else {
			int cnt=0,t,tt=0;
			for(int i=0; i<=x&&cnt<n-1; i++) {
				if((i&x)!=i) {
					break;
				}
				if((i&x)==i) {
					cnt++;
					cout<<i<<" ";
					t=i;
					tt|=i;
				}
			}
			if(cnt==n-1) {
				if(((t+1)|tt)==x) {
					cout<<t+1;
				} else {
					cout<<x;
				}
			} else if(cnt<n) {
				for(int i=1; i<=n-cnt; i++) {
					cout<<x<<" ";
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：IGpig (赞：0)

## CF2072C
### Problem
一个长度为 $n$ 的数组 $a$，满足以下条件：
- $a_1 \mid a_2 \mid a_3\dots a_n=x$，其中$ a|b $是数字 $a$ 和 $b$ 的按位“或”。
- $\operatorname{MEX}({a_1,a_2,a_3\dots a_n})$ 在所有这样的数组中最大化。

$\operatorname{MEX}(S)$ 是最小的非负整数 $z$，使得 $z$ 不包含在集合 $S$ 中，并且所有 $0<y<z$ 都包含在 $S$ 中。 

### Solution
因为要让整个序列或的结果为 $x$，最好的是让整个序列都为 $x$。\
然后看第二个条件，我们可以发现要在不影响结果为 $x$ 的情况下让 $\operatorname{MEX}$ 最大。\
怎么才能不影响结果，因为按位或的性质是某一位上只要有 1，那么最后结果一定有 1，所以可以由此找到最大的 $\operatorname{MEX}$，并且不会有任何一位有影响结果的 1。
~~~cpp
for(mex=0;mex<=n-1;mex++){
    if((mex&x)!=mex) break;
}
~~~
然后就输出 $1\rightarrow {\operatorname{MEX}-1}$，多的就全部输出 $x$。

### Code
~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
LL n,x,t,mex;
int main(){
    cin>>t;
    while(t--){
        LL tmp=0;
        cin>>n>>x;
        for(mex=0;mex<=n-1;mex++){
            if((mex&x)!=mex) break;
            tmp|=mex;
        }
        if(mex==n&&tmp!=x) mex--;
        for(int i=0;i<mex;i++){
            cout<<i<<' ';
        }
        for(int i=mex+1;i<=n;i++) cout<<x<<' ';
        cout<<endl;
    }
    return 0;
}
~~~

---

## 作者：yhl110804 (赞：0)

观察数据范围 $N \leq 2 \times 10^5$ 所以我们可以枚举每一个数是否可以在答案中出现，当一个数 $a$ 的二进制与 $x$ 的并等于 $a$ 时一个数可以在答案中出现。

但是当 $a$ 等于 $n-1$ 时很特殊，必须确保将它加入答案后，答案集合中所有数或的结果等于 $x$ 才可以将它加入答案集合中，否则就要将 $b$ 加入答案集合中以确保答案集合中所有数或的结果等于 $x$。设 $c$ 为 $a_1$ 或到 $a_{n-1}$ 的结果，那么 $b=x-c$。

### Code:
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;char ch=getchar();
   while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
   while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
   return x*f;
}
void write(int x)
{
   if(x<0)putchar('-'),x=-x;
   if(x<10)putchar(x+'0');
   else write(x/10),putchar(x%10+'0');
}
const int N=1e3;
const int mod=1e9+7;
int T;
int n,x;
int sum[N];
int top;
int X;
//int a[N];
void point(int op){
	int kl=0;
//	cout<<op<<"\n";
	for(int i=0;i<op;i++)cout<<i<<" ",kl|=i;
	for(int i=op;i<n;i++)cout<<x-kl<<" ";
	cout<<"\n";
}
signed main(){
	T=read();
	while(T--){
		n=read(),x=read();
		top=0;
		X=x;
		while(X){
			sum[++top]=X&1;
			X>>=1;
		}
		bool fl=0;
		int ans=0;
		for(int i=0;i<n-1;i++){
			int w=i;
			if(w>x){
				fl=1;
				point(i);
				break;
			}
			if((i&x)!=i) {
				fl=1;
				point(i);
				break;
			}
			ans|=i;
		}
		if(!fl){
			if((ans|(n-1))==x)point(n);
			else point(n-1); 
		}
	}
    return 0;
}
/*
111
*/

```

---

## 作者：xuchuhan (赞：0)

赛时很快就有思路了，但是调了蛮久，还拿了一发罚时。

下面讲一下赛时做法。

首先要求 $\text{MEX}$ 值尽量大，那么我们需要找到最大的 $k$ 使得构造出的方案包含 $0\sim k$ 且合法。那么我们考虑如果只有 $x$，$k$ 能取多大。考虑将 $x$ 进行二进制分解，找到其从后往前数最大的连续的 $p$ 个 $1$，那么 $k$ 最大取到 $2^p-1$。若 $k$ 取到 $2^p$（选择 $2^p$ 这个数），因为 $2^p$ 的第 $p$ 位为 $1$，所以无论如何或起来的答案的第 $p$ 位都为 $1$，而 $x$ 的第 $p$ 位为 $0$，所以或起来不可能为 $x$。

那么，$2^p$ 一定不能选中，那么 $\text{MEX}$ 值最多就是 $2^p$。

同时考虑选 $0\sim 2^p-1$ 这个方案的合法性。发现 $0\sim 2^p-1$ 这个区间范围内的数最多也只有 $p$ 位，$p$ 位之后全为 $0$，不会与 $x$ 产生冲突；而 $x$ 前 $p$ 位全是 $1$，同样也不会与它们产生冲突。

现在考虑加入 $n$ 个数的限制。

- 若 $n>2^p$，那么 $0\sim 2^p-1$ 这 $2^p$ 个数可以被全部选中，选完这 $2^p$ 个数之后，存在至少一个空位，将这些空位全部填充 $x$ 即可保证或出来的答案等于 $x$。
- 若 $n<2^p$，那么 $0\sim 2^p-1$ 不可能被取满，最多取到 $0\sim n-1$。但是还要考虑取 $0\sim n-1$，总的或值能不能为 $x$ 的情况。如果 $0\sim n-1$ 的或值小于 $x$，那么只能取 $0\sim n-2$，最后一个空位填充 $x$；否则可以取 $0\sim n-1$。最后考虑如何判断 $0\sim n-1$ 的或值是否小于 $x$：如果 $n-1$ 二进制下的位数与 $x$ 相同，那么或值等于 $x$；否则小于 $x$。

综合一下以上思路，代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,x;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>x;
		int cnt=0,tmp=x;
		while(tmp&1)cnt++,tmp>>=1;//找后面连续的1 
		int y=(1<<cnt); 
		/*代码思路见上文*/
		if(n<=y){
			for(int i=1;i<n;i++)cout<<i-1<<" ";
			int t1=log2(n-1),t2=log2(x);//log2(x)可以求x在二进制下的位数 
			if(t1==t2)cout<<n-1<<" ";
			else cout<<x<<" ";
		}
		else{
			for(int i=0;i<y;i++)cout<<i<<" ";
			for(int i=y+1;i<=n;i++)cout<<x<<" ";
		}
		cout<<"\n";
	}
	return 0; 
}
```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1FHP3eAEWj?t=312)

[代码链接](https://codeforces.com/contest/2072/submission/307828547)

---

