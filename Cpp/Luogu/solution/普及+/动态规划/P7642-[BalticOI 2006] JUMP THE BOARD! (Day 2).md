# [BalticOI 2006] JUMP THE BOARD! (Day 2)

## 题目描述

一个 $n×n$ 的游戏板是由整数填充的，每格一个非负整数。目标是从左上角以任何合法路径跳到右下角。任何一格中的整数表示跳离该位置的步长。如果步长将推进越出游戏板，那么在那个特定的方向上的跳步是禁止的。所有的跳步必须是向右或向下。请注意，$0$ 是一个死胡同，它阻止任何进一步的进展。  
如图 $1$ 中所示的 $4×4$ 板，实圆标识起始位置，虚线圆标识目标位置。图 $2$ 展示了从起点位置到目标位置的三条合法路径，每个路径中都删除了不相关的数字。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/0ql0hhx0.png)  
你的任务是编写一个程序来确定从左上角到右下角的合法路径的数量。

## 说明/提示

#### 数据规模与约定  
- 对于 $100 \%$ 的数据， $4 \le n \le 100$。  
- 合法路径的数量可能相当大。使用 $64$ 位整数变量（C 中的 `long long int`，Pascal 中的 `Int64`）只能获得 $70 \%$ 的分数。可以保证所有的输入导致的路径数可以用不超过 $100$ 位的数字写出。

#### 题目说明  
来源于 [Baltic Olympiad in Informatics 2006](https://www.cs.helsinki.fi/group/boi2006/) 的 [Day 2:Jump](https://www.cs.helsinki.fi/group/boi2006/tasks/jump.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
4
2 3 3 1
1 2 1 3
1 2 3 1
3 1 1 0```

### 输出

```
3```

# 题解

## 作者：Naro_Ahgnay (赞：7)

## 题目大意
给定一个 $n \times n$ 的方格，只能从下或从右移动当前格子上的数那么多的步数，求出从左上角到右下角的方案数。 
## 思路
对于求方案数的题目，不难发现这是一道 dp 题。状态转移方程也非常好推。

设 $dp[i][j]$ 表示现在在第 $i$ 行第 $j$ 列时的方案数，由题意得：


 $\begin{Bmatrix}dp[i+g[i][j]][j]+=dp[i][j],i+g[i][j]≤n\\dp[i][j+g[i][j]]+=dp[i][j],j+g[i][j]≤n\end{Bmatrix}$


其中边界为 $dp[1][1]=1$,答案为 $dp[n][n]$。

但是，我们发现题目的数据范围极大，不得不用高精度。

于是——人生苦短，我用 python!

## code
```python
dp=[]
g=[]
for i in range(0,110):
    dp.append([])
    g.append([])
    for j in range(0,110):
        dp[i].append(0)
n=int(input())
for i in range(1,n+1):
    g[i]=input().split()
    g[i].append(int(g[i][n-1]))
    for j in range(n-1,0,-1):
        g[i][j]=int(g[i][j-1])
    
dp[1][1]=1
g[n][n]=1
for i in range(1,n+1):
    for j in range(1,n+1):
        if(i+g[i][j]<=n):
            dp[i+g[i][j]][j]+=dp[i][j]
        if(j+g[i][j]<=n):
            dp[i][j+g[i][j]]+=dp[i][j]
print(dp[n][n])
```


---

## 作者：Unordered_OIer (赞：4)

# P7642 题解
## Description
给定一张 $n \times n$ 的地图 $g$，每次只能向右或者向下移动，移动的格子数为当前格子里的数值，求有多少种路径能从 $(1,1)$ 到达 $(n,n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0ql0hhx0.png)

## Solution

水题一道，但还是从 $0$ 讲起吧。



### 70 pts

很常见的一种解法：dp。

设走到 $(i,j)$ 的方案数为 $f[i][j]$。

因为不确定上一步从哪来，所以可以考虑从 $(i,j)$ 推下一个位置，即：

$$\begin{cases}f[i+g[i][j]][j]=\sum f[i][j]\\f[i][j+g[i][j]]=\sum f[i][j]\end{cases}$$

这样做，复杂度就是 $\mathcal O(n^2)$，本题数据极小 $n \leq 100$，所以时间很稳。

### code

```cpp
namespace GG{
	ll n,g[N][N],f[N][N];
	int main(){
		n=read();
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++)
				g[i][j]=read();
		g[n][n]=1;
		f[1][1]=1;
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++){
//				if(i+g[i][j]==n&&j+g[i][j]==n)printf("%lld %lld\n",i,j);
				if(i+g[i][j]<=n)f[i+g[i][j]][j]+=f[i][j];
				if(j+g[i][j]<=n)f[i][j+g[i][j]]+=f[i][j];
			}
//		for(ll i=1;i<=n;i++,puts(""))
//			for(ll j=1;j<=n;j++)printf("%lld ",f[i][j]);
		writeln(f[n][n]);
		return 0;
	}
}
```



注意到题目里有一句话：

> 合法路径的数量可能相当大。使用 $64$ 位整数变量（C 中的 `long long int`，Pascal 中的 `Int64`）只能获得 $70 \%$ 的分数。可以保证所有的输入导致的路径数可以用不超过 $100$ 位的数字写出。


### 100pts

老老实实的用高精度实现 $\text{75 pts}$ 的算法！

### code

```cpp
#define p *this
const ll MAX_SIZE=105;
struct Huge{
	static const ll pot=9;
	static const ll mod=1e9;

	ll s[MAX_SIZE>>2],len;
	bool flag;

	Huge(){
		memset(s,0,sizeof(s));
		flag=1;len=1;
	}

	inline void init(){
		memset(s,0,sizeof(s));
		flag=1;len=1;
	}

	Huge operator = (int x){flag=(x>=0?1:0);x=abs(x);s[2]=x/mod;s[1]=x%mod;return p;}
	Huge operator = (string num){
        ll l=num.size(),ed;
        init();len=0;
        if(num[0]=='-')flag=0,ed=1;
        else flag=1,ed=0;
        for(ll i=l-1;i>=ed;i-=pot){
            ++len;
            ll w=1;
            for(ll j=i;j>i-pot&&j>=ed;j--){
            	s[len]+=(num[j]^48)*w;
            	w=(w<<3)+(w<<1);
            }
        }
        return p;
    }

	Huge operator + (Huge a){
		if(flag^a.flag)return a.flag^=1,(p-a);
		Huge c;
		c.len=max(len,a.len);
		c.flag=flag;
		for(ll i=1;i<=c.len;i++){
			c.s[i]+=s[i]+a.s[i];
			if(c.s[i]>=mod){
				c.s[i]-=mod;
				c.s[i+1]++;
			}
		}
		if(c.s[c.len+1])c.len++;
		return c;
	}

	Huge operator += (Huge a){
		p=p+a;
		return p;
	}
	Huge operator /= (Huge a){
		p=p/a;
		return p;
	}

};


ostream& operator << (ostream &out,const Huge &a){
	if(!a.flag)putchar('-');
	printf("%lld",a.s[a.len]);
	for(ll i=a.len-1;i>=1;i--)printf("%09lld",a.s[i]);
	return out;
}
namespace GG{
	ll n,g[N][N];
	Huge f[N][N];
	int main(){
		n=read();
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++)
				g[i][j]=read();
		g[n][n]=1;
		f[1][1]=1;
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++){
//				if(i+g[i][j]==n&&j+g[i][j]==n)printf("%lld %lld\n",i,j);
				if(i+g[i][j]<=n)f[i+g[i][j]][j]+=f[i][j];
				if(j+g[i][j]<=n)f[i][j+g[i][j]]+=f[i][j];
			}
//		for(ll i=1;i<=n;i++,puts(""))
//			for(ll j=1;j<=n;j++)printf("%lld ",f[i][j]);
		cout<<f[n][n]<<endl;
		return 0;
	}
}
```

嗯，这就结束了，可以看到这题还是挺水的，加个高精度而已（



---

## 作者：linyinuo2008 (赞：3)

这是一道较为入门的计数 $\text{DP}$ 题。

首先，我们可以明白每处于一个格子，我们有两种走法：往下走或往右走。所以我们可以明白（有点类似于小奥中的跳台阶问题）它的下一步可以继承它的所有方法数。所以状态装壹方城就很好理解了：

设 $f_{i,j}$ 为走到第 $i$ 行第 $j$ 列的方法数，则

$$f_{i+a_{i,j},j}\leftarrow f_{i+a_{i,j},j}+f_{i,j}$$

$$f_{i,j+a_{i,j}}\leftarrow f_{i,j+a_{i,j}}+f_{i,j}$$

前提是不超出格，还要特判 $a_{i,j}=0$ 的情况。

**注：本题数据范围较大，应使用高精（仅需支持加法和输出）。**

上代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=105;

int n,a[N][N];

struct Bigint
{
	int x[105];
	Bigint()
	{
		memset(x, 0, sizeof(x));
		x[0] = 1;
	}
	void print()
	{
		for (int i = x[0]; i >= 1; i--)
		{
			cout << x[i];
		}
		cout << endl;
	}
	Bigint operator+(const Bigint &B) const
	{
		Bigint c;
		c.x[0] = max(x[0], B.x[0]);
		for (int i = 1; i <= c.x[0]; i++)
			c.x[i] = x[i] + B.x[i];
		for (int i = 1; i <= c.x[0]; i++)
		{
			c.x[i + 1] += c.x[i] / 10;
			c.x[i] %= 10;
		}
		if (c.x[c.x[0] + 1] > 0) c.x[0]++;
		return c;
	}
}f[N][N];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	f[1][1].x[1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(!a[i][j]) continue;
			if(i+a[i][j]<=n) f[i+a[i][j]][j]=f[i+a[i][j]][j]+f[i][j];
			if(j+a[i][j]<=n) f[i][j+a[i][j]]=f[i][j+a[i][j]]+f[i][j];
		}
	f[n][n].print();
	return 0;
}
```

**虎年第一篇题解若有错误，欢迎指出！**


---

## 作者：Danno0v0 (赞：2)

这道题难其实难在高精（

过河卒的改版。

过河卒对于格子 $i,j$ 都可以更新 $i+1,j$ 和 $i,j+1$ 的值。

那么对于这道题，每个格子 $i,j$ 可以更新 $i+num_{i,j},j$ 和 $i,j+num_{i,j}$ 。

然后稍微值得注意的是 $num_{i,j}=0$ 的时候不要更新，否则会被更新三次。

然后另一个需要注意的就是要用高精了。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n,mmp[103][103];
int dp[103][103][101];
int length[103][103];
void add(int x1,int y1,int x2,int y2)
{
	int len=max(length[x1][y1],length[x2][y2]);
	for(int i=1;i<=len;i++)
	{
		dp[x1][y1][i]+=dp[x2][y2][i];
		dp[x1][y1][i+1]+=(dp[x1][y1][i])/10;
		dp[x1][y1][i]%=10;
	}
	int s=100;
	while(!dp[x1][y1][s]) s--;
	length[x1][y1]=s;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
        	cin>>mmp[i][j];
        }
    }
    dp[1][1][1]=1;
    length[1][1]=1;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(mmp[i][j])
    		{
    			add(i+mmp[i][j],j,i,j);
    			add(i,j+mmp[i][j],i,j);
			}
		}
	}
	for(int i=length[n][n];i>=2;i--)
	{
		cout<<dp[n][n][i];
	}
	cout<<dp[n][n][1];
 }
```


---

## 作者：zesqwq (赞：1)

# P7642 [BalticOI 2006 Day 2] JUMP THE BOARD! 题解

[题目传送门](https://www.luogu.com.cn/problem/P7642)

看到这种棋盘上的问题，都可以想到 $\text{dp}$，用 $f_{i,j}$ 表示走到点 $i,j $ 的方案数。转移即从 $f_{i,j}$ 转移至 $f_{i+a_{i,j},j}$ 和 $f_{i,j+a_{i,j}}$，注意不要溢出棋盘范围。

这道题目是需要高精的，因为最后答案有 $100$ 位。但是只涉及加法，因此还是很好些的，而且可以用 `long long` 压 $18$ 位。

时间复杂度 $O(n^2 \dfrac{\log V} \omega)$，其中 $V = 10^{100}$，$\omega = 18$。

$\text{Code:}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
const long long P = 1000000000000000000;
inline int read() {
    static int ans;
    static char c;
    c = getchar(), ans = 0;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) ans = (ans << 1) + (ans << 3) + (c ^ 48), c = getchar();
    return ans;
}
inline void add(long long a[], long long b[]) {
    for (int i = 1; i <= max(a[0], b[0]); i++) {
        a[i] += b[i];
        if (a[i] >= P) a[i] -= P, ++a[i + 1];
    }
    while (a[a[0] + 1]) ++a[0];
}
inline void write(long long a[]) {
    printf("%lld", a[a[0]]);
    for (int i = a[0] - 1; i >= 1; i--) printf("%018lld", a[i]);
}
long long f[N][N][7];
int a[N][N];
int main() {
    int n;
    cin >> n, f[1][1][0] = f[1][1][1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (a[i][j] = read()) {
                if (i + a[i][j] <= n) add(f[i + a[i][j]][j], f[i][j]);
                if (j + a[i][j] <= n) add(f[i][j + a[i][j]], f[i][j]);
            }
        }
    write(f[n][n]);
    return 0;
}
```

---

## 作者：cmk666 (赞：1)

[题目链接](/problem/P7642)

题目大意：给定 $n\times n$ 的矩阵 $a$，从 $(1,1)$ 开始，每次可向下或右走 $a_{i,j}$ 格，求走到 $(n,n)$ 有几种方案。

考虑 dp。设 $f_{i,j}$ 表示从 $(i,j)$ 走到 $(n,n)$ 有多少种方案，那么显然边界条件是 $f_{n,n}=1$，答案为 $f_{1,1}$。

转移也很简单，对于 $(i,j)$，在不越界的情况下是下面两者之和：向右走，方案数有 $f_{i,j+a_{i,j}}$；向下走，方案数有 $f_{i+a_{i,j},j}$。

这样就可以 dp 了，时间复杂度 $O(n^2)$。注意到要高精，因此我们~~不要脸的~~使用 python。代码如下：
```python
n = int(input())
a, f = [], []
for i in range(n):
	a.append(list(map(int, input().split())))
	f.append([0] * n)
for i in range(n - 1, -1, -1):
	for j in range(n - 1, -1, -1):
		if i == j == n - 1:
			f[i][j] = 1
			continue
		if i + a[i][j] < n:
			f[i][j] += f[i + a[i][j]][j]
		if j + a[i][j] < n:
			f[i][j] += f[i][j + a[i][j]]
print(f[0][0])
```

---

## 作者：Liu45318 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7642)

~~如果不用高精是~~一道简单的 DP 题。

设 $f_{i,j}$ 表示走到第 $i$ 行第 $j$ 列的总方案数，$val_{i,j}$ 表示第 $ i $ 行第 $ j $ 列的步长。

对于每个格子 $ (i,j) $ 接下来走的路只有两种可能：从 $ (i,j) $ 走到 $ (i+val_{i,j},j) $；从 $ (i,j) $ 走到 $ (i,j+val_{i,j}) $。于是可以依此写出状态转移方程：

$ f_{i+val_{i,j},j} \gets \sum f_{i,j} $

$ f_{i,j+val_{i,j}} \gets \sum f_{i,j} $

值得注意的是，对于 $ val_{i,j} = 0 $ 的点是死胡同，需要特判。还有答案可能较大，需要使用高精。

AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=101;

struct Number{
	int arr[MAXN],len;
}f[MAXN+10][MAXN+10];
int n,val[MAXN][MAXN];

void print(Number x){
	for (int i=MAXN-x.len;i<MAXN;i++)
		cout<<x.arr[i];
	cout<<endl;
}
Number new_number(){
	Number x;
	x.len=1;
	memset(x.arr,0,sizeof(x.arr));
	return x;
}
Number number_add(Number x,Number y){
	int p=0;
	for (int i=MAXN-1;i>=MAXN-max(x.len,y.len)||p;i--){
		x.arr[i]+=y.arr[i]+p;
		p=x.arr[i]/10;
		x.arr[i]%=10;
		x.len=max(x.len,MAXN-i);
	}
	return x;
} //一些高精模板

void input(){
	cin>>n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			cin>>val[i][j]; 
}

void init(){
	for (int i=0;i<MAXN+10;i++)
		for (int j=0;j<MAXN+10;j++)
			f[i][j]=new_number(); //初始化
}

void DP(){
	f[1][1].arr[MAXN-1]=1;
	f[1][1].len=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (val[i][j]){ //特判val[i][j]=0的情况
				f[i+val[i][j]][j]=number_add(f[i][j],f[i+val[i][j]][j]);
				f[i][j+val[i][j]]=number_add(f[i][j],f[i][j+val[i][j]]);
			}
}

void output(){
	/*for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			printf("f[%d][%d] = \n",i,j);
			print(f[i][j]);
		}*/
	print(f[n][n]);
}

int main(){
	input();
	init();
	DP();
	output();
	return 0; //好习惯
}
```


---

## 作者：free_fall (赞：0)

# 题目大意
在一个 $n\times n$ 的矩阵中，每一个方格内的非负整数表示能从这格向下或向右移动的距离，求从 $(1,1)$ 处移动到 $(n,n)$ 处的方案数。
# 思路
因为每次只能向下或者向右移动，所以在从上往下，从左往右扫的时候无后效性，明显是一道动态规划题目，状态与转移方程也非常明显。

用一个二维数组 ```dp[i][j]``` 记录到达 $(i,j)$ 的方案数，状态转移方程如下：

$\left\{\begin{matrix}
dp_{i+a_{i,j},j}+=dp_{i,j}
 \\
dp_{i,j+a_{i,j}}+=dp_{i,j}
\end{matrix}\right.$

注意要将 $i+a_{i,j}$ 或 $j+a_{i,j}$ 大于 $n$ 的情况排除，起始 $dp$ 数组为空，边界情况 ```dp[1][1]=1```，然后用刷表的形式写就行了。

然后你一边感叹这道题太水了一边交答案，发现只拿了 $70$ 分，再回去看题目，发现答案是不超过 $100$ 位的数字，竟然还要开高精（再见了，我亲爱的 ```__int128```）。

然后我~~在极度愤怒的情况下~~写出了以下的高精模板：
```
struct bignum{
	int num[105],len;
	bignum(){//初始化
		memset(num,0,sizeof(num));
		len=1;
	}
	bignum operator =(int x){//赋值
		len=0;
		while(x){
			num[len++]=x%10;
			x/=10;
		}
		return *this;
	}
	bignum operator +(bignum &a){//加法
		bignum b;
		for(int i=0;i<max(len,a.len);i++){
			b.num[i]+=a.num[i]+num[i];
			if(b.num[i]>=10){
				b.num[i+1]++;
				b.num[i]-=10;
			}
		}
		for(int i=max(len,a.len);i>=0;i--){
			if(b.num[i]){
				b.len=i+1;
				break;
			}
		}
		return b;
	}
	void print(){//输出
		for(int i=len-1;i>=0;i--){
			printf("%d",num[i]);
		}
	}
};
```
# 代码
然后就是完整的代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,a[N][N];
struct bignum{
	int num[105],len;
	bignum(){
		memset(num,0,sizeof(num));
		len=1;
	}
	bignum operator =(int x){
		len=0;
		while(x){
			num[len++]=x%10;
			x/=10;
		}
		return *this;
	}
	bignum operator +(bignum &a){
		bignum b;
		for(int i=0;i<max(len,a.len);i++){
			b.num[i]+=a.num[i]+num[i];
			if(b.num[i]>=10){
				b.num[i+1]++;
				b.num[i]-=10;
			}
		}
		for(int i=max(len,a.len);i>=0;i--){
			if(b.num[i]){
				b.len=i+1;
				break;
			}
		}
		return b;
	}
	void print(){
		for(int i=len-1;i>=0;i--){
			printf("%d",num[i]);
		}
	}
};
bignum dp[N][N];
int main(){
	scanf("%d",&n);
	dp[1][1]=1;//不要忘了边界条件
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]==0)continue;//千万要注意判掉为零的情况，要不然会一直原地蹦迪（笑）
			if(i+a[i][j]<=n)dp[i+a[i][j]][j]=dp[i+a[i][j]][j]+dp[i][j];
			if(j+a[i][j]<=n)dp[i][j+a[i][j]]=dp[i][j+a[i][j]]+dp[i][j];
		}
	}
	dp[n][n].print();
	return 0;
}
```

---

