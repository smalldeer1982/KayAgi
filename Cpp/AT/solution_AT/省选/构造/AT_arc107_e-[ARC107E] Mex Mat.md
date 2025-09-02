# [ARC107E] Mex Mat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc107/tasks/arc107_e

$ N\ \times\ N $ の行列を考えます。この行列の $ i $ 行目、$ j $ 列目の値を $ a_{i,\ j} $ とします。$ i\ =\ 1 $ か $ j\ =\ 1 $ を満たす $ a_{i,\ j} $ については $ 0 $, $ 1 $, $ 2 $ のいずれかの値が入力で与えられます。残りの値は以下の規則に従い定めます。

- $ a_{i,j}\ =\ \mathrm{mex}(a_{i-1,j},\ a_{i,j-1})\ (2\ \leq\ i,\ j\ \leq\ N) $。ただし $ \mathrm{mex}(x,\ y) $ は次の表に従う。
 
$ \mathrm{mex}(x,\ y) $ $ y=0 $ $ y=1 $ $ y=2 $ $ x=0 $ $ 1 $ $ 2 $ $ 1 $ $ x=1 $ $ 2 $ $ 0 $ $ 0 $ $ x=2 $ $ 1 $ $ 0 $ $ 0 $行列の要素のうち、値が $ 0,\ 1,\ 2 $ であるものはそれぞれ何個でしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500{,}000 $
- 入力される $ a_{i,\ j} $ の値はすべて $ 0,\ 1,\ 2 $ のいずれか

### Sample Explanation 1

行列は以下のようになります。 ``` 1 2 0 2 0 1 2 0 0 2 0 1 0 1 2 0 ```

## 样例 #1

### 输入

```
4
1 2 0 2
0
0
0```

### 输出

```
7 4 5```

# 题解

## 作者：jijidawang (赞：11)

性质别的题解已经说的很明了了，就是几条对角线状物经过几轮迭代后就不变了，然后按照这个结论小范围暴力就能过了，时间复杂度 $\Theta(n)$。

[Submission](https://atcoder.jp/contests/arc107/submissions/42079739)。

下面是关于这个性质的一种证明，仅供参考，来自 CF：

断言：
1. 方阵中不可能存在形为 `x x` 的子矩阵。
2. 方阵中不可能存在子矩阵 `2 1 2`。
3. 方阵中不可能存在子矩阵 `1 2 1`。
4. 方阵中不可能存在子矩阵 `0 2 0`。

证明：

断言 1 是显然的。

对于断言 2，如果存在一行 `2 1 2`，不难推出上一行必然是 `? 0 0`，这显然是不可能的，断言 3 类似。

对于断言 4，如果存在一行 `2 1 2`，不难推出上一行必然是 `2 1 2`，这是不可能的。

由此，证明了四个断言。

从而，对于子矩阵 `x y z` 来说，通过讨论 $y$ 的取值可以得到必有 $y=\operatorname{mex}(x,z)$，过程繁而不难，略去。

从而，可以得到：
$$a_{n,m}=\operatorname{mex}(a_{n,m-1},a_{n-1,m})=\operatorname{mex}(a_{n-1,m-2},a_{n-1,m})=a_{n-1,m-1}$$

然而，对于第一行，最基础的断言是不正确的，从而需要对 $n,m$ 较小的情况特殊处理，也就是需要证明，经过常数步之后，四个断言被同时满足（或者结论成立）。这个常数不能太大。

断言 1 总是正确的，所以之后的讨论只能基于断言 1 进行。让我们讨论一个最基本的 $4\times 4$ 方格，其中不含第一行第一列：
```plain
. . . .
. . . .
. . x z
. . w y
```
那么：
- 如果 $w\neq z$，则根据断言 1，$x,y$ 肯定与 $w,z$ 都不同，因为值域大小只有 2，所以 $x=y$。
- 如果 $w=z$，假设 $x\neq y$，于是局面可以被重写为：
  ```plain
  . . . .
  . . . ?
  . . a b
  . ? b c
  ```
  根据断言 1，两个 `?` 只能等于 $a$ 或 $c$，接下来，有两种情况：
  - 两个 `?` 都是 $c$。那么根据断言 1，可以填出：
    ```plain
    . . . .
    . . b c
    . b a b
    . c b c
    ```
    这表明 $a=\operatorname{mex}(b,b)=c$，矛盾。
  - 两个 `?` 中至少有一个 $a$。不妨令左面那个问号是 $a$：
    ```plain
    . . . .
    . . . ?
    . . a b
    . a b c
    ```
    那么可以得到 $\operatorname{mex}(a,a)=b$ 和 $\operatorname{mex}(b,b)=c$，那么经过讨论可以得出必然有 $a=2,\ b=0,\ c=1$：
    ```plain
    . . . .      
    . x v ? 
    x u a b
    t a b c
    ```
    用类似的方法，可以导出 `t u v` 必然是 `0 1 0` 或 `1 0 1`，则根据断言 1 可以知道，其左上的两个位置 `x` 都是 `2`，从而根据 $\operatorname{mex}(2,2)=0$，可以知道 $t=1,\ u=0,\ v=1$，那么根据断言 1，`?` 肯定是 2，然后不难根据 mex 的定义得出他的上面是一个 `0`，又根据断言 1，肯定 `0` 的左边是 `2`。有点麻烦，看一下图：
    ```plain
    . . 2 0
    . 2 1 2
    2 0 2 0
    1 2 0 1
    ```
    但是，我们发现这个构造一定是不合法的，因为它指出 $\operatorname{mex}(2,2)=1$，矛盾。
  
  从而，$w=z$ 时，必然有 $x=y$。


从而，命题得证。也可以由此知道，4 次迭代之后，结论一定成立。

---

## 作者：ainivolAGEM (赞：2)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/article/udrtucir)

希望讲明白了，而不是赌运气。

感谢部分 dalao 的题解提供思路。

## 题目大意

[题目](https://www.luogu.com.cn/problem/AT_arc107_e)给出一个 $n$ 阶方阵 $A$（仅包含 $0$、$1$ 和 $2$）第一行和第一列，此后每一项都满足 $A _ { i , j } = \operatorname { mex } \{ A _ { i - 1 , j } , A _ { i , j - 1 } \}$，现求整个矩阵共有几个 $0$、$1$ 和 $2$。其中 $\operatorname { mex } \{ x , y \}$ 的意思为：在 $0$、$1$ 和 $2$ 中不等于 $x$ 或 $y$ 的最小值。

题目很明确，没尝试过的可以试试小数据产生的结果，找找规律，这个叫观察法。~~没准答案就出来了。~~ 

## 题目分析

我们沿着上面的思路，先从小数据开始。样例看不出什么，那我们从大一点点的数据开始，初始一行一列随机，打出整个 $A$ 看看有没有规律。

### 生成代码如下：


```cpp
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
typedef long long ll;
const int N=54;
ll n,a[N][N];
ll mex(ll x,ll y){
	if(x>y){
		swap(x,y);
	}
	if(x==0&&y==1){
		return 2ll;
	}else if(x==0&&y==0||x==0&&y==2){
		return 1ll;
	}else if(x==1&&y==2||x==1&&y==1||x==2&&y==2){
		return 0ll;
	}
}
int main(){
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		a[1][i]=rand()*rand()%3;
		a[i][1]=rand()*rand()%3;
	}
	for(int i=2;i<=n;i++){
		for(int j=2;j<=n;j++){
			a[i][j]=mex(a[i-1][j],a[i][j-1]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<a[i][j]<<' ';
		}
		cout<<'\n';
	}
}
```
$n = 20$ 时生成结果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ns43w85h.png)

~~很抽象啊有木有。确实啊我第一次看到什么玩意儿啊根本看不懂。~~

第一眼看过去吧，可以发现对角线的数字大致都是相同的，但是前几个数字又好像~~不是好像就是~~不同。

什么时候开始相同的？再大一点的表可以发现大概是 $4$ 到 $5$ 个数时就开始重复前面的了。

### 证明

考虑怎么证明。我们假设一个 $4 \times 4$ 的矩阵。~~当然你也可以直接开打赌运气。~~

```markdown
? ? ? ?
? ? ? ?
? ? a b
? ? c d
```

我们不看第一行第一列，就是要证明无论 $b$ 和 $c$ 怎么取，$a = d$ 恒成立。

设 $b \neq c$，则据 $\operatorname { mex }$ 在三种情况中 $a \neq b$ 且 $ a\neq c$，同时 $b \neq d$ 且 $c \neq d$，可得 $a = d$，此情况得证。

若 $b = c$ ，设 $a \neq d$，我们可变换矩阵如下。

```markdown
? ? ? ?
? ? y e
? x a b
? d b c
```

很明显的，$d$ 和 $e$ 都不能是 $b$，只能是 $a$ 或 $c$，我们分类讨论。若 $d$ 和 $e$ 都为 $c$，那么返回之前 $a \neq d$ 的情况，那么 $x = y = b$，此时出现矛盾：$a = c = \operatorname { mex } \{ b , b \}$，舍去。

那么至少 $d$ 和 $e$ 有一为 $a$，图对称，令 $d = a$，有新矩阵如下。

```markdown
? ? ? ?
? ? ? e
? ? a b
? a b c
```

可以发现矩阵下方有 $\operatorname { mex } \{ \operatorname { mex } \{ a , a \} , \operatorname { mex } \{ a , a \} \} = c$，~~经枚举~~可得 $a = 2$、$b = 0$ 且 $c = 1$。

好好好我知道你很激动，但你先别急。我们把图填一下。

```markdown
? ? ? w
? ? z e
? y 2 0
x 2 0 1
```

~~好看多了是不是~~首先，由 $2 = 2$ 那里回归以前的定理结论 $y = 0$，那么根据 $\operatorname { mex }$ 特性 $y$ 下面的 $2$ 可推出 $x$ 只能等于 $1$，同理可知 $z = 1$，我们再填一下。

```markdown
? ? z w
? y 1 e
x 0 2 0
1 2 0 1
```

新矩阵我们根据之前的性质可以知道 $x \neq 0$ 且 $x \neq 1$，那么 $x = 2$，同理 $y = 2$，同理 $e = 2$。根据 $\operatorname { mex }$，我们可得 $z = 0$，同理 $w = 0$。最终图如下。

```markdown
? ? 0 0
? 2 1 2
2 0 2 0
1 2 0 1
```

发现不对劲没有，那俩 $0$ 挨一起了，很明显不合理啊对不对，而我们自始至终推下来唯一的假设是 $a \neq c$，这只能说明一件事：$a = c$。

至此，所有情况都证明了，而由于我们是在不算第一行第一列的 $4 \times 4$ 矩阵上完成的，所以证明在第四行之后，$a = c$ 始终成立。

换句话说，从第五行开始，$A _ { i , j } = A _ { i - 1 , j - 1 }$。

那么我们先枚举前面的四行四列求出解，后面的就都可以根据第四行和第四列求出解了。

## AC code

代码较诡异，可自己修改。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+4;
const int T=8;
const int C=3;
ll n,a[T][N],b[N][T],ans[C];
ll mex(ll x,ll y){
	if(x>y){
		swap(x,y);
	}
	if(x==0&&y==1){
		return 2ll;
	}else if(x==0&&y==0||x==0&&y==2){
		return 1ll;
	}else if(x==1&&y==2||x==1&&y==1||x==2&&y==2){
		return 0ll;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	if(n<=4){
		for(int i=1;i<=n;i++){
			cin>>a[1][i];
			ans[a[1][i]]++;
		}
		for(int i=2;i<=n;i++){
			cin>>a[i][1];
			ans[a[i][1]]++;
		}
		for(int i=2;i<=n;i++){
			for(int j=2;j<=n;j++){
				a[i][j]=mex(a[i-1][j],a[i][j-1]);
				ans[a[i][j]]++;
			}
		}
		cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2];
		exit(0);
	}
	for(int i=1;i<=n;i++){
		cin>>a[1][i];
		ans[a[1][i]]++;
	}
	for(int i=2;i<=4;i++){
		cin>>a[i][1];
		ans[a[i][1]]++;
	}
	for(int i=2;i<=4;i++){
		for(int j=2;j<=n;j++){
			a[i][j]=mex(a[i-1][j],a[i][j-1]);
			ans[a[i][j]]++;
		}
	}
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			b[i][j]=a[i][j];
		}
	}
	for(int i=5;i<=n;i++){
		cin>>b[i][1];
		ans[b[i][1]]++;
	}
	for(int i=5;i<=n;i++){
		for(int j=2;j<=4;j++){
			b[i][j]=mex(b[i-1][j],b[i][j-1]);
			ans[b[i][j]]++;
		}
	}
	for(int i=4;i<=n;i++){
		ans[a[4][i]]+=n-i;
	}
	for(int i=5;i<=n;i++){
		ans[b[i][4]]+=n-i;
	}
	cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2];
}
```

如有错误欢迎批评指正。

---

## 作者：hbhz_zcy (赞：1)

update: 20240906  更改失误表述

------

题意很简洁，给出一个方阵 $A$ 的 $x=1$ 和 $y=1$ 项，并使用 $A_{i,j}=\mathrm{mex}(A_{i-1,j},A_{i,j-1})$ 式子构造出整个方阵。问方阵中值为 $0,1,2$ 点的数目。  

不难分析出，方阵中只会出现 $0,1,2$。具体的转移关系只有 $3$ 种（假设 $\mathrm{mex}$ 中第一个数不大于第二个）：  
+ $\mathrm{mex}(0,1)=2$  
+ $\mathrm{mex}(0,\mathrm{else})=1$  
+ $\mathrm{else}=0$  

考虑手动模拟一下，看起来似乎有循环。比如：  
```
0 0        1 1        2 2
0 1        1 0        2 0
0 2        1 2        2 1
0 1        1 0        2 0
0 2        1 2        2 1
0 1        1 0        2 0
0 2        1 2        2 1
```
（给定首行首列）  
考虑找一组数据，暴力打一下表，发现可能存在一个性质，$\forall i,j \gt 4,A_{i,j}=A_{i-1,j-1}$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/chtkt7s7.png?x-oss-process=image/resize,h_300 "官方数据")  

假如可以证明上述猜想的正确性，那么就可以只存 $\min(x,y) \le 4$ 的值，$\Theta(N)$ 求解。  

证明：  
分析可能构造出对角线相同的情况：  
```
01  01  02  02  10  12  10  20  21
10  20  10  20  21  01  01  12  02
```  
也就是说，当且仅当以这些情况不断拼接构成的行，产生新行的时候总是可以将性质维持下去。于是我们只需要证明两个东西：  
+ 对于第 $4$ 行且列标不小于 $4$ 的点构成的序列，一定满足这个形式。  
+ 对于第 $4$ 行及之后，向下再推一行，列标不小于 $4$ 的点构成的序列，仍然满足这个形式。  

第一个不太会证明，大概是不满足对角线的情况被满足的情况分隔开来，而经过一轮转移后，一些满足的情况不变，一些不满足的情况变得满足。然后经过若干轮转移后就都满足了。似乎是可以暴力枚举分隔以及新产生的点验证出来的。  
对于第二个，只需要暴力枚举前 $4$ 个值和新加入的值，验证向后新产生的数与后面的序列总能够满足形式，就可以证明了。  

```cpp
//g++ a.cpp -o a -g -std=c++14 -O0 -Wall -fsanitize=undefined
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
namespace rdin{
	const int maxr=1e6+10;char buf[maxr],*l,*r;
	inline char gtc(){if(l==r){r=(l=buf)+fread(buf,1,maxr,stdin);}return l==r?EOF:*l++;}
	inline int qd(){int rt=0;char c=gtc();while(c<'0'||c>'9'){c=gtc();}while('0'<=c&&c<='9'){rt=(rt<<3)+(rt<<1)+(c^48),c=gtc();}return rt;}
}
using rdin::qd;
const int maxn=5e5+10;
int N,a[maxn],b[maxn],f[maxn];LL cnt[3];
int calc(int x,int y){return x+y==1?2:min(x,y)?0:1;}
int main(){
//	freopen("in.txt","r",stdin);
	N=qd();
	for(int i=1;i<=N;i++)  cnt[a[i]=qd()]++;
	b[1]=a[1];for(int i=2;i<=N;i++)  b[i]=qd();
	for(int i=2;i<=4&&i<=N;i++){
		cnt[a[1]=b[i]]++;
		for(int j=2;j<=N;j++)  cnt[a[j]=calc(a[j-1],a[j])]++;
	}
	for(int i=4;i<=N;i++)  cnt[a[i]]+=N-i;
	for(int i=5;i<=N;i++){
		cnt[a[1]=b[i]]++;
		cnt[a[2]=calc(a[1],a[2])]++;
		cnt[a[3]=calc(a[2],a[3])]++;
		cnt[a[4]=calc(a[3],a[4])]+=N-i+1;
	}
	printf("%lld %lld %lld\n",cnt[0],cnt[1],cnt[2]);
	return 0;
}
```

---

## 作者：Mr_Avalon (赞：1)

推了许多性质感觉实在太过贫弱，决定打个表先。

![](https://cdn.luogu.com.cn/upload/image_hosting/kthpa9en.png)

于是发现一个神奇的性质，每个数在经过几行 $\text{mex}$ 之后会一直沿着对角线下去，那么到什么时候会达到这种状态呢？不知道，但显然不会太大，不然复杂度就炸了。

既然不会太大，直接把前五十层打出来，后面在一条对角线上的元素肯定就和第五十层的相同了。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>

const int N=5e5+5;

inline int read()
{
	int v=0,flag=0;char ch=getchar();
	while('0'>ch||ch>'9') flag|=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9') v=v*10+(ch&15),ch=getchar();
	return flag? -v:v;
}

int n,a[N],b[N];
long long ans[3];

inline int mex(int a,int b) {return a&&b? 0:a^1&&b^1? 1:2;}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	#endif

	n=read(),ans[a[1]=b[1]=read()]++;
	for(int i=2;i<=n;i++) ans[a[i]=read()]++;
	for(int i=2;i<=n;i++) ans[b[i]=read()]++;

	for(int k=2;k<=std::min(n,50);k++)
	{
		ans[a[k]=b[k]=mex(a[k],b[k])]++;
		for(int i=k+1;i<=n;i++)
		{
			ans[a[i]=mex(a[i],a[i-1])]++;
			ans[b[i]=mex(b[i],b[i-1])]++;
		}
	}

	if(n>50)
	{
		ans[a[50]=b[50]]+=n-50;
		for(int i=51;i<=n;i++)
		{
			ans[a[i]]+=n-i;
			ans[b[i]]+=n-i;
		}
	}

	printf("%lld %lld %lld",ans[0],ans[1],ans[2]);
}
```


---

## 作者：Claire0918 (赞：0)

定理 1：对于确定的 $x$，任意的 $y$ 都可以使得 $\operatorname{mex}\{x, y\} \neq x$。

这定理可以用定义简单证明。

我们注意到从一定位置开始矩阵内每一条与对角线平行的直线上的数是相等的。

尝试证明该性质。

当 $a_{i, j} = 0$ 时，显然 $a_{i + 1, j} \neq 0, a_{i, j + 1} \neq 0$，从而 $a_{i + 1, j + 1} = 0$。

当 $a_{i, j} = 1$ 时，在 $a_{i - 1, j}$ 或 $a_{i, j - 1}$ 中至少有一个为 $0$，从而 $a_{i, j + 1}$ 或 $a_{i + 1, j}$ 中至少有一个为 $0$，又 $a_{i, j + 1} \neq 1, a_{i + 1, j} \neq 1$，从而 $a_{i + 1, j + 1} = 1$。

$a_{i, j} = 2$ 的方法与 $a_{i, j} = 1$ 的方法是类似的。

于是我们可以先处理出一小块，然后通过性质扩展到其他位置。

“一小块”至少有 $4$ 格，下面作出证明。

我们发现 $a_{i, j} = 1$ 的证明中要求 $a_{i - 1, j}$ 和 $a_{i, j - 1}$ 都有定义，且证明 $a_{i, j - 1}$ 或 $a_{i - 1, j}$ 为 $0$ 可沿对角线扩展要求 $i - 1 \geq 2, j - 1 \geq 2$，从而 $i + 1 \geq 4, j + 1 \geq 4$，即至少处理出 $4$ 格才必然会出现对角线性质。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 500000 + 10, gap = 4;

int n;
int a[maxn], b[maxn];
long long res[3];

inline int read(){
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

inline int mex(int x, int y){
    return x + y == 1 ? 2 : x && y ? 0 : 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        res[a[i] = read()]++;
    }
    b[1] = a[1];
    for (int i = 2; i <= n; i++){
        res[b[i] = read()]++;
    }
    for (int i = 2; i <= n; i++){
        a[1] = b[i];
        for (int j = 2; j <= n; j++){
            if (i > gap && j > gap){
                break;
            }
            a[j] = mex(a[j - 1], a[j]);
            if (i == gap && j >= gap){
                res[a[j]] += n - j + 1;
            }else if (i >= gap && j == gap){
                res[a[j]] += n - i + 1;
            }else{
                res[a[j]]++;
            }
        }
    }
    for (int i = 0; i < 3; i++){
        printf("%lld ", res[i]);
    }

return 0;
}
```

---

## 作者：_abcd_ (赞：0)

[[ARC107E] Mex Mat](https://atcoder.jp/contests/arc107/tasks/arc107_e)

先把矩阵顺时针旋转 $45 \degree$，就可以整行整行的做。手玩一些样例推一下性质，做一轮没有什么好的性质，但是做两轮会发现很有规律。对于 $0/1/2 \space 0 \space 0/1/2$  的情况，发现做两轮后中间那个数还是 $0$。对于 $0 \space 1/2 \space 0$，中间会变成 $0$，对于 $0 \space 1/2 \space 1/2$，则中间的数不会变，对于 $1/2 \space 1/2 \space 1/2$，中间会变成 $1$。这样，在做四轮操作后，序列中的数就不会再变化。因此，只需要算出前若干行和前若干列就行了。复杂度 $O(n)$。

---

### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define maxn 1000005
#define B 5
using namespace std;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*t;
}
int n;
int a[maxn],b[maxn],f[maxn];
ll ans[3];
int mex(int x,int y)
{
    for(int i=0;i<=2;i++)
        if(x!=i&&y!=i)
            return i;
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    n=re();
    for(int i=1;i<=n;i++)
        ans[a[i]=re()]++;
    for(int i=2;i<=n;i++)
        ans[b[i]=re()]++;
    for(int i=1;i<=n;i++)
        f[i]=a[i];
    for(int i=2;i<=n;i++)
    {
        f[1]=b[i];
        for(int j=2;j<=n;j++)
        {
            if(i>B&&j>B)break;
            f[j]=mex(f[j-1],f[j]);
            if(i==B&&j>=B)
                ans[f[j]]+=n-j+1;
            else if(i>B&&j==B)
                ans[f[j]]+=n-i+1;
            else
                ans[f[j]]++;
        }
    }
    printf("%lld %lld %lld",ans[0],ans[1],ans[2]);
    return 0;
}
```

---

