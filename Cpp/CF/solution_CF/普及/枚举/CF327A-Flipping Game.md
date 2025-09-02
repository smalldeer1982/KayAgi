# Flipping Game

## 题目描述

Iahub got bored, so he invented a game to be played on paper.

He writes $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices $ i $ and $ j $ ( $ 1<=i<=j<=n $ ) and flips all values $ a_{k} $ for which their positions are in range $ [i,j] $ (that is $ i<=k<=j $ ). Flip the value of $ x $ means to apply operation $ x=1 $ - $ x $ .

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

## 说明/提示

In the first case, flip the segment from 2 to 5 $ (i=2,j=5) $ . That flip changes the sequence, it becomes: \[1 1 1 0 1\]. So, it contains four ones. There is no way to make the whole sequence equal to \[1 1 1 1 1\].

In the second case, flipping only the second and the third element $ (i=2,j=3) $ will turn all numbers into 1.

## 样例 #1

### 输入

```
5
1 0 0 1 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
4
```

# 题解

## 作者：tribool4_in (赞：8)

> #### 原题曰： $1 \le n \le 100$ 。哇，那岂不是 $n^3$ 能过？！
> 暴力出奇迹！！

所以就有了一种暴力算法：**枚举左右端点，然后求反转后的 $1$ 的个数即可**！

## 具体算法：

- 输入时先求出原数组里的 $1$ 的个数记为 $c$ ，接下来：

- 枚举 $i, j$ 也就是左右端点，先设 $s=c$ ，然后遍历起点到终点的每个数，如果它是 $1$ ，$s--$，否则$s++$ 。每次遍历取最小值，完美！


## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1010], c;
int main() {
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>a[i];
        c += a[i];
    }
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int l = j - i + 1, s = c;
            for (int k = i; k <= j; k++) {
                if (a[k]) s--;
                else s++;
            }
            maxn = max(maxn, s);
        }
    }
    cout<<maxn<<endl;
}
```

管理员求过！

---

## 作者：Priori_Incantatem (赞：6)

#### 方法1：区间DP

设 $f[i][j]$ 为区间 $[i,j]$ 中取反后所有元素的和，$s[i]=\sum_{j=1} ^i a[j]$  
由于只是求和，不会有哪些乱七八糟的其他决策，我们考虑一个简单的转移  
$f[i][j]=max(f[i+1][j]+(a[i]$ $xor$ $1),f[i][j-1]+(a[j]$ $xor$ $1))$

时间复杂度：$O(n^2)$

**代码**

```cpp
#include<cstdio> 
#include<iostream>
using namespace std;
const int Maxn=110,inf=0x3f3f3f3f;
int f[Maxn][Maxn],s[Maxn],a[Maxn];
int n,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read(),s[i]=s[i-1]+a[i];
		f[i][i]=a[i]^1;
		ans=max(ans,f[i][i]+s[n]-a[i]); // 记得考虑区间大小为1的情况
	}
	
	for(int len=2;len<=n;++len)
	{
		for(int i=1;i+len-1<=n;++i)
		{
			int j=i+len-1;
			f[i][j]=max(f[i+1][j]+(a[i]^1),f[i][j-1]+(a[j]^1));
			ans=max(ans,f[i][j]+s[i-1]+s[n]-s[j]);
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
```

#### 方法2：暴力前缀和

既然只能挑一个区间取反，而 $n$ 又小于等于 $100$ ，那么我们为什么不直接暴力枚举呢  
时间复杂度 $O(n^2)$
其实不用前缀和都行，$O(n^4)$ 的算法都能过

```cpp
#include<cstdio> 
#include<iostream>
using namespace std;
const int Maxn=110,inf=0x3f3f3f3f;
int f[Maxn][Maxn],s[Maxn],a[Maxn];
int n,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	a[i]=read(),s[i]=s[i-1]+a[i];
	
	for(int i=1;i<=n;++i) 
	{
		for(int j=i;j<=n;++j)
		ans=max(ans,(j-i+1)-(s[j]-s[i-1])+s[i-1]+s[n]-s[j]);
	}
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

### 前言

数据水的一批，$\mathcal{O}(n^3)$ 给过我觉得是不应该的。

[安利](https://www.cnblogs.com/CM-0728/p/13558931.html)

### 题意

有一个由 $0$ 和 $1$ 组成的序列 $a_1,a_2,a_3,a_4....,a_n$ 。

规定可以选择一段区间取反。问取反后序列中最多有多少个 $1$ 。

### $\sf Solution$

#### $\sf Step1$

哇， $n$ 只有 $100$ ，可以暴力啦！

枚举区间左端点和右端点，然后 $\mathcal{O}(n)$ 统计 $1$ 的个数。

时间复杂度：$\mathcal{O}(n^3)$

#### $\sf Step2$

上面那种太无脑了，想想优化吧。

显然**前缀和**。

先预处理 $1$ 的个数，取反时只需要区间查询，把 $1$ 的个数和 $0$ 的个数互换。


时间复杂度：$\mathcal{O}(n^2)$

### $\sf Code$

```cpp
#include<cstdio>
using namespace std;
int n,a[105],x,y,maxx;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&x),a[i]=a[i-1]+x;//预处理
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
		{
			x=a[j]-a[i-1];//计算区间中1的个数
			y=j-i+1-x;//计算区间中0的个数
			if(a[n]-x+y>maxx)//a[n]-x+y为取反后1的个数
				maxx=a[n]-x+y;//比较
		}
	printf("%d",maxx);
	return 0;
}
```

---

## 作者：若如初见 (赞：3)

#### 此题的另外两篇题解给出的做法都是 $O(n^3)$ 的时间复杂度，可以通过 $n\leq 100$ 的数据。但其实不难发现有一种 $O(n)$ 的做法：  

我们的目标是，让序列在一次翻转之后能获得尽可能多的 $1$ ，也就是在翻转之前，这段子序列中的 $1$ 尽可能少， $0$ 尽可能多。因此，我们记 $[1,i]$ 中 $0$ 的个数为 $a[i]$ , $1$ 的个数为 $b[i]$ ，从左向右扫描，维护 $a[i]-b[i]$ 的最大值即可。  

另一种理解方式，我们假定 $1$ 对答案的贡献为 $-1$， $0$ 对答案的贡献为 $1$ ，那么：

原序列  1 0 0 1 0  
贡献    -1 1 1 -1 1

对“贡献”序列求最大子段和即可。**答案为“贡献”序列的最大子段和与原序列中 $1$ 的个数之和。**~~证明显然~~。时间复杂度 $O(n)$ ，空间复杂度 $O(1)$。 

## Code ： 

```cpp
#include <cstdio>
int n,a,now,ans,cnt;
inline int max(int a,int b){
	return a>b?a:b;
} //手打max函数，据说可以加速
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(a){
			cnt++; //统计1的个数
			if(now) now--;
		} else now++;
		ans=max(ans,now); //ans维护最大子段和
	}
	printf("%d",cnt+ans);
	return 0;
}
```

我还给此题制作了加强版，只允许 $O(n)$ 的算法通过：[U87061 翻转序列](https://www.luogu.org/problem/U87061)


---

## 作者：LRL65 (赞：2)

这题n的数据范围是1~100，所以可以直接用**暴力**。
### 思路：
先统计原数组中有多少个1，存在p中，然后枚举起点和终点，从起点遍历到终点，把p赋值给s，如果是1，s--，如果是0，s++。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101],s,p=0,maxn=0;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];//输入数组
        if(a[i]==1)p++;//统计原数组中有多少个1
    }
    for(int i=1;i<=n;i++){//枚举起点
        for(int j=i;j<=n;j++) {//枚举终点
            s=p;
            for(int k=0;k<j-i+1;k++) {
                if(a[i+k]==0)s++;else s--;//如果是1，s--，如果是0，s++
            }
            maxn=max(maxn,s);//和最大值比较
        }
    }
    cout<<maxn<<endl;//输出
	return 0;
}

```


---

## 作者：Lips (赞：2)

# $n^2$ 过万，暴踩标算。

看到楼下用了区间 $dp$ 的做法，而这个速度很快，也好写，所以窝就写惹暴力做法（

第一，对于每个区间 $(i,j)$，先考虑怎样以 $\operatorname{O}(1)$ 的效率求出 $1$ 的数量？我们发现，其实就是对这个区间进行求和！

### 前置芝士：前缀和

这里简略的说明一下，这个东西珂以在 $\operatorname{O(1)}$ 的效率求出某段区间的和。$sum_i$ 表示从 $1$ 到 $i$ 这段区间的和，便可得到递推公式：$sum_i=sum_{i-1}+a_i$，而对于区间 $[i,j]$ 求和，有公式：$sum_j-sum_{i-1}$。

------

回入正题

既然知道怎样快速求区间和，那怎样求出翻转后区间 $[i,j]$ 的和？珂以直接将这段区间的长度减区间 $[i,j]$ 翻转前的和！加上区间 $[1,i-1]$ 的和与 $[j+1,n]$ 的和，便是翻转区间 $[i,j]$ 后的 $1$ 的数量。

为了对代码理解方便，定义 $4$ 个函数：

- $\operatorname{add(i,j)}$ 

	求区间 $[i,j]$ 的和，直接套用前缀和的公式：$sum_j-sum_{i-1}$。
    
- $\operatorname{len(i,j)}$

	求区间 $[i,j]$ 的长度，很简单，直接为：$j-i+1$。
    
- $\operatorname{query(i,j)}$

	~~线段树？~~ 求区间 $[i,j]$ 翻转后的和，根据上文讲的，就是区间长度减原来的区间和：$\operatorname{len(i,j)}-\operatorname{add(i,j)}$。
    
- $\operatorname{all(i,j)}$

	求翻转区间 $[i,j]$ 后整个数列的和。可以先算出区间 $[i,j]$ 翻转后的和加上左区间 $[1,i-1]$ 与右区间 $[r+1,n]$ 的和：$\operatorname{query(i,j)}+\operatorname{add(1,i-1)}+\operatorname{add(r+1,n)}$。
    
这样，以 $\operatorname{O}(n^2)$ 的复杂度枚举区间 $[i,j]$，然后将翻转后数列总和取个最大值，输出。

$Code:$ 贴个高清代码，已经讲得很详细了~~并且方便您们抄~~

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=110;
int n,a[MAXN],sum[MAXN],ans;
int add(int i,int j)
{
	return sum[j]-sum[i-1];
}
int len(int i,int j)
{
	return j-i+1;
}
int query(int i,int j)
{
	return len(i,j)-add(i,j);
}
int all(int i,int j)
{
	return query(i,j)+add(1,i-1)+add(j+1,n);
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	for(register int i=1;i<=n;i++)
		for(register int j=i;j<=n;j++)
			ans=max(ans,all(i,j));
	printf("%d\n",ans);
	return 0;
}
```
完结撒花。



---

## 作者：小豆子范德萨 (赞：1)

- 发一个dp做法吧，首先这道题不是常规的dp，需要对问题进行转化。我们的目的是要通过翻转某一区间获得尽可能多的1，但是翻转也会带来一定的损失，之前的一些1会被翻转成0，如果翻转了一些不太好的区间，就会“得不偿失了”。
- 那么我们如何判断一次翻转是亏了还是赚了？可以引入一个数组b[i]记录每次反转对你当前有的“money”进行更新，如果a[i]为1，那么反转这次你的钱就会-1，如果a[i]为0，那么你的钱就会+1。那么如何让你在反转一个区间的值之后能赚到多的钱？就是求序列b的"最大连续子序列和"，这就转换为我们熟悉的不能再熟悉的问题了，时间复杂度O(n)。
- 当然也可以直接用i,j暴力枚举b的左端点和右端点，需要O（n^2）的复杂度，求b[i]+b[i+1]+...+b[j]需要O(n)的复杂度，总共的时间复杂度O（n^3）。

最大连续连续子序列求和的dp模板：
- 递归边界:dp[0] = b[0]
- 状态转移方程：
	
    以b[i]为结尾的最大连续子序列可以状态转移到两个子问题上：
    - 一是最大就是b[i]本身
    - 二是把当前元素并入前面一个元素的连续子序列中
	
代码如下(DP做法）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int a[maxn];		//输入数组 
int b[maxn];		
int dp[maxn];		//dp[i]表示以b[i]为结尾的最大连续子序列和 

int main() {
	int n;cin>>n;
	int cnt = 0;	//cnt原来的1的个数 
	for(int i = 0;i < n;i++) {
		cin>>a[i];
		if(a[i] == 1) {
			b[i] = -1;
			cnt++;			//计算输入的总共的1数 
		}
		else b[i] = 1;
	}
	
	dp[0] = b[0];		//dp边界 
	for(int i = 1;i < n;i++) {
		dp[i] = max(b[i],dp[i-1]+b[i]);
	}
	int k = 0;		//需要遍历所有的右端点来得到最大连续子序列和 
	for(int i = 1;i < n;i++) {
		if(dp[i] > dp[k]) {
			k = i;
		}
	}
	cout<<cnt+dp[k];			//原来有的1加最佳翻转后的多出来的1为答案 
	return 0;
}
```


---

## 作者：微分几何 (赞：0)

# 暴力枚举大法好！

# 前缀和
利用前缀和的思想，想知道 $a[i]$ 到 $a[j]$ 中 $1$ 的个数，就是前 $j$ 个数中 $1$ 的个数减去前 $i-1$ 个数中 $1$ 的个数。

# 求答案
我们用 $a0[i]$ 表示前 $i$ 个数中 $0$ 的个数，$a1[i]$ 表示前 $i$ 个数中 $1$ 的个数。

枚举 $i$ 和 $j$ ，在这个区间翻转之后 $1$ 的个数就是原来区间中 $0$ 的个数，整个区间的 $1$ 的个数就是：

$a0[j]-a0[i-1]+a1[i-1]+a1[n]-a1[j]$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a0[n+1],a1[n+1];
	a0[0]=0;a1[0]=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		a0[i]=a0[i-1];
		a1[i]=a1[i-1];
		if(x==0)	a0[i]++;
		else	a1[i]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int p0=a0[j]-a0[i-1],p1=a1[j]-a1[i-1];
			ans=max(ans,p0+a1[i-1]+a1[n]-a1[j]);
		}
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：fls233666 (赞：0)

首先考虑到此题 $n$ 的取值范围为 $1 \le n \le 100$，而反转操作只能进行一次，那么果断选择写 $O(n^2)$ 的暴力枚举算法。

具体来说，就是枚举要反转的区间的左右端点，然后统计区间内与区间外的 $0$ 和 $1$ 的个数。本人的详细思路如下：

1. 读入时统计初始时 $1$ 的个数，记为 $s$;
2. 分别枚举要反转的区间的左端点 $l$ 与右端点 $r$;
3. 在每次右端点 $r$ 枚举时，用一个初始值为 $0$ 的变量 $g$ 进行统计，遇到 $1$ 则 $g-1$ ( 反转后 $1$ 变为 $0$ )，遇到 $0$ 则 $g+1$ ( 反转后 $0$ 变为 $1$ );
4. 每次枚举区间时，寻找 $g+s$ 的最大值，记为 $ans$，即答案。

实现得到代码如下：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
int n,a[111],s,g,ans;
int main(){
	scanf("%d",&n);
	for(rgt i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1)
			s++;  //统计初始 1 的个数
	}
    
	for(rgt l=1;l<=n;l++){  //枚举左端点
		g=0;   
		for(rgt r=l;r<=n;r++){   //枚举右端点
			g+=a[r]==1?-1:1;  //统计反转导致 1 的个数的变化量
			ans=max(ans,g+s);  //比较大小，确定答案
		}
	}
    
	printf("%d",ans);  
	return 0;
}
```


---

## 作者：TLMPEX (赞：0)

思路：~~这道题很简单~~，枚举起点和终点，再模拟即可，具体思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[101];
int main(){
	int i,j,n,s,l=0,z=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k[i];
		if(k[i]==1)l++;//如果是1则l加一
	}
	for(i=1;i<=n;i++){
		s=l;//初始化，每次置为l
		for(j=i;j<=n;j++){
			if(k[j]==1)s--;//如果k[j]为1翻过来则为0目前有的1数减一
			else s++;//如果k[j]为0翻过来则为1目前有的1数加一
			z=max(z,s);//更新最大值
		}
	}
	cout<<z;
}
```


---

