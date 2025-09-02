# 3-cycles

## 题目描述

During a recent research Berland scientists found out that there were $ n $ cities in Ancient Berland, joined by two-way paths. Any two cities are joined by no more than one path. No path joins a city with itself. According to a well-known tradition, the road network was built so that it would be impossible to choose three cities from each of which one can get to any other one directly. That is, there was no cycle exactly as long as 3. Unfortunately, the road map has not been preserved till nowadays. Now the scientists are interested how much developed a country Ancient Berland was. Help them - find, what maximal number of roads could be in the country. You also have to restore any of the possible road maps.

## 样例 #1

### 输入

```
3
```

### 输出

```
2
1 2
2 3
```

## 样例 #2

### 输入

```
4
```

### 输出

```
4
1 2
2 3
3 4
4 1
```

# 题解

## 作者：Edmundino (赞：9)

# 题意

这题要求我们的是

给你一个$n$，求有$n$个结点的最多边的无向图
而且没三个点之间不会有环

# 分析

首先，我要给大家讲一下一个奥数问题

### 抽屉问题

题目：给你$n$个小球

问最多要多少个抽屉来装这些小球

保证一定有两个球在同一个抽屉

过程：我们先要把$n$放入$n$个抽屉中

这时，每个小球都在不同的抽屉了

当我们拿走一个抽屉

此时，就要一个球被抛弃了

他要再找个抽屉

但是剩下的抽屉里都有一个小球

所以那个小球就只好跟一个小球在同一抽屉里了

此时就满足了题目要求

所以答案是$n-1$个抽屉

再回来看这题

这题要求你的是，每三个点间的边不会是环

这就可以装换为：每三个点至少有两个点同一个抽屉里

啥意思呢：

就是我可以把$n$个球分成两组

每组里的点是互相没有连边的

而不同组的点都有一个连边

就像相当于把$n$个点放入两个抽屉

怎么取$3$个点总有两个点在同一抽屉

而同一抽屉的点是不会有连边的

所以就不会产生环

但是如果我们分成三组

此时，我抽任意三个点就有可能三个都不在同一个抽屉

就有几率产生环

所以我就是要把$n$个点分成两部分

~~其实就是二分图~~

好了现在我们来算最多多少个边

分类讨论：

当$n$是偶数时

两个部分的点都是$\frac{n}{2}$个

那$m$就是$\frac{n}{2}\times\frac{n}{2}$

当$n$时奇数时

一个部分是$\frac{n}{2}$个，另一个部分是$\frac{n}{2}+1$个

那$m$就是$\frac{n}{2}\times(\frac{n}{2}+1)$

对于要输出边

那就比较简单

就循环$i=1$到 $\frac{n}{2}$

里面再循环$j=(\frac{n}{2}+1)$到$n$

然后输出$i$,$j$即可

# 代码

代码部分不难理解

我就直接上$AC$完整代码了

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

int n,m;

int main()
{
	cin>>n;
	if(n%2==1)
	{
		m=(n/2)*(n/2+1); 
	}
	else
	{
		m=(n/2)*(n/2);
	}
	cout<<m<<endl;
	for(int i=1;i<=n/2;i++)
	{
		for(int j=n/2+1;j<=n;j++)
		{
			cout<<i<<" "<<j<<endl;
		}
	}
	return 0;
}
```




---

## 作者：hongshixiaobai (赞：2)

# CF41E 3-cycles 题解
[传送门](https://www.luogu.com.cn/problem/CF41E)
## 题意
求结点数为 $n$，且没有结点数恰好等于 $3$ 的环的无向连通图的最大边数 $m$，并输出任意一种可能。
## 思路
题目要求任意三个点不成环，如果把点放在三个抽屉里就有概率成环，那最多把点放进两个抽屉，即把点分为两个集合，其中一个集合里的所有点向另一个集合的所有点连边，使边数最多，即找两个和为 $n$ 的数，使其乘积最大，根据小奥里的＂和不变，差小积大＂可以得到将点划为  $[1,\lfloor\frac{n}{2}\rfloor]$ 和 $[\lfloor\frac{n}{2}\rfloor+1,n]$ 两个集合时最优（将点分为一个集合时即为不连边），以 $n = 5$ 为例，从 $1$ 到 $\lfloor\frac{n}{2}\rfloor$ 分别向 $\lfloor\frac{n}{2}\rfloor+1$ 到 $n$ 连边，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/4w7a0ohl.png)

此时可行边数最多。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,tmpi,tmpj;//全局i，j卡常
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	tmpi = n>>1;//卡常
	tmpj = (n>>1)+1;
	cout<<i*j<<"\n";//输出最多边数
	for(i = 1;i<=tmpi;i++)//构造
	{
		for(j = tmpj;j<=n;j++)
		{
			cout<<i<<' '<<j<<"\n";
		}
	} 
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：2)

### 思路
由任意三个点不组成环，很容易想到二分图。那么把所有点分成两部分，这两部分全部连满即可。
### 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	long long n;
	cin>>n;
	cout<<(n/2)*(n-n/2)<<endl;
	for(int i=1;i<=n/2;i++){
		for(int j=n/2+1;j<=n;j++){
			cout<<i<<' '<<j<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：chl123123 (赞：2)

### 思路：
本题一看就是一道抽屉原理，比较简单，适合刚学数论的同学。仔细思考就知道，意为三个点中有两个点放在同一个抽屉中。

### 代码（c++）：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std；
int main()
{
	ll n；
	cin>>n；
   	//如果不能整除
	if(n%2==1) cout<<(n/2)*(n/2+1)<<endl；
   	//如果可以整除
	else cout<<(n/2)*(n/2)<<endl； 
	for(ll i=1；i<=n/2；i++)
		for(ll j=n/2+1；j<=n；j++)
			cout<<i<<" "<<j<<endl；//按题目要求输出
	return 0；//CE
}
```
[题目传送门](https://www.luogu.com.cn/problem/CF41E)

---

## 作者：midsummer_zyl (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/CF41E)

### [可能食用更佳的地方](https://www.luogu.com.cn/blog/1025321/cf41e-3-cycles-ti-xie)

# 知识讲解

### ROUND 1

桌上有十个苹果，要把这十个苹果放到九个抽屉里，无论怎样放，我们会发现至少会有一个抽屉里面放不少于两个苹果。这一现象就是我们所说的“抽屉原理”。

抽屉原理的一般含义为：“如果每个抽屉代表一个集合，每一个苹果就可以代表一个元素，假如有 $n + 1$ 个元素放到 $n$ 个集合中去，其中必定有一个集合里至少有两个元素。”

抽屉原理有时也被称为鸽笼原理，它由德国数学家狄利克雷首先明确提出来并用来证明一些数论中的问题，因此，也被称为狄利克雷原则。


一、抽屉原理有四种基本的表达：

原则 $1$：把多于 $n + 1$ 个的物体放到 $n$ 个抽屉里，则至少有一个抽屉里的东西不少于两件。

原则 $2$：把多于 $m \times n + 1$ （$n$ 不为 $0$） 个的物体放到 $n$ 个抽屉里，则至少有一个抽屉里有不少于 $m + 1$ 的物体。

原则 $3$：把无数多件物体放入 $n$ 个抽屉，则至少有一个抽屉里有无数个物体。

原则 $4$：把 $m \times n + 1$ 个物体放入 $n$ 个抽屉中，其中必有一个抽屉中至多有 $m - 1$ 个物体

通常，我们把原则 $1$、$2$、$3$ 称为第一抽屉原理，原则 $4$ 称为第二抽屉原理。

————摘自[这篇博客](https://zhuanlan.zhihu.com/p/85350269#:~:text=%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86%E6%9C%89%E6%97%B6%E4%B9%9F%E8%A2%AB%E7%A7%B0%E4%B8%BA%E9%B8%BD%E7%AC%BC%E5%8E%9F%E7%90%86%EF%BC%8C%E5%AE%83%E7%94%B1%E5%BE%B7%E5%9B%BD%E6%95%B0%E5%AD%A6%E5%AE%B6%E7%8B%84%E5%88%A9%E5%85%8B%E9%9B%B7%E9%A6%96%E5%85%88%E6%98%8E%E7%A1%AE%E6%8F%90%E5%87%BA%E6%9D%A5%E5%B9%B6%E7%94%A8%E6%9D%A5%E8%AF%81%E6%98%8E%E4%B8%80%E4%BA%9B%E6%95%B0%E8%AE%BA%E4%B8%AD%E7%9A%84%E9%97%AE%E9%A2%98%EF%BC%8C%E5%9B%A0%E6%AD%A4%EF%BC%8C%E4%B9%9F%E8%A2%AB%E7%A7%B0%E4%B8%BA%E7%8B%84%E5%88%A9%E5%85%8B%E9%9B%B7%E5%8E%9F%E5%88%99%E3%80%82%20%E5%9C%A8%E5%B0%8F%E5%8D%87%E5%88%9D%E5%B8%B8%E8%80%83%E7%9F%A5%E8%AF%86%E7%82%B9%E4%B8%AD%EF%BC%8C%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86%E9%9D%9E%E5%B8%B8%E6%9C%89%E8%B6%A3%EF%BC%8C%E8%80%8C%E4%B8%94%E6%9C%89%E9%9D%9E%E5%B8%B8%E5%BC%BA%E7%9A%84%E8%A7%84%E5%BE%8B%E6%80%A7%E3%80%82%20%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86%E6%98%AF%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6%E4%B8%AD%E4%B8%80%E4%B8%AA%E9%87%8D%E8%A6%81%E8%80%8C%E5%8F%88%E5%9F%BA%E6%9C%AC%E7%9A%84%E6%95%B0%E5%AD%A6%E5%8E%9F%E7%90%86%EF%BC%8C%E5%88%A9%E7%94%A8%E5%AE%83%E5%8F%AF%E4%BB%A5%E8%A7%A3%E5%86%B3%E5%BE%88%E5%A4%9A%E6%9C%89%E8%B6%A3%E7%9A%84%E9%97%AE%E9%A2%98%EF%BC%8C%E5%B9%B6%E4%B8%94%E5%B8%B8%E5%B8%B8%E8%83%BD%E5%A4%9F%E8%B5%B7%E5%88%B0%E4%BB%A4%E4%BA%BA%E6%83%8A%E5%A5%87%E7%9A%84%E4%BD%9C%E7%94%A8%E3%80%82%20%E8%AE%B8%E5%A4%9A%E7%9C%8B%E8%B5%B7%E6%9D%A5%E7%9B%B8%E5%BD%93%E5%A4%8D%E6%9D%82%EF%BC%8C%E7%94%9A%E8%87%B3%E6%97%A0%E4%BB%8E%E4%B8%8B%E6%89%8B%E7%9A%84%E9%97%AE%E9%A2%98%EF%BC%8C%E5%9C%A8%E5%88%A9%E7%94%A8%E6%8A%BD%E5%B1%89%E5%8E%9F%E5%88%99%E5%90%8E%EF%BC%8C%E8%83%BD%E5%BE%88%E5%BF%AB%E4%BD%BF%E9%97%AE%E9%A2%98%E5%BE%97%E5%88%B0%E8%A7%A3%E5%86%B3%E3%80%82%20%E4%BB%8A%E5%A4%A9%EF%BC%8C%20%E6%88%91%E4%BB%AC%E6%9D%A5%E8%AF%A6%E7%BB%86%E7%9A%84%E8%AF%B4%E4%B8%80%E8%AF%B4%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86%E3%80%82,%E4%B8%80%E3%80%81%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86%E6%9C%89%E5%9B%9B%E7%A7%8D%E5%9F%BA%E6%9C%AC%E7%9A%84%E8%A1%A8%E8%BE%BE%EF%BC%9A%20%E5%8E%9F%E5%88%991%EF%BC%9A%20%E6%8A%8A%E5%A4%9A%E4%BA%8En%2B1%E4%B8%AA%E7%9A%84%E7%89%A9%E4%BD%93%E6%94%BE%E5%88%B0n%E4%B8%AA%E6%8A%BD%E5%B1%89%E9%87%8C%EF%BC%8C%E5%88%99%E8%87%B3%E5%B0%91%E6%9C%89%E4%B8%80%E4%B8%AA%E6%8A%BD%E5%B1%89%E9%87%8C%E7%9A%84%E4%B8%9C%E8%A5%BF%E4%B8%8D%E5%B0%91%E4%BA%8E%E4%B8%A4%E4%BB%B6%E3%80%82%20%E5%8E%9F%E5%88%992%EF%BC%9A%20%E6%8A%8A%E5%A4%9A%E4%BA%8Emn%20%28m%E4%B9%98n%29%2B1%EF%BC%88n%E4%B8%8D%E4%B8%BA0%EF%BC%89%E4%B8%AA%E7%9A%84%E7%89%A9%E4%BD%93%E6%94%BE%E5%88%B0n%E4%B8%AA%E6%8A%BD%E5%B1%89%E9%87%8C%EF%BC%8C%E5%88%99%E8%87%B3%E5%B0%91%E6%9C%89%E4%B8%80%E4%B8%AA%E6%8A%BD%E5%B1%89%E9%87%8C%E6%9C%89%E4%B8%8D%E5%B0%91%E4%BA%8E%EF%BC%88m%2B1%EF%BC%89%E7%9A%84%E7%89%A9%E4%BD%93%E3%80%82)
#### 详细版本请见[此篇博客](https://www.zhihu.com/question/40610379)



------------


### ROUND 2：

#### 另外，窝在这里顺便为大家讲解~~非常实用的~~三目运算符：

条件运算符，也称为三元运算符，是一种在确定条件为真或假时选择不同操作的运算符。它的一般形式是：``condition ? expression1 : expression2``。

条件运算符由三个部分组成：

1. 条件（``condition``）：一个可以求值为真或假的表达式。

2. 表达式 $1$（``expression1``）：在条件为真时执行的操作或返回的值。

3. 表达式 $2$（``expression2``）：在条件为假时执行的操作或返回的值。

4. 当条件为真时，整个表达式的值为表达式 $1$ 的值；当条件为假时，整个表达式的值为表达式 $2$ 的值。

这种运算符通常用于简化简单的条件分支语句，例如：

``int max = (a > b) ? a : b;``

以上代码根据条件（$a > b$）的结果，如果为真，则将变量 $max$ 赋值为 $a$ 的值，否则赋值为 $b$ 的值。

条件运算符可以提高代码的简洁性和可读性，但在使用时需要注意避免过度复杂化，以免影响代码可维护性。

[C语言三目运算符 - C语言零基础入门教程](https://blog.csdn.net/zhadenianqu/article/details/119376629)

[C语言条件运算符详解](https://blog.csdn.net/weixin_45743799/article/details/104440656?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169268416116800188572774%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169268416116800188572774&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-104440656-null-null.142^v93^chatgptT3_2&utm_term=%E6%9D%A1%E4%BB%B6%E8%BF%90%E7%AE%97%E7%AC%A6&spm=1018.2226.3001.4187)

------------

# [AC](https://www.luogu.com.cn/record/122109818)代码：

代码还是挺简单的，很容易理解，就不多说了。

```cpp
#include <bits/stdc++.h>
#define 谢谢观赏~ return 0;
#define QWQ }
using namespace std;
int main() {
	int n, ans;
	cin >> n;
	ans = n % 2 ? (n / 2) * (n / 2 + 1) : (n / 2) * (n / 2);
        //三目运算符
	cout << ans << endl;
	for (int i = 1; i <= n / 2; i++)
		for (int j = n / 2 + 1; j <= n; j++)
			cout << i << " " << j << endl;
	谢谢观赏~
QWQ
```

如果您觉得这篇题解对您有帮助，就点个赞吧！谢谢~

---

## 作者：Fool_Fish (赞：1)

一道抽屉原理的题

首先，我们把没有边相连的点放进同一个抽屉

那么很明显，我们需要两个抽屉，这样我们就能保证任取 $3$ 个点都没有环了

任取 $3$ 个点，因为有 $2$ 个抽屉，所以一定会有一个抽屉中有两个以上的点，那么这 $3$ 个点中就一定不可能形成环

假如我们有 $3$ 个抽屉，那么是有可能三个点分散在三个不同抽屉，有可能形成环

综上，我们需要两个抽屉，并且同一抽屉内的点不能连边，不同抽屉中的点连边

接下来是分配问题，即两个抽屉中分别分配多少个点

根据小学数学，当和一定时，平均分配，乘积最大

所以只需要平均的分成两组就好了

如果是奇数的话，就一个多一就行了

至于输出，按照刚才的分组就行了

code

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
int main(){
	int n;
	scanf("%d",&n); 
	if(n%2==1){
		printf("%d\n",(n/2)*(n/2+1));
	}
	else{
		printf("%d\n",(n/2)*(n/2)); 
	}
	for(int i=1;i<=n/2;i++){
		for(int j=n/2+1;j<=n;j++){
			printf("%d %d\n",i,j);
		}
	}
	return 0;
}
```

---

## 作者：int_stl (赞：0)

这道题其实是一个二分图。  
把图的点划为 $[1,\frac{n}{2}]$ 和 $[\frac{n}{2}+1,n]$ 两个集合，最大边数即为 $\lfloor\frac{n}{2}\rfloor \times \lfloor n-\frac{n}{2}\rfloor$。  
然后遍历两个集合，把组合输出即可。  
```cpp
#include <iostream>
#define int long long
using namespace std;
int n;
signed main() {
	cin >> n;
	cout << (n >> 1) * (n - (n >> 1)) << endl;//也可以写为cout << (n >> 1) * ((n >> 1) + (n & 1) ? 1 : 0) << endl;代码把奇偶性都包括进去了
	for (int i = 1; i <= (n >> 1); i++) { //遍历集合，输出每一种可能
		for (int j = (n >> 1) + 1; j <= n; j++) {
			cout << i << " " << j << endl;
		}
	}
}
```

---

## 作者：ttttalk (赞：0)

题面有误，望尽快修改。

[传送门](https://www.luogu.com.cn/problem/CF41E)

### 题意

求结点数为 $n$，没有三元环的连通图的最大边数和构造。

### 思路

一开始猜结论猜了好一会。。后来发现是二分图之后就直接做完了。直接把点平均分为两个集合，然后在不同集合之间连边就行了。

### 代码

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,m;
signed main()
{
	cin.tie(0),cout.tie(0);
	cin>>n;
	cout<<(n/2)*(n-n/2)<<"\n";
	for (int i=1;i<=n/2;i++)
	{
		for (int j=n/2+1;j<=n;j++) cout<<i<<" "<<j<<"\n";
	}
}

```

---

## 作者：DengDuck (赞：0)

思考一下这个图的样子，任意三个点不组成环，那不就是二分图吗？那你就把点划分成两部分，然后两部分连满就行了。

边数为 $x(n-x)$，$x$ 为左边的点数，显然 $x=\lfloor \dfrac n 2\rfloor$ 有最大值。

然后你直接输出就行了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n;
vector<pair<LL,LL> >v;
int main()
{
	scanf("%lld",&n);
	printf("%lld\n",(n/2)*(n-n/2));
	for(int i=1;i<=n/2;i++)
	{
		for(int j=n/2+1;j<=n;j++)
		{
			printf("%d %d\n",i,j);
		}
	}
}
```

---

## 作者：Union_Find (赞：0)

题意不难理解，就是求一个图，上面没有三元环且边数最大。

没有三元环，其实就是一张二分图，题目就很简单了，将所有点平分两份，每次在两份的任意两点之间连边，最后的图就是答案。

代码简单，不必多解释了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long
ll n; 
int main(){
	scanf ("%lld", &n);
	ll s = (n >> 1), t = n - s;
	printf ("%lld\n", s * t);
	for (int i = 1; i <= s; i++)
		for (int j = s + 1; j <= n; j++)
			printf ("%lld %lld\n", i, j);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF41E)

# 题意

给你 $n$ 个点，要求一张联通图 $G$，让这张图有 $n$ 个节点，且没有 $3$ 个节点的环。求最大边数和这张图。

# 思路

没有$3$ 个节点的，很容易想到二分图，就是求两个点集，在里面放上一些点，使得不同集合内的点之间都有连线，且同一集合内的点没有连线，这样就没有三元环，且边数最大。

哪集合大小呢？其实两个集合元素数越接近，边数越多，所以最优的是对半分。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, t; 
int main(){
	scanf ("%d", &n);
	s = (n >> 1);
	t = n - s;
	printf ("%d\n", s * t);
	for (int i = 1; i <= s; i++)
		for (int j = s + 1; j <= n; j++)
			printf ("%d %d\n", i, j);
	return 0;
}

```

---

## 作者：Walter_Fang (赞：0)

### 大致题意
求结点数为 $n$ 并且任意取三结点均为连通图但不是环的无向图的最大边数 $m$，并输出任意一种可能。
### 思路/解析
这是一道抽屉原理的题。我们只需要 $2$ 个抽屉就可以保证任意取 $3$ 个点不可能形成环，因为至少有一个抽屉存在 $2$ 个及以上的点。但是如果将抽屉的数量增加到 $3$ 个，那么就有可能存在没个抽屉 $1$ 个点的情况，这样就有可能存在环。因此，我们只需要 $2$ 个抽屉，并保证同一抽屉内的点不连边，不同抽屉的点连边即可。

对于答案数量，我们只需要平均分成两组就好了。注意当 $n$ 为奇数时需要加 $1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j;
int main(){
	cin>>n;
	if(n%2==1)m=(n/2)*(n/2+1);
	else m=(n/2)*(n/2);
	cout<<m<<'\n';
	for(i=1;i<=n/2;i++)
		for(j=n/2+1;j<=n;j++)
			cout<<i<<' '<<j<<'\n';
}
```

---

## 作者：5k_sync_closer (赞：0)

题意：构造一张点数为 $n$ 的没有三元环的连通无向图，最大化边数。
# 思路
我们知道，[二分图不存在长度为奇数的环](https://oi-wiki.org/graph/bi-graph/#%E6%80%A7%E8%B4%A8)。考虑造一张完全二分图 $K_{x,y}$，此时边数为 $xy$。

问题转化为已知 $x+y=n$，最大化 $xy$。

$$
\begin{aligned}
&xy\\
=&x(n-x)\\
=&-x^2+nx\\
&x_{\text{对}}=\dfrac n2
\end{aligned}
$$

所以 $x$ 取 $\left\lfloor\dfrac n2\right\rfloor$ 时 $xy$ 有最大值 $\left\lfloor\dfrac n2\right\rfloor\left\lceil\dfrac n2\right\rceil$。
# 代码
```cpp
#include <cstdio>
int main()
{
	int n;scanf("%d", &n);
	printf("%d\n", (n >> 1) * ((n >> 1) + (n & 1)));
	for(int i = 1;i <= n >> 1;++i)
		for(int j = (n >> 1) + 1;j <= n;++j)
			printf("%d %d\n", i, j);
	return 0;
}
```


---

