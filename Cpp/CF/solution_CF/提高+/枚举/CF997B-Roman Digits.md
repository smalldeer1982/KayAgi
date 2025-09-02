# Roman Digits

## 题目描述

Let's introduce a number system which is based on a roman digits. There are digits I, V, X, L which correspond to the numbers $ 1 $ , $ 5 $ , $ 10 $ and $ 50 $ respectively. The use of other roman digits is not allowed.

Numbers in this system are written as a sequence of one or more digits. We define the value of the sequence simply as the sum of digits in it.

For example, the number XXXV evaluates to $ 35 $ and the number IXI — to $ 12 $ .

Pay attention to the difference to the traditional roman system — in our system any sequence of digits is valid, moreover the order of digits doesn't matter, for example IX means $ 11 $ , not $ 9 $ .

One can notice that this system is ambiguous, and some numbers can be written in many different ways. Your goal is to determine how many distinct integers can be represented by exactly $ n $ roman digits I, V, X, L.

## 说明/提示

In the first sample there are exactly $ 4 $ integers which can be represented — I, V, X and L.

In the second sample it is possible to represent integers $ 2 $ (II), $ 6 $ (VI), $ 10 $ (VV), $ 11 $ (XI), $ 15 $ (XV), $ 20 $ (XX), $ 51 $ (IL), $ 55 $ (VL), $ 60 $ (XL) and $ 100 $ (LL).

## 样例 #1

### 输入

```
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
```

### 输出

```
10
```

## 样例 #3

### 输入

```
10
```

### 输出

```
244
```

# 题解

## 作者：litble (赞：17)

[这是安利，你就戳一下嘛](https://blog.csdn.net/litble/article/details/80924306)

当然，如果你采取打表找规律的方法做的话，本题当然是一道水题。

但是这个规律是怎么来的呢？

首先我们可知，在$\{1,5,10,50 \}$中取$n$个组成不同数的方案数，和在$\{0,4,9,49 \}$中取$n$个的方案数是一样的。这样转化了之后，这些数两两之间互质，并且出现了0，更加好处理。

我们现在尽量去限制4和9，使得0和49可以任意取。

然后我们发现，9个4=4个9+5个0，为了避免重复，我们取的4的个数不能超过8个。

打表找用0和49代替4和9的例子，发现1个4+5个9=1个49+5个0，所以只要取了4，取9的个数就不能超过4个。如果没有取4，那么取9的个数就不能超过48个。

接下来发现，2个4+1个49+6个0=9个9。也就是说，当不取4的时候，取9的个数不能超过8个。

有了以上三点限制之后，我们可以枚举取4和取9的个数$i$和$j$，剩下的数全选0和49，方案数是$n-i-j$

见下面这个代码，可以发现，当循环跑满了之后的答案会呈现一种线性增长，这就是打表找出的规律的由来。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
typedef long long LL;
int n;LL ans;
int main()
{
    scanf("%d",&n);
   	for(RI i=0;i<=8&&i<=n;++i)
   		for(RI j=0;j<=(i==0?8:4)&&j+i<=n;++j)
   			ans+=n-i-j+1;
   	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：__Hacheylight__ (赞：4)

考思维，。。。

说难不难，看代码只有这么一点

说简单不简单，比赛时推出来也不容易

发现，当n>20时答案公差为49

所以分段做

1.<=20 暴力枚举

2.> 20 直接等差数列

注意long long




```cpp
#include <bits/stdc++.h>
using namespace std ;
long long ans,n ;
long long dfs(int x){
    map<long long,int> a ;
    a.clear() ;
    long long sum=0 ;
    for (int i=0;i<=x;i++)
    for (int j=0;i+j<=x;j++)
    for (int k=0;i+j+k<=x;k++){
        long long t=i+j*5+k*10+(x-i-j-k)*50 ;
        if (!a[t]){
            a[t]=1 ;
            sum++ ;
        }
    } 
    return sum ;
}
int main(){
    scanf("%lld",&n) ;
    if (n<=20) ans=dfs(n) ;
    else ans=dfs(20)+(n-20)*49;
    printf("%lld\n",ans) ;
}
```

---

## 作者：Amm_awa (赞：1)

$$
\huge{\texttt{CF 题解}}\tag*{\texttt{作者：wjl\_100930}}
$$

## 链接

[$\color{red}\fbox{\text{洛谷链接}}$](https://www.luogu.com.cn/problem/CF997B)

[$\color{red}\fbox{\text{ CF 链接 }}$](https://codeforces.com/problemset/problem/997/B)

## 分析 - 1

1. 题目标签是枚举，那么我们先试试枚举，但数据量很大，要用 `long long`。
2. 代码放剪贴板里了。

### Code & Submission

[$\color{red}\fbox{\text{代码}}$](https://www.luogu.com.cn/paste/yd8lwvf2)

[$\color{red}\fbox{\text{记录}}$](https://codeforces.com/problemset/submission/997/232370577)

可以看见，代码在第四个点超时了，接下来应该考虑更优解法。

## 分析 - 2

使用特殊方式：打表。

![](https://cdn.luogu.com.cn/upload/image_hosting/74lkxqtm.png)

可以发现，在 $n \ge 12$ 时，答案每次增长 $49$，这就有了表。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;
int a[13]={0,4,10,20,35,56,83,116,155,198,244,292,341};
//表
signed main()
{
    cin>>n;
    if(n<=12)
        cout<<a[n];
    else
        ans=(long long)(341+(long long)(n-12)*49),cout<<ans;
        //要开 long long
    return 0;
}
```

[$\color{red}\fbox{\text{记录}}$](https://codeforces.com/contest/997/submission/232376163)

---
$\color{#52C41A}\texttt{upd 1: 修改链接错误}$

---
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;[$\color{red}\fbox{\text{~~END~~}}$](https://www.luogu.com.cn/blog/734249/solution-cf997b#)



---

## 作者：Nozebry (赞：1)

## $Problems$
有一种新的数字系统，在这个数字系统中所有的书都有着四个字母组成 $I,V,X,L$，他们分别代表 $1$ $5$ $10$ $50$。

组成数的大小就是这几个字母值的代数和（与字母顺序无关），现在问你从这 $4$ 中字母中选择 $n$ 个，能表示多少个不同的数字。
## $Answer$
这道题就是简单的找规律，再按照题意查找到第 $11$ 项时，不难发现，后面就是以 $49$ 为公差的等差数列，所以做这道题只需先特判前 $11$，以后每一项都运用等差序列的公式来计算。。。
## $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long ans[12] = {0,4,10,20,35,56,83,116,155,198,244,292};//前11项是有规律的
int main()
{
    long long n;
    scanf("%lld",&n);
    if(n<=11)printf("%lld",ans[n]);
    else printf("%lld",ans[11]+(n-11)*49);//从第12项开始，每一项都可以用等差序列的公式来计算
}
```

---

## 作者：5G信号塔报装 (赞：1)

## 题意

枚举 $i,j,k,p$，使得 $i+j+k+p=n$。($i,j,k,p$ 范围分别为 $1,5,10,50$)

## 思路

### 暴力出奇迹

直接贴代码。

```cpp
# include <bits/stdc++.h>
using namespace std;

int n;

int solve(int x) {
	// 暴力出奇迹 枚举
	map <int, bool> ojbk; //map时间换空间，妈妈再也不用担心我MLE啦！
	int num;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= x - i; j++) {
			for (int k = 0; k <= x - i - j; k++) {
				int qwq = i + j * 5 + k * 10 + (x - i - j - k) * 50;
				if (!ojbk[qwq]) ojbk[qwq] = 1, num++;
			}
		}
	}
	return num;
}

signed main() {
	scanf("%d", &n);
	printf("%d\n", solve(n));
	return 0;
} 
```

显然，我们满足不了 $n\leq 10^9$ 的大数据。

[Virtual Judge 记录](https://vjudge.net/solution/29011162)

### 找规律

咱们来打个表：

![](https://pic.downk.cc/item/5ff568113ffa7d37b38dd91d.jpg)


发现：在数据达到一定规模时，答案出现了等差数列！

简单计算可得方差为 $49$。

### 改代码

于是思路就很明朗：**$n\leq 25$ 时暴力枚举答案，$n > 26$ 时利用等差数列求和。**

```cpp
if (n <= 25) printf("%d\n", solve(n));
else printf("%d\n", solve(25) + 49 * (n-25));
```

**BUT!!!**

[Virtual Judge](https://vjudge.net/solution/29011393)

![](https://pic.downk.cc/item/5ff569c73ffa7d37b38ef49a.jpg)

$$\color{white}\text{O I 十 年 一 场 空 \ \ \ 不 开 long long 见 祖 宗}$$

$n \leq 10^9$ 你不开 long long？？？？？？？？？？？？

## Code

**Think Twice, Code Once**

```cpp
## include <bits/stdc++.h>
using namespace std;

# define int long long 

int n;

int solve(int x) {
	// 暴力出奇迹 枚举
	map <int, bool> ojbk;
	int num = 0;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= x - i; j++) {
			for (int k = 0; k <= x - i - j; k++) {
				int qwq = i + j * 5 + k * 10 + (x - i - j - k) * 50;
				if (!ojbk[qwq]) ojbk[qwq] = 1, num++;
			}
		}
	}
	return num;
}

signed main() {
	puts("5G 赋能未来！| by 5G 信号塔包装 | 三网线路检修员");
	scanf("%lld", &n);
	if (n <= 25) printf("%lld\n", solve(n));
	else printf("%lld\n", solve(25) + 49 * (n-25));
	return 0;
} 

// 【调试记录】 
// (1) long long
// (2) 不放了，太丢人
```

---

## 作者：Daeyr_Xu (赞：0)

这到题~~一眼丁真~~，不是靠脑子数学硬算，就是打表找规律。

前者@litble 大神已经详细讲过了（膜拜大神），我就依她的题解进一步的复述一遍（因为第 一次没有看懂，~~芽儿太菜了~~）：

题目简意就是求在{ $1,5,10,50$ } 中取  $n$ 个组成不同数的方案数，我们将每个数减一，就变成在 { $0,4,9,49$ }中取 $n$ 个，由于有0的出现，故更加便于处理。

我们可以发现 $9\times4=4\times9+5\times0$，故 $9$ 个 $4$ 和 $4$ 个 $9+5$ 个 $0$ 为两种同样的情况，于是出现了重 复，那么单纯的排列组合相加是不行的（需要减一），所以如果方案数单调，取4的个数应不超过 $8$ 个。

同理：由 $1\times4+5\times9=1\times49+5\times0$ ，取 $4$ 的时候，取 $9$ 的个数就不能超过 $4$ 个。

由 $49\times9=9\times49+44\times0$ ，没有取 $4$ 的时候，取 $9$ 的个数就不能超过 $48$ 个。

但是由 $9\times9=2\times4+1\times49+6\times0$ ，发现在取 $48$ 个 $9$ 之前，没有取 $4$ 的情况已经出现重复，只不过用 $4$ 代替了一部分 $49$，所以取 $9$ 的个数不能超过 $8$ 个。

由上可知，我们找到了用 $0$ 和 $49$ 代替 $4$ 和 $9$ 的例子，于是我们可以枚举取 $4$ 和取 $9$ 的个数 $ i$ 和 $j$，剩下的数全选 $0$ 和 $49$，方案数是 $n−i−j+1$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans(0);
signed main(){
	cin >> n;
	for (int i=0;i<=8 && i<=n;i++){
		if(!i){
			for (int j=0;j<=8 && j+i<=n;j++)
				ans+=n-i-j+1;
		}
		else 
			for (int j=0;j<=4 && j+i<=n;j++)
				ans+=n-i-j+1;
	}
	cout << ans;
	return 0;
}
```

其次是打表，打表代码如下（其实就是简单的循环，但是包超时的）

```cpp
void solve(int x){
	bool vis[N];
	int ans(0);
	for (int i=0;i<=x;i++){
		for (int j=0;i+j<=x;j++){
			for (int k=0;i+j+k<=x;k++){
				int l = x-i-j-k;
				int p = i+5*j+10*k+50*l;
				if (!vis[p]) {
					vis[p] = 1;
					ans++;
				}
			}
		}
	}
	cout << ans << '\n';
}
```

这是前 $100$ 个数据：

```cpp
4 10 20 35 56 83 116 155 198 244 292 341 390 439 488 537 586 635 684 733 782 831 880 929 978 1027 1076 1125 1174 1223 1272 1321 1370 1419 1468 1517 1566 1615 1664 1713 1762 1811 1860 1909 1958 2007 2056 2105 2154 2203 2252 2301 2350 2399 2448 2497 2546 2595 2644 2693 2742 2791 2840 2889 2938 2987 3036 3085 3134 3183 3232 3281 3330 3379 3428 3477 3526 3575 3624 3673 3722 3771 3820 3869 3918 3967 4016 4065 4114 4163 4212 4261 4310 4359 4408 4457 4506 4555 4604 4653
```

发现在第 $12$ 个数据以后，每个数是前一个数加上 $49$（根据前面数学推导不难发现，第 $12$ 个数据其实就是 $4$ 取 $8$ 个， $9$ 取 $4$ 个的情况，所以后面的规律也不难理解）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;
int db[20]={0,4,6,10,15,21,27,33,39,43,46,48,49};
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=12;++i) db[i]=db[i-1]+db[i];
	if(n<=12) printf("%d",db[n]);
	else printf("%lld",1ll*db[12]+1ll*(n-12)*49);
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

输入一个数字的题大概率结论题，而且 $n$ 每增加一答案绝对递增，有结论题的味了，考虑打表找规律。

先写出以下的打表代码：

```cpp
void solve(int x) {
	map<int, int> m;
	int ans = 0;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; i + j <= x; j++) {
			for (int k = 0; i + j + k <= x; k++) {
				int l = x - i - j - k;
				int p = i + 5 * j + 10 * k + 50 * l;
				if (!m[p]) {
					m[p] = 1;
					ans++;
				}
			}
		}
	}
	cout << ans << '\n';
}
```

得到这个表（$n \le 20$）：

```
4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341, 390, 439, 488, 537, 586, 635, 684, 733
```

易观察到 $292+49=341, 341+49=390, 390 +49 = 439\dots$

得到结论：$n$ 在大于等于 $11$ 时答案成线性递增，$n$ 每增加 $1$ 答案增加 $49$。

于是可以得到以下 AC？代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int l[60] = {4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341, 390}, n;
int mian() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	n--;
	if (n < 11) cout << l[n] << '\n';
	else cout << 49ll * (n - 10) + l[10] << '\n';
	return 0;
}


```

---

## 作者：Targanzqq (赞：0)

一道打表题。

首先我们对于小数据，尝试枚举每个罗马数字的数量，把可能的结果放到桶里，并统计有多少桶不为空。这部分的时间复杂度为 $O(n^4)$。

我们列出这个表，并找到一些规律：


|$i$|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$ans_i$|4|10|20|35|56|83|116|155|198|244|292|341|390|439|488|

然后我们发现，到第 $12$ 位及以后，我们填入的数一定比上一位多 $49$，因此我们可以在此基础上使用等差数列计算答案。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[15]={0,4,10,20,35,56,83,116,155,198,244,292};

signed main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	if(n<=11)cout<<a[n];
	else cout<<a[11]+(n-11)*49;
}
```
打表代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int bx[500005],n=50; 

signed main(){
	ios::sync_with_stdio(false);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=50*i;j++){
			bx[j]=0;
		}
		for(int j=0;j<=i;j++){
			for(int k=0;k+j<=i;k++){
				for(int l=0;l+k+j<=i;l++){
					bx[j+5*k+10*l+50*(i-j-k-l)]++;
				}
			}
		}
		int ans=0;
		for(int j=0;j<=50*i;j++){
			if(bx[j]>0)ans++;
		}
		cout<<ans<<",";
	}
}
```

---

## 作者：Guizy (赞：0)

这题一开始推了半天公式也没有什么头绪，感觉像是找规律。既然是找规律，那我们就先打表试试。

```cpp
#include<bits/stdc++.h>
using namespace std;

int solv[50];

int solve(int x){
	map<int,bool>mp;
	int ans=0;
	for(int i=0;i<=x;i++)
		for(int j=0;i+j<=x;j++)
			for(int k=0;i+j+k<=x;k++){
				int num=i+j*5+k*10+(x-i-j-k)*50;
				if(!mp[num]) ans++,mp[num]=1;
			}
	return ans;
}

int main(){
	
	int n=20;
	
	for(int i=1;i<=n;i++){
		solv[i]=solve(i);
		printf("%d %d\n",i,solv[i]);
	}
	
}
```

打了前 $20$ 个，我们发现，在 $n\geq12$ 的时候，$n$ 每增加 $1$，答案就增加 $49$。

所以，我们分类讨论：

- 当 $n<=12$ 时，输出 $solv_n$。

- 否则输出 $solv_{12}+(n-12)\times49$。

说实话，在你找不到规律时，打表其实也是一个很好的办法。

最后附上 AC 代码（记得加 `long long`）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int Max=30;
int solv[Max];

int solve(int x){
	map<int,bool>mp;
	int ans=0;
	for(int i=0;i<=x;i++)
		for(int j=0;i+j<=x;j++)
			for(int k=0;i+j+k<=x;k++){
				int num=i+j*5+k*10+(x-i-j-k)*50;
				if(!mp[num]) ans++,mp[num]=1;
			}
	return ans;
}

signed main(){
	
	int n;scanf("%lld",&n);
	for(int i=1;i<=12;i++){
		solv[i]=solve(i);
	}
	
	if(n<=12) printf("%lld",solv[n]);
	else printf("%lld",solv[12]+(n-12)*49);
	
}
```

由于 RemoteJudge 总是 UKE，所以就直接放 [AC 记录](https://codeforces.com/contest/997/submission/243231428)吧。

同样是可以通过打表找规律的还有：[P9913 「RiOI-03」water problem](https://www.luogu.com.cn/problem/P9913#submit)。

---

## 作者：fish_shit (赞：0)

## 思路
### 方案一
选择直接暴力，枚举 $4$ 个罗马数字出现的次数。

但考虑到 $n \leq 10^9$，此暴力方法显然不行，需要换种方案。

### 方案二
用暴力代码尝试一下前几个数的答案，可以发现前 $11$ 个数的答案没有规律，但是以后的数字的答案都是有规律的，以后的数字的答案成为了一个等差数列，且公差为 $49$。

所以在输入的 $n$ 大于 $11$ 时，我们可以输出 $11$ 的答案加上 $n$ 与 $11$ 的差再乘上 $49$；否则输出暴力算好的答案。

注意：$n$ 要开 long long。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11]={4,10,20,35,56,83,116,155,198,244,292};//前11个的答案
long long b;//记得开long long 
int main(){
    cin>>b;
    if(b<=11){
    	cout<<a[b-1];
	}
    if(b>=12){
		cout<<292+(b-11)*49;//11的答案再加上需要加的数量乘上每两个数之间的差 
	}
	return 0;
}
```


---

