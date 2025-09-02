# Another MEX Problem

## 题目描述

You are given an array of integers $ a $ of size $ n $ . You can choose a set of non-overlapping subarrays of the given array (note that some elements may be not included in any subarray, this is allowed). For each selected subarray, calculate the MEX of its elements, and then calculate the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all the obtained MEX values. What is the maximum bitwise XOR that can be obtained?

The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, the maximum XOR is $ 2 $ if we take the entire array, $ \operatorname{MEX}([1, 0]) = 2 $ .

In the second test case, the maximum XOR is $ 6 $ if we partition the array into segments $ [1, 2, 0] $ and $ [7, 1, 2, 0, 2, 4, 3] $ :

- $ \operatorname{MEX}([1, 2, 0]) = 3 $ ,
- $ \operatorname{MEX}([7, 1, 2, 0, 2, 4, 3]) = 5 $ ,

 therefore, the XOR is $ 5 \oplus 3=6 $ .In the third test case, the maximum XOR is $ 7 $ if we partition the array into segments $ [1, 0] $ and $ [7, 1, 2, 0, 2, 4, 3] $ :

- $ \operatorname{MEX}([1, 0]) = 2 $ ,
- $ \operatorname{MEX}([7, 1, 2, 0, 2, 4, 3]) = 5 $ ,

 therefore, the XOR is $ 5 \oplus 2 = 7 $ .

## 样例 #1

### 输入

```
4
2
1 0
10
1 2 0 7 1 2 0 2 4 3
10
2 1 0 7 1 2 0 2 4 3
3
1 2 1```

### 输出

```
2
6
7
0```

# 题解

## 作者：Augury (赞：32)

# CF1870E Another MEX Problem 题解

萌新啃了一晚上的官方题解，求管理大大给过/kel

[CnBlogs链接](https://www.cnblogs.com/Augury/p/17718430.html)

## 题意

给你一个序列 $a$，让你选出一些不交的子串，使得它们的 $MEX$ 的异或和最大。

$n\le 5000,a_i\le n$。

## 思路

考虑 dp。

首先这个东西是异或，不好做最优化 dp。于是我们考虑可行性 dp。

设 $dp_{i,j}$ 表示上一个选的区间的右端点位置 $\le i$ 时，答案是否可以是 $j$。

考虑这个东西怎么转移。我们枚举 $i$，然后枚举 $1\le j\le i$，枚举 $0\le k\le 2n$，从 $dp_{j-1,k\oplus MEX(j,i)}$ 转移到 $dp_{i,k}$。

显然，这样的复杂度是 $O(n^3)$ 的，不可通过。于是我们考虑优化。

我们定义一个东西，叫做好的区间。对于一个区间 $[l,r]$，不存在一个区间 $[l_1,r_1]$，使得 $l\le l_1 \le r_1 \le r$，且 $l\neq l_1$ 或 $r\neq r_1$，且 $MEX(l_1,r_1)=MEX(l,r)$，那么区间 $[l,r]$ 是一个好区间。

有一个结论，就是好区间只有 $O(n)$ 个。

假设我们现在有一个好区间 $[l,r]$，他的 $MEX\neq 0$。我们假设 $a_l>a_r$，因为 $a_l<a_r$ 可以类似地讨论。显然，$a_l\neq a_r$，除非 $a_l=0$。

显然有 $MEX(l,r)>a_l$，因为 $MEX(l,r)$ 肯定不能等于 $a_l$，而且如果 $MEX(l,r)<a_l$，就可以把 $a_l$ 踢出去，那么 $[l,r]$ 就不是一个好区间。

我们假设有一个 $r_1>r$，使得 $[l,r_1]$ 是一个好区间，且 $a_l>a_{r_1}$。

这样可能吗？不可能。因为 $a_l<MEX(l,r),a_{r_1}<a_l$，所以 $a_{r_1}<MEX(l,r)$。这就说明，$a_{r_1}$ 已经在 $[l,r]$ 中出现了，不会产生任何贡献，所以 $[l,r_1]$ 不是一个好区间。

所以我们就证明了，对于每个 $l$，至多有一个 $r$，使得 $a_l>a_r$ 且 $[l,r]$ 是一个好区间。

同时，这也说明了，对于每个 $r$，至多有一个 $l$，使得 $a_l<a_r$ 且 $[l,r]$ 是一个好区间。

而且，如果 $a_i=0$，那么 $i$ 一定不会是上面那两种好区间的端点，但 $[i,i]$ 本身就是一个好的区间，它的 $MEX$ 为 $1$。

综上，好的区间最多只有 $2n$ 个。

那么，我们怎么求出所有好的区间呢？

根据上面的定义，我们对于每个 $l$，找到最小的 $r$，使得 $a_l>a_r$ 且 $MEX(l,r)>a_l$ 即可。反方向也是一样。需要特殊处理一下 $0$。

这样，我们就不用枚举所有区间了，只要枚举好的区间就行了，复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define Pi pair<int,int>
using namespace std;
inline int read(){
	int ans=0;bool op=0;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=1;ch=getchar();}
	while('0'<=ch&&ch<='9'){ans=(ans<<1)+(ans<<3)+(ch^48);ch=getchar();}
	if(op)return -ans;
	return ans;
}
const int maxn=5010;
int n;
int a[maxn];
int buc[maxn],mex;
vector<Pi>g[maxn];
bool dp[maxn][maxn<<1];
void solve(){
	//read
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	//clear
	for(int i=1;i<=n;i++)g[i].clear();
	//init
	for(int i=1;i<=n;i++)if(!a[i])g[i].push_back(make_pair(i,1));//特殊处理0
	for(int i=1;i<=n;i++){//i是左端点
		memset(buc,0,sizeof(int)*(n+5)),mex=0;
		for(int j=i;j<=n;j++){
			buc[a[j]]=1;
			while(buc[mex])++mex;
			if(mex>a[i]&&a[j]<a[i]){
				g[j].push_back(make_pair(i,mex));
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		memset(buc,0,sizeof(int)*(n+5)),mex=0;
		for(int j=i;j>=1;j--){//i是右端点
			buc[a[j]]=1;
			while(buc[mex])++mex;
			if(mex>a[i]&&a[j]<a[i]){
				g[i].push_back(make_pair(j,mex));
				break;
			}
		}
	}
	//solve
	memset(dp[0],0,sizeof(bool)*((n<<1)+5));
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		memcpy(dp[i],dp[i-1],sizeof(bool)*((n<<1)+5));
		for(Pi j:g[i]){
			for(int k=0;k<=(n<<1);k++){
				if((k^j.second)<=(n<<1))dp[i][k]|=dp[j.first-1][k^j.second];
			}
		}
	}
	for(int i=(n<<1);i>=0;i--){
		if(dp[n][i]){
			cout<<i<<'\n';
			return;
		}
	}
}
signed main(){//多组数据
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：vegetable_king (赞：21)

不用性质的，好写的。

看到 $\textrm{MEX}$ 和 $\textrm{XOR}$ 这两种很难维护的东西出现在一起，又结合 $n \le 5 \times 10^3$ 的数据范围，考虑 DP。

暴力 DP，设状态 $f_{i, j}$ 表示前 $i$ 个数凑出异或和为 $j$ 是否可行，转移暴力转移即可做到 $O(n^3)$。

考虑优化，发现 $f$ 数组对于一个固定的 $j$，满足 $f_{i, j} = 1$ 的 $i$ 是一个后缀。则设 $g_i$ 表示能造出异或和为 $i$ 的最小前缀，转移考虑暴力枚举新区间 $(j, k)$（$g_i < j \le k \le n$）并更新到新的异或和，但是这也是 $O(n^3)$ 的。

接下来可以发现，有多个异或和相同的区间的时候，取右端点最小的即可，所以我们只需要 $O(n^2)$ 预处理出每个区间的 $\textrm{MEX}$，并求出 $to_{l, x}$ 表示 $l$ 后面异或和等于 $x$ 的区间的最小右端点（不存在即为 $n + 1$），求一个后缀 $\min$ 即可。

现在转移 $g_i$ 的时候就只需要枚举新的区间的异或和 $x$，并更新 $g_{i \oplus x} \gets to_{g_i, x}$。关于转移顺序的问题，类似最短路转移一下即可。

[代码](https://codeforces.com/contest/1870/submission/223894319)

---

## 作者：樱雪喵 (赞：10)

结论没证出来，输。

## Description

给一个长度为 $n$ 的非负整数序列 $a$，你要选取该序列若干不重叠的子段，并对每个子段分别求 $\text{mex}$。令 $x$ 为每个子段 $\text{mex}$ 的异或和，求所有方案中 $x$ 的最大值。

$n\le 5000,0\le a_i\le 5000$。

## Solution 1

KH 讲的神仙做法 /bx

令 $\text{mex}(l,r)$ 表示区间 $[l,r]$ 的 $\text{mex}$ 值。设 $g_{i,j}$ 表示在点 $i$ 右侧最小的 $r$ 使得存在一个以 $r$ 结尾的区间 $\text{mex}(l,r)=j$，其中 $l\ge i$。设 $f_i$ 表示存在若干子段异或和为 $i$ 的情况下，最后一个子段的 $r$ 的最小值。

那么由于值域只有 $5000$，显然 $x\oplus y\le x+y$，答案的值域也不超过 $5000$。$g$ 数组容易在 $O(n^2)$ 的时间复杂度内预处理。考虑 $f$ 数组，我们按 $f_i$ 的值从小到大的顺序对其进行转移。因为 $f_i$ 最小的那个肯定不会再被别人更新，所以可以 $O(n)$ 地用它和 $g_{f_i,j}$ 的值更新后面的 $f$。

更新操作一共执行了 $n$ 次，总复杂度 $O(n^2)$。

## Solution 2

赛时做法。但是关键结论没证出来所以没过。 

观察到值域很小，肯定要在值域上搞点东西。所以设 $f_{i,j}$ 表示前 $i$ 个数选出若干子段后能否得到 $j$。这样显然有：
$$
f_{i,j}|=f_{k-1,j\oplus \text{mex}(k,i)}
$$


朴素转移是 $O(n^3)$ 的，发现异或没有什么能够利用的性质，优化要从 $\text{mex}$ 的性质上入手。

考虑如下情况：若 $\text{mex}(l,r)=\text{mex}(l+1,r)$，那么 $[l,r]$ 这个区间可以完全被 $[l+1,r]$ 这个区间代替，因为它们对答案的贡献相同，且后者对“不重合”的限制更松。也就是说，我们可以只保留满足 $\text{mex}(l,r)\neq \text{mex}(l+1,r)$ 且 $\text{mex}(l,r)\neq \text{mex}(l,r-1)$ 的区间 $[l,r]$，并用它们来转移。这样的区间个数上界是 $2n$，对此将在下文给出证明。

对于一个有效区间 $[l,r]$，显然有 $a_l\neq a_r$，因为如果相等的话随便哪边删一个都不影响 $\text{mex}$。不妨设 $a_l>a_r$，并考虑在 $l$ 固定时满足条件的 $r$ 的数量。

因为 $\text{mex}(l,r)\neq \text{mex}(l+1,r)$，那么意味着 $a_l$ 的加入改变了区间的 $\text{mex}$ 值。也就是说，$\text{mex}(l+1,r)$ 一定等于 $a_l-1$。

同理，因为 $a_r$ 的加入也改变了 $\text{mex}$，可以得出 $\text{mex}(l+1,r-1)=a_r-1$。考虑在固定起点 $l+1$ 的情况下，随着 $r$ 的增加，区间的 $\text{mex}$ 值单调不降。因此满足 $\text{mex}(l+1,r-1)=a_r-1,\text{mex}(l+1,r)=a_r$ 的 $r$ 至多有一个。因此对于每个区间左端点，当 $a_l>a_r$ 时至多有一个有效区间。

$a_l<a_r$ 同理，至此我们证明了有效区间的数量上界为 $2n$。

那么上文说过，转移时只对有效区间进行转移即可，时间复杂度降为 $O(n^2)$。

代码依旧是 Solution 2。

```cpp
const int N=5005;
int f[N][N],mex[N][N];
int n,a[N],flag[N];
vector<int> l[N];
int main()
{
    int T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;i++) l[i].clear();
        for(int i=0;i<=n;i++) for(int j=0;j<=5000;j++) f[i][j]=0;
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++)
        {
            int mx=0;
            for(int j=0;j<=5000;j++) flag[j]=0;
            for(int j=i;j<=n;j++)
            {
                flag[a[j]]=1;
                while(flag[mx]) mx++;
                mex[i][j]=mx;
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                if(mex[i][j]!=mex[i+1][j]&&mex[i][j]!=mex[i][j-1]) l[j].push_back(i);
        f[0][0]=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=5000;j++)
            {
                f[i][j]|=f[i-1][j];
                for(auto k:l[i])
                    if((j^mex[k][i])<=5000) f[i][j]|=f[k-1][j^mex[k][i]];
            }
        }
        int ans=0;
        for(int j=0;j<=5001;j++) if(f[n][j]) ans=j;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Leasier (赞：4)

显然可以 $O(n^3)$ 暴力 dp，但也显然不能通过。

异或和跟 $\operatorname{mex}$ 的结合看上去没有任何优秀的性质，考虑**哪些区间可能是较优的**。

注意到若 $[l, r] \subset [l', r']$ 但 $\operatorname{mex}[l, r] = \operatorname{mex}[l', r']$，**我们完全可以舍弃后者，因为前者更容易满足不交的性质**。

考虑把所有 $\operatorname{mex}[l, r] \neq \operatorname{mex}[l, r - 1], \operatorname{mex}[l, r] \neq \operatorname{mex}[l + 1, r]$ 的 $[l, r]$ 抓出来，此时 $a_l, a_r > \max[l + 1, r - 1]$。

考虑每个 $i$ 作为左右端点中较大的一端，可以发现只可能存在 $2$ 个没法变短的区间，于是此时 $[l, r]$ 只有 $O(n)$ 个。

于是把这些区间抓出来转移即可。时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 5e3 + 7, M = 8191;
int a[N], mex[N][N];
bool vis[N], dp[N][M + 7];
vector<int> v[N];

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, ans;
		cin >> n;
		for (int j = 1; j <= n; j++){
			cin >> a[j]; 
		}
		for (int j = 1; j <= n; j++){
			int cur_mex = 0;
			for (int k = 0; k <= n; k++){
				vis[k] = false;
			}
			for (int k = j; k <= n; k++){
				vis[a[k]] = true;
				while (vis[cur_mex]) cur_mex++;
				mex[j][k] = cur_mex;
			}
		}
		for (int j = 0; j < n; j++){
			v[j].clear();
		}
		for (int j = 1; j <= n; j++){
			for (int k = j; k <= n; k++){
				if (k == j || (mex[j][k - 1] != mex[j][k] && mex[j + 1][k] != mex[j][k])) v[j - 1].push_back(k);
			}
		}
		for (int j = 0; j <= n; j++){
			for (int k = 0; k <= M; k++){
				dp[j][k] = false;
			}
		}
		dp[0][0] = true;
		for (int j = 0; j < n; j++){
			int size = v[j].size();
			for (int k = 0; k <= M; k++){
				if (dp[j][k]){
					dp[j + 1][k] = true;
					for (int l = 0; l < size; l++){
						int r = v[j][l];
						dp[r][k ^ mex[j + 1][r]] = true;
					}
				}
			}
		}
		for (int j = M; j >= 0; j--){
			if (dp[n][j]){
				ans = j;
				break;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：4)

蛮简单的，后悔卡 D 不看 E 了。

------------

考虑暴力 dp 加一个小优化。

先预处理区间 mex。

$f_{i,j}$ 表示前 $i$ 个数，能否凑出 $j$。

考虑优化掉一些没必要用来转移的区间，如果删去左端点或右端点，mex 不变，则一定不会优于更小的区间。

简单的反证法可以证明，每个点作为区间两端的中较大的一个（避免重复计算），最多只有 $2$ 个没法更小的区间（向左、向右各一个），共 $2\times n$ 个。

所以复杂度为 $\operatorname{O}(n^2)$。

------------

代码比较简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+84,maxm=1e4+84,m=1e4+23;
int T,n,res,a[maxn],mex[maxn][maxn],cnt[maxn];
bitset<maxm> f[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=1;l<=n;l++){
            for(int i=0;i<=n+23;i++)
                cnt[i]=0;
            res=0;
            for(int r=l;r<=n;r++){
                cnt[a[r]]++;
                while(cnt[res])
                    res++;
                mex[l][r]=res;
            }
        }
        f[0].reset();
        f[0][0]=1;
        for(int r=1;r<=n;r++){
            f[r]=f[r-1];
            for(int l=1;l<=r;l++)
                if(l==r||mex[l][r]!=mex[l+1][r]&&mex[l][r]!=mex[l][r-1]){
                    for(int s=0;s<=m;s++)
                        f[r][s^mex[l][r]]=f[r][s^mex[l][r]]|f[l-1][s];
                }
        }
        for(int i=m;i>=0;i--)
            if(f[n][i]){
                printf("%d\n",i);
                break;
            }
    }
    return 0;
}
```


---

## 作者：zhongpeilin (赞：3)

# 题目大意：
一个长度为 $N$ 的序列，请你求出将他的任意不相交的子串的 MEX 异或值最大多少？

# 解题思路：
不难发现，这道题他贪心不了，尝试 dp。  
那他这个有后效性吗？其实只需要想到假设他是从左往右选的即可。  
那么设 $dp_{i}$ 为前 $i$ 个位置异或最大值是多少？  
但是我们发现，异或是可能两个大的变成一个小的，所以最优的不一定是局部最大的，不可行，那么我们再加一维：$dp_{i,j}$ 表示前 $i$ 个位置是否可以为 $j$？  
问题又来了，时间爆炸，因为状态已经是 $O(n^2)$ 了，而转移要一个 $O(n)$，时间复杂度 $O(n^3)$。即使 dp 用一个 bitset 来优化，也应该会超时的，继续考虑优化。  
**感觉转移不好优化，再次改状态**。  
因为这道题基本上是 $O(n^2)$ 或者 $O(n^2 \log n)$ 的，而转移基本上需要一个 $O(n)$，状态只能是 $O(n)$ 的。而我们换一个角度，设 $dp_{i}$ 表示异或值要为 $i$，那么下一次可以取的最小的数的下标是多少？  
这不还是 $O(n^2)$ 吗？不是的，但是这里可以不枚举下标了，因为我们可以建图，而对于每个 dp，枚举下一段子串的左右短点，预处理出 MEX 就可以。时间复杂度：$O(n^3 \log n)$，更劣了，悲。  
但是我们发现 MEX 是可以被 $O(n^2)$ 预处理，$O(1)$ 查询。而求枚举下一段也可以通过预处理使得预处理 $O(n^2)$，而使用时 $O(n)$，加上 dijkstra 的 $O(n \log n)$，总共 $O(n^2 \log n)$ 的时间复杂度。  

求 MEX：因为我们发现，MEX 在左端点固定，右端点向右，值变大，所以暴力做，均摊 $O(N^2)$。  

求 $pre_{i,j}$ 表示 $i$ 以后，要一个 MEX 为 $j$ 的段，最小的子串右端点最少是多少？由于对于每个 MEX，可以打个标记，然后 $pre_{i,j}=\min(pre_{i, j}, pre_{i+1, j})$ 就可以，$O(N^2)$。  
希望这篇博客能帮到您！

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){ //快读
	int x = 0; char op = getchar();
	while(op < '0' || op > '9') op = getchar();
	while(op >= '0' && op <= '9'){
		x = x * 10 + (op - '0');
		op = getchar(); 
	}
	
	return x;
}
int n, a[5005], MEX[5005][5005], pre[5005][8005], cnt[5005], dis[10000];

void dijkstra(){
	for(int i = 1; i <= 8000; i++) dis[i] = n + 2;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	q.push({0, 0});
	
	while(!q.empty()){
		int x = q.top().second;
		q.pop();
		for(int i = 0; i <= n; i++){ //枚举下一个子串的MEX
			if(dis[(x ^ i)] > pre[dis[x]][i] + 1){
				dis[(x ^ i)] = pre[dis[x]][i] + 1; //这里要加1，因为子串要互不相交
				q.push({dis[x ^ i], (x ^ i)});
			}
		} 
	}
}
void solve(){
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 0; i <= n + 2; i++){
		for(int j = 0; j <= n + 2; j++){
			pre[i][j] = n + 1;
		} 
	} 
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; j++) cnt[j] = 0;
		for(int j = i; j <= n; j++){
			cnt[a[j]]++;
			MEX[i][j] = MEX[i][j - 1];
			while(cnt[MEX[i][j]]) MEX[i][j]++;//暴力MEX
		} 
	}
	
	for(int i = 0; i <= n; i++){ //打标记
		for(int j = i; j <= n; j++){
			pre[i][MEX[i][j]] = min(pre[i][MEX[i][j]], j);
		} 
	} 
	for(int i = n - 1; i >= 0; i--){ //左移标记
		for(int j = 0; j <= n; j++){
			pre[i][j] = min(pre[i][j], pre[i + 1][j]);
		}
	}
	dijkstra();//跑图
	for(int i = 8000; i >= 0; i--){
		if(dis[i] <= n + 1){ //枚举答案，这里因为下一个可以是n+1，就表示n选了
			cout << i << endl;
			return ;
		}
	}
}
int main() {
	int t = read();
	while(t--) solve();
	return 0;
}
//喜欢的话，记得点个赞哦！


---

## 作者：_maze (赞：2)

观察到题解区好像没有我的做法，于是决定水一篇。

-------

首先考虑暴力转移：设 $f_{i,j}$ 表示当前强制选 $i$ 且当前异或和为 $j$ 时的可行性。转移枚举以 $i$ 为右端点的区间起点及之前的疑惑和。时间复杂度 $O(n^2A)$。其中 $A$ 为最大权值，不可通过。

考虑减少枚举状态来优化转移。发现一个区间仅在两种情况中会成为最优解：

1. 在枚举 $[1,i-1]$ 的时候没有出现该区间的 $\operatorname{mex}$，这说明该区间的 $\operatorname{mex}$ 是枚举过的值中最大的。

2. 在枚举 $[1,i-1]$ 的时候出现过该区间的 $\operatorname{mex}$，但左端点在当前区间左端点左边，即当前区间更小。

对于第一种情况，时间复杂度均摊易得为 $O(n)$ 级别。因为随着枚举，$\operatorname{mex}$ 的最大值不会减少。

对于第二种情况，可以发现在这种情况下 $i$ 会取代上一个区间的最左端 $l$，使得区间可以在舍弃 $l$ 的情况下（范围减小）依然保证 $\operatorname{mex}$ 为当前值。因为每个下标只对应一个权值，所以这部分复杂度也是 $O(n)$ 的。

于是分开枚举两种转移即可。总复杂度降为 $O(nA)$，可以通过。

---

## 作者：541forever (赞：2)

感觉是个挺好的通过去除不必要的转移来优化 dp 的题啊。

考虑暴力 dp 是如何做的，我们设 $dp_{i,j}$ 表示从 $1$ 到 $i$ 的这个前缀，是否能凑出异或和为 $j$ 的数，转移时枚举选的区间的右端点异或上这个区间的 $Mex$ 向后转移或直接不选。

$$dp_{r,j \bigoplus Mex_{k=i}^{r}a_k}|=dp_{i,j}$$

但是我们每次都需枚举 $O(n)$ 个区间，预处理每个区间的 $Mex$ 值后时间复杂度是 $O(n^3)$ 的，不太可以接受。但我们可以发现很多区间的状态都是不必要的，若区间 $[l,r]$ 的 $Mex$ 等于区间 $[l+1,r]$ 或区间 $[l,r-1]$，这个区间就可以被平替掉。接下来，我们证明这种不能被平替掉的区间实际上只有 $O(n)$ 个。我们知道，当 $a_l$ 是 $a_l,a_r$ 中较大的那一个时，能对区间 $[l,r]$ 产生贡献的 $r$ 只有一个，因为若 $l$ 对区间 $[l,r]$ 右贡献，则 $Mex_{i=l}^r a_i> a_l$，又因为 $a_l > a_r$，因此再后面的值小于 $a_l$ 的 $r$ 一定时没有贡献的。同理，当 $a_r$ 为较大的那一个时，也只有一个 $l$ 是有用的。因此，总的有用的区间个数是 $O(n)$ 级别的。在代码实现时，我们可以开 $n$ 个 `vector` 把每个有用的区间 $[l,r]$ 挂在 $l-1$ 的位置，在转移时直接向 $r$ 转移即可。

[Code](https://codeforces.com/contest/1870/submission/224260938)

---

## 作者：_YyD_ (赞：1)

考虑建图，以异或和作为节点，区间 MEX 作为边。

发现每个节点记录一个最短的前缀使得能凑出它，那么同样的节点用这个前缀去异或上边是更优的（简单贪心）。

对这张图做 BFS，初始节点为 $0$，设现在的节点为 $h$，枚举一个 $x$。

如果 $h\oplus x$ 这个节点之前遍历到了，那就不会再去了（BFS 的特性）。

如果没遍历到，就是找出右端点最小能转移过去的边。

这个也很简单，在这之前对于每个 $i,j$ 处理出区间左端点大于 $i$，区间 MEX 等于 $j$ 的最小区间右端点即可。

最终只要找遍历到过的最大的节点即可，复杂度 $O\left(n^2\right)$。

CODE：

```cpp
#include<bits/stdc++.h>

//#define int long long
#define inf 1e7

#define pb(x) emplace_back(x)
#define lowbit(x) x&(-x)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mkp make_pair
#define endl '\n'
#define clrn(x) memset(x,0,sizeof(x))
#define clrx(x) memset(x,0x3f,sizeof(x))
#define eps 1e-18
#define y1 hamuhamu
#define pii pair<int,int>

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define lep(i,l,r) for(int i=(l);i>=(r);--i)

#define fan putchar('\n')
#define fak putchar(' ')

// #pragma GCC optimize(2,3,"Ofast","inline")

using namespace std;

inline int read() {	
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
inline void write(int X) {
	if(X<0) {X=~(X-1); putchar('-');}
	if(X>9) write(X/10);
	putchar(X%10+'0');
}

#define N 5010
#define M 25000010
#define mod 998244353

int n,a[N],b[N*2];
int nx[N][N];
int vis[N*2];
bool t[N][N*2];

void solve(){
	n=read();
	rep(i,1,n)a[i]=read();
	rep(i,1,n+1)rep(j,0,n+1)nx[i][j]=inf;
	rep(i,1,n){
		int mex=0;
		rep(j,0,n)b[j]=0;
		rep(j,i,n){
			b[a[j]]=1;
			while(b[mex])mex++;
			nx[i][mex]=min(nx[i][mex],j);
		}
	}
	lep(i,n,1)rep(j,0,n+1)nx[i][j]=min(nx[i][j],nx[i+1][j]);
	rep(i,0,n*2)vis[i]=0;
	rep(i,0,n*2)b[i]=inf;b[0]=0;
	rep(i,0,n)rep(j,0,n*2)t[i][j]=0;
	t[0][0]=1;
	rep(s,0,n)rep(h,0,n*2)if(t[s][h]&&!vis[h]){
		vis[h]=1;
		rep(i,0,n+1){
			int x=h^i;
			if(vis[x])continue;
			if(nx[b[h]+1][i]>6000)continue;
			b[x]=min(b[x],nx[b[h]+1][i]);
			t[nx[b[h]+1][i]][x]=1;
		}
	}
	int ans=0;
	rep(i,0,n*2)ans=max(ans,(vis[i]||t[n][i])*i);
	write(ans);
}

signed main(){
	int T=read();
	while(T--)solve(),fan;
	return 0;
}
```


---

