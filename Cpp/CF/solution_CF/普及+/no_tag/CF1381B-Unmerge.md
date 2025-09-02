# Unmerge

## 题目描述

Let $ a $ and $ b $ be two arrays of lengths $ n $ and $ m $ , respectively, with no elements in common. We can define a new array $ \mathrm{merge}(a,b) $ of length $ n+m $ recursively as follows:

- If one of the arrays is empty, the result is the other array. That is, $ \mathrm{merge}(\emptyset,b)=b $ and $ \mathrm{merge}(a,\emptyset)=a $ . In particular, $ \mathrm{merge}(\emptyset,\emptyset)=\emptyset $ .
- If both arrays are non-empty, and $ a_1<b_1 $ , then $ \mathrm{merge}(a,b)=[a_1]+\mathrm{merge}([a_2,\ldots,a_n],b) $ . That is, we delete the first element $ a_1 $ of $ a $ , merge the remaining arrays, then add $ a_1 $ to the beginning of the result.
- If both arrays are non-empty, and $ a_1>b_1 $ , then $ \mathrm{merge}(a,b)=[b_1]+\mathrm{merge}(a,[b_2,\ldots,b_m]) $ . That is, we delete the first element $ b_1 $ of $ b $ , merge the remaining arrays, then add $ b_1 $ to the beginning of the result.

This algorithm has the nice property that if $ a $ and $ b $ are sorted, then $ \mathrm{merge}(a,b) $ will also be sorted. For example, it is used as a subroutine in merge-sort. For this problem, however, we will consider the same procedure acting on non-sorted arrays as well. For example, if $ a=[3,1] $ and $ b=[2,4] $ , then $ \mathrm{merge}(a,b)=[2,3,1,4] $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

There is a permutation $ p $ of length $ 2n $ . Determine if there exist two arrays $ a $ and $ b $ , each of length $ n $ and with no elements in common, so that $ p=\mathrm{merge}(a,b) $ .

## 说明/提示

In the first test case, $ [2,3,1,4]=\mathrm{merge}([3,1],[2,4]) $ .

In the second test case, we can show that $ [3,1,2,4] $ is not the merge of two arrays of length $ 2 $ .

In the third test case, $ [3,2,6,1,5,7,8,4]=\mathrm{merge}([3,2,8,4],[6,1,5,7]) $ .

In the fourth test case, $ [1,2,3,4,5,6]=\mathrm{merge}([1,3,6],[2,4,5]) $ , for example.

## 样例 #1

### 输入

```
6
2
2 3 1 4
2
3 1 2 4
4
3 2 6 1 5 7 8 4
3
1 2 3 4 5 6
4
6 1 3 7 4 5 8 2
6
4 3 2 5 1 11 9 12 8 6 10 7```

### 输出

```
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：Yaha (赞：13)

### 一个性质 + bitset
---

先简化一下合并规则：

每次看当前 $a$ , $b$ 两个数组中第一个数，将较小的那个从原数组中删去加入 $p$ 。

---

**假设 $p$ 中相邻两个数为 $p_i$ 和 $p_{i+1}$。**

- 若 $p_i>p_{i+1}$

考虑这两个数是怎么加进来的：

1. 是由两个数组分别过来的：

不可能。 $p_i$ 如果要加进来必须是因为它小于另一边的第一个数，如果 $p_{i+1}$ 正在另一边等着，必须要  $p_i<p_{i+1}$ 才行。

2. 是由同一个数组中过来的：

可行。因为 $p_i$ 要加进来，对它在原数组中的下一个数没有要求。

- 若 $p_i<p_{i+1}$，**且先不考虑前 $i-1$ 个数的影响**（这个等会再推广）

1. 由两个数组分别过来：

符合题意。

2. 由同一个数组过来：

同 $p_i>p_{i+1}$ 。

**结论：如果 $p_i>p_{i+1}$ ，这两个数必须来自同一个数组。**

---

**这是两个数的情况，我们试着推广到三个数。**

假设 $p_i$ ， $p_{i+1}$ 已经确定必须在同一个数组中，不妨设它们都在 $a$ 中。

若 $p_{i+2}$ 在 $b$ 中，即和 $p_i$ 不在一个数组中：

想象这三个数依次加入 $p$ 的情景：

- $p_{i+2}$ 在 $b$ 的第一个等着， $p_i$ 和 $p_{i+2}$ 比较， $p_i$ 较小，所以先从 $a$ 中删去，加入 $p$ ；

-  $p_{i+1}$ 和 $p_{i+2}$ 比较， $p_{i+1}$ 较小，从 $a$ 中删去，加入 $p$ ；

-  $a$ 的第一个数和 $p_{i+2}$ 比较，$p_{i+2}$ 较小，从 $b$ 中删去，加入 $p$ 。

所以，如果 $p_{i+2}$ 小于 $p_i$ ，或者小于 $p_{i+1}$ 的话，不可能和它们不在同一个数组中，即必须在同一个数组中，否则将推出矛盾。

**结论：如果 $p_i>p_{i+2}$ ,或者 $p_{i+1}>p_{i+2}$ ，这三个数必须来自同一个数组。**

因为 $p_i>p_{i+1}$ （因为 $p_i$ 和 $p_{i+1}$ 在同一个数组当中），所以只需要满足 **$p_i>p_{i+2}$** ，就可以说明这三个数必须在同一个数组中了。

---

推得更广的话，应该比较显然了，直接结论吧：

块：定义为**必须来自于同一个数组**的**连续**的几个数。

块头：块中**最大**的数，也是第一个数。

如果 $p_i$ 小于上一个块的块头， $p_i$ 加入上一个块，表示 $p_i$ 必须和这些数来自同一个数组。

否则， $p_i$ 自己新建一个块， $p_i$ 作为块头。

---

这样下来，我们可以将所有的数分为 $cnt$ 个块，这些块之间互不影响，可以随意分配到两个数组中。

剩下的任务就是判断是否能将这 $cnt$ 个块分配到长度相等的两个数组中，即是否能选一些块，凑出 $n$ 。

到这里，思路想必大家都懂了，代码如果不想用 bitset ，也可以 DP 。

---

凑出 $n$ ，首先想到了 dfs ，但是这个想法比较脑残，被 pass 掉了。

然后就想到了 bitset ，一想空间，可行，时间，妥了！

定义: `bitset<10000>B`

如果 `B[i]=1` ，表示可以凑成 $i$ 。每处理一个块的 `siz`，可以选择加入，也可以不加，左移取或，都是 bitset 常规操作。

代码就可以非常短啦。

```cpp
#include<bits/stdc++.h>

using namespace std;

int siz[4100],t,n;

int main(){
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int cnt=0,Max=0,a;//Max是块头
		for(int i=1;i<=2*n;i++)
		{
			scanf("%d",&a);
			if(a<Max) siz[cnt]++;//加入块
			else siz[++cnt]=1,Max=a;//新建块
		}
		bitset<10000> B;
		B[0]=1;//可以凑成0！
		for(int i=1;i<=cnt;i++)
			B|=B<<siz[i];
		if(B[n]) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
}
```


---

## 作者：Scintilla (赞：6)

我好像和你们不太一样，我的思路是问题转化 + 简单 $01$ 背包。

先看最后一组样例：
```
6
4 3 2 5 1 11 9 12 8 6 10 7
```
可以发现 $12$ 在中间，所以 $12$ 和其后的数在同一个数组中，否则 $12$ 会先把它们挤出来。去掉这部分，再看看。
```
4 3 2 5 1 11 9 
```
这是我们发现 $11$ 及其后的数字在同一组中，理由一样，再去掉它们。
```
4 3 2 5 1
```
去掉 $5$ 及其后的数字。
```
4 3 2
```
剩下的三个数必定在一个数组中。

这样，我们把这组数分成了几块：
```
4 3 2 / 5 1 / 11 9 / 12 8 6 10 7
```
不难看出，无论我把这些块如何放到两个数组中，只要两个数组中的块是按顺序的，就一定会按样例的顺序排出，因为后一个块中的第一个数就比前一个块中的所有数都大。例如：
$$a = \{4, 3, 2, 11, 9\}, b = \{5, 1, 12, 8, 6, 10, 7\}$$
$$a = \{4, 3, 2, 5, 1, 11, 9\}, b = \{12, 8, 6, 10, 7\}$$
都是可行的方案。

那么我们需要解决的问题就是能否用这些块拼成一个长度为 $n$ 的数组，问题就被我们转换成了一个简单的 $01$ 背包，直接动态规划解决即可。

时间复杂度 $O(n ^ 2)$，可以通过。
```cpp
int tc;

int n, p[N << 1];
int tot, sz[N << 1];
bool vis[N << 1];

bool f[N];

int main() {
    
    tc = read(), f[0] = true;
    
    while (tc--) {
        n = read() << 1;
        Rep(i, 1, n) p[i] = read();
        int now = n, lst = n;
        Dep(i, n, 1) {
            vis[p[i]] = true;
            if (p[i] == now) {
                while (now && vis[now]) --now;
                sz[++tot] = lst - i + 1, lst = i - 1;
            }
        }
        Rep(i, 1, tot) {
        	Dep(j, n >> 1, sz[i]) f[j] |= f[j - sz[i]];
		}
        puts(f[n >> 1] ? "YES" : "NO");
        tot = 0;
        Rep(i, 1, n) f[i] = false, vis[i] = false;
    }
    
    return 0;
}
```

---

## 作者：RedLycoris (赞：4)

结论+dp

我们可以先观察样例。当 $n=4$ 时，整个序列的最大值为8。在merge后的序列中8后面的数在原序列中一定跟在8后面。同理得，在7后面8前面的所有数都一定跟在7后面。

于是原序列被分成了很多小段。现在要做的事就是将这些小段重新组合，得到两个长度为 $n$ 的原序列。由于你已经分好了，所以你不需要知道小段内的内容，只要知道它们的长度，然后01背包即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=4002;
vector<int>g[mxn];
int n,m;
int a[mxn],pos[mxn];
bool ban[mxn];
vector<int>v;
int dp[mxn][mxn];
inline void solve(){
	cin>>n;for(int i=1;i<=n*2;++i)pos[i]=0;//千万不能用memset！会TLE！
	for(int i=1;i<=n*2;++i)ban[i]=0;
	v.clear();
	for(int i=1;i<=n*2;++i)cin>>a[i],pos[a[i]]=i;
	for(int i=n*2;i;--i){              //分割
		int cnt=0;
		for(int j=pos[i];j<=n*2 and !ban[j];)++cnt,ban[j]=1,++j;
		if(cnt)v.push_back(cnt);
	}
	for(int i=0;i<=v.size();++i)for(int j=0;j<=n;++j)dp[i][j]=0;
	dp[0][0]=1;
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();++i){       //背包
		for(int j=0;j<=n;++j){
			if(dp[i][j]==1){
				dp[i+1][j]=1;
				if(j+v[i]<=n){
					dp[i+1][j+v[i]]=1;
				}
			}
		}
	}
	if(dp[(int)(v.size())][n])cout<<"YES\n";
	else cout<<"NO\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;cin>>T;
	for(;T--;)solve();
}

```

---

## 作者：gaozitao1 (赞：3)

**题目大意**：给定一个长度为 $2n$ 的排序，判断这个排序是否可以由两个长度为 $n$ 的序列通过 $merge$ 操作结合而来。 $merge$ 就是归并排序中的 $merge$ 。

想要解决这一道题，暴力枚举肯定是不可以的，需要首先分析一下 题目。

假设有一个排序为 $3,2,6,1,5,7,8,4$ ，那么可以发现一些结论：

1.  $3$ 和 $2$ 在同一个序列中。否则， $2$ 一定在 $3$ 的前面，通过 $merge$ 操作不可能形成上述排列。

2.  $6$ 和 $1$ 和 $5$ 在一个序列中，否则， $1$ 和 $5$ 一定在 $6$ 的前面，通过 $merge$ 操作不可能形成上述排列。

3.  $8$ 和 $4$ 在一个序列中，否则， $4$ 一定在 $8$ 的前面，通过 $merge$ 操作不可能形成上述排列。

之后，就可以发现一个结论：**从数 $a$ 到下一个比 $a$ 大的数之前的数之前的数，和 $a$ 都在同一个序列中。**

所以，根据这个结论，上一个排序就可以分成4组： $（3,2）,（6,1,5）,（7）,（8,4）$ 。每一组的数量分别是 $2，3，1，2$。

此时，因为 $2+2=1+3=8\div2$ ，所以可以拆成两个序列。

而排序 $6，1，3，7，4，5，8，2$ ，可以分成3组： $（6，1，3），（7，4，5），（8， 2）$ ，每一组的数量分别是 $3，3，2$ 。

因为 $3，3，2$ 不能组成 $4$ ，所以这个排序不能拆成两组。

到这里，又可以发现一个结论：**如果一个排序可以拆成两个序列，那么将这个排序分组之后每一组的数量可以组成等于原序列长度一半的数。**

而判断能否组成一个数，可以使用动态规划（dp）。

  $a_i$ 表示原排序拆成几段之后第i段的长度， $d_j$ 表示这些数能不能组成j，能则 $d_j=1$ ，否则 $d_j=0$ 。
 
**状态转移方程**：$d_j|=d_{j-a_i}$ （竖线是异或）。

 解释：如果能组成 $d_{j-a_i}$ 或能组成 $d_j$ ，那么就可以组成 $d_j$ 。
 
 初始化： $d_0=1$ 。
 
 最后，只需要判断 $d_n$ 是否等于 $1$ 即可。如果 $d_n=1$，那么就可以拆成两个序列，否则不能拆成两个序列。
 
**代码：**
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
const int N=2000;
int a[N*2+1],d[N+1],p[N*2+1];//注意a和p数组大小为2n
int main()
{
	register int i,j,k,l,n,t;
	scanf("%d",&t);
	while(t)
	{
		scanf("%d",&n);
		for(i=1; i<=n*2; ++i)
			scanf("%d",&p[i]);
		//分组
		j=p[1];
		//j记录当前组中第一个数（最大的数）
		//如果有一个数比j大，那么那个数就是下一组的第一个数
		k=1;//k记录当前组中有多少数
		l=0;//l表示组数
		//第一个数一定在第一组
		for(i=2; i<=n*2; ++i)
		{
			if(j<p[i])//如果有一个数比j大，那么那个数就是下一组的第一个数
			{
				a[++l]=k;//记录上一个组的数量
				//更新j和k
				j=p[i];
				k=0;
			}
			++k;//当前组中数的数量加一
		}
		a[++l]=k;//将最后一组放进去
		memset(d,0,sizeof(d));//注意清空
		d[0]=1;//初始化
		for(i=1; i<=l; ++i)
			for(j=n; j>=a[i]; --j)
				d[j]|=d[j-a[i]];//dp
		if(d[n])//判断是否组成
			puts("YES");
		else
			puts("NO");
		--t;
	}
	return 0;
}
```

---

## 作者：Daniel_7216 (赞：1)

先来考虑一个性质：

合并原数组 $A$ 和 $B$ 时，如果 $A_l$ 到 $A_r$ 的最大值小于 $B_k$ 则合并之后 $B_k$ 一定在 $A_l$ 到 $A_r$ 之前，换言之，合并之后的数组 $P$ 中数 $P_x$ 后的第一个比它大的数 $P_y$ 之间的数一定在一个数组里，否则小的数一定会在大的数前。那么在这种情况下，$P_x$ 到 $P_{y-1}$ 就可以看成一个整体，问题转换为给你若干个数，是否可以选出一些使他们的和为 $N$。于是用背包解决。

总体来说很简单，但是归并排序的性质是本题的瓶颈，建议读者自行找几个数组推导。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int n, p[4001], maxx, nxt, a[4001], idx = 0, T;
bool dp[4001];
int main(){
    scanf("%d", &T);
    while (T--){
        idx = 0;
        memset(dp, false, sizeof(dp));
        scanf("%d", &n);
        nxt = 2 * n;
        maxx =  0;
        for (int i = 1; i <= 2 * n; i++){
            scanf("%d", &p[i]);
            if (p[i] > maxx){
            	maxx = p[i];
            	idx++;
            	a[idx]++;
			}else{
				a[idx]++;
			}
        }
        dp[0] = true;
        for (int i = 1; i <= idx; i++){
            for (int j = n; j >= a[i]; j--){
                dp[j] = (dp[j] || dp[j - a[i]]);
            }
        }
        if (dp[n]) printf("YES\n");
        else printf("NO\n");
    }
	return 0;
}
```

---

## 作者：Link_Space (赞：1)

一道较为简单的问题，其实一看到将一个序列均分，我首先想到的就是较为套路的背包，但是这道题看起来好像没有什么可以背包的。

其实我们再仔细阅读题目，我们可以发现这样一个性质，如果我们往 $a$ 或 $b$ 任意一个序列中放了 $p$ 中下标为 $i$ 的这个数，即 $p_i$ ，那么我们必须将 $i$ 后面的数全部一起放入这个序列，直到碰到一个数比 $p_i$ 更大。

这个性质是如何推导的呢？假设我们只取 $p_i$ 这个数放进一个序列，那么我们就会将 $p_{i+1}$ 放进另外一个序列，如果 $p_{i+1}$ 比 $p_i$ 更小的话，当我们 $merge$ 这两个序列的时候应该 $p_{i+1}$ 在前而非 $p_i$ ，这与 $p$ 序列本身的顺序冲突，所以我们就可以反证出上面的那一条性质了。

那么知道了这个性质之后，我们就可以开始 01 背包了，为什么呢？因为假设 $p_i$ 为 $p$ 中一个数，$p_{j}$ 为 $p_i$ 后面的一个大于 $p_i$ 的数，我们必须得把 $p_i$ 至 $p_{j-1}$ 全部放入同一个序列，据此我们可以将 $p$ 序列划为一个个小段，每一个小段都可以放入任意一个序列，那么我们只需要将这些小段的长度作为物体体积，判断是否能刚好填满两个长度为 $n$ 的序列就好了，具体看代码，自认为很简洁：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 4e3 + 5;
int p[N];
int w[N];
int cnt;
int dp[N];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(dp, 0, sizeof dp);
		cnt = 0;
		memset(w, 0, sizeof w);
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= 2 * n;i++)
			scanf("%d", &p[i]);
		int las = 0;
		int len = 0;
		for (int i = 1; i <= 2 * n;i++)
		{
			if(p[i]>las)
			{
				w[++cnt] = len;
				len = 1;
				las = p[i];
			}
			else
				len++;
		}
		dp[0] = 1;
		for (int i = 1; i <= cnt;i++)
			for (int j = n; j >= w[i];j--)
				if(dp[j-w[i]])
					dp[j] = 1;
		if(dp[n])
			puts("YES");
		else
			puts("NO");
	}
}
```


---

## 作者：MyukiyoMekya (赞：1)

Unmerge，题意差不多就是逆向归并排序

手模样例，`3 1 2 4` ，发现这个 3 肯定是 a 或 b 的第一个字母，然后假设把 3 放在 a 的第一个，那么 1 放 b 的第一个就不行，只能放 3 后面，2 也是同理，直到 4 才可以放在 b 。按照这个结论去模拟了所有样例，发现没啥问题。于是我们发现，如果选一个数，那么从这个数开始后面，直到第一个比他大的数前为止的数都必须得选。那么这个题就转化成了：

给定一些数，求把他们分成和相等的两组是否可行

可行性dp走起：	$f_{i,j}=true/false$ 表示使用前 $i$ 个数， a 组的数的和减去 b 组的数的和是否可能到达 $j$ ，然后转移方程显而易见：
$$
f_{i,j} \leftarrow f_{i-1,j+a_i} | f_{i-1,j-a_i}
$$
这个显然可以滚存，然后bitset一下，代码就非常短了

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int a[4000];
inline void work()
{
	int n;read(n);
	n<<=1;
	for(int i=1;i<=n;++i)
		read(a[i]);
	vector<int> dr;
	for(int i=1;i<=n;++i)	// 把问题转化
	{
		reg int pos=i;
		while(pos<n&&a[pos+1]<a[i])
			++pos;
		dr.push_back(pos-i+1);
		i=pos;
	}
	bitset<4000> f;		// 可行性dp
	f[2000]=true;
	for(int i=0;i<(int)dr.size();++i)
		f=(f<<dr[i])|(f>>dr[i]);
	puts(f.test(2000)?"YES":"NO");
	return;
}
signed main(void)
{
	int t;cin>>t;
	while(t--)
		work();
	return 0;
}
```





---

## 作者：傅思维666 (赞：1)

一看到这种数列的题首先想到研究性质。手画几组样例发现，如果一个排列的最大值在这个排列的前$n$项出现，那么这个排列就肯定是废废了，因为这个最大值是出不来的，也就无法构造出这个排列。

然鹅这个性质好像并没有什么用处。这里仅作为思路展示来使用。

然后我们在进一步思考的时候，发现一个问题：对于某一个极大值来讲，从它开始到下一个比它大的值必须要在一个队列里连续排列。

就拿这组样例说话：

```
3 2 6 1 5 7 8 4
```

如果3在第一个队列里了，那么2肯定也在同一个队列里并且紧随其后，才可能保证3,2连续被弹出，否则，如果3在第一个队列，2在第二个队列，那么一开始弹出的就不是3而是2，如果2在6后面，在6没有被弹出之前也不可能轮到2，构造均宣布失败。

那么，这么一个数列就被我们分成了若干个小段，每段由一个段首极大值和在它后面的若干个较小值组成。比如上面的例子，最终我们就将其分成了如下的段落：

```
[3,2],[6,1,5],[7],[8,4]
```

到了这里就容易想到：如果我们能从这些长度不同的段落中挑出任意段，使之恰好能塞满长度$n$的一个排列，那么我们就构造成功了。（题目不需要我们考虑段与段之间的顺序问题）比如上面的样例答案就是：

```
[3,2,8,4],[6,1,5,7]
```

所以好像是个背包问题？

还是最容易的0/1背包。

所以我们只需要统计出所有的段落长度，然后来跑0/1背包即可。状态就定义为：$dp[i][j]$表示前$i$个物品能否装满容量为$j$的背包。一个到达性的背包问题。自然可以想到，如果$dp[i-1][j]$或者$dp[i-1][j-len[i]]$（其中$len[i]$表示第$i$段的长度）可以到达，那么$dp[i][j]$就是可以到达的。

答案就是$dp[tot][n]$，可达就是$YES$，否则就是$NO$。

兴冲冲地写完代码，T了。（逃

后来一看，发现自己狂开了三个$memset$。（绝不能开，开了就T）仔细思考后，发现保存原数列的$a$数组和每段的长度$len$都不需要清空，反正也是被覆盖，没被覆盖的地方也用不上。不影响转移。

那么$dp$数组呢？如果依然$memset$或者手动清空的话还是会T啊。

考虑边转移边清空，我们只需要把初值$dp[0][0]$设置成1，之后转移之前把$dp[i][j]$先清掉，就能保证转移的有序正确性。

那么有了代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,maxx,tmp,cnt,maxpos,tot;
int len[4010],a[4010];
int dp[4010][2010];//dp[i][j]表示前i个物品能否装满体积为j的背包。
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<'0'||ch>'9')
        if(ch=='-')
            f=-1,ch=nc();
    while(ch>='0'&&ch<='9')
        x=x*10+ch-48,ch=nc();
    return x*f;
}
int main()
{
    t=read();
    while(t--)
    {
        tot=0,maxx=0;
        n=read();
        for(int i=1;i<=2*n;i++)
        {
            a[i]=read();
            if(a[i]>maxx)
                maxx=a[i],maxpos=i;
            if(i==1)
                tmp=a[i],cnt=1;
            if(a[i]>tmp)
                len[++tot]=cnt,tmp=a[i],cnt=1;
            if(a[i]<tmp)
                cnt++;
        }
        if(maxpos<n)
        {
            puts("NO");
            continue;
        }
        len[++tot]=cnt;
        dp[0][0]=1;
        for(int i=1;i<=tot;i++)
            for(int j=0;j<=n;j++)
            {
                dp[i][j]=0;
                if(j>=len[i])
                    dp[i][j]|=dp[i-1][j-len[i]];
                dp[i][j]|=dp[i-1][j];
            }
        if(dp[tot][n])
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
```


---

## 作者：cosmicAC (赞：1)

有一个简单的DP，$f_{i,j,k}$（$k\in \{0,1\}$）表示考虑排列$a$由第$i$位开始的后缀中一共有$j$个放进第$0$个数列里，（另$2n+1-i-j$个放在第$1$个数列里），并且第$i$个数放在第$k$个数列里，是否可能有解。

转移就是枚举第$i$个数后方第一个和$a_i$不在同一个序列里的位置$x$，

$$f_{i,j,k}=f_{i,j,k} \vee f_{x,j-(1-k)(x-i),1-k}$$

此处必须要满足$a_x\gt \max_{j=i}^{x-1}a_j$才能先选$\{a_i\dots a_{x-1}\}$再选$a_x$，并且选择的$x$必须让两个序列的长度都不会超过$n$。暴力DP复杂度$O(n^3)$，会TLE on test 2。

考虑优化这个DP。~~直接用`std::bitset`三方过4000~~

发现$a_x\gt \max_{j=i}^{x-1}a_j$这个限制相当于一个单调栈，可以使用如下过程来维护所有合法的$x$：

- 弹栈，直到当前栈顶$\gt a_i$或者栈空了
- 用栈中的所有元素更新$f_{i,*,*}$
- 将$a_i$压入栈中

然而暴力更新复杂度还是错的。观察一下dp转移下标中的$j-(1-k)(x-i)$，发现所有的第二维坐标形成了一条竖直线（当$k=1$）或对角线（当$k=0$），所以对于每一列和每一条副对角线，维护此直线之内所有合法$x$对应的$f$值之和，就可以支持$O(1)$的插入/删除/查询此直线中是否有$1$了。复杂度$O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[4010][2010][2],n,a[4010],T,sta[4010],vsm[2010],dsm[4010];
void ins(int x,int v){
	for(int i=0;i<=n;i++)vsm[i]+=v*f[x][i][0];
	for(int i=x;i<=2*n && i-x<=n;i++)dsm[i]+=v*f[x][i-x][1];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++){
			scanf("%d",a+i);
			for(int j=0;j<=n;j++)f[i][j][0]=f[i][j][1]=0;
		}
		for(int i=0;i<=n;i++)vsm[i]=0;
		for(int i=0;i<=2*n;i++)dsm[i]=0;
		for(int i=2*n,tp=0;i;i--){
			if(i>n)f[i][2*n+1-i][0]=f[i][0][1]=1;
			while(tp&&a[sta[tp]]<a[i])ins(sta[tp--],-1);
			for(int j=max(n+1-i,0);j<=n&&j+i<=2*n+1;j++){
				f[i][j][1]=vsm[j];
				if(j+i<=2*n)f[i][j][0]=dsm[j+i];
			}
			sta[++tp]=i;ins(i,1);
		}
		puts(f[1][n][0]|f[1][n][1]?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：hfctf0210 (赞：1)

从大到小搜索数，若该数未标记，则该数后面所有未标记的数都与该数在一个集合，并将其标记，记录该集合大小。统计完所有集合大小，再进行背包DP
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4005;
int n,m,a[N],p[N],b[N],w[N];
bool f[N];
int main()
{
	int T;scanf("%d",&T);
	f[0]=1;
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++)scanf("%d",&a[i]),p[a[i]]=i,f[i]=0;
		f[0]=1;
		for(int i=1;i<=2*n;i++)b[i]=1;
		m=0;
		for(int i=2*n;i;i--)
		if(b[p[i]])
		{
			w[++m]=0;
			for(int j=p[i];j<=2*n;j++)if(b[j])b[j]=0,++w[m];
		}
		for(int i=1;i<=m;i++)
		for(int j=n;j>=w[i];j--)
		f[j]|=f[j-w[i]];
		if(f[n])puts("YES");else puts("NO");
	}
}
```


---

## 作者：Anita_Hailey (赞：0)

## 正文

考虑 `merge` 的含义。

不难看出的是，这个 `a` 和 `b` 两个序列都是由很多段。

那么，我们只需要把把这些段找出来，在跑一次背包（看看能不能构成），即可。

关于为什么是一段一段的呢,你看啊，假如我这个 $a_1$ 现在很大很大，那么我的 $b1$ 到 $b_j$ 肯定要比 $a_1$ 小，是吧，所以 $b_{j+1}$就比 $a_1$ 大了，之后一直到 $a_k$ 才比 $b_{j+1}$ 更大，所以说

一直到最大数 $2n$ 的出现，不妨设他在 $a$ 里,所以这个 $a$ 之后的都是下降子序列了，那么 去掉这些东西，即把 $2n$ 到 $a_n$ 这里的值都去掉，这时候会重新出来一个最大值，讨论最大值的位置 如果在 $a$ 里，那么接着去掉就行了。
如果在 $b$ 里，那么也接着去掉就行了。

所以，后一段对于前一段在哪里没有影响，那么不难想到了我们可以跑一个背包来看看这些段，是否可以组成一个 n 长的段。

考虑如何对于 $O(n)$ 求，这些序列，咋搞，对于每个值 开一个  $flag$，维护一个 $top$ 指针（指向最大的），然后如果这个点就是最大的的话，就是更新 $top$ 指针就完了，否则修改 $flag$。

那么代码如下。

```cpp
namespace Solution
{
#define IOS std::ios::sync_with_stdio( false ), std::cin.tie( 0 ), std::cout.tie( 0 )
#define Rep( i, j, k ) for( int i = j; i >= k; --i )
#define rdi( ) read < int > ( )
#define rdl( ) read < long long > ( )
#define pti( i ) print < int > ( i ), putchar( ' ' )
#define ptl( i ) print < long long > ( i ), putchar( ' ' )
#define For( i, j, k ) for( int i = j; i <= k; ++i )
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::map;
	using std::queue;
	using std::deque;
	using std::set;
	using std::pair;
	const int Maxn = 4001; 
	vector < pair < int, int > > v;
	int a[ Maxn ];
	void solve( )
	{
		v.clear( );
		int n;
		cin >> n;
		For( i, 1, 2 * n )
			cin >> a[ i ];
		int las = n * 2, mx = 2 * n;
		bool f[ Maxn ];
		std::memset( f, 0, sizeof f );
		Rep( i, 2 * n, 1 )
		{
			f[ a[ i ] ] = 1;
			if( a[ i ] == mx )
			{
				v.push_back( std::make_pair( i, las ) );
				las = i - 1;
			}
			while( f[ mx ] )
				mx--;
		}
		std::reverse( v.begin( ), v.end( ) );
		std::memset( f, 0, sizeof f );
		f[ 0 ] = 1;
		for( int i = 0; i < ( int ) v.size( ); ++i )
		{
			int len = v[ i ].second - v[ i ].first + 1;
			if( len > n )
				break;
			Rep( i, n, len )
				if( !f[ i ] && f[ i - len ] )
					f[ i ] = 1;
		}
		cout << ( f[ n ] ? "YES" : "NO" ) << '\n'; 
	}
	void fakemain( )
	{
		IOS;
		int t;
		cin >> t;
		while( t-- )
			solve( );
		return;
	}

} // namespace Solution
```


---

## 作者：Polaris_Dane (赞：0)

五分钟口胡出来的（

考虑$p$的一个性质

如果出现了一个连续递减子序列，那么这个子序列只能属于$a$或$b$中一个

非常显然，证明略去

更严格来说，如果$p$出现了一个数$s$，设$s'$为$s$后面第一个大于$s$的数，那么$s$到$s'$中间的数全部都应属于$a$或$b$中一个

于是经过分类之后，我们可以进行DP，看能不能凑出来大小刚好为$n$的序列即可

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 500100
#define inf 2e9
#define LL long long
#define ull unsigned long long
const int mod=998244353;
const int base=137;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int t,p[M],maxx,cnt,dp[4010][2010];
vector<int>st;
signed main(void){
	t=read();
	while (t--){
		int n=read();st.clear(),maxx=0;
		for (int i=1;i<=2*n;i++) p[i]=read();
		for (int i=1;i<=2*n;i++){
			if (p[i]>maxx) maxx=p[i],st.push_back(cnt),cnt=0;
			cnt++;
		}st.push_back(cnt),cnt=0;
		dp[0][0]=1;
		for (int i=1;i<st.size();i++)
			for (int j=0;j<=n;j++){
				dp[i][j]=0;
				if (j>=st[i]) dp[i][j]|=dp[i-1][j-st[i]];
				dp[i][j]|=dp[i-1][j];
			}
		if (dp[st.size()-1][n]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

