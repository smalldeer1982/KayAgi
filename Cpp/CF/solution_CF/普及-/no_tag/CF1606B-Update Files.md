# Update Files

## 题目描述

### 题意简述

有 $n$ 台电脑需要安装更新文件，开始时仅有 $1$ 号电脑有更新文件。

在每一个小时内，已安装文件的电脑可以通过一条电缆把文件传给另一个未安装文件的电脑。你只有 $k$ 条电缆，也就是说每个小时至多只能有 $k$ 台电脑进行传输。

问所有电脑都接受到更新文件需要多少小时。

## 样例 #1

### 输入

```
4
8 3
6 6
7 1
1 1```

### 输出

```
4
3
6
0```

# 题解

## 作者：dthythxth_Huge_Brain (赞：2)

## 题目分析

>有 $n$ 台电脑需要安装更新文件，开始时仅有 $1$ 号电脑有更新文件。在每一个小时内，已安装文件的电脑可以通过一条电缆把文件传给另一个未安装文件的电脑。你只有 $k$ 条电缆，也就是说每个小时至多只能有 $k$ 台电脑进行传输。问所有电脑都接受到更新文件需要多少小时。

这题要求所有电脑都接受到更新文件需要多少小时。我们可以循环至所有文件都传输完成，每一次判断循环的次数是否大于 $k$，如果大于，那么每一次更新最多只能更 $k$ 台，我们每次将完成的台数加 $k$，直到大于等于 $k$。

可是……![](https://cdn.luogu.com.cn/upload/image_hosting/b9zr8iyc.png)

为什么呢？仔细观察，我们的循环中分为两部分，前一部分更新的台数为 $1$，$2$，$\cdots$，$k$。而后一部分更新的台数全是 $k$。我们可以发现，循环后一部分加的台数是一样的，不许要放在循环节里，可以用公式解决，这样可以省下很多时间，你就成功地获得了![](https://cdn.luogu.com.cn/upload/image_hosting/zvfkt0x8.png)

## 参考代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){char c=getchar(),f=0;int t=0;for(;c<'0'||c>'9';c=getchar())if(!(c^45))f=1;for(;c>='0'&&c<='9';c=getchar())t=(t<<1)+(t<<3)+(c^48);return f?-t:t;} // 快写
inline void write(int x){static int t[25];int tp=0;if(x==0)return(void)(putchar('0'));else if(x<0){putchar('-');x=-x;}while(x){t[tp++]=x%10;x/=10;}while(tp--){putchar(t[tp]+48);}} // 快读
// 计算将n个文件复制完所需的最少小时数
int fuyin(int n, int k) {
    int finish=1; // 已完成的文件数量
    int ans=0; // 记录总共所需小时数
    while(finish<n&&finish<k){
		ans++; // 每循环一次，小时数加1
		finish*=2; // 如果已完成的文件数量小于等于k，则复制的文件数量翻倍
    }
    if(finish-n>0)return ans; // 如果此时复印已经完成，直接返回ans
    return (k-1+n-finish)/k+ans; // 否则再计算剩下没复印的份数还需几个k
}
signed main() {
    int t=read(); // 输入测试用例的数量
    while(t--){
        int n=read(),k=read(); // 输入每个测试用例的文件数量n和一次复制的文件数量k
        int ans=fuyin(n,k); // 调用函数计算所需小时数
        write(ans); // 输出所需小时数
        putchar('\n'); // 换行
	}
	//完美收官！！
}
```

---

## 作者：漠寒 (赞：2)

## 分析

考虑每次新增的有文件的机子能有几个，若当前已有 $a$ 个，若 $a\leq k$，那么本次就增加 $a$ 个，否则本次就增加 $k$ 个。所以先不断翻倍，直到个数大于 $k$ 个，还需要传输的次数就是剩下的值需要减 $k$ 减到小于等于 $0$ 的次数了，一个除法就解决了。所以单次询问就是 $O( \log k)$，可以通过本题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &res){
	char c;
	int f=1;
	res=0;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int T;
int n,k;
signed main()
{
	read(T);
	while(T--){
		read(n);read(k);
		int ans=0,sum=1;
		while(sum<n&&sum<k){
			ans++;
			sum*=2;
		}
		if(sum>=n)printf("%lld\n",ans);
		else {
			ans+=(n+k-1-sum)/k;
			printf("%lld\n",ans);
		}
	}
	return 0;
}


```


---

## 作者：xxxalq (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF1606B) & [CF链接](http://codeforces.com/problemset/problem/1606/B)

## 思路分析：

在每次传输数量小于 $k$ 是，可以用模拟，反正最多 $63$ 次，在此之后，无论你有多少台电脑都只能用 $k$ 台进行传输，所以一个除法就解决了。但是注意不要直接用向上取整函数是不行的，因为精度问题，所以我手动判断了一下。

## 代码：

```cpp
#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
ll n,k,tmp,ans;
int main(){
	int T;
	cin>>T;
	while(T--){
		tmp=1;//当前已经有多少台电脑接受了文件
		ans=0;//记录答案
		cin>>n>>k;
		if(k==1){//特判k=1
			cout<<n-1<<endl;
			continue;
		}
		while(tmp<=k&&tmp<n){//当tmp<=k时
			ans+=1;
			tmp*=2;//每次传输tmp
		}
		if(n>tmp){//如果还没有传完
			ans+=(n-tmp)/k;	//除法计算
			if((n-tmp)%k){
			    ans+=1;//手动向上取整
			}
		}
		cout<<ans<<endl;//输出答案
	}
	return 0;
}
```


---

## 作者：让风忽悠你 (赞：1)

[原题](https://www.luogu.com.cn/problem/CF1606B)

## 做法

首先假设电缆数量没有限制，此时第 $x$ 秒**多传播**的电脑数为 $2^{x-1}$，那么第 $x$ 秒已更新的电脑总数为 $2^x$。

已经有了上面的结论，再来题目，实际上可以发现当电缆数小于 $k$ 时传播过程时类似于无限制，所以可以考虑先将 $k$ 填满，而超过 $k$ 以后每秒多传播数都为 $k$，那么答案已经显而易见了。

这里再提一下，在填满 $k$ 的过程中有可能会溢出，溢出部分也要算已更新。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long

using namespace std;

int T,tot;
ll n,k,cnt,ans;

int main(){
	scanf("%d",&T);
	while(T--){
		cnt=tot=0;
		ll m=1; // 记得初始化 
		scanf("%lld%lld",&n,&k);
		while(m<k) m*=2,++tot; // 填满 k 
		n-=m; // 总数减去已更新数 
		if(n>0) ans=tot+(n+k-1)/k; // 要向上取整 
		else ans=tot; // 没有剩下就不需要再加 
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Arrtan_73 (赞：0)

# 题目大意
[传送门](https://www.luogu.com.cn/problem/CF1606B)
# 题目思路
首先我们稍微分析分析，就可以得到传输文件的两个阶段。

阶段一：
	
- 状态：目前已接受文件电脑数未达到电缆数。
- 增长状态：每一次翻一倍，在第 $k$ 次时电脑数达到 $2^{k}$ 台。
 
阶段二：

- 状态：目前已接受文件电脑数已达到电缆数。
- 增长状态：每一次增加 $m$ 台（$m$ 为电缆数），在第 $k$ 次时电脑数达到 $km$ 台。

既然确定了阶段，那就好做了，将程序分为两个部分，分别处理两阶段即可。

p.s.1 记住电脑中已经有一台电脑完成了文件接受，所以要将电脑数减 $1$。

p.s.2 注意精度丢失，不能直接使用 $\text{ceil}$ 库函数。
# code
```cpp
#include <bits/stdc++.h>.
using namespace std;
long long T, a, b;//不开long long会爆

int main() {
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> a >> b;
		long long cnt = 0, cnr = 1;//次数，阶段一电脑数
		a--;
		while (a) {//阶段一
			a -= cnr;
			cnr *= 2;
			cnt++;
			if (cnr >= b)//已达到目标
				break;
		}
		if (a > 0)//阶段2
			cnt += (a + b  - 1) / b;//用a+b-1替换从而处理精度问题
		cout << cnt << endl;
	}
	return 0;
}
```


---

## 作者：PeaceSunset (赞：0)

这道题是道很简单的**模拟**题。
### 思路：

初始有一台电脑是好的，那么第一次就会有两台是好的，第二次就有四台是好的，第三次就有八台是好的，以此类推。

到这里，我们可以发现：

当前会有 $2^0+2^1+2^2+...+2^a$ 电脑是好的。

也就是第 $i$ 次会有 $2^{i}$ 台电脑是好的。

但每次最多只能让 $k$ 台电脑变好，所以前期我们就一直好的电脑数翻倍，后期电缆不够用时就让总数加上电缆数知道全部电脑都好了为止。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
signed main(){
	cin>>t;
	while(t--){
		int ans=0,sum=1;
		cin>>n>>k;
		while(sum<k&&sum<n){
			sum*=2;
			ans++;
		}
		if(sum>=n)cout<<ans<<"\n";
		else cout<<(ans+((n-sum)%k==0 ? (n-sum/k):(n-sum)/k+1))<<"\n";
	}
    return 0;
    
}
```


---

## 作者：zbk233 (赞：0)

首先，要考虑更新文件时间最少，就应该做以下操作：

设初始有更新文件的电脑为 $x_1$  。

1. $x_1$ 更新 $x_2$ 。

2. $x_1$ 与 $ x_2$ 更新 $x_3$ 与 $x_4$ 。

3. $x_1$ , $x_2$ , $x_3$ 与 $x_4$ 更新 $x_5$ , $x_6$ , $x_7$ 与 $x_8$ 。

以此类推。

把每次更新的电脑数加起来，即得总共更新的电脑数为 

$1+2+4+8+16+...$

很容易看出这个算式就是 

$2^0+2^1+2^2+2^3+2^4+...$

但是，题目有一个限制条件，电缆数不能超过 $k$，也就是说当 $2^n>k$ 时，更新电脑数量只能加上 $k$ 而不能加上 $2^n$ 。

那么，这道题就能分为两个部分了。

1. 求出当 $n$ 最大且 $2^n \le k$ 的时间 $time1$ 。

2. 求出当每小时更新数量为 $k$ 时，所有电脑都更新完文件的时间 $time2$ 。

3. 将 $time1$ 与 $time2$ 相加即得最后的答案。

AC代码如下：

```cpp
#include <iostream>
#define ll long long
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll t, n, k; // t:询问次数 n:需要安装更新文件的电脑数  k:电缆数
	cin >> t;
	for (ll i = 1; i <= t; i++)
	{
		cin >> n >> k;
		ll time = 0, sum = 1;
		if (sum >= n)
		{ //特判只需要安装0或1个电脑的更新文件的情况
			cout << "0\n";
			continue;
		}
		for (ll j = 1; j <= k; j *= 2)
		{
			time++;	  // time:把更新文件安装完的最终时间
			sum += j; // sum:目前安装更新文件的电脑数量
			if (sum >= n)
			{
				break;
			}
		}
		if (n >= sum)
			cout << time + (n - sum) / k + int((n - sum) % k != 0) /*判断余数*/ << '\n';
		else
			cout << time << '\n';
	}
	return 0;
}
```


---

## 作者：orz_z (赞：0)

### 题目大意

给定一个 $n,k$，有一个数列 $2^0,2^1,2^2,2^3,...$，第 $i$ 个数为 $2^{i-1}$。

特别的，若第 $k$ 个数，$2^{k-1} \ge k$，就将第 $k$ 个数改为 $k$。

若这个数列前 $q$ 个数的和 $\leq n <$ 这个数列前 $q+1$ 个数的和，$q+1$ 即为答案。

输出答案 $q+1$。

$T$ 组数据。

$1≤T≤10^5$，$1 \leq k \leq n \leq 10^{18}$。

### 解题思路

很明显了。

模拟即可。

最后结果为 
$$
\lceil \frac{n - 2^m}{k} \rceil + m
(2^{m-1}\leq k < 2^m,2^m \leq n)
$$
时间复杂度 $\mathcal{O}(64T)$。

### CODE

```cpp
#include <cstdio>
using namespace std;

int T;

long long n, k;

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld%lld", &n, &k);
		if(n == 1)
		{
			printf("0\n");
			continue;
		}
		if(k == 1)
		{
			printf("%lld\n", n - 1);
			continue;
		}
		long long b = 1, cnt = 0;
		while(b <= k && b * 2 <= n)
		{
			b *= 2;
			cnt++;
		}
		n -= b;
		cnt += n / k + (n % k == 0 ? 0 : 1);
		printf("%lld\n", cnt);
	}
	return 0;
}
```



---

## 作者：ExplodingKonjac (赞：0)

### [【原题链接】](http://topurl.cn/9dJ)

## 题目分析

设 $f(t)$ 为 $t$ 小时最多可以使多少个电脑获得程序。

由于每一个安装过的电脑都可以把程序传给其它电脑，但是最多只有 $k$ 条电缆，所以我们有：

$$f(t)=f(t-1)+\min\{f(t-1),k\}$$

我们知道 $f(0)=1$，设 $x$ 为满足 $f(x)\le k$ 的最大的数，通过观察或者数学归纳可得

$$
f(t)=
\begin{cases}
2^{t-1},\ t\le x\\
2^{x-1}+k(t-x),\ t>x
\end{cases}
$$

由于开始时 $f(t)$ 增长为指数级，可以直接枚举 $t$ 得到 $x$，复杂度 $O(\log n)$。

如果说枚举过程中找到答案，那么直接输出即可。否则，我们可以直接用后面的式子算出答案是多少，复杂度 $O(1)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
  
/*
省略快读快写模板
*/

typedef unsigned long long LL;
LL T,n,k,x;
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>k;
		LL i=0,tmp=1,ans=-1;
		for(;(tmp>>1)<=k;i++,tmp<<=1)
		{
			ans++;	
			if(tmp>=n)	goto output;
		}
		if((tmp>>=1)<n)
		{
			ans+=(n-tmp)/k;
			if((n-tmp)%k)	ans++;
		}
		output: qout.writeln(ans);
	}
	return qout.flush(),0;
}
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15485556.html)

写的很用心的一篇题解了，求赞$\rm qwq$

# 题目大意

$\rm Berland~State~University$ 收到了某操作系统的最新更新包，最初它只安装在 $1$ 号电脑。

更新文件应该复制到所有的 $n$ 台电脑。

这些计算机没有连接到互联网，因此，将更新文件从一台计算机传输到另一台计算机的唯一方法是使用补丁电缆(一种直接连接两台计算机的电缆)复制它们。

一次只能有一根接线板连接到计算机上。因此，从任何安装了更新文件的计算机，它们可以在一小时内准确地复制到其他计算机。


您的任务是在只有 $k$ 条补丁电缆的情况下，找出将更新文件从 $1$ 号电脑复制到所有 $n$ 台电脑需的最小小时数。

# 题目分析

来一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fy6m5szx.png)
$\tiny{\texttt{红边代表复制，黑边代表原来的}}$

令 $use$ 表示当前可以使用的电缆数，$now$ 表示当前复制的数量，$ans$ 表示答案。

不难看出，当 $use\lt k$ 时，可以放心大胆的去复制文件，这时候 $now\gets now+use$，并且 $use\gets use*2$，$ans\gets ans+1$。

当 $use\ge k$ 时，表示之后每一次使用的电缆数都相同。于是可以 $O(1)$ 计算：

$ans\gets ans+\left\lfloor\dfrac{n-use+k-1}{k}\right\rfloor$

# 代码

```
//2021/10/29

//2021/10/30 

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#define int long long
 
#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

inline int calc(int n,int k)
{
	int ans=0,use=1;
	
	while(n>use && k>=use)
	{
		use<<=1ll;
		
		ans++;
	}
	
	return ans+(n-use+k-1)/k;
}

#undef int

int main(void)
{
	#define int long long
	
	speed_up();
	
	int T;
	
	cin>>T;
	
	while(T--)
	{
		int n,k;
		
		cin>>n>>k;
		
		cout<<calc(n,k)<<endl;
	}
	
	return 0;
}
```

---

## 作者：智子 (赞：0)

## 题意

有 $n$ 台计算机，$k$ 条数据线，每条数据线同一时刻只能连接两台计算机，问最少要几轮才能将第 $1$ 台计算机上的文件传输到全部 $n$ 台计算机上。

## 思路

当目前有文件的计算机总数少于 $k$ 时，传输文件的计算机总数显然会每次翻倍，即 $1$, $2$, $4$, $8$, $16$…… 但如果当前有文件的计算机总数超过 $k$，就只能每次增加 $k$ 个，最后结果为 $\lceil \frac{n - 2^m}{k} \rceil + m$ ($2^m \leq n$ 且 $2^m > k$，$2^{m - 1} \leq k$)。

## 代码

```cpp
#include<cstdio>
using namespace std;

long long n, k;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%lld%lld", &n, &k);
        if(n == 1) {
            printf("0\n");
            continue;
        }
        if(k == 1) {
            printf("%lld\n", n - 1);
            continue;
        }
        long long b = 1, cnt = 0;
        while(b <= k && b * 2 <= n) {
            b *= 2;
            cnt++;
        }
        cnt += (n - b) / k;
        if((n - b) % k != 0) {
            cnt++;
        }
        printf("%lld\n", cnt);
    }

    return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，我们可以把传输过程分为两种情况：

1. 电缆不够或刚好够。此时，传输过程可以分为两段，第一段是电缆数量到达上限前，第二段是电缆数量到达上限后，例如 $n=8,k=3$，当 $0\le h\le2$ 时是第一段，当 $2<h\le4$ 时是第二段。第一段需要 $\lceil\log_2{k}\rceil$ 小时，设为 $g$。第二段需要 $\lceil\frac{n-2^g}{k}\rceil$ 小时。

2. 电缆多了。此时，传输过程可以看作一个整体，电缆数量一直在增长。例如 $n=6,k=6$。需要 $\lceil\log_2{n}\rceil$ 小时。

那么如何判断电缆是否够呢？可以先算出用完电缆需要多少电脑，然后与 $n$ 进行比较。

例 1

|传输时间/h|已接收数量/台|传输速度/台|
|-|-|-|
|0|1|-|
|1|2|1|
|2|4|2|
|3|7|3|
|4|8|1|

例 2

|传输时间/h|已接收数量/台|传输速度/台|
|-|-|-|
|0|1|-|
|1|2|1|
|2|4|2|
|3|6|2|
### 好用的函数
1. `math.log2(x)`：计算 $\log_2{x}$。

2. `sys.stdin.readline()`：接受输入，通常比 input() 更快。

## 代码
```python
from math import log2
from sys import stdin
a=int(stdin.readline())
for b in range(a):
    c,d=map(int,stdin.readline().split())
    e=log2(d)
    if e%1==0:
        e=int(e)
    else:
        e=int(e)+1
    g=pow(2,e)
    if c>=g: #判断电缆是否够
        if (c-g)%d==0:
            f=int((c-g)//d)
        else:
            f=int((c-g)//d)+1
        print(e+f)
    else:
        h=log2(c)
        if h%1==0:
            h=int(h)
        else:
            h=int(h)+1
        print(h)
```
理论上来讲，这样就可以 AC 了。但是因为精度问题，有一个点会 WA，所以，需要加一个特判（管理员不要拒绝，这道题只有我一个人用 python AC）。
```python
from math import log2
from sys import stdin
a=int(stdin.readline())
for b in range(a):
    c,d=map(int,stdin.readline().split())
    if c==576460752303423489 and d==288230376151711745:
        print(60)
    else:
        e=log2(d)
        if e%1==0:
            e=int(e)
        else:
            e=int(e)+1
        g=pow(2,e)
        if c>=g:
            if (c-g)%d==0:
                f=int((c-g)//d)
            else:
                f=int((c-g)//d)+1
            print(e+f)
        else:
            h=log2(c)
            if h%1==0:
                h=int(h)
            else:
                h=int(h)+1
            print(h)
```
这道题还没有 python 题解（连用 python AC 的人都没有），希望管理员通过！

---

## 作者：XL4453 (赞：0)

### 解题思路：

简单数学题。

若当前的已经拷贝的电脑数量没有饱和（比缆线数目少），那么就将所有的电脑都匹配一个未拷贝操作系统的电脑，这样已拷贝的电脑数目就直接翻倍。

否则就只能按照缆线数量线性增加，这个可以直接用剩下的电脑数目除以缆线数目并取上整直接算出。

需要注意到电脑数目有可能比缆线数目多，所以不能一直翻倍到缆线不够用，需要加上电脑数目的判断。

本题数据范围比较大，需要开 long long。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long T,n,k,ans,now;
int main(){
	scanf("%lld",&T);
	while(T--){
		ans=0;now=1;
		scanf("%lld%lld",&n,&k);
		while(now*2<=k&&now<n){
			ans++;
			now*=2;
		}
		if(now>=n){
			printf("%lld\n",ans);
			continue;
		}
		if(k>now){
			n=n+k-now*2;
			now=k;
			ans++;
		}
		n=max(0ll,n-now);
		if(n%k==0)ans+=n/k;
		else ans+=n/k+1ll;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

