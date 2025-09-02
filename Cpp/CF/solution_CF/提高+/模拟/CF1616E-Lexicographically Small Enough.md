# Lexicographically Small Enough

## 题目描述

You are given two strings $ s $ and $ t $ of equal length $ n $ . In one move, you can swap any two adjacent characters of the string $ s $ .

You need to find the minimal number of operations you need to make string $ s $ lexicographically smaller than string $ t $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 样例 #1

### 输入

```
4
1
a
a
3
rll
rrr
3
caa
aca
5
ababa
aabba```

### 输出

```
-1
0
2
2```

# 题解

## 作者：mayike (赞：9)

题解貌似还没有无数据结构的，我来写一发。

### [题目传送门](https://codeforces.com/problemset/problem/1616/E)

温馨提示：先去做[基础题](https://www.luogu.com.cn/problem/P6116)，你做本题会更加轻松。

## 思路

因为做过提示中的基础题，我第一眼看这题就想到了一个重要的东西：最终状态长啥样？通过题目，我们知道最终状态肯定是 $s,t$ 两个串有同样长度的两段前缀完全相等，前缀后的 $s_i < t_i$，$i$ 后的字符长啥样不管，满足目标即可。

那么 dp 的状态定义就出来了，$f_{i,j,k}$，$k=0$ 或 $k=1$，表示进行到第 $i$ 个，以字母 $j$ 结尾，$k=0$ 指这是前缀的一部分，$k=1$ 指这是前缀后第一个字符的位置。

对于 dp 的转移，我们还需几个辅助数组，$sum_{i,j}$ 表示 $t$ 前 $j$ 个中字母 $i$ 出现次数，$ab_{i,j}$ 表示 $s$ 前 $j$ 个中字母 $i$ 出现次数，$js_{i,j}$ 表示字母 $i$ 在 $s$ 中第 $j$ 个的位置。

现在才是最重要的转移部分！首先，我们根据贪心思想，每次操作只能交换相邻两个字符，相同字符显然没有交换的必要，所以，第 $i$ 位若想用字符 $j$，那肯定是取整个字符串最靠前的部分，且设 $j$ 的位置为 $k$，必然有 $i \le k$，$k$ 是前 $i-1$ 个字符已经变换成前缀的样子时的位置，易证。考虑什么都没变化时的交换次数，是 $k-i$。那变化后的次数呢？想想每个位置的字符，在没有成为前 $i$ 个中的部分时是一直往后被移动的，因为这个字符后的字符往前交换时，会把这个位置的字符换到后一个位置，所以，我们仅需看其他 $25$ 个字符对于 $k$ 后面的位置有多少个是转移到前 $i-1$ 的前缀里即可。

可得：

$$tp \gets sum_{j,i-1}+1$$

$$p \gets js_{j,tp}$$

$$f_{i,j} \gets f_{i-1,t_{i-1}}+p-i+\sum _ {\substack{1 \leq k \leq 26 \\ k \neq j}} \max(sum_{k,i-1}-ab_{k,p},0)$$

这里省去了第三维，是因为第三维在本质上是可以略去的。

那么就可以愉快地写代码了，综合时间复杂度约比 $\mathcal{O}(n\log n\log n)$ 大一些。

**注：此题细节较多，请一定小心。**

**请远离抄袭！**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int T,n,jw,f[N][27][2],sum[27][N],js[27][N],ab[27][N],ans;//f[i][j][0/1]:进行到第i个数，以j结尾，0/1:是b的前缀和？是/不是
string s,t;
int tb(char c){return c-96;}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>s>>t,s=' '+s,t=' '+t,jw=n,ans=LLONG_MAX;
		for(int i=1;i<=26;i++)js[i][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=26;j++)f[i][j][0]=f[i][j][1]=LLONG_MAX,sum[j][i]=sum[j][i-1]+(tb(t[i])==j),ab[j][i]=ab[j][i-1]+(tb(s[i])==j);
			js[tb(s[i])][++js[tb(s[i])][0]]=i;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<tb(t[i]);j++){
				if(js[j][0]<sum[j][i-1]+1)continue;
			    if(i!=1)f[i][j][1]=f[i-1][tb(t[i-1])][0];
				else f[i][j][1]=0;
				f[i][j][1]+=js[j][sum[j][i-1]+1]-i;
				for(int k=1;k<=26;k++)
					if(k!=j)f[i][j][1]+=max(sum[k][i-1]-ab[k][js[j][sum[j][i-1]+1]],0ll);
			}
			if(sum[tb(t[i])][i]>js[tb(t[i])][0]){jw=i;break;}
			if(i!=1)f[i][tb(t[i])][0]=f[i-1][tb(t[i-1])][0];
			else f[i][tb(t[i])][0]=0;
			f[i][tb(t[i])][0]+=js[tb(t[i])][sum[tb(t[i])][i]]-i;
			for(int j=1;j<=26;j++)
				if(j!=tb(t[i]))f[i][tb(t[i])][0]+=max(sum[j][i]-ab[j][js[tb(t[i])][sum[tb(t[i])][i]]],0ll);
		}for(int i=1;i<=jw;i++)
			for(int j=1;j<=26;j++)ans=min(ans,f[i][j][1]);
		cout<<(ans==LLONG_MAX?-1:ans)<<"\n";
	}
	return 0;
}
```

---

## 作者：whhsteven (赞：8)

## 题意

给定长度为 $n$ 的两个字符串 $s$ 和 $t$，每次操作可以交换 $s$ 中的相邻两字符，求使得 $s$ 比 $t$ 字典序小的最少操作次数。

&nbsp;

## 题解

枚举 $s^\prime$ 和 $t$ 公共前缀的长度 $l$，则 $s^\prime[1,l] = t[1,l]$ 且 $s^\prime[l+1] < t[l+1]$。

对于每一个位置 $i$，我们维护出**使得到此位置 $s^\prime$ 和 $t$ 前缀相等的最少操作次数**，并计算出**使得 $s^\prime[1,i-1] = t[1,i-1]$ 且 $s^\prime[i] < t[i]$ 的最少操作次数**。后者中的最小值即为答案。

对于前者，每次从当前位右边找到最近的 $t[i]$ 移过来并维护答案；对于后者，每次从当前位右边找到最近的 $c < t[i]$ 移过来并计算答案。

所以我们对字符集里每个字符按顺序记下其出现位置。这样，每次要找到最近的某个字符，就取该字符最早的没有被使用过的出现位置。

接下来有两条路，主要思想都是用树状数组维护每个字符的位置。

&nbsp;

### 一

考虑将一个字符从位置 $j$ 向前移到位置 $i$ 的过程：

- 该字符前移了 $j - i$，从而可见其所需最少操作次数即为 $j - i$；

- 原位置 $i \sim j - 1$ 的字符现在各后移了 $1$，依次位于位置 $i + 1 \sim j$；

- 其余位置没有变化。

因此，我们用 $26$ 个 `queue` 或 `vector` 等按顺序记下每个字符的所有初始出现位置，用树状数组维护每个初始位置的偏移量。对一个字符，我们更新答案时使用的实际位置即该字符的初始位置加上偏移量。

另外可以注意到，所有尚未被移到前面的字符，它们之间的前后关系不会改变，这样每次找最近的字符时，只需要找初始位置最靠前的即可。

时间复杂度 $O(n\log n)$。

&nbsp;

### 二

同样考虑将一个字符从位置 $j$ 向前移到位置 $i$ 的过程：

- 最少操作次数为 $j - i$；

- 原位置 $i \sim j - 1$ 的字符现在距下一个要操作的位置 $i + 1$ 的距离等于操作前距 $i$ 的距离；

- 原位置 $j + 1 \sim n$ 的字符现在距下一个要操作的位置 $i + 1$ 的距离比操作前距 $i$ 的距离小 $1$。

同样用 $26$ 个 `queue` 或 `vector` 等按顺序记下每个字符的所有初始出现位置，而用树状数组维护每个位置距当前操作位置的距离。区间 $-1$，单点求值，所以维护距离的差分序列即可。

时间复杂度 $O(n\log n)$。

&nbsp;

## 代码

代码中 `ans` 即为所求的答案，`ans2` 为维护的使得前缀相等的最少操作次数，`clst` 表示最近的位置。

&nbsp;

### 一

代码中 `ban` 记录一个初始位置是否已被移到前面去。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define pb pop_back

using namespace std;

namespace acah
{
	using ll = long long;
	
	constexpr int maxn = 2e5 + 7;
	constexpr ll inf = 1e18;
	
	int T, N;
	bool ban[maxn];
	char s[maxn], t[maxn];
	ll ans, ans2, c[maxn];
	
	inline void u(int p, int d) {for(; p <= N; p += (p & (-p))) c[p] += d;}
	inline ll q(int p, ll s = 0) {for(; p; p -= (p & (-p))) s += c[p]; return s;}
	
	int work()
	{
		scanf("%d", &T); while(T--) {
			ans = inf, ans2 = 0;
			memset(c, 0, sizeof c), memset(ban, 0, sizeof ban);
			vector<int> ap[26];
			
			scanf("%d %s %s", &N, s + 1, t + 1);
			for(int i = 1; i <= N; i++) ap[s[i] - 'a'].eb(i);
			for(int i = 0; i < 26; i++) reverse(ap[i].begin(), ap[i].end());
            
			for(int i = 1, p = 1, clst; i <= N; i++) {
				while(ban[p] && p < N) ++p;
				
				if(s[p] >= t[i]) {
					clst = N + 1;
					for(int j = 0; j < t[i] - 'a'; j++)
						if(ap[j].size() && *ap[j].rbegin() < clst) clst = *ap[j].rbegin();
					if(clst != N + 1) ans = min(ans, ans2 + clst - p + q(clst) - q(p));
				} else ans = min(ans, ans2);
				
				if(s[p] != t[i]) {
					if(!ap[t[i] - 'a'].size()) break;
					clst = *ap[t[i] - 'a'].rbegin();
					ban[clst] = true;
					ans2 += clst - p + q(clst) - q(p);
					u(p, 1), u(clst, -1), ap[t[i] - 'a'].pb();
				} else ++p, ap[t[i] - 'a'].pb();
			}
			
			printf("%lld\n", (ans < inf ? ans : -1));
		}
		return 0;
	}
}

int main() {return acah::work();}
```

&nbsp;

### 二

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace acah
{
	using ll = long long;
	
	constexpr int maxn = 2e5 + 7;
	constexpr ll inf = 1e18;
	
	int T, N;
	char s[maxn], t[maxn];
	ll ans, ans2, c[maxn];
	
	inline void u(int p, int d) {for(; p <= N; p += (p & (-p))) c[p] += d;}
	inline ll q(int p, ll s = 0) {for(; p; p -= (p & (-p))) s += c[p]; return s;}
	
	int work()
	{
		scanf("%d", &T); while(T--) {
			ans = inf, ans2 = 0;
			memset(c, 0, sizeof c);
			queue<int> ap[26];
			
			scanf("%d %s %s", &N, s + 1, t + 1);
			for(int i = 1; i <= N; i++) ap[s[i] - 'a'].push(i);
			for(int i = 1; i < N; i++) u(i, 1);
			
			for(int i = 1, clst; i <= N; i++) {
				clst = N + 1;
				for(int j = 0; j < t[i] - 'a'; j++)
					if(!ap[j].empty()) clst = min(clst, ap[j].front());
				if(clst != N + 1) ans = min(ans, ans2 + q(clst - 1));
				
				if(ap[t[i] - 'a'].empty()) break;
				clst = ap[t[i] - 'a'].front(), ap[t[i] - 'a'].pop();
				ans2 += q(clst - 1), u(clst, -1);
			}
			
			printf("%lld\n", (ans < inf ? ans : -1));
		}
		return 0;
	}
}

int main() {return acah::work();}
```

---

## 作者：I_am_Accepted (赞：4)

### Preface

尝试了一上午 $O(n)$ 解法，失败了 qwq，因为区间修改 + 单点查询不可能是线性的。

### Analysis

**注意，以下字符串下标从 $1$ 开始标号，字符集大小 $26$ 当常数看待。**

显然枚举最终 $s$ 和 $t$ 的最长公共前缀长度 $len$，则：

$$\begin{cases}s_i=t_i &i\le len\\s_i>t_i &i=len+1\end{cases}$$

我们从左往右依次增加 $len$，当要使得 $s_{len+1}=t_{len+1}$ 即 $len$ 加 $1$ 时，贪心地选择 $s$ 中 $len$ 右边（或本身就是）距离最近的值为 $t_{len+1}$ 的位置，一步一步调到 $s_{len+1}$ 的位置。

在固定的 $len$ 中，使得 $s_{len+1}>t_{len+1}$ 的贪心方案也与上文类似。

前文的寻找最近位置可以用栈（队列、vector 也行）单次 $O(1)$ 实现。重要的是如何维护 $s$ 中一步一步调度的修改。我们开一个数组 $\{c\}$（用树状数组实时维护），$c_i$ 表示原序列 $s$ 中第 $i$ 位的值现在的位置与 $len$ 的差。若过程中将原序列 $s$ 中第 $i$ 位调换到现在 $len+1$ 的位置上，则 $len$ 增加时 $\{c\}$ 中 $[i,n]$ 区间减 $1$（因为他们没动，而 $len$ 向右了一格， $i$ 之前的因为循环右移也跟着 $len$ 向右一格，所以相对距离不变）。

### Detail

$\{c\}$ 树状数组由于要区间修改 + 单点查询，具体使用了差分。

为了确定每次更新 $len$ 后 $s_{len+1}$ 的值，记录一个数组 $\{vis\}$ 表示对应原始 $s$ 中的这个元素是否被“抛到前面去”了。

### Code

外层循环枚举的 $i$ 实际上是 $len+1$。

[Link](https://codeforces.com/contest/1616/submission/145041309)

---

## 作者：tyr_04 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1616E)

~~在此纪念考试时忘开 long long 的我。~~

## 题目大意

给你两个字符串，每次可以交换字符串一中相邻的两个字符，请你求出最少交换几次可以使字符串一比字符串二的字典序更小。

## 思路

### 贪心部分

贪心，每次分为以下两种情况。

- 在此位置确定字符串一的字典序更小。

- 在此位置以后确定字符串一的字典序更小。

什么意思呢？

举个例子，假设两个字符串分别为：

```
qaq
qwq
```

如果我们要在第一个字符时确定字符串一的字典序更小，必须使字符串一的第一个字符比字符串二的第一个字符的字典序更小。

在这两个字符串中，满足条件的字符串一只有：

```
aqq
```

如果我们要在第二个字符时确定字符串一的字典序更小，必须使字符串一的第二个字符比字符串二的第二个字符的字典序更小。

除此之外，还必须保证之前已改变的字符串一致，如果不一致，字典序就会不同，后面的字符也就不需要再管了。

在这两个字符串中，满足条件的字符串一只有：

```
qaq
```

所以我们只需要找到距离此处最近，且要么目前的字符串一比目前的字符串二的字典序小，要么目前的字符串一与目前的字符串二的字典序相等的情况即可。

只要找到此处字典序更小的情况，就可以记一次答案，而在前面的字符相等的情况下，只需要找出后来字符串一的某个字符的字典序更小的情况再加上前面的字符相等的情况的最小交换数即可。

### 其他部分

接下来，我们要考虑在交换过程中，后面的字符向前移动，可以看做前面交换过的字符在做相对运动，即向后移动一位。

所以，对于每次移动（指后面的字符移动到前面的某个位置，也就是进行多次交换），只需要让在它前面且在它移动到的位置的后面的所有字符的位置加上一即可。

此处可以用求和的方式，找到每一次移动前的最初始位置（刚输入时的位置），并将这个位置的值变为一，前面每一个字符串的位置就是从目前位置的值加到最后一个位置的值。

此处可以用分块或线段树等多种方式求出和，本人的代码就是用的分块。

时间复杂度为 $O(n \sqrt n)$。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char c1[100005],c2[100005];
long long n,sum[30],w[30][100005],u[30],now=0,ans=1e12,h[100005],k[100005],kl=0,ks=0;
int qh(int x)
{
	long long hz=0,nks=(x-1)/kl+1;
	for(int i=x;i<=min(nks*kl,n);i++)
	{
		hz+=h[i];
	}
	for(int i=nks+1;i<=ks;i++)
	{
		hz+=k[i];
	}
	return hz;
}
void become(int x)
{
	for(int i=1;i<=ks;i++)
	{
		if(((i-1)*kl)+1<=x&&(i*kl)>=x)
		{
			k[i]++;
			break;
		}
	}
	return;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		ans=1e12;
		cin>>n;
		kl=sqrt(n);
		if(n%kl==0)
		{
			ks=n/kl;
		}
		else
		{
			ks=n/kl+1;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>c1[i];
		}
		for(int i=1;i<=ks;i++)
		{
			k[i]=0;
		}
		long long g=100000;
		for(int i=1;i<=min(ks*kl,g);i++)
		{
			h[i]=0;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>c2[i];
		}
		for(int i=0;i<=25;i++)
		{
			sum[i]=0;
			u[i]=0;
			for(int j=1;j<=n;j++)
			{
				w[i][j]=-1;
			}
		}
		for(int i=1;i<=n;i++)
		{
			sum[int(c1[i]-'a')]++;
			w[int(c1[i]-'a')][sum[int(c1[i]-'a')]]=i;
		}
		now=0;
		for(int i=1;i<=n;i++)
		{
			if(w[int(c2[i]-'a')][u[int(c2[i]-'a')]+1]==-1)
			{
				for(int j=0;j<c2[i]-'a';j++)
				{
					if(w[j][u[j]+1]!=-1)
					{
						ans=min(ans,now+abs(i-(w[j][u[j]+1]+qh(w[j][u[j]+1]))));
					}
				}
				break;
			}
			else
			{
				for(int j=0;j<c2[i]-'a';j++)
				{
					if(w[j][u[j]+1]!=-1)
					{
						ans=min(ans,now+abs(i-(w[j][u[j]+1]+qh(w[j][u[j]+1]))));
					}
				}
				u[int(c2[i]-'a')]++;
				now+=abs(i-(w[int(c2[i]-'a')][u[int(c2[i]-'a')]]+qh(w[int(c2[i]-'a')][u[int(c2[i]-'a')]])));
				h[w[int(c2[i]-'a')][u[int(c2[i]-'a')]]]++;
				become(w[int(c2[i]-'a')][u[int(c2[i]-'a')]]);
			}
		}
		if(ans==1e12)
		{
			cout<<-1<<endl;
		}
		else
		{
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：songzhihan2010 (赞：1)

### 题目意思 ###
交换相邻的字符，使其字典序小于目标串，求最小操作次数。

### how ###
看到字典序小于某一串，可以将其拆成两部分，一串真前缀与其前缀相同，后第一个字符小于目标串，接下来无论剩下的为什么字符，其字典序都会比其大。所以我们可以尝试枚举前缀长度 $i$ 先保证两个序列前缀相等，后再逐渐挪动第 $i+1$ 的字符，求出答案。
- #### Step 1 怎样求出比当前字符小的字符 ####
碰到这种有关字符的题目，通常字符种类不多，可以开个桶将其记录下来，在我的代码中，$word_{i,j}$ 就是用来记录在模式串中字符 $i$ 的位置在修改后指针逐渐后移，直到该类字符全部使用完(为了维护两串前缀相同，有时会将一些字符挪动到前面，为后续第 $i+1$ 的字符枚举做准备)。
- #### Step 2 怎样维护挪动够字符位置 ####
如果你只看挪动的一个字符，你可能只会发现它仅仅是从他位置移动到第 $i+1$ 的位置，但是你如果将第 $i+1$ 到字符前一个位置整体来看，你会发现他们整体位移了一个位置，这不就是区间修改吗，后面询问就是单点查询，但如果你为了维护字符的位置，你会发现之前移动的字符可能已经跑到了前面，不好处理，那么我们既让知道了初始位置，那直接维护移动的距离就可以了，不用那么麻烦。
- #### Step 3 计算答案 ####
前面这些做完后，只要计算移动的距离，即交换次数就可以了，但值得注意的是，将第 $i$ 位置的字符移到 $j$ 处，只要移动 $|i-j|$，而不是 $|i-j+1|$。
### Finally ###
做完这些，有个非常值得注意的地方——答案大小，我第一次提交 ans 赋值 $10^8$，结果居然炸了，后面开到 $10^{18}$ 就可以了。
```cpp
//write by szh
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int _; 
int n;
char a[N],b[N];
 
vector<int> word[26];
 
int t[N];
int lb(int x){
	return x&-x;
}
void add(int x){
	for(;x;x-=lb(x))
		t[x]++;
}
int sum(int x){
	int res=0;
	for(;x<=n;x+=lb(x))
		res+=t[x];
	return res;
}
 
int main(){
	scanf("%d",&_);
	while(_--){
		scanf("%d%s%s",&n,a+1,b+1);
		for(int i=0;i<26;i++)
			word[i].clear();
		for(int i=n;i;i--)
			word[a[i]-'a'].push_back(i);
		for(int i=1;i<=n;i++)
			t[i]=0;
		long long ans=1e18,s=0;
		for(int i=1;i<=n;i++){
			int c=b[i]-'a';
			for(int x=c-1;x>=0;x--)
				if(word[x].size()){
					ans=min(ans,s+word[x].back()+sum(word[x].back())-i);
				}
			if(word[c].size()){
				s+=word[c].back()+sum(word[c].back())-i;
				add(word[c].back());
				word[c].pop_back();
			}
			else
				break;
		}
		printf("%lld\n",ans<1e18?ans:-1);
	}
}
```

---

