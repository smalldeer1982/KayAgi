# [ARC145D] Non Arithmetic Progression Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_d

以下の条件を全て満たす整数集合 $ S $ を一つ構築してください。なお、この問題の制約下で条件を満たす $ S $ が少なくとも一つ存在することが証明できます。

- $ S $ の要素数は $ N $
- $ S $ の要素は $ -10^7 $ 以上 $ 10^7 $ 以下の相異なる整数
- $ \displaystyle\ \sum\ _{s\ \in\ S}\ s\ =\ M $
- $ S $ の任意の相異なる要素 $ x,y,z $ $ (x\ <\ y\ <\ z) $ について $ y-x\neq\ z-y $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^4 $
- $ |M|\ \leq\ N\times\ 10^6 $
- 入力は全て整数

### Sample Explanation 1

$ 2-1\ \neq\ 6-2 $ であり、 $ 1+2+6=9 $ なのでこの出力は条件を満たします。他にも様々な答えが考えられます。

### Sample Explanation 2

$ M $ が負のこともあります。

## 样例 #1

### 输入

```
3 9```

### 输出

```
1 2 6```

## 样例 #2

### 输入

```
5 -15```

### 输出

```
-15 -5 0 2 3```

# 题解

## 作者：james1BadCreeper (赞：5)

upd: 感谢 [\@Delov](https://www.luogu.com.cn/user/277792) 的 Hack，现在已经更换为正确的构造方式，麻烦管理重审。

---

首先，$y-x\neq z-y$ 相当于 $x+z\neq 2y$。

我们先抛开和为 $M$ 的限制，考虑如何搞定最后那个不等的限制条件。   
这里先给出结论：将数写成三进制，当数的所有位都是 $0,1$ 时可以满足。   
为什么呢？考虑 $x+z=2y$，$y$ 乘上 $2$ 之后每一位都是 $0$ 或 $2$，而 $x$ 和 $z$ 必定有一位不一样（否则就相等了），加上之后肯定有一位是 $1$，必定不等于 $2y$。所以不等关系永远满足。

现在假定我们构造出来的集合可以表示为递增序列 $a$，然后进行下面对 $M$ 的限制的讨论。

假设我们的 $s$ 与 $M$ 的差为 $x$，整个序列如果同时加上或减去一个数，其性质仍然满足。那么我们可以通过这一点将差 $x$ 控制在 $0\sim n-1$ 内。我们将三进制位的最后一位留白（即最后一位不进行构造，留出来一个 $0$），然后选择任意 $x$ 个数加上 $1$ 即可，最后一位的改变并不会影响答案。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long i64;

int n, a[10005];
i64 m, s = 0;

int main(void) {
    cin >> n >> m;
    for (int p = 1; p <= n; ++p) {
        int x = 0, i = p * 2;
        for (int j = 0, z = 1; j < 16; ++j, z *= 3)
            if ((i >> j) & 1) x += z;
        a[p] = x; s += a[p];
    }
    int x = ((m - s) % n + n) % n;
    for (int i = 1; i <= x; ++i) ++a[i], ++s;
    i64 buf = (m - s) / n; s = 0;
    for (int i = 1; i <= n; ++i) printf("%d ", a[i] + buf);
    putchar('\n');
    return 0;
}
```

---

## 作者：vicky2048_2 (赞：2)

感觉这题的构造真的很神奇。

别的题解都把正解构造方式讲得很清楚了，但无一例外都只摆出结论然后证明正确性而不讲推导过程，这对我这种做题极少的傻逼无疑是极其不友好且没有什么帮助的。

建议先看看其他人的题解，如果您看完之后认为他们所提出的构造结论是显然的，或者您是能一直记住这种构造方式，并在日后遇到这种题目时能独立思考出其构造方式的，那么我这篇题解很大概率就是在浪费您的时间。sto

我尽我所能把题目的推导过程以一个弱智（即我本人）的思考方式呈现出来。

------------
读完题之后发现四个条件串在一起毫无头绪，于是考虑推推第四个条件。

$$y-x\neq z-y(x<y<z)\Longrightarrow z+x\neq 2y$$

~~于是我们发现推完之后仍然毫无头绪。~~

我们可以试试考虑 $2y$ 有什么神奇性质。

容易想到 $2y$ 作为一个偶数在二进制下最后一位一定为 $0$。

考虑这个性质对构造 $z$ 和 $x$ 有什么帮助。

联合 $z$ 与 $x$ 一定不等的这一性质，我们很容易就能想到若在二进制下其中一个数最后一位为 $1$ 而另一个数最后一位为 $0$，那么我们一下子就能够使 $z,x,2y$ 满足 $z\neq x$，$z+x\neq 2y$。

但是此时我们又发现在二进制下继续进行性质推导是比较艰难的，上面的思考又启发我们去往进制的方向推导。

------------
因为暂时没有别的思考方向了，~~于是我们选择打完暴力就立马跑路，~~ 于是我们继续思考如何往进制方向考虑构造。

二进制不行我们就考虑三进制。

因为另外三个条件都没啥可推的，所以我们仍然先从第四个条件开始推导。

$$z+x\neq 2y$$

考虑三进制每一位上只有 $0,1,2$ 三种可能，我们发现同一位上 $1,2$ 相加可以构成 $0$，而 $0,1$ 相加不能构成 $2$，$0,2$ 相加不能构成 $1$。

这启发我们构造一种局面，使 $z,x$ 三进制下每一位都为 $0,1$，$2y$ 三进制下每一位都为 $2$（下文称为局面 $1$）；或 $z,x$ 每一位都为 $0,2$，$2y$ 每一位下都为 $1$（下文称为局面 $2$）。

不难证出，**仅仅构造出上述任意一个局面都并不能保证 $z+x\neq 2y$。**

考虑添加条件使上述构造局面可以满足 $z+x\neq 2y$。

------------
考虑局面 $1$。

联合条件 $2$，我们发现 $z$ 与 $x$ 在某一位上一定不相等，即它们相加得到的数字一定在某一位上为 $1$。

这就非常巧合地满足了 $z+x\neq 2y$ 的条件。

且一个数字每一位上都为 $0,1$，那么其乘二之后得到的数字每一位上一定为 $0,2$。

我们对 $2y$ 的限制由每一位下都为 $2$ 修改为每一位下都为 $0,2$ 并不会产生任何问题。

性质三的构造我们暂时还毫无头绪，于是我们先着眼于性质二。

考虑如何构造每一个数不相等且三进制下每一位都为 $0,1$。

这里可以使每一个数在数组的下标转换为二进制之后的形式看作三进制。（这部分可以看看代码去理解）

例如：

$$(4)_{10}=(100)_2\Longrightarrow (100)_3$$

上面的例子即数组中的第四个数暂时先构造为 $(100)_3$。

按这样的方式构造完一个大小为 $n$ 的数组之后我们的集合就已经满足了条件一、二、四了。

设整个集合的数字和为 $sum$，$\Delta=m-sum$。

易得一个性质，即集合内每个数加上一个相同的数并不会改变集合的性质一、二、四。

集合内每个数加上相同的数，$sum$ 加上的则为 $n$ 的倍数。

即 $\Delta$ 会减小 $n$ 的若干倍数。

想要 $\Delta=0$，只有使 $\Delta$ 一开始即为 $n$ 的若干倍数。

这个就很简单了，只要把集合内每个数三进制下的最后一位空出来，然后选择 $\Delta\bmod n$ 个数去加一即可。

易证得这样构造不会破坏性质一二四。

于是性质三的构造方案也就出来了。

done。

------------
这里补充一点点给我自己看的废话。（

如果做到这种题时不小心先推导到局面二了，记得要**在合理时间范围内**耐心地继续瞎搞，发现局面二走不通时要记得还有局面一，总之就是不要心态大溃烂就对了。

------------
```cpp
#include<bits/stdc++.h>
#define N 10004
#define K 14
#define int long long
using namespace std;
int n,m,a[N],sum;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i){
        for(int j=0,ad=3;j<=K;++j,ad*=3)
            if(i&(1ll<<j)) a[i]+=ad;
        sum+=a[i];
    }
    int del=((m-sum)%n+n)%n;
    for(int i=1;i<=del;++i) ++a[i],++sum;
    int ad=(m-sum)/n;
    for(int i=1;i<=n;++i) printf("%lld ",a[i]+ad);
    return 0;
}
```


---

## 作者：Alan_Zhao (赞：2)

## 题解

先不考虑那个和为 $M$ 的限制，只需要构造出来一个大小为 $N-1$ 的不含等差数列的集合。考虑随机化，每次随机一个 $[-10^7,10^7]$ 间的数尝试插入集合，时间复杂度 $O(N^2)$。

最后，设 $x=M-\sum_{i\in S} i$，我们需要检查 $x$ 是否能插入到集合里。如果不能插入的话整个就寄了，需要重新随机，显然不行。

但可以打表。预先随机出来一个大小为 $17000$ 的合法集合 $S$。每次，我们在这个集合里选择 $N$ 个数作为当前集合。维护当前选择的集合内所有数的和 $s$，如果 $s<M$ 那么在 $S\cap [0,\infty)$ 中随机，否则在 $S\cap (-\infty,0]$ 中随机。这样能保证最后需要插入的 $x$ 一定在 $[-10^7,10^7]$ 范围内，而且我们可以 $O(N)$ 地检查 $x$ 能否插入。这样做一轮是 $O(N)$ 的，有足够的时间随机很多轮。

代码长度 144KB，感谢 AtCoder 宽松的代码长度限制。

## 代码

省略了打表部分。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll = long long;
mt19937 eng(chrono::system_clock::now().time_since_epoch().count());
template<typename T> T Rand(const T& _l, const T& _r) { return uniform_int_distribution<T>(_l, _r)(eng); }
int arr[]{ 打表 };
const int N = 1e4 + 5, V = 1e7 + 5;
int n; ll m, ans[N];
bool can[V * 2], vis[V * 2];
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    int len = size(arr) - 1;
    For(i, 1, len) can[arr[i] + V] = 1;
    while (1) {
        ll s = 0;
        For(i, 1, n - 1) {
            int x;
            if (s <= m) do x = arr[Rand(1, len)]; while (!can[x + V] || x < 0);
            else do x = arr[Rand(1, len)]; while (!can[x + V] || x > 0);
            ans[i] = x, s += x, can[x + V] = 0;
        }
        For(i, 1, n - 1) can[ans[i] + V] = 1;
        if (abs(m - s) > int(1e7)) continue;
        ll x = m - s;
        bool flg = 1;
        For(i, 1, n - 1) vis[ans[i] + V] = 1;
        For(i, 1, n - 1) {
            if (abs(2 * ans[i] - x) <= int(1e7) && vis[2 * ans[i] - x + V]) { flg = 0; break; }
            if (abs(2 * x - ans[i]) <= int(1e7) && vis[2 * x - ans[i] + V]) { flg = 0; break; }
        }
        if (flg) {
            ans[n] = m - s;
            For(i, 1, n) cout << ans[i] << " \n"[i == n];
            return 0;
        }
        For(i, 1, n - 1) vis[ans[i] + V] = 0;
    }
    return 0;
}
```

---

## 作者：LiveZoom (赞：1)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc145_d)

## Solution

先不管和为 $m$ 的约束，只考虑第四个条件。

那么条件可以转化为 $2y\neq x+z$，考虑三进制构造。

假设每个数的三进制的每一位都是 $0$ 或 $1$，那么如果 $2y=x+z$，就意味着 $x$ 和 $z$ 的每一位都相等，则 $x=z$。与题意矛盾。

所以只要构造 $n$ 个互不相同的且三进制每一位都是 $0$ 或 $1$ 的数就可以满足第四个条件。

然后考虑一件事情：这 $n$ 个数同时加上同一个数仍能满足约束，所以可以把这 $n$ 个数加上同一个数使得它们的和最接近 $m$。

那么这时候和与 $m$ 的差不会超过 $n$，所以可以先让每一个数最后一位填上一个 $0$，先补 $1$，使得它们的和与 $m$ 模 $n$ 同余，然后同时加上一个数即可。

时间复杂度：$O(n\log n)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 1e4 + 5;

int n, m;
long long sum;
int a[kMaxN];

void diao() {
  int cnt = ((m - sum) % n + n) % n;
  for (int i = 1; i <= cnt; ++i)
    ++a[i];
  sum += cnt;
  for (int i = 1; i <= n; ++i) {
    a[i] += (m - sum) / n;
    cout << a[i] << ' ';
  }
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int s = i * 2;
    for (int j = 0, x = 1; j <= 20; ++j, x *= 3)
      if (s >> j & 1)
        a[i] += x;
    sum += a[i];
  }
  diao();
  return 0;
}
```

~~感觉这种神奇的进制构造方式只能靠做题来积累。~~

---

## 作者：Delov (赞：1)

先抛开和为 $M$ 的限制不谈，我们考虑如何构造出一个不出现 $y-x=z-y$ 的集合。

先移项，得到 $x+z=2y$，一个~~神秘的~~观察：**三进制**

我们考虑选出的数的三进制表示，如果只选择三进制表示下各位上只有 $0$ 和 $1$ 的数，那么一定可以符合要求。因为 $x,y$ 至少有一位不同，$x+y$ 的三进制表示中一定会出现 $1$，而 $2y$ 的三进制表示中只有 $2$。

在值域的限制下，能选出的数的总数大于 $10^4$，于是我们暂时完成了这一步构造。

再考虑如何满足和为 $M$ 的限制。令当前构造出的集合的数的和为 $sum$，$diff=M-sum$，若 $n \mid diff$，则我们可以将差值均摊到每个数上，此时仍不会出现 $x+z=2y$ 的情况，因为两侧的增量相同，仍然不会相等。

当 $n \nmid diff$ 时，我们可以将 $diff$ 补齐到 $n$ 的倍数再均摊下去。做法很妙，通过修改一下第一步构造集合的操作，我们强制选出的数的第 $0$ 位为 $0$，这样每个数都可以在满足限制的条件下再增加 $1$，于是我们只需要给 $diff \bmod n$ 个数加一即可。

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18157231)

### [[ARC145D] Non Arithmetic Progression Set](https://www.luogu.com.cn/problem/AT_arc145_d)

考虑三进制，如果只选只有 $01$ 的数就一定合法。

然后可以考虑平移，即每个数同时 $\pm C$。如果原序列合法，经过该操作之后一定仍然合法。所以只需要构造一个序列，使得和 $\bmod\;n$ 意义下和 $m$ 同余。

暴力选取最小的 $n-1$ 个合法三进制数，接下来补一个非常大的数，使得 $sum$ 同余 $m$，打表可以发现第 $9999$ 个合法的数是 $1.7\times 10^6$ 左右，所以补的数如果接近上界就不会出现不合法的情况。

最后再算一下差值，通过平移把 $sum$ 变成 $m$。

```cpp
int n,m,len,sum,a[10010];
inline void mian()
{
	read(n,m);
	int sum=0;
	for(int i=0;n-1;++i)
	{
		int x=i,fl=1;
		while(x)fl&=(x%3!=2),x/=3;
		if(!fl)continue;
		a[++len]=i,sum+=i;
		if(len==n-1)break;
	}
	int ned=((m-sum)%n+n)%n;
	ned+=(9000000-ned)/n*n,a[n]=ned,sum+=ned,assert(sum%n==(m%n+n)%n);
	int delta=(sum-m)/n;
	for(int i=1;i<=n;++i)a[i]-=delta,write(a[i]);
}
```

---

## 作者：Starry_Ocean (赞：0)

### 题意简化

构造一个含有 $n$ 个元素的集合，使得该集合中所有的元素之和等于 $m$ 且两两不同。对于集合中任意满足 $x < y < z$ 的三个元素，有关系 $x + z \ne 2y$ 。

### 思路
简单打表容易发现，把所有的数都转换为三进制，当所有的位都为 0 或 1 时则满足不等条件。那么代码就很快写出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,s=0,a[10006];
int main(){
	cin>>n>>m;
	for(ll i = 1;i <= n;++i){//枚举n个位置 
		for(ll j = 0,d=3;j <= 14;++j,d*=3){//三进制 
			if(i&(ll)pow(2,j)) a[i]+=d;
		}
		s+=a[i];
	}
	ll k = ((m-s)%n+n)%n;
	for(ll i = 1;i <= k;++i) a[i]++;
	s+=k;
	ll kk=(m-s)/n;
	for(ll i = 1;i <= n;++i){
		cout << a[i]+kk << " ";
	}
	return 0;
} 
```

---

