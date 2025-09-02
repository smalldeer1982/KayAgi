# Di-visible Confusion

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，对于每个位置 $i$，如果 $a_i\%\left(i+1\right)\not=0$，就可以将 $a_i$ 删掉。删掉之后，后面的数都会往前面移动一位。问能否将序列删成空。

## 说明/提示

$1\le t\le10^4,1\le n\le10^5,1\le \sum n\le3\times10^5,1\le a_i\le10^9$。

## 样例 #1

### 输入

```
5
3
1 2 3
1
2
2
7 7
10
384836991 191890310 576823355 782177068 404011431 818008580 954291757 160449218 155374934 840594328
8
6 69 696 69696 696969 6969696 69696969 696969696```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：cyhyyds (赞：5)

首先读题，发现一个性质：

如果 $a_i$ 不被删去，那么 $(a_i \ \bmod \ 2···,i + 1 )= 0$。

这样就启发我们对于每一个 $a_i$ 枚举 $2$ 到 $i+1$。

但是当交上这一份**看似是暴力**的代码时，发现 AC 了！

分析一下时间复杂度：

如果 $a_i$ 不被删去，那么它应该是 $\operatorname{lcm} (2,3···,i+1)$。

而观察到 $a_i\le 10^9$，且 $\operatorname{lcm}(2,3···,23)\ge 10^9$，也就是说对于一个 $a_i$ ，我们最多枚举 $22$ 次。

那么时间复杂度就是 $O(22n)$。

代码如下：
```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 7;

int T, n, a[N];

int main () {
	scanf ("%d", &T);
	
	while (T --) {
		scanf ("%d", &n);
		for (int i = 1; i <= n; i ++) {
			scanf ("%d", &a[i]);
		}
		bool ot = false;
		for (int i = 1; i <= n; i ++) {
			bool fg = false;
			for (int j = 1; j <= i; j ++) {
				if (a[i] % (j + 1)) {
					fg = true;
					
					break;
				}
			}
			if (fg == false) {
				cout << "NO" << endl;
				
				ot = true;
				
				break;
			}
		}
		
		if (ot == false) {
			cout << "YES" << endl;
		}
	}
	
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> CF1603A. [Di-visible Confusion](https://codeforces.ml/problemset/problem/1603/A) *1300

我们每次操作最右边可以删除的位置是最优的，因为不会将原来可操作的变得不可操作，而如果一个数左边的所有数都可以被删除，那么它一定可以经过 $1\sim i$ 这些位置，因此一个数 $a_i$ 能被删去的**必要但不充分条件**是 $\mathrm{lcm}(2\sim (i+1))\nmid a_i$，因为若左边有些数无法删除，那么即是满足上述条件也不一定可以删去 $a_i$。但综合来看，有解即所有数被删除的**充要条件**是 $\forall i\in [1,n],\mathrm{lcm}(2\sim (i+1))\nmid a_i$。由于 $\mathrm{lcm}(2\sim 100)\gg 10^9=\max a_i$ 所以判断一个数是否符合条件只需要试除到 $\min(i+1,100)$ 即可。时间复杂度 $\mathcal{O}(100\times n)$。

```cpp
int main(){
	int T; cin >> T;
	while(T--) {
		int n, ans = 1, a; cin >> n;
		for(int i = 1; i <= n; i++) {
			bool div = 0; cin >> a;
			for(int j = 1; j <= min(100, i + 1); j++) div |= a % j > 0;
			ans &= div;
		} puts(ans ? "YES" : "NO");
	}
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

我们可以考虑模拟整个删除过程。然而，直接模拟可能会非常低效，因为每次删除一个元素后都需要重新计算后续所有元素的位置和条件。我们可以使用一个标记数组或者布尔数组来跟踪哪些位置上的元素可以被删除，然后一次性地执行所有可能的删除操作。

敲黑板，讲思路：

初始化一个布尔数组 `a[n]`，其中 `a[i]` 表示位置 i 上的元素是否可以被删除（即 `a[i] % (i + 1) != 0）`。
遍历这个布尔数组，如果 `a[i]` 为 true，则标记位置 $i$ 上的元素为已删除。
在遍历过程中，我们需要更新剩余未删除元素的索引，因为删除操作会使后续元素的索引前移。这可以通过使用一个变量 `k` 来追踪当前未删除元素的最后一个索引来实现。
在遍历结束后，检查 `k` 是否为 $-1$，这表示所有元素都被删除了。如果是，则输出 `YES`，否则输出 `NO`。

---

## 作者：ImmortalWatcher (赞：1)

假设 $a_i$ 以前的数都可以被删，那么 $a_i$ 能被删只需要满足 $2\sim i+1$ 之间有一个不被 $a_i$ 整除的数即可。

所以可以考虑一个这样的做法：

从 $1$ 到 $n$ 枚举 $a_i$，判断 $2\sim i+1$ 之中有没有整除不了的数，如果都没有，那么这个 $a_i$ 就不会被删，也就不合法。

看似这个算法是 $O(n^2)$ 的，实际上如果要 $2\sim i+1$ 都整除，那就至少是它们所有数的 $\text{lcm}$ 的倍数，但 $a_i\le 10^9$，所以这个循环根本不会跑太多次，可以通过本题。

**code**
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int T,n,a[100010],d[100010];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		bool flag=false;
		for (int i=1;i<=n;i++)
		{
			bool bj=false;
			for (int j=i+1;j>=2;j--)
				if (a[i]%j)
				{
					bj=true;
					break;
				}
			if (!bj)
			{
				puts("NO");
				flag=true;
				break;
			}
		}
		if (!flag) puts("YES");
	}
	return 0;
}
```


---

## 作者：orz_z (赞：0)

### 题目大意

给一个长度为 $n$ 的序列 $a$，对于每个位置 $i$，如果 $a_i \bmod (i+1)\ne0$，就可以将 $a_i$ 删掉。

删掉之后，后面的数都会往前面移动一位。

问能否将序列删成空。

对于 $100\%$ 的数据，$1≤t≤10^4,1≤n≤10^5,1≤\sum n≤3×10^5,1≤a_i≤10^9$。


### 解题思路

首先可以知道，通过删除操作，任何一个数向前移动而不能向后。

那么如果这个序列中有至少一个 $a_i$ 满足 $\forall 1 \leq j \leq i,a_i \bmod j=0$，那么一定无解。 

根据数论知识

> 如果一个数 $x$ 被一个集合 $a$ 的数的 `Lcm`整除，那么 $x$ 整除这个集合内的所有数。

那么循环判断时，可以顺便维护一下 `Lcm`。

时间复杂度 $\mathcal O(tn)$。

反之一定有解。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

long long T, n, a[100005];

long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

signed main()
{
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld", &n);
		for (long long i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		long long now = 1, flag = 1;
		for (long long i = 1; i <= n; i++)
		{
			now = now / gcd(now, i + 1) * (i + 1);
			if (a[i] % now == 0)
			{
				printf("NO\n");
				flag = 0;
				break;
			}
		}
		if (flag)
			printf("YES\n");
	}
	return 0;
}
```



---

## 作者：Daidly (赞：0)

有趣的题。

发现性质：删掉这个数之前的数对其有影响，之后无影响。

考虑如何处理 $a_i \bmod (i+1)=0$ 的数：

把所有可删的数删完，判断剩下的数是否能删即可。

具体的说，对于剩下的不可删的数 $x$，寻找最大的 $i$ 使得 $ans\bmod (i+1)\ne0$，若 $i<1$ 则证明无法删除，反之可删，删除的位置为 $i$，因为可以通过删除其他数使 $x$ 到达 $i$。

注意多测清空。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=1e5+5;
int t,n,a[MAXN],num,cnt;
queue<int>q;
bool f;

int calc(int x,int i){
	int ans=i;
	while(ans--){
		if(x%(ans+1)!=0)return ans;
	}
	return 0;
}

int main(){
	t=read();
	while(t--){
		n=read();
		num=0,cnt=0,f=1;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]%(i+1)==0){
				num++;
				q.push(i);
			}
		}
		while(!q.empty()){
			int x=q.front();
			q.pop();
			if(calc(a[x],x)<1){
				f=0;
				while(!q.empty())q.pop();
				break;
			}
		}
		if(f)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

结论题。

如果这个序列中有至少一个位置上 $a_i$ 可以整除小于等于 $i$ 的所有数，那么一定无解。
反之一定有解。

---
考虑如何证明这个结论。

对于满足上述条件的而无解的原因是：任何一个数只能通过删除前面的某一个数向前移动而不能向后。这个是显然的。

然后只要构造出一组可行操作就行了。考虑从后往前扫描，一旦遇到可行的就立即对其进行操作，并回到最后，若不行则向前扫描。

这样做的话一定不会出现将某一个值从可行的位置上漏过去从而导致不可行的情况，也不会有使得某一种情况无法操作的情况。

其实本质上就是使得所有的都向前挪从而遍历整个序列。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long T,n,a[100005];
long long gcd(long long a,long long b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]);
		long long now=1,flag=1;
		for(long long i=1;i<=n;i++){
			now=now/gcd(now,i+1)*(i+1);
			if(now==0){
				printf("NO\n");
				flag=0;
				break;
			}
			if(a[i]%now==0){
				printf("NO\n");
				flag=0;
				break;
			}
		}
		if(flag)
		printf("YES\n");
	}
	return 0;
}
```


---

## 作者：KAMIYA_KINA (赞：0)

## Tag

数论，找规律。

## Description

给定一个长度为 $n$ 的序列，$a_i$ 可以被删掉当且仅当 $i+1\not| \,\, a_i$，如果某一个 $a_i$ 被删掉之后 $i$ 后面的元素会补到当前位置，求这个序列是否可以被全部消掉。

$T$ 组询问。

$\texttt{data range:} T\leq 10000, n\leq 10^5, \sum n\leq 3\times 10^5,a_i\leq 10^9$。

## Solution

之前我第一眼看错了题，以为是个弱智题，结果发现读错了题，但是仔细一想，发现读错的题的做法就是正解。

考虑位置为 $a_i$ 什么时候才能被消掉，如果后面的数被消掉不会对当前位置造成影响，如果前面的数被削掉，那么就会向前面移动一位，所以一个数被削掉当且仅当一个数前面的数都可以被消掉而且 $2,3\cdots,i+1$ 有一个数不整除 $a_i$。

~~我之前看错的题就是这玩意。~~

假设 $a_i,\cdots, a_n$ 都整除当前位置，那么如果 $a_{i-1}$ 不被整除，就直接干掉 $a_{i-1}$ ，这样所有的 $a_i,\cdots ,a_n$ 都可以向前移动一格，然后重复过程。

假设此时 $a_1$ 不能被消掉，那么无论如何 $a_1$ 都没有办法移动到其他地方去，那么整局就没了。

根据上面两个假设就可以得到结论了。

由于 $a_i\leq 10^9$，所以暴力往前找就可以了，不被整除显然得是 $\operatorname{lcm}(2,3,\cdots,i+1)$ 整除 $a_i$，但是 $\operatorname{lcm}(2,\cdots, 23)\ge 10^9$，所以暴力枚举最多跑 $23$ 次。

## Code

```cpp
const int N = 1e5 + 1;

int n;
int a[N];

inline void solve() {
    int t = rd;
    while(t--) {
        n = rd;
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            int x = rd;
            bool ok = false;
            for(int j = i + 1; j >= 2 && flag; j--) {
                if(x % j != 0) {
                    ok = true;
                    break;
                }
            }
            flag = ok;
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return ;
}
```



---

