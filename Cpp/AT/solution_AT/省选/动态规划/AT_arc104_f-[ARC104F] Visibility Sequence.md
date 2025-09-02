# [ARC104F] Visibility Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc104/tasks/arc104_f

一列に並んだ $ N $ 棟のビルが建設中であり、ビルには左から順番に $ 1,\ 2,\ \ldots,\ N $ の番号がついています。

長さ $ N $ の整数列 $ X $ が与えられ、ビル $ i $ の高さ $ H_i $ は、$ 1 $ 以上 $ X_i $ 以下の整数のいずれかにすることができます。

$ 1\ \leq\ i\ \leq\ N $ に対して、$ P_i $ を次のように定めます。

- $ H_j\ >\ H_i $ を満たすような整数 $ j\ (1\ \leq\ j\ <\ i) $ が存在する場合はそのような $ j $ の最大値、存在しない場合は $ -1 $ とする

全てのビルの高さの組み合わせを考えるとき、 $ P $ としてありうる整数列の個数を $ 1000000007 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ X_i\ \leq\ 10^5 $
- 入力は全て整数である

### Sample Explanation 1

$ H $ としては、次の $ 6 $ 通りが考えられます。 - $ H\ =\ (1,\ 1,\ 1) $ のとき、$ P $ は $ (-1,\ -1,\ -1) $ である - $ H\ =\ (1,\ 2,\ 1) $ のとき、$ P $ は $ (-1,\ -1,\ 2) $ である - $ H\ =\ (2,\ 1,\ 1) $ のとき、$ P $ は $ (-1,\ 1,\ 1) $ である - $ H\ =\ (2,\ 2,\ 1) $ のとき、$ P $ は $ (-1,\ -1,\ 2) $ である - $ H\ =\ (3,\ 1,\ 1) $ のとき、$ P $ は $ (-1,\ 1,\ 1) $ である - $ H\ =\ (3,\ 2,\ 1) $ のとき、$ P $ は $ (-1,\ 1,\ 2) $ である よって、$ P $ としてありうる整数列は $ (-1,\ -1,\ -1),\ (-1,\ -1,\ 2),\ (-1,\ 1,\ 1),\ (-1,\ 1,\ 2) $ の $ 4 $ 個です。

### Sample Explanation 2

$ H $ としては、次の $ 2 $ 通りが考えられます。 - $ H\ =\ (1,\ 1,\ 1) $ のとき、$ P $ は $ (-1,\ -1,\ -1) $ である - $ H\ =\ (1,\ 1,\ 2) $ のとき、$ P $ は $ (-1,\ -1,\ -1) $ である よって、$ P $ としてありうる整数列は $ 1 $ 個です。

## 样例 #1

### 输入

```
3
3 2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
5
2 2 2 2 2```

### 输出

```
16```

## 样例 #4

### 输入

```
13
3 1 4 1 5 9 2 6 5 3 5 8 9```

### 输出

```
31155```

# 题解

## 作者：syzf2222 (赞：9)

题意：有 $n$ 栋楼，第 $i$ 栋楼的高度 $h_i$ 在 $[1,x_i]$ 中随机。对于 $i\in [1,n]$ 定义 $p_i$ 为若 $h_i$ 为前缀最大值则 $p_i=-1$，否则 $p_i$ 为前面离 $i$ 最近的比 $i$ 高的位置。求 $p$ 的种类数。

题解：不难，直接过了。这个数据范围，必然是区间 $dp$。本来我还考虑前缀最大值划分，既然是区间 $dp$，那直接上最大值划分就好了。令 $k$ 为区间 $[l,r]$ 的最后一个最大值的位置，那么 $[k+1,r]$ 的取值必须小于 $h_k$，所以 $p$ 也不小于 $k$，是一个子结构，前缀当然也是一个子结构。设 $dp_{l,r,v}$ 表示区间 $[l,r]$ 内 $h$ 取值不大于 $v$ 的答案。然而 $v$ 很大，然而发现 $v$ 一定可以表示为 $x_a-b$，其中 $a,b\leqslant n$，于是直接 $O(n^4)$ 就过了。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=105;
int dp[N][N][N][N];bool vis[N][N][N][N];
int n,a[N];
inline int dfs(int l,int r,int p,int dt){
	if(l>r)return 1;if(a[p]==dt)return 0;
	if(vis[l][r][p][dt])return dp[l][r][p][dt];
	vis[l][r][p][dt]=true;int res=0;
	for(int k=l;k<=r;k++)
		if(a[p]-dt>=a[k])res=(res+1ll*dfs(l,k-1,k,0)*dfs(k+1,r,k,1))%mod;
		else res=(res+1ll*dfs(l,k-1,p,dt)*dfs(k+1,r,p,dt+1))%mod;
	dp[l][r][p][dt]=res;return res;
}
int main(){
	n=read();a[0]=inf;
	for(int i=1;i<=n;i++)a[i]=read();
	printf("%d\n",dfs(1,n,0,0));
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：NobleNumbat (赞：7)

校内模拟赛考到了，在纸上写了一个对的转移式，结果当时看着不太对就放弃这题了。

写篇题解纪念一下这个唐氏操作。

先考虑整个序列的最大值位置（相同的算后面的），那么最大值对应的 $P$ 一定是 $-1$。所以若最大值位置不同，生成的 $P$ 一定不同。这时看前面半段，后面的最大值对它没有任何限制；后面的半段，整段的最大值限制了它的最大值。

所以设 $f_{l,r,x}$ 表示区间 $l,r$，所有数值小于等于 $x$ 且满足限制，所生成的 $P$ 的方案数。转移直接枚举最大值点即可。转移式：

$$f_{l,r,x}=\sum f_{l,k-1,x}\cdot f_{k+1,r,x-1}$$

但是这里的 $x$ 可能很大。我们发现序列里面一共只有 $n$ 个数，那么大于 $n$ 的数是没有用的。直接把输入的 $X_i$ 对 $n$ 取 $\min$ 即可。

代码十行就够了。

```cpp
using mint = atcoder::modint1000000007;
mint f[102][102][101];
int a[101], n;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = min(a[i], n);
    for (int i = 0; i <= n; i++) for (int k = 0; k <= n; k++) f[i + 1][i][k] = 1;
    for (int i = n; i; i--) for (int j = i; j <= n; j++) for (int k = 1; k <= n; k++) for (int p = i; p <= j; p++) f[i][j][k] += f[i][p - 1][min(k, a[p])] * f[p + 1][j][min(k, a[p]) - 1];
    cout << f[1][n][n].val() << endl;
}
```

---

## 作者：tzl_Dedicatus545 (赞：4)

怎么题解状态全都一样啊/cf/cf/cf，给个更直观的做法！

显然 $p$ 排列和 $a$ 的笛卡尔树构成双射，然后对于相等的值，我们取最右边的作为树根，容易证明这样是正确的。

对于一颗笛卡尔树，为了不重不漏的计数，我们钦定 $b_u=\max\{b_{lc},b_{rc}+1\}$（$b$ 是笛卡尔树上的权值）

容易证明 $\max b \leq n$ ，所以复杂度就全对了！

我们定义 $f_{l,r,k}$ 代表当前笛卡尔树区间是 $[l,r]$，$b_{rt}=k$ 的方案数（$rt$ 为根）。

转移可以通过枚举 $rt$ 方便的完成。

复杂度 $O(n^4)$。

---

## 作者：FZzzz (赞：3)

下面把原题面中的 $p_i=-1$ 改为 $p_i=0$。

考虑某个 $p$ 能否被生成。如果我们连一条 $(i,p_i)$ 的边，那么这构成了一棵以 $0$ 为根的树。考虑生成这个 $p$ 的 $h$ 需要满足什么条件，一个点的 $h$ 值需要不小于它左边的兄弟，并且大于它的儿子。

那么对于一个固定的 $p$，令 $a_i$ 为 $i$ 左边的第一个兄弟，$b_i$ 为 $i$ 最靠右的儿子，$c_i=\max\{c_{a_i},c_{b_i}+1\}$（若 $a_i$ 不存在则看作 $c_{a_i}=0$，$b_i$ 同理），显然 $c$ 是良定义的。那么可以证明 $c$ 就是一个合法的 $h$，并且对于任意合法的 $h$ 都有 $h_i\ge c_i$ 。于是我们只需要比较 $c_i$ 和 $x_i$ 即可判定这个 $p$ 合不合法。

现在回到原题，我们设计 dp：令 $f_{l,r,k}$ 表示 $[l-1,r]$ 这个区间形成了一棵树，且 $c_{b_{l-1}}\le k$ 时，$[l,r]$ 的 $p$ 的方案数。注意 $k$ 这一维只需要开到 $n$。枚举 $b_{l-1}$ 即可转移，时间复杂度 $O(n^4)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=100+5;
int n,a[maxn];
const ll mod=1e9+7;
ll f[maxn][maxn][maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) f[i+1][i][j]=1;
	for(int i=n;i>0;i--) for(int j=i;j<=n;j++) for(int k=1;k<=n;k++)
		for(int x=i;x<=j;x++){
            int p=min(k,a[x]);
			f[i][j][k]=(f[i][j][k]+f[i][x-1][p]*f[x+1][j][p-1]%mod)%mod;
		}
	printf("%lld\n",f[1][n][n]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：Graygoo (赞：2)

这么菜的题题解咋写成这个鬼样子。~~（点名 @Daniel_lele，单调栈树这个名词是你发明的吗)~~
  
  经常写线性笛卡尔树建树的朋友们都知道，我们只需要跑一次题面所述过程就能建出一棵笛卡尔树。
  
  同时如果我们有一棵笛卡尔树，求出向前第一个更大值更是轻而易举的事情，因此不难看出 **题面这个数组和一个笛卡尔树的形态形成双射关系**。
  
  当然还有一些细节要解决。比如，这个笛卡尔树对于相同值是怎么处理的？因为这个数组给出的是第一个严格大于的值，所以相当于把单调栈里所有 **不大于它** 的后缀最大值全部弹掉了，也就说明这棵笛卡尔树对相同值的处理是 **取最后一个最大值作为树根**。
  
  然后就可以随便区间 dp 了，dp 部分太过沙比不予书写，唯一可能值得注意的部分是，由于对于一组大小关系我们总能进行离散化使值不大于 $n$，因此 $X$ 数组可以直接和 $n$ 取 $\min$，这样复杂度就正确了。

---

## 作者：一只绝帆 (赞：2)

## 背景（建议略过）

SD 二轮省集 [@H6_6Q](https://www.luogu.com.cn/user/157462) 讲了这个题，我知道 DP 式子后满怀欣喜地调了3h……

当时觉得人生一片灰暗，已知 DP 式子都不会写 DP 题，结果后来发现 [@H6_6Q](https://www.luogu.com.cn/user/157462) 讲错了。

这诺大的一个 SD 省集竟然需要轮到我这样的垫底人来指出错误，大家都不屑于切黑了/kk。

![](https://cdn.luogu.com.cn/upload/image_hosting/yreg317n.png)

# 正题

先看题意：一个不定序列，每个数在 $[1,x_i]$ 间，对这个序列维护一个新数组 $p$，满足 $p_i$ 为 $i$ 前面第一个大于 $a_i$ 的位置，没有则为 $-1$。

对 $p$ 计数。

$n\leq100,x_i\leq10^5$

一个显然的结论是 $x_i$ 这么大啥用没有，因为我们 $p$ 看的是大小关系，而不是具体的值，所以我们对所有的 $a$ 序列离散化一下就能大大减少状态数了。

比较容易看出离散化之后 $x_i\leq n$。

看这个 $n\leq100$ 就知道一般是区间 DP 没跑了，我们设 $f_{l,r,x}$ 为区间最靠右的最大值 $\leq x$ 时的方案数。

转移枚举最右侧最大值，很容易推出来：

$$f_{l,r,mx}\gets \sum_{k}f_{l,k-1,mx}\times f_{k+1,r,mx-1}$$

由于是最右侧的最大值，那么右侧的最大值就要比当前最大值少 $1$。

[@H6_6Q](https://www.luogu.com.cn/user/157462) 讲课的时候讲右侧最大值讲成了左侧最大值并推了一个对称的式子，然而实际上是错的。

他对此给出了一个很有道理的解释，我们这里直接引用：

![](https://cdn.luogu.com.cn/upload/image_hosting/25f4lj09.png)

AC Code（毒瘤码风）：

```cpp
// Problem: AT_arc104_f [ARC104F] Visibility Sequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc104_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=getchar();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return w?-s:s;
}
const int N=105,p=1e9+7;
using ll=long long;
ll f[N][N][N];
int n,x[N];
int main() {
	n=read();
	F(i,1,n) x[i]=min(read(),n);
	F(l,1,n) F(mx,1,n) f[l][l][mx]=1;
	F(len,2,n) F(l,1,n) {
		int r=l+len-1;if(r>n) break;
		F(k,l,r) F(mx,1,n) (f[l][r][mx]+=(k>l?f[l][k-1][min(mx,x[k])]:1)*(k<r?f[k+1][r][min(mx,x[k])-1]:1)%p)%=p;
	}
	cout<<f[1][n][n]<<endl;
	return 0;
}
```

希望能对想补这题但误入了歧途的 SD 同学们有所帮助/kk。

---

## 作者：_Cheems (赞：2)

感觉没必要硬套笛卡尔树，反而使问题复杂化了。不过思路还是相似的，考虑最大值分治。

这是有效的，因为最大值在不同位置 $pos$ 时，$P$ 显然不同：考虑 $pos_1<pos_2$ 分别是最大值时，对于前者，$pos_2$ 必然向 $[pos_1,pos_2-1]$ 有边；对于后者，$pos_2$ 不可能向 $[1,pos_2-1]$ 有边。两两不同，不重不漏。

注意一下，本题可能有重复元素，所以“最大值”定义为相同的情况尽量向右取，否则上面讨论不成立。

转移十分容易，考虑 $f_{l,r,H}$ 表示区间 $[l,r]$，值域在 $[1,H]$ 时的方案数，枚举最大值位置 $l\le pos\le r$，那么此时新值域为 $H_2=\min(H,x_{pos})$，有 $f_{l,pos-1,H_2}\times f_{pos+1,r,H_2-1}$。

注意到 $x$ 很大，不妨离散化一下，实际上，对 $n$ 取 $\min$ 即可。

记忆化搜索实现，注意一下边界处理，复杂度 $O(n^4)$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + b) % mod
const int N = 1e2 + 5, mod = 1e9 + 7;
int n, x[N], mx;
int f[N][N][N], vis[N][N][N];

inline int dfs(int l, int r, int H){
	if(l > r) return 1;
	if(H < 1) return 0;
	if(vis[l][r][H]) return f[l][r][H];
	vis[l][r][H] = 1;
	for(int pos = l; pos <= r; ++pos){
		int H2 = min(x[pos], H);
		ADD(f[l][r][H], dfs(l, pos - 1, H2) * dfs(pos + 1, r, H2 - 1) % mod);
	}
	return f[l][r][H];
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%lld", &x[i]), x[i] = min(x[i], n), mx = max(mx, x[i]);
	cout << dfs(1, n, mx);
	return 0;
}
```

---

## 作者：BigSmall_En (赞：1)

### [[ARC104F](https://www.luogu.com.cn/problem/AT_arc104_f)] Visibility Sequence

> 给一个长为 $n$ 的数列 $h_{1\dots n}$，第 $i$ 项在 $[1,h_i]$ 中选一个数，得到数列 $x_{1\dots n}$。
>
> 再构造一个数列 $p_{1\dots n}$，$p_i=\max j(j<i,x_j>x_i)$，若不存在这样的 $j$，$p_i=-1$。
>
> 求能构造出多少种 $p$。
>
> $n\leq 100,h_i\leq 10^5$。

显然 $h_i$ 可以很大，但是大于 $n$ 的时候是没有意义的，因为我们只需要看 $x$ 的相对大小。所以可以对 $n$ 取 $\min$（因为算上 $-1$ 之后至多有 $n+1$ 个不同的值，为 $h_i=n$ 的时候就已经能够保证这些值全部被取到）。

考虑 $i$ 与 $p_i$ 之间之间连边，如果 $p_i=-1$ 不妨将其视作一个编号为 $0$ 的点。容易发现构成了一颗树。将 $0$ 号点视为树根，发现这棵树具有以下性质性质。

- 子树根的编号最小且 $x$ 值大于其子树内所有点的 $x$ 值，根据定义可以得到。
- 子树内点的标号连续，即不能出现 $i<j<k<l$，$p_k=i,p_l=j$ 的情况，容易发现 $p_k=i$ 说明 $x_i>x_k>x_j$，而 $p_l=j$ 说明了 $x_j>x_l>x_k$，两者矛盾。
- 子树内深度相同的节点（即兄弟节点）中，编号越大的节点 $x$ 值越大（否则这些节点之间就会连边了）。

于是我们定义 $f_{l,r,k}$ 为区间 $[l,r]$ 构成一颗以 $l$ 为根的树且 $h_l=k$ 的方案数，定义 $g_{l,r,k} $ 为期间 $[l,r]$ 构成了一个最大的数为 $k$ 的森林的方案数。同时定义 $sf$ 和 $sg$ 为 $f,g$ 第三维的前缀和。得到转移：
$$
\begin{aligned}
f_{l,r,k}&\gets g_{l+1,r,k-1} \quad k\leq h_l\\
g_{l,r,k}&\gets f_{l,r,k}\quad k\leq h_l\\
g_{l,r,k}&\gets g_{l,r,k} +\sum_{i=l}^{r-1} sg_{l,i,k}\times f_{i+1,r,k} \quad k\leq h_{i+1}\\
g_{l,r,k}&\gets g_{l,i,k} +\sum_{i=1}^{r-1}g_{l,i,k}\times sf_{i+1,r,k-1}\quad k\leq h_{i+1}
\end{aligned}
$$
第一个和第二个式子表示 $l$ 节点作为区间 $[l,r]$ 的树根。

第三个式子 $f_{i+1,r,k}$ 保证了森林中至少有一个点为 $x=k$，同时也保证了不会算重。

第四个式子 $sf_{i+1,r,k-1}$ 的 $k-1$ 是为了保证第三条性质。

初始状态 $f_{i,i,1}=g_{i,i,1}=1$，答案状态 $sg_{1,n,n}$。

具体实现见代码。

```cpp
using namespace modulo;
using namespace FastIO;

int n,h[N];
ll f[N][N][N],g[N][N][N],sf[N][N][N],sg[N][N][N];
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		h[i]=read();
		h[i]=min(h[i],n);
	}
	for(int i=1;i<=n;++i){
		f[i][i][1]=g[i][i][1]=1;
		for(int j=1;j<=n;++j)
			sf[i][i][j]=sg[i][i][j]=1;
	}
	for(int len=2;len<=n;++len){
		for(int l=1,r=len;r<=n;++l,++r){
			for(int k=1;k<=h[l];++k)
				f[l][r][k]=g[l][r][k]=g[l+1][r][k-1];
			for(int i=l;i<r;++i){
				for(int k=1;k<=h[i+1];++k){
					g[l][r][k]=add(g[l][r][k],mul(sg[l][i][k],f[i+1][r][k]));
					g[l][r][k]=add(g[l][r][k],mul(g[l][i][k],sf[i+1][r][k-1]));
				}
			}
			for(int i=1;i<=n;++i){
				sf[l][r][i]=add(sf[l][r][i-1],f[l][r][i]);
				sg[l][r][i]=add(sg[l][r][i-1],g[l][r][i]);
			}
		}
	}
	printf("%lld\n",sg[1][n][n]);
	return 0;
}
```

#### 后记

写得很烂。

同时感谢这篇[题解](https://www.cnblogs.com/rainybunny/p/13827204.html)对我的启发。

---

## 作者：daniEl_lElE (赞：0)

注意到 $x_i>n$ 没有意义。

容易发现建出的就是单调栈树，于是考虑子树转为区间去 dp。

考虑 $dp_{i,j,k}$ 表示 $[i,j]$ 区间整个是一个子树，$h_i=k$ 的方案数。

转移的时候添加一个辅助 dp 数组 $f_{i,j,k}$ 表示 $[i,j]$ 区间是多个子树的并，$h_i=k$ 的方案数。

考虑转移，显然 $dp_{i,j,k}=dp_{i+1,j,\min(k,x_i)-1}+f_{i+1,j,\min(k,x_i)-1}$，也就是钦定 $i$ 位置大于后面。

$f$ 的转移考虑钦定新拼上的后一段，前一段的 $k$ 应当比后一段小或相等。故 $f_{i,j,k}=\sum_{p=i}^{j-1}(dp_{i,p,\min(k,x_{p+1})}+f_{i,p,\min(k,x_{p+1})})\times dp_{p+1,j,\min(k,x_{p+1})}$。

总复杂度 $O(n^4)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int dp1[105][105][105],dp2[105][105][105];
signed main(){
	int n; cin>>n; int x[n+1]; for(int i=1;i<=n;i++) cin>>x[i];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp1[i][i][j]=1;
	for(int len=2;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
			for(int k=1;k<=n;k++){
				(dp1[l][r][k]+=dp1[l+1][r][min(k,x[l])-1]+dp2[l+1][r][min(k,x[l])-1])%=mod;
			} 
			for(int k=1;k<=n;k++){
				for(int p=l;p<r;p++){
					(dp2[l][r][k]+=(dp1[l][p][min(k,x[p+1])]+dp2[l][p][min(k,x[p+1])])*dp1[p+1][r][min(k,x[p+1])])%=mod;
				}
			}
		}
	}
	cout<<(dp1[1][n][n]+dp2[1][n][n])%mod;
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

对于一个长度为 $N$ 的序列 $H$，可以通过如下方式构造一个序列 $P$：

若存在 $j \in \left[1, i\right)$，使得 $H_j > H_i$，则 $P_i = \max\limits_{j \in \left[1, i\right) \land H_j > H_i} j$，否则 $P_i = -1$。

给定一个长度为 $N$ 的序列 $X$，求所有满足如下条件的 $H$ 序列可以构造出的 $P$ 序列的方案数：

> $\forall i \in \left[1, N\right], H_i \in \left[1, X_i\right]$

对 $10^9 + 7$ 取模。

$1 \le N \le 100, 1 \le X_i \le 10^5$。

## 题解

考虑从 $i$ 向 $P_i$ 连边，发现会连成一个森林，考虑将 $H_0$ 设为 $+\infty$，这样就可以形成一颗以 $0$ 为根的树。可以发现其一定有如下性质：

1. 对于任意节点 $u$，有 $\forall v \in \operatorname{subtree}_u \Rightarrow H_u > H_v$

> 证明：
> 对于任意节点 $x$，有 $H_{fa_x} > H_{x}$，通过不等式的传递性可证。

2. 一定存在一种 $\tt{DFS}$ 方式使得 $\forall i \in \left[1, N\right]$，有 $\operatorname{dfn}(i) = i$

> 证明：
> 考虑 $\tt{DFS}$ 到节点 $u$ 后，下一个访问的节点是否可以是 $u + 1$。
> - 若 $H_u > H_{u + 1}$，那么 $u$ 和 $u + 1$ 之间一定有边相连；
> - 否则对于任意 $i > u + 1$，其不会向 $u$ 连边，所以在 $\tt{DFS}$ 过程中，不会访问其他节点。

3. 对于节点 $u$ 的儿子节点序列 $v_1 < v_2 < \cdots v_k $，有 $\forall i \in \left[1, k\right], H_{v_i} \le H_{v_{i + 1}}$

> 证明：
> 考虑若存在 $i < j$，使得 $H_{v_i} > H_{v_j}$，那么 $v_i$ 和 $v_j$ 之间一定有边相连，矛盾。

4. 对于节点 $u$ 的儿子节点序列 $v_1 < v_2 < \cdots v_k $，有 $\forall i \in \left[1, k\right], H_{v_i} < H_u$

> 证明：
> 考虑若存在 $i$，使得 $H_{v_i} \ge H_u$，那么 $v_i$ 和 $u$ 之间一定没有边相连，矛盾。

至此我们可以得出对于一个节点 $u$，有 $H_u \ge \max\left\{\max\limits_{v \in \operatorname{son}_u}H_v + 1,\max\limits_{v \in \operatorname{brother}_u \land v < u}H_v\right\}$。

考虑如何在给定 $P$ 序列即树的形态的情况下构造出一组合法的 $H$ 或报告无解。发现从叶子节点向上构造并直接将 $H_u$ 的值取至下界一定不劣，因此我们就得出了一个基于贪心的构造方法。

同时我们可以发现按此方法构造出的 $H$ 序列其值不超过 $N$，因此若 $X_i > N$ 那么使其对 $N$ 取 $\min$ 即可。 

考虑按此方法进行 $\tt{DP}$，设 $f_{l, r, x}$ 表示由编号区间 $\left[l, r\right]$ 中的点构成的树且 $l$ 节点作为根节点有 $H_l = x$ 的方案数，$g_{l, r, x}$ 表示由编号区间 $\left[l, r\right]$ 中的点构成的森林且对于编号最大的根节点 $u$ 有 $H_u = x$ 的方案数。

初始状态为 $\forall i \in \left[1, N\right], f_{i, i, 1} = 1$。

接下来考虑如何转移，首先我们有

$$f_{l, r, x} = g_{l + 1, r, x - 1}$$

然后考虑 $g_{l, r, x}$ 的转移，我们可以枚举其最后一棵子树的编号区间和根节点权值，有

$$g_{l, r, x} = \sum\limits_{m = l}^{r - 1}\sum\limits_{\max\limits\left\{a, b\right\} = x} g_{l, m, a} \times f_{m + 1, r, b}$$

考虑若 $b = x$，那么使得枚举的子树作为其最右侧的子树即可；反之则有 $a = x$，使得枚举的子树并入其最右侧的子树即可。

最后答案即为 $\sum\limits_{i = 1}^{N}g_{1, N, i}$。

使用前缀和优化转移即可做到 $\mathcal{O}(N^4)$ 的时间复杂度，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<ValueMatrix> ValueCube;

namespace MODINT {
    constexpr valueType MOD = 1e9 + 7;

    template<typename T1, typename T2, typename T3 = valueType>
    void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a + b;

        if (a >= mod)
            a -= mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a - b;

        if (a < 0)
            a += mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
        return a + b >= mod ? a + b - mod : a + b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
        return a - b < 0 ? a - b + mod : a - b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
        return (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
        a = (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
        T1 result = 1;

        while (b > 0) {
            if (b & 1)
                Mul(result, a, mod);

            Mul(a, a, mod);
            b = b >> 1;
        }

        return result;
    }
}// namespace MODINT

using namespace MODINT;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector H(N + 1);

    for (valueType i = 1; i <= N; ++i) {
        std::cin >> H[i];

        H[i] = std::min(H[i], N);
    }

    auto ModSum = [](valueType const &a, valueType const &b) -> valueType {
        return sum(a, b, MOD);
    };

    ValueCube F(N + 1, ValueMatrix(N + 1, ValueVector(N + 1, 0)));
    ValueCube G(N + 1, ValueMatrix(N + 1, ValueVector(N + 1, 0)));
    ValueCube SumF(N + 1, ValueMatrix(N + 1, ValueVector(N + 1, 0)));
    ValueCube SumG(N + 1, ValueMatrix(N + 1, ValueVector(N + 1, 0)));

    for (valueType i = 1; i <= N; ++i) {
        F[i][i][1] = 1;
        G[i][i][1] = 1;

        std::partial_sum(F[i][i].begin(), F[i][i].end(), SumF[i][i].begin(), ModSum);
        std::partial_sum(G[i][i].begin(), G[i][i].end(), SumG[i][i].begin(), ModSum);
    }

    for (valueType len = 1; len <= N; ++len) {
        for (valueType l = 1; l + len <= N; ++l) {
            valueType const r = l + len;

            for (valueType k = 1; k <= H[l]; ++k) {
                F[l][r][k] = G[l + 1][r][k - 1];
                G[l][r][k] = G[l + 1][r][k - 1];
            }

            for (valueType mid = l; mid < r; ++mid) {
                for (valueType k = 1; k <= H[mid + 1]; ++k) {
                    Inc(G[l][r][k], mul(G[l][mid][k], SumF[mid + 1][r][k - 1]));
                    Inc(G[l][r][k], mul(SumG[l][mid][k - 1], F[mid + 1][r][k]));
                    Inc(G[l][r][k], mul(G[l][mid][k], F[mid + 1][r][k]));
                }
            }

            std::partial_sum(F[l][r].begin(), F[l][r].end(), SumF[l][r].begin(), ModSum);
            std::partial_sum(G[l][r].begin(), G[l][r].end(), SumG[l][r].begin(), ModSum);
        }
    }

    std::cout << SumG[1][N][N] << std::endl;

    return 0;
}
```

---

## 作者：Larry76 (赞：0)

## 前言

更好的阅读体验：[隙间传送](https://www.cnblogs.com/larry76/p/17602490.html)

在这里首先感谢一下题解区的 [FZzzz](https://www.luogu.com.cn/user/174045)，本人的题解思路主要是基于他并给出了自己的理解。

如非特殊说明，本题解中的数学符号原则上与题目中一致。

## 题目分析

需要转化的喵喵题。

我们需要把原问题转化成一个图论计数问题，然后剩下的就很好办了。

好，首先让我们修改一下题目的要求，将不存在的情况设为 $p_i = 0$，这样就可以使得我们的 $p_i$ 的值只可能取到自然数集合中连续的一段 $[0,n-1]$ 了。

考虑连边 $(i,p_i)$，我们首先能得到一个十分显然的性质，就是最终连边连出来的图必定没有环，证明显然，考虑偏序关系不允许出现环即可。

但是这个性质不是很强，我们还可以进一步得到相比更强的性质，就是连出来的图必定是一棵树，这个证明考虑 $p_i$ 的值只会取到 $[0,i-1]$ 而已，又因为不会出现环，故现在此时连出来的是一棵树，并且是以 $0$ 为根节点的树。

现在让我们观察一下每个节点上 $h_i$ 的值，不难发现兄弟之间左方的兄弟的 $h$ 值 $\le$ 右方的兄弟的 $h$ 值，且当前节点的 $h$ 值一定大于他的儿子们。证明显然，考虑如果左方的兄弟大于自己，则自己会被左方的兄弟支配，变成他的儿子，故左右兄弟之间是 $\le$，考虑如果自己的儿子大于等于自己，那么它必定会成为自己的兄弟甚至是祖先的兄弟，故父亲儿子之间是 $\gt$。

让我们定义 $a_i$ 为 $i$ 左边第一个的兄弟，让 $b_i$ 为 $i$ 最右边的儿子，设 $c_i=\max\{c_{a_i} , c_{b_i} + 1\}$，则此时 $c$ 必定是 $h$ 的构造方案之一（证明考虑兄弟之间的偏序关系和父亲儿子之间的偏序关系），并且对于任意的 $h$ 我们都有 $h_i \ge c_i$，于是可以比较 $c_i$ 与 $x_i$ 就可以看出 $p$ 是否合法。

最后，设 $dp_{i,j,k}$ 为区间 $[i-1,j]$ 形成了一棵树，且 $c_{b_{i-1}} \le k$ 时，$[i,j]$ 的方案数，时间复杂度 $\mathcal O(n^4)$。

## 代码实现

这里只给出了代码的关键部分，其余部分还恳请读者自行实现。

```cpp
int n;

int X[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE][MAX_SIZE];

void main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        X[i] = read();
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i + 1][i][j] = 1;
        }
    }
    for (int i = n; i >= 1; --i) {
        for (int j = i; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int p = i; p <= j; p++) {
                    int q = min(k, X[p]);
                    dp[i][j][k] =
                        mt.add(dp[i][j][k],
                               mt.mul(dp[i][p - 1][q], dp[p + 1][j][q - 1]));
                }
            }
        }
    }
    printf("%lld\n", dp[1][n][n]);
    return void();
}
```

---

