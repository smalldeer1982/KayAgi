# Cookies

## 题目描述

Fangy收集饼干。他曾决定拿一个盒子并通过某种方法把饼干放进去。如果我们取一个分割成$1\times 1$的正方形的$k\times k$大小的正方形，并且将主对角线涂色，则涂色的正方形将放入饼干。Fangy还有一个$2^n\times 2^n$的正方形盒子，并且分割成$1\times 1$的小正方形。盒子里的饼干不可以重叠、旋转或者翻转。下面是大小为$2,4$的饼干：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF70A/9aef2cce7422bbcc3d96eecc7a521b9ccbc21abb.png)

为了叠放饼干，小海狮使用了下述的算法。他把最大的饼干放在盒子里的合适位置。它有无数块大小大于$2$的饼干，但却没有大小为$1$的饼干。因此会有剩余的格子。Fangy想要知道会有多少空的格子。

## 说明/提示

如果盒子是$2^3\times 2^3$（就像样例中的），饼干就会按照如下方式摆放：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF70A/def84af13deee4d9d00923b3f69a8767f4ec0e62.png)

## 样例 #1

### 输入

```
3
```

### 输出

```
9```

# 题解

## 作者：_Aoi_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF70A)

根据题目的描述可知：有一个边长为$2^n$的正方形饼干盒子，小海狮想按照题目所给的方式放无数块大小大于$2$的饼干进去，求剩余格子的数量。

我们可以发现：

1. 当 $n=1$ 时：![](https://cdn.luogu.com.cn/upload/image_hosting/u4xylx2k.png)
	
 	空格数量为：$1$ 。
1. 当 $n=2$ 时：![](https://cdn.luogu.com.cn/upload/image_hosting/xj5wf25q.png)
	  
   空格数量为：$3$ 。
1. 当 $n=3$ 时：![](https://cdn.luogu.com.cn/upload/image_hosting/5oviet69.png)
	
   空格数量为：$9$ 。
   
以此类推，我们可以得出下表：
```
n的值：     1 2 3 4...
空格的数量:  1 3 9 27...
```
所以，题目就是让我们求:
## $3^{n-1}$
最后：别忘记 %$1e6+3$ 哦！

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int mod=1000003;//%1e6+3
long long n,ans=1;//十年OI一场空，不开long long见祖宗 
int main()
{
	cin>>n;
	/*不能用pow(3,n-1),因为如果输入的数据太大还没来得及%就炸了*/ 
	for(int i=1;i<=n-1;i++)
	{
		ans*=3;
		ans%=mod;
	}
	cout<<ans;
	return 0;
 } 

```

---

## 作者：yoy68 (赞：0)

根据题目得知

n=3时

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF70A/def84af13deee4d9d00923b3f69a8767f4ec0e62.png)

空白部分是9

再把数转换为3进制,则变成100

所以就是去3*3......3共(n-1)个三



```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+3;
long long f(long long n){
	long long s=1;
	for (int i=1;i<n;i++){
		s=s*3;
		s=s%mod;
	}
	return s;
}
int main (){
	long long n;
	scanf ("%lld",&n);
	if (n==0)printf ("1");
	else printf ("%lld",f(n));
}
```


---

## 作者：CrTsIr400 (赞：0)

这道题，楼下几篇题解已经讲的很清楚了。

如果你急得话，可以直接看结果计算公式$3^{n-1}$。

但是，最好还是跟蒟蒻一起模拟整个公式的推导过程——

首先，我们可以看到把$n=1,n=2,n=3$的正方形分解

得出这样几个图形：

$n=1:$
![cookies1.PNG](https://i.loli.net/2020/02/06/j7ThLrwNoJfgtAK.png)

$n=2:$![cookies2.PNG](https://i.loli.net/2020/02/06/3s6jMv5Jw8zOASK.png)

$n=3:$
![cookies3.PNG](https://i.loli.net/2020/02/06/idQHypcaD2J84kO.png)

然后，我们把这个大正方形沿斜边切开，分成两部分，一个三角形是$2^n\times2^n$的,另一个是$(2^n-1)\times (2^n-1)$的。

![cookies5.PNG](https://i.loli.net/2020/02/06/5GHJQmRF2v7oACa.png)

上面三角，因为是纯三角形，没有空隙，所以不管他。

![cookies4.PNG](https://i.loli.net/2020/02/06/vtZlkdpsLObGPz3.png)

接着看下面三角的分解：

![cookies6.PNG](https://i.loli.net/2020/02/06/RfuMUNvemE9dhzJ.png)

可以从图中看到，下面三角形被分成了三部分——两个三角形和一个正方形。

两个分出来的小三角形可以一直分到只剩$1\times1$的正方形为止，这样可以统计数据了。

小正方形又可以分成两部分，一个$2^{n-1}\times2^{n-1}$的大三角形，一个$(2^{n-1}-1)\times(2^{n-1}-1)$的小三角形。

也就是说，一个下三角形可以分解成$3$个小下三角形，知道小三角形的腰长均为$1$为止。

也就是说，稍微转化一下，我们得出了结果——

$\huge{3^{n-1}}$。

---

## 作者：仗剑_天涯 (赞：0)

这道题的话直接简单粗暴地枚举是不行的。

于是我灵光一闪！

找到了规律... ... 
```cpp
第几项 2 3 4 5  6  7
值     1 3 9 27 81 243 ... ...
```
这不就是一个等比数列吗！（不看第一项）

最后，记得%1000003！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,m=1000003;
int main()
{
	cin>>n;
	n--;//从第二项开始
	s=1;
	for(int i=1;i<=n;i++)
	{
		s=s*3%m;//同余定理a*b%m=(a%m)*(b*m)
	}
	cout<<s;
} 
```


---

## 作者：江山_远方 (赞：0)

~~看发题解的人少，果断水一波~~

咳咳，此题原意就是让你求2^k的方阵中按照图示除了有颜色的方块还有几个方块。

经过打表，发现题目就是求3^n%1000003的值。

emmmm....上代码 这个不用多解释了吧

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n;
int ans;  
int main()
{
	cin>>n;
	ans=1;
	for(int i=1;i<n;i++)ans=ans*3%1000003;
	cout<<ans;
	return 0;
}
```
12行......

---

## 作者：YZ_hang (赞：0)

### 纯粹找规律
看到题目给出的仅仅3组样例时，我们很自然的就想到一种规律，那就是等比数列，比是3，首项是1

~~我就根据这个规律直接试了试，还真是正解~~

于是，我先写了个pow函数，但是发现这样在输入很大时结果会爆longlong，根本来不及mod就爆了

然后写了个手写幂就AC了，code如下
```
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int n;
    long long ans=1;//ans不赋初值为1就会暴零
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){//因为我们发现答案是pow(3,n-1),所以这里只循环n-1次
		ans*=3;//如果n=1就不循环，也就不乘以3，而我们又赋过初值了ans=1，所以不用特判
		ans%=1000003;//每乘一次就mod一次，不会超时，防止了超数据范围
	}
	printf("%lld\n",ans);//答案其实没必要开longlong了，开了更保险
	return 0;
}
```


---

