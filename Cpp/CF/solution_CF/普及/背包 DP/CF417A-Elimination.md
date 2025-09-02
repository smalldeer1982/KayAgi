# Elimination

## 题目描述

The finalists of the "Russian Code Cup" competition in 2214 will be the participants who win in one of the elimination rounds.

The elimination rounds are divided into main and additional. Each of the main elimination rounds consists of $ c $ problems, the winners of the round are the first $ n $ people in the rating list. Each of the additional elimination rounds consists of $ d $ problems. The winner of the additional round is one person. Besides, $ k $ winners of the past finals are invited to the finals without elimination.

As a result of all elimination rounds at least $ n·m $ people should go to the finals. You need to organize elimination rounds in such a way, that at least $ n·m $ people go to the finals, and the total amount of used problems in all rounds is as small as possible.

## 样例 #1

### 输入

```
1 10
7 2
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2
2 1
2
```

### 输出

```
0
```

# 题解

## 作者：Fengxiang008 (赞：12)

### 算法分析：

这是一道背包题。

### 题意理解：

1. 需要 $n \times m$ 个选手进入比赛，有 $k$ 人保送。

2. 淘汰赛分两种比赛。

3. 正常赛，选拔 $n$ 人，需要 $c$ 道题目。

4. 特殊赛，选拔 $1$ 人，需要 $d$ 道题目。

目标：**最少** 需要多少道题目。

### 解题思路：

1. 只需要选拔 $n\times m - k$ 人。

2. 把两种比赛视为背包问题中的两种物品。

3. $dp_i$ 表示选拔不超过 $i$ 人最少题目数量。

4. 背包的容量：人。

5. 物品的重量：比赛选拔的人数；物品的价值：比赛的题数。


### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,c,d,w[5],dp[10205],val[5];
int main()
{
	cin>>c>>d>>n>>m>>k;//c,d 需要的题目数量，n*m个人，k保送的人数
	w[1]=n; //正常赛 
	val[1]=c;
	w[2]=1;//特殊赛 
	val[2]=d;
	for(int i=1;i<=10200;i++)
		dp[i]=1e9;
	dp[0]=0;//选拔 0 个人，最少0道题目
	for(int i=1;i<=2;i++)//2种物品,即普通赛和特殊赛。
		for(int j=w[i];j<=10200;j++)
			dp[j]=min(dp[j],dp[j-w[i]]+val[i]);
	int ans=1e9;
	for(int i=n*m-k;i<=10200;i++)//取最小值
		ans=min(ans,dp[i]);
	cout<<ans<<endl; 
	return 0; 
}
```


---

## 作者：daiarineko (赞：7)

## 0. 题意简述

有两种比赛，第一种能晋级 $n$ 人，需要 $c$ 道题，第二种只能晋级 $1$ 人，需要 $d$ 道题。同时，初始有 $k$ 人保送。请问当至少需要晋级 $n\cdot m$ 人的情况下，至少需要几道题？

## 1. 题目分析&主要代码

考察点：DP

题目难度：普及/提高-

时间复杂度：$\Theta(nm)$

### 题目分析

使用动态规划来求解。

很明显，对于任何目标人数 $i$，我们都可以有两个方式得到：
![](https://cdn.luogu.com.cn/upload/image_hosting/fvuqsl8s.png)
即可以通过第一种比赛使用 $c$ 道题来得到这个价值——$f_{i-n}+c$

也可以通过第二种比赛使用 $d$ 道题来得到这个价值——$f_{i-1}+d$

而我们为了保证题目数最少，肯定会选择两种方案的最小值，即 $\min({f_{i-n}+c},{f_{i-1}+d})$。

最后，题目**不是要求必须晋级 $n\cdot m$ 人，而是要求至少晋级 $n\cdot m$ 人，** 所以输出的时候还要找一遍 $f_{nm} \sim f_{nm-k}$ 的最小值！

### 主要代码

价值遍历顺序：$0\sim nm$。

边界：$0$ 人时需要 $0$ 道题。

循环：
```cpp
register int j=n*m;
f[0]=0;//可选，除非f数组定义在函数内
for(register int i=1;i<=j;++i){
    f[i]=min((i-n>-1)?(f[i-n]+c):32767,f[i-1]+d);//秉着不浪费一点时间/空间的原则，使用三元运算符来避免一个if（其实没啥用）
}
```

取最大值：
```cpp
register int mx=f[j-k];//使用上文的j
for(int i=j-k+1;i<=j;++i) mn=min(mn,f[i]);
```

## 2. 完整代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
int c,d,n,m,k,f[10001];
int main(){
    ios::sync_with_stdio(false);
    cin>>c>>d>>n>>m>>k;
    register int j=n*m;
    f[0]=0;
    for(register int i=1;i<=j;++i){
        f[i]=min((i-n>-1)?(f[i-n]+c):32767,f[i-1]+d);
    }
    register int mn=f[j-k];
    for(int i=j-k+1;i<=j;++i) mn=min(mn,f[i]);
    cout<<mn<<endl;
    return 0;
}

```
## 3. ~~出题人挖坑不埋~~

1. 题目要求**至少**多少道题，所以需要min而不是max，同时三元运算符的否则部分使用的数是**极大数而不是极小数**！
2. 先用c，再用d！~~（因为这个我调了半天代码）~~

## 4. 结尾
这是本蒟蒻的第四篇题解，也是第一篇黄题题解，给个赞再走吧！

###### ~~我绝对不会告诉你我是为了弄点咕值~~

---

## 作者：Zzzzzzzm (赞：6)

### ~~本题是个相当水的黄题~~
首先，我们可以明确的是这道题其实完全不用暴力或者$dp$。看到别的大佬都写的$dp$，讲一个更为**简单**的思路。

这道题我们可以发现简化一下题意，现在他需要$n×m$个人晋级，有$k$个人是内定的黑幕，所以我们只需要让$n×m-k$个人晋级就好了，我们设他为$ans$。

现在$ans$有两种达到的方法，一种是每次晋级一个人，需要出$d$道题，一种是每次晋级$n$个人，需要出$c$道题。我们可以计算两种晋级方式道效率，设特殊赛的效率为$f1$，正常赛为$f2$。效率在此处指一道题的晋级人数

### 接下来很两种情况讨论

- 若$f1≥f2$，很明显我们每次都出$d$道题让一个人晋级是最优的。

- 若$f1<f2$，我们每次就选择尽量多的$c$道题晋级$d$人的方法，直到再选一个人就会让人数多于需要的$ans$人了。剩下的人数在设为$tot$，比较$tot×d$与$c$的大小关系确定是用一个一个补还是出$c$道题晋级$n$人。

此外，值得注意的是如果$k$已经大于等于人数$n×m$了，即$ans≤0$，这直接输出$0$即可。

---

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int c, d, n, m, k, ans;

template<typename T>											//快读 
inline void read(T&x){
	x = 0; char q; bool f = 1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1)+(x<<3)+(q^48);
		q = getchar();
	}
	x = f?x:-x;
}

template<typename T>											//快写 
inline void write(T x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)	write(x/10);
	putchar(x%10+'0');
}

int main(){
	read(c), read(d), read(n), read(m), read(k);				//简单的输入 
	ans = n*m-k;
	if(ans <= 0){												//特判一下如果不需要出题的情况 
		putchar('0');
		return 0;
	}
	double f1 = (double)n/c, f2 = (double)1/d;					//记录下效率高低 
	if(f1 > f2){												//如果正常赛效率高 
		int num = ans-ans/n*n;									//记录ans/n轮之后剩余的人数 
		if(num*d < c)	write(ans/n*c+num*d);
		else	write(ans/n*c+c);
		return 0;
	}
	if(f1 <= f2)	write(ans*d);								//如果特殊赛效率高直接让 ans*d 
	return 0;
}
```


---

## 作者：WanderingTrader (赞：3)

读懂题目以后思路就很容易想了，显然是完全背包问题。  
### 题目分析
有两个物品，一个物品重量为$n$，价值为$c$，另一个物品重量为$1$，价值为$d$（对应两种比赛）。  
我们的包大小为$n\times m$，要求使用大小在$[n\times m-k,n\times m]$的空间中，价值 **最小** 为多少。  
### 代码
初始化：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define N 10005
#define INF 1e8
int dp[N],C;
int main()
{
	int c,d,n,m,k;
	scanf("%d%d%d%d%d",&c,&d,&n,&m,&k);
	C = n*m;
	for(int i = 1;i <= C;++i)
		dp[i] = INF;
	return 0;
}
```  
注意由于我们要求的是完全背包的最小值，所以初始化设成正的INF。

然后我们分别对两个物品进行完全背包。为了方便我们封装函数：
```cpp
void bbINF(int v,int w)
{
	for(int i = w;i <= C;++i)
		dp[i] = min(dp[i],dp[i-w]+v);
}
```
这份代码是不是很熟悉？没错，就是完全背包的板子，它的功能是对一个 **重量为w，价值为v** 的物品做了一次完全背包。  
那么做两次完全背包即可：
```cpp
bbINF(c,n);
bbINF(d,1);
```
参数不要传反了。（本人因为这个错了好多次）

那么我们在规定区间内取最小值即可：
```cpp
int ans = INF;
for(int i = C-k;i <= C;++i)
	ans = min(ans,dp[i]);
printf("%d\n",ans);
```
这样就好了。  

全部代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define N 10005
#define INF 1e8
int dp[N],C;
void bbINF(int v,int w)
{
	for(int i = w;i <= C;++i)
		dp[i] = min(dp[i],dp[i-w]+v);
}
int main()
{
	int c,d,n,m,k;
	scanf("%d%d%d%d%d",&c,&d,&n,&m,&k);
	C = n*m;
	for(int i = 1;i <= C;++i)
		dp[i] = INF;
	bbINF(c,n);
	bbINF(d,1);
	int ans = INF;
	for(int i = C-k;i <= C;++i)
		ans = min(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
```
$$\mathrm{The\ End.}$$

---

## 作者：SSHhh (赞：3)

这道题真心是特别特别水的，就一 n=2 的完全背包。

我们分析一下题意(我当初看了三遍居然把题都没看懂QAQ)：就是有两种比赛，第一种花费 c 道题，晋级 n 个人，第二种花费 d 道题，晋级 1 个人；并且可以直接晋级的人数<=k。那么想都不用想，直接转移就行了：dp[i]=min(dp[i],dp[i-n]+c){i>=n};  dp[i]=min(dp[i],dp[i-1]+d);

唯一的问题是，可以直接晋级的人数<=k，从 n·m-k~n·m 枚举答案就完了。剩下的具体实现应该没有任何难度吧。。。
```cpp
#include<iostream>
#include<string.h>
using namespace std;
int c,d,n,m,k,ans=99999999,dp[10005];
int main()
{
	memset(dp,12,sizeof(dp));	//乱搞的初始化最大值(居然过了)
	cin>>c>>d>>n>>m>>k;
	dp[0]=0;
	for(int i=1;i<=n*m;i++)
	{
		if(i>=n)/*避免数组越界*/	dp[i]=min(dp[i],dp[i-n]+c);	
		dp[i]=min(dp[i],dp[i-1]+d);
	}
	for(int i=n*m-k;i<=n*m;i++)	//这个细节一定要记住
		ans=min(ans,dp[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：cyhtxdy (赞：1)

发一遍和所有题解设计的状态都不同的题解。


------------


读完题目可以发现，此题就是**完全背包问题**的变形。

直接设 $f_i$ 为有 $i$ 道题时可以进入决赛的最大人数，那么套用完全背包问题的模板可以得到状态转移方程： $f_j = \max (f_j, f_{j - w_i} + d_i)$。

仅有两种物品：一种物品价值为 $n$，体积为 $c$；另一种物品价值为 $1$，体积为 $d$。

最终判断能得到价值超过 $n×m-k$ 的最小体积即可。

代码如下：
```
int main () {
	w[1] = rd (), w[2] = rd ();//体积
	n = rd (), m = rd ();
	k = rd ();
	d[1] = n, d[2] = 1;//价值
	
	for (int i = 1; i <= 2; i ++) {
		for (int j = w[i]; j <= 10020; j ++) {//由于总体积不知，所以设最大值10000
			f[j] = max (f[j], f[j - w[i]] + d[i]);
		}
	}
	for (int i = 0; i <= 10020; i ++) {
		if (f[i] >= n * m - k) {//能达到要求
			cout << i;
			return 0;
		}
	}
	return 0;
}
```





---

## 作者：HerikoDeltana (赞：1)

### 分析

这道题是一个完全背包的变形。

~~我一边做这些题时候，都是先看看有什么能套上的模板。~~

首先，我们设 $f_i$ 为有 i 人比赛时所需的题目。 

然后，有两个类型的比赛，因此我们可以直接分别来看，状态转移方程如下：

$$
f_i=\begin{cases}\min\{f_i,f_{i-n}+c\},\quad i \ge n\\ \min\{f_i,f_{i-1}+d\} ,\quad i \le n \times m	\end{cases}
$$

### Code

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define Romano 1
#define S signed
#define U unsigned
#define LL long long
#define R register
#define I inline
#define D double
#define LD long double
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f = 1;
    char c = getchar();
    x = 0;
    while (c < '0' || c > '9') 
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') 
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
const int mxx=1e5+5;
LL c,d,n,m,k,f[mxx],ans=114514;
S main()
{
    fr(c),fr(d),fr(n),fr(m),fr(k);mst(f,12);f[0]=0;//这个初始化卡了好久没过
    for(R LL i=1;i<=n*m;++i) {if(i>=n) f[i]=min(f[i],f[i-n]+c);f[i]=min(f[i],f[i-1]+d);}
    for(R LL i=n*m-k;i<=n*m;++i) ans=min(ans,f[i]);
    fw(ans);
    Heriko Deltana;
}

```
最后小声嘀咕一句：这题面翻译的最后实际上是 n\*m 。


---

## 作者：AC自动机 (赞：1)

### 思路
这题可以说是非常水了，转化一下题意，可以看出，是一个裸的完全背包问题，要求至少选出n*m-k个人，而物体总共有2种，一种是普通比赛，w为n，v为c，另一种为附加赛，w为1，v为d，所以直接完全背包就可以了=￣ω￣=

#### 一个小细节
没有严格要求选n*m-k个人，所以选的人数大于等于n*m-k即可，所以最后出答案的时候要把dp数组扫一遍。

#### 附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[10050];
int v[5];
int w[5];
int main(){
	for(register int i=0;i<=10049;i++){
		dp[i]=99999999;
	}
	int c,d;
	int n,m;
	int k;
	cin>>c>>d;
	cin>>n>>m;
	cin>>k;
	dp[0]=0; w[1]=n; w[2]=1; v[1]=c; v[2]=d;
	for(register int i=1;i<=2;i++){
		for(register int j=w[i];j<=10049;j++){
			dp[j]=min(dp[j],dp[j-w[i]]+v[i]);
		}
	}
	int ans=99999999;
	for(register int i=m*n-k;i<=10049;i++){
		ans=min(dp[i],ans);
	}
	cout<<ans<<endl;
}
```

---

## 作者：龙啸空 (赞：0)

```

```
# 这是一道DP水题

用$dp[i]$来表示在有i人时题目要多少

因为有两个比赛，在进行转移时取两种状态最小值

dp方程为：

$$dp[i] = min(dp[i - N] + C,dp[i - 1] + D);$$

看了楼下的题解，其实好像不用判i>=n的情况,直接对两种状态取$min$,最后从$ N * M - K$到$ N * M$取最小的dp答案（防止dalao内幕）

AC代码：

```

#include<cstdio>
using namespace std;
int C,D,N,M,K;
int dp[1000005];
template<typename T>
T min(const T& a,const T& b){
	if(a < b){
		return a;
	}
	return b;
}
int main(){
	scanf("%d%d%d%d%d",&C,&D,&N,&M,&K);
	dp[0] = 0;
	for(int i = 1;i<=N*M;i++){
		dp[i] = min(dp[i - N] + C,dp[i - 1] + D);
	}
	int ans = 2147483647;
	for(int i = N * M - K; i <= N * M; i++){
		ans = min(ans,dp[i]);
	}
	printf("%d",ans);
	return 0;
}

```


---

