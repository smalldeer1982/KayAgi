# [CCC 2022 S1]  Good Fours and Good Fives

## 题目描述

$\rm Finn$ 非常喜欢 $4$ 和 $5$，他认为所有的数都可以用 $4$ 和 $5$ 进行相加得出。

例：

$14=5+5+4$

$20=4+4+4+4+4$ 或 $20=5+5+5+5$

$40=4+4+4+4+4+4+4+4+4+4$ 或 $40=4+4+4+4+4+5+5+5+5$ 或 $40=5+5+5+5+5+5+5+5$

当然，$4$ 和 $5$ 的顺序并不重要，重要的是他们的个数。

给你一个正整数 $n$，问有多少种方法可以用 $4$ 和 $5$ 拼凑成 $n$。

## 说明/提示

对于 $20\%$ 的数据：$1\le n\le 10$

对于另外 $15\%$ 的数据：$1\le n\le10^5$ 并且保证
$n\equiv0$ $\pmod 4$

对于另外 $15\%$ 的数据：$1\le n\le10^5$ 并且保证
$n\equiv0$ $\pmod 5$

对于 $100\%$ 的数据：$1\le n\le 10^6$

## 样例 #1

### 输入

```
14```

### 输出

```
1```

## 样例 #2

### 输入

```
40```

### 输出

```
3```

## 样例 #3

### 输入

```
6```

### 输出

```
0```

# 题解

## 作者：BabyDragon185 (赞：90)

题目：[P8395](https://www.luogu.com.cn/problem/P8395)。

思路：我们先让数列中所有数**都变成** $4$ 。此时，只有 $n$ 是 $4$ 的倍数时可以满足可以实现，不妨设此时 $n = 4 \times m$ 。

那么如果 $n \bmod 4 = k$ ，那么就可以把 $k$ 个 $4$ **变成** $5$ ,就可以满足有方法。

那么如果 $ m < k $ ，就**不可以**实现了，其他情况**都可以**有实现方法。

再说有**多少种**方法。因为 $4$ 和 $5$ 的最小公倍数是 $20$ ，那么可以将 $5$ 个 $4$ 换成 $4$ 个 $5$ ，就**多出一组**。

所以多出的组数是 $4$ 的最多个数整除 $5$ 。

因为 $4$ 最多的个数应该是 $m-k$ ，所以多出来是组数是 $m-k$ 除以 $5$ 的整数部分。

那么在可以实现时，可实现组数就是 $m-k$ 除以 $5$ 的整数部分加 $1$ 。

代码如下。

```cpp
#include<bits/stdc++.h>//万能头。 
using namespace std;//标准命名空间。
int main()
{
	int n;//n如题目所述。 
	cin>>n;
	if(n/4<n%4)//判断是否有解。 
	{
		cout<<0;
		return 0;//终止程序。 
	}
	cout<<(n/4-n%4)/5+1;//输出组数。 
	return 0;//好习惯！ 
}
```

都看到这里了，不妨点个赞再走吧，但是**千万不要抄袭**！！！

---

## 作者：water_three (赞：23)

### 题目大意：
给定一个数 $n$，求出用 $4$ 和 $5$ 有多少种方案能凑出 $n$。

### 解法：
很容易想到用 $f_i$ 表示凑出数字 $i$ 的合法方案数是多少。然后进行动态规划，有转移方程 $f_i=f_{i-4}+f_{i-5}$。

但是出现了一个问题，我们会发现因为不管加法的顺序，即先加上 $4$ 还是先加上 $5$。所以一种方案被重复计算了很多次。

### 思路：
于是我们考虑先将用 $4$ 能表示的数先记录下来，再来考虑 $5$，这样能避免重复。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[1000001];
int main() {
	cin>>n;
	memset(f,0,sizeof f);
	f[4]=1;
	for(int i=1; i<=1000001; i++)
		if(i-4>0)f[i]+=f[i-4];
	f[5]=1;
	for(int i=1; i<=1000001; i++)
		if(i-5>0)f[i]+=f[i-5];
	cout<<f[n]<<endl;
}
```


---

## 作者：Fr0sTy (赞：11)

### 题意简述
------------

给出一个整数 $n$。

问有多少种情况，使 $n$ 能被拆分成若干个 $4$ 和若干个 $5$ 相加。

### 解题思路
------------

我们设能被拆分成 $x$ 个 $4$ 和 $y$ 个 $5$。

这样可以列出方程：

$$4 \cdot x + 5 \cdot y = n $$

但显然枚举 $x$ 和 $y$ 的值会超时。

所以拿出我们初一的数学知识：**整数解问题**。

我们用含 $y$ 的代数式表示 $x$（当然用含 $x$ 的代数式表示 $y$ 也可以），有以下方程。

 $$ x = \dfrac{n - 5 \cdot y}{4}$$
 
 之后枚举 $y$ 的值即可。
 
 这里要注意，$y$ 的值可能为 $0$，所以我们要从 $0$ 开始枚举。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
int main() {
	scanf("%d",&n);
	for(int i=0;i<=n;i++) {
		if((n-5*i)<0) break;
		if((n-5*i)%4==0) ans++;
	}
	printf("%d",ans);
	return 0;
}
//code by TheCedar
```
 

---

## 作者：ztrztr (赞：4)

## 更新
[2022/10/23] 有一处笔误，感谢 @screen_123 指出

## 思路
这道题是一道暴力数学题，我们来看第二组样例：
```cpp
输入：
40
输出：
3
```
先计算：

第一组：$10$ 个 $4$，$0$ 个 $5$：$4+4+4+4+4+4+4+4+4+4
$

第二组：$5$ 个 $4$，$4$ 个 $5$ ：
$40=4+4+4+4+4+5+5+5+5$

第三组：$8$ 个 $5$：
$40=5+5+5+5+5+5+5+5$

说实话，这道题就是一个求不定方程的组数的题：

给出 $n$，已知 $4x + 5y = n$，求满足等式的个数。

## 实现
实现的话我用的是暴力实现。
1. $x = \lfloor \frac{n}{4} \rfloor$
2. 从 $0$ 开始枚举，到 $x$ 结束，正在枚举的数是 $i$，如果 $(n - i * 4) \bmod 5 = 0$，计数器加 $1$。
3. 输出计数器
### 第一步
$x = \lfloor \frac{n}{4} \rfloor$。因为在 ```C++``` 中，一个整型的除法默认就是向下取整，直接出就行了：
```cpp
x = n / 4;
```
### 第二步
枚举。这部分用 ```for``` 循环就行了。
```cpp
for (int i = 0; i <= x; i++) {
	if ((n - i * 4) % 5 == 0) cnt++;
}
```
### 第三步
输出。
```cpp
cout << cnt;
```
## 代码
下面就是大家想看的代码了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int x, n, cnt = 0;
	cin >> n;
	x = n / 4;
	for (int i = 0; i <= x; i++) {
		if ((n - i * 4) % 5 == 0) cnt++;
	}
	cout << cnt;
	return 0;
}
```
大家千万不要抄袭，不然小心棕名。

---

## 作者：GI录像机 (赞：3)

## 思路梗概：

看到第一眼，exgcd 板子题啊，可以求出一组特解使得 $4x+5y=n$，转念一想，$4$ 和 $5$ 就相差 $1$ 啊，特解~~用脚都能~~构造出来，就是 $x=-n$ 和 $y=n$。然后由于 $x$ 与 $y$ 互质，循环寻找正整数解，每次将 $x+=5$，$y-=4$，保持等式成立就可以啦。

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int a = 4, b = 5, x, y, n = read(), ans = 0;
signed main() {
	x = -n;
	y = n;
	while (y >= 0) {
		x += 5;
		y -= 4;
		if (x >= 0 && y >= 0)ans++;
	}
	write(ans);
	return 0;
}
```


---

## 作者：charleshe (赞：2)

首先，看到这道题，我们必然想到：

设 $dp_i$ 为 $i$ 的分解方法的数量，则有 $dp_i = dp_{i-4} + dp_{i-5}$。

看上去没有问题，事实上它是错的。错的原因：

> 当然，$4$ 和 $5$ 的顺序并不重要，重要的是他们的个数。

那么，对于 $14 = 4 + 5 + 5 $ 和 $14 = 5 + 4 + 5$ 两种情况而言，可以从题面的描述看出它们是一种情况，而代码不会这么认为。显然的，代码没有判断每种情况的顺序。

知道错误原因了，我们就要改正：

由于判断顺序非常麻烦，我们可以命令每一种情况下，第 $i$ 个数不能小于第 $i-1$ 个数，即，一个数只能由 $4 + 4 + \cdots + 4 + 5 + 5 + \cdots + 5$ 来组成，不过 $4$ 和 $5$ 的个数是不限的。

为了满足这种情况，我们需要对上一次加 $4$ 和加 $5$ 的情况进行分类讨论。那么 $dp$ 数组的设置方法也很明显：

设 $dp_{i,0}$ 为上一步是加 $4$ 时 $i$ 的分解方法的数量，$dp_{i,1}$ 为上一步是加 $5$ 时 $i$ 的分解方法的数量。

自然的，由于上一步加的数必须小于等于这一步加的数，所以 $dp_{i,0} = dp_{i-4,0}$，$dp_{i,1} = dp_{i-5,0} + dp_{i-5,1}$。

由于最后一步所加的数可以为 $4$ 也可以为 $5$，所以答案即 $dp_{n,0} + dp_{n,1}$，其中 $n$ 为输入的数。

考虑到刚才的状态转移方程中出现了 $- 4$ 和 $- 5$，所以我们要预处理出 $1$ 到 $5$ 的 $dp$ 值。

$n \leq 10^6$，因此时间复杂度不会炸，且计算得 $n = 10^6$ 时答案为 $50001$，因此开 `int` 足以通过此题。

综上所述，本题便做完了。且此题代码坑点极少，因此代码也好写了。

```cpp
#include <iostream>
using namespace std;
int dp[1000001][2];
int n;
int main(){
	cin>>n;
	dp[1][0]=0;
	dp[1][1]=0;
	dp[2][0]=0;
	dp[2][1]=0;
	dp[3][0]=0;
	dp[3][1]=0;
	dp[4][0]=1;
	dp[4][1]=0;
	dp[5][0]=0;
	dp[5][1]=1;//预处理前几个数的dp值
	for(int i=6;i<=n;i++){
		dp[i][0]=dp[i-4][0];
		dp[i][1]=dp[i-5][0]+dp[i-5][1];
	}
	cout<<dp[n][0]+dp[n][1];
	return 0;
}
```


---

## 作者：sixrc (赞：1)

### 题目大意

给定一个数 $n$，求满足 $4 \times a+5 \times b=n(a,b \ge 0)$ 的 $(a,b)$ 个数。

### 分析

这题数据范围启示我们可以暴力枚举。

考虑枚举 $a \in[0,\dfrac{n}{4}]$，我们把上式变个形：如果 $n -4 \times a$ 是 $5$ 的倍数，就找到了一组合法解 $(a,b)$。时间复杂度 $O(n)$。

枚举 $b$ 也可以。

---

## 作者：skyskyCCC (赞：1)

**前言。**

- 题意：[题目传送门](https://www.luogu.com.cn/problem/P8395)。
- 考查：二元一次方程式。

**分析。**

因为 $4$ 和 $5$ 顺序并不重要，交换顺序算一种。

所以可得 $4x+5y=n$ 的方程式。

小注：在这个方程式中的 $x$ 代表 $4$ 的个数，同时 $y$ 代表 $5$ 的个数，则 $n$ 就为题目所述。

那么我们也可以知道方程式中的 $x$ 与 $y$ 均为**非负整数**，所以我们只要枚举 $x$ 后，判断对应的 $y$ 是否为非负整数即可，如果是，答案加一。

小注 $2$ 号：**非负整数指 $0$ 与正整数**。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,ans;
int main(){
    cin>>n;
    for(int i=0;i<=n/4;i++){//x的范围小于等于n/4，原因见后记。(问题1)
        if((n-i*4)%5==0){
            ans++;
        }
        //以上为判断y的代码，(n-i*4)代表5y,对5取余为0就代表为整数。
    }
    cout<<ans<<"\n";
    return 0;
}
```
**后记。**

问题 $1$ 的解释：

当 $y$ 取最小值 $0$ 时，可得 $4x=n$ 的一元一次方程式，那么 $n$ 只能取 $x=n/4$ 的结果。

---

## 作者：rai1gun (赞：1)

### 1.前言

坑还是蛮多的，dfs 拍了半天发现错在了一个很小的数字 QWQ，果然还是太菜了。

好多人用的都是暴力，那我就来一发 exgcd 吧。

### 2.解法

$\texttt{subtask1}$ 解法：

送分，dfs 或暴力都行。

$\texttt{subtask2}$ 解法：

我们将这个式子设为一个二元一次方程，即： $4x+5y=n$。

不难求出肯定有一组解为 ：
$
\left\{
\begin{aligned}
x= \dfrac{n}{4} \\
y=0
\end{aligned}
\right.
$

然后，我们一直将 $x-5$，将 $y+4$，直到 $0 \le x<5$，我们就得到了 $x$ 的最小整数解。因此，我们就有了解的个数，即为答案。

$\texttt{subtask3}$ 解法：同 $\texttt{subtask2}$。

$\texttt{subtask4}$ 解法：

我们知道，对于二元一次方程，可以用 exgcd 来求解。

我们先用 exgcd 来求出 $x_{max}$ 以及 $x_{min}$ （不知道怎么求得去[这里](https://www.luogu.com.cn/problem/P5656)）。

回忆刚才 $\texttt{subtask2}$ 的解法，我们可以把所有 $x$ 的解列成一个等差数列，其中首项是 $x_{max}$，尾项是 $x_{min}$。解的个数即为 $\dfrac{x_{max}-x_{min}}{5}+1$。

### 3.题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define F1(i,a,b,k) for(int i=a;i<=b;i+=k)
// 快读已省略
inline void exgcd(ll &x,ll &y,ll a,ll b){// 扩欧板子
	if(!b){
		x=1,y=0;
		return ;
	}
	exgcd(x,y,b,a%b);
	ll tmp=x;
	x=y;
	y=tmp-a/b*y;
}
ll T,a,b,c,x,y;
const int Not[]={1,2,3,6,7,11};//无解的情况
int main(){
	a=4,b=5;
	read(c);
	F1(i,0,5,1)
		if(Not[i]==c){
			print(0);
			return 0;
		}
	exgcd(x,y,a,b);
	x*=c,y*=c;
	if(x<=0){
		ll tmp=abs(x)/b+1;
		x=x%b+b;
		y-=tmp*a;
	}
	if(y<=0){
		ll tmp=abs(y)/a+1;
		y=y%a+a;
		x-=tmp*b;
	}
	ll tmp=x/b;
	x-=tmp*b;
	if(!x) x+=b,tmp--;
	y+=tmp*a;
	ll x1=x,y2=y;
	tmp=y/a;
	y-=tmp*a;
	if(!y) y+=a,tmp--;
	x+=tmp*b;
	ll x2=x,y1=y;
	int ans=(x2-x1)/b+1;
	if(c%a==0 && c>20) ans++;
	if(c%b==0 && c>20) ans++;
   // 上面两个情况一定要保证 c>20，否则方程只有全是 4 或者全是 5 的解
	print(ans,' ');
	return 0;
}
```

完结撒花！

---

## 作者：yeshubo_qwq (赞：1)

完全背包求方案数。

对于这道题而言，其实只有两样物品，一件是 $4$，一样是 $5$。

可以直接做两遍循环，状态转移方程：$dp_i=dp_i+dp_{i-4/i-5}$。

记得将 $dp_0$ 的初始值赋 $1$。

代码：

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
namespace P{
	int n,i,dp[1000005];
	void solve(){
		cin>>n;
		dp[0]=1;
		for (i=4;i<=n;i++) dp[i]+=dp[i-4];
		for (i=5;i<=n;i++) dp[i]+=dp[i-5];
		cout<<dp[n];
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	return P::solve(),0;
}


```


---

## 作者：Dream_weavers (赞：0)

建议评红。

注：此题解中的 $c$ 即代表题目中的 $n$。

大致思考一下，就能把题变成：求方程 $4x+5y=c$ 非负整数解组数。这是一道很明显的**二元一次不定方程**，也就是 $ax+by=c$（[B2086](https://www.luogu.com.cn/problem/B2086)），其中 $a=4,b=5$，$c$ 是输入数据。只需循环枚举 $x$，它的上限是 $\left\lfloor\dfrac{c}{a}\right\rfloor$，用 $x$ 求出 $y=\dfrac{c-ax}{b}$，然后判断 $ax+by=c$ 是否成立，累加即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a=4,b=5,c,tot;
int main(){
	scanf("%d",&c);
	for(int x=0;x<=c/a;x++){
		int y=(c-a*x)/b;
		if(a*x+b*y==c)tot++;
	}
	printf("%d",tot);
	return 0;
}

```

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P8395)

# 题意简述

给你一个正整数 $n$，问有多少种方法可以用 $4$ 和 $5$ 拼凑成 $n$。

# Solution

此题并不难，可以将题意理解为求 $5x$ $+$ $4y$ $=$ $n$ 的非负整数解的数量。

暴力枚举，用每一个正整数 $x$ 枚举，看看对应的 $y$ 是不是非负整数，如果是就计数器加一。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, sum = 0; scanf("%d", &n);
	for(int i=0; i<=n; i++) {if((n-(i*5)%4==0)) sum++;}
	printf("%d\n", sum);
	return 0;
}
```

By 2022.6.12 蒟蒻的第十篇题解

---

## 作者：BetaCutS (赞：0)

因为 $4$ 和 $5$ 交换顺序算一种，所以 $4x+5y=n$ 的自然数解个数就是答案。

枚举 $x$，判断对应的 $y$ 是不是整数，如果是答案加一。

## 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int n;
signed main()
{
	n=read();
	int p=n/4,ans=0;
	for(int i=0;i<=p;i++)
		if((n-i*4)%5==0)
			ans++;
	printf("%d",ans);
	return 0;
}

```


---

## 作者：Ag2WO4 (赞：0)

这是一道不定方程题，我们用余数的思维去解决它。

思路：先不断减去 $4$ 直到该数可以被 $5$ 整除，接着不断减去 $5$ 直到该数可以被 $20$ 整除。注意到剩下的每个 $20$ 有全部分成 $4$ 和全部分成 $5$ 两种方法，而被减去的 $4$ 和 $5$ 是不成套的，不能变换。那么有 $n$ 套 $20$ 就有选 $0$ 到 $n$ 个方案一，剩下的全是方案二，共 $n+1$ 种选法。

如果遇到不能拆分的情况，根据贪心的思维，一定是输入数据过小，此时按上面的算法得到的 $20$ 的套数是负的，输出 $n+1$ 与 $0$ 的最大值即可。

Python 代码：
```python
a=int(input())
while a%5:a-=4
a=a//20;print(max(a+1,0))
```
C/C++ 代码：
```c
#include<stdio.h>
int a;
int main()
{
	scanf("%d",&a);
	while(a%5)a-=4;
	if(a<0)putchar(48);
	else printf("%d",a/20+1);
}
```


---

