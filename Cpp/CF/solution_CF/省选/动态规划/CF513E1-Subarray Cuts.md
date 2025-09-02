# Subarray Cuts

## 题目描述

You are given an array of length $ n $ and a number $ k $ . Let's pick $ k $ non-overlapping non-empty subarrays of the initial array. Let $ s_{i} $ be the sum of the $ i $ -th subarray in order from left to right. Compute the maximum value of the following expression:

 $ |s_{1}-s_{2}|+|s_{2}-s_{3}|+...+|s_{k-1}-s_{k}| $ Here subarray is a contiguous part of an array.

## 说明/提示

Consider the first sample test. The optimal solution is obtained if the first subarray contains the first element only, the second subarray spans the next three elements and the last subarray contains the last element only. The sums of these subarrays are $ 5 $ , $ 9 $ and $ 1 $ , correspondingly.

Consider the second sample test. In the optimal solution, the first subarray consists of the first two elements and the second subarray consists of the third element only. Note that the last element does not belong to any subarray in this solution.

## 样例 #1

### 输入

```
5 3
5 2 4 3 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 2
7 4 3 7
```

### 输出

```
8
```

# 题解

## 作者：xtx1092515503 (赞：2)

这题整整调了我一晚上……

首先，我们看到这个式子：

$|s_1-s_2|+|s_2-s_3|+|s_3-s_4|+\dots+|s_{k-1}-s_k|$

我们不如随便把那些绝对值符号拆掉，换成正或负号，这样原式的最大值就是所有拆绝对值的方案中最优的那种。

例如这就是一种合法的方案：

$-(s_1-s_2)+(s_2-s_3)-(s_3-s_4)-\dots+(s_{k-1}-s_k)$

我们再把括号删掉，观察每一项的系数：

$-s_1+2s_2-2s_3+0s_4-\dots+0s_{k-1}-s_k$

发现了什么？

第一项和最后一项的系数必定是$\pm1$，其它项的次数必定是$\pm2$或$0$。且正负号的方案必定是$+,0,\dots,0,-,0,\dots,0,+,0,\dots,0,-,\dots$

即，一个正数，后面跟一堆$0$，然后再来一个负数，然后又是一堆$0$……或者是正负颠倒的情况。

然后就考虑DP。

设$f[i][j][0/1/2][0/1]$表示：

前$i$位，分成$j$段，第$i$个数的符号是：$0\rightarrow-$，$1\rightarrow+$，$2\rightarrow0$，并且上一个非$0$数的符号是$0/1$。

则有：

$\begin{cases}f[i][j][0][0]=max\{f[i-1][j][0][0],f[i-1][j-1][1][1],f[i-1][j-1][2][1]\}-2*num[i]\\f[i][j][1][1]=max\{f[i-1][j][1][1],f[i-1][j-1][0][0],f[i-1][j-1][2][0]\}+2*num[i]\\f[i][j][2][0]=max\{f[i-1][j][2][0],f[i-1][j-1][2][0],f[i-1][j-1][0][0],f[i-1][j][0][0]\}\\f[i][j][2][1]=max\{f[i-1][j][2][1],f[i-1][j-1][2][1],f[i-1][j-1][1][1],f[i-1][j][1][1]\}\end{cases}$


注意，序列中是可以有位置不选的。因此，相邻的两个$2$，可以分成两段，也可以不分。并且，一段连续的$2$，可以被看作是一段$0$，也可以被看作是一段不选的位置，

然后，边界条件为：$f[i][1][0][0]$与$f[i][1][1][1]$是前缀最大子串和。最终结果是$f[i][m-1][0][0]$与$f[i][m-1][1][1]$加上后缀最大子串和的最大值。因为只有$s_1$和$s_m$是$\pm1$，所以要特判掉。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[30100][210][3][2],num[30100],sum[30100],s[2][30100][2],res=0x80808080,ass[30100][2];//0- 1+ 20
int main(){
	scanf("%d%d",&n,&m),memset(f,0x80,sizeof(f));
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	for(int i=1;i<=n;i++)f[i][1][0][0]=max(f[i-1][1][0][0],0)-num[i],f[i][1][1][1]=max(f[i-1][1][1][1],0)+num[i];
	for(int i=1;i<=n;i++)f[i][1][2][0]=max(f[i-1][1][2][0],f[i][1][0][0]),f[i][1][2][1]=max(f[i-1][1][2][1],f[i][1][1][1]);
	for(int i=1;i<=n;i++)for(int j=2;j<m;j++){
		f[i][j][0][0]=max({f[i-1][j][0][0],f[i-1][j-1][1][1],f[i-1][j-1][2][1]})-2*num[i];
		f[i][j][1][1]=max({f[i-1][j][1][1],f[i-1][j-1][0][0],f[i-1][j-1][2][0]})+2*num[i];
		f[i][j][2][0]=max({f[i-1][j][2][0],f[i-1][j-1][2][0],f[i-1][j-1][0][0],f[i-1][j][0][0]});
		f[i][j][2][1]=max({f[i-1][j][2][1],f[i-1][j-1][2][1],f[i-1][j-1][1][1],f[i-1][j][1][1]});
	}
	for(int i=n;i>=1;i--)ass[i][0]=max(ass[i+1][0],0)-num[i],ass[i][1]=max(ass[i+1][1],0)+num[i];
	for(int i=m-1;i<n;i++){
		res=max(res,max(f[i][m-1][0][0],f[i][m-1][2][0])+ass[i+1][1]);
		res=max(res,max(f[i][m-1][1][1],f[i][m-1][2][1])+ass[i+1][0]);
	}
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：ty_mxzhn (赞：0)

什么货梯。

考虑把 $|s_i-s_{i+1}|$ 拆成 $\max(s_i-s_{i+1},s_{i+1}-s_{i})$。此时贡献只会算少不会算多。

问题变成每个点可以选择当做折线的峰也可以当做折线的谷，问你贡献最值。

设计 $f_{i,j,0\sim 3}$ 表示当前折线的状态，转移时直接考虑怎么变化状态。

转移考虑延续上个段还是新开一段，对于下降段和上升段直接考虑要不要单出一个点作为一段，对于峰谷段直接考虑延续或者新开并来到上升和下降段，或者跳过上升和下降段直接来到下一个峰谷段。

但是 $1$ 和 $k$ 要特判，细节较多。

[推歌](https://music.163.com/song?id=487379581&uct2=U2FsdGVkX1/14z0OiKhl7NxzY4Qn0Qsc3hrrxMgtqno=)。

---

## 作者：L_zaa_L (赞：0)

一般我们做题遇到绝对值都会考虑把他给拆掉，于是考虑将这个给拆掉，拆完后可能会剩下这样的：$s_1-s_2+s_2-s_3-s_3+s_4-s_4+s_5+s_5-s_6\cdots -s_{k-2}+s_{k-1}-s_{k-1}+s_k=s_1-2s_3+2s_5-2s_6+\cdots +s_k$

我们发现除了 $s_1$ 和 $s_k$ 系数可以为 $\pm 1$，其他的系数不是 $\pm 2$ 就是 $0$。而且除去 $0$ 之后，$+$ 与 $+$ 不能连在一起，$-$ 和 $-$ 也不能连在一起，$s_1$ 和 $s_k$ 也要算在条件内。

于是我们可以设 $dp_{i,j,0/1/2,0/1}$ 表示前 $i$ 个数字，划分到了第 $j$ 组，当前组的系数是正的，负的还是 $0$，出去零以后，往前第一个组系数是正的还是负的。

于是可以列出以下的式子，式子比较简单，不再做什么解释：

$$\begin{cases}dp_{i,j,0,0}=\max(dp_{i-1,j,0,0},dp_{i-1,j-1,1,1},dp_{i-1,j-1,2,1})+a_i+[j\not=1\land j\not=k]a_i\\dp_{i,j,1,1}=\max(dp_{i-1,j,1,1},dp_{i-1,j-1,0,0},dp_{i-1,j-1,2,0})-a_i-[j\not=1\land j\not=k]a_i\\dp_{i,j,2,0}=\max({dp_{i-1,j,2,0},dp_{i-1,j-1,2,0},dp_{i-1,j,0,0},dp_{i-1,j-1,0,0}}))&(j\not=1)\\dp_{i,j,2,1}=\max(dp_{i-1,j,2,1},dp_{i-1,j-1,2,1},dp_{i-1,j,1,1},dp_{i-1,j-1,1,1})&(j\not=1)\end{cases}$$

然后发现问题是有些数可以不选，对于在中间的那些不选的数，我们可以直接划分在系数 $0$ 组里面，剩下的就是前面的和后面的，前面的在设初始值就可以解决了，后面在求答案的时候把 $1\sim n$ 的 $dp_{i,k,1,1}$ 和 $dp_{i,k,0,0}$ 求最大值就可以解决。

然后就是绝对值的事，拆完之后一定会是正数，如果是负数就肯定不优，时间复杂度 $O(nk)$。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
//#include <immintrin.h>
//#include <emmintrin.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5,base=999983,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int n,k;
int dp[30005][205][3][2],a[N]; 
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read(),k=read();
	For(i,1,n) a[i]=read();
	For(i,0,n) For(j,0,k) For(t,0,2) For(k,0,1) dp[i][j][t][k]=-1e9;
	For(i,1,n){
		For(j,1,min(i,k)){
			dp[i][j][0][0]=max({dp[i-1][j][0][0],dp[i-1][j-1][1][1],dp[i-1][j-1][2][1]})+a[i]+(j!=1&&j!=k)*a[i];
			dp[i][j][1][1]=max({dp[i-1][j][1][1],dp[i-1][j-1][0][0],dp[i-1][j-1][2][0]})-a[i]-(j!=1&&j!=k)*a[i];
			if(j==1) 
				dp[i][1][0][0]=max(dp[i][1][0][0],a[i]),
				dp[i][1][1][1]=max(dp[i][1][1][1],-a[i]);
			if(j!=1)dp[i][j][2][0]=max({dp[i-1][j][2][0],dp[i-1][j-1][2][0],dp[i-1][j][0][0],dp[i-1][j-1][0][0]});
			if(j!=1)dp[i][j][2][1]=max({dp[i-1][j][2][1],dp[i-1][j-1][2][1],dp[i-1][j][1][1],dp[i-1][j-1][1][1]});
//			printf("%lld %lld\n",i,j);
		}
		
	}
	int ans=0;
	For(i,1,n)ans=max({ans,dp[i][k][1][1],dp[i][k][0][0]});
	printf("%lld\n",ans);
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：Galois_Field_1048576 (赞：0)

重要观察：如果把式
$$
\sum_{k = 1}^{n - 1} |s_{k+1}-s_k|
$$
中的绝对值展开，则得到的
$$
\sum_{k = 1}^{n} c_k s_k
$$
满足：$c_1, c_n \in \{\pm 1\}, c_k \in \{2, 0, -2\}~(k = 2, \dots, n - 1)$。

这样我们发现除了 $2$ 和 $-2$ 不能接替出现，也不能像 $2~0~0~2$ 这样隔着若干个 $0$ 出现，所以我们对于一段，事实上有如下四种情况：

* 该段的 $c$ 值为 $-2$；
* 该段的 $c$ 值为 $2$；
* 该段的 $c$ 值为 $0$ 而前面的第一个 $c \ne 0$ 为 $-2$；
* 该段的 $c$ 值为 $0$ 而前面的第一个 $c \ne 0$ 为 $2$。

于是，我们可以直接设
$$
\mathrm{dp}(i, j, T)
$$
为前 $i$ 个数，分成 $j$ 段，其中最后一段符合第 $T$ 个情况。直接转移即可。

代码细节较多，但可以将转移压缩为一个 $64$ 位二进制数，这里得到的结果为：
$$
\mathrm{0x}:\rm FD75\ B931\ 0B53\ F071,
$$
其中其第 $16x+4y \sim 16x+4y+3$ 位的二进制值为 $abcd$，则我们在 $\mathrm{dp}(i, j, x)$ 转移到 $\mathrm{dp}(i - 1, A, B)$ 时：

* 若 $d = 0$，则转移不可行，否则转移规则见下；
* $A = j - c$；
* $B = 2a + b$。

这样，我们可以写出一个较为简洁的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 30000 + 5;

int n, m;
int f[N][210][4], a[N], sum[N], s[2][N][2];
int res = -1e9, rear[N][2];

// neg 0
// pos 1
// zero 2

int main() {
    cin >> n >> m;
    fill(&f[0][0][0], &f[0][0][0] + sizeof(f) / sizeof(int), -1e9);

    for (int i = 1; i <= n; i++) cin >> a[i];

    // 第 1 段
    for (int i = 1; i <= n; i++)
        f[i][1][0] = max(f[i - 1][1][0], 0) - a[i],
        f[i][1][1] = max(f[i - 1][1][1], 0) + a[i],
        f[i][1][2] = max(f[i - 1][1][2], f[i][1][0]),
        f[i][1][3] = max(f[i - 1][1][3], f[i][1][1]);

    int bias[] = {-2, 2, 0, 0};
    const unsigned long long magic = 0xfd75'b931'0b53'f071;

    // 第 [2, last) 段
    for (int i = 1; i <= n; i++)
        for (int j = 2; j < m; j++)
            for (int k = 0; k < 4; k++) {
                f[i][j][k] = f[i - 1][j][k];
                for (long long l = k << 4; l < ((k + 1) << 4); l += 4)
                    if ((magic >> l) & 1)
                        f[i][j][k] = max(f[i][j][k],
                                         f[i - 1][j - ((magic >> (l + 1)) & 1)]
                                          [(magic >> (l + 2)) & 3]);
                f[i][j][k] += bias[k] * a[i];
            };

    // 计算后缀数组 rear
    for (int i = n; i >= 1; i--)
        rear[i][0] = max(rear[i + 1][0], 0) - a[i],
        rear[i][1] = max(rear[i + 1][1], 0) + a[i];

    // 枚举 last
    for (int i = m - 1; i < n; i++) {
        res = max({res, max(f[i][m - 1][0], f[i][m - 1][2]) + rear[i + 1][1],
                   max(f[i][m - 1][1], f[i][m - 1][3]) + rear[i + 1][0]});
    }

    cout << res << endl;

    return 0;
}
```

这就是 magic 带给我的自信。

---

