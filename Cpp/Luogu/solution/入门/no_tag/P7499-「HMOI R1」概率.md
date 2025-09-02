# 「HMOI R1」概率

## 题目背景

“傻子才相信概率。”

## 题目描述

fz 退役之后正在学文化课。

fz 见到一个题，这个题是这样的：

给定区间 $[a, b]$ 和 $[c, d]$，求从其中各等概率选择一个整数，和等于 $e$ 的概率。

fz 本来想把 “等于 $e$” 改成 “$\in [e,f]$”，但是这样他就会变成辣鸡分类讨论出题人，所以他决定不改。

为了方便，你只需输出答案乘 $(b-a+1)(d-c+1)$ 的结果。可以证明这个数是一个整数。

## 说明/提示

样例解释：

对于样例的第一组数据，从 $[1,2]$ 和 $[3,4]$ 中各随机选出一个整数的方案共有 $4$ 种，其中只有 $\{1,4\}$ 和 $\{2,3\}$ 两种方案和为 $5$，故概率为 $\dfrac12$。

---------

令 $N=\max\{|a|,|b|,|c|,|d|,|e|\}$。

对于所有数据：

- $1 \le T \le 1000$；

- $0 \le N \le 10^{18}$。

-----------------

**本题不采用捆绑测试。**

| No.  | Constraints            | Score |
| ---- | ---------------------- | ----- |
| $1$  | 与样例相同             | $10$  |
| $2$  | $N \le 300$            | $10$  |
| $3$  | $N \le 5000$           | $30$  |
| $4$  | $N \le 10^9$           | $20$  |
| $5$  | No further constraints | $30$  |

---------

- Idea: FZzzz  
- Solution: FZzzz  
- Code: FZzzz  
- Data: FZzzz

## 样例 #1

### 输入

```
1
1 2 3 4 5
```

### 输出

```
2```

# 题解

## 作者：phigy (赞：14)


给定区间 $[a,b]$ 和 $[c,d]$ ，求从其中各等概率选择一个整数，和等于 $e$ 的概率。

输出答案乘 $(b-a+1)(d-c+1)$ 的结果 。

$(b-a+1)(d-c+1)$ 就是从 $[a,b]$ 和 $[c,d]$ 各取一个整数的方案数 。

所以就是求 $[a,b]$ 和 $[c,d]$ 从中各取一个整数，和等于 $e$ 的方案数 。

就是求 $[a,b]$ 中有几个整数 $x$ 满足 $c\leq e-x\leq d$ 。

$e-x$ 也是整数，而其范围为 $[e-b,e-a]$ 。

只需要求出 $[e-b,e-a]$ 和 $[c,d]$ 交集中整数个数 。

其交集就是 $[max(e-b,c),min(e-a,c)]$ 。

那么答案就是 $min(e-a,c)-max(e-b,c)+1$ 。

但是答案不可能小于 $0$ ，需要特判 。

```cpp
#include <iostream>

using namespace std;

int t;
long long a,b,c,d,e;

int main()
{
    int i,j,k;
    cin>>t;
    while(t--)
    {
        cin>>a>>b>>c>>d>>e;
        cout<<max(min(e-a,d)-max(e-b,c)+1,(long long)0)<<endl;
    }
    return 0;
}
```


---

## 作者：fls233666 (赞：7)

首先我们发现题目给出的数字都很大 $(0 \le N \le 10^{18})$，一个一个去统计显然是不合理的，我们考虑对于每组数据如何 $O(1)$ 出解。

首先先判断无解的情况。我们知道题目给出的两个区间分别为 $[a,b]$ 与 $[c,d]$，那么当我们**能取到的最大值比 $e$ 小**或者**能取到的最小值比 $e$ 大**时，显然无解。能取到的最大值即为 $b+d$，能取到的最小值即为 $a+c$，判断一下他们与 $e$ 的大小关系即可。

解决了无解的情况，我们来考虑有解时如何快速统计出有几种选择方案。我们发现，**对于一个区间 $[a,b]$ ，如果区间内每个整数都能有对应的一个匹配方案，那么这些方案对应的区间就是 $[e-b,e-a]$。** 因此，我们可以判断一下区间 $[e-b,e-a]$ 与区间 $[c,d]$ 的关系。进一步讨论，可以发现存在以下四种关系：

- $e-b \le c,d \le e-a$ 则匹配方案对应区间为 $[c,d]$，方案数为 $d-c+1$；
- $e-b > c, d\le e-a$ 则匹配方案对应区间为 $[e-b,d]$，方案数为 $d-(e-b)+1$;
- $e-b \le c, d > e-a$ 则匹配方案对应区间为 $[c,e-a]$，方案数为 $(e-a)-c+1$;
- $e-b > c, d > e-a$ 则匹配方案对应区间为 $[e-b,e-a]$，方案数为 $(e-a)-(e-b)+1$。

将以上分类讨论放到代码中实现即可。

下面放上完整代码：

```cpp
#include<iostream>
#include<cstdio> 
#define ll long long
#define rgt register int
using namespace std;

ll a,b,c,d,e,ans;

int main(){
	int test;
	scanf("%d",&test);
	while(test--){
    
		scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e);
        
		if(d+b<e||a+c>e){
			printf("0\n");
			continue;
		}  //判断无解
        
		if(c<=e-a&&e-a<=d)
			d=e-a;  
		if(c<=e-b&&e-b<=d)
			c=e-b;
      //根据分类讨论更改答案区间边界
            
		ans=d-c+1;  //统计方案数
        
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：Fire_Raku (赞：2)

### 题目分析：

要求两个集合里的其中两个数是 $e$ 的概率，因为是概率，所以要除以总方案数，但是题目说了，最后要乘 $(b-a+1)(d-c+1)$，其实就是在乘了一遍方案数，所以题目就变成了：求两个集合里的其中两个数是 $e$ 的方案数。

题目思路：暴力？不行，数据太大了，所以我们得另寻他路。   

我们不妨设 $x_1 = e - d$，$x_2= e - c$，它们分别代表着能组成 $e$ 的数的最小值和最大值，也就是说在最大值和最小值之间，都是有数与 $[c,d]$ 其中的数组成 $e$ 的，但最大值和最小值会受到 $[a,b]$ 的影响，所以还需要判断是否越界。

于是我们就得到了式子：$min(x_2,b) - max(x_1,a)+1$，因为方案数不可能是负数，所以就得 $max(min(x_2,b) - max(x_1,a)+1,0)$。

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std ;

int main(){
	int t ; 
	cin >> t ;
	for(int k = 1 ; k <= t ; k++){
		long long a , b , c , d , e ; //不开long long见祖宗
		cin >> a >> b >> c >> d >> e ;
		cout << max(min(e - c , b) - max(e - d , a) + 1 , (long long)0) << endl ; //记得0也得开long long
	}
	return 0 ;
} 
```

---

## 作者：WinterRain208 (赞：1)

题解 P7499 「HMOI R1」概率

首先题意不再赘述了，请自行查看 [原题](https://www.luogu.com.cn/problem/P7499)。

### 做法

首先我们知道概率是一个复杂凡人 而且带分数的东西，但题目中要求我们乘上一个数字 $(b-a+1)(d-c+1)$。

经过简单的分析我们可以发现区间$[a,b]$和区间$[c,d]$的数字数量分别是上面式子的左右两个因式。

通过乘法原理我们知道这两个因式之积，也就是原式，等价于：从两个区间各选一个数，有多少种不同方法。

题目要求我们求和为$e$的从两个区间里选择的数字，易知这个概率乘上 $(b-a+1)(d-c+1)$ 就是满足条件的方法数。

进一步思考，题目让我们枚举满足条件的数量，我们也可以反其道而行之，排除不可能的答案，从而求出正确答案。

易知一个处于区间$[a,b]$的数字$x$如果满足 $x+d<e$ 那么这个数一定不算在 答案里，同理可得如果 $x+c>e$ 同样不可能。

把$[a,b]$区间所有不满足题意的数字 去掉，剩下的一定可以在另一个区间里对应一个数字，这时候$[a,b]$区间没有被排除掉的数字 个数 就是答案。

其他注意事项请参考代码。

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
long long read(){
	long long f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	return x*f;
}

inline void write(long long x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}

int main(){
	long long t,a,b,c,d,e;
	t=read();
	F(i,1,t){
		a=read(),b=read(),c=read(),d=read(),e=read();
		if(a+c>e||b+d<e)puts("0");
		else {
			long long r=e-a,l=e-b;
			if(r>d)r=d;
			if(l<c)l=c;
			write(r-l+1);putchar('\n');
		}
	}
	return 0;
}  
```

完结撒花，点个赞再走呗



---

## 作者：Mysterious_Mini (赞：1)

这是本蒟蒻的第 $6$ 篇题解。
### 思路：
这是一道概率题。我们设总方法数为 $n$，可行方法数为 $m$，所求的答案就是 $\frac{m}{n}$。

而在本题中，$n$ 很好算，是 $(b-a+1)(d-c+1)$。

此时我们定睛一看：题目要求输出答案数 $\times\,n$ ，不就是 $m$ 吗！

于是咱们可以开心的求 $m$ 去了。

当最大值小于 $e$ 或最小值大于 $e$ 时，无解（概率为 $0$）。剩下的情况概率一定不为 $0$。

------------
#### 其他情况（重点）：

我们设 $[c,d]$ 区间内有数 $x$，若成立，则 $[a,b]$ 区间内必有数 $e-x$。最后输出 $x$ 的个数即可。

$\because c\le x \le d,a \le e-x \le b$

$\therefore \begin{cases}c\le x \le d\ \\e-b \le x \le e-a\end{cases}$

$\therefore \max(c,e-b) \le x \le \min(d,e-a)$
### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long a, b, c, d, e, t, minn, maxn; //注意 1e18 的数据量
int main()
{
    cin >> t;
    for(int i = 1; i <= t; i++)
    {
        cin >> a >> b >> c >> d >> e;
        if(a + c > e || b + d < e) cout << '0' << endl;
        else
        {
            maxn = min(e - a, d);
            minn = max(e - b, c);
            cout << maxn - minn + 1 << endl;
        }
    }
    
    return 0;
}
```
[AC](https://www.luogu.com.cn/record/49961754)！


---

## 作者：Citnaris (赞：1)

# P7499 概率

**分析**

在区间 $[a,b],[c,d]$ 中各取一个数：

① 总情况数： $(b-a+1)\times (d-c+1)$ ；

② 和为 $e$ 的情况数：答案在区间 $[x,y]$ 中，其中满足

$$\left\{\begin{matrix} 
  x \ge e-d\\  
  x \ge a
\end{matrix}\right. 
\left\{\begin{matrix} 
  y\le e-b\\  
  y\le c 
\end{matrix}\right. $$

解得

$$\left\{\begin{matrix} 
  x\ge max(e-d,a) \\  
  y\le min(e-b,c) 
\end{matrix}\right. $$

所以

$$\left\{\begin{matrix} 
  x{\tiny min}= max(e-d,a) \\  
  y{\tiny max}= min(e-b,c)
\end{matrix}\right. $$

所以总个数为 $min(e-b,c)-max(e-d,a)+1$ 。

----

综上，我们发现概率为 $\frac{min(e-b,c)-max(e-d,a)+1}{(b-a+1)\times (d-c+1)}$ ，因为题目要求乘 $(b-a+1)\times (d-c+1)$ 再输出，所以真正的答案就是 $min(e-b,c)-max(e-d,a)+1$ 。但因为这个值可能是负的，即不存在和为 $e$ 的选法，所以要将其与 $0$ 取 $max$ 。

**Code**
```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

long long x[10];

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld%lld%lld%lld",&x[0],&x[1],&x[2],&x[3],&x[4]);
        printf("%lld\n",max(min(x[1],x[4]-x[2])-max(x[0],x[4]-x[3])+1,(long long)0));//注意0
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意
给定区间 $[a,b]$ 和 $[c,d]$，求从其中各等概率选择一个整数，和等于 $e$ 的概率。

观察题目，

发现 $(b-a+1)(d-c+1)$ 就是从区间 $[a,b]$ 和 $[c,d]$ 中找两个数的方案数。

在计算概率的时候要除掉，最后还要乘上去。

那么要输出的就是从 $[a,b]$ 和 $[c,d]$，各选一个数字和等于 $e$ 方案数。

就是求 $[a,b]$ 中有几个整数 $x$ 满足 $c \le e-x \le d$ 。
 
设 $e-c=x_1,e-d=x_2$ ,答案即为 $min(b,x1)-max(a,x2)+1$。

这个数可能小于 $0$，那么就输出 $0$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,c,d,e,n;
int main()
{
    cin>>n;
    while(n--){
        cin>>a>>b>>c>>d>>e;
        ll x1=e-c;
        ll x2=e-d;
        ll ans=min(b,x1)-max(a,x2)+1;
        cout<<max(ans,(ll)0)<<endl;
        //记得是（long long)(0),因为ans是long long
    }
    return 0;
}
```


---

## 作者：SoyTony (赞：0)

# 1.分析
题目要求输出答案与 $(b-a+1)(d-c+1)$ 的乘积，因为概率的实质是符合条件的情况数与总情况数之比，发现这个 $(b-a+1)(d-c+1)$ 就是总情况数，因此实际要求的是符合条件的情况数。

# 2.进一步分析
发现 $[a,b]$ 以及 $[c,d]$ 很大，暴力显然是不行的，发现如果一个元素 $x\ (x\in [a,b])$ 能对应找到一个 $y\ (y\in [c,d])$ 使得，$x+y=e$ 的话，显然 $y=e-x$ 是在 $[c,d]$ 中的。

于是把左右边界分别用 $e$ 减去，得到区间 $[e-b,e-a]$，显然答案要求的是 $\operatorname{Card}([e-b,e-a]\cap[c,d])$，也就是 $\min(e-a,d)-\max(e-b,c)+1$，当然这个值可能为负，要特判。
# 3.实现
```cpp
int t;
ll a,b,c,d,e;
int main(){
    t=read();
    while(t--){
        a=read(),b=read(),c=read(),d=read(),e=read();
        printf("%lld\n",max(0ll,min(e-a,d)-max(e-b,c)+1));
    }
    return 0;
}
```

---

