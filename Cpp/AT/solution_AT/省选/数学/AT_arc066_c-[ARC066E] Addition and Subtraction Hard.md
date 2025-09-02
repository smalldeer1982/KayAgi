# [ARC066E] Addition and Subtraction Hard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc066/tasks/arc066_c

joisinoお姉ちゃんは、$ N $ 項から成る式、$ A_1 $ $ op_1 $ $ A_2 $ $ ... $ $ op_{N-1} $ $ A_N $ を持っています。 ここで、$ A_i $ は整数で、$ op_i $ は、`+` または `-` の記号です。 joisinoお姉ちゃんは大きい数が好きなので、括弧を好きな数だけ( $ 0 $ 個でもよい)挿入することで、計算の順番を変え、式の値を最大化したいです。 開き括弧は数の直前、閉じ括弧は数の直後にのみ、挿入することが許されます。 同じ場所に挿入する括弧の個数に制限はありません。 あなたの仕事は、式に括弧をいくつか挿入した際に、式の値としてありうるものの最大値を求めるプログラムを作ることです。

## 说明/提示

### 制約

- $ 1≦N≦10^5 $
- $ 1≦A_i≦10^9 $
- $ op_i $ は、`+` または `-` の記号である。

### Sample Explanation 1

$ 5\ -\ (1\ -\ 3)\ =\ 7 $ となり、これが最大なので、$ 7 $ を出力します。

### Sample Explanation 2

$ 1\ -\ (2\ +\ 3\ -\ 4)\ +\ 5\ =\ 5 $ となり、これが最大なので、$ 5 $ を出力します。

### Sample Explanation 3

$ 1\ -\ (20\ -\ (13\ +\ 14)\ -\ 5)\ =\ 13 $ となり、これが最大なので、$ 13 $ を出力します。

## 样例 #1

### 输入

```
3
5 - 1 - 3```

### 输出

```
7```

## 样例 #2

### 输入

```
5
1 - 2 + 3 - 4 + 5```

### 输出

```
5```

## 样例 #3

### 输入

```
5
1 - 20 - 13 + 14 - 5```

### 输出

```
13```

# 题解

## 作者：louhao088 (赞：16)

一道贪心好题。

看其他题解都用了动态规划，这里来一个贪心解法。


------------


首先我们很容易得到性质

1. 加法肯定不用括号，括号都用在减号。

2. 如果有在一个减号的括号里有另一个减号，那么第二个减号之后的数都直接加就可以。

第二条性质可以根据观察样例三得知。简单证明：因为在减号的括号里，在减号后面，负负得正这个数就是正的，如果后一个数是加号，则只要把它与上一个减号的数括号起来就可以了，这样也是正的。具体看样例 3。


------------


有了这些性质，我们很容易得出，这两个减号一定是相邻的，我们只要枚举每两个相邻的减号，每次计算这两个是第一次两个减号相连时的答案。

那么怎么计算呢？

其实很简单，因为这是第一次有两个减号相连，那么之前肯定就不会有负负得正的情况，而正数放到负数括号里肯定会变劣，所以在它之前只要统计前缀和，而在他第二个负数之后则只要统计其所有数绝对值之和即可，在两个中间，因为肯定是正数，又在负数括号里，所以要减去。求最大就可以。

不要忘记与不加括号比较，因为有可能没括号。



------------
简短的 ARC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
const int maxn=1e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn],b[maxn],sum[maxn],ans,c[maxn],d,res,g[maxn],ans=0;
char ch;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();a[1]=read();sum[1]=a[1];d=n+1;
	for(int i=2;i<=n;i++)
	{
		ch=getchar();while(ch!='+'&&ch!='-')ch=getchar();
		a[i]=read();g[i]=g[i-1]+a[i];
		if(ch=='-')b[i]=1,sum[i]=sum[i-1]-a[i];else sum[i]=sum[i-1]+a[i];
	}
	for(int i=n;i>=1;i--)if(b[i]==1)c[i]=d,d=i;
	for(int i=d;i<=n;i=c[i])
		if(c[i]) ans=max(ans,sum[i]+g[n]-g[c[i]-1]-sum[c[i]-1]+sum[i]);
	ans=max(sum[n],ans);
	cout<<ans<<endl;
 	return 0;
}
```


---

## 作者：Kinandra (赞：11)

这道需要发现一些性质:

1. 括号显然不加在加号后. 

2. 括号嵌套最多两层, 因为括号内第一个负号后的所有数都可以被加, 第一个负号前的所有数只能被减.

利用这两条性质来DP, 设计状态 $f[i][j]$ 表示考虑到前 $i$个 数, 有 $j$ 个未闭合的左括号时的最大值, 转移很简单, 即枚举各个空位是否插入左括号/右括号. 

第 1 条性质保证了一个数被加/被减只取决于它之前还没有闭合的左括号, 第 2 条性质保证了第二维的大小是O(1)的.

总复杂度O(n).

```cpp
#include <bits/stdc++.h>
#define inf 100000000000000ll
using namespace std;

int read();

int n;
long long f[100005][3];
void chmax(long long &x, long long y) { x = x > y ? x : y; }

int main() {
    n = read();
    f[0][0] = 0, f[0][1] = f[0][2] = -inf;
    for (int i = 1, x; i <= n; ++i) {
        x = read();
        {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]),
            f[i][1] = max(f[i - 1][1], f[i - 1][2]);
            f[i][2] = f[i - 1][2];
        }
        f[i][0] += x, f[i][1] -= x, f[i][2] += x;
        if (x < 0) chmax(f[i][2], f[i][1]), chmax(f[i][1], f[i][0]);
    }
    printf("%lld\n", max(f[n][0], max(f[n][1], f[n][2])));
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：activeO (赞：8)

## 题目大意

[题面](https://www.luogu.com.cn/problem/AT2273)说的很清楚了，这里就不细说了。

## 思路

**贪心**

首先发现如果将 $ a[l,r] $ 加上括号，只要当 $ a_l $ 的符号是 $ - $ 的时候才有意义。然后又可以发现当 $ a[l,r] $ 加上括号后，除了这个 $ a_l $ 和区间前面的若干个正数只能减掉以外，别的负数能变成正数，这之间正数也可以通过和前面的负数一起打括号做到也对答案产生正数的贡献。

又可以发现形如 $ -(...)+... -(...) $这样子，会减掉第一颗括号中的前面若干个正数，还会减掉后面一个括号中前面的若干个正数，而将其合并后，只会减掉第一个括号中前面若干个正数，中间原本没打括号的正数也可以通过上述的方法同样做正数贡献，所以整个算式中，只出现一个大括号中嵌套几个小括号是最优的。

实现上只要枚举到那个负数加括号，括号到哪不用考虑，因为括号中第一个负数后都会变成正数贡献，所以自然可以结尾都在 $ n $。

OI 赛时不够自信，交了个错误的，覆盖了这份提交。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=1e5+5;
int a[maxn],sum[maxn],sumh[maxn];
char ch[maxn];
int t[maxn],tot=0;

signed main(){
	
	int n;
	
	scanf("%lld",&n);
	
	ch[0]='+';
	
	for(int i=1;i<=n;i++){
		if(i!=n) scanf("%lld %c",&a[i],&ch[i]);
		else scanf("%lld",&a[i]);
		if(ch[i-1]=='+') sum[i]=sum[i-1]+a[i];
		else{
			t[++tot]=i;
			sum[i]=sum[i-1]-a[i];
		}
	}
	for(int i=1;i<=n;i++) sumh[i]=sumh[i-1]+a[i];
	
	int res=sum[n];
	
	t[tot+1]=n;
	
	for(int i=1;i<=tot;i++){
		int ch1=sum[t[i]];//前面不加括号
		int ch2=sum[t[i+1]-1]-sum[t[i]];//前面无法改变的若干个正数
		int ch3=sumh[n]-sumh[t[i+1]-1];//后面一定都是正数贡献
		int tmp=ch1-ch2+ch3;
		// printf("%lld %lld %lld\n",ch1,ch2,ch3);
		res=max(res,tmp);
	}
	
	printf("%lld\n",res);
	
	return 0;
}

/*
if ch[i]='-',ch[i+1]='-'
then 
*/
```


---

## 作者：WilliamFranklin (赞：6)

### 主要思路

这是一道非常好的贪心+前后缀和题。

首先，我们很容易得出在减号后面加括号，因为在加号后面加括号就跟没加一样。

那么，我们再想，在减号后面加的第一层括号的左括号，右括号先不管，要想让整个表达式的结果最大，就需要这个括号里的值最小，相信这里大家都能很容易明白，不必多说。

好，为了让整个表达式的结果最大，就需要满足一下条件：

 - 一定在减号后面加括号。
 - 让第一层括号里的值最小。
 
那么，为了让第一层括号里的值最小，就可以在第一层括号里再加几个括号。那，问题来了：怎么加第二层的括号呢？首先，上面的条件 $1$ 还是满足，一样的道理，在加号后面加括号就跟没加一样。但是条件 $2$ 就不一样了，因为要想让第一层的括号里面的值最小，那么，我们就要让第一层括号里减的尽可能多，所以我们还要想办法让第二层括号的值尽可能大。

那如何让第二层括号里的值尽可能大呢？对，让第二层括号里的加号最多，其实每一个第二层括号的左括号就是要加在第一层括号中每一个减号后面，每一个右括号要加在第一层括号中每一个减号后连加部分的末尾。那么，为了让表达式的值最大，只要一个第一层的括号即可，并且第一层的右括号的位置就可以确定了，就要加在整个表达式的末尾。所以，我们枚举第一层括号的左括号放在哪，再求每一种的值，我们取其中的最大值即可。

举个例子：$1 - 1 + 4 - 5 + 1 + 4$，要想让它的值最大，可以这样：$1 - \left( 1 + 4 - \left( 5 + 1 + 4 \right) \right) = 6$。

你们可能会发现：TLE 了。

那么我们就要想办法优化它。我们其实可以这么想：拆开括号。假设第一层左括号的位置为 $i$，第一层左括号的第一个数后面连加部分的最后一个数位置为 $j$，那么它的最大值就是 $1$ 到 $i - 1$ 这一段的最大值加上 $j + 1$ 到 $n$ 后面的每个数的和，再减去第一层左括号的第一个数后面连加部分的最后一个数这几个数的和（其实就是第 $i$ 个数到第 $j$ 个数的和），那么，很容易想到的就是用前后缀和实现。关于具体怎么发现的，大家可以自己将一个表达式的值，按照前面方法加上括号后，再按照数学上的定论展开括号，找出规律。

好啦，废话不多说，贴代码（前面可能讲的不是很清楚，看看代码就应该差不多了）。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[100005];
char c[100005];
long long pre[100005];
long long hou[100005];
long long sum;
long long l[100005], r[100005];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (i != n) {
			cin >> c[i + 1];
		}
	}
	pre[1] = a[1];
	for (int i = 2; i <= n; i++) {
		if (c[i] == '-') {
			if (c[i - 1] != '-') {
				l[++sum] = i;
				pre[i] = pre[i - 1] - a[i];
			} else {
				pre[i] = pre[i - 1] + a[i];
			}
		} else {
			pre[i] = pre[i - 1] + a[i];
		}
	}
	for (int i = 1; i <= sum; i++) {
		r[i] = l[i];
		for (int j = l[i] + 1; j <= n; j++) {
			if (c[j] == '-') {
				break;
			} else {
				r[i] = j;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		hou[i] = hou[i + 1] + a[i];
	}
	long long ans = -1e9; 
	for (int t = 1; t <= sum; t++) {
		long long ans1 = pre[l[t] - 1] + hou[r[t] + 1];
		for (int i = l[t]; i <= r[t]; i++) {
			ans1 -= a[i];
		}
		ans = max(ans, ans1);
	}
	cout << max(ans, pre[n]);
} 
```

可能会有一些不足和缺点，欢迎大佬们指出，谢谢！

---

## 作者：xfrvq (赞：4)

首先有两个非常显然的结论：

1. 括号只会加在减号后（因此括号内的运算一定取反）
2. 两个右括号，两个左括号不会重合在一起。

> $$x_0-(x_1-(x_2))$$
>
> 这个应该等于（$x_{0,1,2,3}$ 都是表达式，即若干个 $a_i$ 的计算结果再移项）
>
> $$x_0-(x_1)+x_2$$

3. 括号不会套到 $\ge3$ 层。说一下原因。

> $$x_0-(x_1-(x_2-(x_3)))$$
>
> 这是带三次括号式子的一般形态。考虑将其化简。
>
> $$x_0-x_1+x_2-(x_3)$$
> 
> 但是显然的有另一种得到这个化简结果的方案。
> 
> $$x_0-(x_1-x_2)-(x_3)$$
>
> 所以套到 $\ge3$ 层的括号都可以化简为更简单的情况。


---

我们考虑 $f_{i,j}$ 代表计算到第 $i$ 位，目前有 $j$ 个未匹配的左括号，此时的最大答案。（$j=0,1,2$）

> 为什么可以想到设计这个状态？$f_i$ 表示计算到第 $i$ 位的答案其实是蛮好想到的，不过这个状态太简陋（表示不了括号的嵌套关系），结合二结论不难可以想到一维与括号相关。

然后考虑转移。

+ 转移 $\tt0$：对 $i$ 这一位不加括号。

$$f_{i,j}=f_{i-1,j}\pm a_i$$

> 解释：正常从 $i-1$ 那一位继承答案。至于那个 $\pm$ 是取加还是减，要看 $a_i$ 前原先的符号，以及目前套着括号个数 $j$（套一个括号符号取一次反）

+ 转移 $\tt1$：在 $i$ 这一位后加一个右括号。

$$f_{i,j}=f_{i-1,j+1}\pm a_i$$

> 解释：加一个右括号，相当于消掉了一位左括号，所以要从 $j+1$ 那里继承答案。$\pm$ 取加还是减类似。

+ 转移 $\tt2$：在 $i$ 这一位前加一个左括号。

$$f_{i,j}=f_{i-1,j-1}\pm a_i$$

> 解释：加一个左括号，相当于新增了一位没有匹配的左括号，所以要从 $j-1$ 那里继承答案。$\pm$ 取加还是减类似。

但是并不是 $\forall j=0,1,2$ 都可以用上述式子，有些边界情况特判。

---

$\tt DP$ 数组只会用到上一位的答案，所以可以滚动数组，空间变成 $O(1)$。

```cpp
#include<stdio.h>

using ll = long long;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

void chkmax(ll &x,ll y){ x < y && (x = y); }

int n,op; ll x,dp[2][3]; char c;

int main(){
	scanf("%d",&n);
	dp[0][0] = 0; dp[0][1] = dp[0][2] = -9e18;
	rep(i,1,n){
		op = (c == '-' ? -1 : 1);
		scanf("%lld",&x),x *= op;
		int cur = i & 1,lst = cur ^ 1;
		rep(j,0,2) dp[cur][j] = dp[lst][j] + x * (j & 1 ? -1 : 1);
		chkmax(dp[cur][0],dp[lst][1] - x);
		if(n > 1) chkmax(dp[cur][1],dp[lst][2] + x);
		if(op < 0) chkmax(dp[cur][1],dp[lst][0] + x);
		if(op < 0) chkmax(dp[cur][2],dp[lst][1] - x);
		if(c != n) do c = getchar(); while(c == ' ');
	}
	printf("%lld\n",dp[n & 1][0]);
	return 0;
}
```

---

## 作者：Ebola (赞：3)

容易看出，两层以上的括号都是无意义的，它一定可以被等价地拆成两层以内。而且括号一定是加在减号后面，不然加了和没加有什么区别

于是设f\[x\]\[0/1/2\]表示考虑到第x个数，前面有0/1/2个未匹配左括号是的最大值，转移需要考虑各种添括号拆括号的情况，代码注释已经非常详细了。注意到f\[x\]\[...\]只与f\[x-1\]\[...\]有关，所以用滚动数组把第一维压掉（不压也行）

注意我们说的“添括号”是指在第i个操作符后添一个左括号，“拆括号”是指在第i个操作符前添一个右括号

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
inline int readopt()
{
    char c=Get();
    while(c!='+'&&c!='-') c=Get();
    return c;
}

typedef long long LL;
int num,n,k;
char opt;
LL f[2][3];

inline LL mymax(const LL &x,const LL &y){return x>y?x:y;}

int main()
{
    n=read();
    f[k=0][0]=read();
    f[0][1]=f[0][2]=-(1ll<<60);
    for(int i=1;i<n;i++,k^=1)
    {
        opt=readopt();num=read();
        if(opt=='+')
        {
            f[k^1][0]=mymax(mymax(f[k][0],f[k][1]),f[k][2])+num;  //原地转移 或 拆1/2个括号
            f[k^1][1]=mymax(f[k][1],f[k][2])-num;  //原地转移 或 拆1个括号
            f[k^1][2]=f[k][2]+num;  //原地转移
        }
        else
        {
            f[k^1][0]=mymax(mymax(f[k][0],f[k][1]),f[k][2])-num;  //原地转移 或 拆1/2个括号
            f[k^1][1]=mymax(mymax(f[k][1],f[k][2])+num,f[k][0]-num);  //原地转移 或 拆1个括号 或 添1个括号
            f[k^1][1]=mymax(mymax(f[k][1]-num,f[k][2]-num),f[k^1][1]);  //拆1/2个括号又添1个括号
            f[k^1][2]=mymax(f[k][2]-num,f[k][1]+num);  //原地转移 或 添1个括号
            f[k^1][2]=mymax(f[k][2]+num,f[k^1][2]);  //拆1个括号又添1个括号
        }
    }
    LL ans=mymax(mymax(f[k][0],f[k][1]),f[k][2]);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Missa (赞：2)

纪念一下第一道独立做出的思维紫题，来写个题解。

%lation，第一个做出这道题，并提示我们“要观察第三个样例”。

> 第二题一点都不难，我看到样例三就当场想到正解了。
>
>——[$\color{black}{l}\color{red}{ation}$](https://www.luogu.com.cn/user/382274)

------------

看到括号，我先想的是 dp。然而数据范围并不允许。观察数据范围，我们需要的是 $O(n \log n)$ 或 $O(n)$ 的算法。这启示我们往二分或贪心想。

先列几个括号的性质：左括号一定加在负号后面（放在加号后面等于没加）、右括号一定在负号前面。有了这几条，再找找最大值有什么性质。

听磊神的，来研究一下第三个样例。

$$1-(20-(13+14)-5)=13$$

看不出什么，拆开看看。

$$1-20+13+14+5=13$$

后面的符号都变成了加号。

一个括号内一定是诸如 `-(a -b +c +d -e +f)` 的样子，现在我们只要让括号中的负数最多。这比较容易做到，以负数为分界线，把一个负数与它后面的正数放在一起，即可让那些正数也变成负数。

`-(a -b +c +d -e +f) -> -(a - (b+c+d) - (e+f))`

即可最大化括号中负数的个数。从括号中的第一个负号开始，后面的所有数字均可转为负号，即对最后的和有正贡献。只需枚举第一个括号的位置，就一定不会错过最优解。

注意事项：

- 一定要与没有加括号的情况取最大值（会挂在 `alladd` 上）
- 前缀和弄清楚每个到底是什么，绝对值和还是带符号和

code:

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define LL long long
using namespace std;
const int M = 100005;
int a[M], p[M], n, op[M], cnt; LL maxx, s1[M], s2[M]; char c;
//s1: 带符号前缀和 s2: 绝对值前缀和
signed main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        if(i != 1) scanf("  %c", &c);
        else c  = '+';
        op[i] = c == '+' ? 1 : -1;
        scanf("%d", &a[i]); if(op[i] == -1) p[++cnt] = i;
        s1[i] = s1[i-1] + 1ll * a[i] * op[i]; s2[i] = s2[i-1] + 1ll * abs(a[i]);
    }
    p[cnt+1] = n+1;
    for(int i = 1; i <= cnt; i++){
        int pl = p[i], pl2 = p[i+1]; 
        LL ans = s1[pl-1] - (s2[pl2-1] - s2[pl-1]) + s2[n] - s2[pl2-1];
        //s1[pl-1] 是枚举到的括号的前面部分，s2[pl2-1] - s2[pl-1] 是枚举到的括号与括号后第一个减号中间的部分的贡献，s2[n] - s2[pl2-1] 是最后一段的贡献
        maxx = max(maxx, ans);
    }
    printf("%lld\n", max(maxx, s1[n])); 
}
```

---

## 作者：81179332_ (赞：2)

左括号一定在减号之后，加在加号后面又不会变号并没有什么用。

假设我们先在有了确定了一个左括号的位置，那么它右边紧邻着的一段加号一定会变成减号。

在它右边第一个减号后，所有数都可以通过加括号变成绝对值。

枚举第一个左括号位置，维护前缀和和后缀绝对值和计算答案。

```cpp
const int N = 100010;
ll ans,res;
ll a[N],pre[N],suf[N],tot;
int n,op[N];
int main()
{
	n = read();
	for(int i = 1;i < n;i++)
	{
		tot += (a[i] = read());
		char ch = getchar();while(ch != '+' && ch != '-') ch = getchar();
		op[i] = (ch == '+') ? 1 : -1;
	}tot += (a[n] = read());
	for(int i = n;i;i--) { suf[i] = a[i];if(~op[i]) suf[i] += suf[i + 1]; }
	for(int i = 1;i <= n;i++) pre[i] = pre[i - 1] + a[i];
	res = a[1];ans = -LINF;
	for(int i = 2;i <= n;i++)
	{
		if(op[i - 1] == -1) ans = max(ans,res + pre[n] - pre[i - 1] - 2 * suf[i]);
		res += a[i] * op[i - 1];
	}ans = max(ans,res);fprint(ans);
    return 0;
}
```

---

## 作者：orz_z (赞：1)





性质：
1. 括号都用在减号后。
2. 减号后加括号除了这个减号和下一个减号之间的数减去，后面所有数都可加上绝对值，显然这个括号最优是右括号放在最后。

故枚举加括号的位置，前缀和优化即可。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE = 1 << 23;
	char buf[SIZE], *S, *T;
	inline char getchar() {
		if (S == T) {
			T = (S = buf) + fread(buf, 1, SIZE, stdin);
			if (S == T)
				return '\n';
		}
		return *S++;
	}
}

namespace Fwrite {
	const int SIZE = 1 << 23;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush() {
		fwrite(buf, 1, S - buf, stdout);
		S = buf;
	}
	inline void putchar(char c) {
		*S++ = c;
		if (S == T)
			flush();
	}
	struct NTR {
		~NTR() {
			flush();
		}
	} ztr;
}

#ifdef ONLINE_JUDGE
	#define getchar Fread::getchar
	#define putchar Fwrite::putchar
#endif

#define int long long

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 1e5 + 10;

int n, a, k, b[_], s[_], ss[_];

signed main() {
	n = read();
	b[1] = 0;
	for (int i = 1; i <= n; ++i) {
		if (i != 1) {
			char c = getchar();
			while (c != '+' && c != '-') c = getchar();
			if (c == '-') b[i] = 1, k++;
		}
		a = read();
		if (b[i] == 1) a = -a;
		s[i] = s[i - 1] + a;
		ss[i] = ss[i - 1] + abs(a);
	}
	int lst = n + 1;
	for (int i = 1; i <= n; ++i)
		if (b[i] == 1) {
			lst = i;
			break;
		}
	if (lst == n + 1 || k == 1)
		return printf("%lld", s[n]), 0;
	int ans = s[n];
	for (int i = lst + 1; i <= n; ++i)
		if (b[i] == 1)
			ans = max(ans, s[lst - 1] - (ss[i - 1] - ss[lst - 1]) + ss[n] - ss[i - 1]), lst = i;
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：KokiNiwa (赞：1)

### 题目叙述
给定长度为 $n$ 的算式，现在可以任意添加加减符号，问算式取值最大多少。

### 题解
首先加法前面添加括号毫无意义。其次如果连套三层括号不如把前两层在某个地方结束了，变成一层符号也不变。

所以可以设 $f_{i,j}$ 表示前 $i$ 个数，已经套了 $j$ 层括号的最大价值。每次讨论前一个数套了多少个括号，这两个数之间是))(还是)(还是什么情况，这样转移即可。注意不要漏)(这样的转移，从 $f_{i-1,0}$ 到 $f_{i,0}$ 的转移。

### 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long LL;
const int CN=1e5+5;
int val[CN];
char op[CN];
char get_not_space(){
	char ret=getchar();
	while(ret==' ')ret=getchar();
	return ret;
}
const LL inf=1e18;
LL f[CN][3];
int N;
bool chkmax(LL &x,const LL &y){return (x<y)?(x=y,1):0;}
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&N);
	op[1]='+';
	for(int i=1;i<=N;++i){
		if(i!=1)op[i]=get_not_space();
		scanf("%d",&val[i]);
		if(op[i]=='-')val[i]=-val[i];
	}
	f[1][0]=val[1];
	f[1][1]=f[1][2]=-inf;
	for(int i=2;i<=N;++i)f[i][0]=f[i][1]=f[i][2]=-inf;
	for(int i=2;i<=N;++i){
		f[i][0]=max(f[i-1][0],max(f[i-1][1],f[i-1][2]))+val[i];
		if(op[i]=='-'){
			chkmax(f[i][1],f[i-1][0]+val[i]); // i-1(i
			chkmax(f[i][1],f[i-1][1]+val[i]); // i-1)(i
			chkmax(f[i][1],f[i-1][1]-val[i]); // i-1,i
			chkmax(f[i][1],f[i-1][2]-val[i]); // i-1)i
			chkmax(f[i][1],f[i-1][2]+val[i]); // i-1)(i

			chkmax(f[i][2],f[i-1][1]-val[i]); // i-1(i
			chkmax(f[i][2],f[i-1][2]-val[i]); // i-1)(i
			chkmax(f[i][2],f[i-1][2]+val[i]); // i-1,i
		}else{
			chkmax(f[i][1],f[i-1][1]-val[i]); // i-1,i
			chkmax(f[i][1],f[i-1][2]-val[i]); // i-1)i
			chkmax(f[i][2],f[i-1][2]+val[i]); // i-1,i
		}
	}
	// for(int i=1;i<=N;++i)cerr<<f[i][0]<<" "<<f[i][1]<<" "<<f[i][2]<<endl;
	printf("%lld\n",max(f[N][0],max(f[N][1],f[N][2])));
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：奇卡 (赞：1)

首先在加号前填括号无意义，最多只能有两重括号嵌套

于是最优解必然是这个形式：

$A-((a_1+a_2+...+a_k)-(b_1+b_2+...+b_k)-(...)-...)+B$

其中$A$为不含括号的式子，$B$为只含加号的式子

$B$只含加号好理解，关键是理解$A$不含括号（即一个式子中最外层括号只能有一对）

如果$A$中有一对括号，那把这对括号的右半边括号打到$B$前面就可以少减一个$a_1+a_2+...+a_k$，显然更优

枚举一下最外层括号的左半边的位置就行了

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
using namespace std;

ll f[N],g[N],a[N];
char op,lst;

int main(){
    int n,x,y=0,i,cnt=0;
    cin>>n;
    ll ans=0;
    for(i=1;i<=n;++i){
        cin>>x;lst=op;
        if(i<n) cin>>op;
        if(lst=='-'){
            x=-x;
            a[++cnt]=x;
        }
        if(y<=0 && x>0) cnt++,a[cnt]=x;
        if(y>0 && x>0) a[cnt]+=x;
        y=x;
    } f[1]=a[1];
    for(i=cnt;i>=1;--i) g[i]=g[i+1]+abs(a[i]);
    for(i=2;i<=cnt;++i) f[i]=f[i-1]+a[i];
    ans=f[cnt];
    for(i=1;i<cnt;++i)
        if(a[i+1]<0) ans=max(ans,f[i+1]-a[i+2]+g[i+3]);
 	cout<<ans; 
} 
```



---

