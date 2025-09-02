# Element Extermination

## 题目描述

You are given an array $ a $ of length $ n $ , which initially is a permutation of numbers from $ 1 $ to $ n $ . In one operation, you can choose an index $ i $ ( $ 1 \leq i < n $ ) such that $ a_i < a_{i +       1} $ , and remove either $ a_i $ or $ a_{i + 1} $ from the array (after the removal, the remaining parts are concatenated).

For example, if you have the array $ [1, 3, 2] $ , you can choose $ i = 1 $ (since $ a_1 = 1 < a_2 = 3 $ ), then either remove $ a_1 $ which gives the new array $ [3, 2] $ , or remove $ a_2 $ which gives the new array $ [1, 2] $ .

Is it possible to make the length of this array equal to $ 1 $ with these operations?

## 说明/提示

For the first two test cases and the fourth test case, we can operate as follow (the bolded elements are the pair chosen for that operation):

 $ [\text{1}, \textbf{2}, \textbf{3}] \rightarrow [\textbf{1},       \textbf{2}] \rightarrow [\text{1}] $

 $ [\text{3}, \textbf{1}, \textbf{2}, \text{4}] \rightarrow       [\text{3}, \textbf{1}, \textbf{4}] \rightarrow [\textbf{3},       \textbf{4}] \rightarrow [\text{4}] $

 $ [\textbf{2}, \textbf{4}, \text{6}, \text{1}, \text{3},       \text{5}] \rightarrow [\textbf{4}, \textbf{6}, \text{1}, \text{3},       \text{5}] \rightarrow [\text{4}, \text{1}, \textbf{3}, \textbf{5}]       \rightarrow [\text{4}, \textbf{1}, \textbf{5}] \rightarrow       [\textbf{4}, \textbf{5}] \rightarrow [\text{4}] $

## 样例 #1

### 输入

```
4
3
1 2 3
4
3 1 2 4
3
2 3 1
6
2 4 6 1 3 5```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：三点水一个各 (赞：23)

### 题意

在一个长 $n$ 数组中，若出现 $a_i<a_{i+1}$ $(1\le i<n)$，则可删除 $a_i$ 和 $a_{i+1}$ 其中一个，问是否能把数组删到只剩一个元素。

### 思路

最后只剩一个数，说明在这之前的操作中有$a_i<a_{i+1}$，

即在若干次操作后，前面剩下一个较小数，后面剩下一个较大数。

所以要使最后只剩下一个数，要使前面的数尽量小，后面的数尽量大。

对于开头的数 $a_1$，

如果 $a_1<a_2$，在满足前面的数尽量小的前提下，删去 $a_2$，保留 $a_1$。

如果 $a_1\ge a_2$，无法进行操作，保留 $a_1$。

不仅对于初始数组的 $a_1a_2$ 是如此，如果后面 $a_2$ 被其他元素替换，**在最后一次操作之前，$a_1$始终能够保留**。

对于最后的数 $a_n$，

如果 $a_{n-1}<a_n$，在满足后面的数尽量大的前提下，删去 $a_{n-1}$，保留 $a_n$。

如果 $a_{n-1}\ge a_n$，无法进行操作，保留 $a_n$。

不仅对于初始数组的 $a_{n-1}a_n$ 是如此，如果后面 $a_{n-1}$ 被其他元素替换，**在最后一次操作之前，$a_n$始终能够保留**。

至此可证明，最后一次操作之前，$a_1$ 和 $a_n$ 都未被删除，

所以对于一个数组，**若 $a_1\ge a_n$ ，不可能最后只剩下一个数**。

现在证明若 $a_1<a_n$，它们之间的所有元素是否都能被删除。

对于第二个元素 $a_2$，

若$a_1<a_2$，则 $a_2$可以被删除，

若$a_1\ge a_2$，$a_2<a_3$，则 $a_2$ 删除，

若$a_1\ge a_2$，$a_2\ge a_3$，先将 $a_2$ 保留,

对于倒数第二个元素 $a_{n-1}$,

若$a_{n-1}<a_n$，则 $a_{n-1}$可以被删除，

若$a_{n-1}\ge a_n$，$a_{n-2}<a_{n-1}$，则 $a_{n-1}$ 删除，

若$a_{n-1}\ge a_n$，$a_{n-2}\ge a_{n-1}$，先将 $a_{n-1}$ 保留,

至此，$a_1,a_2,a_{n-1},a_n$ 都暂时保留，

且因为 $ a_1\ge a_2$，$a_{n-1}\ge a_n$，$a_1<a_n $

所以 $ a_2<a_{n-1}$

所以只要 $ a_2$ 和 $a_{n-1}$ 之间的数能被删除，$a_2$ 和 $a_{n-1}$ 均能被删除，

于是就回到了刚刚证明若 $a_1<a_n$，它们之间的所有元素都能被删除这一命题。

到最后，若$n$为偶数，则最坏情况为 $a_1\ge a_2\ge ...\ge a_{n/2}<a_{n/2+1}<...< a_{n-1}<a_n $

能删到最后只剩一个数。

若$n$为奇数，则最坏情况为 $a_1\ge a_2\ge ...\ge a_{n/2} \text{(>或=或<)} a_{n/2+1}\text{(>或=或<) }a_{n/2+2}<...< a_{n-1}<a_n $

易证 $a_{n/2+1}$ 无论如何都能被删除，

所以能删到最后只剩一个数。

如$[3,2,0,1,2,6,4]\rightarrow [3,2,0,\mathbf{1},\mathbf{2},6,4]\rightarrow [3,2,\mathbf{0},\mathbf{2},6,4]\rightarrow $

$[3,2,\mathbf{0},\mathbf{6},4]\rightarrow [3,\mathbf{2},\mathbf{6},4]\rightarrow [3,\mathbf{6},\mathbf{4}]\rightarrow [\mathbf{3},\mathbf{4}]\rightarrow [3]$


### 结论

当 $a_1<a_n$ 时，输出"YES"，否则输出"NO"。

$\mathtt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,x,a,b,n;
int main()
{
   scanf("%lld",&t);
   for(ll kk=1;kk<=t;++kk)
   {
       scanf("%lld",&n);
       for(int i=1;i<=n;++i)
       {
           scanf("%lld",&x);
           if(i==1) a=x; if(i==n) b=x;
       }
       if(a<b) printf("YES\n");
       else printf("NO\n");
   }
   return 0;
} 
```

---

## 作者：5k_sync_closer (赞：4)

结论：存在策略使得 $a$ 只剩下一个元素 $\Leftrightarrow a_1<a_n$。


------------

充分性证明：观察到操作过程中 $a$ 最左端的数不降，$a$ 最右端的数不增。

>证明：对最左端的数操作时，有 $a_1<a_2$，删除 $a_2$ 后最左端的数不变，删除 $a_1$ 后最左端的数变大。
>
>最右端的数同理。

若存在策略，则删到 $|a|=2$ 时有 $a_1<a_2$，

又因为 $a$ 最左端的数不降，$a$ 最右端的数不增，所以原序列中 $a_1<a_n$。


------------

必要性证明：若 $a_1<a_n$，存在如下策略：

1. 找到 $k=\min\limits_{a_x>a_1}x$。
2. 有 $a_{k-1}<a_k$，删除 $a_{k-1}$ 直到 $k=1$。
3. 重复过程 1，2 直到 $a$ 只剩下一个元素。


------------

```cpp
#include <cstdio>
int T, n, a[300050];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        puts(a[1] < a[n] ? "YES" : "NO");
    }
    return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：3)

这道题我在考场上最开始的想法是：

以第一个数为基准，然后在第一个比它小的数之前都和第一个数一类，剩下的一类，如果剩下的那类有比第一个数大的，那么就输出 `YES`，否则是 `NO`。

原理呢？因为左边一类的可以变成第一个元素，而右边的就是最大的那个元素，然后判断一下就行了。

但是 $3~1~2~4$ 这种数据就会卡掉我的做法，所以我们需要把这种算法改一改。

因为两个峰之间夹的谷肯定会被合并掉，所以我们最开始就去掉这些元素，然后就 A 了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005],p[300005],q[300005],b[300005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			b[i]=a[i];
			p[a[i]]=i;
		}
		b[n+1]=0;
		for(int i=n;i>=1;i--)b[i]=max(b[i],b[i+1]);
		int zz=1;
		int nn=1;
		q[nn]=1;
		while(zz!=n)
		{
			zz=p[b[zz+1]];
			q[++nn]=zz;
		}
		n=nn;
		for(int i=1;i<=n;i++)b[i]=a[q[i]];
		for(int i=1;i<=n;i++)a[i]=b[i];
		int tt=n+1;
		for(int i=1;i<=n;i++)if(a[i]<a[1])
		{
			tt=i;
			break;
		}
		if(tt>n)
		{
			cout<<"YES"<<endl;
		}else
		{
			int flag=0;
			for(int i=tt;i<=n;i++)if(a[i]>a[1])flag=1;
			if(flag)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Andrewzdm (赞：3)

当我们想不出如何才能判断答案为 $\texttt{YES}$ 的时候，不妨从对立面想，看看什么时候答案为 $\texttt{NO}$。

结合题目中的规则，以及样例可以观察到，在数组变化的过程中，最左端的数的大小一定不会减小，最右端的数的大小一定不会增加。

证明：移除一个数的条件为 $a_i < a_{i+1}$，如果最左端的数我们不移除，那么很显然，最左端的数大小不变；如果我们移除了最左端的数，那么新的最左端的数就成了 $a_{i+1}$，比原来的 $a_i$ 要大。最右端的数的变化情况同理。

所以如果 $a_1 > a_n$，不管怎么消除数，最后一定不能只剩下 $1$ 个数。因为就算我们能消到只剩下最后两个数，根据上面证明的结论，这两个数是一定无法移除其中一个的。

接着进行猜想：如果 $a_1 < a_n$，那么答案为 $\texttt{YES}$。

接下来我们就要尝试想出一个策略，保证当 $a_1 < a_n$ 时，我们一定能按照规则操作使得最后只剩下一个数。

这个策略是这样的：每次找到一个离 $a_1$ 最近的一个数 $a_x$，满足 $a_x > a_1$，然后我们用这个 $a_x$ 一路向 $a_1$ “推”，“挤”掉所有下标在 $(1,x)$ 中的数 $a_i$，然后这个 $a_x$ 就来到了 $a_1$ 旁边，我们再把 $a_x$ 移走。反复重复这个策略，最后成为 $a_x$ 的一定是 $a_n$，最后数组只剩下了 $a_1$。

综上所述：
* 当 $a_1 > a_n$ 时，不可能做到使数组只剩下一个数；
* 否则，则必定可以使数组只剩下一个数。

代码：
```cpp
#include<cstdio>
const int maxn = 3e5 + 10;
int a[maxn];

void solve()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", a + i);
	puts(a[n] > a[1] ? "YES" : "NO");
	return;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：yaotianhao (赞：2)

### 题意

给一个长度为 $n$ 的排列，如果有一组 $i$ 满足 $a_i < a_{i+1}$ 就可以把 $a_i$ 或 $a_{i+1}$ 消掉，问最后能不能使这个排列只剩下一个元素。

### 结论

先说结论，只要 $a_1 > a_n$ 就是无解，否则就有解。

### 证明

因为要留下来最后的一个数，所以最后的盘面就只能是 $a_1 < a_2$。

假设 $a_1 > a_n$，我们从两端的第二个数来看，如果 $a_2 > a_1$ 那么留下来的要么是更大的 $a_2$ 或者 $a_1$ 去和后面比，这样无论如何也是不会有 $a_1 > a_2$ 的盘面，如果 $a_1 > a_2$ 那么 $a_2$ 就会和后面去比，而 $a_1$ 就会留下来，这样也不会有有解的盘面。

然后看 $a_n$ 和 $a_{n-1}$ 如果 $a_n > a_{n-1}$，就会是更小的 $a_{n-1}$ 或者 $a_n$ 去和前面的去比，这样不会有有解的盘面，如果 $a_{n-1} < a_n$ 这样还是会留下 $a_n$ 去和前面比，依旧不会有有解盘面。

对于其他的数，和上面同理，所以要是有解的盘面，必须满足 $a_1 < a_n$。

### 代码

代码如下：

````cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int t, n, a[N]; 
signed main() {
	scanf("%d", &t);
	while(t --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		if(a[1] > a[n]) printf("NO\n");
		else printf("YES\n");
	}
}
````

---

## 作者：zmza (赞：2)

这题，我们可以这样想：

我们假设留下的是最后一个数，那么只要前面有比它大的数，并且消不掉的，那么就不可以。如果可以消掉，就是前面有比它小的数，那么就将它消掉。

这个算法是$O(n^2)$的，加个小优化就可以过。

优化：将所有上升的序列都列出来，第一个序列留下最小的数，其他的数列留下最大的数，再跑暴力就可以通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int sum = 0,ne = 1;char tmp;
	for(tmp = getchar(); (tmp < '0' || tmp > '9') && tmp != '-'; tmp = getchar());
	if(tmp == '-')ne = -1,tmp = getchar();
	for(; tmp >= '0' && tmp <= '9'; tmp = getchar())sum = (sum << 3) + (sum << 1) + tmp - '0';
	return sum * ne;
}
const int maxn = 3e5;
int a[maxn];
int b[maxn],cnt;
int main()
{
	int t = read();
	a[0] = 1e9;
	while(t--)
	{
		cnt = read();
		int n = 0;
		for(int i = 1; i <= cnt; i++)//优化
		{
			b[i] = read();
			if(b[i] < b[i - 1])
			{
				if(n == 0)a[++n] = b[1];//第一个上升序列留第一个数，其余的留最大的数。
				else a[++n] = b[i - 1];
			}
		}
		a[++n] = b[cnt];//最后一串数留最后一个数。
		bool flag = 0;
		for(int i = n - 1; i >= 1; i--)//暴力，从后往前扫。
		{
			bool vis = 0;//能不能消掉这个数。
			if(a[i] < a[n])continue;
			for(int j = 1; j < i; j++)//看看前面有没有可以将它消掉的
			{
				if(a[j] < a[i])
				{
					vis = 1;
					break;
				}
			}
			if(vis == 0)
			{
				flag = 1;
				break;
			}
		}
		puts(flag == 1 ? "NO" : "YES");
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

结论题，比较让人恼火。

我们可以得出我们应该尽可能保留 $a_1$，为什么呢？因为我们希望前面的数字尽可能小，你要是删掉它，肯定得用一个大一点的数字，那你换成一个更大的数字，怎么说都是不优的。

同理 $a_n$ 也要尽可能保留。

我们考虑 $a_1<a_2$ 时删掉 $a_2$，持续这么做，直到 $a_2>a_1$,同理尝试删除 $a_3$，一直删一直删，但是保留 $a_n$ 不动。

最后会删成一个单调下降的数列，后面跟着 $a_n$，显然，想要删成一个数字的条件是 $a_1<a_n$，这个结论直接用就可以了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL T,n,a[N];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		if(a[1]<a[n])puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1375C Element Extermination](https://www.luogu.com.cn/problem/CF1375C)

# 题意简述

有一个 $n$ 个数的排列，问是否能在若 $a_i < a_{i+1}$ 可以删除 $a_i$ 或 $a_{i+1}$ 的情况下将这个排列删至一个元素。

# 解题思路

首先，我举一个例子 $\{3,5,1,2,4\}$，这时我们只需要按照顺序分别删除下标为 $2,4,3,5$ 即可，这时剩余元素数量为 $1$。

然后，我们考虑一下 $a_1$：如果 $a_1$ 比 $a_2$ 大，那么容易得知，我们要使情况最优是一定要删除 $a_2$ 的，然后继续从前往后递推，

否则我们就从后往前判断：如果 $a_n$ 大于 $a_{n-1}$，那么我们同样也容易得知，我们要使情况最优要删除 $a_{n-1}$，然后继续从后往前递推，否则我们就保留 $a_n$，然后继续从后往前递推。

接下来我们发现，

如果 $a_1>a_2$，那么最后操作的数仍然是 $a_1$，然后我们删除的数是 $a_1$，也就是说可以一直从前往后比较，则每次都是 $a_1$ 和 $a_i(2 \le i \le n)$ 比较，否则则直接从后往前比较，这时，**第一个数仍然为 $a_1$**。

如果 $a_n>a_{n-1}$，那么我们删除的数为 $a_{n-1}$，也就是说可以一直从后往前比较，则每次都是 $a_i(2 \le i \le n)$ 和 $a_n$ 比较，否则我们继续往前面递推，这时，**最后一个数仍然为 $a_n$**。

最后，我们就会发现，**第一个数一定为 $a_1$，并且最后一个数一定为 $a_n$**。

所以这时，我们就可以推出一个结论：

**若 $a_1 <a_n$，则一定有解，否则一定无解。**

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[1000010];
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		if(a[1]<a[n])//上文推出的结论
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	QwQ;
}
```

---

## 作者：TernaryTree (赞：1)

先放结论：`YES` 与 `NO` 取决于开头元素 $a_1$ 与末尾元素 $a_n$ 的大小关系。

证明：

如果最终消不掉，那么一定是留下了一个单调递减的序列。

而单调递减的序列的开头大于末尾。

如果 $a_1$ 消掉了，那么一定在 $a_1$ 后面有一个 $a_i$ 比 $a_1$ 更大。

如果 $a_n$ 消掉了，那么一定在 $a_n$ 前面有一个 $a_j$ 比 $a_n$ 更小。

也就是说，如果 $a_1>a_n$，那么无论如何操作，留下的数列开头总比末尾大，也就是说消不掉。

否则肯定可以消掉。

代码：

`scanf("%d",&t);while(t--){scanf("%d%d",&n,&a);while(--n)scanf("%d",&b);puts(a<b?"YES":"NO");}`

---

## 作者：Michael1234 (赞：0)

- 本题是**思维**题

- 结论：只要 $a_1<a_n$，即可完成操作。

- 这几种情况称之为可以操作的情况：

1. 如果 $a_{i-1}<a_i<a_{i+1}$：可以删除 $a_i$。

2. 如果 $a_{i-1}<a_i>a_{i+1}$：可以删除 $a_i$。

3. 如果 $a_{i-1}>a_i<a_{i+1}$：可以删除 $a_i$。

- 不可以操作的情况：

1. $a_{i-1}>a_i>a_{i+1}$。

- 不断寻找并操作可以操作的情况，直到找不到可以操作的情况或只剩两个数，此时有三种可能：

1. 剩下一个递减序列，即 $a_1>a_2 ...>a_x$（$x\leq n$）。

2. 剩下一个 $a_1>a_2$。

3. 剩下一个 $a_1<a_2$。

- 此时第 $1,2$ 种情况无解，他们都属于 $a_1>a_n$（因为无论怎么删除， $a_x\leq a_n$）。

- 由于每次删除的是两数之间的一个数，所以剩下的两个数是原来的 $a_1$ 和 $a_n$。

- 所以只要 $a_1<a_n$，此序列有解。

**~~代码就简单了~~**

## CODE

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+5;
int t,n,a[N];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		if(a[1]<a[n])
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0;
}

---

## 作者：raincity (赞：0)

## 分析
这是一道结论题。

暴力一下可以猜测结论是可以删成一个数的充要条件是 $a_1<a_n$。

当然这样就可以 $\color{white}\colorbox{green}{AC}$ 了，但是我们还是要证明一下。

**update: 更新了第二种情况的构造方式，原来的证明有问题。**

**update2：更正了一个笔误的地方**

1. 当 $a_1>a_n$ 的时候，因为只有 $a_i<a_{i+1}$ 的时候才可以删数，所以只有 $a_{n-1}<a_n$ 的时候可以去掉最后一个数。这样结尾的数在最终的时候一定不会变大，所以当删成只有两个数的时候一定有 $a_1>a_2$，无法删完。

2. 当 $a_1<a_n$ 的时候，对于 $a_i<a_{i+1}<\ldots <a_j>a_{j+1}(1\le i<j<n)$，可以把 $a_{i+1},a_{i+2},\ldots a_j$ 删掉，留下 $a_i,a_{j+1}$。如果最终留下 $m$ 个数，那么一定有 $a_1>a_2>\ldots>a_{m-1}$，不然可以继续删，而 $a_m>a_1$，所以从后往前依次删掉 $a_{m-1},a_{m-2},\ldots a_1$，保留最后一个数 $a_m$，最终剩下原来的 $a_n$。

代码懒得贴了，很好写。

---

## 作者：youngk (赞：0)

这道题目给出一个$1-n$的全排列，如果相邻两个数满足$a_{i}<a_{i+1}$，则可以删除其中任意一个，问最终能否删至只剩下一项。

不妨考虑如果第一项大于最后一项的话，那么消到最后如果能剩下两项，一定前一项大于等于第一项，后一项小于等于最后一项，这样的情况不能删至只剩一项。

如果前一项小于最后一项的话，则可以找到一个最高的位置，将在前面的除了第一项全部消去，然后最高项被第一项消去，再选出当前的最高项重复这个操作直至最后一项被选做为用于消去的最高项，则将前面的所有项消去，成功构造（第一项小于最后一项因此不可能被选成为是作为消去的最高项）。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define endl '\n'
#define lowbit(x) x & -x
#define inf 0x3f3f3f3f
#define maxn 310

int x, y, n, t;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> x;
        for (int i = 2; i <= n; i++) {
            cin >> y;
        }
        cout << (x < y ? "YES" : "NO") << endl;
    }
    return 0;
}
```


---

