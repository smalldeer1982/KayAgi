# Number Circle

## 题目描述

You are given $ n $ numbers $ a_1, a_2, \ldots, a_n $ . Is it possible to arrange them in a circle in such a way that every number is strictly less than the sum of its neighbors?

For example, for the array $ [1, 4, 5, 6, 7, 8] $ , the arrangement on the left is valid, while arrangement on the right is not, as $ 5\ge 4 + 1 $ and $ 8> 1 + 6 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1189B/68eb6130a6cefad8260448b1347c6d6d41d81495.png)

## 说明/提示

One of the possible arrangements is shown in the first example:

 $ 4< 2 + 3 $ ;

 $ 2 < 4 + 3 $ ;

 $ 3< 4 + 2 $ .

One of the possible arrangements is shown in the second example.

No matter how we arrange $ 13, 8, 5 $ in a circle in the third example, $ 13 $ will have $ 8 $ and $ 5 $ as neighbors, but $ 13\ge 8 + 5 $ .

There is no solution in the fourth example.

## 样例 #1

### 输入

```
3
2 4 3
```

### 输出

```
YES
4 2 3 ```

## 样例 #2

### 输入

```
5
1 2 3 4 4
```

### 输出

```
YES
4 4 2 1 3```

## 样例 #3

### 输入

```
3
13 8 5
```

### 输出

```
NO```

## 样例 #4

### 输入

```
4
1 10 100 1000
```

### 输出

```
NO```

# 题解

## 作者：1saunoya (赞：3)

这题相对比较简单 意思是


> $a_i < a[i-1] + a[i + 1]$

> $a[0]=a[n]$  

>$a[n + 1] = a[1]$


如果所有的数字满足 $a_i < a[i-1] + a[i + 1]$
输出YES 或者 NO


这里我们 仔细想想 把最小的放中心 然后两边拓展
假设 n = 5

$a_4\ a_2\ a_1\ a_3\ a_5$

可以证明 如果是YES 这肯定是一种答案

先扫一遍
看一下是不是 YES 

如果有一个不满足的话 直接输出 NO

```cpp

#include <bits/stdc++.h>
#define rep(i,j,n) for(register int i=j;i<=n;i++)
#define Rep(i,j,n) for(register int i=j;i>=n;i--)
#define low(x) x&(-x)
using namespace std ;
typedef long long LL ;
const int inf = INT_MAX >> 1 ;
inline LL read() {
    LL res(0) , f(1) ;
    register char c ;
#define gc c = getchar()
    while(isspace(gc)) ;
    c == '-' ? f = - 1 , gc : 0 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(gc)) ;
    return res * f ;
#undef gc
}
 
int n ;
int a[100000 + 5] ;
int ans[100000 + 5] ;
inline void Ot() {
    n = read() ;
    for(register int i=1; i<=n; i++) a[i] = read() ;
    sort(a + 1 , a + n + 1) ;
    int mid = n + 1 >> 1 ;
    if(n & 1) {
        ans[mid] = a[1] ;
        int cnt = 1 ;
        int l = 0 ;
        int r = 0 ;
        while(cnt <= n - 1) {
            ans[mid - (++ l)] = a[++ cnt] ;
            ans[mid + (++ r)] = a[++ cnt] ;
        }
    } else {
        ans[mid] = a[1] ;
        ans[mid + 1] = a[2] ;
        int cnt = 2 ;
        int l = 0 ;
        int r = 0 ;
        while(cnt <= n - 1) {
            ans[mid - (++ l)] = a[++ cnt] ;
            ans[mid + 1 + (++ r)] = a[++ cnt] ;
        }
    }
    ans[0] = ans[n] ;
    ans[n + 1] = ans[1] ;
    int f = 1 ;
    for(register int i=1; i<=n; i++) {
        if(ans[i] >= ans[i - 1] + ans[i + 1]) f = 0 ;
    }
    if(f) {
        puts("YES") ;
        for(register int i=1; i<=n; i++) cout << ans[i] << ' ' ;
    } else {
        puts("NO") ;
    }
    return ;
}
signed main() {
//  freopen("test.in","r",stdin) ;
    return Ot() , 0 ;
}

```

---

## 作者：zct_sky (赞：2)

### Solution:
-----
先对 $n$ 个数进行排序，如果最大值>=次大值+第三大值，则无法构成，输出 `NO` ，否则就可以构成，将最大值和次大值放在第 1、2 个，将第三大值放在最后一个，然后按照从大到小从第 3 个开始放入即可。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline int read(){//快读，可快了
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
int n,a[100010],b[100010];
int main(){
	n=read();
	for(int i=0;i<n;i++)a[i]=read();
	sort(a,a+n);
	if(a[n-1]>=a[n-2]+a[n-3]){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	b[0]=a[n-1],b[1]=a[n-2],b[n-1]=a[n-3];
	for(int i=n-4;i>=0;i--)
		b[n-2-i]=a[i];
	for(int i=0;i<n;i++)
	    cout<<b[i]<<" ";
	return 0; 
}
```

---

## 作者：AC_Dolphin (赞：2)

我们先对$a$进行排序，如果第三大值+第二大值<=最大值，即$a_{n-2}+a_{n-1}<=a_n$，那么肯定不符合题意，输出`NO`，否则就可以，将第三大、第二大值分别放在最大值的两边，即`swap(a[n-1],a[n])`就可以构造出一个这样的数列。

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
int a[MAXN],n,cnt,m;
template<typename T>
inline void read(T& x){
    int f(1);
    char ch(getchar());
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    x=f*x;
}
int main(){
    read(n);
    for(register int i(1);i<=n;++i) read(a[i]);
    sort(a+1,a+n+1);
    if(a[n-2]+a[n-1]<=a[n]) {cout<<"NO";return 0;}
    swap(a[n-1],a[n]);
    cout<<"YES"<<endl;
    for(register int i(1);i<=n;++i) cout<<a[i]<<" ";
    return 0;
}
```
//之前代码放错，请管理员重新审核

---

## 作者：Zekrom (赞：1)

吐槽：cf竟然不能写 return printf(...)   
导致我第二题疯狂Re    
（希望长点记性）   
题目很简单，排序后最大放中间，左右左右递减    
另外:Re时候 我怀疑有卡快排，所以就加了个random_shuffle    
~~然而还是RE~~   
上代码   
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<ctime>
#include<algorithm>
#define inf 0x3f3f3f3f
#define N 1000010
using namespace std;
int n,a[N],b[N];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{ 
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	random_shuffle(a+1,a+1+n);  
	sort(a+1,a+1+n);
	if(a[n]>=a[n-1]+a[n-2]){
		printf("NO\n");	
	}
	else{
		printf("YES\n");
		b[1]=a[n];
		int l=1,r=n+1;
		for(int i=n-1;i>=1;i--){
			if(i%2)b[++l]=a[i];
			else b[--r]=a[i];
		}	
		for(int i=1;i<=n;i++)
		printf("%d ",b[i]);
	}
	return 0;
}

```


---

## 作者：万弘 (赞：1)

[CF1189(Div.2)题解(全)](https://blog.csdn.net/whsstory/article/details/95317811)

## B. Number Circle

题意:给出一个长为$n(3≤n≤10^5)$的序列$a_1,a_2,a_3...a_n(1≤a_i≤10^9)$.求能否把这n个数摆成一个圆,使每一个数都**严格小于**它左右两个数的和.若能,输出"YES",并打印任意一种方案;若不能,输出"NO".  
题解:考虑构造.  
先把序列排序,使$a_i≤a_{j}(1≤i<j≤n)$那么,只要将$a_i$与$a_{j}$摆在一起,$a_i$就一定符合要求.  
但问题来了,$a_n$怎么办呢?考虑将$a_n$与$a_{n-1},a_{n-2}$摆在一起,如果这样也不行,那么$a_n$一定没办法符合要求了(因为$a_n,a_{n-1},a_{n-2}$是最大的两个)  
所以最后的最优序列(之一)就是$$a_1,a_2...a_{n-4},a_{n-3},a_{n-2},a_n,a_{n-1}$$
(由于是个圆,所以$a_1$与$a_{n-1}$相邻,也是一定合法的)

复杂度瓶颈在于排序,$O(nlogn)$.
```cpp
//Wan Hong 2.2
//notebook
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;//到/**********/之前都是我的板子,之后的代码不再提及
#define INF (1ll<<58)
ll read()//快读,之后不再提及
{
	ll x=0,f=1;
	char c;
	do
	{
		c=getchar();
		if(c=='-')f=-1;
	}while(c<'0'||c>'9');
	do
	{
		x=x*10+c-'0';
		c=getchar();
	}while(c>='0'&&c<='9');
	return f*x;
}
ll min(ll a,ll b)
{
	return a<b?a:b;
}
ll max(ll a,ll b)
{
	return a>b?a:b;
}

/**********/
#define MAXN 100011
ll a[MAXN];
int main()
{
	ll n=read();
	for(ll i=1;i<=n;++i)a[i]=read();
	std::sort(a+1,a+n+1);
	if(a[n]>=a[n-1]+a[n-2])
	{
		std::cout<<"NO";
	}
	else
	{
		std::cout<<"YES"<<std::endl;
		std::swap(a[n],a[n-1]);
		for(ll i=1;i<=n;++i)std::cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：cz666 (赞：0)

## 题意简述：

给你一个数列，求让这个数列每一个数都小于它左边的数和右边的数之和（第 $1$ 个数和第 $N$ 个数看作是相邻的）。

## 具体思路：

让我们把这个数列排成符合要求的，第一个想到的应该就是把这个数列按从小到大的顺序排吧，这样能够保证数列第 $2$ 个到第 $N-1$ 个都能是符合条件的，接下来的关键就是第 $1$ 个和第 $N$ 个的关系了：

如果 $a[1]+a[N-1]<=a[N]$ ，那么我们考虑把第 $N$ 个数和第 $N-1$ 个数的位置换一下，这样就能满足现在的第 $N$ 个数以及第 $1$ 个数一定符合条件了。

但是我们又发现这样做或许会导致 $a[N-2]+a[N]<=a[N-1]$ 。那么这样怎么办呢？总不可能一直向前换过去吧 $......$ ，其实如果出现了这个情况，那么就可以直接输出 $NO$ 了。因为如果最大三个都无法满足条件，那么剩下比它们小的更加无法完成了。

所以这题就只要先对数列排序，再考虑清楚上面的两个分支，就能完成了。下面是通过了的代码。

## AC代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);puts("");}
inline void wlk(int x){write(x);printf(" ");}
#undef dd
int n,a[100003];
inline bool cmp(int x,int y){return x<y;}
signed main(){
	int n=read();
	for (register int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1,cmp);
	if (a[1]+a[n-1]<=a[n]){
		swap(a[n-1],a[n]);
		if (a[n-2]+a[n]<=a[n-1]) return puts("NO"),0;
	}
	puts("YES");
	for (register int i=1;i<=n;++i) wlk(a[i]);
	return puts(""),0;
}
```

---

## 作者：世末OIer (赞：0)

假设最大值为a，次大的两个数为b,c
现在让b在a左边，c在a右边，[0......a的位置]按照从小到大排列，[a的位置...n]按照从大到小排列。

如果b+c还是<=a，那么剩下的无论什么数都不能满足要求，输出"NO"

反之，剩下来的数，可以保证，左边或者右边总会有一个数大于等于它。又因为所有的数都是>=1的，所以这个数的左边+右边就一定大于它了。

```cpp
int a[100005],b[100005],n;
signed main(){
	int i,j;
	rdi(n);
	for(i=1;i<=n;++i) rdi(b[i]);
	sort(b+1,b+n+1);
	int lo=1,hi=n,tm=0;
	for(i=1;i<=n;++i){
		if(tm==0) a[lo++]=b[i];
		else a[hi--]=b[i];
		tm=1-tm;
	}
	a[0]=a[n];
	a[n+1]=a[1];
	for(i=1;i<=n;++i) if(a[i]>=a[i-1]+a[i+1]){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	for(i=1;i<=n;++i) cout<<a[i]<<' ';
	cout<<endl;
}
```

---

## 作者：Meatherm (赞：0)

这道题目直接把我从$specialist$变成了$pupil$。

比赛的时候，一看到这个题就想起了各种乱七八糟的指针链表。$150$分没了。

事实上远没有那么复杂。

设$b[]$为排序之后的数组。

首先，若$b[n-2]+b[n-1]\leq b[n]$，那么无解。

否则将$b[n-1]$放在$b[n]$的左侧，$b[n-2]$放在$b[n]$的右侧，将$b[n-3]$放在$b[n-1]$的左侧。以后，$b[i]$放在$b[i+1]$的左侧$(i \geq 1)$。最后连接$b[n-2]$和$b[1]$。这样一定能符合题目要求。

证明：

- 对于$b[n]$，由于不会出现无解的情况（前面判断过了），那么$b[n-1]+b[n-2]>b[n]$，合法。

- 对于$b[n-1]$和$b[n-2]$，由于它们都小于$b[n]$，且另一个相邻的数$>0$，则$b[n-1]$和$b[n-2]$旁边两个数的和必定大于它本身，所以也合法。

- 对于$b[i](1 \leq i \leq n-3)$，由于它被放在$b[i+1]$的左侧，且$b[i+1]\geq b[i],b[i-1]$（如果$i=1$则是$b[n-2]$）$>0$，则$b[i]<b[i+1]+b[i-1 \space or \space (n-2)]$。

```
# include <bits/stdc++.h>
# define rr register
const int N=100010;
int a[N];
int b[N];
int n;
int main(void){
	scanf("%d",&n);
	for(rr int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	std::sort(b+1,b+1+n);
	if(b[n-2]+b[n-1]<=b[n]){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(rr int i=1;i<=n-1;++i){
		if(i==n-2)
			continue;
		printf("%d ",b[i]);
	}
	printf("%d %d",b[n],b[n-2]);
	return 0;
}
```

---

## 作者：F1aMiR3 (赞：0)

题意大概就是有 $n$ 个数，你要把它们排成一圈，使得每个数都小于与它相邻的两个数和

设此序列从小到大排列后为 $s_1,s_2,s_3,...,s_n$ 

若 $s_n\ge s_{n-1}+s_{n-2}$ ，那么显然它是无法构造出的（因为 $s_n$ 两边的数和一定小于等于 $s_n$ ）

若 $s_n<s_{n-1}+s_{n-2}$ ，那么我们一定可以构造出一个满足条件序列

除了 $s_n$ 之外只需保证每个数旁边都有一个比它大的数

我们可以这么构造 $\cdots,s_{n-5},s_{n-3},s_{n-1},s_n,s_{n-2},s_{n-4},s_{n-6},\cdots$

这样每个数一定满足条件

代码~~，应该浅显易懂吧（逃~~

```cpp
#include <deque>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
deque<int> ans;
int n,a[100001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    if(a[n-1]+a[n-2]<=a[n]){printf("NO");return 0;}
    ans.push_front(a[n]);
    for(int i=n-1;i>=1;--i)
    {
        int dir=(n-i)&1;
        if(dir)ans.push_front(a[i]);
        else ans.push_back(a[i]);
    }
    printf("YES\n");
    while(!ans.empty())
    {
        printf("%d ",ans.front());
        ans.pop_front();
    }
    return 0;
}
```

---

