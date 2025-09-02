# National Project

## 题目描述

Your company was appointed to lay new asphalt on the highway of length $ n $ . You know that every day you can either repair one unit of the highway (lay new asphalt over one unit of the highway) or skip repairing.

Skipping the repair is necessary because of the climate. The climate in your region is periodical: there are $ g $ days when the weather is good and if you lay new asphalt these days it becomes high-quality pavement; after that, the weather during the next $ b $ days is bad, and if you lay new asphalt these days it becomes low-quality pavement; again $ g $ good days, $ b $ bad days and so on.

You can be sure that you start repairing at the start of a good season, in other words, days $ 1, 2, \dots, g $ are good.

You don't really care about the quality of the highway, you just want to make sure that at least half of the highway will have high-quality pavement. For example, if the $ n = 5 $ then at least $ 3 $ units of the highway should have high quality; if $ n = 4 $ then at least $ 2 $ units should have high quality.

What is the minimum number of days is needed to finish the repair of the whole highway?

## 说明/提示

In the first test case, you can just lay new asphalt each day, since days $ 1, 3, 5 $ are good.

In the second test case, you can also lay new asphalt each day, since days $ 1 $ - $ 8 $ are good.

## 样例 #1

### 输入

```
3
5 1 1
8 10 10
1000000 1 1000000```

### 输出

```
5
8
499999500000```

# 题解

## 作者：xiaomuyun (赞：4)

# CF1303B National Project 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1303B)
## 题目分析
### 一、计算答案
首先，大家一定要注意这句话：

> You don't really care about the quality of the highway, you just want to make sure that at least half of the highway will have high-quality pavement.（你并不真正关心高速公路的质量，你只想确保至少有一半的高速公路有高质量的路面。）

也就是说，在这 $n$ 天里，需要至少 $\left\lceil\ \dfrac{n}{2}\ \right\rceil$ 天是在好天气下施工。

我们将变量 $need$ 设为 $\left\lceil\ \dfrac{n}{2}\ \right\rceil$，并称 $g+b$ 天为一个周期，然后我们就可以知道施工队至少要修 $need÷g$ 个周期，所以这段时间一共花费了 $(need÷g)×(g+b)$ 天。同时他们可能还要修 $need\bmod g$ 天，因为他们不一定是正好修了 $(need÷g)$ 个周期，可能还需要修几天才能使在好天气下施工的日子有 $need$ 天。
### 二、需要注意的几个点
1. 因为一共要修的长度肯定是要 $\ge n$ 的，所以如果求得的 $ans$ 比 $n$ 还小的话，答案肯定不成立，这时应该直接输出 $n$。要在最后求出答案的时候做一个特判。
2. 如果说施工队在修了 $(need÷g)$ 个周期之后，在好天气下施工的日子已经有 $need$ 天的话，就不需要再加 $need\bmod g$ 了，同时还要在上一个周期里减掉 $b$ 天，因为在上个周期的好日子结束之后，在好天气下施工的日子已经有 $need$ 天了，也就不需要再修 $b$ 天。

~~由于本蒟蒻太菜，就不贴奇奇怪怪的代码了~~
## 总结
这道题是一道 ~~较为简单的~~ 思维题，希望大家能够看懂本蒟蒻的解法，也请 大家在最后点个赞，制作不易~

---

## 作者：do_while_true (赞：4)

首先注意两个地方:

1. 样例从未出错
1. 你的路必须全部铺完

上面两点是CF发的提示

首先记录下来ceil(n/2)的值，记为maxx，如果我们想要maxx全铺上好的路，就要在maxx/g 组好天以及maxx%g个不完整的好天，然后每g个好天后面一定跟着b个坏天，所以我们一也有maxx/g组坏天,但如果maxx%g==0，显然我们在最后一组好天就已经把需要的maxx个好路修完了，不需要修坏路了，这个时候最终的答案需要减去一个b

那么如果这个坏天多余n-ceil(n/2)怎么办，显然我们在坏天是可以选择不修路的，所以我们的答案就是完整的好天数加上完整坏天数加上不完整的好天数

也就是

当$maxx\%g!=0$时

$ans=(g+b)*(maxx/g)+maxx\%a$

当$max\%g==0$时

$ans=(g+b)*(maxx/g)-b$

特别注意，因为我们的路必须全部铺完，所以如果最后ans<n的话直接输出n即可

###  _Code:_ 

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll unsigned long long
using namespace std;
ll T,n,a,b,maxx,ans,t;
int main()
{
	scanf("%llu",&T);
	for(int i=1;i<=T;i++)
	{
		ans=0;
		scanf("%llu%llu%llu",&n,&a,&b);
		maxx=(n+1)/2;
		if(a>=maxx){
			printf("%llu\n",n);
			continue;
		}
		t=maxx/a;
		ans+=(a+b)*t;
		ans+=maxx%a;
		if(maxx%a==0) ans-=b;
		if(ans>=n) printf("%llu\n",ans);
		else printf("%llu\n",n);
	}
	return 0；
}
```


---

## 作者：NaOH_Frog (赞：1)

这道题只要用贪心就行了，至少要有$ceil(n$ $/$ $2)$天好天气

因为天气是$(b+g)$天一循环，$g$天好$b$天坏，所以只要计算：

1.好路要修多久

2.好路修完了以后烂路修完了没有，如果没有就把烂路修完

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ceil(int x, int y){
	if(x % y == 0) return x / y;
	else return x / y + 1;
}//不知道我手打ceil干嘛
long long len(long long n, long long g, long long b){
	long long loop = b + g; //天气循环
	long long good_road = ceil(n, 2); //修多少好路 
	long long num_loop = ceil(good_road, g) - 1; //多少个完整循环, 注意最后一个循环可能不完整 
	long long leftover = good_road - num_loop * g + max(0 * 1LL, (n - good_road) - num_loop * b); //还要再修多少天, 记得特判好路修完坏路没修完的情况 
//	cout << loop << " " << good_road << " " << num_loop << " " << leftover << endl;
	return num_loop * loop + leftover; //总共修多少天 
}
int main(){
    int tc;
    cin >> tc;
    for(int i = 0; i < tc; i++){
        long long n, g, b;
    	scanf("%lld %lld %lld", &n, &g, &b);
        cout << len(n, g, b) << endl; 
    }
    return 0;
}
```


---

## 作者：分离性漫游 (赞：0)

这道题是一道~~快乐~~模拟。

首先这道题有**两种特殊情况**是需要特判的。

**1.好天气大于等于坏天气**
   
也就是说 $g\geq b$  。

如果这个情况是成立的。

那么就直接输出 $ n $ 。

**2.两倍的好天气大于总长度**

也就是 $ 2×g>n $ 。

如果这个情况是成立的。

那么就直接输出 $ n $ 。

**3.其他情况（常规情况）**

步骤如下：

- 算出修完一半的次数。

- 算好天气所需要的次数。

- 算坏天气所需要的次数。

- 算出剩余的次数。

- 最后计算修完一半的次数*（好天气天数+坏天气天数）+剩余次数。

接下来附上代码。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{ 
    long long t,n,g,b;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    	cin>>n>>g>>b;
    	if(g>=b||2*g>n)
    	{
    		cout<<n<<endl;
    		continue;
		}
		int tmp=(n-1)/(2*g);//修完一半的次数
		int x1=tmp*g;//好天气所需次数 
		int x2=min(n/2,tmp*b);//坏天气所需次数
		int sy=n-x1-x2;//剩余的次数 
		cout<<tmp*(g+b)+sy<<endl;
	}
	return 0;
}
```



---

## 作者：serverkiller (赞：0)

# 题意
给定三个数$n,g,b$。

$n$表示要求工作的天数,从第一天开始$g$天是$good$,然后$b$天是$bad$.

问最少需要跳过多少天使得工作时的$good$的天数大于$n$的一半

# solution

不难发现 我们如果跳过很多的$b$肯定时正确的 这样显然满足了二分的性质 所以此题可以考虑二分答案

既然要二分 那么出现了2个问题:
```
1.如何判断mid正确
2.上界与下界
```
先解决第一个问题 其实就相当于过了$n+mid$天那么就是$n+mid$天内$good$的天数 当然 不能超过$n$ 也就是一个小学二年级的周期问题qwq 代码大概是这样的:
```cpp
int nn = n + mid;
int tmp = (nn / (g + b)) * g + min(g,nn % (g + b));
```

然后留下的就是上下界问题 下界是$0$ 而上界~~我还考虑错了很多次~~最后某神犇给我举了一个例子:
$$n=10^9,g=1,b=10^9$$

此时我们会发现跳过的日子的上界应该是$\frac{n\times b}{2}$

下面的是我的理解:
>到了$\frac{n\times b}{2}$的日子 就算$g$再小也会有$\frac{n}{2}$次$g$也就是满足条件的最大的情况

那么根据以上讨论的方法进行二分 代码就不挂了

为什么别人的B都是$O(1)$的 我也不知道啊
~~我才不会说我在写题解的时候胡出来了~~

---

