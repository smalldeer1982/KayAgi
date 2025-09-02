# Bananas in a Microwave

## 题目描述

You have a malfunctioning microwave in which you want to put some bananas. You have $ n $ time-steps before the microwave stops working completely. At each time-step, it displays a new operation.

Let $ k $ be the number of bananas in the microwave currently. Initially, $ k = 0 $ . In the $ i $ -th operation, you are given three parameters $ t_i $ , $ x_i $ , $ y_i $ in the input. Based on the value of $ t_i $ , you must do one of the following:

Type 1: ( $ t_i=1 $ , $ x_i $ , $ y_i $ ) — pick an $ a_i $ , such that $ 0 \le a_i \le y_i $ , and perform the following update $ a_i $ times: $ k:=\lceil (k + x_i) \rceil $ .

Type 2: ( $ t_i=2 $ , $ x_i $ , $ y_i $ ) — pick an $ a_i $ , such that $ 0 \le a_i \le y_i $ , and perform the following update $ a_i $ times: $ k:=\lceil (k \cdot x_i) \rceil $ .

Note that  $ x_i $ can be a fractional value. See input format for more details. Also, $ \lceil x \rceil $ is the smallest integer $ \ge x $ .

At the $ i $ -th time-step, you must apply the $ i $ -th operation exactly once.

For each $ j $ such that $ 1 \le j \le m $ , output the earliest time-step at which you can create exactly $ j $ bananas. If you cannot create exactly $ j $ bananas, output $ -1 $ .

## 说明/提示

In the first sample input, let us see how to create $ 16 $ number of bananas in three timesteps. Initially, $ k=0 $ .

- In timestep 1, we choose $ a_1=2 $ , so we apply the type 1 update — $ k := \lceil(k+3)\rceil $ — two times. Hence, $ k $ is now 6.
- In timestep 2, we choose $ a_2=0 $ , hence value of $ k $ remains unchanged.
- In timestep 3, we choose $ a_3=1 $ , so we are applying the type 1 update $ k:= \lceil(k+10)\rceil $ once. Hence, $ k $ is now 16.

It can be shown that $ k=16 $ cannot be reached in fewer than three timesteps with the given operations.

In the second sample input, let us see how to create $ 17 $ number of bananas in two timesteps. Initially, $ k=0 $ .

- In timestep 1, we choose $ a_1=1 $ , so we apply the type 1 update — $ k := \lceil(k+3.99999)\rceil $ — once. Hence, $ k $ is now 4.
- In timestep 2, we choose $ a_2=1 $ , so we apply the type 2 update — $ k := \lceil(k\cdot 4.12345)\rceil $ — once. Hence, $ k $ is now 17.

It can be shown that $ k=17 $ cannot be reached in fewer than two timesteps with the given operations.

## 样例 #1

### 输入

```
3 20
1 300000 2
2 400000 2
1 1000000 3```

### 输出

```
-1 -1 1 -1 -1 1 -1 -1 -1 3 -1 2 3 -1 -1 3 -1 -1 -1 3```

## 样例 #2

### 输入

```
3 20
1 399999 2
2 412345 2
1 1000001 3```

### 输出

```
-1 -1 -1 1 -1 -1 -1 1 -1 -1 3 -1 -1 -1 3 -1 2 -1 3 -1```

# 题解

## 作者：do_while_true (赞：6)

# $\mathcal{Solution}$

设 $f_i$ 为到达 $i$ 的答案，不能到达则为 $inf$。

设 $g_i$ 为考虑完前面的操作时，单独使用当前操作来到达 $i$ 的最小步数，不能到达则为 $inf$。

每次读进一个操作就把 $g$ dp 一次，然后更新 $f$。

具体的：

1. 初始化 $g_i=\left\{\begin{matrix}0,f_i\neq inf\\inf,f_i=inf
\end{matrix}\right.$

2. 若 $g_i\neq y$，则 $g_{\left \lceil i+x \right \rceil }=\min(g_{\left \lceil i+x \right \rceil },g_i+1)$ 或 $g_{\left \lceil i*x \right \rceil }=\min(g_{\left \lceil i*x \right \rceil },g_i+1)$。

3. 根据 $g$ 更新 $f$，若 $g_i\neq inf$，则对 $f_i$ 更新。

时间复杂度 $\mathcal{O}(nm)$

# $\mathcal{Code}$

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
namespace do_while_true {
	#define ld double
	#define ll long long
	#define re register
	#define pb push_back
	#define fir first
	#define sec second
	#define pp std::pair
	#define mp std::make_pair
	const ll mod = 1e9 + 7;
	template <typename T>
	inline T Max(T x, T y) { return x > y ? x : y; }
	template <typename T>
	inline T Min(T x, T y) { return x < y ? x : y; }
	template <typename T>
	inline T Abs(T x) {	return x < 0 ? -x : x; }
	template <typename T>
	inline T& read(T& r) {
		r = 0; bool w = 0; char ch = getchar();
		while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
		while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
		return r = w ? -r : r;
	}
	template <typename T>
	inline T qpow(T x, T y) {
		re T sumq = 1; x %= mod;
		while(y) {
			if(y&1) sumq = sumq * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return sumq;
	}
	char outch[110];
	int outct;
	template <typename T>
	inline void print(T x) {
		do {
			outch[++outct] = x % 10 + '0';
			x /= 10;
		} while(x);
		while(outct >= 1) putchar(outch[outct--]);
	}
}
using namespace do_while_true;

const int N = 1e5 + 10;
const int INF = 0x3ffffff;

int n, m;
int f[N], g[N];

void work(int q) {
	int t, y; ll x;
	for(int i = 1; i <= m; ++i) g[i] = INF;
	read(t); read(x); read(y);
	if(t == 1) {
		x = x / 100000 + (x % 100000 > 0);
		g[x] = 1;
		for(int i = 1; i <= m; ++i)
			if(f[i] != INF) g[i] = 0;
		for(int i = 1; i <= m; ++i)
			if(g[i] != y && g[i] != INF && i+x <= m)
				g[i+x] = Min(g[i+x], g[i]+1);
		for(int i = 1; i <= m; ++i)
			if(g[i] <= y && f[i] == INF)
				f[i] = q;
	}
	else {
		for(int i = 1; i <= m; ++i)
			if(f[i] != INF) g[i] = 0;
		for(int i = 1; i <= m; ++i) {
			int p = (int)std::ceil(1.0 * i * x / 100000);
			if(g[i] != y && g[i] != INF && p <= m)
				g[p] = Min(g[p], g[i]+1);
		}
		for(int i = 1; i <= m; ++i)
			if(g[i] <= y && f[i] == INF)
				f[i] = q;
	}
}

signed main() {
	read(n); read(m);
	for(int i = 1; i <= m; ++i) f[i] = INF;
	for(int i = 1; i <= n; ++i)
		work(i);
	for(int i = 1; i <= m; ++i) printf("%d ", f[i] == INF ? -1 : f[i]);
	return 0;
}
```

---

## 作者：vectorwyx (赞：3)

非常具有启发意义的一道 dp。

先考虑如果只有第一种操作该怎么做，由于 $\lceil k+x \rceil$ 在 $k$ 为整数时等价于 $k+\lceil x \rceil$，所以这就是一个简单的多重背包问题。令 $f_{i,j}$ 表示前 $i$ 步能否凑出 $j$，转移方程为 $f_{i,j}=[(\sum_{k=0}^{y_{i-1}}f_{i-1,j-k\lceil x_{i-1} \rceil})>0]$。其中 $[x]$ 表示当命题 $x$ 为真时值为 $1$，否则值为 $0$。

然后考虑当前这一行对下一行的贡献，我们发现 $f_{i,j}$ 会对 $f_{i+1,j},f_{i+1,j+\lceil x_{i} \rceil},f_{i+1,j+2\lceil x_{i} \rceil},\cdots,f_{i+1,j+y_{i}\lceil x_{i} \rceil}$ 产生 $f_{i,j}$ 的贡献，而 $f_{i,j+\lceil x_{i} \rceil}$ 又会对 $f_{i+1,j+\lceil x_{i} \rceil},f_{i+1,j+2\lceil x_{i} \rceil},\cdots,f_{i+1,j+y_{i}\lceil x_{i} \rceil},f_{i+1,j+(y_{i+1})\lceil x_{i} \rceil}$ 产生贡献。所以我们可以把第 $i+1$ 行的第 $j,j+\lceil x_{i} \rceil,j+2\lceil x_{i} \rceil,\cdots(0\le j<\lceil x_{i} \rceil)$ 个元素抽离出来，按照 $j$ 的不同分成若干个相互独立的序列，显然第 $i+1$ 行的每个元素都属于某个唯一确定的序列。那么第 $i$ 行的 $f_{i,j}$ 所产生的贡献就转化为了对第 $i+1$ 行中 $j$ 所属的序列进行一次区间修改，借助差分能做到 $O(len_{i})$，其中 $len_i$ 表示第 $i$ 个序列的长度，合在一起就可以做到 $O(m)$ 地转移一行。

而这种做法对于第二种操作仍然成立。我们只需要把第 $i+1$ 行的第 $j,\lceil jx_{i} \rceil,\lceil j\lceil jx_{i} \rceil \rceil,\cdots$ 抽离出来，其余就和第一种操作无异了。总时间复杂度为 $O(nm)$。

还有就是，一定要开 long long！我赛时的代码因为有一处不幸爆 int 而痛失 AC，不然就上紫了┭┮﹏┭┮。

代码如下（码 $LaTex$ 不易，希望能给个赞QAQ！谢谢！）
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define db double
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
 
inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}
 
const int N=205,M=1e5+5;
const db F=100000.0;
int n,m,f[N][M],t[N],y[N],vis[M],ti,st[M],top,val[M],ans[M];
ll x[N];
 
int main(){
	cin>>n>>m;
	fo(i,1,n) scanf("%d %lld %d",&t[i],&x[i],&y[i]);
	//fo(i,1,n) cin>>t[i]>>x[i]>>y[i];
	fo(i,0,n) f[i][0]=1;
	fo(i,1,n){
		++ti;
		if(t[i]==1){
			fo(j,0,m) if(vis[j]!=ti){
				top=0;
				for(int k=j;k<=m;k+=ceil(x[i]/F)) st[++top]=k,val[top]=0;
				fo(k,1,top) val[k]+=f[i-1][st[k]],val[min(k+y[i]+1,top+1)]-=f[i-1][st[k]];
				fo(k,1,top) val[k]+=val[k-1],f[i][st[k]]=val[k],vis[st[k]]=ti;
			}
		}else{
			fo(j,1,m) if(vis[j]!=ti){
				top=0;
				for(ll k=j;k<=m;k=ceil(k*x[i]/F)) st[++top]=k,val[top]=0;
				fo(k,1,top) val[k]+=f[i-1][st[k]],val[min(k+y[i]+1,top+1)]-=f[i-1][st[k]];
				fo(k,1,top) val[k]+=val[k-1],f[i][st[k]]=val[k],vis[st[k]]=ti;
			}
		}
		fo(j,1,m) f[i][j]=(bool)(f[i][j]);
	}
	fo(j,1,m){
		ans[j]=-1;
		fo(i,1,n) if(f[i][j]){
			ans[j]=i;
			break;
		}
	}
	fo(i,1,m) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：bryce (赞：0)

## [Bananas in a Microwave](https://www.luogu.com.cn/problem/CF1498D)
### 思路
直接模拟复杂度会爆掉，于是考虑 $dp$，设 $f_i$ 表示最早出现的操作，每次操作都用 $g_i$ 转移，设 $g_i$ 表示在第 $k$ 次操作时，能通过几次到 $i$，这样就完美地解决了限制 $y$ 的问题。那么 $g_i$ 的转移方程就为 $g_{\lceil i + x\rceil } = \min(g_{\lceil i + x\rceil }, g_i + 1)$，$g_{\lceil i\times x\rceil } = \min(g_{\lceil i\times x\rceil}, g_i + 1)$，最后用 $g$ 更新 $f$ 即可。
### 代码
```cpp
#include<iostream>
#include<cmath>
#define int long long
#define INF 0x3f3f3f3f

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 1e5 + 10;
int n, m;
int f[N], g[N];

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= m; i++) f[i] = INF;
    for (int i = 1; i <= n; i++){
        int t = read(), x = read(), y = read();
        double x0 = 1.0 * x / 100000;
        for (int j = 1; j <= m; j++)
            if (f[j] != INF) g[j] = 0;
            else g[j] = INF;
        if (t == 1){
            for (int j = 0; j <= m; j++){
                int k = ceil(j + x0);
                if (k <= m && g[j] != INF)
                    g[k] = min(g[k], g[j] + 1);
            }
        }else{
            for (int j = 1; j <= m; j++){
                int k = ceil(1.0 * j * 1.0 * x / 100000);
                if (k <= m && g[j] != INF)
                    g[k] = min(g[k], g[j] + 1);
            }
        }
        for (int j = 1; j <= m; j++)
            if (f[j] == INF && g[j] <= y) f[j] = i;
    }
    for (int i = 1; i <= m; i++)
        if (f[i] == INF) cout << -1 << ' ';
        else cout << f[i] << ' ';
    return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

考虑暴力 dp。

设 $f_{i,j}$ 表示操作 $i$ 中是否出现了 $j$。转移为：$f_{i,j}=f_{i-1,j}$，再枚举操作数计算每一轮的 $k$（初始 $f_{i-1,j}=1$ 才能转移），然后进行转移即可。

考虑优化枚举 $j$ 后进行多轮计算 $k$ 并转移的过程。发现每一轮的 $k$ 是单调不减的，我们再记录一个 $g_i$ 表示在当前操作下，转移到 $i$ 所需要的操作轮数。这样我们枚举 $j$ 并且转移的过程可以变为线性的：计算一轮 $k$，每一次更新 $g_j=g_k+1$。下次转移到 $x$ 时 $g_x=y$ 则不能用 $x$ 进行转移了。这样就能使时间复杂度降至 $O(nm)$。

设 $f_i$ 表示转移至 $i$ 的最小操作轮数，转移照常且方便输出答案。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e5 + 10;

int n, m, f[N], g[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  memset(f, -1, sizeof f);
  f[0] = 0;
  For(i,1,n) {
    int t, x, y;
    cin >> t >> x >> y;
    memset(g, 0, sizeof g);
    double x0 = (1.0 * x) / 100000;
    For(j,0,m) {
      if(f[j] == -1 || g[j] == y) continue;
      if(t == 1) {
        int k = j + ceil(x0);
        if(k <= m) if(f[k] == -1) f[k] = i, g[k] = g[j] + 1; 
      } else {
        int k = ceil(j * (1.0 * x) / 100000);
        if(j && k <= m) if(f[k] == -1) f[k] = i, g[k] = g[j] + 1; 
      }
    }
  }
  For(i,1,m) cout << f[i] << ' ';
  return 0;
}
```

---

## 作者：cunzai_zsy0531 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF1498D)

考虑直接模拟。开一个数组 $f_i$ 表示第 $i$ 个位置能够取到的时间，没有取到设为 $-1$。每一次的加或乘操作一步一步做即可。

以加法为例：设这一轮需要加的数为 $x$，最多加的次数为 $y$。用一个数组 $g_i$ 表示加到 $i$ 这个数的次数。当 $g_i=y$ 时，就不能用它继续往后加了。模拟过程是 $O(m)$的，总复杂度 $O(nm)$。

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1e5+13;
int f[N],g[N],n,m,p=100000;
ll lim;
int main(){
	scanf("%d%d",&n,&m);lim=100000ll*m; //要注意对题目中给的x'i的操作，注意乘法会不会爆longlong。
	memset(f,-1,sizeof f);f[0]=0;
	for(int i=1;i<=n;++i){
		int op,y;ll x;
		scanf("%d%lld%d",&op,&x,&y);
		memset(g,0,sizeof g);
		for(int j=0;j<=m;++j){
			if(f[j]==-1||g[j]==y) continue;//特判这个位置能不能更新
			if(op==1){
				int tmp=(x-1)/p+1;
				if(j+tmp<=100000){
					if(f[j+tmp]==-1) f[j+tmp]=i,g[j+tmp]=g[j]+1;//注意这里的特判，因为如果f[j+tmp]已经更新过了，就不用更新g了
				}
			}
			else{
				if(j&&j*x<=lim){
					int tmp=(j*x-1)/p+1;
					if(f[tmp]==-1) f[tmp]=i,g[tmp]=g[j]+1;
				}
			}
		}
	}
	for(int i=1;i<=m;++i) printf("%d ",f[i]);
	return 0;
}
```


---

