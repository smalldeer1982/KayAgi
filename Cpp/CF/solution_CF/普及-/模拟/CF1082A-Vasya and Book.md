# Vasya and Book

## 题目描述

Vasya有一本 $n$ 页的电子书，她每次可以向前或向后翻 $d$ 页（但她不能翻到书外面去）。现在她要从第 $x$ 页翻到第 $y$ 页，求她最少翻的次数。

## 样例 #1

### 输入

```
3
10 4 5 2
5 1 3 4
20 4 19 3
```

### 输出

```
4
-1
5
```

# 题解

## 作者：Lovely_Chtholly (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1082A)

### 【分析】

一共有 $3$ 种情况：

1. 直接翻到：需要满足 $\left| x - y \right| \equiv 0 \pmod d$。

1. 从最前面翻过去：需要满足 $y - 1 \equiv 0 \pmod d$。

1. 从最后面翻过去：需要满足 $n - y \equiv 0 \pmod d$。

最后，取以上情况的最小值即可获得答案。

### 【AC 代码】

```cpp
#define itn int
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int INF=0x3f3f3f3f;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int> s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
itn t=read();
signed main()
{
	while(t--)
	{
		int n=read(),x=read(),y=read(),d=read(),sum=INF;
		if(!(abs(x-y)%d))sum=min(sum,abs(x-y)/d);
		if(!((y-1)%d))sum=min(sum,(x-1+d-1)/d+(y-1)/d);
		if(!((n-y)%d))sum=min(sum,(n-x+d-1)/d+(n-y)/d);
		if(sum==INF)puts("-1");
		else cout<<sum<<"\n";
	}
	return 0;
}
```

~~因为学校网络有限制，所以在洛谷上交不了，但是 CF 自测是AC的。~~

---

## 作者：Furina_Hate_Comma (赞：2)

**分类讨论**。

无非 $3$ 种情况分类。

1. 直接抵达的情况：

满足条件 $\left| x-y \right|=0\pmod d$。

2. 从最前面翻过去：

满足条件 $y-1=0\pmod d$。

3. 从最后面翻过去：

满足条件 $n-y=0\pmod d$。

$3$ 种取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
        int x,y,d,ans=114514,n;
        cin>>n>>x>>y>>d;
        if(abs(x-y)%d==0)
            ans=min(ans,abs(x-y)/d);
        if((y-1)%d==0)
            ans=min(ans,(x-1+d-1)/d+(y-1)/d);
        if((n-y)%d==0)
            ans=min(ans,(n-x+d-1)/d+(n-y)/d);
        if(ans==114514)ans=-1;
        cout<<ans<<endl;
	}
}
```

---

## 作者：reclusive (赞：2)

# 题目大意：

题目其实还是简单易懂的，

就是说有一本书，然后你可以每次翻 $d$ 页，

不过你不可以翻出书外，也就是你最多只能翻到第 $1$ 页或者第 $n$ 页。

然后问你最少要翻多少次才能翻到第 $y$ 页。

# 思路分析：

一开始我的思路是直接看 $(y-x)$ $\bmod$ $d$ 等不等于 $0$，

等于 $0$ 就输出 $(y-x)$ $/$ $d$ 的值，否则输出 $-1$。

不过我后面又看了一遍题目，可以翻到第 $1$ 页或者第 $n$ 页。

那么我们的翻页方法变成了三种：

$1.$ 从 $x$ 翻到 $y$。

这里要注意一下，

题目里没有说 $x$ 一定是大于 $y$ 的，

所以在算 $(y-x)$ 的时候必须要加上 $abs$。

```cpp
minn=min(minn,abs(y-x)/d);
```

$2.$ 先从 $x$ 翻到第 $1$ 页，再从第 $1$ 页翻到 $y$。

这里也要注意，

如果 $(x-1)$ 并不能整除 $d$，

那我们就会少翻一次。

所以我们得先将 $(x-1)$ 转换成 $double$ 类型，

然后除以 $d$ 后再向上取整一下就可以解决问题。

```cpp
minn=min(minn,ceil(double(x-1)/d*1.0)+(y-1)/d);
```

$3.$ 先从 $x$ 翻到第 $n$ 页，再从第 $n$ 页翻到 $y$。

这里要注意的点和第 $2$ 个点相同，请自行体会。

```cpp
minn=min(minn,ceil(double(n-x)/d*1.0)+(n-y)/d);
```

然后我们翻完一次后，就要做标记，

来表示当前询问时可以完成的，

然后最后看看标记是不是 $true$，

是的话就输出以上方式的最小值。

否则输出 $-1$。

# AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
    bool flag=false;int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if (ch=='-')flag=true;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return flag?-x:x;
}//快读优化（可以删去） 
int main()
{
	int t;t=read();//输入 
	for(int i=1;i<=t;i++)
	{
		int n,x,y,d,minn=2147483647,bk=0;
		n=read();x=read();y=read();d=read();//输入 
		if((y-x)%d==0){minn=min(minn,abs(y-x)/d);bk=1;}//从x翻到y 
		int ans;
		ans=0;
		ans+=ceil(double(x-1)/d*1.0);
		if((y-1)%d==0){minn=min(minn,ans+(y-1)/d);bk=1;}//先从x翻到第1页，再从第1页翻到y 
		ans=0;
		ans+=ceil(double(n-x)/d*1.0);
		if((n-y)%d==0){minn=min(minn,ans+(n-y)/d);bk=1;}//先从x翻到第n页，再从第n页翻到y
		if(bk==1)printf("%d\n",minn);
		else printf("-1\n");//输出 
	}
	return 0;//完结撒花！ 
} 
```


---

## 作者：DengDuck (赞：1)

不得不说，这道题真的很好玩。

注意到一个性质：
- 两页之间不一定可以直接到达。
- 任意页数都可以翻到第 $1$ 页 和第 $n$ 页。

那么，我们显然有三种方案：

- 直接从 $x$ 到 $y$ ，显然需要满足 $|x-y|=0\pmod d$ 。
- 从 $x$ 到 $1$ 再到 $y$，需要满足 $y-1=0\pmod d$ 。
- 从 $x$ 到 $n$ 再到 $y$，需要满足 $n-y=0\pmod d$ 。

在方案合法时，算出方案所需的次数，最终找到最小方案，否则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,y,d,ans;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>x>>y>>d;
        ans=1e9;
        if(abs(x-y)%d==0)
        {
            cout<<abs(x-y)/d<<endl;
            continue;
        }
        if((n-y)%d==0)
        {
            ans=min(ans,(n-x+d-1)/d+(n-y)/d);
        }
        if((y-1)%d==0)
        {
            ans=min(ans,(x-1+d-1)/d+(y-1)/d);
        }
        if(ans==1000000000)
        {
            cout<<-1<<endl;
            continue;
        }
        cout<<ans<<endl;
    }
}
```

以上代码运用了一个技巧， `(n-x+d-1)/d` 中的 `d-1` 是为了实现向上取整 。

---

## 作者：Eason_AC (赞：1)

## Advertisement
本文同步发布在[博客园](https://www.cnblogs.com/Eason-AC/p/solution-cf1082a.html)，欢迎打赏！
## Content
给定 $T$ 组数据，每组数据给出四个整数 $n,x,y,d$。小 V 有一本 $n$ 页的书，每次可以恰好翻 $d$ 页，求从第 $x$ 页恰好翻到第 $y$ 页的最少次数，或者报告不存在这样的方案。

**数据范围：$1\leqslant n,d\leqslant 10^9$，$1\leqslant x,y\leqslant n$，$1\leqslant t\leqslant 10^3$。**
## Solution
分类讨论题。

- 如果 $|x-y|\bmod d=0$，那么从第 $x$ 页直接可以翻到第 $y$ 页，那么 $\dfrac{|y-x|}{d}$ 可作为一个答案。
- 如果 $(y-1)\bmod d=0$，那么可以从第 $x$ 页先翻到第 $1$ 页，再翻到第 $y$ 页，那么 $\dfrac{x-1}{d}+\dfrac{y-1}{d}+[(x-1)\bmod d\neq 0]$ 可作为一个答案。 
- 如果 $(n-y)\bmod d=0$，那么可以从第 $x$ 页先翻到第 $n$ 页，再翻到第 $y$ 页，那么 $\dfrac{n-x}{d}+\dfrac{n-y}{d}+[(n-y)\bmod d\neq 0]$ 可作为一个答案。

如果三种情况都不符合就输出 `-1`，否则输出满足情况的答案中的较小值。
## Code
```cpp
int main() {
	MT {
		int n = Rint, x = Rint, y = Rint, d = Rint, ans = 0x3f3f3f3f;
		if(!(abs(y - x) % d)) ans = min(ans, abs(y - x) / d);
		if(!((y - 1) % d)) ans = min(ans, (x - 1) / d + (y - 1) / d + (bool)((x - 1) % d));
		if(!((n - y) % d)) ans = min(ans, (n - x) / d + (n - y) / d + (bool)((n - y) % d));
		println(ans == 0x3f3f3f3f ? -1 : ans);
	}
    return 0;
}
```

---

## 作者：little_sun (赞：1)

# 题解 CF1082A 【Vasya and Book】

## [安利博客](https://www.cnblogs.com/little-sun0331/p/10046308.html)

**史上最难A题，没有之一**

从题意可以看出，翻到目标页只有三种办法

* 先从$x$到$1$,再从$1$到$y$

* 先从$x$到$n$,再从$n$到$y$

* 直接从$x$到$y$

三种的必要条件分别是

* $(y-1)\mod d \equiv 0$

* $(n-y)\mod d \equiv 0$

* $|x-y|\mod d \equiv 0$

所以如果上面三种都不满足的话就输出$-1$

不然就取最小的输出

``` cpp
# include <bits/stdc++.h>

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, x, y, d;
        scanf("%d%d%d%d", &n, &x, &y, &d);
        int ans = 0x7f7f7f7f;
        if(abs(x - y) % d == 0)
            ans = abs(x - y) / d;
        if((y - 1) % d == 0)
            ans = std::min(ans, (x - 1) / d + bool((x - 1) % d) + (y - 1) / d);
        if ((n - y) % d == 0)
            ans = std::min(ans, (n - x) / d + bool((n - x) % d) + (n - y) / d);
        if(ans == 0x7f7f7f7f)
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```





---

## 作者：Dilute (赞：1)

## 分类讨论水题

首先我们根据题意，可以发现从$x$点走到$y$点，只有三种情况

```cpp
|_____|------->|_____|
    x        y
```
_x直接到y_

```cpp
|<----|        |_____|
|------------->|_____|
      x        y
```
_从x先到1号点再到y_

```cpp
|_____|------------->|
|_____|________|<----|
      x        y
```
_从x先到n号点再到y_

（这边画的是$x < y$的情况，$x > y$跟这个其实是差不多的，这里就不给出了）

那么我们只需要对三种情况分类讨论一下，取其中翻书次数最小的就可以了QwQ

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

int main(){
    for(int t = inp(); t >= 1; t--){
        int n = inp();
        int x = inp();
        int y = inp();
        int d = inp();
        int ans = INF;
        if(abs(y - x) % d == 0){ // 如果可以，第一种情况肯定是最优的
            ans = abs(y - x) / d;
        } else {
            if((y - 1) % d == 0) // 第二种情况
                ans = std::min(ans, ((x - 1) / d) + (y - 1) / d + 1);
            if((n - y) % d == 0)
                ans = std::min(ans, (n - x) / d + (n - y) / d + 1); // 第三种情况
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
}
```



---

## 作者：blsya23a2 (赞：0)

## 分析
这道题的翻书方法可以分为三种，规律很好找。

1. 当 $(y-1)\bmod d=0$ 时，可以从 $x$ 到 $1$ 再从 $1$ 到 $y$，翻书次数为 $\left\lceil\frac{x-1}{d}\right\rceil+\left\lceil\frac{y-1}{d}\right\rceil$。

1. 当 $(n-y)\bmod d=0$ 时，可以从 $x$ 到 $n$ 再从 $n$ 到 $y$，翻书次数为 $\left\lceil\frac{n-x}{d}\right\rceil+\left\lceil\frac{n-y}{d}\right\rceil$。
1. 当 $|x-y|\bmod d=0$ 时，可以从 $x$ 到 $y$，翻书次数为 $\left\lceil\frac{|x-y|}{d}\right\rceil$。

把所有可以的翻书方法所需的次数都存储在列表 $d$ 中。如果 $d$ 不是空列表，就输出 $\min(d)$，否则输出 $-1$。注意 $\min(d)$ 可能不是整数。
## 代码
```python
a = int(input())
for b in range(a):
    c = list(map(int,input().split()))
    d = []
    if (c[2]-1)%c[3] == 0:
        e = (c[1]-1)/c[3]
        if e%1 != 0:
            e = e//1+1
        f = (c[2]-1)/c[3]
        if f%1 != 0:
            f = f//1+1
        d.append(e+f)
    if (c[0]-c[2])%c[3] == 0:
        g = (c[0]-c[1])/c[3]
        if g%1 != 0:
            g = g//1+1
        h = (c[0]-c[2])/c[3]
        if h%1 != 0:
            h = h//1+1
        d.append(g+h)
    if abs(c[1]-c[2])%c[3] == 0:
        i = abs(c[1]-c[2])/c[3]
        if i%1 != 0:
            i = i//1+1
        d.append(i)
    if d != []:
        print(int(min(d)))
    else:
        print(-1)
```

---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1082A)

### [思路]

根据题意我们可以列举三种到达方式：

- 无需任何操作直接抵达指定页数需要满足的条件：$ |x-y|\bmod \space d =0 $。

- 从前面翻过去抵达指定页数需要满足的条件：$ (y-1)\bmod \space d =0 $。

- 从后面翻过去抵达指定页数需要满足的条件：$ (n-y)\bmod \space d =0 $。

最后对这些列举出来的方式进行取最小值即可。


------------

取最小值：$ \verb min(a,b); $

绝对值：$ \verb abs(n); $


------------
### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int T,n,x,y,d,mi=INT_MAX;
signed main()
{
	cin>>T;
	for(int i=1; i<=T; i++)
	{
		mi=INT_MAX;//初始化最大 
        	scanf("%lld%lld%lld%lld",&n,&x,&y,&d);
        	if( abs(x-y) %d == 0) mi=min(mi,abs(x-y)/d);
        	/*直接抵达指定页数方式*/ 
        	if( (y-1) %d == 0 ) mi=min(mi,(x-1+d-1)/d+(y-1)/d);
        	/*从前面翻过去抵达指定页数方式*/
        	if( (n-y) %d == 0) mi=min(mi,(n-x+d-1)/d+(n-y)/d);
        	/*从后面翻过去抵达指定页数方式*/
        	if( mi == INT_MAX )mi=-1;
        	printf("%lld\n",ans);
	}
	return 0;//好习惯 
}
```

---

## 作者：CyaNgw_DyG (赞：0)

## 题意：
一本书有 $n$ 页，要从第 $x$ 翻到第 $y$ 页，每次可以翻 $d$ 页，若页码不够了就翻到边缘（第 $1$ 页或者第 $n$ 页），无解输出 $-1$。

## 思路&代码:

显然有 $3$ 种答案的由来：
1. 直接从 $x$ 翻到 $y$。
2. 从 $x$ 翻到 $1$ 再翻到 $y$。
3. 从 $x$ 翻到 $n$ 再翻到 $y$。

对于上面每一种情况的必要条件分别为：

1. $d\mid{x-y}$
2. $d\mid{y-1}$  
3. $d\mid{n-y}$

如果都没有满足就是无解，否则取上面三种情况的最小值即可。

```
# include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
int t,n,x,y,d,minn,ans1,ans2;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>x>>y>>d;
        minn=ans1=ans2=inf;
        if(abs(x-y)%d==0)minn=abs(x-y)/d;
        if((y-1)%d==0){
        	ans1=(x-1)/d+(y-1)/d;
        	if((x-1)%d!=0)ans1++;
        }
        if((n-y)%d==0){
        	ans2=(n-x)/d+(n-y)/d;
        	if((n-x)%d!=0)ans2++;
        }
        minn=min(minn,min(ans1,ans2));
        if(minn==inf)cout<<-1<<"\n";
        else cout<<minn<<"\n";
    }
}
```


---

## 作者：ljk_Elaina (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int INF=2e9+10;

int read() {  //快读
	int xx=0,ww=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') ww=-ww;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		xx=10*xx+ch-48;
		ch=getchar();
	}
	return xx*ww;
}

int T;
int n,x,y,d;
int minn;

int main() {
	T=read();
	while(T--) {
		n=read();
		x=read();
		y=read();
		d=read(); //输入
		minn=INF; //最大值，无穷大
		if(abs(y-x)%d==0) minn=min(minn,abs(y-x)/d); //情况1，更新值
		if((y-1)%d==0||(n-y)%d==0) { //情况2
			if((y-1)%d==0) {
				int ans=(x-1)/d+1;
				ans+=(y-1)/d; //计算
				minn=min(ans,minn); //更新值
			}
			if((n-y)%d==0) {
				int ans=(n-x)/d+1;
				ans+=(n-y)/d; //计算
				minn=min(minn,ans); //更新值
			}
		}
		if(minn!=INF) printf("%d\n",minn); //输出
		else puts("-1");
	}
	return 0;
}
```
考虑两种情况：

1. 如果可以直接翻到不用反弹就记录
1. 如果不能，就看它是否到第一页或最后一页是否能整除 $d$，并分别记录比较。

最后，如果$minn$的值没变，就不能翻到，输出$-1$，否则输出$minn$。

---

## 作者：StudyingFather (赞：0)

我们要从 $ x $ 页到达 $ y $ 页，有3种方法：

1. 直接从 $ x $ 页前往 $ y $ 页。
2. 先从 $ x $ 页前往第 $ 1 $ 页，然后前往第 $ y $ 页。
3. 先从 $ x $ 页前往第 $ n $ 页，然后前往第 $ y $ 页。

我们只需判断这三种情况是否可行，并比较哪个更优即可。

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
 int t;
 scanf("%d",&t);
 while(t--)
 {
  int n,x,y,d,ans=1000000000;
  scanf("%d%d%d%d",&n,&x,&y,&d);
  if(abs(y-x)%d==0)ans=min(ans,abs(y-x)/d);
  if((y-1)%d==0)ans=min(ans,int(ceil((double)(x-1)/d)+ceil((double)(y-1)/d)));
  if((n-y)%d==0)ans=min(ans,int(ceil((double)(n-x)/d)+ceil((double)(n-y)/d)));
  if(ans==1000000000)puts("-1");
  else printf("%d\n",ans);
 }
 return 0;
}
```

---

## 作者：Li2021 (赞：0)

## CF1082A Vasya and Book 题解

### 题目大意

一本 $n$ 页的书，可以往前、往后翻 $d$ 页。问：从第 $x$ 页翻到第 $y$ 页需要翻几次。

### 思路

思路很简单，分三种情况讨论：

1. 直接从第 $x$ 页翻到 $y$ 页，条件是 $ \left|y-x\right| \bmod d = 0 $。

2. 从第 $x$ 页翻到第 $1$ 页，再从第 $1$ 页翻到第 $y$ 页，条件是 $(y - 1) \bmod d = 0$。

3. 从第 $x$ 页翻到第 $n$ 页，再从第 $n$ 页翻到第 $y$ 页，条件是 $(n - y) \bmod d = 0$。

若从 $x$ 页开始翻，用三种情况都翻不到第 $y$ 页的话，则无解，输出 $-1$。

### 代码

码风奇特，请谅解。

```cpp
/* problem: CF1082A  Vasya and Book 
 * date: 2023/3/10
 * author: Li2021
 */
#include <iostream>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;
int T,n,x,y,d;
int main(){
	cin>>T;
	while(T--){
		int ans=inf;
		cin>>n>>x>>y>>d;
		if(abs(y-x)%d==0)  ans=min(ans,abs(y-x)/d);  //第一种情况
		if((y-1)%d==0)  ans=min(ans,(y-1)/d+(x-1)/d+((x-1)%d?1:0));  //第二种情况
		if((n-y)%d==0)  ans=min(ans,(n-y)/d+(n-x)/d+((n-x)%d?1:0));  //第三种情况
		if(ans==inf)  cout<<-1<<endl;  //无解
		else  cout<<ans<<endl;
	}
	return 0;
}
```

---

