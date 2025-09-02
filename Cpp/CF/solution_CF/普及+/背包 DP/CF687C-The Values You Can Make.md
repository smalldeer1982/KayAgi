# The Values You Can Make

## 题目描述

Pari想向Arya买一块昂贵的巧克力。她有n个硬币，第i个硬币的价值是ci。巧克力的价格是k，所以Pari需要把总价值为k的硬币给Arya。现在Pari想要知道所有的值x，使得存在总和为k的硬币，其中某些硬币的总价值为x。

## 样例 #1

### 输入

```
6 18
5 6 1 10 12 2
```

### 输出

```
16
0 1 2 3 5 6 7 8 10 11 12 13 15 16 17 18 
```

## 样例 #2

### 输入

```
3 50
25 25 50
```

### 输出

```
3
0 25 50 
```

# 题解

## 作者：L7_56 (赞：6)

### 对一楼的方法换一个描述：
### [链接](https://www.luogu.com.cn/blog/tuifeidemizhou/solution-cf687c)

可以看成二维的01背包

物品体积即为硬币面额

$k$ 即为背包体积

倒序枚举可以看作背包压缩一维后的操作

这样可以更好理解

$dp[i][j]$ 表示一边的和为$i$，一边的和为$j$的情况是否存在

此时的和为 $i+j$

所以答案在 $i+j=k$ 的情况中，枚举$i$统计就可以了

---

## 作者：DennyQi (赞：3)

由于数据范围只有$500$，因此我们可以暴力地去定义状态。

令$dp_{i,j,k}$表示前$i$个元素中选出一个和为$j$的子集，这个子集凑出$k$是否可行。

显然有$dp_{i,j,k}=dp_{i-1,j,k} \ | \ dp_{i-1,j-a_i,k-a_i} \ | \ dp_{i-1,j-a_i,k}$

时间复杂度$O(n^3)$。

可以利用滚动数组优化。空间复杂度$O(n^2)$

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 510;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,K,ans,a[N],dp[N][N];
int main(){
	// freopen("file.in","r",stdin);
	n = read(), K = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
	}
	dp[0][0] = 1;
	for(int i = 1; i <= n; ++i){
		for(int j = K; j >= a[i]; --j){
			for(int k = 500; k >= 0; --k){
				if(k>=a[i])dp[j][k] |= dp[j-a[i]][k-a[i]];
				dp[j][k] |= dp[j-a[i]][k];
			}
		}
	}
	for(int k = 0; k <= K; ++k){
		if(dp[K][k]) ++ans;
	}
	printf("%d\n",ans);
	for(int k = 0; k <= K; ++k){
		if(dp[K][k]){
			printf("%d ",k);
		}
	}
	printf("\n");
	return 0;
}
```

---

## 作者：lory1608 (赞：2)

这道题很简单的一个$dp$，用$dp[i][j][k]$表示前$i$个物品，价值为$j$元，$k$元的物品是否能取到

可列出状态转移方程:
$dp[i][j][k]=dp[i-1][j][k]|dp[i-1][j-cost_i][k]|dp[i-1][j-cost_i][k-cost_i]$

初始时$dp[0][0][0]=1$

统计$dp[n][k]$即可

时间复杂度$\Theta(n^3)$，空间复杂度$\Theta(n^3)$

很明显可以用滚动数组优化空间到$\Theta(n^2)$

还可以用bitset将时间压为$\Theta(\frac{n^3}{\omega})$，空间复杂度$\Theta(n^2)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<bitset>
using namespace std;
const int maxn=505;
bitset<maxn>dp[2][maxn];
int n,k,a,cnt;
int main()
{
	scanf("%d%d",&n,&k);
	dp[0][0].set(0,1);
	int now=0,last=0;
	for(int i=1;i<=n;++i)
	{
		now=now^1,last=now^1;
		for(int j=0;j<=k;++j)dp[now][j].reset();
		scanf("%d",&a);
		for(int j=0;j<=k-a;++j)
		{
			dp[now][j+a]|=dp[last][j]|(dp[last][j]<<a);
		}
		for(int j=0;j<=k;++j)
		{
			dp[now][j]|=dp[last][j];
		}
	}
	printf("%d\n",dp[now][k].count());
	for(int i=0;i<=k;++i)
	{
		if(dp[now][k][i])printf("%d ",i);
	}
	printf("\n");
	return 0;
}
```

---

## 作者：_edge_ (赞：1)

CSP 前发题解，rp++。

思考这种题目，我们不妨把 01 背包的过程看成在图上进行遍历。

让我们回归 01 背包的方程二维版本他是 $f_{i+1,j}=f_{i,j}$ 或者 $f_{i+1,j}=f_{i,j-{a_{i-1}}}$ 我们把状态看成点，然后把转移看成边就变成了在一个 DAG 上跑背包。

更具体的，我们设 $f_{i,j}$ 表示转移到 $i,j$ 能产生的子集，然后对于每一条边，我们暴力进行进一步转移。

子集这种可以直接用 $bitset$ 进行优化，~~看题解区没有人转化为图论模型，来发一篇。~~

个人认为这样更好理解一点。

时间复杂度是 $O(\dfrac{n^3}{w})$ 的。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
#define pb push_back
using namespace std;
const int INF=505;
const int INFN=INF*INF;
vector <int> ans;
bitset <INF> F[INFN];
int n,k,a[INFN],in[INFN];
struct _node_edge{
	int to_,next_,disv_;
}edge[INFN<<1];
int head[INFN],tot,N;
void add_edge(int x,int y,int z) {
	in[y]++;
	edge[++tot]=(_node_edge){y,head[x],z};
	head[x]=tot;return ; 
}
queue <int> q;
int ys(int x,int y) {
	N=max(N,x*500+y);
	return x*500+y;
}
void print(int X) {
//	cout<<X/500<<" "<<X%500<<" is\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for (int i=1;i<=n;i++) cin>>a[i];
	
	for (int i=0;i<=n;i++) {
		for (int j=0;j<=k;j++) {
			add_edge(ys(i,j),ys(i+1,j),0);
			if (j+a[i+1]<=k) 
				add_edge(ys(i,j),ys(i+1,j+a[i+1]),a[i+1]);
		}
	}
	
	for (int i=0;i<=N;i++)
		if (!in[i]) {
			q.push(i);
			if (i==ys(0,0)) F[i][0]=1;
		}
	
	while (q.size()) {
		int x=q.front();q.pop();
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_,d=edge[i].disv_;
			F[v]|=F[x]<<d|F[x];
			if (!--in[v]) q.push(v);
		}
	}
	
	for (int i=0;i<=k;i++)
		if (F[ys(n,k)][i]) ans.pb(i);
	cout<<ans.size()<<"\n";
	int len=ans.size();
	for (int i=0;i<len;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
	return 0;
}
```


---

## 作者：S00021 (赞：1)

题意不解释。

很明显是一个背包，设计状态 $f_{i,j,k}$ 表示前 $i$ 个物品中选出总价值为 $j$ 的物品，是否可以有一个价值和为 $k$ 的子集，可以枚举是否在 $j$ 里扣除 $v_i$ 的代价，从 $f_{i-1,j-v_i,k},f_{i-1,j-v_i,k-v_i},f_{i-1,j,k}$ 三者中取或转移。

这个明显可以 `bitset` 优化，时间复杂度为 $\mathcal{O}(\frac{n^3}{w})$ ，空间可以滚动数组优化掉一个 $n$ ，复杂度降成 $\mathcal{O}(\frac{n^2}{w})$

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 500
using namespace std;
int n,k,a[MAXN+5];
vector<int>ans;
bitset<505>f[2][MAXN+5];
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[0][0][0]=1;
	for(int i=1;i<=n;i++)	
		for(int j=0;j<=k;j++){
			f[i&1][j]=f[(i&1)^1][j];
			if(j>=a[i]) f[i&1][j]=(f[i&1][j])|(f[(i&1)^1][j-a[i]])|(f[(i&1)^1][j-a[i]]<<a[i]);
		}for(int i=0;i<=k;i++) if(f[n&1][k][i]) ans.push_back(i);
	printf("%lld\n",(int)ans.size()); for(int i=0;i<ans.size();i++) printf("%lld ",ans[i]);
	return 0;
}
//f[i][j][k]=f[i-1][j][k]|f[i-1][j-a[i]][k]|f[i-1][j-a[i]][k-a[i]]
```

---

## 作者：__LZH__ (赞：0)

# CF687C The Values You Can Make

## 题意

给定数组 $a$ 和 $k$，求在 $a$ 中可选出来的两组使得两组之和为 $k$、第一组为 $x$ 中所有不同的 $x$。

## 思路

在原题面中所说的“子集的子集”很难理解，但在转换成上述题意后便可发现此题就是 $01$ 背包。

状态：$dp_{i, u, v}$ 表示前 $i$ 个中选出的第一组和为 $u$、第二组和为 $v$。

转移：$dp_{i, u, v} \to dp_{i - 1, u, v}, dp_{i - 1, u - a_i, v}, dp_{i - 1, u, v - a[i]}$，其中箭头指或运算。

其实 $i$ 这一维可以降掉，这里不多赘述。

## 时空复杂度

时间：$01$ 背包 $O(nk ^ 2)$

空间：$O(nk ^ 2)$，降维后 $O(k ^ 2)$

## 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N = 5e2 + 10;

int n, k, a[N];
bool dp[N][N][N];

signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n);
  dp[0][0][0] = 1;
  for(int i = 1; i <= n; i++){
    for(int u = 0; u <= k; u++){
      for(int v = 0; v <= k; v++){
        dp[i][u][v] |= dp[i - 1][u][v];
      }
    }
    for(int v = 0; v <= k; v++){
     for(int u = k; u >= a[i]; u--){
        dp[i][u][v] |= dp[i - 1][u - a[i]][v];
      }
    }
    for(int u = 0; u <= k; u++){
      for(int v = k; v >= a[i]; v--){
        dp[i][u][v] |= dp[i - 1][u][v - a[i]];
      }
    }
  }
  int ans = 0;
  for(int i = 0; i <= k; i++){
    ans += dp[n][i][k - i];
  }
  cout << ans << '\n';
  for(int i = 0; i <= k; i++){
    if(dp[n][i][k - i]){
      cout << i << ' ';
    }
  }
  return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## CF687C The Values You Can Make 题解

题目翻译感觉不明不白的（至少我看了几遍没看懂），这里给个较为清晰的题面。

### 题目描述
给你 $n$ 个硬币，第 $i$ 个硬币有一个价值 $c_i$，你需要从中选出一些价值和为 $k$ 的硬币组成一个集合，再输出这个集合中硬币可能组成的价值和。
### 算法
动态规划，背包。
### 分析
看完我给的题面描述其实已经很清晰了。这道题可以分为两步：
- 从 $n$ 个硬币中选出来价值和为 $k$ 的硬币集合。
- 输出硬币集合所能凑出的价值和。

我们很容易发现如果是任意一个步骤都很好做，用 $01$ 背包解决。看数据范围 $n\le 500$，考虑套两个 $01$ 背包。

现在设计状态。我们发现对于每个硬币，它都有三种处理可能：不选入硬币集合，选入硬币集合但不用来凑价值和，选入硬币集合且用来凑价值和。所以我们设 $dp_{i,j,k}$ 表示前 $i$ 个硬币中选出价值和为 $j$ 的硬币集合，用来凑出价值和 $k$ 是否可行。

状态转移方程就很好推了，对于前一个硬币有上述三种处理可能，只要有一种可行那么这个硬币就可行，转移方程为 $dp_{i,j,k}=dp_{i-1,j,k}\ \lor\ dp_{i-1,j-c_i,k}\ \lor\ dp_{i-1,j-c_i,k-c_i}$。分别对应三种处理可能。

注意一下边界 $dp_{0,0,0}=1$，最终遍历一遍 $dp_{n,k,p}(0\le p\le 500)$，如果为真就说明可以凑出输出即可，复杂度 $\mathcal O(n^3)$。

注意一下直接开三维数组会 `MLE`，需要用滚动数组优化，这里不细说了，和 $01$ 背包一样。
### 代码
码风较丑，不喜勿喷。（~~@jiayixuan1205 的好看去看她的~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Ryan
{
    const int N=500,M=505;
    int dp[M][M],c[M];
    int n,kk;
    signed work()
    {
        cin>>n>>kk;
        for(int i=1;i<=n;i++)
            cin>>c[i];
        dp[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=N;j>=0;j--)
                for (int k=N;k>=0;k--)
                    if(j>=c[i])
                    {
                        dp[j][k]|=dp[j-c[i]][k];
                        if(k>=c[i])
                            dp[j][k]|=dp[j-c[i]][k-c[i]];
                    }
        int ans=0;
        for(int i=0;i<=N;i++)
            if(dp[kk][i])ans++;
        cout<<ans<<endl;
        for(int i=0;i<=N;i++)
            if(dp[kk][i])
                cout<<i<<" ";
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Ryan::work();
}
```

---

## 作者：tder (赞：0)

试求满足「存在一个 $\{c_n\}$ 的子集 $\{p_m\}$，使得 $\sum p_i=k$ 且存在一个 $\{p_m\}$ 的子集 $\{q_s\}$ 满足 $\sum q_i=x$」的 $x$ 的个数。

---

考虑 dp。

用 $f_{i,j,x}$ 表示在前 $i$ 项中，是否存在和为 $j$ 的子集 $\{p_m\}$，且它的一个子集 $\{q_s\}$ 的和为 $k$。

那么显然，有 $f_{i,0,0}=1$。

接下来考虑转移，判断 $c_i$ 是否在 $\{p_m\}$ 中以及它是否在 $\{q_s\}$ 中，即：

$$
f_{i,j,x}=\max(f_{i-1,j,x},f_{i-1,j-c_i,x},f_{i-1,j-c_i,x-c_i})
$$

答案即为 $\sum f_{n,k,x}$。

显然可以类似背包使用滚动数组压掉第一维。

记 $n,k$ 同阶，时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。

---

## 作者：liaiyang (赞：0)

我们设 $dp_{i,j,k}$ 表示**考虑**了 $1$ 到 $i$ 的数(注意不是全部选择)，左边的和为 $j$，右边的和为 $k$，那么我们有
$$
dp_{i,j,k}=dp_{i-1,j,k}\vee dp_{i-1,j-c_i,k}\vee dp_{i-1,j,k-c_i}
$$

初始化把 $dp_{i,j,k}$ 中 $j,k<0$ 的情况归 $0$， $dp_{0,0,0}=1$ 即可。

时间复杂度 $O(nk^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3,"Ofast")
#define int long long
#define y0 Y0
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y,mod) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y,mod) (((x+=y)>=mod)&&(x-=mod))
mt19937 rnd(time(0));
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define putchar(x) (O-obuf<(1<<21)?*O++=(x):(fwrite(obuf,1,1<<21,stdout),O=obuf,*O++=(x)))
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1;
const int mod=998244353,g=3,gi=332748118;
const int N=510;
int n,k,c[N],ans[N],cnt;
bool dp[N][N];
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd,k=rd;dp[0][0]=1;
    for(int i=1;i<=n;i++) c[i]=rd;  
    for(int s=1;s<=n;s++){
        for(int i=k;i>=0;i--){
            for(int j=k;j>=0;j--){
                if(i>=c[s]) dp[i][j]|=dp[i-c[s]][j];
                if(j>=c[s]) dp[i][j]|=dp[i][j-c[s]];
            }
        }
    }
    for(int i=0;i<=k;i++) if(dp[i][k-i]) ans[++cnt]=i;
    wt(cnt,'\n');
    for(int i=1;i<=cnt;i++) wt(ans[i]," \n"[i==cnt]); 
    fwrite(obuf,1,O-obuf,stdout);
    return 0;
}
```

---

## 作者：shao0320 (赞：0)

#### CF687C The Values You Can Make

大暴力，首先这个背景就是个$0/1$背包。

直接多开一维记录一下可能的子集和即可。

$f(i,j,k)$表示考虑前$i$个物品，价值和为$j$，是否存在方案使得某个子集的和为$k$。

枚举暴力转移即可。

理论复杂度$O(500^3)$，但转移可以位运算常数小，而且由于$0/1$背包的原因显然跑不满，因此可以过。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 505
#define MAXN 500
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,K,a[N],can[N];
bool f[N][N][N];
int main()
{
	n=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	f[0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		memcpy(f[i],f[i-1],sizeof(f[i]));
		for(int j=a[i];j<=K;j++)
		{
			for(int k=0;k<=MAXN;k++)
			{
				//f[i][j][k]|=f[i-1][j][k];
				f[i][j][k]|=f[i-1][j-a[i]][k];
				if(k>=a[i])f[i][j][k]|=f[i-1][j-a[i]][k-a[i]];
			}
		}
	}
	int ans=0;
	for(int i=0;i<=K;i++)can[i]=f[n][K][i],ans+=can[i];
	printf("%d\n",ans);
//	for(int i=0;i<=K;i++)
//	{
//		printf("%d ",i);
//		for(int j=0;j<=25;j++)
//		{
//			printf("%d ",f[1][i][j]);
//		}
//		puts("");
//	}
	for(int i=0;i<=K;i++)if(can[i])printf("%d ",i);puts("");
	return 0;
}
```



---

