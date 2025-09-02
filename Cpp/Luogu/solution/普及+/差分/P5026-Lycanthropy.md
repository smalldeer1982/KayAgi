# Lycanthropy

## 题目背景

小正方形亲眼看见了自己昔日的朋友被卷进了黑暗的深渊，然而它无力阻止……

现在它的朋友已经向它发起了攻击，因此小正方形不得不抵抗。

## 题目描述

我们把山顶上的湖泊看作一条长度为 $m$ 的直线，一开始水深都在水平线上，我们视作此时的水深为 '0'

接下来，在一瞬间，小正方形的"朋友"们跳起并扎入水中，导致在入水点的水降低而远离入水点的水升高，注意两个 "朋友" 可能在同一地点入水。

小正方形的每个朋友有一个体积数值 $v$，当体积为 $v$ 的一个朋友跳入水中，我们设入水点为 $i$，将会导致 $i - v + 1$ 到 $i$ 的水位依次降低 $1,2,\cdots,v$

同样地，第 $i$ 到 $i + v - 1$ 的水位会依次降低 $v,v - 1,\cdots,1$.

相对应地，$i - v$ 的水位不变， $i - v - 1$ 到 $i - 2 * v$ 水位依次增加 $1,2,\cdots,v$， $i - 2 * v$ 到 $i - 3 * v + 1$ 水位依次增加 $v,v - 1,\cdots,1$

同样，$i + v$ 水位不变，$i + v + 1$ 到 $i + 2 * v$ 水位增加 $1,2,\cdots,v$，$i + 2 * v$ 到 $i + 3 * v - 1$ 水位依次增加 $v,v - 1,\cdots,1$

现在小正方形想要穿过这个湖，他想要知道在这 $n$ 个"朋友"跳入水中后湖上每个节点的水位，你能帮帮它吗？

## 说明/提示

对于 $30\%$ 的数据，$n <= 50,m <= 500$

对于 $70\%$ 的数据，$n <= 10^5,m <= 10^5$

对于 $100\%$ 的数据，$n <= 10^6,m <= 10^6,1 <= v <= 10000,1 <= x <= m$

## 样例 #1

### 输入

```
1 10
1 5```

### 输出

```
0 0 1 0 -1 0 1 0 0 0 ```

## 样例 #2

### 输入

```
2 10
2 6
3 1```

### 输出

```
-2 0 0 0 0 0 2 2 2 2```

# 题解

## 作者：WAMonster (赞：18)

NOIP后趁还没出成绩发一篇水题题解。

首先，我们发现当仅有一人落水时，这题的水位增长如果看成一条曲线的话，其增减是线性的。也就是说水位线的变化在图上画出来是一条折线。它长这样：

![](https://s1.ax1x.com/2018/11/17/izDn61.png)

（如图表示一个$v=5$的人在$0$处落水后的新水位）

~~这不珂学！！！水怎么还多了！！！~~

既然它递增/递减是均匀的，那么我们可以考虑先用差分维护某一点的水位与上一点的差值，很显然维护的差值也是一个差分。差分还原成原值需要求前缀和，所以第一次差分之后跑两遍前缀和即可。

这里只列举一人落水的情况，但手玩数据可发现，随便多少人都一样。

~~绿题貌似有点高估了此题难度？~~

注意落水处左边的坐标值可以为负。开两倍数组再搞个指针即可。

code：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int aa[2100000],bb[2100000];
#define isdigit(x) ((x)>='0'&&(x)<='9')
inline int read(){
    int a=0,flag=1;
    char c=getchar();
    while(!isdigit(c)){
        if(c=='-')flag=-1;
        c=getchar();
    }
    while(isdigit(c)){
        a=(a<<1)+(a<<3)+c-48;
        c=getchar();
    }
    return a*flag;
}
int main(){
    n=read(),m=read();
    int *a=aa+1000000,*b=bb+1000000;
    for(int i=1;i<=n;++i){
        int v=read(),x=read();
        a[x-3*v+1]++;
        a[x-2*v+1]-=2;
        a[x+1]+=2;
        a[x+2*v+1]-=2;
        a[x+3*v+1]++;
    }
    for(int i=-40000;i<=m+40000;++i)a[i]+=a[i-1],b[i]+=b[i-1]+a[i];
    for(int i=1;i<=m;++i)printf("%d ",b[i]);
    return 0;
}
```

---

## 作者：Wen_kr (赞：8)

#### 30 Pts

对于 $30\%$ 的数据，考虑暴力模拟，最后输出。 时间复杂度 $O(n^2)$

#### 70Pts

考虑用线段树维护，时间复杂度 $O(n log n)​$。

#### 100 Pts

考虑采用差分套差分，用差分维护差分数组即可。 时间复杂度 $O(n)$

---

## 作者：zmza (赞：4)

此题为差分再套一个差分。

第一种方法：暴力枚举，时间复杂度是$O(n^2)$，能拿到30分;

第二种方法：线段树+差分。时间复杂度为$O(n^2)$,能拿到70分;

第三种方法：差分内套差分。因为这道题只要询问一次，所以时间复杂度为$O(n)$。

我们可以通过画图

![](https://cdn.luogu.com.cn/upload/image_hosting/rc77hccs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

得到公式：

$$r[x - 3 * v + 1]++;$$
$$r[x - 2 * v + 1]-=2;$$
$$r[x + 1]+=2;$$
$$r[x + 2 * v + 1]-=2;$$
$$r[x + 3 * v + 1]++;$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int diff[10000005],n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++)
	{
		int v,x;
		scanf("%d%d",&v,&x);
		diff[x - 3 * v + 1 + 1000000]++;//为什么要加一个很大的数呢？因为x-后面这个数有可能为负数，所以要将这个数加上一个很大的数。
		diff[x - 2 * v + 1 + 1000000] -= 2;
		diff[x + 1 + 1000000] += 2;
		diff[x + 2 * v + 1 + 1000000] -= 2;
		diff[x + 3 * v + 1 + 1000000]++;
	}
	int ans = 0,now = 0;
	for(int i = 0; i <= 1000000; i++)//先将前面不要询问的加上。
	{
		now += diff[i];
		ans += now;//差分套差分，所以就要前缀和的前缀和。
	}
	for(int i = 1000001; i <= m + 1000000; i++)//先计算再输出。
	{
		now += diff[i];
		ans += now;
		printf("%d ",ans);
	}
	return 0;
}

```


---

## 作者：WCG2025 (赞：3)

这道题我们循序渐进，一步步来分析


------------
首先有30的数据在n方算法以内，很自然而然的想到了暴力模拟
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
long long n,z;
long long v[200005],x[200005],m[200005];
void low(long long a,long long b)//a为体积，b为位置 
{
		long long temp=b+1;//这一部分是在模拟那些让水位
		for(long long i=a;i>=0;i--)//下降的部分
		if(b)
		{
			m[b]+=-i;
			b--; 
		}
		for(long long i=a-1;i>=0;i--)
		{
			if(temp<=z)
			{
				m[temp]+=-i;
				temp++;
			}
		}
}
void increase(long long a,long long b)//这一部分是在模拟
{//让水位上升的减函数部分
	long long temp1=a+b;
	long long temp2=b-a;
	for(long long i=0;i<=a;i++)
	if(temp1<=z)
	{
		m[temp1]+=i;
		temp1++;
	}
	for(long long i=0;i<=a;i++)
	if(temp2>0)
	{
		m[temp2]+=i;
		temp2--;
	}
}
void increase2(long long a,long long b)
{//这一部分在模拟让水位上升的增函数部分
	long long temp3=b-2*a-1;
	long long temp4=b+2*a+1;
	for(long long i=a-1;i>=0;i--)
	if(temp3>0)
	{
		m[temp3]+=i;
		temp3--;
	}
	for(long long i=a-1;i>=0;i--)
	if(temp4<=z)
	{
		m[temp4]+=i;
		temp4++;
	}
}
void dfs()
{
	for(long long i=1;i<=n;i++)
	{
		low(v[i],x[i]);//所有的temp都是为了防止越界
		increase(v[i],x[i]);
		increase2(v[i],x[i]);	
	}
}
int main()
{
	n=read();
	z=read();
	for(long long i=1;i<=n;i++)
	{
	v[i]=read();
	x[i]=read();
	}
	dfs();
	for(long long i=1;i<=z;i++)
	printf("%lld ",m[i]);
	return 0;
}
```
但很明显，这样的模拟不够优秀（就从模拟的角度来说）
我们可以搞出一个更好的模拟来，降低常数
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int a[500000];
inline int read()
{
 int x=0,f=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
 return x*f;
}
void change(int pos,int num)
{
	int l=pos-2*num,mid=pos,r=pos+2*num,move=0;
	for(int i=num;i>=1;i--)
	{
		if(l+move>=0)a[l+move]+=i;
			if(l-move>=0&&move!=0)a[l-move]+=i;
			if(mid+move>=0)a[mid+move]-=i;
			if(mid-move>=0&&move!=0)a[mid-move]-=i;
			if(r+move>=0)a[r+move]+=i;
			if(r-move>=0&&move!=0)a[r-move]+=i;
	move++;
	}
return ;
}
int main()
{
	int n,m,v,x;
	n=read();m=read();
	while(n--)
	{
		v=read();x=read();
		change(x,v);
	}
	for(int i=1;i<=m;i++)cout<<a[i]<<" ";
return 0;
}
```
这个情况下的模拟就是少开了几个数组，从而省下了一些查询数组的时间


------------
但正解肯定不是模拟（~~QAQ~~）
看百分之七十的数据范围（wen_kr大佬的提示）
我们就用线段树去做，让时间复杂度降到nlogn
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rr register int
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
typedef long long ll;
using namespace std;
inline int read()
{
	char i=getchar();
	int f=1,res=0;
	while(i<'0'||i>'9'){if(i=='-')f=-1;i=getchar();}
	while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
	return res*f;
}
const int N=2e5+50;
const int add=3e4+5;//平移3e4+5坐标 
ll sum[N<<2],lazy[N<<2];
int n,m;//m个小朋友,水池长为n 
//线段树跑差分 模板 
inline void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
inline void pushdown(int rt,int ln,int rn)//延迟操作
{
	if(lazy[rt])
    {
		lazy[rt<<1]+=lazy[rt];
		lazy[rt<<1|1]+=lazy[rt];
		sum[rt<<1]+=lazy[rt]*ln;
		sum[rt<<1|1]+=lazy[rt]*rn;
		lazy[rt]=0;
	}
}
inline void update(int l,int r,int rt,int L,int R,int x)
{
	if(L<=l&&r<=R)
    {
		sum[rt]+=(r-l+1)*x;//这里就是加上这一区间它所降低
		lazy[rt]+=x;//或者升高的值
		return;
	}
	int mid=(l+r)>>1;
//	[l,mid],[mid+1,r]
    pushdown(rt,mid-l+1,r-mid);
    if(L<=mid) update(lson,L,R,x);
    if(R >mid) update(rson,L,R,x);
    pushup(rt);
}
inline ll query(int l,int r,int rt,int L,int R)
{
	if(L<=l&&r<=R)
    {
		return sum[rt];
	}
	int mid=(l+r)>>1;
	pushdown(rt,mid-l+1,r-mid);
	ll res=0;
	if(L<=mid) res+=query(lson,L,R);
	if(R >mid) res+=query(rson,L,R);
	return res;
}
void change(int l,int r,int x)
{
	update(1,N,1,l,r,x);
}
int main()
{
//  设跳入点为x，体积为v 
//  差分区间 
//  1.(x-3*v,x-2*v] add=1
//  2.(x-2*v,x] add=-1
//  3.(x,x+2*v] add=1
//  4.(x+2*v,x+3*v] add=-1
    m=read();n=read();
    int v,x;
    while(m--)
    {
    	v=read();x=read();
    	change(x-3*v+1+add,x-2*v+add,1);
    	change(x-2*v+1+add,x+add,-1);
    	change(x+add+1,x+2*v+add,1);
    	change(x+2*v+1+add,x+3*v+add,-1);
    }
    for(rr i=1;i<=n;++i)
    {
    	printf("%lld ",query(1,N,1,1,i+add));
    }
}
```
这样每次用差分去跑线段树，加上平移数组（防止越界），我们可以拿到70pts

**但是**
满分才是目标
要想O(n)跑过，线段树肯定没有办法了，那么我们按照出题人的意思
来个差分套差分
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int maxn=1e6+7;
int n,m;
int zk[maxn],zlp[maxn];//直接差分 
/*
v x
1）every i in x-3v~x-2v : zk[i] += 3v-x+i
2) every i in x-2v~x : zk[i] += x-i-v
3) every i in x ~ x+2v : zk[i] += i-x-v
4) every i in x+2v~x+3v : zk[i] += 3v-i+x
*///这一部分好好看，下面的代码全部来源于这里的思想
int main()
{
	n=read();m=read();
	int v,x;
	for(int i=1;i<=n;i++)
	{
		v=read(),x=read();
		int l1=max(0,x-3*v),r1=max(0,x-2*v);//防越界
		zk[l1]+=(3*v-x),zk[r1+1]-=(3*v-x);
		zlp[l1]++,zlp[r1+1]--;
		
		int l2=max(0,x-2*v+1),r2=x;
		zk[l2]+=(x-v),zk[r2+1]-=(x-v);
		zlp[l2]--,zlp[r2+1]++;
		
		int l3=x+1,r3=min(m+1,x+2*v);
		zk[l3]+=(-x-v),zk[r3+1]-=(-x-v);
		zlp[l3]++,zlp[r3+1]--;
		
		int l4=min(m+1,x+2*v+1),r4=min(m+1,x+3*v);
		zk[l4]+=(3*v+x),zk[r4+1]-=(3*v+x);
		zlp[l4]--,zlp[r4+1]++;
	}
	int tmp1=0,tmp2=0;
	for(int i=0;i<=m;i++)
	{
		tmp1+=zk[i],tmp2+=zlp[i];
		if(i)printf("%d ",tmp1+tmp2*i);
	}
	return 0;
}
```
到这里，一百分就拿全了（真不容易）

---

## 作者：Durancer (赞：2)

#### 前言

一个很有意思的差分题目，本萌新做完这道题后对差分确实了解了不少

#### 前置芝士

~~差分：我不知道什么定义~~

From **OIwiki**:差分是一种和前缀和相对的策略，可以当做是求和的逆运算。

#### 思路

首先看到这个题，要先学会把文字叙述转化为图，下面提供一章由 @Chen_怡 提供的好看的图
 
![](https://cdn.luogu.com.cn/upload/image_hosting/uycoh03l.png)

我们可以把每一个朋友跳水后修改值的化成一个这样的**图像**

基于我对差分套差分的理解，我想给出一个更加简单易懂的操作过程：**斜率**

首先因为是在 $x=$ 整数的范围内进行求解，所以说姑且**把上面这张图看做一些点点**

从左到右依次叙述：

- $[i-3v+1,i-2v]$

这一段是一个斜率 $k=1$ 的直线，那么就可以在$i-3v+1$ 处将斜率转变$+1$

$$poi[x-3*v+1]++$$

- $[i-2v+1,i]$

这一段是一个斜率 $k=-1$ 的直线，那么就可以在$i-2v+1$ 处将斜率转变$-2$
,因为上一个区间的之间的斜率是 $1$
$$poi[x-2*v+1]-=2$$

- $[i+1,i+2v]$

这一段是一个斜率 $k=1$ 的直线，那么就可以在$i+1$ 处将斜率转变$+2$

$$poi[x+1]+=2$$

- $[i+2v+1,i+3v]$

这一段是一个斜率 $k=-1$ 的直线，那么就可以在$i+2v+1$ 处将斜率转变$-2$

$$poi[x+2*v+1]-=2$$

- $[i+3v+1,+\infty]$

这一段是一个斜率 $k=0$ 的直线，那么就可以在$i+2v+1$ 处将斜率转变$+1$

$$poi[x+3*v+1]++$$

好像有几个坐标忘记画了QAQ，貌似影响看图，~~欢迎盗图~~

#### 细节

因为考虑到会有减这个操作，所以就把整个位置向右边移动一个很大的数就可以啦

#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
const int N=3e6+9;
const int turn=6e4+9;
int poi[N];
int ret,tot;
int n,m;//朋友的数目，和河的宽度
int read()
{
    int f=1,x=0;
    char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
    return x*f;
}
int main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;i++)
    {
        int v=read();
        int x=read();
        poi[x-3*v+1+turn]++;//表示开始向上升了
        poi[x-2*v+1+turn]-=2;//向下降
        poi[x+1+turn]+=2;
        poi[x+2*v+1+turn]-=2;
        poi[x+3*v+1+turn]++;
    }
    for(int i=0;i<=turn+m;i++)
    {
        tot+=poi[i];
        ret+=tot;
        if(i>=turn+1)
            printf("%d ",ret);
    }
    return 0;
} 
```


---

## 作者：smallfang (赞：2)


题目大致意义：从一个点开始。左右两边**有规律的**变化，最后输出变化后的结果。

所以这道题就是一个差分。

那么我们就要找到差分的式子。由于这道题每次波动时，数值为稳定上升和下降。所以不是很毒瘤，并不需要一个数来记录从上向下更高的距离。如果这么说不太好理解，那就画个图吧。

![lll.png][1]

此题是类似于B的图片。其他难题（duliu）题的波动会是A.那便是另外一道题了。

当然类似于A的毒瘤的题目也不是没有。。。可以去看看三步必杀。。。挺有意思的一道差分题.

当然我们可以画一个草图。然后得到公式：

```
r[x - 3 * v + 1] ++;
r[x - 2 * v + 1] -= 2;
r[x + 1] += 2;
r[x + 2 * v + 1] -= 2;
r[x + 3 * v + 1] ++;
```

![lll.png][2]

当然，这个东西一定要从最小的位置开始。因为一开始也是会有波动的。

然后您就可以写出了这道题的代码：

```cpp

#include <cstdio>

using namespace std;

int n, m;
int r[100001];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++ )
    {
        int v, x;
        scanf("%d%d", &v, &x);
        r[x - 3 * v + 1] ++;
        r[x - 2 * v + 1] -= 2;
        r[x + 1] += 2;
        r[x + 2 * v + 1] -= 2;
        r[x + 3 * v + 1] ++;
    }
    int sum = 0, res = 0;
    for(int i = -10000; i <= 0; i ++)//加上一开始的波动
    {
        sum += r[i];
    }
    for(int i = 1; i <= m; i ++ )
    {
        //printf("%d ", r[i]);
        sum += r[i];
        res += sum;
        printf("%d ", res);

    }
}

```
提交之后，~~可以愉悦的说一声：还没过呢~~，发现这个方法爆炸了,具体问题就处在i-3v+1

如果i=0,3v很大该怎么办呢？

不就直接越界RE了嘛。。。

现在一共是两个办法

### 法1：STL-Map

时间复杂度超标但是可以有效防止负数。

```cpp

#include <map>
#include <cstdio>
#define max(a,b) a>b?a:b

using namespace std;

int n, m;
map<int, int> r;

int main()
{
    scanf("%d%d", &n, &m);
    int maxv = 0;
    for(int i = 1; i <= n; i ++ )
    {
        int v, x;
        scanf("%d%d", &v, &x);
        maxv = max(maxv, 3 * v + 1);
        r[x - 3 * v + 1] ++;
        r[x - 2 * v + 1] -= 2;
        r[x + 1] += 2;
        r[x + 2 * v + 1] -= 2;
        r[x + 3 * v + 1] ++;
    }
    //printf("%d\n", maxv);
    int sum = 0, res = 0;
    for(int i = - maxv; i <= 0; i ++ )
    {
        sum += r[i];
        res += sum;
    }
    for(int i = 1; i <= m; i ++ )
    {
        //printf("%d ", r[i]);
        sum += r[i];
        res += sum;
        printf("%d ", res);

    }
}

```

70分到手

###  法2:

这个方法就是将所有的数加上一个很大的数防止泄露。

最后i+3v这个值也很大
所以差不多2000万才能装下。这道题数组开小一点也会RE到怀疑人生（

最后AC代码：

```cpp
#include <cstdio>
#define max(a,b) a>b?a:b

using namespace std;

inline int read()
{
    int X = 0;
    bool flag = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
            flag = 0;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        X = (X << 1) + (X << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return X;
    return ~(X - 1);
}

int n, m;
int r[2050001];

int main()
{
    n = read();
    m = read();
    int maxv = 0;
    for(int i = 1; i <= n; i ++ )
    {
        int v, x;
        v = read();
        x = read();
        r[x - 3 * v + 1 + 55000] ++;
        r[x - 2 * v + 1 + 55000] -= 2;
        r[x + 1 + 55000] += 2;
        r[x + 2 * v + 1 + 55000] -= 2;
        r[x + 3 * v + 1 + 55000] ++;
    }
    //printf("%d\n", maxv);
    int sum = 0, res = 0;
    for(int i = 0; i <= 55000; i ++ )
    {
        sum += r[i];
        res += sum;
    }
    for(int i = 55001; i <= m + 55000; i ++ )
    {
        //printf("%d ", r[i]);
        sum += r[i];
        res += sum;
        printf("%d ", res);
    }
}
```

Finally, Thanks for your read!

  [1]: https://www.smallfang.fun/usr/uploads/2020/04/2976220799.png
  [2]: https://www.smallfang.fun/usr/uploads/2020/04/881495832.png

---

## 作者：见默思 (赞：2)

~~加个O2跑到了最优解第四名~~

正解就是差分套差分，考虑每个落水的点对差分的贡献，画出来图就会发现，转折点只有三个。

而且如果一个点原来是+1，然后突然变成-1，其实对于差分的贡献是-2，反之亦然，如果-1，那么贡献就是+2

x - 3 * v 这个地方如果在1的右边，作为整个波的起始点，对于差分的贡献只有+1，但是如果x - 3 * v在1的左边，就比较难弄了

详见代码
```cpp
void init(int v,int x){
	if(x - 3 * v > 1){ //如果转折点1在1右边
		sum[x - 3 * v] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		return;
	}
	if(x - 3 * v == 1){//转1在1
		sum[1] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		return;
	}
	if(x - 3 * v < 1 && x - 2 * v > 1){//转1在1左，转2在一右
		sum[1] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		pre += (1 - (x - 3 * v));
		return;
	}
	if(x - 2 * v == 1){//转2在1上
		sum[1] --;
		sum[x] += 2;
		pre += v;
		return;
	}
	if(x - 2 * v < 1 && x > 1){//转2在一左，x在1右
		sum[1] --;
		sum[x] += 2;
		pre += (v - (1 - (x - 2 * v)));
		return;
	}
	if(x == 1){//x在一上
		sum[1] ++;
		pre -= v;
		return;
	}
}
void init1(int v,int x){//对于x的右边的差分讨论就比较方便了
	if(x + 3 * v < n){
		sum[x + 2 * v] -= 2;
		sum[x + 3 * v] ++;
		return;
	}
	if(x + 2 * v < n){
		sum[x + 2 * v] -= 2;
		return;
	}
}
```
剩下的就从一到n跑一次，每次把dif += sum[i] 就是差分了

然后pre += dif，输出pre

上完整代码
```cpp
#include <cstdio>
using namespace std;
const int M = 1e6;
int pre = 0;
int sum[M + 5];
int n,m;
int read(){
	int s = 0,f = 1;
	char ch;
	ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-1') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
void init(int v,int x){
	if(x - 3 * v > 1){
		sum[x - 3 * v] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		return;
	}
	if(x - 3 * v == 1){
		sum[1] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		return;
	}
	if(x - 3 * v < 1 && x - 2 * v > 1){
		sum[1] ++;
		sum[x - 2 * v] -= 2;
		sum[x] += 2;
		pre += (1 - (x - 3 * v));
		return;
	}
	if(x - 2 * v == 1){
		sum[1] --;
		sum[x] += 2;
		pre += v;
		return;
	}
	if(x - 2 * v < 1 && x > 1){
		sum[1] --;
		sum[x] += 2;
		pre += (v - (1 - (x - 2 * v)));
		return;
	}
	if(x == 1){
		sum[1] ++;
		pre -= v;
		return;
	}
}
void init1(int v,int x){
	if(x + 3 * v < n){
		sum[x + 2 * v] -= 2;
		sum[x + 3 * v] ++;
		return;
	}
	if(x + 2 * v < n){
		sum[x + 2 * v] -= 2;
		return;
	}
}
int main(){	
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= m;i ++){
		int v,x;
		v = read();x = read();
		init(v,x);
		init1(v,x);
	//	for(int i = 1;i <= n;i ++) printf("%d ",sum[i]);
	}
	int dif = 0;
	for(int i = 1;i <= n;i ++){
		printf("%d ",pre);
		dif += sum[i];//求dif
		pre += dif;//求差分
	}
	return 0;
}
```


---

## 作者：沧海映繁星 (赞：1)

## **废话**

这是一个极其良（dú）心（liú）的题目

它考察了我们的数学知识和物理知识 ~~尽管很不科学~~

告诉了我们，如何制造更多的水

还告诫了我们：一定不要轻易跳水

## **正题**

好吧，接下来看题目

题目描述中，小正方形的坠（xián）入（dé ）黑（dàn）暗（téng）的朋友，跳入了水中，使水位发生了变化

大致如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/lgjm30h9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当本蒟蒻，第一眼看到这个题目时，首先想到的就是暴力

不过显然，这样会T穿

所以，纯暴力是不行的，需要寻找其他方法

仔细观察题目，发现水位的增长，都是以图中标出的7个点为界限，按一定的规律增长的

将每次增长的高度列出，我们将会看到一堆连着的 1 和 -1

然后，就可以将题目成功的转化为线段树的区间修改

再加上前缀和，即可以解决问题

当然，要注意：注意判断 1 和 m 的位置，不然会出事

接下来上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lp mid << 1
#define rp mid << 1 | 1
#define maxn 2000005
#define int long long
int n,m,x,v;
int f[maxn];
int k1,k2,k3,k4,k5,k6,k7;
int sum[maxn * 4],lazy[maxn * 4];
int read(){
    int t = 0,f = 1;
    char s;
    s = getchar();
    while(s < '0' || '9' < s){
        if(s == '-') f = -1;
        s = getchar();
    }
    while('0' <= s && s <= '9'){
        t = t << 1 + t << 3 + s -'0';
        s = getchar();
    }
    return t * f;
}
void lazys(int p,int l,int r,int k){
    lazy[p] += k;
    sum[p] += (r - l + 1) * k;
}
void down(int p,int l,int r){
    int mid = (l + r) >> 1;
    lazys(lp,l,mid,lazy[p]);
    lazys(rp,mid + 1,r,lazy[p]);
    lazy[p] = 0;
    return;
}
void add(int p,int l,int r,int L,int R,int k){
    if(L <= l && r <= R){
        lazys(p,l,r,k);
        return;
    }
    down(p,l,r);
    int mid = (l + r) >> 1;
    if(L <= mid) add(lp,l,mid,L,R,k);
    if(R > mid) add(rp,mid + 1,r,L,R,k);
    sum[p] = sum[lp] + sum[rp];
}
void query(int p,int l,int r){
    if(l == r){
        f[l] = sum[p];
        return;
    }
    down(p,l,r);
    int mid = (l + r) >> 1;
    query(lp,l,mid);
    query(rp,mid + 1,r);
    // sum[p] = sum[lp] + sum[rp];
    return;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld",&v,&x);
        k1 = x - 3 * v;
        k2 = x - 2 * v;
        k3 = x - 1 * v;
        k4 = x;
        k5 = x + 1 * v;
        k6 = x + 2 * v;
        k7 = x + 3 * v;
        if(1 <= k1){
            add(1,1,m,k1 + 1,k2,1);
            add(1,1,m,k2 + 1,k4,-1);
        }
        if(k1 < 1 && 1 <= k2){
            add(1,1,m,1,1,1 - k1);
            add(1,1,m,2,k2,1);
            add(1,1,m,k2 + 1,k4,-1);
        }
        if(k2 < 1 && 1 <= k4){
            add(1,1,m,1,1,k3 - 1);
            add(1,1,m,2,k4,-1);
        }
        if(k4 < m && m <= k6){
            add(1,1,m,k4 + 1,m,1);
        }
        if(k6 < m && m <= k7){
            add(1,1,m,k4 + 1,k6,1);
            add(1,1,m,k6 + 1,m,-1);
        }
        if(k7 < m){
            add(1,1,m,k4 + 1,k6,1);
            add(1,1,m,k6 + 1,k7,-1);
        }
    }
    query(1,1,m);
    for(int i = 1; i <= m ;i++){
        f[i] += f[i - 1];
        printf("%lld ",f[i]);
    }
    return 0;
}
```
然后，就可以高高兴兴得去AC了吗？

那是当然…………………………不可能的

不然我还写后面写干嘛？闲得慌吗？

线段树做法时间复杂度为 O（n logn）

而这个良（dú）心（liú）出题人将数据开到了$10^6$这已经超过了线段树能做的范围

那么，该怎么做呢？

让我们再看看题目要求：输出最终水位

也就是说，我们不需要像线段树一样的多次询问，只需输出最终结果

问：那我们为什么还要写线段树？

答：~~闲得慌~~ 因为一开始没想到

也就是说，我们只需要对水位值的变化进行差分，再在最后求前缀和就行了

一下才是真正的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 2000005
#define int long long
int n,m,x,v;
int f[maxn],p[maxn];
int k1,k2,k3,k4,k5,k6,k7;
int read(){
    int t = 0,f = 1;
    char s;
    s = getchar();
    while(s < '0' || '9' < s){
        if(s == '-') f = -1;
        s = getchar();
    }
    while('0' <= s && s <= '9'){
        t = t << 1 + t << 3 + s -'0';
        s = getchar();
    }
    return t * f;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld",&v,&x);
        k1 = x - 3 * v;
        k2 = x - 2 * v;
        k3 = x - 1 * v;
        k4 = x;
        k5 = x + 1 * v;
        k6 = x + 2 * v;
        k7 = x + 3 * v;
        if(1 <= k1){
            p[k1 + 1] ++;
            p[k2 + 1] --;
            p[k2 + 1] --;
            p[k4 + 1] ++;
        }
        if(k1 < 1 && 1 <= k2){
            f[1] += 1 - k1;
            p[2] ++;
            p[k2 + 1] --;
            p[k2 + 1] --;
            p[k4 + 1] ++;
        }
        if(k2 < 1 && 1 <= k4){
            f[1] += k3 - 1;
            p[2] --;
            p[k4 + 1] ++;
        }
        if(k4 < m && m <= k6){
            p[k4 + 1] ++;
        }
        if(k6 < m && m <= k7){
            p[k4 + 1] ++;
            p[k6 + 1] --;
            p[k6 + 1] --;
        }
        if(k7 < m){
            p[k4 + 1] ++;
            p[k6 + 1] --;
            p[k6 + 1] --;
            p[k7 + 1] ++;
        }
    }
    for(int i = 1; i <= m ;i++){
        p[i] += p[i - 1];
        f[i] += f[i - 1] + p[i];
        printf("%lld ",f[i]);
    }
    return 0;
}
```


---

## 作者：Su_Zipei (赞：0)

## 题意

　　在一个长度为$m$的序列中，每次给一个下标$x$，和一个权值$v$，然后从$x-v*3$到$x-v*2$单调递增，从$x-v*2$到$x$单调递减，从$x$到$x+v*2$再次递增，然后$x+v*2$到$x+v*3$递减，递增递减都是斜率绝对值为1的直线。
## 分析
　　刚学了差分趁现在还没忘赶紧把自己想的写下来
  
　　看到这个其实很容易想到，对于每次修改，将其分为四个区间进行修改，由于它是单调递增的，所以让每个点对应的差分数组加一就行，这样就用到了线段树维护差分数组，但这样还是效率不是很高，我们仍然可以优化，对于同一区间内的每个点与前一个点的差值也是一定的，所以只要修改区间的两端就可以使整个区间内的差值改变，这样两个点的差值就可以构成一个差分数组，然后通过对这个差分数组求前缀和，可以得到每个点与前一个点的差值，再然后更新每个点值的前缀和数组，然后就可以得到这个点的值，输出就行，也就是，差分套差分。

　　其实这个挺简单的，仔细想想也  很容易  ~~困难~~  想得出来

　　最后是关于负数的问题，数组下标是不能为负数的，会$RE$，某大佬的做法是将原点左移，我试了试也是可以的，后来在洛谷上学习了一篇题解的做法，觉得这个很不错，直接用一个指针来代替数组，其实数组的实质也是指针，比如数组$aa_{10}$->从指针$aa$开始往后数10个，所以只要让一个指针指向数组中间就能实现负下标的数组，感觉挺~~实用~~ 好玩。
　
```
#include<cstdio>
const int N=2e6;//记得开大点，不然会被一些极大的数据RE掉
int aa[N<<1],bb[N<<1];
int main(){
    int *a=aa+N,*b=bb+N;
    int m,n;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int v,x;
        scanf("%d%d",&v,&x);
        a[x-v*3+1]++;
        a[x-v*2+1]-=2;
        a[x+1]+=2;
        a[x+v*2+1]-=2;
        a[x+v*3+1]++;
    }
    for(int i=-40000;i<=40000+m;i++)
        a[i]+=a[i-1],b[i]+=b[i-1]+a[i];
    for(int i=1;i<=m;i++)
        printf("%d ",b[i]);
    return 0;
}
```
 

 



---

