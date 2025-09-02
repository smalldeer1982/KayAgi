# [USACO24DEC] Cowdepenence G

## 题目描述

Farmer John 的 $N$（$1 \leq N \leq 10^5$）头奶牛已经排成一行。第 $i$ 头奶牛的标号是 $a_i$（$1 \leq a_i \leq N$）。如果一些奶牛具有相同的标号，并且他们两两之间的距离都在 $x$ 头牛以内，那么这些奶牛可以组成一个友谊小组（$x$ 是范围 $[1,N]$ 内的一个整数）。每头奶牛必须恰好属于一个友谊小组。

对于从 $1$ 到 $N$ 的每一个 $x$，计算可能组成的友谊小组的最小数量。

## 说明/提示

以下为当 $x=1$ 和 $x=2$ 时将奶牛以最小化小组数量的方式组成友谊小组的一些例子。每个字母对应一个不同的小组。

例：

```
       1 1 1 9 2 1 2 1 1
x = 1: A B B C D E F G G（7 组）
x = 1: A A B C D E F G G（7 组，另一种分组方案）
x = 2: A A A B C D C E E（5 组）
x = 2: A A A B C D C D E（5 组，另一种分组方案）
```

- 测试点 $2\sim 3$：$N\leq 5000$。
- 测试点 $4\sim 7$：对于所有 $i$ 有 $a_i\leq 10$。
- 测试点 $8\sim 11$：没有标号出现超过 $10$ 次。
- 测试点 $12\sim 20$：没有额外限制。

## 样例 #1

### 输入

```
9
1 1 1 9 2 1 2 1 1
```

### 输出

```
7
5
4
4
4
4
4
3
3```

# 题解

## 作者：VitrelosTia (赞：9)

对于固定 $x$，和一个有 $c$ 个的标号，有一个 $O(c)$ 的贪心，考虑从左往右扫，每次一段尽量长，这样答案是 $O(\dfrac n x)$ 的，正确性显然。看到这个答案大小，再观察一手样例发现**答案单调递减**（由于贪心策略显然），就可以想到枚举标号之后根号分治。

当 $x \le B$ 时，直接暴力，复杂度 $O(B\sum c) = O(nB)$。

当 $x > B$ 时，答案只有 $\dfrac n B$ 种，二分变化点，时间复杂度 $O(\dfrac n B 
\log n \sum c) = O(\dfrac n B n \log n)$。

由均值取等，$B$ 取 $\sqrt{n \log n}$。

```cpp
const int N = 1e5 + 5;
int n, B, a[N], ds[N]; vector <int> p[N];
void update(int l, int r, int k) { ds[l] += k; ds[r + 1] -= k; }
int calc(int c, int x) {
    int lst = -1e9, ans = 0;
    for (int t : p[c]) if (t - lst > x) ans++, lst = t;
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; B = sqrt(n * __lg(n));
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]].push_back(i);
    for (int i = 1; i <= n; i++) if (p[i].size()) {
        for (int x = 1; x <= B; x++) update(x, x, calc(i, x));
        for (int x = B + 1; x <= n; ) {
            int l = x, r = n, ans = l, t = calc(i, x);
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (calc(i, mid) == t) l = mid + 1, ans = mid;
                else r = mid - 1;
            }
            update(x, ans, t); x = ans + 1;
        }
    }
    for (int i =  1; i <= n; i++) cout << (ds[i] += ds[i - 1]) << '\n';
    return 0;
}
```

---

## 作者：晴空一鹤 (赞：6)

首先有一个很明显的贪心，对于每种颜色从左至右分组，能和左边的组分到一起就分到一起，不然新开一个组，那么对于每个 $x$ 可以 $O(n)$ 求出答案。

考虑阈值分治，我们对于 $\leq B$ 的 $x$ 直接贪心计算，对于 $\geq B$ 的部分可知每种颜色分成的组数 $\leq \frac{n}{B}$，那么对于每一种可能的组数跑一个二分得到最大的 $x$ 使得最后分成的组数比它大，打上差分标记最后统计答案时做一个前缀和就行了。

时间复杂度 $O(nB+\frac{n^2\log_2{n}}{B})$，取 $B=\sqrt{n\log_2{n}}$ 最优，为 $O(n\sqrt{n\log_2{n}})$，可以通过。

---

## 作者：Chenyichen0420 (赞：5)

## 思路分析

首先贪心一下，每个位置同颜色的靠右分配就能达到最优。

但是，每一次换最远距离就重算时复为 $O(n^2\log n)$，会导致 TLE。所以对于每一个颜色，我们要尽可能减少冗余计算。显然，对于每个颜色两两间的距离出现不同时答案才会更新。这是一个巨大的“剪枝”。

很显然，不同的差不会达到 $n$ 个。而因为重构的时候会除以块的大小，鉴于不同的差的分布，总的复杂度会是 $O(n\sqrt n\log n)$。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[100005], mg, ty, pro;
vector<int>son[100005], nd[100005];
int lov[100005], anp[100005];
inline void get(int x, int a) {
	int ans = 0, np = 0;
	lov[x] = 1e9 + 7; pro -= anp[x];
	while (np < son[x].size()) {
		int cp = upper_bound(son[x].begin(), son[x].end(), son[x][np] + a) - son[x].begin();
		if (cp != son[x].size()) lov[x] = min(lov[x], son[x][cp] - son[x][np]);
		ans++; np = cp;
	}
	if (ans != 1) nd[lov[x]].emplace_back(x);
	anp[x] = ans; pro += ans;
}
signed main() {
	ios::sync_with_stdio(0); cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], son[a[i]].emplace_back(i);
	for (int i = 1; i <= n; ++i)
		if (!son[i].size()) continue;
		else if (son[i].size() == 1) pro++;
		else nd[1].emplace_back(i);
	for (int i = 1; i <= n; ++i) {
		for (int sp : nd[i]) get(sp, i);
		cout << pro << endl;
	}
}
```

---

## 作者：IamZZ (赞：5)

**G 组练习总结#14**

Platinum 组开题，三道 **Benq**，两眼一黑，不省人事。

那就来研究 Gold 组吧。

### 题目大意

FJ 的奶牛们正在交朋友，她们希望组成一个个小组~~促进感情~~。

具体来说，FJ 拥有 $N(N\le 10^5)$ 个奶棚，$i(i\le N)$ 号奶棚里有一只品种为 $a_i(a_i\le N)$ 的奶牛，两个奶棚的距离为编号相减。

奶牛很高傲，只愿意和自己品种相同的奶牛做朋友，同时，为了方便交流，朋友之间的距离不能太远（可能取决于奶牛的嗓门大小吧）。

为了方便管理，FJ 规定奶牛们应组成尽可能少的小组。

现在，他想知道，对于每一个最大交流距离 $x(1\le x\le N)$，最少需要分多少个小组？

### 解题思路

我们首先可以想一些题目的性质，一个小组必定在一段长度小于交流距离的区间里，否则不优。

其次，当我们确定了左端点时，右端点肯定是尽可能大，尽量涵盖更多奶牛。

如果一头奶牛已经超出了左端点的交流范围，新开一组。

#### 暴力

有了这上面的性质，我们可以写出最基础的暴力了，枚举交流距离，扫一遍所有奶牛，超出范围就新开一组，时间复杂度 $\Theta(N^2)$。

这道题目的另外两个部分分很有引导性，解决它们对得出正解有很大帮助。

#### Subtask 1：品种数量不超过 10

既然，品种数量这么少，我们可以考虑对每一个品种单独处理。

思考一下，如果当前的交流距离为 $x$，这个品种的奶牛分组数量不可能大于 $\lceil\frac{N}{x}\rceil$ 个，因为塞不下更多长度为 $x$ 的区间了。

我们找到第一个左端点编号 $pos$，然后在 $pos+x$ 之后找到下一个最近的，设为第二个左端点，同时组数加一。

因为分组数量有上限，这种跳跃的操作不会超过 $\lceil\frac{N}{x}\rceil$ 次。

根据调和级数 $\sum_{x=1}^N\frac{N}{x}\approx N\ln N$，外加一个 $10$ （取决于品种数）的常数，复杂度 $\Theta(N\ln N)$。

跳跃操作可以通过记录数组 $e$ 完成，$e_i$ 表示 $i$ 之后最近的这种品种奶牛的编号。

#### Subtask 2：每个品种的奶牛数量不超过 10

仔细思考，奶牛数量上的限制，同时也限制了什么？

是的，因为每一个小组至少得有一头奶牛吧，小组的数量同时也被限制了。

那我们就可以依据小组的数量来处理答案。

假设我们要求某个品种的奶牛分为 $v$ 组。我们找到满足奶牛被分成了 $v$ 组的最大的交流距离，记这个距离为 $g_v$（用二分）。

我们发现，随着 $v$ 的不断增大，$g_v$ 是不断减小的（理解为**越分越细**），而在 $[g_{v+1}+1,g_v]$ 之间的距离都能用 $v$ 组分配。

我们用一个前缀和，是不是就可以解决每个距离的答案了？时间复杂度 $\Theta(N\log_2N)$，带一个 $10$ （取决于每组数量）的常数。

**解决了两个部分分，有没有发现，问题是不是已经解决了？**

如果将每个品种奶牛数量分开处理，$\le\sqrt N$ 的用 **Subtask 2** 方法，反之用 **Subtask 1** 方法。

我们发现，因为每个品种数量 $\le\sqrt N$，每种奶牛的数量得到了限制，而我们只需要 $\Theta(N\sqrt N \log_2N)$ 的复杂度来处理第一部分。

而对于 $>\sqrt N$ 的品种，这些品种的个数不会超过 $\sqrt N$，我们也可以在 $\Theta(N\sqrt N\ln N)$ 的复杂度内处理第二部分。

综上，我们可以在 $\Theta(N\sqrt N\log_2 N)$ 的时间复杂度内处理这个问题。

完结撒花(●'◡'●)！

### 参考代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,Z=300;
int n,a[N],c[N],e[N],t,o[Z],k,m[N],pos,s,ed[N],to[N],ct[N],sp[N];
int find(int v,int id)//找到最大交流距离g[v]
{
	int l=0,r=sp[v-1],d,x,i,ls,g,ans;//递减的答案，缩小二分范围
    //l可以为0，有些品种的分组有上限，挨太近了
	while(l<=r)
	{
		d=l+r>>1;
		x=to[id],ls=-1e9,g=0;
		for(i=1;i<=c[id];++i)//好比暴力部分，超了范围就开新组
		{
			if(x-ls>d)
			  ++g,ls=x;//更新左端点
			x=ed[x];//同种的下一只奶牛
		}
		if(g>=v)
		  ans=d,l=d+1;
		else
		  r=d-1;
	}
	return ans;
}
void init(int id)//初始化e数组
{
	int i;
	t=n+1;
	for(i=n;i;--i)
	{
		e[i]=t;
		if(a[i]==o[id])
		  t=i;
	}
	return ;
}
int main()
{
	int i,j;
	scanf("%d",&n),sp[0]=n;
	for(i=1;i<=n;++i)
	  scanf("%d",a+i),++c[a[i]];//统计每种奶牛数量
	for(i=1;i<=n;++i)
	{
		if(c[i]>Z)//分类
		  ++k,o[k]=i;
		to[i]=n+1;
	}
	for(j=1;j<=k;++j)
	{
		init(j);//初始化
		for(i=1;i<=n;++i)
		{
			pos=t,s=0;
			while(pos<=n)
			{
				++s;//开新组
				if(pos+i+1>n)
				  break;
				pos=e[pos+i];//i个i个跳跃
			}
			m[i]=m[i]+s;//统计第一部分答案
		}
	}
	for(i=n;i;--i)
	  ed[i]=to[a[i]],to[a[i]]=i;//找到同种的下一只奶牛
	for(i=1;i<=n;++i)
	{
		if(c[i]>Z)
		  continue;
		for(j=1;j<=c[i];++j)
		  ++ct[sp[j]=find(j,i)];//前缀和统计第二部分答案
	}
	s=0;
	for(i=n;i;--i)
	   s=s+ct[i],m[i]=m[i]+s;//前缀和转答案
	for(i=1;i<=n;++i)
	  printf("%d\n",m[i]);
	return 0;
}
```

---

## 作者：happy_zero (赞：4)

显然的贪心：对于每种颜色从左到右扫，没超过距离就加进去，否则新开一组。暴力做是 $O(n^2)$ 的。

观察部分分，一部分是出现次数小于某个值，一个是种类小于某个值，这启示我们进行根号分治。

---
**情况1**：对于每种颜色，若其出现次数 $\le \sqrt n$，则答案也一定不会超过 $\sqrt n$。

可以知道，相同的答案对应的 $x$ 一定是一段区间，所有的 $x$ 被划分成了不超过 $\sqrt n$ 个区间，可以枚举答案，然后二分出对应的区间，那么复杂度则为 $O(n\sqrt n\log n)$。

**情况2**：出现次数超过 $\sqrt n$ 的颜色一定不超过 $\sqrt n$ 种，于是可以直接枚举 $x$，但暴力跳还是会炸。

考虑原来的过程，若一组的左端点为 $l$，则右端点为大于 $l+x$ 的第一个位置。

首先右端点是可以二分的，其次由于一次至少跳 $x$ 长度，最多跳 $\frac{n}{x}$ 次，对于同一种颜色总的复杂度应该是调和级数 $O(n\ln n)$。

---

将 $\ln n$ 近似看为 $\log n$，则总复杂 $O(n\sqrt n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], ans[N], b[N];
vector <int> p[N];
int cal(int i, int x) {
	int res = 1, lst = p[i][0];
	for(auto k : p[i])
		if(k - lst > x) res++, lst = k;
	return res;
}
int main() {
	int n; cin >> n; int sq = sqrt(n) + 1;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], p[a[i]].push_back(i);
	for(int i = 1; i <= n; i++) {
		int len = p[i].size();
		if(len <= sq) {
			if(!len) continue; int now = n;
			for(int j = 1; now; j++) {
				int l = 1, r = now, res = now + 1;
				while(l <= r) {
					int mid = l + r >> 1;
					if(cal(i, mid) <= j) 
						res = mid, r = mid - 1;
					else l = mid + 1;
				}
				b[res] += j, b[now + 1] -= j, now = res - 1;
			}
		} else {
			for(int j = 1; j <= n; j++) {
				int now = 0;
				while(now < len) {
					int l = now, r = len - 1, res = now;
					while(l <= r) {
						int mid = l + r >> 1;
						if (p[i][mid] - p[i][now] <= j)
							res = mid, l = mid + 1;
						else r = mid - 1;
					}
					now = res + 1, ans[j]++;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) 
		b[i] += b[i - 1], cout << b[i] + ans[i] << '\n';
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：4)

每种颜色分开处理。类似整除分块的结论可得，对于 $\le\sqrt n$ 的 $k$ 只有 $\sqrt n$ 种答案，对于 $>\sqrt n$ 的 $k$ 由于划分的段数 $\le\sqrt n$ 也只有 $\sqrt n$ 种不同的答案。

二分找出答案断点的位置，复杂度 $O(n\sqrt n\log n)$。

注意到 $\le\sqrt n$ 的可以不用二分直接枚举。设置一个阈值 $B$，小于 $B$ 暴力，大于 $B$ 二分，那么复杂度是 $O(nB+\frac {n^2}B\log n)$，取 $B=\sqrt{n\log n}$，那么复杂度变为 $O(n\sqrt{n\log n})$。

UPD: 进一步地，引用[ link ](https://codeforces.com/blog/entry/134445)中提供的思路，本题的复杂度其实还可以达到 $O(n\sqrt n)$。

---

## 作者：XGTD (赞：2)

# P11455 [USACO24DEC] Cowdepenence G 题解

## Preface
总体思路就是根号分治。

十二月打了这场的银组没过，~~不服气~~就试了一下金组~~果然被虐~~，这道题一开始常数没写好一直 T 一个点改了两个小时。

## Problem Statement
[P11455](https://www.luogu.com.cn/problem/P11455) 奶牛搞团建。

## Solution
和其他 USACO 题一样，先分析前几个部分分很有帮助，但是这题不一样，前几个部分分和正解的关系非常大,其实就是把第二第三小问的代码合起来。

### Subtask 1

先看第一小问，允许平方复杂度。直接暴力不用我说了吧。

### Subtask 2

第二小问发现只有十种牛，于是可以通过对于每一个种类分别处理，每次枚举 $x$ 用什么，可以二分算出此时分机组，最后将答案全加起来。复杂度为组数也就是十，乘以 $O(N \log N)$。

### Subtask 3

第三小问稍微复杂一点，每种牛最多出现十次，这时有一个非常重要的发现，每一组至少有一头牛（废话），也就是说每种牛最多有十组！此时我们可以逆向思维，不再考虑每一个 $x$ 能分几块（组），而是考虑分成 $j$ 块时 $x$ 至少得是多少。这一可以二分算出，知道了块数的分界线就可以轻松求出每一个 $x$ 的答案。而由于最多十组，复杂度 $O(N \log N)$ 有一个十左右的常数（可别小看这道题常数的威力），可以通过此小问。

### Full Credit

最后再来看正解。首先一个非常重要的发现是，出现次数数超过 $\sqrt{N}$ 的奶牛种类，一共最多 $\sqrt{N}$ 个，而对于这 $\sqrt{N}$ 组，我们可以用第二小问的算法用 $O(N \sqrt{N} \log N)$ 解决。而出现次数小于 $\sqrt{N}$ 的则可以用第三问的算法，同样的复杂度解决。但是这道题做完了吗？还没！像这样你会像我一样 TLE 一个点约零点一秒，因为第一问二分之后其实复杂度还要乘以一个块数，虽然第二小问通过了，但是测试点十三和十四都稍微慢了一点。怎么办？官方题解提供了一种办法，用一个简单的 DP 来代替二分减少了一个 $\log$ 的复杂度。代码里有注释解释。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n, a[100005], ans[100005], ma, c[100005], nex[100005];
vector<int> lab[100005];
vector<int> alg1, alg2;
signed main(){
	std::ios::sync_with_stdio(0);
	n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		ma = max(ma, a[i]);
		lab[a[i]].push_back(i);
	}
	int sq = sqrt(n);
	for(int i = 1; i <= ma; i++){		
		if(lab[i].size() > sq)alg1.push_back(i);
		else if(lab[i].size())alg2.push_back(i);
	}


	//this alg1 is not my actual incontest alg1, rather, a
	//optimaled(both T and M) jumping implementation by the 
	//solution, optimized by a log's complexity
	for(auto i: alg1){
		//all types to be processed by algorithm 1
		//for each x = j
		for(int k = 1; k <= n; k++){
			nex[k] = 0;
		}
		//nex[k] = next number x from k with a[j] = i
		for(auto k: lab[i]){
			nex[k] = k;
		}
		nex[n + 1] = n + 1;
		for(int k = n; k >= 1; k--){
			if(!nex[k])nex[k] = nex[k + 1];
		}
		//that tiny but stunningly effective dp you're
		//seeing above is an extrodinary idea presented
		//by usaco official solution. instead of my 
		//original implemention, which "occationally" runs
		//in time, this implmentation with one less log
		//is gaurenteeed at around 500 ms.
		for(int j = 1; j <= n; j++){
			int pos = lab[i][0];
			while(pos <= n){
				ans[j]++;				
				if(pos + j + 1 <= n)pos = nex[pos + j + 1];
				else break;							
			}
		}
	}
	
	//below is alg2 for subtask 3(ik, confusing naming)
	for(auto i: alg2){
		//for each cow type
		for(int j = 1; j <= lab[i].size(); j++){
			//we want to make j groups
			int l = 1, r = n;
			while(l != r){			
				int mid = l + (r - l) / 2;
				//the x is mid
				int las = lab[i][0], cnt = 1, chec = 1;
				for(int k = 0; k < lab[i].size(); k++){
					if(lab[i][k] - las > mid){
						//exceeded x
						cnt++;
						if(cnt > j){
							//more then j groups made, mid is
							//too small
							chec = 0;
							break;
						}
						las = lab[i][k];
					}
				}
				if(chec)r = mid;
				else l = mid + 1;
			}
			c[l - 1]++;
		}
		c[n + 1]++;
		//every cow type have a starting group
	}
	for(int i = n; i >= 1; i--){
		c[i] += c[i + 1];
	}
	for(int i = 1; i <= n; i++){
		printf("%d\n", ans[i] + c[i]);
	}
	return 0;
}
```
## Result
[AC 记录](https://www.luogu.com.cn/record/197016567)

---

## 作者：cyq32ent (赞：2)

观察可知：当 $x$ 是固定的，对于每一个 $L$，可以通过 $O(N)$ 的贪心解决。

设 $k_L$ 为标签 $L$ 的数量。考虑以下两种方法：

#### 当 $k_L$ 较小时：

设 $c_{i,L}$ 为最小的 $x$，使得标签 $L$ 的奶牛可以分成 $i$ 组。我们对于每个 $i$，使用二分求出 $c_{i,L}$。显然，当 $L$ 固定时，$c_{i,L}$ 是单调减的。对于每个 $L$，求出所有 $c_{i,L}$ 的复杂度为 $\mathcal O(k_L^2\log N)$。我们知道，分为 $i$ 组时，有 $x\in [c_{i},c_{i-1})$。求出后，我们使用差分数组统计贡献即可。

#### 当 $k_L$ 较大时：

设 $d_{i,L}$ 为最小的 $j$，满足 $j\geq i$ 且 $a_j=L$。此时，对于固定的 $x$ 和 $L$，可以通过不断地从当前位置 $i$ 开始，往后跳到 $d_{i+x,L}$ 算出答案。时间复杂度是 $\mathcal O(\frac{N}{x})$。对于每一个 $x$，我们都用相同的算法，那么对于固定的 $L$，时间复杂度为 $\mathcal O(N\log N)$。

我们进行根号分治，设 $B=\sqrt N$ 为分界线，$k_L$ 低于 $B$ 时，使用第一种做法，其余的使用第二种。对于 $k_L$ 低于 $B$ 的部分，时间复杂度约为 $\mathcal O(N B\log N)$，而对于其余部分，由于 $k_L\geq B$，所以这样的 $L$ 最多有 $\frac N B$ 个。所以时间复杂度 $\mathcal O(\frac {N^2} B\log N)$。两者相加，得到的最终复杂度为 $\mathcal O(N^{1.5}\log N)$。

---

## 作者：Kingna (赞：1)

## [P11455 [USACO24DEC] Cowdepenence G](https://www.luogu.com.cn/problem/P11455)

### 题目翻译


Farmer John 的 $N$（$1 \leq N \leq 10^5$）头奶牛已经排成一行。第 $i$ 头奶牛的标号是 $a_i$（$1 \leq a_i \leq N$）。一群奶牛可以组成一个友好小组，如果她们都具有相同的标号，并且每头奶牛都在小组中的其他所有奶牛的 $x$ 头奶牛距离范围内，其中 $x$ 是范围 $[1,N]$ 内的一个整数。每头奶牛必须属于恰好一个友好小组。

对于从 $1$ 到 $N$ 的每一个 $x$，计算可能组成的友谊小组的最小数量。

### 思路

根号分治好题。先用 $n$ 个 `vector` 存储每个值的下标。考虑对于 $x\leq B$ 的情况，对于序列每个值，访问所在下标 vector 进行暴力计算，复杂度为 $O(B \sum c)=O(Bn)$。

对于 $x>B$ 的情况，假设遍历固定 $y$ 值的所在的 vector 下标序列，那么对此计算出的答案至多 $\dfrac{n}{B}$ 种，并且随着 $x$ 增大答案会逐渐变小。那么就至多二分 $\dfrac{n}{B}$ 次寻找答案连续段。比如当前二分出 $x$ 在 $[l,r]$ 区间中使得答案不变为 $t$，那么造成对最终答案的贡献在 $[l,r]$ 区间就会多出 $t$。复杂度为 $O(\dfrac{n}{B}\log n \sum c)=O(n\dfrac{n}{B}\log n)$。

则两部分复杂度总和为 $O(Bn+n\dfrac{n}{B}\log n)$，当 $B=\sqrt{n\log n}$ 时取最小值。

代码：https://pastebin.com/gKsgjRK1

---

## 作者：Istruggle (赞：0)

对于每个 $x$ , 显然分的越长，答案越小，同时我们发现答案具有连续性，也就是说，如果我们单独考虑每个数 对答案的贡献，那么存在区间 $[x,x']$ 答案相同，于是我们可以二分，找到对于一个 $x$ 最大的 $x'$ 进行答案的更新，并将 $x$ 赋值为 $x'+1$ 进行下一轮查找，这样的话时间复杂度为 $\mathcal{O} \left(\frac{n}{x} n\log n\right)$。直接做显然不行，我们考虑对 $x$ 进行根号分治，如果 $x \le B$ 直接暴力查找，时间复杂度 $\mathcal{O}\left(nB\right)$，如果 $x>B$ 则进行二分。由均值不等式得 $nB+\frac{n}{B} n\log n \ge 2\sqrt{nB \times \frac{n}{B} n\log n}$ , 当且仅当 $nB = \frac{n}{B} n\log n$，即 $B = \sqrt{n\log n}$ 时。

---

## 作者：LEE114514 (赞：0)

## 思路

很好的一道题，算是比较巧妙的根号分治了。

一开始拿到题目看到两个特殊性质，我们很容易想到根号分治。不过，按照题目的提示，很容易想到对某种颜色出现次数是否达到 $B$ 进行分类讨论。而且，由于分组必须同颜色，所以我们可以将每种颜色分别计算再求和。不过经过一番思考，你发现这样每种大颜色需要一个 $O(n)$ 计算出所有 $X$ 的算法，小颜色需要一个和颜色出现次数有关而与颜色数无关的算法，这两个问题似乎都解决不了（至少我这种唐王是这样的）。

仔细思考~~瞄一眼题解~~，我们发现另一条路，那就是对 $X$ 进行根号分治。然而前面拆颜色的性质还是需要的。具体的，对出现 $cnt$ 次的颜色 $c$，我们考虑以下两种情况：

1. 若 $x \le B$， 此时有 $O(cnt)$ 计算出这个 $x$ 下的贡献的算法，就是扫描一遍贪心分组。总复杂度是 $O(B \times cnt)$。
2. 否则，当 $x \gt B$ 时，最优方案下每种颜色都不会超过 $O(\frac{n}{B})$ 组，即答案是 $O(\frac{n}{B})$ 的。显然的是答案是单调不升的，即使对每种颜色分开考虑也成立。因此我们二分答案变化点，由于检查的复杂度为 $O(cnt)$，所以二分的复杂度为 $O(\frac{cnt \times n \log n }{B})$。

所有颜色累加，可得前一种情况的复杂度为 $O(nB)$，后一种情况的复杂度为 $O(\frac{n^2 \log n}{B})$。

于是我们取 $B=\sqrt{n \log n}$，此时复杂度最优为 $O(n \sqrt{n \log n})$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int len,n,a[maxn];
int ans[maxn];
int f[maxn];
vector<int> c[maxn];
int calc(int x,int cc){
    int res=0;
    int lst=-1145141;
	for(int y:c[cc]) (y-lst>x)&&(++res,lst=y);
    return res;
}
#define mdf(l,r,x) (ans[l]+=x,ans[r+1]-=x)
int main(){
//	freopen("P11455_8.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",a+i),c[a[i]].emplace_back(i);
	len=sqrt(n*__lg(n));
    for(int x=1;x<=len;++x) for(int i=1;i<=n;++i) mdf(x,x,calc(x,i));
    for(int i=1;i<=n;++i){
	    int lst=len+1;
	    while(lst<n){
	    	int tmp=calc(lst,i);
			mdf(lst,lst,tmp);
	        int L=lst,R=n,MID;
	        while(L<R){
	            MID=(L+R+1)>>1;
	            (calc(MID,i)!=tmp)?R=MID-1:L=MID;
	        }
	        mdf(lst+1,L,tmp);
	    	lst=L+1;
	    }
	}
    for(int i=1;i<=n;++i) printf("%d\n",ans[i]+=ans[i-1]);
}
```

---

## 作者：Add_Catalyst (赞：0)

# 「USACO24DEC G」Cowdepenence 题解

------

## 知识点

根号分治。

## 分析

### $O(n\sqrt{n}\log_2{n})$

我们考虑先将每种颜色分开，然后对于每种颜色分别处理。

可以类比数论分块，我们会发现当距离范围 $x$ 处于某个区间 $[l,r]$ 时，友谊小组的最小数量 $cnt$ 的值是相同的，而且根据数论分块的结论，本质不同的 $cnt$ 数量不会超过 $\sqrt{n}$。

显然 $x,cnt$ 的关系满足单调性，所以我们可以直接暴力二分 $x$ 的阙值，进行检验，并且对每次重复检验的 $x$ 进行**记忆化**，然后差分统计答案。

```cpp
unordered_map<int,int> rec;

void Solve(const Vi &vec) {
	for(int L(1),R(1),c(Check(vec,1)); L<=n; c=Check(vec,L=++R)) {
		for(int l(L+1),r(n),mid((l+r)>>1); l<=r; mid=(l+r)>>1)
			Check(vec,mid)>=c?R=mid,l=mid+1:r=mid-1;
		ans[L]+=c,ans[R+1]-=c;
	}
	rec.clear();
}
```

假设我们现在处理的颜色有 $k$ 个，那么我们有两种检验方法：

- $O(k)$：

  直接一遍扫过去。

  ```cpp
  int Check1(const Vi &vec,const int &lim) {
  	int cnt(0),sta(0);
  	for(const int &x:vec)if(!sta||x-sta>lim)++cnt,sta=x;
  	return cnt;
  }
  ```

- $O(\frac{n}{x}\log_2{k})$：

  我们中间不断二分下一个点。

  ```cpp
  int Check2(const Vi &vec,const int &lim) {
  	int cnt(0),sta(vec.front());
  	while(true) {
  		++cnt;
  		int it(upper_bound(vec.begin(),vec.end(),sta+lim)-vec.begin());
  		if(it==(int)vec.size())break;
  		sta=vec[it];
  	}
  	return cnt;
  }
  ```

我们每次取其中复杂度小的一个。

```cpp
int Check(const Vi &vec,const int &lim) {
	if(rec.count(lim))return rec[lim];
	auto cal=[&]() -> ll { return (ll)rec.size()*lim/n; };
	return rec[lim]=(cal()<20&&(1<<cal())<(int)rec.size()?Check1(vec,lim):Check2(vec,lim));
}
```

时间复杂度 $O(n\sqrt{n}\log_2{n})$。

```cpp
int n;
int a[N],b[N],ans[N];
Vi vec[N];

int Check1(const Vi &vec,const int &lim) {
	int cnt(0),sta(0);
	for(const int &x:vec)if(!sta||x-sta>lim)++cnt,sta=x;
	return cnt;
}

int Check2(const Vi &vec,const int &lim) {
	int cnt(0),sta(vec.front());
	while(true) {
		++cnt;
		int it(upper_bound(vec.begin(),vec.end(),sta+lim)-vec.begin());
		if(it==(int)vec.size())break;
		sta=vec[it];
	}
	return cnt;
}

unordered_map<int,int> rec;

int Check(const Vi &vec,const int &lim) {
	if(rec.count(lim))return rec[lim];
	auto cal=[&]() -> ll { return (ll)vec.size()*lim/n; };
	return rec[lim]=(cal()<20&&(1<<cal())<(int)vec.size()?Check1(vec,lim):Check2(vec,lim));
}

void Solve_Min(const Vi &vec) {
	for(int L(1),R(1),c(Check(vec,1)); L<=n; c=Check(vec,L=++R)) {
		for(int l(L+1),r(n),mid((l+r)>>1); l<=r; mid=(l+r)>>1)
			Check(vec,mid)>=c?R=mid,l=mid+1:r=mid-1;
		ans[L]+=c,ans[R+1]-=c;
	}
	rec.clear();
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n);
	FOR(i,1,n)I(a[i]),b[i]=a[i];
	sort(b+1,b+n+1),b[0]=unique(b+1,b+n+1)-b-1;
	FOR(i,1,n)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	FOR(i,1,n)vec[a[i]].push_back(i);
	FOR(i,1,b[0])Solve_Min(vec[i]);
	FOR(i,1,n)O(ans[i]+=ans[i-1],'\n');
	return 0;
}
```



### $O(n\sqrt{n\log_2{n}})$

发现其实相同颜色中 $x\le \sqrt{n}$ 的部分，直接暴力求解反而更快，这部分复杂度变成了 $O(n\sqrt{n})$。

进一步调整块长，发现如果 $x\le \sqrt{n\log_2{n}}$ 的部分都暴力求解，复杂度就变成了 $O(n\sqrt{n\log_2{n}})$。

```cpp
void Solve(const Vi &vec) {
	FOR(i,1,Bl) {
		int tmp(Check1(vec,i));
		ans[i]+=tmp,ans[i+1]-=tmp;
	}
	for(int L(Bl+1),R(Bl+1),c(Check(vec,Bl+1)); L<=n; c=Check(vec,L=++R)) {
		for(int l(L+1),r(n),mid((l+r)>>1); l<=r; mid=(l+r)>>1)
			Check(vec,mid)>=c?R=mid,l=mid+1:r=mid-1;
		ans[L]+=c,ans[R+1]-=c;
	}
	rec.clear();
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n),Bl=ceil(sqrt(n*log2(n)));
	FOR(i,1,n)I(a[i]),b[i]=a[i];
	sort(b+1,b+n+1),b[0]=unique(b+1,b+n+1)-b-1;
	FOR(i,1,n)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	FOR(i,1,n)vec[a[i]].push_back(i);
	FOR(i,1,b[0])Solve(vec[i]);
	FOR(i,1,n)O(ans[i]+=ans[i-1],'\n');
	return 0;
}
```

### $O(n\sqrt{n})$

> 要求一个整数序列 $(a_1,a_2,\ldots,a_n)$。已知：
>
> - 它是非递增的，即 $a_k \ge a_{k+1}$。
> - $0 \le a_k \le \frac{n}{k}$。
>
> 可以在 $O(C)$ 时间内得到 $a_k$ 的一个值，则可以在 $O(n+\sqrt{n}C)$ 的复杂度内求出整个序列。
>
> ——[Determine A Non-Increasing Integer Sequence of Length n with a[k]<=n/k in O(sqrt(n)) Steps - Codeforces](https://codeforces.com/blog/entry/134445)

我们仿照上面那篇博文分析一下复杂度：

令 $a_0=n+1,a_{n+1}=0$，然后开始分治：

假设现在分治区间为 $[l,r]$，则：

- 如果 $a_{l-1}=a_{r+1}$，则全部赋为同值。
- 否则求出 $a_{mid}$，然后递归 $[l,mid),(mid,r]$。

那么对于深度为 $d$ 的一层，求值操作数量是 $O(2^{\frac{d}{2}})$ 级别的。

所以总复杂度为：
$$
\sum_{d=0}^{\lceil \log_2{n} \rceil} 2^{\frac{d}{2}} \\
$$
即 $O(\sqrt{n})$。那么我们也这么干就可以了。

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define Vi vector<int>
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(1e5+10);

namespace IOEcat {
	//...
} using namespace IOEcat;

int n,Bl;
int a[N],b[N],ans[N];
Vi vec[N];

int Check1(const Vi &vec,const int &lim) {
	int cnt(0),sta(0);
	for(const int &x:vec)if(!sta||x-sta>lim)++cnt,sta=x;
	return cnt;
}

int Check2(const Vi &vec,const int &lim) {
	int cnt(0),sta(vec.front());
	while(true) {
		++cnt;
		int it(upper_bound(vec.begin(),vec.end(),sta+lim)-vec.begin());
		if(it==(int)vec.size())break;
		sta=vec[it];
	}
	return cnt;
}


int Check(const Vi &vec,const int &lim) {
	auto cal=[&]() -> ll { return (ll)vec.size()*lim/n; };
	return cal()<20&&(1<<cal())<(int)vec.size()?Check1(vec,lim):Check2(vec,lim);
}

void Sep(int l,int r,int vl,int vr,const Vi &vec) {
#define mid ((l+r)>>1)
	if(l>r)return;
	if(vl==vr)return ans[l]+=vl,ans[r+1]-=vr,void();
	int vm(Check(vec,mid));
	ans[mid]+=vm,ans[mid+1]-=vm,Sep(l,mid-1,vl,vm,vec),Sep(mid+1,r,vm,vr,vec);
#undef mid
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n),Bl=ceil(sqrt(n*log2(n)));
	FOR(i,1,n)I(a[i]),b[i]=a[i];
	sort(b+1,b+n+1),b[0]=unique(b+1,b+n+1)-b-1;
	FOR(i,1,n)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	FOR(i,1,n)vec[a[i]].push_back(i);
	FOR(i,1,b[0])Sep(1,n,n,1,vec[i]);
	FOR(i,1,n)O(ans[i]+=ans[i-1],'\n');
	return 0;
}
```

---

