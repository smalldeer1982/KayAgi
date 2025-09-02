# Prefix Enlightenment

## 题目描述

There are $ n $ lamps on a line, numbered from $ 1 $ to $ n $ . Each one has an initial state off ( $ 0 $ ) or on ( $ 1 $ ).

You're given $ k $ subsets $ A_1, \ldots, A_k $ of $ \{1, 2, \dots, n\} $ , such that the intersection of any three subsets is empty. In other words, for all $ 1 \le i_1 < i_2 < i_3 \le k $ , $ A_{i_1} \cap A_{i_2} \cap A_{i_3} = \varnothing $ .

In one operation, you can choose one of these $ k $ subsets and switch the state of all lamps in it. It is guaranteed that, with the given subsets, it's possible to make all lamps be simultaneously on using this type of operation.

Let $ m_i $ be the minimum number of operations you have to do in order to make the $ i $ first lamps be simultaneously on. Note that there is no condition upon the state of other lamps (between $ i+1 $ and $ n $ ), they can be either off or on.

You have to compute $ m_i $ for all $ 1 \le i \le n $ .

## 说明/提示

In the first example:

- For $ i = 1 $ , we can just apply one operation on $ A_1 $ , the final states will be $ 1010110 $ ;
- For $ i = 2 $ , we can apply operations on $ A_1 $ and $ A_3 $ , the final states will be $ 1100110 $ ;
- For $ i \ge 3 $ , we can apply operations on $ A_1 $ , $ A_2 $ and $ A_3 $ , the final states will be $ 1111111 $ .

In the second example:

- For $ i \le 6 $ , we can just apply one operation on $ A_2 $ , the final states will be $ 11111101 $ ;
- For $ i \ge 7 $ , we can apply operations on $ A_1, A_3, A_4, A_6 $ , the final states will be $ 11111111 $ .

## 样例 #1

### 输入

```
7 3
0011100
3
1 4 6
3
3 4 7
2
2 3```

### 输出

```
1
2
3
3
3
3
3```

## 样例 #2

### 输入

```
8 6
00110011
3
1 3 8
5
1 2 5 6 7
2
6 8
2
3 5
2
4 7
1
2```

### 输出

```
1
1
1
1
1
1
4
4```

## 样例 #3

### 输入

```
5 3
00011
3
1 2 3
1
4
3
3 4 5```

### 输出

```
1
1
1
1
1```

## 样例 #4

### 输入

```
19 5
1001001001100000110
2
2 3
2
5 6
2
8 9
5
12 13 14 15 16
1
19```

### 输出

```
0
1
1
1
2
2
2
3
3
3
3
4
4
4
4
4
4
4
5```

# 题解

## 作者：Kelin (赞：9)

## [题解](https://blog.csdn.net/BeNoble_/article/details/107141931)

一盏灯最多只会在$2$个集合里出现。

设包含第$i$盏灯的两个集合依次为$L_i,R_i$（若没有则值为$0$）。设$op_S=1$表示集合$S$选过，$op_S=0$表示没选过。

对于第$i$盏灯的情况进行讨论

1. $L_i=0,R_i=0$,说明这盏灯不属于任何集合且$s_i$一定为$1$,故答案不变。
2. $L_i\neq0,R_i=0$，说明这盏灯只由一个集合控制。如果$op_{L_i}=1\land s_i=1$，那么一定要撤销$L_i$的选择。如果$op_{L_i}=0\land s_i=0$，那么一定要选$L_i$。其余两种情况，$L_i$状态必须不变。前两种情况，即$op_{L_i}=s_i$时会使得与$L_i$有关联的集合状态发生改变，故答案会发生改变；而后两种不变。
3. $L_i\neq0,R_i\neq0$,说明这盏灯只由两个集合同时控制，所以这两个集合有关联.与$2.$同理讨论可得：如果$op_{L_i}\oplus op_{R_i}=s_i$，那么其中一个集合的状态一定要发生改变，优先选择改变总操作次数少且与之关联的集合能够改变状态的集合，答案加上这部分开销。否则，两个集合状态都可以不变，故答案不变。

对于关联性问题,常常使用并查集来解决。

设$Cost_u$表示改变改变集合$u$状态的总代价，$Cant_u$表示集合$u$的状态是不是不能改变。

1. 根节点集合$u$的状态要改变，则并查集里所有集合的状态都要取反，这样才能确保不影响$s_{1...i}$。花费代价$Cost_u$，然后$Cost_u$变为其相反数,表示之后撤销的代价.取反可以在根节点打上一个$tag$，子树里的点的实际状态都是原来的状态异或上根节点的$tag$。
2. 由于有合并操作，故某点$x$的实际状态为：$x$到根节点路径上所有节点的$tag$值的异或和。对于一个并查集，只有根节点的$tag$值在之后可能会发生改变，故可以将$x$到**根节点儿子**这一段$tag$值的异或和合并起来，即路径压缩过程中**不引入**根节点的$tag$。
3. 将并查集$x$合并到$y$上：$\ Cost$累加；$\ Cant$取或；$\ tag_x$异或上$tag_y$，以确保$x$的子节点状态不变.

时间复杂度$O(n\alpha(m))$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
typedef int arr[N];
int n, m, Ans;
char s[N];
arr L, R, fa, tag, Cant, Cost, Size;
inline int Gf(int x) {
    if (!fa[x])
        return x;
    if (!fa[fa[x]]) // 跳过根节点的tag
        return fa[x];
    int p = Gf(fa[x]);
    tag[x] ^= tag[fa[x]];
    return fa[x] = p;
}
inline void Merge(int a, int b) {
    fa[a] = b, 
    Size[b] += Size[a], 
    Cost[b] += Cost[a], 
    Cant[b] |= Cant[a],
    tag[a] ^= tag[b];
}
inline int op(int x) { return tag[x] ^ tag[fa[x]]; }
inline int Calc(int i) {
    if (!L[i])
        return Ans;
    if (!R[i]) {
        int x = Gf(L[i]);
        Cant[x] = 1;
        if (op(L[i]) == (s[i] - '0'))
            Ans += Cost[x], tag[x] ^= 1, Cost[x] = -Cost[x];
        return Ans;
    }
    int x = Gf(L[i]), y = Gf(R[i]);
    if (Size[x] > Size[y])
        swap(x, y);
    if (x == y)
        return Ans;
    if ((op(L[i]) ^ op(R[i])) == s[i] - '0') {
        int Cx = Cost[x], Cy = Cost[y];
        if ((Cx < Cy && !Cant[x]) || Cant[y])
            Ans += Cx, tag[x] ^= 1, Cost[x] = -Cx;
        else
            Ans += Cy, tag[y] ^= 1, Cost[y] = -Cy;
    }
    Merge(x, y);
    return Ans;
}
int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    for (int i = 1, c; i <= m; ++i) {
        scanf("%d", &c);
        for (int x; c--;)
            scanf("%d", &x), L[x] ? R[x] = i : L[x] = i;
    }
    for (int i = 1; i <= m; ++i)
        Size[i] = Cost[i] = 1;
    for (int i = 1; i <= n; ++i)
        printf("%d\n", Calc(i));
    return 0;
}
```

---

## 作者：Jelefy (赞：8)

（本题需要用到**种类并查集**的概念。如果对此概念尚不明晰，可以先去做[食物链](https://www.luogu.com.cn/problem/P2024)和[关押罪犯](https://www.luogu.com.cn/problem/P1525)这两道题）

---
首先将题目条件$A_{i_1}∩A_{i_2}∩A_{i_3}=\varnothing$翻译成人话就是：

**每盏灯最多在2个集合中出现**

为什么这很重要呢？如果一盏灯的初始状态为$0$，那么显然它所属的两个集合**要么选择一个，要么选择另一个**。如果初始状态为$1$，那么两个集合**要么两个都选，要么两个都不选**。这种关系可以考虑利用种类并查集来维护：

先假定每盏灯都在两个集合中出现。开2倍空间并查集，定义$1\sim n$为第一层，$n+1\sim 2n$为第二层。

定义“将一盏灯加入并查集”为如下操作：
- 若这盏灯的初始状态为$0$，则将所在的两个集合跨层合并。
- 若这盏灯的初始状态为$1$，则将所在的两个集合同层合并。

那么，若要满足所有已加入并查集的灯都变亮，可知：

**对于并查集中每一个连通块，要么选择其在第一层中的部分，要么选择其在第二层中的部分**（这两个“部分”可以为空）。  
换句话说，选择这两个部分的最终效果是等价的（对于已加入的灯而言）。

怎么证明？假设原来的情况是满足条件的，此时将一个新的灯加入并查集，不论这盏灯的初始状态是$0$还是$1$，都依然满足条件。

因此，只需维护每个连通块分别在两层中的大小，动态维护答案时取$MIN$即可。

最后考虑只在一个集合中出现的灯：将这些灯再加入一个虚集合中。对于该虚集合所在的连通块，只能选择不包含该虚集合的那一层的部分。  
特判即可。
# Code
注：在此代码中虚集合编号为0
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 3e5 + 2;

int n, m, c, x, col[N][2], fa[N << 1], sz[N << 1][2], ans;
char s[N];

int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	ans -= min(sz[x][0], sz[x][1]) + min(sz[y][0], sz[y][1]);
	fa[y] = x;
	sz[x][0] += sz[y][0], sz[x][1] += sz[y][1];
	ans += min(sz[x][0], sz[x][1]);
}

int main(){
	scanf("%d%d%s", &n, &m, s + 1);
	++m;
	for(int i = 1; i < m; i++){
		scanf("%d", &c);
		while(c--){
			scanf("%d", &x);
			col[x][(bool)col[x][0]] = i;
		}
	}
	for(int i = 0; i < (m << 1); i++){
		fa[i] = i;
		sz[i][i >= m] = 1;
	}
	for(int i = 1; i <= n; i++){
		if(s[i] - '0'){
			merge(col[i][0], col[i][1]);
			merge(col[i][0] + m, col[i][1] + m);
		}else{
			merge(col[i][0], col[i][1] + m);
			merge(col[i][1], col[i][0] + m);
		}
		int x = find(0);
		if(sz[x][0] < sz[x][1]) printf("%d\n", (ans >> 1) - sz[x][0] + sz[x][1]);
		else printf("%d\n", ans >> 1);
	}
	return 0;
}
```


---

## 作者：raincity (赞：7)

## 前言
由于已经有的四篇题解都讲得不是非常清楚（我**没有**要抨击别的人的题解的意思，请说我乱D人的喷子们闭嘴），我太菜了看不懂，所以决定自己写一篇。

## 分析
显然不可能重复选同一个子集，这样没有任何意义——又变回原样了。

任意三个子集的交集为空集，翻译成人话，就是每一个位置都只包含在两个集合里面。

我们按次序加入每一个位置，这样可以按次序得到 $S_{1 \sim i}$ 变成 $i$ 个1的最少操作数。

因为每一个位置都只包含在两个集合里面，我们设这两个集合在输入顺序里分别是第 $A,B$ 个，如果只有一个则 $B$ 为0，如果没有则 $A=B=0$。

现在考虑 $S_i$ 是0还是1。

1. 如果是0，那么 $A,B$ 中要选，而且只能选1个。
2. 如果是1，那么 $A,B$ 要么都选，要么都不选。

这时候，我们就要使用 **种类并查集**。

建议先去做 [P2024 食物链](https://www.luogu.com.cn/problem/P2024) 再来食用本题。

类似的，我们将每一个集合拆成两个（这里不好理解，怎么想到了CSP-J 2019 T4，一个拆成两个，如果做过那道题可能更好）。一个代表不选，一个代表选。可以当做分层图理解。

那么，我们现在可以解决这个问题了。

1. 如果是0，那么 $A,B$ 中要选，而且只能选1个，那么将 "A选“和”B不选“连边，将”A不选“和"B选”连边。
2. 如果是1，那么 $A,B$ 要么都选，要么都不选，那么将 "A选“和”B选“连边，将”A不选“和"B不选”连边。

非常明显，每一条边都代表一种合法的选择方案。

也非常明显，每一个联通块里面要么选第一层，要么全部选第二层。所以答案统计的是第一层和第二层的较小值。

此外，这道题不能按秩合并（选和不选不能乱认父亲），为了保证复杂度，只能用路径压缩。WA或者TLE可能是这个原因。

而且按理来说其他题解里面的数组应该开两倍，可是竟然没有RE掉，是数据水还是我理解错了？

## 解决
代码里面有一些细节，有注释。
这份代码以绝对优势(20个点1.14s，除我以外第二1.70s)抢到了rk1（提交了21次，但是毕竟没有浪费你谷评测资源——这是CF题）。

```cpp
#include <ctype.h>
#include <stdio.h>

#define NK 300005
int n, k, ans, siz[NK << 1][2], fa[NK << 1], a[NK], b[NK];
char str[NK];
// 这里的 siz 要存在第一层，第二层的大小，方便统计答案。
// 其他题解的 NK 都不 * 2 的，感觉他们会RE掉

#define gc() getchar()

extern inline int read() { // 快速输入
    int ret = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') ch = gc();
    while (ch >= '0' && ch <= '9') ret = (ret << 1) + (ret << 3) + (ch ^ 48), ch = gc();
    return ret;
}

extern inline int getfa(int x) { //  非递归路径压缩
    int px = x, tmp;
    while (fa[x] != x) x = fa[x];
    while (px != x) tmp = px, px = fa[px], fa[tmp] = x;
    return x;
}

#define min(x, y) ((x) < (y) ? (x) : (y))
#define value(x) min(siz[x][0], siz[x][1])

extern inline void merge(int x, int y) { // 合并 x,y
    x = getfa(x), y = getfa(y);
    if (x == y)
        return;
    ans -= value(x) + value(y);
    fa[y] = x;
    siz[x][0] += siz[y][0], siz[x][1] += siz[y][1];
    // 不要觉得 min(a, b) + min(c, d) = min(a + b, c + d)!要撤销之前的答案，重新统计
    ans += value(x);
}

char buf[2200000], buff[20];
int tot, top;

void write(int x) {
    if (x == 0) {
        buf[tot++] = '0';
        buf[tot++] = '\n';
        return;
    }
    top = 0;
    while (x) buff[top++] = x % 10 + 48, x /= 10;
    while (top) buf[tot++] = buff[--top];
    buf[tot++] = '\n';
}

void flush() { fwrite(buf, 1, tot, stdout); }

int main() {
    n = read(), k = read();
    scanf("%s", str + 1);
    for (register int i = 1; i <= k; i++) {
        register int cnt, x;
        cnt = read();
        while (cnt--) {
            x = read();
            if (!a[x])
	            a[x] = i;
            else
	            b[x] = i;
        }
    }
    // 坑：从0开始循环
    for (register int i = 0; i <= k; i++) siz[i][0] = 1, fa[i] = i;
    for (register int i = k + 1; i <= (k << 1) + 1; i++) siz[i][1] = 1, fa[i] = i;
    // 解释一下为什么设 siz
    // siz[i][0] 表示 i 所在的联通块在第一层的点的个数，siz[i][1] 表示 i 所在的联通块在第二层的点的个数
    // 刚开始 i 所在的联通块只有 i，那么 siz 看 i 在哪一层赋值
    for (register int i = 1; i <= n; i++) {
        if (str[i] == '1')
            merge(a[i], b[i]), merge(a[i] + k + 1, b[i] + k + 1);
        else
            merge(a[i], b[i] + k + 1), merge(b[i], a[i] + k + 1);
        int x = getfa(0);
        if (siz[x][0] < siz[x][1])
            write((ans >> 1) + siz[x][1] - siz[x][0]);
        else
            write(ans >> 1);
    }
    flush();
    return 0;
}
```

---

## 作者：ylxmf2005 (赞：4)

### Description

给定一个长度为 $n$ 的 01 串 $S$，和 $k$ 个 $S$ 的下标子集，且任意三个子集的交集为空集。一次操作可以选择一个子集，将子集中的下标对应的 $S_i$ 取反。令 $m_i$ 为让 $S_{1 \sim i} = 1$ 的最少操作次数，求出所有的 $m_i$，保证有方案。

$1 \leq n,k \leq 3 \times 10^5$。

### Solution

因为三个子集的交集为空集，所以一个数最多出现在两个子集中。将每个子集拆成两个点，一个点为选这个子集，点权为 $1$，一个点为不选这个子集，点权为 $0$。将元素视为边，那么出现两次的元素可以将两个点连边，出现一次的可以与虚拟节点连边，没有出现的不连边。

那么你需要一个将两个点连上一条边，求图上一个点所在联通块的点权之和，而且要能禁止选一些点。~~我会 dfs！~~，带权并查集大法好。

遍历 $i \in [1,n]$。

 - $i$ 在子集 $A$ 中出现。如果 $S_i = 0$，那么将 $A$ 不选与 $\infty$ 虚拟节点合并。如果 $S_i = 1$，那么将 $A$ 选与虚拟节点 $\infty$ 合并。为什么要与 $\infty$ 合并？因为这个点一定不能选，为了避免以后选所以合并。
  
 - $i$ 在子集 $A$ 和 $B$ 中出现。如果 $S_i = 0$，将 $A$ 选与 $B$ 不选合并，$A$ 不选与 $B$ 选合并。如果 $S_i = 1$，将 $A$ 选与 $B$ 选合并，$A$ 不选 与 $B$ 不选合并。


### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, INF = 0x3f3f3f3f;
int n, k, fa[N], val[N], ans = 0;
vector <int> v[N]; 
char S[N];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
} 
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[x] = y, val[y] += val[x];
}
int get(int x) {
    return min(val[find(x)], val[find(x + k)]);
}
int main() {
    scanf("%d%d%s", &n, &k, S + 1);
    for (int i = 1; i <= k; i++) {
        int m, x; scanf("%d", &m);
        while (m--) scanf("%d", &x), v[x].push_back(i);
    } 
    for (int i = 1; i <= k * 2 + 1; i++) fa[i] = i, val[i] = i > k; 
    val[k * 2 + 1] = INF;
    for (int i = 1; i <= n; i++) {
        if (v[i].size() == 1) {  
            ans -= get(v[i][0]);
			merge(v[i][0] + k * (S[i] == '1'), k * 2 + 1);
			ans += get(v[i][0]);
        } else if (v[i].size() == 2) {
			if (S[i] == '0' && find(v[i][0]) != find(v[i][1] + k)) {
        		ans -= get(v[i][0]) + get(v[i][1]);
        		merge(v[i][0], v[i][1] + k), merge(v[i][0] + k, v[i][1]);
        		ans += get(v[i][0]);
        	}
			if (S[i] == '1' && find(v[i][0]) != find(v[i][1])) {
        		ans -= get(v[i][0]) + get(v[i][1]);
        		merge(v[i][0], v[i][1]), merge(v[i][0] + k, v[i][1] + k);
        		ans += get(v[i][0]);
        	}
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：xixiup (赞：4)

## 思路分享

对于这一道题可以考虑**种类并查集**。

根据题意可知，每个灯泡仅可以在两个集合中被修改，所以可以考虑两个集合的情况，又由于每个集合仅能改变一次（改两次就变回原来的状态了），所以总共仅有如下表的4种情况。

| 状态 | 1 | 0 |
| :----------: | :----------: | :----------: |
| **1** | 不变 | 变 |
| **0** | 变 | 不变 |


所以我们就可以考虑建一个图，使得该图有 $2m+2$ 个节点。

我们就可以设 $si_{i,0}$ 为节点 $i$ 不使用时的状态，$si_{i,1}$ 为节点 $i$ 使用时的状态，为了有效地处理一些情况，我们需要开双倍的节点。

但是我们还存在一些仅存在一个点的节点，这些节点就需要单独的两个节点来存储，故总共需要 $2m+2$ 个节点，分为 $2$ 层，第 $1$~$m+1$ 个节点为 $1$ 层，剩下的 $m+1$ 个节点为第二层。

思考，若 $S_i$ 为 $0$，则我们需要一次修改来让它变为 $1$,所以我们需要连接同层的两个节点。但是若为 $1$，则可以修改一次，就要连接不同层的两个节点。

其他一些具体细节会在代码中展示。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300100,maxm=600100;
int n,m,ans,s[maxn],corr[maxn][2];
int fa[maxm],si[maxm][2];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int evaluate(int i){
	return min(si[i][0],si[i][1]);
}
int change(int fx,int fy){
	si[fx][0]+=si[fy][0];
	si[fx][1]+=si[fy][1];
	fa[fy]=fx;
}
void connect(int x,int y){//连接两个节点
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}
	ans-=evaluate(fx)+evaluate(fy);
	change(fx,fy);
	ans+=evaluate(fx);
	return;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		char c=getchar();
		while(c!='0'&&c!='1'){
			c=getchar();
		}
		s[i]=c-'0';
	}
	for(int i=1;i<=m;i++){
		int x;
		scanf("%d",&x);
		for(int j=1;j<=x;j++){
			int y;
			scanf("%d",&y);
			corr[y][(corr[y][0]!=0)]=i;
		}
	}
	m++;
	for(int i=1;i<=m;i++){
		fa[i]=i;
		si[i][0]=1;
	}
	for(int i=m+1;i<=m*2;i++){
		fa[i]=i;
		si[i][1]=1;
	}
	for(int i=1;i<=n;i++){
		if(s[i]==0){//连接不同层的两个结点
			connect(corr[i][0],corr[i][1]+m);
			connect(corr[i][0]+m,corr[i][1]);
		}
		else{//同层的两个结点
			connect(corr[i][0],corr[i][1]);
			connect(corr[i][0]+m,corr[i][1]+m);
		}
		int q=find(0);
		if(si[q][0]<si[q][1]){//因为保证有解，所以需要取一个更大的，以保证正确性。
			printf("%d\n",ans/2-si[q][0]+si[q][1]);
		}
		else{
			printf("%d\n",ans/2);
		}
	}
	return 0;
}

```


---

## 作者：未来姚班zyl (赞：3)

## 题目大意

翻译已经十分清晰了。

## 题目分析

- 条件转化

任意三个交集为 $0$ 意思是每个数只会出现在至多两个集合中。

- ~~套路~~基本分析

每个子集最多操作一次，因为操作两次等于没操作。

- 具体分析

考虑 $s_i$ 对选取子集的限制。假设 $i$ 出现在集合 $A$ 和 $B$ 中（先不考虑只出现一次）。

如果 $s_i=0$，则 $A$ 和 $B$ 中必须只选一个。如果 $s_i=1$，则 $A$ 和 $B$ 要么都选，要么都不选。

这是典型的二分图问题，将集合视为点，如果将第一类中的集合之间连边，则图是二分图，而第二类则是要求 $A,B$ 在二分图的同一边。

先建出二分图并染色。然后从 $1\sim n$ 扫过去，维护点的并查集，记录黑色点和白色点的总和，我们相当于要在每个连通块里选一种颜色的所有点，选数量少的就行。

这时候考虑如果 $i$ 只出现在一个集合里，则相当于钦定了这个集合所在的连通块所选的颜色，扫到它时更新一下就可以。这样写起来细节就比在线维护的做法的少很多。复杂度 $O(n\log n)$，瓶颈在于并查集。

```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=3e5+5;
int n,a[N],b[N],c[N],k,h[N],to[N<<1],nxt[N<<1],cnt,w[N<<1],tot,col[N],sum0[N],sum1[N],f[N],ans,as[N];
string s;
inline void add_(int a,int b,int c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
}
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]); 
}
bool F[N][2];
inline int got(int x){
	if(F[x][0])return sum0[x];
	if(F[x][1])return sum1[x];
	return min(sum0[x],sum1[x]);
}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	ans-=as[x],ans-=as[y],f[x]=y,sum0[y]+=sum0[x],sum1[y]+=sum1[x];
	rep(i,0,1)F[y][i]|=F[x][i];
	ans+=as[y]=got(y);
}
inline void dfs(int x){
	e(x)if(!col[y]){
		if(w[i])col[y]=3-col[x];
		else col[y]=col[x];
		dfs(y);
	}
}
signed main(){
	n=read(),tot=k=read(),cin>>s,s='#'+s;
	repn(i)a[i]=s[i]-'0';
	rep(i,1,k){
		int ct=read();
		rep(j,1,ct){
			int x=read();
			if(!b[x])b[x]=i;
			else c[x]=i;
		}
	}
	repn(i)if(b[i]&&c[i])add_(b[i],c[i],a[i]^1),add_(c[i],b[i],a[i]^1);
	rep(i,1,k)if(!col[i])col[i]=1,dfs(i);
	rep(i,1,k)f[i]=i;
	rep(i,1,k)if(col[i]==1)sum0[i]++;
	else sum1[i]++;
	repn(i){
		if(b[i]&&c[i])merge(b[i],c[i]);
		if(b[i]&&!c[i]){
			int x=find(b[i]);
			ans-=as[x],F[x][(col[b[i]]-1)^a[i]]=1,ans+=as[x]=got(x);
		}
		cout <<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

## [[CF1290C] Prefix Enlightenment](https://www.luogu.com.cn/problem/CF1290C)

前置知识：**种类并查集**。代表例题：[[NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)。

首先需要理解 ”任意三个子集的交集为空集“ 是什么意思。翻译成人话就是：**任意一点顶多出现在两个集合中**。于是我们设 $L_i,R_i$ 分别为包含 $i$ 点的两个集合（若没有则为 $0$）。

题目要求求出对于所有 $m_i$，于是我们考虑一个个加入。对于每个点都有如下情况讨论：

- $S_i=0$，则 $L_i,R_i$ 能且仅能操作一个；
- $S_i=1$，则 $L_i,R_i$ 要么都操作，要么都不操作。

这种维护条件的连通性的题目，想到**种类并查集**。对于每个集合 $k$，设立两个点分别表示操作/不操作，记为 $p(k,0/1)$。则对于如上条件，我们只需连边：

- $S_i=0$，则连边 $p(L_i,0)\leftrightarrow p(R_i,0)$ 和 $p(L_i,1)\leftrightarrow p(R_i,1)$；
- $S_i=1$，则连边 $p(L_i,0)\leftrightarrow p(R_i,1)$ 和 $p(L_i,1)\leftrightarrow p(R_i,0)$。

显然，每一条边都代表一种合法的方案。连完边之后，对于每一个连通块，要么选 ”操作“，要么选 ”不操作“，于是我们在合并的时候统计第一层和第二层的最小值即可。

需要注意：

1. 注意不能按秩合并，那样会导致关系混乱；只能用路径压缩。
2. 还要注意：**要处理一个点仅被一个集合包含的情况**。在上文我们已经说了，如果不存在就是 $0$。所以 $0$ 点需要用来处理这种情况。并查集的空间应该是 $O(2n)$ 的。
3. 对于这个 $0$ 点**不能操作**。所以对于 $0$ 点的两层情况需要特判，只能取不包含的那一部分。

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN=3e5+5;
int n,k,ans;
char s[MAXN];
int L[MAXN],R[MAXN];
int f[MAXN<<1],siz[MAXN<<1][2];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void combine(int u,int v){
	int fu=find(u),fv=find(v);
	if(fu==fv) return;
	ans-=min(siz[fu][0],siz[fu][1])+min(siz[fv][0],siz[fv][1]);
	siz[fu][0]+=siz[fv][0];
	siz[fu][1]+=siz[fv][1];
	f[fv]=fu;
	ans+=min(siz[fu][0],siz[fu][1]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>k>>(s+1);
	for(int i=1,c,x;i<=k;++i){
		cin>>c;
		for(int j=1;j<=c;++j){
			cin>>x;
			L[x]?R[x]=i:L[x]=i;
		}
	}
	for(int i=0;i<=k;++i) f[i]=i,siz[i][0]=1;
	for(int i=k+1;i<=(k<<1|1);++i) f[i]=i,siz[i][1]=1;
	for(int i=1,rt;i<=n;++i){
		if(s[i]=='1') combine(L[i],R[i]),combine(L[i]+k+1,R[i]+k+1);
		else combine(L[i]+k+1,R[i]),combine(L[i],R[i]+k+1);
		rt=find(0);
		if(siz[rt][0]<siz[rt][1]) cout<<(ans>>1)+siz[rt][1]-siz[rt][0]<<'\n';
		else cout<<(ans>>1)<<'\n';
	}
	return 0;
}
```

---

