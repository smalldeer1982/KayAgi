# Moving Chips

## 题目描述

## 题意翻译  
### 题意简述
给你一个大小为$2$×$n$的棋盘，
棋子用'*'表示，空位用'.'表示。  
在一次移动中，你可以选择任何棋子并将其移动到棋盘的任何相邻的格子，如果目的格子中有棋子则把他们合并为一个。

## 样例 #1

### 输入

```
5
1
*
.
2
.*
**
3
*.*
.*.
4
**.*
**..
5
**...
...**```

### 输出

```
0
2
3
5
5```

# 题解

## 作者：CGDGAD (赞：15)

## CF1680E Moving Chips

### 算法

这题里吃的路径其实是可逆的，比如说 A 吃了 B，C 再吃了 B 和 A 吃了 B 然后继续吃了 C 是一样的。所以我们的目标是找出代价最少的一条吃人路径，并且可以钦定任意一个星号作为最终状态。假如设最后留下来的是最右边的某个星号，那就是「从左吃到右」的过程，可以尝试用 DP 来最优化方案。

设 $f(i,0/1)$ 为把第 $1$ 到第 $i-1$ 列全部吃掉，且星号仅在 $(i,0/1)$ 时的最小步数。在对这一列进行 DP 的过程中，我们要考虑的问题是**怎么把上一列的星号全部转移到这一列的目标位置中去**。假如本列有两个星号，**合并一定更优**（否则同时移两个就是浪费），所以也要考虑合并。

- 若全部转移到 $(i,0)$：
    - 从 $(i-1,0)$ 转移：代价为 $1$，但如果 $(i,1)$ 有星号，还需要再加一。
    - 从 $(i-1,1)$ 转移：可以顺便吃了 $(i,1)$，无论如何代价始终为 $2$。
- 若全部转移到 $(i,1)$：
    - 从 $(i-1,1)$ 转移：代价为 $1$，但如果 $(i,0)$ 有星号，还需要再加一。
    - 从 $(i-1,0)$ 转移：代价始终为 $2$。

可以轻松写出状态转移方程。

### 实现

```cpp
int T, n;
int g[200001][2], f[200001][2];

int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i)
            f[i][0] = f[i][1] = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= n; ++j) {
                char c; std::cin >> c;
                g[j][i] = (c == '*');
            }
        }
        int l = 1, r = n;
        while (!g[l][0] && !g[l][1]) ++l;
        while (!g[r][0] && !g[r][1]) --r;
        for (int i = l; i <= r; ++i) {
            f[i][0] = std::min(f[i - 1][0] + g[i][1] + 1, f[i - 1][1] + 2);
            f[i][1] = std::min(f[i - 1][1] + g[i][0] + 1, f[i - 1][0] + 2);
        }
        std::cout << std::min(f[r][0], f[r][1]) - 1 << std::endl;
        // 之前没有特地算 f[l][0/1] 的初始值，循环直接从 l 开始，但是 l-1 -> l 算了 1 步，所以这里减去一。
    }
    return 0;
}
```

---

## 作者：Sellaris (赞：4)

-  简单贪心。手推容易发现每个连通块合并的最少次数一定，所以考虑怎么消耗最少的代价把连通块连起来。注意到只有两行，于是线性从左往右扫分类讨论连通块之间上面下面凸出还是上下平的。

- 代码：

```cpp
///*****Sellaris*****///
//#pragma once
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define ll long long
using namespace std;
//using namespace __gnu_pbds;
const int maxn=2e5+10;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
int n;
char s[3][maxn];
int cnt=0;
inline void solve(){
	cin>>n;
	cin>>s[1]+1;
	cin>>s[2]+1;
	int flag=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(s[1][i]=='.' && s[1][i]==s[2][i]) {
			cnt++;
		}
		if(s[1][i]=='*' && s[1][i]==s[2][i]) {
			ans=ans+2;
			if(flag!=0) ans+=cnt;
			flag=2;//all
			cnt=0;
		}else if(s[1][i]=='*' && s[1][i]!=s[2][i]){
			ans=ans+1;
			if(flag==2 || flag==3) ans+=cnt;
			if(flag==4) ans+=cnt+1,flag=2;
			else flag=3;//up
			cnt=0;
		}else if(s[1][i]=='.' && s[1][i]!=s[2][i]){
			ans+=1;
			if(flag==2 || flag==4) ans+=cnt;
			if(flag==3) ans+=cnt+1,flag=2;
			else flag=4;//down
			cnt=0;
		}
	cout<<ans-1<<endl;
}
signed main(){
    //std::ios::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t=read();
	while(t--){
		solve();
	}
    return 0;
}

```



---

## 作者：汪汪队队长1 (赞：0)

状压，分讨后暴力 dp 就行。

$f[1/2/3][i]$ 表示把前 $i$ 列的棋子移成在第 $i$ 列第一行有棋子/第二行有棋子/第一、二行都有棋子的最少步数。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=998244353;
int n,t,cnt,f[4][N];
char a[3][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=n;j++)
				cin>>a[i][j];
		int s=1,t=n;
		while(a[1][s]=='.'&&a[2][s]=='.')
			s++;
		while(a[1][t]=='.'&&a[2][t]=='.')
			t--;
		if(a[1][s]=='*'&&a[2][s]=='*')
			f[1][s]=f[2][s]=1,
			f[3][s]=0;
		else if(a[1][s]=='*')
			f[1][s]=0,
			f[2][s]=1,
			f[3][s]=1e9;
		else if(a[2][s]=='*')
			f[2][s]=0,
			f[1][s]=1,
			f[3][s]=1e9;
		for(int i=s+1;i<=t;i++)
			if(a[1][i]=='*'&&a[2][i]=='*')
				f[1][i]=f[2][i]=min(f[3][i-1]+3,min(f[1][i-1],f[2][i-1])+2),
				f[3][i]=min(f[3][i-1]+2,min(f[1][i-1],f[2][i-1])+1);
			else if(a[1][i]=='*')
				f[1][i]=min(f[3][i-1]+2,min(f[1][i-1]+1,f[2][i-1]+2)),
				f[3][i]=min(f[3][i-1]+2,min(f[1][i-1]+2,f[2][i-1]+1)),
				f[2][i]=min(f[3][i-1]+3,min(f[2][i-1],f[1][i-1])+2);
			else if(a[2][i]=='*')
				f[1][i]=min(f[3][i-1]+3,min(f[1][i-1],f[2][i-1])+2),
				f[3][i]=min(f[3][i-1]+2,min(f[2][i-1]+2,f[1][i-1]+1)),
				f[2][i]=min(f[3][i-1]+2,min(f[2][i-1]+1,f[1][i-1]+2));
			else
				f[1][i]=min(f[1][i-1]+1,min(f[2][i-1]+2,f[3][i-1]+2)),
				f[2][i]=min(f[2][i-1]+1,min(f[1][i-1]+2,f[3][i-1]+2)),
				f[3][i]=f[3][i-1]+2;
		cout<<min(f[1][t],min(f[2][t],f[3][t]+1))<<'\n';
	}
	return 0;
}

```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
在一个 $2\times n$ 的棋盘里，可以上下左右走，走到星号可以合并这个它，求把所有的星号全都合并的最最小操作数。
## 大体思路
这道题好做的点是只有棋盘两行，这样的话我们直接 DP 就可以。
### 状态设置
$f_{i,j}$ 表示把第 $j$ 列前的星号全都合并了所用的最小步数，当时在第 $i$ 行。

！！一定要注意，每个棋子都可以动，不是只有合并多了的那个可以动，所以得到状态转移方程：

在第一行的时候，分两种情况，若是第 $i$ 列第 $2$ 行是星号，那转移式就是 $f_{1,i}=\min(f_{1,i-1}+2,f_{2,i-1}+2)$（$\min$ 里第一个下面那个棋子也可以往 $(i,j)$ 那个点走，我也往 $(i,j)$ 那个点走，一共花费两次）；

若不是，那转移式就是 $f_{1,i}=\min(f_{1,i-1}+1,f_{2,i-1}+2)$；

在第二行的时候，也分两种情况，若是第 $i$ 列第 $1$ 行是星号，那转移式就是 $f_{2,i}=\min(f_{2,i-1}+2,f_{1,i-1}+2)$；

若不是，那转移式就是 $f_{2,i}=\min(f_{2,i-1}+1,f_{1,i-1}+2)$；

我们手玩一下就可以清晰地了解这个转移式子。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char t[3][200005];
int f[3][200005];
int main(){
	int tt;
	cin>>tt;
	while(tt--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			f[1][i]=0;
			f[2][i]=0;//操作之前清空f数组 
		}
		int b=1,e=n;
		for(int i=1;i<=2;i++){
			for(int j=1;j<=n;j++){
				cin>>t[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			if(t[1][i]=='*'||t[2][i]=='*'){
				break;
			}
			b++;
		}//前后没有*的列不需要转移
		for(int i=n;i>=1;i--){
			if(t[1][i]=='*'||t[2][i]=='*'){
				break;
			}
			e--;
		}
		for(int i=b;i<=e;i++){
			if(t[2][i]=='*'){//转移 
				f[1][i]=min(f[1][i-1]+2,f[2][i-1]+2);
			}
			else{
				f[1][i]=min(f[1][i-1]+1,f[2][i-1]+2);
			}
			if(t[1][i]=='*'){
				f[2][i]=min(f[2][i-1]+2,f[1][i-1]+2);
			}
			else{
				f[2][i]=min(f[2][i-1]+1,f[1][i-1]+2);
			}
		}
		cout<<min(f[1][e],f[2][e])-1<<endl;
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1680E
## 题意
给定一个大小为 $2 \times n$ 的棋盘，上面有若干枚棋子。我们每次操作可以将其中一枚棋子移动到相邻的位置，若两枚棋子在同一个位置，则合并为一个棋子。问合并为一个棋子的最少操作数。
## 思路
本题一看就是动态规划。因为棋盘只有两行，我们便可以在草稿纸上列一下每列两个位置可以有哪几种转移方案。我们设第一行为 $0$，第二行为 $1$，发现可以从有棋子的最左端合并到有棋子的最右端，在第 $i$ 列的两个位置有以下转移方案：

- $f[i][0]$ 有两种情况，第一种是从 $f[i-1][0]$ 再加上走过来的一步，再判断 $(i-1,1)$ 的位置是否有棋子，有再加上一；第二种是从 $f[i-1][1]$ 再加上走过来的两步，因为可以先往上再往右，不用判断 $(i-1,0)$ 是否有棋子。
- $f[i][1]$ 的转移方案与上文类似，这里不再展开。

最后输出上下两个位置的较小值即可。

需要注意的：

- 多测清空。
- 输出要换行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,a[N][2],f[N][2];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)f[i][0]=f[i][1]=0;
		for(int i=0;i<=1;i++){
			for(int j=1;j<=n;j++){
				char ch;
				cin>>ch;
				if(ch=='*')a[j][i]=1;
				else a[j][i]=0;
			}
		}
		int l=1,r=n;
		while(a[l][0]==0&&a[l][1]==0)l++;
		while(a[r][0]==0&&a[r][1]==0)r--;
		for(int i=l;i<=r;i++){
			f[i][0]=min(f[i-1][0]+1+a[i][1],f[i-1][1]+2);
			f[i][1]=min(f[i-1][1]+1+a[i][0],f[i-1][0]+2);
		}
		cout<<min(f[r][0],f[r][1])-1<<'\n';
	}
	return 0;
}
```

---

## 作者：char_phi (赞：0)

今天多校联测考了这道题，我考场上干了三个小时硬是没干出来，后来改了十几分钟就切了，特此写篇题解。

--------

在这里提供一种 $O(n)$ 的算法。

~~大力分类讨论~~。

根据题意，我们需要让一个棋子从起始点移到终点，期间与其他棋子合并以共同移动。那么这个棋子显然是在两边的时候才能更多地与其他棋子合并，以减少冗余移动。不妨设该棋子为最左边的棋子(因为从左往右推和从右往左推是等价的)。称该棋子为主棋子。

考虑如何让主棋子与其他棋子合并。

--------

设 $\text{sus}$ $(\text{status}$，状态$)$，当其值为 $1$ 时说明主棋子其处于第一行。类似地，其值为 $2$ 时说明主棋子目前处于第一行。

当其值为 $0$ 时为不定态，也就是主棋子既可以位于第一行也可以第二行时。

### 当主棋子状态确定时(即 $\text{sus}$ 为 $1$ 或 $2$ 时)

*(以下 `x` 指的就是主棋子)*

- 第一种情况，与同行棋子合并。

```
x *
. .
```

显然只需要将 `x` 向右移动一步即可合并，答案仅需要 $+1$，不需要将主棋子换行，所以 $\text{sus}$ 仍然为 $1$。

--------

- 第二种情况，与异行棋子合并。

```
x .
. *
```

此时可以将主棋子换行与 `*` 合并，**但是**也可以让 `*` 换行到第一行与主棋子合并。分两种情况。

```
x . * *
. * . .
```

$↑$ 这种情况下让第二行的 `*` 到第一行与主棋子合并是更优的。

```
x . . .
. * * *
```

$↑$ 这种情况下让主棋子到第二行与其他棋子合并是更优的。

所以我们可以让此时的 $\text{sus}$ 变为不定态，令答案 $+2$ (因为主棋子和其他棋子必定有一个要换行，所以要额外 $+1$ )。

--------

- 第三种情况，同时与两个行的棋子合并。

```
. *
x *
```

此时主棋子既可变为第一行，也可以变为第二行，对当前一步的答案无影响，于是可以让 $\text{sus}$ 变为不定态，令答案 $+2$ (原因同上一种情况)。

### 当主棋子状态不确定时(即 $\text{sus}$ 为 $0$ 时)

*(以下 `?` 指的就是主棋子处于不定态)*

- 第一种情况，与单个棋子合并。

```
? *
? .
```

由于此时主棋子的位置可以在第一行，也可以在第二行，所以直接令 $\text{sus}$ 变为新棋子所在行，令答案 $+1$ 即可。

--------

- 第二种情况，与两个棋子合并。

```
? *
? *
```

此时主棋子合并之后仍然为不定态，但是新的棋子之一仍需要换行，所以答案应 $+2$。

--------

分类讨论从左往右扫一遍即可。代码里有一些注释辅助理解。

代码实现：

```cpp
#include <iostream>
#define GMY (520&1314)
#define FBI_OPENTHEDOOR(x, y) freopen(#x ".in", "r", stdin), freopen(#y ".out", "w", stdout);
#define re register int
#define char_phi signed
#define _ ' '
#define CASE 10005
#define N 200005
using namespace std;
inline void Fastio_setup(){ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);}

int T, n, sus, final_ans, st, ed;// status 0：不定态；1：行一；2：行二
char s[3][N];

inline void Clean(){ sus = final_ans = st = ed = 0; }

inline void work(){
	Clean();
	cin >> n;
	cin >> s[1]+1;
	cin >> s[2]+1;
	
	for (re i = 1 ; i <= n ; ++ i)// 找起点
		if (s[1][i] == '*' or s[2][i] == '*')
			{ st = i; break; }
	for (re i = n ; i >= 1 ; -- i)// 找终点
		if (s[1][i] == '*' or s[2][i] == '*')
			{ ed = i; break; }
    
	if (s[1][st] == '*' and s[2][st] == '*')// 判断当前位于起点时的状态
		sus = 0, final_ans = 1;
	else if (s[1][st] == '*')
		sus = 1;
	else if (s[2][st] == '*')
		sus = 2;
	
	for (re i = st+1 ; i <= ed ; ++ i){
		if (s[1][i] == '*' and s[2][i] == '*'){
			if (sus == 0)// 不定态与两个棋子合并
				sus = 0, final_ans += 2;
			else if (sus == 1)// 行转不定态
				sus = 0, final_ans += 2;
			else 
				sus = 0, final_ans += 2;
		}
		else if (s[1][i] == '*'){
			if (sus == 0)// 不定态转行
				sus = 1, final_ans += 1;
			else if (sus == 1)// 同行
				sus = 1, final_ans += 1;
			else // 行互换
				sus = 0, final_ans += 2;
		}
		else if (s[2][i] == '*'){
			if (sus == 0)
				sus = 2, final_ans += 1;
			else if (sus == 2)
				sus = 2, final_ans += 1;
			else 
				sus = 0, final_ans += 2;
		}
		else 
			final_ans ++;
	}
	
	cout << final_ans << '\n';
}
// #define IXINGMY
char_phi main(){
	#ifdef IXINGMY
		FBI_OPENTHEDOOR(a, a);
	#endif
	Fastio_setup();
	cin >> T;
	while (T --)
		work();
	return GMY;
}
```

---

## 作者：SMTwy (赞：0)

考虑简单的模拟合并过程。

合并终点处于星号的区间内答案都是等价的。

简单显然一下就是，$4$ 到 $7$ 的一段区间，$4$ 到 $7$ 之间的所有数到两头的距离都是一样的，都为 $3$，如果在区间外，到 $4$ 和 $7$ 的距离一定大于 $3$。

我们考虑从最右端开始，一路合并到最左端。

先 $O(n)$ 预处理出行 $1$ 和行 $2$ 的最左和最右的星号位置，
分别记为 $le1$，$ri1$，$le2$，$ri2$。

因为存在一个同时平移的性质，肯定是从最边界的点一路合并最优，假设终点固定，最后边界一定要到终点，它会经过整段区间，所以在边界之前去合并中间的点显然更劣，浪费次数。

如果 $ri1 \le le2$ 或者 $ri2 \le le1$ 这种情况直接把两行从各自边界位置的一个星号，一路平移到中间 $ri1$ 到 $le2$ 的位置显然是最优的，最终答案再加上 $1$ 次上下平移即可，同时处理一下零的情况。

如果上下两行的区间有交叉，会在上下平移这里出现优劣问题。我们用 $1$ 代替星号。

比如：

$$0100$$

$$1100$$

如果我们要将下面两个星号移动到第一行第二列，两者先在第二行合并再上移步数是 $2$，各自单独移动上去再合并步数是 $3$。

但是对于这种情况：

$$1100$$

$$1100$$

下面两个星号先合并还是先各自上移对于最终答案就没有区别了。

还有这种情况：

$$10000001$$

$$01111110$$

合并点在下面左右合并再上去显然是比把下面的都单独移动上去更优秀。

所以我们就可以有一种 $O(n)$ 的贪心策略。

先对 $le1$，$le2$ 取较大值作为左边界，$ri1$，$ri2$ 取较小值作为右边界。

处于边界之外的点不会涉及上下优劣的情况，直接把它们移动到边界即可。

开一个 $pos$ 变量记录当前合并点处于哪一行。

初始左右边界都是上下都有点的(因为我们移动过来了)。

所以初始 $pos=0$ 意味处于不定态，即对于合并点处于的列来说，它到第一行和第二行步数是一样的的，具体处在哪一行根据下一列来判断在哪一行更优。


**如果上一列是不定态**

下一列如果上下都有星号，那么 $ans$ 加 $2$，依旧处于不定态。

下一列如果只有一个星号，那么 $ans$ 加 $1$，$pos$ 根据下一列的位置对应更新。

下一列是两个点号，直接 $ans$ 加 $1$，不做处理。

**如果上一列 $pos$ 是 $1$**（与 $pos$ 是 $2$ 同理）

下一列如果是上下都有星号，那么 $ans$ 加 $2$，更新成为不定态。

下一列如果是在第一行有星号，那么 $ans$ 加 $1$，位置不变。

下一列如果是在第二行有星号，那么 $ans$ 加 $2$，同时 $pos$ 更新为不定态。
因为此刻上一列到下一列要达成全收集，必须走两步，这两步可以先右再下到第二行，也可以先右，再让下面的上来还是第一行。

下一列是两个点号，直接 $ans$ 加 $1$，不做处理。



可能说起来挺麻烦，其实代码并不复杂，一些细节就看代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=2e5+1000;
int T,n;
char s[3][mx];                        
void MYH(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=2;++i){
            scanf("%s",s[i]+1);
        }
        int po1=0,po2=0,mid=1e9,cn1=0,cn2=0,ans=0;
        for(int i=1;i<=n;++i){
            if(s[1][i]=='*'){if(po1==0)po1=i;cn1=i;}
            if(s[2][i]=='*'){if(po2==0)po2=i;cn2=i;}
        }
        if(cn2<=po1){
            if(cn2==0)ans=cn1-po1;
            else ans=ans+po1-po2+cn1-po1+1;
            printf("%d\n",ans);
            continue;
        }
        else if(cn1<=po2){
            if(cn1==0)ans=cn2-po2;
            else ans=ans+po2-po1+cn2-po2+1;
            printf("%d\n",ans);
            continue;
        }
        ans=ans+abs(cn1-cn2);
        ans=ans+abs(po1-po2);
        int cnt=min(cn1,cn2);int po=max(po1,po2);
        int up=0;ans++;
        s[1][cnt]='*';s[2][cnt]='*';s[1][po]='*';s[2][po]='*';
        for(int i=cnt-1;i>=po;--i){
            if(s[1][i]=='*' && s[2][i]=='*')ans=ans+2;up=0;
            if(s[1][i]=='*' && s[2][i]=='.'){
                if(up==1)ans++;
                else if(up==0)ans++;up=1;
                else ans=ans+2;up=0;
            }
            if(s[1][i]=='.' && s[2][i]=='*'){
                if(up==2)ans++;
                else if(up==0)ans++;up=2;
                else ans=ans+2;up=0;
            }
            if(s[1][i]=='.' && s[2][i]=='.')ans++;
        }
        printf("%d\n",ans);
    }
}
int main(){
  //  freopen("1.in","r",stdin);
  //  freopen("1.out","w",stdout);
    MYH();
    return 0;
}
```

祝您，武运昌隆



---

## 作者：I_am_Accepted (赞：0)

### Analysis

题目中的 Chips 消失机制即对应着在 $2\times n$ 的网格图中找这些 Chips 初始位置的[最小斯坦纳树](https://www.luogu.com.cn/problem/P6192)。

![](https://cdn.luogu.com.cn/upload/image_hosting/wiojcnzg.png)

当然这道题没有那个这么难。

***

**结论：** 此图必然有一个最小斯坦纳树，使得两个相邻列之间的 $2$ 条边最多选择 $1$ 条。

证明略（非常显然，读者自证）。

***

所以只要 $1\to n$ 遍历每一列，记录与上一列连接的是上边还是下边的最小边数，再按当前列 Chips 的状态分类递推（共 $4$ 中状态）。

时间 $O(n)$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010

char ch;
int n,b[N];
pair<int,int> a[N];
void work(){
	cin>>n;
	For(i,1,n){
		cin>>ch;
		a[i].fir=ch=='*';
	}
	For(i,1,n){
		cin>>ch;
		a[i].sec=ch=='*';
	}
	b[n+1]=0;
	Rof(i,n,1) b[i]=b[i+1]+a[i].fir+a[i].sec;
	bool flag=0;
	int a1=1,a2=1,b1,b2;
	For(i,1,n){
		if(!flag && b[i]-b[i+1]==0) continue;
		if(!flag){
			flag=1;
			if(a[i].fir) a2=2;
			if(a[i].sec) a1=2;
			continue;
		}
		if(b[i]==0) continue;
		if(a[i].fir==1 && a[i].sec==1){
			b1=b2=2+min(a1,a2);
		}
		if(a[i].fir==1 && a[i].sec==0){
			b1=1+min(a1,1+a2);
			b2=2+min(a1,a2);
		}
		if(a[i].fir==0 && a[i].sec==1){
			b1=2+min(a1,a2);
			b2=1+min(1+a1,a2);
		}
		if(a[i].fir==0 && a[i].sec==0){
			b1=1+min(a1,1+a2);
			b2=1+min(a2,1+a1);
		}
		a1=b1;
		a2=b2;
	}
	cout<<min(a1,a2)-1<<endl;
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```



---

