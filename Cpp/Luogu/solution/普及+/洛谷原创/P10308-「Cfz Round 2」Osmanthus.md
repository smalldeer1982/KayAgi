# 「Cfz Round 2」Osmanthus

## 题目描述

给定一个长度为 $n$ 的序列 $a$。

我们定义一次操作为，**同时**将序列 $a$ 中的**每个**元素 $a_i$ 替换为 $\bigoplus\limits_{j=1}^i a_j$（即 $a_1$ 至 $a_i$ 的异或和），其中 $\bigoplus$ 表示**按位异或**，即 C++ 中的 `^`。

现有 $q$ 次有序的修改，每次修改会给定两个整数 $x_i,p_i$，表示将 $a_{x_i}$ 的值修改为 $p_i$。**修改之间并不独立，每次修改会对后续的修改产生影响**。

你需要在每次修改后，找到**最小**的正整数 $t$，满足进行 $t$ 次操作后的序列 $a$ 与操作前的序列 $a$ 相同。可以证明一定存在满足要求的正整数 $t$。

由于答案可能很大，所以你只需要输出答案对 $(10^9+7)$ 取模的结果。

## 说明/提示

#### 「样例解释 #1」

第 $1$ 次修改后的序列 $a$ 为 $\{3,2,0\}$，此时进行 $1$ 次操作后的序列 $a$ 为 $\{3,1,1\}$，进行 $2$ 次操作后的序列 $a$ 为 $\{3,2,3\}$，进行 $3$ 次操作后的序列 $a$ 为 $\{3,1,2\}$，进行 $4$ 次操作后的序列 $a$ 为 $\{3,2,0\}$，所以最小的满足要求的正整数 $t$ 为 $4$。

#### 「数据范围」

对于所有数据，$1 \le n,q \le 3\times10^5$，$0 \le a_i,p_i \le 10^9$，$1 \le x_i \le n$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3 3
3 1 0
2 2
1 0
2 0```

### 输出

```
4
2
1```

# 题解

## 作者：Shadow_T (赞：10)

### 题目大意

一开始有一个序列 $a$，有 $q$ 次修改，每次可以修改一个值。对于每次修改后你需要输出此时的 $a$ 进行以下操作若干次的循环节最小长度：

- 将每个元素 $a_i$ 替换为 $\bigoplus\limits_{j=1}^ia_j$。

### 题目分析

首先，我们发现，对于第 $i$ 个元素，它会把前面的元素的组合都出现一遍，那么 $a_i$ 肯定 $2^{\lceil \log_2 i \rceil}$ 循环一次。对于长度为 $n$ 的序列，循环节就是所有 $a_i$ 循环节的最小公倍数，由于都是 $2$ 的整数次方，所以为 $2^{\lceil \log_2 n \rceil}$。

但是很明显，有一段是特殊的，即 $a$ 的前导 $0$，不管迭代其次也不会改变自身，不会影响后面的东西。

然后我们要维护动态前导 $0$，很多人暴力维护赛时过了，这里已经 hack 掉了（第 $7$ 个点）。[This](https://www.luogu.com.cn/discuss/802922)。

其实这个动态前导 $0$ 类似一个动态 $\operatorname{mex}$，可以用 set 维护。详见 [Link](https://www.luogu.com.cn/article/26co4ybo) 的 set 部分。

时间复杂度 $\mathcal{O}(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int a[maxn];
int main()
{
	int n,q;
	cin>>n>>q;
	set<int> s;
	for(int i=1;i<=n+1;i++)
	s.insert(i);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==0) s.erase(s.lower_bound(i));
	}
	while(q--)
	{
		int x,z;
		scanf("%d%d",&x,&z);
		if(a[x]!=0&&z==0) s.erase(s.lower_bound(x));
		else
		{
			if(a[x]==0&&z!=0)
			s.insert(x);
		}
		a[x]=z;
		int y=n-*s.begin()+1;
		int ans=1;
		while(ans<y) ans*=2;
		cout<<ans<<"\n";
	}
}
```

---

## 作者：shinzanmono (赞：9)

我们将 $t$ 称为循环节。**第 $i$ 次操作与第 $i+t$ 次操作的得到的答案相同**。

当 $a_i\neq 0$ 时，我们通过下面的方法证明：

我们知道，当 $n=1$ 时，$t=1$。

当 $n=2$ 时，我们将原数组分为两个长度为 $1$ 的部分，我们知道两个部分的循环节都是 $1$。但是在前面部分的操作中，后面的部分会异或上前面的部分，所以我们需要额外的次数来抵消掉这些操作。所以 $t=2$。

当 $n=4$ 时，将原数组分为两个长度为 $2$ 的部分，两个部分的循环节都为 $2$，根据上面的证明，我们需要两次操作来抵消。故 $t=4$。

我们可以通过这种方法对于 $n=2^k(k\in \mathbb{N_+})$ 的情况得到普遍结论。

我们可以用同样的方法证明 $n\neq2^k(k\in\mathbb{N_+})$ 的情况。

然后我们可知，当 $a_i\neq0$ 时，$t=2^{\lceil\log_2n\rceil}$。

我们考虑 $a_i=0$ 的情况，我们可以发现之前的证明是基于抵消贡献的，当 $a_i=0$ 时，数组并不需要被抵消，所以我们可以将前缀 $0$ 删掉，这样并不影响答案。

于是这道题就解出来了。

---

## 作者：Big_Dinosaur (赞：2)

由于任何数异或 $0$ 都得原数，前缀 $0$ 不需也不能考虑，一直是 $0$ 也不会对后面的数产生贡献；而中间的 $0$ 与后缀 $0$ 异或后可能就不是 $0$ 了，需考虑在内。

再考虑非 $0$ 串答案。设长度为 $n$ 的串答案为 $f(n)$：

- $n=1$：答案为 $1$，永远不会变。
- $n=2^m$：分为两段长为 $\dfrac n 2$ 的串，第一段过 $f(\dfrac n 2)$ 次回原样，但使后一段都异或了不同数，需要再来 $f(\dfrac n 2)$ 次消灭。答案为 $2\times f(\dfrac n 2)$。
- $2\mid n$：与上文类似。答案也为 $2\times f(\dfrac n 2)$。
- $n$ 为奇数：难办。但对于小数据打表可得以下数据：$f(2)=2,f(3)=4,f(4)=4,f(5)=8,f(6)=8,f(7)=8$。从中发现结论：$f(n)=f(\lceil\dfrac n 2\rceil)\times 2$。

整理得 $f(n)=2^{\lfloor\log_2n\rfloor}$。

前缀 $0$ 如何搞？

线段树直接维护！

若左子树对应数组位置全为 $0$，该子树对应数组位置前缀 $0$ 长度为左子树对应数组位置长度加上右子树对应数组位置的前缀 $0$ 长度，否则为左子树对应数组位置的前缀 $0$ 长度。

答案为根节点维护的答案。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
namespace IO{
  inline int r(){
    int z=1,y=0;char t=getchar();while(t<'0'||t>'9'){if(t=='-')z=-1;t=getchar();}
    while(t<='9'&&t>='0'){y=(y<<1)+(y<<3)+(t^48);t=getchar();}return z*y;
  }
  inline void w_(int x){if(x<0){x=-x;putchar('-');}if(x==0)return;w_(x/10);putchar(x%10+48);}
  inline void wln(int x){if(x==0)putchar('0');else w_(x);putchar('\n');}
  inline void ww(int x){if(x==0)putchar('0');else w_(x);putchar(' ');}
  inline void w(int x){if(x==0)putchar('0');else w_(x);}
}
using namespace IO;
namespace D1n0{
  int n,m,a[1919810];
  struct sgt{int l,r,s0,sz;}s[1919810];
  #define ls (id<<1)
  #define rs ((id<<1)|1)
  #define mid (l+r>>1)
  const int p=1e9+7;
  inline void pushup(int id){
    if(s[ls].s0==s[ls].sz)s[id].s0=s[ls].sz+s[rs].s0;
    else s[id].s0=s[ls].s0;
  }
  inline void build(int l,int r,int id){
    s[id].l=l;s[id].r=r;s[id].sz=r-l+1;
    if(l==r){s[id].s0=(a[l]==0);return;}
    build(l,mid,ls);build(mid+1,r,rs);
    pushup(id);
  }
  inline void upd(int id,int f,int x){
    int l=s[id].l,r=s[id].r;
    if(l==r){s[id].s0=(x==0);return;}
    if(f<=mid)upd(ls,f,x);
    else upd(rs,f,x);
    pushup(id);
  }
  inline int qpow(int x,int y){
    int Ans=1;
    while(y){
      if(y&1)Ans=Ans*x%p;
      x=x*x%p;
      y>>=1;
    }
    return Ans;
  }
  inline int log2n(int n){
    int x=1;
    for(ri i=0;i<=100;++i){
      if(x>=n)return i;
      x*=2;
    }
  }
  inline void _(){
    n=r(),m=r();
    for(ri i=1;i<=n;++i)a[i]=r();
    build(1,n,1);
    while(m--){
      int x=r(),p=r();
      upd(1,x,p);
      int cnt=n-s[1].s0;
      wln(qpow(2,log2n(cnt)));
    }
  }
}
signed main(){D1n0::_();}
```

---

## 作者：hgckythgcfhk (赞：2)

说句闲话，很不理解这题为什么让取模，也许只是为了误导吧。

看到异或很自然的想到拆位，这是因为 $01$ 序列比整数序列多了很多性质，比较好处理，看到周期，一般不是把每部分的周期相乘就是取 $\operatorname{lcm}$，显然本题是取 $\operatorname{lcm}$，因为每一位互不影响。然后就不动脑子的写个暴力试试 $01$ 序列的情况。

```cpp
Bool(a,N),b;unsigned n;
inline bitset<N>calc(Bool(c,N)){for(int i=2;i<=n;++i)c[i]=c[i-1]^c[i];return c;}
void debug(Bool(c,N)){for(int i=1;i<=n;++i)cout<<c[i];cout<<'\n';}
signed main(){open;int t;cin>>t>>n;
	for(int i=1;i<=t;++i){cout<<"Task "<<i<<" :\n";
		string s;cin>>s;for(int i=0;i<n;++i)a[i+1]=s[i]&1;
		b=calc(a);int id=0;cout<<"The start station : ",debug(a);
		while(b!=a)cout<<"The "<<++id<<"th time : ",debug(b),b=calc(b);
		cout<<"\n--------\n";
	}
}
```
为了方便，我顺手写了一个生成数据的程序。
```cpp
string s[N];
signed main(){open;int t,n;cin>>t>>n;cout<<t+t<<' '<<n+1<<'\n';
	for(int i=1;i<=t;++i)cin>>s[i];
	for(int i=1;i<=t;++i)cout<<"0"<<s[i]<<'\n';
	for(int i=1;i<=t;++i)cout<<"1"<<s[i]<<'\n';
}
```
发现把 $01$ 序列当作二进制转整数后，周期是比小于这个整数的 $\log$ 最的 $2$ 的幂，这个证明比较复杂，但感性理解一下也比较容易想明白，观察程序输出的结果就可以了。

也就是说，我们现在得到了一个做法，对于每一位组成的二进制数的 $\log$ 相当于最高位 $1$ 的位置，这相当于求 $n-\text{前缀 0 的个数}+1$ 也就是加 $1$，记这个数为 $a$，$2^a$ 就是这一位的答案，由于只有 $2$ 这一个质因子，不需要额外写一个求 $\operatorname{lcm}$ 的函数，直接取最大值即可，由于涉及到分类讨论，为了避免处理这个条件且减少码量，我们可以预处理。

具体看程序，为防止火车头导致被打回，省略了很多宏定义，但不影响阅读。
```cpp
unsigned b[N],c[N];Bool(a[32],N);set<unsigned>d[32];
signed main(){open;int n,q;cin>>n>>q;sca(b);
	for(int i=1,j=1;i<=n;++i)c[i]=j,i==j?j<<=1:0;
	for(int i=31;~i;--i)for(int j=1;j<=n;++j)a[i][j]=(bool)(b[j]&(1<<i));
	for(int i=0;i<32;++i)for(int j=1;j<=n;++j)if(a[i][j])d[i].emplace(n-j+1);
	while(q--){int e,f;cin>>e>>f;
		for(int i=31;~i;--i)if((b[e]&(1<<i))^(f&(1<<i))){
			if(b[e]&(1<<i))d[i].erase(d[i].find(n-e+1));
			else d[i].emplace(n-e+1);}b[e]=f;int ans=1;
		for(int i=0;i<32;++i)if(d[i].size())ans=max(ans,*d[i].rbegin());
		cout<<c[ans]<<'\n';
	}
}
```

---

## 作者：operator_ (赞：2)

# P10308 「Cfz Round 2」Osmanthus

[题目传送门](https://www.luogu.com.cn/problem/P10308)

## 题解

论如何把这道题做出 C >> E 的感觉。

结论不说了，这篇题解主要讲怎么不打表不观察直接推导出这个结论。

不妨把操作倒序，那么就变成不断差分。我们独立考虑初始位置 $p$，值为 $a_p$ 的数，经过 $x$ 次操作，会对位置 $i$ 产生怎样的贡献。发现这个不断差分的过程很像组合数，进一步推导，发现这个贡献就等于 $(\binom{x}{i-p}\bmod 2)\times a_p$，其中要求 $p\le i\le p+x$。

有一个经典结论：$\binom{n}{m}\bmod 2=1\Leftrightarrow n\operatorname{and} m=m$（$\operatorname{and}$ 是位运算与），所以经过 $x$ 次操作后的 $a'_i=\bigoplus\limits_{p=\max(i-x,1)}^ia_p[x\operatorname{and}(i-p)=(i-p)]=\bigoplus\limits_{p=0}^{\min(x,i-1)}a_{i-p}[x\operatorname{and}p=p]$。

由于最终序列与原序列相同，所以 $\forall 1\le i\le n$，都应当有 $\bigoplus\limits_{p=1}^{\min(x,i-1)}a_{i-p}[x\operatorname{and}p=p]=0$，所以所有 $2^k>n$ 都是合法的解，而更小的答案一定是其约数，所以所有合法解都是 $2$ 的幂。

当 $x$ 是 $2$ 的幂时，满足 $x\operatorname{and}p=p$ 的 $p$ 只有 $p=x$ 一个，换言之，此时有 $\forall 1\le i\le n-x,a_i=0$，所以结论就出来了：$x=2^{\lceil\log_2(n-前缀0的个数)\rceil}$。用 set 维护一下即可。

于是你以一种极其小丑的方式通过了本题。

---

## 作者：szh_AK_all (赞：2)

### 分析
当 $a_i\ne0$ 时，循环节的长度 $t$ 与 $2$ 的整数次幂有关。这个规律在理性上官方题解已经证明，在感性上可以用~~打表~~的方法。

那么当 $a_i=0$ 时，显然，如果 $0$ 只出现在 $a$ 数组的中间或结尾，那么对答案没有影响；如果 $0$ 出现在了 $a$ 数组的开头，那么这个 $0$ 对于 $a$ 数组来说是无关紧要的，因为任何数异或 $0$ 都的它本身。

所以，我们可以在每次询问时，求出 $a$ 数组的前缀 $0$ 的个数。那么如何求呢，很容易得出一个暴力的方法。
```cpp
int zero = 0;//代表0的个数
while (a[zero + 1] == 0 && zero + 1 <= n)
	zero++;
```
用这样的方法求明显是超时的，那么可以进行优化。

由于每次修改只修改了一个数，但每次都要重新计算一遍 $0$ 的个数，所以浪费了很多时间。不妨用一个变量 $la$ 记录修改前 $a$ 数组的前缀 $0$ 的数量，再看看修改操作会对 $la$ 产生什么影响。

显然，当每次修改的 $a_{x_i}$ 与 $p_i$ 同为 $0$ 或同不为  $0$ 时，对 $la$ 不会产生影响；反之，分为两种情况。

一：$a_{x_i}=0,p_i\ne0$，若 $x_i$ 不在 $la$ 的范围内，则不会有影响；否则，前缀 $0$ 会在 $x_i$ 这个位置断开，此时 $zero=x_i-1$。

二：$a_{x_i}\ne0,p_i=0$，若 $x_i$ 远远超过了 $la$ 的范围，那么也不会有影响。因为想要让 $la$ 增加，只能在 $la+1$ 这个位置接上一个 $0$，所以当 $x_i=la+1$ 时，$zero$ 应从 $la+1$ 开始计算，用暴力的方法往后不断枚举，直到它对应的位置不为 $0$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005], b[300005];

int main() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int la = 0;
	while (a[la + 1] == 0 && la + 1 <= n)
		la++;
	while (q--) {
		int x, p;
		cin >> x >> p;
		int zero = la;
		if (a[x] != 0 && p == 0) {
			if (x == la + 1) {
				zero = la + 1;
				while (a[zero + 1] == 0 && zero + 1 <= n)
					zero++;
			}
		} else if (a[x] == 0 && p != 0) {
			if (x <= la)
				zero = x - 1;
		}
		la = zero;
		a[x] = p;
		if (n <= zero)
			cout << 1;
		else {
			int kk = n;
			kk -= zero;
			int ans = 0;
			for (int j = 1;; j *= 2) {
				if (j == 1)
					ans++;
				else
					ans += j / 2;
				if (kk <= ans) {
					cout << j;
					break;
				}
			}
		}
		cout << endl;
	}
}
```
[赛时记录](https://www.luogu.com.cn/record/154262589)。

上述方法归根结底还是暴力的方法，这种方法可以通过可能是因为~~数据过水~~。

不过也可以用树状数组维护前缀和，而前缀 $0$ 的个数即为最后一个前缀和为 $0$ 的位置的下标，这个可以用二分实现。

### 附上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[300005], b[300005];
int c[300005];
int n;

void add(int x, int y) {
	for (; x <= n; x += x & (-x))
		c[x] += y;
}

int ask(int x) {
	int ans = 0;
	for (; x; x -= x & (-x))
		ans += c[x];
	return ans;
}

signed main() {
	int q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		add(i, a[i]);
	}
	while (q--) {
		int x, p;
		cin >> x >> p;
		add(x, p - a[x]);
		a[x] = p;
		int l = 1, r = n, zero = 0;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (ask(mid) == 0) {
				l = mid + 1;
				zero = mid;
			} else
				r = mid - 1;
		}
		if (n <= zero)
			cout << 1;
		else {
			int kk = n;
			kk -= zero;
			int ans = 0;
			for (int j = 1;; j *= 2) {
				if (j == 1)
					ans++;
				else
					ans += j / 2;
				if (kk <= ans) {
					cout << j;
					break;
				}
			}
		}
		cout << endl;
	}
}
```

---

## 作者：Mr_RoastFish (赞：1)

~~（鄙蒟蒻第一篇题解，主要记叙我的思维过程，节奏可能较慢）~~

洛谷的月赛题质量是真的高。

[题目传送门（一定要看题）。](https://www.luogu.com.cn/problem/P10308)

首先，题目里有这样一句话：

_“你需要在每次修改后，**找到最小的正整数 $t$**，满足进行 $t$ 次操作后的序列 $a$ 与操作前的序列 $a$ 相同。**可以证明**一定存在满足要求的正整数 $t$。”_

不难发现，对于这道看似**没有多种方案处理**的问题，竟然让我们求最小操作次数。说明操作应该是可循环的，而且“**可以证明一定存在满足要求的正整数 $t$。**”也在暗示我们。所以我们应从**循环节**的角度考虑（~~鄙蒟蒻受到月赛 Binary 题“启发”，竟想着从位运算的角度考虑，差点没崩掉~~）。

紧接着，数据的范围 $1 \le n,q \le 3 \times 10^5$ 也在警示我们不可能每次询问都遍历一遍。

接下来我们可以在草稿纸上从 $n=2$ 开始演算几个数找找规律（比较难）~~子曰：不如打表~~ 于是经过不懈的努力~~臭写打表代码~~，不难发现规律为当 $a_i \ne 0$ 时，$t = 2 ^ {\lceil \log_2 n \rceil}$。具体证明可以看[ shinzanmono的题解](https://www.luogu.com.cn/article/21tabq69)。这里是我的证明思路。

------------

首先考虑 $a_i\ne0$ 时：$n=1$，循环节 $t$ 一定为 $1$。再考虑 $n=2$，可以拆成两个 $length=1$ 的序列，第一个序列一步即可解决，但第二个序列会受第一次操作的影响，变成  $a_1 \oplus a_2$，需要额外一次操作解决，$t=2$。（如果能感觉到**对半劈**，是能想到去考虑 $n=4、8 \cdots 2^k$ 的情况的）由此类推，$n=2^k$ 时， $t=2^{\log_2 n}=n$。同理，$n\ne2^k$ 时可以通过补充前缀 $0$（前缀 $0$ 在异或操作中无影响）使 $n=2^k$。所以结果是 $t=2^{\lceil \log_2 n \rceil}$。

然后我们考虑一下含 $0$ 的情况：上一句话给了我们启示：前缀 $0$ 无意义，所以我们在用 $n$ 算 $t$ 时要把前缀 $0$ 的长度减去。中间有 $0$ 是不能删的。（这个不言自明吧。）

-----------

于是我们把问题的核心转移到如何解决求前缀 $0$ 的长度上面。单次操作的时间复杂度不允许遍历。再看到 $a_i,p_i \ge 0$，所以考虑到转化成求前缀和为 $0$ 的最长序列长度（数据结构敲多的应激反应）。（可能有更好的做法，欢迎大佬在评论区里指出）这里我使用树状数组 $+$ 外部二分查找的双 $\log$ 写法，其实可以在查找时于树状数组内倍增查询把复杂度降到单 $\log$（写起来不比线段树优雅？）

至此这道题完结撒花，下面奉上代码。
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int MOD=1e9+7,MAXN=400005;
int a[MAXN],ans,x,t;
long long quickpow(int x,int p){
	long long ans=1;
	while(p){
		if(p&1)	ans=ans*x%MOD;
		x*=x,p>>=1;
	}
	return ans;
}
long long tree[MAXN],n,m;
void add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i))
		tree[i]+=y;
}
long long query(int x){
	long long ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=tree[i]; 
	return ans;
}
int main(){
	cin>>n>>m;
	bool flag=false;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		add(i,a[i]);
	}
	for(int i=1;i<=m;i++){
		cin>>x>>t;
		add(x,t-a[x]);
		a[x]=t;
		int l=0,r=n;
		while(l<r){
			int mid=(l+r+1)/2;
			if(query(mid)==0)	l=mid;
			else r=mid-1;
		}
		if(n-l==0)	{cout<<1<<endl;continue;}//特判，不然log2就成-inf了
		else cout<<quickpow(2,ceil(log2(n-l)))<<endl;//ceil是向上取整，存于cmath库中
	}
	return 0;
}
```
顺手贴上树状数组查询内倍增的单 $\log$ 算法（部分）。
```cpp
int query(int x){
	int l=log2(x);
	int sum=0,ans=0;
	for(int i=l;i>=0;i--){
		long long k=(1LL<<i);
		if(k+ans<=n&&sum+tree[k+ans]==0)	sum+=tree[k+ans],ans+=k;
	}
	return ans;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		add(i,a[i]);
	}
	for(int i=1;i<=m;i++){
		cin>>x>>t;
		add(x,t-a[x]);
		a[x]=t;
		int l=query(n);
		if(n-l==0)	{cout<<1<<endl;continue;}
		else cout<<quickpow(2,ceil(log2(n-l)))<<endl;
	}
	return 0;
}
```

（管理员大大审核辛苦了，感激不尽。）

---

## 作者：HHC883 (赞：0)

# 题目分析
容易发现，答案其实与序列最前面连续的 $0$ 的个数有关——假设序列的最前面有 $m$ 个连续的 $0$，那么答案就为 $2^{\lceil \log_2(n-m) \rceil}$，特别地，若 $n-m=0$，则答案为 $1$。

比如，样例当中，第一次修改后序列为 $\{3,2,0\}$，最前面一个 $0$ 都没有，即 $m=0$，那么答案就是 $2^{\lceil \log_2(3-0) \rceil}=4$；而第二次修改后序列为 $\{0,2,0\}$，最前面有 $1$ 个连续的 $0$（注意，虽然第三项也是 $0$，但第二项非 $0$，故第三项的 $0$ 不属于“最前面的连续的 $0$”。），即 $m=1$，那么答案为 
$2^{\lceil \log_2(3-1) \rceil}=2$；而第三次修改后，序列变成了全 $0$ 的，即 $n-m=0$，故答案为 $1$。

但是，维护序列最前面的连续的 $0$ 的个数也是个难题。这里的方法就很多了，我选择了使用树状数组，通过判断前缀和是否为 $0$ 来得出某个区间是否全 $0$。

至于那个取模，不用管它，因为答案都不可能连序列的长度，更不可能达到 $10^9+7$，这完全就是出题人用来迷惑你的。
# 参考代码
```cpp
#include<iostream>
using namespace std;
#define int long long
int n,q,a[(int)3e5+5],tree[(int)3e5+5],x,p;
int tab[25];
inline int lowbit(int x){
	return x&(-x);
}
inline void update(int x,int p){
	while(x<=n){
		tree[x]+=p;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int ans=0;
	while(x>=1){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	tab[0]=1;
	for(int i=1;i<=20;i++){
		tab[i]=tab[i-1]<<1;
	}
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		update(i,a[i]);
	}
	while(q--){
		cin>>x>>p;
		update(x,p-a[x]);
		a[x]=p;
		int start=1,tmp=0;
		while(a[start]==0&&start<=n){
			for(int i=20;i>=0;i--){
				if(start+tab[i]-1<=n&&query(start+tab[i]-1)-query(start-1)==0){
					tmp+=tab[i];
					start+=tab[i];
					break;
				}
			}
		}
		int need=n-tmp,ans;
		for(int i=0;i<20;i++){
			if(tab[i]<need&&need<=tab[i+1]){
				ans=tab[i+1];
				break;
			}
		}
		if(need==0) cout<<1<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：irris (赞：0)

> tricky / 二进制，位

$*600$，$6.5$。

## Solution

我们知道操作 $2^k$ 次是容易计算的，$a_i$ 只会贡献 $a_i$ 和 $a_{i+2^k}$。[经典题捏](https://www.luogu.com.cn/problem/P4804)。

我们把 $t$ 写成二进制形式：$t = 2^{\omega_1} + 2^{\omega_2} + \dots + 2^{\omega_m}$，$0 \leq \omega_1 \lt \omega_2 \lt \dots \lt \omega_m$。

显然尝试 **归纳证明** 哦哦哦！！！考虑 $2^{\omega_1} \geq n$ 就一定合法了，因为没有任何影响。否则设 $p = 2^{\omega_1}$，那么操作后 $a'_{p+1} = a_{p+1}$ 即要求 $a_{p+1} \oplus a_1 = a_{p+1}$，因此 $a_1 = 0$。继续归纳可以得到 $a_1 \dots a_{n - p}$ 都是 $0$，得出这是充要条件。

显然我们可以找到一个最小的 $p$ 满足 $a_1\dots a_{n-p}$ 都是 $0$，那么让 $t$ 最小（我们要求最小循环节），就可以得出 $\omega_1 = \lceil \log_2 p\rceil$。虽然 $2^{\omega_1}$ 只是 $t$ 的 lowbit，但是因为 $t$ 最小，取 $t = 2^{\omega_1}$ 即可（另外显然 $2^{\omega_1} \mid (2^{\omega_1} + 2^{\omega_2} + \dots + 2^{\omega_m})$）。

维护 $p$ 可以使用 `std::set`，但是这波没卡暴力有点糖了。

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：To_our_starry_sea (赞：0)

# P10308 「Cfz Round 2」Osmanthus 题解

首先，由操作的互相抵消，我们可以~~大胆猜想~~发现其操作是具有周期性的。证明如下。

设序列为 $a$，$T_n$ 为数列长度为 $n$ 且不含前缀 $0$ 时操作的周期。容易证明的，当 $n = 1$ 时，$T_n = 1$。

当 $n = 2$ 时，我们可以发现，对于将其分为两部分，其各部分的周期为 $T_1$，但是为了抵消前一部分对后一部分的干扰，需要进行另外一次操作，即此时 $T_n = 2$。

当 $n = 3$ 时，将其分为 $2$ 和 $1$ 两部分，由于 $T_2 > T_1$，因此两部分内部抵消的周期为 $T_2$，而为了消除前一序列对后一序列的影响，那么又需要 $T_2$ 次操作，即 此时 $T_n = 4$。
 
一般的，设当前序列长度为 $n = 2^k (k \in \mathbb{N_+})$，我们可以将其分为两个长 $2^{k - 1}$ 的序列，并花费 $2 \times T_{k - 1}$ 的代价来抵消，即 $T_{2^k} = 2^k$。而对于 $n = 2^k + L(L < 2^k \text{ 且 } k \in \mathbb{N_+})$ 的情况，因此两部分内部抵消的周期为 $T_{2^k}$，而为了消除前一序列对后一序列的影响，那么又需要 $T_{2^k}$ 次操作，即 $T_{2^k + L} = 2^{k + 1}(L < 2^k \text{ 且 } k \in \mathbb{N_+})$。

由上归纳可得，$T_n = 2^{\lceil \log_2n \rceil}（n \in \natnums）$。

我们发现，以上的归纳是基于没有前缀 $0$ 的基础上的。当前缀 $0$ 存在时，我们只需要将其不计入长度即可。

但值得注意的是，以上我们只证明了充分性，即不保证不存在 $T_n < 2^{\lceil \log_2n \rceil}$ 的情况。但是，我们可以发现 $n = 2$ 时，一次操作后序列为 $a_1 \text{，} a_1 \bigoplus a_2$，当且仅当 $a_1 = 0$ 时其与原序列相同，这与不含前缀 $0$ 的前提矛盾。进而我们可以归纳证明 $T_n < 2^{\lceil \log_2n \rceil}$ 的情况是不存在的。证毕。

对于维护前缀 $0$ 的方法，本人场上智障的使用了二分套线段树，喜提大常数 $O(n \log^2 n)$。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ls(rt) (rt << 1)
#define rs(rt) (rt << 1 | 1)
const int MAXN = 500005;
const ll MOD = 1e9 + 7;
int n, q, a[MAXN], b[MAXN], sum[MAXN];
int tr[MAXN << 4];
ll Ans[MAXN * 4];
inline void pushup(int rt) {
	tr[rt] = max(tr[ls(rt)], tr[rs(rt)]);
}
inline void build(int rt, int l, int r) {
	if (l == r) {
		tr[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(rt), l, mid);
	build(rs(rt), mid + 1, r);
	pushup(rt);
}
inline void change(int rt, int l, int r, int way, int w) {
	if (l == r) {
		tr[rt] = w;
		return;
	}
	int mid = (l + r) >> 1;
	if (way <= mid) change(ls(rt), l, mid, way, w);
	else change(rs(rt), mid + 1, r, way, w);
	pushup(rt);
}
inline int query(int rt, int l, int r, int qx, int qy) {
	if (qx <= l && r <= qy) return tr[rt];
	int mid = (l + r) >> 1, res = 0;
	if (qx <= mid) res = query(ls(rt), l, mid, qx, qy);
	if (qy > mid) res = max(res, query(rs(rt), mid + 1, r, qx, qy));
	return res;
}
inline ll qmi(ll a, ll b) {
	ll res = a, ans = 1;
	while (b) {
		if (b) ans = ans * res % MOD;
		res = res * res % MOD;
		b >>= 1;
	}
	return ans;
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read(), q = read();
    for (int i = 1; i <= n; i++) a[i] = b[i] = read(), sum[i] = sum[i - 1] ^ a[i];
    build(1, 1, n);
    /*int ans = 0;
    while (1) {
		ans++;
		for (int i = 1; i <= n; i++) b[i] = sum[i], cout << b[i] << " ";
		cout << endl;
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] ^ b[i];
		bool pd = true;
		for (int i = 1; i <= n; i++) {
			if (a[i] != b[i]) {
				pd = false;
				break;
			}
		}
		if (pd) break;
	}
	cout << ans << endl;*/
	Ans[0] = Ans[1] = 1;
	int x = 1;
	while (x <= n) {
		for (int i = x + 1; i <= 2 * x; i++) Ans[i] = Ans[x] * 2 % MOD;
		x = 2 * x;
	}
	while (q--) {
		int x = read(), w = read();
		change(1, 1, n, x, w);
		int l = 1, r = n, ans = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (query(1, 1, n, 1, mid) == 0) l = mid + 1, ans = max(ans, mid);
			else r = mid - 1;
		}
		int len = n - ans;
		printf("%lld\n", Ans[len]);
	}
	return 0;
}

```

---

## 作者：sbno333 (赞：0)

这道题并不简单，质量比较高。

显然，每次都是所有元素变为原来的前缀异或和，经过若干次操作后回到原序列。

可以把这个过程倒着走，即差分，$a_i\gets a_{i-1}\oplus a_i$，不会对结果有影响。

我们不妨设一个数 $x_k$，表示 $k$ 此操作后的表达式。

具体的，设 $x_k$ 最右边为第 $0$ 位，从右往左数第 $i$ 个为 $i-1$ 位。

对于每一个自然数 $z$，如果 $x_k$ 的第 $z$ 位为 $1$，则表示 $k$ 次操作后第 $a_i$ 为所有操作前的 $a_{i-z}$ 的异或和（$i-z\le0$ 时 $a_{i-z}$ 为 $0$）。

例如 $z_4=(10001)_2$，则 $4$ 此操作后 $a_i$ 为 操作前 $a_i\oplus a_{i-4}$ 的值，因为第 $0$ 位和第 $4$ 位为 $1$。

因此我们有 $z_0=1$，$z_i=z_{i-1}\oplus(z_{i-1}\times2)$。

可以证明 $z_i$ 一定为奇数，即一定是 $a_i$ 本身和其它的异或和。

我们考虑计算答案。

显然，除了 $a_i$ 自己以外的所有 $k$ 此操作前对 $a_i$ 答案有贡献的 $a_x$ 异或和为 $0$。

值得注意的是对于每一个 $i$ 都如此。

假设 $k$ 此操作后变为原样，则一定存在一个 $i$，除了小于等 $0$ 的 $x$，$a_x$ 有贡献以外（跟没有一样），只有 $a_i$ 自己和 $a_1$ 有贡献，此时 $a_1$ 显然等于 $0$，相当于没有贡献，通过归纳法，可以算出在 $x_k$ 中，对于最小正整数 $z$，使得 $x_k$ 的第 $z$ 位为 $1$，则 $1\sim n-z$ 均为 $0$，当然，也有可能 $n-z\le0$。我们需要维护一个最大的 $s$，使得对于任意 $1\le i\le s$，有 $a_i=0$，接着寻找最小的 $k$ 使得 $x_k$ 的第 $2\sim s-1$ 位均为 $0$。

此时我们发现当 $k=1$ 时，$x=(11)_2$，此时支持的最小的 $n-z$ 为 $n-1$，即 $z$ 最大为 $1$。

当 $k=2$ 时，$x=(101)_2$，此时支持的最小的 $n-z$ 为 $n-2$，即 $z$ 最大为 $2$。

当 $k=4$ 时，$x=(10001)_2$，此时支持的最小的 $n-z$ 为 $n-4$，即 $z$ 最大为 $4$。

$\dots\dots$

显然，当 $k$ 不为 $2$ 的幂时，一定存在一个 $k'$ 使得 $k'<k$，且 $k'$ 位 $2$ 的幂，支持的 $n-z$ 最小值更小。

假设不成立，首先我们显然有 $x_a\times x_b=x_{a+b}$。

即 $x_{k-k'}\times x_{k'}=x_k$。

此时 $x_k$ 的 $n-z$ 与 $x_{k-k'}$ 的 $n-z$ 最小值相同，因为 $k'$ 为 $2$ 的幂，这样的 $2$ 的幂 可以通过数学归纳法得出必定为 $10000\dots0001$ 的形式。

$k-k'$ 显然小于 $k$，此时乘后不存在进位，因为 $k$ 每加一，$x_k$ 位数就多一，乘上比自身为数多的 $1000\dots0001$ 后显然无法进位，因此相同，即我们的答案必定为 $2$ 的幂。

于是问题就转化为寻找一个最小的 $k$，满足 $k$ 为 $2$ 的幂，且对于任意 $1\le i\le n-k$，$a_i=0$。

维护 $n-k\le s$，且对于任意 $1\le i\le s$，$a_i=0$，可以二分答案，由于 $a_i$ 始终大于等于，可以维护前缀和为 $0$。

接着可以轻易维护 $k$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[300009];
int f[300009];//树状数组
int n;
int lowbit(int x){
	return x&(-x);
}
void ps(int x,int p){
	int t;
	t=x;
	while(t<=n){
		f[t]+=p;
		t+=lowbit(t);
	}
}
int gt(int r){
	int t;
	t=r;
	int ans;
	ans=0;
	while(t){
		ans+=f[t];
		t-=lowbit(t);
	}
	return ans;
}
void _main(){
	int q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ps(i,a[i]);
	}
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		ps(x,y-a[x]);//修改
		a[x]=y;
		int l,r;
		l=0,r=n;
		while(l<r){
			int mid;
			mid=l+r+1;
			mid>>=1;
			if(gt(mid)){
				r=mid-1;
			}else{
				l=mid;
			}
		}
		int fs;
		fs=n-l;//l 为 s，显然 k>=n-s
		int ans;//维护 ans，即 k
		ans=1;
		while(ans<fs){
			ans*=2;
		}
		cout<<ans<<endl;
	}
}
signed main(){
	int t;
	//cin>>t;
	t=1;
	while(t--){
		_main();
	}
	return 0;
}
```

因此取模是诈骗，~~我们要有反诈意识~~。

---

## 作者：yshpdyt (赞：0)

# Sol
通过两次打表找规律过了此题。

通过小数据打表找规律，[具体程序](https://www.luogu.com.cn/paste/h75e4ugt)。

发现在没有 $0$ 的情况下，答案都是 $2^{\lceil \log n \rceil}$ ，尝试证明这个结论。

回想一下，我们每次操作相当一次前缀异或，变成原序列的最小操作次数，就是让 $[2,n]$ 异或 $a_1$ 的次数都是偶数次，不妨考虑一下记录每次前缀异或后，每个位置异或 $a_1$ 的次数，设为 $c_{1,i}$，如果是每个位置异或 $a_j$ 的次数，就是 $a_{j,i}$，这等价于对一个除了第一个元素为 $1$，其他都是 $0$ 的数组不断求前缀和，一个序列操作后变回原序列，当且仅当 $\forall i\in[2,n]$，$c_{1,i}\equiv0 \pmod2\ $ 。

再次[打表](https://www.luogu.com.cn/paste/o38yajv1)，发现每 $2^x$ 次操作，会让 $[2,2^{x}]$ 的区间变成偶数，特别的，当 $2^x=1 $时，$c_{1,2}\equiv 1 \pmod2$，这个结论其实比较好证明，具体来说就是仿照二进制下的进位。

这样让 $[2,n]$ 都变成偶数，就需要找到最小的 $2^x$，使得 $2^x\ge n$，这个实际上就是 $2^{\lceil \log n \rceil}$ 。

那么问题来了，只考虑第一个位置，那后面的位置不会有什么影响吗？实际上，假设 $i>1$，需要每 $2^{\lceil \log(n-i+1) \rceil}$ 次才能使 $\forall j\in [i+1,n]$ 的 $c_{i,j}\equiv0\pmod2$ 。

但是 $\lceil \log(n-i+1) \rceil\le\lceil \log n \rceil$，一定有 $\exist k\in \mathbb {N}$，$2^{\lceil \log n \rceil}=k\times 2^{\lceil \log(n-i+1) \rceil\le\lceil \log n \rceil}$。

所以实际上不用考虑后面。

接着考虑一下不全是正整数的情况，我们知道对于一段前缀全为$0$，每次异或对后续不产生影响，可以删掉，所以找到最小的 $i$，使得 $a_i\neq0$，那 $i$ 之后的 $0$ 根据刚才的结论对答案不产生影响，所以答案就是：

$$2^{\lceil \log(n-i+1) \rceil}$$

维护一下第一个非 $0$ 位的位置即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,res[N];
bool fl[N];
set<ll>q;
struct sgt{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll pos[N];
    void upd(ll p,ll l,ll r,ll x,ll t){
        pos[p]=0;
        if(l==r){
            if(t>0)pos[p]=1;
            else pos[p]=0;
            return ;
        }
        if(x<=mid)upd(ls,l,mid,x,t);
        if(x>mid)upd(rs,mid+1,r,x,t);
        pos[p]=0;
        if(pos[ls])pos[p]=pos[ls];
        if(pos[rs])pos[p]=pos[rs];
    }
    ll qr(ll p,ll l,ll r){
        if(l==r)return l;
        if(pos[ls])return qr(ls,l,mid);
        if(pos[rs])return qr(rs,mid+1,r);
        return n;
    }
}T;
ll ksm(ll x,ll y){
    ll ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        ll x;
        cin>>x;
        T.upd(1,1,n,i,x>0);
    }
    ll p=1,lst=1;
    for(int i=1;i<=n;i++){
        res[i]=p;
        if(i-lst==p/2)p*=2,lst=i;
    }
    res[0]=1;
    for(int i=1;i<=m;i++){
        ll x,y;
        cin>>x>>y;
        T.upd(1,1,n,x,y>0);
        auto t=T.qr(1,1,n);
        cout<<res[n-t+1]<<endl;
    }
    

    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们暴力发现答案都是 $2$ 的幂。似乎可以找到突破口。

首先，如果 $a$ 数组有前导零，这些前导零不会对答案造成影响，因为他们异或起来都是 $0$。所以计算答案时可以去掉。

于是我们得到了一个没有前导零的数组 $a$。我们发现变回来的次数总是 $2$ 的幂。具体地，答案是他的长度 $-1$ 之后的 $\operatorname{highbit}\times2$。例如当 $|a|=5$ 时，$5$ 的二进制是 $\texttt{101}$，$\operatorname{highbit}$ 是 $4$，所以答案是 $8$。

如何证明？我们可以利用分治思想，将 $a$ 分为两半，一直递归下去即可。当递归到 $|a|=1$ 时，答案为 $1$。合并时的答案为两个递归返回值的最大值 $\times2$。最终答案就是 $2$ 的递归深度次幂。

于是题目变为单点修改，求前导零个数。前导零，顾名思义，全是 $0$。所以我们可以判断和是否为 $0$ 来判断前导零。二分前导零的长度，用树状数组维护区间和即可，时间复杂度 $O(n\log^2 n)$。

官解居然用 set 维护，我赛时咋没想到啊。

```
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
int n,q,a[300005],c[300005];
//下面是树状数组单点修改，区间查询的函数
void update(int x,int y)
{
  while(x<=n)
  {
    c[x]+=y;
    x+=lowbit(x);
  }
  return;
}
int query(int x)
{
  int ans=0;
  while(x)
  {
    ans+=c[x];
    x-=lowbit(x);
  }
  return ans;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>n>>q;
  for(int i=1;i<=n;i++) cin>>a[i],update(i,a[i]);
  while(q--)
  {
    int x,y,ans=0,mid,l=0,r=n;
    cin>>x>>y;
    update(x,y-query(x)+query(x-1));//单点修改
    while(l<r)//二分查找前导零长度
    {
      mid=l+r+1>>1;
      if(query(mid)==0) l=ans=mid;
      else r=mid-1;
    }
    int now=n-ans-1;//算出去掉前导零后序列的长度
    if(now==0||now==-1)//特判
    {
      cout<<1<<"\n";
      continue;
    }
    for(int i=30;i>=1;i--)
    {
      if(now&(1<<i-1))//找到highbit
      {
        cout<<(1<<i)<<"\n";
        break;
      }
    }
  }
  return 0;
}
```

---

