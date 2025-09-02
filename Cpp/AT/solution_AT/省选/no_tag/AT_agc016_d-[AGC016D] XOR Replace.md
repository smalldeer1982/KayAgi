# [AGC016D] XOR Replace

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc016/tasks/agc016_d

長さ $ N $ の数列 $ a\ =\ (a_1,\ a_2,\ ...,\ a_N) $ があります。 ただし、各 $ a_i $ は $ 0 $ 以上の整数です。

すぬけ君は次の操作を繰り返し行うことができます。

- $ a $ のすべての要素の XOR を $ x $ とする。 整数 $ i $ ($ 1\ <\ =\ i\ <\ =\ N $) をひとつ選び、$ a_i $ を $ x $ に置き換える。

すぬけ君の目標は、$ a $ を数列 $ b\ =\ (b_1,\ b_2,\ ...,\ b_N) $ に一致させることです。 ただし、各 $ b_i $ は $ 0 $ 以上の整数です。

目標が達成可能か判定し、達成可能ならば必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 10^5 $
- $ a_i $, $ b_i $ は整数である。
- $ 0\ <\ =\ a_i,\ b_i\ <\ 2^{30} $

### Sample Explanation 1

最初、$ a $ のすべての要素の XOR は $ 3 $ です。 $ a_1 $ を選んで $ 3 $ に置き換えると、$ a\ =\ (3,\ 1,\ 2) $ となります。 次に、$ a $ のすべての要素の XOR は $ 0 $ です。 $ a_3 $ を選んで $ 0 $ に置き換えると、$ a\ =\ (3,\ 1,\ 0) $ となり、$ b $ に一致します。

## 样例 #1

### 输入

```
3
0 1 2
3 1 0```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 1 2
0 1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
2
1 1
0 0```

### 输出

```
-1```

## 样例 #4

### 输入

```
4
0 1 2 3
1 0 3 2```

### 输出

```
5```

# 题解

## 作者：小粉兔 (赞：19)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC016.html](https://www.cnblogs.com/PinkRabbit/p/AGC016.html)。

令初始的异或和为 $x$，拿在手中，相当于每次用手中的数把 $a$ 中的一个值顶掉，然后把原来的值拿在手里。

那么可以先判一下 $b$ 是否一定能被得到：只需判 $b$ 的可重集是否包含于 $a \cup \{x\}$ 即可。

然后我们考虑一个过程，用 $x$ 替换了 $a_p$，然后用 $a_p$ 替换了 $a_q$，循环下去。

其实最终一定是要用 $b_i$ 替换 $a_i$ 的，而上面的过程又是从 $x$ 出发走了一条路。

这启发我们从 $b_i$ 向 $a_i$ 连边（不同位置上相同的数值对应同一个点），然后尝试从 $x$ 出发遍历每条边。

注意如果图是一个包含 $x$ 的连通块，则一定可以找到一条欧拉路径（不一定是回路）覆盖所有边。

如果图不连通，或 $x$ 不在连通块内（$x$ 是孤立点），则答案就是边数再加上连通块数再减去 $1$（如果 $x$ 是孤立点就不用减 $1$）。

```cpp
#include <cstdio>
#include <vector>
#include <map>

const int MN = 100005;

int N, A[MN], B[MN], X, cnt, M, Ans;
std::map<int, int> mp;

int vis[MN];
std::vector<int> G[MN];
void DFS(int u) {
	vis[u] = 1;
	for (int v : G[u]) if (!vis[v]) DFS(v);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]), ++mp[A[i]], X ^= A[i];
	for (int i = 1; i <= N; ++i) scanf("%d", &B[i]), --mp[B[i]];
	++mp[X];
	for (auto p : mp) if (p.second < 0) return puts("-1"), 0;
	for (auto &p : mp) p.second = ++cnt;
	for (int i = 1; i <= N; ++i) if (A[i] != B[i]) {
		int u = mp[B[i]], v = mp[A[i]];
		G[u].push_back(v);
		G[v].push_back(u);
		++M;
	}
	for (int i = 1; i <= cnt; ++i) if (!G[i].empty())
		if (!vis[i]) ++Ans, DFS(i);
	if (!G[mp[X]].empty()) --Ans;
	printf("%d\n", M + Ans);
	return 0;
}
```

---

## 作者：attack (赞：16)

## 题意

[题目链接](https://agc016.contest.atcoder.jp/tasks/agc016_d)

给出两个长度为$n$的数组$a, b$

每次可以将$a$中的某个数替换为所有数$xor$之和。

若$a$数组可以转换为$b$数组，输出最少操作次数

否则输出$-1$

## Sol

一般那看到这种$N \leqslant 10^5$而且不可做的题肯定是先找结论啦

不难看出，我们把所有数$xor$起来的数替换掉之后再次$xor$，得到的一定是被替换掉的数。

实际上，我们可以把xor出来的数放到一个新的位置$N+1$，这样每次操作就变成了交换第$N+1$个位置的数和任意一个位置$x$的数

总的问题就变成了

>给出两个长度为$N+1$的数组$a, b$，每次可以在$a$中交换$\forall i \in [1, n]$位置和$N+1$位置的数，问最少交换几次变为$b$数组

首先把$-1$的情况判掉，很显然，把两个数组排序后，若存在一个位置不相同，则一定无解

否则一定有解。

到这里我就不会了。。。。

官方题解非常神仙。

对于$i$位置，若$a_i \not = b_i$，则向$a_i$到$b_i$连一条边

最终答案 = 总边数 + 联通块数 - 1

想一想为什么，对于联通块内的点，假设其大小为$x$，我们一定可以通过$x-1$次操作把他们对应的$a$和$b$变的相同

对于不同联通块之间，我们还需要一步操作使得第$N+1$个位置的数在两个联通块之间转化(第一个除外)

对于第$N+1$个位置需要单独考虑：如果它已经在联通块里则不需要考虑，否则把它看做单独联通块

否则

	2
	1 3
	3 1

可以用并查集维护联通块个数
```cpp
#include<bits/stdc++.h>
const int MAXN = 4e5 + 10;
using namespace std;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}
int N;
int a[MAXN], b[MAXN], ta[MAXN], tb[MAXN], sa, sb, tot = 0, date[MAXN], fa[MAXN];
map<int, bool> ti;
int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}
int unionn(int x, int y) {
	fa[x] = y;
}
int main() {
	N = read();
	for(int i = 1; i <= N; i++) a[i] = read(), sa ^= a[i]; a[N + 1] = sa;
	for(int i = 1; i <= N; i++) b[i] = read(), sb ^= b[i]; b[N + 1] = sb;
	N++;
	memcpy(ta, a, sizeof(a)); memcpy(tb, b, sizeof(b));
	sort(ta + 1, ta + N + 1); sort(tb + 1, tb + N + 1);
	for(int i = 1; i <= N - 1; i++) if(ta[i] != tb[i]) return puts("-1"), 0;
 
	int ans = 0, num = 0;
	for(int i = 1; i <= N; i++) 
		if(a[i] != b[i] || (i == N)) {
			date[++num] = a[i]; date[++num] = b[i];
			if(i < N)ans++;//最后一块单独考虑
		}
	if(ans == 0) return puts("0"), 0;
 
	sort(date + 1, date + num + 1);
	num = unique(date + 1, date + num + 1) - date - 1;
	for(int i = 1; i <= num; i++) fa[i] = i;
	for(int i = 1; i <= N; i++)
		if(a[i] != b[i]) {
			a[i] = lower_bound(date + 1, date + num + 1, a[i]) - date,
			b[i] = lower_bound(date + 1, date + num + 1, b[i]) - date;
			if(!ti[a[i]]) ti[a[i]] = 1;
			if(!ti[b[i]]) ti[b[i]] = 1;
			unionn(find(a[i]), find(b[i]));
		}
		
	for(int i = 1; i <= num; i++)
		if(fa[i] == i) ans++;
	printf("%d", ans - 1);
 
	return 0;
}
```

---

## 作者：Kewth (赞：7)

感觉这个建边很神啊，按我的理解给出一个证明。

令 k 为 a 的异或和。  
不难发现每次操作 a[x] 等价于交换 a[x] 与 k ，  
那么将 a, b, k 离散化后，判无解就很简单了，接下来假设一定有解。

对于 a[i] 和 b[i] ，如果 a[i] != b[i] ，连边 b[i] -> a[i] ，  
这样建出来一个图，把 k 作为当前位置，考虑现在操作 a[x] 在图上的意义，

1. k 向 a[x] 有边，那么操作 a[x] 等价于删掉这条边并移动 k 到 a[x]  
2. k 向 a[x] 无边，但存在 y 向 a[x] 有边，那么操作 a[x] 等价于把 y -> a[x] 的一条边改为 y -> k ，并移动 k 到 a[x] 。

1 操作后边数减一，2 操作后边数不变，最终需要的状态是没有边，可以知道答案的一个下界就是边数，  
现在的目标就是最小化 2 操作的次数使得图没有边。

在有解的情况下，设 K 为 b 的异或和，任意时刻 k 的连边有两种情况：  

- k != K ，k 的出度一定比入度多 1  
- k == K ，k 的出度恰好等于入度

原因：连边 (K, k) 后整张图所有点需要满足入度等于出度。

那么 k 没有出边当且仅当 k 是一个孤立的点且 k = K，  
也就是说对于一个有 x 条边的联通块，一定可以通过 x 次 1 操作将边删干净且 k 停留在 K 。  
当 k = K 且被孤立的时候，就需要通过 2 操作跳到另一个联通块，并且让该联通块与 K 联通。

由此就可以得到最少需要的 2 操作次数了。

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int a[maxn], b[maxn];
int tmp[maxn];
int tot[maxn];
int fa[maxn], size[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++) {
		a[i] = read;
		a[n + 1] ^= a[i];
	}

	for(int i = 1; i <= n + 1; i ++)
		tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 2);

	for(int i = 1; i <= n + 1; i ++) {
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 2, a[i]) - tmp);
		++ tot[a[i]];
	}

	for(int i = 1; i <= n; i ++) {
		b[i] = read;
		int x = int(std::lower_bound(tmp + 1, tmp + n + 2, b[i]) - tmp);
		if(tmp[x] != b[i] or !tot[x]) return puts("-1"), 0;
		b[i] = x;
		-- tot[x];
	}

	for(int i = 1; i <= n + 1; i ++) {
		fa[i] = i;
		size[i] = 1;
	}

	int ans = -1;
	for(int i = 1; i <= n; i ++) {
		int x = find(a[i]), y = find(b[i]);
		if(a[i] != b[i]) {
			/* debug("%d - %d\n", tmp[a[i]], tmp[b[i]]); */
			fa[x] = y;
			if(x != y)
				size[y] += size[x];
			++ ans;
		}
	}

	for(int i = 1; i <= n + 1; i ++)
		if(fa[i] == i and size[i] > 1)
			++ ans;

	if(fa[a[n + 1]] == a[n + 1] and size[a[n + 1]] == 1)
		++ ans;

	printf("%d\n", ans);
}
```

---

## 作者：_Diu_ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT2388)

[AT 的传送门](https://atcoder.jp/contests/agc016/tasks/agc016_d)

一道很神仙的思维题。

我们先观察一下这个操作：

假设当前序列为 $\{a_i\}$ ，异或和为 $A$，

将第 $j$ 位进行交换得：

$a_1,a_2,\dots,a_{k-1},A,a_{k+1},\dots$，

此时异或和恰好为： $a_k$。

因此，一次操作我们可以认为是将位置 $k$ 上的数和位置 $n+1$ 上的数交换。

我们把异或和放在位置 $n+1$，

那么判无解的方法就是看看两个数组是否能一一对应。

接下来就是求方案数了。

我们可以这样假设：

$A:a_1,a_2,a_3,\dots,a_k$ 与

$B:a_k,a_1,a_2,\dots,a_{k-1}$ 对应，这样操作多少次。

显然我们可以把第一个数和 $n+1$ 交换，再把第二个数和 $n+1$ 交换，一次类推，最后再把第一个数和 $n+1$ 换回来，就完成了一个环的交换。

这个交换一共花了 $k+1$ 次操作。

但是考虑一个特例：

$A:a_1,a_2,a_3,\dots,A,\dots,a_k$ 与

$B:a_k,a_1,a_2,\dots,a_1$，

也就是如果第 $n+1$ 个数在这个换里面，

显然我们可以从第 $n+1$ 个数那个地方开始交换，这样就少了一次操作。

所以如果对于每一个 $a,b$ 不对等的位置，从 $a_i$ 往 $b_i$ 连边，

这样会形成若干个环，也就是连通块。

根据刚才的结论，答案为 `总边数+连通块数-1`，

但是像样例 2、4，就能把这个方法卡死，

原因是第 $n+1$ 个数不处于任何环上，导致多减去了 $1$，

所以我们就算 $a_{n+1}$ 和 $b_{n+1}$ 相同，也强制连边，但不统计入总边书，这样就解决了这个问题。

当然也可以用其它的特判方法。

## code

处理连通块（也就是环）的情况我是用并查集来维护的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,a[N],b[N],fa[N],t1[N],t2[N],t3[N],tot;
int find(int x){
	return fa[x]?fa[x]=find(fa[x]):x;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[n+1]^=a[i],t1[i]=a[i];t1[n+1]=a[n+1];
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]),b[n+1]^=b[i],t2[i]=b[i];t2[n+1]=b[n+1];
	++n;
	sort(t1+1,t1+n+1);
	sort(t2+1,t2+n+1);
	for(int i=1;i<=n;i++)
		if(t1[i]^t2[i]){puts("-1");return 0;}
	int ans=0;
	for(int i=1;i<=n;i++)
		if((a[i]^b[i])||i==n)
			t3[++tot]=a[i],t3[++tot]=b[i],ans+=(i<n);
	if(!ans){puts("0");return 0;}
	sort(t3+1,t3+tot+1);
	int low=unique(t3+1,t3+tot+1)-t3-1;
	for(int i=1;i<=n;i++){
		if(a[i]^b[i]){
			a[i]=lower_bound(t3+1,t3+low+1,a[i])-t3;
			b[i]=lower_bound(t3+1,t3+low+1,b[i])-t3;
			int x=find(a[i]),y=find(b[i]);
			if(x!=y)fa[x]=y;
		}
	}
	t1[0]=t1[1]-1;
	for(int i=1;i<=low;i++)if(!fa[i])ans++;
	printf("%lld\n",ans-1);
}
```

---

## 作者：_tourist_ (赞：3)

可以发现一个显而易见的性质：每取出一个数是所有数异或和，再次取出的时候的值就是刚才被替换掉的那个值。

所以题意转化如下：$A$数组有$n+1$个数，$B$数组有$n$个数，从$A$中的指定的一个值开始，每次选择和一个值交换，直至AB两串相等。

不合法的情况很显然：B中有的数在A中没有出现过。

然后最小化方案，考虑建图，如果$A$中的$X$要变成$B$中的$Y$，相当于从$Y$向$X$连一条边，走过这条边相当于把$Y$变成$X$，然后现在手上的是$X$。

可以发现边数就是$AB$前$n$个元素不同的值的个数，要把所有边全部走过，最好情况就是直接有欧拉路，那么交换次数就是边数。

但是通过不合法的性质我们可以发现每个值的入度和出度差至多为1，因为前$n$个元素至多有一个不相同，故对于每个联通块一定都有欧拉路。

所以我们只要对不同联通块之间加一条边就可以满足要求了，答案是**边数+联通块数-1**

注意一个特殊情况：如果$A$中刚开始指定的值在所有联通块中都没有出现过，需要多花费一步进入联通块。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200005;
int n,a[N],sum=0,b[N],val[N],t[N],m,vis[N],ans=0;
int cnt=0;
namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=m;i++) fa[i]=i;}
    int getfather(int x){
        if(x==fa[x]) return x;
        return fa[x]=getfather(fa[x]);
    }
    void unite(int x,int y){
        x=getfather(x),y=getfather(y);
        if(x==y) return;
        fa[x]=y; cnt--;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum^=a[i];
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) val[i]=a[i];
    val[n+1]=sum; a[n+1]=sum;
    sort(val+1,val+n+2);
    m=unique(val+1,val+n+2)-val-1;
    for(int i=1;i<=n+1;i++){
        int pos=lower_bound(val+1,val+m+1,a[i])-val;
        t[pos]++;
    }
    for(int i=1;i<=n;i++){
        int pos=lower_bound(val+1,val+m+1,b[i])-val;
        if(b[i]!=val[pos]||!t[pos]){
            puts("-1");
            exit(0);
        }
        t[pos]--; 
    }
    int pos;
    for(int i=1;i<=m;i++) if(t[i]) pos=i,t[i]=0;
    for(int i=1;i<=n+1;i++){
        int pos=lower_bound(val+1,val+m+1,a[i])-val;
        if(i==n+1||b[i]!=a[i]) t[pos]++;
    }
    if(t[pos]==1&&val[pos]==sum) ans++;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(val+1,val+m+1,a[i])-val;
        b[i]=lower_bound(val+1,val+m+1,b[i])-val;
    }
    DSU::init();
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]) continue;
        if(!vis[a[i]]) vis[a[i]]=1,cnt++;
        if(!vis[b[i]]) vis[b[i]]=1,cnt++;
        ans++; DSU::unite(a[i],b[i]);
    }
    if(ans==0) puts("0");
    else printf("%d\n",ans+cnt-1);
    return 0;
}
```

---

## 作者：qzmoot (赞：3)

# 题解：AT_agc016_d [AGC016D] XOR Replace
## 题目大意
给你一个 $A$ 序列和一个 $B$ 序列。每次你可以选择一个位置 $i$，将 $A_i$ 修改成当前 $A$ 的异或和。问你最少花几次能够实现将 $A$ 修改成 $B$，或者输出无解。
## 分析
这丢到了我们模拟赛的第二题，关键是我们还是联赛模拟啊。但是场切了，感觉没有那么难吧……

言归正传，我看到这个题目的第一个反应就是打个暴力，结果我很糖，写了个迭代加深，结果感觉过不了很多点，于是就开始思考正解了。不难发现每次我们操作一次，异或和就会和 $A_i$ 的值互换。然后我们为了完成目标，就要接着把 $B_j$ 与 $A_i$ 的位置修改。这很像一个欧拉路径。

接着我们考虑把 $A_i$ 与 $B_i$ 连边。对于连通块内，我们的操作数就是边数。但每次转换成另外一个连通块则需要多耗费一个操作次数，那么答案就显而易见了。就是 $n-1$ 再加上我们的连通块数减一。

无解部分也很好判断，开一个桶，把 $A_i$ 序列里的所有数和初始异或和丢进去，再减去 $B_i$ 里的所有数，如果有数的个数小于 $0$ 就无解了。

但是这才是大纲部分，我们还有很多细节需要考虑。如果 $A_i$ 和 $B_i$ 相等，我们不需要连边（连边了也无妨，判断一下连通块的大小就可以了）。

但是答案一定是 $n-1$ 加上一个数吗？如果对于初始异或和 $sum$ 没有出现在 $B$ 中，则我们的答案需要额外加 $1$ 因为如果是 $n-1$ 的话，我们最后的答案中一定是会存在 $sum$ 的，多加一次操作数即可（但是我们模拟赛数据竟然没有出现这个孤立点问题，不判断也可以水过）。

顺便说一句别忘了离散化。
## Code
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+5,inf=1e9;
int n,a[N],b[N],sum,ans;
int f[N<<1],siz[N<<1];
int idx,al=1,gl;
map<int,int>mp;//离散化 
map<int,int>t;//桶 
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]); 
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		f[y]=x,siz[x]+=siz[y];
}
int main()
{
//	freopen("xor.in","r",stdin);
//	freopen("xor.out","w",stdout);
	scanf("%d",&n);
	ans=n-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(!mp[a[i]])
			mp[a[i]]=++idx;
		sum^=a[i];
		t[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		if(a[i]==b[i])
			ans--;
		else
			al=0;
		if(!mp[b[i]])
			mp[b[i]]=++idx;
		t[b[i]]--;
	}
	if(al)
		return puts("0"),0;//特判全部一样 
	t[sum]++;
	for(auto v:t)
		if(v.second<0)
			return puts("-1"),0;//判断不合法 
	for(int i=1;i<=idx;i++)
		f[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++)
		merge(mp[a[i]],mp[b[i]]);//连边 
	for(int i=1;i<=idx;i++)
		if(find(i)==i && siz[i]!=1)
			ans++;//对于每个连通块来统计答案 
	if(siz[find(mp[sum])]==1 || !mp[sum])
		ans++;//孤立点 
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Mingjunyi (赞：2)

## [[AGC016D] XOR Replace](https://www.luogu.com.cn/problem/AT_agc016_d)

来自 @[qzmoot](https://www.luogu.com.cn/user/774854) 同一机房的同学的题解。

模拟赛用不同的思路场切了。

### 题面大意：一个序列，一次操作可以将某个位置变成整个序列的异或和。 问最少几步到达目标序列。

来自梦熊的题面：

有一个长度为 $n$ 的序列 $a$，有以下函数:

```cpp
void update(int u){
	int w=0;
	for(int i=1;i<=n;i++) w^=a[i];
	a[u]=w;
}
```

你可以执行这个函数若干次，其中参数 $u$ 由你指定，请问将序列 $a$ 修改为序列 $b$ 的最小调用次数是多少。

### 分析：

#### 操作逻辑简化
我们先要知道这个操作在干什么。

如果你指定一个 $u$，使 $w = a_u$、$a_u = \oplus_{i = 1}^n a_i$，

那么当你再指定一个 $u^{\prime}$ 时，$a_{u^{\prime}} = \oplus_{i = 1}^n a_i = w$。

这是由于异或具有自反性。

那么，这个操作就相当于你有一个初始为 $a$ 的序列，同时手里还纂着一个 $\oplus_{i = 1}^n a_i$，你每次可将手中的数和序列中的数交换，直到序列 $a$ 变成序列 $b$。

#### 合法情况判断

接下来判断的是怎样才是合法的局面。

根据上面的分析，容易发现这个序列 $a$ 有两种情况：   
1. 序列 $a$ 和序列 $b$ 的数种类相同，且每种种类的数的个数相同。
2. 序列 $a$ 和序列 $b$ 的数种类只有一种不同，该种类数的个数是 $1$，且该数为初始的 $\oplus_{i = 1}^n a_i$。

#### 最小操作数

接下来是最小操作数的分析。

我们的操作肯定是取出一个数，直接放进与 $b$ 对应的位置。

因为只有合法局面（序列中的数一定是一一对应的）才会计算最小操作数，所以这样做一定是最优的。

并且 $a$ 和 $b$ 已经匹配上的位置可以不用考虑。

那么，你会发现我们的拿取操作形成了一个环或链。

因此，我们可以将 $a$ 和 $b$ 中的对应位置的数连边。

其必然形成若干简单环和链，如图：

![img](https://cdn.luogu.com.cn/upload/image_hosting/vork6eeb.png)

![img](https://cdn.luogu.com.cn/upload/image_hosting/5pk81cf6.png)

对于链，其中必定有 $\oplus_{i = 1}^n a_i$，这时最小操作数为**链的边数个数**。

对于环，其中必定没有 $\oplus_{i = 1}^n a_i$，这时我们会先将 $\oplus_{i = 1}^n a_i$ 放到任意一个位置，最后将所有环中数字位置调整完后取出来，最小操作数为**环的边数 + 1**。

用并查集统计答案就可以过了。

最后由于 $a_i,b_i < 2^{30}$，所以用并查集计算答案之前需要离散化。

这种方法好像不需要判孤立点（大概吧，本人没有仔细研究）。

### AC-code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int rd() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-') w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + (ch - '0');
		ch = getchar();
	}
	return x * w;
}
void wt(int x) {
	static int sta[35];
	int f = 1;
	if(x < 0) f = -1,x *= f;
	int top = 0;
	do {
		sta[top++] = x % 10, x /= 10;
	} while (x);
	if(f == -1) putchar('-');
	while (top) putchar(sta[--top] + 48);
}
signed main() {
	int n = rd(),top = 0;
	vector<int> a(n),b(n),c(n * 2),s(n * 2),siz(n * 2),t(n * 2);
	vector<bool> bok(n * 2),ext(n * 2);
	vector<int> in(n * 2);
	for(int i = 0;i<n;i++) a[i] = rd();
	for(int i = 0;i<n;i++) b[i] = rd();
	for(int i = 0;i<n;i++) c[top++] = a[i],c[top++] = b[i];
	int w = 0;
	for(int i = 0;i<n;i++) w ^= a[i];
	c.emplace_back(w);	
	sort(c.begin(),c.end());
	top = unique(c.begin(),c.end()) - c.begin() - 1;
	for(int i = 0;i<n;i++) 
		a[i] = lower_bound(c.begin(),c.begin() + top + 1,a[i]) - c.begin(),
		b[i] = lower_bound(c.begin(),c.begin() + top + 1,b[i]) - c.begin();
	w = lower_bound(c.begin(),c.begin() + top + 1,w) - c.begin();
	for(int i = 0;i<n;i++) t[a[i]]++;
	t[w]++;
	for(int i = 0;i<n;i++) {
		t[b[i]]--;
		if(t[b[i]] < 0) {puts("-1");return 0;}
	}
	bool flag = false;
	for(int i = 0;i<n;i++) 
		if(a[i] != b[i]) {flag = true;break;}
	if(!flag) {wt(0);return 0;}
	for(int i = 0;i<n * 2;i++) {s[i] = i;ext[i] = 0;siz[i] = 0;bok[i] = 0;}
	for(int i = 0;i<n;i++) {
		if(a[i] == b[i]) continue;
		bok[a[i]] = bok[b[i]] = true;
		siz[b[i]]++;
		if(w == b[i]) ext[b[i]] = true; 
	}
	auto find = [&](auto self,int x) -> int {
		if(s[x] ^ x) 
			s[x] = self(self,s[x]);
		return s[x];
	};
	for(int i = 0;i<n;i++) {
		if(a[i] == b[i]) continue;
		int fa = find(find,a[i]),fb = find(find,b[i]);
		if(fa != fb) {
			s[fa] = fb;
			siz[fb] += siz[fa];
			ext[fb] = ext[fb] | ext[fa];
		}
	}
	int ans = 0;
	for(int i = 0;i<n * 2;i++) {
		if(bok[i] && find(find,i) == i) {
			if(ext[find(find,i)]) ans += siz[find(find,i)];
			else ans += siz[find(find,i)] + 1;
		}
	}
	wt(ans);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

**[D - XOR Replace](https://atcoder.jp/contests/agc016/tasks/agc016_d)（5）**

假设 $a_{n+1}=a_1\text{ XOR }a_2\text{ XOR }\dots\text{ XOR }a_n$。那么一次操作相当于交换 $a_i,a_{n+1}$。这要求 $a,b$ 同构。

我们先考虑 $a,b$ 都是排列的做法，不妨假设 $a_i=i$。那么研究 $b$ 上的一个环：

- 如果是自环，不用操作；
- 如果环包含 $n+1$，需要 $|C|-1$ 次操作；
- 否则，需要 $|C|+1$。

不难发现包含 $n+1$ 的环恰好只有一个，那么我们的任务就是最小化环的个数。

这是简单且经典的的，我们在 dfs 的时候直接搜同值域的 $b$ 的位置即可（具体参考代码）。

有一点细节。

[submission](https://atcoder.jp/contests/agc016/submissions/45038285)

---

## 作者：cheng2010 (赞：1)

## 思路

发现，其实题意可以转化为：

给你一个长度为 $n+1$ 的序列，其中，前 $n$ 个是输入，最后一个是前 $n$ 个的异或和，每一次可以把其中一个与最后一个交换，问交换多少下才能把 $a$ 变得与给定的 $b$ 一样。

想到这，这题便不难了。

把 $a_i$ 与 $b_i$ 不同的连边，那么每一条边都是要交换的，所以，答案一定有边的数量，再有，对于每个联通块，它们必须先有一个与 $n+1$ 交换，才可以继续操作，所以答案还要加上联通块的数量（单点不算）

最后，若 $n+1$ 也连了条边出去，那么它是什么都可以，不必在意，答案就要减一。

至于无解：

只要 $b$ 中有 $a$ 中没有的数便无解（$a$ 的异或和不算）。

## code
```cpp
// LUOGU_RID: 196762060
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
int n,a[N],b[N];
int res,ans2,ans1;
struct EDGE
{
	int frm,to;
}edge[N];
map<int,int> head,d,kk,vis;
set<int> t;
int cnt;
inline void add(int x,int y)
{
	d[x]++;
	edge[++cnt].to=y;
	edge[cnt].frm=head[x];
	head[x]=cnt;
}
inline void dfs(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].frm)
	{
		int v=edge[i].to;
		if(!vis[v])
			dfs(v);
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		kk[a[i]]++;
		t.insert(a[i]);
		res^=a[i];
	}
	kk[res]++;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
		kk[b[i]]--;
		t.insert(b[i]);
	}
	for(auto A:kk)
	{
		if(A.second<0)
		{
			puts("-1");
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=b[i])
		{
			int x=b[i],y=a[i];
			add(x,y);
			add(y,x);
			ans2++;
		}
	}
	for(int i:t)
	{
		if(d[i])
		{
			if(!vis[i])
			{
				ans1++;
				dfs(i);
			}
		}
	}
	if(d[res])
		ans1--;
	printf("%lld\n",ans2+ans1);
}
```

---

## 作者：六楼溜刘 (赞：1)

# [AGC016D] XOR Replace

[传送门](https://www.luogu.com.cn/problem/AT_agc016_d)

## 题意

- 给定两长度为 $n$ 的序列 $a,b$，你可以进行任意次以下操作：
    - 将 $a$ 的某个位置赋值为 $a$ 整个序列的异或和。
- 求将 $a$ 变成 $b$ 至少需要操作多少次，无解输出 $-1$。
- $1\le n\le 1\times 10^5,0\le a_i < 2^{30}$

## 题解

趣味题。

考虑手思考一下“赋值为 $a$ 整个序列的异或和”这个操作，假设我们对 $a_i$ 操作，原序列异或和为 $s$，那么新的异或和就变为了 $s\oplus a_i\oplus s=a_i$，相当于将 $a_i$ 和 $s$ 互换。

那么相当于有 $n+1$ 个小球和 $n$ 个盒子，每个小球有颜色，初始为序列 $a$，每次将不在盒子里的那个小球与另一小球交换，问至少需要交换多少次才能让颜色序列变为 $b$。

显然无解当且仅当某种颜色的小球数量对不上，可以直接判掉，考虑怎么求最小操作数。

不难想到对颜色进行图论建模，连边 $(a_i,b_i)$，首先所有不是自环的边需要一次操作，其次除去多出的那个小球所在的连通块以外，每个大小大于 $1$ 的连通块还需要额外一次操作。

具体考虑每个连通块都是一个欧拉回路，唯独多出来的那个小球如果在某个连通块，那么这个连通块是一个不是回路的欧拉路，其余每个连通块都需要在离开的时候将原来的小球换回去，只有他自己不需要。

复杂度 $O(n\log n)$，瓶颈在离散化。

## code

```cpp
#include<bits/stdc++.h>
#define forup(i,s,e) for(int i=(s),E123123123=(e);i<=E123123123;++i)
#define fordown(i,s,e) for(int i=(s),E123123123=(e);i>=E123123123;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void();
#endif
using namespace std;
using i64=long long;
using pii=pair<int,int>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=1e5+5,inf=0x3f3f3f3f;
int n,a[N],b[N],ans;
map<int,int> cnt;
vector<int> lsh;
int sz;
vector<int> e[N];
bool vis[N];
int cc=0;
void dfs(int x){
    vis[x]=1;++cc;
    for(auto i:e[x]){
        if(vis[i]) continue;
        dfs(i);
    }
}
signed main(){
    n=read();
    int sum=0;
    forup(i,1,n){
        a[i]=read();
        sum^=a[i];
        ++cnt[a[i]];
        lsh.push_back(a[i]);
    }
    ++cnt[sum];
    lsh.push_back(sum);
    sort(lsh.begin(),lsh.end());
    lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
    sz=lsh.size();
    forup(i,1,n){
        b[i]=read();
        --cnt[b[i]];
        if(cnt[b[i]]<0){
            puts("-1");
            return 0;
        }
    }
    ans=0;
    forup(i,1,n){
        a[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin();
        b[i]=lower_bound(lsh.begin(),lsh.end(),b[i])-lsh.begin();
        if(a[i]!=b[i]){
            e[b[i]].push_back(a[i]);
            e[a[i]].push_back(b[i]);
            ++ans;
        }
    }
    sum=lower_bound(lsh.begin(),lsh.end(),sum)-lsh.begin();
    dfs(sum);
    forup(i,0,sz-1){
        if(!vis[i]){
            int pc=cc;
            dfs(i);
            ans+=(cc-pc>1);
        }
    }
    printf("%d\n",ans);
}
```

---

## 作者：laoliu12345 (赞：1)

## AT_agc016_d
[题目传送门](https://www.luogu.com.cn/problem/AT_agc016_d)
### 解法说明
首先设 $x$ 为序列的异或和，那对于每一次操作都可以看为将一个数 $a_i$  换为  $x$ ，并将异或和 $x$ 换为这个数 $a_i$。转化后就简单了，对于 -1 的情况，我们只需要对 $A B$ 排序并判断在加上异或和 $x$ 的情况下是否每个对应元素都相等。而对于非 -1 的情况，我们对对应位置不同的元素建边，答案就是建边数加上联通块数减一。
### 题目代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 1000007; 
int a[N],b[N],c[N],d[N]; 
int n; 
map<int,int>f; 
int fa[N]; 
int find(int x) { 
	if(fa[x] != x) fa[x] = find(fa[x]); 
	return fa[x]; 
} 
int main() { 
    //freopen("xor.in","r",stdin);
	//freopen("xor.out","w",stdout);
	cin>>n;
	for(int i = 1;i <= n;++ i) cin>>a[i];
	for(int i = 1;i <= n;++ i) cin>>b[i];
	int t = 0; 
	for(int i = 1;i <= n;++ i) t ^= a[i]; 
	a[n + 1] = t; 
	t = 0; 
	for(int i = 1;i <= n;++ i) t ^= b[i]; 
	b[++ n] = t; 
	for(int i = 1;i <= n;++ i) c[i] = a[i],d[i] = b[i]; 
	sort(c + 1,c + n + 1); 
	sort(d + 1,d + n + 1); 
	for(int i = 1;i <= n;++ i) { 
		if(c[i] != d[i]) { 
			cout<<-1<<endl;
			return 0; 
		} 
	} 
	int cnt = 0; 
	int ans = 0; 
	for(int i = 1;i <= n;++ i) { 
		 if(a[i] != b[i] || i == n)  { 
		 	if(i < n) ans ++; 
		  	if(!f[a[i]])f[a[i]] = ++cnt; 
		  	if(!f[b[i]])f[b[i]] = ++cnt; 
		  	
		 }  
	} 	 
	if(!ans) { 
		cout<<0<<endl;
		return 0; 
	} 
	for(int i = 1;i <= cnt;++ i) fa[i] = i; 
	for(int i = 1;i <= n;++ i) { 
		if(a[i] != b[i]) fa[find(f[a[i]])] = find(f[b[i]]); 
	} 
	for(int i = 1;i <= cnt;++ i) if(fa[i] == i) ans ++; 
	cout<<ans-1<<endl;
	return 0; 
} 
```

---

## 作者：Composite_Function (赞：0)

考虑这个操作有什么性质。注意到一个数被替换成所有数的 $\operatorname{xor}$ 后，所有数的 $\operatorname{xor}$ 即为原来所有数的 $\operatorname{xor}$ 和原来除了这个被替换掉的数的 $\operatorname{xor}$，也就是这个数的 $\operatorname{xor}$。

人话：一个数被替换以后下一个替换的数就是这个原来的数。

这样已经可以把无解的情况给判掉了。考虑最小操作数。

考虑看作一张图。边就是 $b_i \rightarrow a_i$（$a_i \neq b_i$）。每一次可以从一个点到另一个点。考虑什么情况下是一个符合要求的。

注意到每条边至少被走一次。从一个连通块到另一个连通块至少多走一次。所以答案至少是边数加连通块数减一。

同时注意到有解的情况下，每个连通块：

- 要么长成可以分解为环路的图，此时直接沿着环一个一个换即可。
- 要么长成可以一笔画但无法变成环路的图。此时出发点一定是一笔画的出发点，沿着该路径一个一个换即可。

所以答案就是边数加连通块数减一。

---

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = 1e5 + 10;
int n, a[N], b[N], s, cnt, flag;
map<int, int> fa, c;
inline int getfa(int x) {
	return !fa.count(x) || fa[x] == x? x : fa[x] = getfa(fa[x]);
}
inline void merge(int x, int y) {
	x = getfa(x), y = getfa(y);
	if (x != y) fa[x] = y;
}

signed main() {
	rin >> n;
	for (int i = 1; i <= n; ++i) rin >> a[i], s ^= a[i], ++c[a[i]];
	for (int i = 1; i <= n; ++i) rin >> b[i], cnt += a[i] != b[i], --c[b[i]];
	for (int i = 1; i <= n; ++i) if (a[i] != b[i]) fa[a[i]] = a[i], fa[b[i]] = b[i];
	fa[s] = s, ++c[s], --cnt;
	for (int i = 1; i <= n; ++i) merge(a[i], b[i]);
	for (auto p : fa) cnt += p.first == p.second;
	for (auto p : c) flag += abs(p.second);
	if (flag > 1) cout << -1 << endl;
	else cout << cnt << endl;
	return 0;
}
```

---

## 作者：TheShuMo (赞：0)

## 题意

一个序列，一次操作可以将某个位置变成整个序列的异或和。 问最少几步到达目标序列。

## 题解

序列整体异或和用来替换一个序列中的元素，怎么看都是一个很美妙的东西。

设整个序列的异或和为 $x$，将要替换的元素的位置为 $i$，则该被替换元素的值为 $a_i$。\
则替换后的 $a_i' =x$，$x'=(x \oplus a_i) \oplus x =a_i$。

这其实相当于有一个临时变量 $p=x$，每次操作将其与序列中的一个数对换，求序列转换为目标序列的步数。

于是有解当且仅当对于每个当前序列的值与其异或和，在目标序列及其异或和中有一一对应。这个容易判定。

然后是最小步数，这个好像是一个比较典的问题，类似置换，我们将 $a_i$ 和 $b_i$ 连边，这会形成一些环，每个环用其边数加一的代价就可以转换为目标序列（因为要先将 $x$ 换进去再换出来所以要多一次）。

注意若 $x$ 出现在目标序列中，这时候修改这个环不再需要先替换 $x$ 为其中元素，答案要减去 $1$。

代码就不贴了。

---

## 作者：Zhl2010 (赞：0)

一道比较好玩的思维题。

## 题面
一个序列 $a$，一次操作可以将某个位置变成整个序列的异或和。

问最少几步变成序列 $b$。

## 思路
让我们充分发扬人类智慧。

### 第一步
我们可以发现，$a$ 序列变来变去只可能有 $n+1$ 个数，也就是序列原有的数和这个序列的异或和，这一点应该很好理解，因为我们把所有数异或起来的数替换掉之后再次异或，得到的一定是被替换掉的数。

然后我们就可以特判 `-1` 了。

我们需要看一看 $a$ 和 $b$ 序列的数能不能一一对应，我用的是 `map`，遍历序列，$mp_{a_i}$ 需要加一，$mp_{b_i}$ 需要减一，如果 $mp$ 中有小于 $0$ 的数就代表不成立，因为 $b$ 序列要用的数 $a$ 序列没有。

### 第二步（详细讲解原理）
这是最关键而巧妙的一步。

我们考虑将 $a_i$ 替换成 $b_i$，可以从需要替换的 $a_i$ 这个数向 $b_i$ 这个数连接，表示需要替换。

对于联通块内，想要替换完这些数字的次数用该是 $边数+1$，可以这样理解：

对于当前的数 $a_i$ 在连通块内有它需要替换的 $b_i$，就直接将 $b_i$ 和 $a_{n+1}$ 交换，然后再将 $a_{n+1}$ 和 $a_i$ 交换，这时候就交换成功了第一个数，对于第二个数，我们就将需要 $a_{n+1}$ 的 $a_i$ 与之交换（可以发现，联通块内的点都是需要用的），所以只有第一条边需要用 $2$ 次交换，其它只用一次。

然后我们可以发现特殊情况：第 ${n+1}$ 个数。

我们发现，如果 $a_{n+1}$ 向外连了边，对于那个联联通块，就可以少连一条边，所以答案要减一，对于它是单独的点，就不变。

## 代码
注意细节
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010],b[100010],x=0,cnt=0;
int ans=0;
map<int,int>mp;
vector<int>e[100010];
int vis[100010];
void dfs(int now){
	vis[now]=1;
	for(int i=0;i<e[now].size();i++){
		if(!vis[e[now][i]]){
			dfs(e[now][i]);
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mp[a[i]]++;
		x^=a[i];
	}
	mp[x]++;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		mp[b[i]]--;
	}
	for(auto p:mp){
		if(p.second<0){
			puts("-1");
			return 0;
		}
	}
	for(auto &p:mp)p.second=++cnt;
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]){
			int u=mp[b[i]],v=mp[a[i]];
			e[u].push_back(v);
			e[v].push_back(u);
			m++;//记录变数
		}
	}
	for(int i=1;i<=cnt;i++){
		if(e[i].size()!=0&&!vis[i]){//求联通块个数
			ans++;
			dfs(i);
		}
	}
	if(e[mp[x]].size())ans--;
	cout<<ans+m<<endl;
	return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

算是第一次独立想出这样难度的题。

首先考虑手玩一下“变成整个序列的异或和”这个操作。发现如果一开始对 $i$ 位置进行操作，记录一个值为原来所有的 $a_i$ 中，现在不在 $a$ 中的 $a_i=x$，则以后：

- 如果对 $j(j\not=i)$ 操作，则 $a_j\to a_i,x\to a_j$

- 如果对 $i$ 进行操作，则 $a_i\to x$。

然后考虑转换一下问题，就是一开始先花一步选一个位置，把它变成特殊位置，然后每次操作可以选一个位置和特殊位置上的数互换，最后再用一步把特殊位置变回来，求最少需要多少次操作。

这个问题怎么解决呢？一开始考虑这会形成若干个环，但是如果出现重复值会假。然后发现，如果设 $i$ 为特殊位置，然后令 $j$ 和它交换，则特殊位置的值会变成 $a_j$，并且如果交换后 $a_j=b_j$ 则以后不会再动 $j$。

这启发我们让 $a_j$ 向 $b_j$ 连边，每次让特殊位置的 $a_i$ 找到一个 $b_j=a_i$，然后将这位解决，并修改 $x$ 的值为 $a_j$。因此可以发现，**此时原问题的限制就变成，我们需要将每条边恰好经过一次**。

这是什么？欧拉路问题，并且容易发现是回路。再进一步思考，由于有解时每个点 $in_i=out_i$，所以每个联通块一定都有在块内的欧拉回路。

对于多个连通块呢？发现每多一个连通块，就要额外多耗费一次去先进入这个连通块。于是设联通块数量为 $c$，则答案至多为 $n+c$。并查集维护。

其实到这里这题的主题部分已经解决了，但是为什么说至多呢？因为这题还是有很多细节的。

- 首先，如果可重集 $a$ 不等于可重集 $b$，则如果 $b$ 只比 $a$ 多一个数，且多的数为 $\bigoplus_i a_i$，则是有解的，具体就是把 $a$ 中多出来的变成这个，同时答案也要变化。

- 其次，设置和取消特殊位置的两步，如果有一个  $a_i=\bigoplus_ia_i$，则可以省去其中一步。

- 再者，还要特判有 $a_i=b_i$，可以直接省略这一位。同时，还要特判全相等/只有一个位置不等的情况。

- 其他还有较多细节，不一一展开讲，具体可以参考代码。但是由于我感觉这题数据不算特别强，所以欢迎 hack。

总的来说，这是一道完美地融合了两个非常巧妙的思维的神题。虽然比较粪的实现可能给我带来了一定困扰，但是不得不说我还是非常喜欢这一题的。

code：

```cpp
int n,m,a[N],b[N],d[N],c[N],f[N],g[N];
struct DSU{
	int fa[N],siz[N];
	void init(){
		rep(i,1,m){
			fa[i]=i,siz[i]=1;
		}
	}
	int find(int x){
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	il void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y){
			return;
		}
		siz[y]+=siz[x],fa[x]=y;
	}
}D;
void Yorushika(){
	scanf("%d",&n);
	int s=0;
	rep(i,1,n){
		scanf("%d",&a[i]);
		s^=a[i],d[i]=a[i];
	}
	int ans=n;
	rep(i,1,n){
		scanf("%d",&b[i]);
		if(a[i]==b[i]){
			a[i]=b[i]=-1;
			ans--;
		}
		d[i+n]=b[i];
	}
	if(!ans){
		puts("0");
		return;
	}
	if(ans==1){
		rep(i,1,n){
			if(~a[i]){
				if(b[i]==s){
					puts("1");
				}else{
					puts("-1");
				}
				return;
			}
		}
	}
	sort(d+1,d+n+n+1),m=unique(d+1,d+n+n+1)-d-1;
	rep(i,1,n){
		f[i]=lower_bound(d+1,d+m+1,a[i])-d;
		g[i]=lower_bound(d+1,d+m+1,b[i])-d;
		c[f[i]]++,c[g[i]]--;
	}
	int sum=0;
	rep(i,1,m){
		sum+=abs(c[i]);
	}
	if(sum>2){
		puts("-1");
		return;
	}
	if(!sum){
		if(*lower_bound(d+1,d+m+1,s)==s){
			ans--;
		}
	}else{
		ans--;
		rep(i,1,m){
			if(c[i]==-1){
				if(d[i]!=s){
					puts("-1");
					return;
				}
			}
		}
		rep(i,1,m){
			if(c[i]==1){
				rep(j,1,n){
					if(a[j]==d[i]&&b[j]==s){
						a[j]=s,f[j]=-1;
						goto END;
					}
				}
				rep(j,1,n){
					if(a[j]==d[i]){
						a[j]=s,f[j]=lower_bound(d+1,d+m+1,a[j])-d;
						goto END;
					}
				}
			}
		}
	}
	END:
	D.init();
	rep(i,1,n){
		if(~f[i]){
			D.merge(f[i],g[i]);
		}
	}
	rep(i,1,m){
		if(D.fa[i]==i&&D.siz[i]!=1){
			ans++;
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

