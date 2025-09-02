# [ARC164A] Ternary Decomposition

## 题目描述

给定两个整数 $N,K$，判断 $N$ 能不能用 $K$ 个 $3^{n}(n\in \N)$ 之和表示。

**本题有多组测试数据。**

Translated by [lelml](/user/372622).

## 说明/提示

$1\le T \le 10^5,1 \le K \le N \le 10^{18}$

## 样例 #1

### 输入

```
4
5 3
17 2
163 79
1000000000000000000 1000000000000000000```

### 输出

```
Yes
No
Yes
Yes```

# 题解

## 作者：_5t0_0r2_ (赞：3)

# 分析：

首先，任意自然数一定能分解成若干个 $3$ 的自然数次幂的和，但不保证是 $k$ 个。

那么，我们先求出 $n$ 拆分成若干个 $3$ 的自然数次幂的和且个数最少的情况，设拆分成了 $m$ 个数。

因为根据题意，拆分出的数可以相同，同时，当 $x \geq 1$ 时，$3 ^ x = 3 \times 3 ^ {x - 1} = 3 ^ {x - 1} + 3 ^ {x - 1} + 3 ^ {x - 1}$,也就是说，任意一个 $3$ 的**正整数**次幂可以拆分成更小的 $3$ 个 $3$ 的**自然数**次幂，即增加了 $2$ 个数。

所以，要想拆分成 $k$ 个数，应满足 $2$ 个条件：

1. $k \geq m$（因为 $m$ 已经是最小能够拆分的个数了，不能比 $m$ 再小了）。

1. $(k - m) \bmod 2 = 0$（因为每次拆分多出 $2$ 个数，所以拆分出的数的个数一定是 $m + 2p$ 的形式，其中 $p$ 为自然数）。



---

## 作者：FReQuenter (赞：1)

$n<k$ 时一定无解。

首先把 $n$ 进行三进制分解，得到的数每一位上都是 $0,1$ 或 $2$。

我们令这个数的各位和为 $m$。

若 $m$ 与 $k$ 不同奇偶或者非 $0$ 项数数量比 $k$ 大，则无解。因为每拆一个这个数的高位，那么和会增多 $2$，不改变奇偶。

其它就没啥要判断的了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
  int t;
  cin>>t;
  while(t--){
    int n,k;
    cin>>n>>k;
    if(n<k) cout<<"No\n";
    else if(n==k) cout<<"Yes\n";
    else{
      int tmp=n,m=0;
      while(tmp){
        m+=tmp%3;
        tmp/=3;
      }
      if(k%2!=m%2||m>k) cout<<"No\n";
      else cout<<"Yes\n";
    }
  }
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc164_a)    
如果我没记错的话，这题应该是原题。    
## 题意   
给你 $n$ 和 $k$，问你能不能把 $n$ 分解成正好 $k$ 个 $3$ 的自然数幂之和。     
## 解法   
我们首先可以对 $n$ 进行三进制的拆分，求出 $n$ 在三进制下的数位之和，也就是最少的个数。     
我们发现，$3^x(x≥1)=3^{x-1}+3^{x-1}+3^{x-1}$，每次分解都会减少一个数，产生三个数，也就是产生两个数。     
那么，如果 $k$ 个数可以通过上文所说的分解得到，那么 $(k-m)\bmod 2=0$，$m$ 为原来的三进制数位和。我们把上面的条件都判断一下即可。    
时间复杂度 $O(t\log_3n)$，可以通过。      
[CODE](https://www.luogu.com.cn/paste/r7u65dhk)

---

## 作者：TLEWA (赞：0)

考虑对合法解的项数进行变换

由乘方的定义可以推出：

$$3^m = 3^{m-1} \times  3$$

也就是说，项数为 $K - 2x$ 且大于等于 $0$ 的构造（$x$ 为任意整数），都可以通过变换变成 $K$ 项。

你可能会问：如果原构造的所有项次数都为 $0$，那么不就无法再进行变换了吗？事实上这是不可能的，通过反证法可以证明这一点。注意到题目给出了一个条件 $K \le N$，假设原构造的所有项次数都为 $0$，则 $K - 2x = N$，得出 $K > N$ 的结论，与给出条件矛盾。所以原构造的所有项次数不可能都为 $0$。

接下来，我们来证明含有形如 $K - 2x + 1$ 项的构造无法通过变换变成 $K$ 项（反之亦然）：

一个构造的每一项都是 $3^m$ 这样的数字，也就是均为奇数，$K - 2x + 1$ 个奇数相加与 $K$ 个奇数相加的奇偶性显然不同，所以 $K - 2x + 1$ 项的构造不可能变换为 $K$ 项的构造。

由于所有项数 $\le K$ 的合法构造项数都能够被分类为 $K - 2x + 1$ 项或 $K - 2x$ 项。所以我们只需要贪心地构造出任意一个项数 $\le K$ 的数列，如果项数形如 $K - 2x$，可以通过变换变为 $K$ 项，构造出合法解，如果形如 $K - 2x + 1$，则证明无法构造出合法解。

AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
long long T,n,k,maxp;
 
int main() {
	cin >> T;
	while(T--) {
		cin >> n >> k;
		maxp=1350851717672992089; //这个东西是>=1e18 的第一个 3 的次幂
		while(maxp) {
			if(n>=maxp && k) n-=maxp,k--;
			else maxp/=3;
		}
		if(k%2==0 && n==0) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
```


---

## 作者：wnsyou (赞：0)

# [Ternary Decomposition](https://www.luogu.com.cn/problem/AT_arc164_a)

## 题意

共 $T$ 组数据，对于每组数据，给出两个整数 $n$ 和 $k$，问是否存在一个长度为 $k$ 的非负整数序列 $a$，使得 $\sum\limits_{1 \leqslant i \leqslant k} 3^{a_i} = n$，若存在，输出 `Yes`，否则输出 `No`。

### 数据范围

- $1 \leqslant T \leqslant 10^5$。
- $1 \leqslant k \leqslant n \leqslant 10^{18}$。

## 思路

整体思路类似 [CF1095C](https://codeforces.com/problemset/problem/1095/C)，把 $n$ 转为**三进制**。

首先判断一下，$n$ 最多只能分为 $n$ 个 $1$ 相加，若 $n < k$，则必然不成立(虽然题目保证了 $n \geqslant k$)。

令 $n = (\overline{x_1x_2x_3\cdots x_m})_3$，则 $a$ 的长度(设为 $t$)至少为 $\sum\limits_{1\leqslant i \leqslant m} x_i$，当 $t > k$ 时，很明显也不成立，当 $t = k$ 时成立，那么当 $t < k$ 时呢？

若消除一个 $x^i (i > 0)$，则需要用 $3$ 个 $x^{i-1}$ 来替代，会使 $t$ 加 $2$，那么剩下一种情况就推出来了，当 $k - t$ 为偶数时，成立。

### 整理一下

- 当 $n < k$ 时，不成立。
- 当 $n \geqslant k$ 时，令 $n = (\overline{x_1x_2x_3\cdots x_m})_3$，$t = \sum\limits_{1\leqslant i \leqslant m} x_i$；
  - 当 $t > k$ 时，不成立。
  - 当 $t=k$ 时，成立。
  - 当 $t < k$ 时，若 $t\equiv k\pmod{2}$，则成立；否则不成立。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int t;
long long n, k, s;

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t; t--, s = 0) {
    cin >> n >> k;
    /* if (k > n) { 题目已经保证 n >= k 了，不必要。
      cout << "No\n";
      continue;
    } */
    while (n) { // 三进制分解
      s += n % 3, n /= 3;
    }
    cout << (s <= k && s % 2 == k % 2 ? "Yes" : "No") << '\n'; // 各情况分析见上
  }
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

共 $t$ 次询问，每次给你 $n,k$，问能否将 $n$ 表示为 $3^{m_1}+3^{m_2}+\dots+3^{m_k}$，其中 $m_1,m_2,\dots,m_k$ 为正整数。

**分析**

容易发现，对于所有 $n$ 都一定能表示（指用 $m_1,m_2,\dots$），不过不一定是 $k$ 个数而已。那我们可以求出它最少和最多用多少个数表示，再看看能否累加或减少到 $k$ 个。易证表示 $n$ 的最少数的数量是它在三进制下的数位和，最多数量是 $n$，且我们会发现 $3^{m}=3^{m-1}+3^{m-1}+3^{m-1}$，因此可以通过这样替换表示法来看能否用 $k$ 个表示。

判断方式如下：假如最少数量也大于 $k$，那么可以输 `No` 了；假如我们用最多数量，并且经过若干次替换后也得不到 $k$（每次替换数的数量减少 $2$，因此只需要判断 $n-k$ 是否整除 $2$ 即可），那么也可以输 `No` 了。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
long long check(long long k)//三进制数位和
{
	long long ans=0;
	while(k)
	{
		ans+=k%3;
		k/=3;
	}
	return ans;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n,k
		cin>>n>>k;
		if(check(n)>k) cout<<"No"<<endl;//最少数量
		else
		{
			if((n-k)%2) cout<<"No"<<endl;//不能替换
			else cout<<"Yes"<<endl;
		}
	}
	return 0;
}

---

## 作者：abensyl (赞：0)

原题：[ARC164A Ternary Decomposition](https://www.luogu.com.cn/problem/AT_arc164_a)

## 思路

首先，如果 $N<k$，一定不存在解。

将一个数 $N$ 拆成 $\sum\limits_{i=1}^n 3^{m_i}$ 的形式，很容易想到三进制，但是不能直接使用三进制各数位和，加入这个三进制数 $N$ 可以表示为 $\sum\limits_{i=0}^{\lceil log_3 N\rceil}k_i\times 3^{p_i}$，那么很容易找到一种项数为 $\sum\limits_{i=0}^{\lceil log_3 N\rceil} k_i$ 的拆分方式。

如果我们直接使用三进制个数为的和，也就是拆出多项式的项数与 $k$ 进行大小比较，显然答案是错误的，甚至连样例都过不了，但是，可以保证的是，如果即便是这种拆分方式拆出的项数都大于 $k$，该数一定无法进行项数更好的拆分，输出 `No`，结束程序。但是项数小于 $k$，如果那么我们怎么办呢？

试考虑对于 $3^i(i\geq 1)$，我们可以将其转化为 $3\times 3^{i-1}$，那么我们就能够增大我们拆出来的项数了，每次将 $3^i$ 拆成 $3^{i-1}+3^{i-1}+3^{i-1}$，我们可以增加三项，所以说我们可以对原项数与 $k$ 的差进行特判。

然后我们就可以写出代码了：

[代码 + 我的 AC 记录。](https://atcoder.jp/contests/arc164/submissions/43417952)

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

多测。每次给定 $n,k(1\le k\le n\le 10^{18})$，问能否完成如下拆分 $n=3^{m_1}+3^{m_2}+\cdots+3^{m_k}$，其中数列 $m$ 的元素均为非负整数。

## 思路

我们可以先做项数最小的拆分并计算项数 $cnt$，由于我们只需要知道项数而无需具体的指数，因此直接用 ``while`` 循环即可简易完成。对于项数最小的拆分如果我们要扩大项数一定是取一个 $i$，然后进一步拆分 $3^{m_i}=3^{m_i-1}+3^{m_i-1}+3^{m_i-1}$，总共会增加两项，因此只有当 $k-cnt$ 为偶数时能够分解。

注：由于 $k\le n$，因此无需特判。

## 代码

```cpp
cin>>t;
while(t--){
    ll cnt=0;
    cin>>n>>k;
    while(n>0){
	while(n%3)cnt++,n--;
	n/=3;
    }
    if(k>=cnt&&(k-cnt)%2==0)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}
```


---

## 作者：hellolin (赞：0)

## AtCoder Regular Contest 164 - A - Ternary Decomposition

[洛谷题面](https://www.luogu.com.cn/problem/AT_arc164_a) | [AtCoder 题面](https://atcoder.jp/contests/arc164/tasks/arc164_a) | [前往 blog.hellolin.cf 获取更好的阅读体验](https://blog.hellolin.cf/articles/c00e26fc.html)

题目大意是给定正整数 $N$ 和 $K$，问是否存在一个非负整数序列 $(m_1,\ m_2,\ \dots,\ m_K)$ 满足 $N=3^{m_1}+3^{m_2}+\dots +3^{m_K}$。

嘶，~~好像在哪见过~~。

考虑将 $N$ 表示为三进制形式，比如 $17$ 的三进制形式是 $(122)_3$，所以

$$17=1\times 3^2+2\times 3^1+2\times 3^0$$

也就是

$$17=3^2+3^1+3^1+3^0+3^0$$

所以说，我们只要将 $N$ 的三进制形式的所有位相加（令其为 $S$），当 $S> K$ 时输出 `No`，当 $S=K$ 时输出 `Yes`。

```cpp
do {
    s += n%3;
    n /= 3;
} while(n); // 计算 S

if(s>k) {
    ans = "No";
} else if (s==k) {
    ans = "Yes";
}
```

但是 $S< K$ 的时候不能直接判断输出什么，还是例如 $N=17$，此时 $S=5$ 对吧，那如果 $K=6$，输出什么呢？$K=7$ 呢？

答案是 `No` 和 `Yes`。

至于为什么，我们还是来看三进制形式：$(122)_3$。

题目中并没有限制序列中某一个数最多出现几次，所以最高位的那个 $1$ 可以退 $3$ 给下一位，就成了 $(52)_3$（当然三进制下不能这么写）。

发现了么，当高位退了一个 $1$ 给低位，$S$ 就会减一再加三。所以我们可以推断，当 $S\le K$ 并且 $K-S\equiv 0 \pmod 2$，输出 `Yes`，否则是 `No`。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll t, n, k, s;
string ans;
void solve() {
    cin >> t;
    while(t--) {
        cin >> n >> k;
        s = 0; // 多测记得初始化！
        do {
            s += n%3;
            n /= 3;
        } while(n);

        if(s>k) {
            ans = "No";
        } else {
            ans = ((k-s)%2) ? "No" : "Yes";
        }

        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```


---

