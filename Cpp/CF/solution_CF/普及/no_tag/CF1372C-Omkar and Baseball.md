# Omkar and Baseball

## 题目描述

Patrick likes to play baseball, but sometimes he will spend so many hours hitting home runs that his mind starts to get foggy! Patrick is sure that his scores across $ n $ sessions follow the identity permutation (ie. in the first game he scores $ 1 $ point, in the second game he scores $ 2 $ points and so on). However, when he checks back to his record, he sees that all the numbers are mixed up!

Define a special exchange as the following: choose any subarray of the scores and permute elements such that no element of subarray gets to the same position as it was before the exchange. For example, performing a special exchange on $ [1,2,3] $ can yield $ [3,1,2] $ but it cannot yield $ [3,2,1] $ since the $ 2 $ is in the same position.

Given a permutation of $ n $ integers, please help Patrick find the minimum number of special exchanges needed to make the permutation sorted! It can be proved that under given constraints this number doesn't exceed $ 10^{18} $ .

An array $ a $ is a subarray of an array $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first permutation, it is already sorted so no exchanges are needed.

It can be shown that you need at least $ 2 $ exchanges to sort the second permutation.

 $ [3, 2, 4, 5, 1, 6, 7] $

Perform special exchange on range ( $ 1, 5 $ )

 $ [4, 1, 2, 3, 5, 6, 7] $

Perform special exchange on range ( $ 1, 4 $ )

 $ [1, 2, 3, 4, 5, 6, 7] $

## 样例 #1

### 输入

```
2
5
1 2 3 4 5
7
3 2 4 5 1 6 7```

### 输出

```
0
2```

# 题解

## 作者：Meatherm (赞：6)

根据题意，$a$ 是一个排列，所以当序列合法时一定有 $a_i=i$。

我们不需要操作 $a_i=i$ 的前缀和后缀，操作它们不会使答案更优。例如，$a=[1,2,3,7,6,5,4,8]$，那么我们考虑 $a=[7,6,5,4]$ 时的情况即可。当然，如果 $a$ 已经递增，那么答案为 $0$。

接下来，我们分情况讨论。

- 情况 $1$：不存在 $i$ 使得 $a_i=i$。（$a=[7,6,5,4]$）

  一次操作就可以使 $a$ 变得递增。（$[7,6,5,4] \to [\color{red}4\color{black},\color{red}5\color{black},\color{red}6\color{black},\color{red}7\color{black}]$）

- 情况 $2$：存在恰好一个 $i$ 使得 $a_i=i$。（$a=[3,2,1]$）

  一次操作可以使 $a$ 变成情况 $1$（$[3,2,1] \to [\color{red}2\color{black},\color{red}3\color{black},1]$）。总答案为 $2$。
  

- 情况 $3$：存在多个 $i$ 使得 $a_i=i$。（$a=[3,2,5,4,1]$）

  一次操作将这些 $a_i$ 循环移位，可以使 $a$ 变成情况 $1$（$[3,2,5,4,1] \to [3,\color{red}4\color{black},5,\color{red}2\color{black},1]$）。总答案为 $2$。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=200010,INF=0x3f3f3f3f;
int a[N];
int n;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	int T=read();
	while(T--){
		n=read();
		for(rr int i=1;i<=n;++i){
			a[i]=read();
		}
		int l=-1,r=-1;
		for(rr int i=1;i<=n;++i){
			if(a[i]==i){
				continue;
			}else{
				l=i;
				break;
			}
		}
		for(rr int i=n;i>=1;--i){
			if(a[i]==i){
				continue;
			}else{
				r=i;
				break;
			}
		}
		bool flag=true;
		for(rr int i=l;i<=r;++i){
			if(a[i]==i){
				flag=false;
				break;
			}
		}
		if(l==-1&&r==-1){
			puts("0");
		}else{
			if(flag){
				puts("1");
			}else{
				puts("2");
			}
		}
	}	
	return 0;
}
```



---

## 作者：wjh2011 (赞：2)

如果这个排列本来就有序，直接输出 $0$。

如果这个序列不是有序的，我们可以把最前面和最后面本来就在自己的位置的数直接去掉，再判断剩下的数是否都不在自己的位置上，如果剩下的数都不在自己的位置上，输出 $1$。

否则一定可以通过一次操作将序列变为剩下的数都不在自己的位置上的清况，输出 $2$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005];
bool f, g;
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        f = 0, g = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int l = 1, r = n;
        for (; l <= n; l++)
            if (a[l] != l)
                break;
        for (; r; r--)
            if (a[r] != r)
                break;
        for (int i = l; i <= r; i++) {
            if (a[i] != i) f = 1;
            if (a[i] == i) g = 1;
        }
        if (!f) cout << "0\n";
        else if (g) cout << "2\n";
        else cout << "1\n";
    }
    return 0;
}
```

---

## 作者：KaguyaH (赞：1)

> [CF1372C](https://codeforces.com/contest/1372/problem/C).
> [Github blog](https://9u46-mx.github.io/post/Solution-CF1372C/).

---

给定一个排列 $a$。每次可以将 $a$ 中一个区间打乱（每个位置都需要打乱），求使 $a$ 递增的最小操作数。

$1 \leqslant t \leqslant 100$，$1 \leqslant n \leqslant \sum n \leqslant 2 \times 10^5$。

---

若 $a$ 递增，答案为 $0$。

若 $a$ 中所有需要打乱的位置恰好构成一个区间，答案为 $1$。

其余情况，显然答案大于 $1$。考虑是否能通过一次操作将 $a$ 变成答案为 $1$ 的情况。

设第一个需要打乱的位置为 $l$，最后一个需要打乱的位置为 $r$。必然有 $r - l  \geqslant 2$。

令 $m = r - l + 1$，设一个排列 $s_{1 \cdots m}$，$s_i = a_{l + i - 1} - l + 1$，稍微转化一下问题，现有一个排列 $s_{1 \cdots m}(m > 3)$，找到一个排列 $t_{1 \cdots m}$，使得 $\forall\ 1 \leqslant i \leqslant m$ 满足 $t_i \ne s_i \land t_i \ne i$。在下文中请注意区分位置与值。

根据我们的假设，$\exists\ 1 \leqslant i \leqslant m$ 满足 $s_i = i$，设这个 $i$ 为 $p$。考虑最后确定 $t_p$。

$\forall\ i \ne p$ 有 $s_i \ne p$，故 $p$ 可以填在除 $t_p$ 外的任何一个位置。

---

我们假设 $\forall\ 1 \leqslant i \leqslant m \land i \ne p$ 都有 $s_i \ne i$（显然这样比较不优，如果这样可以找到 $t$ 则无此假设也能找到 $t$）。

我们需要在不包括 $p$ 的 $m - 1$ 个位置中，填上包括 $p$ 的任意 $m - 1$ 个值。由于 $p$ 可以填在任意一处，考虑尽量最后填 $p$。

这样的话，对于位置 $t_i$，我们可以填 $m - 3$ 个数（不可以填 $s_i$ 或 $i$ 或 $p$），所以在前 $m - 3$ 次填写中不会出现无法填写的情况。

对于第 $m - 2$ 与第 $m - 1$ 次填写，我们假设还剩下 $a, b, p$ 三个数。假设剩下 $u, v, p$ 三个位置。

那么，我们不可以完成 $t$ 的填写，当且仅当 $s_u = v \land s_v = u$ 且分别与 $a, b$ 相等（即 $a, b$ 均不能填在 $u$ 或 $v$）。

那么，我们只需要尽量使最后填写的 $(u, v)$ 不满足 $s_u = v \land s_v = u$ 即可。

这样的二元组最多有 $\lfloor \frac {m - 1} 2 \rfloor$ 个。最后填写的 $(u, v)$ 可以保证不满足上式，等价于 $m > 3$。

综上，当 $r - l + 1 > 3$ 即 $r - l \geqslant 3$ 时，通过一次操作可以变为答案为 $1$ 的情况，故答案为 $2$。

---

对于 $m = 3$，即 $r - l = 2$，由 $l, r$ 定义可知 $s_1 \ne 1$，$s_2 = 2$，$s_3 \ne 3$，故 $s = [3, 2, 1]$，可令 $t = [1, 3, 2]$，下次选择区间 $[l + 1, r]$ 重排即可。

---

综上，

- 若 $a$ 递增，答案为 $0$；
- 若 $a$ 中所有需要打乱的位置恰好构成一个区间，答案为 $1$；
- 其他情况，答案为 $2$。

---

好难证啊QAQ 感觉证麻烦了>\_<

---

```cpp
# include <cstdio>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
    }
    using namespace Source;
    namespace Solve {
        enum { N = (const uint)2e5 };
        uint n;
        uint a[N + 1];
        static inline const void main() {
            scanf("%u", &n);
            register bool f(true);
            for (register uint i(1); i <= n; ++i) scanf("%u", &a[i]), f = f and a[i] == i;
            if (f) return (const void)puts("0");
            register uint l(1), r(n);
            while (l <= n and a[l] == l) ++l;
            while (r >= 1 and a[r] == r) --r;
            for (register uint i(l); i <= r; ++i) if (a[i] == i) return (const void)puts("2");
            puts("1");
        }
    }
    static hu t;
    static inline const void main() {
        scanf("%hu", &t);
        for (hu i(0); i < t; ++i) Solve::main();
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：chenwenda316 (赞：1)

第三题是很有规律的，题意是：问最少要多少次操作让一个排列变成 $\left[1,2,\cdots,n\right]$ 。操作是，选择一个区间，重新排列使得所有区间内的数都不在原来位置上。

这道题可分三种情况讨论：
- 1.原序列已经是 $\left[1,2,\cdots,n\right]$；
- 2.原序列中，有一段区间中所有元素都错位；
- 3.其他情况

这三种情况分别输出0,1,2。

代码如下：
```cpp
#include <iostream>
#include <algorithm> 
using namespace std;
int main(){
	int a[200010];
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			a[i]=(x==i);
		}
		a[n+1]=1;
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(!a[i] && a[i+1]){
				cnt++;
			}
		}
		if(*min_element(a+1,a+1+n)==1)cout<<"0\n";
		else if(cnt==1)cout<<1<<endl;
		else cout<<2<<endl;
	}
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 先判断输入的排列是否升序，若**满足递增**，则直接输出 0。
- 构建数组 $c$ 表示 $a_{i}$ 和**升序排列**后的 $b_{i}$ 是否相同，若每次循环发现 $c_{i}$ 为 0，且是第一次，则 $flag$ 等于 1。若 $flag$ 等于 1 且这个位置的数**摆放正确**，则 $flag$ 等于 2。若 $flag$ 等于 2 且 $c_{i}$ 等于 0 则输出 2，结束本次测试。
- 若没有结束测试，则输出 1。

### 代码：

```
#include <bits/stdc++.h>

using namespace std;

int n;
int a[200005];
int b[200005];
bool c[200005];

void check() {
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++) b[i] = a[i];
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i ++) c[i] = a[i] == b[i];
	int flag = true;
	for (int i = 1; i <= n; i ++) {
		if (!c[i]) flag = false;
	}
	if (flag) {
		cout << 0 << endl;
		return;
	}
	flag = 0;
	for (int i = 1; i <= n; i ++) {
		if (!c[i] && flag == 0) flag = 1;
		else if (c[i] && flag == 1) flag = 2;
		else if (!c[i] && flag == 2) {
			cout << 2 << endl;
			return;
		}
//		cout << c[i] << " ";
	}
	cout << 1 << endl;
}

int main() {
	int t;
	cin >> t;
	while (t --) check();
	return 0;
}
   	  	 	    		 	 		 		 	    		
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1372C)

有趣的思维题。

首先考虑：即使在最坏的情况下，我们也可以将整个序列全部打乱，即对于任意 $a_i$，都有 $a_i\ne i$，然后再选择区间 $[1,n]$ 进行变换，就能使整个排列升序。

因此，我们得到结论：答案肯定 $\le2$。那么可以分类讨论。

答案为 $0$ 的情况：对于任意 $a_i$，都有 $a_i=i$。

答案为 $1$ 的情况：因为对于 $a_i=i$ 的点来说，由于你要么不动它，要么对它进行两次变换，所以更改它们显然不会使答案更优。因此，答案为 $1$ 时你不能变换 $a_i=i$ 的点，也就是说答案为 $1$ 时是只有一段连续区间不为升序。

答案为 $2$ 的情况：有多段区间不为升序，即除了以上两种情况外的其他情况。

然后直接模拟讨论即可。这里的转化是把序列 $a_i$ 变成一个 $01$ 序列 $b_i$（$a_i=i$ 时，$b_i=1$），然后判断是否只有一段连续为 $0$ 的区间。

时间复杂度 $O(tn)$，可以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
int flag0,flag1,flag2;
int t,n,sum,sum1,a[200005],b[200005];
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		memset(b,0,sizeof(b));
		for(ri i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]==i)
			{
				sum++;	
				b[i]=1;
			}					
		}
		if(sum==n)
		{
			cout<<0<<endl;
			sum=0;
			continue;
		}
		for(ri i=1;i<=n;i++)
		{
			if(b[i]==0)
				flag0=1;
			if(b[i]==1&&flag0==1)
				flag1=1;
			if(b[i]==0&&flag1==1)
			{
				cout<<2<<endl;
				flag2=1;
				break;
			}	
		}
		if(flag2==0)
			cout<<1<<endl;
		flag0=flag1=flag2=sum=0;
	}
    back 0;
}
```

---

## 作者：惟有泪千行 (赞：0)

题意：给你一个序列，每次可以让一个区间$[l,r]$全部错位，求最小次数。

首先我们可以知道答案是不会大于2的，因为第一次可以让所有的数不在自己的位置上，然后第二次全部回到该去的地方。

那么就还有1,0的情况。

对于等于0的情况，它一定是已经排好了的，~~不然你也不可能不动它啊~~。

而对于等于1的情况，回忆一下我们刚才如何得到2的——就可以发现得到2的主要原因是一开始需要将整个序列打乱，也就是说，如果有一个区间刚好错位，我们就可以用1次将它复原，所以当且仅当有一个错位的区间，此时的答案为1。

~~然后就可以A了QWQ~~

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,cnt;
inline int read(){
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int main(){
	t=read();
	while(t--){
		n=read(),cnt=0;
		int ls=0,flag=0;
		for(int i=1;i<=n+1;++i){
			if(i==n+1)m=1+n;
			else m=read();
			if(m==i){
				++cnt;
				if(ls){
					++flag;
					ls=0;
				}
			}
			else{
				if(!ls)ls=i;
			}
		}
		if(flag==1)puts("1");
		else if(cnt==n+1)puts("0");
		else puts("2");
	}
	return 0;
}
```



~~最优解第一~~

---

## 作者：Werner_Yin (赞：0)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13287218.html)
# 题目
[传送门](https://codeforces.com/contest/1372/problem/C)
## 题意
给你一个 $1$ 到 $n$ 的排列。

定义```特殊交换```为：选择一段区间$[l,r]$ ,使得此段区间上的数交换后都不在原来的位置。

问最少多少次可以将此排列变成升序的。

# 思路
## 前言
将语言错选成```C11```，```CE```了！

[见此前言](https://www.cnblogs.com/werner-yin/p/13286923.html)


## 定义
在正确的位置： 对于排列 $T$ ,若$T[i]=i(i\geq 1)$ ,则称 i 在正确的位置，否则，i 在错误的位置。

```wrong```: 整个排列错误的位置的个数。

```firstw```: 第一个错误的位置。

```lasw```: 最后一个错误的位置。
## 分析
我们可以发现，最多 $2$ 次即可。

当 $n=2$ 时， 显然最多 $1$ 次。

当 $n\geq2$ 时，有一个通用的解法：

设原来序列为 $T$ , 目标的升序序列为 $S$ 。

则我们可以选择$[1,n]$ ,第一步将 $T$ 变成 各个位置与 $T$ , $S$ 不同的序列 $K$，在 $n\geq3$ 下，$K$ 必定存在。

再将其变为 $S$。

接下来考虑能否用更少的次数，

用 0 次，则必须已经排好序。

用 1 次，则代表错误的位置连成一片，则一次即可矫正。

## 算法
变量含义见前文定义。

如果 没有错误 即 ```wrong```==0 ,答案为 0

如果 有错误但错误连成一片，即$wrong== lasw - firstw + 1$ ,则答案为 1

否则 答案为 2

# 代码
```cpp
/* 
	* Author :Werner_Yin 
	* Time: 2020-07-11 23:51:29
	* I believe I can AC !
*/ 
#include <bits/stdc++.h>
#define lol long long
#define GDB(x) cout<<"DATA "<<#x<<" :"<<x<<endl; 
#define mes(x) memset(x,0,sizeof(x))
using namespace std;
template <typename T>
void re(T &x){
	#define ge getchar() 
	x = 0;int sgn = 1;char ch = ge;
	for(;!isdigit(ch);ch = ge) if(ch == '-') sgn = -1;
	for(;isdigit(ch);ch = ge) x = (x<<1)+(x<<3)+(ch^48);
	x *= sgn;
}
template <typename T>
void write(T x){
	if(x == 0) putchar(48);
	else if(x < 0) putchar('-');
	int k = 0,que[20];
	while(x > 0){
		que[++k]=x % 10;
		x /= 10;
	}
	for(int i = k;i > 0;i--) putchar(que[i] + 48);
	return;
}
const int MAXN = 1e5 + 10;
int a,wrong; 
int main (){
	int T;
	re(T);
	while(T--){
		int n;
		re(n);
		wrong = 0;
		int firstw = n,lasw = 0;
		for(int i = 1;i <= n;i++) {
			re(a);
			if(i !=a ) {
				firstw = min(firstw,i);
				lasw = i; 
				wrong++;
			}
		}
		int ans = 0;
		if(wrong == 0) ans = 0;
		else if(lasw - firstw + 1 == wrong) ans = 1;
		else ans = 2;
		write(ans);
	}
	return 0;
}
```

---

## 作者：xiexinzhe (赞：0)

# 题意
给你一个 $1$ 到 $n$ 的排列，定义```特殊交换```为：选择一段区间 $[l,r]$，使得此段区间上的数交换后都不在原来的位置。问最少多少次```特殊交换```可以将此排列变成升序的。

# 解答
首先我们要找到一个区间 $[l,r]$ 使区间外的数是升序排列的。接着就要分布判断。
## 分步
- 如果区间内没有数，就说明这个序列已经是升序排列，直接输出 $0$。
- 如果区间内每个数都不在自己的位置上，那么只需要 $1$ 步，就可以让这个序列成为升序排列。
- 剩下的，一定可以在 $2$ 步内完成升序排列。
### 码风不咋地，写得有点长
```cpp
#include <bits/stdc++.h>
using namespace std;
int l,r,t,n,a[200001];
bool pd1();
bool pd2();
int main()
{
    cin>>t;
    for(int pp=1;pp<=t;pp++)
	{
        cin>>n;
        for (int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
        for (l=1;l<=n;l++)//寻找区间开始
        {
        	if (a[l]!=l)
        	{
        		break;
			}
		}
        for (r=n;r>=1;r--)//寻找区间结束
        {
        	if(a[r]!=r)
            {
            	break;
			}
		}
        if(pd1())//已经是升序排列
		{
			cout<<0<<endl;
		}
        else if(pd2())//全部不在自己的位置上
		{
			cout<<1<<endl;
		}
        else//其他情况
		{
			cout<<2<<endl;
		}
    }
    return 0;
}
bool pd1()
{
	for(int i=l;i<=r;i++)
	{
        if(a[i]!=i)//如果不等于，说明并不是升序排列
		{
			return false;
		}
    }
    return true;
}
bool pd2()
{
	for(int i=l;i<=r;i++)
	{
        if(a[i]==i)//如果等于，说明不是完全不对
		{
			return false;
		}
    }
    return true;
}
```

---

