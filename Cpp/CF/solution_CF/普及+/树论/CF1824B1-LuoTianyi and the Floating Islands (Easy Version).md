# LuoTianyi and the Floating Islands (Easy Version)

## 题目描述

这是该问题的简单版本。唯一的区别在于本版本中 $k\le\min(n,3)$。只有当你同时解决了两个版本的问题时，才能进行 Hack。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/12896184a3f823fcd8518f46dc5b68823c932f0f.png)

Chtholly 和浮空岛。LuoTianyi 现在生活在一个有 $n$ 个浮空岛的世界里。这些浮空岛通过 $n-1$ 条无向空中航线连接，任意两个岛屿都可以通过这些航线互相到达。也就是说，这 $n$ 个浮空岛构成了一棵树。

有一天，LuoTianyi 想去见她的朋友们：Chtholly、Nephren、William，等等。她一共想见 $k$ 个人。她不知道他们的具体位置，但她知道他们分别在 $k$ 个不同的岛屿上。她定义：如果某个岛屿到这 $k$ 个有人的岛屿的距离之和在所有 $n$ 个岛屿中最小，则称这个岛屿为“好岛”。

现在，LuoTianyi 想知道，如果这 $k$ 个人被随机分配到 $n$ 个岛屿中的 $k$ 个不同岛屿上，那么“好岛”的期望数量是多少？你只需要告诉她这个期望值对 $10^9+7$ 取模后的结果。

$^\dagger$ 两个岛屿之间的距离是指从一个岛屿到另一个岛屿最少需要经过的航线数量。

## 说明/提示

在第一个样例中，航线构成如下的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/f98245759af7851bb13c350e387c9b296063f10a.png)

如果这两个人分别在岛屿 $1$ 和 $2$ 上，则岛屿 $1$ 和 $2$ 都是好岛。

从岛屿 $1$ 或 $2$ 到所有有人的岛屿的距离和为 $1+0=1$，这是最小值。而从岛屿 $3$ 到所有有人的岛屿的距离和为 $2+1=3$，大于 $1$。

类似地，当两个人在岛屿 $1$ 和 $3$ 时，岛屿 $1,2,3$ 都是好岛。

当两个人在岛屿 $1$ 和 $4$ 时，岛屿 $1,2,3,4$ 都是好岛。

当两个人在岛屿 $2$ 和 $3$ 时，岛屿 $2$ 和 $3$ 都是好岛。

当两个人在岛屿 $2$ 和 $4$ 时，岛屿 $2,3,4$ 都是好岛。

当两个人在岛屿 $3$ 和 $4$ 时，岛屿 $3$ 和 $4$ 都是好岛。

所以“好岛”数量的期望为 $\frac{16}{6}$，对 $10^9+7$ 取模后等于 $666666674$。

在第二个样例中，航线构成如下的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/2f411e079090512cd14c27f9186226921a07c282.png)

总是只有一个好岛，所以期望值为 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4```

### 输出

```
666666674```

## 样例 #2

### 输入

```
5 1
1 2
2 3
3 4
3 5```

### 输出

```
1```

# 题解

## 作者：FFTotoro (赞：10)

## 前言

这场的 C 把我蓝名搞没了，这么简单的 D1 居然没看……

## 解法

如果 $k=1$ 或 $k=3$，那么“好岛”只可能有且仅有 $1$ 个：$k=1$ 显然“好岛”就是选定的那个岛；$k=3$ 时，若 $3$ 个岛在同一条链上，“好岛”就是中间的那个岛，否则 $3$ 个岛中间围住的部分形成了一个“人”字形，“好岛”即为“人”字中的那个分叉处的岛。

现在考虑 $k=2$ 的情况：

首先有个性质，连接选定的 $2$ 个岛的简单路径上的所有岛肯定都是“好岛”。

考虑如何借助这个性质解题；尝试对于每个岛处理，如果令这个岛（设为 $x$）为根结点上的岛，设 $x$ 有 $s$ 个儿子，那么从这 $s$ 个儿子结点所管辖的 $s$ 棵子树中选择两棵子树，再从两棵子树中各选择 $1$ 个岛，这两个岛的简单路径必过 $x$。当然，还有可能 $x$ 在那条链的一端，最后输出的时候加上对应的贡献即可。

那么，问题来了：如果**不考虑 $x$ 在链的一端的情况**，如何计算以 $x$ 为根时的选择儿子方案数？显然的，令 $x$ 的 $s$ 个儿子所管辖的子树大小为 $e_1,e_2,\ldots,e_s$，答案即为：

$$
\begin{aligned}
\sum\limits_{i=1}^{s-1}\sum\limits_{j=i+1}^se_ie_j=\dfrac{\left(\sum\limits_{i=1}^se_i\right)^2-\left(\sum\limits_{i=1}^se_i^2\right)}{2}
\end{aligned}
$$

显然的，$\left(\sum\limits_{i=1}^se_i\right)^2$ 即为 $(n-1)^2$，至于平方和（即第二个 $\sum$）可以用一遍 dfs 便捷地算出。

时间复杂度 $O(n\log m)$，这里 $m=10^9+7$（模数），$\log m$ 为计算逆元的时间复杂度。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%mod*a%mod;
    a=a%mod*a%mod; b>>=1;
  }
  return r;
} // 快速幂，求逆元用
vector<int> g[200001];
int n,e[200001],w[200001];
// e[i] 为子树大小，w[i] 即为平方和
void dfs(int u,int r){
  e[u]=1;
  for(int i:g[u])
    if(i!=r){
      dfs(i,u),e[u]+=e[i];
      (w[u]+=e[i]*e[i]%mod)%=mod;
    }
  (w[u]+=(n-e[u])*(n-e[u])%mod)%=mod;
  // 计算出 w[i]
}
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int k,c=0; cin>>n>>k;
  if(k&1)cout<<"1\n"; // 答案必为 1
  else{
    for(int i=1;i<n;i++){
      int u,v; cin>>u>>v;
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }
    dfs(1,0); // 一遍 dfs
    for(int i=1;i<=n;i++)
      (c+=((n-1)*(n-1)%mod-w[i]+mod)%mod*qpow(2,mod-2)%mod)%=mod; // 算概率
    cout<<(c%mod*qpow(n*(n-1)/2%mod,mod-2)%mod+2)%mod<<endl;
    // 记得加上 2 的贡献（即 x 在链的一端的时候的贡献）
  }
  return 0;
}
```

---

## 作者：Xy_top (赞：6)

简单的 *1800。

考虑 $k=1$ 时，显然答案为 $1$。

考虑 $k=2$ 时，对于每个点，统计它作为好点的次数，显然它只要在选择的两点的路径上就是好点，分类讨论，这个点不在路径端点上那就是 $(sz_u-1)\times (n-sz_u)$，在端点上可以和其他任意的点匹配，为 $n-1$，最后再除一下即可。

最后考虑 $k=3$，显然对于三个点，只有一个好点，就是这三个点两两最近公共祖先的最深的那个点。

所以这道题就解决了，代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define int long long
using namespace std;
int n, k, ans, sum;
int sz[200005];
vector <int> G[200005];
const int mod = 1000000007;
void dfs (int u) {
	sz[u] = 1;
	for (int v : G[u]) {
		if (!sz[v]) {
			dfs (v);
			sz[u] += sz[v];
		}
	}
	ans += sz[u] * (n - sz[u]) * 2 + n - 1;
	ans %= mod;
}
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
signed main () {
	cin >> n >> k;
	For (i, 2, n) {
		int u, v;
		cin >> u >> v;
		G[u].push_back (v);
		G[v].push_back (u);
	}
	if (k == 1) {
		cout << 1;
		return 0;
	} else if (k == 2) {
		dfs (1);
		cout << ans * q_pow (n * (n - 1) % mod, mod - 2) % mod << '\n';
	} else {
		cout << 1;
		return 0;
	}
	return 0;
}
```


---

## 作者：wizardMarshall (赞：5)

一道不错的思维题。

此题解分类讨论比较详细。

## 题意
求 $n$ 个点中随意取 $k$ 个时，与这 $k$ 个点距离总和最短的点的期望个数。

## 思路

为了方便，我们将满足“与其中 $k$ 个点距离总和最短”的点称为好点。

这题是简单版，由数据范围可知 $k\le 3$。我们分类讨论。

-----

对于 $k=1$，显然答案为 $1$ 无疑了，最近的点就是它本身。

-----

对于 $k=3$，答案也为 $1$。原因如下：

任设三个点 $a$，$b$，$c$ 为取的点，按照树上的深度排序（为了分类讨论方便）。

- $a$，$b$，$c$ 并列，属于三个不同的子树，没有包含关系。此时好点为他们共同的最近公共祖先。

- $a$ 包含于 $b$，$b$ 与 $c$ 并列（或 $b$ 包含于 $c$，$a$ 包含于 $c$ 等）。此时好点依然为最近公共祖先。

- $a$ 包含于 $b$，而 $b$ 包含于 $c$。三个点相当于形成了一条链。可知好点为中间的 $b$。

分类讨论后，三个点的情况也解决了。

----

$k=2$ 的情况比较复杂。


首先所谓期望，就是个数总和除以方案数嘛。方案数比较好算，就是两个点的组合：$\dfrac{n(n-1)}{2}$。

注意：同一个点可能多次成为好点，原因是取 $k$ 个点要考虑所有可能的方案数。

既然枚举 $k$ 个点不可能，我们就考虑每个点作为好点的次数。

对于两个点的点集，好点显而易见就是 $a$ 到 $b$ 路径上的所有点（这里也包括自身）。我们可以在深搜树时一一解决。（笔者用的方法情况较多，难调，慎用）


![](https://cdn.luogu.com.cn/upload/image_hosting/3jh4m2ai.png)

如图，$x$ 为当前点，$y$ 为父亲，$1$，$2$ 等均为儿子。图中的几条都是经过 $x$ 的路径。这里面分几种情况：

1. 黄色路径。一个点在 $x$ 的子树里，一个是 $x$ 的祖先（不一定是父亲）。可以通过维护子树大小来计算。

2. 红色路径。一个为 $x$ 自身，一个在子树里。也可以通过子树大小来计算。

3. 绿色路径。其实完全可以和第二种情况合在一起，简而言之就是 $x$ 连向其他点。

4. 蓝色路径。两个点均为子树内（不是 $x$ 自身）。我们知道同一个子树的不能计算，因为它们的最近公共祖先不是 $x$。两个点必须在**不同的子树内**。

具体见代码注释。

----

假设我们已经得出了好点个数总和，以及方案个数。需要做的就是两个数相除。

这里需要使用乘法逆元，记得在之前的操作中也要取模。没有熟练掌握乘法逆元的左转模版[一](https://www.luogu.com.cn/problem/P3811)/[二](https://www.luogu.com.cn/problem/P5431)。

至此，思路结束。

## 代码


```

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int p = 1000000007;
vector <int> edge[200005];
int size[200005];
int fa[200005];
int n, k;
int ans;
int _pow(int x, int b) {
	int ans = 1;
	while (b) {
		if (b % 2) {
			ans = (ans * x) % p;
		}x = (x * x) % p;
		b /= 2;
	}
	return ans;
}
int niy(int x) {//快速幂求逆元
	return _pow(x, p - 2) % p;
}
void dfs(int x) {
	size[x] = 1;
	for (auto i : edge[x]) {
		if (i != fa[x]) {
			fa[i] = x;
			dfs(i);
			size[x] += size[i];//维护子树大小
		}
	}
	ans += ((size[x] - 1) * (n - size[x])) % p;//两个点一个在下一个在上
	ans %= p;
	ans += n - 1;//x与其他点的连边
	ans %= p;
	int sum = 0;
	for (auto i : edge[x]) {
		if (i != fa[x]) {
			sum += (size[i] * (size[x] - 1 - size[i])) % p;//每个子树内的点与其他子树的连边
			sum %= p;
		}
	}
	sum *= niy(2);//由于一对点会被算两次，要用乘法逆元除以2
	sum %= p;
	ans += sum;
	ans %= p;
	return;
}
signed main() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%lld%lld", &a, &b);
		edge[a].push_back(b);
		edge[b].push_back(a); 
	}
	if (k == 1 || k == 3) {//1与3直接输出
		cout << 1;
		return 0;
	}
	ans = 0;
	dfs(1);
	int sum = n * (n - 1) / 2;
	sum %= p;
	
	ans *= niy(sum);//好点总数 / 方案数 = 期望值
	ans %= p;
	cout << ans;
    return 0;
}


```

---

## 作者：CQ_Bab (赞：4)

# 前言
这道题是老师教我们做的，还是挺有意义的。
# 思路
我们首先可以知道一个性质就是若 $k$ 为奇数那么输出 $1$，这个是因为我们只能选这 $k$ 个点的公共点，因为无论往哪一边调一下都不能让增量等于减量，毕竟不可能一个奇数除以 $2$ 等于剩下的。

然后我们就可以来讨论偶数的情况，那么我们可以知道偶数我们只需要保证增量为 $\frac{k}{2}$ 个另一边也有这么多个即可。然后我们又能知道对于一条路径上边数等于点数减一，那么我们就可以用边来考虑。

我们只需要在一条边的一边取出 $\frac{k}{2}$ 个的方案数乘上另一边取出这么多的方案数，然后因为每一条边都要加一，那么我们在加上 $\binom{k}{n}$ 即可。

最后我们就可以得到答案为 $\frac{\sum_{i=1}^{n} siz_i\times(n-siz_i)+\binom{k}{n}}{\binom{k}{n}}$ 然后这道题和[困难版](https://www.luogu.com.cn/problem/CF1824B2)就可以过了。
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
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,k;
const int p=1e9+7;
const int N=1e6+10;
int siz[N];
int fc[N],inv[N];
vector<int>v[N];
int C(int x,int y) {
	return (fc[x]*inv[x-y]%p*inv[y]%p);
}
int qmi(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*x%p;
		x=x*x%p;
		y>>=1;
	}
	return res;
}
int res=0;
void dfs(int x,int fa) {
	siz[x]=1;
	for(auto y:v[x]) {
		if(y!=fa) {
			dfs(y,x);
			siz[x]+=siz[y];
			res+=(C(siz[y],k/2)*C(n-siz[y],k/2)%p);//统计分子
			res%=p;
		}
	}
}
fire main() {
	in(n),in(k);
	if(k&1) {
		cout<<1<<endl;
	} else {
		fc[0]=1;
		rep(i,1,n) fc[i]=fc[i-1]*i%p;
		inv[0]=1;
		inv[n]=qmi(fc[n],p-2);
		rep1(i,n-1,1) inv[i]=inv[i+1]*(i+1)%p;//预处理
		int ni=qmi(C(n,k),p-2);
		rep(i,1,n-1) {
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		dfs(1,0);
		cout<<(res*qmi(C(n,k),p-2)%p+1)%p<<endl;//提出来了C(n,k)
	}
	return false;
}

```

---

## 作者：DengDuck (赞：3)

这道题还是很有意思的，比赛时 KonjacHZX 一直在说很水让我们去想，但是英语不好懒得看。

这个题重点在于 $k\leq 3$。

首先在 $k=1$ 或 $k=3$ 时，不难发现每个点收到的贡献都不一样，所以只有一个点是最优的。

$k=2$ 时，我们发现最优点就是随机抽的两个点之间的点，这个是显然的。

我们都知道期望可以理解为所有情况的平均值，也就是总值除于情况数，情况数自然是 $\dfrac 1 2 n(n-1)$。

然后总值当然就是树上所有距离之和啦。

于是我们统计出树上所有距离之和，再一个逆元代替除法算出答案即可。

```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const LL N=2e6+5;
const LL mod=1e9+7;
LL n,k,x,y,sz[N],ans;
vector<LL>v[N];
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1; 
	}
	return ans;
}
void dfs(LL x,LL fa)
{
	sz[x]=1;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x),sz[x]+=sz[i];
		ans=(ans+sz[i]*(n-sz[i])%mod)%mod;
	}
}
int main()
{
	cin>>n>>k;
	if(k&1)
	{
		puts("1");
		return 0;
	}
	for(int i=1;i<=n-1;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	cout<<(ans*ksm(n*(n-1)/2%mod,mod-2)%mod+1)%mod<<endl;
}
```

---

## 作者：Zi_Gao (赞：2)

## 前言

感觉大家分类讨论了好多无用的东西，其实可以更简化。

## 正文

### 0x00 分析题目

首先可以发现 $k\leq3$，那么自然想到去看看每一个 $k$ 对应的情况：

1. $k=1$ 自然每次答案为 $1$，期望为 $1$。

2. $k=3$ 考虑三个点的交汇处，即任意两点 LCA 中距离每个点距离和最小的那个点，实际上我们还可知道这个点是所有点中距离每个点距离和最小的店。因为此时向任意一个方向走会使得与某两个点的距离增加 $1$，与某一个点的距离减少 $1$。总贡献为 $+1$，显然其他点不优。那么每次答案为 $1$，期望为 $1$。

接下来只需要具体分析 $k=2$ 情况即可。可以发现树上任意选取两个点，这条链上的所有点都会贡献答案，也就是转化为求树上任意两点距离和，而链上点数就是距离加一。

这个问题十分常见，直接考虑每个子树内的点经过子树根到其父亲的那条边的贡献即可，记子树大小为 $s$，根据乘法原理答案贡献为 $s\times\left(n-s\right)$。

最后乘上方案数 $\frac{n\left(n-1\right)}{2}$ 的逆元即可。

### 0x01 代码实现

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

#define INV_DATA_TYPE long long
INV_DATA_TYPE exgcd(INV_DATA_TYPE a,INV_DATA_TYPE b,INV_DATA_TYPE&x,INV_DATA_TYPE&y){if(!b){x=1;y=0;return a;}INV_DATA_TYPE d=exgcd(b,a%b,y,x);y-=a/b*x;return d;}INV_DATA_TYPE inv(INV_DATA_TYPE n,INV_DATA_TYPE p){INV_DATA_TYPE x,y;exgcd(n,p,x,y);x%=p;return x>=0?x:x+p;}

const long long mod=1000000007;
long long ans;
int siz[200010],n;

std::vector<int> e[200010];

void addEdge(int u,int v){
    e[u].push_back(v);
}

void dfs(int u,int p){
    siz[u]=1;
    for(auto v:e[u])
        if(v!=p){
            dfs(v,u);
            siz[u]+=siz[v];
        }
    ans=(ans+1ll*siz[u]*(n-siz[u]))%mod;
    return;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,u,v;
    n=read();
    int k=read();
    if(k&1){
        puts("1");
        return 0;
    }
    for(i=1;i<n;++i){
        u=read();
        v=read();
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,1);

    print((ans*inv(1ll*n*(n-1)>>1,mod)+1)%mod);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：Register_int (赞：1)

对于 $k$ 为奇数的情况，首先好点必定存在，每次从好点移动一格，都会至少让路径长度增加 $\left\lfloor\dfrac k2\right\rfloor+1-\left\lfloor\dfrac k2\right\rfloor=1$，因此好点只有一个。直接输出 $1$。

对于 $k=2$ 的情况，容易发现在这两点间的全是好点，所以直接将树上所有路径长度和算出来，除以总方案数就能算出期望，时间复杂度 $O(n)$。

如何计算路径长度之和？考虑计算每条边的贡献，就是两端的子树中各选一个点，直接计算即可。注意这里的路径长度还要加上 $1$，不过可以在期望中再加上。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; b = b * b % mod, p >>= 1) if (p & 1) res = res * b % mod;
	return res;
}

struct node {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int n, k, s[MAXN]; ll ans;

void dfs(int u, int f) {
	s[u] = 1;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f) continue; dfs(v, u), s[u] += s[v];
		ans = (ans + (ll)s[v] * (n - s[v]) % mod) % mod;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	if (k & 1) return puts("1"), 0;
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0), printf("%lld", (ans * qpow((ll)n * (n - 1) / 2 % mod, mod - 2) % mod + 1) % mod);
}
```

---

## 作者：shinkuu (赞：1)

 **这是一篇只针对 B1 的题解，若想了解 B2 做法请见 [link](https://www.luogu.com.cn/blog/Kato-Megumi/cf1824b2-post)。**

首先发现 $k=1$ 时，答案一定为 $1$。那 $k=3$ 时呢？这时想到 [P4281](https://www.luogu.com.cn/problem/P4281)。~~发现这题没有 spj，故答案也为 $1$。~~实际上，容易发现只有一个点满足条件。具体证明见 [link](https://www.luogu.com.cn/blog/Kato-Megumi/cf1824b2-post)。

当 $k=2$ 时，若两个点分别为 $x$ 和 $y$，容易发现以这两点为顶点的链上的所有点均满足条件。因为是求期望，所以答案即为 $\dfrac{\sum\limits_i\sum\limits _{j\not=i} (dist(i,j)+1)}{n\times (n-1)}$（所有情况答案和除以情况数量）。也可以写成 $\dfrac{\sum\limits_i\sum\limits _{j\not=i} dist(i,j)+n\times(n-1)}{n\times (n-1)}$。

这个答案如何计算呢？可以对每一条边计算它对多少对点产生了贡献，即为 $siz_v\times(n-siz_v)$。其中 $siz_i$ 表示以 $i$ 为根的子树大小，$v$ 为这条边连接的深度更大的点。

code：

```cpp
int n,m;
ll sum=0;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
int siz[N];
void dfs(int u,int f){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs(v,u);
		siz[u]+=siz[v];
		sum+=1ll*siz[v]*(n-siz[v]);
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	if(m==1||m==3){
		puts("1");
		return;
	}
	dfs(1,0);
	int k=1ll*n*(n-1)/2%mod;
	printf("%lld\n",1ll*(sum+k)%mod*qpow(k,mod-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika::solve();
}
```

---

## 作者：WaterSun (赞：0)

# 思路

因为 $k \leq 3$ 考虑分类讨论。

1. $k = 1$：显然答案是 $1$，因为只有有人的那个点是好点。

2. $k = 2$：根据绝对值的几何意义，发现在选定的两个点之间的所有节点都是好点，那么问题转化为了求树上所有路径的节点数量和。众所周知，一条路径上的节点数量等于边的数量加 $1$。因此我们可以求出每一条路径没遍历的次数。假设现在要求 $u \to v$ 的边的遍历次数，那么如果我们选取 $v$ 的子树中的一个节点，再选取一个不在 $v$ 子树中的一个节点，一定能遍历到这条边，其余情况一定不能遍历到这条边。所以如果 $v$ 子树大小为 $sz_v$，那么这条边将会被遍历 $sz_v \times (n - sz_v)$。最后的答案就是 $\frac{(\sum_{i}{sz_i \times (n - sz_i) + \binom{n}{2}})}{\binom{n}{2}}$。

3. $k = 3$：显然答案也是 $1$，因为只有三个点之间的一个交点是好点。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10,mod = 1e9 + 7;
int n,k,ans;
int idx,h[N],ne[M],e[M],sz[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void add(int a,int b){
	ne[idx] = h[a];
	e[idx] = b;
	h[a] = idx++;
}

inline void exgcd(int a,int b,int &x,int &y){
	if (!b){
		x = 1;
		y = 0;
		return;
	}
	exgcd(b,a % b,y,x);
	y = y - a / b * x;
}

inline int get_inv(int a){
	int p = mod,x,y;
	exgcd(a,p,x,y);
	return (x % mod + mod) % mod;
}

inline void dfs(int u,int fa){
	sz[u] = 1;
	for (re int i = h[u];~i;i = ne[i]){
		int j = e[i];
		if (j == fa) continue;
		dfs(j,u);
		sz[u] += sz[j];
	}
	ans += sz[u] * (n - sz[u]);
}

signed main(){
	memset(h,-1,sizeof(h));
	n = read();
	k = read();
	for (re int i = 1;i < n;i++){
		int a,b;
		a = read();
		b = read();
		add(a,b);
		add(b,a);
	}
	if (k == 1 || k == 3) puts("1");
	else{
		int num = n * (n - 1) / 2;
		dfs(1,0);
		printf("%lld",(ans + num) % mod * get_inv(num) % mod);
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

按照 $k$ 的奇偶分开考虑。

$k$ 为奇数。一个好的节点有且仅有一个在任意两个有人的节点 $i,j$ 的路径的交点上的最优位置。若该交点偏移 $1$ 步，则必然会使路径长度和 $+1$。故期望为 $1$。

$k$ 为偶数。任意一个好的节点仍然在任意两个有人的节点 $i,j$ 的交点上。但若对于某个好点的偏移，在偏移后距离增加与减少的距离均为 $\frac{k}{2}$ 时，这个点也是好的。考虑枚举边，若一条边的两边有人的点的数量均为 $\frac{k}{2}$，则这条边有贡献 $1$。即每条边的贡献之和为 $\sum\limits_{u=1}^{n-1} \binom{siz_u}{\frac{k}{2}}\times \binom{n-siz_u}{\frac{k}{2}}$。其中 $siz_u$ 为边 $u$ 左端的节点数量。但是，对于某一条有好点的路径 $x$，其中的边的数量总会比点的数量少一，所以贡献之和还需要加上 $\binom{n}{k}$。所以对于 $k$ 为偶数时，期望为 $\frac{\sum\limits_{u=1}^{n-1} \binom{siz_u}{\frac{k}{2}}\times \binom{n-siz_u}{\frac{k}{2}}+\binom{n}{k}}{\binom{n}{k}}$。

注：求组合数可以先预处理 $1 \le i \le n$ 的阶乘，在用逆元乘。在 $siz_u+1 \le \frac{k}{2}$ 的时候，这条边是没有贡献的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e6+10,p=1e9+7;
int n,k;
int ne[N],e[N],h[N],idx;
int sum,siz[N],__[N];

il int qmi(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p,b>>=1;
	}
	return ans;
}
il int C(int n,int m){
	if(n<m) return 0;
	return __[n]%p*qmi(__[m],p-2)%p*qmi(__[n-m],p-2)%p;
}

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	siz[now]=1;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now),siz[now]+=siz[j];
	}
	return ;
}
il void dfs2(int now,int fa){
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		sum=(sum+C(siz[j],k/2)*C(n-siz[j],k/2))%p;
		dfs2(j,now);
	}
	return ;
}

il void solve(){
	cin>>n>>k;
	for(re int i=1,u,v;i<n;++i)
		cin>>u>>v,
		add(u,v),add(v,u);
	if(k&1){cout<<"1\n";return;}
	__[0]=1;for(re int i=1;i<=n+5;++i) __[i]=__[i-1]*i%p;
	sum=C(n,k);
	dfs(1,0),dfs2(1,0);
	cout<<(sum%p*qmi(C(n,k),p-2)%p)%p<<"\n";
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：AlicX (赞：0)

观察到 $k \leq 3$，所以我们可以分类讨论 $k=1/2/3$ 的每种情况。

观察样例可以发现：$k=1$ 时，好的节点一定是选的点，所以期望一定为 $1$。

那么对于 $k=3$ 的情况，先假设好的节点在他们路径上的交点，那么如果这个好的节点向任意一个点靠近一步，那么对于另外两个点都会远离 $1$ 步，所以好的节点永远不会变，期望同样为 $1$。

最后考虑 $k=2$ 的情况，思考一下可以发现：对于每两个被选的节点，好的节点数为它们之间的距离。所以转换一下问题：求每两个点之间的距离和，继续转换可以发现：点数等于边数加一。所以我们看边数的贡献即可。那么对于连接 $u,v$ 的第 $i$ 条边，$f_i=siz_u \times siz_v$。最后答案记得变为点数求解，即为 $\frac{\sum\limits_{i=1}^{n}f_i+\binom{n}{k}}{\binom{n}{k}}$。

---

## 作者：syysongyuyang (赞：0)

## 前言

其实 $D1$ 就是个简单题，毕竟 $k\leq 3$

## 题意

给定一颗树，随机 $k$ 个点，定义一个点是好点当且仅当这 $k$ 个点到 $u$ 的距离为树中最小，求好点数量的期望。

## 题解

分类讨论一下

考虑 $k=1$ 的时候，只有被选到的点是好点，期望为 $1$

$k=3$ 时，当三个点在一条链上时，我们容易发现中间的节点是唯一的（如果不是，那么会有多的重复段，会多走）。当三个点不在一条链上时，那么这三个节点连接的交点是最优的（和上面一样，选别的会多走）

那么就只有 $k=2$ 时需要考虑

容易发现，$k=2$ 时，两个点在树上形成一条链，链上所有点都对答案有贡献。因此，容易想到统计所有链的长度。但是这个好像不太好搞，我们把它搞到点上，统记对于每个点，经过这个点的链有多少条

但是我们发现，正面搞要算子树内的贡献和子树+祖先的贡献，不太好算。考虑正难则反，统计不合法的数量。简而言之就是统计出在同一子树内选（不会经过 $u$）以及在祖先选链（也不会经过点 $u$）的值。我们枚举 $(u,v) \in |E|$，如果 $v$ 是父亲节点，就设值 $w=n-siz_u$，非法答案是 $\binom {w} {k}$。如果是子节点，那么 $w=siz_v$，那么非法的答案就是 $\binom {w} {k}$，最后每个点的贡献是 $\binom {n} {k}- \binom {w} {k}$

最后简单统计一下和，再乘以 $\binom {n} {k} \bmod 10^9+7$ 下的逆元就可以了

代码实现：

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<bitset>
#include<map>
#include<set>
#define yl sb
#define int long long
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int mod=1e9+7;
struct Edge{
    int v,next;
}edge[N<<1];
int n,k,tot=1,ans=0;
int head[N],fac[N],siz[N],f[N];
inline void add(int u,int v){
    edge[++tot]=(Edge){v,head[u]},head[u]=tot;
}  
inline int read(){
    int s=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') {f=-1;} ch=getchar();}
    while(isdigit(ch)) {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();}
    return s*f;
}
inline void write(int x){
    int top=0,sta[35];
    while(x) {sta[top++]=x%10,x/=10;}
    while(top) {putchar(sta[--top]+'0');}
}
inline int ksm(int a,int b)
{
    int res=1;
    while (b)
    {
        if (b&1)
            res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
inline int C(int n,int m)
{
    if (n<m) return 0;
    if (n==0 || m==0) return 1;
    return fac[n]%mod*ksm(fac[m],mod-2)%mod*ksm(fac[n-m],mod-2)%mod;
}
inline void dfs(int u,int fa)
{
    siz[u]=1;f[u]=fa;
    for (int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].v;
        if (v==fa) continue;
        dfs(v,u);siz[u]+=siz[v];
    }
}
signed main()
{
    n=read(),k=read();fac[0]=1;
    if (k&1) {puts("1");return 0;}
    for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    for (int i=1;i<=n-1;i++)
    {
        int u=read(),v=read();
        add(u,v);add(v,u);
    }
    dfs(1,1);
    for (int i=1;i<=n;i++)
    {
        int res=0;
        for (int j=head[i];j;j=edge[j].next)
        {
            int v=edge[j].v,w;
            if (v==f[i]) w=n-siz[i];
            else w=siz[v];
            res=(res+C(w,k)%mod)%mod;
        }
        ans=(ans+(C(n,k)%mod-res%mod+mod)%mod)%mod;
    }
    printf("%lld\n",ans%mod*ksm(C(n,k),mod-2)%mod);
    return 0;
}
```



---

## 作者：六楼溜刘 (赞：0)

## 题意
- 有一个有 $n$ 个结点的无根树，其中有等概率随机 $k$ 个不同结点为黑色。
- 求出**与所有黑点距离之和最小的点**的期望数量（为方便叙述称之为最优点）。
- $1\le n \le 2\cdot 10^5,1\le k \le 3$，答案对 $10^9+7$ 取模。

## 题解

首先容易发现 $k$ 很小，考虑分三种情况处理。

此外，虽然题目背景中所有有人的点并不等价，但是容易发现其实哪个人在哪个点并不影响期望，当成等价的即可。

- $k=1$

很显然，所有情况的最优点都只有一个，所以期望为 $1$。

- $k=3$

此时所有情况最优点的个数也是 $1$。可以简单分情况讨论一下。

- 假如三个黑点在一条链上，肯定只有中间那个是最优点。
- 假如不在一条链上，我们发现只有三条链的交汇点是最优点（如图）。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/vitjadt4.png)

比如这张图中，很显然只有点 $2$ 是最优点，因为选其它任意点都会导致走了不该走的边或者一条边被算两次。

所以 $k=3$ 时期望也是 $1$。

- $k=2$

参考 $k=3$ 的思路，容易发现 $k=2$ 时两黑点之间链上每个点都是最优点（包括两黑点）。

所以转化为求树上随机链的期望长度。另外发现树上链的总数非常好求（就是 $\frac{n\cdot(n-1)}{2}$），想到求出所有链长度之和除以链的数量。考虑树形 DP。

设 $dp_i$ 表示以 $i$ 为根结点的子树中所有以根为端点的链的长度之和，需要注意在原问题中链的端点也是最优点，故这里的长度指链上点的个数（包括端点），同理，在此处单个点也算作链。又设 $f_i$ 表示子树内点的个数，易得转移方程：

$$f_i=1+\sum\limits_{j \in childen(i)}f_j$$

$$dp_i=1+\sum\limits_{j \in childen(i)}dp_j+f_j$$

$f_i$ 的方程很好理解，关于 $dp_i$ 的方程，首先每个结点自己会算一次，然后以所有子节点为端点的链都会加上点 $i$ 而产生 原长度 $+1$ 的贡献，其中，每个子树内以根为端点的链的数量显然等于 $f_i$，故得此式。

求出 $dp$ 和 $f$ 就很好统计总长度了，假如我们要把以 $u,v$ 为根两棵子树合并到一起，容易发现两棵子树中任选两条以根为端点的链连接起来都会产生一条新的链，也就是说，会对最终答案产生 $f_u\times dp_v+f_v\times dp_u$ 的贡献（就是每一套链都会使另一边产生等同于 $dp$ 的值的贡献），这个式子可以在求 $dp,f$ 的时候一起统计，具体来讲就是最开始把每个点当成只有一个点的树，每次和所有子树合并。另外，这个式子没有统计单个点的“链”，因为题目要求所有黑点两两不同。

复杂度 $O(n)$（如果 $k=2$，当然 $k=1,3$ 的时候是 $O(1)$ 的，但我觉得没必要分那么细）。

## code
```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f,mod=1e9+7;
int n,k,dp[N],pd[N],ans;//这里的 pd 就是上面讲的 f
vector<int> e[N];//邻接表存图
void dfs(int x,int fa){
	pd[x]=1;dp[x]=1;
	for(auto i:e[x]){
		if(i==fa) continue;
		dfs(i,x);//dfs 的时候直接统计答案
		ans=(ans+1ll*pd[i]*dp[x]%mod+1ll*pd[x]*dp[i]%mod)%mod;
		(pd[x]+=pd[i])%=mod;
		dp[x]=((dp[x]+dp[i])%mod+pd[i])%mod;
	}
}
int ksm(int a,int b){//快速幂，用来求逆元
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return c;
}
signed main(){
	n=read();k=read();
	forup(i,1,n-1){
		int u=read(),v=read();
		e[u].push_back(v);e[v].push_back(u);
	}
	if(k==1||k==3){//特判
		puts("1");
		return 0;
	}
	dfs(1,0);
	printf("%lld",1ll*ans*ksm(1ll*n*(n-1)/2%mod,mod-2)%mod);
}
```

---

