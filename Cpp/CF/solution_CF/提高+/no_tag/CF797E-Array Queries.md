# Array Queries

## 题目描述

 $ a $ is an array of $ n $ positive integers, all of which are not greater than $ n $ .

You have to process $ q $ queries to this array. Each query is represented by two numbers $ p $ and $ k $ . Several operations are performed in each query; each operation changes $ p $ to $ p+a_{p}+k $ . There operations are applied until $ p $ becomes greater than $ n $ . The answer to the query is the number of performed operations.

## 说明/提示

Consider first example:

In first query after first operation $ p=3 $ , after second operation $ p=5 $ .

In next two queries $ p $ is greater than $ n $ after the first operation.

## 样例 #1

### 输入

```
3
1 1 1
3
1 1
2 1
3 1
```

### 输出

```
2
1
1
```

# 题解

## 作者：He_Ren (赞：47)

这道题很像一道数据结构题，思路很容易被带偏

但是想想就会发现没有适合的结构

所以先写暴力

发现有两种写法：

1. 直接dp，预处理所有$p$和$k$的答案
2. 每次询问暴力模拟

**要大胆想，不要因为 “算法显然太慢” 或 “算法显然有错” 而放弃对这种算法的思考（因为这通常不会花太长时间）**

算法1需要$O(nk)的预处理，而且空间不够$

算法2，每次询问是$O(\frac{n}{k})$的

**看看每种算法对于什么数据比较慢**

发现第一种算法没有办法处理$k$很大的数据，而算法2没办法处理$k$比较小的情况

**所以就可以综合一下这两种算法**

然后做法就比较显然了

采用算法1预处理$k\leq \sqrt n$的情况，每次询问，如果$k>\sqrt n$就暴力模拟，否则用预处理的值

这样的复杂度是$O(n\sqrt n)$的，$n\leq 10^5$的数据可以跑过

**好的暴力思路或许可以改成正解**

```cpp
#include<cstdio>
#include<cmath>
const int MAXN = 1e5 + 5;
const int MAXM = 316 + 5;

int a[MAXN];
int dp[MAXN][MAXM+5];

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	
	int m=sqrt(n);
	for(int i=n; i>=1; --i)
		for(int j=1; j<=m; ++j)
		{
			if(i+a[i]+j>n) dp[i][j]=1;
			else dp[i][j] = dp[i+a[i]+j][j]+1;
		}
	
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int p,k;
		scanf("%d%d",&p,&k);
		if(k<=m) printf("%d\n",dp[p][k]);
		else
		{
			int ans=0;
			while(p<=n)
			{
				++ans;
				p+=a[p]+k;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：EnofTaiPeople (赞：10)

所谓根号分治，就是暴力预处理。

本题中，很明显当 $k>\sqrt{n}$ 时，$ans<\sqrt{n}$，遇到这些询问暴力做就好了；当 $k\le\sqrt{n}$ 时，暴力预处理就好了，总时间复杂度为 $O((n+q)\sqrt{n})$，空间复杂度为 $n\sqrt{n}$ 达到了时空平衡。

真是一个神奇的操作！
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
char buf[N+5],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x,f=1;for(c=gc;c<48;c=gc)if(c=='-')f=-f;
    for(x=0;c>47;x=x*10+(48^c),c=gc);return x*f;
}
int a[N],f[325][N],n,p,k,Q,q;
int main(){
    int i,j;q=sqrt(n=read());
    for(i=1;i<=n;++i)a[i]=read();Q=read();
    for(i=1;i<=q;++i)
        for(j=n;j;--j)
            f[i][j]=(j+a[j]+i>n)?1:f[i][j+a[j]+i]+1;
    while(Q--){
        p=read(),k=read();
        if(k>q){
            for(i=0,j=p;j<=n;j+=a[j]+k,++i);
            printf("%d\n",i);
        }else printf("%d\n",f[k][p]);
    }return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF797E)
## 思路
诈骗题，这题启示我们很多 $\verb!CF!$ 上的题都是暴力。

首先，我们会想到一种暴力按题意模拟的方法，就是每次把 $p$ 变成 $p+a_p+k$，但是，这个东西的时间复杂度是 $O(n^2)$ 的。

于是我们考虑稍微优化这个方法，设 $f_{i,j}$ 表示当 $p$ 为 $i$，$k$ 为 $j$ 时的次数，但是这个东西的复杂度甚至更劣，用记忆化搜索实现依然要花费 $O(n^2)$ 的时空复杂度。

但是，这两个做法合起来居然就是正解。

为什么呢，因为若 $k \le \sqrt{n}$，我们显然可以用第二种暴力 $O(n \sqrt{n})$ 预处理出答案。而若 $k > \sqrt{n}$，每次 $p$ 至少变大 $\sqrt{n}$，所以时间复杂度 $O(\sqrt{n})$。

然后，你就发现这个题成功被搞过了，时间复杂度为 $O(n \sqrt{n}+q \sqrt{n})$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;
int const M=370;
int f[N][M],n,k,a[N];
inline int dfs(int p,int k){
	if (f[p][k]) return f[p][k];//记忆化，我第一次交的时候忘记记忆化了，然后 TLE 了
	if (p+a[p]+k>n) return f[p][k]=1;
	return f[p][k]=dfs(p+a[p]+k,k)+1;
}
inline int solve(int p,int k){
	if (p+a[p]+k>n) return 1;
	return solve(p+a[p]+k,k)+1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	int limit=sqrt(n);
	for (int i=1;i<=n;++i)
	    for (int j=1;j<=limit;++j)
	        dfs(i,j);
	int q;cin>>q;
	while (q--){
		int p,k;cin>>p>>k;
		if (k<=limit) cout<<f[p][k]<<'\n';
		else cout<<solve(p,k)<<'\n';
	}
	return 0;
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给出一个长度为 $n$ 的序列 $\left \{ a_n \right \} $，$m$ 次询问，每次询问给出 $p,k$,不断执行操作 $p\gets p+a_p+k$，问至少需要多少次才能使 $p$ 大于 $n$。

#### 思路分析


------------
若 $k = 1$，暴力 $\Theta(n^2)$ 肯定不能通过。

考虑根号分治。

若 $k > \sqrt{n}$，直接枚举即可，复杂度 $\Theta(n \log n)$。

若 $k \le \sqrt{n}$，$\Theta(n\log n)$ 预处理答案数组即可。

记录 `ans[i][j]` 表示当 $p=i$ 且 $k=j$ 时最少操作几次可以满足条件。

若 $i + a[i] +j > n$ 则 `ans[i][j] = 1`。

否则 `ans[i][j] = ans[i+a[i]+j][j] + 1`。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int N = 1e5 + 10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int ans[N][320],a[N];
signed main(){
	int n = read();
	for(int i=1;i<=n;i++) a[i] = read();
	int pos = sqrt(n);
	for(int i=n;i>=1;i--){
		for(int j=1;j<=pos;j++){
			if(i + a[i] + j > n) ans[i][j] = 1;
			else ans[i][j] = ans[i + a[i] + j][j] + 1;
		}
	}
	int m = read();
	for(int i=1;i<=m;i++){
		int p = read() , k = read();
		if(ans[p][k] != 0) printf("%lld\n",ans[p][k]);
		else {
			int ans = 0;
			while(p <= n){
				ans++;
				p = p + a[p] + k;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：出言不逊王子 (赞：2)

我们发现每次 $p$ 的增加值会改变，而且毫无规律。

我们考虑 $k\le 100$ 的做法。

我们想到了动态规划。

我们想到了用 $f_{p,k}$ 表示所以 $p$ 和 $k$ 的答案。

时间复杂度是 $O(n\times k)$。

我们考虑 $k \ge 1000$ 的做法。

我们想到了暴力。

一次询问的复杂度是 $O(\frac nk)$。

所有询问加起来就是 $O(\frac {nm}k)$。

我们考虑啥时候这俩能取得一个平衡。

因为 $nm$ 同阶，所以我们考虑方程 $n\times k=\frac{n\times n}k$。

我们得到了 $k=\sqrt n$。

所以 $k \le \sqrt n$ 时用预处理出来的答案，否则直接暴力。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,m,k,a[N],f[N][501],krubb;//f[i][j]为p=i,k=j时的答案 
int main(){
	n=read();fs(i,1,n,1) a[i]=read();krubb=sqrt(n);
	ft(i,n,1,-1){
		fs(j,1,krubb,1){
			if(i+j+a[i]>n) f[i][j]=1;
			else f[i][j]=f[i+a[i]+j][j]+1; 
		}
	} 
	m=read();
	while(m--){
		int p=read(),k=read();
		if(k>krubb){
			int res=0;
			while(p<=n) res++,p+=(a[p]+k); 
			printf("%d\n",res);
		}else printf("%d\n",f[p][k]);
	}
	return 0;
}//本来想在这里塞一句歌词，但是不知道选哪个了
```

---

## 作者：parallet (赞：2)

如今根号分治横行的时代，我也写一篇。

先设一个阈值 $B$。

- 对于 $k\ge B$，我们暴力跳，每次至少会跳 $B$ 个单位长度，则复杂度为 $\Theta(\frac{n}{B})$。

- 对于 $k<B$，我们预处理出所有 $k,p$ 的答案。

	这样可以上一个非常显然的递推。设 $f_{i,j}$ 表示当 $p=i$，$k=j$ 时需要操作的次数。显然 $f_{i,j}=f_{i+a_i+j,j}+1$。
    
   递推的复杂度的同样是 $\Theta(nB)$ 的。
   
显然，当阈值 $B$ 取 $\sqrt n$ 时，复杂度最优，且为 $\Theta(n\sqrt n)$，可以通过本题。

代码同样十分好写：

```cpp
int main()
{
	n=read();
	rep(i,1,n) a[i]=read();
	int B=sqrt(n);
	rev(i,n,1) rep(j,1,B) if(i+a[i]+j>n) f[i][j]=1;else f[i][j]=f[i+a[i]+j][j]+1;
	m=read();
	while(m--)
	{
		int p=read(),k=read();
		if(k<=B) printf("%d\n",f[p][k]);
		else
		{
			int tot=0;//
			while(p<=n) p=p+a[p]+k,++tot;
			printf("%d\n",tot);
		}
	}
	return 0;
}
```


---

## 作者：ImALAS (赞：2)

[传送门QAQ](https://www.luogu.com.cn/problem/CF797E)

## Analysis

这道题看上去就是要用数据结构的样子，然而线段树什么的完全没法维护，因为 $k$ 是变化的。

遇到这种情况，最常见的思路就是往分块或者根号分治上想。

顺着这个思路，不难发现，当 $k \ge \sqrt{n}$ 时，暴力操作的时间复杂度为单次 $O(\sqrt{n})$。

再看一眼数据规模，可以承受住 $O(n\sqrt{n})$ 的时空复杂度。

这时整道题的思路就很明显了，开一个数组，$O(n\sqrt{n})$ 地预处理一下 $k \lt \sqrt{n}$ 的情况就好啦。

时间复杂度 $O((n+q)\sqrt{n})$。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 405;
int f[maxn][maxm],a[maxn],n;
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;++ i)scanf("%d",&a[i]);
	for(int k = 1;k < maxm;++ k) {
		for(int i = n;i;-- i) {
			if(i + a[i] + k > n)f[i][k] = 1;
			else f[i][k] = f[i + a[i] + k][k] + 1;
		}
	}
	int p,k,Q;
	scanf("%d",&Q);
	while(Q --) {
		scanf("%d%d",&p,&k);
		if(k >= maxm) {
			int ans = 0;
			for(;p <= n;p += a[p] + k)++ ans;
			printf("%d\n",ans);
		}
		else printf("%d\n",f[p][k]);
	}
	return 0;
}
```

---

## 作者：RiceFruit (赞：1)

# 题目描述
给你 $n$ 个数 $a_1,a_2,\cdots a_n$，对于每次询问有一个 $p$ 和 $k$，让你求出每次都是 $p$ 变成 $p+a_p+k$，知道 $p>n$ 时需要的次数。
# 算法思路
我们考虑根号分治，当 $k$ 是大于 $\sqrt{n}$ 的时候，显然不会增加太多次，最多只有 $\sqrt{n}$ 次，而当 $k$ 是小于 $\sqrt{n}$ 的时候，我们可以预处理一个 $f_{i,j}$，表示输入为 $i$ 和 $j$ 时的答案，而且 $j$ 是小于 $\sqrt{n}$。

接下来我们考虑 $f_{i,j}$ 怎么求。首先，我们可以固定一个 $j$，然后倒序枚举每一个 $i$，当 $i+a_i+j>n$ 的时候，则说明可以一次到达，直接将 $f_{i,j}$ 赋值成 $1$，而当 $i+a_i+j<=n$ 的时候，我们直接将它赋值成 $f_{i+a_i+j,j}+1$，因为我们是倒序枚举的 $i$，所以前面的一定是已经有值的，于是本题就做完了。
# 代码实现
直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,B=450;
inline int read();
int n,q,b;
int f[N][B];//表示第i个数要加多少次i和j才能>n 
int a[N];
signed main(){ 
	n=read();
	b=sqrt(n);
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int j=1;j<=b;j++){
		for(int i=n;i>=1;i--){
			if(a[i]+i+j>n)
			{
				f[i][j]=1;
			}
			else
			{
				f[i][j]=f[a[i]+i+j][j]+1;
			}
		}
	}
	q=read();
	while(q--){
		int x=read(),k=read();
		if(k>b){
			int cnt=0,now=x;
			while(now<=n){
				now=now+a[now]+k;
				cnt++;
			}
			printf("%d\n",cnt);
		}
		else{
			printf("%d\n",f[x][k]);
		}
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

---

## 作者：CmsMartin (赞：1)

[更好的阅读体验](http://www.cmsblog.top/archives/cf797earrayqueries)

## 题目描述

[题目传送门1](https://www.luogu.com.cn/problem/CF797E)

[题目传送门2](https://codeforces.com/problemset/problem/797/E)

给定长度为 $n$ 的序列 $a$。$m$ 次询问。

每次询问给出 $p,k$。您要不断地执行操作 $p\gets p+a_p+k$，直到 $p>n$ 为止。询问的答案为操作次数。
$1\le n,q\le 10^5$，$1\le a_i\le n$。

## 思路

### Algorithm1

考虑动态规划。

假设 $dp[i][j]$ 表示当 $p=i,k=j$ 时的答案。

方程显然可以写出来：

$$
dp_{i,j} = \left\{
  \begin{array}{lc}
	1 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ i+a_i+n>n\\
   dp_{i+a_i+n,j}+1  \ \ \ \ \ \ \ otherwise
  \end{array}
\right.
$$

预处理时间复杂度 $O(nk)$，空间复杂度 $O(nk)$。

显然做不了。

### Algorithm2

考虑暴力，每次询问时间复杂度 $O(\frac{n}{k})$。

显然也做不了。

---

我们发现，Algorithm1 在 $k$ 比较小的时候可以 AC， Algorithm2 在
$k$ 比较大的时候可以 AC。

所以我们可以大胆结合，当 $k \le \sqrt n$ 时使用 Algorithm1，当 $k \ge \sqrt n$ 的时候使用 Algorithm2。

这样我们的时间和空间复杂度均变成了 $O(n \sqrt n)$， 可以 AC。

这种思想被称作 **根号分治**。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N , Q , Num[100010] , NN;
int P , K;

int Dp[100010][350];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	NN = sqrt(N);
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}

	for(int i = N; i >= 1; i--) {
		for(int j = 1; j <= NN; j++) {
			if(i + Num[i] + j > N) Dp[i][j] = 1;
			else Dp[i][j] = Dp[i + Num[i] + j][j] + 1;
		}
	}

	cin >> Q;
	while(Q--) {
		cin >> P >> K;
		if(K <= NN) {
			cout << Dp[P][K] << endl;
		}
		else {
			int res = 0;
			while(P <= N) {
				P = P + Num[P] + K;
				res++;
			}
			cout << res << endl;
		}
	}
	return 0;
}
```

---

## 作者：Buried_Dream (赞：1)

## 题意：

给定一个序列 $a$，给定 $T$ 组 $p, k$，每次操作为 $p = p + a_p + k$，问需要操作几次才能使得 $p > n$。

## 思路：

模拟的时间复杂度为 $\mathcal{O}(\frac{n}{k})$，如果全部数据按照模拟会超时。

我们设 $dp_{i,j}$ 当 $p = i, k = j $ 时的答案，空间复杂度为 $O(nk)$，会炸。

我们考虑将两种做法结合起来。

如果 $k = \sqrt n$ 的时候，操作次数为 $\sqrt n$。当 $k > \sqrt n$ 的时候，答案必定会小于 $\sqrt n$。 对于这部分我们直接模拟即可。

对于 $k < \sqrt n$ 的这部分答案来说，我们可以用第二种办法提前预处理出来，询问时直接输出即可。

## Ac code:

```cpp
int dp[maxn >> 1][350], num, a[N];

signed main() {
	int tests = 1;  //tests = read();
	while(tests--) {
		int n = read(); num = sqrt(n);	
		for(int i = 1; i <= n; i++) a[i] = read();
		int T = read();
		for(int i = n; i >= 1; i--) {
			for(int j = 1; j <= num; j++) {
				if(a[i] + i + j > n) dp[i][j] = 1;
				else dp[i][j] = dp[i + a[i] + j][j] + 1;
			}
		}	
		while(T--) {
			int p = read(), k = read();
			if(k <= num) printf("%d\n", dp[p][k]);
			else {
				int js = 0;
				while(p <= n) {
					js++, p = p + a[p] + k;
				} printf("%d\n", js);
			}
		} 
	}
}
```

$$The\ End.$$

---

## 作者：wwlw (赞：1)

[Link](https://www.luogu.com.cn/problem/CF797E)
-----------

### Solution

和弹飞绵羊有点像，所以想这题可能和分块有什么关系。于是想到按值域来分块。

当 $k$ 比较大的时候，容易发现跳的次数就非常少，以至于暴力跳都能过。于是当 $k > \sqrt{n}$ 的时候，不妨就直接暴力地跳。复杂度 $O(n\sqrt{n})$

当 $k$ 比较小的时候，也就是 $k\leq \sqrt{n}$，发现这样的 $k$ 很少，所以可以直接对每个 $k$ 预处理出来从位置 $p$ 跳完需要的步数。容易写出方程
$$f_{p,k}=f_{p+a_p+k,k}+1$$
那么 $O(n\sqrt{n})$ 预处理就可以了，每次查询 $O(1)$。

```cpp
#include<stdio.h>
#include<math.h>
#define N 100007
#define M 321

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

int f[N][M],n,a[N],sz;

int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    sz=(int)(sqrt(n)+0.5);
    for(int i=n;i;i--)
        for(int j=1;j<=sz;j++)
            if(i+a[i]+j>n) f[i][j]=1;
            else f[i][j]=f[i+a[i]+j][j]+1;
    int Q=read();
    while(Q--){
        int p=read(),k=read(),ret=0;
        if(k<=sz) printf("%d\n",f[p][k]);
        else{
            while(p<=n) p+=a[p]+k,++ret;
            printf("%d\n",ret);
        }
    }
}
```

---

## 作者：vacation (赞：1)

刚拿到题目,一看数据范围
The first line contains one integer n n (1<=n<=100000),就知道暴力肯定会TLE,dp则空间不够.那么怎么办呢?我们应该分段暴力.我是因为保险起见,数组几乎开到最大,在k<=400时DP,防止TLE.暴力就直接模拟,这里不做叙述.

------------
DP 如果在步骤1时就超过n,则这需要一步,其余在(I+A[I]+A[J])的基础上加一步继续.


------------
代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int q,a[100001],n,p,k,f[100001][405];//F数组可以开到F[100001][K](K>=300);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    cin>>q;
    for(int i=n;i>=1;i--)
        for(int j=1;j<=400;j++)
        {
            if(i+a[i]+j>n) f[i][j]=1;
            else f[i][j]=f[i+a[i]+j][j]+1;
        }//在设定的400前DP
    for (int i=1;i<=q;i++)
    {
        cin>>p>>k;
        if(k<400)
        {
            cout<<f[p][k]<<endl;
            continue;//用DP好的数据直接输出
        }
        int tot=0;
        while (p<=n)
        {
            p+=a[p]+k;tot++;
        }//暴力,一步步累加直到达到条件
        cout<<tot<<endl;
    }
    return 0;	 
}
```


---

## 作者：泠小毒 (赞：1)

# Array Queries
给定一个序列，有q次询问，每次询问给定p和k，重复执行操作p=p+a[p]+k，直到p大于n，询问的答案为操作次数
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190509/)
## 解法
一看数据范围，如果纯模拟是n方的，过不了

然后发现，过不了是因为k太小，所以把k小的打表预处理出来就ok了a.a

那这个小的设定在多少呢，sqrt(n)左右就可以了

总的复杂度就是n×sqrt(n)了
## ac代码
```cpp
#include<bits/stdc++.h>
#define lim 320
using namespace std;
int n,q,x,y,a[100010],dp[100010][400],ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=n;i>=1;i--)for(int j=1;j<=lim;j++)
    {
        dp[i][j]=1;
        if(i+a[i]+j<=n)dp[i][j]+=dp[i+a[i]+j][j];
    }
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&x,&y);
        if(y<=lim)printf("%d\n",dp[x][y]);
        else
        {
            while(x<=n)ans++,x+=a[x]+y;
            printf("%d\n",ans),ans=0;
        }
    }
    return 0;
}
```

---

## 作者：李柯欣 (赞：0)

题目传送门：[CF797E](https://www.luogu.com.cn/problem/CF797E)。

[更好的阅读感受](https://www.luogu.com.cn/blog/likexin/solution-cf797e)？

### 题目大意：

有一个长为 $n$ 的数列 $a$，$q$ 次询问，每次给出两个数 $p$，$k$，不断将 $p$ 加上 $a_p+k$，问加几次可以使 $p>n$。

### 思路：

这种题一看就是 dp。

我们设 $dp_{i,j}$ 表示当询问为 $i$ 和 $j$ 时的答案。

方程也很好写：

$$dp_{i,j}=\min(dp_{i+a_p+j}+1)$$

并倒着转移。

但是当我们头脑冷静下来看看数据范围：

- $1\le n,q\le 10^5$，$1\le a_i\le n$，$1\le p,k\le n$。

而我们的 dp 是 $O(nk)$ 的时间复杂度，显然不行。

再仔细想一想后发现：

在 $k>\sqrt{n}$ 时，预处理还不如询问时的暴力模拟快。

所以：**在 $k$ 比较大的时候，暴力更合适**。

那么我们就把它分成两部分：$k\le\sqrt{n}$ 和 $k>\sqrt{n}$。

预处理 $k\le\sqrt{n}$ 的情况，$k>\sqrt{n}$ 的情况直接暴力。

时间复杂度达到了优秀的 $O(n\sqrt{n})$。

空间复杂度也是 $O(n\sqrt{n})$。

### 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<bitset>
#include<string>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
#include<map>
#include<set>
//#define int long long
using namespace std;
int dp[100001][501]; 
int a[100001];
signed main(){
	int n,k;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	k=sqrt(n);//k 是根号 n。
	memset(dp,0x3f,sizeof(dp));
	for(int i=n;i;i--){
		for(int j=k;j>=1;j--){//预处理。
			if(i+a[i]+j>n){
				dp[i][j]=1;
			}else{
				dp[i][j]=min(dp[i][j],dp[i+a[i]+j][j]+1);
			}
		}
	}
	int q;
	cin>>q;
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(y<=k){//dp 预处理。
			cout<<dp[x][y]<<endl;
		}else{//暴力。
			int tot=0;
			for(int i=x;i<=n;i+=a[i]+y){
				tot++;
			} 
			cout<<tot<<endl;
		}
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/86708649)。


---

## 作者：IANYEYZ (赞：0)

### 写在前面 ###

感觉不难啊，怀疑恶评\kk。

### 正文 ###

经典根号分治，经典 dp 预处理。

首先根号分治，当 $k > \sqrt{n}$ 时直接暴力，当 $k \le \sqrt{n}$ 时调用之前预处理的东西。

重点讲一下预处理时 dp 的转移。

首先是状态：定义 dp[i][j] 为 $p = i$，$k = j$ 时的答案，其中 $j \le \sqrt{n}$。

考虑怎么转移

dp[i][j] 应该从 dp[i+a[i]+j][j] 转移过来（可以多操作一次），因此外层循环从大到小，内层循环顺序貌似无关

注意特判 $i+a[i]+j > n$。（不能操作力）

所以总的转移方程为 
$$\text{dp[i][j] = } \begin{cases}
dp[i+a[i]+j][j] {\kern{100pt} i+a[i]+j \le n}\\
1 {\kern{169pt} i+a[i]+j > n}\\
\end{cases}$$

代码见下：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int dp[100010][326],a[100010],n,m,k,p;
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
	}
	for(int i = n;i >= 1;i--)
	{
		for(int j = 1;j <= sqrt(n);j++)
		{
			if(i+a[i]+j > n)
			{
				dp[i][j] = 1;
			}
			else
			{
				dp[i][j] = dp[i+a[i]+j][j]+1;
			}
		}
	}
	cin>>m;
	for(int i = 1;i <= m;i++)
	{
		cin>>p>>k;
		if(k > sqrt(n))
		{
			int cnt = 0;
			while(p <= n)
			{
				p = p+a[p]+k;
				cnt++;
			}
			cout<<cnt<<endl;
		}
		else
		{
			cout<<dp[p][k]<<endl;
		}
	}
}
```


---

## 作者：漠寒 (赞：0)

## 分析

根号分治题。

发现 $p$ 是单增的，且每次至少增加 $k$。所以如果 $k$ 很大，我们直接暴力跳很少的次数就能跳出去，如果确定了一个 $k$ 值，我们可以倒序 $O(n)$ 处理出每个位置作为起点需要跳多少次才能跳出。

如果将前后两个综合起来，在 $k$ 大于 $\sqrt{n}$ 时直接暴力跳，次数会小于 $\sqrt{n}$。提前预处理所有小于 $\sqrt{n}$ 的 $k$ 下所有位置作为起点需跳多少次，只需花 $O(n\sqrt{n})$ 的时间即可全部处理，所以总时间最多为 $O((n+m)\sqrt{n})$，可以通过此题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m,k;
int a[100005];
int f[100005][321];
int main()
{
	read(n);k=sqrt(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int j=1;j<=k;j++){//预处理 
		for(int i=n;i>=1;i--){
			if(i+a[i]+j>n)f[i][j]=1;
			else f[i][j]=f[i+a[i]+j][j]+1;
		}
	}
	read(m);
	while(m--){
		int x,y;
		read(x);read(y);
		if(y<=k){//提取预处理的答案 
			printf("%d\n",f[x][y]);
		}
		else {//暴力跳 
			int ti=0;
			while(x+a[x]+y<=n){
				ti++;
				x=x+a[x]+y;
			}
			printf("%d\n",ti+1);
		}
	}
}

```


---

## 作者：FutaRimeWoawaSete (赞：0)

根号分治套路题。               

对于 $k$ 进行根号分治：           

如果 $\sqrt n \leq k$，那么我们就直接暴力跳统计答案，单次时间复杂度 $O(\sqrt n)$。           

如果 $k < \sqrt n$，则需要处理的 $k$ 只有至多 $\sqrt n$ 种，我们对于每种 $k$ 倒序枚举预处理出每个点的答案后即可对每个询问 $O(1)$ 回答。      

时间复杂度为 $O((n + q)\sqrt n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,to[Len],num[Len],t,a[Len];
int Print[Len];
struct Node
{
	int p,id;
	Node(){p = id = 0;}
	Node(int P,int ID){p = P , id = ID;}
};
vector<Node> v[Len];
inline void Work(int K)
{
	for(int i = n ; i >= 1 ; i --)
	{
		int to = K + a[i] + i;
		if(to > n) num[i] = 0;
		else num[i] = num[to] + 1;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]); 
	t = sqrt(n);
	int p,k;scanf("%d",&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%d %d",&p,&k);
		if(k <= t) v[k].push_back(Node(p , i));
		else
		{
			int res = 0;
			while(p <= n) 
			{
				p = p + a[p] + k;
				res ++;
			}
			Print[i] = res;
		}
	}
	for(int i = 1 ; i <= t ; i ++) 
	{
		if(v[i].size() > 0) 
		{
			Work(i);
			for(int j = 0 ; j < v[i].size() ; j ++) Print[v[i][j].id] = num[v[i][j].p] + 1;
		}
	}
	for(int i = 1 ; i <= m ; i ++) printf("%d\n",Print[i]);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

算是很套路的根号分治题了吧……

如果 $k$ 比较大那么我们暴力跳几下就可以超过 $n$。容易得到我们跳的次数最多为 $O(\frac{n}{k})$。

如果 $k$ 比较小那么我们考虑直接一波预处理出对于所有 $k$，第 $i$ 个数需要跳多少下才能跳到，可以用类似于 DP 的方式解决。复杂度 $O(nk)$。

套路地，我们考虑设置一个阈值 $x$，使得 $k>x$ 时采取第一种做法，然后预处理出所有 $k\le x$ 的答案。更加套路地，我们有 $x=\sqrt n$ 时取到最优解。

```cpp
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e5+9;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,x,a[N],m,f[409][N];

int main() {
	n=read(), x=pow(n,0.5);
	rep(i,1,n) a[i]=read();
	rep(i,1,x) {
		per(j,n,1) f[i][j]=(j+a[j]+i>n?1:f[i][j+a[j]+i]+1);
	}
	m=read();
	while(m--) {
		int p=read(), k=read();
		if(k<=x) printf("%d\n",f[k][p]);
		else {
			int cnt=0;
			while(p<=n) cnt++, p=p+a[p]+k;
			printf("%d\n",cnt);
		}
	}
	return 0;
}
```

---

## 作者：Sol1 (赞：0)

考虑~~暴力~~。

暴力可以有两种写法：

1. 直接模拟。复杂度$\Theta(NQ)$。

2. 预处理dp：$dp_{p,k}=\begin{cases}p+a_p+k>n,1\\p+a_p+k\leq n, dp_{p+a_p+k,k}+1\end{cases}$。时间复杂度和空间复杂度均为$\Theta(N^2)$，查询复杂度$\Theta(1)$。

但是，可以发现，实际上第一种方法单次查询的最坏复杂度是$\Theta(\frac{N}{k})$，所以对于$k>\sqrt{N}$的情况可以直接模拟。

然后对于所有$k\leq\sqrt{N}$计算$dp$，可以$\Theta(N\sqrt{N})$预处理+$\Theta(1)$或$\Theta(\sqrt{N})$回答一组询问。总复杂度$\Theta((N+Q)\sqrt{N})$。

附代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

int ans[100005][505], n, a[100005];

void Read() {
	scanf("%d", &n);
	for (int i = 1;i <= n;i++) scanf("%d", &a[i]);
}

void Prefix() {
	int m = sqrt(n);
	for (int k = 1;k <= m;k++) {
		for (int i = n;i >= 1;i--) {
			if (i + a[i] + k > n) ans[i][k] = 1;
			else ans[i][k] = ans[i + a[i] + k][k] + 1;
		}
	}
}

void Solve() {
	int q, m = sqrt(n);
	scanf("%d", &q);
	for (int i = 1;i <= q;i++) {
		int p, k;
		scanf("%d%d", &p, &k);
		if (k > m) {
			int sum = 0;
			for (;;) {
				if (p > n) break;
				sum++;
				p += a[p] + k;
			}
			printf("%d\n", sum);
		} else {
			printf("%d\n", ans[p][k]);
		}
	}
}

int main() {
	Read();
	Prefix();
	Solve();
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

这道题容易发现带 $\texttt{log}$ 的数据结构很难维护，又注意到 $n,q \le 10^5$，于是我们考虑根号做法。

我们分两种情况考虑：

1. $k > \sqrt{n}$，此时我们发现 $p$ 最多操作 $\sqrt{n}$ 次就 $>n$ 了，直接暴力做，时间复杂度 $O(\sqrt{n})$。
2. $k \le \sqrt{n}$，我们选择预处理这一部分。定义 $dp[i][j]$ 为当 $p=i,k=j$ 时的答案，转移有 $dp[i][j]=dp[i+a[i]+j][j]+1$。回答时直接输出 $dp[p][k]$。容易看出状态数为 $n\sqrt{n}$，转移复杂度为 $O(1)$，故预处理复杂度为 $O(n\sqrt{n})$，回答复杂度 $O(1)$。

综上所述，总时间复杂度为 $O(n\sqrt{n}+q\sqrt{n})$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int a[100005];
int dp[100005][320];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int sn=sqrt(n);
	for(int i=n;i>=1;i--)
		for(int j=1;j<=sn;j++){
			if(i+a[i]+j>n) dp[i][j]=1;
			else dp[i][j]=dp[i+a[i]+j][j]+1;
		}
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int p,k;
		scanf("%d%d",&p,&k);
		if(k<=sn) printf("%d\n",dp[p][k]);
		else{
			int ans=0;
			while(p<=n){
				ans++;
				p+=a[p]+k;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定长度为 $n$ 的序列 $a$。$m$ 次询问。
- 每次询问给出 $p,k$。您要不断地执行操作 $p\gets p+a_p+k$，直到 $p&gt;n$ 为止。询问的答案为操作次数。
- $1\le n,q\le 10^5$，$1\le a_i\le n$，$1\le p,k\le n$。

# 题目分析

先有纯暴力：

```cpp
for (register int i = p;i <= n;i += a[i] + k) cnt ++;
```

---------

考虑根号分治优化。

定一个值 $S$，当 $k>S$ 时直接暴力算，当 $k<S$ 时，我们预处理出 $pre[i,j]$ 表示询问为 $j + a[j] + i$ 时所需的操作次数。当 $j+a_j+i\gt n$ 时，只需一次操作；其他情况有 $pre[i,j]=pre[i,j+a_j+i]+1$。

$S$ 取 $\sqrt{n}$ 时复杂度为 $\mathcal{O(n\sqrt n)}$。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	#ifndef ONLINE_JUDGE
	#define getc getchar
	#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1e5 + 5,M = 317;
int a[N],pre[M][N];
//pre[i][j]:询问为 j + a[j] + i 时的操作次数 
int n,m;
int main(void) {
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	int sq = sqrt(n);
	for (register int i = 1;i <= sq; ++ i) {
		for (register int j = n;j >= 1; -- j) {
			pre[i][j] = j + a[j] + i > n ? 1 : pre[i][j + a[j] + i] + 1;
		}
	}
	m = read();
	while (m --) {
		int p = read(),k = read();
		if (k >= sq) {
			int cnt = 0;
			for (register int i = p;i <= n;i += a[i] + k) cnt ++;
			printf("%d\n",cnt);
		} else {
			printf("%d\n",pre[k][p]);
		}
	}
	
	return 0;
}
```

---

