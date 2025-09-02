# Puzzle

## 题目描述

Pupils Alice and Ibragim are best friends. It's Ibragim's birthday soon, so Alice decided to gift him a new puzzle. The puzzle can be represented as a matrix with $ 2 $ rows and $ n $ columns, every element of which is either $ 0 $ or $ 1 $ . In one move you can swap two values in neighboring cells.

More formally, let's number rows $ 1 $ to $ 2 $ from top to bottom, and columns $ 1 $ to $ n $ from left to right. Also, let's denote a cell in row $ x $ and column $ y $ as $ (x, y) $ . We consider cells $ (x_1, y_1) $ and $ (x_2, y_2) $ neighboring if $ |x_1 - x_2| + |y_1 - y_2| = 1 $ .

Alice doesn't like the way in which the cells are currently arranged, so she came up with her own arrangement, with which she wants to gift the puzzle to Ibragim. Since you are her smartest friend, she asked you to help her find the minimal possible number of operations in which she can get the desired arrangement. Find this number, or determine that it's not possible to get the new arrangement.

## 说明/提示

In the first example the following sequence of swaps will suffice:

- $ (2, 1), (1, 1) $ ,
- $ (1, 2), (1, 3) $ ,
- $ (2, 2), (2, 3) $ ,
- $ (1, 4), (1, 5) $ ,
- $ (2, 5), (2, 4) $ .

It can be shown that $ 5 $ is the minimal possible answer in this case.

In the second example no matter what swaps you do, you won't get the desired arrangement, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
5
0 1 0 1 0
1 1 0 0 1
1 0 1 0 1
0 0 1 1 0```

### 输出

```
5```

## 样例 #2

### 输入

```
3
1 0 0
0 0 0
0 0 0
0 0 0```

### 输出

```
-1```

# 题解

## 作者：xixike (赞：14)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/CF1700F)

题意：

给你两个只包含 $0, 1$ 的 $2 \times n$ 的数组 $a, b$，每次可以交换相邻两个数，问从 $a$ 变成 $b$ 最少需要交换多少次。

## Solution

先看只有一行的情况：

我们考虑每两个相邻的点对答案的贡献，即交换的次数。

记两个数组 $a, b$ 的前缀和分别为 $sa, sb$，枚举每一位 $ans$ 加上 $|sa_i - sb_i|$ 即为答案。这个应该比较好理解吧。

现在来看如果有两行如何处理：

两行比一行就多了一个上下交换的操作。

我们还是设 $sa_{0/1, i}$ 表示 $a$ 的第一，第二行的前缀和，$sb_{0/1, i}$ 同理。

枚举每一位如果 $sa_{0, i} > sb_{0, i}$ 且 $sa_{1, i} < sb_{1, i}$ 或者 $sa_{0, i} < sb_{1, i}$ 且 $sa_{1, i} > sb_{1, i}$那么我们上下交换，这样就从原本两次的左右交换变成了一次上下交换，节省了一次操作。

当然还要加上 $|sa_{0, i} - sb_{0, i}| + |sa_{1, i} - sb_{1, i}|$。

需要注意的是，$sa$ 是在实时变化的，所以开两个变量来记 $a$ 的前缀和。

最后别忘了判无解：如果 $a, b$ 中 1 的个数不相同那么一定无解。

## Code

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0, f = 1;
        char ch = getchar();
        while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x * f;
    }

    template <typename T> inline void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;
int n, suma, sumb;
int a[2][N], b[2][N], s[2][N];

signed main(){
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    n = read();
    for(int i = 1; i <= n; ++i) suma += (a[0][i] = read());
    for(int i = 1; i <= n; ++i) suma += (a[1][i] = read());
    for(int i = 1; i <= n; ++i){
        sumb += (b[0][i] = read());
        s[0][i] = s[0][i - 1] + b[0][i];
    }
    for(int i = 1; i <= n; ++i){
        sumb += (b[1][i] = read());
        s[1][i] = s[1][i - 1] + b[1][i];
    }
    if(suma != sumb) return puts("-1"), 0;
    int s0 = 0, s1 = 0, ans = 0;
    for(int i = 1; i <= n; ++i){
        s0 += a[0][i], s1 += a[1][i];
        while(s0 > s[0][i] && s1 < s[1][i]) s0--, s1++, ans++;
        while(s0 < s[0][i] && s1 > s[1][i]) s0++, s1--, ans++;
        ans += abs(s0 - s[0][i]) + abs(s1 - s[1][i]);
    }
    write(ans), puts("");
}
```



---

## 作者：devout (赞：11)

考虑如果只有一行，就是一个显然的贪心，用 $d_i$ 表示前 $i$ 个位置的 $a-b$ 的前缀和，答案就是 $\sum |d_i|$

到这个题里，因为交换操作可以任意打乱，所以我们假设所有上下操作都在开头进行，设进行了 $x$ 次，$d_{i,j}$ 表示第 $i$ 行，$j$ 处的 $a-b$ 的前缀和，答案即为 $x+\sum |d_{0,i}|+|d_{1,i}|$

不妨设 $(0,i)$ 的 `1` 挪了下去，那么 $d_{0,j}(j\geq i)$ 减少 1，$d_{1,j}(j\geq i)$ 增加 1

那么在 $d_{0,i}$ 和 $d_{1,i}$ 同号的时候，交换肯定是不优的，因为如果后缀需要交换放到 $i+1$ 交换答案不会变差

异号的时候，我们交换 $k=\min(|d_{0,i}|,|d_{1,i}|)$ 次，因为在 $i$ 处我们节省了 $k$ 次，即使我们让后面更差了，他也可以再通过 $k$ 次交换变回来，答案没有变差

因此这样贪心就可以在 $O(n)$ 的时间内求解了

```cpp
#include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

const int N=2e5+5;

typedef long long ll;
typedef double db;

# define chkmax(a,b) a=max(a,b)
# define chkmin(a,b) a=min(a,b)
# define PII pair<int,int>
# define mkp make_pair

template<typename T> void read(T &x){
    x=0;int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int a[2][N],b[2][N];
ll ans;

int main()
{
    # ifndef ONLINE_JUDGE
    freopen("testdata.in","r",stdin);
    //freopen("test1.out","w",stdout);
    # endif
    read(n);
    int one=0;
    Rep(i,0,1)Rep(j,1,n)read(a[i][j]),one+=a[i][j];
    Rep(i,0,1)Rep(j,1,n)read(b[i][j]),one-=b[i][j];
    if(one)return puts("-1"),0;
    int O=0,I=0;
    Rep(i,1,n){
        O+=a[0][i]-b[0][i];
        I+=a[1][i]-b[1][i];
        if(O<0&&I>0){
            int k=min(-O,I);
            ans+=k;
            O+=k,I-=k;
        }
        else if(O>0&&I<0){
            int k=min(O,-I);
            ans+=k;
            O-=k,I+=k;
        }
        ans+=abs(O)+abs(I);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：ZillionX (赞：6)

# Description

给出两个 $2 \times n$ 的 01 矩阵 $A,B$，每次操作可以交换 $A$ 中任意两个相邻位置的值，求使得 $A = B$ 的最小操作次数。

$n \le 2 \times 10^5$，时限 1s。

# Solution

我们首先考虑 $1 \times n$ 矩阵的情况。

观察样例，不难发现结论：此时使得 $1 \times n$ 矩阵 $A=B$ 的最小操作次数即为

$$\sum_{i=1}^n |{\rm sum}A_i-{\rm sum}B_i|$$

其中 ${\rm sum}A_i= \sum\limits_{j=1}^i A_j$，${\rm sum}B_i$ 同理，对于上式的证明留作读者练习。

接下来考虑拓展到 $2 \times n$ 矩阵的情况，可以发现，无非就是对于原来单独的两行，增加了一个上下交换操作。

我们以将第一行的 $1$ 转移下去的上下交换操作为例，注意到，这会使第一行 $A-B$ 的前缀和减 $1$，而第二行则会加 $1$。

由于答案取绝对值，不难想到，若两行 $A-B$ 的前缀和同号，那么交换操作一定是没有意义的，不会使答案变优。

但是，若它们异号，我们则可以移动 $\min\{|{\rm sum}A_{i,1}-{\rm sum}B_{i,1}|,|{\rm sum}A_{i,2}-{\rm sum}B_{i,2}\}|$ 个 $1$，使得其中之一变为 $0$。这样可以将原来 $2$ 次的左右交换操作，优化为 $1$ 次的上下交换操作。

值得一提的是，尽管这样的移动具有后效性，但可以分析出来，它并不会使我们的答案变劣，因此这是合法的贪心做法。

至此我们就在 $\mathcal O(n)$ 的时间复杂度下完成了本题。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+5;
int n,a[2][N],b[2][N];
LL sum,Ans;
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[0][i]),sum+=a[0][i];
	for (int i=1;i<=n;i++) scanf("%d",&a[1][i]),sum+=a[1][i];
	for (int i=1;i<=n;i++) scanf("%d",&b[0][i]),sum-=b[0][i];
	for (int i=1;i<=n;i++) scanf("%d",&b[1][i]),sum-=b[1][i];
	if (sum) {
		printf("-1");
		return 0;
	}
	LL s0=0,s1=0;
	for (int i=1;i<=n;i++) {
		s0+=a[0][i]-b[0][i],s1+=a[1][i]-b[1][i];
		if (s0<0 && s1>0) {
			int nm=min(-s0,s1);Ans+=nm;s0+=nm,s1-=nm;
		}
		else if (s0>0 && s1<0) {
			int nm=min(s0,-s1);Ans+=nm;s0-=nm,s1+=nm;
		}
		Ans+=abs(s0)+abs(s1);
	}
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：FeelGood (赞：2)

我们先考虑只有一行的情况，记 $sa_{i}$ 为矩阵 $A$ 前 $i$ 个元素中 $1$ 的数量，记 $sb_i$ 为矩阵 $B$ 中前 $i$ 个元素中 $1$ 的数量。

那么让两个矩阵匹配的代价就是 $\sum_{i = 1}^{n}| sa_i - sb_i|$，如何理解呢？

我们先思考当 $sb_{i} > sa_{i}$ 时，对于矩阵 $A$ 的第 $i$ 个位置，前 $i$ 个元素就缺少了 $sb_i - sa_i$ 个 $1$，当我们为了匹配矩阵 $B$，从矩阵 $A$ 后面往前面交换元素时，当前这个元素至少会被交换 $sb_i - sa_i$ 次，对答案的贡献就是 $sb_i - sa_i$ 次。

接下来就是 $sb_i < sa_i$ 的情况了，这时我们把缺少的元素看成是 $0$ 就是上面 $sb_{i} > sa_{i}$ 的情况了。

然后就是矩阵为两行的情况了，我们还是记 $sa_{0/1,i}$ 为矩阵 $A$ 的第 $0/1$ 行前 $i$ 个元素中 $1$ 的数量，$sb_{0/1,i}$ 为矩阵 $B$ 的第 $0/1$ 行前 $i$ 个元素中 $1$ 的数量。

根据上面我们计算代价的公式，我们发现要尽可能的让每一个 $i$ 中 $0$ 或 $1$ 的数量差尽可能小。那么就很容易想到如果一行中多出了一些 $1$，而另一行缺少了一些 $1$，那么我们把多的 $1$ 交换到少的地方，肯定结果肯定不会更劣。

接下来时一些细节的问题了，可以参考一下我的代码。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define lll __int128

using namespace std;

namespace FastRead
{
	void read() {}

	template<typename T1, typename ...T2>
	void read(T1 &n, T2 &...m)
	{
		T1 op = 1;
		char c;
		while (isdigit(c = getchar()) == false)
			if (c == '-')
				op = -1;
		n = c ^ 48;
		while (isdigit(c = getchar()))
			n = (n << 1) + (n << 3) + (c ^ 48);
		n *= op;
		read(m...);
	}
}

using FastRead::read;

namespace Solve
{
	const int MaxN = 2e5;
	
	int a[2][MaxN + 10], b[2][MaxN + 10];
	
	void Sol()
	{
		ll n;
		read(n);
		for (ll i = 0; i <= 1; ++i)
			for (ll j = 1; j <= n; ++j)
				read(a[i][j]);
		for (ll i = 0; i <= 1; ++i)
			for (ll j = 1; j <= n; ++j)
				read(b[i][j]);
		ll cnta0 = 0, cnta1 = 0, cntb0 = 0, cntb1 = 0, ans = 0;
		for (ll i = 1; i <= n; ++i)
		{
			cnta0 += a[0][i] == 1;
			cnta1 += a[1][i] == 1;
			cntb0 += b[0][i] == 1;
			cntb1 += b[1][i] == 1;
			if (cnta0 > cntb0 && cnta1 < cntb1)
				--cnta0, ++cnta1, ++ans;
			else if (cnta0 < cntb0 && cnta1 > cntb1)
				--cnta1, ++cnta0, ++ans;
			ans += abs(cnta0 - cntb0) + abs(cnta1 - cntb1);
		}
		if (cnta0 + cnta1 == cntb0 + cntb1)
			printf("%lld\n", ans);
		else
			printf("-1\n");
	}
}

using Solve::Sol;

int main()
{
	Sol();
	return 0;
}

```

---

## 作者：AKPC (赞：0)

先把矩阵替换成 $01$ 数列，发现对于两个位置 $i,j$，满足 $a_i=b_j=0,a_j=b_i=1$，显然交换这两个 $0,1$ 需要花费 $|i-j|$ 的代价。

那么实际上，可以令 $prea$ 表示 $a$ 的前缀和，$preb$ 表示 $b$ 的，然后可以很显然地推算出代价 $=\sum|prea-preb|$。这个很显然。

然后延申到两行，无非就是多了上下交换操作。如果不上下交换，答案其实就是 $\sum|prea_0-preb_0|+\sum|prea_1-preb_1|$。

现在考虑加入上下交换操作，显然对于 $\forall i\in[1,n]$，若 $a_{0,i}\neq a_{1,i}$，交换 $a_{0,i},a_{1,i}$ 时代价会加上 $1$，而 $prea_{0,i},prea_{1,i}$ 分别加上 $a_{1,i},a_{0,i}$，然后增加 $1$ 的代价。

事实上，如果 $prea_{0,i}-preb_{0,i}$ 与 $prea_{1,i}-preb_{1,i}$ 的正负性不同且一正一负，那么考虑交换上下两数（当然，前面的操作是具有后效性的，可以交换前面的数字处理这一问题）。

[code](/paste/0y60dfly)。

---

## 作者：鱼跃于渊 (赞：0)

一道很棒的思维题。

## 做法

首先无解的情况是最好考虑的，只要两个矩阵内 $1$ 的数量不相同就可以输出 $-1$ 了。  
然后我们考虑只有一行的做法：  
我们设 $sa_i=\sum_{j=1}^{i} a_j$，$sb_i=\sum_{j=1}^{i}b_j$，那么要让两个序列相等的最小代价就是  
$$\sum_{i=1}^{n} \lvert sa_i - sb_i \rvert$$  
可以这么来理解：  

1. 如果 $sa_i<sb_i$，则说明序列 $a$ 的 $[1,i]$ 这段区间 $1$ 的数量要小于 $b$ 中的数量，也就是说我们要从序列 $a$ 的后面往前面调 $\lvert sa_i-sb_i \rvert$ 个 $1$ 过来，那也就是说在 $i$ 上的这个元素至少要交换 $\lvert sa_i-sb_i \rvert$ 次，那它对答案的贡献自然就是 $\lvert sa_i-sb_i \rvert$ 了。  
2. 如果 $sa_i>sb_i$，也就是 $0$ 的数量不足，同理也可以得到上述结论。  

接下来我们考虑如何把这个结论扩展到有两行的情况：  
我们设 $sa_{i,j}=\sum_{k=1}^{j} a_{i,k}$，$sb_{i,j}=\sum_{k=1}^{j} b_{i,k}$（$ i\in \{1,2\}$），则我们仿照只有一行时的结论可以列出一个式子  
$$\sum_{i=1}^{n}\lvert sa_{1,i}-sb_{1,i}\rvert + \lvert sa_{2,i}-sb_{2,i} \rvert$$
这个式子只考虑了左右交换，考虑什么时候才会上下交换，我们分类讨论一下：  

1. 如果 $sa_{1,i}<sb_{1,i},sa_{2,i}<sb_{2,i}$ 或 $sa_{1,i}>sb_{1,i},sa_{2,i}>sb_{2,i}$，显然在这种情况下上下交换只会更劣。所以此时的最小代价为 $\lvert sa_{1,i}-sb_{1,i}\rvert + \lvert sa_{2,i}-sb_{2,i} \rvert$。
2. 如果 $sa_{1,i}>sb_{1,i},sa_{2,i}<sb_{2,i}$ 或 $sa_{1,i}<sb_{1,i},sa_{2,i}>sb_{2,i}$，显然在这种情况下上下交换会减少总交换次数，也就是更优。所以此时的最小代价为 $\lvert sa_{1,i}-sb_{1,i}\rvert + \lvert sa_{2,i}-sb_{2,i} \rvert -\min \{\lvert sa_{1,i}-sb_{1,i}\rvert,\lvert sa_{2,i}-sb_{2,i} \rvert\}$。  

**注意**在实际实现上下交换时不要忘记修改前缀和。  
于是这道题就做完了，时间复杂度为 $O(n)$。  
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,suma,sumb,ans,a[3][N],b[3][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			suma+=a[i][j];
		}
	}
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++){
			cin>>b[i][j];
			sumb+=b[i][j];
		}
	}
	if(suma!=sumb){
		cout<<"-1\n";
		return 0;
	}
	for(int i=1,sa1=0,sa2=0,sb1=0,sb2=0;i<=n;i++){
		sa1+=a[1][i];sa2+=a[2][i];
		sb1+=b[1][i];sb2+=b[2][i];
		if(sa1>sb1&&sa2<sb2){
			if(sa1-sb1<sb2-sa2){
				ans+=sa1-sb1;
				sa2+=sa1-sb1;
				sa1=sb1;
			}
			else{
				ans+=sb2-sa2;
				sa1-=sb2-sa2;
				sa2=sb2;
			}
		}
		if(sa1<sb1&&sa2>sb2){
			if(sb1-sa1<sa2-sb2){
				ans+=sb1-sa1;
				sa2-=sb1-sa1;
				sa1=sb1;
			}
			else{
				ans+=sa2-sb2;
				sa1+=sa2-sb2;
				sa2=sb2;
			}
		}
		ans+=abs(sa1-sb1)+abs(sa2-sb2);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Robin_kool (赞：0)

思维题思维题思维题。

考虑 $1\times n$ 的情况怎么做。肯定是贪心，对于每个点 $i$，它产生的价值就是 $| \sum_{j=1}^i a_j - \sum_{j=1}^i b_j|$，这个不难想，从 $i=1$ 递推过来就行了。

然后变成 $2\times n$，显然只是多了一个上下交换的操作。因为上述的贡献需要取绝对值，所以假设位置 $i$ 上下交换，当且仅当上下两列前缀和更接近时更优。

最后就是细节问题，注意由于上下交换操作前缀和是动态的，两个值维护一下就做完了。

无解很简单，就是 $\sum_{i=1}^n a_{0,i}+a_{1,i}$ 是否等于 $\sum_{i=1}^n b_{0,i} + b_{1,i}$。

```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll n, A, B, a[2][N], b[2][N], s[2][N], x, y, ans; 
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("CF1700F.in", "r", stdin);
	//freopen("CF1700F.out", "w", stdout);
    n = read();
    for(int i = 0; i < 2; ++ i) for(int j = 1; j <= n; ++ j) A += (a[i][j] = read());
    for(int i = 0; i < 2; ++ i) for(int j = 1; j <= n; ++ j) B += (b[i][j] = read()), s[i][j] = s[i][j - 1] + b[i][j];
    if(A != B) return write(-1), 0;
    for(int i = 1; i <= n; ++ i){
    	x += a[0][i], y += a[1][i];
    	while(x > s[0][i] && y < s[1][i]) -- x, ++ y, ++ ans;
    	while(x < s[0][i] && y > s[1][i]) ++ x, -- y, ++ ans;
    	ans += (abs(x - s[0][i]) + abs(y - s[1][i]));
	}
	write(ans);
	return 0;
}

```

---

