# [ABC330D] Counting Ls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc330/tasks/abc330_d

$ N\ \times\ N $ のマス目が与えられます。このうち上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と書きます。  
 各マスの状態を表す $ N $ 個の長さ $ N $ の文字列 $ S_1,S_2,\dots,S_N $ が以下の形式で与えられます。

- $ S_i $ の $ j $ 文字目が `o` であるとき、 $ (i,j) $ には `o` が書かれている。
- $ S_i $ の $ j $ 文字目が `x` であるとき、 $ (i,j) $ には `x` が書かれている。
 
以下の条件を全て満たすマスの三つ組の個数を求めてください。

- 組に含まれる $ 3 $ マスは相異なる。
- $ 3 $ マス全てに `o` が書かれている。
- マスのうち、丁度 $ 2 $ つが同じ行にある。
- マスのうち、丁度 $ 2 $ つが同じ列にある。
 
但し、ふたつの三つ組は、丁度一方に含まれるマスが存在する場合のみ区別します。

## 说明/提示

### 制約

- $ N $ は $ 2 $ 以上 $ 2000 $ 以下の整数
- $ S_i $ は長さ $ N $ の `o` と `x` からなる文字列
 
### Sample Explanation 1

以下の $ 4 $ つの三つ組が条件を満たします。 - $ (1,1),(1,2),(2,1) $ - $ (1,1),(1,3),(2,1) $ - $ (1,1),(1,3),(3,3) $ - $ (1,2),(1,3),(3,3) $

## 样例 #1

### 输入

```
3
ooo
oxx
xxo```

### 输出

```
4```

## 样例 #2

### 输入

```
4
oxxx
xoxx
xxox
xxxo```

### 输出

```
0```

## 样例 #3

### 输入

```
15
xooxxooooxxxoox
oxxoxoxxxoxoxxo
oxxoxoxxxoxoxxx
ooooxooooxxoxxx
oxxoxoxxxoxoxxx
oxxoxoxxxoxoxxo
oxxoxooooxxxoox
xxxxxxxxxxxxxxx
xooxxxooxxxooox
oxxoxoxxoxoxxxo
xxxoxxxxoxoxxoo
xooxxxooxxoxoxo
xxxoxxxxoxooxxo
oxxoxoxxoxoxxxo
xooxxxooxxxooox```

### 输出

```
2960```

# 题解

## 作者：yhx0322 (赞：3)

## Description
给定只包含字符 `o` 和 `x` 的字符矩阵，求出满足以下条件的三元组的数量：
- 三元组中的单元格是不同的。
- 三元组中每个元组所对应的字符矩阵里的字符都为 `o`。
- 恰好有两个元组位于同一行中。
- 恰好有两个元组位于同一列中。

求：最多的三元组的数量。

## Solution
组合数学问题。

可以分别统计出每一行、每一列都分别有多少个 `o`，然后枚举每个 `o` 的位置，利用乘法原理，计算出包含当前的下标的情况下，不同三元组的数量为：$($这一行 `o` 的数量 $-1)$ $\times$ $($这一列 `o` 的数量 $-1)$。

这里 $-1$ 是为了减掉自己的那一个，防止影响计算。

最后累加答案即可。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e3 + 10;
int n;
char s[N][N];
int a1[N], a2[N];

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> s[i][j];
			a1[i] += (s[i][j] == 'o');
			a2[j] += (s[i][j] == 'o');
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[i][j] != 'o') continue;
			ans += ((a1[i] - 1) * (a2[j] - 1));
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：3)

# AT_abc330_d [ABC330D] Counting Ls 题解

计数问题，考察优化能力。

### 解析

观察数据范围，发现我们只能写低于 $n^2$ 级别的算法。这里思考扫一遍整个地图的做法。

为了方便表示，记标为 `o` 的格子为“`o` 格”。记 `row[i]` 为第 $i$ 列 `o` 格的个数，记 `col[i]` 为第 $i$ 行 `o` 格的个数。

如下图，若 A，B，C 点均为 `o`，则 A，B，C 三个点符合要求，记 B 点为“拐点”。

| A |  |
| :----------: | :----------: |
| x |  |
| **B** | **C** |

对于每一个 `o` 格，它都有可能成为“拐点”，所以它对答案 $ans$ 的贡献就很好算啦。有乘法原理，贡献就是 `(row[j]-1)*(col[i]-1)`，为什么要减 $1$ 呢？显而易见，是为了排除自己这个点。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
char c[N][N];
int n;
long long ans;
int col[N],row[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j]; 
			if(c[i][j]=='o'){
				col[i]++; //行
			}
		}
	}
	for(int j=1;j<=n;j++){
		for(int i=1;i<=n;i++){
			if(c[i][j]=='o'){
				row[j]++; //列
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(c[i][j]=='o'){
				ans+=(row[j]-1)*(col[i]-1); //题中说的
			}
		}
	}
	cout<<ans;
return 0;
}
```


---

## 作者：xz001 (赞：2)

- 首先我们发现这样的三元组只有可能是这四种样子：

$$
\begin{matrix}
  &  &  &  & o &|  &o  &  &  &  & O & | & o &  &  &  &  & | & O &  &  &  & o &  & \\
  &  &  &  &  &  | &  &  &  &  &  &  | &  &  &  &  &  & | &  &  &  &  &  &  & \\
  &  &  &  &  &  | &  &  &  &  &  &  | &  &  &  &  &  &  |  &&  &  &  &  &  & \\
  &  &  &  &  &  | &  &  &  &  &  &  | &  &  &  &  &  & | &  &  &  &  &  &  & \\
 o &  &  &  & O & | &  &  &  &  & o &  |  & O &  &  &  & o & | & o &  &  &  &  &  &
\end{matrix}
$$

- 我们可以枚举中间的那个点（即 $O$），然后统计满足这四种情况的三元组数量。

- 代码如下：

```cpp

/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

#define int long long

using namespace std;

int n, h[2005][2005], l[2005][2005], ans;

char s[2005][2005];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++ i)     //计算需要行的前缀和
        for (int j = 1; j <= n; ++ j) 
            h[i][j] = h[i][j - 1] + (s[i][j] == 'o');
    
    for (int j = 1; j <= n; ++ j)     //计算需要列的前缀和
        for (int i = 1; i <= n; ++ i)
            l[i][j] = l[i - 1][j] + (s[i][j] == 'o');
            
    for (int i = 1; i <= n; ++ i) 
    	for (int j = 1; j <= n; ++ j) 
    		if (s[i][j] == 'o') {   
    			ans += h[i][j - 1] * l[i - 1][j];  //计算第一种情况下的三元组个数
    			ans += h[i][j - 1] * (l[n][j] - l[i][j]);  //计算第二种情况下的三元组个数
    			ans += (h[i][n] - h[i][j]) * (l[i - 1][j]);  //计算第三种情况下的三元组个数
    			ans += (h[i][n] - h[i][j]) * (l[n][j] - l[i][j]);  //计算第四种情况下的三元组个数
			}
	
	printf("%lld", ans);
    return 0;
}


```



---

## 作者：Genius_Star (赞：2)

### 题意：

给定 $n \times n$ 的矩阵。

要找出满足以下所有条件的三个单元格的数量：

- 三个单元格必须各不相同。

- 三个单元格中都写有 ``o``。

- 恰好有两个单元格位于同一行。

- 恰好有两个单元格位于同一列。

### 思路：

**updata：突然发现自己想复杂了，吐……**

NOIP2022 T1 的超级弱化版……

直接做是 $O(N^6)$ 的，稍微优化以下是 $O(N^4)$，肯定会 T 掉，考虑前缀和优化。

定义：

- $f_{1,i,j}$ 表示第 $i$ 行 $1 \sim j$ 中 ``o`` 的个数。

- $f_{2,i,j}$ 表示第 $i$ 行 $j \sim n$ 中 ``o`` 的个数。

- $f_{3,i,j}$ 表示第 $j$ 列 $1 \sim i$ 中 ``o`` 的个数。

- $f_{4,i,j}$ 表示第 $j$ 列 $i \sim n$ 中 ``o`` 的个数。

那么考虑枚举其中的一个点 $(x,y)$，那么和其在同一列的点的数量为 $f_{3,x-1,y}+f_{4,x+1,y}$，在同一行的点的数量为 $f_{1,x,y-1}+f_{2,x,y+1}$。

那么通过乘法原理组合起来的贡献为 $(f_{3,x-1,y}+f_{4,x+1,y}) \times (f_{1,x,y-1}+f_{2,x,y+1})$。

则我们的答案为：

$$\sum\limits_{x=1}^n\sum\limits_{y=1}^n (f_{3,x-1,y}+f_{4,x+1,y}) \times (f_{1,x,y-1}+f_{2,x,y+1})$$

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=2020;
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
ll n,ans=0;
ll f1[N][N],f2[N][N],f3[N][N],f4[N][N];
bool a[N][N];
char c;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%c",&c);
			if(c=='o')
			  a[i][j]=1;
		}
		getchar();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		  f1[i][j]=f1[i][j-1]+a[i][j];
		for(int j=n;j>=1;j--)
		  f2[i][j]=f2[i][j+1]+a[i][j];
	}
	for(int j=1;j<=n;j++){
		for(int i=1;i<=n;i++)
		  f3[i][j]=f3[i-1][j]+a[i][j];
		for(int i=n;i>=1;i--)
		  f4[i][j]=f4[i+1][j]+a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]){
				ll x=f1[i][j-1]+f2[i][j+1];
				ll y=f3[i-1][j]+f4[i+1][j];
				ans+=x*y;
			}
		}
	}
	write(ans);
	return 0;
}

```

---

## 作者：Register_int (赞：2)

不妨枚举“L”中间的那个 `o`。那么剩下的两个 `o` 只要在对应的行/列中，就是一个合法的方案。设第 $i$ 行的 `o` 数量为 $x_i$，第 $j$ 列为 $y_j$，则枚举到 $(i,j)$ 时，答案就是 $(x_i-1)(y_j-1)$。直接求和即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 10;

int n, x[MAXN], y[MAXN]; char s[MAXN][MAXN];

ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= n; j++) x[i] += s[i][j] == 'o', y[j] += s[i][j] == 'o';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) if (s[i][j] == 'o') ans += (x[i] - 1) * (y[j] - 1);
	}
	printf("%lld", ans);
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

提前预处理每行、每列 $\texttt{o}$ 的数量。

```
.........
...O...o.
.........
.........
.........
...o.....
.........
```

对于上面的三元组，我们称我标注为大写的 $\texttt{o}$ 是三元组的“中心”。（题目给的都是小写，这里只是区分“中心”才用的大写）。

遍历整个矩阵，如果是 $\texttt{o}$ 则把同一行、列 $\texttt{o}$ 的数量（除它自己以外）相乘，得到以这个 $\texttt{o}$ 为“中心”的三元组个数，最后求和。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long //不开 ll 见祖宗
using namespace std;
const int N=2001;
int n,hang[N],lie[N],ans;
string s[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        for(int j=0;j<n;j++)
            if(s[i][j]=='o')
                hang[i]++,lie[j]++;//预处理行、列
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<n;j++)
            if(s[i][j]=='o')
                ans+=(hang[i]-1)*(lie[j]-1);//以 s[i][j] 为“中心”的答案
    cout<<ans;
    return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

# Solution

考虑先枚举 $\texttt{L}$ 形的中间的点，再枚举同一行的点和同一列的点，但是这样时间复杂度是 $O(N^4)$，显然会超时，考虑优化。

统计答案前先预处理一下每行和每列 `o` 的个数，枚举完中间的点把这一行 `o` 的个数和这一列 `o` 的个数乘一下即可。

时间复杂度 $O(N^2)$。

# Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2001;
int row[N],col[N];
char s[N][N];
int n,cnt;

void read() {};
template<class T,class ...Ts>
void read(T& x,Ts&... xs) {
	x=0; bool f=false; char ch=0;
	while (!isdigit(ch) ) f|=(ch=='-'),ch=getchar();
	while (isdigit(ch) ) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	if (f) x=-x; read(xs...);
}
main()
{
	read(n);
	for (int i=0;i<n;i++)
	scanf("%s",s[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (s[i][j]=='o')
				row[i]++,col[j]++;
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (s[i][j]=='o')
				cnt+=(row[i]-1)*(col[j]-1);
	printf("%lld",cnt);
	return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc330_d)

## 思路

一看这题范围可知不能搜索，考虑找规律。

按照题意，输出的值应为：

- 每个至少有两个 `o` 行的个数 $\times$ （这些行 `o` 的个数 $-1$）$\times$ 与这行的 `o` 重合的列的个数 $\times$ （这些列 `o` 的个数 $-1$）。

找到规律后边读入数据边处理，读入一个 `o` 就将记录当前行列的数组中插入当前列行的值（**注意顺序**）。

之后循环查找每列中是否有第 $i\space (1\le i\le N)$ 行的 `o`，有就记录。

最后按照上面说的规律双重循环查找即可。值可能很大，所以记得**开 long long**。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
inline char readc(){//字符快读
	char c=getchar();
	while(c==' '||c=='\n')c=getchar();
	return c;
}
const int N=2010;
int n;
bool flag[N][N];
ll ans;
vector<int>sth[N],stl[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			char ch=readc();
			if(ch=='o'){
				sth[i].pb(j);
				stl[j].pb(i);
			}
		}
	}
	for(int j=1;j<=n;++j){
		for(auto i:stl[j]){
			flag[i][j]=1;
			//j 里有 i。
		}
	}
	for(int i=1;i<=n;++i){
		if(sth[i].size()>=2){//必须至少有两个 o
			for(int j=1;j<=n;++j){
				if(stl[j].size()<2)continue;//同样必须至少有两个 o
				if(flag[i][j])
					ans+=1ll*(sth[i].size()-1)*(stl[j].size()-1);
             //强转 long long。
			}
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/136920660)

---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC330D] Counting Ls
一道简单题。
### 思路
记录每行与每列的 `o` 数量，记为 $r_i,c_i$。  
在这里，我们定义一个点对行与列的共点为点对的中心，假设我们以 $(i,j)$ 为点对的中心，那么以该点为中心的点对数为第 $i$ 行的点数与 第 $j$ 列的点数分别减一的积（因为计数时排除掉中心），即 $(r_i-1)\times (c_j-1)$。枚举每个中心并累加即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
const int N=2e3+10,INF=INT_MAX,Mod=998244353;
void gtmax(ll a,ll &b){if(a>b)b=a;}
void gtmin(ll a,ll &b){if(a<b)b=a;}
ll n,r[N],c[N],ans;
string s[N];
int main()
{
   ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	f(i,1,n)
	{
		cin>>s[i],s[i]=' '+s[i];
		f(j,1,n)r[i]+=(s[i][j]=='o'),c[j]+=(s[i][j]=='o');
	}
	f(i,1,n)f(j,1,n)if(s[i][j]=='o')ans+=(r[i]-1)*(c[j]-1);
	cout<<ans;
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc330/submissions/47922937)

---

## 作者：__Dist__ (赞：0)

### 题目描述

给定一个 $N \times N$ 的网格，由 `o` 和 `x` 组成。

定义三联格为：

- 三联格中的三个单元格是不同的。
- 所有三个单元格中都写有一个 `o`。
- 正好有两个单元格在同一行。
- 正好有两个单元格位于同一列。

### 思路讲解

绕来绕去。

模拟题，没啥好讲的。

我们枚举每一个为 `o` 的单元格，设这个单元格为 $(i,j)$，那么我们可以选择第 $i$ 行为 `o` 的单元格（$(i,j)$ 除外）与第 $j$ 列为 `o` 的单元格（$(i,j)$ 除外）与其搭配。设第 $i$ 行有 $p$ 个 `o`，第 $j$ 列有 $q$ 个 `o`，那么答案数量就增加 $(p - 1)\times(q-1)$。

在开始统计答案之前把每行每列的 `o` 的数量预处理出来。

统计答案输出即可。

### 代码环节

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2005;
int n;
char s[MAXN][MAXN];
int qzh1[MAXN], qzh2[MAXN];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> s[i][j];
			if(s[i][j] == 'o') {
				qzh1[i]++;
				qzh2[j]++;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if(s[i][j] == 'o') {
				ans += (qzh1[i] - 1) * (qzh2[j] - 1);
			}
		}
	}
	cout << ans;
   	while(true);//别抄代码哦
	return 0;
}
```


---

## 作者：1234567890sjx (赞：0)

读错题了。寄。

发现三个点必然是从一个关键点开始，往左 / 右的方向有一个点，往上 / 下的方向上有一个点。

那么枚举这个关键点，用前缀和记录每一行有多少个 `o`，每一列有多少个 `o`，乘法原理计算即可。

时间复杂度 $O(n^2)$。


---

## 作者：coding_goat (赞：0)

# 原题链接

[洛谷](https://www.luogu.com.cn/problem/AT_abc330_d)

[AT](https://atcoder.jp/contests/abc330/tasks/abc330_d)

考场的时候被这道组合数学题撅爆了，写篇题解。

# 1.思路

我们枚举每一个点，设这个被枚举到的点坐标为 $(i_1,j_1)$，那么我们就要找两个点，分别坐标为 $(i_1,j_2)$ 和 $(i_2,j_1)$，且 $(i_1,j_1)$、$(i_1,j_2)$、$(i_2,j_1)$ 这三个点都为 `o`，并保证 $i_1 \ne i_2$ 且 $j_1 \ne j_2$。

那么只要看 $i_1$ 这一行去除自己有多少个 `o`，$j_1$ 这一列去除自己有多少个 `o`，根据乘法原理，两数相乘即可得到这个点有多少种情况。根据加法原理，只需用一个变量将所有点的情况加起来即可得到所有情况。

现在的时间复杂度为：枚举每个点，并对每个点横着+竖着扫一遍，时间复杂度为 $O(n^3)$。

对于 $n\le 2000$ 的数据肯定不行。

那么怎么优化呢？

我们可以预处理出每一行、每一列有多少个 `o`，记录下来。在枚举每个点的时候就可以直接使用了。

# 2.代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T>inline void read(T &xx){
	xx=0;int f=1;
    char c = getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        xx = (xx<<1)+(xx<<3)+(c^48);
        c = getchar();
    }
    xx*=f;
}
#define maxn 2005
int n;
char c[maxn][maxn];
int row[maxn],col[maxn];//行和列
ll ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>c[i][j];
			
			
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) row[i]+=(c[i][j]=='o');
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) col[j]+=(c[i][j]=='o');
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(c[i][j]=='o')
				ans+=(row[i]-1)*(col[j]-1);
	cout<<ans;
	return 0;
}


```

---

## 作者：joe_zxq (赞：0)

# 思路

我们称三个点中位于中间的那个点为“拐弯点”。即“拐弯点”既与其他两点中的一点在同一行，还与另外一点在同一列。

如图，若我们选取红色框出的三个点，那么蓝色箭头指向的是拐弯点。

![](https://cdn.luogu.com.cn/upload/image_hosting/p9wcog42.png)

于是我们可以预处理出每一行和列有多少个 `o`，然后枚举“拐弯点”。令该行 `o` 的数量为 $r$，该列 `o` 的数量为 $c$，则根据乘法原理，以这个点为“拐弯点”的方案数为 $(r-1)(c-1)$。为什么要减一呢？因为要减去当前这个“拐弯点”。然后累加答案即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
char a[2023][2023];
ll c[2023], r[2023];

int main() {
    ll n, ans = 0;
	cin >> n;   
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 'o') {
				c[j]++;
				r[i]++;
			}
		}
	}
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			if (a[i][j] == 'o') {
				ans += (c[j] - 1) * (r[i] - 1);
			}
		}
	}
	cout << ans;
	return 0;
}
```



---

## 作者：CheZiHe929 (赞：0)

# AT_abc330_d 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc330/tasks/abc330_d)

[Luogu](https://www.luogu.com.cn/problem/AT_abc330_d)

### 简要题意

给定一个 $n$ 行 $n$ 列、由字符 `o` 和字符 `x` 组成的单元格矩阵。

问有多少个三联格满足以下条件：

- 三联格中的三个单元格是不同的。

- 所有三个单元格都为 `o`。

- 正好有两个单元格在同一行。

- 正好有两个单元格在同一列。

### 简要思路

我们统计每行每列的字符 `o` 的数量，对于一个单元格 $s_{i,j}$，如果它是 `o`，我们就让答案加上这一行 `o` 的数量减一（排除自身）$\times$ 这一列 `o` 的数量减一（同样排除自身）。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int n;
char s[2005][2005];
int r[2005],c[2005];//每行每列的 o 的数量
int ans;

signed main(){
	std::cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			std::cin>>s[i][j];
			if(s[i][j]=='o'){
				r[i]++;
				c[j]++;//所在行列数量加一
			}
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='o')ans+=(r[i]-1)*(c[j]-1);//更新答案（注意排除自身）

	std::cout<<ans<<endl;
	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc330/submissions/47955894)

[Luogu](https://www.luogu.com.cn/record/136935418)

**THE END.**

**THANK YOU.**

---

## 作者：jqQt0220 (赞：0)

~~D 会 C 不会，我是什么品种的申必~~

场上真的没打出来 C，但是 D 都切了。

## 题意简述

给出一个 $N\times N$ 的字符矩阵，每个字符为 `o` 或 `x`。求出满足以下条件的不同三个单元格组的数量：
- 三个格子不全在同一行或同一列。
- 三个格子中字符都是 `o`。
- 至少两个格子在同一行。
- 至少两个格子在同一列。

## 思路

有点像组合数学的样子。可以开两个 $r,c$ 数组，存每行每列有多少个 `o`，然后枚举每个格子，如果是 `o`，根据乘法原理，就把这一行和这一列除了当前格的 `o` 数量乘起来，然后累加，即 $(r_{i}-1)(c_{i}-1)$。时间复杂度 $\Theta(n^{2})$。注意答案可能很大，所以**不开 long long 见祖宗**。

AC Code:（连头文件一起删去了些奇奇怪怪的东西）
```cpp
#define ll long long
int n;
char s[2010][2010];
int r[2010],c[2010];
int main()
{
    ___();
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>s[i][j];
            if(s[i][j]=='o')
                r[i]++,c[j]++;//计数
        }
    ll as=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s[i][j]=='o')
                as+=(r[i]-1)*(c[j]-1);//累加答案
        }
    }
    cout<<as<<endl;
    return 0;//完美结束 QwQ
}
```

---

## 作者：无钩七不改名 (赞：0)

简单计数题。

直接枚举中间点，可以发现另外两个和它能组成的三元组的点一定是一个与它同列一个与它同行。我们统计第 $i$ 行的 ``o`` 的数量为 $h_i$，第 $j$ 列的 ``o`` 的数量为 $l_i$。那么如果当前点 $(i,j)$ 为 ``o``，该点为中心的三元组数量便为 $(h_i-1)\times(l_j-1)$。累加答案即可。

### 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2005;

int n,a[N][N],ans_h[N],ans_l[N];
long long ans;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();
	for(int i(1);i<=n;++i)
		for(int j(1);j<=n;++j){
			char ch;scanf(" %c",&ch);
			if(ch=='o')a[i][j]=1,++ans_h[i],++ans_l[j];
		}
	for(int i(1);i<=n;++i)
		for(int j(1);j<=n;++j)
			if(a[i][j]){
				//cout<<i<<" "<<j<<" ans:"<<(ans_h[i]-1)*(ans_l[j]-1)<<'\n';
			//	cout<<ans_h[i]<<" "<<ans_l[j]<<'\n';
				ans+=(ans_h[i]-1)*(ans_l[j]-1);
			}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：xu222ux (赞：0)

## 思路

题目要求构成一个直角三角形。

| $o$ | $o$ |
| :----------: | :----------: |
| $o$ | $x$ |

直角三角形的话，只需定住直角点就可以确定其他两个点的行或列了。

这样就简单了。

每行做一个关于 $o$ 的前缀和，列也做一个。每次定住直角点，扫一下前缀和就行。

~~第四题真的是越出越水~~

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[2003][2003];
long long sum[2003][2003][2];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			sum[i][j][0]=sum[i][j-1][0];
			sum[i][j][1]=sum[i-1][j][1];
			if(a[i][j]=='o'){
				sum[i][j][0]++,sum[i][j][1]++;
			}
		}
	long long ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='o'){
				long long s,x,z,y;//上下左右
				s=sum[i-1][j][1];
				x=sum[n][j][1]-sum[i][j][1];
				z=sum[i][j-1][0];
				y=sum[i][n][0]-sum[i][j][0];
				ans+=s*y+x*y+s*z+x*z;
			}
		}
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：Crazyouth (赞：0)

**分析**

注意到题目所求的三元组即是一个 L 形，那么我们可以枚举 L 形的中心（这样可以保证不重不漏）。那么在它的一列与它的一行需要各选一个做为 L 的延伸，也就是说一个 `o` 的贡献就是它所在的一列的 `o` 数量减一，乘它所在的一行的 `o` 数量减一。累加所有贡献就是答案，并且**不开 long long 见祖宗**。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s[2010];
int ctbh[2010],ctbl[2010];
signed main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=' '+s[i];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(s[i][j]=='o') ctbh[i]++,ctbl[j]++;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(s[i][j]=='o') ans+=(ctbh[i]-1)*(ctbl[j]-1);
	cout<<ans;
	return 0;
}

---

## 作者：time_keeper (赞：0)

# 题意简述
给定一个 $n × n$ 的网格，网格中包含 $o$ 和 $x$ 两种字符

$o$ 表示一个点，$x$ 表示空白。现在要求计算出以每个 $o$ 为中心的三元组数量

其中三元组由三个 $o$ 组成，并且这三个 $o$ 分别有两个位于同一行或同一列上。
# 思路

当我们考虑以某个 $o$ 为中心的三元组时，我们可以观察到以下几点：

- 以当前 $o$ 所在的行为基础，可以选择任意两列。

- 以当前 $o$ 所在的列为基础，可以选择任意两行。

因此，以当前 $o$ 为中心的三元组数量，即为满足上述条件的行列组合数之积。

假设当前 $o$ 所在的行有 `row_cnt[i]` 个 $o$，当前 $o$ 所在的列有 `col_cnt[j]`个 $o$，则以当前 $o$ 为中心的三元组数量为：


> `row_cnt[i] * col_cnt[j]`

但是这样计算会存在重复计数的问题，因为对于同一行或同一列上的其他 $o$，它们也会和当前 $o$ 形成新的三元组。

因此，我们需要减去重复计算的部分。

在当前行上，除了当前 $o$ 之外还有 `row_cnt[i]-1`个 $o$，在当前列上，除了当前 $o$ 之外还有 `col_cnt[j]-1` 个 $o$。因此，我们需要减去重复计数的部分为：


> `(row_cnt[i] - 1) * (col_cnt[j] - 1)`

最后，因为我们在减去重复计数的时候，把以当前 $o$ 为中心的三元组数量减少了两次，所以需要加上 $1$ 来补偿这部分减少的数量。

综上所述，以当前 $o$ 为中心的三元组数量为：


`row_cnt[i] * col_cnt[j] - (row_cnt[i] + col_cnt[j]) + 1`

剩下的见代码注释

# 代码
```cpp
#include <iostream>
using namespace std;

const int N = 5e3;  // 定义最大网格大小为5000
#define int long long  // 使用long long类型

int row_cnt[N], col_cnt[N];  // 分别记录每行和每列'o'的数量
char board[N >> 1][N >> 1];  // 网格板

signed main() {
    int n;
    cin >> n;  // 输入网格大小

    // 读取网格状态并统计每行和每列的'o'数量
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch;
            cin >> ch;
            board[i][j] = ch;

            if (ch == 'o') {
                row_cnt[i]++;
                col_cnt[j]++;
            }
        }
    }

    int ans = 0;  // 记录满足条件的三元组数量

    // 遍历网格，计算以每个'o'为中心的三元组数量
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i][j] == 'o') {
                // 使用数学公式计算以(i,j)为中心的三元组数量
                ans += row_cnt[i] * col_cnt[j] - (row_cnt[i] + col_cnt[j]) + 1;
            }
        }
    }

    cout << ans;  // 输出结果
    return 0;
}
```

---

## 作者：daliuxiaoliu (赞：0)

### 题意简述

给定一个 $n \times n$ 的字符矩阵，求其中有多少个顶点都是 `o` 的直角三角形。

### 思路

先写出暴力做法，再一步步优化。

#### 朴素做法

直接枚举每一个点，枚举一个点用 $O(n^2)$，总共就用了 $O(n^6)$，这个做法会TLE。

#### 优化

对于每一个直角三角形，只用枚举直角所在的顶点，其它两个顶点都不用枚举所在的二维坐标，只用枚举一维即可。

此时，时间复杂度降为 $O(n^4)$，但还是不够。

注意这里是使用的 $O(n^2)$ 的枚举去找每一个顶点能组成的直角三角形，但这里完全可以用排列组合代替。直接将另外两个顶点的可能的情况数乘起来，就能得到每一个顶点所对应的直角三角形的个数，对于每一个点，时间复杂度为 $O(n)$。

经过这两个优化后，时间复杂度为 $O(n^3)$，就差优化最后一个 $O(n)$ 了。

最后的这个 $n$，还可以在每一个顶点的处理进行优化。我们可以发现，每行或列都被算了很多次，但其实算一次就够了。所以只用预处理出每一行和每一列中都有几个 `o`，计算时就可以变成 $O(1)$，预处理用 $O(n^2)$。这里设每一行有 $cntx_i$ 个 `o`， 每一列有 $cnty_i$ 个，那么对于在第 $i$ 行第 $j$ 列的点，它对应的直角三角形就有 $(cntx_i - 1) \times (cnty_i - 1)$ 个。

现在，时间复杂度就优化到了 $O(n^2)$，可以通过此题。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
char a[2005][2005];
int cntx[2005];
int cnty[2005];
long long ans = 0;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++) {
            cin >> a[i][j];
            if (a[i][j] == 'o') cntx[i] ++, cnty[j] ++; // 计数
        }
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (a[i][j] == 'o')
                ans += (cntx[i] - 1) * (cnty[j] - 1); // 排列组合求个数，O(1)
    cout << ans;
    return 0;
}
```

---

