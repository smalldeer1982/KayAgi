# [ABC322D] Polyomino

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_d

いくつかの正方形を辺でつなげてできる、連結な多角形の形をしたパズルのピースのことを **ポリオミノ** と呼びます。

縦 $ 4 $ マス、横 $ 4 $ マスのグリッドと、グリッドに収まる大きさの $ 3 $ 個のポリオミノがあります。  
 $ i $ 番目のポリオミノの形は $ 16 $ 個の文字 $ P_{i,j,k} $ ($ 1\ \leq\ j,\ k\ \leq\ 4 $) によって表されます。$ P_{i,\ j,\ k} $ は何も置かれていないグリッドに $ i $ 番目のポリオミノを置いたときの状態を意味して、$ P_{i,\ j,\ k} $ が `#` の場合は上から $ j $ 行目、左から $ k $ 列目のマスにポリオミノが置かれていることを、`.` の場合は置かれていないことを意味します。(入出力例 $ 1 $ の図も参考にしてください。)

あなたは次の条件を全て満たすように $ 3 $ 個のポリオミノ全てをグリッドに敷き詰めることにしました。

- グリッドの全てのマスはポリオミノで覆われている。
- ポリオミノ同士が重なるように置くことはできない。
- ポリオミノがグリッドからはみ出るように置くことはできない。
- ポリオミノの平行移動と回転は自由に行うことができるが、裏返すことはできない。
 
条件を満たすようにグリッドにポリオミノを敷き詰めることは可能ですか？

## 说明/提示

### 制約

- $ P_{i,\ j,\ k} $ は `#` または `.`
- 与えられるポリオミノは連結である。つまり、ポリオミノを構成する正方形同士は、正方形のみを上下左右に辿って互いに行き来できる
- 与えられるポリオミノは空でない
 
### Sample Explanation 1

入力例 $ 1 $ に対応するポリオミノの形は次の図のようになります。 !\[image1\](https://img.atcoder.jp/abc322/f0e25c2abcdbeade76fcb12eaee39f23.jpg) この場合、次の図のようにポリオミノを配置することで、問題文の条件を満たすようにグリッドにポリオミノを敷き詰めることができます。 !\[image2\](https://img.atcoder.jp/abc322/81e983f85e958e0d612063adcc455c71.jpg) よって答えは `Yes` になります。

### Sample Explanation 2

入力例 $ 2 $ の $ 1 $ 番目のポリオミノのように、ポリオミノは穴の空いた多角形の形をしている場合があります。

### Sample Explanation 3

ポリオミノを敷き詰めるときに、ポリオミノを裏返してはならないのに注意してください。

## 样例 #1

### 输入

```
....
###.
.#..
....
....
.###
.##.
....
..#.
.##.
.##.
.##.```

### 输出

```
Yes```

## 样例 #2

### 输入

```
###.
#.#.
##..
....
....
..#.
....
....
####
##..
#...
#...```

### 输出

```
Yes```

## 样例 #3

### 输入

```
##..
#..#
####
....
....
##..
.##.
....
.#..
.#..
.#..
.#..```

### 输出

```
No```

## 样例 #4

### 输入

```
....
..#.
....
....
....
..#.
....
....
....
..#.
....
....```

### 输出

```
No```

## 样例 #5

### 输入

```
....
####
#...
#...
....
####
...#
..##
....
..##
..#.
..##```

### 输出

```
No```

## 样例 #6

### 输入

```
###.
.##.
..#.
.###
....
...#
..##
...#
....
#...
#...
#...```

### 输出

```
Yes```

# 题解

## 作者：Tang_poetry_syndrome (赞：5)

## [ABC322D] Polyomino 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc322_d) [Atcoder 题面](https://atcoder.jp/contests/abc322/tasks/abc322_d)
### 题目大意
有一个四行四列的网格，其中有三个适合于网格的多米诺骨牌。第 $i$ 个多米诺骨牌的形状由 $16$ 个字符 $P_{i,j,k}(1 \le j,k \le 4)$ 表示。它们描述了在将第 $i$ 个多米诺骨牌放置在网格上时的网格状态。如果 $P_{i,j,k}$ 是 `#`，则表示多米诺骨牌占据从上往下数第 $j$ 行、从左往右数第 $k$ 列的方格；如果是 `.`，则表示该方格未被占据。  
你想要用这三个多米诺骨牌填满网格，同时满足以下条件：
- 网格的所有方格都被多米诺骨牌覆盖。
- 多米诺骨牌之间不能重叠。
- 多米诺骨牌不能超出网格。
- 可以自由地平移和旋转多米诺骨牌，但不能翻转。

求是否可以用多米诺骨牌填满网格并满足这些条件？
### 思路
方格仅四行四列的大模拟，妥妥暴力深搜。如果多米诺骨牌的面积和为 $16$，遍历所有当前多米诺骨牌能放置的位置。如果在深搜出口判断到方格中多米诺骨牌没有重叠（即厚度为 $1$），则可以满足。  
注意，如果多米诺骨牌贴在方格边上可能超出网格，所以将方格位置设于二维数组中间，并将数组稍微开大一点。详见代码。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ll long long
const int N=1e5+10,INF=INT_MAX,Mod=998244353;
char x,mp[20][20];
bool ans=false;
int num,a[12][4][4],c[4][4];
void change(ll t){//将多米诺骨牌转向
	ll i,j;
	for(i=0;i<4;i++)for(j=0;j<4;j++)c[i][j]=a[t][j][3-i];
	for(i=0;i<4;i++)for(j=0;j<4;j++)a[t][i][j]=c[i][j];
}
void dfs(int step)
{
	if(step==3)
	{
		f(i,4,7)f(j,4,7)if(mp[i][j]!=1)return ;
		cout<<"Yes";
		exit(0);		
	}
	f(i,0,3)
	{
		f(j,1,7)f(k,1,7)
		{
			f(g,0,3)f(h,0,3)mp[j+g][k+h]+=a[step][g][h];
			dfs(step+1);
			f(g,0,3)f(h,0,3)mp[j+g][k+h]-=a[step][g][h];
		}
		change(step);
	}
		
		
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    f(i,0,2)
    	f(j,0,3)
    		f(k,0,3)
    			cin>>x,num+=a[i][j][k]=(x=='#');
    if(num==16)dfs(0);
    cout<<"No";
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc322/submissions/46122339)

---

## 作者：small_john (赞：3)

## 思路

简单~~还恶心~~的大模拟。

这道题的思路肯定是直接暴搜每个块的状态。

考虑旋转矩阵：

有一个矩阵，用二维数组存储，考虑将此矩阵顺时针旋转九十度，经过观察，新的矩阵有：$t'_{i,j}=t_{4-j-1,i}$，所以可以得到旋转的代码：

```cpp
void splay(int id)//奇怪的函数名
{
	memcpy(t,tmp[id],sizeof tmp[id]);//把原矩阵拿出来
	for(int i = 1;i<=4;i++)
		for(int j = 1;j<=4;j++)
			tmp[id][i][j] = t[4-j+1][i];//旋转
}
```

然后考虑矩阵平移。

直接枚举位移量。由于最终的块之于字符 `#` 有关，所以在开始的时候需判断每个 `#` 在移位之后是否越界，代码如下：

```cpp
bool ok(int id,int x,int y)//判断是否可行
{
	for(int i = 1;i<=4;i++)
		for(int j = 1;j<=4;j++)
			if(tmp[id][i][j]=='#'&&(i+x>4||j+y>4||i+x<=0||j+y<=0))
				return 0;
	return 1;
}
```

接下来就可以直接暴搜。枚举每个矩阵的旋转次数和位移量，并把信息存起来，最后统计出分布情况，判断是否可行。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char p[4][10][10],tmp[4][10][10],t[10][10],out[4][10][10];
int vis[10][10],t_vis[10][10],p1[4],p2[4];
void splay(int id)//奇怪的函数名
{
	memcpy(t,tmp[id],sizeof tmp[id]);//把原矩阵拿出来
	for(int i = 1;i<=4;i++)
		for(int j = 1;j<=4;j++)
			tmp[id][i][j] = t[4-j+1][i];//旋转
}
bool ok(int id,int x,int y)//判断是否可行
{
	for(int i = 1;i<=4;i++)
		for(int j = 1;j<=4;j++)
			if(tmp[id][i][j]=='#'&&(i+x>4||j+y>4||i+x<=0||j+y<=0))
				return 0;
	return 1;
}
bool ok()//冷知识：函数名一样而参数不一样是可以通过编译的
{
	for(int i = 1;i<=4;i++)
		for(int j = 1;j<=4;j++)
			if(vis[i][j]!=1)
				return 0;
	return 1;
}
void get()//求最后的分布情况
{
	memset(vis,0,sizeof vis);
	for(int x = 1;x<=3;x++)
	{
		for(int i = 1;i<=4;i++)
			for(int j = 1;j<=4;j++)
				vis[i+p1[x]][j+p2[x]]+=out[x][i][j]=='#'; 
	}
}
void dfs(int x)
{
	if(x>3)
	{
		get();
		if(ok()) puts("Yes"),exit(0);//可行
		return;
	}
	memcpy(tmp[x],p[x],sizeof p[x]);
	for(int _ = 1;_<=4;_++)//旋转次数
	{
		for(int i = -4;i<=4;i++)
			for(int j = -4;j<=4;j++)
			{
				if(ok(x,i,j))//可行
				{
					for(int X = 1;X<=4;X++)//记录信息
					{
						for(int Y = 1;Y<=4;Y++)
							out[x][X][Y] = tmp[x][X][Y];
					}
					p1[x] = i,p2[x] = j,dfs(x+1);
				}
			}
		splay(x);//旋转
	}
}
signed main()
{
	for(int i = 1;i<=3;i++)
		for(int j = 1;j<=4;j++)
			for(int k = 1;k<=4;k++)
				cin>>p[i][j][k];
	dfs(1);
	puts("No");
	return 0;
}
```

~~码风冗长，不喜勿喷。~~

---

## 作者：Genius_Star (赞：3)

### 题意：

多面体是由几个正方形的边连接而成的连边多边形拼图。


有一个四行四列的网格，网格内有三个多面体。

第 $i$ 个多角形的形状由 $16$ 个字符第 $P_{i,j,k}$ 个（第 $1 \le j,k \le 4$）表示。

它们描述了当多面体被放置在网格上时网格的状态，如果 $P_{i,j,k}$ 为 ``#``，则从上往下 $j$ 行和从左往下 $k$ 列的方格被多面体占据，如果为 ``.``，则该方格未被占据。

您希望在网格中填入所有三个多面体，以满足以下所有条件。

- 网格的所有方格都被多面体覆盖。

- 多面体不得相互重叠。

- 多面体不得伸出网格.

- 多面体可以自由平移和旋转，但不能翻转

网格中的多面体能否满足这些条件?

### 思路：

~~这次 D 题又出大模拟，真的是……~~

很明显，只是一道暴力的题目，说一下我考场思路吧。

就是将这 $3$ 个多面体的每一种状态存下来（即平移旋转后的所有可能的状态），然后三重循环暴力枚举每一种状态，判断一下这 $3$ 个状态是否满足题目要求。

重要的是如何得到每一个多面体的状态，很明显，我们可以枚举向上平移的次数，向右平移的次数，和旋转的次数 $i,j,k$。

先说一下平移，自己手推一下就可以发现，若要向上平移 $a$ 次，向右平移 $b$ 次，则第 $i$ 行第 $j$ 个应该等于第 $pd(i,a)$ 行第 $pd(i,b)$ 个。

我们定义：

$$pd(x,y)= \begin{cases} n & x+y=n\\(x+y) \bmod n& x+y \ne n \end{cases}$$

那么旋转也是一样，最好自己手推一下，得出若我们要旋转 $1$ 次，则第 $i$ 行第 $j$ 列的方格应该等于第 $j$ 行第 $n-i+1$ 列的方格。

这样可以把每一种状态给求出来，最后我们来看一下判断是否满足题目要求。

对于我们枚举的三个多面体，如果在第 $i$ 行第 $j$ 列的方格为 ``#``，那么将 $f_{i,j} \to f_{i,j}+1$，最后我们检查 $f_{i,j}$ 是否都等于 $1$ 即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=10,M=105;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n=4;
ll l[4]={0};
char s[4][N][N],p[N][M],h[N][M];
char k[4][M][N][N];
ll f[N][N];
ll pd(ll x,ll y){
	if(x+y==n)
	  return n;
	else
	  return (x+y)%n;
}
void PY(ll x,ll a,ll b){ //平移 
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
	    	ll x1=pd(i,a),x2=pd(j,b);
			p[i][j]=s[x][x1][x2];	
	    }	
	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    h[i][j]=s[x][i][j];
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    s[x][i][j]=p[i][j];
}
void XZ(ll x){ //旋转 
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    p[i][j]=s[x][j][n-i+1];
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    s[x][i][j]=p[i][j];
}
void XZ(ll x,ll k){ //旋转 k 次 
	while(k--)
	  XZ(x);
}
void HL(ll x){ //回溯 
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    s[x][i][j]=h[i][j];
}
void FZ(ll x){ //赋值状态 
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    k[x][l[x]][i][j]=s[x][i][j];
}
void init(ll x){ //暴力得出所有状态 
	for(int i=0;i<=3;i++){
		for(int j=0;j<=3;j++){
			for(int k=0;k<=3;k++){
				PY(x,i,j);
				XZ(x,k);
				++l[x];
				FZ(x);
				HL(x);
			}
		}
	}
}
bool check(ll x,ll y,ll z){ //判断枚举的三个状态是否满足 
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
		if(k[1][x][i][j]=='#')
		  f[i][j]++;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
		if(k[2][y][i][j]=='#')
		  f[i][j]++;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
		if(k[3][z][i][j]=='#')
		  f[i][j]++;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    if(f[i][j]==0||f[i][j]>1)
	      return 0;
	return 1;
}
void print(ll x,ll y){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		  putchar(k[x][y][i][j]);
		putchar('\n');
	}
	putchar('\n');
}
int main(){
	for(int i=1;i<=n;i++)
	  cin.getline(s[1][i]+1,N);
	for(int i=1;i<=n;i++)
	  cin.getline(s[2][i]+1,N);
	for(int i=1;i<=n;i++)
	  cin.getline(s[3][i]+1,N);
	init(1);
	init(2);
	init(3);
	for(int i=1;i<=l[1];i++){
		for(int j=1;j<=l[2];j++){
		    for(int k=1;k<=l[3];k++){
		    	if(check(i,j,k)){
		    		puts("Yes");
		    		exit(0);
				}
			}
		}
	}
	puts("No");
	return 0;
}
```


---

## 作者：ケロシ (赞：2)

是一个有点烦的模拟题。  
我们先考虑这三个拼图要拼起来要经过什么样的操作，  
很明显，是旋转和平移。  
直接枚举这两个条件就可以了，  
然后看能不能拼到一起。  
旋转一共有 $4$ 个方向，   
平移有左右和上下的平移，各有 $7$ 种情况。  
那么一共需要枚举 $4^3\times7^6=7529536$ 种情况，再乘以判断和旋转的 $16$ 次运算，总运算 $10^8$ 左右，可以通过。  
```cpp
const int N = 6;
int a[N][N][N], b[N][N], c[N][N];
// 旋转
void rt(int x) {
	FOR(i, 1, 4) {
		FOR(j, 1, 4) {
			b[i][j] = a[x][j][4 - i + 1];
		}
	}
	FOR(i, 1, 4) {
		FOR(j, 1, 4) {
			a[x][i][j] = b[i][j];
		}
	}
}
void solve() {
	FOR(k, 1, 3) {
		FOR(i, 1, 4) {
			string s;
			cin >> s;
			FOR(j, 1, 4) {
				a[k][i][j] = (s[j - 1] == '#');
			}
		}
	}
	REP(r1, 4) { // 枚举三个拼图的旋转情况
		rt(1);
		REP(r2, 4) {
			rt(2);
			REP(r3, 4) {
				rt(3);
				FOR(x1, -3, 3) { // 枚举三个拼图的位置
					FOR(x2, -3, 3) {
						FOR(x3, -3, 3) {
							FOR(y1, -3, 3) {
								FOR(y2, -3, 3) {
									FOR(y3, -3, 3) {
										FOR(i, 1, 4) {
											FOR(j, 1, 4) {
												c[i][j] = 0;
											}
										}
										int fl;
										fl = 1;
										FOR(i, 1, 4) {
											FOR(j, 1, 4) {
												if(!a[1][i][j]) continue;
												int px = i + x1;
												int py = j + y1;
												if(px < 1 || px > 4 || py < 1 || py > 4) {
													fl = 0;
												}
												else {
													c[px][py]++;
												}
											}
										}
										FOR(i, 1, 4) {
											FOR(j, 1, 4) {
												if(!a[2][i][j]) continue;
												int px = i + x2;
												int py = j + y2;
												if(px < 1 || px > 4 || py < 1 || py > 4) {
													fl = 0;
												}
												else {
													c[px][py]++;
												}
											}
										}
										FOR(i, 1, 4) {
											FOR(j, 1, 4) {
												if(!a[3][i][j]) continue;
												int px = i + x3;
												int py = j + y3;
												if(px < 1 || px > 4 || py < 1 || py > 4) {
													fl = 0;
												}
												else {
													c[px][py]++;
												}
											}
										}
										FOR(i, 1, 4) {
											FOR(j, 1, 4) {
												if(c[i][j] != 1) {
													fl = 0;
												}
											}
										}
										if(fl) {
											cout << "Yes" << endl;
											return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "No" << endl;
}
```

---

## 作者：CodingOIer (赞：2)

## Polyomino

### 思路分析

分为以下几个步骤：

1. 输入。
2. 对其进行分割。
3. 暴力进行旋转、平移。

得到的代码结构为：

```cpp
bool check();
void dfs(int x);
void rotate(int id);
int main();
```

对于输入，使用 `char` 的三维数组进行存储：

```cpp
for (int i = 1; i <= 3; i++)
{
    for (int j = 1; j <= n; j++)
    {
        scanf("%s", s[i][j] + 1);
    }
}
```

为了增加代码可读性，使用 `class` 进行存储，结构如下：

```cpp
class block
{
  public:
    int h, w;
    int block[MaxN][MaxN];
};
```

对于分割，我们找到高度、宽度，并将其存入 `block` 中：

```cpp
for (int id = 1; id <= 3; id++)
{
    int start_h;
    start_h = 1;
    for (; !haveH(id, start_h);)
    {
        start_h++;
    }
    int end_h;
    end_h = n;
    for (; !haveH(id, end_h);)
    {
        end_h--;
    }
    int start_w;
    start_w = 1;
    for (; !haveW(id, start_w);)
    {
        start_w++;
    }
    int end_w;
    end_w = n;
    for (; !haveW(id, end_w);)
    {
        end_w--;
    }
    p[id].h = end_h - start_h + 1;
    p[id].w = end_w - start_w + 1;
    for (int i = start_h; i <= end_h; i++)
    {
        for (int j = start_w; j <= end_w; j++)
        {
            p[id].block[i - start_h + 1][j - start_w + 1] = (s[id][i][j] == '#') ? 1 : 0;
        }
    }
}
```

这里需要 $2$ 个辅助函数：

```cpp
bool haveH(int x, int y)
{
    for (int i = 1; i <= n; i++)
    {
        if (s[x][y][i] == '#')
        {
            return true;
        }
    }
    return false;
}
bool haveW(int x, int y)
{
    for (int i = 1; i <= n; i++)
    {
        if (s[x][i][y] == '#')
        {
            return true;
        }
    }
    return false;
}
```

接着，就是令人头大的旋转操作了，大家可以在纸上模拟，可以证明 $s_{i,j}$ 将会旋转到 $s_{j,H-i+1}$ 的位置上（这个函数改了我半个小时）：

```cpp
void rotate(int id)
{
    block t;
    t.h = p[id].w;
    t.w = p[id].h;
    for (int i = 1; i <= p[id].h; i++)
    {
        for (int j = 1; j <= p[id].w; j++)
        {
            t.block[j][p[id].h - i + 1] = p[id].block[i][j];
        }
    }
    p[id] = t;
}
```

最后就是无脑深搜了：

```cpp
void dfs(int id)
{
    if (id == 4)
    {
        check();
    }
    else
    {
        for (int r = 1; r <= 4; r++)
        {
            for (int x = 0; x <= n - p[id].h; x++)
            {
                for (int y = 0; y <= n - p[id].w; y++)
                {
                    for (int i = 1; i <= p[id].h; i++)
                    {
                        for (int j = 1; j <= p[id].w; j++)
                        {
                            sum[i + x][j + y] += p[id].block[i][j];
                        }
                    }
                    dfs(id + 1);
                    for (int i = 1; i <= p[id].h; i++)
                    {
                        for (int j = 1; j <= p[id].w; j++)
                        {
                            sum[i + x][j + y] -= p[id].block[i][j];
                        }
                    }
                }
            }
            rotate(id);
        }
    }
}
```

对于答案的验证问题，我们只需要对每一个有格子的位置加上 $1$，如果有地方为 $0$，则表示没有覆盖，若超过 $1$ 则表示被重复覆盖，均不能作为答案。

下面是 `check` 函数：

```cpp
void check()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (sum[i][j] != 1)
            {
                return;
            }
        }
    }
    printf("Yes\n");
    exit(0);
}
```

注：`exit(0)` 表示结束程序并返回 `0`。

将代码组合就是如下的代码：

```cpp
#include <cstdio>
#include <cstdlib>
const int MaxN = 7;
class block
{
  public:
    int h, w;
    int block[MaxN][MaxN];
};
int n;
int sum[MaxN][MaxN];
char s[MaxN][MaxN][MaxN];
block p[5];
bool haveH(int x, int y)
{
    for (int i = 1; i <= n; i++)
    {
        if (s[x][y][i] == '#')
        {
            return true;
        }
    }
    return false;
}
bool haveW(int x, int y)
{
    for (int i = 1; i <= n; i++)
    {
        if (s[x][i][y] == '#')
        {
            return true;
        }
    }
    return false;
}
void rotate(int id)
{
    block t;
    t.h = p[id].w;
    t.w = p[id].h;
    for (int i = 1; i <= p[id].h; i++)
    {
        for (int j = 1; j <= p[id].w; j++)
        {
            t.block[j][p[id].h - i + 1] = p[id].block[i][j];
        }
    }
    p[id] = t;
}
void check()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (sum[i][j] != 1)
            {
                return;
            }
        }
    }
    printf("Yes\n");
    exit(0);
}
void dfs(int id)
{
    if (id == 4)
    {
        check();
    }
    else
    {
        for (int r = 1; r <= 4; r++)
        {
            for (int x = 0; x <= n - p[id].h; x++)
            {
                for (int y = 0; y <= n - p[id].w; y++)
                {
                    for (int i = 1; i <= p[id].h; i++)
                    {
                        for (int j = 1; j <= p[id].w; j++)
                        {
                            sum[i + x][j + y] += p[id].block[i][j];
                        }
                    }
                    dfs(id + 1);
                    for (int i = 1; i <= p[id].h; i++)
                    {
                        for (int j = 1; j <= p[id].w; j++)
                        {
                            sum[i + x][j + y] -= p[id].block[i][j];
                        }
                    }
                }
            }
            rotate(id);
        }
    }
}
int main()
{
    n = 4;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%s", s[i][j] + 1);
        }
    }
    for (int id = 1; id <= 3; id++)
    {
        int start_h;
        start_h = 1;
        for (; !haveH(id, start_h);)
        {
            start_h++;
        }
        int end_h;
        end_h = n;
        for (; !haveH(id, end_h);)
        {
            end_h--;
        }
        int start_w;
        start_w = 1;
        for (; !haveW(id, start_w);)
        {
            start_w++;
        }
        int end_w;
        end_w = n;
        for (; !haveW(id, end_w);)
        {
            end_w--;
        }
        p[id].h = end_h - start_h + 1;
        p[id].w = end_w - start_w + 1;
        for (int i = start_h; i <= end_h; i++)
        {
            for (int j = start_w; j <= end_w; j++)
            {
                p[id].block[i - start_h + 1][j - start_w + 1] = (s[id][i][j] == '#') ? 1 : 0;
            }
        }
    }
    dfs(1);
    printf("No\n");
    return 0;
}
```

---

## 作者：Miss_SGT (赞：2)

考场看见这题，发现是大模拟便跳过了，其实有一种比较简单的方法。

方格只有 $16$ 个，考虑状态压缩。只需要枚举出 $3$ 个卡牌的所有状态。任意三个状态，两两与起来为 $0$，代表没有重叠。三个或起来为 $2^{16} - 1$ 代表全部填满。两种都满足时，就可以输出了。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while((c<'0'||'9'<c)&&c^'-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	x*=f;
}
char s[3][5][5];
int z[3][100],cnt[3];
inline bool q_bit(int x,int y,int z){return (z>>((x-1)*4+y-1))&1;}
inline int g_bit(int x,int y){return 1<<((x-1)*4+y-1);}
inline int fan(int x){
	int ans=0;
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
		if(q_bit(i,j,x)) ans+=g_bit(j,5-i);
	return ans;
}
inline bool Ok(int x,int y){return 0<x&&x<=4&&0<y&&y<=4;}
void print(int x){
	for(int i=1;i<=4;i++,cout<<'\n')
	for(int j=1;j<=4;j++)
		cout<<q_bit(i,j,x);
}
inline void find(int k){
	bool ok;int h;
	for(int x=-3;x<=3;x++)
	for(int y=-3;y<=3;y++){
		ok=1;h=0;
		for(int i=1;i<=4&&ok;i++)
		for(int j=1;j<=4&&ok;j++)
			if(s[k][i][j]=='#'&&!Ok(i+x,j+y)) ok=0;
			else if(s[k][i][j]=='#') h+=g_bit(i+x,j+y);
		if(!ok) continue;
		for(int f=0;f<4;f++){
			z[k][++cnt[k]]=h;
			h=fan(h);
		}
	}
}
int main(){
	for(int i=0;i<3;i++)
	for(int j=1;j<=4;j++)
		scanf("%s",s[i][j]+1);
	for(int i=0;i<3;i++) find(i);
	for(int i=1;i<=cnt[0];i++)
	for(int j=1;j<=cnt[1];j++)
	for(int k=1;k<=cnt[2];k++){
		if(!(z[0][i]&z[1][j])&&!(z[1][j]&z[2][k])&&!(z[0][i]&z[2][k])&&
			((z[0][i]|z[1][j]|z[2][k])==(1<<16)-1)){
			puts("Yes");
			return 0;	
		}
	}
	puts("No");
	return 0;
}

```


---

## 作者：heyx0201 (赞：1)

# Polyomino 题解
## Meaning
> 给定三个字符矩阵，求它们能不能拼在一起变成一个 $4 \times 4$ 的全部是 `#` 的矩阵。

## Solution
大模拟。说简单也不简单，很复杂；但是说难呢，又不难。

思路：搜索每一个矩阵的状态。

### 0x001 旋转矩阵
一个字符矩阵，考虑顺时针旋转 $90$ 度，推出来得到：
$$
t_{i,j} = s_{4 - j + 1,i}
$$

所以得到了代码：
```cpp
// 旋转矩阵
void swp(int index){
  for (int i = 1; i <= 4; i++){
    for (int j = 1; j <= 4; j++){
      sp[index][4 - j + 1][i] = s[i][j];
    }
  }
}
```
---
### 0x002 平移矩阵
枚举偏移量，然后暴力判断是否可以偏移。

代码：
```cpp
// 平移矩阵
bool py(int index,int x,int y){
  for (int i = 1; i <= 4; i++){
    for (int j = 1; j <= 4; j++){
      if (sp[index][i][j] == '#' && (x + i > 4 || y > j > 4 || x + i < 1 || y + j < 1)){
        return false;
      }
    }
  }
  return true;
}
    
```
---
弄完上面两个东西之后，就可以开始暴力 dfs，枚举旋转次数和偏移量，存起来，判断是否合法即可。
### 0x003 Accept Code
[Accept Record](https://www.luogu.com.cn/record/127362100)
```cpp
#include <bits/stdc++.h>

using namespace std;

char s[4][5][5], sp[4][5][5], pt[4][5][5], t[5][5];
int vis[5][5], t1[4], t2[4];

// 旋转矩阵
void swp(int index) {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      t[i][j] = sp[index][i][j];
    }
  }
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      sp[index][i][j] = t[4 - j + 1][i];
    }
  }
}

// 平移矩阵
bool py(int index, int x, int y) {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (sp[index][i][j] == '#' &&
          (x + i > 4 || y + j > 4 || x + i < 1 || y + j < 1)) {
        return false;
      }
    }
  }
  return true;
}

// 检查矩阵
bool check() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (vis[i][j] != 1) {
        return false;
      }
    }
  }
  return true;
}

// 求最后的分布情况
void ok() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      vis[i][j] = 0;
    }
  }
  for (int id = 1; id <= 3; id++) {
    for (int x = 1; x <= 4; x++) {
      for (int y = 1; y <= 4; y++) {
        vis[x + t1[id]][y + t2[id]] += pt[id][x][y] == '#';
      }
    }
  }
}

// dfs 搜索
void dfs(int x) {
  if (x > 3) {
    ok();
    if (check()) {
      cout << "Yes";
      exit(0);
    }
    return;
  }
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      sp[x][i][j] = s[x][i][j];
    }
  }
  for (int scnt = 1; scnt <= 4; scnt++) {       // 枚举旋转次数
    for (int pyl1 = -4; pyl1 <= 4; pyl1++) {    // 行偏移量
      for (int pyl2 = -4; pyl2 <= 4; pyl2++) {  // 列偏移量
        if (py(x, pyl1, pyl2)) {
          for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
              pt[x][i][j] = sp[x][i][j];
            }
          }
          t1[x] = pyl1, t2[x] = pyl2;
          dfs(x + 1);
        }
      }
    }
    swp(x);
  }
}

int main() {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 4; j++) {
      for (int k = 1; k <= 4; k++) {
        cin >> s[i][j][k];
      }
    }
  }
  dfs(1);
  cout << "No";
  return 0;
}
```


---

## 作者：yszkddzyh (赞：1)

~~这题过于恶心~~，建议评黄！

大家用的都是搜索，我来用一个暴力枚举吧。

这一题的关键是旋转，具体怎么办呢？

读入数组以后，我们先预处理一下，把每个图形移到最左上角，举个例子，我们把下面的图甲：

###### 图甲：

```
....
....
..#.
.##.
```

处理成下面的图乙：

###### 图乙：

```
.#..
##..
....
....
```

这样在后面处理图形的旋转时，会方便一点（~~可能吧~~），但具体要怎么办呢？对于每个图形，我们要找到“最左上角”的点（可能表述得不太严谨），并将它移到 $(1,1)$ 处，比如我们在上面的图甲中找到“最左上角”的点 $(3,2)$，将它平移到 $(1,1)$，并将其它点同样按照此规则平移，即可完成此操作。但“最左上角”的点如何找呢？注意到所有 `#` 字符所在行的编号的最小值即为“最左上角”的点的行号，同样地，所有 `#` 字符所在列的编号的最小值即为“最左上角”的点的列号。在图甲中，三个 `#` 的坐标分别是 $(3,3),(4,2),(4,3)$，则“最左上角”的点的坐标就是 $(3,2)$，其中，$3$ 是 $\{3,4,4\}$ 中的最小值，$2$ 是 $\{3,2,3\}$ 中的最小值。

同时，我们还要求出每个图形经过上述处理后的长和宽，比如上面的图乙中，图形的长为 $2$，宽也为 $2$。这个又怎么求呢？举个例子你就懂了。图乙中，每个 `#` 的坐标分别是 $(1,2),(2,1),(2,2)$，图形的长为 $2$，其实就是横坐标 $\{1,2,2\}$ 的最大值，纵坐标同理。

~~好了，以上都是预处理。~~

然后就是暴力枚举了，具体地，我们分别枚举 $3$ 个图形的左上角的点以及每个图形的方向，然后检查一下是否合理即可。反正数据范围挺小，不管怎么瞎搞都可以，这题主要就是考验码力。

表述的不太清楚，看代码吧！

```cpp
//赛时代码，有点混乱，但注释很清晰

#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int N = 6;
struct crood{
	int x, y, n, m;
    crood(): x(inf), y(inf){}
}fa[4];
//x,y记录“最左上角”的点的坐标
//n,m记录处理后的图形的长、宽
int a[4][N][N], b[4][N][N], cnt[10][10];
//a是原数组，b是将图形移动至左上角后的图形
//cnt记录每个点覆盖的次数，用于判断摆放方法是否合理
//cnt开成10*10的，是为了防止图形越界

void Rotate(int id){//将图形逆时针旋转90度
	int tmp[N][N];
	for(int i = 1; i <= fa[id].m; i++)
		for(int j = 1; j <= fa[id].n; j++)
			tmp[i][j] = b[id][j][fa[id].m - i + 1];
	for(int i = 1; i <= fa[id].m; i++)
		for(int j = 1; j <= fa[id].n; j++)
			b[id][i][j] = tmp[i][j];
	swap(fa[id].n, fa[id].m);//注意长和宽要交换
	return;
}
//work函数表示将图形“铺”在4*4的图上
//id 记录第几个图形，x,y记录“最左上角”点摆在哪
//d记录方向
void work(int id, int x, int y, int d){
	for(int i = 1; i < d; i++)
		Rotate(id);//旋转d次
	for(int i = 1; i <= fa[id].n; i++)
		for(int j = 1; j <= fa[id].m; j++)
			cnt[i + x - 1][j + y - 1] += b[id][i][j];
            //如果此处是 #，将计数数组加1
	return;
}
//del函数表示撤销上一次“铺”的操作
//参数的含义同上
//不需要记录方向，因为上一个work中已经旋转过了
void del(int id, int x, int y){
	for(int i = 1; i <= fa[id].n; i++)
		for(int j = 1; j <= fa[id].m; j++)
			cnt[i + x - 1][j + y - 1] -= b[id][i][j];
	return;
}

int main(){
	
	char c;
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 4; j++)
			for(int k = 1; k <= 4; k++)
				cin >> c, a[i][j][k] = (c == '#' ? 1 : 0);
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 4; j++)
			for(int k = 1; k <= 4; k++)
				if(a[i][j][k])//如果是 #，记录最小值
					fa[i].x = min(fa[i].x, j),
					fa[i].y = min(fa[i].y, k);
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 4; j++)
			for(int k = 1; k <= 4; k++)
				if(a[i][j][k])//如果是 #，记录最大值
					fa[i].n = max(fa[i].n, j - fa[i].x + 1),
					fa[i].m = max(fa[i].m, k - fa[i].y + 1);
                    //横纵坐标要减去“最左上角”点的横纵坐标，请思考原因
	for(int i = 1; i <= 3; i++)
		for(int j1 = 1, j2 = fa[i].x; j1 <= fa[i].n; j1++, j2++)
			for(int k1 = 1, k2 = fa[i].y; k1 <= fa[i].m; k1++, k2++)
				b[i][j1][k1] = a[i][j2][k2];
                //将图形平移，b记录平移后的每个图形
	for(int i1 = 1; i1 <= 4; i1++)
		for(int j1 = 1; j1 <= 4; j1++)
			for(int d1 = 1; d1 <= 4; d1++){
				work(1, i1, j1, d1);
				for(int i2 = 1; i2 <= 4; i2++)
					for(int j2 = 1; j2 <= 4; j2++)
						for(int d2 = 1; d2 <= 4; d2++){
							work(2, i2, j2, d2);
							for(int i3 = 1; i3 <= 4; i3++)
								for(int j3 = 1; j3 <= 4; j3++)
									for(int d3 = 1; d3 <= 4; d3++){
										work(3, i3, j3, d3);
										for(int i = 1; i <= 4; i++)
											for(int j = 1; j <= 4; j++)
												if(cnt[i][j] != 1) goto FLAG;//还有地方没铺，不合法
										for(int i = 1; i <= 10; i++)
											for(int j = 1; j <= 10; j++)
												if((i > 4 || j > 4) && cnt[i][j]) goto FLAG;//图形越界，不合法
                                                //图形只会出右边和下边的界，请思考原因
										cout << "Yes\n";
										goto FLAG2;
										FLAG:
										del(3, i3, j3);
									}
							del(2, i2, j2);
						}
				del(1, i1, j1);
			}
	cout << "No\n";
	FLAG2:
	
	return 0;
}

/* MADE IN CHINA */
```

还是建议自行码代码，真不懂我的思路和代码也不要紧，这种题的做法一般都很多。

---

## 作者：linxuanrui (赞：0)

### 思路

把每种多米诺骨牌的所有状态都预处理出来。

最后枚举所有状态，检查是否能拼成一个完整的棋盘。

难点就在于预处理多米诺骨牌的所有状态。

我们可以枚举向每个方向平移的次数，和旋转的度数。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;
char ch[10][10][10],tmp[5][64][5][5],ans[10][10];
int cnt[5],sum;
void turn(int pos){
	++cnt[pos];
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)tmp[pos][cnt[pos]][i][j] = '.';
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)tmp[pos][cnt[pos]][j][4 + 1 - i] = ch[pos][i][j];
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)ch[pos][i][j] = tmp[pos][cnt[pos]][i][j];
	}
}
bool move1(int pos,int num){
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)tmp[0][0][i][j] = '.';
	}
	for(int i = 1 + num;i <= 4 + num;i++){
		for(int j = 1;j <= 4;j++){
			if(ch[pos][i - num][j] == '#'){
				if(i > 4 || j > 4 || i < 1 || j < 1)return false;
				tmp[0][0][i][j] = ch[pos][i - num][j];
			}
		}
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)ch[pos][i][j] = tmp[0][0][i][j];
	}
	return true;
}
bool move2(int pos,int num){
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)tmp[0][0][i][j] = '.';
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1 + num;j <= 4 + num;j++){
			if(ch[pos][i][j - num] == '#'){
				if(i > 4 || j > 4 || i < 1 || j < 1)return false;
				tmp[0][0][i][j] = ch[pos][i][j - num];
			}
		}
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)ch[pos][i][j] = tmp[0][0][i][j];
	}
	return true;
}
bool check(int X,int Y,int Z){
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++)ans[i][j] = '.';
	}
	for(int j = 1;j <= 4;j++){
		for(int k = 1;k <= 4;k++){
			if(tmp[1][X][j][k] == '#' || tmp[2][Y][j][k] == '#' || tmp[3][Z][j][k] == '#')ans[j][k] = '#';
		}
	}
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= 4;j++){
			if(ans[i][j] != '#')return false;
		}
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i = 1;i <= 3;i++){
		for(int j = 1;j <= 4;j++){
			for(int k = 1;k <= 4;k++)cin >> ch[i][j][k],sum += (ch[i][j][k] == '#');
		}
	}
	if(sum != 16)return cout << "No",0;
	for(int i = 1;i <= 3;i++){
		for(int j = -3;j <= 3;j++){
			if(!move1(i,j))continue;;
			for(int k = -3;k <= 3;k++){
				if(!move2(i,k))continue;;
				for(int l = 0;l <= 3;l++){
					turn(i);
				}
				move2(i,-k);
			}
			move1(i,-j);
		}
	}
	for(int i = 1;i <= cnt[1];i++){
		for(int j = 1;j <= cnt[2];j++){
			for(int k = 1;k <= cnt[3];k++){
				if(check(i,j,k))return cout << "Yes",0;
			}
		}
	}
	cout << "No";
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc322_d)


#### 思路

暴力枚举图形的每个状态也就是旋转操作，所在的位置，直接枚举图形的左端点就行了，然后暴力看它们是否满足题目给出的条件（不能重叠，且可以全部覆盖）就可以了，考虑到字符会对后面处理有影响，于是可以提前预处理成 $01$，方便模拟。


**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10][10],o[10],b[10][10],o1[10],o2[10],c[10][10],c11[10][10],v[10][10],ll;
char w;
void check(int a1,int b1,int c1,int d1,int e)//检查是否匹配 
{
	for(int k = a1;k <= b1;k++)
		for(int z = c1;z <= d1;z++)
		{
			if((a[o[1] + k - a1][o[2] + z - c1] == 1 && e == 1) || (b[o1[1] + k - a1][o1[2] + z - c1] == 1 && e == 2)
			|| (c[o2[1] + k - a1][o2[2] + z - c1] == 1 && e == 3))
			{
				if(!v[k][z]) v[k][z] = 1;
				else 
				{
					ll = 1;
					k = z = 9;
					return;
				}
			}
		}
} 
bool dfs(int x,int y,int zz,int kk)
{
	for(int xt = 1;xt <= 4;xt++)//状态 
	{
	for(int i = 1;i <= 4;i++)
		for(int j = 1;j <= 4;j++)//枚举左端点 
		{
			if(j + o2[4] - o2[2] > 4 || i + o2[3] - o2[1] > 4) continue;
			ll = 0;
			for(int k = 1;k <= 4;k++)
				for(int z = 1;z <= 4;z++)
					v[k][z] = 0;
			check(x,x + o[3] - o[1],y,y + o[4] - o[2],1);
			if(!ll) check(zz,zz + o1[3] - o1[1],kk,kk + o1[4] - o1[2],2);
			if(!ll) check(i,i + o2[3] - o2[1],j,j + o2[4] - o2[2],3);
			for(int k = 1;k <= 4;k++)
					for(int z = 1;z <= 4;z++)
						if(!v[k][z])
						{
							ll = 1;
							k = z = 9;
						}
			if(!ll) return 1;
		}
		for(int k = 1;k <= 4;k++)
				for(int z = 1;z <= 4;z++) 
					c11[k][z] = c[z][4 - k + 1];
			for(int k = 1;k <= 4;k++)
				for(int z = 1;z <= 4;z++) 
					c[k][z] = c11[k][z];
			o2[1] = o2[2] = 2e9; o2[3] = o2[4] = -1e9;	
						for(int i = 1;i <= 4;i++)
							for(int j = 1;j <= 4;j++) if(c[i][j] == 1)o2[1] = min(o2[1],i),o2[2] = min(o2[2],j),o2[3] = max(o2[3],i),o2[4] = max(o2[4],j);
	}
	return 0;
}
int main()
{
	o[1] = o[2] = o1[1] = o1[2] = o2[1] = o2[2] = INT_MAX;
	for(int i = 1;i <= 4;i++)//预处理 
		for(int j = 1;j <= 4;j++)
		{
			cin >> w;
			if(w == '.') a[i][j] = 0;
			else a[i][j] = 1,o[1] = min(o[1],i),o[2] = min(o[2],j),o[3] = max(o[3],i),o[4] = max(o[4],j);
		}
	for(int i = 1;i <= 4;i++)//同上 
		for(int j = 1;j <= 4;j++)
		{
			cin >> w;
			if(w == '.') b[i][j] = 0;
			else b[i][j] = 1,o1[1] = min(o1[1],i),o1[2] = min(o1[2],j),o1[3] = max(o1[3],i),o1[4] = max(o1[4],j);
		}
	for(int i = 1;i <= 4;i++)//同上
		for(int j = 1;j <= 4;j++)
		{
			cin >> w;
			if(w == '.') c[i][j] = 0;
			else c[i][j] = 1,o2[1] = min(o2[1],i),o2[2] = min(o2[2],j),o2[3] = max(o2[3],i),o2[4] = max(o2[4],j);
		}
		for(int xt1 = 1;xt1 <= 4;xt1++)//状态 
		{
			for(int i = 1;i <= 4;i++)
				for(int j = 1;j <= 4;j++)//枚举左端点 
				{
					if(j + o[4] - o[2] > 4 || i + o[3] - o[1] > 4) continue;
					for(int xt = 1;xt <= 4;xt++)
					{
						for(int k = 1;k <= 4;k++)//一样 
							for(int z = 1;z <= 4;z++)
							{
								if(z + o1[4] - o1[2] > 4 || k + o1[3] - o1[1] > 4) continue;
								if(dfs(i,j,k,z))
								{
									cout << "Yes";
									exit(0);
								} 
							}
						for(int k = 1;k <= 4;k++)//翻转 
							for(int z = 1;z <= 4;z++) 
								c11[k][z] = b[z][4 - k + 1];
						for(int k = 1;k <= 4;k++)
							for(int z = 1;z <= 4;z++) 
								b[k][z] = c11[k][z];
							o1[1] = o1[2] = 2e9; o1[3] = o1[4] = -1e9;//重新找端点	
						for(int i = 1;i <= 4;i++)
							for(int j = 1;j <= 4;j++) if(b[i][j] == 1) o1[1] = min(o1[1],i),o1[2] = min(o1[2],j),o1[3] = max(o1[3],i),o1[4] = max(o1[4],j);
					} 
				}
			for(int k = 1;k <= 4;k++)//旋转 
				for(int z = 1;z <= 4;z++) 
					c11[k][z] = a[z][4 - k + 1];
			for(int k = 1;k <= 4;k++)
				for(int z = 1;z <= 4;z++) 
					a[k][z] = c11[k][z];
					for(int i = 1;i <= 4;i++)
			for(int i = 1;i <= 4;i++)
			o[1] = o[2] = 2e9; o[3] = o[4] = -1e9;
			for(int i = 1;i <= 4;i++)
				for(int j = 1;j <= 4;j++) if(a[i][j] == 1) o[1] = min(o[1],i),o[2] = min(o[2],j),o[3] = max(o[3],i),o[4] = max(o[4],j);
		}
	cout << "No";
	return 0;
}
```


---

## 作者：fcy20180201 (赞：0)

## 题意
给你三个 $4 \times 4$ 的方格图，每个方格图上都有一些格子涂了色，一些格子没有（用 ```#``` 和 ```.``` 表示）。现在要将三张方格图中的涂色部分正好拼成一个 $4 \times 4$ 的全涂色方格图（每张方格纸都能随意**平移、旋转**，但**不能翻转**），问是否能办到。

## 思路
看到数据这么小，首先就能想到暴搜。

首先判断总涂色个数是否等于 $16$，如果不是就直接输出 ```No```。

接着在三张方格纸上各指定一个涂色的格子，再分别枚举这三个指定格子拼好后的位置和三张方格纸围绕指定格子旋转 $90\degree$ 的次数。

判断不可行的依据是是否有格子出界，以及有没有格子与其他格子重合（可以用 ```vis``` 数组实现）。

最坏情况下计算次数约等于 $4^9$，再加上剪枝，稳稳地过。

### 坑点
```vis``` 数组每一种情况讨论完后都要**清空**。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char p1[5][5],p2[5][5],p3[5][5];
int cnt1,cnt2,cnt3,cnt4;
bool vis[5][5];
struct node{
	int x,y;
}p1l,p2l,p3l,loc1[18],loc2[18],loc3[18];

node to(node &itl,int &curx,int &cury,int &t,node &cur){//计算每个格子旋转后的位置（手捏几个数据就能看出来了）
	if(t==0)return (node){curx+(cur.x-itl.x),cury+(cur.y-itl.y)};
	if(t==1)return (node){curx+(cur.y-itl.y),cury-(cur.x-itl.x)};
	if(t==2)return (node){curx-(cur.x-itl.x),cury-(cur.y-itl.y)};
	if(t==3)return (node){curx-(cur.y-itl.y),cury+(cur.x-itl.x)};	
}

bool otb(node &cur){//判断是否出界
	return !(cur.x>=0 && cur.x<4 && cur.y>=0 && cur.y<4);
}

int main(){
	for(int i=0;i<4;i++)scanf("%s",p1[i]);
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)if(p1[i][j]=='#'){
		if(!cnt1)p1l={i,j};//指定格子
		loc1[cnt1++]={i,j};//记录每个涂色格子的位置
	}
	for(int i=0;i<4;i++)scanf("%s",p2[i]);
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)if(p2[i][j]=='#'){
		if(!cnt2)p2l={i,j};
		loc2[cnt2++]={i,j};
	}
	for(int i=0;i<4;i++)scanf("%s",p3[i]);
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)if(p3[i][j]=='#'){
		if(!cnt3)p3l={i,j};
		loc3[cnt3++]={i,j};
	}
	if(cnt1+cnt2+cnt3!=16){//判断涂色格子个数
		puts("No");
		return 0;
	}
	bool flag=true;
	for(int a=0;a<4;a++)for(int b=0;b<4;b++)for(int t1=0;t1<4;t1++){
		bool flag1=true;
		for(int i=0;i<cnt1;i++){
			node loc=to(p1l,a,b,t1,loc1[i]);
			if(otb(loc)){flag1=false;break;}
		}
		if(!flag1)continue;//若不符合，直接枚举下一种情况
		for(int i=0;i<cnt1;i++){
			node loc=to(p1l,a,b,t1,loc1[i]);
			vis[loc.x][loc.y]=true;//标记被取过的格子
		}
		for(int c=0;c<4;c++)for(int d=0;d<4;d++)for(int t2=0;t2<4;t2++){
			bool flag2=true;
			for(int i=0;i<cnt2;i++){
				node loc=to(p2l,c,d,t2,loc2[i]);
				if(otb(loc)){flag2=false;break;}
				if(vis[loc.x][loc.y]){flag2=false;break;}
				
			}
			if(!flag2)continue;
			for(int i=0;i<cnt2;i++){
				node loc=to(p2l,c,d,t2,loc2[i]);
				vis[loc.x][loc.y]=true;
			}
			for(int e=0;e<4;e++)for(int f=0;f<4;f++)for(int t3=0;t3<4;t3++){
				bool flag3=true;
				for(int i=0;i<cnt3;i++){
					node loc=to(p3l,e,f,t3,loc3[i]);
					if(otb(loc)){flag3=false;break;}
					if(vis[loc.x][loc.y]){flag3=false;break;}
				}
				if(flag3){flag2=false;break;}//如果找到合法的，直接结束枚举。
			}
			for(int i=0;i<cnt2;i++){
				node loc=to(p2l,c,d,t2,loc2[i]);
				vis[loc.x][loc.y]=false;
			}
			if(!flag2){flag1=false;break;}
		}
		for(int i=0;i<cnt1;i++){
			node loc=to(p1l,a,b,t1,loc1[i]);
			vis[loc.x][loc.y]=false;
		}	
		if(!flag1){flag=false;break;}
	}
	if(flag)puts("No");
	else puts("Yes");
	return 0;
}
```

**注：本蒟蒻的做法很烦，望各位大神指教！！！**

---

