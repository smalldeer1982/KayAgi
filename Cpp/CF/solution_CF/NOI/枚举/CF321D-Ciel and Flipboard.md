# Ciel and Flipboard

## 题目描述

Fox Ciel has a board with $ n $ rows and $ n $ columns, there is one integer in each cell.

It's known that $ n $ is an odd number, so let's introduce ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/6479833d305e8df8be298c6d130b2c56818252f6.png). Fox Ciel can do the following operation many times: she choose a sub-board with size $ x $ rows and $ x $ columns, then all numbers in it will be multiplied by -1.

Return the maximal sum of numbers in the board that she can get by these operations.

## 说明/提示

In the first test, we can apply this operation twice: first on the top left $ 2×2 $ sub-board, then on the bottom right $ 2×2 $ sub-board. Then all numbers will become positive.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/bba86be06e5760920ea393fc6a496f40415e324b.png)

## 样例 #1

### 输入

```
3
-1 -1 1
-1 1 -1
1 -1 -1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
-2 0 0 0 -2
0 -2 0 -2 0
0 0 -2 0 0
0 -2 0 -2 0
-2 0 0 0 -2
```

### 输出

```
18
```

# 题解

## 作者：FutaRimeWoawaSete (赞：8)

**sol of CF321D**

我们凭感觉如果不是 $m$ 的特殊限制，这是个不太可做的问题，所以从 $m = \frac{n + 1}{2}$ 开始入手！！！1

考虑先从比较暴力地想法入手，设 $c(x,y)$ 表示点 $(x,y)$ 是否取反，即采用 $0/1$ 表示。

我们发现在 $m = \frac{n + 1}{2}$ 的意义下，存在以下两条限制：

$\begin{cases}c(x,y) \oplus c(x,m) \oplus c(x,y+m) = 0,y<m\\c(x,y)\oplus c(m,y) \oplus c(x+m,y) = 0,x<m\end{cases}$

动笔画画你就可以发现，任意一个子矩形覆盖到了第 $x$ 行，一定覆盖 $(x,y)$ 与 $(x,y+m)$ 两者中的一个点，而且**必定覆盖** $c(x,m)$ 这个点，也就是同行的中点以及两边距离为中距的两个节点满足的关系。

反转一下看，列也满足这个性质。所以不管怎么覆盖每次总有两个变量一起变化，于是得到了上面的两条约束。

然后你还发现，子矩阵的操作是线性无关的，这是因为任何一个子矩阵操作不可能被表示成若干个其它子矩阵操作。

再进一步，我们发现对于 $c$ 的取值，我们显然知道所有 $c(x,y)$ 满足 $1 \leq x,y\leq m$ 就可以还原出整个矩阵的 $c$，所以总的填发有 $2 ^ {m \times m}$ 种，这不恰好对应了子矩阵操作的方案数 $2 ^ {m \times m}$ 吗，所以确定 $c$ 的过程和操作的过程是等价的。

后面的其实反而更简单一些，我们考虑先枚举第 $m$ 列上前 $m$ 行的 $c$，根据 $c(i,m) \oplus c(m,m) \oplus c(i+m,m)=0$ 可以推出所有的 $c(i+m,m)$ ，即第 $m$ 列的情况。

然后你发现对于前 $m - 1$ 列两两列之间元素它们是互相不影响的，因为它们之和第 $m$ 列及以后的元素相关；同理，前 $m - 1$ 行两两行的元素之间是互相不影响的，因为它们只和 $m$ 行及以后的元素相关。

所以我们可以得出，在填 $c$ 的意义下，若确定了第 $m$ 行第 $m$ 列的信息，前 $m - 1$ 行/列之间的 $c$ 是互相不影响的，这个结论在原来的子矩阵操作意义下一点也不显然。

当然第 $m$ 行上即任意的 $c(m,i)$ 之间也是互相不影响的。上面的式子也很好地说明了这一切，$c(m,i)$ 仅与第 $i$ 列的信息有关。

可以发现第 $m$ 列和第 $m$ 行的元素是信息量比较大的，我们考虑第 $m$ 行的信息，由于两两是不互相影响的所以我们单独考虑每一个列，第 $i$ 个列上先枚举 $c(m,i)$，然后依次枚举每一列上的所有元素后取 $\max$，得到了前 $m$ 行/列的 $c$ 即可还原整个矩形。

注意到在枚举完前 $m - 1$ 行/列的每一个元素时可以得到其在限制中对应的剩下元素的 $c$ 的情况，$\max$ 应取这些元素的和。

时间复杂度 $O(n ^ 2 2 ^ m)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 36;
#define ll long long
#define int ll
const int Inf = 1e12;
int n,m,c[Len][Len],a[Len][Len];
#define v(x,y) (c[x][y] ? -a[x][y] : a[x][y])
inline int c3(int x,int y,int i)
{
	c[x][y] = i , c[x + m][y] = c[x][y] ^ c[m][y];
	c[x][y + m] = c[x][y] ^ c[x][m] , c[x + m][y + m] = c[x][y + m] ^ c[m][y + m];
	int mx = v(x , y) + v(x + m , y) + v(x , y + m) + v(x + m , y + m);
	return mx;
}
inline int c2(int y,int i)
{
	c[m][y] = i , c[m][y + m] = c[m][y] ^ c[m][m];
	int mx = v(m , y) + v(m , y + m);
	for(int i = 1 ; i < m ; i ++) mx += max(c3(i , y , 0) , c3(i , y , 1));
	return mx;
}
inline int c1()
{
	int mx = 0;
	for(int i = 1 ; i <= n ; i ++) mx += v(i , m);
	for(int i = 1 ; i < m ; i ++) mx += max(c2(i , 0) , c2(i , 1));
	return mx; 
}
ll ans = -Inf;
signed main()
{
	scanf("%lld",&n);for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= n ; j ++) scanf("%lld",&a[i][j]);
	m = (n + 1) / 2;
	for(int i = 0 ; i < (1 << m) ; i ++) 
	{
		for(int j = 1 ; j <= m ; j ++) c[j][m] = (i >> (j - 1)) & 1;
		for(int j = m + 1 ; j <= n ; j ++) c[j][m] = c[j - m][m] ^ c[m][m];
		ans = max(ans , c1());
	}
	printf("%lld\n",ans);
	return 0;	
} 
```

---

## 作者：xzyxzy (赞：8)

## orz wfj_2048

Tag：我也不知道叫什么，叫思维题吧。。

# Step1 性质

设$rev[i][j]$表示$(i,j)$这个点最终状态$(0/1)$是否取反

那么有$rev[i][k]\ xor \  rev[i][m]\ xor \ rev[i][m+k]=0$

因为第i行这三个点要么被翻到2个要么0个

同理列也有这个性质

# Step2 推导

那么我们枚举左上的一个四分之一矩形就可以对称出所有位置了

同时会发现，在$(1..m-1,1..m-1)$这四分之一个矩形内的点的$rev$线性无关，也就是说相互独立互不影响，可以同时取最优情况

当$(x,y)(x<m,y<m)$取某种情况时，它对称的三个点的情况取决于$(x,m),(m,y)$的决策，那么我们从枚举一个矩形降到了枚举两条线段

继续优化

如果只枚举$(1...m-1,m)$呢，可以发现$(m,k),k<m$的决策只影响到$(1..m-1,k)$的对称情况，所以$(m,1..m-1)$这些点的决策又是相互独立的，同时可以取到最优决策

由此，只需要枚举$(1...m-1,m)$的决策，然后分别嵌套取最优方案即可

~~代码极好理解~~
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int r[40][40],v[40][40],n,m,ans=-1e9;
int F(int x,int y){return r[x][y]?-v[x][y]:v[x][y];}
int query(int x,int y,int d)
{
	r[x][y]=d; r[x+m][y]=r[m][y]^d;
	r[x][y+m]=r[x][m]^d;
	r[x+m][y+m]=r[m][y+m]^r[x][y+m];
	return F(x,y)+F(x+m,y)+F(x,y+m)+F(x+m,y+m);
}
int query(int y,int d)
{
	int res=0; r[m][y]=d; r[m][y+m]=r[m][m]^d;
	res+=F(m,y)+F(m,y+m);
	for(int x=1;x<m;x++) res+=max(query(x,y,0),query(x,y,1));
	return res;
}
int Calc()
{
	int res=0; for(int x=1;x<=n;x++) res+=F(x,m);
	for(int y=1;y<m;y++) res+=max(query(y,0),query(y,1));
	return res;
}
int main()
{
	scanf("%d",&n); m=(n+1)>>1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&v[i][j]);
	for(int zt=0;zt<(1<<m);zt++)
	{
		for(int x=1;x<=m;x++) r[x][m]=zt>>(x-1)&1;
		for(int x=1;x<m;x++) r[x+m][m]=r[m][m]^r[x][m];
		ans=max(ans,Calc());
	}
	printf("%d\n",ans);
}

```
~~虽然和本题完全没有关系但是还是打个广告~~「[blog](https://www.cnblogs.com/xzyxzy/)」

---

## 作者：lottle1212__ (赞：3)

# [CF321D Ciel and Flipboard](https://www.luogu.com.cn/problem/CF321D)

这道题被搞到模拟赛里去了，我显然没做出来。我一直在考虑的都是贪心策略或者动态规划，但是知道了正确解法后，再看 $n\leq 33$ 的数据范围，才觉自己的想法很可笑。

先说解法。既然数据范围小，但又不是那么小，那一定是和枚举有关，但又不用全枚举。而减少枚举次数就要看题中的特殊性质。数据范围是 $1000$ 似乎并没有什么用处，而 $m=\frac{n+1}2$ 以及 $n$ 为奇数则显得尤为特殊。$m=\frac{n+1}2$ 刚好比 $n$ 的一半大一些。不难注意到，如果矩阵覆盖到了第 $i$ 行，则 $a_{i, m}$ 一定会被覆盖到。进一步，$a_{i, j}, a_{i, j+m}(j<m)$ 中有且仅有一个位置被该矩阵覆盖到。设 $vis_{i, j}$ 表示 $a_{i, j}$ 是否取反，则 $vis_{i, j}\oplus vis_{i, m}\oplus vis_{i, j+m}=0(j<m)$。同理 $vis_{i, j}\oplus vis_{m, j} \oplus vis_{i+m, j}=0(j<m)$。这说明，如果知道了前 $m$ 行、前 $m$ 列是否反转，就可以知道整个矩阵的每个位置是否反转，则有 $2^{m^2}$ 种情况，这与直接枚举是否反转每个矩阵的情况总数相同，说明只要满足以上两个式子的矩阵都是合法的矩阵。观察这个式子，在知道了第 $m$ 行、第 $m$ 列的所有 $vis$ 值的情况下，被第 $m$ 行、$m$ 列所分成的四个区块中一个块内相邻的两个位置是没有关系的，每一个位置只和与其坐标相差 $m$ 的位置有关，所以只要把每个 $(i, j)(i, j<m)$ 和 $(i, j+m), (i+m, j), (i+m, j+m)$ 放一起计算贡献，其余都可以分开来。因此可以考虑令第一个式子中 $i=m$，则有 $vis_{m, j}\oplus vis_{m, m}\oplus vis_{m, j+m}=0$。此时去枚举第 $m$ 行的前 $1$ 至 $m$ 个位置的 $vis$ 值，就可以知道第 $m$ 行的全部 $vis$ 值。然后再观察第 $m$ 列，如果知道了第 $vis_{i, m}(i<m)$，就可以由 $vis_{i, m}\oplus vis_{m, m}\oplus vis_{i+m, m}=0$ 知道 $vis_{i+m, m}$ 的值。接着，对于第 $i$ 行的第 $j(j<m)$ 列，如果知道其 $vis$ 值，就容易知道 $vis_{i+m, j}, vis_{i, j+m}, vis_{i+m, j+m}$ 的值。则在 $O(2^m)$ 枚举完第 $m$ 行的前 $m$ 个位置，计算出整个第 $m$ 行后，就可以分别做每一行 $i(i<m)$，枚举 $vis_{i, m}$，再对于该行每一列 $j(j<m)$，分别枚举 $vis_{i, j}$，就知道 $vis_{i+m, j}, vis_{i, j+m}, vis_{i+m, j+m}$，一起计算 $a_{i, j}, a_{i+m, j}, a_{i, j+m}, a_{i+m, j+m}$ 的贡献，把枚举出每一组 $vis$ 的贡献计算出后求最大，然后累加起来即可。这样子是 $O(n^2)$ 的。因此总复杂度 $O(2^mn^2)$。具体实现见[代码](https://codeforces.com/problemset/submission/321/311407452)。

最后讲讲做完题后的思考。对于我最初的想法，显然是不现实的，应当尽早排除。而这题的教训就是在暴力枚举前务必观察性质，有些部分可以独立枚举的就分开来，于是大大降低了复杂度。

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF321D)。

## 思路

其实不难想，普通的暴力是 $\mathcal O (2^{n^2})$。

每个点的状态有两种，假设经过若干次操作后得到的矩阵是 $a'$，那么我们称 $a'_{i,j}=a_{i,j}$ 的状态为 $0$，$a'_{i,j}=-a_{i,j}$ 的状态为 $1$。

本题的关键在于 $m=\frac{n+1}{2}$，对于每个 $(i,j),(i,m),(i,j+m),(j<m)$，一次修改一定会改变两个点的状态或者不改变状态，令 $c_{i,j}$ 表示点 $(i,j)$ 的最终状态，那么显然有 $c_{i,j}\oplus c_{i,m}=c_{i,j+m}(j<m)$，$c_{i,j}\oplus c_{m,j}=c_{i+m,j},(i<m)$。

也就是说，我们只需枚举左上角 $m\times m$ 矩阵的状态就能确定整个矩阵的状态，时间复杂度 $\mathcal O(2^{m^2})$。

对于一个点 $(i,j),(i,j<m)$，它只会影响到 $4$ 个点，深掘性质发现左上角 $m\times m$ 矩阵的每个数互相独立，也就是每个数的取值并不会影响到另一个数的取值，因此我们可以只枚举左上角 $m\times m$ 矩阵的第 $m$ 列 与 $m$ 行，再贪心的选出左上角矩阵剩下的数，时间复杂度 $\mathcal O (2^nm^2)$。

那么正解就很显然了，只枚举左上角矩阵的第 $m$ 列，贪心的选出第 $m$ 行，时间复杂度 $\mathcal O (2^mm^2)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=100;
int n,m;
int a[Maxn][Maxn];
int c[Maxn][Maxn];

ll ret,ans;

inline int F(int x,int y,int k){
    return k?-a[x][y]:a[x][y];
}
inline int calc(int y,int x,int k,int v1,int v2){
    return F(x,y,k)+F(x+m,y,k^v1)+F(x,y+m,k^v2)+F(x+m,y+m,k^v1^v2^c[m][m]);
}
inline int work(int x,int k){
    int res=F(m,x,k)+F(m,x+m,k^c[m][m]);
    for(int i=1;i<m;i++)
        res+=max(calc(x,i,0,k,c[i][m]),calc(x,i,1,k,c[i][m]));
    return res;
}

int main(){
    scanf("%d",&n);
    m=(n+1)/2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    
    for(int i=0;i<(1<<m);i++){
        ret=0;
        for(int j=0;j<m;j++) c[j+1][m]=(i>>j&1),ret+=F(j+1,m,c[j+1][m]);
        for(int j=1;j<m;j++) ret+=max(work(j,0),work(j,1));
        for(int j=1;j<m;j++) ret+=F(j+m,m,c[j][m]^c[m][m]);
        ans=max(ans,ret);
    }
    printf("%lld",ans);

    system("pause");
    return 0;
}
/*
9
-1 -1 1 1 1 -1 -1 1 1
1 -1 -1 1 1 1 -1 -1 1
-1 1 1 1 1 -1 1 1 1
-1 1 1 1 -1 1 -1 -1 -1
-1 -1 1 -1 1 -1 -1 1 -1
1 1 1 -1 1 1 1 1 -1
-1 1 -1 -1 1 -1 1 -1 -1
1 -1 1 -1 1 1 -1 1 -1
1 -1 1 -1 -1 -1 1 -1 1
*/
```

---

## 作者：111101q (赞：1)

其实就是换一个方式进行枚举，求最大值（根据对称性将矩阵枚举退化为线性枚举）时间复杂度 $O(2^nn^2)$ 

ACcode:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[40][40],n,m,ans=-1e9;
bool vis[40][40];
int num(int x,int y){
	return vis[x][y]?-a[x][y]:a[x][y];
}
int query(int x,int y,bool d){
	vis[x][y]=d;vis[x+m][y]=vis[m][y]^d;
	vis[x][y+m]=vis[x][m]^d;
	vis[x+m][y+m]=vis[m][y+m]^vis[x][y+m];
	return num(x,y)+num(x+m,y)+num(x,y+m)+num(x+m,y+m);
}
int q(int y,bool d){
	int res=0;
	vis[m][y]=d;vis[m][y+m]=vis[m][m]^d;
	res+=num(m,y)+num(m,y+m);
	for(int x=1;x<m;x++)res+=max(query(x,y,0),query(x,y,1));
	return res;
}
int Clac(){
	int res=0;
	for(int i=1;i<=n;i++)res+=num(i,m);
	for(int i=1;i<m;i++)res+=max(q(i,0),q(i,1));
	return res;
}
int main(){
	cin>>n;
	m=n+1>>1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cin>>a[i][j];
	}
	for(int i=0;i<(1<<m);i++){
		for(int x=1;x<=m;x++)vis[x][m]=i>>(x-1)&1;
		for(int x=1;x<m;x++)vis[x+m][m]=vis[m][m]^vis[x][m];
		ans=max(ans,Clac());
	}
	cout<<ans<<endl;
	return 0;//Codeforces
   //ACcode
}
```

---

## 作者：Expert_Dreamer (赞：0)

一道不错的~~模拟~~枚举题。如果认为自己枚举不错的话，那么可以试一试。

### 题目大意
给你一个 $n \times n$ 的矩阵，每次可以把其中 $m \times m$ 的矩阵取反，这里面 $m=\lceil\frac{n}{2}\rceil$。问矩阵中数的总和的最大值。
### 思路
考虑到 $n \le 33$，尝试把矩阵变成线性数组，不难观察到时间复杂度被优化成了 $O(2^{\frac{n}{2}}m^2)$。

如果只用一个数组的话，代码会非常乱，所以我们再开一个数组记录每一个位置的状态。这题的关键就是反转的矩阵都是固定的，且都为 $m$，于是不难想到，前 $m-1$ 列都是独立的。这样一个计算答案的函数就出来了。
```cpp
int work(){
	int res=0;
	for(int i=1;i<=n;i++) res+=w(i,m);
	for(int i=1;i<m;i++) res+=max(q(i,0),q(i,1));
	return res;
}
```
又发现每一行也是独立的。
```cpp
int q(int y,bool d){
	int res=0;
	mp[m][y]=d;
    mp[m][y+m]=mp[m][m]^d;
	res+=w(m,y)+w(m,y+m);
	for(int x=1;x<m;x++) res+=max(q1(x,y,0),q1(x,y,1));
	return res;
}
```
完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50][50],n,ans=INT_MIN;
bool mp[50][50];
int w(int x,int y){
    return mp[x][y]?-a[x][y]:a[x][y];
}
#define m (n+1)/2
int q1(int x,int y,bool d){
	mp[x][y]=d;
    mp[x+m][y]=mp[m][y]^d;
	mp[x][y+m]=mp[x][m]^d;
	mp[x+m][y+m]=mp[m][y+m]^mp[x][y+m];
	return w(x,y)+w(x+m,y)+w(x,y+m)+w(x+m,y+m);
}
int q(int y,bool d){
	int res=0;
	mp[m][y]=d;
    mp[m][y+m]=mp[m][m]^d;
	res+=w(m,y)+w(m,y+m);
	for(int x=1;x<m;x++) res+=max(q1(x,y,0),q1(x,y,1));
	return res;
}
int work(){
	int res=0;
	for(int i=1;i<=n;i++) res+=w(i,m);
	for(int i=1;i<m;i++) res+=max(q(i,0),q(i,1));
	return res;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=0;i<(1<<m);i++){
		for(int x=1;x<=m;x++) mp[x][m]=i>>(x-1)&1;
		for(int x=1;x<m;x++) mp[x+m][m]=mp[m][m]^mp[x][m];
		ans=max(ans,work());
	}
	cout<<ans;
}
```

---

## 作者：不知名用户 (赞：0)

题意：给定 $n\times n,n\in odd$ 的矩形，记 $m=\frac{n+1}{2}$，每次可以选一个 $m\times m$ 的矩形乘 $-1$，求经过若干次操作之后矩形和的最大值。

记 $b_{i,j}$ 表示 $(i,j)$ 最后有没有乘（奇数次）$-1$。显然 $b_{i,x}\oplus b_{i,x+m}=b_{i,m}$，因为每次操作 $b_{i,m}$ 显然会操作其它两个恰好一个，由 $m=\frac{n+1}{2}$ 易证， 把行列下标互换也一样。所以，如果确定了左上角 $m\times m$ 的矩形，整个矩形就确定了。时间复杂度 $\Theta(2^{\frac{n^2}{4}}n^2)$，但这远远不行。

然后，我们发现一些格子是互不相干的。如果花 $\Theta(2^{\frac{n}{2}})$ 的复杂度确定了第 $m$ 列，然后**分别**考虑（复杂度线性不是指数）$b$ 的第 $m$ 行，因为 $b$ 的第 $m$ 行是互不相干的（我太菜了不会证明，不过大概能感受到的），考虑完第 $x$ 行 $m$ 列，在分别考虑第 $x$ 列的其它数。

总结：利用了 $m=\frac{n+1}{2}$ 和互不相干，真的妙。

代码参考了 132533 的，可以感受一下每行每列独立，复杂度 $\Theta(2^{\frac{n}{2}}n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 40;

int a[N][N], b[N][N];
#define c(i,j) (b[i][j]?-a[i][j]:a[i][j])
int n, m;

int calc3(int x, int y, int z)
{
	b[x][y] = z, b[x][y+m] = b[x][y] ^ b[x][m];
	b[x+m][y] = b[x][y] ^ b[m][y], b[x+m][y+m] = b[x+m][y] ^ b[x+m][m];
	return c(x,y) + c(x,y+m) + c(x+m,y) + c(x+m,y+m);
}

int calc2(int x, int y)
{
	b[m][x] = y, b[m][x+m] = b[m][x] ^ b[m][m];
	int i, ans = c(m,x) + c(m,x+m);
	for(i=1;i<m;i++) ans += max(calc3(i,x,0),calc3(i,x,1));
	return ans;
}

int calc1()
{
	int i, ans = 0;
	for(i=m+1;i<=n;i++) b[i][m] = b[m][m] ^ b[i-m][m];
	for(i=1;i<=n;i++) ans += c(i,m);
	for(i=1;i<m;i++) ans += max(calc2(i,0),calc2(i,1));
	return ans;
}

int main()
{
	int i, j, ans = -1e9;
	cin>>n, m = (n + 1) / 2;
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) cin>>a[i][j];
	for(i=0;i<(1<<m);i++)
	{
		for(j=0;j<m;j++) if((i>>j)&1) b[j+1][m] = 1;else b[j+1][m] = 0;
		ans = max(ans,calc1());
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

观察到 $n\le 33$，往 $O(2^{\frac n2})$ 考虑。

考虑记录若干次操作后的 $a_{i,j}$ 的符号 $b_{i,j}$。

不难发现：$b_{i,j}=b_{i-x,j-x}\times b_{x,x} \times b_{x,j-x} \times b_{i-x,x}(i\ge x,j\ge x)$。

其余情况同理。

枚举 $S=\{(i,x-1) | i \in[0,x)\}$ 格子的符号。

然后 $\forall i \neq j, i,j \in[0,x)$，$i,j$ 两列**不会相互影响**。

所以只需**逐个**枚举 $(x-1,i)$ 然后统计答案即可。

复杂度 $O(2^{\frac n2}n^2)$。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/321/submission/246753065)

---

## 作者：litble (赞：0)

这是一道优秀的枚举题。首先设$m=\frac{n+2}{2}$，用$X$表示每一个格子是否被翻转的状态，那么用题意操作完后的矩阵模样，等价于满足$X_{i,j} \oplus X_{m,j} \oplus X_{i+m,j}=0$　（$\oplus$表示异或）且$X_{i,j} \oplus X_{i,m} \oplus X_{i,j+m}$的一个矩阵。

我们需要枚举尽可能少的信息来确定这个矩阵。

首先我们发现，第$m$行和第$m$列的信息比较重要。考虑先枚举第$m$列前$m$个$X$，然后我们可以确定第$m$列后$m$个$X$。

接下来，我们发现前$m-1$列之间互不干扰，所以我们可以分开考虑这些列。
```cpp
int cal1() {
	int re=0;
	for(RI i=1;i<=n;++i) re+=get(i,m);//get(i,j):获得当前X状态下第i行j列的值
	for(RI i=1;i<m;++i) re+=max(cal2(i,0),cal2(i,1));//分开考虑列
	return re;
}
```

假设我们考虑的是第$i$列，我们先考虑$X_{m,i}$的状态，那么我们也知道了$X_{m,i+m}$的状态。

接着发现，$X_{1,i},X_{2,i}...X_{m-1,i}$之间也是互不影响的，也可以再这么来一次。

```cpp
int cal2(int y,int bj) {
	t[m][y]=bj,t[m][y+m]=t[m][y]^t[m][m];
	int re=get(m,y)+get(m,y+m);
	for(RI i=1;i<m;++i) re+=max(cal3(i,y,0),cal3(i,y,1));
	return re;
}
```

最后我们就得到了一个复杂度为$O(n^22^{m})$的解：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
const int inf=0x3f3f3f3f;
int n,m,ans;
int a[34][34],t[34][34],bin[20];
#define get(x,y) (t[x][y]?-a[x][y]:a[x][y])
int cal3(int x,int y,int bj) {
	t[x][y]=bj,t[x+m][y]=t[x][y]^t[m][y];
	t[x][y+m]=t[x][y]^t[x][m],t[x+m][y+m]=t[x][y+m]^t[m][y+m];
	int re=get(x,y)+get(x+m,y)+get(x,y+m)+get(x+m,y+m);
	return re;
}
int cal2(int y,int bj) {
	t[m][y]=bj,t[m][y+m]=t[m][y]^t[m][m];
	int re=get(m,y)+get(m,y+m);
	for(RI i=1;i<m;++i) re+=max(cal3(i,y,0),cal3(i,y,1));
	return re;
}
int cal1() {
	int re=0;
	for(RI i=1;i<=n;++i) re+=get(i,m);
	for(RI i=1;i<m;++i) re+=max(cal2(i,0),cal2(i,1));
	return re;
}
int main()
{
	scanf("%d",&n);
	for(RI i=1;i<=n;++i)
		for(RI j=1;j<=n;++j) scanf("%d",&a[i][j]);
	m=(n+1)>>1,ans=-inf;
	bin[1]=1;for(RI i=2;i<=m+1;++i) bin[i]=bin[i-1]<<1;
	for(RI zt=0;zt<bin[m+1];++zt) {
		for(RI i=1;i<=m;++i) t[i][m]=((zt&bin[i])==0?0:1);
		for(RI i=m+1;i<=n;++i) t[i][m]=t[i-m][m]^t[m][m];
		ans=max(ans,cal1());
	}
	printf("%d\n",ans);
	return 0;
}
```

---

