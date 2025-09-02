# [LnOI2019SP] 龟速单项式变换(SMT)

## 题目背景

题目提供者：朝田诗乃

众所周知，这是一题签到题。

## 题目描述

有如下定义：若正整数序列 $a$ 中存在连续若干个正整数的和为 $m$ 的倍数，则这个正整数序列 $a$ 被称为“$m$ 序列”。

给定 $n$ 和 $m$，你需要知道长度为 $n$ 的任意正整数序列 $a$ 是否都是“$m$ 序列”。

## 说明/提示

样例解释：存在反例 $[1, 2]$。

Subtask 1 (50 pts)：$1 \le n, m \le 5$。

Subtask 2 (50 pts)：$1 \le n, m \le {10}^{18}$。

## 样例 #1

### 输入

```
2 4
```

### 输出

```
NO
```

# 题解

## 作者：ShineEternal (赞：49)

# 题目链接：

https://www.luogu.org/problem/P5497

# 分析：
我们如果看一眼题面却没有头绪不妨看一眼数据，一看到$10^{18}$，我们就大概能猜到这是一道重在思维的规律题。

首先此题不要误认为是1~n的正整数序列（也就只有我这么想？）然后我们就只能被逼的走投无路寻找内在的关系

此时我们连前缀和数组也根本无法使用，但在模拟小数据时可以发现以下性质：

- 如果一个数%m不为0，则可能有$m-1$种取值

- 而如果序列中超过了m-1个数，就一定有两个数%m取值相同

那么我们设前缀和为$s[i]$（此数组实际无法求得）

这时候就可以把前缀和看成一个序列

如果这个序列长度超过$m-1$，那么就必有两个数%m相等

**上面这一条应该不难证明，限于篇幅原因不详细叙述，可以来参考[这篇blog](https://45475.blog.luogu.org/luo-gu-ri-bao)，是我之前的一篇没过的日报，所以大神就不用进去了QAQ**

这两个数%m相等，设为$s[i],s[j](i>j)$,即$s[i]$ $mod$ $m=s[j]$ $mod$ $m$

所以(s[i]-s[j])%m==0

即为j~i区间的和是题目所求的

### 于是问题就简单了，序列长度n>m-1,即n>=m，则YES，否则NO

# code：

```cpp

#include<cstdio>
using namespace std;
int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	if(n>=m)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
```

求过求赞喔

---

## 作者：引领天下 (赞：33)

QAQ我比赛的时候居然煞笔了没想出正解……

我比赛的时候不想动脑子，这样打的：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){puts("YES");}
```

70。。。

其实，大家想一下，如果$n<m$，则肯定能构造一组数据，因为$x%m$的余数就有$m-1$种，所以必然能构造出一组数据。

于是得出结论1： **$n<m$时，答案为`NO`**

~~那么我们可以大胆猜想，不用证明，$n≥m$时一定就是`YES`了~~

好吧我们来证一下

根据抽屉原理，当$n≥m$时，必然有一个余数出现了2次

设这两个余数相同的数分别为$x_i,x_j$，可以以$x_i$为一个元素构造出一个“司$m$序列”，于是有：

$$ (sum_{1}+x_i)-(sum_{2}+x_j)\equiv 0(mod m) $$

进一步：

$$ sum_{1}+x_i\equiv sum_{2}+x_j (mod m) $$

又因为

$$ x_i\equiv x_j (mod m)$$

所以

$$ sum_{2}\equiv 0(mod m) $$

于是可以针对$x_j$构造出一个“司$m$序列”。

命题得证。

于是得到结论：

**$n<m$时，答案为`NO`；否则为`YES`**

代码就不贴了，讲的这么清楚了应该都能自己写出来

---

## 作者：Warriors_Cat (赞：10)

~~一道小学四年级数学题~~

本蒟蒻来一个较为严谨的证明吧。

### 证明如下：

令原序列为$a_1, a_2, ... a_n$

#### 1. n < m

只需让$a_1\equiv1, a_2\equiv 1 ... a_n\equiv1(mod\quad m)$即可使其不行，答案为NO

#### 2. n = m

令

$$S_1 = a_1$$

$$S_2 = a_1 + a_2$$

$$S_3 = a_1 + a_2 + a_3$$

$$...$$

$$S_n = a_1 + a_2 + a_3 + ... + a_n$$

一，若$S_i(i = 1, 2, ... n)\equiv0(mod\quad m)$，则可以，答案为YES

二，若没有$S_i(i = 1, 2, ... n)\equiv0(mod \quad m)$，则余数只能为$1, 2, 3, ... m - 1$。然而有n个数，又因为$n = m$，根据抽屉原理，必有两数$mod\quad m$同余。

不妨设$S_j\equiv S_k(j > k)(mod\quad m)$， 则$S_j - S_k\equiv 0(mod\quad m)$，这是一个$a_{k+1}$到$a_j$的区间，且$mod\quad m$余0。故答案为YES

#### 3. n > m

只需任取m个数，同上，答案为YES

综上，当$n < m$时，答案为NO，否则为YES

于是来敲代码啦...

## Code:

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n, m;//没开ll见祖宗qwq
int main(){
	scanf("%lld%lld", &n, &m);
	if(n >= m) cout << "YES";
	else cout << "NO";
	return 0;
}
```


---

## 作者：shame_djj (赞：10)

[[LnOI2019SP]龟速单项式变换(SMT)](https://www.luogu.org/problem/P5497#submit)

当我们看到一道很明显是规律题的题时，我们可以

从特殊的好想的例子入手

例如此题，考试时我想到的是：

如果是 n 个 1 呢。。。。。

如果 n 个 1 能满足的话

如果把其中的一个 1 变成 2 呢。。。。。

选上那个 2 ，再选 m - 2 个 1 就好了

所以。。。。。。

即使再变成其他数不也都一样吗

那就说明只要 n 个 1 能满足

那么就能满足题述条件

那么怎么样 n 个 1 就不能满足呢

显然，n 比 m 小的话，就不能

所以，代码如下

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    if (n >= m)
        puts ("YES");
    else
        puts ("NO");
    return 0;
}
```

然后，就 AC 了。。。。。。

祝大家在几十天后的 Noip 取得好成绩

也希望自己能更努力一些

---

## 作者：皎月半洒花 (赞：5)

其实是一道水题，以下是证明：

求证
$$\forall k\in\mathbb{N+},m|\sum_{i=0}^{n-1}(k+i)\Longleftrightarrow m\leq n$$

我们把和式展开成为：

$$nk+\frac{n(n-1)}{2}$$

这个东西是$m$的倍数，`+`连接说明应有$m|nk$。而$k$是任意的，所以要有$m|n$，即$n\mod m=0$。

而因为本题的坑点在于选的是`连续子序列`，所以只需要$n\geq m$，就$\exists i\leq n~s.t.i\mod m = 0$

```cpp
#include <cstdio>
#include <iostream>

#define LL long long

using namespace std ;
LL N, M ;

int main(){
    cin >> N >> M ;
    if (M > N) puts("NO") ; else puts("YES") ;
}

```

---

## 作者：rfsfreffr (赞：4)

# ~~由于我太蒟了，这是我比赛时唯一过掉的题目~~


### 题目大意:对于正整数序列a{k+1,k+2...k+n}(k>0),是否在k取任意正整数时，都会有连续若干个的正整数的和为m的倍数（当然，也可以是m）。

看题第一步：审查数据范围

注意到:前50分的数据较小，可以暴力模拟过（就是举反例），可对于后50分来说，就不行了，因为   $n$ 和 $m$ <= $10^{18}$ ,在这种数据范围下，就连$ O(\sqrt n ) $的做法都过不掉，所以要思考其的数论方法

第二步: 思考问题的解决方法

我们先思考在什么情况下,a{1,2,3,4,5...n} **一定**有连续子序列的之和为m的倍数

可以想到:当 n>=m时，其一定是有连续子序列的之和为m的倍数,因为可以只取m,所以此n有解。

我们可以对其继续推广，可以得到:对于a{k+1,k+2...k+n}(k>0)，只要$n>=m$,其一定是有连续子序列的之和为m的倍数。所以$n>=m就是问题的必要条件$

因为我们可以对问题进行转化：可以将其理解为在数轴原点的左边，任取一段长度为n的线，其中有没有覆盖到m的倍数。

由于m的倍数是每隔m隔单位长度就有一个的，所以只要这条线的长度**大于或等于**m其一定是有连续子序列的之和为m的倍数,再从其的几何意义来看，$n>=m$是a{k+1,k+2...k+n}(k>0)有连续若干个的正整数的和为m的倍数的必要条件。

结合上述思考过程就能写出其代码了:

# 代码:

~~~
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
	cin>>n>>m;
	if(n>=m) cout<<"YES";
	else cout<<"NO";
}
~~~

可是，稍加细心的dalao就能注意到，上述证明过程是有漏洞的,因为我只证明了$n>=m$是**必要条件**，并没有证明$n>=m$是**充分必要条件**,对于此证明，尚还不会，望有dalao能指出如何证明

### 此代码可AC，虽然简单，但知识的精华来自其的证明过程和思考过程。如果你只复制了代码AC，你只是加了一个AC量，并没有学习到更多知识。

# 因此 ,少抄题解代码，共建和谐洛谷




---

## 作者：kcs007 (赞：4)

这是一道真·小学数学题

如果n>=m则怎么凑都肯定能凑出来m的倍数，哪怕全都是1，全都是2，全都是3，怎么凑都肯定能凑出来m的倍数

反之当n<m的时候呢？  n个1的值肯定不是m的倍数，以为n小于m

直接上代码
```
#include<iostream>
#define ll long long
using namespace std;
int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);	
}
int main()
{
	ll n,m;
	cin>>n>>m;
	if(m<=n)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```
注意long long

---

## 作者：wkywkywky (赞：3)

一道非常好的签到题

令$S_{i}=\sum_{j=1}^{i}a_{j}$,即$S$序列为$a$序列的前缀和.
注意$S_{0}=a_{0}$
所以$\sum_{k=j}^{i}a_{k}$即$a_{j}+ \cdots +a_{i}=S_{i}-S_{j}$

所以正整数序列$a$中存在连续若干个正整数的和为$m$的倍数

等价于存在$S_{i} \equiv S_{j}(mod m) i,j\in[0,n]$

当$n\geq m$时$S_{0}$到$S_{n}$共$n+1$个数

由抽屉原理得必有两个$S_{i} \equiv S_{j}(mod m) i,j\in[0,n]$

此时正整数序列$a$中存在连续若干个正整数的和为$m$的倍数

否则令$a_{i}=1$，则不是“司$m$序列”

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
	cin>>n>>m;
	if(n<m)cout<<"NO";else cout<<"YES";
	return 0; 
}
```


---

## 作者：chinaxjh (赞：3)

# 分析
手动尝试几组数据，再稍微想一想就会发现如果m＞n则必然输出NO(n个1)，否则输出YES（通过容斥原理会发现可取的余数值最多为m-1，故m=n为最大上限）

注意开int64
# pascal ac code
```pascal
var
 n,m:longint;
begin
 readln(n,m);
 if m>n then writeln('NO')
 else writeln('YES');
end.
```

---

## 作者：JRzyh (赞：2)

啊这，这题满分20。

别被名字吓到，这题不是毒瘤数论题

------------

首先先证明个东西（与题没有太大关系）：

如果 $a=\{x_1,x_2,\dots,x_n\}$ 是司 $m$ 序列，则 $b=\{x_1\bmod m,x_2\bmod m,\dots,x_n\bmod m\}$ 也是司 $m$ 序列。

设连续区间是 $l$ 到 $r$ ：

就要证明

$$(\sum^{r}_{i=l}x_i)\bmod m=(\sum^{r}_{i=l}(x_i\bmod m))\bmod m$$

根据余数可加性，定理得证。

所以下面的 $b_i$ 指 $a_i\bmod m$ 。

先分情况讨论：

1.$n<m$

很容易举反例

$b_1=b_2=b_3=\dots=b_n=1$

和为 $n$ 。

因为 $n<m$ 所以 $n\bmod m=n\neq0$

2.$n\ge m$

令 $S$ 为 $b$ 的前缀和 $\bmod~m$，也就是

$$S_i=(\sum^{i}_{j=1}b_i)\bmod m$$

若有 $S_i(i=1,2,3,\dots,n)=0$，则答案是 YES

否则，那余数只能是 $1,2,3,\dots,m-1$，因为 $n\ge m$

就一定会有 $j,k(j\le k)$ 使得 $S_j=S_k$ ，那么就有 $S_j-S_k=0$，因为 $S$ 是前缀和数组，$S_j-S_k$ 就表示 $[j,k]$ 的一个区间和 $\bmod~m=0$


------------

综上所述，$n<m$ 答案是 ```YES```，$n\ge m$ 答案是 ```NO```

code:

```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int main()
{
	cin>>n>>m;
	cout<<(n>=m?"YES":"NO");
	return 0;
}

```

$40$ 多行的过程，两行核心代码，我都怀疑人生了。

写题解不易，点个赞吧OvO

---

## 作者：Skyjoy (赞：2)

~~好水的签到题~~

~~楼下XCY你发题解总是比我快一步~~

~~XCY你太巨了，我5年级才学的你4年级就学了~~

~~XCY你太巨了，我只能给你的题解作补充了~~

好吧，~~牢骚~~膜拜完了就进入正题吧！

这道题的情况分3类：$n<m$、$n=m$、$n>m$

1. $n<m$

反例很简单，$a_1 \equiv a_2 \equiv a_3 \equiv ... \equiv a_n \equiv 1 (mod\ m)$时，余数永远凑不出$m$，证毕。

2. $n=m$

在研究连续数列余数问题时，有一种很~~土~~有用的方法：$S$大法

什么是$S$大法？我们有一个$S$数列，$S_i=a_1+...+a_i(i=1,2,3...n)$ 。分析连续一段数的和$a_i+a_{i+1}+a_{i+2}+...+a_{j-1}+a_j$就可以直接分析$S_j-S_i$了，只用分析两个数，简单便捷。要知道暴力地在一个数列中分析一堆连续的个数不定的是极为麻烦的，时间还慢~~（复杂度$n^2$）~~，暴力是绝对跑不过去的。而$S$大法解决这件事是轻而易举的。

证明：

1）若$S_i(i=1,2,3...n) \equiv 0(mod\ m)$，即$a_1+...+a_i \equiv 0(mod\ m)$，证毕。

2）不存在1）的情况，余数：$1,2,3,...,m-1$。$\because n=m,m \div (m-1)=1......1$ $\therefore$ 必有$S_i \equiv S_j(mod\ m)$，不妨设$S_j > S_i$，则 $S_j-S_i \equiv 0 (mod\ m)$，证毕。

3. $n>m$

从中任取连续的$m$个数，情况同上。

综上所述，当$n<m$，答案是NO；当$n \geq m$，答案是YES。

# 接下来就是令人激动的代码实现了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;//不用高精，ll就够了
int main(){
	cin>>n>>m;
	if(n>=m){
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
	return 0;
}
```

谢谢各位哥老官们的观看，祝大家NOIp2019rp++！！！

---

## 作者：hmy521 (赞：2)

第一眼看到这个题时，第一反应是：双重循环！
### 思路（双重循环）
- 输入n,m（注意n和m≤10^18，必须开long long）

- 双重循环（i=1~n-1,j=i~n,在i循环里定义一个变量s（初始值为0），然后s每加一个数，就判断一下是否%m==0）

代码：

```
#pragma GCC optimize(3)//o3优化
#include<bits/stdc++.h>//万能头
using namespace std;
inline long long read(){//快读，至于怎么写的，自己理解程序吧
	long long x=0,w=1;
	char c;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*w;
}
int main(){
	long long n,m;
	n=read();
	m=read();
	for(int i=1;i<n;i++){
		int s=0;
		for (int j=i;i<=n;i++){
			s+=j;
			if (s%m==0){
				cout<<"YES"<<endl;
				return 0;//如果是，直接输出YES并结束程序
			}
		}
	}
	cout<<"NO"<<endl;
	return 0;
}
```


提交后，发现两个点AC，8个点
### TLE！

前面已经讲过，n和m≤10^18，这个亚子，开双重循环怎么做得下去？？？而且我突然发现，序列不一定都是不一样的数（你觉得
普及/提高-的题给你出的那么简单？）

显然双重循环=TLE。

那怎么办呢？

听一些dalao说找规律什么东西的，本人试了一下，几秒钟发现规律

设n=2,m=4（样例）

n的序列：

| 1 2|
------
或

|1 1| 
-----
等等等等

很显然，无论怎么凑，都无法到m，更别说m的倍数了

设n=4,m=4

n的序列
|1 2 3 4|
--
最后一个4满足要求。

这些例子都有点麻烦，我们再举个：
n=4,m=4
|1 1 1 1|
---
可以
n=3,m=4
|1 1 1|
---
不可以

所以说，如果数列全是1的情况，n必须要≥m

那这道题就变成了if题了

代码：
```
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long x=0,w=1;
	char c;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*w;
}
int main(){
	long long n,m;
	n=read();
	m=read();
	if(n>=m){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}	
	return 0;
}
```


---

## 作者：Fire_Raku (赞：1)

~~蒟蒻的第一篇题解qwq~~    
**分析题目：**

简要的题目意思就是：判断一个任意的长度为 $n$ 的连续正整数序列，里面是否有连续若干个数，是 $m$ 的倍数

首先，题目数据太大，循环什么的几乎不能用，是一道规律题      
然后，我们就猜猜看，因为 $n$ 和 $m$ 两个数之间肯定是有关系的

$m$ 的倍数是有周期的，从 $m$ 开始，每过 $m$ 个数，就有 $m$ 的倍数，所以，如果长度大于 $m$ 的周期，就说明，$n$ 序列中一定有一个数是 $m$ 的倍数,也就满足若干个数且是 $m$ 的倍数的要求了

贴上蒟蒻的代码：

```cpp
#include<bits/stdc++.h>
using namespace std ;
long long n , m ; 
int main(){
	cin >> n >> m ; 
	if(n >= m) cout << "YES" ; 
	else cout << "NO" ; 
	return 0 ; 
}
```
~~求赞~~

---

## 作者：Amor_Hucsy (赞：1)

楼上的几位巨佬的核心代码基本都是这样的：
```c

    if (n >= m)
    {
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
```
可是是我却想出了另一种方法：

条件： 
1：n>m

2：n%n==0

1：首先判断n是否大于m，如果大于，就继续看第二步，如果小于m就直接输出：“NO”,我们可以用一篇代码来解释：
```c
#include<bits/stdc++.h>
  using namespace std;
  long long n,m;
  int mian()
  {
  if(n>m)
  cout<<"看下一步"；
  else
  {
       cout<<NO;
  }
  return 0;
  }
  ```
2:接着判断n取膜n余数是否等于0，如果等于，就输出：“Yes”，如果不等于0‘就直接输出：“NO”,我们也可以用一篇代码来解释：
```c
#include<bits/stdc++.h>
  using namespace std;
  long long n,m;
  int mian()
  {
  if(n%n==0)
  cout<<"Yes"；
  else
  {
       cout<<NO;
  }
  return 0;
  }
  ```
现在是不是都理解了？

接着直接上代码：
```c
#include<bits/stdc++.h>
using namespace std;
long long n,m;//不开long long只有80分，害的我被坑了2次！
int main(){

    cin>>n>>m;//输入
    if(n>m  &&  n%n==0) //把两个条件一合并，就是这段话，记住必须是n%n，而不是m%n，不然就30分，这是一个大坑点！我就被坑了，呜呜呜
    cout<<"YES";//输出
    else 
     {
           cout<<"NO";//输出
     }

    return 0;//好习惯
}
```

---

## 作者：无限WA循环 (赞：1)

这道题根本不算黄题

~~我想了一分钟~~

先枚举试试

nm 1 2 3 4 5   

1  Y N N N N

2  Y Y N N N

3  Y Y Y N N

4  Y Y Y Y N

5  Y Y Y Y Y

看出来规律了吗
n<m时不行
代码：
```
#include<iostream>
using namespace std;
int main(){
    long long n,m;
    if(n<m)cout<<"NO";
    else cout<<"YES";
    return 0;
}

---

## 作者：Vidoliga (赞：0)

# $\text{题解}$

$\text{仔细观察不难发现,如果n>=m,那必定其中有一个数是m的倍数(这不是小学2年级学的抽屉原理吗)}$

$\text{再观察,如果n<m,那么m一定不等于1(由题),那我便取} \begin{matrix}\underbrace{1,1,1\cdots1}\\\text{n个1}\end{matrix},\text{这样便没有m的倍数了}$

$\text{代码辣:}$

```cpp
#include<cstdio>
#define ll long long
using namespace std;
inline ll read(){
	register ll d=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		d = (d<<1)+(d<<3)+(ch^48);
		ch = getchar();
	}
	return d*f;
}
int main(){
	ll n=read(),m=read();
	printf(n>=m?"YES":"NO");
	return 0;
}
```

$\text{完结撒花}QwQ$

---

## 作者：_Imaginary_ (赞：0)

首先，假设这个数列为 $\{a_n\}$ ，我们令 $S_n=\sum\limits_{i=1}^{n}a_i$。

如果存在一个 $S_n$ 使得 $m|S_n$，那么肯定可以。

否则，我们先考虑输出 `NO` 的情况。

如果存在两个 $S_n$ 使得 $m|(S_i-S_j)$，那么依旧可以。

所以，不存在两个 $S_n$ 关于m同余。

而模m的余数只可能有 $1,...,m-1$ 这 $m-1$ 种，其中排除了0. 所以，由抽屉原理，当 $n\ge m$ 时，必然存在两个数同余，与前面假设矛盾。

综上，当 $n\ge m$ 时，输出`NO`，否则输出`YES`。

最后，注意要开`long long`。

~~20分~~代码：(真的很短)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long long n,m;
	cin>>n>>m;
	if(n>=m) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：moongazer (赞：0)

# 题解 P5497 【[LnOI2019SP]龟速单项式变换(SMT)】
[$\mathfrak{View\space it\space on\space my\space Blog}$](https://blog.seniorious.cc/2019/luogu-5497/)
## 思路
- 令$s_i=a_1+a_2+\dots+a_i$
- $m|(a_l+\dots+a_r)\iff s_r\equiv s_{l-1}\pmod{m}$
- 根据鸽巢原理 $\exists x,y\in[0,n]\cap Z:s_x\equiv s_y\pmod{m}$
$\iff n+1$ 个数分成 $m$ 类,至少有一类至少有两个 $\iff n+1>m\iff n\ge m$

## 代码
这么简单的代码有看的必要吗
```cpp
int main () {
  ll n, m;
  read(n), read(m);
  puts(n >= m ? "YES" : "NO");
  return 0;
}
```

---

## 作者：bym666 (赞：0)

# P5497 龟速单项式变换
我一开始看到这道题的时候想到的思路是分类找规律。我把它分为了三类：n<m,n=m,n>m。
## n<m
很显然，这种情况很容易举反例。比如在这个数列a[1]~a[n]是1~n它的和就肯定不是m的倍数。
## n=m
根据等差数列求和公式，（首项+末项）×项数÷2。可以写出这个数列的和是：（a[1]+a[n]）×m÷2，这个式子可以转化为（a[1]+a[n]）÷2×m，这个式子说明在n=m的情况下任意一个数列的和一定是m的倍数。
## n>m
从a[m+1]~a[n]的和一定是m的倍数，从a[1]~a[m]也一定是m的倍数，所以在这种情况下任意一个数列的和一定是m的倍数。
             
综上所述，我们得出结论：在n<m的情况下输出"NO",其他情况输出"YES".
                       
代码如下：
```
#include <bits/stdc++.h>
using namespace std;
long long n,m;
int main()
{
	cin>>n>>m;
	if(n>=m) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```
                      

---

## 作者：REAL_曼巴 (赞：0)

看到大佬们的证明过程，吾甘拜下风。小六蒟蒻只想到了找规律的方法，只需要多枚举几个，自研究发现规律了。（表我就图片了）

![](https://cdn.luogu.com.cn/upload/image_hosting/5s9dcewk.png)

再换换看看：

![](https://cdn.luogu.com.cn/upload/image_hosting/lwu3q9q9.png)

两组了，差不多了，大家应该知道结论了，这，就是比大小的题！

```cpp

#include<iostream>
using namespace std;
int main(){
	long long n,m;//别int 会炸
	scanf("%lld%lld",&n,&m);
	if(n>=m)cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}
```


---

