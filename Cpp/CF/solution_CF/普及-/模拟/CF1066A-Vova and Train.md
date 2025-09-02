# Vova and Train

## 题目描述

## 题意描述：

$Vova$先生要乘火车去旅行，火车一开始位于$1$点，以每秒1个单位的速度向前行驶，最终到达$L$处。（也就是说，火车在第$1min$时在$1$处,在$2min$时在2处）

铁路沿线挂着一些灯笼，这些灯笼的位于坐标是$v$的倍数的地方，第一个灯笼位于$v$处

同时，有另一列火车停在另一侧的轨道上，这列火车的左右端点位于$l$和$r$处

当$Vova$先生经过一个地点，这个地点既有灯笼，又没有被另一列火车挡住时，我们称$Vova$先生可以看到灯笼，现在，我们需要你求出一路上$Vova$先生能看到几盏灯笼。本题有多组数据。

## 样例 #1

### 输入

```
4
10 2 3 7
100 51 51 51
1234 1 100 199
1000000000 1 1 1000000000
```

### 输出

```
3
0
1134
0
```

# 题解

## 作者：BADFIVE (赞：2)

首先，先扫一遍题目，~~发现是一道大水题~~   

题目要求你求能看到的灯笼数，我们可以分为3部分   
1.全部的灯笼的数量   
2.l左边的灯笼数量  
3.r右边的灯笼数量   
运用这个思想就很好解题了   
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long T, L, V, l, r;
int main(){
    scanf("%lld",&T);
    while(T--){
        int ans=0;
        scanf("%lld %lld %lld %lld",&L,&V,&l,&r);
        printf("%lld\n",L/V-r/V+(l-1)/V);
    }
}
```


---

## 作者：Daniel_yao (赞：1)

### 具体思路

小学奥数之容斥原理。

可以把它分为 3 个部分：

1. 全部的灯笼；
2. L （左端点）的灯笼；
3. R （右端点）的灯笼；

获得公式：全部的灯笼 $-$（左端点的灯笼 $-$ 右端点的灯笼）；

意思就是说，他能看到的灯笼数减去右边他看不到的灯笼数，再把它们的和加上右边的灯笼数，就是他绝对能看得到的灯笼数。（简单的容斥原理，用草稿本退一下即可）。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
  cin >> t;
  while(t--){
    int l, i, r, v;
    cin >> l >> v >> i >> r;
    cout << (l / v) - (r / v) + (i - 1) / v << endl;
  }
  return 0;
}

```
直接切掉！

---

## 作者：LordLaffey (赞：1)

这道题我们首先可能会想到把v的倍数都算出来，但是当我们看到样例的第四组数据时，就应该知道这种做法会超时，所以我们需要进行优化

从题目中可以看出，这道题的答案只与有多少个v的倍数有关，而与v的倍数具体是什么无关，所以我们完全可以用**L/v**这个式子求出[1,L]区间内v的倍数的个数   

然后我们接着往下分析，
>当Vova先生经过一个地点，这个地点既有灯笼，又没有被另一列火车挡住时，我们称Vova先生可以看到灯笼

从这句话我们可以看出这道题最终的答案应该不包括[l,r]区间内v的倍数，那么这里应该怎么算呢  
由于偶然性的存在，我们不能求出[l,r]区间中v的倍数，所以我们只可以用左端点为1的区间来得到解，那么可以利用的区间只有[1,L],[1,r],[1,l]三个，但是我们可以用[1,r]-[1,l]得到[l,r]，再用[1,L]-[l,r]，就可以得出不包括[l,r]的v的倍数个数   

所以最终的式子应该为
## L/v-r/v+(l-1)/v
至于为什么l需要-1呢，因为当v的倍数在火车左端点是不计入总数的

那么最后贴一下代码（代码这么简单就不要copy了吧）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int main(){

    int t;
    scanf("%d",&t);
    while(t--)
    {
        int L,v,l,r;
        scanf("%d%d%d%d",&L,&v,&l,&r);
        int ans;
        ans=L/v-r/v+(l-1)/v;
        cout<<ans<<endl;
    }

    return 0;

}完结撒花✿✿ヽ(°▽°)ノ✿
```



---

## 作者：_lgh_ (赞：0)

### 思路：
~~大水题！~~ 求 $l$ 和 $r$ 区间的灯笼就等于全部的减 $l$ 左边的和 $r$ 右边的。

### 代码：
```cpp
#include<stdio.h>
int main()
{
	int l=0,r=0,L,v,i,m;
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%d %d %d %d",&L,&v,&l,&r),printf("%d\n",(l-1)/v+(L/v)-(r/v));
	return 0;
	
 } 
```


---

## 作者：zct_sky (赞：0)

### Solution:
-----
首先，假设没有另一辆火车，那么 $Vova$ 先生能看到的灯笼数就是所有灯笼数，即为 $\left\lfloor\dfrac{L}{v}\right\rfloor$。

那么，另一辆火车挡住的灯笼数就是 $r$ 左边的灯笼数减去 $l$ 左边的灯笼数，即为 $\left\lfloor\dfrac{r}{v}\right\rfloor-\left\lfloor\dfrac{(l-1)}{v}\right\rfloor$ 。

所以，$Vova$ 先生实际能看到的灯笼数为 $\left\lfloor\dfrac{L}{v}\right\rfloor-\left\lfloor\dfrac{r}{v}\right\rfloor+\left\lfloor\dfrac{(l-1)}{v}\right\rfloor$
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define re register
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
ll t,L,v,l,r; 
int main(){
    t=read();
    for(re int i=0;i<t;i++){
    	L=read(),v=read(),l=read(),r=read();
    	write(L/v-r/v+(l-1)/v),puts("");
	}
	return 0;
}
```

---

## 作者：zplqwq (赞：0)

# CF Vova and Train

啊这。。

emm，最近被校内模拟赛虐了，所以来水题解了。

## 题目分析

首先，我们先扫一遍题目，应该会有一个想法就是遍历一遍，然后判断能都被看到。

但是这样做有一个很严重的问题，就是数据**最大**可以到10000，而此时每组最大可以到$10^9$，很明显会TLE。

那怎么办呢？

其实这道题就要分情况考虑

即：

1. 全部的灯笼的数，设为x
2. l左边的灯笼数量，设为y
3. r右边的灯笼数量，设为z

ok，那就简单了，我们要的答案不过是x-y+z罢了。

即

```c++
L/v-r/v+(l-1)/v
```

## 代码

```c++
#include <bits/stdc++.h>//万能头
using namespace std;
#define int long long//要开long long
int T;
int L, V, l, r;
int ans;
signed main()
{
    cin>>T;
    while(T--)
    {
        ans=0;//切记，ans每次更新之前都要清零，要不然上一次的答案就算进去去了，肯定不是我们想要的
        cin>>L>>V>>l>>r;
        cout<<L/v-r/v+(l-1)/v<<endl;//输出
    }
    return 0;
}//加了反作弊
```





---

## 作者：LucasXu80 (赞：0)

本题解提供详细的解题思路讲解以及Python代码。

### 思路

看到这题，相信很多人的第一感觉都是遍历在路上的每一个数，判断其是否能够被看到。然而这样显然是不行的，因为 Time limit 1s，而数据最多有$10000$组，每组最多要遍历$10^9$遍，TLE妥妥的。

这个时候，我们就明白，一定要找出公式或者快速推出答案的方式，才能AC。那我们现在就来找这个规律。由于我更习惯C++，以下除代码外所有的部分都采用C++的符号，且变量含义与原题中相同。

首先我们不难算出路上的总灯笼个数：$L/v$。如果将其存入变量$ans$中，拿$ans$被挡住的灯笼个数就是最终答案。所以关键就是找出**被挡住了几个灯笼**。

拿一组样例看看吧~

#### 样例1  $10$ $2$ $3$ $7$

首先我们在$ans$中存入$10/2=5$。

接下来，我们将这五个灯笼（位置分别是$2,4,6,8,10$）编号为$1,2,3,4,5$。

我们先来看最左边的那个被挡住的灯笼（应该是2号，我们来看看如何计算得到它）

很容易想到应该拿左端点$l$去除以间隔$v$，得到火车的最左边应该在“1.5”号位置上。

注意，如果这个值是一个整数，那么这个位置上的灯笼是看不到的。否则，我们需要将这个值**向上取整**，因为只有向上取整才会覆盖在火车的范围内。具体实现在代码中。

所以在这里，最左边的看不到的灯笼应该是2号。

而最后一个看不到的灯笼就相对简单多了，直接是$r/v$（向下取整）的值就可以了，原因这里不再赘述。

那么有了这两个值，在样例中应该是2号和3号，我们只需算出在此区间内究竟有几个灯笼。

这就是小学数学内容了，$3-2+1=2$嘛。换做代码就是$right-left+1$。

好了，思路就讲到这里，我们来看代码~

```python

def ceil(n,m): #定义向上取整函数
    if n%m==0: return n//m #如果整除，直接返回两数之商
    else: return n//m+1 #不整除，返回两数之商+1
t=int(input()) #输入
for i in range(t):
    s,v,l,r=map(int,input().split()) #输入4个数
    ans=s//v #总灯笼个数
    left=ceil(l,v) #最左边看不到的灯笼
    right=r//v #最右边看不到的灯笼
print(ans-(right-left+1)) #套公式输出
#print()自带换行，无需另行输出换行
```
### FAQs （大佬请忽略）

**Q:** 为什么代码第2行需要使用$n//m$而不是$n/m$？有何区别？

**A:** 这个情景下两者确实是答案相同，但是两者的答案数据类型不同。$/$默认浮点型$float$，而$//$由于是取整，当然是整形$int$。也就是说，在PY中$10/2$的结果是$5.0$而不是$5$，这会对答案产生影响。



------------


这篇题解就到此为止了，求过求赞！


---

## 作者：ztz11 (赞：0)

# 大水题。。。

题目要求你求能看到的灯笼数，我们可以分为3部分

* 总共的灯笼数——————1

* 在 $l$ 左面的灯笼数（不包括$l$）——————2

* 在 $r$ 左面的灯笼数（包括$r$）——————3

我们知道，由上面的2-3就是被另一列车挡住的灯笼数

所以1-2+3就是答案；

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int t,len,l,r,v;
void solve()
{
	scanf("%d%d%d%d",&len,&v,&l,&r);
	int sl1=len/v;
	int sl2=(l-1)/v;
	int sl3=r/v;
	sl1-=sl3;
	sl1+=sl2;
	printf("%d\n",sl1);
}
int main()
{
	int t;
	scanf("%d",&t);
	for(rii=1;i<=t;i++)
	{
		solve();
	} 
}
```

---

