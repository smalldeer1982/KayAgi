# Equal Reversal

## 题目描述

There is an array $ a $ of length $ n $ . You may perform the following operation on it:

- Choose two indices $ l $ and $ r $ where $ 1 \le l \le r \le n $ and $ a_l = a_r $ . Then, reverse the subsegment from the $ l $ -th to the $ r $ -th element, i. e. set $ [a_l, a_{l + 1}, \ldots, a_{r - 1}, a_r] $ to $ [a_r, a_{r-1}, \ldots, a_{l+1}, a_l] $ .

You are also given another array $ b $ of length $ n $ which is a permutation of $ a $ . Find a sequence of at most $ n^2 $ operations that transforms array $ a $ into $ b $ , or report that no such sequence exists.

## 说明/提示

In the first test case, we can perform the following operations: $ $$$[1,2,4,3,1,2,1,1] \xrightarrow[l=5,\,r=8]{} [1,2,4,3,1,1,2,1] \xrightarrow[l=1,\,r=6]{} [1,1,3,4,2,1,2,1]. $ $ </p><p>In the second test case, we can perform the following operations:  $ $ [1,2,3,1,3,2,3] \xrightarrow[l=1,\,r=4]{} [1,3,2,1,3,2,3] \xrightarrow[l=3,\,r=6]{} [1,3,2,3,1,2,3]. $ $ </p><p>It can be proven that it is impossible to turn  $ a $  into  $ b$$$ in the third and fourth test cases.

## 样例 #1

### 输入

```
5
8
1 2 4 3 1 2 1 1
1 1 3 4 2 1 2 1
7
1 2 3 1 3 2 3
1 3 2 3 1 2 3
3
1 1 2
1 2 1
2
1 2
2 1
1
1
1```

### 输出

```
YES
2
5 8
1 6
YES
2
1 4
3 6
NO
NO
YES
0```

# 题解

## 作者：do_while_true (赞：14)

为什么有些并不显然的东西在题解里是显然的啊，第一种方案构造方式是参考 UOJ 群里八云蓝教的。

---

$a$ 能变换成 $b$ 的充要条件是：

- $a_1=b_1,a_n=b_n$；

- $\{\{a_i,a_{i+1}\}|1\leq i<n,i\in N\}=\{\{b_i,b_{i+1}\}|1\leq i<n,i\in N\}$，也就是相邻元素的无序数对构成的集合相同。

必要：每次操作不会改变 $a_1,a_n$，也不会改变相邻元素的无序数对的集合。

充分：考虑直接构造出这个方案。

---

第一种构造：

若现在已经满足 $a_{[1,i]}$ 与 $b_{[1,i]}$ 相同，设 $a_i=b_i=x,a_{i+1}=b$，$b_{i+1}=c$．

那么 $a_{[i+1,n]}$ 中必然也会出现 $x,c$ 相邻（满足条件二）。

如果 $a_{[i,n]}$ 是 $[x,b,\cdots,c,x,\cdots]$，那么选择两个 $x$ 作为端点旋转即可将 $i+1$ 这个位置匹配成功；

如果 $a_{[i,n]}$ 是 $[x,b,\cdots x,c,\cdots]$，现在想办法把 $x,c$ 转过来：

考虑 $a$ 中 $[x,b,\cdots,x,c]$ 与其对应（区间端点下标相同）在 $b$ 中的 $[x,c,\cdots]$，若这两个区间不满足相邻元素的无序对构成的集合相同（称作平衡），考虑使得两段不平衡的一个数 $y$，形式化地，若将 $a$ 此段中相邻元素组成的无序数对构成的集合称作 $A$，$b$ 构成的称作 $B$，则一定存在一个 $y$ 满足 $\{\{y,z\}|\{y,z\}\in A\}\neq \{\{y,z\}|\{y,z\}\in B\}$，由于 $a$ 和 $b$ 的前 $i$ 个已经相同，那么在 $A$ 中没出现的 $\{y,z\}$ 一定在选出的这一段的后面，所以 $a_{[i,n]}$ 一定形如 $[x,b,\cdots,y,\cdots,x,c,\cdots,y,\cdots]$，选择两个 $y$ 作为端点旋转即可将 $i+1$ 这个位置匹配成功。注意到若 $y=c$，那么在边界上可能会出现点问题，此时直接将 $[x,b,\cdots,c,\cdots,x,c]$ 旋转为 $[x,b,\cdots c,x,\cdots,c]$ 即可转化为平衡时的情况（另一思路是，由于 $|A|=|B|$，说明至少有两个这样的 $y$，选择一个不为 $c$ 的即可）

如果平衡，考虑 $c$ 在无序对集合中出现的奇偶性，那么 $b$ 中这一段的末尾一定是 $c$，这表明 $a$ 中出现了至少两次 $c$，所以在这一段中 $a$ 是 $[x,b,\cdots,c,\cdots,x,c]$ 的形式，那么选择这两个 $c$ 作为端点旋转即可。

---

第二种构造：

考虑建立一个图论模型，建立一个图 $G$，对所有值建一个点，对于所有的 $1\leq i<n$，将 $(a_i,a_{i+1})$ 连一条无向边。那么 $a$ 给定了这张图的一条欧拉路径，而操作相当于翻转在 $G$ 中遍历一个环的顺序。而结论是，通过若干次这样的操作，一定能得到其它任意的起点终点相同的欧拉路径。

首先操作是可逆的，所以考虑将任意两条不一样的路径变为一样的路径。

如果这两条路径从 $x$ 点开始出发的边不同，一条路径 $A$ 走了 $(x,y)$ ，另一条路径 $B$ 走了 $(x,z)$。根据欧拉路径的性质，在走这一步不一样的边之前，$x$ 的邻边还剩下奇数条边没有经过，假设这个数目是 $2k+1$，那么一条合法的欧拉路径会将剩下这 $(2k+1)$ 条边定向为 $(k+1)$ 条出边和 $k$ 条入边。如果在 $A$ 中 $(x,z)$ 是入边，那么 $A$ 翻转 $x\to y\to \cdots \to z\to x$ 这个环即可使得 $A$ 和 $B$ 在这一步上走相同的边；如果 $B$  中 $(x,y)$ 是入边也同理。

那么现在还没考虑的情况就是 $(2k+1)$ 条边中，$A$ 和 $B$ 都将 $(x,y),(x,z)$ 定为了出边，还需要在剩下的 $(2k-1)$ 条边中定  $k$ 条入边和 $(k-1)$ 条出边，如果 $A$ 和 $B$ 有相同的入边 $(c,x)$，那么 $A$ 翻转 $x\to y\to \cdots \to c\to x$，$B$ 翻转 $x\to z\to \cdots \to c\to x$ 即可使得 $A$ 和 $B$ 在这一步上走相同的边。而根据鸽巢原理，$(2k-1)$ 条边中 $A$ 选 $k$ 条，$B$ 也选 $k$ 条，必定会有重复选的。所以一定能找到这样的 $c$．

基于此，我们可以在每一步进行适当的翻转 $A$ 或 $B$ 中一个环的遍历顺序，使得 $A$ 和 $B$ 成为相同的欧拉路径。由于操作可逆，所以得到原结论，通过这样的若干次这样的操作，一定能得到其它任意的起点终点相同的欧拉路径。

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=510;
int n,a[N],b[N];
vpii ans;
void Rev(int l,int r){
	ans.pb(mp(l,r));
	reverse(a+l,a+r+1);
}
bool Solve(int i){
	for(int j=i;j<n;j++)
		if(a[j]==b[i]&&a[j+1]==b[i-1]){
			Rev(i-1,j+1);
			return 1;
		}
	for(int p=i;p<n;p++)
		if(a[p]==b[i-1]&&a[p+1]==b[i]){
			bool fl=0;
			for(int j=i-1;j<=p&&!fl;j++)
				for(int k=p+1;k<=n;k++)
					if(a[j]==a[k]){
						Rev(j,k);
						fl=1;
						break;
					}
			if(!fl){
				return 0;
			}
			for(int j=i;j<n;j++)
				if(a[j]==b[i]&&a[j+1]==b[i-1]){
					Rev(i-1,j+1);
					return 1;
				}
		}
	return 0;
}
void solve(){
	read(n);ans.clear();
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	if(a[1]!=b[1]||a[n]!=b[n]){
		puts("NO");
		return ;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i])continue;
		if(!Solve(i)){
			puts("NO");
			return ;
		}
	}
	puts("YES");
	cout << ans.size() << '\n';
	for(auto x:ans)cout << x.fi << ' ' << x.se << '\n';
}
signed main(){
	int T;read(T);while(T--)solve();
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<clock()<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：11)

给一个完全是图论的解法。

容易发现，如果我们连 $a_{i}\rightarrow a_{i+1}$ 这样一条有向边，从 $a_1$ 开始沿着 $a_{i}\rightarrow a_{i+1}$ 走，则会走出原图的一个欧拉路径。

当我们反转 $[l,r]$ 的时候，到底发生了什么？不难发现 $a_l\rightarrow a_{l+1}\rightarrow ... \rightarrow a_{r}(a_l)$ 是一个环，我们反转以后相当于把它反过来走了一遍。

把边看为无向边，然后设初始图为 $G$，显然，$G$ 的任何一条欧拉路，都可以对应出一个序列 $b$。关键是证明：所有这样得到的序列 $b$ 都可以通过对序列 $a$ 操作得到。

假设 $a$ 与 $b$ 序列在第 $x$ 处开始不同，由题意 $1\lt x\lt n$，否则无解。

设 $u=a_x,v_1=a_{x+1},v_2=b_x$。则一开始我们在 $u$ 点，会走 $u\rightarrow v_1$ 这条边，我们需要证明可以通过若干次环的反转，可以使得其走 $u\rightarrow v_2$ 这条边。

需要注意的是我们走的第一个环一定是边 $u\leftrightarrow v_1$ 所在的环。因为反转环只是调整了你遍历这个环内部点的顺序，但是两个环谁先遍历谁后遍历自始至终是严格确定的。

需要注意的是，在 $a$ 中，虽然你先遍历的是 $u\leftrightarrow v_1$，但是你同样需要在后续某个时刻遍历 $u\leftrightarrow v_2$；在 $b$ 中，虽然先遍历的是 $u\leftrightarrow v_2$，但同样需要在某个时刻遍历 $u\leftrightarrow v_1$ 这条边。这告诉我们，在图 $G$ 中，这两条边都会在一个环上。

好，假设在 $a$ 的欧拉路中，最后 $u\leftrightarrow v_2$ 这条边定向是 $v_2\rightarrow u$，我们发现路径 $u\rightarrow v_1\rightarrow ... \rightarrow v_2\rightarrow u$ 就是一个环，反转它，则就变成了先遍历 $v_2$ 而不是 $v_1$。

类似地，我们假设最后这条边定向是 $u\rightarrow v_2$，则由于它在一个环中（这个环应该不包含边 $u\leftrightarrow v_1$，一定有这样一个环存在，证明见下），反转这个所在环，则定向变为 $v_2\rightarrow u$，回到了上述情况。

由此，我们证明了 $G$ 跑任何一个欧拉路跑出来的序列都是可以得到的，由此我们可以判断是否有解等价于两个序列构造出来的图是否同构。

然后考虑构造方案，根据刚才的证明过程，实质上告诉我们可以从前往后一位位确定，而且每一位的操作次数不超过 $2$（最多反转两次）。

具体地，设 $a_i\neq b_i$，假设存在一个 $j\gt i$ 使得 $a_j=a_{i-1}$ 且 $a_{j-1}=b_i$，则执行一次翻转 $[i-1,j]$ 就可以让第 $i$ 位相同。我们发现其实这等价于上面证明中的第一种情况（即定向为 $v_2\rightarrow u$）。

如果没有这样的 $j$ 存在，那就是第二种情况，也就是存在某个 $\ge i$ 的 $j$ 满足 $a_j=a{i-1}$ 且 $a_{j+1}=b_i$ 了。此时一定存在一个子区间，左端点 $\ge l-1$ 且包含 $[j,j+1]$（也就是上面说的：一定存在于“一个环”中），找到这个区间，反转后又变成了上述情况。

欸我们发现其实这里的构造和上面的证明完全是一一对应的啊。所以操作次数其实 $\le 2\times (n-2)$，时间复杂度 $O(n^3)$。

[记录](https://codeforces.com/contest/1698/submission/162711548)

--------

P.S. 关于所谓的环一定存在的证明。（其实就证明了官方题解所谓的一定存在一个能反转的区间包含 $[j,j+1]$）

我们设 $u\rightarrow v_1\rightarrow ...\rightarrow u$ 是个极小环，当且仅当这个环只出现了两次点 $u$（中间没有再回到过点 $u$）。

那么 $u\rightarrow x$ 和 $y\rightarrow u$ 的边只会出现刚好一次。

所以 $u\rightarrow v_1$ 和 $u\rightarrow v_2$ 不可能同时出现在这个极小环上。

又因为 $u\rightarrow v_2$ 在某个环，所以这个“某个”环不应该存在 $u\leftrightarrow v_1$。

这个东西其实挺难表述出来的，但是想通了以后并不难。如果遇到困难欢迎私信交流（）

Bonus：CF1458D（其实我觉得比这个题简单）

---

## 作者：Social_Zhao (赞：5)

今天学习了 [CF1698F Equal Reversal
](https://www.luogu.com.cn/problem/CF1698F) 的相关内容啊，虽然这样说但是为什么题解里面的代码全是 $n^3$ 的（当然很可能是我没仔细看优化）。

---

首先注意到给出的操作不会改变首尾项以及相邻的无序对构成的可重集（$S(\{a_i\})=\{(\min(a_i, a_{i+1}), \max(a_i, a_{i+1}))\vert 1\leq i < n\}$）。因此如果下列两个条件没有全部满足，我们可以直接回答 $\texttt{NO}$。

1. $a_1=b_1, a_n=b_n$。（$1.1$）
2. $S(\{a_i\})\ne S(\{b_i\})$。（$1.2$）

---

下面的算法表明这个同样也是充分条件。

注意到操作具有可逆性质，我们可以同时对 $\{a_i\}$ 和 $\{b_i\}$ 进行操作使之到达同一个中间状态，然后将对 $\{b_i\}$ 的操作序列反转拼在后面。

从前往后扫，假设现在 $a_{1...i}=b_{1...i}$，考虑进行操作使得 $a_{i+1}=b_{i+1}$。如果这时存在 $b_k=b_i, b_{k-1}=a_{i+1}$，那么翻转 $b$ 的这一段区间可以达到目标（$2.1$）；如果存在 $a_k=a_i, a_{k-1}=b_{i+1}$，那么翻转 $a$ 的这一段区间可以达到目标（$2.2$）。

否则，我们考虑 $a_{i+1...n}$ 和 $b_{i+1...b}$ 当中所有和 $a_i$ 相关的无序对。某一个无序对中，如果 $a_i$ 在序列中实际上出现的位置靠前，则称其为「后缀型无序对」，否则称为「前缀型无序对」。根据上面的条件 $1.2$，无序对是可以建立一一对应关系的。又因为条件 $2.1$ 和 $2.2$ 都没有满足，所以 $(a_i, a_{i+1})$ 和 $(b_i, b_{i+1})$ （这两个都是后缀型）在后面对应的无序对都是后缀型（$3$）。显然，前缀型的个数不会小于后缀型的个数减二。而在 $3$ 当中我们已经确定了四个后缀型，此时后面剩余的前缀型个数严格大于后缀型的个数。则在后面的一一对应中，必然存在一组对应的无序对，它们都是前缀型。我们找到这两个前缀型无序对，分别翻转 $a$ 和 $b$ 中的两个区间，也可以达成目标。

据此可以写出操作次数 $o(2n-2)$，时间复杂度 $O(n^2)$ 的做法，完全不理解为什么题目限制是 $n^2$ 次操作，$n\leq 500$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 505;
int n, a[N], b[N], cnt[N][N];
vector<pair<int, int>> ansA, ansB;
int preA[N], preB[N];

void operateA(int l, int r) { reverse(a + l, a + 1 + r), ansA.emplace_back(l, r); }
void operateB(int l, int r) { reverse(b + l, b + 1 + r), ansB.emplace_back(l, r); }

void solve() {
	n = get();
	for(int i = 1; i <= n; i++) a[i] = get();
	for(int i = 1; i <= n; i++) b[i] = get();
	memset(cnt, 0, sizeof(cnt));
	if(a[1] != b[1] || a[n] != b[n]) return printf("NO\n"), void();
	
	for(int i = 1; i < n; i++) ++cnt[min(a[i], a[i + 1])][max(a[i], a[i + 1])], --cnt[min(b[i], b[i + 1])][max(b[i], b[i + 1])];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(cnt[i][j]) return printf("NO\n"), void();
	
	ansA.clear(), ansB.clear();
	for(int i = 1; i < n; i++) {
		if(a[i + 1] == b[i + 1]) continue;
		int flag = 0;
		for(int j = i + 2; j <= n && !flag; j++) if(a[j] == a[i] && a[j - 1] == b[i + 1]) flag = j; 
		if(flag) { operateA(i, flag); continue; }
		for(int j = i + 2; j <= n && !flag; j++) if(b[j] == b[i] && b[j - 1] == a[i + 1]) flag = j;
		if(flag) { operateB(i, flag); continue; }
		memset(preA, 0, sizeof(preA)), memset(preB, 0, sizeof(preB));
		for(int j = i + 2; j <= n; j++) {
			if(a[j] == a[i]) preA[a[j - 1]] = j;
			if(b[j] == b[i]) preB[b[j - 1]] = j;
		}
		for(int j = 1; j <= n; j++) if(preA[j] && preB[j]) { operateA(i, preA[j]), operateB(i, preB[j]); flag = 1; break; }
		assert(flag);
	}
	
	reverse(ansB.begin(), ansB.end());
	printf("YES\n");
	printf("%d\n", ansA.size() + ansB.size());
	for(auto v : ansA) printf("%d %d\n", v.first, v.second);
	for(auto v : ansB) printf("%d %d\n", v.first, v.second);
}

int main() {
	int T = get();
	while(T--) solve();
	return 0;
}

```

---

## 作者：Godzilla (赞：4)

### CF1698 F

[更好的阅读体验](https://www.cnblogs.com/Tagaki-san/p/18312929)

不错的题目。

考虑必要条件，也就是不变量，发现操作不改变相邻二元组集合，且不能改变 $a_1,a_n$。那么必要条件就是 $a,b$ 相邻二元组集合相等和 $a_1=b_1,a_n=b_n$。

通过构造证明充分性。

对于此类从 $a$ 操作到 $b$ 的问题，且操作可逆，不妨考虑中间状态 $c$，考虑如何操作使得 $a\rightarrow c,b\rightarrow c$。

设目前操作前 $i$ 为 $a,b$ 对应相等，$a_i=x,a_{i+1}=y,b_{i+1}=z$，首先分别考察 $a_{i\dots n}$ 中有无 $zx$ 和 $b_{i\dots n}$ 中有无 $yx$，有的话直接换。

否则猜测必然存在 $a$ 使得 $ax$ 在 $a,b$ 同时存在，考察在 $a_{i\dots n}$ 和 $b_{i\dots n}$，对于任意字符 $p$，形如 $px$ 和 $xp$ 的个数，由于目前存在 $xy$ 和 $xz$，那么它们在 $a,b$ 中相差不超过 $2$。

目前已经出现 $4$ 个 $xp$ 的形式，且 $(p,x)$ 在 $a,b$ 中出现次数相同，要使得 $px$ 和 $xp$ 在 $a,b$ 中相差不超过 $2$，那么必然存在一组对应的 $px$ 存在，那么总操作次数不超过 $2n$，每次暴力查找，复杂度 $\mathcal{O}(n^2)$。

或者考虑连边 $(a_i,a_{i+1})$，用欧拉回路做即可，实现差不多，都很简单。

类似方法：CF1458 D

```cpp
#include <bits/stdc++.h>
#define file_in(x) (freopen(#x".in", "r", stdin))
#define file_out(x) (freopen(#x".out", "w", stdout))
#define ll long long
#define vi vector
#define pb push_back
#define db double
#define pr pair <int, int>
#define mk make_pair
#define fi first
#define se second
#define lb(x) (x & (-x))

using namespace std;

char _c; bool _f; template <class T> void IN(T &x) {
  _f = x = 0; while (_c = getchar(), !isdigit(_c)) {if (_c == '-') _f = 1;}
  while (isdigit(_c)) {x = x * 10 + _c - '0', _c = getchar();} if (_f) x = -x;
}

template <class T> void _write(T x) {
  if (x < 0) return putchar('-'), _write(-x), void();
  if (x > 9) _write(x / 10);
  putchar('0' + x % 10);
}
template <class T> void write(T x) {_write(x), putchar('\n');}
template <class T> void write_s(T x) {_write(x), putchar(' ');}
template <class first, class... rest> void write(first fir, rest... res) {
  write_s(fir), write(res...);
}

#define debug(...) (_debug(#__VA_ARGS__, __VA_ARGS__))
template <class T> void _debug(const char *format, T x) {
  cerr << format << " = " << x << endl;
}
template <class first, class... rest>
void _debug(const char *format, first fir, rest... res) {
  while (*format != ',') cerr << *format++;
  cerr << " = " << fir << ',', _debug(format + 1, res...);
}

bool START;

const int N = 505;

int t_c, n, a[N], b[N], p[N];
vi <pr> va, vb;

bool END;

bool chk() {
  if (a[1] != b[1] || a[n] != b[n]) return 1;
  for (int i = 0; i < n - 1; ++i) if (va[i] != vb[i]) return 1;
  return 0;
}

void opa(int l, int r) {
  va.pb(mk(l, r));
  for (int i = 1; 2 * i <= r - l + 1; ++i) swap(a[l + i - 1], a[r - i + 1]);
}

void opb(int l, int r) {
  vb.pb(mk(l, r));
  for (int i = 1; 2 * i <= r - l + 1; ++i) swap(b[l + i - 1], b[r - i + 1]);
}

signed main() {
  IN(t_c);
  while (t_c--) {
    IN(n), va.clear(), vb.clear();
    for (int i = 1; i <= n; ++i) IN(a[i]);
    for (int i = 1; i <= n; ++i) IN(b[i]);
    for (int i = 1; i < n; ++i) {
      va.pb(mk(min(a[i], a[i + 1]), max(a[i], a[i + 1])));
      vb.pb(mk(min(b[i], b[i + 1]), max(b[i], b[i + 1])));
    }
    sort(va.begin(), va.end()), sort(vb.begin(), vb.end());
    if (chk()) {puts("NO"); continue;}
    va.clear(), vb.clear(), puts("YES");
    for (int i = 1; i < n; ++i) {
      int x = a[i], y = a[i + 1], z = b[i + 1];
      bool fl = 0;
      for (int j = i + 1; j < n; ++j) if (a[j] == z && a[j + 1] == x) {opa(i, j + 1), fl = 1; break;}
      if (fl) continue;
      for (int j = i + 1; j < n; ++j) if (b[j] == y && b[j + 1] == x) {opb(i, j + 1), fl = 1; break;}
      if (fl) continue;
      for (int j = 0; j <= n; ++j) p[j] = 0;
      for (int j = i + 1; j < n; ++j) if (a[j + 1] == x) p[a[j]] = j + 1;
      for (int j = i + 1; j < n; ++j) if (b[j + 1] == x && p[b[j]]) {opa(i, p[b[j]]), opb(i, j + 1); break;}
    }
    write((int)va.size() + vb.size());
    for (auto x : va) write(x.fi, x.se);
    reverse(vb.begin(), vb.end());
    for (auto x : vb) write(x.fi, x.se);
  }
  return 0;
}
```

---

## 作者：ZillionX (赞：3)

# Description

给定序列 $A,B$，若 $A_i = A_j$ ，则可以对 $A_{[i,j]}$ 进行翻转操作，求使得 $A=B$ 且满足操作次数 $\le n^2$ 的任一操作方案，若无解则输出 ``NO``。

$n \le 500$，时限 1s。

# Solution

观察题目中翻转操作的性质，我们首先断言：

- $A,B$ 首尾相同

- $A,B$ 中由相邻无序点对构成的可重集完全相同

这是题目有解的充要条件。

由于翻转操作不改变首尾点对和点对间的相邻关系，因此该条件的必要性显然成立。

接下来，我们尝试构造一种方案，来证明题目的充分性。

考虑对 $A,B$ 同时执行翻转操作，由此得到一个中间状态使得 $A=B$，然后将对 $B$ 的操作倒序输出，得到一种合法方案。

注意到翻转操作有可能破坏前面已经匹配上的一部分序列，使题目变得极不可做。不妨固定 $A_{[1,i-1]}=B_{[1,i-1]}$，尝试进行翻转操作使得 $A_i=B_i$，从而确保操作的顺序性。

![](https://cdn.luogu.com.cn/upload/image_hosting/gm6rhn8c.png)

如上图，我们约定红色为已匹配的部分，蓝色为未匹配的部分，黄色为我们需要翻转的部分。

若未匹配的部分存在 $a_j=b_i, a_{j+1}=a_{i-1}$，我们显然可以对 $[i-1,j+1]$ 执行翻转操作使得 $a_i=b_i$。对于 $B$ 中也有类似的情况。

若此时仍然不能找到一种操作方案，必然是下图中的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/vtlg8p0q.png)

此时，由于前面我们断言的充要条件：$A,B$ 中由相邻无序点对构成的可重集完全相同，在 $A,B$ 中必然有一对完全相同的点对以 $(x,a_{i-1})$ 的形式出现。我们将其在 $A,B$ 中的区间分别翻转即可。

可以发现这样构造出来的操作次数必然 $<2n$，满足题目要求。

至此我们就在就在 $\mathcal O(n^2)$ 的时间复杂度下完成了本题。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
int T,n,a[N],b[N],md1[N],md2[N];
multiset<pair<int,int> > s,t;
vector<pair<int,int> > ans[2];
void rev(int l,int r,bool fl) {
	if (!fl) reverse(a+l,a+r+1);
	else reverse(b+l,b+r+1);
	ans[fl].push_back(make_pair(l,r));
}
int main() {
	scanf("%d",&T);
	while (T--) {
		ans[0].clear(),ans[1].clear();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<=n;i++) scanf("%d",&b[i]);
		if (a[1]!=b[1] || a[n]!=b[n]) {
			printf("NO\n");
			continue;
		}
		s.clear(),t.clear();
		for (int i=1;i<n;i++) {
			s.insert(make_pair(min(a[i],a[i+1]),max(a[i],a[i+1])));
			t.insert(make_pair(min(b[i],b[i+1]),max(b[i],b[i+1])));
		}
		multiset<pair<int,int> >::iterator p1=s.begin(),p2=t.begin();
		bool fl=1;
		while (p1!=s.end() && p2!=t.end()) {
			if ((*p1)!=(*p2)) {
				fl=0;
				break;
			}
			p1++,p2++;
		}
		if (!fl) {
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		for (int i=2;i<n;i++)
			if (a[i]==b[i]) continue;
			else {
				bool fl=0;
				for (int j=i;j<n;j++)
					if (a[j]==b[i] && a[j+1]==a[i-1]) {
						rev(i-1,j+1,0);
						fl=1;break;
					}
				if (fl) continue;
				for (int j=i;j<n;j++)
					if (b[j]==a[i] && b[j+1]==b[i-1]) {
						rev(i-1,j+1,1);
						fl=1;break;
					}
				if (fl) continue;
				memset(md1,0,sizeof(md1));
				memset(md2,0,sizeof(md2));
				for (int j=i+2;j<=n;j++)
					if (a[j]==a[i-1]) md1[a[j-1]]=j;
				for (int j=i+2;j<=n;j++)
					if (b[j]==b[i-1]) md2[b[j-1]]=j;
				for (int j=1;j<=n;j++)
					if (md1[j] && md2[j]) {
						rev(i-1,md1[j],0);
						rev(i-1,md2[j],1);
						break;
					}
			}
		printf("%d\n",ans[0].size()+ans[1].size());
		for (auto v:ans[0]) printf("%d %d\n",v.first,v.second);
		reverse(ans[1].begin(),ans[1].end());
		for (auto v:ans[1]) printf("%d %d\n",v.first,v.second);
	}
	return 0;
}
```


---

## 作者：老莽莽穿一切 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16460338.html)

---

[**CF link**](https://codeforces.com/problemset/problem/1698/F)

[**你谷 link**](https://www.luogu.com.cn/problem/CF1698F)

一道思路非常奇妙的题，当然如果你不考虑证明无脑上也可以通过直觉把这道题给过了。

首先我们考虑这种构造一组解的题目，肯定是第一步找到判定是否有解的**充要条件**，然后再使用一种满足过程中充要条件不变的系统化求解，即如果充要条件满足，则通过这一种过程，一定能构造出一组解，否则不行。

那么就按部就班来考虑充要条件，首先思考这个翻转操作过程中不变的是什么，是相邻点对的集合，即原来存在一组**值**在位置上相邻，则翻转完后依然会相邻，因为翻转的两端是相同的，那么我们可以大胆猜想，是否只要相邻点对的集合相同，就一定有解呢？已经非常接近了，还有一个非常浅显的条件，就是首尾相同，这样是否就一定正确呢？可以尝试证明。

这里需要一些思想的火花，非常奇妙地，我们考虑一个很少用到的模型——欧拉路模型。

我们将给定的数组看成一条欧拉路，将每个值作为节点，相邻的两个值之间看成一条边，那么上面的相邻点对的集合相同就等价于图的形态相同，然后翻转操作等价于找到一个环路径将其翻转，证明过程就变成给定两条欧拉路，问是否能通过对环路径进行翻转使两路径相同，首先欧拉路的起点和终点必须是相同的，对应上面的首尾相同，否则显然一定可以可以构造的，构造方法即后面讲到的本题的构造方法。

我们顺序对 $a$ 数组进行操作，使其从前往后慢慢变成 $b$ 数组，那么考虑每遇到一个 $a_i\ne b_i$，此时一定满足 $\forall k\in[1,i)\cap\mathbb Z,\ a_k=b_k$，那么我们考虑在不破坏前面的情况下将 $a_i$ 变换成 $b_i$，如果后面存在一个 $j$ 满足 $a_j=b_i,a_{j+1}=b_{i-1}$，显然我们可以将 $[i-1,j+1]$ 区间反转，至于之后部分，因为之后的部分依然满足边集相同，所以我们可以利用类似数学归纳法的思想去解决这个问题，因为边集相同，所以 $b_{i-1}$ 和 $b_i$ 之间一定有边，那么既然在 $a$ 中不存在一组 $a_j=b_i,a_{j+1}=b_{i-1}$，那肯定存在至少一个 $j$ 满足 $a_j=b_i,a_{j-1}=b_{i-1}$，一个非常显然地思路是找到一组 $u,v$ 满足 $a_u=a_v,u\in(i,j],v\in(j,n]$，然后翻转区间 $u,v$，那么同时 $a_{j-1}$ 和 $a_j$ 之间的位置关系就会反过来，最后就可以直接像上一种情况一样直接翻转，在图中，这种操作对应找一个包含这条边的环，并将环翻转，那么问题转变成这样一个环存不存在，事实上一定是存在的，欧拉路上不在环上的边只可能在从起点到终点的一条链上，假设这条边出现在链上（显然这条边只能出现一次，否则必然成环），那么这条边将整张图分成不相交的两个部分，分别包含起点和终点，因为两张图的形态相同，所以两边形态分别相同，而与起点相连的部分路径构造完毕，两条路径的端点都应该在这条边上，那我们根本就不需要去操作了，与实际情况不符，我们就自然地排除了这种情况。

那么讲完了原理，实际实现上更为简单，我们可以直接构造，刚刚我们发现了我们构造出图的方式是充要的，那么如果构造过程中发现无法构造，就可以直接判断无解，同时构造过程中有几个特点，首先，在第二种情况下，即需要找一个 $j$ 满足 $a_j=b_i,a_{j-1}=b_{i-1}$，若有多个 $j$ 满足要求，我们只要直接找第一个就好了，证明可以用上面的结论，其实还有更加简单的办法，如果有多个 $j$ 满足要求，则可以直接去下一个 $j$，设为 $j'$，满足 $a_{j'-1}=a_{j-1}$，可以直接用这个 $j'$ 将我们的第一个 $j$ 翻转，构造答案。

[代码](https://codeforces.com/contest/1698/submission/163329147)并没有想象中那么复杂，时间复杂度是 $\mathcal O\left(n^3\right)$，瓶颈是要找到一组 $u,v$ 来翻转。

---

## 作者：Otomachi_Una_ (赞：1)

首先注意到，每次操作后，$\{a_i,a_{i+1}\}$ 的数量是不变的，$a_1,a_n$ 也是不变的。打表或者感性理解容易证明这时充要的。

考虑构造。很简单，从前往后，假设 $i$ 是最小的 $a_i\neq b_i$，显然 $i\geq 2$。那么考虑因为因为存在 $(b_i,b_{i+1})$，所以 $a_i,a_{i+1},\dots,a_{n}$ 肯定存在相邻两个数 $(a_x,a_{x+1})$ 是 $(b_i,b_{i+1})$ 或者 $(b_{i+1},b_i)$。

如果是 $(b_{i+1},b_i)$ 那么反转 $(i-1,x+1)$ 即可。否则先随便找个包含 $(x,x+1)$ 的先反转一下。然后再跟上面一样即可。

只需要 $2n$ 次操作即可。

---

## 作者：Amano_Sei (赞：1)

我们可以发现每次变换首尾和相邻元素组成的无序数对是不会变的，所以这一条件必要性显然，尝试证明充分性。

首先我们给出形式化的充要条件：

- $a_1 = b_1, a_n = b_n$
- $\left[\left\{a_i, a_{i+1}\right\}|1\leq i< n\right] = \left[\left\{b_i, b_{i+1}\right\}|1\leq i< n\right]$

我们可以用归纳来证明充分性。

首先 $n=1$ 时显然，假设 $n\leq m$ 时都成立，下面证明 $n=m+1$ 时也成立。

- 当 $a_2 = b_2$ 时，我们可以删去 $a_1$ 和 $b_1$，$a$ 和 $b$ 剩下的 $m$ 个元素依然满足条件，由假设得知成立。

- 当 $a_2\neq b_2$ 时，由条件可知一定存在一个 $i\geq 2$ 有 $\left\{a_i, a_{i+1}\right\}=\left\{b_1, b_2\right\}$。

  - 当 $a_{i+1}=b_1$ 时，那么一定有 $a_i=b_2$。我们可以简单地对 $[a_1,...,a_{i+1}]$ 进行变换，并且在变换后删去 $a_1$ 和 $b_1$ 也满足条件，由假设得知成立。

  - 当 $a_{i+1}\neq b_1$ 时，那么一定有 $a_{i+1}=b_2$ 和 $a_i=b_1$。[官方题解](https://codeforces.com/blog/entry/104310)中直接表示 $\left\{a_1,...,a_i\right\}\cap \left\{a_{i+1},...,a_n\right\}\neq\varnothing$ 是显然的，我们这里尝试反证。假设 $\left\{a_1,...,a_i\right\}\cap \left\{a_{i+1},...,a_n\right\}=\varnothing$，那么一定有 $\left[a_{i+1},...,a_n\right]$ 这些数只有 $a_{i+1}$（$b_2$）和 $a_i$（$b_1$）这个值有且只有一次相邻，其余的数和 $\left\{a_1,...,a_i\right\}$ 这些数都不相邻。所以对于任意的 $j\geq 2$ 都有 $b_j\in \left\{a_{i+1},...,a_n\right\}$，又由于 $a$ 和 $b$ 中数的出现次数是相同的，所以矛盾。所以 $\left\{a_1,...,a_i\right\}\cap \left\{a_{i+1},...,a_n\right\}\neq\varnothing$，我们可以选择两边相同的元素进行变换后，再把从 $a_1$ 到 “$a_i$ 新换到的位置” 进行变换，并且在变换后删去 $a_1$ 和 $b_1$ 也满足条件，由假设得知成立。

综上，得证。


---

## 作者：lfxxx (赞：0)

好题。

通过对操作的观察和手玩，你感觉到这个操作貌似不会改变数代表的颜色之间的相邻关系，于是你可以把每个颜色建点，然后 $a_i \to a_{i+1}$，你发现操作形如将一个环上的边全部取反，于是你可以知道能把 $a$ 变成 $b$ 的一个必要条件是 $a_1=b_1,a_n=b_n$ 并且将两个数组建图后，将边视作无向边后两个图相同。

考虑说明这个条件同时是充分的，我们直接来构造说明。

考虑假若现在 $a_i=x,a_{i+1}=y$ 而 $b_i=x,b_{i+1}=z$，并且前 $i-1$ 位上 $a=b$，假若后面存在一个 $a_p=z,a_{p+1}=x$ 那直接操作 $[i,p+1]$ 即可，否则后面一定存在若干 $a_q=x,a_{q+1}=z$，我们考虑操作一个 $a_l=a_r=c$ 并且 $[l,r]$ 包含了 $[q,q+1]$，假若这样的区间不存在则会产生矛盾，导出矛盾可以考虑这样一个事情，按照序列 $a$ 建立出来的图一定包含了 $x \to y \to x \to z$ 的路径，按照序列 $b$ 建立出来的图一定包含 $x \to z \to x \to y$ 的路径，由于两个图将边时为无向边后相同，所以这个无向图上一定存在包含了 $x,y$ 的环与包含了 $x,z$ 的环，考虑序列 $a$ 在抵达点 $z$ 之前经过的包含 $x,z$ 的环上的边，发现只要没有访问完所有边（如果访问完了就会访问一次 $z$）环上一定存在一个点 $w$ 满足经过的路径行如 $x \to y \to s \to w \to x \to z$，并且抵达 $z$ 后一定还会经过没有经过的边 $d \to w$，也就是整个路径行如 $x \to y \to s \to w \to x \to z \to d \to w$，那么两个 $w$ 之间包含了 $x \to z$。如果访问完了那么路径 $x \to y \to z \to x \to z$ 也满足两个 $z$ 之间包含了 $x \to z$，故导出了矛盾。

顺着这个证明思路，直接从前往后暴力构造即可做到 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector< pair<int,int> > opt;
bool solve(int a[],int b[],int n,int pos){
    if(pos==n) return true;
    if(a[pos]==b[pos]) return solve(a,b,n,pos+1);
    else{
        if(pos==0) return false;
        for(int i=pos+1;i+1<n;i++){
            if(a[i]==b[pos]&&a[i+1]==b[pos-1]){
                reverse(a+pos,a+i+1);
                opt.push_back(make_pair(pos,i+2));
                return solve(a,b,n,pos+1);
            }
        }
        vector<int> vis;
        vis.resize(n);
        for(int i=pos;i+1<n;i++){
            if(a[i]==b[pos-1]&&a[i+1]==b[pos]) vis[i]=1;
        }
        for(int i=1;i<n;i++) vis[i]+=vis[i-1];
        for(int i=pos-1;i<n;i++){
            bool flag=false;
            for(int j=i+1;j<n;j++){
                if(a[i]==a[j]&&vis[i]!=vis[j-1]){
                    reverse(a+i,a+j+1);
                    opt.push_back(make_pair(i+1,j+1));
                    flag=true;
                    break;
                }
            }
            if(flag==true) break;
        }
        for(int i=pos+1;i+1<n;i++){
            if(a[i]==b[pos]&&a[i+1]==b[pos-1]){
                reverse(a+pos,a+i+1);
                opt.push_back(make_pair(pos,i+2));
                return solve(a,b,n,pos+1);
            }
        }
        return false;
    }
}
void work(){
    int n;
    cin>>n;
    opt.clear();
    int a[501],b[501];
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    if(solve(a,b,n,0)==true){
        cout<<"YES\n";
        cout<<opt.size()<<'\n';
        for(pair<int,int> now:opt) cout<<now.first<<" "<<now.second<<'\n';
    }else{
        cout<<"NO\n";
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
9
3 3 3 3 3 4 1 3 3
3 3 3 3 4 1 3 3 3
*/
```

---

