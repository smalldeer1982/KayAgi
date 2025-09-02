# [HUSTFC 2023] 逆 KMP

## 题目描述

Walk Alone 是一个字符串大师，但是他已经对传统的字符串算法感到无聊，如 KMP 算法，所以他最近在思考逆向的 KMP。下面是他提出的问题：

给你一个长度为 $n$ 的整数序列 $a$，对于任意的整数 $i\ (1\le i\le n)$，满足 $0\le a_i<i$。你需要构造另一个整数序列 $s$，满足以下条件：
- 序列 $s$ 的长度为 $n$，并且其中任意元素 $s_i$ 满足 $1\le s_i\le n$；
- 对于所有的整数 $i\ (1\le i\le n)$ 和 $j\ (1\le j\le a_i)$，满足 $s_{j}=s_{i-a_i+j}$；
- 满足上述条件的前提下，序列 $s$ 中出现的不同元素的数量**最多**。

当然，Walk Alone 可以很轻松地解决这道题，但他想把这道题当作对你的考验。


## 样例 #1

### 输入

```
5
0 0 1 2 3
```

### 输出

```
1 2 1 2 1 ```

## 样例 #2

### 输入

```
11
0 0 0 0 2 1 0 0 3 0 1
```

### 输出

```
1 2 3 1 2 1 1 2 3 4 1 ```

# 题解

## 作者：LroseC (赞：7)

线下菜比选手来写一篇题解

感觉这题很需要选手通过手玩一些例子发现性质，所以希望大家在阅读这篇题解的同时手玩一下我举出的例子来增进理解。

容易发现若给的是严格的 kmp 算法求出的前缀函数 $next$ 数组，我们容易还原出一个唯一的答案。怎么做呢？显然有若 $next(i) = j$，则 $num(i) = num(j)$。那用并查集把每个 $i$ 和 $next(i)$ 合并起来就好了。

然而给的 $a$ 并不是 $next$ 数组，我们考虑通过还原 $next$ 数组，再求出答案。

我们发现事实上 $a$ 数组应该是对 $next$ 数组的一个限制，有 $next(i) \geq a(i)$。

容易发现另一个限制 $next(i - 1) \geq next(i) - 1$。

使数字的种类变多，就是让重复数字变少。$next$ 本身会导致两端数字相同，因此我们希望 $next$ 尽可能小。

所以我们就要在以上两个限制下，找到一个尽可能小的 $next$ 数组。

举个例子：
```
8
0 0 0 0 3 0 0 2
```
容易还原出 $next$
```
0 0 1 2 3 0 1 2
```
然后意识到，可能会出现两段重合的例子，比如：
```
9
0 0 0 0 0 3 0 3 0
```
其 $next$ 好像是
```
0 0 0 1 2 3 2 3 0
```

但是实际上不对，你尝试一下把答案还原出来就会发现端倪。

在位置 $5$ 处，有后面那个 $3$ 给出一个信息：$next(5) = 1$，其本身自带的 a 数组又给出信息 $next(5) = 3$。

显然要取个 $max$，但是事实上不仅仅是取个 $max$，发现其还隐含信息 $next(3) = 1$。也即有结论：若两个信息重合 $next(i) = a,\ b\ (a > b)$，说明 $next(a) = b$。

所以真正的 $next$ 应该是
```
0 0 1 1 2 3 2 3 0
```

当然，不一定仅仅只有两个重合，但是多个重合的情况大体上差不多。这时容易想到一个大力并查集的暴力：

对于每个 $a(i)$，我们从后往前每次减一直至 $0$，沿途经过的位置，其 $next$ 对我当前推过来的数取 $max$，然后把重复的信息用并查集把他们对应的位置合并起来。同一个集合里的位置上的数应该是一样的。

举个例子吧：
```
10
0 0 0 0 4 0 0 4 0 6
```

大家自己尝试一下把答案求出来。

这个暴力还是不够优秀，我们需要更多的性质和结论优化它。

把结论扩展：

假设某位置 i 被后面的 a 给出了  $next(i) = a, b, c, d,\dots$ 的信息，其中 $a > b > c > d > \dots$

则有 $next(i) = a, next(a) = b,next(b) = c,\dots$。

又有：若 $next(a) = b$, 则所有 $b$ 的 $next$ 都是 $a$ 的 $next$。

容易发现 $next(i) = a, b, c, d, \dots$ 一定会把 $a$ 及其所有包含的 $next$，$b$ 及其所有包含的 $next$, $\dots$ 全部合在一起成为一个形如 $next(x) = y, next(y) = z\dots$ 的 $next$ 长串。

我们用大根堆和并查集维护这个长串。

假设某个堆里维护着位置 $i$ 对应的那个长串，设堆顶为 $y$，则有 $next(i) = y$，毋庸置疑。

用完之后，这个堆接着就应当由 $y$ 继承。但是 $y$ 不仅需要从 $i$ 这里继承一个堆，当然还要考虑到 $a(y)$ 本身给了 $next(y) = a(y)$ 以及 $next(y + 1)$ 给了 $next(y) = next(y + 1) - 1$ 两个信息，所以  $y$ 真正的长串还需要加入 $a(y)$ 及其 $next$，$next(y + 1) - 1$ 及其 $next$。

现在问题在于，$a(y)$ 及其 $next$ 们不一定对应着一个堆（因为堆里可能有着更大的元素）。好在这不影响我们求出 $next(y)$，我们取个 $max$ 即可。

接下来这个堆去往何方？堆里的次次大值吗？事实上 $a(y)$ 和 $next(y + 1) - 1$ 也成为了合法继承人之一，所以我们把他们加进堆里。然后我们就发现这个堆似乎不是在维护对应的长串了，因为 $a(y)$ 的 next 们和 $next(y + 1) - 1$ 的 next 们还没被放进来呢。

但是我们发现，这不影响堆里比 $a(y)$ 和 $next(y + 1) - 1$ 大的位置的答案。而对于 $a(y)$ 与 $next(y + 1) - 1$，我们发现，如果把大于它们的位置先全处理了，那么它的 $next$ 们虽然不存在于一个堆里，但是把其需要继承的堆全合并起来就是完整的 $next$ 们了。

所以我们用并查集和堆启发式合并来维护这个过程。我们发现堆里的总元素个数是 $O(n)$ 的，所以复杂度是 $O(n\log^2n)$，写可并堆就是严格 $O(n \log n)$ 的了。

#### 参考代码
```cpp
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <algorithm>

using i32 = int32_t;
using i64 = int64_t;

#define read std::cin

const int N = 2e5 + 10;

int n;
int vis[N];
int nex[N], fa[N];
std::priority_queue<int> heap[N]; 

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(i32 x, i32 y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (x < y) std::swap(x, y);
	if (heap[x].size() > heap[y].size()) std::swap(heap[x], heap[y]);
	fa[x] = y;
	while (heap[x].size()) {
		heap[y].emplace(heap[x].top());
		heap[x].pop();
	}
}

int main(void)
{
	//Think twice, code once!
	std::ios::sync_with_stdio(false);
	read >> n;
	for (i32 i = 1; i <= n; ++i) {
		fa[i] = i;
		heap[i].emplace(i);
		read >> nex[i];
	}
	for (i32 i = n; i >= 1; --i) {
		auto& hp = heap[find(i)];
		while (hp.size() && hp.top() >= i) hp.pop();
		if (nex[i]) {
			hp.emplace(nex[i]);
		}
		if (nex[i + 1] > 1) {
			hp.emplace(nex[i +1] - 1);
		}
		nex[i] = hp.size() ? hp.top() : 0;
		merge(i, nex[i]);
	}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
	}
	i32 res = 1;
	for (i32 i = 1; i <= n; ++i) {
		if (nex[i]) fa[find(i)] = find(nex[i]);
	}
	for (i32 i = 1; i <= n; ++i) {
		i32 f = find(i);
		printf("%d ", vis[f] ? vis[f] : (vis[f] = res++));
	}
	puts("");
	return 0;
}
```


---

## 作者：meyi (赞：5)

赛时：这不是我们 [[SCOI2016] 萌萌哒](https://www.luogu.com.cn/problem/P3295) 吗？没想到都火出省了，转载请注明出处。

基于倍增并查集思想，设 $fa_{i,j}$ 表示 $[i,i+2^j]$ 与 $[fa_{i,j},fa_{i,j}+2^j]$ 完全相同，发现只需要合并 $\log n$ 次，在所有操作结束后将 $fa_{i,j}$ 下放到 $fa_{i,j-1}$，故总时间复杂度为 $O((n+q)\log n\ \alpha(n)$。

有一个细节就是题目要求不同元素数量最多且答案字典序最小，所以我们在合并的时候将较大的下标的 $fa$ 设为较小的下标，并且在分配答案的时候贪心的将当前未出现的最小的正整数分配给当前第一个没有答案且 $fa$ 是自己的位置即可。

代码：
```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100005;
int ans[maxn], n, fa[maxn][17];
int find(int x, int k) {
	return fa[x][k] == x ? x : fa[x][k] = find(fa[x][k], k);
}
void merge(int x, int y, int k) {
	x = find(x, k), y = find(y, k);
	if(x<y)swap(x,y);
	if(x != y) fa[x][k] = y;
}
int main() {
	scanf("%d", &n);
	const int maxk = __lg(n);
	for(int i = 1; i <= n; ++i)
		for(int k = 0; k <= maxk; ++k)
			fa[i][k] = i;			
	for(int i = 1, l1, r1, l2, r2; i <= n; ++i) {
		int x;
		scanf("%d",&x);
		if(x){
			l1=1,r1=x,l2=i-x+1,r2=i;
			for(int k = maxk; ~k; --k)
				if(l1+(1<<k)-1 <= r1) merge(l2, l1, k), l1 += 1<<k, l2 += 1<<k;
		}
	}	
	for(int k = maxk; k; --k)
		for(int i = 1; i+(1<<k)-1 <= n; ++i) {
			int pos = find(i, k);
			merge(i, pos, k-1), merge(i+(1<<k-1), pos+(1<<k-1), k-1);
		}
	int cnt=0;
	for(int i = 1; i <= n; ++i){
		if(find(i,0) == i) ans[i]=++cnt;
		else ans[i]=ans[find(i,0)];
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：1)

## 解法

可以发现这个限制就相当于对于所有 $a_i>0$ 的 $i$，区间 $[1,a_i]$ 和 $[i-a_i+1,i]$ 完全相同。  
可以发现这其实就是 [P3295](https://www.luogu.com.cn/problem/P3295)，双倍经验。  
首先暴力做法就是扫一遍区间，把对应点加入并查集中，这样是 $O(n^2\alpha(n))$ 的，考虑优化。  
由于并查集的并操作具有可合并性，所以我们可以考虑上倍增加速。  
具体而言，我们把一个点拆成 $\log n$ 个点，分别代表从点 $i$ 开始，长为 $2^k$ 的区间。  
那么我们处理限制的时候，对区间做二进制拆分，会拆成 $\log n$ 个区间，分别执行并查集的并操作即可。  
这样还没完，由于我们最终只会查询长度为 $1$ 的区间，所以我们还需要下放关系。  
也就是我们从最长的区间开始枚举，查找它的祖先，把它和它的祖先都分成两半，分别合并两者的前半部分和后半部分。  
这样最终我们就知道了哪些点是相同的，时间复杂度 $O(n\log n)$（忽略并查集）。  
至于要求序列的字典序最小，看看代码就知道了。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define all(x,l,r) &(x)[l],&(x)[r]+1
#define bit(x) (1ll<<(x))
const int N=2e5+5;
int n,a[N];
int tot,ans[N];
int lg[N],fa[30][N];
void init(){
    per(i,2,n) lg[i]=lg[i>>1]+1;
    per(i,0,lg[n]) iota(all(fa[i],1,n),1);
}
int find(int k,int x){
	return fa[k][x]==x?x:fa[k][x]=find(k,fa[k][x]); 
}
void merge(int k,int x,int y){
	x=find(k,x);y=find(k,y);
	if(x!=y) fa[k][x]=y;
}
void update(int l1,int r1,int l2,int r2){
    if(l1==l2) return;
    rep(k,lg[n],0) if(l1+bit(k)-1<=r1){
        merge(k,l1,l2);
        l1+=bit(k);
        l2+=bit(k);
    }
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;init();
    per(i,1,n) cin>>a[i];
    per(i,1,n) if(a[i])
        update(1,a[i],i-a[i]+1,i);
    rep(i,lg[n],1) per(j,1,n-bit(i)+1){
		int p=find(i,j);
		merge(i-1,j,p);
		merge(i-1,j+bit(i-1),p+bit(i-1));
	}
	per(i,1,n) if(!ans[find(0,i)])
		ans[find(0,i)]=++tot;
	per(i,1,n) cout<<ans[find(0,i)]<<" \n"[i==n];
	return 0;
}
```

---

## 作者：Sampson_YW (赞：0)

题目中的条件相当于给定了一些相等的位置（给出的不是 kmp 的 $\text{fail}$ 数组！不会有人和我一样看错了吧）

将相等的位置合并成同一个等价类就容易填方案了。首先让不同的元素数量最多，那么就是每一个等价类的字符都不同。然后让字典序最小，那么从前往后填就行了。

那么只需要合并相同的位置。暴力合并是 $O(n^2)$ 的。但是注意到一开始等价类只有 $n$ 个，每合并一次就会减少一个。那么有效的合并次数只有 $O(n)$ 次。因此考虑加速找不同等价类的过程。

设 $f_i$ 为 $i$ 当前所属的等价类。假如我们要合并 $[1, a_x]$ 和 $[x-a_x+1,x]$ 对应位置上的等价类，可以找到第一个位置 $y$ 使得 $f_y\neq f_{x-a_{x}+y}$，然后将他们合并，然后继续往后找这样的 $y$。$f$ 可以使用并查集维护。那么怎么找这个 $y$ 呢？

考虑维护整个 $f$ 序列：对每个等价类维护其中的元素，合并两个等价类的时候启发式合并一下，并依次修改被合并掉的等价类中的元素的 $f$ 值。找 $y$ 就变为找某两个区间的最长公共前缀。使用线段树维护 $f$ 的子区间哈希值即可做到 $O(n\log^2n)$。

[code](https://www.luogu.com.cn/paste/9gcob5he)

---

