# Wet Shark and Bishops

## 题目描述

Today, Wet Shark is given $ n $ bishops on a $ 1000 $ by $ 1000 $ grid. Both rows and columns of the grid are numbered from $ 1 $ to $ 1000 $ . Rows are numbered from top to bottom, while columns are numbered from left to right.

Wet Shark thinks that two bishops attack each other if they share the same diagonal. Note, that this is the only criteria, so two bishops may attack each other (according to Wet Shark) even if there is another bishop located between them. Now Wet Shark wants to count the number of pairs of bishops that attack each other.

## 说明/提示

In the first sample following pairs of bishops attack each other: $ (1,3) $ , $ (1,5) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ and $ (3,5) $ . Pairs $ (1,2) $ , $ (1,4) $ , $ (2,5) $ and $ (4,5) $ do not attack each other because they do not share the same diagonal.

## 样例 #1

### 输入

```
5
1 1
1 5
3 3
5 1
5 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 1
2 3
3 5
```

### 输出

```
0
```

# 题解

## 作者：fzj2007 (赞：8)

# 第一步 读题

>有一个 $1000\times1000$ 的棋盘，上面有 $n(1\le n\le 200000)$ 个象，每个象的位置为$\left(x_i,y_i\right)$。 
**注意，这里的规定与国际象棋的不同。我们认为，只要两个象在同一对角线，就能够相互攻击到（中间有象也没有关系）。** 求互相攻击的象的对数。

首先看题，是让我们求出有多少组象能互相攻击到。**注意：这里的象和国际象棋的不一样，他可以跨过某一个或一些象来攻击其他象。** 这可是一个大坑啊！注意审题（多看几遍）。

# 第二步 思路

思路一：暴力模拟两个象是否相互攻击，如果相互攻击就累加，最后输出答案。时间复杂度 $O\left(n^2\right)$，但是我们发现 $1 \le n \le 2 \times 10 ^ 5$，这个开到 $n^2$ 明显爆炸了。。所以我们要优化。

------

思路二：我们可以来枚举对角线。我们可以计算每个位置的横坐标与纵坐标的和。以 $3$ 行 $3$ 列来找规律：

|  | $1$ | $2$ | $3$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $1+1=2$ | $1+2=3$ | $1+3=4$ |
| $2$ | $2+1=3$ | $2+2=4$ | $2+3=5$ |
| $3$ | $3+1=4$ | $3+2=5$ | $3+3=6$ |

我们发现，每个右上到左下的斜线上的数值都相等。那么我们就可以判断每一个右上到左下的斜线，从而找到每一个右上到左下的斜线上有多少对象能够互相攻击。

我们再看每一个位置的横坐标与纵坐标的差（由于有可能为负，所以我们都加上一个数值。这个数值一定要大于原本减完可能出现的数值，用来保存负数。由于我们以三行三列来找规律，所以我们统一加上4。）

|  | $1$ | $2$ | $3$ |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $1-1+4=4$ | $1-2+4=3$ | $1-3+4=2$ |
| $2$ | $2-1+4=5$ | $2-2+4=4$ | $2-3+4=3$ |
| $3$ | $3-1+4=6$ | $3-2+4=5$ | $3-3+4=4$ |

我们发现，每个左上到右下的斜线上的数值都相等，那么我们也可以判断每个左上到右下的斜线，最后找到这条斜线上有多少象可以互相攻击。

找到规律后，我们要知道如何来寻找有多少个象可以互相攻击。

| 斜线上象的数量 | 攻击组数 |
| :-----------: | :-----------: |
| $1$ | $0$ |
| $2$ | $1$ |
| $3$ | $3$ |
| $n$ | $1+2+...+\left(n-1\right)=\frac{n\left(n-1\right)}{2}$ |

这样，我们就有了这道题的核心思路。

# 第三步 代码
代码内有讲解，请慢慢食用。
```cpp
#include<bits/stdc++.h>//愉快的万能头
using namespace std;
inline int read(){//快读板子
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+(ch^'0');
		ch=getchar();
	}
	return ans*flag;
}
int n,x,y;//读入需要的数据
int a[2005],b[2005];//分别表示两个对角线
long long ans;//表示答案，出题人很坑要开long long
int main(){
	n=read();//读入n
	for(int i=1;i<=n;i++){//循环模式
		x=read(),y=read();//先读入
		a[x+y]++;//右上到左下的斜线
		b[y-x+1001]++;//左上到右下的斜线，由于是1000*1000的棋盘，所以加上1001（你愿意多加就多加，但是数组别忘了开大）
	}
	for(int i=0;i<=2000;i++)//1000*1000的棋盘，两个1000加起来是2000。
		ans+=(long long)(a[i]*(a[i]-1)+b[i]*(b[i]-1))/2;//这里是同时判断，直接加上这个数的左上到右下、右上到左下的和。（运用乘法分配律），这里要强转一下
	printf("%lld\n",ans);//最后输出
	return 0;//return 233;
}
```
# 第四步 宣传

如果有帮助，请点个赞，谢谢！（撰文不易，`dalao`勿喷！）如果发现我的讲解有`bug`，请及时指出，感谢！




---

## 作者：_Harrisonwhl_ (赞：2)

这道题用暴力 $O(n^2)$ 的做法是不行的，可以用数学公式排列组合。

我们可以找规律，对角线方向为左上到右下时，同一对角线纵横坐标差值相等，在右下到左上时纵横坐标和相等，于是我们可以利用这一特性，算出每个对角线上有几只象，用排列组合算出结果。

最后说两点

1. 要开 $long$ $long$!

2. 每个方向有1999约等于2000条对角线。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2005],b[2005];
long long ans = 0;
int main()
{
    int n,t1,t2;
    cin >> n;
    for (int i = 1;i <= n;i++)
    {
        scanf("%d%d",&t1,&t2);
        a[t1 - t2 + 1000]++;//左上到右下，为防止负下标，需要加1000。
        a[t1 + t2]++;//左下到右上。
    }
    for (int i = 1;i <= 2000;i++)
        ans += a[i] * (a[i] - 1) / 2 + b[i] * (b[i] - 1) / 2;//公式，排列组合。
    cout << ans;
    return 0;
}
```
再附赠快读模版（此题不需要）：
```cpp
int read(){
	int s = 0;
	bool f = 0;
	char ch = getchar();
	while(ch > '9' or ch < '0'){
		if(ch == '-')
			f = 1;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return f?-s:s;
}
```

---

## 作者：Qiancy1427 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF621B)

其实这个题的数据还是很水的，暴力搜索就可以过了。

### 思路

这道题问的是在 $1000 \times 1000$ 的棋盘上有 $n$ 个象，有多少对象会互相攻击。

**注意：**
这里象不会互相遮挡。

简单来看，就是一个比较典型的 DFS，沿四个方向搜索，遇到象答案就加一，直到走到棋盘边界结束。

由于每一对象会被搜到两遍（两个端点各搜一遍），所以最后的答案是计数的一半。

### 关键代码片段

这里有一个小问题。象在四个方向上的范围都是直线，在整个搜索过程中必须沿同一个方向。因此在函数中要有一个变量（$mo$）来记录每次的方向。

先上一下 DFS 部分的代码。

```cpp
void dfs(int x1,int y1,int mo){
	if(x1<=0||x1>1000||y1<=0||y1>1000){	//判断是否出界 
		return;
	}
	if(book[x1][y1]==1)	ans++;	//如果有象 
	dfs(x1+mov[mo][0],y1+mov[mo][1],mo);	//继续向前 
	return;
}
```

### 全部代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int x[200005],y[200005];	//把每个象的坐标都记下来 
int book[1005][1005];	//标记象 
int mov[4][2]={{1,1},{1,-1},{-1,-1},{-1,1}};	//方向数组 
void dfs(int x1,int y1,int mo){
	if(x1<=0||x1>1000||y1<=0||y1>1000){
		return;
	}
	if(book[x1][y1]==1)	ans++; 
	dfs(x1+mov[mo][0],y1+mov[mo][1],mo);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		book[x[i]][y[i]]=1;
	}
	for(int i=1;i<=n;i++){	//每个象依次搜索 
		dfs(x[i],y[i],0);	//四个方向分别搜 
		dfs(x[i],y[i],1);
		dfs(x[i],y[i],2);
		dfs(x[i],y[i],3);
		ans-=4;
	}
	cout<<ans/2;	//最后答案除以二 
	return 0;
}
```

### 说明

这道题数据可能相对较弱，不然其实这个暴力 DFS 其实很有可能超时。不过暴力在比赛的时候也是可以骗到一些分的，也是很有用的。

---

## 作者：流绪 (赞：1)

对角线上的鲨鱼会打架，给一个图里鲨鱼的位置，问有几对鲨鱼会打架？

首先我们把每条对角线上的鲨鱼数量求出来，再遍历每条对角线算出会打架的对数，加起来就好啦！

每条对角线上的鲨鱼会攻击另外的所有鲨鱼，所以会有 n*(n-1) 对,但是我们这样计算会重复算一遍，所以除以 2。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
int a[maxn],b[maxn]; 
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		int c,d;
		cin >> c >> d;
		a[c+d]++;//主对角线 
		b[d-c+1000]++;//副对角线 
	}
	ll cnt = 0; 
	for(int i=1;i<=2000;i++)
		cnt +=a[i]*(a[i]-1)/2+b[i]*(b[i]-1)/2;
	cout << cnt;
	return 0; 
}  
```


---

## 作者：achjuncool (赞：0)

# 思路

显然，如果是在同一条从左下到右上的对角线上的两个棋子，则它们的横纵坐标之差相等；如果是在同一条从右下到左上的对角线上的两个棋子，则它们的横纵坐标之和相等。

所以，我们可以开两个 `unordered_map`，键值分别是横纵坐标之和、横纵坐标之差，映射值是和或差是这个键值的棋子的数量，即同在某一条对角线上的棋子的数量。

对于每一条对角线，设其上有 $x$ 个棋子，则总数增加 $\frac{x(x-1)}{2}$。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll n, x, y, ans;
unordered_map<ll, ll> add, minus1;
unordered_map<ll, ll>::iterator it;
int main(){
	qwq;
	cin >> n;
	for(ll i = 1; i <= n; i++){
		cin >> x >> y;
		it = add.find(x + y);
		if(it == add.end()) add[x + y] = 1;
		else add[x + y]++;
		it = minus1.find(x - y);
		if(it == minus1.end()) minus1[x - y] = 1;
		else minus1[x - y]++;
	}
	for(auto p = add.begin(); p != add.end(); p++) ans += (p->second - 1) * p->second / 2;
	for(auto p = minus1.begin(); p != minus1.end(); p++) ans += (p->second - 1) * p->second / 2;
	cout << ans << endl;
	return 0;
}
```cpp

---

## 作者：HadrianZhang (赞：0)

# 思路

本题的本质就是统计每条对角线上棋子的个数。

若该条对角线的棋子数为 $n$，根据排列组合，得该条对角线上互相攻击的棋子对数为 $\frac{n \times (n-1)}{2}$。

如何统计每条对角线上棋子个数？

首先，在同一条对角线上的情况分两种：

- 左上到右下：每个格子的横坐标与纵坐标之差相等。

- 左下到右上：每个格子的横坐标与纵坐标之和相等。

于是我们可以开两个桶分别统计这两种对角线上，每条对角线上棋子的个数，再根据上面的公式计算答案。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
unordered_map<int,int>p,q;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		p[x-y]++;
		q[x+y]++;
	}
	for(auto it=p.begin();it!=p.end();it++)
	{
		int x=it->second;
		ans+=x*(x-1)/2;
	}
	for(auto it=q.begin();it!=q.end();it++)
	{
		int x=it->second;
		ans+=x*(x-1)/2;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：许多 (赞：0)

做这道题，我们首先要知道，怎么判断两个象在同一对角线。

首先，对角线可以分两类。

![](https://cdn.luogu.com.cn/upload/image_hosting/wk1pz0bn.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/j4jys64o.png)

对于第一种情况，每一个在对角线上的点，它的横坐标与纵坐标的和相等。

对于第二种情况，每一个在对角线上的点，它的横坐标与纵坐标的差相等。

好，到这里，就很好做了，我们维护两个桶，在将一个点加入桶时将 $ans$ 加上当前桶里的值即可。

# 代码

```cpp
#include<cstdio>
#define N 3000
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'&&ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int n,a[N],b[N],ans=0;
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		int x=read(),y=read();
		ans+=a[x+y]+b[x-y+1000];
		a[x+y]++;
		b[x-y+1000]++;
	}
	printf("%d",ans);
	return 0;
}

```


---

## 作者：yangzd (赞：0)

# 题目大意：

在一个 $1000\times1000$ 的国际象棋棋盘上，有 $n$ 个“相”，只要在同一条对角线上的相就能互相攻击，不管中间有没有别的相，求可以互相攻击的相的对数。

# 分析

互相攻击的相满足的条件有两个，坐标 $x+y$ 相等或者 $x-y$ 相等。所以可以按照 $x+y$ 和 $x-y$ 为关键字分别排两次序，相同关键字的 $q$ 个相可以组成 $(1+q-1) \times (q-1)/2$ 对，计算即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct xiang
{
	long long x,y;
	
	bool friend operator<(xiang a,xiang b)
	{
		return a.x-a.y<b.x-b.y;
	}
}a[220000];

struct xiang2
{
	long long x,y;
	
	bool friend operator<(xiang2 a,xiang2 b)
	{
		return a.x+a.y<b.x+b.y;
	}
}b[220000];

long long n;

signed main()
{
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	for(long long i=1; i<=n; i++)
	    cin >> a[i].x >> a[i].y;
	    
	memcpy(b,a,sizeof(b));
	
	long long ans=0;
	
	sort(a+1,a+1+n);
	
	long long ji=0;
	
	a[0].y=2000;
	
	for(long long i=1; i<=n; i++)
	{
		if(a[i].x-a[i].y==a[i-1].x-a[i-1].y)
			ji++;
			
		else
			ji=1;
		
		ans+=(long long)(ji-1);
	}
	
	sort(b+1,b+1+n);
	
	ji=0;
	
	b[0].y=-2000;
	
	for(long long i=1; i<=n; i++)
	{
		if(b[i].x+b[i].y==b[i-1].x+b[i-1].y)
			ji++;
			
		else
			ji=1;
		
		ans+=(long long)(ji-1);
	}
	
	cout << ans << endl;
	return 0;
}

```

---

