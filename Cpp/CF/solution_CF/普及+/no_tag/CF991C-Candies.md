# Candies

## 题目描述

After passing a test, Vasya got himself a box of $ n $ candies. He decided to eat an equal amount of candies each morning until there are no more candies. However, Petya also noticed the box and decided to get some candies for himself.

This means the process of eating candies is the following: in the beginning Vasya chooses a single integer $ k $ , same for all days. After that, in the morning he eats $ k $ candies from the box (if there are less than $ k $ candies in the box, he eats them all), then in the evening Petya eats $ 10\% $ of the candies remaining in the box. If there are still candies left in the box, the process repeats — next day Vasya eats $ k $ candies again, and Petya — $ 10\% $ of the candies left in a box, and so on.

If the amount of candies in the box is not divisible by $ 10 $ , Petya rounds the amount he takes from the box down. For example, if there were $ 97 $ candies in the box, Petya would eat only $ 9 $ of them. In particular, if there are less than $ 10 $ candies in a box, Petya won't eat any at all.

Your task is to find out the minimal amount of $ k $ that can be chosen by Vasya so that he would eat at least half of the $ n $ candies he initially got. Note that the number $ k $ must be integer.

## 说明/提示

In the sample, the amount of candies, with $ k=3 $ , would change in the following way (Vasya eats first):

 $ 68 \to 65 \to 59 \to 56 \to 51 \to 48 \to 44 \to 41 \\ \to 37 \to 34 \to 31 \to 28 \to 26 \to 23 \to 21 \to 18 \to 17 \to 14 \\ \to 13 \to 10 \to 9 \to 6 \to 6 \to 3 \to 3 \to 0 $ .

In total, Vasya would eat $ 39 $ candies, while Petya — $ 29 $ .

## 样例 #1

### 输入

```
68
```

### 输出

```
3
```

# 题解

## 作者：liuyi0905 (赞：3)

很显然，$k$ 越大，吃掉的糖果越多，$k$ 越小，吃掉的糖果越少。有了单调性，就可以用二分答案来解题。

再此浅浅的讲一下二分答案：
>首先，所有的二分，都得满足单调性。

>在一个范围里查找符合条件的与不符合条件的边界，我们称其为**临界点**。应为二分满足单调性，就可以直接判断如果满足条件，就将左边界缩小成 `mid`；否则将右边界缩小成 `mid`。

>直到最后左边界与右边界相撞了，其中一个边界就是答案。

二分写完了，剩下的就是 `check` 函数里的内容了。

1. 定义两个变量 $now$，$sum$，分别表示剩下的糖果和吃掉的糖果。
2. `while` 循环判断是否还有糖果，`now-=x,sum+=x,now-=now/10`，照题目中的做。
3. 最后判断 $sum$ 是否大于 $\frac{n}{2}$，如果是，则 `return 1`；否则 `return 0`。

最后给上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,l,r;
bool check(int x){
	int now=n,sum=0;
	while(now){
		if(now<=x){sum+=now;break;}
		now-=x,sum+=x,now-=now/10;
	}
	return sum>=m;
}
signed main(){
	cin>>n;
	if(n&1)m=n/2+1;
	else m=n/2;
	r=n+1;
	while(l+1<r){
		int mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	cout<<r;
	return 0;
}
```

---

## 作者：傅思维666 (赞：2)


## 题解：

首先来说一下这道题为什么要用二分来解决。

二分需要满足两种结构：第一个，我们知道解可能存在于一个固定的区间。第二个，这个区间必须具有单调性。

假如我们已知的区间是答案的值域，那么这个二分就叫做二分答案。假如我们已知的区间是我们自己定义的一个序列，那么这个二分就叫二分查找。前提就是**必须有序**。一开始本蒟蒻真的没有想到二分，还在那傻乎乎地找。通过这道题也是能够发现，让我们在可能范围内确定一个解，尤其是最小解/最大解。二分真的是一个不错的选择。

那么我们来设计这个二分算法：

首先确定二分区间，这道题的二分区间就是$1-n$，这个应该不用证明...

然后我们确定二分转移的条件：只要按照这个值拿拿拿，拿到的东西满足$tot>n/2$，那么就是合法的，区间左移，否则右移。

那么就是二分的重头戏：判断函数。

这个依照题意模拟就可以。

对于二分循环的写法，如果还有模糊的，请移步本蒟蒻的这篇博客：

[浅谈二分写法](https://www.cnblogs.com/fusiwei/p/11461023.html)

（为了保证二分模板的完整性，我还是喜欢把两个函数分开写...）

代码：

```cpp
#include<cstdio>
#define int long long
using namespace std;
int n,tmp;
int judge(int mid)
{
    int now=n,tot=0;
    while(now)
    {
        if(now<=mid)
        {
            tot+=now;
            break;
        }
        now-=mid;
        tot+=mid;
        now-=now/10;
    }
    return tot;
}
bool check(int mid)
{
    if(judge(mid)>=tmp)
        return 1;
    else
        return 0;
}
signed main()
{
    scanf("%I64d",&n);
    int l=1,r=n;
    if(n&1)
        tmp=n/2+1;
    else
        tmp=n/2;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%I64d",l);
    return 0;
}
```



---

## 作者：Stars_visitor_tyw (赞：2)

## CF991C Candies 题解
### 思路：
很明显，如果一个数 $k$ 符合条件，那么比 $k$ 大的数都能满足条件，符合单调性，可以用二分答案来做，如果当前猜到的数 $mid$ 符合条件，就把左边界变成 $mid$，也就是把答案猜的更大，否则猜的更小，把右边界变成 $mid$。判断函数则定义两个变量 $now$ 和 $sum$，分别表示剩下的糖果和吃掉的糖果。`while` 循环按题意模拟，最后判断 $sum$ 是否大于 $n/2$，如果大于则 `return true`，否则 `return false`。

### 代码：
```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
#define int long long
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(int x)
{
    if(x<0){x=-x;putchar(45);}
    if(x>9) write(x/10);
    putchar(x%10+48);
    return;
}
int n,m,l,r;
bool check(int x)
{
	int now=n,sum=0;
	while(now)
    {
		if(now<=x)
        {
        	sum+=now;
            break;
        }
		now-=x;
        sum+=x;
        now-=now/10;
	}
	return sum>=m;
}
signed main()
{
	n=read();
	if(n&1) m=n/2+1;
	else m=n/2;
	r=n+1;
	while(l+1<r)
    {
		int mid=(l+r)/2;
		if(check(mid)==true)
        {
        	r=mid;
        }
		else l=mid;
	}
	write(r);
	return 0;
}

---

## 作者：ImposterAnYu (赞：1)

# 解析
这题的答案显然满足单调性——$k$ 越大，Vasya 吃掉的糖果数越多。加上这题的 $n$ 比较大，于是我们可以考虑用二分来确定 $k$ 的值。

首先，我们要考虑当 $k$ 已经确定时，如何计算 Vasya 吃掉的糖果数。题目已经说了，每天 Vasya 会先吃 $k$ 个糖果，并且会在糖果数不足 $k$ 时将糖果全部吃掉；Vasya 吃完之后，Petya 会吃掉 $\left\lfloor\dfrac{n}{10}\right\rfloor$ 个糖果（因为 $n$ 的 $10\%$ 就是 $\frac{n}{10}$，并且题目也说了要向下取整）。两个人会一直吃，直到糖果吃完为止。

据此，我们可以写出一个简单的计算 Vasya 吃掉的糖果数的代码：
```c++
		mid = (l + r) >> 1,nn = n,s = t = 0;//mid 为当前的 k，nn 和 n 均为糖果总数，s 为 Vasya 吃掉的糖果数，t 为计算 Vasya 本次吃掉的糖果数。 
		while(nn){//当 nn = 0（即糖果已吃完）时，退出循环，统计答案。 
			t = min(mid,nn),s += t,nn -= t,nn -= nn / 10;//计算 s。 
		}
```
如果 $s \ge \frac{n}{2}$（移项后得 $2s \ge n$），说明当前的 $k$ 符合要求，但是不一定是最小的符合要求的 $k$，所以我们需要将 $r$ 减小到 $k$（因为 $k$ 已经符合要求了，比这个 $k$ 更大的 $k$ 不可能是答案）；如果 $s < \frac{n}{2}$（移项后得 $2s < n$），说明当前的 $k$ 不合要求，符合要求的 $k$ 肯定比这个 $k$ 要大，所以我们需要将 $l$ 就增大到 $k + 1$（因为 $k$ 不符合要求，最小的符合要求的至少为 $k + 1$）。

当我们二分到 $l = r$ 时，我们就已经可以退出二分了（因为这时的答案势必就是 $l$），所以我们执行二分的条件应设为 $l < r$（如果设为 $l \leq r$ 的话，程序就会陷入死循环）。

这样一来，我们就可以得到这题的完整代码了。
# AC code
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 100005
using namespace std;
int1 n,l,r,mid,s,t,nn;

int1 read(){//又是快读。 
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

void print(int1 x){//又是快写。
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 ^ 48);
  	return ;
}

int main(){
	n = read(),l = 1,r = n;//显而易见，答案必然在 [1,n] 之间。 
	while(l < r){//当 l = r（退出循环时，l 不可能大于 r）时，退出二分。 
		mid = (l + r) >> 1,nn = n,s = t = 0;//mid 为当前的 k，nn 和 n 均为糖果总数，s 为 Vasya 吃掉的糖果数，t 为计算 Vasya 本次吃掉的糖果数。 
		while(nn){//当 nn = 0（即糖果已吃完）时，退出循环，统计答案。 
			t = min(mid,nn),s += t,nn -= t,nn -= nn / 10;//计算 s。 
		}
		if((s << 1) >= n){//如果符合条件， 
			r = mid;//缩小 r； 
		}else{//如果不符合条件， 
			l = mid + 1;//增大 l。 
		}
	}
	print(l);//最后的答案就是 l。 
	return 0;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题目大意

两个人轮流吃糖果。第一个人会吃 $k$ 个，第二个会吃 $\left\lfloor\frac{\text{当前个数}}{10}\right\rfloor$ 个。求最小的 $k$，使得第一个人吃的糖果总数不小于一半。

## 题解

这里提供一个倍增的解法吧。

有个结论：$\bm k$** 越大，最终第一个人吃到的糖果越多**。

#### 简证

假设两个人轮流吃糖果的过程为一回合。设 $f(x,y)$ 为 $k=y$ 时第 $x$ 回合剩余的糖果总数，有：

$$\text{x回合第一个人吃掉的糖果数}=x-f(x+1,y)=k+\left\lfloor\frac{y-k}{10}\right\rfloor$$

最后一个式子，由于 $1\ge\left\lfloor\frac{y-k}{10}\right\rfloor-\left\lfloor\frac{y-k-1}{10}\right\rfloor$，因而总是单调不减的。于是，$f(x+1,y)$ 总是随着 $y$ 的增大而不断减小。因此，第二个人每回合吃到的糖果数越来越少，而总回合数也越来越少，于是第一个人吃到的总糖果数越来越多。

我们似乎可以倍增。但是，还要解决一个小问题，就是如果 $k$ 很小，会不会需要很长时间。事实上，即使 $k=1,n=10^{18}$，那么也只需要 $400$ 次左右的循环即可让糖果被吃完。

还有一个小小的优化是，我们让倍增量 $t=2^{60}$，此后不断判断答案或上 $t$ 是否能使得最终迟到的糖果**严格小于一半**，并折半 $t$。因为，只有找到能够使得吃到的糖果总数严格小于一半的最大的 $k$，才能使得最终的答案 $(k+1)$ 最小。而且，从大到小去考虑可以稍稍减去判断时所花费的循环次数。（当然，你也可以循环到第二个人吃掉的糖果已经超过一半时就直接跳出循环）。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
LL qread(){
    LL w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
LL n,p,k=1ll<<60;
bool chk(LL x){
    LL t=n,cnt=0; while(t>0){
        cnt+=min(x,t),t-=min(x,t),t-=t/10ll;
    }
    return cnt>=n/2+n%2;
}
int main(){
    n=qread(); for(;k;k>>=1){if(!chk(p|k)) p|=k;
    printf("%lld\n",p+1);
    return 0;
}

---

## 作者：Dehydration (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF991C)。


显然，这道题是二分答案。

#### 为什么要用二分？

因为是求最小的，想枚举，或者倍增，但是枚举会超时，倍增需要单调（本菜只因不会，所以不如直接二分，验证单调性。

#### 验证单调性：

很明显，$k$ 越大，吃掉的越多，加上上面说过的普通暴力会超时（$n$ 太大），所以二分答案是不会错的。


弄明白上面的，就可以毫无疑问的写代码了：

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool check(long long k, long long sum)
{
    ll a = 0, b = 0;
    while (sum)
    {
        if (sum >= k)
        {
            sum -= k;
            a += k;
        }
        else
        {
            a += sum;
            sum = 0;
        }
        if (sum >= 10)
        {
            long long tem = sum / 10;
            b += tem;
            sum -= tem;
        }
    }

    return a >= b; //坑，需要等号 
}
int main()
{
	cin.tie(0);cout.tie(0);
	//没必要的优化 
    long long sum;
    cin>>sum;
    ll l = 1, r = sum;
    while (l < r)//二分,定义[l,r]搜索，l初始值为1,r为sum(题目里的n),mid查找 
    {
        ll mid = (l + r) / 2;
        if (check(mid, sum))
            r = mid;

        else l=mid+1;
    }
    cout<<l<<endl;//输出l,不是mid(不知道可不可以 
}


```

### 完美撒花！

---

## 作者：Binary_Lee (赞：0)

## [题面传送门](https://www.luogu.com.cn/problem/CF991C)

### 解决思路
看到 $10^{18}$ 的范围，我们可以想到二分答案。只要对于每一个二分出的答案进行 $check$ ，如果可行就往比它小的半边找，不可行就往比它大的半边找。



------------
以下是 $check$ 的过程（以不可行返回 $true$ 为例）：
```cpp
bool check(long long x){
	long long v=0,N=n; //v代表Vasya吃掉的，N代表总共剩余的
	while(N){
		if(N<=x){    //如果不够Vasya吃一次了
			v+=N;    //Vasya全吃掉并退出循环
			break;
		}
		v+=x;  //Vasya吃掉x个
		N-=N/10ll+x;  //减掉Petya吃的和Vasya吃的
	}
	return n%2?v<=n/2:v<n/2;  //根据奇偶分情况判断有没有吃到一半
}
```

------------
剩下主程序中的二分就很好写了。
注意 $l$ 与 $r$ ，$md+1$ 与 $md$ 的区别：

```cpp
if(check(md)) l=md+1;
else r=md;
```


------------

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,r,md,a1; 
bool check(long long x){
	long long v=0,N=n;
	while(N){
		if(N<=x){
			v+=N;
			break;
		}
		v+=x;
		N-=N/10ll+x;
	}
	return n%2?v<=n/2:v<n/2;
}
int main(){
    scanf("%lld",&n);
    l=1,r=n;
    while(l<r){
		md=(l+r)/2;
    	if(check(md)) l=md+1;
		else r=md;
	}
	printf("%lld",l);
  	return 0; 
}
```


---

## 作者：_22222222_ (赞：0)

### Problem

[link](https://www.luogu.com.cn/problem/CF991C)

### Solution

二分答案。

其实二分答案最重要的两个地方，一个是正确性，也就是所说的单调性，另外一个就是 ```bool check()``` 的写法。

首先说一下单调性：

如果你一天吃 $now$ 个是合法的，那么：对于每一个 $mid\geq now$，一天吃 $mid$ 个显然还是合法的，因为另外一个人吃的会更少。

然后就是二分检查当前答案完以后答案区间的变化：

如果当前答案 $mid$ 合法，那么答案区间就会向着更优解移动，此时答案区间变为 $[l,mid]$，否则，答案区间会向着合法解移动，即答案区间变为 $[mid,r]$。

再然后就是 ```check()``` 函数的写法：

注意到一个事情就是另外一个人偷吃所有糖果的 $10\%$，这样暴力模拟进行  ```check``` 的时间复杂度就降到了接近对数的开销。经计算：$n=1e18$ 的时候，暴力模拟的循环次数最多进行约 $350$ 次，所以直接暴力枚举即可。

最后的最后，就是注意下小细节：可能会出现除 $2$ 向下取整判错的情形。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
bool check(int k){
    int all=n,cnt=0;
    while(all){
        if(all<=k){
            cnt+=all;
            all=0;
        }
        else{
            cnt+=k;
            all-=k;
        }
      //  printf("cnt=%lld all=%lld\n",cnt,all);
        if(all>=10){
            all-=all/10;
        }
        else{
            cnt+=all;
            all=0;
        }
     //   printf("cnt=%lld all=%lld\n",cnt,all);
    }
  //  printf("now=%lld,cnt=%lld,return %d\n",k,cnt,cnt>n/2);
    if(n%2){
        return cnt>n/2;
    }
    return cnt>=n/2;
}
signed main(){
    cin>>n;
    int l=1,r=n,ans=1;
    while(l<r){
      //  printf("l=%lld r=%lld\n",l,r);
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}

```

### update

这个题是在 $2022.07.02$ 做的，题解是在 $2022.08.06$ 写的。

代码本身比较简单，但是调代码的心路历程很复杂，当时调不过样例看着满屏调试信息不知道从哪开调。

最后的最后，[给我自己打波广告](https://www.cnblogs.com/22222222STL/)。

---

## 作者：C20210404杜铖昊 (赞：0)

这道题就是一个简单的二分

思路：

k的值只能在[1,n]中

我们将l设为1，r设为n

题意   Vasya and Petya吃的糖果数量写成函数

```
long long answer(long long k){
	long long _now,sum;//sum是Vasya吃的糖果数量
	_now = n,sum = 0;//_now是剩下的糖果
	while(_now){
		if((_now <= k)){
			sum += _now;
			break;
		}
		_now -= k;
		sum += k;
		_now -= _now / 10;
	}
	return sum;
}
```
每次只需要判断k是否满足条件即可

code：
```
#include <cstdio>
#include <iostream>
using namespace std;
long long n;
long long answer(long long k){
	long long _now,sum;
	_now = n,sum = 0;
	while(_now){
		if((_now <= k)){
			sum += _now;
			break;
		}
		_now -= k;
		sum += k;
		_now -= _now / 10;
	}
	return sum;
}
int main(){
	scanf("%lld",&n);
	long long l = 1,r = (n+1)/2,mid;//r的值可以设为（n + 1)/2
	while(l < r){
		mid = (l + r) / 2;
		if(answer(mid) >= (n + 1) / 2) r = mid;//判断
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}
```


---

