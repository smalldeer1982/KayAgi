# Iahub and Xors

## 题目描述

Iahub does not like background stories, so he'll tell you exactly what this problem asks you for.

You are given a matrix $ a $ with $ n $ rows and $ n $ columns. Initially, all values of the matrix are zeros. Both rows and columns are 1-based, that is rows are numbered 1, 2, ..., $ n $ and columns are numbered 1, 2, ..., $ n $ . Let's denote an element on the $ i $ -th row and $ j $ -th column as $ a_{i,j} $ .

We will call a submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ such elements $ a_{i,j} $ for which two inequalities hold: $ x_{0}<=i<=x_{1} $ , $ y_{0}<=j<=y_{1} $ .

Write a program to perform two following operations:

1. Query( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ ): print the xor sum of the elements of the submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ .
2. Update( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ ): each element from submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ gets xor-ed by value $ v $ .

## 说明/提示

After the first $ 3 $ operations, the matrix will look like this:

```
1 1 2
1 1 2
3 3 3
```
The fourth operation asks us to compute 1 xor 2 xor 3 xor 3 = 3.

The fifth operation asks us to compute 1 xor 3 = 2.

## 样例 #1

### 输入

```
3 5
2 1 1 2 2 1
2 1 3 2 3 2
2 3 1 3 3 3
1 2 2 3 3
1 2 2 3 2
```

### 输出

```
3
2
```

# 题解

## 作者：SunsetSamsara (赞：11)

## 思路 & 前置知识
二维树状数组模板题
## 分析
还是和普通二维树状数组一样，开始~~愉快的~~推式子

我们令 $d_{i,j}$ 为这个二维数组的差分数组（注意这里是异或意义的差分数组而不是平常意义的差分数组），则对 $(a,b)$ 到 $(x,y)$ 的异或和就是：
$$\sum\limits_{a\le i\le x}^{\operatorname{xor}}\sum\limits_{b\le j\le y}^{\operatorname{xor}}\sum\limits_{1\le p\le i}^{\operatorname{xor}}\sum\limits_{1\le q\le j}^{\operatorname{xor}}d_{p,q}$$

发现对于每个 $d_{p,q}$ 出现了 $(x-\max\{a,p\}+1)(y-\max\{b,q\}+1)$ 次。又因为异或具有性质 $a \operatorname{xor} a=0$，所以只要关注 $(x-\max\{a,p\}+1)(y-\max\{b,q\}+1)$ 的奇偶性就可以了。

最后，因为 $(x-\max\{a,p\}+1)(y-\max\{b,q\}+1)$ 的奇偶性和下标奇偶性有关，所以只要维护四个二维树状数组即可。其它就是普通树状数组了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lld long long
#define lowbit(x) ((x)&-(x))
lld dif[2][2][1001][1001];//每种奇偶性的树状数组
int n,m;
void update(int x,int y,lld c){
	for(int i=x,j;i<=n;i+=lowbit(i))
		for(j=y;j<=n;j+=lowbit(j))
			dif[x&1][y&1][i][j]^=c;//异或上c,不是加上c
}
lld sum(int x,int y){
	lld ans=0;
	for(int i=x,j;i>=1;i-=lowbit(i))
		for(j=y;j>=1;j-=lowbit(j))
			ans^=dif[x&1][y&1][i][j];//异或上这个值,不是加上这个值
	return ans;
}
int main(){
	int op,x1,y1,x2,y2;
	long long w;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d%d%d%d",&op,&x1,&y1,&x2,&y2);
		if(op==1){
			printf("%lld\n",sum(x2,y2)^sum(x2,y1-1)
							^sum(x1-1,y2)^sum(x1-1,y1-1));//和模板几乎相同
		}else{
			scanf("%lld",&w);
			update(x1,y1,w);
			update(x1,y2+1,w);
			update(x2+1,y1,w);
			update(x2+1,y2+1,w);//修改，与模板完全相同
		}
	}
}
```

---

## 作者：Tobiichi_Origami (赞：7)

**前言**：此题是一道二维树状数组练习题，若没有了解过请先做[上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514)

------------

我们先考虑，整个矩阵的异或和为 $\displaystyle\bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}a_{i,j}$ （$a_{i,j}$ 为原矩阵元素）

根据差分数组我们还可以得出 $\displaystyle a_{i,j}=\bigoplus_{k=1}^{i}\bigoplus_{l=1}^{j}d_{k,l}$ （$d_{i,j}$ 为差分数组）

所以便可以得出，整个矩阵的异或和即为

$$\displaystyle\bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}\bigoplus_{k=1}^{i}\bigoplus_{l=1}^{j}d_{k,l}$$

![](https://cdn.luogu.com.cn/upload/image_hosting/vv0g9am3.png)

如此图，我们可以发现，后两个循环即为用线段标出的位置的异或和，所以这个式子就可以变为

$$\displaystyle\bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}\bigoplus_{k=1}^{(n-i+1)(n-j+1)}d_{i,j}$$

那这时，我们由该如何化简呢？

我们想一下异或的性质，$\forall x\in R ,x\oplus x=0,x\oplus 0 =x$

所以如果 $d_{i,j}$ 一直异或的话，如果次数为奇数，那么所得出的答案不为 $0$，也就被认为是有意义的，所以我们便要使 $(n-i+1)(n-j+1)$ 为奇数（至于前面的 $n^{2}$ 无论它为奇还是偶，只要后面的 $(n-i+1)(n-j+1)$ 为奇数，答案便有意义）。

所以这时，我们就可以建出 $4$ 种状态的树状数组，每次更新和查询就用前缀和和差分的方式进行维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2050;
int t[2][2][N][N];
int n,m;
char op[2];
int lowbit(int x){
	return x&-x;
}
void insert(int x,int y,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			t[x%2][y%2][i][j]^=val;
	return ;
}
int query(int x,int y)
{
	int res=0;
	for(int i=x;i>0;i-=lowbit(i))
		for(int j=y;j>0;j-=lowbit(j))
			res^=t[x%2][y%2][i][j];
	return res;
}
int main()
{
	scanf("%d %d",&n,&m);
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int a,b,c,d;
			scanf("%d %d %d %d",&a,&b,&c,&d);
			printf("%d\n",query(c,d)^query(a-1,d)^query(c,b-1)^query(a-1,b-1));
		}
		if(op==2)
		{
			int a,b,c,d,val;
			scanf("%d %d %d %d %d",&a,&b,&c,&d,&val);
			insert(a,b,val);
			insert(c+1,b,val);
			insert(a,d+1,val);
			insert(c+1,d+1,val);
		}
	}
	return 0;
}
```


---

## 作者：daiarineko (赞：6)

## Link - 链接

[Luogu RMJ CF341D](https://www.luogu.com.cn/problem/CF341D)  
[CF 341D](http://codeforces.com/problemset/problem/341/D)

## Description - 题目简述

维护一个数据结构，支持二维区间异或、区间查询异或和。

## Solution - 题解

我爱数据结构！（bushi

看起来很难，其实比较好写。

### 修改

考虑维护差分数组，这样修改就是 $\Theta(1)$ 的。

若是加法意义下的，需要特别分析加和减，不要用错：![图炸了？联系 qidirj 补图](https://cdn.luogu.com.cn/upload/image_hosting/lzxk98y2.png)

但这题是异或意义下的，异或的逆运算是异或，所以容易做：![图炸了？联系 qidirj 补图](https://cdn.luogu.com.cn/upload/image_hosting/l2g5s45g.png)

（画技太渣，还请见谅）

### 查询

单点查询是很容易的，就相当于在差分数组上求前缀和。

那么区间如何查询呢？

考虑一种暴力的方法。为了避免 Github 不支持 LaTeX 引发的惨案，转成图片（c 为差分数组）：

$$\bigoplus_{i=1}^{x}\bigoplus_{j=1}^{y} a_{x,y} =\bigoplus_{i=1}^{x}\bigoplus_{j=1}^{y}\bigoplus_{k=1}^i\bigoplus_{l=1}^j c_{k,l}$$

通过分析，可以进一步简化：

$$=\bigoplus_{i=1}^{x}\bigoplus_{j=1}^{y}\bigoplus_{k=1}^{(x-i+1)(y-j+1)}c_{i,j}$$

用这张图感性理解一下，就是位于 $(i,j)$ 的数值会被异或 $(x-i+1)(y-j+1)$ 次：  
![图炸了？联系 qidirj 补图](https://cdn.luogu.com.cn/upload/image_hosting/ejahcgwv.png)

继而，根据异或的性质 $a\oplus a = 0 , b \oplus 0 = b$，可以得到：  
仅当 $x$ 和 $i$ 同为奇数或同为偶数时才能对答案做出贡献，对于 $y$ 和 $j$，同理。

因此，我们分别按照 $x,y$ 的奇偶性维护 $2\times2=4$ 个差分树状数组。

时间复杂度：$\Theta(m \log_2^2 n)$，可以通过本题。

### 示例代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1024, maxm = 102400;
int n, m;
int t[2][2][maxn][maxn];
int lowbit(const int &x)
{
    return x & (-x);
}
void update(const int &x, const int &y, const int &w)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            t[x & 1][y & 1][i][j] ^= w;
}
int query(const int &x, const int &y)
{
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ans ^= t[x & 1][y & 1][i][j];
    return ans;
}
signed main()
{
    int op, x, y, xx, yy, v;
    scanf("%lld%lld", &n, &m);
    while (m--)
    {
        scanf("%lld%lld%lld%lld%lld", &op, &x, &y, &xx, &yy);
        if (op == 2)
        {
            scanf("%lld", &v);
            update(xx + 1, yy + 1, v);
            update(x, yy + 1, v);
            update(xx + 1, y, v);
            update(x, y, v);
        }
        else
        {
            printf("%lld\n", query(xx, yy) ^ query(x - 1, yy) ^ query(xx, y - 1) ^ query(x - 1, y - 1));
        }
    }
    return 0;
}
```


---

## 作者：Qiiiiiii_ (赞：4)

前置知识：二维树状数组(区间修改，区间查询)

二维树状数组例题：[上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514)

若已过上述例题，则本题可视为水题通过。

若未过上述例题，则本题解介绍一下异或意义下的二维树状数组。

类似于普通二维树状数组，我们先定义一个异或意义下的差分: $d[i][j]=a[i][j]$^$a[i-1][j]$^$a[i][j-1]$^$a[i-1][j-1]$ ($a[i][j]$原矩阵内的数)。再重定义求和符号 :$\displaystyle \sum_{i=1}^x \sum_{j=1}^y d[i][j]=d[1][1]$^$d[1][2]$^...^$d[1][y]$ ^$d[2][1]$^$d[2][2]$...^$d[2][n]$ ......$d[n][1]$^$d[n][2]$^...$d[n][n]$ 。(以下所有的求和符号皆为重定义后的意义)定义 a ** b 表示b^b^b...^b (b自异或a次)。显然，自异或奇次为自己，自异或偶次为0 。


那么，$\displaystyle a[x][y]=\sum_{i=1}^x \sum_{j=1}^y d[i][j]$。证明：

因为$d[i][j]=a[i][j]$ ^ $a[i-1][j]$^$a[i][j-1]$ ^ $a[i-1][j-1]$.

所以 $a[x][y]=$ $\displaystyle \sum_{i=1}^x \sum_{j=1}^y a[i][j]$ ^ $  \displaystyle\sum_{i=1}^{x-1} \sum_{j=1}^y a[i][j]$ ^ $ \displaystyle\sum_{i=1}^x \sum_{j=1}^{y-1} a[i][j]$ ^ $\displaystyle\sum_{i=1}^{x-1} \sum_{j=1}^{y-1} a[i][j]$ 。

定义前缀和, $s[x][y]=\displaystyle \sum_{i=1}^x \sum_{j=1}^y a[i][j]$ 。

我们将 $\displaystyle a[x][y]=\sum_{i=1}^x \sum_{j=1}^y d[i][j]$ 带入得 $s[x][y]=$ $\displaystyle [(x+1) * (y+1)] $ ** $ \sum_{i=1}^x \sum_{j=1}^y d[i][j]$ ^ $\displaystyle (y+1) $ ** $ \sum_{i=1}^x \sum_{j=1}^y i $ ** $ d[i][j]$ ^ $\displaystyle (x+1) $ ** $\sum_{i=1}^x \sum_{j=1}^y j $ ** $ d[i][j]$ ^ $\displaystyle \sum_{i=1}^x \sum_{j=1}^y (i * j)$ ** $d[i][j]$ 。

开4颗树状数组维护 $d[i][j]$ , $i $ ** $ d[i][j]$ , $j $ ** $ d[i][j],(i * j) $ ** $ d[i][j]$ 这四个值。（注意：在树状数组中，加号被重定义为 ^ 号）。

(以下符号与原题无关，仅与重定义后的树状数组有关)

这里阐述一下树状数组所维护的东西: 对于定义在此树状数组下的矩阵 $v$ ，其各值分别为 $v[i][j]$,我们使用树状数组 $w[i][j]$ 维护其前缀异或和.对于一次询问$ask(x,y)$，我们的返回值 $\displaystyle ask(x,y)=\sum_{i=1}^x \sum_{j=1}^y v[i][j]$ ，即将 $(x,y)$ 在树状数组中的管辖范围内的所有 $w[i][j]$ 异或和。对于此树状数组下的一次修改"$add(x,y,k)$(即$v[x][y]->v[x][y]$^$k$)"，我们修改了所有包含 $(x,y)$ 的 $w[i][j]$ 值，使其异或 $k$ .

我们在原题中需要用此重定义的树状数组维护4个不同矩阵 $d[i][j]$ , $i $ ** $ d[i][j]$ , $j $ ** $ d[i][j],(i * j) $ ** $ d[i][j]$ 的前缀异或和。

时间复杂度 $O(mlog^2n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define dl double
#define re register
#define LL inline ll
#define I inline int
#define V inline void
#define gc getchar()
#define FOR(i,a,b) for(re int i=(a) , i##i=(b) ; i<=i##i ; ++i)
#define ROF(i,a,b) for(re int i=(a) , i##i=(b) ; i>=i##i ; --i)
using namespace std;
const int N=1050;
LL read(){
	ll p=0,w=0;
	char ch=gc;
	while(!isdigit(ch)) w=ch=='-'?1:0,ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
ll n,m,d[N][N];
struct ao{
	ll s[N][N];
	I lowbit(int x){ return x&(-x);}
	V add(int x,int y,ll k){
		if(!x||!y||!k) return ;
		for(re int i=x;i<=n;i+=lowbit(i))
			for(re int j=y;j<=n;j+=lowbit(j))
				s[i][j]^=k;
	}
	LL ask(int x,int y){
		ll as=0;
		for(re int i=x;i;i-=lowbit(i))
			for(re int j=y;j;j-=lowbit(j))
				as^=s[i][j];
		return as;
	}
}a,ai,aj,aij;
V add(int x,int y,ll k){ a.add(x,y,k),ai.add(x,y,k*(x&1)),aj.add(x,y,k*(y&1)),aij.add(x,y,k*(x*y&1));}
V add(int x1,int y1,int x2,int y2,ll k){ add(x1,y1,k),add(x2+1,y1,k),add(x1,y2+1,k),add(x2+1,y2+1,k);}
LL ask(int x,int y){ return ((x+1)*(y+1)&1)*a.ask(x,y)^((y+1)&1)*ai.ask(x,y)^((x+1)&1)*aj.ask(x,y)^aij.ask(x,y); }
LL ask(int x1,int y1,int x2,int y2){ return ask(x2,y2)^ask(x2,y1-1)^ask(x1-1,y2)^ask(x1-1,y1-1); }
int main (){
	int cz,x1,y1,x2,y2,k;
	n=read(),m=read();
	FOR(i,1,m){
		cz=read();
		if(cz==2) x1=read(),y1=read(),x2=read(),y2=read(),k=read(),add(x1,y1,x2,y2,k);
		else x1=read(),y1=read(),x2=read(),y2=read(),printf("%d\n",ask(x1,y1,x2,y2));
	}
	return 0;
}
```


---

## 作者：mlvx (赞：3)

### 题意

两种操作，对子矩阵进行异或，以及求子矩阵的异或和。

### 分析

令 $d_{i,j}=a_{i,j}\oplus a_{i-1,j}\oplus a_{i,j-1}\oplus a_{i-1,j-1}$，即异或意义下的差分数组（下文的差分均表示异或意义下的差分）。

由差分的定义可知，$a_{i,j}=\bigoplus\limits_{p=1}^i\bigoplus\limits_{q=1}^j d_{p,q}$。


故 $\bigoplus\limits_{i=1}^x\bigoplus\limits_{j=1}^y a_{i,j}=\bigoplus\limits_{i=1}^x\bigoplus\limits_{j=1}^y\bigoplus\limits_{p=1}^i\bigoplus\limits_{q=1}^j d_{p,q}$。

注意到 $d_{i,j}$ 被异或了 $(x-i+1)(y-j+1)$ 次，由于异或的性质，$x\oplus x=0$，所以我们只需要关注 $(x-i+1)(y-j+1)$ 的奇偶性即可。

易知仅当 $x,i$ 同奇偶，$y,j$ 同奇偶时 $d_{i,j}$ 才有贡献。

故把原来的二维树状数组再加上两维，一个表示当前 $x$ 的奇偶，一个表示当前 $y$ 的奇偶。

### 代码

```cpp#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1100;
int n,q,op,a,b,c,d;ll k,tr[2][2][N][N];
int lbt(int x){return x&(-x);}
void add(int x,int y,ll v){for(int i=x;i<=n;i+=lbt(i))for(int j=y;j<=n;j+=lbt(j))tr[x&1][y&1][i][j]^=v;}
ll query(int x,int y,ll ret=0){for(int i=x;i;i-=lbt(i))for(int j=y;j;j-=lbt(j))ret^=tr[x&1][y&1][i][j];return ret;}
int main(){
	ios::sync_with_stdio(0);cin.tie(),cout.tie();
	cin>>n>>q;
	while(q--){
		cin>>op>>a>>b>>c>>d;
		if(op==1)cout<<(query(a-1,b-1)^query(a-1,d)^query(c,b-1)^query(c,d))<<'\n';
		else cin>>k,add(a,b,k),add(a,d+1,k),add(c+1,b,k),add(c+1,d+1,k);
	}return 0;
}
```

---

## 作者：partychicken (赞：2)

二维树状数组+差分就解决了

~~树套树是不可能树套树的，这辈子都不可能树套树的~~

另：提供某些思路

1.扫~~猫~~ ~~喵~~线（打不出来了，自己意会）加线段树

2.各种树套树（推荐线段树套线段树，有大佬愿意写平衡树我也不反对，本蒟蒻很期待红黑树套红黑树的题解）

3.CDQ分治+线段树（树状数组）（CDQ到现在也没学会，羡慕那些什么题都用CDQ消掉一维的dalao）

4.CDQ套CDQ （CDQ不会的，转去百度 [传送门](www.baidu.com)）

5.暴力（不同于以上做法的是，这种做法期望得分0分）

6.输出样例（逃

7.~~抄题解，划掉划掉~~

异或并不能直接累加啊。。。根据结论，一维树状数组开俩
，于是二维，开四个就好了,每次操作看修改哪个。
```
#include<bits/stdc++.h>
   
#define ll long long
  
using namespace std;  

const int maxn=1000+10;  

ll C[4][maxn][maxn];  

inline int lowbit(int x)  
{  
    return x&(-x);  
}  

int getw(int x,int y)  
{  
    int res=0;  
    if(x&1) res+=1;  
    if(y&1) res+=2;  
    return res;  
}  

void update(int x,int y,ll v)  
{  
    int wh=getw(x,y);  
    for(int i=x;i<maxn;i+=lowbit(i))
	{
		for(int j=y;j<maxn;j+=lowbit(j)) 
		{
			C[wh][i][j]^=v; 
		}   
	}     
}  

ll query(int x,int y)  
{  
    int wh=getw(x,y);
    ll res=0;
    for(int i=x;i>0;i-=lowbit(i))
	{
		for(int j=y;j>0;j-=lowbit(j))  
		{
			res^=C[wh][i][j];
		}
	}        
    return res;
}
  
int main()  
{   
    ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m;  
    memset(C,0,sizeof(C));  
    cin>>n>>m; 
    int x1,y1,x2,y2,p;  
    ll v;  
    while(m--)  
    {  
        cin>>p;
        cin>>x1>>y1>>x2>>y2;  
        if(p==1)  
        {  
            ll res=query(x2,y2);  
            res^=query(x2,y1-1);  
            res^=query(x1-1,y2);  
            res^=query(x1-1,y1-1);  
            cout<<res<<endl; 
        }  
        else  
        {  
            cin>>v;  
            update(x1,y1,v);  
            update(x1,y2+1,v);  
            update(x2+1,y1,v);  
            update(x2+1,y2+1,v);  
        }  
    }  
    return 0;  
}  
```

---

## 作者：Hoks (赞：2)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF341D)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf341d)内食用应该不会更佳。

前置芝士：[p4514上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514)。

## 思路分析
延续前置芝士中的二维树状数组，本篇题解也是二维树状数组写法。
### 区间修改
首先考虑一维树状数组的情况，值周所众，一维树状数组是使用差分求区间和的。

而前置芝士中采取了二维差分求子矩阵和的方法，所以由此我们联想到这题能否用二维差分。举个栗子，对如下全 $0$ 的矩阵而言。

$\begin{array}{c}
0 & 0 & 0 &0 & 0 \\
0 & 0 & 0 &0 & 0 \\
0 & 0 & 0 &0 & 0 \\
0 & 0 & 0 &0 & 0 
\end{array}$

给中间的 $2 \times 3$ 的矩阵异或上 $x$ 即可得到新的差分矩阵。

$\begin{array}{c}
0 & 0 & 0 &0 & 0 \\
0 & x & 0 &0 & x \\
0 & 0 & 0 &0 & 0 \\
0 & x & 0 &0 & x 
\end{array}$

因为这里是异或所以不用像前置芝士中一样将左下角和右上角加上的数取反。
### 区间查询
造完了二维树状数组接下去就是愉快的查询了，首先考虑暴力的写法的二维前缀和。

$$\sum\limits_{1\le i\le x}^{\operatorname{xor}}\sum\limits_{1\le j\le y}^{\operatorname{xor}}\sum\limits_{1\le p\le i}^{\operatorname{xor}}\sum\limits_{1\le q\le j}^{\operatorname{xor}}a_{p,q}$$
然后考虑拆开他，发现每个 $a_{p,q}$ 出现了 $(x-i+1)\times (y-j+1)$ 次。

又因为： $a\oplus a=0$。

所以答案是否异或 $a_{p,q}$ 只与 $(x-i+1)\times (y-j+1)$ 的奇偶性有关，考虑将前置芝士中的四个树状数组变为四个奇偶性不同的数组计算，即可得到与之前相同的操作了。

## 代码
```cpp
#include<bits/stdc++.h>
#define ec 114514
using namespace std;
int n,m;
int a[1010][1010][2][2];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int lowbit(int x){return x&-x;}
void add(int x,int y,int num)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			a[i][j][x&1][y&1]^=num;
}
int query(int x,int y)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		for(int j=y;j>=1;j-=lowbit(j))
			ans^=a[i][j][x&1][y&1];
	return ans;
}
signed main()
{
	n=read(),m=read();
	while(m--)
	{
		int zx,zy,yx,yy,d,op;
		op=read(),zx=read(),zy=read(),yx=read(),yy=read();
		if(op==2)
		{
			d=read();
			add(zx,zy,d),add(zx,yy+1,d),add(yx+1,zy,d),add(yx+1,yy+1,d);
		}
		else printf("%d\n",query(yx,yy)^query(zx-1,yy)^query(yx,zy-1)^query(zx-1,zy-1));
	}
	return 0;
}
```
完结撒花！

---

## 作者：forest114514 (赞：2)

### CF341D Iahub and Xors

二维树状数组板子

> 前置副本：**P4514 上帝造题的七分钟**
>
> 维护前缀和，列个式子（$a$ 是差分数组）
$$
> Sum(x0,y0)=\sum\limits_{x=1}^{x0}\sum\limits_{y=1}^{y0}\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{y}a_{i,j}
> $$
> 变个形状：
> $$
> Sum(x0,y0)=\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}\sum\limits_{x=1}^{x0}\sum\limits_{y=1}^{y0}[x\ge i][y\ge j]a_{i,j}
> $$
> 考虑对于每一个 $(i,j)$ 存在多少对 $(x,y)$，满足 $x\ge i,y\ge j$，显然有 $(x0-i+1)(y0-j+1)$ 对。
>
> 所以原式可写成：
 $$
> Sum(x0,y0)=\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}(x0-i+1)(y0-j+1)a_{i,j}$$
>$$=\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}(x0-i+1)(y0-j+1)a_{i,j}$$
>$$=(x0+1)(y0+1)\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}a_{i,j}-(y0+1)\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}i\times a_{i,j}-(x0+1)\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}j\times a_{i,j}+\sum\limits_{i=1}^{x0}\sum\limits_{j=1}^{y0}i\times j\times a_{i,j}
> $$
> 我们维护四个差分的树状数组就行了…….

同理，对于这道题，我们有
$$
xor(x0,y0)=\bigoplus\limits_{x=1}^{x0}\bigoplus\limits_{y=1}^{y0}\bigoplus\limits_{i=1}^{x}\bigoplus\limits_{j=1}^{y}a_{i,j}$$
$$ 
=\bigoplus\limits_{i=1}^{x}\bigoplus\limits_{j=1}^{y}\bigoplus\limits_{x=1}^{x0}\bigoplus\limits_{y=1}^{y0}[x\ge i][y\ge j]a_{i,j}$$
$$
=\bigoplus\limits_{i=1}^{x0}\bigoplus\limits_{j=1}^{y0}(x0-i+1)\oplus(y0-j+1)\oplus a_{i,j}$$
$$
=\bigoplus\limits_{i=1}^{x0}\bigoplus\limits_{j=1}^{y0}(x0-i)\oplus(y0-j)\oplus a_{i,j}$$
$$
=x0\oplus  y0\oplus\bigoplus\limits_{i=1}^{x0}\bigoplus\limits_{j=1}^{y0} i\oplus j\oplus a_{i,j}
$$
一个区间四次查询后 $x0\oplus y0$ 抵消掉了，所以只有 $i\oplus j$ 会对查询产生影响，对于 $i,j$ 的奇偶性，开四个数组数组即可

CODE：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
#define lowbit(x) (x&(-x))
const int N=1005;
int n,q,f[2][2][N][N];
void update(int x,int y,int u){
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j)) f[x&1][y&1][i][j]^=u;
}
int query(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j)) res^=f[x&1][y&1][i][j];
	return res;
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,q);
	int x1,x2,y1,y2,opt,w;
	while(q--){
		read(opt,x1,y1,x2,y2);
		if(opt==1){
			LL res=query(x2,y2);res^=query(x1-1,y2);
			res^=query(x2,y1-1),res^=query(x1-1,y1-1);
			write(res,'\n');
		}else{
			read(w);
			update(x1,y1,w),update(x1,y2+1,w);
			update(x2+1,y1,w),update(x2+1,y2+1,w);
		}
	}
	return 0;
}
```

---

## 作者：dxy2020 (赞：1)

# 题目大意

给你一个初始全为零的 $n^2$ 矩阵，要求支持二维区间异或、查询区间异或和。

# 思路

二维树状数组模板题，由于需要二维区间修改，故考虑四个树状数组维护差分数组。

设 $d_{i,j}$ 为所维护的差分数组，则修改 $(x_1,y_1)$ 和 $(x_2,y_2)$ 矩阵时，只需更新 

$$(x_1,y_1),(x_2+1,y_1),(x_1,y_2+1),(x_2+1,y_2+1)$$

区间即可。

区间查询同理，做一个二维前缀和，只需要求出

$$(x_1-1,y_1-1),(x_1-1,y_2),(x_2,y_1-1),(x_2,y_2)$$

区间异或和即可。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,op,a,b,c,d,w;
int Tree[2][2][1005][1005];
inline void in (int &x){
	x=0;char c=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9'){x=(x*10)+(c^48);c=getchar();}
}
inline int lowbit (int x){
	return x&(-x);
}
inline void update (int x,int y,int k){
	for (int i=x;i<=n;i+=lowbit(i))
		for (int j=y;j<=n;j+=lowbit(j))
			Tree[x&1][y&1][i][j]^=k;
}
inline int query (int x,int y){
	int sum=0;
	for (int i=x;i;i-=lowbit(i))
		for (int j=y;j;j-=lowbit(j))
			sum^=Tree[x&1][y&1][i][j];
	return sum;
}
signed main(){
	in (n);in (m);
	while (m--){
		in (op),in (a),in (b),in (c),in (d);
		if (op==1){
			printf("%lld\n",query (c,d)^query (c,b-1)^query (a-1,d)^query (a-1,b-1));
		}
		if (op==2){
			in (w);
			update (a,b,w);update (a,d+1,w);
			update (c+1,b,w);update (c+1,d+1,w);
		}
	}
	return 0;
}
```


---

## 作者：DPair (赞：1)

提供一种 CDQ 分治的做法，可以解决 $n$ 更大时的问题。

## 【思路】
本题简要题意就是实现区间异或区间异或和。

由于本题 $n$ 很小，我们可以用二维树状数组解决，但是由于这道题像极了二维数点，我们考虑用 CDQ 分治来做。

首先由于这道题是矩形修改，我们先传统艺能拆一下点，我们不妨把一个修改拆成四个后缀修改，一个查询拆成四个前缀查询。

然后我们考虑一个修改点给一个前缀点的贡献，不难发现就是以修改点为左上角，查询点为右下角的一个矩形的异或和，所以当且仅当矩形大小为奇数是会有贡献。

那么不难发现，产生贡献的一对点横纵坐标的奇偶性分别相同，于是考虑用状压开 $4$ 个树状数组分别表示 $4$ 种奇偶性的组合，修改和查询都在对应的树状数组上进行，那么就可以保证修改的和查询的都是可以产生贡献的对了。

剩下的 CDQ 分治跑一下三维偏序就行了，第三层的树状数组改成上述的 $4$ 个树状数组即可。

空间 $O(m+n)$ ，时间 $O(m\log m \log n)$ ，可以过。

## 【代码】
删去了不重要的快读和头文件
```cpp
/*
    author: DPair
    language: C++11
*/
typedef long long LL;
#define INF 0x3f3f3f3f
#define MAXN 100005
int ans[MAXN];
int tot, n, m;
struct NODE{
    int x, y;LL val;
    NODE(){}
    NODE(int x, int y, LL val) : x(x), y(y), val(val) {}
    inline int num(){return ((x & 1) << 1) | (y & 1);}
}e[MAXN << 2], g[MAXN << 2];

LL BIT[4][1005];
inline int lowbit(int x){return x & -x;}
inline void modify(LL c[], int x, LL y){for (;x <= n;x += lowbit(x)) c[x] ^= y;}
inline LL query(LL c[], int x){LL ret = 0;for (;x;x -= lowbit(x)) ret ^= c[x];return ret;}
void CDQ(int l, int r){
    if(l == r) return ;
    int mid = (l + r) >> 1;
    CDQ(l, mid);CDQ(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r){
        if(e[i].x <= e[j].x){
            if(e[i].val >= 0) modify(BIT[e[i].num()], e[i].y, e[i].val);
            g[k ++] = e[i ++];
        }
        else{
            if(e[j].val < 0) ans[-e[j].val] ^= query(BIT[e[j].num()], e[j].y);
            g[k ++] = e[j ++];
        }
    }
    while(j <= r){
        if(e[j].val < 0) ans[-e[j].val] ^= query(BIT[e[j].num()], e[j].y);
        g[k ++] = e[j ++];
    }
    for (int t = l;t < i;++ t) if(e[t].val >= 0) modify(BIT[e[t].num()], e[t].y, e[t].val);
    while(i <= mid) g[k ++] = e[i ++];
    for (int t = l;t <= r;++ t) e[t] = g[t];
}
bool b[MAXN];
int main(){
    read(n, m);
    for (int i = 1;i <= m;++ i){
        int opt, x1, y1, x2, y2;LL w;
        read(opt, x1, y1, x2, y2);
        if(opt == 2){
            read(w);
            e[++ tot] = NODE(x1, y1, w);
            e[++ tot] = NODE(x1, y2 + 1, w);
            e[++ tot] = NODE(x2 + 1, y1, w);
            e[++ tot] = NODE(x2 + 1, y2 + 1, w);
        }
        else{
            b[i] = 1;
            e[++ tot] = NODE(x1 - 1, y1 - 1, -i);
            e[++ tot] = NODE(x1 - 1, y2, -i);
            e[++ tot] = NODE(x2, y1 - 1, -i);
            e[++ tot] = NODE(x2, y2, -i);
        }
    }
    memset(ans, 0, sizeof(ans));
    CDQ(1, tot);
    for (int i = 1;i <= m;++ i)
        if(b[i]) print(ans[i]);
}
```

---

## 作者：Honor誉 (赞：1)


[我的博客](https://blog.csdn.net/qq_35019468/article/details/101981131)

这题我们可以考虑差分，设$d_ij$=$a_ij$^$a_{i-1}j$^$a_i{j-1}$^$a_{i-1}{j-1}$

在我们修改的时候：

操作区间为(x1,y1)(x2,y2),那么仅仅会有四个点所构成的前缀和会发生变化。

即：(x1,y1),(x2+1,y1),(x1,y2+1),(x2+1,y2+1)。

那么我们异或的前缀和只用修改这四个点的前缀合即可。（因为其他的点的异或和都被异或了偶数遍）

那么前缀和的查询又怎样呢？

因为我们维护的是前缀和，所以想要得到要求的数组的前缀和，我们只需要异或抵消即可。

即：（x1-1,y1-1）,(x1-1,y2),(x2,y1-1),(x2,y2)

这样这题就十分简单了。

直接用树状数组维护异或前缀和。

但是我们要根据x,y坐标的奇偶性建4棵树状数组来分类讨论。

因为我们需要从一维异或和考虑，因为我们是求的异或和，所以我们修改的点为奇数点，那么所产生的异或和的变化是只会在奇数位体现。反之亦然。那我们就把这个推广到二维，所以要开4个树状数组，分奇偶性计算异或和。

```cpp
#include<bits/stdc++.h>
#define N 1010
using namespace std;
int x1,y3,x2,y2,n,m,op;
long long num[N][N][2][2],z;
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int y,long long z)
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		for(int j=y;j<=n;j+=lowbit(j))
		{
			num[i][j][x&1][y&1]^=z;
		}
	}
}
long long sum(int x,int y)
{
	long long ans=0;
	for(int i=x;i;i-=lowbit(i))
	{
		for(int j=y;j;j-=lowbit(j))
		{
			ans^=num[i][j][x&1][y&1];
		}
	}
	return ans;
}
int main()
{
//	freopen("1.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d%d",&x1,&y3,&x2,&y2);
			printf("%lld\n",sum(x2,y2)^sum(x2,y3-1)^sum(x1-1,y2)^sum(x1-1,y3-1));
		}else{
			scanf("%d%d%d%d%lld",&x1,&y3,&x2,&y2,&z);
			add(x1,y3,z);
			add(x1,y2+1,z);
			add(x2+1,y3,z);
			add(x2+1,y2+1,z);
		}
	}
	return 0;
}
```



---

## 作者：LJC00753 (赞：1)

前言：

因为有些东西我不会数学表示发，用代码表示了.....

详细说一下二维树状数组的做法

对异或进行差分 $d_{i,j} = a_{i,j}$ xor $a_{i-1,j}$ xor $a_{i,j-1}$ xor $a_{i-1,j-1}$ 

然后对于同一个矩阵，我们异或了一个数，那么只有

$d_{x_{0},y_0}$ ,$d_{x_1+1,y_1+1}$ ,$d_{x_0,y_1+1}$ ,$d_{x_1+1,y_0}$ 的值会改变，其他的都因为$a_{i,j}$ ,$a_{i-1,j}$ , $a_{i,j-1}$ , $a_{i-1,j-1}$ 
中有偶数个数被xor了x，值不变

![](https://cdn.luogu.com.cn/upload/pic/55839.png)

如图，标注了xor x的会被改变

然后是查询，查询的话就是要求二维xor的前缀和

如果查询 (x,y)的前缀xor

那么答案就是 
```
for(int i = x; i >= 1; i -= 2)
	for(int j = y; j >= 1; j -= 2)//不会数学公式表达就用代码表示了
   ans ^= d[i][j];
```

因为可以转化成
```
for(int i = x; i >= 1; i -= 2)
	for(int j = y; j >= 1; j -= 2)//不会数学公式表达就用代码表示了
   ans ^= a[i][j]^a[i-1][j]^a[i][j-1]^a[i-1][j-1];
```

即

```
for(int i = x; i >= 1; i --)
	for(int j = y; j >= 1; j --)
   ans ^= a[i][j];
```
然后我们珂以开4个二维树状数组，分别维护所有x,y都奇偶性相同的点

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1005
#define lowbit(x) (x&(-x))
#define int long long

int n,m;
struct szsz {//二维树状数组 
	int c[MAXN][MAXN];
	void gai(int x,int y,int v) {//修改 
		int yy = y;
		for(int i = x; i <= n; i += lowbit(i))
			for(int j = y; j <= n; j += lowbit(j))
			c[i][j] ^= v;
	}
	
	int he(int x,int y) {//求和 
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i))
			for(int j = y; j > 0; j -= lowbit(j)) {
				ans ^= c[i][j];
			}
		
		return ans;
	}
}c[5];

int QAQ(int x,int y) {//坐标转化成对应树状数组的编号 
	int rt = 0;
	if(x&1) rt += 1;
	if(y&1) rt += 2;
	return rt; 
}


signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i = 1; i <= m; i ++) {
		int opt,ax,ay,bx,by,v;
		scanf("%lld",&opt);
		if(opt == 1) {
			scanf("%lld%lld%lld%lld",&ax,&ay,&bx,&by);
			int ans = c[QAQ(bx,by)].he(bx,by);
				ans ^= c[QAQ(bx,ay-1)].he(bx,ay-1);
				ans ^= c[QAQ(ax-1,by)].he(ax-1,by);
				ans ^= c[QAQ(ax-1,ay-1)].he(ax-1,ay-1);
			printf("%lld\n",ans);	
		} else {
			scanf("%lld%lld%lld%lld%lld",&ax,&ay,&bx,&by,&v);
			c[QAQ(ax,ay)].gai(ax,ay,v);
			c[QAQ(bx+1,ay)].gai(bx+1,ay,v);
			c[QAQ(ax,by+1)].gai(ax,by+1,v);
			c[QAQ(bx+1,by+1)].gai(bx+1,by+1,v);
		}
	}
	return 0;
 } 
 
```


---

## 作者：鱼跃于渊 (赞：0)

一道二维树状数组的模板题。  

## 解法

考虑推式子，设原数组为 $a_{i,j}$，在异或意义下的差分数组为 $d_{i,j}$。  
首先原先整个矩阵的异或和为 $\bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}a_{i,j}$，而 $a_{i,j}=\bigoplus_{x=1}^{i}\bigoplus_{y=1}^{j}d_{x,y}$，所以整个矩阵的异或和又等于  

$$ \bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}\bigoplus_{x=1}^{i}\bigoplus_{y=1}^{j}d_{x,y}=\bigoplus_{i=1}^{n}\bigoplus_{j=1}^{n}\bigoplus_{k=1}^{(n-i+1)(n-j+1)}d_{i,j}$$  

考虑继续化简，由异或的性质可以得到：$\forall x\in \Z,x \oplus x=0,x\oplus 0=x$。  
所以 $\bigoplus_{k=1}^{(n-i+1)(n-j+1)}d_{i,j}$ 是否为 $0$ 取决于 $(n-i+1)(n-j+1)$ 的奇偶性。  
因此我们分别按照 $i,j$ 的奇偶性开 $4$ 个树状数组，其他方面就和普通树状数组没区别了。  
时间复杂度 $O(m\log^2 n)$，可以通过此题。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define lowbit(x) ((x)&(-(x)))
const int N=1e3+5;
int n,m,t[2][2][N][N];
void add(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			t[x&1][y&1][i][j]^=k;
}
int query(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res^=t[x&1][y&1][i][j];
	return res;
}
int query(int x1,int y1,int x2,int y2){
	return query(x2,y2)^query(x1-1,y2)^query(x2,y1-1)^query(x1-1,y1-1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1,op,x1,y1,x2,y2,k;i<=m;i++){
		cin>>op>>x1>>y1>>x2>>y2;
		if(op==1) cout<<query(x1,y1,x2,y2)<<'\n';
		else{
			cin>>k;
			add(x1,y1,k);
			add(x2+1,y1,k);
			add(x1,y2+1,k);
			add(x2+1,y2+1,k);
		}
	}
	return 0;
}
```

---

## 作者：Hurraciny (赞：0)

# 写在前面 🍜
为了能更加理解本题的做法，建议先出门左拐 [P4514 上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514)。

# 算法分蜥 🦎
这道题也是比较直接的，需要对于一个矩阵的某个子矩阵进行操作或查询，非常明显的一个支持区间修改和查询的二维树状数组。

在操作过程中，正常树状数组是 $\sum_{i=l}^{r} = pre_r-pre_{l-1}$，但是这里因为是异或，所以就是 $\bigoplus_{i=l}^r = pre_r \oplus pre_{l-1}$ 了。

同时，有个小小的点，因为两个一样的数异或起来等于 0，因此在本题中，当需要将若干个值异或若干次时，只需判断次数的奇偶性即可求出最终值。

# 代码 🐎
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
namespace IO{   //快读快写
    inline int input(){
        int x = 0;
        bool f = 0;
        char ch = getchar();
        while(!isdigit(ch)){
            if(ch == '-')
                f = 1;
            ch = getchar();
        }
        while(isdigit(ch)){
            x = (x<<1)+(x<<3)+(ch^48);
            ch = getchar();
        }
        if(f)
            x = -x;
        return x;
    }
    inline void print1(int x){
        if(x < 0)
            putchar('-'), x = -x;
        if(x >= 10)
            print1(x/10);
        putchar(x%10+'0');
    }
    inline void print(int x){
        print1(x);
        putchar('\n');
    }
}
using namespace IO;
const int N = 1002;
int n;
inline int Xor_pow(int x, int p){   //求x异或p次的值
    if(p&1)
        return x;
    return 0;
}
//二维树状数组模版
class Tree_Array{
private:
    int tree1[N];
    int tree2[N];
    inline int lowbit(int x){return x&-x;}
    inline void modify(int x, int v){
        for(int i = x; i <= n; i += lowbit(i))
            tree1[i] ^= v, tree2[i] ^= Xor_pow(v, x-1);
        return;
    }
    inline int query(int x){
        int ret = 0;
        for(int i = x; i; i -= lowbit(i))
            ret ^= Xor_pow(tree1[i], x)^tree2[i];
        return ret;
    }
public:
    inline void modify(int l, int r, int v){
        modify(l, v);
        modify(r+1, v);
    }
    inline int query(int l, int r){
        return query(r)^query(l-1);
    }
};
class Tree_Array_Out{
private:
    Tree_Array tree1[N];
    Tree_Array tree2[N];
    inline int lowbit(int x){return x&-x;}
    inline void modify(int x, int L, int R, int v){
        for(int i = x; i <= n; i += lowbit(i))
            tree1[i].modify(L, R, v), tree2[i].modify(L, R, Xor_pow(v, x-1));
        return;
    }
    inline int query(int x, int L, int R){
        int ret = 0;
        for(int i = x; i; i -= lowbit(i))
            ret ^= Xor_pow(tree1[i].query(L, R), x)^tree2[i].query(L, R);
        return ret;
    }
public:
    inline void modify(int l, int r, int L, int R, int v){
        modify(l, L, R, v);
        modify(r+1, L, R, v);
    }
    inline int query(int l, int r, int L, int R){
        return query(r, L, R)^query(l-1, L, R);
    }
};

Tree_Array_Out tree;
int main(){
    int m;
    n = input();
    m = input();
    while(m--){
        int op = input(), l = input(), L = input(), r = input(), R = input();
        if(op == 1)
            print(tree.query(l, r, L, R));
        else
            tree.modify(l, r, L, R, input());
    }
    return 0;
}

```

---

## 作者：_anll_ (赞：0)

## 题意
给定 $n\times n$ 的矩阵，有 $m$ 次操作：进行区间异或以及询问区间异或和。

## 思路
前置芝士(二维树状数组求和)：[P4514 上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514)

依旧按照板子来。回忆二维前缀异或和。不妨令 $[x,y]$ 表示从 $(1,1)$ 到 $(x,y)$ 的区间异或和。所以 
$(x1,y1)$ 到 $(x2,y2)$ 的区间异或和等价于 $[x2,y2] \oplus [x1-1,y2] \oplus [x2,y1-1] \oplus[x1-1,y1-1]$。

我们集中来看如何算出 $[x,y]$。定义两个数组：原数组 $a$ 和差分数组 $d$。由于 $[x,y]=\bigoplus\limits^x_{i=1}\bigoplus\limits^y_{j=1}a_{i,j}$，我们又知道
$a_{i,j}=\bigoplus \limits^i_{p=1}\bigoplus\limits^j_{q=1}d_{p,q}$，那么可以推出 $[x,y]=\bigoplus\limits^x_{i=1}\bigoplus\limits^y_{j=1}\bigoplus\limits^i_{p=1}\bigoplus\limits^j_{q=1}d_{p,q}$。

我们重新将 $a^x$ 定义为 $a$ 被异或了 $x$ 次。模拟或浅推一下就会发现上文的式子变成了 $\bigoplus\limits^x_{i=1}\bigoplus\limits^y_{j=1}{d_{i,j}}^{(x-i+1)\times(y-j+1)}$。由于异或有 $a\oplus a=0$ 这一性质，所以我们只需要考虑 $(x-i+1)\times(y-j+1)$ 的奇偶性即可。通过乘法奇偶性与加减奇偶性易得出：当且仅当 $y$ 与 $j$、$x$ 与 $i$ 同奇偶时 $d_{i,j}$ 对答案有贡献。

不妨维护四个二维数组。具体而言，在二维树状数组的基础上再开两维，第一维维护当前 $x$ 的奇偶性，第二维维护当前 $y$ 的奇偶性。剩下的就和二维树状数组板子一样了。

## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1005;
int n,m,tr[N][N][2][2];
int lowbit(int x){return x&-x;}
void add(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			tr[i][j][x&1][y&1]^=k;
}
int Find(int x,int y,int k=0){
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			k^=tr[i][j][x&1][y&1];
	return k;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;int op,x1,y1,x2,y2,k;
	while(m--){
		cin>>op>>x1>>y1>>x2>>y2;
		if(op==1){
			cout<<(Find(x2,y2)^Find(x1-1,y1-1)
				 ^Find(x1-1,y2)^Find(x2,y1-1))<<endl;
		}
		else{
			cin>>k;
			add(x1,y1,k);add(x2+1,y2+1,k);
			add(x1,y2+1,k);add(x2+1,y1,k);
		}
	}
	return 0;
} 
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

给定一个矩阵，动态的矩形异或，矩形查询异或值。

### 题目分析

由于异或运算具有可逆性，即两次异或同一个数等于没异或，所以我们可以考虑利用二维前缀和，例如我们要将矩形 $(x_1,y_1,x_2,y_2)$ 异或上 $k$，我们就可以先将 $(1,1,x_2,y_2)$ 都异或上 $k$，然后再对于多异或的区域异或回来，与传统前缀和一样，我们只需再对于 $(1, 1, x_1-1,y_2), (1,1,x_2,y_1-1), (1,1,x_1-1,y_1-1)$ 都异或上 $k$ 即可。对于查询同理。

但是发现我们对于 $(1,1,x,y)$ 都异或上 $k$ 的时候，前缀和数组 $(x,y)\sim(n,n)$ 都需要修改。时间复杂度过不了。

考虑到是区间修改，单点查询，且区间有一边界是确定的，所以可以考虑二维树状数组。

同时，因为本题是异或树状数组，所以异或偶数次是没有用的，于是我们可以根据横纵坐标差的奇偶性来维护 $4$ 个树状数组从而维护异或前缀和。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e3 + 5;
int n, q, opt, x1, x2, y1, y2, k, t[2][2][N<<1][N<<1];

int lowbit(int x){return x & -x;}

void update(int x, int y, int val)
{
	for(int i = x;i <= n;i += lowbit(i))
		for(int j = y;j <= n;j += lowbit(j))
			t[x%2][y%2][i][j] ^= val;
}

int query(int x, int y)
{
	int res = 0;
	for(int i = x;i;i -= lowbit(i))
		for(int j = y;j;j -= lowbit(j))
			res ^= t[x%2][y%2][i][j];
	return res;
}

signed main()
{
	scanf("%d %d", &n, &q);
	while(q--)
	{
		scanf("%d", &opt);
		if(opt == 1)
		{
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("%d\n", query(x1-1, y1-1) ^ query(x1-1, y2) ^ query(x2, y1-1) ^ query(x2, y2));
		}
		else
		{
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &k);
			update(x1, y1, k);
			update(x1, y2+1, k);
			update(x2+1, y1, k);
			update(x2+1, y2+1, k);
		}
	}
	return 0;
}
```

---

## 作者：Erotate (赞：0)

其实这题和 [上帝造题的七分钟](https://www.luogu.com.cn/problem/P4514) 挺像的，所以我们考虑能不能像那题一样多开几个树状数组来降低时间复杂度。因为这题是异或操作，所以答案的每一位的奇偶性与下标的奇偶性有关，因此我们可以维护四个树状数组来统计奇偶性不同的答案。

接下来就和模板一样了。对于操作一，直接利用二维前缀和查询即可，和加法是一样的。同理对于操作二，也根据前缀和的性质修改 $(x1,y1),(x2+1,y1),(x1,y2+1),(x2+1,y2+1)$ 这几个点就行了。

```cpp
const int N=1e3+5;
int n,m,c[2][2][N][N];
void add(int x,int y,int v){
	for(int i=x;i<=n;i+=lb(i))
		for(int j=y;j<=n;j+=lb(j)) c[x&1][y&1][i][j]^=v;
}
int ask(int x,int y){
	int res=0;
	for(int i=x;i;i-=lb(i))
		for(int j=y;j;j-=lb(j)) res^=c[x&1][y&1][i][j];
	return res;
}
void update(int x,int y,int x2,int y2,int v){
	add(x,y,v),add(x,y2+1,v),add(x2+1,y,v),add(x2+1,y2+1,v);
}
int query(int x,int y,int x2,int y2){
	return ask(x-1,y-1)^ask(x-1,y2)^ask(x2,y-1)^ask(x2,y2);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    n=read(),m=read();
    while(m--){
    	int opt=read(),x=read(),y=read(),x2=read(),y2=read();
    	if(opt==2){
    		int val=read();
    		update(x,y,x2,y2,val);
		}else Write(query(x,y,x2,y2));
	}
    return 0;
}

```


---

