# [AGC066D] A Independent Set

## 题目描述

给定一个由 `A` 和 `B` 组成、长度为 $N$ 的字符串 $S$。保证 $S$ 中 `A` 的个数不超过 $\frac{N+1}{2}$。此外，给定一个正整数序列 $(x_1,\ \ldots,\ x_{N-1})$。

你可以对该字符串重复进行如下操作：

- 选择满足 $1\leq i\leq N-1$ 的整数 $i$，交换 $S$ 的第 $i$ 个字符和第 $i+1$ 个字符。该操作的代价为 $x_i$。

你的目标是使 $S$ 中任意两个 `A` 不相邻。请你求出为达成目标所需的总代价的最小值。

有 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 限制条件

- $1\leq T\leq 10^5$
- $2\leq N\leq 10^6$
- $S$ 是由 `A` 和 `B` 组成的长度为 $N$ 的字符串。
- $S$ 中 `A` 的个数不超过 $\frac{N+1}{2}$。
- $1\leq x_i\leq 10^6$
- 所有测试数据中 $N$ 的总和不超过 $10^6$。

### 样例解释 1

- 对于第 $1$ 组测试数据，通过对 $i=1$ 进行操作，$S$ 由 `BAAB` 变为 `ABAB`，目标达成，总代价为 $x_1=3$。
- 对于第 $2$ 组测试数据，不进行任何操作即可达成目标，总代价为 $0$。
- 对于第 $3$ 组测试数据，通过对 $i=1$、$i=4$ 进行操作，$S$ 由 `BAAABBB` 变为 `ABAABBB`，再变为 `ABABABB`，目标达成，总代价为 $x_1+x_4=13$。
- 对于第 $4$ 组测试数据，通过对 $i=4$、$i=3$、$i=5$ 进行操作，$S$ 由 `BAAABBB` 变为 `BAABABB`，再变为 `BABAABB`，再变为 `BABABAB`，目标达成，总代价为 $x_4+x_3+x_5=15$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
4
BAAB
3 4 5
5
BBBBB
1 2 3 4
7
BAAABBB
8 7 6 5 4 3
7
BAAABBB
100 7 6 5 4 3
20
BAABAABBBABAAABBBABB
12 85 37 44 25 14 36 29 71 53 15 47 13 80 14 74 53 76 19```

### 输出

```
3
0
13
15
133```

# 题解

## 作者：konjakujelly (赞：9)

# AGC066D

令 $T$ 为操作之后的字符串，那么如果在 $T$ 的末尾加上一个字符 `B`，那么 $T$ 就可以被表示为若干个 `AB` 和 `B` 拼接的结果。

那么 $T$ 就可以划分为若干的子段，形为 `B` 或 `ABABABAB...`。  
可以断言的是，若一个段为 `B`，则这个位置未发生过交换操作，因为若有 `A` 与这个位置交换过的话，用这个 `A` 与 `B` 直接构成一段 `AB` 显然是更优的。

由此，我们可以 $dp$ 了。  
设 $dp_i$ 表示将原串的前 $i$ 个字符变成可由 `B` 和 `AB` 拼接得来的字符串的最小代价。  

第一种转移为在后面接 `B`，即当原串的第 $i$ 个字符为 `B` 时，有 $dp_i \leftarrow dp_{i-1}$。  

第二种转移为在后面接 `AB` 段；  
将 `A` 视为 $1$，`B`视为 $-1$ 做前缀和，第 $i$ 个位置的前缀和记为 $s_i$，那么有转移：
$$ 
dp_i \leftarrow \min_{s_i=s_j} {dp_j+w_{j+1,i}}
$$
其中 $w_{l,r}$ 表示将 $[l, r]$ 这个区间内的 `A` 移到奇数位置上，`B` 移到偶数位置上的最小代价。  
我们发现若有 $s_j=s_k=s_i,(j<k<i)$， 则 $w_{j+1,i}=w_{j+1,k}+w_{k+1,i}$，所以 $j$ 到 $i$ 的转移是可以被 $k$ 到 $i$ 的转移替代的，所以对于相同的 $s_i$ 只需要使用最后一个出现的位置去进行转移就行了，此时转移总数变为了 $O(n)$。  

剩下的问题就是计算 $w_{l,r}$。  
记 $x_i$ 的前缀和为 $c_i$ ，那么将一个位置为 $i$ 的字符移动到位置 $j$ 的代价为 $|c_{i-1}-c_{j-1}|$，设 $[l,r]$ 中第 $i$ 个 `A` 要移动到位置 $p_i$，那么
$$
w_{l,r}=\sum{|c_{i-1}-c_{p_i-1}|}
$$
我们断言，对于一个满足 $\forall_{l \leq i < r} s_i \neq s_r$ 的区间，要么 $\forall_i {i \leq p_i}$ 要么 $\forall_i {i \geq p_i}$。  
这是由于，仅有当一个前缀满足 `A` 和 `B` 的数量相等之后，后续 $i$ 和 $p_i$ 的大小关系才有可能发生改变，由此结论可得
$$
w_{l,r}=|\sum c_{i-1} - \sum c_{p_i-1}|
$$

至此，$w_{l,r}$ 就可以 $O(1)$ 计算了。

总复杂度 $O(n)$。

---

## 作者：ZnPdCo (赞：3)

我们设 $f_i$ 表示考虑到第 $i$ 个字符的答案，如果 $S_i=\tt B$，那么无论如何 $\tt B$ 都可以直接接到字符串尾部，因为这么做不违反要求。也就是 $f_i=f_{i-1}$。

然后，我们发现，对于一段区间，如果 $\tt A$ 与 $\tt B$ 的数量相等，那么答案只能为 $\tt ABABAB\cdots$ 交替分布。我们设 $w_{l,r}$ 为把区间 $l\sim r$ 变成上面这样分布的最小代价。若 $[j+1,i]$ 的 $\tt A$ 与 $\tt B$ 的数量相等，那么就有 $f_i=f_j+w_{j+1,i}$。

我们把 $\tt A$ 看作 $+1$，$\tt B$ 看作 $-1$，它们的前缀和为 $s$。若 $s_i=s_j$，那么 $[j+1,i]$ 的 $\tt A$ 与 $\tt B$ 的数量相等。
$$
f_i=\min\begin{cases}
f_{i-1} & S_i={\tt B},\\
f_j+w_{j+1,i} & s_i=s_j
\end{cases}
$$
我们考虑如何计算 $w_{l,r}$。设 $c$ 为 $x$ 的前缀和，我们发现交换 $x$ 上和 $y$ 上的字母需要花费 $|c_{y-1}-c_{x-1}|$ 的代价。

我们的目标为将所有的 $\tt A$ 移动到与 $l$ 同奇偶的位置，所以我们可以求出 $[l,r]$ 中 $\tt A$ 的位置 $i$ 以及所有与 $l$ 同奇偶的位置 $j$，代价就是：
$$
\sum|c_j-c_i|
$$
相当于把每个 $\tt A$ **都向后或都向前**移动到距离它最近的一个与 $l$ 同奇偶的位置。

考虑为什么这样做是对的，假如我们有两个 $\tt A$ 的位置 $i_1,i_2$，与两个与 $l$ 同奇偶的位置 $j_1,j_2$。其中 $i_1,i_2<j_1,j_2$。

我们发现把 $i_1$ 移动到 $j_1$ 加上把 $i_2$ 移动到 $j_2$ 的代价，和把 $i_1$ 移动到 $j_2$ 加上把 $i_2$ 移动到 $j_1$ 的代价是一样的。

同时为什么都向后或都向前，而没有一个向后一个向前的配对情况呢？

可以反证，如果存在这种情况，那么一定也是存在都向后或都向前的方案的。

所以上面的答案是正确的。

进一步化简，因为都是向后或都是向前，所以 $c_j-c_i$ 的正负性肯定都是一样的，所以化简为：
$$
|\sum c_j-\sum c_i|
$$
我们可以预处理 $[l,r]$ 中 $\tt A$ 的位置 $i$ 以及所有与 $l$ 同奇偶的位置 $j$ 的前缀和计算即可。

同时，有可能有 $\tt A$ 结尾的情况的存在，这也是合法的，所以我们在结尾添加一个 $\tt B$，这样所有情况都包含了。

---

上面的做法是 $O(n^2)$ 的。容易发现如果区间 $[i,j]$ 是 $\tt A$ 与 $\tt B$ 的数量相等的，$[j+1,k]$ 也是 $\tt A$ 与 $\tt B$ 的数量相等的，那么取 $f_j$ 计算必定不比取 $f_{i-1}$ 计算劣。

因为 $\tt A$ 与 $\tt B$ 的数量相等的，所以 $[i,j]$ 在匹配时肯定可以不跨出边界匹配达到最优解。两个最优解合并也必定是最优解，所以我们只需要找到最后的一个 $s_i$ 的位置即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000010
#define P 998244353
using namespace std;
ll n, Case;
ll x[N], s[N], c[N], c0[N], c1[N], ca[N], f[N];
char str[N];
inline ll w(ll l, ll r) {
	if(l % 2 == 0) return abs((ca[r] - ca[l - 1]) - (c0[r] - c0[l - 1]));
	else return abs((ca[r] - ca[l - 1]) - (c1[r] - c1[l - 1]));
}
void solve() {
	map<ll, ll> ma;
	scanf("%lld %s", &n, str + 1);
	for(ll i = 1; i < n; i ++) {
		scanf("%lld", &x[i]);
	}
	str[++ n] = 'B';
	for(ll i = 1; i <= n; i ++) {
		f[i] = 1e18;
		c[i] = c[i - 1] + x[i];
		ca[i] = ca[i - 1], c0[i] = c0[i - 1], c1[i] = c1[i - 1];
		if(i % 2 == 0) c0[i] += c[i - 1];
		else c1[i] += c[i - 1];
		s[i] = s[i - 1];
		if(str[i] == 'A') {
			s[i] ++;
			ca[i] += c[i - 1];
		}
		else {
			s[i] --;
		}
	}
	ma[0] = 0;
	for(ll i = 1; i <= n; i ++) {
		if(str[i] == 'B') {
			f[i] = f[i - 1];
		}
		if(ma.find(s[i]) != ma.end()) {
			f[i] = min(f[i], f[ma[s[i]]] + w(ma[s[i]] + 1, i)); 
		}
		ma[s[i]] = i;
	}
	printf("%lld\n", f[n]);
}
int main() {
	scanf("%lld", &Case);
	while(Case--) solve();
}
```

---

## 作者：Rainbow_qwq (赞：3)

每个移动的代价都是正的，考虑最终移动完的最优结果是怎样的。

假设只有一连串的 `A`，移动完后一定会变成 `ABABABA`，只是 `AB` 串从哪个位置开始需要确定，而开始的位置是 $O(n)$ 个。

假设有两串 `A`，移动完后的结果可能是两个 `AB` 串；或者相向移动，合起来变成一个大的 `AB` 串。

经过类似的考虑发现，最优的移动是：把一开始的 `A` 连续段切分成左右（也可能不切），再把若干个 `A` 连续段合在一起，变成一个 `ABAB` 串。

可以发现，上述的移动可以概括为：将一个 $AB$ 个数相等的区间变成 `ABABAB..` 或 `BABABA..`。

那么这样的移动只有 $O(n)$ 种，只需要处理 $r_i$ 表示 $[i,r_i]$ 是 $AB$ 个数相等的。每次移动的代价也是固定的，因为把这个区间变成 `ABABAB` 或 `BABABA` 的话 `A` 的移动方向都是相同的，可以前缀和后 $O(1)$ 计算。

设 $f_{i,0/1}$ 表示操作完前 $i$ 个字符，最后一个字符是 $B/A$ 的最小代价。转移只需要枚举下一个操作区间 $[i,r_i]$ 变成 `ABAB` 还是 `BABA`，或者第 $i$ 个字符不操作，复杂度 $O(n)$。[Submission](https://atcoder.jp/contests/agc066/submissions/51960048)

```cpp
#define maxn 1000005
#define inf 0x3f3f3f3f3f3f3f3f

int n,w[maxn],sum[maxn],sum1[maxn],sum2[maxn],r[maxn];
char s[maxn];
int pre[maxn],tmp[maxn];

int f[maxn][2];

void work()
{
	n=read();
	scanf("%s",s+1);
	For(i,1,n-1)w[i]=read();
	For(i,1,n)sum[i]=sum[i-1]+w[i];
	For(i,1,n){
		sum1[i]=sum1[i-1];
		if(s[i]=='A')sum1[i]+=sum[i-1];
		sum2[i]=sum[i];
		if(i>=2) sum2[i]+=sum2[i-2];
	}
	
	For(i,1,n)pre[i]=pre[i-1]+(s[i]=='A'?1:-1);
	int mn=*min_element(pre,pre+n+1);
	For(i,0,n)pre[i]-=mn;
	For(i,0,n)tmp[i]=-1;
	Rep(i,n,0){
		r[i]=tmp[pre[i]];
		tmp[pre[i]]=i;
	}
	
	auto S2=[&](int l,int r){
		return sum2[r]-(l>=2?sum2[l-2]:0);
	};
	auto S1=[&](int l,int r){
		return sum1[r]-(l>=1?sum1[l-1]:0);
	};
	
	For(i,1,n+1) f[i][0]=f[i][1]=inf;
	f[1][0]=0;
	For(i,1,n){
		if(s[i]=='A') f[i+1][1]=min(f[i+1][1],f[i][0]);
		else f[i+1][0]=min(f[i+1][0],min(f[i][0],f[i][1]));
//		cout<<"f: "<<i<<" "<<f[i][0]<<" "<<f[i][1]<<"\n";
		if(r[i-1]!=-1){
			int j=r[i-1];
//			cout<<"i,j "<<i<<" "<<j<<"\n";
			int val=S2(i,j-1)-S1(i,j);
			f[j+1][1]=min(f[j+1][1],min(f[i][0],f[i][1])+abs(val));
//			cout<<"i,val01 "<<i<<" "<<val<<"\n";
			val=S2(i-1,j-2)-S1(i,j);
			f[j+1][0]=min(f[j+1][0],f[i][0]+abs(val));
//			cout<<"i,val10 "<<i<<" "<<val<<"\n";
		}
	}
	int res=min(f[n+1][0],f[n+1][1]);
	cout<<res<<"\n";
}

signed main()
{
	int T=read();
	while(T--)work();
	return 0;
}
```

---

## 作者：rizynvu (赞：1)

首先考虑如果知道了 A 最后的位置，最后的答案是多少。  
记 $s_{1\sim k}, t_{1\sim k}$ 分别为 $S$ 中 A 的位置和最后 A 的位置。  
因为如果交换两个 A 或 B 肯定是不优的，因为这并没有做出实质上的改变，所以说一定是 $s_i$ 最后移到 $t_i$ 的位置上（不然会产生交叉，不优）。  
那么从 $s_i$ 移动到 $t_i$，对应的代价就为 $\sum\limits_{i = \min\{s_i, t_i\}}^{\max\{s_i, t_i\} - 1} x_i$，但这个 $\sum$ 肯定是不希望看到的，于是定义 $x'_i = \sum\limits_{j = 1}^{i - 1} x_i$，那么代价就可以写作 $|x'_{s_i} - x'_{t_i}|$。

下文的 $x$ 指代上面的 $x'$。

考虑到限制 A 不能相邻在形式上有什么特殊。  
考虑从反面考虑，A 相邻的不能是 A 就意味着 A 相邻的一定是 B。  

于是最终的序列一定可以被刻画成许多 AB 和 B 相连接的情况。  
但是不好的一点是末尾的 A 似乎太特殊了，于是考虑手动添加一个 B 并钦定其不能移动（代价为 $+\infty$）。

接下来因为目标是 A，于是考虑最后串的 AB 会有什么性质。  
如果去手玩一下，应该能得到一个结论：每次一定是选 A 和 B 个数相同的段然后变为 AB 不断复制的形式。  
这也是比较好理解的，因为如果找到了这样的段还是要把段内的 A 移到段外，最后肯定会多交换一段距离，对应代价肯定更大。

那么找到了这个性质，就可以考虑 DP 了。  
记 $f_i$ 为考虑了 $S$ 的前 $i$ 个字符的位置分配且占用的就是 $1\sim i$ 的位置的最小代价。  
考虑怎么转移。

1. 这个位置是 B 且钦定这个 B 不在任何一个需要重排的段内。  
   那么这个 B 的位置一定不会发生改变，于是有 $f_i = f_{i - 1}$。
2. 钦定这个位置为一个需要重排的段的段尾。  
   考虑找到段头 $j(j < i)$，那么可以考虑把 A 当作 $1$，B 当作 $-1$ 做前缀和，那么必然有 $s_{j - 1} = s_i$。  
   于是有 DP 转移 $f_i = f_{j - 1} + \operatorname{cost}(j, i)$。  
   其中 $\operatorname{cost}(l, r)$ 指的是 $l, r$ 内重排的代价。

   但是现在有个问题就是 $j$ 的数量可能过多了。  
   考虑到如果有 $k < j$ 满足 $k$ 也可以作为段头，实际上有 $\operatorname{cost}(k, j - 1) + \operatorname{cost}(j, i) = \operatorname{cost}(k, i)$。  
   这是因为 $[k, j - 1]$ 内的 A 和 B 数量也是相同的，所以重排不会影响到 $[j, i]$。  
   所以发现 $f_{k - 1} + \operatorname{cost}(k, j - 1)$ 会转移到 $f_{j - 1}$，就也能让 $f_{k - 1} + \operatorname{cost}(k, j - 1) + \operatorname{cost}(j, i)  = f_{k - 1} + \operatorname{cost}(k, i)$ 转移到 $f_i$ 了。  
   所以说只需要考虑合法的最大的一个 $j$ 转移过来就可以了。

   接下来还有个问题，就是 $\operatorname{cost}(l, r)$ 怎么算。  
   因为钦定了最终的形式是 AB 重复，于是可以知道最后的 A 肯定是在 $l, l + 2, \cdots, r - 1$ 的位置。  
   但是好像还是不是很好做，于是去发掘性质，但是 $\operatorname{cost}$ 本身已经没啥可参考了，于是考虑这个区间 $[l, r]$ 具有的性质。  
   根据前面转移得到的信息，这个 $[l, r]$ 一定不会在中间存在一个断点使得断掉后两部分的 AB 数量相同。  
   那么实际上说明，对于 $[l, r]$ 的每一个前缀，A 的数量都比 B 多，或者是每个前缀 B 数量都比 A 多。  
   这是因为每次前缀和的变化是 $\pm 1$ 的，如果存在小于等于就必然有等于，存在等于就必然有断点，矛盾。  
   那么这又告诉的信息是要么 $s_1 \le l, s_2\le l + 2, \cdots$，要么 $s_1\ge l, s_2\ge l + 2, \cdots$，即每个 $s_i$ 与 $t_i$ 的大小关系（$\le, \ge$）其实是相同的。  
   那么对于 $\sum\limits_{i = 1}^k |x_{s_i} - x_{t_i}|$ 的这个绝对值就可以拆开，套在外面变成 $|\sum\limits_{i = 1}^k x_{s_i} - \sum\limits_{i = 1}^k x_{t_i}|$。  
   这就好做了，对于 $s_i$ 就维护一个关于 A 的前缀和。因为 $t_i \bmod 2$ 是一样的，再维护一个关于下标 $\bmod\ 2$ 的前缀和即可。

最后时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr int maxn = 1e6 + 10;
int n;
char s[maxn];
ll x[maxn], sumb[maxn], suma[maxn], f[maxn];
int w[maxn * 2];
inline void solve() {
   scanf("%d%s", &n, s + 1);
   for (int i = 2; i <= n; i++) {
      scanf("%lld", &x[i]);
      x[i] += x[i - 1];
   }
   s[++n] = 'B', x[n] = 1e18;
   memset(w, -1, sizeof(int) * (n + n + 1));
   memset(f, 0x3f, sizeof(ll) * (n + 1));
   f[0] = 0ll, w[n] = 0;
   for (int i = 1, now = n; i <= n; i++) {
      suma[i] = suma[i - 1];
      if (i > 1) {
         sumb[i] = sumb[i - 2] + x[i];
      }
      if (s[i] == 'A') {
         suma[i] += x[i];
         now++;
      } else {
         f[i] = f[i - 1];
         now--;
      }
      if (~ w[now]) {
         int j = w[now];
         f[i] = std::min(f[i], f[j] + std::abs((sumb[i - 1] - (j ? sumb[j - 1] : 0ll)) - (suma[i] - suma[j])));
      }
      w[now] = i;
   }
   printf("%lld\n", f[n]);
}
int main() {
   for (int T, _ = scanf("%d", &T); T--; ) {
      solve();
   }
   return 0;
}
```

---

## 作者：critnos (赞：0)

我擦为什么你们写的这么短还是线性，我是目光呆滞哥。

dp 比较好想，感受一下，操作可以看做是把若干个互不相交的区间中 AB 个数相等的区间操作成 AB 或者 BA 交替的形式，然后找到每个左端点对应的最小的右端点满足区间中 AB 个数相等，然后记一下操作了前 $i$ 个数、最后一个是 A/B 的答案。

问题是怎么计算这 $n$ 个区间的操作代价。设这个区间是 $[l,r]$，这个区间包含了第 $[L,R]$ 个 A。并且设 $s_i=\sum_{j=1}^{i-1} x_j$，设第 $i$ 个 A 在 $p_i$。不妨设我们在算把区间操作成 AB 交替的代价

* 第 $L\le i\le R$ 个 A 要被丢到 $l+2(i-L)$ 这个位置，代价是 $|s_{p_i}-s_{l+2(i-L)}|$。
* 第 $l\le i\le r,i\equiv l \pmod 2$ 个位置需要接受第 $L+(i-l)/2$ 个 A，代价是 $|s_i-s_{p_{L+(i-l)/2}}|$。

拆掉绝对值，我们在第一条算 $s_{p_{L\sim R}}$ 的贡献，在第二条算 $s_{l\sim r}$ 的贡献，再把条件转化一下，做一些二维数点即可。

时间复杂度 $O(n\log n)$。

[一份提交记录](https://atcoder.jp/contests/agc066/submissions/56155415)

---

## 作者：Acoipp (赞：0)

写在前面：这场 AGC 题出得很好。

这道题要求在交换之后 $\texttt{A}$ 不能相邻，那最后一定是 $\texttt{ABABAB\dots}$ 这样的形态，即 $\texttt{AB}$ 交替，不然不优秀。

为了防止 $\texttt{A}$ 在结尾导致不必要的讨论，我们令这个字符串结尾多一个字符 $\texttt{B}$，那么字符串一定就分成了若干段 $\texttt{B}$ 和若干段 $\texttt{AB}$ 交替。

还有一个性质就是这若干段 $\texttt{AB}$ 交替中的每一段都是原来序列中的一个区间交换得到的，因为从其它区间交换过来不如直接选择相邻的一个匹配。

然后考虑 DP，如果 $s_i=\texttt{B}$，那么 $dp_i \gets dp_{i-1}$，然后我们用前缀和来快速判断一个区间的 $\texttt{A}$ 和 $\texttt{B}$ 个数是否相等，再进行转移，即如果 $[j,i]$ 中两者个数相等，那么 $dp_i \gets dp_{j-1}+w_{j,i}$，$w_{j,i}$ 表示这一段构成 $\texttt{ABAB\dots}$ 的最小花费。

容易发现如果 $[k,i]$ 和 $[j,i]$ 两者数量相等，那么 $[k,j-1]$ 两者数量相等，并且 $w_{k,i}=w_{k,j-1}+w_{j,i}$，所以每次转移只需要找到最近的 $j$ 转移即可，转移数量就是 $O(n)$ 的。

接下来考虑计算 $w_{j,i}$，如果位置 $i$ 上的 $\texttt{A}$ 最终要到位置 $j$ 上，那么答案就要加上 $x_i+x_{i+1}+\dots+x_{j-1}$，对 $x$ 做前缀和，答案加上 $x_{j-1}-x_{i-1}$。

并且所有 $(i,j)$ 要么全部 $i>j$，要么全部 $i<j$，因为如果这个比较符号变化了，那么一定代表有一个位置 $\texttt{A}$ 的数量等于 $\texttt{B}$ 的数量，与前文假设不符，所以 dp 就可以完全优化到 $O(n)$ 了。

代码如下，仅供参考，时空复杂度均为 $O(n)$：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define N 2000005
using namespace std;
const ll W = 1000000;
ll T,n,a[N],dp[N],q[N],c[N],i,f[N],sa[N],sb[N];
char s[N];
inline ll calc(ll l,ll r){return abs((sa[r]-sa[l-1])-(sb[r-1]-sb[l]+c[l-1]));}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n>>(s+1);
		for(i=1;i<n;i++) cin>>a[i];
		s[++n] = 'B';
		for(i=1;i<=n;i++){
			if(s[i]=='A') q[i]=q[i-1]-1;
			else q[i]=q[i-1]+1;
			dp[i]=inf,c[i]=c[i-1]+a[i];
			sa[i]=sa[i-1],sb[i]=sb[i-2]+c[i-1];
			if(s[i]=='A') sa[i]+=c[i-1];
		}
		for(i=-n;i<=n;i++) f[i+W]=inf;
		dp[0]=0,f[0+W]=0;
		for(i=1;i<=n;i++){
			if(s[i]=='B') dp[i]=min(dp[i],dp[i-1]);
			if(f[q[i]+W]!=inf) dp[i]=min(dp[i],dp[f[q[i]+W]]+calc(f[q[i]+W]+1,i));
			f[q[i]+W]=i;
		}
		cout<<dp[n]<<endl;
	}
	return 0;
}
```

---

## 作者：AsiraeM (赞：0)

首先，所有操作完成后的串一定形如一段连续的 `B`，加一段 `AB` 交替，加一段连续的 `B`...... 为了方便，规定 `AB` 交替的段必须以 `A` 开头，以 `B` 结尾。为了方便，规定 `AB` 交替的段必须以 `A` 开头，以 `B` 结尾。  
但这样可能会出现 `ABAB......ABA` 的情况，只要在原串的最后加入一个 `B` 就可以了。不难发现这个 `B` 一定不会移动。  

注意到如果最后的串中有一段连续的 `B`，那么必定没有 `A` 会跨过这一段 `B`，否则在这一段 `B` 中找一个 `B` 与这个 `A` 配成 `AB` 交替的段一定更优。  
因此，定义 $S[i,j]$ 为原串的第 $i$ 到第 $j$ 个字符构成的子串，$A_{i,j}$ 为 $S[i,j]$ 中 `A` 的个数，$B_{i,j}$ 为 $S[i,j]$ 中 `B` 的个数，$C_{i,j}$ 为使 $S[i,j]$ 变为 `AB` 交替的段的最小操作次数。可列出：
$$f_{i}=\min\limits_{A_{j,i}=B_{j,i}}(f_{j-1}+C_{j,i})$$
即每次分出一段在最终串中为 `AB` 交替的串。  
特别地，如果 $S_i=$ `B`，那么还要再额外转移 $f_i=\min(f_i,f_i-1)$，即分出一段在最终串中为连续的 `B` 的串。  
在一段最终串是 `AB` 交替的串中，最优方案显然是原串中第 $i$ 个 `A` 移到最终串中第 $i$ 个 `A` 的位置。一个 `A` 从 $S_a$ 移到 $S_b$（$a<b$）的花费是 $\sum\limits_{i=a}^{b-1}x_i$，记下 $x$ 的前缀和 $Sumx$，可以在 $O(N^2)$ 的时间复杂度内计算所有 $C$。

这个 DP 是 $O(N^2)$ 的，需要优化的地方有二：DP 的转移与 $C$ 的计算。  
根据上面所说的一段在最终串中是 `AB` 交替的串中的最优方案，容易证明，对于一段在最终串中是 `AB` 交替、且存在 $i<k<j$ 使得 $A_{k,j}=B_{k,j}$ 的 $S[i,j]$，$S[k,j]$ 中 `A` 的移动是不会跨过 $k$ 的，因此可以将 $S[i,j]$ 拆成互不影响的 $S[i,k-1]$ 与 $S[k,j]$。  
不停地这样拆分下去，每个 $i$ 就最多只需要考虑一个 $f_{j-1}+C_{j,i}$ 形式的转移，这里 $j$ 满足不存在一个 $j<k<i$ 使得 $A_{k,i}=B_{k,i}$。于是 DP 的转移就变成 $O(N)$ 的。  

同时，注意到仅当 $S[i,j]$ 可以被拆成互不影响的 $S[i,k-1]$ 与 $S[k,j]$ 时，$S[i,j]$ 中才会存在运动方向不相同的 `A`，因此 DP 转移所要用到的 $S[i,j]$ 中 `A` 的运动方向都是相同的，即对于所有 $a$，子串中第 $a$ 个 `A` 在原串中与最终串中位置的前后关系相同。  
因此，可以将 `A` 在原串中位置对应的 $Sumx$ 合并成一项，`A` 在最终串中位置对应的 $Sumx$ 合并成一项，分别记下 $Sumx$ 在奇数位置、偶数位置、原串中为 `A` 的位置的前缀和，就可以 $O(1)$ 计算单个 $C$。  

Code:
```cpp
//Talk is cheap.Show me the code.
#include<bits/stdc++.h>
namespace xcy{
const int MAXN=1000005;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
ll a[MAXN],b[MAXN],c[MAXN],s[MAXN],sc[MAXN][2],f[MAXN],g[MAXN],ls[MAXN<<1],t,n,i,j,k,l;
 
inline void fread(ll &X){ll A=1;X=0;char C=getchar();while(!isdigit(C)&&C!='-')C=getchar();if(C=='-')A=-1,C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();X*=A;}
inline void fout(ll X){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(' ');return;}char C[25]{};ll Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}
inline ll get(ll I,ll J){return llabs((s[I]-s[J])-(sc[I][(J&1)^1]-sc[J][(J&1)^1]));}

int mian()
{
    memset(ls,0xff,sizeof(ls));
    fread(t);while(t--){
    fread(n);ls[n+4]=0;
    for(i=1;i<=n;++i)a[i]=(getchar()=='A'?1:-1);
    for(i=1;i<n;++i)fread(c[i]),c[i]+=c[i-1];
    for(i=1,a[n+1]=-1,b[0]=n+4;i<=n+1;++i)
        b[i]=b[i-1]+a[i],g[i]=ls[b[i]],ls[b[i]]=i,
        s[i]=s[i-1]+(a[i]>0?c[i-1]:0);
    for(i=1;i<=n+1;++i)for(j=0;j<=1;++j)
        sc[i][j]=sc[i-1][j]+((i&1)==j?c[i-1]:0);
    for(i=1;i<=n+1;++i)f[i]=std::min(a[i]<0?f[i-1]:INF,
                       g[i]>=0?f[g[i]]+get(i,g[i]):INF),
                       f[i]=std::min(f[i],INF);
    for(i=0;i<=n+1;++i)ls[b[i]]=-1;
    fout(f[n+1]);putchar('\n');
    }return 0;
}}
int main(){return xcy::mian();}
```

---

