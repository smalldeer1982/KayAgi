# Find a Mine

## 题目描述

This is an interactive problem.

You are given a grid with $ n $ rows and $ m $ columns. The coordinates $ (x, y) $ represent the cell on the grid, where $ x $ ( $ 1 \leq x \leq n $ ) is the row number counting from the top and $ y $ ( $ 1 \leq y \leq m $ ) is the column number counting from the left. It is guaranteed that there are exactly $ 2 $ mines in the grid at distinct cells, denoted as $ (x_1, y_1) $ and $ (x_2, y_2) $ . You are allowed to make no more than $ 4 $ queries to the interactor, and after these queries, you need to provide the location of one of the mines.

In each query, you can choose any grid cell $ (x, y) $ , and in return, you will receive the minimum Manhattan distance from both the mines to the chosen cell, i.e., you will receive the value $ \min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|) $ .

Your task is to determine the location of one of the mines after making the queries.

## 说明/提示

In the first test case, we start by querying the upper-left corner $ (1, 1) $ and get the result $ 3 $ , which means that there is a mine on the counter diagonal, and there is no mine above it.

In the image below, each cell contains a number indicating the distance to the blue cell. The green cells are candidates to contain the nearest mine.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9f8890c987cfc62ebf33297af68261e59cb82050.png)Then we ask three cells on that diagonal, and at the last query, we get the result $ 0 $ , which means that a mine is found at the position $ (2, 3) $ .

The second mine was located at the position $ (3, 2) $ .

In the second test case, we start by asking the lower-right corner $ (5, 5) $ , and get the result $ 1 $ , which means that one of the two neighbours contains a mine, let's call it mine $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/529c76a59b6e1128854ef8942281235840d099a4.png)Then we ask cell $ (2, 2) $ . We can see that these green cells don't intersect with the green cells from the first query, so they contain the other mine, let's call it mine $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/759e71e2b3a5d456c063d438414900b4ab40b3f1.png)Query $ 3 $ is cell $ (3, 3) $ . These cells contain mine $ 1 $ , but we still don't know where exactly. Nevertheless, we can determine that the only possible cell for mine $ 2 $ is $ (1, 1) $ , because all other candidates are at a distance closer than $ 3 $ for this query.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9b91f7f88f4e4ce648a34002d2c4a2f09feeedee.png)

## 样例 #1

### 输入

```
2
4 4

3

2

2

0

5 5

1

2

3```

### 输出

```
? 1 1

? 1 4

? 4 1

? 2 3

! 2 3

? 5 5

? 2 2

? 3 3

! 1 1```

# 题解

## 作者：I_will_AKIOI (赞：4)

CF 的第一道通过的交互题。

### 题目大意

在一个 $n\times m$ 的棋盘上有两个地雷，你每次可以询问一个点 $(x,y)$，交互库会计算这个点到这两个地雷的曼哈顿距离，并输出距离中更小的一个。你需要通过**不超过 $4$ 次**询问得出一个地雷的位置。

### 思路

我们设第 $i$ 次的询问结果为 $d_i$。

样例解释非常的良心，已经给出了大致思路。他告诉我们询问点 $(1,1)$ 可以得出其中一个地雷在哪个对角线上。注意这里需要分类讨论：若距离小于 $n$，则对角线的左下方端点为 $(d_1+1,1)$，否则端点为 $(n,d_1+2-n)$。右上角端点同样分讨。设他们为 $x1,y1,x2,y2$。

接下来我们询问两个端点，由于地雷在同一个对角线上，我们可以得出地雷的位置：$\displaystyle(x1-\frac{d_2}{2},y1+\frac{d_2}{2})$ 和 $\displaystyle(x2+\frac{d_3}{2},y2-\frac{d_3}{2})$。

为什么地雷会有两个位置？因为在询问端点的过程中，另外一个不在对角线上的地雷可能会“干扰”询问。也就是说比在对角线上的地雷更近。所以我们还需要进行最后一次询问，判断哪个点才是地雷。（当 $d_4=0$ 时说明是地雷）

### 代码

```
#include<iostream>
using namespace std;
void solve()
{
  int n,m,d[4];
  cin>>n>>m;
  cout<<"? "<<1<<" "<<1<<endl;
  cin>>d[0];
  //第一次询问
  int x1,y1,x2,y2;
  if(d[0]<n) x1=d[0]+1,y1=1;
  else x1=n,y1=d[0]+2-n;
  if(d[0]<m) x2=1,y2=d[0]+1;
  else x2=d[0]+2-m,y2=m;
  //计算出对角线的两个端点
  cout<<"? "<<x1<<" "<<y1<<endl;
  cin>>d[1];
  cout<<"? "<<x2<<" "<<y2<<endl;
  cin>>d[2];
  d[1]/=2;
  d[2]/=2;
  x1-=d[1],y1+=d[1];
  x2+=d[2],y2-=d[2];
  //算出地雷的两个位置
  cout<<"? "<<x1<<" "<<y1<<endl;
  cin>>d[3];
  if(d[3]==0) cout<<"! "<<x1<<" "<<y1<<endl;
  else cout<<"! "<<x2<<" "<<y2<<endl;
  //询问其中一个位置，如果距离为0说明是该点，否则是另一个点
  return;
}
int main()
{
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：ttq012 (赞：4)

考虑询问矩形的四个角，这样不需要麻烦的分类讨论。

首先询问 $(1,1)$ 和 $(1,n)$ 两个角，考虑通过她们直接求出可能为答案的坐标 $(x_1,y_1)$。

然后询问 $(x_1,y_1)$。若回复为 $0$，那么显然 $(x_1,y_1)$ 就是一个答案，直接输出。

否则就询问 $(m,1)$ 并将 $(1,1)$ 和 $(m,1)$ 放为一组，得出坐标 $(x_2,y_2)$。此时 $(x_2,y_2)$ 就一定为一组合法的解，不再需要询问。

该方法最多询问 $4$ 次，可以通过。

---

## 作者：hgckythgcfhk (赞：4)

形式化题意：这是一个交互题，在一张 $n\times m$ 的网格图上，有两个关键点，你可以提出不超过 $4$ 次询问，然后找到其中一个关键点，多测。

其实本题没考任何算法，主要是思路和细节，但不代表在实现上没有任何技巧，比如我刚写完的时候看 CF 的提交记录，看到了一种适用于大部分交互题且非常优雅的实现方式。

我记得有个红题让求曼哈顿距离相等的点集相关的忘了是周长还是面积，由于时间久远，大概是半年前，那个题我找不到了，但并不重要，重要的是做那个题的时候我们通过画图发现，这个曼哈顿距离意义下的圆其实是一个对角线平行于坐标轴的正方形。

看起来这个结论好像没什么用，但是，注意到正方形，我们可以拆成 $4$ 条直线，直线就是一个关键的性质，两个补重合的直线至多有一个交点，这告诉我们可以解方程。

我们把询问看作给定一个“圆心”，然后我们就能知道一个最小的“半径”使得”圆“上有关键点。由于我们很容易就能确定“圆”的大小和位置，也就是说，我们每次询问可以得到一个某个点在某个以 $(a,b)$ 为“圆心”的限制，如果两个“圆”有交点，则**其中一个**交点一定是一个解。

可以看到，**其中一个**是个不太好处理且细节极多的东西，不信你可以实现一下试试，而且这还容易导致进行额外操作去检查到底是哪一个，非常恶心，为了避免这个东西，我的做法是只询问 $(1,1),(1,m),(n,1)$ 这样的好处是每两个之间在网格的合法范围内最多有 $1$ 个交点，询问这 $3$ 个点可以证明至少有 $1$ 个交点。

然后只要解方程解出交点即可。

设交点为 $(x,y)$，$3$ 次询问得到的数为 $a,b,c$。

满足:

$$
\begin{aligned}
\operatorname{dis}[(1,1),(x,y)]=a,\\
\operatorname{dis}[(1,m),(x,y)]=b,\\
\operatorname{dis}[(n,1),(x,y)]=c
\end{aligned}
$$

的其中两个。

要么 $1,2$ 成立，要么 $1,3$ 成立，但不可能 $2,3$ 成立，这个原因不太好语言描述，直接给个图。

![$1,2$ 成立](https://cdn.luogu.com.cn/upload/image_hosting/nyw48hhf.png)

![$1,3$ 成立](https://cdn.luogu.com.cn/upload/image_hosting/nyw48hhf.png)

![$2,3$ 无法同时成立](https://cdn.luogu.com.cn/upload/image_hosting/2rpsbhpa.png)

发现，我们构造不出来一种使得都不成立的设置关键点的方案，因为如果有方案使得这 $3$ 个都无法同时成立，一定不止两个关键点，这个结论的正确性可以这样理解，一个直线上一定至少有一个关键点，如果 $3$ 个直线没有交点，则说明这 $3$ 个直线至少各有一个交点，与题设的两个不符。

这样就做完了，但是，这个题有坑，导致我调了很久，问题就在解方程的地方，我们解出来不一定是整数，要判断一下，这里有两种判断方法，一种是直接根据字面意思判断，这样使得本题可以加强到不超过 $3$ 次，或者 $4$ 次询问找出两个，另一种是直接用 ```int``` 向下取整，用最后一次询问检查一下。

理论上，不用 $4$ 个角也是可做的，但我太菜了没写出来，只会这种最简单的做法。

这是我第一次通过的程序，说实话，实现的比较暴力，并不优雅。

```cpp
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define ll long long
#define void inline void
using namespace std;constexpr unsigned N=1000001;
signed main(){open;int t;cin>>t;while(t--){int n,m;cin>>n>>m;ll x,y,t1,t2;
	cout<<"? "<<1<<' '<<1<<endl;ll ul;cin>>ul;
	cout<<"? "<<1<<' '<<m<<endl;ll ur;cin>>ur;
	cout<<"? "<<n<<' '<<1<<endl;ll dl;cin>>dl;
	t1=ul+2,t2=ur-m+1;x=(t1+t2)/2ll,y=t1-x;
	if(x<=n&&x>=1&&y<=m&&y>=1){  int chk;cout<<"? "<<x<<' '<<y<<endl;cin>>chk;if(chk==0){  cout<<"! "<<x<<' '<<y<<endl;continue;}}
	t1=ul+2,t2=dl-n+1;y=(t1+t2)/2ll,x=t1-y;
	if(x<=n&&x>=1&&y<=m&&y>=1){/*int chk;cout<<"? "<<x<<' '<<y<<endl;cin>>chk;if(chk==0){*/cout<<"! "<<x<<' '<<y<<endl;continue; }
}}

```

后来，我想看看有没有不用 $4$ 个角做的写法，于是我点开了提交记录，发现其他人的程序出奇的一致，~~CF 不罚 CTJ 吗~~，但有个实现的非常好的地方，不仅能把最后的检查写的非常简洁，而且适用于大部分交互题，平时我们交互题做的不多，所以我认为哪怕只是学到这个写法都是有意义的。

大概就是：

```cpp
inline unsigned get(cit x,cit y){cout<<"? "<<x<<' '<<y<<endl;int len;cin>>len;return len;}
```

现给出修改后的完整程序。

```cpp
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define ll long long
#define void inline void
using namespace std;constexpr unsigned N=1000001;
inline unsigned get(cit x,cit y){cout<<"? "<<x<<' '<<y<<endl;int len;cin>>len;return len;}
signed main(){open;int t;cin>>t;while(t--){int n,m;cin>>n>>m;ll x,y,t1,t2;
	ll ul=get(1,1),ur=get(1,n),get(m,1);
	t1=ul+2,t2=ur-m+1;x=(t1+t2)/2ll,y=t1-x;
	if(x<=n&&x>=1&&y<=m&&y>=1&&get(x,y)==0){cout<<"! "<<x<<' '<<y<<endl;continue;}
	t1=ul+2,t2=dl-n+1;y=(t1+t2)/2ll,x=t1-y;
	if(x<=n&&x>=1&&y<=m&&y>=1             ){cout<<"! "<<x<<' '<<y<<endl;continue;}
}}

```

建议大家不要过度参考 CF 的提交记录的解方程部分，因为正常人都不会一下子写出最终的表达式，极其容易写错，我这个做法是观察到未知数的系数为 $1$，先手动移项，再直接接一个很简单的方程，这样常数和码量确实会大几乎可以忽略不计的一点点，但这样做是很自然的，甚至我一遍就解对了。

最后注意一下，一定不要偷懒写个 ```\n```，虽然 ```endl``` 很麻烦，我也不喜欢用，但是交互题要清空缓冲区，用 ```endl``` 其实是最方便的做法。

本题有一定的思维难度，但并不多，没有考任何算法，但非常创新，值得做一下，建议评红或橙。

---

## 作者：Louis_lxy (赞：2)

## 前言
纪念一下第一次做出交互题！

发现题解区好像没有这种做法？那我就来发一篇吧。
## 思路
~~很暴力的做法。~~

由于我数学太蒻了，所以只能想到这种做法。

显然，我们可以将曼哈顿距离转化成圆，那么就是求输入的圆有几个交点。

然后进一步转化，在方格阵（不知道是不是这么叫）上的一个圆其实也相当于一条直线，那么问题就转化成了几条直线求交点。

然后我们就要确定是用几次询问确定可能的点，我选的是 $3$ 次，具体原因如下：
1. 如果询问 $2$ 次，会得到一个有可能的点，但是并不像 $3$ 次那样好理解，还要再次询问得到另外的点，比较麻烦。
2. 询问 $3$ 次，会得到两个可能的点，但是非常好推式子。
3. 询问 $4$ 次就直接确定节点非常难（至少我不会 qaq）。

然后简单想一下发现，绝对值这个东西非常讨厌，想要去掉它，绝对值中的一个数直接设为极大/极小值。询问可以用 $(1,1)$，$(1,m)$，$(n,1)$ 也可以用 $(n,m)$，$(1,m)$，$(n,1)$（或许 $(1,1)$，$(n,m)$，$(1,m)/(n,1)$ 也可以？不过我没试过，感觉也是可以的）。我用的是 $(1,1),(1,m),(n,1)$（当然，用第二组的也可以用类似过程推出结果），显然这样每个已知数都是最大或最小值了，我们就可以直接去掉绝对值，不会去绝对值的建议 bdfs 后再来做。

然后我们就可以列出方程，注意这里的三个方程只需满足 $1$，$2$ 或满足 $1$，$3$ 即可，容易发现不可能满足 $2$，$3$，因为画图可以发现查询 $1$，$m$ 得到的直线不可能与查询 $n$，$1$ 得到的直线相交，他们是平行的（当然也可以重合），原因是得到的直线必然与查询点的非对应的对角线平行。

$$
1:(x-1)+(y-1)=a\\
2:(x-1)+(m-y)=b\\
3:(n-x)+(y-1)=c
$$

然后，我们接着用小学学的等式的性质瞎搞一波，就变成了如下式子（当然你要先会解二元一次方程），斜杠是或不是除号。

$$
x=a+2-y\\
y=\frac{a+m+1-b}{2}/\frac{a+c+3-n}{2}
$$

然后带入两个式子（指求 $y$ 的两个式子），求出必然有一组解成立，否则就没有地雷。但是由于可能有一组方程得到的答案是不同的地雷导致方程不成立，可能解出小于等于 $0$ 的解，所以要特判一下。小于等于 $0$ 的解不能询问！
## 警示后人
由于交互题我们做的少，所以容易有这些问题：
1. 交互题返回给程序的答案不会显示，指在 CF 评测的数据不会显示。
2. 每次询问要刷新缓冲区。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int get(int x, int y)//询问的函数，交互题这样写会使代码更好理解
{
	printf("? %d %d", x, y); cout << endl;
	int ans;
	scanf("%d", &ans);
	return ans;
}

int main()
{
	int t, n, m, a, b, c, x, y, ans;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		if ((n == 1 && m < 3) || (m == 1 && n < 3)) { printf("! 1 1"); cout << endl; continue; }//不知道有没有用的特判
		a = get(1, 1), b = get(1, m), c = get(n, 1);//得到三组答案
		y = (a + m + 1 - b) / 2, x = a + 2 - y;//先解一组方程
		if (y > 0 && x > 0)//如果这组方程成立
		{
			ans = get(x, y);//询问
			if (ans)//如果这组方程不是结果（即使范围对也有可能不成立）
			{
				y = (a + c + 3 - n) / 2, x = a + 2 - y;//解另一组方程
				printf("! %d %d", x, y); cout << endl;//显然另一组方程必然成立，直接输出即可
			}
			else printf("! %d %d", x, y); cout << endl;//成立就直接输出
		}
		else
		{
			y = (a + c + 3 - n) / 2, x = a + 2 - y;//解另一组方程
			printf("! %d %d", x, y); cout << endl;//显然另一组方程必然成立，直接输出即可
		}
	}
}
```
## 后记
这题可能思路主要难点也是不同方法的区别点是想到用几次询问来确定可能的点，不同的数量会造成思路的很大区别。

感觉这题黄？没有特别难吧，比我做任何绿题的思考时间都要短啊。~~大模拟除外~~。这题主要就是因为是交互题才略微难一点吧，其实我感觉橙都可以。~~但是某个题解说的红太夸张了。~~

---

## 作者：luobotianle (赞：1)

首先考虑只有一个地雷的情况。

如果只有一个地雷，我们可以先查出它在哪条对角线上，再查询一次该对角线的端点获取距离，$2$ 次即可完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/jh1s0ul9.png)

如图，查询两个蓝色的位置即可。

但现在有两个地雷，意味着第二次获取到的距离可能会受到另一个地雷的影响，导致获得的距离不对；
![](https://cdn.luogu.com.cn/upload/image_hosting/t721gka4.png)

这时我们查出的距离可能是 $d2$，并不是我们想要的距离。

怎么办？

我们发现，如果我们同时查询这条对角线的两个端点，那么总有一个距离是到在这条对角线上，也就是我们需要的地雷的。

![](https://cdn.luogu.com.cn/upload/image_hosting/5eu8bhi0.png)

对于上图，$d1$ 和 $d3$ 总有一个会被查到。

所以接下来我们要判断 $d2$ 和 $d4$ 这两个距离的干扰。

此时，我们手里有对角线的两个端点 $(x1,y1)$ 和 $(x2,y2)$，以及两个距离，假定它们是 $d2$ 和 $d3$；

那么地雷的可能存在的位置就是 $(x1-\frac{d2}{2},y1+\frac{d2}{2})$ 和 $(x2+\frac{d3}{2},y3-\frac{d3}{2})$，其中有一个是另一个地雷干扰的结果。

所以我们只需要用手里的最后一次查询机会去判断地雷在哪个位置就好了。查询结果是 $0$ 意味着在这里，否则就在另一个位置。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int T;
int n,m,d[105];
inline int get(int x,int y){
	cout<<"? "<<x<<" "<<y<<endl;
	int a;
	cin>>a;
	return a;
}
inline int get(pii a){
	return get(a.first,a.second);
}
void add(pii &a,int x,int y){
	a.first+=x;
	a.second+=y;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		d[1]=get(1,1);
		pii a,b;
		if(d[1]<n)a={d[1]+1,1};
		else a={n,d[1]-n+2};
		if(d[1]<m)b={1,d[1]+1};
		else b={d[1]-m+2,m};
		d[2]=get(a);
		d[3]=get(b);
		d[2]/=2;d[3]/=2;
		add(a,-d[2],d[2]);
		add(b,d[3],-d[3]);
		int f=get(a);
		if(f==0){
			cout<<"! "<<a.first<<" "<<a.second<<endl;
		}
		else{
			cout<<"! "<<b.first<<" "<<b.second<<endl;
		}
		
	}
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

有点坑的题。

## 题意

一个 $n\times m$ 的矩形上有两个地雷，你可以进行不多于 $4$ 次询问。每次询问给出一个点 $(x, y)$，交互库会回答你这个点到两个地雷的曼哈顿距离的较小值。求出其中一个地雷的坐标。

## 思路

注意这个题必须使用一些相对精巧的询问。有一种垃圾的想法是通过一些询问，算出所有可能点对，之后进行 check。这样是错误的，因为可能构造出多个点对符合你的不精巧的询问。

给出一种相对精巧的询问方式。

先询问 $(1, 1)$ 和 $(n, m)$，通过得到的答案可以知道地雷一定在两条直线上。这两条直线可能重合，但是完全不影响做法。

接下来询问 $(n, 1)$，又能得到一条直线。这条直线与之前的两条直线不可能都没有交点。

- 如果只有一个交点，答案就是这个交点；
- 否则有两个交点。询问其中的一个，若得到 $0$，答案就是它；否则就是另一个。

[AC record](https://codeforces.com/contest/1934/submission/252047732)

```cpp
int n, m; vector <pii> edge, dot;

il void solve() {
	read(n, m); edge.clear(); dot.clear();
	cout << "? 1 1" << endl;
	int t = read(); edge.eb(-1, t + 2);
	cout << "? " << n << ' ' << m << endl;
	t = read(); edge.eb(-1, n + m - t);
	cout << "? " << n << " 1" << endl;
	t = read(); edge.eb(1, t - n + 1);
	rep1(i, 0, 1) {
		pii p = edge[i], q = edge[2];
		if ((p.snd - q.snd) & 1) continue;
		int x = (p.snd - q.snd) / (q.fst - p.fst);
		int y = p.fst * x + p.snd;
		if (x >= 1 && x <= n && y >= 1 && y <= m) dot.eb(x, y);
	}
	if (dot.size() == 1) return cout << "! " << dot[0].fst << ' ' << dot[0].snd << endl, void();
	cout << "? " << dot[0].fst << ' ' << dot[0].snd << endl;
	if (read()) cout << "! " << dot[1].fst << ' ' << dot[1].snd << endl;
	else cout << "! " << dot[0].fst << ' ' << dot[0].snd << endl;
}

int main() {
	for (int T = read(); T--; ) solve();
	rout;
}
```

---

## 作者：Elaina_0 (赞：0)

蒟蒻生来通过的第一道交互qwq

AD：[博客喵~](https://www.cnblogs.com/Elaina-0)

## 分析

读题发现样例已经给出了一种明确的思路...

首先询问 $[1,1]$ 可以得出地雷位于哪一条斜线上，

之后两次我们分别询问这条斜线的两个端点，那么我们通过第1、2次或第1、3次询问，必然会在斜线上得到至少一种解，

如果得到了两种解，那么最后一次询问其中一个解是否正确，正确则直接输出，错误则输出另外的一个解。

举个栗子：假设我们现在有两个地雷分别位于 $[4,3]$ 和  $[3,5]$ 的位置上（在图中用 ● 表示）。

![](https://cdn.luogu.com.cn/upload/image_hosting/s53y4p13.png)

第一次询问交互机的回答是 $5$ ，因此我们确定了其中一个地雷所在的斜线位置（在图中用 $\color{red}X$ 表示）。

![](https://cdn.luogu.com.cn/upload/image_hosting/a7jkp27r.png)

接着，我们询问斜线端点的位置，第一次询问靠上的端点，得到的回答为 $1$ ，另一次得到的回答是 $2$ 。

此时我们只能在斜线上确定一个解，因此这个解即为所求。

那如果第二个地雷不在 $[3,5]$ 而在 $[4,5]$ 呢？

那么我们第二次得到的回答也是 $2$ ，这时我们可以在斜线上确定两个解，利用最后一次询问确定就可以啦~


```cpp
int n,m;
int d[5];

void work(){
	int x,y;
	cin>>n>>m;
	
	printf("? 1 1\n");
	cout.flush();
	d[1]=rd;
	if(!d[1]){
		printf("! 1 1\n");
		cout.flush();
		return ;
	}

	y=d[1]+1>m?d[1]+1-m:0;
	printf("? %lld %lld\n",y+1,d[1]+1-y);
	cout.flush();
	d[2]=rd;
	if(!d[2]){
		printf("! %lld %lld\n",y+1,d[1]+1-y);
		cout.flush();
		return ;
	}
	
	x=d[1]+1>n?d[1]+1-n:0;
	printf("? %lld %lld\n",d[1]+1-x,x+1);
	cout.flush();
	d[3]=rd;
	if(!d[3]){
		printf("! %lld %lld\n",d[1]+1-x,x+1);
		cout.flush();
		return ;
	}
	
	if(d[2]&1){
		printf("? %lld %lld\n",(d[1]+1-x)-d[3]/2,x+1+d[3]/2);
	}else{
		printf("? %lld %lld\n",y+1+d[2]/2,(d[1]+1-y)-d[2]/2);
	}
	cout.flush();
	
	d[4]=rd;
	if(!(d[4]+(d[2]&1))){
		printf("! %lld %lld\n",y+1+d[2]/2,(d[1]+1-y)-d[2]/2);
		cout.flush();
	}else{
		printf("! %lld %lld\n",(d[1]+1-x)-d[3]/2,x+1+d[3]/2);
		cout.flush();
	}
}

signed main(){
	int T=rd;
	while(T--){
		work();
	}

	我永远喜欢伊蕾娜！
}
```

---

## 作者：GameFreak (赞：0)

## 前言

本人于省选前一天为蹲点向参赛选手送出祝福，随手开了一局 CF，但是因为写混了两个 case 导致直至第二天早上才调出 C，望各位引以为戒，要打草稿。

## 题意

给出一个 $n\times m$ 的网格，左上角为 $(1,1)$，右下角为 $(n,m)$。交互库隐藏了两个有 mine 的格子 $(x_1,y_1)$ 和 $(x_2,y_2)$。

你每次可以选择一个点 $(x,y)$ 进行询问，交互库返回 $\min\left(|x_1-x|+|y_1-y|,|x_2-x|+|y_2-y|\right)$（即曼哈顿距离的较小值）。

$T$ 组测试，每组测试点给出 $n,m$，需要在不超过 $4$ 次询问中确定一个 mine 的位置。

$1\le T\le 3\times 10^3,2\le n,m\le 10^8$.

## 思路

考虑每次询问可以得到一个环，并且环上一定存在至少一个 mine；特别的，对四个角的询问可以得到一条直线。

于是考虑先问出两条直线，不妨询问 $(1,1)$ 和 $(1,m)$，那么可以发现情况分为三类：

#### Case 1

两条直线恰有一个交点，比如下面这样：

```plain
####*#@###
#####!####
####@#*###
###@###*##
##@#####*#
```

第一是发现交点上面的不能有 mine，所以 mine 只会在下面的“人”字上。

那么此时考虑取这个交点 `!` 对其进行询问。若 `!` 就是一个 mine，则可直接返回，否则说明 mine 一定在去掉交点剩下的两条线段上。

而我们在询问 `!` 时可以得到一个环，而我们同时也知道 mine 一定在环上，所以环和两条直线形成的两个交点必定有至少一个 mine，随便取一个询问即可。

#### Case 2

两条直线完全不交，比如下面这样：

```plain
###!##*###
##@####*##
#@######*#
@########*
##########
```

不难发现分析是一样的，依旧可以通过取 `!` 询问得到环，然后判断环与直线的交点。

#### Case 3

两条直线恰好错开且没有交点，比如下面这样：

```plain
#*?
#@*
@##
```

很容易会想到当作完全不交的情况做，但这样是错的。

因为这个时候直接取 `?` 的位置，如果距离为 $1$ 那么就可能取得第一行的 `*`，而这个位置是“人”字形的上方，不可能有 mine。

因此需要特殊处理，取到正中心的 `@`。

------

观察上面三种 case，不难发现保证正确的关键就在于 mine 不存在于两条直线形成的“人”字形（当然也可能是“八”）上方。

因此从顶端询问，可能的点总会在下方，同时一定交在线上，而不会产生误判。

## Code

```cpp
#include <algorithm>
#include <iostream>
using i32 = int;
void assert(bool check, const char* info = nullptr) {
	if (!check) {
		puts(info), exit(0);
	}
}
void solve() {
	i32 n, m;
	std::cin >> n >> m;
	i32 a, b, c, d;
	std::cout << "? " << 1 << ' ' << 1 << std::endl;
	std::cin >> a;
	std::cout << "? " << 1 << ' ' << m << std::endl;
	std::cin >> b;
	/**
	 * x-1+y-1=a
	 * x+y=a+2
	 * y=a+2-x
	 * (x,a+2-x)
	 *
	 * x-1+m-y=b
	 * x-y=b-m+1
	 * y=x-b+m-1
	 * (x,x-b+m-1)
	 *
	 * x-b+m-1=a+2-x
	 * 2x=a+2+b-m+1
	 */
	i32 x = (a + b - m + 3) / 2, y = a + 2 - x;
	if (x < 1 || x > n || y < 1 || y > m)
		x = std::max(1, a + 2 - m), y = a + 2 - x;	//, puts("114514");
	else if (((a + b - m + 3) & 1))
		++x;
	assert(1 <= x && x <= n && 1 <= y && y <= m, "! 0 0");
	std::cout << "? " << x << ' ' << y << std::endl;
	/**
	 * p-x+y-q=c
	 * q=a+2-p
	 * p-x+y-a-2+p=c
	 * 2p=c+a+x-y+2
	 */
	if (std::cin >> c, c == 0)
		return std::cout << "! " << x << ' ' << y << std::endl, void();
	i32 p = (c + x - y + a + 2) / 2, q = a + 2 - p;
	i32 h = (c + x + y + b - m + 1) / 2, w = -b + m - 1 + h;
	if (((c + x - y + a + 2) & 1) || p < 1 || p > n || q < 1 || q > m) {
		return assert(!((c + x + y + b - m + 1) & 1 || h < 1 || h > n ||
						w < 1 || w > m),
					  "! -1 0"),
			   std::cout << "! " << h << ' ' << w << std::endl, void();
	} else {
		std::cout << "? " << p << ' ' << q << std::endl;
		if (std::cin >> d, d == 0)
			return std::cout << "! " << p << ' ' << q << std::endl, void();
		else
			return assert(!((c + x + y + b - m + 1) & 1 || h < 1 || h > n ||
							w < 1 || w > m),
						  "! -2 0"),
				   std::cout << "! " << h << ' ' << w << std::endl, void();
	}
}
signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	i32 Test = 1;
	std::cin >> Test;
	for (; Test; --Test) solve();
	return 0;
}
```

---

