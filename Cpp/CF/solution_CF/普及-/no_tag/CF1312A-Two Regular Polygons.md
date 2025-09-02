# Two Regular Polygons

## 题目描述

You are given two integers $ n $ and $ m $ ( $ m < n $ ). Consider a convex regular polygon of $ n $ vertices. Recall that a regular polygon is a polygon that is equiangular (all angles are equal in measure) and equilateral (all sides have the same length).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/95b1bef3403a130cb1532da909306b47c3e9056c.png) Examples of convex regular polygons Your task is to say if it is possible to build another convex regular polygon with $ m $ vertices such that its center coincides with the center of the initial polygon and each of its vertices is some vertex of the initial polygon.

You have to answer $ t $ independent test cases.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/0982568e883452a4972ef18c303a083c1c1e1608.png) The first test case of the example It can be shown that the answer for the second test case of the example is "NO".

## 样例 #1

### 输入

```
2
6 3
7 3```

### 输出

```
YES
NO```

# 题解

## 作者：立风yu (赞：18)

~~本蒟蒻来写题解了~~

$Update\ $在@Thomas_Cat 的建议下修改了一下公式

题意：有一个正 $m$ 边形和一个正 $n$ 边形 $(m<n)$，这两个正多边形的中心重合，并且正 $m$ 边形的顶点都在正 $n$ 边形的顶点上。

其实这个题画个图就会做了，通过画图我们可以发现，只要 $n$ 是 $m$ 的倍数，也就是 $n\ \bmod\ m = 0$ 的时候，满足题意，输出 `YES` ，$n$ 不是 $m$ 的倍数的时候，输出 `NO` 。

上代码：

```cpp
#include <iostream>
using namespace std;
int main(){
    int t,n,m;//数据范围较小，所以用int就够了
    cin>>t;//t组数据
    for (int i=1;i<=t;i++){
        cin>>n>>m;
        if (n%m==0)cout<<"YES"<<endl;//n是m的倍数，输出"YES"
        else cout<<"NO"<<endl;//反之，输出NO
    }
    return 0;//好习惯
}
```


---

## 作者：do_while_false (赞：5)

这题很简单。

这是一道数学题，因为 $n>m$ ，所以我们不用讨论 $m>n$ 的情况只用讨论 $n>m$ 的情况即可。

![](https://i.loli.net/2020/03/10/BSOymqeMXxP6VfW.png)
观察这张图，我们发现一个规律:

本来(黑色正六边形)的图形相邻两点的距离相等，而要使变化后的图形(红色正三角形)相邻两点的距离相等，我们需要在原来的图形上取所有距离为 $6 \div 3 = 2$ 的点，并相连。通过观察得出，此时变化后的图形中点和变化前的图形中点一致。

![](https://i.loli.net/2020/03/10/qQj5yr1DHz2XklU.png)

再观察这张图，我们可以发现，因为 $5$ 是一个质数，它没有因数，因此在保证中点相同的情况下，不可能找到一个正 $m$ 边形的点在它的顶点上。

由这两个规律，我们可以推广出一个结论:
- 如果 $n\mod m=0$ ，则可以构造出原题要求的图形。
- 否则的话，就不行。

这样我们就能得出以下代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main(void) {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		if(n%m==0) printf("YES\n");//判断条件 
		else printf("NO\n");
	}
	return 0;
}
```
管理员求过,qaq。

---

## 作者：_NUOMI_ (赞：3)

根据题意，所有多边形都是正凸多边形，且中心都在一点上。

设有一个有``m``条边的正多边形(以下简称``M``)和一个有``n``条边的正多边形(以下简称``N``)，且两个多边形中心为一点。

学过圆的朋友们都知道，此时只要做其中一个多边形的外接圆，则另一个多边形顶点都在这个外接圆上。

若``N``的顶点都在``M``上，则``m``至少是``n``的两倍(或是``n``的其他倍数)

**所以若要``N``的顶点都在``M``上，必须有``m mod n=0`` 。**

根据题目，有``t``组数据，只需要一个``while``和一个``if``就行啦！

接下来就很简单了，~~像我这样的蒟蒻都能写出来~~

```cpp
#include<iostream>
using namespace std;
int chara,dong,lin;//t→chara;m→dong;n→lin。坏习惯(？)
int main()
{
    cin>>chara;
    while(chara!=0)
    {
        cin>>dong>>lin;
        if(dong%lin==0)
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }
        chara=chara-1;//下一组数据        
    }
    return 0;//好习惯(确信)
}
```
~~好像我就是大家口中的异教徒？~~ ``⊙⊙``

蒟蒻的第一篇题解，望通过``qwq``

---

## 作者：do_while_true (赞：2)

### 题目翻译

$T$组数据，对于每组数据，给出$n,m$，询问正$n$边形和正$m$变形顶点都重合时中心是否重合($m<=n$)

### 思路分析

十分简单的数学题，想要中心重合，而$m<=n$，所以只要$n$是m的倍数就可以了

接下来是关于这个结论的证明

对于任意正m边形并且m>=3，它的中心就是它的外接圆的圆心(参考于[百度百科](https://baike.baidu.com/item/%E6%AD%A3%E5%A4%9A%E8%BE%B9%E5%BD%A2/1614461?fr=aladdin))

那么如果有另一个正n边形与正m边形中心重合，则这两个多边形外接圆重合，那么我们还要满足**正m边形的m个点**和**正n边形的m个顶点**重合。

而在外接圆上，**正m边形的m个顶点**之间的距离相等，**正n边形的n个顶点**之间的距离相等，如果**正m边形的m个顶点**都和**正n边形的n个顶点中的m个顶点**重合，也就说明正n边形选出来的这**m个顶点**之间的距离相等。

而这m个顶点之间有**m个区间**，这m个区间内所包含的n边形节点个数也要相同。而一共剩下(n-m)个节点，这些节点分布在这m个区间内，想要这m个区间内的节点个数都相等，则必须满足 m是(n-m)的因数，既然m是-m的因数，所以我们只需要满足m是n的因数就可以了。


这里给出我的[评测](https://codeforces.ml/problemset/submission/1312/72794392)

### *Code:*

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(n%m==0) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：Thomas_Cat (赞：0)

对于这样的题目，我们只需要考虑 $n > m$ 即可，无 $n \le m$ 情况（否则不构成题目所属条件）

我们从原图看起：

[![yiqyY4.png](https://s3.ax1x.com/2021/01/29/yiqyY4.png)](https://imgchr.com/i/yiqyY4)

由上图，我们可以发现，所有的三角形的所有顶点都在原六边形的顶点上（$A,C,E$），并且我们发现他们所构成的出三角形以外的部分的三角形全等（$\triangle ABC \cong \triangle AFE \cong \triangle EDC$），因此我们发现，如果顶点数 $m | n$ 即 $n \bmod m = 0$，即可成立。输出 `YES` 。


---

再来看一个反例：

[![yiqOXt.png](https://s3.ax1x.com/2021/01/29/yiqOXt.png)](https://imgchr.com/i/yiqOXt)

我们发现当正方形不在顶点上时是不能成立的，即没有全等和所有的边和中心都是相等的。

---

综上所述，分为两种情况：

- 当 $m | n$ 即 $n \bmod m = 0$ ，会有全等出现，输出 `YES`

- 当 $m \nmid n$ 即 $n \bmod m \ne 0$，不会有全等和边相等出现，输出 `NO`

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
    cin>>t;
    while(t--){
    	int n,m;
        cin>>n>>m;
        if(n%m==0) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
	return 0;
}
```

---

## 作者：梦游的小雪球 (赞：0)

#### ~~这道题似乎只算个小红题啊~~
### 梦雪的思路：
- 如果**m是n的倍数**，那么正m边形的中心与正n边形正多边形的**中心重合**，且正n边形的**顶点都在**正m边形**的顶点上**。([详细解释请参考](https://www.luogu.com.cn/blog/0408Dodgemin/cf1312a-ti-xie))
## 实现代码：
**若思路不清楚请见注释（~~应该也没有什么好看的~~）**
```
#include<bits/stdc++.h>
using namespace std;
int a; //共a组数据
int main(){
	cin>>a;
	while(a--){	//a组数据
		int m,n;
		cin>>m>>n;	//每组的n和m
		if(m%n==0)
			cout<<"YES"<<endl;//如果m是n的倍数
		else
			cout<<"NO"<<endl;
	}
	return 0; 
}
```
望通过（~~感觉一直在努力凑字数~~）

---

## 作者：添哥 (赞：0)

## 吐槽：此题恶评！实际上是个红题！！
#### 前置芝士：小学数学。

------------

> 一个有 $m$ 的倍数条边的正凸多边形，使得这个多边形的中心与给定的 $m$ 边形的中心重合，那么有 $m$ 的倍数条边的正凸多边形的顶点一定都在 $m$ 边形的顶点上。——沃·兹基硕德

不知道这个知识怎么办？没关系，下面有 ~~咱蒟蒻听得懂的~~ 复杂论证过程：

我们来康康下面这个图（自己脚画的，可能不太准确，凑合着看哈~）

![](https://cdn.luogu.com.cn/upload/image_hosting/y1wlxg78.png)

好像上面那个结论其实有那么一点道理呢~

$n$ 边形会有 $n÷m-1$ 个顶点在 $m$ 边形的**任意相邻**两个顶点中间，但是 $m$ 边形的任意相邻两个顶点中间的 $n$ 边形的顶点个数**必须相等**，否则无法形成一个正 $n$ 边形。


------------

所以窝就用简洁明了但不大严谨的语言证明完毕了qaq

#### 所以代码就粗来啦~

```cpp
#include<iostream>
using namespace std;
int main()
{
	int t,n,m;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>m;
		if(n%m==0)//判断是否为倍数
        {
			cout<<"YES"<<endl;
        }
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Leonine (赞：0)

首先我们来理解一下题意。

题目是想让你判断在$n$边形中能否放置$m$边形，且中心点相同。如果你不懂数论~~比如我~~，我们可以列举一下情况。

六边形中可以放置三角形；

![](https://cdn.luogu.com.cn/upload/image_hosting/fp9dw4nv.png)

八边形中可以放置四边形；

![](https://cdn.luogu.com.cn/upload/image_hosting/45b66q63.png)

十边形中可以放置五边形……

![](https://cdn.luogu.com.cn/upload/image_hosting/8wlb5hbx.png)

我们发现，在成立的图形中，$n$总是大于$m$,而且$n$都是$m$的倍数！

再仔细想一想，因为只有$n$边形，可以围住$m$边形，而且，$n$变形中加入$m$边形后留下的空隙，可以是多边形，才能够符合条件！

因为边数最小的多边形是三角形。由此，我们可以得到关键的代码：
```cpp
if(n%m) //n是m的倍数
     	printf("NO \n");//当n不是m的倍数时，条件不成立
   else //当n是m的倍数时，条件成立
   	printf("YES \n");
```


由此，我们得到了正宗的AC代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,n;//输入t次，m边形和n边形
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
        scanf("%d %d",&n,&m);
        if(n%m)
            printf("NO \n");//注意，这里输出的是大写的“NO”
        else
            printf("YES \n");//注意，这里输出的是大写的“YES”
    }
    return 0;
}
 
```
看懂了么，点个赞再走啊。

第一次交题解，管理员大大求过。
 

---

## 作者：Andrewzdm (赞：0)

# [CF1312A Two Regular Polygons](https://www.luogu.com.cn/problem/CF1312A)
这题是道数学题没错，不过是道特别简单的数学题。

很明显只要 $n\ mod\ m=0$ 答案就是 `YES`，否则就是 `NO` 。

这是因为我们要让两个凸正多边形的中心重合且两个多边形有若干个重合的顶点。下图是一个例子：

![图例](https://cdn.luogu.com.cn/upload/image_hosting/0v0ewjvv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

接下来我把含有 $m$ 条边的正多边形简称为红色多边形，把含有 $n$ 条边的正多边形简称为黑色多边形。

首先两个正多边形内接于同一个圆。黑色多边形的中心角是 $360\degree/n$ ，红色多边形的中心角是$360\degree/m$ 。

为了确保红色多边形的顶点都与黑色多边形的顶点重合，所以要让 $(360\degree/m)\ mod\ (360\degree/n)=0$ ，因此我们可以得到 $n\ mod\ m=0$ 。

因为题目明确规定 $m<n$ ，所以不需要考虑别的情况。

代码如下：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n, m;
		cin >> n >> m;
		if(n % m == 0)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
```
~~这道题好像真的没有什么可说的……~~

---

