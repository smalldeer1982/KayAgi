# Find Maximum

## 题目描述

Valera 有一个 $n$ 个数的 **非负整数** 数组 $a$ ，其元素分别为 $a_0,a_1,\cdots,a_{n-1}$。同时有一个函数 $f(x)=\sum_{i=0}^{n-1}a_i\cdot bit(i)$，$bit(i)$ 指的是数字 $x$ 在二进制中第 $i$ 位的值是否为 1。

举个例子，当 $n=4,x=11(11=2^0+2^1+2^3)$ 时，$f(x)=a_0+a_1+a_3$。

对于所有 $0\le x \le m$ 的整数 $x$ ，请求出 $f(x)$ 的最大值。

## 说明/提示

- $1 \le n \le 10^5$

- $0 \le a_i \le 10^4$

- $0\le s_i \le 1$

## 样例 #1

### 输入

```
2
3 8
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
17 0 10 2 1
11010
```

### 输出

```
27
```

# 题解

## 作者：WaterSky (赞：3)

# [CF353C Find Maximum](https://www.luogu.com.cn/problem/CF353C)

这是挺有意思的一道题。

-----
## 算法分析
这题的算法也不难想，就是**贪心**与**动态规划**。
## 贪心：
由于其中的元素只有 **$0$ 和正整数**，那么我们就能得出以下结论：
- 当这个元素为 $0$ 时，**不选**，选了就是浪费空间。
- 否则能尽量多选就**尽量选**，使利益**最大化**。  

所以根据**第二条结论**，我们需要将 $f$ 数组初始化，设为**没有 $s$ 的限制的最大值**，即全部加起来，这一步我们可以用**前缀和**来处理。

## 动态规划：
根据以上推论，能得出以下状态转移式：
$$f_i = \max(f_i,f_{i-1}+a_i s_i)$$

其中，$f_i$ 表示前 $i$ 个在**空间与价值最大化时的价值**。

显而易见，最终答案就是 $f_n$。
## 实现：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],s[100005],dp[100005];
char S[100005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
        	cin>>a[i],s[i]=s[i-1]+a[i]; //前缀和处理

	for(int i=1;i<=n;i++) 
        	cin>>S[i];

	for(int i=1;i<=n;i++)
		if(S[i]==1) dp[i]=s[i-1]; //预处理

	for(int i=1;i<=n;i++) 
		dp[i]=max(dp[i],dp[i-1]+a[i]*S[i]); //状态转移
        
	cout<<dp[n];//得出结论
	return 0;
}
```
感谢管理员审核！

---

## 作者：Jr_Zlw (赞：2)

## 贪心

因为  $a_i\geq 0$，所以明显多选不亏。

可以从高到低位考虑，改动原来的数必须往小了改，所以改动的最高位必须是  $1$  改成  $0$。如果选择将某一个  $1$  变为  $0$，那么后面的数无论怎么改都是小于原数的，所以全部填上  $1$  就可以了。

所以具体来说做一个从低位到高位的前缀和，枚举每一个为  $1$  的位，高位记录从后面到这一位的答案，低位查询前缀和得到改变这一位的答案，取最大值输出即可。

时间复杂度  $O(n)$。

代码：

```
#include<cstdio>
#include<cstring>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
inline int read()
{
	int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
template<typename T> inline T max(const T&x,const T&y){return x<y?y:x;}
const int N=1e5+10;char s[N];int a[N],n;
int main()
{
	n=read();rep(1,n,i)a[i]=a[i-1]+read();scanf("%s",s);
	int res=0,ans=0;for(int i=n-1;~i;--i)if(s[i]=='1'){ans=max(ans,res+a[i]);res+=a[i+1]-a[i];}
	printf("%d\n",max(res,ans));return 0;
}
```


---

## 作者：Graphcity (赞：1)

## 思路

我们设最终答案为 $ans$，$ans=\sum_{i=0}^{n-1}2^i\cdot k_i$。

如果放开 $0\le x \le m$ 的限制，答案肯定就是把所有 $k_i$ 全部填满，也就是把所有 $a_i$ 全部相加。

同理，如果我们在 $s_i=1$ 的时候故意填上值为 0 的 $k_i$，那么最优的方案肯定就是把 $k_0\sim k_{i-1}$ 全都填上 1。设 $sum_i=\sum_{i=0}^ia_i$，$f_i$ 表示 **仅考虑前 $i$ 位** 时的最大答案，就可以对 $f_i$ 赋初值

$f_i=[s_i=1]\times sum_{i-1}$

除了这种特殊情况，其它情况则必须得受到 $s$ 的限制，正常填写即可，此时

$f_i=\max(f_i,f_{i-1}+a_i\times s_i)$

这就是 **动态规划** 的过程。

## 代码

代码十分简单，这里贴上主函数的部分：

```cpp
scanf("%d",&n);
for(int i=1;i<=n;++i) scanf("%d",&a[i]);
for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
for(int i=1;i<=n;++i)
{
    char ch; cin>>ch;
    s[i]=ch-'0';
}
for(int i=1;i<=n;++i) if(s[i]==1) f[i]=sum[i-1];
for(int i=1;i<=n;++i) f[i]=max(f[i],f[i-1]+a[i]*s[i]);
printf("%d",f[n]);
return 0;
```

---

