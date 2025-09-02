# [USACO16JAN] Subsequences Summing to Sevens S

## 题目描述

Farmer John 的 $N$ 头奶牛站成一排，这是它们时不时会做的事情。每头奶牛都有一个独特的整数 ID 编号，以便 Farmer John 能够区分它们。Farmer John 希望为一组连续的奶牛拍照，但由于童年时与数字 $1 \ldots 6$ 相关的创伤事件，他只希望拍摄一组奶牛，如果它们的 ID 加起来是 7 的倍数。

请帮助 Farmer John 确定他可以拍摄的最大奶牛组的大小。

## 说明/提示

在这个例子中，$5+1+6+2+14 = 28$。

## 样例 #1

### 输入

```
7
3
5
1
6
2
14
10```

### 输出

```
5```

# 题解

## 作者：人殇物已非 (赞：242)

### 2021.7.30 update:

添加了 $\LaTeX$ ，补充了被 hack 的问题。
~~（实在没想到4年前的代码会被hack)~~

（这题解审核也太严了，好辛苦啊>_<）

**首先：**

这个题肯定不能直接模拟，你要是暴力枚举端点，看看数据范围。。。。$50000^3$ 下辈子都过不去。

**然后：**

我们就想到了一个求区间和的好东西：

**当然是 “前缀和” 了啊！**

我们只要先预处理前缀和，然后用 ```pre[r]-pre[l]``` 就是区间和了，这样只要再拿他 $\bmod$ $7$ 就可以判断了，最后求最大长度就可以了！

**发现不行。。。。 $n^2$ 的复杂度啊。。。预计得分 $70$ 。**

**改思路！**

我们可以先直接求 $\bmod$ $7$ 意义下的前缀和，然后只要看看余数的重复就可以了。

**这里需要用到一个小定理：若两个数相减 $(\bmod$ $7=0)$ ，那么这两个数 $\bmod$ $7$ 的余数一定相同！！（很好证明，自己有兴趣不妨去试试证明）**

这样的话瞬间就简单了。

我们只要求出相同的一个余数第一次和最后一次之间的长度即是最长长度！
但是我们不知道哪个余数最长，所以：

枚举 $0$ ~ $6$ 共 $7$ 个余数各自的最长长度，再在他们 $7$ 个里找最长的！

**最后附上代码（每步都有解释哦！）**


```cpp
 #include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
int pre[maxn];
int n,len,mx=-1;
int first[7],last[7];//%7的余数为0~6,所以开7的数组就可以了； 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>pre[i];
		pre[i]=(pre[i]+pre[i-1])%7; //%7意义下的前缀和 ，就变成了前缀和%7的余数；		
	}
	for(int i=n;i>=1;i--)//(pre[i]是当位置为i时 前缀和%7的余数） 
		first[pre[i]]=i;   //第一次出现pre[i]这个余数的时候的位置为i ；
	//倒着扫一遍 不断更新最后就是这个余数第一次出现； 
	first[0]=0;//从头加到i是7的倍数的情况下，需要把0的第一次出现设为0，即把整个区间[1,i]选上了。
	for(int i=1;i<=n;i++)
		last[pre[i]]=i;//最后一次出现pre[i]这个余数时位置为i； 
		
	for(int i=0;i<=6;i++)   //这里是看哪个余数的长度最大，last[i]-first[i]就是余数i的最大长度
	//(最后一次出现减第一次出现 显然是最长的)
	//两个位置相减就是长度；因为是前缀和(前缀和为【i+1，j】的区间,所以j-i即为区间的长度） 
	//这里不是一般的 j-i+1(末位置 减 首位置+1） 为长度，紧扣前缀和的定义！！ 
	mx=max(last[i]-first[i],mx);
	//前缀和求原区间长度是 j-i；一般的区间长度是 j-i+1； 
	cout<<mx<<endl;
} 
```

---

## 作者：「已注销」 (赞：68)

前缀和，$s[i]$表示$[1,i]$的和，$[l,r]$的和就可以拆成$s[r]-s[l-1]$，当$s[r]$和$s[l-1]$模$7$相同时，区间就能被$7$整除，求出前缀和每个余数对应的最小的$l-1$和最大的$r$从而算出最长区间长度，可以边读入边记录。端点模$7$为$0$到$6$的最长区间长度的最大值就是答案，注意判断区间是否存在
用滚动数组，时间$O(n)$，空间常数
```
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a,s,l[]={0,-1,-1,-1,-1,-1,-1},r[7],ans; //s是前缀和，l[i]存%7为i的最小l-1,r[i]存%7为i的最大r,-1代表没有%7为i的前缀和,当有任意前缀和s[x]%7等于0时,最长区间长度就是x
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a);
		s=(s+a)%7;
		if(l[s]==-1)l[s]=i;
		r[s]=i;
	}
	for(int i=0;i<7;++i)if(l[i]!=-1)ans=max(ans,r[i]-l[i]);
	printf("%d",ans);
}
```

---

## 作者：天有不测风云 (赞：15)

本题让我意识到了卡常的重要性。

前置芝士：[前缀和](https://oi-wiki.org/basic/prefix-sum/#_1)。

### 思路

题目让我们求一个区间，这个区间的和能被 $7$ 整除。由于是 $10^6$ 的数据范围，肯定不能直接暴力枚举。

此时我们就需要一个东西——前缀和。前缀和就是数组前几项的和。比如假设我们现在需要求出数组第 $2$ 项与第 $5$ 项之间元素的和，就可以用数组前 $5$ 项的和减去前 $2$ 项，在 $O(1)$ 的时间复杂度内完成区间求和。

```cpp
for (register int i = 1; i <= n; ++i) {
	a[i] = read<int>();
	b[i] = a[i] + b[i - 1];
}
```

像这样就可以求出 $a$ 数组的前缀和数组：$b$ 数组。

按照一开始这个思路，我们就可以写出这样的代码：

```cpp
signed main() {
	int n;
	n = read<int>();
	for (register int i = 1; i <= n; ++i) {
		a[i] = read<int>();
		b[i] = a[i] + b[i - 1]; //计算前缀和
	}
	int ans = 0;
	for (register int i = 1; i <= n; ++i) {
		for (register int j = i + ans; j <= n; ++j) {
			if ((b[j] - b[i - 1]) % 7 == 0) {
				ans = j - i + 1;
			}
		}
	}
	write(ans);
	return 0;
}
```

然而……

![](https://cdn.luogu.com.cn/upload/image_hosting/oydbnmlr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

很明显，我们上面的做法太过暴力，导致 T 了一个点。~~此时吸氧即可通过。~~

但是，会发现，只超时了一点点。所以，下面介绍~~常用~~卡常操作之一：**循环展开**。

> **循环展开**，英文中称（Loop unwinding 或 loop unrolling），是一种牺牲程序的尺寸来加快程序的执行速度的优化方法。可以由程序员完成，也可由编译器自动优化完成。
>
> 循环展开通过将循环体代码复制多次实现。

循环展开可以充分地发挥 CPU 多核性能。

### 代码

加了循环展开之后的 AC 代码：

```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;

template<typename T> inline T read() {
	T X = 0; bool flag = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') flag = 0; ch = getchar();}
	while (ch >= '0' && ch <= '9') {X = (X << 1) + (X << 3) + ch - '0'; ch = getchar();}
	if (flag) return X;
	return ~ (X - 1);
}

template<typename T> inline void write(T X) {
	if (X < 0) {putchar('-'); X = ~ (X - 1);}
	int s[50], top = 0;
	while (X) {s[++top] = X % 10; X /= 10;}
	if (!top) s[++top] = 0;
	while (top) putchar(s[top--] + '0');
	putchar('\n');
	return;
}

int a[1000005], b[1000005];

signed main() {
  int n;
  n = read<int>();
  for (register int i = 1; i <= n; ++i) {
    a[i] = read<int>();
    b[i] = a[i] + b[i - 1];
  }
  int ans = 0;
  for (register int i = 1; i <= n; ++i) {
    int num = n - 4;
    register int j;
    for (j = i + ans; j <= num; j += 4) {//循环展开
      if ((b[j] - b[i - 1]) % 7 == 0) ans = j - i + 1;
      if ((b[j + 1] - b[i - 1]) % 7 == 0) ans = j - i + 2;
      if ((b[j + 2] - b[i - 1]) % 7 == 0) ans = j - i + 3;
      if ((b[j + 3] - b[i - 1]) % 7 == 0) ans = j - i + 4;
    }
    for (; j <= n; ++j)
      if ((b[j] - b[i - 1]) % 7 == 0) ans = j - i + 1;
  }
  write(ans);
  return 0;
}
```

上面那个点以 961ms 通过。

---

## 作者：Utilokasteinn (赞：12)

[Link](https://www.luogu.com.cn/problem/P3131)

再来一篇 DP 的题解。

设 $f_{i,j}$ 表示以第 $i$ 个数结尾的区间，且区间和模 $7$ 等于 $j$ 的区间长度的最大值。

不难发现，加上一个新的数 $x$ 就可以使长度加 $1$。所以方程为：

$$f_{i,(j+x)\%mod}=f_{i-1,j}+1$$

显然，前提是 $f_{i-1,j}+1$ 大于 $0$ ，否则该区间的长度为 $0$ ，区间和肯定不是 $j$。

当然，也可以以自己为开头构成一个新的区间。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s; 
}
int n,f[50005][7],ans;
main()
{
    n=read();
    for(int i=1,x;i<=n;i++)
    {
        x=read();
        for(int j=0;j<7;j++)
            if(f[i-1][j])
                f[i][(j+x)%7]=f[i-1][j]+1;
        f[i][x%7]=max(f[i][x%7],1);
    }
    for(int i=1;i<=n;i++)
		ans=max(ans,f[i][0]);
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：听取MLE声一片 (赞：11)

这道题有很多人被 `hack` 了，就来交一发题解。

首先还是按照被 `hack` 的方法去做，算出每一位前缀和并对 `7` 取模。

这里用到的一个规律：

如果 $a \equiv b(mod\ c)$ 则 $(a-b)\equiv 0(mod \ c)$。

例如 $a=10,b=3,c=7$ 时，满足上述规律，证明起来比较容易，这里就不赘述。

做法就是枚举 `0` 到 `6` 的每一个余数，然后从前扫一遍，记录下这个余数最前出现的位置 `s`；再从后扫一遍，记录下它最后出现的位置 `t`，显然长度就是 `t-s` 因为和为 `7` 倍数的一段**不包括** `s` 所以不需要加一。

下面是**被hack**的代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[500010],b[500010],ans; 
int main()
{
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=(a[i]+b[i-1])%7;
	}
	for(int i=0;i<=6;i++){
		int s=0,t=0;
		for(int j=1;j<=n;j++)
			if(b[j]==i){
				s=j;
				break;
			}
		for(int j=n;j>=1;j--)
			if(b[j]==i){
				t=j;
				break;
			}
		ans=max(ans,t-s);
	}
	cout<<ans;
	return 0;
}

```

然后就有人提出了 `hack` 数据。

例如输入 `1 7`,正确输出为 `1`，代码输出为 `0`;

输入 `2 3 4`，正确输出为 `2`，代码输出为 `0`。

找一下规律，我们发现如果和整除七的一段是从头开始的，而上面也说过，和为 `7` 倍数的一段**不包括** `s`，所以就没有办法统计答案从头开始的数据。

怎么办呢？很简单，只需要把内层循环的 `j` 改成从 `0` 开始就可以解决从第一位开始的情况。

这里代码就不放了，直接在上面修改即可。

---

## 作者：言琢დ (赞：5)

**感谢认真负责的管理 @SSerxhs 指出本文中的错误。**

本题中仅涉及加法和取模运算，因此可以直接把读入的序列取模并找到前缀和。

考虑一个平凡的结论：

$$sum(l,r)\mod7=0$$

相当于（其中 $s[i]$ 表示 $1\sim i$ 的前缀和）

$$s[r]\equiv s[l-1]\mod~7$$

可以考虑统计出每一个余数 $0\dots6$ 中最左端点的位置和最右端点的位置 `L[]` 和 `R[]`。

对每一个余数而言，`R[]-L[]` 一定是最长的，而所有余数中的最优解，不难发现就是全局的最优解。

```cpp
#include<cstdio>
inline int in();
inline void wr(int);
const int N=(int)5e4+5;
int s[N],L[7],R[7];
inline int mx(int,int);
inline int mn(int,int);
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("3131.in","r",stdin);
	freopen("3131.out","w",stdout);
#endif
	register int n=in();
	for(register int i=0;i<7;++i)
		L[i]=N<<1;
	L[0]=0;
	for(register int i=1;i<=n;++i){
		s[i]=(s[i-1]+in())%7;
		if(L[s[i]]==(N<<1))L[s[i]]=i;
		R[s[i]]=i;
	}
	register int ans=0;
	for(register int remainder=0;remainder<7;++remainder){
		if(R[remainder]==0||L[remainder]==(N<<1))
			continue;
		ans=mx(ans,R[remainder]-L[remainder]);
	}
	wr(ans),putchar('\n');
}
inline int mx(int x,int y){
	return x>y?x:y;
}
inline int mn(int x,int y){
	return x<y?x:y;
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：_•́へ•́╬_ (赞：3)

# 我居然傻到用DP！
### $ans[i][j]$表示以第$i$个数字结尾并且%7等于$j$的最大的区间长度
```cpp
#include<bits/stdc++.h>
#define rpt(n) for(register int ttxyc=0;ttxyc<n;++ttxyc)//宏定义
#define inr int//手残人士用
using namespace std;
int n,a,ans[50000][7];
main()
{
    scanf("%d%d",&n,&a);
    ans[0][a%7]=1;//顺便把第一个给特殊处理了
    for(register inr i=0;i<n-1;++i)
    {
        scanf("%d",&a);//在线读入
        for(register inr j=0;j<7;++j)
            if(ans[i][j])//从某个地方开始取，可以到j
                ans[i+1][(j+a)%7]=ans[i][j]+1;//再取一个
        ans[i+1][a%7]=max(ans[i+1][a%7],1);//只取这一个的答案
    }
    int maxn=0;//最后再取一遍最大值，因为不一定一直取到最后一个最好
    for(register inr i=0;i<n;++i)maxn=max(maxn,ans[i][0]);
    printf("%d",maxn);//输出
}
```

---

