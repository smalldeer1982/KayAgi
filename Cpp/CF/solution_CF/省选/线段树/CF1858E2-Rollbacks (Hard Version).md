# Rollbacks (Hard Version)

## 题目描述

This is a hard version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1, 1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# 题解

## 作者：CSP_Sept (赞：10)

## 题意

维护一个初始为空的序列 $a$，支持以下操作：

- $\texttt{+ }x$：在序列末端插入 $x$；
- $\texttt{- }k$：在序列末端删除 $k$ 个数（$k$ 不超过当前序列长度）；
- $\texttt{?}$：查询序列中不同的数字个数；
- $\texttt{!}$：撤回前一个 $\texttt +/\texttt -$ 操作。

$q$ 次操作，强制在线，$1\le q,x\le 10^6$，询问操作不超过 $10^5$。

## 解法

**本题解含有 $O(q\log q)$ 做法与 $O(q)$ 做法。**

经典地，我们用 set 维护所有数字的出现的所有位置，更新时只需要查询其首位即可。

这样我们可以轻松实现 $\texttt +$ 操作。

为了实现 $\texttt -$ 操作，我们引入序列 $A$，使得序列 $A$ 的前 $l$ 位恰好为序列 $a$（$l$ 为序列 $a$ 此时的长度）。这样一来，我们更新时直接将 $l$ 更改为 $l-k$ 即可。

这样做同样是为了方便进行 $\texttt !$ 操作。因为我们实际上保留了 $1\sim l_{\max}$ 的所有信息，足以进行回溯。

对于 $\texttt !$ 操作，我们使用 stack 存储所有操作，并尝试逆向地进行还原，具体情况与上面的 $\texttt +/\texttt -$ 操作思路一致。

**特别地，对于 $\texttt +$ 操作，我们需要存储原来的 $A_{l'}$ 而不是 $x$。这是容易理解的。**

至于答案的更新，我们在所有元素**第一次出现的位置**标记为 $1$，这个是已经维护过的。

那么 $\texttt ?$ 操作只需要输出该数组在 $[1,l]$ 上的区间和即可。

至此，我们需要一个可以支持单点修改、查询区间和的数据结构。拉一个树状数组即可。

时间复杂度 $O(q\log q)$。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>

#define N 1000010
#define M 1000000
#define ll long long
using namespace std;

inline ll rd(){
	char c;
	bool flag = 0;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			flag = 1;
	ll res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + c - '0';
	return flag ? -res : res;
}

int q, l = 0;
int a[N], c[N];

set <int> s[N];

void add(int x, int y){
	for( ; x <= M ; x += x & -x) c[x] += y;
}
int query(int x){
	int ans = 0;
	for( ; x ; x -= x & -x) ans += c[x];
	return ans;
}

struct lst{
	int st, x;
};

lst init(char op, int x){
	lst t;
	t.st = (op == '+'), t.x = x;
	return t;
}

vector <lst> oper; 

int main(){
	memset(a, -1, sizeof(a));
	q = rd();
	while(q--){
		char op; int x;
		scanf("\n%c", &op);
		if(op == '+'){
			x = rd(); ++l;
			if(a[l] != -1){
				if(s[a[l]].size()){
					add(*s[a[l]].begin(), -1);
					s[a[l]].erase(l);
				}
				if(s[a[l]].size()) add(*s[a[l]].begin(), 1);
			}
			oper.push_back(init(op, a[l]));
			a[l] = x;
			if(x != -1){
				if(s[x].size()) add(*s[x].begin(), -1);
				s[x].insert(l);
				add(*s[x].begin(), 1);
			}
		}
		else if(op == '-'){
			x = rd(); l -= x;
			oper.push_back(init(op, x));
		}
		else if(op == '?'){
			printf("%d\n", query(l));
			fflush(stdout);
		}
		else{
			lst last_alt = oper.back(); oper.pop_back();
			if(last_alt.st){
				int t = last_alt.x;
				if(a[l] != -1){
					if(s[a[l]].size()){
						add(*s[a[l]].begin(), -1);
						s[a[l]].erase(l);
					}
					if(s[a[l]].size()) add(*s[a[l]].begin(), 1);
				}
				a[l] = t;
				if(t != -1){
					if(s[t].size()) add(*s[t].begin(), -1);
					s[t].insert(l);
					if(s[t].size()) add(*s[t].begin(), 1);
				}
				--l;
			}
			else l += last_alt.x;
		}
	}
	return 0;
}
```

## 优化

虽然上述代码已经可以通过，但是考虑优化之。

逐个解决瓶颈：

- **树状数组**：可以用前缀和替代。容易发现是可行的；
- **维护各个元素出现的位置**：我们发现改变一个元素第一次出现的位置，必然伴随着一个当前已知位置该元素的更新或该元素的彻底删除。据此可以只用一个数组 $pos$ 代替上述题解中提出的 set 进行维护。

据此，我们得到时间复杂度 $O(q)$ 的做法。代码从略。

___

**2023.08.17** 修正一处笔误。

---

## 作者：_•́へ•́╬_ (赞：5)

## 思路

直接上主席树。

一棵记哪些位置上的数是第一次出现，用来回答询问。

一棵记哪些数字出现过。

一棵记每个位置是哪次操作加入的，用来对付删除操作。

## [code](https://codeforces.com/contest/1858/submission/218958301)

MLE。

## 优化

第一棵树就是搞笑的。可以直接记答案。

第二棵树只记 01，可以底层分块，就是区间长度 $\leq 32$ 时直接把指针当 `bitset` 用。

第三棵树，因为每个操作只被撤销一次，但可以删除再加入多次，所以可以写一个栈维护。别用 `vector`，用链式前向星。

## [code](https://codeforces.com/contest/1858/submission/218982989)

---

## 作者：Eznibuil (赞：3)

与 Easy Version 的区别在于在线。

显然有一个朴素的想法，每个数出现的最小位置计数，前缀和即可。

于是以 $O(1)$ 每修改解决了不带回滚的问题。

现在来带上回滚，快速撤销第一个操作是显而易见的，问题在于第二个操作的撤销。

考虑操作所形成的操作树，快速撤回到对应节点是可以的。这时候暴力跳更新即可做到 $O(q^2)$。

但是没必要建树，正如官方题解所说，存一个数组来代表树即可。然后把操作时 $a$ 序列的大小存进去，这样只需要一个维护一个当前深度的最后一个数即可，撤销一操作时直接把数组尾部砍掉。

现在的问题是维护一个数出现最小位置。发现只要超出当前大小即可不管，而超过当前大小的都可以保留在数组内，无需反复删除添加。但是要注意占位问题，一个最小位置被占后应重置为 $+\infty$。于是可以做到 $O(1)$ 撤销第二个操作。

总 $O(q)$。
```cpp
#include<stdio.h>
int le,e[1000001],p[1000001],la[1000001],s[1000001],ap[1000001],lrb;
struct rollback
{
	int p,la,s,ape,apela;
}rb[1000001];
int main()
{
	int q,n=0;
	scanf("%d",&q);
	for(int i=0;i<1000001;i++)
		ap[i]=1e9;
	while(q--)
	{
		char o[3];
		scanf("%s",o);
		if(o[0]=='+')
		{
			scanf("%d",e+le),rb[lrb++]=rollback{p[le],la[n],s[le],ap[e[le]],ap[e[la[n]]]};
			if(ap[e[la[n]]]==n)
				ap[e[la[n]]]=1e9;
			s[le]=n?s[la[n-1]]:0,p[le]=n,la[n]=le;
			if(ap[e[le]]>n)
				ap[e[le]]=n,s[le]++;
			le++,n++;
		}
		else if(o[0]=='-')
		{
			int k;
			scanf("%d",&k),n-=k,rb[lrb++]=rollback{-1,k,0,0,0};
		}
		else if(o[0]=='!')
			if(~rb[lrb-1].p)
				lrb--,n--,le--,p[le]=rb[lrb].p,la[n]=rb[lrb].la,s[le]=rb[lrb].s,ap[e[le]]=rb[lrb].ape,ap[e[la[n]]]=rb[lrb].apela;
			else
				n+=rb[--lrb].la;
		else
			printf("%d\n",n?s[la[n-1]]:0),fflush(stdout);
	}
	return 0;
}
```

---

## 作者：RockyYue (赞：2)

我们要查询的是当前序列中不同数的个数，且加入和删除一直是在序列末端进行的，这启示我们只需要记录在序列中位置最靠前的每种数的位置。

由此衍生出一些想法：
- 对于加入操作：第一次出现的数，其贡献为 $1$，否则为 $0$，记 $fir_i$ 为 $i$ 在序列中第一次出现的位置。
- 对于查询操作：维护序列长度 $len$，查询时树状数组求和即可。
- 对于删除操作：直接在序列长度记录改变即可。
- 对于撤回操作：
	- 记录 $preop_i,prelen_i$ 为第 $i$ 次操作为撤回（```!```）时要撤回的操作类型（```'+'/'-'```）和撤回后的长度。
	- 若撤回的操作为加入（```'+'```）且这次操作加入的数是第一次出现，同时撤回其贡献。

代码如下（温馨提示：仅供理解上文描述，请勿参考）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, Q = 1e6 + 5;
int c[N];
void upd(int x, int v) {
	for (; x < N; x += (x & -x)) c[x] += v;
}
int qry(int x) {
	int res = 0;
	for (; x; x -= (x & -x)) res += c[x];
	return res;
}
int fir[N];
int prelen[Q], add[Q]; char preop[Q];	// add[i]: 第i次操作加入的数（如果操作不是加入，无意义）
signed main() {
	int q; cin >> q;
	int len = 0;
	for (int i = 1; i <= q; ++i) {
		char op; int x; cin >> op;
		if (op == '+') {
			cin >> x;
			++len;
			if (fir[x] == 0 || fir[x] >= len) fir[x] = len, upd(len, 1);
		} else if (op == '-') {
			cin >> x;
			len -= x;
		} else if (op == '?') {
			cout << qry(len) << '\n';
		} else {
			len = prelen[i];
			if (preop[i] == '+' && prelen[i] + 1 == fir[add[prelen[i] + 1]]) upd(add[prelen[i] + 1], -1);
		}
		if (op == '+' || op == '-') preop[i + 1] = op, prelen[i + 1] = (op == '+' ? len - 1 : len + x);
		else if (op == '?') preop[i + 1] = preop[i], prelen[i + 1] = prelen[i];
		else preop[i + 1] = preop[len], prelen[i + 1] = prelen[len];
		add[i] = x;
	}
	return 0;
}
```

发现样例就不能通过。原因在于删除操作（```'-'```）的处理太过简单，导致如果后续操作通过不断加入恢复原来的长度，这一部分删去的数的贡献也会被计入，如样例 1 中：
- 当前序列为 ```1 2 3```。
- 删除后两个，序列剩余 ```1```。
- 加入一个 ```1```，序列为 ```1 1```。
- 此时 ```len=2```，若查询，会得到 ```2```，这里包括了初始序列中 ```2``` 的贡献，是错误的。

这启示我们在加入元素时要清除之前在这个位置上的元素的贡献再加入当前元素贡献。

同理，在撤回加入操作时也需要先清空当前这个位置上元素的贡献再加上操作前这个位置上元素的贡献。

具体措施为：
- 维护序列上具体元素的值 $a_{1\dots len}$。
- 清除贡献时，如果这是该元素第一次出现，需要把 $fir$ 数组上值更新到第二个，那么就不能只维护一个 $fir$，而是对于每个值维护一个 ```set```，表示其所有出现位置。

从另一篇题解中学到，原来不需要记录那么多的 $pre$ 数组，只需要开一个栈维护之前的操作即可，写起来更为优美。

具体实现时注意，当你改变一个位置上值计算贡献时：
- 判断改变前/后这个位置是否为空，防止 RE。
- 对于改变前/后两个值，都要先清除贡献后加入贡献，因为 ```set``` 中第一个元素（即 $fir$）可能会在 ```set``` 改变后随之改变，而贡献只会记录第一次出现。

这两点具体见代码中 upd 部分。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct Op {
	char op; int pos, fr, x;
};
stack<Op> o;
int a[N], len = 0, c[N];
int lowbit(int x) { return x & -x; }
void Upd(int x, int v) {
	for (; x < N; x += lowbit(x)) c[x] += v;
}
int qry(int x) {
	int res = 0;
	for (; x; x -= lowbit(x)) res += c[x];
	return res;
}
set<int> occur[N];
void add(int x) { Upd(*occur[x].begin(), 1); }
void del(int x) { Upd(*occur[x].begin(), -1); }
void upd(int pos, int to) {
	int fr = a[pos]; a[pos] = to;
	set<int> &f = occur[fr], &t = occur[to];
	if (f.size()) {
		del(fr), f.erase(pos);
		if (f.size()) add(fr);
	}
	if (t.size()) del(to);
	t.insert(pos), add(to);
}
signed main() {
	int q; cin >> q;
	while (q--) {
		char op; int x; cin >> op;
		Op t;
		if (op == '+') {
			cin >> x;
			t.op = '+', t.pos = ++len, t.fr = a[len];
			o.push(t), upd(len, x);
		} else if (op == '-') {
			cin >> x;
			t.op = '-', t.x = x;
			o.push(t), len -= x;
		} else if (op == '!') {
			t = o.top(); o.pop();
			if (t.op == '+') upd(t.pos, t.fr), --len;
			else len += t.x;
		} else {
			cout << qry(len) << '\n';
		}
	}
	return 0;
}
```

---

## 作者：LGyxj (赞：2)

来一发树分块的题解。

做完 Easy Version 就一直在想操作树。

建树过程很显然，不再赘述。

我们实际上要求的就是某个点到根的路径上的不同值的数量，这是一条链上的查询，所以考虑树分块，也就是在树上放一些关键点，每个关键点维护到根的 bitset 。

大概就是对于每个点，如果它上面有 $2B$ 个点不是关键点，那么把它的 $B$ 层祖先设为关键点，并更新子树。

新建一个关键点的过程就是暴力跳父节点，然后找到一个已经存在的关键点，取或即可。

查询的过程类似，但是不能对每个询问都新建 bitset ，这样显然会 TLE ，所以先找到已经存在的关键点祖先，更新已经存在的 bitset ，并且记录哪些位被修改了，查询结束后暴力撤销即可。

可以证明树中只会有 $O(\frac n{B})$ 个关键点，因为每次新建关键点的时候，一定存在 $B$ 个点不是关键点，那么令 $B = O(\sqrt q)$ 。

这样就可以做到 $O(\frac {q \sqrt q}{\omega} + m \sqrt q)$ 。

实测并不很慢。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <bitset>
#include <vector>
using namespace std;
const int N = 1e6 + 5, M = 20, K = 1000, P = 1005;
int m, tot, tx, cur;
int fa[M][N], val[N];
int disx[N], tt;
bitset<N> bs[P], cnt;
int vis[N], ansp[P];
vector<int> tc[N];
void proc(int x) {
	int p = x; ++ tx;
	while (vis[x] == -1) {
		bs[tx][val[x]] = 1;
		x = fa[0][x];
	}
	vis[p] = tx;
	bs[tx] |= bs[vis[x]];
	ansp[tx] = bs[tx].count();
}
int get(int x) {
	static int stk[N];
	int p = x, q = disx[p], tt = 0;
	for (int i = 0; q; ++ i, q >>= 1) (q & 1) && (p = fa[i][p]);
	int qx = ansp[vis[p]], px = vis[p];
	while (vis[x] == -1) {
		if (!bs[px][val[x]]) 
			bs[px][val[x]] = 1, stk[++ tt] = val[x], ++ qx;
		x = fa[0][x];
	}
	while (tt) bs[px][stk[tt --]] = 0;
	return qx;
}
void upd(int x) {
	for (int & y : tc[x]) {
		if (~vis[y]) continue;
		disx[y] = disx[x] + 1;
		upd(y);
	}
}
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	static int stk[N];
	cin >> m; stk[++ tt] = 0;
	memset(vis, -1, sizeof vis);
	vis[0] = 0;
	while (m --) {
		char op;
		cin >> op;
		if (op == '+') {
			int x; cin >> x;
			val[++ tot] = x;
			fa[0][tot] = stk[tt];
			stk[++ tt] = tot; tc[fa[0][tot]].push_back(tot);
			disx[tot] = disx[fa[0][tot]] + 1;
			for (int j = 1; j < M; ++ j) fa[j][tot] = fa[j - 1][fa[j - 1][tot]];
			cur = tot;
			if (disx[tot] == K << 1) {
				int px = tot;
				for (int i = 0, j = K; j; ++ i, j >>= 1) (j & 1) && (px = fa[i][px]);
				proc(px); disx[px] = 0; upd(px);
			}
		} else if (op == '-') {
			int k; cin >> k;
			for (int i = 0; k; ++ i, k >>= 1) (k & 1) && (cur = fa[i][cur]);
			stk[++ tt] = cur;
		} else if (op == '!') cur = stk[-- tt];
		else cout << get(cur) << '\n' << flush;
	}
	return 0;
}
```

---

## 作者：Leasier (赞：2)

~~卡主席树的抽象题。~~

------------

考虑没有撤销操作怎么做。

考虑维护 $a_{1 \sim N}$ 的答案 $ans_{1 \sim N}$，其中 $N$ 表示最后一次添加操作到达的下标。

设 $n$ 表示当前 $a$ 的元素个数，则：

- 添加操作：令 $n \leftarrow n + 1$，$N \leftarrow n$，考虑新加入的 $x$ 的情况。

维护时间戳 $tm_x$ 表示 $x$ 第一次在 $a$ 中何处出现，$ref_i$ 表示在最新涉及到与 $i$ 有关的历史 $a$ 中 $a_i$ 的值，$\Delta_i$ 表示在在最新涉及到与 $i$ 有关的历史 $a$ 中 $a_i$ 对答案产生的贡献。

若 $tm_{ref_n} = n$，则最近一次历史上 $a_n$ 产生了贡献，在 $n$ 处删去其此前的标记，即令 $\Delta_n \leftarrow \Delta_n - 1$。

若 $tm_x = 0$ 或 $tm_x \geq n$，则 $x$ 在目前维护的 $a_{1 \sim N}$ 中未出现，在 $n$ 处标记其产生了贡献，即令 $\Delta_{tm_x} \leftarrow \Delta_{tm_x} - 1$，$tm_x \leftarrow n$，$\Delta_n \leftarrow \Delta_n + 1$。

最后，令 $ref_n \leftarrow x$，$ans_n \leftarrow ans_{n - 1} + \Delta_n$ 即可。

- 删除操作：令 $n \leftarrow n - k$ 即可。
- 查询操作：输出 $ans_n$ 即可。

对于撤销操作，用一个栈记录修改即可。注意 $ans_n$ 的原值也要记录。

时间复杂度为 $O(q)$。

代码：
```cpp
#include <stdio.h>

int top = 0;
int stk[1000007], save1[1000007], ref[1000007], save2[1000007], tm[1000007], addition[1000007], save3[1000007], save4[1000007], ans[1000007];
char op[7];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int main(){
	int q = read(), len = 0;
	for (int i = 1; i <= q; i++){
		scanf("%s", &op[1]);
		if (op[1] == '+'){
			int x = read();
			len++;
			top++;
			stk[top] = x;
			save1[top] = ref[len];
			save2[top] = tm[ref[len]];
			if (tm[ref[len]] == len){
				addition[len]--;
				tm[ref[len]] = 0;
			}
			save3[top] = tm[x];
			if (tm[x] == 0 || tm[x] > len){
				addition[tm[x]]--;
				tm[x] = len;
				addition[len]++;
			}
			ref[len] = x;
			save4[top] = ans[len];
			ans[len] = ans[len - 1] + addition[len];
		} else if (op[1] == '-'){
			int k = read();
			len -= k;
			stk[++top] = -k;
		} else if (op[1] == '!'){
			if (stk[top] > 0){
				ans[len] = save4[top];
				ref[len] = save1[top];
				if (save3[top] == 0 || save3[top] > len){
					addition[len]--;
					tm[stk[top]] = save3[top];
					addition[save3[top]]++;
				}
				if (save2[top] == len){
					tm[save1[top]] = len;
					addition[len]++;
				}
				len--;
			} else {
				len -= stk[top];
			}
			top--;
		} else {
			printf("%d\n", ans[len]);
			fflush(stdout);
		}
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：2)

### 思路

看到有加数，减数，回滚，不同数字个数，要求在线，马上想到可持久化权值线段树。因为回滚不会回滚之前的回滚操作而只会回滚加减，因此我们要维护一个数组存储所有的加减操作，每次回滚从后面弹掉一个。我们还要维护每个状态时数列的长度 $len$，每次删除时回到最后的一个长度为 $len-k$ 的状态，回滚时删除现在这个 $len$ 的状态。

然鹅直接交会喜提 MLE，考虑优化。因为没有区间查询不同数字个数，所以只需每个版本记录一下不同数字个数即可。每次加入新的数也只需用到叶子结点是否有值这个信息，所以也可以用一个 `map` 记录。然后就可以 AC 了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int now,rt[1000010],cnt,len[1000010],g[1000010],ans[1000010];
vector<int>f[1000010];  //每个len的编号集
map<int,bool>mapp;
struct ss{
	int l,r;  //结构体只用开左右儿子
}tr[21000000];
void update(int &i,int j,int l,int r,int c){
	int mid=(l+r)>>1;
	i=++cnt;
	tr[i]=tr[j];
	if(l==r){
		if(mapp[i]==0&&mapp[j]==0){
			ans[now]++;  //用map判断是否有值
		}
		mapp[i]=1;
		return;
	}
	if(c<=mid){
		update(tr[i].l,tr[j].l,l,mid,c);
	}
	else{
		update(tr[i].r,tr[j].r,mid+1,r,c);
	}
}
int main(){
	ios::sync_with_stdio(0);
	int n,m,las=0;
	char c;
	cin>>n;
	f[0].push_back(0);  //最先len=0
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='+'){
			cin>>m;
			now++;
			ans[now]=ans[now-1];  //先复制再更新
			update(rt[now],rt[now-1],1,1e6,m);
			len[now]=len[now-1]+1;
			f[len[now]].push_back(now);
			g[++las]=now;  //记录
		}
		else if(c=='-'){
			cin>>m;
			++now;
			len[now]=len[g[las]]-m;
			ans[now]=ans[f[len[now]].back()];  //找到继承对象
			rt[now]=rt[f[len[now]].back()];
			f[len[now]].push_back(now);
			g[++las]=now;
		}
		else if(c=='!'){
			++now;
			f[len[g[las]]].erase(f[len[g[las]]].end()-1);  //删除
			las--;
			ans[now]=ans[g[las]];
			len[now]=len[g[las]];
			rt[now]=rt[g[las]];  //继承，注意回滚不用记录len
		}
		else{
			cout<<ans[now]<<"\n";
		}
	}
}
```

---

## 作者：a999999 (赞：2)

## CF1858E2 题解

### 思路

首先，只考虑插入和查询的话，我们可以发现这么一个事情：

每种数字只在它第一次被加入时对答案有贡献。

再考虑删除操作，自然会想到用主席树维护已经存在的数字，删除时将 $root_n$ 指向 $root_{n-k}$ 即可。

但是删除后再插入时会覆盖原来位置上的 $root$，影响撤销操作。

这个时候我们可以换一种思路，用树的节点来表示每个插入的数字，并在节点上记录答案。

插入操作对应为在当前节点下加一个儿子；

删除操作对应为向上跳 $k$ 步，考虑到会有新点，可以使用树上倍增；

撤销操作对应为回到上一次操作的节点处。

### 细节

使用此法最大的难点在于空间优化(主席树的空间开到了 $2\times 10^7$)。

1. 不必在主席树中储存答案，只要在 `+ x` 前查询是否有对应 $x$ 的节点就可以知道答案。

2. 在已经有对应 $x$ 的节点时可以不新增节点，直接将新节点 $root$ 赋值为旧节点的即可。

3. 用栈储存还没有上一次、上上次操作完之后队尾的节点，回滚时直接去掉栈顶即可。

### 代码

```c++
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
#define N 1000010
#define lgN 21
#define LEN 21001000
#define inf 1000000
int lc[LEN],rc[LEN],tot;
int root[N],ans[N],n;
int fa[N][lgN];
int endpos[N],top;
void add(int p,int q,int x,int l=1,int r=inf){//插入
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid){
		lc[q]=++tot;
		rc[q]=rc[p];
		add(lc[p],lc[q],x,l,mid);
	}
	else{
		rc[q]=++tot;
		lc[q]=lc[p];
		add(rc[p],rc[q],x,mid+1,r);
	}
}
bool ask(int p,int x,int l=1,int r=inf){//查询x节点是否存在
	if(!p)return 1;
	if(l==r)return 0;
	int mid=(l+r)>>1;
	return x<=mid?ask(lc[p],x,l,mid):ask(rc[p],x,mid+1,r);
}
signed main(int argc,char **argv){
//	freopen("order.in","r",stdin);
//	freopen("order.out","w",stdout);
	int T,x,t;
	char opt[4];
	scanf("%d",&T);
	while(T--){
		scanf("%s",opt);
		if(*opt=='+'){
			scanf("%d",&x);
			if(ask(root[endpos[top]],x))
				add(root[endpos[top]],root[++n]=++tot,x),ans[n]=ans[endpos[top]]+1;
			else root[++n]=root[endpos[top]],ans[n]=ans[endpos[top]];//节省空间
			fa[n][0]=endpos[top];//树上倍增
			for(int i=1;i<lgN;++i){
				fa[n][i]=fa[fa[n][i-1]][i-1];
				if(!fa[n][i])break;
			}
			endpos[++top]=n;
		}
		else if(*opt=='-'){
			scanf("%d",&x);
			t=endpos[top];
			for(int i=0;i<lgN;++i)
				if((x>>i)&1)t=fa[t][i];
			endpos[++top]=t;
		}
		else if(*opt=='!')
			top--;
		else
			printf("%d\n",ans[endpos[top]]),
			fflush(stdout);
	}
//	printf("MEM:%d",tot+top+n);
	return 0;
}
```

#### 题外话

比赛时 1：30 开，没想到树上倍增，写了主席树之后空间复杂度不对，卡住了；

用快读，空间被卡还触发了 ILE；

最后
![呜呜呜](https://cdn.luogu.com.cn/upload/image_hosting/rdc3g0k0.png)


---

## 作者：Register_int (赞：2)

纪念打的最好的一次（倒开切 E2）。

~~不用考虑离线怎么做，离线做法跟在线毫无关系。~~

先来考虑一个前置问题：给定一个序列，要求实现单点修改，前缀数颜色。强制在线。

如果没有单点修改，可以将询问转化为：有多少个数在位置 $k$ 之前出现过。我们可以记录每个颜色第一次出现的位置，插进树状数组中进行求解。加上单点修改呢？这时我们需要动态维护每个数第一次出现的位置，不妨考虑一个暴力一点的思路：维护颜色出现的所有位置，第一次出现的位置显然就在第一位。这个可以使用 `set` 轻松完成。

回到原问题，先来解决掉烦人的删除操作。可以发现，我们可以“假装删除”，也就是将序列 $a$ 的长度 $len$ 减去 $k$ 而不真正去改序列的内容。由于我们查颜色数是全局的，所以将 $[1,len]$ 这一前缀的答案输出即可。在序列末尾加的操作也可以看作 $len\leftarrow len+1$ 后单点修改 $a_{len}$ 的值。这样我们就单次 $O(\log n)$ 完成了除撤销以外的操作。

由于每次修改，变动的元素个数是 $O(1)$ 的，可以直接将这些元素存进栈内，撤销时弹出栈顶复原即可。时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int c[MAXN];

inline 
void add(int k, int x) {
	for (int i = k; i <= 1e6; i += i & -i) c[i] += x;
}

inline 
int query(int k) {
	int res = 0;
	for (int i = k; i; i &= i - 1) res += c[i];
	return res;
}

struct node {
	int k, x, len;
}; stack<node> s;

set<int> t[MAXN]; int a[MAXN], len;

inline 
void modify(int k, int x) {
	int y = a[k]; a[k] = x;
	if (x == y) return ;
	if (!t[y].empty()) {
		add(*(t[y].begin()), -1), t[y].erase(k);
		if (!t[y].empty()) add(*(t[y].begin()), 1);
	}
	if (!t[x].empty()) add(*(t[x].begin()), -1);
	t[x].insert(k), add(*(t[x].begin()), 1);
}

inline 
void undo() {
	node q = s.top(); s.pop();
	modify(q.k, q.x), len = q.len;
}

int n, k; char opt[2];

int main() {
	for (scanf("%d", &n); n--;) {
		scanf("%s", opt);
		if (*opt == '!') undo();
		else if (*opt == '?') cout << query(len) << endl;
		else {
			scanf("%d", &k), s.push({ len + 1, a[len + 1], len });
			if (*opt == '+') modify(++len, k);
			else len -= k;
		}
	}
}
```

#### bonus

仔细思考就能发现 `set` 是没有必要的。不考虑撤销，则每次修改时，由于修改的是序列末尾的元素（被删除的不会影响到前缀答案），所以每个数第一次出现的位置 **只会在从无到有后再从有到无**。暴力修改即可。

线性做法目前不会。

---

## 作者：Zimo_666 (赞：1)

## E2. Rollbacks (Hard Version)

强制在线。

不难想出如果没有回滚的话，直接用 `set` 维护每个数的出现位置，然后类似前缀和或者树状数组回答询问。

有回滚之后我们考虑维护一个 $a$ 数组，其中前面 $len_{now}$ 位是准确的，后面的都是为了回滚维护类似于之前的状态。

我们用一个栈记录回滚操作。

对于 `+` 是好用 set、树状数组维护的

对于 `-` 直接把 $a$ 数组长度改了即可。

对于 `?` 直接回答树状数组 $[1,l]$ 区间和即可。

对于 `!` 操作，如果要回滚的是 `+`，那么和正常 `+` 反过来即可，如果是 `-` 那么直接把 $a$ 数组长度改了即可。

代码还是比较好实现的，注意我们在存储栈的时候，我们对于 `+` 操作，我们需要存原来的 $a_{l'}$ 而不是 $x$，判的时候也注意判一下是不是等于初值，也就是说是不是原来就没有值，避免 `RE`。

[Code](https://codeforces.com/contest/1858/submission/232162245)

---

## 作者：_edge_ (赞：1)

介绍两种做法。

首先你需要把这个操作看成一棵树一样的，具体而言就是，`+` 相当于是给这个节点加一个叶子，`-` 就是跳到 $k$ 即祖先，`!` 回退到上一个位置，`?` 查询当前节点到他祖先的本质不同数字个数。

$k$ 级祖先可以加叶子之后处理其倍增数组。

如果是 E1 你可以直接离线，然后这棵树建出来之后用 DFS 解决当前节点的答案。

如果是 E2 你可以直接使用主席树维护当前节点的信息，但是这样做会导致你空间炸掉，所以你得实现的非常精细，不能开 `sum[x]` 表示 $x$ 这个节点里面非 $0$ 的数量，直接用是否有这个节点表示他是否存在，然后答案可以直接从祖先继承过来。

[code](https://codeforces.com/contest/1858/submission/219033789)

当然，这太不优美了，可以尝试另外一种思考方式。

接下来搬运自官方题解。

我们设一个，$a$ 是当前这个维护的序列，根据加入时间从小往大，然后 $a$ 是 $A$ 的一个前缀，先别急着说 $A$ 是啥，直接看接下来的维护。

对于一个 $a$ 序列，我们把相同的数的贡献统计在最前面那个相同的数，然后统计答案就比较方便了，可以直接利用数据结构维护。

对于 `+` 操作，我们直接在 $a$ 后面加一个数，如果 $A$ 序列在当前这个位置有值，那么直接把这个值给扔了，在树状数组上进行修改即可。

对于 `-` 操作，我们直接把 $a$ 的长度减掉就可以了，所以这里就是保证了 $a$ 是 $A$ 的前缀。

对于 `!` 操作，我们可以直接在 `+` 和 `-` 操作的时候记录当前的修改。

对于 `?` 操作，即为查询树状数组上前缀的和。

这里还需要一个 set 来维护相同数的出现位置，当然你会发现这个做法非常的暴力，很多地方都可以通过实现精细来做到更加优秀，~~但是我好像看不懂 jly 的代码~~。

代码可以参考 CF 官方题解的。

---

## 作者：Purslane (赞：1)

# Solution

被降智了，一直在思考怎么把三棵主席树的空间给降下来。如果我不往主席树那边想说不定真能两场干上 Specialist。

考虑没有 Rollback 怎么做。

我们发现，事实上重要的只有每种数第一次出现的位置。因为前面的数比后面的数更加安全。而我们在后面加数根本不会影响前面那个数是不是第一次出现，因此我们只需要在加数的时候判断这个数是否第一次出现即可。

如果是连续删掉后 $k$ 个数，我们考虑并不把他们删掉，而是记录数组的实际长度，将其减去 $k$。查询的时候只需要看前 $len$ 个数里面有多少个数是第一次出现。因此你发现这要求你用一个树状数组或者线段树去记录每个位置是否是第一次出现。这样我们能做到 $O(1)$。

如果是加一个数，我们让数组的实际长度加一。如何判断是否是第一次出现呢？我们可以记录目前我们认定的这种数出现的最早的位置，记为 $pos$。如果 $pos \ge len'$ 或者 $a_{pos} \neq v$ 就是第一次出现。这会在 $pos$ 被删掉之后第一次再加入 $v$ 发生。注意此时要修改 $pos$。大概就做完了。

总结一下我们维护了什么：

1. 当前的数组。我们实际的数组是他的一个前缀。
2. 每个位置是否是第一次出现。这实际上是一个树状数组或者线段树。
3. 每种数的目前认定的最早出现。

当我们加入一个数，分别有 $1$，$\log n$，$1$ 次修改。

我们删去一堆数，只修改一个长度。

再考虑有 Rollback 怎么做。

你发现直接记录一下你改了那些位置即可，回滚的时候暴力改回去。这样每个操作都相当于被执行了两次。而你只需要额外搞 $O(n)$ 的空间（那个修改 $\log n$ 次的树状数组其实只需要记录在哪里加的就行了）。时间 $O(n \log n)$，足以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,len,a[MAXN],lst[MAXN],tr[MAXN];
stack<vector<pair<int,pair<int,int>>>> st; //我们记录增量 
void update(int pos,int v) {while(pos<=n) tr[pos]+=v,pos+=pos&-pos;return ;}
int query(int pos) {int ans=0;while(pos) ans+=tr[pos],pos-=pos&-pos;return ans;}
void roll_back(void) {
	auto vc=st.top(); st.pop();
	for(auto v:vc) {
		int op=v.first,pos=v.second.first,val=v.second.second;
		if(op==0) len-=val;
		if(op==1) a[pos]-=val;	
		if(op==2) lst[pos]-=val;
		if(op==3) update(pos,-val);
	}
	return ;
}
int is_first(int v) { //这时候 len 应该已经修改了 
	if(lst[v]>=len||a[lst[v]]!=v) return 1;
	return 0;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	memset(lst,0x3f,sizeof(lst));
	ffor(i,1,n) {
		char ch;
		cin>>ch;
		if(ch=='+') {
			++len; int v; cin>>v;
			int flg=is_first(v);
			vector<pair<int,pair<int,int>>> vc;
			
			vc.push_back({1,{len,v-a[len]}}),a[len]=v;
			int lenv=query(len)-query(len-1);
			vc.push_back({3,{len,-lenv}}),update(len,-lenv);
			if(flg) vc.push_back({3,{len,flg}}),update(len,flg);
			
			if(flg||len<lst[v]) vc.push_back({2,{v,len-lst[v]}}),lst[v]=len;
			vc.push_back({0,{0,1}});
			st.push(vc);	
		}
		else if(ch=='-') {
			int k; cin>>k; len-=k; 
			vector<pair<int,pair<int,int>>> vc;
			vc.push_back({0,{0,-k}});
			st.push(vc);	
		}
		else if(ch=='!') roll_back();
		else {
			int ans=query(len);
			cout<<ans<<endl<<flush;	
		}
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

对于 ez version，我们发现可以使用建操作树来解决。

具体地，设 $F_i$ 表示操作 $i$ 后的序列，$f(i,k)$ 表示树上 $i$ 的 $2^k$ 级祖先。我们维护一个 $p$ 表示目前维护的序列长度。

+ 对于 `+` 操作，直接将 $f(i,0)$ 设为 $p$，因为显然是在 $p+1$ 这个位置添加 $x$。然后简单的维护 $f(i,k)$。
+ 对于 `-` 操作，由于我们已经维护了这个倍增的东西，我们直接用 $\log$ 的复杂度向前跳，跳到 $x$ 个之前。
+ 对于撤销操作，我们维护一下 `+` 和 `-` 操作的一个栈和操作 $i$ 结束后的 $p$，这样可以快速回溯到上一个 `+` 和 `-` 操作之前。
+ 对于查询操作，我们发现加减一个数字可以 $O(1)$ 维护数字种类的（类似莫队的 `void del(int x)` 和 `void add(int x)`）。

```cpp
#include <bits/stdc++.h>
#define clr() fflush(stdout);
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
const int K=25, N=1e6+5;
//#define int long long
int ret;
vector<int> e[N]; char op[N];
int cnt[N], ans[N], v[N], x[N], f[N][K], pos[N];
int Q, cq, jmp, i, k;
inline void add(int id) {if(!cnt[id]) ++ret; ++cnt[id]; return ;}
inline void del(int id) { --cnt[id]; if(!cnt[id]) --ret; }
inline void dfs(int id)
{
    if(id) add(v[id]);
    ans[id]=ret;
    for(auto nxt : e[id]) dfs(nxt); del(v[id]);
    return ;
}
stack<int> q;
signed main()
{
    scanf("%d", &Q);
    rep(i, 1, Q)
    {
        scanf(" %c", op+i);
        if(op[i]=='+')
        {
            scanf("%d", x+i);
            f[++cq][0]=jmp;
            rep(k, 1, 21) f[cq][k]=f[f[cq][k-1]][k-1];
            jmp=cq;
            v[cq]=x[i]; q.push(i);
        }else if(op[i]=='-')
        {
            scanf("%d", x+i);
            rep(k, 0, 21) if(x[i]&(1<<k)) jmp=f[jmp][k];
            q.push(i);
        }
        else if(op[i]=='!') jmp=pos[q.top()-1], q.pop();
        pos[i]=jmp;
//      puts("ok");
    }
    rep(i, 1, cq) e[f[i][0]].emplace_back(i);
    dfs(0);
    rep(i, 1, Q) if(op[i]=='?') printf("%d\n", ans[pos[i]]);
    return 0;
}
```

对于 hard version，我们发现 ez version 写的完全不适用了，因为我们是离线下来做才能保证复杂度的。

我们重新思考一下怎么做这个题，对于一个序列其颜色种类数等价于问有多少个数在这个序列中**第一次出现**。我们发现这个东西是可以维护的。

还记得刚刚的 $p$ 吗？这个东西现在依然很有用。

+ 对于 `+` 操作，我们直接在末尾 $p+1$ 处加上一个数。如果他是第一次出现则计数器加一。
+ 但是我们只是这样维护计数器会发现删除这样的操作很难实现，思考，会发现不如我们利用 `p` 实现**一种“假”删除**，考虑后面的查询操作，本质相当于问 $a_1, a_2, \cdots, a_p$ 这些数中第一次出现的数的个数。所以删除操作直接 $p\gets p-x$。为了方便查询，我们将计数器加一改为在 $p+1$ 的位置加一，查询也变成求前缀和。
+ 对于回溯操作，还是直接动 $p$，然后类似 ez version 的维护一个栈即可。
+ 对于查询操作，我们发现目前只需要解决两个问题：如何知道这个数是不是第一次出现？如何快速求前缀和？我们对每个数维护一个 `std::set` 记录其出现的情况，前缀和则直接树状数组解决就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5, Pn=1e6;
int tr[N], a[N]; int ret;
int n, Q, i, j, cnt, x;
int lsq[N], lsp[N], lsv[N]; char lsop[N];
inline void add(int x, int k)
{ while (x<=Pn) tr[x]+=k, x+=x&-x; return ;}
inline int ask(int x)
{ ret=0; while (x) ret+=tr[x], x-=x&-x; return ret;}
set<int> q[N]; char op;
inline void chg(int pos, int nxt)
{
    if(!q[a[pos]].empty())
    {
        add(*q[a[pos]].begin(), -1);
        q[a[pos]].erase(pos);
        if(!q[a[pos]].empty()) add(*q[a[pos]].begin(), 1);
    }
    if(!q[nxt].empty()) add(*q[nxt].begin(), -1);
    a[pos]=nxt; q[nxt].insert(pos);
    add(*q[nxt].begin(), 1);
}
int main()
{   int q=0;
    scanf("%d", &Q); while(Q--)
    {
        scanf(" %c", &op);
        if(op=='!') 
        {
            q=lsq[cnt];
            if(lsop[cnt]=='+') chg(lsp[cnt], lsv[cnt]);
            --cnt;
        }else if(op=='?') printf("%d\n", ask(q)), fflush(stdout);
        else if(op=='+')
        {
            scanf("%d", &x);
            ++cnt; lsq[cnt]=q; lsop[cnt]='+'; lsp[cnt]=q+1; lsv[cnt]=a[q+1]; ++q;
            chg(q, x);
        }else
        {
            scanf("%d", &x);
            ++cnt; lsq[cnt]=q; lsop[cnt]='-';
            q-=x;
        }
//      printf("%d\n", q);
//      for(int i=1;i<=q;++i) printf("%d\n", a[i]);
//      puts("");
    }
    return 0;
}
```



---

## 作者：cwfxlh (赞：0)

# [CF1858E2](https://www.luogu.com.cn/problem/CF1858E2)  

这种题完全不会啊。  

考虑这几种操作，不难发现 $+$ 和 $-$ 不是对称的，于是我们重点在于加速删除。有一种想法是把删除变成左移 $endpos$，询问区间询问，这样似乎可以优化掉删除的复杂度。    

进一步细节考虑，因为转化成了区间询问，于是我们对于每种值第一次出现的位置记一个权值 $1$，这样就可以区间求和来询问了。每种值第一次出现的位置可以用一个 set 来维护，第一关键字是权值，第二关键字是位置。对于 $+$ 操作，我们直接修改 $v_{endpos+1}$ 的值，并将 $endpos+1$，修改值的时候，序列 $01$ 权值的变化位置是 $O(1)$ 的，于是可以树状数组维护。$-$ 的回滚操作可以直接位移 $endpos$，$+$ 的回滚可以开一个栈记录下修改前的元素，改回去即可。     

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,k1,k2,k3,k4,k5,k6,k7,k8,k9;
char op;
int stk[1000003][2],tot;
int v[1000003],len;
pair<int,int>bl1;
set<pair<int,int> >apr;
int TreeAr[1000003];
int lowbit(int X){return (X&(-X));}
void modify(int wz,int val){
	for(int i=wz;i<=1000000;i+=lowbit(i))TreeAr[i]+=val;
	return;
}
int Query(int wz){
	int ret=0;
	for(int i=wz;i;i-=lowbit(i))ret+=TreeAr[i];
	return ret;
}
void del(int X,int Y){
	bl1=(*apr.lower_bound(make_pair(X,0)));
	if(bl1.second!=Y)apr.erase(make_pair(X,Y));
	else{
		modify(Y,-1);
		apr.erase(make_pair(X,Y));
		auto i=apr.lower_bound(make_pair(X,0));
		if(i!=apr.end()&&(*i).first==X)modify((*i).second,1);
	}
	return;
}
void add(int X,int Y){
	auto i=apr.lower_bound(make_pair(X,0));
	if(i==apr.end()||(*i).first>X){
		modify(Y,1);
		apr.insert(make_pair(X,Y));
		return;
	}
	else{
		if((*i).second>Y){
			modify(Y,1);
			modify((*i).second,-1);
		}
		apr.insert(make_pair(X,Y));
		return;
	}
	return;
}
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%s",&op);
		if(op=='+'){
			scanf("%d",&k1);
			stk[++tot][0]=len+1;
			stk[tot][1]=v[len+1];
			if(v[len+1]!=0)del(v[len+1],len+1);
			len++;
			v[len]=k1;
			add(k1,len);
		}
		if(op=='-'){
			scanf("%d",&k1);
			stk[++tot][0]=-1;
			stk[tot][1]=k1;
			len-=k1;
		}
		if(op=='?'){
			printf("%d\n",Query(len));
			fflush(stdout);
		}
		if(op=='!'){
			if(stk[tot][0]==-1){
				len+=stk[tot][1];
				tot--;
			}
			else{
				del(v[len],len);
				len--;
				if(stk[tot][1]!=0)add(stk[tot][1],stk[tot][0]);
				v[stk[tot][0]]=stk[tot][1];
				tot--;
			}
		}
	}
	return 0;
}
```


---

## 作者：TernaryTree (赞：0)

相对简单的 $2600$。

考虑维护每个数出现的所有位置 $P_i=\{j\mid a_j=i\}$。用 set 实现。

若问题改为查询前缀数字个数，答案即为满足 $\min\{P_i\}\le k$ 的 $i$ 个数。单点改，区间查，可以用树状数组维护之。

用栈处理 $\texttt{+/-}$ 操作。每次回退即在栈顶弹一个元素并相应地操作。

$\texttt{-}$ 操作看作是后面的询问只询问一个当前序列的前缀，后面实际上我们就不删了，因为回退可能还要用。

接下来一一讲解四种操作的具体实现。

---

### $\texttt+$ 操作：

```cpp
void insert(int x) {
	++n;
	if (a[n] != -1) {
		if ((*p[a[n]].begin()) == n) {
			add(n, -1);
			p[a[n]].erase(n);
			if (p[a[n]].size()) add(*p[a[n]].begin(), 1);
			p[a[n]].insert(n);
		}
		p[a[n]].erase(n);
	}
	s[++top] = oper('+', a[n]);
	a[n] = x;
	p[x].insert(n);
	if ((*p[x].begin()) == n) {
		add(n, 1);
		p[x].erase(n);
		if (p[x].size()) add(*p[x].begin(), -1);
		p[x].insert(n);
	}
}
```

插入一个数时，如果当前位置以前是有数的，我们首先要维护 $P$ 的性质，如果要删掉的这个数是第一个那么就去掉。如果还有第二个还要递补进来成为最小，判一下。

然后在操作序列里将旧的数存上，回退的时候要用。

后面插入时类似地维护 $P$。

### $\texttt-$ 操作：

```cpp
void remove(int k) {
	n -= k;
	s[++top] = oper('-', k);
}
```

直接长度假装减掉即可，扔到操作序列。

### $\texttt?$ 操作：

```cpp
int query() {
	return ask(n);
}
```

树状数组查询前 $n$ 个被标记为第一次出现的数个数（即 $\min\{P_i\}\le n$ 的个数）即可。

### $\texttt!$ 操作：

```cpp
void rollback() {
	if (s[top].op == '+') {
		int x = s[top].x;
		if ((*p[a[n]].begin()) == n) {
			add(n, -1);
			p[a[n]].erase(n);
			if (p[a[n]].size()) add(*p[a[n]].begin(), 1);
			p[a[n]].insert(n);
		}
		p[a[n]].erase(n);
		if (x != -1) {
			a[n] = x;
			p[x].insert(n);
			if ((*p[x].begin()) == n) {
				add(n, 1);
				p[x].erase(n);
				if (p[x].size()) add(*p[x].begin(), -1);
				p[x].insert(n);
			}
			n--;
		} else {
			a[n] = -1;
			n--;
		}
		--top;
	} else {
		n += s[top].x;
		--top;
	}
}
```

如果要回滚的是插入，那么直接将现在新的再换成操作序列里旧的。注意实现细节。

否则长度直接加上就行。

---

总复杂度 $\Theta(q\log q)$。细节略多。

---

