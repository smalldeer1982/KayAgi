# Lucky Tickets

## 题目描述

Vasya thinks that lucky tickets are the tickets whose numbers are divisible by 3. He gathered quite a large collection of such tickets but one day his younger brother Leonid was having a sulk and decided to destroy the collection. First he tore every ticket exactly in two, but he didn’t think it was enough and Leonid also threw part of the pieces away. Having seen this, Vasya got terrified but still tried to restore the collection. He chose several piece pairs and glued each pair together so that each pair formed a lucky ticket. The rest of the pieces Vasya threw away reluctantly. Thus, after the gluing of the $ 2t $ pieces he ended up with $ t $ tickets, each of which was lucky.

When Leonid tore the tickets in two pieces, one piece contained the first several letters of his number and the second piece contained the rest.

Vasya can glue every pair of pieces in any way he likes, but it is important that he gets a lucky ticket in the end. For example, pieces 123 and 99 can be glued in two ways: 12399 and 99123.

What maximum number of tickets could Vasya get after that?

## 样例 #1

### 输入

```
3
123 123 99
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
1 1 1 23 10 3
```

### 输出

```
1
```

# 题解

## 作者：Plozia (赞：8)

[博客阅读效果更佳！](https://blog.csdn.net/BWzhuzehao/article/details/104290289)

题目大意：

给出 $N$ 个数，分别为 $a_1,a_2,...,a_n$ 。将其中任意两个数进行首尾相接组合，**每个数只能使用一次**，求最大能获得3的倍数的个数。

题解：

此题出现了“3的倍数”，根据数学知识，易得如果一个数的各位数字之和是3的倍数，那么这个数是3的倍数。反过来也成立。

那么，拼成的数是3的倍数有几种情况呢？

假设我们使用 $x$ , $y$ 进行拼凑，拼凑成的数为 $z$ 。

* 如果 $x$ , $y$ 都是3的倍数，代表 $x$ , $y$ 的各位数字之和都是3的倍数，拼凑后 $z$ 各位数字之和也是3的倍数，所以 $z$ 是3的倍数。
* 如果 $x$ , $y$ 其中一个数模3余1，另一个数模3余2，代表其中一个数各位数字之和模3余1，另一个数各位数字之和模3余2，拼凑后 $z$ 各位数字之和为3的倍数（余数1+2=3模3余0），所以 $z$ 是3的倍数。

当且仅当两数满足上述两个条件之1时，拼凑成的数是3的倍数。

又因为题目中数的大小并不影响最终结果，所以我们首先可以将这些数按模3的余数分成3类，将模3余0，1，2的数的总个数分别存在 $three$ , $one$ , $two$ 中。

那么答案是多少？

因为**每个数只能用一次**，所以：

* 对上述情况1， $x$ , $y$ 都是3的倍数，每两个数能拼凑成一个符合要求的新数，所以情况1的答案为 $three/2$（注意此处的除是除完之后向下取整，相当于 Pascal 中的 div ，可以过滤掉剩余最后一个数的情况）。
* 对上述情况2，分别需要一个模3余1与模3余2的数，这样的两个数能拼凑成一个符合要求的新数，当拿不出两个中的任意一个数时，就结束统计，所以答案为 $min(one,two)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000+10;
int n,three,two,one;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
	    int t;
		scanf("%d",&t);
		if(t%3==0) three++;
		if(t%3==1) one++;
		if(t%3==2) two++;
	}
	printf("%d\n",three/2+min(one,two));
	return 0;
}
```


---

## 作者：test_check (赞：2)

[$\huge CF43C Lucky Tickets$](https://www.luogu.org/problem/CF43C)


本题其实不是很难，关键还是要靠我们去理解。来一起看一看如何解决吧。

------------
输入就不用说了，主要还是要看如何解决。我们设$ans$为最终的答案。根据题意，仔细的思考，$ans$应该等于什么呢？我们再设$a[3]$这个数组。根据数学知识可得：
>每当输入一个数$x$后，$a[x \%3]++$,最终$ans$即是$a[0]/2+min(a[1],a[2]);$

为什么是这样呢？其实，根据数学方法很轻松就可以得出来，因为比较简单，我就不再赘述了。
部分代码如下$:$
```cpp
    for(int i=0;i<n;i++)
    {
        cin>>x;
        a[x%3]++;  //统计
    }
    int ans=a[0]/2+min(a[1],a[2]);  //更新ans的值
    cout<<ans;
```
------------

扔出完整代码$↓↓↓$
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,x,a[3]={0};
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        a[x%3]++;
    }
    int ans=a[0]/2+min(a[1],a[2]); 
    cout<<ans;
}
```
好了，本文章到此为止。**~~喜欢它吗~~** $(QAQ)$

---

## 作者：Tune_ (赞：1)

这题其实不怎么难，关键是理解！

根据3的整除特征，配对的两个数只要除以3的余数和等于0或3即可。

即两个3的倍数配对或除以3余2和除以3余1的两个数配对，配对后的数即是3的倍数。

用a[3]数组记录除以3的余数的三种情况的个数。

答案为：

```
a[0]/2+min(a[1],a[2])
```
完整代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[3]={0},c;
    for(int i=1;i<=n;i++)
    {
    	cin>>c;
    	a[c%3]++;
    }
    cout<<a[0]/2+min(a[1],a[2]);
    return 0;
}
```


---

## 作者：蒟蒻lxy (赞：1)

### 数学题

- **推导**


首先看到
>输出最多有多少个 **_3的倍数_**

既然是3的倍数，那我们来回顾一下小学奥数中3的倍数规律：
>
> 3的倍数的各位数之和为3的倍数

那么我们可以用除以3的余数将所有数分类   
余数分别可能有：0、1、2

- 对于余数为0的数，本身就是3的倍数  
- 对于余数为1的数，可以与余数为2的数拼接让余数变为（1+2）%3=0，即可通过拼接变为3的倍数   
- 对于余数为2的数，同理

由此可以开一个ys数组，存储每种类别数的个数  
我们统计一下每一个数的类别，保存于ys数组就可以了

```
#include<bits/stdc++.h>
using namespace std;
int ys[5],n,α;
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> α,ys[α%3]++;//%3可得出类别
	cout << ys[0]+min(ys[1],ys[2]) << endl;
   //ys[1]的数可以和ys[2]的数拼接，但是其中多处来的就没有办法得出3的倍数，故此取min
	return 0;
}
```
没毛病是不是？交一下试试会发现第1个点就错了。

怎么回事？

看题目：
>没有进行匹配的数不算   
>没有进行匹配的数对答案没有贡献

那可怎么算啊？  
想想，每次需要凑出3的倍数，也可以由2个3的倍数相加而得

所以将ys[0]除以2就可以啦

真正的代码：
```
#include<bits/stdc++.h>
using namespace std;
int ys[5],n,α;
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> α,ys[α%3]++;//%3可得出类别
	cout << ys[0]+min(ys[1],ys[2]) << endl;
   //ys[1]的数可以和ys[2]的数拼接，但是其中多处来的就没有办法得出3的倍数，故此取min
	return 0;
}
```
~~珍爱生命，请勿复制~~   
~~这反作弊做得好~~

---

## 作者：林家三少 (赞：0)

这道题我们只需要知道一个公式$:$

$a[0]/2+min(a[1],a[2])$

这是什么意思呢，$a[0]$就是$n$个数里面%$3$余数为$0$的数的个数，

那么$a[1]$就是$n$个数里面%$3$余数为$1$的数的个数，

$a[2]$就是$n$个数里面%$3$余数为$2$的数的个数。

为什么我们要统计余数为$0,1,2$的数的个数呢，大家都知道数字和 %$3==0$ 的数 %$3==0$ ，而且数字和 %$3$ 的余数加起来 $==3$ 的几个数 %$3$也$==0$ ，所以我们只要求出了 $a[0],a[1],a[2]$ 的值，就可以根据上面的公式求出答案。

上代码$:$(~~就不写注释了~~)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int a[4],s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		a[s%3]++;
	}
	cout<<a[0]/2+min(a[1],a[2]);
	return 0;
}
```


---

## 作者：Suuon_Kanderu (赞：0)

这道题是个数学题，我主要是讲讲思路。

首先我们知道，一个数如果能被三整除，那么它的所有位上的数数之和也能被三整除  ~~废话~~ 所以如果两个数都能被三整除，连起来也能被三整除。

其次，如果两个数不能被三整除，那他们如果余数的和等于三，连起来就能被三整除！！

so，我们用输进来的数，都%3，把余数为三的数除以二，再把余数为一和二的数配对（取最小值），就得到了楼上或楼下的神奇公式。

```
#include<bits/stdc++.h>
using namespace std;
 inline int read() 
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') 
    {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') 
    x=x/* *10 */+ch-'0',ch=getchar();
    //因为只和每位上的数有关，索性不乘10
    return x*f;
}
int main()
{
    int n,q,a,b,c;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
         q=read();
         if(q%3==0)a++;
         else if(q%3==1)b++;
            else c++;
    }
    int ans=a/2+min(b,ac); 
    cout<<ans<<endl;
}
```


---

