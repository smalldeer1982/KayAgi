# Matrix Cascade

## 题目描述

There is a matrix of size $ n \times n $ which consists of 0s and 1s. The rows are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ n $ from left to right. The cell at the intersection of the $ x $ -th row and the $ y $ -th column is denoted as $ (x, y) $ .

AquaMoon wants to turn all elements of the matrix to 0s. In one step she can perform the following operation:

- Select an arbitrary cell, let it be $ (i, j) $ , then invert the element in $ (i, j) $ and also invert all elements in cells $ (x, y) $ for $ x > i $ and $ x - i \ge \left|y - j\right| $ . To invert a value means to change it to the opposite: 0 changes to 1, 1 changes to 0.

Help AquaMoon determine the minimum number of steps she need to perform to turn all elements of the matrix to 0s. We can show that an answer always exists.

## 说明/提示

In the first test case, we can use the following scheme:

1. perform the operation on the cell $ (1, 3) $ .

Clearly, the elements of the initial matrix are not all 0, so at least one operation is required. Thus, $ 1 $ is the answer.

In the second test case, we use the following scheme:

1. perform the operation on the cell $ (3, 3) $ ;
2. perform the operation on the cell $ (1, 1) $ .

It can be shown that there is no way to convert all elements to 0s in $ 0 $ or $ 1 $ steps, so the answer is exactly $ 2 $ .

## 样例 #1

### 输入

```
3
5
00100
01110
11111
11111
11111
3
100
110
110
6
010101
111101
011110
000000
111010
001110```

### 输出

```
1
2
15```

# 题解

## 作者：芷陌陌吖 (赞：13)

[更好的阅读体验](https://www.cnblogs.com/zhimomoya-blog/articles/Solution-CF1864D.html)

> update（2023/09/18）题意 fixed，抱歉题目翻译出锅 qwq

### 题意

给定一个由 $0$ 和 $1$ 组成的大小为 $n\times n$ 的矩阵。

定义一次操作为：选择矩阵上第 $i$ 行第 $j$ 列一个位置 $(i,j)$，将其取反，并取反所有满足 $x>i,x-i\ge|y-j|$ 的位置 $(x,y)$。

其中，“取反”的意思为：把 $0$ 变为 $1$，$1$ 变为 $0$。

求要把给定矩阵全变为 $0$ 的最少操作次数。

有 $t$ 组测试数据。

数据范围：$1\le t\le 10^5,2\le n\le 3\times10^3$，保证所有测试数据中 $1\le \sum n^2\le 9\times10^6$。

### 题解

我们先形象化一下操作，实际上就是把这个点向下找一个类似三角形的区域取反。如下图，对 $(1,4)$ 操作，红色为要取反的点。

![image](https://cdn.luogu.com.cn/upload/image_hosting/a38ty1i7.png)

首先考虑如何操作才能变为全 $0$。因为我们一次操作影响的是这行之后的元素，且行内的操作不会相互影响，所以考虑按照行从 $1$ 到 $n$ 来修改。当发现当前元素为 $1$，我们就执行一次操作即可。显然对于第一行我们最少的操作就是把所有为 $1$ 的进行操作即可，既然第一行操作确定了，那么后面行的操作也可以确定，即这样操作下来一定满足操作数最少，且全为 $0$。

如果操作直接对下面的行进行暴力修改，则时间复杂度为 $O(n^4)$。考虑优化修改操作。

考虑把一个操作转化一下：

如下图，黄色代表对该点进行一次题面所述操作。

![image](https://cdn.luogu.com.cn/upload/image_hosting/8qchjrnj.png)

那么这次操作可以通过递归拆分为：（红色代表对单点进行取反）

![image](https://cdn.luogu.com.cn/upload/image_hosting/r75qdcbi.png)

对于递归的黄色操作，我们可以对每个元素记录一个操作次数，对这些地方的操作次数加上 $1$，这样就可以 $O(1)$ 完成修改。

但要特别注意边界情况。

当黄色操作在左右边界时，如下图：

![image](https://cdn.luogu.com.cn/upload/image_hosting/cdkziqky.png)

操作就应该转化为：

![image](https://cdn.luogu.com.cn/upload/image_hosting/gneb82mi.png)

在右边界同理。

这样的总时间复杂度为 $O(n^2)$。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int T,n,a[N][N],cnt[N][N];
const int SIZE=1<<23;
char buf[SIZE],*p1=buf,*p2=buf,pbuf[SIZE],*pp=pbuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
#define putchar(c) (pp-pbuf==SIZE?(fwrite(pbuf,1,SIZE,stdout),pp=pbuf,*pp++=c):*pp++=c)
inline int read()
{
	int x=0;
	char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
inline int readchar()
{
	char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	return (c^48);
}
inline void write(int x)
{
	int out[20],cnt=0;
	do
	{
		out[++cnt]=(int)(x%10);
		x/=10;
	}
	while (x);
	for (int i=cnt;i>=1;i--) putchar((char)(out[i]^48));
	return;
}
inline void rev(int x,int y)     //对单点取反
{
	if (a[x][y]==0) a[x][y]=1;
	else a[x][y]=0;
}
int main()
{
	T=read();
	while (T--)
	{
		n=read();
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++)
			a[i][j]=readchar(),cnt[i][j]=0;//a 记录当前元素为 0 或 1，cnt 记录需要取反的次数
		int ans=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				cnt[i][j]%=2;          //我们只需要关心取反次数的奇偶性
				if (cnt[i][j]==1) rev(i,j);
				if (a[i][j]==1) rev(i,j),ans++,cnt[i][j]++;
				cnt[i][j]%=2;
				if (cnt[i][j]==1)      //将修改下传
				{
					rev(i+1,j),cnt[i+1][j-1]++,cnt[i+1][j+1]++;
					if (j!=1&&j!=n) cnt[i+2][j]+=cnt[i][j];
				}
			}
		}
		write(ans),putchar('\n');
	}
	fwrite(pbuf,1,pp-pbuf,stdout);
	return 0;
}
```



---

## 作者：EuphoricStar (赞：7)

拆题中式子的绝对值，得：

- $x - y \ge i - j$
- $x + y \ge i + j$

也就是说我们操作 $(i, j)$ 会影响到满足上面条件的所有点 $(x, y)$。

考虑按 $i + j$ 从小到大操作，这样第二个条件就可以舍去。那我们只需要一个树状数组维护有多少个已操作的点满足第一个条件，就可以知道 $(x, y)$ 的状态，从而知道该点是否需要操作。

时间复杂度 $O(n^2 \log n)$。

[code](https://codeforces.com/contest/1864/submission/220546895)

---

## 作者：DerrickLo (赞：6)

我们注意到对如图倒三角形上的所有点操作都会影响到目标点。

![](https://cdn.luogu.com.cn/upload/image_hosting/6occo9e3.png)

那么我们可以维护两个前缀和，第一个前缀和表示如下的点是否操作

![](https://cdn.luogu.com.cn/upload/image_hosting/lon83wvr.png)

第二个前缀和表示这些点是否操作

![](https://cdn.luogu.com.cn/upload/image_hosting/ld1emb20.png)

这样我们求出了前缀和之后，将两个前缀和异或一下就知道该点是否要操作了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,b[2][3005],c[2][3005],ans;
char a[3005][3005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=1;i<=n;i++)cin>>(a[i]+1);
		for(int j=0;j<=n+1;j++)b[0][j]=b[1][j]=c[0][j]=c[1][j]=0;
		for(int i=1;i<=n;i++){
			int sum=0;
			for(int j=1;j<=n;j++){
				b[1][j]=b[0][j+1]^sum;
				c[1][j]=c[0][j-1]^sum;
				int nowans=b[1][j]^c[1][j-1];
				if(nowans^(a[i][j]-'0'))ans++,sum^=1,b[1][j]^=1,c[1][j]^=1;
			}
			b[1][n+1]=b[1][n];
			for(int j=1;j<=n+1;j++)b[0][j]=b[1][j],c[0][j]=c[1][j];
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：信息向阳花木 (赞：5)

不难看出每次取反是对以此点为顶点的三角形区域（类似）进行取反操作，因此我们只要维护 $(i,j)$ 所在正反对角线和所在列的取反情况就可以。具体地说，先处理这个点的取反情况，如果这个点是 $1$，那就再取反。取反时只要将取反标记下传给左对角线 $(i + 1, j - 1)$，列 $(i + 1, j)$，右对角线 $(i+1,j+1)$。

不画图了，这题比较水，应该能想象出来（（

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 3010;

int t, n, res;
int a[N][N], tt[N][N], tr[N][N], tl[N][N];
char s[N][N];

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		res = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++ ) cin >> (s[i] + 1);
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= n; j ++ )
			{
				a[i][j] = s[i][j] - '0';
				tt[i][j] = tl[i][j] = tr[i][j] = 0;
			}
				
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= n; j ++ )
			{
				if(tt[i][j])
				{
					a[i][j] ^= 1;
					tt[i + 1][j] ^= 1;
					tl[i + 1][j - 1] ^= 1;
					tr[i + 1][j + 1] ^= 1;
				}
				if(tl[i][j])
				{
					a[i][j] ^= 1;
					tl[i + 1][j - 1] ^= 1;
				}
				if(tr[i][j])
				{
					a[i][j] ^= 1;
					tr[i + 1][j + 1] ^= 1;
				}
				if(a[i][j])
				{
					res ++;
					a[i][j] ^= 1;
					tt[i + 1][j] ^= 1;
					tl[i + 1][j - 1] ^= 1;
					tr[i + 1][j + 1] ^= 1;
				}
			}
		printf("%d\n", res);
	}
	return 0;
}
```

---

## 作者：hanjinghao (赞：4)

# 思路

从上往下、从左往右扫过去，如果发现当前格子是 $ 1 $，就以它为顶点覆盖一个三角形。

考虑优化这个过程：把一个三角形分成三部分：左边界、有边界、以顶点下方那个格子为顶点的三角形。对于每个格子，维护三个标记（左斜线、右斜线、下方的三角形），把左斜线的标记传给左下方的格子，右斜线的标记传给右下方的格子，三角形的标记传给下方的格子。

时间复杂度 $ O(n ^ 2) $。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 3005;
char s[N][N];
int tag[N][N], tl[N][N], tr[N][N];

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n, ans = 0;
		read(n);
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (s[i][j] != '0') goto Fail;
		puts("0");
		continue;
		Fail:;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				tag[i][j] = tl[i][j] = tr[i][j] = 0;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (tag[i][j])
				{
					if (s[i][j] == '0') s[i][j] = '1';
					else s[i][j] = '0';
					if (i != n)
					{
						if (j != 1) tl[i + 1][j - 1] ^= 1;
						tag[i + 1][j] ^= 1;
						if (j != n) tr[i + 1][j + 1] ^= 1;
					}
				}
				if (tl[i][j])
				{
					if (s[i][j] == '0') s[i][j] = '1';
					else s[i][j] = '0';
					if (i != n)
					{
						if (j != 1) tl[i + 1][j - 1] ^= 1;
					}
				}
				if (tr[i][j])
				{
					if (s[i][j] == '0') s[i][j] = '1';
					else s[i][j] = '0';
					if (i != n)
					{
						if (j != n) tr[i + 1][j + 1] ^= 1;
					}
				}
				if (s[i][j] == '1')
				{
					++ans;
					if (i != n)
					{
						if (j != 1) tl[i + 1][j - 1] ^= 1;
						tag[i + 1][j] ^= 1;
						if (j != n) tr[i + 1][j + 1] ^= 1;
					}
				}
			}
		}
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：Drind (赞：3)

### 题目解析
这题是异或操作，我们可以当成计算每个点被覆盖多少次再模上 $2$。我们考虑每层每层处理。因为选择一个点之后将会覆盖一个锥形范围，所以在上一层被覆盖的地方这一层一定被覆盖，同时，新覆盖的地方就是这个选定的点所在两条斜线和这一行的交点。
![](https://cdn.luogu.com.cn/upload/image_hosting/a6ahx4m1.png)

如图，紫色代表开始选中的点，蓝色代表每行从上一行继承来的点，红色代表每行新增的点，不难发现红色点都在紫色点所在的两个斜线上。

对于每个点，我们计算一下他所在的两个斜线上有多少被选中过的点，再加上上一行递推来的，模 $2$，就是它是否被覆盖，若跟目标状态不一样，就选中这个点。用斜线前缀和维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3000+10;

int a[N][N];
int sum1[3*N],sum2[3*N],t[N];

inline void fake_main(){
	int n,ans=0; cin>>n;
	for(int i=1;i<=n;i++) t[i]=0;
	memset(sum1,0,sizeof(sum1));
	memset(sum2,0,sizeof(sum2));//两条斜线的前缀和数组
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char ch; cin>>ch;
			a[i][j]=ch-'0';
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			t[j]+=sum1[i-j+n];
			t[j]+=sum2[i+j];
			t[j]%=2;//每个点处理是否被覆盖
		}
		for(int j=1;j<=n;j++){
			if(t[j]!=a[i][j]){//判断是不是需要选中这个点
				t[j]++; t[j]%=2;
				sum1[i-j+n]++; sum1[i-j+n]%=2;
				sum2[i+j]++; sum2[i+j]%=2;
				ans++;
			}
		}//注意t数组没有被清空，下一行继续使用
		
	}
	cout<<ans<<endl;
}

signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：One_JuRuo (赞：1)

## 思路

第一时间想到的是暴力，因为同一行的互不影响，所以第一行的 $1$ 一定都需要操作，然后把后续的状态更新，再操作第二行的所有的 $1$，但是很可惜是 $O(n^4)$ 的复杂度，必然会 TLE。

所以思考其他的办法，考虑到可以统计有多少操作更改了这个位置的状态，所以可以使用一个类似前缀和的方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/h09d2wzv.png)

如上图，可以发现黑色方框的状态会被红色方框的操作影响。

所以想办法统计红色方框进行的操作总数。

令 $b_{i,j}$ 表示格子 $(i,j)$ 是否做过操作， $c_{i,j}$ 表示所有会影响格子 $(i,j)$ 的状态的操作总数，包括本格子的操作。

再简单画一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8vcg30y8.png)

绿色为 $c_{i-1,j-1}$ 单独涉及的区域，黄色为 $c_{i-1,j+1}$ 单独涉及的区域，蓝色为 $c_{i-1,j-1}$ 和 $c_{i-1,j+1}$ 共同涉及的区域。

所以可以推断出公式为 $c_{i,j}=c_{i-1,j-1}+c_{i-1,j+1}-c_{i-2,j}+b_{i-1,j}$。

然后再判断经过这么多次操作后，这个格子的状态，再判断是否需要操作，再更改 $c_{i,j}$ 和 $b_{i,j}$。

然后发现样例都不对，在调试后发现，是当 $j=1$ 或者 $j=m$ 时发生了错误，所以只需要特判，这种情况更加简单公式为 $c_{i,j}=c_{i-1,j+1}+b_{i-1,j}$ 或者 $c_{i,j}=c_{i-1,j-1}+b_{i-1,j}$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[3005][3005],b[3005][3005],c[3005][3005],ans;
char ch[3005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),ans=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%s",ch+1);
			for(int j=1;j<=n;++j)
			{
				b[i][j]=0,a[i][j]=ch[j]-'0';
			}
		}
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=n;++j)
			{
				if(j==1) c[i][j]=c[i-1][j+1]+b[i-1][j];
				else if(j==n) c[i][j]=c[i-1][j-1]+b[i-1][j];
				else c[i][j]=c[i-1][j-1]+c[i-1][j+1]-((i>=2)?c[i-2][j]:0)+b[i-1][j];
				if((c[i][j]%2)^a[i][j]) ++c[i][j],++ans,b[i][j]=1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：M1rac0 (赞：0)

容易发现，对 $(x,y)$ 进行操作，被影响的单元格组成的集合为 $S(x,y) = \{ (i,j) \mid (i+j \geq x+y) \wedge (i-j \geq x-y) \}$。

有一个显然的最优策略：按照行号从小到大遍历，对当前行所有为 $1$ 的单元格进行操作。

证明也很简单，考虑归纳。定义 $f(x,y)$ 为将 $(x,y)$ 变为 $0$ 的操作函数。若前 $i$ 行的全部单元格都为 $0$，对于所有为 $1$ 的单元格 $(i+1,j)$，$f(i+1,j)$ 有两种情况：

1. 对该格进行操作，然后终止问题。注意此情况不会影响行号 $\leq i$ 的单元格和第 $i+1$ 行的其他格。
1. 若 $i>0$，对一个行号比它小且能影响到它的单元格 $(i',j')$ 进行操作，然后递归求解 $f(i',j')$。

若进入情况 2，最终一定有单元格被点击至少两次。两次操作可以抵消，因此一定不优。$\square$

接下来考虑如何维护操作。构造映射 $g:(x,y) \rightarrow (x+y-1, x-y+n)$，则对所有 $(x,y)$，$g(S(x,y))$ 组成一个矩形，差分后二维树状数组维护即可。由于值域为 $\{ 0,1 \}$，可以用 bitset 优化空间。空间复杂度为 $O(\frac{n^2 \log^2 n}{w})$；时间复杂度 $O(n^2 \log^2 n)$，但是常数极小，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int n, lim, ans;
bitset<N> a[N];
struct fenwick {
  bitset<N * 2> c[N * 2];
  inline void clear() {
    for (int i = 1; i <= lim; i++)
      for (int j = 1; j <= lim; j++)
        c[i][j] = 0;
  }
  inline void modify(int x, int y) {
    for (int i = x; i <= lim; i += i & -i)
      for (int j = y; j <= lim; j += j & -j)
        c[i][j] = c[i][j] ^ 1;
  }
  inline int query(int x, int y) {
    int res = 0;
    for (int i = x; i; i -= i & -i)
      for (int j = y; j; j -= j & -j)
        res ^= c[i][j]; 
    return res;
  }
} t;
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n; lim = n * 2 - 1;
    for (int i = 1; i <= n; i++) {
      string s; cin >> s;
      for (int j = 1; j <= n; j++) a[i][j] = s[j - 1] - '0';
    }
    ans = 0, t.clear();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (a[i][j] ^ t.query(i + j - 1, i - j + n))
          ans++, t.modify(i + j - 1, i - j + n);
    cout << ans << '\n';
  }
  return 0;
} 
```

---

## 作者：Scorilon (赞：0)

首先把式子拆一下，可以知道 $x-i \ge |y-j|$ 等价于 $x-y \ge i-j$ 和 $x+y \ge i+j$，注意到每次操作 $(i,j)$，影响到的点 $(x,y)$ 均要满足 $x>i$，那么我们每次就必须要按照从上往下的顺序进行，否则上面的点无法影响到，即从第一行开始操作。

又注意到对于 $(i,j)$ 如果执行了两次操作相当于没有执行操作，因此对于 $(i,j)$ 我们最多执行一次操作。

所以得出了一种贪心求法：从第一行往下，每次碰到不是 $0$ 的就修改，可以证明一定步数最小。时间复杂度 $O(n^4)$ 无法承受。

我们考虑优化修改的过程，注意到我们修改的时候区域是连续的，类似一个三角形的形状，所以我们可以类比二维前缀和与二维差分，维护两条直线来进行优化，分别是斜率为 $1$ 和斜率为 $-1$ 的两条直线。

我们用 $b$ 数组维护斜率为 $-1$ 的直线，用 $c$ 数组维护斜率为 $1$ 的直线，注意到状态只有 $\{1,0\}$，因此我们可以用异或来简便操作。

时间复杂度 $O(n^2)$。

```cpp
#include <cstdio>

int t;
int n;
int a[3005][3005];
int b[3005][3005],c[3005][3005];

void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) scanf("%1d",&a[i][j]);
	}
	int sum=0,tot=0;//sum表示修改次数，tot辅助于修改 
	for(int i=1;i<=n;i++) {//从第一行开始，自上而下 
		for(int j=1;j<=n;j++) {//求出每个格子的状态，要注意边界 
			a[i][j]^=(sum&1);//前面行的操作对当前行的影响，如果有影响到当前可以改变，如果没有影响到在后面与b，c异或时可以抵消 
			if(j-2>=1) a[i][j]^=b[i-1][j-2];
			if(j+2<=n) a[i][j]^=c[i-1][j+2];
		}
		for(int j=1;j<=n;j++) {//统计有多少个格子在第i行被执行操作 
			if(a[i][j]) ++sum;
		}
		tot=0;
		for(int j=1;j<=n;j++) {//下传 
			tot^=a[i][j];
			b[i][j]=b[i-1][j-1]^tot;
		}
		tot=0;
		for(int j=n;j>=1;j--) {//下传，注意边界 
			tot^=a[i][j];
			if(j!=n) c[i][j]=c[i-1][j+1]^tot;
			else c[i][j]=tot;
		}
	}
	printf("%d\n",sum);
}

int main() {
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：ollo (赞：0)

提供一个不要拆贡献的做法。

首先对于每一行都只有上面的行会对它产生影响，又因此有操作顺序一定是从上往下操作，所以我们可以对每一行分开考虑。

观察题目所给的式子 $x - i \ge \left|y - j\right|$ 并结合样例，不难发现每个染色点每往下一行影响区间都会往左右扩展一格。显然每个点的影响区间都是单调不减的。

考虑统计每个点所拥有的区间左端点和区间右端点，每往下一层就分别往左右传一位，那么我们可以轻松的判断一个点是否需要染色，直接记即可。时间复杂度 $O(n^2)$。

[code](https://codeforces.com/contest/1864/submission/220586420)

---

## 作者：Imken (赞：0)

题意：有一个 $n \times n$ 的 01 矩阵。每次操作可选择一个元素 $(i, j)$，将自己及满足条件的元素反转，即反转 $(x, y)$ 满足 $x > i$ 且 $x - i \ge \left|y - j\right|$。求使整个矩阵变为全 $0$ 所需的最少操作次数。

这个题目条件不是很直观，画一下会明显一些。如对点 $(1, 2)$ 进行操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/fdv94528.png)

（红线上及以下的点会被翻转）

考虑一个非常暴力的做法，即从上往下从左往右遍历，找到 $1$ 就对这个点进行操作，这样的操作次数一定是最小的。

然后考虑对暴力进行优化。可以想到使用懒标记优化每次操作。打三个懒标记，意义分别为翻转左下方、翻转正下方、翻转右下方。

剩下的看代码，我说的没代码清楚。

```cpp
inline void pushdown(int x, int y)
{
	if (mp[x][y].ltag) {
		mp[x + 1][y - 1].ltag ^= 1;
		mp[x + 1][y - 1].dtag ^= 1;
		mp[x + 1][y - 1].val ^= 1;
		mp[x][y].ltag = 0;
	}
	if (mp[x][y].rtag) {
		mp[x + 1][y + 1].rtag ^= 1;
		mp[x + 1][y + 1].dtag ^= 1;
		mp[x + 1][y + 1].val ^= 1;
		mp[x][y].rtag = 0;
	}
	if (mp[x][y].dtag) {
		mp[x + 1][y].dtag ^= 1;
		mp[x + 1][y].val ^= 1;
		mp[x][y].dtag = 0;
	}
}

inline void solve()
{
	// ...
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (mp[i][j].val == 1) {
				ans++;
				// 关于这个地方正确性的说明：pushdown 时，dtag 会被更新三次，等价于更新一次
				mp[i][j].ltag ^= 1;
				mp[i][j].rtag ^= 1;
				mp[i][j].dtag ^= 1;
			}
			pushdown(i, j);
		}
	}
	// ...
}
```


---

