# Robot Program

## 题目描述

There is an infinite 2-dimensional grid. The robot stands in cell $ (0, 0) $ and wants to reach cell $ (x, y) $ . Here is a list of possible commands the robot can execute:

- move north from cell $ (i, j) $ to $ (i, j + 1) $ ;
- move east from cell $ (i, j) $ to $ (i + 1, j) $ ;
- move south from cell $ (i, j) $ to $ (i, j - 1) $ ;
- move west from cell $ (i, j) $ to $ (i - 1, j) $ ;
- stay in cell $ (i, j) $ .

The robot wants to reach cell $ (x, y) $ in as few commands as possible. However, he can't execute the same command two or more times in a row.

What is the minimum number of commands required to reach $ (x, y) $ from $ (0, 0) $ ?

## 说明/提示

The explanations for the example test:

We use characters N, E, S, W and 0 to denote going north, going east, going south, going west and staying in the current cell, respectively.

In the first test case, the robot can use the following sequence: NENENENENE.

In the second test case, the robot can use the following sequence: NENENEN.

In the third test case, the robot can use the following sequence: ESENENE0ENESE.

In the fourth test case, the robot doesn't need to go anywhere at all.

In the fifth test case, the robot can use the following sequence: E0E.

## 样例 #1

### 输入

```
5
5 5
3 4
7 1
0 0
2 0```

### 输出

```
10
7
13
0
3```

# 题解

## 作者：A_Konnyaku (赞：7)

## $ CF243A \ \ Robot \ Program\   $    题解

---

[题目传送门](https://www.luogu.com.cn/problem/CF1452A)

---
### 简单题意
我们在 $ (x,y) $ ,要走到 $ (0,0) $ 。有 $ 2 $ 种选择：

- 向上下左右任意一个方向行走一个单位。

- 停留在当前位置不动。

问最少的选择次数（理解成  步数或操作次数 皆是珂以）

---
###  思路探究

 举个栗子：
![](https://cdn.luogu.com.cn/upload/image_hosting/q4r24ruq.png)

   我们容易知道红点的坐标为 $ (4,8) $ ,绿点的坐标为 $ (8,8) $ ，蓝点的坐标为   $ (6,4) $ 。
   这代表了几种情况：


设 $ x,y $ 为点的横坐标，纵坐标，则有：

-  $ x<y $
- $ x=y $
-  $ x>y $

 共三种情况；
 

 
 $ \because $ 要使操作次数（走步数最少）
 
 $ ∴ $我们则沿折线走，最后在 $ x,y $ 轴上~~慢慢挪动~~走一步停一步即可。
 
$ Done $
 
 
---
### 具体步骤

$ Rt $ :

![](https://cdn.luogu.com.cn/upload/image_hosting/ruk2pag6.png)
- 设 $ m=max(x,y)\ ;\ n=min(x,y) $

走到 $ x $ 或 $ y $ 轴所需的步数是 $ n\times 2 $ ，接着走一步停一步,（**注意最后就无需停止了,故减去一**）步数是 $ (m-n)\times2-1 $。

####  ** $ But $ **

若 $ x=y $ ，走完 $ n\times 2 $ 步就已经到达原点了，无需再走；

所以我们需要特判。

当 $ x=y $ 时，直接输出 $ n\times 2 $ 即可,最后 ```return 0;```

 $ \green {AC!} $ 

---
### $ \green {AC}\ \  Code $
```cpp
/*
Author :A_Konnyaku
Luogu_Number:359953
Time:2021/Jan/31st/20:36:39
*/
#include<bits/stdc++.h>
using namespace std;
int  i,d,m,n,x,y,tot=0;
//以上不解释
int main()
{

	ios::sync_with_stdio(false);//输入输出流加速是个好习惯
    cin>>d; //输入数据组数
	for(i=0;i<d;i++)//Started!!
    {
	cin>>x>>y;//坐标
		if(x==y)//特判
        {
			cout<<2*x<<endl;
			continue;
		}
		int n=min(x,y),m=max(x,y);//定义m,n
		tot=2*n+(m-n)*2-1;
        cout<<tot<<endl;
		tot=0;//一定要归零
    }
	return 0;
}
```
---
其他

- 蒟蒻第一篇题解，管理员大大求过qwq

- ~~不要脸的要个赞~~

---

## 作者：ql12345 (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF1452A)

### 题面：

一个二维矩阵，每次可以上下左右走1格或不动，但不能连续走两步相同的（两次不动也算），求从$(0,0)$走到$(n,m)$的最少步数

### Solution：

- 策略：先从$(0,0)$一横一下走到$(min(n,m),min(n,m))$，然后就变成了一条直线上的问题，先向终点走一步，然后一停一走

- 答案计算：可以发现第一步是$2\times min(n,m)$的，第二步由于先走了一步，可以看做是第一次不用停，少走一步，以后两步挪一格，所以答案为$2\times (max(n,m)-min(n,m))-1$，加起来即得总答案

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << max(n, m) * 2 - (n == m ? 0 : 1) << '\n';
    }
    return 0;
}
```

---

## 作者：帝千秋丶梦尘 (赞：2)

## [题目链接](https://www.luogu.com.cn/problem/CF1452A)

因为$x$到$0$和$y$和$0$是肯定要走的,

所以我们就是要想到如何走使得停留的次数最少

而这题中$x$和$y$两种情况：

1）当$x$和$y$的差值的绝对值不过$1$时

可以想到横一步,竖一步，这样就不可能会停留，自然步数最少了

2）当$x$和$y$的差值的绝对值超过$1$时

那么肯定有停留的情况了，那如何走呢？

我们可以将这个问题化为之前的问题：

只要先将$x$和$y$取相同的值，那么就是第一种情况

（注意先走较大的数的方向，例如x=1,y=4，那就先竖着走一步）

那余下的不到的步数那只能走一步停一步了

code:

```cpp
#include<bits/stdc++.h>
#define ri register
using namespace std;
int n;
signed main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(ri int i(1);i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		if(abs(x-y)<=1)
		{
			cout<<x+y<<endl;
		}
		else
		{
			cout<<min(x,y)*2+(max(x,y)-min(x,y)-1)*2+1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_ajthreac_ (赞：2)

### 0.Description
你现在在 $(0,0)$ 点，你要走到 $(x,y)$ 点，每次只能向平行于坐标轴方向走 $1$ 单位距离或停一步，且相邻两步的方向不能相同。求最小的步数。
### 1.Solution
既然不能连续走一样的方向，那么我们肯定要先尽量走折线走到 $\min\{n,m\}$ ，然后走一步停一步即可。
### 2.Implementation
走到 $\min\{n,m\}$ 所需的步数是 $\min\{n,m\}\times2$ ，接着走一步停一步（注意最后就不用停了）的步数是 $(\max\{n,m\}-\min\{n,m\})\times2-1$ 。但是如果 $n=m$ 的话后面那部分就没有了，所以需要特判。
### 3.Code
[开头代码](https://www.cnblogs.com/juruoajh/p/12632444.html)
```cpp
int T,x,y;
int main(){
	Read(T);
	while(T--){
		Read(x),Read(y);
		x=abs(x),y=abs(y);
		if(x==y)cout<<min(x,y)*2<<endl;
		else cout<<min(x,y)*2+(max(x,y)-min(x,y))*2-1<<endl;
	}
	return 0;
}
```

---

## 作者：—维尼— (赞：2)

## 题目思路

机器人弱化弱化弱化版（bushi），给定一个目标坐标和一个机器人，初始坐标为$(0,0)$，共五种操作：每次可以选择上下左右走一格或者不动，相邻操作不能相同，问至少要多少操作才能到达目标点

## 题目思路

相邻操作不能相同的话，我们就按照上，右，上，右这样行走，直到x轴或者y轴到达目标点，这样当然是最优的情况，然后问题就转化成了处理直线行走的问题，此时贪心，例如向右走，走一格停一格，即为：右，停，右，停，右……速度为$0.5$格/操作，也是最优，或者变方向的话，应为：右，上，右，下，右，速度都一样

如何实现？

我们先是向右上跳，直到到达目标行或者目标列，那么此时操作数为：$2\times \min(x,y)$

之后特判，如果两数只相差$1$，直接输出$ans+1$

差$0$，也就是已经到了,直接输出$ans$

剩下的就$ans+2\times max(x,y)-min(x,y)$

## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int x,y,ans=0;
		cin>>x>>y;
		int cha=max(x,y)-min(x,y);
		ans+=min(x,y)*2;
		if(cha==0){
			cout<<ans<<endl;
			continue;
		}
		if(cha==1){
			cout<<ans+1<<endl;
			continue;
		}
		ans+=cha*2;
		cout<<ans-1<<endl;
	}
}
```

---

## 作者：CZ_7 (赞：1)

## ~~大水题~~

先看数据范围：
```
 (0≤x,y≤10^4)
```
哎呀呀 呀呀 呀呀

都是非负的哩！

那我们就要往左下（↙）走折线，再走一步顿一步走到（0,0）

请看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,cnt;
int main(){
	cin>>n;//数据组数
	for(int i=1;i<=n;i++){
		cin>>x>>y;//每组数据坐标
		if(x==y){//特判坐标横纵相等
			cout<<2*x<<endl;//输出2倍坐标
			continue;
		}
		int t=min(x,y);//定义t为（x，y）的最小值
		cnt+=2*t;//走折线，2倍的t
		x-=t,y-=t;//减去（现在x、y应有一个为0）
		cnt+=2*max(x,y)-1;//那个不为零的走到零，因为走一步空一步所以*2，但注意要先走再停，最后就不用停了故-1
		cout<<cnt<<endl;//输出
		cnt=0;//还原
	}
	return 0;
}
```
## RP++!


---

## 作者：luosw (赞：1)

要使步数最小，考虑下面的路径：向上向右交替进行，必要时停下。形式化地，若要到 $(m,n)$，先向右向上交替走 $\min(m,n)$ 步，然后再朝一个方向行进 $\max(m,n)-\min(m,n)$ 步，每走一步停一次。

简单证明：首先 $(m,n)$ 位于 $O,x+,y+$ 或第一象限上，因此若向下，左走会损失步数，则停顿。而具体的到 $(m,n)$ 的步骤每种解法的步数仅有尽可能交替向右向上走的解法最优。 

容易推出答案 $ans$ 满足

$$
ans=\begin{cases}2x\qquad x=y,\\2\min(x,y)+2[\max(x,y)-\min(x,y)]-1 \qquad \text{Otherwise.}\end{cases}
$$

---

## 作者：Terrific_Year (赞：1)

题意：

有一个无限的二维网格。

机器人站在$(0,0)$并希望到达$(x,y)$。下面是机器人可以执行下列命令：

- 向北移动从$(i,j)$到$(i,j+1)$；
- 向东移动从$(i,j)$到$(i+1,j)$；
- 向南移动从$(i,j)$到$(i,j-1)$；
- 向西移动从$(i,j)$到$(i-1,j)$；
- 留在$(i,j)$。

机器人想要在尽可能少的命令下到达$(x,y)$。但是，他不可能连续执行两次或多次相同的命令。

从$(0,0)$到$(x,y)$所需的最小命令数是多少？

$t(1<t\le100)$组数据，每组数据两个整数$x,y(0\le x,y \le 10^4)$。每组数据输出一行答案。

----
由于均为非负整数，比较容易想出思路~~不是也很容易~~。

很容易想到它可以东北交替前进，需要的时候停下。

因为如果它需要向南或西走，总路程至少会加一至少再增加一个命令，所以还不如停在那。

- $x\mathrlap{\,/}{=}y$时，很容易推出：$answer=x+y+abs(x-y)-1$

- $x=y$时，$answer=x+y+abs(x-y)$(也可以是$2x$或者$2y$~~主要是懒得打代码~~)

$AC\ Code:$

```cpp
#include<cstdio>
int t,x,y;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&x,&y);
        printf("%d\n",x+y+(x<y?y-x:x-y)-(int)(x!=y));
        //x!=y时需要-1
        //(x<y?y-x:x-y)也可以写成abs(x-y)但是要改一下头文件
    }
    return 0;
}
```

$Pascal:$

```pascal
var
    x,y,t:longint;
begin
    read(t);
    for i:=1 to t do
    begin
        read(x,y);
        if x<>y then writeln(x+y+abs(x-y)-1)
        else writeln(x+y+abs(x-y));
    end;
end.
```

---

## 作者：Fan_Tuan (赞：0)

# 题意
一个机器人想要从$(x, y)$走到$(0, 0)$, 每次可以向上下左右任意一个方向行走一个单位或者不动， 但是不能连续执行同一操作两次， 求最小步数。
# 思路
从题目描述来看， $x, y \ge 0$, 所以我们完全可以只看向下向左这两个操作，按照题意，我们画几个图也不难看出我们按照以下方式走是最优的

###### ...向下，向左，向下...   **, 静止不动， **， 静止不动...

那么到底以哪种操作为开始，哪种操作为结束呢？

手推一下大概可以看出...  

1. 若$x > y$, 开始的操作为向下，否则为向左;
1. 等到机器人运动到$x$或$y$轴上之后，操作数为$min(x, y) * 2 + 1$ ;
3. 然后我们只需再走($max(x, y) - min(x, y)) * 2$的步数到达$(0, 0)$;

###### 最终$ans = max(x, y) * 2 - 1$。

然后我们就会发现对于$x = y$的情况，这个结论是不正确的，所以我们特判一下$x = y$的情况， $ans = x + y$;


# 代码
```c
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int t;

signed main () {
	scanf("%d", &t);
	while (t--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x == y) printf("%d\n", x + y);
		else printf("%d\n", max(x, y) * 2 - 1);	
	}
	return 0;
}
```


---

## 作者：SpeedStar (赞：0)

#### 算法分析

假设 $x \leqslant y$，先花费 $2x$ 秒移动到 $(x, x)$，然后每次向上移动 $1$ 秒再停留 $1$ 秒即可。

#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::swap;
using std::max;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int x, y;
		cin >> x >> y;
		if (x > y) swap(x, y);
		cout << x * 2 + max(0, (y - x) * 2 - 1) << '\n';
	}
	
	return 0;
}
```


---

## 作者：fisheep (赞：0)

## 题意：
初始坐标$(0,0)$，然后你可以进行如下操作：

设其坐标$(x,y)$

* $(i,j+1)$ 将`y+1`
* $(i+1,j)$ 将`x+1`
* $(i-1,j)$ 将`x-1`
* $(i,j-1)$ 将`y-1`

然后每次不能连续向同一个方向移动，如果需要必须停顿一下。求移动到规定位置所需最少的步数。


## 想法：
首先拿到这道题感觉不是很难，感性理解一下不难发现横纵坐标交替走这种方法是最快的，也就是你到达$(n,n)$时只需要`2n`步，然后就尽可能让横纵坐标抵消，剩下的坐标直接走一步停一步，就可以得到

$ans=abs(abs(x)-abs(y))* 2-1+min(abs(x),abs(y))*2$

因为当你到达时不需要再停了，所以`-1`。

但是你会发现，你仅仅这么写的话，当坐标为$(n,n)$时会锅掉，但我们只需要特判掉即可。

## Code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int t,x,y;
int ans;
int main(){
  	t=read();
  	while(t--){
  		x=read(),y=read();
  		if(x==y) ans=2*abs(x);
  	else ans=abs(abs(x)-abs(y))*2-1+min(abs(x),abs(y))*2;
        printf("%d\n",ans);
    }
    return 0;
}
```

#### ps:话说看这数据范围感觉并不需要`abs`。

---

## 作者：le_星辰 (赞：0)

简单规律题，首先为了达到目标位置，尽量不要绕着走，所以可以走一个两个方向交替进行的过程使 $x$ , $y$ 其中一个和目标位置相同，然后就进行走一步停一步的策略，然后分为两种情况，如果 $x<y$ 那么执行第一个过程时最后一定要向右走，这样更优，另外一种情况同理，然后就能直接输出答案了。
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int T,er,ec,mi,ans,nowr,nowc;
int main() {
	cin>>T;
	while(T--){
		ans=0;
		cin>>er>>ec;
		mi=min(er,ec);
		ans+=2*mi;//过程1
		nowr=mi,nowc=mi;
		if(nowr==er&&nowc==ec){
			cout<<ans<<endl;
			continue;
		}
		if(er<=ec){//过程2
			ans+=2*(ec-nowc)-1;
		}else{
			ans+=2*(er-nowr)-1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：WitheredZeal (赞：0)



# 题意  
你要从$(0,0)$走到$(n,m)$，每一秒可以选择走或者不走，相邻两秒不能都走同一个方向，最少需要几步。  

# 题解  
显然如果不考虑“相邻两秒不能都走同一个方向”，直接往右边和上面走就行了（按坐标系方向来看）。  
考虑这个条件，倒回去走显然不如停在原地优。  
不妨设$n\geq m$  
那么是这么走的$1212121\cdots12121010101\cdots10101$  
这里总共有$n$个1，所以总长度为$2n-1$  
但是如果$n=m$，长度应该是$2n$  
那么就做完了  

```cpp
signed main()
{
	int T;
	cin>>T;
	init();
	while (T--)
	{
		cin>>n>>m;
		if (n<m) swap(n,m);
		if (n==m) cout<<2*n<<endl;else cout<<2*n-1<<endl;
	}
}
```

---

