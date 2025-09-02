# Paint

## 题目描述

给定长度为 $n$ 的颜色序列 $a_i$，每次你可以选择任意长度的**连续且颜色相同**的一段位置，将其全部变成任意同一种颜色，问你最少总共需要多少次操作才能使得整个序列颜色相同。

**限制：** 每一种颜色初始时在序列中最多只有20个位置（是该种颜色）。

## 样例 #1

### 输入

```
3
5
1 2 3 2 1
4
1 1 2 2
5
1 2 1 4 2```

### 输出

```
2
1
3```

# 题解

## 作者：dottle (赞：18)

有一个显然的合并方法，其操作次数为 $n-1$，若让两个相同颜色的像素 $i,j$ 在同一次操作内更改颜色，则答案会减少 $1$。要这样做的话，我们相当于需要让 $(i,j)$ 的所有像素变成同一个颜色，再让 $[i,j]$ 的所有像素变为同一个颜色。我们称这样过程为优化了 $(i,j)$。容易发现，对于 $a<b<c<d$，我们不能同时优化 $(a,c)$ 与 $(b,d)$。

令 $f_{i,j}$ 表示合并 $[i,j]$ 的最大优化次数。那么最终的答案就是 $n-1-f_{i,n}$。转移方程则是

$$
f_{i,j}=\max(f_{i+1,j},\max_{a_i=a_k}f_{i+1,k-1}+1+f_{k,j}) 
$$

前半部分不赘述，后半部分的含义即我们优化了 $(i,k)$。注意加号后面是 $f_{k,j}$ 而非 $f_{k+1,j}$，原因是我们可以同时优化 $(i,k)$ 和 $(k,j)$，表示这三个像素在同时被更改颜色了。

---

## 作者：wmy_goes_to_thu (赞：9)

这个就是 ICPC Kunming 的题，看到这个范围显然要想区间 dp：

第一步，贪心地把每一段同颜色的区间缩点，设第 $i$ 个点的颜色为 $c_i$。

第二步，设 $f_{i,j}$ 表示 $[i,j]$ 染成 $c_j$ 的最小代价。为什么答案是 $f_{1,n}$？因为如果不染成 $c_n$，就会把 $c_n$ 进行染色，这样还不如一步把 $[1,n-1]$ 染成 $c_n$ 好。

第三步，转移：

显然，$f_{i,j}$ 可以转移为 $\min\{f_{i+1,j},f_{i,j-1}\}+1$。

如果存在一个 $i\leq k\lt j$ 且 $c_k=c_j$，那么我们可以分成两段 $[i,k]$ 和 $(k,j]$ 进行转移，也就是 $f_{i,k}+f_{k+1,j}$，所以只需要记录每个点 $i$ 的 $pre_i$（也就是上一个和它颜色相同的点）即可。

复杂度 $O(20n^2)$，常数不大，可过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[3005][3005],a[3005],b[3005],s[3005],d[3005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int m,n=0;
		cin>>m;
		for(int i=1;i<=m;i++)scanf("%d",&b[i]),d[b[i]]=0;
		for(int i=1;i<=m;)
		{
			int j=i;
			while(j<=m&&b[j]==b[i])j++;
			a[++n]=b[i],i=j;
		}
		for(int i=1;i<=n;i++)
		{
			s[i]=0;
			if(d[a[i]])s[i]=d[a[i]];
			d[a[i]]=i;
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
			f[i][j]=INT_MAX;
		for(int i=1;i<=n;i++)f[i][i]=f[i+1][i]=0;
		for(int l=2;l<=n;l++)for(int i=1;i<=n-l+1;i++)
		{
			int j=i+l-1;
			f[i][j]=min(f[i][j-1],f[i+1][j])+1;
			for(int k=s[j];k>=i;k=s[k])
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
		cout<<f[1][n]<<endl;
	}
	return 0;
}
```

---

## 作者：Komorebi_03 (赞：8)

## 思路
这道题和[P4170 [CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170)的思路有点类似。

给出一段序列，上面有不同的颜色区间，问把这个序列变为同一种颜色的最小操作次数。

那么可以把问题转化为：用最小次数，把序列的颜色都变成序列最后一段颜色的颜色。

那么可以得出一种 DP 思路，先把 $\begin{bmatrix} 1,n-1 \end{bmatrix}$ 染成同一种颜色，最后一次把颜色染成 $n$ 的颜色就行了。

所以可以设 $dp_{l,r}$ 为将区间 $\begin{bmatrix} l,r \end{bmatrix}$ 全部染为 $a_r$ 需要的最小操作次数。

由上可得转移方程式为：

 $dp_{l,r} = \begin{cases}
  dp_{l+1,r}+1	\\
  dp_{l,r-1}+1	\\
  dp_{l,k}+dp_{k+1,r} & a_k=a_r	\\
\end{cases}$ 

上述三种转移的意思分别是：

1. 最左边的点先不管，在完成区间 $\begin{bmatrix} l+1,r \end{bmatrix}$ 的操作后，再把最左边的点并上。

2. 与第一个同理，最右边的点先不管，完成区间 $\begin{bmatrix} l,r-1 \end{bmatrix}$ 的操作后，把最右边的点并上。

3. 当我们在操作前两个转移时，可能会出现并不是最优的情况，比如下面这种情况：![](https://cdn.luogu.com.cn/upload/image_hosting/aj2zzfqv.png)显然先把两个红色之间的颜色全部染为红色再染左边剩余的两个是最优的，而不是先把 $\begin{bmatrix} 1,n-1 \end{bmatrix}$ 合起来再并上 $n$，所以就有了第三种转移，枚举一个和 $a_r$ 同颜色的 $a_k$，先操作 $\begin{bmatrix} l,k \end{bmatrix}$，再操作 $\begin{bmatrix} k+1,r \end{bmatrix}$。

注意，最后一种转移还需要额外记录上一个和这个点颜色相同的点。

复杂度为 $O(n^2)$。

```cpp
//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3e3+10;
int T,n,a[N],pre[N],pos[N],dp[N][N];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int main()
{
    T=read();
    while (T--)
    {
        n=read();
        for (int i=1;i<=n;i++)
        {
            a[i]=read();
            pos[a[i]]=0;
        }
        for (int i=1;i<=n;i++)
        {
            pre[i]=pos[a[i]];
            pos[a[i]]=i;
        }
        for (int len=2;len<=n;len++)
        {
            for (int l=1;l+len-1<=n;l++)
            {
                int r=l+len-1;
                dp[l][r]=dp[l][r-1]+1;
                for (int k=pre[r];k>=l;k=pre[k])
                    dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
            }
        }
        cout<<dp[1][n]<<"\n";
    }
    return 0;
    //Amireux_35
}
```


---

## 作者：Cry_For_theMoon (赞：6)

[传送门](https://codeforces.com/contest/1572/problem/C)

不知道比 1B 水到哪里去了。

个人感觉真实难度不到 2200。

#### 分析：

容易想到区间 dp：设 $f(i,j)$ 为令区间 $[i,j]$ 同色的最少操作次数。

结论：**一定存在一种最优方案使得最后的颜色为 $c_i$**。

证明：容易发现先让 $[i+1,j]$ 同色，再让这个颜色和 $c_i$ 统一会是一类最优解，因为不管什么时候合并 $c_i$ ，由于它是最左边的点，对其它的也没有影响。那么最后合并的时候，要么本来 $[i+1,j]$ 的颜色就是 $c_i$，符合条件；否则我们必须花一次操作调整颜色，就修改 $[i+1,j]$ 的颜色为 $c_i$ 即可。

所以修改 dp 状态的定义为 $f(i,j)$ 为令区间 $[i,j]$ 的颜色为 $c_i$ 的最优答案。

那么最暴力的转移：

$f(i,j)=\min\{f(i,k)+f(k+1,j)+[c_i\neq c_{k+1}]\}$

这个东西是三方的。题目告诉我们同色点不超过 $20$ 个所以可以大胆猜测绝大部分 $[c_i \neq c_{k+1}]$ 的点是无意义的。事实上，可以证明，我们的最优解，要么取转移点 $k$ 满足 $c_i=c_{k+1}$，要么直接取 $f(i+1,j)+1$：

一个感性的理解方式就是把所有 $c=c_i$ 的点作为分割点，可以分割出很多段（不算分割点）。那么除了 $f(i+1,j)+1$ 以外，不会存在一段被劈成两部分的情况。如果存在，我们把这一段的右半部分放入左半部分，很显然一定会少掉一次让右半部分的颜色变成 $c_i$ 的操作，至多会多出一次让左右部分颜色统一的操作，因此答案不会变差。至于 $f(i+1,j)+1$ 情况的存在则是因为：可能这一段里没有点的 $c=c_i$。

因此总复杂度大概为 $O(20 n^2)$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=3e3+10,INF=1e9;
int T,n,a[MAXN],ans;
int f[MAXN][MAXN];
vector<int>occ[MAXN];
void solve(){
	scanf("%d",&n);ans=INF;
	rep(i,1,n){
		occ[i].clear();
		scanf("%d",&a[i]);
	}
	rep(i,1,n){
		occ[a[i]].pb(i); 
	}
	rep(i,1,n){
		rep(j,i,n){
			if(i==j)f[i][j]=0;
			else f[i][j]=INF;
		}
	}
	rep(len,2,n){
		rep(i,1,n){
			int j=i+len-1;if(j>n)break;
			f[i][j]=min(f[i][j],1+f[i+1][j]);
			int sz=occ[a[i]].size();
			int L=lower_bound(occ[a[i]].begin(),occ[a[i]].end(),i)-occ[a[i]].begin();
			rep(R,L+1,sz-1){
				if(occ[a[i]][R]>j)break;
				f[i][j]=min(f[i][j],f[i][occ[a[i]][R]-1]+f[occ[a[i]][R]][j]);
			}
		}
	}
	printf("%d\n",f[1][n]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve(); 
	}

	return 0;
}
```

---

## 作者：August_Light (赞：4)

# Paint 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1572C)

## 写在前面

从模拟赛赛题 [YACS 835](https://iai.sh.cn/problem/835) 来的。

## 题意简述

$t$ 组数据，给定长度为 $n$ 的颜色序列 $a$，每次你可以选择任意长度的连续且颜色相同的一段位置，将其全部变成任意同一种颜色，问你最少总共需要多少次操作才能使得整个序列颜色相同。

保证每一种颜色初始时在序列中最多只有 $p$ 个位置。

$t \le 10^3, \sum n \le 3 \times 10^3, a_i \le n, p = 20$。

## 前置知识

- 区间 DP

## 解法

数据范围小但不完全小，先考虑区间 DP。

设 $f_{l,r}$ 为 $[l,r]$ 变为同一颜色的最小操作数。

然后不会做了。

~~写一个 $O(\frac {n^4} w)$ 的 bitset 优化 DP~~

~~为了方便转移，我们猜出一个结论~~：对于一个区间 $[l,r]$，必定存在一种最优方案使得最终颜色为 $a_r$，也就是说能保住区间端点的颜色。

事实上这是对的：

- $l = r$ 显然成立。
- 如果 $[l,r-1]$ 存在全部变为 $a_r$ 的最优方案，那么成立。
- 如果 $[l,r-1]$ 不存在全部变为 $a_r$ 的最优方案，那么必须花费一步把 $[l,r-1]$ 和 $a_r$ 统一，此时把 $[l,r-1]$ 染成 $a_r$ 即可。

DP：

枚举断点 $k$，如果 $a_k = a_r$，那么说明不需要额外染色；否则就要额外染一次。

$$f_{l,r} = \begin{cases} 0 & l = r \\ \min\limits_{k=l}^{r-1}(f_{l,k} + f_{k+1,r} + [a_k \ne a_r]) & \text{otherwise} \end{cases}$$

以上方法时间复杂度 $O(n^3)$。

$p = 20$ 的限制还没用上。

当 $a_k \ne a_r$ 时，这种方案肯定没有 $a_k = a_r$ 要好，因为需要一步来统一两个区间的颜色。

所以找到每一个 $a_k = a_r$ 的地方对 $f_{l,k} + f_{k+1,r}$ 取 $\min$ 即可。

不要忘记 $f_{l,r} \gets f_{l,r-1} + 1$ 保个底。

以上方法时间复杂度 $O(n^2 p)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define memset0(a) memset(a, 0, sizeof(a))
using namespace std;
typedef long long LL;

// 省略快读快写的实现

void chkmin(int &x, int y) {
    x = min(x, y);
}

const int MAXN = 3e3 + 5;
const int INF = MAXN;

int n;
int a[MAXN];

int pre[MAXN], lst[MAXN];
int f[MAXN][MAXN]; // f[l][r] = 把 [l,r] 统一为 a[r] 的最小次数

int main() {
    for (int t = read(); t--;) {
        int n = read();
        for (int i = 1; i <= n; i++)
            a[i] = read();

        memset0(pre); memset0(lst);
        for (int i = 1; i <= n; i++) {
            pre[i] = lst[a[i]];
            lst[a[i]] = i;
        }

        for (int len = 1; len <= n; len++) {
            for (int l = 1, r = l + len - 1; r <= n; l++, r++) {
                if (len == 1) {
                    f[l][r] = 0;
                    continue;
                }

                /* 暴力做法：
                f[l][r] = INF;
                for (int k = l; k+1 <= r; k++)
                    chkmin(f[l][r], f[l][k] + f[k+1][r] + (a[k] != a[r]));
                */

                // 正解
                f[l][r] = f[l][r-1] + 1;
                for (int k = pre[r]; k >= l; k = pre[k])
                    chkmin(f[l][r], f[l][k] + f[k+1][r]);
            }
        }
        write(f[1][n], '\n');
    }
    return 0;
}
```


---

## 作者：0xFF (赞：4)

#### 题目简述


------------
给定一个长度为 $n$ 的数字序列，选择其中**连续且相同**的一段将此区间全部变为同一个颜色，询问最少需要几次操作才能使整个数字序列颜色相同。

$t \leq 1000$，$n \leq 3000$，$a_{i}\leq n $ , $\sum n \leq 3000$。

#### 题目分析


------------
一看题目描述发现和洛谷[P4170涂色](https://www.luogu.com.cn/problem/P4170)非常类似，都是用区间动规解决，唯一的不同是本题是一个加强版，不仅要求连续区间还增加了**颜色相同**这一限制。

- 首先设计状态：把每一段相同的颜色的区间看作是同一个已经确定了点，设 $c_i$ 表示第 $i$ 个点的位置，$f(i,j)$ 表示把 $[i,j]$ 这段区间全部涂成 $c_j$ 的最小操作次数。

- 接下来就是进行状态的转移：可以看出来 $[i,j]$ 这个区间肯定是从 $[i+1,j]$ 与 $[i,j-1]$ 这两个区间转移过来的，所以状态转移方程是 $f(i,j) = \min \left\{f_{i+1, j}, f_{i, j-1}\right\}+1$。

- 然后是区间动规的常用操作枚举断点但是三重循环的复杂度明显是不够优秀的，所以可以考虑记录每个点 $i$ 的 $pre_i$ 表示上一个与 $i$ 颜色相同的数字的位置然后把现在正在处理的序列分成两段 $[i,k]$,$[k+1,j]$ 进行转移即 $f(i,j) = \min \left\{f(i, j), f(i, k)+f(k+1, j)\right\}$。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#define INF 2147483648
#define ll long long
using namespace std;
const int N = 3005;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
ll f[N][N];
ll a[N],b[N],pre[N],vis[N];
int main(){
	int T = read();
	while(T--){
		int m = read();
		int cnt = 0;
		for(int i=1;i<=m;i++){
			b[i] = read();
			vis[b[i]] = 0;
		}
		int pos = 1;
		while(pos<=m){
			int j = pos;
			while(j <= m && b[j] == b[pos])
				j++;
			a[++cnt] = b[pos];
			pos = j;
		}
		for(int i=1;i<=cnt;i++){
			pre[i] = 0;
			if(vis[a[i]])	
				pre[i] = vis[a[i]];
			vis[a[i]] = i;
		}
		for(int i=1;i<=cnt;i++){
			for(int j=1;j<=cnt;j++){
				f[i][j] = INF;
			}
		}
		for(int i=1;i<=cnt;i++)
			f[i][i] = f[i+1][i] = 0;
		for(int len = 2;len <= cnt;len++){
			for(int i=1;i<=cnt-len+1;i++){
				int j = i + len - 1;
				f[i][j] = min(f[i][j-1],f[i+1][j]) + 1;
				for(int k=pre[j];k>=i;k=pre[k]){
					f[i][j] = min(f[i][j],f[i][k]+f[k+1][j]);
				}
			}
		}	
		printf("%d\n",f[1][cnt]);
	}
	return 0;
}
```


---

## 作者：ListenSnow (赞：2)

[原题链接](https://codeforces.com/problemset/problem/1572/C "原题链接")

## 题意

给定长度为 $n$ 的颜色序列 $a_i$，每次你可以选择任意长度的**连续且颜色相同**的一段位置，将其全部变成任意同一种颜色，问你最少总共需要多少次操作才能使得整个序列颜色相同。

**限制**： 每一种颜色初始时在序列中最多只有 $20$ 个位置（是该种颜色）。

$n \leq 3000$。

## 思路

考虑将区间 $[l,r]$ 内染成同一种颜色，最暴力的办法就是钦定一种颜色，每次选择一个位置染成该颜色，那么最坏情况下需要染 $r-l$ 次。而如果当前区间的两端颜色相同，那么就可以减少一次染色操作。这启发我们在序列中选取若干个相同颜色的点对，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/t4r3gym7.png)


显然，如果选取的两对点对相交，那么也只能减少一次操作了。

于是题意就转化为了在序列中选取最多不相交的相同颜色点对。可以考虑区间 dp。

令 $f_{l,r}$ 为在 $[l,r]$ 区间内最多选取的点对数量，得到转移方程：

$$f_{l,r}=\max(f_{l+1,r},\max_{a_k=a_r} )f_{i+1,k-1}+1+f_{k,j}$$

这个转移的实质上就是在枚举左端点可以和哪一个点配对，由于一个点可以同时向左和向右配对，所以转移方程里是 $f_{k,j}$ 而不是 $f_{k+1,j}$。

根据题意，区间中满足 $a_k=a_r$ 的位置不超过 $20$，所以这样转移的复杂度是正确的。

## code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3030;
int f[N][N],n,a[N];
vector<int>pos[N];
void chkmax(int &a,int b){if(a<b) a=b;}
void solve()
{
	scanf("%d",&n);for(int i=1;i<=n;i++) pos[i].clear();
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),pos[a[i]].push_back(i),f[i][i]=0;
	for(int len=2;len<=n;len++)
	    for(int l=1,r=l+len-1;r<=n;l++,r++)
	    {
	    	f[l][r]=f[l+1][r];
	    	for(auto k:pos[a[l]])
	    	{
	    		if(k<=l) continue;if(k>r) break;
	    		chkmax(f[l][r],f[l+1][k-1]+1+f[k][r]);
	    		//f[k][r]而不是f[k+1][r]，因为可以同时优化l,k,r 
			}
		}
	printf("%d\n",n-1-f[1][n]);
}
int main()
{
	int T;scanf("%d",&T);while(T--) solve();
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2700}$
---
### 解题思路：

完全不能理解如何直接想到正解，那就一步一步来吧。

在进行具体做题之前，将所有相同颜色段缩成一个会有利于想题，直接代码中实不实现就随意了。

首先是一个一眼就能看出来的朴素 $\text{DP}$，$f_{i,j,k}$ 表示把 $[i,j]$ 染色成 $k$ 的最小代价，转移就是枚举一个中间点和两边的颜色算个染色贡献。复杂度是多少方都懒得算，正确性保证了就行。

---
接下来的一步也是容易发现的，当固定 $i,j$ 的时候，所有的 $k$ 中 $f_{i,j,k}$ 取值最大和最小的差值不超过 $1$，超过了就用 $1$ 的代价整体染色一次就行。

优化过后的转移方程为 $f_{i,j,k}=\min_{l=j}^k{f_{i,l,k}+f_{l,j,k}}$。针对这个转移方程，可以发现连续段越长被优化的可能性就越大，因为任意的一个连续段都不劣于拆开的若干段。

发现此时制约复杂度的最大难题在于状态，而区间 $[i,j]$ 又很难被优化，所以就将注意力放在染成的颜色上，而直接省去颜色又指向了将颜色取出其最特殊的两个代表，两端颜色上。

此处首先可以发现将整个颜色染成两端任意的一种颜色的代价一定是相同的，且一定是所有颜色的两种取值中较小的那一种。证明比较简单，不赘述。

不那么一眼的部分在于不同的颜色去更新大区间颜色时是否会造成转移错误的情况。此处可以用归纳法进行证明，此处只给出一个证明思路。同时注意到两端对称，以下都以将区间染色右端的颜色为例。

奠基过程考虑最大的一个区间 $[1,n]$，和所有区间一样，一定存在一种方案使得所有的位置染色成 $c_n$，且使用的操作次数最少。

归纳过程，需要证明对于任意一个区间，即使认为所有的 $c_j\neq c_l$ 的位置上都有 $c_l$ 是较多转移次数的那一个位置，也不会影响最终的答案。此时可以写出相应的转移方程 $f_{i,j}=\min_{l=i}^j f_{i,l}+f_{l+1,j}+1-[c_j=c_l]$。

这其中很清晰地分为两个部分，$c_j=c_l$ 的位置不用考虑，反正这一个部分在一开始就是这样的，对于 $c_j\neq c_l$ 的位置，结合之前长区间更优的结论，可以将所有的不等情况直接放到 $f_{i,j-1}+f_{j,j}+1$，也就是 $f_{i,j-1}+1$ 考虑。而在这种情况下问题就非常明了了，如果 $f_{i,j-1,c_j}$ 确实是较小的一个，则在它的区间之内一定有 $c_j$ 颜色存在，而此时用内部的更新一定不劣。

由此就得到最终解法，由于每一个颜色的位置不算很多，记录下每一种颜色的所有位置就能快速求解了。最后的总复杂度为 $O(n^2)$。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=3005;
int T,n,a[MAXN],pre[MAXN],u[MAXN],f[MAXN][MAXN];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d\n",&n);
		for(int i=1;i<=n;i++)pre[i]=u[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			pre[i]=u[a[i]];
			u[a[i]]=i;
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		if(i!=j)f[i][j]=1000000000;
		for(int len=2;len<=n;len++){
			for(int i=1;i<=n-len+1;i++){
				int j=i+len-1;
				f[i][j]=f[i][j-1]+1;
				for(int l=pre[j];l>=i;l=pre[l])
				f[i][j]=min(f[i][j],f[i][l]+f[l+1][j]);
			}
		}
		printf("%d\n",f[1][n]);
	}
	return 0;
}
```


---

## 作者：Kingna (赞：1)

这道题是由两种方法的。
## 方法一
定义 $dp_{i,j}$ 表示将区间 $[l,r]$ 全部染成 $a_r$ 的最小操作次数。

$dp_{i,j}$ 转移有三种情况：

* 将区间 $[l,r-1]$ 全部染成相同颜色 $a_{r-1}$，花费 $dp_{l,r-1}$。再将 $[l,r-1]$ 全部染成 $a_r$，花费 $1$ 次操作。故 $dp_{i,j}=\min\{dp_{i,j},dp_{i,j-1}+1\}$。

* 将区间 $[l+1,r]$ 全部染成 $a_{r}$，花费 $dp_{l+1,r}$。再将 $[l,l]$ 染成 $a_r$，花费 $1$ 次操作。故 $dp_{i,j}=\min\{dp_{i,j},dp_{i+1,j}+1\}$。

* 将区间 $[l,r]$ 分为 $[l,k]$ 和 $[k+1,r]$ 两半，且 $a_k=a_r$。那么我们可以把 $[l,k]$ 全部染成 $a_k$，$[k+1,r]$ 全部染成 $a_r$，可以使得最后 $[l,r]$ 全部被染成 $a_r$。故 $dp_{i,j}=\min\{dp_{i,j},dp_{i,k}+dp_{k+1,j}\}$。  

复杂度 $O(n^3)$，需要优化。

我们观察题面会发现限制： **每一种颜色初始时在序列中最多只有 20 个位置（是该种颜色）**。

所以我们满足 $a_k=a_r$ 的 $k$ 最多 $20$ 个。我们记录 $pre_i$ 数组，表示 $i$ 前面第一个和 $i$ 颜色相同的位置。于是枚举 $k$ 是只需要利用 $pre$ 数组疯狂前跳就行。

复杂度 $O(20\times n^2)$。卡卡就过。

注意事项：千万不要 memset 数组，每次循环清理到 $n$ 即可。

```c++
// 997ms，可能需要多交几遍卡卡常
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3005;

int T, n, a[N], dp[N][N], vis[N], pre[N]; 

signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = vis[i] = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[a[i]]) pre[i] = 0;
			else pre[i] = vis[a[i]];
			vis[a[i]] = i;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) dp[i][j] = 0;
				else dp[i][j] = 1e9;
			}
		}
		for (int len = 2; len <= n; len++) {
			for (int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
				for (int k = j; k; k = pre[k]) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
		cout << dp[1][n] << endl;
	}
}
```
## 方法二
有一个显然的合并方式，操作次数 $n-1$。我们在此基础上考虑最大可以优化的次数。如果两个相同颜色 $i,j$ 在同一次操作内合并，答案会优化掉 $1$。

则定义 $dp_{i,j}$ 表示区间 $[i,j]$ 最大可以优化次数。答案则为 $n-1-dp_{i,j}$。

转移即为 $dp_{i,j}=\max\{dp_{i,j-1},dp_{i,k}+dp_{k+1,j-1}+1\}$，且 $a_k=a_j$。

```c++
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3005;

int T, n, a[N], dp[N][N], vis[N], pre[N]; 

signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = vis[i] = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[a[i]]) pre[i] = 0;
			else pre[i] = vis[a[i]];
			vis[a[i]] = i;
		}
		for (int i = 1; i <= n; i++) dp[i][i] = 0;
		for (int len = 2; len <= n; len++) {
			for (int i = 1; i + len - 1 <= n; i++) {
				int j = i + len - 1;
				dp[i][j] = dp[i][j - 1];
				for (int k = pre[j]; k >= i; k = pre[k]) dp[i][j] = max(dp[i][j], dp[i][k] + 1 + dp[k + 1][j - 1]);
			}
		}
		cout << n - 1 - dp[1][n] << endl;
	}
}
```

---

## 作者：pref_ctrl27 (赞：1)

[$\mathcal Link$](https://www.luogu.com.cn/problem/CF1572C)

一个很有意思的题。

显然，每次操作我们会选择将一段染成其相邻段的颜色。我们称这一过程为合并。最坏情况下，需要 $n-1$ 次合并。

试着计算染色会减少多少代价。

考虑有多少个点未被合并，则这些点颜色相同，且将序列分割为若干段。显然，这会省下点个数 $-1$ 的代价（因为最坏情况下会有一个点未被合并）。

对于所有向未染色合并的块，考察每一段内的情况，同样分析形成该块时有多少点未被合并，仍然会减少点数 $-1$ 的代价，然后继续考虑下一层……

设 $f(i,j)$ 表示将 $[i,j]$ 合并成一个块省下的代价最多为多少。

考虑 $i$ 是否会被合并，不会就是 $f(i,i)+f(i+1,j)$，会的话考虑是否存在下一个被省下的点数，不存在就是 $f(i+1,j)$，存在的话设为 $k$，答案为 $f(i+1,k-1)+f(k,j)+1$。

由于同种颜色最多 $20$ 个所以复杂度为 $\mathcal O(kn^2)$，$k=20$。


```cpp
#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

#define LOG(FMT...) // fprintf(stderr, FMT)

const int N=3005;

int a[N], dp[N][N], t[N], nxt[N];

int main(){
	int T; scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		for(int i=0;i<=n;++i) t[i]=0, nxt[i]=0;

		for(int i=1;i<=n;++i) scanf("%d", a+i), nxt[t[a[i]]]=i, t[a[i]]=i;
		for(int i=1;i<=n;++i) if(nxt[i]==0) nxt[i]=n+1;
		
		for(int i=1;i<=n;++i) LOG("%d ", nxt[i]);
		LOG("\n");

		for(int l=1;l<=n;++l){
			for(int i=1;i+l<=n;++i){
				int j=i+l;
				dp[i][j]=dp[i+1][j];
				int k=nxt[i];
				while(k<=j){
					dp[i][j]=max(dp[i][j], dp[i+1][k-1]+dp[k][j]+1);
					k=nxt[k];
				}
			}
		}
		printf("%d\n", n-1-dp[1][n]);
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

质疑：这有 CF 2700？？？？？？？？？？

upd：转移方程代码对了但是式子写错了（

## 思路

区间 dp。令 $dp_{i,j}$ 表示把 $i\sim j$ 染成 $c_j$ 的方案（$c_i$ 也可以）。为什么这样可以做呢？我们假设 $i \sim j-1$ 染成的不是 $c_j$ 那么其实我们把左边染成 $c_j$ 和把 $c_j$ 染成左边是等价的。

所以也不难理解答案就是 $dp_{1,n}$ 了。

然后考虑转移：要么是 $i\sim j-1$ 染成了同一个颜色然后需要全部变成 $j$ 的颜色，要么是 $i+1 \sim j$ 染成了同一个颜色然后需要处理 $i$。因此第一个方程是：

$$dp_{i,j}=\min\{dp_{i+1,j},dp_{i,j-1}\}+1$$

而我们还有一种情况就是在前面某个位置 $k$ 有 $c_k=c_j$，那么我们可以把 $i\sim k$ 染成同一种颜色，$k+1 \sim j$ 染成同一种颜色。这种方案不需要额外步数。

$$dp_{i,j}=\min_{k\in[i,j]\land c_k=c_j} (dp_{i,k}+dp_{k+1,j})$$

那么这里发现暴力枚举 $k$ 是 $n^3$ 的，会 TLE，所以预处理一个数组 $pre$，$pre_i$ 表示 $i$ 前面第一个和 $i$ 相同颜色的点的位置。这个预处理可以开桶扫一遍，然后每次枚举 $k$ 就只需要向前跳了，容易发现最多跳 $20$ 次。

于是复杂度 $O(pn^2)$（$p$ 为最多跳跃次数，为 $20$）。注意我们应该把相同颜色的缩在一个点，否则会出锅。然后我们会发现区间 dp 自带 $0.5$ 倍常数，那个 $20$ 也严重跑不满，所以可以卡过去。

## 代码

```cpp
#include <bits/stdc++.h>
#define _cst const
#define _IfD long long
#define _siz 20
char buf[1<<_siz],buffer[1<<_siz],*p1=buf,*p2=buf,c=' ';
int op1=-1; _cst int op2=(1<<_siz)-1;
inline char gc(){return (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<_siz,stdin)),p1==p2?EOF:*p1++);}
inline void flush(){fwrite(buffer,1,op1+1,stdout),op1=-1;}
inline void pc(_cst char &x){if(op1==op2)flush();buffer[++op1]=x;}
template<typename T>void read(T &w){
	w=0;bool f=1;char ch=gc();
	for(;ch<'0' || ch>'9';ch=gc()) if(ch=='-')f=0;
	for(;'0'<=ch && ch<='9';ch=gc()) w=(w<<1)+(w<<3)+(ch^48);
	w=f?w:-w;
}template<typename T,typename ...Arg>void read(T &w,Arg &...arg){
	read(w); read(arg...);
}template<typename T>void wrt(T x){
  	if(x<0) pc('-'),x=-x;
	if(x>9) wrt(x/10);
	pc(x%10|48);
}template<typename T>void write(T x){
	wrt(x); pc(c);
}template<typename T,typename ...Arg>void write(T x,Arg ...arg){
	write(x); write(arg...);
}
template<typename T>inline T qmax(_cst T &a,_cst T &b){return a>b?a:b;}
template<typename T,typename ...Arg>inline T qmax(_cst T &a,_cst T &b,_cst Arg &...arg){return qmax(a,qmax(b,arg...));}
template<typename T>inline T qmin(_cst T &a,_cst T &b){return a<b?a:b;}
template<typename T,typename ...Arg>inline T qmin(_cst T &a,_cst T &b,_cst Arg &...arg){return qmin(a,qmin(b,arg...));}
template<typename T>inline void qswap(T &a,T &b){a+=b,b=a-b,a-=b;}

using namespace std;

const int MAXN=3005;
int a[MAXN],b[MAXN],pre[MAXN],h[MAXN],m;

int dp[MAXN][MAXN];

void solve(){
	memset(h,0,sizeof(h));m=0;
	int n; read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;){
		int j=i+1;
		while(j<=n && a[j]==a[i]) j++;
		b[++m]=a[i],i=j;
	}
	for(int i=1;i<=m;i++) pre[i]=h[b[i]],h[b[i]]=i;
	
	for(int l=2;l<=m;l++){
		for(int i=1;i+l-1<=m;i++){
			int j=i+l-1;
			dp[i][j]=qmin(dp[i][j-1],dp[i+1][j])+1;
			for(int k=pre[j];k>=i;k=pre[k]) dp[i][j]=qmin(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	}
	
	wrt(dp[1][m]),pc(10);
}

int main(){
	int T; read(T);
	while(T--) solve();
	return flush(),0;
}
```

---

