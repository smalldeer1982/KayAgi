# [AGC002E] Candy Piles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc002/tasks/agc002_e



## 样例 #1

### 输入

```
2
1 3
```

### 输出

```
First```

## 样例 #2

### 输入

```
3
1 2 1
```

### 输出

```
First```

## 样例 #3

### 输入

```
3
1 2 3
```

### 输出

```
Second```

# 题解

## 作者：Heartlessly (赞：95)

## Description

有 $n$ 堆石子，每堆石子有 $a_i$ 个，两人轮流操作。要么取走石子最多的一堆，要么将每堆石子取走 $1$ 个。谁取走最后 $1$ 个石子，谁就输了。假设两人都足够聪明，求先手必胜还是后手必胜。

$(1 \leq n \leq 10^5,1 \leq a_i \leq 10^9)$

## Solution

不妨先按 $a_i$ 从大到小排序。对于石子最多的一堆，只要不直接取完，那么这堆石子仍然是最多的。

举个例子，对于 $\{a\} = \{7,7,7,6,4,4,4,2,2\}$，排完序后能够得到下图。

![uxC5ND.png](https://s2.ax1x.com/2019/10/13/uxC5ND.png)

对于取走石子最多的一堆，实际就是消去最左边一行；对于取走每堆石子取走 $1$ 个，实际就是消去最下面一行。

![uxCT9H.png](https://s2.ax1x.com/2019/10/13/uxCT9H.png)

我们不妨再把点阵转化为一个网格图。

从原点开始，每人每次可以选择向右或向上移动一格，向右代表消去最左边一行，向上代表消去最下面一行。很容易发现，当走到网格图的边界（下图中的实线部分）时，所有石子刚好被取完。

![uxiGyn.png](https://s2.ax1x.com/2019/10/13/uxiGyn.png)

显然边界上的点都是必败点，因为谁走到边界谁就输了。

对于任意一个不在边界上的点，如果它的上面和右面都是必败点，那么这个点一定是必胜点。如果它的上面和右面有一个是必胜点，那它就是必败点。（下图用 ○ / × 分别表示必败点和必胜点）

![uxite0.png](https://s2.ax1x.com/2019/10/13/uxite0.png)

因为从原点 $(0,0)$ 出发，所以当原点是必胜点时，后手必胜；原点是必败点时，先手必胜。

将整个网格图构造出来复杂度太大，所以考虑找规律：

除了边界外，同一对角线上的点全部是相同类型的点。

我们可以通过算出原点最右上方且不在边界上的点的类型，来知道原点是必胜点还是必败点。

找到以原点为左下角的最大正方形，设其右上方顶点为 $(i,i)$ 。当它到最上面且不在边界上的点的距离和最右面且不在边界上的点的距离其中一个为奇数时，这个点为必败点，反之这个点为必胜点。

![uxiNwV.png](https://s2.ax1x.com/2019/10/13/uxiNwV.png)

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 1e5;
int n, a[MAXN + 5];

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = 1; i <= n; ++i)
        if (i + 1 > a[i + 1]) {//找到以原点为左下角的最大正方形，其右上方顶点为 (i, i) 
            int j = 0;
            for (; a[j + i + 1] == i; ++j);
            if (((a[i] - i) & 1) || (j & 1)) puts("First");
            else puts("Second");
            break;
        }
    return 0;
}
```



---

## 作者：PragmaGCC (赞：12)

因为我们要选择的是最大的那一堆，所以先将整个序列从大到小排序。

举个例子：

```
1 1 4 5 1 4 1 9 1 9
```

排序后变成了这样

```
9 9 5 4 4 1 1 1 1 1
```

变成图：

```
0 0
0 0
0 0
0 0
0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

拿走最大的一堆就是拿走最左端的一列，每堆拿走一个就相当于抽走最底下一行。

然后我们发现这是一个**两人在方格上走棋，只能往上或往右，谁先到边界谁输，请问谁必胜**的问题。

如果一个点的右方和上方都是必胜点，则这个点为必败点。如果有一个是必败点，那么这个点是必胜点。

在这里边界必败。

将所有点的状态都标出来，定义一个点的状态为 $f(x,y)=0/1$。

我们发现 $f(x,y)=f(x+1,y+1)$。

证明：

- 若 $f(x,y)=0$，则 $f(x+1,y)=1,f(x,y+1)=1$。所以 $f(x+2,y),f(x+1,y+1)$ 中必有一个是必败态。此时只能为 $f(x+2,y)$。因此，$f(x+2,y+1)=1$。同理可推出 $f(x+1,y+2)=1$。由 $f(x+1,y+2)=1,f(x+2,y+1)=1$ 得到 $f(x+1,y+1)=0$。
- 若 $f(x,y)=1$，则 $f(x+1,y),f(x,y+1)$ 中至少有一个为 $0$，不妨设为 $(x,y+1)$ 。则 $f(x+1,y+1)=0$。

所以，我们只需要考虑极端（即只能向右/向上）的情况，对比两个方向上到边界的距离即可。

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
bool cmp(int a, int b) { return a > b; }
int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        if (a[i + 1] < i + 1) {
            int cnt = 0;
            while(a[i+cnt+1] == i) cnt++;
            const bool f = ((a[i] - i) & 1) || (cnt & 1);
            puts(f ? "First" : "Second");
            break;
        }
    }
    return 0;
}
```



---

## 作者：zhenglier (赞：12)

首先先%一下楼上的大佬。不过小蒟蒻看不懂大佬的代码，就只能自己写了。

这题是一个博弈论~~废话~~。

我们弄些数据可以先打一个表（此打表非彼打表）找下规律。比如数据
```
5
12 9 4 3 12
```
我们应该先对这一堆糖排个序，就变成了
```
12 12 9 4 3
```
我们让数据再可视化一点，就变成了（其中每一行中0的个数表示这一堆糖里糖的个数）
```
000 
0000 
000000000 
000000000000 
000000000000
```
我们可以发现对于任意一种选法（去掉一堆或每一个去掉一个）相当于把原点（最早在左下角）向右或向上移动一个点。所以对于每一种最终状态，比如
```
000 
0001 
001100000 
111000000000 
100000000000
```
原点经过的路径为一条折线。

易知，该图中边缘一圈都是必输态，而且一个点如果上方和右边都是必输态，则当前点为必胜态，其余都为必输态，则该图可转换为（我们把必输态的点变为？，必胜态的点变为！)。
```
???
!?!?
?!?!?????
!?!?!?!?!???
?!?!?!?!??!?
```
对于小部分的数据，我们可以模拟建图，但是事实上这是不可能的。所以我们要想办法再找一下规律。

我们可以找到一些点，他的横坐标等于纵坐标且这个点不在边界时，这些点的状态与原点相同。其中横坐标最大的点的状态肯定也和原点相同。（有点绕，自己慢慢理解吧）

所以我们可以枚举横坐标就行了。

再看不懂就看代码吧。
```cpp
//注意别复制代码，最好自己打一份。
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)scanf("%d",a+i);
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;++i){
        if(i+1>a[i+1]){
        	int ans=0;
            for(int j=i+1;a[j]=i;++j)ans^=1;
            ans|=(a[i]-i)&1;
            if(ans)puts("First");
            else puts("Second");
            return 0;
		}
	}
}
```

---

## 作者：xh39 (赞：10)

## 暴力

将a从大到小排序。

发现操作的顺序并不影响操作的结果。所以设 $f[i][j]$ 为用了 $i$ 次操作1,$j$ 次操作2。此时的状态先手的胜(值为 $1$)负(值为 $0$)情况。

一次操作相当于取一些糖果,然后将对方变成先手。所以只要能转移的状态有一个为先手负,则该点为先手胜。

列出状态转移方程:```f[i][j]=f[i+1][j]||!f[i][j+1]```。

边界情况:$f[i][a[i]]=1$。

暴力代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
bool f[10005][10005];
#define A b<=10000&&c<=10000
int n,a[1000005];
bool fyr(int b,int c){
	if(b>=a[c]){
		return 1;
	}
	if(A&&f[b][c]){
		return f[b][c];
	}
	bool ykb=!(fyr(b+1,c)&&fyr(b,c+1));
	if(A){
		f[b][c]=ykb;
	}
	return ykb;
}
int main(){
	int i;
	cin>>n;
	for(i=0;i<n;i++){
		scanf("%d",a+i);
	}
	sort(a,a+n,greater<int>());
	cout<<(fyr(0,0)?"First":"Second");
	return 0;
}
```
## 正解
请先看暴力再继续。

```f[i][j]=!f[i+1][j]||![i][j+1]```①

```f[i][j]=!(f[i+1][j]&&f[i][j+1])``` ②

将②代入①得```f[i][j]=(f[i+2][j]&&f[i+1][j+1])||(f[i+1][j+1]&&f[i][j+2])```。

可以看出,$f[i+1][j+1]$ 是必要条件,而 $f[i+2][j]$ 与 $f[i][j+2]$ 至少得满足其中一个。

所以```f[i][j]=f[i+1][j+1]&&(f[i+2][j]||f[i][j+2])```。

再次代入递推得 ```f[i][j]=f[i+2][j+2]&&(f[i+1][j+3]||f[i+3][j+1])```。

所以得出一个结论:```f[i][j]=f[i+a][j+a]&&(f[i+a-1][j+a+1]||f[i+a+1][i+a-1])```

①左右都碰到了边界。

|x|x|x|
|-:|-:|-:|
|1|0|x|
|[0]()|1|x|

必要点为0,说明负。

②左碰到边界,右未碰到。

|x|x|x|x|x|||||
|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|1|0|1|0|1|x|x|x|x|
|[0]()|[1]()|[0]()|[1]()|1|0|1|0|x|
|0|1|0|1|0|[1]()|0|1|x|

可能查询的值已用浅蓝色标出,发现0和1交替出现,即 $f[i][i]=f[i-1][i+1]$,所以 $f[0][0]=f[i-1][i+1]$。

$f[b][a[b]]=1$,所以就直接暴力往右扫,看什么时候碰到边界就可以了。

③左未碰到边界,右碰到了。

与②类似,自己手推。也可以参考代码。

④左右都未碰到。
|||x|||
| -----------: | -----------: | -----------: | -----------: | -----------: |
|  |?|x|||
|B|?|x|x|x|
|  |[A]()|?|?||
|  |  |B|  ||

同样是判断奇偶性,但要上面的和右边的都要判断。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1000005];
string s[5]={"Second","First"};
int main(){
	int n,i,j;
	cin>>n;
	for(i=0;i<n;i++){
		scanf("%d",a+i);
	}
	sort(a,a+n,greater<int>());
	for(i=0;a[i]>i;i++){
	}
	i--;
	if(a[i+1]<=i-1){ //右无。 
		if(i&&a[i-1]<=i+1){ //左无。//① 
			cout<<s[0];
		}else{ //③
			cout<<s[(a[i]-1-i)&1]; 
		}
	}else{
		if(i&&a[i-1]<=i+1){ //②
			for(j=i;a[j]>i;j++){ //一直往前扫到碰到边界。
			}
			cout<<s[(j-1-i)&1];
		}else{ //④
			for(j=i;a[j]>i;j++){
			}
			cout<<s[((a[i]-1-i)&1)||((j-1-i)&1)]; //上右只有有一个为1即可输出First。
		}
	}
	return 0;
}
```


---

## 作者：crashed (赞：10)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/AT1999)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;原题似乎不太好做，我们考虑换一个模型。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;先将糖果按照数量降序排序。我们在平面直角坐标系上面用矩形来表示这些糖果堆。每个矩形宽度为$1$，长度为糖果的数量。图形内部的左下角方格为$(1,1)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;现在，矩形内部的每一个位置，就有了实际的含义：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$(x,y)$表示进行了$x-1$次吃最大堆的操作和$y-1$次每堆吃一个的操作。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;每个位置可以向左走或者向上走，表示吃一整堆或者每堆吃一个。也就是$(x,y)$可以到达$(x+1,y)$或者$(x,y+1)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑用一个布尔函数$f(x,y)$表示$(x,y)$时先手的胜负状态。$f(x,y)=T$表示必胜，反之，表示必败。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是存在如下的性质：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果$f(x,y)=F$，那么$f(x+1,y)$和$f(x,y+1)$均为$T$；如果$f(x,y)=T$，那么$f(x+1,y)$和$f(x,y+1)$中至少有一个为$F$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很好理解。并且我们还可以得出：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;定理：$f(x,y)=f(x+1,y+1)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;证明：分情况讨论，如果$f(x,y)=T$，那么先手一定会将局面转移到$F$态，而后手只能将$F$态转移到$T$态，所以$f(x+1,y+1)=T$；如果$f(x,y)=F$，运用反证法：  
```
0 ?
1 1 ?
0 1 0
```  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果$f(x,y)=F$，$f(x+1,y+1)=T$，我们就可以确定$f(x+2,y)$和$f(x,y+2)$。对于$(x+1,y+2)$和$(x+2,y+1)$，它们不可能是$F$，只可能是$T$，而这样一来又不满足$f(x+1,y+1)=T$，因此这种情况不存在，$f(x+1,y+1)=F$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是，我们证明了对角线上的$f$都是相等的。我们只需要找到$(1,1)$的对角线上最后一个点就可以了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难发现，这样一个点满足如果向上走就再也不能向右走；向右走再也不能向上走的条件。转化成易于判断的条件就是，寻找一个最大的$i$，使得$i+1>a_{i+1}$。我们只需要判断$f(i,i)$即可。$f(i,i)$可以由$f(i+1,i)$和$f(i,i+1)$转移，这两个又很好计算（跟奇偶有关），于是我们就可以算出$f(i,i)$，进而得到$f(1,1)$。  
# 代码
```cpp
#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 1 ) + ( x << 3 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

int a[MAXN];
int N;

bool cmp( const int &a, const int &b ) { return a > b; }

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] );
	std :: sort( a + 1, a + 1 + N, cmp );
	int fir = 1;
	for( ; fir <= N && fir + 1 <= a[fir + 1] ; fir ++ );
	bool up = ( a[fir] - fir + 1 ) & 1, rig = true;
	for( int i = fir + 1 ; i <= N && a[i] >= fir ; i ++, rig ^= 1 );
	bool tag = ! ( up & rig );
	puts( tag ? "First" : "Second" );
	return 0;
}
```

---

## 作者：Soulist (赞：5)


### 1.前置芝士：

博弈论，当然这道题不需要 SG 函数之类的东西

我们只需要知道这样一个**引理**？

对于一场游戏，假设先后手公平，那么一个状态为必胜，当前仅当其能转移的状态有一个为必输，而一个状态为必输，当前仅当其能转移的状态均为必赢。

我们不妨用 $0$ 表示必输， $1$ 表示必赢

### 2.本题如何做？

**$Step1.$转化**

考虑转化问题模型，我们将 $a$ 值排序，我们将这些连续的 $a$ 铺在网格图上，可以得到一个连续的图形，第$i$个矩形的高度为$a_i$

那么初始没有操作我们就在$(1,1)$这个位置

那么两种操作可以分别理解成为你向右/向上走一步

谁先走出去谁输

所以不难发现，边界都是必输$(0)$的状态，接下来有一个比较好玩的性质


**对于任意一个点，它的右上方点的状态与其相同**

#### 证明：

不妨假设此点为$0$且其右上方的点状态为$1$

那么它两边的点应该长这个样子：因为$0$只能走到$1$，所以图应该

$$1~~1$$

$$0~~1$$

我们可以尝试把这张图继续画下去

$$0 ~~1~~..$$

$$1~~1~~1$$

$$0~~1~~0$$

很快你发现矛盾了，这说明好像情况有些不对，所以如果一个点是$0$那么它右上方的点的状态也是$0$

当然对$1$也类似套路就可以推出矛盾，所以我们可以得出结论**对于任意一个点，它的右上方点的状态与其相同**

--------------------------

**$Step2.$解法**

我们考虑先$O(n\log n)$的排序，构造出模型

然后发现$(1,1)$的状态等同于$(2,2)...(x,x)$

于是我们可以$O(N)$的扫一遍，找到边界（即$y=x$这条直线上最外面的点）

然后此点可能可以向上走也可能可以向右走

于是只要判一下两边是否存在$0$就可以知道$(1,1)$的状态了

至于如何判？我们发现最边界一定是$0$（比如这个点最上面和它最右边）

那么因为现在这个点已经是$y=x$的边界了，也就是说它最多长这样：

$x$

$(x)~~x~~x$

于是我们只要判一下与两边的距离$\%2$的值就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 1e5 + 5 ;
int a[N], n ;
bool cmp( int x, int y ) {
	return x > y ; 
}
signed main()
{
	n = read(); rep( i, 1, n ) a[i] = read() ; 
	sort( a + 1, a + n + 1, cmp ) ; 
	int ans ; 
	rep( i, 1, n ) {
		if( a[i + 1] < ( i + 1 ) ) {
			ans = ( a[i] - i ) % 2 ;
			int flag = 0 ; 
			for( re int j = i + 1; j <= n; ++ j ) {
				if( a[j] == ( i ) ) ++ flag ; 
			}
			ans = max( ans, flag % 2 ) ;
			break ;
		}
	}
	if( ans ) puts("First");
	else puts("Second");
	return 0;
}
```

---

## 作者：zhaoyp (赞：4)

[AGC002E](https://atcoder.jp/contests/agc002/tasks/agc002_e)

$\text{Difficulty : 2889}$ 。

# Description

> 有 $n$ 堆石子，每堆石子有 $a_i$ 个，两人轮流操作。要么取走石子最多的一堆，要么将每堆石子取走 $1$ 个。谁取走最后 $1$ 个石子，谁就输了。假设两人都足够聪明，求先手必胜还是后手必胜。

# Solution

神仙题。

是一个经典的将博弈过程转化成网格图的模型。

考虑将 $a$ 降序排序，排在一个 $n$ 列的网格图上。初始站在 $(1,1)$ 这个位置上，令站的位置的右上部分是剩余的石子，那么两种操作相当于向上或向右走一格，谁走出去谁就输了。

记 $f_{x,y}$ 表示在 $(x,y)$ 上胜负状态，$1$ 代表先手必胜，$0$ 代表先手必败。

下面我们来证明：$f_{x,y} = f_{x+1,y+1}$。

一个状态是必败态，当且仅当它的所有后继状态都是必胜态；一个状态是必胜态，当且仅当它的后继状态存在一个必败态。

- 若 $(x,y)$ 必胜，则 $(x+1,y),(x,y+1)$ 中至少有一个必败，必败的所有后继状态都是必胜，$(x+1,y+1)$ 都是他们的后继状态，所以 $(x+1,y+1)$ 必胜。

- 若 $(x,y)$ 必败。则 $(x+1,y),(x,y+1)$ 必胜，则 $(x+2,y+1),(x+1,y+2)$ 必胜。所以 $(x+1,y+1)$ 的两个后继状态都是必胜，故 $(x+1,y+1)$ 必败。

于是我们只需要找到 $(1,1)$ 所在对角线上的最后一个点。在这个点上，之后要么一直向上，要么一直向右，两个后继状态的胜负根据剩余步数的奇偶比较好判断。就可以推出 $(1,1)$ 的状态。

时间复杂度 $O(n)$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n,a[maxn],ans;
bool cmp(int a,int b){return a > b;}
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	sort(a + 1,a + 1 + n,cmp);
	for(int i = 1;i <= n;i++)
		if(i + 1 > a[i + 1])
		{
			int x = (a[i] - i + 1) & 1,y = 1;
			for(int j = i + 1;j <= n&&a[j] >= i;j++)
				y ^= 1;
			puts(x + y == 2 ? "Second" : "First");
			return 0 ;
		}
}
```

---

## 作者：CYJian (赞：3)

## AGC002E

这题也算是比较简单的一道博弈题。

首先我们把 $a_i$ 从大到小排序，然后画出一个高度的柱状图，就可以转化成下面这个问题：

一开始你在 $(1, 1)$，每一次你可以从 $(x,y)$ 走到 $(x+1,y)$ 或者 $(x, y+1)$。你不能走到 $(n+1,y)$，对于任意 $y \in Z$；也不能对于任意 $x \in [1,n]$ 走到高于 $(x,a_x)$ 的地方。无法继续走的人判负。

比如下面这个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/4omlhx4y.png)

然后就可以非常方便的在 $O(n^2)$ 的时间复杂度内计算出胜负关系了。

但是没有办法通过，考虑优化：我们只关心 $(1,1)$ 的胜负关系。不难发现，满足 $y=x+b$，$b \in Z$ 的点状态是一样的。所以我们可以通过计算对角线上任意一个点的状态来得到我们想要的状态。

再举一个栗子：（ $W$ 为以所在点起始时先手胜，$L$ 为以所在点起始时先手负）

![](https://cdn.luogu.com.cn/upload/image_hosting/ldy8ckw5.png)

对于最靠近边界的点，我们发现只需要计算其 向上/向右 到边界的距离的奇偶性，就可以知道这个点的胜负状态：如果存在一个方向的距离是奇数，那么必胜；否则必败。

简单判断就完事了。代码简单，不贴了（

---

## 作者：小木虫 (赞：2)

### Preface  
经典博弈论转化为走网格的题目，但是本蒟蒻一开始搞成了删除头尾数目的网格。  
### Problem   
给你 $n$ 堆糖果，两个人轮流吃糖果，有两种吃糖果的方法：  
1.每堆分别吃一个。  
2.吃掉最多的那堆。  
问谁不会吃掉最后一个糖果。  

### Solution  
我们先按常规套路将糖果按数目降序排序，然后我们发现第二种吃糖方法等于直接删除没删除的最前面一堆，第一种方法就是将所有堆全部减一糖果。  

于是我们可以设状态：$G_{i,j}$ 为 $i$ 前面的糖果堆悉数删除，并且所有糖果堆都分别被吃了 $j$ 个糖果后这手能否赢下游戏。  
状态转移方程为 $G_{i,j}\leftarrow(\neg G_{i+1,j})\lor (\neg G_{i,j+1})$

我们现在已经可以利用该状态进行 dp 了，但是这样的时间复杂度过高，我们需要再在状态形成的网格上面找规律。  

众所周知，找规律要从结束状态开始倒退来找，于是我们从最后一堆开始倒退来找规律。最后一堆仅受自己一堆的上面状态影响，所以这是一个交叉的 01 串。  
这时为 0 的状态就会影响前面一堆相同高度的状态，那个状态一定为 1。  
根据归纳法总结，处于同一对角线上的状态其答案一致，于是我们只需要找同对角线上最高的状态就行了，其转移只受上面的一连串与右边的一连串状态影响。这跟其奇偶性相关。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;int a[N];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n,greater<int>());
	for(int i=1;i<=n;i++){
		if(i+1>a[i+1]){
			int j=0;
			while(a[i+j+1]==i)j++;
			if(((a[i]-i)%2==1)||(j%2==1))
				cout<<"First";
			else cout<<"Second";
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：foreverlasting (赞：2)

题面：

桌上有N 堆糖果,第i 堆糖果有Ai 个糖。两人在玩游戏，轮流进行，每次进行下列两个操作中的一个

1.将当前最大的那堆糖果全部吃完

2.将每堆糖果吃掉一个

吃完的人输,假设两人足够聪明，问谁能必胜 1<=n<=1^5 1<=ai<=10^9

输出First（表示第一个人必胜）,或Second（表示第二个人必胜）

博弈论。

好神的博弈论，不看题解完全不会系列。首先我们将决策表打印出来，是长成这样的：![](https://img-blog.csdn.net/20180820172743360?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RpNENvdmVSeQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)（别人的图）

那么很明显，从大到小排序后，无论是都删去一个，还是删去最大的一列在这张图上永远是删去一排。也就是说，当对手选择一种操作，你选择另一种操作时，当前的点永远会随着对角线移动，那么先手必胜就会长成这样。
![](https://img-blog.csdn.net/20180820172951241?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RpNENvdmVSeQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

那么就很简单了，判断一下对角线，就写好了。

code:
```
//2018.9.24 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e5+10;
namespace MAIN{
    inline bool cmp(const res &x,const res &y){
        return x>y;
    }
    int n,a[N];
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++)a[i]=read();
        sort(a+1,a+n+1,cmp);
        for(res i=1;i<=n;i++)
            if(i+1>a[i+1]){
                res j=i+1,ans=0;
                while(a[j]==i)ans^=1,j++;
                if((ans||((a[i]-i)&1)))puts("First");
                else puts("Second");
                return;
            }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：ImmortalWatcher (赞：1)

很妙的博弈论。

我们考虑将题目换一个模型，排序后把每颗糖都摆放出来，那么就会出现类似如下的样子。

```
000
0000
0000000
0000000
000000000
```
我们一开始在原点，那么可以发现，操作一本质上就是向上走了一行，操作二就是向右走了一列，最后走到边界就是吃完了所有的糖果。

令 $f(x,y)$ 表示第 $x$ 行，第 $y$ 列的胜败状态，由定义可知，边界都是必败态。

那么可以发现，如果一个点上方或右方有必胜态，那么此点必败。如果没有，则为必胜态。

一个小结论：

$$f(x,y)=f(x+1,y+1)$$

分情况讨论。

- 如果 $(x,y)$ 为必胜态，那么如图所示。

```
败
胜败
```
假设 $(x+1,y+1)$ 为必败态那么可得下图

```
败
胜败
败败败
胜败胜败
```

具体来说：

- 因为 $(x+1,y)$ 为必败态，$(x+1,y+1)$ 为必败态，所以 $(x+2,y)$ 必须为必胜态。

- 同理 $(x,y+2)$ 必须为必胜态。

- 所以 $(x,y+2)$ 和 $(x+2,y)$ 的上方和右方都为必败态。

- 这时候 $(x+1,y+1)$ 就必须是必胜态，与假设矛盾，所以 $(x+1,y+1)$ 只能是必胜态。

- 如果 $(x,y)$ 为必败态，那么 $(x,y+1)$ 和 $(x+1,y)$ 必有其中一个是必胜态，也就得到 $(x+1,y+1)$ 一定是必败态。

结论得证。

剩下的事情就是找到一个从原点开始的最右上的点，就可以知道原点的状态。

因为是最右上的，也就是边界，那么也就是要么一直走上方，要么一直走右方，考虑奇偶性即可得到该点的胜败状态。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100010];
bool cmp(int x,int y){return x>y;}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1,cmp);
    for (int i=1;i<=n;i++)
        if (i+1>a[i+1])
        {
            int ret=0;
            for (int j=i+1;j<=n;j++) 
                if (a[j]==i) ret++;
            if((ret&1)||((a[i]-i)&1)) puts("First");
            else puts("Second");
            return 0;
        }
    return 0;
}
```


---

## 作者：KAMIYA_KINA (赞：1)

## Tag

博弈。

## Description

给定 $n$ 堆分别为 $a_i$ 的物品，每一次可以取所有堆的物品一个或者取掉最大的一个物品。如果一个人把所有的物品都取完他就输了。

求出先手必胜还是后手必胜。

$\texttt{data range:} n\leq 10^5, a_i\leq 10^9$.

## Solution

将物品从大到小排序之后不难发现问题转化为了取一个网格图的第一行或者第一列，最终谁会后把物品取完。

这一步转化是比较不显然的，但是想清楚之后可以发现整个问题可以直接转化为一个网格图，求出从 $(0,0)$ 离开这个网格图的问题，这个网格图的边界就是将物品排序之后的一个轮廓（可以自己画图具体理解一下）。

到这里我们又陷入了瓶颈，你会发现到了边缘的时候存在两种情况：

第一种是直接走出去，这一种会导致当前操作的人输掉，所以只有走无可走的时候才选这条路。

第二种是沿着边缘走，但是注意不能往左边和下面走。

这个时候我们发现，如果走到了边缘，胜负就很容易求出。如果往上面有奇数个，那么说明此时操作的人必胜，往右边亦然。

这个时候需要大胆猜测一番，我们猜测当前点与右上角的点的博弈情况一定相同！

首先感性的认识，对于后手而言，如果右上角的点是后手必胜，那么后手一定可以转移到右上角的点。

但是直接证明具有一定难度，所以考虑反证法，假设 $0$ 为必败，$1$ 为必胜。

假设当前点为 $0$，右上角的点为 $1$，那么就有：

```
1 1
0 1
```

这种局面，我们对这个局面进行扩展。

```
0 1? 
1 1 1?
0 1 0
```

我们发现了矛盾，此刻这个右上角的点明显被两个 $1$ 给包含了，所以你发现他扯淡了。

对于当前点为 $1$，右上角为 $0$ 的情况。

初始一定有：

```
1 0
1 1
```

你看他直接扯淡了。

所以我们直接发现，当前点的状态与右上角点的状态一定一样。

对于原点直接往右上角跳到一个边缘点然后处理就可以了，时间复杂度为排序的 $O(n \lg n)$，用基数排序可以做到 $O(n)$。

```cpp
const int N = 1e5 + 10;

int n;
int a[N];

inline void input() {
    n = rd;
    FOR(i, 1, n) a[i] = rd;
    return ;
}

inline void init() {
    sort(a + 1, a + 1 + n, greater<int>());
    return ;
}

inline void work() {
    for(int i = 1; i <= n; i++) 
        if(i + 1 > a[i + 1]) {
            int j = 0;
            for(; a[i + j + 1] == i; j++);
            if((j & 1) || (a[i] - i) & 1) puts("First");
            else puts("Second");
            break;
        }
    return ;
}

inline void solve() {
    input();
    init();
    work();
    return ;
}
```

---

## 作者：ETHANK (赞：1)

博弈论经典题目。

可以发现将数组降序排列后看成一堆方块，每次操作相当于把最左边的一列或者最底下一行的方块消除，消除最后一个方块的人输掉游戏。下面用 $(x,y)$ 表示消掉了前 $x$ 列 和前 $y$ 行的所有方块。

（这里就不再赘述必胜态和必败态的定义了）

引理：若 $(x+1,y+1)$ 没有消除全部方块，那么 $(x,y)$ 和 $(x+1,y+1)$ 的状态相同。

证：

- 若 $(x+1,y+1)$ 是必败态，则先手从 $(x,y)$ 无论怎么走，后手都可以转移到 $(x+1,y+1)$ 这个状态。

- 若 $(x+1,y+1)$ 是必胜态，由定义知道 $(x+2,y+1)$ 和 $(x+1,y+2)$ 至少有一个必败态（消除全部方块后先手必胜，所以必败态必然满足假设）。不妨设 $(x+2,y+1)$ 是必败态，那么由上一种情况推出 $(x+1,y)$ 是必败态，它与 $(x,y)$ 相邻。所以 $(x,y)$ 是必胜态。

这样就证明了初始状态 $(0,0)$ 等价于最大的 $(x,x)$ 。而最大化 $x$ 意味着这个点之后只能沿单方向 $+1$ ，判断是否存在一个方向需要奇数次操作消除即可。

时间复杂度：$O(N)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e5+5;
int a[N],n;
bool cmp(int x,int y){return x>y;}
int main(){
    n=read();
    rep(i,1,n)a[i]=read();
    sort(a+1,a+n+1,cmp);
    rep(i,1,n){
        if(i+1>a[i+1]){
            int ans=0;
            for(int j=i+1;a[j]==i;++j)ans^=1;
            ans|=(a[i]-i)&1;
            puts(ans?"First":"Second");
            break;
        }
    }
    return 0;
}
```





---

