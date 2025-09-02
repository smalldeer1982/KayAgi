# [CERC2016] 不可见的整数 Invisible Integers

## 题目描述

《隐形的整数》是一个简单的猜数游戏。在这个游戏中，给定n个提示，玩家将尝试去猜一个仅包含自然数1到9的数字序列，满足所有n个提示。每个提示是一个包含若干互不相同的1到9之间的整数序列，它是这样生成的：


1.随机选择一个序列中的位置作为起点。


2.随机选择任意一个方向，左或者右。


3.从起点开始沿着选定的方向走，遍历完这个方向的每个数字，将每个数字第一次出现的顺序记录下来。


请找到长度最短的满足所有n个提示的序列。


## 说明/提示

一个可行的序列是(1,2,1,4,1,3,4)。

对于提示序列(1,2)，可以选择位置3，然后往左走。

对于提示序列(3,4)，可以选择位置6，然后往右走。

对于提示序列(1,4,3)，可以选择位置3，然后往右走。

对于提示序列(3,1,4,2)，可以选择位置6，然后往左走。

对于提示序列(1,2,4,3)，可以选择位置1，然后往右走。


## 样例 #1

### 输入

```
5
1 2 0
3 4 0
1 4 3 0
3 1 4 2 0
1 2 4 3 0```

### 输出

```
7```

# 题解

## 作者：chen_03 (赞：11)

对于方向相同的两个提示 $x,y$，我们考虑如果 $y$ 能接在 $x$ 的第 $i$ 位之后，应当满足什么条件：

- $x,y$ 作为集合时，$y\subseteq x$；
- $x$ 从第 $i$ 位开始往后的部分（包括第 $i$ 位）是 $y$ 的子序列。

如果我们按这个方向依次填数，若已经填到了 $x$ 的第 $i$ 位，那么我们可以选择停止考虑 $x$，转而考虑 $y$。

若 $i$ 满足条件，则 $i+1$ 也满足条件。我们可以对于每对 $(x,y)$ 预处理出这个最小的 $i$，或者发现不存在这样的 $i$。

（以下所有下标均从 $0$ 开始。记 $a_{i,l}$ 表示提示 $i$ 的第 $l$ 位；$p_{i,l}$ 表示数字 $l$ 在提示 $i$ 中的出现位置，若没有出现则为 $+\infty$；$L_i$ 表示提示 $i$ 的长度）

考虑如果只能往右走怎么做。我们从左到右依次填数。考虑 DP，设 $f(S,i,l)$ 表示已经考虑了集合 $S$ 中的提示，当前正在考虑提示 $i$，已经填了 $i$ 的第 $0\sim l-1$ 位（正在等待第 $l$ 位）时的最短长度。有两种转移：

- 停止考虑 $i$，转而考虑 $j$。转移为 $f(S\cup\{j\},j,0)\leftarrow f(S,i,l)$，需满足 $j$ 可以接在 $i$ 的第 $l$ 位之后。
- 填一个数。我们可以直接填 $a_{i,l}$，转移为 $f(S,i,l+1)\leftarrow f(S,i,l)+1$。

考虑扩展到一般情况。设 $f(S,i,l,j,r)$ 表示已经考虑了集合 $S$ 中的提示，当前正在考虑的向左走的提示为 $i$，已经填了 $i$ 的第 $l\sim L_i-1$ 位（正在等待第 $l-1$ 位），当前正在考虑的向右走的提示为 $j$，已经填了 $j$ 的第 $0\sim r-1$ 位（正在等待第 $r$ 位）时的最短长度。

注意：我们仍然是**从左到右依次填数**，所以向左走的提示要从后往前匹配，向右走的提示要从前往后匹配，这导致了两个方向的提示转移方式的不同。

有三种转移：

- 把 $i$ 换成 $k$。转移为 $f(S\cup\{k\},k,x,j,r)\leftarrow f(S,i,0,j,r)$，其中 $x$ 表示**所有**满足 $i$ 能接在 $k$ 的第 $x$ 位之后的 $x$。
- 把 $j$ 换成 $k$。转移为 $f(S\cup\{k\},i,l,k,0)\leftarrow f(S,i,l,j,r)$，需满足 $k$ 能接在 $j$ 的第 $r$ 位之后。
- 填一个数。枚举填的数 $k$，转移为 $f(S,i,l-[a_{i,l-1}=k],j,r+[a_{j,r}=k])\leftarrow f(S,i,l,j,r)+1$。需满足 $p_{i,k}\le l$（注意不是 $l-1$）且 $p_{j,k}\le r$。

**有亿点细节：**

我们需要想办法记录当前考虑的提示是否为对应方向的第一个提示。具体地，我们可以新增一个编号为 $n$ 的提示作为占位符（可以认为它的长度为 $0$）。在 $f(S,i,l,j,r)$ 中，若 $i=n$，则表示不再新增向左的提示；若 $j=n$，则表示还没有考虑过向右的提示。

DP 初值为 $f(\varnothing,n,0,n,0)=f(\{i\},i,L_i,n,0)=0$。需要新增一种转移：

- 停止新增向左的提示。转移为 $f(S,n,0,j,r)\leftarrow f(S,i,0,j,r)$。

注意转移顺序。时间复杂度 $\mathcal{O}(2^n (10n)^2\cdot n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
int n,ht[15][15],pos[15][15],st[15],len[15],tr[15][15];
int f[1029][11][11][11][11],cur,ans;
inline int get_tr(int x,int y){
	if((st[x]&st[y])^st[y])return inf;
	int a=pos[y][ht[x][len[x]-1]],b,i;
	if(a==inf)return len[x];
	for(i=len[x]-1;i;--i){
		b=a,a=pos[y][ht[x][i-1]];
		if(a==inf || a>b)break;
	}
	return i;
}
inline void upd(int &x,int y){x>y?x=y:0;}
int main(){
	scanf("%d",&n);
	memset(pos,0x3f,sizeof(pos));
	memset(tr,0x3f,sizeof(tr));
	memset(f,0x3f,sizeof(f));
	for(int i=0,j,x;i<n;++i){
		j=0;
		while(scanf("%d",&x) && x){
			ht[i][j]=--x;
			pos[i][x]=j++;
			st[i]|=1<<x;
		}
		len[i]=j;
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			if(i!=j)tr[i][j]=get_tr(i,j);
	f[0][n][0][n][0]=0;
	for(int i=0;i<n;++i)
		f[1<<i][i][len[i]][n][0]=0;
	ans=inf;
	for(int S=0;S<(1<<n);++S){
		for(int i=0;i<=n;++i){
			for(int l=len[i];~l;--l){
				for(int j=0;j<=n;++j){
					for(int r=0;r<=len[j];++r){
						if((cur=f[S][i][l][j][r])>=inf)continue;
						if(S==(1<<n)-1 && l==0 && r==len[j])upd(ans,cur);
						for(int k=0;k<n;++k){
							if(S>>k&1)continue;
							if(i!=n && l==0)
								for(int x=tr[k][i];x<=len[k];++x)
									upd(f[S|(1<<k)][k][x][j][r],cur);
							if(j==n || r>=tr[j][k])
								upd(f[S|(1<<k)][i][l][k][0],cur);
						}
						if(i!=n && l==0)upd(f[S][n][0][j][r],cur);
						for(int k=0,L,R;k<9;++k){
							if(i==n)L=0;
							else{
								if(pos[i][k]>l)continue;
								L=l-(pos[i][k]==l-1);
							}
							if(j==n)R=0;
							else{
								if(pos[j][k]>r)continue;
								R=r+(pos[j][k]==r);
							}
							upd(f[S][i][L][j][R],cur+1);
						}
					}
				}
			}
		}
	}
	printf("%d\n",ans<inf?ans:-1);
	return 0;
}
```


---

## 作者：devout (赞：7)

第四个AC的来水一发题解（

发现同方向上的一些提示是可以接在另一些提示后面的，考虑提示 $z$ 如果能接在 $x$ 的第 $y$ 位之后，那么他应该满足的条件是：

- $\forall a\in z,a\in x$
- $x$ 在第 $y$ 后面的数在 $z$ 中相对顺序不变

那么我们可以当一个 $x$ 已经可以被另一个 $z$  接在后面的时候，我们只去考虑 $z$ 就好了。

所以我们可以设计一个转移方程，用 $f[S][l][i][r][j]$ 表示现在已经不考虑的提示的集合为 $S$，向左方向走的当前考虑到的提示为 $l$，现在考虑到他的第 $i$ 位，向右方向走当前考虑到的提示为 $r$，现在考虑到他的第 $j$ 位的时候的最短的长度

那么转移的时候，可以转移到在后面添加一个下一位的数，或者之前出现过的数，或者更换当前考虑的 $l,r$

转移的复杂度是 $O(2^n\times (10n)^2\times n)$ 左右的一个效率（大概...

---

## 作者：UKE_Automation (赞：0)

### P3685 [CERC2016] 不可见的整数 Invisible Integers

[$\text{Link}$](https://www.luogu.com.cn/problem/P3685)

观察到 $n\le 10$，说明我们肯定要状压条件。于是基本的状态就是设现在往左 / 右扩展的的是哪一个条件，并且放到了第几位。不过这里的问题就是如果我们同时向两边扩展，我们实际上是很难考虑到向右和向左的条件相交这个情况的。解决方案是我们只考虑从左往右放数字，然后把向左扩展的反着放即可。

进一步可以发现，有些条件之间是有关系的。例如对于某两个条件 $i,j$，如果 $i$ 已经放到了第 $x$ 位，那么此时把这一位当成 $j$ 的第一位，把 $j$ 放完后就可以同时满足两个条件，我们称 $j$ 可以接在 $i$ 的第 $x$ 位后面。这告诉我们转移的时候是可以更换条件的。

那么状态就是 $dp(S,i,j,k,l)$ 表示当前已经考虑到的集合为 $S$；当前向右的条件是 $i$，且放完 $1\sim j-1$ 位、准备放第 $j$ 位；当前向左的条件是 $k$，且放完 $len_k\sim l+1$ 位、准备放第 $l$ 位，还需要的最少步数。转移有三种：

- 把向右的条件 $i$ 换成 $x$，需要满足 $x$ 可以接在 $i$ 的第 $j$ 位后，转移为 $dp(S\cup \{x\},x,1,k,l)\to dp(S,i,j,k,l)$。
- 把向左的条件 $k$ 换成 $x$，需要满足 $k$ 已经放完，并且可以接在 $x$ 的第 $y+1$ 位后，转移为 $dp(S\cup\{x\},i,j,x,y)\to dp(S,i,j,k,0)$。
- 枚举下一个要放的数 $x$，需要满足此时这个 $x$ 在 $i$ 的前 $j$ 位以及 $k$ 的前 $l+1$ 位出现过，并且为了更优此时一定要有一个条件的下一位是这个数，转移为 $dp(S,i,j+[a_{i,j}=x],k,l-[a_{k,l}=x])+1\to dp(S,i,j,k,l)$。

然后就是初值和终止状态。为了限制这两个，我们定义 $i=0$ 表示还没有考虑向右的条件，$k=0$ 表示向左的条件已经考虑完了。那么初值就是 $dp(U,i,len_i+1,k,0)=0$，其中 $U$ 是全集；而答案就是 $dp(\varnothing,0,0,0,0)$ 或者 $dp(\{k\},0,0,k,len_k)$。同时为了转移到 $k=0$，我们还要再加一个转移：

- 不再考虑向左的条件，转移为 $dp(S,i,j,0,0)\to dp(S,i,j,k,0)$。

那么这道题就做完了，复杂度是 $O(2^n\times 10^2\times n^3)$ 的，可以通过。由于转移顺序不是特别清晰所以可以用记忆化搜索实现。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
int Add(int x, int y) {return x + y >= Mod ? x + y - Mod : x + y;} void pls(int &x, int y) {x = Add(x, y);}
int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} void sub(int &x, int y) {x = Del(x, y);}
int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> 
inline void read(T &x) {
	x = 0; bool flg = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
inline void write(T x, bool typ = 0) {
	static short stk[50], top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do stk[++top] = x % 10, x /= 10; while(x);
	while(top) putchar(stk[top--] | 48);
	typ ? putchar(' ') : putchar('\n');
}

int n;
int ht[11][11], len[11], pos[11][11];
int dp[1 << 10][11][11][11][11];

int vis[11];
int check(int x, int y, int p) {
	for(int i = 1; i <= 9; i++) vis[i] = 0;
	for(int i = 1; i < p; i++) vis[ht[x][i]] = 1;
	int pos = p;
	for(int i = 1; i <= len[y]; i++) {
		if(vis[ht[y][i]]) continue;
		if(pos <= len[x] && ht[y][i] == ht[x][pos]) pos++;
		else return 0;
	}
	if(pos != len[x] + 1) return 0;
	return 1;
}

int dfs(int p, int S, int i, int j, int k, int l) {
	if(dp[S][i][j][k][l] != -1) return dp[S][i][j][k][l];
	if(S == (1 << n) - 1 && j == len[i] + 1 && l == 0) return dp[S][i][j][k][l] = 0;
	int cur = Inf;
	if(i != 0) {
		for(int x = 1; x <= n; x++) {
			if((S >> (x - 1)) & 1) continue;
			if(check(i, x, j)) cur = min(cur, dfs(p + 1, S | (1 << (x - 1)), x, 1, k, l));
		}
	}
	else {
		for(int x = 1; x <= n; x++) {
			if((S >> (x - 1)) & 1) continue;
			cur = min(cur, dfs(p + 1, S | (1 << (x - 1)), x, 1, k, l));
		}
	}
	if(k != 0 && l == 0) {
		for(int x = 1; x <= n; x++) {
			if((S >> (x - 1)) & 1) continue;
			for(int y = 0; y <= len[x]; y++) {
				if(check(x, k, y + 1)) cur = min(cur, dfs(p + 1, S | (1 << (x - 1)), i, j, x, y));
			}
		}
		cur = min(cur, dfs(p + 1, S, i, j, 0, 0));
	}
	for(int x = 1; x <= 9; x++) {
		if((ht[i][j] == x || ht[k][l] == x) && pos[i][x] <= j && pos[k][x] <= l + 1) {
			cur = min(cur, dfs(p + 1, S, i, j + (ht[i][j] == x), k, l - (ht[k][l] == x)) + 1);
		}
	}
	return dp[S][i][j][k][l] = cur;
}

int main() {
	read(n);
	for(int i = 1; i <= n; i++) {
		int x;
		for(int j = 1; j <= 9; j++) pos[i][j] = Inf;
		while(1) {
			read(x);
			if(!x) break;
			ht[i][++len[i]] = x;
			pos[i][x] = len[i];
		}
	}
	memset(dp, -1, sizeof dp);
	int ans = dfs(0, 0, 0, 0, 0, 0);
	for(int i = 1; i <= n; i++) {
		ans = min(ans, dfs(0, 1 << (i - 1), 0, 0, i, len[i]));
	}
	if(ans == Inf) write(-1);
	else write(ans);
	return 0;
}
```

---

## 作者：OIer_Automation (赞：0)

几个月前的模拟赛考题，当时没几个人改出来，现在又做了一遍 QAQ。

考虑到题目中给出的限制非常的恶心，直接 dp 的限制会特别多，因此我们很难设计一个状态使得我们可以容易的转移。但是关注到这题的 $n\le 10$，并且长度最多也只有 $9$，那么我们可以考虑一个近似搜索的思路。

我们从左往右填数，考虑只有向右的提示时我们如何 dp。容易想到我们进行状压，并考虑当前正在完成哪一个提示，完成到了第几位。令 $f(S,i,l,j,r)$ 表示完成的提示状态为 $S$，当前正在完成第 $i$ 个和第 $j$ 个提示，第 $i$ 个提示向右并且现在需要填写第 $l$ 位，第 $j$ 个提示向左并且现在需要填写第 $r$ 位，并且最终完成所有提示的最小所需长度。注意这里即使是向左的提示我们依然从左向右填写，因此向左的匹配的填写是倒序的，特别的，当 $l=\text{len}(i)+1$ 时，说明 $i$ 已填写完毕，$r=0$ 时，说明 $j$ 这个提示已经完成。那么我们有以下转移：

1. 直接填写 $i$ 接下来所需要的数字。此时的所需长度为 $f(S,i,l+1,j,r)+1$，并且需要保证填写不会导致 $j$ 的失败，也就是当前填写的数字 $x$ 在 $j$ 中的出现位置不能在 $r$（包括 $r$）之前，或根本没有出现，否则在 $j$ 中的 $x$ 会提前出现。
2. 直接填写 $j$ 接下来所需要的数字。此时的所需长度为 $f(S,i,l,j,r-1)+1$，同理填写的 $x$ 在 $i$ 中不能晚于 $l$（包括 $l$）出现，或根本没有出现，否则在 $i$ 中 $x$ 会提前出现。

3. 直接填写 $i,j$ 接下来一个共同需要的数字。此时的所需长度为 $f(S,i,l+1,j,r-1)+1$。

4. 将 $i$ 替换成其他还未考虑的提示。此时的所需长度为 $f(S\cup\{i\},p ,1,j,r)$，并且需要保证完成 $p$ 这个提示不会导致 $i$ 这个提示的失败，也就是当你成功完成 $p$ 这个提示的时候，你可以保证 $i$ 也一定完成了。

   我们可以预处理这个内容，因为 $p$ 总是从头开始，所以我们只关心 $i,l,p$ 三个参数。设 $g(i,l,p)$ 表示当 $i$ 需要填写第 $l$ 位的时候，能否在后面接入 $p$。如何求解是容易的，我们暴力跑一遍 $p$ 的内容，并动态维护当前的 $i$ 匹配到的位置 $l'$。如果当前这一位的 $x$ 可以匹配，那么对 $l'$ 加 $1$，否则判定 $x$ 在 $i$ 中的位置是否在 $l'$ 前，显然如果这个位置不在 $l'$ 之前，或根本没有出现，那么 $x$ 在 $i$ 中会提前出现。到最后，如果 $i$ 全部匹配，那么可以认为 $g(i,l,p)$ 为真。

5. **如果 $j$ 已经完成**，找一个还未考虑的提示 $p$，并枚举其当前应该填写的位置 $r'$。此时的所需长度为 $f(S\cup\{j\},i,l,p,r')$，并且需要保证完成 $j$ 的时候，我们可以认为 $p$ 已经该填写 $r'$。

   先解释为什么不像上一个转移一样动态转移，这是因为你的上一个提示可以对你的这一个提示做贡献，因此你是不知道这一个提示的哪些位已经被匹配了，如果你在所有位置暴力去找这个长度，因为每一个位置其实只对应一个最优长度，所以你不如在完成这个提示时重新枚举。考虑怎样判定 $p$ 是否可以已经填写 $r'$ ，我们将整个序列颠倒过来看，我们发现 $p,r',j$ 之间满足的内容其实和之前我们维护的 $i,l,p$ 是相同的，直接用即可。

可以用记忆化优化整个过程。关于复杂度，我们发现有 $O(2^n(10n)^2)$ 个状态，其中有 $O(2^n10n^2)$ 个状态的转移是 $O(10n)$ 的，$O(2^n(10^n)^2)$ 个状态的转移是 $O(n)$ 的，因此总复杂度是 $O(2^n(10n)^2n)$。具体实现的细节是很多的，因为在开始某一种提示的填写时，另一种可能还没有需要填写的提示，因此我们可以新增一个字符串 $n+1$ 当作还没有开始的标志，而用字符串 $0$ 表示已经结束。需要注意因为向右的提示直到最后都会被影响，因此 $i$ 始终不为 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline 

const int N=12,inf=2e9;

int n;
int dp[1<<10][N][N][N][N],len[N],a[N][N],pos[N][N];
bitset<N>pre[N][N];

il bool Check(int x,int l,int y){
	for(int i=1;i<len[y];i++){
		if(l<len[x]&&pos[x][a[y][i]]==l)l++;
		else if(pos[x][a[y][i]]==inf||pos[x][a[y][i]]>l)return false;
	}
	return l==len[x];
}
il int Dfs(int typ,int x,int l,int y,int r){
	if(dp[typ][x][l][y][r]!=-1)return dp[typ][x][l][y][r];
	int _x=x,_y=y,_typ=typ;
	if(l==len[x])_x=0,_typ|=1<<(x-1);
	if(y&&r==0)_y=0,_typ|=1<<(y-1);
	if(_x==0&&_y==0&&_typ==(1<<n)-1)return dp[typ][x][l][y][r]=0;
	int res=inf,opt=x>n?typ:typ|1<<(x-1);
	for(int i=1;i<=n;i++){
		if(((typ>>(i-1))&1)||i==x||i==y)continue;
		if(pre[x][l][i])res=min(res,Dfs(opt,i,1,y,r));
	}
	if(y){
		if(r==0){
			int opt=y>n?typ:typ|1<<(y-1);
			for(int i=1;i<=n;i++){
				if(((typ>>(i-1))&1)||i==x||i==y)continue;
				for(int v=1;v<=len[i];v++)if(pre[i][v][y])res=min(res,Dfs(opt,x,l,i,v-1));
			}
			res=min(res,Dfs(opt,x,l,0,0));
		}else{
			if(l<len[x]&&pos[y][a[x][l]]<=r)res=min(res,Dfs(typ,x,l+1,y,r)+1);
			if(pos[x][a[y][r]]<l)res=min(res,Dfs(typ,x,l,y,r-1)+1);
			if(l<len[x]&&a[x][l]==a[y][r])res=min(res,Dfs(typ,x,l+1,y,r-1)+1);
		}
	}else if(l<len[x])res=min(res,Dfs(opt,x,l+1,y,r)+1);
	return dp[typ][x][l][y][r]=res;
}

int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=9;j++)pos[i][j]=inf;
	for(int i=1;i<=9;i++)pos[n+1][i]=1;
	for(int i=1;i<=n;i++)while(1){
		cin>>a[i][++len[i]];
		if(!a[i][len[i]])break;
		pos[i][a[i][len[i]]]=len[i];
	}
	len[n+1]=2;
	for(int i=1;i<=n;i++)pre[n+1][2][i]=pre[i][len[i]][n+1]=1;
	for(int i=1;i<=n;i++)for(int j=0;j<=len[i];j++)for(int k=1;k<=n;k++)pre[i][j][k]=Check(i,j,k);
	for(int opt=0;opt<1<<n;opt++)for(int x=0;x<=n+1;x++)for(int l=0;l<=len[x];l++)for(int y=0;y<=n+1;y++)for(int r=0;r<=len[y];r++)dp[opt][x][l][y][r]=-1;
	int ans=Dfs(0,n+1,2,n+1,0);
	cout<<(ans>=inf?-1:ans);
}
```

---

