# [POI 2006] MIS-Teddies

## 题目描述

Byteoian 是一家专业生产儿童玩具的公司。他们生产的玩具质量上乘，广受好评。

但最近，有人发现他们生产的泰迪熊存在致命缺陷。总共有四种泰迪熊型号：$A1$，$A2$，$B1$，$B2$，一旦将三个字母相同或数字相同的泰迪熊放在一块，就会对泰迪熊造成致命损坏。

如果一种摆放泰迪熊的方案中不存在连续三个字母相同或数字相同的泰迪熊，则称这种摆放方案是**安全的**。

现在你收集了一些泰迪熊，你想要知道有多少种安全的摆放泰迪熊的方案。由于安全的方案可能较多，请输出方案数对 $1\,000\,000$ 取模的结果。

## 说明/提示

$0 \leq n_{A1},n_{A2},n_{B1},n_{B2} \leq 38$。

## 样例 #1

### 输入

```
0 1 2 1```

### 输出

```
6```

# 题解

## 作者：Alex_Wei (赞：5)

> *[P3448 [POI2006]MIS-Teddies](https://www.luogu.com.cn/problem/P3448)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

还算有趣的 DP，感觉难度没有黑牌。

奇奇怪怪的限制 + 很小的数据范围，动态规划没跑了。注意到我们根本不需要知道序列长什么样，只要每种玩具放的个数以及最后两个玩具是什么就可以转移了。因此设六维 DP $f_{i,j,k,l,m,n}$ 表示放了 $i,j,k,l$ 个 $A1,A2,B1,B2$（分别标号为 $0,1,2,3$），最后两个玩具分别是 $m$ 和 $n$ 的方案数，转移直接枚举下一个放什么，检查一下是否符合题意即可。

空间复杂度可以通过滚动数组优化。时间复杂度四方，有 $64$ 倍常数。

```cpp
const int N = 39;
const int mod = 1e6;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int a, b, c, d, ans, f[2][N][N][N][4][4];
bool check(int x, int y, int z) {
	if(x == -1) return 1;
	int a = (x & 1) + (y & 1) + (z & 1), b = (x < 2) + (y < 2) + (z < 2);
	return a && a < 3 && b && b < 3;
}
int main(){
	cin >> a >> b >> c >> d, f[0][0][0][0][0][0] = 1;
	for(int I = 0, i = 0; I <= a; I++, i ^= 1) {
		mem(f[i ^ 1], 0, N);
		for(int j = 0; j <= b; j++)
			for(int k = 0; k <= c; k++)
				for(int l = 0, s = I + j + k; l <= d; l++, s++)
					for(int x = 0; x < 4; x++)
						for(int y = 0, v; y < 4; y++)
							if(v = f[i][j][k][l][x][y]) {
								int q2 = s <= 1 ? -1 : x, q1 = !s ? -1 : y;
								if(I < a && check(q2, q1, 0)) add(f[i ^ 1][j][k][l][y][0], v);
								if(j < b && check(q2, q1, 1)) add(f[i][j + 1][k][l][y][1], v);
								if(k < c && check(q2, q1, 2)) add(f[i][j][k + 1][l][y][2], v);
								if(l < d && check(q2, q1, 3)) add(f[i][j][k][l + 1][y][3], v);
							}
	}
	for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) add(ans, f[a & 1][b][c][d][i][j]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：FjswYuzu (赞：3)

非常搞笑的一道 dp，细节多裂了，我感到震惊。

考虑到我们的数据范围比较小并且熊的种数很少，所以显然我们可以直接将其作为 dp 的四维（其中一维是当前的总熊数，但是显然我们知道熊的总数和三种熊的数量，肯定知道第四种的数量）。新添加一只熊，造成的影响只有前面两个，再次将其作为 dp 两维。

定义 $dp_{i,a,b,c,x,y}$ 为当前选了 $i$ 只熊，$a$ 个 $A1$ 熊，$b$ 个 $A2$ 熊，$c$ 个 $B1$ 熊，可以得到有 $i-a-b-c$ 个 $B2$ 熊，上上次选了 $x$ 种熊，上次选了 $y$ 种熊。其中 $0 \leq x,y \leq 3$。我们在转移的过程中发现，dp 过程只会用到 $dp_{i-1}$ 去更新 $dp_i$，可以滚动数组。

细节很多，可以给具体实现，注释看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=1000000;
bool ident(int x,int y,int z)
{
	if((x&1) && (y&1) && (z&1))	return false;//A1 和 B1 冲突
	if(!(x&1) && !(y&1) && !(z&1))	return false;//A2 和 B2 冲突
	if(x<=1 && y<=1 && z<=1)	return false;//A 字符冲突
	if(x>=2 && y>=2 && z>=2)	return false;//B 字符冲突
	return true;
}
int a1,a2,b1,b2,dp[2][40][40][40][4][4];
int main(){
	scanf("%d %d %d %d",&a1,&a2,&b1,&b2);
	int n=a1+a2+b1+b2;
	if(n<=1)	return puts("1")&0;//特判一只熊或者没有熊
	for(int i=0;i<=3;++i)
	{
		for(int j=0;j<=3;++j)
		{
			int a=int(i==0)+int(j==0),b=int(i==1)+int(j==1),c=int(i==2)+int(j==2),d=int(i==3)+int(j==3);
			if(a>a1 || b>a2 || c>b1 || d>b2)	continue;
			dp[0][a][b][c][i][j]=1;//填两只熊的情况要自己判断。注意看下是否超过了总数
		}
	}
	for(int i=3;i<=n;++i)
	{
		memset(dp[i&1],0,sizeof dp[i&1]);//注意清空
		for(int a=0;a<=min(i,a1);++a)
		{
			for(int b=0;b<=min(i,a2);++b)
			{
				if(a+b>i)	continue;
				for(int c=0;c<=min(i,b1);++c)
				{
					if(a+b+c>i)	continue;
					int d=i-a-b-c;
					if(d>b2)	continue;
					for(int x=0;x<=3;++x)
					{
						for(int y=0;y<=3;++y)
						{
							for(int z=0;z<=3;++z)
							{//枚举当前四种熊的情况以及上上个，上个，当前这个选的熊的情况
								if(!ident(x,y,z))	continue;
								int la=a-int(z==0),lb=b-int(z==1),lc=c-int(z==2),ld=d-int(z==3);
								if(la<0 || lb<0 || lc<0 || ld<0)	continue;
								dp[i&1][a][b][c][y][z]+=dp[(i&1)^1][la][lb][lc][x][y];
								dp[i&1][a][b][c][y][z]%=MOD;//dp 更新
							}
						}
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=3;++i)	for(int j=0;j<=3;++j)	ans+=dp[n&1][a1][a2][b1][i][j],ans%=MOD;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：joe_zxq (赞：1)

这是一道~~非常有趣的~~ dp 练习题。码字不易，给个赞吧。

## 状态

由于数据范围非常小，我们可以考虑设计多维 dp 状态。我们对四种熊进行编号，$A1,A2,B1,B2$ 分别对应编号 $0,1,2,3$。首先，dp 状态中显然需要有当前分别放置了多少个各个型号的熊。因为当前的熊不可以与前两者的字母和数字完全相同，需要记录当前位置之前两只熊的型号，放入 dp 状态之中。

综上所述，我们可以定义状态 `dp[i][j][k][l][x][y]`，其中 $i,j,k,l$ 表示当前四种熊分别放了多少个，$x,y$ 表示前两只熊的类型。

## 滚动

这题的空间比较充裕，但是我们可以养成滚动第一维的好习惯，成功将空间压缩数十倍，开 long long 都丝毫不怕卡空间。

## 转移

这个转移过程首先要枚举 $i,j,k,l$，可以接着枚举 $x,y$ 进行 dp 的转移，但是我是直接手写了所有转移情况，建议先复制粘贴出所有的转移可能，然后输出不合法的情况。这样，你的代码会看起来十分壮观。

注意取模。

## 初始化

算法需要对所有放了两只熊的 dp 值初始化为 $1$，方便后期实现转移时可以调取前两只熊的类型。

## 特判

由于某些种类的泰迪熊的数量可能为 $0$，需要特判 $n_{A1} + n_{A2} + n_{B1} + n_{B2} \le 1$ 的情况，此时的答案显然为 $1$。

## 复杂度

时间复杂度：$O(n_{A1} \cdot n_{A2} \cdot n_{B1} \cdot n_{B2})$。

空间复杂度：$O(n_{A2} \cdot n_{B1} \cdot n_{B2})$。

## 实现

十分的壮观。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll N = 40, mod = 1e6;
ll a, b, c, d, ans, dp[3][N][N][N][4][4];

void add(ll& x, ll y) {
	x = (x + y) % mod;
}

void solve() {
	cin >> a >> b >> c >> d;
	if (a + b + c + d <= 1) {
		cout << 1;
		return;
	}
	for (ll i = 0; i < 4; i++) {
		for (ll j = 0; j < 4; j++) {
			ll cnt[4] = {0, 0, 0, 0};
			cnt[i]++, cnt[j]++;
			dp[cnt[0] % 3][cnt[1]][cnt[2]][cnt[3]][i][j] = 1;
		}
	}
	for (ll i = 0; i <= a; i++) {
		for (ll j = 0; j <= b; j++) {
			for (ll k = 0; k <= c; k++) {
				for (ll l = 0; l <= d; l++) {
					if (i >= 1) {
						add(dp[i % 3][j][k][l][0][0], dp[(i - 1) % 3][j][k][l][3][0]);
						add(dp[i % 3][j][k][l][1][0], dp[(i - 1) % 3][j][k][l][2][1] + dp[(i - 1) % 3][j][k][l][3][1]);
						add(dp[i % 3][j][k][l][2][0], dp[(i - 1) % 3][j][k][l][1][2] + dp[(i - 1) % 3][j][k][l][3][2]);
						add(dp[i % 3][j][k][l][3][0], dp[(i - 1) % 3][j][k][l][0][3] + dp[(i - 1) % 3][j][k][l][1][3] + dp[(i - 1) % 3][j][k][l][2][3] + dp[(i - 1) % 3][j][k][l][3][3]);
					}
					if (j >= 1) {
						add(dp[i % 3][j][k][l][0][1], dp[i % 3][j - 1][k][l][2][0] + dp[i % 3][j - 1][k][l][3][0]);
						add(dp[i % 3][j][k][l][1][1], dp[i % 3][j - 1][k][l][2][1]);
						add(dp[i % 3][j][k][l][2][1], dp[i % 3][j - 1][k][l][0][2] + dp[i % 3][j - 1][k][l][1][2] + dp[i % 3][j - 1][k][l][2][2] + dp[i % 3][j - 1][k][l][3][2]);
						add(dp[i % 3][j][k][l][3][1], dp[i % 3][j - 1][k][l][0][3] + dp[i % 3][j - 1][k][l][2][3]);
					}
					if (k >= 1) {
						add(dp[i % 3][j][k][l][0][2], dp[i % 3][j][k - 1][l][1][0] + dp[i % 3][j][k - 1][l][3][0]);
						add(dp[i % 3][j][k][l][1][2], dp[i % 3][j][k - 1][l][0][1] + dp[i % 3][j][k - 1][l][1][1] + dp[i % 3][j][k - 1][l][2][1] + dp[i % 3][j][k - 1][l][3][1]);
						add(dp[i % 3][j][k][l][2][2], dp[i % 3][j][k - 1][l][1][2]);
						add(dp[i % 3][j][k][l][3][2], dp[i % 3][j][k - 1][l][0][3] + dp[i % 3][j][k - 1][l][1][3]);
					}
					if (l >= 1) {
						add(dp[i % 3][j][k][l][0][3], dp[i % 3][j][k][l - 1][0][0] + dp[i % 3][j][k][l - 1][1][0] + dp[i % 3][j][k][l - 1][2][0] + dp[i % 3][j][k][l - 1][3][0]);
						add(dp[i % 3][j][k][l][1][3], dp[i % 3][j][k][l - 1][0][1] + dp[i % 3][j][k][l - 1][2][1]);
						add(dp[i % 3][j][k][l][2][3], dp[i % 3][j][k][l - 1][0][2] + dp[i % 3][j][k][l - 1][1][2]);
						add(dp[i % 3][j][k][l][3][3], dp[i % 3][j][k][l - 1][0][3]);
					}
				}
			}
		}
		if (i >= 1) {
			memset(dp[(i - 1) % 3], 0, sizeof dp[(i - 1) % 3]);	
		}
	}
	add(ans, dp[a % 3][b][c][d][0][0] + dp[a % 3][b][c][d][0][1] + dp[a % 3][b][c][d][0][2] + dp[a % 3][b][c][d][0][3]);
	add(ans, dp[a % 3][b][c][d][1][0] + dp[a % 3][b][c][d][1][1] + dp[a % 3][b][c][d][1][2] + dp[a % 3][b][c][d][1][3]);
	add(ans, dp[a % 3][b][c][d][2][0] + dp[a % 3][b][c][d][2][1] + dp[a % 3][b][c][d][2][2] + dp[a % 3][b][c][d][2][3]);
	add(ans, dp[a % 3][b][c][d][3][0] + dp[a % 3][b][c][d][3][1] + dp[a % 3][b][c][d][3][2] + dp[a % 3][b][c][d][3][3]);
	cout << ans;
}

int main() {
	solve();
	return 0;
}
```

---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P3448)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-jie-p3448-poi2006mis-teddies)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

这道题是在给出我们 $4$ 个物品和一系列禁止条件后让我们求方法总数，很容易就想到了 $DP$ 。我们从最简单的想法讲起。

令 $f[i][j][k][l][m][x][y]$ 表示一共取了 $i$ 个玩具，其中有 $j$ 个 $A_1$ 型的，$k$ 个 $A_2$ 型的，$l$ 个 $B_1$ 型的，$m$ 个 $B_2$ 型的，且前两个用的玩具分别是 $x$ 和 $y$ $\text{( x , y 为 0 至 3 的整数，且与 }A_1\,,A_2\,,B_1\,,B_2\text{ 型的玩具的编号依次对应)}$ 时的方法数。但很明显，内存爆了。于是我们想到了降维。

令 $f[i][j][k][l][x][y]$ 表示一共取了 $i$ 个玩具，其中有 $j$ 个 $A_1$ 型的，$k$ 个 $A_2$ 型的，$l$ 个 $B_1$ 型的，$i-j-k-l$ 个 $B_2$ 型的，且前两个用的玩具分别是 $x$ 和 $y$ 时的方法数。则状态转移方程为 $f[i][j][k][l][x][y] = f[i-1][j-1][k][l][x'][y'] + \cdots$。注意到每次状态转移只需要用到第一维前一个数的方法数，故第一维可以滚动掉，就有了 $f[2][j][k][l][x][y]$ ，表示在循环第 $i$ 次时取了 $i$ 个玩具，其中有 $j$ 个 $A_1$ 型的，$k$ 个 $A_2$ 型的，$l$ 个 $B_1$ 型的，$i-j-k-l$ 个 $B_2$ 型的，且前两个用的玩具分别是 $x$ 和 $y$ 时的方法数。

为了方便枚举且减少内嵌循环，我便用一个四进制数 $q$ 来表示前两个玩具取的状况，$q\div{4}$ 为前 $2$ 个取的玩具的编号，$q\mod{4}$ 为前 $1$ 个取的玩具的编号，即有 $f[now][j][k][l][q]$ 在进行第 $i$ 次循环时表示一共取了 $i$ 个玩具，其中有 $j$ 个 $A_1$ 型的，$k$ 个 $A_2$ 型的，$l$ 个 $B_1$ 型的，$i-j-k-l$ 个 $B_2$ 型的，且前两个用的玩具分别是 $q\div{4}$ 和 $q\mod{4}$ 时的方法数。

那么现在怎么判断合法方法数呢？注意到每个玩具所含元素 **（见下表）** ，如果前两个玩具含有四个互不相同的的元素，那么接下来可以取任意的玩具；如果前两个玩具一模一样，那么只剩下一个玩具可以取（不含重复元素），即 $3$ 与这种玩具的编号差；现在剩下的情况就是仅有一个相同元素的两个不同玩具，只要不含有相同那个元素（即不为那两个玩具）即可。

| |$A$|$B$|$1$|$2$|
| -----------: | -----------: | -----------: | -----------: | -----------: |
|$A_1$|$\checkmark$|  |$\checkmark$|  |
|$A_2$|$\checkmark$|  |  |$\checkmark$|
|$B_1$|  |$\checkmark$|$\checkmark$|  |
|$B_2$|  |$\checkmark$|  |$\checkmark$|

由于在前取两个玩具时没有限制，我们只需要判断取两个玩具时是否有足够的个数，若可行，则可行方法数加一。
#### 但此时，我们发现了特殊的情况，就是当总和小于等于一时，无法构成两个连续的玩具，所以我们直接输出总和（因为总和为一时只有$1$种情况，总和为零时只有$0$种情况）。
$\Large\mathscr{Part\,\,2\;\;}\text{Code\qquad}\tiny\sout\text{我就知道你们只看这个}$
```cpp
#include <cstdio>
const int N=40,M=1000000; // M 是模数
int a[4],f[2][N][N][N][16],sum,now,ans; // a 为 4 个玩具的数量，sum 为总和，now 为滚动
inline bool check(int x,int y){ // 判断函数
	int l1=x/4,l2=x%4;
	if(l1+l2==3) return 0;
	else if(l1!=l2) return (y==l1)||(y==l2);
	return y!=3-l1;
}
int main(){
	for(register int i=0; i<4; i++){ // 输入
		scanf("%d",a+i);
		sum+=a[i];
	}
	if(sum<=1){ // 特判
		printf("%d",sum);
		return 0;
	}
	for(register int i=0; i<16; i++){ // 枚举前取两个玩具的方法
		int aa[]={(i/4==0?1:0)+(i%4==0?1:0),(i/4==1?1:0)+(i%4==1?1:0),(i/4==2?1:0)+(i%4==2?1:0),(i/4==3?1:0)+(i%4==3?1:0)};
		if(aa[0]>a[0]||aa[1]>a[1]||aa[2]>a[2]||aa[3]>a[3]) continue;
		f[0][aa[0]][aa[1]][aa[2]][i]++;
	}
	for(register int i=3; i<=sum; ++i){ // 取 n 个玩具，因为前两个玩具已经被取，所以从 3 开始循环
		now^=1;
		for(register int j=a[0]; j>=0; --j){
			for(register int k=a[1]; k>=0; --k){
				for(register int l=a[2]; l>=0; --l){
					int m=i-j-k-l;
					if(m>a[3]) break; // 这里能直接跳出循环的原因是 j, k, l 均是从大到小枚举的，所以再循环均是无意义的
					for(register int q=0; q<16; ++q){ // 枚举前两个玩具的每一种状态
						f[now][j][k][l][q]=0; //由于是滚动数组，所以要先归零
						for(register int w=0; w<4; ++w){
							if(check(q,w)) continue; // 注意这里是判断不能取的跳过循环
							if(j&&q%4==0) f[now][j][k][l][q]+=f[now^1][j-1][k][l][w*4+q/4]%M; //判断是否能取（即上一个取的状态不为零）
							else if(k&&q%4==1) f[now][j][k][l][q]+=f[now^1][j][k-1][l][w*4+q/4]%M;
							else if(l&&q%4==2) f[now][j][k][l][q]+=f[now^1][j][k][l-1][w*4+q/4]%M;
							else if(m&&q%4==3) f[now][j][k][l][q]+=f[now^1][j][k][l][w*4+q/4]%M;
						}
					}
				}
			}
		}
	}
	for(register int i=0; i<16; ++i) ans+=f[now][a[0]][a[1]][a[2]][i]%M; //统计方法总数
	printf("%d",ans%M); //打印
	return 0;
}
```
代码里该解释的都注释了……

我相信如果你没吸氧，肯定会 $T$ 几个点，所以，才有了接下来的……

$\Large\mathscr{Part\,\,3\;\;}\text{打表！}$

我们发现，上述代码的时间复杂度虽然是 $\Theta(N^4)$，但常数达到了 $256$ 倍！对于不可避免的外层循环，我们无能为力，但对于内嵌的枚举与判断，我们却可以在此做文章，下面给出一个$\footnotesize\sout\text{（简单的不能再简单的）}$打表程序。
```cpp
char c[]={'j','k','l','m'};
for(int i=0; i<16; i++) for(int j=0; j<4; j++) if(!check(i,j)) printf("\t\tif(%c) f[now][j][k][l][%d]+=f[now^1][j%s][k%s][l%s][%d]%M;\n",c[i%4],i,(i%4==0?"-1":""),(i%4==1?"-1":""),(i%4==2?"-1":""),(j*4)+(i/4)); //是不是很长？（极限压行）
```
其中 $check$ 函数为上文提到过的判断函数。但这还不够，效率和原来的代码一样，所以我们减少判断，减少多余模，于是就有了以下代码：
```cpp
#include <cstdio>
const int N=40,M=1000000;
int a[4],f[2][N][N][N][16],sum,now,ans;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
}
int main(){
	for(register int i=0; i<4; i++){
		scanf("%d",a+i);
		sum+=a[i];
	}
	if(sum<=1){
		printf("%d",sum);
		return 0;
	}
	for(register int i=0; i<16; i++){
		int aa[]={(i/4==0?1:0)+(i%4==0?1:0),(i/4==1?1:0)+(i%4==1?1:0),(i/4==2?1:0)+(i%4==2?1:0),(i/4==3?1:0)+(i%4==3?1:0)};
		if(aa[0]>a[0]||aa[1]>a[1]||aa[2]>a[2]||aa[3]>a[3]) continue;
		f[0][aa[0]][aa[1]][aa[2]][i]++;
	}
	for(register int i=3; i<=sum; ++i){
		now^=1;
		for(register int j=a[0]; j>=0; --j){
			for(register int k=a[1]; k>=0; --k){
				for(register int l=a[2]; l>=0; --l){
					int m=i-j-k-l;
					if(m>a[3]) break;
					if(j){
						f[now][j][k][l][0]=f[now^1][j-1][k][l][12]%M;
						f[now][j][k][l][4]=(f[now^1][j-1][k][l][9]+f[now^1][j-1][k][l][13])%M;
						f[now][j][k][l][8]=(f[now^1][j-1][k][l][6]+f[now^1][j-1][k][l][14])%M;
						f[now][j][k][l][12]=(f[now^1][j-1][k][l][3]+f[now^1][j-1][k][l][7]+f[now^1][j-1][k][l][11]+f[now^1][j-1][k][l][15])%M;
					}
	                if(k){
	                	f[now][j][k][l][1]=(f[now^1][j][k-1][l][8]+f[now^1][j][k-1][l][12])%M;
	                	f[now][j][k][l][5]=f[now^1][j][k-1][l][9]%M;
	                	f[now][j][k][l][9]=(f[now^1][j][k-1][l][2]+f[now^1][j][k-1][l][6]+f[now^1][j][k-1][l][10]+f[now^1][j][k-1][l][14])%M;
	                	f[now][j][k][l][13]=(f[now^1][j][k-1][l][3]+f[now^1][j][k-1][l][11])%M;	
					}
        	        if(l){
        	        	f[now][j][k][l][2]=(f[now^1][j][k][l-1][4]+f[now^1][j][k][l-1][12])%M;
        	        	f[now][j][k][l][6]=(f[now^1][j][k][l-1][1]+f[now^1][j][k][l-1][5]+f[now^1][j][k][l-1][9]+f[now^1][j][k][l-1][13])%M;
        	        	f[now][j][k][l][10]=f[now^1][j][k][l-1][6]%M;
        	        	f[now][j][k][l][14]=(f[now^1][j][k][l-1][3]+f[now^1][j][k][l-1][7])%M;
					}
                	if(m){
                		f[now][j][k][l][3]=(f[now^1][j][k][l][0]+f[now^1][j][k][l][4]+f[now^1][j][k][l][8]+f[now^1][j][k][l][12])%M;
                		f[now][j][k][l][7]=(f[now^1][j][k][l][1]+f[now^1][j][k][l][9])%M;
                		f[now][j][k][l][11]=(f[now^1][j][k][l][2]+f[now^1][j][k][l][6])%M;
                		f[now][j][k][l][15]=f[now^1][j][k][l][3]%M;
					}
				}
			}
		}
	}
	for(register int i=0; i<16; ++i) ans+=f[now][a[0]][a[1]][a[2]][i]%M;
	printf("%d",ans%M);
	return 0;
}
```
于是我们就愉快地 [$AC$](https://www.luogu.com.cn/record/32183359) 了。$\text{（用时：}1.69s\text{， 内存：}8.28MB\text{）}$

↓奇怪的空行

$\color{white}\colorbox{white}{我是不会告诉你吸氧才跑了 340ms 的qwq}$

---

## 作者：Taduro (赞：1)

这是一道dp。

设$f[i][a][b][c][y][x]$表示dp到第i个熊，第一种熊用了a个，第二种用了b个，第三种用了c个，那么自然第四种用了i-a-b-c个，最后一只熊是第x种，倒数第二只是第y种的方案数。

把每一位都枚举出来，再枚举倒数第三只熊判断合法就可以转移了。

因为转移只会用到i和i-1，所以第一维可以滚动掉，还有，前两只熊要自己用手填出来。

以及判断合法的方式借鉴了另一篇题解。

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#define mod 1000000
using namespace std;
int f[2][39][39][39][4][4];
int u[4],ans,p[4][4];
int main(){
//	freopen("3448.in","r",stdin);
//	freopen("my.out","w",stdout);
	scanf("%d%d%d%d",&u[0],&u[1],&u[2],&u[3]);
	int n=u[0]+u[1]+u[2]+u[3],o,d;
	if (n<2){
		puts("1");
		return 0;
	}
	p[0][0]=p[0][2]=1;p[0][1]=p[0][3]=-1;
	p[1][0]=p[1][1]=1;p[1][2]=p[1][3]=-1;
	for (int i=0; i<=3; i++)
		for (int j=0; j<=3; j++){
			if (i==j&&u[i]<2) continue;
			if (i==0&&u[i]){
				if (j==0&&u[j]) f[0][2][0][0][0][0]++;
				if (j==1&&u[j]) f[0][1][1][0][0][1]++;
				if (j==2&&u[j]) f[0][1][0][1][0][2]++;
				if (j==3&&u[j]) f[0][1][0][0][0][3]++;
			}
			if (i==1&&u[i]){
				if (j==0&&u[j]) f[0][1][1][0][1][0]++;
				if (j==1&&u[j]) f[0][0][2][0][1][1]++;
				if (j==2&&u[j]) f[0][0][1][1][1][2]++;
				if (j==3&&u[j]) f[0][0][1][0][1][3]++;
			}
			if (i==2&&u[i]){
				if (j==0&&u[j]) f[0][1][0][1][2][0]++;
				if (j==1&&u[j]) f[0][0][1][1][2][1]++;
				if (j==2&&u[j]) f[0][0][0][2][2][2]++;
				if (j==3&&u[j]) f[0][0][0][1][2][3]++;
			}
			if (i==3&&u[i]){
				if (j==0&&u[j]) f[0][1][0][0][3][0]++;
				if (j==1&&u[j]) f[0][0][1][0][3][1]++;
				if (j==2&&u[j]) f[0][0][0][1][3][2]++;
				if (j==3&&u[j]) f[0][0][0][0][3][3]++;
			}
		}
	for (int i=3; i<=n; i++){
		o=i%2;
		for (int a=0; a<=u[0]; a++)
		for (int b=0; b<=u[1]; b++)
		for (int c=0; c<=u[2]; c++){
			if (a+b+c<i-u[3]) continue;
			d=i-a-b-c;
			for (int x=0; x<=3; x++)
			for (int y=0; y<=3; y++){
			f[o][a][b][c][y][x]=0;
			for (int z=0; z<=3; z++){
				if(abs(p[0][x]+p[0][y]+p[0][z])==3||
				   abs(p[1][x]+p[1][y]+p[1][z])==3) continue;
				if (x==0&&a)
					(f[o][a][b][c][y][x]+=f[o^1][a-1][b][c][z][y])%=mod;
				if (x==1&&b)
					(f[o][a][b][c][y][x]+=f[o^1][a][b-1][c][z][y])%=mod;
				if (x==2&&c)
					(f[o][a][b][c][y][x]+=f[o^1][a][b][c-1][z][y])%=mod;
				if (x==3&&d)
					(f[o][a][b][c][y][x]+=f[o^1][a][b][c][z][y])%=mod;
			}
			}
		}
	}
	o=n%2;
	for (int i=0; i<=3; i++)
		for (int j=0; j<=3; j++){
			(ans+=f[o][u[0]][u[1]][u[2]][i][j])%=mod;
//			printf("%d %d: %d\n",i,j,f[o][u[0]][u[1]][u[2]][i][j]);
		}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：怺忆 (赞：1)

由题目得 A1和B1、A1和A2、A2和B2、B1和B2放在一起不得超过2个
所以我们给A1、B1、A2、B2定一个权值
```cpp
p[0][1]=p[0][3]=1;p[0][2]=p[0][4]=-1;
p[1][1]=p[1][2]=1;p[1][3]=p[1][4]=-1;
```
w、x、y为三个熊的标号
```cpp
if(abs(p[0][x]+p[0][y]+p[0][w])==3||
abs(p[1][x]+p[1][y]+p[1][w])==3) continue;
```
这样可以判断是否有三只不合规的熊放在一起

我们可以码一个DP
f[i][j][k][g][x][y][z]
i-->枚举A1个数
j-->枚举A2个数
k-->枚举B1个数
g-->枚举B2个数
x、y、z枚举的序列后三只熊

所以我们可以定义 f[40][40][40][40][5][5][5]

但这显然超出128MB
然后我们就可以发现循环中i是依次增加的，且每次只需要i-1的数值，所以我们自然会想到滚动数组
就可以定义 f[2][40][40][40][5][5][5]
但要记得 f[i%2][j][k][g][x][y][z]=0;

但这样还不行，时效过不去
所以就枚举后两只熊；
f[2][40][40][40][5][5]
再枚举这个序列的上一状态，也就是上一只熊；
本题的大致思想便是如此；
DP中要注意将不存在的情况判停
代码如下
```cpp
#include<bits/stdc++.h>
#define TT 1000000
using namespace std;
int ans,f[2][40][40][40][5][5],n,p[2][5],a,b,c,d,h[5],hh[5];
int get(int i,int j,int k,int g,int x,int w,int y){
	if(y==1) i--;
	if(y==2) j--;
	if(y==3) k--;
	if(y==4) g--;
	return f[i%2][j][k][g][w][x];
}
int main(){
	scanf("%d%d%d%d",&a,&b,&c,&d);
	n=a+b+c+d;f[0][0][0][0][0][0]=1;
	p[0][1]=p[0][3]=1;p[0][2]=p[0][4]=-1;
	p[1][1]=p[1][2]=1;p[1][3]=p[1][4]=-1;
	for(int i=0;i<=a;i++)
	for(int j=0;j<=b;j++)
	for(int k=0;k<=c;k++)
	for(int g=0;g<=d;g++)
	for(int x=0;x<=4;x++)
	for(int y=1;y<=4;y++){
		f[i%2][j][k][g][x][y]=0;
		int m=i+j+k+g;
		if(m>0&&y==0) break;
		if(m>1&&x==0) break;
		hh[0]=1<<30;hh[1]=i;hh[2]=j;hh[3]=k;hh[4]=g;
		h[1]=h[2]=h[3]=h[4]=0;
		h[x]++;h[y]++;
		if(h[1]>i||h[2]>j||h[3]>k||h[4]>g) continue;
		for(int w=0;w<=4;w++){
			if((x<1||y<1)&&w>0) break;
			if(m-1>1&&w==0) continue;
	    	if(abs(p[0][x]+p[0][y]+p[0][w])==3||abs(p[1][x]+p[1][y]+p[1][w])==3) continue;
			h[y]--;h[w]++;hh[y]--;
			if(h[w]>hh[w]) continue;
			h[y]++;h[w]--;hh[y]++;
			int ff=get(i,j,k,g,x,w,y);
			f[i%2][j][k][g][x][y]=(f[i%2][j][k][g][x][y]+ff)%TT;
		}
		if(i==a&&j==b&&k==c&&g==d)
		ans=(ans+f[a%2][b][c][d][x][y])%TT;
    }
	printf("%d",ans);
	return 0;
}

```



---

