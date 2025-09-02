# Nagisa loves Tomoya

## 题目描述

可爱的古河渚得到了一个序列。她定义一次操作为 将所有的 $a_i$ 变为 $a_i+a_{(i\ mod \ n+1)}$ 
然后她会向你进行 $Q$ 次询问，每次问你 $x,y$ ,意义为在第 $x$ 次操作后位置 $y $ 的元素是多少。

这个问题太简单了，我们的 Nagisa 轻易地就解决了这个问题。请问您能解决这个问题吗？


## 说明/提示

对于$30 \%$的数据，满足：
$1 \leq n \leq 100$

$1 \leq x \leq 100$

$1 \leq Q \leq 100$

对于 $50\%$ 的数据：

$1\leq n \leq 100000$

$1 \leq x \leq 500$

$1 \leq Q \leq 100$

对于 $100 \%$ 的数据，满足

$1 \leq n \leq 10^6$

$1 \leq a_i \leq 10^9$

$1 \leq x \leq 2000$

$1 \leq Q \leq 10^4$

## 样例 #1

### 输入

```
5
1 2 3 4 5
2
1 2
2 2```

### 输出

```
5
12```

# 题解

## 作者：Misaka19280 (赞：9)

这题是洛谷八月月赛T1,按照出题人的说法这题是普及-的难度~~（那我怕不是完了），于是我评价了一个蓝题~~

我们先~~口胡~~人工模拟一波

我们来列一个表（~~直接复制@阿姆斯特朗炮 巨佬的题解中的表，但是他的那篇题解也感谢我了所以我就搬了过来 [放一个他的友链](https://www.luogu.org/blog/user51508/scp-007-luo-gu-ba-yue-yue-sai-t1-post)~~）

![授权如下](https://cdn.luogu.com.cn/upload/pic/30985.png)

↑授权图

```
						a1 a2 a3

                   a1+a2  a2+a3  a3+a1

			a1+2a2+a3 	a2+2a3+a1	a3+2a1+a2

		a1+3a2+3a3+a1 a2+3a1+3a3+a2 a3+3a1+3a2+a3

```

我们抽样调查（滑稽）一下第一列

```

						a1

					   a1+a2

					 a1+2a2+a3

				   a1+3a2+3a3+a1
```

咳咳

看出来什么了吗

没看出来？

好吧，我们把系数抽出来

1
1 1
1 2 1
1 3 3 1

这个裸的杨辉三角看出来了吧= =

于是就非常开心了

求出杨辉三角

对于每次询问，直接求出从x开始的后面每一位乘以对应的杨辉三角形第x层的系数就可以了

复杂度O(qy)可以接受

当然要预处理出来杨辉三角形

下面我们上代码

```
Const 
	maxx=2001;
	moha=998244353; //不要在意这个变量的名称

Var
	a:array[1..1000000]of longint;
	yh:array[1..maxx,1..maxx]of longint;
	n,i,m,x,y,j,cnt,xx:longint;
	ans:qword;
	
Begin
	readln(n);
	for i:=1 to n do
		read(a[i]);
	for i:=1 to maxx do
		begin
			yh[i,1]:=1;
			yh[i,i]:=1;
			for j:=2 to i-1 do
				yh[i,j]:=(yh[i-1,j-1]+yh[i-1,j]) mod moha; //杨辉三角形要直接取膜，不然会爆
		end; //预处理杨辉三角形
	readln(m);
	for i:=1 to m do
		begin
			read(x,y);
			ans:=0;
			j:=y;
			cnt:=1; //这个cnt完全没必要，但是总觉得写了更清楚
			inc(x); //这里inc(x)需要自己想一下原因,emm算了告诉你吧，你比如说x=1，就是求第y和y+1的值，你要是不inc的话就只求y了
			xx:=x;
			while x>0 do
				begin
					ans:=(ans+a[j]*yh[xx,cnt]) mod moha;
					j:=j mod n+1;
					dec(x);
					inc(cnt);
				end;
			writeln(ans);
		end;
End.
```

什么你跟我说Pascal看不懂？= =

那就光看思路，去其他的楼看代码= =（虽然我的思路并不怎么清晰Orz）

还有一个洛谷的题目数量统计bug，跟这题有关

[一个奇怪的现象](https://www.luogu.org/discuss/show/60850)

~~其实月赛的时候我为了测试大一点的数据手残打了个文件然后就获得了0分的好成绩~~

---

## 作者：R·Buffoon (赞：5)

**前言**：交的时候只有50分，狂调了许久，一直以为是炸$int$了，改成$long long$，还是50分，把杨辉三角多预处理了几个（本来只预处理到$2001$），就给过了（?）
***
**正文：**~~显然~~，这道题暴力是不能过的，所以，只能用其他算法，~~易得~~，是数论

于是，开始手%找规律（用题目的数据来，只列$a_1$）
$$a_1$$
$$a_1+a_2$$
$$a_1+2a_2+a_3$$
$$a_1+3a_2+3a_3+a_1$$
$$a_1+4a_2+6a_3+4a_4+a_5$$
$$a_1+5a_2+10a_3+10a_4+5a_5+a_1$$
$$a_1+6a_2+15a_3+20a_4+15a_5+6a_1+a_2$$
$$a_1+7a_2+21a_3+35a_4+35a_5+21a_1+7a_2+a_3$$
$$a_1+8a_2+28a_3+56a_4+70a_5+56a_1+28a_2+8a_3+a_4$$
把每项的系数提取出来，就是
$$1$$
$$1\qquad1$$
$$1\qquad2\qquad1$$
$$1\qquad3\qquad3\qquad1$$
$$1\qquad4\qquad6\qquad4\qquad1$$
$$1\qquad5\qquad10\qquad10\qquad5\qquad1$$
$$1\qquad6\qquad15\qquad20\qquad15\qquad6\qquad1$$
$$1\qquad7\qquad21\qquad35\qquad35\qquad21\qquad7\qquad1$$
$$1\qquad8\qquad28\qquad56\qquad70\qquad56\qquad28\qquad8\qquad1$$
这不就是一个[杨辉三角](https://baike.baidu.com/item/%E6%9D%A8%E8%BE%89%E4%B8%89%E8%A7%92/215098?fr=aladdin)吗？~~打表打上瘾~~

而且，通过观察可以发现，变量是每$n$个一循环，~~然后，就可以愉快的切题啦！~~
~~~cpp
#include<bits/stdc++.h>
#define RI register int
#define LL long long
using namespace std;

int in()
{
    int qwq=0;char c=getchar();
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar()) qwq=(qwq<<1)+(qwq<<3)+(c&15);
    return qwq;
}

const int N=1e6+5;
const int M=2005;
const int mod=998244353;

int n;
int a[N];
int q,x,y;
LL yang[M][M],ans;

inline void qaq()
{
	yang[0][0]=1;
	for(RI i=1;i<M;++i)
	{
		yang[i][0]=1;
		for(RI j=1;j<M;++j)
		{
		    yang[i][j]=(yang[i-1][j]+yang[i-1][j-1])%mod;
		}
	}
}

int main()
{
    qaq();//杨辉三角预处理（从零开始预处理，之后操作方便）
    
    n=in();
    for(RI i=1;i<=n;++i) a[i]=in();
    
    //打表代码（验证预处理的杨辉三角是否正确）
    /*for(RI i=0;i<=n;++i)
    {
    	for(RI j=0;j<=i;++j)
    	{
    		cout<<yang[i][j]<<" ";
		}
		cout<<endl;
	}*/
	
    q=in();
    for(RI i=1;i<=q;++i)
    {
    	x=in(),y=in();
	    ans=0;
    	for(RI j=0;j<=x;++j)//从零开始（的...）
    	{
    	    if(y==n) ans=(a[y]*yang[x][j]+ans)%mod,y=1;
            else ans=(a[y]*yang[x][j]+ans)%mod,++y;
		}
		printf("%lld\n",ans%mod);
    }
	
    return 0;
}
~~~
代码中的这一段
~~~cpp
if(y==n) ans=(a[y]*yang[x][j]+ans)%mod,y=1;
else ans=(a[y]*yang[x][j]+ans)%mod,++y;
~~~
也可以这么写
~~~cpp
ans=(ans+a[y]*yang[x][j])%mod;
y=(y%n)+1;
~~~
不过后者跑得好慢，比前者慢了近450ms
***
**结语**：因为杨辉三角少预处理几个导致被卡50分这件事告诉我们，不能吝啬（笑）

~~哦，对了，放出来的代码是改良后的，原来的杨辉三角预处理是从1开始~~

~~还有，我是第520个通过此题的人~~

---

## 作者：noiking (赞：4)

手推了样例
加上刚刚才做了一个和杨辉三角沾边的题
然后就玄学的发现了本题最大的秘密
然而即使如此，刷题之路依然艰难：
	杨辉三角递推初始值不对
    x和q的范围看反
    数组从0还是1开始
    要mod数组长度
    ++j还是j++
    开long long
哦
杨辉三角是这样滴
      1 
     1 1
    1 2 1
   1 3 3 1
  1 4 6 4 1
1 5 10 10 5 1
......
想知道杨辉三角和组合数的关系请右转[noip2016 组合数问题](https://www.luogu.org/problemnew/show/P2822)

    果然晚上不适合做题
    （其实是我太菜，especially数论
    当然so are图论，数据结构……）
    

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define ll long long
#define N 1000005
using namespace std;
int n,q,a[N];
ll yhsj[2003][2003],ans;
int read(){
 	int k=0,f=1;char c=getchar();
 	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
 	for(;c<='9'&&c>='0';c=getchar())k=(k<<3)+(k<<1)+c-'0';
 	return f*k;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
	yhsj[0][0]=1ll;
	for(int i=1;i<=2002;i++){
		for(int j=1;j<=2002;j++)yhsj[i][j]=(yhsj[i-1][j]+yhsj[i-1][j-1])%mod;
	}
	q=read();
	for(int i=1,x,y;i<=q;i++){
		x=read(),y=read();ans=0ll;int j=y;x++;
		for(int k=1;yhsj[x][k]!=0;k++){
			if(j==n)ans=(a[j]*yhsj[x][k]%mod+ans)%mod,j=1;
			else ans=(a[j]*yhsj[x][k]%mod+ans)%mod,j++;
		}
		printf("%lld\n",ans%mod);
	}
	return 0;
}
```
还有就是附送30分傻X代码
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define mod 998244353
#define N 100005
using namespace std;
int n,x[101],y[101],mx,q,dp[501][N];
int read(){
 	int k=0,f=1;char c=getchar();
 	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
 	for(;c<='9'&&c>='0';c=getchar())k=(k<<3)+(k<<1)+c-'0';
 	return f*k;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)dp[0][i]=read();
    q=read();
    for(int i=1;i<=q;i++)x[i]=read(),mx=max(mx,x[i]),y[i]=read();
    for(int i=1;i<=mx;i++)
    	for(int j=1;j<=n;j++)
    		dp[i][j]=(dp[i-1][j]+dp[i-1][j%n+1])%mod;
    for(int i=1;i<=q;i++)printf("%d\n",dp[x[i]][y[i]]%mod);
    return 0;
}


```

---

## 作者：Yyxxxxx (赞：3)

# 题意
对于一个数列$A:A_1,A_2...A_n$，进行$k$次操作。  
每次操作$\forall i,A_i=A_i+A_{i\%n+1}$。  
求第$x$次操作后$A_y$的值。  
# 题解
首先来模拟下，对于一个$n=3$的数列:  
每次$A_1=A_1+A_2,A_2=A_2+A_3,A_3=A_3+A_1$，初始值为$a_1,a_2,a_3$
$$a_1,a_2,a_3$$
$$a_1+a_2,a_2+a_3,a_3+a_1$$
$$a_1+2a_2+a_3,a_2+2a_3+a_1,a_3+2a_1+a_2$$
$$...$$
单看$A_1$，有：
$$1a_1$$
$$1a_1+1a_2$$
$$1a_1+2a_2+1a_3$$
$$1a_1+3a_2+3a_3+1a_1$$
$$...$$
显而易见，系数就是杨辉三角，而且数据范围比较小，可以直接开数组预处理。  
综上：
$$Ans=\sum\limits_{k=0}^yC_x^k\cdot a_{(y+k)\%mod}$$
所以说代码就很显而易见了。
# $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=2e3+5;
long long f[maxm][maxm];
const int mod=998244353;
int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	return x*f;
}
void init()
{
	f[0][0]=1;
	for(int i=1;i<maxm;i++)
	{
		f[i][0]=1;
		for(int j=1;j<maxm;j++)
			f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod;
	}
}
const int maxn=1e6;
int a[maxn];
int main()
{
	int n=read(),q;
	for(int i=1;i<=n;i++)a[i]=read();
	init();q=read();
	for(int i=1;i<=q;i++)
	{
		int x=read(),y=read();
		long long ans=0;
		for(int k=0;k<=x;k++)
		{
			ans=(ans+a[y]*f[x][k]%mod)%mod;
			y=y%n+1;
		}
		printf("%lld\n",ans%mod);
	}
	return 0;
}
```


---

## 作者：SofanHe (赞：2)

~~人工智障推荐了这个题,然后我尝试查看题解,结果空空如也.于是就诞生了这个题解~~

### 题目分析

看看题……嗯，不错~~，是个好模拟题~~。（没看数据范围）

然后上手了，模拟一下……~~手动画图中~~

![第一个正常的图](https://cdn.luogu.com.cn/upload/pic/30800.png)

看出了什么？注意看系数！

~~什么？你说没看出来？ 那看看这个杨辉三角表~~

![杨辉三角表](https://cdn.luogu.com.cn/upload/pic/30801.png)

很好，仿佛找到了思路。

于是继续手写往下推。不愉快的事情发生了！

下一列是什么？

![不正常的一列](https://cdn.luogu.com.cn/upload/pic/30802.png)

稍微动一下脑筋，把那个系数2拆成1+1，就有了

![正常了](https://cdn.luogu.com.cn/upload/pic/30803.png)

这样我们取一下Mod就可以了。

哦对了，还得对x排一下序，防止多做

### 题目关键

手动模拟看出系数关系。

### Code
```cpp
#include<bits/stdc++.h>
#define lL long long
using namespace std;
const int Mod = 998244353,Nmax = 1000001,Qmax = 10001;

int n,a[Nmax],m,C[2010],yyt,tot=1,iid;
struct Question{int x,y,id;}q[Qmax];
long long ans[Qmax];

bool comp(Question tt,Question yy){
	return tt.x<yy.x;
}

inline void Init(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		a[i] %= Mod;
	}
	
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d",&q[i].x,&q[i].y);
		q[i].id = i;q[i].x+=1;
	}
	
	sort(q+1,q+m+1,comp);
}

inline void Doit(){
	C[1] = 1;C[2] = 1;
	for(int i=2;tot<=m;){
		if(q[tot].x==i){
			yyt = q[tot].y;iid = q[tot++].id;
			for(int k=1;k<=i;++k)
				ans[iid] = (ans[iid] + (lL)((lL)C[k] * (lL)a[(yyt-2+k)%n + 1])%Mod)%Mod;
		}
		if(q[tot].x!=i)
			for(int k=(++i);k>1;--k)
				C[k] =(C[k] + C[k-1])%Mod;
	}
}

inline void Prin(){
	for(int i=1;i<=m;++i)
		printf("%lld\n",ans[i]);
}

int main(){
	Init();
	Doit();
	Prin();
	return 0;
}
```

---

## 作者：lbh666 (赞：1)

## 题目大意
给出一个序列，序列的长度为 $n$，定义一次操作为将所有的 $a_i$ 变成 $a_i + a_{(i \bmod n + {1})}$，再给出两个数 $x$ 和 $y$，求 $x$ 次操作后 $a_y$ 是多少。

## 思路分析
看到这种题，不妨模拟一下。

假设 $n = 3$，输入了三个数，分别是 $a_1$ 到 $a_3$。

简单点来说，每个数都赋值为自己和下一个数的和，最后一个数赋值为自己和第一个数的和，所以得出下面的三组数。

```cpp
     a1             a2           a3
   a1+a2          a2+a3         a3+a1
 a1+2a2+a3      a2+2a3+a1      a3+2a1+a2
a1+3a2+3a3+a1  a2+3a3+3a1+a2  a3+3a1+3a2+a3
   ......         ......         ......
```

我们再选一组调查。

```cpp
     a1
   a1+a2   
 a1+2a2+a3      
a1+3a2+3a3+a1
```

把系数拎出来。

```cpp
      1
    1   1
   1  2  1
  1  3  3  1
```

这就是杨辉三角，其它两组也是杨辉三角。

```cpp
     a1  //操作0次后 
   a1+a2   //操作1次后 
 a1+2a2+a3   //操作2次后 
a1+3a2+3a3+a1   //操作3次后 
```

我们为了让上面的数的层数与操作次数挂上关系，把层数从 $0$ 一直编号到 $3$，于是问题从求 $x$ 次操作后 $a_y$ 的值变成了求上面数据的第 $x$ 层的每个数的和。

系数有杨辉三角记录，那其余数呢？

我们把上面的数据的最后一行去掉系数后的序列拎出来，`a1+a2+a3+a1`，再把 $a$ 也给省了，只剩下下标 `1 2 3 1`，我们发现下标是连续的，到 $n$ 后再回到 $1$ 开始循环。

我们只需要一个变量来记录 $a$ 数组的下标就好了，但不用新开一个变量，因为每一层的第一个数等于塔尖的那个数，塔尖的数是我们要操作的数，那么 $y$ 不就是塔尖那个数的下标？所以 $y$ 也可以作为某一层第一个数的下标，往后计算的时候，不断把 $y$ 加 $1$ 就可以，特判一下是否到 $n$，如果到了，把 $y$ 赋值为 $1$ 即可。

## 操作步骤
- 建一个二维数组来构造一个杨辉三角，并把它初始化。

- 输入。

- 把杨辉三角第 $x$ 层每一列的数乘上 $a_y$ 的积加进答案，别忘了每次更新 $y$，并且答案要模上 $998244353$。

- 对于每次询问，输出答案即可。

#### 下面上代码！

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2005,M=1e6+5;
const int T=998244353;  
int n,q,ans=0;
int dp[N][N],a[M]; //用dp二维数组来构建杨辉三角 

inline int read(){  //快读优化 
    int x=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}

void init(){   //构建杨辉三角 
	dp[0][0]=1; 
	for(int i=1;i<=N;++i){
		dp[i][0]=1; //每一层的第0列为1 
		for(int j=1;j<=N;++j){
			dp[i][j]=(dp[i-1][j]+dp[i-1][j-1])%T;//把它加上上面的数与左上角的数 
		}
	}
}

signed main(){
	init(); //初始化一下 
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	q=read();
	while(q--){
		int x,y;
		x=read(),y=read();
		for(int i=0;i<=x;++i){  //枚举杨辉三角第x层的每一列 
			ans+=(dp[x][i]*a[y])%T; //dp[x][i]代表第x层第i个系数，把它与a[y]相乘的积模上T再加进答案 
			ans%=T;  //自己模一次，不加这个的话，就会喜获10分 
			if(y==n)y=1;    //如果已经到头了，就回到第一个数 
			else ++y;   //否则继续往下 
		}
		cout<<ans<<"\n"; //输出 
		ans=0;  //清零很重要 
	}
	return 0;
}
```

#### 最后，求管理员通过！

---

## 作者：cosf (赞：0)

## [P4828](https://www.luogu.com.cn/problem/P4828)

可以发现，每次操作都是将序列中相邻两数相加得到新的序列。看到这个，一眼就可以想到杨辉三角。我们需要的即杨辉三角中第 $x$ 行（从 $0$ 开始）的数字作为系数，也就是以 $x$ 为底的组合数。

操作了 $x$ 次以后，显然 $a_y$ 就会变成 $\sum_{i=0}^x\binom{x}{i}a_{(y+i-1) \bmod n + 1}$。

时间复杂度是 $O(x(x+Q))$ 的。要预处理。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 2005
#define MAXM 1000006
#define MOD 998244353

using ll = long long;

ll C[MAXN][MAXN];

ll val[MAXM];

int main()
{
	C[0][0] = 1;
	int n;
	cin >> n;
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			C[i + 1][j] += C[i][j];
			C[i + 1][j] %= MOD;
			C[i + 1][j + 1] += C[i][j];
			C[i + 1][j + 1] %= MOD;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> val[i];
	}
	int q;
	cin >> q;
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		ll res = 0;
		for (int i = 0; i <= x; i++)
		{
			res += C[x][i] * val[(y + i - 1) % n + 1] % MOD;
			res %= MOD;
		}
		cout << res << endl;
	}
	return 0;
}

```


---

