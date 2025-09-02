# [ARC047C] N!÷K番目の単語

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc047/tasks/arc047_c

高橋語には $ N $ 種類の文字があります。

この問題では便宜上、各文字に辞書順で小さい順に $ 1 $ ～ $ N $ の整数を割り振って扱うことにします。

高橋語の単語は全て $ N $ 文字からなり、$ N $ 種類の文字が全てちょうど $ 1 $ 個ずつ含まれます。 また、そのような文字列は全て高橋語の単語です。

つまり、高橋語の単語は $ N! $ 個あります。

ある $ N $ 以下の正の整数 $ K $ が与えられるので、高橋語の単語の中で辞書順で小さい方から $ N!\ ÷\ K $ 番目の単語を求めてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ N\ ≦\ 20 $ を満たすデータセットに正解した場合は $ 30 $ 点が与えられる。
- $ 1\ ≦\ N\ ≦\ 10^5 $ を満たすデータセットに正解した場合はさらに $ 70 $ 点が与えられる。合計で$ 100 $点となる。

### Sample Explanation 1

$ 1,2,3,4 $ の並び替えのうち、辞書順で小さい方から $ 4!\ ÷\ 3\ =\ 8 $ 番目の文字を出力しなければなりません。 高橋語の単語のうち辞書順で小さい方から順に $ 8 $ 個を列挙すると $ 1,\ 2,\ 3,\ 4 $ $ 1,\ 2,\ 4,\ 3 $ $ 1,\ 3,\ 2,\ 4 $ $ 1,\ 3,\ 4,\ 2 $ $ 1,\ 4,\ 2,\ 3 $ $ 1,\ 4,\ 3,\ 2 $ $ 2,\ 1,\ 3,\ 4 $ $ 2,\ 1,\ 4,\ 3 $ となります。よって $ 2,\ 1,\ 4,\ 3 $が求めるべき単語です。

## 样例 #1

### 输入

```
4 3```

### 输出

```
2
1
4
3```

## 样例 #2

### 输入

```
11 7```

### 输出

```
2
7
9
5
4
11
10
8
6
3
1```

# 题解

## 作者：chroneZ (赞：2)

给定 $n, k$，求字典序意义下第 $\frac{n!}{k}$ 个长度为 $n$ 的排列。

---

记**当前**确定到前 $t$ 项，前 $t$ 项中未被使用的数值构成有序集 $S$，**$a_i$ 表示在恰好确定了前 $i - 1$ 项后，答案排列的第 $i$ 项为当前有序集 $S$ 中的第 $a_i$ 项**，“剩余项对应的排列”的名次为 $x$，

- “剩余项”指：序列 $s = [a_{t + 1}, a_{t + 2}, \dots, a_n]$。
- “剩余项对应的排列”指：
  - 定义一种映射 $f$ 使得 $f(s) = p$，其中 $s$ 为一元素两两不相同的序列，$p$ 为一长度与 $s$ 相同的排列，使得 $p_i$ 表示对序列 $s$ 中的元素从小到大排序后 $s_i$ 的名次。
  - 对于剩余项 $s = [a_{t + 1}, a_{t + 2}, \dots, a_n]$，其对应的排列指 $f(s)$。

从小范围开始考虑。回想一下逆康托展开的推导，类似地，记 $x = \frac{n!}{k}$，则对于每种取值下的 $a_1$，其后的 $[a_2, a_3, \dots, a_n]$ 都会有 $(n - 1)!$ 种取值方案，容易得到 $a_1 = \lceil \frac{x}{(n - 1)!} \rceil$。确定 $a_1$ 后，$x \gets x \bmod (n - 1)!$，注意若得到 $x = 0$，则剩余项对应的排列为 $[n - t, n - t - 1, \dots, 1]$，此时可以且必须直接输出结果，证明可参考康托展开。

类似地，$a_i = \lceil \frac{x}{(n - i)!} \rceil$，随后 $x \gets x \bmod (n - i)!$，若得到 $x = 0$ 则直接确定剩余项。重复此步骤可得到最终结果。但是本题 $n, k$ 达到了 $10^5$ 量级，显然此时对应的 $x = \frac{n!}{k}$ 会非常大，无法直接计算。

其实本题的核心就在于 $\frac{n!}{k}$ 这个形式。仍然考虑我们刚才提到的那个步骤，对 $a_1$ 的计算式，将 $x \gets \frac{n!}{k}$ 代入得 $a_1 = \lceil \frac{\frac{n!}{k}}{(n - 1)!} \rceil = \lceil \frac{n}{k} \rceil$，之后 $x \gets \frac{n!}{k} \bmod (n - 1)! = (\frac{n}{k} \times (n - 1)!) \bmod (n - 1)!$，取模后显然系数 $\frac{n}{k} < 1$，容易得到最终 $x \gets \frac{(n~\bmod~k) \times (n - 1)!}{k}$。记 $c_2 = n \bmod k$，则此时 $x$ 又可写作 $\frac{c_2(n - 1)!}{k}$ （同理若 $x = 0$，则可以且必须直接输出结果，后文不再作强调）。

继续地，将 $\frac{c_2(n - 1)!}{k}$ 代入 $a_2$ 的计算式，同理有 $a_2 = \lceil \frac{\frac{c_2(n - 1)!}{k}}{(n - 2)!} \rceil = \lceil \frac{c_2(n - 1)}{k} \rceil$，随后 $x \gets \frac{c_2(n - 1)!}{k} \bmod (n - 2)! = (\frac{c_2(n - 1)}{k} \times (n - 2)!) \bmod (n - 2)! = \frac{(c_2(n - 1)~\bmod~k) \times (n - 2)!}{k}$，记 $c_3 = c_2(n - 1) \bmod k$，则 $x$ 可写作 $\frac{c_3(n - 2)!}{k}$。

如此归纳下去，我们可以得到改良后的计算步骤：令 $c_1 = 1$，$c_{i + 1} = c_i(n - i + 1) \bmod k$，则 $a_i = \lceil \frac{c_i(n - i + 1)}{k} \rceil$。当得到某一个 $c_{q + 1} = 0$ 时，可以且必须直接确定 $\forall i \in [q + 1, n], a_i = n - i + 1$。

至于怎么用 $a_i$ 还原真正的答案序列，可以使用树状数组二分 $\mathcal{O}(n \log n)$ 实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int MN = 1e5 + 10;
int t[MN], n, k;
inline void add(int x, int v) {for(; x < MN; x += x & -x) t[x] += v;}
inline int query(int x){
	int s = 0, pos = 0;
	for(int j = 18; j >= 0; j--){
		if(pos + (1 << j) > n) continue;
		if(s + t[pos + (1 << j)] > x) continue;
		s += t[pos + (1 << j)], pos += 1 << j;
	}
	return pos;
}
// 求最大的满足 sum(1, pos) <= x 的 pos
// 容易发现本题中要求最小的满足 sum(1, pos) = x 的 pos, 因此应使用 query(x - 1) + 1
inline i64 dv(i64 x, i64 p) {return (x + p - 1) / p;}
void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++) add(i, 1);
	i64 x = 1;
	for(int i = 1; i <= n; i++){
		int pos = query(dv(x * (n - i + 1), k) - 1) + 1; add(pos, -1);
		cout << pos << "\n";
		x = x * (n - i + 1) % k;
		if(x == 0){
			int cur = n - i;
			while(cur > 0){
				int pos = query(--cur) + 1; add(pos, -1);
				cout << pos << "\n";
			}
			break;
		}
		// x 对应题解中的 c_i, pos 对应题解中的 a_i
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	solve();
}
```

---

## 作者：AC_love (赞：1)

这玩意看起来就是逆康托展开，逆康托展开怎么做呢？

直接模拟即可。首先，若排列的长度是 $N$，排名是 $K$：

对于第一位的数，我们可以求一下他是当前没选的数中排第几的：$a_1 = \lceil \dfrac{K}{(N - 1)!} \rceil$，然后我们把 $K$ 赋值成 $K \bmod (N - 1)!$，继续求 $a_2$，以此类推。

我们求出整个 $a$ 序列后，即可利用 $a$ 序列还原出原排列。

但是我们注意到：这道题 $N!$ 非常非常大，我们很难直接模拟，怎么办呢？

考虑本题有特殊要求：这个排列的字典序是 $\dfrac{n!}{k}$，我们可以从这里下手。

$$a_1 = \lceil \dfrac{n!}{k(n - 1)!} \rceil = \lceil \dfrac{n}{k} \rceil$$

此时有：

$$K = \dfrac{n!}{k} \bmod (n - 1)! = (\dfrac{n}{k} \times (n - 1)!) \bmod (n - 1)!$$

小学四年级的时候我们就知道：做除法的时候，被除数和除数同时约掉一个 $x$，商不变，余数也约掉一个 $x$。因此有：

$$K = (\dfrac{n}{k} \times (n - 1)!) \bmod (n - 1)! = \dfrac{(n \bmod k) \times (n - 1)!}{k}$$

根据这个求一下 $a_2$，得到：

$$a_2 = \lceil \dfrac{(n \bmod k)(n - 1)}{k} \rceil$$

此时求一下 $K$ 的新值：

$$K = \dfrac{(n \bmod k) \times (n - 1)!}{k} \bmod (n - 2)!$$

转化一下：

$$K = \dfrac{((n \bmod k)(n - 1) \bmod k)(n - 2)!}{k}$$

我们都知道乘法时取模可以只在最后一次取，因此：

$$K = \dfrac{(n(n - 1) \bmod k)(n - 2)!}{k}$$

根据这个求一下 $a_3$：

$$a_3 = \lceil \dfrac{(n(n - 1) \bmod k)(n - 2)}{k} \rceil$$

找到规律，对于任何一个 $a_i$，都有：

$$a_i = \lceil \dfrac{(\prod_{i = n - i + 2}^n i) \bmod k(n - i + 1)}{k} \rceil$$

需要注意的是：计算过程中，会出现取模之后分子等于 $0$ 的情况，此时后面的所有 $a_i = n - i + 1$，不需要再算下去了。

这样我们就可以求出所有 $a_i$，随便套个平衡树就能反推出原序列了。

[code](https://atcoder.jp/contests/arc047/submissions/59747757)

---

## 作者：ifffer_2137 (赞：0)

校 NOIP 模拟赛 T2。~~这不是逆康托展开板子~~。
### 题意
求长度为 $n$ 的排列中字典序第 $\dfrac{n!}{k}$ 小的。
### 分析
首先你要知道[逆康托展开](https://oi-wiki.org/math/combinatorics/cantor/#%E9%80%86%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80)。

然后你按照它模拟，可惜失败了。数字太大维护不了。

那我们考虑手动算。

首先拿 $\dfrac{n!}{k}$ 除以 $(n-1)!$，约掉 $(n-1)!$ 剩下 $\dfrac{n}{k}$，所以第一位填 $\lceil \dfrac{n}{k} \rceil$。

填好以后考虑后面 $n-1$ 位，我们需要的排名是 $\dfrac{n!}{k}-(n-1)!(\lceil \dfrac{n}{k} \rceil-1)$。

同样除以 $(n-2)!$，约去 $(n-2)!$，得到 $\lceil \dfrac{n}{k}-(n-1)(\lceil \dfrac{n}{k} \rceil-1) \rceil$，填进去。

同理弄几步，可以发现了，阶乘的部分大多数可以约掉，具体处理手法是维护一个值 $rk$，每次乘上阶乘约去后多余的那一项，然后求出填哪个数，再减去填的那个数对排名产生的贡献。注意取上整的时候可以把第一项的 $k$ 拿到分母上，这样维护比较方便。

时间复杂度是逆康托展开的复杂度，这里写了粗糙二分套 BIT 是 $O(n\log^2n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
int n,k,cnt,val;
int p[maxn];
class Fenwick_Tree{
public:
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void update(int x,int k){while(x<=n){c[x]+=k;x+=lowbit(x);}}
	int query(int x){int res=0;while(x){res+=c[x];x-=lowbit(x);}return res;}
}tr;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),k=read();val=1,cnt=0;
	for(int i=n-1;i>=1;i--){
		val*=(i+1);int t=(val+k-1)/k;
		int l=1,r=n;cnt++;
		while(l<=r){
			int m=(l+r)>>1;
			if(m-tr.query(m)>=t){
				p[cnt]=m;
				r=m-1;
			}else{
				l=m+1;
			}
		}
		tr.update(p[cnt],1);
		val-=(t-1)*k;
	}
	for(int i=1;i<=n;i++){
		if(tr.query(i)-tr.query(i-1)==0){
			p[++cnt]=i;
			break;
		}
	}
	for(int i=1;i<=n;i++) cout<<p[i]<<"\n";
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[AT_arc047_c [ARC047C] N!÷K番目の単語](https://www.luogu.com.cn/problem/AT_arc047_c)

### 解法

首先你需要了解一下[康托展开](https://oi-wiki.org/math/combinatorics/cantor/)。

相信你在学习了如上内容后，就知道本题其实仅仅是一道逆康托展开的模板题。

但是 $\dfrac{n!}{k}$ 太大，发现要写高精度，计算量太大。

同样运用上面的思路，对于从右往左数第 $i$ 位，如果它是 $p$，并且前方有 $w(w\le n-i)$ 个数比它小，那么它会对排名增加 $(p-w-1)\times(i-1)!$。

考虑将排名转化为 $\dfrac{n!}{k}=\dfrac{n}{k}\times(n-1)\times\cdots\times1$，此时只要找到一个尚未出现在排列中的最大的 $p$ 满足 $(p-w-1)\le\dfrac{i}{k}$ 就可以了。因为随着 $p$ 的增加， $w$ 的增量只可能为 $0$ 或 $1$，所以式子满足单调性，可以二分。

找到以后只要将 $\dfrac{n}{k}$ 减去 $(p-w-1)$ 就是前方剩余的排列数量除以 $(n-1)!$，所以只要将前者再乘上 $(n-1)$ 就可以对第 $(n-1)$ 位操作了。

至于 $w$，用树状数组或线段树维护，复杂度 $O(n\log n)$。

那么加起来复杂度就是 $O(n\log^2n)$，优秀一点的话可以做到 $O(n\log n)$。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=100005;
long long n,k,a[N],now,d;
std::vector<int>c;
struct Tree{
    int b[N];
    inline int lowbit(int x){return x&(-x);}
    inline void update(int x,int k){
        for(int i=x;i<=n;i+=lowbit(i))
            b[i]+=k;
    }
    inline int query(int x){
        int sum=0;
        for(int i=x;i;i-=lowbit(i))
            sum+=b[i];
        return sum;
    }
}tree;
signed main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>k;
    now=n;d=k;
    for(int i=1;i<=n;++i) c.push_back(i);
    for(int i=n;i>=1;--i){
        int l=0,r=c.size()-1,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(1ll*(c[mid]-1-tree.query(c[mid]))*d<1ll*now) ans=mid,l=mid+1;
            else r=mid-1;
        }
        // cout<<ans<<' '<<now<<' '<<'\n';
        a[i]=c[ans];
        now-=1ll*(c[ans]-1-tree.query(c[ans]))*d;
        now=1ll*now*(i-1);
        tree.update(c[ans],1);
        c.erase(c.begin()+ans);
    }
    for(int i=n;i>=1;--i) cout<<a[i]<<'\n';
    return 0;
}
```

---

