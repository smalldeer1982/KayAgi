# yyf hates choukapai

## 题目背景

非酋 yyf 总是抽不到自己想要的卡，因此还十分讨厌抽卡。但玩 sif 不可能不抽卡，于是他去请教了一下欧皇 dew。dew 告诉了他关于抽卡的秘密，然而 yyf 还是不知道如何让自己欧气尽量地大，于是他找到了你。

## 题目描述

dew 告诉 yyf，人在抽每张卡时欧气值都是固定的，第 $i$ 张卡的欧气值为 $a_i$，而在连抽时，欧气值等于第一张卡的欧气值。

“每次抽卡的欧气之和”指每次单抽的欧气之和加上每次连抽的欧气之和，一次连抽的欧气不加权，只计算一次。

yyf 想 $c$ 连抽（连续抽 $c$ 张卡）$n$ 次，单抽 $m$ 次，因为一直单抽太累，**yyf 不想连续单抽超过 $d$ 次（可以连续单抽恰好 $d$ 次）**。共有 $c\times n+m$ 张卡，抽卡的顺序不能改变，每张卡都必须且只能抽一次，只能改变哪几张卡连抽、哪几张卡单抽。那么 yyf 每次抽卡的欧气之和最多能达到多少，又如何实现呢？

## 说明/提示

$20\%$ 的数据有 $1 \le n \le 5$，$1 \le m \le 5$，$2 \le c \le 5$。

$50\%$ 的数据有 $1 \le n \le 40$，$1 \le m \le 200$，$2 \le c \le 20$。

另有 $20\%$ 的数据有 $d=m$。

$100\%$ 的数据有 $1 \le n \le 40$，$1 \le m \le 80000$，$2 \le c \le 3000$，$1 \le a_i \le 10000$，$1 \le d \le m$，$d\times (n+1) \ge m$。

共 $10$ 个测试点，每个测试点答案错误 $0$ 分，答案正确方案错误 $6$ 分，答案正确方案正确 $10$ 分。

样例解释：输出的方案就是样例解释了 QAQ。

样例一：单抽 $1$，连抽 $2\sim 4$，连抽 $5\sim 7$，单抽 $8$，连抽 $9\sim 11$，单抽 $12$，欧气值总和为 $2+7+5+8+5+9=36$。

样例二：单抽 $1$，连抽 $2\sim 3$，单抽 $4$，单抽 $5$，连抽 $6\sim 7$，单抽 $8$，单抽 $9$，欧气值总和为 $7+3+7+7+5+10+2=41$。

可以证明在满足条件的情况下上述两种方案是欧气值总和最大的。

## 样例 #1

### 输入

```
3 3 3 3
2 7 1 4 5 3 6 8 5 1 2 9```

### 输出

```
36
2 5 9```

## 样例 #2

### 输入

```
2 5 2 2
7 3 3 7 7 5 1 10 2```

### 输出

```
41
2 6 ```

# 题解

## 作者：天梦 (赞：7)

# P4852 yyf hates choukapai

[链接](https://www.luogu.com.cn/problem/P4852)

这道题调了很久，也带给我一些反思，反思写到最后。

## 1 状态设计

我的状态设计与大部分题解的并不相同，我的状态数会更少一些，设 $f_{i,j}$ 表示一共抽了 $j$ 次，其中，有 $i$ 次是连抽，并且第 $j$ 次抽是连抽。

## 2 转移

首先，我们在序列的后面加上 $c$ 个 $0$ ，这样我们就可以强制最后一次是连抽而不影响正确性。

我们枚举前一次连抽是第几次：
$$
f_{i,j}=\max\limits_{\max(j-d-1,0)\le k\le j-1} \{ f_{i-1,k}+sum_{now-c+1}-sum_{last} \}
$$
其中 $sum$ 是前缀和，$now$ 是状态 $f_{i,j}$ 对应的位置，也就是 $i\times c+(j-i)$ ，$last$ 是 $f_{i-1,k}$ 对应的位置，计算方法和左边相同。那么这个就是一个裸的单调队列。

记录方案的话就开一个数组对应记一下就可以了。

## 3 注意事项

+ 在 dp 中，所有的变量的范围一定要卡死。
+ 所有不合法的状态一定不要随意赋值。
+ 不要随意的初始化。
+ 所做的一切操作一定要符合你的状态。

> 不遵守上述事项的结果就是我调了一天。



## 4 代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
// #define int long long
#define uint unsigned int
#define ull unsigned long long
#define N 310000
#define M 70
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,c,d,a[N],f[M][100000],sum[N],g[M][100000];
int q[N],l,r;

inline int get_posi(int id,int jd){
    return id*c+(jd-id);
}

inline void prework(){
    n++;
    for(int i=1;i<=n*c+m;i++) sum[i]=a[i]+sum[i-1];
}

inline int compeat(int id,int k){
    return f[id-1][k]-sum[get_posi(id-1,k)];
}

inline void print(int id,int jd){
    if(g[id][jd]<=0) return;
    print(id-1,g[id][jd]);
    int posi=get_posi(id-1,g[id][jd])-c+1;
    if(posi>0) printf("%d ",posi);
}

int main(){
    read(n);read(m);read(c);read(d);
    for(int i=1;i<=n*c+m;i++) read(a[i]);
    prework();
    for(int i=1;i<=n;i++){
        l=r=0;
        for(int j=0;j<=n+m&&j<=(d+1)*i;j++){
            while(l<r&&(q[l+1]<j-d-1||q[l+1]<i-1)) l++;
            if(j>=i&&l<r){
                int k=q[l+1];
                int now=get_posi(i,j),last=get_posi(i-1,k);
                f[i][j]=f[i-1][k]-sum[last]+sum[now-c+1];
                g[i][j]=k;
            }
            while(l<r&&compeat(i,q[r])<compeat(i,j)) r--;
            q[++r]=j;
        }
    }
    printf("%d\n",f[n][n+m]);
    print(n,n+m);
    return 0;
}
```



---

## 作者：ouuan (赞：4)

为了方便下文中设 $s=n*c+m$

### 算法一（纯暴力）

暴力枚举所有方案。

时间复杂度：$O(C^{\,n}_{\;s})$，然而实际上有一堆剪枝，剪完之后复杂度会不会下一个数量级呢？出题人懒得算，反正数据这么小，暴力20分肯定稳的。

期望得分：$20$ 分

### 算法二（d=m）

因为 $d=m$ ，可以不管 $d$ 的限制

设 $f(i,j)$ 表示前 $i$ 张卡中连抽 $j$ 次的最大欧气，则可以得到方程：

$f(i,j)=\max(f(i-1,j)+a[i],f(i-c,j-1)+a[i-c+1])$

两种转移分别代表第 $i$ 张卡是单抽/一次连抽的结尾。

输出方案：记录一下每个 $f(i,j)$ 是由谁转移来的，算完dp之后从 $n$ 倒回去，如果倒回去的过程中某两张卡的间隔是 $c$ 代表这两张卡之间有一次连抽

时间复杂度：$O(sn)$

期望得分：$20$ 分

### 算法三（无优化dp）

选一组牌 $[l,r]$ 连抽其实就是使欧气总和减少了 $\sum\limits_{i=l+1}^ra_i$ ，所以预处理出 $b_i=\sum\limits_{j=i+1}^{i+c-1}a_j\ (i∈[1,s-c+1])$ ，题目就变成了选择 $n$ 个 $b_i$ ，它们两两的下标之差大于等于 $c$ 且小于等于 $c+d$，求它们的和的最小值。特别地，选择的第一个 $b_i$ 下标要小于等于 $d+1$，最后一个 $b_i$ 下标要大于等于 $s-c-d+1$（不这样转化也能做，但出题人感觉转化之后方便一些）

设 $f(i,j)$ 为在 $b_{[1,i]}$ 中选择 $j$ 个且选择 $b_i$ 的最小和，可以得到：

$f(i,j)=\min\limits_{k∈[i-c-d,i-c]}(f(k,j-1))+b[i]$

时间复杂度：$O(snd)$

期望得分：$50$ 分

### 算法四（数据分治）

~~使用数据分治结合算法二和算法一/三，可以获得更高的分数。~~

时间复杂度：$O(d==m?sn:C^{\,n}_{\;s}||snd)$

期望得分：$40/70$ 分

### 算法五（不会输出方案）

~~看出题人多么仁慈还给你准备了部分分~~

时间复杂度：$O(?)$

期望得分：$12$~$60$ 分

### 算法六（单调队列优化dp）

看这玩意 → $k∈[i-c-d,i-c]$

嗯用单调队列优化一下就好了

不会单调队列？[~~如果一个人比你小，还比你强，那你就永远打不过他了~~](https://sweetlemon.blog.luogu.org/dan-diao-dui-lie)

输出方案：记录一下每个 $f(i,j)$ 由谁转移而来，就说明选了这个 $b_i$ ，而选了某个 $b_i$ 就说明 $i$ 是某一次连抽的起始

时间复杂度：$O(sn)$

期望得分：$100$ 分

### Bonus

~~在~~[~~我用v4评测机的第一次提交的编译信息~~](https://www.luogu.org/record/show?rid=9924927)~~里可以看到出题人的良心提示：~~

```
if (sta[i]<1||sta[i]>s-c+1||i>1&&(sta[i]-sta[i-1]<c||sta[i]-sta[i-1]>c+d))
```

从这一行可以看出两次连抽的起始下标之差要在 $[c,c+d]$ 内。

实际上是v4评测机神仙到能显示spj的warning...然而并不知道为什么之后的提交就没有这个waring了.

### 标程

```
#include <iostream>

using namespace std;

const int N=45,M=80005,C=3005;
const int S=N*C+M;

int n,m,c,d,s,a[S],b[S],f[S][N],p[S][N],q[N][S][2],head[N],tail[N],sum,ans[N],anss,ansi; //其实可以只开一个单调队列，然而出题人懒

int main()
{
	int i,j;
	
	cin>>n>>m>>c>>d;
	
	s=n*c+m;
	
	for (i=1;i<=s;++i)
	{
		cin>>a[i];
		sum+=a[i];
	}
	
	for (i=2;i<=c;++i)
	{
		b[1]+=a[i]; //先算出b1
	}
	
	for (i=2;i<=s-c+1;++i)
	{
		b[i]=b[i-1]-a[i]+a[i+c-1]; //然后O(1)算出剩下的b
	}
	
	for (i=1;i<=n;++i)
	{
		head[i]=1; //将所有单调队列初始化为空队
	}
	
	for (i=1;i<=s-c+1;++i)
	{
		if (i<=c)
		{
			f[i][1]=b[i]; //i<=c时之前必然没有连抽，只有f(i,1)有定义，而此时队列还是空的，所以直接赋为bi就好了
		}
		else
		{
			for (j=(i+c-2)/(c+d)+1;j<=(i+c-1)/c&&j<=n;++j) //应该是f(i,j)有定义的准确范围，自己手推一下就可以推出来了，然而两个验题的都没有把范围卡死就过了
			{
				if (head[j-1]<=tail[j-1]&&q[j-1][head[j-1]][1]<i-c-d)
				{
					++head[j-1]; //将下标小于i-c-d的b出队
				}
				
				if (j-1>=(i-2)/(c+d)+1&&j-1<=(i-1)/c) //如果f(i-c,j-1)有定义就将其入队
				{
					while (head[j-1]<=tail[j-1]&&q[j-1][tail[j-1]][0]>=f[i-c][j-1])
					{
						--tail[j-1];
					}
					q[j-1][++tail[j-1]][0]=f[i-c][j-1];
					q[j-1][tail[j-1]][1]=i-c;
				}
				
				f[i][j]=q[j-1][head[j-1]][0]+b[i];
				p[i][j]=q[j-1][head[j-1]][1]; //记录f(i,j)由谁转移而来
				
				if (i>=s-c+1-d&&j==n&&anss<sum-f[i][j]) //只有下标大于等于s-c+1-d的时候才能用f(i,n)更新答案
				{
					anss=sum-f[i][j];
					ansi=i;
				}
			}
		}
	}
	
	cout<<anss<<endl;
	
	for (j=n;j>=1;--j)
	{
		ans[j]=ansi;
		ansi=p[ansi][j];
	}
	
	for (j=1;j<=n;++j)
	{
		cout<<ans[j]<<' ';
	}
	
	return 0;
}
```

---

## 作者：风羽跃 (赞：3)

来波比较短的单调队列~

首先当前连抽多少次、单抽多少次、抽了多少牌这三个状态，我们**只需要记录其二，就可以算出剩下那个**。

由于连抽的次数上限只有40，因此我们先记一维连抽。

其次单抽和总牌数，显然记录总牌数更方便转移（~~好像也没方便多少~~），因此第二维我们记总牌数。

综上所述，我们用 **$f[i][j]$ 表示前 $i$ 张牌连抽 $j$ 次的最大欧气值。**

考虑**枚举本次连抽的位置** $k$(为了计算方便，我们设 $k$ 为本次连抽的起始卡牌的前一个位置），转移方程显然：

$f[i][j]=\max(f[k][j-1]+a[k+1]+s[i]-s[k+c])$，

其中 $\max(0,i-c-d) \le k \le i-c$。

题目还要求输出方案，开个数组记录前驱就好啦。

时间复杂度 $O(n^3)$。

先贴个暴力代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>

#define maxn 200005
#define maxm 42

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n,p,q,c,d,a[maxn],s[maxn],f[maxn][maxm],pre[maxn][maxm];

inline void print(int i,int j)
{
	if(!j) return ;
	print(pre[i][j],j-1);
	cout<<pre[i][j]+1<<" ";
}

int main()
{
	cin>>p>>q>>c>>d;
	n=p*c+q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	memset(f,0xcf,sizeof(f));
	for(int i=1;i<=d;i++){
		f[i][0]=s[i];
	}
	for(int j=1;j<=p;j++){
    //注意外层循环先枚举j（其实枚举i或j都能写，但为了后续优化这里我们先枚举j）
		for(int i=j*c;i<=n;i++){
			for(int k=max(0,i-c-d);k<=i-c;k++){
				if(f[k][j-1]+a[k+1]+s[i]-s[k+c]>f[i][j]){
					f[i][j]=f[k][j-1]+a[k+1]+s[i]-s[k+c];
					pre[i][j]=k;
				}
			}
		}
	}
	cout<<f[n][p]<<endl;
	print(n,p);
	puts("");
	return 0;
}
```
考虑优化，观察 $k$ 的取值范围，当 $i$ 增大时显然 $k$ 决策区间的左右边界都单调递增，所以用单调队列维护砍掉一维。

复杂度 $O(n^2)$。

AC 代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>

#define maxn 200005
#define maxm 42

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n,p,Q,c,d,a[maxn],s[maxn],f[maxn][maxm],pre[maxn][maxm];

int q[maxn],l=1,r=0;

inline void print(int i,int j)
{
	
	if(!j) return ;
	print(pre[i][j],j-1);
	cout<<pre[i][j]+1<<" ";
}

inline int calc(int j,int k)
{
	return f[k][j-1]+a[k+1]-s[k+c];
}

int main()
{
	cin>>p>>Q>>c>>d;
	n=p*c+Q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	memset(f,0xcf,sizeof(f));
	for(int i=1;i<=d;i++){
		f[i][0]=s[i];
	}
	for(int j=1;j<=p;j++){
		l=1,r=0;
		for(int k=max(0,j*c-c-d);k<=j*c-c;k++){
			while(l<=r&&calc(j,q[r])<=calc(j,k)) r--;
			q[++r]=k;
		}
		for(int i=j*c;i<=n;i++){
			while(l<=r&&q[l]<max(0,i-c-d)) l++;//弹掉左边失效的
			if(l<=r) f[i][j]=calc(j,q[l])+s[i],pre[i][j]=q[l];//更新答案
			int k=i+1-c;//下一个i的决策集合新元素
			while(l<=r&&calc(j,q[r])<=calc(j,k)) r--;
			q[++r]=k;
		}
	}
	cout<<f[n][p]<<endl;
	print(n,p);
	puts("");
	return 0;
}

```
最后补充一句：队列建议手写，常数小取用元素也方便。

---

## 作者：zhendelan (赞：3)

[P4852 yyf hates choukapai](https://www.luogu.com.cn/problem/P4852)  

前置知识：$wqs$二分+单调队列优化$dp$。
  
## 分析
    
很容易看出，单抽是一个比连抽更优的操作。所以如果没有$m$的限制，那肯定是会一直用单抽的。     

设答案为$f(x)$，$x$为单抽的次数。那么$f(x)$的图像肯定是一个上凸包(单抽的价值会不断下降,不要误以为单调上升的就一定是凸函数)。

这个时候函数的极值点$(x,f(x))$不一定会在题目$m$的范围限制内。我们要让他左移取极值点。  

设$f'(x)=f(x)-px$，当$p$增大的时候，那么肯定极值点会往左移，所以当他刚好取在$m$点时，我们就找到了$f(m)$。然后我们二分这个$p$就可以了。  

其实上面讲的比较复杂，讲人话就是给每次单抽一个额外费用，带着这个费用$dp$就会限制单抽的次数，然后使得单抽次数在限制范围内。当刚好只取到$m$次的时候，就是最优的。

那带着费用的时候怎么$dp$呢。  

像其他题解一样写成单调队列优化就可以了。  

设$f[i]$为前$i$个最多抽多少欧气值。  

$f[i]=\max_{i-j<=d}\{g[j]+(s[i]-s[j])+(i-j)*x,f[i-c]+a[i-c+1]\}$

其中$s$为前缀和,$a$为每张卡的欧气值，$g$是为了限制次数产生的，为第$i$次连抽完后的最大值。  

要注意边$dp$边记录单抽的次数。

## 时间复杂度  

$dp$复杂度$O(n)$。二分复杂度$O(\log V)$。$V$是二分的值域，这里可以开到$10000$。  

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,d;
const int N = 2e5+20;
int a[N],s[N];
double f[N],fq[N];
int cnt[N],from[N],q[N],tot,cntq[N],from1[N];
const double eps = 1e-2;
const double inf = 1e14;
int ans[N];
void solve(double extra)
{
	f[0] = fq[1] = cntq[1] = q[1] = 0;
	for(int i=1,h=1,t=1;i<=tot;i++)
	{
		f[i] = -inf;
		if(i-c>=0&&f[i-c]+a[i-c+1]>f[i]) 
		{
			f[i]=f[i-c]+a[i-c+1],from[i] = i-c,cnt[i]=cnt[i-c];
			while(h<=t && f[i]-s[i]+extra*i>fq[t])t--;
			q[++t] = i;fq[t] = f[i]-s[i]+extra*i;cntq[t] = cnt[i];
			from1[i] = from[i];
		}
		while(h<=t&&i-q[h]>d)h++;
		if(h<=t&&fq[h]+s[i]-extra*i>f[i])
			f[i]=fq[h]+s[i]-extra*i,from[i] = -q[h]-1,cnt[i] = cntq[h]+i-q[h];
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&c,&d);
	tot = c*n+m;
	for(int i=1;i<=tot;i++)
		scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	double l = 0,r=1e4;
	while(l+eps<r)
	{
		double mid = (l+r)/2;
		solve(mid);
		if(cnt[tot]>m) l=mid;
		else r = mid;
	}
	solve(r);
	int sum = 0,cntt=0,flag=0;
	for(int i=tot;i;)
	{
		if(flag) from[i] = from1[i];
		if(from[i]>=0) sum+=a[from[i]+1],ans[++cntt]=from[i]+1,i = from[i],flag=0;
		else 
		{
			from[i]++;
			for(int j=-from[i]+1;j<=i;j++)sum+=a[j];
			i=-from[i];
			flag = 1;
		}
	}
	printf("%d\n",sum);	
	for(int i=cntt;i;i--)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：RedreamMer (赞：3)

[$\Large\texttt{P4852}$](https://www.luogu.com.cn/problem/P4852)

[$\small\texttt{In My cnblogs}$](https://www.cnblogs.com/RedreamMer/p/13930211.html)

联赛前的一篇 $\texttt{DP}$ 题解，祝各位不要挂分。

标签：单调队列优化 $\texttt{DP}$ 。

这也是我第一次写单调队列题解，写的不好请见谅QwQ。

并输出选择方案。

## 题意

一段序列，你要在序列里选择 $n$ 段长 $c$ 的子序列，价值为序列第一个数，还要选 $m$ 个数，价值为它本身，求最大的价值和，但是**不能选**连续 $d$ 个数，求最大价值和。

$1 \le n \le 40$，$1 \le d \le m \le 80000$，$2 \le c \le 3000$ 

保证有解。

## 思路

看上去不这么显然观察到 $n$ 只有 $40$ ，可能是一个与 $n$ 密切有关的 $\texttt{DP}$。

先建立 $\texttt{dp[i]}$ ，表示前 $i$ 个数的最大价值，如果普通暴力转移，时间会爆炸并且这个方程有后效性的（即前i个数末尾有几个单选的数可能会影响到后面的选择）。

考虑二维 $\texttt{DP}$ ，建立$\texttt{dp[i][j]}$ 表示前 $i$ 个数有 $j$ 个长为 $c$ 的子序列，很容易得到转移方程，每一步都 $j-1$ 转移上来。

可以列出状态转移方程：

$$\texttt{dp[i][j]=dp[k-c][j-1]+sum[i]-sum[k]+a[k-c+1]}$$

其中，方案为在 $k-c+1$ 到 $k$ 选一段长为 $c$ 序列，在 $k+1$ 到 $i$ 选 $i-k$ 个单个的数。

$k$ 的范围十分显然，$i-d \le k \le i$

但是一算复杂度直接炸了，考虑优化。

---

观察式子，发现没有带 $k$ 的项与带 $i$的项相关联，可以把sum[i]单独提出来，剩下的全和 $k$ 有关。

单调队列可做。

每次将式子入单调队列，并排除 $k$ 过小的情况可以做到 $\texttt{O(1)}$ 转移。

方案的计算就再开一维记录每一个状态从何而来。

总复杂度 $\large\texttt{O(n(nc+m))}$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e6;
const int M = 40;
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a,b,c,d,mx,dp[N+10][M+10][2],s[N+10],sum[N+10],qu[N+10][2],l,r;

inline int calc(int n,int m) {
    return dp[n-c][m][0]-sum[n]+s[n-c+1];
}

inline void print(int n,int m) {
    if(m==-1) return;
    print(dp[n][m][1],m-1);
    printf("%lld ",n+1);
}

signed main()
{
    // freopen("in1.in", "r", stdin);
    a=read();
    b=read();
    c=read();
    d=read();
    mx=a*c+b;
    for(int i=1;i<=mx;i++) s[i]=read(),sum[i]=s[i]+sum[i-1];
    for(int i=1;i<=d;i++) dp[i][0][0]=sum[i];
    for(int i=1;i<=a;i++) {
        l=1,r=0;
        for(int j=i*c;j<=mx;j++) {
            while(l<=r&&qu[r][0]<calc(j,i-1)) r--;
            qu[++r][0]=calc(j,i-1);
            qu[r][1]=j;
            while(l<=r&&qu[l][1]<j-d) l++;
            dp[j][i][0]=qu[l][0]+sum[j];
            dp[j][i][1]=qu[l][1]-c;
        }
    }
    printf("%lld\n",dp[mx][a][0]);
    print(dp[mx][a][1],a-1);
    return 0;
}
```

---

## 作者：Mariposa (赞：2)

考虑$dp$，设状态量$dp[i][j]$表示抽到$i$用了$j$次连抽的最大值。

预处理前缀和：$sum[i]=\sum\limits_{j=1}^i a[j]$

状转方程：$dp[i][j]=\max\{\quad dp[i-k-c][j-1]+a[i-k-c+1]+sum[i]-sum[i-k]\quad |\quad k\in[0,d]\quad\}$

意思是可以选长度为$k$的一段单抽，然后来一次连抽。

注意到没有$i$和$i-k$的关联项，故直接单调队列维护即可。

时间复杂度$\Theta(n*(cn+m))$

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,c,d,tot;
const int maxn=2e5+10;
int a[maxn],sum[maxn],dp[maxn][50];
int p[maxn][50],q[maxn],l,r;
inline void out(int i,int j){
	if(j==0)return;
	out(p[i][j]-1,j-1);
	printf("%d ",p[i][j]);
}
int main(){
	//freopen("P4852.in","r",stdin);
	//freopen("P4852.out","w",stdout);
	n=read(),m=read(),c=read(),d=read();
	tot=c*n+m;
	for(int i=1;i<=tot;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=d;i++)
		dp[i][0]=sum[i];
	for(int j=1;j<=n;j++){
		memset(q,0,sizeof(q));
		l=1,r=0;
		for(int i=j*c;i<=tot;i++){
			dp[i][j]=dp[i-c][j-1]+a[i-c+1];
			p[i][j]=i-c+1;
			while(l<=r&&i-q[l]>d)l++;
			if(l<=r&&dp[i][j]<dp[q[l]-c][j-1]+a[q[l]-c+1]+sum[i]-sum[q[l]]){
				dp[i][j]=dp[q[l]-c][j-1]+a[q[l]-c+1]+sum[i]-sum[q[l]];
				p[i][j]=q[l]-c+1;
			}
			while(l<=r&&dp[i-c][j-1]-sum[i]+a[i-c+1]>=dp[q[r]-c][j-1]+a[q[r]-c+1]-sum[q[r]])r--;
			q[++r]=i;
		}
	}
	printf("%d\n",dp[tot][n]);
	out(tot,n);
	return 0;
}
```
深深地感到自己的弱小。

---

