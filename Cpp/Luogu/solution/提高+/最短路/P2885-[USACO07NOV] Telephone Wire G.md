# [USACO07NOV] Telephone Wire G

## 题目描述

Farmer John's cows are getting restless about their poor telephone service; they want FJ to replace the old telephone wire with new, more efficient wire. The new wiring will utilize N (2 ≤ N ≤ 100,000) already-installed telephone poles, each with some heighti meters (1 ≤ heighti ≤ 100). The new wire will connect the tops of each pair of adjacent poles and will incur a penalty cost C × the two poles' height difference for each section of wire where the poles are of different heights (1 ≤ C ≤ 100). The poles, of course, are in a certain sequence and can not be moved.

Farmer John figures that if he makes some poles taller he can reduce his penalties, though with some other additional cost. He can add an integer X number of meters to a pole at a cost of X2.

Help Farmer John determine the cheapest combination of growing pole heights and connecting wire so that the cows can get their new and improved service.

给出若干棵树的高度，你可以进行一种操作：把某棵树增高h，花费为h\*h。


操作完成后连线，两棵树间花费为高度差\*定值c。


求两种花费加和最小值。


## 样例 #1

### 输入

```
5 2
2
3
5
1
4```

### 输出

```
15```

# 题解

## 作者：asuldb (赞：38)

先说说暴力做法吧，我们用f[i][j]表示前i棵树，其中第i棵树高度为j时的最小花费，于是我们有一个很好推的的dp式子了

$$f[i][j]=(j-h[i])^2+min(f[i-1][k]+c*abs(j-k))$$

于是对于每一棵树的每一种高度我们要枚举前面的那一棵树的所有高度来算一个最小值，于是复杂度大概是$O(n*max(h)^2)$，在$N ≤ 100,000$，树的高度小于$100$的数据下靠着比较优秀的常数以及O2卡了过去

暴力代码：
```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#define re register
#define mp make_pair
#define xx first
#define y second
#define maxn 100001
#define int long long
#define inf 9999999999
using namespace std;
int f[maxn][101],h[maxn];
int n,c,maxx,mid;
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
signed main()
{
    n=read();
    c=read();
    for(re int i=1;i<=n;i++) h[i]=read(),maxx=max(h[i],maxx);
    for(re int i=1;i<=n;i++)
    for(re int j=0;j<=100;j++) f[i][j]=inf;
    for(re int i=h[1];i<=maxx;i++)
        f[1][i]=(i-h[1])*(i-h[1]);
    for(re int i=2;i<=n;i++)
    {
        for(re int j=h[i];j<=maxx;j++)
        {
            for(re int k=h[i-1];k<=maxx;k++)
            {
                f[i][j]=min(f[i][j],f[i-1][k]+c*abs(j-k)+(j-h[i])*(j-h[i]));
            }
        }
    }
    int ans=inf;
    for(re int i=h[n];i<=maxx;i++)
    ans=min(ans,f[n][i]);
    cout<<ans<<endl;
    return 0;
}
```
那么这个复杂度其实是明显不对的，我们用暴力刚过去也主要靠洛谷评测机的性能比较优秀

于是我们再去看dp的方程

有两种情况：

$$f[i][j]=(j-h[i])^2+min(f[i-1][k]-c*k+c*j)\ \ (k<j)$$

$$f[i][j]=(j-h[i])^2+min(f[i-1][k]+c*k-c*j)\ \  (k>j)$$

后面那些东西显然可以用单调队列优化一下

那么我们可以分类讨论一下，就可以解决这个恶心的绝对值了

至于我们如何分类讨论呢，我们只要巧妙的改变循环的顺序就可以做到这一点了

也就是说我们正着循环再倒着来一遍就好了

至于具体怎么搞，代码里说的应该很清楚了

于是就是代码了，大概可以跑到最优解第二吧

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<fstream>
#define re register
#define inf 999999999
using namespace std;
int f[2][101],n,c;
int h[100001];
int now,m;
int ans=inf;
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	   x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
int main()
{
	n=read();
	c=read();
	now=1;
	for(re int i=1;i<=n;i++) h[i]=read(),m=max(m,h[i]);
		for(re int i=0;i<=m;i++) f[0][i]=f[1][i]=inf;
	for(re int i=h[1];i<=m;i++) f[now][i]=(i-h[1])*(i-h[1]);
	//这里其实并没有使用真正单调队列的必要，我们只需要存好最小值就好了 
	for(re int i=2;i<=n;i++)
	{
		now^=1;
		int k=inf;
		for(re int j=h[i-1];j<=m;j++)
		{
			k=min(k,f[now^1][j]-j*c);
			if(j>=h[i]) f[now][j]=k+(j-h[i])*(j-h[i])+c*j;
		}
		//这里对应的方程其实就是f[i][j]=(j-h[i])^2+min(f[i-1][k]-c*k+c*j) (k<j)
		//因为这里正序枚举j可以保证j一定大于等于k的高度 
		k=inf;
		for(re int j=m;j>=h[i];--j)//至于这里为什么是枚举到h[i],而不是h[i-1]
		//我们可以想啊，如果h[i-1]大于h[i],这里的循环也枚举到h[i-1]
		//那么f[now]从h[i-1]到h[i]的值并没有被更新，这显然是是不行的 
		//至于h[i-1]小于h[i]并没有什么关系，因为我们并不能使h[i]的高度减小 
		{
			k=min(k,f[now^1][j]+j*c);
			f[now][j]=min(f[now][j],k-c*j+(j-h[i])*(j-h[i]));
		}
		//这里对应的方程其实就是f[i][j]=(j-h[i])^2+min(f[i-1][k]+c*k-c*j) (k>j)
		// 因为这里的倒叙枚举可以保证j一定小于等于k的高度 
		for(re int i=0;i<=m;i++) f[now^1][i]=inf;
		//记得把上一层数组初始化，我们下次又要用这一层了 
	}
	for(re int i=h[n];i<=m;i++)
	ans=min(ans,f[now][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Erina (赞：23)

## 这里的题解都好玄学啊, 提供两种新的方法

不是非常明白为什么一定要扫两遍...... 况且别的题解都差不多是这种方法...... 这里是两种新的方法......

### 1

原来的dp方程: $dp[i,j]=min\{dp[i,k]+(j-arr[i])^2+C*abs(j-k)\}$

暴力转移......是不是$nh^2$的

发现随着考虑节点高度的增加, 它左边相邻电线杆的最优高度**必定**不降(想一想, 为什么)

也就是说当`j`增加时`k`必定不降, 维护一个指针然后乱搞一波......

是非常快的$O(nh)$算法了...... 为什么要循环两次, 正着一次反着一次??? 为什么要单调队列?

代码如下:

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[100000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,100000),s==t)?EOF:*s++)
	inline int read() { //快读板子......
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
int n, arr[100005], c;
int dp[100005][105], maxh;
int main() {
	n = read(), c = read();
	for (int i = 1; i <= n; i++)
		maxh = max(arr[i] = read(), maxh);
	for (int i = arr[1]; i <= maxh; i++)
		dp[1][i] = (i - arr[1]) * (i - arr[1]);// 这个......没什么好说的......
	for (int i = 2; i <= n; i++) {
		int ptr = arr[i - 1];
		for (int u = arr[i]; u <= maxh; u++) {
			while (dp[i - 1][ptr] + abs(u - ptr) * c >dp[i - 1][ptr + 1] + abs(u - ptr - 1) * c && ptr < maxh)
				ptr++;//我们知道这个是有单调性的, 所以不需要遍历, 也不需要单调队列
			dp[i][u] = dp[i - 1][ptr] + abs(u - ptr) * c + (u - arr[i]) * (u - arr[i]);
			// 转移答案
		}
	}
	int ans = 0x7fffffff;
	for (int i = arr[n]; i <= maxh; i++)
		ans = min(ans, dp[n][i]);// 统计最小值......
	cout << ans;
}
```

### 2

想一想要是高度是1e9怎么办......

想不到吧这题其实有$O(n)$的做法

但是常数比较大~~废话~~

就是考虑枚举不拔高的电线杆......

然后发现整个序列被切成了很多个区间......

然后发现中间的所有东西最小的时候**必定**全部一样高, 况且两端点处**一定**最高

为什么呢? 第一个结论是因为你要把中间一个区间全部拔高, 但是如果你不全部拔一样高, 那么你把最高的一个按下去一格一定最优(因为一定拔高, 所以一定能够按下去)

第二个结论正确性显然.

而一个区间对应的是一个二次函数, 可以O(1)求出极值.

然后...... 用一个单调栈维护一个递减的序列.

每一次把一根电线杆入队时, 先弹出所有比它小的, 并且假设它不被拔高, 中间的全部都被拔高, 然后再找**第一个**比它大的电线杆, 再算一次. 然后入栈.

然后发现整个算法其实是$O(n)$的, 但是常数比较大. ~~因为本人比较菜代码之后再补~~

然后和现在的最高评分题解加起来就是四种不同的算法啦!


---

## 作者：niiick (赞：6)

$dp[i][j]$表示考虑前$i$个电线杆，且第$i$根高度为$j$时的最小花费

首先容易想到一个$O(nh^2)$的方程
$dp[i][j]=min(\ dp[i-1][k]+abs(j-k)*c\ )+(j-h_i)^2$

但是这样复杂度肯定爆炸，
我们考虑把上述方程的**绝对值分开考虑**

$dp[i][j]=min(\ dp[i-1][k]+j*c-k*c) )+(j-h_i)^2$ ，$(k<=j)$

$dp[i][j]=min(\ dp[i-1][k]+k*c-j*c) )+(j-h_i)^2$ ，$(j<=k)$

$(j-h_i)^2$是定值，$min()$里面得值可以**直接用一个变量mi维护**

即在求$dp[i][j]$得时候**对**$j$**分别正序倒叙更新一次**

**正序更新开始前先令**$mi=min(dp[i-1][k]-k*c)(1<=k<=h_i)$

**正序**从$j=h_i$开始到$j=100$都要更新，每次更新$dp[i][j]$前**先更新**$mi=min(mi,dp[i-1][j]-j*c)$

**倒叙**从$j=100$开始到$j=h_i$都要更新，每次更新$dp[i][j]$前**先更新**$mi=min(mi,dp[i-1][j]+j*c)$

这样复杂度就降到了$O(n*h)$
*******************

```cpp
//niiick
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
#define sqr(x) ((x)*(x))

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=100010;
int n,c,ans=1e9;
int hi[maxn];
int dp[maxn][110];

int main()
{
    n=read();c=read();
    for(int i=1;i<=n;++i) hi[i]=read();
    
    memset(dp,67,sizeof(dp));
    for(int i=hi[1];i<=100;++i) 
    dp[1][i]=sqr(i-hi[1]);
    
    for(int i=2;i<=n;++i)
    {
        int mi=1e9;
        for(int k=1;k<hi[i];++k) mi=min(mi,dp[i-1][k]-c*k);
        for(int j=hi[i];j<=100;++j)
    	{
    		mi=min(mi,dp[i-1][j]-c*j);
            dp[i][j]=min(dp[i][j],mi+c*j+sqr(j-hi[i]));
        }
    	mi=1e9;
    	for(int j=100;j>=hi[i];--j)
    	{
    		mi=min(mi,dp[i-1][j]+c*j);
            dp[i][j]=min(dp[i][j],mi-c*j+sqr(j-hi[i]));
        }
    }
    
    for(int i=hi[n];i<=100;++i)
    ans=min(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}

```


---

## 作者：「QQ红包」 (赞：6)

最简单的转移楼下讲得很清楚了

$f[i][j]$ 表示前i棵电线杆,当第i根电线杆高度为j的时候费用,然后转移很方便,然后正常的TLE

不难发现,每次转移是个开口向上的二次函数(可以自己算算),然后我们枚举上一棵树的高度的过程中,

如果随着高度的增加费用增加了,就可以不用继续转移了

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char s;
    int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(s>='0'&&s<='9'));
    if(s==EOF)exit(0);
    if(s=='-')base=-1,s=getchar();
    while(s>='0'&&s<='9')
    {
        k=k*10+(s-'0');
        s=getchar();
    }
    return k*base;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        write(-x);
    }
    else
    {
        if(x/10)write(x/10);
        putchar(x%10+'0');
    }
}
int n,c,p,x,s,mh;
int h[100100];
int f[100100][100];
int main()
{
    n=read();c=read();
    for (register int i=1;i<=n;i++) 
    {
        h[i]=read();
        if (h[i]>mh) mh=h[i];
    }
    memset(f,1,sizeof(f));
    for (register int i=h[1];i<=100;i++) f[1][i]=(i-h[1])*(i-h[1]);
    for (register int i=2;i<=n;i++)
    {
        for (register int j=h[i];j<=mh;j++)//hm:电线杆的最大高度
        {
            s=(j-h[i])*(j-h[i]);//先算出来快些?
            p=233333333;
            for (register int k=h[i-1];k<=mh;k++)
            {
                x=f[i-1][k]+s+c*abs(k-j);
                //下面和这一句是等效的,似乎快点?f[i][j]=min(f[i][j],x);
                if (x<f[i][j])
                {
                    f[i][j]=x;
                }
                if (x>p) break;//比上一个更多就不用转移了
                p=x;
            }
        }
    }
    int ans=f[n][h[n]];
    for (register int i=h[n]+1;i<=100;i++) ans=min(ans,f[n][i]);//找答案
    printf("%d",ans);
    return 0;
}

```

---

## 作者：pigstd (赞：5)

设$dp_{i,j}$表示第$i$个房子被拔高到$j$的高度后最小的花费，下文中记最大的高度为$h$。

那么显然：$dp_{i,j}=\min(dp_{i-1,k}+c \times | j-k |)+(j-c_i)^2$。

但是直接转移是$O(n \times h^2)$的，我们需要优化。

那么$dp$方程可以看为：

- 当$k \le j$时，$dp_{i,j}= \min( dp_{i-1,k} + c \times ( j - k ))+( j - h_i )^2  = \min( dp_{i-1,k} - c \times k ) + c\times j + (j-h _i )^2$

- 当$j \le k$时，$ dp_{i,j} = \min( dp_{ i - 1 , k } + c \times ( k - j )) + ( j - h_i )^2  = \min(dp_{ i - 1 , k } + c \times k )-c \times j + ( j - h_i )^2$

显然，$dp_{i-1,k}+c \times k $和$dp_{i-1,k}-c \times k $都是可以提前预处理出来的，那么$\min(dp_{i-1,k}+c \times k )$和$\min(dp_{i-1,k}-c \times k )$也可以通过$O(h)$提前预处理出来。

然后再用滚动数组优化一下空间就可以了。

时间复杂度：$O(n \times h)$，空间复杂度：$O(n+h)$

[code](https://www.luogu.com.cn/paste/8a13chog)

---

## 作者：jun头吉吉 (赞：4)

## 题意
给出若干棵树的高度，你可以进行一种操作：把某棵树增高$h$，花费为$h^2$。

操作完成后连线，两棵树间花费为高度差$\times$定值$c$。

求两种花费加和最小值。
## 题解
朴素的$dp$方程还是很简单的。我们用$f_{i,j}$表示到第$i$颗树，最后一棵的高度为$j$的最小花费。那么则有：

$$f_{i,j}=\min_{w=h_{i-1}}^{maxheight}(f_{i-1,w}+c\times|j-w|+(j-h_i)^2)$$

于是我们想出了一个时间复杂度为$O(maxheight^2\times n)$，空间复杂度为$O(maxheight\times n)$的暴力。

用压位后空间复杂度可以做到$O(2n)$，但时间还是超限。

于是我们来大胆地猜测：$f_{i,j}$转移的$w_1$与$f_{i,j+1}$转移的$w_2$，满足$w_1\le w_2$，即满足**决策单调性**。于是把时间优化到了$O(maxheight\times n)$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100000+100;
int n,c,h[N];
#define min(x,y) (x)>(y)?(y):(x)
#define max(x,y) (x)>(y)?(x):(y)
#define chkmx(x,y) (x)=max((x),(y))
#define chkmn(x,y) (x)=min((x),(y))
#define stO cout<<
#define SJY ans
#define TXDY <<
#define AKIOI endl;
#define sq(x) (x)*(x)
#define int unsigned long long
int ABS(int x,int y){
	if(y>x)return y-x;
	else return x-y;
} 
namespace SJYAKZJOI{
	//最坏复杂度：O(1000*n)→那也是O(n)  （逃 
	int f[2][1001],mxh=0,tmp=0;
	void Day1(){
		for(int i=1;i<=n;i++)
			chkmx(mxh,h[i]);
		for(int j=h[1];j<=mxh;j++)
			f[1][j]=sq(j-h[1]);
		for(int i=2;i<=n;i++){
			int now=i&1,lst=(i-1)&1;
			int lll=h[i-1];
			for(int j=h[i];j<=mxh;j++){
				f[now][j]=0x3f3f3f3f3f3f3f3f;
				while(f[lst][lll]+c*ABS(j,lll)+sq(j-h[i])>=f[lst][lll+1]+c*ABS(j,lll+1)+sq(j-h[i])&&lll<mxh)
				tmp++,
				lll++;
				f[now][j]=f[lst][lll]+c*ABS(j,lll)+sq(j-h[i]);
			}
			//printf("%d\n",i);
		}
		//cout<<tmp<<endl;
		int ans=0x3f3f3f3f3f3f3f3f;
		for(int j=h[n];j<=mxh;j++)
			chkmn(ans,f[n&1][j]);
		stO SJY TXDY AKIOI
	}
}
signed main(){
	//freopen("city.in","r",stdin);
	//freopen("city.out","w",stdout);
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	SJYAKZJOI::Day1();
	return 0;
}
```

---

## 作者：devout (赞：3)

这题卡暴力其实可以减小 $n$ 增加树高就好了

考虑暴力$dp$

- 状态：$f_{i,j}$表示第$i$棵树的高度为$j$的时候的最小花费

- 转移：先考虑一个暴力的转移

$$f_{i,j}=\min\{f_{i-1,k}+c\times\operatorname{abs}(j-k)+(j-a_i)^2\}$$

也就是暴力的做法，不难发现树高取$\max\{a_i\}$以上显然不优，所以这个东西是$O(n(\max\{a_i\})^2)$的，考虑优化

我们把这个式子里面的$j$拎出来，并且对于绝对值分类讨论，变成

$$f_{i,j}=
\begin{cases}
c\cdot j+(j-a_i)^2+\min\{f_{i-1,k}-c\cdot k\}\ (j\geq k)\\
-c\cdot j+(j-a_i)^2+\min\{f_{i-1,k}+c\cdot k\}\  (j<k)
\end{cases}
$$

显然，后面那一坨带$\min$的东西可以进行单调栈优化

那么复杂度就变成$O(n\max\{a_i\})$的了

- 初值：因为一些部分可能取不到，所以$f_{i,j}=inf$，同时因为我们第"0"棵树和第棵树之间应该不能算贡献，所以初值是$f_{0,i}=0$即可

- 答案：$\min\{f_{n,i}\}$

注意~~大家不要被讨论蒙蔽了双眼~~，这里的树只能拔高不能拔低，所以我们只要对于每一个$j\geq a_i$计算$f$就可以

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;
const int M=105;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,c;
int a[N];
int f[N][M];
int s[N],top;
int ans=INT_MAX;

int calc(int i,int j,int opt){
    return f[i][j]+c*j*opt;
}

int main()
{
    memset(f,0x3f,sizeof(f));
    read(n),read(c);
    Rep(i,1,n)read(a[i]);
    Rep(i,1,100)f[0][i]=0;
    Rep(i,1,n){
        top=0;
        Rep(j,1,100){
            while(top&&calc(i-1,s[top],-1)>calc(i-1,j,-1))top--;
            s[++top]=j;
            if(j>=a[i])f[i][j]=min(f[i][j],c*j+(j-a[i])*(j-a[i])+calc(i-1,s[1],-1));
        }
        top=0;
        _Rep(j,100,1){
            while(top&&calc(i-1,s[top],1)>calc(i-1,j,1))top--;
            s[++top]=j;
            if(j>=a[i])f[i][j]=min(f[i][j],-c*j+(j-a[i])*(j-a[i])+calc(i-1,s[1],1));
        }
    }
    Rep(i,1,100)ans=min(ans,f[n][i]);
    printf("%d\n",ans);
    return 0;
}   
```


---

## 作者：Lynkcat (赞：2)

#### 思路源自 $zhang le xing$ 大佬的讲课 "动态规划**入门**"，$ORZ$。

* 先考虑最朴素的暴力 $dp$ ，可以设计 $f(i,j)$ 为第 $i$ 个电线杆高度为 $j$ 时最小的代价，显然我们可以枚举前一个电线杆的高度为 $k$ ,这样我们就可以得出一个方程 $f(i,j)=\min(f(i-1,k)+C \times |j-i|)+(j-h[i])^2$。

* 时间复杂度为 $O (n \times \max(h[i]) ^2)$。

* 虽然可以通过这道题，但我们还可以继续优化

* 我们可以发现，在 $j$ 递增时，$k$ 值也必定递增。所以我们可以考虑只用一个指针扫过去，时间复杂度为 $O (n \times \max(h[i])$

* 事实上还有一种优化：

* 这里直接引用 $zhang le xing$ 大佬课件上的解释：


>假设已经枚举出所有不进行拔高的电线杆，不拔高的电线杆把序列划分为若干个区间，要求对所有其他电线杆进行拔高操作，那么最优方案必定是对每个区间分别设定一个高度，把区间内所有的电线杆都拔到这个高度。观察可以发现每个区间的代价都是一个二次函数，可以 $O(1)$ 求出极值。
同时可以发现，如果区间中最高的电线杆不低于区间端点之一，将整个区间拔高并不优。因此，可以用单调栈维护动态规划求解。
时间复杂度 $O(N)$ 


* 这里解释下为什么最优方案必定是对每个区间分别设定一个高度，把区间内所有的电线杆都拔到这个高度。因为如果这个区间是参差不齐的，把最高的高度压下去一定更优，由此可得这个结论是正确的。



---

## 作者：attack (赞：2)

一开始自己写了个DP，居然能过样例

特别兴奋，

但是交上去只有70分

发现时间复杂度有点高

思路比较简单：

我们可以很容易的看出这道题具有无后效性，

用dp[i][j]表示前i棵树，第i棵树高度为j的最小代价

先预处理一下dp[1][j]，然后对于每一棵树，我们枚举它的前一棵树的高度和这棵树的高度，

计算一下就好

时间复杂度n\*h\*h


代码：

        
                            
                            

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdlib>
using namespace std;
const int MAXN=100001;
const int INF =0x7f7f7f7f;
inline void read(int &n)
{
    char c='+';bool flag=0;n=0;
    while(c<'0'||c>'9'){c=getchar();if(c=='-')flag=1;}
    while(c>='0'&&c<='9')n=n*10+c-48,c=getchar();
}
int dp[MAXN][201];// 第i棵树，高度为j的最小花费
int n,C; 
int a[MAXN];
int maxheight;
int main()
{
    read(n);read(C);
    memset(dp,INF,sizeof(dp));
    for(int i=1;i<=n;i++)
        read(a[i]),maxheight=max(maxheight,a[i]);
    for(int i=a[1];i<=maxheight;i++)
        dp[1][i]=(i-a[1])*(i-a[1]);
    for(int i=2;i<=n;i++)//枚举所有树 
        for(int j=a[i];j<=maxheight;j++)//枚举这棵树的高度 
            for(int k=a[i-1];k<=maxheight;k++)//枚举前一棵树的高度 
                dp[i][j]=min(dp[i][j],
                            ((j-a[i])*(j-a[i])+(dp[i-1][k])+abs(j-k)*C));
    int ans=0x7fffff;
    for(int i=a[n];i<=maxheight;i++)
        ans=min(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}
```
然后化简一下式子


 ![](https://cdn.luogu.com.cn/upload/pic/6976.png) 

（图片来自2017SD夏令营lrh老师讲课）










```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=300005;
const int INF =0x7fffff;
const int maxheight=100;
int dp[301];// 第i棵树，高度为j的最小花费
int f[301];
int n,C;
int a[MAXN];
int bgsum[MAXN];
int edsum[MAXN];
int main() {
    scanf("%d%d",&n,&C);
    for(int i=0; i<n; i++)
        scanf("%d",&a[i]);
    memset(dp, 0x3f, sizeof(dp));
    for(int i=a[0]; i<=maxheight; i++)
        dp[i]=(i-a[0])*(i-a[0]);
    for(int i=1; i<n; i++) { //枚举所有树
        memcpy(f,dp,sizeof(dp));
        for(int j=0; j<=maxheight; j++)    dp[j]=bgsum[j]=edsum[j]=INF;
        bgsum[0]=f[0];
        for(int j=1; j<=maxheight; j++)
            bgsum[j]=min(bgsum[j-1],f[j]-C*j);
        edsum[maxheight]=f[maxheight]+maxheight*C;
        for(int j=maxheight-1; j>=0; j--)
            edsum[j]=min(edsum[j+1],f[j]+C*j);
        for(int j=a[i]; j<=maxheight; j++) //枚举这棵树的高度
            dp[j]=min(edsum[j]-C*j,bgsum[j]+C*j)+(j-a[i])*(j-a[i]);
    }
    int ans=0x7fffff;
    for(int i=a[n-1]; i<=maxheight; i++)
        ans=min(ans,dp[i]);
    printf("%d",ans);
    return 0;
}

```

---

## 作者：zby2001 (赞：2)

看到这题，第一个想法就是DP：

f[i][j]表示到第i棵高度为j的最优值。

顺序枚举树，再枚举每棵树的高度，然后枚举前一棵树的高度然后转移:

f[i][j] = max{f[i][k] + abs(j - k) + j - height[i]}    (height[i - 1] <= k <= 100, height[i] <= j <= 100)

但这样做时间复杂度是O(n\*h\*h)的，明显过不去。

然后我发现单棵树每个高度j的转移和高度j - 1的转移方程相差不大，可以利用这个性质进行转移优化。

我定义一个数组g[j], 表示此棵树的高度为j时，从前一棵树的高度为k(k <= j)，转移来的最小值。

就有 g[j] = min(g[j - 1] + c, f[i - 1][j])

同样，定义一个数组h[j],表示从前一棵树的高度k(k >= j)，转移来的最小值。

就有h[j] = min(h[j + 1] + c, f[j - 1][j])

这样就移去了恶心的绝对值计算。

最后 f[i][j] = min(g[j], h[j]) + (j - height[j])^2

这样，我们就把时间复杂度压缩为了O(nh)

(楼上几位大神Orz，什么贪心，二次函数之类的优化我是真的没看出来)











```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cstdlib>
#include<cmath>
#include<set>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
typedef long long LL;
typedef int T;
const int M = 1000000007;
int n, nc;
int heit[100009];
int f[2][103];
int g[109], h[109];
T _read();
void init();
void solve();
int main() {
    init();
    solve();
    return 0;
}
void init() {
    n = _read();
    nc = _read();
    for(int i = 1; i <= n; i++)
        heit[i] = _read();
    for(int i = 0; i < heit[1]; i++)
        f[1][i] = 0x3fffffff;
    f[1][101] = 0x3fffffff;
    for(int i = heit[1]; i <= 100; i++) {
        int cz = i - heit[1];
        f[1][i] = cz * cz;
    } // 初始化
}
void solve() {
    int d = 1;
    for(int i = 2; i <= n; i++) {
        d ^= 1; //滚动数组
        for(int j = 0; j <= 101; j++) {
            g[j] = 0x3fffffff;
            h[j] = 0x3fffffff;
        }
        for(int j = heit[i - 1]; j <= 100; j++) {
            g[j] = min(g[j - 1] + nc, f[d^1][j]);
        } // g数组的转移
        for(int j = 100; j >= heit[i]; j--) {
            h[j] = min(h[j + 1] + nc, f[d^1][j]);
        } // h数组的转移
        for(int j = 0; j < heit[i]; j++)
            f[d][j] = 0x3fffffff;
        f[d][101] = 0x3fffffff;
        for(int j = heit[i]; j <= 100; j++) {
            int cz = j - heit[i];
            cz *= cz;
            f[d][j] = min(h[j], g[j]) + cz; // 计算答案
        }
    }
    int ans = 0x3fffffff;
    for(int i = heit[n]; i <= 100; i++)
        ans = min(ans, f[d][i]);
    printf("%d\n", ans);
}
T _read() {
    T a = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-')
            f *= -1;
        c = getchar();
    }
    while(c <= '9' && c >= '0') {
        a *= 10;
        a += c - '0';
        c = getchar();
    }
    return a * f;
}
```

---

## 作者：piuke (赞：1)

~~据说是单调队列的样子~~

# 分析
## 状态分析
发现有三个量：
1. 电线杆
2. 该电线杆的高度
3. 当时的最小费用


所以令$dp_{i,j}$表示第$i$杆电线杆高度为$j$时所花的最小费用即可
## 暴力DP分析
分析：无

状态转移方程
$$dp_{i,j}=min\{dp_{i-1,k}+c*|j-k|+(j-h_i)^2\}$$
嗯，枚举一下当前电线杆的高度($j$)和前一根电线杆的高度($k$)即可
## 优化分析
上一个的复杂度是$O(n*{H_{max}}^2)$

而$H_{max}=100$，$n=100000$，不爆才怪……（好像LGOJ评测机很好的样子）

首先，$j-h_i$是一个定值，所以可以暂时不管

然后，看到有一个$|j-h_i|$，绝对值，数学遇到了该怎么办？分类讨论。

所以
$$dp_{i,j}=min\{dp_{i-1,k}+c*k\}-c*j+(j-h_i)^2(k>=j)$$
$$dp_{i,j}=min\{dp_{i-1,k}-c*k\}+c*j+(j-h_i)^2(k<j)$$
诶？枚举$k$时，$j$为一个定值。这样一来，$j,k$就可以同时枚举！

搞一个预处理，显然$dp_{1,j}=(j-h_1)^2$，于是，下面就可以通过$j,k$同时枚举而优化，伪代码如下
```
for i 2 to n {
    long long Minn=INF,Minn1=INF;
    for j 0 to h[i]
        Minn=Min dp[i-1][j]-c*j;
    for j h[i] to maxh
        Minn=Min dp[i-1][j]-c*j;
        dp[i][j]=Min Minn+c*j+(j-h[i])*(j-h[i]);
    for j 100 downto j>=h[i] {
        Minn1=Min dp[i-1][j]+c*j;
        dp[i][j]=Min Minn1-c*j+(j-h[i])*(j-h[i]);
    }
}
```
End......
# 代码
暴力+$O2$靠LG强评测机能过的代码
```cpp
// luogu-judger-enable-o2
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<bitset>
#include<cstdio>
#include<cctype>
#include<string>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
#define reg register
template <typename T>
inline T read() {
    T a=0; char c=getchar(),f=1;
    while(c<'0'||c>'9') {
        if(c=='-') f=-f;
        if(c==-1) return c;
        c=getchar();
    }
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+(c^48),c=getchar();
    return a*f;
}
template <class T>
inline int write(T x) {
    if(x<0) x=(~x)+1, putchar('-');
    if(x/10) write(x/10);
    return putchar(x%10|48);
}
template <class T>
inline int write(T x,char c) {
    return write(x)&&putchar(c);
}
template <class T>
inline T Max(T a,T b) { return a>b?a:b; }
template <class T>
inline T Min(T a,T b) { return a<b?a:b; }
template <class T>
inline T Abs(T a) { return a<0?-a:a; }
int n=read<int>(),c=read<int>();
long long h[100001];
long long dp[100001][101];
long long ans=0x3f3f3f3f;
long long mh;
int main() {
    for(reg int i=1;i<=n;i++)
        mh=Max(mh,h[i]=read<long long>());
    memset(dp,0x3f,sizeof dp);
    for(reg int i=0;i<=mh;i++)
        dp[1][i]=(i-h[1])*(i-h[1]);
    for(reg int i=2;i<=n;i++) {
        for(reg int j=h[i];j<=mh;j++) {
            for(reg int k=h[i-1];k<=mh;k++) {
                dp[i][j]=Min(dp[i][j],dp[i-1][k]+c*Abs(j-k)+(j-h[i])*(j-h[i]));
            }
        }
    }
    for(reg int i=1;i<=mh;i++) {
        ans=Min(ans,dp[n][i]);
    }
    write(ans);
}
```
正解代码
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define reg register
template <typename T>
inline T read() {
    T a=0; char c=getchar(),f=1;
    while(c<'0'||c>'9') {
        if(c=='-') f=-f;
        if(c==-1) return c;
        c=getchar();
    }
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+(c^48),c=getchar();
    return a*f;
}
template <class T>
inline int write(T x) {
    if(x<0) x=(~x)+1, putchar('-');
    if(x/10) write(x/10);
    return putchar(x%10|48);
}
template <class T>
inline int write(T x,char c) {
    return write(x)&&putchar(c);
}
template <class T>
inline T Min(T a,T b) { return a<b?a:b; }
const long long INF=1e15;
int n=read<int>(),c=read<int>();
long long h[100001];
long long dp[100001][101];
long long ans=INF;
long long mh;
int main() {
    for(reg int i=1;i<=n;i++)
        h[i]=read<long long>();
    memset(dp,0x3f,sizeof dp);
    for(reg int i=h[1];i<=100;i++)
        dp[1][i]=(i-h[1])*(i-h[1]);
    for(reg int i=2;i<=n;i++) {
        long long Minn=INF,Minn1=INF;
        for(int j=0;j<=h[i];j++)
            Minn=Min((dp[i-1][j]-c*j),Minn);
        for(int j=h[i];j<=100;j++) {
            Minn=Min(Minn,dp[i-1][j]-c*j);
            dp[i][j]=Min(dp[i][j],Minn+c*j+(j-h[i])*(j-h[i]));
        }
        for (int j=100;j>=h[i];j--) {
            Minn1=Min(Minn1,(dp[i-1][j]+c*j));
            dp[i][j]=Min(dp[i][j],Minn1-c*j+(j-h[i])*(j-h[i]));
        }
    }
    for(reg int i=1;i<=100;i++)
        ans=Min(ans,dp[n][i]);
    write(ans);
}
```


---

