# 【MX-X9-T2】『GROI-R3』XOR

## 题目描述

给出四个非负整数 $l, r, k, x$。你需要找到任意一个整数 $n$ 满足 $l \leq n \leq r$ 且 $\bigoplus\limits_{i=k}^n i = x$。其中，$\bigoplus\limits_{i=k}^n i$ 表示 $k \sim n$ 中所有整数的二进制按位异或和。

如有多解，求出任何一个均可。如果无解，请指出。

## 说明/提示

**【样例解释】**

对于第一组数据，取 $n = 6$，则 $1 \oplus 2 \oplus \cdots \oplus 6 = 7$，符合题意。可以证明，这是在 $[1, 10]$ 范围内唯一合法的解。

对于第二组数据，容易验证 $n = 19$ 是一组合法的解。此外，在 $[16, 30]$ 区间内，$n = 23$ 和 $n = 27$ 也合法，所以输出它们也正确。

**【数据范围】**

| 测试点编号 | $T \leq$ | $r \leq$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1\sim 4$ | $5000$ | $5000$ |  |
| $5\sim 8$ | $10^5$ | $10^9$ | AB |
| $9\sim 14$ | $10^5$ | $10^9$ | A |
| $15\sim 20$ | $10^5$ | $10^9$ |  |

- 特殊性质 A：保证 $k$ 为偶数。
- 特殊性质 B：保证 $x \leq 1$。

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10^5$，$1 \leq k \leq l \leq r \leq 10^9$，$0 \leq x \leq 2\times 10^9$。

## 样例 #1

### 输入

```
6
1 10 1 7
16 30 7 7
432327 42682357 114514 1
45445 473274 4741 280230
713243 34783411 114514 1919810
432754349 970503499 231891327 987305496
```

### 输出

```
6
19
432327
-1
1919810
923498342
```

# 题解

## 作者：XCDRF_ (赞：8)

# P11798【MX-X9-T2】『GROI-R3』XOR

[原题传送门](https://www.luogu.com.cn/problem/P11798)

[更好的阅读体验](https://www.luogu.com.cn/article/79svjn7h)

## 解题思路

题目要求求区间异或和，先转化成前缀异或和。

但是本题的数据范围有点大，如果每个都算出来不仅会 TLE 还会 MLE。

此时，我们打表发现，从 $0$ 到 $n$ 的异或和是有规律的。

令 $F(n)=0\oplus1\oplus\cdots\oplus n$，则有：

$$
F(n)=\begin{cases} n,&n\equiv 0\pmod4,\\ 1,&n\equiv 1\pmod4,\\ n+1,&n\equiv 2\pmod4,\\ 0,&n\equiv 3\pmod4.
\end{cases}
$$

这样一来，我们就能很方便的算出前缀异或和。剩下的事就简单了。

题目要求 $F(n)\oplus F(k-1)=x$，可转化为 $F(n)=x\oplus F(k-1)$。令 $t=x\oplus F(k-1)$，也就是说我们要找到一个 $n\in[l,r]$，使得 $F(n)=t$。

下面我们分类讨论：

- 当 $n\equiv 0\pmod4$ 时：$F(n)=n \Rightarrow n=T(T\equiv 0\pmod4)$。
- 当 $n\equiv 1\pmod4$ 时：$F(n)=1 \Rightarrow T=1$。
- 当 $n\equiv 2\pmod4$ 时：$F(n)=n+1 \Rightarrow n=T-1(T\equiv 3\pmod4)$。
- 当 $n\equiv 3\pmod4$ 时：$F(n)=0 \Rightarrow T=0$。

因此：

1. 如果 $T=1$，则只要在区间内存在 $n\equiv1\pmod4$ 的数即可。我们可以选区间内最小的 $n\equiv1\pmod4$。
2. 如果 $T=0$，则必须选 $n\equiv3\pmod4$，选区间内最小的 $n\equiv3\pmod4$。
3. 如果 $T\not\in\{0,1\}$：
   - 若 $T\equiv0\pmod4$，则必须有 $n=T$，检查 $T\in[l,r]$；
   - 若 $T\equiv3\pmod4$，则必须有 $n=T-1$，检查 $T-1\in[l,r]$；
   - 其他情况无解。

## 参考代码

```cpp
#include<iostream>
using namespace std;
int T,l,r,k,x;
int get(int x){
	if(x%4==0) return x;
	if(x%4==1) return 1;
	if(x%4==2) return x+1;
	if(x%4==3) return 0;
}
void solve(){
	cin>>l>>r>>k>>x;
	int a=get(k-1);
	int t=a^x;
	if(t==1){
		for(int i=l;i<=r;i++)
			if(i%4==1){
				cout<<i<<'\n';
				return;
			} 
		cout<<-1<<'\n';
		return;
	}
	if(t==0){
		for(int i=l;i<=r;i++)
			if(i%4==3){
				cout<<i<<'\n';
				return;
			} 
		cout<<-1<<'\n';
		return;
	}
	if(t%4==0&&t>=l&&t<=r){
		cout<<t<<'\n';
		return;
	}
	if(t%4==3&&t-1>=l&&t-1<=r){
		cout<<t-1<<'\n';
		return;
	}
	cout<<"-1\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>T;
    while(T--) solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/204410201)

---

## 作者：modfish_ (赞：3)

## 思路
容易发现，记 $f(n)=\bigoplus_{i=0}^ni$，有：

$$f(n)=\begin{cases}n,&n\bmod 4=0\\1,&n\bmod 4=1\\n+1,&n\bmod 4=2\\0,&n\bmod 4=3\end{cases}$$

用归纳法也容易证明。

于是不妨记 $x'=x\oplus f(k-1)$，问题变成求 $f(n)=x'$。简单分讨即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    scanf("%d", &T);
    while(T --){
        int l, r, k, x;
        scanf("%d %d %d %d", &l, &r, &k, &x);
        k --;
        if(k % 4 == 1) k = 1;
        else if(k % 4 == 2) k ++;
        else if(k % 4 == 3) k = 0;
        x ^= k;
        if(x % 4 == 0 && l <= x && x <= r) printf("%d\n", x);
        else if((x - 1) % 4 == 2 && l <= x - 1 && x - 1 <= r) printf("%d\n", x - 1);
        else if(x == 1){
            int a = l + 1 - (l % 4);
            if(a < l) a += 4;
            if(a <= r) printf("%d\n", a);
            else printf("-1\n");
        }else if(x == 0){
            int a = l + 3 - (l % 4);
            if(a <= r) printf("%d\n", a);
            else printf("-1\n");
        }else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：dg114514 (赞：2)

引理：$\bigoplus\limits_{i=1}^n i=\begin{cases}
n & n \equiv 0 \pmod 4 \\
1 & n \equiv 1 \pmod 4 \\
n+1 & n \equiv 2 \pmod 4\\
0 & n \equiv 3 \pmod 4\end{cases}$。证明：~~暴力验证发现 $10^9$ 内都没问题。~~

题目说满足 $\bigoplus\limits_{i=k}^n i = x$ 的条件，可以往等式两端异或上 $\bigoplus\limits_{i=1}^{k-1} i$，也就是 $\bigoplus\limits_{i=1}^n i = x \oplus \bigoplus\limits_{i=1}^{k-1} i$，即令 $t=x \oplus \bigoplus\limits_{i=1}^{k-1} i$，找到 $n\in[l,r]$ 使 $\bigoplus\limits_{i=1}^{n} i=t$。然后根据上述前缀异或和性质来分讨，即：

- 当 $t=1$ 时，找到 $[l,r]$ 区间中随便一个数 $u$ 使 $u\equiv 1\pmod 4$，如果找不到 $u$，显然无解输出 $-1$。

- 当 $t=0$ 时，找到 $[l,r]$ 区间中随便一个数 $u$ 使 $u\equiv 3\pmod 4$，如果找不到 $u$，显然无解输出 $-1$。

- 其他情况：由于~~我懒~~方便，直接枚举 `[t-2,t+2]` 区间看有没有数 $u$ 既在 $[l,r]$ 区间又满足 $\bigoplus\limits_{i=1}^{u} i=t$ 即可。找不到输出 $-1$。

分讨完，这题就被剖析完了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int sum(int n){
	if(n&3==0) return n;
	if((n&3)==1) return 1;
	if((n&3)==2) return n+1;
	return 0;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T,l,r,k,x,t,f;
	cin>>T;
	while(T--){f=1;
		cin>>l>>r>>k>>x;
		x^=sum(k-1);
		if(x==0){
			t=((l>>2)<<2)+3;
			if(t<l) t+=4;
			if(t<=r){
				cout<<t<<"\n";
				continue;
			} 
		}
		if(x==1){
			t=((l>>2)<<2)+1;
			if(t<l) t+=4;
			if(t<=r){
				cout<<t<<"\n";
				continue;
			} 
		}
		for(int i=x-2;i<=x+2;i++)
			if(sum(i)==x&&i>=l&&i<=r){
				cout<<i<<"\n";
				f=0;
				break;
			}
		if(f)cout<<"-1\n";
	}
} 
```

---

## 作者：lcfollower (赞：2)

~~笑话：我以前给别人出模拟赛出了个求 $[l,r]$ 所有整数的异或和。（~~

在做这题之前，你可以先试试[这个](https://www.luogu.com.cn/problem/P3908)。

---

首先容易想到异或**抵消**的性质，把原式 $\bigoplus\limits_{i=k}^n i = x$ 改为 $\left(\bigoplus\limits_{i = 1}^{k - 1} \oplus \bigoplus\limits_{i = 1}^n\right) = x$。

然后~~打表~~发现 $\bigoplus\limits_{i = 1}^y$（$y$ 为正整数）有一定规律，具体可见我上面传送的题目的题解或者[这里](https://www.luogu.com.cn/paste/iv2d79zy)，规律也写里面了。

然后可以直接求出 $\bigoplus\limits_{i = 1}^{k - 1}$，根据异或拥有**交换律**得出 $\bigoplus\limits_{i=1}^n = \left( x \oplus \bigoplus\limits_{i = 1}^{k - 1}\right) = need$。

最后分类讨论即可。

- $need = 0$，直接找一个符合范围的在模 $4$ 意义下为 $3$ 的即可。
- $need = 1$，直接找一个符合范围的在模 $4$ 意义下为 $1$ 的即可。
- $need \ne 0 ,1$，可以直接计算出两种方案中**每种方案唯一的 $n$**，判断是否在模 $4$ 意义下为相应规律所对应的余数即可：
 
- 都不行无解，输出 $-1$。

具体可以见代码：

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 100000000000000

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 1e6 + 10;

inline int Xor (int x){
  if (!(x % 4)) return x;
  if (x % 4 == 1) return 1;
  if (x % 4 == 2) return x + 1;
  return 0;
} inline void solve (){
  int l = read () ,r = read () ,k = read () ,x = read ();
//k <= l <= n <= r
  int pre = Xor (1 ,k - 1) ;

  int need = (x ^ pre);

    //k ^ ... ^ n = (1 ^ ... ^ (k - 1) ) ^ (1 ^ ... ^ n);
    
  //1 ~ n 的异或和为 need。
//cout << "need : " << ' ' << need << endl;

  if (!need){
    for (int i = l ; i <= min (l + 3 ,r) ; i ++) if (i % 4 == 3){writeln (i) ; return ;}
  } if (need == 1){
    for (int i = l ; i <= min (l + 3 ,r) ; i ++) if (i % 4 == 1) {writeln (i) ; return ;}
  }

  if (l <= need && need <= r && !(need % 4)) writeln (need) ;//此时 need 由 1 ^ 2 ^ ... ^ need 得到。
  else if (l < need && need <= r + 1 && (need - 1) % 4 == 2) writeln (need - 1) ;//此时 need 由 1 ^ 2 ^ ... ^ (need - 1) 得到。
  else puts("-1");
    
} signed main (){

  int T = read ();
  while (T --) solve ();
    
  return 0 ;
}
```

---

## 作者：幸存者 (赞：2)

uod on 4.8：修正了一处错误。

闲话：赛时我的开题顺序是 2143，所用时间约为 2.41h、0.51h、0.48h、0.25h，单调递减。

---

为啥大家都会打表啊，来个不用打表的做法。

首先，注意到当 $k\ge2$ 时，$\bigoplus\limits_{i=0}^{2^k-1}i=2^k-1$，证明可以考虑 $x\bigoplus(2^k-1-x)=0$，且 $2^{k-1}$ 为偶数。

那么我们就可以递推的求 $\bigoplus\limits_{i=0}^ni$ 了。具体地，考虑分为 $0\sim2^k-1$ 和 $2^k\sim n$ 两部分（其中 $2^k-1\le n<2^{k+1}-1$），有以下两种情况：

- 当 $k\ge2$ 时，第一部分显然为 $0$，计算出第二部分的数的个数奇偶性，若为偶数则必为 $0\sim n-2^k$ 对应的答案，若为奇数则在 $0\sim n-2^k$ 对应答案的基础上加 $2^k$ 即可。

- 当 $k<2$ 时，$n\le2$，特判即可。

那么我们可以把 $x$ 异或上 $\bigoplus\limits_{i=0}^{k-1}i$，之后就是要找到 $n\in[l,r]$ 且 $\bigoplus\limits_{i=0}^ni=x$。

对于这个问题，我们同样可以递推地求解。

设当前考虑到二进制位 $d$，则 $0\le l\le r\le2^{d+1}-1$。再设 $op$ 为所求答案 $n$ 的奇偶性（因为你需要知道最高位被异或的次数的奇偶性），那么有以下五种情况：

- $x<0$ 或 $x\ge2^{d+1}$：显然无解，返回 $-1$。

- $d=1$：这时无法使用结论，但注意到 $l,r$ 都很小，暴力即可。

- $r<2^d$：$d$ 这一位没有用，直接递归到 $d-1$ 即可。

- $l\ge2^d$：$\le2^d-1$ 的数必然被算进答案，于是就变成了 $l-2^d,r-2^d,d-1,x-[op=0]\times2^d$ 时的情况。

- $l<2^d\le r$：分成两部分，分别是上述两种情况。

这样的话这题就做完了，但我们还需要分析一下时间复杂度：注意到考虑到二进制位 $d$ 时 $l$ 必为 $0$ 或初始 $l$ 的后缀，$r$ 必为 $2^{d+1}-1$ 或初始 $r$ 的后缀，所以状态数和时间复杂度都是 $O(\log V)$ 的。

具体细节可以参考我的赛时代码（核心部分）：

```cpp
int calc(int n)
{
	if (n < 0) return 0;
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 3;
	int x = (1 << __lg(n + 1));
	return ((n - x) % 2 == 0 ? x : 0) + calc(n - x);
}
int get(int x, int y)
{
	return (x == -1 ? -1 : x + y);
}
int query(int l, int r, int d, int x, int op)
{
	if (x < 0 || x >= (1 << d + 1)) return -1;
	if (d == 1)
	{
		for (int i = l; i <= r; i++) if (i % 2 == op && calc(i) == x) return i;
		return -1;
	}
	if (r < (1 << d)) return query(l, r, d - 1, x, op);
	if (l >= (1 << d)) return get(query(l - (1 << d), r - (1 << d), d - 1, x - (op == 0 ? (1 << d) : 0), op), (1 << d));
	int ans = query(l, (1 << d) - 1, d - 1, x, op);
	if (ans == -1) ans = get(query(0, r - (1 << d), d - 1, x - (op == 0 ? (1 << d) : 0), op), (1 << d));
	return ans;
}
bool Med;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << "MB" << endl;
	int T;
	cin >> T;
	while (T--)
	{
		int l, r, k, x;
		cin >> l >> r >> k >> x;
		x ^= calc(k - 1);
		int ans = query(l, r, 29, x, 0);
		if (ans == -1) ans = query(l, r, 29, x, 1);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

本题作为异或的思维题，可以利用异或性质进行一些有趣的分析，以下我提供的是一种奇怪的思路（也许易于理解？）。
## 题意理解
本题是一道涉及区间异或和构造题。由数据范围，我们遗憾地发现，$T \le 10^5$！也就是说，我们要在常数时间复杂度或对数复杂度内解决问题！这是我们想到，这也许是一道别出心裁的构造题？
## 思路分析
本题涉及异或，作为一种神奇的运算，有很多性质值得我们运用，例如交换律和结合律，在此，让我介绍一下相邻数异或的一个重要性质——奇偶抵消！我们容易发现，对于任意偶数，它与其相邻的下一个奇数的异或和总为 $1$！（证明略）这样，每四数均能形成异或和为零的组合，这不正是一个基于此进行分类讨论及常数时间内判断的重要结论吗？下面，让我详细展示具体分类：

1. $k$ 为偶数。此时构造出的 $n$ 为奇数时，其异或和必为 $0$ 或 $1$，其余情况，其异或和为 $n$ 或 $n \oplus 1$。可由此关于 $l$ 和 $r$ 进一步讨论。
2. $k$ 为奇数。此时构造出的 $n$ 为奇数时，其异或和为 $k$ 或 $k \oplus 1$，否则，其异或和为 $k \oplus n$ 或 $k \oplus n \oplus 1$。可由此关于 $l$ 和 $r$ 进一步讨论。
## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{int t;cin>>t;
 while(t--)
 {long long l,r,k,x;
  cin>>l>>r>>k>>x;
  if(k==l&&x==k)
  {cout<<k<<'\n';
   continue;
  }
  if(k%2==1)
  {if(x==(k^1)||x==k)
   {if(x==k)
    {if(r%4==k%4) cout<<r<<'\n';
    else if(l!=r&&(r-1)%4==k%4) cout<<r-1<<'\n';
    else if(r-2>=l&&(r-2)%4==k%4) cout<<r-2<<'\n';
    else if(r-3>=l&&(r-3)%4==k%4) cout<<r-3<<'\n';
    else cout<<"-1\n";
    }
    else
    {k+=2;
     if(r%4==k%4) cout<<r<<'\n';
    else if(l!=r&&(r-1)%4==k%4) cout<<r-1<<'\n';
    else if(r-2>=l&&(r-2)%4==k%4) cout<<r-2<<'\n';
    else if(r-3>=l&&(r-3)%4==k%4) cout<<r-3<<'\n';
    else cout<<"-1\n";
    }
   }
   else if((x^k)>=l&&(x^k)<=r&&((x^k)-k)%4==1)
    cout<<(x^k)<<'\n';
   else if((x^1^k)>=l&&(x^1^k)<=r&&((x^1^k)-k)%4==3)
   cout<<(x^1^k)<<'\n';
   else
    cout<<"-1\n";
  }
  else
  {if(x==1||x==0)
   {if(x==0)
    {k--;
    if(r%4==k%4) cout<<r<<'\n';
    else if(l!=r&&(r-1)%4==k%4) cout<<r-1<<'\n';
    else if(r-2>=l&&(r-2)%4==k%4) cout<<r-2<<'\n';
    else if(r-3>=l&&(r-3)%4==k%4) cout<<r-3<<'\n';
    else cout<<"-1\n";
    }
    else
    {k++;
     if(r%4==k%4) cout<<r<<'\n';
    else if(l!=r&&(r-1)%4==k%4) cout<<r-1<<'\n';
    else if(r-2>=l&&(r-2)%4==k%4) cout<<r-2<<'\n';
    else if(r-3>=l&&(r-3)%4==k%4) cout<<r-3<<'\n';
    else cout<<"-1\n";
    }
   }
   else if((x)>=l&&(x)<=r&&((x)-k)%4==0)
    cout<<(x)<<'\n';
   else if((x^1)>=l&&(x^1)<=r&&((x^1)-k)%4==2)
   cout<<(x^1)<<'\n';
   else
    cout<<"-1\n";
  }
 }  
}
```

---

## 作者：canwen (赞：1)

## Solution
赛时以为是不可做题遂没有拼尽全力，最后被黄暴虐了。

建议体验下[这道题（P3908）](https://www.luogu.com.cn/problem/P3908)然后这道题便是水题一道了。

由异或的性质，$x = \bigoplus\limits_{i=k}^n i = \bigoplus\limits_{i=1}^n i \oplus \bigoplus\limits_{i=1}^{k-1} i$。

所以问题转换成判断是否存在 $l \le n \le r$ 使得 $\bigoplus\limits_{i=1}^n i = x \oplus \bigoplus\limits_{i=1}^{k-1} i$，而该等式右边是已知的且可以 $O(1)$ 求。

那么根据[这道题（P3908）](https://www.luogu.com.cn/problem/P3908)题解中所证明出的的规律分类讨论即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define pb push_back
#define mk make_pair
#define fst first
#define snd second
#define pc putchar('\n')
#define nowtime (double)clock()/CLOCKS_PER_SEC
int in(){int k=0,kk=1;char a=getchar();while(!isdigit(a)){if(a=='-') kk=-1;a=getchar();}while(isdigit(a))k=(k<<3)+(k<<1)+a-'0',a=getchar();return k*kk;}
void out(int a){if(a<0) putchar('-'),a=-a;if(a>9) out(a/10);putchar('0'+a%10);}

int getc(int n){
	int res = 0;
	if(n % 4 == 1) res = 1;
	else if(n % 4 == 3) ;
	else if(n % 4 == 0){
		res = n;
	}else{
		res = n+1;
	}
	return res;
}
signed main(){
	int T = in();
	while(T--){
		int l,r,k,x;
		l=in(),r=in(),k=in(),x=in();
		int ans = -1;
		int kk = x ^ getc(k-1);
		if(kk == 0 || kk == 1){
			_rep(i,l,min(l+3,r)){
				if(getc(i) == kk){
					ans = i;
				break;
				}
			}
		}else if(getc(kk) == kk && kk >= l && kk <= r){
			ans = kk;
		}else if(getc(kk-1) == kk && kk-1 >= l && kk -1 <= r){
			ans = kk-1;
		}
		cout << ans << endl;
		
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

### 题意

给出四个非负整数 $l, r, k, x$，求任意一个整数 $n\in[l,r]$ 满足 $\bigoplus\limits_{i=k}^n i = x$。

### 思路

这题主要考察异或前缀和的性质。

首先题目要求的是区间异或和，所以我们考虑求异或前缀和。我们有：

$$f(n)=\bigoplus\limits_{i=0}^n i=\begin{cases}n&n\equiv 0\pmod{4}\\1&n\equiv 1\pmod{4}\\n+1&n\equiv 2\pmod{4}\\0&n\equiv 3\pmod{4}\end{cases}$$

由于 $\bigoplus\limits_{i=k}^ni=x$，$f(n)=f(k-1)\oplus x$。我们求得 $f(k-1)\oplus x=a$。那么即求是否存在整数 $n\in [l,r]$ 使得 $f(n)=a$。

- 若 $a=0$，即 $f(n)=0$，那么 $n\equiv 3\pmod 4$。直接选一个区间内模四得三的数即可。
- 若 $a=1$，即 $f(n)=1$，那么 $n\equiv 1\pmod 4$。直接选一个区间内模四得一的数即可。
- 若 $a\equiv 0\pmod 4$ 且 $a\neq0$，那么 $n=a$，否则不可能有 $f(n)=a$。
- 若 $a\equiv 3\pmod 4$，那么 $n=a-1$，否则不可能有 $f(n)=a$。
- 否则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int f(int n){
	if(n%4==0) return n;
	else if(n%4==1) return 1;
	else if(n%4==2) return n+1;
	else return 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int l,r,k,x;cin>>l>>r>>k>>x;
		int s=x^f(k-1);
		if(s==0){
			int ans=l+(3-l%4+4)%4;
			if(ans<=r){
				cout<<ans<<"\n";
				continue;
			}
		}
		if(s==1){
			int ans=l+(1-l%4+4)%4;
			if(ans<=r){
				cout<<ans<<"\n";
				continue;
			}
		}
		if(s%4==0){
			if(s>=l && s<=r){
				cout<<s<<"\n";
				continue;
			}
		}
		if(s%4==3){
			if(s-1>=l && s-1<=r){
				cout<<s-1<<"\n";
				continue;
			}
		}
		cout<<"-1\n";
	}
    return 0;
}
```

---

## 作者：CaiZi (赞：1)

记 $f(m)=\bigoplus\limits_{i=0}^{m}i$。

首先，异或的逆运算为异或（因为连续异或同一个数两次等同于没有异或）。所以可以把原条件改为 $f(k-1)\oplus f(n)=x$，记 $t=x\oplus f(k-1)$，$t$ 是已知的，我们需要求出 $f(n)=t$。

然后我们有一个广为人知的式子：
$$f(m)=\begin{cases}m&m\equiv0\pmod4\\1&m\equiv1\pmod4\\m+1&m\equiv2\pmod4\\0&m\equiv3\pmod4\end{cases}$$
> 证明：取 $m=3$，此时 $f(m)=0$。而当某个 $m\equiv3\pmod4$ 成立时：
> $$\begin{aligned}f(m+4)&=f(m)\oplus(m+1)\oplus(m+2)\oplus(m+3)\oplus(m+4)\\&=4\lfloor\frac{m+1}{4}\rfloor\oplus(4\lfloor\frac{m+2}{4}\rfloor+1)\oplus(4\lfloor\frac{m+3}{4}\rfloor+2)\oplus(4\lfloor\frac{m+4}{4}\rfloor+3)\end{aligned}$$
> 由于 $4\lfloor\frac{m+1}{4}\rfloor,4\lfloor\frac{m+2}{4}\rfloor,4\lfloor\frac{m+3}{4}\rfloor,4\lfloor\frac{m+4}{4}\rfloor$ 的二进制下末尾两位均为 $0$，而 $0,1,2,3$ 的二进制下非末尾两位均为 $0$。因此它们互不干扰，可以把它们分别求异或再相加：
> $$\begin{aligned}f(m+4)&=4\lfloor\frac{m+1}{4}\rfloor\oplus4\lfloor\frac{m+2}{4}\rfloor\oplus4\lfloor\frac{m+3}{4}\rfloor\oplus4\lfloor\frac{m+4}{4}\rfloor+1\oplus2\oplus3\oplus0\\&=0\end{aligned}$$
> 于是我们用归纳法证明了，对于 $m\equiv3\pmod4$，有 $f(m)=0$。然后同样按照上面的方法，可以依次推出 $m\equiv0,1,2\pmod4$ 的情况。

然后我们考虑反向对这个式子进行分类讨论：
- 取 $n\equiv0\pmod4$：当 $t=n$ 时。
- 取 $n\equiv1\pmod4$：当 $t=1$ 时。
- 取 $n\equiv2\pmod4$：当 $t=n+1$ 时。
- 取 $n\equiv3\pmod4$：当 $t=0$ 时。

分别判断这四种取值能否有某种可以成立即可，注意需要满足 $l\le n\le r$。

代码展示：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int _,l,r,k,x,t;
inline int calc(int m){
	if(m%4==0)return m;
	else if(m%4==1)return 1;
	else if(m%4==2)return m+1;
	else return 0;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>_;
	while(_--){
		cin>>l>>r>>k>>x;
		t=x^calc(k-1);
		if(t%4==0&&l<=t&&t<=r){//通用的情况
			cout<<t<<'\n';
		}
		else if(t%4==3&&l<=t-1&&t-1<=r){//通用的情况
			cout<<t-1<<'\n';
		}
		else if(t==1){//t=1的情况
			if(l%4==1)cout<<l<<'\n';
			else if(l%4==0&&l+1<=r)cout<<l+1<<'\n';
			else if(l%4==3&&l+2<=r)cout<<l+2<<'\n';
			else if(l%4==2&&l+3<=r)cout<<l+3<<'\n';
			else cout<<"-1\n";
		}
		else if(t==0){//t=0的情况
			if(l%4==3)cout<<l<<'\n';
			else if(l%4==2&&l+1<=r)cout<<l+1<<'\n';
			else if(l%4==1&&l+2<=r)cout<<l+2<<'\n';
			else if(l%4==0&&l+3<=r)cout<<l+3<<'\n';
			else cout<<"-1\n";
		}
		else{//否则就是无解
			cout<<"-1\n";
		}
	}
	return 0;
}
```

---

## 作者：huanglihuan (赞：1)

### Solution
首先我们设 $s(x)=\bigoplus\limits_{i=0}^x i$，那么有：
$$s(x)=\begin{cases}x,&x\bmod 4=0\\1,&x\bmod 4=1\\x+1,&x\bmod 4=2\\0,&x\bmod 4=3\end{cases}$$
紧接着，我们可以通过前缀异或和，接下来通过分讨前缀的方法得出答案。
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
#define in(x,y,z) x>=y&&x<=z
using namespace std;
const int N = 2e6 + 5;
int a [N];
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
int xor1 (int n)
{
	if (n < 0) return 0;
	int m = n % 4;
	if (m == 0) return n;
	else if (m == 1) return 1;
	else if (m == 2) return n + 1;
	else return 0;
}
int sum (int l,int r,int k,int x)
{
	int kk = k - 1;
	int f = xor1 (kk);
	int t = x ^ f;
	if (t % 4 == 0)
    {
		int c = t;
		if (c >= l && c <= r) return c;
	}
	if (t == 1)
    {
		int m = l % 4;
		int d = (1 - m + 4) % 4;
		int s = l + d;
		if (s <= r) return s;
	}
	if (t % 4 == 3)
	{
		int c = t - 1;
		if (c >= l && c <= r) return c;
	}
	if (t == 0)
	{
		int m = l % 4;
		int d = (3 - m + 4) % 4;
		int s = l + d;
		if (s <= r) return s;
	}
	return -1;
}
signed main ()
{
	int T;
	cin >> T;
	while (T--)
    {
		int l, r, k, x;
		cin >> l >> r >> k >> x;
		cout << sum (l,r,k,x) << endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

概括一下题意：在给定范围 $l \leq n \leq r$ 中找到一个整数 $n$，使得从 $k$ 到 $n$ 的所有整数按位异或的结果等于给定值 $x$。如果没有解，输出 `-1`。

我们来回顾下按位异或的性质：
> - **交换性与结合性**：$a \oplus b = b \oplus a$，且 $(a \oplus b) \oplus c = a \oplus (b \oplus c)$。
> - **自反性**：$a \oplus a = 0$。
> - **0的吸收性**：$a \oplus 0 = a$。

**那么怎样计算区间的异或值？**

假设我们要计算从 $k$ 到 $n$ 的异或值，记作：
$$
	\text{xor}(k, n) = k \oplus (k+1) \oplus \dots \oplus n
	$$
- 我们可以利用前缀异或的方式来简化计算。如果 $\text{xor}(a, b)$ 表示从 $a$ 到 $b$ 的异或和，则：
$$
	\text{xor}(a, b) = \text{XOR}(b) \oplus \text{XOR}(a-1)
	$$
其中 $\text{XOR}(i)$ 表示从 0 到 $i$ 的异或和。我们可以通过找到 $\text{XOR}(n)$ 和 $\text{XOR}(k-1)$ 来得到从 $k$ 到 $n$ 的异或值。

所以不难发现前缀异或的规律：
- $\text{XOR}(i) = \begin{cases} 
	i & i \mod 4 = 0 \\
	1 & i \mod 4 = 1 \\
	i + 1 & i \mod 4 = 2 \\
	0 & i \mod 4 = 3
	\end{cases}$

我们要找到 $n$ 使得：
$$
	\text{xor}(k, n) = x
	$$
即：
$$
	\text{XOR}(n) \oplus \text{XOR}(k-1) = x
	$$
通过简单的代数变换，我们可以得到：
$$
	\text{XOR}(n) = x \oplus \text{XOR}(k-1)
	$$
因此，只需要遍历 $n$ 从 $l$ 到 $r$，计算 $\text{XOR}(n)$ 并检查是否满足上述条件。

$\huge Code$

```cpp
#include <iostream>

using namespace std;

// 计算从0到x的异或和
int XOR(int x) {
	if (x % 4 == 0) return x;
	if (x % 4 == 1) return 1;
	if (x % 4 == 2) return x + 1;
	return 0;
}

int main() {
	int T;
	cin >> T;
	
	while (T--) {
		int l, r, k, x;
		cin >> l >> r >> k >> x;
		
		// 计算XOR(k-1)
		int sum = XOR(k - 1);
		
		// 目标值为 x ⊕ XOR(k-1)
		int ans = x ^ sum;
		
		// 遍历[l, r]区间查找n
		bool found = false;
		for (int n = l; n <= r; ++n) {
			if (XOR(n) == ans) {
				cout << n << '\n';
				found = true;
				break;
			}
		}
		
		if (!found) {
			cout << "-1\n";
		}
	}
	
	return 0;
}
```

果然不出所料交上去后发现 $TLE$ 了。
| 测试点编号 | $T \leq$ | $r \leq$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1\sim 4$ | $5000$ | $5000$ |  |
| $5\sim 8$ | $10^5$ | $10^9$ | AB |
| $9\sim 14$ | $10^5$ | $10^9$ | A |
| $15\sim 20$ | $10^5$ | $10^9$ |  |

- 特殊性质 A：保证 $k$ 为偶数。
- 特殊性质 B：保证 $x \leq 1$。

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10^5$，$1 \leq k \leq l \leq r \leq 10^9$，$0 \leq x \leq 2\times 10^9$。

所以，为了解决这个问题，我们需要找到满足条件的整数 $n$，使得在给定区间 $[l, r]$ 内，从 $k$ 到 $n$ 的所有整数的异或和等于 $x$。直接遍历区间会导致超时，因此我们需要优化算法。

我们可以利用上文推出的异或的性质来高效地解决问题：

1. **计算目标值**：通过计算从 $0$ 到 $k-1$ 的异或和，得到目标值 $ans = x \oplus XOR(k-1)$，其中 XOR 是异或前缀和函数。
2. **检查四个条件**：根据异或前缀和的规律，我们可以将问题分解为四个条件，逐一检查是否存在满足条件的 n：
   - **情况一**：当 $ans$ 能被 $4$ 整除时，直接检查 $ans$ 是否在区间内。
   - **情况二**：当 $ans$ 为 $1$ 时，检查是否存在$\mod 4$ 余 $1$ 的数。
   - **情况三**：当 $ans-1 \mod 4$ 余 $2$ 时，检查 $ans-1$ 是否在区间内。
   - **情况四**：当 $ans$ 为 $0$ 时，检查是否存在 $\mod 4$ 余 $3$ 的数。

$\Huge Code$
```cpp
#include <iostream>

using namespace std;

int XOR(int x) {
	switch (x % 4) {
		case 0: return x;
		case 1: return 1;
		case 2: return x + 1;
		default: return 0; // x % 4 == 3
	}
}

int solve(int l, int r, int k, int x) {
	int sum = XOR(k - 1);
	int ans = x ^ sum;
	
	// 情况一：ans % 4 == 0，检查n=ans是否在区间内
	if (ans % 4 == 0) {
		int n = ans;
		if (n >= l && n <= r) {
			return n;
		}
	}
	
	// 情况三：检查(ans-1) %4 ==2，n=ans-1是否在区间内
	if ((ans - 1) % 4 == 2) {
		int n = ans - 1;
		if (n >= l && n <= r) {
			return n;
		}
	}
	
	// 情况二：ans ==1，寻找mod4=1的数
	if (ans == 1) {
		int rem = l % 4;
		int delta = (1 - rem + 4) % 4;
		int start = l + delta;
		if (start <= r) {
			return start;
		}
	}
	
	// 情况四：ans ==0，寻找mod4=3的数
	if (ans == 0) {
		int rem = l % 4;
		int delta = (3 - rem + 4) % 4;
		int start = l + delta;
		if (start <= r) {
			return start;
		}
	}
	
	// 无解
	return -1;
}

int main() 
{
	int T;
	cin >> T;
	
	while (T--) {
		int l, r, k, x;
		cin >> l >> r >> k >> x;
		cout << solve(l, r, k, x) << '\n';
	}
	
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/204848396)

---

## 作者：Linyijun_ (赞：1)

# P11798【MX-X9-T2】『GROI-R3』XOR
## 解题思路
对于这个题目我们知道从 k 异或到 n 的值。

因为 1 到 n 的异或和是有规律的，所以我们可以先算 1 到 k 的异或和，接着就可以得到 1 到 n 的异或和，接着通过逆推的方式来求到 n 。

我们设  $f(n)=1\bigoplus2…\bigoplus n$  ,则有：

 $$$f(n) = \begin{cases} n, & n\equiv 0(\mod 4 )  \\ 1, &  n\equiv 1(\mod 4 )\\ n+1 & n\equiv 2(\mod 4 ) \\ 0, &n\equiv 3(\mod 4 )\end{cases}$$$ 

 具体的可以参考题目 [P3908](https://www.luogu.com.cn/problem/P3908) 。

 接着重要的是讲我们如何通过逆推来得到答案，当我们得到  $f(n)$ 时。
 
 1. $f(n)\equiv 0(\mod 4 )$ 的话，那么  $n=f(n)$ 。
 2.  $f(n)=1$ 只要使  $n\equiv 1(\mod 4 )$ 。
 3.  $f(n)\equiv 3(\mod 4 )$  那么使  $n=f(n)-1$ 。
 4.    $f(n)=0$ ， 那么使  $n\equiv 3(\mod 4 )$ 。

 同时，我们还要保证我们求得的  $n$ ，要在  $[l,r]$ 的范围内，试完一遍无可行的解，就输出 -1 。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,l,r,k,x,p,q,ans;
int f(int x){
	if(x%4==0)return x;
	if(x%4==1)return 1;
	if(x%4==2)return x+1;
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r>>k>>x;
		p=f(k-1);
		q=x^p;
		if(q>=l&&q<=r&&q%4==0){
			cout<<q<<endl;
			continue;
		}else if(q-1>=l&&q-1<=r&&(q-1)%4==2){
			cout<<q-1<<endl;
			continue;
		}
		else {
			if(q==1){
				if(l%4==0)ans=l+1;
				else if(l%4==1)ans=l;
				else if(l%4==2)ans=l+3;
				else ans=l+2;
				if(ans<=r)cout<<ans;
				else cout<<-1;
				cout<<endl;
				continue;
			}if(q==0){
				if(l%4==0)ans=l+3;
				else if(l%4==1)ans=l+2;
				else if(l%4==2)ans=l+1;
				else if(l%4==3)ans=l;
				if(ans<=r)cout<<ans;
				else cout<<-1;
				cout<<endl;
				continue;
			}
		}cout<<-1<<endl;
	}
	return 0;
} 
```
如有什么不好的地方，请指出我这个~~蒟蒻~~的问题。

---

## 作者：Yi_chen123 (赞：0)

ps：大括号搞了半天没弄出来。

## 思路

我们记 $f(x)$ 为 $1$ 至 $x$ 的异或和，即 $1 \oplus 2 \oplus 3 \oplus \cdots \oplus n$。\
基于异或定理 $4i \oplus (4i+1) \oplus (4i+2) \oplus (4i+3) = 0$，我们能得出以下结论：

$$
f(x) = \begin{cases}
n, & n \equiv 0 \pmod 4 \\
1, & n \equiv 1 \pmod 4 \\
n+1,& n \equiv 2 \pmod 4 \\
0, &n \equiv 3 \pmod 4
\end{cases}
$$

并且，原式 $\bigoplus\limits_{i=k}^n i = x$ 可以经过如下转换：

$$
\bigoplus\limits_{i=1}^{k-1} i \oplus \bigoplus\limits_{i=1}^n i = x
$$

$$
f(k-1) \oplus f(n) = x
$$

$$
f(n) = x \oplus f(k-1)
$$

此时，我们令 $y = x \oplus f(k-1)$，思路就简单明了了，题目实际就是让我们求出满足 $n \in [l,r]$ 且 $f(n) = y$ 的 $n$ 值！\
那么，我们只需要进行~~小学二年级就学过的~~分类讨论，就能找到正解了。

- 当 $y=0$ 时，$f(n) = 0$。所以倒推出 $n \equiv 3 \pmod 4$，只要在此基础上符合 $n \in [l,r]$ 均有解。
- 当 $y=1$ 时，$f(n) = 1$。得 $n \equiv 1 \pmod 4$，解法同上。
- 当 $y \notin \{0,1\}$ 时，需要进行进一步讨论：
- - 当 $y \equiv 0 \pmod 4$ 时，$f(x)=n=y$，可证得满足 $y \in [l,r]$ 即为原式解。
  - 当 $y \equiv 2 \pmod 4$ 时，$f(x)=n+1=y$，可证得移项得 $n=y-1$，满足 $(y-1) \in [l,r]$ 即为原式解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int f(int n){
	switch(n % 4){
		case 0 : return n; break;
		case 1 : return 1; break;
		case 2 : return n+1; break;
		case 3 : return 0; break;
	}
}
signed main(){
    int t;
    cin >> t;

    while(t--){
    	int l, r, k, x;
    	cin >> l >> r >> k >> x;

    	int y = x ^ f(k - 1);
    	if(y == 0){
    		bool flag = false;
    		for(int i = l; i <= r; ++i){
    			if(i % 4 == 3){
    				cout << i << endl;
    				flag = true;
    				break;
				}
			}
			if(!flag) cout << "-1\n";
		}
		else if(y == 1){
			bool flag = false;
    		for(int i = l; i <= r; ++i){
    			if(i % 4 == 1){
    				cout << i << endl;
    				flag = true;
    				break;
				}
			}
			if(!flag) cout << "-1\n";
		}
		else{
			if(y % 4 == 0 && y <= r && y >= l){
				cout << y << endl;
			}
			else if(y % 4 == 3 && y - 1 <= r && y - 1 >= l){
				cout << y - 1 << endl;
			}
			else cout << "-1\n";
		}
	}
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

如果你对异或有兴趣的话，一定会注意到如何更好的计算 $f(n)=\bigoplus\limits_{i=0}^n i$。

考虑到当最低位二进制下为 $1$ 时，将异或和两两分组，不考虑最后一位，其它位两两抵消，此时其它位均为 $0$。

否则其它位不变。

然后考虑最低位怎么求，我们四个四个分组，显然哪一组并不重要，每一组中间两个最低位为 $1$，否则为 $0$。

我们再形象点，$f(n)$ 最低一位就是 $n$ 最低两位异或和。

于是我们可以先把等式两边都异或上 $f(k-1)$。

然后我们知道 $f(n)$，尝试倒推 $n$。

不考虑最低位，所有位不全为 $0$ 时，$n$ 最低位确定为 $0$，$n$ 其它位确定为 $f(n)$ 对应为的数 ，得到以后，我们还要判定得到的 $n$ 最低两位异或和得到的是否是 $f(n)$ 最低位，以及是否满足 $l\le n\le r$。

否则，我们分讨，$n$ 最低位为 $0$ 或者 $1$，为 $0$ 就一种情况就是本来就没数，为 $1$，最后两位确定，剩下位自己填，相当于 $n=4x+a$，$a$ 位常数，$x$ 几都可以。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int qx(int x){//f(x)
	if(x&1){
		return ((x>>1)&1)^(x&1);
	}
	return ((x>>1)<<1)+((x>>1)&1)^(x&1);
}
void _main(){
	int l,r,k,x;
	cin>>l>>r>>k>>x;
	x^=qx(k-1);
	k=1;
	if(x==1){
		int z;
		z=(r-1)/4;
		z=z*4+1;
		if(z>=l){
			cout<<z<<endl;
		}else{
			cout<<-1<<endl;
		}
		return;
	}
	if(x==0){
		int z;
		z=(r-3)/4;
		z=z*4+3;
		if(z>=l){
			cout<<z<<endl;
		}else{
			cout<<-1<<endl;
		}
		return;
	}
	if((x&1)!=((x>>1)&1)){
		cout<<-1<<endl;
		return;
	}
	int z;
	z=((x>>1)<<1);
	if(z<l||z>r){
		cout<<-1<<endl;
	}else{
		cout<<z<<endl;
	}
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：ztd___ (赞：0)

怎么全世界都是用什么奇妙打表算的啊。难道全世界只有我是用奇妙小性质算的吗。但是奇妙小性质真的很好想啊。代码也很浓缩啊。真是一道奇妙题。

文中的绝大多数 $p$ 都表示题目里的终点 $n$。

首先引出我们的奇妙小性质。
> **奇妙小性质 1：**  
> 对于任意**非负偶数** $k$，$k \oplus (k + 1) = 1$。

证明很奇妙，不然为什么叫奇妙小性质。

显然，一个非负偶数的二进制形式必然是一坨 01 串加上一个 $0$。

所以这个东西加上的 $1$ 一定直接在末尾的地方加上而不会有进位，就是把最后的 $0$ 变成 $1$。

那么显然，这两个东西前面的 01 串都是一样的，全消掉了，只剩下末尾的 $0$ 和 $1$，而 $0 \oplus 1 = 1$，所以得证了。

奇妙小性质又可以帮我们弄出来一个东西。
> **奇妙小性质 2：**  
> 对于非负偶数 $k$ 和非负奇数 $p(p > k)$，$\bigoplus\limits_{i=k}^p i = (\frac{p - k + 1}{2}) \bmod 2$。

证明也很简单啊。根据奇妙小性质 1，我们将一个非负偶数和这个数加 $1$ 分成一组。这样一组的异或和就是 $1$。

总共是 $p - k + 1$ 个数，$2$ 个数一组，总共就是 $(\frac{p - k + 1}{2})$ 组。每组的异或和为 $1$，总共就是 $(\frac{p - k + 1}{2})$ 个 $1$ 异或在一起。其中每两个可以互相抵消，剩下的就是 $(\frac{p - k + 1}{2}) \bmod 2$ 了。

有了这些奇妙的东西我们就可以解决问题了。为了方便同学们理解，我们一个一个 Subtask 解决。

### 特殊性质 AB
满足 $x \le 1$ 且 $k$ 为偶数。

显然就是让 $(\frac{p - k + 1}{2}) \bmod 2 = x$ 且 $l \le p \le r$ 且 $p$ 为奇数嘛。

那就可以直接找 $l$ 后面的第一个奇数，然后看答案对不对。

不对说明要再多异或一组，一组两个，所以 $p$ 就要加 $2$。否则直接输出 $p$ 不就好了。

然后判断最终是不是 $p \le r$。如果超出了就输出 `-1` 好了。因为我们一开始找的 $p$ 就是 $l$ 后面的，所以最后没必要判 $l$。

### 特殊性质 A
满足 $k$ 为偶数。

既然从一个偶数开始，到一个奇数结束，异或和肯定是 $0$ 或 $1$，而起点是 $k$ 已经固定了，那只能通过改终点来让结果出现 $0$ 和 $1$ 以外的数字。

然后因为如果终点是奇数等于没改，所以我们肯定要将终点改成一个偶数 $p$。这样我们的结果就会是 $p$ 或者 $p \oplus 1$。显然 $p \oplus 1$ 是奇数。

题目告诉我们结果为 $x$，那我们直接判断 $x$ 的奇偶就好了啊！太奇妙了！

如果 $x$ 是偶数，因为终点不能是奇数，所以最终的终点肯定是 $x$ 了。那么就判断 $k$ 到 $x$ 的异或和是不是 $x$ 就好了。

否则，当 $x$ 为奇数时，因为终点是偶数，所以终点肯定是 $x - 1$。如果是 $x + 1$ 的话答案就大了。那么就判断 $k$ 到 $x - 1$ 的异或和是不是 $x$ 就好了。

然后判断终点是不是在 $l$ 和 $r$ 之间就可以了啊！我们拿到了奇妙的 50pts。

### 正解
既然 $k$ 是奇数，那么就考虑把问题化成 $k$ 为偶数的形式。

有一个众所周知的奇妙小定理。
> **奇妙小定理 3：**  
> $x \oplus x = 0$，$x \oplus 0 = x$。

然后因为 $k$ 是肯定要异或上的，所以把题目中的式子化成这个样子：
$$k \oplus (\bigoplus\limits_{i=k+1}^p i) = x$$

两边同时异或 $k$ 得到：
$$k \oplus k \oplus (\bigoplus\limits_{i=k+1}^p i) = x \oplus k$$

即：
$$0 \oplus (\bigoplus\limits_{i=k+1}^p i) = x \oplus k$$

也就是：
$$\bigoplus\limits_{i=k+1}^p i = x \oplus k$$

而 $k + 1$ 是偶数，所以我们让 $x \gets x \oplus k$，$k \gets k + 1$，就可以把式子改成 $k$ 为偶数的形式了。太奇妙了。

然后也是拿到了 100pts。奇妙好题。然后不管哪种情况，注意判断终点是否在 $l$ 和 $r$ 以内即可。

给出经过简单优化后位居最优解第三的代码。
```cpp
#include <bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;
inline int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x;
}
inline void write(int x) {
    if (x >= 10) write(x / 10);
    putchar(x % 10 + 48);
}
int main() {
    int T, l, r, k, x;
    T = read();
    while (T--) {
        l = read(), r = read(), k = read(), x = read();
        if (k & 1) x ^= k, k++;
        if (x <= 1) {
            int p = ((l & 1) == 0 ? l + 1 : l);
            int t = (p - k + 1) / 2;
            int y = ((t & 1) == x ? p : p + 2);
            if (y > r) puts("-1");
            else write(y), putchar('\n');
        } else {
            if ((x & 1) == 0) {
                if (x >= l && x <= r) {
                    int p = x - 1;
                    int t = (p - k + 1) / 2;
                    if ((t & 1) == 0) write(x), putchar('\n');
                    else puts("-1");
                } else puts("-1");
            } else {
                if (x - 1 >= l && x - 1 <= r) {
                    int p = x - 2;
                    int t = (p - k + 1) / 2;
                    if ((t & 1) == 0) puts("-1");
                    else write(x - 1), putchar('\n');
                } else puts("-1");
            }
        }
    }
    return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

说句闲话：风铃草习惯在洛谷提交页面写代码，写一半不小心随机打开了书签栏中的链接……

我码没了，警钟长鸣。

---

记 $f(n)=\oplus^n_{i=1}i$。

根据经典结论：

$$f(n)=
\begin{cases}
 n & n\equiv0\pmod 4\\ 
 1 & n\equiv1\pmod 4\\ 
 n+1 & n\equiv2\pmod 4\\ 
 0 & n\equiv3\pmod 4
 
\end{cases}$$

[证明](https://www.cnblogs.com/Mychael/p/8633365.html)。

然后你可以先去把 [P3098](https://www.luogu.com.cn/problem/P3908) A 了。

---

异或可以前缀异或和，那么利用上面的柿子求一个连续自然数区间的异或和就会做了。

所以有 $x=f(k-1)\oplus f(n)$。

依据异或的性质可以得出 $f(n)=f(k-1)\oplus x$。

大分讨找出 $[l,r]$ 间合法的 $n$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f(int n){
    if(n%4==0)return n;
    if(n%4==1)return 1;
    if(n%4==2)return n+1;
    if(n%4==3)return 0;
}
void solve(){
    int l,r,k,x;
    cin>>l>>r>>k>>x;
    int flc=f(k-1);
    x^=flc;
    if(x==0){
        for(int i=l;i<=r;i++){
            if(i%4==3){
                cout<<i<<endl;
                return;
            }
        }
        puts("-1");
        return;
    }
    if(x==1){
        for(int i=l;i<=r;i++){
            if(i%4==1){
                cout<<i<<endl;
                return;
            }
        }
        puts("-1");
        return;
    }
    if(l<=x&&r>=x&&x%4==0){
        cout<<x<<endl;
        return;
    }
    if(l<=x-1&&r>=x-1&&x%4==3){
        cout<<x-1<<endl;
        return;
    }
    puts("-1");
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：liyunhe (赞：0)

## 题意分析

设 $f(n)$ 表示 $1\sim n$ 的异或和。找到一个 $l \le n\le r$ 的 $n$。满足 $k\sim n$ 的异或和为 $x$，因为异或两次等于异或 $0$，所以等价于 $f(n) \oplus f(k-1)=x$。

## 做法解析

首先，异或有一个规律：

- 当 $n \equiv 0 (\bmod 4)$ 时，$f(n)=n$；
- 当 $n \equiv 1 (\bmod 4)$ 时，$f(n)=1$；
- 当 $n \equiv 2 (\bmod 4)$ 时，$f(n)=n+1$；
- 当 $n \equiv 3 (\bmod 4)$ 时，$f(n)=0$。

### 简单证明

1. **基例验证：**
   - $n = 0$：$f(0)=0$，符合 $n\equiv0(\bmod4)$ 时，$f(n)=n$。
   - $n = 1$：$f(1)=0\oplus1=1$，符合 $n\equiv1(\bmod 4)$ 时，$f(n)=1$。
   - $n = 2$：$f(2)=0\oplus1\oplus2=3$，符合 $n\equiv2(\bmod4)$ 时，$f(n)=n+1$。
   - $n = 3$：$f(3)=0\oplus1\oplus2\oplus3=0$，符合 $n\equiv3(\bmod4)$ 时，$f(n)=0$。
2. **归纳步骤：**
   - **当 $n=4k$**：
     - $f(4k)=4k$。
     - 下一步：$f(4k+1)=f(4k)\oplus(4k+1)=4k\oplus(4k+1)=1$（因为 $4k$ 和 $4k+1$ 仅在最低位不同，异或后为 $1$）。
   - **当 $n=4k+1$**：
     - $f(4k+1)=1$。
     - 下一步：$f(4k+2) = f(4k+1)\oplus(4k+2) = 1\oplus(4k+2)$。由于 $4k+2$ 的二进制最低两位为 `10`，异或 `01` 后得到 `11`，即结果为 $(4k+2)+1=4k+3$。
   - **当 $n=4k+2$**：
     - $f(4k+2)=4k+3$。
     - 下一步：$f(4k+3)=f(4k+2)\oplus(4k+3)=(4k+3)\oplus(4k+3)=0$。
   - **当 $n=4k+3$**：
     - $f(4k+3)=0$。
     - 下一步：$f(4(k+1))=f(4k+3)\oplus4(k+1) = 0\oplus4(k+1) = 4(k+1)$，符合 $n\equiv0(\bmod4)$ 时，$f(n)=n$。
3. **周期性验证：**
   - 每四个连续整数（$4m, 4m+1, 4m+2, 4m+3$）的异或和为 $0$，因为它们的二进制最后两位覆盖 `00`、`01`、`10`、`11`，异或后每一位均为 $0$。因此，当 $n\ge4$ 时，异或和可分解为完整的四个数块（异或和为 0）和余数部分，余数部分的异或结果由上述归纳步骤确定。

其实更简单的可以用一个程序模拟小范围的数找到规律即可，比赛时就是这么做的，结束后再找的证明。

### 构造函数

根据这个规律，可以得到一个函数，$O(1)$ 求出 $f(x)$。

```cpp
long long get_xor(long long x){//f(x)函数
    if(x%4==0)return x;
    if(x%4==1)return 1;
    if(x%4==2)return x+1;
    if(x%4==3)return 0;
}
```

利用 $f(k-1)\oplus x$ 得到 $f(n)$。再逆向使用性质，得到 $n$，然后判断是否在范围中。

- $f(n)=0$ 时，最小的大于等于 $l$ 且符合 $n \equiv 3 (\bmod 4)$ 的数为 $l+(3-l\bmod4+4)\bmod4$。
- $f(n)=1$ 时，最小的大于等于 $l$ 且符合 $n \equiv 1 (\bmod 4)$ 的数为 $l+(1-l\bmod4+4)\bmod4$。
- $f(n)\equiv 0(\bmod4)$（即 $n\equiv 0(\bmod4)$）时，有且仅有 $f(n)$ 本身符合条件。
- $f(n)\equiv 3(\bmod4)$（即 $n\equiv 2(\bmod4)$）时，有且仅有 $f(n)-1$ 符合条件。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long get_xor(long long x){
    if(x%4==0)return x;
    if(x%4==1)return 1;
    if(x%4==2)return x+1;
    if(x%4==3)return 0;
}
long long get_ans(long long l,long long r,long long n){//逆向得范围部分，n为f(n)
    if(n==0&&l+(3-l%4+4)%4<=r)return l+(3-l%4+4)%4;
    if(n==1&&l+(1-l%4+4)%4<=r)return l+(1-l%4+4)%4;
    if(n%4==0&&l<=n&&n<=r)return n;
    if(n%4==3&&l<=n-1&&n-1<=r)return n-1;
    return -1;
//其实不在范围直接可以返回-1
}
int main(){
    int T=0;
    cin>>T;
    while(T--){
        long long l,r,k,x;
        cin>>l>>r>>k>>x;
        long long xorn=get_xor(k-1)^x;//xorn即为f(n)
        cout<<get_ans(l,r,xorn)<<'\n';
    }
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

梦熊真是蒸蒸日上啊。

有一个经典结论是，$1\sim n$ 的异或和对 $4$ 同余具有规律。具体的当取余为 $0,1,2,3$ 时答案分别是 $n,1,n+1,0$。可以归纳证明。

题目里求一个区间的异或和，只需要差分一下。问题转化为找到一个 $l \le n\le r$ 的 $n$ 使得 $1\sim n$ 的异或和为 $y$。

分类讨论即可。

---

## 作者：Getaway_Car_follower (赞：0)

MX-X T2 最难的一集。

首先我们设 $f(x)=\oplus_{i=1}^x i$。

那么就有 $f(k-1)\oplus f(n)=x$，也就是说，$ f(n)=f(x-1)\oplus k$。

很显然如果我们能快速求出 $f(x)$ 就能快速求出右边那坨玩意儿，然后我们就发现：

$$f(x)=\begin{cases}x&x\bmod 4=0 \\  1& x\bmod 4=1 \\ x+1& x\bmod 4=2 \\ 0& x\bmod 4=3\end{cases}$$

具体的直接数学归纳一下就可以证了。

那么我们已知等式右边那坨的值，根据 $f(x)$ 的公式，直接反推回去就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;

int T,l,r,k,x;
int getxor(int x){
	if(x%4==0) return x;
	if(x%4==1) return 1;
	if(x%4==2) return x+1;
	if(x%4==3) return 0;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;while(T--){
		cin>>l>>r>>k>>x;
		x^=getxor(k-1);
//		cout<<x<<endl;
		if(x==0){
			int ans=-1;
			for(int i=l;i<=r;i++){
				if(i%4==3){
					ans=i;
					break;
				}
			}
			cout<<ans<<endl;
		}
		else if(x==1){
			int ans=-1;
			for(int i=l;i<=r;i++){
				if(i%4==1){
					ans=i;
					break;
				}
			}
			cout<<ans<<endl;
		}
		else if(l<=x-1&&x-1<=r&&(x-1)%4==2) cout<<x-1<<endl;
		else if(l<=x&&x<=r&&x%4==0) cout<<x<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```

---

## 作者：wurang (赞：0)

### 简要题意

我们要找到一个整数 $n$ 使得 $l \leq n \leq r$ 并且从 $k$ 到 $n$ 的所有整数的二进制按位异或和等于 $x$。

### 思路

我们首先要知道异或的一个性质，即：

$$
0 \oplus 1 \oplus 2 \oplus \dots \oplus x-2 \oplus x-1 \oplus x = \begin{cases}
 x \equiv 0 \pmod{4} & x\\
 x \equiv 1 \pmod{4} & 1\\
 x \equiv 2 \pmod{4} & x+1\\
 x \equiv 3 \pmod{4} & 0
\end{cases}
$$

利用异或 $a \oplus a = 0$ 的性质，我们可以将从 $k$ 到 $n$ 的异或和表示为从 $0$ 到 $n$ 的异或和与从 $0$ 到 $k-1$ 的异或和的异或。也就是说：

$$
k \oplus (k+1) \oplus \cdots \oplus n = (0 \oplus 1 \oplus \cdots \oplus n) \oplus (0 \oplus 1 \oplus \cdots \oplus (k-1))
$$

让我们用 $S(m)$ 表示从 $0$ 到 $m$ 的异或和。要找到从 $k$ 到 $n$ 的所有整数的异或和等于 $x$，即要找到 $n$ 使得：

$$
S(n) \oplus S(k-1) = x
$$

我们枚举 $n$ 即可得到 $40$ 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int ans;
int flag;
int l,r,k,x;

int solov(int op)
{
	if(op % 4 == 0)return op;
	if(op % 4 == 1)return 1;
	if(op % 4 == 2)return op+1;
	if(op % 4 == 3)return 0;
}

int main()
{
	cin >> T;
	while(T--)
	{
		ans = -1;
		cin >> l >> r >> k >> x;
	    
	    for(int i = l; i <= r; i++)
	    {
	    	if((solov(i) ^ solov(k-1)) == x)
	    	{
	    		ans = i;
	    		break;
			}
		}
		
		cout << ans << "\n";
	}
    return 0;
}
```

### 优化

要使 $S(n) \oplus S(k-1) = x$，即 $S(n) = x \oplus S(k-1)$。（两边同时异或 $S(k-1)$ 即可）

按照最开始的性质，通过 $x \oplus S(k-1)$ 对 $4$ 取模的值进行分类讨论即可得到满分代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int ans;
int flag;
int l,r,k,x;

int solov(int op)//快速计算
{
	if(op % 4 == 0)return op;
	if(op % 4 == 1)return 1;
	if(op % 4 == 2)return op+1;
	if(op % 4 == 3)return 0;
}

int main()
{
	cin >> T;
	while(T--)
	{
		ans = 0x3f3f3f3f;
		cin >> l >> r >> k >> x;
	    flag = solov(k-1) ^ x;
	    if(flag == 0)//针对计算函数中的if(op % 4 == 3)return 0倒推;
        {
            for(int i = l; i <= r; i++)
	    		if(i % 4 == 3)
                {
					ans = min(ans,i);
                    break;
                }
        }
		if(flag == 1)//针对if(op % 4 == 1)return 1倒推;
        {
            for(int i = l; i <= r; i++)
				if(i % 4 == 1)
                {
                    ans = min(ans,i);
                    break;
                }
        }
	    if(flag - 1 <= r && flag - 1 >= l && (flag-1)%4==2)//针对if(op % 4 == 2)return op+1倒推;
			ans = min(ans,flag-1);
	    if(flag <= r && flag >= l && flag%4==0)//针对if(op % 4 == 0)return op倒推;
			ans = min(ans,flag);
			
		if(ans == 0x3f3f3f3f)cout << -1 << "\n";
		else cout << ans << "\n";
	}
    return 0;
}
```

---

## 作者：lznxes_xh (赞：0)

从 $0$ 到 $n$ 的异或和具有周期性，可以通过以下公式快速计算：
$$
\text{xor}(n) = \begin{cases}
n & \text{if } n \equiv 0 \pmod{4} \\
1 & \text{if } n \equiv 1 \pmod{4} \\
n + 1 & \text{if } n \equiv 2 \pmod{4} \\
0 & \text{if } n \equiv 3 \pmod{4}
\end{cases}
$$
这个性质可以帮助我们快速计算任意区间的异或和。

从 $k$ 到 $n$ 的异或和可以表示为：

$$
\bigoplus_{i=k}^n i = \text{xor}(n) \oplus \text{xor}(k-1)
$$
根据上述性质，我们可以将问题转化为：

$$
\text{xor}(n) \oplus \text{xor}(k-1) = x
$$
即：

$$
\text{xor}(n) = x \oplus \text{xor}(k-1)
$$
设 $t = x \oplus \text{xor}(k-1)$，则我们需要找到 $n$ 满足：

$$
\text{xor}(n) = t
$$

根据 $t$ 的不同情况，我们可以分类讨论：

- $t=0$

  - 根据异或和的性质，$\text{xor}(n) = 0$ 当且仅当 $ n \equiv 3 \pmod{4} $。

  - 因此，我们需要在区间 $[l, r]$ 内找到满足 $n \equiv 3 \pmod{4}$ 的最小整数。

- $t=1$：

  - 根据异或和的性质，$\text{xor}(n) = 1$  当且仅当 $n \equiv 1 \pmod{4}$。
  - 因此，我们需要在区间 $[l, r]$ 内找到满足 $n \equiv 1 \pmod{4}$ 的最小整数。

- $t\equiv 0\pmod{4}$

  - 根据异或和的性质，$\text{xor}(n) = t$ 当且仅当 $n=t$ 且 。$n \equiv 0 \pmod{4}$
  - 因此，我们需要检查 $t$ 是否在区间 $[l,r]$ 内，并且满足 $n \equiv 0 \pmod{4}$。

- $ t \equiv 3 \pmod{4} $
  - 根据异或和的性质，$\text{xor}(n) = t$ 当且仅当 $n=t-1$ 且 $n \equiv 2 \pmod{4}$。
  - 因此，我们需要检查 $t-1$ 是否在区间 $[l, r]$ 内，并且满足 $t - 1 \equiv 2 \pmod{4}$。

时间复杂度：$O(T)$

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int xo0(int n) 
{
	int mod = n % 4;
	if (mod == 0) return n;
	else if (mod == 1) return 1;
	else if (mod == 2) return n + 1;
	else return 0;
}
int find(int l,int r,int ys)
{
	for (int i = l;;i++)
	{
		if (i % 4 == ys) return i;
	}
}
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) 
	{
		int l, r, k, x;
		cin >> l >> r >> k >> x;
		int xo1 = xo0(k - 1);
		int t = x ^ xo1;
		int ans = -1;
	//	cout<<t<<' ';
		if (t == 0) 
		{
		//	int r = 3;
			int st = find(l,r,3);
			if (st <= r) ans = st;
		} 
		else if (t == 1) 
		{
		//	int r = 1;
			int st = find(l,r,1);
			if (st <= r) ans = st;
		} 
		else if (t % 4 == 0) 
		{
			if (t >= l && t <= r && (t % 4 == 0)) ans = t;
		} 
		else if (t % 4 == 3) 
		{
			int now = t - 1;
			if (now >= l && now <= r && (now % 4 == 2)) ans = now;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Tyih (赞：0)

# Solution

~~本蒟蒻在赛时没有想出正解，感觉可以重开了。~~

我们先令 $f(n) = \bigoplus\limits_{i=1}^n i$ 可以通过打表发现：

$$
f(n)=
\begin{cases}
n,\quad\quad\quad n \equiv 0 \pmod 4 \\
1,\quad\quad\quad n \equiv 1 \pmod 4\\
n+1,\quad\: n \equiv 2 \pmod 4 \\
0,\quad\quad\quad n \equiv 3 \pmod 4
\end{cases}
$$

由于 $x=\bigoplus\limits_{i=k}^n i$，我们可以另 $x'=f(k-1) \bigoplus x$，此时 $x'=f(n)$，所以我们只需要根据 $x'$ 逆推出 $n$ 的值即可。

若 $x'=1$， 则 $n \equiv 1 \pmod 4$，只需找出在区间 $[l,r]$ 之间的一个数 $n$ 使 $n \equiv 1 \pmod 4$。

若 $x'=0$， 则 $n \equiv 3 \pmod 4$，只需找出在区间 $[l,r]$ 之间的一个数 $n$ 使 $n \equiv 3 \pmod 4$。

若 $x' \equiv 0 \pmod 4$， 则 $n = x'$。

由 `if(n%4==2) return n+1` 可以推出若存在 $n$ 满足条件，则 $x' \equiv 3 \pmod 4$。此时 $n=x'-1$。

其余情况无解。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r,k,x,ans;
inline int f(int n){
	if(n%4==0) return n;
	if(n%4==1) return 1;
	if(n%4==2) return n+1;
	if(n%4==3) return 0;
}
void solve(){
	cin>>l>>r>>k>>x;
	int t=f(k-1)^x;
	if(t==1){
		ans=l+1-(l%4);
		while(ans<l) ans+=4;
	}
	else if(t==0){
		ans=l+3-(l%4);
		while(ans<l) ans+=4;
	}
	else if(t%4==0) ans=t;
	else if(t%4==3) ans=t-1;
	else ans=-1;
	if(l>ans || ans>r) ans=-1;
	cout<<ans<<"\n";
	return ;
}
int main(){
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：O_N_N (赞：0)

显然的，本题的问题在于求下面这个函数的逆函数。

$
F(n) = 
\begin{cases}
n, & \text{if } n \equiv 0 \pmod{4} \\
1, & \text{if } n \equiv 1 \pmod{4} \\
n + 1, & \text{if } n \equiv 2 \pmod{4} \\
0, & \text{if } n \equiv 3 \pmod{4}
\end{cases}
$

我们先求出

$ F(n) = x⊕{F(k-1)} $

我们再手搓一个

$ F^{-1}(n) $

所以

$  F^{-1}(F(n))=n $

然后判断 $ n $ 是否存在于合法的区间中，就可以解决问题啦！

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 计算从 0 到 n 的异或和
ll xorPrefix(ll n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}
void j11C() {
    int t;
    cin >> t;
    while (t--) {
        ll l, r, k, x;
        cin >> l >> r >> k >> x;

        // 计算从 0 到 k-1 的异或和
        ll prefix_k_minus_1 = xorPrefix(k - 1);

        // 计算目标值 f(n) = x ⊕ f(k-1)
        ll target = x ^ prefix_k_minus_1;
        ll f=1;
        if (target == 1) {
            for (ll i = l; i <=r&&i<l+4 ; ++i) {
                if(xorPrefix(i)==target){
                    cout<<i<<endl;
                    f=0;
                    break;
                }
            }

        } else if (target == 0) {
            for (int i = l; i <=r&&i<l+4 ; ++i) {
                if(xorPrefix(i)==target){
                    cout<<i<<endl;
                    f=0;
                    break;
                }
            }
        } else{
            if((target-1)%4==2){
                if(target-1>=l&&target-1<=r){
                    cout<<target-1<<endl;
                    f=0;
                }
            }else if((target)%4==0){
                if(target>=l&&target<=r){
                    cout<<target<<endl;
                    f=0;
                }
            }
        }
        if(f){
            cout<<-1<<endl;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    j11C();
    return 0;
}
```

---

## 作者：InversionShadow (赞：0)

[前置知识？](https://www.luogu.com.cn/problem/P3908)

首先通过打表可以得出 $\bigoplus\limits_{i = 1} ^ n i$ 的值：

+ 当 $i \bmod 4 = 0$，答案为 $n$；

+ 当 $i \bmod 4 = 1$，答案为 $1$；

+ 当 $i \bmod 4 = 2$，答案为 $n + 1$；

+ 当 $i \bmod 4 = 3$，答案为 $0$。

观察题目，求的是 $\bigoplus\limits_{i = k} ^ n i = x$，转为前缀异或：$\bigoplus\limits_{i = 1} ^ n i$ 异或上 $\bigoplus\limits_{i = 1} ^ {k - 1} i$ 等于 $x$，变成 $\bigoplus\limits_{i = 1} ^ n i = x \bigoplus \bigoplus\limits_{i = 1} ^ {k - 1} i$，其中右式是定值，那就可以知道左式了。

从而判断 $n$ 的范围即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 100;

int t;

int solve(int x) {
  if (x % 4 == 1) {
    return 1;
  }
  if (x % 4 == 2) {
    return x + 1;
  }
  if (x % 4 == 3) {
    return 0;
  }
  return x;
}

signed main() {
  cin >> t;
  while (t--) {
    int l, r, k, x;
    cin >> l >> r >> k >> x;
    int g = solve(k - 1) ^ x;
    bool f = 1;
    if (g == 0) {
      for (int i = l; i <= r; i++) {
        if (i % 4 == 3) {
          cout << i << '\n';
          f = 0;
          break;
        }
      }
      if (f) {
        cout << "-1\n";
      } 
    } else if (g == 1) {
      for (int i = l; i <= r; i++) {
        if (i % 4 == 1) {
          cout << i << '\n';
          f = 0;
          break;
        }
      }
      if (f) {
        cout << "-1\n";
      } 
    } else if ((g - 1) % 4 == 2) {
      if (l <= g - 1 && g - 1 <= r) {
        cout << g - 1 << '\n';
      } else {
        cout << "-1\n";
      }
    } else if (g % 4 == 0) {
      if (l <= g && g <= r) {
        cout << g << '\n';
      } else {
        cout << "-1\n";
      }
    } else {
      cout << "-1\n";
    }
  }
  // solve(n) ^ solve(k - 1) = x
  return 0;
}
```

---

