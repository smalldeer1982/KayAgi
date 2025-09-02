# [ABC248E] K-colinear Line

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_e

座標平面上の $ N $ 個の点が与えられます。 $ 1\leq\ i\leq\ N $ について、$ i $ 番目の点の座標は $ (X_i,\ Y_i) $ です。

座標平面上の直線であって、$ N $ 個の点のうち $ K $ 個以上の点を通るものの個数を求めてください。  
ただし、そのようなものが無数に存在する場合は `Infinity` を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 300 $
- $ \lvert\ X_i\ \rvert,\ \lvert\ Y_i\ \rvert\ \leq\ 10^9 $
- $ i\neq\ j $ ならば $ X_i\neq\ X_j $ または $ Y_i\neq\ Y_j $
- 入力はすべて整数

### Sample Explanation 1

$ x=0 $, $ y=0 $, $ y=x\pm\ 1 $, $ y=-x\pm\ 1 $ の $ 6 $ 本の直線が条件をみたします。 例えば、$ x=0 $ は、$ 1 $, $ 3 $, $ 5 $ 番目の $ 3 $ 個の点を通ります。 よって、$ 6 $ を出力します。

### Sample Explanation 2

原点を通る直線は無数に存在します。 よって、`Infinity` を出力します。

## 样例 #1

### 输入

```
5 2
0 0
1 0
0 1
-1 0
0 -1```

### 输出

```
6```

## 样例 #2

### 输入

```
1 1
0 0```

### 输出

```
Infinity```

# 题解

## 作者：FFTotoro (赞：5)

本题要求确定一共有多少条直线至少经过了 $K$ 个点。

所以，我们首先需要一个判断三点共线的函数；利用相似三角形的原理即可。

```cpp
bool pd(int a,int b,int c){
    return (ay[b]-ay[a])*(ax[c]-ax[a])==(ax[b]-ax[a])*(ay[c]-ay[a]);
}
```

于是，我们可以使用枚举部分时间复杂度为 $O(n^3)$，标记部分时间复杂度 $O(n^4)$ 的的做法：

先枚举两个点（两点确定一条直线），然后再在其它点中看有没有和这两个点共线的。然后统计一下这条直线上一共有多少个点，如果点数大于或等于$K$ 那么答案就加一。

注意，如果一条直线统计完，需要给这条直线中的每两个点打上已判定的标记，避免重复的统计。

本题需要一个特判：如果 $K=1$，那么显然有无数条直线满足要求，输出 `Infinity` 即可。

核心代码：

```cpp
for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
		if(!f[i][j]){
			vector<int> v; v.push_back(i); v.push_back(j);
			for(int x=j+1;x<=n;x++)if(pd(i,j,x))v.push_back(x);
			for(int x=0;x<v.size()-1;x++)for(int y=x+1;y<v.size();y++)f[v[x]][v[y]]=true;
			if(v.size()>=k)c_all++;
		}
```

---

## 作者：VelvetChords (赞：2)

# AT_abc248_e [ABC248E] K-colinear Line
## 0.前言
校内比赛有这道题，虽然分数比较美丽，但仍然来发个题解。

## 1.问题介绍
给定 $n$ 个点，要求找出平面上至少包含 $k$ 个点的直线的数量。如果有无数条直线满足条件，则输出 `Infinity`。

## 2.思路
推公式题。

众所周知，两点确定一条直线（这谁都懂吧）。如果有多个点共线，这些点属于同一条直线。

那这题就很好懂了，就是判断哪些点在同一条直线上一条上。


直线的斜率可以通过两个点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 计算得出：

$$斜率=\frac{y_2 - y_1}{x_2 - x_1}$$
     
通过公式，判断两个点间的斜率是否相等，从而判断这些点是否共线。

但由于平面上有多个点，我们可以枚举每一对点，检查和其他点是否共线。

使用一个二维数组来记录第 $i$ 个点和第 $j$ 个点是否共线，从而避免重复计算。

如果 $k = 1$，意味着所有点都在同一条直线上，任何经过一个点的直线都符合条件，因此应该输出 `Infinity`。

对每对点 $(i, j)$，判断是否存在其他点与这两点共线。如果共线的点数大于等于 $k$，增加答案。

使用动态标记数组可以避免重复计算。

代码的核心公式是通过斜率判断共线性：

$$(y_l - y_j)\times(x_l - x_i) = (y_l - y_i) \times (x_l - x_j)$$

这个公式是通过扩展两点斜率公式得到的，避免了浮点数的误差。

整体时间复杂度为 $O(n^3)$，对于 $n$ 较小的情况可以接受。

## 3.代码
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// 定义结构体Node用于存储坐标点(x, y)
struct Node
{
    ll x, y;
}a[310];// 最多有310个点
// ok数组用于记录哪些点对已经被判断过是否在同一直线上
bool ok[310][310];
int n,k,ans,b[310],cnt=2,len;
// cmp判断三个点是否共线
bool cmp(Node i, Node j, Node k)
{
    return (k.y-j.y)*(k.x-i.x)==(k.y-i.y)*(k.x-j.x);
}
int main()
{
    cin>>n>>k;
    // 任意两点都算，输出Infinity
    if (k == 1)
    {
        cout << "Infinity";
        return 0;
    }
    for(int i=1;i<=n;i++)
        cin>>a[i].x>>a[i].y;
    // 遍历所有的点对，检查每一对点是否能与其他点共线
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            // 如果点对i,j已经检查过，就跳过
            if(!ok[i][j])
            {
                cnt=2; // 计数器，至少包含i和j两个点
                len=0; // b数组的长度，用来存储共线的点
                memset(b,0,sizeof(b)); // 清空b数组
                // 检查其他点是否与i和j共线
                for(int l=1;l<=n;l++)
                {
                    // 跳过点i和点j
                    if(l==i||l==j) continue;
                    // 判断点l是否与i, j共线
                    if(cmp(a[i],a[j],a[l]))
                    {
                        cnt++;// 共线，计数器加1
                        b[len++]=l; // 将共线点l添加到b数组中
                    }
                }
                // 将点i和点j也加入b数组
                b[len++]=i;
                b[len++]=j;
                // 更新ok数组，标记这些点对已经共线
                for(int x= 0;x<len;x++)
                    for (int y=0;y<len;y++)
                        ok[b[x]][b[y]]=true;
                // 共线点数大于等于k，增加答案
                if(cnt>=k) ans++;
            }
        }
    }
    // 输出结果，即符合条件的点对数量
    cout<<ans;
    return 0;
}
```

---

## 作者：迟暮天复明 (赞：2)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16421271.html)

赛时 WA/TLE 共计七次。

题意：平面内有 $N$ 个点，问总计有多少条经过至少 $K$ 个点的直线。

$N\leq300$

-----
首先 $k=1$ 明显答案是 `Infinity`。

否则我做出任意两个点确定的直线解析式。排序后我就知道每一条线出现了几次。那么它所经过的点数就是满足 $X\times(X-1)=T\times2$。这样就做完了。时间复杂度 $O(n^2\log n^2)$。

实现时注意直线的参数约分等细节。并且注意 $X-Y+1=0$ 和 $-X+Y-1=0$ 两个其实是一条直线，需要强制将某个数转成正数以防止错误计算。

[Code](https://paste.ubuntu.com/p/Kr7dsV7VM8/)

---

## 作者：WaterSun (赞：2)

# 思路

首先，我们得清楚如何判断三点共线。

对于每一个点，它的横纵坐标都有这么一个关系：$n \times x + m = y$（其中 $n,m$ 为常数）。

那么，对于三点共线的点来说，$n,m$ 是相同的。因此我们得出三个式子。

$$n \times x_a + m = y_a$$

$$n \times x_b + m = y_b$$

$$n \times x_c + m = y_c$$

我们用二式减去一式，得：$n = \frac{y_b - y_a}{x_b - x_a}$。

用三式减去一式，得：$n = \frac{y_c - y_a}{x_c - x_a}$。

如果这三个点在同一直线上，它们的 $n$ 是相同的。

所以，判断三点共线的条件就是：$\frac{y_b - y_a}{x_b - x_a} = \frac{y_c - y_a}{x_c - x_a}$。

为了避免精度问题，直接改为乘法：$(x_c - x_a) \times (y_b - y_a) = (x_b - x_a) \times (y_c - y_a)$。

然后，我们暴力枚举二个点，再看一下能与这两个点共线的点的数量。

如果大于了 $K$，就将答案加 $1$。

**注：在 $K$ 为 $1$ 的情况下是有无数条直线的。**

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 310;
int n,m,ans;
int x[N],y[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check(int a,int b,int c){//公式 
	return ((x[c] - x[a]) * (y[b] - y[a]) == (x[b] - x[a]) * (y[c] - y[a]));
}

int main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		x[i] = read();
		y[i] = read();
	}
	if (m == 1){//特判 
		puts("Infinity");
		return 0;
	}
	for (re int i = 1;i <= n;i++){//枚举前两点 
		for (re int j = i + 1;j <= n;j++){
			bool falg = true;
			for (re int k = 1;k < j;k++){//算是去重吧，因为我们枚举的点是直线中最低的点，如果有了更低的点说明重复了 
				if (k != i && check(i,j,k)){
					falg = false;
					break;
				}
			}
			if (falg){
				int res = 2;//算共线的数量 
				for (re int k = j + 1;k <= n;k++){
					if (check(i,j,k)) res++;
				}
				if (res >= m) ans++;//判断，更新答案 
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路

我们先来判断无解的情况：学过数学的都知道，两点确定一条直线。也就是说，在 $2 \le k$ 时，是一定有解的，但解不一定正数。所以，在 $k=1$ 时，由于无法确定某一条直线，而过一点又有无数条直线，这就无解。

在 $2 \le k$ 时，$n$ 的范围不大，我们完全可以先确定某两个点，再在剩下的点中枚举，若枚举的这个点与确定的点共线，则该直线穿过的点数增加一。而这里有一个问题，就是我们在确定两个点的时候可能会重复，所以我们还需要开一个标记数组，用来判断任意两个点是否已经匹配过，即这两个点对应的直线是否枚举到了。那么，在找完与每两个点连成的直线经过的所有点后，我们再将这些点中任意两个点进行标记即可。

注：确定任意三点共线的公式：若三点共线，则 $(x_b-x_a) \times (y_c-y_a)-(x_c-x_a) \times (y_b-y_a)-(x_b-x_a) = 0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
const int N=505;
int x[N],y[N];
bool if_k(int a,int b,int c){return ((x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a]))==0;}//判断三点共线 
bool vis[N][N];
int s[N];//用来存某条直线经过的点编号 
int ans;
signed main()
{
	cin>>n>>k;
	if(k==1) return cout<<"Infinity",0;
	for(int i=1;i<=n;i++) 
		cin>>x[i]>>y[i];
	for(int a=1;a<=n;a++)//先确定两个点 
		for(int b=a+1;b<=n;b++)
			if(vis[a][b]==1) continue;//这条直线枚举过了 
			else
			{
				int idx=0;
				s[++idx]=a,s[++idx]=b;
				for(int c=b+1;c<=n;c++)//枚举剩下的点 
					if(if_k(a,b,c)==1) 
						s[++idx]=c;
				for(int i=1;i<=idx-1;i++)//都标记 
					for(int j=i+1;j<=idx;j++)
						vis[s[i]][s[j]]=1;
				if(idx>=k) ans++;//这条直线满足条件	
			}
	return cout<<ans,0;
} 
```


---

## 作者：maziming (赞：1)

### 题目意思：
题目给出了 $n$ 个点，找到其上至少有 $k$ 个点的线。
### 想法：
众所周知，两点确定一条直线，所以，我们找到两个点，再判断哪个点跟这两个点在一条直线上。

那如何判断呢？

只要看点 $a$ 和点 $b$ 组成的直线和 $a$ 和点 $c$ 组成的直线斜率是否相同，所以我们要打一个判断三点共线的函数：

```cpp
bool pd(aa a,aa b,aa c)
{
	if((c.y-b.y)*(c.x-a.x)==(c.y-a.y)*(c.x-b.x))return true;
	return false;
}
```
#### 当 $k$ 等于 $1$ 时记得输出 `Infinity` ！！！

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,k,l[305],ans;
bool s[305][305];
struct aa{
	ll x,y;
}a[305];
bool pd(aa a,aa b,aa c)
{
	if((c.y-b.y)*(c.x-a.x)==(c.y-a.y)*(c.x-b.x))return true;
	return false;
}//判断三点是否共线
int main()
{
	cin>>n>>k;
	if(k==1){cout<<"Infinity";return 0;}//特判
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)//枚举两点
		{
			if(s[i][j]==1)continue;//如果两点已经在之前被标记在一条线上了，跳过
			ll sum=0;//sum用来记下这一条线有几个点
			memset(l,0,sizeof(l));//l用来存储这一条线上的点
			l[++sum]=i,l[++sum]=j;//将i点和j点存储进去
			for(int k=1;k<=n;k++)//枚举第三点
			{
				if(k==i||k==j)continue;//跳过i点和j点
				if(pd(a[i],a[j],a[k]))l[++sum]=k;//如果三点共线，就标记k点
			}
			for(int j=1;j<=sum;j++)
				for(int k=1;k<=sum;k++)
					s[l[j]][l[k]]=1;//将这一条线上的点标记在一条线上了
			if(sum>=k)ans++;//如果这一条线上的点数有k个，就加上
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：tsh_qwq (赞：1)

## 题意：
在 $n$ 个点中找到 $k$ 个可以连成一条**直线**的点。  

## 做法：
首先我们需要一个判断三点共线的函数：
```cpp
bool pd(int a,int b,int c)
{
	if(((x[b]-x[a])*(y[c]-y[a])==(x[c]-x[a])*(y[b]-y[a])))return 1;
	return 0;
}
```
#### 解释一下原理（我看其他题解都没有就写一写）：  
在这里，斜率可以通过两点之间的坐标差来计算。具体来说，计算 $a$ 和 $b$ 之间的斜率，以及 $a$ 和 $c$ 之间的斜率。

- $a$ 和 $b$ 之间的斜率是 $\frac{y_b - y_a}{x_b - x_a}$。
  
- $a$ 和 $c$ 之间的斜率是 $\frac{y_c - y_a}{x_c - x_a}$。

如果三点共线，那么这两条线段的斜率应该相等。

ok，现在就十分的简单了，其他题解都讲得比较清楚了，就是枚举两个点，再寻找其他共线的点，在标记一下就可以了。 

**一定要特判 $k = 1$**。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int x[502],y[502];
bool b[502][502];
int s[502];
int ans;
bool pd(int a,int b,int c)
{
	if(((x[b]-x[a])*(y[c]-y[a])==(x[c]-x[a])*(y[b]-y[a])))return 1;
	return 0;
}
signed main()
{
	cin>>n>>k;
	if(k==1)
	{
		cout<<"Infinity";
		return 0;
	}
	for(int i=1;i<=n;i++) 
	{
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(b[i][j]==1)continue;
			else
			{
				int qwq=1;
				s[qwq]=i;
				qwq++;
				s[qwq]=j;
				for(int xx=j+1;xx<=n;xx++)
				{
					if(pd(i,j,xx))
					{
						qwq++;
						s[qwq]=xx;
					}
				}
				for(int xx=1;xx<=qwq;xx++)
				{
					for(int yy=xx+1;yy<=qwq;yy++)
					{
						b[s[xx]][s[yy]]=1;
					}
				}
				if(qwq>=k)ans++;
			}
		}
	}
	cout<<ans;
	return 0; 
}
```

---

## 作者：__sunshao321__ (赞：0)

## 题目大意：
在平面直角坐标系上有 $N$ 个点，每个坐标分别为（$xi$，$yi$），现在要求出有多少条**直线**至少经过了 $K$ 个点。

## 分析：

### 情况 1（$K$ 等于一时）：

当 $K$ 等于一时，直接输出 $\texttt{Infinity}$ 就可以了，因为经过一个点的直线有无数条。

### 情况 2（$K$ 不等于一时）：
首先，我们要知道一个叫[**斜率**](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111?fr=ge_ala)的东西。

然后，我们会发现：

设有三个点 $A$，$B$，$C$，若点 $A$ 和点 $B$ 连成的**线段**的斜率与点 $A$ 和点 $C$ 连成的**线段**的斜率**相等**，那么这里三个点就一定在同一条**直线**上。

知道了这个，就非常简单了，像其他题解说的一样，枚举两个点，再寻找其他**共线**的点，最后**标记**一下就可以了。

## 代码：

```cpp
//本人码风有点丑，勿喷
#include<bits/stdc++.h>
using namespace std;
int n,k;
int x[502],y[502];
bool b[502][502];
int s[502];
int ans;
bool pd(int a,int b,int c){
	return (((x[b]-x[a])*(y[c]-y[a])==(x[c]-x[a])*(y[b]-y[a])));
}
int main(){
	cin>>n>>k;
	if(k==1){
		cout<<"Infinity";
		return 0;
	}
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(b[i][j]==1) continue;
			else{
				int w=1;
				s[w]=i;
				w++;
				s[w]=j;
				for(int xx=j+1;xx<=n;xx++){
					if(pd(i,j,xx)){
						w++;
						s[w]=xx;
					}
				}
				for(int xx=1;xx<=w;xx++)
					for(int yy=xx+1;yy<=w;yy++)
						b[s[xx]][s[yy]]=1;
				if(w>=k) ans++;
			}
		}
	}
	cout<<ans;
	return 0; 
}
```

---

## 作者：I_Like_Play_Genshin (赞：0)

小清新简单数学题

## Solution

首先，我们应该枚举两个点，因为两点确定一条直线。

然后，我们应该枚举所有的点，检查这三个点是否共线，如果是，那么计数变量加一。

最后判断这个变量是否大于 $K$ 即可。

如何判断三点共线？

> 运用直线的斜率，我们可以知道，如果两条直线的斜率相等，那么两条直线相等
>
> 我们设三个点分别为 $p1,p2,p3$
> 那么我们可以求出 $p1,p2$ 和 $p2,p3$ 的斜率
>
> 那么这两条斜率分别是 $\dfrac{p1_y-p2_y}{p1_x-p2_x}$ 和 $\dfrac{p2_y-p3_y}{p2_x-p3_x}$，但是因为可能会有精度误差，所以我们要设置一个 $eps$ 来判断两个数是或否相等

## Code 
三点共线：
```cpp
struct Point {
  double x, y;
} p[kMaxN];

double Slope(int a, int b) {
  return (p[a].y - p[b].y) / (p[a].x - p[b].x);
}

bool C(int x, int y, int z) {
  return abs(Slope(x, y) - Slope(y, z)) <= eps;
}
```

---

