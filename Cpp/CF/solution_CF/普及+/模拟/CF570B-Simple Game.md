# Simple Game

## 题目描述

One day Misha and Andrew were playing a very simple game. First, each player chooses an integer in the range from $ 1 $ to $ n $ . Let's assume that Misha chose number $ m $ , and Andrew chose number $ a $ .

Then, by using a random generator they choose a random integer $ c $ in the range between $ 1 $ and $ n $ (any integer from $ 1 $ to $ n $ is chosen with the same probability), after which the winner is the player, whose number was closer to $ c $ . The boys agreed that if $ m $ and $ a $ are located on the same distance from $ c $ , Misha wins.

Andrew wants to win very much, so he asks you to help him. You know the number selected by Misha, and number $ n $ . You need to determine which value of $ a $ Andrew must choose, so that the probability of his victory is the highest possible.

More formally, you need to find such integer $ a $ ( $ 1<=a<=n $ ), that the probability that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570B/fcf679a711cde29d2e9f9a082e28c313061224e7.png) is maximal, where $ c $ is the equiprobably chosen integer from $ 1 $ to $ n $ (inclusive).

## 说明/提示

In the first sample test: Andrew wins if $ c $ is equal to $ 2 $ or $ 3 $ . The probability that Andrew wins is $ 2/3 $ . If Andrew chooses $ a=3 $ , the probability of winning will be $ 1/3 $ . If $ a=1 $ , the probability of winning is $ 0 $ .

In the second sample test: Andrew wins if $ c $ is equal to $ 1 $ and $ 2 $ . The probability that Andrew wins is $ 1/2 $ . For other choices of $ a $ the probability of winning is less.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
2```

# 题解

## 作者：LKY928261 (赞：10)

## 题目分析

首先，根据七上的数学知识，当 $c$ 满足 $|c-a|<|c-m|$ 时，一定是以下三种情况之一：

- $c<a<m$
- $c>a>m$
- $a<c<m$ 且 $c-a<m-c$

(~~七上数学课没听的请移步其他题解~~)

然后在草稿纸上算一算，可以发现：

- 当 $a<m$ 时，$a=m-1$ 的概率最大；
- 当 $a>m$ 时，$a=m+1$ 的概率最大。

由此可知：

- 当 $m<=n/2$ 时，$a$ 取 $m+1$ 最优；
- 否则，$a$ 取 $m-1$ 最优；

这不就行了！

主要代码：

```cpp
if(m<=n/2)cout<<m+1<<"\n";
else cout<<m-1<<"\n";
```

## 一个巨坑

根据这样写完代码，提交以后却错了是怎么回事？

再仔细一想，发现当输入 `1 1` 时应当输出 `1`！这是一个巨坑。

因此再加一个特判：

```cpp
if(n==1&&m==1)cout<<"1\n";
```

## 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	if(n==1&&m==1)cout<<"1\n";//巨坑
	else if(m<=n/2)cout<<m+1<<"\n";
	else cout<<m-1<<"\n";
	//本人从不打return 0;
}
```

---

## 作者：珅肐 (赞：4)

题目要使$|c-a|<|c-m|$成立

即要使随机出来的$c$距离$a$比距离$m$要近

要想尽可能使式子成立，就需要把$a$选在$m$附近，让随机出来的数字距离$a$都是最近的才行。

那么很显然，要么选择$m-1$，要么选择$m+1$.

进行区间大小的比对

若$m-1>=n-(m+1)+1$即选$m-1$更优

否则选$m+1$更优
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int main(){
	int n=read(),m=read();
	if(n==1 && m==1){puts("1");return 0;}
	if(m-1>=n-m)printf("%d\n",m-1);
	else printf("%d\n",m+1);
	return 0;
}

```


---

## 作者：伟大的王夫子 (赞：3)

针对此题，我们要画一个图

![](https://cdn.luogu.com.cn/upload/image_hosting/tenyqlql.png?x-oss-process=image)
首先特判$n=1, m=1$

那么直接输出$1$

否则$a\not = m$

如果说选取的$a < m$ 那么满足条件的$c$在左边括号区域

选取$a  = m - 1$ 可让其最大,$c$的值有$m-1$种

否则，若$a > m$,那么符合条件的$c$在右边括号区域

可选取$a = m + 1$使其最大，$c$的值有$n - (m+1) + 1 = n - m$种

判断一下那个大。解不等式$n - m > m -1$得

$n > 2m-1$根据整数的离散型，$n \ge 2m$

用if-else判断一下即可

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int main() {
	cin >> n >> m;
	if (m == 1) printf("%d\n", min(m + 1, n));
	else if (n >= 2 * m) printf("%d", m + 1);
	else printf("%d", m - 1);
} 
```

---

## 作者：Durancer (赞：2)

## 一道概率学题目，主要是找赢得概率更大的地方

------------
首先，我们分为三种情况

1、2m<n 即m在n/2的左边

2、2m==n 即m在n/2的点上，也是很容易出错的地方

3、2m>n 即m在n/2的右边；


------------


首先我们在讨论之前，我们要集中思考一下，a放在哪个地方更优，好，首先来一个对照试验，变量为a距离m的距离


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/ig6n1ts0.png)

------------
![](https://cdn.luogu.com.cn/upload/image_hosting/nvk9f5et.png)


------------
另一种情况也一样，由此可见，当|m-a|=1时，距离可能为最大

------------


### ok，先看第一种情况！

分为a在m右边和a在m左边讨论

让我们先画图解释
![](https://cdn.luogu.com.cn/upload/image_hosting/oe718jju.png)

------------
当a在m左边时，胜率如图所示，约为一个半的格子


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/ig6n1ts0.png)


------------
当a在m右边时，胜率如图所示，约为五个半的格子

显然，当a=m+1时胜率更大


------------
### 第二种情况！！


------------
很多同学可能会想的是，m这个线段的中间，所以+1-1都一样啊
那么请看题目，这是从1开始的！！！，话不多说，上图

------------
![](https://cdn.luogu.com.cn/upload/image_hosting/cpvnr9tm.png)


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/iz1zq0pp.png)


------------
由此可见，当a在m+1的位置时，要比在m-1的位置m的胜率要大，所以这种情况要选择m+1的位置，可以和第一种情况结合起来


------------
### 第三种情况！！！


------------
话不多说，仍然是上图片
![](https://cdn.luogu.com.cn/upload/image_hosting/1y42j9zt.png)


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/nj80mymj.png)


------------
由此可见a=m-1时m的胜率会更大一些


------------
### 最后上代码，简单易懂


------------
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	//分2m<n即m在n的一半的左边
	//还有2m>=n即在n一半以及右边来判断；
	//——————————————————————分割线———————2m<=n———————————
	if(m==1&&n==1) 
	{
		cout<<1<<endl;
		return 0; 
	}
	if(2*m<=n)
	{
		cout<<m+1<<endl;
		return 0;
	}
	//——————————————————————分割线————————2m>n——————————
	if(2*m>n)
	{
		cout<<m-1<<endl;
		return 0;
	}
	return 0;
}
```


------------
初次叫题解，图片可能截得不是很均匀，望见谅~~

---

## 作者：FCB_Yiyang2006✈ (赞：2)

# 看到题目名字进来的，苦思冥想发现偏数学的方法
思路：这是一道概率问题，可以让所有的用平均数来作比较。
细节：蒟蒻第一次就错了:
# WA!!!（万绿丛中一点红）
1 1时输出1！！！

上代码（蒟蒻代码仅供参考）
```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
int main()//主晗二叉树
{
   int n,m,mid;
   cin>>n>>m;
   mid=(n+1)/2;//平均值
   if(m==1&&n==1)//特判
   {
	cout<<1;
   }
   //下面的简单知道概率的人都懂
   else if(m<mid)
   { 
	cout<<m+1;
   }
   else if(m>mid)
   {
	cout<<m-1;
   }
   else
   {
   	if(n%2==1)
	{ 
	cout<<m-1;
	}
   	else 
	{
	cout<<m+1<<endl;
	}
   }
   return 0;//结束了！结束了！结束了！
}
```
（~~少点注释，方便复制提交AC~~）


---

## 作者：KEBrantily (赞：1)


# **题意转化：**
    一条长为n的路，路上有一点m，问你在什么地方再设一点a可以使路上**任意一点**到点a的概率大于到点m的概率
    

------------


我们可以数形结合

![](https://cdn.luogu.com.cn/upload/image_hosting/uutc357u.png)


所谓概率更大，也就是说**从离点m更远的一端到点a的长度小于到点m的长度**
（因为此长度内所有的点到a的距离都小于到m的距离）

如图，在被绿色框住的范围内的点到点a的距离都小于到点m的距离，也就是所谓的**概率**，所以我们可以知道，**若被绿色盖住的范围更大，则到点a距离小于到点m距离的概率更大**

------------


## 具体做法如下

1.  因为这道题的点都是整数，所以先特判一下，当**n=1时输出1**（路的长度就为1，m<=n，所以m也只能为1，因此必不可能出现一点a使得这个端点到a的距离小于m，只能等于，此时概率为0，就愉快的输出1就好了）


1. 对于长度不是1的道路，我们做如下处理：

因为上面说了是要使**从离m更远的一端到m的距离大于到a的距离**

### 即

  我们把道路的中点mid看做一个分界点，**当m处于[0,mid]中时，a要属于(m，n]才能使端点到a的距离更小**，且当a与m的差值为1时（即**a=m+1**），才能使所谓的概率更大

同理，**当m处于[mid,n]时，a要属于[0,mid)且**a=m-1**才能使概率更大**


------------

因为长度什么的都是整数，对于除法运算有限制，所以我分奇数和偶数两种情况写（注意不要忘记考虑**m正好位于中点**的情况）

### 代码

```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define maxn 100010

using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n==1){cout<<1;return 0;}
	if(n%2==0&&m>n/2) cout<<m-1;
	if(n%2==0&&m<=n/2) cout<<m+1;
	if(n%2!=0&&m>=n/2+1) cout<<m-1;
	if(n%2!=0&&m<n/2+1) cout<<m+1;
	return 0;
}
```
码风丑勿喷
##### （因为排版等问题一遍审核没过，所以我准备~~写点骚话~~重新排一下版）

---

## 作者：Imy_bisLy (赞：1)

这个题我本身，没有什么思路，看到题面就傻了，看了看题解我，才领会到题目的意思

题目要使|c-a|<|c-m|成立

即要使随机出来的c距离a比距离m要近

要想尽可能使式子成立，就需要把a选在m附近，让随机出来的数字距离a都是最近的才行。

那么很显然，要么选择m-1，要么选择m+1

#### 此时，m到达a的距离最小为1，那么此时随机的c只要位于a的同侧，或者位于异侧的 m +/- 1 的远处那么|c-a|<|c-m|这个式子便是成立的

进行区间大小的比对

若m-1>=n-(m+1)+1即选m-1m−1更优

否则选m+1更优
 					
  					by---珅肐
 ### 解释一下这段话的意思，其实题目中的a可以是1~n之间的任意一个值要求的是概率
  也就是说：如果左区间的区间越大，那么a在m-1的位置时得到
|c-a|<|c-m|的概率越大，反之越小，那么a再m+1的位置上面更优。
这怕是给自己写的题解
```
## #include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	if(n==1&&m==1) {
		printf("1");
		return 0;	
	}
	if(m-1>=n-m)//m前的区间大于m后的区间 
	printf("%d",m-1);//m前的区间更优 
	else printf("%d",m+1);//否则m后的区间更优
	//概率更大 
	return 0;
} 
```


---

## 作者：Histone (赞：1)

考虑两种情况

- $2m \leq n$

- $2m > n$

图中P点表示 **$\frac{n}{2}$**。

![](https://cdn.luogu.com.cn/upload/image_hosting/qfvxxp8h.png)

我们知道，要使 **$\mid c-a \mid < \mid c-m \mid$** 概率最大

就要使随机出来的 $1-n$ 离$a$比较近。

现在我们想象从 $1-n$ 中间点是 **$P (\frac{n}{2})$**

可以看到，当$2m \leq n$时，$M_1$在$P$的左边，所以我们让$a = m+1$为最优解。

同理，当$2m > n$时，$M_1$在$P$的右边，所以我们让$a = m-1$为最优解。

代码：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

inline int read(){
	re int ans = 0;re bool f = 1;re char ch = getchar();
	while(ch<'0'||ch>'9'){if (ch=='-')f = 0;ch = getchar();}
	while(ch>='0'&&ch<='9'){
		ans = (ans<<3)+(ans<<1)+(ch^48);
		ch = getchar();
	}
	return f?ans:~(ans-1);
}

signed main(void){
	int n = read(),m = read();
	if(n==1&&m==1)
		printf("1\n");
	else if(n>=2*m)
		printf("%d\n",m+1);
	else
		printf("%d\n",m-1);
	return 0;
}
```


---

## 作者：金霸王电池 (赞：0)

这是一道概率题。

首先我们化简一下题目中的式子。

$\lvert c-a \rvert<\lvert c-m \rvert$

$\Leftrightarrow c^2-2ca+a^2<c^2-2cm+m^2$

$\Leftrightarrow -2ca+a^2<-2cm+m^2$

$\Leftrightarrow 2(a-m)c>a^2-m^2$

$\Leftrightarrow $ 若 $a<m$，$c\le \lfloor \frac{a+m}{2}\rfloor$;若 $a>m$，$c\ge \lceil \frac{a+m}{2}\rceil$

因此， $a$ 取 $c-1$ 或 $c+1$ 时概率最大。

需要说明的是，$m=n=1$ 时 $a=1$ ，需要特判。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n==1&&m==1){//特判
		cout<<1;
		return 0;
	}
	if(m-1>=n-m)cout<<m-1;
	else cout<<m+1;
	return 0;
} 
```




---

## 作者：XL4453 (赞：0)

题目分析:

考虑贪心。

将1到 $n$ 分为三个区间：$\left[1,m\right]$ ; $\{m\}$ ; $\left[m+1,n\right]$。

对于单独的一个 $m$，无论如何都不可能找到可以使得这个点满足条件的 $a$，所以也就不考虑他了。

那么也就是要在 $\left[1,m\right]$ 和 $\left[m+1,n\right]$ 中找一个更大的满足条件，而且这两个区间是冲突的，也就是满足一个一定有另一个不满足。

然后可以发现，满足条件的 $a$ 一定在 $m$ 的旁边，否则会发现在可能满足条件的一侧也会存在一部分点不满足条件。

注意需要特判 $n$ 和 $m$ 都等于一的情况，此时区间里只有一个数，直接输出即可。


------------

代码：
```cpp
#include<cstdio>
using namespace std;
int n,m,ans;
int main(){
	scanf("%d%d",&n,&m);
	if(m==1&&n==1){
		printf("1");
		return 0;
	}
	if(n-m+1>m)ans=m+1;
	else ans=m-1;
	if(ans==0)ans=1;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Zxsoul (赞：0)

# 构造学水题

### 题面： 

 •  给 n，m，求一个数 a (1 ≤ a ≤ n)，使得当 c 在 1 到 n 的整
数中随机取值时, |c − a| < |c − m| 成立的概率最大。

 • n, m <= 10^9, m <= n
 
 ---
### 思路：

- $a$ 在 $1-n$ 之间，$m$ 已知，使 $a$ 到 $c$ 的距离小于$ m$ 到 $c$ 的距离

- 如果 $2m > n$，则 $\ m\ $ 位于靠近 $\ n\ $ 的一侧，此时只要取$ \ <m\ $ 的数即可，因为 $\ m$取整数，要使概率最大,则$\ a\ $取 $\ m-1\ $是最大   
- 同理，$2m > n$，则 $\ m\ $ 位于靠近$\ 1\ $ 的一侧，此时只要取$ \ >m\ $ 的数即可，要使概率最大,则$\ a\ $取 $\ m+1\ $是最大

- 	$${a\ \in\ N^* \ ,c\ \in\ N^*} $$
- 水题，但还是要写，因为自己绝对值这方面不怎么理解，比赛时也是误打误撞写出来的，！！

## 由于我在Typro做的公式写不上，就委屈大家看图片了，抱歉，抱歉。
					
![](https://cdn.luogu.com.cn/upload/image_hosting/jtp24xqt.png)
# 我的Code简单易懂
```cpp
/*
  CF570B Simple Game
  2020/10/4
  by BZQ
*/ 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cctype>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
using namespace std;
const int manx = 50009;
typedef long long LL;
int n,m;
int main(){
	cin >> n >> m;
	if(n == 1)//因为所有数都需要取整数，所以特判一下 
	{
		cout << 1;
		return 0;//因为当前也满足下面的条件，为了防止再次运行，return 0；	
	} 
    if(m*2 <= n) cout << m + 1;//等号放在下面也可以，但不可以同时成立。 
    if(m*2 > n) cout << m - 1;
    return 0;
	 
}
```
# 感谢观看~
				
				

					

---

