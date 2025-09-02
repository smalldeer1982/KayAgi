# The Number of Products

## 题目描述

给出一个由$n$个非零整数构成的序列$a_1,a_2,\dots,a_n$。

你需要计算下列两个值：

1.下标对$(l,r)(l\le r)$使得$a_l*a_{l+1}*\dots*a_r$为负数；

2.下标对$(l,r)(l\le r)$使得$a_l*a_{l+1}*\dots*a_r$为正数；

## 样例 #1

### 输入

```
5
5 -3 3 -1 1
```

### 输出

```
8 7
```

## 样例 #2

### 输入

```
10
4 2 -4 3 1 2 -4 3 2 3
```

### 输出

```
28 27
```

## 样例 #3

### 输入

```
5
-1 -2 -3 -4 -5
```

### 输出

```
9 6
```

# 题解

## 作者：Ofnoname (赞：14)

首先，所有数都只考虑正负性，所以正数一律视为1，负数一律视为-1.以计算乘积为负数为例

类似前缀和，我们可以处理一个“前缀积”，设为S，那么$a_l*a_{l+1}*...*a_r$就于$S_R \div S_{L-1}$。并且显然$L=1$时$S_0$应该设为1.

也就是说，每读入一个数$a_i$并计算$S_i$，我们就分析之前的$S_0,S_1,S_2,...S_{i-1}$，如果符号与$a_i$不同就可以将ans++，所有$S_i$里多少是正，多少是负是可以用桶存储的，复杂度为$O(N)$。

乘积为正数结果显然就是$N*(N+1)/2 - ans$。

```cpp
#include <bits/stdc++.h>
#define MAX (200000 + 7)
using namespace std;

int N,sum=1,T[2],a[MAX];
long long ans;

int main()
{
	scanf("%d", &N); T[0] = 1;
	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", a + i);
		sum *= a[i]>0 ? 1 : -1;
		ans += sum>0 ? T[1] : T[0];
		T[sum>0 ? 0 : 1]++;
	}cout<<ans<<' '<<(long long)N*(N+1)/2-ans;
}

```

---

## 作者：梦里调音 (赞：5)

昨天比赛的一道题。

算法：**前缀和**

时间复杂度：O(n)

设置变量：对于a[i],前面一整段的符号，前面的正子序列数，前面的负子序列数。

若a[i]前一整段是正序列，则让答案加上之前的正子序列数，正子序列数加一

否则，让答案加上负子序列数，负子序列数加一

不开LL见祖宗。

结束。

```
#include <bits/stdc++.h>
using namespace std;
long long int n;
long long int f,z;
int main(){
	cin>>n;
//前面整段的符号
//   		 前面的正子段
//			       前面的负子段 
	long long int sgn=1,pos=1,neg=0;
	for(long long int i=1;i<=n;i++){
		long long int a;
		cin>>a;
		if(a<0)sgn=-sgn;
		if(sgn>0){
			z+=pos;
			f+=neg;
			pos++;
		}
		else{
			z+=neg;
			f+=pos;
			neg++;
		}
	}
	cout<<f<<" "<<z<<endl;
}
```


---

## 作者：基地A_I (赞：5)

~~看到没有人写题解我就赶紧过来了~~

设 $f[i][0/1]$ 表示**以i结尾** 0表乘积为正数，1表乘积为负数 的子区间数，那么我们可以推出方程

- 如果 i 是+，则 $f[i][0]=f[i-1][0]+1$（加上自己），$f[i][1]=f[i-1][1]$

- 如果 i 是-，则 $f[i][0]=f[i-1][1]$，$f[i][1]=f[i-1][0]+1$

最后统计答案：

$$ans[0/1]=\sum_{i=1}^nf[i][0/1]$$

Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 2e5+7;
int n,a,l,r;
int f[N][2];
signed main()
{
	n = read();
	for(int i=1;i<=n;++i) {
		a = read();
		if(a > 0) f[i][0] = f[i-1][0]+1, f[i][1] = f[i-1][1];
		else f[i][0] = f[i-1][1], f[i][1] = f[i-1][0]+1;
		l += f[i][0], r += f[i][1];
	}
	printf("%lld %lld\n",r,l);
	return 0;
}
```

---

## 作者：Derpy (赞：2)

# ~~**我又来颓题解了**~~

第一暴力，一个一个枚举左右端点再扫就是N^3，T不T。。。自己拿捏

第二暴力就是可以预处理出区间正负。。。好想法但是N^2也会T昂

看到前面大佬的前缀积一头雾水，我果然还是太蒻了。

于是我就开始自己找规律

拿到第一组数据，先把它们全化成正负

就是：
```cpp
+-+-+
```
把它们所有的配对都写出来，会形成一个金字塔（第i行第j个表示第i个数作左端点，第j个数作右端点所形成的子串的正负性，最后的答案其实就是金字塔中正负号数量的总和）

得到：
```cpp
+--++
 --++
  +--
   --
    +
```
这样看其实也不是很明显，我们来看第二组

化成符号:
```cpp
++-+++-+++
```
继续写配对

```cpp
++----++++
 +----++++
  ----++++
   +++----
    ++----
     +----
      ----
       +++
        ++
         +
```
~~还有点好看~~

但好不好看是次要的，我们仔细观察这个结构，这个金字塔是由很多个正方形和三角形构成的，三角形由+号构成，正方形由+ - 交替构成。

一列一列地看会比较好想，代码实现也要容易一些，观察一下，没有遇到负号的时候每一列比起前一列就只是在最下面添加了一个+号而已，其它部分都保持不变，遇到负号就将当前所有的正负号反转再添上一个负号（也可以理解为添加一个正号再反转，代码实现中就为这种写法）。按照这样的规律下来就可以O(n)计算整个“金字塔”中的正负号数量总和了

具体实现看代码：

```cpp
#include<bits/stdc++.h>
#define int long long	//记得开long long 
#define mx 200005
using namespace std;
int a[mx];
inline int r()	//朴素的快读 
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) a[i]=r();
	int ansz=0/*正积子串累加器*/,ansf=0/*负积子串累加器*/,cntz=0/*之前提到的每一列的正号数量*/,cntf=0/*同理,每一列负号数量*/;
	for(int i=1;i<=n;i++)
	{
		cntz++;//增加的正号 
		if(a[i]<0)//遇到负号时 
		{
			swap(cntz,cntf);//由于全部反转,所以正号的数量变成负号的数量，负号的数量变成正号的数量 
		}
		ansz+=cntz;//正号累加 
		ansf+=cntf;//负号累加 
	}
	cout<<ansf<<" "<<ansz<<endl;//输出答案 
	return 0;
}
```


---

## 作者：Sooke (赞：2)

### 简要题意

求序列 $a_{1}\ \dots\ a_{n}$ 有多少子段积为负，多少为正，$a_i \neq 0$ 。

---

### 解题思路

> 正正得正，正负得负，负正得负，负负得正。

子段积的具体值我们无从得知，我们只需要正负性，所以对于每个 $a_i$ ，具体值也是不必要的，其符号才是重点。联想到：

> $0\oplus0 = 0,\ 0 \oplus 1 = 1,\ 1 \oplus 0 = 1,\ 1 \oplus 1 = 0$ 。

所以原题等同于把 $> 0$ 的 $a_i$ 赋为 $0$ ，$< 0$ 的 $a_i$ 赋为 $1$ ，求有多少子段异或和为 $1$ ，有多少为 $0$ 呀！

而 $a_l \oplus a_{l+1} \oplus\ \dots\ \oplus a_r$ ，只要预处理出**前缀异或和** $s_n = a_1 \oplus a_2 \oplus\ \dots\ \oplus a_n$ ，它就等于 $s_r \oplus s_{l-1}$ ！

问题进一步得到简化，预处理出 $s$ 后，对于每个 $r$ ，都统计多少 $l \le r$ 满足 $s_{l-1} = 0$ 以及 $1$ ！

直接扫过去用一个计数器统计就可以啦。

---

### 代码实现

```cpp
#include <bits/stdc++.h>

inline int read() {
    char c, _c; int x; for (c = _c = getchar(); !isdigit(c); c = getchar()) { _c = c; }
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return _c == '-' ? -x : x;
}

const int N = 1e6 + 5;

int n, x, y, a[N];
long long ans0, ans1;

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        if (a[i] > 0) {
            a[i] = 0;
        } else {
            a[i] = 1;
        }
    }
    x++;
    for (int i = 1; i <= n; i++) {
        a[i] ^= a[i - 1];
        if (a[i] == 0) {
            ans0 += x; ans1 += y; x++;
        } else {
            ans0 += y; ans1 += x; y++;
        }
    } printf("%lld %lld\n", ans1, ans0);
    return 0;
}
```

---

## 作者：一梦南柯 (赞：2)

[题目传送 Biu~](https://www.luogu.org/problem/CF1215B)

题目大意：题目会给你一个序...~~你还是点传送门吧~~


------------
能够知道$n\le2*10^5$,故复杂度只可能是$O(n) or O(n logn)$ 

至于$O(nlogn)$基本不予考虑，~~因为它是div2 B题~~，因为二分在此题的作用并不必要，于是序列+$O(n)$基本上能联想到前缀和了

我们在此题使用一个正前缀和数组，一个负前缀和数组，正的直接加上，负的考虑负负得正也能够转化到ans里去

其他要点在代码注释中会提到


------------
~~殆马~~如下：

貌似空间有一定的浪费，但当时没来的及管那么多

~~还有变量名也丑到不能看啊~~

```
#include<bits/stdc++.h>
#define rint register int
#define ll long long 
using namespace std;
const int maxn=2e5+5;
int a[maxn],tmp;
int pre[maxn],cnt[maxn],rcnt[maxn];
ll ans;
int main()
{
	int n;
	cin>>n;
	ll tot=(ll)n*(n+1)>>1;//这里是所有子段的总数
    //long long要注意
	//cout<<tot<<endl;
	pre[0]=1;
	for(rint i=1;i<=n;++i)
	{
		cin>>tmp;
        
		tmp>0?a[i]=1:a[i]=-1;//将正负转化成1与-1
        
		pre[i]=pre[i-1]*a[i];//pre[i]即a1~ai的数字乘积正负
        //pre好像也算个前缀qwq
		if(pre[i]>0) cnt[i]=1;//正的前缀和（的前缀和）
		else rcnt[i]=1;//负的前缀和（的前缀和）
        
		cnt[i]+=cnt[i-1];
		rcnt[i]+=rcnt[i-1];
	}
	for(rint i=1;i<=n;++i)
	{
		//cout<<cnt[i]<<" ";
		if(pre[i]>0) ans+=cnt[n]-cnt[i-1];
        	//通过模拟全为正的序列可轻松码出上方语句
		else ans+=rcnt[n]-rcnt[i];
        	//上方为何是n-i，读者自行思考
	}
	cout<<tot-ans<<" "<<ans<<endl;
    //求出正的子段个数，剩下的个数即是负的
    //反之亦然
	return 0;
}
```


---

## 作者：幽界の冥神 (赞：1)

这题就是一道简单DP啊，还卡我10min。

我们设$f_i$表示以$i$结尾为乘积正数的个数，$g_i$表示以$i$结尾为乘积负数的个数，我们就可以推递推式了。

$1.$ 初始化：当$a[i] > 0$,时$f[i] = 1$；否则$g[i] = 1$;

$2.$ 递推：

(1)$a[i] > 0:f[i] += f[i - 1],g[i] +=g[i - 1]$

(2)$a[i] < 0:f[i] += g[i - 1], g[i] += f[i - 1]$

解释一下：若$a[i] > 0$，对子串乘积的正负没有影响，反之会使子串乘积的正负正好相反，本题的转移方程就显而易见了。

$3.$ 答案：累加$g[i]$, $f[i]$即可

上代码：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define N 200005

using namespace std;

int n, a[N], pos[N], tot;
long long f[N], g[N];

int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf ("%d", a + i);
		if (a[i] > 0) f[i] = 1;
		else g[i] = 1;
	}
	for (int i = 2; i <= n; ++i) {
		if (a[i] > 0) {
			f[i] += f[i - 1];
			g[i] += g[i - 1];
		}
		else {
			f[i] += g[i - 1];
			g[i] += f[i - 1];
		}
	}
	long long rg = 0, rf = 0;
	for (int i = 1; i <= n; ++i) {
		rf += f[i];
		rg += g[i];
	}
	printf ("%I64d %I64d\n", rg, rf);
	return 0;
}
```

---

## 作者：zbk233 (赞：0)

## 解题思路

一道动态规划题。

我们用 $z_i$ 表示下标以 $i$ 结尾的乘积为正数的子区间个数，用 $f_i$ 表示下标以 $i$ 结尾的乘积为负数的子区间个数。

输入 $a_i$，若 $a_i>0$ 则 $z_i=1$，若 $a_i<0$ 则 $f_i=1$。

解释：若 $a_i$ 是正数，就必然会组成一个只有自己一个数的，乘积为正数的区间，反之亦然。

若 $a_i>0$，则 $z_i+=z_{i-1},f_i+=f_{i-1}$。

若 $a_i<0$ ，则 $z_i+=f_{i-1},f_i+=z_{i-1}$。

解释：若 $a_i$ 是正数，那么 $a_i$ 乘以正数就一定是正数，乘以负数就一定是负数，所以之前算出来的负数子区间个数不变，正数子区间个数只需要加上由自己一个数组成的子区间就行了。

若 $a_i$ 是负数，那么 $a_i$ 乘以正数就一定是负数，乘以负数就一定是正数，所以之前算出来的正数子区间和负数子区间应该调换位置，并且负数子区间个数需要加上由自己一个数组成的子区间。

最后，将所有的 $z_i$ 和 $f_i$ 分别加起来，就可以得到答案了。

## 参考代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[200005];
int z[200005];
int f[200005];
long long n,ans1,ans2;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]>0?z[i]=1:f[i]=1;
		if(a[i]>0){
			z[i]+=z[i-1];
			f[i]+=f[i-1];
		}
		else{
			z[i]+=f[i-1];
			f[i]+=z[i-1];
		}
		ans1+=f[i];
		ans2+=z[i];
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```


---

## 作者：joelbobo (赞：0)

题目的意思大概是在给定长度为$n$的数列$\left\{ a_n \right\}$，找出所有区间的正负

长度为$n$，也就是说整数区间的数量有$\frac {n(n+1)}{2}$个

### 所以有$O(n^2)$的做法:

$O(n)$统计一个前缀和$negative[i]\ : \ $代表 第$i$个元素之前负数的数量

当$negative[i]\geq 0$时，$negative[i]=negative[i-1]$

当$negative[i] <  0$时,  $  neagtive[i]=negative[i-1]+1$

然后$\Theta (\frac {n(n-1)}2 )$枚举区间端点$(l\leq r)$,如果该区间负数有奇数个，那么区间乘积一定为负

用刚才的前缀和$(negative[r]-neagtive[l-1]) \wedge 1$可以$O(1)$判断

### 在$O(n^2)$的方法基础上改进：

在$O(n)$ 统计前缀和$negative[i]$的时候，我们会发现当$negative[i]$有奇数个负数的时候，一定乘积$<0$,如果有$m$个元素的前缀和都是奇数，那么剩下$n-m$个元素的前缀和必然是偶数->也就是乘积$>0$的，而$negative[j]_{j>i}$有偶数个负数的时候，$[i+1,j]$内一定有奇数个负数（偶-奇=奇），所以根据乘法计数原理，正负得负的区间有$m(n-m)$个，再把本来就是负的$m$个区间加上，那么一共有$m(n-m+1)$个乘积为负的区间，

因为$a_i\neq 0$,所以非正既负，那么正的区间就是$\frac{n(n+1)}{2}-m(n-m+1)$个


可以发现没用到除了$i$之前为奇数个负数的元素以外其他的$negative[i]$，所以可以用一个变量$s$代替

代码如下
```cpp
#include<iostream>
using namespace std;
long long n,a[200005]={};
long long ans=1,s=0;
int main (){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>=0)a[i]=1;
		else a[i]=-1;
	}
	for (int i=1;i<=n;i++){
		ans*=a[i];
		if(ans<0)s++;
	}
	s=s*(n-s+1);
	cout<<s<<" "<<(n*(n+1)/2-s);
} 
```



---

## 作者：Tenshi (赞：0)

# DP

## 分析：

**我们记：相应乘积为负的区间为负区间，反之则为正区间。 同时，区间的右端r记为“尾”**

输入的数组记为a

由问题的特征，我们想到用po（positive）数组来描述正区间的个数，ne（negative）数组来描述负区间的个数，但这是不够的，需要更准确的刻画：

po[i] 表示以 i 为尾的所有正区间的个数

ne[i] 表示以 i 为尾的所有负区间的个数

（我们可以知道：po[i]+ne[i]=i）

进行如下讨论：

①： a[i]>0时

如果以 i+1 为尾的正区间包括着以 i 为尾的正区间，则有p[i-1]个，否则有一个（即a[i]）


```cpp
po[i]=po[i-1]+1;
ne[i]=i-po[i];
```
②： a[i]<0时

类似地，

```cpp
po[i]=ne[i-1];
ne[i]=i-po[i];
```

状态转移方程已经找出，边计算边统计即可：

```cpp
ll cntpo=0,cntne=0;

    FOR(i,1,n){
        if(a[i]>0){
            po[i]=po[i-1]+1;
            ne[i]=i-po[i];
        }else{
            po[i]=ne[i-1];
            ne[i]=i-po[i];
        }
        
        cntne+=ne[i];
        cntpo+=po[i];
    }
```

完整代码：

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define SET0(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define DWN(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
typedef long long ll;
const int N=2e5+5;
ll a[N],po[N],ne[N];
int n;
void scan(){
    cin>>n;
    FOR(i,1,n) cin>>a[i];
}

void solve(){
    ll cntpo=0,cntne=0; //记录

    FOR(i,1,n){
        if(a[i]>0){
            po[i]=po[i-1]+1;
            ne[i]=i-po[i];
        }else{
            po[i]=ne[i-1];
            ne[i]=i-po[i];
        }
        
        cntne+=ne[i];
        cntpo+=po[i];
    }
    cout<<cntne<<' '<<cntpo;
}
int main(){
    scan(); //输入
    solve(); //处理，输出
    return 0;
}
```



---

## 作者：开始新的记忆 (赞：0)

题目大意：给你n个数（都不为0），求其中有多少个子序列的乘积大于0，有多少个子序列的乘积小于0。

大致思路：x代表以当前数结尾的负数乘积个数，y代表以当前数结尾的正数乘积个数。先O（n）扫一遍，如果是正数，那么x就会增加1，如果是负数，那么x和y会互换，并交换后的x增加1，最后在每次判断后负数的个数和正数的个数都得增加。

code：
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans1=0,ans2=0,x=0,y=0;
int a[200010];
int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
	{
		if(a[i]<0)
		{
			swap(x,y);
			++x;
		}
		else
			++y;
		ans1+=x;ans2+=y;
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}
```


---

## 作者：WHFF521 (赞：0)

数的大小无关，只关心**正负**；

发现如果从1到i，如果前缀乘是负的，从1到j，前缀和是正的，其中（i<j），
**那么i+1到j也是负的；**

可以直接记录前缀乘是负数的点的个数cnt，然后他们自己各是一个区间，与其他前缀乘是正数的点之间也是负的，答案就是cnt*(n-cnt)+cnt;(乘法法则)


```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll cnt;
ll n;
ll mul=1;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		ll x;
		scanf("%lld",&x);
		if(x<0) mul*=-1;
		else mul*=1;
		if(mul<0) cnt++; 
	}
	printf("%lld %lld",cnt*(n-cnt+1),n*(n+1)/2-cnt*(n-cnt+1));
	return 0;
}
```


---

## 作者：弦巻こころ (赞：0)

一道简单的dp

题意给了,我们设dp[i][1]为当前处理到第i个数时,有多少个区间乘积为正数.我们设dp[i][2]为当前处理到第i个数时,有多少个区间乘积为负数.那么转移就为

若当前数为正整数

$$
dp[i][1]=2*dp[i-1][1]+1-dp[i-2][1]
$$

$$
dp[i][2]=2*dp[i-1][2]-dp[i-2][2]
$$

若当前数为负整数

$$
dp[i][1]=dp[i-1][1]+dp[i-1][2]-dp[i-2][2]
$$

$$
dp[i][2]=dp[i-1][2]+dp[i-1][1]+1-dp[i-2][1]
$$

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[200005][3];
int pd[200005];
int n;
int x;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x<0)pd[i]=-1;
		else pd[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
    	dp[i][1]+=dp[i-1][1];//转移上一个的答案
      dp[i][2]+=dp[i-1][2];
		if(pd[i]==1)
		{
			
			dp[i][1]++;
			dp[i][1]+=dp[i-1][1];//转移
			dp[i][2]+=dp[i-1][2];
			if(i>=2)
			{
				dp[i][1]-=dp[i-2][1];//减去前面挨不着的
				dp[i][2]-=dp[i-2][2];
			}
		}
		if(pd[i]==-1)//同上
		{
			dp[i][2]++;
			dp[i][1]+=dp[i-1][2];
			dp[i][2]+=dp[i-1][1];
			if(i>=2)
			{
				dp[i][1]-=dp[i-2][2];
				dp[i][2]-=dp[i-2][1];
			}
		}
	}
	cout<<dp[n][2]<<" "<<dp[n][1]<<endl;
    return 0;
}

```
听说CYJian神仙 Rank16上橙了%%%%

---

