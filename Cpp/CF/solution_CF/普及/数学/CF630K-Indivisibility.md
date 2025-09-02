# Indivisibility

## 题目描述

开发电脑游戏的IT City公司，准备改善员工奖励机制。奖励机制是这样的，当游戏的注册用户开始花钱购买产品时，公司会精确的跟踪每笔交易。每次当交易次数不能被2~10之间的任何数字整除时，这个游戏的每个开发者都会得到一个小奖励。

游戏设计师Petya知道公司即将发布一款由他开发的新游戏。根据他的经验，他预测第一个月将会有n个人购买这个游戏。现在Petya想知道他能够获得多少次奖励？

## 样例 #1

### 输入

```
12
```

### 输出

```
2```

# 题解

## 作者：ivyjiao (赞：12)

这道题看似是求不能被 $2$ 到 $10$ 中任意一个数整除的数的数量，实际上只有 $2$ $3$ $5$ $7$，因为 $2$ 到 $10$ 其它数都是这些数的倍数。

我们知道，$n$ 中 $2$ 的倍数有 $\lfloor\dfrac{n}{2}\rfloor$ 个，$n$ 中 $3$ 的倍数有 $\lfloor\dfrac{n}{3}\rfloor$ 个，$n$ 中 $6$ 的倍数有 $\lfloor\dfrac{n}{6}\rfloor$ 个。但是算 $2$ $3$ 时会把 $6$ 减两遍，所以要加回来。所以，式子是：

$$n-\lfloor\dfrac{n}{2}\rfloor-\lfloor\dfrac{n}{3}\rfloor+\lfloor\dfrac{n}{6}\rfloor$$

以此类推 $5$ $7$ 的情况，得出最终的式子：

$$n-\lfloor\dfrac{n}{2}\rfloor-\lfloor\dfrac{n}{3}\rfloor-\lfloor\dfrac{n}{5}\rfloor+\lfloor\dfrac{n}{6}\rfloor-\lfloor\dfrac{n}{7}\rfloor+\lfloor\dfrac{n}{10}\rfloor+\lfloor\dfrac{n}{14}\rfloor+\lfloor\dfrac{n}{15}\rfloor+\lfloor\dfrac{n}{21}\rfloor-\lfloor\dfrac{n}{30}\rfloor+\lfloor\dfrac{n}{35}\rfloor-\lfloor\dfrac{n}{42}\rfloor-\lfloor\dfrac{n}{70}\rfloor-\lfloor\dfrac{n}{105}\rfloor+\lfloor\dfrac{n}{210}\rfloor$$

（其实正常推出来的式子顺序不是这样的，~~为了我的强迫症~~已经按分母从小到大排序）

由于 $n\leq 10^{18}$，所以要开 `long long`。

```cpp
#include<iostream>
using namespace std;
long long n;
int main(){
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/6-n/7-n/10-n/14-n/15-n/21-n/30+n/35+n/42+n/70+n/105-n/210)<<endl;
}
```

评价：大水绿。

---

## 作者：Zxsoul (赞：8)

## 解释目的：
看了一楼大佬的代码觉得原理讲的确实详细，但需要**容斥四个数**时就只给出了公式，没有**详细讲解**。（当然我也是没看懂，所以我就用把四个数**分成**三个数的容斥公式），在我看来比较好理解。虽然我的代码公式最后化简后也是一楼大佬的式子，但我的有分步，比较好理解。
# 思路：
  题目大意我就不说了。这是一个典型的**容斥**问题，关于**容斥原理**下面会给出。
  
  1. 原理：|A∪B∪C| = |A|+|B|+|C| - |A∩B| - |B∩C| - |C∩A| + |A∩B∩C| （这是三个数是的容斥公式）
  
  2. 理论就是保证和中没有重复的数（最后详解，给大家解释一下，就不用了麻烦大家百度了）
  3. 看似被2~10整除，其实就是2,3,5,7 所以此时需要容斥的内容就是：2,3,5,7的所有倍数，且不重复。
  4. 举个例子 2和3的倍数之中6以及6的倍数是被多加了一遍，所以n/2+n/3-n/6。
  5. 2,3,5的倍数时，重复的倍数就是6,10,15,按上边公式：n/2+n/3+n/5-n/6-n/10-n/15+n/30;
  6. 其实就是重复的部分就是两个数的最小公倍数。
  7.
    
  ### 看图理解![](https://cdn.luogu.com.cn/upload/image_hosting/j0vk4rts.png)
  ---
  ## 原理明白了就上代码
  ```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long  n,rongchi,a,b,c,d;//必须用long long，int 会爆，看题目数据范围（n（1≤n≤10^18））。 
	cin>>n;
	a=n/2+n/3+n/5-n/6-n/10-n/15+n/30;//我用a,b,c,d将四个数拆成每组三个的个体容斥问题，最后再相加。有人会疑问这样做一定会重复的，所以最后在进行相减。
	d=n/2+n/5+n/7-n/10-n/35-n/14+n/70;
	b=n/2+n/3+n/7-n/6-n/14-n/21+n/42;
	c=n/3+n/5+n/7-n/15-n/21-n/35+n/105;//减去重复的部分这一块需要画图说明，多减得就加，多加就减。
    rongchi=a+b+c+d-n/2-n/2-n/3-n/3-n/5-n/5-n/7-n/7+n/6+n/10+n/15+n/14+n/21+n/35-n/210;
    //n/210不是因为合并时的重复，而是当四个数存在时，第四个数与前三个数的公共部分在前面是没有的，所以要特别减掉。 
	cout<<n-rongchi;
}
```
第一次题解，公式不知道怎么写出那种模样，谅解一下。
用心写题解。
# 感谢观看~
  

---

## 作者：Enigmatic (赞：3)

这题本来是道容斥原理，但题目数据范围过于小了

此题说是2到10，实际上有效的只有2,3,5,7 

其余的数都是2或3或5或7的倍数

我们知道，n中2的倍数是n/2

n中3的倍数是n/3

n中2,3的倍数是n/2+n/3

不过这样会把6的倍数算两遍

所以n中2,3的倍数就是n/2+n/3-n/6

依此类推2,3,5的倍数是n/2+n/3+n/5-n/6-n/10-n/15+n/30

2,3,5,7的倍数是n/2+n/3+n/5+n/7-n/6-n/10-n/14-n/15-n/21-n/35+n/30+n/42+n/70+n/105-n/210（想一想，为什么？）

代码如下
```
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
int main()
{
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/7-n/6-n/10-n/14-n/15-n/21-n/35+n/30+n/42+n/70+n/105-n/210)<<endl;
	return 0; 
} 

---

## 作者：ecxjs (赞：2)

假如一个数不能被 $2$ 至 $9$ 中的所有数整除，那就一定不是 $2$，$3$，$5$，$7$ 的倍数。所以我们一个个来，慢慢理清思路，就能做出了。不难发现，这道题是一道容斥原理。

1. 先减去 $2$，$3$，$5$，$7$ 的倍数：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
int main()
{
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/7);
   	return 0;
}
```
2. 由于刚刚 $2$ 的倍数减了一次，$3$ 的倍数也减了一次，也就是 $2$ 和 $3$ 的公倍数的倍数被多减了一次，还得把它加上去。代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
int main()
{
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/7-n/6-n/10-n/14-n/15-n/21-n/35）;
   	return 0;
}
```

3. $2$、$3$、$5$ 的公倍数的倍数减了又加了三次，所以还要继续减一次：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
int main()
{
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/7-n/6-n/10-n/14-n/15-n/21-n/35+n/30+n/42+n/70+n/105);
    	return 0;
}
```

4. $2$，$3$，$5$，$7$ 的最小公倍数 $210$ 的倍数，减了 $4$ 次，理解为 $-4$ 次，加了 $6$ 次，理解为 $-4+6=2$ 次，又减了四次，理解为 $2-(-4)=-2$ 次，所以减掉两次，还得加一次。这下就好了， $AC$ 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
int main()
{
	cin>>n;
	cout<<n-(n/2+n/3+n/5+n/7-n/6-n/10-n/14-n/15-n/21-n/35+n/30+n/42+n/70+n/105-n/210)<<endl;
    	return 0;
} 

```

所以大家做题的时候，需要先看题，然后逐步分析，最后就能 $AC$ ：

![](https://www.luogu.com.cn/images/congratulation.png)

为了让大家更加放心的食用，我的提交记录：[this](https://www.luogu.com.cn/record/96314292)。

本蒟蒻水平较差，大佬轻喷。


---

## 作者：int32 (赞：1)

容斥水题。

题目说是 $2\sim10$，其实只用考虑 $2,3,5,7$ 的整除情况，。因为 $1$ 一定被整除，$4,6,8,9,10$ 都是 $2,3,5,7$ 中至少一个数的倍数。

如此，先减去 $\dfrac{n}2+\dfrac{n}3+\dfrac{n}5+\dfrac{n}7$，再加上 $\dfrac{n}{2\times3}+\dfrac{n}{2\times5}+\dfrac{n}{2\times7}+\dfrac{n}{3\times5}+\dfrac{n}{3\times7}+\dfrac{n}{5\times7}$，再减去 $\dfrac{n}{2\times3\times5}+\dfrac{n}{2\times3\times7}+\dfrac{n}{2\times5\times7}+\dfrac{n}{3\times5\times7}$，最后加上 $\dfrac{n}{2\times3\times5\times7}$。

输出即可。

---

## 作者：庄nnnn额 (赞：1)

这里的 $x\sim y$，全部指 $\left[x,y\right]$。
### 简化题意
>求出 $n$ 以内不能被 $2\sim10$ 之间的任何整数整除的数的数量。

### 解题思路
首先，我们要知道一个定理：
>一个能被 $a$ 整除的数 $n$ ，加上一个不能被 $a$ 整除的数 $m$ ，结果一定不能被 $a$ 整除。

定理很简单，这里就不给证明了。

所以，一个不能被 $2\sim10$ 之间的任何整数整除的数 $n$，加上一个**能被 $2\sim10$ 之间的任何整数整除的数** $m$，也是一个不能被 $2\sim10$ 之间的任何整数整除的数。注意，$m$ 必须**能被所有的数整除**，否则就可能不行。比如 $n=4$，只能被 $2$ 和 $4$ 整除，$m=11$，不能被所有的数整除，$n+m=15$，$15$ 能被 $3$ 和 $5$ 整除。

而我们知道，最小的能被 $2\sim10$ 之间的任何整数整除的数，是 $\operatorname{lcm}(2,3,4,\cdots,9,10)=2520$。这样，所有能被 $2\sim10$ 之间的任何整数整除的数都是 $2520$ 的倍数。

所以，任何不能被 $2\sim10$ 之间的任何整数整除的数，都可以看成 $2520$ 的倍数（或 $0$ ）加上一个比 $2520$ 小的一个不能被 $2\sim10$ 之间的任何整数整除的数。

那么，我们可以把 $1\sim n$ 分成 $\left\lceil\frac{n}{2520}\right\rceil$ 份，前 $\left\lfloor\frac{n}{2520}\right\rfloor$ 份（①）每份长 $2520$，第 $i$ 份就是 $2520(i-1)+1\sim2520i$，最后一份（②）是剩下的。我们可以把①、②两部分（也有可能没有某一部分）分开处理。
### ①
这一部分，第 $i$ 份里的不能被 $2\sim10$ 之间的任何整数整除的数，都可以拆为第 $1$ 份里的一个不能被 $2\sim10$ 之间的任何整数整除的数加上 $2520(i-1)$。那么，这一部分里每一份里的不能被 $2\sim10$ 之间的任何整数整除的数是一样多的。所以，可以求出第一份（$1\sim2520$）里的不能被 $2\sim10$ 之间的任何整数整除的数的个数，再乘以份数（$\left\lfloor\frac{n}{2520}\right\rfloor$），就是这一部分的总个数了。

那么，重点来了。**怎么求 $1\sim2520$ 中不能被 $2\sim10$ 之间的任何整数整除的数的个数呢？**

其实，最简单的方法是：**写程序枚举啊！！！**

写个程序，枚举 $1\sim2520$ 中的数，挨个判断满不满足条件，最后输出总个数就行了。

**Code:**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	bool y;
	int s=0;
	for(int i=1;i<2520;i++){//挨个枚举
		y=1;
		for(int j=2；j<11；j++){//枚举因数
			if(i%j==0){//如果发现能被一个数整除，打上标记，退出
				y=0;
				break;
			}
		}
		if(y)++s;//如果没有发现标记，总个数++
	}
	printf("%d"，s);
	return 0;
}
```
运行程序，程序输出结果：
```
576
```
那么，$1\sim2520$ 中不能被 $2\sim10$ 之间的任何整数整除的数的个数出来了，这个部分的结果就好算了。
### ②
这一个部分，长度为 $n\bmod2025$，由于长度过短，直接暴力求。同①，求 $1\sim (n\bmod2025)$ 中不能被 $2\sim10$ 之间的任何整数整除的数的个数就行了。
## 你们最想要的来了：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long n;
	int sum=0;
	bool y;
	scanf("%lld"，&n);
	for(int i=1;i<=n%2520;i++){//②部分
		y=1;
		for(int j=2；j<11；j++){
			if(i%j==0){
				y=0;
				break;
			}
		}
		if(y)++sum;
	}
	printf("%lld",n/2520*576/*①部分*/+sum);
	return 0;
}
```
然后，就：[
![](https://www.luogu.com.cn/images/congratulation.png)](https://www.luogu.com.cn/record/69748446)

---

## 作者：chenpengda (赞：1)

**容斥**，因为一个数不能被$2$至$9$中的所有数整除，等价于不是$2$、$3$、$5$、$7$的倍数。

首先，假设所有数都符合条件。

**第一步**，先把答案中是$2$、$3$、$5$、$7$的倍数的数减去，

```cpp
ans-=n/2;
ans-=n/3;
ans-=n/5;
ans-=n/7;
```


**第二步**：这个时候因为$2$和$3$的公倍数的倍数被多减了一次（在$2$的倍数减一次，$3$的倍数减一次），要加上一次。其他的也同样如此。

```cpp
ans+=n/6;//2*3
ans+=n/10;//2*5
ans+=n/14;//2*7
ans+=n/15;//3*5
ans+=n/21;//3*7
ans+=n/35;//5*7
```

**第三步**：这个时候$2$、$3$、$5$的公倍数的倍数因为开始减了$3$次（$2$、$3$、$5$），然后第二步加了$3$次（$2\times 3$、$2\times 5$、$3\times 5$）所以还没有减，再减去一次，其他的也同样如此。

```cpp
//减去三个数的倍数 
ans-=n/30;//2*3*5
ans-=n/42;//2*3*7
ans-=n/70;//2*5*7
ans-=n/105;//3*5*7
```
**最后一步**，$2、3、5、7$的公倍数$210$的倍数，在开始减了$4$次，第二步加上了$6$次，第三部减了$4$次，相当于减了$2$次，所以再加上$1$次。

```cpp
ans+=n/210;
```
最后输出即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long n,ans=0;
	cin>>n;
	ans=n;
	ans-=n/2;
	ans-=n/3;
	ans-=n/5;
	ans-=n/7;
    
	ans+=n/6;
	ans+=n/10;
	ans+=n/14;
	ans+=n/15;
	ans+=n/21;
	ans+=n/35;
    
	ans-=n/30;
	ans-=n/42;
	ans-=n/70;
	ans-=n/105;
    
	ans+=n/210;
	cout<<ans; 
} 
```


---

## 作者：feecle6418 (赞：1)

这题就是最显然的容斥，直接用DFS处理即可。$[2,9]$ 中某 $k$ 个数的 $\mathrm{lcm}$ **对能被 $[2,9]$ 中的一些整除的数的个数的贡献**显然是 $(-1)^{k-1}\times n\div\mathrm{lcm}$（请好好理解这句话）。最后用 $n$ 减去累加的答案即可。

下面给出主体部分的代码：

```cpp
void DFS(int now,int left,int lastt,int all){
//now：目前dfs到第几个数
//left：还剩几个数
//all：能用的总数（本次容斥的k）
//lastt：上次选的数
	if(!left){
		long long lcc=1;
		for(int i=1;i<=all;i++){
			lcc=Lcm(lcc,a[i]);
			if(lcc>n)return ;
		}
		ans+=n/lcc*neg1[all-1];
		return ;
	}
	for(int i=lastt+1;i<=m-left+1;i++){
		a[now]=x[i];//x[i]=i+1,1<=i<=9,m=9
		DFS(now+1,left-1,i,all);
	}
}
```

---

## 作者：ruruo (赞：0)

# 写在前面

建议难度：普及-

标签：容斥

前置知识：[容斥原理](https://baike.baidu.com/link?url=0ynEuz18NtwFkJdT3nEo8kNp3DnDa3o5DaOkacoNdJq6Ztwk1m6O1MyZVwZvKcdj0KfJF8HAwHITIW_daSM-aPOjQ-k7rCwEN1kLrzZlNFh5yLqdssvkIq5YKB1HPCc__cqeEP8XW0-_LxHRvwNl3a)

# 分析

四元容斥定理：$|\,A\cup B\,\cup C\,\cup D|=|\,A\,|+|\,B\,|+|\,C\,|+|\,D\,|-|\,A\cap B\,|-|\,A\cap C\,|-|\,C\cap B\,|-|\,A\cap D\,|-|\,B\cap D\,|-|\,C\cap D\,|+|\,A\cap B\,\cap C|+|\,A\cap B\,\cap D|+|\,A\cap D\,\cap C|+|\,D\cap B\,\cap C|-|\,A\cap B\,\cap C\,\cap D|$

只要能被 $2, 3, 5, 7$ 中的一个整除即可满足题意，因为 $1$ 一定整除，$4, 6, 8, 10$ 能被 $2$ 整除， $9$ 能被 $3$ 整除。

最后代入四元容斥定理公式即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    cout << n - n / 2 - n / 3 - n / 5 - n / 7 + n / 6 + n / 10 + n / 14 + n / 15 + n / 21 + n / 35 - n / 30 - n / 42 - n / 70 - n / 105 + n / 210 << endl;
    return 0;
}
```


---

## 作者：FJ_Farmer_Johhn (赞：0)

# 题意
本题的题意很简单，就不多加阐述了
# 思路
## 前置知识：容斥原理
小学奥数内容，不懂的可以戳[这里](https://baike.baidu.com/link?url=dsyCAt4kxcvIxFKZk8QOOuJ0nQ8YxKytKdnbH2WVMCdH--3GQlCcOCwQy0iqRLWvAkmmWZGx6b_qLbACTT1tqyiC2d2X0jh8c2Lybq6iBGXG3dfuxj31t9TFteH2w1QtwpY5SvaTovrnn_6-sfpKGq)
## 解题过程
首先，本题就是要减去2~10之间每一个数的整数倍，而经简单思考可得实际上就是减去其中质数的整数倍，即2,3,5,7的整数倍，可列出式子：
$$ ans=n-n/2-n/3-n/5-n/7 $$
然而，我们发现事情并没有那么简单，因为根据容斥原理可得可以两个数的乘积整除的数是被多减了一次的，因此我们要把它们加回来，所以在上一步的基础上，得到式子：
$$ ans=n-n/2-n/3-n/5-n/7+n/6+n/10+n/14+n/15+n/21+n/35 $$
以此类推，减去三个数的乘积，加上四个数的乘积，就可以得出最终的式子：
$$ ans=n-n/2-n/3-n/5-n/7+n/6+n/10+n/14+n/15+n/21+n/35-n/30-n/70-n/42-n/105+n/210 $$
## 温馨提示
数据范围是1e18，别忘了开long long。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
int main()
{
    scanf("%lld",&x);
    printf("%lld",x-x/2-x/3-x/5-x/7+x/6+x/10+x/14+x/15+x/21+x/35-x/30-x/70-x/42-x/105+x/210);
    return 0;
}
```
完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：_wjr_ (赞：0)

前置知识：[容斥原理](https://baike.baidu.com/link?url=LNym9s5tKAHfi7K_bD261RR-bZ1TItRp5y5quvKC3LDyd1Ym-FbBc5LN5Ur7gT_ioYDVunOfgNYwgI7mDDFAK-YiW1vHKY3BU4ebBfWkMN5wvLoQ3UYcN920mmoe0FGq0UFWro7VLg6oKbJ61uZT_K)

本题题目代码难度不大，主要原因是它思考的难度。

由于题目中给定数据范围是 $n \le 10^{18}$，所以普通的枚举等复杂度为 $O(n)$ 的代码无法通过此题。

那该怎么办捏？

其实，这道题可以很好的运用容斥原理解决。

首先，我们需要明确一件事情：

如果一个正整数 $n$ 不能被 $2,3,5,7$ 中任何一个数整除，那它就不能被 $2$ 至 $9$ 中任意一个数整除。

然后，我们可以画出一个形如下图的四维文氏图：

![](https://cdn.luogu.com.cn/upload/image_hosting/djqoitz8.png)

其中，`2x` 表示 $2$ 的倍数，`3x` 表示 $3$ 的倍数 $\cdots$ 

而不包括在四个椭圆内部的就是不能被 $2,3,5,7$ 中任何一个数整除的数。我们需要求出的就是 $1,2,\cdots,n$ 中这样的数。

为求出这类数的个数，我们可以首先求出包含在四个椭圆内的数，再用 $n$ 减去这个数。

那，四个椭圆内的数的个数是多少呢？

在下式中，我们把 `从 1 到 n 中所有 a 的倍数` 替换为 $n_a$，其中 $a$ 为正整数。

从前置知识中，我们可以知道，在这四个椭圆内的数 $x = n_2 + n_3 + n_5 + n_7 - n_6 - n_{10} - n_{14} - n_{15} - n_{21} - n_{35} + n_{30} + n_{42} + n_{70} + n_{105} - n_{210}$。

那么， $n - x$ 即为所求。

于是，我们便可以写出如下显而易见的代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

long long n;

int main()
{
	cin >> n;
	cout << n - (n / 2 + n / 3 + n / 5 + n / 7 - n / 6 - n / 10 - n / 14 - n / 15 - n / 21 - n / 35 + n / 30 + n / 42 + n / 70 + n / 105 - n / 210) << endl;//计算上述 x 的值，然后用 n 减去 x 即为所求
    return 0;
}
```

完结撒花~

---

## 作者：fengxiaoyi (赞：0)

### 修改日志

$2022/11/7:$ 把 `\mod` 改成了 `\bmod`。

### 思路

**容斥原理**

如果不懂容斥原理，请自行查阅书籍。

要想获得奖励，当且仅当交易数 $k\bmod \lbrace 2,3,4,5,6,7,8,9,10 \rbrace \ne 0$，就这用容斥原理找出可获得奖励集合 $A=\lbrace x\in N| x\bmod \lbrace 2,3,4,5,6,7,8,9,10 \rbrace \ne 0\rbrace$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
	scanf("%lld",&n);
	printf("%lld",n-n/2-n/3-n/5-n/7+n/6+n/10+n/14+n/15+n/21+n/35-n/30-n/105-n/70-n/42+n/210);
	return 0;
}
```

---

## 作者：OLE_OIer (赞：0)

这道题是一道简单的组合数学题。

前置知识：容斥原理

容斥原理是这样的：

两元容斥原理：$|\,A \cup B\,|=|\,A\,|+|\,B\,|-|\,A \cap B\,|$

三元容斥原理：$|\,A\cup B\,\cup C|=|\,A\,|+|\,B\,|+|\,C\,|-|\,A\cap B\,|-|\,A\cap C\,|-|\,C\cap B\,|-|\,A\cap B\,\cap C|$

四元容斥原理：$|\,A\cup B\,\cup C\,\cup D|=|\,A\,|+|\,B\,|+|\,C\,|+|\,D\,|-|\,A\cap B\,|-|\,A\cap C\,|-|\,C\cap B\,|-|\,A\cap D\,|-|\,B\cap D\,|-|\,C\cap D\,|+|\,A\cap B\,\cap C|+|\,A\cap B\,\cap D|+|\,A\cap D\,\cap C|+|\,D\cap B\,\cap C|-|\,A\cap B\,\cap C\,\cap D|$

只要是 $2$ 或 $3$ 或 $5$ 或 $7$ 的倍数的都可以被 $[\,2,10\, ]$ 中的一个数整除,直接代入四元容斥的公式即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n;
	cin>>n;
	cout<<n-
	(n/2+n/3+n/5+n/7)
	+(n/6+n/10+n/14+n/15+n/21+n/35)
	-(n/30+n/42+n/70+n/105)+(n/210);
	return 0;
}
```

---

