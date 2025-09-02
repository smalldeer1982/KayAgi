# 「GMOI R1-T1」Perfect Math Class

## 题目描述

Index 给了你一个函数如下：

$$f(x)=a_kx^k+a_{k-1}x^{k-1}+\cdots+a_1x^1+a_0$$

画出它的函数图像（`*` 表示经过该点，`.` 表示不经过该点），大小为 $n\times m$，其中 $x$ 的范围是 $[0,n-1]$，$f(x)$ 的范围是 $[0,m-1]$。

具体的，你需要输出一个 $n\times m$ 的字符矩阵，若该函数经过整点 $(x,y)$，则**从左往右**第 $x+1$ 列，**从下往上**第 $y+1$ 行输出 `*`，否则为 `.`。

## 说明/提示

样例 $1$ 解释：

该函数为 $f(x)=x$，显然在 $x\in[0,4], f(x)\in[0,4]$ 时穿过 $(0,0),(1,1),(2,2),(3,3),(4,4)$ 这些整点。

对于 $100\%$ 的数据，$-12\le a_i\le 12
$，$n=m$。每个测试点等分。

| 测试点 | $n\le$ | $m\le$ | $k\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $1$ | $0$ | $-$ |
| $2$ | $5$ | $5$ | $0$ | $-$ |
| $3$ | $5$ | $5$ | $1$ | $a_1=1$ |
| $4$ | $5$ | $5$ | $1$ | $a_0+a_1\le 2$ |
| $5$ | $10$ | $10$ | $1$ | $-$ |
| $6$ | $10$ | $10$ | $2$ | $a_0=a_1=0,a_2\ge n$ |
| $7$ | $100$ | $100$ | $2$ | $-$ |
| $8$ | $100$ | $100$ | $3$ | $-$ |
| $9$ | $100$ | $100$ | $5$ | $-$ |
| $10$ | $100$ | $100$ | $7$ | $-$ |

## 样例 #1

### 输入

```
5 5 1
0 1
```

### 输出

```
....*
...*.
..*..
.*...
*....```

## 样例 #2

### 输入

```
8 8 1
0 2
```

### 输出

```
........
...*....
........
..*.....
........
.*......
........
*.......
```

# 题解

## 作者：scp020 (赞：28)

### 题目大意

给定一个函数 $f(x)$ 的各项的系数，让你画出这个函数图像。

### 解决

因为这道题只是让我们画出在整数点上的图像，所以我们考虑从 $0$ 到 $n-1$ 枚举横坐标，即可求出对应的纵坐标，进行记录即可。

这里需要一个 $calc$ 函数，顾名思义，就是求出一个 $x$ 对应的 $y$ 的值。对于次数为 $i$ 的项（常数项认为是次数为 $0$），当前项的值为 $a_i \times x ^ i$。

特殊注意的是：本题输出顺序有所调整。如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/vvttllks.png)

### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(long long &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
long long n,m,k,a[10];
char ans[200][200];
inline long long ksm(long long a,long long b)
{
	long long ret=1;
	while(b)
	{
		if(b&1) ret=ret*a,b--;
		a=a*a,b>>=1;
	}
	return ret;
}
inline long long calc(const int &x)
{
	long long ret=0;
	for(int i=0;i<=k;i++) ret+=a[i]*ksm(x,i);
	if(ret>m) return -50;
	return ret;
}
int main()
{
	read(n),read(m),read(k);
	for(int i=0;i<=k;i++) read(a[i]);
	for(int i=0;i<n;i++) ans[m-calc(i)][i]='*';
	for(int i=1;i<=m;i++,Putchar('\n'))
		for(int j=0;j<n;j++)
			if(ans[i][j]=='*') Putchar('*');
			else Putchar('.');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```



---

## 作者：zhang_kevin (赞：12)

我们可以先枚举 $x$。如果 $x \in [0,n-1]$，我们就求出 $f(x)$。求 $f(x)$ 时可以使用快速幂，但暴力也可以过。

如果 $f(x)$ 符合范围，标记 $(x,f(x))$，最后输出 `*`，其他的都输出 `.`。

另外注意开 `long long`，放一份赛时 AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool vis[101][101];
long long a[101];
typedef long long ll;
inline int fp(ll a, ll n){
    int ans = 1;
    while(n){
        if(n & 1)
            ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
int n, m, k;
inline ll f(int x){
	ll res = a[0];
	for(ll i = k; i >= 1; i--){
		res += a[i] * fp(x, i);
	}
	return res;
}
signed main(){
	cin >> n >> m >> k;
	for(int i = 0; i <= k; i++){
		cin >> a[i];
	}
	for(int i = 0; i <= n - 1; i++){
		int ff = f(i);
		if(ff >= 0 && ff <= m - 1){
			vis[n-ff][i+1] = true;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(vis[i][j]) putchar('*');
			else putchar('.');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：ChrisWangZi (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/P8924)

------------

## 思路
这道题，其实就是当~~那个本蒟蒻不会的~~函数 $f(x)$ 的返回值为 $y$ 时，便在 $(x+1,y+1)$ 的位置输出 ``*`` ，否则输出 ``.`` 。

 一个 for 再加上判断就可以了。
 
 唯一的坑点：**从下往上**(将 $y$ 倒着循环即可)
 
 ~~本蒟蒻调了半天样例，才发现是从下往上~~
 
 ## 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[10];
int n,m,k;
long long f(int x){//那个函数
	long long ans=0;
	for(int i=0;i<=k;i++){
		ans+=a[i]*pow(x,i);
	}
	return ans;
}
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++){
		cin>>a[i];
	}
	for(int y=n-1;y>=0;y--){
		for(int x=0;x<=m-1;x++){//坑点
			if(f(x)==y){
				cout<<'*';
			}
			else{
				cout<<'.';
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：6)

## 官方题解

注意到一个显然的性质：$(x,y)$ 点为 `*` 当且仅当 $f(x)=y$。

也就是说，我们只要枚举 $x$，计算出对应的 $f(x)$，然后在 $(x,f(x))$ 处更改为 `*` 即可。

由于 $|f(x)|$ 最大值是 $12\times 100^{7}$ 左右，所以只要开 `long long` 即可。

此题唯一需要注意的是下标，左下角为 $(0,0)$，还有算出 $f(x)$ 后要进行判断是否在 $\left[0,m-1\right]$ 范围之内，否则可能会 RE。

---

## 作者：Day_Of_Dream (赞：4)

说一句题外话：身为T1，这道题还是比较良心的。

## 下面进入正题

预备知识：[平面直角坐标系](https://baike.baidu.com/item/%E5%B9%B3%E9%9D%A2%E7%9B%B4%E8%A7%92%E5%9D%90%E6%A0%87%E7%B3%BB/1296463?fr=aladdin)

先分析思路：

根据题意，先写出函数，再计算标点，前提是要初始化整个方阵为‘.’，最后打印输出即可。

那怎么计算标点呢？

很简单，只需枚举 $x$ 的值就可以了，同时计算 $f(x)$ 的值，并判断合不合法即可。

### Q1：那 $x$ 的取值范围是多少呢？

先思考 $x$ 表示什么。

在平面直角坐标系中，$x$ 轴表示横轴，那么 $x=1$ 这条直线在平面直角坐标系中到底是什么样的呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/1ohcxkyq.png)

如图，蓝色的线就是 $x=1$ 这条直线。由此我们得出，**$x$ 表示的是列，那么 $f(x)$ 表示的是行**。

那么因为题中 $n$ 表示行，$m$ 表示列，所以 $x$ 的范围是 $0≤x<m$，$f(x)$ 的范围是 $0≤x<n$。

### Q2：那 $f(x)$ 怎么算？

用循环，依次枚举即可。

但是这里面有一个**坑点**。

#### 能不能发现 $f(x)≥n$ 就退出循环呢？

答案是**不能**。

因为如果后面 $a(i)<0$，那么 $f(x)$ 算到最后可能会小于 $n$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[110][110];
long long n,m,a[10],q;
long long k;
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			c[i][j]='.';
		}
	}//初始化
	for(int x=0;x<m;x++)
	{
		q=0;//这里q表示f(x)的值
		for(int i=k;i>=0;i--)
		{
			q=q+a[i]*pow(x,i);
		}
		if(q<n&&q>=0)
		{
			c[n-q-1][x]='*';//重点+坑点，请读者自行体会为什么用（n-q-1）来表示行
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cout<<c[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```
这篇题解到此结束，感谢大家的观看。


---

## 作者：Infinite_Eternity (赞：4)

### Warning

警钟长鸣，这个蒟蒻因为数组开小了导致 $100 \rightarrow 60$。~~但也因此正正好好 rank 635 拿到了 1RMB。~~

# Description

[P8924 「GMOI R1-T1」Perfect Math Class](https://www.luogu.com.cn/problem/P8924)

给定一个如下的函数：

$$f(x)=a_kx^k+a_{k-1}x^{k-1}+\cdots+a_1x^1+a_0$$

画出它的函数图像。具体地，输出一个 $n\times m$ 的字符矩阵，若该函数经过整点 $(x,y)$，则**从左往右**第 $x+1$ 列，**从下往上**第 $y+1$ 行输出 `*`，否则为 `.`。

数据范围：$-12\le a_i\le 12
$，$n=m$。

# Analysis

模拟题。

- 首先，将函数 $f(x)=a_kx^k+a_{k-1}x^{k-1}+\cdots+a_1x^1+a_0$ 表示出来：(为了避免进行不必要的冗余的计算，我特判了 $x=0$ 的情况）

```cpp
int cnt=0;
if (j==0)
    cnt=cnt+a[0];
else
{
    for (register int num=k; num>=0; --num)
    {
        if (num!=0)
            cnt=cnt+a[num]*(int)pow(j,num);
        else
            cnt=cnt+a[num];
    }
}
```

- 接下来，对于每个点的 $x$ 坐标，计算出其对应的 $f(x)$ 值，并于 这个点的 $y$ 坐标相比。若相同，则标记这个点。

- 最后，由于第一象限和二维数组的方向正好相反，所以我们需要逆向输出：

```cpp
for (register int i=m-1; i>=0; --i)
{
    for (register int j=0; j<n; ++j)
    {
        if (ans[i][j]==1)
            printf("*");
        else
            printf(".");
    }
    printf("\n");
}
```

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register char c = getchar();
    register int x = 0, f = 1;
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return x * f;
}
signed main()
{
    int n,m,k;
    n=read(),m=read(),k=read();
    int a[k+1],ans[m+1][n+1]= {0};
    for (register int i=0; i<=k; ++i)
        a[i]=read();
    for (register int i=0; i<m; ++i)
    {
        for (register int j=0; j<n; ++j)
        {
            int cnt=0;
            if (j==0)
                cnt=cnt+a[0];
            else
            {
                for (register int num=k; num>=0; --num)
                {
                    if (num!=0)
                        cnt=cnt+a[num]*(int)pow(j,num);
                    else
                        cnt=cnt+a[num];
                }
            }
            if (i==cnt)
                ans[i][j]=1;
        }
    }
    for (register int i=m-1; i>=0; --i)
    {
        for (register int j=0; j<n; ++j)
        {
            if (ans[i][j]==1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：ran_qwq (赞：4)

模拟题。

对于 $i\in[0,n-1]$，求出 $f(i)$。如果 $0\leq f(i)<m$，则能包含在图像内，把这个点打上标记。最后把所有打上标记的点输出 ```*```，其他点输出 ```.``` 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=1e9;
//省略快读快写 
int n,m,k,a[10],b[110][110];
int power(int x,int y)//求x^y的值，这种写法比pow要快 
{
	int ans=1;
	for(int i=1;i<=y;i++)
		ans*=x;
	return ans;
}
signed main()
{
	n=read(),m=read(),k=read();
	for(int i=0;i<=k;i++)
		a[i]=read();
	for(int i=0;i<n;i++)
	{
		int ans=0;
		for(int j=k;j>=0;j--)
			ans+=a[j]*power(i,j);
		if(ans>=0&&ans<m)
			b[ans][i]=1;
	}
	for(int i=m-1;i>=0;i--)
	{
		for(int j=0;j<n;j++)
			if(b[i][j])
				cout<<"*";
			else
				cout<<".";
		puts("");
	}
}

```


---

## 作者：xixisuper (赞：3)

# P8924 「GMOI R1-T1」Perfect Math Class

遇题不决，暴力美学。

## 1.读题

第一眼看到题面上长长的一段函数，真的十分唬人。

简化一下题意。

- 有一个函数 $f(x)=a_kx^k+a_{k-1}x^{k-1}+\cdots+a_1x^1+a_0$。
- 用 `*` 和 `.` 组成的 $n\times m$ 的字符矩阵表示 $x$ 取 $0$ ~ $n-1$ 时的函数图像 。
- 若该函数经过整点 $(x,y)$，则**从左往右**第 $x+1$ 列，**从下往上**第 $y+1$ 行输出 `*`，否则为 `.`。
- 对于 $100\%$ 的数据，$-12 \le a_i \le 12$，$n = m \le 100$，$k \le 7$。

## 2.解题

如果不是因为看了一眼数据范围我就果断放弃这题了。

由于所有的数据都很小，所以我们可以考虑暴力。对于每一个 $x$，都求一遍 $f(x)$，然后把 $(x,f(x))$ 的位置打上一个标记（注意这里 $f(x)$ 可能过大，所以只需要把 $f(x)\le m$ 的情况打上标记就行了）。输出时，根据当前位置标记的有无，决定是输出 `*` 还是 `.`。

求一次函数值的时间复杂度是 $O(k)$，要求 $n$ 次函数值，所以总时间复杂度为 $O(k \times n)$。

**十年 oi 一场梦，不开 long long 见祖宗。** ~~不要问我怎么知道的~~

## 3.题解

蒟蒻代码，不喜勿喷。

```cpp
#include <iostream>
#define ll long long
using namespace std;
bool mp[1000][1000];//标记数组
ll num[1000];//即题面中的 a 序列
ll y[1000];//y[x] 表示 f(x) 的值
int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++){
		cin>>num[i];
	}
	for(int i=0;i<n;i++){
		ll mi=1;
		for(int j=0;j<=k;j++){//求函数值
			y[i]+=(num[j]*mi);
			mi*=i; 
		}
		if(y[i]+1<=m) mp[i+1][y[i]+1]=1;//打标记
	}
	//由于打标记时是按照“从左往右，从下往上”的顺序存储的
	//所以输出时要外层循环由大到小，内层循环从小到大
	//标记数组二维坐标内外颠倒
	//详见下方输出部分
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			if(mp[j][i]) cout<<'*';
			else cout<<'.';
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Elairin176 (赞：3)

[传送门](https://www.luogu.com.cn/problem/P8924)       
简单题目。       
我们首先指定 $mp_{i,j}$ 为 $x=i$，$y=j$ 时的情况，一开始都初始化为 `.`。之后可以枚举 $[0,n-1]$，对于每一个在范围内的 $x$，我们计算 $f(x)$。我们指定 $y=f(x)$。首先，判断 $y$ 是否在 $[0,m-1]$ 这个区间内，如果 $y<0$，那么我们跳过这一个数（即 continue）。如果 $y≥ m$，那么我们直接结束遍历（即 break）。 如果在区间内，我们将 $mp_{m-y-1,x}$ 的值定为 `*`。计算 $f(x)$ 时我们可以使用快速幂。    
需要注意的是：    
- 计算 $f(x)$ 时不要忘记开 `long long`。    
- 本题 $x$ 和 $y$ 的方向有些特殊。 

CODE：   
```cpp
#include <iostream>
using namespace std;
long long n,m,k,a[100];
inline int pw(int a,int b){//快速幂
	if(b==1){
		return a;
	}
	if(b==0){
		return 1;
	}
	int mid=pw(a,b/2);
	if(b&1){
		return mid*mid*a;
	}else{
		return mid*mid;
	}
}
inline long long make(int x){//计算f(x)
	int ans=0;
	for(int i=k;i>=0;i--){
		ans+=pw(x,i)*a[i];
	}
	return ans;
}
char mp[200][200];
int main(void){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=0;i<=n;i++){//初始化
		for(int j=0;j<=m;j++){
			mp[i][j]='.';
		}
	}
	for(int i=0;i<=k;i++){
		scanf("%lld",&a[i]);
	}
	for(int x=0;x<=n-1;x++){//枚举
		long long y=make(x);
		if(y>=m){//如果大于等于就break
			break;
		}
		if(y<0){//小于0就continue
			continue;
		}
		mp[m-y-1][x]='*';//否则绘制
	}
	for(int i=0;i<n;i++){//输出
		for(int j=0;j<m;j++){
			cout<<mp[i][j];
		}
		cout<<endl;
	}
}
```


---

## 作者：zfx_VeXl6 (赞：3)

直接按题意模拟即可。

注意循环时第一重循环的是 $f(x)$，第二重循环的是 $x$。因为画图是从上到下，而坐标是从下往上的，所以在循环 $f(x)$ 的时候要从 $m-1$ 开始循环到 $0$。

当循环到一个点 $(x,y)$ 的时候，求出 $f(x)$ 的值，如果 $y=f(x)$，则在这点输出 `*`，否则输出 `.`。

核心代码：

```cpp
for(int y=m-1;y>=0;y--)
{
    for(int x=0;x<n;x++)
    {
        int fx=0;
        for(int i=0;i<=k;i++)
            fx+=a[i]*pow(x,i);
        if(y==fx)
            cout<<'*';
        else
            cout<<'.';
    }
    cout<<'\n';
}
```

---

## 作者：Iniaugoty (赞：2)

感谢GMOI，让我这个蒟蒻终于有一场公开赛能够250pts+。

我在的出题组（[传送门，欢迎加入](https://www.luogu.com.cn/team/52191)）曾有一个人在数学课上出过绘制函数图像的题目，甚至也是用 ```*``` 和 ```.```，不过不是这样的多项式函数，而是输入解析式，这里不多说了。我看到这题感到莫名亲切，于是决定赛后来提交一篇题解（~~虽然我认为肯定过不了~~）。

根据函数的定义，我们知道，对于函数定义域内的任意 $x$，$\operatorname{f}(x)$ 有且仅有一个与其对应的值，也就是说，在输出数据中，每一列**最多**只有一个点是 ```*```，（也可能没有，$\operatorname{f}(x)$ 的值域为 $[0,m)$，超出就不输出了）。于是我们就得到了一个很简单的做法，只要计算出 $\operatorname{f}(x)$ 的定义域 $[0,n)$ 中每个正整数 $x$ 对应的 $\operatorname{f}(x)$ 的值即可。

AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,a[10],s[105];//s[i] 存储 x=i 时 f(x) 的值，超出值域则为 -1
long long f(long long x){//求 f(x) 的值
    long long t=1,sum=0;
    for(int i=0;i<=k;i++){
        sum+=t*a[i];
        t*=x;
    }
    if(sum<0||sum>=m)
        return -1;//出界改为-1 
    return sum;
}
int main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=0;i<=k;i++)
        scanf("%lld",&a[i]);
    for(int i=0;i<n;i++)
        s[i]=f(i);
    for(int i=m-1;i>=0;i--){//打印图像，注意 y 轴是从大到小的
        for(int j=0;j<n;j++){
            if(i==s[j])
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
    return 0;
}
```

另外需要注意的是：不开 ```long long``` 见祖宗。

其实本题还有另一种做法。任意一元函数，可以看作某个二元方程的解集的映射，只要在输出每个位置时判断这个位置的 $x$ 和 $y$ 是否符合 $y=\operatorname{f}(x)$ 即可。但这太浪费时间了，不TLE都对不起出题组。于是这个想法刚一萌生就被我摒弃。

本题解作者是个大蒟蒻，才上初一，CSP-J连初赛都过不了，难免有一些错误的地方，希望看到的大佬指正。

---

## 作者：____someone____ (赞：2)

## Description:

[$\text{\color{orangered}题目传送门}$](https://www.luogu.com.cn/problem/P8924)

[$\text{\color{orange}更好的食用效果}$](https://www.luogu.com.cn/blog/666someonebk999/solution-at-p8924)

题目大意：给一个函数，让你画出它在第一象限（包含坐标轴）的图像。

## Solution:

~~真正的签到题~~，直接模拟就可以。

首先，我们可以定义一个函数 $\operatorname{f}(x)$ 用来求出这个函数的函数值，然后就可以按照题意进行循环模拟了。

如果 $\operatorname{f}(x)$ 等于 $y$，则输出 `*`；反之，输出 `.`。

注意：因为 $y$ 轴的正方向是向上的，所以**外层循环要从大往小循环**。

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=10;
int n,m,k,a[M];

int f(int x)
{
	int ans=0;  //记得初值赋0 
	for(int i=1;i<=k+1;i++)
		ans+=a[i]*pow(x,i-1);  //求函数值 
	return ans;
}

int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=k+1;i++)
		cin>>a[i];
	for(int y=m-1;y>=0;y--)  //从m-1到0，因为要包含坐标轴 
	{
		for(int x=0;x<n;x++)  //同上 
		{
			if(f(x)==y)cout<<'*'; 
			else cout<<'.';
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Perfect Math Class](https://www.luogu.com.cn/problem/P8924)
## 思路分析
题意：给出一个次数 $\le7$ 的函数解析式，画出它的[函数图像](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E5%9B%BE%E5%83%8F/514135?fr=aladdin)（链接来自百度百科）。

由于此处的 $n$ 很小（$\le100$），所以可以直接暴力求出每个 $x$ 对应的 $f(x)$，那么 $(x,f(x))$ 处的点就标 `*`。

本题中的 $|f(x)|$ 最大只有 $12\times100^7$ 也就是 $10^{15}$ 级别而已，所以 `long long` 范围可以存下，而且 $\notin[0,m-1]$ 的 $f(x)$ 要舍去。
## 细节处理
- 本题的的 $x,y\in[0,n-1]$。
- 本题在输出时是倒着输出的，所以 $y$ 的值变为 $m-i-1$。
- 要开 `long long`。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[10];
long long ans[105];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<=k;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++)
	{
		long long p=1,y=0;//要开 long long 
		for(int j=0;j<=k;j++) 
		{
			y+=p*a[j];//求 f(x) 
			p*=i;
		}
		ans[i]=y;
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(ans[j]==m-i-1)//倒着输出 
				putchar('*');
			else
				putchar('.');
		}
		putchar('\n');
	}
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：Daidly (赞：1)

记 `ans[x][y]` 为最终的答案，则初始时 `ans[x][y]='.'`。

对每一个 $x\in[0,n-1]$ 按函数计算出对应的 $y$，判断是否在 $[0,m-1]$ 内，若是则 `ans[x][y]='*'`。

- 记得开 `long long`；

- 我这里提前预处理了 $x^i$，不预处理也没事。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

const int N=1e2+5;
char ans[N][N];
int n,m,k,a[N],p[N][N];

int calc(int x){
	int y=0;
	for(int i=0;i<=k;++i){
		y+=a[i]*p[x][i];
	}
	return y;
}

signed main(){
	n=read(),m=read(),k=read();
	for(int i=0;i<=k;++i)a[i]=read();
	for(int i=0;i<n;++i){
		p[i][0]=1;
		for(int j=1;j<=k;++j)p[i][j]=p[i][j-1]*i;
	}
	for(int x=0;x<n;++x){
		for(int y=0;y<m;++y)ans[x][y]='.';
	}
	for(int x=0;x<n;++x){
		int y=calc(x);
		if(y>=0&&y<=m-1)ans[x][y]='*';
	}
	for(int y=m-1;y>=0;--y){
		for(int x=0;x<n;++x)printf("%c",ans[x][y]);putchar('\n');
	}
	return 0;
}
```
如果觉得有帮助就点个赞吧。

---

## 作者：小明小红 (赞：1)

# P8924 Perfect Math Class题解

~~说句题外话，这次比赛对于本蒟蒻来说真的好难啊！！！~~

在考场上做了一道题，这道题最主要的难点就是函数，有些人没学过函数，不过理解一下还是可以做的，最主要这数据较水，很舒服就过去了，上思路。

**简化题意**：给定 $a$ 数组为系数，带入不同的 $x$ 求多项式的值并在图上第 $x$ 列从下往上第 $f(x)$ 个位置标记点，最后输出 $m$ 行每行 $n$ 个字符。

**主要思路**：用数组记录下输入的 $a$ 各项，然后带入 $x$ 求值记录在二维数组中，最后输出即可，整体来说是小暴力。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,k,a[19];     //输出m行每行n个字符 
bool mapp[109][109];//注意a数组是存输入的，mapp数组是记录结果的 
int main()                    
{
	cin>>n>>m>>k;
	for(ll i=0;i<=k;i++)
	{
		cin>>a[i];
	}
	for(ll i=0;i<n;i++)
	{
		ll ans=0;
		for(ll j=0;j<=k;j++)
		{
			ans+=pow(i,j)*a[j];//最重要的，带入x求f(x)的结果再乘上系数累加即可 
		}
		if(ans<=105&&ans>=0)//注意特判了一下，没有这个特判只有十分 
			mapp[ans][i]=1; //特判函数算出来的在输出范围内 
	}
	for(ll i=m-1;i>=0;i--)//输出，注意这个m是逆序 
	{
		for(ll j=0;j<n;j++)
		{
			if(mapp[i][j]==1)//将mapp转换为字符 
			{
				cout<<"*";
			}
			else
			{
				cout<<".";
			}
		}
		cout<<endl;
		
	}
	return 0;
 } 
```


---

## 作者：lelml (赞：1)

赛时第一发居然挂了qwq。

思路：我们都知道，函数中一个 $x$ 只能对应一个 $f(x)$，所以只需要按照题目中给的 $x$ 的范围 $0 \le x \le n-1$ 算出所有整数 $x$ 对应的 $f(x)$，判断是否满足 $0 \le f(x) \le m-1$ 存在一个二维数组中，最后以字符矩阵的形式输出即可。

### Talk is cheap, Show me the code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,f[101],g[101][101];
int calc(int x){
	int ans=0;
	for(int i=0;i<=k;i++){
		int tmp=1;
		for(int j=1;j<=i;j++) tmp*=x;
		ans+=tmp*f[i];
	}
	return ans;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++) cin>>f[i];
	for(int i=0;i<n;i++){
		if(calc(i)<=m-1&&calc(i)>=0) g[calc(i)][i]=1;
	}
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<n;j++){
			if(g[i][j]==0) cout<<'.';
			else cout<<'*';
		}
		cout<<endl;
	}
}
```


---

## 作者：JackMerryYoung (赞：0)

# 前言

老年选手没打但是口胡。

# 正文

大意是给你一个 $K$ 次函数，让你画出函数图像（整点）。

看到数据范围如此之小，直接上模拟呗。

我们开一个 $N \times M$ 的字符数组，做完直接输出。

直接先全初始化为点，然后枚举第 $i$ 个点, $\mathcal{O}(K)$ 求这个点的函数值，

再判断这个函数值是否超出 $M$, 没超出就去涂色，超出画板范围就忽略。

复杂度 $\mathcal{O}(N (M + K))$. 不会有人无聊到用快速幂吧。

注意这个函数图像是数学的坐标轴，即 y 轴正方向为上, x 轴正方向为右，不要被坑了。

还有要开 `__int128_t`.

# 代码

其实看看题解区大佬的实现就行，这里不放了。

# 后言

以后看到数据范围较小，就直接上暴力、模拟或状压。

---

## 作者：IOI_AK_LHY (赞：0)

## 前言

[题目传送门](https://www.luogu.com.cn/problem/P8924)。

[在博客内食用效果更佳](https://www.luogu.com.cn/blog/749988/solution-p8924)！

## 题目分析

这道题目考察了关于函数的知识，~~数学好的OIers们就很快能做出来~~。

首先我来讲一下本题最重要的判断条件。

设一个函数 $f(x)=2x^2 + \dfrac{1}{2}x + 3$，则**对于每一个 $x$，都有唯一的 $y$ 与其对应。** 这就是函数的映射，也就是自变量与函数值的对应。

对于上面那个函数，当 $x=1$ 时，$y=2 \times 1^2 + \dfrac{1}{2} \times 1 + 3 = 2 + \dfrac{1}{2} + 3 = \dfrac{11}{2}$，即这个函数的图像过点 $(1,\dfrac{11}{2})$。同理，可得到此函数图像也过点 $(2,12)$。

下图是函数 $f(x)=2x^2 + \dfrac{1}{2}x + 3$ 的图像（工具：[desmos](https://www.desmos.com/calculator?lang=zh-CN)）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ln2qfxpl.png)

那么，现在我们已经了解自变量与函数值的对应了，那么这道题就差不多做完了。

先来放上最重要的判断条件代码。

```cpp
for(int i=0;i<n;i++) //这里就用i来代替x了
	for(int j=0;j<m;j++){
		long long y=0;
		for(int l=0;l<=k;l++)
			y+=a[l]*pow(i,l); //这里将x对应的函数值y求出来
		if(y==j)
			ans[i][j]='*'; //如果x,y符合函数的对应关系，那么点(x,y)在函数图像上，这个点就是‘*’。
		else
			ans[i][j]='.'; //否则就是‘.’
	}
```

想必大家都已经懂这段代码的意思了。

接下来我们来处理输出的问题。

因为数组的 `[0][0]` 在左上角，而平面直角坐标系的 $(0,0)$ 在左下角，所以我们输出答案的时候要逆时针旋转 $90$ 度。具体操作如下：

```cpp
for(int i=n-1;i>=0;i--){
	for(int j=0;j<m;j++)
		cout<<ans[j][i];
	cout<<endl;
}
```

现在，整个代码已经出来了。

## 代码实现

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,m,k,a[10];
char ans[105][105];
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			int y=0;
			for(int l=0;l<=k;l++)
				y+=a[l]*pow(i,l);
			if(y==j)
				ans[i][j]='*';
			else
				ans[i][j]='.';
		}
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<m;j++)
			cout<<ans[j][i];
		cout<<endl;
	}
	return 0;
}
```

题解制作不易，希望能够帮助到大家！

---

## 作者：Strelizia_Qy (赞：0)

# **思路**：

注意到数据范围：$n,m\le100$。

所以我们可以遍历每一个点 $\left(x,y\right)$，将 $x$ 带入函数 $f(x)$ 计算（函数每一项的系数用数组存起来），判断是否满足：如果 $f(x)=y$，说明函数图像经过该点，输出 ` * ` 。否则函数图像不过该点，输出 ` . ` 。

- $f(x)$ 可能会超过 `int` 范围，要开 `long long` 。
- 题目要求输出**从下往上**，所以遍历行数时要倒着来（即：从 $n-1$ 到 $0$ ）


# **AC代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
int n,m,k,a[10];
bool check(int x,int y)//验证点 (x,y) 是否在函数图像上 
{
	ll ans=0;//不开 long long 见祖宗 
	for(int i=0;i<=k;i++)ans+=pow(x,i)*a[i];//计算 f(x)
	if(ans==y)return 1;
	else return 0;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++)cin>>a[i];
	for(int i=n-1;i>=0;cout<<endl,i--) 
	{
		for(int j=0;j<m;j++)
		{
			if(check(j,i))cout<<"*";
			else cout<<".";
		}
	}
    return 0;
}
```


---

## 作者：sgl654321 (赞：0)

### 题目大意
给定 $k$ 次函数 $f(x)=a_kx^k+a_{k-1}x^{k-1}+\cdots+a_0$，在一个 $n\times m$ 的矩阵中画出其图像。
### 解题思路
简单模拟题。定义答案矩阵 $ans[i][j]$，标记当 $x=i$ 时 $f(x)$ 是否等于 $j$，如果是则为 $1$，不是则为 $0$。

遍历 $[0,n-1]$ 中所有横坐标 $x$，并求出 $f(x)$。 把矩阵中 $ans[x][f(x)]$ 标记为 $1$。

最后遍历 $i\in[0,m-1] $，$j\in[0,n-1]$。如果 $ans[j][i]=1$，则输出 ```*```，否则输出 ```.```。

等等，真的这样就可以了吗？

测试一下大样例，发现出现了 RE。RE 通常有两种情况：一是除数为 $0$，二是数组越界。这一题不涉及除法，那就是第二种情况。

我们发现，当函数的次数和系数较大时，随着 $x$ 的增大，$f(x)$ 的增长是很快的。过了不久， $f(x)$ 就会超过 $m-1$。所以要特判一下。

还有，观察数据范围我们发现 $a_i$ 的值可能为负数。所以函数值 $f(x)$ 也有可能是负数。这个也得特判一下。

加上这两个特判就可以了！
### 参考代码
这里规定如果 $f(x)<0$ 或者 $f(x)>m-1$，则将 $f(x)$ 返回 $m+2$，作为一种特判。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,ans[110][110],a[110];
long long y;
long long f(long long x){
	long long ret=0;
	for(int i=0;i<=k;i++){
		y=1;
		for(int j=1;j<=i;j++)
			y=y*x;
		ret+=y*a[i];
	}
	if(ret<0)return m+2; 
	if(ret>m)return m+2;
//	cout<<x<<" "<<ret<<endl;
	return ret;

}
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<=k;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		ans[i][f(i)]=1;
	for(int i=m-1;i>=0;i--){
		for(int j=0;j<n;j++)
			if(ans[j][i]==1)
				cout<<"*";
			else cout<<".";
		cout<<endl;
	}
		
	return 0;
}
```

---

## 作者：I_AK_CTSC (赞：0)

这道题大家可以模拟。
# 思路分析
这道题我们就是根据题目中给的公式去枚举 $x$ ，从而得出每一个 $f(x)$ 的值就可以了。然后对于平面直角坐标系 $(x,f(x))$ 这个点进行标记即可。

但是我们要考虑到由于数组的存储方式与函数的存储方式不同。

什么意思呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/g4ba22yl.png)

当 $x = 0$ 的时候，数组中存储位置为左上角，但是平面直角坐标系中存储位置是右下角，所以我们要改变横坐标的值。

我们很明显发现当数组中存储的横坐标值为 $x$ 时，在数组里时 $n-x-1$ ，然后再进行标记即可啦。

当然，当 $n-x-1$ 的值小于零的时候，就可以不操作了，毕竟再操作也超出范围了，还不如不操作，省省时间。

综上分析，本题结束。

代码如下：

```cpp
#include <iostream>
#include <cstdlib>

using namespace std;
typedef long long ll;
ll a[105];
char ch[1005][1005];
void init()//先进行预处理
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			ch[i][j] = '.';
		}
	}
	return;
}
int main()
{
	init();
	ll n, m;
	cin >> n >> m;
	ll k;
	cin >> k;
	for (ll i = 0; i <= k; ++i)
	{
		cin >> a[i];
	}
	for (int i = 0; i < m; ++i)
	{
		ll j;
		j = 0;
		ll l = 1;
		for (int p = 0; p <= k; ++p)
		{
			j += l * a[p];
			l *= i;
		}
		ll o = n - j - 1;//这里才是真正要存储的横坐标
		if (o < 0)//小于零了，就不做了
		{
			break;
		}
		ch[o][i] = '*';
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cout << ch[i][j];
		}
		cout << endl;//别忘了换行
	}
	return 0;
}
```

最后附上一句名言：

不贵于无过,而贵于能改过。——王守仁

---

## 作者：strcmp (赞：0)

**题目大意：** 给定 $n,\,m,\,k$ 和一个 $k$ 次的多项式 $f = a_kx^k + \cdots +a_0$，要求将这个多项式经过的所有整点画在一个 $n \times m$ 的矩阵上，规定其定义域为 $[0,\,n - 1]$，值域为 $[0,\,m - 1]$。

### Solution

注意到，因为横坐标为整数是 $(x,\,y)$ 为整点的必要条件，所以对于经过整点的多项式 $f(x)$，$x$ 只需要在 $\mathbb N$ 上进行考虑。这就使得我们可以通过遍历所有可能的 $x \in \mathbb N$ 的取值，来画出 $f(x)$ 经过的所有整点。

接下来，应当对 $f$ 进行程序上的实现。这个部分相对简单，每次将总和直接加上 $a_ix^i$ 即可。最坏情况下，总和不会超过 $1.3 \times 10^{15}$，所以开 ```long long``` 即可。

需要注意的是，在取出总和之后，如果总和大于 $m - 1$ 或者小于 $0$，则应当返回一个无效值，防止可能的越界情况。

题目没有明确说明的是，对于所有的输入数字，都保证是整数，所以可以放心得将 ```long long``` 都开上。（事实上，使用 ```double``` 也没有问题，其对于范围 $[0,\,m - 1]$ 内的整数是完全精确的）

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2e2 + 10;
ll n, m, k; ll a[maxn], yc[maxn]; 
char c[205][205];
ll f(ll x) {
    ll sum = 0; yc[1] = x;
    for (int i = 2; i <= 10; i++)yc[i] = yc[i - 1] * x;
    for (int i = 0; i <= k; i++) {
        sum += a[i] * yc[i];
    }
    if (sum > m - 1 || sum < 0)return -1;
    return sum;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(); cout.tie(); cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = '.';
        }
    }
    for (int i = 0; i <= k; i++)cin >> a[i]; yc[0] = 1;
    for (int i = 0; i < n; i++) { 
        ll d = f(i);
        if (d == -1)continue;
        //当函数值为无效值时应当直接跳过
        c[d][i] = '*'; 
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            cout << c[i][j];
        }
        cout << "\n";
    }//对于输出顺序建议自己尝试
    return 0;
}
```




---

