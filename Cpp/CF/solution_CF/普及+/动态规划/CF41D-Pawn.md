# Pawn

## 题目描述

国际象棋棋盘最底行站了一个兵。 它只有两种行动方式： 向上左或向上右走。 它可以选择从最低行哪个节点开始他的旅程。

每个格子上有 $0-9$ 颗豌豆，而士兵想移动到最上一行并且积累到尽可能多的豌豆。同时，因为这个士兵必须把豌豆平均分给自己和他的 $k$ 个兄弟，他所收集到的豌豆必须是 $k+1$ 的倍数。请找到他可以收集到的最多豌豆，并确定他的操作序列。

规定士兵不能手动扔出豌豆，并且他必须捡起所到达的每一个格子的所有豌豆。

## 样例 #1

### 输入

```
3 3 1
123
456
789
```

### 输出

```
16
2
RL
```

## 样例 #2

### 输入

```
3 3 0
123
456
789
```

### 输出

```
17
3
LR
```

## 样例 #3

### 输入

```
2 2 10
98
75
```

### 输出

```
-1
```

# 题解

## 作者：lenlen (赞：17)

很好的一道 DP 题。

### Problem

题目大意：给定一个棋盘，你从最下面一行任选一个位置开始移动，每次只能向右上方或者左上方移动，求满足经过路径的权值和是 $k+1$ （给定常数）的倍数的情况下最大权值和是多少。

数据范围： $n,m \leq 100,k \leq 10$。

### Solution

为了接下来的表述，我们将题目中的 $k$ 换用 $p$ 来表示。

不看权值和是 $p+1$ 的倍数这个条件，很板子的一道 DP，然后加上这个条件，就不知道怎么设二维状态了。

后来看了一眼题解，看到了第一句话： DP 不了，再加一维。觉得这句话很精髓。

我们可以设 $dp_{i,j,k}$ 表示在 $i,j$ 位置能否达到权值为 $k$，值域就是 $\{0,1\}$。然后转移也就变得简单了：

$$dp_{i,j,k}=dp_{i+1,j-1,k-a_{i,j}} \mid dp_{i+1,j+1,k-a_{i,j}}$$

（其中 $\mid$ 是或运算符）

当然边界超出之类的问题就不再多说了。注意你是从最后一行开始移动，所以横坐标要逆向枚举。最后我们可以先计算出可能的最大值 $x$（也就是枚举 $k$ 的边界），最后计算 $\max\limits_{j=1}^m dp_{1,j,ap}(a \in \mathbb N)$ 即可得出答案。

本题还有一个要输出的东西，就是你所经过的路径，这点其实很好办，我们在更新状态的时候，看看该状态是从哪种状态更新过来的，顺便记录一下就可以了，可能有点抽象，具体看代码实践。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=107;
int n,m,t;
int f[N][N][N<<4];
char w[N][N][N<<4],ans[N];
int a[N][N],mx,maax;
string s;
int main()
{
    scanf("%d%d%d",&n,&m,&t);t++;
    for(int i=1;i<=n;i++)
    {
        cin>>s;s='?'+s;
        maax=0;
        for(int j=1;j<=m;j++) a[i][j]=s[j]-'0',maax=max(maax,a[i][j]);
        mx+=maax;//这就是k的上界，k的大小不可能超过mx
    }
    for(int i=1;i<=m;i++) f[n+1][i][0]=1;
    for(int i=n;i>=1;i--)//枚举横纵坐标
    for(int j=1;j<=m;j++)
    for(int k=mx;k>=a[i][j];k--)
    {
        if(j>1) 
        {
            if(f[i+1][j-1][k-a[i][j]]) w[i][j][k]='R';//这个部分和下面类似的部分就是记录到达该点的应走的状态
            f[i][j][k]|=f[i+1][j-1][k-a[i][j]];
        }
        if(j<m) //是m不是n
        {
            if(f[i+1][j+1][k-a[i][j]]) w[i][j][k]='L';
            f[i][j][k]|=f[i+1][j+1][k-a[i][j]];
        }
    }
    int flag=0;
    for(int k=mx/t*t;k>=0&&!flag;k-=t)//枚举t的倍数
    for(int i=1;i<=m&&!flag;i++) 
    {
        if(f[1][i][k]) //找到答案的话，因为我们是从大到小寻找，所以第一个找到的答案必然是最优解
        {
            flag=1;
            printf("%d\n",k);
            int x=1,y=i,z=k;
            while(x!=n)
            {
                ans[x]=w[x][y][z];
                z-=a[x][y];
                if(ans[x]=='R') y--;
                else y++;
                x++;
            }
            printf("%d\n",y);
            for(int i=n-1;i;i--) cout<<ans[i];
            cout<<"\n";
            break;
        }
    }
    if(!flag) printf("-1\n");
}
```


---

## 作者：Sagittarius (赞：11)

大致思路：本题显然是DP，如果没有整除这个限制是非常简单的。而本题要求最后的豌豆数能被k+1整除，因此不能单纯地追求豌豆数最大。原本的二维f[i][j]也不适用了。

先贤名言：DP不了，再加一维。

f[i][j][k]表示到达i,j的时候k个豆子能否取到。能则为1否则为0。枚举i,j,k，时间复杂度O(n×m×n×9),每次从f[i+1][j-1][k-a[i][j]]和f[i+1][j+1][k-a[i][j]]转移过来。

答案：从大到小枚举k，枚举j，如果k能被总人数整除，而且f[1][j][k]==1，输出答案。

至于路径，在转移的时候顺便记录。详见代码：

```cpp
#include<bits/stdc++.h>
#define maxnm 110
#define maxp 15
#define fsb(a,b,c) for (int a=b;a<=c;a++)
#define fbs(a,b,c) for (int a=b;a>=c;a--)
using namespace std;
int n,m,p,a[maxnm+1][maxnm+1],f[maxnm+1][maxnm+1][maxp*maxnm+1];//f的第三维应是可能的最大总豆数
char d[maxnm+1][maxnm+1][maxp*maxnm+1],t[maxnm+1];
inline int check(int x,int y){
	return 1<=y&&y<=m;
}
inline void dfs(int x,int y,int k){
	if (x==n){
		printf("%d\n",y);return;
	}
	if (d[x][y][k]=='R') dfs(x+1,y-1,k-a[x][y]);else dfs(x+1,y+1,k-a[x][y]);
	printf("%c",d[x][y][k]);
}
int main(){
	scanf("%d%d%d",&n,&m,&p);
	fsb(i,1,n){
		t[0]='+';scanf("%s",t+1);
		fsb(j,1,m) a[i][j]=t[j]-'0';
	}
	memset(f,0,sizeof(f));fsb(j,1,m) f[n][j][a[n][j]]=1;
	fbs(i,n-1,1)fsb(j,1,m)fsb(k,a[i][j],maxp*maxnm){
		if (check(i+1,j-1)&&f[i+1][j-1][k-a[i][j]]){
			f[i][j][k]=1;d[i][j][k]='R';
		}
		if (check(i+1,j+1)&&f[i+1][j+1][k-a[i][j]]){
			f[i][j][k]=1;d[i][j][k]='L';
		}//从两个方向转移
	}
	fbs(k,maxp*maxnm,0){
		if (k%(p+1)!=0) continue;
		fsb(j,1,m)
			if (f[1][j][k]){
				printf("%d\n",k);dfs(1,j,k);//输出路径
				return 0;
			}
	}
	printf("-1\n");return 0;
}
```

---

## 作者：JWRuixi (赞：5)

这是一道很好的 dp 题，~~我想了好久。。。~~

- 题意

在 $n \times m$ 棋盘上延斜线走，使得路径上的数和为 $k$ 的倍数且最大，输出这个最大值并输出路径和起始的列数，从第 $n$ 行走到第一行。

- 分析

考虑先去掉被 $k$ 整除的性质，那么就是一个很见到的二维 dp，直接设 $f_{i,j}$ 为走到 $(i,j)$ 的最大值，显然状态转移方程为：

$$f_{i,j}=\max\{f_{i+1,j-1},f_{i+1,j+1}\}+a_{i,j}$$

现在考虑加上限制，发现做不了，所以只能加上一维，时间通不过再优化，设 $f_{i,j,r}$ 表示走到 $(i,j)$ 且模 $k$ 余 $r$ 的最大值。那么上一个的余数显然可以用这一个倒退回去，即：

$$f_{i,j}=\max\{f_{i+1,j-1,r^\prime},f_{i+1,j+1,r^\prime}\}+a_{i,j}$$

其中满足：$r^\prime=(r-a_{i,j}\bmod (k+1)+(k+1))\bmod (k+1)$

至于路径吗，在 dp 的过程中记录下上以个转移的是右还是左，在用 dfs 退回去就完了。

时间复杂度 $O(n^2m)$，可以通过本题。

- code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 105;

int a[maxn][maxn], n, m, mod, f[maxn][maxn][maxn];
char trs[maxn][maxn][maxn];

void print (int i, int j, int k) {
	if (i == n) {
		write(j);
		puts("");
		return;
	}
	if (trs[i][j][k] == 'L') {
		print(i + 1, j + 1, (k - a[i][j] % mod + mod) % mod);
		putchar('L');
		return;
	}
	if (trs[i][j][k] == 'R') {
		print(i + 1, j - 1, (k - a[i][j] % mod + mod) % mod);
		putchar('R');
		return;
	}
}

signed main () {
	n = read(), m = read(), mod = read() + 1;
	for (int i = 1; i <= n; i++) {
		char s[maxn];
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) {
			a[i][j] = s[j] - '0';
		}
	}
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= m; i++) f[n][i][a[n][i] % mod] = a[n][i];
	for (int i = n - 1; i; i--) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < mod; k++) {
				int l = f[i + 1][j + 1][(k - a[i][j] % mod + mod) % mod], r = f[i + 1][j - 1][(k - a[i][j] % mod + mod) % mod];
				if (j + 1 <= m && ~l && f[i][j][k] < l + a[i][j]) {
					f[i][j][k] = l + a[i][j];
					trs[i][j][k] = 'L';
				} 
				if (j - 1 >= 1 && ~r && f[i][j][k] < r + a[i][j]) {
					f[i][j][k] = r + a[i][j];
					trs[i][j][k] = 'R';
				} 
			}
		}
	}
	int now = 0;
	for (int i = 1; i <= m; i++) {
		if (f[1][now][0] < f[1][i][0]) now = i;
	}
	if (f[1][now][0] == -1) return puts("-1"), 0;
	write(f[1][now][0]), puts("");
	print(1, now, 0);
}
```

---

## 作者：FanYongchen (赞：4)

这道题，乍一看，是一道很简单的二维 dp 。

但是题目中说：**他所收集到的豌豆必须是 $k+1$ 的倍数**。

所以，原来的二维 dp 就不行了。

怎么办？再加一维。

$f_{i,j,k}$ 表示第 $i$ 行第 $j$ 列收集的豌豆数除以 $p$ （题目描述中的 $k$）所得的余数为 $k$ 时的最大豌豆数。

这里记 $a_{i,j}$ 为第 $i$ 行第 $j$ 列的豌豆数。

那么，对于 $f_{i,j,k}$ ，从第 $i+1$ 行第 $j-1$ 列和第 $i+1$ 行第 $j+1$ 列走过来时的余数 $y$ 应该为 $(k-a_{i,j}\bmod p+p)\bmod p$.

那么即可推出状态转移方程：

对于 $f_{i,j,k}$，这里记 $y=(k-a_{i,j}\bmod p+p)\bmod p$.

$f_{i,j,k}=\max(f_{i+1,j+1,y},f_{i+1,j-1,y})+a_{i,j}$.

当然也要看 $f_{i+1,j+1,y},f_{i+1,j-1,y}$ 有没有走过。

但是答案还要输出路径。

这里我们可以用一个栈保存路线，然后判断这是从左边走过来的还是从右边走过来的就行了。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <stack>
#include <cmath>
#include <ctime>
using namespace std;
#define ms(x,y) memset(x,y,sizeof(x))
#define mc(x,y) memcpy(x,y,sizeof(x))
int n,m,p;
int a[105][105];
int f[105][105][15];
int main()
{
    clock_t t1=clock();
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif//这些都不用管

//=================================='
    ms(f,-1);//先全部赋值成走不到
    cin>>n>>m>>p,p++;//这里有p+1个人
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            char c;
            cin>>c;
            a[i][j]=c-'0';//输入要注意
        }
    for(int j=0;j<m;j++) f[n-1][j][a[n-1][j]%p]=a[n-1][j];//初始状态
    for(int i=n-2;i>=0;i--)//倒着推上去
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<p;k++)
            {
                int x=(k-a[i][j]%p+p)%p;
                if(j>0&&f[i+1][j-1][x]!=-1) f[i][j][k]=max(f[i][j][k],f[i+1][j-1][x]+a[i][j]);
                if(j<m-1&&f[i+1][j+1][x]!=-1) f[i][j][k]=max(f[i][j][k],f[i+1][j+1][x]+a[i][j]);
                //注意，这里要判读是否在边界和是否能走到
            }
        }
    }
    int pos=0;//寻找最大值
    for(int i=1;i<m;i++)
        if(f[0][i][0]>f[0][pos][0]) pos=i;
    if(f[0][pos][0]==-1) cout<<(-1);//无解
    else
    {
        cout<<f[0][pos][0]<<"\n";
        stack<char> ans;//用栈保存，因为这里是倒退回去的
        int j=pos;//从pos开始走
        int x=0,y=0;
        //x表示当前的余数
        //y表示走过来时应该的余数
        for(int i=0;i<n-1;i++)
        {
            y=(x-a[i][j]%p+p)%p;//求出应该的余数
            if(j==0) ans.push('L'),j++;
            else if(j==m-1) ans.push('R'),j--;//边界情况
            else if(f[i][j][x]==f[i+1][j+1][y]+a[i][j]) ans.push('L'),j++;
            else ans.push('R'),j--;//判断是从哪走过来的
            x=y;
        }
        cout<<j+1<<"\n";//这里下标从0开始，但答案从1开始。
        while(!ans.empty()) cout<<ans.top(),ans.pop();
    }
//==================================

    cerr<<"Time used:"<<clock()-t1<<"ms"<<"\n";//这也不用管
    return 0;
}
```

---

## 作者：ncwzdlsd (赞：3)

显然，这是一道 DP 题。

大佬曾说，DP 不了，再加一维。由于题目要求了“权值和是 $k+1$ 的倍数”这个条件限制，所以单纯地使用二维 DP 并不能很好地解决这个问题，于是乎我们要祭出三维 DP 大法，判断士兵所在位置能否满足豌豆数的要求。

我们设 $f(i,j,k)$ 表示士兵在位置 $(i,j)$ 能否获得价值为 $k$ 的豌豆，用数组 $a_{i,j}$ 来存储矩阵，就可以列出状态转移方程：

$$
f(i,j,k)=f(i+1,j-1,k-a_{i,j})
$$

或

$$
f(i,j,k)=f(i+1,j+1,k-a_{i,j})
$$

类似这种用 DP 思想记录能否实现的题目还有很多，感兴趣的同学可以找找。

除此之外，还要注意的是，由于移动是从最后一行开始的，所以在枚举状态的时候，我们要选择倒着枚举。最后在得到解时，我们只需要在所有可能的情况下取最大值即可。

题目还要求输出路径，这个的实现也比较简单，我们只需要在搜索的过程中，记录一下上一个转移来的状态即可。

代码实现也比较简单，这里就不给了，实在不会的可以参考其他题解，要自己思考哟！

---

## 作者：KillerXu (赞：3)

挺有意思的一道题，如果仅仅是积累到最多的豌豆，方程很好写：

$$f[i][j]=max\{ f[i+1][j-1],f[i+1][j+1]\}+a[i][j]$$

但是要求答案能整除$k+1$，这样转移显然就不行了。

那我们就将所有到这个点的得分都记录下来！设$f[i][j][k]$为到达$i$行$j$列这个点，能否能得分$k$。能为$1$，不能为$0$。

那么只要由$f[i+1][j-1][k-a[i][j]]$和$f[i+1][j+1][k-a[i][j]]$转移过来就行了。至于路径的记录，只需要再开一个和$f$一样大的数组，转移时记录路径，输出时，只需要找到一个正确的终点，然后按照记录的路径递推回去，递推时把路径序列记录下来，最后输出即可。

## Code
```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define N 105

using namespace std;

int n , m , K;
int a[N][N];
struct data{
	bool check;//记录能否能得到 
	char way;//记录路径 
}f[N][N][5005];
char t[N];

int main(){
	cin >> n >> m >> K;
	for(int i = 1; i <= n; i++){
		cin >> t;
		for(int j = 1; j <= m; j++) a[i][j] = t[j - 1] - '0';
	}
	for(int j = 1; j <= m; j++) f[n][j][a[n][j]].check = 1;//初始化 
	for(int i = n - 1; i >= 1; i--)
	 for(int j = 1; j <= m; j++)
	  for(int k = N * 15; k >= a[i][j]; k--){
	   	if(j - 1 > 0 && f[i + 1][j - 1][k - a[i][j]].check){//判断能否能转移 
	   		f[i][j][k].check = 1; 
			if(f[i][j][k].check) f[i][j][k].way = 'R';//记录路径 
	    }
	    if(j + 1 <= m && f[i + 1][j + 1][k - a[i][j]].check){//同上 
	    	f[i][j][k].check = 1;
	    	if(f[i][j][k].check) f[i][j][k].way = 'L';
	    }
	  }
	int j = 0;//记录答案的位置 
	int maxn = 0;//记录答案 
	for(int k = N * 15; k >= 0; k--){//枚举答案 
		if(k % (K + 1) == 0){//答案是否满足要求 
			for(int i = 1; i <= m; i++) if(f[1][i][k].check) {maxn = k; j = i; break;}//有满足答案的，就记录下来 
		}
		if(j != 0) break;
	}
	if(j == 0){ printf("-1"); return 0; }//没有答案输出-1 
	printf("%d\n" , maxn);
	for(int i = 1; i <= n - 1; i++){//递推记录路径 
		t[i] = f[i][j][maxn].way;
		int T = maxn;
		maxn -= a[i][j];
		if(f[i][j][T].way == 'L') j++; else j--;
	}
	
	printf("%d\n" , j);
	for(int i = n - 1; i >= 1; i--) printf("%c" , t[i]);
	return 0;
}
```

---

## 作者：火羽白日生 (赞：3)

> 给定 $n$ 行 $m$ 列的矩阵，每个格子都有一个权值，有两种行动方式： 向左上或向右上走，要求从最低层到最高层获取权值和最大且为 $k+1$ 的倍数，求：最大权值和，起始位置和一个可行的移动序列。

如果没有 $k+1|\sum w$ 的限制的话就是个简单的 DP。

秉持 DP 不了再加一维的想法，在原来的想法上再加一维 $k$。

设 $f_{i,j,k}$ 为在点 $(i,j)$ 时且已获得权值为 $k$ 是否可行，转移有：

$$f_{i,j,k}=\begin{cases}[f_{i+1,j-1,k-a_{i,j}}=1] & j-1\geq 1\\ [f_{i+1,j+1,k-a_{i,j}}=1] & j+1\leq m\end{cases}$$

为了获得最大权值和，倒序枚举所有可能的权值和，找到第一个满足 $k+1|\sum w$ 且满足 $f_{1,i,\sum w}=1$ 的数并记录。

移动序列的话就在转移 $f$ 数组的时候顺便记录一下，最后递推回去即可。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=105,maxk=15;
	
	int n,m,K;
	int a[maxn][maxn];
	bool f[maxn][maxn][maxn*maxk+5];
	char pos[maxn][maxn][maxn*maxk+5],stk[maxn];
	
	inline int main(){
		n=read(); m=read(); K=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				char ch; cin>>ch;
				a[i][j]=ch-'0';
			}
		for(int i=1;i<=m;i++) f[n][i][a[n][i]]=1;
		for(int i=n-1;i>=1;i--)
			for(int j=1;j<=m;j++)
				for(int k=maxn*maxk;k>=a[i][j];k--){// 转移并记录移动序列
					if(j-1>=1 && f[i+1][j-1][k-a[i][j]]){
						f[i][j][k]=1;
						pos[i][j][k]='R';
					}
					if(j+1<=m && f[i+1][j+1][k-a[i][j]]){
						f[i][j][k]=1;
						pos[i][j][k]='L';
					}
				}
		int j=0,ans=0;
		for(int k=maxn*maxk;k>=0;k--){// 选择权值最大且满足要求的数
			if(k%(K+1)==0)
				for(int i=1;i<=m;i++)
					if(f[1][i][k]){
						ans=k,j=i;
						break;
					}
			if(j) break;
		}
		if(!j){puts("-1"); exit(0);}
		printf("%d\n",ans);
		for(int i=1;i<=n-1;i++){// 递推移动序列
			stk[i]=pos[i][j][ans];
			int tmp=ans;
			ans-=a[i][j];
			if(pos[i][j][tmp]=='L') j++;
			else j--;
		}
		printf("%d\n",j);
		for(int i=n-1;i>=1;i--) printf("%c",stk[i]); puts("");
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Durancer (赞：3)

### 前言

> 当你觉得这是个DP,但是不能DP的时候，记得加上一维  - cxk

### 思路

一个很清新的二维矩阵构造题目，只是考验设状态的能力，这个构造其实没什么难的，递归处理即可。

那就一步步深入设计状态吧。

首先看到二维，先想着 $f_{i,j}$ 表示到了 $(i,j)$ 位置能拿到的最大值。

一般来说我们就可以直接按照层数进行枚举转移了，但是偏偏有一个神奇的限制条件，要被 $k+1|f_{i,j}$。

注意，这是一个条件，是可以用 $\text{true/false}$ 来表示的，既然二维的无法表示完全，那么是不是可以考虑三维的，反正数据范围特别小，可以撑开。

那么我们来思考第三维可以用来干甚么。

现在的候选值有 **从左下/右下转移过来的**，**能够拿到的值**，**最大可以拿到的值**。

这个时候就应该开始想，如果是第一个，那么第三位肯定是 $\text{0/1}$ 无疑了，可是还是得不到我们想要的能否记录被整除，那么就继续思考别的方法。第一个已经去除嗲掉了。

继续思考第二个，能够拿到的值？这个看起来确实很吸引人，因为只要能够知道到一个位置能够取到那些值，然后枚举一下最大值，那不就出来了嘛，而且根据在矩阵中移动的情况来看，最多的取值就仅仅只有 $100\times 9=900$ ，可以撑得下！枚举所有值依旧不在话下。

看第三个，和 $f_{i,j}$ 能干的事一样，所以就**感谢投稿，不予通过**。

所以我们就非常愉快的设计出了状态转移方程为 $f_{i,j,k}$ 表示到了第 $(i,j)$ 的点，并且已经取完了这个位置的豌豆数量。

那么考虑转移，类似于一个背包的转移，不过 $f$ 数组是一个 $\text{bool}$ 类型的叭。

值得注意的是，发现 $f$ 数组无法记录路径，可以考虑在抓一个值来记录一下路径，然后就皆大欢囍了。

$$f_{i,j,k}|=f_{i+1,j-1,k-a_{i,j}},\text{if}\to \text{true},g_{i,j,k}=\text{R}$$

$$f_{i,j,k}|=f_{i+1,j+1,k-a_{i,j}},\text{if}\to \text{true},g_{i,j,k}=\text{L}$$

最后从最大值开始枚举，找到符合条件的直接递归处理即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int N=109;
const int M=2009;
const int B=2000;
int n,m,mod;//行，列，被k+1整除
int a[N][N];
int f[N][N][M];//拿起(i,j)的豆子来之后，（不）可以得到k？ 
char g[N][N][M];//"R""L" 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void prepare()
{
	for(int i=1;i<=m;i++)
		f[n][i][a[n][i]]=1;//标记 
}
void DP()
{
	for(int i=n-1;i>=1;i--)//行 
		for(int j=1;j<=m;j++)//列 
			for(int k=B;k>=a[i][j];k--)
			{
				if(j-1>=1)//从左下，移动到这里转移 
				{
					if(f[i+1][j-1][k-a[i][j]])
					{
						f[i][j][k]=1;
						g[i][j][k]='R';
					}
				}	
				if(j+1<=m)//从右下，移动到这个地方转移 
				{
					if(f[i+1][j+1][k-a[i][j]])
					{
						f[i][j][k]=1;
						g[i][j][k]='L';
					}
					
				}
			}
}
void output(int x,int y,int k)
{
	if(x==n) 
	{
		printf("%d\n",y);
		return;
	}
	if(g[x][y][k]=='R')//从左下转移 
	{
		output(x+1,y-1,k-a[x][y]);
		printf("R");
	}
	else if(g[x][y][k]=='L')
	{
		output(x+1,y+1,k-a[x][y]);
		printf("L");
	}
}
int main()
{
	n=read();
	m=read();
	mod=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%1d",&a[i][j]);
	prepare();
	DP(); 
	for(int i=M-2;i>=0;i--)//直接找最大 
	{
		if(i%(mod+1)!=0) continue;
		for(int j=1;j<=m;j++)
		{
			if(f[1][j][i])//有了
			{
				printf("%d\n",i);
				output(1,j,i);
				return 0; 
			}	
		} 
	}
	printf("-1\n");
	return 0;
}
```












---

## 作者：清尘 (赞：3)

[更好的阅读体验](https://www.cnblogs.com/whx666/p/10633305.html)

一道较为简单的dp，这里介绍一个时间和空间优化的方法

类似一个记录路径的数塔问题

## 一个小小的优化：

因为最后的结果要被 k+1 整除，所以可以记录到每一个点  对 k+1 取余结果不同的最优解（最大值），不用记录每一个数，浪费空间和时间，时间和空间复杂度降为   n * m * k

## 路径记录

再开两个数组分别记录每个最优解是由哪个状态转移而来的，输出时递归输出
递归过程
```cpp
void print (int x, int y, int q) {    // 递归到第x行，第y列，%(k+1) 的结果为q 
	if (x == n) printf ("%d\n", y);
	else {
		print (x + 1, y + ans[x][y][q].lr, ans[x][y][q].mod);
		if (ans[x][y][q].lr == 1) putchar ('L');
		else putchar ('R');
	}
}
```

## 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct e {int lr, mod;} ans[105][105][15]; //ans记录每一步方向及 %k的余数
int n, m, k, a[105][105], f[105][105][15], w; 
char ch;
void print (int x, int y, int q) {    // 递归到第x行，第y列，%(k+1) 的结果为q 
	if (x == n) printf ("%d\n", y);
	else {
		print (x + 1, y + ans[x][y][q].lr, ans[x][y][q].mod);
		if (ans[x][y][q].lr == 1) putchar ('L');
		else putchar ('R');
	}
}
int main(){
    scanf ("%d %d %d", &n, &m, &k); k++;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)  cin >> ch, a[i][j] = ch -'0';
    memset (f, -1, sizeof (f));
    for (int i = 1; i <= m; i++)  f[n][i][a[n][i]%k] = a[n][i];
    for (int i = n - 1; i; i--)
      for (int j = 1; j <= m; j++)
        for (int p = 0; p < k; p++) {
          int t = (p + a[i][j]) % k;
          if (j != 1 and f[i+1][j-1][p] >= 0) 
            f[i][j][t] = f[i+1][j-1][p] + a[i][j], ans[i][j][t] = (e) {-1, p};
          if (j != m and f[i+1][j+1][p] >= 0 and f[i+1][j+1][p] + a[i][j] > f[i][j][t]) 
            f[i][j][t] = f[i+1][j+1][p] + a[i][j], ans[i][j][t] = (e) {1, p};
        }
    for (int i = 1; i <= m; i++) if (f[1][i][0] > f[1][w][0]) w = i;  //找到起始位置 
    if (!w) {puts("-1"); return 0;}
    printf ("%d\n", f[1][w][0]);
    print (1, w, 0);
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# $\text{CF41D  - Prawn}$ 题解

## 题目大意

给你一个 $n\times m$ 的矩阵 $a$ ，你在第 $n$ 行（第几列由你选择），你每一次可以向左上或右上移动一步，移动到第 $1$ 行为止。

已知每个格子都有一个权值，你经过后就会获得这个权值，现在让你给出一种移动方案满足：

1. 经过的权值和 $w$ 满足 $k+1\mid w$。

2. 在满足第一条限制的情况下 $w$ 要尽可能的大。

输出 $w$ 和移动方案，数据范围保证：$n,m\le100,0\le a(i,j)\le9,0\le k\le 10$。

## 思路分析

用 $v$ 表示某一时刻路径上的权值和，$q=k+1$。

考虑不管第一条限制，那么这题就变成了一道极其类似这道[数字三角形](https://www.luogu.com.cn/problem/P1216)的题，直接 $dp(i,j)$ 表示走到 $(i,j)$ 后 $v$ 的最大值，随便转移两下即可解决。

 现在考虑加上第一条限制，还是考虑 dp。

> 设计 dp 状态的时候，没有限制什么是不能通过把 dp 状态增加一维解决的，如果有，那就把 dp 状态再加一维。
>
> ——沃·兹基硕得

所以我们可以设计出一个很合理的状态表示：$dp(i,j,r)$ 表示走到 $(i,j)$ 且满足 $v\equiv r\pmod{q}$ 的 $v$ 的最大值。

那么首先我们可以得出 dp 边界：
$$
dp\left(n,j,a(i,j)\bmod q\right)=a(n,j)\hspace{2cm}(1\le j\le m)
$$
这个式子的意义非常显然，就是对于第一行的每个位置 $(1,j)$，获得的权值只可能是 $a(1,j)$，所以此时的 $r$ 只能是 $a(1,j)\bmod q$。

接下来考虑状态转移，首先考虑方程的含义——对于每个状态只可能从左下或右下转移而来，那么方程也非常好写：
$$
\begin{aligned}
dp(i,j,r)&=\max\left(dp(i+1,j+1,r^\prime),dp(i+1,j-1,r^\prime\right)\\
r^\prime&=\left(r-a(i,j)\right)\bmod q
\end{aligned}
$$
首先考虑 $r^\prime$ 的意义：显然，$r^\prime$ 表示如果走到 $(i,j)$ 时 $v\equiv r\pmod q$，当且仅当走这步之前的权值和 $v^\prime$ 满足 $v^\prime\equiv r^\prime\pmod q$。

 $dp(i,j,r)$ 只可能从 $dp(i+1,j+1,r^\prime)$  或者 $dp(i+1,j-1,r^\prime)$ 这两个状态转移而来，分别代表这一步走的是左上还是右上，由于题目要求最大化 $v$ 所以要取个最大值。

然后计算答案 $ans$ 只需要在，由于答案一定是走到第 $1$ 行且 $v\equiv 0\pmod q$ 所以可以写出统计方程：
$$
ans=\max_{i=1}^mdp(1,i,0)
$$
最后输出方案，可以在状态转移的时候直接记录一下每一步是走得左上还是右上，递归输出一下即可，具体请看代码。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=105;
int dp[MAXN][MAXN][11],a[MAXN][MAXN],n,m,k,q;
char tr[MAXN][MAXN][11];
//tr表示对应转移到dp状态走的是左上还是右上 
inline void print(int x,int y,int r) {
	//递归输出答案,(x,y,r)等价于dp时的状态 
	if(x==n) {
		//到起点了,输出第几列 
		printf("%lld\n",y);
		return ;
	}
	if(tr[x][y][r]=='L') {
		//走左上,注意是(x+1,y+1)可以画图想一想为什么 
		print(x+1,y+1,(r-a[x][y]%q+q)%q);
		//由于这里是逆推,所以在回溯时输出 
		putchar('L');
	} else {
		//走右上,一样 
		print(x+1,y-1,(r-a[x][y]%q+q)%q);
		putchar('R');
	}
	return ;
}
signed main() {
	memset(dp,-1,sizeof(dp));
	//-1表示走不到 
	scanf("%lld%lld%lld",&n,&m,&k);
	q=k+1;
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=m;++j) {
			scanf("%1lld",&a[i][j]);
		}
	}
	for(register int i=1;i<=m;++i) dp[n][i][a[n][i]%q]=a[n][i];
	for(register int i=n-1;i>=1;--i) {
		for(register int j=1;j<=m;++j) {
			for(register int r=0;r<q;++r) {
				int L=dp[i+1][j+1][(r-a[i][j]%q+q)%q],R=dp[i+1][j-1][(r-a[i][j]%q+q)%q];
				//L表示前一步走左上的,R表示前一步走右上的 
				if(j+1<=m&&L!=-1) dp[i][j][r]=max(dp[i][j][r],L+a[i][j]); 
				if(j-1>=1&&R!=-1) dp[i][j][r]=max(dp[i][j][r],R+a[i][j]);
				//状态转移,注意不能越界,而且前一个状态可以走到 
				if(dp[i][j][r]==L+a[i][j]) tr[i][j][r]='L'; 
				if(dp[i][j][r]==R+a[i][j]) tr[i][j][r]='R';
				//记录走法，输出用 
			}
		}
	}
	int r=0;
	for(register int i=1;i<=m;++i) {
		if(dp[1][i][0]!=-1&&dp[1][i][0]>dp[1][r][0]) r=i;
		//找到最优情况的终点,根据每一步的转移方案逆推出起点和路径 
	}
	if(dp[1][r][0]==-1) {
		puts("-1");
		return 0;
		//走不到,无解 
	} 
	printf("%lld\n",dp[1][r][0]);
	print(1,r,0);
	return 0;
}
```



---

## 作者：NaN_HQJ2007_NaN (赞：0)

基础 DP 题。

定义 $f_{i,j,k}$ 表示从第一行走到 $(i,j)$，且数字总和模 $p$ 等于 $k$。

转移方程为：

$$
f_{i+1,j-1,(k+a_{i+1,j-1})\bmod p}=\max (f_{i,j,k}+a_{i+1,j-1})
$$

$$
f_{i+1,j+1,(k+a_{i+1,j+1})\bmod p}=\max(f_{i,j,k}+a_{i+1,j+1})
$$

同时还需要定义 $g_{i,j,k}$ 表示当前状态是由哪一种转移过来的。

注意边界情况。

复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100+5,inf=INT_MAX/2;
int n,m,p,f[N][N][11],a[N][N],g[N][N][11];
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>p;++p;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      char x;cin>>x;
      a[i][j]=x-'0';
      for(int k=0;k<p;++k)f[i][j][k]=-inf;
    }
  }
  for(int j=1;j<=m;++j)f[1][j][a[1][j]%p]=a[1][j];
  for(int i=1;i<n;++i){
    for(int j=1;j<=m;++j){
      for(int k=0;k<p;++k){
        int tk=(k+a[i+1][j-1])%p,val=f[i][j][k];
        if(j>1&&f[i+1][j-1][tk]<val+a[i+1][j-1]){
          f[i+1][j-1][tk]=val+a[i+1][j-1];
          g[i+1][j-1][tk]=1;
        }
        tk=(k+a[i+1][j+1])%p;
        if(j<m&&f[i+1][j+1][tk]<val+a[i+1][j+1]){
          f[i+1][j+1][tk]=val+a[i+1][j+1];
          g[i+1][j+1][tk]=0;
        }
      }
    }
  }
  int w=1;
  for(int j=1;j<=m;++j){
    if(f[n][j][0]>f[n][w][0]){
      w=j;
    }
  }
  if(f[n][w][0]<0){
    cout<<-1<<endl;
    return 0;
  }
  cout<<f[n][w][0]<<endl;
  cout<<w<<endl;
  int i=n,j=w,k=0;
  while(i>=2){
    if(g[i][j][k]){
      cout<<"R";
      k=(k-a[i][j]%p+p)%p;--i;++j;
    }else {
      cout<<"L";
      k=(k-a[i][j]%p+p)%p;--i;--j;
    }
  }
  return 0;
}

```


---

## 作者：technopolis_2085 (赞：0)

分析：

标准的动态规划题。

设计状态：

令 $dp_{i,j,x}$ 表示到了第 $i$ 列的第 $j$ 个格子，且目前豌豆数量为 $x$ 的倍数的最多豌豆数。

转移：

对于第 $i$ 行第 $j$ 列的格子，它可以从第 $i+1$ 行第 $j-1$ 个格子或者第 $j+1$ 个格子中转移过来。

从第 $n$ 行一直递推到第 $1$ 行。

然后我们在第一列中找到最大的一个值满足它是 $k+1$ 的倍数。如果找不到，就可以输出 $-1$ 并结束程序了。

最后是输出过程。

考虑逆序推导，对于第 $i$ 行，可以像 dfs 一样先把第 $i+1$ 行到第 $n$ 行的路径算出来，然后再输出第 $i+1$ 行到第 $i$ 行的路径。

推导完了以后第 $n$ 行的起点自然也就出来了。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=110;
char s[maxn][maxn];
int a[maxn][maxn];
int dp[maxn][maxn][15];
int n,m,k;
int start=-1;

vector<char> path;

void dfs(int x,int y,int num){
	if (x==n){
		start=y;
		return;
	}
	
//	printf("%d %d\n",x,y);
	
	if (start!=-1) return;
	
	if (y-1>=1&&dp[x+1][y-1][((num-a[x][y])%k+k)%k]+a[x][y]==dp[x][y][num]){
	//	printf("R: %d %d %d\n",dp[x+1][y-1][((num-a[x+1][y-1])%k+k)%k],a[x+1][y-1],dp[x][y][num]);
		dfs(x+1,y-1,((num-a[x][y])%k+k)%k);
		path.push_back('R');
	}
	
	if (start!=-1) return;
	
	if (y+1<=m&&dp[x+1][y+1][((num-a[x][y])%k+k)%k]+a[x][y]==dp[x][y][num]){
	//	printf("L: %d %d %d\n",dp[x+1][y+1][((num-a[x+1][y+1])%k+k)%k],a[x+1][y+1],dp[x][y][num]);
		dfs(x+1,y+1,((num-a[x][y])%k+k)%k);
		path.push_back('L');
	} 
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	k++;
	
	for (int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for (int j=1;j<=m;j++) a[i][j]=s[i][j]-'0';
	}
	
	memset(dp,-1,sizeof(dp));
	for (int i=1;i<=m;i++) dp[n][i][a[n][i]%k]=a[n][i];
	
	for (int i=n-1;i>=1;i--){
		for (int j=1;j<=m;j++){
			if (j-1>=0){
				for (int x=0;x<k;x++){
					if (dp[i+1][j-1][x]!=-1) dp[i][j][(x+a[i][j])%k]=max(dp[i][j][(x+a[i][j])%k],dp[i+1][j-1][x]+a[i][j]);
				}
			}
			
			if (j+1<=m){
				for (int x=0;x<k;x++){
					if (dp[i+1][j+1][x]!=-1) dp[i][j][(x+a[i][j])%k]=max(dp[i][j][(x+a[i][j])%k],dp[i+1][j+1][x]+a[i][j]);
				}
			}
		}
	}
	
	int ans=-1;
	int id=-1;
	for (int i=1;i<=m;i++){
		if (dp[1][i][0]!=-1){
			if (dp[1][i][0]>ans){
				ans=dp[1][i][0];
				id=i;
			}
		}
	}
	
	if (ans==-1){
		printf("-1\n");
		return 0;
	}
	
	printf("%d\n",ans);
	
	dfs(1,id,0);
	printf("%d\n",start);
	
	for (int i=0;i<(int)path.size();i++) printf("%c",path[i]);
	return 0;
}
```


---

## 作者：BigJoker (赞：0)

线性 DP

首先把 $k$ 自增 $1$

设 $f_{i,j,p}$ 表示当前走到 $(i,j)$，目前所获得的豌豆数量 $\bmod k$ 为 $p$ 的获得豌豆数量的最大值。

先初始化，由于从最后一排开始走的，而且并不知道初始是哪一个点。

所以 $f_{n,i,a_{n,i}\bmod k}\gets a_{n,i}$

先考虑第一问，状态转移很好写，从下一行中选择即可。

$f_{i,j,p}\gets \max\{f_{i+1,j-1,G(p-a_{i,j})}\,f_{i+1,j+1,G(p-a_{i,j})}\}$

$G(x)$ 表示 $x\bmod k$，该值为非负。

最后的答案就是 $\max\limits_{i=1}^{m} f_{1,i,0}$

解决了第一问，再来看二三问。

二三问其实也很好想，设 $pre_{i,j,p}$ 表示 $f_{i,j,p}$ 的答案是由 $(i+1,j-1)$ 转移而来还是由 $(i+1,j+1)$ 转移而来。

所以我们就可以根据 $pre$ 倒推路径，然后求起点和操作。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef long long LL;
const int N=1e2+5;
const int K=11;
il int qr(){
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') (ch=='-'?f=-1:1),ch=getchar();
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*f;
}
il void qw(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) qw(x/10);
	putchar(x%10+'0');
}
int n=qr(),m=qr(),k=qr()+1,f[N][N][K],pre[N][N][K],val[N][N],ans=-1,pos;
vector<char>lis;
int sub(int x,int y){
	return ((x-y)%k+k)%k;
}
void printfi(){
	int i=1,j=pos,p=0;
	while(i<n){
		if(~pre[i][j][p]) lis.push_back('L');
		else lis.push_back('R');
		int ii=i+1,jj=j+pre[i][j][p],pp=sub(p,val[i][j]);
		i=ii,j=jj,p=pp;
	}
	qw(j),putchar('\n');
}
void printse(){
	reverse(lis.begin(),lis.end());
	for(const char&i:lis) putchar(i);
}  
int main(){
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=m;j++){
			char x;
			cin>>x;
			val[i][j]=x-'0';
		}
	mem(f,128);
	for(re int i=1;i<=m;i++) f[n][i][val[n][i]%k]=val[n][i];
	for(re int i=n-1;i;i--)
		for(re int p=0;p<k;p++)
			for(re int j=1;j<=m;j++){
				f[i][j][p]=max(max(f[i+1][j-1][sub(p,val[i][j])]+val[i][j],f[i+1][j+1][sub(p,val[i][j])]+val[i][j]),f[i][j][p]);
				if(f[i][j][p]==f[i+1][j-1][sub(p,val[i][j])]+val[i][j]) pre[i][j][p]=-1;
				if(f[i][j][p]==f[i+1][j+1][sub(p,val[i][j])]+val[i][j]) pre[i][j][p]=1;
			}
	for(re int i=1;i<=m;i++) if(f[1][i][0]>ans) ans=f[1][i][0],pos=i;
	qw(ans);
	if(~ans) putchar('\n'),printfi(),printse();
	return 0;
}
```

---

## 作者：LunateCirno (赞：0)

一眼看去就是dp题，如果没有结果是K+1的倍数限制的话是道简单题。

常规方法状态表示是$dp[i][j]$，我们观察数据范围，发现仅仅是$100$，此时复杂度才到$100\times100$，对于1s的时间限制还有很多空余，于是我们可以想到在题目限制条件上在增加一维，此时观察到每位数字都小于$10$，一般限制数据大小的题目都会有使用到的可能性，可以发现即使每位都取到了最大，最后的数据也就$9\times100$的数据量，完全可以加一维，因此我们就得到了状态表示$dp[i][j][k]$，用bool数组$dp[i][j][k]$表示在$(i,j)$点上是否存在和为k的值，通过将一个节点左下、右下的结点，来更新当前结点的所有值，来获得当前结点所有值的可能性。
 
 最终运算次数为$100\times100\times9\times100$可以过
 
 最终通过循环，将$dp[1][j][k]$分别遍历j、k找到能被K+1整除的最大值保存即可。
 
 求路径的话可以先记录下最终的点，之后向前回溯，如果$dp[i-1][j-1/j+1][k-val[i][j]]=true$说明是从左/右结点转移过来的，将R/L压入栈内，最终将结果弹栈就是最终路径。
 
 最终代码(存储时从第n行开始，使得转移从1~n转移)
 
```cpp
 #include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3fffffff;
const int N = 105 + 5;
const int M = 9e2 + 5;
bool dp[N][N][M];
int dpmax[N][N], arr[N][N]; //dpmax用于保存dp[i][j][k]数组中最大值，减少遍历次数
stack<char> ans;            //用于存储路径
int main()
{
    int n, m, K;
    cin >> n >> m >> K;
    for (int i = n; i >= 1; i--)   //输入到数字数组中
    {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++)
            arr[i][j + 1] = s[j] - '0';
    }
    for (int i = 1; i <= m; i++)   //初始化第一行
    {
        dp[1][i][arr[1][i]] = true;
        dpmax[1][i] = arr[1][i];
    }
    for (int i = 2; i <= n; i++)  //从第二行开始更新
    {
        for (int j = 1; j <= m; j++)
        {
            int xl = i - 1, xr = i - 1;  // (xl,yl)表示左下点，(xr,yr)表示右下点
            int yl = j - 1, yr = j + 1;
            if (yl >= 1)        //如果合法，通过左下点更新，同时更新dpmax最大值
            {
                for (int k = 0; k <= dpmax[xl][yl]; k++)
                {
                    if (dp[xl][yl][k] == true)
                    {
                        dp[i][j][k + arr[i][j]] = true;
                        dpmax[i][j] = max(dpmax[i][j], k + arr[i][j]);
                    }
                }
            }
            if (yr <= m)        //如果合法，通过右下点更新，同时更新dpmax最大值
            {
                for (int k = 0; k <= dpmax[xr][yr]; k++)
                {
                    if (dp[xr][yr][k] == true)
                    {
                        dp[i][j][k + arr[i][j]] = true;
                        dpmax[i][j] = max(dpmax[i][j], k + arr[i][j]);
                    }
                }
            }
        }
    }
    int idx = 0;             //结束位置
    int maxx = -1;           //最大值
    for (int i = 1; i <= m; i++)            //寻找最后一行中符合结果的最大值，idx保存该数据y坐标
    {
        for (int k = dpmax[n][i]; k >= 0; k--)
        {
            if ((dp[n][i][k] == 1) && (k % (K + 1) == 0))
            {
                if (k > maxx)
                {
                    maxx = k;
                    idx = i;
                }
                break;
            }
        }
    }
    if (maxx == -1)          //不存在符合结果是直接输出-1
    {
        cout << -1;
    }
    else                     //存在结果，搜索路径，通过回溯
    {
        int idxmax = maxx;
        int sidx;            //保存起点坐标
        for (int i = n; i >= 2; i--)
        {
            int xl = i - 1, xr = i - 1;
            int yl = idx - 1, yr = idx + 1;
            int flag = 0;    //用于标识是否已经从一边找到了，防止使用两次
            if (yl >= 1)
            {
                if (dp[xl][yl][idxmax - arr[i][idx]] == true)
                {
                    ans.push('R');
                    flag = 1;
                    idxmax -= arr[i][idx];
                    idx = yl;
                    if (i == 2)
                        sidx = yl;
                }
            }
            if (yr <= m)
            {
                if (!flag && dp[xr][yr][idxmax - arr[i][idx]] == true)
                {
                    ans.push('L');
                    idxmax -= arr[i][idx];
                    idx = yr;
                    if (i == 2)
                        sidx = yr;
                }
            }
        }
        cout << maxx << endl
             << sidx << endl;
        while (!ans.empty())   //输出栈中数据
        {
            char temp = ans.top();
            ans.pop();
            cout << temp;
        }
    }
    //system("pause");
    return 0;
}
```


---

## 作者：strange757 (赞：0)

首先如果不考虑题目中豌豆数必须是 $k + 1$ 的倍数这个条件，那么 $dp$ 方程式非常好推， 可以注意到每个格子中的数都是小于等于9的， 且 $n <= 100$ ， 由此可以得出总数最多为900， 并不算大，多开一维完全开的下，所以可以想到 $dp$ 状态， $dp[i][j][k]$ 表示到达坐标 $i, j$ 时，总数是否能为 $k$ , 转移方程式为 

$f[i][j][s] = f[i + 1][j - 1][s - a[i][j]]|f[i + 1][j + 1][s - a[i][j]] $

至于行动序列，只要再开一个数组记录一下是从哪个位置走来的，然后递归输出答案即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N = 105;
int n, k, m, a[N][N];
int f[N][N][N*10], ans;
char s[N], d[N][N][N*10];
void dfs(int x, int y, int w){
	if(x == n) {
		printf("%d\n", y);
		return ;
	}
	if(d[x][y][w] == 'R')dfs(x + 1, y - 1, (w - a[x][y]));
	if(d[x][y][w] == 'L') dfs(x + 1, y + 1, (w - a[x][y]));
	cout << d[x][y][w] ;
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		scanf("%s", (s + 1));
		for(int j = 1; j <= m; j++){
			a[i][j] = s[j] - '0';
		}
	}
	ans = - 1;
	for(int i = 1; i <= m; i++) f[n][i][a[n][i]] = 1;
	for(int i = n - 1; i >= 1; i--){
		for(int j = 1; j <= m; j++){
			for(int s = a[i][j]; s <= 9 * n; s++){
				f[i][j][s] = f[i + 1][j - 1][s - a[i][j]]|f[i + 1][j + 1][s - a[i][j]];
				if(f[i + 1][j - 1][s - a[i][j]])d[i][j][s] = 'R';
				if(f[i + 1][j + 1][s - a[i][j]])d[i][j][s] = 'L';
				if(i == 1 && s %( k + 1) == 0 && f[i][j][s]) ans = max(ans, s);
			}
		}
	}
	if(ans == -1){
		printf("-1");
		return 0;
	}
	printf("%d\n", ans);
	for(int i = 1; i <= m; i++){
		if(f[1][i][ans]) {
			dfs(1, i, ans);
			return 0;
		}
	}
	return 0;
}
```

---

