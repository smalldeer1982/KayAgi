# Salyg1n and Array (simple version)

## 题目描述

This is the simple version of the problem. The only difference between the versions is the limit on the number of queries. In this version, you can make no more than 100 queries. You can make hacks only if both versions of the problem are solved.

This is an interactive problem!

salyg1n has given you a positive integer $ k $ and wants to play a game with you. He has chosen an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ). You must print $ a_1 \oplus a_2 \oplus \ldots \oplus a_n $ , where $ \oplus $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation. You can make queries of the following type:

- $ ? $ $ i $ : in response to this query, you will receive $ a_i \oplus a_{i + 1} \oplus \ldots \oplus a_{i + k - 1} $ . Also, after this query, the subarray $ a_i, a_{i + 1}, \ldots, a_{i + k - 1} $ will be reversed, i.e., the chosen array $ a $ will become: $ a_1, a_2, \ldots a_{i - 1}, a_{i + k - 1}, a_{i + k - 2}, \ldots, a_{i + 1}, a_i, a_{i + k}, \ldots, a_n $ .

You can make no more than $ 100 $ queries to answer the problem.

## 说明/提示

In the first test case, the jury has chosen the array $ a $ $ = $ $ [4, 2, 5, 1] $

In the second test case, the jury has chosen the array $ a $ $ = $ $ [5, 7, 1, 3, 3, 7] $

## 样例 #1

### 输入

```
2
4 2

6

4

6 6

4```

### 输出

```
? 1

? 3

! 2

? 1

! 4```

# 题解

## 作者：sunkuangzheng (赞：6)

**【题目大意】**

交互题，交互库隐藏长度为 $n$ 的序列 $a$，你每次可以询问长度为 $k$ 的区间 $[l,l+k-1]$ 的异或值（$\oplus_{i=l}^{l+k-1}a_i$）并同时将这个区间翻转。$1 \le k \le n \le k^2 \le 2500$，你最多可以进行 $100$ 次询问。**保证 $n,k$ 均为偶数**。

**【题目分析】**

首先你要能计算出这题的数据范围：$1 \le k \le 50$。我们先考虑 $n \bmod k = 0$ 的情况，显然我们可以从 $1$ 开始问过去，只需要 $\dfrac{n}{k}$ 次询问就可以得到答案。由数据范围，$\dfrac{n}{k} \le k$，所以最多需要 $50$ 次询问。

类似的，如果 $n \bmod k \ne 0$，我们也可以先顺序问过前面的区间，最后留下一个长度在 $2 \sim 2k-2$ 的区间。下面的讨论都针对这个区间。为了表述直观，使用 $1,2,3$ 表示 $a_1,a_2,a_3$ 等。

先用一个例子来看，假设 $n = 10,k = 6$，我们的询问如下：

蓝色表示询问过 $1$ 次的数字，红色表示 $2$ 次，绿色表示 $3$ 次。

$$[\color{blue}{1,2,3,4,5,6}\color{black},7,8,9,10](\text{询问区间}\,[1,6])$$

$$[\color{blue}{6,5,}\color{red}{4,3,2,1,}\color{blue}7,8,\color{black}9,10](\text{询问区间}\,[3,8])$$

$$[\color{blue}{6,5,8,7,}\color{green}{1,2,3,4,}\color{blue}{9,10}\color{black}](\text{询问区间}\,[5,10])$$

你发现所有元素都被异或了奇数次，所以你将三次询问结果异或起来就是要求的值。

研究一下刚才我们的询问过程，核心在于第二次询问。记 $m = \dfrac{n \bmod k}{2} + 1$，我们询问以 $m + 1$ 为左端点的区间。这次操作会使得我们将区间 $[m+1,k]$ 被重复询问，即染上红色。与此同时，这段区间会被**恰好翻转到位置 $[n-k+1,n-m+1]$**。然后我们再询问 $[n-k+1,n]$ 的时候，这部分一定由询问过 $2$ 次的红色部分和未被询问过的黑色部分组成。经过这次操作，所有数字都会异或奇数次。

分析我们的询问次数。前半段最多花费 $\lfloor \dfrac{n}{k} \rfloor$ 次询问，后半段需要 $2$ 次询问，所以最多不会超过 $51$ 次询问，可以同时通过 E1 和 E2。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,x,i,pi;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> k;int res = 0;
        if(n == k){
            cout << "? 1" << endl,cin >> res;
            cout << "! " << res << endl;continue;
        }
        for(i = 1;i <= n - k + 1;i += k) cout << "? " << i << endl,cin >> x,res ^= x;
        if(n % k == 0){cout << "! " << res << endl;continue;}
        cout << "? " << i - k + (n % k) / 2 << endl,cin >> x,res ^= x;
        cout << "? " << n - k + 1 << endl,cin >> x,res ^= x;
        cout << "! " << res << endl;
    }
}
```


---

## 作者：mayike (赞：2)

~~简单题~~

### [题目传送门](https://codeforces.com/problemset/problem/1867/E1)

## 思路

首先，必须知道 $x \operatorname{xor} x = 0,0 \operatorname{xor} x = x$，$x$ 规定为自然数。那么这题就简单了。

作图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ji08z9t9.png)

先问 $1$ 区间，再问了 $2$ 区间，则红色区域的异或值被抵消成 $0$，此时查询后要翻转区间，则区间 $2$ 转成区间 $3$，再询问区间 $4$，那么红色区域的异或值就回来了，此时的异或值为区间 $1$，区间 $2$ 的白色区域以及区间 $4$ 的白色区域的异或值。

因为区间长度为 $k$，所以这个操作等价于在假设询问过区间 $1$ 的情况下，后两次连续询问的长度是相同且在 $1 \le x \le k$ 里随便拟定长度的。

那么总次数至多为 $\frac{n}{k}+2 \le 52$ 满足条件，因为 $n,k$ 都是偶数，那么我们对 $a = n \bmod k$，这一段进行两次连续且长度相同的询问即可。

代码也比较短。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int T,n,k,cnt,ps,ans;
	cin>>T;
	while(T--){
		cin>>n>>k;
	    cnt=ps=ans=0;
		int sum=(n-k)/2,x,js;
		cnt=sum/k,ps=sum%k;
		cout<<"? "<<1<<endl;
		cin>>x,ans^=x,js=k+1;
		if(ps!=0){
			cout<<"? "<<js-(k-ps)<<endl;
			cin>>x,ans^=x,js=js+ps;
			cout<<"? "<<js-(k-ps)<<endl;
			cin>>x,ans^=x,js=js+ps;
		}for(int i=1;i<=cnt*2;i++){
			cout<<"? "<<js<<endl;
			cin>>x,ans^=x,js+=k;
		}cout<<"! "<<ans<<endl;
	}
}
```

---

## 作者：One_JuRuo (赞：2)

## 思路

首先考虑，$n$ 是 $k$ 的倍数的情况，直接枚举询问所有每一段就好，然后输出每一段的异或和的异或和。

![](https://cdn.luogu.com.cn/upload/image_hosting/1i9ukfhn.png)

如上图，每次询问都没有重叠部分，颠转互不干扰。

那么，$n$ 不是 $k$ 的倍数的情况呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/v8vf3blk.png)

可以看到，与第一种情况的区别就是末尾多了一小截，那么我们需要考虑如何计算这一小截的异或和。

很容易想到，提前在前面计算这个长度的异或和，后续就可以和第一种情况一样了。

可以发现，解题的关键就是查询后会颠转这个特殊性质，见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s7b8rh0i.png)

因为异或的性质，自己异或自己会变成 $0$，所以同一段的异或两次就会变成 $0$。使用这个性质可以发现，如果两个询问区间重叠，那么因为颠转，获得的异或和会转移到一起。

那么我们可以考虑先构造出前面一截是余数长度的区间的异或何，后续就是第一种情况了。

因为每次取得区间长度都是固定的，所以两段红色的区间长度也一定一样，因为两段长度和是余数，所以一段我们就取余数的一半。

因为 $n$ 和 $k$ 在题目中都给定了是正偶数，所以不用担心余数是奇数的情况。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,sum,a;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k,sum=0;
		if(n%k)
		{
			cout<<"? 1"<<endl;
			cin>>a,sum^=a;
			cout<<"? "<<1+(n%k)/2<<endl;
			cin>>a,sum^=a;
		}
		for(int i=(n%k)+1;i<=n;i+=k) cout<<"? "<<i<<endl,cin>>a,sum^=a;
		cout<<"! "<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

交互题。给出一个长度为 $n$ 的保密序列 $a$。

给定一个整数 $k$，你可以向交互库询问不超过 $100$ 次，每次给出 `? x`，交互库会告诉你 $\operatorname{xor}_{k=x}^{x+k-1} a_k$，然后翻转区间 $[x,x+k-1]$。

询问完成后，输出 `! x`，$x$ 表示整个序列的异或和。

$T$ 多组数据。

$1\leq T \leq 10^3,1 \leq k \leq n \leq k^2 \leq 2500,k\equiv n\equiv 0\pmod{2}$

## 思路

萌新第一道交互题。

首先不妨将序列 $a$ 按照块长为 $k$ 分块，则最后会剩下一个散块（可能长度为 $0$）。

我们不妨考虑一个特殊情况，对于 $n\bmod k$ 的情况是平凡的。每个块都询问一次即可。

然后考虑一般的情况，首先可以先搞定 $[1,n-(n\bmod k)]$ 的答案。然后考虑最后的散块怎么求。

由于询问 $100$ 次，考虑散块可能需要 $k$ 次询问，于是自然想到对于散块中的每一个元素都询问一次才行。

考虑枚举散块的每一个元素，询问以它结尾的区间，以此类推。

然后由于区间会翻转，所以每一次都会有一个固定的公共部分，异或起来后由于 $k,n$ 是偶数所以公共部分会恰好抵消。所以这个方法是正确的。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int T,n,k;

inline void query(int pos, int &v){
	assert(pos >= 1 && pos <= (n - k + 1));
	cout<<"? "<<pos<<endl;
	cin>>v;
}

void solve(){
	cin>>n>>k;int ret = 0;
	for(int i=1,ans;i<=(n - k + 1);i+=k){
		query(i, ans);
		ret ^= ans;
	}
	if(n % k){
		for(int i=(n - (n % k) + 1),ans;i<=n;i++){
			query(i - k + 1, ans);
			ret ^= ans;
		}
	}
	cout<<"! "<<ret<<endl;
}

signed main(){
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：233L (赞：1)

首先 $k \mid n$ 是好做的。对于 $k \nmid n$，可以先把前面的整段直接询问，后面的 $m(k<m<2k,2 \mid m)$ 个数再单独做。

考虑相邻询问的影响。假设先问 $[1,k]$，再问 $[2,k+1]$，我们记 $A= \oplus_{i=1}^{k-1}a_i, B=a_k,C=a_{k+1}$，那么第一次的结果是 $A \oplus B$，第二次的结果是 $A \oplus C$，两次异或起来就是 $B \oplus C$，且此时序列从 $ABC$ 变成了 $BCA$，相当于 $A$ 往右平移了 $2$ 格。于是可以继续往下迭代，最后 $A$ 会往右平移 $\frac{n-k}{2}$ 格，$A$ 的右侧还有一个元素，再询问一次，恰好就是所有元素的异或和。这样的询问次数是 $\frac{n}{k}+k$，因为 $n^2 \le k$，所以 $\frac{n}{k} \le k \le 50$，总次数就在 $100$ 以内，可以过 easy version。

https://codeforces.com/contest/1867/submission/222969045

---

## 作者：Daniel_yao (赞：0)

## Problem
交互题。交互库有一个长度为 $n$ 的数列 $a$，求其所有元素的异或和，每次你可以选择一个 $i$，询问 $[i,i+k-1]$ 中的异或和，并将其翻转。询问不能超过 $100$ 次。**保证 $n$ 与 $k$ 均为偶数**。

$1 \le k \le n \le k^2 \le 2500$。
## Solve
当 $n\bmod k=0$ 时，直接分成 $\frac{n}{k}$ 然后区间覆盖询问就行了。

当 $n \bmod k\not=0$ 时，$[1,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 直接区间覆盖询问即可，对于 $[k\left\lfloor \dfrac{n}{k} \right\rfloor+1,n]$，选择 $[k\left\lfloor \dfrac{n}{k} \right\rfloor-k+2,n-k+1]$ 的所有 $i$ 并且询问即可。

证明：原数组记为 $a_i$，询问 $k\left\lfloor \dfrac{n}{k} \right\rfloor-k+2$ 时，$k\left\lfloor \dfrac{n}{k} \right\rfloor+1$ 会被计算进去，而 $[k\left\lfloor \dfrac{n}{k} \right\rfloor-k+2,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 总共会被计算两次，即两次异或操作，抵消。以此类推，最后，$[k\left\lfloor \dfrac{n}{k} \right\rfloor+1,n]$ 的所有数将会被计算一次。而 $[k\left\lfloor \dfrac{n}{k} \right\rfloor-k+2,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 将会被计算 $(n \bmod k) + 1$ 次，而 $n \bmod k$ 为偶数，则 $(n \bmod k) + 1$ 为奇数。则原数列每个数都可以不重不漏的计算一次。

区间覆盖询问时，操作数为 $\left\lfloor \dfrac{n}{k} \right\rfloor$，题目数据范围给出 $1 \le k \le n \le k^2 \le 2500$，所以 $\left\lfloor \dfrac{n}{k} \right\rfloor \le k \le n \le 50$，所以询问数最多不会超过 $50$ 次。而 $(n \bmod k) + 1 = n-\left\lfloor \dfrac{n}{k} \right\rfloor+1\le 50$，所以总询问数不会超过 $100$ 次，可以通过本题。

时间复杂度 $O(Tn)$。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

int n, T, k, res;

int ask(int i) {
  cout << "? " << i << '\n';
  fflush(stdout);
  int x; cin >> x;
  return x;
}

void solve() {
  res = 0; 
  cin >> n >> k;
  int i;
  for (i = 1; i + k - 1 <= n; i += k) {
    res ^= ask(i);
  } 
  if(n % k == 0) {
    cout << "! " << res << '\n';
    fflush(stdout);
  } else {
    res ^= ask(i - k + (n % k) / 2);
    res ^= ask(n - k + 1);
    cout << "! " << res << '\n';
    fflush(stdout);
  }
  return ;
}

signed main() {
  cin >> T;
  while(T--) {
    solve(); 
  }
  return 0;
}
```

---

