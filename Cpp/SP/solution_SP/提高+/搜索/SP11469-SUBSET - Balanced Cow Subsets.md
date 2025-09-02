# SUBSET - Balanced Cow Subsets

## 题目描述

Farmer John's owns N cows (2 <= N <= 20), where cow i produces M(i) units of milk each day (1 <= M(i) <= 100,000,000).

 FJ wants to streamline the process of milking his cows every day, so he installs a brand new milking machine in his barn.

Unfortunately, the machine turns out to be far too sensitive: it only works properly if the cows on the left side of the

barn have the exact same total milk output as the cows on the right side of the barn!

Let us call a subset of cows "balanced" if it can be partitioned into two groups having equal milk output.

 Since only a balanced subset of cows can make the milking machine work, FJ wonders how many subsets of his N cows are balanced.

 Please help him compute this quantity.

 `INPUT FORMAT:` `* Line 1: The integer N.` `* Lines 2..1+N: Line i+1 contains M(i).` `SAMPLE INPUT` `4 ` `1 ` `2 ` `3 ` `4` `INPUT DETAILS:` `There are 4 cows, with milk outputs 1, 2, 3, and 4.` `OUTPUT FORMAT: ` `* Line 1: The number of balanced subsets of cows. ` `SAMPLE OUTPUT:` `3` `OUTPUT DETAILS: ` `There are three balanced subsets: the subset {1,2,3}, which can be partitioned into {1,2} and {3}, the subset {1,3,4}, ` `which can be partitioned into {1,3} and {4}, and the subset {1,2,3,4} which can be partitioned into {1,4} and {2,3}.`

# 题解

## 作者：DarkShadow (赞：8)

# SP11469（折半搜索）

## 题目大意：

给出 $N$ 个数，求可以被分成两个和相等的集合的子集数。

## 思路分析：

首先考虑朴素的 DFS，每个数有三种情况：选为 $A$ 集合，选为 $B$ 集合，两个集合都不选。暴力 DFS 时间复杂度为 $3^{20}$。

观察到 $N$ 很小，而 $3^{10}$ 是可以通过本题的，于是考虑折半搜索。

我们设前半部分搜索出来的两个集合和分别为 $A$、$B$，后半部分为 $D$、$C$，则 $A+D=B+C$。

变形可得 $A-B=C-D$。

所以我们只需要记录当前 DFS 搜出来的两个集合差为多少。

### part1. 第一遍 DFS

首先 DFS 从 $1$ 到 $(1+N)\div 2$，记录当前搜出来两个集合的差，同时用状态压缩记录选了哪些数。搜完后用 vector 记录当前状态。

由于差可能很大或为负数，我们需要用 map 编号（也就是离散化）后加入 vector。

### part2. 第二遍 DFS

和第一遍相似，DFS 从 $(1+N)\div 2 +1$ 到 $N$，记录的内容和第一遍相同。

搜完后在 vector 的对应位置记录答案。

DFS 代码：
```cpp
void dfs(int a,int b,int c,int d){//a表示当前位置，b表示结束位置，c表示搜索出来的差，d表示状压后的状态
	if(a==b+1){
		if(a!=n+1){//第一遍 DFS 后记录答案
			if(!m[c])  m[c]=++p;
			v[m[c]].push_back(d);
		}
		else{//第二遍 DFS 后记录答案
			int t=m[c];
			for(auto i:v[t])
				vis[i|d]=1;
		}
		return ;
	}
	dfs(a+1,b,c,d);//枚举三种情况
	dfs(a+1,b,c+A[a],d|(1<<a));
	dfs(a+1,b,c-A[a],d|(1<<a));
}
```
### part3. 计算答案

这部分比较简单，枚举 vis 数组中所有状态记录答案。

## 完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,A[25],p,ans;
bool vis[2100000];
map<int,int> m;
vector<int> v[2100000];
void dfs(int a,int b,int c,int d){//a表示当前位置，b表示结束位置，c表示搜索出来的差，d表示状压后的状态
	if(a==b+1){
		if(a!=n+1){//第一遍 DFS 后记录答案
			if(!m[c])  m[c]=++p;
			v[m[c]].push_back(d);
		}
		else{//第二遍 DFS 后记录答案
			int t=m[c];
			for(auto i:v[t])
				vis[i|d]=1;
		}
		return ;
	}
	dfs(a+1,b,c,d);//枚举三种情况
	dfs(a+1,b,c+A[a],d|(1<<a));
	dfs(a+1,b,c-A[a],d|(1<<a));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	int mid=(1+n)>>1;
	dfs(1,mid,0,0);//第一次搜索
	dfs(mid+1,n,0,0);//第二次搜索
	for(int i=1;i<=(1<<n+1);i++)
		ans+=vis[i];//计算答案
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xixike (赞：6)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15379937.html)

# Description

[SP11469 SUBSET - Balanced Cow Subsets
](https://www.luogu.com.cn/problem/SP11469)

# Solution

又是一道折半搜索题。

我们还是枚举一半的数，记录每一种情况的和。

然后爆搜另一半，当和为 $S$ 时，判断前一半是否可以凑出 $S$，如果可以，打个标记即可。

两次凑出 $S$ 时，可能会有重复选用的数组，但其实不用管。

考虑到重复的话，两边同时删去同一个数也相等，但可能选用相同的数会多次出现，所以要打个标记。

dfs 过程中，状压记录一下当前选用了哪些数，加和减状压相同的状态也可以，前面证明过重复的数没有影响了。

这道题由于还需要找到和为 $S$ 的状态有哪些，可以用一个 vector 存一下，但是和太大了。

所以还要用一个 map 离散化一下，不是真正的离散化，因为不需要排序，只需要标记一下即可。

代码还是比较容易理解的。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
#define ri register int

using namespace std;

const int N = 30;
const int S = (1 << 20) + 10;
int n, mid, cnt;
int a[N];
map <int, int> mp;
vector <int> g[S];
bool vis[S];

inline void dfs1(int x, int sum, int now){
	if(x > mid){
		if(!mp.count(sum)) mp[sum] = ++cnt;
		g[mp[sum]].push_back(now);
		return;
	}
	dfs1(x + 1, sum, now);
	dfs1(x + 1, sum + a[x], now | (1 << (x - 1)));
	dfs1(x + 1, sum - a[x], now | (1 << (x - 1)));
}

inline void dfs2(int x, int sum, int now){
	if(x > n){
		if(mp.count(sum)){
			int t = mp[sum];
			for(auto x : g[t])
				vis[x | now] = 1;
		}
		return;
	}
	dfs2(x + 1, sum, now);
	dfs2(x + 1, sum + a[x], now | (1 << (x - 1)));
	dfs2(x + 1, sum - a[x], now | (1 << (x - 1)));
}

int main(){
	scanf("%d", &n);
	for(ri i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	mid = n >> 1;
	dfs1(1, 0, 0), dfs2(mid + 1, 0, 0);
	ri ans = 0;
	for(ri i = 1; i <= (1 << n); i++)
		ans += vis[i];
	printf("%d\n", ans);
	return 0;
}
```

# End

---

## 作者：5k_sync_closer (赞：3)

Meet in the middle。

设选出的两个集合为 $A,B$，$Q=\{A\cup B|\sum\limits_{a\in A}a=\sum\limits_{b\in B}b\}$，容易发现 $|Q|$ 即为所求。

考虑把原序列分成 $X,Y$ 两半。

$$
\begin{aligned}
\sum\limits_{a\in A}a&=\sum\limits_{b\in B}b\\
\sum\limits_{a\in A\cap X}a+\sum\limits_{a\in A\cap Y}a&=\sum\limits_{b\in B\cap X}b+\sum\limits_{b\in B\cap Y}b\\
\sum\limits_{a\in A\cap X}a-\sum\limits_{b\in B\cap X}b&=\sum\limits_{b\in B\cap Y}b-\sum\limits_{a\in A\cap Y}a
\end{aligned}
$$

所以

$$
\begin{aligned}
Q&=\{A\cup B|\sum\limits_{a\in A}a=\sum\limits_{b\in B}b\}|\\
&=\{[(A\cup B)\cap X]\cup[(A\cup B)\cap Y]|\sum\limits_{a\in A\cap X}a-\sum\limits_{b\in B\cap X}b=\sum\limits_{b\in B\cap Y}b-\sum\limits_{a\in A\cap Y}a\}
\end{aligned}
$$

对 $X$ 爆搜出所有 $A\cap X,B\cap X$，记录每个 $\sum\limits_{a\in A\cap X}a-\sum\limits_{b\in B\cap X}b$ 对应的 $(A\cup B)\cap X$。

对 $Y$ 爆搜出所有 $A\cap Y,B\cap Y$，将所有等于 $\sum\limits_{b\in B\cap Y}b-\sum\limits_{a\in A\cap Y}a$ 的 $\sum\limits_{a\in A\cap X}a-\sum\limits_{b\in B\cap X}b$ 的记录的 $(A\cup B)\cap X$ 与此时的 $(A\cup B)\cap Y$ 之并加入 $Q$。

状态压缩一下，用哈希表 + `vector` 维护之。
```cpp
#include <cstdio>
#include <vector>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
int n, m, c, q, a[25];bool v[1048576];
__gnu_pbds::gp_hash_table<int, vector<int> > g;
void F(int x, int s, int S)
{
	if(x >= m) {g[s].push_back(S);return;}
	F(x + 1, s, S);F(x + 1, s + a[x], S | 1 << x);F(x + 1, s - a[x], S | 1 << x);
}
void G(int x, int s, int S)
{
	if(x >= n) {for(auto T : g[s]) v[S | T] = 1;return;}
	G(x + 1, s, S);G(x + 1, s + a[x], S | 1 << x);G(x + 1, s - a[x], S | 1 << x);
}
int main()
{
	scanf("%d", &n);m = n >> 1;for(int i = 0;i < n;++i) scanf("%d", a + i);
	F(0, 0, 0);G(m, 0, 0);for(int i = 1;i < 1 << n;++i) q += v[i];return !printf("%d", q);
}
```


---

## 作者：Ofnoname (赞：3)

[SP11469 SUBSET - Balanced Cow Subsets](https://www.luogu.org/problem/SP11469)

大家一定是在[P3067](https://www.luogu.org/problem/P3067)的推荐里找到这道题的，两道题题面相同，数据范围相同，连样例都一样。但是那道题的代码一般是过不了这道题的，显然可以发现如果折半搜出的两个序列数字都相等的话是会被卡爆的，这是我们就需要更稳更好打的方法。

我们换个角度考虑，`N`只有区区20，所有选或不选的方案数只有$2^N\ = \ 1e6$，如果在两次搜索就把每种选的情况可行性做出来，就可以解决问题。

第一次搜索时，我们记录每一种结果可以被哪些组合拼出来（`N == 20`，组合状态是可以压缩的）。当然一种结果可能被多个组合拼出来，所以要用`vector`记录，而一个结果也可能很大，需要用`map`离散化（编个号就行，不用排序）。

那么第二次搜索时，每当我们得到一个结果`S`，我们是需要前一半产生`-S`的总和来得到方案的，显然`-S`的方案就是`S`的方案反过来而已，是完全等效的，那么我们遍历第一次搜到的所有能使前一半算出`S`的方案，他们的组合与后一半的组合并在一起就是一个可能的答案。

```cpp
#include <bits/stdc++.h>
#define MAX (2000000 + 7)
using namespace std;

int N, mx, mc, ans, a[23], use[MAX];

vector <int> d[MAX];
map <int, int> M;

void DFS1(int i, int sum, int now)//now为压缩状态，sum为当前和 
{
	if (i > mx)
	{
		if (!M.count(sum)) M[sum] = ++mc;//（伪）离散化
		d[M[sum]].push_back(now);//当前now可以拼出sum的和 
		return;
	}
	DFS1(i+1, sum, now);
	DFS1(i+1, sum+a[i], now|(1<<(i-1)));
	DFS1(i+1, sum-a[i], now|(1<<(i-1)));
}

void DFS2(int i, int sum, int now)
{
	if (i > N)
	{
		if (M.count(sum))
		{
			int x = M[sum];//寻找前一半能拼出-sum的组合 
			for (int i = 0; i < d[x].size(); i++)
				use[d[x][i] | now] = 1;//两半组合就是一个可能的一个答案 
		}return;
	}
	DFS2(i+1, sum, now);
	DFS2(i+1, sum+a[i], now|(1<<(i-1)));
	DFS2(i+1, sum-a[i], now|(1<<(i-1)));
}

int main()
{
	scanf("%d", &N), mx = N >> 1;
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	DFS1(1, 0, 0), DFS2(mx + 1, 0, 0);
	for (int i = 1; i <= 1<<N; i++)//遍历每一种 
		ans += use[i];
	printf("%d\n", ans);
}
```



---

## 作者：Suan_CY (赞：2)

# SP11469题解

## [题目传送门](https://www.luogu.com.cn/problem/SP11469)

### 题目重现：

> 给出 $N（1\leq N\leq20）$个数，$M_i (1 \leq M_i \leq 10^8)$，在其中选若干个数，如果这几个数可以分成两个和相等的集合，那么方案数加 $1$。问总方案数。

如果我们把题目简化一下，如果一个集合的每个元素都放到 $A$ 或者 $B$ 中，使得 $A$ 中的元素和 $B$ 中的元素和相等，那么称这个集合是平衡的。

现在题目问集合 $S$ 有多少个**子集**是平衡的。

> ## 思路1：DFS

我们可以暴力 DFS 找出 $S$ 的所有子集，然后挨个验证每个子集是否平衡。但是！！！

$S$ 的子集最多有 $2^{20}$ 个，对于每个子集，假设它的大小为 $x$，那么使用 DFS 验证的时间就是 $O(2^{x})$，这个时间复杂度显然通过不了此题，那么考虑更优的方法。

> ## 思路2：折半搜索（也是本篇重点）

### Part $1$： 什么是折半搜索

折半搜索，顾名思义，就是把将要搜索的问题分成两半，分别进行搜索，这样原本时间复杂度为 $O(2^{n})$ 就能降到 $O(2^{\frac{n}{2}})$。

### Part $2$：分析此题如何使用折半搜索解决此题

既然我们用了更高级的算法，那么显然不能用上面 DFS 的思路来解题。

我们又能想到，对于 $S$ 里的每一个元素我们都有 $3$ 种选择：
> 1 放到集合 $A$ 中。
>
> 2 放到集合 $B$ 中。
>
> 3 不选。

思考：为什么能不选？

因为这个思路是枚举集合 $S$，题目要求找的是 $S$ 的子集。那么对于 $S$ 的子集来说，当然可以有一些 $S$ 的元素不在这个子集中，所以可以不选。

这种思路直接搜索的时间复杂度是 $O(3^{20})$，我们也是无法接受的，故折半搜索，分成两部分搜索，把三种情况**全部讨论一遍**。那应该怎么合并呢？

设 $A$ 集合中的和为 $sum1$，$B$ 集合中的和为 $sum2$（前半部分的 $sum$ 大写，后半部分的 $sum$ 小写）。

那么对于前半部分，可以知道两部分的差为 $SUM1-SUM2$，那么如果与后半部分的 $sum2-sum1$ 相等，可知两部分合起来，$SUM1+sum1$ 和 $SUM2+sum2$ 就相等了。

那我们不难想到，使用 map 或者**二分**等手段都能完成此题，但还是过不了此题，为什么？

对于这个问题，可以音速举出反例：

没错，对于集合 $1\space1\space2\space2$ 来说。

两个 $1$ 分到 $A$ 集合还是 $B$ 集合是**不同的分法**，但是都是对于**同一个子集的讨论**（这里的讨论是指看一下这个子集是否平衡），所以就导致一个自己被统计了多次，产生了错误。

所以可以采用状态压缩（状态压缩，简称“状压”，是指用二进制表示当前状态的一种节省空间的方式）记录一下子集是什么样的，防止重复统计，状压代码如下：
```cpp
void dfs1(int pos,ll sum1,ll sum2,int now){
    if(pos>n/2){
        if(num[sum1-sum2]==0) num[sum1-sum2]=++idx;
        v[num[sum1-sum2]].push_back(now);
        return;
    }
    dfs1(pos+1,sum1,sum2,now);
    dfs1(pos+1,sum1+a[pos],sum2,now|(1<<pos-1));
    dfs1(pos+1,sum1,sum2+a[pos],now|(1<<pos-1));
}
```
而 dfs2 中我们可以使用 $ans$ 数组来记录某个子集是否平衡，代码如下：

```cpp
void dfs2(int pos,ll sum1,ll sum2,int now){
    if(pos>n){
        if(num.count(sum2-sum1)){
            int tidx=num[sum2-sum1];
            for(int i=0;i<v[tidx].size();i++){
                ans[now|v[tidx][i]]=1;
            }
        }
        return;
    }
    dfs2(pos+1,sum1,sum2,now);
    dfs2(pos+1,sum1+a[pos],sum2,now|(1<<pos-1));
    dfs2(pos+1,sum1,sum2+a[pos],now|(1<<pos-1));
}
```

在两次 dfs 结束以后，在 main 函数中遍历 $ans$ 数组有多少个 $1$ 即可（因为用了状压）。

最终代码：

```cpp
#include"bits/stdc++.h"
#define ll long long
#define CLOSE ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define Labs(x) ((x)>0?(x):-(x))
using namespace std;
ll n,a[25],idx;
vector<int> v[2000005];
map<ll,int> num;
bool ans[2000005];
void dfs1(int pos,ll sum1,ll sum2,int now){
    if(pos>n/2){
        if(num[sum1-sum2]==0) num[sum1-sum2]=++idx;
        v[num[sum1-sum2]].push_back(now);
        return;
    }
    dfs1(pos+1,sum1,sum2,now);
    dfs1(pos+1,sum1+a[pos],sum2,now|(1<<pos-1));
    dfs1(pos+1,sum1,sum2+a[pos],now|(1<<pos-1));
}
void dfs2(int pos,ll sum1,ll sum2,int now){
    if(pos>n){
        if(num.count(sum2-sum1)){
            int tidx=num[sum2-sum1];
            for(int i=0;i<v[tidx].size();i++){
                ans[now|v[tidx][i]]=1;
            }
        }
        return;
    }
    dfs2(pos+1,sum1,sum2,now);
    dfs2(pos+1,sum1+a[pos],sum2,now|(1<<pos-1));
    dfs2(pos+1,sum1,sum2+a[pos],now|(1<<pos-1));
}
int main(){
	CLOSE
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	}
	dfs1(1,0,0,0);
	dfs2(n/2+1,0,0,0);
	int res=0;
	for(int i=1;i<(1<<n);i++) res+=ans[i];
	cout<<res;
	return 0;
}
```
最后附上双倍经验和折半搜索板子题：

[双倍经验](https://www.luogu.com.cn/problem/P3067)

[折半搜索板子题](https://www.luogu.com.cn/problem/P4799)

---

## 作者：ivyjiao (赞：2)

[双倍经验](https://www.luogu.com.cn/problem/P3067)

思路：

$O(3^n)$ 会 TLE，而 $O(3^{\frac n 2})$ 不会，所以我们采用折半搜索。

由于

$$A=B$$

我们设前一半在 $A$ 中放的数为 $l_1$，在 $B$ 中放的数为 $r_1$，后一半在 $A$ 中放的数为 $l_2$，在 $B$ 中放的数为 $r_2$，那么

$$l_1+l_2=r_1+r_2$$

所以

$$l_1-r_1=r_2-l_2$$

即

$$|l_1-r_1|=|l_2-r_2|$$

因此，我们只需要记录每一种 $|l_1-r_1|$ 代表的方案，再将它们与每一种  $|l_2-r_2|$ 匹配即可。

为什么要化成最后一个式子？因为数组不允许负数下标。

代码：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include<vector>
using namespace std;
int n,a[21],realans,cnt;
bool ans[2000001];
unordered_map <int,int> mp;
vector <int> G[2000001];
void dfs1(int now,int l,int r,int galley){
    if(now==n/2+1){
        if(!mp[abs(l-r)]) cnt++,mp[abs(l-r)]=cnt;//离散化
        G[mp[abs(l-r)]].push_back(galley);//记录每一种方案
        return;
    }
    dfs1(now+1,l,r,galley);
    dfs1(now+1,l+a[now],r,galley|(1<<(now-1)));//状压
    dfs1(now+1,l,r+a[now],galley|(1<<(now-1)));//状压*2
}
void dfs2(int now,int l,int r,int galley){
    if(now==n+1){
        int aa=mp[abs(l-r)];//必须加这句话！不然 TLE！
        for(int i=0;i<G[aa].size();i++) ans[G[aa][i]|galley]=1;//对于每一种可能的方案，将其标为“可能”。
        return;
    }
    dfs2(now+1,l,r,galley);
    dfs2(now+1,l+a[now],r,galley|(1<<(now-1)));//状压*3
    dfs2(now+1,l,r+a[now],galley|(1<<(now-1)));//状压*4
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs1(1,0,0,0);
    dfs2(n/2+1,0,0,0);
    for(int i=1;i<=(1<<n);i++) realans+=ans[i];//统计有多少种可能的方案。
    cout<<realans;
}
```


---

## 作者：DukeLv (赞：2)

这道题是一个折半搜索(meet in the middle)的题,中间还有一部分状压.(n<20导致一开始就会往状压上想,发现其实爆搜也不会超时很多)

因为爆搜不会超时很多,我们考虑剪枝,这时折半搜索的优势体现出来了.一开始是20,而折半搜索可以用空间换时间,把20的范围变成两个10,这样就可以把3^20变为2* 3^10了.

具体怎么做呢?这个题有三种状态:

不选,放左边,放右边.

爆搜的时候肯定要搜这三种情况.这个地方优化不了,所以我们要先枚举前一般的状态,把状态和答案全存下来,(需要用状压来记录当前的选择).存在map中留着以后使用.然后搜索后一半,每次去map中查找,看有没有相同的状态,然后直接打上标记,(因为可能重复计算),这样的话就可以满足不重不漏.

剩下就是代码细节了,大家可以自己看看,用状压dp的一些基本操作就行了.

代码:

```

#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#include<vector>
#include<map>
#include<complex>
#include<cstring>
using namespace std;
#define duke(i,a,n) for(int i = a;i <= n;i++)
#define lv(i,a,n) for(int i = a;i >= n;i--)
#define clean(a) memset(a,0,sizeof(a))
#define cp complex<db>
#define enter puts("")
const long long INF = 1LL << 60;
const double eps = 1e-8;
typedef long long ll;
typedef double db;
template <class T>
void read(T &x)
{
    char c;
    bool op = 0;
    while(c = getchar(), c < '0' || c > '9')
        if(c == '-') op = 1;
    x = c - '0';
    while(c = getchar(), c >= '0' && c <= '9')
        x = x * 10 + c - '0';
    if(op) x = -x;
}
template <class T>
void write(T x)
{
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}
int vis[2000003];
int n,m,cnt;
int a[25];
map <int,int> mp;
vector <int> dist[2000006];
void dfs1(int num,ll tot,int now)
{
	if(num > m)
	{
		if(mp.find(tot) == mp.end()) mp[tot] = ++cnt;
		dist[mp[tot]].push_back(now);
		return;
	}
	dfs1(num + 1,tot,now);
	dfs1(num + 1,tot + a[num],now | (1 << (num - 1)));
	dfs1(num + 1,tot - a[num],now | (1 << (num - 1)));
}
void dfs2(int num,int tot,int now)
{
	if(num > n)
	{
		if(mp.find(tot) == mp.end()) return;
		int id = mp[tot];
		for(int i = 0;i < (int)dist[id].size();i++)
		vis[dist[id][i] | now] = 1;
		return;
	}
	dfs2(num + 1,tot,now);
	dfs2(num + 1,tot + a[num],now | (1 << (num - 1)));
	dfs2(num + 1,tot - a[num],now | (1 << (num - 1)));
}
int main()
{
	read(n);
	m = n >> 1;
	duke(i,1,n)
	read(a[i]);
	dfs1(1,0,0);
	dfs2(m + 1,0,0);
	int ans = 0;
	duke(i,1,(1 << n))
	{
		ans += vis[i];
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：_Weslie_ (赞：1)

双倍经验：[P3067](https://www.luogu.com.cn/problem/P3067)。

## 题意简述

给定长度为 $n$ 的一个序列 $a$，对于每一个数 $a_i$，可以把它加入 $A$ 和 $B$ 两个集合之一或者不加入任何一个集合，要求所有数处理完后，$A$ 与 $B$ 两个集合中数的和相等，求方案数。

$n\le20$ 且 $a_i\le 10^8$。

## 思路

对于一个数 $a_i$，在最后有三种状态：

- 它在 $A$ 集合。
- 它在 $B$ 集合。
- 它不在任何一个集合中。

所以如果我们暴搜复杂度是 $\operatorname{O}(3^n)$ 的。而 $3^{20}=3486784401$，因此暴搜自然过不去。

我们只好使用折半搜索将时间复杂度降到 $\operatorname{O}(3^{\frac{n}{2}})$。

如何折半搜索？

首先我们将序列分成 $[1,\dfrac{n}{2}]$ 和 $[\dfrac{n}{2}+1,n]$ 两部分，分别搜索。

我们首先证明一个等式：设 $[1,\dfrac{n}{2}]$ 区间内 $A$ 集合的数的和为 $p_1$，$B$ 集合的和为 $q_1$。同理 $[\dfrac{n}{2}+1,n]$ 区间内 $A$ 集合的数的和为 $p_2$，$B$ 集合的和为 $q_2$。

则 $q_1-p_1=p_2-q_2$。

证明：由题意可得 $p_1+p_2=q_1+q_2$，移项可得上面的式子。

对于 $[1,\dfrac{n}{2}]$ 的部分，我们先暴力搜索，然后当搜索完成后，记录 $q_1-p_1$ 的值。

对于 $[\dfrac{n}{2}+1,n]$ 的部分，我们也是先暴力搜索，同时记录 $p_2-q_2$。在搜索完成后进行匹配，得到答案。

写出代码：

```
map<long long,int>mp; 
void dfs1(int now,long long sum){
	if(now==n/2+1){
		mp[sum]++;
		return; 
	}
	dfs1(now+1,sum);
	dfs1(now+1,sum+a[now]);
	dfs1(now+1,sum-a[now]);
}
long long ans;
void dfs2(int now,long long sum){
	if(now==n+1){
		if(sum!=0)ans+=mp[sum];//0不能统计
		return;
	}
	dfs2(now+1,sum);
	dfs2(now+1,sum-a[now]);
	dfs2(now+1,sum+a[now]);
}
```

但是这个代码是错误的。

对于序列 $a=\{1,2,1,2\}$ 而言：

我们将 $a_1$ 和 $a_4$ 放入 $A$ 集合，其余的放入 $B$ 集合和 $a_2$ 和 $a_3$ 放入 $A$ 集合中是一种方案，因为我们都是选择了相同的 $4$ 个数。

显然这个代码会重复统计。

所以我们要用一个二进制数，存储每个点是否被选。$1$ 代表选了。然后按照二进制位把它压成一个十进制数。如果统计答案是这个状态已经算过了，就不算了。

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n,a[25];
map<int,vector<int> >mp; 
void dfs1(int now,long long sum,int S){
	if(now==n/2+1){
		mp[sum].push_back(S);
		return; 
	}
	dfs1(now+1,sum,S);
	dfs1(now+1,sum+a[now],S|(1<<(now-1)));
	dfs1(now+1,sum-a[now],S|(1<<(now-1)));
}
long long ans;
bool b[1048577];
void dfs2(int now,long long sum,int S){
	if(now==n+1){
		if(mp.count(sum)){
			for(int S2:mp[sum]){
				if(b[S+S2]==0)ans++;
				b[S+S2]=1;
//				printf("%d\n",S+S2);
			}
		}
		return;
	}
	dfs2(now+1,sum,S);
	dfs2(now+1,sum-a[now],S|(1<<(now-1)));
	dfs2(now+1,sum+a[now],S|(1<<(now-1)));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	dfs1(1,0,0);
	dfs2(n/2+1,0,0);
	printf("%d",(ans-1));
	
	return 0;
}
```

---

## 作者：dyc2022 (赞：1)

双倍经验：P3067。

***

一道双向搜索题。先讲一下常规做法，再讲一下优化。

原问题：对于每个元素，可以选择选入 $A$ 集合，选入 $B$ 集合，或不选。要使得每个集合的元素之和相等。

转换成：对于 $n$ 个元素的集合 $S$（可能是多重集）的每个元素 $S_i$，都有一个权值 $p_i$，且满足 $\forall p_i \in \{-1,0,1\}$。问有多少种 $p$ 序列，使得：

$$\sum^{n}_{i=1}S_ip_i = 0$$

然后，就变成了存在多少种 $p$ 序列，使：

$$\sum^{\frac{n}{2}}_{i=1}S_ip_i = x$$

且

$$\sum^{n}_{i=\frac{n}{2}+1}S_ip_i = -x$$

于是这就是双向搜索的板子了。先在前半段搜出所有的和，然后在后半段搜出和，看有没有前半段的相反数。

因为数字可能很大，也可能是负数，因此要用 `map`。

还有，由于它问的是有多少个集合可以拆分，而不是问有多少种拆分方法，因此要进行查重，对于同一个子集的不同拆分方案，要只算一种。

复杂度为 $O(3^{\frac{n}{2}})$。但是，由于是用到了 `map`，所以常数极大！[不 AC 代码](https://www.luogu.com.cn/record/124018125)如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[24],n,mid,ans;
struct Node{vector<int>id;};
map<int,Node> mp;
int f[3049999];
void dfs1(int x,int sum,int k)
{
	if(x>mid)
	{
		mp[sum].id.push_back(k);
		return;
	}
	dfs1(x+1,sum,k);
	dfs1(x+1,sum+a[x],k+(1<<x));
	dfs1(x+1,sum-a[x],k+(1<<x));
}
void dfs2(int x,int sum,int k)
{
	if(x>n)
	{
		int len=mp[-sum].id.size();
		for(int i=0;i<len;i++)
		{
			int tmp=k+mp[-sum].id[i];
			if(!f[tmp])
			{
				f[tmp]=1;
				ans++;
			}
		}
		return;
	}
	dfs2(x+1,sum,k);
	dfs2(x+1,sum+a[x],k+(1<<x));
	dfs2(x+1,sum-a[x],k+(1<<x));
}
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	mp.clear();
	mid=n>>1;
	dfs1(1,0,0);
	dfs2(mid+1,0,0);
	printf("%lld",ans-1); 
	return 0;
}
```

（这个代码可以 AC P3067）

***

考虑优化：

由于 `map` 是使用红黑树来维护，因此 `map` 存的数字越大，用的时间也越多。

于是，使用离散化就可以轻松 AC。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 4096000
using namespace std;
int n,a[40],mid;
map<int,int> mp;
vector<int> id[N];
int f[3020202],ans,cnt;
void dfs1(int x,int sum,int v)
{
	if(x>mid)
	{
		if(mp[sum]==0)mp[sum]=++cnt;
		id[mp[sum]].push_back(v);
		return;
	}
	dfs1(x+1,sum,v);
	dfs1(x+1,sum+a[x],v|(1<<(x-1)));
	dfs1(x+1,sum-a[x],v|(1<<(x-1)));
}
void dfs2(int x,int sum,int v)
{
	if(x>n) 
	{
		int xxx=mp[-sum];
		if(xxx==0)return;
		int xx=id[xxx].size();
		for(int i=0;i<xx;i++)
		{
			int t=v|id[xxx][i];
			if(!f[t])
			{
				f[t]=1;
				ans++;
			}
		}
		return;
	}
	dfs2(x+1,sum,v);
	dfs2(x+1,sum+a[x],v|(1<<(x-1)));
	dfs2(x+1,sum-a[x],v|(1<<(x-1)));
}
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	mid=n>>1;
	mp.clear();
	dfs1(1,0,0);
	dfs2(mid+1,0,0);
	printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：Milthm (赞：0)

我们发现直接枚举子集是 $3^{n}$ 的，虽然 $n$ 只有 $20$，但是还是过不去。

所以考虑折半搜索，先搜前一半，然后把算出来的和离散化，状压之后用 `vector` 存储对应的状态。然后再搜索后一半，搜索的内容和前一半一样，在最后标记一下所有可能的状态，最后统计一遍有标记的位置就好了。

有一些要注意的：

- 可行方案要去重。

- 数组不要开小。

- 位运算的优先级较低。

时间复杂度的话，因为一个和对应的状态最多只有 $2^{\frac{n}2}$ 个，所以时间复杂度为 $O(2^{\frac{n}2}\times 3^{\frac{n}2})=O(6^{\frac{n}2})$，可以通过本题。


```cpp
#include<bits/stdc++.h>
#define N 2000005
using namespace std;
int n,a[N],idx,ans[N];
vector<int>ans1[N];
unordered_map<int,int>qwq;
void dfs(int x,int sum,int t){
	if(x>n/2){
		if(!qwq[sum])qwq[sum]=++idx;
		ans1[qwq[sum]].push_back(t);return;
	}
	dfs(x+1,sum,t);
	dfs(x+1,sum+a[x],t|(1<<x-1));
	dfs(x+1,sum-a[x],t|(1<<x-1));
}
void dfs2(int x,int sum,int t){
	if(x>n){
		int r=qwq[sum];
		if(r)for(int i=0;i<ans1[r].size();++i)ans[ans1[r][i]|t]=1;
		return;
	}
	dfs2(x+1,sum,t);
	dfs2(x+1,sum+a[x],t|(1<<x-1));
	dfs2(x+1,sum-a[x],t|(1<<x-1));
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    dfs(1,0,0);dfs2(n/2+1,0,0);int sum=0;
    for(int i=1;i<(1<<n);++i)sum+=ans[i];
    cout<<sum;
    return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

### SUBSET - Balanced Cow Subsets  

#### *Description*

**题目大意**：从 $n$ 个数中选若干个数，使得这若干个数可以被分成两个和相等的集合，求选数的方案数。

**数据规模**：$1\leq n\leq20$，每个数都不超过 $10^8$。
 
#### *Solution*

很每个数有 3 种情况：作为选出数分出的第一个集合，作为选出数分出的第二个集合，或不作为选出的数。

那么第一种方法，$3^n$ 暴力搜索，但这样一定会 TLE。

所以考虑折半搜索，我们设前半段分到第一集合的数和为 $a_1$，第二集和的和为 $b_1$，后半段为 $a_2$ 和 $b_2$，因为和相等，所以 $a_1+a_2=b_1+b_2$，移项得 $a_1-b_1=b_2-a_2$。

所以我们分两次搜索时各自记录当前所选数的 $a,b$ 之差，把第一次搜索得到的所有 $a_1-b_1$ 放到一个 `map` 里面，第二次在 `map` 里面找 $b_2-a_2$ 的值。

问题在于：答案求的是选数的方案，而不是分成两个相等集合的方案。这里很多题解没说清楚，为什么要用一个二进数来看选不选。

很喜欢[ MistZero ](https://www.luogu.com.cn/user/487752)的那篇题解，设 4 个数为：

```
3 3 3 3
```

如果单纯是选两个和相等的集合的方案，选 $a_1,a_3$ 作为第一个集合，$a_2,a_4$ 作为第二个集合，与选 $a_1,a_2$ 作为第一个集合，选 $a_3,a_4$ 作为第二个集合是不同的两种选法，但是在这道题目看来，这两种选法都选了 $a_1,a_2,a_3,a_4$，所以被视为一种方案。所以我们求答案要用二进制枚举每个数选或不选，这样才不会有重复方案

#### *Code*

洛谷寄了，所以只有 vjudge 的 ac 记录

![](https://pic.imgdb.cn/item/64e75853661c6c8e54bd22ab.png)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 20
#define MAXS (1 << 20)
int n, cnt, a[MAXN + 5];
map<int, int> mp;
vector<int> G[MAXS + 5];
bool vis[MAXS + 5];
void dfs1(int id, int sum, int now) {
	if (id > n / 2) {
		if (mp.count(sum) == 0) mp[sum] = ++ cnt;
		G[mp[sum]].push_back(now);
		return;
	}
	dfs1(id + 1, sum, now);
	dfs1(id + 1, sum + a[id], now | (1 << (id - 1)));
	dfs1(id + 1, sum - a[id], now | (1 << (id - 1)));
	return;
}
void dfs2(int id, int sum, int now){
	if(id > n){
		if(mp.count(sum) != 0){
			int t = mp[-sum];
			for(auto S : G[t]) vis[S | now] = 1;
		}
		return;
	}
	dfs2(id + 1, sum, now);
	dfs2(id + 1, sum + a[id], now | (1 << (id - 1)));
	dfs2(id + 1, sum - a[id], now | (1 << (id - 1)));
	return;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	dfs1(1, 0, 0);
	dfs2(n / 2 + 1, 0, 0);
	int ans = 0;
	for(int i = 1; i <= (1 << n); i ++) ans += vis[i];
	printf("%d", ans);
	return 0;
}
```

---

## 作者：OrezTsim (赞：0)

考虑枚举 $3^n$ 种情况，用三进制数表示。

对于每一位，$0$ 表示不放，$1$ 表示放入第一个集合，$2$ 表示放入第二个集合。

这样显然会 TLE。考虑 meet in the middle。

考虑枚举前 $3^{\left\lfloor\frac{n}{2}\right\rfloor}$ 种情况，开一个数组 / map 处理出所有可能的情况。

随后枚举后 $3^{n-\left\lfloor\frac{n}{2}\right\rfloor}$ 种情况，和前面处理出的答案合并。

考虑如何合并。设前半段的第一个集合和为 $a$，第二个集合和为 $b$；后半段的第一个集合为 $a'$，第二个集合和为 $b'$，则有 $a+a'=b+b'$。

移项有 $a-b=b'-a'$，那么只要将答案用差为索引记录即可。

但是我们会发现一个情况，就是第一个集合和第二个集合只是我们规定的顺序，本质上它是无序对；除此之外，你不可以选两个空集。那么答案就是 $\dfrac{ans-1}{2}$ 了吗？

其实不是。

看题目，发现要求选数的方案而非具体的安排方案，例如：

```
3 3 3 3
```

对于这四个数，分段为 `3 3/3 3`，前半段和后半段内共可以组成 $2$ 个合法答案。

你会发现，$a_1+a_2=a_3+a_4$ 本质上和 $a_1+a_3=a_2+a_4$ 是一种选数方案。

考虑在枚举状态时加入选数的状态，用二进制 $0/1$ 来表示。

开一个数组记录是否计算过一种方案的答案即可。

复杂度是 $O(3^{\left\lfloor\frac{n}{2}\right\rfloor}\times2^{\left\lfloor\frac{n}{2}\right\rfloor})$ 即 $O(6^{\left\lfloor\frac{n}{2}\right\rfloor})$ 的。$3$ 为枚举集合分布，$2$ 为记录的选数方案。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
unordered_map <int, int> id; bool kk[N];
int n, idx, a[N]; vector <int> kel[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
    int mid = n >> 1, lim = 1, res = 0; for (int i = 1; i <= mid; ++i) lim *= 3;
    for (int s = 0; s < lim; ++s) {
        int tmp = s, sum = 0, sta = 0;
        for (int cnt = 1; cnt <= mid; ++cnt, sta = tmp % 3? (sta << 1 | 1) : (sta << 1), tmp /= 3)
            if ((tmp % 3) & 1) sum += a[cnt]; else if (tmp % 3) sum -= a[cnt];
        if (!id[sum]) id[sum] = ++idx;
        kel[id[sum]].emplace_back(sta);
    }
    int lst = mid; mid = n - mid, lim = 1;
    for (int i = 1; i <= mid; ++i) lim *= 3;
    for (int s = 0; s < lim; ++s) {
        int tmp = s, sum = 0, sta = 0;
        for (int cnt = 1; cnt <= mid; ++cnt, sta = tmp % 3? (sta << 1 | 1) : (sta << 1), tmp /= 3)
            if ((tmp % 3) & 1) sum -= a[cnt + lst]; else if (tmp % 3) sum += a[cnt + lst];
        int curid = id[sum]; if (!curid) continue;
        for (auto dk: kel[curid]) {
            if (!((dk << mid) + sta)) continue;
            if (kk[(dk << mid) | sta]) continue;
            kk[(dk << mid) | sta] = true, ++res;
        }
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：Sooke (赞：0)

### 解题思路

首先你要做过[这题](https://www.luogu.org/problemnew/show/P3067)。

两题其实是本质相同的。因为对于每一个物品，要么不选，要么选，选了后呢，要么放一边，要么放另一边。

也就是说，一个物品对应 $3$ 种状态。

注意 $n \leqslant 20$，直接暴枚 $3^n$ 肯定是凉凉的。在这种情况下，数据范围小，暴搜又不行，考虑**折半搜索**。

什么是折半搜索？其实是有一种**分治**的思想，把整个问题分成两部分，两部分分别做完后，再合并。

对于这道题而言，我们分别暴枚两半物品的选取状态，把是否选择用**二进制**表示，同时记录权值之和（放一边加权值，放另一边减权值）。最后，枚举两半权值之和为相反数的，计算对答案的贡献。

在搜索部分，时间复杂度变为了 $3^{\frac{n}{2}}$，但合并呢？

也许有很多人，代码直接粘过来 $TLE$ 了。看到下面这个数据：

```
20
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
```
输出应该是 $524287$，可程序跑出来的时间就有了明显的差距，包括另一篇题解，也超时了。

这是什么原因？请仔细思考合并的复杂度。

我们考虑上面那个数据分成两半，每一半可能出现的和无非在 $[-10,\ 10]$ 之间，程序告诉我们 $0$ 出现了 $8953$ 次，$1,\ -1$ 出现了 $8350$ 次。合并的时候，因为互为相反数的都要枚举，仅观察 $0,\ 1,\ -1$，枚举的次数就已经达到了 $8953 \times 8953 + 8350 \times 8350$ 次！

瓶颈就在于相同的和出现次数过多，我们知道每个和都对应一个二进制状态，实际上，对于这类数据，存在大量相同的和，对应的二进制状态也是相同的，这就没必要再做一遍了。

优化方案也十分明朗了，只需要用一个 $set$，避免权值和、状态都相同的重复。

时间复杂度不会证，反正下界是 $3^{\frac{n}{2}}$。

### 代码实现

先给权值排个序，使剪枝更加有效。

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

const int maxN = 100005;

int n, m, numA, numB, ans, cnt, w[maxN];
std::pair<int, int> a[maxN], b[maxN];
std::set<std::pair<int, int> > setA, setB;
bool used[1 << 21];

void dfs1(int dep, int now, int stat) {
    if (dep > m) {
        if (setA.count(std::make_pair(now, stat))) { return; }
        setA.insert(std::make_pair(now, stat));
        a[++numA] = std::make_pair(now, stat);
        return;
    }
    dfs1(dep + 1, now, stat);
    dfs1(dep + 1, now + w[dep], 1 << dep | stat);
    dfs1(dep + 1, now - w[dep], 1 << dep | stat);
}
void dfs2(int dep, int now, int stat) {
    if (dep == m) {
        if (setB.count(std::make_pair(-now, stat))) { return; }
        setB.insert(std::make_pair(-now, stat));
        b[++numB] = std::make_pair(-now, stat);
        return;
    }
    dfs2(dep - 1, now, stat);
    dfs2(dep - 1, now + w[dep], 1 << dep | stat);
    dfs2(dep - 1, now - w[dep], 1 << dep | stat);
}

int main() {
    scanf("%d", &n); m = n / 2;
    for (int i = 1; i <= n; i++) { scanf("%d", &w[i]); } std::sort(w + 1, w + n + 1);
    dfs1(1, 0, 0); std::sort(a + 1, a + numA + 1);
    dfs2(n, 0, 0); std::sort(b + 1, b + numB + 1); a[0].first = -19260817;
    for (int i = 1, j = 1, lst; i <= numA; i++) {
        if (a[i - 1].first == a[i].first) { j = lst; } else {
            for (; j <= numB && b[j].first < a[i].first; j++); lst = j;
            if (j > numB) { break; }
        }
        for (; j <= numB && b[j].first == a[i].first; j++) { ans += !used[b[j].second | a[i].second]; used[b[j].second | a[i].second] = true; }
    }
    printf("%d\n", ans - 1);
    return 0;
}
```

---

## 作者：mrclr (赞：0)

[嘟嘟嘟spoj](https://www.spoj.com/problems/SUBSET/en/)
[嘟嘟嘟vjudge](https://vjudge.net/problem/SPOJ-SUBSET)
[嘟嘟嘟luogu](https://www.luogu.org/problemnew/show/SP11469)


这个数据范围都能想到是折半搜索。

但具体怎么搜呢？

还得扣着方程模型来想：我们把题中的两个相等的集合分别叫做左边和右边，令序列前一半中放到左边的数为$a$，右边的数为$b$，后一半同理为$c$和$d$。则我们要找的就是满足$a + c = b + d$的选取方案。

然后变形$a - b = d - c$。因此我们只要在前一半枚举$a, b$，存起来，然后在后一半枚举$c, d$，然后查找$d - c$是否出现过。

注意不是每一个数都要选，所以枚举的时候有三种情况：1.不选。2.选到左边。3.选到右边。所以复杂度为$O(3 ^ {\frac{n}{2}})$。

还有一点就是状态判重，这个用二进制表示就行。
具体实现就是用$map$离散化$a - b$，然后因为$a - b$可能由好多种选取方案得来的，所以开一个$vector$记录每一个$a - b$对应的状态。统计答案的时候用一个$bool$数组判重即可。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 22;
const int maxp = 1.2e6 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, m;
ll a[maxn];

int cnt = 0;
map<int, int> mp;
vector<int> v[maxp];
bool vis[maxp];

void dfs1(int stp, ll tot, int now)
{
  if(stp > m)
    {
      if(mp.find(tot) == mp.end()) mp[tot] = ++cnt;
      v[mp[tot]].push_back(now); return;
    }
  dfs1(stp + 1, tot, now);
  dfs1(stp + 1, tot + a[stp], now + (1 << (stp - 1)));
  dfs1(stp + 1, tot - a[stp], now + (1 << (stp - 1)));
}
void dfs2(int stp, ll tot, int now)
{
  if(stp > n)
    {
      if(mp.find(tot) == mp.end()) return;
      int id = mp[tot];
      for(int i = 0; i < (int)v[id].size(); ++i) vis[v[id][i] | now] = 1;
      return;
    }
  dfs2(stp + 1, tot, now);
  dfs2(stp + 1, tot + a[stp], now + (1 << (stp - 1)));
  dfs2(stp + 1, tot - a[stp], now + (1 << (stp - 1)));
}

int main()
{
  n = read(); m = n >> 1;
  for(int i = 1; i <= n; ++i) a[i] = read();
  dfs1(1, 0, 0); dfs2(m + 1, 0, 0);
  int ans = 0;
  for(int i = 1; i < maxp; ++i) ans += (int)vis[i];
  write(ans), enter;
  return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

奇妙 meet in the middle。

首先不难想到的是考虑一种划分 $T=T_0+T_1$，那么每个数的三种状态为 $\in T_0,\in T_1,\notin T$。直接暴力枚举是 $\mathcal{O}(3^{n})$ 的，看到 $n\le 20$ 且是选择类问题，考虑 meet in the middle。那么分两半枚举数的状态，同时维护 $sum(T_0)-sum(T_1)$，然后合并一下就好了。

问题来了，对于一个合法的子集 $T\in S$，可能有多种合法的划分 $T=T_0+T_1$，那么一个 $T$ 可能会被计数多次。我们考虑做一个去重。所以维护一个状态 $st$ 表示每个数是否被选进了 $T$，无论它是 $\in T_0$ 还是 $\in T_1$ 都是一样的。那么所有 $st$ 相同的划分也只能算一次，所以说搜第一半的时候与将每种 $sum(T_0)-sum(T_1)$ 对应的划分方案的 $st_0$ 放到一个 vector 里面，搜出另一半 $st_1$ 的时候，在 $-sum$ 对应的 vector 里面找出所有被前一半凑出来的 $st_0$，将 $st_0\otimes st_1$（$\otimes$ 表示或）对应的选法标为合法，最后统计合法位置个数。复杂度 $\mathcal{O}(3^{\lceil\frac{n}{2}\rceil}2^{\lceil\frac{n}{2}\rceil})=\mathcal{O}(6^{\lceil\frac{n}{2}\rceil})$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
using i64 = int64_t;
using db = double;
using std::cin;
using std::cout;
constexpr int N = 25;

int n, m;
std::array<i64, N> a;
std::array<bool, 1 << 21> ans;
__gnu_pbds::cc_hash_table<i64, std::vector<int> > mp;

void dfs(int u, i64 sum, int s, int ed, bool type) {
   if (u > ed) {
		if (!type) mp[sum].emplace_back(s);
      else for (auto i : mp[-sum]) ans[s | i] = true;
      return ;
   }
   dfs(u + 1, sum, s, ed, type);
   dfs(u + 1, sum + a[u], s | (1 << u - 1), ed, type);
   dfs(u + 1, sum - a[u], s | (1 << u - 1), ed, type);
   return ;
}

int main() {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   cin >> n, m = n >> 1;
   for (int i = 1; i <= n; ++i) cin >> a[i];
   dfs(1, 0, 0, m, false), dfs(m + 1, 0, 0, n, true);
   i64 ret = 0;
   for (int i = 1; i < (1 << n); ++i) ret += ans[i];
   cout << ret << "\n";
   return 0;
}

---

## 作者：wwxxbb (赞：0)

## 思路：Meet in the middle

考虑将原序列分成两半，则对于每个数有三种情况：加入 A 集合，加入 B 集合，或者两个都不加。这样的复杂度是 $\mathcal{O}(3^n)$，考虑用折半搜索优化到 $\mathcal{O}(3^{\frac{n}{2}})$。

我们枚举一半，用 map 记录每种情况的和，再枚举另一半，判断与前一半是否能凑成 $sum$，可以的话打个标记。

我们状压记录当前选了哪些数，但是由于一种结果可能被多个组合拼出来，所以要用 vector 记录一下状态。

效率挺高的，~~但是我用 unordered_map 大肠~~。

貌似还可以用 bitset 优化，~~但是我把 bitset 当 bool 数组了~~。

[双倍经验](https://www.luogu.com.cn/problem/P3067)。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 21, M = (1 << 20) + 1;

int n, mid, a[N];
int cnt, ans;
bitset<M> st;
unordered_map<int, int> mp;
vector<int> s[M];

void dfs1(int x, int sum, int now) {
    if (x > mid) {
        int &t = mp[sum];
        if (!t) t = ++ cnt; // 伪离散化
        s[t].emplace_back(now);
        return;
    }
    dfs1(x + 1, sum, now);
    dfs1(x + 1, sum + a[x], now | 1 << x - 1);
    dfs1(x + 1, sum - a[x], now | 1 << x - 1);
}

void dfs2(int x, int sum, int now) {
    if (x > n) {
        int t = mp[sum];
        if (t) for (auto i : s[t])
        	st[now | i] = 1;
        return;
    }
    dfs2(x + 1, sum, now);
    dfs2(x + 1, sum + a[x], now | 1 << x - 1);
    dfs2(x + 1, sum - a[x], now | 1 << x - 1);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n; mid = n >> 1;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    dfs1(1, 0, 0);
    dfs2(mid + 1, 0, 0);
    for (int i = 1; i <= 1 << n; i ++)
        ans += st[i];
    return cout << ans, 0;
}
```

---

