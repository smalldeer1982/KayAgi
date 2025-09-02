# 数列分段 Section II

## 题目描述

对于给定的一个长度为 $N$ 的正整数数列 $A_{1\sim N}$，现要将其分成 $M$（$M\leq N$）段，并要求每段连续，且每段和的最大值最小。

关于最大值最小：

例如一数列 $4\ 2\ 4\ 5\ 1$ 要分成 $3$ 段。

将其如下分段：

$$[4\ 2][4\ 5][1]$$

第一段和为 $6$，第 $2$ 段和为 $9$，第 $3$ 段和为 $1$，和最大值为 $9$。

将其如下分段：

$$[4][2\ 4][5\ 1]$$

第一段和为 $4$，第 $2$ 段和为 $6$，第 $3$ 段和为 $6$，和最大值为 $6$。

并且无论如何分段，最大值不会小于 $6$。

所以可以得到要将数列 $4\ 2\ 4\ 5\ 1$ 要分成 $3$ 段，每段和的最大值最小为 $6$。


## 说明/提示

对于 $20\%$ 的数据，$N\leq 10$。

对于 $40\%$ 的数据，$N\leq 1000$。

对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$M\leq N$，$A_i < 10^8$， 答案不超过 $10^9$。


## 样例 #1

### 输入

```
5 3
4 2 4 5 1```

### 输出

```
6```

# 题解

## 作者：浅色调 (赞：327)

###本题解法：二分答案+贪心###

**思路：**首先，分析题目，求最大值的最小化，直接联想到二分，So我们直接二分答案，关键是要怎么去高效的check，我看了大家基本上使用了前缀和，但实际上这个空间是可以省略的，为什么呢？我们考虑一个贪心的思路，能加的就加上，不能则新开一段，so对于二分的值x，我们从数列a从前往后扫，如果tot大于了x，我们不加而是tot重新赋值并且num++，最后只需判断num是否不小于m就行了。这样判断与前缀和一样是O(n)的复杂度，但是节省了空间且容易思考。

**注意：**二分时的区间取值问题，很明显，对于l的赋值应该取数列中的最大值，而r应该取数列的总和。(亲测，如果l赋值为0或1，第4个点会wa)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],l,r,mid,ans;
inline bool check(int x)
{
    int tot=0,num=0;
    for(int i=1;i<=n;i++)
    {
        if(tot+a[i]<=x)tot+=a[i];
        else tot=a[i],num++;
    }
    return num>=m;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),l=max(l,a[i]),r+=a[i];
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid))l=mid+1;
        else r=mid-1;
    }
    cout<<l;
    return 0;
}
```

---

## 作者：thoq (赞：255)

如果你不知道什么是二分答案，请先看其他题解，而我想借此题谈谈二分答案的本质，并发散思维，得到一些新的算法。

个人认为，二分答案由“二分”和“答案”组成。宏观上，二分，是对问题状态空间的一种遍历方式，主要作用是降低时间复杂度；答案，即枚举答案，则是一种解题方法，主要作用是化求解为判定，降低难度。

具体来讲：

- 答案。在此题中，我们首先要确定答案的范围。显然，答案最小可能是数列中的最大值（记为 $l$ ），最大可能是所有数的和（记为 $r$）。其次，我们发现，给出一个解，判定这个解是否合法，在此题中显得简单。这启示我们用枚举答案再判定的方法解决此题。

- 二分。二分建立在答案的基础上。此题中答案的排布，是有一定规律的，即，存在一个分界点 $p$，使得 $\left[l,p\right)$中的数都是非法解，$\left[p,r\right]$中的数都是可行解。而 $p$ 即为所求的最小解。这种性质启示我们用一种特定的方法来枚举答案，于是有了二分。

很多人便能够写出以下程序：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 100010;
int n,m,a[N];
bool check(int k)
{
	int cur=0,ans=1;
	for(int i=1;i<=n;i++)
	{
		if(cur+a[i]>k)
		{
			cur=0;
			ans++;
		}
		cur+=a[i];
	}
	return ans<=m;
}
int main()
{
	scanf("%d%d",&n,&m);
	int l=0,r=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		r+=a[i];
		l=max(l,a[i]);
	}
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```
至此，还没有结束。我们可以创新吗？

关于答案，这是此题的基本解决方式，似乎无从下手；而二分，只是枚举答案的一种方式，我们还可以换其他方式，比如，直接枚举。
```cpp
	for(int i=l;i<=r;i++)
		if(check(i))
		{
			printf("%d\n",i);
			return 0;
		}
```
重复部分不再贴出。此代码 TLE60 分，因为枚举的方式过于朴素。不过，这很好体现了答案思想，更让我们思考，还有什么遍历状态空间（此题中体现为枚举答案）的方式呢？

有啊，比如倍增。
```cpp
	int p=1,j=r;
	while(p)
	{
		int k=j-p+1;
		if(k>=l&&check(k))
		{
			ans=k;
			j-=p;
			p*=2;
		}
		else p/=2;
	}
```
此代码 AC，时间复杂度和二分答案相同，不妨称之“倍增答案”。倍增答案几乎能完成所有二分答案的题，但为什么没有广泛使用呢？大概是二分更好写吧。

---

## 作者：Jezemy (赞：91)

这是一道二分题，主要的特点在于提到了“最大值最小”

基本思路是先不考虑分段次数，从最小的和枚举到最大的和，看哪个和满足指定分段次数m相等

**最小的和**：全部都分段，此时最小和为max(arr)

**最大的和**：只分一段，此时最大和为sum(arr)

其实可以在最小和和最大和直接直接遍历，但是为了加速，使用二分查找

对于left mid right分段的左右区间，有三种情况，若

**分段数 > 指定分段次数** ， 说明指定的和太小，应该让和大点，才能让分段次数少点，因此进入右区间left = mid + 1

**分段数 = 指定分段次数** ， 此时分段数刚刚好，若是从小到大遍历，可直接退出，
但是倘若是二分查找，得继续往左区间看有没有更小的分段次数满足要求，因此right = mid -1

**分段数 < 指定分段次数** ， 说明此时指定的和太大，导致分段数太少，因此要让和小一点，因此进入左区间，right = mid -1

综合三种情况就有

当 **分段数>指定分段次数，进入右区间**

当 **分段数<=指定分段次数，进入左区间**

以下为代码

其中，check函数的作用在于给定一个和MaxSum，在数组arr中找到根据该给定和可以分成多少组，最后将最后分得组数和指定组数m做对比，然后指导下一步操作。

```python
def check(maxSum, arr, m):
	# cnt初始化为1是因为若直接进入循环，cnt实际上漏算了最后一个分组
	Sum, cnt = 0,1
	for num in arr:
		if Sum + num <= maxSum:
			Sum += num
		else:
			Sum = num
			cnt += 1
	return cnt > m

if __name__ == '__main__':
	n, m = [int(i) for i in input().split()]
	arr = [int(i) for i in input().split()]
	left = max(arr)
	right = sum(arr)
	# 从最大值和全部值的和做二分
	while left <= right:
		mid = (left + right) // 2
		if check(mid, arr, m):
			left = mid + 1
		else:
			right = mid - 1
	print(left)
```


---

## 作者：Awdrgysxc (赞：57)

这题还是有点意思的，看都好多人的check都和蒟蒻的有点不同
### 【分析】

首先我们看到题目求每段和的最大值最小，可以考虑二分，分每段和。
因为涉及区间之和，我们可以用前缀和来维护
```cpp
scanf("%d%d",&n,&m);
    for(int i = 1;i <= n; i++)
    {
        int x;
        scanf("%d",&x);
        sum[i] = sum[i-1] + x;
    }
```
我们不难得出$R = sum[n]$ $L = sum[1]$

注意：第一个数并不一定是最小的，但在非负的情况下$sum[1]$
一定是最小的

#### 二分：
```cpp
while(L <= R)
    {
        Mid = (L + R) >> 1;
        if(check(Mid)) Ans = Mid,R = Mid - 1;
        else L = Mid + 1;
    }
```
现在的问题就是check函数怎么写

好多人都是从1枚举到n, 看看在这些数里满足每段和的最大值小于等于mid最少分几段，再与$m$比较一下；蒟蒻还有一种方法:
#### 【详见代码】
```cpp
inline bool check(int mid)
{
    int Pos = 0,Cnt = m,Tmp = 1;
    //先定义一个Pos表示当前的位置，一定要初始0
    //Cnt表示m种
    //Tmp表示走到哪里
    while(Cnt--)
    {
        while(sum[Tmp] - sum[Pos] <= mid && Tmp <= n) Tmp++;
        //如过这个区间和<=mid&&tmp不超过n
        //下一个数加进来
        Pos = --Tmp;
        //这里一定要-1
        if(Pos == n) return 1;
        //如果在m >= 0是就到了n，这说明了mid大于等于答案
        //所以ans = mid,R = mid - 1;
    }
    return 0;
}
```
这会有点难理解，大家认真想想。

这种方法理论上说是会快一些。
### 【代码】
```cpp
#include <cstdio>
#include <iostream>
#define reg register 
#define min(x,y)(x<y?x:y)

using namespace std;

const int M = 100010;
int n,m,sum[M],Ans,Mid,R,L;

inline int read() {
	reg int ret=0;reg bool flag=0;reg char c=getchar();
	while((c<'0')|(c>'9')) flag^=!(c^'-'),c=getchar();
	while((c>='0')&(c<='9')) ret=(ret<<3)+(ret<<1)+(c^'0'),c=getchar();
	return flag?-ret:ret;
}

inline bool check(int mid)
{
    int Pos = 0,Cnt = m,Tmp = 1;
    while(Cnt--)
    {
        while(sum[Tmp] - sum[Pos] <= mid && Tmp <= n) Tmp ++;
        Pos = --Tmp;
        if(Pos == n) return 1;
    }
    return 0;
}

int main(void)
{
    n = read(),m = read();
    for(int i = 1;i <= n; i++)
    {
        int x = read();
        sum[i] = sum[i-1] + x;
    }
    L = sum[1];
    R = sum[n];
    while(L <= R)
    {
        Mid = (L + R) >> 1;
        if(check(Mid)) Ans = Mid,R = Mid - 1;
        else L = Mid + 1;
    }
    printf("%d",Ans);
    return 0;
}
```

---

## 作者：蹲在丛中笑 (赞：52)

大家二分的打法都好传统啊

鉴于我是一个蒟蒻，二分的边界常常打错，所以就主动放弃了l和r

而是从int的32位一位位判能否取到

————————————————————————

也就是 二分的还是每一段和的最大值

如果得出能在m段以内取光所有数，就说明还能取得更小

最后把答案+1就可以了

```cpp
#include<stdio.h>
#define N 100005
int n,m,ans,a[N];
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=30;i>=0;i--) {
        for(int j=1,k=1;j<=m;j++) {
            for(int t=0;t+a[k]<=ans+(1<<i)&&k<=n;k++) t+=a[k];
            if(k>n) goto Next;
        }
        ans+=1<<i;
        Next:;
    }
    printf("%d\n",ans+1);
}
```
（其实这么打主要是因为代码短）


---

## 作者：最喜欢saber了 (赞：51)

[题目传送门](https://www.luogu.org/problemnew/show/P1182)

这道题我用的方法是二分答案，（但我太弱了，还是做了很久）
首先我来介绍一下二分答案吧，（因为我太弱了，所以我用了一年的时间才弄懂）。

比如我们要从一本英汉词典上查一个单词，如果你从头到尾一页一页的翻着找（并仔细一点），这样找可以保证一定能找到，但是最坏情况你要把整本词典都翻一遍，那就麻烦了（而且很累）。

有什么改进的方法吗？当然有。

我们考虑把这个词典从中间分开，看一下中间那一页的主要单词都是啥，然后去判断我要找的单词应该在左半部分还是右半部分，再去那一部分考虑怎么找就好了。同样的，在另一部分也是要进行划分并且判断的操作。这样一直进行下去，便能很快的找到答案，而且根本不需要翻过整个词典来。

可以证明，如果一页一页的找，最多要找 $n$ 次，但是用这个方法，最多找$floor(log2n)$次。

我们把这个方法叫做“二分答案”。顾名思义，它用二分的方法枚举答案，并且枚举时判断这个答案是否可行。但是，二分并不是在所有情况下都是可用的，使用二分需要满足两个条件:

1.有上下界

2.区间有单调性


二分答案应该是在一个单调闭区间上进行的。也就是说，二分答案最后得到的答案应该是一个确定值，而不是像搜索那样会出现多解。二分一般用来解决最优解问题。刚才我们说单调性，那么这个单调性应该体现在哪里呢？

可以这样想，在一个区间上，有很多数，这些数可能是我们这些问题的解，换句话说，这里有很多不合法的解，也有很多合法的解。我们只考虑合法解，并称之为可行解。考虑所有可行解，我们肯定是要从这些可行解中找到一个最好的作为我们的答案， 这个答案我们称之为最优解。

最优解一定可行，但可行解不一定最优。我们假设整个序列具有单调性，且一个数x为可行解，那么一般的，所有的 $x'(x'<x)$ 都是可行解。并且，如果有一个数y是非法解，那么一般的，所有的 $y'(y'>y)$ 都是非法解。

那么什么时候适用二分答案呢？注意到题面：使得选手们在比赛过程中的最短跳跃距离尽可能长。如果题目规定了有“最大值最小”或者“最小值最大”的东西，那么这个东西应该就满足二分答案的有界性（显然）和单调性（能看出来）。

(以上内容感谢一位dalao的帮助)

好，下面来切入正题：

首先，我们来确定一下上下界，

我们定义$l$ ,$r$为区间的两端点，由于要求每段的最大值的最小值，所以 $l $应该取所有数中最大的那个（想想这是为什么），而 $r$ 是不是只能是区间和了。

那么我们的judge函数该怎么写呢？

我写的这个judge函数我刚开始也没怎么理解。。。（我太弱了） 这里的judge函数其实意思就是：在a数组内，能否满足每组的和比x小。如果是，返回0；否，返回1。

于是献上代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cctype>
#include<cstdlib>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &x){//模板输入输出优化
    x=0;T f=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
    for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
    x*=f;
}
template<typename T>inline void write(T x){
    if(x<0)putchar('-'),x*=-1;
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
const int maxa = 1e5+10;
int n,m,tot,now,a[maxa],l=0,r=0,mid;
inline bool judge(int x){//据某位叫x的dalao的观点，内联函数要快一点
	for(int i=1;i<=n;++i){//这里大家应该看得出，
                          //这个操作是在用贪心来看一看这个最大值是否能为x
		if(tot+a[i]<=x)tot+=a[i];
		else tot=a[i],now++;
	}
	if(now>=m)return true;
	else return false;
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;++i){
		read(a[i]);
		l=max(a[i],l);//l为区间最大数
		r+=a[i];//累加求r
	}
	while(l<=r){//二分模板
		mid=(l+r)>>1;
		tot=0,now=0;
		if(judge(mid))l=mid+1;
		else r=mid-1;
	}
	write(l);
	return 0;//完成！！！
}
```

欢迎dalao纠错。
谢谢观看，请记住，我太弱了。

---

## 作者：zhaowangji (赞：47)

**注意**：凡是题目里出现要求“最大值最小”或“最小值最大”（或者是解读题意后发现），那么一般使用**二分答案**

二分答案的写法有很多模板，但使用的情况各不相同

```cpp
while(l<r)
{
    int mid=(l+r)>>1;
    if(check(mid))
        r=mid;
    else
        l=mid+1;
}

```
这是最大值最小

```cpp
while(l<r)
{
    int mid=(l+r+1)>>1;
    if(check(mid))
        l=mid;
    else
        r=mid-1;
}

```
这是最小值最大

```cpp
while(l+1<r)
{
   int mid=(l+r)>>1;
  if(check(mid))
  		l=mid;
  else r=mid;
             
```
我们老师说上面这种方法可以涵盖所有的情况，可实际使用起来却不尽如人意（至少这道题是的）

（其实check函数因为是自己写的，所以if与else后面跟者的语句可以变换，但是赋值应该不可以改）

因为题目中说“每段和最大值最小为多少”故使用模板一
```cpp
#include<iostream>
using namespace std;
int n,m;//题目
int a[100007];//n<=100000
int kl,kr=1e9+1,km;//即l，r，m
//kl下面会改，kr是因为Ai之和不超过10^9
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],kl=max(kl,a[i]);
        //l至少为所有元素中最大的值
	while(kl<kr)//最上面那个模板
	{
		km=(kl+kr)/2;//即>>1
        	//km代表当前假设的答案，用它去试
		int sum=0,tot=0;//sum是每段的和，tot是段数
		for(int i=1;i<=n;i++)
		{//枚举每一个数
			if(sum+a[i]<=km)sum+=a[i];
            		//不用重新分段，就加进去
			else sum=a[i],tot++;
            		//分一段，合变为当前数，段数加一
		}
		if(tot<m)kr=km;//段数少，说明数太大，要改小一点（注意是<，因为如果=可能还有更优的答案）
		else kl=km+1;//模板
	}
	cout<<kl<<endl;//最后kl是答案
	return 0;    
}
```


---

## 作者：wancong (赞：29)

## 本题数据范围有误

这题非常水，注意查找区间的控制。我这个题解重点不讲思路，而是

### 指出本题的一个漏洞：数据范围有误。

思路大佬们都说过了，每次猜测一个答案，即可行区间的最中间，当合法（也就是分的段数小于等于规定段数）时，可以继续减小；否则应当增大。不过，这个和二分查找不完全相同。

区间之和可以用前缀和来描述。`sum[i] += sum[i - 1];`

这样，由于每一项都是非负，sum数组是单调递增（严格说是非单调递减）的。因此，我们在找不大于某个和的某一段时，可以使用upper_bound。

开始是这样写的：

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int sum[100001];

int main()
{
    int k, l, r, mid, n, i, cnt, tmp = 0;
    scanf("%d %d", &n, &k);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &sum[i]);
        if (sum[i] > tmp) tmp = sum[i];
        sum[i] += sum[i - 1];
    }
    l = tmp, r = sum[n];
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        tmp = cnt = 0;
        i = 1;
        while (cnt <= k && i <= n)
        {
            i = upper_bound(sum + i, sum + n + 1, tmp + mid) - sum;
            tmp = sum[i - 1];
            cnt++;
        }
        if (cnt > k) l = mid + 1;
        else r = mid;
    }
    printf("%d", r);
    return 0;
}
```

但是，很奇怪的，WA第五个点。下载了一下，这个点真有100000个整数。

借助Clion（~~不是打广告~~，但jetbrains的IDE真的做得很好）强大的调试功能，我尝试观察sum的元素，发现竟然出现了负值！很明显，int溢出了。因此，在查找的过程中，upper_bound出现了问题。

全部改成long long就过了：

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

long long sum[100001];

int main()
{
    int k, n, i, cnt;
    long long tmp = 0, l, r, mid;
    scanf("%d %d", &n, &k);
    for (i = 1; i <= n; i++)
    {
        scanf("%lld", &sum[i]);
        if (sum[i] > tmp) tmp = sum[i];
        sum[i] += sum[i - 1];
    }
    l = tmp, r = sum[n];
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        tmp = cnt = 0;
        i = 1;
        while (cnt <= k && i <= n)
        {
            i = upper_bound(sum + i, sum + n + 1, tmp + mid) - sum;
            tmp = sum[i - 1];
            cnt++;
        }
        if (cnt > k) l = mid + 1;
        else r = mid;
    }
    printf("%lld", r);
    return 0;
}
```

而调试器告诉我，这组数据所有整数之和大约是$2.5*10^9$，这说明，**题目中数据范围限制：$ΣAi <= 10^9$是有问题的，恳请出题组改正一下！**

另外，我还尝试了不用upper_bound的做法：

```cpp
tmp = cnt = 0;
i = 1;
while (cnt <= k && i <= n)
{
    while (i <= n && sum[i] - tmp <= mid) i++;
    tmp = sum[i - 1];
    cnt++;
}
```

发现这样也能AC！这是因为，二进制减法的基本性质！即使被减数和减数超int，只要差不超int，则结果依然正确。~~了解一下就好了，要是仔细解释，可以写三大张纸了~~(\*╹▽╹\*)。

原来，数据范围限制$ΣAi <= 10^9$的意思是，保证每段之和小于10^9啊！这题不走心哦！

### 最后再次提醒出题人，最好修改一下，否则会误导大众，出现不明WA也无处下手！

---

## 作者：Heartlessly (赞：24)

## 算法解析

- 本题主要考察二分答案的运用，我呢加了一点前缀和，跑一遍 36ms，应该是最优解。答案的区间为数列中数的** 最大值 ~ 总和 **。第 4 个点的确比较坑，不需要像楼下一样特判，只要区间正确就能过。

## 示例代码

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n, m, x, f[100001], p, l, r, mid, sum, ans, maxn;//f数组前缀和，sum为分割数列的段数，ans为最终答案，maxn为数列中的最大值
int main(){
    scanf ( "%d %d", &n, &m );
    for ( int i = 1; i <= n; i++ )
    scanf ( "%d", &x ), f[i] = f[i-1] + x, maxn = max ( maxn, x );//前缀和与找出最大值
    l = maxn, r = f[n];//定义二分的区间
    while ( l <= r ){
        mid = ( l + r ) >> 1;//二分套路不解释
        p = 1, sum = 1;//初始就有1段，p为当前分段位置
        for ( int i = 2; i <= n; i++ ){
            if ( f[i] - f[p-1] > mid )//如果第i~p-1个数的和大于mid
            p = i, sum++;//当前位置为i，段数+1
        }
        if ( sum > m ) l = mid + 1;//如果段数大于m，搜后半段
        else r = mid - 1, ans = mid;//符合要求，把mid赋值给ans，搜前半段
    }
    printf ( "%d\n", ans );//输出答案
    return 0;
} 
```

---

## 作者：野鹤 (赞：22)

这道题呢，从“最大值最小”可以~~很明显~~的看出这是一道**二分答案**的题

先说一下二分吧，二分就好比猜数的游戏，你猜一个数字，对方告诉你是大还是小，从而确定下一个猜的数字是猜比刚才猜的数字大还是小，相比于枚举来说大大缩短了时间，提高了效率。

二分答案呢具有两个性质：最大值最小或最小值最大以及单调性。

二分答案呢就是先把你的mid**假装**当成真正的答案，然后再用check函数检查一下合法不合法，从而改变边界，具体的下面的代码里会说。

首先是主函数：
```cpp
int main(){
    cin>>n>>m;//输入
    cin>>a[1];
    ll r,l=0;
    sum[1]=a[1];
	for(int i=2;i<=n;i++){
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
		l=max(l,a[i]);
	}
    r=sum[n];
     //一个前缀和方便check函数里面的求和，确定左边界和右边界。
	while(l<=r){
		ll mid=(l+r)/2;
		if(check(mid))
			l=mid+1;//如果合法说明比mid大的数都合法，左边界右移。
			else r=mid-1;//如果不合法说明比mid大的数都不合法，右边界左移。
	}
    //一个二分的板子。
	cout<<l;
	return 0;
} 
```
下面是check函数：

```cpp
bool check(ll mid){
	int now=0;//现在遍历到了第几个数。
	int t=0;//计数器。
	for(int i=2;i<=n;i++){
		if(sum[i]-sum[now]>mid){
			t++;
			now=i-1;
      //如果此区间的和比mid值大了，为了保持mid值的合法性，把i-1作为此区间的末尾数。
		}
     //i是本区间的末尾数。
	}
	if(t>=m)return true;//如果最后分的区间大于等于了要分的区间，说明mid合法继续二分。
	else return false;//反之便不合法。
}
```

AC代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
ll n,a[1000001],m,sum[100001];
bool check(ll mid){
	int now=0;
	int t=0;
	for(int i=2;i<=n;i++){
		if(sum[i]-sum[now]>mid){
			t++;
			now=i-1;
		}
	}
	if(t>=m)return true;
	else return false;
}


int main(){
    cin>>n>>m;
    ll r,l=0;
    cin>>a[1];
    sum[1]=a[1];
	for(int i=2;i<=n;i++){
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
		l=max(l,a[i]);
	}
	r=sum[n];
	while(l<=r){
		ll mid=(l+r)/2;
		if(check(mid))
			l=mid+1;
			else r=mid-1;
	}
	cout<<l;
	return 0;
} 
```
其实这道题~~一点也不难~~，易错点可能在左边界的初始值取错了，要取这个数列中的最大数的值。


---

## 作者：King_Han (赞：6)

“最大值的最小值”或“最小值的最大值”。明显的二分答案。

主要难度是在写一个check函数，显然这题比较水用不着前缀和这种高端的东西。~~就算写了也还是O（n），快不了多少。~~

注释见代码

```
#include<bits/stdc++.h>//万能库是个好东西
using namespace std;
int n,m,maxx=0,low,hih,mid;
int a[100005];
inline bool check(int x)//检查分组要求是否合法 
{
	int grp=1;//一开始所有数构成一个组 
	maxx=0;
	for(int i=1;i<=n;i++)
	{
		if(maxx+a[i]<x)//只要区间和小于答案就加上a[i]否则分组加1，开始计算下一个区间的和 
		{
			maxx+=a[i];
		}
		else
		{
			grp++;
			maxx=a[i];
		}
	}
	if(grp>m)
		return 0;//此时分好的组大于要求的组，证明现在的答案太小了，所以要找右半区 
	else
		return 1;//此时分好的组小于等于要求的组，证明现在的答案太大了，所以要找左半区 
}
inline void devide(int l,int r)//用递归的形式二分，当然while也可以 
{	
	mid=(l+r)/2;
	if(l+1>=r)
		return;//二分边界 
	else
	{
		if(check(mid)==1){
			devide(l,mid);//意义见check函数注释 
		}
		else{
			devide(mid,r);
		}
	}
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;//数据很小cin完全可以 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		low=max(low,a[i]); 
		hih+=a[i];
		/*我们知道，二分答案的前提是答案要满足单调性，对于题意，显然答案区间肯定是在
		这个数组的最大值到整个数组的和之间的，这个区间也显然满足单调递增。故将左边界
		设为这个数组的最大值，将右边界设为整个数组的和，这样就可以二分了！*/ 
	}
	devide(low,hih);
	printf("%d",mid);//此时mid就是答案，因为二分区间到最后肯定有且仅有一个元素在l和r之间。 
	return 0;//再见:)
}
```

---

## 作者：QLUjyroooy (赞：6)

这个题时一个典型的二分答案（最大的最小、最小的最大）

　　首先根据题意，我们确定段的最大值一定在整个数组的最大值和10^9之间，因此做如下定义

　　　l = maxn, r = 1000000000; 
　　然后我们确定好一个mid = （l+r）>> 1，表示最大值为mid时是否可行；

　　下面就进行二分的正常过程，判断

　　然后遍历整个数列，记录下一个tot，表示这个数列中最大值不超过mid时，需要分成的段数，用now来代表当前段的和

 

　　now+a[i]<mid时：可以继续加，这个段还没有结束

　　now+a[i]==num时：说明当前段已经达到了最大值，记下这个段（tot++），now=0，以便分析下一个段

　　now+a[i]>num时：说明这个段加上a[i]之后超过mid，就不能加上这个a[i]，那么这个段已经计算完（tot++），a[i]算到下一个段内

　　

　　如果tot<m,说明要达到当前的段数m，mid的值必须要降低，这样才能使段数增多，收缩右边界；

　　否则，改变左边界。
  
  
  ```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN=100001;
int maxn = -1;
int n, m, a[1000010];
int l = maxn, r = 1000000000;
int judge(int num){
    int now = 0;
    int tot = 0;
    for(int i=1;i<=n;i++){
        if(now+a[i]<num){
            now += a[i];
        }
        else if(now+a[i]==num){
            now = 0;
            tot++;
        }
        else if(now+a[i]>num){
            now = a[i];
            tot++;
        }
    }
    if(now) tot++;  //如果还有剩余的一个值，那么这个单独算一个段
    if(tot>m)return 0;
    else return 1;
    
}

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        maxn = max(a[i], maxn);
    }
    int l = maxn, r = 1000000000;     
    if(n==m){
        cout << maxn;
        return 0;
    }
    while(l<r){
        int mid = (l+r) >> 1;
        if(judge(mid)==1){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    cout << r;
    return 0;
}
```

---

## 作者：Deny_小田 (赞：6)

本题是一个典型的二分。

数组开大点不要钱！开小了会抓狂！

二分结果，然后最后输出二分的较大值。

废话不多说，上代码：





    

```cpp
#include <stdio.h>
#include <stdbool.h>
#define Size 1000001      //别开小了，建议和我一样
int A[Size],n,m; 
bool IsOK(int m);
int main(){
    int i,u = -Size,r = 0,Mid;        //u是最小的，r是最大的 
    scanf("%d %d",&n,&m);
    for(i = 0; i < n; i++){
        scanf("%d",&A[i]);
        r += A[i];
        if(A[i] > u) u = A[i];
    }
    while(1){
        if(r == u) break;
        Mid = (r+u)/2;
        if(IsOK(Mid) == true) r = Mid;
        else u = Mid+1;
    }
    printf("%d\n",r);
    return 0;
}
bool IsOK(int mi){
    int i,s = 0,p = 1;
    for(i = 0; i < n; i++){
        if(s+A[i] > mi){
            s = A[i];
            p++;
        }
        else s += A[i];
    }
    if(p > m) return false;
    else return true; 
}
```

---

## 作者：ylsoi (赞：4)

典型的二分答案（关键句最大的最小。。。最小的最大。。。。）

但是很多人WA了第四个点（其实我一开始也WA了），主要是因为对于二分答案的临界值没有判断的好，我们可以当左边和右边相邻的时候判定它结束，然后在输出的时候再做一次判定

代码如下

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn=100000+10;
int n,m,a[maxn];
bool find(int now)
{
    int s=0,r=1;//r是划分的段数，所以要从1开始（相当于植树问题啦）
    for(int i=1;i<=n;i++)
    {
        s+=a[i];
        if(s>now)
        {
            s=a[i];
            r++;
        }
    }
    if(r>m)return false;
    return true;
}
int main()
{
    int sum=0,left=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        left=max(left,a[i]);
        sum+=a[i];
    }
    int right=sum;
    while(left+1<right)//这里就是判断相邻的时候！！
    {
        int mid=((left+right)/2);
        if(find(mid))right=mid;
        else left=mid;
    }
    if(find(left))printf("%d",left);//因为我们不知道在相邻的时候，谁是可以的，又因为要尽量地取最小值，所以要从左边开始判断
    else printf("%d",right);
    return 0;
}
```

---

## 作者：FHXZ (赞：4)

贪心加二分。。。

最大值最小类问题基本上就是用二分，所以很容易想到二分答案并检验

但由于细节问题还是WA了不少次。。。

直接上代码~

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
int n,m,a[10000000],l,r;
int maxx=0;
int sum=0;
int check(int x)
{
    int now=0;
    int tot=0;
    for (int i=1;i<=n;i++)
    {
        if(now+a[i]<x)
        {
            now+=a[i];
        }
        else if(now+a[i]==x)
        {
            now=0;
            tot++;
        }
        else if(now+a[i]>x)
        {
            now=a[i];
            tot++;
        }
    }
    if(now)
    tot++;
    if(tot>m) return 0;
    else return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {scanf("%d",&a[i]);
    sum+=a[i];
    maxx=max(maxx,a[i]);}
    if(n==m)
    {printf("%d",maxx);
    return 0;}
    else
    {
         l=maxx,r=sum;
        while(l<r)
        {
            int mid=(l+r)>>1;
            if(check(mid)==1)
            r=mid;
            else l=mid+1;
        }
    }
    printf("%d\n",r);
    return 0;
}
```

---

## 作者：qzcbw (赞：3)

#### 请看题目：

#### P1182 数列分段`Section II`

时间限制: 1 Sec  内存限制: 128 MB

#### 题目描述

对于给定的一个长度为N的正整数数列A−i，现要将其分成M(M≤N)段，并要求每段连续，且每段和的最大值最小。 

#### 关于最大值最小： 

例如一数列4 2 4 5 1要分成3段 

将其如下分段： 

[4 2][4 5][1] 

第一段和为6，第2段和为9，第3段和为1，和最大值为9。 

将其如下分段： 

[4][2 4][5 1] 

第一段和为4，第2段和为6，第3段和为6，和最大值为6。 

并且无论如何分段，最大值不会小于6。 

所以可以得到要将数列4 2 4 5 1要分成3段，每段和的最大值最小为6。 

#### 输入

第11行包含两个正整数N，M。 

第22行包含N个空格隔开的非负整数Ai，含义如题目所述。 

#### 输出

一个正整数，即每段和最大值最小为多少。 

#### 样例输入

5 3

4 2 4 5 1


#### 样例输出

6

#### 提示

对于20%的数据，有N≤10； 

对于40%的数据，有N≤1000； 

对于100%的数据，有N≤100000, M≤N,Ai之和不超过10^9。 

题目看好了吗？  没看好 ~~滚~~ 上去看。

### 题目分析

算法：二分算法

所以说，

如果你不会二分，就 ~~别看我的题解~~ 先去学。

好了，步入正题。

首先，我们要输入。 （废话）

输入中可以确定左指针与右指针的位置。

```cpp
scanf("%d%d",&n,&k);

    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        r+=a[i];
        if(a[i]>l)
        l=a[i];    
}
```

接下来，我们打一个二分的框架。

~~（不会打的别看了）~~  我在下面会讲。

```cpp
while(l<=r)

    {
        m=l+(r-l)/2;
        t=0,tot=0;
        if(judge(m))l=m+1;//缩小范围
        else r=m-1;
}
```


有人会问，函数judge里是什么呢？

我当然会讲（不讲写这题解干嘛）

### 重点（敲黑板）：

```cpp
inline bool judge(int x){
    for(int i=1;i<=n;i++){
        if((t+a[i])<=x)
        t+=a[i];
        else{
            t=a[i];
            tot++;
        }
    }
    return tot>=k;
}
```

让我们逐步分析！

第一行就不用解读了吧。

第二行，循环，找到分段的数量。

```cpp
for(int i=1;i<=n;i++){
```

接下来，判断。
```cpp
if((t+a[i])<=x)
t+=a[i];
else{
     t=a[i];
     tot++;
}

```


#### 如果这个段落里还可以塞数据，我们就塞。

#### 如果塞不进去，就将计数器加一，把段落清空，重新塞。

#### 塞完了就判断是否达到段落要求，达到了就返回。

```cpp
return tot>=k;
```


最后输出。

（不贴代码了）

（还是贴一下吧）

^o^

#### AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int l,r,m;
long long t,tot,a[10000001];
inline bool judge(int x)
{
    for(int i=1;i<=n;i++)
	{
        if((t+a[i])<=x)
		t+=a[i];
        else{
        	t=a[i];
			tot++;
		}
    }
    return tot>=k;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
	{
        scanf("%d",&a[i]);
        r+=a[i];
        if(a[i]>l)
        l=a[i];    
	}
    while(l<=r)
	{
        m=l+(r-l)/2;
        t=0,tot=0;
        if(judge(m))l=m+1;
        else r=m-1;
    }
    printf("%d",l);
    return 0;
}
```

#### 附录：二分框架分析

（这里把变量定得明确一些）

```cpp
while（left<=right)
    {
        mid=left+(right-left)/2;//也可以用(left+right)/2，这里用left+(right-left)/2纯属喜好，都是求中点数值。
        if(judge(mid))left=mid+1;
        else right=mid-1;
}
```

(left表示左指针，right表示右指针，中点为mid)

我们先取中点，然后判断所要求的数值所在的范围，

如果合法，说明数值可能在中点右边，将左指针移至当前中点。

如果不合法，说明数值可能在中点左边，将右指针移至当前中点。

继续判断直到左指针大于等于右指针，就得出所求答案了。

是不是很简单？ ^o^

#### 谢谢——qzhwcbw


---

## 作者：封禁用户 (赞：3)

简单的二分题，二分时的最大值是所有数的和，最小值是所有数里最大的数，这样可以减少时间复杂度，最后的答案要加一。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
//============================================
int N,M,sum,Max,a[100005];
//============================================
void init();
void work();
bool judge();
//============================================
bool judge(int mid)
{
   int summ=0,key=1;
   for(int i=1;i<=N;i++){
      if( summ+a[i]<=mid )summ+=a[i];
      else{
         summ=a[i];
         key++;
      }
   }
   if(key>M)return true;
   else return false;
}
//============================================
void init()
{
   cin>>N>>M;
   for(int i=1;i<=N;i++){
      cin>>a[i];
      sum+=a[i];
      Max=max( Max , a[i] );
   }
}
//============================================
void work()
{
   int high=sum,low=Max,mid;
   mid=(high+low)/2;
   while(low<=high){
      //printf("%d\n",mid);
      if( judge(mid)==true )
         low=mid+1;
      else
         high=mid-1;
      mid=(high+low)/2;
   }
   printf("%d",mid+1);
}
//============================================
int main()
{
   init();
   work();
   //system("pause");
   return 0;
}
```

---

## 作者：神之右大臣 (赞：2)

给大家普及一个知识，只要看到最大值最小或最小值最大等字样就往二分上想吧！

然后是正解部分：
   我们可以二分答案；
   对于每次二分的区间取中间值mid，并对其进行check()判断；
   如果所有段的最大值为mid时可以分成m段(注意，如果此时分成的段比m还小，那么也是可行的，因为你可以随便拆拆就能拆成m段，但显然可能不是最优的解),那么我们就将二分区间更改为(l,mid)，因为(mid+1,r)区间所有的答案均可行且都不是最优的。否则将区间改为(mid+1,r);
   
 另外说明一下,二分的退出条件是l==r，并记录ans等于此时的r。
 然后输出ans就好了
   ```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[100010],sum[100010];
int ans;
bool check(int x)
{
	for(int i=1;i<=n;i++){
		if(sum[i]-sum[i-1]>x){
			return 0;
		}
	}
	int tmp=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(sum[i]-tmp>x){
			tmp=sum[i-1];
			++cnt;
			i--;
		}
	}
	if(cnt+1>m)  return 0;
	return 1;
}
void erfen(int l,int r)
{
	if(l==r){
		ans=l;
		return;
	}
	int mid=(l+r)/2;
	if(check(mid)) erfen(l,mid);
	else erfen(mid+1,r);
}
int main ()
{	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	erfen(1,sum[n]);
	cout<<ans;
}
```


---

## 作者：Ryan_ (赞：2)

~~写个水题题解水估值~~

这题是一道最简单的二分答案题

但第一次交只有80分  第四个点没过（看讨论区好像挺多卡在#4的）

最后发现一个细节，即二分的左端点为所有数字的最大值 正确性易证

相关习题：Best Cow Fences（poj2018）

AC代码：
```
//把n个数分成m组，每组长度之和<=size,是否可行
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100001],sum;
bool valid(int size){
	int group=1,rest=size;
	for(int i=1;i<=n;i++){
		if(rest>=a[i])rest-=a[i];
		else group++,rest=size-a[i];
	}
	return group<=m;
}
int main(){
	//二分答案，判定“每组长度不超过二分的值”时
   //能否在m组内把书分完
	cin>>n>>m;
	int maxn=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		maxn=max(maxn,a[i]);
	}
	int l=maxn,r=1<<30;
	while(l<r){
		int mid=(l+r)>>1;
		if(valid(mid))r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}

```


---

## 作者：封禁用户 (赞：2)

//本人第一次写关于二分答案的题解，各位大佬请原谅题解的各种问题

同样是二分，其实没必要多此一举

下面的大佬写得太复杂了

我的好像短一些

我的思路是这样的：

题目要求我们把给出的数据进行分段

我们只需要二分每段的最大值，

再算出如果按这个最大值，能分出几组

如果比题目给出的m大，就将二分的范围缩小到前半段

如果小过m，就将二分的范围变为后半段

注意：

1、二分的范围是从max（a[i]）~ a[i]~a[n]的和

2、算组数时，最后要加1，因为最后就算远远不够最大值，也得分一组

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
long long n,m,r,s,g,x[1000000],l,mid;
int main()
{
    cin>>n>>m;//输入n和规定组数m 
    for (int i=1;i<=n;i++)
    {scanf("%d",&x[i]);r+=x[i];l=max(l,x[i]);}//确定两个指针的值 
    while (l+1<r)//当两个指针没有挨在一起时，进行二分答案 
    {
        mid=(l+r)/2;g=0;s=0;//取两个指针的中间值，注意将组数和部分和清零 
        for (int i=1;i<=n;i++) 
        {
            if (x[i]>mid) {l=mid;continue;}
            //如果x[i]本来就大于mid，跳过循环
            //其实如果在 max（a[i]）~ a[i]~a[n]范围内二分，写不写都可以 
            if (g+x[i]>=mid) s++,g=x[i]; else g+=x[i];
            //如果部分和变量加上x[i]大于等于mid，组数加一，并把g赋值为x[i]，否则加上x[i] 
        }
        if (g>0) s++;//上面说过，因为最后就算远远不够最大值，也得分一组，所以还得加一 
        if (s<=m) r=mid; else l=mid;
        //如果组数不够，说明最大值太小，所以要增大，否则减少 
    }
    cout<<l;//输出l其实就是输出被设为最大值的mid 
    return 0;
}
```

---

## 作者：骑着肥猪飙 (赞：2)

虽然很水，但是调了好长时间；


注意：

1. 二分边界l=max(a[i]),r=sum(a[i]);

如果l=0 or 1；

对于 ：

5 2
1 2 3 7897979 4；

答案不会是7897979！！！！！

卡了我半年！！！！！


还有一个小细节，check时，可能最后剩下几个数加起来不到x，但组数也要加，所以加一个特判；

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,l=1,r,a[200001];
bool check(int x)
{
    int tot=0,sum=0;
    for(int i=1;i<=n;i++)
    {
        if(sum+a[i]>=x) tot++,sum=0;
        sum+=a[i]; 
    }
    if(sum) tot++;//判断是否有多余的数没统计；
    if(tot>m) return true;//x不够大，增大x；
    else return false;//tot=m时，由于让max尽量小，所以尽量减小x；
}
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),r+=a[i];
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<l;
}
int main()
{
    solve();
    return 0;
}
```

---

## 作者：doby (赞：2)

结合木材加工和切绳子一起学习效果更佳……

二分，可是有一点小问题……

```cpp
#include<cstdio>
using namespace std;
int n,m,a[100009],l,r=0,mid,sum,ans,maxx=0;
int cheak(int s)
{
    sum=0,ans=0;//这一部分仿照数列分段1……
    for(int i=1;i<=n;i++)
    {
        sum=sum+a[i];
        if(sum>s){ans++,sum=a[i];}
    }
    ans++;
    if(ans>m){return 1;}//切多了，mid可以更大
    else{return 0;}//否则变小一点
}
int main()
{
    freopen("divide_b.in","r",stdin);
    freopen("divide_b.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>maxx){maxx=a[i];}
        r=r+a[i];
    }
    l=maxx;
    if(m==n){printf("%d",l);return 0;}//简单的规律
    while(l+1<r)//二分
    {
        mid=(l+r)/2;
        if(cheak(mid)){l=mid;}
        else{r=mid;}
    }
    if(!cheak(r-1)){printf("%d",r-1);return 0;}//往小的答案再搜寻一下……
    printf("%d",r);//输出
    return 0;
}
```

---

## 作者：SiTer (赞：2)

```cpp

//2015-10-10 21:36
/*
洛谷1182 数列分段Section II
本题地址： http://www.luogu.org/problem/show?pid=1182

题目描述
对于给定的一个长度为N的正整数数列A[i]，现要将其分成M（M≤N）段，并要求每段连续，且每段和的最大值最小。
关于最大值最小：
例如一数列4 2 4 5 1要分成3段
将其如下分段：
[4 2][4 5][1]
第一段和为6，第2段和为9，第3段和为1，和最大值为9。
将其如下分段：
[4][2 4][5 1]
第一段和为4，第2段和为6，第3段和为6，和最大值为6。
并且无论如何分段，最大值不会小于6。
所以可以得到要将数列4 2 4 5 1要分成3段，每段和的最大值最小为6。
输入输出格式
输入格式：
输入文件divide_b.in的第1行包含两个正整数N，M，第2行包含N个空格隔开的非负整数A[i]，含义如题目所述。

输出格式：
输出文件divide_b.out仅包含一个正整数，即每段和最大值最小为多少。

输入输出样例
输入样例#1：
5 3
4 2 4 5 1
输出样例#1：
6
说明
对于20%的数据，有N≤10；
对于40%的数据，有N≤1000；
对于100%的数据，有N≤100000，M≤N， A[i]之和不超过10^9。
*/

/*
一开始以为是爆搜 不过一看数据很显然不可能了 
然后就是二分
其实就是白书上的猜数字游戏
假设将N个数字分成M段 段落最大和为ans
很明显我们要求的就是最小的ans
虽然我们现在不知道最小的ans等于多少 但我们可以判断一个数是大于最小的ans还是小于最小的ans
因为这个最小的ans是一个边界 
如果一个数Y比最小的ans小 那么这个数就不能将N个数字分成段落最大和为Y的M段
（因为分完了M段以后 会有剩余数字没分例如将） 
如果一个数Y比最小的ans大 那么这个数就可以将N个数字分成段落最大和为Y的M段
函数 judge 为判断Y比ans小还是大（判断规则如上面两句话的后半部分）  小返回-1大返回1 
我们设置一个范围：A到B  （A=1 B=1000000）
mid=(A+B)/2 =500000
如果 judeg（mid）=-1 
那么很显然最小的ans就在mid+1（500001）到B（1000000）的范围里 
那么就更新A=mid+1；
 judeg（mid）=1则反之
 直到A=B A即为所求 
*/
#include <cstdio>
#include <iostream>
using namespace std;
int N,M;
long long Map[100010];
int judge(int num){
    int begin=1;
    for(int i=1;i<=M;i++)
    {
        int temp=0;
        for(int j=begin;j<=N-M+i;j++,begin++)
        {
            temp+=Map[begin];
            if(temp>num) break;
        }
    }
    return begin > N ? 1 : -1 ;
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
        scanf("%I64d",&Map[i]);
    int up=1000000000,down=1;
    while(1)
    {
        if(up == down) break ;
        int mid=(up+down)/2;
        judge(mid) == -1 ? down=mid+1 : up=mid ;
    }
    printf("%d",up);
    return 0;
}


```

---

## 作者：YanjunchenEdward (赞：2)

**[color=purple]首先感谢xyf、lxc帮我复习了二分答案！谢谢~[/color]**

这是一题很经典的二分，主要问题就是如何解决[u]“最大的最小”[/u]。由于本题数据很大，所以就别想着爆搜了。二分答案会非常快。代码来了！

```delphi

var
  a:array[0..10000000] of longint;
  n,m,so,shi,sum,sum1,m1,tr,s1:int64;//实验证明longint会爆
  i:longint;
procedure divide(mi,ma:int64);//开始二分，这里int64别忘了
var
  t1,t2,mid:int64;//还有这里
begin
  if mi=ma then begin writeln(mi); halt; end;//找到正解
  t1:=0; t2:=0;
  mid:=(mi+ma) div 2;//取中间值作为假设的答案
  for i:=1 to n do begin
    t1:=t1+a[i];//累加
    if t1>mid then begin//如果当前数列已经大于答案
      t1:=a[i]; inc(t2);//不能再放了，必须分一组
    end;
  end;
  inc(t2);//这个别忘了，因为最后还有一组
  if t2<=m then divide(mi,mid);//如果分组数小于规定分组数，说明答案太大了
  if t2>m then divide(mid+1,ma);//反之，答案偏小
end;
begin
  readln(n,m);
  for i:=1 to n do begin
    read(a[i]); sum:=sum+a[i];//记录答案最大值
    if a[i]>s1 then s1:=a[i];//最小不是0，而是本数列的最大值
  end;
  divide(s1,sum);
end.


```

---

## 作者：一碗粥 (赞：2)

题解君来也！rn首先，第一反应是枚举（爆搜），but我写的连样例都要等2秒钟。。。瞬间没希望了，于是老老实实地去写二分了。rn二分的话，很明显就是二分答案了，其实这题也不会很难，仅仅是二分这种方法比较难想到。rn整个程序的步骤就是：先读入，找到一个最大的数，再计算一下总和，l=最大数；r=总和，这样二分的话能够大大地减小时间复杂度，就没有必要从1到maxlongint了。rn这里有一个小技巧，怎样计算一共要分多少段？可以去参见数列分段Section I

标程：

```cpp
var
 l,r:int64;
 i,j,k,m,n:longint;
 a:array[1..100000] of longint;
function search(k:int64):int64;
var
  i:longint;
  t,ans:int64;
begin
  t:=a[1]; ans:=1;
  for i:=2 to n do
  if t+a[i]>k then
  begin
    t:=a[i];
    inc(ans);
   end
  else
  t:=t+a[i];
  search:=ans;
end;
begin
  read(n,m);
  for i:=1 to n do begin
  read(a[i]);
  if a[i]>l then l:=a[i];
  r:=r+a[i];
 end;
 while l<r do
 begin
  if search((l+r) div 2)<=m then
   r:=(l+r) div 2
  else l:=(l+r) div 2+1;
 end;
 write(l);
end.

```

---

## 作者：Ghost_lzy (赞：2)

二分答案，然后前m-1次用尺取法，如果前m-1次走到n那么第m个是没法尺取下去了，最后判断第m个是否走到了n（这句话很绕，不管他）

，复杂度为nlogn，数据规模4\*1e6左右.(最好写，建议如果时间松用这个)

还有种做法，nloglogn,预处理前缀和，二分答案，如上，然后再二分前缀和位置，数据规模可以到5\*1e6.（前缀和要特判n=3）

还有更牛逼的O(n)做法，不再过多介绍，自行思考，做题用以上两个就行了。

我为了好写,nlogn.

  
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m;
int a[100005],ub,lb=0,mid;
bool C(int mid)
{
    int now=1,sum=0;
    for(int i=1;i<m;i++)
  {
    while(a[now]+sum<=mid&&now<=n)
    {
        sum+=a[now];now++;
    }now--;
    if(now==n) return true;
    sum=0;now++;
  }
    while(a[now]+sum<=mid&&now<=n)
    {
        sum+=a[now];now++;
    }now--;
    if(now==n) return true;
    return false;
}
int main()
{   
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ub+=a[i];
    }
    while(ub-lb>1)
    {
        mid=(lb+ub)/2;
        if(C(mid)) ub=mid;
        else lb=mid;
    }
    if(C(lb)) printf("%d",lb);
    else printf("%d",ub);
}
```
/\*
10
2 5 1 4 7 3 6 2 5 1

9
1 1 5 1 1 1 5 1 1

\*/

---

## 作者：mool (赞：1)

####     敲完看了题解很多聚聚说l不能设置0,1，但自己代码里面就用的0和上界1e9啊，也能跑过。 我思路同样是二分答案，对于每一个check的x，从左往右依次加上当前位置上的权值啊a[i],以tmp记录，如果大于了x，则tmp减去当前权值a[i]，并新开一段存储之前的和（也就是tmp），然后将tmp设置为当前a[i],继续往右。同理跑一遍从右往左。连续的分段，要么从左往右两个合在一起，要么从右往左合在一起。然后判断左右两种情况是否满足最大值小于x。

请大佬指正为何l不能为0，qaq。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n,m;
int a[maxn];
int judge(int x){
    int ans1, ans2;
    ans1 = ans2 = -maxn;
    int tmp = 0;
    int l = 0, r = 0;//分别记录顺序和逆序的分段数
    for (int i = 0; i < n;i++){
        tmp += a[i];
        if (tmp>x){
            ++l;
            tmp -= a[i];
            ans1 = max(ans1, tmp);
            tmp = a[i];
        }
    }
    tmp = 0;
    for (int i = n - 1; i > -1; i--)
    {
        tmp+=a[i];
        if (tmp > x)
        {
            ++r;
            tmp -= a[i];
            ans2 = max(ans2, tmp);
            tmp = a[i];
        }
    }
    ++l, ++r;
    return ((l <= m && ans1 <= x) || (r <= m) && ans2 <= x);
}
int main(int argc, char const *argv[])
{
    cin >> n >> m;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    int l = 0, r = 1e9;
    while(l<r){
        int mid = l+r >> 1;
        // cout << l << " " << r<<"\n";
        if (judge(mid))
            r = mid;
        else
        {
            l = mid+1;
        }
    }
    cout << l;
    return 0;
}
```



---

## 作者：Mosklia (赞：1)

##			 一波很诡异的TLE？！
个人感觉二分这个东西楼下，楼下的楼下，楼下的楼下的楼下...已经讲得很好了，此处无需复述

本人主要就是讲一下遇到的一点小小问题，希望对大家有所帮助

本人第一次提交的代码是这个样子的：
（似乎并没有什么问题啊）
```cpp
#include<iostream>
using namespace std;
const int maxn = 100000 + 5;
unsigned long long a[maxn], s[maxn], m, n;
bool test(unsigned long long val){
	int l = 0, r = 1, res = 1;
	while(r <= n){//贪心求连续段数
		if(s[r] - s[l] > val){
			res++;
			l = r - 1;
			continue;
		}
		r++;
	}
	if(res > m) return false;
	return true;
}
int main(){
	cin>> n>> m;
	for(int i = 1; i <= n; ++i){
		cin>> a[i];
		s[i] = a[i] + s[i-1];
	}
	unsigned long long le = 1, re = s[n] + 1, mid = (le + re)>>1;
	while(le < re - 1){//二分不多讲
		if(test(mid)){
			re = mid;
			mid = (le + re)>>1;
		}
		else{
			le = mid;
			mid = (le + re)>>1;
		}
	}
	cout<< re;
	return 0;
}
```
结果交上去。。。
#1 AC, #2 TLE, #3 AC, #4 TLE, #5 AC

其实有一个错误很明显：

对于以下一组数据：

3 2

1 100 1

第一次进入test函数时val的值为51，结果会一直卡在第8~12行，从而TLE。

其正确的做法是加上一行“if(a[r] > val) return false;”

因为如果数列中有一个数大于传入的val，那么无论如何分段最终最大段的值都不可能小于等于val。

从而正确的程序如下：
```cpp
#include<iostream>
using namespace std;
const int maxn = 100000 + 5;
unsigned long long a[maxn], s[maxn], m, n;
bool test(unsigned long long val){
    int l = 0, r = 1, res = 1;
    while(r <= n){
        if(a[r] > val) return false;//注意这里
        if(s[r] - s[l] > val){
            res++;
            l = r - 1;
            continue;
        }
        r++;
    }
    if(res > m) return false;
    return true;
}
int main(){
    cin>> n>> m;
    for(int i = 1; i <= n; ++i){
        cin>> a[i];
        s[i] = a[i] + s[i-1];
    }
    unsigned long long le = 1, re = s[n] + 1, mid = (le + re)>>1;
    while(le < re - 1){
        if(test(mid)){
            re = mid;
            mid = (le + re)>>1;
        }
        else{
            le = mid;
            mid = (le + re)>>1;
        }
    }
    cout<< re;
    return 0;
}
```
希望对大家有所帮助

---

## 作者：Mr_Wolfram (赞：1)

这是一道典型的二分答案问题（最大值最小，最小值最大）关键是对于细节的处理。

二分的框架：


```cpp
//l=max{num[i]},r=sum{num[i]}
while(l<=r){
        int m=(l+r)>>1;
        if(chk(m)){
            r=m-1;
        }else l=m+1;
    }
    cout<<l;
```
二分的框架是普遍使用的，关键是检验函数的设计，此处的检验函数的含义为： 是否存在一种合法的划分，使得每段的最大值都不大于m。

设计好了检验函数，就要思考l与r的转移:若存在这种合法的划分，说明m偏大，r=m-1;反之，l=m+1.

此处应注意l的初始值为num中的最大值。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int read(){
    int rv=0,fh=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') fh=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        rv=(rv<<1)+(rv<<3)+c-'0';
        c=getchar();
    }
    return fh*rv;
}
int n,m,num[100005],pre[100005];
bool chk(int x){
    int tot=0,last=0;
    for(int i=1;i<=n;i++){
        if((pre[i]-pre[last])>x){
            tot++;
            last=i-1;
        }
    }
    tot++;
    if(tot<=m) return 1;
    else return 0;
} 
int main(){
    freopen("in.txt","r",stdin);
    n=read();m=read();
    int l=1,r,m=0;
    for(int i=1;i<=n;i++){
        num[i]=read();
        l=max(l,num[i]);
        pre[i]=pre[i-1]+num[i];
    }    
    r=pre[n];
    while(l<=r){
        int m=(l+r)>>1;
        if(chk(m)){
            r=m-1;
        }else l=m+1;
    }
    cout<<l;
    int t;
    fclose(stdin);
    return 0;
}

```



---

## 作者：wowowo！ (赞：1)

### 一道二分答案，比较基础，思路就是先按照套路找中间点，从1~n循环，total（我用来累加的）加上a[i]<=mid的话就加进去否则就分组数++。

```cpp
#include<cstdio>
using namespace std;
int tmp,total,tot,ans,mid,l,r,minn=0,a[100001],n,m; 
bool pd(int t)
{
    tmp=0;
    total=0;
    for (int i=1;i<=n;i++)
    {
        if (total+a[i]<=t)
          total+=a[i];
        else
        {
          tmp++;
          total=a[i];
        }
    }
    if (tmp+1<=m)//这里需要特别注意，tmp需要加1
      return true;
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
      scanf("%d",&a[i]);
      if (minn<a[i])
        minn=a[i];
      tot+=a[i];
    }
    l=minn;r=tot;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (pd(mid))
          r=(ans=mid)-1;
        else
          l=mid+1;
    }
    printf("%d",ans);
}
```

---

