# N Problems During K Days

## 题目描述

Polycarp has to solve exactly $ n $ problems to improve his programming skill before an important programming competition. But this competition will be held very soon, most precisely, it will start in $ k $ days. It means that Polycarp has exactly $ k $ days for training!

Polycarp doesn't want to procrastinate, so he wants to solve at least one problem during each of $ k $ days. He also doesn't want to overwork, so if he solves $ x $ problems during some day, he should solve no more than $ 2x $ problems during the next day. And, at last, he wants to improve his skill, so if he solves $ x $ problems during some day, he should solve at least $ x+1 $ problem during the next day.

More formally: let $ [a_1, a_2, \dots, a_k] $ be the array of numbers of problems solved by Polycarp. The $ i $ -th element of this array is the number of problems Polycarp solves during the $ i $ -th day of his training. Then the following conditions must be satisfied:

- sum of all $ a_i $ for $ i $ from $ 1 $ to $ k $ should be $ n $ ;
- $ a_i $ should be greater than zero for each $ i $ from $ 1 $ to $ k $ ;
- the condition $ a_i < a_{i + 1} \le 2 a_i $ should be satisfied for each $ i $ from $ 1 $ to $ k-1 $ .

Your problem is to find any array $ a $ of length $ k $ satisfying the conditions above or say that it is impossible to do it.

## 样例 #1

### 输入

```
26 6
```

### 输出

```
YES
1 2 4 5 6 8 
```

## 样例 #2

### 输入

```
8 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
YES
1 
```

## 样例 #4

### 输入

```
9 4
```

### 输出

```
NO
```

# 题解

## 作者：chsyao (赞：5)

有趣的构造题。。

设数列的和为$S$

先考虑和最小的一种构造方案。由题目可得，这个数列必须是一个单调上升的序列，因此和最小的数列显然就是一个首项为$1$，公差为$1$，项数为$k$的等差数列

如果此时$S>n$，那么显然是无解的

否则我们考虑往数列的某些位置加数

显然所有公差为$1$的等差数列都是符合题意的数列，因此我们可以先把数列的每一项都加上一个$\lfloor\frac{n-S}{k}\rfloor$

现在还剩$(n-S)\ mod\ k$需要加。

前面说过，每一个公差为$1$的等差数列都是满足的，因此我们可以考虑每次把数列的某个后缀都加$1$

假设我们把从$i$到$k$的这个后缀加$1$，那么$i$必须满足$a_i+1\leq 2a_{i-1}$，这里暴力的加就好了

如果已经加不下去了，那么就已经无解了

计算复杂度：

构造开始的等差数列$O(k)$

数列加一个数$O(k)$

暴力加后缀，最多只会加$k$次，这里的复杂度还是$O(k)$

因此总复杂度$O(k)$

下面上代码
```cpp
#include <algorithm>
#include <cstdio>

using namespace std ;

typedef long long LL ;
const int N=2e5+10 ;

int a[N] ;
int n , k ;
LL sum ;

int main ()
{
	int i ;
	scanf("%d%d",&n,&k);
	for ( i=1 ; i<=k ; i++ ) a[i]=i,sum+=(LL)i;
	if ( sum>n ) return puts("NO")*0;
	LL d=(n-sum)/k , l=n-sum-d*k;
	while ( l )
	{
		for ( i=k ; l && i>=1 ; i-- ) 
			if ( a[i]+d+1<=2*(a[i-1]+d) ) a[i]++,l--;
		if ( l && a[k]+d+1>2*(a[k-1]+d) ) return puts("NO")*0;
	}
	puts("YES");
	for ( i=1 ; i<=k ; i++ ) printf("%lld ",a[i]+d);
	return 0 ;
}
```

---

## 作者：momo5440 (赞：2)

这是一道挺诡异的构造题，题目描述也需要改一下，其中要求的第三条应该为**a**到第**k**项的求和等于**n**，下面就让我们进入正题

首先让我们考虑一个数列：

**1，2，3，4，5，……，k-1，k**

这是最基本的等差数列，很明显任意一项也都满足题目中所描述的条件——证明：设这是第**i**项(**i**>=2)则需满足**i-1 < i <= 2 * (i-1)** 左边很明显成立现在只需关注右边将其左右移动一下则变为**i>=2**很明显这在(**i**>=2)的条件下恒成立

那么便考虑什么情况下构造不出来，很明显上述数列是最小的符合题意的数列，所以构造不出来的条件**之一**就是上述数列的和比**n**大，即**k*(k+1)/2>=n**

下面就来证一个引理：任意公差为1的数列相邻两项就算加1也不会不满足提议设其第**i**项为**m**(**m**>=2)， 只需证(m-1)+1<m+1<=2*[ (m - 1) +1 ]这十分好证，在此请读者们自行证明

由引理可以让我们想到一个问题，**上述数列相邻两项加任意实数是不是都仍然满足题意**，这也十分好证只需将加的数设为**l**然后根据题意列式即可

于是我们就得出对**n**操作的第一步：首先从**n**中挖出**k*(k+1)/2**来构造出上述数列然后对于剩下的**n-k*(k+1)/2**将他分成k份（每一份都是整数）将平凡的等差数列（上述数列）每一项都加上这k份中的一份由刚才的推论可以得出加上了这**k**份后的数列仍然满足题意

现在只需要考虑剩下的那被分完的n所剩下来的部分，因为**n-k*(k+1)/2**不一定被k整除所以一定会有剩余，我们设这个剩余为**nn**，很明显我们想要把**nn**也均分给完成了第一部的数列，由引理知假如相邻两项都加一则数列仍然满足题意，但是由于**nn<=k**所以必定会有一项能加一而相邻的一项不能加一，不能加的肯定在左边，因为假如第i项加了但第i+1项没加那么这两项就会相等因为这个数列公差为一
在刚才证明引理推论时可以发现到后面当第i项的值越来越大时他与第i-1项的值的俩倍的差会越来越大所以假如这个断层出现在后面我们完全不用担心，所以我们的任务是摸清楚在哪里的断层会造成影响

这很好知道，当断层出现在1，2之间时会出现问题所以我们不能把断层放在这里，而会出现这种情况的**n**必定等于**k*(k+1)/2+k-1**所以在这里需要特判一下，我们只需把那个多余的一给最后一位就行了，但是这里也还需特判，若k==3时输出的数列就会变为1，2，5这很明显是不对的所以也需要特判

我们的第二步差不多也就出来了：从后到前把每一位加上一直到**nn**耗尽，而且还需要特判

差不多也就是这么多了，有问题欢迎私信，把我的博客厚颜无耻地贴上[博客](https://www.luogu.org/blog/ailundeyugang/#)

把代码贴上

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll a[maxn],n,k,t,l;
int main(){
	cin>>n>>k;
	if (k*(k+1)/2>n){
		cout<<"NO"<<endl;
		return 0;
	}
	if (n==k*(k+1)/2+k-1){
		if (k==1){
			cout<<"YES"<<endl;
			cout<<'1'<<endl;
			return 0;
		}
		if (k==2){
			cout<<"NO"<<endl;
			return 0;
		}
		if (k==3){
			cout<<"NO"<<endl;
			return 0;
		}
		cout<<"YES"<<endl;
		cout<<'1'<<' '<<'2'<<' ';
		for (int i=3;i<=k;i++){
			if (i==k){
				cout<<i+2<<' ';
				return 0;
			}
			cout<<i+1<<' ';
		}
		return 0;
	}
	cout<<"YES"<<endl;
	ll sum=k*(k+1)/2;
	t=(n-sum)/k,l=(n-sum)%k;
	int tp=k;
	for (int i=1;i<=l;i++){
		a[tp]++;
		tp--;
	}
	for (int i=1;i<=k;i++){
		cout<<a[i]+i+t<<' ';
	}
}
```


---

## 作者：Rainy_chen (赞：1)

没人写题解那我过来写一发

首先题意是想让我们构造一个长度为$k$的并且和为$n$的数列 并满足一些奇怪的条件  
  
### 官方题解

![](https://cdn.luogu.com.cn/upload/pic/59544.png)

我们简单翻译一下  

首先令$nn = n-\sum_{i=1}^ki$ 我们很容易能得出当$nn < 0$时答案是无解 这是因为对原数列填上$1,2\dots k$是和最小的方案 如果在这个情况下和依然大于$n$ 那么很显然是无解的

之后构造数列$a$ 首先令$a_i=\lfloor\frac {nn}k\rfloor$ 但对于最右边的$nn\%k$个数 我们令其为$\lceil\frac {nn}k\rceil$ 那么此时我们构造出的数列$a$的和应当是$nn$ 这一点是显然的（原话如此）  
我们可以发现$a$一定是一个单调不减数列 之后我们对每一个$i$ 给$a_i$加上$i$ 这样做以后我们得到的$a$一定是满足以下两个条件的
- 和为$n$
- 单调递增  
  
  
$a$是否满足$a_i\le 2a_{i-1}$呢？ 并不一定  
比如说对于$n=13,k=4$ 我们按照这种方法构造出了一个$a$ 那么它长这个样子  
$a=\{1,3,4,5\}$ 那么很显然这个数列并不符合我们要求的规则  
但是至少在某些情况下它是对的 比如$nn\not=k-1$或者$k=1$ 对于其他的情况 我们要分情况讨论  
我们发现出现上面这种情况的唯一可能就是$nn=k-1$ 那么我们可以经过推理得出$n = (\sum_{i=1}^ki)+k-1$  
首先可以证明当$k=2,k=3$时遇到这种情况是无解的 我们可以直接根据上面这个式子求出$n,k$ 然后自己手玩来证明确实无解  
对于剩下的情况 我们可以直接给$a_2$减一 然后给$a_k$加一  
首先我们需要考虑给$a_2$减一会不会导致$a_3$不合法 然后我们发现$a_2,a_3$的差似乎只有2（这是因为当$nn=k-1$时从$a_2$到$a_k$都会加一 而给$a_i$加$i$又造成了1的差） 而$a_2 > a_1 > 0$ 于是$a_2>1$ 这就导致即使$a_2$减一 $a_3$也是合法的  
至于说$a_k$加一会不会不合法 这里的证明和上面这个是差不多的 

然后这东西就做完了 很麻烦对吧 于是我们这里再介绍一种做法

### 非官方做法

![](https://cdn.luogu.com.cn/upload/pic/59545.png)

简单来说 我们需要先将$a_i$赋值为$i$ 然后对于剩下的$nn$ 我们给每一个$a_i$分配$\lfloor\frac {nn}k\rfloor$ 对于之后剩下的数 我们再从后往前枚举 在满足要求的情况下给每个数分配上尽量多的值 如果再之后数还没分配完 就可以判定无解了  

我们需要解决的是两个问题
 - 当我们进行第二步操作时 为什么数列依然是合法的
 - 当我们进行完第三步操作后 为什么如果数没分配完就无解了  
 
 
第一个问题是很好解决的  
很显然我们发现$a_i\le 2a_{i-1}$的本质就是$a_i-a_{i-1}\le a_{i-1}$  
对于数列$\{1\dots k\}$ 给每个数加上一个常量后$a_i-a_{i-1}$是不变的 而此时$a_{i-1}$又会增大 上面那个不等式依然是会被满足的  

第二个问题也不难解决  
很显然当我们给每个数分配上$\lfloor\frac {nn}k\rfloor$后剩下的值是一个不超过$k-1$的数  
而我们从后往前遍历的时候每一个数应该都能至少$+1$ 如果我们分配不完这个数 那就说明有一个位置不能让我们给他$+1$ 然后出于解决第一个问题时的那个式子 如果我们当前这个位置不能$+1$ 之后的所有位置都不能$+1$  
那我们为什么不给$a_1$加上一？ 这样的话之后的数不是就可以变得更大了吗  
对 没错 但是给$a_1$加上一的代价是之后所有数都要$+1$ 因为在这一步之前所有数的差只有1 为了满足递增的条件我们不得不付出至少$k$的代价 而我们能用来分配的数是不超过$k-1$的  

然后就做完了  

官方题解 来源于 `MikeMirzayanov`  
非官方题解 来源于 `myHandle`  
在这里向他们表示感谢

---

## 作者：NOI_O2 (赞：0)

## 题面
[D. N Problems During K Days](https://codeforces.com/contest/1157/problem/D)

## 思路
对于这题，刚开始我陷入了对公式的执着，企图用公式直接确定第一个数，然后试着去找序列。经过思考和手动模拟后发现很难保证正确性。

对于这题，第一步很明确，就是确定第一个数。如果给定了 $n$ 和 $k$，那么第一个数是可以确定的。因为如果我们只保证后一个数比当前数多 $1$，并且确定第一个数是 $1$，那么可以根据 $k$ 确定对应的最小和 $sum=\cfrac{k(k+1)}{2}$
 这个公式比较基础。这样我们就可以把 $n<sum$ 的情况全部排除掉了。

接下来，分析确定的 $k$ 和 $n\geq sum$ 的情况：
首先，可以确定一个公式：$n−sum=k\times t+res$ $res<k$ 这个公式也比较基础。有了这个公式后，就比较明了，因为可以在 $sum$ 的基础上把 $t$ 个 $k$ 平摊掉，这样 $k$ 个数每个数加 $1$。

接下来处理 $res$，这里可能需要动脑袋思考一下。但我们依然需要明确，第一个数是不可以改变的，因为第一个数改变了会直接影响后面的所有数。

处理 $res$ 时，我们可以直接从当前确定的数组从后往前进行加操作，操作的前提是满足题目给定的条件。加了之后会发现，如果当前的数加了一个数后，那么右边已经加过的数范围又变了，又可以加了，但是有限度，因为第一个数已经确定了。（这里也提醒了我们为什么不从左往右进行处理）。

处理 $res$ 的时候，如果出现了遍历一遍后，$res>0$ 并且没有加数的情况，就表示数组已经无法满足题目给定的条件了，直接输出 `NO` 即可。
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int n;
int k;
int a[100101];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
    //第一个数为1的最基础的情况
	int sum=(k*(k+1))>>1;
	if(sum>n)
	{
		cout<<"NO
";
		return 0;
	}
	n-=sum;
	int res=n%k;
	a[1]=1+n/k;
	for(int i=2;i<=k;++i)
		a[i]=a[i-1]+1;
    //满足最低要求后，还剩下res < k
	while(res)
	{
		bool flag=1;
        //第一个数一定不能变
		for(int i=k;i>1;--i)
		{
			int tmp=(a[i-1]<<1)-a[i];
			if(res>0&&tmp>0)
			{
            	//数组中有数变化了
				flag=0;
				if(res>=tmp)
				{
					a[i]+=tmp;
					res-=tmp;
				}
				else
				{
					a[i]+=res;
					res=0;
				}
			}
		}
		if(flag)
		{
			cout<<"NO
";
			return 0;
		}
	}
	cout<<"YES
";
	for(int i=1;i<=k;++i)
		cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：0)

简单题。

首先在满足合法前提下让总和最小，不难想到是一个首项为 $1$，公差为 $1$，项数是 $k$ 的等差数列。

如果现在总和已经比 $n$ 大，那么肯定就是无解。

考虑调整。对于一个等差数列，在一个位置上加 $1$，其后面的数都加 $1$ 才能保证合法，所以每次一个位置加 $1$ 可以认为是后缀加 $1$。

我们发现，在一个靠前的位置后缀加，能扩大后面的数增加的范围，也能使得 $n$ 减小，总的来说就是一定能让当前状态更优。所以我们的策略是从前往后扫，能加就加。

然后就是计算一个位置能加多少了，设一个位置当前值为 $a_i$，前一个位置的值为 $a_{i-1}$，所以最多增加的值就是 $2\times a_{i-1}-a_i$。然后加了会让后缀都加 $1$，设后缀一共有 $x$ 个数，总和距离 $n$ 还剩 $y$，那么为了保证能正好凑出 $n$，所以最多增加 $\lfloor \frac{y}{x} \rfloor$。

所以第 $i$ 个位置最多能增加 $\min(2\times a_{i-1}-a_i,\lfloor \frac{y}{x} \rfloor)$。

因为是后缀加，所以直接记录后缀加了多少，枚举到一个数直接加上这个值即可。

因为第一个数是没有第二个限制的，所以令 $a_0=+\infty$ 即可。

如果枚举结束还没有凑出 $n$，即为无解。

如果凑出来就是有解，输出序列即可。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,k,a[N],sum;
signed main()
{
	k=read(),n=read();
	for(int i=1;i<=n;i++){
		a[i]=i;
		k-=i;
	}
	if(k<0){
		puts("NO");
		return 0;
	}
	a[0]=1e9;
	for(int i=1;i<=n;i++){
		a[i]+=sum;
		int x=n-i+1;
		int y=min(2*a[i-1]-a[i],k/x);
		a[i]+=y;
		sum+=y;
		k-=x*y;
	}
	if(k){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	return 0;
}

```

---

## 作者：Yuno (赞：0)

这是一个垃圾 $O(klog_2n)$ 的做法。

首先由等差数列等比数列的基本知识可得：

设数列和为 $S$ ，则对于一个固定的 $a_1$

$S_{min}=k\times a_1+\frac {(k-1)\times k}{2}$

$S_{max}=a_1\times (2^k-1)$

然后有一个比较显然但是我不会严谨证明的结论：

当 $S_{min}\leq n \leq S_{max}$ 时，一定有解。

感性理解一下，每个数加加减减一定可以凑出 $n$。

所以我们可以枚举在 $[1,10^9]$ 里枚举首项，注意枚举的起点可以先算一下，防止超时。

具体地说，因为 $S_{max}\geq n$，所以 $a_1 \geq \frac {n}{2^k-1}$

这样还是不够，假如当前枚举的数的 $S_{min}\geq n$， 那么之后的数显然也不可能作为首项，退出。

这样可以找到一个首项，找不到就输出 $NO$。

然后就是要构造这个数列。

记当前构造到了第 $i$ 项，已构造数列和为 $sum$，当前要填入的数为 $x$。

设 $len=k-i+1$

则有 $sum+len\times x+\frac{(len-1)*len}{2}\leq n$

不然的话后面怎么填都会超过 $n$.所以找一个最大的 $x$ 满足这个式子即可。

那么由于 $x$ 满足单调性，所以二分一下，感觉也可以数学方法算，~~不管了~~

还有一个小细节，为了防止爆 $long\ long$， 在算 $S_{max}$ 时，如果当前数已经大于 $10^9$， 就返回一个极大值。

复杂度：$O(klog_2n)$

$Code:$

```cpp
#include <bits/stdc++.h>
#define int long long
using std::cin;
using std::cout;

const int N = 100007;
int n, k, a[N];

int qp(int base, int p) {
	int res = 1;
	while (p) {
		if (p & 1) {
			if (res * base > 1000000000)
			return 1000000001;
			res *= base;
		}
		p >>= 1;
		if (base * base > 1000000000) {
			base = 1000000001;
		} else
		base *= base;
	}
	return res;
}

signed main() {
	std::ios::sync_with_stdio(0);
	cin >> n >> k;
	int st = n / (qp(2, k) - 1);
	int pos = -1;
	for (int i = st; i <= 1e9; ++ i) {
		a[1] = i;
		int min = k * a[1] + (k - 1) * k / 2;
		int max = a[1] * (1 - qp(2, k)) / (1 - 2);
		if (min > n) {
			break;
		}
		if (min <= n && n <= max) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "NO\n";
		return 0;
	}
	int s = a[1];
	for (int i = 2; i <= k; ++ i) {
		int l = a[i - 1] + 1, r = a[i - 1] * 2, len = k - i + 1, ans = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			int x = len * mid + (len - 1) * len / 2;
			if (x + s > n) r = mid - 1;
			else l = mid + 1, ans = mid;
		}
		a[i] = ans;
		s += a[i];
	}
	cout << "YES\n";
	for (int i = 1; i <= k; ++ i) {
		cout << a[i] << ' ';
	}
	cout << '\n';
	return 0;
}
```

---

