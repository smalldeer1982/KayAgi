# [USACO17FEB] Why Did the Cow Cross the Road II G

## 题目背景

*本题与 [白金组同名题目](/problem/P3657) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 饲养了 $N$ 种奶牛，编号从 $1$ 到 $N$。一些品种的奶牛和其他奶牛间相处良好，事实证明，如果两个品种的奶牛编号分别为 $a,b$，当 $|a-b| \leq 4$ 时，这两个品种的奶牛能友好相处，否则不能友好相处。

一条长长的道路贯穿整个农场，道路的左侧有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场），道路的右侧也有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场）。为了让奶牛们安全穿过马路，Farmer John 希望能在马路上画出一些人行道（牛行道？），要求这些人行道满足如下条件：

1. 人行道从左侧的某个牧场出发，连接到右侧的某个牧场；
2. 人行道连接的两个牧场的奶牛要能友好相处；
3. 人行道不能在道路中间相交；
4. 每个牧场只能与一条人行道相连。

你需要帮 FJ 求出最多能有多少条人行道。

## 样例 #1

### 输入

```
6
1
2
3
4
5
6
6
5
4
3
2
1```

### 输出

```
5```

# 题解

## 作者：张心博harry (赞：18)

### 我向来是遇到动规就懵逼的那种人......

[题目传送门](https://www.luogu.com.cn/problem/P6119)

------------

### 大体思路：

拿到一道动态规划题目怎么办？

~~坦然逝去。~~

当然是去推状态转移方程啦！

#### 怎么推？

如果你不愿意看，可以直接去看状态转移方程。

一般我会用一个名为 $f$ 的数组去推导（我想这也是大多数人的嗜好）。

我们把 $f_{i,j}$ 设为取序列 $a$ 的前 $i$ 项，序列 $b$ 的前 $j$ 项的最长公共子序列（ $LCS$ ），那么状态转移方程就是：
$$f_{i,j}=\begin{cases}\max(f_{i-1,j},f_{i,j-1})\\f_{i-1,j-1}+1(|a-b| \leq 4) \end{cases}$$

当然，你也可以设为设为取序列 $a$ 的第 $i$ 项，序列 $b$ 的第 $j$ 项的最长公共子序列。但是这样做不但状态转移方程变了，而且似乎还要把 $f$ 数组初始化......

这里提一句，其实推导状态转移方程有技巧的。这里有我总结出来的两种方法：

1. 手打样例，亲手去模拟一下样例，可以发现规律。

2. 根据题目描述。有些题目甚至直接把方程打了出来，就算不是这样我们也可以根据题目给出的蛛丝马迹进行推导。

3. ~~借鉴题解，参考题解。~~

--------

### 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define forr(a,b) for(int i=a;i<=b;i++) //简化一下
#define foor(a,b) for(int j=a;j<=b;j++)
using namespace std;
int a[1001]={0},b[1001]={0};
int f[1001][1001]={0};
int main(){
	int n;
	cin>>n;
	forr(1,n) cin>>a[i];
	forr(1,n) cin>>b[i];
	forr(1,n){
		foor(1,n){
			if(abs(a[i]-b[j])<=4){ //abs取绝对值
				f[i][j]=max(f[i][j],f[i-1][j-1]+1);
			}
			else{
				f[i][j]=max(f[i-1][j],f[i][j-1]);
			}
		}
	}
	cout<<f[n][n]<<endl;
	return 0;
}
```

--------

### 总结：

注意推导状态转移方程的部分。

#### 后记：

大佬们都说这题很简单，不过我觉得对我来说还挺难的。

动态规划我学的一直都不太好，这道题目做的时候我也是参考了题解，希望这篇题解没有错误，但愿能过吧。

---

## 作者：Grow2011 (赞：12)

最近刷 DP，顺手写篇题解。

## 题目解析：

想必你们已经知道了，这道题就是 DP，但是，凡是 DP，就一定逃不开 DP 的定义和递推方程。

先看定义:${DP_{i,}}_j$ 的定义为马路左边选至第 $i$ 个农场，马路右边选至第 $j$ 个农场最多的马路数量。

那这道题的递推方程要怎么推呢？

先说结果：

$$ {dp_{i,}}_j = \left\{ \begin{aligned} &\max({dp_{i,}}_{j-1},{dp_{i-1,}}_j,{dp_{i-1,}}_{j-1}+1) & \lvert a_i-b_j\rvert\leqslant 4 \cr &\max({dp_{i,}}_{j-1},{dp_{i-1,}}_j,{dp_{i-1,}}_{j-1})& \lvert a_i-b_j\rvert>4 \end{aligned} \right. $$

哪是如何推出来的呢？

首先可以看出，${DP_{i,}}_j$ 只有两种递推状态：新增边和不新增边。

首先看不增边：因为没有增加边，所以只要选 ${DP_{i-1,}}_j$ 和 ${DP_{i,}}_{j-1}$ 中的 MAX 值就可以了。

再看增边：因为题目说了，不可以有边相交，而且一个农场只能连接 1 条路，所以转移方程也很简单，就是 ${DP_{i-1,}}_{j-1}+1$，但要注意判断当前的 $a_i$ 和 $b_i$ 之间的差有没有达到 4 以上。

知道了转移方程，就可以 DP 了，这里就不在赘述，直接附上代码。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005],dp[1005][1005];
signed main(){
    cin >> n;
    for(int i = 1;i<=n;i++)cin >> a[i];
    for(int i = 1;i<=n;i++)cin >> b[i];
    //输入 
    for(int i = 1;i<=n;i++){
    	for(int j = 1;j<=n;j++){
    		if(abs(a[i]-b[j])<=4)dp[i][j] = max(dp[i][j-1],max(dp[i-1][j],dp[i-1][j-1]+1));
    		else dp[i][j] = max(dp[i][j-1],max(dp[i-1][j],dp[i-1][j-1]));
    		//转移 
		}
	}
	cout << dp[n][n];
	//输出 
    return 0;
}
```

---

## 作者：Na2PtCl6 (赞：7)

这题放在金组里面算比较水的了
## 分析题目
如果把题面中的绝对值差 $\le 4$ 改成等于，你会怎么做？

这就是 LCS 模板诶！而且 $O(n^2)$ 的 dp 就行了！

我们设 $f(i,j)$ 为取序列 $a$ 的前 $i$ 项，序列 $b$ 的前 $j$ 项的 LCS，则 $f(i-1,j)$ 为不取 $a_i$ 这个元素时的 LCS，则 $f(i,j-1)$ 为不取 $b_j$ 这个元素的 LCS，则 $f(i-1,j-1)$ 为 $a_i$ 和 $b_j$ 都不取的 LCS，则 $f(i,j) = \lbrace$ $max\{f(i-1,j),f(i,j-1)\} \atop f(i-1,j-1)+1~(a_i=b_j)$

我们发现，都不取的情况没有提到，因为 $f(i-1,j)$ 和 $f(i,j-1)$ 一定比 $f(i-1,j-1)$ 更优或相等，所以被省略了。而 $f(i-1,j-1)+1$ 是 $a_i$ 和 $b_j$ 都取的情况，这个状态沿用了 $a_i$ 和 $b_j$ 都不取的状态，在这基础上长度加 $1$。

再改回来，这个问题就用同样的方法解决即可。

状态转移方程:  $f(i,j) = \lbrace$ $max\{f(i-1,j),f(i,j-1)\} \atop f(i-1,j-1)+1~(|a_i-b_j| \le 4)$

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1004;
int n,a[maxn],b[maxn],f[maxn][maxn];

const int _max(const int &a,const int &b){
	return a>b?a:b;
}

const int _abs(const int &k){ return k>0?k:-k;}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(_abs(a[i]-b[j])<=4)
				f[i][j]=_max(f[i][j],f[i-1][j-1]+1);
			else
				f[i][j]=_max(f[i-1][j],f[i][j-1]);
		}
	printf("%d",f[n][n]);
	return 0;
}
```

---

## 作者：qwerty12346 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/P6119)

## 题意

就是让我们求出最多能有多少条人行道。

## 思路

用一个动态规划，然后在里面判断就可以了。

## 状态定义

$dp_{i,j}$ 表示上面匹配到 $i$，下面匹配到 $j$ 的最大值。

## 状态转移方程

$dp_{i,j}=\max(dp_{i,j},dp_{i-1,j-1}+1)$

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],b[10005],f[1005][1005];//定义dp数组
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
	    if(abs(a[i]-b[j])<=4)f[i][j]=max(f[i][j],f[i-1][j-1]+1);//判断并更新
	    else f[i][j]=max(f[i-1][j],f[i][j-1]);//否则这样更新
	}
    }
    cout<<f[n][n];
    return 0;
}
```


---

## 作者：蓝莲花__ (赞：2)

### 考虑树状数组优化DP

一个O（n^2）的做法：设f(i,j)表示上面匹配到i，下面匹配到j的最大值，转移f(i,j)=max(f(i-1,j-1)+1)     (abs(a[i]-b[j])<=4)

再考虑怎么优化。枚举上面的从1到n，每次求当前为i时的最大的在范围内的f值，每次在范围内的最多只有4+4+1=9个值，用树状数组维护每种颜色的前缀最大值，转移时暴力枚举这几种颜色即可

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&-x
using namespace std;
const int N=1e5+11;
int f[N],n,m,a[N],t[N],b[N];
int ask(int x){int res=0;for(;x;x-=lowbit(x))res=max(res,t[x]);return res;}
void add(int x,int k){for(;x<=n;x+=lowbit(x))t[x]=max(t[x],k);return;}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i){int x;cin>>x;b[x]=i;}
	for(int i=1;i<=n;++i){
		int lef=max(1,a[i]-4),rig=min(n,a[i]+4);
		for(int j=lef;j<=rig;++j)f[j]=ask(b[j]-1);
		for(int j=lef;j<=rig;++j)add(b[j],f[j]+1);
	}
	cout<<ask(n);
	return 0;
} 
```


---

## 作者：Strelitzia (赞：1)

#### Why Did the Cow Cross the Road II G

$\ \ \ \ \ $[题目链接](https://www.luogu.com.cn/problem/P6119)

----------------

$\ \ \ \ \ $逛luogu时偶然翻到的一道题。

$\ \ \ \ \ $一看题目发现好长，但是题目意思确是十分明确。

$\ \ \ \ \ $给你路的两边的每个位置的编号，尽可能的连接满足条件的两边。

$\ \ \ \ \ $样例图：

![](https://cdn.luogu.com.cn/upload/image_hosting/av5hprqh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$\ \ \ \ \ $答案是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/yi0jh93u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$\ \ \ \ \ $两地的编号的差小于4才能连接。

$\ \ \ \ \ $且不能交叉。

$\ \ \ \ \ $反例：

![](https://cdn.luogu.com.cn/upload/image_hosting/wh0mesoa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$\ \ \ \ \ $这样就不行。

$\ \ \ \ \ $所以这道题可以看做改变了的LCS。

$\ \ \ \ \ $区别在于连边的条件不是相等，而是值的差$≤$4。

$\ \ \ \ \ $代码如下：


```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int a[1005],b[1005],n;
int dp[1005][1005];
int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) {
		read(a[i]);
	}
	for (int i = 1 ; i <= n ; ++ i) {
		read(b[i]);
	}
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			if (abs(a[i] - b[j]) <= 4) {		//更改了判断的条件
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max (dp[i - 1][j],dp[i][j - 1]);						//如果不满足的情况
			}
		}
	}
	print(dp[n][n]);
	return 0;
}
```

$\ \ \ \ \ $Thanks♪(･ω･)ﾉ。

---

## 作者：lianchanghua (赞：1)

感谢 @[I_like_magic](https://www.luogu.com.cn/user/778235) 帮忙修改 Markdown 和 $\LaTeX$。

#### 题目大意

有 $N$ 种奶牛，编号从 $1$ 到 $N$。假设两个品种的奶牛编号分别为 $a,b$，当 $|a-b| \leq 4$ 时，这两个品种的奶牛能友好相处，否则不能友好相处。

一条长长的道路贯穿整个农场，道路的左侧和右侧分别有 $N$ 个牧场。

为了让奶牛安全通过，所以画出了人行道，人行道满足条件有：

1. 人行道从左侧的某个牧场出发，连接到右侧的某个牧场；
2. 人行道连接的两个牧场的奶牛要能友好相处；
3. 人行道不能在道路中间相交；
4. 每个牧场只能与一条人行道相连。

最多能有多少人行道？

#### 思路

我们瞄一眼数据规模，就会发现：$1 \le N \le 1000$。如此大的数据，断然不可以爆搜，所以，我们就想到了动态规划。这时候，头疼的就来了：转移方程是什么？其实很简单，我们只要纸上模拟一下，推出规律即可。

转移方程即为：

$dp_{i,j} = \begin{cases}
   \max \{dp_{i,j},dp_{i−1,j−1}+1\}&\text{if }|a-b|\le 4\\
   \max \{dp_{i-1,j},dp_{i−1,j−1}\}&\text{if }|a-b|> 4\\
\end{cases}$

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[10005],b[10005],dp[1005][1005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
    cin>>n;
    for(int i=1;i<=n;i++)	cin>>a[i];
    for(int i=1;i<=n;i++)	cin>>b[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
	    	if(abs(a[i]-b[j])<=4)	dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
	    	else 					dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
    }
    cout<<dp[n][n];
    return 0;
}
```

---

## 作者：Hilaria (赞：0)

[link](https://www.luogu.com.cn/problem/P6119)

### 题意

给你两组长度为 $n$ 的序列，求出最多有多少对合法的配对。

判断配对合法的条件：

$1.$ 配对的两个数 $(a,b)$ 必须分别从第一组和第二组组数中选取。

$2.$ 配对的两个数的权值差要小于等于 $4$

$3.$ 假设在第一组数中选取的数的位置分别是 $a_1,a_2,a_3\dots a_k$。

在第二组数中选取的数的位置分别是 $b_1,b_2,b_3\dots b_k$。

满足 $a_1<a_2<a_3\dots <a_k$ 且 $b_1<b_2<b_3\dots <b_k$。

$4.$ 每个数最多与一个数配对。

---

### 思路

这个题很明显想让我们求出这两组数的 LCS。但是判断条件从相等变为了差值为 $4$，但是我们依然可以用动态规划 dp 来搞这个题。

而且 $n$ 的范围是 $1\le n\le 1000$，那我们 $O(n^2)$ 的时间复杂度也不慌啊。

所以设 $dp[i][j]$ 为在第一组数中前 $i$ 个数和在第二组数中前 $j$ 个数中最多有多少个合法数对。

然后我们考虑到这个 dp 的条件换了啊（就是对于模板 LCS 换了）。

那分类讨论一波啊。

我们枚举 $i,j$，对于 $dp[i][j]$ 来说，它可以分两种情况：

$1.$ $a[i]$ 和 $b[j]$ 差值小于等于 $4$，那我们可以将重量个数配对，配对的答案就应该为 $dp[i-1][j-1]+1$，所以转移方程为：

$dp[i][j]=\max(dp[i][j],dp[i-1][j-1]+1)$

$2.$ 那如果 $a[i]$ 和 $b[j]$ 差值大于 $4$，那我们不仅可以放弃第一组的数 $a[i]$，也可以放弃第二组的数 $b[j]$（我第一次做就漏了一种可能，直接挂分）。

那这种情况的转移方程为：

$dp[i][j]=\max(dp[i-1][j],dp[i][j-1])$

最后把这两种情况总结起来，就是完整的转移方程：

$dp[i][j]=\begin{cases}\max(dp[i][j],dp[i-1][j-1]+1)&\left|a[i]-b[i]\right|\le4\\\max(dp[i-1][j],dp[i][j-1])\end{cases}$

---

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX=1e3+10;

int n;
int a[MAXX];
int b[MAXX];
int dp[MAXX][MAXX];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(abs(a[i]-b[j])<=4)
			{
				dp[i][j]=max(dp[i-1][j-1]+1,dp[i][j]);
			}
			else
			{
				dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
			}
		}
	}
	printf("%d",dp[n][n]);

	return 0;
}
```


---

## 作者：BigJoker (赞：0)

# 0x00 前言

随到了加强版，就来看题了，挺水的，几行代码，前置知识：动态规划。

# 0x01 思路

十分简单，设 $dp_{i,j}$ 表示第一个牧场的前 $i$ 头和 第二个的前 $j$ 头牛匹配的最大值。

当前第 $a_i$ 和 $b_j$ 符合条件的话：

那么就是前 $(i-1)$ 头和 $(j-1)$ 匹配并且加上 $1$，还要与 $dp_{i,j-1}$ 和 $dp_{i-1,j}$ 取最大值。

否则：

$dp_{i-1,j}$ 和 $dp_{i,j-1}$ 取最大值即可。

只要时时记住数组的含义，就很好做了。

# 0x02 代码

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int N=1e3+5;
int n,dp[N][N];
struct Cow{
	int A,B;
}x[N];
int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) scanf("%d",&x[i].A);
	for(re int i=1;i<=n;i++) scanf("%d",&x[i].B);
	for(re int i=1;i<=n;i++){
		for(re int j=1;j<=n;j++){
			dp[i][j]=dp[i-1][j-1];
			if(abs(x[i].A-x[j].B)<=4) dp[i][j]++;
			dp[i][j]=max(dp[i][j],max(dp[i][j-1],dp[i-1][j]));
		}
	}
	printf("%d",dp[n][n]);
	return 0;
} 
```

---

## 作者：lytqwq (赞：0)

两排农场，可以连接左右的两个农场 $i,j $ $ (|a_i-b_j|\le4) $ 来产生 $1$ 的贡献，连接不能相交，求最大贡献。

设 $f_{i,j}$ 为第一排看了前 $i$ 个农村，第二排看了前 $j$ 个农村的最大贡献。

有状态转移方程：

$$
f_{i,j}=\max( f_{i-1,j},f_{i,j-1},f_{i-1,j-1}+[ |a_i-b_j|\le4 ] )
$$


直接递推 $O(n^2)$

发现这个 连接左右的两个农场的条件 比较牛 ，对于一个 $i$ ，最多只有 $9$ 个 $j$ 才能行，而其他的项都是取前面的值，我们可以只对于每个 **可行的连接** 求它的 $f$ ，然后就成了个二维数点的问题，树状数组维护最大值即可

时间复杂度 $O(nlogn)$

这里直接给一个~~简洁的~~ $O(nlogn)$ 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100100;
int n,a[N],b[N],wz[N],c[N],fans[N],maxn;
vector<int> to[N];
int lowbit(int x){return x&(-x);}
void update(int x,int y){for(int i=x;i<=n;i+=lowbit(i))c[i]=max(c[i],y);}
int query(int x){int ans=0;for(int i=x;i>=1;i-=lowbit(i))ans=max(ans,c[i]);return ans;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),wz[a[i]]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		for(int v=-4;v<=4;v++)if(b[i]+v>=1&&b[i]+v<=n)to[i].push_back(wz[b[i]+v]);
		sort(to[i].begin(),to[i].end());
		int len=to[i].size();
		for(int o=0;o<len;o++)fans[o]=query(to[i][o]-1)+1,maxn=max(maxn,fans[o]);
		for(int o=0;o<len;o++)update(to[i][o],fans[o]);
	}
	printf("%d\n",maxn);
}
```



---

## 作者：_edge_ (赞：0)

看着 dalao 们发了这么多优秀的题解，本蒟蒻深感无力呀。

首先看到题目，题目的意思很简单，就是说给定两个序列，这两个序列之间可以互相连边。满足 $|a_i-b_j| \le 4$ 并且不交叉，才能连边。

那么从题目开始分析，首先可以预处理一下所有可能的连边情况。

然后该怎么统计答案呢？

思考一下，怎么样可以满足不交叉呢？

假设 m 是答案，那么答案的序列是不是必须满足如下条件呢？

$a_i<a_{i+1}<a_{i+2}< \cdots <a_{m}$ 

$b_i<b_{i+1}<b_{i+2}< \cdots <b_{m}$

好，那么我们得出一个结论，所有满足 $|a_i-b_j| \le 4$ 的情况中要找出像上面那样的序列。

于是这道题目变成了一道最长上升子序列的模板了！(注意是双关键字)。

~~现在我们已经成功的把一道绿的难度变成了黄的难度。~~

那么最长上升子序列这里可以用 $O(n^2)$ 的卡过去 ~~(也许是数据太弱了)~~。

这里介绍一种 $O(n \log n)$ 的做法：

先按第一关键字来排序，排的时候如果第一关键字是等于的情况就把第二关键字按从大到小排，因为这里 $a_i < a_{i+1}$ 也就是说如果等于那么只能取一个，什么情况会只取一个呢？也就是最长上升子序列的最坏情况**最长不上升子序列**。

然后按照 $O(n \log n)$ 的最长上升子序列做法来处理一遍，然后就愉快的 AC 了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int INF=1005;
int a[INF],b[INF];
struct _node_data {
        int l,r;
} aa[INF*INF];//注意数组开 n*n 。
int n,f[INF*INF],tot;
int fzx_abs(int x) {
        return x<0 ? -x : x;
}
bool cmp(_node_data xx,_node_data yy) {
        if (xx.l!=yy.l) return xx.l<yy.l;
        else return xx.r>yy.r;//按第二关键字从大到小排序。
}
signed main()
{
        scanf("%lld",&n);
        for (int i=1; i<=n; i++) scanf("%lld",&a[i]);
        for (int i=1; i<=n; i++) scanf("%lld",&b[i]);
        for (int i=1; i<=n; i++)
                for (int j=1; j<=n; j++)
                        if (fzx_abs(a[i]-b[j])<=4) {
                                aa[++tot].l=i; aa[tot].r=j;
                                // cout<<aa[tot].l<<" "<<aa[tot].r<<endl;
                        }
        sort(aa+1,aa+1+tot,cmp);
        int len=1; f[len]=aa[1].r;
        for (int i=2; i<=tot; i++) {
                if (f[len]<aa[i].r) f[++len]=aa[i].r;
                else {
                        int l=1,r=len,ans=0;
                        while (l<=r) {
                                int Mid=(l+r)>>1;
                                if (f[Mid]>=aa[i].r) {r=Mid-1; ans=Mid;}
                                else l=Mid+1;
                        }
                        f[ans]=aa[i].r;
                }
        }
        cout<<len<<"\n";
        return 0;
}

```

**谢谢观赏！**

---

## 作者：神秘番茄厂长 (赞：0)

### 贼简单

仔细理一理不难发现，这题实际上是求两个数列的最长公共子序列$（LCS）$

并且是个裸的模板题，只是把条件从相同变成了相差不超过$4$。

用$dp[i][j]$表示$a$串前$i$个和$b$串前$j$个元素来匹配能得到的最大长度

在$a[i]$与$b[i]$满足条件时：
$$dp[i][j]=dp[i-1][i-1]+1$$

否则:
$$dp[i][j]=max(max(dp[i][j-1],dp[i-1][j]),dp[i][j])$$

代码：
```c++
#include<bits/stdc++.h>
using namespace std;

const int N=1e3+10;
int n,a[N],b[N],dp[N][N];

int main()
{
	cin>>n;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);

	for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
	{
		if(abs(a[i]-b[j])<=4)
		dp[i][j]=dp[i-1][j-1]+1;
		dp[i][j]=max(max(dp[i][j-1],dp[i-1][j]),dp[i][j]);
	}
	cout<<dp[n][n];
	return 0;
}

```

---

