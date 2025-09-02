# [ABC390C] Paint to make a rectangle

## 题目描述

给定一个 $H$ 行 $W$ 列的网格。  
以下将从上往下第 $i$ 行 $(1 \leq i \leq H)$、从左往右第 $j$ 列 $(1 \leq j \leq W)$ 的格子称为格子 $(i, j)$。  
网格的状态由 $H$ 个长度为 $W$ 的字符串 $S_1, S_2, \ldots, S_H$ 表示如下：

- 若 $S_i$ 的第 $j$ 个字符是 `#`，则格子 $(i, j)$ 被涂黑。
- 若 $S_i$ 的第 $j$ 个字符是 `.`，则格子 $(i, j)$ 被涂白。
- 若 $S_i$ 的第 $j$ 个字符是 `?`，则格子 $(i, j)$ 未被涂色。

高桥君希望通过将未被涂色的格子分别涂白或涂黑，使得所有黑色格子形成一个矩形。  
更具体地说，需要存在四个整数 $(a, b, c, d)$ $(1 \leq a \leq b \leq H, 1 \leq c \leq d \leq W)$，满足以下条件：

> 对于所有格子 $(i, j)$ $(1 \leq i \leq H, 1 \leq j \leq W)$：  
> - 若满足 $a \leq i \leq b$ 且 $c \leq j \leq d$，则格子 $(i, j)$ 被涂黑。  
> - 否则，格子 $(i, j)$ 被涂白。

请判断是否存在这样的涂色方案。

## 说明/提示

### 约束条件

- $1 \leq H, W \leq 1000$
- $H$ 和 $W$ 为整数
- $S_i$ 是由 `#`、`.`、`?` 组成的长度为 $W$ 的字符串
- 至少存在一个被涂黑的格子

### 样例解释 1

网格的初始状态如下（`?` 表示未涂色的格子）：  
![](https://img.atcoder.jp/abc390/85b372e4c19d09eb4f842736d40de3b9.png)  
将格子 $(1, 3)$、$(2, 2)$、$(2, 4)$ 涂黑，并将格子 $(3, 1)$、$(3, 5)$ 涂白后，所有黑色格子可形成如下矩形：  
![](https://img.atcoder.jp/abc390/535404bb0565608276c41ef49d8f2336.png)  
因此输出 `Yes`。

### 样例解释 2

若要使所有黑色格子形成矩形，必须将格子 $(2, 2)$ 涂黑，但该格子已被涂白。因此无法满足条件，输出 `No`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 5
.#?#.
.?#?.
?...?```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3
?##
#.#
##?```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1
#```

### 输出

```
Yes```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc390_c)

### 题意

找一个长方形，判断其所有格子是否全部为黑色，且没有多余的黑色格子。其中若 $(i,j)$ 点为 `?`，可以将其涂为任意黑色或者白色。

### 思路

由于只有一个长方形，可以求出这个长方形四条边最左侧的黑色格子纵坐标 $U$，最下侧的黑色格子纵坐标 $D$，最左侧的黑色格子横坐标 $L$，最右侧的黑色格子横坐标 $R$。

这样就得到了一个长方形，其左上角为 $(U,L)$，右下角为 $(D,R)$。然后可以遍历这个长方形，由于字符为 `?` 的点可以涂成黑色，就将其算作黑色。所以只需判断长方形内有无白色即可，无则输出 `Yes`，有则输出 `No`。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10;
char s[N][N];
signed main(){
	int n=read(),m=read();
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	int u=INT_MAX,d=INT_MIN,l=INT_MAX,r=INT_MIN;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(s[i][j]=='#'){
				u=min(u,i),d=max(d,i);
				l=min(l,j),r=max(r,j);
			}
	for(int i=u;i<=d;++i)
		for(int j=l;j<=r;++j)
			if(s[i][j]=='.')
				return printf("No\n"),0;
	printf("Yes\n");
	return 0;
}
```

---

## 作者：ryf2011 (赞：7)

# 题目思路
我们考虑暴力。

暴力查找每一个单元格，再此过程中，寻找存在黑色单元格的最小和最大列数序号，以及存在黑色单元格的最小和最大行数序号。

寻找完成后，我们就查找最小与最大行数和最小与最大列数这个区间内的所有单元格，由于不能修改已经确定的单元格，因此，如果找到了白色单元格，说明无论如何都无法通过填充将黑色单元格变成矩形，那么此时就确定不可行。

如果在查找完成后，仍未发现白色单元格，由于可以修改未知单元格，所以此时可以通过修改未知单元格使黑色单元格呈现出矩形，那么此时就确定可行。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int h,w,mincol=2147483647,maxcol,minrow=2147483647,maxrow; //mincol:黑色单元格最小列数；maxcol:黑色单元格最大列数；minrow:黑色单元格最小行数；maxrow:黑色单元格最大行数 
char s[1005][1005];
int main(){
	scanf("%d %d",&h,&w);
	for(int i=1;i<=h;i++){
		scanf("%s",s[i]+1);
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(s[i][j]=='#'){ //更新最大、最小值 
				minrow=min(minrow,i);
				maxrow=max(maxrow,i);
				mincol=min(mincol,j);
				maxcol=max(maxcol,j);
			}
		}
	}
	for(int i=minrow;i<=maxrow;i++){ //在此区间内查找 
		for(int j=mincol;j<=maxcol;j++){ //在此区间内查找 
			if(s[i][j]=='.'){ //如果出现白色单元格，说明不可能，退出循环 
				printf("No\n");
				return 0;
			}
		}
	}
	printf("Yes\n");
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：封禁用户 (赞：5)

### 思路：
直接暴力，用四个变量记录当前最小和最大的 $x,y$ 坐标（一定要枚举黑色的，作者在这里卡了    $10$ 分钟），枚举这个空间内所有字符，因为如果这个空间里有白色，说明无论如何都无法用黑色组成一个矩形，所以出现白色就退出，全是黑色或有
`
?
`
则正确.  
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n,m,minx=2147483647,miny=2147483647,maxx=0,maxy=0;
	cin>>n>>m;
	char a[1005][1005];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(a[i][j]=='#') {//一定是黑色（#），不是（？）
				minx=min(minx,i);miny=min(miny,j);//记录最小x,y
				maxx=max(maxx,i);maxy=max(maxy,j);//记录最大x,y
			}
	for(int i=minx;i<=maxx;i++)
		for(int j=miny;j<=maxy;j++)
			if(a[i][j]=='.') {//判断是否为白色
				cout<<"No";
				return 0;
			}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：FlowerAccepted (赞：5)

## 解题思路

首先，我们发现，这个矩形必须包括所有已知的黑色网格（`#`）

那么，在最小化这个矩形的情况下（这时最容易得到解），

- 矩形的上边就是最上面黑色网格的 $i$，
- 矩形的下边就是最下面黑色网格的 $i$，
- 矩形的左边就是最左面黑色网格的 $j$，
- 矩形的右边就是最右面黑色网格的 $j$。

然后在这个框中遍历，看看有没有白色网格即可。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring> // 我的电脑没有万能头QwQ
using namespace std;

char a[1005][1005]; // 多开一点

int main() {
    int h, w, mini = 1005, maxi = 0, minj = 1005, maxj = 0; // 存上下左右边
    string t;
    cin >> h >> w;
    for (int i = 1; i <= h; i ++) {
        cin >> t;
        for (int j = 1; j <= w; j ++) {
            a[i][j] = t[j - 1]; // 字符串下标从0开始，数组我从1开始用
            if (a[i][j] == '#') { // 更新上下左右边
                mini = min(mini, i);
                maxi = max(maxi, i);
                minj = min(minj, j);
                maxj = max(maxj, j);
            }
        }
    }
    for (int i = mini; i <= maxi; i ++) {
        for (int j = minj; j <= maxj; j ++) {
            if (a[i][j] == '.') { // 判断
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}

```
至此，此题 Accepted。

## 复杂度分析
这个算量最大的是输入和检测上下左右边，所以复杂度为 $O(HW)$。

---

## 作者：TitleGodofWar (赞：4)

## [ABC390C] Paint to make a rectangle
[题目传送门](https://www.luogu.com.cn/problem/AT_abc390_c)
## 题意  

   有一个 $ H $ 行 $ W $ 列的网格，若 $(i,j)$ $(1\le i\le H,1\le j\le W)$ 表示网格中第 $ i $ 行，第 $ j $ 列的单元格。
对于每个网格，有 `.` 、`#`、`?`三种状态：  
 
>1.若该网格的状态为 `.` 则 $(i,j)$ 被涂成白色；  
>2.若该网格的状态为 `#` 则 $(i,j)$ 被涂成黑色；  
>3.若该网格的状态为 `?` 则 $(i,j)$ 尚未涂黑；　　

   将每个 `?` 单元格涂成黑色或白色，使得**所有的**黑色单元格组成一个矩形。  
$H$ , $W$ $\le 1000$。  

   题目中要求**所有的**黑色单元格组成一个矩形，所以在已经确定的黑色单元格 `#` 出现的上下左右界所框定的矩形中，必须全为 `?` 与 `#` ；换句话说，在这个矩形中若是出现 `.` 就可以肯定不存在满足题目要求的情况。    

   所以，我们可以在输入时找出黑色单元格 `#` 出现的上下左右界，再遍历这个矩形，判断是否出现了 `.`，最后输出答案就可以了。
## CODE:  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
char a[1005][1005];
int n,m;
int mu=oo,md=-oo,ml=oo,mr=-oo;//初始化
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]=='#'){
                mu=min(mu,i);//找出上下左右界
                ml=min(ml,j);
                md=max(md,i);
                mr=max(mr,j);
            }
        }
    }
    for(int i=mu;i<=md;i++){
        for(int j=ml;j<=mr;j++){
            if(a[i][j]=='.'){//出现'.'就直接输出No
                cout<<"No"<<"\n";
                return 0;
            }
        }
    }

    cout<<"Yes"<<"\n";
    return 0;
}

```
[AC 记录](https://www.luogu.com.cn/record/200570371)  
蒟蒻的第一篇题解，点个赞支持一下呗。 qwq。

---

## 作者：high_sky (赞：2)

## 思路
大概是找出所能得到黑色部分的最小矩阵，然后枚举矩阵中的每一个值，看有没有已经涂成白色了的。

一些细节就是分别找出左上、左下、右上、右下四个角落的黑色坐标。然后对枚举矩阵开始的点以及结束的点进行计算即可。

可能要问，为什么要取 $4$ 个点？

我个人的当时的理解是这样的：如果只取左上、右下的点会有一种情况，使得它的矩阵判断失误：
```
..#.#
.#..#
```

只看左上、右下的点就会导致左下的那点没有包括到，导致答案出错。

代码不难，如下：
```cpp
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>
#define N 1005
using namespace std;
int n,m;
char a[N][N];
int ltx,lty,rtx,rty,lbx,lby,rbx,rby;
signed main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i ++)
		scanf("%s",a[i] + 1);
	for (int i = 1;i <= n;i ++) {
		if (ltx || lty) break;
		for (int j = 1;j <= m;j ++)
			if (a[i][j] == '#') {
				ltx = i,lty = j;
				break;
			}
	}
	for (int i = n;i;i --) {
		if (lbx || lby) break;
		for (int j = 1;j <= m;j ++)
			if (a[i][j] == '#') {
				lbx = i,lby = j;
				break;
			}
	}
	for (int i = 1;i <= n;i ++) {
		if (rtx || rty) break;
		for (int j = m;j;j --)
			if (a[i][j] == '#') {
				rtx = i,rty = j;
				break;
			}
	}
	for (int i = n;i;i --) {
		if (rbx || rby) break;
		for (int j = 1;j <= m;j ++)
			if (a[i][j] == '#') {
				rbx = i,rby = j;
				break;
			}
	}
	int lx = min({ltx,rtx,lbx,rbx}),rx = max({ltx,rtx,lbx,rbx});
	int ly = min({lty,rty,lby,rby}),ry = max({lty,rty,lby,rby});
	for (int i = lx;i <= rx;i ++)
		for (int j = ly;j <= ry;j ++)
			if (a[i][j] == '.') return puts("No"),0;
	puts("Yes");
	return 0;
}
```

---

## 作者：Ray_yi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc390_c)

### 思路：

看到数据范围后，直接考虑暴力。

题目让我们求一个由黑色单元格组成的长方形，容易发现，我们只需要求出这个长方形范围就可以了。

具体来说，我们遍历每一个黑色单元格，建四个变量，分别存储长方形上边界，下边界，左边界和右边界，再在其中判断，如果有白色单元格，就一定不行，直接输出即可。在这里，如果在长方形中遇到了问号，就默认变为黑色，否则变为白色。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a=0x3f3f3f3f,b,c=0x3f3f3f3f,d;
char t[1500][1500];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>t[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(t[i][j]=='#'){//分别存储长方形的上下左右边界
				a=min(a,i);
				b=max(b,i);
				c=min(c,j);
				d=max(d,j);
			}
		}
	}
	for(int i=a;i<=b;i++){
		for(int j=c;j<=d;j++){
			if(t[i][j]=='#'||t[i][j]=='?') continue;//为黑色单元格
			else{//是白色单元格
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes";//符合标准
	return 0; 
}
```

---

## 作者：TheTrash (赞：1)

### 题意

有一个 $H$ 行 $W$ 列的矩阵，你需要找到一个能覆盖矩阵中所有黑色方格的矩形。如果有这个矩形输出 ```Yes```，否则输出 ```No```。

### 思路

枚举每个格子，确定最小的能将所有黑色方格全部覆盖的矩形并枚举这个矩形的每个格子，如果矩形中有白色方格就停止枚举并输出 ```No```。如果矩形中的每个格子都不是白色的就输出 ```Yes```。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,mx1=9999999,mx2=-1,my1=9999999,my2=-1,f;
char k[1005][1005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			cin>>k[i][j];
			if(k[i][j]=='#'){
				if(i<mx1) mx1=i;
				if(i>mx2) mx2=i;
				if(j<my1) my1=j;
				if(j>my2) my2=j;
				f=1;
			}
		}
	if(f==0) puts("No"),exit(0);
	for(int i=mx1;i<=mx2;i++){
		for(int j=my1;j<=my2;j++){
			if(k[i][j]=='.') puts("No"),exit(0);
		}
	}
	puts("Yes");
}
```

---

## 作者：ljk8886 (赞：1)

## 分析
因为我们要知道能不能组成一个黑色矩形，所以我们先要保证所有已知的黑色方格都在这个矩形里面，所以我们先确定矩阵大小即要求黑色方格行和列的最大值和最小值，最后遍历这个矩形，看一下里面有没有白色方格，有就输出 `No`，没有就输出 `Yes`。

## 代码
```cpp
#include <bits/stdc++.h>
#define ft first
#define sd second
#define endl '\n'
#define pb push_back
#define md make_pair
#define gc() getchar()
#define pc(ch) putchar(ch)
#define umap unordered_map
#define pque priority_queue
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 bint;
typedef pair<int, int> pii;
typedef pair<pii, int> pi1;
typedef pair<pii, pii> pi2;
const ll INF = 0x3f3f3f3f;
inline ll read()
{
	ll res = 0, f = 1;
	char ch = gc();
	while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : f), ch = gc();
	while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = gc();
	return res * f;
}
inline void write(ll x)
{
	if (x < 0) x = -x, pc('-');
	if (x > 9) write(x / 10);
	pc(x % 10 + '0');
}
inline void writech(ll x, char ch) { write(x), pc(ch); }
const int N = 1e3 + 5;
char ch[N][N];
int main()
{
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> ch[i][j];
	int x1, y1, x2, y2; x1 = y1 = INF, x2 = y2 = 0; // 求行列的最大值和最小值
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (ch[i][j] == '#')
			{
				x1 = min(x1, i), y1 = min(y1, j);
				x2 = max(x2, i), y2 = max(y2, j);
			}
		}
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			if (ch[i][j] == '.') // 有白色方格
			{
				puts("No");
				return 0;
			}
	puts("Yes");
	return 0;
}
```

---

## 作者：cjx_AK (赞：1)

#### 题目说让我们求将整个图填完所有的黑色是否构成一个矩形。

我们考虑记录矩形的左上角和右下角，左上角就是每个黑色点中最小的横坐标和竖坐标。（若是取第二小则上面有点覆盖不到）

右下角就是每个黑色点中最大的横竖坐标。

然后枚举这个矩形，如果有白色说明不行，否则可以。


code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
char s[1001][1001];int x,y,xx=1e7,yy=1e7,l;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			
			
			if(s[i][j]=='#'){
				xx=min(xx,i);
				yy=min(yy,j);
				x=max(i,x);
				y=max(y,j);
				l=1;
			}
			
		}
	}
//	cout<<xx<<' '<<yy<<' '<<x<<' '<<y<<endl;
if(!l){
	cout<<"No";
	return 0;
}
	for(int i=xx;i<=x;i++){
		for(int j=yy;j<=y;j++){
			if(s[i][j]!='#'&&s[i][j]!='?'){
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes";
}
```

---

## 作者：lfxxx_ (赞：1)

不难发现，在 $(x_{min},y_{min})$ 到 $(x_{max},y_{max})$ 这个矩形中不会有白点，不然就是不可能完成的，其中 $x_{min}$ 为所有黑点 $x$ 坐标的最小值，$y_{min}$ 为所有黑点 $y$ 坐标的最小值，$x_{max}$ 为所有黑点 $x$ 坐标的最大值，$y_{max}$ 为所有黑点 $y$ 坐标的最大值。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
char s[N][N];
signed main()
{
    int n,m;
    cin>>n>>m;
    int lx=n+1,ly=m+1,rx=0,ry=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            cin>>s[i][j];
            if(s[i][j]=='#')
                lx=min(lx,i),rx=max(rx,i),ly=min(ly,j),ry=max(ry,j);
        }
    for(int i=lx;i<=rx;++i)
        for(int j=ly;j<=ry;++j)
            if(s[i][j]=='.')
                cout<<"No",exit(0);
    cout<<"Yes";
}  
```

---

## 作者：syx_2014 (赞：1)

我们发现，如果可以形成一个矩形，那必将所有的黑格子包含在内，而在没有不包含任何黑色格子的情况下都可以形成矩形。换句话说就是黑色格子形成了矩形的框架。

所以我们依次求最高、最低、最左、最右的黑色格子以求出左上右下的坐标。

我们从左上遍历到右下，如果这个矩形里要么是黑格子，要么是未涂色的格子的话就输出 ```Yes```，否则输出 ```No```（注意，这个矩形里一定包含所有的黑格子）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[1005][1005];
int main(){
	cin>>n>>m;
	int x1=10000,y1=10000,x2=-11111,y2=-11111;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='#') x1=min(i,x1),y1=min(j,y1),x2=max(i,x2),y2=max(j,y2);
		}
	}
	for(int i=x1;i<=x2;i++){
		for(int j=y1;j<=y2;j++){
			if(a[i][j]!='#'&&a[i][j]!='?'){
				cout<<"No\n";
				return 0;
			}
		}
	}
	cout<<"Yes\n";
	return 0;
}

```

---

## 作者：ARIS2_0 (赞：1)

### 思路

要让黑色格子的部分成为矩形，等价于让一个最小的矩形覆盖现有的所有的黑色格子，因为矩阵如果更大，无法覆盖的可能性肯定也更大。

那么，记录下所有黑色格子的最小横坐标 $x_1$，最大横坐标 $x_2$，最小纵坐标 $y_1$，最大纵坐标 $y_2$，如果所有的格子 $(i,j)(x_1\le i\le x_2,y_1\le y_2)$ 都不是白色，则可以通过将这个矩阵变为黑色来满足题目要求，否则无法满足题目要求。

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=1e3+10;
char c[maxn][maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
    int mini=inf,maxi=0,minj=inf,maxj=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
            if(c[i][j]=='#'){
                mini=min(mini,i);
                maxi=max(maxi,i);
                minj=min(minj,j);
                maxj=max(maxj,j);
            }
        }
    }
    bool g=1;
    for(int i=mini;i<=maxi;i++){
        for(int j=minj;j<=maxj;j++){
            if(c[i][j]=='.'){
                g=0;break;
            }
        }
        if(!g)break;
    }
    cout<<(g?"Yes\n":"No\n");
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

---

## 作者：hjyowl (赞：1)

### 题目大意

有一个矩阵，被黑色，白色，未定颜色的格子铺满，求能否把所有未定颜色的格子选上颜色，求能否让一块全是黑色其他都是白色的。

### 思路

首先最朴素的思路就是取枚举每个没有未定颜色的格子的颜色，但是时间复杂度的问题就不用说了。

所以说，我们可以发现，我们把黑色的最边上的轮廓找出来，如果哪个轮廓里面的全部是未定颜色的和黑色的就行了。

好做完了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 5010;
char g[N][N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin >> n >> m;
	int mnx = 1e9,mny = 1e9,mxx = -1e9,mxy = -1e9;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			cin >> g[i][j];
			if (g[i][j] == '#'){
				mnx = min(mnx,i);
				mny = min(mny,j);
				mxx = max(mxx,i);
				mxy = max(mxy,j);
			}
		}
	}
	for (int i = mnx; i <= mxx; i ++ ){
		for (int j = mny; j <= mxy; j ++ ){
			if (g[i][j] == '#' || g[i][j] == '?'){
				
			}
			else{
				cout << "No";
				return 0;
			}
		}
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：XXh0919 (赞：1)

最浮躁的一次 ABC，C 题都没场切。

### 题意

有一个长 $H$，宽 $W$ 的矩阵，单元格 $(i,j)$ 的符号为 $S_{i,j}$。$S_{i,j}$ 有以下三种情况：
- 如果 $S_{i,j}$ 是 `#`，则表示 $S_{i,j}$ 是黑色的。
- 如果 $S_{i,j}$ 是 `.`，则表示 $S_{i,j}$ 是白色的。
- 如果 $S_{i,j}$ 是 `?`，则表示 $S_{i,j}$ 未涂色。

问你能否将所有未涂色的单元格涂成黑色或白色，使得所有黑色的方格能够构成一个矩形。

### 解法

通过大眼观察法观察样例，很容易得到要想构成一个全是黑色的矩形，我们要知道初始状态下已经涂成黑色的左上角和右下角单元格的坐标，然后以这两个单元格作为黑色矩形的左上角和右下角，遍历一遍，遍历过程中如果发现其中有白色单元格，说明无法构成这个矩形，直接输出 `No`，然后结束程序；否则就说明这个矩形中只有黑格子和未涂色的格子，符合要求，遍历完了之后输出 `Yes`。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N = 1e6 + 15;

const int I_LOVE_CCF = 1;

int n, m;
char s[2005][2005];
int hmx, hmn = 1e18, wmx, wmn = 1e18;

inline int read (int &n) {
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) {
		if (ch == '-') f = -1;
		ch = getchar ();
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar ();
	}
	n = x * f;
	return n;
}


signed main () {
	read (n), read (m);
	rep (i, 1, n) {
		rep (j, 1, m) {
			cin >> s[i][j];
			if (s[i][j] == '#') {
				hmx = max (hmx, i);
				wmx = max (wmx, j);
				hmn = min (hmn, i);
				wmn = min (wmn, j);
			}//找黑格子中左上角和右下角单元格坐标
		}
	}
	rep (i, hmn, hmx) {
		rep (j, wmn, wmx) {
			if (s[i][j] == '.') {
				puts ("No");
				return 0;
			}//有白格子：回家种地
		}
	}
	puts ("Yes");//符合要求：事事顺利
	return 0;
} 
```
最后，祝各位新年快乐，心想事成！

---

## 作者：jinfanhao (赞：1)

我们可以找到黑色方块最上面，最下面，最左面，最右面，看其中是不是黑色方块或未画成的格子，如果全不是白色格子就是合法的，否则不合法。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+1;
int n,m,op[N],sum=0,f[N],miny=INT_MAX,minx=INT_MAX,maxx,maxy;
char ch[N][N];
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			cin >> ch[i][j];
			if(ch[i][j]!='#')continue;
			minx=min(minx,i);
			maxx=max(maxx,i);
			miny=min(miny,j);
			maxy=max(maxy,j);
		}
	}
	for(int i=minx; i<=maxx; ++i){
		for(int j=miny; j<=maxy; ++j){
			if(ch[i][j]=='.'){
				printf("No");
				return 0;
			}
		}
	}
	printf("Yes");
	return 0;
}
```

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc390/tasks/abc390_c)

## 题目简述
给定一个 $H$ 行 $W$ 列的网格 $S$，如果 $S_{i,j}$ 为 `#`，则为黑色格；如果为 `.`，则为白色格；如果为 `?`，则无颜色。

现在要求将每个 `?` 涂成黑色或白色，判断是否能让所有的黑色格能组成一个矩形。

## 主要思路
首先可以得知已经涂了 `#` 的格子颜色是不能改变的，并且所有的 `#` 都必须在一个矩形内，也就是说可以记录一下出现 `#` 的最小 $x$ 坐标，最大 $x$ 坐标，最小 $y$ 坐标，最大 $y$ 坐标。

然后判断一下在由这四个坐标构成的矩形内有没有出现 `.`，如果出现，则必然在这个矩形内不会全为 `#`；而 `?` 如果出现在这个矩形内，则可以涂成黑色，反之为白色。

## 时间复杂度
$O(HW)$

## AC Code
```cpp
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#define OUT 0
#define endl '\n'
#define pc putchar
#define gc getchar
#define MAMBA return
typedef long long ll;
const int N = 1e3 + 10;
typedef long double db;
const int INF = 0x3f3f3f3f;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)
int _abs(int a) { if (a < 0) return -a; return a; }
int _pow(int a,int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }
void print(string s) { size_t n = s.length(); for (size_t i = 0; i < n; i++)pc(s[i]); }
void print(ll x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
void print(int x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
inline int read_int() { int f = 1, x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }return x * f; }int man();
inline ll read_ll() { int f = 1; ll x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }return x * f; }int main() { MAMBA man(); }
// ----------------------------

// ----------------------------
char grid[N][N];
// ----------------------------


int man() {
	int h = read_int(), w = read_int();
	// ----------------------------
	int x_min, x_max, y_min, y_max;
	x_min = y_min = INF;
	x_max = y_max = -INF;
	rep(i, 1, h) {
		rep(j, 1, w) {
			grid[i][j] = gc();
			if (grid[i][j] == '#') {
				x_min = min(x_min, i);
				x_max = max(x_max, i);
				y_min = min(y_min, j);
				y_max = max(y_max, j);
			}
		}
		gc();
	}
	bool flag = true;
	rep(i, x_min, x_max) {
		rep(j, y_min, y_max) {
			if (grid[i][j] == '.') flag = false;
		}
	}
	// ----------------------------
	print((flag) ? ("Yes") : ("No"));
	MAMBA OUT;
}
/*
				 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
			 __.'              ~.   .~              `.__
		   .'//   A    C    之   \./  之    真    理  \`.
		 .'//                     |                     \`.
	   .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \`.
	 .'//.-"                 `-.  |  .-'                 "-.\`.
   .'//______.============-..   \ | /   ..-============.______\`.
 .'______________________________\|/______________________________`.
*/
```

---

## 作者：Ambrose0321 (赞：0)

思路：
---

我们找到所有黑色格子横纵坐标的最小值和最大值，如果这个范围内有白色格子，黑色格子就不是矩阵，如果没有白色格子，就是矩阵。


AC code:
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef pair<int, int> pii;
const int N = 200005, P = 998244353, INF = 2139062143;
int gcd(int A, int B) {return B ? gcd(B, A % B) : A;}
int lcm(int A, int B) {return A * B / gcd(A, B);}
int n, m, a = 2e9, b = 2e9, x, y;
char s[1001][1001];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; j++)
			if (s[i][j] == '#')
				x = max(x, i), y = max(y, j), a = min(a, i), b = min(b, j);
	}
	for (int i = a; i <= x; i++)
		for (int j = b; j <= y; j++)
			if (s[i][j] == '.') {
				puts("No");
				return 0;
			}
	puts("Yes");
}
```

---

---

## 作者：chaqjs (赞：0)

## 题目翻译

你将得到一个由 $H$ 行和 $W$ 列组成的网格。

设 $(i,j)$ 表示顶部的第 $i$ 行（$1 \leq i \leq H$）和左侧的第 $j$ 列（$1 \leq j \leq W$）处的单元格。

网格的状态由 $H$ 字符串 $S_1, S_2, \ldots, S_H$ 表示，每个字符串的长度为 $W$，如下所示：

- 如果 $S_i$ 的第 $j$ 个字符是 `#`，单元格 $(i,j)$ 被涂成黑色。

- 如果 $S_i$ 的第 $j$ 个字符是 `.`，单元格 $(i,j)$ 被涂成白色。

- 如果 $S_i$ 的第 $j$ 一个字符是 `？`，单元格 $(i,j)$ 尚未绘制。

高桥想把每个还没有被涂上颜色的单元格涂成白色或黑色，这样所有的黑色单元格就形成了一个矩形。

高桥想把每个还没有被涂上颜色的单元格涂成白色或黑色，这样所有的黑色单元格就形成了一个矩形。

更准确地说，他希望存在一个四元组整数 $(a,b,c,d)$（ $1 \leq a \leq b \leq H$ , $1 \leq c \leq d \leq W$），这样：

> 对于每个单元格 $(i,j)$（$1 \leq i \leq H, 1 \leq j \leq W$），如果 $a \leq i \leq b$ 和 $c \leq j \leq d$，单元格为黑色；
> 
> 否则，单元格为白色。

请确定这是否可能。

## 解题思路
我们要找到一个黑色矩形，所以我们直接枚举整个网格，找到能成为矩形的黑色单元格的左上角和左下角，然后再枚举整个矩形若里面有白色单元格，则说明一定不能构成矩形，反之说明能构成矩形。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int h, w;
char s[N][N];

int main(){
	cin.tie(0)->sync_with_stdio(0);
	
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			cin >> s[i][j];
	
	int x = 0x3f3f3f3f, y = 0x3f3f3f3f, m = -1, n = -1;
  // 找到左上角和左下角
	for (int i = 1; i <= h; i++){
		for (int j = 1; j <= w; j++){
			if (s[i][j] == '#'){
				x = min(x, i);
				y = min(y, j);
				m = max(m, i);
				n = max(n, j);
			}
		}
	}

  // 枚举这个矩形
	for (int i = x; i <= m; i++){
		for (int j = y; j <= n; j++){
			if (s[i][j] == '.'){
				cout << "No";
				return 0;
			}
		}
	}
	
	cout << "Yes";
	
	return 0;
}
```

---

## 作者：__Ship_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc390_c)

## 思路一

将**所有的问号区域填充为黑色**过后在枚举矩形边界来判断是否可行。

但是明显这样会直接爆炸，我们来仔细看看题目。

题目说的是将**所有**的黑色方块变成矩形。

## 思路二

我们先找到所有黑色方块的边界最大是多少，然后把所有是问号的全部涂黑，在枚举这个边界判断是不是全黑就好了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int h,w,l=1e9,r=-1e9,u=1e9,d=-1e9;
char a[1005][1005];
int main(){
	cin>>h>>w;
	for(int i = 1 ; i <= h ; i++){
		for(int j = 1 ; j <= w ; j++){
			cin>>a[i][j];
		}
	}
	for(int i = 1 ; i <= h ; i++){
		for(int j = 1 ; j <= w ; j++){
			if(a[i][j]=='#'){
				l=min(l,j);
				r=max(r,j);
				u=min(u,i);
				d=max(d,i);
			}
			if(a[i][j]=='?'){
				a[i][j]='#';
			}
		}
	}
	
	for(int i = u ; i <= d ; i++){
		for(int j = l ; j <= r ; j++){
			if(a[i][j]!='#'){
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes";
	return 0;
}

```

---

## 作者：Yuexingfei_qwq (赞：0)

终于又创历史新巅了。
## 思路  
把整个黑色矩形的四个边算出来，然后用两个循环检查这个范围里面有没有白色的格子即可。
## AC CODE
赛时代码。
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int h, w;
char s[1100][1100];
int lh = inf, rh = -inf, lw = inf, rw = -inf;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> h >> w;
	F(i, 1, h, 1) {
		F(j, 1, w, 1) {
			cin >> s[i][j];
			if (s[i][j] == '#') {
				lh = std::min(lh, i);
				rh = std::max(rh, i);
				lw = std::min(lw, j);
				rw = std::max(rw, j);
			}
		}
	}
	bool f = 1;
	F(i, lh, rh, 1) {
		F(j, lw, rw, 1) {
			if (s[i][j] == '.') {
				f = 0;
				break;
			}
		}
		if (!f) {
			break;
		}
	}
//--------------------------
	F(i, 1, h, 1) {
		if (i < lh || i > rh) {
			F(j, 1, w, 1) {
				if (s[i][j] == '#') {
					f = 0;
					break;
				}
			}
		}
		if (!f) {
			break;
		}
	}
//--------------------------

/*  实测证明，上面这一段删掉也能通过，详见：
	https://atcoder.jp/contests/abc390/submissions/62113041
*/
	cout << (f ? "Yes" : "No") << el;
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc390/submissions/62048830)

---
完结~~不~~散花。

---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/AT_abc390_c) & [Atcoder 题目链接](https://atcoder.jp/contests/abc390/tasks/abc390_c)

# 题意简述

给你一个 $n\times m$ 的网格，每个格子有黑、白或者不涂三种状态。

你需要把不涂的格子涂上黑色或者白色，问是否可以使所有黑色的盒子都在同一个矩形内且该矩形内只有黑色格子。

# 思路

首先这个矩形肯定越小越好，并且这一定是最优的，我们先用已有的黑色格子确定它的上下左右四个端点。

然后只要这四个端点内没有白色的格子即可。

可以暴力枚举也可以二维前缀和。

# 代码：


```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=1003;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int T,n,m,s[maxn][maxn],up,down,l,r;

char a[maxn][maxn];

void solve(){
	cin>>n>>m;
	r=0,down=0;
	l=m+1,up=n+1;
	for(int i=1;i<=n;i++){
		cin>>(a[i]+1);
		for(int j=1;j<=m;j++){
			if(a[i][j]=='#'){
				l=min(l,j);
				up=min(up,i);
				down=max(down,i);
				r=max(r,j);
			}
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(a[i][j]=='.');
		}
	}
	if(s[down][r]-s[up-1][r]-s[down][l-1]+s[up-1][l-1]==0){
		cout<<"Yes\n";
	}else{
		cout<<"No\n";
	}
	return;
}

int main(){
	T=1;
	while(T--){
		
		solve();
	}
	return 0;
}
```

---

## 作者：xiaoyin2011 (赞：0)

## AT_abc390_c [ABC390C] 绘制长方形 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc390_c)

### 题目大意

给定 $H \times W$ 的网格纸，其中 $(i, j)$ 标记的格子有三种可能：

- `#` 代表已经涂黑
- `.` 代表已经涂白
- `?` 代表还没有涂色

问有没有一种上色方法（把所有 `?` 变为 `#` 或 `.`）使得存在四元组 $(a, b, c, d)$：

- $(i, j)$ 满足 $a \le i \le b$ 且 $c \le j \le d$，则是黑色。
- 不满足上述条件，则是白色。

也就是有没有上色方法可以让网格纸中恰只有一个黑色矩形。

**题目保证至少有一个已经涂成黑色的方格。**

### 解题

我们先考虑另一个问题，在 $H \times W$ 的网格中，所有方格都可以被涂成黑色，有些方格已经涂成了黑色，问是否有一种涂色方式可以形成**最小的**黑色矩形覆盖所有已有的黑色方格。

显然，如果把画布全部涂成黑色一定可以覆盖所有黑色方格，但是这不是最小的。

我们可以考虑从上下左右四个方向中央还原一些黑色变成白色。推到不能再推的时候就是最小的了。什么情况会阻碍我们向中心推呢？遇到已经被确定为黑色的方格时。

因此，我们可以统计所有黑色方格的最小和最大横坐标、最小和最大纵坐标，在这个四元组构成的矩形内，恰好包含所有黑色方格。

---

那上面这个问题和本题有什么关系呢？由于本题添加了确定为白色的方格，而这些方格不能涂色。

如果我们选取最小的满足条件的矩形内部有白色，就说明更大的满足条件的矩形内部也一定有白色，所有满足条件的矩形都不能涂色，所以输出 `No`；反之内部没有，那么我们就有了一种例子可以实现，题目只需要判断是否存在，那么果断输出 `Yes`。

---

观察数据范围：$H, W \le 1000$。所以我们只需要先找出最小矩形，然后遍历最小矩形内部，看看有没有 `.`，如果有，就输出 `No`，反之 `Yes`。

而且题目保证至少有一个黑色方格，所以不用害怕最大最小值变量的初始值会进入到后面的遍历中。

### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int H, W, ub = 1e9, db = -1e9, lb = 1e9, rb = -1e9;
char mp[1005][1005];
int main()
{
	scanf("%d%d", &H, &W);
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			scanf("\n%c", &mp[i][j]);
			if (mp[i][j] == '#')
			{
				ub = min(ub, i);
				db = max(db, i);
				lb = min(lb, j);
				rb = max(rb, j);
			}
		}
	}
    bool flag = 0;
	for (int i = ub; i <= db; i++)
		for (int j = lb; j <= rb; j++)
			if (mp[i][j] == '.')
				flag = 1;
	if (flag) printf("No\n");
	else printf("Yes\n");
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

很㵘的一道题。

## 题目大意

给定一个 $N\times M$ 的矩阵，每个元素 $S_{i,j}$ 都为 `#`，`.` 和 `?` 中的一种，`?` 可以染成 `#` 或 `.`，问染色后是否有可能使 `#` 形成的连通块为矩形。

## 解题思路

考虑一个矩形的性质，其有四个顶点 $(a,b,c,d)$，且对于所有 $a\le i\le b,c\le j\le d$ 都有 $S_{i,j}$ 为 `#`。而因为 `?` 可随便染色，所以我们只需根据 `#` 横纵坐标的最值确定矩形的范围，最后看这个范围内是否有 `.` 即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,m,a=1e18,b,c=1e18,d,cnt;
char x[1001][1001];

int main()
{
    n=read(); m=read();

    for(R ll i=1; i<=n; ++i)
    {
        for(R ll j=1; j<=m; ++j)
        {
            scanf(" %c",&x[i][j]);
            cnt+=(x[i][j]=='?');

            if(x[i][j]=='#')
            {
                a=min(a,i); b=max(b,i);
                c=min(c,j); d=max(d,j);
            }
        }
    }

    if(a==1e18) printf(cnt?"Yes":"No"), exit(0);

    for(R int i=a; i<=b; ++i)
    {
        for(R int j=c; j<=d; ++j)
        {
            if(x[i][j]=='.')
            printf("No"), exit(0);
        }
    }

    printf("Yes");
    return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

首先，我们可以遍历整个网格，找到所有黑色方块的最小和最大行列索引。

我定义了几个变量，用于找到黑色方块的左上角和右下角的坐标。

然后，在确定了矩形的边界后，接下来需要检查这个边界内的所有方块。确保条件满足。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int main () {
    int H, W; cin >> H >> W;
    vector <string> grid (H);
    for (int i = 0; i < H; i ++) cin >> grid[i];
    int top = H, bot = -1, l = W, r = -1;
    for (int i = 0; i < H; i ++) {
        for (int j = 0; j < W; j ++) {
            if (grid[i][j] == '#') {
                top = min (top, i);
                bot = max (bot, i);
                l = min (l, j);
                r = max (r, j);
            }
        }
    }
    if (bot == -1) {
        cout << "No" << endl;
        return 0;
    }
    for (int i = top; i <= bot; i ++) {
        for (int j = l; j <= r; j ++) {
            if (grid[i][j] == '.') {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

很简单的暴力枚举。先枚举出字符 `#` 出现的横纵坐标的最大和最小值，然后用这四个坐标值组成一个矩形，枚举这个矩形内是否只有 `?` 或 `#` 即可。核心代码：
```cpp
int minx=1e9,maxx=0,miny=1e9,maxy=0;
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		if(c[i][j]=='#'){
			minx=min(minx,i);
      maxx=max(maxx,i);
			miny=min(miny,j);
			maxy=max(maxy,j);
		}
	}
}
bool ok=1;
for(int i=minx;i<=maxx;i++)
	for(int j=miny;j<=maxy;j++)
		if(c[i][j]!='#' and c[i][j]!='?')
			ok=0;
cout<<(ok?"Yes":"No");
```

[参考代码](https://atcoder.jp/contests/abc390/submissions/62065366)

---

## 作者：Nahia (赞：0)

### 思路

> 考虑暴力求解。

记录下黑色单元格存在的最小行、最大行、最小列、最大列的下标，然后判断一下这块区域里有没有白色单元格，如果有，那黑色单元格就一定不能够形成矩形。再检查这块区域外有没有黑色单元格，如果有，那黑色单元格也一定不能够形成矩形。如果两次检查都通过了，那么未知单元格就一定能够形成矩形。

注意：不用管未知单元格，因为在黑色单元格区域内的未知单元格可以被染成黑色单元格，在黑色单元格区域外的未知单元格可以被染成白色单元格，只要检查黑色单元格和白色单元格的位置就可以了。

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int h, w;
    cin >> h >> w;
    string s[1005];
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }
    int a = h, b = 0, c = w, d = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                a = min(a, i);
                b = max(b, i);
                c = min(c, j);
                d = max(d, j);
            }
        }
    }
    for (int i = a; i <= b; i++) {
        for (int j = c; j <= d; j++) {
            if (s[i][j] == '.') {
                cout << "No";
                return 0;
            }
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#' && (i < a || i > b || j < c || j > d)) {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}
```

---

