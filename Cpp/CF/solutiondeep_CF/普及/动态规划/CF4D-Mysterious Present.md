# 题目信息

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

# AI分析结果

### 题目重写
# 神秘的礼物

## 题目描述

Peter决定给他的澳大利亚朋友寄一张生日贺卡。为了让礼物更加神秘，他决定制作一个信封链。这里的链是指一个信封序列 $ A $ = { $ a_{1},a_{2},...,a_{n} $ }，其中第 $ i $ 个信封的宽度和高度分别严格大于第 $ (i-1) $ 个信封的宽度和高度。链的大小是链中信封的数量。

Peter希望从他拥有的信封中制作一个最大尺寸的链，并且这个链必须能够放入一张贺卡。如果贺卡的宽度和高度分别小于链中最小的信封的宽度和高度，那么贺卡就可以放入链中。不允许旋转贺卡和信封。

Peter有很多信封，但时间很少，这个艰巨的任务就交给你了。

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

### 题解分析与结论

这道题的核心是求一个二维的最长严格上升子序列（LIS），并且需要输出这个序列的编号。题解中主要采用了动态规划（DP）的方法，部分题解还结合了排序和记忆化搜索等优化手段。

#### 关键思路与技巧
1. **排序优化**：大多数题解都提到了先按照宽度（或高度）进行排序，这样可以简化问题，使得在DP过程中只需要考虑另一个维度的递增关系。
2. **动态规划**：通过DP来求解最长上升子序列，状态转移方程通常为 $f_i = \max\{f_j+1 | j<i, w_j<w_i, h_j<h_i\}$。
3. **路径记录**：为了输出序列，很多题解使用了`pre`数组或类似的结构来记录每个状态的前驱，最后通过递归或迭代输出路径。
4. **记忆化搜索**：部分题解使用了记忆化搜索来避免重复计算，提高了效率。

#### 推荐题解
1. **Juanzhang (4星)**：使用了记忆化搜索，避免了重复计算，代码简洁且高效。
2. **Plozia (4星)**：详细解释了排序的必要性，并提供了清晰的DP实现，代码可读性强。
3. **CaiXY06 (4星)**：代码简洁，直接使用DP求解，并记录了路径，适合初学者理解。

#### 扩展思路
- **时间复杂度优化**：对于更大的数据集，可以考虑使用二分查找来优化DP过程，将时间复杂度从 $O(n^2)$ 降低到 $O(n \log n)$。
- **多维度LIS**：类似的问题可以扩展到更高维度，比如三维或更多维度的LIS问题。

#### 推荐题目
1. [P3902 递增](https://www.luogu.org/problemnew/show/P3902) - 一维LIS问题。
2. [P1020 导弹拦截](https://www.luogu.org/problemnew/show/P1020) - 二维LIS问题的变种。
3. [P1091 合唱队形](https://www.luogu.org/problemnew/show/P1091) - 双向LIS问题。

### 精选题解代码
#### Juanzhang (4星)
```cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef pair <int, int> pii;
typedef pair <pii, int> ppi;
const int maxn = 5010;
ppi a[maxn];
int n, w, h, dp[maxn], pre[maxn];

int dfs(int x) {
	if (~dp[x]) {
		return dp[x];
	}
	dp[x] = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].fir.fir > a[x].fir.fir && a[i].fir.sec > a[x].fir.sec && dp[x] < dfs(i)) {
			dp[x] = dp[i], pre[x] = i;
		}
	}
	return ++dp[x];
}

void write(int x) {
	if (x) {
		printf("%d ", x);
	}
	if (pre[x]) {
		write(pre[x]);
	}
}

int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d %d %d", &n, &w, &h);
	a[0] = make_pair(make_pair(w, h), 0);
	for (int i = 1; i <= n; i++) {
		a[i].sec = i;
		scanf("%d %d", &a[i].fir.fir, &a[i].fir.sec);
	}
	dfs(0);
	printf("%d\n", --dp[0]);
	if (dp[0]) {
		write(0);
	}
	return 0;
}
```

#### Plozia (4星)
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 5000 + 10;
int n, f[MAXN], las[MAXN], wz, hz, cnt;
struct node
{
	int w, h, id;
}a[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool cmp(const node &fir, const node &sec)
{
	if (fir.w ^ sec.w) return fir.w < sec.w;
	return fir.h < sec.h;
}

void print(int k)
{
	if (k == -1) return ;
	print(las[k]); printf("%d ", a[k].id);
}

int main()
{
	n = read(), wz = read(), hz = read();
	for (int i = 1; i <= n; ++i)
	{
		int w = read(), h = read(); las[i] = -1;
		if (w <= wz || h <= hz) continue;
		a[++cnt].w = w; a[cnt].h = h; a[cnt].id = i;
	}
	if (cnt == 0) {printf("0\n"); return 0;}
	sort(a + 1, a + cnt + 1, cmp);
	for (int i = 1; i <= cnt; ++i)
	{
		f[i] = 1;
		for(int j = 1; j < i; ++j)
		{
			if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i])
			{
				f[i] = f[j] + 1;
				las[i] = j;
			}
		}
	}
	int ans = 0, flag = 0;
	for (int i = 1; i <= cnt; ++i)
	{
		if (f[i] > ans)
		{
			ans = f[i];
			flag = i;
		}
	}
	printf("%d\n", ans); print(flag);
	return 0;
}
```

#### CaiXY06 (4星)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int w,h,x;
}a[5010];
int n,m,W,H,f[5010],pre[5010],ans,pos;
inline bool cmp(node x,node y){
	return x.w<y.w;
}
inline void write(int x){
	if(!x)return;
	write(pre[x]);
	printf("%d ",a[x].x);
}
int main(){
	scanf("%d%d%d",&m,&W,&H);
	for(int i=1,w,h;i<=m;i++){
		scanf("%d%d",&w,&h);
		if(w>W&&h>H)a[++n]=(node){w,h,i};
	}
	if(!n)return puts("0"),0;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<i;j++)
		if(a[j].w<a[i].w&&a[j].h<a[i].h&&f[j]+1>f[i]){
			f[i]=f[j]+1;
			pre[i]=j;
		}
		if(f[i]>ans){
			ans=f[i];
			pos=i;
		}
	}
	printf("%d\n",ans);
	write(pos);
	return 0;
}
```

---
处理用时：58.88秒