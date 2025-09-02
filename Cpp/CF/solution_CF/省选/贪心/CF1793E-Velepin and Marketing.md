# Velepin and Marketing

## 题目描述

The famous writer Velepin is very productive. Recently, he signed a contract with a well-known publication and now he needs to write $ k_i $ books for $ i $ -th year. This is not a problem for him at all, he can write as much as he wants about samurai, space, emptiness, insects and werewolves.

He has $ n $ regular readers, each of whom in the $ i $ -th year will read one of the $ k_i $ books published by Velepin. Readers are very fond of discussing books, so the $ j $ -th of them will be satisfied within a year if at least $ a_j $ persons read the same book as him (including himself).

Velepin has obvious problems with marketing, so he turned to you! A well-known book reading service can control what each of Velepin's regular readers will read, but he does not want books to be wasted, so someone should read each book. And so they turned to you with a request to tell you what the maximum number of regular readers can be made satisfied during each of the years, if you can choose each person the book he will read.

## 说明/提示

In the first example, in the first year, the optimal division is $ 1, 2, 2, 2, 2 $ (the first book is read by the first person, and everyone else reads the second). In the second year, the optimal solution is $ 1, 2, 2, 3, 3 $ (the first book is read by the first person, the second book is read by the second and third person, and all the others read the third book). In the third year, the optimal split will be $ 1, 2, 3, 4, 2 $ . Accordingly, the number of satisfied people over the years will be $ 5, 5, 3 $ .

In the second example, in the first year, the optimal division is $ 1, 1, 1, 1, 1, 2 $ , then everyone will be happy except the $ 6 $ -th person. In the second year, the optimal division is $ 1, 1, 1, 1, 2, 3 $ , then everyone will be happy except the $ 5 $ -th and $ 6 $ -th person.

## 样例 #1

### 输入

```
5
1 2 2 2 2
3
2
3
4```

### 输出

```
5
5
3```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6
2
2
3```

### 输出

```
5
4```

## 样例 #3

### 输入

```
6
4 4 1 4 4 4
3
2
3
4```

### 输出

```
6
5
1```

# 题解

## 作者：I_am_Accepted (赞：12)

@[陈玉彬](https://www.luogu.com.cn/user/333119) 教的线性做法 orz。

将 $a_1,\dots,a_n$ 非降序排序（桶排序）。

**结论：一定存在最优解使得看同一本书的人都是连续段，而且快乐的人一定是下标的一个前缀，而且要么只有第一个组的前缀快乐要么一个组的快乐状态相同。**

证明可以考虑调整法，但是过于繁琐及套路，这里不再赘述。

所以我们线性预处理出 $f_i$，表示将 $a[1,i]$ 均变为快乐的最多书数量。

对于书数量递增，我们答案一定递减，用一个指针扫。接着就变成单个判定问题：在 $x$ 本书的情况下能否让至少 $y$ 个人快乐。

这个问题可以 $O(1)$ 做：

* 若可以让 $a_1,\dots,a_y$ 看同一本书，即 $x\le n-y+1$，则判定为 $[a_y\le n-x+1]$。
* 否则，$a_1$ 和 $a_y$ 必然不在同一段，判定为 $[f_y+n-y\ge x]$。

总复杂度 $O(n)$，跑了 62ms。

---

## 作者：zac2010 (赞：9)

动态规划题。首先我们对 $a$ 数组排个序，因为 $a_i$ 小的不管什么情况下都比 $a_i$ 大的更优。

有结论：设最终答案为 $t$ 人满足，那么前缀 $1$ 到 $t$ 的人必定能构成一种可行方案。

还有结论：假设一种方案分出了 $x$ 个组，那么一定能合并成 $1$ 到 $x-1$ 中任意数量的组。也就是说，我们只要求出满足多少人的情况下最多能分成多少组别，小于这个组别数量的也都是可行的。

不难发现状态 $f_i$ 表示要求前 $i$ 个人满意的最多组别，有递推式 $f_i=mx_{i-a_i}+1$ 其中 $mx$ 数组是 $f$ 数组的前缀最大值，由于一组一定是连续的一段区间，所以能这样转移。至于 $a_i>i$ 的情况 $f_i=0$ 表示不可行。

注意，我们现在的 $f_i$ 还没有算上后面不满足的人的组别数。在推出所有的 $f_i$ 之后，如果 $i \le a_i$ 那么加上 $n-i$ 表示剩下的既然不满足那就可以每人成一个组别，如果 $i > a_i$ 那么为 $n-a_i+1$ 其中 $n-a_i$ 表示 $a_i$ 这个位置之后的每个都自成一组，前 $a_i$ 个成一组，虽然 $a_i$ 那个人可能不满足，但对于 $i$ 及其以前位置满足就够了。

最后把 $f_i$ 映射到一个数组其下标表示组别数，再做一个后缀最大值即可。

[代码](https://codeforces.com/contest/1793/submission/193599293)。

---

## 作者：OccDreamer (赞：6)

## 题目大意

有 $n$ 个读者，第 $i$ 年他们要一起读 $k_i$ 本书，**每一本书至少要让一个人读，每一个人也只能读恰好一本书。** 如果某一个人 $j$，如果有 $a_j$ 个人这一年里和他读了同一本书，那么他就会感到满足。

对于所有的 $q$ 组询问，每组给定一个 $k_i$，求感到满足的人数的最大值。

-----------------------------------------------

## $\text{Solution}$

我们先将 $a_i$ 排序，考虑到答案一定是一个前缀 $[1,x]$，不然我们可以交换两个人 $i \in [1,x]$ 和 $j \in [x+1,n]$，这样显然不会更劣。

考虑设计一个状态 $f_i$ 表示前 $i$ 个人最多可以读 $f_i$ 本书，且读这 $f_i$ 本书的人都感觉满足。

转移是很简单的，$f_i=\max\{f_{i-1},f_{i-a_i}+1\}$。

接下来考虑怎么对于每一组询问求出答案。

既然答案是一个前缀，那么我们考虑二分这一个前缀，接下来的问题转化为：我们怎么判定前缀 $[1,x]$ 是否合法。

首先我们贪心的想，我们让后面的 $n-x+1$ 个人每人读一本书。

接下来分为两种情况：

- 如果后面人数有剩余，那么我们让他们和 $[1,x]$ 中的读统一本书，再判定即可。
- 如果书有剩余 $r$ 本，考虑检查 $f_{x-a_x}$ 是否 $\geq c$，如果是则我们让前 $x-a_x$ 个人中不满足的和 $[x-a_x+1,x]$ 中的人读同一本即可。

代码实现很简单。

```cpp
#include<bits/stdc++.h>

#define fi first
#define se second
#define vc vector
#define db double
#define END exit(0)
#define pb push_back
#define mk make_pair
#define ll long long
#define PI pair<int,int>
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define err cerr << " -_- " << endl
#define debug cerr << "------------------------" << endl

//useful:
//#define cout cerr
//#define OccDreamer
//#define int long long

using namespace std;

namespace IO{
	inline int read(){
		int X=0, W=0;char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(ll x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void sprint(ll x){write(x);putchar(32);}
	inline void eprint(ll x){write(x);putchar(10);}
}using namespace IO;

const int inf=1e9;
const int MAXN=4e5+5;
const int mod=998244353;

int n, k;
int a[MAXN], f[MAXN];

inline bool judge(int x, int k){
	int c=n-x, rest=c-k;
	if(rest>=0 && x+rest<a[x]) return 0;
	if(rest>=0) return 1;
	k-=c;
	if(a[x]>x) return 0;
	if(f[x-a[x]]>=k) return 1;
	return 0;
}

inline void solve(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+1+n); f[0]=0;
	for(int i=1;i<=n;++i){
		if(a[i]>i) f[i]=f[i-1];
		else{
			f[i]=f[i-a[i]]+1;
		}
		f[i]=max(f[i-1],f[i]);
	}
	int q=read(), k, l, r, mid;
	while(q--){
		k=read();
		l=1, r=n;
		int c;
		while(l<=r){
			mid=(l+r)>>1;
			if(judge(mid,k-1)) l=mid+1;
			else r=mid-1;
		}
		eprint(r);
	}
	return ;
}

int main(){
	solve();
	return 0;
}
```

另外提一嘴，二分的过程可以在询问之前改为枚举，这样就可以做到 $O((n+q) \log n)$ 了。











---

## 作者：Lyrella (赞：4)

**[$\text{Problem - 1793E - Codeforces}$](https://codeforces.com/problemset/problem/1793/E)** **$\text{*2600}$**

# 备注

2024.10.19 考试 T2。考场未能想出正解，找到性质但没有根据性质往 dp 方面想，而是想通过多枚举状态找最优解，需要反思！

# 简要题意

有一个数列 $A$，我们需要将其分成若干组。对于一个 $i$，若 $i$ 所在的分组中元素个数大于等于 $a_i$ 则有贡献，给出 $q$ 次询问，求分成 $x$ 组时最大贡献。

数据范围：$2\le n,q\le3\times10^5,1\le a_i,x\le n$。

# 题解

首先观察题目我们可以得出以下性质：

1. 我们将 $A$ 按 $a_i$ 排序，选前面的一段满足条件肯定比后面的更优；（显然）
2. 我们分组时将相邻的一段一起选一定不劣；

所以我们每次需要做的事其实就是**选择一段前缀让它满足条件**。

我们先设 $\operatorname{ans}_i$ 表示分成 $i$ 组的最大贡献，但是想直接转移肯定不现实，经过尝试我们只能发现： $\operatorname{ans}_i$ 具有单调性。

这时我们需要另外引入几个辅助函数，我们设 $f_i$ 表示钦定第 $i$ 个数对答案有贡献时最多能分多少组，因为对于 $i$，我们需要将第 $i-a_i+1$ 到第 $i$ 个数分成一组，所以转移方程为：$f_i=f_{i-a_i}+1$，但是若 $a_i>i$，$f_i$ 就无意义，这里需要注意。若 $f_i$ 有意义，那么当前分的组数就为 $f_i+n-i$ 组；否则组数为 $n-a_i+1$。

然后就能够求出**第** $i$ 个有贡献时的答案，然后根据 $\operatorname{ans}_i$ 单调性可以直接后缀取最大值，时间复杂度瓶颈在于排序，是 $O(n\log n)$ 的，但是有人用桶排序 $O(n)$ 更优。

# 代码

```cpp
signed main(){
	freopen("xcpc.in", "r", stdin);
	freopen("xcpc.out", "w", stdout);
	n = rd(), q = rd();
	for(int i = 1; i <= n; ++i)a[i] = rd();
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; ++i){
		if(a[i] <= i)f[i] = f[i - a[i]] + 1, g = f[i] + n - i;
		else f[i] = 0, g = n - a[i] + 1;
		f[i] = max(f[i], f[i - 1]);
		ans[g] = i;
	}
	for(int i = n; i; --i)ans[i] = max(ans[i], ans[i + 1]);
	for(int i = 1; i <= q; ++i){
		int x = rd();
		printf("%d ", ans[x]);
	}
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

背刺我的调整法终于有出头之日了！

现将 $a$ 排个序。

我们将人分为两种：满足愿望的和不满足愿望的。

分析性质：

1. 如果一组里面所有人都是不满足愿望的，那么只保留一个，将其他人分到别的组会更优。

2. 一定是 $a$ 的某个后缀不满足要求，否则交换会更优；

3. 每组一定对应原序列的一个连续区间；

4. 如果存在两个组，他们都同时含有不满足愿望的人和满足愿望的人，可以分离一个不满足愿望的人，将他们合并，显然更优；

5. 如果存在两个组，一个组全都是满足愿望的人，另一组两种人都有，那么可以模仿 $4$ 的操作。

说了这么多，发现最终结果相当简单：某个前缀全都要满足，某个后缀全部不满足并且打散；某个前缀全部满足并且被分到了一组，中间一段给前缀凑数，后面打散。

这两者都可以 $O(n)$ 快速解决。

使用桶排可以做到 $O(n)$，但是我比较懒。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,INF=1e9;
int n,q,a[MAXN],pre[MAXN],dp[MAXN],ans[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	sort(a+1,a+n+1);
	ffor(i,1,n) {
		if(a[i]>=i) ans[1+n-a[i]]=max(ans[1+n-a[i]],i);
		else ans[1+n-i]=max(ans[1+n-i],i);
	}
	ffor(i,1,n) {
		if(a[i]<=i) dp[i]=pre[i-a[i]]+1;
		else dp[i]=-INF;
		if(dp[i]>=1) ans[dp[i]+n-i]=max(ans[dp[i]+n-i],i);
		pre[i]=max(pre[i-1],dp[i]); 
	}
	roff(i,n-1,0) ans[i]=max(ans[i+1],ans[i]);
	cin>>q;
	ffor(i,1,q) {
		int k;
		cin>>k,cout<<ans[k]<<'\n';	
	}
	return 0;
}
```

---

## 作者：Masterwei (赞：3)

#### 前言

我们的模拟赛题，赛时切了，考完老师说正解要什么数据结构？

#### 思路

注意到我们可以将读者的要求人数从小到大排序，因为你发现答案为 $i$ 的话，最优方案肯定是选取前 $i$ 个。我们可以算出答案为 $i$ 的最大组数，然后简单转换即可。

我们设 $f_i$ 表示答案为 $i$，且只用排序后的前 $i$ 个所能得到的最大组数，转移显然，就是钦定 $i$ 所在的组至少有 $a_i$ 个人，即 $f_i=\max_{j=1}^{i-a_i}a_j+1$。

接着，我们贪心的想，答案为 $i$ 的最大组数其中一种方案，必然是由前 $i$ 个组成最大的组数再加上 $n-i$。意思就是对于剩下的 $n-i$ 个不算答案的数，我们尽可能去凑组数。

如何保证保证正确性？你发现那 $n-i$ 个数无非是去凑人头，而同样的事如果交给算进答案的那 $i$ 个数，显然不会更劣。

用桶排即可 $O(n)$，我用的 `sort`。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=3e5+5;
int n,q,a[Maxn];
int ans[Maxn];
int f[Maxn],g[Maxn];
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n);
	f[0]=0;q=read();
	for(int i=1;i<=n;i++){
		if(i-a[i]>=0)f[i]=g[i-a[i]]+1;
		g[i]=max(g[i-1],f[i]);
		int cost=0;
		if(i-a[i]>=0)cost=f[i]+n-i;
		else cost=n-a[i]+1;
		ans[cost]=i;
	}
	for(int i=n;i;i--)ans[i]=max(ans[i],ans[i+1]);
	while(q--){
		int x=read();
		printf("%d\n",ans[x]);
	}
	return 0;
}
```

---

## 作者：tangml (赞：1)

### 一道十分简明的序列题

##### 题意简述
$n$ 个人，每个人都要给一个 $[ 1 ,m ]$ 之间的整数，且每个 $[ 1 , m ]$ 间的整数需至少给一个人。
每个人有一个阈值 $a_i$ ,若与第 $i$ 个人拥有相同数字的人数至少为 $a_i$ （包括自己），那么他就是高兴的。
多次询问，每次一个 $m$ ，求最多高兴人数。

##### 解决方案
易证得：按 $a_i$ 排序，一定是从前往后一段一段分组。

设 $f_i$ 表示前 $i$ 个人都高兴，至多分为几段。
所以我们可以写出动态转移方程。


``` cpp
f[j]=f[i]=max( f[j]+1,f[i] )  (0<=j<=i-a[i]  a[i]<=j)
```




##### 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=3e5+100;
int n,m;
int T; 
int a[N];
int f[N];
int ans[N];

int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

//2024/1/16
int main()
{
	m=read();
	for(int i=1;i<=m;i++)	a[i]=read();
	sort(a+1,a+m+1);//按a[i]排序，一定是从前往后一段一段分组。
	for(int i=1;i<=m;i++)
	{
		if(i>=a[i])
		{
			f[i]=f[i-a[i]]+1;
			ans[f[i]+m-i]=max(i,ans[f[i]+m-i]);
		}//高兴人数为i，整数范围至多为f[i]+m-i
		else	ans[m-a[i]+1]=max(i,ans[m-a[i]+1]);//高兴人数为i，整数范围至多为m-a[i]+1 
		f[i] = max(f[i], f[i - 1]);
	}//dp:f[i]=max{f[j]+1} (0<=j<=i-a[i]  a[i]<=j)
	for(int i=m;i>=1;i--)		ans[i]=max(ans[i],ans[i+1]);
	T=read();
	while(T--)
	{
		n=read();
		printf("%d\n",ans[n]);
	}
	return 0;
} 
```

---

## 作者：Day_Tao (赞：1)

原题题意等价于 $n$ 个点分为 $k$ 组，设第 $i$ 个点所在组的长度为 $l_i$，则总贡献为 $\sum\limits_{i=1}^n [a_i\le l_i]$。不难发现，分组越多，贡献越小，所以我们考虑枚举贡献，对于每一种贡献确定分组的上限。不难发现，对于相同的贡献，肯定是贪心地考虑 $a_i$ 更小的，这样的 $a_i$ 才更容易被满足。所以考虑对 $a$ 排序，每次取一段前缀，计算假设这段前缀都被满足的分组上限。

继续贪心地想，对于满足一段前缀合法如何使得分组数量最大。要满足前缀合法就可能往后取，由于后面的数字不用考虑贡献，没有被选中的那些人都可以每人分一组，后面多保留一个一定不劣与前面多保留一个的贡献，所以贪心策略就转化成了考虑保留尽量多的后面的数的情况下，最小化前面数字分组数。我们记 $f_i$ 表示前 $i$ 个数都合法的最大分组数。考虑 $a_i>i$，前面的数字必须分为一组，并且会影响到一些后面的数，所以 $f_i=n-a_i+1$。否则就考虑将 $i$ 作为当前 $i$ 所在组的最后一个数，前面的 $a_i-1$ 个数也都要分到这一组里。由于 $a_i$ 单调不降，所以前面的数划分到当前组肯定也是合法的。我们再记 $g_i$ 表示保证 $i$ 之前都合法，且不会将 $i$ 之后的数都划分进去的最大分组数。在 $a_i\le i$ 的情况下 $f_i$ 就是 $g_{i-a_i}+1+n-i$，表示 $i-a_i$ **之前的划分最大方案** + $i-a_i+1\sim i$ **划分为一段的贡献** + **后面** $n-i$ **个数单独划分的贡献**，同时 $g_i=g_{i-a_i}+1$，并将 $g_i$ 取前缀 $\max$。

得到 $f$ 数组之后就双指针枚举贡献及最大分组数，将 $f_i$ 与 $i$ 的对应关系给映射到 $ans$ 数组中，询问的时候直接查询即可。但是注意分组数的上限为 $n-a_1+1$，再多的分组答案就为 $0$ 了。排序使用桶排，时间复杂度 $O(n)$。

code：

```cpp
const int N=3e5+5;
int n,m,a[N],f[N],g[N],ans[N],q,cnt[N];
inline void SOLVE(){
	n=rd();for(int i=1;i<=n;i++)++cnt[rd()];
	for(int i=1;i<=n;i++)while(cnt[i])cnt[i]--,a[++m]=i;
	for(int i=1;i<=n;i++){
		if(a[i]<=i)f[i]=g[i-a[i]]+1+n-i,g[i]=g[i-a[i]]+1;
		else f[i]=n-a[i]+1,g[i]=0;cmx(g[i],g[i-1]);
	}for(int i=1,j=n-a[1]+1;i<=n;i++){
		if(f[i]==f[i+1])continue;
		while(j>f[i+1])ans[j]=i,j--;
	}q=rd();while(q--){int x=rd();printf("%lld\n",ans[x]);}
	return ;
}
```

---

## 作者：聪明的乖宝宝 (赞：1)

# 思路
首先，随着书的数量的多，开心的人的数量单调不增，所以只要我们预处理出想要有 $ x $ 人开心，最多有几本书，就可以 $ O(1) $ 查询了。

其次，贪心，想要 $ x $ 个人开心，我们要有限选择让 $ a_x $ 小的人开心，这样才能使得书尽可能多。所以先将 $ a $ 数组由小到大排序。

分两种情况讨论：
- 当 $ a_x<x $ 时，用后面的人补齐，保证前 $ x $ 个人开心。
- 当 $ a_x\geq{x} $ 时，用第 $ x-a_x+1 $ 到第 $ x $ 个人使得第 $ x $ 个人开心，然后在利用之前求出的使得前 $ x-a_x $ 个人开心的最多的书的数量，在 $ x $ 之后的人每人还可以分配一本书。

通过递推线性预处理出来结果，注意到 $ a $ 的数据范围，排序也可以通过桶排优化到线性~~也可以不优化~~。
# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,q;
const int N=300010;
int a[N];
int f[N];
int k[N];
int ans[N];
bool com(int a,int b)
{
    return a<b;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+1+n,com);
    for(int i=1;i<=n;i++)
    {
        if(a[i]>i)
        {
            f[i]=0;
            k[i]=n-a[i]+1;
        }
        else
        {
            f[i]=f[i-a[i]]+1;
            k[i]=f[i]+n-i;
        }
        f[i]=max(f[i-1],f[i]);
        if(k[i]>0)ans[k[i]]=i;
    }
    for(int i=n;i>=1;i--)ans[i]=max(ans[i],ans[i+1]);
    cin>>q;
    while(q--)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",ans[x]);
    }
    return 0;
}

```

---

## 作者：Sirkey (赞：1)

[或许更好的阅读体验](https://www.cnblogs.com/sirkey2119/articles/18414175)

首先发现，每个人过的题是不同的，所以我们不关心过了那些题目。

我们要直接去求分成 $k$ 组最多的通过数是不容易的。我们可以转换一下，求当 $i$ 个题通过的时候 __最多__分多少组。为什么记最多，因为化成 $k$ 个组通过 $i$ 题可以的情况下，我们可以任意合并两个组，保证依然可以通过 $i$ 个题。相当于求了上界，方便求答案。

目前已知，要求：__当 $i$ 个题通过的时候 最多分多少组__ 。

我们考虑记两个内容 ：

$F_i$ ：表示通过前 $i$ 个题分成了多少组（只关心前 $i$ 个被分成了多少组）。

$G_i$ ： 表示通过前 $i$ 个题最少用了多少个人（因为会有后面的拿来充数）。

介绍一下定义，我们要求的其实是一个 $ans$ 表示 $i$ 个分组最多通过几道题。因为我求了 $F_i$ 和 $G_i$，所以我们可以得到所有的人被分成了多少组。即 $(n - G_i) + F_i$。将 $ans_{(n - G_i) + F_i}$ 赋值为 $i$，同时 $ans_i = \max(ans_i,ans_{i-1})$。这样就求出了 $ans$ 数组。

当前可能 $F_i$ 和 $G_i$ 记录的情况可能不止过了 $i$ 道题。但在后面会重新被更改为最大的，所以不影响答案。

关于转移。我们知道将排序后连续一段放在一个组别中一定最优。因为当花费了 $a_i$ 个人帮助 $i$ 个人完成了题目，但 $i-1$ 不在，所以有要花费 $a_{i-1}$  来完成第 $i-1$ 个题目，这显然不优。其次，我们转移中，$G_i$  越小转移越优。因为 $G_i$ 越大那么没用的越少，我们要求最多没用的一定是单个单个分开，所有 $G_i$ 越大一定不比自己小的优。在 $G_i$ 相同的情况下，$F_i$ 越大越好，这就不多解释了。

转移还要分类讨论一下。

$a_i > i$：找到 $1 \sim (a_i - i)$ 中最小的 $G_j$，最大的 $F_j$

$a_i \le i$：$F_i = 1,G_i = a_i$

我们动态求前缀的最小的 $G_j$，最大的 $F_j$。



```
#include<bits/stdc++.h>
#define int long long
#define debug(x) cout<<#x<<"[:]"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
void write(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int MX = 3e5 + 10;
int a[MX];
int f[MX], g[MX];
int ans[MX], G[MX];
sky pa[MX];
const int inf = 1e18 + 10;
struct sky {
	int a,b,id;
};
sky merge(sky x,sky y) {
	if(x.a < y.a) return x;
	if(x.a > y.a) return y;
	if(x.a == y.a)
		if(x.b > y.b) return x;
		else return y;
}
signed main() {
	ios::sync_with_stdio(0), cout.tie(0);
	int n = read();
	int Q = read();
	FOR(i,1,n) a[i] = read();
	sort(a+1,a+n+1);
	FOR(i,1,n) g[i] = inf;
	FOR(i,1,n) {
		if(i - a[i] >= 1) {
			sky A = pa[i - a[i]];
			f[i] = A.b + 1;
			g[i] = A.a + A.id + a[i] + (i - a[i] - A.id);
		} else f[i] = 1,g[i] = a[i];
		sky B = {g[i] - i, f[i], i};
		pa[i] = merge(B,pa[i - 1]);
	}
	FOR(i,1,n) G[i] = (n - g[i]) + f[i];
	FOR(i,1,n) ans[G[i]] = i;
	ROF(i,n,1) ans[i] = max(ans[i + 1],ans[i]);
	FOR(i,1,Q) {
		int k = read();
		cout<<ans[k]<<" ";
	}
	return 0;
}

```

——end——

---

