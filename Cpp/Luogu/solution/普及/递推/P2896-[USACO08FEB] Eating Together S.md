# [USACO08FEB] Eating Together S

## 题目描述

The cows are so very silly about their dinner partners. They have organized themselves into three groups (conveniently numbered 1, 2, and 3) that insist upon dining together. The trouble starts when they line up at the barn to enter the feeding area.

Each cow i carries with her a small card upon which is engraved Di (1 ≤ Di ≤ 3) indicating her dining group membership. The entire set of N (1 ≤ N ≤ 30,000) cows has lined up for dinner but it's easy for anyone to see that they are not grouped by their dinner-partner cards.

FJ's job is not so difficult. He just walks down the line of cows changing their dinner partner assignment by marking out the old number and writing in a new one. By doing so, he creates groups of cows like 111222333 or 333222111 where the cows' dining groups are sorted in either ascending or descending order by their dinner cards.

FJ is just as lazy as the next fellow. He's curious: what is the absolute mminimum number of cards he must change to create a proper grouping of dining partners? He must only change card numbers and must not rearrange the cows standing in line.

FJ的奶牛们在吃晚饭时很傻。他们把自己组织成三组（方便编号为1, 2和3），坚持一起用餐。当他们在谷仓排队进入喂食区时，麻烦就开始了。


每头奶牛都随身带着一张小卡片，小卡片上刻的是Di（1≤Di≤3）表示她属于哪一组。所有的N（1≤N≤30000）头奶牛排队吃饭，但他们并不能按卡片上的分组站好。


FJ的工作并不是那么难。他只是沿着牛的路线走下去，把旧的号码标出来，换上一个新的。通过这样做，他创造了一群奶牛，比如111222333或333222111，奶牛的就餐组按他们的晚餐卡片按升序或降序排列。


FJ就像任何人一样懒惰。他很好奇：怎样他才能进行适当的分组，使得他只要修改最少次数的数字？由于奶牛们已经很长时间没有吃到饭了，所以“哞哞”的声音到处都是，FJ只好更换卡号，而不能重新排列已经排好队的奶牛。


## 说明/提示

感谢@一思千年 提供翻译


## 样例 #1

### 输入

```
5
1
3
2
1
1
```

### 输出

```
1
```

# 题解

## 作者：程雅馨 (赞：14)

$\color{blue}\text{蓝色蒟蒻从哥哥那里得来一个简单的优化办法（表述有些问题请原谅）}$

在题目中可以得出：

只用找一次最长不上升序列
再找一次最长不下降序列
记录下长度
用总数减去较大的那个就好了

代码也很简单：
```
#include<iostream>
#include<cmath>
using namespace std;
int n,s,a[30005],f[30005],f1[30005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]>=a[j])
			f[i]=max(f[i],f[j]);
		}
		f[i]++;
	}//最长不下降序列
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]<=a[j])
			f1[i]=max(f1[i],f1[j]);
		}
		f1[i]++;
	}//最长不上升序列
	for(int i=1;i<=n;i++){
		s=max(s,f[i]);
		s=max(s,f1[i]);
	}//取最长
	cout<<n-s;
	return 0;
}
```
$\color{blue}\text{但是就这样交上去会超时}$

仔细观察（也不用很仔细）
就能发现卡片上的数字只有$1 2 3$，重复率非常高

于是
可以将内层倒序循环
如果找到数字相同那么前面就不用找了
因为前面已经处理过了

```
#include<iostream>
#include<cmath>
using namespace std;
int n,s,a[30005],f[30005],f1[30005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]>=a[j])
			f[i]=max(f[i],f[j]);
			if(a[i]==a[j])break;//前面已经被处理过可以跳过
		}//内层倒序循环
		f[i]++;
	}//最长不下降序列
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]<=a[j])
			f1[i]=max(f1[i],f1[j]);
			if(a[i]==a[j])break;
		}
		f1[i]++;
	}//最长不上升序列
	for(int i=1;i<=n;i++){
		s=max(s,f[i]);
		s=max(s,f1[i]);
	}
	cout<<n-s;
	return 0;
}
```
补一句：

这个方法最长不上升序列、最长不下降序列、最长上升序列、最长下降序列都可以用，但数据重复率较高的效果更明显一些。

---

## 作者：奶酥奶酥QwQ (赞：14)

每次可以改变一个数字，要求使给定的数列变成单调递增或递减，求最小操作数

分析，显然，这个有两个任务，

1.变成单调递增所需操作

2.变成单调递减所需操作

比较一下就是结果。


考虑任务一：在分析后不难发现修改LIS上的数字是不划算的。

证明：设数列An，LIS为数列$Ai$…$Aj$…$Ak$任务目标是生成一个长度为n的LIS。

情况1：修改非LIS上数字

不难想到，无论修改那个数字都有方法使LIS程度增加1，并且此题最多一次操作能使LIS程度增加1，所以修改非LIS上数能得到更优。

情况2：修改LIS上的数字

如果修改LIS上一个数字能使LIS更优，则必定存在一个和这个LIS等长的LIS，将那个视为LIS即回到情况1


任务二和任务一类似，不再赘述。


这样此题便成为求$n-max(LIS,LDS)$

再次回到此题数据范围，不难看出动态规划解法的不足，可以用基于二分查找的求法得到$O(log n)$解法。


基于二分查找的LIS 解法。

纪录各个长度LIS最后的数字大小。显然，最后一个数字小比最后一个数字大更优，设$Ax$为当前查找的项，若$Ax$如果比所有的LIS的大小都大，则可以得到更长的LIS。把$Ax$成为更长的LIS的最后一个数字。

否则，利用二分查找找到以$Ax$结尾的LIS。


注意，这里的二分查找是upper\_bound


代码实现如下

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<cstdlib>
using namespace std;
const int maxn = 300000;
int A[maxn],f1[maxn],f2[maxn];
int main()
{
    int n;scanf("%d",&n);
    for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
    int cnt = 1;f1[cnt] = A[1];
    for(int i = 2;i <= n;i++){
        if(A[i] >= f1[cnt]){
            f1[++cnt] = A[i];
        }else
            *upper_bound(f1+1,f1+cnt+1,A[i]) = A[i];
    }
    int ans = cnt;
    cnt = 1;f2[cnt] = A[1];
    for(int i = 2;i <= n;i++){
        if(A[i] <= f2[cnt]) f2[++cnt] = A[i];
        else *upper_bound(f2+1,f2+1+cnt,A[i],greater<int>()) = A[i];
    }
    printf("%d\n",n-max(ans,cnt));
    return 0;
} 
```

---

## 作者：Priori_Incantatem (赞：9)

这题很像那个[P2837 晚餐队列安排](https://www.luogu.org/problem/P2837)，只不过这题的$D_i$是$1$~$3$

设$f[i][j]$为当第$i$头牛的编号为$j$时，让$1$~$i$这个序列合法需要的最少操作次数


每次取最优值是，只用考虑它前面的一个元素就好了，因为考虑前面的那个元素时已经让序列合法并且方法最优了

**考虑让序列升序排列的最优方案：**
```cpp
if(a[i]==1)
{
	f[i][0]=f[i-1][0];//前面的数只能为1
	f[i][1]=min(f[i-1][1],f[i-1][0])+1;//把第i个元素改为2，然后考虑前面为1或为0的最优值，后面都是同理
	f[i][2]=min(f[i-1][2],min(f[i-1][0],f[i-1][1]))+1;
}
if(a[i]==2)
{
	f[i][0]=f[i-1][0]+1;
	f[i][1]=min(f[i-1][1],f[i-1][0]);
	f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]))+1;
}
if(a[i]==3)
{
	f[i][0]=f[i-1][0]+1;
	f[i][1]=min(f[i-1][0],f[i-1][1])+1;
	f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]));
}
```

降序排列也是同理，只是代码上稍微有些改动

### AC代码：

```cpp
#include<cstdio>
#include<cstring> 
const int Maxn=30000+10;
int a[Maxn],f[Maxn][3];
int n,ans;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int min(int x,int y)
{
	return x>y?y:x;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	for(int i=1;i<=n;++i)
	{
		if(a[i]==1)
		{
			f[i][0]=f[i-1][0];
			f[i][1]=min(f[i-1][1],f[i-1][0])+1;
			f[i][2]=min(f[i-1][2],min(f[i-1][0],f[i-1][1]))+1;
		}
		if(a[i]==2)
		{
			f[i][0]=f[i-1][0]+1;
			f[i][1]=min(f[i-1][1],f[i-1][0]);
			f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]))+1;
		}
		if(a[i]==3)
		{
			f[i][0]=f[i-1][0]+1;
			f[i][1]=min(f[i-1][0],f[i-1][1])+1;
			f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]));
		}
	}
	ans=min(f[n][0],min(f[n][1],f[n][2]));
	memset(f,0,sizeof(f));
	for(int i=n;i>=1;--i)
	{
		if(a[i]==1)
		{
			f[i][0]=f[i+1][0];
			f[i][1]=min(f[i+1][1],f[i+1][0])+1;
			f[i][2]=min(f[i+1][2],min(f[i+1][0],f[i+1][1]))+1;
		}
		if(a[i]==2)
		{
			f[i][0]=f[i+1][0]+1;
			f[i][1]=min(f[i+1][1],f[i+1][0]);
			f[i][2]=min(f[i+1][0],min(f[i+1][1],f[i+1][2]))+1;
		}
		if(a[i]==3)
		{
			f[i][0]=f[i+1][0]+1;
			f[i][1]=min(f[i+1][0],f[i+1][1])+1;
			f[i][2]=min(f[i+1][0],min(f[i+1][1],f[i+1][2]));
		}
	}
	ans=min(min(ans,f[1][0]),min(f[1][1],f[1][2]));
	printf("%d\n",ans) ;
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：7)

#### Description

给定一个序列 $D[i]$，求至少需要改变多少个位置的值使得这个序列为不严格上升序列或不严格下降序列。

#### Solution

算法 $1$：因为要求修改一些数使得序列为上升或者下降序列，所以我们可以计算除了上升或者下降之外的数的最小值。

所以考虑计算一个序列的不连续不严格最长上升子序列和不连续不严格最长下降子序列，假设上升的长度为 $k_1$，下降的长度为 $k_2$，答案为：

$$n-\max\{k_1,k_2\}$$

因为要求答案最小，所以要减去的 $k_1$ 或者 $k_2$ 的值就要最大。

求 LIS 和 LDS 可以采用 $O(n^2)$ 的做法，但会 T 一个点。

```cpp
// wsq AK IOI, hope me to AC

#include <bits/stdc++.h>

using namespace std;

int d[30086];
int dp1[30086];
int dp2[30086];

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);
	// LIS
	int LiS = 0;
	for (int i = 1; i <= n; i++) {
		int Max = 0;
		for (int j = 1; j < i; j++)
			if (d[j] <= d[i])
				Max = max(Max, dp1[j]);
		dp1[i] = Max + 1;
		LiS = max(LiS, dp1[i]);
	}
	// LDS
	int LdS = 0;
	for (int i = 1; i <= n; i++) {
		int Max = 0;
		for (int j = 1; j < i; j++)
			if (d[j] >= d[i])
				Max = max(Max, dp2[j]);
		dp2[i] = Max + 1;
		LdS = max(LdS, dp2[i]);
	}
	// ANS
	printf("%d", n - max(LiS, LdS));
	return 0;
}
```

算法 $2$：二分优化，略。

算法 $3$：因为 $D_i\in\{1,2,3\}$，所以我们考虑升维，先以 LIS 为例子进行分析。

假设我们第 $i$ 位要改成 $k$，或这位就是 $k$ 我们不改，使得这个这个序列为 LIS 当且仅当第 $i-1$ 位小于等于 $k$，所以状态转移的第一部分就是 $\min\{dp[i - 1][p]\}(1 \le p \le k)$，后面一部分要进行分类讨论，如果 $d[i]\ne k$，即这一位不是 $k$ 要修改，那么就要加 $1$。

这种做法适用于 $D_i$ 非常小，我们就可以得到如下的状态转移方程：

$$dp[i][k]=\begin{cases}k=1,dp[i-1][1]+[d[i]\ne 1]\\k=2,\min\{dp[i-1][1],dp[i-1][2]\}+[d[i]\ne 2]\\k=3,\min\{dp[i-1][1],dp[i-1][2],dp[i-1][3]\}+[d[i]\ne 3]\end{cases}$$

LDS 同理，可以直接看代码。

```cpp
// wsq AK IOI, hope me to AC

#include <bits/stdc++.h>

using namespace std;

int d[30086];
int dp1[30086][4];
int dp2[30086][4];

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);
	for (int i = 1; i <= n; i++) {
		dp1[i][1] = dp1[i - 1][1] + int(d[i] != 1);
		dp1[i][2] = min(dp1[i - 1][1], dp1[i - 1][2]) + int(d[i] != 2);
		dp1[i][3] = min(dp1[i - 1][1], min(dp1[i - 1][2], dp1[i - 1][3])) + int(d[i] != 3);
	}
	int LiS = min(dp1[n][1], min(dp1[n][2], dp1[n][3]));
	for (int i = 1; i <= n; i++) {
		dp2[i][3] = dp2[i - 1][3] + int(d[i] != 3);
		dp2[i][2] = min(dp2[i - 1][3], dp2[i - 1][2]) + int(d[i] != 2);
		dp2[i][1] = min(dp2[i - 1][1], min(dp2[i - 1][2], dp2[i - 1][3])) + int(d[i] != 1);
	}
	int LdS = min(dp2[n][1], min(dp2[n][2], dp2[n][3]));
	printf("%d", min(LiS, LdS));
	return 0;
}
```

---

## 作者：kkxhh (赞：4)

首先我们看这个题目,显然是可以用 **LIS** 和 **LDS** 的 **O(nlogn)** 的方法做的

但是有没有更好的办法呢？

当然是有的，在其他的题解中已经给出了 **O(n)** 的做法

~~但是我过于蒟蒻开始根本没看懂~~

于是这里就大概说一下 **O(n)** 做法的状态是怎么转移的

首先我们定义**up1 up2 up3**分别是在单调递增的情况下以1 2 3结尾的最小费用
而**down1 down2 down3**则是单调递减下的最小费用

那么假设目前最新的一个数字是1的时候

**up1**显然是不变的，因为它不需要额外的费用也能保证自己仍然是以1结尾单调递增的

而对于**up2**，首先它要把结尾变成2，于是费用铁定要+1，但是对于结尾是2的单调递增序列，它的倒数第二位既可以是1也可以是2，于是它就应该从**up1**和**up2**中较小的一位加上1转移过来

同理**up3**则是由**up1 up2 up3**中的最小者转移过来再加个1

单调递减情况下的转移也差不多，此处就不再阐述了

还有一个需要注意的点就是转移的顺序

因为**up3**的转移涉及到**up2**和**up1**，而**up2**也涉及到了**up1**所以单调递增的转移顺序应该是3 2 1，同理单调递减的转移顺序应该是1 2 3

代码就不贴了，~~毕竟和其他题解写得几乎一模一样~~

---

## 作者：zht467 (赞：4)

当然有O(3n)的做法了

因为 Di（1 <= Di <= 3） 就 3 种情况

所以可以这么搞

f[i][j][0] 表示前 i 个，且第 i 个变成 j 的 递增 序列最小修改次数

f[i][j][1] 表示前 i 个，且第 i 个变成 j 的 递减 序列最小修改次数

具体如何转移看代码吧





        
```cpp
#include <cstdio>
#include <iostream>
const int MAXN = 30001;
int n, ans = ~(1 << 31);
int a[MAXN], f[MAXN][4][2];
inline long long read()
{
    long long x = 0, f = 1;
    char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}
inline int min(int x, int y)
{
    return x < y ? x : y;
}
int main()
{
    int i, j;
    n = read();
    for(i = 1; i <= n; i++) a[i] = read();
    for(i = 1; i <= n; i++)
    {
        f[i][1][0] = f[i - 1][1][0] + (a[i] != 1);
        f[i][2][0] = min(f[i - 1][1][0], f[i - 1][2][0]) + (a[i] != 2);
        f[i][3][0] = min(f[i - 1][1][0], min(f[i - 1][2][0], f[i - 1][3][0])) + (a[i] != 3);
        f[i][1][1] = min(f[i - 1][1][1], min(f[i - 1][2][1], f[i - 1][3][1])) + (a[i] != 1);
        f[i][2][1] = min(f[i - 1][3][1], f[i - 1][2][1]) + (a[i] != 2);
        f[i][3][1] = f[i - 1][3][1] + (a[i] != 3);
    }
    for(i = 1; i <= 3; i++)
        for(j = 0; j <= 1; j++)
            ans = min(ans, f[n][i][j]);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：小柯 (赞：4)

疑惑：为什么看到i-1都不用滚动数组？

像一些大佬的方法一样，用递推，不过加了一个滚动数组的优化，时间复杂度为
$O(n)$
空间复杂度为
$O(1)$

# 代码

```
#include<cstring>
#include<cstdio>
#define OO 2147483647
int n,d,i,ii,iii,s,f1[2][4],f2[2][4];
char x;
int Min(int a,int b,int c=OO,int d=OO,int e=OO,int f=OO){
	if(a<=b&&a<=c&&a<=d&&a<=e&&a<=f)return a;
	if(b<=a&&b<=c&&b<=d&&b<=e&&b<=f)return b;
	if(c<=a&&c<=b&&c<=d&&c<=e&&c<=f)return c;
	if(d<=a&&d<=b&&d<=c&&d<=e&&d<=f)return d;
	if(e<=a&&e<=b&&e<=c&&e<=d&&e<=f)return e;
	if(f<=a&&f<=b&&f<=c&&f<=d&&f<=e)return f;
}
int r(){
	s=0;
	x=getchar();
	while(x<'0'||x>'9')x=getchar();
	while(x>='0'&&x<='9')s=(s<<1)+(s<<3)+x-'0',x=getchar();
	return s;
}
void w(int x){
	if(x<0){
		w(-x);
		return;
	}
	if(x==0)return;
	w(x/10);
	putchar(x%10+'0');
}
int main(){
	n=r();
	for(i=1;i<=n;i++){
		d=r();
		ii=i&1,iii=(i+1)&1;
		if(d==1){
			f1[ii][1]=f1[iii][1];
			f1[ii][2]=Min(f1[iii][1],f1[iii][2])+1;
			f1[ii][3]=Min(f1[iii][1],f1[iii][2],f1[iii][3])+1;
			f2[ii][1]=Min(f2[iii][1],f2[iii][2],f2[iii][3]);
			f2[ii][2]=Min(f2[iii][2],f2[iii][3])+1;
			f2[ii][3]=f2[iii][3]+1;
		}
		if(d==2){
			f1[ii][1]=f1[iii][1]+1;
			f1[ii][2]=Min(f1[iii][1],f1[iii][2]);
			f1[ii][3]=Min(f1[iii][1],f1[iii][2],f1[iii][3])+1;
			f2[ii][1]=Min(f2[iii][1],f2[iii][2],f2[iii][3])+1;
			f2[ii][2]=Min(f2[iii][2],f2[iii][3]);
			f2[ii][3]=f2[iii][3]+1;
		}
		if(d==3){
			f1[ii][1]=f1[iii][1]+1;
			f1[ii][2]=Min(f1[iii][1],f1[iii][2])+1;
			f1[ii][3]=Min(f1[iii][1],f1[iii][2],f1[iii][3]);
			f2[ii][1]=Min(f2[iii][1],f2[iii][2],f2[iii][3])+1;
			f2[ii][2]=Min(f2[iii][2],f2[iii][3])+1;
			f2[ii][3]=f2[iii][3];
		}
	}
	n&=1;
	w(Min(f1[n][1],f1[n][2],f1[n][3],f2[n][1],f2[n][2],f2[n][3]));
	return 0;
}
```


---

## 作者：呆瓜yy (赞：3)



~~我才不会告诉你我不会lower_bound和upper_bound呢！~~


------------


（ 一个小蒟蒻只能想到最长不降子序列的解法^-^）：
 
简单地说，就是用一个数组d1保存目前的最长不降子序列。当后面遇到一个cow[i]比d1[len1]大或与它相等的时候，就把这个cow[i]放在d1数组的最后面；否则就用这个cow[i]替换掉d1数组里第一个比它大的数（不会影响d1的长度）。（反过来也是类似的方法）

   

**代码如下：**

```cpp
#include<cstdio>
  
#include<algorithm>
  
using namespace std;

int n,  cow[30005],  few[30005],  more[30005],  len1=1,  len2=1,  d1[30005],  d2[30005];

int main( )

{

	scanf("%d",&n); 
	for(int i=1;i<=n;i++)
	  scanf("%d",&cow[i]);
	for(int i=1;i<=n;i++)
	  if(d1[len1]<=cow[i] && i!=1)
	  {
	  	  len1++;
	  	  d1[len1]=cow[i];
	  }
	  else
      {
      	  int l=0,r=len1,m;
      	  while(l+1<r)
      	  {
      	  	  m=(l+r)/2;
      	  	  if(d1[m]<=cow[i])
      	  	    l=m;
      	  	  else 
      	  	    r=m;
          }
          d1[r]=cow[i];//要注意这里的r和l。(我试了很多遍才试出来的QAQ）
      }
	
	for(int i=1;i<=n;i++)
	  if(d2[len2]>=cow[i])
	  {
	  	len2++;
	  	d2[len2]=cow[i];
	  }  
	  else
	  {
	  	  int l=0,r=len2,m;
	  	  while(l+1<r)
	  	  {
	  	  	  m=(l+r)/2;
	  	  	  if(d2[m]<cow[i])
	  	  	    r=m;//这里是反过来的QAQ
	  	  	  else 
	  	  	    l=m;
		  }
		  d2[r]=cow[i];
	  }
	printf("%d",n-max(len1,len2));
	return 0;
}
```

---

## 作者：geray_king (赞：1)

这道题，蒟蒻没有想到用什么LIS和LDS，所以只能用状态转移一个一个推。
因为只有两种情况，递增或者递减。所以我创建了两个状态转移的数组up和dn
up[i][0]代表第i位是‘1’的切满足递增的序列所需要修改的次数
up[i][1]代表第i位是‘2’的切满足递增的序列所需要修改的次数
以此推下去
dn[i][0]则代表第i位是1的满足递减的序列所需要修改的次数
序列中只有1 2 3 三个数字。
遇到1的时候也只有3种情况（a[i]==1）
1.不修改 对应的up[i][0]=up[i-1][0]
因为不用修改，满足单调递增，所以此处1必定由前面的1转移而来
2.修改为2 对应的up[i][1] = min(up[i-1][0],up[i-1][1])+1;
//由于2，且单调递增，所以2前面只能是1或者2，本次需修改所以+1；
3.修改为3 对应的
up[i][2] = min(min(up[i-1][1],up[i-1][0]),up[i-1][2])+1;
//递增的，3可以由 3 2 1转移而来，修改为3因此+1；
递减的序列也如此递推，就能得到正确的答案了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int up[maxn][3];
int dn[maxn][3];
int a[maxn];
int main()
{
    int n;
    //freopen("azerah.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i]==1)
        {
            up[i][0] = up[i-1][0];
            up[i][1] = min(up[i-1][0],up[i-1][1])+1;
            up[i][2] = min(min(up[i-1][1],up[i-1][0]),up[i-1][2])+1;
            dn[i][0] = min(dn[i-1][0],min(dn[i-1][1],dn[i-1][2]));
            dn[i][1] = min(dn[i-1][2],dn[i-1][1])+1;
            dn[i][2] = dn[i-1][2]+1;
        }
        else if(a[i]==2)
        {
            up[i][0] = up[i-1][0]+1;
            up[i][1] = min(up[i-1][0],up[i-1][1]);
            up[i][2] = min(min(up[i-1][1],up[i-1][0]),up[i-1][2])+1;
            dn[i][0] = min(dn[i-1][0],min(dn[i-1][1],dn[i-1][2]))+1;
            dn[i][1] = min(dn[i-1][2],dn[i-1][1]);
            dn[i][2] = dn[i-1][2]+1;
        }
        else
        {
            up[i][0] = up[i-1][0]+1;
            up[i][1] = min(up[i-1][0],up[i-1][1])+1;
            up[i][2] = min(min(up[i-1][1],up[i-1][0]),up[i-1][2]);
            dn[i][0] = min(dn[i-1][0],min(dn[i-1][1],dn[i-1][2]))+1;
            dn[i][1] = min(dn[i-1][2],dn[i-1][1])+1;
            dn[i][2] = dn[i-1][2];
        }
    }
    int ans = 1000000;
    for(int i=0;i<3;i++)
    {
    	ans = min(ans,up[n][i]);
    	ans = min(ans,dn[n][i]);
	}
	cout<<ans<<endl; 
}
```


---

## 作者：circlegg (赞：1)

求出最长的正链和反链，取最长的，若长度为len，则n-len就是最优解，证明：

序列中有两个集合：集合A与集合B，A为链集合，B为折点集合，两集合没有交集，且A∪B=总集U

需要修改的值为n-len，则序列中有n-len个折点，若存在更优解，使修改数量为m<n-len，则有m个折点

所以B集合元素变少，A集合元素变多，但是最长链长度固定为len，A集合元素固定不变，所以最优解不为m，为n-len

评测信息    20:24    美国wallace    7ms

···
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,maxu=1,maxd=1,l,r,mid,h[30005],d[30005];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&h[i]);
    }
    d[1]=h[1];
    for(int i=2;i<=n;i++){//最长不下降子序列 
        l=1,r=maxu;
        while(l<=r){
            mid=(l+r)/2;
            if(d[mid]<=h[i]){//带等于就是链的长度，不带就是单调序列长度 
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        d[l]=h[i];
        if(l>maxu){
            maxu++;
        }
    }
    d[1]=h[1];
    for(int i=2;i<=n;i++){//最长不上升子序列 
        l=1,r=maxd;
        while(l<=r){
            mid=(l+r)/2;
            if(d[mid]>=h[i]){
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        d[l]=h[i];
        if(l>maxd){
            maxd++;
        }
    }
    printf("%d",n-max(maxu,maxd));
    return 0;
}
···
```

---

## 作者：郑yz (赞：0)

## 这题真的很简单很简单
## 就是求一次最长不上升子序列，再求一次最长不下降子序列就好了
### 相信不用再解释了直接上代码但要注意优化（还要吸口氧）

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
int n,m,ans,a[30005],f[30005];

int main(void){
	scanf("%d",&n);
	ans=9999999;
	for(register int i=1;i<=n;++i)scanf("%d",a+i);
	for(register int i=1;i<=n;++i){
		f[i]=1;
		for(register int j=1;j<i;++j)
		   if(a[i]>=a[j])f[i]=max(f[i],f[j]+1);
		ans=min(ans,n-f[i]);
    }
	for(register int i=1;i<=n;++i){
		f[i]=1;
		for(register int j=1;j<i;++j)
		   if(a[i]<=a[j])f[i]=max(f[i],f[j]+1);
		ans=min(ans,n-f[i]);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：_Qer (赞：0)

~~非正解凑个数~~

听说dp最长不下降/不上升子序列会T？

蒟蒻不服，开O2强行卡常过了（~~我才不会说我92分7次~~）。

放上通过记录[click here](https://www.luogu.org/record/show?rid=8283812)

```cpp
#include <iostream>
#include <cstdio>
//减少头文件不知道能不能加速
using namespace std;
unsigned int n, arr[30010];
unsigned int up[30010], down[30010], maxup, maxdown;
//up是不下降，down是不上升，maxup是最长不下降长度，maxdown是最长不上升长度
//unsigned int加速（丢掉符号运算）
int main() {
	scanf("%d", &n);//scanf加速，下同
    //这里写个输入优化还能更快
	for (register int i = 1; i <= n; ++i) {
    	//循环变量用register int加速，下同，++i似乎也比i++快一点
		scanf("%d", &arr[i]);
	}
	for (register int i = 1; i <= n; ++i) {
		up[i] = 1;
		down[i] = 1;
		for (register int j = 1; j < i; ++j) {
		    if (arr[i] == arr[j]) {
		        up[i] = max(up[i], up[j] + 1);
		        down[i] = max(down[i], down[j] + 1);
			} else if (arr[i] > arr[j]) {
				up[i] = max(up[i], up[j] + 1);
			} else {
				down[i] = max(down[i], down[j] + 1);
			}
		}
		maxup = max(maxup, up[i]);
		maxdown = max(maxdown, down[i]);
	}
    //以上把最长不下降和不上升放一起
	cout << n - max(maxup, maxdown) << endl;
	return 0;
}
```

最后提醒一下，这个程序要吸氧才能过！

---

## 作者：cs18 (赞：0)

//先分析一下思路，需要将牛编号，成为单调序列（递增或递减），还要求变化的最小

//这样的话，就可以在原来的基础上找到一个最长不降子序列或者最长不升子序列，比较出一个最大的长度，用总长减去这个数就行了

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
int n,j;
int a[30001],b[30001];//本蒟蒻真的比较弱，又设了一个数组b来到这推一遍 
int d1[30001],len1,d2[30001],len2;//正着一个，倒着一个 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i]>=d1[len1])    d1[++len1]=a[i];
        else    
        {
            j=upper_bound(d1+1,d1+len1+1,a[i])-d1;//c++中STL的内置函数，在1到len1中找到一个大于a[i]的一个数的序号[STL源码学习----lower_bound和upper_bound算法](https://www.cnblogs.com/cobbliu/archive/2012/05/21/2512249.html "STL源码学习----lower_bound和upper_bound算法")不懂的看这里
            d1[j]=a[i];
        }
    }
    for(int i=1;i<=n;i++)
    b[i]=a[n+1-i];//本蒟蒻将原数组倒过来了 
    for(int i=1;i<=n;i++)
    {
        if(b[i]>=d2[len2])    d2[++len2]=b[i];
        else    
        {
            j=upper_bound(d2+1,d2+len2+1,b[i])-d2;//重新寻找一遍，速度挺快的，在其他题中能过special judge（数据范围1e6） 
            d2[j]=b[i];
        }
    }    
    int maxn=max(len1,len2);//比较出一个最大的 
    printf("%d",n-maxn);//算出需要改变的，直接输出即可 
}
```

---

