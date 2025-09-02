# [ABC376F] Hands on Ring (Hard)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_f

**注：この問題は B 問題とほぼ同じ設定です。本文中で太字で示されている部分および制約のみが異なります。**

あなたはあるリングを両手で握っています。 このリングは $ N\ (N\geq\ 3) $ 個のパーツ $ 1,2,\dots,N $ によって構成されており、パーツ $ i $ とパーツ $ i+1 $ ($ 1\leq\ i\leq\ N-1 $)、およびパーツ $ 1 $ とパーツ $ N $ がそれぞれ隣接しています。

最初、左手はパーツ $ 1 $ を、右手はパーツ $ 2 $ を握っています。 あなたは、$ 1 $ 回の *操作* で以下のことを行えます。

- 片方の手を、今握っているパーツに隣接するいずれかのパーツに移動する。ただし、移動先にもう一方の手がない場合に限る。

以下の図は、初期状態およびそこから行える操作と行えない操作の例を示したもので、リングの各パーツに書き込まれた数はそのパーツの番号を、L と書かれた丸は左手を、R と書かれた丸は右手を示しています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc376_f/163f7a1ba782e2030fd80929195629b6c8f8ddb5.png)

あなたは今から与えられる $ Q $ 個の指示に順番に従う必要があります。 $ i\ (1\leq\ i\leq\ Q) $ 個目の指示は文字 $ H_i $ および整数 $ T_i $ によって表され、その意味は以下の通りです：

- 操作を何回か（$ 0 $ 回でもよい）行うことで、$ H_i $ が `L` ならば左手、`R` ならば右手が、パーツ $ T_i $ を握っている状態にする。 このとき、$ H_i $ によって指定された手ではない方の手を **動かしてもよい**。

**なお、本問題の設定および制約の下では、どのような指示も達成可能なことが証明できます。**

すべての指示に従うために必要な操作回数の合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 3\leq\ N\ \leq\ 3000 $
- $ 1\leq\ Q\ \leq\ 3000 $
- $ H_i $ は `L` または `R`
- $ 1\leq\ T_i\leq\ N $
- $ N,Q,T_i $ は整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc376/d9baddfa26f7a1ccd163cbd8ad01fde4.png) 以下のように操作を行うことで、$ Q $ 個の指示すべてに順番に従うことができます。 1. 右手をパーツ $ 2\rightarrow\ 3\rightarrow\ 4 $ と移動させることで、$ 1 $ 番目の指示に従う。 2. 左手をパーツ $ 1\rightarrow\ 6\rightarrow\ 5 $ と移動させることで、$ 2 $ 番目の指示に従う。 3. 左手をパーツ $ 5\rightarrow\ 6 $ と移動させたのち、右手をパーツ $ 4\rightarrow\ 5 $ と移動させることで、$ 3 $ 番目の指示に従う。 このとき行う操作回数の合計は $ 2+2+1+1=6 $ であり、これが最小です。

### Sample Explanation 2

操作を $ 1 $ 度も行わずに指示に従うことができる場合もあります。

## 样例 #1

### 输入

```
6 3
R 4
L 5
R 5```

### 输出

```
6```

## 样例 #2

### 输入

```
100 2
L 1
R 2```

### 输出

```
0```

## 样例 #3

### 输入

```
30 8
R 23
R 26
R 29
L 20
R 29
R 19
L 7
L 16```

### 输出

```
58```

# 题解

## 作者：Down_syndrome (赞：22)

# [ABC376F] 题解

## 题意

有一个长度为 $n$ 的环，上面有 $n$ 个位置，顺时针数分别是 $1$ 到 $n$。一开始，你的左手在位置 $1$ 上，右手在位置 $2$ 上。你的两只手都可以移动，每次可以移动到相邻的位置，但是不能两只手在同一个位置上。共有 $q$ 此操作，第 $i$ 次给出 $h_i$ 和 $x_i$，表示将左手（此时 $h_i=$ `L`）或右手（此时 $h_i=$ `R`）移动到位置 $x_i$ 上，求以此完成 $q$ 次操作的最少移动次数。

## 思路

既有思维难度又有实现难度的好题。

看到“最少”等关键词，这种最值问题的做法常常是 dp。

考虑设 $f_{i,j,k}$ 表示第 $i$ 次操作后左手在位置 $j$ 上，右手在位置 $k$ 上的最少移动次数。

这个状态正确性显然，但是需要优化。

可以发现，第 $i$ 次操作后一定有一只手在 $t_i$ 上，所以我们可以减少一维状态，设 $f_{i,j}(t_i\ne j)$ 表示第 $i$ 次操作后**另一只手**在位置 $j$ 上的最小值。

**另一只手**指的是第 $i$ 次操作没有**要求移动**的那只手。

好了，我们来考虑转移吧！

令 $\operatorname{solve}(al,ar,bl,br)$ 表示一只手原来在 $al$，后来移动到 $bl$，另一只手原来在 $ar$，后来移动到 $br$ 的最少移动次数。注意，这里**没有**强调 $l$ 一定是左手。事实上，位置相同时，是左手还是右手显然不会影响答案。

那么，我们就能轻松列出转移式子：

$$f_{i,j}=
\begin{cases} 
\min\{f_{i-1,k}+\operatorname{solve}(x_{i-1,},k,x_i,j)\}&(x_i\ne j,x_{i-1}\ne k,h_i=h_{i-1})\\
\min\{f_{i-1,k}+\operatorname{solve}(k,x_{i-1},x_i,j)\}&(x_i\ne j,x_{i-1}\ne k,h_i\ne h_{i-1})
\end{cases}$$

很明显，这样的转移时间是 $O(n^2q)$ 的，我们还要优化。

哪里还能够优化呢？

仔细观察一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/46zkcaia.png)

对于上图这种情况，左手（字母 L）想要移动到目标位置（字母 T），改如何移动？

第一种情况是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/30li3inw.png)

左手直接绕过右手（字母 R）移动到指定位置。

第二种情况是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/x9enrgst.png)

先把右手挪到位置 $6$，再把左手移过去。

注意到，**肯定不会**出现这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/zirbrn2g.png)

这种情况和第二种情况差别在哪呢？

差别在右手多挪了一步。

显然，右手多挪一步是不必要的，因为在一次操作中，没有**要求移动**的手移动的唯一目的就是给**要求移动**的手让路。

然而，让路只用让一步就够了，不需要挪到更远的地方。所以，如果右手给左手让路，那么最后**两只手一定相邻**。

这个性质给了我们启示，让我们能够优化转移。

事实上，这个性质我们可以改说成：如果一次操作后，两只手**没有相邻**，那么没有**要求移动**的手一定没有移动，也就是在原来的位置。

所以我们不必要枚举原来这只手的位置，**直接从当前位置转移就行了**。

如果一次操作后**两只手相邻**，我们依然像上述方式转移，枚举原来的手的位置。但是两只手相邻的情况很少，只有两种（一只手位置固定，另一只手在他的两边），所以枚举的复杂度可以接受。

另外，还有一种情况需要枚举手的位置，就是这一次操作**要求移动**的手和上一次操作**要求移动**的手不是同一只，并且这次操作后**两只手的位置不相邻**，那么上一次**要求移动**的手一定**没有移动**，我们只要枚举这一次**要求移动**的手原来的位置，也像上述方式转移就行了。这种情况数更少，只有一种（两只手的位置都被固定了），复杂度同样可以接受。

令 $\operatorname{adjacent}(x,y)$ 表示 $x$ 和 $y$ 相邻，$\operatorname{not\ adjacent}(x,y)$ 表示 $x$ 和 $y$ 不相邻，我们改写一下转移方程：

$$f_{i,j}=
\begin{cases} 
\min\{f_{i-1,k}+\operatorname{solve}(x_{i-1,},k,x_i,j)\}&(\operatorname{adjacent}(x_i,j),x_i\ne j,x_{i-1}\ne k,h_i=h_{i-1})\\
\min\{f_{i-1,k}+\operatorname{solve}(k,x_{i-1},x_i,j)\}&(\operatorname{adjacent}(x_i,j),x_i\ne j,x_{i-1}\ne k,h_i\ne h_{i-1})\\
f_{i-1,j}+\operatorname{solve}(x_{i-1},j,x_i,j)&(\operatorname{not\ adjacent}(x_i,j),x_i\ne j,x_{i-1}\ne j,h_i=h_{i-1})\\
\min\{f_{i-1,k}+\operatorname{solve}(k,x_{i-1},x_i,j)\}&(\operatorname{not\ adjacnet}(x_i,j),x_i\ne j,x_{i-1}\ne k,h_i\ne h_{i-1},x_{i-1}=j)
\end{cases}$$

这样时间复杂度就被我们优化到了 $O(nq)$。

做完了！——吗？

还有一个恶心的实现点，就是 $\operatorname{solve}$ 函数的值怎么求啊？

这个是真的很多细节。

具体方式就是：

枚举两只手的移动方向，是顺时针还是逆时针。然后枚举两只手的移动顺序，再判断一只手按照这个顺序移动时会不会被另一只手挡住。

如果你不会实现，或者实现错了调不出来而懊恼，可以参考一下下面代码的实现。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+5;
int n,q,ans,x[N],f[N][N];
char op[N][5];
bool between(int x,int l,int r){//x 是否在 l 到 r 的顺时针区间内
	if(l<=r) return l<=x&&x<=r;
	else return !(r<x&&x<l);
}
int solve(int al,int ar,int bl,int br){
	int ans=1e9;
	if(!between(ar,al,bl)&&!between(bl,ar,br)||!between(al,ar,br)&&!between(br,al,bl)) ans=min(ans,(bl-al+n)%n+(br-ar+n)%n);//全部顺时针 
	if(!between(ar,bl,al)&&!between(al,br,ar)||!between(al,br,ar)&&!between(br,bl,al)) ans=min(ans,(al-bl+n)%n+(ar-br+n)%n);//全部逆时针 
	if(!between(ar,al,bl)&&!between(bl,br,ar)||!between(al,br,ar)&&!between(br,al,bl)) ans=min(ans,(bl-al+n)%n+(ar-br+n)%n);//l 顺 r 逆 
	if(!between(ar,bl,al)&&!between(bl,ar,br)||!between(al,ar,br)&&!between(br,bl,al)) ans=min(ans,(al-bl+n)%n+(br-ar+n)%n);//l 逆 r 顺 
	return ans;
}
int main(){
	scanf("%d%d",&n,&q);
	op[0][0]='L';
	x[0]=1;
	memset(f,0x3f,sizeof(f));
	for(int i=2;i<=n;i++) f[0][i]=i-2;
	for(int i=1;i<=q;i++){
		scanf("%s%d",op[i],&x[i]);
		for(int j=1;j<=n;j++){//枚举另一只手在哪 
			if(j==x[i]) continue;
			if(x[i]%n+1==j||(x[i]-2+n)%n+1==j){//另一只手与目标相邻，则之前位置任选 
				if(op[i][0]==op[i-1][0]){//这次出手的手位置确定 
					for(int k=1;k<=n;k++){//枚举另一只手的位置 
						if(k==x[i-1]) continue;
						f[i][j]=min(f[i][j],f[i-1][k]+solve(x[i-1],k,x[i],j)); 
					}
				}
				else{//另一只手的位置确定 
					for(int k=1;k<=n;k++){//枚举这次出手的手的位置 
						if(k==x[i-1]) continue;
						f[i][j]=min(f[i][j],f[i-1][k]+solve(k,x[i-1],x[i],j));
					}
				}
			}
			else{//另一只手与目标不相邻，则之前就在这个位置
				if(op[i][0]==op[i-1][0]){
					if(x[i-1]!=j) f[i][j]=min(f[i][j],f[i-1][j]+solve(x[i-1],j,x[i],j));
				}
				else if(j==x[i-1]){//枚举这次出手的手的位置 
					for(int k=1;k<=n;k++){
						if(k==x[i-1]) continue;
						f[i][j]=min(f[i][j],f[i-1][k]+solve(k,x[i-1],x[i],j));
					}
				}
			}
		}
	}
	ans=1e9;
	for(int i=1;i<=n;i++) ans=min(ans,f[q][i]);
	printf("%d",ans);
	return 0;
}
```

完结撒花！留下一个赞吧！

---

## 作者：OIbishop (赞：5)

### 题目大意
$n$ 个环形格子，有两个手，初始位于 $1$，$2$。给定 $q$ 个指令，每个指令指定一只手移动到某个格子上，移动时两只手不能相互越过，期间可以移动另一只手。依次执行这些指令，问最小的移动次数。
### 解题思路
由于上一次操作会影响这一次，所以考虑 dp。

设状态为 $dp_{i,j,k}$ 表示前 $i$ 个操作左手在 $j$ 右手在 $k$ 的最小移动次数。转移十分简单，但时间复杂度为 $O(qn^2)$ 无法通过。注意到上一次操作后一只手一定在目标位置，所以可以更改状态为 $dp_{i,j}$ 表示前 $i$ 个操作上一只手在位置 $j$ 的最小移动次数。只需要分类讨论一下这一次操作和上一次操作的手是否一致即可。转移方程为 $dp_{now,i}=dp_{now-1,j}+cost(i,lstpos,j)$  
具体实现请看代码。

```cpp
#include <bits/stdc++.h>
using std :: cin ; using std :: cout;
const int N = 3005;
int n , q , dp[N][N];
#define PII std::pair<int,int>
inline PII Move1 (int p1 , int p2 , int t) // p1 -> t
{
	int c = 0; // 顺时针从p1到t, p2为另一只手的位置 
	if (p1 == t) return {0 , p2};
	if (t == p2) p2 = (t + 1) % n , c++;
	if (p2 <= p1) p2 += n; if (t <= p1) t += n; // 断环为链 
	if (t <= p2) 
	{
		c += t - p1 ;
		return {c , p2 % n};
	}
	if (t > p2) 
	{
		c += t - p2 + 1 , p2 = t + 1;
		c += t - p1 ;
		return {c , p2 % n};
	}
	assert (0);
}
inline PII Move2 (int p1 , int p2 , int t) // 逆时针 
{
	PII lazy = Move1 (n - 1 - p1 , n - 1 - p2 , n - 1 - t);
	return {lazy.first , n - 1 - lazy.second};
}
signed main ()
{
	cin >> n >> q;
	memset (dp , 0x3f , sizeof dp);
	char lst = 'L' ; int pos = 0; dp[0][1] = 0;
	for (int j = 1; j <= q; j++)
	{
		char opt ; int t; cin >> opt >> t; --t; // 为了方便，将1~n转化为0~n-1 
		for (int i = 0; i < n; i++)
		{
			int p1 = pos , p2 = i;
			if (lst ^ opt) p1 ^= p2 ^= p1 ^= p2;
			PII now = Move1 (p1 , p2 , t);
			dp[j][now.second] = std::min (dp[j][now.second] , dp[j - 1][i] + now.first);
			now = Move2 (p1 , p2 , t);
			dp[j][now.second] = std::min (dp[j][now.second] , dp[j - 1][i] + now.first);
		}
		lst = opt , pos = t;
	}
	cout << *std::min_element (dp[q] , dp[q] + n);
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：3)

思路简单，但是写起来有点复杂。建议先把 B 的 $\mathcal{O}(q)$ 直接计算的写了这道题会好写一点。

显然记录 $f_i$ 表示另一只手在 $i$ 的最小代价。记上一次手移到的点是 $las$。

如果这一次和上一次移动的手是一样的。不妨移动的都是左手，那么右手在上次偏移过之后不动，左手移动就可以了。

另一种情况有点复杂。不妨上一次移动的是左手，这一次移动的是右手。首先就是另一只手不动，这和上面的情况是差不多的。

另一种情况就是左手、右手都移动。比如左手在右手的顺时针方向，然后同时顺时针移动。那么是可以看成右手先调整到左手逆时针方向后 $1$ 格；然后右手移动到指定位置，左手在指定位置顺时针方向后 $1$ 格；最后调整左手位置。这种情况就这个 dp 即可。

最后调整可以移动的手的位置。感觉赛时写了挺久导致没时间写 G 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3005, inf = 0x3f3f3f3f;
int n, q, ans, x, f[N], g[N], las, y, z, dist;
char s[3], lst[3];
int main(){
//	freopen("data.in", "r", stdin);
	scanf("%d%d", &n, &q);
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	lst[0] = 'L';
	las = 1;
	for(int i = 2; i <= n; i++){
		f[i] = i - 2;
	}
	while(q--){
		scanf("%s%d", s, &x);
		if(s[0] == lst[0]){
			if(las == x) continue ;
			for(int i = 1; i <= n; i++){
				if(i == las || i == x){
					g[i] = inf;
					continue ;
				}
				if((las < i && i < x) || (x < i && i < las)){
					g[i] = f[i] + (n - abs(las - x));
				}
				else{
					g[i] = f[i] + abs(las - x);
				}
			}
		}
		else{
			for(int i = 1; i <= n; i++){
				if(i == las) continue ;
				if((i < las && las < x) || (x < las && las < i)){
					g[las] = min(g[las], f[i] + n - abs(i - x));
				}
				else{
					g[las] = min(g[las], f[i] + abs(i - x));
				}
			}
			y = las;
			y--;
			if(y == 0) y = n;
			dist = (n + x - y) % n;
			dist = min(dist, n - dist);
			g[x % n + 1] = min(g[x % n + 1], f[y] + dist * 2);
			
			y = las % n + 1;
			z = x - 1;
			if(z == 0) z = n;
			dist = (y + n - x) % n;
			dist = min(dist, n - dist);
			g[z] = min(g[z], f[y] + dist * 2);
			g[x] = inf;
		}
		for(int i = (x % n + 1) % n + 1, j = x % n + 1; i ^ x; i = i % n + 1, j = j % n + 1){
			g[i] = min(g[i], g[j] + 1);
		}
		for(int j = (x + n - 2) % n + 1, i = (j + n - 2) % n + 1; i ^ x; i = (i == 1 ? n : i - 1), j = (j == 1 ? n : j - 1)){
			g[i] = min(g[i], g[j] + 1);
		}
		for(int i = 1; i <= n; i++){
			f[i] = g[i];
			g[i] = inf;
//			printf("f[%d] = %d\n", i, f[i]);
		}
		las = x, lst[0] = s[0];
	}
	ans = inf;
	for(int i = 1; i <= n; i++){
		ans = min(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Neil_Qian (赞：3)

# [ABC376F] Hands on Ring (Hard) 题解

一开始以为 B 是这题的部分分，唐完了。不过以下两个函数是可以用的：

```cpp
inline int movel(int L,int R,int x){//左边移到x
	if(R==x)return 1e9;
	if(min(x,L)<=R&&R<=max(x,L))return n-abs(x-L);
	else return abs(x-L);
}
inline int mover(int L,int R,int x){//右边移到x
	if(L==x)return 1e9;
	if(min(x,R)<=L&&L<=max(x,R))return n-abs(x-R);
	else return abs(x-R);
}
```

其实和 B 最大的不同在于可以动另一个端点。很容易设计出一个动态规划：$f_{i,L,R}$ 表示左端点在 $L$，右端点在 $R$ 的最小代价。状态很明显只有 $O(nQ)$。

考虑转移。设原来的位置是 $L,R$，新的位置是 $L_1,R_1$，则代价可以用上述函数轻松表示出来。但容易发现很多转移是无效的，$L,R$ 所延申出来的状态远远没有 $O(n)$，其实只有以下情况：

- 不该移动的不移动。

- 不该移动的为了让出位置，到达该移动到的新的位置的左右。因为一旦移动，只能是为了让出位置，必然尽可能少移动。

然后就做完了，时间复杂度 $O(nQ)$。细节比较多，给出赛时代码。

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;
const int N=3002;int n,Q,x[N],dp[N][N],cost;char t[N];
inline int movel(int L,int R,int x){
	if(R==x)return 1e9;
	if(min(x,L)<=R&&R<=max(x,L))return n-abs(x-L);
	else return abs(x-L);
}
inline int mover(int L,int R,int x){
	if(L==x)return 1e9;
	if(min(x,R)<=L&&L<=max(x,R))return n-abs(x-R);
	else return abs(x-R);
}
int main(){
	// freopen(".in","r",stdin),freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),
	cin>>n>>Q,memset(dp,0x3f,sizeof(dp)),t[0]='L',x[0]=1,dp[0][2]=0;
	for(int i=1;i<=Q;i++){
		cin>>t[i]>>x[i];
		for(int j=1;j<=n;j++){
			int L,R,T[3]={(x[i]-2+n)%n+1,x[i]%n+1,(t[i]==t[i-1]?j:x[i-1])};
			if(t[i-1]=='L')L=x[i-1],R=j;
			else L=j,R=x[i-1];
			for(int id=0,l;id<3;id++){
				l=T[id];int L1,R1;
				if(t[i]=='L')L1=x[i],R1=l;
				else L1=l,R1=x[i];
				if(L1==R1)continue;
				dp[i][l]=min(dp[i][l],dp[i-1][j]+
				min(movel(L,R,L1)+mover(L1,R,R1),mover(L,R,R1)+movel(L,R1,L1)));
			}
		}
	}
	return cout<<*min_element(dp[Q]+1,dp[Q]+n+1)<<"\n",0;
}
```

---

## 作者：zhm080507 (赞：2)

# [AT_abc376_F](https://atcoder.jp/contests/abc376/tasks/abc376_f)

#### 题目大意

左右手可以在一个环上以一的代价移动到相邻位置（不能重叠）给定 $q$ 次询问要求将某一只手移动到给定位置花费的最小代价之和。

#### 算法分析

我们先想转移方式：

首先容易想到一个 $O(n^3)$ 的转移方程：即对每一次询问，枚举上一次不固定手的位置和这一次不固定手的位置。但是会超时。

但我们发现一个性质：如果确定了上一次的不固定手的位置，那么转移到这一次操作的不固定手的位置也是确定的（当然分两种转的方向）。有点难想但我们可以考虑以下情况：

- 如果不需要移动另一只手，那么显然最有情况是固定的；

- 如果需要让路，那么显然是放到目标位置的下一个位置。

可能会认为这样不一定最优，但只要我们按两个方向都跑一边，就不会有问题。（即顺时针需要让路，逆时针一定不需要，所以肯定会得到最优解）

转移方式确定了，现在考虑如何转移：

我们想到如果我们确定了旋转方向，那么我们可以很容易地变环为链，有挡路的情况直接让路就行了。

具体实现见代码。

#### code

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=3123,inf=1e9;
int n,q,lst,pos,opt,x;
char ch;
int f[N][N],ans;

struct node{
	int ps,dis;
};

int num(char x){
	if(x=='L') return 0;
	else return 1;
}

node clac(int p1,int p2,int to){//只顺时针操作的答案 
	if(p2<p1) p2+=n;
	if(to<p1) to+=n;//保证p1在最左边 
	if(to<p2) return {p2%n,(to-p1)%n};
	//如果目标在中间，直接移动就行了
	int d=(to-p2+1)+(to-p1);
	//代价为 移动p2 + 移动p1 
	return {(to+1)%n,d};
}
node clac2(int p1,int p2,int to){
	node tmp=clac(n-p1-1,n-p2-1,n-to-1);
	//实际上就是反过来算一次 
	return {n-tmp.ps-1,tmp.dis};
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	ans=inf;
	//两维f[i][j]表示第i轮不固定的那一个在j位置
	//具体原理就是没有意义的情况值是 inf 
	for(int i=0;i<=q;i++)
		for(int j=0;j<n;j++)
			f[i][j]=inf;
	f[0][1]=0;//初始时只有（2-1）可能有意义 
	//这里将值域变为0~n-1方便取模运算
	lst=0;pos=0;
	for(int i=1;i<=q;i++){
		cin>>ch>>x;
		opt=num(ch);
		x--;
		for(int j=0;j<n;j++){
			int p1=pos,p2=j;
			//ps是上一轮固定的位置，j是枚举的上一轮的位置 
			if(lst!=opt) swap(p1,p2);
			//如果上一轮动的和这一轮不一样，交换（因为ps是固定的
			node tmp=clac(p1,p2,x) ;//计算把p1动到x的代价和另一只手的位置
			f[i][tmp.ps]=min(f[i][tmp.ps],f[i-1][j]+tmp.dis);
			tmp=clac2(p1,p2,x);//同上，但方向相反
			f[i][tmp.ps]=min(f[i][tmp.ps],f[i-1][j]+tmp.dis); 
		}
		lst=opt,pos=x;
		//为下次询问记录 
	}
	for(int i=0;i<n;i++)
		ans=min(ans,f[q][i]);
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：postpone (赞：2)

这题硬分类讨论比较难写，提供一个简单一点的思路。

可以把“左手或右手移动到某位置”简化为“一只手移动到某位置”。下面称这个要求动的手为“主手”，另外一个是“副手”。

主手要移动到某位置，不能碰到副手，又因为代价要尽可能小，则仅当副手“挡路”了，才会一点一点的挪动，那么可以发现，这两只手如果都动了，它们动的方向肯定是相同的。

现在再分类为主手顺时针动和逆时针动，就简单许多了。

以顺时针举例：算出主手和副手顺时针移动到目标的距离，设为 $dx$ 和 $dy$（$dx$ 为主手），若 $dx \geq dy$，说明若要顺时针移动，副手就“挡路”了，则副手需要移动到目标后面一格（顺时针方向），反之副手不“挡路”，还在原来的位置。

再回到怎么处理“左右”和“主副”，一种简便的方法是：把转移的过程封装成一个函数，参数为主手的位置、副手的位置和目标位置。记录上一次主手是哪只手，若不同，则传参反一下就行。

围绕“副手在哪里”建立状态方程即可。

代码可以参考 [jls 的赛时代码](https://atcoder.jp/contests/abc376/submissions/58951485)，简洁易懂。

---

## 作者：不知名用户 (赞：2)

赛时一直在想 G 就没怎么想这题，输麻了。

### 题意

双手拿着一个戒指，戒指看成一个 $n$ 个点的环，编号为 $1,2,\cdots,n$，$i(1\le i<n)$ 和 $i+1$ 相邻，$n$ 和 $1$ 相邻。你可以将一个手指移动到该手指相邻的位置，但是要求另一只手此时不在目标位置。

最开始左手在 $1$ 位置，右手在 $2$ 位置。你需要依次遵循 $q$ 个指示，第 $i$ 个指示由手的编号（`L` 或 `R`）和目标位置组成，表示要把该手移动到目标位置。

求最小移动次数。本题和 B 题唯一的区别是可以移动另一只手。

### 做法

DP。$f[i][j]$ 表示完成第 $i$ 个指示后另一只手在位置 $j$ 时的最小操作次数。不好转移。

容易发现操作次数最小的方案每步肯定是把指定的手往某个方向移动，如果撞到另一只手就推着走，一步当两步。所以一个状态只有两种转移，即两个方向，其余转移都是不必要的。虽然导致 DP 数组存的部分和上面的意义不符，但是答案是不会大的，因为每步不存在更优的做法。

时间复杂度和状态数一样，$O(nq)$ 的。

状态转移部分直接上代码，分讨有亿点多：

```cpp
int a = x[i-1], b = j;
if(c[i-1]=='R') swap(a,b);
if(c[i]=='R') swap(a,b);
//向右
int L = a, R = b, g = x[i];
if(R<L) R += n;
if(g<L) g += n;
if(L<=R&&R<=g) Min(f[i][md(g+1)],f[i-1][j]+g+1-R+g-L);
else Min(f[i][b],f[i-1][j]+g-L);
//向左
L = a, R = b, g = x[i];
if(L<g) L += n;
if(R<g) R += n;
if(g<=R&&R<=L) Min(f[i][md(g-1)],f[i-1][j]+R-g+1+L-g);
else Min(f[i][b],f[i-1][j]+L-g);
```

### 完整代码

<https://atcoder.jp/contests/abc376/submissions/59006261>

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3010;
int f[N][N];
char c[N];
int n, x[N];

int md(int x){x%=n;if(!x)x=n;return x;}
void Min(int &x, int y){x=min(x,y);}

int main()
{
	int q, i, j;
	scanf("%d%d", &n, &q);
	memset(f,0x3f,sizeof f);
	c[0] = 'L', x[0] = 1, f[0][2] = 0;
	for(i=1;i<=q;i++)
	{
		c[i] = getchar();while(c[i]!='L'&&c[i]!='R') c[i] = getchar();
		scanf("%d", &x[i]);
		for(j=1;j<=n;j++) if(f[i-1][j]!=f[0][0])
		{
			int a = x[i-1], b = j;
			if(c[i-1]=='R') swap(a,b);
			if(c[i]=='R') swap(a,b);
			//向右
			int L = a, R = b, g = x[i];
			if(R<L) R += n;
			if(g<L) g += n;
			if(L<=R&&R<=g) Min(f[i][md(g+1)],f[i-1][j]+g+1-R+g-L);
			else Min(f[i][b],f[i-1][j]+g-L);
			//向左
			L = a, R = b, g = x[i];
			if(L<g) L += n;
			if(R<g) R += n;
			if(g<=R&&R<=L) Min(f[i][md(g-1)],f[i-1][j]+R-g+1+L-g);
			else Min(f[i][b],f[i-1][j]+L-g);
		}
	}
	int ans = 1e9;
	for(i=1;i<=n;i++) ans = min(ans,f[q][i]);
	printf("%d", ans);
	return 0;
}
/*
f[i][j] 表示前 i 次操作后另一个位置在 j
直接转移不好做，但是一个状态只有两种转移，其余转移一定是不优的。
*/
```

---

## 作者：Cosine_Func (赞：1)

显然 dp。

先设计状态。设 $dp_{i,j,k}$ 为前 $i$ 个操作，左手在 $j$，右手在 $k$ 时的最小操作次数。显然会炸。考虑优化。显然只需要保留一个位置，故设 $dp_{i,j}$ 为前 $i$ 个操作，另一只手在 $j$ 时的最小操作次数。状态转移很显然，只需要模拟顺时针和逆时针操作，中间遇到另一只手就“推”着到达终点。时间复杂度 $O(NQ)$。

[参考代码](https://atcoder.jp/contests/abc376/submissions/60362014)

---

## 作者：superl61 (赞：1)

[题目传送门](https://atcoder.jp/contests/abc376/tasks/abc376_f) 

一个朴素的状态定义的想法是 $f_{i, j, k}$ 表示当前是第 $i$ 个操作，左手在 $j$ 位置，右手在 $k$ 位置，最少的操作数。采用刷表法转移的话可以做到 $O(qn^2)$。

发现每个操作中有一只手的位置是给定的，因此前面的状态设计中其实有很多无用状态。

考虑 $f_{i, j}$ 表示当前是第 $i$ 个操作，未指定的那只手在 $j$ 位置，最少的操作数。转移可以做到 $O(nq)$。

现在最麻烦的问题是怎么算移动的步数。赛场上没有想出来断环成链还有翻转的神犇做法，这里给一种码量很大但分讨很清楚的方法，分讨基本上写出一种就可以全部复制粘贴。

记 `Move1(L, R, target)` 表示要移动的那只手位置在 $L$，要移动到 $target$，另一只手在 $R$，顺时针的移动步数。`Move2(L, R, target)` 就是逆时针。

根据 $L, R$ 的位置关系，$target$ 在二者之间还是两边，一个 `Move` 总共涉及到 $4$ 种情况，条件注意写清楚，最后就是要知道两点之间顺（逆）时针的移动步数，这个可以在 $O(n^2)$ 的时间内预处理一个 $dis$ 数组以便直接调用。

时间复杂度 $O(n^2 + nq)$。我的代码中还特判了一下第一次移动。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i(l);i<=(r);++i)
#define G(i,r,l) for(int i(r);i>=(l);--i)
using namespace std;
using ll = long long;
char buf[100], *p1 = buf, *p2 = buf;
inline int gc(){
	return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 100, stdin), p1 == p2) ? EOF : *p1 ++;
}
inline int rd(){
	int x = 0; char ch; bool f = 1;
	while(!isdigit(ch = gc())) f ^= (ch == '-');
	do x = (x << 3) + (x << 1) + (ch ^ 48); while(isdigit(ch = gc()));
	return f ? x : -x;
}
const int N = 3005;
const int inf = 0x3f3f3f3f;
struct Node{
	int u, v, d;
};
char H[N];
int f[N][N], dis[N][N][2], Target[N];
int n, q;
void Min(int &x, int y){
	if(x > y) x = y;
}
Node Move1(int L, int R, int target){ // 顺时针 
	if(L == target){
		return (Node){L, R, 0};
	}
	if(L > R){ 
		if(target > L || target < R){// 不被阻挡
			return (Node){target, R, dis[L][target][0]};	
		}
		else{// 被阻挡 
			int ret;
			if(target == n) ret = 1;
			else ret = target + 1;
			return (Node){target, ret, dis[L][target][0] + dis[R][ret][0]};
		}
	}
	else{
		if(target > L && target < R){// 不被阻挡
			return (Node){target, R, dis[L][target][0]};
		}
		else{// 被阻挡 
			int ret;
			if(target == n) ret = 1;
			else ret = target + 1;
			return (Node){target, ret, dis[L][target][0] + dis[R][ret][0]};
		}
	}
}
Node Move2(int L, int R, int target){ // 逆时针
	if(L == target){
		return (Node){L, R, 0};
	} 
	if(L <= R){// 不被阻挡
		if(target < L || target > R){
			return (Node){target, R, dis[L][target][1]};	
		}
		else{// 被阻挡
			int ret;
			if(target == 1) ret = n;
			else ret = target - 1;
			return (Node){target, ret, dis[L][target][1] + dis[R][ret][1]};
		}
	}
	else{
		if(target > R && target < L){// 不被阻挡
			return (Node){target, R, dis[L][target][1]};
		}
		else{// 被阻挡
			int ret;
			if(target == 1) ret = n;
			else ret = target - 1;
			return (Node){target, ret, dis[L][target][1] + dis[R][ret][1]};
		}
	}
}
signed main(){
	n = rd(), q = rd();
	F(st, 1, n) {
		int x = st;
		F(i, 1, n){
			if(++ x > n) x = 1;
			dis[st][x][0] = i;
			dis[st][x][1] = n - i;
		}	
	}
	memset(f, 0x3f, sizeof(f));
	F(i, 0, q - 1){
		while(!isalpha(H[i + 1] = gc()));
		Target[i + 1] = rd(); // i + 1轮的操作
		
		if(!i){
			if(H[i + 1] == 'L'){
				Node move1 = Move1(1, 2, Target[i + 1]);
				Min(f[1][move1.v], move1.d);
				
				Node move2 = Move2(1, 2, Target[i + 1]);
				Min(f[1][move2.v], move2.d);
			}
			else{
				Node move1 = Move1(2, 1, Target[i + 1]);
				Min(f[1][move1.v], move1.d);
				
				Node move2 = Move2(2, 1, Target[i + 1]);
				Min(f[1][move2.v], move2.d);
			}
		}
		else{
			int Mainpoint = Target[i];
			F(Subpoint, 1, n){
				if(H[i + 1] == H[i]){
					Node move1 = Move1(Mainpoint, Subpoint, Target[i + 1]);
					Min(f[i + 1][move1.v], f[i][Subpoint] + move1.d);
					
					Node move2 = Move2(Mainpoint, Subpoint, Target[i + 1]);
					Min(f[i + 1][move2.v], f[i][Subpoint] + move2.d);
//					cerr << i << ' ' << move1.u << ' ' << move1.v << ' ' << move1.d << '\n';
//					cerr << i << ' ' << move2.u << ' ' << move2.v << ' ' << move2.d << '\n';
				}
				else{
					Node move1 = Move1(Subpoint, Mainpoint, Target[i + 1]);
					Min(f[i + 1][move1.v], f[i][Subpoint] + move1.d);
					
					Node move2 = Move2(Subpoint, Mainpoint, Target[i + 1]);
					Min(f[i + 1][move2.v], f[i][Subpoint] + move2.d);
//					cerr << i << ' ' << move1.u << ' ' << move1.v << ' ' << move1.d << '\n';
//					cerr << i << ' ' << move2.u << ' ' << move2.v << ' ' << move2.d << '\n';
				}
			}
		}
	}
	int ans = inf;
	F(i, 1, n) Min(ans, f[q][i]);
	printf("%d", ans);
	return fflush(0);
}
```

---

## 作者：zrl123456 (赞：1)

## 题目

[[ABC376F] Hands on Ring (Hard)](https://www.luogu.com.cn/problem/AT_abc376_f)   

题目考察：dp。  
题目简述：  
有一个有 $n$ 个节点的环，一开始你的两只手分别在 $1$ 节点和 $2$ 节点，每次你的手可以移动到相邻两个节点（即假设原来在 $x$ 处，那么就能移动到 $(x+n-2)\bmod n+1$ 和 $x\bmod n+1$），前提是另一只手不在将要移动的格子上。  
有 $q$ 次操作，每次操作（$h_i,t_i$）要求你将左手或右手（$h_i$）移到某一个格子（$t_i$），问所有操作结束之后最少移动多少次。  
数据范围：  
- $3\le n\le 3000$。
- $1\le q\le 3000$。
- $\forall i\in[1,n],h_i$ 要么是 `L`，要么是 `R`。
- $1\le t_i\le n$。
## 做法
### 朴素 dp
**显然**，我们可以得到一个状态为 $\Theta(n^2q)$ 的 dp，设 $f_{i,j,k}$ 为第 $i$ 次操作中左手放在了 $j$ 节点，右手放在了 $k$ 节点，转移方程为（$\text{dist}(x,y,z)$ 表示在不经过 $z$ 点的情况下，从 $x$ 到 $y$ 的距离）：  
$$f_{i,j,k}=\min_{j_0=1}^n(\min_{k_0=1}^n(f_{i-1,j_0,k_0}+\min(\text{dist}(j_0,j,k_0)+\text{dist}(k_0,k,j),\text{dist}(k_0,k,j_0)+\text{dist}(j_0,j,k))))$$
但是每个状态都需要 $\Theta(n^2)$ 转移，时间复杂度（$\Theta(qn^4)$）不可接受（尽管能用滚动数组滚掉第一位）。  
> #### 证明
> 证明先移动一个手再移动另一个手更优。  
> 分类讨论：  
> 1. 如果另一只手挡住了这只手的运动路线，直接将另一只手移到一个位置就行了。
> 2. 否则另一只手不动就行了。

于是我们想到了后面的优化。  
### 优化 $1$
我们发现，实际上有意义的状态并不多，第 $i$ 次操作你的一只手一定要在 $t_i$ 节点上，这样的话有意义的状态就变成了 $\Theta(n)$ 个，但时间复杂度仍然是 $\Theta(qn^3)$。  
### 优化 $2$
我们又发现，有意义的状态只有 $\Theta(n)$ 个，所以我们不需要 $\Theta(n^2)$ 枚举上一个状态，直接用 `map` 或直接压维的方式解决，时间复杂度为 $\Theta(qn^2)$（可能带 $\log$）。  
### 优化 $3$
我们又双叒叕发现，每个上一个状态只会出现 $1$ 个第 $2$ 种情况，于是我们换种方式转移（我不会告诉你我忘了叫什么了）。  
这样每次操作的有效状态为：$dp_{i,i-1}$ 和 $dp_{i,i+1}$（所有的上一个的有效状态均可转移），其他的 $dp_{i,j}$（一个有效状态只会转移一个）。  
时间复杂度为 $\Theta(qn)$。  
### 代码
[这呢](https://atcoder.jp/contests/abc376/submissions/59063708)

---

## 作者：HNOIRPplusplus (赞：1)

看到这题，联想到 B 题，我们考虑 DP。

设 `dp[k][i][j]` 表示当前进行到第 $k$ 轮，左手在 $i$，右手在 $j$，最小的移动次数为多少。转移有两种，一种是顺时针挪，一种是逆时针挪。

挪动的时候检查一下在目标方向上和目的地的距离，以及和另一只手的距离。如果和目的地更近就直接转移过去，否则需要把另一只手先挪到目的地后一格，然后再把询问的手挪过去。

本质上来说题目并没有什么思路难度，但是实现难度相较于思路来说还是有点大，写的时候写了我有一段时间。

容易发现直接这么开是开不下的，所以我们需要把 $k$ 的那一维滚动掉。同时从上一次转移过来到下一次的状态是有限的，所以我使用了 `map<pair<int, int>, int>` 的方式进行 dp 数组的存放，~~同时也导致我的代码十分的丑陋~~。在本题数据表现十分优秀。

代码（丑陋的）：

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200005;

vector<int> g[N];
int dis[N], vis[N], r[N];

signed main() {
  int n, q;
  cin >> n >> q;
  map<pair<int, int>, int> last;
  last[make_pair(1, 2)] = 0;
  while(q--) {
    char h;
    int t;
    cin >> h >> t;
    map<pair<int, int>, int> last2;
    if(h == 'L') {
      for(auto i : last) {
        int l = i.first.first, r = i.first.second;
        int dis1 = (l >= r ? l - r : l - r + n), dis2 = (l >= t ? l - t : l - t + n);
        if(dis1 > dis2) {
          if(last2.count(make_pair(t, r)) == 0) {
            last2[make_pair(t, r)] = i.second + dis2;
          } else {
            last2[make_pair(t, r)] = min(last2[make_pair(t, r)], i.second + dis2);
          }
        } else {
          if(last2.count(make_pair(t, (t + n - 2) % n + 1)) == 0) {
            last2[make_pair(t, (t + n - 2) % n + 1)] = i.second + dis2 + dis2 - dis1 + 1;
          } else {
            last2[make_pair(t, (t + n - 2) % n + 1)] = min(last2[make_pair(t, (t + n - 2) % n + 1)], i.second + dis2 + dis2 - dis1 + 1);
          }
        }
        dis1 = (l <= r ? r - l : r - l + n), dis2 = (l <= t ? t - l : t - l + n);
        if(dis1 > dis2) {
          if(last2.count(make_pair(t, r)) == 0) {
            last2[make_pair(t, r)] = i.second + dis2;
          } else {
            last2[make_pair(t, r)] = min(last2[make_pair(t, r)], i.second + dis2);
          }
        } else {
          if(last2.count(make_pair(t, t % n + 1)) == 0) {
            last2[make_pair(t, t % n + 1)] = i.second + dis2 + dis2 - dis1 + 1;
          } else {
            last2[make_pair(t, t % n + 1)] = min(last2[make_pair(t, t % n + 1)], i.second + dis2 + dis2 - dis1 + 1);
          }
        }
      }
    } else {
      for(auto i : last) {
        int l = i.first.first, r = i.first.second;
        int dis1 = (r >= l ? r - l : r - l + n), dis2 = (r >= t ? r - t : r - t + n);
        if(dis1 > dis2) {
          if(last2.count(make_pair(l, t)) == 0) {
            last2[make_pair(l, t)] = i.second + dis2;
          } else {
            last2[make_pair(l, t)] = min(last2[make_pair(l, t)], i.second + dis2);
          }
        } else {
          if(last2.count(make_pair((t + n - 2) % n + 1, t)) == 0) {
            last2[make_pair((t + n - 2) % n + 1, t)] = i.second + dis2 + dis2 - dis1 + 1;
          } else {
            last2[make_pair((t + n - 2) % n + 1, t)] = min(last2[make_pair((t + n - 2) % n + 1, t)], i.second + dis2 + dis2 - dis1 + 1);
          }
        }
        dis1 = (r <= l ? l - r : l - r + n), dis2 = (r <= t ? t - r : t - r + n);
        if(dis1 > dis2) {
          if(last2.count(make_pair(l, t)) == 0) {
            last2[make_pair(l, t)] = i.second + dis2;
          } else {
            last2[make_pair(l, t)] = min(last2[make_pair(l, t)], i.second + dis2);
          }
        } else {
          if(last2.count(make_pair(t % n + 1, t)) == 0) {
            last2[make_pair(t % n + 1, t)] = i.second + dis2 + dis2 - dis1 + 1;
          } else {
            last2[make_pair(t % n + 1, t)] = min(last2[make_pair(t % n + 1, t)], i.second + dis2 + dis2 - dis1 + 1);
          }
        }
      }
    }
    last = last2;
  }
  int ans = 1145141919810114514;
  for(auto i : last) {
    ans = min(ans, i.second);
  }
  cout << ans;
}
```

---

## 作者：Wzhone (赞：0)

这道题蒟蒻考场上面想了好久把所有需要的结论都找到了但是最后还是没写出来然后对着 $O(n^2)$ 的数量级打了一个 $O(n)$ 的代码 qwq

好了前言到此结束我们来看题目。

首先有一个非常显然的暴力，我们令 $dp_{i,j,k}$ 表示现在在第 $i$ 个操作，左手在 $j$ 位置，右手在 $k$ 位置，我们需要的答案最少是多少。

不难发现上一步操作固定了一个位置，那么我们考虑去掉一维，然后用一个数组 $dp_{i,j}$ 表示现在在第 $i$ 个操作，副手在 $j$ 位置，我们需要的答案最少是多少。

但是这个时候复杂度仍然是 $O(n^3)$，因为我们要枚举原来副手的位置。复杂度陷入了瓶颈，我们要想办法优化。

我们考虑如何固定了初始状态和目标状态的一只手的时候该怎么做。

我们不难发现另外一只手多动一定是不优的，哪怕实在要动下一轮再动贡献也不会减少，那么我们考虑这一轮的贡献就只剩下了两种：

- 推着另一只手到目标位置
- 绕过另一只手到目标位置

贡献是容易 $O(1)$ 求得的。我们发现这两种方式对应了两种目标状态，所以这样一个状态只会转移到两个最优状态。

其他状态一定不优于这两个状态，所以正确性我们甚至可以不管，这样我们把转移复杂度降到了 $O(1)$ 级别，可以通过此题。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define F(i, j, k) for(ll i = j; i <= k; i++)
#define dF(i, j, k) for(ll i = j; i >= k; i--)
#define fi first 
#define se second 
#define eb emplace_back

const ll MAXN = 3010;

ll dp[MAXN][MAXN];
char c[MAXN]; ll p[MAXN];
ll n, q;

ll get_dis(ll pre1, ll pre2, ll nex1, ll& nex2){
    if(nex1 < pre1) nex1 += n;
    if(pre2 < pre1) pre2 += n;
    if(pre2 > nex1){
        nex2 = pre2; nex2 %= n;
        return nex1 - pre1;
    }else{
        int ans = 0; nex2 = nex1 + 1;
        ans += nex2 - pre2; ans += nex1 - pre1;
        nex2 %= n;
        return ans;
    }
}

ll get_dis2(ll pre1, ll pre2, ll nex1, ll& nex2){
    ll ans = get_dis(n - pre1, n - pre2, n - nex1, nex2);
    nex2 = n - nex2; nex2 = (nex2 + n) % n;
    return ans;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    
    memset(dp, 0x3f, sizeof dp);

    c[0] = 'L'; dp[0][1] = 0; p[0] = 0;

    F(i, 1, q){
        cin >> c[i] >> p[i]; p[i] --;
        F(j, 0, n - 1){
            ll pre1, pre2, nex1, nex2;
            if(c[i] == c[i - 1]) pre1 = p[i - 1], pre2 = j;
            else pre1 = j, pre2 = p[i - 1];
            nex1 = p[i]; int ans = get_dis(pre1, pre2, nex1, nex2);
            dp[i][nex2] = min(dp[i][nex2], ans + dp[i - 1][j]);
            ans = get_dis2(pre1, pre2, nex1, nex2);
            dp[i][nex2] = min(dp[i][nex2], dp[i - 1][j] + ans);
        }
    }
    
    ll ans = 0x7fffffff;
    F(i, 0, n - 1) ans = min(ans, dp[q][i]);
    
    cout << ans;

    return 0;
}
```

---

## 作者：lhyuu (赞：0)

考虑描述一个状态，只需两个维度分别记录左手和右手的位置即可。观察到，每次操作都会将状态的其中一个维度固定。只需枚举另一只手的位置就可以确定当前状态。

于是设计 $dp$ 状态 $f_{i,j}$ 表示第 $i$ 次操作时，未被确定的手的位置为 $j$ 时的最小操作次数。

然后分类讨论：

- 操作 $i-1$ 和 $i$ 均固定了左（右）手：

  
  则此时 $j$ 有两种情况，一种是回归 [简单版](https://atcoder.jp/contests/abc376/tasks/abc376_b)，不更改另一只手的位置，继承 $i-1$ 时另一只手的状态，代价加上 $t_{i-1}$ 移动到 $t_i$ 的步数；另一种是移动另一只手，则最终另一只手一定与 $t_i$ 相邻，枚举上一个状态中另一只手的位置转移即可。

- 操作 $i-1$ 固定了左（右）手，操作 $i$ 固定了右（左）手：

  同理，两种情况：不更改另一只手的位置，或将另一只手移动到当前手的相邻位置。

---

