# [USACO24JAN] Cowmpetency S

## 题目描述

Farmer John 正在为他的奶牛们雇用一位新的牛群领队。为此，他面试了 $N$（$2\le N\le 10^5$）头奶牛来担任该职位。在面试第 $i$ 个候选牛后，他会为候选牛分配一个 $1$ 到 $C$（$1\le C\le 10^9$）范围内的整数「牲任力」分数 $c_i$，与她们的领导能力相关。

由于 Farmer John 面试了如此多的奶牛，他没能记得所有奶牛的牲任力分数。然而，他确实记得 $Q$（$1\le Q<N$）对数字 $(a_j,h_j)$，其中奶牛 $h_j$ 是第一头比奶牛 $1$ 到 $a_j$ 拥有严格更高牲任力分数的奶牛（所以 $1\le a_j<h_j\le N$）。

Farmer John 现在告诉你序列 $c_1,\ldots,c_N$
（其中 $c_i=0$ 表示他忘记了奶牛 $i$ 的牲任力分数）和 $Q$ 对 $(a_j,h_j)$。帮助他求出与此信息一致的最小字典序的牲任力分数序列，或者判断不存在这样的序列！如果一个分数序列比另一个分数序列于这两个序列不同的第一个位置上的奶牛分配了更小的分数，则这个分数序列的字典序更小。

每个测试点包含 $T$（$1\le T\le 20$）个独立的测试用例。输入保证所有测试用例的 $N$ 之和不超过 $3\cdot 10^5$。 

## 说明/提示

### 样例解释 1

我们可以看到给定的输出满足所有 Farmer John 记得的数对。

- $\max(c_1)=1$，$c_2=2$ 且 $1<2$，故第一个数对是满足的
- $\max(c_1,c_2,c_3)=2$，$c_4=3$ 且 $2<3$，故第二个数对是满足的
- $\max(c_1,c_2,c_3,c_4)=3$，$c_5=4$ 且 $3<4$，故第三个数对是满足的

存在一些其他的序列与 Farmer John 的记忆相一致，如

$1\ 2\ 2\ 3\ 5\ 4\ 1$  
$1\ 2\ 2\ 3\ 4\ 4\ 5$

然而，其中没有序列比给定的输出字典序更小。 

### 样例解释 2

在测试用例 $3$ 中，由于 $C=1$，唯一可能的序列是

$1\ 1$

然而，在这种情况下，奶牛 $2$ 的分数并不比奶牛 $1$ 高，因此我们无法满足条件。

在测试用例 $5$ 中，$a_1$ 和 $h_1$ 告诉我们奶牛 $6$ 是第一头分数严格高于奶牛 $1$ 到 $4$ 的奶牛。因此，奶牛 $1$ 到 $6$ 的最高得分是奶牛 $6$，为 $5$。由于奶牛 $7$ 的分数为 $7$，所以奶牛 $7$ 是第一头比奶牛 $1$ 到 $6$ 得分更高的奶牛。因此，第二个陈述「奶牛 $9$ 是第一头比奶牛 $1$ 到 $6$ 得分更高的奶牛」不能成立。 

### 测试点性质

 - 测试点 $3$：$N \le 10$ 且 $Q,C\le 4$。
 - 测试点 $4-8$：$N\le 1000$。
 - 测试点 $9-12$：没有额外限制。

## 样例 #1

### 输入

```
1
7 3 5
1 0 2 3 0 4 0
1 2
3 4
4 5```

### 输出

```
1 2 2 3 4 4 1```

## 样例 #2

### 输入

```
5
7 6 10
0 0 0 0 0 0 0
1 2
2 3
3 4
4 5
5 6
6 7
8 4 9
0 0 0 0 1 6 0 6
1 3
6 7
4 7
2 3
2 1 1
0 0
1 2
10 4 10
1 2 0 2 1 5 8 6 0 3
4 7
1 2
5 7
3 7
10 2 8
1 0 0 0 0 5 7 0 0 0
4 6
6 9```

### 输出

```
1 2 3 4 5 6 7
1 1 2 6 1 6 7 6
-1
1 2 5 2 1 5 8 6 1 3
-1```

# 题解

## 作者：vegetable_king (赞：19)

[可能更好的阅读体验](https://yjh965.github.io/post/usaco24jan-cowmpetency-s-ti-jie)

**一个不需要任何数据结构，代码好写，而且时间复杂度严格 $O(n)$ 的解法！**

下文中令 $a$ 为题目中的 $c$ 序列。

考虑一对限制 $(x, y)$ 的本质是什么。根据题意得知，$\max_{i = 1}^x a_i < a_y$，且 $a_k \le \max_{i = 1}^x a_i(x < k < y)$，于是可以推出 $\max_{i = 1}^{y - 1} a_i < a_y$，也就是说。$a_k(x < k < y)$ 一定不是严格前缀最大值，而 $a_y$ 一定是严格前缀最大值。

于是我们可以 $O(n)$ 求出数组 $b$，$b_i = -1/0/1$，表示 $a_i$ 一定不是 / 不一定是 / 一定是 前缀最大值，或者推出矛盾（即一个位置同时应该是 $-1, 1$ 的情况），判无解即可。

考虑构造。首先我们考虑 $a$ 全都不确定的情况，此时是简单的，$b_i = 1$ 时令 $a_i = \max_{j = 1}^{i - 1} a_j + 1$，否则令 $a_i = 1$ 即可。

如果当前的 $a_i$ 确定了，那我们考虑判断合不合法。

1. 如果 $b_i = 1$ 且 $a_i \le \max_{j = 1}^{i - 1} a_j$ 则一定无解，因为我们在最小化字典序的同时最小化了前缀 $\max$。
2. 如果 $b_i = -1$ 且 $a_i > \max_{j = 1}^{i - 1}$，则我们考虑往前找到一个最大的 $p$ 使得 $a_p$ 未确定且 $b_i \ne -1$，令 $a_p = a_i$ 来满足 $a_i$ 的限制。如果找不到这样的 $p$ 那么显然无解；调整后 $a_p$ 可能会与 $[p + 1, i - 1]$ 中的一些位置的限制冲突，此时也一定无解。因为冲突的位置 $o$ 一定满足 $a_o$ 确定了，且 $b_o = 1$，而这样的位置相当于给前缀 $\max$ 设置了上界。

于是我们可以做到 $O(n)$ 构造并且判定是否有解。[代码](https://www.luogu.com.cn/paste/nlgubm4q)在这里。

---

## 作者：Aria_Math (赞：19)

是线性的哦。

考虑在前缀 $\max$ 上分析。限制 $(a,h)$ 代表前缀 $\max$ 从 $a$ 到 $h-1$ 都相等，并在 $h$ 处有增加。把所有限制全部拿出来，可以得到每个前缀 $\max$ 无要求/与上一处相等/比上一处大。设前缀 $\max$ 为 $pre$：

- 若无要求/与上一处相等：填 $1$ 即可。
- 比上一处大：填 $pre_{i-1}+1$。

有一个特例：要求 $pre_i=pre_{i+k}$，但 $a_{i+k}$ 是一个很大的常量，此时需要找到 $i$ 前面第一个能填的数，把那个位置设为 $a_{i+k}$。

最后判一下是否合法即可。代码是赛时的，比较丑。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Node { int u, v; } b[N];
int n, q, c, a[N], lst[N], dsu[N], tag[N], pre[N];
void Solve() {
	scanf("%d%d%d", &n, &q, &c);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), lst[i] = a[i] ? lst[i - 1] : i;
	for(int i = 1, u, v; i <= q; ++i) scanf("%d%d", &u, &v), b[i] = {u, v - 1};
	for(int i = 1; i <= n; ++i) dsu[i] = i + 1;
	for(int i = 1; i <= q; ++i) dsu[b[i].u] = b[i].v + 1, tag[b[i].v + 1] = 1;
	pre[0] = 1;
	for(int i = 1; i <= n; ++i) { // 求出每个点的 pre
		pre[i] = pre[i - 1] + tag[i];
		for(int j = i; j < dsu[i]; ++j) pre[i] = max(pre[i], a[j]);
		for(int j = i; j < dsu[i]; ++j) pre[j] = pre[i];
		i = dsu[i] - 1;
	}
	bool isOK = 1;
	for(int i = 1; i <= n; ++i) { // 根据 pre 求出 a
		if(!a[i]) a[i] = pre[i - 1] == pre[i] ? 1 : pre[i];
		else if(pre[i] != pre[i - 1] && pre[i] > a[i])  {
			if(lst[i]) a[lst[i]] = pre[i];
		}
		if(a[i] > c) isOK = 0;
		pre[i] = max({pre[i], pre[i - 1], a[i]});
		tag[i] = 0;
	}
	for(int i = 1; i <= n; ++i) pre[i] = max(pre[i - 1], a[i]);
	for(int i = 1; i <= q; ++i) 
		if(pre[b[i].u] < pre[b[i].v] || pre[b[i].u] == pre[b[i].v + 1]) isOK = 0;
	if(!isOK) printf("-1\n");
	else for(int i = 1; i <= n; ++i)
		printf("%d%c", a[i], i == n ? '\n' : ' ');
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	int t; scanf("%d", &t);
	while(t--) Solve();
	return 0;
}
```

---

## 作者：hytallenxu (赞：14)

## 题目大意
给定一个序列 $c$（表示奶牛的能力值）和 $n$ 个条件。

第 $i$ 个条件说明了第 $h_j$ 个奶牛必须是**第一个**比前 $a_i$ 个奶牛**能力值高**的奶牛。

问是否有符合所有条件的序列。如果有，输出**字典序最小的**。如果没有，输出 $-1$。

## 思路
这题完全可以评蓝。

观察题面不难发现需要维护区间修改和区间最大值，这个时候我们可以选用线段树来维护。笔者赛时写的线段树，但由于方便大家理解，代码部分换成分块。

首先对条件按照 $a_i$ 排序。这是一种贪心。

然后对于每一个条件，设定三个值：

1. 区间 $[1,a_i]$ 的最大值。（设为 $x$。）

2. 区间 $[1,h_i-1]$ 的最大值。（设为 $y$。）

3. 区间 $[1,h_i]$ 的最大值。（设为 $z$。）

我们做出如下判断：

1. 假如 $x=z$：

表示代表 $c$ 数组位于 $h_i$ 的值需要更新（因为 $z$ 一定要**大于等于** $x$）。

这里又分两种情况：

1）$c$ 数组在 $h_i$ 这个位置已经被占用（即非 $0$）。

2）$c$ 数组在 $h_i$ 这个位置可以被占用（即 $0$）。

对于第一种 case，直接输出 $-1$（没办法修改了就肯定不符合条件了）。

而对于第二种 case，直接修改 $c_{h_i}$ 为 $x+1$ **以保证字典序最小**。

2. 假如 $x<y$：

表示 $c_{h_i}$ 并不是**第一个**大于 $c_{a_i}$ 的位置。

此时需要从 $a_i$ **倒序**搜到 $1$ 号位置看是否**存在**一个位置原先是 $0$（表示能填入 $y$），使得 $h_i$ 前面没有数大于区间 $[1,a_i]$ 的最大值。

这样就可以保证 $h_i$ 是**第一个**大于区间 $[1,a_i]$ 的最大值的位置。

后面的事情就好说了。

1) 尝试把所有位置的 $0$ 填为 $1$。

2) 检查有没有数字大于 $C$。

3) 重新扫一遍条件，假如出现 $x<y$ 或者 $x=z$ 的话就输出 $-1$。

4) 输出序列。

## Code
代码放在了[剪贴板](https://www.luogu.com.cn/paste/gyy95rmx)。

---

## 作者：Genius_Star (赞：7)

### 题意：

给定 $n$ 组约定条件 $(l_i,r_i)$，需要满足 $l_i + 1 \sim n$ 中第一个大于 $\max\limits_{i=1}^{l_i} \Big( a_i \Big)$ 的位置在 $r_i$。

目前 $a$ 中有些值确定，有些值待定，你需要找到符合条件且字典序最小的序列 $a$。

### 思路：

感觉下位蓝？细节有点儿多。

先对于第 $i$ 数找到前一个不确定值的位置 $last_i$。

然后将约束条件按照 $l_i$ 从小到大排序，对于每组约束条件，记：

- $Max_1$ 为 $[1,l_i]$ 内 $a$ 的最大值。

- $Max_2$ 为 $[l_i+1,r_i-1]$ 内 $a$ 的最大值。

如果 $Max_2>Max_1$ 了，说明 $a_{r_i}$ 肯定不是第一个大于 $Max_1$ 的数，此时有两种情况：

- 如果 $last_{l_i}$ 是存在的，即我们可以修改 $[1,l_i]$ 范围内的值，因为要使得字典序最小，可以令 $a_{last_{l_i}} \to Max_2$，那么现在 $Max_1$ 也变化为 $Max_2$。

- 否则，这个区间是固定的了，没有满足要求的编排方案，输出 $-1$。

之后再次判断 $a_{r_i}$ 的值，分三种情况：

- 如果 $a_{r_i}$ 的值是确定的，判断是否满足 $a_{r_i}>Max_1$ 这个条件。

- 如果是不确定的，且 $Max_1=0$，表示 $[1,l_i]$ 也都不确定，则 $a_{r_i}$ 至少应该是 $2$。（因为肯定要留 $1$ 在前面的位置）

- 如果是不确定的，且 $Max_1 \ne 0$，则要使得字典序最小，令 $a_{r_i} \to Max_1 + 1$。

经过上面的判断之后，对于当前还没有确定下来的值，因为要使得字典序最小，直接令其为 $1$ 即可。

注意，最后为了保险起见，我们可以再按照约束条件检查一遍；且 $a$ 中每一个数都应该 $\le c$。

上面需要求区间最大值，且支持单点修改，可以使用线段树进行维护。

时间复杂度为 $O(T \times N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char a=getchar();
    while(a<'0'||a>'9'){
        if(a=='-')
          f=-1;
        a=getchar();
    }
    while(a>='0'&&a<='9'){
        x=(x<<1)+(x<<3)+(a^48);
        a=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r;
	ll Max;
}X[N<<2];
struct St{
	ll l,r;
	bool operator<(const St&rhs)const{
		return l<rhs.l;
	}
}s[N];
ll T,n,m,c,x,y;
ll a[N],last[N];
void pushup(ll c){
	X[c].Max=max(X[c<<1].Max,X[c<<1|1].Max);
}
void build(ll c,ll l,ll r){
	X[c].l=l,X[c].r=r;
	if(l==r){
		X[c].Max=a[l];
		return ;
	}
	ll mid=(l+r)>>1;
	build(c<<1,l,mid);
	build(c<<1|1,mid+1,r);
	pushup(c);
}
void add(ll c,ll i,ll v){
	if(X[c].l==i&&i==X[c].r){
		X[c].Max=v;
		return ;
	}
	ll mid=(X[c].l+X[c].r)>>1;
	if(i<=mid)
	  add(c<<1,i,v);
	else
	  add(c<<1|1,i,v);
	pushup(c);
}
ll qureyMax(ll c,ll l,ll r){
	if(l>r)
	  return 0;
	if(X[c].l==l&&r==X[c].r)
	  return X[c].Max;
	ll mid=(X[c].l+X[c].r)>>1;
	if(r<=mid)
	  return qureyMax(c<<1,l,r);
	else if(l>mid)
	  return qureyMax(c<<1|1,l,r);
	else
	  return max(qureyMax(c<<1,l,mid),qureyMax(c<<1|1,mid+1,r));
}
void solve(){
	n=read(),m=read(),c=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!a[i])
		  last[i]=i;
		else
		  last[i]=last[i-1];
	}
	for(int i=1;i<=m;i++)
	  s[i]={read(),read()};
	sort(s+1,s+m+1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		ll l=s[i].l,r=s[i].r;
		ll Max1=max(1ll,qureyMax(1,1,l)),Max2=qureyMax(1,l+1,r-1);
		if(Max2>Max1){
			if(!last[l]){
				puts("-1");
				return ;
			}
			a[last[l]]=Max2;
			add(1,last[l],Max2);
			Max1=Max2;
		}
		if(a[r]!=0){
			if(Max1>=a[r]){
				puts("-1");
				return ;
			}
		}
		else{
			if(!Max1){
				a[r]=2;
				add(1,r,2);
			}
			else{
				a[r]=Max1+1;
				add(1,r,Max1+1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!a[i])
		  a[i]=1;
		if(a[i]>c){
			puts("-1");
			return ;
		}
	}
	for(int i=1;i<=m;i++){
		if(qureyMax(1,1,s[i].l)>=a[s[i].r]||qureyMax(1,s[i].l+1,s[i].r-1)>=a[s[i].r]){
			puts("-1");
			return;
		}		
	}
	for(int i=1;i<=n;i++){
		write(a[i]);
		if(i!=n)
		  putchar(' ');
	}
	putchar('\n');
}
int main(){
//	freopen("A.in","r",stdin);
	T=read();
	while(T--)
	  solve();
	return 0;
}
```


---

## 作者：Mirage_Insane (赞：5)

我们先分析题目：

对于一个限制 $(a, b)$，其实就是规定了下面这两个东西：

1. $ \max \{c_1, c_2,\ldots, c_a\} < c_b$。


2. $ \max \{c_1, c_2,\ldots, c_a\} \geq \max \{c_{a + 1}, c_{a + 2},\ldots, c_{b - 1}\}$。

我们还可以得到： $c_b = \max \{c_1, c_2,\ldots, c_b\}$。这个东西我们留到最后再来用。

考虑贪心。

对于每一个位置 $i$，我们记录一下他前面有哪些点 $j$ 与它之间有 $(j, i)$ 的限制。由于后面的点的值的选取很可能受到前面的点的值的限制，于是我们按照 $i$ 从小到大， $j$ 从小到大的顺序依次解决每一个限制（ $i$ 为第一关键字， $j$ 为第二关键字）。

由于一段区间的 ``max`` 值是只增不减的，无论你新填的值有多小，都不会导致这个 ``max`` 变小。于是对于 $(a, b)$ 的限制，如果不满足限制 2，那只能选择在区间 $[1, a]$ 中新填一个更大的值来使得该区间的 ``max`` 值变大。这当然会影响 $c_b$ 的取值。所以我们要先去满足限制 2，再去考虑限制 1。

我们令 $sum1 = \max \{c_1, c_2, \ldots, c_a\}, sum2 = \max \{c_{a + 1}, c_{a + 2}, \ldots, c_{b - 1}\}$。当 $sum1 < sum2$ 时，不符合限制 2。需要在区间 $[1, a]$ 中选择一个位置进行修改。由于要字典序最小，所以很自然地想到去修改最后一个可修改的位置，并且刚好将其修改为 $sum2$。如果区间 $[1, a]$ 中没有可以修改的位置，则无解。

解决完限制 2 后，我们再令 $sum = \max \{c_1, c_2, \ldots, c_a\}$，当 $sum \geq c_b$ 时，显然只能通过修改 $c_b$ 的值来满足限制。要字典序最小，将其修改为 $sum + 1$ 显然为最优方案。但如果 $c_b$ 无法被修改，则无解。

至此，我们完成了大部分工作。回顾上面的过程，我们需要维护区间最大值，并且支持单点修改。笔者用的线段树。事实上，很多东西都可以轻易地解决这两件事，不细说了。

最后，输出答案时，如果：

1. 当前的 $c_i > C$。

2. 存在限制 $(a, b)$，但 $c_b ≠ \max \{c_1, c_2, \ldots, c_b\}$。

满足其一，则无解。

当然，如果到最后了都还有 $c_i$ 没有被填值的话，为了让字典序尽可能地小，填 $1$ 当然最优。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
int ans[100005], pre[100005];
bool flag[100005];
vector<int> a[100005];
int find(int l, int r) { // 找到 [l, r] 中最后一个可修改的位置。
	int Ri = r;
	while(l < r) {
		int mid = l + r >> 1;
		if(pre[mid] < pre[Ri]) l = mid + 1;
		else r = mid;
	}
	return l;
}
struct Tree {
	int l, r, sum;
}tree[100005 << 2];
void make_tree(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) {
		tree[i].sum = ans[l] + (ans[l] == 0);
		return;
	}
	int mid = l + r >> 1;
	make_tree(i << 1, l, mid), make_tree(i << 1 | 1, mid + 1, r);
	tree[i].sum = max(tree[i << 1].sum, tree[i << 1 | 1].sum);
}
void update(int i, int x, int k) {
	if(tree[i].l == tree[i].r) {
		tree[i].sum = k;
		return;
	}
	if(tree[i << 1].r >= x) update(i << 1, x, k);
	else update(i << 1 | 1, x, k);
	tree[i].sum = max(tree[i << 1].sum, tree[i << 1 | 1].sum);
}
int query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].sum;
	int ans = 0;
	if(tree[i << 1].r >= l) ans = max(ans, query(i << 1, l, r));
	if(tree[i << 1 | 1].l <= r) ans = max(ans, query(i << 1 | 1, l, r));
	return ans; 
}
int main() {
	int T;
	SF("%d", &T);
	while(T--) {
		memset(flag, 0, sizeof(flag));
		int n, q, c, len = 0;
		SF("%d%d%d", &n, &q, &c);
		for(int i = 1; i <= n; i++) {
			a[i].clear();
			SF("%d", &ans[i]);
			if(ans[i] == 0) flag[i] = 1;
			pre[i] = pre[i - 1] + flag[i];
		}
		make_tree(1, 1, n);
		for(int i = 1; i <= q; i++) {
			int index, now;
			SF("%d%d", &index, &now);
			a[now].push_back(index);
		}
		for(int i = 1; i <= n; i++) {
			if(a[i].size() == 0) continue;
			sort(a[i].begin(), a[i].end());
		}
		bool check = false;
		for(int i = 1; i <= n; i++) {
			if(a[i].size() == 0) continue;
			for(int j : a[i]) {
				int sum = query(1, 1, j);
				if(j != i - 1) {
					int pos = query(1, j + 1, i - 1);
					if(sum < pos) {
						int index = find(1, j); 
						if(pre[index] == 0) {
							check = true;
							break;
						}
						ans[index] = pos;
						update(1, index, pos);
					}
				}
				sum = query(1, 1, j);
				if(sum >= ans[i]) {
					if(flag[i]) ans[i] = sum + 1, update(1, i, sum + 1);
					else {
						check = true;
						break;
					}
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			if(ans[i] > c) {
				check = true;
				break;
			}
			if(a[i].size()) {
				if(query(1, 1, i - 1) >= ans[i]) {
					check = true;
					break;
				}
			}
		}
		if(check) {
			PF("-1\n");
			continue;
		}
		for(int i = 1; i < n; i++) PF("%d ", ans[i] + (ans[i] == 0));
		PF("%d\n", ans[n] + (ans[n] == 0));
	}
	return 0;
}
```

---

## 作者：lml0928 (赞：4)

### Part 0. 题目简述

[题目传送门](https://www.luogu.com.cn/problem/P10134)

给定一个数组 $c$，长度为 $n$，值域大小为 $v$。

$c$ 数组中有一些位置为 $0$，表示该位置的数未知。

对于 $c$ 数组有 $q$ 条限制 $(a_i, h_i)$ ，表示第 $h_i$ 头牛是第一头分数大于 $\max\limits_{1\le i\le a_i}{c_i}$ 的牛。

求出符合所有条件的 $c$ 中**字典序最小的**。

### Part 1. 题目做法

我们先判断约束之间是否冲突，把条件看做区间 $[a_i, h_i]$。

容易发现：如果两个区间相交，那么必有一个无法满足。

献上我~~丑陋~~的图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/bpzdz7l9.png) 

我们可以按照右端点为第一关键字，左端点为第二关键字来排序，如果发现前一个和自己的右端点不同，而且前面的右端点在我左端点后面，那就不能满足了。

右端点相同的线段，直接选择左端点最小的满足即可。这样就有：

> 对于所有的 $2 \le i \le n$，都有 $a_{i-1} < h_{i-1} \le a_i < h_i$。

这样，我们把输入自相矛盾的情况排除掉了。

接下来，按照刚才排好的顺序，逐步满足。

我们使用**贪心**的做法，将所有输入为 $0$ 的 $c_i$  设为 $1$。

设当前条件为 $(l,r)$。

如果 $\max\limits_{1\le i\le l }{c_i} <\max\limits_{1\le i\le r-1 }{c_i}$，我们必须在 $1\le i \le l$ 的范围中选择一个 $i$，使得 $i$ 最靠后且 $i$ 可修改，并将 $c_i$ 改为 $\max\limits_{1\le i\le r-1 }{c_i}$。不存在这样的 $i$ 则无解。选最靠后的，是因为要求字典序最小的答案。

如果 $c_r$ 可以修改，根据题意，改为 $\max\limits_{1\le i\le r-1 }{c_i} +1$ 为最优解。

如果 $c_r$ 不可修改，并且 $c_r \le \max\limits_{1\le i\le r-1 }{c_i}$，那么此题无解。

但是这里还有一个问题：如果后面的要求改动了和当前要求有关的数，那么当前要求会被破坏。所以我们定义一个变量 $leftmodi$，表示当前最靠左的可修改的位置。

判断可修改的时候，加上这个细节即可。
每次满足完当前条件后，让 $leftmodi \gets r$，因为 $r$ 左边的数都会影响到这个条件。

最后，判断整个序列的最大值是否 $> c$ 即可。

不难发现，这需要一种支持单点修改，前缀查询的数据结构，树状数组很适合用在这里。

终于，我们把这道~~费脑的~~题做出来了！

### Part 2. 代码

~~附上代码供众人批判~~

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = (int)3e5 + 10;
int v[N];
int tr[N];
int lst[N];
int n, q, c;
struct node
{
	int l, r;
	bool operator < (const node& cmp) const
	{
		if(r != cmp.r) return r < cmp.r;
		return l < cmp.l;
	}
};
int Lowbit(int x)
{
	return x & (-x);
}
void Modi(int p)
{
	int t = v[p];
	for(int i = p; i <= n; i += Lowbit(i)) tr[i] = max(tr[i], t);
}
int Query(int p)
{
	int res = 0;
	for(int i = p; i; i -= Lowbit(i)) res = max(res, tr[i]);
	return res;
}
node a[N];
vector<node> ve;
void Solve()
{
	memset(tr, 0, sizeof tr);
	cin >> n >> q >> c;
	for(int i = 1; i <= n; i++)
	{
		cin >> v[i];
		if(v[i] == 0)
		{
			lst[i] = i;
			v[i] = 1;
		}
		else lst[i] = lst[i - 1];
		Modi(i);
	}
	for(int i = 1; i <= q; i++) cin >> a[i].l >> a[i].r;
	sort(a + 1, a + q + 1);
	ve.clear();
	for(int i = 1; i <= q; i++)
	{
		if(a[i].r != a[i - 1].r && a[i - 1].r > a[i].l)
		{
			cout << "-1\n";
			return;
		}
	}
	for(int i = 1; i <= q; i++)
	{
		if(a[i].r != a[i - 1].r) ve.push_back(a[i]);
	}
	int leftmodi = 1;
	for(auto now : ve)
	{
		int x = now.l, y = now.r;
		if(Query(x) < Query(y - 1))
		{
			if(leftmodi <= lst[x])
			{
				v[lst[x]] = Query(y - 1);
				Modi(lst[x]);
			}
			else
			{
				cout << "-1\n";
				return;
			}
		}
		if(lst[y] == y)
		{
			v[y] = Query(y - 1) + 1;
			Modi(y);
		}
		else if(v[y] <= Query(y - 1))
		{
			cout << "-1\n";
			return;
		}
		leftmodi = y;
	}
	if(Query(n) > c) cout << "-1\n";
	else
	{
		for(int i = 1; i <= n; i++) cout << v[i] << ' ';
		cout << '\n';
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) Solve();
	return 0;
}
```

### Part 3. 后记
~~多测不清空，亲人两行泪~~

---

## 作者：anjack_511 (赞：3)

质量好高的思维题！但是赛时网络波动，~~体验不好~~。

其实这题并不需要线段树。

不难想到，我们先将所有的要求按照 **左端点排序**。我们首先发现：

- 对于一个要求 $(a_i, h_i)$，所有 $[a_i, h_i)$ 之间的牛的领导力都低于 $h_i$。
  
从而，对于一个要求 $(a_i, h_i)$，所有 $[a_i, h_i)$ 之间的牛 $a_j$，其之后第一头比 $a_j$ 有严格更高领导力的牛都为 $h_i$。

根据上面的性质。假如有两个要求 $(a_i, h_i)$ 和 $(a_j, h_j)$ 两个要求，排序后 $i < j$，如果后面的询问中 $a_j$ 小于前一个询问的 $h_i$，那么有解当且仅当 $h_j = h_i$。否则无解。

这个性质告诉我们，当左端点有序的时候，右端点也就有序了。

我们考虑画图来理解这个问题，之后每条线段代表一个要求，左边的圆点代表 $a_i$，右边的三角代表 $h_i$

![pF1CMFS.png](https://s11.ax1x.com/2024/02/05/pF1CMFS.png)
-----
![pF1CQJg.png](https://s11.ax1x.com/2024/02/05/pF1CQJg.png)

根据上面的性质，第一张图是一个合格的情况，而第二张图不是一个合格的情况。

-----

我们更进一步思考，考虑两个 $h_i$ 不同的要求之间的关系。

我们发现，对于所有 $h$ 相同的询问，实际上只用保留一个最左端的 $a$。这是因为最左端的条件最强，即所有 $[a, h)$ 的牛的领导力都要比 $h$ 和 $a$ 弱，我们再来画个图，**上个要求的 $h$ 和下个要求 $a$ 之间连一条实黑线**：

![pF19e5F.png](https://s11.ax1x.com/2024/02/05/pF19e5F.png)

$max_1$ 是 $[h_{i - 1}, a_i]$ 中领导力最大的值，$max_2$ 是 $(a_i, h_i)$ 中领导力最大的值。

对于 $[1, a_i]$，在 $a_i$ 之后的第一个比 $[1, a_i]$ 大的牛是 $h_i$，所以在 $(a_i, h_i)$ 之间的牛的领导力不能大于 $[1, a_i]$ 的，进而不能大于 $max_1$，故 $max_2$ 不能大于 $max_1$。

- 如果现有的 $max_2 > max_2$，那么找 $[h_{i-1}, a_i]$ 中 **最后一个** 可以改的牛的领导力，将其改为 $max_2$ （保证字典序最小）。如果找不到，那么无解。
- 如果 $h_i$ 比前面的小，那么把 $h_i$ 改为 $\max(max_1, max_2) + 1$。如果不可修改，那么无解。

现在我们也能更严谨的解释为什么只需要保证左端点最小的要求就可以了。如果已满足了它自己，那么对于比它左端点大的要求的 $max_1$ 不变，$max_2$ 只会变小。

-----

在实现的时候，首先给所有为零的 $c$ 填上 $1$，这是保证不劣的。并标记这些可以修改的 $c$，方便后面修改。

注意在改完所有的之后判断每只牛的领导力是否小于 $C$。

由于每头牛只会被枚举一次，所以时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int t, n, m, c, ci[MAXN], tag[MAXN];
struct qr{
    int a, h;
    bool operator < (const qr &x) const {
        return a < x.a;
    }
} q[MAXN];
void work()
{
    scanf("%d%d%d", &n, &m, &c);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &ci[i]);
        tag[i] = ci[i];
        if(!ci[i]) ci[i] = 1;
    }
    for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].a, &q[i].h);
    sort(q + 1, q + 1 + m);
    q[0].h = 1;
    for(int i = 1; i <= m; i++){
        if(q[i].h == q[i - 1].h) continue;
        if(q[i].h != q[i - 1].h && q[i].a < q[i - 1].h){
            printf("-1\n");
            return; // 判断是否无解
        }
        int mx1 = -1, mx2 = -1, cc = 0;
        for(int j = q[i - 1].h; j <= q[i].a; j++){
            mx1 = max(mx1, ci[j]);
            if(tag[j] == 0) cc = j; // 找 max1
        }
        for(int j = q[i].a + 1; j < q[i].h; j++)
            mx2 = max(mx2, ci[j]); // 找 max2
        if(mx1 < mx2){
            if(!cc) { printf("-1\n"); return;}
            ci[cc] = mx2;
        }
        if(tag[q[i].h] && ci[q[i].h] <= max(mx1, mx2)){
            printf("-1\n");
            return; // 如果 h_i 不能被更改且不满足条件，那么无解
        } 
        else if(tag[q[i].h] == 0)
            ci[q[i].h] = max(mx1, mx2) + 1;
    }
    for(int i = 1; i <= n; i++)
        if(ci[i] > c) {
            printf("-1\n"); 
            return;
        }
    printf("%d", ci[1]);
    for(int i = 2; i <= n; i++){
        printf(" %d", ci[i]);
    }
    printf("\n"); // 好坑，赛时竟然要判行末空格
    return;
}
int main()
{
    scanf("%d", &t);
    while(t--) work();
    return 0;
}
```


---

## 作者：cff_0102 (赞：3)

注：下面所说的“前缀最大值”均为严格最大值。

对于每一对 $(a_i,h_i)$，我们有：

- 对于 $1\sim a_i$ 的数，（如果只考虑这个条件的话）它们可以是前缀最大值，也可以不是；
- 对于 $a_i+1\sim h_i-1$ 的数，它们不可能是前缀最大值；
- 对于 $h_i$，它必须是前缀最大值。

注意到如果有一个 $h_i$ 在其它的 $a_j+1\sim h_j-1$ 中，那么是无解的。如果有一对 $(a_i,h_i),(a_j,h_j)$ 满足 $h_i=h_j$，$a_i<a_j$，那么 $(a_i,h_i)$ 的要求更严格，后者就可以直接忽略。

把无解情况排除并忽略掉上面所说的情况后，剩下的区间必然互不相交，这样就可以从左到右对每个区间分别考虑了。

设 $mx1_i$ 为 $h_{i-1}\sim a_i$ 的最大值，$mx2_i$ 为 $a_i+1\sim h_i-1$ 的最大值，$lst$ 为在 $h_{i-1}\sim a_i$ 的最后一个可填的数的位置，如果不存在即为 $0$。因为 $h_{i-1}$ 是前缀最大值，所以 $mx1_i$ 即为目前 $1\sim a_i$ 的最大值。因此可以对以下情况进行判断：

如果此时 $mx1_i<mx2_i$，那么因为 $a_i+1\sim h_i-1$ 的数不能是前缀最大值，所以要在 $1\sim a_i$ 找到一个数并将它改成 $mx2_i$。显然如果 $lst\ne0$ 则填在 $lst$ 是字典序最小的选择。而如果 $lst=0$，也就是 $h_{i-1}\sim a_i$ 都不可修改，那就绝对无解了，因为即使在 $h_{i-1}$ 前有可以修改的点，也必须把它改成比 $h_{i-1}$ 大的数，这又违反了 $h_i$ 必须是前缀最大值的规则。如果可以修改，在把 $lst$ 修改成 $mx2_i$ 后，记得将 $mx1_i$ 更新为 $mx2_i$。

现在 $a_i+1\sim h_i-1$ 的数不能是前缀最大值的要求已经满足了，接着就要满足 $h_i$ 必须是前缀最大值的要求了。如果这个数可以修改，直接将其修改为 $mx1_i+1$ 即可；如果这个数不能修改，且这个数小于等于 $mx1_i$，那么就无解。

把所有数填好后，记得判断是否有数字大于 $C$，如果有，依题意，也是无解的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int c[N];
pair<int,int>p[N];
bool f[N];
int mian(){
    int n,q,C;cin>>n>>q>>C;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        if(!c[i])f[i]=c[i]=1;
        else f[i]=0;
    }
    for(int i=1;i<=q;i++)cin>>p[i].first>>p[i].second;
    sort(p+1,p+1+q);
    p[0].second=1;
    for(int i=1;i<=q;i++){
        if(p[i].second==p[i-1].second)continue;
        if(p[i].first<p[i-1].second)return cout<<-1<<endl,0;
        int mx1=0,mx2=0,lst=0;
        for(int j=p[i-1].second;j<=p[i].first;j++){
            mx1=max(mx1,c[j]);
            if(f[j])lst=j;
        }
        for(int j=p[i].first+1;j<p[i].second;j++){
            mx2=max(mx2,c[j]);
        }
        if(mx1<mx2){
            if(lst){
                c[lst]=mx2;
                mx1=mx2;
            }else return cout<<-1<<endl,0;
        }
        if(f[p[i].second]){
            c[p[i].second]=mx1+1;
        }else{
            if(c[p[i].second]<=mx1)return cout<<-1<<endl,0;
        }
    }
    for(int i=1;i<=n;i++)if(c[i]>C)return cout<<-1<<endl,0;
    for(int i=1;i<=n;i++)cout<<c[i]<<" ";cout<<endl;
    return 0;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;while(t--)mian();
    return 0;
}
```

---

## 作者：fire_and_sweets (赞：2)

#### 题意

我们可以先简化一下题目，即：给出一个序列 $c_1,c_2,\cdots,c_n(1\le n\le 10^5,1\le c_i\le C)$，其中有一些元素不知道。给定 $1\le Q\le N$ 个约束条件，第 $i$ 个约束条件为：要求第 $h_i$ 个元素是第一个严格大于前 $a_i$ 个元素的后续元素，要求确定不知道的元素，求出所有可能的序列中字典序最小的序列即可。如果这样的序列不存在，输出 $-1$。

#### 思路

我们先考虑一下无解的情况。如果要求第 $h_i$ 个元素是第一个严格大于前 $a_i$ 个元素的后续元素，那么显然，$c_{a_{i+1}}\cdots c_{h_{i-1}}$ 都需要小于等于 $c_1\cdots c_{a_i}$ 中的最大值，否则第一个满足要求的后继不可能是第 $h_i$ 个元素。这说明了以下几点：

1. 若 $a<b<c$，且前 $a$ 个元素的第一个满足要求的后续元素是第 $c$ 个元素，则前 $b$ 个元素的第一个满足要求的后续元素也是第 $c$ 个元素。换而言之，对于若干个 $h$ 相同的约束，只需要关注 $a$ 最小的那个即可，其他约束自然就满足了。

2. 不存在 $a_i<a_j<h_i<h_j$ 的情况，即约束的区间 $[a,h]$。

3. 除了端点以外不相交。为了方便讨论每个序列影响范围不知道元素的取值，我们将区间从小到大排序，将每一个序列影响的范围分成这几段：$h_{i-1}+1\sim a_i,a_i+1\sim h_i-1,h_i$。

这样，我们就有了思路。如果 $c_{h_i}$ 的值已经知道:

1. 检查第一段和第二段的最大值与 $c_{h_i}$ 比较，如果出现大于 $c_{h_i}$ 的情况那么  肯定没有这样的序列，直接输出 $-1$。

2. 如果第一段的最大值小于第二段的最大值，那么需要将第一段的最大值增大至和第二段一样，如果其中有不知道的元素，就把最后一个不知道的元素赋值为第二段的最大值，其余元素填 $1$ 满足字典序最小；如果没有不知道的元素，就需要检查前一个区间的h是否不知道，如果是不知道的那么就将其赋值为第二段的最大值，否则无论如何也无法满足这个约束，直接输出 $-1$。

3. 将第二段中所有不知道的元素都赋值为 $1$ 满足字典序最小。

如果 $c_{h_i}$ 的值不知道，则不需要上述第一步，并将 $c_{h_i}$ 赋值为前缀最大值 $+~1$ 即可。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int N = 100010;
int dat[N]; // 用来存储题目中给定的 c 数组
struct Node // 使用结构体存储所有限制 
{
	int a, h;	
	bool operator < (const Node& _) const // 重载比较函数：把所有限制排序 
	{
		if (h != _.h) return h < _.h; // 第一关键字：h
		return a < _.a; // 第二关键字：a 
	}
} res[N];

PII getinfo(int start, int end) // getinfo 函数返回了一个 pair<int, int> 
{ // 其中 first 表示当前区间最后一个 0 的位置，second 表示区间中所有元素的最大值 
	int pos = -1, maxn = 0;
	for (int i = start; i <= end; i ++ )
	{
		if (dat[i] == 0) pos = i; // 记录区间 0 的位置
		maxn = max(maxn, dat[i]); // 打擂法求出区间最大值 
	}
	return {pos, maxn};
}

void fillzero(int start, int end, int pos, int tar) // 把区间 [start, end] 中的 0 赋值 
{ // 这样赋值：pos 位置的 c 数组赋值成 tar，其他元素赋值成 1
	for (int i = start; i <= end; i ++ )
		if (dat[i] == 0)
		{
			if (i != pos) dat[i] = 1; // 如果位置不是 pos，赋值成 1 
			else dat[i] = tar; // 如果位置是 pos，赋值成 tar 
		}
}

void solve()
{
	int n, c, q;
	cin >> n >> q >> c;
	for (int i = 1; i <= n; i ++ ) cin >> dat[i];
	for (int i = 1; i <= q; i ++ ) cin >> res[i].a >> res[i].h; // 读入 
	sort(res + 1, res + 1 + q); // 把所有约束条件排序 
	int premax = 0, lst = 0;
	bool lstv = 0;
	for (int i = 1; i <= q; i ++ )
	{
		if (lst == res[i].h) continue;
		if (res[i].a < lst) // 包含的区间只考虑 a 最靠左的（条件最强），如果两个区间交叉肯定不合法
		{
			cout << -1 << endl;
			return;
		}
		PII seg1, seg2; // 计算两段的信息 
		seg1 = getinfo(lst + 1, res[i].a), seg2 = getinfo(res[i].a + 1, res[i].h - 1); // 题解中提到，我们可以把一个区间分成两段。
		seg1.second = max(premax, seg1.second); // 和前缀最大值取 max
		if (dat[res[i].h])
		{
			if (seg1.second >= dat[res[i].h] || seg2.second >= dat[res[i].h])
			{ // 前面铁定比 h 大了，无解 
				cout << -1 << endl;
				return;
			} 
			if (seg2.second > seg1.second) // 第二节比第一节目前看着大
			{
				if (seg1.first == -1) // 如果第一节没有 0 
				{
					if (lstv) // 把前面可变的 h 改掉 
					{
						dat[lst] = seg2.second; // 改到第二节的最大值即可 
						fillzero(lst + 1, res[i].h - 1, -1, -1);
					}
					else // 否则一定无解 
					{
						cout << -1 << endl;
						return;
					}
				}
				else fillzero(lst + 1, res[i].h - 1, seg1.first, seg2.second); // 第一节有 0，就把第一节最后一个 0 改成后面的最大值，其他地方填 1
			}
			else fillzero(lst + 1, res[i].h - 1, -1, -1);
			lstv = false;
			premax = dat[res[i].h];
			lst = res[i].h;
		}
		else // 这个 h 可以改正 
		{
			if (seg2.second > seg1.second) // 第二节比第一节目前看着大
			{
				if (seg1.first == -1) // 如果第一节没有 0 
				{
					if (lstv) // 把前面可变的 h 改掉 
					{
						dat[lst] = seg2.second; // 改到第二节的最大值即可 
						fillzero(lst + 1, res[i].h - 1, -1, -1); // 全部填 1 
					}
					else // 否则一定无解 
					{
						cout << -1 << endl;
						return;
					}
				}
				else fillzero(lst + 1, res[i].h - 1, seg1.first, seg2.second); // 第一节有 0，就把第一节最后一个 0 改成后面的最大值，其他地方填 1
			}
			else fillzero(lst + 1, res[i].h - 1, -1, -1);
			dat[res[i].h] = max(max(seg1.second, seg2.second), 1) + 1;
			if (dat[res[i].h] > c) // 超出范围了 
			{
				cout << -1 << endl;
				return;
			}
			lstv = true, premax = dat[res[i].h], lst = res[i].h;
		}
	}
	fillzero(lst + 1, n, -1, -1);
	for (int i = 1; i <= n; i ++ ) cout << dat[i] << " ";
	cout << endl;
}

int main()
{
	int T;
	cin >> T;
	while (T -- ) solve(); // 多组测试数据 
	return 0;
}
```

---

## 作者：_qhbd_ (赞：1)

# 题意
共 $T$ 组数据。

每组数据给定 $N,Q,C$ 和一个原值域为 $[1,C]$ 但实际值域为 $[0,C]$ 且有 $N$ 个元素的序列 $c$ 以及 $Q$ 对数对 $(a_i,h_i)(1\le i\le Q)$。

对于 $c_i=0(1\le i\le N)$，即不确定其值，否则确定。

对于数对 $(a_i,h_i)(1\le i\le Q)$，即 $c_{h_i}$ 为序号最小的严格大于 $\max_{j=1}^{a_i}c_j$ 的元素。

对于每组数据输出可能的最小字典序的原序列，若不可能存在符合条件的序列则输出 `-1`。
# 思路
首先先将 $Q$ 组数对按 $a_i$ 从小到大的顺序排序，至于为什么稍后讲解。

然后对于排序后每组数对 $(a_i,h_i)$ 取 $Maxa=\max_{j=1}^{a_i}c_j$ 和 $Maxb=\max_{j=1}^{h_i-1}c_j$，若 $Maxb>Maxa$ 则意味着 $c_{h_i}$ 不为序号最小的严格大于 $\max_{j=1}^{a_i}c_j$ 的元素。

此时判断在 $c_j(1\le j\le a_i)$ 中是否有待定值的元素：若有则将其序号最大的值待定元素修改为 $Maxb$，然后 $Maxa==Maxb$，符合条件；若没有，则不可能存在符合条件的序列，直接输出 `-1`。

因为这里有修改 $c_j(1\le j\le a_i)$ 的情况，所以将 $Q$ 组数对按 $a_i$ 从小到大的顺序排序，这样保证每次的修改能够影响到后续的判断，不会有多余修改。


其次，分类讨论：

- 若 $c_{h_i}$ 的值待定，则为其赋值为 $Maxa+1$。
- 若 $c_{h_i}$ 的值确定，则判断 $c_{h_i}$ 是否严格大于 $Maxa$，也就是是否存在符合条件的序列。

因为需要动态地维护区间最大值，所以这里用了线段树，在初始化时，可以把为 $0$ 的值在线段数内修改为 $1$，这样在类上文赋值 $Maxa+1$ 时需要的特判可以省略。

然后记得在赋值过程中判断赋的值是否大于 $C$，以及最后得到的序列是否合法即可。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=1e5+5;
int t,N,Q,C,c[n],mx;
struct imf{int a,h;}d[n];
inline bool cmp(imf a,imf b){return a.a<b.a;}
int tr[n<<2],zero[n<<2];
inline void build(int p,int l,int r){
    if(l==r){
        tr[p]=(c[l]==0?1:c[l]);
        if(c[l]==0)
            zero[p]=l;
        else 
            zero[p]=0;
        return;
    }
    build(p<<1,l,l+r>>1);
    build(p<<1|1,(l+r>>1)+1,r);
    tr[p]=max(tr[p<<1],tr[p<<1|1]);
    zero[p]=max(zero[p<<1],zero[p<<1|1]);
}
inline void modify(int p,int l,int r,int x,int w){
    if(l>x||r<x)
        return;
    if(l==r){ 
        tr[p]=w;
        return;
    }
    modify(p<<1,l,l+r>>1,x,w);
    modify(p<<1|1,(l+r>>1)+1,r,x,w);
    tr[p]=max(tr[p<<1],tr[p<<1|1]);
    zero[p]=max(zero[p<<1],zero[p<<1|1]);
}
inline int query(int p,int l,int r,int R){
    if(l>R)
        return 0;
    if(r<=R)
        return tr[p];
    return max(query(p<<1,l,l+r>>1,R),query(p<<1|1,(l+r>>1)+1,r,R));
}
inline int queryzero(int p,int l,int r,int R){  
    if(l>R)
        return 0;
    if(r<=R)
        return zero[p];
    return max(queryzero(p<<1,l,l+r>>1,R),queryzero(p<<1|1,(l+r>>1)+1,r,R));
}
int main(){
    // freopen("b.in","r",stdin);
    // freopen("b.out","w",stdout);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&N,&Q,&C);
        for(int i=1;i<=N;i++)
            scanf("%d",&c[i]);
        build(1,1,N);
        for(int i=1;i<=Q;i++)
            scanf("%d%d",&d[i].a,&d[i].h);
        stable_sort(d+1,d+Q+1,cmp);
        bool k=false;
        for(int i=1;i<=Q;i++){
            if(d[i].h==d[i-1].h)continue;
            if(query(1,1,N,d[i].h-1)>query(1,1,N,d[i].a)){
                int id=queryzero(1,1,N,d[i].a);
                if(id==0){
                    printf("-1\n");
                    k=true;
                    break;
                }
                else{
                    c[id]=query(1,1,N,d[i].h-1);
                    modify(1,1,N,id,c[id]);
                }
            }
            if(c[d[i].h]!=0){
                if(query(1,1,N,d[i].a)>=c[d[i].h]){
                printf("-1\n");
                    k=true;
                    break;
                }
            }
            else{
                c[d[i].h]=query(1,1,N,d[i].a)+1;
                if(c[d[i].h]>C){
                    printf("-1\n");
                    k=true;
                    break;
                }
                modify(1,1,N,d[i].h,c[d[i].h]);
            }
        }
        if(k)
            continue;
        for(int i=1;i<=Q;i++)
            if(query(1,1,N,d[i].a)>=c[d[i].h]||query(1,1,N,d[i].h-1)>query(1,1,N,d[i].a)){
                printf("-1\n");
                k=true;
                break;
            }
        if(k)
            continue;
        for(int i=1;i<=N;i++)
            printf("%d ",c[i]==0?1:c[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Cuiyi_SAI (赞：1)

update at 2024-2-16:  
感谢 Arctic_Spider 提供的 Hack 数据，解决了源代码的思路无法通过 #3 的问题（赛时直接用暴力跑过去的）。主要问题出在满足了后面限制可能会导致前面的限制被破坏了，因此最后要再扫一边 $c$ 数组判断是否真的满足所有限制，否则输出 $-1$。

## $\text{Question}$

给你长度为 $n$ 的序列 $c$，$0\le c_i\le C$。若当前位置为 $0$ 则表示这个数未知,需要你填。要求你填数使得序列字典序最小，并满足给出的 $q$ 条限制 $(a_j,h_j)$，使得 $C_{h_j}$ 是第一个**严格大于** $C_1\cdots C_{a_j}$ 的数。

## $\text{Solution}$

首先考虑将给定的限制形式化，然后找性质。
若用 $maxc_i$ 表示 $c_i$ 的**前缀最大值**，对于限制 $(a,h)$ 则可以表示为
$$
maxc_{h-1}<maxc_h
$$
$$
maxc_a=maxc_{h-1}
$$
可以发现上述条件就是限制的充要条件。

由上述分析可以发现限制其实跟 $maxc$ 紧密相关。因此得到启发，我们需要维护前缀最大值数组 $maxc_i$。但是我并没有用什么数据结构，而是直接根据每个限制来逐个调整。

具体的，为了不使得后面的操作影响前面，先将性质按照 $a_i$ 递增排序，然后对于限制分讨调整 $maxc$ 使得其满足要求（注意，以下操作都是在 $maxc$ 数组上进行的，而非原数组）：
1. 首先我们要维护我们可以填数（即 $0$）的位置，因为后续的调整都只能在这些位置上进行，而且用一个少一个。

2. 我们还要维护可以填数的位置最大能填多少，这是为了避免因调整后面限制而导致的对前面性质的破坏。

3. 如果已经确定的数就已经违反了限制，显然这种情况我们无法改变，或者说能填的位置由于大小限制无法逆转局势，那么无解。

4. 然后就是从后往前找到第一个能填的位置，填上恰好满足限制而最小的数，并更新后面的 $maxc$。

得到了满足所有限制的 $maxc$ 以后，由于其其实是个 $c$ 的前缀最大值数组，我们可以用字典序最小的要求还原出 $c$ 数组。


## $\text{Code}$
具体实现可以看看代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,C,c[100010],maxc[100010],lst[100010],maxn[100010];
struct node{
    int a,h;
} s[100010];
bool cmp(node aa,node bb){
    if(aa.a==bb.a) return aa.h<bb.h;
    return aa.a<bb.a;
}
long long baoli=1e15;
int b[15];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q>>C;
        memset(lst,0,sizeof(lst));
        for(int i=1;i<=n;i++) cin>>c[i],maxc[i]=max(maxc[i-1],c[i]);
        for(int i=1;i<=q;i++) cin>>s[i].a>>s[i].h;
        sort(s+1,s+1+q,cmp);
        //lst_i 表示上一个不确定的位置，特别的c_i=0则 lst_i=i 
        for(int i=1;i<=n;i++){
            if(c[i]==0) lst[i]=i; 
            else lst[i]=lst[i-1];
            maxn[i]=C; //maxn_i 记录的是若当前位不确定，那么能填的最大数是多少 
        }
        bool flag=true;
        for(int i=1;i<=q;i++){
            int a=s[i].a,h=s[i].h;
            if(maxc[h-1]==0) maxc[h-1]=1;  //若前面所有的数都不确定，那么贪心的令其为最小 
            if((c[h]!=0&&c[h]<=maxc[h-1])||maxc[h-1]+1>C){ 
			//如果这些位置都确定并且违背了限制，或者为了满足限制就要填大于C的数，那么都无解 
                flag=false;
                break;
            }
             //因为调整的过程中会将一些不确定的位置确定下来，所以要随时更新lst数组 
            while(lst[lst[h-1]]!=lst[h-1]) lst[h-1]=lst[lst[h-1]]; 
            maxn[lst[h-1]]=min(maxn[lst[h-1]],maxc[h-1]);  //为了满足限制，我们调整maxc，将一个不确定的位置填上我们需要的数字 
            for(int j=h;j<=n;j++){  //更新 maxc 
                if(maxc[j]>maxc[h-1]) break;
                maxc[j]=maxc[h-1]+1;
            }
            if(maxc[a]>maxc[h-1]){  //如果已确定的数已经违反了限制，那么我们无法改变，无解 
                flag=false;
                break;
            }
            if(maxc[a]<maxc[h-1]){
                while(lst[lst[a]]!=lst[a]) lst[a]=lst[lst[a]]; //更新不确定的位置 
                if(!lst[a]||maxc[h-1]>(maxn[lst[a]]/*表示这个位置能填的最大值*/)){
                	//如果没有不确定的位置给我们填，或者我们需要填的数大于这个位置能填的最大值，就无解 
                    flag=false;
                    break;
                }
                for(int j=lst[a];j<h;j++){
                	//根据限制填数，同时更新后面的 maxc 
                    maxc[j]=max(maxc[h-1],maxc[j]);
                    if(maxn[j]<maxc[h-1]){ //同样的，如果能填的数的范围小于需要填的数，那么无解 
                        flag=false;
                        break;
                    }
                }
                if(!flag) break;
                //填了一个数，不确定的位置少一个，更新lst 
                lst[a]=lst[lst[a]-1];
            }
        }
        // 根据 maxc 倒推出字典序最小的 c 并输出
        for(int i=1;i<=n;i++){
            if(c[i]) continue;
            if(maxc[i]>maxc[i-1]) c[i]=maxc[i];
            else c[i]=1;
        }
        for(int i=1;i<=n;i++) maxc[i]=max(maxc[i-1],c[i]);
        for(int i=1;i<=q;i++){
            if(maxc[s[i].h-1]!=maxc[s[i].a]||maxc[s[i].a]>c[s[i].h]){
                flag=false;
                break;
            }
        }
        if(!flag) cout<<"-1";
        else{
            cout<<c[1];
            for(int i=2;i<=n;i++) cout<<' '<<c[i];
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：MhxMa (赞：1)

### 分析

在更新奶牛的牲任力分数序列中：  
- 如果某个奶牛的牲任力分数已知，则将其标记为已访问；  
- 如果某个奶牛的分数未知，记录其下标，并将其添加到一个集合中。

然后可以根据记忆信息更新分数：  
对于每个数对 $(a_j,h_j)$，找到区间内未知分数的奶牛，根据规则更新其分数,同时判断，确保序列满足条件。

书写代码时，需要注意处理边界情况和各种可能的情况，在 USACO 比赛中，千万不要像我一样多输出换行，否则答案会错误。

### 赛时 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, q, c, tp;
long long mp[1000001], mp2[1000001], mp3[1000001], isv[1000001];
pair<long long, long long> pairl[1000001];
set<long long> setl;

bool cmp(pair<long long, long long> a, pair<long long, long long> b) {
	return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second);
}

void solve() {
	setl.clear();
	cin >> n >> q >> c;
	for (long long i = 1; i <= n; i++) {
		cin >> mp[i];
		if (!mp[i]) {
			setl.insert(i);
			isv[i] = 1;
		} else {
			isv[i] = 0;
		}
		mp3[i] = max(mp3[i - 1], mp[i]);
	}
	for (long long i = 1; i <= q; i++) {
		cin >> pairl[i].first >> pairl[i].second;
	}

	sort(pairl + 1, pairl + q + 1, cmp);
	tp = 0;

	for (long long i = 1; i <= q; i++) {
		if (pairl[i].first < tp && pairl[i].second != tp) {
			cout << "-1";
			return;
		}
		tp = pairl[i].second;
	}

	tp = n + 1;
	for (long long i = q; i >= 1; i--) {
		long long a = min(pairl[i].second - 1, tp), b = pairl[i].first + 1;

		for (long long j = a; j >= b; j--) {
			if (!isv[j] && mp[j] > mp3[pairl[i].first]) {
				set<long long>::iterator tp2 = setl.upper_bound(pairl[i].first);
				if (tp2 == setl.begin()) {
					cout << "-1";
					return;
				}
				--tp2;
				long long tp3 = *tp2;
				mp[tp3] = max(mp[tp3], mp[j]);
			} else if (isv[j] && mp[j] > mp3[pairl[i].first]) {
				set<long long>::iterator tp2 = setl.upper_bound(pairl[i].first);
				if (tp2 == setl.begin()) {
					cout << "-1";
					return;
				}
				--tp2;
				long long tp3 = *tp2;
				mp[tp3] = max(mp[tp3], mp[j]);
				mp[j] = 0;
			}
		}
		tp = pairl[i].first;
	}
	tp = 0;
	for (long long i = 1; i <= q; i++) {
		long long x = pairl[i].second, j;
		stack<long long> r;
		for (j = i; j <= q && pairl[j].second == x; j++) {
			r.push(pairl[j].first);
		}
		long long maxn = 0;
		if (r.size() && tp == r.top()) {
			maxn = max(maxn, mp2[tp]);
			r.pop();
		}
		for (long long k = tp + 1; k <= x - 1; k++) {
			if (!mp[k])
				mp[k] = 1;
			if (maxn && mp[k] > maxn) {
				cout << "-1";
				return;
			}
			mp2[k] = max(mp2[k - 1], mp[k]);
			if (r.size() && k == r.top()) {
				maxn = max(maxn, mp2[k]);
				r.pop();
			}
		}
		if (isv[x])
			mp[x] = max(mp[x], maxn + 1);
		else if (maxn >= mp[x]) {
			cout << "-1";
			return;
		}
		mp2[x] = max(mp2[x - 1], mp[x]);
		tp = x;
		i = j - 1;
	}
	for (long long i = tp + 1; i <= n; i++) {
		if (!mp[i])
			mp[i] = 1;
		mp2[i] = max(mp2[i - 1], mp[i]);
	}
	if (mp2[n] > c) {
		cout << "-1";
		return;
	}
	for (long long i = 1; i <= n; i++) {
		cout << mp[i];
		if (i != n) {
			cout << " ";
		}
	}
	return;
}

int main() {
	long long T;
	cin >> T;

	while (T--) {
		solve();
		cout<<endl;
	}

	return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

一道好题，让我加强了对拍与细节的意识。

## 思路

对于 $Q$ 对数 $(x,y)$，可以看作有两个限制：

+ $\max\{c_{1} \dots c_{x}\}=\max\{c_{1} \dots c_{y-1}\}$

+ $\max\{c_{1} \dots c_{x}\} < c_{y}$

也就是说要构造一个字典序最小的序列，使得给定的这些条件全部满足。

首先对于第一个条件，如果不满足，因为我们想到得到的是字典序最小的序列，所以就考虑将 $c_{i} \dots c_{x}$ 中下标最大的待定值改为 $\max\{c_{1} \dots c_{y-1}\}$，如果没有就无解。

对于第二个条件，如果不满足，那么如果 $c_{y}$ 待定，就修改即可，否则无解。

我们需要先考虑第一个条件，因为第一个条件会改变第二个条件需要用到的 $\max\{c_{1} \dots c_{x}\}$。

然后由于我们需要字典序最小，所以我们将数对按照 $x$ 排序，这样我们对于 $c_{i}(i\le x)$ 的修改可以被后面的数对使用，到后面可以避免一定的修改。这是这样做的意义，略过正确性证明，读者可以自己思考这样做的正确性。

最后判断再一遍所有的条件是否符合，以及是否所有 $c$ 中的元素都小于 $C$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=1e5+5;
struct node {
	int l,r,maxn,lz;
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define maxn(x) tr[x].maxn
	#define lz(x) tr[x].lz
};
int c[N],go[N];
pair<int,int> l[N];
bool st[N];
int tt;
int n,q,C;
struct segment_tree {
	node tr[N*4];
	void pu(int x) {maxn(x)=max(maxn(x*2),maxn(x*2+1));}
	void build(int x,int l,int r) {
		l(x)=l,r(x)=r;
		if(l==r) {
			maxn(x)=c[l];
			return;
		}
		int mid=l+r>>1;
		build(x*2,l,mid),build(x*2+1,mid+1,r);
		pu(x);
	}
	void change(int x,int pl,int k) {
		int l=l(x),r=r(x);
		if(l==r&&l==pl) {
			maxn(x)=k;
			return;
		}
		int mid=l+r>>1;
		if(pl<=mid) change(x*2,pl,k);
		else change(x*2+1,pl,k);
		pu(x);
	}
	int qry(int x,int ll,int rr) {
		if(ll>rr) return -1;
		int l=l(x),r=r(x);
		if(l>=ll&&r<=rr) return maxn(x);
		int mid=l+r>>1,maxn=-1;
		if(mid>=ll) maxn=max(maxn,qry(x*2,ll,rr));
		if(mid<rr) maxn=max(maxn,qry(x*2+1,ll,rr));
		pu(x);
		return maxn;
	}
}tree;
signed main() {
//	freopen("A.out","w",stdout);
	cin>>tt;
	while(tt--) {
		bool fd=0;
		for(int i=1;i<=n;i++) c[i]=go[i]=st[i]=0;
		for(int i=1;i<=q;i++) l[i]={0,0};
		cin>>n>>q>>C;
		for(int i=1;i<=n;i++) {
			cin>>c[i];
			if(!c[i]) {
				go[i]=i;
			}
			else go[i]=go[i-1],st[i]=1;
		}
		for(int i=1;i<=q;i++) cin>>l[i].x>>l[i].y;
		tree.build(1,1,n);
		sort(l+1,l+1+q);
		for(int i=1;i<=q;i++) {
			if(max(tree.qry(1,1,l[i].x),(int)1)<max((int)1,tree.qry(1,1,l[i].y-1))) {
//				cout<<"&&&&"<<i<<endl;
				int tmp=max((int)1,tree.qry(1,1,l[i].y-1));
				if(!go[l[i].x]) {
//					cout<<"!!"<<endl;
					fd=1;
					break;
				}
				tree.change(1,go[l[i].x],tmp);
				c[go[l[i].x]]=tmp;
			}
			if(st[l[i].y]) {
				if(c[l[i].y]<=max((int)1,tree.qry(1,1,l[i].x))) {
//					cout<<"??"<<endl;
					fd=1;
					break;
				}
			}
			else if(c[l[i].y]<=max((int)1,tree.qry(1,1,l[i].x))) {
				int tmp=max(tree.qry(1,1,l[i].x),(int)1)+1;
				if(tmp>C) {
//					cout<<"@@"<<endl;
					fd=1;
					break;
				}
				tree.change(1,l[i].y,tmp);
				c[l[i].y]=tmp;
			}
		}
		if(fd) {
			puts("-1");
			continue;
		}
//		for(int i=1;i<=n;i++) cout<<c[i]<<' ';
//		cout<<endl;
		for(int i=1;i<=q;i++) {
			if(c[l[i].y]<=max((int)1,tree.qry(1,1,l[i].x))) {
//				cout<<"**"<<endl;
				fd=1;
				break;
			}
			if(max((int)1,tree.qry(1,1,l[i].x))<max((int)1,tree.qry(1,1,l[i].y-1))) {
//				cout<<"(("<<endl;
				fd=1;
				break;
			}
		}
		for(int i=1;i<=n;i++) if(c[i]>C) {
//			cout<<"##"<<endl;
			fd=1;
			break;
		}
		if(fd) {
			puts("-1");
			continue;
		}
		for(int i=1;i<=n;i++) if(c[i]) cout<<c[i]<<' '; else cout<<"1 ";
		puts("");
	}
	return 0;
}
```

---

## 作者：Ranmantic_Tea (赞：0)

拿到题目不用多想，直接线段树。

对于一个询问，他是分成了两段。

一：对于 $1$ 到 $a_{i}$ 这一段的最大值小于 $h_{i}$。

二：$1$ 到 $a_{i}$ 这一段的最大值要大于 $a_{i} + 1$ 到 $h_{i} - 1$ 这一段的最大值。

如果没有条件二，我们直接一颗线段树搞定。

具体的，我们扫一遍，每一次把 $1$ 到 $a_i$ 这一段的最大值用线段树得到，如果当前为要改，就变成最大值加 $1$。如果没有询问搞成，但是要修改就搞成 $1$。没有修改就不动他。

但是现在有了条件二，我们考虑记一下在当前扫到的 $i$ 之前的最后一个可以修改的位置，如果有需要就直接改，改成 $a_{i} + 1$ 到 $h_{i} - 1$ 这一段的最大值。

要注意的是我们需要排序，按照 $a_{i}$ 排序，因为真么想我们都可以是对小的一段扩展到大的吧。

这道题本质上是个贪心，要求字典序最小，就直接放他的最小值就可以，这同样可以使后面的更小。这个贪心不多赘述，看有了性质二为什么可以直接改。

首先，他的 $a_{i}$ 并不相同，所以我们可以先到更改这个对其他的影响。

存在的可能情况只有 $a_{i}$ 小于 $a_{j}$，$h_{i}$ 小与 $h_{j}$。

显而易见，更改对当前值对这个情况没有影响，直接搞。

要注意的是需要排序，因为同一个 $h_{i}$ 下，$a_{i}$ 小的应该先满足更大。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
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
inline void out(ll x) {
	if (x < 0) putchar('-');
	if (x > 9) out(x / 10);
	putchar('0' + x % 10);
}
const int MX = 3e5 + 10;
int a[MX], id[MX];
#define lw(x) (x<<1)
#define rw(x) (x<<1|1)
#define mid ((l+r)/2)
int tree[MX * 4];
int h[MX], top = 0;
void push_up(int x) {
	tree[x] = max(tree[lw(x)], tree[rw(x)]);
}
void build(int x, int l, int r) {
	if (l == r) {
		tree[x] = a[l];
		return;
	}
	build(lw(x), l, mid);
	build(rw(x), mid + 1, r);
	push_up(x);
}
void change(int x, int l, int r, int id, int w) {
	if (l == r) {
		tree[x] = w;
		return ;
	}
	if (id <= mid) change(lw(x), l, mid, id, w);
	else change(rw(x), mid + 1, r, id, w);
	push_up(x);
}
ll find(int x, int l, int r, int ln, int rn) {
	if (ln <= l && r <= rn) return tree[x];
	ll ans = 0;
	if (mid >= ln) ans = max(ans, find(lw(x), l, mid, ln, rn));
	if (mid < rn) ans = max(ans, find(rw(x), mid + 1, r, ln, rn));
	return ans;
}
basic_string<int>p[MX];
int next(int x) {
	int l = 1, r = top;
	ll ans = 0;
	while (l <= r) {
		if (h[mid] <= x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	if (ans == 0) return -1;
	return h[ans];
}
ll n, c, Q;
bool check() {
	build(1, 1, n);
	FOR(i, 1, n) {
		if (a[i] > c) return 0;
		for (int y : p[i]) {
			ll A = find(1, 1, n, 1, y);
			if (y != i - 1) {
				ll B = find(1, 1, n, y + 1, i - 1);
				if (B > A) return 0;
			}
			if (A >= a[i]) return 0;
		}
	}
	return 1;
}
struct sky {
	int x, y;
} q[MX];
bool cmp(sky &a, sky &b) {
	return a.x < b.x;
}
signed main() {
//	freopen("P10134_4.in", "r", stdin);
//	freopen("P10134.out", "w", stdout);
	int T = read();
	while (T--) {
		n = read(), Q = read(), c = read();
		FOR(i, 1, n) a[i] = read();
		top = 0;
		FOR(i, 1, n) p[i].clear();
		build(1, 1, n);
		FOR(i, 1, Q)  q[i].x = read(), q[i].y = read();
		sort(q + 1, q + Q + 1, cmp);
		FOR(i, 1, Q) {
				p[q[i].y] += q[i].x;
		}
		FOR(i, 1, n) {
			if (a[i] == 0) {
				h[++top] = i;
				ll sum = 0;
				for (int y : p[i]) {
					ll A = find(1, 1, n, 1, y);
					sum = max(sum, A);
					ll B = -1;
					if (y != i - 1) B = find(1, 1, n, y + 1, i - 1);
					else continue;
					if (A < B) {
						int id = next(y);
						if (id == -1) continue;
						a[id] = B;
						sum = max(sum, B);
						change(1, 1, n, id, B);
					}
				}
				a[i] = sum + 1;
				change(1, 1, n, i, sum + 1);
			} else {
				for (int y : p[i]) {
					ll A = find(1, 1, n, 1, y);
					ll B = -1;
					if (y != i - 1) B = find(1, 1, n, y + 1, i - 1);
					if (B == -1) continue;
					if (A < B) {
						int id = next(y);
						if (id == -1) continue;
						a[id] = B;
						change(1, 1, n, id, B);
					}
				}
			}
		}
		if (check()) {
			cout << a[1];
			FOR(i, 2, n) cout << " " << a[i];
			puts("");
		} else cout << "-1", puts("");
	}
	return 0;
}
```

——end——

---

## 作者：Jerrywang09 (赞：0)

线段树可以有效减少思维含量。建议评分：蓝。

设
$$
x=\max _{k=1}^i a_k
$$
$$
y=\max _{k=i+1}^{j-1} a_k
$$
则 FJ 的限制 $(i, j)$ 可以表示为 $x\ge y$ 并且 $x<a_j$。

将所有限制按 $i$ 从小到大排序后，对每个限制 $(i, j)$ 执行以下流程。

1. $x<y$。如果 $1\sim i$ 全部填完了，则无解。否则，为了字典序最小，找到**最靠近** $i$ 的没填的下标 $pre(i)$，$a_{pre(i)}\leftarrow y$，$x\leftarrow y$。
2. $a_j$ 已经填数但 $a_j\le x$。一定无解。
3. $a_j$ 没有填数。如果 $1\sim i$ 全都没有填数，$a_j\leftarrow 2$，不然 $a_j\leftarrow x+1$。

然后扫描一遍整个 $a$ 数组，如果 $a_i>c$ 则无解，如果 $a_i$ 没有填则 $a_i\leftarrow 1$。

最后复查一遍，输出答案。线段树需要支持单点修改、区间查询最大值。

```cpp
// Title:  Cowmpetency
// Source: USACO24JAN Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=300010;
using namespace std;

int n, T, C, a[N], pre[N]; pii q[N];
struct node
{
    int l, r, x;
} t[N<<4];
#define lc p<<1
#define rc p<<1|1
void build(int p, int l, int r)
{
    t[p]={l, r, a[l]};
    if(l==r) return;
    int m=l+r>>1;
    build(lc, l, m), build(rc, m+1, r);
    t[p].x=max(t[lc].x, t[rc].x);
}
int query(int p, int l, int r)
{
    if(l<=t[p].l && t[p].r<=r) return t[p].x;
    int m=t[p].l+t[p].r>>1, res=0;
    if(l<=m) res=max(res, query(lc, l, r));
    if(r>m)  res=max(res, query(rc, l, r));
    return res;
}
void modify(int p, int i, int x)
{
    if(t[p].l==t[p].r) {t[p].x=x; return;}
    int m=t[p].l+t[p].r>>1;
    if(i<=m) modify(lc, i, x); else modify(rc, i, x);
    t[p].x=max(t[lc].x, t[rc].x);
}
#define err {puts("-1"); return;}
void solve()
{
    scanf("%d%d%d", &n, &T, &C);
    rep(i, 1, n)
    {
        scanf("%d", a+i);
        if(a[i]) pre[i]=pre[i-1]; else pre[i]=i;
    }
    build(1, 1, n);
    rep(i, 1, T) scanf("%d%d", &q[i].F, &q[i].S);
    sort(q+1, q+T+1);
    rep(k, 1, T)
    {
        int i=q[k].F, j=q[k].S;
        int x=query(1, 1, i), y=query(1, i+1, j-1);
        if(x<y)
        {
            if(!pre[i]) err
            x=a[pre[i]]=y, modify(1, pre[i], y);
        }
        if(a[j] && a[j]<=x) err
        if(!a[j])
            a[j]=x?x+1:2, modify(1, j, a[j]);
    }
    rep(i, 1, n)
    {
        if(a[i]>C) err
        if(!a[i]) a[i]=1, modify(1, i, a[i]);
    }
    rep(k, 1, T)
    {
        int i=q[k].F, j=q[k].S;
        int x=query(1, 1, i), y=query(1, i+1, j-1);
        if(!(x>=y && a[j]>x)) err
    }
    rep(i, 1, n) printf("%d%c", a[i], " \n"[i==n]);
}

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    int T; scanf("%d", &T);
    while(T--) solve();
    
    return 0;
}
```

---

