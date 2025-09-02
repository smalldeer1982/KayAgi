# [USACO18FEB] Teleportation S

## 题目描述

Farmer John 最不喜欢的农活之一就是到处搬运牛粪。为了简化这一过程，他发明了一个绝妙的装置：牛粪传送器！与其用拖拉机后面的拖车搬运牛粪，他可以使用牛粪传送器将牛粪从一个位置瞬间传送到另一个位置。

Farmer John 的农场建在一条笔直的长路上，因此农场上的任何位置都可以简单地用其在这条路上的位置来描述（实际上就是数轴上的一个点）。传送器由两个数字 $x$ 和 $y$ 描述，其中被带到位置 $x$ 的牛粪可以瞬间传送到位置 $y$。

Farmer John 决定建造一个传送器，其第一个端点位于 $x = 0$；你的任务是帮助他确定另一个端点 $y$ 的最佳选择。特别地，农场上有 $N$ 堆牛粪（$1 \leq N \leq 100,000$）。第 $i$ 堆牛粪需要从位置 $a_i$ 搬运到位置 $b_i$，Farmer John 会分别搬运每一堆牛粪。如果我们用 $d_i$ 表示 Farmer John 搬运第 $i$ 堆牛粪时拖拉机行驶的距离，那么如果他直接用拖拉机搬运第 $i$ 堆牛粪，则 $d_i = |a_i - b_i|$；如果他使用传送器，则 $d_i$ 可能会更小（例如，通过用拖拉机从 $a_i$ 运到 $x$，然后从 $y$ 运到 $b_i$）。

请帮助 Farmer John 确定通过将传送器的另一个端点 $y$ 建在一个精心选择的最优位置，可以实现的最小 $d_i$ 总和。搬运每堆牛粪时使用相同的 $y$ 位置。

## 说明/提示

在这个例子中，通过设置 $y = 8$，Farmer John 可以实现 $d_1 = 2$、$d_2 = 5$ 和 $d_3 = 3$。请注意，$y$ 在范围 $[7,10]$ 内的任何值也会产生最优解。

题目来源：Brian Dean

## 样例 #1

### 输入

```
3
-5 -7
-3 10
-2 7```

### 输出

```
10
```

# 题解

## 作者：mulberror (赞：17)

安利一下自己博客园博客：[传送门](https://www.cnblogs.com/chhokmah/p/10463469.html)

-----

## 题解

先吐槽一波题目：便便传送门，出题人还真的有一点厉害的~~滑稽~~。

废话不多说。

-----

首先问题的本质就是求如果当这个传送门的端点位于$y$的时候，最小的求出总代价，我们设为函数$f(y)$。

因为这个$f(y)$是一个具有分段线性的结构函数，我们就在求$f(y)$的时候遍历$y$，就可以了。每次当我们处理到两段函数的交界处时，我们就算出两个函数的斜率，算出其中的最小值。

因为有$n$个点，那么复杂度就是$O(n)$，但是一开始我们的各个点的顺序不定，那么我们需要花$O(nlogn)$的时间来进行排序，然后在用$O(n)$的时间遍历计算$f(y)$。

以上的算法比较的简单，但是我们需要用数学计算出每一个交接点的位置就是$y$的值，以及斜率多少和在每一个交接点的变化。

其中$f_i(y)=min(|a_i-b_i|,|a_i-0|+|b_i-y|)$，表示只用于传送门的代价（第一部分表示直接移动，第二个部分表示如果使用传送门），每一个$f_i(y)$函数都是一个简单的函数，我们可以推导出以下的玩意：

![](https://s2.ax1x.com/2019/03/02/kqYIiV.png)

$$f(y)=\sum^{n}_{i=1}f_i (y)$$

对于交接点，每一个函数对最终的答案都是有贡献的，例如如果$|a_i|≥|a_i-b_i|$，那么就说明$f_i(y)$中没有交接点，那么答案就是讲$f_i(y)$向上平移$|a_i-b_i|$。

对于图片中另外一种情况，如果$a_i<0$并且$a_i≥b_i$，那么就说明$f_i$有三个交接点，那么这个贡献的计算就是：当$y=0$时，$f_i(y)$的斜率$-1$，在$y=b$时$+2$，在$y=2b$时$-1$。

可以选择用$map$映射存储$f(y)$函数在各个交接点出的斜率的变化，然后再按照$y$的顺序遍历就可以得到答案了。

----

## ac代码
```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
# include <ctype.h>
# include <iostream>
# include <cmath>
# include <map>
# define LL long long
# define ms(a,b) memset(a,b,sizeof(a))
# define ri (register int)
# define inf (0x7f7f7f7f)
# define pb push_back
# define fi first
# define se second
# define pii pair<int,int>
using namespace std;
inline int gi(){
    int w=0,x=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int n;
map<int,int>mp;
LL x=0,y=-inf,s=0;
int main(){
	n=gi();
	for (int i=1;i<=n;i++){
		int a=gi(),b=gi();
		x+=abs(a-b);
		if (abs(a)>abs(a-b)) continue;
		mp[b]+=2;
		if ((a<b&&a<0)||(a>=b&&a>=0)) mp[0]--,mp[2*b]--;
		if ((a<b&&a>=0)||(a>=b&&a<0)) mp[2*b-2*a]--,mp[2*a]--;
	}
	LL ans=x;
	map<int,int>::iterator it;
	for (it=mp.begin();it!=mp.end();it++){
		int ny=it->fi,tmp=it->se;
		x+=s*(ny-y); y=ny; s+=tmp;
		ans=min(ans,x);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：5)

## 题意
有 $N$ 个货物分别要从数轴的 $a_i$ 运到 $b_i$，有一个起点在 $0$ 的传送门，可以瞬间运送到 $y$，求所有货物运送长度的最小总和。
## 思路
首先要注意，传送门只能从 $0$ 到 $y$，货物也必须是从起点到终点，所以运送的路线只有两种可能，一种是从 $a_i$ 直接到 $b_i$，另一种是从 $a_i$ 到 $0$，再从 $y$ 到 $b_i$。

接下来对每一条路线进行分析，传送门的位置会对路线的缩短造成什么影响。分析可知，如果 $|a_i|<|b_i-a_i|$，使用传送门才有可能让路线变得更短，令 $d_i=|b_i-a_i|-|a_i|$，那么 $y$ 的位置从 $b_i-d_i$ 开始，每向右移动一个单位，路线就缩短一个单位，然后从 $b_i$ 开始，每向右移动一个单位，路线就增加一个单位，然后从 $b_i + d_i$ 开
始，路线不再缩短。

我们可以尝试对 $y$ 进行枚举，但这样效率较低，但在枚举的过程中，只有最多 $2N$ 个点处会导致增量发生变化，显然，在增量不变的前提下，枚举只会不断让答案变得更优或者更劣，所以最优值一定会出现在增量发生变化的点上。因此我们只需要对每个增量发生变化的点进行考虑，统一计算连续段中总和的变化，并调整增量。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;
const int kMaxN = 1e5 + 1;
Pii e[kMaxN * 3] = {{1 << 31, 0}};  // 坐标、变化量
int n, m, d, a, b;
long long ans = 1e16, t, v;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a >> b;
    t += abs(b - a);          // 累加总和
    d = abs(b - a) - abs(a);  // 计算变化半径
    if (d > 0) {              // 半径存在
      e[++m] = {b - d, -1};   // 值下降
      e[++m] = {b, 2};        // 值上升
      e[++m] = {b + d, -1};   // 值持平
    }
  }
  sort(e + 1, e + 1 + m);
  for (int i = 1; i <= m; i++) {
    t += (e[i].first - e[i - 1].first) * v;  // 计算总量变化
    v += e[i].second;                        // 更新增量
    ans = min(ans, t);                       // 更新答案
  }
  cout << ans;
  return 0;
}

```

---

## 作者：analysis (赞：5)

## [USACO18FEB] Teleportation S 题解

首先，我们要对题意进行简化。

### 题意简化

令

$$
f(y) = \sum_{i=1}^{n}\min(|a_i-b_i|,|a_i| + |b_i-y|)
$$

求

$$
\min(f(y))
$$

### 初步思考

这是一个最优解问题，我们会往贪心或动态规划上去思考。

当然，在这一步还不能确定使用什么办法，所以继续向下分析。

先看看这个 $f$ 函数，它是由 $n$ 个 $\min$ 函数组成的。

先考虑暴力。

---

- 朴素做法

枚举每个 $y$，时间 $O(Z)$，其中 $Z = 2 \times 10^8$。

对于 $y$，计算 $f(y)$，时间 $O(n)$。

总时间 $O(Zn)$。

---

显然不能暴力，于是要开始优化。

### 尝试优化计算过程

于是我们观察 $\min$ 函数。

函数中，$a_i$、$b_i$ 是给出的，系常量，而 $y$ 则是变量。

把 $\min$ 拆开，里面的表达式都是一次形式的，所以我们可以很容易的预估到函数图像。

大概是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/2qt96yrz.png)

其中，那三个红点就是关键点。

$A$ 点：$|a_i| + |b_i-y|$ 开始变得比 $|a_i-b_i|$ 小。

$B$ 点：显而易见，这个点就是 $y = b_i$。

$C$ 点：回到 $|a_i-b_i|$ 更小的节点。

$B$ 点我们知道了，接下来计算 $A$、$C$ 点。

显然 $A$、$C$ 点满足：

$$
|a_i-b_i| = |a_i| + |b_i-y|
$$

$A$ 点在 $B$ 点前，故 $y < b_i$，所以：

$$
A:y = b_i - (|a_i-b_i| - |a_i|)
$$

类似的有：

$$
C:y = b_i + (|a_i-b_i| - |a_i|)
$$

然后我们就算完了。

接下来回到 $f$ 函数。

这些性质给了我们什么提示？

单个 $\min$ 函数只有三个拐点，容易想到差分斜率。

把原式化一下：

$$
f(y) = \sum_{i=1}^{n}\min(|a_i-b_i|,|a_i| + |b_i-y|)
$$

$$
= \sum_{i=1}^{n}|a_i-b_i| + \sum_{i=1}^{n}[|a_i| + |b_i-y| < |a_i-b_i|]|a_i| + |b_i-y| - |a_i-b_i|
$$

维护斜率的差分，$A$、$C$ 点为 $-1$，$B$ 点为 $2$。

然后……好像没什么优化。

差分要求前缀和，好像最多把 $O(n)$ 消掉，$O(Z)$ 的时间复杂度还是够呛。

那就得考虑优化枚举了。

### 尝试优化 $y$ 的枚举

$Z$ 带来的时间复杂度很大，我们考虑优化他。

这时候，很容易想到贪心。

容易想到，$y = b_i$ 才有可能最优。

因为若 $y \not= b_i$，那么 $f(y) = \sum|a_i-b_i|$。

所以这样时间复杂度化为 $O(n)$。

### 整理

所以，做法很明了了。

维护斜率的差分，$A$、$C$ 点为 $-1$，$B$ 点为 $2$。

当然，有一类函数没有拐点，即满足 $|a_i| \geq |a_i-b_i|$ 的。

特判即可。

然后对有记录的斜率变化点求值，记录 $ans$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;
map<int,int> tann;
int ans;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        ans += abs(a-b);
        if(abs(a) < abs(a-b))
        {
            tann[b] += 2;
            int tmp = abs(a-b) - abs(a);
            tann[b - tmp]--;
            tann[b + tmp]--;
        }
    }
    map<int,int>::iterator it;
    int sum = ans,lst=-1e9,lstd=0;
    for(it = tann.begin();it!=tann.end();it++)
    {
        int now = it->first,data = it->second;
        sum += (now - lst) * lstd;
        lst = now;
        lstd += data;
        ans = min(ans,sum);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：lllyyykkk (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/P4264)
## 前言
本人认为差分和离散化可以更好的解释这题的思路。
## 思路
对于一个点来说有两种方式，一种是从 $a_i$ 直接到 $b_i$，另一种是从 $a_i$ 到 $0$，从 $0$ 传送至 $y$，再从 $y$ 到 $b_i$。

对于一个需要考虑第二种方式的点 $(a_i=2,b_i=7)$，我们可以列出一个代价与 $y$ 的位置的关系的表格：  
| $y=$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ | $11$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $f(y)=$ | $5$ | $5$ | $4$ | $3$ | $2$ | $3$ | $4$ | $5$ | $5$ |

我们可以发现，$y$ 对于 $f(y)$ 的影响可以是作为两个等差数列，而要区间修改一个等差数列，我们就可以自然想到用二阶差分来进行维护。  
所以对于上文的例子，它的差分数组如下：
| $y=$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ | $11$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 一阶差分 | $0$ | $0$ | $-1$ | $-1$ | $-1$ | $1$ | $1$ | $1$ | $0$ |
| 二阶差分 | $0$ | $0$ | $-1$ | $0$ | $0$ | $2$ | $0$ | $0$ | $-1$ |

那么，设 $d$ 为第二种方式对第一种方式的减少代价大小，我们就只需要修改三个位置的值。

在统计答案时，我们只需要统计这些被修改的点，取其中的最大值。~~其实就是一种离散化和贪心的思想。~~

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,cnt;
long long sum,v,ans;
pair<int,int>a[N*3];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		v+=abs(x-y);
		int d=abs(x-y)-abs(x);
		if(d>0){
			a[++cnt]={y-d,-1};
			a[++cnt]={y,2};
			a[++cnt]={y+d,-1};
		}
	}
	sort(a+1,a+cnt+1);ans=v;
	for(int i=1;i<=cnt;i++){
		v+=(a[i].first-a[i-1].first)*sum;
		sum+=a[i].second;
		ans=min(ans,v);
	}
	cout <<ans<<'\n';
	return 0;
}
``````

---

## 作者：羚羊WANG (赞：4)

[题目传输门](https://www.luogu.com.cn/problem/P4264)

简单介绍一下题目意思：

$Farmer John$正在正在搬粪，他要把粪从$a$地搬运到$b$地

他经过良心发现，决定在$x=0$的地方建造一个垃圾回收站，你的任务是确定一个最优的点$y$，使得他可以通过传输门或直接走到$b$地的最大值

通过观察，我们可以发现，有一些点是永远都是不可能走传输门的。



~~这些点的条件是什么呢~~

**$abs(a)>abs(a-b)$**

满足这个条件的两个点，我们可以直接把$abs(a-b)$的值加入$ans$值

我们可以设$f(x)$表示的是第$x$个点变化的规律

结果发现$f(x)$变化规律是一个很有规律~~其实没有~~的函数图像

### 此时，就来到了这道题最难的部分

其实，这个函数有三个交接点，我们只要用一个差分去维护这个函数图像就行了

那么，三个交接点是哪三个呢

#### 其实是$a-b$ , $b$ , $a+b$
当交接点为$a-b$时，斜率为$-1$

当交接点为$b$时，斜率为$2$

当交接点为$a+b$时，斜率为$-1$

然后，就用一个map维护函数图像的交接点就行了

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int ans;
int sum;
map<int,int> mp;
int minn;
int k;
int l;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			int x;
			int y;
			x=read();
			y=read();
			ans+=abs(x-y);
			if(abs(x)<=abs(x-y))//初始化三个交接点
				{
					mp[y]+=2;
					mp[y-abs(x-y)+abs(x)]--;
					mp[y+abs(x-y)-abs(x)]--; 
				}
		}
	minn=ans;
	l=-100000000;
	map<int,int>::iterator i;
	for(i=mp.begin();i!=mp.end();++i)//分别枚举三个交接点
		{
			int y=i->first;
			int h=i->second;
			minn+=sum*(y-l);
			l=y;
			sum+=h;
			ans=min(ans,minn);
		}
	write(ans);//输出
	return 0;
}
```

最后，祝大家$AC$此题

---

## 作者：Zenith_Yeh (赞：3)

首先设 $f(y)$ 为当传送口为 $y$ 是的代价：

$f_i(y)=min(|a_i-b_i|,|a_i|+|b_i-y|)$。

不难发现 $f_i(y)$ 为一个具有分段线性的结构函数，可以通过讨论 $y$ 的范围，使它变为一个一次函数。

**分两种情况：**

- 若 $|a_i-b_i|≤|a|$，说明使用传送口比不使用要更劣。
- 若 $|a_i-b_i|>|a|$，此时有三个交接点。
	
    分别为:
    1. $\ \ \ \ \ \ b-abs(a-b)+abs(a)$，斜率为 $-1$;
    1. $\ \ \ \ \ \ b$，斜率为 $2$;
    1. $\ \ \ \ \ \ b+abs(a-b)-abs(a)$，斜率为 $-1$;

所以可以选择用 $map$ 映射存储 $f(y)$ 函数在交接点的斜率的变化，然后再按照 $y$ 的顺序遍历就可以得到答案了。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int n,ans,s;
map<int,int> f_y;
signed main()
{	n=read();
	for(register int i=1;i<=n;++i)
	{	int a=read(),b=read();
		ans+=abs(a-b);
		if(abs(a)<=abs(a-b))//三种情况
		{	f_y[b]+=2;
			f_y[b-abs(a-b)+abs(a)]--;
			f_y[b+abs(a-b)-abs(a)]--;
		}
	}
	register int minn=ans,l=-0x7fffffff;
	map<int,int>::iterator bb;//用于遍历map中的每一对数
	for(bb=f_y.begin();bb!=f_y.end();bb++)
	{	int y=bb->first,gong=bb->second;
		minn+=s*(y-l);
		l=y;
		s+=gong;//注意用了差分，所以加前缀和
		ans=min(ans,minn);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：PanH (赞：2)

### 提供一种不用 map 的写法。
~~做法是一样的~~，不过常数确实小一点。

## 做法
别的题解做法讲的比较清楚了，概括一下就是把每个牛粪的 $d_i$ 做出一个关于 $y$ 的函数，这个函数要么是**分段的一次函数**，要么是**常数函数**。

对于分段函数维护它的三个拐点，由于斜率只有 $0,-1,1$ ，所以可以用差分维护一下所有函数和的斜率。

发现我们不需要知道拐点是属于哪个函数的，只要知道拐点之后的函数斜率是什么，所以可以选择排序一遍再做，实现可以看代码。（其实有点类似于离散化了）。

code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct node{
	int op,x;
	bool operator < (const node &o) const {return x<o.x;}
}t[N];
int n,a[N],b[N],now,tot,s,ans;
signed main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	cin>>n;
	//我的代码将所有情况的贡献减去了abs(a[i]),在最后加上 abs(a[i]) 。 
	//这样可以使所有分段函数最低点在 0 （其实没啥用） 。 
	for(int i=1,tmp;i<=n;i++)				
	{
		cin>>a[i]>>b[i];
		tmp=abs(b[i]-a[i])-abs(a[i]);
		if(tmp>0)	//分段函数的情况 
		{
			t[++tot]=(node){-1,b[i]-tmp};
			t[++tot]=(node){2,b[i]};
			t[++tot]=(node){-1,b[i]+tmp};
			s+=abs(a[i]),now+=tmp;
		}
		else s+=abs(b[i]-a[i]);		//常数函数的情况 
	}
	sort(t+1,t+tot+1),ans=now;
	for(int i=1,inc=0;i<=tot;i++)
	{
		inc+=t[i].op; 
		now+=(t[i+1].x-t[i].x)*inc;
		ans=min(ans,now);
	}
	cout<<ans+s;
	return 0;
}
```


---

## 作者：elijahqi (赞：2)

 http://www.elijahqi.win/2018/03/06/luogu4264/ 
http://blog.csdn.net/elijahqi/article/details/79452689
第一次打usaco感觉是
银里最神的题了？我没有ak进到au 实在太菜

首先写出式子min(|a|+|y-b|,|a-b|) 那么可以分类讨论一下 把这个式子写出一次函数的形式

观察到 它应该会存在斜率为+1或者-1的向下凸起 那么我们不妨假设首先我每个的代价都是 a-b  然后我去观察这个图像 来写出我到底是什么时候能够使得减小量最大 那么我们不妨把减小量倒过来 变成向上凸起的山峰 现在相当于求所有山峰的最大值即可 怎么求 我针对山峰的左端点排序 再针对山顶排序  做的时候根据已经添加的山峰的最右端维护一个小根堆  然后弹出为了计算山峰和山峰之间的答案我们怎么搞呢 就是首先删除到一半就停止了的山峰 然后对下坡和上坡的差值进行计算 然后添加上中间进入的山峰 注意过了一个山顶之后需要将上坡和下坡进行一个交换
```
#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>
#define N 110000
#define ll long long
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
inline int abs(int x){return x<0?-x:x;}
struct node{
    int l,r,top;
    inline friend bool operator <(const node &a,const node &b){
        return a.r>b.r;
    }
}data[N],data1[N];
priority_queue<node,vector<node> >q;
int n,cnt,up,down;ll ans=0,mx1,mx;
inline bool cmp1(const node &a,const node &b){return a.l<b.l;}
inline bool cmp2(const node &a,const node &b){return a.top<b.top;}
int main(){
//	freopen("teleport.in","r",stdin);
//	freopen("teleport.out","w",stdout);
    n=read();ans=0;
    for (int i=1;i<=n;++i){
        int a=read(),b=read(),l,r;node tmp;tmp.top=b;
        ans+=abs(a-b);if (abs(a-b)<=abs(a)) continue;
        if (a>=0){
            if (a>b){l=b-b,r=2*b;if (l>r) swap(l,r);tmp.l=l;tmp.r=r;}
            if (a<b){l=a<<1;r=2*b-2*a;if (l>r) swap(l,r);tmp.l=l;tmp.r=r;}
            data1[++cnt]=data[cnt]=tmp;continue;
        }if (a>b){l=a<<1;r=2*b-2*a;if (l>r) swap(l,r);tmp.l=l;tmp.r=r;}
        if (a<b){l=b-b,r=2*b;if (l>r) swap(l,r);tmp.l=l;tmp.r=r;}
        data1[++cnt]=data[cnt]=tmp;
    }sort(data+1,data+cnt+1,cmp1);sort(data1+1,data1+cnt+1,cmp2);
    int now=1;
    for (int i=1;i<=cnt;++i){
        while(!q.empty()&&q.top().r<data1[i].top) {
            mx1-=q.top().r-data1[i-1].top,q.pop(),--down;
        }mx1+=(ll)(up-down)*(data1[i].top-data1[i-1].top);
        while(data[now].l<=data1[i].top&&now<=cnt) {
            q.push(data[now]),++up,mx1+=data1[i].top-data[now].l;++now;
        }
        mx=max(mx,mx1);--up;++down;
    }
    printf("%lld\n",ans-mx);
    return 0;
}
```

---

## 作者：Tsawke (赞：1)

# [LG-P4264 [USACO18FEB]Teleportation S](https://www.luogu.com.cn/problem/P4264) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P4264-Solution)

### 题面

数轴上存在 $ n $ 对 $ a_i, b_i $ 表示有一坨牛粪需要从 $ a_i $ 送到 $ b_i $ 并贡献 $ d_i = \vert a_i - b_i \vert $，数轴上存在一个起点为 $ 0 $，终点为 $ y $ 的便便传送门，可以在 $ 0 $ 的贡献下将牛粪从 $ 0 $ 传送到 $ y $，同样贡献为不用传送门走的距离，最小化贡献和，求最小值。

$ 1 \le n \le 10^5, -10^8 \le a_i, b_i \le 10^8 $。

### Solution

~~这道题告诉我们，题做不出来的时候要多去去厕所，去溜达一圈之后或许就突然想明白了~~。。

我感觉还算是一道挺有意思的题，比较奇妙，难度适中，蓝色评的也很合理。

显然当 $ y $ 确定后对于每一对 $ a_i, b_i $ 的贡献即为 $ f(y)_i = \min(\vert a_i - b_i \vert, \vert a_i \vert + \vert y - b_i \vert) $，我们的答案即为 $ \sum_{i = 1}^n f(y)_i $。

此时显然如果有 $ \vert a_i - b_i \vert \lt \vert a_i \vert $，解一下就是 $ a_i \ge b_i \gt 0 \vee 0 \le a_i \lt b_i \lt 2a_i \vee 0 \gt a_i \gt b_i \gt 2a_i \vee a_i \lt b_i \lt 0 $，那么一定不走传送门，也就是选前者，这样的话对于这个 $ f(y)_i $ 就是一条直线，不过这一大坨不等式看着就很阴间，画个图吧：

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_11_07_2.png)

观察发现剩下的可能性就只有 $ 0 \le 2a_i \lt b_i \vee b_i \lt2a_i \le 0 \vee a_i \lt 0 \lt b_i \vee b_i \lt 0 \lt a_i $ 了，而这一段区间则与 $ y $ 相关，需要额外讨论一下。

此时的原式为 $ f(y)_i = \min(\vert a_i - b_i \vert, \vert a_i \vert + \vert y - b_i \vert) $，考虑分类讨论，如在 $ 0 \le 2a_i \lt b_i $ 的条件下，原式转化为 $ \min(b_i - a_i, a_i + \vert y - b_i \vert) $，然后把 $ y $ 和 $ b_i $ 之间的关系讨论一下（这里就很简单了，不多赘述，注意一下 $ b_i \lt 2b_i - 2a_i $ 在条件下恒成立即可），最终可以写成一下柿子：

$ 0 \le 2a_i \lt b_i $：
$$
f(y)_i = \left\{
	\begin{array}{ll}
	b_i - a_i &\quad y \in (-\infty, 2a_i] \cup [2b_i - 2a_i, +\infty) \\
	-y + a_i + b_i &\quad y \in (2a_i, b_i) \\
	y + a_i - b_i &\quad y \in [b_i, 2b_i - 2a_i)
	\end{array}
\right.
$$
然后在 $ b_i \lt2a_i \le 0 $ 同理可以推出：

$ b_i \lt2a_i \le 0 $：
$$
f(y)_i = \left\{
	\begin{array}{ll}
	a_i - b_i &\quad y \in (-\infty, 2b_i - 2a_i] \cup [2a_i, +\infty) \\
	-y - a_i + b_i &\quad y \in (2b_i - 2a_i, b_i) \\
	y - a_i - b_i &\quad y \in [b_i, 2a_i)
	\end{array}
\right.
$$
剩下的两个区间也同理推导一下即可：

$ a_i \lt 0 \lt b_i $：
$$
f(y)_i = \left\{
	\begin{array}{ll}
	b_i - a_i &\quad y \in (-\infty, 0] \cup [2b_i, +\infty) \\
	-y - a_i + b_i &\quad y \in (0, b_i) \\
	y - a_i - b_i &\quad y \in [b_i, 2b_i)
	\end{array}
\right.
$$
$ b_i \lt 0 \lt a_i $：
$$
f(y)_i = \left\{
	\begin{array}{ll}
	a_i - b_i &\quad y \in (-\infty, 2b_i] \cup [0, +\infty) \\
	-y + a_i + b_i &\quad y \in (2b_i, b_i) \\
	y + a_i - b_i &\quad y \in [b_i, 0)
	\end{array}
\right.
$$
现在我们也就能确定下来每一条 $ f(y)_i $ 的形状了，都是类似下图的形状，只是 “转折点” 不同，和 $ y $ 无关的认为其没有转折点即可。

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_11_07_3.png)

此时我们就需要考虑一下求 $ \sum_{i = 1}^nf(y)_i $ 了。

不难想到 $ O(n) $ 记录一下每一条线的 “转折点” 的位置，建立一个差分数组，然后每条线段斜率变为 $ -1 $ 之后对应位置加上 $ -1 $，斜率变为 $ 1 $ 之后加上 $ 2 $，变回与 $ y $ 相关之后再加上 $ -1 $，然后我们把差分数组做个前缀和，这样当前的前缀和数组的值就是 $ i $ 相对 $ i - 1 $ 的总答案变化量，对于 $ 0 $ 处我们认为其为 $ \sum_{i = 1}^n \vert a_i - b_i \vert $，然后在前缀和上再做一个前缀和，令其为 $ sum_i $，则不难想到答案即为 $ \min\{sum_i\} $，然后这里因为坐标值域范围很大，所以考虑离散化，为了写着方便，直接开一个 `map` 存即可，排序也省了。

至此，我们就做完了这道奇怪的大分类讨论，复杂度 $ O(n \log n) $，卡在排序上。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template< typename T = int >
inline T read(void);

int N;
ll origin(0);
ll mn(LONG_LONG_MAX);
map < ll, ll > mp;
ll sum[310000]; int cnt(0);

void Insert(int p, int v){
    if(mp.find(p) == mp.end())mp.insert({p, v});
    else mp[p] += v;
}
void InsertAll(int sp1, int sp2, int sp3){
    Insert(sp1, -1);
    Insert(sp2, 2);
    Insert(sp3, -1);
}

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        int a = read(), b = read();
        origin += abs(a - b);
        if(0 <= 2 * a && 2 * a < b)InsertAll(2 * a, b, 2 * b - 2 * a);
        else if(b < 2 * a && 2 * a <= 0)InsertAll(2 * b - 2 * a, b, 2 * a);
        else if(a < 0 && 0 < b)InsertAll(0, b, 2 * b);
        else if(b < 0 && 0 < a)InsertAll(2 * b, b, 0);
    }
    ll cur(0), sum(origin); int lft(INT_MIN);
    mn = origin;
    for(auto v : mp){
        sum += (ll)cur * (v.first - lft);
        cur += v.second, lft = v.first;
        mn = min(mn, sum);
    }
    printf("%lld\n", mn);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_07 初稿

---

## 作者：Na2PtCl6 (赞：0)

看到题解区都是维护斜率，我不禁感叹，人和人之间的差距真的是后天难以弥补的啊。读的都是同一个题面，但是有的人能认识到斜率的本质，像我这样的菜鸡就只会用数据结构暴力拆绝对值。

### 分析
考虑每个答辩，$0$ 到起点到位置是定值，然后 $y$ 到终点距离是个绝对值函数，所以我们可以找到能使得这坨答辩运输的路程减小的 $y$ 的范围。我们将其称为这坨答辩的领域。

根据一次函数的性质，“领域”内有代表性的点只有三个：运输的终点，以及“领域”的左右端点。

可以开很多个 `vector` 来提前标记每个答辩的“领域”，扫到一个点就把在这个点上有加入标记的答辩丢进集合，把有删除标记的答辩从集合中剔除。

这样我们就按顺序从小到大枚举所有代表性的点，并且找出这个点在哪些答辩的“领域”内。

可以用树状数组维护集合内答辩的终点，小于当前点的终点就用当前坐标去减，大于则反之，这样就实现了拆绝对值。

在领域外的点就是原路程，统计一个和就行了。

### 代码
```cpp
#include<set>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=114514,S=1e8+1;
int n,res,sz,cnt,tot,ori,a[maxn],b[maxn];
vector< int > coor,ins[maxn*3],del[maxn*3];

struct item{
    int init,pos,l,r,len;
    bool operator < (const item &comp)const{
        return pos<comp.pos;
    }
}manure[maxn];

struct BIT{
    int sum[maxn*3];
    
    void add(int p,int v){
        while(p<=sz+1){
            sum[p]+=v;
            p+=p&-p;
        }
    }
    
    int query(int p){
        int ret=0;
        while(p){
            ret+=sum[p];
            p-=p&-p;
        }
        return ret;
    }
    
}t1,t2;



signed main(){
//    printf("%d\n",0x7fffffff+1);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&a[i],&b[i]);
        manure[i].init=abs(a[i]);
        a[i]+=S,b[i]+=S;
        manure[i].pos=b[i];
        manure[i].len=abs(b[i]-a[i]);
        ori+=manure[i].len;
        if(a[i]<b[i]){
            manure[i].l=a[i]+manure[i].init;
            manure[i].r=b[i]+b[i]-a[i]-manure[i].init;
        }
        else{
            manure[i].r=a[i]-manure[i].init;
            manure[i].l=b[i]-(a[i]-b[i])+manure[i].init;
        }
        if(manure[i].l<=manure[i].r)
            coor.push_back(b[i]),coor.push_back(manure[i].l),coor.push_back(manure[i].r);
    }
    sort(b+1,b+n+1);
    sort(manure+1,manure+n+1);
    sort(coor.begin(),coor.end());
    for(int i=1;i<=n;i++){
        if(manure[i].l>manure[i].r)
            continue;
        manure[i].l=lower_bound(coor.begin(),coor.end(),manure[i].l)-coor.begin();
        manure[i].r=upper_bound(coor.begin(),coor.end(),manure[i].r)-coor.begin()-1;
//        printf("pos:%lld l:%lld r:%lld\n",b[i]-S,manure[i].l,manure[i].r);
        ins[manure[i].l].push_back(i);
        del[manure[i].r+1].push_back(i);
        
    }
    res=ori;
//    printf("%lld\n",mini);
    sz=coor.size();
    for(int i=0;i<sz;i++){
        for(int j:ins[i]){
            ++cnt;
            tot+=b[j];
            ori-=manure[j].len;
            ori+=manure[j].init;
            int pos=lower_bound(coor.begin(),coor.end(),b[j])-coor.begin();
            t1.add(pos+1,1);
            t2.add(pos+1,b[j]);
        }
        for(int j:del[i]){
            --cnt;
            tot-=b[j];
            ori+=manure[j].len;
            ori-=manure[j].init;
            int pos=lower_bound(coor.begin(),coor.end(),b[j])-coor.begin();
            t1.add(pos+1,-1);
            t2.add(pos+1,-b[j]);
        }
        int pos=lower_bound(coor.begin(),coor.end(),coor[i])-coor.begin();
        int presum=t2.query(pos+1),precnt=t1.query(pos+1);
        int val=precnt*coor[i]-presum+(tot-presum)-coor[i]*(cnt-precnt);
        printf("pos:%lld num1:%lld sum1:%lld num2:%lld sum2:%lld val:%lld\n",coor[i]-S,precnt,presum,cnt-precnt,tot-presum,val);
        res=min(res,ori+val);
    }
    printf("%lld\n",res);
    return 0;
}
/**
3
-20 21
114 514
1919 810
*/

```

---

## 作者：HappyJaPhy (赞：0)

- [博客阅读体验更佳](https://www.luogu.com.cn/blog/ImDustSans/solution-p4264)
- [题目传送门](https://www.luogu.com.cn/problem/P4264)
# 题意
- 有 $n$ 个物品，分别需要从 $a_i$ 运输到 $b_i$ 处，$x=0$ 处有一个传送门入口，选择一个传送门出口 $y$，使得总运输距离 $d$ 最小，输出最小值。

# 分析
- 很明显，传送门对于总距离 $d$ 的贡献是可以拆分成对于每一个物品的贡献之和的，因为有 $d=\sum d_i$。
- 然后我们分析一下 $y$ 的选址对于每一个物品的 $d_i$ 的贡献。
- 通过画图和分类讨论可以发现，一共有两种情况，而且每个 $y$ 对应的 $d_i=f_i(y)=\min(|a_i-b_i|,|a_i|+|b_i-y|)$ 是分段且线性的，根据线性函数的一些性质，我们可以利用对斜率的差分来求解 $d=\min_{y\in \mathbb{R}}{\sum f_i(y)}$。

## 画图
1. $|a|>|a-b|$
- 这时候肯定不会走传送门的，因为运去 $x=0$ 那里都比直接运要远。

2. $|a|<|b|$
![0<a<b](https://cdn.luogu.com.cn/upload/image_hosting/32eahftb.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/mzspywmo.png)
- 如图所示，这种情况下三个分段点分别是 $2a$，$b$ 和 $2b-2a$。

3. $a<0<b/b<0<a$
![](https://cdn.luogu.com.cn/upload/image_hosting/2fno3fcj.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ijhzhit6.png)
- 如图所示，这种情况下的三个分段点是 $0$，$b$ 和 $2b$。
- 而且，这三种情况的初始值均为 $|a-b|$，所以初始值 $f(-\infty)$ 要设成 $\sum|a_i-b_i|$。

## 实现
- 对于每一个物品，根据上图分类后利用 map 来存储差分的数组。对第一个分段位置 $-1$，对第二个 $+2$，最后一个 $-1$。处理完之后按 $y$ 的值从小到大遍历 map，对于每一个 $f(y)$ 的分段点的值求最小值即可。

# 代码
```cpp
#include <bits/stdc++.h>
#define inf 0x7fffffff
#define int long long
using namespace std;
int n, x, y = -inf, s, ans;
map<int, int> mp;

inline void read(int &x) {
	int w = 1;
	char ch = x = 0;
    while (ch < '0' || ch > '9') {
    	if (ch == '-') w *= -1;
    	ch = getchar();
	}
    while(ch >= '0' && ch <= '9') {
    	x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= w;
	return ;
}

signed main() {
	read(n);
	int a, b;
	for (int i = 1; i <= n; i++) {
		read(a), read(b);
		x += abs(a - b);
		if (abs(a) > abs(a-b)) continue; //第一种情况
		mp[b] += 2;
		if ((a < b && a < 0) || (a >= b && a >= 0)) { //处理后两种情况
			mp[0]--;
			mp[b << 1]--;
		} else if ((a < b && a >= 0) || (a >= b && a < 0)) {
			mp[(b - a) << 1]--;
			mp[a << 1]--;
		}
	}
	ans = x;
    int now, tmp;
	for (auto it : mp) { //对于每一个分段点都统计，取最小值
		now = it.first, tmp = it.second;
		x += s * (now - y);
		y = now;
		s += tmp;
		ans = min(ans, x);
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：raincity (赞：0)

## 分析
对于确定的 $y$，有 $dis=\sum_{i=1}^n\min(|a_i-b_i|,|a_i|+|b_i-y|)$。

设 $g_i(y)=\min(|a_i-b_i|,|a_i|+|b_i-y|)$。

设 $f(y)=\sum_{i=1}^ng_i(y)$，则 $ans=\min \{f(y)\}$。

显然 $f(y)$ 在 $y=b_i$ 时取最小值。

对于 $1\le i\le n$：

若 $|a_i-b_i|\le |a_i|$，则 $g_i(y)$ 的图像为一条直线 $y=|a_i-b_i|$。

若 $|a_i-b_i|>|a_i|$，则 $g_i(y)$ 为一个单谷函数，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xfnpna7s.png)

容易知道 $|a_i-b_i|=|a_i|+|x_A-b_i|=|a_i|+|x_C-b_i|$，且 $k_{AB}=-1,k_{BC}=1$，$x_B=b_i$。

解得 $x_A=b_i-|a_i-b_i|+|a_i|$，$x_C=b_i+|a_i-b_i|-|a_i|$。

将 $x_A,x_B,x_C$ 称为“关键点”。在 $x_A,x_C$ 处标  -1，在 $x_B$ 标 2，只需要先求出 $\sum_{i=1}^n|a_i-b_i|$，然后在每一个关键点进行修改即可。

## 解决
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;;

const int N = 100005;
int n, a, b, tot, sum;
long long res, ans;

struct diff {
	int val, pos;
	bool operator <(const diff &other) const { return pos < other.pos; }
	diff(int val, int pos): val(val), pos(pos) {}
	diff(): val(0), pos(0) {}
}d[N * 3];

template <typename T>
void read(T &ret) {
	ret = 0;
	char ch = getchar(), flag = 0;
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-')
		ch = getchar(), flag = 1;
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
	if (flag)
		ret = -ret;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		read(a), read(b);
		int x = abs(a - b), y = abs(a);
		if (x > y)
			d[++tot] = diff(-1, b - x + y), d[++tot] = diff(2, b), d[++tot] = diff(-1, b + x - y);
		res = res + x;
	}
	ans = res;
	// cout << "res = " << res << endl;
	sort(d + 1, d + tot + 1);
	for (int i = 1, j = 1; i <= tot; ) {
		while (d[j].pos == d[i].pos && j <= tot) sum += d[j].val, res = res + (d[j + 1].pos - d[j].pos) * sum, j++;
		i = j, ans = min(ans, res);
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：2xyz (赞：0)

### 假如只有1堆牛粪：


------------

### 1. a≤b

对于起点a，有两种选择：

1. 不借助传送门，花费为 | a - b | 

2. 借助传送门，此时应先从a走到0，再从y走到b，花费为 | a | + | y - b |

我们可以画出下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4rit3brp.png)

分类讨论：

1. | a | ≥ | a - b | ，此时传送门修在任何地点 都不如 不借助传送门优。

2. 当传送门修在2a与b之间时，总花费递减。

3. 当传送门修在b与a+b之间时，总花费（相较于第2步，下同）递增。

**当a小于0时怎么办？**

首先明确一点：**如果要借助传送门，那么a可以小于0，但是b一定不小于0。** 因为a需要先走到0，如果b也小于0，那么不借助传送门一定更优。

当 | a | < | a - b | 时，

1. 当传送门修在0与b之间时，总花费递减。

2. 当传送门修在b与2b之间时，总花费递增。

### 2. a>b

与a≤b时相反，留给大家自行思考。

本题利用 差分的思想 和 map 来存储函数的斜率。

代码：

```cpp
#include<map>
#include<cstdio>
using namespace std;
int n,a,b;
int slope,last;   //slope记录斜率,last记录上一个点的位置 
long long ans,l;
map<int,int>f;
inline int abs(int x) {
	if(x<0) return -x;
	return x;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d %d",&a,&b);
		ans+=abs(a-b);
		if(abs(a)>=abs(a-b)) continue;
		if(a<b) {
			if(a>=0) {
				f[2*a]--;
				f[b]+=2;
				f[a+b]--;
			} else if(b>=0) {
				f[0]--;
				f[b]+=2;
				f[2*b]--;
			}
		} else if(a>b) {
			if(a<0) {
				f[b-(a-b-(-a))]--;
				f[b]+=2;
				f[b+(a-b-(-a))]--;
			} else if(b<0) {
				f[b+b]--;
				f[b]+=2;
				f[0]--;
			}
		}
	}
	l=ans;
	for(map<int,int>::iterator i=f.begin();i!=f.end();i++) {   //不会map,此处是借鉴其他题解写的 
		int x=i->first,slope_x=i->second;
		l+=slope*(x-last);   //差分 
		slope+=slope_x;
		ans=min(ans,l);
		last=x;
	}
	printf("%lld",ans);   //Also you may want to consider whether the answer is necessarily an integer or not...
	return 0;
}
```

---

