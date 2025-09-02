# Anti-Theft Road Planning

## 题目描述

This is an interactive problem.

A city has $ n^2 $ buildings divided into a grid of $ n $ rows and $ n $ columns. You need to build a road of some length $ D(A,B) $ of your choice between each pair of adjacent by side buildings $ A $ and $ B $ . Due to budget limitations and legal restrictions, the length of each road must be a positive integer and the total length of all roads should not exceed $ 48\,000 $ .

There is a thief in the city who will start from the topmost, leftmost building (in the first row and the first column) and roam around the city, occasionally stealing artifacts from some of the buildings. He can move from one building to another adjacent building by travelling through the road which connects them.

You are unable to track down what buildings he visits and what path he follows to reach them. But there is one tracking mechanism in the city. The tracker is capable of storing a single integer $ x $ which is initially $ 0 $ . Each time the thief travels from a building $ A $ to another adjacent building $ B $ through a road of length $ D(A,B) $ , the tracker changes $ x $ to $ x\oplus D(A,B) $ . Each time the thief steals from a building, the tracker reports the value $ x $ stored in it and resets it back to $ 0 $ .

It is known beforehand that the thief will steal in exactly $ k $ buildings but you will know the values returned by the tracker only after the thefts actually happen. Your task is to choose the lengths of roads in such a way that no matter what strategy or routes the thief follows, you will be able to exactly tell the location of all the buildings where the thefts occurred from the values returned by the tracker.

## 说明/提示

For the sample test, $ n=2 $ and $ k=4 $ .

You choose to build the roads of the following lengths:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1673F/dd6799b620199bc45a1a875eaf67515e296c4b3c.png)The thief follows the following strategy:

1. Start at $ B_{1,1} $ .
2. Move Right to $ B_{1,2} $ .
3. Move Down to $ B_{2,2} $ .
4. Move Left to $ B_{2,1} $ .
5. Move Up to $ B_{1,1} $ .
6. Move Right to $ B_{1,2} $ .
7. Steal from $ B_{1,2} $ .
8. Move Left to $ B_{1,1} $ .
9. Steal from $ B_{1,1} $ .
10. Move Down to $ B_{2,1} $ .
11. Move Right to $ B_{2,2} $ .
12. Move Up to $ B_{1,2} $ .
13. Steal from $ B_{1,2} $ .
14. Move Left to $ B_{1,1} $ .
15. Move Down to $ B_{2,1} $ .
16. Steal from $ B_{2,1} $ .

The tracker responds in the following way:

1. Initialize $ x=0 $ .
2. Change $ x $ to $ x\oplus 1=0\oplus1=1 $ .
3. Change $ x $ to $ x\oplus 4=1\oplus4=5 $ .
4. Change $ x $ to $ x\oplus 8=5\oplus8=13 $ .
5. Change $ x $ to $ x\oplus 2=13\oplus2=15 $ .
6. Change $ x $ to $ x\oplus 1=15\oplus1=14 $ .
7. Return $ x=14 $ and re-initialize $ x=0 $ .
8. Change $ x $ to $ x\oplus 1=0\oplus1=1 $ .
9. Return $ x=1 $ and re-initialize $ x=0 $ .
10. Change $ x $ to $ x\oplus 2=0\oplus2=2 $ .
11. Change $ x $ to $ x\oplus 8=2\oplus8=10 $ .
12. Change $ x $ to $ x\oplus 4=10\oplus4=14 $ .
13. Return $ x=14 $ and re-initialize $ x=0 $ .
14. Change $ x $ to $ x\oplus 1=0\oplus1=1 $ .
15. Change $ x $ to $ x\oplus 2=1\oplus2=3 $ .
16. Return $ x=3 $ and re-initialize $ x=0 $ .

## 样例 #1

### 输入

```
2 4



14

1

14

3```

### 输出

```
1
8
2 4

1 2

1 1

1 2

2 1```

# 题解

## 作者：RedLycoris (赞：4)

题目有一个很强的提示是“无论怎么走都要能判断出来”，这启示我们可能有很多道路的长度都是相同的。

然后，我们可以这么设计：

+ 当 $i$ 固定时，所有 $a_{i,j}$ 到 $a_{i+1,j}$ 的路的长度均相同。

+ 当 $j$ 固定时，所有 $a_{i,j}$ 到 $a_{i,j+1}$ 的路的长度均相同。


这样，就避免了在不同行中折返走（列同理）的情况。

长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9fr6cttz.png)

红色是折返走的地方，虽然在不同行但效果一样，如果我们把他们的路径长度赋为相同的权值就可以异或掉了。

通过这个折返走我们可以发现行/列是可以分开考虑的，再由异或想到我们可以用前 $5$ 个二进制位表示行，后 $5$ 个来表示列，所以我们就先对行单独进行分析。

问题就可以被简化成一个一维的图（ $1$ 列 $n$ 行），你需要对这些路赋值，需要能判断出走到哪儿了。

我们尝试对 $a_{i,1}$ 赋值为 $i$ （注意，是格子，不是路径长度！$a_{i,1}$ 是假设我们已经把它拍扁成一维了），再让 $a_{i,1}$ 到 $a_{i+1,1}$ 的路径的长度赋值为 $i \oplus (i-1)$ （ $\oplus$ 表示异或）。

假设我们当前在的格子的权值为 $t$，询问给你的路径异或值为 $x$，那么你最后到达的格子的权值就是 $t \oplus x$。由于所有格子的权值都唯一，你就可以做到唯一确定了。

到了这里，你得到了一个路径总长度约为 $1.3\times10^5$ 的做法。

优化一：

你看着这个 $i \oplus (i-1)$ 写成二进制后很不舒服，每条路径的长度都有很多个 $1$。然后你想精简它，虽然题目说了长度必须是正整数不能为 $0$，所以最好就让这个长度在二进制下只有一个 $1$。~~根据你在CSP2019的经验~~，你想到了格雷码这个东西，编码中相邻的两个数在二进制下恰好相差一位！

这边改改那边改改，你得到了一个总长度约为 $8\times10^4$ 的做法。~~很遗憾还是过不去~~

优化二：

再一次观察每条路径的长度。~~突然发现~~，路径长度出现的频率是不同的。比如，$2^0$ 出现的频率是最大的，$2^1$ 次之，到 $2^4$ 都是大幅减小，但到了 $2^5$ 又变得和 $2^0$ 一样多了。

探究出现的原因，发现是行&列位数分配不当的原因，原来的方案是对于所有的列的路径长度就要直接乘上 $2^5$。

但这个 $2^4$ 啊，长度很小，但频率却非常小，感觉上就没有被充分利用。

所以我们考虑用第 $0,2,4,6,8$ 位维护行，$1,3,5,7,9$ 位维护列，就可以做到约 $4.7\times 10^4$ 的总长度了。

Code:

```cpp
int gc[114514];
int rgc[114514];
inline int GET(int x){
	return gc[x];
}
inline void prep(){//计算格雷码
	gc[0]=0;
	for(int i=0;i<6;++i){
		int csz=1<<i;
		for(int j=0;j<csz;++j){
			gc[csz*2-j-1]=csz+gc[j];
		}
	}
	for(int i=0;i<=32;++i)rgc[gc[i]]=i;
}
inline int HANG(int x){//行列分离
	int rt=0;
	for(int i=0,j=0;i<5;j+=2,++i){
		if(x&(1<<i)){
			rt+=(1<<j);
		}
	}
	return rt;
}
inline int LIE(int x){
	int rt=0;
	for(int i=0,j=1;i<5;j+=2,++i){
		if(x&(1<<i)){
			rt+=(1<<j);
		}
	}
	return rt;
}
inline int RHANG(int x){
	int rt=0;
	for(int i=0,j=0;i<5;j+=2,++i){
		if(x&(1<<j)){
			rt+=(1<<i);
		}
	}
	return rt;
}
inline int RLIE(int x){
	int rt=0;
	for(int i=0,j=1;i<5;j+=2,++i){
		if(x&(1<<j)){
			rt+=(1<<i);
		}
	}
	return rt;
}
int k;
inline void solve(){
	int n;cin>>n>>k;
	fflush(stdin);
	for(int i=1;i<=n;++i){
		for(int j=1;j<n;++j){
			cout<<LIE(GET(j)^GET(j-1))<<' ';//0 2 4 6 8
			fflush(stdout);
		}
		cout<<endl;fflush(stdout);
	}
	for(int i=1;i<n;++i){
		for(int j=1;j<=n;++j){
			cout<<HANG(GET(i)^GET(i-1))<<' ';//1 3 5 7 9
			fflush(stdout);
		}
		cout<<endl;fflush(stdout);
	}
	fflush(stdin);
	int curh=0,curl=0;
	for(;k--;){
		int x;cin>>x;fflush(stdin);
		int l=RLIE(x),h=RHANG(x);
		curh^=h,curl^=l;
		cout<<rgc[curh]+1<<' '<<rgc[curl]+1<<endl;
		fflush(stdout);
	}
}
int main(){
	prep();
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return (0-0);
}
```

---

## 作者：AC_love (赞：3)

首先我们不妨在一维的一根线上思考这个问题。

我们发现：我们可以这样安排：

小偷初始位置在 $0$ 号点，追踪仪器初始化为 $0$。

走到 $1$ 号点时，追踪仪器的数字变成 $1$。

此时需要异或 $1$，因此 $0$ 号点到 $1$ 号点路径长度为 $1$。

走到 $2$ 号点时，追踪仪器的数字变成 $2$。

此时从 $(01)_2$ 变成 $(10)_2$ 需要异或 $(11)_2$ 也就是 $3$，因此 $1$ 号点到 $2$ 号点的路径长度为 $3$。

走到 $3$ 号点时，追踪仪器的数字变成 $3$。

此时从 $(10)_2$ 变成 $(11)_2$ 需要异或 $(01)_2$ 也就是 $1$，因此 $2$ 号点到 $3$ 号点的路径长度为 $1$。

走到 $4$ 号点时，追踪仪器的数字变成 $4$。

此时从 $(11)_2$ 变成 $(100)_2$ 需要异或 $(111)_2$ 也就是 $7$，因此 $3$ 号点到 $4$ 号点的路径长度为 $7$。

以此类推，走到 $31$ 号点时，追踪仪器的数字变成 $31$，也就是 $(11111)_2$。

由于走回头路时，两段相同的路径异或在一起会互相抵消，因此我们可以直接根据追踪仪器上的数字来确定此时小偷的位置。

同理我们可以把这个一维的东西上升到二维。

那么我们很容易想到，让前五位表示横着走的，后五位表示竖着走的。

举个例子，现在小偷的位置是 $(32, 32)$，也就是说小偷横着在 $31$ 号点（注意 $(1, 1)$ 是 $0$ 号点）竖着也在 $31$ 号点，那么我们希望追踪仪器上显示的就是 $(1111111111)_2$。

假如小偷的位置是 $(16, 16)$，那么追踪仪器上显示的就是 $(0111101111)_2$。

这样显然可以根据追踪仪器上的数来确定小偷的位置，但是也存在问题：这样的路径长是多少？

不难想到，我们这样设计路径长的时候，横着的每条路径的长度其实是 $i \oplus (i - 1)$，而竖着的路径长度为 $(i \oplus (i - 1)) \times 2^5$。

这么一合计，你发现你的路径总长度约为 $1.36 \times 10^5$，超出了题目限制。

我们考虑能不能精简路径长度呢？

我们发现 $i \oplus (i - 1)$ 这个长度很浪费，因为每个 $i \oplus (i - 1)$ 里都有好几个二进制位上有 $1$，而实际上我们不需要那么多 $1$。这时我们想起了[格雷码](https://www.luogu.com.cn/problem/P5657)，这个东西每次后一位只会和前一位最多有一位相差 $1$，是我们优化路径长度的不二之选。

然而就算加了格雷码之后，我们发现，所有路径的总长大约为 $8.4 \times 10^4$，仍然超出了题目限制。

那么应该怎么办呢？

我们想到，竖着的路径长度后面都需要乘一个 $2 ^ 5$，而横着的就不用，这就很不平衡，横着的往外延伸多远都很短，竖着的往外延伸一点就老长。

> 不患寡而患不均。
>
> —— 《论语 · 季氏》

显然，让横竖相差过大不是我们希望看到的，那么我们可以考虑把横竖交叉排列，让 $1, 3, 5, 7, 9$ 位表示横的，$2, 4, 6, 8, 10$ 位表示竖的。比如 $(2, 2)$ 就可以表示为 $(0000000011)_2$，这相比原来的 $(0000100001)_2$ 要节约了很多。

此时就算 $n$ 卡满，路径长的总和也只有 $4.7 \times 10^4$，刚好卡进了 $4.8 \times 10^4$ 的限制，不多不少刚刚好。

如何求格雷码呢？官方题解给了我们一个很好的启发：

> 如果我们已经有了 $k$ 位的格雷码，我们可以扩展到 $k + 1$ 位。方法是先把它复制一遍，在复制后的格雷码前面加个 $1$，在原来的格雷码前面加个 $0$。
>
> —— 译自官方题解

代码实现如下（部分参考官方题解）：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 32;
int memory[114514];

inline int read()
{
	long long xr = 0, F = 1;
	char cr;
	while(cr = getchar(), cr < '0' || cr > '9')
		if(cr == '-')
			F = -1;
	while(cr >= '0' && cr <= '9') xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

int maxpow2(int t)
// 找到 t 里有几个因数 2 
{
	int k = t;
	if(memory[t] != -1)
		return memory[t];
	int p = 1;
	while(!(t & 1))
	{
		p <<= 1;
		t >>= 1;
	}
	return memory[k] = p;
}

int n, k;
int h[N][N - 1];
// 横着的街道的长度 
int s[N - 1][N];
// 竖着的街道的长度 
int way[N][N];
// 根据位置推测长度 

struct pos
{
	int x;
	int y;
};
pos p[N * N];
// 根据长度推测位置 

int main()
{
	n = read(), k = read();
	memset(memory, -1, sizeof(memory));
	for(int i = 0; i < N; i = i + 1)
		for(int j = 0; j < N - 1; j = j + 1)
			h[i][j] = maxpow2(j + 1) * maxpow2(j + 1);
	for(int i = 0; i < N - 1; i = i + 1)
		for(int j = 0; j < N; j = j + 1)
			s[i][j] = 2 * maxpow2(i + 1) * maxpow2(i + 1);
	for(int i = 0; i < n; i = i + 1)
	{
		for(int j = 0; j < n - 1; j = j + 1)
			cout << h[i][j] << " ";
		cout << endl;
	}
	for(int i = 0; i < n - 1; i = i + 1)
	{
		for(int j = 0; j < n; j = j + 1)
			cout << s[i][j] << " ";
		cout << endl;
	}
	for(int i = 0; i < n; i = i + 1)
		for(int j = 0; j < n; j = j + 1)
		{
			if(!i && !j)
				continue;
			if(!i)
				way[i][j] = way[i][j - 1] ^ h[i][j - 1];
			else
				way[i][j] = way[i - 1][j] ^ s[i - 1][j];
			p[way[i][j]] = (pos){i, j};
		}
	int now = 0;
	while(k --)
		now ^= read(),
		cout << p[now].x + 1 << " " << p[now].y + 1 << endl;
	return 0;
}
```

---

## 作者：enucai (赞：2)

## Preface

这题代码实现很容易，但构造的优化过程甚为巧妙。

## Analysis

### Step1. 朴素方法

用一个 $10$ 位的**二进制数**表示一个位置。其中高 $5$ 位表示行，低 $5$ 位表示列。例如：$(3,2)$ 可表示为 $\mathtt{00010-00001}$。

则一条边的边权即为连接两个点的点权的**异或和**。

经过实测，当 $n=32$ 时，边权和为 $136224$，超出限制。

### Step2. 优化一 格雷码优化

考虑每条边相邻两个点的点权二进制不同的位数较多，**减少不同的位数数量**即可减小边权总和。

因此想到 [[CSP-S2019] 格雷码](https://www.luogu.com.cn/problem/P5657)。将二进制前五位与后五位，从按照二进制大小排序，改为**按格雷码排序**。

经过实测，当 $n=32$ 时，边权和为 $84480$，超出限制。

### Step3. 优化二 行列错位优化

行与列交错出现，可以**增加**相邻位置二进制数**相同位**的数量。因此用 $0,2,4,6,8$ 位表示**行**，用 $1,3,5,7,9$ 位表示**列**，即可减小总边权。

经过实测，当 $n=32$ 时，边权和为 $47616$，符合限制，可以通过本题。

## Code

[Codeforces Status](https://codeforces.com/contest/1673/submission/155846213)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
int id[400],a[35]={0,1,5,4,20,21,17,16,80,81,85,84,68,69,65,64,320,321,325,324,340,341,337,336,272,273,277,276,260,261,257,256};
int dX(int x) {int y=0; For(i,0,4) if(x&(1<<(i*2))) y|=(1<<(i*2)); return y;}
int dY(int x) {int y=0; For(i,0,4) if(x&(1<<(i*2+1))) y|=(1<<(i*2)); return y;}
int n,k;
signed main(){
	cin>>n>>k;
	For(i,0,31) id[a[i]]=i+1;
	For(i,1,n) For(j,1,n-1) printf("%lld%c",2*(a[j-1]^a[j]),j==n-1?'\n':' ');
	For(i,1,n-1) For(j,1,n) printf("%lld%c",a[i-1]^a[i],j==n?'\n':' ');
	fflush(stdout);
	int x=0,y=0;
	while(k--){
		int path; cin>>path;
		x^=dX(path),y^=dY(path);
		cout<<id[x]<<" "<<id[y]<<"\n";
		fflush(stdout);
	}
}
```

---

## 作者：huangrenheluogu (赞：0)

好玩构造题。

推荐序：说说我的思路，毕竟最后的代码都是一样的。翻题解的时候，发现“格雷码优化”，但是如果考试的时候不知道或者忘记了这种方法怎么办？我的思路可以默认直接使用这种优化方法。

开始，我思考的是一个很朴素的方法，边权为 $1,2,4,8\cdots,2^n$，这样可以知道走了多少条边。

可以发现显然不可行，一条边就可以超过题目中的限制。但是这种方法实在是太浪费了，这样，它的反馈结果是 $(0\cdots01)_2,(0\cdots011)_2,\cdots,(1\cdots1)_2$，显然不是我们想要的。

节省一点？比如 $1\rightarrow3$ 之后，可以先用较小的代价消掉后面的 $1$，比如异或上 $1$。

那么，可以有下面的边长。

```cpp
int c[35] = {0, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1, 16, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1};
```

为了把行和列分开来，就把列右移五位就好了。

试试看！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, las, num;
int c[35] = {0, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1, 16, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1};
int to[35], tot, x[35], y[35], lg[35], X, Y;
inline void calc(int num, int &x, int &y){
	x = num;
	y = num << 5;
	return ;
}
int main(){
    n = 32;
	for(int i = 2; i <= 16; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= 31; i++) calc(c[i], x[i], y[i]);
	for(int i = 1; i < n; i++) tot ^= c[i], to[tot] = i;
	tot = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < n; j++) tot += x[j];
	}
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= n; j++) tot += y[i];
	}
	printf("%d\n", tot);
	return 0;
}
```

输出发现 $tot=84480>4.8\times10^4$。

怎么办？

观察发现，$1$ 个数比较多，要不把 $y$ 的 $1$ 弄少一点？

可以写出第二版代码。

改一下 calc 函数就好了。

```cpp
inline void calc(int num, int &x, int &y){
	num = lg[num];
	x = 1 << num * 2;
	y = 1 << num * 2 + 1;
	return ;
}
```
感觉这个方法比较聪明，我也是从 Sol 里学过来的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, las, num;
int c[35] = {0, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1, 16, 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1};
int to[35], tot, x[35], y[35], lg[35], X, Y;
inline void calc(int num, int &x, int &y){
	num = lg[num];
	x = 1 << num * 2;
	y = 1 << num * 2 + 1;
	return ;
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 2; i <= 16; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= 31; i++) calc(c[i], x[i], y[i]);
	for(int i = 1; i < n; i++) tot ^= c[i], to[tot] = i;
	tot = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < n; j++) printf("%d ", x[j]), tot += x[j];
		puts("");
	}
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= n; j++) printf("%d ", y[i]), tot += y[i];
		puts("");
	}
//	printf("%d\n", tot);
	fflush(stdout);
	while(k--){
		scanf("%d", &num);
		num ^= las;
		las = num;
		X = Y = 0;
		for(int i = 0; i <= 9; i++){
			if(num >> i & 1){
				if(i & 1){
					Y |= 1 << i / 2;
				}
				else{
					X |= 1 << i / 2;
				}
			}
		}
		printf("%d %d\n", to[Y] + 1, to[X] + 1);
		fflush(stdout);
	}
	return 0;
}

```

---

