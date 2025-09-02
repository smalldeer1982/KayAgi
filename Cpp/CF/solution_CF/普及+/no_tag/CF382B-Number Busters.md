# Number Busters

## 题目描述

Arthur and Alexander are number busters. Today they've got a competition.

Arthur took a group of four integers $ a,b,w,x $ $ (0<=b&lt;w,0&lt;x&lt;w) $ and Alexander took integer $ с $ . Arthur and Alexander use distinct approaches to number bustings. Alexander is just a regular guy. Each second, he subtracts one from his number. In other words, he performs the assignment: $ c=c-1 $ . Arthur is a sophisticated guy. Each second Arthur performs a complex operation, described as follows: if $ b>=x $ , perform the assignment $ b=b-x $ , if $ b&lt;x $ , then perform two consecutive assignments $ a=a-1; b=w-(x-b) $ .

You've got numbers $ a,b,w,x,c $ . Determine when Alexander gets ahead of Arthur if both guys start performing the operations at the same time. Assume that Alexander got ahead of Arthur if $ c<=a $ .

## 样例 #1

### 输入

```
4 2 3 1 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2 3 1 7
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1 2 3 2 6
```

### 输出

```
13
```

## 样例 #4

### 输入

```
1 1 2 1 1
```

### 输出

```
0
```

# 题解

## 作者：_edge_ (赞：2)

没人发题解？

感觉我的做法好麻烦，用官方题解来推推柿子就很快能解决了。

先来说一下我的做法吧。

首先，对于 $c\le a-3000$ 的情况，我们可以直接进行暴力处理，复杂度大概也是可以接受的。

然后就是比较大的情况，其实我们可以发现这个东西肯定是有一个循环节的，并且这个循环节是在 $1000$ 的范围之内，因为总共就 $1000$ 个数。

我一开始以为这个 $b$ 就是这个循环节的头结果越写越不对，总的来说，就是 $b$ 会先到一段不循环的，然后再到循环节，类似于基环树一样。

为了避免在没到循环的时候就结束，我加了上面的特判。

对于有循环节的，我们可以记录循环节内 $c$ 减少的次数以及经过的秒数。

然后这个东西我们可以直接对他二分，形式化就是 $c-ans \times sum >a$ 其中 $ans$ 要最大，$sum$ 为循环节内 $c$ 减少的次数。

然后对于零散开的，即循环节只有一段的，范围不超过 $1000$ 可以直接暴力找。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=1e3+5;
int a,b,w,x,c,f[INF],sum,sum1,ans,f1[INF],iu;
void DFS(int y) {
//	cout<<y<<" endl\n";
	if (f[y]) {ans+=f[y];c-=f1[y];sum-=f[y];sum1-=f1[y];iu=y;return ;}
	f[y]=sum;f1[y]=sum1;
	if (y>=x) {sum1++;sum++;DFS(y-x);}
	else sum++,DFS(w-(x-y));
	return ;
}
void DFS1(int y) {
//	cout<<y<<" "<<c<<" "<<a<<" endl\n";
	if (c<=a) return ;
	ans++;
	if (y>=x) {c--;DFS1(y-x);}
	else DFS1(w-(x-y));
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>a>>b>>w>>x>>c;
	if (c-a<=3000) {DFS1(b);cout<<ans<<"\n";return 0;}
	DFS(b);
//	cout<<sum1<<" "<<sum<<" endl\n";
//	while (c-sum1>a) c-=11111sum1,ans+=sum;
	int l=0,r=1e15,ans1=0;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (c-Mid*sum1>a) l=(ans1=Mid)+1;
		else r=Mid-1;
//		cout<<l<<" "<<r<<" "<<c-Mid*sum1<<" "<<ans1<<" "<<" pp\n";
	}
//	cout<<ans1<<" "<<sum1<<" "<<ans1*sum<<" "<<" oo\n";
	c-=sum1*ans1;ans+=ans1*sum;
//	cout<<c<<" "<<a<<" kkk\n";
	memset(f,0,sizeof f);
	DFS1(iu);cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：_txb_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF382B)

## 思路：
只要 $c$ 还小于 $a$ 时，就要执行操作，
- $a$ 大于等于 $x$ 时，$b=b-1$，$c=c-1$。
- $a$ 小于 $x$ 时，$a=a-1$，$c=c-1$，$b=w-x+b$。

如果 $c$ 大于 $a$，就直接退出循环，并且每一次循环时答案都加一，其他几位题解也是这样的思路，但都无法通过，我们可以把它转化为数学，不用循环。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,ans,a,b,c,w,x,t;
int main()
{
	cin>>a>>b>>w>>x>>c; 
    sum=(long long)a*w+b;//求出1项 
    ans=(long long)c*w;//求出2项 
    t=(ans-sum-1)/(w-x)+1;
    if(t<0) cout<<0;//答案要大于0 
    else cout<<t;//输出t 
    return 0;
}
```


---

## 作者：_KUK_ (赞：2)

# 分析
一共有两种操作：

$b$ $\ge$ $x$ 时，$b = b - 1$，$c = c - 1$

$b$ $<$ $x$ 时，$a = a - 1$，$c = c - 1$，$b = w - x + b$

以此类推模拟到 $c$ $<$ $a$，每次再把秒数 $+1$ 就行了。

代码如下：
```cpp
#include<iostream>
using namespace std;
int main()
{
	long long a,b,w,x,c;
	cin>>a>>b>>w>>x>>c;
	int cnt=0;
	while(c>a)
	{
		if(b>=x)
		{
			b=b-x;
			c=c-1;
		}
		else
		{
			a=a-1;
			c=c-1;
			b=w-(x-b);
		}
		cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}
```



---

## 作者：QWQ_jyc (赞：2)

在 $c<a$ 前每一步都有两种方案：

$\bullet$ $b\geq x$ 时，$b=b-1$，$c=c-1$

$\bullet$ $b<x$ 时，$a=a-1$，$c=c-1$，$b=w-x+b$

以此类推模拟到 $c<a$，并在每次操作结束后将秒数 $+1$ 即可。

代码懒得放了。

---

## 作者：封禁用户 (赞：1)

## 前言：
竟然有如此水的绿题。

## 思路：

根据题目我们可以知道，只要 $c$ 还小于 $a$ 的话，就要执行该操作。

如果当 $a$ 大于等于 $x$ 的话，$b=b-1$，$c=c-1$。

如果当 $a$ 小于 $x$ 的话，$a=a-1$，$c=c-1$，$b=w-x+b$。

最后输出 $num$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long sum=0,ans=0,num=0,a,b,c,w,x;

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> a >> b >> w >> x >> c; 
	sum=(long long)a*w+b;
	ans=(long long)c*w;
	num=(ans-sum-1)/(w-x)+1;
	if(num<0)
	{
		cout << 0 << endl;
	}
	else
	{
		cout << num << endl;
	}
	return 0;
}
``````

---

## 作者：封禁用户 (赞：0)

### 题解

这道题目要求根据给定的操作规则，计算使不等式 $c \leq a$ 成立的最小秒数。操作规则涉及五个变量 $a$、$b$、$w$、$x$ 和 $c$，并且每秒可以执行一次操作。

首先，需要理解操作规则对 $a$ 和 $c$ 的影响。当 $b \geq x$ 时，$b$ 会减少 $x$ 的值，同时 $c$ 减少 $1$。而当 $b < x$ 时，$a$ 和 $c$ 同时减少 $1$，并且 $b$ 会根据 $w$ 和 $x$ 的关系进行调整。

目标是使 $c$ 的值不大于 $a$。考虑到每次操作 $c$ 都会减少 $1$，而 $a$ 只有在 $b < x$ 的情况下才会减少，可以推断出，在 $b$ 减到小于 $x$ 之前，希望 $a$ 的值尽可能地大，以便在后续的操作中能够保持 $c \leq a$。

接下来，需要考虑如何计算达到 $c \leq a$ 的最小秒数。由于每次 $b$ 减到小于 $x$ 时，$a$ 和 $c$ 都会减少，可以尝试找出 $b$ 减少到小于 $x$ 的次数与 $a$ 和 $c$ 的关系。

通过观察操作规则，可以发现，每次 $b$ 减少到小于 $x$ 时，$a$ 减少的总量与 $b$ 和 $x$ 的差值以及 $w$ 的值有关。同时，$c$ 减少的总量则是 $b$ 减少到小于 $x$ 的次数。

### 代码：
```cpp
#include <iostream>
using namespace std;
long long a, b, w, x, c, cnt;
void solve(){
    if(c <= a){
		cnt = 0;
		return;
	}
    long long kkk = (1ll * a * w - 1ll * w * c + b)/(x - w);
    cnt = kkk;
    if(abs(1ll * kkk * (x - w)) < abs(1ll * a * w - 1ll * w * c + b)){
    	cnt++;
	}
    return;
}
int main(){
	while(cin >> a >> b >> w >> x >> c){
   		solve();
   		cout << cnt;
	}
	return 0;
}
```

---

## 作者：PokerKing (赞：0)

总共就两种情况。

当 $b\geq x$ 时，$b$ 要减 $x$，$c$ 要减去一。

当 $b\lt x$ 时，$a$ 和 $c$ 都要减一，$b=w-x$。

如果 $c>a$，退出循环。

每一次循环判断 $b$ 跟 $x$ 的关系，然后秒数加一。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,w,x;
int main(){
	cin>>a>>b>>w>>x>>c;
	int res=0;//时间
	while(c>a){//一直循环
		if(b<x)
		{
			a--;
			b+=w;
		}
		c--;
		b-=x;
		res++;//每一回合秒数+1
	}
	cout<<res;
	return 0;
}
```

---

## 作者：wbxxxx (赞：0)

# 思路：

这道题其实只用直接模拟即可，因为题意中已经告诉我们式子了。

分别进行两种操作：
- $b\ge x$ 时，$ b \gets b-x $，$ c \gets c-1 $。
- $b<x$ 时，$ a \gets a-1 $，$ c \gets c-1 $，$ b \gets w-x+b $。

# 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int X=0,w=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
int a[10000009],b[100000009],f[10000009];
int i,j,k,sum,cnt,ans;
signed main()
{
	int n=read(),m=read(),tt=read(),yy=read(),cc=read();
	while(cc>n){
		if(m>=yy){
			m-=yy;
			cc--;
		}
		else{
			n--,cc--;
			m=tt-(yy-m);
		}
		cnt++;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：Y_zhao111 (赞：0)

### Description
题目传送门：[CF382B Number Busters](/problem/CF382B)。

### Analysis
> 两个人玩游戏，他们有 $a$，$b$，$w$，$x$，$c$ 五个数，每秒可执行一次操作，要使最终结果为 $c\le a$。操作如下：如果 $b\ge x$，则 $b=b-x$，同时 $c=c-1$；如果 $b<x$，则 $a=a-1$，$c=c-1$，$b=w-(x-b)$。求 $c\le a$  时已经走过的秒数。

题目已经说的很清楚了，按照模拟即可。

在 $c<a$ 时，执行以下操作：
+ $b \ge x$ 时，$b=b−1$，$c=c−1$。
+ $b < x$ 时，$a=a−1$，$c=c − 1$，$b=w−x+b$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	typedef long long LL;
	
	LL a , b , w , x , c;
	cin >> a >> b >> w >> x >> c; //5个数字
	
	LL ans = 0; //最后的秒数
	
	while(c > a) //模拟
	{
		if(b >= x)
			b -= x , c --;
		
		else if(b < x)
			a -- , c -- , b = w - (x - b);
		
		ans ++; //秒数++
	}
	
	cout << ans << endl;
	return 0;
}
```

---

