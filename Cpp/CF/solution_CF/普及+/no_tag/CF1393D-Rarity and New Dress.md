# Rarity and New Dress

## 题目描述

Carousel Boutique is busy again! Rarity has decided to visit the pony ball and she surely needs a new dress, because going out in the same dress several times is a sign of bad manners. First of all, she needs a dress pattern, which she is going to cut out from the rectangular piece of the multicolored fabric.

The piece of the multicolored fabric consists of $ n \times m $ separate square scraps. Since Rarity likes dresses in style, a dress pattern must only include scraps sharing the same color. A dress pattern must be the square, and since Rarity is fond of rhombuses, the sides of a pattern must form a $ 45^{\circ} $ angle with sides of a piece of fabric (that way it will be resembling the traditional picture of a rhombus).

Examples of proper dress patterns: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/1313c2f6e2e4ec2b50b9f433196c0f6817a45d78.png) Examples of improper dress patterns: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393D/53b6557287b6852020c7bea84c9bc4969c632d30.png) The first one consists of multi-colored scraps, the second one goes beyond the bounds of the piece of fabric, the third one is not a square with sides forming a $ 45^{\circ} $ angle with sides of the piece of fabric.

Rarity wonders how many ways to cut out a dress pattern that satisfies all the conditions that do exist. Please help her and satisfy her curiosity so she can continue working on her new masterpiece!

## 说明/提示

In the first example, all the dress patterns of size $ 1 $ and one of size $ 2 $ are satisfactory.

In the second example, only the dress patterns of size $ 1 $ are satisfactory.

## 样例 #1

### 输入

```
3 3
aaa
aaa
aaa```

### 输出

```
10```

## 样例 #2

### 输入

```
3 4
abab
baba
abab```

### 输出

```
12```

## 样例 #3

### 输入

```
5 5
zbacg
baaac
aaaaa
eaaad
weadd```

### 输出

```
31```

# 题解

## 作者：引领天下 (赞：6)

考虑每个点的答案与什么有关。

与它向上、向左、向下、向右最远能扩展到什么地方都有关。

显然这 $4$ 个方向中，能扩展的最近的一个方向限制了这个菱形的大小。

那么我们只需对每个点处理出以上 $4$ 个方向的值，即可完成对答案的计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans;
char c[2005][2005];
ll up[2005][2005],down[2005][2005],le[2005][2005],ri[2005][2005];
int main(){
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)scanf("%s",c[i]+1);
	for(register int i=1;i<=n;i++)
	for(register int j=1;j<=m;j++)up[i][j]=(c[i][j]==c[i-1][j])?up[i-1][j]+1:1;//处理向上的最远区域
	for(register int i=n;i;i--)
	for(register int j=1;j<=m;j++)down[i][j]=(c[i][j]==c[i+1][j])?down[i+1][j]+1:1;//处理向下的最远距离
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++)if(c[i][j]!=c[i][j-1])le[i][j]=1;
		else le[i][j]=min(min(up[i][j],down[i][j]),le[i][j-1]+1);//注意！由于要求这个菱形完全由同一种字符组成，所以向左扩展的同时还要考虑向上、向下的方向上是否满足当前的扩展
		for(register int j=m;j>=1;j--)if(c[i][j]!=c[i][j+1])ri[i][j]=1;
		else ri[i][j]=min(min(up[i][j],down[i][j]),ri[i][j+1]+1);//向右同理
		for(register int j=1;j<=m;j++)ans+=min(le[i][j],ri[i][j]);//由于我们刚才在左右扩展的过程中考虑了上下方向的扩展，所以直接取左右扩展中较小的作为当前的限制即可。
	}
	printf("%lld",ans);
}
```

---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1393D 【Rarity and New Dress】

### 题意

+ $n\times m$ 的矩形，剪倾斜 $45^o$ 的菱形，要求剪下的每个格子都同色；
+ $1\le n,m\le1000$。

### 做法

温馨提示：这里写的是非 dp 做法，数据稍强点就会被卡，想学正解的可以看楼下，本题解仅供参考。

----

可以想到按大小依次枚举菱形，每次求边长为 $x$ 的菱形有多少。

边长为 $1$ 的菱形显然是 $n\times m$ 个。

边长为 $2$ 的菱形呢？

考虑判断 $i,j$ 可不可以为菱形的中心，需要满足以下条件：
1. 周围四个格子颜色和中间相同。

边长为 $k$ 的菱形呢？

需要满足以下条件：
1. 周围四个格子颜色和中间相同；
2. 周围四个格子和中间的格子都可以为边长为 $k-1$ 的菱形的中心。

可以先把条件一处理出来，然后设 $dp_{k,i,j}$ （bool 类型）为格子 $i,j$ 能否为边长为 $k$ 的菱形的中心，方程为 $dp_{k,i,j}=\operatorname{and}dp_{k-1,x,y}$。

复杂度 $O(N^3)$。

显然过不了 $1000$ 的数据。

但是我们发现参与计算的都是 bool 类型，可以用 bitset 优化。

侥幸通过，复杂度 $O(\dfrac{N^3}{w})$。

### 代码

```cpp
#include <cstdio>
#include <bitset>

using namespace std;

const int N = 2e3 + 5;

char map[N][N];

bitset<N> b[N];
bitset<N> c[N];

int gx[] = {1, -1, 0, 0};
int gy[] = {0, 0, -1, 1};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", map[i] + 1);
	}
	int ans = n * m;
	for (int i = 2; i < n; ++i) {
		for (int j = 2; j < m; ++j) {
			for (int f = 0; f < 4; ++f) {
				int x = i + gx[f];
				int y = j + gy[f];
				if (map[i][j] != map[x][y]) {
					break;
				}
				if (f == 3) {
					b[i][j] = 1;
				}
			}
		}
		ans += b[i].count();
	}
	for (int k = 1; k <= n / 2; ++k) {
		for (int i = 2; i < n; ++i) {
			c[i] = b[i] & (b[i] << 1) & (b[i] >> 1) & b[i - 1] & b[i + 1]; // 递推式和之前说的有些不同，用了状压的思想。
			ans += c[i].count();
		}
		for (int i = 2; i < n; ++i) {
			b[i] = c[i];
		}
	}
	printf("%d", ans);
}
```

---

## 作者：stoorz (赞：3)

看到这题容易联想到经典的 dp 题 [最大正方形](https://www.luogu.com.cn/problem/P1387)。利用类似方法，可以在 $O(nm)$ 的复杂度内求出一个 $n\times m$ 的 01 矩阵内有多少个内部数字完全相同的正方形。

但是本题所求为类似菱形，无法直接用上述方法求出。但是我们发现，将原图按逆时针方向旋转 $45°$ 后，可以将菱形变成一个类似正方形的形状。

![](https://cdn.luogu.com.cn/upload/image_hosting/4698axyg.png)

那么对于这个“正方形”，它必然由奇数行构成，且正方形中任意奇数行比任意偶数行正好多一个格子。也就是这个“正方形”内奇数行的格子必然组成一个 $k\times k$ 的“正方形”，偶数行的格子必然组成一个 $(k-1)\times (k-1)$ 的“正方形”。

那么我们可以将这个图黑白染色，分别求出以 $(x,y)$ 为其颜色的右下角，能构成的最大正方形。字母的不同与 01 的不同实质上是一样的。然后回到菱形，枚举每一个格子 $(i,j)$，以这个格子为菱形最下方的格子的方案数即为 $\max(f[i][j],f[i-1][j]+1)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=2010;
int Q,n,m,a[N][N];
ll ans,f[N][N];
char ch;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			while (ch=getchar()) 
				if (ch>='a' && ch<='z') break;
			a[i][j]=ch-'a'+1;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (i==1) f[i][j]=1LL;
			else if (a[i][j]!=a[i-1][j-1] || a[i][j]!=a[i-1][j+1] || a[i][j]!=a[i-2][j]) f[i][j]=1LL;
			else f[i][j]=1LL+min(f[i-1][j-1],min(f[i-1][j+1],f[i-2][j]));
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (a[i][j]==a[i-1][j])
				ans+=min(f[i][j],f[i-1][j]+1);
			else ans++;
		}
	cout<<ans;
	return 0;
}

```

---

## 作者：K_Madoka (赞：2)

题目翻译：求图上任意大小，形如样例，只含有同一种字母的菱形的个数。

这道题比赛时没想出来，赛后看了看别人的代码，找到了一种比较简单的方法。

我们设数组$dp[0/1/2/3][i][j]$分别表示以$(i,j)$这个位置上下左右四个方向延伸的最长长度

对于$dp[0][i][j]$，需要考虑它的左边一位和下面一位

对于$dp[1][i][j]$，需要考虑它的下面一位和右边一位

对于$dp[2][i][j]$，需要考虑它的左边一位和上面一位

对于$dp[3][i][j]$，需要考虑它的右边一位和上面一位

最后统计答案就是$ans+=min(min(dp[0][i][j],dp[1][i][j]),min(dp[2][i][j],dp[3][i][j]))+1;$

具体细节看代码吧

```cpp
#define MAXN 2010
ll n,m,dp[4][MAXN][MAXN];
char s[MAXN][MAXN];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>(s[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]==s[i-1][j]&&s[i][j]==s[i][j-1])
                dp[0][i][j]=min(dp[0][i-1][j],dp[0][i][j-1])+1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){//注意要倒序
            if(s[i][j]==s[i-1][j]&&s[i][j]==s[i][j+1])
                dp[1][i][j]=min(dp[1][i-1][j],dp[1][i][j+1])+1;
        }
    }
    for(int i=n;i>=1;i--){//注意要倒序
        for(int j=1;j<=m;j++){
            if(s[i][j]==s[i][j-1]&&s[i][j]==s[i+1][j])
                dp[2][i][j]=min(dp[2][i][j-1],dp[2][i+1][j])+1;
        }
    }
    for(int i=n;i>=1;i--){//注意要倒序
        for(int j=m;j>=1;j--){
            if(s[i][j]==s[i][j+1]&&s[i][j]==s[i+1][j])
                dp[3][i][j]=min(dp[3][i][j+1],dp[3][i+1][j])+1;
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans+=min(min(dp[0][i][j],dp[1][i][j]),min(dp[2][i][j],dp[3][i][j]))+1;//统计答案
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：huayucaiji (赞：2)

首先我们可以转化一下问题，我们先令一个满足衣服图案的区域的**几何中心**为这个衣服的中心，我们再令以 $(x,y)$ 为中心的最大的衣服的半径为 $r_{x,y}$。那么我们的答案就为：

$$ans=\sum\limits_{i=1}^n\sum\limits_{j=1}^m (r_{i,j}+1)$$

对于**半径**我们结合图再来规定一下。对于下图（来自题目）：

![](https://espresso.codeforces.com/2756dfb01eeaf6b75dd6dd252612345a7bad4ffd.png)

比如对于第一张图（左一），我们的半径为 $1$；中间的那幅，半径为 $2$；最右边的半径为 $0$。

我们来具体分析如何求解。

我们如果把这个图形分成左右两半，我们会发现都是一个金字塔的形状，且从上往下宽度以 $2$ 为公差递增。这就是我们解决问题的切入点，分别取统计两边的金字塔大小，两边取 $\min$，即为半径大小。但是怎么求金字塔大小？以左边为例我们先来求以 $(x,y)$ 为中心的上下方向的线段的最大长度，记为 $len_{x,y}$。然后我们再令 $(x,y)$ 左边的最大金字塔的长度为 $left_{x,y}$。则我们有 $left_{x,y}=\min(\lfloor\frac{len_{x,y}}2\rfloor,left_{x,y-1}+1)$。右边同理。这个问题就解决了。

顺便提一句：记得用 ```getchar()```，否则会被卡常。~~博主亲测过得哟，亲。~~

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=2000+10;
int n,m,u[maxn][maxn],l[maxn][maxn],r[maxn][maxn],d[maxn][maxn],len[maxn][maxn];
char c[maxn][maxn];

signed main() {
	n=read();m=read();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			c[i][j]=getchar();
		}
		c[0][0]=getchar();
	}
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]==c[i-1][j]) {
				u[i][j]=u[i-1][j]+1;
			}
		}
	} 
	for(int i=n;i>0;i--) {
		for(int j=1;j<=m;j++) {
			if(c[i][j]==c[i+1][j]) {
				d[i][j]=d[i+1][j]+1;
			}
			len[i][j]=1+min(d[i][j],u[i][j])*2;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=m;j++) {
			if(c[i][j]==c[i][j-1]) {
				l[i][j]=min(len[i][j]/2,l[i][j-1]+1);
			}
		}
	}
	
	int ans=0;
	for(int i=1;i<=n;i++) {
		for(int j=m;j>0;j--) {
			if(c[i][j]==c[i][j+1]) {
				r[i][j]=min(len[i][j]/2,r[i][j+1]+1);
			}
			ans+=min(l[i][j],r[i][j])+1;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：StupidSeven (赞：1)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF1393D)

教练让我们打的一场模拟赛，写这题的时候脑瘫了，交了五发

## Analysis
考虑dp，设某一个点的状态 $ f[i][j] $表示第 $i$ 行第 $j$ 列的字符对答案的贡献，发现 $ f [i][j] $ 的值只跟 $ f [i-1][j-1],f [i-1][j],f[i-1][j+1],f[i-2][j]$ 这四个有关，当这几个位置对应的字母都等于$map[i][j]$时，我们可以更新答案，否则 $f[i][j]=1$

进一步思考可以推出更新答案时的转移方程:
$ f[i][j]=\min(f[i-1][j-1],f[i-1][j],f[i-1][j+1],f[i-2][j])+1 $

## Code
```cpp
#include<map>
#include<ctime>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define M 2010
#define int long long
inline int Readint(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;
}
char Map[M][M];
int n,m,f[M][M],ans;
signed main(void){
    n=Readint();m=Readint();
    for(int i=1;i<=n;i++){
        scanf("%s",Map[i]+1);
    }
    for(int i=1;i<=m;i++)
        f[1][i]=f[2][i]=1;
    for(int i=3;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(Map[i][j]==Map[i-1][j]&&Map[i][j]==Map[i-1][j-1]&&Map[i][j]==Map[i-1][j+1]&&Map[i][j]==Map[i-2][j]){
                int x=min(min(f[i-2][j],f[i-1][j-1]),min(f[i-1][j],f[i-1][j+1]));
                f[i][j]=x+1;
            }
            else f[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans+=f[i][j];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Mirasycle (赞：0)

观察到一个 $n$ 阶菱形必然由以它中心相邻的 $4$ 个格子为中心的 $4$ 个 $n-1$ 阶菱形拼成，这启发我们设 $dp_{i,j,k}$ 表示中心为 $(i,j)$ 的格子能否产生 $k$ 阶菱形，该状态为 $1$ 的条件是周围四个格子与之同色，且周围四个格子能产生 $4$ 个 $k-1$ 阶的菱形。这显然会超时。解决方案：
1. 可以 bitset 乱搞。
1. 一般遇到 bool 类型的 dp，如果某一维度具有单调性，也就是说越大越好。这里显然就是因为 $k$ 大的时候满足，那么小的时候必然也满足。这个时候我们可以将状态中的 $k$ 提出来，放到 dp 值里面，这样只需要最大化 $dp_{i,j}$ 即可。两种处理方式，第一种就是每个点能向 $4$ 个方向扩展的距离取 $\min$，这时也不需要 dp 了，循环判断即可。第二种还是 dp，我们发现如果设置中心点的话会有后效性，因为 $(i,j)$ 依赖于 $(i-1,j)~(i,j-1)~(i+1,j)~(i,j+1)$，刚刚因为有 $k$ 的阶段所以无后效性，现在去掉 $k$ 后就有了。于是我们直接选取菱形最右边的点就行。

---

