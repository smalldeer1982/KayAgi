# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 样例 #1

### 输入

```
3
-1 -2 -3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
-4 2 0 5 0
```

### 输出

```
11
```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2
```

### 输出

```
18
```

# 题解

## 作者：LuckyCloud (赞：19)

#### 利用数学推导，排除无关变量，然后进行求解。


------------
  
  **应该可以看出，前缀和后缀交叉的情况下，交叉的那部分，相当于没有变化。
  那么**
  
  **据题可知：**
  
  **设 前缀为A，后缀为B，未变化部分的为C。序列数字总和为S（允许A，B，C都为空的情况，此时A=B=C=0）**
  
  ** 因为 A+B+C=S，需求解为 -（A+B）+C 的最大值**
  
  **所以 —（A+B）+C的最大值 = —（S-C）+C的最大值 = 2C-S **
  

------------

  
  ### 综上 显然S是定值，我们要做的就是让C最大，问题就变成了求最大子段和了。
    LuckyCloud 
  
  **附上丑陋的代码**
  ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,Max,S,a[100093],sum,ans;
inline long long read()
{
  long long cnt=0,f=1;char ch=getchar();
  while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
  while (ch>='0'&&ch<='9'){cnt=cnt*10+ch-48;ch=getchar();}
  return cnt*f;
}
int main()
{
  n=read();
  for (int i=1;i<=n;i++)
  {
   a[i]=read();
   sum+=a[i];
  }
  for (int i=1;i<=n;i++)
   if (S+a[i]<0) S=0;
   else {S+=a[i];Max=max(Max,S);}
  Max=max(Max,S);
  ans=Max*2-sum;
  printf("%lld\n",ans);
  return 0;
}
```
  
  



---

## 作者：Level_Down (赞：8)

其实这道题非常简单，只要找对了方法，作为橙题也不为过。

根据题意，前缀和后缀都覆盖的地方相当于不变，不用考虑。

在剩下的情况中，我们假设所有的数都进行变化，现在想要达到最大的总和，我们需要筛选出一段数不变化，即我们要求出所有数都变化后的数列中的最小子段和。

在换一句话来说，就是求出原数列中最大子段和的相反数。

这里设原数列总和为 $sum$，最大子段和为 $ans$，我们不难发现最终的答案就是 $ans - (sum - ans)$，即最大子段和（不变化的那段数）与变化的那段数总和（$sum - ans$）的相反数的和。

至此，我们可以推出极简代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005],sum,ans,ans2;//原数列总和为sum，最大子段和为ans。
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i],ans2 = max(ans2 + a[i],0),ans = max(ans,ans2);
        //求出最大子段和和原数列总和。
    }
    cout << ans - (sum - ans);//输出答案。
    return 0;//AC！
}
```


---

## 作者：fzj2007 (赞：5)

## 第一步 读题

>给你一个数字序列，你可以选择它的一些前缀或后缀(可能是空的)中的每个数字都乘以 $-1$。前缀和后缀可以交叉也可以为空。问能得到的最大序列和是多少。

简化一下就是我们可以把一个序列的前面连续几个数和后面连续几个数（可以不取）换成相反数，然后求这个序列的和。问这个和最大是多少。

## 第二步 思路

由于一个数乘 $-1$ 后再乘 $-1$，则结果为原数。那么我们就可以不考虑交叉的情况（因为交叉的情况与不选交叉这一部分的情况相同）。

首先，我们分析一下本题： $n \le 10^5$，所以这道题我们的时间复杂度不可能为 $O\left(n^2\right)$，因为会超时。那么由于这个题是一个序列问题，所以我们大概就想到了一个思路：预处理。最常见的预处理，前后缀和，在这道题里大概用的上。所以我们考虑前后缀和。

我们可以先求出序列的前后缀和（如果大于 $0$ 就可以改为$0$，因为我们还要乘 $-1$），再求出原序列的总和。时间复杂度 $O\left(n\right)$。

现在我们有两种思路：

- 直接暴力，当位置为 $i$ 时，求出 $i$ 后面的后缀和中最小的一个（因为最小的一个乘以 $-1$ 就变成最大的了。）那我们就需要两重循环，时间复杂度 $O\left(n^2\right)$，上面我们也说了 $n \le 10^5$，明显超时。我们考虑优化。

- 由于我们每次都要查找**当前位置的后面的后缀和最小的一个，所以我们可以选择把后缀和改成当前位置后面的最小的后缀和。** 那么时间复杂度就是 $O\left(n\right)$ 。最后，我们可以考虑当前位置的前缀和与后缀最优结果的加和最小的情况（还是乘 $-1$ 的缘故）。那么这部分的时间复杂度也是 $O\left(n\right)$。然后最后我们用原序列的总和减去这个最小结果（如果最小结果为正数的话我们就取 $0$）。那么最后的总时间复杂度为 $O\left(n\right)$，完全不会超时。

## 第三步 代码

终于到了你们最喜欢的部分了。。（请勿抄袭！）

```
#include<bits/stdc++.h>
using namespace std;
int last[100005],first[100005],p[100005],n,result,ans;//first和last分别存储前后缀和，p读入，n为序列长度，result表示最后的答案，ans存储原序列和。 
int main(){
	cin>>n;//读入
	for(int i=1;i<=n;i++) cin>>p[i];//读入序列
	for(int i=1;i<=n;i++) first[i]=first[i-1]+p[i],ans+=p[i];//前缀和和序列和同时求出来233
	for(int i=n;i>=1;i--) last[i]=last[i+1]+p[i];//后缀和。由于是后缀和，所以从倒序遍历
	for(int i=n;i>=1;i--) last[i]=min(last[i],last[i+1]);//求出当前后缀最优结果。我们可以从后面一项中直接寻找过来，就像动态规划的转移方程（本来就是。。）
	result=ans;//赋值，用来存储
	for(int i=0;i<=n;i++)//记得从0开始啊。。前面也说了要多算一遍0
		result=max(result,ans-2*(first[i]+last[i+1]));//这里是转移方程，我们要最大值，那就用max，max第二个参数的意思就是当前的前缀和和后面的最优情况。
	cout<<result<<endl;//输出
	return 0;//bye~
}
```

### 第四步 其他

- 撰文不易，大佬勿喷！
- 文章若有`bug`请私信作者，感激不尽！
- 如果有帮助，请帮忙点下赞，感谢！


---

## 作者：4526_ (赞：3)

[题目链接](https://www.luogu.org/problem/CF33C)

[双倍经验](https://www.luogu.org/problem/SP7507)

挺有意思的一道题，有一定的思维难度 ~~然而完全没有代码难度~~

**主要思想：DP+优化**

大致思路：

**一、O（n方）做法：**

1、预处理 前缀和 / 后缀和，枚举 前缀终点 / 后缀终点

2、前后缀若有交界，中间一段**特殊处理**

3、小优化：由2可知枚举时保证 **后缀终点 始终在 前缀终点 之后**仍然是正解

但是n最大为1e5，这样显然过不了

**二、O（n）做法：**

分析可知**处理后每个数有四种情况**：

- **既不是前缀也不是后缀**

- **作为前缀被处理**

- **作为后缀被处理**

- **作为前缀和后缀各被处理一次**

那么根据每种情况分别推出转移方程即可

同样由一（2）可知状态4去掉也不影响答案

具体情况见代码

AC代码：

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;

int n,arr[100010],ans[100010][5];
//arr为原序列，ans为用于dp的数组，具体含义见下

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
	//处理
	for(int i=1;i<=n;++i){
		//以下是转移方程
		//ans[i][1]表示第i个数既不是前缀也不是后缀，对答案的贡献为arr[i]
		//可由（第i-1个数 是前缀 / 既不是前缀也不是后缀）转移
		ans[i][1]=max(ans[i-1][1],ans[i-1][2])+arr[i];
		//ans[i][2]表示第i个数是前缀，对答案的贡献为 -arr[i]
		//可由（第i-1个数 是前缀）转移
		ans[i][2]=ans[i-1][2]-arr[i];
		//ans[i][3]表示第i个数是后缀，对答案的贡献为 -arr[i]
		//可由（第i-1个数 是前缀 / 是后缀 / 什么都不是）转移
		ans[i][3]=max(ans[i-1][1],max(ans[i-1][2],max(ans[i-1][3],ans[i-1][4])))-arr[i];
		//ans[i][4]表示第i个数既是前缀也是后缀，对答案的贡献为arr[i]
		//可由（第i-1个数 是后缀 / 什么都是）转移
		//ans[i][4]=max(ans[i-1][2],ans[i-1][4])+arr[i]; 这不重要
		//以上是转移方程
	}
	//ans[0][0]用于存储最终答案
	ans[0][0]=max(ans[n][1],
			  max(ans[n][2],
			  max(ans[n][3],
				  ans[n][4])));
	printf("%d",ans[0][0]);
	return 0;
}


```

欢迎来[我的blog](https://www.luogu.org/blog/4526-Au/)看看

---

## 作者：MilkyCoffee (赞：2)

比较简单的一道蓝题。

上手之后根本没有考虑数论，直接上 dp 。

显然，非第一个的数一共有四种状态：

- 属于前缀

	如果这个数属于前缀，那么它的上一个数也一定是前缀
- 既属于前缀也属于后缀

	如果这个数既属于前缀也属于后缀，那么它的上一个数可以是前缀，也可以既是前缀也是后缀。
- 不属于前缀也不属于后缀

	如果这个数不属于前缀也不属于后缀，那么它的上一个数可以是前缀，也可以不是前缀也不是后缀
- 属于后缀

	如果这个数是后缀，那么它的上一个数可能是所有状态，

写成代码就是：

```cpp
dp[i][1] = dp[i-1][1] - a[i]; // 前缀
dp[i][2] = max4(dp[i-1][1], dp[i-1][2], dp[i-1][3], dp[i-1][4]) - a[i]; // 后缀
dp[i][3] = max(dp[i-1][1], dp[i-1][3]) + a[i]; // 属于前缀也属于后缀
dp[i][4] = max(dp[i-1][1], dp[i-1][4]) + a[i]; // 不属于前缀或后缀
```

由上可得，$dp_{i,3}$ 和 $dp_{i,4}$ 的值和作用是完全一样的，删掉一个也可以 AC 这题。

tip : 因为排版问题交了几次，这次应该可以了。

---

## 作者：BreakPlus (赞：1)

[$\large \text{CF33C Wonderful Randomized Sum}$](https://www.luogu.com.cn/problem/CF33C)

### $\text{Discription}$

把序列的一个可以为空的前缀和一个后缀的数乘以 $-1$，求操作后序列和的最大值。

### $\text{Solution}$

我们可以发现，如果前后缀有相交的子段，子段中的数会被乘以 $2$ 次 $-1$，相当于没变。所以我们可以只考虑不相交的情况。

我们可以计算出所有前/后缀，如果对其进行操作，对答案的贡献值。显然前/后缀操作后对答案的贡献值是它的和乘以 $-2$。

加下来我们看看暴力怎么做。~~暴力是不是，加边，加边，加边，并查集查询。~~ 我们可以枚举一个前缀，然后枚举与它不相交的后缀，答案取原先的值加前缀和后缀的贡献。

现在我们考虑咋优化：我们发现可以取的后缀贡献也是个后缀，我们可以再预处理出后缀贡献的后缀最大值（雾），这样就不需要枚举后缀了。

时间复杂度：$\textsf{O}(n)$。

### $\text{Code}$

异常的整齐……

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],pr[100010],hz[100010],hzm[100010],N,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],N+=a[i],ans+=a[i]; // 统计原序列的和，答案至少为这个数字
	for(int i=1;i<=n;i++) pr[i]=pr[i-1]+a[i]; // 先求前缀和
	for(int i=1;i<=n;i++) pr[i]=(-pr[i])*2; // 求修改前缀的贡献
	for(int i=n;i>=1;i--) hz[i]=hz[i+1]+a[i]; // 后缀和
	for(int i=1;i<=n;i++) hz[i]=(-hz[i])*2; // 后缀贡献
	for(int i=n;i>=1;i--) hzm[i]=max(hz[i],hzm[i+1]); // 后缀贡献的后缀最大值
	for(int i=0;i<=n;i++) ans=max(ans,N+pr[i]+hzm[i+1]); // O(n) 求出答案
	cout<<ans<<endl;
	return 0; 
}
```

---

## 作者：_lxy_ (赞：1)

### 题意
有一个数组，可以将它的前缀和后缀中的每一个数都变为它的相反数，求经过操作后得到的最大的序列和。
### 分析
操作后前缀和后缀重叠的部分变了两次相反数，因此重叠的部分的每一个数相当于没有变化，所以将和最大的子段之外的每一个数都变为相反数是最优的，因为否则变为相反数后序列和就会变小。所以最后的答案就是原数组除去最大子段的部分都变为相反数后在加上最大子段和。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,sum;
int main()
{
    scanf("%d",&n);
    int i,j,maxx=0,mx=0;
    for(i=0;i<n;i++)
    {
    	int x;
    	scanf("%d",&x);
    	sum+=x;
    	mx=max(mx+x,0); //如果将这个数加入当前最大子段更优，就加入，否则将最大子段和清零 
    	maxx=max(maxx,mx); //更新最大值 
	}
	printf("%d\n",-(sum-maxx)+maxx); //除最大子段之外的所有数变为相反数后加上最大子段和 
    return 0;
}
```


---

## 作者：wcarry (赞：1)

## 题目大意：
变换一次可使**前缀**和**后缀**上的每一个数都乘 $-1$，**前缀**和**后缀**的长度在区间 $[0,n]$ 间。变换只可进行一次，使得变化后的数列的和最大。

## 思路：
![](https://cdn.luogu.com.cn/upload/image_hosting/sxlh6tbv.png)

如图，若选择的前缀和后缀如图所示，则它们等价（中间重叠的部分两次乘 $-1$ 抵消了）。

所以可以令所选择的前缀和后缀不互相重叠。

现在只需要统计当**前缀长度**不大于 $i$ 时，**后缀长度**不超过 $n-i$ 时，满足 $1\le i\le n$ 时，数列变化量的**最大值**即可。
## 解法：

* Step1：统计长度为 $[0,n]$ 的**前缀**被改变时**序列和**被改变的量。将长度为 $i$ 时，序列和的改变量称为 $dpa[i]$。
* Step2：统计长度为 $[0,n]$ 的**后缀**被改变时**序列和**被改变的量。将长度为 $i$ 时，序列和的改变量称为 $dpb[i]$。
* Step3：

	令 $maxa[i]=\max\limits _{0\le j\le i}\{dpa[j]\}$
    
   令 $maxb[j]=\max\limits _{0\le j\le i}\{dpb[j]\}$
* Step4：$ans=\max\limits_{1\le i\le n}\{maxa[i]+maxb[n-i]\}+\sum\limits_{1\le i\le n}a[i]$

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define re register
#define ll long long
#define inf 0x3f3f3f3f

template<typename T>
inline void read(T &x){
	x=0;re bool f=false;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x=f?-x:x; return ;
}

template<typename T>
inline void write(T x){
	if(x<0){x=-x;putchar('-');}
	if(x>=10){write(x/10);}
	putchar(x%10+'0');
}

int const N=1e5+5;
int a[N],dpa[N],dpb[N],maxa[N],maxb[N];

signed main(){
	int n; read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=1;i<=n;i++){
		dpa[i]=dpa[i-1]-2*a[i];
	}
	for(int i=n;i>=1;i--){
		dpb[n-i+1]=dpb[n-i]-2*a[i];
	}
//	for(int i=1;i<=n;i++){
//		write(dpa[i]),putchar(' ');
//	}puts("");
//	for(int i=1;i<=n;i++){
//		write(dpb[i]),putchar(' ');
//	}
	for(int i=1;i<=n;i++){
		maxa[i]=max(maxa[i-1],dpa[i]);
		maxb[i]=max(maxb[i-1],dpb[i]);
	}
	int ans=-inf,sum=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,maxa[i]+maxb[n-i]);
		sum+=a[i];
	}
	ans+=sum;
	write(ans),puts("");
}
```

---

## 作者：Misaka_Mik0t0 (赞：1)

当前缀与后缀有重合时，重合部分乘了两次 $-1$，没有变化，可以忽略。因此，我们可以认为前缀与后缀不能重合。

我们先预处理出前缀和 $h_i$ 与后缀和 $t_i$，并算出原始数列的和 $s$，答案就是 $s-2\times($ 前、后缀和 $)$。由于前、后缀不重合，可以枚举每一个数，让前缀、后缀均在这个数前、后。答案为：

$\max_{i=0}^n(s-2\times(\max_{j=1}^ih_j+\max_{j=i+1}^nt_j))$

只需再预处理出 $maxh_i=\max_{j=0}^ih_j$，$maxt_i=\max_{j=i}^{n+1}t_i$ 即可。

参考代码：（能AC，但仅供参考，建议自己通过以上内容自己敲一遍代码）
```cpp
#include<cstdio>
const int maxn=100005;
int n,p[maxn],h[maxn],t[maxn],lim,ans,l;
int main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i)scanf("%d", p+i);
	h[0]=p[0];
	for(int i=1;i<n;++i)h[i]=h[i-1]+p[i];
	for(int i=n-1;i>=0;--i)t[i]=t[i+1]+p[i];
	for(int i=0;i<n;++i){if(lim>h[i])lim=h[i];h[i]=lim;}
	lim=0,ans=h[n-1];
	for(int i=n-1;i>=0;--i){if(lim>t[i])lim=t[i];t[i]=lim;}
	for(int i=n-1;i>=0;--i)if(ans>(i>0?h[i-1]:0)+t[i])ans=(i>0?h[i-1]:0)+t[i];
	for(int i=0;i<n;++i)l+=p[i];
	printf("%d", l-2*ans);
	return 0;
}
```

---

## 作者：Z_M__ (赞：1)

**思路一：** 开始的想法是处理出每个位置最优的左边和右边取反的位置，从而处理处每个位置的最优值，再从中去最大值即可。

**思路二：** 因为数列的两端都可以取反连续的一段，所以$ans=(-l)+mid+(-r)$，其中 $l$ 为左边取反的那一段的前缀和和， $r$ 为右边取反的那一段的后缀和和，$mid$ 为中间不取反的一段。

为了让$ans$大，所以 $-l\ge 0, -r\ge 0$，即 $l\le 0, r \le 0$ , **所以 $mid$ 为最大子串和**。

**证明：** 在序列 $a$ 中， 设 $p1、p2$ 为 $mid$ 的左端点和右端点，则 $a[p1 - 1] \le 0, a[p2 + 1] \le 0$， 因为如果$a[p1 - 1]$ 或 $a[p2 + 1] > 0$ 则 $mid$ 就不是最大子串和了。
所以当 $mid$ 不是最大子串和时，$l$ 必定大于最优解的 $l$，则$-l$ 小于最优解的 $-l$, $-r$ 同理，又因为 $mid$ 也小于最优解 ($mid$为最大子串和时)的 $mid$, 所以此时的$ans$ 必定小于 $mid$为最大子串和时的 $ans$, 所以当 $mid$ 为最大子串和时为最优方案。

设$sum$ 为数列总和， 所以

$sum = l + mid + r$

$l + r = sum - mid$

$- (l + r) = mid - sum$

$(-l) + (-r) = mid - sum$
则 $ans= (-l) + mid + (-r) = (mid - sum) + mid = 2*mid-sum$

所以只要处理出$mid$ 和 $sum$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int MAXN = 1e5 + 10;
int n, a[MAXN], sum, ans, mid, tot;
int main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], sum += a[i];// 处理sum
	tot = 0, mid = -inf;
	for (int i = 1; i <= n; i++)
	{
		tot = max (tot + a[i], 0);
		mid = max (tot, mid); // 贪心处理最大子串
	}
   ans = 2 * mid - sum;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：chufuzhe (赞：1)

首先，处理一下交叉的情况。

以下图为例，前缀是 $1-5$，后缀是 $3-6$，中间 $3-5$ 的部分是交叉的部分，乘了两遍 $-1$，就相当于没变，所以就相当于前缀是 $1-3$，后缀是 $5-6$。因此，可以不用单独考虑交叉的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/zmbdaeu7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$*(-1)$，显然对于越小的数收益越大，所以以前缀为例，可以用前缀和，记录每一个位置及其之前的位置的最小值，后缀也可以这样实现。

然后可以枚举一个中间点，将前面的最小值和后面的最小值相加，取最小值，这个就是需要乘以 $-1$ 的数的和。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io {
    char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
    inline char gc() {
        if (p1 != p2)
            return *p1++;
        p1 = buf;
        p2 = p1 + fread(buf, 1, 1 << 21, stdin);
        return p1 == p2 ? EOF : *p1++;
    }
    #define G gc

    #ifndef ONLINE_JUDGE
    #undef G
    #define G getchar
    #endif

    template <class I>
    inline void read(I &cn) {
        char c; int sig = 1;
        while(!isdigit(c = G())) if(c == '-') sig = 0;
        if(sig) {cn = c-48; while(isdigit(c = G())) cn = (cn<<3)+(cn<<1)+(c-48); }
        else    {cn = 48-c; while(isdigit(c = G())) cn = (cn<<3)+(cn<<1)+(48-c); }
    }
    inline void write(int n) {
        if(n < 10) {
            putchar(n % 10 + '0');
            return ;
        }
        write(n / 10);
        putchar(n % 10 + '0');
    }
}
using namespace io;
int a[100005];
int q[100005];
int h[100005];
int main()
{
	int n, s = 0;
	read(n);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
	}
	for(int i = 1; i <= n; i++) { //前缀和
		q[i] = q[i - 1] + a[i];
	}
	for(int i = 1; i <= n; i++) { //取最小值
		q[i] = min(q[i], q[i - 1]);
	}
	for(int i = n; i >= 1; i--) {
		h[i] = h[i + 1] + a[i];
	}
	for(int i = n; i >= 1; i--) {
		h[i] = min(h[i], h[i + 1]);
	}
	for(int i = 1; i <= n; i++) //找中间点
		s = min(s, q[i] + h[i + 1]);
	s = -2 * s;
	for(int i = 1; i <= n; i++)
		s += a[i];
	cout << s << endl;
	return 0;
}

```


---

## 作者：Yi_Fan (赞：1)

# 前言：
作为一个数论题我们应该从数论突破，于是有了这个解法


------------
# 题意：
给出一个数列，可已将前缀或后缀(可能是空的)中的每个数字都乘以 $-1$ ，就是取相反数，最大序列和是多少


------------
# 分析：
数论就要用数学方式思考，所以我发现：

1. 我们要将未变化前的最大字段和取出并且保留下来，剩下的就取反
1. 设最大字段和为 $a$，数列总和为 $b$  ,实现出来就是：
$a-(b-a)=2*a-b$


------------
# 程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
//变量区
int n;//序列长度 
int a[100001];//记录序列 
int sum;//序列总和 
int ans1,ans2;//最大字段和 
//主函数 
int main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		sum += a[i];//记录总和 
	}
	for(int i = 1; i <= n; i ++) {
		ans1 = max(ans1 + a[i],0);
		ans2 = max(ans2 , ans1);//记录最大字段和 
	}
	cout<<ans2*2-sum;//公式 
	return 0;
}
```



---

## 作者：zhenglier (赞：1)

## ~~数学瞎搞~~

看到这道题，因为要反转前后缀，考虑使用前缀和和后缀和，有一种写法是$O(n)$查找最大前缀和最大后缀，但这种方法是错误的，因为两段区间不能重叠（重叠区域符号不变，相当于没覆盖）。

但这种想法给了我们一个启示，我们可以枚举前缀的右端点$i(1\leq i\leq n)$，然后枚举后缀的左端点$j(i\leq j\leq n)$，这样就可以防止区间重叠，这样的做法是$O(n^2)$的，对于$n=100000$的数据肯定会TLE。

因为后缀的最小值其实不用暴力扫，可以从后往前做一个最小值的后缀，然后就可以$O(1)$查找最小后缀的值，这样复杂度就被优化为$O(n)$，就可以AC了。

```cpp#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,sum;
int a[N];
int st[N]; 
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)scanf("%d",a+i),sum+=a[i];
    for(int i=n;i;--i){
	st[i]=st[i+1]+a[i];
    }
    for(int i=1;i<=n;++i){
        a[i]+=a[i-1];
    }
    for(int i=n;i;--i)st[i]=min(st[i+1],st[i]); 
    int ans=sum;
    for(int i=0;i<=n;++i){
	ans=max(ans,sum-2*(a[i]+st[i+1]));
    }
    cout<<ans<<endl;
}
```

---

## 作者：这有一只匿 (赞：1)

可以明显看出，如果前缀后缀交叉那么就和前缀后缀所取得位置相同的效果是一样的，所以可以不用考虑交叉的情况。那么问题就简化了很多，就可以贪心了。

我们考虑一个i（1<=i<=n），那么我们只需选取在i之前的前缀最小且为负值的和后缀最小且为负值的然后把他们变正再相加在加上中间没变的，之后对于所有的i的情况取一个MAX即可。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAX=1e5+5;
const int INF=2147483647;
int n;
int pre[MAX],suf[MAX],a[MAX],minp[MAX],mins[MAX],maxn;
int main()
{
    scanf("%d",&n);
    minp[0]=1;mins[n+1]=n;
    for(int i=1;i<=n;i++)
    {
    scanf("%d",&a[i]);
    pre[i]=pre[i-1]+a[i];//前缀和
    if(pre[minp[i-1]]>pre[i])minp[i]=i;//在i之前前缀和最小的位置
    else minp[i]=minp[i-1];
    }
    for(int i=n;i>=1;i--)
    {
    suf[i]=suf[i+1]+a[i];
    if(suf[mins[i+1]]>suf[i])mins[i]=i;//在i之后后缀和最小的位置
    else mins[i]=mins[i+1];
    }
    for(int i=1;i<=n;i++)
    {
    int ans=0;
    int l=minp[i],r=mins[i];
    if(l==r)ans=max(pre[n],-pre[n]);//这个要特判……
    else 
    {
    if(pre[l]<0)ans+=-pre[l];//只有小于零才改变
    else ans+=pre[l];
    if(suf[r]<0)ans+=-suf[r];
    else ans+=suf[r];
    ans+=pre[r-1]-pre[l];
    }
    maxn=max(maxn,ans);
    }
    cout<<maxn;
    return 0;
}
```

---

