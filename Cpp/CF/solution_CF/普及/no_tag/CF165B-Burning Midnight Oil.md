# Burning Midnight Oil

## 题目描述

有一天，Vasy被委托了一个非常重要的任务:在一个晚上写一个程序。该程序由n行代码组成。Vasya已经筋疲力尽了，所以他这样工作：首先他写v行代码，喝一杯茶，然后他写![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)行代码，再喝一杯茶，然后他再写![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)v行......以此类推。
![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/ff48225f7f772c08409f2d464b02c44cf20620e2.png)，表示a除以b后向下取整。若当前![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/ff48225f7f772c08409f2d464b02c44cf20620e2.png)的值等于0，Vasya会睡着，但此之前他必须先完成程序。
Vasya想知道，在睡着之前，允许他写出不少于n行代码的最小值v可以取多少。

## 样例 #1

### 输入

```
7 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
59 9
```

### 输出

```
54
```

# 题解

## 作者：fls233666 (赞：2)

首先可以发现，**答案具有单调性**：设答案为$v$，则$v,v+1,v+2,v+3...$都是可以写完这$n$行代码的。因此，我们使用**二分答案**。

二分边界：根据数据范围，$1 \le n \le 10^9$。因此下界设为$1$，上界设为$10^9$

二分得到一个答案后，**按照题意模拟**，如果能写完所有代码，缩小上界；不能写完所有代码，缩小下界。

下面是代码：

```cpp
#include<iostream>
using namespace std;
bool ck(int wn,int wk,int wv){
	int n=wn,k=1,v=wv,w;   
	w=v/k;
	while(w&&n>0){   //模拟写代码过程，直到写完或睡着
		n-=w;
		k*=wk;
		w=v/k;
	}
	if(n<=0)   //根据是否成功写完返回bool值
		return true;   
	else
		return false;    
}
int main()
{
	int n,pk,l=1,r=1000000000,md;
	scanf("%d%d",&n,&pk);  //读入
	while(l<r){   //二分
		md=(l+r)/2;
		if(ck(n,pk,md))  //检查答案可行性
			r=md;   //缩小上界
		else
			l=md+1;   //缩小下界
	}
	printf("%d",l);   //输出答案
	return 0;
}
```


---

## 作者：tallnut (赞：1)

二分的几乎模板题？
# 思路
我们发现如果 $v$ 能够满足条件，$v+1$ 依然能满足条件，因此答案具有单调性。

这当然要用——**二分答案**。

二分下界 $1$，上界 $n$。因为当答案为 $n$ 时最初就会加上 $n$，一定能满足。套上二分板子即可。

至于 check() 函数，就开 long long，然后开两个变量根据题意模拟即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/137603430)。
```
#include <iostream>
using namespace std;
int n,k;
long long l,r,mid,ans;
bool check(long long x)
{
	unsigned long long sum = x;
	unsigned long long tmpk = k;
	while (tmpk <= x)
	{
		sum += x / tmpk;
		tmpk *= k;
	}
	return sum >= n;
}
int main()
{
	cin >> n >> k;
	l = 1;
	r = n;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans;
}
```

---

## 作者：luogu_sdfx1803 (赞：0)

## 题目分析
这道题乍一看，具有十分明显的 **单调性** ，即若答案 $a$ 符合条件，那么 $v$ 即便大于 $a$,也是可以打完 $n$ 行代码。但若直接枚举的话可能会超时。既然是这样，便可以用 **二分答案** 来解决这道题。

当我们得出一个二分答案时，便要加以判断。注意，当一个二分答案符合要求时，不可以直接设为总答案，因为可能存在更优解。

例如不可以这样：
```cpp
if(check(mid)==1){
   cout<<mid;
   return 0; 
}
```
应该这样：
```cpp
if(check(mid)==1){
   rt=mid; 
}
```
## 题目代码

如下：
```cpp
#include<bits/stdc++.h>
#define int long long //谨防见祖宗
using namespace std;
int n,k,a,b;
int check(int x){
	int m=n;
	a=x;
	b=1; //设置初始值
	while(m>0&&a>0){
		m-=a;b*=k;a=x/b; //进行模拟	
	}
	if(m<=0){
		return 1; //符合条件
	}
	else{
		return 0;
	}
}
signed main(){
	cin>>n>>k;
	int lt=1-1,rt=1e9+1; //定义二分查找的边界
	while(lt+1!=rt){ //若lt和rt相邻，则无元素可查找
		int mid=(lt+rt)/2; //取中间值
		if(check(mid)==1){ //若符合条件
			rt=mid; //看一下是否还有最优解
		}
		else{ //说明取小了
			lt=mid;
		}
	}
	cout<<rt;
	return 0;
}
```


---

## 作者：zxh923 (赞：0)

# CF165B Burning Midnight Oil 题解

[题目传送门](https://www.luogu.com.cn/problem/CF165B)

### 思路

题意指找出最小的满足要求的 $v$，而且我们可以发现，$v$ 越小，行数就越少，由此我们可以想到二分答案。

在二分答案中，我们一般使用
```cpp
mid=(l+r)/2;
```
但为了防止爆掉，我们可以使用
```cpp
mid=(r-l)/2+l;
```
效果是相同的，但有效地防止了爆掉。

### 代码

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long n,k,l,r,mid,ans;
bool check(int x){//判断v是否符合条件
	long long cnt=0,a=1;
	while(x/a!=0){
		cnt+=x/a;
		a*=k;
	}
	return cnt>=n;//达到要求为1
}
int main(){
    std::ios::sync_with_stdio(0);//读写优化
    cin>>n>>k;//读入
    l=0;
    r=1e9;
    while(l<r){//二分答案
		mid=(r-l)/2+l;//防止爆int
		if(check(mid)){
			r=mid;
			ans=mid;//如果行数达到或超过要求
		}
		else{
			l=mid+1;//如果达不到要求
		}
	}
	cout<<ans;
	return 0;
}
```
### 函数部分详细解释

只要写的行数仍然不是 $0$，就把这一次写的行数加到能够写的行数中。当这次写的行数为 $0$ 时，代表睡着了，需要判断当前行数是否符合要求。

如不符合，把 $r$ 调小继续二分。

如符合，记录答案，把 $l$ 调大继续二分。

---

## 作者：zhanghaosong (赞：0)

# CF165B Burning Midnight Oil 题解

### 灵机一动

由于如下的两点理由，我们认定，本题算法——**二分答案**！

1. 题中写“允许他写出**不少于** $n$ 行代码的**最小**值 $v$ 可以取多少”

2. 这道题的解具有**单调性**。当 $v\uparrow,\left \lfloor \frac{v}{k^i} \right \rfloor \uparrow(k\in[1,2...n])$

### 思路

我们可以对 $v$ 进行二分答案。定义两个变量 $l=1,r=10^9$。如果 ZHS（不用管他叫什么）没有完成任务，左端点加 $1$；如果完成任务，右端点减 $1$。知道 $l\leq r$ 不成立为止。

在 `check()` 函数中，按照题意模拟 ZHS 写代码的过程即可。

### 坑点

数据范围 $1 \leq n \leq 10^9$，极容易爆 `int`。所以我们开启 `long long` 长整型更保险。

### 代码

真的不贴了（逃哇）……

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF165B)

这道题目让我们求这个东西：

> 设 $\left \lfloor \displaystyle \frac v {k^i} \right \rfloor=x$，求 $\sum_{i=0}^{x>0}x \ge n$ 满足这个条件的最小的 $i$ 的值。

我们看一下数据范围：$1\le n\le 1\times 10^9$。只能使用 $O(n)$ 级别的算法，但是这样肯定是不够的，因为你只要枚举两次：一次是当前的 $v$，另一次则是当前的 $v$ 能否满足条件。

那我们顿时就想到了枚举较为快速的二分答案。我们再看一下是否满足单调性。的确，当 $v$ 越大，$\sum_{i=0}^{x>0}$ 一定也是越大的。（这里还是设 $\left \lfloor \displaystyle \frac v {k^i} \right \rfloor=x$）

我们再来算一下时间，每次枚举都是 $O(\log_2n)$ 而我们每次计算 $\sum_{i=0}^{x>0}$ 的时间复杂度差不多是 $O(\log_2n)$，所以综合起来是 $O(n)$ 的复杂度，所以不会超时。

那么就可以了，注意一下 $\operatorname {check}$ 函数就行了，二分答案还是很简单的。 

---

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
bool check(int x){//检查当前是否可以 
	long long ans=0;
	for(int i=1;(int)(x/i)>0;i*=k)ans+=(x/i);
	if(ans>=n)return true;
	return false;
}
int main(){
	scanf("%d%d",&n,&k);
	int l=1,r=n,mid,ans;
	while(l<=r){//二分答案
		mid=(r-l)/2+l;//mid的写法，以防暴int
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Cutler (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF165B)

简化题意：

给定 $n$ 和 $k$，求满足

$$
\sum_{i=0} \left \lfloor \frac{v}{k^i} \right \rfloor \le n
$$

的最小的 $v$

可以看出答案是具有单调性的。如果 $v$ 符合条件，那么 $v + 1$ , $v + 2$ 也都是符合条件的。求出最小的 $v$ ，显然要用二分了。

首先是要二分 $v$ 值的，那么 $check$ 函数根据题意模拟即可。

直接看代码吧。

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int n, k;

void input(){scanf("%lld%lld",& n,& k);}

int mypow(int a,int b){
	int ans = 1;
	while(b){
		if(b & 1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

bool check(int x){
	int sum = n, t = x, v = 1;
	while(t && sum > 0){
		sum -= t;
		v *= k;
		t = x / v;
	}
	return sum <= 0;
}

void work(){
	int l = 1,r = 1e9+1;
	while(l < r){
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	
	printf("%lld\n", l);
}

signed main(){
	input();
	
	work();
	
	return 0;
}
```

优雅结束。

---

## 作者：_HiKou_ (赞：0)

枚举不太现实，最好用二分查找。

由题可知 $1\leq n \leq 10^9$，所以我们可以在本题的数据范围 $\left[1,10^9\right]$ 内用二分的方法来找到最小的 $v$。

当然，也可以在 $\left[1,n\right]$ 的范围内进行二分查找。

这里是证明：如果此时的 $v$ 为答案且满足 $v>n$，由题知 $v-1$ 一定优于 $v$。以此类推，可得 $v$ 的取值范围在 $\left[1,n\right]$ 之间。

具体的，对于每一个 $v$，可以求出在这个 $v$ 下最多能写多少代码，记为 $m$。

- 如果 $m<n$，表示这个 $v$ 太小了，要往大了取。
- 如果 $m>n$，表示这个 $v$ 太大了，要往小了取。

还有一点，最好开 long long 不然可能会溢出。

CODE：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,ans;
ll ef(ll l,ll r)//二分
{
	if(l>=r)return r;
	ll mid=(l+r)>>1;//右移，即除以2
	ll times=1,now=0;//表示除以的数和现在写的行数
	while(mid/times)//可以自动向下取整
	{
		now+=mid/times;
		times*=k;
	}
	if(now>=n)return ef(l,mid);//二分
	if(now<n)return ef(mid+1,r);
}
int main(){
	scanf("%lld%lld",&n,&k);
	cout<<ef(1,n);
	return 0;
}
```

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF165B)

思路一：暴力枚举 $v$ ：

时间复杂度： $O(nlogn)$

看到 $1 \le n \le10^{9}$ ，嗯，肯定会超时。

思路二：二分寻找 $v$ ：

时间复杂度： $O(logn*logn)$

$1 \le n \le10^{9}$ ，可以通过。

方法：

- $1.$ 输入 $n$ 和 $k$ ；

- $2.$ 二分查找 $v$ 的值；

- $3.$ 判断是否可行；

- $4.$ 根据上一步结果更新答案并修改范围。

细节：

- $1.$ Vasya会先写 $v$ 行代码，所以统计时计数器不应该归零，应该初始为 $v$ ；

- $2.$ $v$ 的上界初始为 $n$ 。这里借鉴一下dalao[@暮光闪闪](https://www.luogu.com.cn/user/19811)的思路：

由于 $n \le v$ $+$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png) $+$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png) $+$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/a5bacd91332aa3ca090a08cb4e8f844f5d3d784c.png) $+$......由题目数据易知：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)、![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)、![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/a5bacd91332aa3ca090a08cb4e8f844f5d3d784c.png) 等都为非负数，不妨考虑最坏的情况就是这些数都为0。那么就有 $n \le v$，所以把 $v$ 上界设为 $n$ 就对了。

- $3.$ 一定要开 $long$ $long$ ，一定要开 $long$ $long$ ，一定要开 $long$ $long$ ！

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long//个人习惯 
using namespace std;
LL l=1,r,ans,n,k;//l、r是二分的下界和上界，ans是答案，n、k如题意 
int check(LL x)//check函数是用来检测当前二分到的v是否可行的 
{
	LL cnt=x;//cnt是计数器 
	for(LL i=k;x/i>0;i*=k)//如果[x/i]的值变为了0，分母只会越来越大，[x/i]的值会一直为0，要及时跳出 
	{
		cnt+=(x/i);//加上这一行代码 
	}
	return cnt>=n;//如果写够了代码，返回1；反之返回0 
}
int main()
{
	cin>>n>>k;//输入 
	r=n;//设置上界 
	while(l<=r)//二分 
	{
		LL mid=(l+r)/2; 
		if(check(mid))//如果可行 
		{
			ans=mid;//更新答案 
			r=mid-1;//缩小上界 
		}
		else//如果不可行 
		{
			l=mid+1;//扩大上界 
		}
	}
	cout<<ans;//输出答案 
	return 0;//结束程序 
}
```

---

## 作者：皮卡丘最萌 (赞：0)

这道题目无法直接枚举来得到答案，所以我们可以用二分+判定来加快速度。

我们可以直接枚举答案，再进行判断，例如样例2：59 9

首先l=1,r=59.

第一次mid=(1+59)/2=30，此时可以打30+3=33行，不行，t=mid+1=31

第二次mid=(31+59)/2=45，此时可以打45+5=50行，不行，t=mid+1=46

第三次mid=(46+59)/2=52，此时可以打52+5=57行，不行，t=mid+1=53

第四次mid=(53+59)/2=56，此时可以打56+6=62行，可以，w=mid-1=55,并保存答案56

第五次mid=(53+55)/2=54，此时可以打54+6=60行，可以，w=mid-1=53,并保存答案54

第六次mid=(53+53)/2=53，此时可以打53+5=58行，不行，t=mid+1=54，此时t>w，退出循环，并且输出结果。

这里枚举答案时有一个注意点，就是判断时累加器要用int64/long long，不然可能会炸。

代码：
```pascal
var n,m,t,w,mid,bao:longint;
function pd(x:longint):boolean;           //判断答案
var y:longint; s:int64;
begin
s:=x; y:=x;                               //首先至少打了x行
while y>0 do
  begin y:=y div m; s:=s+y; end;             //枚举共打几行
exit(s>=n);                 //如果足够返回true，不够返回false
end;

begin
readln(n,m);
t:=1; w:=n;                       //初始化
while t<=w do
  begin
  mid:=(t+w) div 2;               //求中间值
  if pd(mid) then
    begin bao:=mid; w:=mid-1; end       //可以就保存答案
  else t:=mid+1;                      //不可以则缩小范围
  end;
writeln(bao);                 //输出答案
end.
```


---

## 作者：暮光闪闪 (赞：0)

## 思路
很明显这道题用二分。~~因为这是我们学校的二分专题上的题~~

题意就是要使v+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/a5bacd91332aa3ca090a08cb4e8f844f5d3d784c.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/ede57aab14af8ddc634829ecddc32e347a436c9b.png)+...的值大于等于n。
一直暴力试v的值就行了，如果式子加起来的值超过了n，就使v的值变小，直到无法超过。这里的上界也很好确定。以下是简单的推导：

由于v+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/a5bacd91332aa3ca090a08cb4e8f844f5d3d784c.png)+![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/ede57aab14af8ddc634829ecddc32e347a436c9b.png)+...>=n由题目数据易知![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)、![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)、![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/a5bacd91332aa3ca090a08cb4e8f844f5d3d784c.png)、![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF165B/ede57aab14af8ddc634829ecddc32e347a436c9b.png)等都为非负数。不妨考虑最坏的情况就是这些数都为0。那么就有v>=n，所以把v上界设为n就对了。
## 代码如下：
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll n,k;
bool check(ll x){
	ll sum=0;//sum计算式子的现在值
	ll cnt=1;//k的指数部分
	while(x/(cnt*=k))//如果[a/b]的值变为了0，分母只会越来越大，[a/b]的值会一直为0，要及时跳出
		sum+=x/cnt;
	if(sum+x>=n)return 1;//如果式子值大于n，那么说明此方案能行
	return 0;//否则该方案不行
}
int main(){
	cin>>n>>k;
	ll l=1,r=n,ans;
	while(l<=r){
		ll mid=(l+r)/2;//二分固定套路
		if(check(mid)){
			ans=mid;//如果答案可以，那么就更新最终ans
			r=mid-1;//同时使v的上界变小
		}
		else l=mid+1;//否则使v的下界变大
	}
	cout<<ans;
	return 0;
}
```

---

