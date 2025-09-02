# Random Task

## 题目描述

One day, after a difficult lecture a diligent student Sasha saw a graffitied desk in the classroom. She came closer and read: "Find such positive integer $ n $ , that among numbers $ n+1 $ , $ n+2 $ , ..., $ 2·n $ there are exactly $ m $ numbers which binary representation contains exactly $ k $ digits one".

The girl got interested in the task and she asked you to help her solve it. Sasha knows that you are afraid of large numbers, so she guaranteed that there is an answer that doesn't exceed $ 10^{18} $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
5
```

# 题解

## 作者：Rachel_in (赞：10)

### 这是一道二分加数位dp的好题:

有一个结论：$n$+1~ $2n$有$k$个$1$的个数是单调的(n越大个数越大);

### 证明:

对于一个$n$， 序列为:$n+1,n+2,n+3,n+4,....,2n-1,2n$

而对于$n+1$,序列为:$n+2,n+3,n+4,n+5,....,2n+1,2n+2$

其中$n+2,n+3,n+4....2n$都是一样的，所以他们的$1$的个数也是一样的。我们再看剩下的，$2n+2$是$n+1$的两倍，也就是这两者的$1$的个数一样($n+1$右移一位),也就是最后$n+1$的序列中还剩下:$2n+1$ , 不管$2n+1$是不是有k个1，$n+1$满足条件序列的个数起码不小于$n$这个序列。所以这个是单调的。

### 解题
证明了这个结论之后，题目就变得简单了。我们每次二分n,然后判断$sum(2*n)-sum(n)$是否大于m，那怎么得到sum的值呢？数位dp。

详见**代码**：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10|'0');
}
int l,r,m,K,len,a[100],dp[100][100];
int dfs(int mq,int sum,bool Lim){
	if(!mq) return (sum==K?1:0);
	if(!Lim&&dp[mq][sum]!=-1) return dp[mq][sum];
	int k=Lim?a[mq]:1;
	int res=0;
	for(int i=0;i<=k;i++)
		if(sum+(i==1)<=K)
			res+=dfs(mq-1,sum+(i==1),Lim&&(i==k));
	if(!Lim) dp[mq][sum]=res;
	return res;		
}
inline int solve(int x){
	len=0;
	while(x){
		a[++len]=x&1;
		x>>=1;
	}	
	return dfs(len,0,1);
}
inline int work(int x){
	return solve(x*2)-solve(x);
}
signed main(){
	while(~scanf("%lld%lld",&m,&K)){
		memset(dp,-1,sizeof(dp));
		l=0;r=1e18;
		int mid;
		bool flag=true;
		while(l<r-1){
			mid=(l+r)>>1;
			int ty=work(mid);
			if(ty==m){
				write(mid);
				puts("");
				flag=false;
				break;
			}
			if(ty>m) r=mid;
			else l=mid;
		}	
		if(flag) write(r),puts("");
	}
}
```


---

## 作者：BrotherCall (赞：2)

看到很多大佬都给出数位 $dp$ 的做法，本蒟蒻就在这里介绍一下如何用组合数来计算吧。

### 题面：

[CF431D Random Task](https://www.luogu.com.cn/problem/CF431D)

### 题意：

给定两个数 $m$ 和 $k$ ，要求输出一个 $ans$ ，满足在 $[ ans + 1 , 2 ans] $ 这个区间中恰有 $m$ 个数的二进制表示中恰有 $k$ 个 1 （输出的 $ans$ 为任一满足题意的即可）。

### 解法：

这题的第一步也是最重要的一步，在于挖掘题目性质。

**性质一**：

我们用 $cnt_i$ 表示在 $[i + 1 , 2 i]$ 这个区间内二进制表示中恰有 $k$ 个 1 的数的个数 。

那么这个 $cnt_i$ 一定随 $i$ 的增大而 单调不减 。

证明：

$cnt_i$ 中包含的数为 $[i + 1 , 2 i]$ 。
$cnt_{i+1}$ 中包含的数为 $[i+2,2i+2]$ 。

可以看出两个区间中 $[i+2,2i]$ 这一段是重合的 。

前者可表示为 $\{i+1\} \cup [i+2,2i]$ 。
后者可表示为 $\{2i+1 , 2i + 2\} \cup [i + 2 , 2i]$ 。

而 $2i+2 = (i + 1) << 1$ ，它们两者包含 1 的个数相同。所以我们可以知道 $cnt_{i+1}$ 比 $cnt_i$ 对其大小贡献多的部分在于 $2i+1$ ， 其他部分完全相同，所以 $cnt_i$ 单调不减 。

自此，我们可以知道这道题的答案具有可二分性。

**性质二：**

如果我们用 $f_i$ 表示在 $[1,i]$ 这个区间内二进制表示中恰有 $k$ 个 1 的数的个数，那么 $cnt_i$ 即为 $f_{2i} - f_i$ 。

### 重难点：如何算出 $f_i$ :

这里我们就需要一些组合数学的知识了。

首先我们需要把一个数字十进制转二进制。

```cpp
void change(int x){
    if(x == 0) return ;
    change(x >> 1);
    s += ((x & 1) + '0');
}
```

然后对这个二进制数进行 $f_i$ 的计算 。

举个例子：$i_{10} = 183$ ， $k = 3$ 时 ， $i_2 = 10110111$ 。

我们把 $[1,10110111]$ 按位从高到低拆成若干个区间：

$[0,10000000) , [10000000 , 10100000) …… [10110110,10110111) , \{10110111\}$ 。

在第一个区间中，可以理解成 7 个数中选 3 个的组合数个数 。第二个区间中，已经有一个 1 被确定，那么其组合数为 5 个数中选 2 个的组合数个数 ……

以此类推，设 $w$ 为一个区间右端点最低的 1 处于的位置，$h$ 为区间左端点 1 的个数，那么该区间符合条件数的个数为 $C_{w - 1}^{k - h}$ 。然后 $[1,i]$ 的答案其实就是各区间的答案相加。

代码实现极其简单而又清新：

```cpp
for(int i=0;i<siz;i++){
    if(s[i] == '0') continue;
    if(k - numone <= 0) break;
    sum += zhs[siz - i - 1][k - numone];
    numone ++;
}
```

综上：这题只需要先预处理 $C_1^1$ ~ $C_{64}^{64}$ ，然后二分答案判断 $mid$ 的 $f_{2mid} - f_{mid}$ 是否等于 $m$ 就行啦。

### 时间复杂度：

预处理是 $O(64^2)$ 的 ，二分答案 + 计算  $f_i$ 是 $O(\log^2 n)$ 的。

所以总复杂度为 $O(\log^2 n)$ 。

[Code](https://www.luogu.com.cn/paste/9phg7vkw)

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF431D)

看到数据范围肯定会想到二分，再加上 $[n+1,2n]$ 的奇怪限制，可以直感答案是有单调性的。

具体地，记录 $f(n)$ 表示 $[n+1,2n]$ 中二进制表示有 $k$ 个 $1$ 的数的数量，则有 $f(n) \le f(n+1)$。

证明就是比较 $[n+1,2n]$ 和 $[n+2,2n+2]$，中间部分是一样的，只有头尾不同。前面多了 $n+1$，而后面多了 $2n+1$ 和 $2n+2$，$2n+2$ 含有的 $1$ 数量显然与 $n+1$ 相同，于是得证。

然后二分答案即可，check 部分直接求 $[1,n]$ 有 $k$ 个 $1$ 的数量，数位 dp 或者直接利用组合数计数都行。

---

## 作者：dsjkafdsaf (赞：1)

# [My blog](https://www.cnblogs.com/dsjkafdsaf/)

## 题目描述

求一个$n$，使得$n+1$到$2n$这些数的二进制中恰好有$k$个$1$的数有$m$个。

## Input

输入包含两个正整数$m，k$。$(0<=m<=1e18, 1<=k<=64) $

## Output

输出$n$。 

## Sample Input

```
1 1

3 2
```
## Sample Output
```
1
5
```
首先我们要知道这个答案是具有单调性的。

即若满足$m>n$，则区间$[m,2m]$内满足条件的数的数量$>$区间$[n,2n]$内满足条件的数的数量。

***

证明如下：

将区间$[n+1,2n]$分割成两个区间$[n+1,n+1]$和$[n+2,2n]$。

而区间$[n+2,2*(n+1)]$可以分割成$[n+2,2n]$和$[2n+1,2n+2]$。

而$2n+2$二进制中$1$的数量和$n+1$中$1$的数量是相同的。

而多了一个$2n+1$只有可能让数量增加，所以答案满足单调性。

即对于$m>n$，则区间$[m,2m]$内满足条件的数的数量$>$区间$[n,2n]$内满足条件的数的数量。

证毕。

***

于是我们就可以二分求解了。

现在我们就只用判断$[n+1,2n]$中满足条件的数的数量即可。

我们发现对于区间$[n+1,2n]$满足条件的数的数量可以转换为$[1,2n]$-$[1,n]$的数量。

而一个前缀的数量肯定会更好求解。

问题进一步转换为求解$[1,n]$内满足条件数的数量。

这个问题我们可以利用两种方法求解：

### 方法一：计数DP

对于当前$n$,我们从二进制位高的开始考虑，首先我们只有在遇到一个$1$时才能更新答案。

对于当前遇到的$1$，我们发现前面的位上的数是固定的，一共有$tot$个$1$，而我们再后面的$i$个位上可以选择$k-tot$个位置放置$1$,所以答案增加$C(i,n-tot)$，然后$tot++$即可。

## 代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define reg register
#define Raed Read
#define clr(a,b) memset(a,b,sizeof a)
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])
#pragma GCC target("avx,avx2,sse4.2")
#pragma GCC optimize(3)

inline int Read(void) {
	int res=0,f=1;
	char c;
	while(c=getchar(),c<48||c>57)if(c=='-')f=0;
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>=48&&c<=57);
	return f?res:-res;
}

template<class T>inline bool Min(T &a, T const&b) {
	return a>b?a=b,1:0;
}
template<class T>inline bool Max(T &a, T const&b) {
	return a<b?a=b,1:0;
}

const int N=1e5+5,M=2e5+5,mod=1e9+7;

bool MOP1;

int m,k,C[70][70];

int solve(int x) {
	int Ans=0,tot=0;
	drep(i,63,0)if(x&(1ll<<i)) {
		if(tot<=k)Ans+=C[i][k-tot];
		tot++;	
	}
	return Ans;
}

bool MOP2;

inline void _main() {
	m=Read(),k=Read();
	int L=1,R=1e18,Ans=0;
	C[0][0]=1;
	rep(i,1,64) {
		C[i][0]=1;
		rep(j,1,i)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	while(L<=R) {
		int mid=(L+R)>>1;
		if(solve(mid*2)-solve(mid)>=m)Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%lld\n",Ans);
}

signed main() {
	_main();
	return 0;
}
```

### 方法二：数位DP

我们可以直接将$n$转换为二进制数，那么就可以直接$dp$了。

$dp[i][j]$代表考虑到第$i$位，$1$的数量为$j$的数的个数。

## 代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define reg register
#define Raed Read
#define clr(a,b) memset(a,b,sizeof a)
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])
#pragma GCC target("avx,avx2,sse4.2")
#pragma GCC optimize(3)

inline int Read(void) {
	int res=0,f=1;
	char c;
	while(c=getchar(),c<48||c>57)if(c=='-')f=0;
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>=48&&c<=57);
	return f?res:-res;
}

template<class T>inline bool Min(T &a, T const&b) {
	return a>b?a=b,1:0;
}
template<class T>inline bool Max(T &a, T const&b) {
	return a<b?a=b,1:0;
}

const int N=1e5+5,M=2e5+5,mod=1e9+7;

bool MOP1;

int m,k,dp[70][70],A[70];

int dfs(int pos,int tot,int limit) {
	if(!pos)return tot==k;
	if(!limit&&dp[pos][tot]!=-1)return dp[pos][tot];
	int up=limit?A[pos]:1,res=0;
	rep(i,0,up)res+=dfs(pos-1,tot+i,limit&(i==up));
	if(!limit)dp[pos][tot]=res;
	return res;
}

int solve(int x) {
	int len=0;
	while(x)A[++len]=x&1,x>>=1;
	return dfs(len,0,1);
}

bool MOP2;

inline void _main() {
	//	cerr<<"M="<<(&MOP2-&MOP1)/1024.0/1024.0<<endl;
	m=Read(),k=Read();
	int L=1,R=1e18,Ans=0;
	memset(dp,-1,sizeof dp);
	while(L<=R) {
		int mid=(L+R)>>1;
		if(solve(mid*2)-solve(mid)>=m)Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%lld\n",Ans);
}

signed main() {
	_main();
	return 0;
}
```

---

## 作者：R_shuffle (赞：0)

模拟赛做到了这题，所以来发一篇题解。

不难注意到，$k=1$ 的时候可以随便输出一个数，这个证明很简单，因为考虑乘二在二进制中相当于右移一位，所以 $[i+1,2i]$ 中一定有二的幂次。

然后打表发现性质。不难注意到，设 $f_k(n)$ 表示 $[n+1,2n]$ 中二进制表示 $1$ 的个数为 $k$ 的数的个数，有 $f_k(n)$ 单调不降，且差分后绝对值不超过 $1$。然后把每一个变化点的二进制表示写出来，不妨设 $f_k(x)=a,f_k(x+1)=a+1$，那么 $x$ 的二进制表示中 $1$ 的个数是 $k-1$。考虑把所有二进制表示中 $1$ 的个数相同的数放在一起排序，设为序列 $S_k$，那么对于题目中要求的东西 $m,k$，不难发现 $(S_{m,k-1},S_{m+1,k-1}]$ 都是满足条件的。特别的，令 $S_{0,k-1}=0$。

知道了这个，问题就转成了求 $S_{i,j}$，考虑按位确定，然后把问题递归下去，可以做到 $\log^2V$ 的复杂度，整体就是 $O(\log^2V)$ 的。

实际上还可以扩展一下，求所有满足的数的个数。可以用上面的方法简单的解决，就不赘述了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
#define int long long
inline int read()
{
    int re=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
    while( isdigit(ch)) re=(re<<3)+(re<<1)+(ch^48),ch=getchar();
    return re*f;
}
int C(int n,int m)
{
    if(n<0||m<0||n<m) return 0;
    int re=1,pos=1;
    for(int i=n;i>=n-m+1;i--)
    {
        re*=i;
        while(re%pos==0&&pos<=m) re/=pos,pos++;
    }
    return re;
}
int get(int rk,int sum)
{//第rk小的popcount=sum的数
    if(sum==1)
    {
        return (1ll<<(rk-1));
    }
    int tot=0;
    for(int i=sum;;i++)
    {
        int ts=tot+C(i-1,sum-1);
        if(tot<rk&&ts>=rk)
        {
            return (1ll<<(i-1))+get(rk-tot,sum-1);
        }
        tot=ts;
    }
}
void work()
{
    int m=read(),k=read();
    if(k==1)
    {
        cout<<"1\n";
        return ;
    }
    if(m==0)
    {
        cout<<1<<'\n';
        return ;
    }
    int l=get(m,k-1),r=get(m+1,k-1);
 //   cout<<l<<' '<<r<<' ';
    cout<<l+1<<'\n';
}
int cnt[105];
signed main(){
#if __MY_TEST__
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t=1;
    while(t--) work();
    // for(int i=1;i<=1000;i++)
    // {
    //     memset(cnt,0,sizeof cnt);
    //     for(int j=i+1;j<=i+i;j++) cnt[__builtin_popcount(j)]++;
    //     cout<<i<<"->"<<i+i<<'\n';
    //     for(int i=1;i<=10;i++) cout<<i<<":"<<cnt[i]<<'\n';
    // }
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF431D)

### 题目大意
求一个数 $n$，使得 $n+1$ 到 $2n$ 的 $n$ 个数中有 $m$ 个数转成二进制后有 $k$ 个 $1$，输出任意一个 $n$ 均可。

### 解题思路
显然这个东西是单调的，因为对于任意一个数 $n-1$ 来说，如果变成了 $n$，那么范围中的数就少了 $n$ 而多了 $2n-1$ 与 $2n$，而显然 $2n$ 中 $1$ 的数目与 $n$ 中是相同的，这就意味着我们可以进行二分，接下来就要计算 $n+1$ 到 $2n$ 中有多少个数有 $k$ 个 $1$，可以分别计算 $1$ 到 $n$ 与 $1$ 到 $2n$ 后相减。

实际上这个计算过程就是数位 dp，可以进行枚举第一个与 $n$ 二进制不同的位置，从高向低枚举，假设之前的位置都全部相等，那么对于第 $i$ 位，答案就要加上 $C^{k-cnt}_{i}$，其中 $cnt$ 表示的就是之前所出现了的 $1$ 的总数。

其实，该问题等价与在 $1$ 到 $n-1$ 中找 $m$ 个数有 $k-1$ 个 $1$。

证明：

对于 $n=1$，显然成立。

如果对于 $n$，对于任意的 $k$，在 $1$ 到 $n-1$ 二进制中有 $k-1$ 个 $1$ 的数的个数与到 $n+1$ 到 $2n$ 中有 $k$ 个 $1$ 的数的个数相同。

如果 $n$ 变成了 $n+1$，那 $[1,n-1]$ 变成了 $[1,n]$，多了 $n$，$[n+1,2n]$ 变成了 $[n+2,2n+2]$，少了 $n+1$，多了 $2n+1,2n+2$。

所以若对 $n$ 命题成成立，对于 $n+1$ 命题也成立。

由数学归纳法，命题得证。

所以有了这个结论，就可以直接使用倍增进行计算，从高位向低位，每次看该位是否能取 $1$。

---

## 作者：Eason2009 (赞：0)

怎么都在组合数和数位 dp 啊，来个题解区没有的简单做法。

首先，$n$ 越大，答案肯定越大。证明就是考虑每次 $n$ 变为 $n+1$ 时，统计的区间从 $[n+1,2n]$ 变为 $[n+2,2n+2]$。而 $2n+2$ 和 $n+1$ 的二进制表示中 $1$ 的个数是一样的。因此可以二分这个 $n$，然后可以 dp。设 $dp_{n,k}$ 表示 $[1,n]$ 中二进制表示中 $1$ 的个数为 $k$ 的数的个数。那么对于当前 $n$，我们求的其实就是 $dp_{2n,k}-dp_{n,k}$。

然后考虑转移，枚举二进制下最后一位是 $0/1$，可以得到如下转移：

当 $2\mid n$ 时，$dp_{n,k}=dp_{\frac{n}{2},k}+dp_{\frac{n}{2}-1,k-1}+(k==1)$。

当 $2\nmid n$ 时，$dp_{n,k}=dp_{\frac{n}{2},k}+dp_{\frac{n}{2},k-1}+(k==1)$。

边界状态就是 $n=0$ 或 $k=0$ 时，$dp_{n,k}=0$。

用 map 存状态后发现有效状态数是 $k\log n$ 的，因此记忆化一下即可通过。下面浅证一下这个结论。

可以从初始状态 $(n,m)$ 开始画图，发现 $m$ 相同时，不同的 $n$ 最多只有 $2$ 个，因此转移中不同的 $n$ 数量为 $\log n$ 的，每个 $n$ 最多对应着 $k$ 个不同的状态，因此有效状态数是 $k\log n$ 的。再加上 map 本身带的一个 $\log$，复杂度就是 $O(\log^3 n)$ 的。

dp 部分代码：


```cpp
map<pii,int>mp;
int calc(int n,int k)
{
	if(!k) return 0;
	if(!n) return 0;
	if(mp.count({n,k})) return mp[{n,k}];
	if(n%2==0) return mp[{n,k}]=calc(n/2,k)+calc(n/2-1,k-1)+(k==1);
	return mp[{n,k}]=calc(n/2,k)+calc(n/2,k-1)+(k==1);
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
又是一道利用二进制性质进行巧妙解题的题目。  
### Problem  
给定两个超大的整数：$m,k$。求任意一个 $n$，使得 $[n+1,2n]$ 区间内有 $m$ 个数的二进制中有 $k$ 个 1。  
### Problem  
这道题乍一看很奇怪，一个区间内的数的二进制能有啥性质呢？我们再看一眼数据范围，铁是数位 dp 没错了。$l,r$ 并且数据还贼老大，这明显就是数位 dp 嘛。接下来我们要思考：利用数位 dp 能求啥？似乎可以求出一个区间内符合二进制中有 $k$ 个 1 的数的个数。  
很明显这题是让我们搞出 $l,r$。而数位 dp 只是一个判断这个区间合法的工具。

感觉...有点像二分？  
但是一个区间内符合二进制中有 $k$ 个 1 的数的个数是随着 $n$ 单调不减的吗？  
这时候就不得不硬着头皮去分析这个玩意了，根据数学归纳法，如果上述命题成立，那么 $n$ 与 $n+1$ 是递增的，如果 $n$ 与 $n+1$ 是递增的，那么上述命题成立。  
于是我们只需要证出 $n$ 比 $n+1$ 小或等于就可以了。  
很显然它们代表的区间之间有一大部分是重合的，唯一不同的是 $n$ 的头部：$n+1$ 与 $n+1$ 的尾部：$2n+2,2n+1$。  
$n+1$ 与 $2n+2$ 之间的关系是二倍，根据二进制的性质，它们的 1 个数相等。  
于是 $n+1$ 的区间多出了一个数：$2n+1$，不管它的 1 个数是多少，反正不会对答案有负贡献。  
于是我们证明了 $n,n+1$ 之间是单调不减的，整个命题得证。  
于是我们二分套一个数位 dp，这题就做完了：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll dp[65][65][2];ll m,k,tot,p[65];
ll dfs(int pos,int sum,int limit){
	if(pos==tot&&sum==k)return 1;
	if(pos==tot)return 0;
	if(dp[pos][sum][limit]!=-1)
		return dp[pos][sum][limit];
	dp[pos][sum][limit]=0;
	int sz=0;
	if(limit)sz=p[pos+1];
	else sz=1;
	for(int i=0;i<=sz;i++){
		dp[pos][sum][limit]+=dfs(pos+1,sum+i,limit&&(i==sz));
	}
	return dp[pos][sum][limit];
}
ll solve(ll x){
	//cout<<x<<endl;
	memset(dp,-1,sizeof(dp));
	ll res=0;tot=0;ll tmp=x;
	while(tmp){p[++tot]=tmp&1;tmp/=2;}
	for(int i=1;i<=tot/2;i++)
		swap(p[i],p[tot-i+1]);
	//for(int i=1;i<=tot;i++)cout<<p[i];
	//cout<<endl;
	res-=dfs(1,0,0==p[1]);
	if(p[1]==1)res-=dfs(1,1,1);
	//cout<<res<<endl;
	memset(dp,-1,sizeof(dp));tmp=2*x;tot=0;
	while(tmp){p[++tot]=tmp&1;tmp/=2;}
	for(int i=1;i<=tot/2;i++)
		swap(p[i],p[tot-i+1]);
	//for(int i=1;i<=tot;i++)cout<<p[i];
	//cout<<endl;
	res+=dfs(1,0,0==p[1]);
	if(p[1]==1)res+=dfs(1,1,1);
	//cout<<res<<endl;
	return res;
}
int main(){
	cin>>m>>k;
	ll l=1;ll r=1e18;
	while(l<r){
		ll mid=(l+r)/2;
		if(solve(mid)>=m){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}
```


---

## 作者：AladV (赞：0)

## 题意分析
求出任意一个 $n$ 使得 $[n+1,2n]$ 区间内有 $m$ 个数字的二进制表示法中有 $k$ 个 $1$.

## 做法分析
本题解做法与 Codeforces 官方题解做法相同，且不与其他洛谷题解重复。

首先我们先证明一个结论：

$[n+1,2n]$ 区间内的，二进制表示法中有 $k$ 个 $1$ 的数字的数量小于等于区间 $[n+2,2*(n+1)]$。我们把这两个数列罗列出来看一看：

$n+1, n+2,n+3,......,2*n$

$\ \ \ \ \ \ \ \ \ \ \ n+2,n+3,......,2*n,2*n+1,2*n+2$

对比即可发现下面的数列少了一个 $n+1$ ，多了一个 $2*n+1$ 和 一个 $2*n+2$。
显然，$2*n+2$ 和 $n+1$ 的二进制表示法中的 1 的数量相同，所以这个结论是对的。

这样一来我们就证明了 $n$ 的单调性，也就是说我们可以二分啦！

显然，对于区间 $[l,r]$ 来说，我们可以通过计算 $[1,l-1]$ 和 $[1,r]$ 的答案来得到。然后我们考虑如何计算区间 $[1,x]$ 的答案。

我们把 $x$ 当成二进制来看，从高位到低位，我们找每一个 $1$.找到一个 $1$ 后，假设我们已经循环过了 $cnt$ 个 $1$，这时因为一共要有 $k$ 个 $1$，所以我们在剩下的 $i$ 位中还需要出现 $k-cnt$ 个 $1$. 到这里其实我们是在参照着 $x$ 来构造出符合条件的数字。我们还需要预处理一个组合数来计算 $C^{k-cnt}_i$。然后就做完了，剩下的部分就是一个二分。
细节详见代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,k;
int combi[64][64];
int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
int bitcount(int x)
{
    // cout<<x<<endl;
    int res=0;
    while(x)
    {
        if(x%2) res++;
        x>>=1;
    }
    return res;
}
bool bit(int x,int k)
{
    return ((x>>k)&1);
}
int calc(int x)
{
    int res=(bitcount(x)==k);
    // cout<<res<<endl;
    int cnt=0;
    for(int i=63;i>=0;i--) if(bit(x,i)) res+=combi[i][k-cnt],cnt++;
    // cout<<res<<endl;
    return res;
}
signed main()
{
    combi[0][0]=1;
    for(int i=1;i<=63;i++) for(int j=0;j<=i;j++) combi[i][j]=combi[i-1][j]+((j)?(combi[i-1][j-1]):0);
    m=read(),k=read();
    int l=1,r=LLONG_MAX/2;
    
    while(l<r)
    {
        int mid=(l+r)>>1;
        if((calc(mid*2)-calc(mid))<m) l=mid+1;
        else r=mid; 
    }
   
    cout<<l<<endl;
    return 0;
}
```


---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF431D)

# 题解

由于题目要求的 $n$ 十分巨大（$n\le 10^{18}$），并且要求**恰好**有 $m$ 个数二进制下有 $k$ 个 $1$，考虑二分~~（先猜后证~~

但是如果要使用二分，需要证明单调性，我们记 $f(x)$ 为 $x+1$ 到 $2x$ 之间的数中，他们二进制表示下恰好有 $k$ 个 $1$ 的数字个数，如果有单调性，显然是 $f(x)\le f(x+1)$，如何证明？

由于 $f(x)$ 是区间 $[x+1,2x]$ 的个数，$f(x+1)$ 是区间 $[x+2,2x+2]$ 的个数，去除相同的部分，$f(x)$ 就剩下 $x+1$，而 $f(x+1)$ 剩下 $2x+1,2x+2$，由于 $x+1$ 与 $2x+2$ 的 $1$ 的个数相同（相当于左移一位），那么如果 $2x+1$ 满足条件，$f(x)=f(x+1)-1$，反之 $f(x)=f(x+1)$，也就是说，无论如何都有 $f(x)\le f(x+1)$，可证其单调性。

考虑目前二分到一个 $n$，我们如何计算 $f(n)$？考虑记 $g(n)$ 为 $[1,n]$ 中满足条件的数，那么 $f(n)=g(2n)-g(n)$，而 $g(n)$ 可以考虑使用数位 $DP$ 来做。

优化：其实 $g(x)$ 可以使用组合数进行优化，这样也是合理的。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13474384.html
```



---

