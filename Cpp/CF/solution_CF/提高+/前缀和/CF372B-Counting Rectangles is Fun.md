# Counting Rectangles is Fun

## 题目描述

给定一个${n * m}$的01矩阵, q次询问, 每次询问指定一个子矩形, 求该子矩形种有多少个只包含0的子矩阵.

矩阵从上到下编号1~n, 从左到右编号1~m.

## 样例 #1

### 输入

```
5 5 5
00101
00000
00001
01000
00001
1 2 2 4
4 5 4 5
1 2 5 2
2 2 4 5
4 2 5 3
```

### 输出

```
10
1
7
34
5
```

## 样例 #2

### 输入

```
4 7 5
0000100
0000010
0011000
0000000
1 7 2 7
3 1 3 1
2 3 4 5
1 2 2 7
2 2 4 7
```

### 输出

```
3
1
16
27
52
```

# 题解

## 作者：Develop (赞：9)

这是一个对前缀和的妙用的题目

首先我们可以用二维前缀和预处理出所有的(单独一个的)子矩阵是否全$0$

我们把它存到$qzh[i][j]$数组中(它存的只是前缀和)

那么现在我们再开一个$Q[i][j][i_1][j_1]$表示母矩阵左上方的端点为$(i,j)$，右下方的端点为$(i_1,j_1)$的全$0$子矩阵的个数

首先我们可以用$O(n^4)$的时间枚举左上端点和右下端点，将左上为$(i,j)$，右下为$(i_1,j_1)$的全$0$矩阵(不是子矩阵)预处理一下，即$Q[i][j][i_1][j_1]=1;$

那么我们现在就是要利用前缀和对这个四维数组计算答案进行优化
![](https://cdn.luogu.com.cn/upload/image_hosting/gol75ood.png)

我们发现，对于一般的**二维**前缀和，$Q[i][j]$的答案要被累加进$Q[i_1][j_1]$，当且仅当$i<=i_1,j<=j_1$，我们将这种关系称之为偏序，这是一个二维偏序；即一个点有贡献，那他对横纵坐标大于它的所有点，都有贡献；一句话，如果这个矩阵往两个方向扩展，那他要加的贡献就需要往另外两个方向；在图中就是说要我们计算红的区域的和，但我们要更新的是所有黄色区域的前缀和数组。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dlp0237.png)

那么我们再来看这幅图：当$Q[a][b][c][d]$需要累加进$Q[x_1][y_1][x_4][y_4]$，当且仅当${a>=x_1,b>=y_1,c<=x_4,d<=y_4}$；那么这里的偏序关系是含大于号的，怎么办？

其实我们在计算普通前缀和的时候是把$i,j$从小往大枚举，它对应着带小于号的偏序，所以这里的$a,b$就从大往小枚举。

显然一种计算前缀和的方法是容斥。但还有一种更加简单计算高维前缀和的方法。
![](https://cdn.luogu.com.cn/upload/image_hosting/5rfnq6md.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/rrn0t832.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/bsde4n00.png)

这样，按照上上上图中**黄色**区域的扩展方向将前缀和每次单独扩展一个方向，有几维，就扩展几次。

所以这就是一个需要计算四维前缀和的题目。

```cpp
#include <bits/stdc++.h>
#include <algorithm>
#define Freopen(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define ll long long
using namespace std;
void solve();
int n,m,q;
char s[50];
int qzh[50][50];
int Q[50][50][50][50];
int main()
{
	//Freopen() 
	scanf("%d%d%d\n",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		for(int j=1;j<=m;j++)
			qzh[i][j]=s[j-1]-'0',
			qzh[i][j]+=qzh[i-1][j]+qzh[i][j-1]-qzh[i-1][j-1];
	}	
	solve();
	return 0;
}
void solve()
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int i1=i;i1<=n;i1++)
	for(int j1=j;j1<=m;j1++)
		if(qzh[i1][j1]-qzh[i-1][j1]-qzh[i1][j-1]+qzh[i-1][j-1]==0)
			Q[i][j][i1][j1]++;//记录的左上和右下 
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			for(int i1=1;i1<=n;i1++)
				for(int j1=1;j1<=m;j1++)	
					Q[i][j][i1][j1]+=Q[i+1][j][i1][j1];
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			for(int i1=1;i1<=n;i1++)
				for(int j1=1;j1<=m;j1++)	
					Q[i][j][i1][j1]+=Q[i][j+1][i1][j1];
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			for(int i1=1;i1<=n;i1++)
				for(int j1=1;j1<=m;j1++)	
					Q[i][j][i1][j1]+=Q[i][j][i1-1][j1];
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			for(int i1=1;i1<=n;i1++)
				for(int j1=1;j1<=m;j1++)	
					Q[i][j][i1][j1]+=Q[i][j][i1][j1-1];
	while(q--)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",Q[a][b][c][d]);
	}
	return;
}

```
具体实现的方法在代码里。

---

## 作者：wrpwrp (赞：5)

```cpp
题目大意:
	给定一个n*m的01矩阵，q次询问，每次询问一个矩形，求该
	矩形中有对少个只包含0的的子矩形
数据范围：
	n,m<=40
	q<=3e5
解题思路:
	这可能是我见过最水的紫题了。。。
	设f[a][b][c][d]为以左上角(a,b)为定点，右下角在(c,d)以内的所有矩形，那么显然会有：
	f[a][b][c][d]=f[a][b][c-1][d]+f[a][b][c][d-1]-f[a][b][c-1][d-1]+ok[a][b][c][d]
	查询的时候直接枚举所有的c，d一起就行了
	很容易就可以达到（n^4+n^2*q）就过了？？？？
	但是这题有一个很简单的优化诶....
	一开始我们左上右下都是定的可以使用前缀和，优化以后定左上角，右下角，不定，那么左上角可以不定吗？
	显然可以。
	设dp[a][b][c][d]为（a,b)(c,d)的答案
	那么有
	dp[a][b][c][d]=dp[a+1][b][c][d]+dp[a][b+1][c][d]-dp[a+1][b+1][c][d]+f[a][b][c][d];
	于是就是(n^4+q)的了
	
```
```cpp
#include <iostream>
using namespace std;

#define R register
const int MAXN=40+5;

int f[MAXN][MAXN][MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];
int sum[MAXN][MAXN];
int n,m,q;

inline bool chk(int a,int b,int c,int d)
{
	return sum[c][d]-sum[c][b-1]-sum[a-1][d]+sum[a-1][b-1]==0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(R int i=1;i<=n;i++)
		for(R int j=1;j<=m;j++)
		{
			char a;cin>>a;
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(a=='1');
		}
	for(R int a=1;a<=n;a++)
		for(R int b=1;b<=m;b++)
			for(R int c=a;c<=n;c++)
				for(R int d=b;d<=m;d++)
					f[a][b][c][d]=f[a][b][c-1][d]+f[a][b][c][d-1]-f[a][b][c-1][d-1]+chk(a,b,c,d);
	for(R int a=n;a>=1;a--)
		for(R int b=m;b>=1;b--)
			for(R int c=n;c>=a;c--)
				for(R int d=m;d>=b;d--)
					dp[a][b][c][d]=dp[a+1][b][c][d]+dp[a][b+1][c][d]-dp[a+1][b+1][c][d]+f[a][b][c][d];
	for(R int i=1;i<=q;i++)
	{
		int a,b,c,d;cin>>a>>b>>c>>d;
		/*int ans=0;
		for(R int j=a;j<=c;j++)
			for(R int k=b;k<=d;k++)
				ans+=f[j][k][c][d];*/
		printf("%d\n",dp[a][b][c][d]);
	}
	return 0;
}
```


---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
给定一个 ${n * m}$ 的 $0/1$ 矩阵, $q$ 次询问, 每次询问指定一个子矩形, 求该子矩形种有多少个只包含 $0$ 的子矩阵。  
$n,m\le40,q\le3\times 10^5$
## $\text{Solution}$
小清新水紫。  
似乎已经把 $O(nmq)$ 的复杂度写在数据范围上了...  
考虑枚举这个矩形的长和宽，那么剩下的就只能 $O(1)$ 查询。  
不难想到**前缀和**。  
定义一个矩阵的坐标为**右下点的坐标**。  
按照这个坐标的定义对于每个长和宽 $(a,b)$ 都  预处理出矩形个数的前缀和，复杂度 $O(n^2m^2)$。  
那么我们如果在 $(x1,y1,x2,y2)$ 的矩形中询问大小为 $a\times b$ 的矩形，就相当于查询坐标在 $(x1+a-1,y1+b-1,x2,y2)$ 这个矩形内的 $a\times b$ 的矩形的总个数。  
总时间复杂度 $O(n^2m^2+qnm)$。  

PS：本题由于那个四维前缀和数组跨度太大，请务必**把记录长宽的两维开在后面！**这样在回答询问的时候始终是连续访问，否则会由于过多的 cache miss 而超时...（至少对于我的垃圾码是这样）改完后跑的飞快毫无压力。

后来看题解似乎有 $O(n^2m^2)-O(1)$ 的神奇偏序前缀和魔法操作，也很妙。  

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e6+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,q;
int sum[50][50],num[50][50][50][50];
inline int Sum(int x1,int y1,int x2,int y2){
  return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
/*inline int Num(int a,int b,int x1,int y1,int x2,int y2){
  return num[a][b][x2][y2]-num[a][b][x1-1][y2]-num[a][b][x2][y1-1]+num[a][b][x1-1][y1-1];
}*/
#define Num(a,b,x1,y1,x2,y2) num[x2][y2][a][b]-num[x1-1][y2][a][b]-num[x2][y1-1][a][b]+num[x1-1][y1-1][a][b]
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();q=read();
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) scanf("%1d",&sum[i][j]);
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
  }
  for(int a=1;a<=n;a++){
    for(int b=1;b<=m;b++){
      for(int i=a;i<=n;i++){
	for(int j=b;j<=m;j++)
	  num[i][j][a][b]=num[i-1][j][a][b]+num[i][j-1][a][b]
	    -num[i-1][j-1][a][b]+(Sum(i-a+1,j-b+1,i,j)==0);
      }
    }
  }
  //debug
  for(int i=1;i<=q;i++){
    int x1=read(),y1=read(),x2=read(),y2=read();
    int ans(0);
    for(int a=1;a<=x2-x1+1;a++){
      for(int b=1;b<=y2-y1+1;b++){
	ans+=Num(a,b,x1+a-1,y1+b-1,x2,y2);
      }
    }
    printf("%d\n",ans);
  }
  return 0;
}
/*
*/

```


---

## 作者：star_eternal (赞：1)

### 注意一个性质

存在一行假设$x$个$0$时 ，  以第$i$个$0$结尾的纯$0$矩阵个数为$i$
那么我我们假设$ f[i][j][k][h] $表示以$i,j$为坐上角的矩阵中 ， 当以$k,h$为右下角的纯0矩阵数。这个处理的复杂度为$O(n^5)$
然后对于每一个查询输出$\sum_{k = a} ^ c{\sum_{h = b}^df[a][b][k][h]}$即可这个操作复杂的为$O(n^2 * q)$总复杂度$O(n^5 + n^2 *q)$
4秒完全够用
```
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn = 40 + 4;
int f[Maxn][Maxn][Maxn][Maxn] , sum[Maxn][Maxn];
char mtix[Maxn][Maxn];
int n , m , q;
int main()
{
	scanf("%d%d%d",&n , &m, &q);
	for(int i = 1;i <= n;i++){
		scanf("%s",mtix[i] + 1);
		for(int j = 1;j <= m;j++)
			if(mtix[i][j] == '1')continue;
			else 
				if(mtix[i][j - 1] == '0')sum[i][j] = sum[i][j - 1] + 1;
				else sum[i][j] = 1;
	}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			for(int k = i;k <= n;k++)
				for(int h = j;h <= m;h++){
					int cnt = 0 , tmp = 1e9;
					for(int x = k ;x >= i;x--){
						tmp = min(tmp , min(sum[x][h] , h - j + 1));
						cnt += tmp;
					}
					f[i][j][k][h] = cnt;
				}
	for(int i = 1;i <= q;i++)
	{
		int a , b , c , d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int ans = 0;
		for(int j = a;j <= c;j++)
			for(int k = b ;k <= d;k++)
				ans += f[a][b][j][k];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

首先用二维前缀和找出每一个好矩形，容易发现查询其实是一个四维偏序的数点，直接上四维前缀和就好了。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m,o;
int a[45][45];
int pre[45][45];
int Q[45][45][45][45];
int main(){
	n=read(),m=read(),o=read();
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)a[i][j]=s[j-1]-'0';
		for(int j=1;j<=m;j++)pre[i][j]=pre[i-1][j]+pre[i][j-1]+a[i][j]-pre[i-1][j-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int p=i;p<=n;p++){
				for(int q=j;q<=m;q++){
					if(pre[p][q]-pre[i-1][q]-pre[p][j-1]+pre[i-1][j-1]==0)
						Q[i][j][p][q]=1;					
				}
			}
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			for(int p=1;p<=n;p++){
				for(int q=1;q<=m;q++){
					Q[i][j][p][q]+=Q[i+1][j][p][q];
				}
			}
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			for(int p=1;p<=n;p++){
				for(int q=1;q<=m;q++){
					Q[i][j][p][q]+=Q[i][j+1][p][q];
				}
			}
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			for(int p=1;p<=n;p++){
				for(int q=1;q<=m;q++){
					Q[i][j][p][q]+=Q[i][j][p-1][q];
				}
			}
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			for(int p=1;p<=n;p++){
				for(int q=1;q<=m;q++){
					Q[i][j][p][q]+=Q[i][j][p][q-1];
				}
			}
		}
	}
	while(o--){
		int i=read(),j=read(),p=read(),q=read();
		cout<<Q[i][j][p][q]<<'\n';
	}
}
```

---

## 作者：lfxxx (赞：0)

我们可以首先 $O(n^4)$ 的枚举所有子矩形，然后问题就是怎么快速算出包含的所有矩阵权值和，不难发现对于一个子矩阵 $(a,b,c,d)$ 可以将其坐标转变为 $(n-a+1,m-b+1,c,d)$ 然后对于一个限制可以转变为四个维度上均小于给定值的所有矩阵权值和，也就是一个四维前缀和，直接容斥求出，具体地，我们对丢失一个维度上的行的信息去容斥，那么就可以求出挖掉一个角的信息，再把个角的信息加上即可。

复杂度是 $O(n^4 + q)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
int n,m,q;
int pre[maxn][maxn];
int f[maxn][maxn][maxn][maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			pre[i][j]=c-'0';
			pre[i][j]+=(pre[i][j-1]+pre[i-1][j]-pre[i-1][j-1]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int x=i;x<=n;x++){
				for(int y=j;y<=m;y++){
					if(pre[x][y]-pre[x][j-1]-pre[i-1][y]+pre[i-1][j-1]==0) f[n-i+1][m-j+1][x][y]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int x=1;x<=n;x++){
				for(int y=1;y<=m;y++){
					f[i][j][x][y]+=(f[i][j][x][y-1]+f[i][j][x-1][y]+f[i][j-1][x][y]+f[i-1][j][x][y]-f[i-1][j-1][x][y]-f[i-1][j][x-1][y]-f[i-1][j][x][y-1]-f[i][j-1][x-1][y]-f[i][j-1][x][y-1]-f[i][j][x-1][y-1]+f[i][j-1][x-1][y-1]+f[i-1][j][x-1][y-1]+f[i-1][j-1][x][y-1]+f[i-1][j-1][x-1][y]-f[i-1][j-1][x-1][y-1]);
				}
			}
		}
	}
	while(q--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		a=n-a+1,b=m-b+1;
		cout<<f[a][b][c][d]<<'\n';
	}
	return 0; 
}
```

---

## 作者：ELLIAS (赞：0)

## DP
### NULL Problem :

#### 题目描述
给定一个${n* m}$的01矩阵, q次询问, 每次询问指定一个子矩形, 求该子矩形种有多少个只包含0的子矩阵.
矩阵从上到下编号1~n, 从左到右编号1~m.
#### 输入格式
第一行三个整数n,m,q. 接下来n行, 每行m个整数描述该矩阵. 接下来q行, 每行四个整数a,b,c,d表示询问的子矩阵左上角为(a,b), 右下角为(c,d).
#### 输出格式
对于每个询问, 输出一个整数表示答案.

### EINS Solution

看到本题很小的数据范围 ${1<=n,m<=40}$ , 内心或许会萌发一些类似于把整张图状压的想法. 但看到时限是 ${4s}$ , 当然会想到本题可以使用暴力求解.

本题要求两个点之间共有多少个全部为0的子矩阵,q的范围高达${3* 10^5}$, 不难想到, 可以通过暴力的dp打出表然后${O(1)}$查询.

令${dp[x1][y1][x2][y2]}$表示从(x1, y1)到(x2, y2)的答案, 不难得到状态转移方程:

约定${x1<=x2, y1<=y2}$

${dp[x1][y1][x2][y2]=dp[x1][y1][x2-1][y2]+dp[x1][y1][x2][y2-1]-dp[x1][y1][x2-1][y2-1]}$

${dp[x1][y1][x2][y2] +=}$ 该区域内能获得的矩形数量

### ZWEI Code

代码就比较好写:
```cpp
register int n = read (), m = read (), _ = read (), nico;
	for (Re int i = 1; i <= n; ++ i)
	{
		for (Re int j = 1; j <= m; ++ j)
		{
			scanf ("%1d", &nico);
			if (nico) lin[i][j] = 0;
			else lin[i][j] = lin[i-1][j] + 1;
		}
	}
	
	for (Re int frx = 1; frx <= n; ++ frx)
	{
		for (Re int fry = 1; fry <= m; ++ fry)
		{
			for (Re int tox = frx; tox <= n; ++ tox)
			{
				for (Re int toy = fry; toy <= m; ++ toy)
				{
					ans[frx][fry][tox][toy] = ans[frx][fry][tox-1][toy] + ans[frx][fry][tox][toy-1] - ans[frx][fry][tox-1][toy-1];
					nico = tox - frx + 1;
					for (Re int k = toy; k >= fry; -- k)
					{
						nico = min (nico, lin[tox][k]);
						ans[frx][fry][tox][toy] += nico;
					}
				}
			}
		}
	}
	
	while (_ --) writelen (ans[read()][read()][read()][read()]);
```

---

