# Bessie's Birthday Cake (Easy Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the easy version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ y = 0 $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 2 $ , $ 6 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that can be used, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C1/a4f3a6e3efd4b2b24052c536629245c4fd02196b.png)

## 样例 #1

### 输入

```
3
8 4 0
1 6 2 5
8 8 0
1 3 2 5 4 6 7 8
4 2 0
1 3```

### 输出

```
2
6
2```

# 题解

## 作者：abc1234shi (赞：4)

题目的意思是从边开始，所有的边共构成了多少个三角形，而我们可以通过点数，来知道边数：有几条边，就有几个点。我们先找到这个图形可以划分成多少个三角形，其实这个这个图形是几边形无所谓，只有 $x$ 的值对我们是有用的，有 $x$ 条边，就有 $x$ 个点。首先我们把点排序，然后组成一个新的图形来看，我们数一下这个图形有几条不相交的对角线，很明显是 $x-3$ 条，所以三角形的数量就等于边加 $1$ 个也就是 $x-2$ 个三角形。然后将这个图形从头到尾遍历，如果两个点相差 $2$，答案就加 $1$。但是要注意最后一个点 $x$ 是否和第 $1$ 个点是否构成三角形，如果构成，答案还要加 $1$。

---

## 作者：littlebug (赞：3)

## Solution

根据样例的图来分析：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C1/a4f3a6e3efd4b2b24052c536629245c4fd02196b.png)

首先，我们很容易得出结论，当多边形不存在时，如果有 $x$ 个点，那么能构成的三角形个数为 $x-2$。可以考虑前 $3$ 个点构成一个三角形，后面每加一个点就增加一个三角形。

最简单的就是样例 #2 了，如果所有点都被选定，则答案为 $n-2$。

然后看样例 #3，此时 $n=4$（即总共点数为 $4$），如果所有点都被选定，那么答案为 $n-2=2$，但是样例中只选定了 $2$ 个点啊！再仔细看看，在这 $2$ 个三角形中，点 $4$ 和点 $2$ 都是三角形的顶点，所以**对答案有贡献的点总共有 $4$ 个**！

于是就快乐地得出了结论，答案 $=$ 对答案有贡献的点的个数 $-2$。接下来讨论如何计算对答案有贡献的点的个数就可以了。

容易得到，如果多边形的一个顶点 $A$ **未被选中**，但与它相邻的两个顶点都**被选中**，那么连接与它相邻的两个点，点 $A$ 就可以作为三角形的一个顶点，即对答案做出贡献了。

于是只要统计**选中的点的个数**和**与两个选中点相邻的点的个数**就行了。答案等于这两种点的个数之和 $-2$。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n,x,y;
int a[MAXN];
il void solve()
{
	cin>>n>>x>>y;
	for(int i=1;i<=x;++i)
		cin>>a[i];
	sort(a+1,a+x+1);
	int ans=x;
	for(int i=2;i<=x;++i)
	{
		if(a[i]-a[i-1]==2)
			++ans;
	}
	if(a[1]+n-a[x]==2)
		++ans;
	cout<<ans-2<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：luobotianle (赞：2)

对于 Bessie 选出的 $x$ 个点，我们可以将其看作一个多边形，那么根据中学数学知识，在其中最多可以切出 $x-2$ 个三角形；同时，对于每两个距离恰好为 $2$ 的点，也可以连出一个三角形。

由于 Easy Vision 中 $y=0$，所以直接输出答案即可。

注意如果第 $n$ 个点和第 $1$ 个点间的距离为 $2$ 也要 `ans++`。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int T,n,x,y;
int a[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>y;
		for(int i=1;i<=x;i++)cin>>a[i];
		sort(a+1,a+1+x);
		int ans=x-2;
		for(int i=2;i<=x;i++)if(a[i]-a[i-1]==2)ans++;
		if(a[x]+2-n==a[1])ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：bjqxszx_liruixuan (赞：1)

## 思路
这道题 y = 0 ，所以只需考虑这 x 点。把它们看做一个多边形，有 x - 2 个三角形。然后找到所有相差为二的点，把他们加起来就是答案。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int t,n,x,y,a[10000005],ans;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		ans=0;
		cin>>n>>x>>y;
		for(int i=1;i<=x;i++)//输入每个点。
		{
			cin>>a[i];
		}
		sort(a+1,a+x+1);//排序。
		for(int i=2;i<=x;i++)
		{
			if(a[i]-a[i-1]==2)//找到所有相差为二的点。
			{
				ans++;
			}
		}
		if(a[1]-0+n-a[x]==2)//判断第一个点和最后一个点是否满足。
		{
			ans++;
		}
		cout<<ans+x-2<<endl;//将它们加上x-2。
	}
 	return 0;
}


```

---

## 作者：Atserckcn (赞：1)

### 首先来个题目翻译

这是问题的简单版本。两个版本之间的唯一区别是对 $y$ 的约束。在此版本中，$y=0$。只有当两个版本都得到解决时，您才能进行黑客攻击。
贝茜从她最好的朋友艾尔西那里收到了一个生日蛋糕，它以一个规则的多边形的形式出现，带有 $n$ 面。蛋糕的顶点编号为
顺时针方向 $1$ 到 $n$。你和 Bessie 将选择其中一些顶点来切割不相交的对角线到蛋糕中。换言之，对角线的端点必须是所选顶点的一部分。
贝茜只想分发一块蛋糕，这会导致一个三角形以保持一致性。碎片的大小无关紧要，整个蛋糕不必分成所有三角形（蛋糕中允许其他形状，但不计算在内）。

Bessie 已经选择了可用于形成对角线的 $x$ 个顶点。她希望你选择的顶点不超过 $y$ 个，这样她可以给出的三角形蛋糕的数量就会最大化。

贝茜最多可以送出三角形蛋糕多少块？

### 正解：

因为是取若干个三角形，所以我们不难想出由 $n$ 个点中随意取若干个点，由初中数学可知，共 $n-2$ 种情况。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,x,y,T,a[MAXN],ans;
int main(){
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&x,&y);
		for(int i=1;i<=x;i++)
			scanf("%d",&a[i]);
		ans=x-2;//上得
		sort(a+1,a+x+1);
		for(int i=2;i<=x;i++)
			if(a[i]-a[i-1]==2)//每两个距离为2的点都可以组成一个三角形
					ans++;
		if(a[x]-n==a[1]-2) ans++;//特判：第n个点与1号点距离为2
		printf("%d\n",ans);
	}
	return 0;
}
```

感谢观看。

---

## 作者：Xlon_Rainfi (赞：1)

## 思路

其实只需要把选中的点组成一个新的多边形，然后我们就可以发现有 $x$ 个点的多边形可以连出 $x-2$ 个三角形。此外，两个位置差为 $2$ 的点也是可以连出一个三角形。

于是我们只需要对点的位置排个序，然后从头到尾遍历一遍，发现差为 $2$ 的相邻两点就 `cnt++`，最后输出 $x-2+cnt$ 就是最终答案了。

**注意**：首尾点的位置差为 $n-a_x+a_1$，如果这个为 $2$ 也得 `cnt++`。

**时间复杂度**：每组数据 $O(n \log_2 n)$。

## C++ 代码

```
#include <iostream>
#include <algorithm>
#include <string.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int T,n,x,y,ans,a[N];
int main(){
	//数据较大，关闭同步流加快输入输出速度
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
    	ans=0,memset(a,0,sizeof(a));	//保险起见清空一下
    	cin>>n>>x>>y;
    	for(int i=1;i<=x;i++)cin>>a[i];
    	sort(a+1,a+x+1);	//排序点的位置
    	for(int i=2;i<=x;i++)if(a[i]-a[i-1]==2)ans++;
    	if(n-a[x]+a[1]==2)ans++;	//判断首尾点的位置差
    	cout<<ans+x-2<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

找能划分成几个三角形，题目的意思是从边入手，边构成了多少个三角形，而我们数边是通过数点来完成的，所以我们从点入手。
其实这个图形是几边形无所谓，只有 $x$ 的值对我们是有用的，首先我们把点排序，然后组成一个新的图形来看，然后我们要数一下有几条不相交的对角线，很明显是 $x-3$ 条，但是会隔成 $x-2$ 个三角形，但是，数对角线的时候，我们把所有的点考虑成了相邻的，假如不相邻，就像 case3 一样，如果 $v [ i  ] =v[ i-1 ]+2$ ，那么相邻的边也可以组成一个三角形，所以需要相加，但别忘了，点是环状的，所以最后一个点单独拿出来考虑。

代码时间到！
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve() {
	int n,x,y;
	cin>>n>>x>>y;
	vector<int>v(x);
	for(int i=0;i<x;i++) cin>>v[i];
	sort(v.begin(),v.end());
	int ans=x;
	for(int i=1;i<(int)v.size();i++)
		if(v[i]==v[i-1]+2) ans++;
	int a=v.size(),b=v[a-1]+2;
	if(b>n) b-=n;
	if(b==v[0]) ans++;
	cout<<ans-2<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
//各位大佬给个面子，点个赞吧
```

---

## 作者：wangzc2012 (赞：0)

# CF1942C1 Bessie's Birthday Cake (Easy Version)
## 题意概括
有一个正 $n$ 边形，给定 $x$ 个关键点，你可以额外指定至多 $y$ 个关键点。在关键点两两之间任意连互相不交叉的对角线，使得整个图形被划分出的区域中三角形的数量尽可能多。
## 思路分析
首先，题目中已经说明，$y=0$。因此，我们可以将这 $x$ 个关键点看作是一个 $x$ 边形。  
在这里需要引入一个小知识：对于一个 $x$ 边形，以顶点连接顶点，最多可以连出 $x-2$ 个三角形。  
所以，此时这个 $x$ 边形已经可以分出 $x-2$ 个三角形了。

同时，我们还需要考虑，两个关键点间的距离如果为 $2$ ，将他们连接也可以得到一个三角形。因此，我们如果发现有关键点间的距离为 $2$，答案就加 $1$。  
在这里需要注意，第一个关键点与做后一个关键点间的距离为 $n-2$，需要特判。
## AC Code
代码有点丑，请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y,a[2000005];
int main(){
    ios::sync_with_stdio(false);  
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while (t--){
        cin>>n>>x>>y;
        int ans=x-2;
        for (int i=1;i<=x;i++) cin>>a[i];
        sort(a+1,a+x+1);
        for (int i=2;i<=x;i++){
            if (a[i]-a[i-1]==2) ans++;
        }
        if (a[x]-a[1]==n-2) ans++;
        cout<<ans<<'\n';
    }
    return 0;
}
```
## 更新日志
2024年7月25日：删去了题解中无用的语句，同时优化了表达方式。

---

## 作者：jwsdy (赞：0)

# 题解：CF1942C1 Bessie's Birthday Cake (Easy Version)

~~初二学生党福音~~

## 题目分析

在一个有 $n$ 个点的正多边形（也就是正 $n$ 边形）我们需要对特定的 $x$ 个点进行连线保证平面内出现的三角形最多（咱也不知道 $y$ 有啥用）。

## 解题过程

对于给定的 $x$ 个点，我们可以将其看作是一个 $x$ 边形，对于一个 $x$ 边形而言，它从某个顶点出发，除了与自己相邻的两个顶点外，别的顶点均可相连，也就是可连成 $x-2$ 条边，而每连一条边就会多创造出一个三角形，即一开始就会有 $x-2$ 个三角形。

若两点编号差值为 $2$，即又可以连成一条边构成一个三角形，可通过将 $x$ 个点的编号升序排序后比较得出。

**注意**：不要忘记比较首尾两个点的编号！！！ 

## 小tips

各位 cin 和 cout 党可以用快读增强输入效率。

```
template<typename T> void read(T&x){
	int s=1;
	x=0;
	char c;
	do{
		c=getchar();
		if(c=='-') s=-1;
	}while(!isdigit(c));
	do{
		x=x*10+c-'0';
		c=getchar();
	}while(isdigit(c));
	x*=s;
}
```
### code
```
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
//快读 
template<typename T> void read(T&x){
	int s=1;
	x=0;
	char c;
	do{
		c=getchar();
		if(c=='-') s=-1;
	}while(!isdigit(c));
	do{
		x=x*10+c-'0';
		c=getchar();
	}while(isdigit(c));
	x*=s;
}
const int N=2e6;
int t,n,x,y; 
int a[N];
int ans;
signed main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	read(t);
	while(t--){
		read(n),read(x),read(y);
		ans=x-2;
		for(int i=1;i<=x;i++) read(a[i]);
		sort(a+1,a+1+x);
		for(int i=2;i<=x;i++)
		if(a[i]-a[i-1]==2) ans++;//如果相差2，即可连线 
		if(a[1]+n-a[x]==2) ans++;//比较首尾编号 
		cout<<ans<<endl; 
	}
	return 0;
}
```

---

## 作者：xiaoxiongbinggan (赞：0)

# Bessie's Birthday Cake 题解

## 题目分析

在一个正 $n$ 边形中，给出 $x$ 个点，求出以这 $x$ 个点为顶点所构成的个数最多的三角形（因为是简单版本，所以输入的 $y$，也就是增加点的个数始终为 $0$。）。

分析完毕。

正 $n$ 边形的性质：以某一个顶点出发，连接其他顶点，最多可以构成 $n-2$ 个三角形。

但题目中给出的正 $n$ 边形中只有 $x$ 个边可以与其它边相连接，那我们就可以把他看成正 $x$ 边形，那一开始就有 $x-2$ 个三角形，并且若两个点的编号之差为 $2$（就是说两个点相距 $2$ 个距离）那他们也可以构成三角形。

要特判第 $x$ 个点与第 $1$ 个点的距离并不是 $2$，而是 $n-2$。

## Code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;
int a[1000000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		int n,x,y;
		cin>>n>>x>>y;
		for(int i=1;i<=x;i++){
			cin>>a[i];
		}
		int ans=x-2;
		sort(a+1,a+1+x);//一定要有排序，好查找相距距离为2的点
		for(int i=1;i<=x;i++){
			if(i==1){//特判第一个点与最后一个点的距离是否是n-2 
				if(a[x]-a[i]==n-2) ans++;
				continue;
			}
			if(a[i]-a[i-1]==2){
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：Hanrui1206 (赞：0)

## 思路
通过多边形的性质判断即可。
多边形的性质常见有：

- 内角和：$n$ 边形的内角和为 $(n - 2) \times 180^   \circ$。
- 外角和：任意多边形的外角和为 $360 ^ \circ$。
- 对角线性质：多边形的对角线数量和性质依赖于边的数量。例如，$n$ 边形共有 $n (n - 3) / 2$ 条对角线，且从一个顶点出发的对角线可以将多边形分成 $(n - 2)$ 个三角形。

这可以利用多边形性质把给定的 $x$，看作一个 $x$ 边形，那么这个 $x$ 边形至少会有 $x - 2$ 个三角形。

当两点距离相差 $2$ 时，也会有一个三角形，我们依次累加上去就可以了。

---

## 作者：天使宝贝 (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF1942C1)

### 思路&分析

这道题中 $y = 0$，所以我们直接忽略 $y$。

首先我们把 $x$ 个点看作一个多边形，这样我们就拥有了 $x - 2$ 个三角形，接着我们找到所有相差为 $2$ 的点，累加到答案中，最后在特判一下第 $x$ 个和第 $1$ 个之间的差是否为 $2$ 即可。

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
constexpr int MAXN = 2e5 + 5;
int T, n, x, y, a[MAXN], ans;
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    IOS;  // 读入加速
    cin >> T;
    while (T--)
    {
        ans = 0;
        cin >> n >> x >> y;
        for (int i = 1; i <= x; i++)
            cin >> a[i];
        sort (a + 1, a + x + 1, cmp);
        for (int i = 1; i < x; i++)
            if (a[i] - a[i + 1] == 2)
                ans++;
        if (a[x] + n - a[1] == 2)
            ans++;
        cout << x - 2 + ans << endl;  // 还得加上最开始拥有的 x - 2 个三角形
    }
    return 0;
}
```

---

## 作者：imsbNR (赞：0)

# 题解：CF1942C1 Bessie's Birthday Cake (Easy Version)

## 思路

我们可以把 $x$ 个点看成一个 $x$ 边形，那么一开始我们就有 $x - 2$ 个三角形。

我们再看别的，因为当两点之间距离为 $2$ 时可以连边形成一个新三角形，加到答案里即可。

需要特判第 $x$ 个与第 $1$ 个之间距离是不是 $2$ 哦。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, a[N], n, x, y, ans;
void solve()
{
	cin >> n >> x >> y;
	ans = x - 2;
	for (int i = 1; i <= x; i++)
		cin >> a[i];
	sort(a + 1, a + x + 1, greater<int>());
	for (int i = 1; i < x; i++)
		if (a[i] - a[i + 1] == 2)
			ans++;
	if (a[x] + n - a[1] == 2)
		ans++;
	cout << ans << '\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：__XU__ (赞：0)

# CF1942C1 题解

### 思路：

通过多边形的性质判断即可。

### 做法：

首先，我们可以把给定的 $x$, 看作一个 $x$ 边形，那么这个 $x$ 边形至少会有 $x-2$ 个三角形（多边形性质）。

其次，我们知道，当两点距离相差 $2$ 时，也会有一个三角形，我们依次累加上去就可以了。

### 注意：

$a_1$ 与 $a_x$ 的差为 $a_1+n-a_x$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t;
int a[N];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	cin>>t;
	while(t--){
		int cnt=0;
		int n,x,y;
		cin>>n>>x>>y;
		for(int i=1;i<=x;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+x,cmp);
		for(int i=1;i<=x-1;i++){
			if(a[i]-a[i+1]==2){
				cnt++;
			}
		}
		if(a[x]+n-a[1]==2){
			cnt++;
		}
		cout<<x-2+cnt<<'\n';
	}
	return 0;
} 

```

谢谢观看。

---

## 作者：Miracle_1024 (赞：0)

## 思路
	
   1. 看完题后我们可以得知任意 $x$ 个点内部可以构成 $ x-2$ 个三角形。对于外部点三角形,我们可以发现，只有两个点距离恰好为 $2$ 点时候可以构成外部一个三角形。
   
   2. 注意到相邻连续的一段特殊点可以被缩掉。缩点之后这一段点就只剩下左右端点了，最后会得到若干个特殊点，这样从一个点向其它所有点连边，然后把边上的边连起来，然后这道题就解决咯。
   
## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,n,x,y,ans,a[N];
int main(){
    cin>>t;
	while(t--){
		cin>>n>>x>>y;
    	ans=x-2;        
    	for(int i=1;i<=x;i++)cin>>a[i];
    	sort(a+1,a+x+1);
    	for(int i=2;i<=x;i++)if(a[i]-a[i-1]==2)ans++;
    	if(a[1]+n-a[x]==2)ans++;  
    	cout<<ans<<endl;
	}    
}
```

---

## 作者：HasNoName (赞：0)

### 思路

因为在 $n>2$ 时 $n$ 个点可以组成 $n-2$ 个三角形，所以只需要考虑两个点和多边形角上的点组成的三角形。

由于如果两个已选点中间的点的个数不为 $1$，则一定不能组成题目所要求的三角。

因为如果两点相邻则一定不行。若中间的点的个数大于 $1$，如果中间有已选点则不行，否则要么组不成三角形要么与已有三角形重叠，因为组成的三角形一定没有点在多边形未选点上。

若两个已选点中间的点的个数为 $1$，且中间已有已选点，则组成的三角形一定没有点在多边形未选点上。

排序之后再统计即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,k;
int a[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        int ans=max(m-2,0);//内部组成的三角形数
        for(int i=1;i<=m;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+m+1);
        for(int i=1;i<m;i++)//统计与为选点组成的三角
        {
            if(a[i+1]==a[i]+2)
            {
                ans++;
            }
        }
        if((a[m]+2)%n==a[1])ans++;//a[m]与a[1]也可能中间点的个数为1
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：hyman00 (赞：0)

### 题意

有一个正 $n$ 边形的蛋糕，目前有 $x$ 个关键点为顺时针的第 $a_i$ 个，你可以再添加 $y$ 个关键点，然后在关键点之间连边，边不相交，最大化分出的三角形个数。

$4\le n\le 10^9,2\le x\le \min(n,2\times 10^5),0\le y\le n-x$ 

在 C1 中，有 $y=0$ 

### C1 做法

关键点的位置是固定的。

我们令 $d_i$ 为第 $i$ 个和下一个顺时针上的距离，不难发现答案为 $x-2+\sum_{i}[d_i=2]$。

解释下，就是这 $x$ 个点构成了一个 $x$ 边形，能分出 $x-2$ 个，外面如果距离恰好为 $2$ 会多一个。

复杂度 $O(n\log n)$，瓶颈在于排序。

### C2 做法

考虑 C1 中的 $d_i=2$ 的情况，其实就是说中间跨过的点也有可能成为某个三角形的顶点，即答案为可能是**可能成为某个三角形的顶点**的顶点个数减二。

一开始这样的点数我们是知道的，考虑继续标记一个点带来的贡献。

- $d=2k(k>1)$ 

可以一个隔一个地标记，标记 $x(x<k)$ 个的贡献是 $2x$，另外如果恰好 $k-1$ 可以有额外的一个贡献.

- $d=2k-1(k>0)$

同上，但是不会有额外贡献。

综上，前一种情况更优。把 $\{d_i\}$ 按奇偶性分别从小到大排序，贪心地先选偶数再选奇数，可以证明是最优的。

复杂度也是 $O(n\log n)$。

### 赛时代码

```c++
int n,x,y;
int a[200005];
int d[200005];
vi v0,v1;
void run(){
	cin>>n>>x>>y;
	rep(i,x)cin>>a[i];
	sort(a,a+x);
	rep(i,x-1)d[i]=a[i+1]-a[i];
	d[x-1]=a[0]+n-a[x-1];
	v1.clear();
	v0.clear();
	rep(i,x){
		if(d[i]&1)v1.pb(d[i]);
		else v0.pb(d[i]);
	}
	int s=x-2;
	sort(all(v0));
	sort(all(v1));
	for(int i:v0){
		if(i==2){
			s++;
		}
		else{
			if(y>=i/2-1){
				y-=i/2-1;
				s+=i-1;
			}
			else{
				s+=y*2;
				y=0;
			}
		}
	}
	for(int i:v1){
		if(y>=i/2){
			y-=i/2;
			s+=i-1;
		}
		else{
			s+=y*2;
			y=0;
		}
	}
	cout<<s<<"\n";
}
```

---

