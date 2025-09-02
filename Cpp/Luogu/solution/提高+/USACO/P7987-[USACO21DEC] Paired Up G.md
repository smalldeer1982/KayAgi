# [USACO21DEC] Paired Up G

## 题目描述

数轴上总计有 $N$（$1\le N\le 10^5$）头奶牛。第 $i$ 头奶牛的位置为 $x_i$（$0 \leq x_i \leq 10^9$），而第 $i$ 头奶牛的重量为 $y_i$（$1 \leq y_i \leq 10^4$）。

根据 Farmer John 的信号，某些奶牛会组成对，使得

- 每一对包含位置相差不超过 $K$ 的两头不同的奶牛 $a$ 和 $b$（$1\le K\le 10^9$）；也就是说，$|x_a-x_b|\le K$。

- 每一头奶牛要么包含在恰好一对中，要么不属于任何一对。

- **配对是极大的**；也就是说，没有两头未配对的奶牛可以组成对。

你需要求出未配对的奶牛的重量之和的可能的范围。具体地说，

- 如果 $T=1$，计算未配对的奶牛的最小重量和。

- 如果 $T=2$，计算未配对的奶牛的最大重量和。

## 说明/提示

【样例解释1】

在这个例子中，奶牛 $2$ 和 $4$ 可以配对，因为她们的距离为 $2$，不超过 $K = 2$。这个配对方案是极大的，因为奶牛 $1$ 和 $3$ 的距离为 $3$，奶牛 $3$ 和 $5$ 的距离为 $3$，奶牛 $1$ 和奶牛 $5$ 的距离为 $6$，均大于 $K = 2$。未配对的奶牛的重量和为 $2 + 2 + 2 = 6$。

【样例解释2】

在这里，奶牛 $1$ 和 $2$ 可以配对，因为她们的距离为 $2 \leq K = 2$，同时奶牛 $4$ 和 $5$ 可以配对，因为她们的距离为 $2 \leq K = 2$。这个配对方案是极大的，因为只剩下了奶牛 $3$。未配对的奶牛的重量和即为 $2$。

【样例解释3】

这个例子的答案为 $693+992+785=2470$。

【数据范围】

- 测试点 4-8 满足 $T=1$。
- 测试点 9-14 满足 $T=2$ 且 $N\le 5000$。
- 测试点 15-20 满足 $T=2$。

## 样例 #1

### 输入

```
2 5 2
1 2
3 2
4 2
5 1
7 2```

### 输出

```
6```

## 样例 #2

### 输入

```
1 5 2
1 2
3 2
4 2
5 1
7 2```

### 输出

```
2```

## 样例 #3

### 输入

```
2 15 7
3 693
10 196
12 182
14 22
15 587
31 773
38 458
39 58
40 583
41 992
84 565
86 897
92 197
96 146
99 785```

### 输出

```
2470```

# 题解

## 作者：houzhiyuan (赞：19)

[更垃圾的阅读体验](https://hydro.ac/d/houzhiyuan/p/P12401/solution)

因为有的需要求最大，有的需要求最小，考虑用 dp 解决。

考虑如果选择了一些奶牛要叉掉，首先需要满足这些叉掉的奶牛之间的距离需要大于 $k$，然后还要满足剩下奶牛可以匹配。

为了使剩下的奶牛尽量可以匹配，显然相邻两个匹配最优。

设 $f_{i,j} $ 表示已经做完了前 $i$ 头奶牛，叉掉了的奶牛数是奇数头还是偶数头（$j=0$ 表示偶数，$j=1$ 表示奇数）的最大或最小值。

那么通过 $i,j$ 的奇偶性，就可以判断出 $i$ 前面选择了的奶牛数量的奇偶性。

直接分情况转移，记录 $las$ 表示满足 $las$ 到 $i$ 的距离大于 $k$ 的最大的 $las$。

- 前面选择了偶数头奶牛，那么必然可以两两匹配，如果叉掉这头奶牛，那么就是 $f_{las,1-j}+y_i$，如果选择这头奶牛，这头奶牛需要与后面的进行匹配，因此需要满足 $i$ 到 $i+1$ 距离小于等于 $k$ ，如果满足，就转移 $f_{i-1,j}$。

- 前面选择了奇数头奶牛，那么必然剩下一头奶牛没有匹配，如果叉掉这头奶牛，需要让前一头奶牛与后面一头奶牛匹配，因此需要满足 $i-1$ 到 $i+1$ 距离小于等于 $k$，那么转移 $f_{las,1-j}+y_i$，如果选择这头奶牛，这头奶牛需要与前面的进行匹配，因此需要满足 $i-1$ 到 $i$ 距离小于等于 $k$ ，如果满足，就转移 $f_{i-1,j}$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,k,f[N][2],_=1,las;
struct hzy{int x,y;}a[N];
void get(int &x,int y){x=x<y?x:y;}
void getmax(int &x,int y){x=x>y?x:y;}
int main(){
	scanf("%d%d%d",&T,&n,&k);
	if(T==2)_=-1;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].y*=_;
	a[0].x=-1e9,a[n+1].x=2e9;
	memset(f,63,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		while(a[i].x-a[las+1].x>k)las++;
		int z=i&1;
		get(f[i][z],f[las][z^1]+a[i].y);
		if(a[i].x-a[i-1].x<=k)get(f[i][z],f[i-1][z]);
		if(a[i+1].x-a[i-1].x<=k)get(f[i][z^1],f[las][z]+a[i].y);
		if(a[i+1].x-a[i].x<=k)get(f[i][z^1],f[i-1][z^1]);
	}	
	if(n&1)printf("%d",f[n][1]*_);
	else printf("%d",f[n][0]*_);
}
```

---

## 作者：Eibon (赞：5)

全局的最小值（和最大值）问题，考虑 dp。

其实最小值不一定要 dp，因为对于其来说没有“配对是极大的”的限制。

但是因为要求解最大值，最大值与最小值的 dp 是相通的，所以考虑最小值的 dp。

设 $dp_{i,j}$ 表示前 $i$ 头奶牛在匹配队列中的有 $j$ 头，但这样时间空间都会炸，发现 $j$ 对最终答案无实际影响，只有 $j$ 的奇偶性对答案有实际影响，也就是前面奶牛中是否有未匹配的奶牛。

所以设 $dp_{i,0/1}$ 表示前 $i$ 头奶牛是否有未匹配的奶牛的答案。其中，$dp_{i,i\bmod2}$ 表示没有，另一个同理。

考虑当前的奶牛，可以选择加入匹配中，当然也可以不选择。

也就是说，牛只有 $2$ 种状态。

设 $l$ 表示距离当前奶牛 $i$ 超过 $k$ 的离奶牛 $i$ 最近的奶牛的编号。这个可以用双指针 $O(n)$ 维护。

 - 如果前面匹配了偶数头奶牛，那么它们一定都能互相匹配。
   - 如果当前奶牛不选择，答案为 $dp_{l,j\oplus 1}+y_{i}$。
   - 否则，这头奶牛要与后面的奶牛进行匹配，答案为 $dp_{i-1,j}$，要求第 $i$ 头奶牛必须与第 $i+1$ 头奶牛距离小于 $k$。
 - 不然，前面一定还空余一头奶牛。
   - 如果当前奶牛选择，它与前面一头奶牛距离必须小于 $k$，答案为 $dp_{i-1,j}$。
   - 否则，只能让空余的奶牛与下一头匹配，那么第 $i-1$ 头奶牛必须与第 $i+1$ 头奶牛距离小于 $k$。此时答案为 $dp_{l,j\oplus1}+y_{i}$。

计算最大值的话要先将所有 $y_{i}$ 取相反数，最后答案统计再取一遍相反数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
int T=1,op,n,k,ans;
int dp[maxn][2],x[maxn],y[maxn];
void solve()
{
	scanf("%lld%lld%lld",&op,&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		if(op==2){
			y[i]=-y[i];
		}
	}
	x[0]=-inf;
	x[n+1]=inf;
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	int l=0;
	for(int i=1;i<=n;i++){
		while(x[i]-x[l+1]>k){
			l++;
		}
		int j=i&1;
		int p=j^1;
		dp[i][j]=dp[l][p]+y[i];
		if(x[i+1]-x[i-1]<=k){
			dp[i][p]=dp[l][j]+y[i];
		}
		if(x[i]-x[i-1]<=k){
			dp[i][j]=min(dp[i][j],dp[i-1][j]);
		}
		if(x[i+1]-x[i]<=k){
			dp[i][p]=min(dp[i][p],dp[i-1][p]);
		}
	}
	if(n&1){
		ans=dp[n][1];
	}
	else{
		ans=dp[n][0];
	}
	if(op==2){
		ans=-ans;
	}
	printf("%lld\n",ans);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Wilson_Lee (赞：5)

根据经验，这题显然是伪装成图匹配的dp题，然后推dp方程，设 $dp[i][0/1]$ 表示到第 $i$ 个为止，确定第 $i$ 个不匹配/匹配的最值。

对于 $T=1$：

未配对的奶牛的重量和最小，即已配对的奶牛的重量和最大，此时无需考虑“**配对是极大的**”这一限制，因为若前面有奶牛没有匹配就不满足当前方案最大。

dp方程（这个应该不难理解）：

$dp[i][0]=\max\{dp[i-1][0],dp[i-1][1]\}$；

$dp[i][1]=\max\{dp[i-2][0]+a[i]+a[i-2],dp[i-1][0]+a[i]+a[i-1]\}$（如果能匹配的话）。

对于 $T=2$:

未配对的奶牛的重量和最大，即已配对的奶牛的重量和最小，这时“**配对是极大的**”这一限制就显得尤为恶心了。

这时不妨考虑若 $i$ 不参与匹配，那么就说明对于所有 $j$ 满足 $x_i-x_j<=k$ 都必须完成匹配。

设最小满足条件的位置为 $pos$，若 $i-pos$ 为偶数，两两互相配对即可，若 $i-pos$ 为奇数，说明最前面那个要和之前的匹配，其余两两匹配。

当 $i$ 参与匹配时同理，这里就不再赘述了。

dp方程（~~这里的空白太小我写不下~~ 见代码）。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
int a[MAXN],x[MAXN],dp[MAXN][2];
int sum[MAXN];
int T,n,k,ans;
void solve1()
{
    memset(dp,-0x3f,sizeof(dp));
    dp[1][0]=0;
    for(int i=2;i<=n;++i)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
        if(i>2 && x[i]-x[i-2]<=k) dp[i][1]=max(dp[i][1],dp[i-2][0]+a[i]+a[i-2]);
        if(x[i]-x[i-1]<=k) dp[i][1]=max(dp[i][1],dp[i-1][0]+a[i]+a[i-1]);
    }
    printf("%d\n",ans-max(dp[n][0],dp[n][1]));
}
void solve2()
{
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=dp[1][0]=0;
    for(int i=2;i<=n;++i)
    {
        int j=lower_bound(x+1,x+n+1,x[i]-k)-x;
        if((i-j)&1) dp[i][0]=dp[j][1]+sum[i-1]-sum[j];
        else dp[i][0]=min(dp[j-1][0],dp[j-1][1])+sum[i-1]-sum[j-1];
        if(i>2 && x[i]-x[i-2]<=k)
        {
            int pos=lower_bound(x+1,x+n+1,x[i-1]-k)-x,tmp;
            if((i-1-pos)&1) tmp=min(dp[pos-1][0],dp[pos-1][1])+sum[i-2]-sum[pos-1];
            else tmp=dp[pos][1]+sum[i-2]-sum[pos];
            dp[i][1]=min(dp[i][1],tmp+a[i]);
        }
        if(x[i]-x[i-1]<=k) dp[i][1]=min(dp[i][1],min(dp[i-2][0],dp[i-2][1])+a[i]+a[i-1]);
    }
    printf("%d\n",ans-min(dp[n][0],dp[n][1]));
}
int main()
{
    cin>>T>>n>>k;
    for(int i=1;i<=n;++i) scanf("%d %d",&x[i],&a[i]),ans+=a[i],sum[i]=sum[i-1]+a[i];
    if(T==1) solve1();
    else solve2();
    return 0;
}
```

---

## 作者：XL4453 (赞：4)

### 解题思路：

挺麻烦的 $\text{DP}$ 题。

首先发现题目中的两个问题本质一样，将其中一个问题乘上 $-1$ 之后就变成了另一个，所以不妨只考虑一种。下面的题解以求最小为例。

---

先考虑一种朴素的 $\text{DP}$ 思路，记 $f_{i,j}$ 表示考虑到第 $i$ 个位置，其中已经匹配好的一共有 $j$ 个。

然后考虑转移。很明显，根据周边的位置的情况需要分出不同的情况讨论。

首先可以令 $i$ 不被匹配，由于答案单调不减，这种情况下需要从距离 $i$ 长度超过 $k$ 的位置里面选一个最靠右的转移。这个位置对于递增的 $i$ 同样是单调的，可以直接从前一个推过来。

不过这种转移方式并不是一定可行的，如果之前的位置上出现了奇数个被认为是已经匹配的，就要求这个位置的前一个可以和后一个进行匹配，否则在令 $i$ 不匹配之后，就会出现不可能的情况。否则，在任意位置上不存在出现奇数个最近的两个相邻的区块需要进行匹配的情况之后就一定能够说明存在至少一组可行的匹配。

也可以令 $i$ 和之前的某一个位置进行匹配。这样就需要分两种情况讨论，之前如果有奇数个未匹配的就和之前的匹配，反之就和之后的进行匹配。这个地方有一个很显然的贪心就是选择相邻的两个进行匹配一定是最有可能实现的情况，所以直接判断和之前或者之后的最近的位置是否能够匹配就行了。

---
这样的时间复杂度是 $O(n^2)$ 的，不能通过。

但是根据上面的转移，可以发现其实真正决定匹配的是 $j$ 的奇偶性，直接记录下这个就行了。

优化后总复杂度 $O(n)$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=1000000000;
int T,n,k,x[100005],y[100005],l,ans,f[100005][2],ti,now;
int main(){
	scanf("%d%d%d",&T,&n,&k);
	if(T==2)ti=-1;
	else ti=1;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
		y[i]*=ti;
	}
	x[0]=-INF;
	x[n+1]=2*INF;
	for(int i=0;i<=n+1;i++)
	f[i][0]=f[i][1]=INF;
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		while(x[i]-x[l+1]>k)l++;
							f[i][i&1]=min(f[i][i&1],f[l][!(i&1)]+y[i]);
		if(x[i+1]-x[i-1]<=k)f[i][!(i&1)]=min(f[i][!(i&1)],f[l][i&1]+y[i]);
		if(x[i]-x[i-1]<=k)	f[i][i&1]=min(f[i][i&1],f[i-1][i&1]);
		if(x[i+1]-x[i]<=k)	f[i][!(i&1)]=min(f[i][!(i&1)],f[i-1][!(i&1)]);
	}
		
	printf("%d",n&1?f[n][1]*ti:f[n][0]*ti);
	return 0;
}
```


---

## 作者：Mine_King (赞：2)

[在我的个人博客获得更好的阅读体验](https://caijimk.github.io/post/LuoguP7987)  
[在我的博客园博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/LuoguP7987.html)

## Problem

[洛谷 P7987 [USACO21DEC] Paired Up G](https://www.luogu.com.cn/problem/P7987)

**题目大意：**

有 $n$ 个点，其中第 $i$ 个点位置为 $x_i$，权值为 $y_i$。若两个点 $i, j$ 满足 $|x_i - x_j| \le k$，则这两个点之间有一条边。  
求一个匹配，在满足其为极大匹配的情况下匹配点的权值和最大/最小。  
求总权值和与匹配点的权值和的差。

## Solution

提供一种不同于洛谷题解区的解法。

**结论：作为答案的匹配中的任意两对匹配 $(a, b)$ 和 $(c, d)$，区间 $[a, b]$ 与区间 $[c, d]$ 一定不交。**

这个可以用调整法证明。如果两个匹配 $(a, b)$ 和 $(c, d)$ 满足 $a < c < b < d$，则可以将匹配调整成 $(a, c)$ 和 $(b, d)$。  
如果两个匹配 $(a, b)$ 和 $(c, d)$ 满足 $a < c < d < b$，则匹配可以调整成 $(a, c)$ 和 $(d, b)$。

于是我们可以得到另一个结论：**一个点只会与其前两个点或后两个点匹配。**  
因为如果某个点 $i$ 与 $i - 3$ 匹配，则 $i - 2$ 和 $i - 1$ 必然会成为匹配点。此时不满足区间无交。

于是我们就可以 $\verb|dp|$ 了：设 $dp_{i, 0 / 1 / 2}$ 表示只考虑前 $i$ 个点，第 $i$ 个点不在匹配中或与 $i - 1$ 匹配或与 $i - 2$ 匹配时的答案。

考虑转移。  
我们不妨设 $l_i$ 为第一个与 $i$ 有边的节点。显然 $1 \sim i - 1$ 中有且仅有 $l_i \sim i - 1$ 与 $i$ 有边。  
$l_i$ 可以双指针求出。

对于 $dp_{i, 0}$：

- 若 $x_i - x_{i - 1} > k$，则 $i - 1$ 无论是什么状态都是合法的。  
- 否则，必须满足 $1 \sim i - 1$ 中所有与 $i$ 有边的点都必须是匹配点。  
  - 如果这些点的个数为偶数，因为每个点只能与前后四个匹配，且区间无交，且每个点都要是匹配点，所以只能相邻两个匹配。  
  - 如果这些点的个数为奇数，依然相邻两个匹配，且最前面那个要与另外的点匹配。

所以有：

$$
dp_{i, 0} = \left\{
\begin{array}{ll}
  \min/\max(dp_{i - 1, 0}, dp_{i - 1, 1}, dp_{i - 1, 2}) & x_i - x_{i - 1} > k \\
  \min/\max(dp_{l_i - 1, 0}, dp_{l_i - 1, 1}, dp_{l_i - 1, 2}) + \sum\limits_{j = l_i}^{i - 1} y_j & x_i - x_{i - 1} \le k, i - l_i \equiv 0 \pmod{2} \\
  \min/\max(dp_{l_i, 1}, dp_{l_i, 2}) + \sum\limits_{j = l_i + 1}^{i - 1} y_j & x_i - x_{i - 1} \le k, i - l_i \equiv 1 \pmod{2}
\end{array}
\right.
$$

对于 $dp_{i, 1}$，当且仅当 $x_i - x_{i - 1} \le k$ 时才能转移，且 $i - 2$ 无论时什么状态都是合法的。  
所以有：

$$
dp_{i, 1} = \left.
\begin{array}{ll}
  \min/\max(dp_{i - 2, 0}, dp_{i - 2, 1}, dp_{i - 2, 2}) + y_{i - 1} + y_i & x_i - x_{i - 1} \le k
\end{array}
\right.
$$

对于 $dp_{i, 2}$：首先必须满足 $x_i - x_{i - 2} \le k$。  
然后需要满足 $i - 1$ 无法匹配，这里的分析与 $dp_{i, 0}$ 类似，不再赘述。

$$
dp_{i, 2} = \left\{
\begin{array}{ll}
  \min/\max(dp_{i - 3, 0}, dp_{i - 3, 1}, dp_{i - 3, 2}) & x_i - x_{i - 2} \le k, x_{i - 1} - x_{i - 3} > k \\
  \min/\max(dp_{l_{i - 1} - 1, 0}, dp_{l_{i - 1} - 1, 1}, dp_{l_{i - 1} - 1, 2}) + \sum\limits_{j = l_{i - 1}}^{i - 2} y_j + y_i & x_i - x_{i - 2} \le k, x_{i - 1} - x_{i - 3} \le k, i - 2 - l_{i - 1} \equiv 0 \pmod{2} \\
  \min/\max(dp_{l_{i - 1}, 1}, dp_{l_{i - 1}, 2}) + \sum\limits_{j = l_{i - 1} + 1}^{i - 2} y_j + y_i & x_i - x_{i - 2} \le k, x_{i - 1} - x_{i - 3} \le k, i - 2 - l_{i - 1} \equiv 0 \pmod{2}
\end{array}
\right.
$$

然后这题就做完了。

## Code

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int t, n, k, x[100005], y[100005], l[100005];
long long sum[100005], dp[100005][3];

int main() {
	scanf("%d%d%d", &t, &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]), sum[i] = sum[i - 1] + y[i];
	for (int ri = 1, le = 1; ri <= n; ri++) {
		while (x[ri] - x[le] > k) le++;
		l[ri] = le;
	}
	if (t == 1) {
		long long inf = ~0x3f3f3f3f3f3f3f3f;
		memset(dp, ~0x3f, sizeof(dp));
		dp[0][0] = 0;
		dp[1][0] = 0;
		if (x[2] - x[1] > k) dp[2][0] = 0;
		else dp[2][1] = y[1] + y[2];
		if (x[3] - x[2] > k) dp[3][0] = max(dp[2][0], dp[2][1]);
		else {
			dp[3][0] = dp[2][1];
			dp[3][1] = y[2] + y[3];
			if (x[3] - x[1] <= k) dp[3][2] = y[1] + y[3];
		}
		for (int i = 4; i <= n; i++) {
			if (x[i] - x[i - 1] > k)
				dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
			else if ((i - l[i]) % 2 == 0)
				dp[i][0] = max({dp[l[i] - 1][0], dp[l[i] - 1][1], dp[l[i] - 1][2]}) +
					sum[i - 1] - sum[l[i] - 1];
			else dp[i][0] = max(dp[l[i]][1], dp[l[i]][2]) + sum[i - 1] - sum[l[i]];
			if (x[i] - x[i - 1] <= k)
				dp[i][1] = max({dp[i - 2][0], dp[i - 2][1], dp[i - 2][2]}) + y[i - 1] + y[i];
			if (x[i] - x[i - 2] <= k) {
				if (x[i - 1] - x[i - 3] > k)
					dp[i][2] = max({dp[i - 3][0], dp[i - 3][1], dp[i - 3][2]}) + y[i - 2] + y[i];
				else if ((i - 2 - l[i - 1]) % 2 == 0)
					dp[i][2] =
						max({dp[l[i - 1] - 1][0], dp[l[i - 1] - 1][1], dp[l[i - 1] - 1][2]}) +
						sum[i - 2] - sum[l[i - 1] - 1] + y[i];
				else dp[i][2] = max(dp[l[i - 1]][1], dp[l[i - 1]][2]) +
						sum[i - 2] - sum[l[i - 1]] + y[i];
			}
			if (dp[i][0] < 0) dp[i][0] = inf;
			if (dp[i][1] < 0) dp[i][1] = inf;
			if (dp[i][2] < 0) dp[i][2] = inf;
		}
		printf("%lld\n", sum[n] - max({dp[n][0], dp[n][1], dp[n][2]}));
	} else {
		long long inf = 0x3f3f3f3f3f3f3f3f;
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0;
		dp[1][0] = 0;
		if (x[2] - x[1] > k) dp[2][0] = 0;
		else dp[2][1] = y[1] + y[2];
		if (x[3] - x[2] > k) dp[3][0] = min(dp[2][0], dp[2][1]);
		else {
			dp[3][0] = dp[2][1];
			dp[3][1] = y[2] + y[3];
			if (x[3] - x[1] <= k) dp[3][2] = y[1] + y[3];
		}
		for (int i = 4; i <= n; i++) {
			if (x[i] - x[i - 1] > k)
				dp[i][0] = min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
			else if ((i - l[i]) % 2 == 0)
				dp[i][0] = min({dp[l[i] - 1][0], dp[l[i] - 1][1], dp[l[i] - 1][2]}) +
					sum[i - 1] - sum[l[i] - 1];
			else dp[i][0] = min(dp[l[i]][1], dp[l[i]][2]) + sum[i - 1] - sum[l[i]];
			if (x[i] - x[i - 1] <= k)
				dp[i][1] = min({dp[i - 2][0], dp[i - 2][1], dp[i - 2][2]}) + y[i - 1] + y[i];
			if (x[i] - x[i - 2] <= k) {
				if (x[i - 1] - x[i - 3] > k)
					dp[i][2] = min({dp[i - 3][0], dp[i - 3][1], dp[i - 3][2]}) + y[i - 2] + y[i];
				else if ((i - 2 - l[i - 1]) % 2 == 0)
					dp[i][2] =
						min({dp[l[i - 1] - 1][0], dp[l[i - 1] - 1][1], dp[l[i - 1] - 1][2]}) +
						sum[i - 2] - sum[l[i - 1] - 1] + y[i];
				else dp[i][2] = min(dp[l[i - 1]][1], dp[l[i - 1]][2]) +
						sum[i - 2] - sum[l[i - 1]] + y[i];
			}
			if (dp[i][0] > inf) dp[i][0] = inf;
			if (dp[i][1] > inf) dp[i][1] = inf;
			if (dp[i][2] > inf) dp[i][2] = inf;
		}
		printf("%lld\n", sum[n] - min({dp[n][0], dp[n][1], dp[n][2]}));
	}
	return 0;
}
```

---

## 作者：xishanmeigao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7987)

我们钦定所有分组 $(i,j)$ 形成的区间都是不相交或者互相包含的。即不存在类似 $(1,4),(2,3)$ 这样的分组。

不难发现，$j-i\in\{1,2\}$。因为若 $(i,i+3)$ 配对，则 $i+1,i+2$ 必定也可以配对，不符合极大的条件。

下面只考虑 $T=1$。

设 $f_{i,0/1}$ 表示 $i$ 和前面的点配对/不配对的最大体重，$W(i,j)$ 表示区间 $[i,j]$ 的体重和。

- 若 $i$ 不配对，设 $p$ 表示最大的位置满足 $a_i-a_p>K$，则 $[p+1,i-1]$ 的全部都要配对。如果该区间长度是偶数，相邻的配对即可， $f_{p,0/1}+W(p+1,i-1)\to f_{i,0}$。若是奇数，则单独考虑 $p+2$，$f_{p+1,1}+W(p+2,i-1)\to f_{i,0}$。
- 若 $i$ 配对。
  - 若配对 $i-1$，则 $f_{i-2,0/1}+y_{i-1}+y_i\to f_{i,1}$。
  - 若配对 $i-2$，设 $p$ 表示最大的位置满足 $a_{i-1}-a_p> K$。然后用类似 $i$ 不配对的转移去做。

$T=2$ 只需把 `max`变成 `min` 即可。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=1e5+10;

int n,K,x[N],y[N];
int s[N],pre[N];
int f[N][2];

int W(int i,int j)
{
	if(i>j) return 0;
	return s[j]-s[i-1];
}

int main()
{
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	int type;
	scanf("%d%d%d",&type,&n,&K);
	for(int i=1; i<=n; i++)
		scanf("%d%d",&x[i],&y[i]), s[i]=s[i-1]+y[i];

	for(int i=1; i<=n; i++)
	{
		int l=1,r=i-1,res=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(x[i]-x[mid]>K) res=mid, l=mid+1;
			else r=mid-1;
		}
		pre[i]=res;
	}

	if(type==1)
	{
		for(int i=1; i<=n; i++)
		{
			if(i>1)
			{
				if(x[i]-x[i-1]<=K) f[i][1]=max(f[i-2][0],f[i-2][1])+y[i]+y[i-1];
				if(i>2 && x[i]-x[i-2]<=K)
				{
					int p=pre[i-1];
					if(p==i-3) f[i][1]=max(f[i][1],max(f[p][0],f[p][1])+y[i-2]+y[i]);
					else
					{
						int t=i-3-(p+1)+1;
						if(t&1) f[i][1]=max(f[i][1],f[p+1][1]+W(p+2,i-3)+y[i-2]+y[i]);
						else f[i][1]=max(f[i][1],max(f[p][0],f[p][1])+W(p+1,i-3)+y[i-2]+y[i]);
					}
				}
			}
			int p=pre[i];
			if(p+1>i-1) f[i][0]=max(f[p][0],f[p][1]);
			else
			{
				int t=i-1-(p+1)+1;
				if(t&1) f[i][0]=f[p+1][1]+W(p+2,i-1);
				else f[i][0]=max(f[p][0],f[p][1])+W(p+1,i-1);
			}
		}

		int ans=max(f[n][0],f[n][1]);
		printf("%d\n",s[n]-ans);
	}	
	else
	{
		memset(f,0x3f,sizeof(f));

		f[0][0]=f[0][1]=0;
		for(int i=1; i<=n; i++)
		{
			if(i>1)
			{
				if(x[i]-x[i-1]<=K) f[i][1]=min(f[i-2][0],f[i-2][1])+y[i]+y[i-1];
				if(i>2 && x[i]-x[i-2]<=K)
				{
					int p=pre[i-1];
					if(p==i-3) f[i][1]=min(f[i][1],min(f[p][0],f[p][1])+y[i-2]+y[i]);
					else
					{
						int t=i-3-(p+1)+1;
						if(t&1) f[i][1]=min(f[i][1],f[p+1][1]+W(p+2,i-3)+y[i-2]+y[i]);
						else f[i][1]=min(f[i][1],min(f[p][0],f[p][1])+W(p+1,i-3)+y[i-2]+y[i]);
					}
				}
			}
			int p=pre[i];
			if(p+1>i-1) f[i][0]=min(f[p][0],f[p][1]);
			else
			{
				int t=i-1-(p+1)+1;
				if(t&1) f[i][0]=f[p+1][1]+W(p+2,i-1);
				else f[i][0]=min(f[p][0],f[p][1])+W(p+1,i-1);
			}
		}

		int ans=min(f[n][0],f[n][1]);
		printf("%d\n",s[n]-ans);
	}	
	
	return 0;
}
```

---

## 作者：StillEmpty (赞：0)

笑死了，做完一看题解发现自己的做法巨臭巨长，明明是差不多的 dp。本题看我思路就好了，别学我的代码实现，因为不仅长，边界细节还巨恶心。

首先毫无疑问我们先按 $x$ 排序。dp 状态设计还是很容易想出来的：假设只有前 $i$ 头牛存在，第 $i$ 头牛是最后剩余的情况下的最优答案。

然后我们发现一个问题，影响答案的因素不仅仅是上一个剩余牛在哪，还有上一个剩余牛前面的不剩余牛的数量的奇偶性。其实很好理解，如果一个剩余牛前面的不剩余牛有奇数个，那这个剩余牛后面一个牛必须和前面的牛配对。我们进一部推导可以得到：

如果一个剩余牛前面有奇数个不剩余牛，那这个剩余牛前一个牛和后一个牛都是不剩余牛。

这非常好理解，因为如果两牛配对则距离小于 $k$，而如果两牛之间隔了两个不剩余牛则说明它们的距离大于 $k$，所以若两牛配对则它俩之间最多只有一个剩余牛。

为了避免更恶心的判断，我们称 $f_i$ 为在前 $i$ 位有偶数个不剩余牛的情况下，第 $i$ 位为剩余牛的答案与 第 $i-1$ 位为剩余牛的答案的较优值。（最后我发现这个看似简单的更简单的方法导致了更多的恶心。）

然后我们还要记录当前前一个距离大于 $k$ 的牛，还要记录从左到右第一个能选的牛（因为可能与太左的牛间间隔的牛中存在距离大于 $k$ 的，以上记录还要分奇偶记录，所以高度不建议使用我这个实现：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int t, n, k, init;
struct Cow {
    int x, y;
    bool operator<(const Cow &fuck) const {return x < fuck.x;}
} a[N+1];
bool nogkaft[N+1]; int llim[N+2][2], rlim[N+1];
int ans, f[N+1], g[N+1], tr[N+1][2];
int choose(int a, int b) {
    if(t == 1) return min(a, b);
    else return max(a, b);
}
int trans(int i, bool b) {
    int ret = tr[rlim[i]][b];
    if(rlim[i]%2 == (!b) && rlim[i]+1 < i) ret = choose(ret, g[rlim[i]+1]);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t >> n >> k; init = (t == 1) ? 1e9 : -1e9; ans = init;
    for(int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
    sort(a+1, a+n+1);
    {
        if(n % 2 == 1) goto Q;
        for(int i = 1; i <= n; i += 2) {
            if(a[i+1].x-a[i].x > k) goto Q;
        }
        if(t == 1) {
            cout << 0 << endl; exit(0);
        }
        else ans = 0;
    }
    Q: a[0].x = -1e9;
    for(int i = 1; i <= n; ++i) {
        int l = 0, r = i-1;
        while(l < r) {
            int mid = (l+r+1)/2;
            if(a[i].x-a[mid].x > k) l = mid;
            else r = mid-1;
        }
        rlim[i] = l;
    }
    nogkaft[n] = true;
    for(int i = n-2; i >= 1; i -= 2) {
        if(a[i+2].x-a[i+1].x <= k) nogkaft[i] = true;
        else break;
    }
    tr[0][0] = 0; tr[0][1]= init; llim[1][0] = 0; llim[1][1] = 114514;
    for(int i = 1; i <= n; ++i) {
        bool b = i%2; f[i] = init; g[i] = init;
        if(llim[i][!b] <= rlim[i]) f[i] = trans(i, !b)+a[i].y;
        if(llim[i-1][!b] <= rlim[i-1] && i >= 3 && i < n && a[i].x-a[i-2].x <= k) g[i] = trans(i-1, !b)+a[i-1].y;
        if(a[i].x-a[i-1].x > k) {
            tr[i][b] = choose(f[i], g[i]);
            tr[i][!b] = tr[i-1][!b];
            llim[i+1][b] = i; llim[i+1][!b] = llim[i][!b];
        }
        else {
            tr[i][b] = choose(tr[i-1][b], choose(f[i], g[i]));
            tr[i][!b] = tr[i-1][!b];
            llim[i+1][0] = llim[i][0]; llim[i+1][1] = llim[i][1];
        }
        if(nogkaft[i]) ans = choose(ans, choose(f[i], g[i]));
    }
    cout << ans << endl;
    return 0;
}
```

---

