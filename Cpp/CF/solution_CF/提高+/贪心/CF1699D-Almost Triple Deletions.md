# Almost Triple Deletions

## 题目描述

You are given an integer $ n $ and an array $ a_1,a_2,\ldots,a_n $ .

In one operation, you can choose an index $ i $ ( $ 1 \le i \lt n $ ) for which $ a_i \neq a_{i+1} $ and delete both $ a_i $ and $ a_{i+1} $ from the array. After deleting $ a_i $ and $ a_{i+1} $ , the remaining parts of the array are concatenated.

For example, if $ a=[1,4,3,3,6,2] $ , then after performing an operation with $ i=2 $ , the resulting array will be $ [1,3,6,2] $ .

What is the maximum possible length of an array of equal elements obtainable from $ a $ by performing several (perhaps none) of the aforementioned operations?

## 说明/提示

For the first testcase, an optimal sequence of operations would be: $ [1,2,3,2,1,3,3] \rightarrow [3,2,1,3,3] \rightarrow [3,3,3] $ .

For the second testcase, all elements in the array are already equal.

For the third testcase, the only possible sequence of operations is: $ [1,1,1,2,2,2] \rightarrow [1,1,2,2] \rightarrow [1,2] \rightarrow [] $ . Note that, according to the statement, the elements deleted at each step must be different.

For the fourth testcase, the optimal sequence of operations is: $ [1,1,2,2,3,3,1,1] \rightarrow [1,1,2,3,1,1] \rightarrow [1,1,1,1] $ .

For the fifth testcase, one possible reachable array of two equal elements is $ [4,4] $ .

## 样例 #1

### 输入

```
5
7
1 2 3 2 1 3 3
1
1
6
1 1 1 2 2 2
8
1 1 2 2 3 3 1 1
12
1 5 2 3 3 3 4 4 4 4 3 3```

### 输出

```
3
1
0
4
2```

# 题解

## 作者：I_am_Accepted (赞：9)

结论题。

* * *

**结论：** 序列可以被删完当且仅当长度为偶数且众数出现次数不多于序列一半。

**证明：**（严谨的证明 CF 上有，这里就不放了。）

首先众数出现次数多于一半显然不行。

设众数为 $x$，值 $y$ 没出现在序列中过。 

反证法。假设 $x$ 出现次数不多于一半删完，**我们将除了 $x$ 外的数中选一些全部赋为 $y$，使得 $x,y$ 出现次数相同。**

照这样说，那 $x,y$ 岂不是都删不完吗？但是 $x,y$ 之间可以删啊！

矛盾，原命题成立。

* * *

于是就有了 DP 的想法：$f(i)$ 表示将区间 $[1,i]$ 删到只剩 $a_i$ 这种值，最后长度的最大值。

设 $a_0,a_{n+1}$ 为通配符，则答案为 $f(n+1)-1$。

考虑转移
$$
f(i)=1+\max_{j=0}^{i-1}[\text{Del}(j+1,i)\ \land\ a_i=a_j]f(j)
$$
其中 $\text{Del}(l,r)$ 表示 $[l,r]$ 区间是否可以被删完。

至此 $O(n^2)$ 解决。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug cerr<<"Line#"<<__LINE__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int long long
#define N 5003
int cnt[N],a[N],f[N],n;
inline bool equ(int x,int y){return x==0 || y==n+1 || a[x]==a[y];}
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	fill(f,f+2+n,0);
	int mx;
	For(i,0,n){
		if(i && !f[i]) continue;
		fill(cnt+1,cnt+1+n,0);
		mx=0;
		For(j,i+1,n+1){
			if(((j^i)&1) && mx*2<=j-i && equ(i,j)) ckmx(f[j],f[i]+1);
			ckmx(mx,++cnt[a[j]]);
		}
	}
	cout<<f[n+1]-1<<endl;
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T; 
	while(T--)work();
return 0;}
```

---

## 作者：Sellaris (赞：9)

- 提供了预处理 DP ，随机 DP , 最短路 DP 三种做法。

- **TAG :** DP 


- **Solution1 :** 预处理 DP 

	注意到给定性质：删除的 **相邻两个数不能相同** 。
    
   考虑一个区间什么时候能完全删掉？ 
    
   **当且仅当区间长度为偶数，且区间众数的出现次数小于等于区间长度的一半。** 读者不难自证。
   
   结合数据范围发现可以先枚举区间预处理出区间可否被完全删掉，然后直接套路枚举区间进行 DP 即可。
   
   
```cpp
int n=0;int a[maxn]={0};int dp[maxn][maxn]={0};int tong[maxn]={0};int f[maxn]={0};
inline void solve(){
PRE:
	 int mx=0;int reg=0;
    n=read();
    int ans=0;
    for(int i=1;i<=n;i++) {a[i]=read(); }
    
    for(int i=1;i<=n;i++){
    	
        for(int j=1;j<=n+1;j++) tong[j]=0;mx=0;
        
        for (int j=i;j<=n;j++) {
        	(++tong[a[j]]);
            if(mx< tong[a[j]] ) mx=tong[a[j]];reg=j-i+1;
            if( (reg%2==0) && mx<=reg/2 ) dp[i][j]=1;
            else {
				dp[i][j]=0;//cout<<dp[i][j]<<" ";DP数组是预处理数组
			}
        }
	}
	
DP:
	
    memset(f,0,sizeof(f));f[1]=1;
    
    for(int i=2;i<=n;i++){
    	
        if (dp[1][i-1]) f[i]=1;//f[i]以a[i]结尾的最长答案，真正的 DP 数组
        
        for (int j=i-1;j>=1;j--){
        	if(a[i]!=a[j]) continue;
            else{
				reg=i-j-1;
				if ( (reg==0 || dp[j+1][i-1] ) && f[j] ) f[i]=max(f[i],f[j]+1);
			}
        }
    }
    ans=f[n];
    for (int i=1;i<n;i++ ){
        if(dp[i+1][n]==0){
            continue;
        }else ans=max(ans, f[i]);
    }
   cout<<ans<<endl;
}
```


- **Solution2 :** 区间随机 DP

	发现区间 **绝对众数** 若存在则每次在区间内有 $\frac{1}{2}$ 以上的概率取到 ，于是考虑随机数维护 DP ，省去了预处理操作。 **并且在值域较大时避免了离散化开桶的流程。** 错误率大概在 $ \frac{n^{2}}{2^{k}}$ 左右 （ $k$ 是区间随机次数） ，即每次对区间随机取数。区间操作每次维护前缀、区间、后缀的随机取数即可。
    
```cpp
///*****Sellaris*****///
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e3+10;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
int n,a[maxn];int dp[maxn];int sum[maxn][maxn];
struct node{
    int id,v;
    bool operator <(const node &s)const{
         return (s.v==v)? (id<s.id) : (v<s.v) ; }
}b[maxn];

inline bool ask(int l,int r){
    if(l>r) return 1;
    int reg=((rand())%(r-l+1))+l;reg=a[reg];
    if((sum[r][reg]-sum[l-1][reg])*2>r-l+1) return 0;
    return 1;
}

inline int run(int l,int r){
    #define K 100 //随机次数
    for(int i=l;i<=r;i++){
        int flag=1;
        for(int k=1;k<=K && flag;k++) if(!ask(1,b[i].id-1)) flag=0;
        if( (b[i].id&1) && flag) dp[b[i].id]=1;
        else dp[b[i].id]=0;
    }
    
	for (int j=l;j<=r;j++)
		for(int i=l;i<j;i++){
			if(!dp[b[i].id]) continue;
			int flag=1;
			for(int k=1;k<=K && flag;k++) if(!ask(b[i].id+1,b[j].id-1)) flag=0;
			if(((b[j].id-b[i].id)&1) && flag ) dp[b[j].id]=max(dp[b[j].id],dp[b[i].id]+1);
		}
	int anss=0;
	for (int i=l;i<=r;i++){
		int flag=1;
		for (int k=1;k<=K && flag;k++)
			if(!ask(b[i].id+1,n)) flag=0;
		if(((n-b[i].id+1)&1) && flag) anss=max(anss,dp[b[i].id]);
	}
	return anss;
}

inline void solve(){
    n=read();for(int i=1;i<=n;i++) a[i]=read(),b[i].id=i,b[i].v=a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) sum[i][j]=sum[i-1][j];
        sum[i][a[i]]++;//sum是一个后缀桶（？
    }

    sort(b+1,b+1+n);b[n+1].v=0;
    int ans=0;int p=1;//一个指针
    for(int i=1;i<=n+1;i++)
        if(b[p].v!=b[i].v) ans=max(ans,run(p,i-1)),p=i;
    cout<<ans<<endl;
}
signed main(){
    srand(time(0));
    int t=read();while(t--){solve();}
    return 0;
}
```
- **Solution3 :** 最短路 DP

    
   没码。先最短路处理掉能消掉的，不能消掉的就把区间代价算出来，然后扫过去就行，读者不难自行尝试。
   
	简而言之，利用了图论，排除了一些冗余的 DP 状态使得效率大大提高。

---

## 作者：Miraik (赞：4)


设 $f_i$ 表示留下 $a_i$，处理 $1$ 到 $i$ 可以得到的最优值。

则 $f_{i}= \max \{f_j+1\}$，其中 $a_i=a_j$ 且 $a_{j+1}$ 至 $a_{i-1}$ 可以被全部消除。

然后容易发现对于长度为偶数的区间 $a[l,r]$，其可以被全部消除当且仅当区间众数出现的次数不大于区间长度一半。

答案为 $\max ⁡\{f_i\}$，其中 $a_{i+1}$ 至 $a_n$ 能够被全部消除。

[code](https://codeforces.com/contest/1699/submission/162796997)


---

## 作者：yyyyxh (赞：3)

vp 时严重降智，最后看了官方题解的提示胡了个憨憨做法。

提示：考虑哪一些区间可以直接消除。

没有发现有结论的我想：面对**哪些区间**这样的问题一般是区间 DP，于是设计状态 $f_{l,r}$ 表示 $[l,r]$ 能否被删除，转移首先可以枚举分段点将两段可以删除的区间拼起来，然后如果 $f_{l+1,r-1}$ 与 $a_l\neq a_r$ 同时成立那么 $f_{l,r}$ 也成立。

直接 DP 是 $O(n^3)$ 的，用 bitset 存下对于同一个左端点/右端点哪些右端点/左端点 $f_{l,r}$ 为真，枚举分段点直接与起来即可。

剩下的与其它题解一样，设 $g_{i}$ 表示强制保留 $a_i$，$[1,i]$ 最多剩余多少个 $a_i$，利用 $f_{l,r}$ 转移。

时间复杂度 $O(\frac{n^3}{\omega})$。

```cpp
#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
int read(){\\……
}
int a[5003],n;
bool f[5003][5003];
bitset<2501> L[5003],R[5003];
int g[5003];
int main(){
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;++i) a[i]=read(),L[i].reset(),R[i].reset();
		for(int i=1;i<n;++i)
			if(a[i]^a[i+1]){
				f[i][i+1]=1;
				L[i].set((i+1)>>1);
				R[i+1].set((i-1)>>1);
			}
			else f[i][i+1]=0;
		for(int len=4;len<=n;len+=2)
			for(int l=1,r=len;r<=n;++l,++r){
				if(f[l+1][r-1]&&a[l]!=a[r]) f[l][r]=1;
				else if((L[l]&R[r]).any()) f[l][r]=1;
				else f[l][r]=0;
				if(f[l][r]) L[l].set(r>>1),R[r].set((l-1)>>1);
			}
		int ans=0;
		for(int i=1;i<=n;++i){
			g[i]=-0x3f3f3f3f;
			for(int j=i-1;j>=0;j-=2)
				if((!j||a[j]==a[i])&&(f[j+1][i-1]||j+2>i))
					if(g[j]+1>g[i]) g[i]=g[j]+1;
			if(i==n||f[i+1][n]) if(g[i]>ans) ans=g[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：NKL丶 (赞：1)

## Description

给定一个数列 $S$，现对其进行若干次操作，每次操作将相邻两个不相等的数从数列中删去，其余数字相对次序不变，问在操作过后，若数列里仅剩同一种数字，数列长度最大为多少。（$1 \leq S_i \leq |S| \leq 5 \times 10^3$）

## Solution

首先，对于一个序列 $l$，倘若其能被完全删去，不难发现如下性质：

- $|l|$ 应为偶数。
- 序列内众数的出现次数不应超过 $\frac{|l|}{2}$。

我们发现 $S$ 的长度较小，考虑 $O(N^2)$ 的线性dp。

定义 $f[i]$ 表示最终数列以第 $i$ 位为**结尾**时的数列长度，易知枚举断点时仅能从开头或者与 $S_i$ 相同的位转移，同时需要满足断点与当前点之间可以完全删去。

此时复杂度为 $O(N^2)$，发现若枚举断点时暴力判断是否合法，则会使复杂度乘上一个 $N$，因此我们可以进行预处理，提前处理每段序列是否能被删去即可。

## [code](https://www.luogu.com.cn/paste/o9krlkbb)

---

## 作者：FReQuenter (赞：1)

## 思路

### Part 1：为什么要dp

首先，我们明确一下一个序列能被删光的条件：

- $n$ 是偶数。

- 序列中任意一个数出现次数最多有 $\frac{2}{n}$ 次。

证明：

1. 如果 $n$ 是奇数，每次删偶数个数，得到的最终结果会是奇数，不可能是 $0$。

2. 我们每次删除只能删两个不同的数，若一个数出现频率大于 $\frac{2}{n}$，（我们假设它出现了 $k$ 次）删到最后肯定会剩下 $n-2\times(n-k)=2\times k-n$ 个相同数，大于 $0$，无法删光。

接下来，我们就可以判断每个区间 $l,r$ 能不能被删光。我们可以通过 $n^2$ 的枚举左右端点做到。那么，怎样使这些区间合起来对答案产生贡献呢？我们考虑 dp 。

### Part 2：如何dp

#### （1）状态设计

我们发现需要记录的状态有：看到第 $i$ 位（以 $a_i$ 结尾）的最长长度。

特别地，我们还需要记录从 $a_1$ 到 $a_{i-1}$ 能不能完全删除。我们可以进行预处理，用 $f_i$ 为 $1$ 表示能彻底删除，否则用 $0$ 表示。

#### （2）状态转移

对于每一组 $i,j(1\leq j < i \leq n ,a_i=a_j)$，如果我们可以将 $a_{j+1},a_{j+2}...,a_{i-1}$ 全部删除，那我们可以让 $a_i$ 继承每一个以 $a_j$ 结尾的数组。当然， $f_i>f_j$。综上所述，我们可以写出状态转移方程了 ：

$$f_i={\max}^{i-1}_{j=1}(f_j>0 \operatorname{and} a_i=a_j \operatorname{and} \; [a_{j+1},a_{j+2}...,a_{i-1}]\;\text{can been deleted})\times(f_j+1)$$

最后，我们可以把所有答案继承到 $f_{n+1}$ 去，最后输出 $f_{n+1}-1$ 即可。注意 $a_j$ 不能和 $a_n+1$ 进行比较、继承从而产生不合法状态。

## 代码

```cpp
#include<iostream>
#include<unordered_map>
#define int long long
using namespace std;
int a[5005],f[5005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,mq=0;
        cin>>n;
        unordered_map<int,int> mp;
        for(int i=1;i<=n;i++) cin>>a[i];
        f[0]=f[n+1]=0;//边界条件
        for(int i=1;i<=n+1;i++){
            f[i]=((i&1)&&mq<=(i>>1));
            mq=max(mq,++mp[a[i]]);
            //预处理，从a[1]~a[i-1]能否删光
            //mq是指出现最多的数的频率
        }
        for(int i=1;i<=n;i++){
            mp.clear();mq=0;
            if(f[i]){//如果从a[1]~a[i-1]都能删光
                for(int j=i+1;j<=n+1;j++){
                    if(((j-i)&1)&&(mq<=((j-i)>>1))&&(a[i]==a[j]||j==n+1)) f[j]=max(f[j],f[i]+1);//状态转移
                    mq=max(mq,++mp[a[j]]);
                    //重新计算到当前位的出现最多的数的频率
                }
            }
        }
        cout<<f[n+1]-1<<'\n';
    }
}
```

---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16526002.html)

[题目传送门](https://codeforces.com/problemset/problem/1699/D)
### 题目大意
给定一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每次操作你可以选择相邻的两个不同的数字删去，然后剩下的部分连成一个序列。  
现在求让这个序列所以值相等的前提下，序列的最长长度。  
多组数据，数据组数 $T\le 1000$  
$1\le n\le 5000$，$1\le a_i\le n$，$\sum n\le 10^4$
### 题目解析
考虑 DP，发现很不可做。  
由于 $n\le 5000$，所以区间 DP 貌似不可做，因为如果是区间 DP 肯定需要枚举断点，不可行。  
所以考虑线性 DP，然后枚举转移点 $O(n^2)$ 做。  
由于需要让剩下的数字一样，所以设 $f_i$ 为前面 $i$ 个并且第 $i$ 个一定需要选的答案。  

现在问题到了如何判断是否能够转移，也就是判断一段是否能全部删除光。  
不难发现结论：一段数组可以删光当且仅当这段数组长度为偶数并且众数的出现次数不超过数组长度一半。  
证明是显然的。

有了这个结论，我们可以预处理所有的区间是否能够删除即可。
```cpp
int n,w[maxn][maxn],f[maxn],a[maxn],t[maxn],ans;
void work(){
	n=read(); int i,j,maxx=-1; for(i=1;i<=n;i++) a[i]=read();
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) w[i][j]=i>j;
	for(i=1;i<=n;i++){
		maxx=-1; for(j=1;j<=n;j++) t[j]=0;
		for(j=i;j<=n;j++){
			t[a[j]]++; maxx=mmax(maxx,t[a[j]]);
			if(maxx<=((j-i+1)>>1)&&((j-i)&1)) w[i][j]=1;
		}
	}
	f[1]=1; for(i=2;i<=n;i++) if(w[1][i-1]) f[i]=1; else f[i]=-INF;
	for(i=1;i<=n;i++) for(j=i-1;j>=1;j-=2) if(a[i]==a[j]&&w[j+1][i-1]) f[i]=mmax(f[i],f[j]+1);
	ans=0; for(i=1;i<=n;i++) if(w[i+1][n]||i+1>n) ans=mmax(ans,f[i]); print(ans),pc('\n'); return;
}
```

---

