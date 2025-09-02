# [USACO24JAN] Cowmpetency G

## 题目描述

Farmer John 正在为他的奶牛们雇用一位新的牛群领队。为此，他面试了 $N$（$2\le N\le 10^9$）头奶牛来担任该职位。在每次面试后，他会为候选牛分配一个 $1$ 到 $C$（$1\le C\le 10^4$）范围内的整数「牲任力」分数 $c_i$，与她们的领导能力相关。

由于 Farmer John 面试了如此多的奶牛，他已经忘记了所有奶牛的牲任力分数。然而，他确实记得 $Q$
（$1\le Q\le \min(N-1,100)$）对数字 $(a_i,h_i)$，其中奶牛 $h_i$ 是第一头比奶牛 $1$ 到 $a_i$ 拥有**严格**更高牲任力分数的奶牛（所以 $1\le a_i<h_i\le N$）。

Farmer John 现在告诉你这 $Q$ 个数对 $(a_i,h_i)$。请帮助他数一下有多少个牲任力分数序列与此信息一致！输入保证存在至少一个这样的序列。由于这个数字可能非常大，输出该值模 $10^9+7$ 的余数。

## 说明/提示

### 样例解释 1

以下六个序列是仅有的与 Farmer John 记忆一致的序列：

$1\ 1\ 2\ 1\ 3\ 1$  
$1\ 1\ 2\ 1\ 3\ 2$  
$1\ 1\ 2\ 1\ 3\ 3$  
$1\ 1\ 2\ 2\ 3\ 1$  
$1\ 1\ 2\ 2\ 3\ 2$  
$1\ 1\ 2\ 2\ 3\ 3$  

### 样例解释 2

确保输出答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $3-4$：$N\le 10$ 且 $Q,C\le 4$。
- 测试点 $5-7$：$N,C\le 100$。
- 测试点 $8-10$：$N\le 2000$ 且 $C\le 200$。
- 测试点 $11-15$：$N,C\le 5000$。
- 测试点 $16-20$：没有额外限制。

## 样例 #1

### 输入

```
6 2 3
2 3
4 5```

### 输出

```
6```

## 样例 #2

### 输入

```
10 1 20
1 3```

### 输出

```
399988086```

# 题解

## 作者：Genius_Star (赞：15)

### 思路：

**感觉不错，中等蓝吧……**

考虑对第 $i$ 个数有三种可能的状态 $-1/1/0$ 分别表示：**不可能**是严格前缀最大值；**一定**是严格前缀最大值；**可能**是前缀最大值。

那么我们需要对于一个限制 $(x,y)$，确定一些位置的状态。

因为该限制需要满足：

$$\max\limits_{i=x+1}^y a_i \le \max\limits_{i=1}^x a_i < a_y$$

则区间 $[x+1,y-1]$ **不可能**是严格前缀最大值，状态为 $-1$；且单点 $y$ **一定**是严格前缀最大值。

经过这样的判断，如果一个点既**一定**又**不可能**，那么就**无解**。

然后考虑动态规划算法，定义 $dp_{i,j}$ 表示考虑序列 $a$ 中前 $i$ 项，其前缀最大值为 $j$ 时的可能方案，则状态转移方程为：

$$dp_{i,j}=\begin{cases} dp_{i-1,j} \times j & op_i=-1\\ \sum\limits_{k=1}^{j-1} dp_{i-1,k}  + dp_{i-1,j} \times j& op_i = 0 \\ \sum\limits_{k=1}^{j-1} dp_{i-1,k}& op_i = 1\end{cases}$$

很容易想到用**前缀和优化**，定义：

$$s_{i,j}=\sum_{k=1}^j dp_{i,k}$$

状态转移方程优化为：

$$dp_{i,j}=\begin{cases} dp_{i-1,j} \times j & op_i=-1\\ s_{i-1,j-1} + dp_{i-1,j} \times j& op_i = 0  \\ s_{i-1,j-1} & op_i = 1\end{cases}$$

时间复杂度为 $O(NC)$，至此，我们已经获得了 75pts 的好成绩。

但是因为 $N$ 实在是太大了，**重复**的状态段特别多，考虑**缩段**，将连续的一段 $0$ 和 $-1$ 缩为一个点，因为状态为 $1$ 的个数是 $O(q)$ 级别的，可以不用缩点，而且缩点之后的状态转移不好计算。

定义第 $i$ 段的长度为 $A_i$，状态为 $OP_i$，即若 $OP_i=1$，则 $A_i=1$；然后定义 $dp_{i,j}$ 表示前 $i$ 段的前缀最大值为 $j$ 的方案数，则状态转移方程为：

$$dp_{i,j}=\begin{cases} dp_{i-1,j} \times j^{A_i} & OP_i = -1 \\ f(A_i,j) \sum\limits_{k=1}^{j-1} dp_{i-1,k} + dp_{i-1,j} \times j^{A_i}& OP_i = 0 \\ \sum\limits_{k=1}^{j-1} dp_{i-1,k} & OP_i = 1\end{cases}$$

其中 $f(x,y)$ 表示 $x$ 个在 $[1,y]$ 范围内的数，出现至少一个 $y$ 的方案数，则相当于任意取的方案数减去不出现 $y$ 的方案数：

$$f(x,y)=y^x-(y-1)^x$$

这个也可以进行前缀和优化：

$$dp_{i,j}=\begin{cases} dp_{i-1,j} \times j^{A_i} & OP_i = -1 \\ f(A_i,j) \times s_{i-1,j-1} + dp_{i-1,j} \times j^{A_i}& OP_i = 0 \\ s_{i-1,j-1} & OP_i = 1\end{cases}$$

这样加上快速幂的计算，时间复杂度为 $O(QC \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll Q=505,N=10100,mod=1e9+7; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct St{
	ll l,r;
	bool operator<(const St&rhs)const{
		if(r==rhs.r)
		  return l<rhs.l;
		return r<rhs.r;
	}
}h[N];
ll n,q,c,cnt=0,l=1;
ll A[Q],op[Q];
ll dp[Q][N],s[Q][N];
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
	 	  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	n=read(),q=read(),c=read();
	for(int x,y,i=1;i<=q;i++){
		x=read(),y=read();
		h[i]={x+1,y};
	}
	sort(h+1,h+q+1);
	for (int i=1;i<=q;i++){
		if(h[i].r==h[i-1].r)
		  continue;
		if(l>h[i].l){
			puts("0");
			exit(0);
		}
		if(l<h[i].l){
			cnt++;
			A[cnt]=h[i].l-l;
			op[cnt]=0;
		}
		if(h[i].l<h[i].r){
			cnt++;
			A[cnt]=h[i].r-h[i].l;
			op[cnt]=-1;
		}
		cnt++;
		A[cnt]=1;
		op[cnt]=1;
		l=h[i].r+1;
	}
	if(h[q].r<n){
		cnt++;
		A[cnt]=n-h[q].r;
		op[cnt]=0;
	}
//	for(int i=1;i<=cnt;i++){
//		write(op[i]);
//		putchar(' ');
//	}
//	putchar('\n');
	dp[0][0]=1;
	for(int i=0;i<=c;i++)
	  s[0][i]=1;
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=c;j++){
			ll x=qpow(j,A[i]),y=qpow(j-1,A[i]);
			if(op[i]==-1)
			  dp[i][j]=(dp[i-1][j]*x)%mod;
			else if(!op[i])
			  dp[i][j]=(((x-y+mod)%mod*s[i-1][j-1])%mod+(dp[i-1][j]*x)%mod)%mod;
			else
			  dp[i][j]=s[i-1][j-1];
			s[i][j]=(s[i][j-1]+dp[i][j])%mod;
		}
	}
//	for(int i=1;i<=cnt;i++){
//		for(int j=1;j<=c;j++){
//			write(s[i][j]);
//			putchar(' ');
//		}
//		putchar('\n');
//	}
	write(s[cnt][c]);
	return 0;
}
```


---

## 作者：vegetable_king (赞：4)

[可能更好的阅读体验](https://yjh965.github.io/post/usaco24jan-cowmpetency-g-ti-jie/)

在阅读本篇题解之前，请阅读 [[USACO24JAN] Cowmpetency S 题解](https://yjh965.github.io/post/usaco24jan-cowmpetency-s-ti-jie/)（或者[洛谷博客链接](https://www.luogu.com.cn/blog/477443/usaco24jan-cowmpetency-s-ti-xie)）。

首先考虑一个 $O(nc^2)$ 的暴力 dp：设 $f_{i, j}$ 表示目前考虑 $a$ 前 $i$ 项，前缀 $\max = j$ 的方案数。转移方程显然：
$$
f_{i, j} \gets
\begin{cases}
j \times f_{i - 1, j} & b_i = -1\\
j \times f_{i - 1, k} (k \le j) & b_i = 0\\
j \times f_{i - 1, k} (k < j) & b_i = 1\\
\end{cases}
$$
可以前缀和优化至 $O(nc)$。

我们发现，如果将 $b$ 中连续的 $0, -1$ 缩成一段，则段数是 $O(q)$ 的，而连续的一段 $0, -1$ 可以一起计算。设第 $i$ 段元素为 $b_i$，长度为 $c_i$（当 $b_i = 1$ 时 $c_i = 1$），$f_{i, j}$ 表示目前考虑前 $i$ 段，前缀 $\max = j$ 的方案数。转移方程考虑讨论当前这一段是否出现了新的前缀最大值：

$$
f_{i, j} \gets j^{c_i} \times f_{i - 1, j} (b_i \ne 1)\\
f_{i, j} \gets g_{c_i}(x) \times f_{i - 1, k} (k < j, b_i \ne -1)\\
$$

其中 $g_y(x)$ 为 $y$ 个 $[1, x]$ 的整数至少有一个为 $x$ 的方案数，用任意情况减去一个 $x$ 都没有的情况可以推出 $g_y(x) = x^y - (x - 1)^y$。

可以前缀和优化至 $O(qc \log n)$，[代码](https://www.luogu.com.cn/paste/jptui5nq)在这里。

---

## 作者：qwer6 (赞：1)

[Link](https://www.luogu.com.cn/problem/P10138)

## 1. Description

对于一个长度为 $n$，所有元素均在 $[1,c]$ 的范围内的序列 $val$，询问满足 $q$ 个限制的序列有多少个。

限制形如 $(a,h)$，要求 $val_h$ 是第一个严格大于 $\max \limits_{i=1}^{a} val_i$ 的值位置，题给条件满足至少存在一个合法序列。

## 2. Solution

考虑限制 $(a,h)$，设 $x=\max\limits_{i=1}^a val_i,y=\begin{cases}0\ (a+1>h-1)\\ \max\limits_{i=a+1}^{h-1} val_i\end{cases},z=val_h$，那么有 $y\le x<z$。

因此对于 $h$ 这个位置，一定是严格前缀最大值，对于 $[a+1,h-1]$ 这些位置，一定不是严格前缀最大值。

我们不妨使用一个数组 $opt$ 表示整个序列的限制情况，当 $opt_i>0$ 时，这个位置一定是严格前缀最大值，当 $opt_i<0$ 时，这个位置一定不是严格前缀最大值，当 $opt_i=0$ 时，这个位置没有限制。

所以对于一个限制 $(a,h)$，将 $[a+1,h-1]$ 这一段减一，然后在 $h$ 这个位置加一即可。由于必存在一个合法序列，所以不会出现一个位置同时进行了加一和减一两种操作的情况，也就是既一定又不一定的情况。

然后考虑 dp，定义 $f_{i,j}$ 表示考虑前 $i$ 项，此时前缀最大值为 $j$ 的方案数，那么转移可以分为两种：这一项是或不是严格前缀最大值。

当这一项是严格前缀最大值时，由于前缀最大值是 $j$，所以这一项必须是 $j$，且前 $i-1$ 项的前缀最大值严格小于 $j$，那么就有 $\sum\limits_{k=1}^{j-1} f_{i-1,k}$ 种情况，可以使用前缀和优化，定义 $g_{i,j}=\sum\limits_{k=1}^j g_{i,k}$，那么就有 $g_{i-1,j-1}$ 种情况。

当这一项不是严格前缀最大值时，前 $i-1$ 项的前缀最大值一定是 $j$，这一项可以取 $1\sim j$ 的任一一个，那么就有 $f_{i-1,j}\times j$ 种情况，无需优化。

因此，转移可以写为：
$$
f_{i,j}=
\begin{cases}
f_{i-1,j}\times j\ (opt_i<0)\\
f_{i-1,j}\times j+g_{i-1,j-1}\ (opt=0)\\
g_{i-1,j-1}\ (opt>0)\\
\end{cases}
$$
此时的时空复杂度为 $O(nc)$，考虑优化。

我们发现，有很多段 $opt$ 序列的值是一样的，所以我们考虑将 $opt$ 分成若干段连续的区间，那么区间数是 $O(q)$ 的，那么 $f_{i,j}$ 表示考虑前 $i$ 段，此时前缀最大值为 $j$ 的方案数。

所以此时只需考虑一段 $(l,r,opt)$ 怎么快速转移。

当 $opt<0$ 的时候，显然 $f_{i,j}=f_{i-1,j}\times j^{r-l+1}$。

当 $opt>0$ 的时候，由于 $opt>0$ 的位置一共就只有 $O(q)$ 个，所以可以直接暴力转移。

当 $opt=0$ 的时候，就需要分类讨论了：

1. 前缀最大值出现在前 $i-1$ 段，那么这 $r-l+1$ 个值可以取 $[1,j]$ 的任一一个值，所以一共有 $f_{i-1,j}\times j^{r-l+1}$ 种。
2. 前缀最大值出现在第 $i$ 段，那么这 $r-l+1$ 个值中至少有一个为 $j$，考虑反转问题，在 $r-l+1$ 个值中一个 $j$ 都没有的情况有 $(j-1)^{r-l+1}$ 种，而一共有 $j^{r-l+1}$ 种情况，所以这 $r-l+1$ 个值中至少有一个为 $j$ 情况有 $j^{r-l+1}-(j-1)^{r-l+1}$ 种，而前 $i-1$ 段的前缀最大值小于 $j$，就有 $\sum\limits_{k=1}^{j-1} f_{i-1,k}$ 种情况，同样可以使用前缀和优化，定义 $g_{i,j}=\sum\limits_{k=1}^{j} f_{i,k}$。那么就一共有 $g_{i-1,j-1}\times [j^{r-l+1}-(j-1)^{r-l+1}]$ 种情况。

所以，当 $opt=0$ 的时候，$f_{i,j}=f_{i-1,j}\times j^{r-l+1}+g_{i-1,j-1}\times [j^{r-l+1}-(j-1)^{r-l+1}]$。

那么我们只需要根据所有限制求出 $opt$ 序列分成的 $(l,r,opt)$，然后转移即可，注意两个区间有交的情况，此时需要合并。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=105,M=1e4+5,mod=1e9+7;
int n,m,c,ans,cnt;
int f[N*3][M];
struct Line{
    int l,r,opt;
    bool operator <(const Line &a){
        return l<a.l;
    }
}a[N<<1],b[N<<1];
int sub(int x,int y){
    x-=y;
    return x<0?x+mod:x;
}
int add(int x,int y){
	x+=y;
	return x>=mod?x-mod:x;
}
int mul(int x,int y){
	long long res=1ll*x*y;
	return res>=mod?res%mod:res;
}
int binpow(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=mul(res,a);
        a=mul(a,a);
        b>>=1;
    }
    return res;
}
int init(){
    int tmp=0,_l=a[1].l,_r=a[1].r,_opt=a[1].opt;
    for(int i=2,l=a[1].l,r=a[1].r;i<=cnt;i++){
        if(a[i].opt!=_opt||a[i].l>min(a[i].r,_r)){//必然视为两份  
            b[++tmp]={_l,_r,_opt};
            _l=a[i].l,_r=a[i].r,_opt=a[i].opt;
        }else _r=max(a[i].r,_r);
    }
    b[++tmp]={_l,_r,_opt};
    int ttmp=tmp,las=1;
    for(int i=1;i<=tmp;i++){
        if(las<=b[i].l-1)b[++ttmp]={las,b[i].l-1,0};
        las=b[i].r+1; 
    }
    if(las<=n)b[++ttmp]={las,n,0};
    sort(b+1,b+ttmp+1);
    return ttmp;
}
void DP(int idx,int l,int r,int opt){
    int len=r-l+1;
    if(opt==-1){
        for(int i=1;i<=c;i++)
            f[idx][i]=mul(f[idx-1][i],binpow(i,len));
    }else if(opt==0){
        for(int j=1,sum=0,x;j<=c;j++){
            sum=add(sum,f[idx-1][j-1]),x=binpow(j,len);
            f[idx][j]=mul(sum,sub(x,binpow(j-1,len)));
            f[idx][j]=add(f[idx][j],mul(f[idx-1][j],x));
        }
    }else{
        for(int j=1,sum=0;j<=c;j++){
            sum=add(sum,f[idx-1][j-1]);
            f[idx][j]=sum;
        }
        for(int i=2;i<=len;i++){
            for(int j=1,sum=0;j<=c;j++){
                sum=add(sum,f[idx][j-1]);
                f[idx][j]=sum;
            }
        }
    }
}
signed main(){
	read(n),read(m),read(c);
	for(int i=1,x,y;i<=m;i++){
        read(x),read(y);
        if(x+1<=y-1)a[++cnt]={x+1,y-1,-1};
        a[++cnt]={y,y,1};
    }
    sort(a+1,a+cnt+1);
    cnt=init();
    f[0][0]=1;
    for(int i=1;i<=cnt;i++)
        DP(i,b[i].l,b[i].r,b[i].opt);
    for(int i=1;i<=c;i++)ans=add(ans,f[cnt][i]);
    write(ans);
}
```

---

## 作者：Wei_Han (赞：1)

我是蠢货。

简单观察一下性质，我们假设有 $a_i < a_j < h_i < h_j$，也就是两个区间是有交的，那么 $h_i$ 应为 $[1,a_i]$ 之后的第一个最大值，且 $h_i$ 也应比 $(a_i,h_i)$ 中的所有数大，那么进而可以发现 $h_i$ 一定是 $[1,a_j]$ 后第一个比它大的数，而 $h_j$ 无论填什么都无法合法，完全覆盖的情况是同理的。所以当任意两个区间有交时，答案为 $0$，然后简单讨论一下重合情况就好了，左端点重合一样无解，右端点重合显然 $a_i$ 更小的要求更严格，所以我们可以将所有区间排序后去重，问题转化为一堆无交集区间怎么做。

这样就简单很多了，由于 $n \leq 10^9$，我们逐个区间来看：

![](https://cdn.luogu.com.cn/upload/image_hosting/o4mctec6.png)

设 $f_{i,j}$ 表示到第 $i$ 个区间，$h_i$ 为 $j$ 的方案数，如图，我们令 $(h_{i-1},a_i]$ 的区间长为 $l_1$，$[a_i,h_i)$ 的长度为 $l_2$。

考虑枚举 $k$ 表示 $(h_{i-1},a_i]$ 中的最大值，那么向 $(h_{i-1},h_i)$ 中填数的方案数为 $k^{l_1+l_2} - (k-1)^{l_1}k^{l_2}$，减一个数是减去了 $(h_{i-1},a_i]$ 没有取 $k$ 的方案，然后拿之前的方案数加起来就好了，注意再讨论一下 $i-1$ 时就取到了 $k$ 的方案，也就是有转移：

$$f_{i,j} = \sum \limits_{k=1}^{j-1} f_{i-1,k}k^{l_1+l_2}+k^{l_2}(k^{l_1}-(k-1)^{l_1})\sum \limits_{p=1}^{k-1} f_{i-1,p}$$

最后的一个 $\sum$ 显然可以前缀和优化掉，此时复杂度 $O(qc^2\log n)$，然后发现每一轮枚举计算的 $k$ 其实是重复的，可以再一遍前缀和优化，或者将转移该写为：

$$f_{i,j} = f_{i,j-1}+f_{i-1,k}k^{l_1+l_2}+k^{l_2}(k^{l_1}-(k-1)^{l_1})\sum \limits_{p=1}^{k-1} f_{i-1,p}$$

这里 $k=j-1$，这样就可以 $O(1)$ 转移了，注意对于最后一个位置，$(h_{m},n]$ 之前的数是可以随便取的，统计答案时算上就好了，复杂度 $O(qc\log n)$。

```cpp
const ll N=1e6+5,M=2e4+5,mod=1e9+7;
ll n,q,C,cnt,f[105][M],pre[105][M];
struct Q{ll a,h;}a[105],b[105];
inline ll qpow(ll a,ll b){return !b?1ll:qpow(a*a%mod,b>>1)*((b&1)?a:1ll)%mod;}
signed main(){
	read(n),read(q),read(C);fo(1,i,q) read(a[i].a),read(a[i].h);
	sort(a+1,a+1+q,[&](Q a,Q b){return a.h==b.h?a.a<b.a:a.h<b.h;});
	fo(1,i,q) fo(1,j,q) if(a[i].a<a[j].h&&a[i].a>=a[j].a&&a[i].h!=a[j].h) return wr(111),0;
	fo(1,i,q) if(a[i].h==a[i-1].h) continue;else b[++cnt]=a[i];q=cnt;fo(1,i,cnt) a[i]=b[i];
	fo(0,j,C) f[0][1]=1;fo(1,j,C) pre[0][j]=1;
	fo(1,i,q){
		fo(1,j,C)
		{
			ll k=j-1;if(k==0) continue;
			ll num=pre[i-1][k-1];
			ll len1=a[i].a-a[i-1].h,len2=a[i].h-a[i].a-1;
			num=num*qpow(k,len2)%mod*((qpow(k,len1)-qpow(k-1,len1)+mod)%mod)%mod;
			num=(num+f[i-1][k]*qpow(k,len1+len2)%mod)%mod;
			f[i][j]=(f[i][j-1]+num)%mod;
		}
		fo(1,j,C) pre[i][j]=(pre[i][j-1]+f[i][j])%mod;
	}
	ll sum=0;fo(1,j,C) sum=(sum+f[q][j]*qpow(C,n-a[q].h)%mod)%mod;wr(sum),pr;
	return 0;
}
``````

---

## 作者：cff_0102 (赞：1)

注：下面所说的“前缀最大值”均为严格最大值。

对于每一对 $(a_i,h_i)$，我们有：

- 对于 $1\sim a_i$ 的数，（如果只考虑这个条件的话）它们可以是前缀最大值，也可以不是；
- 对于 $a_i+1\sim h_i-1$ 的数，它们不可能是前缀最大值；
- 对于 $h_i$，它必须是前缀最大值。

注意到如果有一个 $h_i$ 在其它的 $a_j+1\sim h_j-1$ 中，那么是无解的。如果有一对 $(a_i,h_i),(a_j,h_j)$ 满足 $h_i=h_j$，$a_i<a_j$，那么 $(a_i,h_i)$ 的要求更严格，后者就可以直接忽略。

把无解情况排除并忽略掉上面所说的情况后，剩下的区间必然互不相交。

先抛开 $N\le10^9$ 的数据范围不谈，来看看假设我们为每头奶牛设计一个状态，应该怎么进行 dp。

显然，这头奶牛有三种可能：

- 它可以是前缀最大值，也可以不是；
- 它不能是前缀最大值；
- 它必须是前缀最大值；

分别记这三种情况为 $0,-1,1$，第 $i$ 头奶牛的状态记为 $sta_i$。设 $dp_{i,j}$ 表示考虑前 $i$ 头奶牛，且前 $i$ 头奶牛中的最大值为 $j$ 时，有几种填法。那么可以推出如下状态转移方程：

$$dp_{i,j}=\begin{cases}\sum\limits^{j-1}_{k=1}dp_{i-1,k}&sta_i=1\\\sum\limits^{j-1}_{k=1}dp_{i-1,k}+dp_{i-1,j}\times j&sta_i=0\\dp_{i-1,j}\times j&sta_i=-1\end{cases}$$

其中求和的部分可以使用前缀和解决，这样就能在 $O(NC)$ 的时间复杂度内解决。

但是本题的 $N\le10^9$，显然不能直接设状态。注意到每一对 $(a_i,h_i)$ 都可以导致状态多出一块的 $0,-1,1$（分别是 $h_{i-1}+1\sim a_i$，$a_i+1\sim h_i-1$ 和 $h_i$），又注意到本题的 $Q\le100$，显然可以把每一块这样相同的状态合在一起考虑，因为这些格子可以选取的数的范围是相同的，直接使用快速幂即可求出这一整块的方案数。

设 $dp_{i,j}$ 为考虑前 $i$ 块，且这 $i$ 块的最大值为 $j$ 时，有几种填法，再设 $len_i$ 为第 $i$ 段的长度，那么可以得出：

$$dp_{i,j}=\begin{cases}\sum\limits^{j-1}_{k=1}dp_{i-1,k}&sta_i=1\\\sum\limits^{j-1}_{k=1}dp_{i-1,k}\times(j^{len_i}-(j-1)^{len_i})+dp_{i-1,j}\times j^{len_i}&sta_i=0\\dp_{i-1,j}\times j^{len_i}&sta_i=-1\end{cases}$$

$h_Q\sim N$ 的 $sta_i$ 全部为 $0$，这一块也是需要计算的，方法相同，不要忘了。

这里同样可以用前缀和优化，最后的复杂度就变为 $O(QC\log N)$ 了（其中 $\log N$ 是快速幂的复杂度）。这个转移方程式可以参照代码理解。

需要注意的是，如果跳过了一个本文开头所说的可以忽略的区间，那么需要把上一个区间的最后一个答案复制过来，否则处理下一块的答案时读到的之前的答案就是 $0$ 了。另外，还要注意数组的初始化，特别不要忘记初始化前缀和数组。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105,M=1e4+5,mod=1e9+7;
pair<int,int>p[N];
int dp[N*3][M],sdp[N*3][M],len[N*3];
int ksm(int a,int b){
	int base=a,ans=1;
	while(b){
		if(b&1)ans*=base,ans%=mod;
		base*=base;base%=mod;
		b>>=1;
	}
	return ans;
}
int cal(int l,int r){
	return r-l+1;
}
int cal2(int n,int x){
	//有 n 个数，每个数的范围是 1-x，且这 n 个数的最大值是 x，求方案数 
	return (ksm(x,n)-ksm(x-1,n)+mod)%mod;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,q,c;cin>>n>>q>>c;
    for(int i=1;i<=q;i++)cin>>p[i].first>>p[i].second;
    sort(p+1,p+1+q);
    p[0].second=0;
    dp[0][0]=1;
    for(int j=0;j<=c;j++)sdp[0][j]=1;
    for(int i=1;i<=q;i++){
		int i1=i*3-2,i2=i*3-1,i3=i*3;
        if(p[i].second==p[i-1].second){
        	for(int j=1;j<=c;j++)sdp[i3][j]=sdp[i1-1][j],dp[i3][j]=dp[i1-1][j];
        	continue;
        }
        if(p[i].first<p[i-1].second)return cout<<0<<endl,0;
        int __1=cal(p[i].first+1,p[i].second-1),_0=cal(p[i-1].second+1,p[i].first);
		for(int j=1;j<=c;j++){
			//第一段的 0
			dp[i1][j]=(dp[i1-1][j]*ksm(j,_0)%mod/*不是前缀最大值*/+sdp[i1-1][j-1]*cal2(_0,j)%mod/*是前缀最大值*/)%mod;
			//第二段的 -1
			dp[i2][j]=dp[i1][j]*ksm(j,__1)%mod;//不是前缀最大值
			//第三段的 1
			dp[i3][j]=sdp[i2][j-1]/* *cal2(1,j) */;//是前缀最大值
			sdp[i1][j]=(sdp[i1][j-1]+dp[i1][j])%mod;
			sdp[i2][j]=(sdp[i2][j-1]+dp[i2][j])%mod;
			sdp[i3][j]=(sdp[i3][j-1]+dp[i3][j])%mod;
		}
    }
    for(int j=1;j<=c;j++){
    	int _0=cal(p[q].second+1,n);
    	dp[q*3+1][j]=(dp[q*3][j]*ksm(j,_0)%mod+sdp[q*3][j-1]*cal2(_0,j)%mod)%mod;
    	if(_0==0)dp[q*3+1][j]=dp[q*3][j];
    	sdp[q*3+1][j]=(sdp[q*3+1][j-1]+dp[q*3+1][j])%mod;
	}
	cout<<sdp[q*3+1][c];
    return 0;
}
```

---

## 作者：Helenty (赞：0)

限制转化为强制其一定是或不是前缀唯一最大值，然后合并连续段考虑，连续段个数为 $O(Q)$。

那么我们设 $f_{i,j}$ 前 $i$ 个连续段的最大值为 $j$ 的方案数。

后面接 $x$ 个严格前缀最大值有 $f_{i,j}\binom{k-j}{x}\rightarrow f_{i+1,k}$。

接 $x$ 个非严格前缀最大值有 $f_{i,j}j^x\rightarrow f_{i+1,j}$。

接 $x$ 个无限制数有 $f_{i,j}(k^x-(k-1)^x)\rightarrow f_{i+1,k} (k>j),f_{i,j}j^x\rightarrow f_{i+1,j}$。

容易发现只有上面的无法优化，可以想到我们不用将一定前缀最大值的数缩成连续段因为其个数本身就只有 $O(Q)$。

那么接一个严格前缀最大值有 $f_{i,j}\rightarrow f_{i+1,k}(k>j)$。

这样就可以做到 $O(QC\log n)$ 了。

---

