# [ABC310G] Takahashi And Pass-The-Ball Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc310/tasks/abc310_g

高橋くんが $ N $ 人います。

$ i $ 番目の高橋くんは、整数 $ A\ _\ i $ とボール $ B\ _\ i $ 個を持っています。

高橋くんたちは $ 1 $ 以上 $ K $ 以下の整数 $ x $ を一様ランダムに選び、次の操作を $ x $ 回繰り返します。

- すべての $ i $ について、$ i $ 番目の高橋くんは $ A\ _\ i $ 番目の高橋くんに自分が持っているボールをすべて渡す。
 
操作は $ N $ 人によって同時に行われることに注意してください。

$ i=1,2,\ldots,N $ について、一連の操作が終了したとき $ i $ 番目の高橋くんが持っているボールの個数の期待値を $ {}\bmod{998244353} $ で求めてください。

 期待値 $ {}\bmod{998244353} $ の定義 この問題で求める期待値は必ず有理数になることが証明できます。 また、この問題の制約下では、求める期待値を既約分数 $ \frac\ yx $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。 このとき、$ y\equiv\ xz\pmod{998244353} $ を満たす $ 0\leq\ z\lt998244353 $ がただ一つ存在するので、$ z $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times10^5 $
- $ 1\leq\ K\leq\ 10^{18} $
- $ K $ は $ 998244353 $ の倍数でない
- $ 1\leq\ A\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ 0\leq\ B\ _\ i\lt998244353\ (1\leq\ i\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

操作を $ 2 $ 回行うと、それぞれの高橋くんが持っているボールは以下のようになります。 !\[\](https://img.atcoder.jp/abc310/eeca44e66744660173a72967840e158a.png) $ x=1 $ が選ばれた場合、それぞれの高橋くんが持っているボールの数は $ 4,0,1,2,5 $ 個です。 $ x=2 $ が選ばれた場合、それぞれの高橋くんが持っているボールの数は $ 2,0,4,1,5 $ 個です。 よって、求める期待値はそれぞれ $ 3,0,\dfrac52,\dfrac32,5 $ です。 $ {}\bmod{998244353} $ での値を求めるとそれぞれ $ 3,0,499122179,499122178,5 $ となるので、これらを順に空白区切りで出力してください。

### Sample Explanation 2

$ 1 $ 回以上操作すると、すべてのボールを $ 1 $ 番目の高橋くんが持つことになります。

## 样例 #1

### 输入

```
5 2
3 1 4 1 5
1 1 2 3 5```

### 输出

```
3 0 499122179 499122178 5```

## 样例 #2

### 输入

```
3 1000
1 1 1
1 10 100```

### 输出

```
111 0 0```

## 样例 #3

### 输入

```
16 1000007
16 12 6 12 1 8 14 14 5 7 6 5 9 6 10 9
719092922 77021920 539975779 254719514 967592487 476893866 368936979 465399362 342544824 540338192 42663741 165480608 616996494 16552706 590788849 221462860```

### 输出

```
817852305 0 0 0 711863206 253280203 896552049 935714838 409506220 592088114 0 413190742 0 363914270 0 14254803```

## 样例 #4

### 输入

```
24 100000000007
19 10 19 15 1 20 13 15 8 23 22 16 19 22 2 20 12 19 17 20 16 8 23 6
944071276 364842194 5376942 671161415 477159272 339665353 176192797 2729865 676292280 249875565 259803120 103398285 466932147 775082441 720192643 535473742 263795756 898670859 476980306 12045411 620291602 593937486 761132791 746546443```

### 输出

```
918566373 436241503 0 0 0 455245534 0 356196743 0 906000633 0 268983266 21918337 0 733763572 173816039 754920403 0 273067118 205350062 0 566217111 80141532 0```

# 题解

## 作者：Purslane (赞：9)

# Solution 1

把传球当做连边，你会得到一个内向基环树。

然后求出 $[1,k]$ 时间内每个人每个时刻拥有球的总数，最后除以 $k$ 即可。

考虑跟踪每一组球。他的路径肯定是在非环边上跳父亲，然后在环上绕圈圈。

可以用树上前缀和与环上前缀和解决。

不过没调出来，至今不知道问题在哪。

# Solution 2

可以搞的形式化一点。

我们定义一个初始矩阵 $\mathbf A_{1\times n}$ 表示每个人目前拥有的球的个数。

有一个转移矩阵 $\mathbf T_{n \times n}$ 表示传球的过程。那么一次传球后矩阵变为 $\mathbf A \mathbf T$。$\mathbf T$ 只有在第 $i$ 行第 $a_i$ 列有值 $1$。

于是你想求的就是 $\sum_{i=1}^k \mathbf A\mathbf T^i$。

如果 $k=2m$ 那么可以化简为 $\sum_{i=1}^m \mathbf A\mathbf T^i+(\sum_{i=1}^m \mathbf A \mathbf T^i) \times \mathbf T^m$。

否则 $k=2m+1$。我们单独把 $\mathbf A\mathbf T$ 放在一旁，令 $\mathbf A'=\mathbf A\mathbf T$ 就可以化成上面的形式。

其实你发现 $T^m$ 的实际意义是 $m$ 次传球后每个人的球传给了谁。

因此它依旧是每一行只有一个位置有值。所以可以 $O(n)$ 求一次乘法。

我们递归地处理问题，返回 $\sum_{i=1}^k \mathbf A\mathbf T^i$ 和 $\mathbf T^k$ 即可。

时间复杂度 $O(n \log K)$。足以通过本题。

代码：[link](https://atcoder.jp/contests/abc310/submissions/44593308)。

---

## 作者：小木虫 (赞：8)

### Preface
有点小套路的一道题目，但是如果你能熟练使用倍增的话本题会很简单。  
### Problem  
给你一个 $n$ 个点的内向基环树森林，每个点有点权。  
Alice 会随机选一个 $1$ 到 $k$ 之间的数 $x$（$k$ 给定）。  

然后在 $x$ 秒内，每秒每个点会将其点权贡献给父亲（父亲的点权加上了这个点的点权），然后这个点减去自身的点权。  
这些点的操作是同时做的。

问每个点最后的期望权值是多少,模 $998244353$。  
$n\leq 2\times 10^5,k\leq 10^{18}$。  
保证 $k$ 不是模数的倍数。
### Solution  
容易发现这个期望是假的，题目实际上是要我们求出所有 $k$ 种情况下某个点的权值的加和。  
那么显然地，每个点会向 $k$ 步之内的每个点做贡献。 

然后你看到了基环树。  
我会分讨！先对每个子树开深度桶，差分，然后贡献挂环再处理环的差分！   

好想法，但是这太麻烦了，题目给的不止一个基环树，而且分类讨论会写的非常难看，也不好调，我们来想一个更加聪明的简单做法。  

有一个很显然，但是大多数人不会注意到的事实，就是倍增的适用性。  
当然，树和序列是倍增最常用的场景，但是观察倍增的过程，我们可以得出一个结论，即每个元素的后继不多于一个的图或序列是可以倍增的。  

所以，理所当然地，环和基环树也可以进行倍增。  

考虑这个题的倍增，我们要求的是某个点被贡献的权值总和，显然倍增的意义是通过 $2^i$ 步内可贡献给点 $u$ 的权值和，这个可以简单实现，然后将数层倍增组合。

在实现上，我们对 $k$ 的二进制从下到上进行倍增，若 $k$ 的这一位为 $1$ 则对答案加上目前状态的贡献，同时将目前状态滚动使得状态与答案对齐。  

复杂度 $O(n\log k)$。

code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,k,inv;
void qpow(int a,int b){
	inv=1;a%=mod;
	while(b){
		if(b&1)inv=(inv*a)%mod;
		a=(a*a)%mod;b>>=1;
	}
}
void move(vector <int> &a,vector <int> b){
	vector <int> res(n);
	for(int i=0;i<n;i++)res[i]=a[b[i]];
	a=res;
}
vector <int> modify(vector <int> a,vector <int> x){
	vector <int> res(n);
	for(int i=0;i<n;i++)res[a[i]]=(res[a[i]]+x[i])%mod;
	return res;
}
void add(vector <int> &x,vector <int> y){
	for(int i=0;i<n;i++)x[i]=(x[i]+y[i])%mod;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k;qpow(k,mod-2);
	vector <int> a(n),b(n);
	for(auto &x:a)cin>>x,x--;
	for(auto &x:b)cin>>x;
	vector <int> ans(n);
	b=modify(a,b);
	while(k){
		if(k&1){
			add(ans,b);
			b=modify(a,b);
		}
		add(b,modify(a,b));
		move(a,a);k>>=1;
	}
	for(auto x:ans)cout<<(x*inv)%mod<<" ";
	return 0;
}
```


---

## 作者：Rain_chr (赞：5)

### 题目翻译

有 $n$ 个人，每个人有一个传递的对象 $a_i$，还有 $b_i$ 个球。

每次传递时所有人同时将自己的所有球传给传递对象，一场游戏的结果就是每个人最后得到的球数。

给定一个 $k$，从 $[1,k]$ 中等概率随机抽取一个 $x$，表示游戏进行 $x$ 轮。

问最后游戏结果的期望。

### 题目分析

显然，等概率抽取就是诈骗，可以算出 $k$ 轮游戏结果的总和再除以 $k$。

而每个人都有一个传递的对象，转换为图论就是每个点有一条出边，可以意识到这就是一个基环树森林。

那既然是基环树，按照套路，答案就可以分为环和树来计算。

1. 树

在 $k$ 趋近于无穷大时，树上的球都会进入环。观察每个点上的球只会传给祖先，便可以想到树上差分再求和，算出只在树上的点 $k$ 次收到的球。

**注意：这 $k$ 有可能小于深度，所以树上差分时要跟深度取最小值**

2. 树环交接

在最大深度次轮游戏后，所有的球都会集中到环上。所以我们可以提前处理这一部分，并且求出最终每个节点的球都会落在环的哪一个节点上。

设最大深度为 $D$，环长为 $len$，节点 $i$ 会对环上所有点产生 $\lfloor \frac{D}{len} \rfloor \times a_i$ 的贡献。

而其余的次数，就是从 $i$ 入环的节点处往后贡献 $D \bmod len$ 个，这里我们用差分解决。

3. 环

至此，我们已经清空了树上的球，所有的球都落在了环上。我们可以按照树环交接部分的思想，分成整体和剩余来处理，在此不再赘述。

综上，我们以 $\operatorname O(n)$ 的时间复杂度解决了这题。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=998244353;
int a[N],b[N];
vector<int> g[N];
vector<int> dot;

bool book[N];
void dfs1(int x)
{
	dot.push_back(x);
	book[x]=1;
	for(int i=0;i<g[x].size();i++)
	{
		int to=g[x][i];
		if(book[to])
			continue;
		dfs1(to);
	}
}
vector<int> ring;
bool vis[N],key[N];
int base;
bool dfs2(int x)
{
	vis[x]=1;
	if(vis[a[x]])
	{
		ring.push_back(x);
		base=a[x];
		vis[x]=0;
		key[x]=1;
		return x!=base;
	}
	else
	{
		bool op=dfs2(a[x]);
		vis[x]=0;
		if(op)
		{
			key[x]=1;
			ring.push_back(x);
			return x!=base;
		}
		else return 0;
	}
}
int ans[N];
int n;
int bz[20][N]; 
int d[N];
int tag[N];
int bl[N];
void dfs3(int x,int fa,int grand)
{
	bl[x]=grand;
	for(int i=0;i<g[x].size();i++)
	{
		int to=g[x][i];
		if(to==fa||key[to])
			continue;
		d[to]=d[x]+1;
		dfs3(to,x,grand);
	}
}
void dfs4(int x,int fa)
{
	for(int i=0;i<g[x].size();i++)
	{
		int to=g[x][i];
		if(to==fa||key[to])
			continue;
		dfs4(to,x);
		tag[x]+=tag[to];
		tag[x]%=mod;
	}
}
int dif[N<<1],w[N];
int rk[N];
void work(int s,int k)
{
	ring.clear();
	dot.clear();
	dfs1(s); //所有基环树上的点都给找出来 
	dfs2(s); //找环 
	reverse(ring.begin(),ring.end());
	//统计树上节点的贡献（环上的不加）
	for(int i=0;i<ring.size();i++) //求出深度 
	{
		rk[ring[i]]=i+1;
		dfs3(ring[i],0,ring[i]);
	}
	for(int i=0;i<dot.size();i++) //树上差分 
	{
		int x=dot[i],t=d[x],w=b[x];
		if(t)
		{
			tag[bz[0][x]]=(tag[bz[0][x]]+w)%mod;
			t=min(t,k+1);
			for(int j=log2(t);j>=0;j--)
				if(t>=(1<<j))
				{
					t-=(1<<j);
					x=bz[j][x];
				}
			tag[x]=(tag[x]-w+mod)%mod;
		}
	} 
	for(int i=0;i<ring.size();i++) //树上求和 
		dfs4(ring[i],0);
	for(int i=0;i<dot.size();i++)	
		ans[dot[i]]+=tag[dot[i]],ans[dot[i]]%=mod;
	//清空树上的节点 
	int Max=0,len=ring.size();
	for(int i=0;i<dot.size();i++)
		Max=max(Max,d[dot[i]]);
	int sum=0;
	for(int i=0;i<=len*2;i++) dif[i]=0;
	for(int i=0;i<=len;i++) w[i]=0;
	for(int i=0;i<dot.size();i++)
	{
		int x=dot[i],now=min(Max,k)-d[x];
		if(now<0) continue; 
		sum=(sum+now/len*b[x]%mod)%mod;
		dif[rk[bl[x]]+key[x]]=(dif[rk[bl[x]]+key[x]]+b[x])%mod;
		dif[rk[bl[x]]+now%len+1]=(dif[rk[bl[x]]+now%len+1]-b[x]+mod)%mod;
		w[(rk[bl[x]]+now%len-1)%len+1]+=b[x]; 
		w[(rk[bl[x]]+now%len-1)%len+1]%=mod;
	}
	for(int i=1;i<=len*2;i++)
		dif[i]+=dif[i-1],dif[i]%=mod;
	for(int i=0;i<ring.size();i++)
	{
		ans[ring[i]]+=dif[i+1]+dif[i+len+1]+sum;
		ans[ring[i]]=ans[ring[i]]%mod;
	}
	k-=Max;
	if(k<0)
		return ;
	//环上互相传递 
	sum=0;
	for(int i=1;i<=len;i++)
		sum+=w[i],sum%=mod;
	for(int i=0;i<len;i++)
		ans[ring[i]]=(ans[ring[i]]+k/len%mod*sum%mod)%mod;
	sum=0;
	for(int i=1;i<=k%len;i++)
		sum+=w[i],sum%=mod;
	for(int i=k%len+1;i<=k%len+len;i++)
	{
		ans[ring[(i-1)%len]]=(ans[ring[(i-1)%len]]+sum)%mod;
		sum-=w[(i-k%len-1)%len+1];
		sum+=w[(i-1)%len+1]; 
		sum=(sum%mod+mod)%mod;
	}
}
int ksm(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		bz[0][i]=a[i];
		g[i].push_back(a[i]);
		g[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		cin>>b[i];
	//倍增
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n;j++)
			bz[i][j]=bz[i-1][bz[i-1][j]];
	//找出每一个基环树
	for(int i=1;i<=n;i++)
	{
		if(book[i])
			continue;
		work(i,k);
	}  
	int inv=ksm(k%mod,mod-2);
	for(int i=1;i<=n;i++)	
		cout<<ans[i]*inv%mod<<endl;
	return 0;
} 
```

### 总结

本题是基环树的好题，把基环树树环结合的思想体现的淋漓尽致。

只是代码长度有3.5kb，对于初学者而言过难，适合基环树进阶。





---

