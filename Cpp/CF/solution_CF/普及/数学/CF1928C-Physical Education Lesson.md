# Physical Education Lesson

## 题目描述

In a well-known school, a physical education lesson took place. As usual, everyone was lined up and asked to settle in "the first– $ k $ -th" position.

As is known, settling in "the first– $ k $ -th" position occurs as follows: the first $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , the next $ k - 2 $ people have numbers $ k - 1, k - 2, \ldots, 2 $ , the next $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , and so on. Thus, the settling repeats every $ 2k - 2 $ positions. Examples of settling are given in the "Note" section.

The boy Vasya constantly forgets everything. For example, he forgot the number $ k $ described above. But he remembers the position he occupied in the line, as well as the number he received during the settling. Help Vasya understand how many natural numbers $ k $ fit under the given constraints.

Note that the settling exists if and only if $ k > 1 $ . In particular, this means that the settling does not exist for $ k = 1 $ .

## 说明/提示

In the first test case, $ k $ equals $ 2, 3, 5, 6 $ are suitable.

An example of settling for these $ k $ :

  $ k $ / № $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ 9 $  $ 10 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 5 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 6 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  In the second test case, $ k = 2 $ is suitable.

## 样例 #1

### 输入

```
5
10 2
3 1
76 4
100 99
1000000000 500000000```

### 输出

```
4
1
9
0
1```

# 题解

## 作者：int_R (赞：7)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18013970/CF1928C)

[原题链接](https://www.luogu.com.cn/problem/CF1928C)

先考虑暴力枚举每个 $k$ 是否合法，发现 $k$ 合法当且仅当 $(2k-2)\mid (n-x)$ 或者 $(2k-2)\mid (n+x-2)$ 并且 $k\geq x$。因为当 $n$ 处于每一段中的第 $1\sim k$ 个数中时 $n-x$ 是上一段的结尾，$n$ 处于每一段中的第 $k\sim 2k-2$ 个数中时 $n+(x-2)$ 是这一段的结尾。

所以直接枚举 $n-x$ 和 $n+(x-2)$ 的因数 $p$，要保证 $2\mid p$ 并且 $\dfrac{p+2}{2}\geq x$。注意可能有重复的，可以用 set 去重。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<set>
#include<math.h>
using namespace std;
int T,x,n;set <int> s;
inline void A(int y)
    {if(!(y&1)&&y/2+1>=x) s.insert(y);}
inline void work()
{
    cin>>n>>x;
    int a=n-x,b=n+(x-2);
    for(int i=1;i<=sqrt(a);++i)
        if(!(a%i)) A(i),A(a/i);
    for(int i=1;i<=sqrt(b);++i)
        if(!(b%i)) A(i),A(b/i);
    cout<<s.size()<<'\n';s.clear();
}
int main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：信息向阳花木 (赞：7)

感觉就是数学题（？）

讨论 $x$ 是在第一段还是在第二段。

设 Vasya 在第 $m + 1$ 组，他前面有 $m$ 组，有 $m \times t$ 人。其中 $t$ 是每组的人数 $2k - 2$。我们求的是可能的 $k$ 个数。

如果 $x$ 在第一段，可知 $m \times t + x = n$。求 $k$ 的个数也相当于求 $t$ 的整数解个数。解上面的方程得 $t = \frac{n - x}{m}$。又因为 $k = \frac{t + 2}{2}$，所以要使 $k$ 是整数，$t$ 必须是偶数。所以第一段 $k$ 的个数就是 **$n-x$ 的偶因子个数**。注意检验，$x$ 要满足第一段的要求：$1 \leq x \leq k$。算出 $k$ 后检验一下就好了。

第二段同理。写的式子就是 $m \times t + 2k - x = n$。
这里 $2k - x$ 是 Vasya 在这组里面排的位置。例如他在第二段编号是 $k - 1$，所在位置就是第 $k + 1$ 个位置。将 $k = \frac{t + 2}{2}$ 带入式子，化简得 $(m + 1) \times t = n + x - 2$。同理，$k$ 的个数就是 **$n + x - 2$ 的偶因子个数**。还是要检验，$x$ 要在第二段就必须满足 $2 \leq x \leq k - 1$。不满足的就舍去。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int t, n, x;
int a[N];

int main()
{
    scanf("%d", &t);
    while (t -- )
    {
        scanf("%d%d", &n, &x);
        int p = n - x, q = n + x - 2, res = 0;
        for (int i = 1; i <= p / i; i ++ )
        {
            if(p & 1) break;
            if(p % i == 0)
            {
                if(i % 2 == 0)
                {
                    int k = (i + 2) / 2;
                    if(x >= 1 && x <= k) res ++;
                }
                int j = p / i;
                if(j != i && j % 2 == 0)
                {
                    int k = (j + 2) / 2;
                    if(x >= 1 && x <= k) res ++;
                }
            }
        }
        for (int i = 1; i <= q / i; i ++ )
        {
            if(q & 1) break;
            if(q % i == 0)
            {
                if(i % 2 == 0)
                {
                    int k = (i + 2) / 2;
                    if(x > 1 && x < k) res ++;
                }
                int j = q / i;
                if(j != i && j % 2 == 0)
                {
                    int k = (j + 2) / 2;
                    if(x > 1 && x < k) res ++;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
```

---

## 作者：HappyJaPhy (赞：4)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF1928C)
- [原题传送门](https://codeforces.com/problemset/problem/1928/C)

# 题意
- 一种上下波动的数组，给出所在的位置 $n$ 和对应的数字 $x$，求出有几种数组满足条件。令 $k$ 为最大值，则数组长成这样子：

$$1,2,3,\cdots,k-1,k,k-1,k-2,\cdots,2,1,2,3,\cdots$$

- 如图，每 $2(k-1)$ 就循环一次。

![](https://cdn.luogu.com.cn/upload/image_hosting/zdbgkisf.png)

# 分析
- 因为每 $2(k-1)$ 个数就循环一次，因此可以列出同余方程 $n\equiv x\pmod{2(k-1)}$，若 $x\neq1$，则还可以列出 $n\equiv2k-x\pmod{2(k-1)}$，可以化成 $n\equiv2-x\pmod{2(k-1)}$。

- 因此问题就转化成了怎么求解 $a\equiv b\pmod x$ 中的 $x$。转化一下得 $a-b\equiv0\pmod x$，也即 $x\mid a-b$，因此答案就是 $a-b$ 的偶数约数个数。复杂度 $O(\sqrt n)$。

- 注意事项：如果 $k=x$ 时成立的话，在两个式子里都会被统计一次，因此要注意判重。

# AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1e9
using namespace std;
int x, n;

inline int read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') {
		ch = getchar();
		if (ch == '-')
			m *= -1;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return x;
}

inline void print(int x) {
	if (x < 0)
		putchar('-'), x = -x;
	static int stk[50];
	int top = 0;
	do {
		stk[top++] = x % 10;
		x /= 10;
	} while (x);
	while (top) {
		putchar(stk[--top] + 48);
	}
	putchar('\n');
	return ;
}

inline bool check(int i, int b, int x) {
	return !(i & 1) && i > 2 && (i / 2 + 1) >= x && !(b != x && (i / 2 + 1) == x); //注意判重
}

inline int work(int a, int b, int x) {
	int m = a - b, res = 0;
	for (int i = 1; i * i <= m; i++) {
		if (m % i == 0) {
			if (check(i, b, x)) res++;
			if (check(m / i, b, x)) res++; //记录答案
		}
	}
	return res;
}

signed main() {
	int T;
	read(T);
	while (T--) {
		read(n), read(x);
		int res = work(n, x, x);
		if (x != 1) res += work(n, 2 - x, x); //x 不等于 1 时有另一种可能
		if (!((n - x) & 1) && x <= 2) res++; //k=2的方案
		print(res);
	}
	return 0;
}
```
- 感谢围观！

---

## 作者：UniGravity (赞：3)

## Solution CF1928C Physical Education Lesson
洛谷[传送门](https://www.luogu.com.cn/problem/CF1928C)

更新：修改了复杂度的错误。

### 题意
定义一个 $k$ 位数列为前 $k$ 个数是 $1,2,3,\ldots,k$，接下来 $k-2$ 个数是 $k-1,k-2,\ldots,2$，在接下来 $k$ 个数是 $1,2,3,\ldots,k$，如此循环。

现在你知道这个数列的第 $n$ 项是 $x$，求所有可能的 $k$ 的数量。

### 做法
一道很有意思的题目。

------------

首先序列长这个样子：   
![](https://cdn.luogu.com.cn/upload/image_hosting/zdbgkisf.png)

发现序列循环的长度是 $2k-2$，可以从题意得出。

假设我们知道 $n$ 在第几个循环中，假设这个循环的**结尾**为 $y$，那么可得：
$$y=2k-2$$
想要求出所有 $k$ 的值，只需要对 $\frac{y+2}{2}$ 进行分解因数即可。

这里需要注意如果 $y+2$ 是奇数那么没有满足条件的 $k$，且 $k$ 的值不为 $1$。

------------

我们发现第 $n$ 个数有两种可能，进行分类讨论：

------------

第一种情况，$n$ 在**上升序列**中，即下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/dr705vnv.png)
我们发现由于知道了 $x$ 和 $n$，且我们知道序列是公差为 $1$ 的等差数列，我们可以方便的得出 $y$ 值（见上文）：
$$n-x-2=2k-2$$

按照上文求因数即可。

------------

第二种情况，$n$ 在**下降序列**中，即下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/iuvdxgwm.png)
我们也可以得出这个式子，求出 $k$ 的值：
$$n+x-4=2k-2$$

------------

然后我们发现一个问题，$k$ 的值在这两种情况中可能重复，即在数列的顶端。

由于求因数，$k$ 的数量级为 $\sqrt{n}$，发现这个数字不大，可以直接把算出来的 $k$ 丢进 set 里，输出答案时直接输出 set 的大小。

当然如果开个桶也是可以的。

那么就做完了，复杂度 $O(\sqrt{n}\log n)$，但是能通过。

### 代码
```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

int t;
int n, x, n1, n2;
set< int > st;

inline void ins(int k) {
	if (k >= x) st.insert(k);
}

inline void work() {
	scanf("%d %d", &n, &x);
	st.clear();
	n1 = n - x;
	if (n1 % 2 == 0) {
		n1 /= 2;
		for (int i = 1; i * i <= n1; i++) {
			if (n1 % i == 0) {
				ins(i + 1);
				if (i != n1 / i) ins(n1 / i + 1);
			}
		}
	}
	n2 = n + x - 2;
	if (n2 % 2 == 0) {
		n2 /= 2;
		for (int i = 1; i * i <= n2; i++) {
			if (n2 % i == 0) {
				ins(i + 1);
				if (i != n2 / i) ins(n2 / i + 1);
			}
		}
	}
//	for (set< int >::iterator it = st.begin(); it != st.end(); it++) printf("%lld ", *(it));
	printf("%d\n", (int) st.size());
}

// 2 4 6 -> 1 2 3

int main() {
	scanf("%d", &t);
	while (t--) {
		work();
	}
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：3)

定义：$2$ 的循环节为 $1,2$，$3$ 的循环节为 $1,2,3,2$，以此类推。显然，$k$ 的循环节长度为 $k\times2-2$。

注意到第 $n$ 个数字可能处于一段循环节的末尾或者前面，考虑分类讨论：

1. 在前面时：等价于有多少个循环节可以**恰好**拼成长度为 $n-x$ 的序列。

2. 在后面时：等价于有多少的循环节可以**恰好**拼成长度为 $n+x-2$ 的序列。

以上两种情况结合样例显然可得。

单独考虑情况 $1$：考虑枚举循环节长度 $[1,\sqrt n]$，对答案进行统计（具体见代码，用文字难以表述）。

考场上，我蒯了情况一的代码来算情况二并加到一起，但是发现算重了。考虑到对自身并不会容斥的现状的深刻认识，我开了一个 map 容器来去重，顺利通过了本题。

[记录](https://codeforces.com/contest/1928/submission/245928180)

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6;
map<int,int>mp;
int calc(int x,int y){
	int ans=0;
	for(int i=1;i*i<=x;++i)
		if(x%i==0){
			int k=x/i;
			if(i%2==0&&(i+2)/2>=y&&!mp[i])++ans,mp[i]=1;
			if(k!=i&&(k+2)/2>=y&&k%2==0&&!mp[k])++ans,mp[k]=1;
		}
	return ans;
}

void solve(){
	mp.clear();
	int n,x,k,ans=0;cin>>n>>x;
	//1、处于序列开头
	k=n-x;
	ans+=calc(k,x);
	//2、处于序列末尾
	k=n+x-2; 
	ans+=calc(k,x);
	printf("%d\n",ans);
}
signed main(){
	ios::sync_with_stdio(cin.tie(cout.tie(0)));
	int T=1;for(cin>>T;T--;)solve();
	return 0;
} 
```


---

## 作者：apiad (赞：1)

由于 $n \le 10^9$。不可能线性，想到如何降到根号级别。

求因数就是根号！

但是还得分讨。

- 如果 $x$ 在递增的段上，那么我们需要枚举 $n-x$ 的因数，也就是枚举 $2k-2$ 可以取的值。注意，这个因数必须是偶数，因为 $2k-2$ 是偶数吗，并且这个因数要小于等于 $k$。最后还需要特判一下 $n-x$ 本身是他的因数哦。

- 还有一种情况，$x$ 在递减序列上。我们枚举 $n-x+2$ 的因数，为啥呢，我们要枚举这个下降序列结束的那个点的因数，为啥要 $-2$？你自己手玩一下就知道了。这个因数本质根上面一种也是一样的。

在上述两种中找到了合法的 $k$ 我们怕有重复，所以直接丢进 set，最后输出它的大小即可。

时间复杂度是 $O( \sqrt n \log n)$。

[code](https://codeforces.com/contest/1928/submission/245848172)。

---

## 作者：Cure_Wing (赞：1)

[CF1928C Physical Education Lesson](https://www.luogu.com.cn/problem/CF1928C)

### 思路

我们发现，由于 $k>1$，整个长度为 $2k-2$ 的区间可以分为两个阶段：第一段是 $1\sim k$ 的上升，第二段是 $k-1\sim2$ 的下降。于是我们分这两种情况讨论。

当他处于上升的报数时，前一个完整循环的长度为 $n-x$，因为相对于之前多了 $1\sim x$ 的报数。由于前 $n-x$ 个数组成了任意多次完整的循环，所以我们可以枚举 $n-x$ 的因数，得到的就是 $2k-2$，然后检验一下解出的 $k$ 是否符合要求即可。检验的主要有两个内容，一是 $k$ 是大于 $1$ 的整数，二是 $k$ 要大于或等于 $x$，否则不可能报到 $x$。

当他处于下降的报数时，把这个循环报完后总长度为 $n+x-2$，因为还需要报 $x-1\sim2$ 才能完成循环。由于这也是完整的循环，我们可以按照前一段的方法寻找 $k$。

对于 $k=x$ 的特殊情况，$x$ 处于上升段有可能视作下降段，但是对于这种情况下的 $n,x$，解出来的 $k$ 一定相同，所以无需在意。

时间主要消耗在枚举因数，时间复杂度 $O(\sum\sqrt{n+x})$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using std::cin;using std::cout;
int t,n,x,ans;
std::map<int,bool>p;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<'\n'){
		cin>>n>>x;p.clear();p[1]=1;ans=0;
		for(int i=1;1ll*i*i<=n-x;++i)
			if((n-x)%i==0){
				int t1=(i+2)/2,t2=((n-x)/i+2)/2;
				if((i+2)%2==0&&t1>=x){ans+=!p[t1];p[t1]=1;}
				if(((n-x)/i+2)%2==0&&t2>=x){ans+=!p[t2];p[t2]=1;}
			}
		for(int i=1;1ll*i*i<=n+x-2;++i)
			if((n+x-2)%i==0){
				int t1=(i+2)/2,t2=((n+x-2)/i+2)/2;
				if((i+2)%2==0&&t1>=x){ans+=!p[t1];p[t1]=1;}
				if(((n+x-2)/i+2)%2==0&&t2>=x){ans+=!p[t2];p[t2]=1;}
			}
	}
	return 0;
}
```

---

## 作者：w9095 (赞：1)

[CF1928C Physical Education Lesson](https://www.luogu.com.cn/problem/CF1928C)

我们发现，每 $2k-2$ 个数构成了一个周期。其中，前 $k$ 个数为前周期，后 $k-2$ 个数为后周期。我们对于 $x$ 所处的周期进行分类讨论。

当 $x$ 在前周期时，它是周期中的第 $x$ 个元素。将总数 $n$ 减去 $x$，剩下的数一定是由若干个完整的周期组成。枚举它的约数，我们可以用这个约数解出 $k$ 的值。只有 $k$ 为整数且 $k\ge n$，才能算作一个解，因为前周期最大的数是 $k$。

当 $x$ 在后周期时，它是周期中的第 $2k-2-x+2$ 个元素。将总数 $n$ 减去 $2k-2-x+2$，剩下的数 $(n+x-2)-(2k-2)$ 一定是由若干个完整的周期组成。我们发现，减去的 $2k-2$ 正好是我们要枚举的约数，并不影响 $(n+x-2)$ 对 $2k-2$ 的整除性。所以我们直接枚举 $(n+x-2)$ 的约数，我们可以用这个约数解出 $k$ 的值。只有 $k$ 为整数且 $k\gt n$，才能算作一个解，因为后周期最大的数是 $k-1$。

注意 $x$ 在后周期时，$x\ne1$，因为我们发现后周期没有 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,x,n;
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0,now=0;
	   	scanf("%lld%lld",&x,&n);
	   	now=x-n;
	   	for(long long i=1;i*i<=now;i++)
	   	    if(now%i==0)
		   	    {
		   	    	if(i%2==0&&(i+2)/2>=n)ans++;
		   	    	if((now/i)!=i&&(now/i)%2==0&&((now/i)+2)/2>=n)ans++;
				}
		now=x+n-2;
		if(n!=1)
		   for(long long i=1;i*i<=now;i++)
		   	    if(now%i==0)
			   	    {
			   	    	if(i%2==0&&(i+2)/2>n)ans++;
			   	    	if((now/i)!=i&&(now/i)%2==0&&((now/i)+2)/2>n)ans++;
					}
		printf("%lld\n",ans);
	   }
	return 0;
}
```

---

## 作者：PLDIS (赞：0)

第 $n$ 项是 $x$ 所在周期有两种情况：一种是形如 $1,2,\dots,x$，另一种是形如 $k,k-1,\dots,x$。

对这两种分讨，以前者为例。

首先，将最后一个 $1$ 到最后一个元素之间的数（含端点）删去，此时，数列只剩下 $1,2,\dots,k-1,k,k-1,\dots,2$ 这样的长度为 $2k-2$ 的周期。

这时，将剩下的数列个数求一遍约数个数即可。

两种情况需要去重。

**注意**：约数需要特判 $< x$ 的情况，因为如果 $k \leq x$，数列中就不可能有 $x$ 了。

```cpp
int find_p(int x, int y, int k){
	// 这里将两个情况混合起来考虑，注意要 unique 然后二分。
	vector<int> vec;
	for(int i = 1; i * i <= x; i++){
		if(i * i == x){
			if(i % 2 == 0) vec.push_back(i);
		}
		else if(x % i == 0){
			if(i % 2 == 0) vec.push_back(i);
			if((x / i) % 2 == 0) vec.push_back(x / i);
		}
	}
	for(int i = 1; i * i <= y; i++){
		if(i * i == y){
			if(i % 2 == 0) vec.push_back(i);
		}
		else if(y % i == 0){
			if(i % 2 == 0) vec.push_back(i);
			if((y / i) % 2 == 0) vec.push_back(y / i);
		}
	}
	sort(vec.begin(), vec.end());
	vector<int>::iterator pos = unique(vec.begin(), vec.end());
	return pos - lower_bound(vec.begin(), pos, k * 2 - 2) + 1;
}
 
void solve(int testcase, ...){
	int n, x; cin >> n >> x;
	cout << find_p(n - x, n + x - 2, x) - 1 << endl;
}
```

---

## 作者：CEFqwq (赞：0)

毒瘤，最后一分钟才切掉。思路很简单，实现很恶心。

因为第 $n$ 个数为 $x$，显然分类讨论：

1. $n \equiv x \pmod {2k-2}$。

2. $(n+x-2) \equiv 0 \pmod {2k-2} $。

那么先线性筛，然后把 $n-x$ 和 $n+x-2$ 分别枚举质因数，然后写两个 dfs 枚举可能的 $k$ 即可。

每次 dfs 枚举的个数不会大于 $10000$。而且 $1 \leq t \leq 100$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,ttn,tttn;
int a[200005],cnt=0;
bool vis[200005];
int zy[200005],ccnt=0,ans;
set<int>S;
map<pair<int,int>,bool>vs;
void dfs(int i,int now) {//第一种情况
	if(S.find(now)==S.end()) {
		S.insert(now);
		if(now%2==0&&(now+2)/2>=x&&ttn%now==x) {
		//	cout<<now<<"\n";
			ans++;
		}
	}
	if(vs[make_pair(now,i)]==1)return;
	vs[make_pair(now,i)]=1;	
	if(i==ccnt+1)return;
	dfs(i+1,now*zy[i]);
	dfs(i+1,now);
}
void dfs2(int i,int now) {//第二种情况
	if(S.find(now)==S.end()) {
		S.insert(now);
		if(now%2==0&&(now+2)/2>=x) {
		//	cout<<now<<"\n\n";
			ans++;
		}
	}
	if(vs[make_pair(now,i)]==1)return;
	vs[make_pair(now,i)]=1;	
	if(i==ccnt+1)return;
	dfs2(i+1,now*zy[i]);
	dfs2(i+1,now);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=2; i<=100000; i++) {//线性筛
		if(!vis[i]) {
			a[cnt++]=i;
			vis[i]=1;
		}
		for(int j=0; j<cnt; j++) {
			if(i*a[j]>100000)break;
			vis[i*a[j]]=1;
			if(i%a[j]==0)break;
		}
	}
	cin>>t;
	while(t--) {
		cin>>n>>x;
		int tmpn=n-x;
		ttn=n;
		ccnt=0;
		ans=0;
		for(int i=0; i<cnt; i++) {//对 n-x 分解质因数
			if(a[i]>tmpn)break;
			while(tmpn%a[i]==0) {
				zy[++ccnt]=a[i];
				tmpn/=a[i];
			}
		}
		if(tmpn>1)zy[++ccnt]=tmpn;
		S.clear();
		vs.clear();
		dfs(1,1);
		if(x>=2) {//x=1 时没有这种情况
			ccnt=0;
			n+=(x-2);
			tttn=n;
			for(int i=0; i<cnt; i++) {//对 n+x-2 分解质因数
				if(a[i]>n)break;
				while(n%a[i]==0) {
					zy[++ccnt]=a[i];
					n/=a[i];
				}
			}
			if(n>1)zy[++ccnt]=n;
			//	S.clear();
			//	S.erase(1);
			vs.clear();
			dfs2(1,1);
		}
		if(ttn%2==0&&x==2)ans++;//特判 x=2 的情况，因为上面搜索时这种情况因为 n%2!=x 被排除
		cout<<ans<<"\n";
	}
}
```

---

## 作者：快斗游鹿 (赞：0)

观察 $x$ 的分布规律：

先在 $x$ 位置出现一次，然后每隔 $2k-2$ 个位置会出现两次，一次是在 $2k-2x$ 个位置后，另一次是在前一次出现的 $2x-2$ 个位置后。我们称前者为第一位置，后者为第二位置。因为第一次出现与循环节无关，故可以先将 $n$ 减去 $x$。

如果 $n$ 在第二位置，那么 $n$ 一定可以被表示成 $(2k-2)a$，其中 $a$ 是**正整数**。可以枚举 $n$ 的因数并解出 $k$，只要 $k$ 是不为 $1$ 的正整数，那么一定合法。

如果 $n$ 在第一位置，那么 $n$ 一定可以被表示成 $(2k-2)a+2k-2x$，其中 $a$ 是**自然数**。转换一下，$n=(2k-2)(a+1)-2(x-1)$，那么 $n+2(x-1)$ 一定可以被 $2k-2$ 整除，同样枚举因数，解出 $k$ 并判断，注意去重。

还需要注意，解出的 $k$ 必然**不小于 $x$**。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,x,ans;
map<int,int>mp;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void _work(int len,int op){
	for(int i=1;i*i<=len;i++){
		if(len%i==0){
			if(i%2==0){
				int k=(i+2)/2;
				if(!mp[i]&&!op){
					if(k>=x)mp[i]=1,ans++;//,cout<<i<<endl;
				}
				if(!mp[i]&&op){
					if(k>=x)mp[i]=1,ans++;
				}
			}
			int xxx=len/i;
			if(xxx%2==0){
				int k=(xxx+2)/2;
				if(!mp[xxx]&&!op){
					if(k>=x)mp[xxx]=1,ans++;//,cout<<xxx<<endl;
				}
				if(!mp[xxx]&&op){
					if(k>=x)mp[xxx]=1,ans++;
				}
			}
		}
	}
}
void solve(int len){
	_work(len,0);
	//printf("%lld\n",ans);
	if(x!=1){
		_work(len+2*(x-1),1);
	}
	printf("%lld\n",ans);
}
signed main(){
	//freopen("std.in","r",stdin);
	T=read();
	while(T--){
		n=read();x=read();ans=0;mp.clear();
		if(n<x){
			puts("No");continue;
		}
		n-=x;
		solve(n);
	}
	return 0;
}
 
```


---

