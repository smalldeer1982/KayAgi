# Simple Repetition

## 题目描述

Pasha 喜欢质数 $ ^{\text{∗}} $ ！有一次他想找一个新的质数生成的方法，于是他在网上搜到了这样的数字生成方法：

- 选择一个没有前导零的正整数 $x$ 和一个正整数 $k$，把 $x$ 连写 $k$ 次得到新的正整数 $y$。

例如当 $x=52,\ k=3$ 时，$y=525252$，$x=6,\ k=7$ 时，$y=6666666$。

Pasha 想让得到的数是质数，但是他不知道怎么判断这种方法生成的是不是质数。请你写一个程序来判断 $y$ 是否是质数。

 $ ^{\text{∗}} $ 质数，也叫素数，指的是那些含有恰好 $2$ 个不同正约数的正整数。例如 $13$ 是一个质数，因为这个数只有 $2$ 个不同正约数 $1$ 和 $13$。$1$ 则不是质数，因为 $1$ 只有 $1$ 个不同正约数，那就是 $1$。

## 样例 #1

### 输入

```
4
52 3
6 7
7 1
1 7```

### 输出

```
NO
NO
YES
NO```

# 题解

## 作者：GUO120822 (赞：1)

首先考虑 $k=1$ 的情况，得到的数就是 $x$。所以判断 $x$ 是否是质数即可。

然后就是 $k\neq 1$ 的情况。对于这种情况，设 $x$ 位数为 $num$，手玩一下发现得到的数是 $(x \times 10^{num}+x)\times 10^{num}\dots$。

所以展开可以知道就是 $x \times (10^{(k-1)num}+10^{(k-2)num}+\dots)$，第二个数必不等于 $1$，所以当 $x\neq 1$ 时，不合法；当 $x=1$ 时，$11$ 合法。特判即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct FSI{
	template<typename T>
	FSI& operator >> (T &res){
		res=0;T f=1;char ch=getchar();
		while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
		while (isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
		res*=f;
		return *this;
	}
}scan;
int T,x,k,i;
bool isprime(int x)
{
	int i;
	if (x==1) return false;
	for (i=2;i<=sqrt(x);i++)
	{
		if (x%i==0) return false;
	}
	return true;
}
void work()
{
	scan>>x>>k;
	if (x==1&&k==2){printf("YES\n");return;}
	if (k!=1) printf("NO\n");
	else
	{
		if (isprime(x)) printf("YES\n");
		else printf("NO\n");
	}
}
int main()
{
	scan>>T;
	while (T--) work();
	return 0;
}
```

---

## 作者：_weishiqi66_ (赞：1)

给定 $x$ 要求判断将该数复制 $k$ 次后，其是否为素数。

记 $n$ 为 $x$ 的位数，则将 $x$ 复制一次后可表示为 $x \times 10^{n} +x$ 将其整理可得 $x \times (10^{n} +1)$.易得,只有当 $x$ 和 $10^{n} +1$ 中同时存在一个 $1$ 和一个素数时，该数为素数。复制 $k$ 次的判断方法同上。



```
#include <bits/stdc++.h>
#define int long long 
using namespace std;

int t,x,k;
signed main() {
	cin>>t;
	while(t--) {
		cin>>x>>k;
		if(x==1) {
			if(k==2) cout<<"YES\n";
 //打表可得 在题目限定的数据范围内，位数上都为1的数里，只有11为素数。
			else cout<<"NO\n";
		}
		else {
			if(k==1) {
				bool f=1;
				for(int i=2;i*i<=x&&f==1;i++) if(x%i==0) f=0;
				if(f==1) cout<<"YES\n";
				else cout<<"NO\n";
			}
			else cout<<"NO\n";
			
			
		}
	}
	return 0;
}
```

---

## 作者：IGpig (赞：0)

## CF2093C

### Solution

因为是把 $x$ 复制 $k$ 次，所以新的数一定有一个因数是 $x$，那么当 $k=1$ 时，只需要判断 $x$ 是不是质数就可以了。

然后就想想什么时候 $k$ 是质数，因为 $k$ 一定是一个由若干个零和一个一组成的循环节组成的数，枚举一下发现，只有 $11$ 是质数，其他都不是。

所以可以推出以下结论：

- 当 $k=1$，答案为 $x$ 是否为质数。
- 当 $k=2$ 且 $x=1$，答案为正确。
- 否则为错误。

### Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
LL n,k,t,x;
bool check(LL q){
    for(int i=2;i*i<=q;i++){
        if(!(q%i)) return 0;
    }
    return 1;
}
int main(){
    cin>>t;
    while(t--){
        cin>>x>>k;
        if(x==1){
            if(k==2) cout<<"YES\n";
            else cout<<"NO\n";
            continue;
        }
        if(x>1&&k>1) cout<<"NO\n";
        else if(k==1){
            if(check(x))cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}
~~~

---

## 作者：cwxcplh (赞：0)

~~我还从没有见过如此简单的关于质数的题……~~

**题目大意：** 给你一个 $n$ 和一个 $k$，要求你把 $n$ 重复 $k$ 次变成一个新的数，求这个数是不是质数。

首先最好想的情况：$k=1$ 时，这时候直接判断 $n$ 是不是质数就对了，让我们来看其他情况。

如果 $n=1$ 且 $k\not=1$，那么我们可以得到的是除了 $k=2$ 的情况，其他情况下都是合数，具体证明大家可以自己去搜，过程过长，不在这里赘述了。

如果 $n\not=1$ 且 $k\not=1$，那么这个数就必定是质数，原因：任何一个 $\overline{\underbrace{a_1a_2a_3\dots a_1a_2a_3\dots}_{k\text{个循环}}}$ 的数必定能写成这样的形式：$\overline{a_1a_2a_3\dots}\times\underbrace{\underbrace{100\dots}_{n\text{个数}}\underbrace{100\dots}_{n\text{个数}}\dots}_{k-1\text{个循环}}1$，所以它必然是一个合数。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
bool pd(int x)
{
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)
        {
            return false;
        }
    }
    return true;
}
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        if(n>=1&&k>1)
        {
            if(n==1&&k==2)
            {
                cout<<"YES"<<endl;
            }
            else
            {
                cout<<"NO"<<endl;
            }
        }
        else if(n>1&&k==1)
        {
            cout<<(pd(n)?"YES":"NO")<<endl;
        }
        else if(n==1&&k==1)
        {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

这是一道关于质数的问题。问题大意是输入两个正整数 $x$ 和 $k$，求将 $x$ 复制 $k$ 次以后，得到的数是否是质数。

先看范围：$x\le10^9,k\le7$，所以直接复制后判断质数最大会达到 $10^{69}$，不可取。我们可以这么想：如果你将一个数复制多次，那么得到的数肯定会有一个类似 $100\cdots010\cdots001$ 的约数。举个例子：你将 $114$ 复制 $5$ 次， 得到的数就相当于 $114\times1001001001001$。类似的你会发现一旦复制超过 $2$ 次，那么它最后肯定不是质数。注意：$11$ 是一个个例。

综上所述，当复制的次数超过 $2$ 次时，若结果为 $11$ 则是质数，否则就不是；若复制次数为 $1$ 次，即不复制时，直接判断 $x$ 是否为质数即可。判断质数的方法就是从 $2$ 开始一直到 $\lfloor\sqrt{x}\rfloor$，如果发现了能整除 $x$ 的数，那么就不是质数；否则就是质数。

明白了上面的一切就可以出代码了：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b,c,t;
bool primeq(int x){
    if(x==1) return false;
	for(int i=2;i*i<=x;i++){
		if(x%i==0) return false;
	}
	return true;
}
int main()
{
   cin>>t;
	while(t--){
		cin>>a>>b;
		if(b==1){
		    if(primeq(a)) cout<<"yes\n";
		    else cout<<"no\n";
		}
		else{
		    if(a==1&&b==2) cout<<"yes\n";
		    else cout<<"no\n";
		}
	}
   return 0;
}
```

---

## 作者：Ag2WO4 (赞：0)

诈骗题。

设 $x$ 长度为 $l$，若 $k>1$ 则必然有因子 $\sum_{n=0}^{k-1} 10^{nl}$，故直接判断是否 $k=1$ 且 $x$ 为质数即可。注意特判 $x=1$ 的情况。

上代码，但~~筛是用小冰 AI 写的~~。
```python
def sieve_of_eratosthenes(n):
    primes = [True] * (n + 1) # 初始化一个布尔列表，表示每个数是否为质数
    primes[0] = primes[1] = False # 0和1不是质数
 
    p = 2
    while p * p <= n:
        if primes[p]:
            for i in range(p * p, n + 1, p):
                primes[i] = False # 将p的倍数标记为非质数
        p += 1
     
    return [i for i, is_prime in enumerate(primes) if is_prime]
 
n = 100000
prime_numbers = sieve_of_eratosthenes(n)
for i in range(int(input())):
    x,k=map(int,input().split())
    if x==1:print('NO'if k-2 else'YES');continue
    p=(k==1)
    for i in prime_numbers:
        if i**2>x or p==0:break
        p=x%i
    print('YES'if p else'NO')
```

---

## 作者：Phigros_11calors (赞：0)

场上切了 A-D，E 题没想出来，还是太菜了。

### 思路

这题要求我们判断一个整数连写 $k$ 次是不是质数。

首先 $x=1$ 要特判，$x=1$ 的时候只有 $k=2$ 得到的数 $11$ 是质数，其他情况都不是质数。

然后是 $k=1$。这种情况得到的数都是原数，判断原数是否是质数即可。

考虑 $x,k \ne 1$。我们设 $b$ 为 $x$ 的位数，容易得到把 $x$ 连写 $k$ 次的结果等于 $x \times ({10}^{(k-1)b}+{10}^{(k-2)b} + \cdots + {10}^b+1)$。比如当 $x=39,\ k=3$ 时，得到的数是 $393939=39 \times 10101$。于是得到的数能分解成两个数 $x$ 和 ${10}^{(k-1)b}+{10}^{(k-2)b} + \cdots + {10}^b+1$ 的积，这两个数都不等于 $1$（因为 $x,k \ne 1$），因此得到的数是合数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k,flag=1;
        cin>>n>>k;
        if(n==1){
            if(k==2)cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
            continue;
        }
        if(k>1)flag=0;
        for(int i=2;i*i<=n;i++){
            if(n%i==0)flag=0;
        }
        puts(flag?"Yes":"No");
    }
}
```

[AC 记录](https://codeforces.com/contest/2093/submission/314522828)

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

分讨一下吧。

首先，当 $k = 1$ 的时候，我们直接判断 $n$ 是否为质数即可。

当 $k > 1$ 时，若 $n = 1$，只有 $11$ 是质数（即 $k = 2$ 的时候），可以直接特判掉。而若 $n > 1$，那么记 $x$ 有 $a$ 位，则：

$$
y = x \times 10 ^ {a(k - 1)} + 10 ^ {a(k - 2)} + \dots + x \times 10 ^ {0}
$$

则 $y$ 含有 $x$ 这个因子，故此时一定为 `NO`。

我们对这几类情况简单分讨即可，代码：

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

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

bool ck(ll x) {
    if (x <= 1) return false;
    
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    ll T = rd();
    
    while (T--) {
        n = rd(), k = rd();
        
        if (n > 1 && k > 1) {
            puts("NO");
        } else if (k == 1) {
            puts(ck(n) ? "YES" : "NO");
        } else {
            puts((k == 2) ? "YES" : "NO");
        }
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2093/submission/314836358)

---

