# Maximum AND

## 题目描述

给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：

1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 样例 #1

### 输入

```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0```

### 输出

```
2
0
7```

# 题解

## 作者：jrxxx (赞：14)

提供一个实现较为简洁的两 $\log$ 做法。

## 思路

按位贪心。

若要某一位上答案为 $1$，对于交换后的 $\{a_i\},\{b_i\}$ 需满足：$\forall i\in[1,n]$， $a_i$ 与 $b_i$ 在这一位上 $0/1$ 取值不同。

若这一位答案能取 $1$，在这之后，为了保证这一位上的异或值不受影响，$a_i$ 和 $b_i$ 都只能和在这一位上取值相同的数交换。

也就是说，将某一位上确定取 $1$ 之后，需要将 $\{a_i\},\{b_i\}$ 按这一位上的 $0/1$ 取值分裂开，后续的判断递归进入每一个子集合，所有子集合答案取到时整体答案才能取到。

## 实现

思路很简单，但是代码一看就很细节。

这时候，我们拿出了万能的 $\text{sort}$。

将 $\{a_i\}$ 从小到大排序，$\{b_i\}$ 从大到小排序。

判断能否取 $1$ 直接遍历，看看是不是每一个位置上 $a_i,b_i$ 这一位取值都不同。

若能取 $1$，贡献给答案。接下来在每一个子集合，发现它们的下一位已经有序了（因为 $\text{sort}$ 后按二进制位从高到低的优先级有序）。

若取 $0$，这一位上取值不影响后续集合划分，将 $\{a_i\},\{b_i\}$ 在这一位上推平（$0/1$ 都可以），重新 $\text{sort}$ 消去这一位上取值对集合划分的影响。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7,V=30;
int a[N],b[N];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int T,n,i,j,ans;
	for(cin>>T;T--;)
	{
		cin>>n;
		for(i=1;i<=n;++i) cin>>a[i];
		for(i=1;i<=n;++i) cin>>b[i];
		sort(a+1,a+n+1,less<int>());
		sort(b+1,b+n+1,greater<int>());
		ans=0;
		for(i=V;~i;--i)
		{
			for(j=1;j<=n;++j)
				if((a[j]&(1<<i))==(b[j]&(1<<i)))
					break;
			if(j>n) ans|=1<<i;//贡献给答案
			else 
			{
				for(j=1;j<=n;++j)//推平成1
					a[j]|=(1<<i),b[j]|=(1<<i);
				sort(a+1,a+n+1,less<int>());//重新排序，抹去这一位上原有对集合划分的影响
				sort(b+1,b+n+1,greater<int>());
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```




---

## 作者：Ginger_he (赞：7)

## 题目描述

给定两个长度为 $n$ 的序列 $a$ 和 $b$，你可以任意排列 $b$。

令 $c_i=a_i\oplus b_i$，求 $c_1\,\&\,c_2\,\&\ldots\,\&\,c_n$ 的最大值。

## 题解
纪念[苏联小渣](https://www.luogu.com.cn/user/399286)第一次场切 Div2 D。

假设答案的第 $j$ 位为 $1$，那么由与运算的性质得到，对于每个 $i$，$c_i$ 的第 $j$ 位都为 $1$，又由异或的性质得到，$a_i$ 和 $b_i$ 的第 $j$ 位有且仅有一个 $1$。所以，**序列 $a$ 中第 $j$ 位为 $1$ 的个数和序列 $b$ 中第 $j$ 位为 $0$ 的个数是相等的。**

那么我们是否就能从高往低逐位枚举呢？考虑序列 $a=\{3,0\},b=\{2,1\}$，序列 $a$ 中的 $3$ 的最高位可以与序列 $b$ 中的 $1$ 匹配，但是第二位只能与序列 $b$ 中 $2$ 的第二位匹配。所以为了保证每次匹配的数是相同的，**我们需要考虑的是前 $j$ 位而非第 $j$ 位**。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
int t,n,a[N],b[N],ans;
bool check(int x)
{
	vector<int> u,v;
	for(int i=1;i<=n;i++)
	{
		u.push_back(a[i]&x);
		v.push_back((b[i]&x)^x);
	}
	sort(u.begin(),u.end());
	sort(v.begin(),v.end());
	return u==v;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		for(int i=29;i>=0;i--)
		{
			if(check(ans|(1<<i)))
				ans|=(1<<i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：5)

纪念第一次场切 Div 2 D。

这题思路可能讲得比较绕，所以我尽量以通俗的方式讲。

题目的意思就是给定一个序列 $a$，让你任意排列 $b$，使得 $(a_1 \oplus b_1) \text{ and }(a_2 \oplus b_2) \text{ and }... \text{ and }(a_n \oplus b_n)$ 最大。

这题和 [ARC 146 B](https://atcoder.jp/contests/arc146/tasks/arc146_b) 很像，做法是几乎一样的。

很明显的按位贪心。首先有几个引理：

- 异或：每一位相同为 $0$ 不同为 $1$。

- 按位与：若干个数按位与后，某一位结果为 $1$ 当且仅当参与运算的每个数在这一位都为 $1$。

- $2^0+2^1+2^2+...+2^{n-1}<2^n$，根据上面按位与的引理我们可以知道，当我们选择**从高位往低位贪心**时，在每一位可以选择**对于当前位而言的最优策略**。因为后面的位不管怎么选，也比不过在这一位选最优策略。这也恰好证明这题贪心是可行的。

---

首先，我们创造两个集合 $A_1$ 和 $B_1$，分别存储初始时 $a$ 中和 $b$ 中的数。

**记 $A_i$ 和 $B_i$ 为对应集合，也就是可以进行匹配的集合（即满足下标相等的集合）**

然后我们从高位往低位贪心。首先我们要找到第一个**可行位**，指的是在这一位上可以通过匹配让所有 $a_i \oplus b_i$ 按位与起来在这一位为 $1$。

根据异或的性质，两个数只有在这一位不同，它们异或起来才能在这一位为 $1$。

而集合 $A_1$ 中的数和 $B_1$ 中的数都可以分为**两种类型**：在这一位为 $1$ 和在这一位不为 $1$。于是：

- 设 $A_1$ 中有 $x_1$ 个数在这一位为 $1$，有 $y_1$ 个数在这一位为 $0$；

- 设 $B_1$ 中有 $x_2$ 个数在这一位为 $1$，有 $y_2$ 个数在这一位为 $0$。

因为我们不知道后面情况如何，只想让在这一位的结果最优。所以，我们不直接选定谁一定匹配谁，而是把在这一位可以匹配的数都放到两个对应集合中。这时这一位可以产生贡献当且仅当 $x_1=y_2,x_2=y_1$，因为要让 $a$ 中的 $1$ 和 $b$ 中的 $0$ 匹配，$a$ 中的 $0$ 和 $b$ 中的 $1$ 匹配。如果满足这个条件，我们就把原来的 $A_1$ 和 $B_1$ 集合**分裂为四个集合**：$A_2,B_2$ 和 $A_3,B_3$。其中：

- 分裂后的第一个对应集合中，$A_2$ 存储 $A_1$ 中在这一位为 $1$ 的数，$B_2$ 存储 $B_1$ 在这一位为 $0$ 的数；

- 分裂后的第二个对应集合中，$A_3$ 存储 $A_1$ 中在这一位为 $0$ 的数，$B_3$ 存储 $B_1$ 在这一位为 $1$ 的数。

同时，答案加上在这一位的贡献。

接下来的问题和上面的处理类似，**相当于上面所述的子问题**。我们不再是只分裂一个集合，而是当且仅当**当前有的所有集合都满足上述条件，再分别根据上述规则对现有的每个集合进行分裂等操作**。

下面是一开始写的形式化题解，如果感觉绕**可以跳过**，如果对于上述解释有疑问可以在评论区写出或者私信我，我会第一时间回复（~~因为这一题想起来很简单说起来挺麻烦~~

---

形式化题解：

考虑把数字划分到一些集合中，每个集合有两个关键字，分别存储 $a$ 中的一些数和 $b$ 中的一些数。设第 $i$ 个集合内原本在 $a$ 中的**某个**数为 $D_i^{(a)}$，原本在 $b$ 中的**某个**数为 $D_i^{(b)}$。考虑每个子问题，即在每一位的状态以及转移，我们从高位到低位枚举，枚举到了第 $i$ 位。对于现在有的所有集合，假设我们枚举到了第 $j$ 个集合。我们想要使得答案最优，也就是想要让这个集合某个 $D_j^{(a)}$ 和 $D_j^{(b)}$ 在第 $i$ 位不同，这样才能让它们异或起来第 $i$ 位为 $1$，对答案产生贡献。设这个集合大小为 $w$（即：这个集合有 $w$ 个 $D_j^{(a)}$，有 $w$ 个 $D_j^{(b)}$）这个集合内满足在这一位为 $1$ 的 $D_j^{(a)}$ 有 $x$ 个，满足在这一位为 $1$ 的 $D_j^{(b)}$ 有 $y$ 个。则我们称这个集合为**在第 $i$ 位合法的**当且仅当 $x+y=w$。**在第 $i$ 位合法的**，表示这个集合可以**分裂**为两个集合，其中第一个集合中原本在 $a$ 的数在这一位为 $1$，第一个集合原本在 $b$ 中的数在这一位为 $0$；第二个集合则恰恰相反。这样，我们就保证了分裂出来的两个集合中，其中任意一个集合中的任意一个原本在 $a$ 中的数，一定能在这个集合中找到一个原本在 $b$ 中的数，使得这两个数异或起来在这一位为 $1$。这么做是为了转移到下一位。如果在第 $i$ 为现有的集合中，所有集合都是**在第 $i$ 位合法的**，那么这一位就能对答案产生贡献。能对答案产生贡献，我们就要在这一位进行转移，转移的过程就是把现有的所有集合按照上述过程分裂。

可能很绕，举个例子：

假设现在有一个集合，这个集合分为 $a,b$ 两个部分，它们的 $i$ 位如下：

$D_j^{(a)}:[1,1,1,1,0,0,0]$

$D_j^{(b)}:[0,0,0,0,1,1,1]$

那么这个集合就是**在第 $i$ 位合法的**。它可以分裂成两个集合，其中每个集合的数的第 $i$ 位如下：

$\text{First }(a):[1,1,1,1]\text{ }(b):[0,0,0,0]$

$\text{Second }(a):[0,0,0]\text{ }(b):[1,1,1]$

相当于是一个分治。

最后就是初始状态：只有一个集合，并且所有数都在集合中。

---

这个做法是严格 $O(n \log a_i)$ 的，其中集合可以用 vector 实现。

注意几点：

- vector 的清空；

- 由于可以证明最终集合个数是 $\le n$ 的，而一些集合实质上并不会进行分裂，所以再进行分裂后如果分裂出的集合大小为 $0$ 要减去。（~~我才不会告诉你因为这个赛时吃了一发罚时~~

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, s1, s2, siz, sizz, pd, ans, a[100010], b[100010];
vector <int> d[100010], p[100010], dd[100010], pp[100010];
signed main(){
	scanf ("%lld", &t);
	while (t --){
		for (int i=1; i<=siz; i++) d[i].clear(), p[i].clear();
		siz = 1; ans = 0;
		scanf ("%lld", &n);
		for (int i=1; i<=n; i++){
			scanf ("%lld", &a[i]);
			d[1].push_back(i);
		}
		for (int i=1; i<=n; i++){
			scanf ("%lld", &b[i]);
			p[1].push_back(i);
		}
		for (int i=30; i>=0; i--){
			pd = 1;
			for (int j=1; j<=siz; j++){
				s1 = s2 = 0;
				for (int k=0; k<d[j].size(); k++){
					int x = a[d[j][k]];
					if ((x >> i) & 1) s1 ++;
					int y = b[p[j][k]];
					if ((y >> i) & 1) s2 ++;
				}
				if (s1 + s2 != d[j].size()){
					pd = 0;
					break;
				}
			}
			if (pd){
				for (int j=1; j<=siz; j++){
					for (int k=0; k<d[j].size(); k++) dd[j].push_back(d[j][k]), pp[j].push_back(p[j][k]);
				}
				for (int j=1; j<=siz; j++) d[j].clear(), p[j].clear();
				sizz = 0;
				ans += (1 << i);
				for (int j=1; j<=siz; j++){
					sizz ++;
					for (int k=0; k<dd[j].size(); k++){
						int x = a[dd[j][k]];
						int y = b[pp[j][k]];
						if ((x >> i) & 1) d[sizz].push_back(dd[j][k]);
						if (!((y >> i) & 1)) p[sizz].push_back(pp[j][k]);
					}
					if (d[sizz].size() == 0) sizz --;
					sizz ++;
					for (int k=0; k<pp[j].size(); k++){
						int x = a[dd[j][k]];
						if (!((x >> i) & 1)) d[sizz].push_back(dd[j][k]);
						int y = b[pp[j][k]];
						if ((y >> i) & 1) p[sizz].push_back(pp[j][k]);
					}
					if (d[sizz].size() == 0) sizz --;
				}
				for (int j=1; j<=siz; j++){
					dd[j].clear(), pp[j].clear();
				}
				siz = sizz;
			}
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：myEnd (赞：3)

原题：[戳我戳我](https://www.luogu.com.cn/problem/CF1721D)

### 题解
从 $n$ 的数据范围 $10^5$ 考虑到用一个 $\mathcal O(n \log n)$ 的复杂度的代码实现。

从要求的答案反推，考虑从高位到低位贪心枚举每一位，判断这一位是否可行。

那么考虑设一个 $mask$ 表示到这一位之前的最优答案，并假设这一位可行。

考虑到两个布尔变量：$x \oplus y$ 为真 $\Leftrightarrow x = \lnot y $。对应到 $8$ 位的 `int`，再注意到要有 `(a[i] & mask) ^ (b[i] & mask) = mask`，两个式子结合一下就有：`a[i] & mask = ~(b[i] & mask)`。 又因为 $\{b_i\}$ 可以换顺序，所以直接开一个桶统计即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[(int)1e5+7], b[(int)1e5+7];

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	
	register int T, ans = 0;
	cin >> T;
	while(T--)
	{
		cin >> n;
		for(register int i=1, t; i<=n; ++i) cin >> t, a[i] = t;
		for(register int i=1, t; i<=n; ++i) cin >> t, b[i] = t;
		
        ans = 0;
        register bool can = true;
        register map<int, int> mp;
		for(register int bi = 30; bi >= 0; --bi, can = true)
		{
            // mask = ans | (1<<bi)
			mp.clear();
			for(register int i=1; i<=n; ++i) ++mp[a[i] & (ans | (1<<bi))];
			for(register int i=1; i<=n; ++i) --mp[(~b[i]) & (ans | (1<<bi))];
			
			for(register auto it: mp) if(it.second != 0){can = false; break;}
			
			if(can) ans |= 1<<bi;
		}
		
		cout << ans << '\n';
	}
	
	cout << endl; 
	
	return 0;
}
```

---

## 作者：Hooch (赞：1)

### 题目大意

给定两个长度为 $n$ 的非负整数序列 $a,b$，定义函数 $f(a,b)$ 为：

+ 令 $c_i=a_i\oplus b_i$，$f(a,b)=c_1\ \&\ c_2\ \& \cdots \&\  c_n$。

请你重排 $b$，使得 $f(a,b)$ 最大。

### Solution

首先，因为题目要求所有 $c_i$ 都 $\&$ 起来，那么如果其中只有一个 $c_i$，那么和不做同样的，所以就不能让 $b_i$ 去 $\oplus$ 和它异或和最大的 $a_i$。

并且我们通过这条性质也能想到一种做法，就是枚举二进制下第 $i$ 位是否能成为 $1$，如果能，那么不管后面的 $i-1\sim 0$ 位能重排成怎样，我们都要这样排。原因就是 $2^0+2^1+\cdots+2^{i-1}=2^i-1$,也就是说如果这个 $i$ 不排，继续往下枚举，那么不管取得的结果有多大，都无法比第 $i$ 位为 $1$ 大。也就是**能排就排**。

然后我们考虑序列的重排，显然，判断在 $b$ 中是否能把第 $i$ 为排成 $1$，只需要在 $a$ 中记录下二进制下第 $i$ 位为 $1$ 的数的数量，并且找到 $b$ 中第 $i$ 位为 $0$ 的数量，如果两者相等，就能第 $i$ 位的并就能为 $1$。

但是还有一个问题，不能每次都对 $b$ 这么做。因为如果这一位排好了，但是上一次排好的那一位可能就被打乱了。对于这一点，我们有一种解决办法：**就是每次重排后将序列分裂**。分裂的原理是因为对于每一个二进制下第 $i$ 位相等的 $b_j$，都可以互相调换顺序而使得第 $i$ 位结果不变，而分裂成两个序列，就是把第 $i$ 位为 $0$ 的放到一个，把为 $1$ 的放到另一个。

每一次，我们同时对所有序列判断是否能重排。若所有序列都行，那么就将答案加上 $2^i$，再把所有序列分裂。若不行，那么直接进入下一个回合，因为不管怎样排都没有影响。

由于每一次序列长度和都为 $n$，一共执行 $\log a$ 次，所以最终时间复杂度为 $Θ(n\log a)$。

### 代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i(j); i <= n; ++i)
#define rep2(i, j, n) for (int i(j); i >= n; --i)
using namespace std;
const int N = 1e5 + 5;
struct node {
	vector <int> a, b; int n; 
	inline void print() {
		cout << "!!!\n";
		rep1(i, 0, n - 1) cout << a[i] << ' '; cout << '\n';
		rep1(i, 0, n - 1) cout << b[i] << ' '; cout << '\n';
		cout << '\n';
	}
} f;
vector <node> g;
inline bool check(node x, int p) {
	int b1, b0; b0 = b1 = 0;
	rep1(i, 0, x.n - 1) if (x.b[i] & (1 << p)) b1++; else b0++;
	rep1(i, 0, x.n - 1) {
		int v = (x.a[i] & (1 << p));
		if (v) {
			if (!b0) return false;
			--b0;
		} else {
			if (!b1) return false;
			--b1;
		}
	} return true;
}
inline void split(node x, int id, int p) {
	node a, b; vector <int> P, Q; a.n = b.n = 0;
	int k = 0, l = 0;
	rep1(i, 0, x.n - 1) if (x.b[i] & (1 << p)) P.push_back(x.b[i]); else Q.push_back(x.b[i]);
	rep1(i, 0, x.n - 1) {
		int v = (x.a[i] & (1 << p));
		if (v) {
			a.n++;
			a.a.push_back(x.a[i]);
			a.b.push_back(Q[k++]);
		} else {
			b.n++;
			b.a.push_back(x.a[i]);
			b.b.push_back(P[l++]);
		}
	}
	if (a.n && b.n) g[id] = a, g.push_back(b);
	else if (b.n) g[id] = b;
	else g[id] = a;
}
main(void) {
	ios::sync_with_stdio(false);
	int T; cin >> T; while (T--) {	
		cin >> f.n; f.a.clear(); f.b.clear(); g.clear();
		rep1(i, 1, f.n) {int x; cin >> x; f.a.push_back(x);}
		rep1(i, 1, f.n) {int x; cin >> x; f.b.push_back(x);}
		g.push_back(f); int ans = 0;
		rep2(p, 30, 0) {
			bool flg = 0;
			rep1(i, 0, g.size() - 1) {
				if (!check(g[i], p)) {flg = 1; break;}
			}
			if (!flg) { 
				rep1(i, 0, g.size() - 1) split(g[i], i, p);
				ans += (1 << p);
			}
		} cout << ans << '\n';
	}
}
```

---

## 作者：Sellaris (赞：1)

- 简单题，赛时写挂了，后来发现是低级错误。可惜了。

- 写的是两只 $\log$ 但是跑得飞快。

- 首先按从高到低位贪心，发现本位若对答案有贡献则应该从原来的一个集合划分为两个集合。我们把从两个数组划分出来的集合记为 $A_i$ 和 $B_i$ 。初始时只有两个集合 $A_1$ 和 $B_1$ 。请注意，每个 $A_i$ 和 $B_i$ 显然是一一对应的。

- 考虑最高的合法的位 $j$ ，容易发现合法时当且仅当 $j$ 位上所有 $A_i$ 和对应的 $B_i$ 的 $0$ 和 $1$ 数量相反，因为最后是按位与保留。这样答案就应该贪心的累加，并从每个集合中按本位分类出两个新的集合。以此类推，往下处理。

- 对于高位没有贡献就应该直接舍去高位。对于具体实现的时候，对 $b$ 数组任意排序等价于对两个数组按大小相反排序，我们发现排序后的处理到的当前位必定是连续的 $0$ 段和 $1$ 段，于是我们直接拿一个 STL 维护下标来分段表示集合，并对分段的集合进行排序和反转，这样就实现了一个丑陋又简易的分治算法。


```cpp
///*****Sellaris*****///

//I will win stars full sleeves in my dream.

#pragma once
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
#include <bits/extc++.h>
#include<ext/rope>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>//用tree
#include<ext/pb_ds/hash_policy.hpp>//用hash
#include<ext/pb_ds/trie_policy.hpp>//用trie
#include<ext/pb_ds/priority_queue.hpp>//用priority_queue

#define ll long long

typedef std::pair<int,int> pii;

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

const int maxn=2e5+10;
const int mo=1e9+7;

inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}

set<int> pos;
int a[maxn];
int b[maxn];
int n;
inline void solve(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	reverse(a+1,a+1+n);
	
	int ans=0;
	///for(int i=1;i<=n;i++) cout<<(bitset<5>)a[i]<<" ";cout<<"\n";
	///for(int i=1;i<=n;i++) cout<<(bitset<5>)b[i]<<" ";cout<<"\n";
	pos.clear(),pos.insert(1),pos.insert(n+1);
	for(int j=29;j>=0;j--){
		//for(int i=1;i<=n;i++) cout<<(bitset<5>)a[i]<<" ";cout<<"\n";
		//for(int i=1;i<=n;i++) cout<<(bitset<5>)b[i]<<" ";cout<<"\n";
		auto ed=pos.begin();ed++;
		auto bg=pos.begin();
		int f=0;
		while(ed!=pos.end()){
			int cnta=0,cntb=0;
			for(int i=(*bg);i<(*ed);i++){
				if(((a[i])&(1<<j))) cnta++;
				if(!((b[i])&(1<<j))) cntb++;	
			}
			if(cnta!=cntb) f=1;
			//cout<<"f="<<f<<" l="<<(*bg)<<" r="<<(*ed)<<" cnta1="<<cnta<<" cntb0="<<cntb<<" ans="<<ans<<endl;
			ed++;bg++;
		}
		if(f==0) {
			ans^=(1<<j);//cout<<" ans="<<ans<<endl;
			for(int i=2;i<=n;i++){
				if(((a[i-1])&(1<<j)) && ((a[i])&(1<<j))==0 ) pos.insert(i);
			}
		}else{
			for(int i=1;i<=n;i++){
				a[i]&=(1<<j)-1;
				b[i]&=(1<<j)-1;
			}
			
		}
		ed=pos.begin();ed++;
		bg=pos.begin();
		while(ed!=pos.end()){
			sort(a+(*bg),a+(*ed));
			sort(b+(*bg),b+(*ed));
			reverse(a+(*bg),a+(*ed));
			ed++;bg++;
		}
		//for(int i=1;i<=n;i++) cout<<(bitset<5>)a[i]<<" ";cout<<"\n";
		//for(int i=1;i<=n;i++) cout<<(bitset<5>)b[i]<<" ";cout<<"\n\n";
	}
	cout<<ans<<endl;
}
```


---

## 作者：naught (赞：0)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18500396)

# Maximum AND

## 题外话

用 `sort` 肘过去了？

## 题面翻译

给定数组 $a$ 和 $b$，重排 $b$ 数组，求 $a_i \oplus b_i$ 之后与和的最大值。

## Solution

不难想到按位贪心。从最高位开始，逐位讨论是否能为 $1$。

接下来有一个做法：

先将 $a$ 数组升序排序， $b$ 数组降序排序。为什么这么排？因为这样最高位越容易异或成 $1$。

接下来按位计算，如果可以使该位值为 $1$，那么就让答案加上该位，反之，跳过该位，除去该位影响后再排序，具体怎么做到？很简单，所有 $a_i$ 和 $b_i$ 都把这位变为 $1$ 或 $0$ 即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string.h>
#include <cstring>
using namespace std;

typedef long long ll;
#define Maxn 100005
#define Maxlen 30
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, a[Maxn], b[Maxn], ans;

bool smaller(int a, int b) { return a < b; }

bool bigger(int a, int b) { return a > b; }

int main()
{
    int _ = read();
    while(_--)
    {
        n = read(); ans = 0;
        fo(i, 1, n) a[i] = read();
        fo(i, 1, n) b[i] = read();
        sort(a + 1, a + n + 1, smaller),
        sort(b + 1, b + n + 1, bigger);
        fr(pos, 0, Maxlen) { // 从高到低位考虑。
            bool could_be_one = true; int pos_num = (1 << pos);
            fo(i, 1, n) if( (a[i] & pos_num) == (b[i] & pos_num) ) { could_be_one = false; break; }
            if( could_be_one ) ans |= pos_num; // 可以，则加上该位
            else // 不可以
            {
                fo(i, 1, n) a[i] |= pos_num, b[i] |= pos_num; // 把所有数的该位都变为 1 。
                sort(a + 1, a + n + 1, smaller), 
                sort(b + 1, b + n + 1, bigger); // 重新排序。
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

## Tips

没有。硬要说的话，$ans$ 多测要清为 $0$？

---

## 作者：可爱的小棉羊 (赞：0)

这道题被搬到学校考试的 T3，又成为了 rnk1。

好的我们来看这道题，对于这种位运算结果最大的东西，我们有一个显而易见的贪心：从高往低位去贪。

我们有了这个前提就能很简单解决这道题了。

### Sol

考虑记录三元组 $(l,r,step)$，表示考虑到第 $step$ 位的区间 $[l,r]$。

显然如果这个区间可以使 $step$ 位为 $1$ 当且仅当 **$a$ 中这位为 $0$ 的个数等于 $b$ 中为 $1$ 的个数**。

那么就很简单了，一开始我们考虑 $(1,n,29)$，我们分治的去解决：

如果所有的考虑的区间中有一个 $(step,l,r)$ 无法满足上面的条件，那么这位无法为 $1$，所有 $step\to (step-1)$。

否则我们分为两个子问题，继续分治。

我用了个队列维护了这个过程，时间复杂度 $O(n\log n)$。

代码很烂，建议不要学：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int step;
	int l,r;
};
int t; 
int cnt;
int n,a[200005],b[200005];
queue<node>q;
stack<node>st;
node  calc(int step,int l,int r){
	node x;
	x.step=step;
	x.l=l;
	x.r=r;
	return x;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		while(!q.empty())q.pop();
		while(!st.empty())st.pop();
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		int ans=0;
		q.push(calc(29,1,n));
		for(int i=29;i>=0;i--){
			bool f=0;
			while(!q.empty()){
				node u=q.front();
				
				int k=0,k2=0;
				for(int j=u.l;j<=u.r;j++){
					if(a[j]&(1<<i))k++;
					if(!(b[j]&(1<<i)))k2++;
				}
				if(k!=k2)f=1;
				q.pop();
				st.push(u);
			}
			if(f==1){
				while(!st.empty()){
					node u=st.top();
					st.pop();
					u.step--;
					q.push(u);
				}
				continue;
			}
			ans|=(1<<i);
			while(!st.empty()){
				node u=st.top();
				st.pop();
				int pos=u.l;
				for(int j=u.l;j<=u.r;j++){
					if(a[j]&(1<<i)){
						swap(a[j],a[pos]);
						pos++;
					}
				}
				pos=u.l;
				for(int j=u.l;j<=u.r;j++){
					if(!(b[j]&(1<<i))){
						swap(b[j],b[pos]);
						pos++;
					}
				}
				if(pos!=0)q.push(calc(i-1,pos,u.r));
				if(pos>u.l)q.push(calc(i-1,u.l,pos-1));
			}
		}
		cout<<ans<<"\n";
	} 
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1721D%20Maximum%20AND)

# 思路

经典贪心，二进制拆分后，从高位往低位枚举。

如果答案的第 $i$ 位为 $1$，说明 $\forall p \in [1,n]$，$c_p$ 的第 $i$ 位都是 $1$。进而由异或的性质得到，$\forall p \in [1,n]$，$a_p$ 的第 $i$ 位与 $b_p$ 的第 $i$ 位不同。

但是单单判断第 $i$ 位是不行的，需要将前 $i$ 位一起判断。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,ans;
int arr[N],brr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline bool check(int x){
    vector<int> a,b;
    for (re int i = 1;i <= n;i++){
        a.push_back(arr[i] & x);
        b.push_back((brr[i] & x) ^ x);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    return (a == b);
}

inline void solve(){
    ans = 0;
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++) brr[i] = read();
    for (re int i = 30;~i;i--) ans |= (check(ans | (1 << i)) << i);
    printf("%d\n",ans);
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Masna_Kimoyo (赞：0)

这个题应该说有两个关键点

第一个是由题目意思得出。

令 $f(a,b)$ 为一些二进制数的和

如果当前二进制位能够加入答案，那么首先，其数量在 AB 当中加起来是 $n$ 。其次，组合时，AB 的这一位必须全部错开。

第二个是实现方面。

贪心思想告诉我们，如果你选了当前这二进制位，前面的所有位加起来都没有你大。所以我们肯定是从大的开始选。也就是枚举时从高位到低位

第一位肯定是最简单的，只需要判数量，但这没有完。到了第二位，其实和第一位产生了联系，他们的解不是相互独立的。

因为第一位的顺序其实已经差不多确定好了。准确来讲，是确定了组合，但是没有确定排列。

而我们要找到第二位是否有解，那么就要从第一位已经产生的排列中继续组合。由于接下来的每一位都是用的相同方式，所以我想到了递归。

但这样并不好写（其实是蔡），我们继续考虑性质

既然每一位的答案都互不独立，都有联系，那我们为什么不把他们考虑成一个整体呢。

于是：

记枚举到当前位时答案为 $ans$ ，用二进制将答案表示出来，再把它丢进 AB 里看看，你会发现，如果有一个组合满足条件，那么 A 中装 $ans$ 的那些位取反，就等于在同一个下标下，B 中本来装 $ans$ 的那些位。

这时就只有两种情况，$ans$ 或者 $ans \operatorname{xor} (2^k - 1)
$ ，而且两者数量相同，不然就不能做到完全匹配。

`map` 可以方便地维护相同数据的数量信息。所以我们用它。

由于我懒，所以就直接搞了 `auto` ，其实只需要找一下当前 `map` 的首和尾是否满足数量相同，因为中间的都包含在他们之间了。

于是代码：

```cpp
#include<bits/stdc++.h>
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
int n;
const int N=1e5+5;
int a[N],b[N],cnt[100];
/*
inline int Solve(){
    n=read();
    int ans=0;
    memset(cnt,0,sizeof(cnt));
    for(register int i=1;i<=n;++i)  a[i]=read();
    for(register int i=1;i<=n;++i)  b[i]=read();
    for(register int i=0;i<30;++i){
        for(register int j=1;j<=n;++j)
            cnt[i]+=(((1<<i)&a[j])==(1<<i))+(((1<<i)&b[j])==(1<<i));
    }
    for(register int i=0;i<30;++i)
        cout<<cnt[i]<<' ';cout<<" cnt\n";
    for(register int i=29;~i;--i){
        if(cnt[i]!=n) continue;
        ans|=(1<<i);
    }
    return ans;
}
*/
inline int Solve(){
    n=read();
    for(register int i=1;i<=n;++i)  a[i]=read();
    for(register int i=1;i<=n;++i)  b[i]=read();
    int ans=0;
        map<int,int> mp1,mp2;
    for(register int i=29;~i;--i){
        ans|=(1<<i);
        mp1.clear(),mp2.clear();
        for(register int j=1;j<=n;++j)
            mp1[a[j]&ans]++,mp2[b[j]&ans]++;
        for(auto x:mp1){
            int u=x.first;
            if(mp2[u^ans]!=x.second){
                ans-=(1<<i);
                break;
            }
        }
    }
    return ans;
}
signed main(){
    int T=read();
    while(T--){
        printlf(Solve());
    }
    return 0;
}

```

---

## 作者：BigSmall_En (赞：0)

### [CF1721D](http://codeforces.com/problemset/problem/1721/D) Maximum AND

> 给你两个数组 $a,b$。定义一个数组 $c$，其中每个元素 $c_i=a_i\oplus b_i$。定义函数 $f(a,b)=c_1\& c_2\&\cdots \& c_n$。求一个 $b$ 的排列 $b'$，使得 $f(a,b')$ 的值最大，输出这个最大值。
>
> $\oplus$ 为按位异或，$\& $ 为按位与。
>
> 数据范围：$n\leq 10^5,0\leq a_i,b_i\leq 2^{30}$。

一个显然的点是 $a,b$ 的地位是等价的，也可以对 $a$ 数组进行排列。

最后答案是所有 $c_i$ 按位与的形式。根据我们处理这类位运算的思想，需要从高位往低位贪心，高位答案能取 $1$ 就取 $1$。

答案的第 $k$ 位要取 $1$，其必要条件是所有 $c_i$ 的这一位取值都要是 $1$。同时只有 $0\oplus 1=1\oplus 0=1$，这也就说明了如果 $a_i$ 这一位为 $1$，那么 $b_i$ 这一位为 $0$；如果 $a_i$ 这一位为 $0$，$b_i$ 这一位为 $1$。最终可以得出 $a,b$ 中所有数的第 $k$ 位为 $1$ 的个数为 $n$。

所以在满足第 $k$ 位可以取 $1$ 的前提下，我们将 $a,b$ 重新排序，重排后的 $a$ 数组第 $k$ 位为 $1$ 的在前，为 $0$ 的在后；$b$ 数组则反之，$0$ 在前，$1$ 在后。这样得到的数组上下异或起来就是满足这一位的与为 $1$ 的。同时假设重排后 $a$ 数组 $k$ 位为 $0$ 的位置为 $mid$，那么 $[1,mid-1]$ 和 $[mid,r]$ 这两个区间内的数随意排列也是满足这一位为 $k$ 这一条件的。

显然这是一个分治的过程。但是如果对于更低的位我们也要取 $1$，显然此时**每一个**子区间都要合法。一旦这一位不能取 $1$，那么这一位的所有子区间都不用再分治了，直接继承到更更低的位即可。

#### 代码实现

赛时代码，及其繁琐，有很大的精简空间。

```cpp
const int N=100005;
int n,a[N],b[N];bool ans[32];

int tmp;
inline bool cmpa(int x,int y){return ((x>>tmp)&1)>((y>>tmp)&1);}
inline bool cmpb(int x,int y){return ((x>>tmp)&1)<((y>>tmp)&1);}

typedef pair<int,int>ttfa;
ttfa lis[N],que[N];int tot,top;
inline bool check(int loc,int l,int r){
	int bota=0,botb=0,len=r-l+1;
	for(int i=l;i<=r;++i){
		if((a[i]>>loc)&1)++bota;
		if((b[i]>>loc)&1)++botb;
	}
	if(bota+botb!=len)return 0;
	return 1;
}
inline void divs(int loc,int l,int r){
	//printf("divs %d %d %d\n",loc,l,r);
	int bota=0,botb=0;
	for(int i=l;i<=r;++i){
		if((a[i]>>loc)&1)++bota;
		if((b[i]>>loc)&1)++botb;
	}
	tmp=loc;
	sort(a+l,a+r+1,cmpa);
	sort(b+l,b+r+1,cmpb);
	if(bota!=0)que[++top]={l,l+bota-1};
	if(botb!=0)que[++top]={r-botb+1,r};
}
inline void solve(){
	n=read();
	memset(ans,1,sizeof(ans));
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)b[i]=read();
	lis[tot=1]={1,n};
	for(int k=30;k>=0;--k){
		for(int i=1;i<=tot;++i){
			if(!check(k,lis[i].first,lis[i].second))
				{ans[k]=0;break;}
		}
		if(ans[k]==0)continue;
		top=0;
		for(int i=1;i<=tot;++i)
			divs(k,lis[i].first,lis[i].second);
		tot=top;
		for(int i=1;i<=tot;++i)
			lis[i]=que[i];
	}
	int lasans=0;
	for(int i=30;i>=0;--i)
		if(ans[i])lasans|=(1<<i);
	printf("%d\n",lasans);
}
int main(){
	int T=read();
	while(T--)solve();
	return 0;
}
```



---

## 作者：happybob (赞：0)

赛时过了 ABC 就没做了，赛后这题没看题解也做出来了。

考虑按位贪心，即对于二进制从高到低判断每位是否可以为 $1$。因为 $f(a,b)$ 是按位与运算，所以若 $f(a,b)$ 二进制下的第 $i$ 位为 $1$，那么所有 $a_i \oplus b_i$ 二进制下的第 $i$ 位必定也为 $1$。

由于操作为异或，所以必定是 $1$ 和 $0$ 或 $0$ 和 $1$，遍历每一位的时候判断能否构造这一位为 $1$ **且不与以前的任意一位冲突**，如果能，则把 $0$ 和 $1$ 分组，一开始每一组分成两组，一组 $0$，一组 $1$。接下来每一位枚举时，只能在组内打乱顺序而不能在组和组之间交换。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <vector>
using namespace std;

const int N = 1e5 + 5;

int n, a[N], b[N], t, bel[N], bel2[N];
vector<int> A[N][2], A2[N][2];

inline bool pd(int x, int i)
{
	return (x & (1 << (i - 1)));
}

int main()
{
	scanf("%d", &t);
	for (int lp = 1; lp <= t; lp++)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]), bel[i] = bel2[i] = 1;
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
		int ret = 0;
		for (int i = 30; i >= 1; i--)
		{
			int maxn = 0;
			for (int j = 1; j <= n; j++)
			{
				A[j][0].clear();
				A[j][1].clear();
				A2[j][0].clear();
				A2[j][1].clear();
			}
			for (int j = 1; j <= n; j++)
			{
				//pn[bel[j]][pd(b[j], 1)].push_back()
				A[bel[j]][pd(b[j], i)].push_back(j);
				A2[bel2[j]][pd(a[j], i)].push_back(j);
				maxn = max(maxn, bel[j]);
			}
			int now = 0;
			bool f = false;
			for (int j = 1; j <= maxn; j++)
			{
				if (A[j][0].size() != A2[j][1].size() || A[j][1].size() != A2[j][0].size())
				{
					f = true;
					break;
				}
			}
			if (f) continue;
			for (int j = 1; j <= maxn; j++)
			{
				if (A[j][0].size()) now++;
				for (int k = 0; k < A[j][0].size(); k++)
				{
					bel[A[j][0][k]] = now;
				}
				for (int k = 0; k < A2[j][1].size(); k++)
				{
					bel2[A2[j][1][k]] = now;
				}
				if (A[j][1].size()) now++;
				for (int k = 0; k < A[j][1].size(); k++)
				{
					bel[A[j][1][k]] = now;
				}
				for (int k = 0; k < A2[j][0].size(); k++)
				{
					bel2[A2[j][0][k]] = now;
				}
			}
			if (now) ret += (1 << ((i - 1)));
		}
		printf("%d\n", ret);
	}
	return 0;
}
```



---

## 作者：XiaoQuQu (赞：0)

更好的阅读体验与 CF1721 A-D 题解：[My Blog](blog.zshfoj.com)。

感觉上是比较巧妙的位运算题目，对于这种二进制下的位运算操作一般考虑贪心（因为有高位必定大于所有低位的优秀贪心性质）。

因为对 $c$ 进行了一个与运算，也就是说只有 $c$ 的每一个数的第 $k$ 位为 $1$，最终答案的第 $k$ 位才为 $1$。因为有上述的贪心性质，我们直接尝试让 $a,b$ 匹配，使得答案的最高位为 $1$。$a,b$ 配对后答案的第 $k$ 位为 $1$ 当且仅当 $a$ 中所有的数的前 $k$ 位的 $1$ 的个数恰好等于 $b$ 中的所有的数的前 $k$ 位 $0$ 的个数。详细匹配细节看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN];

void work()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    int k = 0;
    for (int t = 29; t >= 0; --t) {
        k |= 1 << t;
        map<int, int> mp;
        for (int i = 1; i <= n; ++i) {
            mp[a[i] & k]++;
            mp[~b[i] & k]--;
        }
        bool flag = true;
        for (int i = 1; i <= n; ++i) 
            if (mp[a[i] & k] != 0) 
                flag = false;
        if (!flag) k ^= (1 << t);
    }
    cout << k << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        work();
    }
    return 0;
}
```


---

