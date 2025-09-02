# [JRKSJ R1] JFCA

## 题目描述

给出一个环，上面有 $n$ 个点，每个相邻的点对之间的距离为 $1$。

每个点有两个属性 $a_i$ 和 $b_i$，对于点 $i$，定义 $f_i$ 为它与满足 $i\ne j$ 且 $a_j\ge b_i$ 的 $j$ 与 $i$ 在环上的最短距离。特殊地，如果没有满足条件的 $j$，其 $f_i=-1$。

## 说明/提示

### 数据规模与约定

对于 $20\%$ 的数据，$1\le n \le 10^3$；\
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le a_i,b_i\le 10^9$。

我们对于测试点 $4$ 至 $11$ 采用捆绑测试。

### 样例 1 解释
对于 $i=1$，$a_3=3= b_1=3$, $1$ 和 $3$ 的距离是 $1$，所以 $f_1=1$。\
对于 $i=2$，$a_3=3> b_2=2$, $2$ 和 $3$ 的距离是 $1$，所以 $f_2=1$。\
对于 $i=3$，$a_2=2> b_3=1$, $2$ 和 $3$ 的距离是 $1$，所以 $f_3=1$。

$\text{Upd 2021.3.30}$：增加一组 hack 数据。


## 样例 #1

### 输入

```
3
1 2 3
3 2 1```

### 输出

```
1 1 1```

## 样例 #2

### 输入

```
5
5 4 3 5 6
7 6 5 4 3```

### 输出

```
-1 2 1 1 1```

## 样例 #3

### 输入

```
5
1 1 2 1 1
2 2 2 2 2```

### 输出

```
2 1 -1 1 2```

# 题解

## 作者：cyffff (赞：21)

### T1 JFCA
#### Subtask 1
这个 $Subtask$ 中 $n \leqslant 10^3$ ,暴力 $O(n^2)$ 向左右拓展即可，但是由于没有 $O2$，只能通过数据点 $1$ 至 $4$ 数据点（数据点 $4$ 可极限通过），期望得分 $20$.

#### Subtask 2
采用捆绑测试，$10^5$ 的数据可以想到要用 $O(n\log n)$ 的算法。

于是我们可以想到二分，但是 $a_j$ 没有单调性。于是我们可以维护区间最大值，满足单调性。

由于题目说这是一个环，我们可以使用分类讨论或者断环为链，这篇题解主要讲断环为链。

我们将每个数存 $3$ 遍，即 $a_{i+n+n}=a_{i+n}=a_i$.

定义 $f(i,j)=\max_{k=i}^j a_k$，我们设当前处理的是序号为 $i$ 的数，则 $check(x)=\max(f(i-x,i-1),f(i+1,i+x))$ 。

我们对于$i+n$ 二分一次即可。


注意事项：
- 1.断环为链时，我们复制 $3$ 遍的原因是处理较后的数时可能会造成数组越界错误。
- 2.我们可以使用 $ST$表 平衡复杂度到 $n\log n$，也可以使用其他数据结构如线段树做到 $n\log^2 n$ 的复杂度。
- 3.由于 $i\ne j$，求区间最大值时不能直接算 $f(i-x,i+x)$。


接下来就可以愉快的二分了，不理解的和剩余的内容可以结合代码理解。

$std$:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,st[N][30],lg[N];
namespace IO{
	//read(),write()
}using namespace IO;
inline int query(int l,int r){
	int q=lg[r-l+1];
	return max(st[l][q],st[r-(1<<q)+1][q]);
}
inline int ef(int x,int i){//二分
	int l=1,r=n;
	while(l<r){
		int mid=l+r>>1;
		if(max(query(i-mid,i-1),query(i+1,i+mid))>=x){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	return l==n?-1:l;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){//断环为链
    	st[i][0]=st[i+n][0]=st[i+n+n][0]=read();
	}
	for(int i=2;i<=n+n+n;i++){
	    lg[i]=lg[i>>1]+1;
	}
	int ln=lg[n+n+n];
	for(int i=1;i<=ln;i++){//ST表预处理
		for(int j=1;j+(1<<i)-1<=n+n+n;j++){
			st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
		}
	}
	for(int i=1;i<=n;i++){
		int b=read();
		int a2=ef(b,i+n);
		write(a2);
		out[len++]=' ';
	}
	fwrite(out,1,len,stdout);
    return 0;
}
```
这道题作为 $T1$ 还是很水的，后面的题就很毒瘤了。

感谢大家参与这场比赛！

---

## 作者：Durancer (赞：11)

### 前言

考察二分和 $\text{ST}$ 表的结合运用。

### 思路

既然说好了是劣弧，所以肯定只能在向左或者向右的 $\dfrac{len}{2}$ 个点中寻找（~~貌似不说也是这么干~~）。

再看如何寻找最小长度，线性一个个查找肯定不现实，所以就考虑区间最大值如何去操作。

可以发现有一个性质，一个区间内，一旦一个端点被固定下之后，这个区间内的最大值会随着区间的扩大而**非严格单调递增**，那么就找到这个区间的单调性了，现在多了一个二分可以选择。

维护区间最大值，看数据范围，可以用 $\text{ST}$ 表进行维护。

现在就有了一种做法，确定一个位置，然后向前向后分别二分进行查找。

时间复杂度为 $O(n\log n)$ ，可以通过此题。

至于如何断环成链，可以想一想：因为我们是要从左面和右面查找，那么前面和后面我们应该是存储一个完整的链，而我们当前固定的点是在中间的，所以就开**三倍**空间，复制三次链。以中间一条链为基准，进行前面后面的查找。

### 坑点

二分的时候可能随手就写成了这种形式qwq。

```cpp
	int l=i-len+1;
    	int r=i;
    	//或者是
        int l=i;
        int r=i+len-1;
```
其实这种想法是 $\text{very}$ 错误的，以为我们要找到区间一定是不能包含 $i$ 这个点的，因为一旦这样那么有时候会出现一个奇奇怪怪的错误，注意看题目（$i\neq j$）

而且 `i+len-1` 这种做法也是错误的，自己手膜一下发现根本不需要 $+1-1$ 的操作。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
const int N=1e5+9;
const int M=23;
int Max[N*3][M+1];//a[i]的最大值 
//处理中间一个复制的环的时候向左右挪动可能会发生数组越界，
//所以直接三倍，只处理中间一环即可。
//当一个端点确定是，该区间扩展时，最大值非严格单调递增，用二分，+st表维护 
int Log[N];
int a[N],b[3*N];
int n;
int f[N];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
} 
int max(int a,int b)
{
	if(a>b) return a;
	else return b;
}
int min(int a,int b)
{
	if(a<b) return a;
	else return b;
}
int RMQ(int l,int r)
{
	int k=Log[r-l+1];
	return max(Max[l][k],Max[r-(1ll<<k)+1][k]);
}
void prepare()
{
	for(int i=1;i<=n;i++)//每次二分最长为一个链，不需要处理过多 
		Log[i]=log2(i);
	for(int j=1;j<M;j++)
		for(int i=1;i+(1ll<<j)-1<=3*n;i++)
			Max[i][j]=max(Max[i][j-1],Max[i+(1ll<<(j-1))][j-1]);
}
void erfen()
{
	int len=n/2;
	for(int i=n+1;i<=n+n;i++)
	{
		int ans=0x3f3f3f3f;
		if(RMQ(i-len,i-1)>=b[i])// 找左边 |i-len+1-----i-1|//注意没有i！！！ 
		{
			int l=i-len;
			int r=i-1;//Wrong，最后不能有i这个位置 
			while(l<=r)
			{
				int mid=(l+r)>>1;
				int cal=RMQ(mid,i-1);
				//printf("l= %d , r= %d , mid= %d , cal= %d\n",l,r,mid,cal);
				if(cal>=b[i])//Wrong在这个范围内有，缩小范围 
				{
					//std::cout<<"b[i]= "<<b[i]<<std::endl;
					ans=min(ans,i-mid);
					l=mid+1;
				}
				else r=mid-1;//扩大范围继续找 
			}
		}
		if(RMQ(i+1,i+len)>=b[i])// 找右边 |i+1------i+len-1|，不要包含i！！！ 
		{
			int l=i+1;
			int r=i+len;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				int cal=RMQ(i+1,mid);//Wrong 
				//printf("l= %d , r= %d , mid= %d , cal= %d\n",l,r,mid,cal);
				if(cal>=b[i])
				{
					ans=min(ans,mid-i);
					r=mid-1;
				}
				else l=mid+1; 
			}
		}
		if(ans!=0x3f3f3f3f)
			printf("%d ",ans);
		else printf("-1 ");
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		Max[i][0]=Max[i+n][0]=Max[i+n+n][0]=read();
	for(int i=1;i<=n;i++)
		b[i]=b[i+n]=b[i+n+n]=read();
	prepare();
	erfen();
	return 0;
}
```

---

## 作者：Terac (赞：5)

[**_原题_**](https://www.luogu.com.cn/problem/P7333)  

一道不难的题目。  

题意已经很明确了。我们发现数据范围是 $1\leq n\leq 10^5$，可以想到正解是一个 $\mathcal{O}(n\sqrt {n})$ 或 $\mathcal{O}(n \log n)$ 的做法。  

## 题解  


我们要找到与 $x$ 距离最近的 $i$，显然是按从 $x$ 递增和递减两个方向去比较。复杂度劣的主要原因是比较很多不满足条件的数，即 $a_i$ 的值比 $b_x$ 小。  

为了优化复杂度，我们维护一个区间内 $a_i$ 最大值，如果区间最大值比  $b_x$ 小，那整个区间都不会有符合题意的 $a_i$，大大减少了比较次数。  

但因为这是一个环，为了断环成链，需要开三倍空间，方便处理左右边界，并将原来的 $\left[1,n\right]$ 放到 $\left[n+1,n+n\right]$ 内处理，同时还有个小细节，即特判当 $f_x=n$ 时，这说明 $x$ 绕了 $n$ 个数回到了 $x$，此时将 $f_x \gets -1$。


容易想到分块。  

对于 $x$ 所在的块内，直接暴力枚举块边。然后像原来一样，按距 $x$ 的距离递增比较每个块，若块内最大值大于 $b_x$，就继续按距 $x$ 的距离递增比较每个数，找到距 $x$ 最近的 $i$ 使 $a_i \geq b_x$。  

时间复杂度为 $\mathcal{O}(n\sqrt{n})$，但因为对于随机期望运行次数很少，跑得飞快。  

您也可以像出题人那样写二分 ST 表，思路都很简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n , a[N * 3] , b[N * 3] , belong[N * 3] , f[N];
int L , C , s[N * 3] , t[N * 3] , maxx[N * 3];
void init() {
    C = 0;
    L = sqrt(3 * n);
    for(int i = 1; i <= n * 3; i += L) {
        s[++ C] = i;
        t[C] = min(n * 3 , i + L - 1);
        for(int j = s[C]; j <= t[C]; j ++) {
            belong[j] = C;
            maxx[C] = max(maxx[C] , a[j]);
        }
    }
}
int query_l(int x , int k) {
	int edge = belong[x];
	for(int i = x - 1; i >= s[edge]; i --) 
		if(a[i] >= k) 
			return x - i;
	for(int i = edge - 1; i >= 1; i --) 
		if(maxx[i] >= k) 
			for(int j = t[i]; j >= s[i]; j --) 
				if(a[j] >= k) 
					return x - j;
	return -1;
}
int query_r(int x , int k) {
	int edge = belong[x];
	for(int i = x + 1; i <= t[edge]; i ++) 
		if(a[i] >= k) 
			return i - x;
	for(int i = edge + 1; i <= C; i ++) 
		if(maxx[i] >= k) 
			for(int j = s[i]; j <= t[i]; j ++) 
				if(a[j] >= k) 
					return j - x;
	return -1;
}
int main() {
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++) 
		scanf("%d" , &a[i]) , a[i + n] = a[i] , a[i + n + n] = a[i];
	for(int i = 1; i <= n; i ++)
		scanf("%d" , &b[i]);
	init();
	for(int i = 1; i <= n; i ++) {
		f[i] = min(query_l(n + i , b[i]) , query_r(n + i , b[i]));
		if(f[i] == n) 
			f[i] = -1;
	}
	for(int i = 1; i <= n; i ++) 
		printf("%d " , f[i]);
	return 0;
}
```  

---

## 作者：wfycsw (赞：5)

我的做法与楼上的几位巨佬们的截然不同，说到底还是没有灵敏地一眼看出可以用**二分**做,但是，我的这种方法也并不比他们慢。

接下来讲一讲我的方法，首先题目中说是一个n个点的**环**，所以我们在输入时**断环为链**：
```cpp
for(RI i=1;i<=n;i=-~i){
	scanf("%d",&a[i]);
	a[i+n]=a[i];
}
for(RI i=1;i<=n;i=-~i){
	scanf("%d",&b[i]);
	b[i+n]=b[i];
}
```
然后,循环逐一求解，不过对于双重循环的$O(n^2)$复杂度是必定会超时的，所以我们要进行一些**剪枝和优化**。

对于$a_i$,它可以帮助其他$b_i$求解，因此我们要把它存下来，不过并不是所有的都要存，因为但$a_i$比$a_j$大且$i>j$,则完全可以将$a_j$从中**删去**，所以我们就可以用个**单调栈**存储：
```cpp
for(RI j=t;j>0;--j)
	if(d[j][1]>=b[i]){
		if(i%n==d[j][0]) break;
		f[i%n]=min(f[i%n],i-d[j][0]);//记录答案
		break;
	}
while(d[t][1]<=a[i]&&t) --t;//删除元素
d[++t][1]=a[i];d[t][0]=i;
```

对于$b_i$,就不能将它删去，因为那样就没有答案了。所以只能在每次循环时比较$a_i$和$b_j$的大小，如果$b_j\le a_j$,则记录答案。但是逐一比较的话其复杂度又会退回到$O(n^2)$。发现每次大循环$a_i$只有一个，但$b_j$有多个，于是便可以给b装一个**优先队列**，当$a_i$小于前面较小的元素时就可直接退出循环:

```cpp
while(q.size()&&a[i]>=-q.top().first){
	if(i%n==q.top().second) break;
	f[q.top().s%n]=min(f[q.top().s%n],i-q.top().s);//记录答案
	q.pop();
}
q.push((du){-b[i],i});
```

接下来奉上完整的代码:

```cpp
#include<bits/stdc++.h>
#define RI register int
#define du pair<int,int> 
#define f first
#define s second
#define ru(x,y) q.push((du){-x,y})
using namespace std;
const int N=1e5+3;
int a[N<<1],b[N<<1],f[N],d[N<<1][2];
inline int min(int x,int y){return x<y?x:y;}
priority_queue<du>q;
int main(){
	RI n,t=0;
	memset(f,127/3,sizeof f);
	scanf("%d",&n);
	for(RI i=1;i<=n;i=-~i){
		scanf("%d",&a[i]);
		a[i+n]=a[i];
	}
	for(RI i=1;i<=n;i=-~i){
		scanf("%d",&b[i]);
		b[i+n]=b[i];
	}
	for(RI i=1,m=n<<1;i<=m;i=-~i){
		for(RI j=t;j>0;--j)
			if(d[j][1]>=b[i]){
				if(i%n==d[j][0]) break;
				f[i%n]=min(f[i%n],i-d[j][0]);
				break;
			}
      while(d[t][1]<=a[i]&&t) --t;
		d[++t][1]=a[i];d[t][0]=i;
		while(q.size()&&a[i]>=-q.top().f){
			if(i%n==q.top().s) break;
			f[q.top().s%n]=min(f[q.top().s%n],i-q.top().s);
			q.pop();
		}
		ru(b[i],i);
	}
	for(RI i=1;i<n;i=-~i)
		printf("%d ",f[i]>n?-1:f[i]);
	printf("%d",f[0]>n?-1:f[0]);//注意n%n==0
	return 0;
}
```
总的时间复杂度也是$O(nlogn)$,加上亿些卡常的话可以27ms跑过。

---

## 作者：Scorilon (赞：4)

### 题意

给定一个长度为 $n$ 的环，求一个 $a_j \ge b_i$ 且距离最近的点。

### 题解

对于 $20\%$ 的点，直接暴力向左右扩展就可以。

对于 $100\%$ 的点，先断环成链，三倍空间。我们注意到随着区间的扩大，最大值是呈非严格单调递增的状态的。因为区间扩大的同时也包含着原区间，那么最大值不会小于原最大值。根据这个可以进行二分，单次询问时间复杂度 $O(\log n)$.

同时可以用 $\tt{ST}$ 表来平衡时间复杂度，总复杂度 $O(n\log n)$.

要注意 $i \not= j$.

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int N=3e5+5;
const int Logn=23;

int n;
int logn[N],f[N][Logn+5];

void init() {//打一个log2的表
	logn[1]=0;
	logn[2]=1;
	for(int i=3;i<=n+n+n;i++) logn[i]=logn[i>>1]+1;
}

int query(int l,int r) {//查询区间最大值
	int s=logn[r-l+1];
	return max(f[l][s],f[r-(1<<s)+1][s]);
}

int binary_search(int a,int x) {//二分
	int l=1,r=n;
	while(l<r) {
		int mid=l+((r-l)>>1);//等同于l+r>>1
		if(max(query(x-mid,x-1),query(x+1,x+mid))>=a) r=mid;
		else l=mid+1;	
	}
	return l==n?-1:l;
}

int main() {
	n=read();
	for(int i=1;i<=n;i++) f[i+n+n][0]=f[i+n][0]=f[i][0]=read();//断环成链
	init();
	for(int j=1;j<=Logn;j++) {
		for(int i=1;i+(1<<j)-1<=n+n+n;i++) {
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=n;i++) {
		int b=read();
		printf("%d ",binary_search(b,i+n));
	}
	return 0;
}
```


---

## 作者：cmll02 (赞：4)

ST 表 + 二分，时间复杂度 $O(n\log n)$ 做法。

发现我们要找的东西和区间最大值有关。

然后这东西不用修改。

显然想到 ST 表。

然后发现对于端点固定的一个区间，$\max$ 值单调不降。

很明显的二分了。

实现看代码，注意判边界和 $-1$，断环成链开三倍空间即可。

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=1e6+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int Max[MAXN][21];
int Query(int l,int r)
{
    int k=log2(r-l+1); 
    return max(Max[l][k],Max[r-(1<<k)+1][k]);}
int main()
{
    int N=read(),M=N;
    for(int i=1;i<=N;i++) Max[i][0]=Max[i+N][0]=Max[i+N+N][0]=read();
    for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=N+N+N;i++)
            Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
    for(int i=1;i<=M;i++)
    {
        int x=read();
        int l=i+1,r=N+i-1,ans=-1,res=99999999;
        if(Query(l,r)<x)
        {
            l=N+i+1,r=N+N+i-1;
            if(Query(l,r)<x){printf("-1 ");continue;}
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(Query(N+i+1,mid)>=x)ans=mid,r=mid-1;
                else l=mid+1;
            }
            printf("%d ",ans-i-N);
        }
        else
        {
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(Query(mid,N+i-1)>=x)ans=mid,l=mid+1;
                else r=mid-1;
            }
            res=i+N-ans;
        }
        l=N+i+1,r=N+N+i-1;
        if(Query(l,r)<x){printf("%d ",res);continue;}
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(Query(N+i+1,mid)>=x)ans=mid,r=mid-1;
            else l=mid+1;
        }
        int yp=ans-i-N;if(yp>res)yp=res;
        printf("%d ",yp);
    }
    return 0;
}
```

---

## 作者：ZBH_123 (赞：3)

## 大体思路：二分查找+ST 表优化
没有读题的点击这里：[题目传送门](luogu.com.cn/problem/P7333)

首先，通过题目我们可以得知，本题要求的就是对于每一个 $b_i$，在环上查找到距离最近的一个 $a_j$，使得 $a_j \ge b_i$。而 $a_j$ 所在的位置就是 $f_i$。


那么第一个问题是，如何把一个环展开，变成一个序列呢？其实非常简单，我们只需要把数组下标开到 $2 \times n$，$a_{n+1} \sim a_{2 \times n}$ 存储 $a_1 \sim a_n$ 的值，对于 $b$ 数组同理。这时，我们就会发现，$b_i$ 这个值在整个序列里出现了两次，一次在 $b_i$，另一次在 $b_{i+n}$。那么，我们就可以在整个展开后的序列的左侧查找距离 $b_i$ 最近的满足条件的 $a_j$，在序列的右侧查找距离 $b_{i+n}$ 最近的 $a_j$，再把两次查找的距离进行比较，就可以得出 $f_i$ 啦。


这时，我们自然就能想到二分查找。在左侧查找时，由于最终得到的位置要尽可能的靠左，所以当 $mid$ 左侧的区间存在合法的 $a_j$，那么就往左侧找，否则就往右侧找。在右侧查找时同理。


这时，我们自然就能写出在左侧查找时的二分查找代码：
```cpp
int findleft(int l,int r,int x){
	while(l<r){
		int mid=(l+r)/2;
		if(find(l,mid)>=x)
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
```
现在关键点来了，我们如何判断左侧是否有合法的 $a_j$ 呢？一个一个地去判断吗？这样时间复杂度会高。我们仔细思考一下，由于本题合法的 $a_j$ 是要 $\ge b_i$ 的，那么左侧的区间没有合法的 $a_j$ 就肯定是因为左侧区间所有的 $a_j$ 全部 $< b_i$。这时，我们只需要维护 $a$ 数组的区间最大值，看它是否 $\ge b_i$ 就行了。


维护区间最大值的方法有： ST 表、线段树等。由于这里需要维护静态区间最大值，所以可以不必使用线段树，而是使用查询效率更高的 ST 表。


最后，我们得出了两个距离，如果左边没有合法的 $a_j$，那就输出右边的距离；反之亦然。否则，就输出两个距离中的最小值。如果两边都没有合法的 $a_j$，$f_i$ 就等于 $-1$。这样，我们就能很轻松的写出代码啦。
### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200001],b[200001],f[200001][21],base[200001]={-0x7f,0,1};
void st(){//ST表的模板
	for(int i=3;i<=2*n;i++)
		base[i]=base[i/2]+1;
	for(int i=1;i<=2*n;i++)
		f[i][0]=a[i];
	for(int j=1;j<=base[2*n]+1;j++)
		for(int i=1;i+(1<<j-1)<=2*n;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
}
int find(int l,int r){
	int k=base[r-l+1];
	return max(f[l][k],f[r-(1<<k)+1][k]);//查询区间最大值
}
int findleft(int l,int r,int x){
	while(l<r){
		int mid=(l+r)/2;
		if(find(l,mid)>=x)//左边有合法的就去左边
			r=mid;
		else//没有就去右边
			l=mid+1;
	}
	return l;
}
int findright(int l,int r,int x){
	while(l<r){
		int mid=(l+r)/2;
		if(find(mid+1,r)>=x)//右边有合法的就去右边
			l=mid+1;
		else//否则就去左边
			r=mid;
	}
	return r;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		b[i+n]=b[i];
	}
	st();
	for(int i=1;i<=n;i++){
		if(find(i+1,i+n-1)<b[i])//两边都没有
			cout<<-1<<' ';
		else{
			int x1=findleft(i+1,i+(n-1)/2,b[i])-i;
			int x2=i+n-findright(i+(n-1)/2+1,i+n-1,b[i]);
			if(a[findleft(i+1,i+(n-1)/2,b[i])]<b[i])//左边没有就输出右边的距离
				cout<<x2<<' ';
			else if(a[findright(i+(n-1)/2+1,i+n-1,b[i])]<b[i])//右边没有就输出左边的距离
				cout<<x1<<' ';
			else//否则输出最小值
				cout<<min(x1,x2)<<' ';
		}
	}
}
```


---

## 作者：xfrvq (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P7333)
 
[博客食用](https://www.luogu.com.cn/blog/solution-p7333)

---

**solution 1**
 
直接暴力枚举长度，复杂度 $O(n^2)$ ，可以过 $\text{subtask\space1}$

期 $\text{20pts}$

---

**solution 2**

定义 $\operatorname{Max}(p,q)$ 为 $\max_{i=p}^{i\leq q} a_i$

二分长度，每次取 $\max(\operatorname{MAX}(i-mid,i-1),\operatorname{MAX}(i+1,i+mid))$，判断其是否大于 $b_i$

断环为链，用三倍空间存 $a$ 数组，其中 $a_i=a_{i+n}=a_{i+n+n}$

所以原来的公式应该变成

$$\max(\operatorname{MAX}(n+i-mid,n+i-1),\operatorname{MAX}(n+i+1,n+i+mid))$$

计算两个 $\operatorname{MAX}$ ，用 ST表

注意 ST表 需要开三倍空间，对应 $a$ 数组的断环为链三倍空间

---

代码：

```cpp
#include<stdio.h>
#include<math.h>
int n,n3,a[300001],b[100001];
inline const int& max2(const int& a,const int& b){return a > b ? a : b;}
template<int maxn> struct ST{
	int st[maxn + 1][33];
	void init(){
	    for(int i = 1;i <= n3;++i) st[i][0] = a[i];
		for(int j = 1;(1 << j) <= n3;++j)
			for(int i = 1;i + (1 << j) - 1 <= n3;++i)
				st[i][j] = max2(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
	}
	int query(int l,int r){
		int j = log2(r - l + 1);
		return max2(st[l][j],st[r - (1 << j) + 1][j]);
	}
};
ST<300000> st;
int main(){
	scanf("%d",&n),n3 = n * 3;
	for(int i = 1;i <= n;++i) scanf("%d",a + i),a[i + n] = a[i + n + n] = a[i];
	for(int i = 1;i <= n;++i) scanf("%d",b + i);
	st.init();
	for(int i = 1;i <= n;++i){
		int l = 1,r = n;
		while(l < r){
			int mid = l + r >> 1;
			if(max2(st.query(n + i + 1,n + i + mid),st.query(n + i - mid,n + i - 1)) >= b[i]) r = mid;
			else l = mid + 1;
		}
		if(l == n) printf("-1 ");
		else printf("%d ",l);
	}
	return 0;
}
```


---

## 作者：FxorG (赞：3)

# $\text{Description:}$

环上找一个大于这个点且距离最近的点

# $\text{Solution:}$

不难发现，假如区间 $[l,r]$ 满足条件，显然 $[l,r+1]$ 也满足，满足单调性直接二分max就好，二分长度，然后正反来一次，max直接ST表，然后不写断环成链的话特判一下就好了。

复杂度 $O(n\log n)$

# $\text{Code:}$

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>

#define N (int)(1e5+5) 

using namespace std;

int f[N][20],a[N],b[N],n;

int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}

int gt(int l,int r) {
//	cout<<l<<" "<<r<<endl;
	if(l<1) return max(gt(n+l,n),gt(1,r));
	if(r>n) return max(gt(l,n),gt(1,r-n));
	if(l>r) return 0;
	
	int le=r-l+1,qwq=log2(le); 
	return max(f[l][qwq],f[r-(1<<qwq)+1][qwq]);
} 

int main() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),f[i][0]=a[i];
	for(int i=1;i<=n;i++) b[i]=rd();
	for(int i=1;i<=18;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
	for(int i=1;i<=n;i++) {
		int l=1,r=n-1,answ=0x7fffffff;
		while(l<=r) {
			int mid=(l+r)>>1,res=gt(i+1,i+mid);
			if(res>=b[i]) answ=min(answ,mid),r=mid-1;
			else l=mid+1;
		//	cout<<res<<endl;
		}
		l=1,r=n-1;
		while(l<=r) {
			int mid=(l+r)>>1,res=gt(i-mid,i-1);
			if(res>=b[i]) answ=min(answ,mid),r=mid-1;
			else l=mid+1;
		//	cout<<res<<endl;
		}
		printf("%d ",answ==0x7fffffff?-1:answ);
	}
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：2)

## 前言

[传送门](https://www.luogu.com.cn/problem/P7333)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-p7333)

# 思路

首先看数据范围 $10^5$，$O(n \log_2 n)$ 可以过，自然想到**二分**。

二分具有单调性，那么如何确保整个 $a$ 序列按顺序排列呢？

我们可以使用 **st 表**维护区间最大值，如果在这个距离中已经有了 $a_i\ge b_j$ 那么最大值一定指向的是新加入进来的那个值，否则在之前二分就已经不会再继续扩展了。

对于环形结构我们必须**断环为链**，这样可以将环形变为链形，并且保证答案的正确性。

这时我们就必须要考虑**二分**与**断环为链了**，因为二分会向右扩展 $mid$，所以两倍会越界，那么就需要开三倍。

那么我们如何判断无解呢？在 $l = n$ 时说明已经过了一圈但是还是没有找到 $a_i\ge b_j$，又回到了 $j$，说明无解。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[300010],LOG2[300010],st[300010][30];

inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while (ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while (ch >= '0' && ch <= '9'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

void init(){
	for(int i = 2;i <= 3 * n;i++)
		LOG2[i] = LOG2[i >> 1] + 1; 
	for(int i = 1;i <= n;i++)
		st[i][0] = st[i + n][0] = st[i + n + n][0] = a[i];
	int k = LOG2[3 * n];
	for(int i = 1;i <= k;i++)
		for(int j = 1;j + (1 << i) - 1 <= 3 * n;j++){
			st[j][i] = max(st[j][i - 1],st[j + (1 << i - 1)][i - 1]); 
		}	
}	

int num(int l,int r){
	int s = LOG2[r - l + 1];
	int x = max(st[l][s],st[r - (1 << s) + 1][s]);
	return x; 
}

int two(int x,int y){
	int l = 1,r = n;
	while(l < r){
		int mid = (l + r) >> 1;
		if(max(num(y - mid,y - 1),num(y + 1,y + mid)) >= x)
			r = mid;
		else
			l = mid + 1;
	}
	return l == n ? -1 : l;
} 

int main(){
	n = read(); 
	for(int i = 1;i <= n;++i)
		a[i] = read();
	init();
	for(int i = 1;i <= n;i++){
		int b = read();
		printf("%d ",two(b,i + n));
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：2)

考虑二分距离。

然后来考虑 check 怎么打。

整一个 ST 表维护 $a$ 的最大值，然后二分距离的时候判断距离内有无满足条件的元素即可。

注意此题的坑点在于你 Query 的时候需要注意不能把自己包含进去。

具体来说就是拆询问。

把 一个 $[l,r]$ 拆成 $[l,x],[x+1,r]$，然后讨论一下。

```cpp
#include <bits/stdc++.h>

const int N = 2e5, L = 20;

int n, a[N + 5], b[N + 5];

struct RangeMaxQuery {
	int f[N + 5][L + 5];
	
	void initTable() {
		for (int i = 1; i <= n; ++i) {
			f[i][0] = a[i];
		}
		
		int lim = std::log(n) / std::log(2) + 1;
		for (int j = 1; j <= lim; ++j) {
			for (int i = 1; i <= n - (1 << j) + 1; ++i) {
				f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	
	int rangeQ(int l, int r) {
		if (l > r) {
			return 0;
		}
		int len = std::log(r - l + 1) / std::log(2);
		return std::max(f[l][len], f[r - (1 << len) + 1][len]);
	}
	
	int rangeQuery(int l, int r) {
		if (l >= 1 && r <= n) {
			return rangeQ(l, r);
		} else if (l <= 0 && r <= n) {
			return std::max(rangeQ(n + l, n), rangeQ(1, r));
		} else {
			return std::max(rangeQ(l, n), rangeQ(1, r - n));
		}
	}
} rmqEr;

int calc(int x) {
	int l = 1, r = n / 2, res = 0;
//	std::cout << "\n{" << x << "}\n";
	while (l <= r) {
//		std::cout << "[" << l << " " << r << "]\n";
		int mid = (l + r) / 2;
		if (std::max(rmqEr.rangeQuery(x - mid, x - 1), rmqEr.rangeQuery(x + 1, x + mid)) >= b[x]) {
			r = mid - 1;
			res = mid;
		} else {
			l = mid + 1;
		}
	}
//	std::cout << "\n(" << x << " " << res << ")\n";
	if (res == 0) {
		return -1;
	} else {
		return res;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> b[i];
	}
	rmqEr.initTable();
	for (int i = 1; i <= n; ++i) {
		std::cout << calc(i) << ' ';
	}
	return 0;
}
```

---

## 作者：haozinojc (赞：0)

本题主要考察**二分**和 **ST 表**。

## 思路：

拿到这道题，看到搜点和[劣弧](https://baike.baidu.com/item/%E5%8A%A3%E5%BC%A7/3163496)后，大家肯定都会想到**二分**。

将整个环变成一条链即可进行我们平时的操作，环变链的操作，我的[这篇博客](https://www.luogu.com.cn/blog/644337/guan-yu-ou-jian-dp)下面部分里有提及，不会的或感兴趣的可以去看看。

变成一条链之后，就很好操作了。对于一个点，我们看它的左右部分的**区间最大值**，判断左右部分是否有合法的点，再在对应的区域内再次二分。最后，比较得出最小距离就可以了。

维护区间最大值有很多种方法，由于这里是静态查询，所以用 ST 表会比较好（如果不会 ST 表可以试试线段树，但不一定能过）。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define re register int
using namespace std;
const int N=2e5+10,M=30;
int n;
int a[N],b[N],st[N][M],cur[N]={-0x7f,0,1};

int fen1(int l,int r,int cnt){
	while(l<r){
		int mid=(l+r)/2;
		if(find(l,mid)>=cnt)r=mid;
		else l=mid+1;
	}
	return l;
}
int fen2(int l,int r,int cnt){
	while(l<r){
		int mid=(l+r)/2;
		if(find(mid+1,r)>=cnt)l=mid+1;
		else r=mid;
	}
	return r;
}
void ST(){
	for(re i=3;i<=2*n;i++)cur[i]=cur[i/2]+1;
	for(re i=1;i<=2*n;i++)st[i][0]=a[i];
	for(re j=1;j<=cur[2*n]+1;j++){
		for(int i=1;i+(1<<j-1)<=2*n;i++){
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int find(int l,int r){
	int k=cur[r-l+1];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}

signed main(){
	cin>>n;
	for(re i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(re i=1;i<=n;i++){
		cin>>b[i];
		b[i+n]=b[i];
	}
	ST();
	for(re i=1;i<=n;i++){
		if(find(i+1,i+n-1)<b[i])cout<<-1<<" ";
		else{
			int ans1=fen1(i+1,i+(n-1)/2,b[i])-i;
			int ans2=i+n-fen2(i+(n-1)/2+1,i+n-1,b[i]);
			if(a[ans1+i]<b[i])cout<<ans2<<" ";
			else if(a[i+n-ans2]<b[i])cout<<ans1<<" ";
			else cout<<min(ans1,ans2)<<" ";
		}
	}
	return 0;
}


```


---

## 作者：kdy20100729 (赞：0)

### [传送门](https://www.luogu.com.cn/problem/P7333)

## 题意简述:  
对于每个 $b_j$ （$1 \leq j \leq n$）找到最近的大与等于它的 $a_i$,要求 $i \neq j$。输出 $\operatorname{abs}(i-j)$，如果没有则输出 $-1$。

## 解题思路：  
对于起点 $j$，我们查找 $j$ 左边区间的最大值中满足 $a_i \geq b_j$ 且左边界最近的。对于起点 $j$，我们查找 $j$ 右边区间的最大值中满足 $a_i \geq b_j$ 且右边界最近的。  
对于这两个问题，区间最值可以使用ST表进行 $\mathcal{O}(1)$ 询问，区间的边界可以用二分来查找，因为我们发现，从 $j$ 为起点，往左扩展边界的区间最大值是递增的，从 $j$ 为起点，往右扩展边界的区间最大值也是递增的。  
数组有序，符合二分查找的条件。

## Code:  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r,len,mid,a[300005],b[300005],dp[300005][25],log_2[300005];
bool check(int l,int r,int x)//判断 [l,r] 区间的最大值是否大于等于 x
{
    int s=log_2[r-l+1];
    int cnt=max(dp[l][s],dp[r-(1<<s)+1][s]);
    if (cnt>=x)
        return true;
    return false;
}
int help(int pos)//二分搜索边界
{
    len=n;
    r=pos-1;
    l=pos-n+1;
    while(l<=r)//搜索左边
    {
        mid=(l+r)/2;
        if (check(mid,r,b[pos-n])==true)
        {
            l=mid+1;
            len=min(len,pos-mid);
        }
        else
            r=mid-1;
    }
    l=pos+1;
    r=pos+n-1;
    while(l<=r)//搜索右边
    {
        mid=(l+r)/2;
        if (check(l,mid,b[pos-n])==true)
        {
            r=mid-1;
            len=min(len,mid-pos);
        }
        else
            l=mid+1;
    }
    if (len==n)
        return -1;
    return len;
}
signed main()
{
    cin >> n;
    for(int i=1; i<=n; i++)//初始化
    {
        cin >> a[i];
        dp[i][0]=dp[i+n][0]=dp[i+2*n][0]=a[i];
    }
    for(int i=1; i<=n; i++)
        cin >> b[i];
    for(int i=1; i<=20; i++)//预处理 dp 数组
        for(int j=1; j+(1<<i)-1<=3*n; j++)
            dp[j][i]=max(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
    for(int i=2; i<=3*n; i++)//预处理 log_2 数组
        log_2[i]=log_2[i/2]+1;
    for(int i=1; i<=n; i++)//利用二分查找并输出答案
        cout << help(i+n) << " ";
    return 0;
}
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Problem]}}$

$n$ 个数对 $(a_i,b_i)$ 在同一个环上，你需要求出 $f_{1 \cdots n}$，使得 $f_{i}$ 等于满足 $a_{j}\geq b_{i}$ 的离 $i$ **最近**的 $j$ 到 $i$ 的**距离**。

$\color{blue}{\texttt{[Solution]}}$

注意我们要求的是距离。

这个东西是有单调性（A.K.A. 可二分性）的，即如果 $x$ 的距离内有点 $j$ 满足 $a_{j}>b_{i}$，则 $(x+1)$ 的距离内一定也有（点 $j$ 明显就是嘛）。

这个结论有什么用？很简单，我们可以**二分答案**。

具体来说，我们先要破环为链，把链三倍，使 $a_{i+2 \times n}=a_{i+n}=a_i$。这样区间 $[i-t,i-1]$ 和 $[i+1,i+t]$ 就是所有到 $i$ 距离 $\leq t$ 的点。

如何快速判断这个区间内有没有满足条件的点呢？很简单，只要这些点中最大的 $a_{k}\geq b_{i}$ 即可。

如何快速地求出最大值呢？很简单，用一个 **ST 表**即可。

最后的时间复杂度：$T(3 \times n \times \log (3 \times n)+n \times \log (3 \times n))=O(n \times \log n)$。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e5+100;
int lg[N*3],f[20][N*3],n,a[N*3];
inline int query(int l,int r){
	register int s=lg[r-l+1];
	return max(f[s][l],f[s][r-(1<<s)+1]);
}
inline bool check(int t,int i,int x){
	return max(query(i-t,i-1),query(i+1,i+t))>=x;
}
inline int work(int x,int i){
	int l=1,r=n-1,ans=-1;
	while (l<=r){
		int mid=(l+r)>>1;
		if (check(mid,i,x)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
int main(){
	n=read();lg[0]=-1;
	for(int i=1;i<=n;i++)
		a[i+2*n]=a[i+n]=a[i]=read();
	for(int i=1;i<=3*n;i++){
		lg[i]=lg[i>>1]+1;
		f[0][i]=a[i];
	}
	for(int j=1;(1<<j)<=3*n;j++)
		for(int i=1;i+(1<<j)-1<=3*n;i++)
			f[j][i]=max(f[j-1][i],f[j-1][i+(1<<(j-1))]);
	for(int i=1;i<=n;i++){
		printf("%d ",work(read(),i+n));
	}
	return 0;
}
```

---

