# Sport Mafia

## 题目描述

Each evening after the dinner the SIS's students gather together to play the game of Sport Mafia.

For the tournament, Alya puts candies into the box, which will serve as a prize for a winner. To do that, she performs $ n $ actions. The first action performed is to put a single candy into the box. For each of the remaining moves she can choose from two options:

- the first option, in case the box contains at least one candy, is to take exactly one candy out and eat it. This way the number of candies in the box decreased by $ 1 $ ;
- the second option is to put candies in the box. In this case, Alya will put $ 1 $ more candy, than she put in the previous time.

Thus, if the box is empty, then it can only use the second option.

For example, one possible sequence of Alya's actions look as follows:

- put one candy into the box;
- put two candies into the box;
- eat one candy from the box;
- eat one candy from the box;
- put three candies into the box;
- eat one candy from the box;
- put four candies into the box;
- eat one candy from the box;
- put five candies into the box;

This way she will perform $ 9 $ actions, the number of candies at the end will be $ 11 $ , while Alya will eat $ 4 $ candies in total.

You know the total number of actions $ n $ and the number of candies at the end $ k $ . You need to find the total number of sweets Alya ate. That is the number of moves of the first option. It's guaranteed, that for the given $ n $ and $ k $ the answer always exists.

Please note, that during an action of the first option, Alya takes out and eats exactly one candy.

## 说明/提示

In the first example, Alya has made one move only. According to the statement, the first move is always putting one candy in the box. Hence Alya ate $ 0 $ candies.

In the second example the possible sequence of Alya's actions looks as follows:

- put $ 1 $ candy,
- put $ 2 $ candies,
- eat a candy,
- eat a candy,
- put $ 3 $ candies,
- eat a candy,
- put $ 4 $ candies,
- eat a candy,
- put $ 5 $ candies.

This way, she will make exactly $ n=9 $ actions and in the end the box will contain $ 1+2-1-1+3-1+4-1+5=11 $ candies. The answer is $ 4 $ , since she ate $ 4 $ candies in total.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0```

## 样例 #2

### 输入

```
9 11
```

### 输出

```
4```

## 样例 #3

### 输入

```
5 0
```

### 输出

```
3```

## 样例 #4

### 输入

```
3 2
```

### 输出

```
1```

# 题解

## 作者：Lily_White (赞：9)

解方程，设共执行放入操作$x$次。

$$\frac{x(x+1)}2-(n-x)=k$$

化简并解得（舍去负解）

$$ x = \frac{-3+\sqrt{9+8(n+k)}}2 $$

因为题目保证有解，所以不必考虑`sqrt`的精度问题，但需要注意输出大数时，需要加入
```cpp
cout << fixed << setprecision(0);
```

Code：
```cpp
    #include <bits/stdc++.h>
    using namespace std;
     
    int main()
    {
    	long long n, k;
    	cin >> n >> k;
    	if (n == 1)cout << 0 << endl,exit(0);
    	cout << fixed << setprecision(0);
    	cout << n - (-3 + round(sqrt(4 * (2 * n + 2 * k) + 9))) / 2 << endl;
    	return 0;
    }
```

---

## 作者：Konnyaku_ljc (赞：5)

## （雾
看完所有的题解后，感觉就这么一个字。有开long long的大佬，有二分的……   
这2000ms的限制，int 2*10^9的范围……这不就是个暴力吗？！！！  
```cpp
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int n,k,sum;
//n,k为题意，sum记录拿的糖果总数（包括吃掉的）
int main()
{
    cin>>n>>k;//输入
    for(int i=1;i<=n;i++)
    {
	    sum+=i;//累加总数
	    if(sum==k+n-i)
        //当动作数与剩下的糖果数之和减去吃掉的等于总的时
	    {
	        cout<<n-i<<endl;//输出
	        return 0;//结束代码
	    }
    }
}
```
~~没错，我给评的是入门难度……~~

---

## 作者：GOODwell (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1195B)

### 本题可以利用暴力枚举
这题无论是空间还是时间上都可以利用暴力枚举 A 了。


------------

设 $cnt$ 为蛋糕总数（包括**吃掉的**蛋糕数量），放入盒子的油蛋糕数为 $i$ ，$n$、$k$ 如题，那么
$$ cnt-(k+n-i)==0 $$
这个式子是在刚刚好把每一块蛋糕都处理好的的情况下才能成立的，

所以可以通过枚举 $i$ 来判断这个式子是否成立。

代码里有注释，重点在**第９行**的判断，下面上代码。

```
#include<bits/stdc++.h>
using namespace std;

int main() {
	int n,k,cnt=0; //n,k 如题，cnt 为总数
	cin>>n>>k;
	for(int i=1;i<=n;i++) {
		cnt=cnt+i; //在总数上累加吃掉的蛋糕数量
		if(cnt-(k+n-i)==0) { 
		//总数－（剩下的数量＋操作数－吃掉的油蛋糕数）为刚刚好可以处理完时的情况
			cout<<n-i<<endl;
			break;//也可以直接 return
		}
	}
	return 0;
}
```


如有错误，欢迎指正。

最后感谢您的阅读，感谢管理员辛苦的批题解。

---

## 作者：Meatherm (赞：4)

~~题面翻译浓浓的珂学气息啊。~~

由于$1\leq n\leq 10^9$，于是这道题可以采用$O(\log2 (n))$复杂度的解法来解决。

二分枚举放黄油蛋糕的次数。设当前放黄油蛋糕的次数为$mid$，那么当前放了$\sum_{i=1}^n i$ 块黄油蛋糕，吃了$n-mid$块蛋糕。

- 如果黄油蛋糕的数量$-$吃掉的黄油蛋糕的数量$=k$，那么答案为$mid$。

- 如果黄油蛋糕的数量$-$吃掉的黄油蛋糕的数量$>k$，那么蛋糕放得太多，右端点应往左移。

- 否则左端点应往右移，增加放蛋糕的次数。

```
# include <bits/stdc++.h>
# define rr register
long long n,k;
int main(void){
	scanf("%I64d%I64d",&n,&k);
	if((1+n)*n/2==k){//没啥卵用的特判
		printf("0");
		return 0;
	}
	long long l=1,r=n;
	long long sum=0;
	while(l<=r){//不用担心放0次蛋糕的情况 因为第一个操作永远都是放蛋糕
		long long mid=(l+r)>>1;
		sum=(1+mid)*(mid)/2;
		if(sum-(n-mid)==k){
			printf("%I64d",n-mid);
			return 0;
		}
		if(sum-(n-mid)>k){
			r=mid-1;
		}
		else l=mid+1;
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：2)

## CF1195B Sport Mafia

简单数学题。

列个方程，设操作了 $x$ 次，（如果设吃了多少次好像不太行）

等差数列求和公式： $(1+2+3+...+n)=\frac{1}{2}(n+1)(n)$。

于是乎就有方程： $\frac{1}{2}(x+1)(x)-(n-x)=m$

简单化简一下，     $x+x^2-2n+2x=2m$。

合并同类项，       $x(x+3)=2m+2n$。

所以我们只需要暴力枚举 $x$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	int i=0;
	while(1)
	{
		if((i+3)*i==2*m+2*n)
		{
			cout<<n-i<<endl;
			break;
		}
		i++;
	}
}
```


---

## 作者：L_Y_T (赞：2)

$很容易得出,放入糖果数目依次为1,2,3,4,5,6,....$

$则,盒子中糖果的总数就是1,3,5,9,15,.....$

$那么,对应的可以吃的糖果数就是n-1,n-2,n-3.....$

$思路:在前缀和中,如果放入盒子中的总数-吃的总数==k的话,直接输出$

即:
```cpp
  	if(rest >= k && rest - x == k) {
            cout << x <<endl ;
            return 0 ;
        }
```
## 代码如下
```cpp

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std ;
int n , k ,ans , rest = 0 , ex = 1 ;
int main () {
    cin >> n >> k ;
    n -- ;rest = 0 ;
    if(n == 0) cout << "0" ;
    else 
    for(int i = 1 ; i <= n ; i ++) {
        int x = n - i +1;
        rest += i ;
        if(rest >= k && rest - x == k) {
            cout << x <<endl ;
            return 0 ;
        }
    }
    return 0 ;
}

```

---

## 作者：Zekrom (赞：2)

设添加x次   
则 最终结果为 $\frac{x(x+1)}2-(n-x)=k $    
移项得$x(x+3)=2(n+k)$    
因为$x(x+3)$在正数域上单调，二分即可    

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
ll n,k;
inline ll read(){
	ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{
	n=read();k=read();
	ll l=0,r=n;
	while(l<r){
		ll mid=(l+r)>>1;
		if((ll)((mid*mid+3*mid)/2)<n+k)l=mid+1;else r=mid;
	} 
	printf("%lld\n",n-l);
	return 0;
}
```


---

## 作者：_SkyLine_ (赞：1)

数学题，解一元二次方程即可。
## 思路分析
设操作二的个数为 $q$ 次，则可知操作一的个数为 $(n-q)$ 次。

据上述未知数可列出方程：
$$\large\frac{q(q+1)}{2}-(n-q)=k$$
我们知道操作二放入**比上一次放入的个数多一个的黄油蛋糕**，而第一次操作放入了一个蛋糕，可推知共放入了
$$\large 1+2+ \cdots +q$$
个蛋糕。对于这样的数列，有等价式子 $\frac{q(q+1)}{2}$ 可替换。而剩下的当蛋糕个数应该等于加入的蛋糕个数与吃掉的蛋糕个数之差，所以列出该方程。

解该方程，得
$$\large q= \frac{-3 \pm \sqrt{9+8n+8k}}{2}$$
因为 $-\frac{3}{2} < 0,\sqrt{9+8n+8k} \ge 0$，得 $\frac{-3 - \sqrt{9+8n+8k}}{2} < 0$，不符合题意，舍去。得到最后的 $q= \frac{-3 + \sqrt{9+8n+8k}}{2}$。

不过由于我们求出的是操作二的次数，而题目要求输出操作一的个数，所以最后输出 $(n-q)$ 即可。

记得开 ```long long```。

## $\textrm{Code:}$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,x;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	x=(ll)(-3+(ll)(sqrt(1LL*9-1LL*4*(-2*1LL*n-2*1LL*k))))/(2*1LL);
	cout<<(ll)(n-x);
	return 0; 
}
```
最后的输出忘了化成最简形式了，不过它们是等价的，照上文理解就行。

---

## 作者：sakuya726 (赞：1)

对于每次放糖果的数量是一个等差数列1,2,3,4,5..x(这里的x是我们设的未知数,表示一共放了多少次糖果)

那么放入盒子里面的糖果的总值就是(1+x)*x/2 ~~这个都求不来的话就去找高斯~~

一共有n次操作,我们设一共放入了x次糖果,那么剩下的(n-x)就是吃掉的糖果次数

因为每次吃一个,所以吃掉的糖果总数也是(n-x)

那么我们可以初步得到这样一个式子-> 放进去的-吃掉的=剩下的

转换成字母表达就是-> (1+x)*x/2-(n-x)=k

再去掉分母,移项合并得到关于x的一个式子

x^2+3x=2(n+k)

因为x肯定是正整数.

所以左边部分是单调递增的,右边的两个参数n和k我们又已知

所以,二分的想法便油然而生了.

通过二分来得到x的值,如果左边小了就往大的二分,左边大了便往小的二分,一旦相等就说明当前这个x是我们想要的那个值

输出n-x就行了(别忘了要输出的是吃的糖果数量)

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 50000
#define rg register
inline ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll sum;
ll n,k;
ll ans;
inline ll get_ans(ll x)
{
	return (x*x+3*x);
}
int main()
{
	n=read(),k=read();
	if(n==1) 
	{
		cout<<0;
		return 0;
	}
	sum=2*(n+k);
	ll l=1,r=n;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(get_ans(mid)==sum)
		{
			cout<<n-mid;
			return 0;
		}
		if(get_ans(mid)>sum)
		{
			r=mid-1;
		}
		else if(get_ans(mid)<sum)
		{
			l=mid+1;
		}
	}
}
```


---

## 作者：Llf0703 (赞：1)

~~怎么都这么麻烦啊~~

用 $cur$ 表示盒子里的糖数，如果剩下的操作全部用来吃刚好能吃到 $k$ 就直接输出。

```cpp
#include<bits/stdc++.h>

using namespace std;

signed main()
{
    int n,k; scanf("%d%d",&n,&k);
    for (int i=0,cur=0;i<=n;i++,cur+=i) if (cur-k==n-i) return !printf("%d",n-i);
}
```

---

## 作者：Big_Dinosaur (赞：0)

#### 思路
我们假设 $n$ 次全是放，则盒子里有 $\dfrac{n(n+1)}{2}$ 块蛋糕，而实际上是 $m$ 块，说明有一些被吃掉了，设吃了 $eat$ 块。接下来，我发现了每吃一块，剩下的块数会减少 $n-eat+2$ 块。

那么，设 $t$ 为 $\dfrac{n(n+1)}{2}$，只要 $t>m$，就不断将 $t$ 减去 $n-eat+2$，并将 $eat$ 加 $1$，最后输出 $eat$ 即可；当然，也可以将 $t$ 减去 $n+1$，再把 $n$ 减 $1$，然后将 $eat$ 加 $1$，最后输出 $eat$。两种方法等价。

[AC Code](https://codeforces.com/contest/1195/submission/213457296)

---

## 作者：zgy_123 (赞：0)

一道简单的数学题，解方程即可。

首先假设两种操作的次数分别是 $x$ 和 $y$。

可以列出方程：

$$\left\{\begin{matrix}
 x+y=n\\\frac{y(y+1)}{2}-x=k
\end{matrix}\right.$$

带入得：

$$\frac{y(y+1)}{2}-(n-y)=k$$

$$\frac{1}{2}y^2+\frac{1}{2}y-n-k+y=0$$

$$y^2+3y-2n-2k=0$$

带入一元二次方程求根公式：$x=\frac{-b\pm\sqrt{b^{2}-4ac}}{2a}$，得：

$$y=\frac{-3\pm\sqrt{9+8(n+k)}}{2}$$

由于 $9+8(n+k)\ge9$，所以 $\sqrt{9+8(n+k)}\ge3$，故 $y=\frac{-3-\sqrt{9+8(n+k)}}{2}$ 应当舍去。

最后化简得：

$$y=\frac{-3\pm\sqrt{9+8(n+k)}}{2}$$

因为题目要求的是吃掉的蛋糕的数量，即 $x$，这里要输出的是 $n-\frac{-3+\sqrt{9+8n+8k}}{2}$。

注意要开 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll n,k,x;
	cin>>n>>k;
	x=sqrtl(9+8*n+8*k);
	cout<<n-((ll)-3+x)/2;
	return 0;
}

```

---

## 作者：xiahaob (赞：0)

### 题意简述
各位大佬应该看了题目都应该知道吧。

题目的意思就是：有两种操作，一种操作是吃掉一个蛋糕，另一个操作是放比上一次放的个数多一个的蛋糕。给定操作的总数和还剩下的蛋糕。求吃掉了几个蛋糕。

### 题目分析

题意非常显然，直接从   $0-n$   枚举吃的蛋糕个数，在计算判断即可，时间复杂度为   $O(n)$ ， 但这道题实在~~太水了~~ 所以也能过。但我们细细想。她每次吃的个数是固定的  $1$ 个，放的蛋糕也是依次递增的。很容易表示出来。所以可以只用解个一元二次方程就可以做出来了。时间复杂度为  $O(1)$ ，已经为最优了。接下来就是高光的数学时刻了。

设珂朵莉一共吃了 $x$ 次蛋糕，所以珂朵莉一共放了   $n-x$ 次蛋糕。

因为每次放的蛋糕比上一次放的个数多一个的蛋糕，且第一次放了  $1$  个。

所以珂朵莉最后一次放蛋糕时放了  $n-x$  个。

所以珂朵莉一共放了  $\sum_{i=1}^{n-x}i$  个。

用等差数列求和公式化简得到珂朵莉一共放了 $\dfrac{(1+n-x)(n-x)}{2}$  。

但珂朵莉有吃掉了  $x$  个，所以 $k= \dfrac{(1+n-x)(n-x)}{2}-x$ 。

化简得  $x^2-(2 \times n+3)\times x +n^2+n-2 \times k =0$ 。

所以用一元二次方程求根公式就能把它解出来 。

一元二次方程：

形如 $a \times x^2+b \times x +c=0$ 的方程为一元二次方程 。

它的解为 $x=\dfrac{-b\pm \sqrt{b^2-4 \times a \times c}}{2 \times a}$ 。

二元一次方程一般有两个解，我们肯定只考虑符合实际意义的解。也就是说答案是小于 $n$ 的那个解 。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不然过不了
ll qpow(ll a,ll b){//快速幂模板
	ll ans=1;
	while(b){
		if(b&1) ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}
int main(){
	//方程为x^2-(2*n+3)*x+n^2+n-2*k=0;
	ll n,k;
	scanf("%lld%lld",&n,&k);
	ll a=1,b=-2*n-3,c=qpow(n,2)+n-2*k;//处理参数，不然写起来很晕
	ll x1=(-b+sqrt(qpow(b,2)-4*a*c))/(2*a);
	ll x2=(-b-sqrt(qpow(b,2)-4*a*c))/(2*a);
   //方程的两个根
	if(x1<=n) printf("%lld",x1);
	else printf("%lld",x2);
   //判断是否符合实际意义
}
```

（蒟蒻码风丑，不喜勿喷）

这道题确实很水，方程其实很容易就能想出来，代码实现起来也非常容易。

蒟蒻如有说错的地方，请各位大佬随时私信我 。

感谢观看，**请勿抄袭**。

---

## 作者：ImposterAnYu (赞：0)

# 解析
设我们可爱的珂朵莉（误）进行了 $x$ 次操作二（第 $x$ 操作增加 $x$ 块黄油蛋糕），$n - x$ 次操作一（每次操作减少 $1$ 块黄油蛋糕），则我们可以得到方程：
$$\frac{x(x + 1)}{2} - (n - x) = k$$

（$\sum\limits_{i = 1}^{x}{i}$，也就是 $1+2+3+…+x$，和 $\frac{x(x + 1)}{2}$ 是相等的，这个不用我解释吧![](//图.tk/g)![](//图.tk/6)）

去括号，得
$$\frac{x(x + 1)}{2} - n + x = k$$
移项，得
$$\frac{x(x + 1)}{2} - n + x - k = 0$$
两边同时 $\times 2$，再调一下顺序，得
$$x(x + 1) + 2x - 2n - 2k = 0$$
把左边变一下形，得
$$x(x + 3) - 2(n + k) = 0$$
化简 $x(x + 3)$，得
$$x^{2} + 3x - 2(n + k) = 0$$
这样，我们就得到了一个最基础的一元二次方程。用通用公式解这个方程，可得
$$x = \frac{\pm\sqrt{9 + 8(k + n)}- 3}{2}$$
因为我们只需要它的非负整数解（题目保证有解），所以可得
$$x = \frac{\sqrt{9 + 8(k + n)}- 3}{2}$$
所以，最后的答案就是 $n - \frac{\sqrt{9 + 8(k + n)}- 3}{2}$。

注意：因为 `sqrt`是 `double` 类型的函数，所以算出 $\sqrt{9 + 8(k + n)}$ 后，要将结果强制转换成整型，以免造成精度误差。
# code
~~我认为我的代码不需要加更多注释，再看不懂我也没办法了。~~
```c++
#include<bits/stdc++.h>
#define int1 long long
//#define p 1145141919810114514
using namespace std;
int1 t,n,k;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	n = read(),k = read();
	print(n - (((int1)sqrt(9 + 8 * (k + n)) - 3) >> 1));//sqrt() 为求根函数，为 double 类型，所以要强制转型。
  	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-CF1195B)  
[本题解同步发表于作者的个人博客](https://froldh.github.io/2019/07/22/codeforcesPlan/CF1195/)  
设放入的蛋糕操作数目为t，显然放入t*(t+1)/2个蛋糕。吃掉的蛋糕数目为n-t，两者相减等于k。  
化简方程得t^2 + 3*t - 2*(n + k) = 0,显然我们要求的n-t的t来源于该方程的正数解。结合二次函数知识可得它在[0,+∞] 单调递增且有零点(唯一)，所以可以二分答案求解。  
```cpp
#include <cstdio> 

using namespace std;

int main() {
	int n, k, l = 0, r = 100000;
	scanf("%d %d", &n, &k);
	long long p = - 2 * ((long long)n + k);
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		long long ans = (long long)mid * (mid + 3) + p;
		if(ans <= 0) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", n - l);
	return 0;	
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

## 作者：bits (赞：0)

- 解题所需预备知识（一元二次方程）

1.定义

形如$ax^2+bx+c=0(a,b,c$是常数，且$a\not=0)$的方程称为**一元二次方程**

2.根的判别式

定义：当$a\not=0$时，判别式$\Delta=b^2-4ac$

当$\Delta<0$时，原方程**无实数解**

当$\Delta=0$时，原方程有**两个相等的**实数解（不能说只有一个实数解）

当$\Delta>0$时，原方程有**两个不相等的**实数解

本题中题目保证有解，因此$\Delta\geq0$

3.求根公式

$x_{1,2}$ $=$ $-\frac{b\pm\sqrt{b^2-4ac}}{2a}$
$(a\not=0$ 且 $\Delta\geq0)$

- 题目分析

根据题目，可以发现珂朵莉（或者说是英文题意中的Alya）放入的蛋糕是一个等差数列。

因此我们设放蛋糕$a$次，则她一共吃了$(n-a)$次。

所以放入了$\frac{a^2+a}{2}$块蛋糕。

列出关于$a$的一元二次方程$\frac{a^2+a}{2}-(n-a)=k$

整理得$\frac{a^2+3a}{2}-(n+k)=0$

代入求根公式，并舍去负根，
化简得$x=\frac{-3+\sqrt{9+8n+8k}}{2}$

因而写出代码：

**注意：请到最后输出时再取整**

```cpp
#include <cstdio>
#include <cmath>

int main(){
    double n, k;
    scanf("%lf%lf", &n, &k);
    double delta = 9 + 8 * n + 8 * k;
    double x = (sqrt(delta) - 3) / 2;
    double result = n - x;
    printf("%d\n", (int)result);
    return 0;
}
```

---

## 作者：zylll (赞：0)

设$x$为吃糖果的次数，则可列出方程：$(n-x+1)(n-x)=2(k+x)$。

化简可得：$x^2 -(2n+3)x+n^2+n-2k=0$

这个一元二次方程有可能出现$2$种解的情况，对于比$n$大的舍去即可。

代码：

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n, k, a, b, c, ans, qaq;
int main() {
	cin >> n >> k;
	a = 1;
	b = -((n << 1) + 3);
	c = (ll)n * n + n - (k << 1);
	ans = ((-b + (ll)sqrt((ll)(b * b) - (ll)(4 * a * c))) / (a << 1)) > n ? ((-b - (ll)sqrt((ll)(b * b) - (ll)(4 * a * c))) / (a << 1)) :((-b + (ll)sqrt((ll)(b * b) - (ll)(4 * a * c))) / (a << 1));
	cout << ans << endl;
	return 0;
}
```


---

## 作者：AC_Dolphin (赞：0)

直接推公式好评

设操作1进行了$x$次，操作2进行了$y$次，因为总共进行了$n$次，所以$x+y=n$①，因为进行了$y$次操作2，所以放了$\Sigma_{i=1}^y i$块蛋糕，即$y(y+1)/2$块，又因为拿出了$x$块蛋糕，所以$y(y+1)/2-x=k$②

由①得$x=n-y$，代入②得$y(y+1)=2(n-y+k)$

整理，得$y^2+3y-2(n+k)=0$

由球根公式得$y=(±\sqrt{9+8(n+k)}-3)/2$

若取负，则$-\sqrt{9+8(n+k)}-3$必小于$0$，所以$y<0$，不符合题意，所以必定取正，$y=(\sqrt{9+8(n+k)}-3)/2$

题目要求$x$，所以$x=n-y=n-(\sqrt{9+8(n+k)}-3)/2$

**注意：因为要开long long，所以不能直接用sqrt函数，需要枚举**

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define rep(i,n) for(re int (i)=1;(i)<=(n);++(i))
typedef long long ll;
ll n,m;
il int read(){
	re char ch(getchar());
	re int f(1),x(0);
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int main(){
	n=read(),m=read();
	for(ll register i=1;;i++) if(i*i==9+(n+m)*8) {//枚举
		cout<<n-(i-3)/2;
		return 0;
	}
	
	return 0;
}
```

---

## 作者：Aehnuwx (赞：0)

看了 [Ravenclaw_OIer](https://www.luogu.org/space/show?uid=87696) 这位大佬的题解，愈发感觉我就是个 **.

我同样也是解方程的，通过题目描述，我们可以设 $ x $ 为放的次数，设 $ y $ 为吃的次数，可得方程组:

$$ \begin{cases} x+y=n \\ \dfrac{x(x+1)}{2}-y=k \end{cases} $$

然而！！！

我竟然没有**化简**！！！

我直接 $ \text{O(n)} $ 枚举 $ x,y $ ！

真是。。。

这题明明有 $ \text{O(1)} $ 的直接解方程，和 $ \text{O(log n)} $ 的二分。。。

能过去估计是因为 register?

下面附上比赛代码

$ \rm code $

```cpp
# pragma GCC optimize(2)
# pragma GCC optimize(3)
# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
using namespace std;
# define int long long // 1e9 ^ 2 不开 LL?
int n, k;
signed main() {
	cin >> n >> k;
	if(n == 1) return puts("0"), 0; // 这特判应该可以不要的
	for(register int x = 1; x <= n; ++x) { // register 万岁
		int y = n - x;
//		cout << x << ' ' << y << '\n';
		if(((x * (x + 1)) >> 1) - y == k) cout << y << '\n', exit(0); 
	}
} 
```


---

## 作者：Karry5307 (赞：0)

### 题意

给定常数$n$和$k$，解关于$x$的方程$\frac{(n-x)(n-x+1)}{2}=k+x$。

$\texttt{Data Range:}1\leq n\leq 10^9,0\leq k\leq 10^9$

### 题解

比赛时想的是二分答案。

由于$x\leq n$，所以只需要设右端点为$n$即可。

主要是如何$\texttt{check}$的问题。

设原方程的解为$x_0$，现在二分到的值为$x_1$，如果$x_1>x_0$，那么有

$$n-x_1<n-x_0$$

那么有

$$\frac{(n-x_1)(n-x_1+1)}{2}<\frac{(n-x_0)(n-x_0+1)}{2}$$

但是

$$k+x_1>k+x_0$$

所以联立一下

$$\frac{(n-x_1)(n-x_1+1)}{2}<k+x_1$$

所以，当用$mid$代入原方程两边时，如果左边小于右边，则移动右端点，否则移动左端点。

答案为$0$的情况特判就好了。

时间复杂度$O(\log n)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=1e5+51;
ll cnt,k,l,r,mid,tmp;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline ll calc(ll eat)
{
	ll rem=cnt-eat;
	return (rem+1)*rem/2;
}
int main()
{
	cnt=read(),k=read();
	l=1,r=cnt;
	while(r-l>10)
	{
		mid=(l+r)>>1,tmp=calc(mid);
		if(tmp<k+mid)
		{
			r=mid-1;
		}
		else
		{
			l=mid;
		}
	}
	for(register int i=l;i<=r;i++)
	{
		if(calc(i)==k+i)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	puts("0");
}
```

---

## 作者：两年打铁 (赞：0)

# 题意
有n步操作，每一步操作可以为以下两种中的一种

1：往盒子里加入上一次加入的糖果个数+1个糖果

2：吃掉一个糖果。


yy一下发现直接枚举（滑稽）吃掉的显然不可以，那我们枚举加入的次数。

套一波高斯定理，设x为加入糖果的步数，那么盒子里糖果的个数就是$x(x+1)/2-(n-x)$

我们要使得$x(x+1)/2-(n-x)=k$

变形一波得到

$x(x+1)/2+x=k+n$

即

$x(x+3)=2*(k+n)$

然后发现x*(x+3)是根号级别的，直接保证了枚举的复杂度，答案即为n-x

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define kong putchar(' ')
#define huan putchar('\n')
#define int long long 
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[10001];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
int n,m;
signed main()
{
	read(n);
	read(m);
	for(register int i=0;i<=1e7;++i)
	{
		if(i*(i+1)/2+i==n+m)
		{
			write(n-i);
			return 0;
		}
	}
	return 0;
}
```


---

