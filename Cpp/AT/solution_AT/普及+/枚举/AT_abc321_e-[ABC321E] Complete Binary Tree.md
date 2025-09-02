# [ABC321E] Complete Binary Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc321/tasks/abc321_e

$ 1 $ から $ N $ までの番号が付けられた $ N $ 頂点からなる木があります。 各 $ i\ (2\ \leq\ i\ \leq\ N) $ について、頂点 $ i $ と頂点 $ \lfloor\ \frac{i}{2}\ \rfloor $ を結ぶ辺が張られています。 逆に、これら以外の辺は存在しません。

この木において、頂点 $ X $ との距離が $ K $ である頂点の数を求めてください。 ただし、$ 2 $ 頂点 $ u,v $ の距離は、頂点 $ u,v $ を結ぶ単純パスに含まれる辺の個数として定義されます。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ T\ \leq\ 10^5 $
- $ 1\leq\ N\ \leq\ 10^{18} $
- $ 1\leq\ X\ \leq\ N $
- $ 0\leq\ K\ \leq\ N-1 $
- 入力は全て整数
 
### Sample Explanation 1

$ N=10 $ のとき、木は以下の図のようになります。 !\[\](https://img.atcoder.jp/abc321/0d1a718458ffcf25a6bc26d11b3a7641.png) このとき、 - 頂点 $ 2 $ との距離が $ 0 $ である頂点は $ 2 $ の $ 1 $ つです。 - 頂点 $ 2 $ との距離が $ 1 $ である頂点は $ 1,4,5 $ の $ 3 $ つです。 - 頂点 $ 2 $ との距離が $ 2 $ である頂点は $ 3,8,9,10 $ の $ 4 $ つです。 - 頂点 $ 2 $ との距離が $ 3 $ である頂点は $ 6,7 $ の $ 2 $ つです。 - 頂点 $ 2 $ との距離が $ 4 $ である頂点は存在しません。

## 样例 #1

### 输入

```
5
10 2 0
10 2 1
10 2 2
10 2 3
10 2 4```

### 输出

```
1
3
4
2
0```

## 样例 #2

### 输入

```
10
822981260158260522 52 20
760713016476190629 2314654 57
1312150450968417 1132551176249851 7
1000000000000000000 1083770654 79
234122432773361868 170290518806790 23
536187734191890310 61862 14
594688604155374934 53288633578 39
1000000000000000000 120160810 78
89013034180999835 14853481725739 94
463213054346948152 825589 73```

### 输出

```
1556480
140703128616960
8
17732923532771328
65536
24576
2147483640
33776997205278720
7881299347898368
27021597764222976```

# 题解

## 作者：Genius_Star (赞：13)

### 题意：

有一个 $n$ 个节点树，有着 $n-1$ 条边，对于第 $i$ 条边连接着 $\lfloor \frac{i}{2} \rfloor$（$i \ge 2$），每次询问第 $x$ 号节点距离为 $k$ 条边的点的个数。

### 思路：

~~感觉比 F 题难一些……~~

自己画一下图就可以知道，题目中给出的树是一颗完全二叉树，节点 $i$ 的左儿子为 $i \times 2$，右儿子为 $i \times 2 + 1$。

因为 $n$ 非常的大，足足有 $10^{18}$，所以暴力肯定行不通。

一步一步想，先来考虑对于 $x$ 号节点往下的距离 $k$ 条边的点的个数，看看样例中的图：

![](https://img.atcoder.jp/abc321/0d1a718458ffcf25a6bc26d11b3a7641.png)

拿 $x=2,k=2$ 来说，从 $2$ 号点往下走 $2$ 条边可以走到 ${8,9,10}$ 号节点，于是我们可以发现，对于往下走 $k$ 条边，到达的点的深度肯定是一样的，那么我们可以求一下那一层中最左边的点与最右边的点，两者相减就是可以到达的点数。

开头讲了完全二叉树的性质，我们可以根据这个性质来找，从 $x$ 号点开始，一直往左儿子走，走 $k$ 条边到达的点就是最左边的点，最右边的点就是一直往右左。

则可以将 $x$ 的编号 $\times 2$ 去到左儿子进行 $k$ 次得到的编号就是最左边的点，最右边的点就是不断 $\times 2+1$。

这里涉及到一个小问题，按样例说，$2$ 号点走 $2$ 次最左边是 $8$，最右边是 $11$，但是 $n$ 只有 $10$，我们就可以将 $n$ 当作做右边的点进行运算。

那么，定义左边的点编号为 $l$，最右边的点编号为 $r$，则可以到达的点的个数是 $\min(r,n)-l+1$。

现在解决了第一个问题，即向下走能走到的点的个数，那么向上走呢？

其实这个很好处理，一直遍历 $x$ 的祖先，即不断除以二。

计算一下当前这个 $x$ 的祖先向下走 $k-p$（其中 $p$ 表示是 $x$ 的第 $p$ 个祖先）条边的点数，因为可能走到 $x$ 这边来（因为是简单路径，不能重复经过），所以要减去 $x$ 的 $p-1$ 个祖先向下走 $k-p-1$ 条边的点的个数。

这样我们将所有值加在一起，就是最终的答案。

单次查询时间复杂度：$O(\log^2x)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
ll read(){
	ll x;
	scanf("%lld",&x);
	return x;
}
void write(ll x){
	printf("%lld",x);
}
ll T,n,x,k,ans=0;
ll F(ll x,ll n,ll k){ //计算 x 号点向下走 k 条边能走到的点数
    if(k<0)
	  return 0;
    ll l=x,r=x;
    for(int i=0;i<k;i++){
        l<<=1ll;
        r=r<<1ll|1ll;
        if(l>n)  //如果最左边点都超过 n 了，那么没有贡献
		  return 0;
    }
    return min(r,n)-l+1ll;
}
int main(){
	T=read();
	while(T--){
		n=read(),x=read(),k=read();
		ans=F(x,n,k);
		while(x/2ll){ //遍历 x 的祖先
			k--;
			ans+=F(x/2,n,k)-F(x,n,k-1);
			x>>=1ll;
		}	
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：sunzz3183 (赞：11)

# [ABC321E] Complete Binary Tree 题解

## 题意

$T$ 组数据，每组给你三个数 $n,x,k$，让你求在大小为 $n$ 的完全二叉树上，距离 $x$ 点距离为 $k$ 的点有多少个。

-   $1\leq T \leq 10^5$
-   $1\leq N \leq 10^{18}$
-   $1\leq X \leq N$
-   $0\leq K \leq N-1$

## 题解

一颗树有 $\left \lfloor \log_2(n) \right \rfloor )+1$ 层，所以考虑一步步往上跳来求解。

![](https://pic.imgdb.cn/item/650f75e8c458853aef3deb15.png)

对于这样的一张图，以 $4$ 为起点，距离 $3$ 的点分别是 $3,10,11$。

显然我们发现，当一个点是由父边得来，则可以直接转化成求该子树第 $k-temp$ 层有多少个节点（ $temp$ 为到子树根节点的路径长度）。

但是，显然除了最后一层，其他层都是满的，所以我们要判断子树的第 $k-temp$ 层是不是整颗树的最后一层，不是则节点数固定（要么是下面的公式，要么不存在，为 $0$），是则要把该层最后一个点的编号对于 $n$ 取 $\min$，那么该层节点数就是该层最后一个点编号减去第一个点编号然后加一。

然后由图可得：

- $u$ 子树的第 $t$ 层第一个节点 $u\times 2^t$。

- $u$ 子树的第 $t$ 层节点个数 $2^t$。

- $u$ 子树的第 $t$ 层最后一个节点 $u\times 2^t+2^t$。

具体步骤看代码注释。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
int n,x,k,ans,d;
void solve(int u,int temp,int lst){
    if(!u)return;//跳到终点
    if(temp==k){ans++;return;}//无法跳跃
    int sonl=u<<1,sonr=u<<1|1;//左右儿子
    if(sonl!=lst){//判断，不能往回计算
        int dep=floor(log2(sonl))+1,len=k-temp-1;//该儿子的层数，还能走的步数（注意这里到儿子的步数是 temp+1）
        if(dep+len<d)//不到最后一层
            ans+=1ll<<len;
        else if(dep+len==d){//是最后一层
            int l=sonl<<len;//看解释
            int r=(l-1)+(1ll<<len);
            r=min(n,r);
            if(l<=r)ans+=r-l+1;
        }//还有超过最后一层，因为为 0，所以不考虑
    }
    //同上
    if(sonr!=lst){
        int dep=floor(log2(sonr))+1,len=k-temp-1;
        if(dep+len<d)
            ans+=1ll<<len;
        else if(dep+len==d){
            int l=sonr<<len;
            int r=(l-1)+(1ll<<len);
            r=min(n,r);
            if(l<=r)ans+=r-l+1;
        }
    }
    solve(u>>1,temp+1,u);//向上跳跃
    return;
}
void Main(){
    n=read(),x=read(),k=read();ans=0;
    d=floor(log2(n))+1;//该树层数
    solve(x,0,0);
    printf("%lld\n",ans);
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T=read();
    while(T--)Main();
    return 0;
}
```


---

## 作者：不知名用户 (赞：4)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc321_e)。

题意：有 $T$ 次询问，每次给出 $N,X,K$，求 $N$ 个节点的二叉树中距离 $X$ 为 $K$ 的节点数。

考虑枚举 $X$ 和距离 $X$ 为 $K$ 的节点的 LCA。

![](https://img.atcoder.jp/abc321/0d1a718458ffcf25a6bc26d11b3a7641.png)

为说明细节，以求上图中距离 4 为 2 的节点个数为例，以下简称问题 1。

确定 LCA 后，只需要求出 LCA 的子树中与 LCA 距离是某个值的节点个数即可。

> 注意！这里有个细节，为了防止 LCA 的后代再往走向 LCA 的路径走（如上图，解决问题 1 时 LCA 为 2 时会计算到节点 4！），所以要强制 LCA 向另一边的子节点走一步（当然在 LCA 不是 $X$ 且还需要往子节点走，如问题 1 中 LCA 为 4,1 时就不用往下走，因为 4 没有往上走，走到 1 步数用完了）。

细节处理代码：
```cpp
int y = x >> i, z = k - i;
//x,k 见题意，i 为 x 距 LCA 的长度，y 为 LCA，z 为答案节点距 LCA 的长度 
if(i>0&&z)//既要往上走，也不能无路可走 
{
	int a = (x >> i - 1) & 1;//x 在 y 的左子树还是右子树 
	if(a&1ll) y = y * 2, z--;//往左子树强制走一步 
	else y = y * 2 + 1, z--;
}
```

再解决刚刚的问题：在一个 $N$ 个节点的二叉树中，$A$ 子树中距离 $A$ 为 $B$ 的节点数。由于 $A$ 的左子节点为 $2*A$，右子节点为 $2*A+1$，那么不难归纳得出节点在 $[A*2^B,(A+1)*2^B-1]$，与 $[1,N]$ 取并集即可。

[考场代码](https://atcoder.jp/contests/abc321/submissions/45867716)实在太丑，见谅。

---

## 作者：robertuu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc321_e)

讲一种投机取巧的方法。

显然，这道题的树几乎是满二叉树，我们知道满二叉树中在一个点的子树上距离其为 $k$ 的点的数量是 $2^k$，这道题的也差不多。

首先，把距离 $x$ 为 $k$ 的点这样分为几部分：$x$ 子树上距离 $x$ 为 $k$ 的点、$x$ 的兄弟的子树上距离这个兄弟为 $k - 2$ 的点、$x$ 父亲的兄弟子树上距离其 $k - 3$ 的点 ... （最后会有一个特例：$x$ 的 $k$ 级祖先）

这样就可以不断向上跳（反正最多只有 $\log n$ 层），每跳一次更新一下答案，更新又分为三种情况：

（叙述中的“层”表示查询节点子树中的那一层，不是整棵树的！）

#### 情况一：需要查询的那一层是满的

这种情况很简单，答案就是 $2^{dis}$。

#### 情况二：需要查询的那一层不存在（一个点都没有）

这种情况出现时，$x \times 2^{dis} > n$，只需要进行判断即可（答案为 $0$），判断时需要注意变量溢出的情况。

#### 情况三：需要查询的那一层半满

我们需要处理出最后一个点（其实是 $n + 1$ 号点）的各个祖先在最后一层缺少几个元素，答案为 $2^{dis} - r$，$r$ 就是预处理出的那个答案。

这样问题就可以解决了！

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,k;
long long kthdep(long long x,long long k) // 判断第 k 层是否存在
{
	for(int i = 1;i <= k && x <= n+1;i++) x *= 2;
	return x;
}
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&x,&k);
		long long tmp = n + 1,cnt = 0;
		map<long long,long long> mp,d;
		d[tmp] = 0; mp[tmp] = 1;
		while(tmp != 1)
		{
			if(tmp/2*2 < tmp) mp[tmp/2] = mp[tmp]; // 在右子树
			else mp[tmp/2] = mp[tmp] + (1ll<<cnt); // 在左子树（整个右子树不存在）
			d[tmp/2] = ++cnt; tmp /= 2;
		}
		long long check = x,ans = 0;
		if(kthdep(check,k) <= n+1) ans += (1ll<<k);
		if(mp[check] && d[check] == k) ans -= mp[check];
		check = x/2*2+(x%2==0);
		x /= 2; k -= 2;
		while(x && k >= 0)
		{
			if(kthdep(check,k) <= n+1) ans += (1ll<<k);
			if(mp[check] && d[check] == k) ans -= mp[check];
			check = x/2*2+(x%2==0);
			x /= 2; k--;
		}
		if(x && k == -1) ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：OIerBoy (赞：2)

# Sol
考场没调出来，考完赶紧写发题解祭奠一下。

这道题主要就是模拟，细节比较多。

思路就是一层一层的计算贡献：

![](https://cdn.luogu.com.cn/upload/image_hosting/v5aw0cmv.png)

如图，我们首先计算出以结点 $x$ 为根的子树第 $k$ 层的结点数，再计算结点 $x$ 的父节点的另一个子节点的 $k-1$ 层的结点数，以此类推，直到 $k=1$。

思路就是这样，但是有很多的小细节，例如：

- 在计算子树第 $i$ 层的结点数时要判断是否存在这一层以及这一层是否是满的。

- 当 $k=1$ 时，需要判断当前是否时根节点，即当前 $x$ 是否为 $1$，如果是则无贡献。

具体细节请看代码。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}
#define N 200005
#define Mod 998244353
int T,n,k,x,dn;
int deep(int s){
	int dep=0;
	For(i,0,63)
	if((1ll<<i)>s){
		dep=i;break;
	}return dep;
}
int son(int x,int k){
	if(deep(x)+k>dn)return 0;
	int s=(x<<k)+(1ll<<k)-1;
	return max(min(n,s)-(x<<k)+1,0ll);	
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>k;
		dn=deep(n);
		int ans=son(x,k);
		while(x>1&&k){
			if(k==1)ans+=(x==1?0:1);
			else ans+=son(x^1,k-2);
			k--;x>>=1;
		}cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：happybob (赞：1)

简单题。

考虑枚举 LCA，显然 LCA 必然是 $x$ 的祖先。

由于是完全二叉树，枚举 LCA 的复杂度显然是 $O(\log n)$ 的。

枚举之后，转化成子问题，求点 $u$ 的子树中有多少个到 $u$ 距离为 $k$ 的点。

比较显然的，点 $x$ 的子树中距离为 $k$ 的点的编号为 $x \times 2^k, x\times2^k+1,\cdots,x\times2^k+(2^k-1)$。直接做一下就好了。



---

## 作者：rainygame (赞：1)

最后二十分钟终于过了 E……

首先我们可以把答案分成两部分：在 $x$ 的子树内和不在 $x$ 的子树内的。

考虑第一个，我们可以设两个指针 $l$ 和 $r$，初始时它们都是 $x$，然后逐步向下走。$l$ 表示能走到的数的左边，所以每次都只往左子树走；同理，$r$ 总是往右边走。最后统计也比较简单：如果没到最后一层，就是 $r-l+1$，否则就是 $[e,n]$ 和 $[l,r]$ 的并集（$e$ 表示最后一层的第一个数）

然后考虑第二种，发现路径类似于走到父亲的另一颗子树，那么直接往上走即再走到另一棵子树，就可以化为第一个问题了。

时间复杂度 $O(T \log^2 n)$。

代码中定义的 `solve(int x, int k)` 表示以 $x$ 为结点往下走 $k$ 层可以访问到的结点数量。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int t, n, k, x, tmp, cnt, ans, lcnt, rcnt;

int solve(int x, int k){
	int l(x), r(x);
	while (k && r < n){
		l <<= 1;
		r = r<<1|1;
		--k;
	}
	if (k || l > n) return 0;
	if (l < cnt || r <= n) return r-l+1;
	return n-l+1;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> t;
    while (t--){
    	cin >> n >> x >> k;
    	
    	tmp = n;
    	cnt = -1;
    	while (tmp){
    		tmp >>= 1;
    		++cnt;
		}
		cnt = 1<<cnt;
		
		ans = solve(x, k--);
		while (k >= 0 && x > 1){
			if (!k){
				++ans;
				break;
			}
			--k;
			if (x & 1) ans += solve(x-1, k);
			else ans += solve(x+1, k);
			x >>= 1;
		}
		
		cout << ans << '\n';
	}

    return 0;
}

```


---

## 作者：liyujia (赞：1)

### 题意

有一个 $N$ 个节点的完全二叉树，第 $i-1(2\leq i\leq n)$ 条边连接点 $i$ 和点 $\lfloor\frac{i}{2}\rfloor$，边权为 $1$，求出和点 $X$ 最短路距离恰好为 $K$ 的点的数量。多测。

$N,X,K\leq 10^{18}$，至多 $10^5$ 组测试数据。

### 解法

乍一看好像挺简单，仔细想又挺麻烦，实际上倒也不算麻烦...

首先，我们枚举它们的 LCA $Y$，这是个经典套路。

此时 $Y$ 子树中符合条件的点一定在 $Y$ 不是 $X$ 祖先的那个子节点 $Z$ 的子树中，或者干脆就是 $Y$，此时，子树中符合的点到 $Z$ 的距离也是确定的。

所以，我们先特判 $Y$ 符合条件的情况，就是看是否存在距离为 $K$ 的祖先。

然后问题就变成了求一个点 $Z$ 中子树中和 $Z$ 距离恰好为 $L$ 的点，只需要对上述满足条件的 $Z$ 分别求解即可。

如果这棵子树是满二叉树，那么是简单的，只需要判断最深的一个点离 $Z$ 是否大于等于 $L$，是则有 $2^L$ 种方案，否则为 $0$，显而易见。

如果只是普通的完全二叉树，此时 $Z$ 一定是 $N$ 的祖先，不妨递归为左右子树处理，因为它的左子树一定不是 $N$ 的祖先，这样就保证了时间复杂度。

再特判一些细节，这道题就做完了。时间复杂度 $O(T\log^2N)$，其中 $T$ 是数据组数。实际上只跑了 500+ms。

说起来有点长，写起来还是简单的。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, x, k;
int dep(int x){//x 的深度
    for(int i = 1; i <= 61; i++)
        if((1ll << i) - 1 >= x)
            return i;
}
int sub(int x, int k){//x 子树离 x 恰好 k 的点个数
    int l = n;
    if(x > n || k < 0) return 0;
    if(k == 0) return 1;
    if(x * 2 > n) return 0;//神奇特判们
    for(int i = 1; i <= 61; i++)//判断 x 是不是 n 的祖先
        if(l == x)
            return sub(x * 2, k - 1) + sub(x * 2 + 1, k - 1);//递归处理
        else l /= 2;
    l = x;
    int dc = 0;
    while(l * 2 <= n) l *= 2, dc++;//求 x 子树中最远的点与 x 的距离
    if(dc < k) return 0;
    return 1ll << k;
}
signed main(){
    cin >> t;
    while(t--){
        cin >> n >> x >> k;
        int ans = (dep(x) > k) + sub(x * 2, k - 1) + sub(x * 2 + 1, k - 1);//在 x 子树内
        for(int i = 1; i <= 60; i++)
            if(x > 1)
                ans += sub(x ^ 1, k - 2), k--, x /= 2;//满足条件的 Z
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：small_john (赞：0)

## 思路

首先，根据题意，容易得到这棵树是一颗完全二叉树。

接下来就是如何求一个节点 $u$ 的 $k$ 层儿子的个数。

$u$ 他的 $k$ 层儿子的最左边的一个肯定就是一直取他的做儿子，编号为 $u\times2^k$。而这一层最多有 $2^k$ 个，所以最右边的儿子编号为 $u\times2^k+2^k-1$。但最大的节点编号为 $n$，所以最右边的儿子编号为 $\min(u\times2^k+2^k-1,n)$。最后的个数就是这两个数的差加 $1$。

```cpp
int qpow(int x,int y)//快速幂
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x;
		y>>=1;
		x = x*x;
	}
	return res;
}
int get_dep(int x)//求深度
{
	int res = 0;
	while(x) res++,x/=2;
	return res;
}
int solve(int u,int dis)
{
	if(u>n) return 0;
	int depu = get_dep(u);
	if(dis>dep-depu) return 0;//如果总深度太深，就直接退出
	int mn = u*qpow(2,dis),mx = mn+qpow(2,dis)-1;
	if(mx>n) mx = n; 
	if(mn>n||mx<mn) return 0;//不合法
	int res = mx-mn+1;
	return res;
}
```

那么，如何求距离 $u$ 为 $k$ 的点呢？

最初，肯定有 $u$ 的 $k$ 级儿子。而如果 $u$ 是他父亲的左儿子，那么就还有他父亲的右儿子的 $k-2$ 级儿子。否则，就还有他父亲的左儿子的 $k-2$ 级儿子。

这样逐层往上找就行了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int __int128//防止报long long
using namespace std;

template<typename T> void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x<=9) return putchar(x+48),void();
    write(x/10);
    putchar(x%10+48);
}
template<typename T> void writen(T x)
{
    write(x);
    puts("");
}
int T,n,x,k,dep;
int qpow(int x,int y)//快速幂
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x;
		y>>=1;
		x = x*x;
	}
	return res;
}
int get_dep(int x)//求深度
{
	int res = 0;
	while(x) res++,x/=2;
	return res;
}
int solve(int u,int dis)
{
	if(u>n) return 0;
	int depu = get_dep(u);
	if(dis>dep-depu) return 0;//如果总深度太深，就直接退出
	int mn = u*qpow(2,dis),mx = mn+qpow(2,dis)-1;
	if(mx>n) mx = n; 
	if(mn>n||mx<mn) return 0;//不合法
	int res = mx-mn+1;
	return res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--)
	{
		read(n),read(x),read(k);
		dep = get_dep(n);
		int ans = solve(x,k);
		while(x>1&&k>0)
		{
			if(k==1) ans++;//特判
			else
			{
				if(x&1) ans+=solve((x/2)*2,k-2);//是他父亲的右儿子
				else ans+=solve((x/2)*2+1,k-2);//是他父亲的左儿子
			}
			x>>=1,k--;
		}
		writen(ans);
	}
	return 0;
}
```

---

## 作者：wizardMarshall (赞：0)

这道题还是有点难度的……

## 题意

题面意思为：构建一颗二叉树，求离某个点距离为 $k$ 的点的个数。

对于任意节点 $x$，它的两个节点分别是 $2x$ 和 $2x+1$。其实有点像线段树，但跟线段树没什么关系，因为线段树节点的编号没有什么实际意义（只是指代一个区间）。

通过观察样例发现，这棵二叉树的编号是按照深度优先的顺序来编号的，并且是一颗完全二叉树。这样就很好做了。

我们将在树上移动设定为一次操作。它共有以下几种情况：

- 往父亲节点走，也就是 $\lfloor x/2 \rfloor$

- 往左儿子节点走，也就是 $2x$

- 往右儿子节点走，也就是 $2x+1$

由于一个节点只有一个父亲节点，所以在经过后两种操作后就**永远不能往上走**，只能往下不回头。

然后还有一个性质，就是对于点 $x$，他子树的第 $k$ 层（$x$ 自己是第零层）的点权范围是：

$$[x\times2^k,x\times2^k+2^k-1]$$

很好理解。注意，由于总共只有 $n$ 个点，所以还要判断一下右边界有没有超出。

因此，我们枚举往上走的步数。抓一张样例图：

![](https://img.atcoder.jp/abc321/0d1a718458ffcf25a6bc26d11b3a7641.png)

举个例子，我们从点 $2$ 开始走，走两步。枚举：

不往上走，还在原地。此时判断 $2$ 这个点的子树第三层的点有几个（因为还有三步可以走，因此判断第三层）。此时第三层的点权太大，已经超出范围。

往上走一步，$\lfloor 2 / 2 \rfloor =1$，到达 $1$ 点。注意，此时不是判断 $1$ 这个子树的第二层有几个，因为可能会**走回头路**。我们只能退而求其次，往另一个儿子先走一步（也就是点 $3$），然后再求点 $3$ 子树的第一层有多少个点（$[3\times2^1,3\times2^1+2^1-1]$，也就是 $[6,7]$）。

往上走两步。这个时候 $\lfloor 1 / 2 \rfloor=0$，没有节点，直接退出。（当点为 $0$ 时就退出，因为 $k$ 很大，会有许多无用的循环）

------

## 代码

大概思路就是这样。数据范围有点大，位运算时会越界，开了 `__int128`。结合代码理解：


```c++


#include <bits/stdc++.h>
using namespace std;

#define int __int128 //为防止玄幻越界开大

int read() {//配套快读快写
	char s= getchar();
	while (s < '0' || s > '9')s = getchar();
	int sum = 0;
	while (s >= '0' && s <= '9') {
		sum = sum * 10 + s - '0';
		s = getchar();
	}
	
	return sum;
}
void print(int x) {
	if (x >= 10) {
		print(x / 10);
	}
	putchar((x % 10) + '0');
}
signed main() {
	int T = read();
	while (T--) {
		int n = read(), x = read(), k = read();
		int ans = 0;
		int last = x;
		int LOG = 1;//同样防止位运算越界
		for (int i = 0; i <= k; i++) {//往上走i步
			if (!x)break;//到0就跳出
			if (i == 0) {
				if (x <= n && k <= 64 && x * (LOG << k) <= n) {//没有往上走，判断整个子树的第k层。k<=64同样是防止越界，因为往下那么多层很大，没有意义
					ans += min(n, x * (LOG << k) + (LOG << k) - 1) - (x * (LOG << k)) + 1;//区间最左最右。注意不要超过n
				}
			}else {
				if (i == k) {//往上刚好走了k步,不能往下走
					ans++;
				}else {
					if (x * 2 == last) {//之前是2x，往另一个儿子2x+1走
						int temp = x * 2 + 1;
						if (temp <= n && (k - i - 1) <= 64 && temp * (LOG << (k - i - 1)) <= n) {//i是往上走的步数，还有1步是从当前点到另一个子树走的步
							ans += min(n, temp * (LOG << (k - i - 1)) + (LOG << (k - i - 1)) - 1) - (temp * (LOG << (k - i - 1))) + 1;//同样不要超过n
						}
					}else {//反之亦然
						int temp = x * 2;
						if (temp <= n && (k - i - 1) <= 64 && temp * (LOG << (k - i - 1)) <= n) {
							ans += min(n, temp * (LOG << (k - i - 1)) + (LOG << (k - i - 1)) - 1) - (temp * (LOG << (k - i - 1))) + 1;
						}
					}
				}
			}
			last = x;
			x /= 2;
		}
		print(ans);
		printf("\n");
		
	}
	return 0;
}


```

赛时代码较为冗长笨拙，还请谅解。

---

## 作者：Hellsing_Alucard (赞：0)

其实是个简单模拟题，我写的可能有些复杂。

对于一个点 $x$，答案的情况分为两个部分，儿子和其他点。

对于儿子，可以暴力硬求，枚举第 $k$ 层最小的儿子和最大的儿子，然后进行判断。

其他节点，你可以一步一步向上爬，如果该点是右儿子，那么查找左儿子，反之亦然。
```cpp
#include<bits/stdc++.h>

using namespace std;

#define int i128
#define i64 long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a,b,c) for(int a=(b);a<=(c);a++)
#define dn(a,b,c) for(int a=(b);a>=(c);a--)
#define pii pair<int,int>
#define pivi pair<int,vector<int> >
#define lc k<<1
#define rc k<<1|1
#define fi first
#define se second
#define endl '\n'
#define i16 short

const int N=2e5+100,M=2e6+100;
const int mod=998244353;
const int inf=0x3f3f3f3f;
const ull uinf=1e18+14;

namespace IO{
    inline int read(){
        char c=getchar();int x=0,fh=0;
        while(c<'0'||c>'9'){fh|=c=='-';c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
        return fh?-x:x;
    }
    inline void wt(int x){
        if(x<0){x=-x;putchar('-');}
        if(x>9)wt(x/10);
        putchar((x%10)^48);
    }
    inline void write(int x,bool op){
        wt(x);
        putchar(op?'\n':' ');
    }
}using namespace IO;
int n,k;
inline int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}
int len,dep;
inline int clac(int x,int pos){
    if(x==0)return 1;
    x--;
    int u=pos*2+1;
    int l=u,r=u;
    if(x>=62)return 0;
    up(i,1,x){
        l=l*2;
        r=r*2+1;
    }
    if(r<=n)return (r-l+1);
    if(l>n)return 0;
    return n-l+1;
}
inline int clac2(int x,int pos){
    if(x==0)return 1;
    x--;
    int u=pos<<1;
    int l=u,r=u;
    if(x>=62)return 0;
    up(i,1,x){
        l=l*2;
        r=r*2+1;
    }
    if(r<=n)return (r-l+1);
    if(l>n)return 0;
    return n-l+1;
}
int x;
signed main() {
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
    int T;
    T=read();
    while(T--){
        n=read();x=read();k=read();
        len=0,dep=0;//len表示这棵树有多少层是满二叉树，dep表示在第几层
        up(i,0,63){
            if((1ll<<i)-1<n&&(1ll<<(i+1))-1>=n){
                len=i;
            }
            if((1ll<<i)-1<x&&(1ll<<(i+1))-1>=x){
                dep=i+1;
            }
        }
        if(k==0){
            cout<<1<<endl;
            continue;
        }
        int upp=0,down=0;//upp表示x点上方有多少个节点距离为k，down表示下方有多少个点距离为k
        int w=k,pos=x,pre=x;
        while(pos!=1){//不停的升到父亲节点，如果该点是右儿子，那么查找左儿子，反之亦然
            pos/=2;w--;
            if(w<0)break;
            if(pre==pos*2)upp+=clac(w,pos);
            else if(pre==pos*2+1)upp+=clac2(w,pos);
            pre=pos;
        }
        int l=x,r=x;
        if(k>=62){
            down=0;
            goto F;
        }
        up(i,1,k){
            l=l*2;
            r=r*2+1;
        }
        if(r<=n)down=(r-l+1);
        else if(l>n)down=0;
        else down=n-l+1;
        F:;
        write(upp+down,1);    
    }
    return 0;
}
```

---

