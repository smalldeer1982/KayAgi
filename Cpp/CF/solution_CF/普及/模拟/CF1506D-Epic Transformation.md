# Epic Transformation

## 题目描述

You are given an array $ a $ of length $ n $ consisting of integers. You can apply the following operation, consisting of several steps, on the array $ a $ zero or more times:

- you select two different numbers in the array $ a_i $ and $ a_j $ ;
- you remove $ i $ -th and $ j $ -th elements from the array.

For example, if $ n=6 $ and $ a=[1, 6, 1, 1, 4, 4] $ , then you can perform the following sequence of operations:

- select $ i=1, j=5 $ . The array $ a $ becomes equal to $ [6, 1, 1, 4] $ ;
- select $ i=1, j=2 $ . The array $ a $ becomes equal to $ [1, 4] $ .

What can be the minimum size of the array after applying some sequence of operations to it?

## 样例 #1

### 输入

```
5
6
1 6 1 1 4 4
2
1 2
2
1 1
5
4 5 4 5 4
6
2 3 2 1 3 1```

### 输出

```
0
0
2
1
0```

# 题解

## 作者：Gokix (赞：6)

[CF1506D](https://www.luogu.com.cn/problem/CF1506D)

这里提供一种 $O(T \sum n)$ 的做法，基于一种有关栈的神奇算法。

------------

题目大意是说每次删除序列中还在的两个不同的数，问最后还剩下多少个数。很显然最后剩下的数权值都是一样的，再仔细想一下这个剩下的数在一开始的序列中肯定出现的至少 $n/2$ 次（只有一个特例：$n$ 为奇数则最后剩下一个没法配对的，这个只需要特判一下就好了，所以后面不再讨论这种情况），不然肯定可以找个方法把所有的数配对完。而下面要介绍的这个有关栈的算法就可以 $O(n)$ 寻找一个在序列中出现至少 $n/2$ 次的数的权值。

------------

下面开始对该算法进行介绍：

条件与问题：长度为 $n$ 的序列 $a$ 中有一个出现的至少 $n/2$ 次的数 $x$，试求 $x$。

算法流程：

1. 开一个栈 $s$ ，将 $a_1$ 入栈。

2. 循环遍历 $a_2$ ~ $a_n$。假设当前遍历到 $a_i$, 记栈顶为 $top$ 若 $a_i=top$，则将 $a_i$ 入栈；否则，将 $top$ 出栈。

3. 循环后的栈中只会剩下 $x$，取栈顶即为答案。

------------

算法的正确性易证，栈中最后只会剩下的所有数权值一定都一样。而对于每个 $x$ ，不是与其它数一起被丢掉了，就是在栈里。又因为 $x$ 的个数至少有 $n/2$，最最不好的情况就是每一个非 $x$ 的数都与 $x$ 配对丢掉，而非 $x$ 数一定没有 $x$ 多，所以栈中一定会剩下 $x$。

------------

回到本题，按照上述方法进行。如果最后栈顶的数没有出现至少 $n/2$ 次（或者栈为空栈），则所有的数都可以配对（除了那个 $n$ 为奇数最后剩一个的情况）。如果栈顶的数 $x$ 满足出现至少 $n/2$ 次，记其出现 $cnt$ 次，则非 $x$ 的数有 $n-cnt$ 个，也就是配了 $n-cnt$ 对，所以 $n-(n-cnt) \times 2$ 就是答案。

------------

CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack> 
using namespace std;
long long t,n,a[200010],cnt,ans;
stack <long long> s;
 
void init(){
	memset(a,0,sizeof(a));
	cnt=ans=0;
	while(!s.empty()) s.pop();
}
 
int main()
{
	long long i,j,u,v;
	cin>>t;
	while(t--){
		init();
		cin>>n;
		for(i=1;i<=n;i++){
			cin>>a[i];
		}
		for(i=1;i<=n;i++){
			if(s.empty()) s.push(a[i]);
			else{
				u=s.top();
				if(u!=a[i]) s.pop();
				else s.push(a[i]);
			}
		}
		if(s.empty()){//空栈别忘了
			if(n&1) cout<<1<<endl;//特判n为奇数最后剩一个
			else cout<<0<<endl;
			continue;
		}
		u=s.top();
		for(i=1;i<=n;i++){
			if(a[i]==u) cnt++;
		}
		if(cnt<=n/2){//没出现至少n/2次
			if(n&1) cout<<1<<endl;
			else cout<<0<<endl;
		}
		else cout<<n-(n-cnt)*2<<endl;
	}
	return 0;
}
```


---

## 作者：moqizhu2005 (赞：4)

### CF 1506D Epic Transformation

我们可以把所有数相消的顺序排列成一个数列。那么我们需要满足的条件即为相邻的数不相等。

所以如果有一个数的数量小于等于$\frac{n}{2}$，对于$n$为偶数的情况，最坏情况下，即存在一个数x的数量等于$\frac{n}{2}$，一定可以排列成：

$$a,x,a,x,b,x\cdots c,x\text{（其中$a,b,c$为其他数量小于$\frac{n}{2}$的数）}$$

这种情况答案为$0$。

同理，如果$n$为奇数，最坏情况下可以排列成：

$$x,a,x,a,x,b\cdots x,c,x\text{（其中$a,b,c$为其他数量小于$\frac{n}{2}$的数）}$$

这种情况答案为$1$，即最后一个位置的数字不能被消除。

如果有一个数的数量$x_{sum}$大于$\frac{n}{2}$的话，可知最坏情况下，其他数最多可以为这个数提供$n-x_{sum}$的消除次数，剩下的数无法消除。所以易得答案为$n-2*(n-x_{sum})$。

判断各个数的数量可以使用排序后计算的方法。

由于排序后，相等的数都被排在一起，所以当相邻的两个数不同时即为临界点，可以计算前一个数的数量。

代码如下：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=200005;
ll t,n,a[maxn];
int main(){
    scanf("%lld",&t);
    while(t--){
    	scanf("%lld",&n);
    	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    	sort(a+1,a+1+n);
    	ll p=0,ma=0;
    	for(int i=1;i<=n;i++){
    		if(a[i]!=a[i-1]){
    			ma=max(ma,p);
    			p=1;//注意当前数第一次出现，计数为1
			}
    		else p++;
		}
		ma=max(ma,p);
		if(ma>n/2) printf("%lld\n",n-2*(n-ma));
		else if(n%2==1) printf("1\n");
		else printf("0\n");
	}
	return 0;
}

```


---

## 作者：_GW_ (赞：3)

## 思路
首先找规律，发现影响答案的只会是出现最多的数的出现次数。

就拿第一个样例来说：把三个一放到左边，与其余三个匹配，那么就一定能匹配成功。但如果一再多一个，就会有 $2$ 个无法匹配成功，因为需要匹配的数量变多了 $1$，而能拿来给一做匹配少了 $1$，对答案的影响为 $2$。

但还需要分类讨论一下。

用 $cnt$ 表示出现最多的数的出现次数吧。

如果 $n$ 是偶数，那么答案就是 $cnt$ 乘二减 $n$。

但还要与 $0$ 取一个较大值，毕竟不可能为负数。

如果 $n$ 是奇数，那么至少有一个不能完成匹配。

然后如果 $cnt$ 小于等于 $n$ 除二，那么就输出一，因为只有多余的那个无法匹配。

否则就与偶数的讨论方法一样。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,num,n,m,val,a[N],b[N];
map<int,int> mp;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;mp.clear();num=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];mp[a[i]]++;
			num=max(num,mp[a[i]]);//就是上述思路中的cnt
		}
		if(n%2==1)//奇数
		{
			if(num<=n/2)
			{
				cout<<1<<endl;
			}
			else
			{
				cout<<max(num*2-n,0)<<endl;
			}
		}
		else//偶数
		{
			cout<<max(num*2-n,0)<<endl;	
		}	
	}
	return 0;
}
```


---

## 作者：thhxxx (赞：2)

# 题目翻译

共 $t$ 组数据，每次给出一个数组 $a$，以及数组的长度 $n$，可在数组中任选两个两个**不同**的数字删除，求如何选可使剩余的数字最少。

数据范围：$1\leq t \leq 10^4$，$1\leq n \leq 2 \cdot 10^5$，$1\leq a_i \leq 10^9$，而且所有组的数字数量一共不超过 $2 \cdot 10^5$。

# 思路

采用贪心的策略，用一个 ```map``` 来记录每个数字出现的次数，再用一个优先队列来维护，优先把出现次数多的数字删除，而本题因为只能选两个不同的数字，所以每次删去出现次数**最多**的数字和**次多**的数字。

# AC代码

```
#include <iostream>
#include <queue>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;

    while (n--)
    {
        priority_queue<pair<int, int>> q;
        int m;
        cin>>m;
        map<int,int> mp;

        for (int i=0;i<m;i++)
        {
            int x;
            cin>>x;
            mp[x]++;
        }

        for (auto i : mp)
        {
            q.push({i.second, i.first});
        }

        int size=m;

        while (q.size()>=2)//当数组里还有两个以上不同的数字时候重复
        {
            auto i=q.top();//取出最大的数
            q.pop();
            auto j=q.top();//取出次大的数
            q.pop();

            int a=i.first-1;//最大的数的量减一
            int b=j.first-1;//次大的数的量减一
            size-=2;//总数减二

            if (a) q.push({a, i.second});//若最大的数的量不为零，将其放回优先队列
            if (b) q.push({b,j.second});//若次大的数的量不为零,将其放回优先队列
        }
        cout<<size<<'\n';
    }

    return 0;
}
```

---

## 作者：shengnan (赞：1)

题意：给一个序列，每次可删除两个不相同的数，问若干次操作后最少有几个数。

思路：把原序列离散化，开一个桶统计每个数出现的次数。根据**贪心**的思想，我们现在想要序列中相同数的个数尽量少，所以每次尽量消去个数最多的两个数。（感性理解一下）

实现：怎么动态维护 相同数最多的个数？这里我用**大根堆**，把不为 $0$ 的个数数放到堆里，每次取两个消掉。若堆中只剩一个数，那么这个数就是最后最少有的数的个数，因为没有别的数可以和它消了；若堆空，则全消完，答案为 $0$。

AC代码：

```c
#include <bits/stdc++.h>
using namespace std;
int n,a[200005],b[200005],len,c[200005],t,ans,x,y;
priority_queue<int> q;
int main(){
	scanf("%d",&t);
	while(t--){
	    scanf("%d",&n);ans=0;memset(c,0,sizeof(c));
	    while(!q.empty())q.pop();
	    for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	    sort(b+1,b+1+n);len=unique(b+1,b+1+n)-b-1;
	    for(int i=1;i<=n;i++)
		   a[i]=lower_bound(b+1,b+1+len,a[i])-b,c[a[i]]++;
	    for(int i=1;i<=len;i++)if(c[i])q.push(c[i]);
	    while(!q.empty()){
	    	if(q.size()==1){ans=q.top();break;}
	    	x=q.top();q.pop();y=q.top();q.pop();
	    	x--;y--;if(x)q.push(x);if(y)q.push(y);
		}
	    printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：LinkZelda (赞：1)

- **题意**：

给定 $n$ 个数，每次可以选择其中两个**不同**的数进行删除，求最后最少剩下多少个数。

- $Solution$:

因为要是不同的数，所以我们容易想到开个桶记录每个数出现次数，值域较大，我们应该使用 `map` 来实现。

1. 如果出现次数最多的数只出现了 $\frac n 2$ 次或以下的话，显然这些数是可以两两不同的进行删除的。判断一下 $n$ 的奇偶性即可（因为每次删 $2$ 个数）。

1. 如果出现次数最多的数出现了大于 $\frac n 2$ 次的话，我们可以推一下式子，设该数出现次数为 $cnt$，有：

$$
ANS=n-(n-cnt)\times2=2\times cnt-n
$$

这个式子中的 $n-cnt$ 是可以与该数配对删除的数的个数，然后乘以 $2$ 就是删除的总个数，再减一下就是答案了。

- [代码](https://www.luogu.com.cn/paste/uq7jegwn)

---

## 作者：xkcdjerry (赞：0)

令 $f_x$ 为 $x$ 在 $a$ 中出现的次数。

那么有一个很容易猜的结论：如果存在一个数 $x$ 使得 $2f_x>n$，那么最后会剩下 $2f_x- n$ 个数。否则会剩余 $n$ 模 $2$ 的余数。

接下来提供每一部分的证明：（各部分小标题加粗方便寻找）

-----

**命题一**：如果存在一个数 $x$ 使得 $2f_x>n$，那么最后会剩下 $2f_x - n$ 个数无法消除。  

**证明**：  
由于其它所有数一共有 $n-f_x$ 个，那么最多可以消掉 $n-f_x$ 个 $x$，会剩余 $f_x-(n-f_x)=2f_x-n$ 个。  

实现：
$x$ 可以使用[摩尔投票法](https://www.luogu.com.cn/problem/P2397)花 $O(n)$ 时间和 $O(1)$ 空间搞出来。  
大概证一下：这个算法思想等于是维护一群一样的数，新数和它一样就丢进去，不一样就拎出来这一群数里的一个和它相消。而这个题里面任意安排相消次序都没法把 $x$ 消完，等于是随机次序的摩尔投票就更不可能消完了。  
所以**如果存在** $x$，那么它一定是剩下的这一堆数，但是还是由于随机投票导致可能有一个并不是超过一半的被留在了最后这一堆数里，所以还需要 $O(n)$ 统计一次统计出的数目确定是否有 $2f_x>n$。

----

**命题二**：如果 $n$ 为偶数且命题一的条件不成立，那么最后一定不会有剩余。

**证明**：  
$n=2$ 时，本结论显然。

$n=4$ 时，存在三种情况：  
* 有两个不同的数字 $x,y$，满足 $f_x=f_y=2$，命题显然成立。
* 有三个不同的数字 $x,y,z$，满足 $f_x=2$，$f_y=f_z=1$，命题显然成立。
* 有四个不同的数字 $a,b,c,d$，满足 $f_a=f_b=f_c=f_d=1$，命题显然成立。

综上，$n=4$ 时，本命题成立。

如 $n=2t$ $(t \geqslant 3)$：取出 $f_x$ 最大和第二大的两个数 $x$ 和 $y$ 并相消，那么新的情况满足如下条件：
* $n'=n$
* 因为 $2f_y \leqslant 2f_x < n$，那么$2f'_y=2(f_y-1) \leqslant 2f'_x=2(f_x-1) < n'=n-2$。
* 对于 $f_x$ 第三大及以后的数 $z$，存在 $f_z \leqslant n/3$，那么 $2f'_z=2f_z \leqslant \frac{2}3n$，又因为 $x \geqslant 3$ 即 $n \geqslant 6$，所以 $2f'_z=\frac{2}3n \leqslant n'=\frac{n}2$。

综上，最大和第二大的数相消后新的情况仍然满足命题二的条件且 $n'=n-2$，故由数学归纳法可知命题二正确。

----
**命题三**：如果 $n$ 为奇数且命题一的条件不成立，那么最后一定会剩余 $1$ 个。

**证明**：  
令 $n=2t+1$,则：  
由于消去是两两消去的，最多能消去 $2x$ 个，所以至少会留下 $1$ 个。  

如果开始时从 $f_x$ 最大的 $x$ 中指定一个为剩余的，那么：
如 $n=3$，则显然会剩余两个不一样的数，剩余的可以消完。  
如 $n>3$，则：  
* $2f'_x=2(f_x-1) < n-2 < n' = n-1$。  
* 由命题一的条件不成立的 $f_x$ 第二大及以后的 $y$ 有满足 $f_y<f_x$，则 $2f'_y=2f_y \leqslant 2(f_x-1) < n'$。

根据命题二可得指定一个为剩余的后剩余的恰好可消完，所以最多会留下 $1$ 个。

综上，恰好会留下 $1$ 个，即证。

---
综上，初始结论正确。

代码：~~我知道你们都想看这个~~
```
#include <cstdio>
#define N 200010
int a[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",a+i);
        //判断是否存在x使得cnt(x)>cnt(others)
        //显然如果存在x p就是x
        int p=-1,c=0;
        for(int i=0;i<n;i++)
        {
            if(p==-1) p=a[i];
            if(p==a[i]) c++;
            else {if(!--c) p=-1;}
        }
        //验证是否存在
        c=0;
        for(int i=0;i<n;i++) if(p==a[i]) c++;
        if(c*2>n) printf("%d\n",c*2-n);
        else puts(n&1?"1":"0");
    }
}
```
[AC 记录](https://www.luogu.com.cn/record/77042761)

---

