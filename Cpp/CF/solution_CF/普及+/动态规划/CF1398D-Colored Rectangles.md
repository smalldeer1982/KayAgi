# Colored Rectangles

## 题目描述

You are given three multisets of pairs of colored sticks:

- $ R $ pairs of red sticks, the first pair has length $ r_1 $ , the second pair has length $ r_2 $ , $ \dots $ , the $ R $ -th pair has length $ r_R $ ;
- $ G $ pairs of green sticks, the first pair has length $ g_1 $ , the second pair has length $ g_2 $ , $ \dots $ , the $ G $ -th pair has length $ g_G $ ;
- $ B $ pairs of blue sticks, the first pair has length $ b_1 $ , the second pair has length $ b_2 $ , $ \dots $ , the $ B $ -th pair has length $ b_B $ ;

You are constructing rectangles from these pairs of sticks with the following process:

1. take a pair of sticks of one color;
2. take a pair of sticks of another color different from the first one;
3. add the area of the resulting rectangle to the total area.

Thus, you get such rectangles that their opposite sides are the same color and their adjacent sides are not the same color.

Each pair of sticks can be used at most once, some pairs can be left unused. You are not allowed to split a pair into independent sticks.

What is the maximum area you can achieve?

## 说明/提示

In the first example you can construct one of these rectangles: red and green with sides $ 3 $ and $ 5 $ , red and blue with sides $ 3 $ and $ 4 $ and green and blue with sides $ 5 $ and $ 4 $ . The best area of them is $ 4 \times 5 = 20 $ .

In the second example the best rectangles are: red/blue $ 9       \times 8 $ , red/blue $ 5 \times 5 $ , green/blue $ 2 \times       1 $ . So the total area is $ 72 + 25 + 2 = 99 $ .

In the third example the best rectangles are: red/green $ 19       \times 8 $ and red/blue $ 20 \times 11 $ . The total area is $ 152 + 220 = 372 $ . Note that you can't construct more rectangles because you are not allowed to have both pairs taken to be the same color.

## 样例 #1

### 输入

```
1 1 1
3
5
4```

### 输出

```
20```

## 样例 #2

### 输入

```
2 1 3
9 5
1
2 8 5```

### 输出

```
99```

## 样例 #3

### 输入

```
10 1 1
11 7 20 15 19 14 2 4 13 14
8
11```

### 输出

```
372```

# 题解

## 作者：lndjy (赞：8)

看见数据范围，发现 $O(n^3)$ 是正好可以通过的，于是考虑 dp。

设 $f_{i,j,k}$ 表示 $R,G,B$ 分别用了前 $i,j,k$ 个时答案的最大值。

选任意两种不同的颜色，也就是有 $3$ 种情况：

- 颜色 $RG$，也就是 $f_{i-1,j-1,k}+a_i+b_j$。
- 颜色 $RB$，也就是 $f_{i-1,j,k-1}+a_i+c_k$。
- 颜色 $GB$，也就是 $f_{i,j-1,k-1}+b_j+c_k$。

得到转移方程：

$$f_{i,j,k}=\max\{f_{i-1,j-1,k}+a_i+b_j,f_{i-1,j,k-1}+a_i+c_k,f_{i,j-1,k-1}+b_j+c_k\}$$

$f_{R,G,B}$ 即为答案。

代码：

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int f[205][205][205];
int r,g,x;
int a[205],b[205],c[205];
long long ans;
int dfs(int i,int j,int k)
{
	if(f[i][j][k]) return f[i][j][k];
	if(i&&j) f[i][j][k]=max(f[i][j][k],dfs(i-1,j-1,k)+a[i]*b[j]);
	if(i&&k) f[i][j][k]=max(f[i][j][k],dfs(i-1,j,k-1)+a[i]*c[k]);
	if(j&&k) f[i][j][k]=max(f[i][j][k],dfs(i,j-1,k-1)+b[j]*c[k]);
	return f[i][j][k];
}
signed main()
{
	cin>>r>>g>>x;
	for(int i=1;i<=r;i++)  cin>>a[i];
	for(int i=1;i<=g;i++)  cin>>b[i];
	for(int i=1;i<=x;i++)  cin>>c[i];
	sort(a+1,a+r+1);
	sort(b+1,b+g+1);
	sort(c+1,c+x+1);
	cout<<dfs(r,g,x);
	return 0;
}

```


---

## 作者：Ryo_Yamada (赞：7)

看到这题第一反应贪心。交了一发（ll开了）， WA6。冷静下来，造了组 hack 数据：
```
4 2 2
19 19 19 19
20 20
20 20
```
按贪心的思路，答案会是 $20 \times 20 + 20 \times 20$，因为每次都取最大的两个不同颜色的木棍相乘。而正确的应该是 $19 \times 20 \times 4$。

于是这题就是 dp 了，$200^3$ 的数组能开下。但是当时写贪心花了太长时间，再去推 dp 会很费时间，怎么办？没错，我写了码量小好写的记搜。

$dp_{i,j,k}$ 表示 红、绿、蓝三种颜色分别还剩 $i, j, k$ 个时的最大面积。$dfs$ 三种选择情况，当然别忘了判边界（是否都还有剩余）。

$\text{Code}$：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int N = 205;
int R, G, B;
int r[N], g[N], b[N];
long long dp[N][N][N];//这题一定开ll，不然会 WA6

long long dfs(int x, int y, int z) {
	if(dp[x][y][z]) return dp[x][y][z];//如果已搜过，直接返回。
	if(x && y) dp[x][y][z] = max(dp[x][y][z], dfs(x - 1, y - 1, z) + r[x] * g[y]);
	if(x && z) dp[x][y][z] = max(dp[x][y][z], dfs(x - 1, y, z - 1) + r[x] * b[z]);
	if(z && y) dp[x][y][z] = max(dp[x][y][z], dfs(x, y - 1, z - 1) + b[z] * g[y]);//三种情况取 max
	return dp[x][y][z];
}

int main() {
	cin >> R >> G >> B;
	for(int i = 1; i <= R; i++) scanf("%d", r + i);
	for(int i = 1; i <= G; i++) scanf("%d", g + i);
	for(int i = 1; i <= B; i++) scanf("%d", b + i);
	sort(r + 1, r + R + 1);
	sort(g + 1, g + G + 1);
	sort(b + 1, b + B + 1);//别忘了排序
	cout << dfs(R, G, B);
	return 0;
}
/*4 2 2
  19 19 19 19
  20 20
  20 20
*/

```


---

## 作者：b6e0_ (赞：7)

[CF题面传送门](https://codeforces.com/contest/1398/problem/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1398D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1398D)

有一个经典的结论，就是对于两个序列 $a$ 和 $b$，如果要对里面的元素两两配对乘起来求和，那么和最大就是大对大、小对小，和最小就是大对小、小对大。因为要让和最大，$a$ 中的最大元素要乘上最大的数，让和最小就相反。

看到这个数据范围，明显是差不多 $O(RGB)$ 的复杂度，考虑三维 dp。

$dp_{i,j,k}$ 表示 $r$ 中选 $i$ 个，$g$ 中选 $j$ 个，$b$ 中选 $k$ 个配对所能得到的最大值。假如无法配对得到 $dp_{i,j,k}$ 就为 $0$。按照状态的定义，要将 $r$、$g$ 和 $b$ 排递减序，此时状态等价于 $r$ 中选前 $i$ 个，$g$ 中选前 $j$ 个，$b$ 中选前 $k$ 个配对所能得到的最大值。边界为 $dp_{1,1,0}=r_1g_1,dp_{1,0,1}=r_1b_1,dp_{0,1,1}=g_1b_1$。转移方程为：

$$dp_{i,j,k}=\max(dp_{i-1,j-1,k}+r_ig_j,dp_{i-1,j,k-1}+r_ib_k,dp_{i,j-1,k-1}+g_jb_k)$$

下面考虑如何判断 $dp_{i,j,k}$ 是能得到的。首先，$i+j+k$ 肯定要是偶数。还有一种情况：$i=4,j=1,k=1$。这样虽然加起来是偶数，但是无法得到，因为至少要有两个 $r$ 是乘起来的。所以还要满足$i+j\ge k$、$i+k\ge j$和$j+k\ge i$。

还要注意一点：最后的 $dp_{R,G,B}$ 可能无法得到，所以比较方便的一个方法是对所有 $dp$ 值比 $\max$。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[205],b[205],c[205],dp[205][205][205],ans;
signed main()
{
	int r,g,B,i,j,k;
	cin>>r>>g>>B;
	for(i=1;i<=r;i++)
		cin>>a[i];
	for(i=1;i<=g;i++)
		cin>>b[i];
	for(i=1;i<=B;i++)
		cin>>c[i];
	sort(a+1,a+r+1,greater<long long>());
	sort(b+1,b+g+1,greater<long long>());
	sort(c+1,c+B+1,greater<long long>());
	dp[1][1][0]=a[1]*b[1];
	dp[1][0][1]=a[1]*c[1];
	dp[0][1][1]=b[1]*c[1];
	for(i=0;i<=r;i++)
		for(j=0;j<=g;j++)
			for(k=0;k<=B;k++)
				if(!((i+j+k)&1)&&i+j>=k&&i+k>=j&&j+k>=i)
				{
					if(i&&j&&dp[i-1][j-1][k])
						dp[i][j][k]=dp[i-1][j-1][k]+a[i]*b[j];
					if(i&&k&&dp[i-1][j][k-1])
						dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k-1]+a[i]*c[k]);
					if(j&&k&&dp[i][j-1][k-1])
						dp[i][j][k]=max(dp[i][j][k],dp[i][j-1][k-1]+b[j]*c[k]);
					ans=max(ans,dp[i][j][k]);
				}
	cout<<ans;
	return 0;
}
```
时间复杂度为 $O(RGB)$。

---

## 作者：123zbk (赞：1)

第一眼以为是贪心，每次将最大的两个不是相同颜色的数相乘。但是它会漏掉剩余的很多数。比如这组数据：

$r_i:80\ 80\ 80\ 80 ,g_i:100\ 100,b_i:100\ 100$

如果按贪心的思想，就应该是两个 $100$ 相互配对，但是只能选两次，正确的选法是选择 $4$ 个 $80$ 和 $100$ 组合。

然后考虑 dp，$R,G,B<=200$，直接三层循环暴力即可。

$dp[i][j][k]=\max\{dp[i][j][k],dp[i-1][j-1][k]+r[i]*g[j],dp[i-1][j][k-1]+r[i]*b[k],dp[i][j-1][k-1]+g[j]*b[k]\}$

循环时从 $0$ 开始，否则会丢掉如 $dp[0][1][1]$ 这样的情况。

别忘了排序。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=205;
int R,G,B,r[maxn],g[maxn],b[maxn],dp[maxn][maxn][maxn],ans;
signed main()
{
    scanf("%lld%lld%lld",&R,&G,&B);
    for(int i=1;i<=R;i++)
    {
        scanf("%lld",&r[i]);
    }
    for(int i=1;i<=G;i++)
    {
        scanf("%lld",&g[i]);
    }
    for(int i=1;i<=B;i++)
    {
        scanf("%lld",&b[i]);
    }
    sort(r+1,r+R+1,greater<int>());
    sort(g+1,g+G+1,greater<int>());
    sort(b+1,b+B+1,greater<int>());
    for(int i=0;i<=R;i++)
    {
        for(int j=0;j<=G;j++)
        {
            for(int k=0;k<=B;k++)
            {
                if(i&&j)
                {
                    dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k]+r[i]*g[j]);
                }
                if(i&&k)
                {
                    dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k-1]+r[i]*b[k]);
                }
                if(j&&k)
                {
                    dp[i][j][k]=max(dp[i][j][k],dp[i][j-1][k-1]+g[j]*b[k]);
                }
                ans=max(ans,dp[i][j][k]);
            }
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：AC_love (赞：1)

很容易就能想到：长的边要尽可能匹配长的边，这样才能让乘积最大化。因此我们首先对三种颜色的棍子的长度从大到小排好序，然后发现 $n \le 200$，可以直接 $O(n ^ 3)$ DP。

考虑设 $f(i, j, k)$ 表示红色取了前 $i$ 个，绿色取了前 $j$ 个，蓝色取了前 $k$ 个时的面积最大值。

转移其实很显然。

每次一定只会取两种颜色的木棍各一对，因此 $f(i, j, k)$ 可以从 $f(i - 1, j - 1, k), f(i - 1, j, k - 1)$ 或 $f(i, j - 1, k - 1)$ 转移而来。

取最大值即可。

核心代码：

```c++
int dfs(int i, int j, int k)
{
	if(f[i][j][k] != -1)
		return f[i][j][k];
	f[i][j][k] = 0;
	if(i && j)
		tomax(f[i][j][k], dfs(i - 1, j - 1, k) + a[i] * b[j]);
	if(i && k)
		tomax(f[i][j][k], dfs(i - 1, j, k - 1) + a[i] * c[k]);
	if(j && k)
		tomax(f[i][j][k], dfs(i, j - 1, k - 1) + b[j] * c[k]);
	return f[i][j][k];
}
```

---

## 作者：KSToki (赞：1)

我开始的基本思路是每次取两个最大的乘起来，即用贪心做。但当目前三个数中最小值不止一个时就变得难以处理。看了看数据范围，显然可以用 $O(RGB)$ 的时间复杂度过，于是我们开始放心大胆的~~瞎搞~~。

先从大到小排序是少不了的。设 $f[i][j][k]$ 为在 $r$ 中取了前 $i$ 个，在 $g$ 中取了前 $j$ 个和在 $b$ 中取了前 $k$ 个时的最大值。显然有两种决策：

- 选一个出来，不选（针对 $R$、$G$、$B$ 的和是奇数），为 $max(f[i-1][j][k],max(f[i][j-1][k],f[i][j][k-1]))$。
- 选两个出来，加入答案里，为 $max(f[i-1][j-1][k]+r[i]\times g[j],max(f[i-1][j][k-1]+r[i]\times b[k],f[i][j-1][k-1]+g[j]\times b[k]))$

当转移过程中 $i,j,k$ 出现 $0$ 时，用上述转移会发生越界，因此我把这种情况单独列出来讨论了。显然，只有 $1$ 个 $0$ 时才有意义，需要转移。

代码就很简单了：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int R,G,B,r[201],g[201],b[201],f[201][201][201];
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	cin>>R>>G>>B;
	for(register int i=1;i<=R;++i)
		cin>>r[i];
	for(register int i=1;i<=G;++i)
		cin>>g[i];
	for(register int i=1;i<=B;++i)
		cin>>b[i];
	sort(r+1,r+R+1,cmp);
	sort(g+1,g+G+1,cmp);
	sort(b+1,b+B+1,cmp);
	for(register int i=1;i<=R;++i)
	    for(register int j=1;j<=G;++j)
	        f[i][j][0]=f[i-1][j-1][0]+r[i]*g[j];
	for(register int i=1;i<=R;++i)
	    for(register int j=1;j<=B;++j)
	        f[i][0][j]=f[i-1][0][j-1]+r[i]*b[j];
	for(register int i=1;i<=G;++i)
	    for(register int j=1;j<=B;++j)
	        f[0][i][j]=f[0][i-1][j-1]+g[i]*b[j];
	for(register int i=1;i<=R;++i)
	    for(register int j=1;j<=G;++j)
	        for(register int k=1;k<=B;++k)
	            f[i][j][k]=max(max(f[i-1][j-1][k]+r[i]*g[j],max(f[i-1][j][k],max(f[i][j-1][k],f[i][j][k-1]))),max(f[i-1][j][k-1]+r[i]*b[k],f[i][j-1][k-1]+g[j]*b[k]));
	cout<<f[R][G][B]<<endl;
	return 0;
}
```
代码转移时顺序可能有点混乱，主要是比赛时我开始没有考虑到第一种情况。但理解了打起来很简单，没什么问题。

---

## 作者：H6_6Q (赞：1)

### 题目翻译：

给出 $R$ 对红色木棍 $r_1,r_2...r_R$，$G$ 对绿色木棍 $g_1,g_2...g_G$，$B$ 对蓝色木棍 $b_1,b_2...b_B$ 的长度（ $R,G,B \le 200$ ），每次可以选出两对颜色不同的木棍组成一个矩形，每对木棍只能使用一次，木棍可以有剩余。请最大化所有组成的矩形的面积。

### 思路：

很容易想到一个贪心的思路即在同一种颜色的木棍中，如果一对长度为 $k$ 的木棍选过，那么所有长度大于 $k$ 的木棍都已经选过。

那么可以先将每种颜色的木棍排降序，这样最优解所选的木棍一定是这个颜色的一个前缀。

这样的话再进行dp就很简单了，设 $dp_{i,j,k}$ 为已经选了 $1\sim i$ 中的所有红色木棍，$1\sim j$ 中的所有绿色木棍，$1\sim k$ 中的所有蓝色木棍。

转移即：

$$dp_{i+1,j+1,k}=\max(dp_{i+1,j+1,k},dp_{i,j,k}+r_{i+1}\times g_{j+1})$$
$$dp_{i,j+1,k+1}=\max(dp_{i,j+1,k+1},dp_{i,j,k}+g_{j+1}\times b_{k+1})$$
$$dp_{i+1,j,k+1}=\max(dp_{i+1,j,k+1},dp_{i,j,k}+r_{i+1}\times b_{k+1})$$

时间复杂度：$\text{O}(R\times G\times B)$

### Code：

```cpp
#include<bits/stdc++.h>

using namespace std;

int read()
{
	int ans=0,f=1;
	char b=getchar();
	while(b>'9'||b<'0'){if(b=='-')f=-1;b=getchar();}
	while(b>='0'&&b<='9'){ans=ans*10+b-'0';b=getchar();}
	return ans*f;
}

const int N=205;
int R,G,B,r[N],g[N],b[N],dp[N][N][N],ans;

bool cmp(int a,int b)
{
	return a>b;
}

signed main()
{
	R=read();G=read();B=read();
	for(int i=1;i<=R;++i)
		r[i]=read();
	for(int i=1;i<=G;++i)
		g[i]=read();
	for(int i=1;i<=B;++i)
		b[i]=read();
	sort(r+1,r+1+R,cmp);
	sort(g+1,g+1+G,cmp);
	sort(b+1,b+1+B,cmp);
	for(int i=0;i<=R;++i)
		for(int j=0;j<=G;++j)
			for(int k=0;k<=B;++k)
			{
				dp[i+1][j+1][k]=max(dp[i+1][j+1][k],dp[i][j][k]+r[i+1]*g[j+1]);
				dp[i][j+1][k+1]=max(dp[i][j+1][k+1],dp[i][j][k]+g[j+1]*b[k+1]);
				dp[i+1][j][k+1]=max(dp[i+1][j][k+1],dp[i][j][k]+r[i+1]*b[k+1]);
				ans=max(ans,dp[i][j][k]);
			}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：pomelo_nene (赞：1)

首先将每组的木棍排个序，定义 $dp_{i,j,k}$ 为第一组考虑前 $i$ 个，第二组考虑前 $j$ 个，第三组考虑前 $k$ 个。

首先考虑边界和答案。只要 $i,j,k$ 中有两个及以上个 $0$，这一位就是 $0$。答案就是 dp 数组里面最大的那一个。

如果有一位是 $0$，那么我们只能从剩下的两种里面选一个。

否则，我们考虑用三种颜色组成一个矩形，用红蓝，红绿，绿蓝判断一下就好了。转移比较显然，可以看代码。

注意要理解好题意。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL dp[205][205][205],a[205],b[205],c[205],suma[205],sumb[205],sumc[205];
int main(){
	LL r,B,g;
	scanf("%lld %lld %lld",&r,&B,&g);
	for(LL i=1;i<=r;++i)	scanf("%lld",&a[i]);
	for(LL i=1;i<=B;++i)	scanf("%lld",&b[i]);
	for(LL i=1;i<=g;++i)	scanf("%lld",&c[i]);
	sort(a+1,a+1+r,greater<LL>());
	sort(b+1,b+1+B,greater<LL>());
	sort(c+1,c+1+g,greater<LL>());
	LL ans=0;
	for(LL i=0;i<=r;++i)
	{
		for(LL j=0;j<=B;++j)
		{
			for(LL k=0;k<=g;++k)
			{
				if(i && j && k)	dp[i][j][k]=max(dp[i-1][j-1][k]+a[i]*b[j],max(dp[i-1][j][k-1]+a[i]*c[k],dp[i][j-1][k-1]+b[j]*c[k]));
				else if(i && j)	dp[i][j][k]=dp[i-1][j-1][k]+a[i]*b[j];
				else if(i && k)	dp[i][j][k]=dp[i-1][j][k-1]+a[i]*c[k];
				else if(j && k)	dp[i][j][k]=dp[i][j-1][k-1]+b[j]*c[k];
				ans=max(ans,dp[i][j][k]);
//				printf("dp[%lld][%lld][%lld]=%lld\n",i,j,k,dp[i][j][k]);
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：SGColin (赞：1)

根据排序不等式，肯定是大的相乘贡献更大。

但是涉及到三个颜色两两组合，直接让大的互相组合，有可能会出现某种颜色剩下很多没有用的情况。

但是贡献的原则不变，同种颜色先按照大小排序，然后DP。

`f[i][j][k]` 表示用了前 `i` 对红色，前 `j` 对绿色，前 `k` 对蓝色的最有答案，转移就讨论最后一个矩形怎么构成的就行了。

注意从0开始循环，否则会漏掉用 `f[0][0][0]` 更新形如 `f[1][1][0]` 的情况。

```C++
for (int i = 1; i <= r[0]; ++i) r[i] = rd();
sort(r + 1, r + 1 + r[0], cmp);
for (int i = 1; i <= g[0]; ++i) g[i] = rd();
sort(g + 1, g + 1 + g[0], cmp);
for (int i = 1; i <= b[0]; ++i) b[i] = rd();
sort(b + 1, b + 1 + b[0], cmp);
for (int i = 0; i <= r[0]; ++i)
  for (int j = 0; j <= g[0]; ++j)
    for (int k = 0; k <= b[0]; ++k) {
      if (i > 0 && j > 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + 1ll * r[i] * g[j]);
      if (i > 0 && k > 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + 1ll * r[i] * b[k]);
      if (j > 0 && k > 0) f[i][j][k] = max(f[i][j][k], f[i][j - 1][k - 1] + 1ll * g[j] * b[k]);
      ans = max(ans, f[i][j][k]);
    }
```

---

## 作者：kimi0705 (赞：0)

# Colored Rectangles
## 题意
你手里有 $3$ 套不同颜色的**木棍对**，包括：
- $R$ **对**红色的棍子，第 $i$ **对**的两根木棍长度均为 $r_i$；
- $G$ **对**绿色的棍子，第 $i$ **对**的两根木棍长度均为 $g_i$；
- $B$ **对**蓝色的棍子，第 $i$ **对**的两根木棍长度均为 $b_i$；

现在你要按照如下步骤构造长方形：
1. 选择任意一种颜色的任意一对木棍；
2. 选择任意一种**不同颜色**的任意一对木棍；
3. 将木棍摆成长方形，使得对边木棍的颜色相同，邻边木棍的颜色不同。计第 $i$ 个构造出的长方形的面积为 $S_i$。

注意：每一堆木棍只能使用 $1$ 次，你不必使用每一堆木棍。

若 $s$ 为你构造出的长方形的总数，请你计算：
$$\max \sum_{i=1}^s S_i=\max \sum_{i=1}^{s}(x_iy_i)$$
## 思路
考虑 $\texttt{dp}$。
### 设计状态
设 $dp_{i,j,k}$ 表示 $\texttt{R}$ 用了 $i$ 次，$\texttt{G}$ 用了 $j$ 次，$\texttt{B}$ 用了 $i=k$ 次。
### 考虑转移
- 可以取 $\texttt{RG}$, 即 $dp_{i,j,k}=dp_{i-1,j-1,k} + a_ib_j$
- 可以取 $\texttt{GB}$, 即 $dp_{i,j,k}=dp_{i,j-1,k-1} + b_jc_k$
- 可以取 $\texttt{BG}$, 即 $dp_{i,j,k}=dp_{i-1,j,k-1} + a_ic_k$

**综合起来**:$dp_{i,j,k}=\max\{dp_{i-1,j-1,k} + a_ib_j,dp_{i,j-1,k-1} + b_jc_k,dp_{i-1,j,k-1} + a_ic_k\}$
### 初值
好像不需要初值，为 $0$ 即可
### 终值
$dp_{R,G,B}$
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[205][205][205];
int r, g, b;
int x[205], y[205], z[205];
signed main() {
	cin >> r >> g >> b;
	for (int i = 1; i <= r; i++)  cin >> x[i];
	for (int i = 1; i <= g; i++)  cin >> y[i];
	for (int i = 1; i <= b; i++)  cin >> z[i];
	sort(x + 1, x + r + 1);  // 排序
	sort(y + 1, y + g + 1);
	sort(z + 1, z + b + 1);
	for (int i = 0; i <= r; i++) { // dp
		for (int j = 0; j <= g; j++) {
			for (int k = 0; k <= b; k++) {
				if (i && j) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k] + x[i] * y[j]);
				if (i && k) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1] + x[i] * z[k]);
				if (j && k) dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1] + y[j] * z[k]);
			}
		}
	}
	cout << dp[r][g][b];
	return 0;
}
```
### tips
- 要开 $\text{long long}$。
- $\texttt{dp}$ 的遍历要从 $0$ 开始。
---


好像 @[$\bf \color{#E74C3C}{lndjy}$](https://www.luogu.com.cn/user/196899)的思路的转移写错了，写成加号了......

---

## 作者：rouxQ (赞：0)

## 题意
给定三种颜色的棍子若干对，每次可以选取不同颜色的两对棍子组成一个矩形，最大化矩形的总面积。
## $\operatorname{Sol}$
首先我们发现这么一个结论：对于长的棍子，应当尽量与长的棍子配对组成矩形，可用排序不等式证明（$\text{同序和}\ge \text{乱序和}\ge \text{逆序和}$）。

所以我们先把三种棍子分别按长度从大到小排序，再考虑 dp。

设 $f(i,j,k)$ 表示选取 $i$ 对红棍子， $j$ 对绿棍子， $k$ 对蓝棍子的矩形总面积最大值，显然有转移方程：

$$f(i,j,k)=\max\{f(i-1,j-1,k)+R_i \times G_j,f(i-1,j,k-1)+R_i\times B_k,f(i,j-1,k-1)+G_j\times B_k\}$$

最后答案为 $\max f(i,j,k)$。
## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int R[201], G[201], B[201];
long long f[201][201][201];
bool cmp(int x, int y){return x > y;}
int main (){
    int r, g, b;
    cin >> r >> g >> b;
    for (int i = 1; i <= r; i++)cin >> R[i];
    for (int i = 1; i <= g; i++)cin >> G[i];
    for (int i = 1; i <= b; i++)cin >> B[i];
    sort(R + 1, R + 1 + r, cmp); sort(G + 1, G + 1 + g, cmp);
    sort(B + 1, B + 1 + b, cmp);
    f[1][1][0] = R[1] * G[1];
    f[1][0][1] = R[1] * B[1];
    f[0][1][1] = G[1] * B[1];
    for (int i = 0; i <= r; i++)
        for (int j = 0; j <= g; j++)
            for (int k = 0; k <= b; k++){
                if (i && j)f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + R[i] * G[j]);
                if (i && k)f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + R[i] * B[k]);
                if (j && k)f[i][j][k] = max(f[i][j][k], f[i][j - 1][k - 1] + G[j] * B[k]);
            }
    long long Max = 0;
    for (int i = 0; i <= r; i++)
        for (int j = 0; j <= g; j++)
            for (int k = 0; k <= b; k++)
                Max = max(Max, f[i][j][k]);
    cout << Max << endl;
    return 0;
}
```

---

