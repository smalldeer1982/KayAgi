# Rock Is Push

## 题目描述

你现在在一个$n×m$的迷宫的左上角（即点$(1,1)$），你的目标是到达迷宫的右下角（即点$(n,m)$）。一次移动你只能向右或者是向下移动一个单位。比如在点$(x,y)$你可以移动到点$(x+1,y)$或点$(x,y+1)$

迷宫中的一些点是岩石，当你移动到一个有岩石的点时岩石将被推到你移动方向的下一个点（你可以把岩石想象成推箱子游戏中的箱子），而如果那个点上也有一个岩石，它就会被按相同方向推的更远，以此类推（比如当前点右边有连着的十块岩石，你向右走一个点这些岩石就都会被向右推一个点）

这个迷宫被不可移动或是摧毁的墙包围着，石头是不允许被推到墙外或者摧毁墙的。（比如你右边有一个石头，而再往右是墙，你就不能往右移动了）

现在，请你计算出有多少种不同的可以到达终点的方案，由于方案数可能很大，结果请对$10^9+7$取模。两条路径中如果有任意的至少一个点不同，那就认为这两种方案是不同的。

## 说明/提示

第一个样例中，不需要移动就能到达终点，所以只有一种路径方案，输出$1$

第二个样例中终点被岩石挡住了，无法到达，所以没有方案可以到达终点，输出$0$

点击本网址可以看到第三个样例的例图
https://assets.codeforces.com/rounds/1225/index.html

## 样例 #1

### 输入

```
1 1
.
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
...
..R
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 4
...R
.RR.
.RR.
R...
```

### 输出

```
4
```

# 题解

## 作者：water_tomato (赞：8)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1225e-rock-is-push-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1225E)。

$n\times m$ 的场地上存在一些箱子，碰到了就会被推动，不可以使任何箱子被推出场地。求从 $(1,1)$ 走到 $(n,m)$ 的方案数。 

## 解析

发现该问题类似于过河卒，考虑 dp。由于向右和向下移动所涉及的箱子不同，且如果越过了箱子就一定不会再次推到（不能往回走），考虑如下设置状态：

记 $f_{i,j}$ 为从上方走到 $(i,j)$ 的所有方案数，$g_{i,j}$ 为从左方走到 $(i,j)$ 的所有方案数。在不考虑箱子的情况下，显然有：$f_{i,j}=f_{i-1,j}+g_{i-1,j}$ 和 $g_{i,j}=g_{i,j-1}+f_{i,j-1}$。

容斥思想下，我们再考虑减去不合法的方案数。我们发现除了第一排和第一列以外，其他行列都可以看作有上一行某处走下来再向右走或从左一列走过来再向下走。因此我们可以抽象出第 $0$ 行和第 $0$ 列，并赋予初值 $f_{1,1}=g_{1,1}=1$，为防止答案重复统计，同时也赋予初值 $f_{2,1}=g_{1,2}=-1$，容易判断这是正确的。

在此前提下，以除去不合法的向右走方案数为例。我们发现如果往下走到 $(i,j)$，由于 $(i,j)$ 及其左边的箱子都不会被推到，我们只需要判断一直往右走到哪里不合法就可以了。类似于前缀和地定义 $r_{i,j}$ 为 $(i,j)$ 及其右边（同一行）的箱子数总和。则除去从上方走到 $(i,j)$ 再往右走的不合法方案等价于将 $g_{i,m-r_{i,j+1}+1}$ 减去 $f_{i,j}$，另一个同理，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
const int mod=1e9+7;
int n,m;
char ma[N][N];
int f[N][N];//向下走
int g[N][N];//向右走
int r[N][N],d[N][N];//石头数
inline void add(int &a,int b){
	a=a+b>=mod?a+b-mod:a+b;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",ma[i]+1);
	if(n==1&&m==1){printf("1\n");return 0;}//特判
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(ma[i][j]=='R') r[i][j]=d[i][j]=1;
			r[i][j]+=r[i][j+1];d[i][j]+=d[i+1][j];
		}
	}//预处理 r,d 数组
	f[1][1]=g[1][1]=1;
	f[2][1]=g[1][2]=-1;//这么做是为了防止第一行和第一列有方案未删除或重复
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			add(f[i][j],f[i-1][j]);add(f[i][j],g[i-1][j]);
			add(g[i][m-r[i][j+1]+1],mod-f[i][j]);
			add(g[i][j],g[i][j-1]);add(g[i][j],f[i][j-1]);
			add(f[n-d[i+1][j]+1][j],mod-g[i][j]);
		}
	}
	printf("%d\n",(f[n][m]+g[n][m])%mod);
	return 0;
}
```



---

## 作者：Kelin (赞：8)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102844671)

一个$n\times m$的网格上有一些箱子

你只能向下或者向右走，如果碰到了箱子你可以沿着你行走的方向推动它

与之相连的在同一个方向上的所有箱子会一起向这个方向移动

求从$(1,1)$走到$(n,m)$的方案数在模$10^9+7$下的结果

$1\le n,m\le2000$

---

[样例$3$的动图]( https://assets.codeforces.com/rounds/1225/index.html)

---

## 题解
如果不能推动，那就差不多是过河卒了，这题也同样考虑$DP$

考虑到推动会有向下向右的区别

设$D_{i,j}/R_{i,j}(Down/Right)$表示从$(1,1)$到$(i,j)$，上一步是向下$/$右走的方案数

初始$D_{1,1}=R_{1,1}=1$

假设我们当前在$(i,j)$且当前位置没有箱子，考虑向右最多能走多少步

假设从$(i,j+1)$到$(i,m)$上有$k$个箱子，那么我们最多就能向右走$m-j-k$步

即$(i,j+1)$到$(i,m-k)$这些格子我都能走到

由于是向右走过来的那么$R_{i,j+1},...,R_{i,m-k}$的方案都要加上$R_{i,j}+D_{i,j}$

记$CntD_{i,j}$表示从$(i,j)$向下到$(n,j)$有多少箱子，$CntR_{i,j}$表示从$(i,j)$向右到$(i,m)$有多少箱子

那么就有

>$R_{i,j+1},...,R_{i,m-CntR_{i+1,j}}$都要加上$R_{i,j}+D_{i,j}$
>
>$D_{i+1,j},...,D_{n-CntD_{i+1,j},j}$都要加上$R_{i,j}+D_{i,j}$

区间加法可以使用差分数组进行优化，然后同一列$/$行求和即可

因为差分只会影响到后面枚举的状态，所以可以直接在原数组上进行修改，然后求前缀和

最后答案就是$D_{n,m}+R_{n,m}$

---

## 作者：pipiispig (赞：7)

这题是个dp QwQ, 我们可以强制每个点转向， 然后互相维护， 通过前缀和 和 双指针可以优化到n方， 可以通过此题
```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 7;
int dp[2005][2005][2];
int sum[2005][2005][2];
int r[2005][2005][2];
char a[2005][2005];
int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) 
			cin >> a[i][j];
	if(n == 1 && m == 1) {puts("1"); return 0;}
	for(int i = n; i >= 1; i --)
		for(int j = m; j >= 1; j --) {
			r[i][j][0] = r[i][j + 1][0] + (a[i][j] == 'R');
			r[i][j][1] = r[i + 1][j][1] + (a[i][j] == 'R');
		}
	dp[n][m][0] = dp[n][m][1] = sum[n][m][0] = sum[n][m][1] = 1;
	for(int i = n; i >= 1; i --)
		for(int j = m; j >= 1;j --) {
			if(i == n && j == m) continue;
			dp[i][j][0] = ( sum[i][j + 1][1] - sum[i][m - r[i][j + 1][0] + 1][1] + mod) % mod;
			dp[i][j][1] = ( sum[i + 1][j][0] - sum[n - r[i + 1][j][1] + 1][j][0] + mod) % mod;
			sum[i][j][0] = (sum[i + 1][j][0] + dp[i][j][0]) % mod;
			sum[i][j][1] = (sum[i][j + 1][1] + dp[i][j][1]) % mod;
		}
	cout << (dp[1][1][1] + dp[1][1][0] + 1ll * 2 * mod) % mod;
	return 0;
}

---

## 作者：BinDir0 (赞：6)



###[写题解不易，来我的博客玩玩qwq？](https://www.cnblogs.com/lost-in-tianyi/p/11762166.html)

在打CF的时候没想到www这个**dp**真的蛮巧妙的

这是一道dp题（废话

假设我们走到了$(i,j)$位置，因为我们只能下移/右移，那么我们所有上方与左方的石块（即$\{ (i,j)|i<n \space || \space j<m \}$的石块）不管被推到那里都与我无瓜（可以画几张图略推一推，还是比较明显），即该题无后效性，可用dp求解。

合在一起不是很好算，我们可以考虑将右移与下移分开对其进行dp。

因此我们可以用数组$rs,ds$来记录某位置右边的石头数量以及下方的石头数量，因为只有这些石头对$(i,j)$的状态转移有关

设二维状态数组$r,d$，表示在$(i,j)$位置时下一步向右（$r$）或向下（$d$）走，到达目标位置$(n,m)$的方案总数，由定义可得$r[n][m]=d[n][m]=1$。

### 重点来惹w：状态转移方程

之所以说这道题巧妙，一是因为它分成了$r,d$两块来dp，再一个就是状态转移方程了。

![捕获.PNG](https://i.loli.net/2019/10/29/NbfTv8lPxtoeJsU.png)

如上图所示，假设我们在黄色格子$(i,j)$，蓝色圆形为石头，虚线为石头移动轨迹。那么易得$ds[i][j]=1$（$rs$定义忘了的看上文）。因为我们下一步必须向下走，所以我们可以选择连续走$1$步、$2$步、...一直到$n-i-ds[i][j]$步为止，此时下面的石头刚好全部被一个接一个地推到了墙上排好。因此状态转移方程即

$$d[i][j]=\sum_{k=1}^{n-i-ds[i][j]}r[i][j+k]$$

$$r[i][j]=\sum_{k=1}^{m-i-rs[i][j]}d[i+k][j]$$

**（提前解一个疑：这里对$r$数组进行求和而非$d$数组求和的原因是我们连续往下走了$k$步后下一步应该往右，因此这里用$r$，反之亦然）**

想想还是蛮巧的（或者是窝太弱啦qaq

当然一个一个枚举$r[i][j+k],d[i+k][j]$肯定会超时，因此这里我们使用前缀和保存。

如果还有点没懂的dalao们可以看看蒟蒻代码里的注释www~

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n , m , r[2100][2100] , d[2100][2100] , ds[2100][2100] , rs[2100][2100];
long long sumr[2100][2100] , sumd[2100][2100];
const int mod = 1e9 + 7;
char s[2100];
//d:down r:right
int main()
{
	scanf("%d%d" , &n , &m);
	for(register int i = 1 ; i <= n ; i++ )
	{
		scanf("%s" , s + 1);
		for(register int j = 1 ; j <= m ; j++ )
		{
			if(s[j] == 'R') rs[i][j] = 1 , ds[i][j] = 1;
		}
	}
	if(n == 1 && m == 1)
	{
		cout << (rs[1][1] ^ 1);
		return 0;
	}
	for(register int i = n ; i >= 1 ; i-- )
	{
		for(register int j = m ; j >= 1 ; j-- )
		{
			ds[i][j] += ds[i][j + 1];
			rs[i][j] += rs[i + 1][j];
		}
	}
	r[n][m] = d[n][m] = sumd[n][m] = sumr[n][m] = 1;
	for(register int i = n ; i >= 1 ; i-- )
	{
		for(register int j = m ; j >= 1 ; j-- )
		{
			if(i == n && j == m) continue;
			r[i][j] = (sumd[i][j + 1] - sumd[i][m - ds[i][j + 1] + 1]) % mod;
			d[i][j] = (sumr[i + 1][j] - sumr[n - rs[i + 1][j] + 1][j]) % mod;
			//+1 : sum±Ø±¸  n - ds : ¼´i + (n - i - ds)»¯¼òºóµÄ½á¹û.
			//d[i][j] : ´Ë²½ÏòÏÂ×ßºóÓÐ¼¸ÖÖ¿ÉÄÜµ½(n , m); r[i][j] : ÏòÓÒ×ß
			//ds[i][j] : (i , j) ÏÂÃæÓÐ¶àÉÙ¿éÊ¯Í· , rs[i][j] : (i , j)ÓÒ±ß 
			//d[i][j] = sum(r[n - i - 1...ds[i][j + 1] + i][j]) , rÍ¬Àí
			//ÒâÎªÔÚÏÂÒ»¸öÏòÓÒ×ßÖ®Ç°£¬Ñ¡ÔñÏòÏÂ×ß1...ds[i][j + 1]´Î£¬È»ºóÔÙÏòÏÂ×ßµÄ·½°¸ÊýÖ®ºÍ¡£
			//ÇÉÃîwww
			sumr[i][j] = (sumr[i + 1][j] + r[i][j]) % mod; 
			sumd[i][j] = (sumd[i][j + 1] + d[i][j]) % mod; 
		}
	}
	/*for(register int i = 1 ; i <= n ; i++ )
	{
		for(register int j = 1 ; j <= m ; j++ )
		{
			cout << d[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	for(register int i = 1 ; i <= n ; i++ )
	{
		for(register int j = 1 ; j <= m ; j++ )
		{
			cout << r[i][j] << ' ';
		}
		cout << endl;
	}*/
//	cerr << r[1][1] << " " << d[1][1] << endl;
	cout << ((r[1][1] + d[1][1]) % mod + mod) % mod;
	return 0;
}
```

---

## 作者：thjkhdf12 (赞：4)

本题中求一个方案数，但是具有一个类似推箱子的东西：石头，如果沿当前方向有一串石头顶到了墙，那么就不能继续往下走了。所以预处理一下每个点右边和下边的石头数量，然后在dp的时候减去在无法推动的石头上走过的方案数就可以了

$f$数组为$3$维，$f[i][j][0/1]$表示在$(i,j)$点向右(第三维为$0$)和向下（第三维为$1$)的方案数，方案数的转移很简单，只需要将点$i,j$的方案数加上它右边和下边的点的方案数就可以了，然后处理一下石头的问题。对于如图迷宫

之前图片没搞好。。重新上传一下

![](https://cdn.luogu.com.cn/upload/image_hosting/7dkpyqr2.png)

我们来用第$4$行举例，在dp时倒着递推，使在$(4,4)$点和$(5,4)$点转向的方案数汇集到$f[4][4][1]$（一直向右走方案数显然是0了，一直在石头上……）然后在计算$f[3][4][0]$时减去$f[n-2+1][j][1]$也就是$f[4][4][1]$就可以了，其中$2$是预处理出的当前点右侧的石头数量

因为只能向下或者向右走，不用考虑同一个石头既能向右时碰到又能向下时碰到

代码如下

代码中的$f[n-sumr[i][j]+1][j][1]$即表示在石头上转向的方案数
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

#define mfor(i,a,b) for(register int i=(a);i<=(b);i++)
#define mrep(i,a,b) for(register int i=(a);i>=(b);i--)
typedef long long int LL;

const int maxn = 2010;
const int mod = 1e9 + 7;
char a[maxn][maxn];
LL sumd[maxn][maxn];	//sumd[i][j]表示点(i,j)下方的石头数量
LL sumr[maxn][maxn];	//sumr[i][j]表示点(i,j)右侧的石头数量
LL f[maxn][maxn][2];    //第三维0向右，1向下
int n, m;

int main()
{
    cin >> n >> m;
    mfor(i, 1, n)
    {
        //scanf_s("%s", a[i] + 1, maxn);
        scanf(" %s", a[i] + 1);
    }
    if (n == m && n == 1)
    {
        if (a[1][1] == '.')
        {
            cout << 1;
            return 0;
        }
    }
    mrep(i, n, 1)
    {
        mrep(j, m, 1)
        {
            sumd[i][j] = sumd[i][j + 1] + (a[i][j] == 'R' ? 1 : 0);
            sumr[i][j] = sumr[i + 1][j] + (a[i][j] == 'R' ? 1 : 0);
        }
    }
    mfor(i, 1, n - 1)
    {
        if (!sumr[i][m]) f[i][m][0] = 1;
    }
    mfor(i, 1, m - 1)
    {
        if (!sumd[n][i]) f[n][i][1] = 1;
    }
    mrep(i, n - 1, 1)
    {
        mrep(j, m - 1, 1)
        {
            (f[i][j][0] += f[i + 1][j][1]) %= mod;
            (f[i][j][1] += f[i][j + 1][0]) %= mod;
            if (a[i + 1][j] == 'R') (f[i][j][0] += f[i + 1][j][0] - f[n - sumr[i + 1][j] + 1][j][1] + mod) %= mod;	//撞到了石头，对方案数进行处理（减去在石头上转向的方案数）
            else (f[i][j][0] += f[i + 1][j][0]) %= mod;
            if (a[i][j + 1] == 'R') (f[i][j][1] += f[i][j + 1][1] - f[i][m - sumd[i][j + 1] + 1][0] + mod) %= mod;	//同上
            else (f[i][j][1] += f[i][j + 1][1]) %= mod;
        }
    }
    cout << (f[1][1][0] + f[1][1][1]) % mod;
}
```

---

## 作者：岂非 (赞：2)

[题目传送门~](https://www.luogu.com.cn/problem/CF1225E)

和朋友 duel 到的一个简单有趣数数题。

思路可能会讲的细一点，所以有点长。

首先，考虑没有石头或石头固定的情况。相信大家都能轻松设计出一个 $O(nm)$ 两维 DP 的算法。如果你不会，请不要在这道题上浪费时间。

加入推动石头的限制。面对更复杂的 DP 情况，一般都可以通过加几维做出来。这里我们先加两维，一维用来表示横行后面有多少石头，一维表示纵列后面有多少石头。用这两维判断能不能更新。

显然这个 $O(n^2m^2)$ 的东西很烂，做不了。

思考一下有什么好的性质，可以压一下状态。

可以想到，如果石头固定，就不存在后面两维，非常简单。后面两维都是我们在推石头的过程中产生的很多问题。

我们不要让前面推过的石头再对后面的贡献产生影响。

### 思路 1：

可能不是很好理解，但是是比较好想。我们考虑，不要推石头。一个点的方案数对后面产生的贡献，是一个区间。直接用前缀和维护一下。横行和纵列推石头贡献是分开的，拿两个数组交叉贡献一下。

### 思路 2：

思路一是我做题时想的思路过程，感觉可能不是很好理解。这里还有一种更具体的解释。

一条从起点到终点的路径，必定是一个形似这样的东西。

![](https://cdn.luogu.com.cn/upload/image_hosting/qlwzdz0j.png)

在没有石头或者石头固定的情况，我们是一格一格往前推的。差不多就是下图橙色箭头这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/mmc6ieli.png)

诶像这样的东西肯定会对后面的推石头产生影响啊，所以我们抛弃这个传统做法，换用绿色箭头的这个从拐点来 DP。

首先，由于是拐点，所以他后面的石头一定是没动过的。所以我们搞个后缀和预处理可以轻松确定他最远能走到哪。

所以这个拐点的方案数就可以贡献到后面一段区间，拿个差分做一下区间加就可以。

状态设计：`f[2010][2010][2]`，第一维是 $n$，第二维是 $m$，最后一维表示是向右拐点还是向下拐点。

两个思路是同一个做法的不同解释。第一个好想，第二个好理解。

代码

```cpp
#include <cstdio>
#define MOD 1000000007
#define ll long long
using namespace std;
ll n,m,suf[2010][2010],suf1[2010][2010],f1[2010][2010],f2[2010][2010];
char mp[2010][2010];
int main(){
	scanf("%lld%lld",&n,&m);
	if(n==1&&m==1){
		puts("1");return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%s",&mp[i][1]);
	}
	for(int i=1;i<=n;i++){//做一个后缀和预处理 
		for(int j=m;j>0;j--){
			if(mp[i][j]=='R'){
				suf[i][j]=1;
			} 
			suf[i][j]+=suf[i][j+1]; 
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=n;i>0;i--){
			if(mp[i][j]=='R'){
				suf1[i][j]=1;
			}
			suf1[i][j]+=suf1[i+1][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f1[i][j]+=f1[i][j-1];f2[i][j]+=f2[i-1][j];
			f1[i][j]%=MOD;f2[i][j]%=MOD;
			f1[i][j]+=MOD;f2[i][j]+=MOD;
			f1[i][j]%=MOD;f2[i][j]%=MOD;
			if(i==1&&j==1){//特判(1,1)两边都可以走 
				if(m!=1&&suf[i][j+1]<m-j){
					f1[i][j+1]+=1;
					f1[i][m-suf[i][j+1]+1]-=1;
				}
				if(n!=1&&suf1[i+1][j]<n-i){
					f2[i+1][j]+=1;
					f2[n-suf1[i+1][j]+1][j]-=1;
				}
			}
			else{
				if(m!=j&&suf[i][j+1]<m-j){//交叉转移 
					f1[i][j+1]+=f2[i][j];
					f1[i][j+1]%=MOD;
					f1[i][m-suf[i][j+1]+1]-=f2[i][j];
					f1[i][m-suf[i][j+1]+1]+=MOD;
					f1[i][m-suf[i][j+1]+1]%=MOD;
				}
				if(n!=i&&suf1[i+1][j]<n-i){
					f2[i+1][j]+=f1[i][j];
					f2[i+1][j]%=MOD;
					f2[n-suf1[i+1][j]+1][j]-=f1[i][j];
					f2[n-suf1[i+1][j]+1][j]+=MOD;
					f2[n-suf1[i+1][j]+1][j]%=MOD;
				}
			}
		}
	}
	printf("%lld",(f1[n][m]+f2[n][m])%MOD);
	return 0;
}
```

---

## 作者：incra (赞：1)

### Sol
考虑 DP，设 $f_{i,j,k}$ 表示从 $(1,1)$ 到 $(i,j)$，且最后一步的走法是右（$k=0$）或者下（$k=1$）的方案数。

考虑 $k=0$ 怎么转移，设 $p_{i,j,0}$ 表示最小的数，满足 $(i,p_{i,j,0})$ 往右推石头可以到达 $(i,j)$（假定此时保证 $p_{i,j,0}$ 一定是没有石头的）。那么 $f_{i,j,0}=\displaystyle\sum_{k=p}^{j-1} f_{i,k,1}$。

$k=1$ 同理。

这个式子不难想到前缀和优化，答案即为 $f_{n,m,0}+f_{n,m,1}$，注意 $n=m=1$ 的特判。
### Code
[Link](https://codeforces.com/contest/1225/submission/315535579)。

---

## 作者：Sol1 (赞：0)

感觉这题非常有趣，~~[尤其是这个样例解释。](https://assets.codeforces.com/rounds/1225/index.html)~~

这个问题形式上类似格线游走，虽然无法直接使用格线游走的模型解决，仍然可以考虑 DP。

考虑到我们只能向右或向下走，那么如果我们在某一步向右推了一块石头，那么它右边的石头一定都没动过。这启发我们在 DP 中记录最后一步向哪一个方向走。

如果我们仍然一步一步转移，那么会产生一个问题——我们无法得知走到 $(i,j)$ 时，从那个方向推了多少块石头过来。

但是我们又注意到我们在判断 $(i,j)$ 能否向右走的时候只关心我们从 $(i,j)$ 左侧推了多少块石头过来，而如果我们在游走过程中从 $(k,j-1)$ 走到 $(k,j)$ 再走到 $(i,j)$ 其中 $k<i$，那么 $(k,j)$ 左侧的所有石头都不可能被推到 $(i,j)$，而 $(k,j)$ 右侧的所有石头都一定被推到 $(i,j)$，因为如果这些石头被动过，那么一定在一个时刻游走到了 $x$ 坐标 $>k$ 的位置，再走回 $(k,j)$，与只能向下向右矛盾。

这启发我们枚举最后的连续一段向一个方向走，然后强制上一步往另外一个方向走。可以转移当且仅当最后走的一段上面的石头能够全部被推到目标点下方。

直接转移是 $O(nm(n+m))$，无法通过。但是容易使用前缀和优化到 $O(nm)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int n, m, dp[2][2005][2005], pres[2][2005][2005];
char mp[2005][2005];
vector <int> rrk[2005], crk[2005];

inline void Read() {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) cin >> mp[i][j];
	}
}

inline void Prefix() {
	for (int i = n;i >= 1;i--) {
		for (int j = m;j >= 1;j--) {
			if (mp[i][j] == 'R') {
				rrk[i].push_back(j);
				crk[j].push_back(i);
			}
		}
	}
}

inline void Solve() {
	if (n == 1 && m == 1) {
		cout << 1 << endl;
		return;
	}
	dp[0][1][1] = dp[1][1][1] = 1;
	pres[0][1][1] = pres[1][1][1] = 1;
	for (int i = 1;i <= n;i++) {
		for (int j = 1 + (i == 1);j <= m;j++) {
			int lst;
			if (m - j >= rrk[i].size()) lst = 1;
			else lst = rrk[i][m - j];
			dp[0][i][j] = (pres[1][i][j - 1] - pres[1][i][lst - 1] + mod) % mod;
			if (n - i >= crk[j].size()) lst = 1;
			else lst = crk[j][n - i];
			dp[1][i][j] = (pres[0][i - 1][j] - pres[0][lst - 1][j] + mod) % mod;
			pres[1][i][j] = (pres[1][i][j - 1] + dp[1][i][j]) % mod;
			pres[0][i][j] = (pres[0][i - 1][j] + dp[0][i][j]) % mod;
		}
	}
	cout << (dp[0][n][m] + dp[1][n][m]) % mod << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	Read();
	Prefix();
	Solve();
	return 0;
}
```

---

