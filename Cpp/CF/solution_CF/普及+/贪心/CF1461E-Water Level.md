# Water Level

## 题目描述

In recent years John has very successfully settled at his new job at the office. But John doesn't like to idly sit around while his code is compiling, so he immediately found himself an interesting distraction. The point of his distraction was to maintain a water level in the water cooler used by other zebras.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461E/7f311014452a10e23ecd60bd4752a8b017b50a00.png)Originally the cooler contained exactly $ k $ liters of water. John decided that the amount of water must always be at least $ l $ liters of water but no more than $ r $ liters. John will stay at the office for exactly $ t $ days. He knows that each day exactly $ x $ liters of water will be used by his colleagues. At the beginning of each day he can add exactly $ y $ liters of water to the cooler, but at any point in time the amount of water in the cooler must be in the range $ [l, r] $ .

Now John wants to find out whether he will be able to maintain the water level at the necessary level for $ t $ days. Help him answer this question!

## 说明/提示

In the first example, John can't increase the amount of water at the beginning of the first day, since it would exceed the limit $ r $ . That is why after the first day the cooler will contain $ 2 $ liters of water. The next day John adds $ 4 $ liters to the cooler but loses $ 6 $ liters, leaving John with $ 0 $ liters, which is outside the range $ [1, 10] $ .

In the second example, after the first day John is left with $ 2 $ liters of water. At the beginning of the next day he adds $ 5 $ liters, then $ 6 $ liters get used, leaving John with $ 1 $ liter of water which is in range $ [1, 10] $ .

In the third example, after the first day John is left with $ 7 $ liters, after the second day — $ 5 $ liters, after the fourth — $ 1 $ liter. At the beginning of the fifth day John will add $ 9 $ liters and lose $ 2 $ liters. Meaning, after the fifth day he will have $ 8 $ liters left. Then each day the water level will decrease by $ 2 $ liters and after the eighth day John will have $ 2 $ liters and after the ninth day — $ 0 $ liters. $ 0 $ is outside range $ [1, 10] $ , so the answer is "No".

In the fourth example, after the first day John is left with $ 15 $ liters of water. At the beginning of the second day he adds $ 7 $ liters and loses $ 5 $ , so after the second day he is left with $ 17 $ liters. At the beginning of the third day he adds $ 7 $ more liters of water and loses $ 5 $ , so after the third day he is left with $ 19 $ liters. $ 19 $ is in range $ [15, 25] $ so the answer is "Yes".

## 样例 #1

### 输入

```
8 1 10 2 6 4```

### 输出

```
No```

## 样例 #2

### 输入

```
8 1 10 2 6 5```

### 输出

```
Yes```

## 样例 #3

### 输入

```
9 1 10 9 2 9```

### 输出

```
No```

## 样例 #4

### 输入

```
20 15 25 3 5 7```

### 输出

```
Yes```

# 题解

## 作者：IIIIndex (赞：7)

### 题意：

​	有一个水桶，水桶里面有$k$升水，我们每天**开始**的时候可以往里面注入$y$升水，每天的消耗量是$x$升，问我们能否使水量在$[l,r]$范围内保持$t$天

### 思路：

​	本体数据范围比较特殊，容易爆long long，这是比较重要的一个点，但我们看到$1≤x≤10^6$，考虑从$x$入手进行分类讨论。

​	首先就是最容易想到的情况：$y<x$，这种情况下，我们水桶内的水是**单调递减**的，但由于我们水量最低为$l$，所以说我们能撑的最大天数$T$是$\lfloor \frac{k-l}{x-y} \rfloor$，如果$T≥t$，我们就输出Yes。当然，我们需要特判一下**第一天**早上加水时是否会超过$r$，如果会超过的话我们需要让水**先被消耗一天**（这样就保证了加水后水不会超过$r$），再进行判断。

​	接下来就是$y≥x$的情况，在这种情况下，容易得出，我们不让水**溢出**的最优策略就是等水**无法承受下一次使用**的时候再加水。因为我们不必担心水不够用（因为$y≥x$），只需担心加水后水是否会溢出，所以说我们的策略能够尽可能避免**水溢出**（如果我们某一次加水使得水溢出了，说明我们无法保持水位了，此时就该输出No）。只要在加水前对我们的$t$进行检验，如果$t≤T$了，就可以直接输出Yes了。同时，我们还应该记录$k\%x$，不难想到，如果存在某**两次**取水后，$k_1\%x \equiv k_2 \%x$，这样我们两次的状态就**相同**了，说明我们可以**永远**使水保持在$[l,r]$的范围之内，此时就可以直接输出Yes。

### 代码：

​	~~根据cf的题解，学到了新的return技巧~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    long long k,l,r,t,x,y;
    cin>>k>>l>>r>>t>>x>>y;
    if(y<x){
        if(k+y>r)t--,k-=x;
        if(k<l) return cout<<"No", 0;
        long long rst=(k-l)/(x-y);
        if(rst>=t)return cout<<"Yes", 0;
        else return cout<<"No", 0;
    }
    else{
        vector<bool>was(x,false);
        while(t>0){
            if(was[k%x])return cout<<"Yes", 0;
            ll rst=min(t,(k-l)/x);
            t-=rst;
            if(t<=0)break;
            k-=rst*x;
            was[k%x]=true;
            k+=y;
            if(k<l||k>r)return cout<<"No", 0;
        }
    }
    return cout<<"Yes", 0;
}
```



---

## 作者：Leap_Frog (赞：5)

### P.S.
贡献了 5发 CE 后终于双倍经验了过去。。。  
不开 \_\_int128 见祖宗，不过更加离谱的是洛谷上没有 CF 64位机子的接口。。。  

### Description.
略

### Solution.
分类讨论。  
首先如果 $x>y$，那么除了第一天倒水者肯定持续倒水。  
直接讨论一下就好了。。。  
这里会用到 $\times$ 会炸 long long，不过笔者 VP 时用的 \_\_int128。  
然后赛后因为 `P.S.` 中的原因只能先特判乘积是否大于 $2\times 10^{18}$。  
如果 $x<y$，那么最终结果肯定是类似于先让另一个人倒到不能到，然后直接倒一大碗水。  
然后一直循环。。。由于 $x\le 10^6$ 所以我们可以暴力，这样复杂度是 $O(x)$ 的。  
然后就好了。  
具体看代码。。。

### Coding.
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
long long l,r,st,t,x,y;set<long long>s;
int main()
{
	read(st),read(l),read(r),read(t),read(x),read(y);
	if(x>y)
	{
		if((x-y<2e18/t&&st-l>=t*(x-y))&&st+y<=r) puts("Yes");
		else if(x-y<2e18/t&&st-l>=t*x-(t-1)*y) puts("Yes");
		else puts("No");
		return 0;
	}
	long long qwq=st,tp;qwq=l+(qwq-l)%x,t-=(st-qwq)/x;
	if(t<=0) return puts("Yes"),0;else if(qwq+y>r) return puts("No"),0;
	while(t>0)
	{
		qwq+=y;if(qwq>r) return puts("No"),0;else tp=qwq,qwq=l+(qwq-l)%x,t-=(tp-qwq)/x;
		if(t<=0) return puts("Yes"),0;else if(s.count(qwq)) return puts("Yes"),0;else s.insert(qwq);
	}
	return puts("Yes"),0;
}
```

---

## 作者：紊莫 (赞：1)

**数据点**分讨题。

首先，对于 $x>y$ 的情况，每天的水一定是在减少的，那么最多能撑 $\left \lfloor \dfrac{k-l}{x-y} \right \rfloor$ 天，当然，特判一下第一天不能加水的情况，下文的 ``ck`` 函数判断合法情况。

```cpp
if (!ck(k + y)) t--, k -= x;
if (!ck(k)) return (void)puts("No");
if ((k - l) / (x - y) >= t)
  return (void)puts("Yes");
else
  return (void)puts("No");
```

然后，对于 $x\le y$ 的情况，显然我们只要每天加，水一定是够的，但是要考虑水满出去的问题，所以策略变成能不加就不加，否则加水。

那么我们最多能不加 $\left \lfloor \dfrac{k-l}{x} \right \rfloor$ 天，后加一次水，假如你直接这样做会 TLE on #88。所以考虑优化，你发现当前水位相同时，后面的情况一定是相同的，那么出现循环就一定有解，额外开一个数组记录出现情况即可。

但是 $k$ 可能很大，怎么记录呢？注意到我每次操作都是减掉若干个 $x$，那么我们将 $k \bmod{x}$ 记录一下。显然模意义下相等就可以看做方案一样，因为减去若干个 $x$ 后他们都能到达某个值。



---

## 作者：Xiphi (赞：0)

## CF1461E

对 $x$ 数据点分治。若 $x \le y$，则贪心策略为：一直倒到溢出为止，然后看已有的操作个数能不能使其小于等于 $r$，复杂度 $O(x)$。若 $x>y$，则贪心策略为每次都减少 $y$，这样肯定是不劣的，简单计算即可。最后记得开 int128。 

---

## 作者：zimujun (赞：0)

考虑分三种情况讨论。

- 最简单的，$x = y$：显然只要 $k - x$ 或 $k + y$ 有一个在范围内就有解；
- 其次，考虑 $x > y$：因为无论如何用掉的总比添加的多，所以“能加水就加水”维持的时间才是最长的。因为 $x > y$，所以最多只有第一天不能加水，判断一下，做个除法就能得到最大天数；
- 最后是 $x < y$：这种情况下，你更需要注意往饮水机里倒水的时候尽量不超出上限，因此每次先尽可能让饮水机用光，再向桶内加水是个最优的方案。考虑首先让水消耗到不得不加，接下来定义一步操作为：向饮水机内加一次水，并让饮水机消耗到极限。判断是否能加水，计算一步操作后饮水机接下来的水位和一步操作持续的天数都是容易 $O(1)$ 完成的，要是一直没能走到不能加水的位置，至多 $x$ 步操作之后就会回到起点，这样的话就说明这个过程是可以循环的，可以无限进行下去。

[代码链接，感觉没有 *2200。](https://codeforces.com/contest/1461/submission/155011653)

---

