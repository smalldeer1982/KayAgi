# Game with Stones

## 题目描述

Bob decided to take a break from calculus homework and designed a game for himself.

The game is played on a sequence of piles of stones, which can be described with a sequence of integers $ s_1, \ldots, s_k $ , where $ s_i $ is the number of stones in the $ i $ -th pile. On each turn, Bob picks a pair of non-empty adjacent piles $ i $ and $ i+1 $ and takes one stone from each. If a pile becomes empty, its adjacent piles do not become adjacent. The game ends when Bob can't make turns anymore. Bob considers himself a winner if at the end all piles are empty.

We consider a sequence of piles winning if Bob can start with it and win with some sequence of moves.

You are given a sequence $ a_1, \ldots, a_n $ , count the number of subsegments of $ a $ that describe a winning sequence of piles. In other words find the number of segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ), such that the sequence $ a_l, a_{l+1}, \ldots, a_r $ is winning.

## 说明/提示

In the first test case, Bob can't win on subsegments of length $ 1 $ , as there is no pair of adjacent piles in an array of length $ 1 $ .

In the second test case, every subsegment is not winning.

In the fourth test case, the subsegment $ [1, 4] $ is winning, because Bob can make moves with pairs of adjacent piles: $ (2, 3) $ , $ (1, 2) $ , $ (3, 4) $ . Another winning subsegment is $ [2, 3] $ .

## 样例 #1

### 输入

```
6
2
2 2
3
1 2 3
4
1 1 1 1
4
1 2 2 1
4
1 2 1 2
8
1 2 1 2 1 2 1 2```

### 输出

```
1
0
4
2
1
3```

# 题解

## 作者：Alex_Wei (赞：8)

> CF1584E. [Game with Stones](https://codeforces.ml/problemset/problem/1584/E) *2300

首先分析满足条件的区间 $[l,r]$ 的性质：由于 $a_l$ 只能与 $a_{l+1}$ 匹配，所以 $a_{l+1}\geq a_l$。同理，$l+1$ 处剩下来的 $a_{l+1}-a_l$ 只能与 $a_{l+2}$ 匹配，故 $a_{l+2}\geq a_{l+1}-a_l$。依次类推，得到对于任意前缀 $[l,m]$ 都有 $a_m+a_{m-2}+\cdots\geq a_{m-1}+a_{m-3}+\cdots$ 即 $a_m+a_{m-2}+\cdots-a_{m-1}-a_{m-3}-\cdots\geq 0$。显然还需满足 $a$ 的奇数下标处的和等于偶数下标处的和，即 $a_r+a_{r-2}+\cdots= a_{r-1}+a_{r-3}+\cdots$。

一般这种数子区间问题都使用**增量法**实时维护 $r\to r+1$ 的所有 $l$ 的合法性，即维护 $s_{l,r}=a_r+a_{r-2}+\cdots-a_{r-1}-a_{r-3}-\cdots$。注意到这相当于给所有 $s_{l,r}$ 取反后加上 $a_{r+1}$，然后查询 $s_{l,r+1}=0$ 的位置 $l$ 的个数。由于操作是全局的，因此可以用 `map` 维护（`multiset` 求数的个数是 $\mathcal{O}(\log n+\rm count)$ 的，无法接受）。时间复杂度 $\mathcal{O}(n\log n)$。

**启示：增量法做子区间计数问题**。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair <ll, ll>

const int N = 3e5 + 5;
ll n, ans;
map <ll, int> s;
int main(){
	int T; cin >> T;
	while(T--) {
		cin >> n, ans = 0, s.clear();
		for(ll i = 1, a, ne = 1, del = 0; i <= n; i++) {
			cin >> a, ne ^= 1, del = -del + a;
			ne ? s[del - a]++ : s[a - del]++;
			while(s.size()) {
				if(ne) {
					pll it = *--s.end();
					if(it.first > del) s.erase(--s.end());
					else break;
				} else {
					pll it = *s.begin();
					if(it.first < -del) s.erase(s.begin());
					else break;
				}
			} ans += ne ? s[del] : s[-del]; 
		} cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：wyr_ (赞：5)

## 题意
- 定义在长度为 $k$ 的序列 $s=\{s_1,\ldots,s_k\}$ 上的「操作」为选择一个正整数 $i$ 满足 $1\leq i< k$ 且 $s_i\neq0,s_{i+1}\neq0$，将 $s_i$ 和 $s_{i+1}$ 减去 $1$。 

- 定义一个序列「winning」，当且仅当存在一种操作序列（可以为空）使依次操作后 $s$ 满足 $\forall i\in [1,k],s_i=0$。

- 给定长度为 $n$ 的序列 $a=\{a_1,\ldots,a_n\}$，求它有多少个非空连续子段是「winning」的。

- $1\leq n\leq 3\times 10^5,0\leq a_i\leq10^9$
## 思路

记操作 $(i,i+1)$ 为将第 $i$ 和 $i+1$ 个数减去 $1$。下面一段中的 $s_i$ 都指其初始值。

看到这种题，一般都要手动模拟一下。 对于一个序列 $s$，我想让它全变为 $0$，怎么操作？从左往右看，首先 $s_1$ 要变为 $0$，由于题目中要求相邻两个一起操作，所以 $s_1$ **只能**和 $s_2$“绑定”，必须进行 $s_1$ 次操作 $(1,2)$。 操作完后，第 $2$ 个数变为 $s_2-s_1$。 再考虑 $s_2$ 怎样变为 $0$，由于 $s_1$ 已经是 $0$ 了，所以它**只能**和 $s_3$“绑定”，进行 $s_2-s_1$ 次操作 $(2,3)$。

把每个数**第一次**被操作时序列发生的变化列出来看看？（我们不关心第二次操作，因为第二次操作后它必须变为 $0$）
$$
\begin{aligned}
s_1&\leftarrow 0\\
s_2&\leftarrow s_2-s_1\\
s_3&\leftarrow s_3-(s_2-s_1)\\
s_4&\leftarrow s_4-[s_3-(s_2-s_1)]\\
&\vdots\\
s_k&\leftarrow s_k-(\ldots-(s_2-s_1)\ldots)
\end{aligned}$$
展开看看？
$$
\begin{aligned}

s_1&\leftarrow 0\\
s_2&\leftarrow s_2-s_1\\
s_3&\leftarrow s_3-s_2+s_1\\
s_4&\leftarrow s_4-s_3+s_2-s_1\\
&\vdots\\
s_k&\leftarrow

\begin{cases}
s_k-s_{k-1}+\cdots+s_1 &k\equiv1\pmod 2\\
s_k-s_{k-1}+\cdots-s_1 &k\equiv 0\pmod 2
\end{cases}

\end{aligned}
$$
如果所有操作都能顺利进行，那么 $\forall i\in [1,k),s_i=0$。 保证之前的操作符合规则的前提下，判断 $s_k$ 是否为 $0$，就可以知道序列是否「winning」了。 同时我们发现另一个规律——$s_k$ 最终变成的数是一个正负交替和。

由于操作时一个数变为 $0$ 后就不能再操作了，所以任意一步操作后不应该出现负数。 又因为最后一步结束后所有数都为 $0$，「winning」子段 $\{a_j,\ldots,a_i\}$ 满足：
$$
\begin{aligned}
a_{j+1}-a_j&\geq0\\
a_{j+2}-a_{j+1}+a_j&\geq0\\
a_{j+3}-a_{j+2}+a_{j+1}-a_j&\geq0\\
&\vdots
\end{aligned}
$$
$$
\begin{cases}
a_i-a_{i-1}+\cdots+a_j=0 & i-j+1\equiv 1 (\mod 2)\\
a_i-a_{i-1}+\cdots-a_j=0 & i-j+1\equiv 0 (\mod 2)
\end{cases}
$$
（实际上长度至少为 $2$ 就行了，为了表达清楚多写几项）

用自然语言概括起来是两条要求：
1. 整个序列的「下标最大一项为正」的正负交替和等于 $0$。
2. 「从开头到中间任意项」的「下标最大一项为正」的正负交替和大于等于 $0$。

至此，问题转化为对每一个 $i\in [1,n]$，求有多少个 $j\in [1,i]$，满足 $a$ 的子区间 $[j,i]$ 的「$a_i$ 对应项为正」的正负交替和满足上述要求。

将每个 $i$ 的答案求和即为最终答案。 
## 做法
### 暴力
枚举 $i$，再暴力枚举 $j$，然后一个个判断中间的数是否符合规则，时间复杂度是 $O(n^3)$ 的。 由于只需要求 $j$ 的数量而不是具体值，考虑用某种数据结构优化。 
### 正解
由于奇数下标项和偶数下标项的符号不同，想到开两个数据结构 $odd$ 和 $even$，当枚举到 $i$ 时分别存左端点为 $1\sim i-1$，右端点为 $i-1$，奇数项下标为正/负的交替和。 如 $i=5$ 时，$odd$ 中有：
$$\begin{aligned}
a_1-a_2+a_3-a_4&\\
-a_2+a_3-a_4&\\
a_3-a_4&\\
-a_4&
\end{aligned}$$
$even$ 中有：
$$\begin{aligned}
-a_1+a_2-a_3+a_4&\\
a_2-a_3+a_4&\\
-a_3+a_4&\\
a_4&
\end{aligned}$$
当枚举一个 $i$ 时，很明显对应 $j$ 的个数就是数据结构 $odd$ 或 $even$（取决于 $i$ 的奇偶）中等于 $-a_i$ 的数的个数。 然后，数据结构中每个数加上 $a_i$（或 $-a_i$），再插入 $a_i$（或 $-a_i$）。

 同时为了符合第2条要求，还要再删去以正项结尾且小于 $0$ 的子段交替和；再删去以负项结尾且大于 $0$ 的子段交替和（此时它的相反数，也就是对应的以正项结尾的交替和小于 $0$）。 以上例子中 $odd$ 变为：
$$\begin{aligned}
a_1-a_2+a_3-a_4+a_5&\\
-a_2+a_3-a_4+a_5&\\
a_3-a_4+a_5&\\
-a_4+a_5&\\
a_5
\end{aligned}$$
然后继续枚举下一个 $i$。

那么，需要维护的操作有：
1. 所有数加上一个数。
2. 插入一个数。
3. 查找数据结构内等于给定值的数的个数。
4. 删除所有小于 $0$ 或大于 $0$ 的数。

显然用C++ STL map可以实现：
1. 全局标记，$O(1)$。
2. 将 $x$ 插入时，键 $x$ 对应的值加 $1$，$O(\log n)$。
3. 查询 $x$ 的个数时结果即为键 $x$ 对应的值，$O(\log n)$。
4. 单个数删除 $O(\log n)$，总时间复杂度见后文。


具体的删除操作是，在插入 $a_i$（或 $-a_i$）后，若枚举到的 $i$ 为奇数，此时 $even$ 中所有交替和都以负项结尾，删去 $odd$ 中小于 $0$ 的数和 $even$ 中大于 $0$ 的数；若枚举到的 $i$ 为偶数，此时 $odd$ 中所有交替和都以负项结尾，删去 $odd$ 中大于 $0$ 的数和 $even$ 中小于 $0$ 的数。

别忘了题面中 $0\leq a_i\leq10^9$！当 $a_i=0$ 时，它自己能成为一个合格的子段，所以枚举到 $a_i=0$ 时答案加 $1$。

对删除操作的时间复杂度分析：$\forall j \in [1,n]$，数据结构中删除了以 $a_j$ 为首项的某个子段交替和后，不会再次出现以 $a_j$ 为首项的不同子段交替和。 所以删除操作至多进行 $O(n)$ 次。

总时间复杂度 $O(n\log n)$。

## Code
```cpp
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
void ins(map<ll,ll> &m,ll &dt,ll k){
	dt+=k;
	if(m.find(k-dt)==m.end())m[k-dt]=0;
	++m[k-dt];
}
void ins2(map<ll,ll> &m,ll &dt,ll k,ll cnt){
	dt+=k;
	if(m.find(k-dt)==m.end())m[k-dt]=0;
	m[k-dt]+=cnt;
}
ll fin(map<ll,ll> &m,ll &dt,ll k){
	if(m.find(k-dt)==m.end())return 0;
	return m[k-dt];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		map<ll,ll>odd,even;
		ll dt1=0,dt2=0,ans=0;
		for(int i=1,a;i<=n;++i){
			cin>>a;
			if(a==0){
				++ans;
			}
			if(i&1){
				ans+=fin(odd,dt1,-a);
				ins(odd,dt1,a);
				ins(even,dt2,-a);
				while(odd.empty()?0:odd.begin()->first+dt1<0)odd.erase(odd.begin());
				while(even.empty()?0:(--even.end())->first+dt2>0)even.erase(--even.end());
			}
			else{
				ans+=fin(even,dt2,-a);
				ins(even,dt2,a);
				ins(odd,dt1,-a);
				while(odd.empty()?0:(--odd.end())->first+dt1>0)odd.erase(--odd.end());
				while(even.empty()?0:even.begin()->first+dt2<0)even.erase(even.begin());
			}
		}
		cout<<ans<<'\n';
	}
}

---

## 作者：LAWArthur (赞：4)

# 题意
有一个序列，在其上可以做操作：将相邻两个数减 $1$，求有多少个连续子序列可以通过执行若干次该操作让其全变为 $0$。

# 题解
这题官方题解是 $O(n\log n)$ 的，但其实有做法可以做到 $O(n)$ ~~（代码还短）~~。

## 一个小构造
通过手玩样例可以发现，一个序列可以被删完等价于：
1. 这个序列中每一个位置都满足：
 - 若该位置为奇数位，则这一位置的前缀奇数位之和一定**大于等于**偶数位之和；
 - 若该位置是偶数位，则这一位置的前缀奇数位之和一定**小于等于**偶数位之和。
2. 这个序列的奇数位之和与偶数位之和相等。

于是我们可以对于每个位置构造一个值：

$$c_i=\sum\limits_{j=1}^i (-1)^{j-1}a_j$$

于是一个序列可以被删完的条件就变为：
$$\begin{cases}
(-1)^{i-1}c_i\ge 0\\
c_n=0
\end{cases}$$

而且可以发现，$c$ 是有满足前缀性质的，于是我们可以很方便地知道某一子序列中每一个位置的 $c$ 值。

## 维护
因为条件 $2$ 是结尾相关的，所以我们希望从左往右扫描序列，对于序列中每一个位置，求出以它为结尾的满足条件的子序列个数，这个显然需要一个数据结构维护。

如果只有条件 $2$，我们只需要维护位置 $i$ 之前有多少个 $j$ 满足 $c_j=c_i$ （因为 $c$ 有前缀性质）。

所以现在只需要考虑条件 $1$ 如何处理。

不妨只考虑奇数位上的情况（偶数可以类似处理）：

对于奇数位 $i$，若其之前有一个位置 $j$ 满足 $c_i<c_j$，那么子序列 $[i,j]$ 以及**以这个子序列为前缀的所有子序列**就都不满足条件了。而由于我们处理时从左往右枚举每一位，可以发现 $i$ 之后涉及到的**所有以 $j$ 开头的子序列都是不满足条件的**。这就说明，我们可以从数据结构中**删去 $j$**，因为它不会再构成任何一个满足条件的子序列。

而我们可以发现，在处理第 $i$ 位时，被删除的位置一定是数据结构中**所有**大于 $c_i$ 的数（对于奇数位则是小于），因此，在将 $c_i$ 插入时，它一定会成为数据结构中所有数的**最大/小值**。

于是我们就可以使用一个**双端单调队列**来维护。而又因为删除前/后缀之后，满足 $c_i=c_j$ 的 $j$ 一定是队列的某一个前/后缀，若是我们**合并 $c$ 相同的项**，查询便可以优化到 $O(1)$。而又因为每个位置最多被插入一次、删除一次，因此总复杂度是 $O(n)$ 的。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 300005
typedef long long ll;
ll T,n,a[N],ans,acm;
pair<ll,ll> q[2*N];// first为c的值，second为重数
ll l,r;
 
void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	q[N]=make_pair(0,1);
	l=N,r=N+1;
	acm = 0;
	ans=0;
 
	for(int i=1;i<=n;i++){
		if(i&1){//奇数位
			acm+=a[i];
			while(l<r&&q[r-1].first>acm)r--;//删除c_j>c_i的后缀
			if(l<r&&q[r-1].first==acm){
				ans+=q[r-1].second;//记录答案
				q[r-1].second++;
			}
			else q[r++]=make_pair(acm,1);
		}
		else {/偶数位
			acm-=a[i];
			while(l<r&&q[l].first<acm)l++;//删除c_j<c_i的前缀
			if(l<r&&q[l].first==acm){
				ans+=q[l].second;//记录答案
				q[l].second++;
			}
			else q[--l]=make_pair(acm,1);
		}
	}
	cout << ans << endl;
}
 
int main(){
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：王熙文 (赞：2)

居然自己想出了 2300 /cy

## 思路

首先可以先将区间满足的条件转化一下。对于一个区间 $[l,r]$，想使 $a_l=0$，则 $a_{l+1}$ 必须减去 $a_l$。接下来，$a_{l+2}$ 又得减去减之后的 $a_{l+1}$，即 $a_{l+1}-a_l$，$a_{l+3}$ 又得减去 $a_{l+2}-a_{l+1}+a_{l}$。直到最后，$[l,r-1]$ 都变成 $0$ 了，$a_r$ 减之后也得为 $0$。

可以发现对于一个位置，减之后为 $a_i-a_{i-1}+a_{i-2}-a_{i-3}+ \cdots$。即与它同奇偶的加，不同奇偶的减。

记录两个前缀和，$q0$ 表示所有偶数位的和，$q1$ 表示所有奇数位的和。

先不考虑 $a_r$ 的限制，那其他的条件一定是减之后大于等于 $0$。

考虑枚举左端点 $l$，然后二分右端点 $r$，使得对于 $[l,r]$ 的数减之后都大于等于 $0$。注意此时不考虑 $a_r$ 减之后等于 $0$，这个以后再说。

如何验证？对于一个位置 $i$，$i$ 减之后的数为：

* $i$ 为奇数，$(q1_i-q1_{l-1})-(q0_i-q0_{l-1})$
* $i$ 为偶数，$(q0_i-q0_{l-1})-(q1_i-q1_{l-1})$

因为要求大于等于 $0$，所以转化一下条件：

* $i$ 为奇数，$q1_i-q0_i \ge q1_{l-1}-q0_{l-1}$
* $i$ 为偶数，$q0_i-q1_i \ge q0_{l-1}-q1_{l-1}$

因为枚举了左端点，所以后面的一定了，则所有 $i$，前面的（$q1_i-q0_i$ 或 $q0_i-q1_i$）最小值需要大于等于后面的（$q1_{l-1}-q0_{l-1}$ 或 $q0_{l-1}-q1_{l-1}$）。区间最小值可以使用 st 表（或者线段树等）求出来。

这样我们求出了右端点 $r$，但没有考虑 $a_r$ 必须为 $0$ 的限制。可以将 $a_r$ 表示出来，为：

* $r$ 为奇数，$q1_r-q0_r = q1_{l-1}-q0_{l-1}$
* $r$ 为偶数，$q0_r-q1_r = q0_{l-1}-q1_{l-1}$

其实这两个式子是等价的。

那么我们现在要求二分出来的区间 $[l,r]$ 内有多少个 $i$（$i$ 为子区间的右端点，即上面分讨的 $r$），满足 $q1_i-q0_i=q1_{l-1}-q0_{l-1}$，即求区间有多少个数等于某个数。这个问题可以将区间拆成前缀形式，然后离线排序之后扫描过去求出来。

求出来这个问题整个题目就解决了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;

int a[300010],qzh1[300010],qzh2[300010],qzh[300010];

int lg2[300010],st[2][20][300010];

int query0(int l,int r) // i%2==0
{
	int len=lg2[r-l+1];
	return min(st[0][len][l],st[0][len][r-(1<<len)+1]);
}

int tot;
struct Query
{
	int wz,x,f;
} q[600010];
bool cmp(Query x,Query y)
{
	return x.wz<y.wz;
}

map<int,int> cnt;

int query1(int l,int r) // i%2==1
{
	int len=lg2[r-l+1];
	return min(st[1][len][l],st[1][len][r-(1<<len)+1]);
}

signed main()
{
	lg2[1]=0; for(int i=2; i<=3e5; ++i) lg2[i]=lg2[i>>1]+1;
	int t; cin>>t; while(t--)
	{
		cnt.clear();
		cin>>n;
		for(int i=1; i<=n; ++i)
		{
			cin>>a[i];
			qzh1[i]=qzh1[i-1]+a[i]*(i&1),qzh2[i]=qzh2[i-1]+a[i]*(!(i&1));
			qzh[i]=qzh1[i]-qzh2[i];
			st[0][0][i]=(i%2==0?-qzh[i]:1e18);
			st[1][0][i]=(i%2==1?qzh[i]:1e18);
		}
		for(int i=1; i<=19; ++i)
		{
			for(int j=1; j<=n-(1<<i)+1; ++j)
			{
				st[0][i][j]=min(st[0][i-1][j],st[0][i-1][j+(1<<i-1)]);
				st[1][i][j]=min(st[1][i-1][j],st[1][i-1][j+(1<<i-1)]);
			}
		}
		tot=0;
		for(int l=1; l<=n; ++l)
		{
			int el=l,er=n,mid,ans=l-1;
			while(el<=er)
			{
				mid=(el+er)>>1;
				if(query1(l,mid)>=qzh[l-1] && query0(l,mid)>=-qzh[l-1]) ans=mid,el=mid+1;
				else er=mid-1;
			}
			q[++tot]={ans,qzh[l-1],1},q[++tot]={l-1,qzh[l-1],-1};
		}
		sort(q+1,q+tot+1,cmp);
		int now=0,ans=0;
		for(int i=1; i<=tot; ++i)
		{
			while(now<=q[i].wz) ++cnt[qzh[now]],++now;
			ans+=cnt[q[i].x]*q[i].f;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：KAMIYA_KINA (赞：2)

## Tag

数据结构。

## Description

定义一次操作为你可以选取相邻的两个非零的数，并将它们减一。

定义一个区间是好的当且仅当你可以通过任意次操作使得这个区间所有的数最后都为 $0$。

给定一个长度为 $n$ 的序列 $\{a_n\}$，求其好的区间数。

$\texttt{data range:} n\leq 10^5$.

## Solution

一个区间合法必须奇数位上数字和等于偶数位上数字和。

但是这只是必要条件，并不是充分条件，例如 $\{3,1,1,3\}$ 就不是一个合法的序列。

我们定义一种新型的前缀运算，表示前缀中奇数位减去偶数位的值。

我们需要保证所有前缀经过该运算之后值都大于等于 $0$，那么转化一下之后会发现，如果某一个位置 $l$ 开头的到某一个位置 $r$，这个前缀运算不合法，那么以 $l$ 开头的 $r$ 后面的都不会合法。

所以我们可以记录一下每个位置结束的时候的一个前缀值，那么如果后面存在前缀值相等的时候那么就是合法的，因为 $S_r-S_l=0$ 很明显中间的值也是合法的，所以维护一个 $S_i$，在每一次加入一个数的时候去掉到这个位置就会导致不合法的位置数。

如果是奇数位，那么就往上加，如果是偶数位，那么就往下减。可以用一个 map 去维护。

时间复杂度 $O(n\lg n)$.

## Code

```cpp
using ll = long long;

const int N = 3e5 + 1;

int n;
int a[N];
map<int, int> vis;

inline void input() {
    n = rd;
    for(int i = 1; i <= n; i++) a[i] = rd;
    return ;
}

void ers(int x, bool typ) {
    if(!typ) {
        while(!vis.empty()) {
            auto tem = vis.begin();
            if(tem->first < x) vis.erase(tem);
            else return ;
        }
    } else {
        while(!vis.empty()) {
            auto tem = vis.end(); tem--;
            if(tem->first > x) vis.erase(tem);
            else return ;
        }
    }
    return ;
}

inline void work() {
    vis.clear(), vis[0]++;
    ll ans = 0;
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(i & 1) sum += a[i];
        else sum -= a[i];
        ans += vis[sum];
        if(i < n) {//删去到当前点不合法的前缀位置
            if(i & 1) ers(sum - a[i + 1], 0);
            else ers(sum + a[i + 1], 1);
        }
        vis[sum]++;
    }
    cout << ans << '\n';
    return ;
}

inline void solve() {
    int t = rd;
    while(t--) {
        input();
        work();
    }
    return ;
}
```



---

## 作者：intel_core (赞：0)

存在方案的充要条件不太好找，但是必要条件很容易。

不难发现区间必须满足奇数位位上的和必须等于偶数位上的和，并且不能有数比相邻两个数和要大。

必要条件是显然的，同时如果这两个条件都满足的话显然也是存在方案的。

我们记 $s_i=\sum_{k=1}^i(-1)^ka_k$，这样只需要维护 $s_{l-1}=s_r$ 并且区间中间无非法点的区间个数即可。

可以开一个 `map` 或者 `unordered_map` 直接统计，复杂度 $O(n \log n)$。

代码非常简单，~~就不放了~~。

---

