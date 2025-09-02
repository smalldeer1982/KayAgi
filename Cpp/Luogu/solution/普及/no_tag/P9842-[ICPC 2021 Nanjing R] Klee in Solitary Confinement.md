# [ICPC 2021 Nanjing R] Klee in Solitary Confinement

## 题目描述

自从旅行者来到蒙德，蒙德的人们突然对计算机编程和算法产生了极大的兴趣，包括西风骑士团的火花骑士可莉。

被琴再次关进禁闭室后，可莉决定花时间学习著名的 Mo's 算法，该算法可以在不进行修改的情况下以 $\mathcal{O}(n^{1.5})$ 的时间复杂度计算某些区间查询问题。

为了检查可莉是否真正掌握了该算法（或者实际上是在秘密制造另一个炸弹），琴给了她一个整数序列 $a_1, a_2, \cdots, a_n$ 和一些查询 $[l_i, r_i]$，要求她找到连续子序列 $a_{l_i}, a_{l_i + 1}, \cdots, a_{r_i}$ 中的众数。众数是指在子序列中出现次数最多的数字。

在 Mo's 算法的帮助下，可莉毫不费力地解决了这个问题，但她脑海中又出现了另一个问题。给定一个长度为 $n$ 的整数序列 $a_1, a_2, \cdots, a_n$ 和一个整数 $k$，你可以最多进行一次以下操作：选择两个整数 $l$ 和 $r$，使得 $1 \le l \le r \le n$，并将 $k$ 加到每个 $a_i$ 上，其中 $l \le i \le r$。注意可以选择不进行此操作。计算如果你选择最优地进行（或不进行）操作，整个序列的众数的最大出现次数。

## 说明/提示

对于第一个样例测试用例，选择 $l = 1$ 和 $r = 2$，我们将得到序列 $\{4, 4, 4, 4, 4\}$。显然，众数是 $4$，出现了 $5$ 次。

对于第二个样例测试用例，选择 $l = 4$ 和 $r = 6$，我们将得到序列 $\{3, 2, 3, 3, 3, 3, 3\}$。众数是 $3$，出现了 $6$ 次。

对于第四个样例测试用例，选择不进行操作。众数是 $1$ 和 $-2$，它们都出现了 $3$ 次。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 2
2 2 4 4 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 1
3 2 3 2 2 2 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
7 1
2 3 2 3 2 3 3
```

### 输出

```
5
```

## 样例 #4

### 输入

```
9 -100
-1 -2 1 2 -1 -2 1 -2 1
```

### 输出

```
3
```

# 题解

## 作者：CashCollectFactory (赞：5)

这一套 ICPC 的问题全是关于原神的诶，可莉好可爱，所以必须交一份题解来宠爱可莉呢~

## 思路简述
1. 统计各个数在不同位置上出现次数的前缀和。对于 $x$ 来说，它可由 $x$ 和 $x-k$ 得到，而一个区间内的众数可通过枚举不同的区间得到。
2. 用 $sum[i][0]$ 表示该数字 $x$ 在下标 $i$ 处出现了几次。

3. 用 $sum[i][1]$ 表示该数字 $x-k$ 在下标 $i$ 处出现了几次。

容易得到递推公式：$ans = sum[n][0]+sum[r][1]-sum[l-1][1]-(sum[r][0]-sum[l-1][0])$。

化简得到：$ans = sum[n][0]+sum[r][1]-sum[r][0]+sum[l-1][0]-sum[l-1][1]$。

依照此式进行前缀和（类似动态规划）即可，最终时间复杂度为 $O(n)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,k,a[N],sum[N*4][2],mx,g,ans;
vector<int>e[N*4]; 
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];a[i]+=2e6;
        e[a[i]].push_back(a[i]);
        e[a[i]+k].push_back(a[i]);
        g=max(g,a[i]+k);
        mx=max({mx,(int)e[a[i]].size(),(int)e[a[i]+k].size()});
    }
    if(!k){
        cout<<mx/2<<endl;
		 return 0;
    }
    for(int i=0;i<=g;i++){
        if(e[i].size()==0) continue;
        for(int j=0;j<e[i].size();j++){
            sum[j+1][0]=sum[j][0]+(e[i][j]==i);
            sum[j+1][1]=sum[j][1]+(e[i][j]!=i);
        }
        int tmp=sum[1][0]-sum[1][1];
        for(int j=1;j<=e[i].size();j++){
            tmp=max(tmp,sum[j-1][0]-sum[j-1][1]);
            ans=max(ans,sum[e[i].size()][0]+sum[j][1]-sum[j][0]+tmp);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：3)

## Part 1 题目大意

给定一个长度为 $n$ 的序列，可以对区间 $[l,r]$ 整体加上 $k$，求最优情况下[众数](https://baike.baidu.com/item/%E4%BC%97%E6%95%B0/44796)的最大数量。

## Part 2 大体思路

由于 $1 \le n \le 10^6$，故不考虑 $O(n^2)$ 的做法，考虑 $O(n)$ 的做法。

**如何记录每个数的出现次数情况？**

也许你会像我一样第一时间想到 map，但事实是，map 的调用速度远远小于普通数组，如果使用 map 会出现超时的悲剧。

而 $-10^6 \le  a_i \le 10^6$，那我们就可以将读入进来的 $a_i$ 整体加上 $10^6$，这样子就变成 $0 \le a_i \le 2 \times 10^6$ 了。我们可以放心的开一个 $f$ 数组储存每个数出现的次数。

**什么时候可以不用考虑将区间 $[l,r]$ 整体加上 $k$?**

- 显而易见，当 $k = 0$ 时，也就是 $a_i$ 无论加不加上 $k$ 都不会有任何变化时。

- $a_{1 \dots n}$ 中的最大值 $maxn$ 和最小值 $minn$ 相差不超过 $| k |$ 时。因为就算是 $minn$ 加上 $| k |$ 后也会超过 $maxn$，这样就一定不会再和 $a_{1 \dots n}$ 中的任何数重合，众数的出险次数也就必然不会有任何改变。

**如何考虑将区间 $[l,r]$ 整体加上 $k$ 并求众数出现的次数？**

首先，如果我们让 $a_i$ 在区间 $[l,r]$ 中，令 $f_i$ 表示数字 $i$ 在整个序列中出现的次数，则造成的变化就是：

- $f_{a_i} \leftarrow \max(f_{a_i} - 1,0)$。

- $f_{a_i+k} \leftarrow f_{a_i + k} + 1$。

那么，我们就可以用一个数组 $g$ 来存储如上变化。

如何使用 $g$ 数组呢？上文中可以看到，如果我们用 $g$ 数组记录变化的话，那么 $g_{a_i + k} + f_{a_i+k}$ 就是在变化之后，$a_i + k$ 的出现次数。

对于答案 $result$，我们可以在枚举 $g$ 数组前对 $result$ 进行一次更新，让 $result$ 为 $f_{1 \dots n}$ 的最大值，再在 $g$ 数组枚举时，每次令 $result \leftarrow max(result,f_i + g_i)$。

## Part 3 代码 不含注释

```
#include <bits/stdc++.h>
using namespace std;
const int sum=2e6+5;
int n,m,a[sum],result,f[sum*2],g[sum*2],maxn=-1e9,minn=1e9;
inline int read()
{
	int x=0,y=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-') y=-1;ch=getchar();
	}
	while (ch>='0' && ch<='9')
	{
		x=x*10+int(ch-'0');ch=getchar();
	}
	return x*y;
}
int main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read()+sum;
		f[a[i]]++,maxn=max(maxn,a[i]),minn=min(minn,a[i]);
	}
	for (int i=1;i<=n;i++) result=max(result,f[a[i]]);
	if (maxn-minn<abs(m) || m==0) { cout<<result;return 0; }
	for (int i=1;i<=n;i++)
	{
		g[a[i]]=max(g[a[i]]-1,0);
		g[a[i]+m]++;
		result=max(result,g[a[i]+m]+f[a[i]+m]);
	}
	cout<<result;
	return 0;
}
```

---

## 作者：Thekhoi_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9842)

### P9842 [ICPC 2021 Nanjing R] Klee in Solitary Confinement=桶的应用+众数的概念

**注意到 $1\le n\le 10^6$，考虑 $O(n)$ 做法。**

考虑不需要进行任何操作的情况。

- 显然 $k=0$ 时，无论如何操作都不会改变 $a_i$ 的值。
 
-  记 $Max$，$Min$ 分别为 $a_1\sim a_n$ 中的最大值和最小值。

   当 $Min+\vert k\vert>Max$ 时，无论如何操作 $a_i$ 的值都不会再与 $a_1\sim a_n$ 中的数重合。故不会改变众数的出现次数。

此时直接输出众数个数即可。

**注意到 $-10^6\le a_i,k\le 10^6$。**

考虑 $a_i\gets a_i+2\times10^6$，则 $10^6\le a_i\le 3\times 10^6$，进而 $a_i-\vert k\vert\ge0，a_i+\vert k\vert\le 4\times 10^6$。

记 $s[i]$ 为 $i$ 出现的次数。 

对 $1\le i\le n$，有两种情形：

-  $i\notin [l,r]$，此时不需要进行操作。
-  $i\in [l,r]$，则 $a_i\gets a_i+k$。记 $f[i]$ 为 $i$ 的贡献，则 $f[a_i]\gets f[a_i]-1$，$f[a_i+k]\gets f[a_i+k]+1$。此时 $s[a_i+k]+f[a_i+k]$ 为 $a_i+k$ 出现的次数，更新 $ans$ 即可。     

可结合代码理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+5,M=1e6+5,V=2e6,Inf=1e8; 
int n,k,a[M],s[N],ans;
int Max=-Inf,Min=Inf,f[N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=V,s[a[i]]++;//这里加上V是为了让a[i]-|k|>=0
		Max=max(Max,a[i]),Min=min(Min,a[i]);
	}
	for(int i=1;i<=N;i++) ans=max(ans,s[i]);//求原始众数
	if(Max-Min<abs(k)||k==0){cout<<ans;return 0;}//特判  
	for(int i=1;i<=n;i++){
		f[a[i]]--,f[a[i]+k]++;
		if(f[a[i]]<0) f[a[i]]=0;
		ans=max(ans,f[a[i]+k]+s[a[i]+k]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：2)

## 解题思路
由于加的数是固定的，每个数只有两种情况 $a_i+k$ 或者 $a_i$，我们同时不难看出最终的答案必定为原数组，如果要让区间的所有数都修改会有影响，不妨存一个数组来记录前 $i$ 个数修改后的数据，每次我们从头到尾扫一遍原数组，将 $a_i+k$ 与 $a_i$ 的个数分别修改 $+1,-1$ 这样我们就可以通过修改后这个数的个数加上原来就有的个数即可，特别的，如果某个数的个数小于 $0$ 的时候，我们可以直接不取前面的，最大化，至于如果大于 $0$ 我们肯定希望这个数越多越好，所以不需要修改。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define re register
#define mp make_pair
#define pb push_back
#define lowbit(x) x&(-x)
#define FOR(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define ROF(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)
using namespace std;
inline int read(){
	int p=0, q=1;
	char ch=getchar();
	while (!isdigit(ch)) q=(ch=='-')?-1:1,ch=getchar();
	while (isdigit(ch)) p=(p<<3)+(p<<1)+(ch^48),ch=getchar();
	return p*q;
}
//--------------------------------------------------------------------
int n,k;
int ans=0;
int a[2000005];
int sum[5000005];
int res[5000005];
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[a[i]+2000000]++;
		ans=max(ans,sum[a[i]+2000000]);
	}
	for(int i=1;i<=n;i++){
		res[a[i]+2000000]--;
		res[a[i]+k+2000000]++;
		res[a[i]+2000000]=max(res[a[i]+2000000],0ll);
		ans=max(ans,sum[a[i]+k+2000000]+res[a[i]+k+2000000]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：卷王 (赞：2)

## 大体思路

这道题考验了桶的灵活运用和众数的概念。

众数指的是一个数列里面出现次数最多的那个数。比如：`1 2 3 3 4` 的众数就是 $3$，他出现了 $2$ 次。

于是我们很容易想到使用 $mp_i$ 表示 $i$ 的出现次数。

对于我们枚举到的所有 $i (1\leq i\leq n)$ 有两种情况：

* 不将 $i$ 放入我们选择的区间。$a_i$ 还是 $a_i$，所以不需要任何操作。

* 将 $i$ 放入我们选择的区间。$a_i$ 变成了 $a_i+k$，它的贡献是 $a_i$ 的个数减一，$a_i+k$ 的个数加一。那么显然，我们可以用一个数组 $ds_i$ 来记录这个贡献。

## 完整代码

我有两种代码，一种是用 map 实现的桶，一种是用偏移量解决 $a_i$ 是负数，无法作为桶的下标的问题。其中 map 因为复杂度是 $O(n\log n)$ 所以可能会 TLE。

map 版：（TLE on #88）

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() { int x = 0, f = 1; char ch = getchar(); while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); } while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); } return x * f; }
int n,k,maxx=-1e8,minn=1e8,ans=0,tmp=0,a[1000007]; map<int,int>mp,ds;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read(),mp[a[i]]++,maxx=max(maxx,a[i]),minn=min(minn,a[i]);
	for(int i=1;i<=n;i++) ans=max(ans,mp[a[i]]);
	if(maxx-minn<abs(k)||k==0) { printf("%d",ans); return 0; }
	for(int i=1;i<=n;i++){
		ds[a[i]]=max(ds[a[i]]-1,0);
		ans=max(ans,(++ds[a[i]+k])+mp[a[i]+k]);
	}
	printf("%d",ans);
	return 0;
}
```

偏移量版：（AC）

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() { int x = 0, f = 1; char ch = getchar(); while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); } while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); } return x * f; }
int n,k,maxx=-1e8,minn=1e8,ans=0,tmp=0,a[1000007],mp[4000007],ds[4000007];
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read(),a[i]+=2000001,mp[a[i]]++,maxx=max(maxx,a[i]),minn=min(minn,a[i]);
	for(int i=1;i<=n;i++) ans=max(ans,mp[a[i]]);
	if(maxx-minn<abs(k)||k==0) { printf("%d",ans); return 0; }
	for(int i=1;i<=n;i++){
		ds[a[i]]=max(ds[a[i]]-1,0);
		ans=max(ans,(++ds[a[i]+k])+mp[a[i]+k]);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：WZwangchongming (赞：1)

可莉可爱捏！但是没有芙芙可爱！



---

Solution：

直接考虑枚举众数的值。

假设枚举的这个众数的值为 $x$。那么我们可以知道，如果操作了一个区间 $[l,r]$，且这个区间里有 $a$ 个 $x$ 和 $b$ 个 $x-k$，那么最后 $x$ 的个数就会增加 $b-a$ 个。

所以就有一个很自然的贪心：让 $x$ 产生的贡献为 $-1$，$x-k$ 的贡献为 $1$，其余的贡献为 $0$，再求一个最大子段和。那么 $x$ 的最多出现次数只需要再加上 $x$ 原来的出现次数。最后对所有 $x$ 取一个最大值就可以得到答案。

但是这个贪心的时间复杂度是 $O(n^2)$ 的。

明显，既不是 $x$ 又不是 $x-k$ 的那些位置对答案不会产生影响。因此，对于每一个 $x$，单独把所有值为 $x$ 或 $x-k$ 的位置存进一个 vector 里，在每个 vector 中做最大子段和。这样每个数最多被放进 $2$ 个 vector，时间复杂度 $O(n)$。


---


Main code：


```cpp
void solve() {
	n = read(), k = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read() + 2e6;
		vec[a[i]].eb(-1), vec[a[i] + k].eb(1);
	}
	int ans = 0;
	for(int i = 0; i <= 4000000; i++) 
		if(vec[i].size()) {
			int res = 0, sum = 0;
			for(auto &x : vec[i]) if(x == -1) res++;
			ans = max(ans, res);
			for(auto &x : vec[i]) {
				sum = max(sum + x, x);
				ans = max(ans, res + sum);
			}
		}
	printf("%d\n", ans);
} 
```

---

## 作者：ziyanlin2013 (赞：1)

# 题解：P9842 [ICPC 2021 Nanjing R] Klee in Solitary Confinement

[题目传送门](https://www.luogu.com.cn/problem/P9842)  

# 简要题意
给定 $n,k$ 和一个长都 $n$ 的序列，你可以选择对一个区间 $[l,r]$ 的数整体加上 $k$，也可以不加。**最大化众数出现次数**并输出。

# 解题思路
考虑对于每一个 $a_i$ 计算最多能出现几次。发现如果对于等于 $a_i$ 的数加上 $k$ 的贡献为 $-1$，等于 $a_i-k$ 的数加上 $k$ 的贡献为 $1$，其他数的贡献为 $0$。答案就是求一个**最大子段和**。  

因为每一个数最多只会加入两次计算，所以复杂度为  $O(n)$ 。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
int n,k,a[N],maxx,f,b[2*N],m,ans,val;
int mp[4*N];
vector<int> e[2*N];
void work(int u,int x){
	f=0,ans=0;
	for (int v:e[x]){
		f=max(f,0)+v;
		ans=max(ans,f);
	}
	maxx=max(maxx,mp[u]+ans);
}
int sum(int x){
	return lower_bound(b+1,b+m+1,x)-b;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
        a[i]+=1000000;
		mp[a[i]]++;
		b[i*2-1]=a[i];
		b[i*2]=a[i]+k;
		maxx=max(maxx,mp[a[i]]);
	}
	if(k==0){
		cout<<maxx;
		return 0;
	}
	sort(b+1,b+2*n+1);
	m=unique(b+1,b+2*n+1)-b-1;
	for (int i=1;i<=n;i++){
		e[sum(a[i])].push_back(-1);
		e[sum(a[i]+k)].push_back(1);
	}
	for (int i=1;i<=2*n;i++){
		work(b[i],i);
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：Anakin_XYLei (赞：1)

## 题意
 
见题目。

## Solution

首先，给定数组的值域有正负，$k$ 也有正负，但范围较小，不妨直接开四倍数组来记录。

我们不妨先记录每个值出现的次数在 `cnt[]` 中。此处可以求一个答案的下界。

然后，我们枚举给定数组中的每个数 $A[i]$。并计算若把 $A[i]$ 或 $A[i]-k$ 作为众数，并在给区间 $[j,i]$ 加 $k$ 操作后用值为 $A[i]$ 或 $A[i]-k$ 的数的数量更新答案。

那么，怎么确定 $j$ 呢？

我们可以用一种前缀和的形式来处理。

用 $B[i]$ 表示给区间 $[1,i]$ 加 $k$ 操作后对值为 $i$ 的数的数量的影响。用 $minB[i]$ 表示 $B[1...i]$ 的最小值。此时 $minB[i]$ 所对应的 $B[j]$ 的 $j$ 即为最佳值。

显然，我们使用 $B[A[i]]-minB[A[i]]$ 即可得到最佳贡献，加上 $cnt[A[i]]$ 后更新答案。

同时，$A[i]+k$ 也有可能是最佳的众数，同样更新。

## Code

```cpp
#include <bits/stdc++.h>

const int N = 1e6+6;

int A[N];
int cnt[4*N];
int B[4*N];
int minB[4*N];
int n,k;
int res=0;
int main() {
    std::cin>>n>>k;
    for (int i=1;i<=n;i++) {
        std::cin>>A[i];
        A[i]+=2*N;
        cnt[A[i]]++;
        res=std::max(res,cnt[A[i]]);
    }
    for (int i=1;i<=n;i++) {
        B[A[i]]--;
        B[A[i]+k]++;
        minB[A[i]]=std::min(minB[A[i]],B[A[i]]);
        minB[A[i]+k]=std::min(minB[A[i]+k],B[A[i]+k]);
        res=std::max({res,cnt[A[i]]+B[A[i]]-minB[A[i]],cnt[A[i]+k]+B[A[i]+k]-minB[A[i]+k]});
    }
    std::cout<<res<<std::endl;
}
```

---

## 作者：SDLTF_凌亭风 (赞：1)

脑子题。吃了某一次模拟赛的亏，这次绝不使用数据结构做。当然，也确实不需要数据结构。

先想想怎么骗一部分分。显然当 $k = 0$ 的时候答案是很简单的输出出现最多的数的个数。

以此为基础我们想象怎么扩展到这个问题。

对于第 $i$ 个数计算他对哪个数能有贡献。不难发现我们把 $i$ 包含到区间内的时候，他对自己的贡献一定是变小了 $1$，如果这个时候贡献为负数了，那说明还不如不选前面那一段区间。于是把 $i$ 作为新的区间的开头进行贡献。

讲得很抽象但是做起来相当简单。

另外，如果你尝试使用桶，请注意负数的问题。我的处理方法是使用一个偏移量整体转正数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int delta = 2000003;
int contri[delta << 1], cnt[delta << 1], raw[delta << 1], res;

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int n, k; cin >> n >> k;
	for(int i = 1; i <= n; cin >> raw[i], ++ cnt[raw[i] + delta], res = max(res, cnt[raw[i] + delta]), ++ i);
	if(k) {
		int tmp;
		for(int i = 1; i <= n; ++ i) {
			tmp = raw[i];
			if(-- contri[tmp + delta] < 0) contri[tmp + delta] = 0;
			res = max(res, (++ contri[tmp + delta + k]) + cnt[tmp + delta + k]);
		}
	}
	cout << res;
}
```

---

## 作者：wuyin331 (赞：0)

# 题解

我们可以有一次操作来让一段连续的区间的元素加上 $k$，假设最后求的最多元素为 $x$，那么我们只需要找到一段连续的区间 $[l,r]$，在这一段区间里面会有 $i$ 个 $x-k$，与 $j$ 个 $x$。那么答案为 $h[x] - j + i$。由于 $h[x]$ 是一个常量，也就是说我们需要求得 $ \max (i - j)$。

我们可以建立一个哈希表，来表示 $[1,n]$ 之间每一个不同的元素个数。再用一个  ```unordered_map``` 来在线维护一段区间的 $i - j$，做法类似双指针，即可通过该题。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<numeric>
#define int long long
using namespace std;
int t, n, m, k, q, nums[1000005],h[4000005];
const int M = 2000000;
unordered_map<int,int>mp;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	memset(h,0,sizeof(h));
	int ans=0;
	for(int i=1;i<=n;i++) cin>>nums[i];
	for(int i=1;i<=n;i++) h[M+nums[i]]++,ans=max(h[M+nums[i]],ans);
	int cnt=0;
	if(k==0){
		cout<<ans<<'\n';
		return 0;
	}
	for(int j=1;j<=n;j++){
		if(mp[nums[j]-k]>0) mp[nums[j]-k]--;
		mp[nums[j]]++;
		ans=max(ans,mp[nums[j]]+h[M+nums[j]+k]);
	} 
	cout<<ans<<'\n';
	return 0;
} 
```


---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9842)
# 题意
给定 $n$ 和 $k$，和一个长度为 $n$ 的序列，可以对任意的 $1 \le l,r \le n$，给区间 $[ l,r ]$ 加上 $k$，求最优情况下众数的数量。
# 思路
首先看到 $1 \le n \le 10^6$，所以不考虑枚举。

对于第 $i$ 个数，看它能对那个数有贡献。由此发现，如果将 $i$ 包含到修改区间，他对自己的贡献一定是变小 $1$。如果此时贡献为负数，说明不选前面一段更好，将 $i$ 作为新的区间开头。

思路毕。

代码就不贴了，求关~

---

