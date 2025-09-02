# [USACO15DEC] Breed Counting S

## 题目描述

Farmer John 的 $N$ 头奶牛，从左到右编号为 $1 \ldots N$，排成一队。

所有牛都可以分为三个品种，每头牛都有一个品种编号（只能为 $1,2,3$ 中的一个）。FJ 有 $Q$ 个询问，每个询问希望求出某个区间内每个品种奶牛的数量。

## 样例 #1

### 输入

```
6 3
2
1
1
3
2
1
1 6
3 3
2 4```

### 输出

```
3 2 1
1 0 0
2 0 1```

# 题解

## 作者：MZY666 (赞：14)

[原题传送门](https://www.luogu.com.cn/problem/P6180)。[在我的博客中食用更佳。](https://www.luogu.com.cn/blog/MZY666/solution-p6180)

题意概括：

先输入两个数 $N$，$Q$，分别表示牛个数和询问个数。

接下来先输入每只牛的类型，随后再输入 $Q$ 组询问，每组询问是两个数：$a$ 和 $b$，表示询问这两个牛的编号之间每种牛各有多少只。

要求输出每组询问的结果。**记得换行**。

思路：前缀和。如何实现呢？

在题中有这样一句话：

>每个询问希望求出某个**区间内**每个品种奶牛的数量。

划重点：区间内。那么我们就可以用三个一位数组 $x[i],y[i],z[i]$来存储每一种奶牛到第 $i$ 头时的总数量。

这样一来，每次用后面读入牛的编号所对应的个数减去前面读入牛的编号-1所对应的个数即可算出区间和（前缀和）了，即：

```cpp
x_sum=x[b]-x[a-1],y_sum=y[b]-y[a-1],z_sum=z[b]-z[a-1].
```

是时候上完整代码了！
```cpp
#include<bits/stdc++.h>//万能头文件好
#define ll long long//个人习惯
using namespace std;
ll x[100005],y[100005],z[100005];//数组最好开大个5个左右，以防万一
int main(){
	ll n,q,i,a,b;//习惯先把变量放这，数组放上面
	scanf("%lld%lld",&n,&q);//读入N和Q，为了方便都写的n和q.
	for(i=1;i<=n;i++){
		scanf("%lld",&a);//读入a，此时的a用于暂存当前品种 
		x[i]=x[i-1];y[i]=y[i-1];z[i]=z[i-1];
        //把之前的每一种类型的奶牛先加上来，稍稍压行
		switch(a){//判断这只牛的类型
			case 1:
				x[i]++;
				break;
			case 2:
				y[i]++;
				break;
			case 3:
				z[i]++;
				break;
		}//把这只牛加上去
	}
	for(i=1;i<=q;i++){//开始读入询问
		scanf("%lld%lld",&a,&b);//读入题目描述中的a和b.
		printf("%lld %lld %lld\n",x[b]-x[a-1],y[b]-y[a-1],z[b]-z[a-1]);
        //这一步前面有单独分析。
	}
	return 0;//over
}

```

还是很简单的把。本蒟蒻还不会树状数组（好像有大佬这样做），如有需要请移步他处。

完结撒花~

---

## 作者：do_while_false (赞：3)

【大概思路】

本题很容易想到前缀和。

> 前缀和是一种重要的预处理，能大大降低查询的时间复杂度。我们可以简单理解为“数列的前 nn 项的和”。

如果有数组 $\{1,1,4,5,1,4\}$，则有其前缀和数组 $\{1,2,6,11,12,16\}$ 。

我们很容易发现，如果设前缀和数组为 $f$ 数组，原数组为 $a$，那么 $f_i\gets f_{i-1}+a_i$ ，如果数组下标从 $1$ 开始，那么初始条件则为 $f_1\gets a_1$ 。

事实上，$f_ik$还有另一层含义:

$$\sum_{i=1}^ka_i$$

即 $f_k=a_1+a_2+a_3... a_k$

这时，我们可以发现一个性质

假如我们有两个数 $x,y(x<y)$ ，则 $f_x$ 表示 $a_1+a_2+a_3... a_x$ ，$f_y$ 表示 $a_1+a_2+a_3... a_y$ ，因为 $x<y$ ，所以 $f_y-f_x$ 其实表示的就是 $a_{x+1}+a_{x+2}+a_{x+3}...+a_y$ 。

那我们怎么表示 $\sum_{i=l}^ra_i$ 呢？

根据上面的结论，很容易发现 $\sum_{i=l}^ra_i$ 就是 $f_r-f_{l-1}$ 。

对于这题，我们只用开三个前缀和数组然后就可以愉快的模拟啦！

【~~Talk is cheap,show me the code.~~】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a,b,ans1,ans2,ans3,k1[100005],k2[100005],k3[100005],s[100005];//k1,k2,k3是三个前缀和数组 
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main() {
    n=read();q=read();
    for(int i=1;i<=n;i++) {//建立前缀和数组 
        s[i]=read();
        if(s[i]==1) {
            k1[i]=k1[i-1]+1;
            k2[i]=k2[i-1];
            k3[i]=k3[i-1];
        }
        if(s[i]==2) {
            k2[i]=k2[i-1]+1;
            k1[i]=k1[i-1];
            k3[i]=k3[i-1];
        }
        if(s[i]==3) {
            k3[i]=k3[i-1]+1;
            k2[i]=k2[i-1];
            k1[i]=k1[i-1];
        }
    }
    for(int i=1;i<=q;i++) {//计算答案 
        a=read();b=read();
        swap(a,b);
        ans1=k1[b]-k1[a];
        ans2=k2[b]-k2[a];
        ans3=k3[b]-k3[a];
        if(s[a]==1) ans1+=1;
        else if(s[a]==2) ans2+=1;
        else if(s[a]==3) ans3+=1;
        printf("%d %d %d\n",ans1,ans2,ans3);
    }
    return 0;
}
```

---

## 作者：LongDouble (赞：3)

这题其实可以不用树状数组、线段树等数据结构。

仔细阅读题面，不难发现，这题只有查询操作，而没有修改操作。

而**前缀和**刚好可以满足这个功能！

直接开三个前缀和，维护每种牛的个数即可。

比较一下时间复杂度：

树状数组、线段树：$O((N+Q)\log N)$。

前缀和：$O(N+Q)$。

而且相比树状数组、线段树，前缀和不需要专门写一大堆建树、维护、查询的函数。

以下是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int s1[100010], s2[100010], s3[100010];
int n, q;

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		s1[i] = s1[i - 1];
		s2[i] = s2[i - 1];
		s3[i] = s3[i - 1];
		if (a == 1) s1[i]++;
		if (a == 2) s2[i]++;
		if (a == 3) s3[i]++;
	}
	for (int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d ", s1[r] - s1[l - 1]);
		printf("%d ", s2[r] - s2[l - 1]);
		printf("%d\n", s3[r] - s3[l - 1]);
	}
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：2)

### 题解[[USACO15DEC]Breed Counting S](https://www.luogu.com.cn/problem/P6180)  
# 前置知识——前缀和  
实际上，这道题目可以继续加强，比如加上修改操作。  
但是现在没有这个操作，所以我们不考虑线段树&树状数组。  
考虑**前缀和**。  
## 前缀和是什么  
毫无疑问，如同它的名字一样，是求它前缀的一个和。我们用 $sum$ 来表示这个前缀和数组。那么 $sum(i)$ 就是区间$[1,i]$的和。  
## 前缀和的优点是什么  
要是是朴素算法，求区间$[l,r]$的和需要从 $l$ 到 $r$ 扫一遍，复杂度为$\Theta(n)$；而如果是初始化完的前缀和，只需要把区间$[1,r]$的和减去$[1,l-1]$区间的和，注意是**L-1**!  
假设有 $m$ 次咨询，朴素算法需要$\Theta(n\times m)$的时间，而前缀和只需要初始化的$\Theta(n)$的时间和求和的$\Theta(m)$的复杂度，总复杂度为$\Theta(n+m)$，无疑是非常快的。  
前缀和初始化的代码是：  
```cpp
sum[0] = 0;
for(int i = 1;i <= n;i++)
	sum[i] = sum[i - 1] + a[i];  //a[i]是我们要维护的数。  
```

# Solution  
这道题目考虑开3个前缀和，然后进行求解。  
直接上代码吧，前面讲的够详细了。  

# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

template<class T>
inline void read(T& x) {
	x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

const int N = 1e5 + 9;

int cow[4][N];
int n,q,x,l,r;

int main() {
	read(n);read(q);
	for(int i = 1;i <= n;i++) {
		cow[1][i] = cow[1][i - 1];
		cow[2][i] = cow[2][i - 1];
		cow[3][i] = cow[3][i - 1];
		read(x);
		if(x == 1) cow[1][i]++;
		if(x == 2) cow[2][i]++;
		if(x == 3) cow[3][i]++;
	}
	for(int i = 1;i <= q;i++) {
		read(l);read(r);
		printf("%d %d %d\n",cow[1][r] - cow[1][l - 1],cow[2][r] - cow[2][l - 1],cow[3][r] - cow[3][l - 1]);
	}
	return 0;
}
```

---

## 作者：HsKr (赞：1)

**线段树太强辣！！！**

发现没有线段树题解，于是发一篇。

**不会线段树？[这里](https://oi-wiki.org/ds/seg/)or[这里](https://www.luogu.com.cn/blog/247658/HsKr-5)。**

思路：3个线段树，分别维护奶牛的品种。对于品种操作，就对相应的品种进行change；对于查询操作，就分别对每个品种进行ask。

注意：建树要建3个。建树中可省略线段树1模板中sum的操作（不改也可以）。如果您不是结构体党，可以不建树。

其余跟线段树模板题没什么区别。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
const int maxn=100010;
long long n,m,a[maxn];
struct SegmentTree{
    int l,r;
    long long sum,add; 
}one[maxn*4],two[maxn*4],three[maxn*4];
void build(SegmentTree t[],int p,int l,int r){//对线段树t的[l,r]建树，当前节点为p 
    t[p].l=l;t[p].r=r;//初始化左右端点 
    if(l==r){//搜到根节点了 
//        t[p].sum=a[l];
        return;
    }
    int m=l+r>>1;//从中间划开 
    build(t,ls(p),l,m);build(t,rs(p),m+1,r);//对子树建树 
//    t[p].sum=t[ls(p)].sum+t[rs(p)].sum;
}
void push_down(SegmentTree t[],int p){//下传懒标记 
    if(t[p].add){//懒标记还有 
        t[ls(p)].sum+=t[p].add*(t[ls(p)].r-t[ls(p)].l+1);//左子树加上 
        t[rs(p)].sum+=t[p].add*(t[rs(p)].r-t[rs(p)].l+1);//右子树加上 
        t[ls(p)].add+=t[p].add;t[rs(p)].add+=t[p].add;//懒标记下传 
        t[p].add=0;//清空当前懒标记 
    }
}
void change(SegmentTree t[],int p,int l,int r,int x){//对t线段树的[l,r]加上x，当前节点为p 
    if(l<=t[p].l && t[p].r<=r){//覆盖 
        t[p].sum+=x*(t[p].r-t[p].l+1);//此段加上 
        t[p].add+=x;//打上懒标记 
        return;
    }
    push_down(t,p);//下面要更改了！！！下传懒标记 
    int m=t[p].l+t[p].r>>1;//分两半 
    if(l<=m) change(t,ls(p),l,r,x);//左半有交集改左半 
    if(m<r) change(t,rs(p),l,r,x);//同上 
    t[p].sum=t[ls(p)].sum+t[rs(p)].sum;//更新当前节点 
}
long long ask(SegmentTree t[],int p,int l,int r){//对t线段树的[l,r]查询，当前节点为p 
    if(l<=t[p].l && t[p].r<=r) return t[p].sum;//覆盖，直接返回此段答案 
    push_down(t,p);//下面要查询了！！！下传懒标记 
    int m=t[p].l+t[p].r>>1;
    long long sum=0;
    if(l<=m) sum+=ask(t,ls(p),l,r);//左半有交集查左半 
    if(m<r) sum+=ask(t,rs(p),l,r);//同上 
    return sum;
}
int main(){
    scanf("%lld%lld",&n,&m);
    build(one,1,1,n);
    build(two,1,1,n);
    build(three,1,1,n);//对三个品种建树 
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
    	if(a[i]==1){
    		change(one,1,i,i,1);
		}
		else if(a[i]==2){
			change(two,1,i,i,1);
		}
		else{
			change(three,1,i,i,1);
		}//对三个品种加1 
	}
	for(int i=1;i<=m;i++){
		long long l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld %lld %lld\n",ask(one,1,l,r),ask(two,1,l,r),ask(three,1,l,r));
		//查询每个品种 
	}
    
    return 0;
}
```

这题前缀和和树状数组皆可做，但它们的适用范围不及线段树。但用线段树总感觉有点大材小用了，杀鸡焉用牛刀！

---

## 作者：answerend42 (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P6180)

[更好的阅读体验](https://answerend42.github.io/2020/03/08/lg6180/)

题意简述

  给出 $n$ 头奶牛，每头可分为三种，对于 $q$ 次询问，给出区间内各种奶牛的数量。
  
思路

题目的数据范围限制为 $N,Q\leq10^5$ ，肯定不能够使用暴力对于每一个区间跑一遍统计。这一题有只要求查询而不要求修改，很自然就想到了前缀和。

那么什么是前缀和呢？

根据[OI Wiki 上的解释](https://oi-wiki.org/basic/prefix-sum/)

>前缀和是一种重要的预处理，能大大降低查询的时间复杂度。我们可以简单理解为“数列的前 $n$ 项的和”。

如果用数组 $a$ 和其前缀和数组 $b$ 表示出来

$a_1=1,a_2=5,a_3=3,a_4=2,...$

则数组 $b$ 可以表示如下


$b_1=1,b_2=6,b_3=9,b_4=11,...$

不难推出式子

$$
b_i=b_{i-1}+a_i
$$

如果要查询数组 $a$ 从 $l$ 到 $r$ 之间所有数的和，只用输出 $b_r-b_{l-1}$

原理：

$$b_r=\sum_{i=1}^{r}a_i$$
$$b_{l-1}=\sum_{i=1}^{l-1}a_i$$

注意，一定是 $l-1$ 如果是 $l$ 就会将 $a_l$ 减去

根据上述，给出代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();int ret=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9'){ret=(ret<<1)+(ret<<3)+ch-'0';ch=getchar();}
    return ret*f;
}
const int N = 100005;
int n,q,a[2][N],b[2][N],c[2][N];
//a[0],b[0],c[0]为原始数组
//a[1],b[1],c[1]为对应的前缀和数组
int main()
{
    n=read();q=read();
    for(int i=1;i<=n;i++)
    {
        int t=read();
        if(t==1)
            a[0][i]++;
        else if(t==2)
            b[0][i]++;
        else if(t==3)
            c[0][i]++;
        a[1][i]=a[1][i-1]+a[0][i];
        b[1][i]=b[1][i-1]+b[0][i];
        c[1][i]=c[1][i-1]+c[0][i];
    }
    for(int i=1;i<=q;i++)
    {
        int l=read(),r=read();
        printf("%d %d %d\n",a[1][r]-a[1][l-1],b[1][r]-b[1][l-1],c[1][r]-c[1][l-1]);
    }
}
```


---

## 作者：Skies (赞：1)

## 目前代码最短且最优解！~~蒟蒻（和我一样）专属~~
首先，看到区间、个数、累计，很容易想到前缀和（呵呵，很容易？）

我们来看看前缀和是个什么东东

对于一个给定的数列 A, 它的前缀和数列S 是通过递推能求出来得

![](https://private.codecogs.com/gif.latex?%5Cfn_cm%20S%5Bi%5D%20%3D%20%5Csum_%7Bj%3D1%7D%5E%7Bi%7D%20A%5Bj%5D)                                                

部分和,即数列A中某个下标区间内的数的和,可以表示为前缀和相减的形式:

![](https://private.codecogs.com/gif.latex?%5Cfn_cm%20sum%5Bl%2Cr%5D%20%3D%20%5Csum_%7Bi%3Dl%7D%5E%7Br%7D%20A%5Bi%5D%20%3D%20S%5Br%5D%20-%20S%5Bl-1%5D)

然后根据题意办事判断

开3个数组装1，2，3 的前缀和即可
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N= 100010;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
inline int inc(int x,int v,int mod){x+=v;return x>=mod?x-mod:x;}
inline int dec(int x,int v,int mod){x-=v;return x<0?x+mod:x;}
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if(x==0){putchar(48);return;}int len=0,dg[20];while(x>0){dg[++len]=x%10;x/=10;}for(register int i=len;i>=1;i--)putchar(dg[i]+48);}
int a[N];
int p1[N],p2[N],p3[N];
int main()
{
	//freopen("未命名1.in","r",stdin);
	//freopen("未命名1.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]==1)
		{
			p1[i]=+1;
		}
		if(a[i]==2)
		{
			p2[i]=+1;
		}
		if(a[i]==3)
		{
			p3[i]=+1;
		}
		p1[i]+=p1[i-1];
		p2[i]+=p2[i-1];
		p3[i]+=p3[i-1];
	}
	for(int i=1;i<=m;i++) 
	{
		int p=read(),q=read();
		write(p1[q]-p1[p-1]),putchar(' ');
		write(p2[q]-p2[p-1]),putchar(' ');
		write(p3[q]-p3[p-1]),putchar(' ');
		putchar('\n');
	}
   return 0;
}
```

---

