# [ARC137B] Count 1's

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc137/tasks/arc137_b

$ 0,1 $ からなる長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

あなたはこれから，次の操作をちょうど $ 1 $ 回行います．

- $ A $ の**連続する**部分列を選び，そこに含まれる要素を flip する．つまり，$ 0 $ ならば $ 1 $ に変え，$ 1 $ ならば $ 0 $ に変える． なお，ここで選ぶ部分列は空であることも許され，その場合 $ A $ の要素は全く変化しない．

あなたのスコアは，$ A $ に含まれる $ 1 $ の個数です． あなたが取るスコアとしてあり得る値が何通りあるか求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 1 $
- 入力される値はすべて整数

### Sample Explanation 1

スコアとしてあり得る値は，$ 0,1,2,3 $ の $ 4 $ 通りです． 例えば，$ A $ の $ 2 $ 番目から $ 4 $ 番目までの要素を flip すると，$ A=(0,0,0,1) $ となり，スコアは $ 1 $ になります．

## 样例 #1

### 输入

```
4
0 1 1 0```

### 输出

```
4```

## 样例 #2

### 输入

```
5
0 0 0 0 0```

### 输出

```
6```

## 样例 #3

### 输入

```
6
0 1 0 1 0 1```

### 输出

```
3```

# 题解

## 作者：Glacial_Shine (赞：5)


[更好的体验(包括A~C)](https://blog.csdn.net/weixin_46700592/article/details/129032554?spm=1001.2014.3001.5501)

---

## 思路
假设我们所能得到的分数的最大值为 $ansmax$，最小值为 $ansmin$，则答案一定为 $ansmax - ansmin + 1$，因为每次多改变一个节点，所能取到的分数只会改变一，在整数情况下看他是连续的。

再稍微转换一下，就会发现，其实也就是求变换之后所能对原分数产生的改变的最大值和最小值的差。

于是我们将问题变为了如何求改变的最大值和最小值。

我们先将原数组按一下方式处理：

- 如果 $a_i$ 为 $1$，则将 $b_i$ 设为 $-1$。
- 如果 $a_i$ 为 $0$，则将 $b_i$ 设为 $1$。

此时的 $b$ 数组记录的就是如果改变这个节点，会对当前分数产生的影响。

我们再将 $b$ 数组取一个前缀和，此时 $b$ 数组表示的就是从第一个节点到这个节点全部改变对分数产生的影响。

我们记录一个从起点开始改变，所能得到分数的最大值为 $maxn$，最小值为 $minn$。

我们从一开始枚举，对于每个节点，我们都将 $ansmax$ 和 $ansmin$ 更新一下，然后更新一下 $maxn$ 和 $minn$ 就可以了。

更新方式看代码。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, a[300005], b[300005], maxn, minn, ansmax, ansmin;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = b[i - 1] + (a[i] == 0 ? 1 : -1);
    for (int i = 1; i <= n; i++) {
        ansmax = max(ansmax, b[i] - minn);
        //b[i]-minn 就是以当前节点为结尾所能产生的最大值
        ansmin = min(ansmin, b[i] - maxn);
        //b[i]-maxn 就是以当前节点为结尾所能产生的最小值
        maxn = max(maxn, b[i]);
        minn = min(minn, b[i]);
    }
    printf("%d", ansmax - ansmin + 1);
    return 0;
}
```

---

## 作者：_UniqueGirl_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc137_b)

## 解题思路

假设我们能得到的最大的分数是 $maxx$,最小的分数是 $minx$,我们的可能的种类就是 $maxx-minx+1$,因为这一区域的分数都是可以做到的。而之所以如此，是因为每增加或减少一个数字，就只会改变一个 $0$ 或 $1$，所以这一区间的分数都可以拿到。

于是，问题就成为了让我们求最大分数和最小分数。

我们再用 $b$ 数组记录当前改变会对分数产生的影响，$maxn$ 代表当时所能得到的最大分数，$minn$ 同理。

所以，当：

- $a_i$ 等于 $1$ 时，我们将 $b_i$ 设为 $-1$。因为将其反转后分数会减一。

- $a_i$ 等于 $0$ 时，我们将 $b_i$ 设为 $1$。因为将其反转后分数会加一。

此时，我们再给 $b$ 取前缀和，这时数组 $b$ 就表示从开头到当前节点的所有改变造成的影响。

我们就可以从一枚举，每次更新各个变量的数值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[300005],b[300005];

int main(){
	int n,maxx=0,minx=0,maxn=0,minn=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[i]=b[i-1]+(a[i]==0?1:-1);
	for(int i=1;i<=n;i++){
		maxx=max(maxx,b[i]-minn),
		minx=min(minx,b[i]-maxn);
		maxn=max(maxn,b[i]),
		minn=min(minn,b[i]);
	}
	cout<<maxx-minx+1;
	return 0;
}


```


---

## 作者：Ray_yi (赞：2)

### 思路：

容易发现，得分的可能数就是能得到分数的最大值和最小值之间的数的总数。为什么呢？因为这个数列只由 $0$ 和 $1$ 组成，最大值和最小值之间的每个数总是能得到的。

所以，我们只需要求这段数列的最大值和最小值就可以了。

我们用一个 $b$ 数组记录当前改变对分数产生的影响，再对于每个 $a_i$ 做以下操作：

- 当 $a_i$ 为 $1$ 时，我们把 $b_i$ 设为 $-1$，因为把 $1$ 变为 $0$ 减去了 $1$。
- 当 $a_i$ 为 $0$ 时，我们把 $b_i$ 设为 $1$，因为把 $0$ 变为 $1$ 加上了 $1$。

此时，我们再给 $b$ 数组做一个前缀和，这时的 $b$ 数组即为从开头到当前数的所有改变所受到的影响。

枚举以当前数为结尾所产生的最大值与最小值即可。

~~就不给代码了。~~

---

## 作者：_shine_ (赞：1)

## [参考文献](https://zhuanlan.zhihu.com/p/484020484)
## 题目大意
现在有一个全部是由 $0$ 和 $1$ 组成的序列 $A$，现在可以让你做一次操作，选择一个连续字段进行反转操作。

现在问你有多少种可能的得分。
## 思路
我们可以发现：

如果原来的数为 $1$，经过反转操作后会减 $1$，记作 $-1$。

如果原来的数为 $0$，经过反转操作后会加 $1$，记作 $+1$。

那么，我们拿样例来看一看：

```+1 -1 -1 +1```

现在这个问题就转变为：只有 $1$ 和 $-1$ 的数组内的区间和有多少种不同的数，我们使用最大与最小字段区间和就可以算出答案。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int n,a[maxn],f[maxn];
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
		f[i]=f[i-1];
		if(a[i]==1)f[i]-=1;
		else f[i]+=1;
	}
	int ans=0;
	int sum=0,num=0;
	for(int i=1;i<=n;++i){
		sum=max(sum,f[i]-num);
		num=min(num,f[i]);
	}
	ans+=sum;
	sum=num=0;
	for(int i=1;i<=n;++i){
		sum=min(sum,f[i]-num);
		num=max(num,f[i]);
	}
	ans-=sum;
	cout << ans+1 << endl;
	return 0;
}
```


---

## 作者：_hxh (赞：1)

### 题意

给定一个仅由 $0$ 和 $1$ 组成的，长度为 $n$ 的序列 $A$，可以选择 $A$ 的一个连续子段（可以选择一个空子段），对该子段进行反转操作，最后 $A$ 中 $1$ 的个数就是获得的分数，求有多少种可能的得分。

### 分析

题目中告诉我们可以进行一次反转操作，而反转操作可以让 $1$ 变成 $0$，$0$ 变成 $1$，这说明什么？反转 $1$ 会让我们的得分减少 $1$，反转 $0$ 会让我们的得分增加 $1$。既然我们只要求有多少种可能的得分，所以我们可以把 $A$ 数组中 $0$ 和 $1$ 转化成 $1$ 和 $-1$ 用新的 $B$ 数组存储起来，**这样在 $A$ 数组中反转子段改变的分数就是 $B$ 数组中对应的子段的和啦**。

***

举个例子：

反转 $A_0$ 到 $A_2$。

||反转前|反转后|
|:-:|:-:|:-:|
|$A$ 数组|`0 1 0 1 0 1`|`1 0 1 1 0 1`|
|$B$ 数组|`1 -1 1 -1 1 -1`|`1 -1 1 -1 1 -1`（不变）|
|分数|$\color{blue}{3}$|$\color{red}{4}$|

$B_0 + B_1 + B_2 = 1 - 1 + 1 = 1 = \color{red}{4} - \color{blue}{3}$

注：$B$ 数组不会变化。

***

所以我们利用前缀和的方法可以计算每个区间贡献的**得分变化量**，遍历一下就可以求出最大和最小变化量（或增加值），再减一下就是答案了（记得加 $1$）。

为什么能直接减？难道最大和最小值之间的每个值都能取到吗？当然，$A$ 数组仅由 $1$ 和 $0$ 组成，在取到最大值和最小值的过程中总能取到这些值的。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5;
int n,a[N],max_now,min_now,ans_max,ans_min;
signed main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		a[i] = a[i - 1] + 1 - (a[i] << 1);
	}
	for (int i = 1;i <= n;i++)
	{
		ans_max = max(ans_max,a[i] - min_now);
		ans_min = min(ans_min,a[i] - max_now);
		max_now = max(max_now,a[i]);
		min_now = min(min_now,a[i]);
	}
	cout << ans_max - ans_min + 1 << endl;
	return 0;
}
```

---

## 作者：joker_opof_qaq (赞：1)

### 题意简述

给你一个 $01$ 串，你可以进行 $1$ 次操作，选取一个字串，让这个串中的 $0$ 变成 $1$，$1$ 变成 $0$。


### 思路分析

使用前缀和算法算出来最大、最小字段和，再根据序列连续性算出最大最小值之间数的个数。

此时我们根据 $a_i$ 取值的不同先预处理 $sum_i$ 的值。

- $a_i$ 等于 $0$，将 $sum_i-1$，因为他如果改变就会让结果 $+1$，所以暂时赋 $-1$。
- $a_i$ 等于 $1$，将 $sum_i+1$，因为他改变会使答案 $-1$，所以赋 $+1$。
跑完前缀和，去跑最大，最小字段和，就可以求出 $max$ 和 $min$ 了，自然也就做完了。

### code 和代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
const int N=1e6;
int n,a[N],sum[N],max1, max2,min1,min2;
int main() {
    n=read();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==0)sum[i]=sum[i-1]-1;
        if(a[i]==1)sum[i]=sum[i-1]+1;
    }
    for(int i=1;i<=n;i++) {
        max1=max(max1,sum[i]-min2);
        min1=min(min1,sum[i]-max2);
        max2=max(max2,sum[i]);
        min2=min(min2,sum[i]);
    }
    cout<<max1-min1+1;
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/171880090)

---

## 作者：QuaternaryTree (赞：0)

**题目大意**：

给你一个 $01$ 数组，你可以对他进行一次操作，将选中的区间内的数反转，问你 $1$ 的数量的取值有几种可能。

**思路**：

如果我们将 $1$ 反转则会变成 $0$，$1$ 的数量减一，如果我们将 $0$ 反转则会变成 $1$，$1$ 的数量加一。我们将 $1$ 记为 $-1$，$0$ 记为 $+1$，然后我们就可以求最大、最小子段和来计算中 $1$ 的数量。

**代码**：

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <iomanip>

#define int long long

const int MAXN = 3e6 + 10;

int N;

int a[MAXN];
int sum[MAXN];

int maxn1,minn1;
int maxn2,minn2;

signed main(){
	scanf("%lld",&N);
	for(int i = 1;i <= N;i++){
		scanf("%lld",&a[i]);
		if(a[i] == 0)
			sum[i] = sum[i - 1] - 1;
		if(a[i] == 1)
			sum[i] = sum[i - 1] + 1;
	}
	
	for(int i = 1;i <= N;i++){
		maxn1 = std::max(maxn1,sum[i] - minn2);
		minn1 = std::min(minn1,sum[i] - maxn2);
		maxn2 = std::max(maxn2,sum[i]),
		minn2 = std::min(minn2,sum[i]);
	}
	
	printf("%lld\n",maxn1 - minn1 + 1);
	return 0;
}
```

---

## 作者：木棉絮123 (赞：0)

看到题解区居然没有相同的做法有些惊讶，感觉我的思路更自然一些。

所有得分的情况等于最大得分减去最小得分再加一[^1]，其他题解说的很详细了这里不再赘述。

问题转化为求最大得分和最小得分。我们只讨论求最大得分，不失其一般性[^2]。

先统计全部的 $1$ 的个数。不难发现操作序列中每一个 $0$ 造成 $+1$ 的贡献，每一个 $1$ 造成 $-1$ 的贡献。我们考虑扫描每一段**极大的[^3]**对得分造成**非负贡献**的操作序列，这样可以用双指针优化，因为我们能够把整个序列拆成若干个不相交的极大的序列，中间被一个 $1$ 隔开。假设已经选了一段操作序列，如果这一段序列贡献小于零，那么把他丢掉再从当前位置开始扫描一定是更优的。由于我们不知道答案在何处取得，所以在内层扫描时去一个最大值即可。

### 核心代码

```cpp
//为了代码简洁略去无关片段，只放了求最大值的部分。
int n,a[MAX];
void solve()
{
	cin>>n;
	fo(i,1,n)
		cin>>a[i];
	int sum=0,maxs=0;
	fo(i,1,n)
		sum+=a[i];
	maxs=sum;
	int i=1,j=1;
	for(i=1;i<=n;)
	{
		int d=0;
		for(j=i;j<=n;j++)
		{
			if(a[j]==0)
				d++;
			else
				d--;
			maxs=max(maxs,sum+d);
			if(d<0)
				break;
		}
		i=j+1;
	}
}
```

[AC 记录](https://www.luogu.com.cn/record/191605489)

[^1]: 感性理解就是多选一个数或少选一个数带来的改变恰好是加减一的，所以能恰好覆盖整个最小值到最大值的部分。
[^2]: 求最小值就是反过来。
[^3]: 即最长的，左右两边不能扩展或再扩展一个就会造成贡献为负的序列。参考极大连通子图中“极大”的定义。

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_arc137_b)

首先可以发现：

- 如果原来的数为 $1$，经过反转操作后会减 $1$，记作 $-1$。

- 如果原来的数为 $0$，经过反转操作后会加 $1$，记作 $+1$。

所以，样例就成了：$+1$ $-1$ $-1$ $+1$。

所以，这个问题就是：只有 $1$ 和 $-1$ 的数组内，区间和有多少种不同的数。可以算出最大与最小字段的区间和，就是答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin >>n;
	int a[n+1],b[n+1];
	b[0]=0;//每次b[i]都要先赋成b[i-1]的值，当i=1是i-1是0，所以要先把b[0]赋为0 
	for(int i=1;i<=n;i++){//循环n次 
		cin >>a[i];//输入 
		b[i]=b[i-1];//先赋值为上一个 
		if(a[i]==1){//1
			b[i]-=1;//-1
		}else{//0
			b[i]+=1;//+1
		}
	}
	int ans=0,ma=0,mi=0;//ans是答案，s是b[i]和mi差最大的时的值，mi是b此时遍历到的值的最小值 
	for(int i=1;i<=n;i++){//循环n次
		ma=max(ma,b[i]-mi);//取b[i]-mi和ma的最大值 
		mi=min(mi,b[i]);//取b[i]和mi的最小值 
	}
	ans+=ma;//答案加上最大的 
	ma=0;//重新赋成0 
	mi=0;//重新赋成0
	for(int i=1;i<=n;i++){
		mi=min(mi,b[i]-ma);//取b[i]-ma和mi的最小值
		ma=max(ma,b[i]);//取b[i]和ma的最大值 
	}
	ans-=mi;//答案减去最小的
	cout<<ans+1<<endl;//输出，AT要加换行 
	return 0;
}
```

---

## 作者：DDF_ (赞：0)

## 题面

给定一个 $0,1$ 数组，需要进行一次操作：选定一段连续区间（可以选空区间），进行取反。

求数组中 $1$ 的个数有多少种取值。

## 题解

首先，设 $ans$ 为操作后数组中 $1$ 的个数。那么就有一个结论：$ans$ 的取值范围肯定是一段连续的正整数。

因为假设你取了一段区间 $[l,r]$，无论你下次取 $[l-1,r]$、$[l+1,r]$、$[l,r-1]$ 还是 $[l,r+1]$，都会对 $ans$ 产生 $1$ 的影响。

所以我们可以想到，求 $ans$ 取到的最大值 $ansmx$ 和最小值 $ansmn$，那么 $ans$ 的取值的数量就为 $[ansmn,ansmx]$ 的元素个数。

如何求这个值？

考虑到每次多取一个数就会对 $ans$ 产生 $1$ 的影响，所以可以定义数组 $s$，$s_i$ 为取 $a_i$ 对答案造成的影响，那么 $s_i$ 是由 $1$ 或 $-1$ 组成的。

那么就可以找区间和最大的 $s$ 区间，与区间和最小的 $s$ 区间。

所以可以想到前缀和。

用前缀和维护区间和最大值和最小值不多赘述。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,mx,mn;
int ansmx,ansmn;
int main() {
	scanf("%d",&n);
	for(int i=1,a;i<=n;i++) {
		scanf("%d",&a);
		sum+=a?-1:1;
		ansmx=max(ansmx,sum-mn);
		ansmn=min(ansmn,sum-mx);
		mx=max(mx,sum),mn=min(mn,sum);
	}
	printf("%d",ansmx-ansmn+1);
	return 0;
}
```

---

## 作者：_czy (赞：0)

### 题意

有一个 $01$ 数组，你可以任选一个连续的子段取反，$1$ 的数量的取值有几种可能

### 分析

容易发现：如果将 $0$ 取反，则 $1$ 的数量加 $1$；如果将 $1$ 取反，则 $0$ 的数量减 $1$。并且稍微思考得到：$1$ 的数量的取值是一个连续的区间，我们可以通过最大值与最小值求可能数。

### 过程

将原数组转换成一个由 $1,-1$ 组成的数组，然后求最大、最小子段和。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300003
int n,a[N],mx1,mn1,mx2,mn2;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		a[i]=a[i-1]+(a[i]==0?1:-1);
	}
	for(int i=1;i<=n;i++){
		mx1=max(mx1,a[i]-mn2),
		mn1=min(mn1,a[i]-mx2);
		mx2=max(mx2,a[i]),
		mn2=min(mn2,a[i]);
	}
	printf("%d",mx1-mn1+1);
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你一个数组，可以对他进行一次操作，使得选中的区间里的数反转，求一次操作后可以让序列中 $1$ 的个数有多少种可能。

## 解题思路

它问我们有多少种可能，就是再问我们一次操作后 $1$ 的最大次数与 $1$ 的最小次数的差，这可以简单证明一下。怎么求？这不就是最大子区间和与最小子区间和的差，把 $0$ 看成 $-1$，把 $1$ 看成 $1$，再用一个前缀和数组就可以解决这个问题了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n;
int a[N], sum[N];
int max1, max2;
int min1, min2;
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == 0) sum[i] = sum[i - 1] - 1;
        if(a[i] == 1) sum[i] = sum[i - 1] + 1;
    }
    for(int i = 1; i <= n; i++) {
        max1 = max(max1, sum[i] - min2);
        min1 = min(min1, sum[i] - max2);
        max2 = max(max2, sum[i]);
        min2 = min(min2, sum[i]);
    }
    cout << max1 - min1 + 1;
    return 0;
}
```

---

## 作者：CarlosLiu (赞：0)

## 题意描述
给你一个只有 $0$ 和 $1$ 构成的序列。现在，你可以选序列的一个连续的子段（可以为空），做一个将其中的 $0$ 变为 $1$ 而 $1$ 变为 $0$ 的操作。将你的分数定义为最后 $1$ 的个数。让你输出你有多少种可能的得分。
## 解题思路
显然，不操作的得分就是一开始 $1$ 的个数。在这个的基础上，你改变一个 $0$ 会使分数加一，否则就减一。我们设 $b _ {i}$ 为这样的正一负一的值。最后分数的增加就是子段中 $b _ {i}$ 之和。

我们设这个子段是从 $i$ 到 $j$ 的。如果我们把 $sum _ {i}$ 记为 $\sum _ {k=i} ^ {j} b _ {k}$ 的值，那么 $sum _ {j}-sum _ {i-1}$ 就是分数的增加。我们可以提前分别算出 $sum _ {1}$ 到 $sum _ {i}$ 中最大和最小的，这样把 $j$ 从 $1$ 到 $n$ 遍历一遍，就能求出最大和最小增加值。

但是，最大最小值之间的每个值都能取到吗？是的！！！我们将子段增加或减去一个数，增加值加一或减一。将取到最小值的子段逐步调到取到最大值的子段的过程中，可以取到最大最小值之间的每个值。

综上，就可以得到答案了。
## 代码
```
#include<bits/stdc++.h>
int n,a[300009],b[300009],sum[300009];
int max[300009],min[300009],ans1,ans2;
int main() {
	std::cin>>n;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		b[i]=1-2*a[i];
		sum[i]=sum[i-1]+b[i];
		if(max[i-1]<sum[i]) max[i]=sum[i];
		else max[i]=max[i-1];
		if(min[i-1]>sum[i]) min[i]=sum[i];
		else min[i]=min[i-1];
	}
	for(int i=1;i<=n;i++) {
		if(ans1>sum[i]-max[i]) ans1=sum[i]-max[i];
		if(ans2<sum[i]-min[i]) ans2=sum[i]-min[i];
	}
	std::cout<<ans2-ans1+1;
	return 0;
}
```


---

