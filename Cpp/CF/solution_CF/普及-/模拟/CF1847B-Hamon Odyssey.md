# Hamon Odyssey

## 题目描述

乔纳森正在与迪奥的吸血鬼手下战斗。其中有 $n$ 个吸血鬼，它们的强度分别为 $a_1, a_2,\cdots, a_n$。
将 $(l,r)$ 表示由索引 $l$ 到 $r$ 的吸血鬼组成的一组。乔纳森意识到每个这样的组的强度取决于它们的最弱环节，即按位与操作。更具体地说，组 $(l,r)$ 的强度等于 $f(l,r) =$ $a_l \ \& \ a_{l+1} \ \& \ a_{l+2} \ \& \cdots \&  \ a_r$。这里，$\&$ 表示按位与操作。

乔纳森希望能快速击败这些吸血鬼手下，因此他会将吸血鬼分成连续的组，使得每个吸血鬼正好属于一组，并且这些组的强度之和尽量小。在所有可能的分组方式中，他希望找到组数最多的方式。

给定每个吸血鬼的强度，找出在所有可能的分组方式中，拥有最小强度之和的组的最大数量。

## 样例 #1

### 输入

```
3
3
1 2 3
5
2 3 1 5 2
4
5 7 12 6```

### 输出

```
1
2
1```

# 题解

## 作者：WsW_ (赞：6)

### 更新
* 2023/7/10 在思路中完善对于切割后最后一段的处理方法；补充一个标点；补充提交记录。  

感谢指出问题！看得出来审核员真的很细心！
### 思路  

#### $\operatorname{and}$ 运算的性质
[$\operatorname{and}$ 运算（百度百科）](https://baike.baidu.com/item/AND/8739341?fr=ge_ala)  
观察对于每一位 $\operatorname{and}$ 运算的四种情况，易总结出：
$$a,b\ge a\operatorname{and} b$$  
因此，题意中的最小值肯定为：
$$a_1\operatorname{and}a_2\operatorname{and} \cdots\operatorname{and}a_n$$  
另外，$\operatorname{and}$ 运算显然满足结合律和交换律。  
当 $a\operatorname{and}b>0$ 时，$a,b>0$。  
当 $a\ne 0$ 且 $b\ne 0$ 时，$a\operatorname{and}b<a+b$。  

#### 分类讨论
当 $a_1\operatorname{and}a_2\operatorname{and} \cdots\operatorname{and}a_n>0$ 时，我们可以根据结合律将式子分割成**任意**两个部分，设两个部分值分别为 $a,b$，则 $a \operatorname{and} b=a_1\operatorname{and}a_2\operatorname{and} \cdots\operatorname{and}a_n>0$。  
$$\because a_1\operatorname{and}a_2\operatorname{and} \cdots\operatorname{and}a_n>0$$
$$\therefore a \operatorname{and} b>0$$
$$\therefore a,b>0$$
$$\therefore a+b>a\operatorname{and}b$$
所以无法进行分割，答案为 1。  

当 $a_1\operatorname{and}a_2\operatorname{and} \cdots\operatorname{and}a_n=0$ 时，采用贪心算法。  
从 $a_1$ 遍历到 $a_n$，不断进行 $\operatorname{and}$ 运算，当值为 $0$ 时，切一刀，段数加一。  
因为当前值已经为 $0$ 时，再进行 $\operatorname{and}$ 运算依然为 $0$ ，继续操作无意义。 
我们只需要统计切了几刀即可，每分出一段切一刀，最终能分出的段数等于刀数。   
对于最后一部分，如果运算后值不为 $0$，那么就需要把它并入前一段，总刀数不变；如果运算后值为 $0$，那么在末尾再切一刀，总刀数加一。

### 代码与[提交记录](https://codeforces.com/contest/1847/submission/212442623)
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200004];
int ans;
int minn;
int an=-1;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&a[1]);
		minn=a[1];
		for(int i=2;i<=n;i++){
			scanf("%d",&a[i]);
			minn=minn&a[i];//计算最小值
		}
		if(minn>0){
			printf("1\n");
			continue;
		}
		ans=0;
		an=-1;
		for(int i=1;i<=n;i++){
			if(an==-1){//一段的开头
				an=a[i];
			}
			an=an&a[i];
			if(an==0){//分段
				an=-1;
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：5)

### 分析

我们需要把数列 $a$ 分成若干段，使得每一段中的数按位与起来的值之和尽可能小，并使段数尽可能多。

我们知道，一堆数按位与起来只会让结果越来越小。我们设 $a_1\  \texttt{\&}\  a_2\  \texttt{\&}\  \cdots\  \texttt{\&} \ a_n=x$，那么如果把数列 $a$ 分成若干段，每一段中的数按位与起来的值一定不小于 $x$。

只有 $0$ 加若干个 $0$ 才等于 $0$，所以如果 $x \neq 0$，那么 $a$ 只能作为一大段，因为如果将 $a$ 分成了多段，每一段中的数按位与起来都不小于 $x$，总和至少是 $x$ 与段数的乘积，显然是大于 $x$ 的。于是我们可以得到，如果 $x \neq 0$，那么段数就一定为 $1$。

接下来，我们考虑 $x=0$ 时的情况。我们知道我们要把 $a$ 分成若干段，使得每一段中的数按位与起来的值都为 $0$，那我们把 $a$ 从前往后扫，记录当前段的按位与的值，当某一瞬间按位与的值为 $0$，新开一段并记录段的数量即可。

要注意若最后多出来的几个数按位与的值不为 $0$，需要将它们合并到上一段中。

### 代码

```c++
const int N=2e5+5;
int a[N];
void solve(){
	int ans=0,n=read(),x,k=-1;
	for(int i=1;i<=n;i++) a[i]=read();
	x=a[1];
	for(int i=2;i<=n;i++) x=x&a[i];
	if(x!=0){
		cout<<1<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		if(k==-1) k=a[i],ans++;
		k=a[i]&k;
		if(k==0) k=-1;
	}
	if(k!=-1) ans--;
	cout<<ans<<endl;
}
```

---

## 作者：Furina_Hate_Comma (赞：2)

一道**性质**题。

按位且运算有以下性质：

$$a \land b\le a+b$$

根据这条性质，我们知道此时的最小值一定是 $a_1\land a_2\land a_3\cdots a_n$。

然后又因为只有 $a=0$ 且 $b=0$ 时：才有 $a\land b=a+b$。

所以就是找可以拆成且值等于 $0$ 的区间的最大数量。

code：
```
#include<bits/stdc++.h>
using namespace std;
int a[500000];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,ans=INT_MAX;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i]; 
			ans&=a[i];
		}
		if(ans!=0)cout<<1<<'\n';
		else{
			int tot=0,now=INT_MAX;
			for(int i=1;i<=n;i++){
				now&=a[i];
				if(now==0){
					tot++;
					now=INT_MAX;
				}
			}
			cout<<tot<<endl;
		}
	}
}
```

---

## 作者：arkerny (赞：0)

## 题目大意

将一个数组分为若干个子段，使得各段的按位与运算结果之和最小，且使段的数量最大。

## 题目分析

本题主要考察位运算的性质。

首先，根据按位与运算的性质可得最小值必为 $a_1 \operatorname{and} a_2 \operatorname{and} \dots \operatorname{and} a_n$:

取数 $a,b$ 的二进制表示，手模一下按位与运算易得 $a,b \ge a \operatorname{and} b$。

同时，$a+b \ge a \operatorname{and} b$，当且仅当 $a=b=0$ 时取等，因此 $a_1 \operatorname{and} a_2 \operatorname{and} \dots \operatorname{and} a_n > 0$ 时，答案为 $1$。

$a_1 \operatorname{and} a_2 \operatorname{and} \dots \operatorname{and} a_n = 0$ 时，从头到尾找按位与为 $0$ 的子段的最大数量即为答案。但是这里需要注意，在已经取了 $k$ 段后，第 $k+1$ 段的按位与值可能始终取不到 $0$，在这种情况下，则应当将第 $k+1$ 段与第 $k$ 段再做一次按位与运算使最后一段的按位与值取到 $0$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;

int n,ans,a[2000010],minn;

void init()
{
    ans=0;
    return ;
}

void solve()
{
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    minn=a[1];
    for(int i=2;i<=n;i++)
    {
        minn&=a[i];
    }
    if(minn>0)
    {
        printf("1\n");
        return ;
    }
    for(int i=1;i<=n;i++)
    {
        int j=i;
        int now=a[i];
        while(j<n&&now>0)
        {
            now&=a[++j];
        }
        if(now==0)
        {
            ans++;
        }
        i=j;
    }
    printf("%d\n",ans);
    return ;
}

int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：dengqingrui123 (赞：0)

# Step 0 前置知识

$\operatorname{and}$ 即 `&`——按位与。

#### 按位与的特性：

  $a , b \le a \operatorname{and} b$
  
因此可以得出题中的最小值：
  $a_1 \operatorname{and} a_2 \operatorname{and} \cdots \operatorname{and} a_n$
  
# Step 1 解题思路

因为 $1 \le n \le 2 \times 10 ^ 5$ 考虑使用 $O(nT)$ 的算法。

先输入数据存在数组 $a$ 中，定义 $ans \gets 1$ 然后从头开始扫一遍数组 $a$ 一旦发现有 $k$ 个数按位与在一起结果为 $0$ 时，` ans++ `，随后继续扫，直到扫到结尾为止。

这时会有两种情况：
1. 最后 $k_n$ 个数按位与后结果大于 $0$ ，这时要把最后 $k_n$ 个数与 $k_{n-1}$ 合在一起，最后 `ans--`；
2. 在数组 $a$ 中找不到连续的 $k$ 个数按位与起来等于 $0$，即 数组 $a$ 中不存在任何一种拆分能比数组 $a$ 全部数按位与起来更小，此时 $ans \gets 1 $；

**特别注意，别认为 $O(nT)$ 会 TLE，因为题目中有“所有测试用例中 $n$ 的总和不超过 $2 \times 10 ^ 5$”这句话，所以不用担心TLE。**

# Step 2 AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

long long T, n, a[200005], sum, t[45], tt[45], k[200005], top = 1,ans;

inline void find(long long x){
	long long qwq = 1;
	while (x){
		if (x & 1) t[qwq] = 1;
		x >>= 1,qwq++;
	}
}

inline bool jiancha(){
	long long ans = 0;
	for (int i = 1; i <= 40; i++) if (tt[i] == 1) return false;
	return true;
}

int main(){
	scanf ("%lld", &T);
	while (T--){
		scanf ("%lld", &n);
		for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
		memset (k, 0, sizeof(k));
		sum = a[1],top = 0;
		for (int i = 2; i <= n; i++) sum &= a[i];//判断是否为第二种情况。
		if (sum){printf ("1\n");continue;}
		for (int i = 1; i <= 40; i++) tt[i] = 1;
		for (int i = 1; i <= n; i++){
			find(a[i]);
			for (int j = 1; j <= 40; j++) if (t[j] == 0) tt[j] = 0; 
			for (int j = 1; j <= 40; j++) t[j] = 0;
			if (jiancha()){
				k[++top] = 1;
				for (int j = 1; j <= 40; j++) tt[j] = 1;
			}
		}
		ans = 0;
		for (int i = 0; i <= n; i++) if (k[i]) ans = i;
		printf ("%lld\n", ans);
	}
	return 0;
}

```
# Step 3 最后警告
**十年OI一场空，多测不清见祖宗。**

---

## 作者：guozhetao (赞：0)

## 题意
给定一个 $n$ 位的数组 $a_i$，并将 $a_i$ 分开成 $ans1$ 个连续的部分，并使得 $a_i \land a_2 \dots a_n = a_1 \land a_2 \dots a_i + a_{i + 1} \land a_{i + 2} \dots a_j + a_{j + 1} \land a_{j + 2} \dots a_n$，并输出 $ans1$ 的最大值。
## 思路
本题目主要考察与运算。

首先设 $a_1 \land a_2 \dots a_i$ 为 $A$，$a_{i + 1} \land a_{i + 2} \land a_n$ 为 $B$。根据题目，$A + B=A \land B$，且 $A \land B \leq \min(A,B) \leq A + B(A,B \geq 0)$，所以 $A \land B = \min(A,B) = A + B$。因为 $\min(A,B) = A + B(A,B \geq 0)$，所以 $A = B = 0$。所以如果数组 $a$ 能满足题意的分成几个连续的部分，$a_i \land a_2 \dots a_n = 0$。所以如果数组的 $a_i \land a_2 \dots a_n > 0$，输出 `1` 即可。

然后，我们设 $ans1 = 1$，我们遍历数组，依次寻找能使 $a_i \land + a_{i + 1} \dots a_j = a_{j + 1} \land a_{j + 2} \dots a_n$ 的最小的 $j(j < n)$。如果找得到，就意味着剩下的数组还能继续分割，所以 $ans \gets ans + 1,i \gets j + 1$。因为计算 $a_{j + 1} \land a_{j + 2} \dots a_n$ 耗时很大，我们**需要预处理**。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int ask[200005];
inline int find(int x) {
	int anss = a[x];
	if(anss == 0) return x;
	x++;
	for(;x <= n;x++) {
		anss &= a[x];
		if(anss == 0) return x;
	}
	return -114514;
}
signed main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
		memset(ask,0,sizeof(ask));
		ask[n] = a[n];//预处理
		for(int i = n - 1;i >= 1;i--) ask[i] = ask[i + 1] & a[i];
		int ans = ask[1],ans1 = 1;
		if(ans) {
			printf("1\n");
			continue;
		}
		for(int i = 1;i <= n;) {
			int x = find(i);
			if(x < i or x == n or ask[x + 1] != ans) {
				printf("%d\n",ans1);
				break;
			}
			ans1++;
			i = x + 1;
		}
	}
}

```


---

## 作者：_5t0_0r2_ (赞：0)

# 分析：
位运算中的 $\text{and}$ 运算有这么几条性质：

$a \geq a \land  b$ 且 $b \geq a \land b$，**当且仅当** $a = b$ 时两式可以取到等号。

这个道理不难理解，对于任意一个二进制下的数，它按位与另一个书，原数为 $0$ 的位不可能变成 $1$，但原数为 $1$ 的位可能变成 $0$，所以原数只能变小不能变大。

所以可以得出最小强度之和为：

$a_1 \land a_2 \land \dots \land a_n$。

设这个数为 $x$。

同时，$\text{and}$ 运算还有一条性质：

$a + b \geq a \land b$，**当且仅当** $a = 0$ 且 $b = 0$ 时取到等号。

接下来，我们分类讨论。

当 $x = 0$ 时，根据前一条性质，我们把序列 $a$ 不断拆分，使每段拆分出的序列按位与的值也为 $0$ 即可。

否则，当 $x > 0$ 时，不管怎么拆结果都大于 $x$，所以答案为 $1$。

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

给定一个数组，将这个数组分为若干段，每一段 $[l, r]$ 的“强项”值为 $f_{l, r} = a_l \& a_{l + 1} \& \dots \& a_{r} $。当每一段的“强项”之和最小时，最多分为几段。

### 题目分析

本题主要考察位运算与。

根据一个数与上另一个数，这个数只会变小或不变，不会变大这一性质，对于某一段的“强项”值 $f_{l, r}$，我们不难发现，将其分为两段 $[l, mid]$ 和 $[mid+1, r]$，$f_{l, r} \le f_{l, mid} + f_{mid+ 1, r}$（当 $f_{l, mid}$ 和 $f_{mid+1,r}$ 都为 $0$ 时，不等式取等）。

用人话说就是当 $f_{l, r} = 0$ 时，我们有可能将其分为两段，并且这两段的“强项”之和等于 $f_{l,r}$。但是当 $f_{l, r} \neq 0$ 时，如将其分为两段，两段“强项”之和一定大于 $f_{l, r}$。

所以说，当 $f_{1, n} = 0$ 时，我们可以将数组扫一遍，每当前面多项的“强项”值为 $0$ 时，在此分开。当 $f_{1,n} \neq 0$ 时，输出 $1$。（$\forall i \in [1, n-1] f_{1, n}\ge f_{1,i} + f_{i+1,n}$）

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 5;
int T, n, sum, a[N], ans;

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		sum = INT_MAX;
		for(int i = 1;i <= n;i++)
		{
			scanf("%d", &a[i]);
			sum = a[i] & sum;
		}
		if(sum != 0)
			printf("1\n");
		else
		{
			sum = INT_MAX, ans = 0;
			for(int i = 1;i <= n;i++)
			{
				sum = sum & a[i];
				if(sum == 0)
					ans++, sum = INT_MAX;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

