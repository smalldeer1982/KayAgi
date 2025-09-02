# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 9
1 1 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715
```

### 输出

```
2147483648
```

# 题解

## 作者：SqrtSecond (赞：2)

这道题也是非常简单。

首先先算出黄水晶与蓝水晶各有几个，然后算出结果即可。

我开心地写出了如下的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y,z,needa,needb;
int main(){
	scanf("%lld%lld%lld%lld%lld",&a,&b,&x,&y,&z);
	needa=2*x+y;needb=y+3*z;
	printf("%lld",max(needa-a,0)+max(needb-b,0));
}
```
（欣喜若狂的我没发现第三个样例）

当我开心地提交代码时，才发现WA了。

我回过来看第三个样例，才知道应该开$longlong$。

AC代码如下（带注释）：
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y,z;
long long needa,needb;//需要水晶个数 
long long ans;//答案 
long long k=0;//存储一个longlong的0，因为后面max函数需要，否则会CE 
int main(){
	scanf("%lld%lld%lld%lld%lld",&a,&b,&x,&y,&z);
	needa=2*x+y;needb=y+3*z;//算出需要多少水晶 
	printf("%lld",max(needa-a,k)+max(needb-b,k));//max是为了防止a>needa或b>needb 
}
```


---

## 作者：Cloote (赞：1)

依旧先了解以下题目大意
###### ~~题面已经说的很清楚了不是吗？~~
差不多可以得到以下几个式子：
~~~
目标黄水晶=目标黄水晶球*2+目标绿水晶球*1
目标蓝水晶=目标绿水晶*1+目标蓝水晶球*3
~~~
然后我们就可以将题目已知的条件代入这两个式子，再与现有的黄水晶和蓝水晶相减，输出它们的和就可以了.

但出题人特别友善，通过样例3告诉我们要开`long long`。

提交上去后，你会惊奇地发现：**WA**了

很简单，这是因为现在有的蓝水晶数和黄水晶数可能已经比目标数大了，这时候就会出现相减得负数的情况，只需要一个特判就行了.

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,y,z,ansa,ansb;
template<typename T>void read(T& x)//快读不用管
{
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') f=1,c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	if(f) x=-x;
}
int main()
{
	ios::sync_with_stdio(false);//可以让输入输出流的速度跟printf的速度一样
	read(a);read(b);read(x);read(y);read(z);
   //不用快读：cin>>a>>b>>x>>y>>z;
	ansa=x*2+y;目标数
	ansb=y+z*3;		
	ansa-=a;
	ansb-=b;
	if(ansa<0) ansa=0;//特判
	if(ansb<0) ansb=0;
	cout<<ansa+ansb;
	return 0;//完结撒草
}
```


---

## 作者：_StarBird_ (赞：0)

**题解 CF912A 【Tricky Alchemy】**

[题目传送门](https://www.luogu.com.cn/problem/CF912A)

[在博客中食用更佳](https://www.luogu.com.cn/blog/jch2008/solution-cf912a)

平心而论，这题难度高了，显然应该是 ${\color{Red}\text{入门}}$（小声

------------
**【题目大意】**

这题翻译的已经很不错了 没什么好说的

就是问你在题目给定的转换方式下，还要几个水晶

------------
**【做法】**

很显然，我们知道最后需制作出多少个水晶球，就能算出需要多少个黄水晶和蓝水晶。由此作差即可。

值得注意的事：

1. 十年OI一场空，不开`long long`见祖宗（样例3不应该给，有提示作用
2. 作差以后，如果发现水晶还有剩余，应按需要0个计算

切 水 题 の 快 乐
```cpp
#include<bits/stdc++.h>
#define ll long long //注意要开long long 
using namespace std;
int a,b,x,y,z; //强迫症行为，输入数据是在int范围内的（ 
ll _max(ll u,ll v) //手写max好习惯
{
	if (u>v) return u;
	return v;
}
int main()
{
	scanf("%d%d%d%d%d",&a,&b,&x,&y,&z);
	ll k=1;
	printf("%lld\n",_max((ll)(k*2*x+y-a),0)+_max((ll)(k*3*z+y-b),0)); //一个是黄水晶，一个是蓝水晶，按题目中公式求出即可，为避免出现负数与0求max 
	return 0; //完结撒草
}
```


---

## 作者：baoxuanming (赞：0)


原题地址：[$\color{blue}\text{Tricky Alchemy}$](https://www.luogu.com.cn/problem/CF912A)
## 题意
某人有$A$个黄水晶和$B$个蓝水晶，他的任务是做出$x$个黄水晶球，$y$个绿水晶球和$z$个蓝水晶球。
配料表如下：
>2个黄水晶可造出1个黄水晶球

>1个黄水晶加上1个蓝水晶可造出1个绿水晶球

>3个蓝水晶可造出1个蓝水晶球

现在，这位仁兄让你帮帮他，让他知道他还缺少多少水晶。

## 思路
我们造$x$个黄水晶球，要$2x$个黄水晶；

造$y$个绿水晶球，要$y$个黄水晶和$y$个蓝水晶；

造$z$个蓝水晶球，要$3z$个蓝水晶。

这么算下来，我们一共要$2x+y$个黄水晶和$y+3z$个蓝水晶，再分别减去原来的$A$个黄水晶和$B$个蓝水晶，最后将两者相加，便是答案。

但是也有一点要注意，如果有一种水晶已经足够，就在答案上加$0$即可，不要加上一个负数。
***
完结撒fa！

---

## 作者：KEBrantily (赞：0)

## 题意
你手里有 A 个黄水晶和 B 个蓝水晶，其中两个黄水晶可以造一个黄水晶球，三个蓝水晶可以造一个蓝水晶球，一黄一蓝两个水晶可以造一个绿水晶球。

现在你需要 x 个黄水晶球，y 个绿水晶球，z 个蓝水晶球，问你总共还需要多少个水晶能满足要求。


------------


## 分析
反向考虑，既然 黄水晶 * 2 = 黄水晶球，黄水晶 + 蓝水晶 = 绿水晶球，蓝水晶 * 3 = 蓝水晶球；

那你总共需要的水晶数tot = x * 2 + y + z * 3 + y；

但是并不能直接拿 tot 与 A+B 的大小进行比较，因为可能你黄水晶不够，但蓝水晶很多，导致 A+B >= tot 但是仍然需要水晶的情况发生，所以就需要单独判断；


------------


## 代码呐
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define maxn 110
#define maxm 500 

using namespace std;

long long a,b,x,y,z,ans;

int main(){
	cin>>a>>b>>x>>y>>z;
    if(x*2+y<=a &&z*3+y<=b){
    	cout<<0;
    	return 0;
    }
    if(x*2+y>a) ans+=x*2+y-a;
    if(z*3+y>b) ans+=z*3+y-b;
    cout<<ans;
	return 0;
}
```

题解虽短但也用心，不喜勿喷，谢谢啦。

---

## 作者：七夜 (赞：0)

//首先，这道题的出题人还是有点良心，直接就把坑放在了样例里（也就是第三个）

//int一定会爆，所以，long long就完了。

//只需要两个计数器，记录需要的黄水晶和蓝水晶就完了，下面上本蒟蒻的代码

```
#include<bits/stdc++.h>//偷懒专用库 
using namespace std;
long long n,m,a,b,c,tot,pop,ans;//前文已提 
int main()
{
	cin>>n>>m>>a>>b>>c;//本来想用快读，刚学的快读，但是考虑到longlong万一出错就尴尬了，就改了 
	tot+=2*a+b-n;//记录需要的黄水晶 
	pop+=b+3*c-m;//记录需要的蓝水晶 
	if(tot>0)//只要需要，就加 
	 ans+=tot;
	if(pop>0)//同理 
	 ans+=pop;
	cout<<ans;//输出总数 
	return 0;//完美结束 
}
```
//望通过

---

## 作者：Clever_Jimmy (赞：0)

一道数学题……

首先，我们要x个黄水晶球就要2*x个黄水晶；

再者，我们要y个绿水晶球就要y个黄水晶和y个蓝水晶；

最后，我们要z个蓝水晶球就要3*z个蓝水晶。

统计统计：我们一共要2*x+y个黄水晶和y+3z个蓝水晶。

----------------------------------

```c
#include <stdio.h>
#include <stdlib.h>
long long int yellow,blue,sum,huang,lan;
long long int x,y,z;
/*
	yellow是我们已有的黄水晶数量；
    blue是我们已有的蓝水晶数量；
    sum是我们还需的水晶总数；
    huang是我们还需的黄水晶的数量；
    lan是我们还需的蓝水晶的数量；
    x是我们要做的黄水晶球的个数；
    y是我们要做的绿水晶球的个数；
    z是我们要做的蓝水晶球的个数。
    
    这一题的数据是0~10^9
	所以我们应该开大一点，用long long
*/

int main()
{

    scanf("%lld %lld",&yellow,&blue);
    scanf("%lld %lld %lld",&x,&y,&z);//既然用了long long，就用%lld
	huang=2*x+y;//计算我们还需要多少黄水晶
    lan=3*z+y;//计算我们还需要多少蓝水晶
    if(huang>yellow)//如果需要的大于我们已有的
		sum=sum+huang-yellow;//把差的加进sum里面
    if(lan>blue)
		sum=sum+lan-blue;//同理
    printf("%lld",sum);//输出
	system("pause");
	return 0;
}

```



---

## 作者：PC_DOS (赞：0)

一道模拟题，只需要分别求出两种水晶各自所需要的总量并减去所拥有的两种水晶的量，判断一下是否小于零(如果小于零就让差值等于0)再输出两个差值的和即可。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long nCrystalBlue, nCrystalYellow,nNeedYellow,nNeedBlue; //nCrystalBlue、nCrystalYello-持有的两种水晶的量，nNeedYellow、nNeedBlue-需要的两种水晶的量
	long long nNeedCrystalBallYellow, nNeedCrystalBallGreen, nNeedCrystalBallBlue; //三种水晶球的量
	cin >> nCrystalYellow >> nCrystalBlue; //读入持有的水晶的量
	cin >> nNeedCrystalBallYellow >> nNeedCrystalBallGreen >> nNeedCrystalBallBlue; //读入需要制作的三种水晶球的量
	nNeedYellow = 2 * nNeedCrystalBallYellow + nNeedCrystalBallGreen - nCrystalYellow; //计算黄水晶所需的总量与持有量的差
	nNeedBlue = nNeedCrystalBallGreen + 3 * nNeedCrystalBallBlue - nCrystalBlue; //计算蓝水晶所需的总量与持有量的差
	if (nNeedYellow < 0) //如果黄水晶所需的总量与持有量的差小于0，即黄水晶充裕
		nNeedYellow = 0; //不需要更多黄水晶
	if (nNeedBlue < 0) //如果蓝水晶所需的总量与持有量的差小于0，即蓝水晶充裕
		nNeedBlue = 0; ///不需要更多蓝水晶
	cout << nNeedYellow + nNeedBlue; //输出两个需求量的和
	return 0; //结束
}
```

---

## 作者：Achiles (赞：0)

# 题解 CF912A

[原题地址](https://www.luogu.org/problemnew/show/CF912A)

首先说说我设的变量：
```
yelcry,blucry;//黄水晶和蓝水晶的个数
yelbal,grebal,blubal;//黄水晶球，绿水晶球和蓝水晶的个数
ans;//额外需要水晶个数
```

题目要求“还额外需要几个水晶”，因此我们可能面临两种情况：没有差的水晶和有差的水晶，因此我们用判断来解决：

```
if(yelcry<yelbal*2+grebal) ans+=yelbal*2+grebal-yelcry;//如果 现有黄水晶个数 小于 需要黄水晶个数，就加上差价

if(blucry<grebal+blubal*3) ans+=grebal+blubal*3-blucry;//如果 现有蓝水晶个数 小于 需要蓝水晶个数，就加上差价

//如果没有差的水晶就对原ans数值不做改变
```

最后加上输入输出就够了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long yelcry,blucry;//黄水晶和蓝水晶的个数
long long yelbal,grebal,blubal;//黄水晶球，绿水晶球和蓝水晶的个数
long long ans;//额外需要水晶个数
int main()
{
    cin>>yelcry>>blucry>>yelbal>>grebal>>blubal;//输入
    if(yelcry<yelbal*2+grebal) ans+=yelbal*2+grebal-yelcry;//如果 现有黄水晶个数 小于 需要黄水晶个数，就加上差价
    if(blucry<grebal+blubal*3) ans+=grebal+blubal*3-blucry;//如果 现有蓝水晶个数 小于 需要蓝水晶个数，就加上差价
    cout<<ans;//输出
    return 0;
}
```

等等！为什么我们在定义变量时用了```long long```？

其实你会发现，如果使用```int```类型变量，在测试样例3时会输出```-2147483647```，是因为 $10^9$ 大小的数据范围用```int```类型会**越界**，产生不必要的麻烦，所以我们要使用```long long```

（出题人挺友善的，把这个特殊数据给在了样例里）

应该看得懂吧？勿抄！！

---

