# Friction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualc/tasks/codefestival_2016_qualC_d

高橋君の部屋には縦 $ H $ 行、横 $ W $ 列、 $ H\ \times\ W $ 個のブロックからなるオブジェがあります。 各ブロックには色がついています。色は英小文字(`a`-`z`) で表されます。上から $ i $ 個目、左から $ j $ 個目のブロックの色は $ c_{i,j} $ です。

あまり見栄えが良くないため高橋君はこのオブジェを解体しようとしています。解体作業は以下の操作の繰り返しになります。

- $ W $ 個の列のうち一つを選び、その列を一段沈める。その列の一番下にあったブロックは消滅する。

同じ色のブロックは引き寄せ合う力を持つため、この操作にかかるコストは、「選んだ列のブロックと(操作前に)横に隣り合っているブロックで、色が同じもの の個数」になります。

高橋君はこの作業を $ H\ \times\ W $ 回行うことで全てのブロックを消滅させオブジェを解体します。操作する列の順番をうまく選ぶことによって、解体にかかるコストの総和を最小化してください。

## 说明/提示

### 制約

- $ 1≦H≦300 $
- $ 2≦W≦300 $
- $ c_{i,j} $ は英小文字(`a`-`z`)

### 部分点

- $ W=3 $ を満たすデータセットに正解すると、$ 300 $ 点が与えられる。

### Sample Explanation 1

例えば下図のような順で操作するとコストの総和は $ 2 $ に出来て、これが最小値です。 !\[c116dab4c0a2f42759c6476d95330a37.png\](https://atcoder.jp/img/code-festival-2016-qualc/c116dab4c0a2f42759c6476d95330a37.png)

### Sample Explanation 2

はじめに真ん中の列を全て沈め、次に左の列を全て沈め、最後に右の列を全て沈めることでコスト$ 0 $を達成できます。

### Sample Explanation 3

右の列を一段沈める→左の列を一段沈める→右の段を全て沈める→左の段を全て沈める とすることでコスト$ 0 $にすることが可能です。

## 样例 #1

### 输入

```
2 3
rrr
brg```

### 输出

```
2```

## 样例 #2

### 输入

```
6 3
xya
xya
ayz
ayz
xaz
xaz```

### 输出

```
0```

## 样例 #3

### 输入

```
4 2
ay
xa
xy
ay```

### 输出

```
0```

## 样例 #4

### 输入

```
5 5
aaaaa
abbba
ababa
abbba
aaaaa```

### 输出

```
24```

## 样例 #5

### 输入

```
7 10
xxxxxxxxxx
ccccxxffff
cxxcxxfxxx
cxxxxxffff
cxxcxxfxxx
ccccxxfxxx
xxxxxxxxxx```

### 输出

```
130```

# 题解

## 作者：Mobius127 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2087)

因为三列之间的操作可以交替进行，所以我们两列两列地去考虑费用。

易设 $f_{x, y}$ 为左一列推 $x$ 次，右一列推 $y$ 次的最小代价。

$val_{x, y}$ 当左一列推完 $x$ 次，右一列推完 $y$ 次后，再推一次的花费。

显然有 

$$f_{x, y}=\min{f_{x-1, y}+val_{x-1, y}, f_{x, y-1}+val_{x, y-1}}$$

考虑怎么求得 $val$，这个显然可以像对角线那样递推，同时要去掉推完之后相同的情况。

那么整个题就愉快地写完啦。

又想到递推 $f$ 的时候应该要从总次数一定时开始推，所以我们再转化一下，由 $f_{x, y}$ 去更新 $f_{x+1, y}, f_{x, y+1}$ 。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int N=305;
typedef long long ll;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
char mp[N][N];
int val[N][N], f[N][N];
int n, m, ans;
int solve(int x){
	memset(val, 0, sizeof(val));
	for(int i=0; i<=n; i++)
		for(int l=n-i, r=n; l&&r; l--, r--)
			if(mp[l][x]==mp[r][x+1])
				val[i][0]++;
	for(int i=1; i<=n; i++)
		for(int l=n, r=n-i; l&&r; l--, r--)
			if(mp[l][x]==mp[r][x+1])
				val[0][i]++;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			val[i][j]=val[i-1][j-1]-(mp[n-i+1][x]==mp[n-j+1][x+1]);
	memset(f, 9, sizeof(f));f[0][0]=0;
	for(int i=0; i<=n*2; i++)
		for(int j=0; j<=min(i, n); j++){
			int x=j, y=i-j;
			if(x>n||y>n) continue;
			if(x<n) f[x+1][y]=min(f[x+1][y], f[x][y]+val[x][y]);
			if(y<n) f[x][y+1]=min(f[x][y+1], f[x][y]+val[x][y]);
		}
	return f[n][n];
}
signed main(){
	n=read(), m=read();
	for(int i=1; i<=n; i++)
		scanf("%s", mp[i]+1);
	for(int i=1; i<m; i++)
		ans+=solve(i);
	printf("%d", ans);
	return 0;
}
```


---

## 作者：lky1433223 (赞：0)

这道题折腾了我半天来想为啥互相不影响2333

# [推销博客](https://www.cnblogs.com/Shiina-Rikka/p/11769551.html)

我们发现，相邻两列的代价与其他两列无关，比如1、2列的代价并不会影响2、3列的代价。因此$DP$计算相邻两列的计划。

设$f[x][y]$表示第一列往下推了$x$格， 第二列往下推了$y$格的最小代价。

转移显然 $f[x][y] = \min(f[x-1][y] + cost[x-1][y],f[x][y-1] + cost[x][y-1] )$

$cost$可以使用前缀和计算，节省一维的时间复杂度。

每次计算相邻两列即可。时间复杂度$O(h^2 \cdot w)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN =  305;
int n, m;
char th[MAXN][MAXN];
inline int calc(const int &x)
{
	static int f[MAXN][MAXN];
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= n; ++j)
			f[i][j] = (th[i][x] == th[j][x + 1]);
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= n; ++j)
			f[i][j] = f[i - 1][j - 1] + f[i][j];
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= n; ++j)
			f[i][j] += min(f[i - 1][j], f[i][j - 1]);
	return f[n][n];
}
int main()
{
	scanf("%d %d", &n, &m);
	for(register int i = 1; i <= n; ++i)
		scanf("%s", th[i] + 1);	
	register int ans = 0;
	for(register int i = 1; i < m; ++i)
		ans += calc(i);
	cout << ans << endl;
}
```
至于相邻两列代价与其他列无关的问题，我一开始也有疑问，而网上找到的题解都没有详细解释。我自己尝试~~证明~~感性理解了一波。可能出锅。

我们首先考虑只有1、2两列的情况，这两列之间会有一个最优解。再考虑加进来第3列，2、3列之间也会有一个最优解。这两个最优解为何不会冲突呢？

因为他们的关系只是这两列之间的相对关系，就拿第三个样例的前三列来说。

1、2列的最优解应该是：第一列向下两次，第二列向下一次，之后每列轮换向下移动，最小代价为4。

不画图了表格写一下子，自己手玩。

|1|2|3|4|
|--|--|--|--|
|aa| a| a|  |
|ab|ab| b| a|
|ab|ab|ab|ab|
|ab|ab|ab|ab|
|aa|aa|aa|ab|

而2、3列之间应该是将第3列一直推到底，总代价为8。

|1|2|3|4|5|6|
:-|:-|:-|:-|:-|:-
|aa|a |a |a |a |a |
|bb|ba|b |b |b |b |
|ba|bb|ba|b |b |b |
|bb|ba|bb|ba|b |b |
|aa|ab|aa|ab|aa|a |

这两列合到一起呢？

实际可以先操作第3列，再操作1、2，并不会对结果产生影响。
以此类推，第$i$列与第$i + 1$列的操作都是相对的，因此相邻并没有影响，$DP$结果直接相加即可。


---

