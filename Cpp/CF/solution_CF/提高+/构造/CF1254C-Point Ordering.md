# Point Ordering

## 题目描述

This is an interactive problem.

Khanh has $ n $ points on the Cartesian plane, denoted by $ a_1, a_2, \ldots, a_n $ . All points' coordinates are integers between $ -10^9 $ and $ 10^9 $ , inclusive. No three points are collinear. He says that these points are vertices of a convex polygon; in other words, there exists a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ such that the polygon $ a_{p_1} a_{p_2} \ldots a_{p_n} $ is convex and vertices are listed in counter-clockwise order.

Khanh gives you the number $ n $ , but hides the coordinates of his points. Your task is to guess the above permutation by asking multiple queries. In each query, you give Khanh $ 4 $ integers $ t $ , $ i $ , $ j $ , $ k $ ; where either $ t = 1 $ or $ t = 2 $ ; and $ i $ , $ j $ , $ k $ are three distinct indices from $ 1 $ to $ n $ , inclusive. In response, Khanh tells you:

- if $ t = 1 $ , the area of the triangle $ a_ia_ja_k $ multiplied by $ 2 $ .
- if $ t = 2 $ , the sign of the cross product of two vectors $ \overrightarrow{a_ia_j} $ and $ \overrightarrow{a_ia_k} $ .

Recall that the cross product of vector $ \overrightarrow{a} = (x_a, y_a) $ and vector $ \overrightarrow{b} = (x_b, y_b) $ is the integer $ x_a \cdot y_b - x_b \cdot y_a $ . The sign of a number is $ 1 $ it it is positive, and $ -1 $ otherwise. It can be proven that the cross product obtained in the above queries can not be $ 0 $ .

You can ask at most $ 3 \cdot n $ queries.

Please note that Khanh fixes the coordinates of his points and does not change it while answering your queries. You do not need to guess the coordinates. In your permutation $ a_{p_1}a_{p_2}\ldots a_{p_n} $ , $ p_1 $ should be equal to $ 1 $ and the indices of vertices should be listed in counter-clockwise order.

## 说明/提示

The image below shows the hidden polygon in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254C/662320cdf58665333639b68f5fe0cd63c31bc0cd.png)The interaction in the example goes as below:

- Contestant reads $ n = 6 $ .
- Contestant asks a query with $ t = 1 $ , $ i = 1 $ , $ j = 4 $ , $ k = 6 $ .
- Jury answers $ 15 $ . The area of the triangle $ A_1A_4A_6 $ is $ 7.5 $ . Note that the answer is two times the area of the triangle.
- Contestant asks a query with $ t = 2 $ , $ i = 1 $ , $ j = 5 $ , $ k = 6 $ .
- Jury answers $ -1 $ . The cross product of $ \overrightarrow{A_1A_5} = (2, 2) $ and $ \overrightarrow{A_1A_6} = (4, 1) $ is $ -2 $ . The sign of $ -2 $ is $ -1 $ .
- Contestant asks a query with $ t = 2 $ , $ i = 2 $ , $ j = 1 $ , $ k = 4 $ .
- Jury answers $ 1 $ . The cross product of $ \overrightarrow{A_2A_1} = (-5, 2) $ and $ \overrightarrow{A_2A_4} = (-2, -1) $ is $ 1 $ . The sign of $ 1 $ is $ 1 $ .
- Contestant says that the permutation is $ (1, 3, 4, 2, 6, 5) $ .

## 样例 #1

### 输入

```
6

15

-1

1```

### 输出

```
1 1 4 6

2 1 5 6

2 2 1 4

0 1 3 4 2 6 5```

# 题解

## 作者：Falashiro (赞：5)

前置知识：向量与叉积。

考虑对三角形面积的询问有什么用。

然后发现，对于一条固定的线段，由于没有点之间的确切的距离，以这条线段为一边的三角形的面积可以转化为另一个顶点到这条线段所在直线的距离（即这个三角形的高）。

于是，对于询问 $1\ i\ j\ k$ ，当 $i,\ j$ 固定时，这个询问转化为询问点 $k$ 到直线 $A_iA_j$ 的距离。

对于由 $2$ 个在凸包上相邻的点连接组成的直线，其他点按逆时针排序后到这条直线的距离显然是先变大再变小，于是只要找到那个离这条直线最远的点，通过询问 $\vec{A_iA_j}\times\vec{A_iA_k}$ 的正负判断在其他点在这个点的哪一边，然后两边分别按到直线的距离排序即可得到答案，要注意排序的方式。

以上操作需要进行 $2n-4$ 次询问，还剩 $n+4$ 次询问，只需要在 $n+4$ 次询问内找到任意 $2$ 个在凸包上相邻的点即可。

可以钦定其中一个点是 $A_1$ ，然后通过询问 $\vec{A_1A_j}\times\vec{A_1A_k}$ 的正负就能很容易地求出一个与 $A_1$ 相邻的点，这一步需要询问 $n-2$ 次。

于是通过 $3n-6$ 次询问就能求出答案。

代码实现难度不高，我自认为自己代码可读性挺高的。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1005
int n;
struct node{
	int s,a,pos;
}t[N];
bool cmp(node x,node y){
	if(x.a<y.a)return 1;
	if(x.a>y.a)return 0;
	if(x.a==1)return x.s>y.s;
	return x.s<y.s;
}
signed main(){
	scanf("%lld",&n);
	int maxn=-1,x=2,y;
	for(int i=1;i<=n;i++)
		t[i].pos=i;
	for(int i=3;i<=n;i++){
		printf("2 1 %lld %lld\n",x,i);
		fflush(stdout);
		scanf("%lld",&y);
		if(y==1)x=i;
	}
	for(int i=2;i<=n;i++){
		if(i==x)continue;
		printf("1 1 %lld %lld\n",x,i);
		fflush(stdout);
		scanf("%lld",&t[i].s);
		if(t[i].s>maxn)maxn=t[i].s,y=i;
	}
	x=y;
	for(int i=2;i<=n;i++){
		if(i==x)continue;
		printf("2 1 %lld %lld\n",x,i);
		fflush(stdout);
		scanf("%lld",&t[i].a);
	}
	sort(t+1,t+n+1,cmp);
	printf("0 1 ");
	for(int i=1;i<=n;i++)
		if(t[i].pos!=1)printf("%lld ",t[i].pos);
	return 0;
}
```

---

## 作者：Mine_King (赞：3)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/CF1254C.html)

感谢~~小笼包~~凸包之神 djwj223 提供的思路。

## Problem

[CF1254C Point Ordering](https://www.luogu.com.cn/problem/CF1254C)

**题目大意：**

**交互题**，有一个由 $n$ 个顶点组成的没有三点共线的凸包，每次可以有两种询问：

- 第一种询问三个点，返回这三个点组成的三角形的面积的 $2$ 倍。
- 第二种询问三个点 $A_i,A_j,A_k$，返回 $\overrightarrow{A_iA_j} \times \overrightarrow{A_iA_k}$ 的正负。

要求在 $3n$ 次询问后从 $1$ 开始逆时针输出点的编号。如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254C/662320cdf58665333639b68f5fe0cd63c31bc0cd.png)

应该输出 `0 1 3 4 2 6 5`。

## Solution

考虑第二种询问相当于询问 $A_k$ 在 $A_iA_j$ 的左侧（正）还是右侧（负）。

然后考虑钦定两个点，发现其他的点与这两个点的询问可以求出他们构成的三角形的高（以钦定的两个点连成的线段为底）。

![](https://images.cnblogs.com/cnblogs_com/mk-oi/1842536/o_220923083632_QQ截图20220923163423.png)

于是就有这样一个想法：  
任意找两个点，然后用 $n-2$ 次询问得到其他点在左侧还是右侧。再使用 $n-2$ 次询问得到其他点到直线的距离的相对大小。容易发现直线切割后的两半部分都依然是凸包，所以点到直线的相对大小必定是先增大再减小。  

接下来的问题就是对于每一部分确定哪些在左侧，哪些在右侧。  
一个比较容易想到的做法是找到距离最大的点，然后用操作 $2$ 区分点在左侧还是右侧。然后对于右侧从小到大排序，左侧从大到小排序。

![](https://images.cnblogs.com/cnblogs_com/mk-oi/1842536/o_220923084658_QQ%E6%88%AA%E5%9B%BE20220923164543.png)

由于两部分都会取出一个顶点，再去掉最初钦定的两个点，要对其余的每个点进行询问，所以需要 $n-4$ 次询问。

但是最高点可能有两个，不过手玩一下就会发现没什么问题。

总询问次数 $n-2+n-2+n-4=3n-8$，但是当最初选择的两个点相邻的时候会变成 $n-2+n-2+n-3=3n-7$。

还有不懂的可以看代码：

## Code

```cpp
//Think twice,code once.
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,p;
long long mx;
vector<pair<long long,int> >r,l,a1,a2;
vector<int>ans;
int main()
{//钦定最初的两个点1 2
	scanf("%d",&n);
	for(int i=3;i<=n;i++)
	{
		printf("2 1 2 %d\n",i);fflush(stdout);
		int x;scanf("%d",&x);
		if(x==-1) r.emplace_back(0,i);
		else l.emplace_back(0,i);
	}//区分左右侧
	ans.push_back(1);
    //先处理右侧
	for(int i=0;i<(int)r.size();i++)
	{
		printf("1 1 2 %d\n",r[i].second);fflush(stdout);//询问点到直线的距离
		scanf("%lld",&r[i].first);
		if(r[i].first>mx) mx=r[i].first,p=r[i].second;//记录最高点
	}
	for(auto i:r)
	{
		if(i.second==p) continue;
		printf("2 1 %d %d\n",p,i.second);fflush(stdout);//判断在最高点左侧还是右侧
		int x;scanf("%d",&x);
		if(x==-1) a1.push_back(i);
		else a2.push_back(i);
	}
	sort(a1.begin(),a1.end());sort(a2.begin(),a2.end());reverse(a2.begin(),a2.end());//右侧从小到大，左侧从大到小
	for(auto i:a1) ans.push_back(i.second);
	if(p) ans.push_back(p);
	for(auto i:a2) ans.push_back(i.second);
	ans.push_back(2);
	p=mx=0;a1.clear();a2.clear();
    //处理左侧
	for(int i=0;i<(int)l.size();i++)
	{
		printf("1 1 2 %d\n",l[i].second);fflush(stdout);//同上
		scanf("%lld",&l[i].first);
		if(l[i].first>mx) mx=l[i].first,p=l[i].second;//同上
	}
	for(auto i:l)
	{
		if(i.second==p) continue;
		printf("2 1 %d %d\n",p,i.second);fflush(stdout);//同上
		int x;scanf("%d",&x);
		if(x==-1) a1.push_back(i);
		else a2.push_back(i);
	}
	sort(a1.begin(),a1.end());sort(a2.begin(),a2.end());reverse(a2.begin(),a2.end());//同上
	for(auto i:a1) ans.push_back(i.second);
	if(p) ans.push_back(p);
	for(auto i:a2) ans.push_back(i.second);
	printf("0 ");
	for(auto i:ans) printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：Imakf (赞：3)

Div2F 还是比较需要思维力的，思维好的同学估计做的比 E 快。

**本题解讲解如何求出顺时针顺序，若要求出逆时针顺序，直接逆序输出即可。**

由于题目中的**点**的命名过于鬼畜，本题解中用 $A_1,A_2,...,A_n$ 代替。

## 凭空多出的条件

我们不如先假设，如果我们**已经找到一对相邻的顶点** $A_xA_y$，比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/akg24gvy.png)

举个例子：我们找到了 $A_3A_4$ 这对相邻的顶点。

如果我们用 $1$ 操作去检查以 $A_3A_4$ 为底边的所有三角形的面积，实际上我们会得到所有点到 $A_3A_4$ 这条直线的距离比例。也就是知道谁离 $A_3A_4$ 更近或更远。

我们从 $A_3$ 开始，按顺时针查看每一个点到 $A_3A_4$ 的距离，发现趋势是：**先变大，后变小**。如果看成是函数的话，则是单峰函数。

![](https://cdn.luogu.com.cn/upload/image_hosting/fijmf1qu.png)

我们就**按到** $A_3A_4$ **距离从小到大枚举每一个点**，并判断该点应该位于函数的左侧（单调递增区间）还是右侧（单调递减区间）。判断这个可以用操作 $2$ 完成。

我们对左侧区间维护一个**双端队列**，对于右侧区间维护一个栈。我们初始把最近的点，加入左侧的队列尾部中。

因为在凸包上行走，永远是向内侧拐弯，所以如果 $A_x,A_y,
A_z$ 是三个相邻的点，且按顺时针排序，那么必然有 $\overrightarrow{A_xA_y} \times \overrightarrow{A_xA_z}<0$。

对于下一个点 $A_z$，我们检查队列尾部的点 $A_y$，是否满足 $\overrightarrow{A_3A_y} \times \overrightarrow{A_3A_z}<0$，也就是进行 $2$ 操作。如果满足，那么当前选中的点的顺序**暂且**可以构成凸包，直接把 $A_z$ 丢入队列末尾 ；反之不行，那么 $A_y$ 必然不在左侧队列，而应该在右侧栈中。于是把它从队列尾部弹出，压入右侧栈顶，最后再把 $A_z$ 丢入队列末尾。接着重复上述操作直到所有除了 $3,4$ 的点都入栈或入队列。

最后按顺序先遍历左侧队列的元素，再遍历右侧栈中元素即为答案。

按照上述算法，我们只需 $2n-4$ 次询问就可以知道答案，但**前提是我们找到了一对相邻的顶点。**

而因为我太菜，实在想不到 $n$ 次以内找相邻顶点的方法，所以只能另辟蹊径。

## 蹊径

如果我们不能找到相邻顶点，我们干脆就**不要求它们相邻**就好了嘛！显然，多数情况下，我们选出的这两个顶点组成的线段会把凸包分割为两个子凸包。如图，我们选中了 $A_1A_2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/eawxobju.png)

此时的 $A_1A_2$ 有个非常美妙的性质：如果把两个子凸包分别拿出来看，那么 $A_1A_2$ 在凸包中**一定是相邻的两个顶点**！所以依然可以使用上文那个算法！我们唯一的工作变成了:**在** $n+4$ **次操作内得知每个点在** $A_1A_2$ **的哪一侧**。这直接用操作 $2$ 询问 $\overrightarrow{A_1A_2} \times \overrightarrow{A_1A_i}$ 就好了！只需 $n-2$ 次！

总共只需要 $3n-6$ 次询问！

```cpp
#include <iostream>
// 代码是求逆时针顺序的
#define rg register
#define MX (1000 + 4)
#define ll long long
using namespace std;

struct Triangle{
	ll S ,ind;
	bool operator <(const Triangle& B)const{return S < B.S;}
}T[MX];
vector<Triangle> pt[2];
deque<int> Ans;
stack<int> Tmp;

int main(){
	int n;
	cin >> n;
	for(rg int i = 3 ; i <= n ; ++i){
		cout.flush() << "1 1 2 " << i << "\n";
		cin >> T[i].S;
		T[i].ind = i;
		cout.flush() << "2 1 2 " << i << "\n";
		int pos;
		cin >> pos;
        // 按点 i 在 A1A2 的哪一侧进行分类
		if(pos > 0)	pt[0].push_back(T[i]);
		else pt[1].push_back(T[i]);
	}
    // 按三角形面积排序
	sort(pt[0].begin() ,pt[0].end());
	sort(pt[1].begin() ,pt[1].end());
	if(!pt[0].empty())	Ans.push_back(pt[0][0].ind);
	for(int i = 1 ,pos ; i < (int)pt[0].size() ; ++i){
		cout.flush() << "2 1 " << pt[0][i].ind << " " << Ans.back() << "\n";
		cin >> pos;
		if(pos < 0){
			Tmp.push(Ans.back());
			Ans.pop_back();
		}
		Ans.push_back(pt[0][i].ind);
	}
	while(!Tmp.empty()){
		Ans.push_back(Tmp.top());
		Tmp.pop();
	}
	
	Ans.push_back(2);
	if(!pt[1].empty())	Ans.push_back(pt[1][0].ind);
	for(int i = 1 ,pos ; i < (int)pt[1].size() ; ++i){
		cout.flush() << "2 2 " << pt[1][i].ind << " " << Ans.back() << "\n";
		cin >> pos;
		if(pos < 0){
			Tmp.push(Ans.back());
			Ans.pop_back();
		}
		Ans.push_back(pt[1][i].ind);
	}
	while(!Tmp.empty()){
		Ans.push_back(Tmp.top());
		Tmp.pop();
	}
	cout.flush() << "0 1 ";
	while(!Ans.empty()){
		cout.flush() << Ans.back() << " ";
		Ans.pop_back();
	}
	return 0;
}
```

~~这是我CF上做的第一道交互~~

---

## 作者：_ReClouds_ (赞：2)

首先，我们观察询问次数限制：$n*3$ 次。

通过这个，我们大概可以受到一点启发：整个算法会分三步走，每个流程的询问都是 $\mathcal{O}(n)$ 的。

其次，我们观察两种询问：

1.   询问三角形的面积；
2.   询问向量叉积的符号。

我们先来看看，第二种询问有什么用呢？

因为所有点都在凸包上，所以不必担心两个向量不在同一象限的问题。

由此，我们可以使用第二种询问获得两个向量的**相对位置**信息。

这样我们就得到了一个思路：

-   我们可以用 $\mathcal{O}(n)$ 次询问找到凸包上的一条边。

而第一种询问又有什么用呢？

回想**旋转卡壳**寻找**对踵点**的过程：每次对于一条边，我们在凸包上找出一点，使其与该边组成的**三角形面积最大**。

这个思路可不可以用于此呢？当然可以！

于是我们又得到了一个思路：

-   如果我们已经找出了凸包上找到了一条边，那么我们可以用 $\mathcal{O}(n)$ 次询问找出它的对踵点。

所以，我们可以先求出点 $1$ 在逆时针顺序上的下一个点，然后对于这条边求出其对踵点。

如果跑一遍上述的算法，询问次数是不超过 $2*n$ 的（准确的次数为 $2*n - 4$）。

同时，我们可以得到**这条边和每一个点组成的三角形面积**，并且可以得到它们互相之间的大小关系。

它们又有什么用呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/lko9kv58.png)

如图，假设凸包上该边的对踵点为点 $B$，同时存在点 $A,C$ 和边 $f, g$，不存在边 $h$。

如果我们把点 $B$ 删除，连同边 $f, g$ 一起去掉并连上边 $h$，那么点 $A,C$ 都有可能成为该边的**新对踵点**。

所以，我们可以将每个点和其对应的三角形面积打包后，以后者为关键字从大到小排序，然后依次扫描它们。

每一次扫描的实质是**以原对踵点为基础**，并**不断地加入点和边**以维护这个“连通块”。

显然，每次加入进来的边都是凸包上的边。所以，我们只要用合理的方式维护这个结构即可。

如何维护？

可以发现，如果把这个结构展开（即铺成一条线），那么每次操作都只会在原结构的基础上往线段**两端**加点和边。

“两端”意味着我们仅需判断**向量之间的相对位置**，这样就可以用第一种询问做了，配合上双端队列维护即可。

具体地，我们可以将点 $1$ 向原对踵点连接形成一个向量，同时将点 $1$ 向扫描到的点连接形成另一个向量，然后用第一种询问判断它们的相对位置即可。这一步也会有 $\mathcal{O}(n)$ 次询问，更准确地说，一共有 $n - 3$ 次。

总的询问次数为 $3 * n - 7$ 次，可以无压力通过。

可能会存在一些细节，但是由于凸包结构的优美性质，这些细节都可以用很简便的方法完美处理。

最后贴上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<deque>

#define MAXN 1005

using LL = long long;
using namespace std;

int n, nxt1, len;

struct Triangle
{
	int idx;
	LL S;

	bool operator < (const Triangle &t) const
	{
		return S > t.S;
	}
} t[MAXN];

int main()
{
	scanf("%d", &n);
	nxt1 = 2;
	for(register int i = 3; i <= n; i++)
	{
		printf("2 1 %d %d\n", nxt1, i);
		fflush(stdout);
		int res; scanf("%d", &res);
		if(res == -1) nxt1 = i; 
	}
	for(register int i = 2; i <= n; i++)
	{
		if(i == nxt1) continue;
		t[++len].idx = i;
		printf("1 1 %d %d\n", nxt1, i);
		fflush(stdout);
		scanf("%lld", &t[len].S);
	}
	sort(t + 1, t + len + 1);
	deque<int> ans;
	ans.push_back(t[1].idx);
	for(register int i = 2; i <= len; i++)
	{
		printf("2 1 %d %d\n", t[1].idx, t[i].idx);
		fflush(stdout);
		int res; scanf("%d", &res);
		if(res == 1) ans.push_front(t[i].idx);
		else ans.push_back(t[i].idx);
	}
	printf("0 1 %d", nxt1);
	for(register int i = 1; i <= len; i++)
	{
		printf(" %d", ans.back());
		ans.pop_back();
	}
	putchar('\n');
	fflush(stdout);
	return 0;
}
```

---

## 作者：qianyuzhe (赞：2)

## 题意简述

给定一个凸包的点数，每次可以询问由三个点围成的三角形面积的两倍或以某个点为起点的两个不同向量的叉积的正负性，要求在不多于 $3n$ 次询问后从 $a_1$ 开始逆时针输出凸包的点的编号。

## 题目分析

由于答案与点的具体坐标无关，我们不妨以 $a_1$ 为原点，$a_2$ 为 $(1,0)$ 建立平面直角坐标系。

考虑先将剩余点分为 $y>0$ 和 $y<0$ 的两部分，注意到操作二实际上是在判定直线 $a_ia_j$ 和 $a_ia_k$ 斜率的大小关系，因此对于 $i\in[3,n]$ 我们依次询问 `2 1 2 i`，若为 $1$ 则 $y_i>0$，否则 $y_i<0$，共 $n-2$ 次询问。

考虑确定除 $1,2$ 外所有点的具体坐标。对于 $i\in[3,n]$ 我们依次询问 `1 1 2 i`即可得到 $y_i$ 的绝对值，结合刚才得到的结果即可得出 $y_i$，共 $n-2$ 次询问。

现在，我们可以找出所有点中纵坐标最小和最大的点，分别记为 $L,R$，若 $L,R$ 均大于 $2$，则最终答案必为 $1\dots L\dots2\dots R\dots$。

考虑以 $1,L,2,R$ 为边界将点分为四个部分。我们对于 $i\in\{i|y_i<0\land i\not=L\}$ 依次询问 `2 1 L i`，对于 $i\in\{i|y_i>0\land i\not=R\}$ 依次询问 `2 1 R i`，即可划分出四个点集，共 $n-4\sim n-2$ 次询问。

最后，我们对于以 $1,L$ 为边界的部分按 $y_i$ 降序排序并输出，对于以 $L,2$ 为边界的部分按 $y_i$ 升序排序并输出，对于以 $2,R$ 为边界的部分按 $y_i$ 升序排序并输出，对于以 $R,1$ 为边界的部分按 $y_i$ 降序序排序并输出，记得前面还要输出一个 `0`。

不难看出，我们实际上运用了 Andrew 算法的思想，将原点集分为左下凸壳、右下凸壳、右上凸壳、左上凸壳四个部分，分别以纵坐标为关键字排序输出。

总询问次数 $3n-8\sim 3n-6$，时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
long long n,s,i,l,r,y[1005];
vector<long long>v1,v2,v3,v4;
bool cmp(long long a,long long b){return y[a]<y[b];}
bool CMP(long long a,long long b){return y[a]>y[b];}
int main(){
	cin>>n;
	for(i=3;i<=n;i++){
		cout<<"2 1 2 "<<i<<endl;//判纵坐标正负
		cin>>y[i];
		cout<<"1 1 2 "<<i<<endl;//求纵坐标绝对值
		cin>>s;
		y[i]*=s;
	}
	for(l=r=i=1;i<=n;i++){//求L,R 
		if(y[i]<y[l])l=i;
		if(y[i]>y[r])r=i;
	}
	for(i=1;i<=n;i++){
		if(i!=l&&y[i]<0){//下方点分类 
			cout<<"2 1 "<<l<<' '<<i<<endl; 
			cin>>s;
			if(s<0)v1.push_back(i);
			else v2.push_back(i);
		}
		if(i!=r&&y[i]>0){//上方点分类
			cout<<"2 1 "<<r<<' '<<i<<endl;
			cin>>s;
			if(s<0)v3.push_back(i);
			else v4.push_back(i);
		}
	}
	sort(v1.begin(),v1.end(),CMP);
	sort(v2.begin(),v2.end(),cmp);
	sort(v3.begin(),v3.end(),cmp);
	sort(v4.begin(),v4.end(),CMP);
	cout<<"0 1";//输出 
	for(i=0;i<v1.size();i++)if(v1[i]>2)cout<<' '<<v1[i];
	if(l>2)cout<<' '<<l;
	for(i=0;i<v2.size();i++)if(v2[i]>2)cout<<' '<<v2[i];
	cout<<" 2";
	for(i=0;i<v3.size();i++)if(v3[i]>2)cout<<' '<<v3[i];
	if(r>2)cout<<' '<<r;
	for(i=0;i<v4.size();i++)if(v4[i]>2)cout<<' '<<v4[i];
	return cout<<endl,0;
}
```

---

## 作者：ifffer_2137 (赞：1)

~~终于有一次，几乎做出一道非传统题。~~
### 题意
有一个 $n$ 个点组成的凸包，每次询问可以问 $3$ 个点形成的三角形面积，或者两个同起点向量的叉积正负号，让你在 $3n$ 次询问内还原凸包上点编号的逆时针顺序。
### 分析
先说我一眼秒了的后两步。

问三角形面积数值卵用没有，想办法在大小关系上搞点性质。假设我们找到两个相邻的点，固定为底，我们把其它所有点问一圈，容易发现得到的面积序列是合唱队形（底一定，高先升后降）。这样从最高点切开，通过叉积正负性，把其它点分到两侧即可。这里用了 $2n$ 次左右。

然后我们只要用 $n$ 次左右搞出随便两个相邻点就好了。这里我就比较唐了，一直想用三角形面积结果卡了半天。其实钦定一个，用叉积问一圈，找一个跟其它比都是顺时针的就行了。

于是就做完了。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e3+5;
int n,x,mx;
int s[maxn];
vector<pii> v[2];
int ask(int t,int i,int j,int k){
	cout<<t<<' '<<i<<' '<<j<<' '<<k<<'\n';
	fflush(stdout);
	return read();
}
void reply(){
	cout<<0<<' ';
	cout<<1<<' '<<x<<' ';
	for(pii i:v[0]) cout<<i.sec<<' ';
	cout<<mx<<' ';
	for(pii i:v[1]) cout<<i.sec<<' ';
	cout<<'\n';
	fflush(stdout);
}
signed main(){
	n=read();
	x=2;
	for(int i=3;i<=n;i++) if(ask(2,1,x,i)==-1) x=i;
	for(int i=2;i<=n;i++) if(i^x) s[i]=ask(1,1,x,i),mx=(s[i]>s[mx]?i:mx);
	for(int i=2;i<=n;i++) if((i^x)&&(i^mx)){if(ask(2,1,mx,i)==-1) v[0].eb(mkpr(s[i],i)); else v[1].eb(mkpr(s[i],i));}
	sort(v[0].begin(),v[0].end());sort(v[1].begin(),v[1].end(),[](pii x,pii y){return x>y;});
	reply();
	return 0;
}
```

---

## 作者：MSqwq (赞：1)

**CSP2023 RP++**  
首先考虑叉积的询问本质是两个向量的顺逆时针关系，即可以确定三个点之间的相对位置关系。  
考虑怎么有效的询问，如果固定一个点，有两个动点，那么太难维护信息，而且次数也不多，不妨先固定两个点，让一个点动，发现为了好处理，如果那两个定点是相邻的那就相当于确定了一条线段了，这就有很多性质了。  
Motivation：确定一条线段。  
因为答案要求逆时针输出，那就假设找 $1$ 号点的下一个点，那么根据我们询问二的本质可以发现，这个点满足与 $1$ 的单位向量可以逆时针旋转和其他所有点与 $1$ 的单位向量重合。即满足恒等式 $ask_2(1,i,se)=-1$，$i$ 为非 $1$ 和 $se$ 的所有点。  
现在求出了一条线段了，我们需要确定其他的点，那么发现此时再用询问二就没有太大的效果，考虑询问一，询问一可以给我们带来面积，如果再结合已知的定线段，可以发现其他点和这条线段组成的面积是一个单峰函数，逆时针的顺序就是先增后减，如果可以把整个图分成两半，那按照面积的顺序就可以得到答案了。  
那么思路变成求到峰值的点，然后将所有点分成两半，按面积先增后减的关系输出。  
求峰点，扫一遍就可以了，显然是和已知线段组成面积最大的那个点。分成两半那么就用询问二好了，仿照确定一条线段的思路，那么就是对 $ask_2(1,mx,i)$ 的结果分类，如果结果是 $1$ 那么就是在后半段，如果是 $-1$ 那么就是在前半段。  
最后面积可能会很大，用合适的数据类型储存。  
询问次数 $3n-7$。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

const int N=1010;
int s[N];
int ask(int opt,int i,int j,int k)
{
	cout<<opt<<" "<<i<<" "<<j<<" "<<k<<endl;
	int res;cin>>res;return res;
}
bool cmp1(int x,int y){return s[x]<s[y];}
bool cmp2(int x,int y){return s[x]>s[y];}
signed main()
{
	int n=read(),se=2,mx=0;
	for(int i=3;i<=n;i++)if(ask(2,1,i,se)==1)se=i;//确定一条线段
	for(int i=2;i<=n;i++)//确定峰值点
	{
		if(i==se)continue;
		s[i]=ask(1,1,se,i);
		if(s[i]>s[mx])mx=i;
	}
	vector<int>a,b;
	for(int i=2;i<=n;i++)//确定其他点的位置关系
	{
		if(i==se||i==mx)continue;
		int opt=ask(2,1,mx,i);
		if(opt==1)b.push_back(i);
		else a.push_back(i);
	}
	sort(a.begin(),a.end(),cmp1),sort(b.begin(),b.end(),cmp2);//确定具体关系
	cout<<0<<" "<<1<<" "<<se<<" ";
	for(auto x:a)cout<<x<<" ";cout<<mx<<" ";for(auto x:b)cout<<x<<" ";
	return 0;
}
```


---

