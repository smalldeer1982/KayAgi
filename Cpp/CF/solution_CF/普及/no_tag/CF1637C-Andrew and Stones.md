# Andrew and Stones

## 题目描述

Andrew has $ n $ piles with stones. The $ i $ -th pile contains $ a_i $ stones. He wants to make his table clean so he decided to put every stone either to the $ 1 $ -st or the $ n $ -th pile.

Andrew can perform the following operation any number of times: choose $ 3 $ indices $ 1 \le i < j < k \le n $ , such that the $ j $ -th pile contains at least $ 2 $ stones, then he takes $ 2 $ stones from the pile $ j $ and puts one stone into pile $ i $ and one stone into pile $ k $ .

Tell Andrew what is the minimum number of operations needed to move all the stones to piles $ 1 $ and $ n $ , or determine if it's impossible.

## 说明/提示

In the first test case, it is optimal to do the following:

1. Select $ (i, j, k) = (1, 2, 5) $ . The array becomes equal to $ [2, 0, 2, 3, 7] $ .
2. Select $ (i, j, k) = (1, 3, 4) $ . The array becomes equal to $ [3, 0, 0, 4, 7] $ .
3. Twice select $ (i, j, k) = (1, 4, 5) $ . The array becomes equal to $ [5, 0, 0, 0, 9] $ . This array satisfy the statement, because every stone is moved to piles $ 1 $ and $ 5 $ .

 There are $ 4 $ operations in total.In the second test case, it's impossible to put all stones into piles with numbers $ 1 $ and $ 3 $ :

1. At the beginning there's only one possible operation with $ (i, j, k) = (1, 2, 3) $ . The array becomes equal to $ [2, 1, 2] $ .
2. Now there is no possible operation and the array doesn't satisfy the statement, so the answer is $ -1 $ .

In the third test case, it's optimal to do the following:

1. Select $ (i, j, k) = (1, 2, 3) $ . The array becomes equal to $ [2, 0, 2] $ . This array satisfies the statement, because every stone is moved to piles $ 1 $ and $ 3 $ .

 The is $ 1 $ operation in total.In the fourth test case, it's impossible to do any operation, and the array doesn't satisfy the statement, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
4
5
1 2 2 3 6
3
1 3 1
3
1 2 1
4
3 1 1 2```

### 输出

```
4
-1
1
-1```

# 题解

## 作者：baiABC (赞：6)

首先可以发现，当 $n=3$ 时， $2 \nmid a_2$ 时无解，否则有解且答案为 $\dfrac{a_2}{2}$。下面不妨设 $n>3$。

当 $a_2=a_3=\dots=a_{n-1}=1$ 时无解（操作一次都不能进行）。

其他情况是必有解的，可以找到一个中间的非零偶数（如果没有就找中间最大的奇数）减二，把 $a_1$ 或 $a_n$ 加一，给其他数中的一个奇数加一。这样的操作进行下去必能把中间的数都变成偶数，显然有解。

如果有一堆是偶数，一定不需要把它加一而浪费操作次数，而奇数堆需要加一才能每次减二减到 $0$。

设中间所有数的和为 $S$，中间奇数的个数为 $C$。不难发现，每次操作后 $C+S$ 都会减二（`S -= 2`，`C -= 2` 或 `--S, --C`），而最终目标中 $S=C=0$，所以最少操作次数为 $\dfrac{C+S}{2}$。
### 代码：
**注意开 `long long` ！**
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, a[100001];
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		bool ok = false;
		int c = 0;
		long long s = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a+i);
			if(i == 1 || i == n) continue;
			if(a[i] > 1) ok = true;
			if(a[i] & 1) ++c; // 是奇数
			s += a[i];
		}
		if(!ok) {puts("-1"); continue;}
		if(n == 3)
		{
			if(a[2] & 1) puts("-1");
			else printf("%d\n", a[2]/2);
			continue;
		}
		printf("%lld\n", (s+c)/2);
	}
	return 0;
}
```

---

## 作者：让风忽悠你 (赞：3)

[原题](https://www.luogu.com.cn/problem/CF1637C)

## 做法

首先考虑无解的情况，因为 $i,j,k$ 满足 $i \le j \le k$，当 $n=3$ 时，$j$ 只能为 2，那么此时如果 $a_2$ 为奇数则无解；题目中还提到 $a_j \ge 2$，所以当 $\forall i \in[2,n-1],a_i=1$ 时无解。

排除掉无解情况后，记录 $sum=\sum\limits_{i=2}^{n-1}\lfloor\frac{a_i}{2}\rfloor$，奇数个数为 $cnt$，最终结果为 $ans$，不难发现，当 $cnt=0$,即全部都是偶数时，$ans=sum$；如果 $cnt>0$，即存在奇数，因为将奇数增加加为偶数的同时可以对另外一个数做 $-2$，$ans=sum+cnt$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 100005
#define ll long long

using namespace std;

int T,n;
ll ans,a[N]; // 记得要开ll 

int main(){
	scanf("%d",&T);
	while(T--){
		bool pd=0;
		ans=0ll;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(i>1 && i<n){
				if(a[i]>1) pd=1;
				ans+=((a[i]+1)/2);
			} // 因为遇到奇数要加一，实际上就是向上取整 
		}
		if((n==3 && a[2]&1ll) || !pd){
			printf("-1\n");
			continue;
		} // 判断无解情况 
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Novice233 (赞：2)

题意很简单，每一次可以选取第 $i$ 堆石子 ($ 1 \lt i \lt n$ )，拿出两个，放在任意两堆中。若最后可以将所有石子放在第 1 堆和第 $n$ 堆中，输出最少所需步数。否则，输出-1。

这道题唯一的难点就是如何判无解。比赛的时候，我就是因为判错了无解了情况，被罚了 350 分。

如果除了头和尾，中间只有一个数且为奇数，则显然无解。

如果中间只有一个数且为偶数，则显然有解。

如果中间的数全为 1，则显然无解。

如果中间超过了一个数且不全为 1。若想让奇数变成偶数，就将一个石子放在这堆上，还有一个石子放在两头。也就不难看出，只要中间有大于等于两堆，就必然有解。

代码
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
long long a[N],n,t;
int main(){
	cin>>t;
	while(t--){
		long long cnt1=0,cnt2=0,cnt3=0;
		long long ans=0;
		long long cnt=0;
		cin>>n;
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++) cin>>a[i],cnt+=a[i];
		for(int i=2;i<=n-1;i++){
			//if(a[i]!=1) cnt3++;
			if(a[i]%2==0) cnt1++,cnt3++;
			if(a[i]%2==1&&a[i]!=1) cnt2++,cnt3++;
			if(a[i]==1) cnt2++;
		} 
		if(cnt3==0) cout<<-1;
		else if(cnt2<=1&&cnt1==0) cout<<-1;
		else cout<<(cnt-a[n]-a[1])/2+(cnt2+1)/2;//求解
		cout<<endl;
	} 
	return 0;
} 
```


---

## 作者：windflower (赞：1)

~~两端的数读进来一点用都没有~~  
操作很简单，每次给一个数减二，另两个数加一，把它分到左右两堆。  
注意到：
- 减 2 不改变积偶性，加 1 必改变奇偶性。
- 偶数一定能完全分到左右两堆。

那么问题就变成了
- 能否通过操作使除了两端的堆以外均变为偶数。

再将之前的信息整合：
- 一次操作最多能将 2 个奇数变为非 0 偶数
- 非 0 偶数一定能操作

简单地说就是，除非中间只有一个数且为奇数（它无法改变自己奇偶性），不然操作一旦开始就能一直进行到结束。  
那么计算答案就简单了：
**假如有 cnt 个奇数，那么就有 cnt 次加 1 需要用于改变奇偶性，其它的加 1 均可直接加到两端。**   


附 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,cnt,sum;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cnt=sum=0;
		scanf("%*d");
		for(int i=2;i<n;i++){
			cin>>a;
			cnt+=a%2;
			sum+=a;
		}
		scanf("%*d");
		if((n==3&&cnt==1)||sum==n-2)cout<<-1<<endl;
		else cout<<(sum+cnt)/2<<endl;
	}
	return 0;
}
```


---

## 作者：Morpheuse (赞：1)

# 题意
有 $n$ 堆石子 $a_1,a_2,...,a_n$.

每堆石子有一定数量.

对于 $[2,n-1]$ 内的所有石子最后都要移到位置 $1$ 或位置 $n$.

每步能且只能把 $a_j$ 中的 $2$ 颗石子颗分别放到 $a_i$ 和 $a_k$.

并要求满足 $1\leq i   <j<k\leq n$.

问是否能移完和最小移动步数.

# Solution

很明显对于 $\forall a_i\ge2$ 的情况我们应该降 $a_i$ 减 $2$ 直到 $a_i$ 变成 $0$ 或 $1$ 之后再考虑，我们称这种操作为降值.

当然了，降值也要算步数.

降值之后，我们的 $a$ 一定是一个只包含 $0$ 和 $1$ 的数组.

$0$ 我们就不用管了，因为已经移完了.

那我们发现对于序列 

$0\ 1\ 1\ 2\ 1\ 0$

我们要把中间的数字移走，可行的方法有很多，但是都包含一种操作，就是把 $2$ 拆出来的两个 $1$ 至少分一个到序列中的 $1$ 上面，让序列中的 $1$ 变成 $2$ 后再继续分.

也就是说，只要我们原本序列中有一个数 $a_x\ge2$ 就能让所有的 $1$ 变成 $0$.

好了思路讲完了.

显然走完上述流程后就是最小的移动步数了.

考场代码比较冗杂

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define maxn 100010
 
int n,t;
int a[maxn];
 
int main()
{
	scanf("%d", &t);
	while(t --)
	{
		scanf("%d", &n);
		long long ans , cnt1 , cnt2 , flag;//ans1记录奇数个数 ans2记录偶数个数 flag 记录是否全为 1 
		ans = cnt1 = cnt2 = flag = 0;
		for(int i = 1 ; i <= n ; ++ i)
		{
			scanf("%d", &a[i]);
			if(i == 1 || i == n) continue;
			if(a[i] != 1) flag = 1;
			if(a[i] == 1) cnt1 ++;
			if(a[i] >= 2)
			{
				if(a[i] & 1)
				{
					ans += (a[i] / 2);
					a[i] = 1;
					cnt1 ++;
				}
				else
				{
					ans += (a[i] / 2);
					a[i] = 0;
					cnt2 ++;
				}
			}
		}
		if(flag == 0)
		{
			printf("-1\n");
			continue;
		}
		if(cnt2 > 0 || (cnt1 > 1))
		{//如果存在最少一个偶数 
			ans += cnt1;
			printf("%lld\n", ans);
		}
		else if(cnt1 == 0)
			printf("%lld\n", ans);
		else
			printf("-1\n");
		}
	}
}
```


---

## 作者：Fa1thful (赞：1)

### 一、题意
给你 $n$ 堆石头，$a$ 数组每堆石头的数量，可以选择三个位置，将中间位置中的石头堆中拿出两块分别放置一个在左右两个位置上，问最后将所有石子都放置在 $1$ 和 $n$ 这两个位置上需要进行多少步操作。

### 二、分析
首先很容易想到如果这堆石子的个数是偶数，那么仅用 $\frac{x}{2}$ 次就可以把这堆石头移到 $1$ 和 $n$ 或者其他位置上。那么顺着这个思路就可以把奇数考虑成一个偶数-1,所以想要让奇数变成偶数只需要在偶数迁移的时候分一个到奇数上就可以了。那么如果在中间的部分全是 $1$，那么就不能进行任何操作，所以这种情况显然是达不成目标的。那么当 $n=3$ 的时候，中间只要是奇数就不行。因为是奇数的话最后把所有石子都分完终究会剩下一个 $1$ 没有办法分走。所以我们的贪心思路是这样的：

首先先判断是否可以达成目标，然后枚举中间的每一个数。如果中间的数是奇数，那么它需要 $\frac{x+1}{2}$ 步才能移走。因为要想尽快地移走肯定先主要向 $1$ 和 $n$ 这两个位置移，只有在这堆是奇数没有办法移走的情况下才会分一个到这个奇数堆上。如果这个数是偶数，那么它需要 $\frac{x}{2}$ 次才能移走。直接加上每个数的步数就可以了，因为在这个贪心策略中这些数移走的方法都是互相独立的。

还有一种特殊情况就是中间不全都是 $1$ 的但是中间都是奇数的情况。这种情况只要知道一个不为 $1$ 的奇数也可以移到别的奇数上让别的奇数变成偶数就可以按照上一种情况做了。

### 三、代码
```cpp
# include <bits/stdc++.h>
using namespace std;
long long a[100005];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		bool flag = false;
		for (int i = 2; i <= n - 1; i++)
		{
			if (a[i] > 1) flag = true;
		}
		if (flag == false && n != 3)    //不是3但是全是1 
		{
			cout << -1 << endl;
			continue;
		}
		if (n == 3 && a[2] % 2 == 1)   //是3只要是奇数就不行 
		{
			cout << -1 << endl;
			continue;
		}
		long long ans = 0;    //比赛的时候没开long long见祖宗了。。。 
		for (int i = 2; i <= n - 1; i++)
		{
			long long sum = a[i] / 2;   //偶数 
			if (a[i] % 2 == 1) sum++;   //如果是奇数，那么还需要+1/2. 
			ans += sum;   //统计答案 
		}
		cout << ans << endl;
	}
	return 0;
}
```
谢谢观赏

---

## 作者：include_BM (赞：1)

对于 $i\in[2,n-1]$，若 $a_i$ 为偶数，那么直接进行 $\frac{a_i}{2}$ 次操作即可；若 $a_i$ 为奇数，则需要从其他数借一个 $1$（这并不影响其他数的操作次数），变成偶数后再进行 $\frac{a_i+1}{2}$ 次操作。 

考虑哪些序列无解：

1. $n=3$ 且 $a_2$ 为奇数，显然无解。
2. $\forall i\in[2,n-1],a[i]=1$，那么没有可以操作的数，显然无解。

其他情况均有解，举几个例子：

$[1,1,2,1]\rightarrow[1,2,0,2]\rightarrow[2,0,0,3]$

$[1,2,3,1]\rightarrow[2,0,4,1]\rightarrow[3,0,2,2]\rightarrow[4,0,0,3]$

$[1,3,3,1]\rightarrow[2,1,4,1]\rightarrow[2,2,2,2]\rightarrow[3,0,2,3]\rightarrow[4,0,0,4]$

由于对于偶数 $x$ 有 $\frac{x}{2}=\left\lfloor\frac{x+1}{2}\right\rfloor$，对于奇数 $x$ 有 $\frac{x+1}{2}=\left\lfloor\frac{x+1}{2}\right\rfloor$，故最终答案为 $\sum_{i=1}^n\left\lfloor\frac{a_i+1}{2}\right\rfloor$。

代码：

```cpp
const int N=1e5+10;
ll n,a[N],ans,f;
signed main(){
    for(int T=read();T;--T){
        n=read(),ans=f=0;
        for(int i=1;i<=n;++i) a[i]=read();
        for(int i=2;i<n;++i) f+=(a[i]!=1);
        if((n==3&&(a[2]&1))||(n>3&&!f)){puts("-1");continue;}
        for(int i=2;i<n;++i) ans+=(a[i]+1)/2;
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

## 作者：FiraCode (赞：0)

[【题目链接】](https://www.luogu.com.cn/problem/CF1637C)
## 题意：
给你 $n$ 堆石子，每次选三个数 $(i,j,k)$ 要求 $a_j \le 2$。

然后我们对 $(a_i , a_j , a_k)$ 进行一些操作：

$\left\{\begin{matrix}
  & a_j - 2\\
  & a_i + 1\\
  & a_k + 1
\end{matrix}\right.$

最后求让所有石子都在两边的最少操作次数，若无解，输出 $-1$。
## 题解思路：
我们先看看什么时候无解：
>第一种无解的情况就是一共有 $3$ 堆，中间一堆还是奇数，那么我们只能选 $(1,2,3)$，那么只能从中间往左右分，中间怎么分总会剩一个，那么无解。

>还有一种类似的情况：
>$(a，0，0，0，0，....，b，0，0，0，...，c)$，其中 $b$ 是奇数。
>那么我们就可以把零都去掉，就变成了上一种情况，那么依旧无解。

>还有一种就是所有的数都 $<2$，那么必定无解，输出 $-1$。

我们发现如果一个序列他有一个奇数，那么我们就要把一个数加到这个数上，比如：
$(2,a,3,b,100)$ 此时，$3$ 是奇数，如果不给 $3$ 一个，那么 $3$ 怎么分也分不完。

就是若这个奇数前面多出来了 $2$，那么：

$(first , 2 , odd)$，我们让 $2$ 分出一个给第一个 $(first)$，另一个给这个奇数 $(odd)$，即 $odd + 1$，那么奇数的下一个就是偶数，那么这个奇数就变成了偶数。

若这个奇数的后面多出来了个 $2$，那么：

$(odd , 2 , last)$，我们让 $2$ 分出一个给最后一个 $(end)$，另一个给这个奇数 $(odd)$，那么这个奇数同样也可以变成偶数。

所以只要某个地方(当然不能是这个奇数的位置)多出来了一个 $2$，那么奇数的个数就 $-1$。

所以当一个奇数被填补之后，他就变成了一个偶数，他也能填补别的石子。

因为他被填补之后，他至少是 $2$ (因为他 $+1$ 了，所以不可能是 $0$ )，那么他就能继续填补别的奇数。

怎样证明他移动的次数是最少的呢？

对一个序列比如：

$(0 , 5 , 6 , 5 , 7)$，按照我们刚才的填法，那么对于每个奇数 $(第一个数以及最后一个数除外)$，最多会被填补一次。

因为他被填补成偶数时只会填补别的石子，而不再被填补，因为他本身就是偶数了。

那么操作成功的必要条件就是对于每个数 $a_i$，至少有一个 $\le 2$ 的。

当然若这个序列的长度为 $3$ 并且中间那个数是奇数的话，那么他 $\le 2$ 也没有用了。

[【AC 记录】](https://www.luogu.com.cn/record/73720257)
## AC Code:
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000010;
int n;
long long a[N];
int main() {
	int T;
	cin >> T;
	while (T --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		int cnt1 = 0 , cnt0 = 0 , cnte = 0;//cnt1是1的个数，用来判断是否无解
		//cnt0是奇数的个数，cnte是偶数的个数，当然偶数不能为0，因为如果为零那么就不能填补
		for (int i = 2; i <= n - 1; ++ i) {//第一个数和最后一个数不用动，所以从2开始，到n-1
			//分别统计1，奇数，偶数不包含零的个数
			if (a[i] == 1)cnt1 ++;
			else if (a[i] % 2 == 0 && a[i] != 0) cnte ++;
			else if (a[i] % 2 == 1) cnt0 ++;
		}
		bool flag = (cnte) || ((cnt0) && (cnt0 + cnt1 >= 2));//判断是否有解
		if (!flag) {
			puts("-1");//若无解，输出-1
			continue;
		}
		long long ans = 0;
		for (int i = 2; i <= n - 1; ++ i) ans += (a[i] + 1) / 2;//统计步数
		cout << ans << endl;
	}	
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1200}$
---
### 解题思路：

不是很难，但还是挺有意思的一道题。

首先判断无解，当一个序列中全都是 $1$ 或者当 $n=3$ 的时候 $a_2$ 是一个偶数就一定不可行。

否则一定可行，每一次操作如果 $i$ 或者 $k$ 不在端点处，就一定可以有一个点的奇偶性变化，而且总和减去在两个端点的数量。

所以就可以发现每一次操作之后奇数个数和总和一定减少了 $2$，直接求出这个值就行了。 可以证明，这个总和一定是偶数。


---
如果需要构造方案，每一次将 $j$ 选为一个不为 $1$ 的数，并将 $i$ 和 $k$ 放在奇数位置或者端点就行了。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
long long n,T,x,cnt1,ans,sum;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%I64d",&n);
		cnt1=0;sum=0;
		int flag=1;
		for(int i=1;i<=n;i++){
			scanf("%I64d",&x);
			if(i==1||i==n)continue;
			if(x!=1)flag=0;
			if(x&1)cnt1++;
			sum+=x;
		}
		if(n==3){
			if(sum&1)printf("-1\n");
			else printf("%I64d\n",sum/2);
			continue;
		}
		if(flag){
			printf("-1\n");
			continue;
		}
		printf("%I64d\n",(sum+cnt1)/2);
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

先说判断无解的结论：

- 无解当且仅当 $n=3\land (a_2\bmod2=1)$，或者 $n>3\land a_2,a_3,\cdots,a_{n-1}=1$。

对于 $n=3$ 的情况，是容易说明的。

而对于 $n > 3$ 的情况，我们能发现，只要所有的元素不全为 $1$，我们就可以将一个奇数或者偶数匀到至多两个奇数上去使他们变成偶数，然后就能将中间所有的数消空了。

对于答案的计算，考虑偶数的情况，我们只会对其操作 $a_i/2$ 次，而对于奇数，由于要先匀一个数上去让其变为偶数，所以操作次数是 $\lceil a_i/2\rceil$ 次。

```cpp
const int maxn = 1e5 + 5;
int n;
using ll = long long;
ll a[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        bool flg = 1;
        FOR(i, 2, n - 1) flg &= (a[i] == 1);
        if (flg || (n == 3 && (a[2] & 1))) print(-1);
        else {
            ll ans = 0;
            FOR(i, 2, n - 1) if (a[i] & 1) ans += ((a[i] + 1) >> 1); else ans += (a[i] >> 1);
            print(ans);
        }
    }
    return output(), 0;
}
```

---

## 作者：sprads (赞：0)

### 前置内容

定义一次操作的形式为 $(i,j,k)$，$i<j<k$。

显然，无论进行多少次操作，数列值的总和不变。

也就是说，数值可以不断在 $[2,n-1]$ 转移，数值和不减少。

### 分析

对于 $x\in [2,n-1]$，要把 $a_x$ 减为 $0$，我们分奇偶讨论。

若 $a_x$ 是个偶数，一直将它作为 $j$，需要不断减 $2$，减到零为止。要进行 $\dfrac{a_x}{2}$ 次操作（不可能再少了）。

再考虑较麻烦的情况，若 $a_x$ 是个奇数，需要在操作中给它补上 $1$，才能够刚好不断减 $2$ 变为 $0$。而这个 $1$ 就从减 $2$ 操作中补过来（只补一次即最优）。只需让先前的一次操作中 $i=x$ 或 $k=x$ 即可。这时候至少需要 $\dfrac{a_x+1}{2}$ 次操作。

所以，稍加变换，最少操作次数就是 $\sum_{x=2}^{n-1}\lceil \dfrac{a_x}{2}\rceil$。

### 合法性及正确性

显然，如果所有奇数都能够被调整为偶数（在任意时刻被调整为偶数都可以），则有解，否则无解。

当 $a_x > 1$ 时，就可以进行至少一次减 $2$ 操作。

这时，如果 $[2,n-1]$ 中仍有奇数（不能是 $a_x$），则一定可以对它加 $1$，把它调整为偶数。否则将 $1$ 加给 $a_1$ 或 $a_n$。

同样地，此时加了 $1$ 的数一定可以重复 $a_x$ 的操作过程，达到将所有奇数调整为偶数的目的。

即只要有 $a_x > 1$，就有解且能够满足操作次数最少。

**注意**：

- 特判 $n=3$ 时，只要 $a_2$ 是一个奇数，就无解。

- 开 `long long`。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100005;
int T,n,a[N];
inline int rd(){
	int x = 0;char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
inline bool check(){//判断是否有解
	for(int i = 2;i < n;i++)
		if(a[i] > 1)return 1;
	return 0;
}
int main(){
	T = rd();
	while(T--){
		n = rd();
		for(int i = 1;i <= n;i++)
			a[i] = rd();
		if(n == 3 && (a[2] & 1) || !check()){//无解条件
			puts("-1");
			continue;
		}
		ll res = 0;
		for(int i = 2;i < n;i++)
			res += (a[i] + 1) / 2;//统计答案，上取整
		printf("%lld\n",res);
	}
	return 0;
}
```


---

