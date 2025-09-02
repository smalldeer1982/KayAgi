# [ABC252G] Pre-Order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc252/tasks/abc252_g

頂点 $ 1 $ を根とした $ N $ 頂点の根付き木があります。頂点には $ 1,2,\ldots,N $ の番号がついています。

根から始めて深さ優先探索を行い、行きがけ順で頂点番号を記録したところ、順に $ P_1,P_2,\ldots,P_N $ となりました。   
 ただし、深さ優先探索では、現在の頂点に複数の子がある場合、まだ探索していない頂点のうち最も番号が小さい頂点へ移動することとします。

 行きがけ順とは 根から始めて次の手順を繰り返して根付き木上の頂点を列挙します。 2. 現在いる頂点 $ u $ をまだ記録していなければ記録する。
3. その後、$ u $ の子のうち、まだ探索していないものがあればその頂点に移動する。
4. そうでない時、$ u $ が根であれば探索を終了する。そうでなければ、$ u $ の親に移動する。
 この時、列挙された頂点を順に並べたものが行きがけ順です。 

条件をみたす根付き木として考えられるものの数を $ 998244353 $ で割った余りを求めてください。  
 ただし、ある $ 2 $ つの「頂点 $ 1 $ を根とした $ N $ 頂点の根付き木」が異なるとは、ある根以外の頂点が存在して、その親が異なる事を言います。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ P_i\leq\ N $
- $ P_1=1 $
- $ P_i $ はすべて異なる
- 入力は全て整数

### Sample Explanation 1

条件をみたす根付き木としては次の $ 3 $ 通りが考えられます。よって、 $ 3 $ を出力します。 !\[\](https://img.atcoder.jp/abc252/554e2b202029960276be7564aaa0576b.png) また、次のような木は考えられません。頂点 $ 2 $ の子の頂点のうち、番号の小さい頂点 $ 3 $ が頂点 $ 4 $ より先に探索され、 このときの行きがけ順は $ 1,2,3,4 $ となるからです。 !\[\](https://img.atcoder.jp/abc252/a6f35bb1addccc64564d36b812669d55.png)

## 样例 #1

### 输入

```
4
1 2 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
8
1 2 3 5 6 7 8 4```

### 输出

```
202```

# 题解

## 作者：qwerty12346 (赞：8)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc252_g)

## 题意

就是求满足条件的树的方案数，并对 $998244353$ 取模。

## 做题方法

直接用区间动态规划来做这题。再在循环里求 $i$ 和 $j$ 的中心值将这个中心值定为 $k$。然后再嵌一个循环来递推 $dp_{j,k}$ 的值。

## 状态定义

$dp_{i,j}$ 表示区间 $[i,j]$ 满足条件的树的方案数。

## 状态转移方程

枚举在以 $i$ 为虚拟根的情况下子树的点 $k$，则会有 $dp_{i,j}=(dp_{i,j}+dp_{i+1,k}×dp_{k,j})$ 个。

## 边界处理

直接循环让 $dp_{i,i}$ 的初始值赋为 $1$。

## 目标

求 $dp_{1,n}$ 的值。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long n,a[10005],f[1005][1005];//定义dp数组
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        f[i][i]=1;//赋初始值
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j+i-1<=n;j++)
	{
	    int k=j+i-1;
	    for(int l=j+1;l<=n;l++)if(l==k||a[j+1]<a[l+1])f[j][k]=(f[j][k]+f[j+1][l]*f[l][k])%mod;//状态转移方程
	}
    }
    cout<<f[1][n]<<endl;
    return 0;
}
```


---

## 作者：max666dong123 (赞：5)

## 题意

存在一棵 $n$ 个点的树，给定序列 $P_n$ 表示树的先序遍历，特别地，已知当一个节点有多个儿子的时候会优先遍历编号较小的儿子。求满足条件的树的方案数。对 ``998244353`` 取模。

## 思路

用 ``区间 DP`` 来做。

定义 $f_{i,j}$ 表示以 $i$ 为**虚拟根**，$P[i \sim j]$ 的方案数。

![](https://cdn.luogu.com.cn/upload/image_hosting/dfomn27b.png)

枚举 $i$ 的子树末尾 $k$，可以发现只有在 $k=r$ 或 $P_{i+1}<P_{k+1}$ 时才可以。

状态转移方程：

$$f_{i,j}=(f_{i,j}+f_{i+1,k} \times f_{k,j})\bmod 998244353$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N=5e2+10;
const int MOD=998244353;
int a[N],f[N][N];
int n;
signed main(){
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][i]=1;
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=len+l-1;
			for(int k=l+1;k<=n;k++){
				if(k==r||a[l+1]<a[k+1]){  
//					cout<<"YES"<<endl;
					
					f[l][r]=(f[l][r]+f[l+1][k]*f[k][r])%MOD;
//					cout<<f[l][r]<<" "<<l<<" "<<r<<endl;
				}
			}
		}
	}
	cout<<f[1][n];
	return 0;
}

```


---

## 作者：shinkuu (赞：3)

挺好的区间 dp。

如果简单地将 $dp_{i,j}$ 设为区间 $[i,j]$ 的前序遍历序列形成以 $i$ 为根的子树的方案，会发现一个点可能会有多个儿子，难以处理。所以设 $dp_{i,j,0/1}$ 为区间 $[i,j]$ 的前序遍历序列形成以 $i$ 为根的子树/前序遍历最先为 $i$ 的方案。$dp_{i,j,0}$ 转移的时候考虑枚举 $[i,k]$ 形成以 $i$ 为根的子树。则有：

$$dp_{i,j,0}=dp_{i,k,1}+dp_{k+1,j,0}$$

但是题目要求是先走编号小的点，则要求有 $p_i<p_{k+1}$。

对于 $dp_{i,j,1}$，则可以看作为一个点 $i$ 连向一棵或若干棵子树，则有：

$$dp_{i,j,1}=dp_{i+1,j,0}+dp_{i+1,j,1}$$

code：

```cpp
int n,m,e[N],dp[N][N][2];
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
		dp[i][i][0]=dp[i][i][1]=1;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;																							
			for(int k=i;k<j;k++){
				if(e[i]<e[k+1])
					dp[i][j][0]=(dp[i][j][0]+1ll*dp[i][k][1]*dp[k+1][j][0]%mod)%mod;
			}
			dp[i][j][1]=dp[i+1][j][0];
			dp[i][j][0]=(dp[i][j][0]+dp[i][j][1])%mod;
		}
	}
	printf("%d\n",dp[1][n][1]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：harmis_yz (赞：2)

## 分析

考虑区间 DP。

定义状态函数 $\mathit{f}_{l,r,1/0}$ 表示在 $P_l,P_{l+1},\dots,P_r$ 这些点中，$P_l$ 是或不是唯一（子）树根时的答案。

对于 $\mathit{f}_{l,r,1}$，$P_l$ 的第一个儿子一定是 $P_{l+1}$。所以有：$f_{l,r,1}=f_{l+1,r,1/0}$（$P_{l+1}$ 是或不是 $P_l$ 的唯一儿子的答案）。

对于 $\mathit{f}_{l,r,0}$，枚举一个中转点 $k$，表示 $P_l,P_{l+1},\dots,P_k$ 是一棵（子）树，$P_{k+1},P_{k+2},\dots,P_r$ 是若干棵（子）树。同 $f_{l,r,1}$，有：$f_{l,r,0}=\sum\limits_{k=l}^{r-1}f_{l,k,1} \times f_{k+1,r,1/0}[P_{l} \le P_{k+1}]$。因为两个的方案数是相互独立的，所以要乘起来。

答案很明显就是 $f_{1,n,1}$，初始化 $f_{i,i,1}=1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=505,p=998244353;
int n,P[N];
int f[N][N][2];

il void solve(){
	n=read();
	for(re int i=1;i<=n;++i) P[i]=read(),f[i][i][1]=1;
	for(re int l=n-1;l>=1;--l)
	for(re int r=l+1;r<=n;++r){
		f[l][r][1]=(f[l+1][r][0]+f[l+1][r][1])%p;
		for(re int k=l;k<r;++k) if(P[l]<=P[k+1]) 
			f[l][r][0]=(f[l][r][0]+f[l][k][1]*(f[k+1][r][0]+f[k+1][r][1])%p)%p;	
	} 
	printf("%lld\n",f[1][n][1]);
	return ;
}

signed main(){
	solve();
	return 0;
}

```


---

## 作者：A6n6d6y6 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc252_g)

## 问题描述
给定 $n$ 个点构成的多叉树的先序遍历，
输出有多少种树，答案对 $998244353$ 取模。

## 做题思路
考虑区间 DP。

对于区间 $[l,r]$ 有两种可能：
- $l$ 是这区间唯一子树的根；直接通过 $[l+1,r]$ 转移；
- $l$ 是这区间众多子树的根之一。枚举子树的结尾 $k$，通过 $[k+1,r]$ 转移（注意 $a_l<a_{k+1}$，因为优先遍历序号小的节点）。

不妨设 $f_{l,r,0/1}$ 示区间 $[l,r]$ 对应的树中 $l$ 是/否为区间根节点时子树的数量。

状态转移方程：

$$f_{l,r,1}=f_{l+1,r,0}+f_{l+1,r,1}$$

$$f_{l,r,0}=f_{l,k,1}\times(f_{k+1,r,0}+f_{k+1,r,1}),\forall a_l<a_{k+1}$$

显然，初始值为：$f_{l,l,1}=1$。最终答案：$f_{1,n,1}$。时间复杂度：$O(n^3)$。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e2+10,mod=998244353;
int n,a[maxn],f[maxn][maxn][2];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)f[i][i][1]=1;//初始化
    for(int i=1;i<=n;i++){
        for(int l=1,r=i;r<=n;l++,r++){
            f[l][r][1]=(f[l][r][1]+f[l+1][r][0]+f[l+1][r][1])%mod;
            for(int k=l;k<=r;k++){
                if(a[l]>=a[k+1])continue;
                f[l][r][0]=(f[l][r][0]+f[l][k][1]*(f[k+1][r][0]+f[k+1][r][1])%mod)%mod;
            }
        }
    }//DP
    cout<<f[1][n][1];//输出
    return 0;
}
```

---

## 作者：Leaper_lyc (赞：2)

简单提一下思路。

设 $f_{i,j}$ 表示区间 $[i,j]$ 合法的方案数。

对于先序遍历，我们知道序列的第一位就是根，第二位是第一个被遍历到的点。

显然，我们可以虚拟一个根 $p_i$，那么转移时考虑枚举在以 $p_i$ 为虚拟根的情况下子树的点 $p_k$，显然 $p_k>p_{i+1}$。

根据乘法原理，显然有 $f_{i,j}=f_{i,j}+f_{{i+1},k}\times f_{k,j}$。

那么我们便可以快乐地 AC 了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 505;
const int mod = 998244353;

int n;
int f[_][_];
int p[_];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		f[i][i] = 1;
	}
	for (int l = 2; l <= n; l++)
		for (int i = 1, j; i <= (n - l + 1); i++) {
			j = (i + l - 1);
			for (int k = i + 1; k <= n; k++)
				if (k == j || p[i + 1] < p[k + 1])
					f[i][j] = 1ll * (f[i][j] + 1ll * f[i + 1][k] * f[k][j] % mod) % mod;
		}
	cout << f[1][n];
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
很显然啊，是个区间 dp，那么我们就来搞懂动态规划的四要素即可。首先是状态定义，我们定义 $f_{i,j}$ 以 $p_i$ 为根，区间 $p_i\sim p_j$ 满足条件的方案数。然后，递归起点就是当 $i$ 等于 $j$ 时方案数为 $1$ 了。那么就到最难的状态转移方程了我们先打一个区间 dp 的模板，求出 $i$ 和 $j$ 还有 $l$ 长度（这个就不讲了），然后在 $i\sim j$ 之间枚举一个中间点为 $k$，那么我们就要用到乘法原理了，我们发现若 $j$ 等于 $k$ 或 $p_{i+1}\leq p_{k+1}$ 我们都可以分成两部分，然后将他们的方案数相乘在累加，所以 $f_{i,j}=f_{i,j}+f_{i+1,k}\times f_{k,j}$ 这里有一个难点就是为什么后面是 $f_{k,j}$ 而不是 $f_{k+1,j}$ 其实这里是因为我们不能确定后面有多少棵子树，那么就有可能一些树不是以 $p_{k+1}$ 为根的，所以我们这里回到定义就能明白为什么是虚拟根了吧！其实就是用 $p_{k}$ 将另一边的所有子树给综合在一起求方案数，因为根节点确定了所以就没有影响了。最后输出 $f_{1,n}$ 即可。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=510;
int n, p[N];
int f[N][N]; //1.状态函数f[i][j]:即以p[i]为根，区间p[i, j]满足条件的树的方案数
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>p[i];
	for(int i=1; i<=n; i++)//2.递推起点
		f[i][i]=1;
	for(int l=2; l<=n; l++)//3.递推关系
		for(int i=1; i+l-1<=n; i++) {
			int j=i+l-1;//先序遍历:即深度优先搜索，以p[i]为根，画图
			for(int k=i+1; k<=n; k++) //先搜索p[i]的编号最小的第一棵子树p[i+1, k]
				if(k==j || p[i+1]<p[k+1])//再搜索p[i]的后面的子树p[k+1, ..不知道棵数]
					f[i][j]=(f[i][j]+f[i+1][k]*f[k][j])%mod;//搜索后面的子树，方法等价于以p[k]为根,即f[k][j]
		}
	cout<<f[1][n]<<endl;//4.答案
	return 0;
}
```

还有一种解法。
# 思路
我们可以发现这是一道 Dp 题，然后我们就可以想如何定义状态，我们定义 $f_{i,j,0/1}$ 为点 $i\sim j$ 的方案数，然后 $0$ 表示不已 $i$ 为跟否则则为根。然后我们根据 $N\leq 500$ 可以知道为区间 dp，那么我们就思考如何转移。

- $f_{i,j,1}=f_{i+1,j,1}+f_{i+1,j,0}$ 因为我们的 $i$ 一定为根那么就可以忽略不计直接就等于 $i+1\sim j$ 的方案数。
- $f_{i,j,0}=f_{i,k,1}\times (f_{k+1,j,1}+f_{k+1,j,0})$ 这里我们枚举出第一棵树的最后一个节点，然后再乘上下一个开头到最后的方案数之和即可，但是这里有一个条件就是 $p_i\leq p_{k+1}$ 因为对于同一个层的先遍历小的，这里 $i$ 一定比 $k+1$ 先遍历到，所以要加上判断。

最后答案就为 $f_{1,n,1}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=510,mod=998244353;
int f[N][N][2];
int n,p[N];
fire main() {
	in(n);
	rep(i,1,n) in(p[i]);
	rep(i,1,n) f[i][i][1]=1;
	rep(l,2,n) {
		rep(i,1,n-l+1) {
			int j=i+l-1;
			f[i][j][1]=(f[i+1][j][1]+f[i+1][j][0])%mod;
			rep(k,i+1,j) if(p[i]<=p[k]) f[i][j][0]=(f[i][j][0]+f[i][k-1][1]*(f[k][j][0]+f[k][j][1]))%mod;
		}
	}
	cout<<f[1][n][1]<<endl;
	return false;
}

```

---

## 作者：_shine_ (赞：1)

### 1.题目大意
有一棵 $n$ 个结点的树，给定 $p_n$ 表示树的先序遍历。当一个节点有多个儿子的时候会优先遍历编号较小的儿子。求满足条件的树的方案数。对 $998244353$ 取模。
### 2.思路分析
考虑使用区间 DP 解决此题。

定义 $f_{i,j}$ 表示以 $p_i$ 为虚拟根，区间 $\left[i,j\right]$ 满足条件的树的方案数，枚举在以 $i$ 为虚拟根的情况下子树的点 $k$，则显然有 $f_{i,j}=\left(f_{i,j}+f_{i+1,k}\times f_{k,j}\right)$。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=998244353;
const int maxn=5e2+10;
int n,p[maxn];
int f[maxn][maxn];
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> p[i];
	}
	for(int i=1;i<=n;++i){
		f[i][i]=1;
	}
	for(int i=2;i<=n;++i){
		for(int j=1;i+j-1<=n;++j){
			int m=i+j-1;
			for(int k=j+1;k<=n;++k){
				if(k==m || p[j+1]<p[k+1]){
					f[j][m]=(f[j][m]+f[j+1][k]*f[k][m])%inf;
				}
			}
		}
	}
	cout << f[1][n] << endl;
	return 0;
} 
```


---

## 作者：Big_Dinosaur (赞：0)

设 $dp_{l,r}$ 为从 $l$ 到 $r$ 能构成若干能在同一根上放的子树的方案数。答案为 $dp_{2,n}$。

转移：

$$dp_{l,r}=\displaystyle \sum_{i=l+1}^{r+1} dp_{i+1,l-1}\times dp_{l,r}\times[a_i>a_l]$$。

道理很简单。判大小，因为当 $a_l>a_i$ 时，先序遍历不会先 $a_i$ 再 $a_l$。让 $[i+1,l-1]$ 内的结点在 $i$ 下，$[i,r]$ 的节点放 $a_i$ 右边，$a_i$ 的父亲下。

边界：

- $dp_{a,a}=1$。
- $dp_{a,b}=1(a>b)$。

---

## 作者：Furina_Saikou (赞：0)

感觉是真的蓝。
# 思路

我们设 $dp_{l,r}$ 表示区间 $[l,r]$ 以 $l$ 为根，以 $r$ 结尾的子树的方案数（但实际考虑的其实是区间 $[l+1,r]$，因为 $l$ 是不能改变位置的）。

初始状态将所以的 $dp_{i,i}$ 设为 $1$。

考虑从后往前枚举 $l$，再从 $l$ 往后枚举 $r$，这样枚举也能保证用到的区间都被求解过。接着枚举 $i$ 的子节点 $k$ 作为分割点（令人不解的是明明枚举到 $r$ 就行，为什么那么多人枚举到 $n$？这样显然是错的），因为两个小区间是独立的，所以合并成大区间时应考虑它们的 **乘积**，因此我们能得到状态转移方程 $dp_{l,r}=(dp_{l,r}+dp_{l+1,k}\times dp_{k,r})$。

DP 中的计数问题确实很让人头疼，我们要考虑什么情况是才是合法的，显然如果分割点 $k$ 正好是右端点 $r$ 是合法的，还有就是题目说先遍历子节点中小的点，所以建出来的树同级应是升序的，也就是要保证 $p_{l+1}<p_{k+1}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=514,mod=998244353;
int n,a[N],dp[N][N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i][i]=1;
	}
	for(int l=n-1;l;l--)
	{
		for(int r=l+1;r<=n;r++)
		{
			for(int k=l+1;k<=r;k++)
			{
				if(k==r||a[l+1]<a[k+1])
				{
					dp[l][r]=(dp[l][r]+dp[l+1][k]*dp[k][r])%mod;
				}
			}
		}
	}
	cout<<dp[1][n];
	return 0;
}
```

记得取模哦。

---

## 作者：Mirasycle (赞：0)

先序遍历就是 dfs 序，dfs 序的子树就是一段区间，所以我们考虑区间 dp。设 $dp_{i,j}$ 表示 $[i,j]$ 这一段的方案数。很套路的就得到类似于 $dp_{l,k} \times dp_{k+1,r} \to dp_{l,r}$ 这样子的方程，但是注意一下在计数 dp 里面一定要小心要不重不漏，也就说上述区间划分会造成多统计的，比如区间 $[1,2]~[3,4]~[5,6]$ 可以通过 $dp_{1,4} \times dp_{5,6}$ 产生，也可以通过 $dp_{1,2} \times dp_{3,6}$ 产生。

解决方法就是钦定第一个划分出来的区间不同即可，于是我们就要求划分出来的左区间单独形成一个子树，不能再被划分为多个子树。这里不需要再开辅助数组 $f$ 来单独计数。可以直接通过钦定区间最左边的一个数为根解决，这样子当 $[l,r]$ 进行划分的时候最先划出来的就是 $[l+1,k]$ 其中由于 $l+1$ 为根，所以第一个划分出来的区间只有一个子树，而为了让后面划分出来的右区间可以有形成多个区间的选择，我们这里可以创建一个虚根 $k$，使得有右区间 $[k+1,r] \to [k,r]$，这样子有了虚根之后就在虚根 $k$ 下面划分出多个子树了。

于是我们可以列出转移方程 $dp_{l,r}=\sum\limits_{k}dp_{l+1,k} \times dp_{k,r}$。转移条件是 $a_{l+1}<a_{k+1}$ 或者 $k=r$，为了满足先遍历小编号儿子的要求。

---

## 作者：Xiphi (赞：0)

板子题。设 $dp_{l,r}$ 表示满足 $p_l$ 到 $p_r$ 的合法的树的个数。考虑如何转移，前序遍历的性质之一是第一个恒为根，那么我们自然的想到可以枚举下一层第一个根是那个，设其为 $k$，则有 $dp_{l,r}\leftarrow dp_{l+1,k}\times dp_{k,r}$。

注意到这样会有问题，因为 $p_k$ 是必须要大于 $p_{l+1}$ 的，特判掉即可。

本人使用记忆化实现，代码很短。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int p=998244353;
int n,a[5005],dp[505][505];
int dfs(int l,int r){
	if(dp[l][r]) return dp[l][r];
	for(int k=l+1;k<=r;++k){
		if(k==r||a[l+1]<a[k+1]) dp[l][r]+=dfs(l+1,k)*dfs(k,r)%p,dp[l][r]%=p;
	}
	return dp[l][r];
}
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i],dp[i][i]=1;
    cout<<dfs(1,n);
	return 0;
}




```

---

## 作者：daniEl_lElE (赞：0)

区间 dp。

## 思路

考虑 $dp_{i,j}$ 表示用 $i\sim j$ 号点组成了一个树的方案数。

我们考虑一个节点可以有多个子树，故改变状态定义为 $dp_{i,j,0/1}$ 表示 $i\sim j$ 节点组成单独子树/一些并列的子树的方案数。

对于前者，我们只需要将 $dp_{i+1,j,0}+dp_{i+1,j,1}$ 转移至 $dp_{i,j,0}$ 即可，意思是以 $i$ 为目前的根并拼接若干个 $i\sim j$ 的子树。

对于后者，我们先钦定一个 $k$ 为中间点，将 $dp_{i,k}$ 和 $dp_{k+1,j}$ 的状态合并即可。

考虑如何不重复计算，我们可以选择其中一者固定为单独的一个子树，另一个为若干个子树即可。即若 $a_i<a_{k+1}$，$dp_{i,k,0}\times(dp_{k+1,j,0}+dp_{k+1,j,1})$ 可以转移到 $dp_{i,j,1}$。

总复杂度 $O(n^3)$。可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int dp[505][505][2];
signed main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) dp[i][i][0]=1;
	for(int len=2;len<=n;len++){
		for(int l=1;l<=n-len+1;l++){
			int r=l+len-1;
			dp[l][r][0]=(dp[l][r][0]+dp[l+1][r][0]+dp[l+1][r][1])%mod;//作为树根。
			for(int k=l;k<r;k++) if(a[l]<a[k+1]) dp[l][r][1]=(dp[l][r][1]+dp[l][k][0]*(dp[k+1][r][0]+dp[k+1][r][1])%mod)%mod;//合并若干个子树，为了避免重复选择将前面单个和后面任意个合并。
		}
	}
	cout<<(dp[1][n][0]);
	return 0;
}
```

---

