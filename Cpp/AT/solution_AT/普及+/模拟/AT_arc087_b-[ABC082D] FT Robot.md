# [ABC082D] FT Robot

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc082/tasks/arc087_b

二次元平面の原点にロボットが置かれています。 最初、ロボットは $ x $ 軸の正の向きを向いています。

このロボットに命令列 $ s $ が与えられます。 $ s $ は次の $ 2 $ 文字のみからなり、先頭から末尾まで順に実行されます。

- `F` : 今向いている向きに長さ $ 1 $ だけ移動する。
- `T` : 時計回りまたは反時計回りの好きな方向に $ 90 $ 度だけ向きを変える。

ロボットの目標は、命令列をすべて実行し終わった後に座標 $ (x,\ y) $ にいることです。 この目標が達成可能か判定してください。

## 说明/提示

### 制約

- $ s $ は `F`, `T` のみからなる。
- $ 1\ \leq\ |s|\ \leq\ 8\ 000 $
- $ x $, $ y $ は整数である。
- $ |x|,\ |y|\ \leq\ |s| $

### Sample Explanation 1

$ 1 $ 番目の `T` で反時計周りに $ 90 $ 度だけ向きを変え、$ 2 $ 番目の `T` で時計周りに $ 90 $ 度だけ向きを変えればよいです。

### Sample Explanation 2

$ 1 $ 番目の `T` で時計周りに $ 90 $ 度だけ向きを変え、$ 2 $ 番目の `T` で時計周りに $ 90 $ 度だけ向きを変えればよいです。

### Sample Explanation 5

例えば、$ 1 $ 番目の `T` で反時計周りに $ 90 $ 度だけ向きを変え、$ 2 $ 番目の `T` で反時計周りに $ 90 $ 度だけ向きを変えればよいです。

## 样例 #1

### 输入

```
FTFFTFFF
4 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
FTFFTFFF
-2 -2```

### 输出

```
Yes```

## 样例 #3

### 输入

```
FF
1 0```

### 输出

```
No```

## 样例 #4

### 输入

```
TF
1 0```

### 输出

```
No```

## 样例 #5

### 输入

```
FFTTFF
0 0```

### 输出

```
Yes```

## 样例 #6

### 输入

```
TTTT
1 0```

### 输出

```
No```

# 题解

## 作者：0xyz (赞：12)

不到 400b 而且可读的代码。

### 一、做法

一开始的思路是针对每一个 `T` 左转还是右转来搜索，但是这样时间复杂度爆炸。

然后就是正解。假设在现在操作到的位置之前有 $c$ 个 `T`，分类讨论。

1. $c=0$，机器人的方向一定是 $x$ 轴正方向。
2. $c=1,3,5,7,9,…$，机器人的方向一定可以是并且只能是 $y$ 轴的正方向或者负方向。
3. $c=2,4,6,8,10,…$，机器人的方向一定可以是并且只能是 $x$ 轴的正方向或者负方向。

这一性质可以用数学归纳法证明。

所以我们可以在去掉 $c=0$ 的所有字符影响后，以 $c$ 的奇偶性将机器人的横纵坐标分开来考虑。这个可以用动态规划做。

以横坐标为例，我们把一段段的 `F` 的长度记录下来。假设已经遍历完了的最近一段 `F` 长度为 $w$。我们用一个 `bool` 值 $x_{i-1,j}$ 代表这次操作前能否达到第 $j$ 位，那么这一次操作可以是减少横坐标，也可以是增加横坐标。所以我们就有 $x_{i,j}=x_{i-1,j+w}\operatorname{or}x_{i-1,j-w}$，其中 $\operatorname{or}$ 是逻辑或运算。然后这个东西就是一堆逻辑或运算，所以我们可以用滚动数组优化和 `bitset` 优化，直接将一次转移写成 `x=x<<w|x>>w`。

最后就是判断所有操作后能否同时达到最终的横纵坐标。

时间复杂度 $O(\frac{n^2}{\omega})$，可以通过此题。

注意途中横纵坐标在不断减的时候很可能变为负数，所以要加上一个值保证下标恒为正。

### 二、代码

最后就是这个不到 400b 的代码了。末尾加上一个 `T` 是为了处理最后可能出现的一段 `F`。

```cpp
#include<bits/stdc++.h>
#define z 16005
using namespace std;
int n,X,Y,p,c,w;
string s;
bitset<z*2>x,y;
int main(){
	x[z]=y[z]=1;
	cin>>s>>X>>Y;s+="T";n=s.size();
	for(int i=0;i<n;i++)
		if(s[i]=='T'){
			if(!c)X-=i;
			else if(w=i-1-p){
				if(c&1)y=y<<w|y>>w;
				else x=x<<w|x>>w;
			}
			p=i;c++;
		}
	if(x[z+X]&&y[z+Y])cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：Mysterious_Cat (赞：9)

### 话说这么好的题没人写题解？？？
## 正文：
### 题目大意：给出一个由F和T构成的指令序列，F为向当前方向移动一格，T为转向九十度
### 题目思路：$DP$
#### Step 1：考虑字符串转化
对于字符串题目，无非只有两种做法  
1. 进行模拟求解
2. 转化为数据，再进行算法优化  

很明显，第$1$种做法明显超时，所以考虑数据转化。  

不难发现，在每次遇到转向前，F前进一格方向不变，所以连续的$k$个F可看作一次操作：向当前方向移动$k$格。  

继续来考虑T，从$x$轴正（负）方向转向后变为$y$轴正（负）方向，同理从$y$轴正（负）方向转向后变为$x$轴正（负）方向。在$x$轴正（负）方向上移动只改变机器人的横坐标，在$y$轴正（负）方向上移动只改变机器人纵坐标，互相无影响，可将$x$轴与$y$轴分开存。  

**示例：**
```cpp
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == 'T')
		{
			n[id]++;//设n数组表示数据量，id = 1时为x轴，id = 2时为y轴
			w[id][n[id]] = len;//w数组表示F个数
			len = 0;//len为已经累加的F个数
			id = 3 - id;//转向
		}
		else len++;//累加F
	}
```
#### Step 2:算法优化
因为遇T是有决策的，所以一定是$DFS$或$DP$，但$DFS$时间复杂度过高，考虑$DP$。  

我们发现：对于T操作，其实就是选择正方向或负方向，因为在$x$轴正（负）方向上移动与在$y$轴正（负）方向上移动互相无影响，所以分开$DP$，计算$x$轴是否能到达目标$x_1$，计算$y$轴是否能到达目标$y_1$.

- **状态定义：$dp[i][j]$为第$i$次移动后能否到达坐标$j$**
- **转移方程：$dp[i][j] = dp[i - 1][j - w[i]] || dp[i - 1][j - w[i]]$**
- **边界条件：坐标系中有负数，所以需要平移，$-8000 + NR < j + NR < 8000 + NR$**

**示例：**
```cpp
dpx[1][w[1][1] + NR] = true;
	for(int i = 2; i <= n[1]; i++)
		for(int j = -8000; j <= 8000; j++)
		{
			if(j - w[1][i] > -8000) dpx[i][j + NR] |= dpx[i - 1][j + NR - w[1][i]];
			if(j + w[1][i] < 8000) dpx[i][j + NR] |= dpx[i - 1][j + NR + w[1][i]];
		}
```


------------
## Code（猜到你们就只会看这里）:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int NR = 8005;

bool dpx[NR / 2][NR * 2], dpy[NR / 2][NR * 2];
int n[3], w[3][NR];

int main()
{
	int x, y, len = 0, id = 1;
	string s;
	cin >> s >> x >> y;
	s += 'T';
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == 'T')
		{
			n[id]++;
			w[id][n[id]] = len;
			len = 0;
			id = 3 - id;
		}
		else len++;
	}
	dpx[1][w[1][1] + NR] = true;
	for(int i = 2; i <= n[1]; i++)
		for(int j = -8000; j <= 8000; j++)
		{
			if(j - w[1][i] > -8000) dpx[i][j + NR] |= dpx[i - 1][j + NR - w[1][i]];
			if(j + w[1][i] < 8000) dpx[i][j + NR] |= dpx[i - 1][j + NR + w[1][i]];
		}
	dpy[0][0 + NR] = true;
	for(int i = 1; i <= n[2]; i++)
		for(int j = -8000; j <= 8000; j++)
		{
			if(j - w[2][i] > -8000) dpy[i][j + NR] |= dpy[i - 1][j + NR - w[2][i]];
			if(j + w[2][i] < 8000) dpy[i][j + NR] |= dpy[i - 1][j + NR + w[2][i]];
		}
	if(dpx[n[1]][x + NR] && dpy[n[2]][y + NR]) printf("Yes");
	else printf("No");
	
	return 0;
}
```


---

## 作者：Find_Yourself (赞：2)

首先可以观察到一个非常重要的性质：对于一次前进的操作，如果前面有奇数次转向，则走上下，否则走左右。（当然如果一开始就前进就只能走右）

于是我们可以将其拆成许多的“块”，并分成两类，即前进方向为左右还是上下。

![](https://cdn.luogu.com.cn/upload/image_hosting/oooxm0qy.png)

然后对于两个维度分别 dp 。

$f_{i},_{j}=f_{i-1},_{j-val} \ | \ f_{i-1},_{j+val}$

$g$ 同理。

当然还要对负数的情况以及边界进行一下处理。

## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 8000 + 5, nn = 8000;
string s;
int len, ex, ey, tot = 0;
bool f[2][N * 2], g[2][N * 2];
struct node{int type, num;}a[N];
vector<int> v[2];
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> s >> ex >> ey; len = s.size(); s = "." + s;
	int cnt = 0, flag = 0;
	for (int i = 1; i <= len; ++i) { //预处理出每个块 
		if (s[i] == 'F') {
			if (!flag) a[++tot].type = cnt % 2, a[tot].num = 1, flag = 1;
			else if (flag) ++a[tot].num;
		} else {
			flag = 0;
			++cnt;
		}
	}
	int st = 1, t = 0, t2 = 0;
	if (s[1] == 'F') st = 2, f[0][a[1].num + nn] = 1; //单独处理一下一开始就前进的情况 
	for (int i = st; i <= tot; ++i) v[a[i].type].push_back(a[i].num);
	g[0][nn] = 1;
	if (st == 1) f[0][nn] = 1;
	for (int i = 0; i < v[0].size(); ++i) { //横坐标DP 
		for (int j = -nn; j <= nn; ++j) {
			f[t ^ 1][j + nn] = 0;
			if (j - v[0][i] >= -nn) f[t ^ 1][j + nn] |= f[t][j - v[0][i] + nn];
			if (j + v[0][i] <= nn) f[t ^ 1][j + nn] |= f[t][j + v[0][i] + nn];
		}
		t ^= 1;
	}
	for (int i = 0; i < v[1].size(); ++i) { //纵坐标DP 
		for (int j = -nn; j <= nn; ++j) {
			g[t2 ^ 1][j + nn] = 0;
			if (j - v[1][i] >= -nn) g[t2 ^ 1][j + nn] |= g[t2][j - v[1][i] + nn];
			if (j + v[1][i] <= nn) g[t2 ^ 1][j + nn] |= g[t2][j + v[1][i] + nn];
		}
		t2 ^= 1;
	}
	if (f[t][ex + nn] && g[t2][ey + nn]) cout << "Yes" << endl; //如果都能达到，输出Yes 
	else cout << "No" << endl;
	return 0;
}
```


---

## 作者：Rnfmabj (赞：2)

为什么不用用神奇的 `bitset` 呢？

-----

此类题目的一个经典 trick 是横纵无关，即横向移动与纵向移动相互独立。这很好理解，因为你一开始横着（向右），旋转一次以后不管往左还是往右，转完都只能纵向移动，再旋转一次以后又变成只能横向移动，……并且在旋转之前只能朝着上次决定的方向走，所以连续的若干个前进指令可以被压缩为一个“前进若干步”的指令。我们发现，除了一开始被题目强制指定的朝着 $x$ 轴正方向以外，接下来到底是转向正方向还是反方向都是我们可以决定的。

然后就可以把横向和纵向分别处理，问题转化为经典的动态规划：在一个坐标轴上有若干条指定距离的指令，第 $i$ 条指令的距离为 $d_i$ ，求是否可通过改变指令方向来到达某个点。

设 $f_{i,j} ∈ {0,1}$ 表示考虑到第 $i$ 个指令时，是否可以到达点 $j$ 。 则有 $f_{i,j}=f_{i-1,j-a_i}\  \operatorname{or}\  f_{i-1,j+a_i}$ 。复杂度 $O(n^2)$，是对的，但是我们的坐标轴长度差不多有 $8000$ 的样子，跑起来有点虚。

于是我们用滚动数组和 `bitset` 优化一手，顺便节省下码量。这样一来直接令 `f[i]=(f[i-1]<<a[i]) | (f[i-1]>>a[i])` 即可。时间复杂度 $O(\frac{n^2} {w} )$，跑得嗷嗷快。

```cpp
const ll maxn=8e3+5;
char c[maxn];//读入指令
bitset<16005>f[2];
ll a[2][maxn],cnt[2];//0为横向，1为纵向
ll s;
void solve(){
	cin>>(c+1);
	ll n=strlen(c+1)+1;
	c[n]='T';//设置不存在的最后一位为转向，便于统计
	ll x=R,y=R;
	ll p=1;
	while(c[p]!='T')p++;//预处理出固定方向的第一个指令。这个的方向不受我们控制，所以要特判。（其实后面的操作取个反就行了，影响不大）
	s=p-1;
	bool cur=0;
	ll tmp=0;
	for(ll i=p;i<=n;i++){
		if(c[i]=='T'){
			a[cur][++cnt[cur]]=tmp;
			tmp=0;
			cur^=1;//改变方向
		}
		else tmp++;
	}
	f[0][s+(ll)8e3]=1;//注意是从预处理出的起点开始而不是原点
    //加上8e3是为了处理负数坐标，做一个水平平移
	for(ll i=1;i<=cnt[0];i++){
		f[1].reset();//清空当前
		f[1]=(f[0]<<a[0][i])|(f[0]>>a[0][i]);//转移
		f[0]=f[1];//滚动
	}
	if(!f[0][x+(ll)8e3]){
		puts("No");//横向已经挂掉了就已经不可能了
		return ;
	}
	f[0].reset();//清空，接着做纵向
	f[0][(ll)8e3]=1;//纵向就是从原点开始了
	for(ll i=1;i<=cnt[1];i++){
		f[1].reset();
		f[1]=(f[0]<<a[1][i])|(f[0]>>a[1][i]);
		f[0]=f[1];
	}//同上
	if(!f[0][y+(ll)8e3]){
		puts("No");
		return ;
	}
	puts("Yes");
	return ;
}
```



---

## 作者：small_john (赞：1)

## 前言

简单的 DP 题。

## 思路

首先要明确一个性质，当 `T` 的个数为偶数时，机器人肯定是按照平行于横轴方向行驶，否则按平行于纵轴方向行驶。

把这道题分开处理，设 $dp1_{i,j}$ 表示第 $i$ 步能不能走到横坐标为 $j$ 的点，$dp2_{i,j}$ 表示第 $i$ 步能不能走到纵坐标为 $j$ 的点。

如果一步一步转移会 MLE，所以把每一段连续的 `F` 记录为一步，记 $m$ 为总步数。

接下来就是状态转移方程式。设 $now$ 为这一步走的长度，$cnt$ 为当前 `T` 的个数。那么就分两种情况：

1. $cnt\equiv0\pmod2$：转移 $dp1$。由于第一步只能朝正方向走，所以 $dp1_{1,j}=dp1_{0,j-now}$，而其他的正负方向都可以，即 $dp1_{i,j}=dp1_{i,j-now}\operatorname{or}dp1_{i,j+now}$。

2. $cnt\equiv1\pmod2$：转移 $dp2$。方向没有限制都可以，即 $dp2_{i,j}=dp2_{i,j-now}\operatorname{or}dp2_{i,j+now}$。

DP 完之后，只需要判断 $dp1_{m,x}$ 和 $dp2_{m,y}$ 的值，两个都为 $1$ 就输出 `Yes`，否则输出 `No`。

注：由于坐标存在负数情况，所以 DP 时下标加上 $8000$ 保证为非负数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 8e3+10,M = 8e3;
string s;
int x,y,cnt,now,m,dp1[N][N*2],dp2[N][N*2];
signed main()
{
	cin>>s>>x>>y;
	dp1[0][M] = dp2[0][M] = 1;
	s+='T';//处理最后一段F
	for(int i = 0;i<s.size();i++)
	{
		if(s[i]=='T')
		{
			if(s[i-1]!='T')
			{
				m++;
				for(int j = -8000;j<=8000;j++)
					if(cnt%2==0)
					{
						if(j+now+M<N*2) dp1[m][j+M] = m!=1&&dp1[m-1][j+now+M];
						if(j-now+M>=0)dp1[m][j+M]|=dp1[m-1][j-now+M];
					}
					else dp1[m][j+M] = dp1[m-1][j+M];
				now = 0;
			}
			cnt++;
		}
		else now++;
	}
	m = now = cnt = 0;
	for(int i = 0;i<s.size();i++)
	{
		if(s[i]=='T')
		{
			if(s[i-1]!='T')
			{
				m++;
				for(int j = -8000;j<=8000;j++)
					if(cnt%2)
					{
						if(j+now+M<N*2) dp2[m][j+M] = dp2[m-1][j+now+M];
						if(j-now+M>=0) dp2[m][j+M]|=dp2[m-1][j-now+M];
					}
					else dp2[m][j+M] = dp2[m-1][j+M];
				now = 0;
			}
			cnt++;
		}
		else now++;
	}
	if(dp1[m][x+M]&&dp2[m][y+M]) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

我们把二维坐标分成 $2$ 个一维的单独考虑。

设 $dp_{i,j}$ 表示第 $i$ 次移动后能否到达 $j$ 处。

定义 $1$ 个二维数组 d，$d[0]$ 表示的是 $x$ 轴正方向 F 的个数，$d[1]$ 表示的是 $y$ 轴正方向 F 的个数。

枚举 $i$ 和 $j$。

有 $2$ 种情况：

- 从前面 $j-d[0/1][i]$ 的位置来的。

- 从后面 $j+d[0/1][i]$ 的位置来的。

判断是否越界，没越界 $\mathrm{or}$ 运算一下即可。

状态转移方程：

$$
dp_{i,j}=dp_{i,j-d[0/1][i]} \space \mathrm{or} \space dp_{i,j+d[0/1][i]}
$$

最后判断 $2$ 个维度是否都满足条件即可。

注意：

- 初始时，$x$ 轴的只能走 $1$ 个方向，而 $y$ 轴的 $2$ 个方向都可以。

- 坐标可能为负，所以下标需要加上一个大数，变为非负数。

完结撒花~

## Code

[Link](https://atcoder.jp/contests/abc082/submissions/54693946)

---

## 作者：Erica_N_Contina (赞：0)



# [ABC082D] FT Robot



## 思路

一开始我们的想法是能不能通过模拟或者类似 BFS 的算法解决此问题。

我们将字符串进行压缩，将一连串的 $F$ 压缩成一个块，在这个块上我们标记一共有几个 $F$。因为在一连串 $F$ 中我们不能更改我们的方向，所以我们完全可以把一连串的 $F$ 进行压缩。然后我们预处理出每个 $F$ 块前有几个 $T$。

为什么要这样做呢？

我们考虑到，对于一个 $F$ 操作，机器人是水平运动还是竖直移动和这个 $F$ 前面的 $T$ 的数量有关。

机器人的初始方向为 $x$ 轴的正方向，所以如果 $F$ 前面的 $T$ 的个数为 $0$，那么它只能够向 $x$ 轴正方向移动。

由于对于每一个 $T$ 我们都必须做出转向，所以我们很容易总结出当 $F$ 前面的 $T$ 的个数为奇数时，其方向为竖直方向。否则若 $T$ 的数量为偶数时，其方向为水平方向。

对于 $T$ 的个数为 $0$ 的 $F$，我们可以直接处理，然后把遇到的第一个 $T$ 时候的机器人的位置作为起点。这样我们就只需要讨论 $T$ 的个数的奇偶性了。

接下来我们就可以拿出我们的 dp 了

## dp 设计

我们记录 $2$ 个 bool 类型的数组 $dpx_{i,j}$，定义为第 $i$ 次操作能否到达 $x$ 坐标为 $j$ 的点。$dpy_{i,j}$ 定义为第 $i$ 次操作能否到达 $y$ 坐标为 $j$ 的点。

假设目前的 $F$ 块前面有奇数个 $T$，块长度为 $l$，那么我们就可以如此转移 $dpx_{i,j}=dpx_{i-1,j+l} || dpx_{i-1,j-l}$。对于 $dpy$ 我们也可以这样转移。

最后假设目标点为 $(gx,gy)$，操作序列的长度为 $k$（压缩之后，即原序列中 $F$ 块的个数为 $k$），那么我们只需要判断 $dpx_{k,gx}\&\&dpy_{k,gy} $ 是否为 true 即可。

## 优化

$dpx,dpy$ 的第二维由于我们只记录 bool 值，所以我们可以使用 bitset 进行优化。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e5;//N作为偏移量,防止负下标 
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;
int x,y,l,cnt,w;

bitset<N*2>dpx,dpy;
string s;

int main(){
	dpx[N]=dpy[N]=1;
	cin>>s>>x>>y;
	s+="T";//处理最后一串F 
	for(int i=0;i<s.size();i++){
		if(s[i]=='T'){
			if(!cnt)x-=i;//前面没有一个T,我们就把第一个T所在的位置作为起点 
			else if(l){
				if(cnt%2)dpy=dpy<<l|dpy>>l;
				else dpx=dpx<<l|dpx>>l;
			}
			l=0;cnt++;//cnt记录前面F串的数量 
		}else l++;//l记录前面F串的长度 
	}
	
	if(dpx[N+x]&&dpy[N+y])cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}

```






---

