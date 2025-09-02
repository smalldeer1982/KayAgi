# Candies and Stones

## 题目描述

小杰拉尔德和他的教练迈克玩一个有趣的游戏。

游戏开始时，有 $n$ 个糖果和 $m$ 块石头。杰拉尔德和迈克轮流行动，迈克先行动。

- 迈克行动时，他会检查杰拉尔德吃了多少糖果和石头。如果杰拉尔德吃了 $a$ 块糖和 $b$ 块石头，他就会得到 $f(a, b)$ 奖分。其中 $f(a, b) = (x_a + y_b) \bmod p$。
- 杰拉尔德行动时，他要么从糖果堆里吃掉一块糖果，要么从石头堆里吃掉一块石头。

当迈克看到杰拉尔德把除了一块糖和一块石头之外的糖果和石头都吃光时，他最后一次得分，游戏结束。迈克不允许杰拉尔德吃所有的糖果，也不允许他吃所有的石头。编程求出杰拉尔德如何游戏才能获得最大的分数，并求出一组方案。

## 样例 #1

### 输入

```
2 2 10
0 0
0 1
```

### 输出

```
2
SC
```

## 样例 #2

### 输入

```
3 3 10
0 2 0
0 0 2
```

### 输出

```
10
CSSC
```

## 样例 #3

### 输入

```
3 3 2
0 1 1
1 1 0
```

### 输出

```
4
SCSC
```

# 题解

## 作者：Ignotus (赞：13)

线性空间做法。

首先，如果不需要输出方案，那么直接设 $f_i$ 为纵坐标是 $i$ 的最大答案，按行转移就行了。

关键是在输出方案的处理上。我们考虑按走的步数分治，主要的思想就是通过 dp 值在中间的合并，使得每次都能找到一个新的最优决策点，然后分治下去，求起点到最优决策点，和最优决策点到终点的答案。

具体来说，如果我们现在分治区间的起点终点分别是 $(s_x,s_y),(e_x,e_y)$，从起点走到终点需要 $d$ 步，则我们要找到对于所有从起点开始走 $\frac{d}{2}$ 步能够到达的点。dp 分别令 $f_i,g_i$ 为从起点/终点开始更新到第 $i$ 列的最优答案，在决策点处合并。找到最优决策点之后分治下去即可。

最后统计答案，我们记录决策点的时候是按顺序记录的，所以直接算出所有决策点处的答案和就是最优答案；判断相邻两个决策点之间的位置关系即可得到方案。

设 $n,m$ 同阶，则空间复杂度 $\mathcal O(n)$，时间复杂度 $\mathcal O(n^2)$。

时间复杂度分析：$T(n^2)=2T((\dfrac{n}{2})^2)+\mathcal O(n^2)=\mathcal O(n^2)$。

具体实现详见代码。

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define pii pair <int, int>
#define fi first
#define se second

template <typename T>
void rd(T& x){
    x = 0; char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}
template <typename T, typename... Args>
void rd(T& x, Args&... args){rd(x); rd(args...);}

const int N = 2e4 + 10;

int n, m, p, x[N], y[N];
ll ans, f[N], g[N];
pii st[N << 1]; // 决策点

void solve(int sx, int sy, int ex, int ey, int cur, int siz){
    st[cur] = {sx, sy}, st[cur + siz] = {ex, ey};
    if(siz < 2) return void();
    vector <pii> vec;
    for(int i = sy; i <= ey; ++i) f[i] = g[i] = 0;
    int k = siz / 2;
    for(int i = sx, dx; i <= ex; ++i){
        dx = i - sx;
        for(int j = sy, dy; j <= ey; ++j){
            dy = j - sy;
            if(dx + dy > k) break;
            if(dy) f[j] = max(f[j], f[j - 1]);
            f[j] += (x[i] + y[j]) % p;
            if(dx + dy == k) vec.push_back({i, j});
        }
    }
    k = siz - k;
    for(int i = ex, dx; i >= sx; --i){
        dx = ex - i;
        for(int j = ey, dy; j >= sy; --j){
            dy = ey - j;
            if(dx + dy > k) break;
            if(dy) g[j] = max(g[j], g[j + 1]);
            g[j] += (x[i] + y[j]) % p;
        }
    }
    ll mx = -1, t = 0; pii ret;
    for(auto it : vec){
        int i = it.fi, j = it.se;
        t = f[j] + g[j] - (x[i] + y[j]) % p;
        if(t > mx) mx = t, ret = {i, j};
    }
    k = siz / 2;
    solve(sx, sy, ret.fi, ret.se, cur, k);
    solve(ret.fi, ret.se, ex, ey, cur + k, siz - k);
}

int main(){
    rd(n, m, p);
    for(int i = 1; i <= n; ++i) rd(x[i]);
    for(int i = 1; i <= m; ++i) rd(y[i]);
    solve(1, 1, n, m, 1, n + m - 2);
    for(int i = 1; i <= n + m - 1; ++i) ans += (x[st[i].fi] + y[st[i].se]) % p;
    printf("%lld\n", ans);
    for(int i = 2; i <= n + m - 1; ++i){
        if(st[i].fi == st[i - 1].fi) putchar('S');
        else putchar('C');
    }
    putchar('\n');
    return 0;
}
```


---

## 作者：mrsrz (赞：10)

显然是个$O(nm)$的DP，$f[i][j]$表示走到$(i,j)$的最大价值，转移：$f[i][j]=\max(f[i-1][j],f[i][j-1])+val[i][j]$。

方案则对每个位置记录一下从哪个状态转移来的即可。

然而空间复杂度$O(nm)$，比45MB不知多多少。

不难想到用滚动数组把$f$数组优化到$O(m)$，对于状态转移数组，每一位只有两种状态，所以可以用bitset存。

这样空间复杂度达到了$O(\frac{nm}{\omega})$。

然而这个bitset要47MB（毒瘤QAQ）。

我们考虑把矩阵分成两半，求出$(0,0)$到中间每个点的DP值，求出中间每个点（下面一行）到$(n-1,m-1)$的DP值。

然后我们就可以知道最优解经过中间的时候，是在哪一列了。

然后分别对前半部分计算路径，后半部分计算路径即可。这样bitset只用开一半，即可卡过。

当然算前一半路径可以计算第一遍DP值的时候同时进行。

代码写丑了QAQ

## Code：
```cpp
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
std::bitset<20001>b[10001];
int x[20001],y[20001],p,n,m,mid;
inline int f(int a,int b){int s=x[a]+y[b]-p;return s+(s>>31&p);}
void output(int x,int y){
	if(!x&&!y)return;
	if(!b[x].test(y))output(x,y-1),putchar('S');else output(x-1,y),putchar('C');
}
long long dp1[2][20001],dp2[2][20001];
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<n;++i)scanf("%d",x+i),x[i]%=p;
	for(int i=0;i<m;++i)scanf("%d",y+i),y[i]%=p;
	if(n==1){
		long long ans=0;
		for(int i=0;i<m;++i)ans+=f(0,i);
		printf("%lld\n",ans);
		for(int i=1;i<m;++i)putchar('S');
		return 0;
	}
	mid=n>>1;
	int cur=0,cur2=0;
	dp2[0][0]=f(0,0);
	for(int i=0;i<m;++i)dp2[0][i]=dp2[0][i-1]+f(0,i);
	for(int i=1;i<mid;++i){
		cur2^=1;
		memset(dp2[cur2],0,sizeof*dp2);
		dp2[cur2][0]=dp2[cur2^1][0]+f(i,0);
		b[i].set(0);
		for(int j=1;j<m;++j)
		if(dp2[cur2][j-1]>dp2[cur2^1][j]){
			dp2[cur2][j]=dp2[cur2][j-1]+f(i,j);
		}else
		dp2[cur2][j]=dp2[cur2^1][j]+f(i,j),b[i].set(j);
	}
	dp1[0][m-1]=f(n-1,m-1);
	for(int i=m-2;~i;--i)dp1[0][i]=dp1[0][i+1]+f(n-1,i);
	for(int i=n-2;i>=mid;--i){
		cur^=1;
		memset(dp1[cur],0,sizeof*dp1);
		dp1[cur][m-1]=dp1[cur^1][m-1]+f(i,m-1);
		for(int j=m-2;~j;--j)
		if(dp1[cur][j+1]>dp1[cur^1][j]){
			dp1[cur][j]=dp1[cur][j+1]+f(i,j);
		}else
		dp1[cur][j]=dp1[cur^1][j]+f(i,j);
	}
	int P=0;
	for(int i=1;i<m;++i)
	if(dp1[cur][i]+dp2[cur2][i]>dp1[cur][P]+dp2[cur2][P])P=i;
	printf("%lld\n",dp1[cur][P]+dp2[cur2][P]);
	output(mid-1,P);
	memset(dp1,0,sizeof dp1);
	cur=0;
	for(int i=m-2;~i;--i)dp1[0][i]=dp1[0][i+1]+f(n-1,i);
	b[n-mid-1].reset();
	for(int i=n-2;i>=mid;--i){
		b[i-mid].reset();
		cur^=1;
		memset(dp1[cur],0,sizeof*dp1);
		dp1[cur][m-1]=dp1[cur^1][m-1]+f(i,m-1);
		b[i-mid].set(m-1);
		for(int j=m-2;~j;--j)
		if(dp1[cur][j+1]>dp1[cur^1][j]){
			dp1[cur][j]=dp1[cur][j+1]+f(i,j);
		}else
		dp1[cur][j]=dp1[cur^1][j]+f(i,j),b[i-mid].set(j);
	}
	putchar('C');
	for(int x=mid,y=P;x!=n-1||y!=m-1;){
		if(!b[x-mid].test(y))putchar('S'),++y;else putchar('C'),++x;
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：6)

不好玩题目，使我的空间被卡。

### 解题思路

考虑空间限制更大的情况的做法：钦定 $f_{i,j}$ 表示吃了 $i$ 颗糖，$j$ 颗石子的最优解，$g_{i,j}$ 为 $0$ 表示转移时吃了糖，为 $1$ 表示吃了石子，$val_{i,j}$ 表示原题面表述的 $f(i-1,j-1)$。

转移方程如下：

$$f_{i,j}=\begin{cases}
val_{i,j}+f_{i-1,j} & j=1 \\
val_{i,j}+f_{i,j-1} & i=1 \\
val_{i,j}+f_{i-1,j} & i\gt 1,j\gt 1,f_{i-1,j} \gt f_{i,j-1} \\
val_{i,j}+f_{i,j-1} & i\gt 1,j\gt 1,f_{i-1,j} \leq f_{i,j-1} \\
\end{cases}$$

边界为 $f_{1,1}=val_{1,1},f_{0,j}=f_{i,0}=0$。

但是空间过不去，考虑优化。

根据转移方程，$f$ 显然可以滚动掉一维，而 $g$ 可以使用 bitset 存储节省空间，这样空间就会减少到大约 50MB。

接下来我们只需要进行常数级别的优化即可：考虑用时间常数换空间常数：我们进行两次转移，第一次仅记录 $i\geq \lfloor\frac n 2\rfloor$ 时的转移点，第二次仅记录 $i\leq \lfloor\frac n 2\rfloor$ 的转移点。

第一次转移完毕后记录终点 $(n,m)$ 在 $i=\lfloor\frac n 2\rfloor$ 时的决策点，记为 $(\lfloor\frac n 2\rfloor,M)$，并记录转移路径，第二次转移完毕后记录 $(1,1)$ 到达决策点 $(\lfloor\frac n 2\rfloor,M)$ 时的转移路径，两个拼起来就是 $(1,1)$ 到 $(n,m)$ 的转移路径。

时间复杂度为 $O(n^2)$ 带常数 $2$，空间复杂度 $O(\frac {nm} {2w})$，实际运行空间为 25MB+eps，可以通过。

---

## 作者：lytqwq (赞：3)

难点在空间限制 $\text{45MB}$，空间复杂度为 $O(n^2)$ 的 dp 过不去，我们可以每 $\sqrt{n}$ 行存一下答案，从第 $n-\sqrt{n}$ 行再跑一遍 dp，这一遍全存，转化为到点 $(i,j)$ 的子问题，继续跑就完了。

时间复杂度 $O(n^2)$，空间复杂度 $O(n\sqrt{n})$。



代码如下：



```cpp
#include<bits/stdc++.h>
#define ll long long
#define PI pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define ui unsigned int
using namespace std;
const int N=20010,K=151;
int n,m,p;;
bool g[K][N],dg[K][N];
int x[N],y[N];
int f[K][N],now[2][N],nowg[2][N],df[K][N];
stack<int> ans;
int main(){
	scanf("%d%d%d",&n,&m,&p);
	n--;m--;
	int k=max(sqrt(n),1.0);
	for(int i=0;i<=n;i++){
		scanf("%d",&x[i]);
	}
	for(int i=0;i<=m;i++){
		scanf("%d",&y[i]);
	}
	int op=0;
	for(int i=0;i<=n;i++){
		op^=1;
		memset(nowg[op],0,sizeof(nowg[op]));
		memset(now[op],0,sizeof(now[op]));
		for(int o=0;o<=m;o++){
			now[op][o]=now[op^1][o]+(x[i]+y[o])%p;
			nowg[op][o]=1;
			if(o!=0&&now[op][o]<now[op][o-1]+(x[i]+y[o])%p){
				now[op][o]=now[op][o-1]+(x[i]+y[o])%p;
				nowg[op][o]=0;
			}
		}
		if(i%k==0){
			for(int o=0;o<=m;o++)f[i/k][o]=now[op][o],g[i/k][o]=nowg[op][o];
			for(int o=0;o<=m;o++)nowg[op][o]=o;
		}
	}
	int nowx=n,nowy=m;
	for(int i=n/k;i>=0;i--){
		memcpy(df[0],f[i],sizeof(df[0]));
		memcpy(dg[0],g[i],sizeof(dg[0]));
		for(int o=i*k+1;o<=min(n,(i+1)*k);o++){
			for(int v=0;v<=m;v++){
				df[o-i*k][v]=df[o-i*k-1][v]+(x[o]+y[v])%p;
				dg[o-i*k][v]=1;
				if(v!=0&&df[o-i*k][v]<df[o-i*k][v-1]+(x[o]+y[v])%p){
					df[o-i*k][v]=df[o-i*k][v-1]+(x[o]+y[v])%p;
					dg[o-i*k][v]=0;
				}
			}
		}
		for(;nowx>=(i*k+1);){
			ans.push(dg[nowx-i*k][nowy]);
			if(dg[nowx-i*k][nowy]==0){
				nowy--;
			}
			else{
				nowx--;
			}
		}
	}
	while(nowy!=0){
		ans.push(0);
		nowy--;
	}
	printf("%d\n",now[op][m]);
	while(!ans.empty()){
		if(ans.top())printf("C");
		else printf("S");
		ans.pop();
	}
	return 0;
}

```



---

## 作者：听取MLE声一片 (赞：1)

如果只需要计算最大值是容易 $O(n^2)$ 的，设 $f_{i,j}$ 表示吃了 $i$ 个物品，其中 $j$ 个为糖果的最大分数。

转移就是 $f_{i,j}=\max (f_{i-1,j-1},f_{i-1,j})+(a_i+b_{i-j})\bmod p$，使用滚动数组空间就可以线性。

朴素的记录方案是记录每个位置是由哪个位置转移过来的，这道题可以简化为记录是否吃糖果。可是这题空间限制非常紧，直接开显然开不下。

考虑分块，对 $f_{i,j}$ 的第一维分块，块长为 $B$。

先顺着对每个块跑 dp，处理出每个块末尾的 dp 状态，每个块开头继承上个块末尾的信息。

然后再倒着处理每个块。对于每个块跑一遍记录方案的 dp。

从后面的块得知最优转移的其中一个是 $f_{r,p}$，其中 $r$ 为块的右端点，然后从 $p$ 位置不断向前跳即可得出方案。

这两次 dp 每个块内的时间复杂度都为 $O(Bn)$，总时间复杂度为 $O(\frac{n}{B}Bn)=O(n^2)$。

空间上，需要开一个 $\frac{n^2}{B}$ 的数组开记录每个块末尾的 dp 状态，还需要开一个 $Bn$ 的数组来记录每个块内的转移信息。平衡一下，令 $\frac{n}{B}=B$，即 $B=\sqrt n$，则空间复杂度为 $n\sqrt n$。

如果转移信息使用 bitset，则取 $B=\sqrt{nw}$ 最优，不过没有必要。

注意 dp 数组初值要设负无穷，以及最后要加上一个都不吃的分数。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=4e4+10;
const int M=2e4+10;
const int B=201;
int n,m,k,mod,a[N],b[N],L[N],R[N];
int Ans[N],cnt;
ll ans,f[2][N],dp[B][M];
bitset<M>st[B];
int check(int x,int y){
	if(x<0||x>=n||y<0||y>=m)return 0;
	return 1;
}
void solve(int p){
	memset(f,128,sizeof(f));
	int l=L[p],r=R[p],w=(l&1)^1;
	for(int i=0;i<n;i++)
		f[w][i]=dp[p-1][i];
	for(int i=l;i<=r;i++){
		int u=(i&1),v=u^1;
		memset(f[u],128,sizeof(f[u]));
		for(int x=0;x<min(i+1,n);x++){
			int y=i-x,w=(a[x]+b[y])%mod;
			if(!check(x,y))continue;
			if(x)
				f[u][x]=max(f[u][x],f[v][x-1]+w);
			if(y)
				f[u][x]=max(f[u][x],f[v][x]+w);
		}
	}
	w=(r&1);
	for(int i=0;i<n;i++)
		dp[p][i]=f[w][i];
}
int calc(int p,int q){
	memset(f,128,sizeof(f));
	memset(st,0,sizeof(st));
	int l=L[p],r=R[p],w=(l&1)^1;
	for(int i=0;i<n;i++)
		f[w][i]=dp[p-1][i];
	for(int i=l;i<=r;i++){
		int u=(i&1),v=u^1,d=i-l+1;
		memset(f[u],128,sizeof(f[u]));
		for(int x=0;x<min(i+1,n);x++){
			int y=i-x,res=0,w=(a[x]+b[y])%mod;
			if(!check(x,y))continue;
			if(x){
				res=f[v][x-1]+w;
				if(res>f[u][x]){
					f[u][x]=res;
					st[d][x]=1;
				}
			}
			if(y){
				res=f[v][x]+w;
				if(res>f[u][x]){
					f[u][x]=res;
					st[d][x]=0;
				}
			}
		}
	}
	for(int i=r-l+1;i>=1;i--){
		Ans[++cnt]=st[i][q];
		if(st[i][q])q--;
	}
	return q;
}
int main()
{
	n=read(),m=read(),mod=read();
	k=n+m-2;
	for(int i=1;i<M;i++)
		dp[0][i]=-1e9;
	for(int i=0;i<n;i++)
		a[i]=read();
	for(int i=0;i<m;i++)
		b[i]=read();
	int t=k/B;
	for(int i=1;i<=t;i++){
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+B;
	}
	if(R[t]<k){
		t++;
		L[t]=R[t-1]+1;
		R[t]=k;
	}
	for(int i=1;i<=t;i++)
		solve(i);
	for(int i=0;i<n;i++){
		dp[t][i]+=(a[0]+b[0])%mod;
		if(dp[t][i]>ans)
			ans=dp[t][i];
	}
	cout<<ans<<'\n';
	int p=n-1;
	for(int i=t;i>=1;i--)
		p=calc(i,p);
	for(int i=k;i>=1;i--){
		if(Ans[i])
			cout<<'C';
		else cout<<'S';
	}
	return 0;
}

```

---

