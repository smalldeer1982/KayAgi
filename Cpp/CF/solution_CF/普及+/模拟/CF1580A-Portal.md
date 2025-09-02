# Portal

## 题目描述

### 题意描述

CQXYM发现了一个大小为$n×m$的、由$n$行$m$列的格子组成的矩阵$A$。此矩阵的每一个方格要么是一个黑曜石块，要么是空的。

CQXYM可以用一次操作将一个黑曜石块挖掉变成空格子，或者是在空格子里放上黑曜石块。

（注意：$（x，y）$意思是纵坐标为$x$、横坐标为$y$的格子）（即$x$行$y$列）

现有一个$a×b$（$a$行$b$列）的矩阵$M$，当且仅当它满足如下条件时，它可以称为一个“下界传送门”：
$a≥5$，$b≥4$。
对于所有$1<x<a$的$x$，格子$（x，1）$与格子$（x，b）$都有黑曜石块。
对于所有$1<x<b$的$x$，格子$（1，x）$与格子$（a，x）$都有黑曜石块。
对于所有的$1<x<a$，$1<y<b$，格子$（x，y）$为空格子。
$（1，1）$、$（1，b）$、$（a，1）$、$（a，b）$四个格子存不存在黑曜石块均可。

请注意：是$a$行、$b$列，不是$a$列、$b$行。
注意四个角的格子可以存在黑曜石块，也可能是空格子。

CQXYM想要知道使得此矩阵的至少一个子矩阵成为一个“下界传送门”所需的最小操作数。
（子矩阵的行数$a≥5$，列数$b≥4$）

## 说明/提示

第一组样例最终形成的“下界传送门”如下：

```cpp
<pre class="verbatim"><br></br>1110<br></br>1001<br></br>1001<br></br>1001<br></br>0111<br></br>
```

### 译者注释

一个最小的“下界传送门”如下,其中四角的格子为0或1均可

0110

1001

1001

1001

0110

## 样例 #1

### 输入

```
1
5 4
1000
0000
0110
0000
0001```

### 输出

```
12```

## 样例 #2

### 输入

```
1
9 9
001010001
101110100
000010011
100000001
101010101
110001111
000001111
111100000
000110000```

### 输出

```
5```

# 题解

## 作者：pengyule (赞：6)

> 给定 01 矩阵 $a$ 。你可以进行如下操作
>
> - 选择一个位置反色（1 变 0，0 变 1）
>
> 问使得 $a$ 满足下述条件的最少操作数
>
> - $\exists$ 大小为 $a×b$ 的矩形 $M$ 满足以下条件：
>   - $a≥5$，$b≥4$。
>   - 对于所有 $1<x<a$，块 $M_{x,1}$ 和 $M_{x,b}$ 为 1。
>   - 对于所有 $1<x<b$，块 $M_{1,x}$ 和 $M_{a,x}$ 是黑曜石块。
>   - 对于所有 $1<x<a,1<y<b$，块 $M_{x,y}$ 是一个空块。
>   - $M_{1,1},M_{1,b},M_{a,1},M_{a,b}$ 可以是任何类型。

需要一定的思维。

考虑枚举矩形的上下界（并且定住它）。考虑以类似双指针的方式移动左右边界。

首先枚举矩形的右边界。当一个以当前右边界为右边界、4为宽的矩形的代价<以当前右边界为右边界、当前左边界为左边界的矩形的代价时，将左边界移动到新矩形对应的左边界位置（即右边界-3处）。

关于算代价：用一个变量 $cnt$ 记录每个矩形 不计右边界这一条线 需要的代价，对每一个右边界的位置，再临时用 $cnt$ 加上右边界所需的代价来更新答案。每向右移动一次右边界，只需要在 $cnt$ 上更新上下边界新增的总计2个位置的代价。每移动一次左边界，重新利用二维前缀和算代价。

关于预处理：预处理出二维前缀和数组就够用了。

【参考代码】[CF Submission](https://codeforces.com/problemset/submission/1581/130464660)

---

## 作者：xh39 (赞：4)

必须提前学习 动态规划 算法。建议学习[求最大子序列](https://www.luogu.com.cn/problem/P1115)。

题意简述:寻找一个行至少为 $5$，列至少为 $4$ 的子矩阵。并把矩阵中间全部改成  $0$，边界改成 $1$，但四个角不用改。求最小修改次数。

不难想到暴力算法:枚举起始点 $(x0,y0)$，终点 $(x1,y1)$。

但是显然会超时，不难想到最大子矩阵的优化思路，首先枚举  $x0,x1$，然后再设计dp转移,dp转移类似最大子序列。

设 $f_k$ 为以编号为 $k$ 的元素结尾，**除去最右边一列**最优需要修改几次。(至于为什么除去，稍后会讲)

那么可以有以下两种转移方式:

沿用上一次的最小值。那么答案就是 第 $k$ 列 $[x0,x1]$ 修改成 $0$ 最少次数。(关于具体求法后面会讲)

为什么这样就是对的呢?因为无论如何都得加上 修改次数，所以上一次的最小值一定是这一次的最小值。

新开一个子序列。此时不可能再开一个长度超过 $4$ 的子序列。因为这样就变成了 沿用上一次的最小值 情况。所以这种情况需要将第 $k,k-1,k-2$ 列全部修改成两边 $1$ 中间 $0$，将 $k-3$ 列中间修改成 $1$(只针对 $[x0,x1]$ 行)。

状态转移方程的代码($q0(i,j,k)$ 表示第 $(i,j)$ 行 $k$ 列 全部改成中间 $0$ 两边 $1$ 的最小次数，$q1$ 则改成中间 $1$)(使用了滚动数组):
```cpp
for(k=3;k<m;k++){
  f[i]=min(q0(i,j,k)+q0(i,j,k-1)+q1(i,j,k-2),f[i-1]+q0(i,j,k));
}
```

接下来就看如何求 $q$。实际上可以枚举所有的 $i,j,k$，暴力预处理，本人赛后才想到这种暴力的方法，所以讲一下前缀和的做法，如果不想看可以跳过。

这种静态区间求和问题可以想到前缀和。对于第一种情况，只需求一次出区间和，而第二种情况只需求 $4$ 次，因此不需要二维前缀和。

那么可以分别设 $s0(i,j)$ 表示将第 $j$ 列 $[1,i]$ 行修改成 $0$ 的最小次数，$s1$ 表示修改成 $1$ 的最小次数。

预处理部分代码($a$ 表示输入给出的原矩阵)：
```cpp
for(i=1;i<=n;i++){
  for(j=1;j<=m;j++){
    s0[i][j]=s0[i-1][j]+a[i][j];
    s1[i][j]=s1[i-1][j]+!a[i][j];
  }
}
```
但是到这里还没有做完，因为我们把最右边一列给删掉了，现在要复原回来。那么就要加回来。如何加就简单了，不讲。最后把所有的 $f$ 取最小值就得到答案了。

为何要去掉右边?因为如果不去掉，那么前一个的最小值无法代表当前的最小值。

代码:
```cpp
#include<iostream>
using namespace std;
bool a[2005][2005];
int s0[2005][2005],s1[2005][2005];
int q(int l,int r,int y){
	return s0[r-1][y]-s0[l][y]+!a[l][y]+!a[r][y]; //两边都得是1,中间是0。
}
void Main(){
	int n,m,i,j,k,l,ykb,sum=0,Min=999999999;
	char A;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>A;
			a[i][j]=(A=='1');
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			s0[i][j]=s0[i-1][j]+a[i][j];
			s1[i][j]=s1[i-1][j]+!a[i][j];
		}
	}
	for(i=1;i<=n;i++){
		for(j=i+4;j<=n;j++){ //行至少为5。
			sum=999999999; //采用了滚动数组优化。于是初始值赋为无穷大。
			for(k=3;k<m;k++){
				sum=min(q(i,j,k)+q(i,j,k-1)+s1[j-1][k-2]-s1[i][k-2],sum+q(i,j,k)); //最左边两边不需要加,所以查询的区间是[i+1,j-1]。
				Min=min(Min,sum+s1[j-1][k+1]-s1[i][k+1]); //要把最右边加回来。
			}
		}
	}
	cout<<Min<<endl;
}
int main(){
	int t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
}
```

---

## 作者：Illusory_dimes (赞：1)

[不知道更好还是更坏，反正要用来骗访问的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15169251.html#_label4_2)

## Description

在一个 $n$ 行 $m$ 列的 $0/1$ 矩阵里面，找到一个至少 5 行， 4 列的矩形，最小化将选定矩阵修改成以下要求的矩阵的修改次数：

1. 除去最外一圈，其余均为 0 ；

2. 最外一圈除了四角，其余均为 1 。

多测。

$5\leq n \leq 400,\ 4\leq m\leq 400$

## Solution

首先最暴力的就是 $\small O(n^2m^2)$ 枚举两个点加 $\small O(nm)$ 统计答案，统共 $\small O(n^3m^3)$ 。

加个前缀和， $\small O(n^2m^2)$ 。

考虑怎么优化，枚举这些已经不能再优了，但是其实和前缀和思想一样，我们可以在计算许多矩形的时候利用一下前面已有的答案。

但我们还是先定上下边界，然后从左往右计算定好右边界的时候的最小答案。

（我是从右往左，因为1开始有点晕，n开始方便一点，但讲的时候还是从左往右）

然后我们可以先算最左边最小的矩形，然后发现向右扩展的时候有点麻烦，所以我们干脆先撇掉最右边这一列，这样扩展起来就好多了，

这是我们就只需要算两个东西：

1.以右边界为起点的最小矩形答案

2.以右边界为起点的其它矩形最小答案

显然情况 2 就是前面传下来的答案，直接就可以用，一也可以 $\small O(1)$ 算。

最后再全部加上最右边这一列的贡献就可以了。

时间复杂度 $\small O(n^3)$ 级。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 410, INF = 1e9;
ll t, n, m, ans, cnt[N];
ll pos[N][N], qzh[N][N];
string s[N];
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {s = (s << 3) + (s << 1) + ch - '0'; ch = getchar();}
	return s * w;
}
inline ll calc(int x1, int y1, int x2, int y2) {
	ll res = qzh[x2][y2] - qzh[x1 - 1][y2];
	ll ret = qzh[x2][y1 - 1] - qzh[x1 - 1][y1 - 1];
	return res - ret;
}
inline void mian() {
	n = read(); m = read(); ans = INF;
	for (int i = 1; i <= n; ++i) {
		getline(cin, s[i]);
		for (int j = 1; j <= m; ++j) {
			pos[i][j] = s[i][j - 1] - '0';
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			qzh[i][j] = pos[i][j];
			qzh[i][j] += qzh[i - 1][j] + qzh[i][j - 1] - qzh[i - 1][j - 1];
		}
	}
	for (int l = 1; l <= m; ++l) {
		for (int r = l + 3; r <= m; ++r) {
			cnt[n - 3] = r - l - 1 - calc(n, l + 1, n, r - 1) + 6;
			cnt[n - 3] += calc(n - 3, l + 1, n - 1, r - 1);
			cnt[n - 3] -= calc(n - 3, l, n - 1, l) + calc(n - 3, r, n - 1, r);
			for (int i = n - 4; i >= 1; --i) {
				cnt[i] = r - l - 1 - calc(i + 3, l + 1, i + 3, r - 1) + 6;
				cnt[i] += calc(i, l + 1, i + 2, r - 1);
				cnt[i] -= calc(i, l, i + 2, l) + calc(i, r, i + 2, r);
				ll num = (!pos[i][l]) + (!pos[i][r]);
				cnt[i] = min(cnt[i], cnt[i + 1] + calc(i, l + 1, i, r - 1) + num);
			}
			for (int i = 1; i <= n - 4; ++i) {
				ans = min(ans, cnt[i + 1] + r - l - 1 - calc(i, l + 1, i, r - 1));
			}
		}
	}
	printf("%lld\n", ans);
}
int main() {
	t = read();
	while (t--) mian();
	return 0;
}
```

---

## 作者：S00021 (赞：1)

## 真的没有乱搞题解吗？

首先 $\mathcal{O}(n^2 m^2)$ 的暴力就是枚举矩形左上角和右下角，然后用预处理的前缀和数组 check，但是显然过不去。

然后你可能会想可不可以将某一维枚举时重新设定一个上限，当然这样是不可以的，出题人会把你定向卡，你将会愉悦地收获 `wrong answer on test 61` 的好成绩。

那么我们的出发点不应该是减少循环次数了，而是找到一个最优化剪枝作为支点，把循环内冗余的状态剪掉，稍微试几次就可以发现我们只要枚举了左上角，左上角控制的矩形的半个外轮廓所产生的代价不可能被消去，而右下角往外移的时候原有的要变成空格子的格子产生的代价也不可能被消去，所以一旦答案比这两者加起来要小就不继续循环。

这个剪枝实际效果很好，复杂度仍然是 $\mathcal{O}(n^2m^2)$ 但是实测跑得很快。

代码：

```cpp
#include<bits/stdc++.h>
#define rg register
#define MAXN 400
using namespace std;
int n,m,s[MAXN+5][MAXN+5];
inline int sum1(int x,int y,int a,int b){
	return s[a][b]-s[x-1][b]-s[a][y-1]+s[x-1][y-1];
}
inline int sum0(int x,int y,int a,int b){
	return (a-x+1)*(b-y+1)-sum1(x,y,a,b);
}
signed main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(rg int i=1;i<=n;i++)
			for(rg int j=1;j<=m;j++){
				char ch=0; while(!isdigit(ch)) ch=getchar();
				s[i][j]=ch-'0';
			}int ans=0x3f3f3f3f;
		for(rg int i=1;i<=n;i++)
			for(rg int j=1;j<=m;j++)
				s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		for(rg int x=1;x<=n;x++)
			for(rg int y=1;y<=m;y++)
				for(rg int a=x+4;a<=n;a++)
					for(int b=y+3;b<=m;b++){
						rg int ret1=sum0(x,y+1,x,b-1)+sum0(x+1,y,a-1,y);
						rg int ret2=sum0(x+1,b,a-1,b)+sum0(a,y+1,a,b-1);
						rg int empt=sum1(x+1,y+1,a-1,b-1);
						if(ans<ret1+empt) break;
						ans=min(ans,ret1+ret2+empt); 
					}printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1580A)

------------
# 思路：
首先处理二维前缀和，然后枚举上行 $w$ 和下行 $s$ 然后预处理 $F$ 数组。

设 $l,r$ 为左右界 $f_i$ 该数组意为 $L$ 为 $1$ 并且，$R$ 至少大于 $i$ 的前缀和的最小值。

然后枚举左界 $L$ 用 $R$ 至少大于等于 $L + 3$ 的 $F$ 数组去减去 $1 \sim L$ 的部分。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;
const int maxn=405;
int mp[maxn][maxn];
int sum[maxn][maxn],f[maxn];
int T,n,m;
void init()
{
 
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            sum[i][j]=mp[i][j]=0;
            f[j]=0;
        }
    }
}
inline int getsum(int lx,int ly,int rx,int ry)
{
	return sum[rx][ry]-sum[rx][ly-1]-sum[lx-1][ry]+sum[lx-1][ly-1];
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        init();
        string s;
        for(int i=1;i<=n;i++)
        {
            cin>>s;
            for(int j=1;j<=s.size();j++)
            {
                int t=s[j-1]-'0';
                mp[i][j]=t;
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mp[i][j];
            }
        }
        int ans=1e9;
        for(int i=1;i<n;i++)
        {
            for(int j=i+4;j<=n;j++)
            {
                for(int k=4;k<=m;k++)
                {
                    f[k]=getsum(i+1,1,j-1,k-1)+(k-1)*2-getsum(i,1,i,k-1)-getsum(j,1,j,k-1)+j-i-1-getsum(i+1,k,j-1,k);
                    //计算的依次是中间的空白 上下的边缘和 右边的边缘 （左边缘不计算） 
                }
                for(int k=m-1;k>=4;k--)
                {
                    f[k]=min(f[k],f[k+1]);
                }
				for(int k=1;k+3<=m;k++)
				{
					int tmp=f[k+3]-(getsum(i+1,1,j-1,k)+k*2-getsum(i,1,i,k)-getsum(j,1,j,k))+(j-i-1)-getsum(i+1,k,j-1,k);
					ans=min(ans,tmp);
				}
            }
        }
        cout<<ans<<endl;
 
    }
    return 0;
}
 ```

---

