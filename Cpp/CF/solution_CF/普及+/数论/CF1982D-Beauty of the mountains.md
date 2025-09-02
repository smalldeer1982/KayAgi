# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：SnapYust (赞：4)

# 题目传送门

[Beauty of the mountains](https://www.luogu.com.cn/problem/CF1982D)

# 思路

观察数据范围，可知 $\sum n\times m\le250000$，所以考虑一种 $O(nm)$ 的解法。

我们先假设所有无雪盖的山峰高度之和为 $c1$，有雪盖的山峰高度之和为 $c2$，分别求出 $h1,h2$。

注意到每次操作只能选一个 $k\times k$ 的矩阵，所以我们可以枚举所有 $k\times k$ 矩阵的左上角，也就是 $1\le i\le n-k+1,1\le j\le m-k+1$。

对于每个枚举的矩阵左上角，我们可以统计矩阵中的无雪盖和有雪盖的山峰的个数，可以用前缀和简单求出。

具体地，给一个前缀和 $sum_{i,j}=\begin{aligned}\sum_{k=1}^i\sum_{l=1}^jb_{k,l}\end{aligned}$（其中 $b_{i,j}$ 的取值为 $0/1$，表示此山峰有无雪盖），那么对于一个矩阵的左上角 $(i,j)$，这个矩阵内的无雪盖山峰个数为 $s1=sum_{i+k-1,j+k-1}-sum_{i-1,j+k-1}-sum_{i+k-1,j-1}+sum_{i-1,j-1}$，有雪盖山峰个数为 $s2=k\times k-s1$。

同时，对于一个 $k\times k$ 矩阵，我们可以使其内山峰加上一个整数（包括 $0$），给每个矩阵按顺序编号，最大可以编到 $n\times m$。用两个数组（$x1,x2$）表示这个矩阵中无雪盖山峰和有雪盖山峰的个数。

可以得到一个方程，设每个矩阵的改变量是 $c_i$，那么：

$$h_1+c_1x1_1+c_2x1_2+...=h_2+c_1x2_1+c_2x2_2+...$$

其中只有 $c_i$ 是未知数，那么：

$$(x1_1-x2_1)c_1+(x1_2-x2_2)c_2+...=h_2-h_1$$

这个方程是这样的形式：

$$a_1x_1+a_2x_2+...+a_nx_n=b(a_1,...,a_n,b\in Z)$$

根据裴蜀定理，这个方程有整数解当且仅当 $\gcd(a_1,...a_n)\mid b$ 时。

所以若上述方程有整数解那就输出 `YES`，否则输出 `NO`。

# Code

思路讲的比较抽象。

细节比较多。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sum[505][505]={0},cn=0,t;
long long a[505][505],c1=0,c2=0,x1[250050]={0},x2[250050]={0};
string c[505];
long long gcd(long long a,long long b){if(b)while((a%=b)&&(b%=a));return a+b;}
void solve(){
	c1=0,c2=0,cn=0;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j],sum[i][j]=0;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=c[i][j-1]-'0'+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            if(c[i][j-1]-'0'==1)c1+=a[i][j];
            else c2+=a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
    	if(i+k-1>n)break;
        for(int j=1;j<=m;j++){
        	if(j+k-1>m)break;
            if(i+k-1<=n&&j+k-1<=m){
                int s1=sum[i+k-1][j+k-1]-sum[i+k-1][j-1]-sum[i-1][j+k-1]+sum[i-1][j-1];
                x1[++cn]=s1;
                x2[cn]=k*k-s1;
            }
        }
    }
	c2=c1-c2;
	if(c2==0){cout<<"YES"<<endl;return;}
	for(int i=1;i<=cn;i++)x2[i]-=x1[i];
	long long h=x2[1];
	for(int i=2;i<=cn;i++)h=gcd(h,x2[i]);
	if(h==0){cout<<"NO"<<endl;return;}
	if(c2%h==0)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1982D)

前置知识：[裴蜀定理](https://www.luogu.com.cn/problem/P4549)，二维前缀和。

先对原矩阵做一下二维前缀和，记最初有雪的格子的总高度减去无雪的格子的总高度为 $s$。然后考虑枚举原矩阵中每一个大小为 $k$ 的矩阵，计算出给这个矩阵加一后 $s$ 的变化，记作 $c_i$。由于我们可以对每个大小为 $k$ 的矩阵做任意多次加一操作，那么问题就转化为，求 $c_1\times x_1+c_2\times x_2\dots =s$ 是否有解。根据裴蜀定理可知如果这个方程有解，一定满足 $s$ 是 $c_1,c_2,\dots$ 的最大公因数的倍数，根据这个性质判断即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int t,n,m,k,a[N][N],s[N][N],sa,sb,b[N][N];
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while (t--){
		cin>>n>>m>>k;sa=sb=0;k--;
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				cin>>b[i][j];
			}
		}
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				char x;cin>>x;a[i][j]=x-'0';
				s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
				if (a[i][j]==0) sa+=b[i][j];
				else sb+=b[i][j];
			}
		}sa=abs(sa-sb);sb=0;
		for (int i=1;i+k<=n;i++){
			for (int j=1;j+k<=m;j++){
				int siz=s[i+k][j+k]-s[i-1][j+k]-s[i+k][j-1]+s[i-1][j-1];
				sb=__gcd(sb,abs((k+1)*(k+1)-siz-siz));
			}
		}
		//cout<<sa<<" "<<sb<<endl;
		if (sb==0){
			if (sa==0) cout<<"YES\n";
			else cout<<"NO\n";
			continue;
		}
		if (sa%sb==0) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：2)

主要算法：二维前缀和+裴蜀定理

### 思路：
我们考虑到，如果要让这两部分分别相等（$0$ 部分的和为 $sum_0$，$1$ 部分的和为 $sum_1$），那么我们对于每一个 $k\times k$ 的矩阵 $m_{i}$，假设当前矩阵被选且其中有 $num_{i,0}$ 个 $0$，和 $num_{i,1}$ 个 $1$，且当前答案系数为 $c_i$。

我们令 $sum_0$ 加上 $c_k\times num_{i,0}$，$sum_1$ 加上 $c_k\times num_{i,1}$，那么 $sum_0$ 会加上 $\underset{i\in S} {\sum}c_i\times num_{i,0}$，$sum_1$ 会加上 $\underset{i\in S}{\sum}c_i\times num_{i,1}$。这两部分加上原来的部分就是我们要求的相等的和，所以设原来两部分的差为 $mn$，这样则有 $\underset{i\in S} {\sum}c_i\times |num_{i,0}-num_{i,1}|=mn$。

而绝对值内的部分可以通过**二维前缀和**预处理，$c$ 为未知数，所以这是标准的不定方程的形式，我们利用**裴蜀定理**，求出所有 $|num_{i,0}-num_{i,1}|$ 的 $\gcd$ （如果其中存在 $0$ 则跳过），如果所有这些数都是 $0$ 且 $mn=0$，或者这个 $\gcd$ 整除 $mn$ 则有方案，否则无方案。

为什么要求出所有的 $|num_{i,0}-num_{i,1}|$ 的 $\gcd$？因为你选的多，这个 $\gcd$ 就会尽可能小。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t,n,m,k,a[501][501],b[501][501],f[501][501][2],c[501][501][2];

signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		int suma=0,sumb=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char ch;cin>>ch;
				b[i][j]=ch-'0';
				if(b[i][j]==1)suma+=a[i][j];
				else sumb+=a[i][j];
			}
	    }
	    int mn=abs(suma-sumb);
	    for(int i=1;i<=n;i++){
	    	for(int j=1;j<=m;j++){
	    		f[i][j][1]=f[i-1][j][1]+f[i][j-1][1]-f[i-1][j-1][1];
				f[i][j][0]=f[i-1][j][0]+f[i][j-1][0]-f[i-1][j-1][0];
				if(b[i][j]==1)f[i][j][1]++;
				if(b[i][j]==0)f[i][j][0]++;
			}
		}
		for(int i=1;i+k-1<=n;i++){
			for(int j=1;j+k-1<=m;j++){
				c[i][j][0]=f[i+k-1][j+k-1][0]-f[i+k-1][j-1][0]-f[i-1][j+k-1][0]+f[i-1][j-1][0];
				c[i][j][1]=f[i+k-1][j+k-1][1]-f[i+k-1][j-1][1]-f[i-1][j+k-1][1]+f[i-1][j-1][1];
			}
		}
		/*
		cout<<"checking 0:"<<endl;
		for(int i=1;i+k-1<=n;i++){
			for(int j=1;j+k-1<=m;j++){
				cout<<c[i][j][0]<<" ";
			}
			cout<<endl;
		}
		cout<<"1:"<<endl;
		for(int i=1;i+k-1<=n;i++){
			for(int j=1;j+k-1<=m;j++){
				cout<<c[i][j][1]<<" ";
			}
			cout<<endl;
		}
		cout<<"checked"<<endl;
		*/
		int g=0;
		for(int i=1;i+k-1<=n;i++){
			for(int j=1;j+k-1<=m;j++){
				if(g==0)g=abs(c[i][j][0]-c[i][j][1]);
				else g=__gcd(g,abs(c[i][j][0]-c[i][j][1]));
			}
		}
		if(g==0&&mn==0)cout<<"YES";
		else if(g!=0&&mn%g==0)cout<<"YES";
		else cout<<"NO";
		cout<<"\n";
	}
}

```

---

## 作者：Angraecum (赞：1)

主要描述思路过程。

---------------

首先观察数据范围，发现数据允许 $O(n^3)$ 的做法，考虑是去枚举所有子矩形并且用 $O(n)$ 的时间对其进行操作，并且每个子矩形的信息是可以用二维前缀和维护的。

尝试去发掘一些性质，我们观察这个修改操作，发现它的本质是在不断按子矩形内 $0,1$ 个数差缩小两堆数的总和之间的差距。那么可以考虑记录下所有子矩形中 $0,1$ 个数的差值（为方便就记绝对差），然后再来观察怎么进行下一步。

其实想到这里剩下的做法就很显然了，我们做完以上转化后可以理解为是有 $n$ 个数，每个数可以不选或选多次，问是否能凑成一个数 $m$，也就是初始两堆数的总和之差。

这个问题又可以表示成这样一个形式：问一个 $n$ 元一次方程 $a_1\cdot x_1+a_2\cdot x_2+\cdots+a_n\cdot x_n=m$ 是否有解。$a_i$ 是每个子矩形的 $0,1$ 个数绝对差，也就是系数；$x_i$ 是操作每个子矩形所用的 $c$ 。然后这个问题就可以用**裴蜀定理**解决。

结论：当 $\gcd\limits_{i=1}^n a_i\mid m$ 时，方程有解，输出 ``YES``，反之 ``NO``。

代码是因为想着 $O(n^3)$ 也能过就只写了一维前缀和。

[code](https://codeforces.com/contest/1982/submission/271030738)

---

## 作者：liuliucy (赞：0)

## 思路
首先转换问题，求有雪高度和（称为 $s_0$ ）减去无雪高度和（称为 $s_1$）的和为 $0$ 是否可行。

我们发现，在 $k\times k$ 的方格中同时增加 $c$，其实就是给无雪的增加了 $a\times c$ 的高度（$a$ 是 $k\times k$ 方格中无雪的位置的个数），有雪增加了 $b\times c$，差值增加了 $(a-b)\times c$ 我们如果求出了所有的 $(a-b)$ 存到 $s$ 数组中，便就是求是否存在整数 $c_i$ 使得 $\sum s_i c_i=s_0-s_1$ 用裴蜀定理验证即可。
## code
记得开 long long。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500;
int a[505][505],T;
int b[505][505];
int sum[2][505][505];
int s[N*N+5];
int cnt=0;
int n,m,k;
long long sum1,sum2;
void read(int &x){
	char ch=getchar();x=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
}
int ssum(int x,int y,int p){
	return sum[p][x][y]+sum[p][x-k][y-k]-sum[p][x-k][y]-sum[p][x][y-k];
}
signed main(){
	scanf("%d",&T);
	while(T--){
//		scanf("%d%d%d",&n,&m,&k);
		read(n);read(m);read(k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				read(a[i][j]); 
			}
		}sum1=sum2=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%1d",&b[i][j]); 
				if(b[i][j])sum1+=a[i][j];
				else sum2+=a[i][j];
			}
		}
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				sum[1][i][j]=sum[1][i-1][j]+sum[1][i][j-1]-sum[1][i-1][j-1];
				sum[0][i][j]=sum[0][i-1][j]+sum[0][i][j-1]-sum[0][i-1][j-1];
				sum[b[i][j]][i][j]++;
			}
		}cnt=0;
		memset(s,0,sizeof(s));
		for(int i=k;i<=n;i++){
			for(int j=k;j<=m;j++){
				s[++cnt]=ssum(i,j,1)-ssum(i,j,0);
			}
		}
		sum1-=sum2;
		if(sum1==0){
			printf("YES\n");
			continue;
		}
		int g=0;
		for(int i=1;i<=cnt;i++){
			g=__gcd(s[i],g);
		}
		if(g==0){
			printf("NO\n");
			continue;
		}
		if(sum1%g==0){
			printf("YES\n");
		}
		else printf("NO\n");
	}
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

单独考虑每一个山的贡献很难做，不妨以 $k\times k$ 的矩形为基础计算贡献。

我们发现每在 $k\times k$ 的矩阵内加上 $x$ 的贡献，钦定有雪与无雪的山分别作正、负贡献，记为 $b_i$。操作前的贡献为 $sum$，有雪的山总高度和无雪的格子的总高度相等其等价于判断 $\sum x_ib_i+sum=0$，即为 $\sum x_ib_i=-sum$。

这就是一个 $n$ 阶裴蜀定理，若 $-sum$ 为 $\gcd{x_i}$ 的倍数，则 $x_i$ 有整数解。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 505;

int T, n, m, k, a[N][N], s[N][N], Ans;

bool b[N][N];

int ask(int x1, int y1, int x2, int y2) {
  return s[x2][y2] - s[x2][y1-1] - s[x1-1][y2] + s[x1-1][y1-1];
}

void solve() {
  Ans = 0;
  int sum = 0;
  cin >> n >> m >> k;
  memset(s, 0, sizeof s);
  For(i,1,n) For(j,1,m) cin >> a[i][j];
  For(i,1,n) {
    For(j,1,m) {
      char c; cin >> c;
      b[i][j] = c - '0';
    }
  } 
  For(i,1,n) {
    For(j,1,m) {
      sum += (b[i][j] ? a[i][j] : -a[i][j]);
      int F = (b[i][j] == 1 ? 1 : -1);
      s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + F;
    }
  }
  For(i,1,n-k+1) {
    For(j,1,m-k+1) {
      int k1 = ask(i, j, i+k-1, j+k-1);
      Ans = __gcd(Ans, k1);
    }
  }
  if(sum == 0) {
    puts("YES");
    return ;
  }
  if(Ans == 0) {
    puts("NO");
    return ;
  }
  if(sum % Ans == 0) puts("YES");
  else puts("NO");
  return ;
}

signed main() {
  // ios::sync_with_stdio(0);
  // cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：ben090302 (赞：0)

有趣数论（？）题。

将有雪盖的山的贡献看作高度，没有的视为其高度的相反数（即贡献系数分别为正负 $1$）。

则当总贡献为 $0$ 的时候即为合法。

先扫一遍算出初始总贡献 $sum$。

考虑二维前缀和维护每一个 $k*k$ 范围的贡献系数的和记作 $d$，那么在这个范围 $+c$ 造成对总贡献的影响就是 $cd$ 。

假设有 $w$ 种不同的贡献系数，第 $i$ 个记作 $a_i$，每个范围加 $x_i$ 可刚好抵消 $sum$ ，那么就是解方程 $\sum\limits_{i=1}^{w}a_i x_i=-sum$。

根据裴蜀定理，当且仅当 $sum$ 是 $\gcd(a_1,a_2....,a_w)$ 的倍数时方程有整数解。

就做完了


code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,k;
int a[505][505];
char tp[505][505];
int b[505][505];
int s[505][505];
int query(int x,int y,int xx,int yy){
    return s[xx][yy]+s[x-1][y-1]-s[xx][y-1]-s[x-1][yy];
}
vector<int> M;
signed main(){
    cin>>T;
    while(T--){
        M.clear();
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>tp[i][j];
                if(tp[i][j]=='1') b[i][j]=1;
                else b[i][j]=-1;
                s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+b[i][j];
            }
        }
        int sum=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                sum+=a[i][j]*b[i][j];
            }
        }
        if(sum==0){
            cout<<"YES\n";
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int x=i,y=j,xx=i+k-1,yy=j+k-1;
                if(xx>n or yy>m) continue;
                M.push_back(abs(query(x,y,xx,yy)));
            }
        }
        sort(M.begin(),M.end());
        unique(M.begin(),M.end());
        int nm=M.size()-1;
        for(int i=0;i<M.size();i++){
            if(M[i]==M[i+1] or M[i]>M[i+1]){
                nm=i;
                break;
            }
        }
        int Z=M[0];
        for(int i=1;i<=nm;i++){
            Z=__gcd(Z,M[i]);
        }
        if(Z==0){
             cout<<"NO\n";
            continue;
        }
        if(sum%Z==0) {
            cout<<"YES\n";
        }
        else cout<<"NO\n";
    }
}
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

显然，每个格子的值具体是多少我们并不关心，我们只关心两种格子的值的**差值**，记为 $\Delta$。

很显然，对 $k \times k$ 的子矩形中的每一个数都加上 $c_{1}$，再加上 $c_{2}$，与直接加上 $c=c_{1}+c_{2}$ 没有区别。因此，如果有解，一定存在这样的解：我们对每个需要变化的子矩形最多进行 $1$ 次操作。

当然，如果对某个子矩形不进行操作，我们也可以对它进行一次加上 $c=0$ 的操作。这样，一定存在这样的一组解：我们对每个 $k \times k$ 的子矩形都进行且只进行 $1$ 次操作。

对于某个子矩形，加入它有 $x$ 个有雪的格子，那么它一定有 $\left ( k^{2}-x \right )$ 个没有雪的格子。那么对这个子矩形进行一次操作后，会使 $\Delta$ 变化为 $\Delta + c \times \left [ \left ( k^{2}-x \right ) -x\right ]$（显然你想要 $\Delta$ 减小只需让 $c$ 为负数）。

对每个子矩形维护这样一个特征值 $\left [ \left ( k^{2}-x \right ) -x\right ]$，记为 $t$。对这个子矩形的操作必然使 $\Delta$ 增加或减小 $t$ 的倍数。

这样我们就获得了一系列的 $t$，记为 $t_{1},t_{2},t_{3}, \dots ,t_{g}$。问题变成解下面的不定方程是否有**整数解**：

$$\Delta=\sum\limits_{i=1}^{g}c_{i} \cdot t_{i}$$

显然如果 $\Delta$ 是 $\gcd \{ t_{i} \}$ 的倍数，则有解；反之则无解。

$\color{blue}{\text{[code]}}$

```cpp
typedef long long ll;

char c[510];
int n,m,T,res,k;ll delta;
int a[510][510],b[510][510],s[510][510];

inline int Abs(int u){
	return ((u<0)?-u:u);
}
inline int gcd(int u,int v){
	if (v==0) return u;
	return gcd(v,u%v);
}

int main(){
	T=read();
	while (T--){
		n=read();m=read();k=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]=read();
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				b[i][j]=s[i][j]=0;//只能这么清空 
		delta=0;res=-1;
		
		for(int i=1;i<=n;i++){
			scanf("%s",c+1);
			for(int j=1;j<=m;j++)
				if (c[j]=='1'){
					delta+=a[i][j];
					b[i][j]=1;
				}
				else{
					delta-=a[i][j];
					b[i][j]=-1;
				}
		}
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+b[i][j];
		
		for(int i=k;i<=n;i++)
			for(int j=k;j<=m;j++){
				int tmp=s[i][j]-s[i-k][j]-s[i][j-k]+s[i-k][j-k];
				if (res==-1) res=Abs(tmp);
				else res=gcd(res,Abs(tmp));
			}
		
		if (res==0) printf("%s\n",(delta==0?"Yes":"NO"));
		else if (delta%res==0) printf("yEs\n");
		else printf("nO\n");
	}
	
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

首先，我们只需要考虑 $1$ 和 $0$ 的高度和差，假设现在我们只进行一次操作，那么设我们选择的一个矩阵内 $1$ 有 $x$ 个，$0$ 有 $y$ 个，因为同增同减，那我们只需要考虑 $|x-y|$ 个位置带来的贡献，显然，如果当前总和差为 $d$，那么我们只需要令 $|x-y|$ 整除 $d$，此时就可以取到一个合法的 $c$。

进一步的，当进行多次操作时，假如令 $|x-y|$ 为 $a$，刚才的式子可以看做当 $ac=d$ 的一个关于 $c$ 的一元方程。那么此时有多个矩阵，每个矩阵都可以加不同的 $c$，每个矩阵的 $a$ 也不同，可以将上面式子拓展 $\sum a_i c_i = d$，就是一个关于 $c$ 的多元方程，这东西其实就是裴蜀定理拓展，有结论 $\gcd(a_1,a_2,...,a_n)|d$ 时方程有解，$c$ 有合法取值。

之后用二维前缀和计算每个矩阵 $a$ 和 $c$ 即可。

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define bug (x>=1&&x<=n&&y>=1&&y<=m) 
#define push_back pb
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
const int N=1e6+5,M=1e7+5;
const db eps=1e-7;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,m,k,mp[505][505],mp1[505][505];
ll pre[505][505][4];char op[N];
inline ll get(pii a,ll op){return pre[a.first][a.second][op]-pre[a.first-k][a.second][op]-pre[a.first][a.second-k][op]+pre[a.first-k][a.second-k][op];}
inline void solve(){
	fo(1,i,n) fo(1,j,m) read(mp[i][j]);
	fo(1,i,n){scanf("%s",op+1);fo(1,j,m) mp1[i][j]=op[j]-'0';}
	fo(1,i,n) fo(1,j,m)
	{
		pre[i][j][0]=pre[i-1][j][0]+pre[i][j-1][0]-pre[i-1][j-1][0];
		pre[i][j][1]=pre[i-1][j][1]+pre[i][j-1][1]-pre[i-1][j-1][1];
		pre[i][j][2]=pre[i-1][j][2]+pre[i][j-1][2]-pre[i-1][j-1][2]+(!mp1[i][j]?mp[i][j]:0);
		pre[i][j][3]=pre[i-1][j][3]+pre[i][j-1][3]-pre[i-1][j-1][3]+(mp1[i][j]?mp[i][j]:0);
		if(mp1[i][j]) pre[i][j][1]++;else pre[i][j][0]++;
	}
	ll sum=abs(pre[n][m][2]-pre[n][m][3]);ll ans=0;
	fo(k,i,n) fo(k,j,m){ll op=abs(get({i,j},0)-get({i,j},1));if(!op) continue;if(!ans) ans=op;else ans=__gcd(ans,op);}
	if(!ans&&!sum)printf("Yes\n");
	else if(ans&&!(sum%ans)) printf("Yes\n");
	else printf("No\n");	
}
signed main(){
	read(t);while(t--){read(n),read(m),read(k);solve();fo(0,k,3) fo(1,i,n) fo(1,j,m) pre[i][j][k]=mp[i][j]=mp1[i][j]=0;}
	return 0;
}
``````

---

## 作者：yshpdyt (赞：0)

## 题意
一个 $n\times m$ 的矩阵 $a_{i,j}$，每个位置还有一个颜色白或黑 $(0 /1)$ ，每次可以选择一个 $k\times k$ 的子矩阵让其每个位置的值加上任意值，求任意次操作后，是否能使两种颜色的权值和相同。 

## Sol
说句闲话：赛时秒了，但不知道最后一步的结论卡到比赛结束前 $5$ 分钟才过。

我们只在乎两种颜色的权值和的差，不妨设没有更改前：
$$c=\sum\limits_{color_{i,j}=0}a_{i,j}-\sum\limits_{color_{i,j}=1} a_{i,j}$$

我们的目标是让 $c$ 归零。

注意到每次选择一个子矩阵，如果其中有 $p$ 个 $0$，那么剩下就有 $k^2-p$ 个 $1$，如果使该矩阵每个位置增加 $x$，对 $c$ 的影响为增加 $x(2p-k^2)$。观察到这个式子只与我们选择的矩阵和增加的值有关，而和次数无关，所以每次增加操作相互独立。

不妨把所有 $k\times k$ 的子矩阵的 $(2p-k^2)$ 记录下来（感性理解一下，记录的越多肯定越好凑出答案，全记下来复杂度也不会超），可以用二维前缀和快速完成，设有 $m$ 个不同的 $(2p-k^2)$，设第 $i$ 个为 $a_i$。

于是问题变成了一个数列，给每个位置分配一个乘法系数，问是否可能让前 $m$ 项的和等于 $-c$，写成数学语言：

$$\sum\limits_{i=1}^m a_ix_i=-c$$

或者不妨换一种更形象的形式：

$$a_1x_1+a_2x_2+a_3x_3+\cdots+a_nx_n=-c$$

这是什么？这是 $n$ 元一次方程啊！这个问题是判断该方程是否有整数解。擅长数论的同学肯定一眼的就发现了 （~~可惜我不擅长~~），这个方程是多元线性丢番图方程。

直接给出定理：如果 $a_1,a_2,\cdots,a_n$ 是整数，方程 $a_1x_1+a_2x_2+\cdots+a_nx_n=c$ 有整数解，当且仅当 $\gcd(a_1,a_2,\cdots,a_n)|c$。

于是这道题就被解决了，注意特判系数为 $0$ 的情况。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 505
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,k,sum[N][N],a[N][N],c[N][N];
ll top,q[250005];
void sol(){
    top=0;
    cin>>n>>m>>k;
    ll x=0,y=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=1;j<=m;j++){
            a[i][j]=s[j-1]-'0';
            if(a[i][j])x+=c[i][j];
            else y+=c[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    }
    for(int i=1;i+k-1<=n;i++){
        for(int j=1;j+k-1<=m;j++){
            ll p=sum[i+k-1][j+k-1]-sum[i-1][j+k-1]-sum[i+k-1][j-1]+sum[i-1][j-1];
            q[++top]=(2*p-k*k);
        }
    }
    sort(q+1,q+top+1);
    top=unique(q+1,q+top+1)-(q+1);
    ll t=x-y;
    if(t==0){
        cout<<"YES\n";
        return ;
    }
    ll d=0;
    for(int i=1;i<=top;i++){
        if(q[i]==0)continue;
        if(d==0)d=q[i];
        else d=__gcd(d,q[i]);
    }
    if(d&&t%d==0)cout<<"YES\n";
    else cout<<"NO\n";
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}

```

---

