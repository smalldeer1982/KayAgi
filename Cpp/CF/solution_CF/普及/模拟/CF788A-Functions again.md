# Functions again

## 题目描述

Something happened in Uzhlyandia again... There are riots on the streets... Famous Uzhlyandian superheroes Shean the Sheep and Stas the Giraffe were called in order to save the situation. Upon the arriving, they found that citizens are worried about maximum values of the Main Uzhlyandian Function $ f $ , which is defined as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788A/3dafed09a51e28ade00bc9bec53248a85d7ce6d3.png)In the above formula, $ 1<=l&lt;r<=n $ must hold, where $ n $ is the size of the Main Uzhlyandian Array $ a $ , and $ |x| $ means absolute value of $ x $ . But the heroes skipped their math lessons in school, so they asked you for help. Help them calculate the maximum value of $ f $ among all possible values of $ l $ and $ r $ for the given array $ a $ .

## 说明/提示

In the first sample case, the optimal value of $ f $ is reached on intervals $ [1,2] $ and $ [2,5] $ .

In the second case maximal value of $ f $ is reachable only on the whole array.

## 样例 #1

### 输入

```
5
1 4 2 3 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 5 4 7
```

### 输出

```
6```

# 题解

## 作者：mulberror (赞：5)

$$\href{https://www.chhokmah.top/}{\Large\texttt{My blog}}$$

---
# Functions again
> Link：[CF](http://codeforces.com/problemset/problem/788/A)  

给你一个函数和一个序列，让你求在这个序列上这个函数的最大值。    
函数为以下：  

$$f(l,r)=\sum^{r-1}_{i=l}|a_i-a_{i+1}|\times (-1)^{i-l}$$
## Solution
一眼动态规划。  
我们可以发现绝对值里面的东西可以先预处理出来。  
把差分写出来。  
然后看一下这个函数是如何构造出来的。  
可以发现，这个函数是形如$+-+-$的构造方式。  
那么我们就考虑动态规划
$f[i][0..1]$表示以$i$为结尾，$0$为第$i$位为$+$，$1$为$-$号。
类似于最大子段和的做法。  
相邻两项很显然是不同号的。  
得到以下的转移方程
$$f[i][0]=max(f[i-1][1]+d[i],d[i])$$
$$f[i][1]=max(f[i-1][0]-d[i],0)$$
然后从$1~n-1$遍历最大值就可以了。
我们机房好像有大佬用$O(nlogn)$做法过掉的，我来口胡以下。

---
**以下为SB现场**
参考以上的思路，对于$+-$两个号建立一个线段树，然后在查询的时候递归合并求解。  
时间复杂度为$O(nlogn)$。

~~吐槽一句，楼上的代码太长了。。~~
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0; T fl = 1; char ch = 0;
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1; 
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48); 
    x *= fl; 
}
typedef long long ll;
const int N = 1e5 + 5;
int n;
ll a[N], d[N], f[N][2];
ll ans = 0; 
int main() {
    read(n);
    for (int i = 1; i <= n; i ++) read(a[i]);
    for (int i = 1; i <= n; i ++) d[i] = abs(a[i] - a[i + 1]); 
    for (int i = 1; i <= n; i ++) {
        f[i][0] = max(f[i - 1][1] + d[i], d[i]);
        f[i][1] = max(f[i - 1][0] - d[i], 0ll);
    }
    for (int i = 1; i < n; i ++) ans = max(ans, max(f[i][0], f[i][1]));
    printf("%lld\n", ans);
    return 0; 
}
```

---

## 作者：Erotate (赞：1)

### Solution

显然,我们可以预处理出每两个元素之间的差的绝对值,并用数组 $d$ 来储存。然后我们考虑 dp。

我们定义 $f_{i,j} (j=0,1)$ 为以 $i$ 为结尾并且第 $i$ 位的符号为 $j$ （当 $j$ 为 0 时，符号为正，否则为负）的最大值。

那么，我们就可以写出状态转移方程了：

$$f_{i,0}= \max(f_{i-1,1}+d_i,d_i)$$

$$f_{i,1}= \max(f_{i-1,0}-d_i,0)$$

最后统计一下答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,a[N],d[N],f[N][2],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=n;++i) d[i]=abs(a[i]-a[i+1]);
	for(int i=1;i<=n;++i){
		f[i][0]=max(d[i],f[i-1][1]+d[i]);
		f[i][1]=max(0LL,f[i-1][0]-d[i]);
	}
	for(int i=1;i<n;++i) ans=max(ans,max(f[i][1],f[i][0]));
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：OIerJiang_1017 (赞：0)

## [CF788A 题目传送门](https://www.luogu.com.cn/problem/CF788A)

## 题目大意
定义一个函数，函数如下：$f(l,r) = \sum\limits_{i = l}^{r - 1 }|a_i−a_{i+1}| \cdot (−1)^{i−l}$，而 $1 \leq l \leq r \leq n$，其中 $n$ 是数组 $a$ 的大小，$|x|$ 表示 $x$ 的绝对值。现在给你一个函数，请取恰当的 $l,r$ 使 $f$ 值最大，并输出最大的 $f$ 值。

## 解决思路
直接考虑**动态规划**，令 $f_{i,0}$ 表示以 $i$ 为结尾，第 $i$ 位为 $+$ 号；令 $f_{i,1}$ 表示以 $i$ 为结尾，第 $i$ 位为 $-$ 号。然后通过计算两个相邻的数的差值，存入数组 $dp$，随后用得到的**状态转移方程**求出最大值。
```cpp
f[i][0] = max(dp[i], f[i - 1][1] + dp[i]);
f[i][1] = max(0ll, f[i - 1][0] - dp[i]);
//状态转移方程求最大值
```
最后再来一重循环求答案的最大值即可。

### 注意事项
$-10^9 \leq a_i \leq 10^9$，需要开 `long long`。

## 代码展示
```cpp
#include <iostream>
#define ll long long
//不开long long见祖宗
using namespace std;

const int N = 1e5 + 10;
ll n, a[N], dp[N];
ll f[N][2], ans;
//f[i][j]表示以i为结尾并且第i位的符号为j

int main()
{
	scanf("%lld", &n);//建议scanf,更快
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		dp[i] = abs(a[i] - a[i + 1]);//简化公式，加快速度
	for(int i = 1; i <= n; i++)
	{
		f[i][0] = max(dp[i], f[i - 1][1] + dp[i]);
		f[i][1] = max(0ll, f[i - 1][0] - dp[i]);
		//状态转移方程求最大值
	}
	for(int i = 1; i < n; i++) //求最大值 
		ans = max(max(f[i][0], f[i][1]), ans);
	printf("%lld\n", ans);//建议printf,更快
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

# [CF788A](https://www.luogu.com.cn/problem/CF788A) [Functions again](https://codeforces.com/problemset/problem/788/A)

## 题意

给定长度为 $n$ 的序列 $a$，对于任意的 $1\le l<r\le n$，定义

$$f(l,r)=\sum_{i=l}^{r-1}\left((-1)^{i-l}\cdot|a_{i+1}-a_i|\right)$$

求 $\max\limits_{1\le l<r\le n}\{f(l,r)\}$。

$n\le10^5,|a_i|\le10^9$。

## 题解

首先注意到 $a$ 数组本身是没用的。可以直接差分，令 $a'_i=|a_{i+1}-a_i|$。

再看看 $f$ 函数，求的本质上就是 $a'$ 数组的“另类的”最大子段和。

只不过正负号还需要处理一下，因为其元素的正负可能变化。

注意到如果 $l$ 是奇数（或偶数），整个数列就已经确定了。

那么我们对 $l$ 的奇偶性分类，分别跑一个最大子段和即可。（不会最大子段和的戳[这里](https://www.luogu.com.cn/blog/lzy-lzy/qiu-ou-jian-zui-tai-zi-duan-hu)）

时间复杂度 $\Theta(n)$。记得答案开 `long long`。

## 代码实现

```cpp
const int N=100005;
int n,a[N];
void Solve(int CASE)
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)a[i]=abs(a[i+1]-a[i]);
	ll ans1=0,ans2=0,t=0,mi=0;
	for(int i=1;i<n;i++)//奇数位开始 奇加偶减
	{
		if(i&1)t+=a[i],ans1=max(ans1,t-mi);
		else t-=a[i],mi=min(mi,t);
	}
	t=mi=0;
	for(int i=2;i<n;i++)//偶数位开始 奇减偶加
	{
		if(!(i&1))t+=a[i],ans2=max(ans2,t-mi);
		else t-=a[i],mi=min(mi,t);
	}
	cout<<max(ans1,ans2);
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
定义一个函数，函数如下：
$f[l,r]=\sum^{r-1}_{i=l}|a_i-a_{i+1}|\times (-1)^{i-l}$. ($1\le l,r\le n$)  
$|x|$ 表示 $x$ 的绝对值.  
现在给你一个函数，请取恰当的 $l,r$ 使 $f$ 值最大，请输出最大的 $f$ 值.  
$2\le n\le 10^5$
## $\text{Solution}$
先求出差分数组的绝对值 $d_{1...n-1}$.  
定义：
$$sum_i=\sum_{j=1}^i d_j\times(-1)^{j+1}$$
那么我们的 $f_{l,r}$ 就可以表示为：  
$$(-1)^{r+1}\times (sum_r-sum_{l-1})$$
所以从前往后扫分别记录 $sum$ 的最大值和最小值即可.
## $\text{Description}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

ll n,m,k;
ll x[N],a[N],sum[N];
ll mn,mx,ans;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) x[i]=read();
  for(int i=1;i<n;i++) a[i]=abs(x[i]-x[i+1])*((i&1)?1:-1);
  for(int i=1;i<n;i++){
    sum[i]=sum[i-1]+a[i];
    if(i&1) ans=max(ans,sum[i]-mn);
    else ans=max(ans,mx-sum[i]);
    mx=max(mx,sum[i]);mn=min(mn,sum[i]);
  }
  printf("%lld\n",ans);
  return 0;
}
/*

*/

```


---

## 作者：xzggzh1 (赞：0)

不是很理解为啥有的题解都是动态规划做的，还有一个带 $\log$ 的……

---

题意：

给定 $n$ 个数，求

$$\large f[l,r]=\sum^{r-1}_{i=l} | \ a[i]-a[i-1] \ | \times (-1)^{i-l} $$

的最大值。

---

首先，这个 $f$ 的值和原来的 $a$ 并没有关系，我们只需考虑其差分数组的绝对值即可。

当你把这个转换过了的数组搞出来， 就会发现对于取的区间就是所有奇数位取正，然后偶数位取负的和，对于每个起始位奇偶性相同的区间，他们其实用的都是同一个数组。

然后你会发现，其实题目就转换为求分别两个数组的最大子序列和，其中一个数组原差分数组的绝对值在奇数位取负，一个是在偶数位取负。

最大子序列和就只要贪心就好了。

具体实现也简单，可以看代码。

---

```cpp
#define int long long 
const int Maxn=1e5+5;
inline int R(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
} 
int d2[Maxn],d[Maxn],d1[Maxn],a[Maxn];
signed main() {
	int n=R();
	for(int i=1;i<=n;i++)
	{
		a[i]=R();
		if(i>1) d[i]=abs(a[i]-a[i-1]);
	}
	for(int i=2;i<=n;i++)
	{
		d1[i]=d2[i]=d[i];
		if(i%2) d1[i]=-d[i];
		else d2[i]=-d[i];
	}
	int ans=0,now=0;
	for(int i=2;i<=n;i++)
	{
		now+=d1[i];
		if(now<0)now=0;
		else ans=max(now,ans);
	}
	ans=max(now,ans);now=0;
	for(int i=2;i<=n;i++)
	{
		now+=d2[i];
		if(now<0)now=0;
		else ans=max(now,ans);
	}
	ans=max(now,ans);now=0;
	printf("%lld\n",ans);
}

```
 

---

## 作者：泠小毒 (赞：0)

# T3-Functions again
定义一个函数，函数如下：$f[l,r]=\sum_{i=l}^{r-1}|a_i-a_{i-1}|\times(-1)^{i-l}$

|x|表示x的绝对值。现在给你一个函数，请取恰当的l,r使f值最大，请输出最大的f值
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190507/)
## 解法
先把差分数组都求出来，同机房大佬都是O(n)动规做的，好像是最大子串和

我呢，菜的要死，只能nlogn做，用一个堆和链表来维护，每次找出最小的点，把它设为负，合并两边的，将三个点合并成一个点，在途中统计一下最大的答案
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,del[100010],ll[100010],rr[100010];
long long a[100010],ans=0;
struct node{int num;bool operator<(const node&x)const{return a[num]>a[x.num];}};
priority_queue<node>q;
int main()
{
	scanf("%d",&n),l=1,r=n-1;
	for(int i=1;i<=n;i++)cin >> a[i];
	for(int i=1;i<n;i++)a[i]=abs(a[i]-a[i+1]),q.push({i}),ll[i]=i-1,rr[i]=i+1;
	while(!q.empty()&&l<=r)
	{
		while(l<=r&&del[l])l++;
		while(l<=r&&del[r])r--;
		node u=q.top();
		q.pop(),ans=max(ans,a[u.num]);
		if(del[u.num])continue;
		if(u.num==l)
		{
			del[l]=1,ll[rr[l]]=0;
			while(l<=r&&del[l])l++;
			continue;
		}
		if(u.num==r)
		{
			del[r]=1,rr[ll[r]]=0;
			while(l<=r&&del[r])r--;
			continue;
		}
		a[u.num]=a[ll[u.num]]+a[rr[u.num]]-a[u.num],del[ll[u.num]]=del[rr[u.num]]=1;
		ll[u.num]=ll[ll[u.num]],rr[u.num]=rr[rr[u.num]],rr[ll[u.num]]=ll[rr[u.num]]=u.num;
		q.push(u);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：liuyifan (赞：0)

## DP
如果奇数位开始，那么奇数位必为正，偶数位必为负

反之，如果从偶数位开始，那么偶数位必为正，奇数位也必为负

只要分奇偶循环各自走一遍，求最大和就好了

code：
```cpp
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
ll a[100005],f[100005][2],ans,n;
int main()
{
    scanf("%lld",&n);
    for(reg int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(reg int i=1;i<n;i++)a[i]=abs(a[i]-a[i+1]);//预处理
    f[1][1]=a[1];
    ans=a[1];//初始化
    for(reg int i=2;i<n;i++)
	{
        if(i&1)//等价于i%2，位运算
		{
            f[i][0]=f[i-1][0]-a[i];
            f[i][1]=max(a[i],f[i-1][1]+a[i]);//分奇偶数位处理
            ans=max(ans,max(f[i][0],f[i][1]));
        }
        else
		{
            f[i][0]=max(a[i],f[i-1][0]+a[i]);
            f[i][1]=f[i-1][1]-a[i];
            ans=max(ans,max(f[i][0],f[i][1]));
        }//同上
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

