# [ABC099D] Good Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc099/tasks/abc099_d

$ N $ 行 $ N $ 列からなるグリッドがあり、上から $ i $ 行目の左から $ j $ 列目のマスを $ (i,j) $ とします。

これらのマスは色 $ 1 $ から 色 $ C $ までのいずれかの色で塗られていなければならず、はじめに $ (i,j) $ は色 $ c_{i,j} $ で塗られています。

グリッドが、$ 1\ \leq\ i,j,x,y\ \leq\ N $ を満たす任意の $ i,j,x,y $ に対して以下の条件を満たす場合、良いグリッドであるとします。

- $ (i+j)\ \%\ 3=(x+y)\ \%\ 3 $ ならば $ (i,j) $ の色と $ (x,y) $ の色は同じ
- $ (i+j)\ \%\ 3\ \neq\ (x+y)\ \%\ 3 $ ならば $ (i,j) $ の色と $ (x,y) $ の色は異なる

ただし、$ X\ \%\ Y $ は $ X $ を $ Y $ で割った余りを表すこととします。

グリッドが良いグリッドになるように $ 0 $ 個以上のマスを塗り替えます。

あるマスにおいて、塗り替える前の色が $ X $ であり、塗り替えた後の色が $ Y $ である場合に感じる、そのマスに対して感じる違和感は $ D_{X,Y} $ です。

すべてのマスに対して感じる違和感の和のとりうる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 3\ \leq\ C\ \leq\ 30 $
- $ 1\ \leq\ D_{i,j}\ \leq\ 1000\ (i\ \neq\ j),D_{i,j}=0\ (i=j) $
- $ 1\ \leq\ c_{i,j}\ \leq\ C $
- 入力は全て整数

### Sample Explanation 1

\- $ (1,1) $ を色 $ 2 $ に塗り替えます。$ (1,1) $ に対して感じる違和感は $ D_{1,2}=1 $ となります。 - $ (1,2) $ を色 $ 3 $ に塗り替えます。$ (1,2) $ に対して感じる違和感は $ D_{2,3}=1 $ となります。 - $ (2,2) $ を色 $ 1 $ に塗り替えます。$ (2,2) $ に対して感じる違和感は $ D_{3,1}=1 $ となります。 このとき、すべてのマスに対して感じる違和感の和は $ 3 $ です。 なお、$ D_{i,j}\ \neq\ D_{j,i} $ である場合に注意してください。

## 样例 #1

### 输入

```
2 3
0 1 1
1 0 1
1 4 0
1 2
3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
4 3
0 12 71
81 0 53
14 92 0
1 1 2 1
2 1 1 2
2 2 1 3
1 1 2 2```

### 输出

```
428```

# 题解

## 作者：Nightingale_OI (赞：3)

### 大意

有一个乱的 $ n \times n $ 矩阵，每个位置有颜色 $ c_{i,j} $ 。

要给它重新染色，使得如果 $ a + b \equiv c + d \quad (mod \, 3) $ ，则格子 $ (a,b) $ 与格子 $ (c,d) $ 同色，反之不同色。

把一个格子从颜色 $ i $ 改为颜色 $ j $ 的代价为 $ d_{i,j} $ 。

求最终满足要求的最小代价。

### 思路

可以把格子分为 $ 3 $ 组，同组格子强制同色，不同组格子强制不同色。

先求出每组格子统一变为每种颜色的代价，再枚举 $ 3 $ 组格子分别变为哪 $ 3 $ 种颜色即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
long long a[3][50];
int b[50][50];
int main(){
    cin>>n>>m;
    f(i,1,m)f(j,1,m)scanf("%d",&b[i][j]);
    f(i,1,n)f(j,1,n){
        s=(i+j)%3;
        scanf("%d",&l);
        f(k,1,m)a[s][k]+=b[l][k];
    }
    long long ans=10101010101;
    f(i,1,m)f(j,1,m)f(k,1,m)if(i!=j && i!=k && j!=k)ans=min(ans,a[0][i]+a[1][j]+a[2][k]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：wendywan (赞：1)

# [题目：AT_abc099_d [ABC099D] Good Grid](https://www.luogu.com.cn/problem/AT_abc099_d)


## 题目大意
给一个 $ N \times  N $ 的网格，每个格子都有一种颜色。颜色种类为 $ 1 \to C $，而每种颜色转换都有一种代价。

现在你要进行操作使得每个模 $3$ 余数相同的格子颜色都相同。

求最小代价。

输入：先是每种颜色 $ i \to j $ 的代价，后是每个点的颜色。


---


## 暴力
首先我们先观察 $C$ 的大小，$ C \le 30 $。考虑每种颜色枚举，这时复杂度为 $ O ( C ^ 3 ) $。

然后统计出每次枚举中每个格子逐一搜索变为该开始枚举出的颜色的代价，此时是 $ O ( C ^ 3 \cdot N ^ 2 )$。


---


**暴力 代码如下：**
```cpp
int finans = 100000005;
for( int i = 1; i <= C; i ++ ){//0
    for( int j = 1; j <= C; j ++ ){//1
        if( i == j ) continue;
        for( int k = 1; k <= C; k ++ ){//2
            //枚举三种颜色
            int ans = 0;
            if( ( i == k ) || ( j == k ) ) continue;// 如果颜色相同
            for( int x = 1; x <= N; x ++ ){
                for( int y = 1; y <= N; y ++ ){
                    // 枚举格子
                    int l = x + y;
                    if( l % 3 == 0 ){
                        if( c[x][y] == i ) continue;
                        else ans += D[c[x][y]][i];
                    }
                    if( l % 3 == 1 ){
                        if( c[x][y] == j ) continue;
                        else ans += D[c[x][y]][j];
                    }
                    else{
                        if( c[x][y] == k ) continue;
                        else ans += D[c[x][y]][k];
                    }
                    //变换颜色统计答案
                }
            }
            finans = min( finans, ans );
        }
    }
}

```
~~然后你就发现过了样例，t了~~



---


## 正解
正解其实就是在暴力代码的基础上稍作优化和改动。

使用预处理优化，开 $f$ 数组。

$f[i][j]$ 表示将 $(i + j) % 3 = i$ 的点改成j的颜色的代价。

此时预处理 $O( C \cdot N ^ 2 )$，
操作时还是枚举每种颜色，节省了 $ O( N ^ 2 ) $ 的复杂度。

**最终复杂度 $O( C \cdot N ^ 2 )$**。 


---


## code
```cpp
#include<bits/stdc++.h>
using namespace std;

int N, C;
int D[35][35], c[505][505];
int f[5][35];//将(i + j) % 3 = i的改成j的颜色的代价
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin >> N >> C;
    for( int i = 1; i <= C; i ++ ){
        for( int j = 1; j <= C; j ++ ){
            cin >> D[i][j];
        }
    }
    for( int i = 1; i <= N; i ++ ){
        for( int j = 1; j <= N; j ++ ){
            cin >> c[i][j];
        }
    }//%1\2\3改变成第i种颜色的代价
    
    //==========================输入


    int finans = 1e18;
    for( int i = 1; i <= C; i ++ ){//枚举颜色
        for( int x = 1; x <= N; x ++ ){
            for( int y = 1; y <= N; y ++ ){
                //枚举单点
                int j = ( x + y ) % 3;
                if( c[x][y] == i ) continue;
                else f[j][i] += D[c[x][y]][i];//统计代价
            }
        }
    }
    for( int i = 1; i <= C; i ++ ){//0
        for( int j = 1; j <= C; j ++ ){//1
            if( i == j ) continue;
            for( int k = 1; k <= C; k ++ ){//2
                if( ( i == k ) || ( j == k ) ) continue;
                int ans = 0;
                ans += f[0][i] + f[1][j] + f[2][k];
                //计算答案：最终情况的最小值
                finans = min( finans, ans );
            }
        }
    }
    cout << finans;
    return 0;
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

# AT\_abc099\_d \[ABC099D] Good Grid

~~话说这是绿？~~

## 解法

由题意得，我们就是要将整个矩阵分成三种颜色，求最小代价。

直接设 $f_{0/1/2, k}$ 表示将颜色为 0/1/2 的分组的数全部化为 $k$ 的最小花费，由于 $n$ 和 $m$ 非常小，所以直接暴力枚举即可。最后的答案便是 $\min{f_{0, i} + f_{1, j} + f_{2, k}}(i,j,k = 1 \sim m)(i \ne j \ne k)$。

## 注意事项

十年 OI 一场空，不开 long long 见祖宗。

## 代码

```
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 60;

int n, m;
int d[N][N], f[3][N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m; 
	for (int i = 1; i <= m; i++) 
		for (int j = 1; j <= m; j++) 
			cin >> d[i][j];
	
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) {
			int col = (i + j) % 3, x;
			cin >> x;
			for (int k = 1; k <= m; k++)
				f[col][k] += d[x][k];
		}
	
	int res = 1e18;
	for (int i = 1; i <= m; i++) 
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= m; k++) 
				if (i != j && j != k && i != k)
					res = min(res, f[0][i] + f[1][j] + f[2][k]);
	cout << res << '\n';
	
	return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

考虑将同色的格子分为一组，共分为 $3$ 组。求出 $3$ 组每组成为每种颜色的错误值，随后枚举每组应当变成哪种颜色即可。

详见代码

code:

```cpp
%:include<bits/stdc++.h>
#define int long long
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//快读快写自动略过
int n,c;
int d[68][68];
int f[68][10];
int ans=1145141919810;
signed main()<%
  	//freopen(".in","r",stdin);
  	//freopen(".out","w",stdout);
    n=read();
    c=read();
    for(int i=1;i<=c;i++)
        for(int j=1;j<=c;j++)
            d[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int op=(i+j)%3;
            int x=read();
            for(int k=1;k<=c;k++)
                f[k][op]+=d[x][k];//变成某种颜色的错误值
        }
    for(int i=1;i<=c;i++)
        for(int j=1;j<=c;j++)
            for(int k=1;k<=c;k++)
                if(i!=j and i!=k and j!=k)//颜色不能相同
                    ans=std::min(ans,f[i][0]+f[j][1]+f[k][2]);//取最小的错误值
 	write(ans);
    return 0;//撒花
%>

```

---

## 作者：Walter_Fang (赞：1)

## 大致题意

给定一个 $n\times n$ 的矩阵 $c$，代表初始颜色。我们要给该矩阵重新染色，若 $a+b \equiv c+d \pmod 3$，则格子 $a$ 与格子 $b$ 同色，否则不同色。将格子的颜色从 $i$ 更改成 $j$ 的代价是 $d_{i,j}$。

## 思路/解析

将所有格子分为 $3$ 组，同一组的格子颜色必须相同，不同一组的格子颜色必须不同。先求出每组格子全部变成每种颜色的代价，再枚举 $3$ 组格子分别变成哪 $3$ 种颜色，即可通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=50,M=3,inf=2e18;
long long n,m,s,x,i,j,k,ans=inf,c[N][N],f[M][N];
int main(){
    cin>>n>>m;
    for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
			cin>>c[i][j];
    for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
	        s=(i+j)%3;
	        cin>>x;
	        for(k=1;k<=m;k++)f[s][k]+=c[x][k];
    	}
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)
            for(k=1;k<=m;k++)
                if(i!=j&&i!=k&&j!=k)
							ans=min(ans,f[0][i]+f[1][j]+f[2][k]);
    cout<<ans<<'\n';
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定一个 $N\times N$ 的矩阵 $c_{i,j}$，值域为 $[1,C]$。再给定一个代价矩阵 $d_{i,j}$ 表示将 $i$ 变为 $j$ 需要花费代价 $d_{i,j}$。

好的矩阵表示对于任意 $i,j,x,y$，如果 $i+j\equiv x+y \pmod 3$，则 $c_{i,j}=c_{x,y}$；否则 $c_{i,j}\neq c_{x,y}$。

现问将 $c$ 变为好的矩阵的最小的代价。

**解题思路**

由于 $\bmod 3$ 只有三种情况，所以最后的 $c$ 恰巧只存在 $3$ 种值，这可以直接枚举。而把 $c_{i,j}$ 变为 $k$，那么 $f_{(i+j)\bmod 3,k}\gets f_{(i+j)\bmod 3,k}+d_{c_{i,j},k}$。

最终答案为：

$$
\min_{i=1}^C\min_{j=1}^C\min_{k=1}^Cf_{0,i}+f_{1,j}+f_{1,k}\ (i,j,k\text{ 互不相同})
$$

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505;
int n, c, a[35][35], f[3][35];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> c;
  for(int i = 1; i <= c; i++) {
    for(int j = 1; j <= c; j++) {
      cin >> a[i][j];
    }
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      int tmp = (i + j) % 3, x;
      cin >> x;
      for(int k = 1; k <= c; k++) {
        f[tmp][k] += a[x][k];
      }
    }
  }
  int ans = 1e9;
  for(int i = 1; i <= c; i++) {
    for(int j = 1; j <= c; j++) {
      for(int k = 1; k <= c; k++) {
        if(i != j && j != k && k != i) {
          ans = min(ans, f[0][i] + f[1][j] + f[2][k]);
        }
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc099_d)。


## Solution

先把每个 $c_{i,j}$ 丢进对应模 $3$ 余数的 vector，然后对这 $3$ 个 vector 求出统一成颜色 $j$ 的错误值。设 $x+y \equiv i\pmod 3$，统一成颜色 $j$ 的错误值为 $w_{i,j}$。枚举互不相等的 $i,j,k$ 为统一成的三种颜色，取 $\min w_{0,i}+w_{1,j}+w_{2,k}$ 即可。 

```cpp
#include<bits/stdc++.h>
#define il inline
#define eb emplace_back
using namespace std;
const int N=505;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m,ans=inf,d[N][N],a[N][N];
vector<int> v[3];

int w[3][N];

main(){
	n=wrd(),m=wrd();
	for(int i=1;i<=m;++i) for(int j=1;j<=m;++j) d[i][j]=wrd();
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) a[i][j]=wrd();
	
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) v[(i+j)%3].eb(a[i][j]);
	for(int i=0;i<3;++i){
		for(int j=1;j<=m;++j){
			for(int k:v[i]) w[i][j]+=d[k][j];
		}
	}
	
	for(int i=1;i<=m;++i){
		for(int j=1;j<=m;++j){
			if(i==j) continue;
			for(int k=1;k<=m;++k){
				if(i^k && j^k) ans=min(ans,w[0][i]+w[1][j]+w[2][k]);
			}
		}
	}
	return printf("%d",ans),0;
}
```

---

