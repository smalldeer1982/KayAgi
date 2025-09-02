# NIT Destroys the Universe

## 题目描述

定义 $\operatorname{mex}$ 为一个集合中最小的没有出现过的非负整数。

给定一个由 $n$ 个非负整数组成的的序列 $a$，NIT 可以进行若干次操作，每次操作选择 $l$ 和 $r$（$1\le l \le r \le n$），将 $a_l, a_{l+1} \cdots a_r$ 全部修改为 $\operatorname{mex}(\{a_l, a_{l+1} \cdots a_r\})$。本题有多组数据，对于每一组数据，请回答 NIT 最少需要多少次操作可以让整个序列都为 $0$。

## 说明/提示

$1 \le t \le 10^4$，$1 \le n \le 10^5$，$0 \le a_i \le 10^9$，$\sum n \le 2 \cdot 10^5$。

## 样例 #1

### 输入

```
4
4
0 0 0 0
5
0 1 2 3 4
7
0 2 3 0 1 2 0
1
1000000000```

### 输出

```
0
1
2
1```

# 题解

## 作者：Dry_ice (赞：6)

申明：已经根据管理要求进行修改，感谢指正。

[Blog浏览](https://www.cnblogs.com/dry-ice/articles/cf1696b.html)

> 第二次打 cf Global Round。

这个第二题是真的思维，代码极短。

## 问题分析
本题中的 $\text{mex}(l,r)$ 操作其实就是一个表象，瞄准最终目的 $\forall a_i,a_i=0$ 就好办。

显然答案只有 $3$ 种可能：$0$，$1$，$2$。下面就来证明一下这个~~简单明了~~的答案。

## 结论证明
$1^{\circ}$ 答案为 $0$：显而易见，当初始数列为全 $0$ 时答案为 $0$。
$2^{\circ}$ 答案为 $1$：把 $0$ 想成隔板，中间为平台，若连续平台仅一个，设为 $a_i$ 到 $a_j$， 则只需一次操作使 $l=i,r=j$ 即可。如题例 $2$：
```
5
0 1 2 3 4
```
只需使 $l=2,r=5$ 一次操作即可。

$3^{\circ}$ 答案为 $2$：对于除了以上两种情况，如题例 $3$：
```
7
0 2 3 0 1 2 0
```
只需找到最左最右的非零位置 $l = 2$ 和 $r = 6$ 进行操作，置为 $4$，然后再执行一次 $l=2$，$r=6$ 即可将 $a_2$ 到 $a_6$ 全部置零即将 $a$ 序列置零。故答案为 $2$。
以此类推，可得其他类似情况答案亦为 $2$。

综上所述，答案仅可能为 $0$，$1$ 或 $2$。证毕。

> 看到这里，代码就很简单了。

## Code
```cpp
#include <stdio.h>
const int N = (int)1e5 + 5;
int n, a[N];
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        int Ans = (a[n] != 0); //末尾值要特殊处理
        for (int i = 2; i <= n; ++i)
            if (a[i] == 0 && a[i - 1] != 0) ++Ans;
		//统一连续平非零平台数
        printf("%d\n", Ans > 1 ? 2 : Ans); //运用所证结论
    }
    return 0;
}
```

## The end. Thanks.

---

## 作者：SoyTony (赞：3)

# 题意
一个数列 $a$，每次操作支持修改一个区间 $[l,r]$，使其中所有的数都变为没有出现在该区间的最小的非负整数。

求把数列全部变成 $0$ 的最小操作次数。
# 题解
首先能得到的是，如果区间里没有 $0$，那么操作后全部是 $0$，如果有 $0$ 则需要进行两步操作（先变成任意一个数再变成 $0$），或者是把 $0$ 隔开去逐个操作。

然后不难发现一个事情，整个数列操作两次一定可以全部变成 $0$，所以统计非零连续区间个数，输出其与 $2$ 相比的较小值。

---

## 作者：zjk0105 (赞：2)

# 解题思路

答案最多为 $2$，因为在 $[1,n]$上最多执行两次操作总是有效的。

（如果数组至少包含一个零，我们需要 $2$次操作。否则我们需要  $1$次操作。）

如果数组由零组成，则答案为 $0$。

如果所有非零元素在数组中形成一个连续的段，则答案是 $1$。

要检查这一点，您可以找到最左边和最右边出现的非零元素，并检查它们中间的元素是否也非零。

否则答案为 $2$。

时间复杂度为 $O(n)$。

# $AC$代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,a[N],ans;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0;//非 0 段数，记得清零 
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]&&a[i-1]==0)
				ans++;
		}
		cout<<min(2,ans)<<'\n';//最多 2 步，取最小值 
	}
}
```


---

## 作者：zct_sky (赞：1)

### Solution:
-----
先分类讨论。

- 如果这个序列里都是 $0$，那么不需要操作（$0$ 次）。

- 如果这个序列里只有连续一段是非 $0$ 的，那么只需对这段非 $0$ 序列进行 $1$ 次操作，整个序列就都变成 $0$ 了。

- 如果这个序列有一段以上是非 $0$ 的，那么就对整个序列进行 $2$ 次操作，整个序列就都变成 $0$ 了。（在进行第一次操作后，整个序列都变成了 $ \operatorname{mex}(\{a_l,a_{l+1},\dots,a_r\}) $，而且因为原序列中有 $0$，所以 $ \operatorname{mex}(\{a_l,a_{l+1},\dots,a_r\}) $ 一定是非  $0$ 的，也就是说整个序列都是非 $0$ 的。此时再对整个序列进行一次操作，整个序列就都变成 $0$ 了。）

所以，整个序列的最少操作次数就是整个序列非 $0$ 段数和 $2$ 之间的最小值（非 $0$ 段数求法：当 $a_{i-1}=0$，且 $a_i \neq 0$ 时，就有 $1$ 段非 $0$ 段。（$a_0$ 初始化为 $0$））。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
inline ll re(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void wr(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) wr(x/10);
	putchar(x%10+48);
	return;
}
int t;
int main(){  
	t=re();
	for(int tt=0;tt<t;tt++){
		int a=0,last,n=re(),ans=0;
		for(int i=1;i<=n;i++){
			last=a;a=re();
			if(!last&&a)ans++;
		}
		wr(min(ans,2)),puts("");
	}
    return 0;
}
```

---

## 作者：litachloveyou (赞：1)

每一个操作都可以让一段区间内的值变成最小没出现过的整数，于是我们很容易想到，**最坏的情况就是将整个区间变成最小没出现过的整数，然后再变一次就能满足题目的要求。**

------------
于是，答案最大就是两次了。那么其他特殊情况呢？

------------
如果**只有一个区间里面全是非零数**，那么我们只需要一次操作就可以将这个区间全部变为零。如果已经全是零了，那么不需要任何操作就可以满足题目条件。

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n;
	scanf("%d", &n);
	vector<int>a(n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] != 0)
		{
			cnt++;
			while (a[i] != 0 && i < n-1)
			{
				i++;
			}
		}
	}
	if (cnt > 1)puts("2");
	else if (cnt == 1)puts("1");
	else puts("0");
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：CodeMao (赞：0)

很具有**思维性**的一道题。

### 简述题意

给定一个序列 $a$，每次选取一个区间 $[l,r]$，将区间内所有的数均改为区间内未出现的最小非负整数，问最少需要多少次操作才能使 $a$ 序列全部为 $0$。

### 主要思路：

- 一共有三种情况，分别是答案为 $0,1,2$。
  
  - 第一种（答案为 $0$）：$a$ 序列中所有元素均为 $0$，无需进行操作，所以答案为 $0$。
    
  - 第二种（答案为 $1$）：$a$ 序列中所有不为 $0$ 的元素全部出现在一个连续的段或 $a$ 序列中不存在 $0$，只需进行 $1$ 次操作把这个连续的段中的所有元素改为 $0$ 即可，所以答案为 $1$。
    
  - 第三种（答案为 $2$）：$a$ 序列中既有 $0$ 也有非 $0$ 元素，此时只需选取从第一个 $0$ 到最后一个 $0$ 这段区间，将这段区间中的元素全部改为一个不为 $0$ 的数，然后再把整个 $a$ 序列改为 $0$，一共需要 $2$ 步操作，所以答案为 $2$。
    
- 所以只需判断是否为第一、二两种情况即可，即只需判断是否存在 $a_i\neq 0$，但 $a_{i-1}=0$ 这种情况。如果存在，存在几个，如果存在 $0$ 个，则答案为 $0$；如果存在 $1$ 个，则答案为 $1$；如果存在 $>1$ 个，则答案为 $2$。
  

这道题主要还是**思维**，代码很短，甚至都不需要数组。

```cpp
#include <cstdio>
int t,n,lst,x;
inline void in(int &a){
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
}
inline void op(int a){
    if(a>9) op(a/10);
    putchar(a%10+'0');
}      
inline void out(int a,bool f){
    op(a);
    if(f) puts("");else putchar(' ');
}
inline int min(int a,int b){
    return a<b?a:b;
}
int main(){
	//freopen("G:\\C\\in.in","r",stdin);
	//freopen("G:\\C\\out.out","w",stdout);
	in(t);
	while(t--){
		in(n);int ans=0;lst=0;
        for(int i=1;i<=n;++i,lst=x){
            in(x);
            if(x&&!lst) ans++;
        }
        out(ans<=1?ans:2,1);
    }
    return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

对于这道题，我们有一个很显然错误的贪心做法：

- 每次选择一段尽可能长的包含 $0$ 的区间，对这个区间进行一次操作。显然的，这个区间内的所有数字都会变成 $0$。

我们拿可爱的样例举个例子：

`0 2 3 0 1 2 0`

1. 对 $[2,3]$ 区间进行一次操作，$w=\operatorname{mex}(\{2,3\})=0$，所以 $a_2 \to 0,a_3 \to 0$，序列变成 `0 0 0 0 1 2 0`。

1. 对 $[5,6]$ 区间进行一次操作，$w=\operatorname{mex}(\{1,2\})=0$，所以 $a_5 \to 0,a_6 \to 0$，序列变成 `0 0 0 0 0 0 0`。

总共需要 $2$ 次操作。

容易发现，如果按照这种贪心做法，那么答案应该是数组中出现的 $0$ 的数量 $-$ 开头出现的 $0$ 的数量 $-$ 结尾出现的 $0$ 的数量 $+1$。

在上面那个例子中，答案就是 $3-1-1+1=2$。

既然这个贪心做法是错的，那么我们就要举出一个反例：

`1 0 2 0 3`

根据上面那个贪心做法，答案应该是 $2-0-0+1=3$，但实际上，我们可以通过如下操作使操作次数只有两次：

1. 对 $[1,5]$ 区间进行一次操作，$w=\operatorname{mex}(\{1,0,2,0,3\})=4$，所以 $a_1 \to 4,a_2 \to 4,a_3 \to 4,a_4 \to 4,a_5 \to 4$，序列变成 `4 4 4 4 4`。

1. 对 $[1,5]$ 区间进行一次操作，$w=\operatorname{mex}(\{4,4,4,4,4\})=0$，所以 $a_1 \to 0,a_2 \to 0,a_3 \to 0,a_4 \to 0,a_5 \to 0$，序列变成 `0 0 0 0 0`。

于是我们考虑对这个贪心算法进行修正：我们发现，不管是什么样的数组，我们都可以通过对 $[1,n]$ 操作两次使得所有元素归零，于是我们只需要把贪心算法的答案对 $2$ 取个 $\min$ 即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int b[100005];
void cf(){
	int n=read();
	int a[n+1];
	for(int i=1;i<=n;i++)
		a[i]=read();
	int cnt=0;
	for(int i=1;i<=n;i++)
		b[i]=0;
	for(int i=1;i<=n;i++){ //这里我的实现方法稍微有一点不一样，大家理解即可
		if((a[i]==0&&b[cnt]==0)||(a[i]!=0&&b[cnt]!=0)) continue;
		cnt++;
		b[cnt]=a[i];
	}
	if(b[cnt]==0) cnt--;
	if(b[1]==0) cnt--;
	printf("%d\n",min(2,(cnt+1)/2));
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：BetaCutS (赞：0)

可以证明，任何序列能在 $2$ 步内变为 $0$。

证明：先 $l=1,r=n$，现在每个数都是一样的。然后再 $l=1,r=n$，全部变为 $0$。

因为最多有 $2$ 步，所以就能分三种情况：

1. 不用操作。如果一开始序列全为 $0$ 就不用操作啦。

2. 只用一次。有且仅有一个非 $0$ 的连续段，就可以对这一段进行一次操作，把它们全变为 $0$。

3. 其他的情况就是 $2$ 步。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,a[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		int ans=0;//非0段数
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]&&!a[i-1])
				ans++;
		}
		printf("%d\n",min(2,ans));//最多2步
	}
	return 0;
}

```


---

## 作者：JS_TZ_ZHR (赞：0)

## 题解：

先分类讨论。全是 $0$ 不用操作。

如果可以找到一个区间使得这个区间里面包含所有的非 $0$ 元素那么对这个区间进行一次操作即可。

如果这样的区间不存在，显然不能一次操作使得所有元素变成 $0$。此时对整个序列进行两次操作。因为有 $0$ 存在，所以序列的 $\text{mex}$ 大于 $0$，第一次操作后这个序列变为一个不存在 $0$ 的序列，然后就变为一次操作解决的情况。

## 代码：

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int T,n,a[N],ans,cnt;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		cnt=ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
			if(a[i]&&!a[i-1])ans++;
		ans=min(ans,2ll);
		cout<<ans<<endl;
		
	}
} 
```


---

## 作者：Avocadooo (赞：0)

### 1.题目思路

首先根据 $ \text{mex}(l,r) $ 的定义，可以发现一个很显然的性质。

> 对于一个不包含 $ 0 $ 的连续串，其 $ \text{mex} $ 一定为 $ 0 $。
>>因为在该连续串中最小的未出现的非负整数一定为 $ 0 $。

那么是不是就意味着我们只需要统计不包含 $ 0 $ 的不可扩展的连续串的个数呢？

考虑同时存在多个非零连续串的情况，如下：

$$ 0\;10\;2\;3\;4\;0\;2\;0\;1\;2\;6 $$

根据之前的思路，我们需要进行三次操作才能把序列变为全 $ 0 $。

$$ \text{opt}(2,5) : 0\;0\;0\;0\;0\;0\;2\;0\;1\;2\;6 $$

$$ \text{opt}(7,7) : 0\;0\;0\;0\;0\;0\;0\;0\;1\;2\;6 $$

$$ \text{opt}(9,11) : 0\;0\;0\;0\;0\;0\;0\;0\;0\;0\;0 $$

但最开始想操作性质的时候，我们只考虑了区间 $ \text{mex} $ 为 $ 0 $ 的情况，那区间 $ \text{mex} $ 不为 $ 0 $ 的情况呢？

这样考虑后，我们可以发现对某一个包含 $ 0 $ 的区间执行操作后，整个区间会变成**单独一个**不包含 $ 0 $ 的区间，我们再对这个区间进行一次操作，区间就会变为一个全部为 $ 0 $ 的区间。例子如下：

$$ 0\;10\;2\;3\;4\;0\;2\;0\;1\;2\;6 $$

$$ \text{opt}(1,11) : 5\;5\;5\;5\;5\;5\;5\;5\;5\;5\;5 $$

$$ \text{opt}(1,11) : 0\;0\;0\;0\;0\;0\;0\;0\;0\;0\;0 $$

那么对**整个序列**(同样满足上述性质)执行该操作，最多两次即可完成。

我们就可以完美的解决本题了。

### 2.代码

```cpp
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=300005;
int a[N];
void solve()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	int l=1,r=n;
	while(l<=n && a[l]==0) l++;
	while(r>=1 && a[r]==0) r--;
	if(l>r) return void(puts("0"));
	for(int i=l;i<=r;i++) if(a[i]==0) ans++;
	cout<<min(2,ans+1)<<endl;
}
int main()
{
	int _test__Case;
	scanf("%d",&_test__Case);
	while(_test__Case--)
	{
		solve();
	}
}
```

---

## 作者：Morgen_Kornblume (赞：0)


# B

观察到选择一段连续的不含 $0$ 的区间 $[l,r]$ ，显然此区间的 $mex(l,r)$ 一定 $=0$。那么我们可以贪心地选择序列中所有的连续**极长**的不含 $0$ 区间，统计它们的数量即为答案。

然而这样你会很快地收获 WA on pretest 2，为什么呢？

因为假如有两个及以上如上所述的区间，那么我们可以花一次操作，选择整个序列，这样整个序列的 $mex$ 值肯定不为 $0$，那么整个序列在操作后就不含 $0$，然后再次对整个序列操作，序列就变为全 $0$ 了。

所以说，最多的操作次数即为 $2$，答案上限为 $2$。

```cpp
int T;
	int n=0;
	int a[100010];
	
	void main(){
		cin>>T;
		while(T--){
			for(int i=1;i<=n;i++)a[i]=0;	
			cin>>n;
			for(int i=1;i<=n;i++)cin>>a[i];
			int pos=1,ans=0;
			while(pos<=n){
				while(pos<=n&&a[pos]==0)pos++;
				if(pos<=n&&a[pos]!=0){
					ans++;
					for(;pos<=n&&a[pos]!=0;pos++);
				}
			}
			ans=min(ans,2);
			cout<<ans<<endl;
		}
	}

```

---

## 作者：yeshubo_qwq (赞：0)

## Description

定义 $\operatorname{mex}$ 为一个集合中最小的没有出现过的非负整数。

给定一个由 $n$ 个非负整数组成的的序列 $a$，NIT 可以进行若干次操作，每次操作选择 $l,r$（$1\le l \le r \le n$），将 $a_l, a_{l+1} \cdots a_r$ 全部修改为 $\operatorname{mex}(\{a_l, a_{l+1} \cdots a_r\})$。请回答 NIT 最少需要多少次操作可以让整个序列都为 $0$。

## Solution

当集合内没有 $0$ 时，集合中最小的没有出现过的非负整数是 $0$（称操作 $1$）；当集合内有 $0$ 时，集合中最小的没有出现过的非负整数非 $0$（称操作 $2$）。

于是乎，我们就可以分三种情况：

+ 序列初始状态都为 $0$，不需要操作，答案为 $0$。

+ 序列初始状态中只有一段连续非 $0$ 的，只需要用操作 $1$ 将那一段变成 $0$，答案为 $1$。

+ 否则用操作 $2$ 将整个序列变成全部非 $0$ 的，再用操作 $1$，答案为 $2$。

答案可以转化为序列中连续非 $0$ 的段数和 $2$ 的最小值。

## Code

```cpp
#include <bits/stdc++.h>
#define gc getchar
#define pc putchar
#define F(i,x,y) for (register int i=x;i<=y;i++)
#define Endl pc('\n');
using namespace std;
int min (int x,int y) { return x<y?x:y; }
inline void read(int &x);
inline void write(int x);
int T,n,ans,fl,a[200005];
int main(){
	read(T);
	while (T--){
		read(n);
		F(i,1,n) read(a[i]);
		ans=0;;
		F(i,1,n)
			if (a[i]!=0) fl++;
			else ans+=(fl!=0),fl=0;
		ans=min(ans+(fl!=0),2),fl=0;
		write(ans); Endl
	}
	return 0;
}
inline void read(int &x){
	char c=gc(); int flag=1;
	while (!isdigit(c) && c!='-') c=gc();
	if (c=='-') flag=-1,x=0; else x=(c^48);	c=gc();
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=gc();
}
inline void write(int x){
	if (x<0) pc('-'),x=-x;
	if (x>9) write(x/10);
	pc(x%10+'0');
}
```


---

## 作者：Jasper08 (赞：0)

### 题目分析

当 $a=[0,1,2,3,0,1,2,0]$ 时，我们说 $a$ 有 $2$ 段。当 $a=[0,4,0,3,2,1,0,3]$ 时，我们说 $a$ 有 $3$ 段。以此类推……

我们可以进行分类讨论。

第一种情况：$a$ 有 $0$ 段。（ $a$ 中的数全为 $0$ ）

显然只需要 $0$ 次。

第二种情况：$a$ 有 $1$ 段。

例如，$a=[0,1,2,5,0]$ 时，我们取 $l=2,r=4$ ，那么 $\text{mex}(a_2,a_3,a_4)=0$ ，将 $a_2,a_3,a_4$ 都替换为 $0$ ，此时 $a$ 中的数全部为 $0$ . 

一般地，对于 $a$ 只有 $1$ 段的情况，设其开始于第 $i$ 个数，结束于第 $j$ 个数，那么取 $l=i,j=r$ 即可，只需要 $1$ 次。

第三种情况：$a$ 有 $\ge 2$ 段。

例如，当 $a=[0,1,4,2,0,5,0,12,3,0,1,0] $ 时，第一次先取 $l=2,r=11$ ，那么 $\text{mex}(a_2,a_3,...,a_{11})=6$ ，所以 $a=[0,6,6,6,6,6,6,6,6,6,6,0]$ . 第二步再取 $l=2,r=11$ 即可让 $a$ 全部变为 $0$ .

一般地，对于 $a$ 有大于等于 $2$ 段的情况，设第一段开始于 $i$ ，最后一段结束于 $j$ ，那么第一次取 $l=i,r=j$ ，第二次再取 $l=i,r=j$ 即可让 $a$ 全部变为 $0$ .

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x*f;
}

int main() {
	int t = read();
	while (t -- ) {
		int n = read();
		bool all_zero = 1, find_fnzero = 0, find_snzero = 0, change_zero = 0;
        	//all_zero判断是否全是0,find_fnzero判断是否找到了第1段,find_snzero判断是否找到了第2段,change_zero判断第1段是否结束
		for (int i = 1; i <= n; ++i) {
			int t = read();
			if (t) { //如果t不为0
				all_zero = 0; //说明不全是0
				if (!find_fnzero && !find_snzero) //如果第1段和第2段都没找到
					find_fnzero = 1; //那么t就是第1段的开始
				else if (change_zero) //如果第1段已经结束
					find_fnzero = 0, find_snzero = 1; //那么t就是第2段的开始
			}
			else if (!t && !all_zero) //如果t=0且找到了第1段
				change_zero = 1; //那么第1段就结束了
		}
		if (all_zero) //如果全是0,就不用操作
			puts("0");
		else if (find_fnzero) //如果只有1段,需要操作1次
			puts("1");
		else //如果有大于等于2段,需要操作2次
			puts("2");
	}
	return 0;
}

```

---

## 作者：Burnling (赞：0)

### 分析

记每一次操作后的序列为 $b$ .

序列 $b$ 有如下两种情况：

1.  $\forall i \in[l,r],a_i\not=0$ 时，序列 $b$ 在区间 $[l,r]$ 内每一项均为 $0$ .
2.  $\exist i\in[l,r],a_i=0$ 时，序列 $b$ 在区间 $[l,r]$ 中每一项的值均为 $\operatorname{mex}(\{a_l,a_{l+1},\dots,a_{r-1},a_r\})$ .

对于每一个区间 $[l,r]$ ，最多仅需要两次操作（情况 2 然后情况 1）即可使 $\forall i \in[l,r],a_i=0 $ .

一个显然的性质为：对于每个序列，最多只需要 $2$ 次操作即可使整个序列都为 $0$ .

因此，用 $0$ 将原序列分割成若干段，记段数为 $k$ ：

1. 当 $k=0$ 时，意味着原数组所有元素均为 $0$ .
2. 当 $k=1$ 时，意味着只存在一个区间 $[l,r]$ 满足情况 1.
3. 当 $k \geq 2$ 时，意味着存在多于 2 个满足情况 1 的区间，如果对于每一段都进行操作 1 ，共需要 $k(k>1)$ 次操作。但显然我们可以对整个序列进行两次操作（情况 2 然后情况 1）即可使整个序列均为 $0$ .

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e5;

int N;
int A[maxN];

int main() {
	int T;
	scanf("%d",&T);
	
	while(T--) {
		scanf("%d",&N);
		
		memset(A,0,sizeof(A));
		int cnt = 0;
		
		for(int i = 1; i<=N; i++) scanf("%d",&A[i]);
		
		for(int i = 1; i<=N+1; i++) {
			if(A[i] == 0 && A[i-1] != 0) cnt++; //统计段数 
		}
		
		if(cnt <= 1) printf("%d\n",cnt);
		else printf("2\n");
	}
	return 0;
}

```



---

