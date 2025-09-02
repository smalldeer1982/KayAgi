# 「EZEC-4」paulzrm Loves Array

## 题目背景

原题面：

$\color{gray}\text{zrmpaul}$ has an array consisting of $n$ integers: $a_1,a_2,...,a_n$. The initial value of $a_i$ is $i(1\le i\le n)$. There are $m$ operations, including four types as follows.

Type $1$: `1` sort the array.   
Type $2$: `2` sort the array and reverse it.   
Type $3$: `3 x y` swap $a_x,a_y$. **It is guaranteed that $x$ is not equal to $y$, and $1\leq x ,y \leq n$**.    
Type $4$: `4` reverse the array.

You need to output the array after $m$ operations.

First line with two intergers $n,m(1\leq n,m\leq 10^6)$.

Next $m$ lines are the operations.

One line, $n$ numbers, the array.

## 题目描述

小 Z 有一个下标从 $1$ 开始并且长度为 $n$ 的序列，初始时下标为 $i$ 位置的数字为 $i$。有 $m$ 个操作，每个操作会是以下四种之一。

- `1` 对序列从小到大进行排序。
- `2` 对序列从小到大进行排序后将其翻转，(译者注：就是从大到小排序）。
- `3 x y` 将下标为 $x,y$ 的数交换位置。保证 $x\neq y$ 且 $1\le x,y\le n$。
- `4` 将序列翻转。

你要输出在 $m$ 次操作后的序列。

## 说明/提示

【数据范围】

**【本题采用捆绑测试】**

subtask 1（24pts）: $1\leq n,m\leq 2 \times 10^3$ 。

subtask 2（13pts）: 没有操作三。

subtask 3（63pts）: $1\leq n,m\leq 10^6$ 。


【样例解释】

序列经过的操作为：
> $1, 2, 3, 4, 5$     
$1, 2, 3, 4, 5$   
$5, 4, 3, 2, 1$   
$5, 2, 3, 4, 1$   
$1, 4, 3, 2, 5$   
$5, 4, 3, 2, 1$



## 样例 #1

### 输入

```
5 5
1
2
3 2 4
4
3 1 5```

### 输出

```
5 4 3 2 1```

# 题解

## 作者：RedLycoris (赞：15)

这里是官方题解

---

考虑到在所有的排序操作之后，之前的所有操作都会没有用。

所以我们只需要找到最后的一个排序操作后处理即可。

对于翻转，我们只需要设定一个变量$x$。

如果是正序，$x=0$，反之，$x=1$ 

如果翻转了，$x=1-x$

如果交换了：

当 $x=0$ 时 $swap(a[l],a[r])$ 

当 $x=1$ 时 $swap(a[n-l+1],a[n-r+1])$

最后输出即可。 

Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool rev;
int ope[1000005];
int x[1000005],y[1000005];
int arr[1000005];
int main(){
	int n,m,lst;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)arr[i]=i;
	for(int i=1;i<=m;++i){
		scanf("%d",ope+i);
		if(ope[i]==3)scanf("%d%d",x+i,y+i);
	}
	for(lst=m;lst;--lst)if(ope[lst]==1 or ope[lst]==2)break;
	if(ope[lst]==2)rev=1;
	else rev=0;
	for(int i=lst+1;i<=m;++i){
		if(ope[i]==3){
			if(not rev)swap(arr[x[i]],arr[y[i]]);
			else swap(arr[n-x[i]+1],arr[n-y[i]+1]);
		}else rev=1-rev;
	}
	if(rev==0)for(int i=1;i<=n;++i)printf("%d ",arr[i]);
	else for(int i=n;i;--i)printf("%d ",arr[i]);
	return 0;
}
```

---

## 作者：hensier (赞：3)

[在个人博客中体验更佳](https://shenyouran.github.io/P6823/)

我们来逐一分析三个子任务，并一一应对。

### $\text{Subtask 1: 暴力枚举}$

期望得分：$24$ 分

时间复杂度：$\mathcal O(mn \log n)$

我们可以调用下列的 `STL` 函数，并结合 `greater` 容器来完成模拟：

|操作编号|函数|用法|时间复杂度|说明|
| :----------: | :----------: | :----------: | :----------: | :----------: 
|$1$|[`sort`](https://zh.cppreference.com/w/cpp/algorithm/sort)|将 $a$ 数组从小到大排列：`sort(a+1,a+n+1);`|$\mathcal O(n \log n)$|无|
|$2$|[`sort`](https://zh.cppreference.com/w/cpp/algorithm/sort)|将 $a$ 数组从大到小排列：`sort(a+1,a+n+1,greater<int>());`|$\mathcal O(n \log n)$|用容器 [`greater<int>`](https://zh.cppreference.com/w/cpp/utility/functional/greater) 可以将排列顺序改为从大到小|
|$3$|[`swap`](https://zh.cppreference.com/w/cpp/algorithm/swap)|将 $a,b$ 两个数的值交换：`swap(a,b);`|$\mathcal O(1)$|无|
|$4$|[`reverse`](https://zh.cppreference.com/w/cpp/algorithm/reverse)|将 $a$ 数组反转：`reverse(a+1,a+n+1);`|$\mathcal O(n)$|无|

`C++` 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000001];
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=i;
    while(m--)
    {
        switch(read())
        {
            case 1:
            {
                sort(a+1,a+n+1);
                break;
            }
            case 2:
            {
                sort(a+1,a+n+1,greater<int>());
                break;
            }
            case 3:
            {
                int x,y;
                scanf("%d%d",&x,&y);
                swap(a[x],a[y]);
                break;
            }
            case 4:
            {
                reverse(a+1,a+n+1);
                break;
            }
        }
    }
    for(int i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}
```

### $\text{Subtask 2: 特殊处理}$

期望得分：$13$ 分

时间复杂度：$\mathcal O(m)$

我们可以将所有的操作均保存在数组里。由于 $\text{Subtask 2}$ 中没有操作 $3$，因而不妨找到最后一个排序操作，再往后查看反转操作。如果反转操作个数为奇数，则反转整个序列，否则序列保持不变。

`C/C++` 代码如下：

```cpp
#include<stdio.h>
#include<stdbool.h>
int n,m,p,opt[1000001];
bool rev;
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)opt[i]=read();//由于没有操作 3，故每行只需要输入一个数即可
    for(int i=m;i;i--)
    {
        if(opt[i]<3)//找到最后一个排序操作
        {
            p=i;
            break;
        }
    }
    /*
    由于没有操作 3，因而第 m 次操作之后只能有操作 4，其数量为 m-p 次。
    条件 1：m-p 模 2 余 1。
    条件 2：最后一次排序为从大到小。
    如果上述条件有偶数个成立，那么不需要反转，否则需要反转。
    这时就可以用到异或运算（xor）。异或运算规定两个 bool 类型的变量若相同，则运算结果为 0，反之为 1。
    例：
    false xor false = false
    false xor true = true
    true xor false = true
    true xor true = false
    从上述情形中可以发现，这正好能满足我们的需求。因而反转条件可以按照这个思路编写。
    */
    if(((m-p)&1)^(opt[p]==2)for(int i=n;i;i--)printf("%d ",i);//a&1 与 a%2 等价
    else for(int i=1;i<=n;i++)printf("%d ",i);//不需要反转则从 1 到 n 直接输出
    return 0;
}
```

### $\text{Subtask 3: 全面考虑}$

期望得分：$100$ 分

时间复杂度：$\mathcal O(m)$

类比 $\text{Subtask 2}$ 的做法，我们可以将所有操作保存到数组中，找到最后一个排序操作的编号，然后依次进行后续的操作。

对于 $a_x,a_y$ 的交换，如果序列目前被倒置，那么其等同于交换 $a_{n-x+1},a_{n-y+1}$。我们可以根据反转次数的奇偶性来判断应当交换哪两个数字。

`C/C++` 代码如下：

```cpp
#include<stdio.h>
#include<stdbool.h>
int n,m,p,a[1000001],opt[1000001][3];
bool flag,rev;
void swap(int x,int y)//这个手写函数传递的是下标，方便进行交换
{
    int t=a[x];
    a[x]=a[y];
    a[y]=t;
}
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=i;
    for(int i=1;i<=m;i++)
    {
        opt[i][0]=read();
        if(opt[i][0]==3)
        {
            opt[i][1]=read();
            opt[i][2]=read();
            flag=true;//出现操作 3 则标记 flag 为 true
        }
    }
    for(int i=m;i;i--)
    {
        if(opt[i][0]<3)
        {
            p=i;
            break;
        }
    }
    if(flag)//判断是否含有操作 3
    {
        if(opt[p][0]==2)rev=true;//特判最后一个排序操作从大到小
        for(int i=p+1;i<=m;i++)
        {
            if(opt[i][0]==3)
            {
                //判断当前序列是否为正序
                if(rev)swap(n-opt[i][1]+1,n-opt[i][2]+1);
                else swap(opt[i][1],opt[i][2]);
            }
            else rev^=true;//将 rev 进行异或 true 的运算（即原来 true 变为 false，原来 false 变为 true）
        }
    }
    else if(((m-p)&1)^(opt[p][0]==2))rev=true;
    if(rev)for(int i=n;i;i--)printf("%d ",a[i]);
    else for(int i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：Remake_ (赞：2)

由于我在打比赛时太菜想不出正解，所以只能打暴力qwq，结果一不小心用暴力过了，来发篇题解。

首先我们来看看裸的暴力，暴力```sort```+暴力```reverse```，时间复杂度为$\operatorname{O}(mn\log n)$，面对如此强大的数据范围很明显卡不过去。

考虑优化qwq，首先我们发现在一次排序操作之后，前面的所有操作都将没有用，所以我们找到最后一个排序操作，然后从这个操作开始执行，我们发现加了这个优化之后程序快了很多，但是还是卡不过去。

那么接下来再分享一个优化，即对于连续的$k$次```reverse```，可以将其转化为$(k \operatorname{mod}2)$次```reverse```，这个东西挺好证的吧，因为连续的两次```reverse```可以相互抵消。

大的优化至此已经结束，~~这个程序加上火车头已经可以过了~~，但是在真实的比赛中是用不了火车头的qwq，那么我们来卡常：

* $1,$关输入输出同步流。

* $2,$循环用```register int```

* $3,$STL的```reverse```贼慢，我们手写来优化常数

然后......就过了qwq，[AC
记录](https://www.luogu.com.cn/record/38239900)。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, opt[1000005], x[1000005], y[1000005], a[1000005], start = 1, cnt;
void rvs()
{
    for (register int i = 1; i <= n / 2; ++i)
        swap(a[i], a[n - i + 1]);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (register int i = 1; i <= n; ++i)
        a[i] = i;
    for (register int i = 1; i <= m; ++i)
    {
        cin >> opt[i];
        if (opt[i] == 3)
            cin >> x[i] >> y[i];
        if (opt[i] == 1 || opt[i] == 2)
            start = i + 1;
    }
    if (opt[start - 1] == 2)
        rvs();
    for (register int i = start; i <= m; ++i)
    {
        if (opt[i] == 4)
            ++cnt;
        else
        {
            if (cnt % 2)
                rvs();
            swap(a[x[i]], a[y[i]]);
            cnt = 0;
        }
    }
    if (cnt % 2)
        rvs();
    for (register int i = 1; i <= n; ++i)
        cout << a[i] << ' ';
}
```

话说数据理论上讲可以把我的代码卡到$\operatorname{O}(mn)$，但是我深得面向数据编程的精髓（逃

---

## 作者：genshy (赞：2)

## 前言

比赛时，没注意到一个坑点，一直卡了我一个小时。

## 题解

首先，我们会发现一个问题，那就是操作一以及操作二之前的操作都是无用的。

因为无论你怎么变，到最后都是升序排列或者降序排列。

这样，我们就得到了一个大概的思路，找到最后一个操作二或者是操作一。

然后对剩下的操作进行暴力修改。

然后这样你会发现比朴素的暴力要多过几个点，但还是会 TLE，说明我们的算法

还可以在优化一下。

我们考虑一下，对于连续的操作四，我们不必要每次都暴力 $sawp$ 一下。

实际上，经过偶数次操作四后，原序列保持不变，经过奇数次之后，

直接暴力 $swap$ 就可以啦。

我们记录一个 $tag$ 表示连续的操作四的个数，每遇到一个操作三，

看看当前的 $tag$ 值，如果是偶数，我们不需要对原序列进行操作，

反之暴力 $swap$ ，之后在交换操作三两个数的值。

**Update**

以上做法，在比赛的时候是可以稳过的，但赛后出题人加强了一下数据，就被卡住了。

我们还可以在优化一下，每次操作三，我们涉及到的只会是两个地方的值，

所以我们没必要对整个序列都 $swap$ 一下。

我们还是记录一个 $tag$ 如果 $tag$ 是奇数，表明此时序列是倒序的，

那我们就需要交换的是  $n-x+1$ 和 $n-y+1$这两个地方的值，

反之交换 $x$ 和 $y$ 这两个地方的值。

到最后如果 $tag$ 是奇数就倒序输出，反之正序。

**一个比较坑的点**：

他可能没有操作一或者操作二，所以我们要在一开始给整个序列赋个初值。

**code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,type,maxn,res = 0,cnt,a[1000010];
struct node
{
	int opt,x,y;
}q[1000010];
inline int read()
{
    int s = 0,w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){s =s * 10+ch - '0'; ch = getchar();}
    return s * w;
}
int main()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = i;//给整个序列赋个初值
	for(int i = 1; i <= m; i++)//把操作离线下来
	{
		q[i].opt = read();
		if(q[i].opt == 3)
		{
			cnt++;
			q[i].x = read(); q[i].y = read();
		}
		if(q[i].opt == 1 || q[i].opt == 2)//找到最后一个操作一或者操作二·
		{
			type = q[i].opt; maxn = i;//type 记录最后一次操作的种类
		}
	}
	if(type == 1)//如果最后一次是操作一，就升序排列，反之降序排列
	{
		for(int i = 1; i <= n; i++) a[i] = i;
	}
	if(type == 2)
	{
		for(int i = n; i >= 1; i--) a[i] = n-i+1;
	}
	for(int i = maxn+1; i <= m; i++)
	{
		if(q[i].opt == 3)
		{			
		    if(res & 1)//1表示当前序列是倒许排列
			{
				swap(a[n-q[i].x+1], a[n-q[i].y+1]);
			}
			else swap(a[q[i].x],a[q[i].y]);
		}
		else if(q[i].opt == 4) res ^= 1;//一个小技巧，亦或一，和累加是相似的
	}
	if(res & 1) for(int i = 1; i <= n/2; i++) swap(a[i],a[n-i+1]);//如果最后的tag是1，表明当前是倒序的，swap一下就可以啦
	for(int i = 1; i <= n; i++) printf("%d ",a[i]);
	return 0;
}
```



---

## 作者：wzkdh (赞：1)

~~这道题只有四个基本操作，但是竟然不是红题，可见有坑...~~

第一眼看到这个题，没注意数据范围，直接朴素写法，结果肯定是tle一片。。。

那么我们来考虑一下优化：

首先操作一和操作二都是排序，无论排序之前是什么顺序，排序之后都是一样的顺序，所以在最后一次排序之前的所有操作都是没有意义的。所以我们可以将所有操作存到一个数组之中，从后向前查找最后一个操作一或者操作二，然后之后的操作从这里开始，就可以省去之前所有的操作。

加上这个优化并之后提交发现第二组数据依旧tle，我们可以看到第二组数据保证没有操作三，而我们的优化可以使程序只需运行一次操作一或者二，所以可以易得数据二中在最后一个排序操作后有大量的操作四，而操作四是翻转序列，两次翻转就等于啥也没干，所以我们可以数出排序后操作四的次数，如果为奇数，就翻转，偶数则不需操作。具体方法我们可以定义一个变量$x$=0,每找到一个操作四就令$x$=1-$x$，就可以实现判断奇偶。

至于代码，因为是赶时间写出来的，所以看上去可能很烂（就是很烂。。。）不过考虑到~~题解通过率~~帮助大家理解，还是放上来吧，大佬轻喷qwq。。。

```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,m,a[1000010],b[1000010],st=1,b1[1000010],b2[1000010],bj;
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		a[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		if(b[i]==3)
		{
			scanf("%d%d",&b1[i],&b2[i]);
			bj=1;
		}
	}
	for(int i=m;;i--)
	{
		if(b[i]==1||b[i]==2)
		{
			st=i;
			break;
		}
	}
	if(bj==0)
	{
		if(b[st]==1)
			sort(a+1,a+1+n);
		else if(b[st]==2)
			sort(a+1,a+1+n,cmp);
		int f=m-st;
		if(f%2)
		{
			reverse(a+1,a+1+n);
		}
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
		return 0;
	}
	for(int i=st;i<=m;i++)
	{
		if(b[i]==1)
			sort(a+1,a+1+n);
		else if(b[i]==2)
			sort(a+1,a+1+n,cmp);
		else if(b[i]==3)
		{
			int e;
			e=a[b1[i]];
			a[b1[i]]=a[b2[i]];
			a[b2[i]]=e;
		}
		else if(b[i]==4)
			reverse(a+1,a+1+n);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}

---

## 作者：张驰666 (赞：1)

这题其实就是~~简单的~~模拟，数据也~~不是很强~~

所以这题就只有**入门的难度**

其实想法很容易得到：

1.如果直接进行翻转的操作，会很复杂，那么就定义一个flag数组来标记当前数组本来应该是正的(```flag=false```)或者反的(```flag=true```)，最后再根据flag正向或者反向输出。

2.第一个操作和第二个操作其实都有初始化的功能。举个例子：```1 4 3 5 2``` 进行1号操作变成```1 2 3 4 5```，进行了2号操作变成```5 4 3 2 1```，之前进行了什么操作并没有什么关系，于是我们可以记录最后一个1或者2，再从对应位置进行后面的操作。（具体操作可以见代码）（代码里没有```sort```是因为第一次初始化之后数组就是从小到大升序排列的）

3.交换时要判断一下当前是正向还是反向的，举个例子，a数组（存储数字的数组）里的数字是：```1 7 5 3 4 2 6```，交换第4个和第6个数字，若是正向的，操作完就是：```1 7 5 2 4 3 6```，若是反向的，则就是：```1 3 5 7 4 2 6``` 。 由此可以得出：（其中q是存储问题的，详见代码）
```cpp
if(flag==false)	swap(a[q[i][1]],a[q[i][2]]);
else	swap(a[n-q[i][1]+1],a[n-q[i][2]+1]);
```

这就是大体的思路，虽然不是最优解，但AC还是足够了。

## 下面是AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x=1,q[1000005][3],a[1000005];//q数组存储问题，a数组存储数字 
bool flag=false;//flag来表示数组正反，flag=false正向输出,反之就反向 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	a[i]=i;//初始化 
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&q[i][0]);//读入 
		if(q[i][0]==1 || q[i][0]==2)	x=i;//记录最后的1或2（因为1或2具有初始化的功能） 
		if(q[i][0]==3)	scanf("%d%d",&q[i][1],&q[i][2]);//3号的读入一共3个 
	}
	if(q[x][0]==1)	x++;
	if(q[x][0]==2)	flag=true,x++;//执行最后的1或2 
	for(int i=x;i<=m;i++)
	{
		if(q[i][0]==3)
		{
			if(flag==false)	swap(a[q[i][1]],a[q[i][2]]);//正向交换 
			else	swap(a[n-q[i][1]+1],a[n-q[i][2]+1]);//反向交换是与正向交换不一样的 
		}
		if(q[i][0]==4)	flag=!flag;//改变正反向 
	}
	if(flag==false)	for(int i=1;i<=n;i++)	printf("%d ",a[i]);//正向输出 
	else	for(int i=n;i>=1;i--)	printf("%d ",a[i]);//反向输出 
}
```

**注**： _这是蒟蒻第一次写题解，可能有不足的地方，欢迎指出！~_ 

---

## 作者：EdisonBa (赞：0)

## P6823 zrmpaul Loves Array 题解

#### 题目链接

<https://www.luogu.com.cn/problem/P6823>

#### 题目分析

这道题是一个很不错的锻炼代码能力的题，主要思路是模拟。

注意：如果中出现任意一个 $1$ 或 $2$ ，那么它前面的顺序就会被打乱。所以我们只要在所有操作中从后往前找第一个 $1$ 或 $2$ ，来确定起始位置。

我们可以把序列用数组 `len1[i]` 来存储。因为下面会进行翻转操作，为了方便，我们可以再开一个数组 `len2[i]` 来帮助操作。

对于操作1：直接正序存入数组1。

对于操作2：直接倒序存入数组1。

对于操作3：可以用 swap 函数交换数组中两数的位置。

对于操作4：我们可以把数组1中的数正序存入数组2，再把数组2反向输出到数组1.

在这里需要注意一点，如果有两个操作4挨在了一起，那么它们两个就可以相互抵消。我们要判断有无这种情况。



#### 代码

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=1000035;

struct node{ //为了判断最后的1或2，我们需要把每种操作存起来
	ll id,x,y;
}t[maxn];

ll len1[maxn],len2[maxn];

int main()
{
	
	ll n,m;
	n=read();
	m=read();
	for(int i=1;i<=n;++i)//先初始化
	{
		len1[i]=i;
	}
	
	ll cz=0;//cz用来记录操作种类
	for(ll i=1;i<=m;++i)
	{
		cz=read();
		t[i].id=cz;
		if(cz==3) 
		{
			t[i].x=read();
			t[i].y=read();
		}
	}
	
	ll left; //left记录最后的1或2 出现的位置
	for(ll i=m;i>=1;--i)
	{
		if(t[i].id==1 || t[i].id==2)
		{
			left=i;//记录
			break;
		}
	}
	
	for(ll k=left;k<=m;++k)
	{
		if(t[k].id==1)
			for(ll i=1;i<=n;++i)
				len1[i]=i;
				
		else if(t[k].id==2)
		{
			ll j=n;
			for(int i=1;i<=n;++i)
			{
				len1[i]=j;
				j--;
			}	
		}
		
		else if(t[k].id==4)
		{
			if(t[k+1].id==4) //此处特判两个4挨在一起的情况
			{
				k++; //这里k只能+1，因为continue之后k还会+1，这样才一共+2
				continue;
			}
			
			ll j=n;
			for(ll i=1;i<=n;++i) //倒序存入数组2
			{
				len2[i]=len1[j];
				j--;
			}
			
			for(int i=1;i<=n;++i) //再返回到数组1
			{
				len1[i]=len2[i];
			}
		}
		
		else if(t[k].id==3)
		{
			ll xx=t[k].x;
			ll yy=t[k].y;
			swap(len1[xx],len1[yy]); //交换两数的位置
		}
	}
	
	for(ll i=1;i<=n;++i)
	printf("%lld ",len1[i]); //输出操作完毕的序列
	return 0;	
}
```

![](<https://img2020.cnblogs.com/blog/2101156/202009/2101156-20200908173630499-153371706.png>)

解决方法：卡常 or 吸氧



---

## 作者：晴耕雨读罢了 (赞：0)

首先直接模拟会炸得分24分。

# 附上代码
```
#include<bits/stdc++.h>//万能头 
using namespace std;
int n,m,a[1000005];
struct data{
	int id,y,x;
}b[1000005];
int cmp1(int a,int b)//从大到小排 
{
    return a>b;
}
void fz(){
	for (int i=1;i<=n/2;i++) {
		swap(a[i],a[n-i+1]);
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[i]=i;//初始化数组
	for(int i=1;i<=m;i++){
		cin>>b[i].id;
		/* 判断操作 */ 
		if(b[i].id==1){
		    sort(a+1,a+n+1);//从小到大排		 
	    } 
	    if(b[i].id==2){
	    	sort(a+1,a+n+1,cmp1);
		}
		if(b[i].id==3){
			cin>>b[i].x>>b[i].y;
			swap(a[b[i].x],a[b[i].y]);
		}
		if(b[i].id==4){
		    fz();
		}
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
} 
```


------------
那么则么做呢？

这里运行1,2中排序后前面操作会不算。

找到最后一个排序即可
# 附上主要代码
## 记录位置
	for(int i=1;i<=m;i++){
		cin>>b[i].id;
		if(b[i].id==3)cin>>b[i].x>>b[i].y;
		if(b[i].id==2||b[i].id==1){
			zhz=max(zhz,b[i].id);
			jh=b[i].id;
		}
	}
```
## 倒排```
void fz(){
	for (int i=1;i<=n/2;i++) {
		swap(a[i],a[n-i+1]);
	}
}
```



---

## 作者：过往梦魇之殇 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P6823)

**思路简述:**

因为数字（总体上来看）不会发生改变，所以每次排序后都会变成$1,2,\ldots,n$或者$n,(n-1),\ldots,1$的形式。

所以我们从最后一个排序操作开始做模拟，并标记反转（反转两次=不反转）

若不反转，执行操作三的时候交换的应该是$a[x]$ $and$ $a[y]$

反转标记为$1$时，则交换的应该是$a[n-x+1]$ $and$ $a[n-y+1]$

大致思路如上。

**代码展示:**
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int maxn=1e6+10;
int n,m,flag,last,x[maxn],y[maxn],opt[maxn];
int a[maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(re int i=1;i<=n;++i){
		a[i]=i;
	}
	for(re int i=1;i<=m;++i){
		scanf("%d",&opt[i]);
		if(opt[i]==1||opt[i]==2){
			last=i;
		}
		if(opt[i]==3){
			scanf("%d%d",&x[i],&y[i]);
		}
	}
	if(last) flag=(opt[last]==1)?0:1; 
	for(re int i=last+1;i<=m;++i){
		if(opt[i]==4){
			flag=1-flag;
		}
		if(opt[i]==3){
			if(flag){
				swap(a[n-x[i]+1],a[n-y[i]+1]);
			}
			else{
				swap(a[x[i]],a[y[i]]);
			}
		}
	}
	if(flag){
		for(re int i=n;i>=1;--i){
			printf("%d ",a[i]);
		}
	}
	else{
		for(re int i=1;i<=n;++i){
			printf("%d ",a[i]);
		}
	}
	return 0;
}
```
> $Thanks$ $For$ $Watching!$

---

## 作者：calcio (赞：0)

签到题还是有点思维难度的，但也比至于那么难，不过需要注意的点比较多。

自己在一个点上卡了一个小时（太菜了，该退役了）。

现讲一下思路吧。观察一下这四个操作，你就会发现一个神奇的规律。

在排序操作之前的操作是对答案没有任何影响的。

所以，我们只需要找到最后的一个操作1 或者操作 2 ，如果最后一次是操作 1 原序列就正着排，反之倒着排序。

之后，我们就可以模拟操作三和操作四了。

操作三直接暴力 swap ，操作四的话可以打个标记，奇数的把这个序列暴力翻转。

一个比较坑的点就是一开始要把原序列赋为从 1−n 的排列,(因为他可能只有操作 4)

随机数据的话还是跑的比较快的。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,type,maxn,res,cnt,a[1000010];
struct node
{
	int opt,x,y;
}q[1000010];
inline int read()
{
    int s = 0,w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){s =s * 10+ch - '0'; ch = getchar();}
    return s * w;
}
int main()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = i;//一开始序列为1-n 的排列
	for(int i = 1; i <= m; i++)
	{
		q[i].opt = read();
		if(q[i].opt == 3)
		{
			cnt++;
			q[i].x = read(); q[i].y = read();
		}
		if(q[i].opt == 1 || q[i].opt == 2)//找最后一次排序操作
		{
			type = q[i].opt; maxn = i;
		}
	}
	if(type == 1)//如果是 1 就升序排列
	{
		for(int i = 1; i <= n; i++) a[i] = i;
	}
	if(type == 2)//反之降序排列
	{
		for(int i = n; i >= 1; i--) a[i] = n-i+1;
	}
	for(int i = maxn+1; i <= m; i++)
	{
		if(q[i].opt == 3)
		{			
		    if(res & 1)//如果前面序列反转了偶数次，就对序列暴力翻转
			{
				for(int j = 1; j <= n/2; j++) swap(a[j],a[n-j+1]);
			}
			swap(a[q[i].x],a[q[i].y]);//暴力交换
			res = 0;
		}
		else if(q[i].opt == 4) res += 1;//统计有多少个操作 4
	}
	if(res & 1) for(int i = 1; i <= n/2; i++) swap(a[i],a[n-i+1]);
	for(int i = 1; i <= n; i++) printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：happybob (赞：0)

这个题目费了我好久啊，如果数据小一点，真的就是暴力红题，sort+reverse就ok了，但是最重要的问题还是数据

n, m <= 10^6

10^6 = 1000000

我们先想一下，如果从0开始循环到n-1，加上sort和reverse，肯定TLE，不过这么写也能拿Subtask #1的24分

其实我们只要找到最后一个从大到小或者从小到大枚举不就OK了吗？几天前这么写是AC了，但#22是个防止暴力过的新数据点，TLE卡了很多人啊。

首先如果翻转数组用reverse会TLE更多点，所以自己写个循环，但#22还过不了。

现在注意了，翻转其实不用真得翻转，只要bool flag翻转时 flag = !flag，在指令3swap时判断，如果flag为true的话从右往左数格子交换，不然就从左往右可以了

代码出来，费了我几天啊，~~建议改为普及~~

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[1000005], num[1000005], x[1000005], y[1000005];

int main()
{
    bool flag = true;
    int n, m, cur = 0, cnt = 0, cnt2 = 0, xb = 0;
    scanf("%d %d", &n, &m);
    for(register int i = 0; i < m; ++i)
    {
        scanf("%d", &num[i]);
        if(num[i] == 3)
        {
            scanf("%d %d", &x[cur], &y[cur]);
            ++cur;
        }
        if(num[i] == 1 || num[i] == 2)
        {
            xb = i;
        }
    }
    for(register int i = 0; i < n; ++i)
    {
        arr[i] = num[xb] == 1 ? i + 1 : n - i;
    }
    for(register int i = 0; i < xb; ++i)
    {
        if(num[i] == 3)
        {
            ++cnt;
        }
    }
    for(register int i = xb + 1; i < m; ++i)
    {
        if(num[i] == 3)
        {
            if(!flag)
            {
                register int temp2 = arr[n - x[cnt]];
                arr[n - x[cnt]] = arr[n - y[cnt]];
                arr[n - y[cnt]] = temp2;
                cnt++;
            }
            else
            {
                register int temp2 = arr[x[cnt] - 1];
                arr[x[cnt] - 1] = arr[y[cnt] - 1];
                arr[y[cnt] - 1] = temp2;
                cnt++;
            }
        }
        else if(num[i] == 4)
        {
            flag = !flag;
        }
    }
    if(flag)
    {
        for(register int i = 0; i < n; ++i)
        {
            printf("%d ", arr[i]);
        }
    }
    else
    {
        for(register int i = n - 1; i >= 0; --i)
        {
            printf("%d ", arr[i]);
        }
    }
    return 0;
}
```



---

## 作者：loceaner (赞：0)

## 思路

和官方题解思路竟然一样……

显然如果找到了最后一个排序操作那么之前的操作可以忽略。

找到最后一个排序操作，如果是 $1$ 操作就将数组正向赋值，如果是 $2$ 操作就反向赋值。

用一个标记记录现在的数组是翻转了还是未翻转，如果未翻转则三操作直接翻转 $x$ 和 $y$，否则翻转 $n-x+1$ 和 $n - y + 1$。（很好理解，想想看）

然后最后看看当前状态是翻转还是未翻转，如果翻转了就倒序输出，否则正序输出。

## 代码

```cpp
/*
  Time: 18/09/20 20:15
  Author: Loceaner
  Description: 
  Debug: m写成n 
*/
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 1e6 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int n, m, a[A], last, opt;
struct node { int opt, x, y; } cz[A];

int main() {
  n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int lx = read();
    if (lx == 1 || lx == 2) last = i, opt = lx;
    if (lx == 3) {
      int x = read(), y = read();      
      cz[i].x = x, cz[i].y = y;
    }
    cz[i].opt = lx;
  }
  if (opt == 2) for (int i = 1; i <= n; i++) a[i] = n - i + 1; 
  else for (int i = 1; i <= n; i++) a[i] = i;
  int flag = 0;
  for (int i = last + 1; i <= m; i++) {
    if (cz[i].opt == 3) {
      if (!flag) swap(a[cz[i].x], a[cz[i].y]);
      else  swap(a[n - cz[i].x + 1], a[n - cz[i].y + 1]);     
    }
    else flag ^= 1;
  }
  if (!flag) for (int i = 1; i <= n; i++) cout << a[i] << " ";
  else for (int i = n; i >= 1; i--) cout << a[i] << " ";
  return 0;  
}
```

---

## 作者：tribool4_in (赞：0)

看到这题第一印象是：暴力？

一看范围：$1\le n,m\le10^6$，没希望了（~~尽管据说能卡过~~）......

回到正题。根据题目易知，**前面不管有多少个操作，一次排序（1、2 操作）便前功尽弃**。所以我们可以**找到最后一次排序操作，从那里开始进行操作**，这样便省去了不少操作。

但是这样还是过不了（~~除非卡常~~）。现在有 2 种操作，翻转和交换。这两种操作如何优化呢？

![https://cdn.luogu.com.cn/upload/image_hosting/w5t4sh3z.png](https://cdn.luogu.com.cn/upload/image_hosting/w5t4sh3z.png)

见图，我们只需定义一个 $bool$ 变量 $ r $ 来表示是否翻转，每次翻转只需执行 ```r = 1 - r``` 即可。那交换呢？

由图可知，假设我们要交换 $i,j$。

如果没有交换过（$r=0$），则直接交换 $i,j$；

如果有交换过（$r=1$），则交换 $(n-i+1),\ (n-j+1$) 。

最后，如果 $r=0$，直接输出原数组；如果 $r=1$，翻转后输出。完成！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, last;
bool r;
int cmd[N];
int x[N], y[N];
int a[N];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) a[i] = i;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", cmd + i);
        if (cmd[i] == 3) scanf("%d%d", x + i, y + i);
    }
    for (last = m; last; --last) if (cmd[last] == 1 or cmd[last] == 2) break;
    if (cmd[last] == 2) r = 1;
    else r = 0;
    for (int i = last + 1; i <= m; ++i) {
        if (cmd[i] == 3) {
            if (!r) swap(a[x[i]], a[y[i]]);
            else swap(a[n - x[i] + 1], a[n - y[i] + 1]);
        } else r = 1 - r;
    }
    if (r == 0) for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
    else for (int i = n; i; --i) printf("%d ", a[i]);
    return 0;
}
```


---

