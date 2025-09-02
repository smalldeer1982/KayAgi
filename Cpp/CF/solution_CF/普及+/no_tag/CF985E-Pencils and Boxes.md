# Pencils and Boxes

## 题目描述

Mishka received a gift of multicolored pencils for his birthday! Unfortunately he lives in a monochrome world, where everything is of the same color and only saturation differs. This pack can be represented as a sequence $ a_{1},a_{2},...,a_{n} $ of $ n $ integer numbers — saturation of the color of each pencil. Now Mishka wants to put all the mess in the pack in order. He has an infinite number of empty boxes to do this. He would like to fill some boxes in such a way that:

- Each pencil belongs to exactly one box;
- Each non-empty box has at least $ k $ pencils in it;
- If pencils $ i $ and $ j $ belong to the same box, then $ |a_{i}-a_{j}|<=d $ , where $ |x| $ means absolute value of $ x $ . Note that the opposite is optional, there can be pencils $ i $ and $ j $ such that $ |a_{i}-a_{j}|<=d $ and they belong to different boxes.

Help Mishka to determine if it's possible to distribute all the pencils into boxes. Print "YES" if there exists such a distribution. Otherwise print "NO".

## 说明/提示

In the first example it is possible to distribute pencils into $ 2 $ boxes with $ 3 $ pencils in each with any distribution. And you also can put all the pencils into the same box, difference of any pair in it won't exceed $ 10 $ .

In the second example you can split pencils of saturations $ [4,5,3,4] $ into $ 2 $ boxes of size $ 2 $ and put the remaining ones into another box.

## 样例 #1

### 输入

```
6 3 10
7 2 7 7 4 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 2 3
4 5 3 13 4 10
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3 2 5
10 16 22
```

### 输出

```
NO
```

# 题解

## 作者：lenlen (赞：11)

### Problem

题目大意：给定一个序列 $a$，要求能不能把该序列分成若干个序列，满足任意一组元素个数不少于 $k$，最大值与最小值的差不大于 $d$，每个元素只能放进一组。

数据范围： $k,n \leq 5 \times 10^5,d,a_i \leq 10^9$。

### Solution

一道容易的贪心+ DP（放在 Div2 E 有点水了）。

我们可以想到一种贪心思路，排完序后按顺序取，看能否满足条件。若我们有一组内不是按顺序取的，比如排完序后数组为 $a_1,a_2, \cdots ,a_n$，有一组是 $a_l,a_{l+1}, \cdots ,a_{i-1},a_{i+1}, \cdots ,a_{r-1},a_r$。那么 $a_i$ 无论放进哪一个组，都会增加那一组的最大值与最小值的差值，肯定不优。

我们可以设 $f_i$ 表示以 $i$ 结尾的前缀数组能否满足条件。转移式：

$$f_{i-1}=1 \Rightarrow f_j=1(j-i+1 \geq k,a_j-a_i \geq d)$$

初始状态 $f_0=1$，每次遍历 $[i+k-1,n]$。

可是如果我们对于每一个 $f_{i-1}=1$，都去遍历一遍 $[i,n]$，那么会被极限数据卡到 TLE。所以我们要考虑优化：对于一个 $i$ 前面一个满足条件的 $j$ 遍历到了 $p$，即 $a_p-a_j>d$ 或者 $p-j+1<k$。那么我们考虑对于 $i(i>j)$ 时，要不要遍历 $[i,p-1]$。显然是不用的，因为 $j$ 遍历到 $p$ 结束，证明对于 $k \in [j+k-1,p],f_k=1$，没必要再更新。所以每一次遍历 $[\max(p,i+k-1),n]$ 即可。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7232;
int n,m,d,a[N];
int f[N];
int mx(int x,int y)
{
    return x>y?x:y;
}
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    f[0]=1;
    for(int i=1,j=1;i<=n&&!f[n];i++)
    {
        if(f[i-1])
        {
            j=mx(j,i+m-1);
            while(j<=n&&a[j]-a[i]<=d)
            {
                f[j]=1;
                ++j;
            }
        }
    }
    if(f[n]) printf("YES\n");
    else printf("NO\n");
}
```


---

## 作者：hzoi_liuchang (赞：6)

### 分析
这道题我们要用到$bool$类型的$DP$

为了方便处理，我们将所有数从小到大排一下序

我们设$f[i]$为当前遍历到第$i$个数，是否合法

其中值为$1$代表合法，值为$0$代表不合法

在转移时需要枚举每一个左端点，如果左端点的状态合法，我们再用当前的状态不断向右更新

最后如果$f[n]$为$1$，那么输出`YES`,否则输出`NO`
### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
typedef long long ll;
bool f[maxn];
ll a[maxn];
int main(){
    ll n,k,d;
    scanf("%lld%lld%lld",&n,&k,&d);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+1+n);
    f[0]=1;
    ll p=1;
    for(ll i=0;i<=n;i++){
    	if(f[i]){
    		p=max(p,i+k);
    		while(p<=n && a[p]-a[i+1]<=d){
    			f[p]=1;
    			p++;
    		}
    	}
    }
    if(f[n]==0) printf("NO\n");
    else printf("YES\n");
    return 0;
}
```

---

## 作者：JWRuixi (赞：4)

CF 难度 $2100$，感觉上有点高。。。

- 分析

由于 $n$ 达到 $5 \times 10^5$，所以考虑线性做法，显然不能贪心，所以考虑 dp。

由于存在减法影响答案，可以考虑先进行排序，显然一定选一段连续的数。可以观察到对于一个左端点，右端点一定单调不降，这样的话就可以单调队列维护右端点。

如此启发我们搞 dp，设 $f_i$ 表示前 $i$ 个数是否能分成满足题意的若干段。显然，转移即是否存在端点 $j$ 使得 $f_{j-1}$ 等于 $1$ 且 $j$ 到 $i$ 可分为满足题意的一组。

利用我们之前的到的方法，我们可以快速将一个左端点转移到一个右端点，所以时间复杂度 $O(n)$，具体见代码。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 5e5 + 500;

int n, a[maxn], f[maxn], k, d;

signed main () {
	n = read(), k = read(), d = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	f[0] = 1;
	int j = 1;
	for (int i = 0; i <= n; i++) {
		if (f[i]) {
			j = max(j, i + k);
			while (j <= n && a[j] - a[i + 1] <= d) f[j] = 1, j++;
		}
	}
	if (f[n]) puts("YES");
	else puts("NO");
}
```

---

## 作者：_edge_ (赞：3)

大家好，我是暴力数据结构选手。

首先一看到这道题目，就应该要想到贪心，将其从小到大排序肯定是最优的，证明大概就是考虑如果一个中间的数被换出去，肯定不优。

脑子一抽就想到暴力 DP，然后用数据结构来维护掉。

具体的，设 $f_i$ 表示 $i$ 结尾的能不能分出来。

然后转移就是 $f_i \leftarrow f_j \vee f_i$ 并且 $a_i-a_{j+1}\le d$ 以及 $i-j \ge k$。

我们发现这两个限制条件都具有单调性，及对于 $a_i$ 能到达的最远的 $a_{j+1}$ ，$a_{j+2}$ 也肯定满足所需要的条件，通过这一点，可以用二分来将最远的点搞出来。

对于第二个限制条件，可以计算最近的 $j$ 满足条件，然后这个题目就变成了给定一个区间，求区间是否有 $1$。

然后这就是暴力树状数组或者线段树来维护就可以了。

时间复杂度 $O(n \log n)$。

~~我自己脑子一抽用了个 ST 表，但实际上根本不用。~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=5e5+5;
int n,k,d,a[INF],f[INF][25],f1[INF][25],lg[INF],ll[INF],ff[INF];
int query(int l,int r) {
	int len=lg[r-l+1];
	return max(f[l][len],f[r-(1<<len)+1][len]);
}
int query1(int l,int r) {
	int len=lg[r-l+1];
	return min(f1[l][len],f1[r-(1<<len)+1][len]);
}
int tree[INF];
void t_add(int x,int y) {for (int i=x;i<=5e5;i+=i&-i) tree[i]+=y;return ;}
int t_query(int x) {int sum=0;for (int i=x;i;i-=i&-i) sum+=tree[i];return sum;}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k>>d;
	for (int i=1;i<=n;i++) 
		cin>>a[i];
	sort(a+1,a+1+n);
	for (int i=1;i<=n;i++) 
		f[i][0]=a[i],f1[i][0]=a[i];
	for (int i=1;i<=25;i++) {
		if ((1<<i)>n) break;
		for (int j=1;j+(1<<i)-1<=n;j++) {
			f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
			f1[j][i]=min(f1[j][i-1],f1[j+(1<<(i-1))][i-1]);
		}
	}
	lg[0]=-1;
	for (int i=1;i<=n;i++)
		lg[i]=lg[i>>1]+1;
	ff[0]=1;
	for (int i=1;i<=n;i++) {
		int l=1,r=i,ans=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (a[i]-a[Mid]<=d) r=(ans=Mid)-1;
			else l=Mid+1;
		}
		ll[i]=ans-1;
	}
	
	for (int i=k;i<=n;i++) {
		if (ll[i]==0) ff[i]=1;
		else {
			if (ll[i]>i-k) continue;
			int kk=t_query(i-k)-t_query(ll[i]-1);
			ff[i]=(kk>=1);
		}
		t_add(i,ff[i]);
//		cout<<i<<" "<<ff[i]<<" "<<ll[i]<<" overrrr\n";
	}
	if (ff[n]) cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}
```



---

## 作者：NaN_HQJ2007_NaN (赞：2)

贪心+DP。

先从小到大排序。

定义 $f_i$ 表示序列 $[1,i]$ 能否分组。

转移为 $f_i|=f_j[a_i-a_j\le d,j\le i-k+1]$。

右区间可以直接算出来，左区间可以二分或根据单调性弄个指针。

定义 $sum_i=\sum\limits_{t=1}^{i}f_t$，前缀和减一下判断是否为正即可。

复杂度 $O(n\log n)$ 或 $O(n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int sum[N],n,k,d,a[N];
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>k>>d;
  for(int i=1;i<=n;++i)cin>>a[i];
  sort(a+1,a+n+1);
  int ok,l,r;
  for(int i=1;i<=n;++i){
    ok=0;
    if(i>=k&&a[i]-a[1]<=d)ok=1;
    l=lower_bound(a+1,a+n+1,a[i]-d)-a;r=i-k+1;
    if(l<=r&&sum[r-1]-sum[max(l-2,0)])ok=1;
    sum[i]=sum[i-1]+ok;
  }
  if(ok)cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
  return 0;
}

```


---

## 作者：fa_555 (赞：2)

under 题解 [CF985E](https://www.luogu.org/problem/CF985E)

---

### 题意

给定大小为 $n$ 的可重集合 $T$ 与整数 $k, d$，求若干互不相交的可重集合 $S_i$，使得

- $\bigcup S_i = T$

- $|S_i| \ge k$

- $\max\{S_i\} - \min\{S_i\} \le d$

判断能否找到一组合法的解。

- $1 \le k, n \le 5 \times 10^5, \ d \le 10^9$

### 解题

初看题面，很容易想到一种贪心做法：

从小到大排序，每次选择第一个未被选用的数 $a_i$，将 $a_i \sim a_i + d$ 的所有数划分到同一集合中。

不难想到这种算法是错误的。考虑数据 `4 2 1 1 2 2 3`，就可以把这种算法卡掉。对于这组数据，唯一合法的划分方案为 $S_1 = \{1, 2\}, S_2 = \{2, 3\}$。上述贪心将两个元素 `2` 划分到了同一个集合中，导致 `3` 无法分配。

~~自然想到~~利用 dp。

令 `f[i]` 表示前 i 个数有无合法划分方案。转移时利用队列，考虑 `a[i] - a[i - K]` 的差值与 `k` 的大小关系。细节见代码。

### 代码

``` cpp
#include<algorithm>
#include<bitset>
#include<iostream>
#include<queue>

std::bitset<500003> f;
int N, K, D, z[500003];
std::queue<int> q;

bool dp() {
	f[0] = 1;
	for (int i = K; i <= N; ++i) {
		if (f[i - K]) q.push(z[i - K + 1]);
		while (q.size() && z[i] - q.front() > D)
			q.pop();
		f.set(i, (bool)q.size());
	}
	return f[N];
}

int main() {
	std::cin >> N >> K >> D;
	for (int i = 1; i <= N; ++i)
		std::cin >> z[i];
	std::sort(z + 1, z + N + 1);
	std::cout << (dp() ? "YES" : "NO");
	return 0;
}


```

---

## 作者：awa水水湖awa (赞：1)

# [Pencils and Boxes 题目链接](https://www.luogu.com.cn/problem/CF985E)
######  ~~第一篇题解，求过。~~
# 问题：
题目大意：给出一个序列 $a$，将其任意分成若干段（可以打乱顺序），使每段长度大于等于 $k$ 且最大值和最小值的差值小于等于 $d$。

数据范围：$1 \le n \le 5 \times10^5$，$0 \le d \le 10^9$，$1 \le a_i \le 10^9$
## 思路：
首先想到从小到大排序，然后**贪心**。细想一下，发现不行。

hack:
```cpp
7 3 3
1 1 2 2 4 5 6
```
可以看到，如果每次选刚好 $k$ 个，会选出 `1 1 2,2 4 5,6` 三组。如果每次按多了选，会选出 `1 1 2 2 4,5 6` 两组。显然不合题意。

------------

考虑**动态规划**。

设 $f_i$ 表示前 $i$ 个数是否能分成满足题意的组，有值表示合法，没值表示非法。每次都尝试能否将一整个合法组添加至上一个合法组。

$last_i$ 表示第一个能与 $i$ 分在一组的数，即 $a_i-a_{last_i}\le d$。

由此得出若 $i-last_i+1 \ge k$ 且 $i-k$ 至 $last_i-1$ 中存在合法的 $f_j$，则可以将长度为 $k$ 至 $i-last_i+1$ 的合法组拼到上一个合法组，即 $f_i$ 合法。如果每一次都将区间枚举时间复杂度太大，可以用前缀和优化。

举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ov50acw.png)

首先枚举第一段的合法组有哪些，得：

![](https://cdn.luogu.com.cn/upload/image_hosting/y01cma5e.png)

然后从 $i=5$ 开始找能否将新的组拼在上一个合法组后，发现 $i=5$ 不行。

到 $i=6$。可以将 $6-k+1$ 至 $6$ 的合法组 $(2,4,5)$ 拼到 $f_{last_6}$ 的合法组后，所以 $f_6$ 合法。

到 $i=7$。可以将 $7-k+1$ 至 $7$ 的合法组 $(4,5,6)$ 拼到 $f_{last_7-1}$ 的合法组后，所以 $f_7$ 合法。

到 $i=8$。可以将 $8-k+1$ 至 $8$ 的合法组 $(5,6,6)$ 拼到 $f_{last_8}$ 的合法组后，或将 $last_8$ 至 $8$ 的合法组 $(4,5,6,6)$ 拼到 $f_{last_8-1}$ 的合法组后，所以 $f_8$ 合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/0eh2je76.png)

发现 $f_8$ 不为 $0$，所以有解。

## 解题步骤：
1. 首先将序列 $a$ 从小到大排序。
```cpp
	sort(a+1,a+n+1);
```

2. 预处理每一个 $a_i$ 从左往右数第一个满足 $a_i-a_j\le d$ 的数记为 $last_i$。
```cpp
	int L=1;
	for(int i=1;i<=n;i++)
	{
		while(a[i]-a[L]>d)
		{
			L++;
		}
		last[i]=L;
	}
```
3. 先处理出第一段的结果有哪些。
```cpp
	for(int i=k;i<=n;i++)//从k开始是因为不满k个分出来的组不合法。
	{	
		if(a[i]-a[1]<=d)
		{                     
			f[i]+=1;
			f[i]+=f[i-1];
		}
		else break;
	}
```
从 $k$ 开始是因为不满 $k$ 个分出来的组不合法。

4. 动态规划。
```cpp
	for(int i=k+1;i<=n;i++)
	{
		if((i-last[i]+1)>=k && f[i-k]-f[last[i]-2])//(f[i-k]-f[last[i]-1])+(f[last[i]-1]-f[last[i]-2)整理得f[i-k]-f[last[i]-2]
		{
			f[i]++;//有合法解
		}
		f[i]+=f[i-1];//前缀和
	}
```
5. 判断 $f_n$ 是否有合法解。
```cpp
	if(f[n]-f[n-1]!=0)cout<<"YES";//f[n]-f[n-1]是因为用了前缀和
	else cout<<"NO";
```

## 代码
```cpp
	//题号:CF985E
	#include<bits/stdc++.h>
	using namespace std;
	long long k,n,d,a[500005],last[500005],f[500005];//10^9,用long long保险点
	int main()
	{
		cin>>n>>k>>d;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		int L=1;
		for(int i=1;i<=n;i++)
		{
			while(a[i]-a[L]>d)
			{
				L++;
			}
			last[i]=L;
		}
		for(int i=k;i<=n;i++)
		{
			if(a[i]-a[1]<=d)
			{                     
				f[i]+=1;
				f[i]+=f[i-1];
			}
			else break;
		}
		for(int i=k+1;i<=n;i++)
		{
			if((i-last[i]+1)>=k && f[i-k]-f[last[i]-2])//(f[i-k]-f[last[i]-1])+(f[last[i]-1]-f[last[i]-2])整理得f[i-k]-f[last[i]-2]
			{
				f[i]++;//有合法解
			}
			f[i]+=f[i-1];//前缀和
		}
		if(f[n]-f[n-1]!=0)cout<<"YES";//f[n]-f[n-1]是因为用了前缀和
		else cout<<"NO";
	
		return awa;
	}
```

---

## 作者：caoshuchen (赞：1)

# [Pencils and Boxes](https://www.luogu.com.cn/blog/caoshuchen/cf985e-zhong-zhuai)

## 思路

首先，这道题最先是想到**贪心**，我们先将数组升序排序，然后依次看每一个位置最多能与它后面那个元素组合，然后把这两个数围出的区间全部组在一起，但是这有个问题：如果说分最后一个区间不够了，那我们就需要拿前面的补，而如果前面分不出来（元素个数等于$k$），就需要更靠前的来不给前一个区间，前一个区间再补给当前这个区间，但如果前面的前面也分不出来那就又要往前找。这是什么特征？**有后效性**。

那我们就换下一个思路，很明显，既然贪心解决不了那就换 dp，从零维（贪心）升到一维，来保证**无后效性**。

先是还要从小到大排个序，目的是方便进行查找最大最小的差值，从而更容易的保证分组正确性。

然后定义一个 $dp[i]$ 表示前 $i$ 个元素能否分组成功，那么初始值为 $dp[0]= true$ 那我们就可以看一下怎么递推 dp：

首先我们要枚举以 $j$ 为左边界 $i$ 为右边界的区间，使得区间长度 $\ge k$ 并且 $a_i-a_j \le d$ 然后我们就可以说明 $[j,i]$ 这个区间是成立的，所以 $dp[i]$ 成不成立就变向取决于 $dp[j-1]$ 成不成立，所以我们只需要枚举所有合法的 $j$ 即可，所以有公式：

$$dp[i]=dp[i] || dp[j-1](j\le i - k + 1,a_i-a_j\le d)$$

但是我们会发现时间复杂度会失控得达到 $O(n^2)$ 的级别，所以我们需要优化。

我们最先发现：这个 $i$ 在往后移的同时 $j$ 的下界也会随之往后或静止不动，但不会往前移，因为 $a_i-a_j\le d, a_i-a_{j-k}>d$ 那么由于升序排列，$a_{i+1}>a_i$ 则 $a_{i+1}-a_{j-k}>a$ 恒成立，所以说，我们可以进行双指针的操作来对 $j$ 的下界进行维护。

既然我们原本就知道 $j$ 的上界，现在又可以通过双指针找到下界，那么整个枚举的区间就已知了，我们只需要知道区间 $[j_{low}-1,j_{up}-1]$ 中是否有某个 dp 值为 true 即可。

那我们就可以使用线段树或树状数组来进行查找与修改，复杂度也是理想的 $O(\log_2n)$ 加上枚举 $i$ 的一层循环，最终复杂度为 $O(n\log_2n)$。

## [Code](https://www.luogu.com.cn/paste/h0czxzgg)

**这个标题是超链接，里面有更详细的代码**

```c++
#include <bits/stdc++.h>
using namespace std;

inline int lowbit(int x) {
	return x & (-x);
}

int n, k, d;
int a[500005];
bool dp[500005];

int t[500005];

void mdf(int x, int v) {
	while (x <= n + 1)
		t[x] += v, x += lowbit(x);
}
int qry(int x) {
	if (x <= 0)
		return 0;
	int ans = 0;
	while (x)
		ans += t[x], x -= lowbit(x);
	return ans;
}

int main() {
	cin >> n >> k >> d;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	dp[0] = true;
	mdf(1, 1);
	for (int i = 1, j = 1; i <= n; i++) {
		while (a[i] - a[j] > d) j++;
		if (qry(i - k + 1) - qry(j - 1) >= 1)
			dp[i] = true, mdf(i + 1, 1);
	}
	if (dp[n])
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}

```

---

## 作者：linaonao (赞：1)

## 思路
题目不是很难，要求一个可行方案，使所有整数被分到元素数大于等于$k$的集合，且统一集合中相差最大的两个元素只差小于等于$d$。

于是我们先用一点贪心的想法，把这个数列能分的（即相差小于$d$）且数量够的先分，不能分的再开一组，就很好解决了。

再用dp来处理，因为$n\le5*10^5$ , 所以用一个一位数组$f[i]$记录到第$n$个数是否可行（1可行，0不可行）。

具体方法是找到一个$f[i]$可行，移动指针$now$，通过比较$a[i+1]+d$与$a[now]$的大小来得出$f[now]$的值，最后看$f[n]$的值输出$YES$或$NO$。

还有一个注意点：如果($now<i+know$),可以直接从$i+k$开始，减少循环次数。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define N 500005
#define rint register int
#define ll long long 
#define in inline 
#define gc getchar
#define pc putchar
template<typename T>in void read(T &x){
	x=0;int f=0;char ch=gc();
	for(;!isdigit(ch);ch=gc())f|=ch=='-';
	for(;isdigit(ch);ch=gc())x=(x<<1)+(x<<3)+(ch^48);
	x=f?-x:x; 
} 
template<typename T>in void write(T x){
	if(x<0){pc('-');x=-x;}
	else if(x>9)write(x/10);
	pc(x%10+48);
}
using namespace std;
ll k,n,d,a[N],f[N];
int main(){
	cin>>n>>k>>d;
	for(rint i=1;i<=n;++i){
		read(a[i]);
	}
	sort(a+1,a+n+1);
	f[0]=1; ll now=1;
	for(rint i=0;i<=n;++i){
		if(f[i]){
			now=max(now,i+k);
			while(now<=n&&a[i+1]+d>=a[now]) f[now++]=1;
		}
	} 
	if(f[n]==0)printf("NO");
	else printf("YES");
	return 0;
}//题目不难，但最好自己打一遍
~~~

#### 这是我的第一篇题解，求过！

---

## 作者：Vidoliga (赞：0)

### 题意

给定集合 $S$，让你判断能否划分集合 $S=T_1\cup T_2 \cup T_3 \cup \dots \cup T_p$，并且 $T_1\cap T_2 \cap T_3 \cap \dots \cap T_p=\varnothing$。
并满足 $\forall i,|T_i| \geq k$，并且 $\forall i,j \in T_s,|i-j| \leq d$ 。

很裸的 $dp$ 。

考虑朴素状态和转移。

首先你发现将集合排序，然后区间划分一定不劣。

于是从小到大排序，设 $f_i$ 表示以 $i$ 为结尾是否可行，$1$ 表示可行，$0$ 表示不可行。

显然可以写出 $O(n^2)$ 转移：$f_i=\max_{j=1}^{i-k+1}(f_{j-1}[a_i-a_j \leq d])$。

然后你发现要满足 $a_i-a_j \leq d$ 一定是存在某个 $r$ ，满足 $\forall j \in [r,i],a_i-a_j \leq d$

又由于 $a$ 单调性，所以 $r$ 单调递增，那么可以类似单调队列做。

复杂度 $O(n)$。

实现细节可用前缀和。

```cpp
signed main(){
	n=read();k=read();d=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	f[0]=1;g[0]=1;
	int r=0;
	for(int i=1;i<=n;i++){
		while(r<=i&&a[i]-a[r]>d) r++;
		if(i-r+1>=k) f[i]=((g[i-k]-g[r-2])!=0);
		g[i]=g[i-1]+f[i];
	}
	f[n]?puts("Yes"):puts("No");
	return 0;
}
```


---

