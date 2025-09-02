# The Race

## 题目描述

Every year a race takes place on the motorway between cities A and B. This year Vanya decided to take part in the race and drive his own car that has been around and bears its own noble name — The Huff-puffer.

So, Vasya leaves city A on the Huff-puffer, besides, at the very beginning he fills the petrol tank with $ α $ liters of petrol ( $ α>=10 $ is Vanya's favorite number, it is not necessarily integer). Petrol stations are located on the motorway at an interval of $ 100 $ kilometers, i.e. the first station is located $ 100 $ kilometers away from the city A, the second one is $ 200 $ kilometers away from the city A, the third one is $ 300 $ kilometers away from the city A and so on. The Huff-puffer spends $ 10 $ liters of petrol every $ 100 $ kilometers.

Vanya checks the petrol tank every time he passes by a petrol station. If the petrol left in the tank is not enough to get to the next station, Vanya fills the tank with $ α $ liters of petrol. Otherwise, he doesn't stop at the station and drives on.

For example, if $ α=43.21 $ , then the car will be fuelled up for the first time at the station number $ 4 $ , when there'll be $ 3.21 $ petrol liters left. After the fuelling up the car will have $ 46.42 $ liters. Then Vanya stops at the station number $ 8 $ and ends up with $ 6.42+43.21=49.63 $ liters. The next stop is at the station number $ 12 $ , $ 9.63+43.21=52.84 $ . The next stop is at the station number $ 17 $ and so on.

You won't believe this but the Huff-puffer has been leading in the race! Perhaps it is due to unexpected snow. Perhaps it is due to video cameras that have been installed along the motorway which register speed limit breaking. Perhaps it is due to the fact that Vanya threatened to junk the Huff-puffer unless the car wins. Whatever the reason is, the Huff-puffer is leading, and jealous people together with other contestants wrack their brains trying to think of a way to stop that outrage.

One way to do this is to mine the next petrol station where Vanya will stop. Your task is to calculate at which station this will happen and warn Vanya. You don't know the $ α $ number, however, you are given the succession of the numbers of the stations where Vanya has stopped. Find the number of the station where the next stop will be.

## 说明/提示

In the second example the answer is not unique. For example, if $ α=10 $ , we'll have such a sequence as $ 1 $ , $ 2 $ , $ 3 $ , and if $ α=14 $ , the sequence will be $ 1 $ , $ 2 $ , $ 4 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
unique
5
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
not unique
```

# 题解

## 作者：Creroity (赞：10)

~~啊，交了7遍总算过了……~~

说实话这题的思路~~很简单~~，稍微画一下图其实就可以想到解法，但问题是坑点真的多……改了我半天。

### 主要思路：

我们拿样例一举个例子：

先画一下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m4gzmlr6.png)

然后就是我们的主要思路了。

因为题目中说 $x \geqslant 10$ 所以我们可以假定一个 Minx 和 Maxx 来存储目前算出的 x 一次性所能走的最少的站点数和最多站点数。

按照此方法，我们只需要在最后判断 Minx 和 Maxx 是否相等即可。

自行绘图（或者说手动假设一下）可以得出从 A 点至一号站点时剩余的油量是初始的 $x - 10$ 

![](https://cdn.luogu.com.cn/upload/image_hosting/f8oery7o.png)

则可以得出此时 x 的最小值为 1 ，即一站。因为需要取最小值，那我们就假设每次的 x 都不会有多出来的小数。所以此时 $Minx = a \div i$ 其中 a 为此时的加油站的站点位置， i 为此时的加油次数。

而最大值同理，只是我们假设它会有多余的小数部分，因为多余的小数部分不可能叠加起来大于一，所以我们假设多余的小数部分叠加刚好为极限值 1 。则 $Maxx = (a + 1) \div i$ 。

之后的两次操作同理，但是记得每次都要对求出来的最大与最小值进行比较以确定此点为极值。

![](https://cdn.luogu.com.cn/upload/image_hosting/e02ruekn.png)

最终计算出 Maxx 和 Minx ，将其向下取整，若最大值向下取整后等于本身，那么就将其减一。（因为本来就是多出来的，如果不等于的话这个多出来的就相当于自动减掉了）

再接着就只剩下判断最大值与最小值是否相等了，若不相等则说明有多个 x ，否则只有一个解。

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
double Minx,Maxx;
int main(){
	cin>>n>>a;
	Minx=a;
	Maxx=a+1;
	for(int i=2;i<=n;i++){
		cin>>a;
		Minx=max(Minx,a*1.0/i);
		Maxx=min(Maxx,(a+1)*1.0/i);
	}
	Minx*=n+1,Maxx*=n+1;
	int Min=floor(Minx);
	int Max=floor(Maxx);
	if(Maxx==floor(Maxx))Max--;
	if(Min!=Max){
		cout<<"not unique";
		return 0;
	}
	cout<<"unique"<<endl;
	cout<<Min;
	return 0;
}
```
###### ~~第一次懒得贴注释……~~

求个赞吧！

---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF48C)

# 思路
这道题其实就是一个不断找 $ x $ 上下边界的过程。我们不断输入当前加油的站点，不断缩小 $ x $ 的最小和最大值，最后再判断其是否其是否有唯一解。

### 为了让各位读者更好地理解思路，我们来分析一波样例。
对于样例一，Vanya 第一次在一号加油站加油，我们明显可得 $ 0\le x-10<10 $，即 $ 10\le x<20 $。  
Vanya 第二次在二号加油站加油，我们明显可得 $ 0\le 2x-20<10 $，即 $ 10\le x<15 $。  
Vanya 第一次在一号加油站加油，我们明显可得 $ 0\le 3x-40<10 $，即 $ \frac{40}{3} \le x<\frac{50}{3} $。

综上所述，我们不难发现，$ \frac{40}{3}\le x<15 $。

接下来，我们就应该求 Vanya 下一次加油的地点，所以我们要求 $ 4x $ 的范围，即 $ \frac{160}{3}\le 4x<60 $。而根据 $ 4x $ 的范围可以发现，Vanya 下一次将在五号加油站加油。

所以我们可以用一个 $ maxxx $ 和 $ minnn $ 变量来记录 $ x $ 的最大值和最小值，一边输入加油站编号一边更新两个变量的值。

最后我们再判断一下，如果 $ maxxx/10 $ 等于 $ minnn/10 $，就有唯一解，输出 unique 和 $ maxxx/10 $，否则无唯一解，输出 not unique。

**特别注意**：如果 $ maxxx $ 等于 $ \lfloor maxxx\rfloor $，则要将 $ maxxx $ **减一**。（因为不等式右边取的是小于号）

### 若有疑问，请自行移步代码注释。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,t,minn,maxx;//minn和maxx用于记录最终答案 
	double minnn=0,maxxx=1e9;//用于计算最小和最大值 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		minnn=max(minnn,t*10.0/i);
		maxxx=min(maxxx,(t*10.0+10)/i);//边输入边计算 
	}
	maxx=floor(maxxx*(n+1));
	minn=floor(minnn*(n+1));
	if (maxx==maxxx*(n+1))
		maxx--;//一定要加上此特判 
	if (minn/10!=maxx/10)//判断是否有唯一解 
		cout<<"not unique"<<endl;
	else
		cout<<"unique"<<endl<<maxx/10<<endl;
}
```

---

## 作者：灰鹤在此 (赞：3)

我们来分析一波题目，简化以下就是求动态一元一次不等式的最大解和最小解。我们拿样例 $1$ 来分析一波：可得 Vanya 在第 $1$、$2$、$4$ 号加油站停靠加油，而且加了 $\alpha$ 升油。

我们先假设 Vanya 只在第 $1$ 号加油站加油，可以得出一个不等式：$0\le\alpha-10<10$ 即 $10\le\alpha<20$。

然后我们再假设 Vanya 又在 $2$ 号加油站加了油，可以又得出一个不等式： $0\le2\alpha-20<10$ 化简得：$1\le\alpha<15$。

最后我们再假设 Vanya 在 $4$ 号加油站加了油，又可以得出一个不等式：$0\le3\alpha-40<10$ 化简得 $\dfrac{40}{3}\le\alpha<\dfrac{50}{3}$。

然后我们该干什么？那就是分析 $4\alpha$ 的范围，因为我们的任务是计算 Vanya 他下一个要停靠的加油站。通过以上 $3$ 个不等式，我们可以确定：$\dfrac{40}{3}\le\alpha<15$，所以 $\dfrac{160}{3}\le4\alpha<60$，$\dfrac{160}{3}≈53.3333$，所以我们可以确定 Vanya 将会在第 $5$ 个加油站停靠。

分析解题过程，我们发现：由于每一个加油站间隔为 $10$，我们在列不等式时都是以 $10$ 的倍数为常量，但是最后我们计算下一个加油站的编号时又要将得出的不等式两端的值除以 $10$。因此，我们可以直接将 $\alpha=10\alpha$（迷惑的操作），最终得出的（$\alpha\times$ 下一次加油的总次数 ）就是 Vanya 下一个会停靠的加油站。

我们可以用 $maxn$ 来记录不等式右端的值（注意是小于而不是小于等于），用 $minn$ 来记录不等式左端的值（是小于等于而不是小于）。所以在编号输入的同时，直接计算 $\alpha$ 的两个极值 $maxn$（$maxn=$（编号 $+1$）$\div$加油的次数）和 $minn$（$minn=$ 编号 $\div$ 加油的次数）。

最后只需要判断 $maxn$ 是否等于 $minn$，若等于，则可以确定他下一个停靠的加油站就是 $minn$ 向下取整的编号。

最后一个坑点：如果 $maxn==maxn$ 向下取整的值，那么 $maxn$ 是不能取的！因为在前文曾经提到过，不等式的右端是小于号！所以我们需要将 $maxn$ 减去 $1$ 与 $minn$ 进行大小比较。

下面呈上 $AC$ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double minn,maxn,a;
int main(){
	scanf("%d%lf",&n,&a);
	int i;
	minn=a;
	maxn=a+1;
	for(i=2;i<=n;i++){
		scanf("%lf",&a);
		minn=max(minn,a/i);
		maxn=min(maxn,(a+1)/i);
	}
	minn*=n+1;
	maxn*=n+1;
	int in=floor(minn),ax=floor(maxn);//floor(x)向下取整的STL函数
	if(maxn==ax){
		ax--;
	}
	if(in!=ax){
		printf("not unique");
	}else{
		printf("unique\n%d",in);
	}
	return 0;
}
```


---

## 作者：L__A (赞：3)

不妨设β=α/10，已加油的站点为a1,a2,a3...

同时设|x|为x的整数部分（小数向下取整） 

依题意可知10i<=iβ<10i+10， 

等价于①a1=|β|,a2=|2β|,a3=|3β|..an=|nβ|,

那么我们要求的下一个加油站点a(n+1)=|(n+1)β|。 

①式等价于②ai<=iβ<ai+1(1<=i<=n)。

又可设要求的可能的下一个加油站为X，

则在②式中的左侧找到β最大的值MI，右侧找到β最小的值MX，

又设l=|(n+1)MI|,r=|(n+1)MX|,则l<=X<=r，

注意当r为整数时，右侧不可取等，因此时右侧不满足②式的取等条件 

此时若l==r则X有唯一确定值X=l=r，若l!=r，则X值不唯一

附代码：
```cpp
#include <cstdio>
#include <cmath>

using namespace std;

#define mx(x,y) (x>y ? x : y)
#define mi(x,y) (x<y ? x : y)

int n,t,NE,l,r;
double MI,MX;

void re(int &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}

int main()
{
	re(n);
	re(t);
	MI=t; MX=t+1;
	for(int i=2;i<=n;i++)
	{
		re(t);
		MI=mx(1.0*t/i,MI);
		MX=mi(1.0*(t+1)/i,MX);
	}
	MI*=n+1; MX*=n+1;
	l=(int)floor(MI);
	r=(int)floor(MX);
	if(MX==floor(MX)) r--;
	if(l!=r) printf("not unique");
	else printf("unique\n%d",l);
	return 0;
}
```

---

## 作者：CJ_LIU_XC (赞：2)

思路其实挺简单的，可以简单的画个图（~~灵魂画手就不展现了~~）。

其实可以对每一个进行枚举，我们可以像左和向右依次寻找 $MAX$ 和 $MIN$。

这个时候我们直接在读入 $n$ 个数时直接进行处理，分别处理出 $MAX$ 和 $MIN$即可。

最后，万众瞩目的AC code：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
typedef long long ll;
using namespace std;

int n,t,NE,l,r;
double MIN,MAX;

int read()
{
    int ans = 0;
    char ch = getchar();
    while (!isdigit(ch) && ch != '-') ch = getchar();
    bool sign = false;
    if (ch == '-') sign = true, ch = getchar();
    while (ch >= '0' && ch <= '9') ans = ans * 10 + (ch - '0'), ch = getchar();
    return (sign == true ? -ans : ans);
}

int main()
{
	n = read(), t = read(); 
	MIN = t, MAX = t + 1;
	for (int i = 2; i <= n; i++)
	{
		t = read();
		MIN = max(1.0 * t / i, MIN);
		MAX = min(1.0 * (t + 1) / i, MAX);
	}
	MIN *= n + 1, MAX *= n + 1;
	l = (int)floor(MIN);
	r = (int)floor(MAX);
	if (MAX == floor(MAX)) r--;
	if(l != r) printf("not unique\n");
	else printf("unique\n%d\n",l);
	return 0;
}
```


---

## 作者：_HMZ_ (赞：1)

暴力出奇迹，打表过省一。

## 解题思路：

各位大佬全是数学推导啊……作为一个蒟蒻我表示不服气。

既然数学是不会了，那么有没有暴力算法呢？

肯定是有的，~~毕竟万物皆可暴力~~很显然，我们可以确定一个上下界。

为什么呢？当你走到第一个加油站的时候油箱里剩余的必须小于 $10$。

不然你就不用在这个加油站加油了，可以直接走到下一个。

既然范围只有 $10$，就可以暴力枚举一次加的油，这里注意精度不能太大，不然会超时。

## AC代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,a[100005],ans,cnt;
double now;
void check()//已经知道一次加多少油了，就可以直接模拟了。
{
	double oil=now;
	for(int i=1;i<=n;i++)
	{
		oil-=double((a[i]-a[i-1])*10.0);
		if(oil>=10.0 || oil<0.0)
			return;
		oil+=now;
	}
	if(ans==0 || ans==(int(oil)/10+a[n]))
		ans=int(oil)/10+a[n];
	else//出现多个答案。
	{
		cout<<"not unique";
		exit(0);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(now=(a[1]-a[0])*10.0;(double)now < (double)(a[1]-a[0])*10.0+10.0; now+=0.00001)//暴力出奇迹
		check();
	cout<<"unique"<<endl<<ans;
	return 0;
}
```

~~好耶！喜提最劣解！~~

---

## 作者：BADFIVE (赞：1)

**题意：** 给定 $n$ 个加油站，一辆车由 $A$ 点跑到 $B$ 点，每个 $100m$ 有一个加油站，每开 $100m$ 需要 $10$ 升油。在每个车站会检查一下油量，若车子若开不到下一个加油站则加 $x$ 升油。  
**思路：** 开始有 $x$ 升油下面给出加油的记录。问下一次加油在哪一站。若答案唯一输出具体哪站。油箱容量无限。每次都要对求出来的 $MAX$ 与 $MIN$ 进行比较以确定极值。   
$codes$:   
```cpp
double now = x;
	double siz = 0;
	for(ll i = 1; i <= n; i++)
	{		
		siz += floor(now/gg);
		now -= floor(now/gg)*gg;
		if(siz != p[i]){
			double cha = (siz - p[i])*10.0 - (10.0-now-eps);
			now = 10.0 - eps;
			x -= cha / i;
		}
		siz = p[i];
		now += x;
	}
	return now;
```

---

## 作者：伟大的王夫子 (赞：1)

我采取一种非常特殊的计算上下界的办法。我们每经过一个加油站，就先看看他有没有加油，根据有与没有，列出不等式的系数进行求解。

加设现在用了$b$油，加了$a$次油，那么如果加油了，那么不等式就是
$a\alpha+b - 10 <0$。

否则便是$a\alpha + b -10>=0$。
	
  其余的都一样。
    
 最后我们要找的位置是第$n+1$个得满足$a_{n+1} \times 10 \le \alpha(n+1)<(a_{n+ 1}+ 1)\times 10$的位置。
 

 由$\alpha$的范围和这个数为整数可知$l(n+1)\le a_{n + 1} \le r(n+1)$。
 
 但是都要向下取整。
 
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
double a_val = 1.0, b_val;
int n, a[1010];
bool v[1000010];
double l = -1e9, r = 1e9;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i), v[a[i]] = 1;
	for (register int i = 1; i <= a[n]; ++i) {
		b_val -= 10;
		//printf("%lf %lf\n", a_val, b_val);
		if (v[i] ) r = min(r, -(b_val - 10.0) / a_val), ++a_val;
		else l = max(l, -(b_val - 10.0) / a_val);
		
	}
	//cout << l << ' ' << r << endl;
	l /= 10, r /= 10;
	l *= (n + 1), r *= (n + 1);
	l = floor(l), r = floor(r) == r ? r - 1 : floor(r); 
	
	
	if (l == r) {
		puts("unique");
		printf("%.0lf", l);
	} else puts("not unique");
} 
```
不能想当然认为$\alpha$为整数。题中$\alpha$的值较难求出，但可以准确求出车站的值。

---

## 作者：yhx0322 (赞：0)

## 题目简述
现有 $n$ 个已经加过油的加油站，如果当前剩余油量 $< 10$ 升，则会加 $x$ 升的油。

初始状态下，有 $x$ 升油。每个加油站之间的距离为 $100$ 米，耗油量为 $10$ 升。

## 思路
首先，从左向右求出能到达的编号最小的车站，记为 $mi$ ，然后在从右向左求出能到的的编号最大的车站，记为 $ma$ 。

#### 初始化：

`mi = a[1];ma = a[1] + 1;`

#### 向下取整
`Min = floor(mi);
Max = floor(ma);`

#### 注意特判!!!
`if(ma == Max) Max--;`

## 代码
```c++
#include <bits/stdc++.h>


using namespace std;


const int N = 1e3 + 10;

int n;
int a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	double mi = a[1], ma = a[1] + 1;
	for(int i = 2; i <= n; i++) {
		mi = max(mi, a[i] * 1.0 / i);
		ma = min(ma, (a[i] + 1) * 1.0 / i);
	}
	mi *= (n + 1), ma *= (n + 1);
	int Min = int(mi), Max = int(ma);
	if (ma == Max) Max--;
	if (Max != Min) {
		printf("not unique");
		return 0;
	}
	printf("unique\n%d",Max);
	return 0;
}


```

---

## 作者：ttwyzz (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF48C)

### 题目大意

给 $n$ 个已经加过油的加油站，加油的条件是开不到下一个加油站就加  $x$ 升的油，每个加油站等距 $100$ 米，耗油 $10$ 升，初始油量为 $x$ 升。

### Solution

- 求出能到达的最小车站 $\,minx\,$。
- 求出能到达的最大车站 $\,maxx\,$。

如何处理这个过程呢？



------------

```
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	double minx = a[1];
	double maxx = a[1] + 1;
	for(int i = 2; i <= n; ++i)
	{
		minx = max(minx,a[i]*1.0/i);
		maxx = min(maxx,(a[i]+1)*1.0/i);
	}
	minx = minx * (n+1);
	maxx = maxx * (n+1);

```


------------

大概就是这样，$minx$ 和 $maxx$ 初始值直接设定为$\,a[1]$ 和 $\,a[1] + 1$ ，然后直接扫一遍，求出最大基数，再处理小数点的问题。



------------

```
	int Min = floor(minx);
	int Max = floor(maxx);
	if(maxx == Max) Max--;
```


------------

如果就是它本身，那就减 $1$，因为我们开始的初始值。

最后处理 $Min$ 和 $Max$ 是否相等就好了。


### Code


------------
```
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 20;

int n;
int a[maxn];

int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	double minx = a[1];
	double maxx = a[1] + 1;
	for(int i = 2; i <= n; ++i)
	{
		minx = max(minx,a[i]*1.0/i);
		maxx = min(maxx,(a[i]+1)*1.0/i);
	}
	minx = minx * (n+1);
	maxx = maxx * (n+1);
	int Min = floor(minx);
	int Max = floor(maxx);
	if(maxx == Max) Max--;
	if(Max != Min)
	{
		printf("not unique");
		return 0;
	}
	printf("unique\n%d",Max);
	return 0;
}
```


------------
完结撒花！


---

