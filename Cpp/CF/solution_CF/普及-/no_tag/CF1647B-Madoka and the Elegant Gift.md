# Madoka and the Elegant Gift

## 题目描述

Madoka's father just reached $ 1 $ million subscribers on Mathub! So the website decided to send him a personalized award — The Mathhub's Bit Button!

The Bit Button is a rectangular table with $ n $ rows and $ m $ columns with $ 0 $ or $ 1 $ in each cell. After exploring the table Madoka found out that:

- A subrectangle $ A $ is contained in a subrectangle $ B $ if there's no cell contained in $ A $ but not contained in $ B $ .
- Two subrectangles intersect if there is a cell contained in both of them.
- A subrectangle is called black if there's no cell with value $ 0 $ inside it.
- A subrectangle is called nice if it's black and it's not contained in another black subrectangle.
- The table is called elegant if there are no two nice intersecting subrectangles.

For example, in the first illustration the red subrectangle is nice, but in the second one it's not, because it's contained in the purple subrectangle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/527c997c3730172d58419587c380220df58d0b35.png)Help Madoka to determine whether the table is elegant.

## 说明/提示

In the second test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/274bbf1f30d832fb82dd64034e57adcb4cd9b242.png)In the fourth test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/6dc815ec1b802f77b63db126c6131ed14481d644.png)

## 样例 #1

### 输入

```
5
3 3
100
011
011
3 3
110
111
110
1 5
01111
4 5
11111
01010
01000
01000
3 2
11
00
11```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：BMTXLRC (赞：1)

转换题目的意思就可以得到题目要求是：

**求一个矩阵中所有黑色连通块是否都为矩形。**

如果直接去 dfs 看每个连通块可能会比较麻烦，我们考虑在什么情况下他不是矩形。

很显然，如果有一个“凸起”这个连通块就不是矩形，什么叫凸起呢，就是一下四种情况之一：

```
01 10 11 11
11 11 01 10
```

不难发现只要这个矩阵中的任意一个 $2\times 2$ 矩阵中的 $0$ 个数是 $1$ 个，那么这个矩阵就不符合题意。

实现代码如下：

```cpp
//CF1647-B
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int T,n,m;
char a[N][N];
int check(int x,int y){
    int ans=0;
    if(a[x][y]=='0') ans++;
    if(a[x+1][y]=='0') ans++;
    if(a[x][y+1]=='0') ans++;
    if(a[x+1][y+1]=='0') ans++;
    return ans;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        for(register int i=1;i<=n;i++){
            scanf("%s",a[i]+1);
            a[i][m+1]='\0';
        }
        bool ok=true;
        for(register int i=1;i<n;i++){
            if(!ok) break;
            for(register int j=1;j<m;j++){
                int ans=check(i,j);
                if(ans==1){
                    ok=false;
                    break;
                }
            }
        }
        printf(ok?"YES\n":"NO\n");
    }
}
```

---

## 作者：windflower (赞：1)

简要题意：
>给定一个由 `0` 和 `1` 描述的矩形，称只包含 `1` 的矩形为黑矩形，问是否任意两个不包含于其它黑矩形的黑矩形不相交。

仔细分析可以发现，若是两个最大的黑矩形相交，那么必定存在一个 $2\cdot 2$ 的矩形含有三个 1 和一个 0 ，因此我们只需要判断是否存在这样的子矩形即可。  
附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
char a[105][105];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=0;i<n;i++)scanf("%s",a[i]);
		for(int i=0;i<n-1;i++)
			for(int j=0;j<m-1;j++)
			  	if(a[i][j]+a[i][j+1]+a[i+1][j]+a[i+1][j+1]-'0'*4==3){
			  		cout<<"NO"<<endl;
			  		goto end;
				}
		cout<<"YES"<<endl;
		end:;
	}
}
```


---

## 作者：Elgo87 (赞：1)

**题意**：

你有一个 $n\times m$ 的 $01$ 矩阵，现在定义：

- 一个子矩阵内若全都是 $1$，则这个矩阵是黑色的；
- 子矩阵 $A$ 的任意一个元素都在子矩阵 $B$ 之内，且至少存在 $B$ 的一个元素不在 A 之内，则称 $B$ 包含 $A$；
- 若一个黑色的子矩阵 $A$ 不被任意一个黑色的子矩阵包含，则称这个子矩阵 $A$ 是 $\texttt{nice}$ 的。
- 若两个子矩阵有公共点，且两个子矩阵互不包含，则这两个矩阵是相交的。

你的任务是，给你一个 $01$ 矩阵，判断是否存在两个 $\texttt{nice}$ 的矩阵相交。

**观察性质：**

显然，不相邻（指上下左右四个方向没有接触）的块（指数字为 $1$ 的连通块）是不可能有 $\texttt{nice}$ 矩阵相交的，所以我们可以对于每个连通块分别处理。

我们发现，如果连通块是一个矩形，那么这个连通块有且仅有一个 $\texttt{nice}$ 矩阵，所以不可能有两个矩阵相交。

但如果不是矩形，我们可以很容易地在其中找到一个子矩阵和一个 $\texttt{nice}$ 矩阵（读者不妨自己试试），所以如果遇到这种连通块，直接输出 $\texttt{NO}$ 就好，于是这个问题被解决了。

**写法：**

那么如何判断一个连通块是否是一个矩形呢？

首先 $\texttt{DFS}$ 一下连通块，找出 $sx,sy,ex,ey$（分别代表最小的 $x$ 坐标、最小的 $y$ 坐标、最大的 $x$ 坐标、最大的 $y$ 坐标），然后判断以 $(sx,sy)$ 为左上角、$(ex,ey)$ 为右下角的矩阵中是否都是 $1$ 即可。

判断 $1$ 的复杂度是 $\mathcal O(n^2)$ 的，无法通过此题。

但是判断都是 $1$ 时，我们想到了二维前缀和。我们只需要比较这部分的二维前缀和和矩阵面积是否相等，就解决了判断这个连通块是否是矩形的问题。

**参考代码：**

```cpp
# include <bits/stdc++.h>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define endl putchar('\n')
# define space putchar(' ');
# define begining {
# define ending }
# define int long long
using namespace std;

inline int read() {
	int num = 0; int nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
	return num * nev;
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}

int n, m;
int  b[105][105] = {};
int  s[105][105];
int  vis[105][105] = {};
int dx[4] = {0, 0, -1, 1}; //四个方向
int dy[4] = {1, -1, 0, 0}; //四个方向
void dfs(int x, int y, int& sx, int& sy, int& ex, int& ey) {
	sx = min(x, sx);
	sy = min(y, sy);
	ex = max(x, ex);
	ey = max(y, ey);
	for (int i = 0; i < 4; i ++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (xx > 0 && yy > 0 && xx <= n && yy <= m && vis[xx][yy]) {
			vis[xx][yy] = 0;
			sx = min(xx, sx);
			sy = min(yy, sy);
			ex = max(xx, ex);
			ey = max(yy, ey);
			dfs(xx, yy, sx, sy, ex, ey);
		}
	}
}

void solve() {
	n = read(), m = read();
	for (int i = 1; i <= n; i ++) for (int j = 1; j <= m; j ++) { char ch; cin >> ch; vis[i][j] = b[i][j] = ch - '0'; } // 读入矩阵
	for (int i = 1; i <= n; i ++) for (int j = 1; j <= m; j ++) { //计算二维前缀和
		s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + b[i][j];
	} 
	
	for (int i = 1; i <= n; i ++) { //找连通块
		for (int j = 1; j <= m; j ++) {
			int sx=1e9, ex=-1e9, sy=1e9, ey=-1e9;
			if (vis[i][j]) {
				dfs(i, j, sx, sy, ex, ey);
				if ((ey-sy+1)*(ex-sx+1) != s[ex][ey] - s[ex][sy-1] - s[sx-1][ey] + s[sx-1][sy-1]) { // 如果有非矩形的连通块，输出 NO 然后退出即可
					puts("NO");
					return ;
				}
			}
		}
	}
	puts("YES");
}


signed main()
{
	int T = read();
	while (T --) solve();
	return 0;
}

 
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1647B](https://www.luogu.com.cn/problem/CF1647B)

* **【题目翻译】**

给定一个 $n\times m$ 的只包含 $0/1$ 的矩阵，问是否能找到两个只包含 $1$ 的极大子矩阵，使得它们相交但是不完全重合。

* **【解题思路】**

题目条件满足当且仅当可以找到一个 $2\times 2$ 子矩阵，使得它只包含 $3$ 个 $1$。

因为如果找到了，它就会形如：

![](https://cdn.luogu.com.cn/upload/image_hosting/vxf0west.png)

显然不可能用一个极大矩形覆盖它，也不可能用两个不相交的极大矩形覆盖它，只可能用两个相交的极大矩形覆盖它。


* **【代码实现】**

```cpp
#include <iostream>
#include <array>
 
using namespace std;
 
array<array<char,100>,100> table;
 
int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int line,row;
		cin>>line>>row;
		for(int i=0;i<line;i++)
			for(int j=0;j<row;j++)
				cin>>table[i][j];
		for(int i=1;i<line;i++)
			for(int j=1;j<row;j++)
				if(table[i][j]+table[i-1][j]+table[i][j-1]+table[i-1][j-1]-4*'0'==3)
				{
					cout<<"No";
					goto nextcase;
				}
		cout<<"Yes";
		nextcase:cout<<'\n'; 
	}
	return 0;
}
 
```

---

## 作者：清烛 (赞：0)

题面较复杂，这里给出简要翻译：

给定一个 $n\times m$ 网格，每格为黑色（1）或白色（0）。判断这个网格内是否**不含**两个相交的极大矩形。具体可以上 CF 看一下题图和样例方便理解。

发现只要存在一个*三角形*就有两个交叉的情况，例：

```
10	notice that 1  and      are intersecting
11              1      1 1
```

就是存在的。所以判一下四个朝向的三角形即可。

```cpp
const int maxn = 205;
char a[maxn][maxn];
int n, m;

int main() {
    int T; read(T);
    while (T--) {
        read(n, m);
        FOR(i, 1, n) read(a[i] + 1);
        bool flg = 0;
        FOR(i, 1, n) FOR(j, 1, m) {
            if (j < m && a[i][j] == '1' && a[i][j + 1] == '1') {
                if (i > 1) flg |= ((a[i - 1][j] == '1' && a[i - 1][j + 1] == '0') || (a[i - 1][j] == '0' && a[i - 1][j + 1] == 1));
                if (i < n) flg |= ((a[i + 1][j] == '1' && a[i + 1][j + 1] == '0') || (a[i + 1][j] == '0' && a[i + 1][j + 1] == 1));
            }
            if (i < n && a[i][j] == '1' && a[i + 1][j] == '1') {
                if (j > 1) flg |= ((a[i][j - 1] == '1' && a[i + 1][j - 1] == '0') || (a[i][j - 1] == '0' && a[i + 1][j - 1] == '1'));
                if (j < m) flg |= ((a[i][j + 1] == '1' && a[i + 1][j + 1] == '0') || (a[i][j + 1] == '0' && a[i + 1][j + 1] == '1'));
            }
        }
        print(flg ? "No" : "Yes");
    }
    return output(), 0;
}
```

---

## 作者：风羽跃 (赞：0)


题意转化：给定一个矩形，判断连通块的形状是否都为矩形。

简单解释一下，题目中所述“nice”矩形就是极大矩形。

显然一个矩形联通块只含有一个“nice”矩形，反过来，如果一个连通块内任意两个极大矩形不交，则只能是矩形联通块。

如何判断是否存在非矩形呢？单调栈？悬线？

显然非矩形连通块一定会出现一个四宫格内出现三个 $1$ 的情况，遍历矩形判断即可。

Code：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>

#define For(i,l,r) for(int i=(l);i<=(r);i++)

const int N=105,mod=0;

using namespace std;

int n,m;
char mp[N][N];

int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int main()
{
	int T=read();
	while(T--){
		n=read(),m=read();
		bool flag=true;
		For(i,1,n){
			For(j,1,m){
				cin>>mp[i][j];
				if(i>1&&j>1){
					int cnt=mp[i][j]+mp[i-1][j]+mp[i][j-1]+mp[i-1][j-1]-'0'*4;
					if(cnt==3) flag=false;
				}
			}
		}
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}

```


---

## 作者：Toorean (赞：0)

## 题意
给出一个矩阵 $arr$，求 $arr$ 中元素为 $1$ 形成的部分，是否有两个相交矩阵（即拥有重复元素）？
## 思路
如果拥有重复元素，那么 $arr$ 中元素为 $1$ 形成的一个个部分，就不是一个规整的矩形。因此，模拟即可。这里有一个技巧，不要判断为 $1$ 时的值，而是判断为 $0$ 的时候，可以省去大量码量。
## AC Code 
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

#define LL long long
#define MAXN 110 // Datas MAX
#define INF 0x3f3f3f3f
#define mpa make_pair
#define fir first
#define sec second
#define max(x,y) (x > y ? x : y)
#define min(x,y) (x < y ? x : y)
#define openFile(_FileName) freopen (_FileName".in", "r", stdin); freopen (_FileName".out", "w", stdout)
#define yon(x) ((x) ? puts ("YES") : puts ("NO"))
#define ffor(_INDEX,l,r) for (int _INDEX = (l); _INDEX <= (r); _INDEX++)
#define _for(_INDEX,l,r,_Value) for (int _INDEX = (l); _INDEX <= (r); _INDEX += _Value)
#define rfor(_INDEX,l,r) for (int _INDEX = (l); _INDEX >= (r); _INDEX --)
#define _rfor(_INDEX,l,r, _Value) for (int _INDEX = (l); _INDEX >= (r); _INDEX -= _Value)

using namespace std;

int T, n, m;
int f[MAXN][MAXN];
char mp[MAXN][MAXN];

template <typename T> inline void read (T &x) {
    T f = 1; x = 0;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') { f = -1; };
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar ();
    }
    x *= f;
}

template <typename T, typename ... Args> inline void read (T &t, Args&... args) {
    read(t), read(args...);
}

bool canUse (int x, int y) {
    return x >= 1 && y >= 0 && x <= n && y < m;
}

bool solve (int n, int m) {
    memset (mp, 0, sizeof (mp));
    
    ffor (i, 1, n) {
        ffor (j, 1, m) {
             cin >> mp[i][j];
             mp[i][j] -= '0';
        }
    }
    
    ffor (i, 1, n) {
        ffor (j, 1, m) {
            if (!mp[i][j]) {
                if (mp[i - 1][j] && mp[i][j - 1] && mp[i - 1][j - 1]) {
                    return false;
                }
                if (mp[i + 1][j] && mp[i][j + 1] && mp[i + 1][j + 1]) {
                    return false;
                }
                if (mp[i + 1][j] && mp[i][j - 1] && mp[i + 1][j - 1]) {
                    return false;
                }
                if (mp[i - 1][j] && mp[i][j + 1] && mp[i - 1][j + 1]) {
                    return false;
                }
                
            }
        }
    }
    
    return true;
}

signed main (void) {
    
    // cin.tie (0);
    // cout.tie (0);
    
    read (T);
    while (T--) {
        read (n, m);
        yon (solve (n, m));
    }
    
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

其实本身很简单，如果存在一个 $2\times2$ 的子矩形，黑色的个数恰好为 $3$ 个，礼物就不优雅；否则就优雅。

但是我在考场上没能想到这一点，于是我想出了一个方法。

对于所有的 $i,l,r(1\le i\le n\operatorname{and}1\le l\le r\le m)$：

如果满足对于所有的 $j(l\le j\le r)$，都有 $a[i][j]=1$，那么，必须要满足对于所有的 $j(l<j\le r)$ 都有 $a[i-1][j]=a[i-1][j-1]\operatorname{and}a[i+1][j]=a[i+1][j-1]$。

很明显，还是第一个解法更简单的多，但我还是想提供第二种解法。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100
int t;
int n;
int m;
int a[max_n+2][max_n+2];
int ok1;
int ok2;
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1647B_1.in","r",stdin);
	freopen("CF1647B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;++i){
			char s[max_n+2];
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)a[i][j]=s[j]-'0';
		}
		ans=true;
		for(int i=1;i<=n;++i){
			ok1=-1;
			ok2=-1;
			for(int j=1;j<=m;++j){
				if(!a[i][j]){
					ok1=ok2=-1;
					continue;
				}
				if(a[i-1][j]!=ok1&&ok1!=-1){
					ans=false;
					break;
				}
				if(a[i+1][j]!=ok2&&ok2!=-1){
					ans=false;
					break;
				}
				ok1=a[i-1][j];
				ok2=a[i+1][j];
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71288321)

By **dengziyue**

---

## 作者：JS_TZ_ZHR (赞：0)

## 题意：

给定一个 $01$ 方阵，问是否有两个相交的极大全 $1$ 子矩阵。

## 题解：

如果存在两个相交的极大全 $1$ 子矩阵的话，那么在几何图形上含 $1$ 的格子就会出现 “凸起”，如题面里的图，最右侧那个就是。

![](https://subdomains.codeforces.ml/espresso/2f929e91f6170f9a4f394ef28fd36640c776b05f.png)

判断方法很简单，有这样形状的话，就一定存在一个 $2\times 2$ 的子矩阵中有 $3$ 个 $1$。

```cpp
include<bits/stdc++.h>
#define N 1000005
#define int long long 
using namespace std;
int T,n,m;
char s[1005][1005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		bool flag=1;
		for(int i=1;i<=n;i++)cin>>s[i]+1;
		for(int i=1;i<n;i++){
			for(int j=1;j<m;j++){
				if(s[i][j]-'0'+s[i+1][j]-'0'+s[i][j+1]+s[i+1][j+1]-'0'-'0'==3)flag=0;
			}
		}
		puts(flag?"YES":"NO");
	}
} 
```


---

