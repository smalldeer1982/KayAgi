# Latin Square

## 题目描述

You are given a square matrix of size $ n $ . Every row and every column of this matrix is a permutation of $ 1 $ , $ 2 $ , $ \ldots $ , $ n $ . Let $ a_{i, j} $ be the element at the intersection of $ i $ -th row and $ j $ -th column for every $ 1 \leq i, j \leq n $ . Rows are numbered $ 1, \ldots, n $ top to bottom, and columns are numbered $ 1, \ldots, n $ left to right.

There are six types of operations:

- R: cyclically shift all columns to the right, formally, set the value of each $ a_{i, j} $ to $ a_{i, ((j - 2)\bmod n) + 1} $ ;
- L: cyclically shift all columns to the left, formally, set the value of each $ a_{i, j} $ to $ a_{i, (j\bmod n) + 1} $ ;
- D: cyclically shift all rows down, formally, set the value of each $ a_{i, j} $ to $ a_{((i - 2)\bmod n) + 1, j} $ ;
- U: cyclically shift all rows up, formally, set the value of each $ a_{i, j} $ to $ a_{(i\bmod n) + 1, j} $ ;
- I: replace the permutation read left to right in each row with its inverse.
- C: replace the permutation read top to bottom in each column with its inverse.

 Inverse of a permutation $ p_1 $ , $ p_2 $ , $ \ldots $ , $ p_n $ is a permutation $ q_1 $ , $ q_2 $ , $ \ldots $ , $ q_n $ , such that $ p_{q_i} = i $ for every $ 1 \leq i \leq n $ .One can see that after any sequence of operations every row and every column of the matrix will still be a permutation of $ 1, 2, \ldots, n $ .

Given the initial matrix description, you should process $ m $ operations and output the final matrix.

## 说明/提示

Line breaks between sample test case answers are only for clarity, and don't have to be printed.

## 样例 #1

### 输入

```
5
3 2
1 2 3
2 3 1
3 1 2
DR
3 2
1 2 3
2 3 1
3 1 2
LU
3 1
1 2 3
2 3 1
3 1 2
I
3 1
1 2 3
2 3 1
3 1 2
C
3 16
1 2 3
2 3 1
3 1 2
LDICRUCILDICRUCI```

### 输出

```
2 3 1 
3 1 2 
1 2 3 

3 1 2 
1 2 3 
2 3 1 

1 2 3 
3 1 2 
2 3 1 

1 3 2 
2 1 3 
3 2 1 

2 3 1 
3 1 2 
1 2 3```

# 题解

## 作者：George1123 (赞：30)

来菜园采菜啊 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/14162749.html)

---

## 题面

> [CF1458C Latin Square](https://www.luogu.com.cn/problem/CF1458C)

> $T$ 组测试数据，每次给一个 $n\times n$ 的矩阵，每行每列都是个 $1\to n$ 的排列。有 $m$ 次操作，如果是 `UDLR` 就是要把整个矩阵每行/每列往一个方向循环移动一格。如果是 `IC`，就是把矩阵每行/每列变成原来的逆矩阵。求最后的矩阵。

> 数据范围：$1\le T\le 1000$，$1\le \sum n\le 1000$，$1\le \sum m\le 10^5$，$1\le a_{i,j}\le n$。

---

## 题解

> 刚才有个群友问我 G 菜鸡发生肾摸事了，我说怎么回事？给我发了几张 `CF` 分数对比图，我一看！嗷！原来是昨天，我打了一场 `CF`，爆零了，掉分到 `newbie` ，又被嘲讽了。

为了方便下标从 $0$ 开始，即 $i,j,a_{i,j}$ 的范围都是 $[0,n)$。

如果只有 `UDLR` 操作，维护两位的错位即可。

这个 `IC` 操作有很多性质，比如先 `I` 再 `C` 和直接 `I` 形成的矩阵正好是右上-左下翻转关系。

假如把一个题目中描述的矩阵看成 $n\times n$ 个 $(i,j,a_{i,j})$ 三元组组成的集合，那么 `I` 就是让所有 $(i,j,a_{i,j})$ 变成 $(i,a_{i,j},j)$，`C` 就是让所有 $(i,j,a_{i,j})$ 变成 $(a_{i,j},j,i)$。

对于一个三元组 $(i,j,k)$，每次 `R` 就是让它变成 $(i,(j+1)\bmod n,k)$，`LDU` 同理。

所以可以维护对于每个三元组，原来的 $3$ 维现在变到哪了，以及 $3$ 维当前各有多少错位。

由于对于每个三元组情况是一样的，所以可以每次 $\Theta(1)$ 维护。

然后最后把矩阵按变化构造即可，总时间复杂度 $\Theta(n^2+m)$。

---

## 代码

我菜，参考了 `tourist` 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);i>=0;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1000;
int n,m,a[N][N][3],b[N][N];
int p[3],o[3],f[3];
string str;

//Main
void Main(){
    cin>>n>>m;
    R(t,3) f[o[t]=t]=0;
    R(i,n)R(j,n){
        cin>>a[i][j][2],--a[i][j][2];
        a[i][j][0]=i,a[i][j][1]=j;
    }
    cin>>str;
    for(char c:str){
        if(c=='R') f[1]++;
        else if(c=='L') f[1]--;
        else if(c=='D') f[0]++;
        else if(c=='U') f[0]--;
        else if(c=='I') swap(o[1],o[2]),swap(f[1],f[2]);
        else if(c=='C') swap(o[0],o[2]),swap(f[0],f[2]);
    }
    R(i,3) (((f[i]%=n)+=n)%=n);
    R(i,n)R(j,n){
        R(t,3) p[t]=(a[i][j][o[t]]+f[t])%n;
        b[p[0]][p[1]]=p[2];
    }
    R(i,n)R(j,n) cout<<b[i][j]+1<<" \n"[n-j==1];
    cout<<'\n';  
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t; for(cin>>t;t--;Main());
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：chen_03 (赞：14)

提供一种另类的做法 qwq

以下讨论均在模 $n$ 意义下进行。

如果只有 `U`、`D`、`L` 和 `R` 操作，给上下平移、左右平移分别打一个标记即可。

但是本题还有 `I` 操作和 `C` 操作。假设当前 $a_{i,j}=k$，经过 `RI` 操作就变成了 $a_{i,k}=j+1$。所以在维护 `I` 操作和 `C` 操作的同时，还要打一个全局加的标记。

所以，答案可以视作原矩阵经过一定的 `I` 操作和 `C` 操作，再向下平移 $x$ 格、向右平移 $y$ 格、全局加上 $z$ 得到的。

考虑每种操作会让 $x,y,z$ 发生怎样的变化：

- `U`：$a_{i,j}=k$ 变为 $a_{i-1,j}=k$。执行 $x\leftarrow x-1$ 即可。
- `D`：$a_{i,j}=k$ 变为 $a_{i+1,j}=k$。执行 $x\leftarrow x+1$ 即可。
- `L`：$a_{i,j}=k$ 变为 $a_{i,j-1}=k$。执行 $y\leftarrow y-1$ 即可。
- `R`：$a_{i,j}=k$ 变为 $a_{i,j+1}=k$。执行 $y\leftarrow y+1$ 即可。
- `I`：$a_{i,j}=k$ 变为 $a_{i,k}=j$。交换 $y,z$ 即可。
- `C`：$a_{i,j}=k$ 变为 $a_{k,j}=i$。交换 $x,z$ 即可。

但在向下平移 $x$ 格、向右平移 $y$ 格、全局加上 $z$ 之前，我们还要维护 `I` 操作和 `C` 操作。把操作序列中的 `I` 和 `C` 提取出来，组成一个新的序列。

由于 `II` 操作和 `CC` 操作相当于什么都不做，所以我们不断地删除序列中的 `II` 和 `CC`。这样得到的序列一定形如 `ICIC...` 或 `CICI...`。

到这里我们卡住了，这应该怎么维护呢 qwq

别急，设一开始 $a_{i,j}=k$，我们以 `ICIC...` 为例找找规律：

- `I`：$a_{i,k}=j$。
- `C`：$a_{j,k}=i$。
- `I`：$a_{j,i}=k$。
- `C`：$a_{k,i}=j$。
- `I`：$a_{k,j}=i$。
- `C`：$a_{i,j}=k$。

我们发现，执行 $6$ 次操作后，矩阵会恢复原样。`CICI...` 同理。所以，把序列的长度模 $6$，然后暴力操作即可。

时间复杂度 $\mathcal{O}(\sum n^2+m)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int T,n,m,a[1005][1005],b[1005][1005],x,y,z,bg,cnt;
char s[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				scanf("%d",&a[i][j]);
				--a[i][j];
			}
		}
		scanf("%s",s+1);
		x=y=z=cnt=0;
		for(int i=1;i<=m;++i){
			if(s[i]=='U')x=(x-1+n)%n;
			if(s[i]=='D')x=(x+1)%n;
			if(s[i]=='L')y=(y-1+n)%n;
			if(s[i]=='R')y=(y+1)%n;
			if(s[i]=='I'){
				swap(y,z);
				if(!cnt)cnt=1,bg=0;
				else (cnt&1)^bg?--cnt:++cnt;
			}
			if(s[i]=='C'){
				swap(x,z);
				if(!cnt)cnt=1,bg=1;
				else (cnt&1)^bg?++cnt:--cnt;
			}
		}
		cnt%=6;
		for(int k=1,kk=bg;k<=cnt;++k,kk^=1){
			if(kk==0)
				for(int i=0;i<n;++i)
					for(int j=0;j<n;++j)
						b[i][a[i][j]]=j;
			else
				for(int i=0;i<n;++i)
					for(int j=0;j<n;++j)
						b[a[i][j]][j]=i;
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)
					a[i][j]=b[i][j];
		}
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				printf("%d%c",(a[(i-x+n)%n][(j-y+n)%n]+z)%n+1," \n"[j==n-1]);
	}
	return 0;
}
```


---

## 作者：Warriors_Cat (赞：7)

[题面传送门](https://www.luogu.com.cn/problem/CF1458C)。

~~题意太长了不想描述，自己看吧qwq~~。

这题好神啊，思维含量真的高 orz。

---

### $Solution:$

很显然，如果这题只有 `RLDU` 这四个操作的话，那么就是一个 sb 题，直接维护行和列加了多少即可。

但，加上 `IC` 操作后，这题就变得有些困难了。

考虑 `IC` 操作的本质，对于一个坐标 $(i, a_i)$，其求逆操作其实就是变成 $(a_i, i)$。

照这样，我们考虑把每个点看成一个三维坐标 $(i, j, a_{i, j})$。进行 `I` 操作就相当于交换 $y$ 坐标和 $z$ 坐标，进行 `C` 操作就相当于交换 $x$ 和 $z$ 坐标。

于是每次我们都可以存储这个 $x, y, z$ 坐标现在对应的是什么类型，最后加回去就可以了。

很显然每一次操作都是 $O(1)$ 的，最后处理也是 $O(n \times n)$ 的。

over，时间复杂度为 $O(n^2 + m)$。没有任何的高级算法的思维题属实强。

---

### $Code:$

非赛时代码，码风可能有一点不同。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = y; i >= x; --i)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 1010, M = 100010;
int n, m, a[N * N][3], mov[10], pos[10], ans[N][N]; char s[M];
inline int id(int x, int y){ return (x - 1) * n + y; }
inline void work(){
	n = read(); m = read();
	rep(i, 1, n) rep(j, 1, n){
		int k = id(i, j);
		a[k][0] = i; a[k][1] = j; a[k][2] = read();
	}
	scanf("%s",  s + 1);
	rep(i, 0, 2) pos[i] = i, mov[i] = 0;
	rep(i, 1, m){
		if(s[i] == 'R') ++mov[pos[1]];
		if(s[i] == 'L') --mov[pos[1]];
		if(s[i] == 'D') ++mov[pos[0]];
		if(s[i] == 'U') --mov[pos[0]];
		if(s[i] == 'I') swap(pos[1], pos[2]);
		if(s[i] == 'C') swap(pos[0], pos[2]);
	}
	rep(i, 1, n * n){
		rep(j, 0, 2) a[i][j] = (a[i][j] + mov[j] - 1 + m * n) % n + 1;
		ans[a[i][pos[0]]][a[i][pos[1]]] = a[i][pos[2]];
	}
	rep(i, 1, n){
		rep(j, 1, n){
			printf("%d ", ans[i][j]);
		}
		puts("");
	}
}
int main(){ int T = read(); while(T--) work(); return 0; }
```


---

## 作者：STrAduts (赞：5)

一种少见的矩阵变换思维题。

在此，我们不再赘述暴力，考虑正解。

首先，对于逆排序其实就是将一个位置上的数变为这个数的行数或列数在原数组中所在行或列出现的地址。

也就是原题中说的：$p_{q_i} = i, i \in [1, n]$

定义原数组为 $a$，以 $a$ 为基础我们定义三元组 $(x, y, z)$，表示当前操作以后 $a_{(x, y)} = z, x \in [1, n], y \in [1, n]$。

那么不难发现，对原矩阵进行操作其实也可以转化成对三元组进行操作。如下。

- **R**：$(x, y, z)$ ---> $(x, y + 1, z)$
- **L**：$(x, y, z)$ ---> $(x, y - 1, z)$
- **D**：$(x, y, z)$ ---> $(x + 1, y, z)$
- **U**：$(x, y, z)$ ---> $(x - 1, y, z)$
- **I**：$(x, y, z)$ ---> $(x, z, y)$
- **C**：$(x, y, z)$ ---> $(z, y, x)$

实在不理解可以自己手构一个矩阵模拟一下。

很显然每一个操作都会对每一个三元组产生影响，也就是说我们只需要维护对应三元组中每个位置的变动量即可。

在操作执行完后，枚举 $x, y$，就会有 $ans_{(f(x + Δx), f(y + Δy))} = f(z + Δz), x \in [1, n], y \in [1, n]$。

其中 $f(x) = \left\{\begin{array} \\ x \mod n + n(x < 0) \\ n(n | x) \\ x \mod n(x \geq 0, n \nmid x); \end{array}\right.$

```cpp
#include <cstdio>

void Swap(int &x, int &y) {
	int t = x;
	x = y;
	y = t;
}

const int MAXK = 5;
const int MAXN = 1005;
const int MAXL = 1e5 + 5;
int a[MAXN][MAXN], op[MAXK], w[MAXK], n, m; 
char s[MAXL];
int ans[MAXN][MAXN];

int Mod(int x) {
	if(x < 0)
		return x % n + n;
	else {
		if(x % n == 0)
			return n;
		else
			return x % n;		
	}
}

int main() {
	int t;
	scanf ("%d", &t);
	while(t--) {
		scanf ("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) 
				scanf ("%d", &a[i][j]);
		for(int i = 0; i <= 3; i++) 
			op[i] = i, w[i] = 0;
		scanf ("%s", s + 1);
		for(int i = 1; i <= m; i++) {
			if(s[i] == 'R')
				w[op[2]]++;
			else if(s[i] == 'L')
				w[op[2]]--;	
			else if(s[i] == 'D')
				w[op[1]]++;
			else if(s[i] == 'U')
				w[op[1]]--;
			else if(s[i] == 'I')
				Swap(op[2], op[3]);
			else if(s[i] == 'C')
				Swap(op[1], op[3]);
		}
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++) {
				int temp[MAXK] = {0, i, j, a[i][j]};
				ans[Mod(temp[op[1]] + w[op[1]])][Mod(temp[op[2]] + w[op[2]])] = Mod(temp[op[3]] + w[op[3]]);
			}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++)
				printf("%d ", ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：5)

注意到 RLDU 和 IC 根本就不是一个性质的，很难一起在矩阵上面搞。我们考虑，初始的每个格子显然都对答案矩阵的恰好一个格子做出贡献，那么我们考虑拆开它们，考虑每个单个格子对答案矩阵的贡献。

我们考虑把一个格子看成三元组 $(i,j,a_{i,j})$。那么 RL 是在 $j$ 上面增减，DU 是在 $i$ 上面增减，IC 则是交换第一三或二三维。我们考虑对一开始的 $n^2$ 个三元组每个分别维护这 $m$ 次操作。优化点在于，将操作转化为这种抽象的事情之后，变得可合并了，即先后若干个操作可以压缩到一个新的 $\mathrm O(1)$ 的操作（这个套路类似于矩乘，还有之前某次洛谷月赛的 D2D），来用压缩操作的时间换取对所有元素做这么多次操作的时间。

那么我们维护这些操作合并起来是什么样子。每个三元组可能某一维会被增加，可能某两维会被交换。那么我们维护原先的每一维被加了多少，然后现在跑到了哪个位置上了即可。什么都是 $\mathrm O(1)$ 的。

**_[code](https://www.luogu.com.cn/paste/lmt11ap7)_**

---

## 作者：tzc_wk (赞：5)

现场被这题区分了/kk

首先要明确的一点是 LRUD 和 IC 肯定不是同一类的。如果 $s$ 中只包含 LRUD，那此题就变得异常简单。直接维护两个标记 $x,y$ 表示行/列分别位移了多少就可以了。

重头戏在于 I 和 C。首先我们要理解 I 和 C 的本质。

对于排列 $p_1,p_2,\dots,p_n$，我们如果把每个元素看作一个二维坐标 $(i,p_i)$，那么这个排列的逆元相当于 $(p_i,i)$，即交换两维坐标的值。

I 和 C 也是如此。如果我们把这个矩阵看作 $n^2$ 个三维空间里的点 $(i,j,a_{i,j})$，那么 I 操作其实就是交换 x,z 坐标的值，C 操作其实是交换 y,z 的值。

这样一来这题就很好做了，对于 LRUD，记录每一维的增量，对于 IC，记录当前每一维是原来的第几维，这样每个操作都可以 $\mathcal O(1)$ 解决了。

看到没？什么超纲的算法都没有。所以啊，菜是原罪/kk

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
template<typename T>
void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1000;
const int MAXM=1e5;
int n,m,a[MAXN*MAXN+5][3],b[MAXN+5][MAXN+5],p[3],x[3];
char s[MAXM+5];
void inc(int &x){x++;if(x>=n) x-=n;}
void dec(int &x){x--;if(x<0) x+=n;}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		scanf("%d",&a[(i-1)*n+j][2]);
		a[(i-1)*n+j][0]=i;a[(i-1)*n+j][1]=j;
	}
	for(int i=0;i<3;i++) p[i]=i,x[i]=0;scanf("%s",s+1);
	for(int i=1;i<=m;i++){
		if(s[i]=='U') dec(x[p[0]]);
		if(s[i]=='D') inc(x[p[0]]);
		if(s[i]=='L') dec(x[p[1]]);
		if(s[i]=='R') inc(x[p[1]]);
		if(s[i]=='I') swap(p[1],p[2]);
		if(s[i]=='C') swap(p[0],p[2]);
	}
//	for(int j=0;j<3;j++) printf("%d\n",x[j]);
	for(int i=1;i<=n*n;i++){
		for(int j=0;j<3;j++) a[i][j]=(a[i][j]-1+x[j])%n+1;
//		for(int j=0;j<3;j++) printf("%d ",a[i][j]);printf("\n");
		b[a[i][p[0]]][a[i][p[1]]]=a[i][p[2]];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) printf("%d ",b[i][j]);
		printf("\n");
	}
}
signed main(){
	int qu;scanf("%d",&qu);
	while(qu--) solve(); 
	return 0;
}
```

---

## 作者：luanyanjia (赞：4)

一个很傻的做法。

考虑同时维护原矩阵 $M$，行变换后的矩阵 $H$，列变换后的矩阵 $C$。那么以下操作对他们的影响就是：

- $R$：$M,C$ 向右移动，$H$ 所有元素加一（如果原来是 $n$ 就变回 $1$）。
- $L$：$M,C$ 向左移动，$H$ 所有元素减一（如果原来是 $1$ 就变成 $n$）。
- $D$：$M,H$ 向下移动，$C$ 所有元素加一（如果原来是 $n$ 就变回 $1$）。
- $U$：$M,H$ 向上移动，$C$ 所有元素减一（如果原来是 $1$ 就变成 $n$）。
- $I$：交换 $M,H$，$C$ 沿主对角线翻转。
- $C$：交换 $M,C$，$H$ 沿主对角线翻转。

同时维护三个矩阵的交换情况（一个排列），反转情况，加法 $tag$，平移情况即可。

证明一些结论：排列进行一次逆变换相当于 $(i,p_i)$ 变成 $(p_i,i)$，向右平移对应 $(i,p_i)$ 变成 $(i + 1,p_i)$，行变换之后自然变成 $(p_i,i+1)$，所以是整体加一。又考虑到，行变换后的第 $i$ 列对应所有 $i$ 在每一行中的位置，列同理。由于拉丁方的性质行变换的第 $i$ 列和列变换后的第 $i$ 行互为逆排列。这样翻转也得到解释了。

这是模拟赛搬的题的弱化，代码中省去了 IO 部分。

```cpp
#include<bits/stdc++.h>
const int MX=1005,MXK=100000;
int n,k,T;
char op[MXK+5];
short m[3][MX][MX];
inline void Add(short &a,short b){(a+=b)>=n?a-=n:1;}
inline short Sum(short a,short b){return (a+b)>=n?a+b-n:a+b;}
struct node{
    short rev[3],tag[3],x[3],y[3],p[3];
    node(){rev[0]=rev[1]=rev[2]=tag[1]=tag[2]=tag[0]=x[0]=x[1]=x[2]=y[0]=y[1]=y[2]=0;p[0]=0,p[1]=1,p[2]=2;}
    node(int n1,int n2,int n3,int n4,int n5,int n6,int n7,int n8,int n9,int n10,int n11,int n12,int n13,int n14,int n15){
        rev[0]=n1;rev[1]=n2;rev[2]=n3;
        tag[0]=n4;tag[1]=n5;tag[2]=n6;
        x[0]=n7;x[1]=n8;x[2]=n9;
        y[0]=n10;y[1]=n11;y[2]=n12;
        p[0]=n13;p[1]=n14;p[2]=n15;
    }
    inline node friend operator*(const node &a,const node &b){
        node c;
        c.tag[0]=Sum(a.tag[0],b.tag[a.p[0]]);
        c.tag[1]=Sum(a.tag[1],b.tag[a.p[1]]);
        c.tag[2]=Sum(a.tag[2],b.tag[a.p[2]]);
        c.rev[0]=a.rev[0]^b.rev[a.p[0]];
        c.rev[1]=a.rev[1]^b.rev[a.p[1]];
        c.rev[2]=a.rev[2]^b.rev[a.p[2]];
        c.x[0]=a.x[0];c.x[1]=a.x[1];c.x[2]=a.x[2];
        c.y[0]=a.y[0];c.y[1]=a.y[1];c.y[2]=a.y[2];
        if(!a.rev[0])Add(c.x[0],b.x[a.p[0]]),Add(c.y[0],b.y[a.p[0]]);
        else Add(c.x[0],b.y[a.p[0]]),Add(c.y[0],b.x[a.p[0]]);
        if(!a.rev[1])Add(c.x[1],b.x[a.p[1]]),Add(c.y[1],b.y[a.p[1]]);
        else Add(c.x[1],b.y[a.p[1]]),Add(c.y[1],b.x[a.p[1]]);
        if(!a.rev[2])Add(c.x[2],b.x[a.p[2]]),Add(c.y[2],b.y[a.p[2]]);
        else Add(c.x[2],b.y[a.p[2]]),Add(c.y[2],b.x[a.p[2]]);
        c.p[0]=b.p[a.p[0]];
        c.p[1]=b.p[a.p[1]];
        c.p[2]=b.p[a.p[2]];
        return c;
    }
};
node f[MXK+5];
inline void Solve(){
    io>>n>>k;
    node L=node(0,0,0,0,n-1,0,0,0,0,1,0,1,0,1,2);
    node R=node(0,0,0,0,1,0,0,0,0,n-1,0,n-1,0,1,2);
    node U=node(0,0,0,0,0,n-1,1,1,0,0,0,0,0,1,2);
    node D=node(0,0,0,0,0,1,n-1,n-1,0,0,0,0,0,1,2);
    node I=node(0,0,1,0,0,0,0,0,0,0,0,0,1,0,2);
    node C=node(0,1,0,0,0,0,0,0,0,0,0,0,2,1,0);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)io>>m[0][i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)m[1][i][m[0][i][j]-1]=j+1;
    for(int j=0;j<n;j++)
        for(int i=0;i<n;i++)m[2][m[0][i][j]-1][j]=i+1;
    io>>op;
    f[0]=node();
    for(int i=1;i<=k;i++){
        if(op[i-1]=='R')f[i]=f[i-1]*R;
        else if(op[i-1]=='L')f[i]=f[i-1]*L;
        else if(op[i-1]=='D')f[i]=f[i-1]*D;
        else if(op[i-1]=='U')f[i]=f[i-1]*U;
        else if(op[i-1]=='I')f[i]=f[i-1]*I;
        else f[i]=f[i-1]*C;
    }
    node now=f[k];
    int pos=0;
    for(int i=0;i<3;i++)if(now.p[i]==0)pos=i;
    for(int x=0;x<n;x++,io<<'\n'){
        for(int y=0;y<n;y++){
            short X=now.x[pos],Y=now.y[pos];
            if(now.rev[pos])Add(X,y),Add(Y,x);
            else Add(Y,y),Add(X,x);
            int tmp=Sum(m[pos][X][Y],now.tag[pos]);
            if(tmp>n)tmp-=n;
            if(tmp==0)tmp=n;
            io<<tmp<<' ';
        }
    }
}
int main(){
    io>>T;
    while(T--)Solve();
    return 0; 
}
```

---

## 作者：kernel_panic (赞：3)

模拟赛考了这题，赛时想出了一个用矩阵乘法的屑做法，常数巨大，没想到还跑的挺快。

## 思路
首先为了方便操作，我们让矩阵的行列编号都从 $0$ 开始，并且让所有元素都减 $1$。

前 $4$ 个操作显然可以用矩阵表示。我们把 $1$ 个元素 $a_{i,j}$ 在矩阵中的位置表示成向量 $\begin{bmatrix} i & j & 1 \end{bmatrix}$，变换矩阵如下：
$$
R=
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 1 & 1 \\
\end{bmatrix}
,
L=
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & -1 & 1 \\
\end{bmatrix}
,
D=
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
1 & 0 & 1 \\
\end{bmatrix}
,
U=
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
-1 & 0 & 1 \\
\end{bmatrix}
$$

考虑后 $2$ 个操作，不难发现对于 $1$ 个元素 $a_{i,j}$，对其施加 $\texttt{I}$ 变换的本质是将其列编号和值互换。$\texttt{C}$ 变换同理。

所以我们最终将 $a_{i,j}$ 表示成向量 $\begin{bmatrix} a_{i,j} & i & j & 1 \end{bmatrix}$，容易写出所有的变换矩阵：
$$
\begin{aligned}
  & R=
  \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & 1 & 1 \\
  \end{bmatrix}
  ,
  L=
  \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & -1 & 1 \\
  \end{bmatrix}
  ,
  D=
  \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 1 & 0 & 1 \\
  \end{bmatrix}
  ,
  U=
  \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & -1 & 0 & 1 \\
  \end{bmatrix}
  , \\
  &I=
  \begin{bmatrix}
  0 & 0 & 1 & 0 \\
  0 & 1 & 0 & 0 \\
  1 & 0 & 0 & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}
  ,
  C=
  \begin{bmatrix}
  0 & 1 & 0 & 0 \\
  1 & 0 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}
\end{aligned}
$$

对于操作序列，我们构造出矩阵后直接累乘。乘法在模 $n$ 意义下进行。

设变换完的矩阵为 $b$。对于 $a_{i,j}$，我们构造向量 $\begin{bmatrix} a_{i,j} & i & j & 1 \end{bmatrix}$，设乘上变换矩阵后的向量为  $\begin{bmatrix} c & x & y & 1 \end{bmatrix}$，让 $b_{x,y}\leftarrow c$ 即可。

输出时记得加 $1$。

时间复杂度 $O(nm)$。

## 代码
```cpp
#include <cstdint>
#include <iostream>

using i64 = int64_t;
constexpr size_t N = 1 << 10;
constexpr size_t M = 1 << 20;

int n, m;

struct mat {
    i64 _m[4][4];
    constexpr mat() : _m{} {}
    constexpr i64 &operator()(int i, int j) { return _m[i - 1][j - 1]; }
    constexpr const i64 &operator()(int i, int j) const { return _m[i - 1][j - 1]; }
    friend mat operator*(const mat &A, const mat &B) {
        mat R;
        for (int i = 1; i <= 4; i++) {
            for (int k = 1; k <= 4; k++) {
                for (int j = 1; j <= 4; j++) { R(i, j) = (R(i, j) + A(i, k) * B(k, j) % n + n) % n; }
            }
        }
        return R;
    }
    constexpr static mat R() {
        mat R;
        R(1, 1) = 1;
        R(2, 2) = 1;
        R(3, 3) = 1;
        R(4, 3) = R(4, 4) = 1;
        return R;
    }
    constexpr static mat L() {
        mat R;
        R(1, 1) = 1;
        R(2, 2) = 1;
        R(3, 3) = 1;
        R(4, 3) = -1, R(4, 4) = 1;
        return R;
    }
    constexpr static mat D() {
        mat R;
        R(1, 1) = 1;
        R(2, 2) = 1;
        R(3, 3) = 1;
        R(4, 2) = R(4, 4) = 1;
        return R;
    }
    constexpr static mat U() {
        mat R;
        R(1, 1) = 1;
        R(2, 2) = 1;
        R(3, 3) = 1;
        R(4, 2) = -1, R(4, 4) = 1;
        return R;
    }
    constexpr static mat I() {
        mat R;
        R(1, 3) = 1;
        R(2, 2) = 1;
        R(3, 1) = 1;
        R(4, 4) = 1;
        return R;
    }
    constexpr static mat C() {
        mat R;
        R(1, 2) = 1;
        R(2, 1) = 1;
        R(3, 3) = 1;
        R(4, 4) = 1;
        return R;
    }
    constexpr static mat E() {
        mat R;
        for (int i = 1; i <= 4; i++) R(i, i) = 1;
        return R;
    }
};

int a[N][N], b[N][N];
mat R = mat::R();
mat L = mat::L();
mat D = mat::D();
mat U = mat::U();
mat I = mat::I();
mat C = mat::C();

char opt[M];

int T;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> T;
    while (T--) {
        mat A = mat::E();
        std::cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> a[i][j];
                a[i][j] -= 1;
            }
        }
        std::cin >> opt;
        for (int i = 0; i < m; i++) {
            if (opt[i] == 'R') A = A * R;
            if (opt[i] == 'L') A = A * L;
            if (opt[i] == 'D') A = A * D;
            if (opt[i] == 'U') A = A * U;
            if (opt[i] == 'I') A = A * I;
            if (opt[i] == 'C') A = A * C;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int a = ((::a[i][j] * A(1, 1) + i * A(2, 1) + j * A(3, 1) + A(4, 1)) % n + n) % n;
                int x = ((::a[i][j] * A(1, 2) + i * A(2, 2) + j * A(3, 2) + A(4, 2)) % n + n) % n;
                int y = ((::a[i][j] * A(1, 3) + i * A(2, 3) + j * A(3, 3) + A(4, 3)) % n + n) % n;
                b[x][y] = a;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { std::cout << b[i][j] + 1 << " \n"[j == n - 1]; }
        }
        std::cout << "\n";
    }
    return 0;
}
```

---

## 作者：duyi (赞：3)

[更好的阅读体验（我要进来咯！！！）](https://www.cnblogs.com/dysyn1314/p/14163636.html)

# CF1458C Latin Square

[题目链接](http://codeforces.com/contest/1458/problem/C)

## 本题题解

发现 $\texttt{RLDU}$ 和 $\texttt{IC}$ 是完全不同的两类操作，将它们同时维护很困难。

本题的突破口是：初始时的每个格子，最终都会恰好对应答案里的一个格子。于是我们拆开来考虑每个格子对答案的“贡献”。

把一个格子看成三元组 $(i,j,a_{i,j})$，考虑一次操作会对这个三元组产生什么样的影响：

- $\texttt{R}$：$(x, y, z) \to (x,y + 1, z)$。注意，这里的加法是在 $\bmod n$ 意义下的，下同。
- $\texttt{L}$：$(x, y, z) \to (x, y - 1, z)$。注意，这里的减法是在 $\bmod n$ 意义下的，下同。
- $\texttt{D}$：$(x, y, z) \to (x + 1, y, z)$。
- $\texttt{U}$：$(x, y, z)\to (x - 1, y, z)$。
- $\texttt{I}$：$(x, y, z)\to (x, z, y)$。即交换 2, 3 两项。
- $\texttt{C}$：$(x, y, z)\to (z, y, x)$。即交换 1, 3, 两项。

发现转化后，这 $6$ 种对三元组进行的操作，是“可合并”的。

具体地，我们遍历要进行的 $m$ 个操作，就能预处理出：依次进行这些操作后，任意一个初始三元组会产生什么变化。

然后枚举每个格子，将预处理出的变化作用于这个格子上，就能知道这个格子最终对答案的贡献是什么。

时间复杂度 $\mathcal{O}(m + n^2)$。

## 参考代码

[小夫，我要进来咯！！！](https://www.cnblogs.com/dysyn1314/p/14163636.html)


---

## 作者：feecle6418 (赞：2)

考场上想到了大体思路，但是以为矩阵一定是一行循环同构来的所以一直 wa……

考虑这样一种暴力：求出每个格子从哪里来。

首先求出 $posl(i,j)$（原矩阵第 $j$ 列第几行元素是 $i$），$posh(i,j)$（原矩阵第 $i$ 列第几行元素是 $j$）。我们设三个函数：

- $\mathrm{Find}(x,y,t)$ 表示 $a(x,y)$ 在 $t$ 时刻是什么；
- $\mathrm{Findposh}(x,y,t)$ 表示 $a(x,?)$ 在 $t$ 时刻是 $y$；
- $\mathrm{Findposl}(x,y,t)$ 表示 $a(?,x)$ 在 $t$ 时刻是 $y$。

那么答案 $ans(i,j)=Find(i,j,m)$。

由于代码实在太容易理解了，这里直接给出如何求出这三个函数的代码：

```cpp
int Findposh(int x,int y,int t){//t时刻，a_{x,?}=y
	if(t==0)return posh[x][y];
	if(str[t]=='L')return f(Findposh(x,y,t-1)-1);
	if(str[t]=='R')return f(Findposh(x,y,t-1)+1);
	if(str[t]=='U')return Findposh(x%n+1,y,t-1);
	if(str[t]=='D')return Findposh((x-2+n)%n+1,y,t-1);
	if(str[t]=='I')return Find(x,y,t-1);
	if(str[t]=='C')return Findposh(y,x,t-1);
}
int Findposl(int x,int y,int t){//t时刻，a_{?,x}=y
	if(t==0)return posl[y][x];
	if(str[t]=='L')return Findposl(x%n+1,y,t-1);
	if(str[t]=='R')return Findposl((x-2+n)%n+1,y,t-1);
	if(str[t]=='U')return f(Findposl(x,y,t-1)-1);
	if(str[t]=='D')return f(Findposl(x,y,t-1)+1);
	if(str[t]=='I')return Findposl(y,x,t-1);
	if(str[t]=='C')return Find(y,x,t-1);
}
int Find(int x,int y,int t){//t时刻，a_{x,y}=?
	if(t==0)return a[x][y];
	if(str[t]=='L')return Find(x,y%n+1,t-1);
	if(str[t]=='R')return Find(x,(y-2+n)%n+1,t-1);
	if(str[t]=='U')return Find(x%n+1,y,t-1);
	if(str[t]=='D')return Find((x-2+n)%n+1,y,t-1);
	if(str[t]=='I')return Findposh(x,y,t-1);
	if(str[t]=='C')return Findposl(y,x,t-1); 
}
```

可是这样仍然是 $O(n^2m)$ 的……

考虑优化。你会发现，每次调用函数的形式与 $(x,y)$ 相对于原位置的相对位置与 $x,y$ 的具体值没有关系，只与操作序列有关。这意味着存在一个普适的函数，$f(x,y)=(arrayid,i,j,dx,dy,d,rev)$ 表示操作后 $a(x,y)$ 等于操作前 $a/posl/posh(i+dx,j+dy)+d$（若 $rev=1$ 则需要交换最后 $i+dx,j+dy$ 的值）。对于任意 $x,y$，$f$ 的表达式都是一样的——而 $f$ 只与操作序列有关，我们可以 $O(m)$ 求出 $f$。

代码非常好写，而且非常好懂，假如没看懂上面的直接看代码就懂了：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[1005][1005],n,m,t[1005],H,L,ans[1005][1005],posh[1005][1005],posl[1005][1005];
char str[100005];
struct Thing{
	int array_id,xdlt,ydlt,dlt,isrev;
};
Thing Findposh(int t);
Thing Findposl(int t);
Thing Find(int t);
int main(){
	int tc;
	cin>>tc;
	while(tc--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]),posh[i][a[i][j]]=j,posl[a[i][j]][j]=i;
		cin>>str+1;
		Thing t=Find(m);
	//	cout<<t.xdlt<<' '<<t.ydlt<<' '<<t.isrev<<' '<<(char)t.array_id<<' '<<t.dlt<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int ti=i,tj=j;
				//if(t.isrev)swap(ti,tj);
				int x=((t.xdlt+ti)%n+n)%n+n,y=((t.ydlt+tj)%n+n)%n+n;
				x=(x-1)%n+1,y=(y-1)%n+1;
				if(t.isrev)swap(x,y);
				int ans;
				if(t.array_id=='p')ans=a[x][y];
				if(t.array_id=='h')ans=posh[x][y];
				if(t.array_id=='l')ans=posl[x][y];
				ans=((ans+t.dlt)%n+n)%n+n;
				ans=(ans-1)%n+1;
				cout<<ans<<' ';
			}
			puts("");
		}
		puts("");
	}
}
Thing Findposh(int t){//t时刻，a_{x,?}=y
	Thing tmp;
	if(t==0)return {'h',0,0,0,0};
	if(str[t]=='L'){
		tmp=Findposh(t-1),tmp.dlt--;
		return tmp;
	}
	if(str[t]=='R'){
		tmp=Findposh(t-1),tmp.dlt++;
		return tmp;
	}
	if(str[t]=='U'){
		tmp=Findposh(t-1),tmp.xdlt++;
		return tmp;
	}
	if(str[t]=='D'){
		tmp=Findposh(t-1),tmp.xdlt--;
		return tmp;
	}
	if(str[t]=='I'){
		return Find(t-1);
	}
	if(str[t]=='C'){
		tmp=Findposh(t-1),swap(tmp.xdlt,tmp.ydlt),tmp.isrev^=1;
		return tmp;
	}
}
Thing Findposl(int t){//t时刻，a_{?,x}=y
	Thing tmp;
	if(t==0)return {'l',0,0,0,1};
	if(str[t]=='L'){
		tmp=Findposl(t-1),tmp.xdlt++;
		return tmp;
	}
	if(str[t]=='R'){
		tmp=Findposl(t-1),tmp.xdlt--;
		return tmp;
	}
	if(str[t]=='U'){
		tmp=Findposl(t-1),tmp.dlt--;
		return tmp;
	}
	if(str[t]=='D'){
		tmp=Findposl(t-1),tmp.dlt++;
		return tmp;
	}
	if(str[t]=='I'){
		tmp=Findposl(t-1),swap(tmp.xdlt,tmp.ydlt),tmp.isrev^=1;
		return tmp;
	}
	if(str[t]=='C'){
		tmp=Find(t-1),swap(tmp.xdlt,tmp.ydlt),tmp.isrev^=1;
		return tmp;
	}
}
Thing Find(int t){//t时刻，a_{x,y}=?
	Thing tmp;
	if(t==0)return {'p',0,0,0,0};
	if(str[t]=='L'){
		tmp=Find(t-1),tmp.ydlt++;
		return tmp;
	}
	if(str[t]=='R'){
		tmp=Find(t-1),tmp.ydlt--;
		return tmp;
	}
	if(str[t]=='U'){
		tmp=Find(t-1),tmp.xdlt++;
		return tmp;
	}
	if(str[t]=='D'){
		tmp=Find(t-1),tmp.xdlt--;
		return tmp;
	}
	if(str[t]=='I'){
		return Findposh(t-1);
	}
	if(str[t]=='C'){
		tmp=Findposl(t-1),swap(tmp.xdlt,tmp.ydlt),tmp.isrev^=1;
		return tmp;
	}
}
```

---

## 作者：qianyuzhe (赞：2)

## 题意简述

给定一个方阵，其每行每列都是 $1\sim n$ 的一个排列，共有 $m$ 次操作，每次操作将矩阵向某个方向循环移动一位或将矩阵的每行/列变为其逆排列，求 $m$ 次操作后的矩阵。

## 题目分析

循环移位显然是简单的，对于排列 $p(x)$ 的逆排列 $p^{-1}(x)$，有 $pp^{-1}(x)=p^{-1}p(x)=x$，即对原排列的 $i$ 与 $x_i$ 互换。

对于原矩阵的每个位置 $a_{i,j}$，考虑如下四元组 $(i,j,a_{i,j},1)^T$，对于 $6$ 种操作，其变化如下（暂时不考虑取模）：

1. `U`(循环上移)：$(i,j,a_{i,j},1)^T\leftarrow(i-1,j,a_{i,j},1)^T$
3. `D`(循环下移)：$(i,j,a_{i,j},1)^T\leftarrow(i+1,j,a_{i,j},1)^T$
4. `L`(循环左移)：$(i,j,a_{i,j},1)^T\leftarrow(i,j-1,a_{i,j},1)^T$
5. `R`(循环右移)：$(i,j,a_{i,j},1)^T\leftarrow(i,j+1,a_{i,j},1)^T$
6. `I`(各行求逆)：$(i,j,a_{i,j},1)^T\leftarrow(i,a_{i,j},j,1)^T$
7. `C`(各列求逆)：$(i,j,a_{i,j},1)^T\leftarrow(a_{i,j},j,i,1)^T$

把它写成矩阵乘法的形式：

1. `U`(循环上移)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}1&0&0&-1\\0&1&0&0\\0&0&1&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

3. `D`(循环下移)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}1&0&0&1\\0&1&0&0\\0&0&1&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

3. `L`(循环左移)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}1&0&0&0\\0&1&0&-1\\0&0&1&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

4. `R`(循环右移)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}1&0&0&0\\0&1&0&1\\0&0&1&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

5. `I`(各行求逆)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}1&0&0&0\\0&0&1&0\\0&1&0&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

6. `C`(各列求逆)：$\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}\leftarrow\begin{bmatrix}0&0&1&0\\0&1&0&0\\1&0&0&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}i\\j\\a_{i,j}\\1\end{bmatrix}$

将每一步的矩阵相乘，就将一系列变换转化为了一个变换 $P$，用原矩阵的每一位右乘 $P$ 即可。时间复杂度 $O(n^2+m)$，空间复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int t,n,m,i,j,k,o[1005][1005];
string s;
struct mat{
	int a[4][4];
	mat(){}
	mat(int a00,int a01,int a02,int a03,
		int a10,int a11,int a12,int a13,
		int a20,int a21,int a22,int a23,
		int a30,int a31,int a32,int a33){
		a[0][0]=a00;a[0][1]=a01;a[0][2]=a02;a[0][3]=a03;
		a[1][0]=a10;a[1][1]=a11;a[1][2]=a12;a[1][3]=a13;
		a[2][0]=a20;a[2][1]=a21;a[2][2]=a22;a[2][3]=a23;
		a[3][0]=a30;a[3][1]=a31;a[3][2]=a32;a[3][3]=a33;
	}
	mat operator*(mat t){
		int i,j,k;
		mat r;
		memset(r.a,0,sizeof(r));
		for(i=0;i<4;i++)
			for(k=0;k<4;k++)
				for(j=0;j<4;j++)
					r.a[i][j]=((r.a[i][j]+a[i][k]*t.a[k][j])%n+n)%n;//注意负数
		return r;
	}
}p,q[1005][1005];
int main(){
	cin.tie(0)->ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		p=mat(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);//初始化P为单位矩阵
		for(i=0;i<n;i++){//为了取模方便下标从0开始
			for(j=0;j<n;j++){
				cin>>k;
				q[i][j]=mat(i,0,0,0, j,0,0,0, k-1,0,0,0, 1,0,0,0);
			}
		}
		cin>>s;
		for(i=0;i<m;i++){//计算P
			if(s[i]=='U')p=mat(1,0,0,-1, 0,1,0,0, 0,0,1,0, 0,0,0,1)*p;
			if(s[i]=='D')p=mat(1,0,0,1, 0,1,0,0, 0,0,1,0, 0,0,0,1)*p;
			if(s[i]=='L')p=mat(1,0,0,0, 0,1,0,-1, 0,0,1,0, 0,0,0,1)*p;
			if(s[i]=='R')p=mat(1,0,0,0, 0,1,0,1, 0,0,1,0, 0,0,0,1)*p;
			if(s[i]=='I')p=mat(1,0,0,0, 0,0,1,0, 0,1,0,0, 0,0,0,1)*p;
			if(s[i]=='C')p=mat(0,0,1,0, 0,1,0,0, 1,0,0,0, 0,0,0,1)*p;
		}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				q[i][j]=p*q[i][j];//用原矩阵的每一位右乘P
				o[q[i][j].a[0][0]][q[i][j].a[1][0]]=q[i][j].a[2][0];//结果存进新矩阵
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)cout<<o[i][j]+1<<' ';
			cout<<'\n';
		}
	}
    return 0;
}
```

---

## 作者：RockyYue (赞：1)

#### 1458C

给定 $a_{1\dots n,1\dots n}$，每行和每列均为 $\{1\dots n\}$ 排列，$m$ 操作，每次为将整个矩阵上/下/左/右循环移动一个，或将每行/每列分别替换为其逆排列，排列 $p_{1\dots n}$ 的逆排列 $a$ 满足 $a_{p_i}=i$，求最终矩阵，要求 $O(n^2+m)$。

#### Sol

- 这种维护矩阵整体操作题目，且操作关于坐标和值的题，可以维护若干三元组 $(i,j,x)$，表示当前时刻下 $a_{i,j}=x$，这与直接维护矩阵的区别在于，你不需要以每个点坐标为操作索引，而是对整体维护这三个值中统一的变化。
- 记录 $f_{i,j,0/1/2}$ 表示初始位置为 $(i,j)$ 点对应的三元组，移动操作则记录 $add_{0/1/2}$ 表示每一维的增量（循环意义下），$add_2$ 后续再提。
- 逆排列操作，相当于对每个三元组交换 $(i,x)$ 或 $(j,x)$，于是维护 $match_{0/1/2}$，$match_k$ 表示当前时刻三元组中 $i/j/x$ 地位的数记录在 $f_{i,j,match_k}$ 上，相当于是 $f$ 第三维的交换标记（则初始 $match_i=i$）。
- 则对于逆排列操作，直接交换 $match$ 即可。对于移动操作，在 $add_{match_{0/1}}$ 上加减。
- 最终记录答案为矩阵 $b$，则对于 $b_{f_{i,j,match_0+add_{match_0}},f_{i,j,match_1+add_{match_1}}}=f_{i,j,match_2}$，这里加是循环意义下的。

---

## 作者：Piwry (赞：1)

## 解析

（下面为了方便默认矩阵下标从 $0$ 开始，并且矩阵元素的值都减 $1$（即限制在 $[0, n-1]$ 内））

考虑将矩阵的 $a[i][j]$ 视为一个三元组 $(i, j, a[i][j])$

前四种操作都比较简单。而后两种操作可以发现实质上就是交换三元组的 第 $2, 3$ 个元素（`I`）和 第 $1, 3$ 个元素（`C`）

接着不难想到将三元组视为一个向量，各种变换则视为矩阵（当然矩乘要在模 $n$ 的意义下进行），这样就做完了

（当然不想大常数矩阵搞也可以；就是讨论可能会有些麻烦）

具体实现可能需要一些 trick。首先将变换 `I` 和 `C` 做成一个三维矩阵很显然，但前面四个变换就没法表示成三维矩阵；这时可以考虑给三元组再加一维，且这维的值恒为 $1$，即 $(i, j, a[i][j], 1)$，这样再用四维矩阵就可以表示前四种变换了

（其实感觉这个 trick 还蛮常见的）

还有疑问可以参考代码，感觉应该不难看懂

## CODE

```cpp
#include <cstdio>
#include <cstring>

const int MAXN =1010, MAXM =1e5+20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

void read_string(char *s){
	char ch =getchar();
	while(ch < 'A' && ch > 'Z')
		ch =getchar();
	int tot =0;
	while(ch >= 'A' && ch <= 'Z')
		s[tot++] =ch, ch =getchar();
}

/*------------------------------Matrix------------------------------*/

namespace Matrix{
	const int MAXS =4;
	int M;
	
	struct Mx{
		int r, c;
		int matrix[MAXS][MAXS]/*row, column*/;
		
		Mx(){
			memset(matrix, 0, sizeof(matrix));
		}
		Mx(const int &n, const int &m):r(n), c(m){
			memset(matrix, 0, sizeof(matrix));
		}
		Mx(const int &n, const char *typ):r(n), c(n){
			memset(matrix, 0, sizeof(matrix));
			if(typ[0] == 'u')
				for(int i =0; i < n; ++i)
					matrix[i][i] =1;
		}
		Mx(const int &n, const int &m, const char *val_matrix):r(n), c(m){
			int cur =0;
			for(int i =0; i < n; ++i)
				for(int j =0; j < m; ++j){
					char ch =val_matrix[cur++];
					if(ch == '+' || ch == '1')
						matrix[i][j] =1;
					else if(ch == '-')
						matrix[i][j] =-1;
					else
						matrix[i][j] =0;
				}
		}
		
		Mx operator * (const Mx &B) const{
			Mx C(r, B.c);
			for(int i =0; i < r; ++i)
				for(int k =0; k < c; ++k) if(matrix[i][k])
					for(int j =0; j < B.c; ++j)
						C.matrix[i][j] =(C.matrix[i][j]+matrix[i][k]*B.matrix[k][j]+M)%M;
			return C;
		}
	};
}
using Matrix::Mx;

/*------------------------------Main------------------------------*/

const Mx U(4, 4, "100-010000100001"),
		 D(4, 4, "100+010000100001"),
		 L(4, 4, "1000010-00100001"),
		 R(4, 4, "1000010+00100001"),
		 I(4, 4, "1000001001000001"),
		 C(4, 4, "0010010010000001");

int main(){
	for(int t =0, T =read(); t < T; ++t){
		int n =read(), m =read();
		Matrix::M =n;
		int matrix[MAXN][MAXN];
		for(int i =0; i < n; ++i)
			for(int j =0; j < n; ++j)
				matrix[i][j] =read();
		char oper[MAXM];
		read_string(oper);
		
		Mx mov(4, "unit");
		for(int i =0; i < m; ++i){
			if(oper[i] == 'U')
				mov =U*mov;
			else if(oper[i] == 'D')
				mov =D*mov;
			else if(oper[i] == 'L')
				mov =L*mov;
			else if(oper[i] == 'R')
				mov =R*mov;
			else if(oper[i] == 'I')
				mov =I*mov;
			else
				mov =C*mov;
		}
		
		int ans[MAXN][MAXN] ={0};
		for(int i =0; i < n; ++i)
			for(int j =0; j < n; ++j){
				Mx cur(4, 1);
				cur.matrix[0][0] =i;
				cur.matrix[1][0] =j;
				cur.matrix[2][0] =matrix[i][j]-1;
				cur.matrix[3][0] =1;
				
				cur =mov*cur;
				ans[cur.matrix[0][0]][cur.matrix[1][0]] =cur.matrix[2][0];
			}
		for(int i =0; i < n; ++i){
			for(int j =0; j < n; ++j)
				write(ans[i][j]+1), putchar(' ');
			putchar('\n');
		}
		putchar('\n');
	}
}
```

---

