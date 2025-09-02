# [NWRRC 2016] Folding

## 题目描述

### 题目大意：

求一个 $W\times H $ 的矩形通过折叠变为一个 $w\times h$ 的矩形的最少折叠次数，其中每次折叠的折痕必须平行于矩形的一边。

------------

## 样例 #1

### 输入

```
2 7
2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 6
4 8
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 5
1 6
```

### 输出

```
-1
```

# 题解

## 作者：无名之雾 (赞：4)

# [NWRRC2016] Folding 题解

## 题意

给出一个 $W \times H$ 的矩形，问你经过多少次的折叠后才可以变成一个 $w \times h$ 的矩形。

## 思路

本题没有什么思维上的难点，只需按部就班的模拟不断将 $W$ 和 $H$ 除以 $2$
直到符合题意，输出操作次数即可。

## 坑点

1. 本题并没有保证 $W \ge w$，$H \ge h$。所以应在开头特判，如若 $W < w$，或 $H < h$ 直接输出 $-1$。

1. 如果你的操作过程是不断将 $w$ 和 $h$ 乘 $2$ 那么没事。但如果是将 $W$ 和 $H$ 不断除以 $2$ 逼近 $w$ 和 $h$，则需要开浮点类型。~~我是绝对不会告诉你我就是这样WA的。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int double //一定要开double！！
#define s(w,h) if(w>h)swap(w,h)
#define wh(x,y,cnt) while(x>y)x/=2,cnt++;
signed main(){
    int W,H,w,h;
    cin>>W>>H>>w>>h;
    s(W,H);s(w,h); //更换长宽位置
    if(W<w||H<h)cout<<-1; //特判
    else{
       int a=W,b=H,cnt1=0,cnt2=0;
	    wh(a,w,cnt1);wh(b,h,cnt2);
	    if(W<h)cout<<cnt1+cnt2;
	    else{
	        int cnt3=0,cnt4=0;
	        swap(w,h);wh(W,w,cnt3);wh(H,h,cnt4);
	        cout<<min(cnt1+cnt2,cnt3+cnt4);
	    }
    }
    return 0;
}
```

---

## 作者：Scrutiny (赞：2)

不妨 $W\le H,w\le h.$

容易知道，一个有一条边长为 $a$ 的矩形，沿这条边折叠后，边长最小值为 $\dfrac{a}{2}.$

如果 $W< w$ 或者 $H<h$，那么无法完成折叠要求，输出 `-1`.

否则，不断将 $W$ 和 $H$ 不断除以 $2$，直到 $W\le w$ **且** $H\le h$，统计除的次数.

再互换 $W$ 和 $H$，再次执行上述指令，两次除的次数中小的那个值即为所求答案.

特别提醒：按笔者题解的做法，$W,H,w,h$ 不能开整数类型.

**CODE:**

```cpp
#include<bits/stdc++.h>
using namespace std;
long double W,H,w,h,a,b;
int cnt1,cnt2,cnt3,cnt4;
int main(){
	cin>>W>>H>>w>>h;
	if(W>H){
		swap(W,H);
	}
	if(w>h){
		swap(w,h);
	}
	if(W<w||H<h){
		printf("-1");
		return 0;
	}
    a=W,b=H;
	while(a>w){
	    a/=2;
	    ++cnt1;
	}
	while(b>h){
	    b/=2;
	    ++cnt2;
	}
    if(W<h){
        cout<<cnt1+cnt2;
        return 0;
    }
    swap(w,h);
	while(W>w){
	    W/=2;
	    ++cnt3;
	}
	while(H>h){
	    H/=2;
	    ++cnt4;
	}
	cout<<min(cnt1+cnt2,cnt3+cnt4);
	return 0;
}
```


---

## 作者：Liuliuliuliuliu (赞：1)

## [P7036 【NWRRC2016】 Folding](https://www.luogu.com.cn/problem/P7036)

## 一、题目大意
求一个将 $W \times H$ 这么大的矩形折叠成 $w \times h$ 的最少折叠次数。其中每次折叠必须平行于矩形的一边。

$1 \le W,H,w,h \le 10^9$。

## 二、解题思路
 首先看题目中没有保证 $W \le w$ 或者 $H \le h$，所以应先判断 $W$ 是否比 $w$ 小（因为一张纸**没有办法**越折叠越大）这里我加了个特判。
```cpp
int tp(){//特判  
	if(x>a||y>b) return 1;//如果目标长度比初始长度要大，那么返回1；
	if(x==a&&y==b) return 2; //如果目标长度和初始长度相等，那么直接返回2；
	return 0;
}
```
这里要注意，我们应该用**较长**的初始边比较**较长**的目标边（即应当让 $\max(W,H)$ 与 $\max(w,h)$ 相比较），所以读入后要紧接着两个判断，让长的边都到 $W$ 和 $w$ 上，代码如下。
```cpp
	if(W<H) swap(W,H);
	if(w<h) swap(w,h);
```

然后我们接着想，要是折叠次数最小，就需要让每次折叠尽可能多的面积。又因为一次折叠最多折叠一半的面积，所以只要还没有到目标长度，每次让 $W$，$H$ 都对半折叠就好。

但由于做除法每次都自动向下取整，所以我们改用用目标向初始值做乘法的方式，避免这一情况的发生。即 `w*=2;h*=2`。

## 三、完整代码如下
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
#define int long long
inline int Read(){
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-48;c=getchar();}
    return x*f;
}
inline void Write(int x)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) Write(x/10);
	putchar(x%10+'0');
}

int a,b,x,y;
int ans=-1;

int tp(){
	if(x>a||y>b) return 1;
	if(x==a&&y==b) return 2; 
	return 0;
}

signed main(){
	a=Read();b=Read();
	x=Read();y=Read();
  	//a=W,b=H,x=w,y=h;
	if(a<b) swap(a,b);
	if(x<y) swap(x,y);
	if(tp()==1){
		Write(ans);
		return 0;
	}
	else if(tp()==2){
		Write(0);
		return 0;
	}
	ans=0;
	while(1){
		if(a<=x&&b<=y) break;
		if(y<b){
			y*=2;
		}
		else x*=2;
		if(x<y) swap(x,y);
		ans++;
	}	
	Write(ans);
	return 0;
}
```

---

## 作者：Linge_Zzzz (赞：1)

cpp


------------
### 1. 难度评定  
这道题主要考的是模拟，难度应在 [普及-] 。 

### 2. 题目描述  
求一个 $ W \times H $ 的矩形通过折叠变为一个 $ w \times h $ 的矩形的最少折叠次数，其中每次折叠的折痕必须平行于矩形的一边。

### 3. 题解

+  我们都知道，长为 $ x $ 的纸折叠后最短长度为 $ x/2 $，所以一张长为 $ x/2 $ 的纸展开后最大长度为 $ x $ 。

+  我们不妨想象一张已经叠好的 $ w \times h $ 的纸，通过 $ ans $ 次打开可获得一张 $ W \times H $ 的纸。

+  既然纸展开的最大长度只要超过目标长度就一定能展开为目标长度，我们就可以开始模拟了。 

### 4. 模拟过程
![](https://cdn.luogu.com.cn/upload/image_hosting/r8w8qs53.png)

**注意！在任何时刻下必须保证 $ W \ge H $ ， $w \ge h $ ！！！**

### 5. 代码实现 （好好看注释）
```cpp
/*
//P7036 [NWRRC2016]Folding 代码 
*/ 
#include <bits/stdc++.h>
using namespace std;
int W,H,w,h,ans=0;
int main()
{
	cin>>W>>H>>w>>h;
	if(W<H)swap(W,H);     //这里是保证 W > H 且 w > h 
	if(w<h)swap(w,h);
	if(W<w||H<h)          //特判，当 W < w 或 H < h 时不可能 
	{
		cout<<"-1\n";
		return 0;
	}
	while(w<W||h<H)       //只要有没满足条件的边，就要继续展开 
	{
		if(h<H)h*=2;      //展开过程 
		else w*=2;
		if(w<h)swap(w,h); //维持 w > h 
		ans++;
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：Doubeecat (赞：1)

> F.Folding
> 
> 求一个 $W \times H$ 的矩形通过折叠变为一个 $w\times h$ 的矩形的最少折叠次数，其中每次折叠的折痕必须平行于矩形的一边。
> 
> $1\le W,H,w,h\le10^9$

~~场上队友写挂好几发被我撵下来了~~

首先这个题比较不喜欢的是它并没有保证长边和短边（队友就是在这里挂了好多发）所以先把短边和长边算出来，后文中提到的 $W,H,w,h$ 均保证 $W\leq H,w \leq h$，然后来讨论情况。

首先讨论无解的情况：显然，如果我们的最短边比目标最短边短，或者最长边比目标最长边短就无解了。你折纸总不可能越折越长对吧。
 
接着考虑有两种折叠情况：将 $W$ 变成 $w$，$H$ 变成 $h$。或者将 $W$ 变成 $h$，$H$ 变成 $w$.

所以代码就很好写了，因为一次对折变短一半，我们不断用短边乘二靠近长边，统计次数即可。

Code:

```cpp
int solve(int y,int x) {
    if (x == y) return 0;
    int cnt = 0;
    while (1) {
        x *= 2;++cnt;
        if (x >= y) return cnt;
    }
}

signed main() {
    //FO(folding)
	int ans = 0;
    read(a,b,c,d);
    l1 = min(a,b),h1 = max(a,b),l2 = min(c,d),h2 = max(c,d);
    if (l2 > l1 || h2 > h1) {
        printf("-1");return 0;
    }
    ans = min(solve(l1,l2) + solve(h1,h2),solve(l1,h2) + solve(h1,l2));
    printf("%d",ans);
	return 0;
}
```

---

## 作者：Struggle_ong (赞：1)

### [P7036 [NWRRC2016]Folding ](https://www.luogu.com.cn/problem/P7036)

### 题目大意：

给定一个矩形 $ W \times H $，求最少经过几次折叠，能形成一个 $ w \times h $ 的矩形，注意，每次折叠的折痕必须平行于矩形的一边。

### Solution:

首先可以特判不符合的，即 $ W < w $ 或 $ H < h $ 时。然后特判折叠次数为 $ 0 $ 的。对于剩下的矩形，我们可以逆向思维，先给定一个折叠好的小矩形，边长每次乘 $ 2 $，通过 $ ans $ 次后可以展开成大矩形。$ ans $ 即为所求。

#### 注意：

在计算时要随时判断长和宽并随时调整。

#### AC代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;
inline int read()
{
	int s=0,w=-1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*w;
}
const int N=1e6+10;
int main()
{
	int W=read(),H=read(),w=read(),h=read(),ans=0;
	if(W<H)swap(W,H);
	if(w<h)swap(w,h);
	if(W<w||H<h){cout<<-1;return 0;}
	if(W==w&&H==h){cout<<0;return 0;}
	while(H>h||W>w)
	{
		if(H>h)h*=2;
		else w*=2;
		if(h>w)swap(h,w);
		ans++;
	}
	cout<<ans;
	return 0;
}
```
为防抄袭，代码有误。

请不要~~三键AC~~抄袭。

---

## 作者：no2lxs (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P7036)
------------
这道题整体来说还是比较简单的，但是要注意一个坑点：要在算的时候判断长和宽并随时调整，且一开始也需要判断，不然会直接输出负一（见样例二）。

还有一个点，在算时尽量用小矩形边长乘二而不是大矩形边除以二，因为会自动取整。

### code
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>//sort函数库 
#include<cstdlib>
#include<cstring>
#include<bits/stdc++.h>
#include<map>
#define gets(S) fgets(S,sizeof(S),stdin)
#pragma optimize GCC(2)
using namespace std;
int w,h,w1,h1;
int main()
{
	cin>>w>>h>>w1>>h1;
	int sum=0;
	if(w<h)swap(w,h);
	if(w1<h1)swap(w1,h1);//判断长宽
	if(w<w1||h<h1)
	{
		cout<<-1;//判断是否能得到
		return 0;
	}
	else if(w==w1&&h==h1)
	{
		cout<<0;
		return 0;//直接判断
	}
		while(h>h1||w>w1)
		{
			if(h1<h)
			{
				h1*=2;
			}
			else
			{
				w1*=2;
			}
			if(h1>w1)
			{
				swap(h1,w1);//再次判断长和宽
			}
			sum++;
		}
	cout<<sum;
		return 0;
} 
```



---

