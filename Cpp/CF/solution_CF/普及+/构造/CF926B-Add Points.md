# Add Points

## 题目描述

There are $ n $ points on a straight line, and the $ i $ -th point among them is located at $ x_{i} $ . All these coordinates are distinct.

Determine the number $ m $ — the smallest number of points you should add on the line to make the distances between all neighboring points equal.

## 说明/提示

In the first example you can add one point with coordinate $ 0 $ .

In the second example the distances between all neighboring points are already equal, so you shouldn't add anything.

## 样例 #1

### 输入

```
3
-5 10 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
100 200 400 300 600 500
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
10 9 0 -1
```

### 输出

```
8
```

# 题解

## 作者：Luo_gu_ykc (赞：3)

## 题目大意

给你一个长度为 $n$ 的序列，将这 $n$ 个数放在数轴上，你需要在数轴上加一些点，使得每两个相邻的点长度相同。

## 思路

要使长度相同，明显我们可以先求默认的 $n$ 个点的每两个相邻点的距离。

这时候我们转化一下题意，看成将每两个相邻点之间的距离平均分为几段，使得每段的长度相同，要使得分的段最少即可。

那么我们使得分的段越少，那么其实就是每段之间的长度越长越好，但是每两个相邻点之间的距离都要整除这个长度，其实就能转化成求每两段相邻点的距离的最大公约数。

那么其实问题就已经解决了，但是我们要注意，要求的是需要加的点数，所以最后要算出这两个相邻点之间被分成了多少段，加的点数明显为段数减一；

## Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 5;

int n, a[N];

int gcd(int x, int y){ // 欧几里得算法求 gcd
	return y == 0 ? x : gcd(y, x % y);
} // 当然可以用 C++ 自带的 __gcd 函数

signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n); // 序列不保证有序，自然需要排序
	int k = a[2] - a[1];
	for(int i = 3; i <= n; i++){
		k = gcd(k, a[i] - a[i - 1]); // 求出每两个相邻点距离的最大公约数
	}
	int sum = 0;
	for(int i = 2; i <= n; i++){
		sum += ((a[i] - a[i - 1]) / k) - 1; // 算出段数
	}
	cout << sum;
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

## 思路

简化一下题意，其实就是求在一个序列中最少加入多少个数，能使其变为一个等差数列。

先把原数组排序，然后我们就要想办法求出最后组成的等差数列的公差，其实就是求一个最大的 $mn$ 使得每一组 $a_i-a_{i-1}$ 都是 $mn$ 的整数倍，$mn$ 其实就是所有 $a_i-a_{i-1}$ 的最大公因数。这时候算出这个等差数列的项数 $\frac{a_n-a_1}{mn}+1$，最后减去原来有的数的个数即可，最后答案即为 $\frac{a_n-a_1}{mn}+1-n$。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=300050;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n;
int mn;

int a[maxn];

int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++){
		mn=gcd(mn,a[i]-a[i-1]);
	}
	write((a[n]-a[1])/mn-n+1);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}


```

---

## 作者：cppcppcpp3 (赞：0)

[传送门。](https://www.luogu.com.cn/problem/CF926B)

## Solution

首先对 $a_i$ 排序。令 $d_i=a_i-a_{i-1}$。

显然新的点都要插入到两个原来的点之间，意味着每个 $d_i$ 都将会被平均分成若干份，不妨设 $d_i=k_it_i$，其中 $t_i$ 为新的相邻点之间的距离，可知 $t_i$ 为 $d_i$ 的因数。现在要使所有 $t_i$ 都相等，同时插入点数尽量少，即 $t$ 尽量大，则 $t=\gcd\limits_{i=2}^{n}d_i$。

于是除去 $a_1$ 一点的总点数为 $\dfrac{a_n-a_1}{t}$，插入点数为 $\dfrac{a_n-a_1}{t}-(n-1)$。 

复杂度 $O(n\log n)$，在于排序。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,d,a[N];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd();
	sort(a+1,a+n+1),d=a[n]-a[n-1];
	for(int i=2;i<n;++i) d=__gcd(d,a[i]-a[i-1]);
	return printf("%lld",(a[n]-a[1])/d-(n-1)),0; 
}
```

---

## 作者：Szr__QAQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF926B)


------------
**题意**：

在一条数轴上有 $n$ 个点，已知每个点所代表的数，现在需要添加若干个点，要求添加的点的个数最小，使 **相邻的两个点的距离全部相同**。


------------
**思路**：

看到 **相邻的两个点的距离全部相同** 这句话时，就不难想到一个数学知识，就是 **等差数列**，所以题目就是让我们将一条数列分割成相等的若干个区间，使给出的点都是该数列的 $x$ 等分点。这样，我们只需要 **将原数列从小到大排序，再用一个数组求出并存储两两相邻点之差，最后求所有差值的最大公约数** 就能完成该题了。

那为何求出每个差值的最大公约数就可以了呢，我们不妨设每个差值的最大公约数为 $m$，这样，**每两个相邻的点的距离就一定是** $m$ **的** $k$ **倍**，且各个 k 的最大公约数为 $1$，所以，只要插入 **差值除以 $m$ 再减去 $1$** 个点即可。

------------
小芝士：
```cpp
C=__gcd(A,B); //__gcd用于求出数A与数B的最大公约数，即数C
```


------------
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int qwq=2e6+5;
int n,k,a[qwq],ans[qwq];
//ans数组存储数列中相邻两个数的距离 

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	k=a[n]-a[1];
	for(int i=2;i<=n;i++)
	{
		ans[i]=a[i]-a[i-1];
	}
	for(int i=2;i<=n;i++)
	{
		ans[i]=__gcd(ans[i],ans[i-1]);
	}
	int QAQ=1+k/ans[n]-n;
   	cout<<QAQ<<endl;
	return 0;
}
```


------------

本人只是一名小蒟蒻，若有错误请指正，谢谢大家。

---

## 作者：Milthm (赞：0)

## CF926B 题解

### 题目解法

这题十分简单，首先从小到大排序数列，求出所有相邻两个数差值的最大公因数，得到最后每个数的差。（即等差数列完整情况下的公差）


然后，根据等差数列项数公式，项数就是 $\frac{(a_n-a_1)}{n}+1$。接着用项数再减去数列中已经有的数字个数，得到没有存在在数列中的数字，就是最终的结果。

### AC代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int gcd(int x,int y){//最大公因数可参考
    if(x%y==0)return y;
    return gcd(y,x%y);
}
int n,a[1000005],f[1000005],ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<n;i++){
        f[i+1]=gcd(f[i],a[i+1]-a[i]);//求出最大公因数
    }
    ans=(a[n]-a[1])/f[n]+1;//求出理论最大值
    for(int i=1;i<=n;i++){
        if((a[i]-a[1])%f[n]==0)ans--;//如果重复了就减一
    }
    cout<<ans;//输出答案
    return 0;
}
```


---

## 作者：lovely_hyzhuo (赞：0)

题意简述：给出 $n$ 个点的坐标，求最少添加几个点，是的两两相邻点距离相等。

首先，题目中提到，

我们最后的序列**一定是以现在的坐标最大点和现在的坐标最小点为左右端点的，才能达到最小。**

所以我们只需先将原数组从小到大排，求出两两数据之差，求差的最大公约数即可。

正确性证明：假设 $k$ 是每个差值的最大公约数，那么每两个点之间的距离一定是 $k$ 的倍数，因而插入差值 $/k-1$ 个点，一定可以把每个区间分成相等的几部分。因为 $n$ 的范围很小，所以这样不会超时。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],c[1000010];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	int t=a[n-1]-a[0];
	for(int i=1;i<n;i++)
	{
		c[i]=a[i]-a[i-1];
	}
	for(int i=1;i<n;i++)
	{
		c[i]=__gcd(c[i],c[i-1]);
	}
    cout<<t/c[n-1]-n+1;
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意:给你n个点的坐标（在同一直线上），现在你需要添加若干个点，使得相邻两个点的距离都相等。

大致思路：因为我们最后的数列肯定是以给出的最左边和最右边当一个区间的，我们只需先从小到大排，算出每相邻两个点的距离，然后求出n-1个距离的最大公约数即可

```
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010];
int main()
{   int n,m;
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    sort(a+1,a+n+1);
    m=a[n]-a[1];
    for(int i=2;i<=n;++i)
        b[i]=a[i]-a[i-1];
    for(int i=2;i<=n;++i)
        b[i]=__gcd(b[i],b[i-1]);
    cout<<m/b[n]-n+1<<endl;
    return 0;
}
```


---

## 作者：AuCloud (赞：0)

~~一道尚未评定的水题~~

[更好的](https://fkx4-p.top/?p=46)[阅读体验](https://www.cnblogs.com/H2SO4/p/11341161.html)

# 思路
来分析分析样例：
```cpp
3
-5 10 5
```
![](https://cdn.luogu.com.cn/upload/pic/71475.png)

我们把它升序排列，会得到这个东西↑

~~不~~仔细地观察后可以发现：加一个（0，0）的点显然是最优的

再~~用脚趾头~~想想为什么，我们发现，这题题意就是想让我们把一段线段x等分，使得给出的点都是它的x等分点。

而通过我们的~~敏锐的第六感~~做题经验，不难看出最优解即*相邻点距离的最大公约数*

# 做法
显然此题难点在于求n个数的gcd

而要求多个数的gcd，两两求之后合并即可。

证明：

以三个数为例，设有a,b,c三数，x=gcd(a,b),y=gcd(x,c)，因为a%x=0，x%y=0，所以a%y也等于零，且y是符合条件的最大值。

所以我们可以递推求n个长度的gcd，然后出解即可
# 代码
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int a[100001];
int b[100001];
int main()
{
    int n;
    cin >> n;
    for ( int i = 1; i <= n; i++ )
    {
        cin >> b[i];
    }
    sort ( b + 1, b + n + 1 );
    for ( int i = 2; i <= n; i++ )
        a[i] = b[i] - b[i-1];
    int dis = b[n] - b[1];
    for ( int i = 2; i <= n; i++ )
    {
        a[i] = __gcd( a[i], a[i-1] );
        //在<cmath>里的神奇函数（妈妈再也不用担心我不会辗转相除啦！）
    }
    cout << dis / a[n] - n + 1;
    /*此时的a[n]即为最优的线段长度，dis/a[n]为线段个数，
    再加1是点的个数，最后减去原有的n个点，输出*/
    return 0;
}

```
完美收官（~~你们没发现开头的链接是两个吗~~）

---

## 作者：A_Đark_Horcrux (赞：0)

思路非常好想：只要找出每对相邻的点距离差的最大公约数k，然后在每对点之间插入 差值/k-1个点。即可满足要求。

拿样例举例：

```cpp
3

-5 10 5
```
先排序：
```cpp
-5 5 10
```
$\text{5-(-5)=10，10-5=5，}$10和5的最大公约数是5，所以在-5和5间插入$\text{10/5-1}$，也就是一个点；在5和10之间插入$\text{5/5-1}$，也就是0个点，所以一共插入1个点。

正确性也很明显：既然k是每个差值的最大公约数，那么每两个点之间的距离一定是k的倍数，因而插入 差值/k-1个点，一定可以把每个区间分成相等的几部分。n<=100000，所以这样不会超时。

附代码！


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int gcd(int x,int y) {return x%y?gcd(y,x%y):y;}//求最大公约数
int n,s,k,i,a[100001];//n:点数，s:要加入的点数，k:最大公约数
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序
	for(i=2;i<=n;i++) k=gcd(k,a[i]-a[i-1]);//找最大公约数
	for(i=2;i<=n;i++) if(a[i]-a[i-1]>=k) s+=(a[i]-a[i-1])/k-1;//s+=每一段要加入的点的个数
	printf("%d",s);
	return 0;
}
```


---

