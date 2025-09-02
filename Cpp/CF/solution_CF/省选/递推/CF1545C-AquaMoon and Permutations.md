# AquaMoon and Permutations

## 题目描述

Cirno has prepared $ n $ arrays of length $ n $ each. Each array is a permutation of $ n $ integers from $ 1 $ to $ n $ . These arrays are special: for all $ 1 \leq i \leq n $ , if we take the $ i $ -th element of each array and form another array of length $ n $ with these elements, the resultant array is also a permutation of $ n $ integers from $ 1 $ to $ n $ . In the other words, if you put these $ n $ arrays under each other to form a matrix with $ n $ rows and $ n $ columns, this matrix is a [Latin square](https://en.wikipedia.org/wiki/Latin_square).

Afterwards, Cirno added additional $ n $ arrays, each array is a permutation of $ n $ integers from $ 1 $ to $ n $ . For all $ 1 \leq i \leq n $ , there exists at least one position $ 1 \leq k \leq n $ , such that for the $ i $ -th array and the $ (n + i) $ -th array, the $ k $ -th element of both arrays is the same. Notice that the arrays indexed from $ n + 1 $ to $ 2n $ don't have to form a Latin square.

Also, Cirno made sure that for all $ 2n $ arrays, no two arrays are completely equal, i. e. for all pair of indices $ 1 \leq i < j \leq 2n $ , there exists at least one position $ 1 \leq k \leq n $ , such that the $ k $ -th elements of the $ i $ -th and $ j $ -th array are different.

Finally, Cirno arbitrarily changed the order of $ 2n $ arrays.

AquaMoon calls a subset of all $ 2n $ arrays of size $ n $ good if these arrays from a Latin square.

AquaMoon wants to know how many good subsets exist. Because this number may be particularly large, find it modulo $ 998\,244\,353 $ . Also, she wants to find any good subset. Can you help her?

## 说明/提示

In the first test case, the number of good subsets is $ 1 $ . The only such subset is the set of arrays with indices $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ .

In the second test case, the number of good subsets is $ 2 $ . They are $ 1 $ , $ 3 $ , $ 5 $ , $ 6 $ , $ 10 $ or $ 2 $ , $ 4 $ , $ 7 $ , $ 8 $ , $ 9 $ .

## 样例 #1

### 输入

```
3
7
1 2 3 4 5 6 7
2 3 4 5 6 7 1
3 4 5 6 7 1 2
4 5 6 7 1 2 3
5 6 7 1 2 3 4
6 7 1 2 3 4 5
7 1 2 3 4 5 6
1 2 3 4 5 7 6
1 3 4 5 6 7 2
1 4 5 6 7 3 2
1 5 6 7 4 2 3
1 6 7 5 2 3 4
1 7 6 2 3 4 5
1 7 2 3 4 5 6
5
4 5 1 2 3
3 5 2 4 1
1 2 3 4 5
5 2 4 1 3
3 4 5 1 2
2 3 4 5 1
1 3 5 2 4
4 1 3 5 2
2 4 1 3 5
5 1 2 3 4
6
2 3 4 5 6 1
3 1 2 6 4 5
6 1 2 3 4 5
5 6 1 3 2 4
4 3 6 5 2 1
5 6 1 2 3 4
4 5 6 1 2 3
3 4 5 6 1 2
1 2 3 4 5 6
2 5 4 1 6 3
3 2 5 4 1 6
1 4 3 6 5 2```

### 输出

```
1
1 2 3 4 5 6 7
2
1 3 5 6 10
4
1 3 6 7 8 9```

# 题解

## 作者：7KByte (赞：4)

这个限制条件给人感觉是非常刻意的设计（差评

首先保证一定有解。

我们再来看下第二个限制条件有什么用，这意味着选了 $i$ 就不能选 $i + n$ ，选了 $i + n$ 就不能选 $i$。

显然，如果某一列一个数只出现了一次，是在第 $i$ 行出现的，那么必须要选第 $i$ 行。然后将与第 $i$ 行相关的行/列删去，得到一个规模为 $n-1$ 的子问题。

同时根据第二个限制条件，规模为 $n$ 的子问题当前保留的行数不超过 $2n$ 。

所以如果不存在一列一个数只出现一次，那么每一列每个数出现恰好两次。

这意味着我们可以将这 $2n$ 行分成两个拉丁方，两边都是合法的，所以任意选择一行，然后将方案数 $\times2$ 即可。

其余的直接暴力枚举即可，不需要任何算法和数据结构，时间复杂度 $\mathcal{O}(N^3)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
int n, a[N << 1][N], v[N], c[N][N];
vector<int>w;
void solve(){
	scanf("%d", &n);
	w.clear();
	memset(v, 0, sizeof(v));
	memset(c, 0, sizeof(c));
	rep(i, 1, n + n)rep(j, 1, n)scanf("%d", &a[i][j]), c[a[i][j]][j]++;
	int ans = 1;
	rep(i, 1, n){
		int cur = 0;
		rep(j, 1, n + n)if(!v[j]){
			rep(k, 1, n)if(c[a[j][k]][k] == 1){cur = j;break;}
			if(cur)break;
		}
		if(!cur) {
			ans = (ans << 1) % 998244353;
			cur = 1;while(v[cur])cur++;
		}
		v[cur] = 1;
		rep(j, 1, n + n)if(!v[j]){
			rep(k, 1, n)if(a[j][k] == a[cur][k]){v[j] = 1;break;}
			if(v[j])rep(k, 1, n)c[a[j][k]][k]--;
		}
		rep(k, 1, n)c[a[cur][k]][k]--;
		w.push_back(cur);
	}
	printf("%d\n",ans);
	for(int y:w)printf("%d ",y);putchar('\n');
}
int main(){
	int T;scanf("%d", &T);
	while(T--)solve();
	return 0;
} 
```

---

## 作者：Sky_Maths (赞：3)

# 主题

这里详细说明一下计算答案的方法背后的东西，即为什么方案数是 $\times 2$ 而不是其他的东西。

# 证明

## 证明什么：对于 $2n\times n$ 的当前矩阵，拉丁方阵的方案数等于任意指定一行后的方案数 $\times 2$。

首先，当前对于每一列，每个 $i$ 都出现了 $2$ 次，因为每列都要有一个 $i$，故每个 $i$ 都需要出现 $i$ 的两排有且仅有一排在答案中。

可以将这个选择抽象成一个图，对于每列的每个 $i$ 都会连一条边，最终的图上会出现 $n^2$ 条边，每条边连接的两个点都只能被选择一个，这不就是二分图染色吗，但是你不会也没关系，我们继续看下面：

最终是一个 $2n$ 个点 ， $n^2$ 条边的图，已知该图必定存在一种合法染色方案。

可以将原图分为互相没有边连接的 $k$ 个连通块，每个连通块都有且只有 $2$ 种染色方案，故最终会有 $2^k$ 种方案。

# 代码

我们可以用并查集计算连通块个数。

因为要输出方案，所以我的代码使用了分层连通块（就是将 $i$ 拆成 $i$ 和 $i+2n$）。

对变量的解释说明：
- ```A[i][j]``` 即原排列数组的值，但是存在一些0，即被删除的
- ```b``` 这里用了两次，第一次是出现次数，第二次是记录出现位置
- ```c``` 记录必选可能出现位置
- ```id``` 必选
- ```pa``` 并查集
- ```&f``` 大概相当于 ```define f b[A[i][j]]```
- ```k``` 连通块个数
- ```d``` 是否必选
- ```find(i)``` 找祖先

[Code-Link](https://codeforces.com/contest/1545/submission/224615053)

---

## 作者：SnowTrace (赞：2)

好题。

$i$ 和 $i+n$ 不能同时选一定能带来一些性质。

我们考虑最简单的问题，有没有一个排列是**必选**的。

一个排列是**必选**的等价于这个排列在某个列上对应的数只在这个列中出现了一次。

很容易先把必选的挑出来，把和必选的排列不能同时选的所有排列删掉，然后继续迭代。

考虑第一个条件有什么用。

实际上它告诉我们，**每次至少能够确定两个排列的状态**。

迭代到不能再迭代，也就是没有数在当前列只出现一次，但是注意到，我们每次迭代实际上是在每一列都确定了一个数，那么由于一定有合法的解，每一列中没有被确定的数至少会出现一次。

假设当前确定了 $x$ 个排列必选，那么至少确定了 $2x$ 个排列的状态，从而只有 $2n-2x$ 个排列没确定，而没确定的元素是 $n-x$ 个，又因所有没被确定的元素都应该在这些未确定的排列中出现且不止出现一次，所以每一个元素都出现了两次。

此时考虑对限制连边，容易发现是一张二分图。二分图的每个联通块都有 $2$ 种选法，从而容易计算答案。

构造一组解只需要在迭代到不能再迭代，然后随便挑一个没被确定的钦定它必须选，继续迭代即可。

代码中的实现是考虑到每次迭代到不能再迭代相当于确认了一个联通块，然后给其中一个任意染一个色（也就是钦定这个点必选），则可以消去一个联通块，从而继续迭代求解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n;
int a[1005][505];
int ok[1005];
vector<int>id[505][505];
void solve(){
	cin >> n;
	for(int i = 1;i<=2*n;i++)ok[i] = 0;
	for(int i =0;i<=n;i++)for(int j =0;j<=n;j++)id[i][j].clear();
	for(int i=1;i<=2*n;i++){
		for(int j =1;j<=n;j++){
			cin >> a[i][j];
			id[a[i][j]][j].push_back(i);
		}
	}
	int tt = 0,ans = 1;
	while(tt<n){
		int pos = 0;
		for(int i = 1;i<=n;i++){
			for(int j = 1;j<=n;j++){
				int tot =0,e;
				for(int x:id[i][j]){
					if(ok[x]!=-1)++tot,e = x;
				}
				if(tot!=1)continue;
				pos = e;
				break;
			}
			if(pos!=0)break;
		}

		if(!pos){
			for(int i = 1;i<=2*n;i++)if(ok[i]!=-1 and ok[i]!=1){
				pos = i;break;
			}
			ans = ans*2%mod;
		}
		ok[pos] = 1;++tt;
		for(int i = 1;i<=n;i++){
			id[a[pos][i]][i].erase(lower_bound(id[a[pos][i]][i].begin(),id[a[pos][i]][i].end(),pos));			
			for(int x:id[a[pos][i]][i])ok[x] = -1;

		}
		
	}
	cout << ans << endl;
	for(int i = 1;i<=2*n;i++)if(ok[i]==1)cout << i << " ";cout << endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Leasier (赞：1)

~~行数 $2n$ 挺奇怪的，但一开始也不知道咋用 /youl~~

**考虑先确定一些一定好的行**：

- 若 $1 \leq i \leq 2n, 1 \leq j \leq n$ 使得 $a_{i, j}$ 在第 $j$ 列中唯一，则第 $i$ 行一定是好的。

考虑每次删去一个这样的行以及存在一列与其相同的行。由题给信息，这样的行至少存在一个。

若某个时刻矩阵未被删空但不存在这样的行，则每列中每个出现过的数至少出现两次。

**注意到经过若干次前述的确定性删除，未删除行的数量一定 $\leq$ 待确定集合大小的两倍。**

于是由鸽笼原理，此时每列中每个出现过的数恰好出现两次。

又因为保证有解，未删除行一定可以被划分为两个合法的集合。

随便选一个未删除行删掉，将方案数乘二即可。

暴力实现即可。时间复杂度为 $O(\sum n^3)$。

代码：
```cpp
#include <stdio.h>

const int mod = 998244353;
int a[1007][507], cnt[507], ansp[507];
bool vis[1007];

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m, ans_way = 1;
		scanf("%d", &n);
		m = n * 2;
		for (int j = 1; j <= m; j++){
			for (int k = 1; k <= n; k++){
				scanf("%d", &a[j][k]);
			}
		}
		for (int j = 1; j <= m; j++){
			vis[j] = false;
		}
		for (int j = 1; j <= n; j++){
			bool flag = false;
			for (int k = 1; k <= n; k++){
				int pos = -1;
				for (int l = 1; l <= n; l++){
					cnt[l] = 0;
				}
				for (int l = 1; l <= m; l++){
					if (!vis[l]) cnt[a[l][k]]++;
				}
				for (int l = 1; l <= m; l++){
					if (!vis[l] && cnt[a[l][k]] == 1){
						pos = l;
						break;
					}
				}
				if (pos != -1){
					flag = true;
					ansp[j] = pos;
					break;
				}
			}
			if (!flag){
				ans_way = ans_way * 2 % mod;
				ansp[j] = 1;
				while (vis[ansp[j]]) ansp[j]++;
			}
			vis[ansp[j]] = true;
			for (int l = 1; l <= m; l++){
				if (!vis[l]){
					for (int x = 1; x <= n; x++){
						if (a[l][x] == a[ansp[j]][x]){
							vis[l] = true;
							break;
						}
					}
				}
			}
		}
		printf("%d\n", ans_way);
		for (int j = 1; j <= n; j++){
			printf("%d ", ansp[j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：hsaht2426 (赞：1)

比 D 难。

#### 赛时(?)想法：

首先是**形式化题面**。

先考虑**放缩**一下，考虑**判定性问题**，形式化拉丁方：

我们对每个点计一个可选集合，那么拉丁方问题可以转化为:

选择 $n$ 个集合使得其并集包含在其补集中。

然后尝试用第 $n+i$ 个排列和第 $i$ 个排列在至少一个位置上相同的条件**简化问题**。

那么两者之间一定有一个不能选，不能出现相同元素，这就是一个二选一问题。

结合前面的问题，可得对于合法的选择方案，你必然有至少选到 $n$ 个元素在其补集中。

又由于其补集最大只有 $n$ 个元素，所以得到该补集有 $n$ 个元素。

然后就不会做了。

这个问题此时没有什么简单情形，也没有什么有启发性的必要条件。

#### 正确做法：

所以我们**推倒重来**。

不好形式化题面，也没有什么简单情形，考虑进行一个**放缩**。

但此时转为判定性问题或判断无解都容易否掉，那只能尝试是否有启发性的**必要条件**。

容易去考虑一个值的情况。

如果某行某值未出现，显然与有拉丁方的条件相悖。

如果某行某值只出现了一次，那么这个值必须要。

发现似乎可以依靠删掉这个**递推**，考虑选择它会有什么影响，显然此时与它相关的排列都必须删掉，此时方案数不变。

否则必然每个值都在任意一行出现两次，简单分析一下就会发现仍是一个 $2\times m$ 行 $m$ 列的矩阵。

似乎有点乱了？理一理我们有什么条件:

- 每个值都在任意一行出现两次

- 存在 $n$ 个排列构成了一个拉丁方阵

由于我们前面选的都是必须选的，所以此时一定有 $m$ 个排列构成了一个拉丁方阵。

结合一下上一个条件，用值**分组**。

这就是说一定有 $m$ 个排列组成的矩阵每个值都在任意一行出现一次。

换句话说，剩下的 $m$ 个排列组成的矩阵每个值也都在任意一行出现一次。

所以事实上这个 $2\times m$ 行 $m$ 列的矩阵就是两个拉丁方。

但是还是不好计数。

类比一下前面的情况，我们可以随意取一行，将方案数乘 $2$，然后继续**递推**。

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。

---

## 作者：Little09 (赞：1)

考虑如果存在有一个数组的有一列中存在一个只出现了 $1$ 次的数，那么这个数组肯定要选入。然后与它有相同位的数组肯定不能选入。

如果上述条件不满足，显然是每一列每个剩余的数出现 $2$ 次（鸽巢原理）。于是根据题意，原始数组和添加的数组都是 Latin square。我们只要任意指定一个数组选入，将答案乘 $2$ 即可。

依次进行以上操作使所有数组的选入或不选入状态确定。可以使用队列维护，容易发现每个数组进队一次，每次操作的复杂度 $O(n^2)$。故总复杂度 $O(n^3)$。

~~这就是 2800 的题吗~~

[赛时代码](https://codeforces.com/contest/1545/submission/122129775)，写得很丑，仅供参考。

---

## 作者：intel_core (赞：0)

从给定的条件入手，不难发现 $i$ 和 $i+n$ 最多同时选一个。因此最终的方案一定是 $i$ 和 $i+n$ 挑一个。

然后从每个数出现次数的角度考虑，如果有一个数只出现了一次，那就必然要选。如果没有这样的数，那么相当于每个数都出现恰好两次，于是可以任选一个，并把方案数 $\times 2$。

这样一来，每次选一行的时候一定至少干掉了其余的一行，因此过程可以一直进行下去。

因为最多进行 $n$ 轮，每轮 $O(n^2)$，因此复杂度 $O(n^3)$。

---

## 作者：Mr_Wu (赞：0)

vp 的时候一直在思考给的条件有啥用，给排列之间连了一堆边，看二分图左部点右部点连边是啥意思，最后都扯到2-SAT方案数上去了，也是怪可笑的。

考完后换了一个方向想就顺利解决了这个问题，看来做题还是要从多角度思考啊。

---------

首先我们先不考虑给的条件是什么意思，我们从这个地方入手：$2n$ 个选 $n$ 个。

到这里其实可能仍想不出来，所以可以再考虑对所有排列的同一个位置进行分析，事情就变的明朗了。

对于一个位置 $p$，我们将所有排列按第 $p$ 位的值分类，如果存在一类里只有一个排列那么这个排列显然是要在答案里的。所以我们先考虑这样的情况，就是如果用上述方法无法确定出一个在答案里的排列，那么由于是 $2n$ 选 $n$ 所以容易发现每一类里恰有 $2$ 个排列。如果我们对每个 $p$ 分出的每一类里的两个排列连边就可以发现条件充要地转化为边上两者中选恰一个。做一遍二分图染色后统计答案即可。

现在考虑如果确定了一个排列我们会怎么做，我们就会把所有与它有相同位的排列都删掉。注意到给的条件说明“有相同位”这个关系是存在一个完美匹配的，所以当我们确定一个排列后，我们至少会删除一个排列，即它在完美匹配中的配对。那么在这次变化后，选的排列数减 1，总排列数至少减 2，所以仍然可以使用上述算法继续求解。

时间复杂度 $O(n^3)$

---------

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

typedef long long ll;
const int MAXN=1005;
const int MOD=998244353;
ll q_pow(ll a,ll b,ll p=MOD){
	ll ret=1;
	for(;b;a=a*a%p,b>>=1)if(b&1)ret=ret*a%p;
	return ret;
}

int T,N,a[MAXN][MAXN],st[MAXN];
void choose(int p){
	st[p]=2;
	for(int i=1;i<=2*N;++i)if(!st[i]){
		for(int j=1;j<=N;++j)if(a[i][j]==a[p][j]){
			st[i]=1;
			break;
		}
	}
}
int cnt[MAXN];
bool tryit(){
	for(int i=1;i<=N;++i){
		for(int j=1;j<=N;++j)cnt[j]=0;
		for(int j=1;j<=2*N;++j)if(!st[j])++cnt[a[j][i]];
		int c=0;
		for(int j=1;j<=N;++j)if(cnt[j]==1){c=j;break;}
		if(!c)continue;
		int p=0;
		for(int j=1;j<=2*N;++j)if(!st[j]&&a[j][i]==c){p=j;break;}
		choose(p);
		return 1;
	}
	return 0;
}
bool G[MAXN][MAXN];
int col[MAXN];
void dfs(int u,int c){
	col[u]=c;
	for(int i=1;i<=2*N;++i)if(G[u][i]&&!col[i])dfs(i,3-c);
}
void getans(){
	for(int i=1;i<=2*N;++i)st[i]=0;
	while(1){if(!tryit())break;}
	for(int i=1;i<=2*N;++i)col[i]=0;
	for(int i=1;i<=2*N;++i)for(int j=1;j<=2*N;++j)G[i][j]=0;
	for(int i=1;i<=2*N;++i)if(!st[i])for(int j=i+1;j<=2*N;++j)if(!st[j]){
		bool flag=0;
		for(int k=1;k<=N;++k)if(a[i][k]==a[j][k]){flag=1;break;}
		if(flag)G[i][j]=G[j][i]=1;
	}
	int cnt=0;
	for(int i=1;i<=2*N;++i)if(!st[i]&&!col[i])dfs(i,1),++cnt;
	printf("%d\n",q_pow(2,cnt));
	for(int i=1;i<=2*N;++i)if(col[i]==1||st[i]==2)printf("%d ",i);putchar('\n');
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=2*N;++i)for(int j=1;j<=N;++j)scanf("%d",&a[i][j]);
		getans();
	}
	return 0;
}
```

---

## 作者：fsy_juruo (赞：0)

我们先考虑如何找出一个幻方。定义一次“选择”操作为选出一行，且将与该行存在位置相同的相同数字的行删去。

首先，如果在“选择”若干行之后，存在某一行，使得其某一列的数字在所有剩余的行中只出现一次（如样例 3 第一列的 6），显然，这一行是归属于原幻方的。故“选择”这一行。

反之，由于鸽巢原理，在每一列上，该列所有的数字必定刚好出现 2 次。容易发现存在 2 种填法。故我们将答案乘二之后，随意“选择”一行。

重复以上操作，直至取满 $n$ 行即可。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}

const int maxN = 510, P = 998244353;
int t, n;
int a[maxN << 1][maxN], occur[maxN][maxN], choose[maxN][maxN], c[maxN << 1];

void occupy(int l, int y) {
	c[l] = 1 + (1 ^ y);
	_rep(i, 1, n) occur[i][a[l][i]]--, choose[i][a[l][i]] = std::max(choose[i][a[l][i]], y);
}
int main() {
	read(t);
	while(t--) {
		read(n);
		_rep(i, 1, 2 * n) {
			_rep(j, 1, n) read(a[i][j]),  occur[j][a[i][j]]++;
		}
//		_rep(i, 1, n) {
//			_rep(j, 1, n) {
//				std::cout << occur[i][j] << " ";
//			}
//			std::cout << "\n";
//		}
		int Numx = 0, Numy = 0, ans = 1;
		_rep(k, 1, n) {
			Numx = 0, Numy = 0;
			_rep(i, 1, n) {
				if(Numx || Numy) break;
				_rep(j, 1, n) {
					if(choose[i][j]) continue;
//					std::cout << i << " " << j << " " << occur[i][j] << std::endl;
					if(occur[i][j] == 1) {
						Numx = i; Numy = j; 
						break;
					}
				}
			}	
//			std::cout << Numx << " " << Numy << std::endl;
			if(!Numx && !Numy) {
				ans = 2ll * ans % P;
				int flg = -1;
				_rep(i, 1, 2 * n) {
					if(c[i] == 0) {
						occupy(i, 1);
//						std::cout << i << " " ;
						flg = i;
						break;
					}
				}
				_rep(i, 1, n) {
					int kk = a[flg][i];
					if(occur[i][kk]) {
						_rep(j, 1, 2 * n) {
							if(c[j]) continue;
							if(a[j][i] == kk) {
								occupy(j, 0);
//								std::cout << j << " " ;
							}
						}
					}
				}
			} else {
				int flg = 0;
				_rep(i, 1, 2 * n) {
					if(c[i]) continue;
					if(a[i][Numx] == Numy) {
						occupy(i, 1);
//						std::cout << i << " " ;
						flg = i;
						break;
					}
				}
				_rep(i, 1, n) {
					int kk = a[flg][i];
					if(occur[i][kk]) {
						_rep(j, 1, 2 * n) {
							if(c[j]) continue;
							if(a[j][i] == kk) {
								occupy(j, 0);
//								std::cout << j << " " ;
							}
						}
					}
				}
				
			}
//			std::cout << std::endl;
		}
		writesp(ans, '\n');
		_rep(i, 1, 2 * n) {
			if(c[i] == 1) std::cout << i << " ";
		}
		memset(c, 0, sizeof(c));
		memset(choose, 0, sizeof(choose));
		memset(occur, 0, sizeof(occur));
	}
	return 0;
}
```

---

