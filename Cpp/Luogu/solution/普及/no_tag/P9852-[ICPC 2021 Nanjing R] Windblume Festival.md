# [ICPC 2021 Nanjing R] Windblume Festival

## 题目描述

蒙德城的风花节即将到来！人们正在为巴巴托斯和他们所爱的人准备风花。风花节也是一个改善人际关系的机会。

在节日期间，每年都会玩一个由代理团长琴发明的著名游戏。在游戏中，编号从 $1$ 到 $n$ 的 $n$ 个玩家围成一个圈，每人手中持有一个整数。每一轮，将有一名玩家被移除。游戏将在只剩下一名玩家时结束。

在每一轮中，设 $k$ 为剩余玩家的数量，$a_i$ 为玩家 $i$ 手中的整数。选择两个相邻的玩家 $x$ 和 $(x \bmod k + 1)$，并将玩家 $(x \bmod k + 1)$ 移出游戏。然后玩家 $x$ 的整数将从 $a_x$ 变为 $(a_x - a_{x \bmod k + 1})$。在本轮中，玩家 $y$ 在下一轮中将成为玩家 $(y - 1)$，对于所有 $x < y \le k$，尽管他们手中的整数不会改变。

琴想知道通过在每轮中最优地选择玩家，最后剩下的玩家手中可能持有的最大整数。

## 说明/提示

对于第一个样例测试用例，遵循如下策略，其中下划线的整数是每轮中被选中的玩家持有的整数。

$\{\underline{1}, -3, 2, \underline{-4}\}$（选择 $x = 4$）$\to$ $\{-3, \underline{2, -5}\}$（选择 $x = 2$）$\to$ $\{\underline{-3, 7}\}$（选择 $x = 2$）$\to$ $\{10\}$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
4
1 -3 2 -4
11
91 66 73 71 32 83 72 79 84 33 93
12
91 66 73 71 32 83 72 79 84 33 33 93
13
91 66 73 71 32 83 72 79 84 33 33 33 93
1
0
```

### 输出

```
10
713
746
779
0
```

# 题解

## 作者：wylnh (赞：9)

**做法**：**模拟**

**题意**：一个长为 $n$ 的环形数组，每次操作对于任意 $i,j$，删除 $a_j$，将 $a_i$ 减去 $a_j$，使得最后剩余的数最大。

**思路**：由题意可知，一次操作即将两数合并为两数之差。因此假设按操作先后顺序， $a_1$ 表示最后一个操作的数， $a_n$ 表示第一个操作的数，题意即为将 $a_1$ 到 $a_n$ 连成一个算式，在每个数之前添加一个符号，使得算式值最大。
- 对于第 $i$ 个数，若想让其符号为 $+$，则需将其与第 $i-1$ 个数做一次操作，否则直接操作。
- 比如想构造 $a_1-a_2-a_3+a_4+a_5$，则：
  - 先从前往后找第一个符号为 $+$ 的数，即 $a_4$，那么就将其与 $a_3$ 做一次操作，得到 $a_1,a_2,a_3-a_4,a_5$。
  - 同样找到符号为 $+$ 的 $a_5$，将其与 $a_3-a_4$ 做一次操作，得到 $a_1,a_2,a_3-a_4-a_5$。
  - 最后剩下的都是 $-$ 号了，就直接依次进行操作，得到 $a_1-a_2-(a_3-a_4-a_5)$，即 $a_1-a_2-a_3+a_4+a_5$。
- 所以只需要选择相邻的数，前一个为 $+$ 号，后一个为 $-$ 号，两两做差，枚举最大值即可。
- 注意：当 $n=1$ 时，直接输出 $a_1$，无需进行操作。

**代码**：
```c
#include<bits/stdc++.h>
#define ll long long
#define INF -0x7f7f7f7f
using namespace std;
const int N=1e6+10;
ll T,n,a[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		ll sum=0,ans=INF;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=abs(a[i]);//统计最大可能达到的值
		}
		if(n==1){//特判
			cout<<a[1]<<"\n";
			continue;
		}
		for(int i=1;i<=n;i++){
			ans=max(ans,sum-abs(a[i])-abs(a[i%n+1])+a[i]-a[i%n+1]);//sum减去两数的绝对值，加上做差后的值，即为每次操作的贡献
		}
		cout<<ans<<"\n";
	}
	
	return 0;
}
```

**后记**：如有错误或不足请  _dalao_  指出。（~~点个![/z](https://cdn.luogu.com.cn/upload/pic/62236.png)再走呀！~~）

---

## 作者：wangbinfeng (赞：4)

[![](https://img.shields.io/badge/题目-P9852:Windblume_Festival-green)
![](https://img.shields.io/badge/难度-暂无评定（入门）-red)
![](https://img.shields.io/badge/考点-数学(math)-blue)
![](https://img.shields.io/badge/题型-传统题-yellow)](https://www.luogu.com.cn/problem/P9852)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------
题意为：对于 $n$ 个数字，每次操作将其中两个数相减并合并为一个数，问这个数最大是多少。

首先，对于 $\forall a<0,b>0$ 有 $a-b<a,\lvert a-b\rvert>a$。对于 $\forall a>0,b<0$ 有 $a-b>a,\lvert a-b\rvert>a$。证明略。其中  $\forall$ 意为任意，如不理解可忽略。

如果输入数据中**同时存在正数和负数**，设正数和负数数量分别为 $n,m$，则可以用 $1$ 个正数减去 $m-1$ 个负数，用 $1$ 个负数减去 $n-1$ 个正数，再用唯一的正数减去唯一的负数。故答案应当为**其所有数绝对值之和**。

当输入数据**全为正数**时，我们很容易想到将其中一组正数减成负数，然后转换成第一种情况。因此，答案应当为**前 $n-1$ 大的数之和减去最小数**。负数同理，答案为**前 $n-1$ 小的数的绝对值之和减去最大数的绝对值**。

当输入**有零**时，其余数字有正有负同第一组。否则若全为正数可用零随意减一正数变为负数，全为负数同理故这种情况答案与第一种情况相同，即**其所有数绝对值之和**。

下面是用数学公式的推导（由于公式有些庞大，不保证可以正常显示，可以使用[博客](https://www.luogu.com.cn/blog/wangbinfeng/solution-p9852)查看）：

$$
\text{令所有正数存在 a 中，数量为 n；所有负数存在 b 中，数量为 m 。零的数量为 q 即}n,m,q\isin\N,\forall 1\le i\le n,a_i>0,\forall 1\le j\le m,b_j<0.    \\
\text{令a,b中元素按其绝对值升序，即}\forall 2\le i\le n,a_i>a_{i-1},\forall 2\le j\le m,b_j<b_{j-1}.     \\

\text{ans} = \begin{cases}
   a_1 &&\text{if}&& n=1,m=0,q=0  \\
   b_1 &&\text{if}&& n=0,m=1,q=0  \\
   \lparen a_1-b_2-b_3-...-b_m \rparen -\lparen b_1-  a_2-a_3-...-a_m \rparen &&\text{if}&& n\ge 1,m\ge 1,q=0  \\
   a_n-\lparen a_1-a_2-a_3-...-a_{n-1}\rparen &&\text{if}&& n\ge 1,m=0,q=0\\
   b_n-\lparen b_1-b_2-b_3-...-b_{n-1}\rparen &&\text{if}&& n=0,m\ge1,q=0\\
   a_1-\lparen0-a_2-a_3-...-a_n\rparen-b_1-b_2-...-b_m &&\text{if}&& q\neq0\\
\end{cases}\\
\text{可以推出：}\\
\text{ans} = \begin{cases}
   a_1 &&\text{if}&& n=1,m=0,q=0  \\
   b_1 &&\text{if}&& n=0,m=1,q=0  \\
   \lvert a_1\rvert+\lvert a_2\rvert+...+\lvert a_n\rvert+\lvert b_1\rvert+\lvert b_2\rvert+...+\lvert b_m\rvert &&\text{if}&& n\ge 1,m\ge 1,q=0  \\
   \lvert a_2\rvert+\lvert a_3\rvert+...+\lvert a_n\rvert -\lvert a_1\rvert &&\text{if}&& n\ge 1,m=0,q=0\\
   \lvert b_2\rvert+\lvert b_3\rvert+...+\lvert b_n\rvert -\lvert b_1\rvert &&\text{if}&& n=0,m\ge1,q=0\\
   \lvert a_1\rvert+\lvert a_2\rvert+...+\lvert a_n\rvert+\lvert b_1\rvert+\lvert b_2\rvert+...+\lvert b_m\rvert &&\text{if}&& q\neq0\\
\end{cases}\\
$$

------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long      //这并不是一个好习惯，不建议使用
int a,n,t,sum,minn=0x7ffffffffffffff;
bool z,f;         //分别表示输入数据中是否存在正数/负数
inline int read(){       //这是快读（即快读读入，速度远大于scanf和cin），建议背过
	int x=0,f=1;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-f;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
signed main(){           //signed=signed int=int
	for(t=read();t--;f=z=false,sum=0,minn=0x7ffffffffffffff){//循环t次，并且多测清空
    	n=read();
		for(int i=1;i<=n;i++){
			a=read();
			if(a==0)z=f=true;
			else if(a>0)z=true;
			else f=true;
			sum+=abs(a);
			minn=min(minn,abs(a));
		}
		if(n==1){printf("%lld\n",a);continue;} //不要忘记这行
		if(z&&f)printf("%lld\n",sum);        //有正有负（或有零）
		else printf("%lld\n",sum-2*minn);	   //只有正/负
  }
}

```

---

## 作者：RyanCh (赞：2)

思路：

考虑如下两种情况：

1. 全为负数或全是正数：我们发现可以将全是负数转为全是正数，此时我们必须舍弃一个数并将其减去。
2. 负数和正数相结合：我们考虑对于每一个下一位是负数的正数，都可以将其后面的正数和负数减去，最后可以转换为所有数的绝对值之和。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
#define int long long
int T, n, a[N];
signed main() {
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld", &n);
		if(n == 1) {
			scanf("%lld", &a[0]);
			printf("%lld\n", a[0]);
			continue;
		}
		for(int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		bool pd = 1;
		for(int i = 1; i <= n; i++)
			if(a[i] > 0) {
				pd = 0;
				break;
			}
		if(pd)
			for(int i = 1; i <= n; i++)
				a[i] = abs(a[i]);
		int minn = INT_MAX, sum1 = 0, sum2 = 0, ans;
		for(int i = 1; i <= n; i++)
			minn = min(minn, a[i]), sum1 += a[i], sum2 += abs(a[i]);
		if(minn < 0) ans = sum2;
		else ans = sum1 - minn * 2;
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：RAND_MAX (赞：1)

## 题目大意
$n$（$1 \le n\le 10^6$）个数围成一个环，每次可以将相邻两个数替换为两数之差，问最后剩余的数的最大值。
## 解题思路
设本次操作的两个数分别为 $a$ 与 $b$。

注意到 $a$ 与 $b$ 也是由一堆数相减而成的，根据~~小学~~数学知识可知，$a-(b-c)$ 等同于 $a-b+c$。所以最后留下的数**一定**是在这 $n$ 个数之间添加 $+$ 和 $-$ 所得的结果且至少有一个 $+$ 和一个 $-$（算式开头默认加号）。

分三种情况讨论：

### $n$ 个数有非正数有非负数

此时只需在负数前加减号，在正数前加减号即为答案。

结果为 $\sum a_i $。

### $n$ 个数全都是非负数

此时只需将最小值前加减号，其余加加号即为答案。

设最小值所在下标为 $x$，则结果为 $a_1+\dots+a_{x-1}-a_x+a_{x+1}+\dots+a_n$。

即为 $\sum a_i -2a_x$。

### $n$ 个数全都是非正数
此时只需将最大值前加加号，其余加减号即为答案。

设最大值所在下标为 $x$，则结果为 $-a_1-\dots-a_{x-1}+a_x-a_{x+1}-\dots-a_n$。

即为 $2a_x-\sum a_i $。

------------
后两种情况可简化为 $\sum \left| a_i \right|-2\left| a_x \right|$。

## 代码
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
int T,n,x,sum,minn,fl1,fl2;
void init()//初始化
{
	x=0;
	sum=0;
	minn=inf;
	fl1=0;
	fl2=0;
} 
signed main()
{
	cin>>T;
	while(T--)
	{
		init();
		cin>>n;
		if(n==1)
		{
			cin>>x;
			cout<<x<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			sum+=abs(x);//求和
			minn=min(minn,abs(x));//最小值
			if(x<=0)//判断有无非正数
			{
				fl1=1;
			}
			if(x>=0)//判断有无非负数
			{
				fl2=1;
			}
		}
		if(fl1&&fl2)//如果非正非负数都有
		{
			cout<<sum<<endl;
		}
		else//否则全为非负数或全为非正数
		{
			cout<<sum-(minn<<1)<<endl;
		}
	}
 	return 0;
}
```

---

## 作者：pMatrix (赞：0)

有一定博弈和数论的味道，当然并不是。
## 分析
既然是一个圆环，所以我会旋转这个环使其更加易于分析。

首先考虑正数（或者等于 $0$）与负数都存在的情况，为了便于描述，我用 $1$ 和 $0$ 来代替它们。例如：$10100111011$。不难发现，我们可以通过一系列的减法，使得除了位置 $1$ 以外的所有正数减到离它们最近的、左边的负数中，也就是变成了：$10000$。再通过不断选取位置 $1$，将负数全都减到其中，这样，负数通过一次减法变成正数，而其他正数通过两次减法又没有发生变化。

结论显而易见，$ans=\sum\lvert a_{i}\rvert$。

有了上面的结论，我们可以考虑既有正数又有负数的情况了。不妨先考虑全是正数，可以联想到，我们不可避免的要去选择一个数，其实在最终的答案里符号为负。而一旦有了这个负数，我们就不必要再去选取另一个数了。例如 $n=4$，我们选取 $a_{2}$，先使其右边的数都减到其中，也就是 $a_{1}，a_{2}-a_{3}-a_{4}$。再做一次减法，变成 $a_{1}-a_{2}+a_{3}+a_{4}$。这样就保证了结果尽可能的大。

如何选取这个数？显然选取绝对值最小最好——别忘了还有全是负数的情况。对于负数，我们应该使其在结果中有且仅有一个数不变号，还是 $n=4$，我们通过不断选位置 $1$，其实变成 $a_{1}-a_{2}-a_{3}-a_{4}$，其中 $a_{1}$ 是绝对值最小的数。

这两种情况的结论也就在原有的 $ans$ 的基础上，再减去两倍的 $\min(\lvert a_{i}\rvert)$。
## 代码
重要提醒，$n=1$ 在我的代码中需要特判，否则会不小心把负数当成正数输出。另外，看到 $a_{i}$ 的取值范围这么大，建议无条件开 `long long`，内存绝对够用的。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN = 1e6 + 5;
int t, n;
long long a[MAXN], ans, MIN;
int cnt1, cnt2;
int main()
{
	cin >> t;
	while (t--)
	{
		ans = 0; MIN = 0x7fffffffffffffff; cnt1 = cnt2 = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			if (a[i] < 0)cnt1++;
			else cnt2++;
		}
		if (n == 1)
		{
			cout << a[1] << "\n";
			continue;
		}
		for (int i = 1; i <= n; i++)ans += abs(a[i]);
		if (cnt1 == n || cnt2 == n)
		{
			for (int i = 1; i <= n; i++)if (abs(a[i]) < MIN)MIN = abs(a[i]);
			ans -= 2 * MIN;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：枫原万叶 (赞：0)

# 题解 P9852

## 分析

简化一下题面，就是只使用减法使整个数列所得的值最大。

我们可以想到的是如果出现了正数和负数的，那么最大值一定是所有数的绝对值之和，因为只要把所有数减到负数上最后再用一个正数减去负数就可以得到了。

对于全是正数或者全是负数的其实没有什么差别，前者差了一个负数后者差了一个正数，所以我们需要使用一个绝对值最小的数造出一个当前数列所需的数，其实就是所有数的绝对值之和减去绝对值最小的那个数的乘二就可以了。

思路和代码都不难，重要的是理解题目意思。最后记得特判长度为一的情况，不然会被卡。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e6+10;
ll arr[MAXN],ans,minn,maxx;
int t,n,c1,c2;

int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 	cin>>t;
	while(t--){
		cin>>n;
		c1=c2=ans=0;
		minn=LLONG_MAX;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
			if(arr[i]>=0) c1++;
			else c2++;
		}
		if(n==1){
			cout<<arr[1]<<endl;
			continue;
		}
		
		if(c1==n||c2==n){
			for(int i=1;i<=n;i++) arr[i]=abs(arr[i]);
			for(int i=1;i<=n;i++)
				minn=min(minn,arr[i]),ans+=arr[i];
			cout<<ans-2*minn<<endl;
		}else{
			for(int i=1;i<=n;i++)
				ans+=abs(arr[i]);
			cout<<ans<<endl;
		}
		
	}
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{43}$ 篇题解。

# $\mathbf{0x01}$ 承

每次将环形数组的相邻两位变为两位之差，最大化剩下的数。

# $\mathbf{0x02}$ 转

看了之前的题解很多都在分类讨论，其实可以先用以下思路分析。

很显然可以想到，如果想要最大化剩下的数，需要让操作的最后一步 $a_i-x\to ans$ 中 $x$ 尽量小，而如果想让 $x$ 尽量小，需要让倒数第二步 $a_j-x'\to x$ 中的 $a_j$ 最小或 $x'$ 最大，以此类推……

对于 $a_2$，其实就是在判断 $a_1-(a_2-a_3)$ 和 $a_1-a_2-a_3$ 的大小，后面数同理。在以上过程中，我们发现：第一个数确定下来之后，其实就相当于在给后面的数字添加正负号。但是 $a_1$ 和 $a_2$ 的符号是不能变的，因此式子中至少要有一个正号或负号。

当然，推到这里我们就能得出结论：

- 数组中全是负数，除最大数（绝对值最小的数）之外的**其余**数绝对值之和相加再加上最大数即为答案；
- 数组里全是正数，除最小数之外的**其余**数之和减去最小数即为答案；
- 数组里正负都有，所有数的绝对值之和即为答案。

形式化地讲：

$f(x)=\begin{cases}\sum\limits_{i=1}^n|a_i|-2\times|\min\{a_1,a_2\cdots a_n\}|&\forall a_i\times a_j\leq0\\\sum\limits_{i=1}^n|a_i|&\text{otherwise}\end{cases}$

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,a[1000006];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		bool zheng=0,fu=0;
		ll ans=0,MIN=2147483647ll*2147483647ll;
		for(int i=0;i<n;i++){
			cin>>a[i];
			if(a[i]>0)zheng=max(zheng,true);
			if(a[i]<0)fu=max(fu,true);
			ans+=abs(a[i]),MIN=min(MIN,abs(a[i]));
		}
		cout<<(n==1?a[0]:ans-2*(zheng^fu)*MIN)<<endl;
	}
}
```

---

## 作者：TheForgotten (赞：0)

# P9852 [ICPC2021 Nanjing R] Windblume Festival 题解
[题目传送门](https://www.luogu.com.cn/problem/P9852)
## 题目大意
给一个长度为 $n$ 环形整数序列 $a$，每次操作可以任意选择一个下标 $x$，令 $a_x=a_x-a_{(x\bmod n)+1}$，之后移除 $a_{(x\bmod n)+1}$。最后会剩下一个元素，要求最大化这个元素。
## 思路
看到样例，我们可以考虑进行分类讨论。当序列 $a$ 中只有正数或者只有负数时，我们都可以转化成只有正数，但是我们必须舍弃一个数，于是舍弃对答案贡献最小的那一个数。
如果序列 $a$ 中既有正数又有负数，那么就对所有在正数后方的负数进行操作，将绝对值累加到正数之中，那么问题就变成了使绝对值之和最大化。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
int T,n,a[N];
bool flag=1;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	cin>>T;
	while(T--) {
		cin>>n; 
		if(n==1) {
			cin>>a[0];
			cout<<a[0]<<"\n";
			continue;
		}//n=1时特判 
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		flag=1;
		for(int i=1;i<=n;i++)
			if(a[i]>0){//如果是一个正数 
				flag=0;
				break;
			}
		if(flag){
			for(int i=1;i<=n;i++){
				a[i]=abs(a[i]);
			}
		}
		int minn=INT_MAX,sum1=0,sum2=0,ans;
		for(int i=1;i<=n;i++){
			minn=min(minn,a[i]);
			sum1+=a[i];
			sum2+=abs(a[i]);
		}
		if(minn<0) ans=sum2;
		else ans=sum1-minn*2;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

感觉我的思路很烦，但是很自然。  

首先手玩一下样例可以发现，我们相当于可以添加正负号，但是，负号至少添加一个，至多添加 $n-1$ 个，而零的存在相当于可以忽视这个限制。  

然后想到一个贪心的做法，我们把最小的那个数字减减减，最后一下子加到最大的数字上，显然可以得到最大值。在全是正数的情况下，这个东西是对的，但是考虑负数，记负数个数为 $g$，当 $g=0$ 时沿用上面的做法，当 $0<g<n$ 时，我们相当于可以随意加减，答案就是绝对值之和，当 $g=n$ 时，我们一定会选出最大的一个数改变符号（注意这里是负数，所以是绝对值最小的）。  

最后，记得特判 $n=1$ 的情况，否则会像我一样 WA 很多次。

---

## 作者：Iris_Aurora (赞：0)

题目大意：有一些数围成一个环，每次可以将相邻两个数替换成前者减后者的差，问最后得到的数的最大值。

分三种情况讨论：

1. 全是正数的情况：以 $6$、$13$、$10$、$20$ 为例，用绝对值最小的 $6$ 减去 $13$ 和 $10$ 得到 $-17$，然后用 $20$ 减去 $-17$ 得到 $37$，是用 $13$、$10$、$20$ 的绝对值和减去 $6$ 的绝对值得到答案。
2. 全是负数的情况：以 $-24$、$-17$、$-15$、$-28$ 为例，先将 $-24$、$-17$、$-28$ 相减得到 $-69$，然后用绝对值最小 $-15$ 减去 $-69$ 得到 $54$，是用 $-24$、$-17$、$-28$ 的绝对值和减去 $-15$ 的绝对值得到答案。
3. 有正有负的情况：以 $16$、$-34$、$14$、$7$ 为例，先将 $-34$、$14$、$7$ 相减得到 $-55$，然后用 $16$ 减去 $-55$ 得到 $71$，是用 $16$、$-34$、$14$、$7$ 的绝对值和得到答案。

那么第 $1$、$2$ 种情况为什么要选绝对值最小的数呢，因为舍去这个数相当于减去他的双倍绝对值，自然要选绝对值最小的。

最后注意：一定一定要特判 $n = 1$ 的情况！！

---

## 作者：zyn_ (赞：0)

# P9852 [ICPC2021 Nanjing R] Windblume Festival

## 题目大意

有一个长度为 $n$ 的**环形**序列 $\{a_i\}$（即 $a_i$ 与 $a_{i+1}$ 相邻，$a_n$ 与 $a_1$ 相邻。**以下下标均按模 $n$ 处理**）。每次操作选一个 $x$，将 $a_x$ 变为 $a_x-a_{x+1}$，然后将 $a_{x+1}$ 移出序列。求 $n-1$ 次操作后，剩余一个数的最大值。

$1\le n\le 10^6$。

## 题目分析

如果 $n=1$，答案就是 $a_1$。以下默认 $n\ge 2$。

观察样例会发现，无论怎么操作，最后剩下的数必定可以表示成

$$
\sum_{i=1}^{n}a_ib_i
$$

其中 $b_i=\pm 1$，且 $b_i$ 不全为 $1$ 或 $-1$。

例如 $a_1=1$，$a_2=-3$，$a_3=2$，$a_4=-4$。则取 $b_1=b_3=1$，$b_2=b_4=-1$，剩下的数为 $1+3+2+4=10$。

下证，对于满足要求的序列 $\{b_i\}$，$\sum_{i=1}^{n}a_ib_i$ **均可以作为剩下的数**。

### 证明这个命题

使用数学归纳法。归纳奠基是 $n=2$，此时 $b_1=1$，$b_2=-1$；或 $b_1=-1$，$b_2=1$。命题成立。

假设 $n=k$ 时命题成立，考虑 $n=k+1$ 时的情形。

$\{b_i\}$ 中至少有一个数为 $1$，也至少有一个数为 $-1$。由于 $\{a_i\}$ 是环形序列，不妨设 $b_1=1$，$b_2=-1$。

**情况一：** 若 $b_3=-1$，则第一次操作，取 $x=1$。此时，序列 $\{a_i\}$ 变为新的序列 $\{a_i'\}=\{a_1-a_2,a_3,\dots,a_{k+1}\}$。令 $\{b_i'\}=\{1,b_3,\dots,b_{k+1}\}$。

$$
\begin{aligned}
\sum_{i=1}^{n}a_ib_i & = a_1b_1+a_2b_2+\sum_{i=3}^{k+1}a_ib_i \\
& = (a_1-a_2)+\sum_{i=2}^{k}a_i'b_{i+1} \\
& = \sum_{i=1}^{k}a_i'b_i'
\end{aligned}
$$

变为 $n=k$ 的情形。由归纳假设，命题成立，递推到 $n=k+1$。

**情况二：** 若 $b_3=1$，则第一次操作，取 $x=2$。此时，序列 $\{a_i\}$ 变为新的序列 $\{a_i'\}=\{a_1,a_2-a_3,a_4,\dots,a_{k+1}\}$。令 $\{b_i'\}=\{1,-1,b_4,\dots,b_{k+1}\}$。

$$
\begin{aligned}
\sum_{i=1}^{n}a_ib_i & = a_1b_1+a_2b_2+a_3b_3+\sum_{i=4}^{k+1}a_ib_i \\
& = a_1-(a_2-a_3)+\sum_{i=3}^{k}a_i'b_{i+1} \\
& = \sum_{i=1}^{k}a_i'b_i'
\end{aligned}
$$

变为 $n=k$ 的情形。由归纳假设，命题成立，递推到 $n=k+1$。

于是 $n=k+1$ 时，命题必成立。故可知对于任意正整数 $n\ge 2$，命题成立。

### 回到原题

那么，本题等价于，合理安排 $\{b_i\}$ 的值，使 $\sum_{i=1}^{n}a_ib_i$ 最大。

考虑对每个 $i$，当 $a_i\ge 0$ 时 $b_i=1$，当 $a_i\lt 0$ 时 $b_i=-1$。

如果这样安排后，$b_i$ 不全为 $1$ 或 $-1$，那么此时 $\sum_{i=1}^{n}a_ib_i$ 的值，即为 $\sum_{i=1}^{n}|a_i|$，就是答案。

如果 $b_i$ 全为 $1$，那么 $a_i$ **全为非负数**。为使答案最大，应该将**最小的** $a_i$，其对应的 $b_i$ 设为 $-1$。设 $\{a_i\}$ 中最小值为 $x$，答案为 

$$
\sum_{i=1}^{n}a_i-2x
$$

如果 $b_i$ 全为 $-1$，那么 $a_i$ **全为负数**。为使答案最大，应该将**最大的** $a_i$，其对应的 $b_i$ 设为 $1$。设 $\{a_i\}$ 中最大值为 $x$，答案为

$$
2x-\sum_{i=1}^{n}a_i
$$

$b_i$ 全为 $1$ 或 $-1$ 的情况，答案可以合并为：

$$
\sum_{i=1}^{n}|a_i|-2|x|
$$

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
long long x,sum,mn;
bool has_pos,has_neg;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        if(n==1){scanf("%lld",&x);printf("%lld\n",x);continue;}
        has_pos=has_neg=false;
        mn=0x3f3f3f3f3f3f3f3fLL;sum=0;
        while(n--){
            scanf("%lld",&x);
            sum+=(x>0?x:-x);
            mn=min(mn,x>0?x:-x);
            if(x>=0)has_pos=true;
            if(x<=0)has_neg=true;
        }
        if(has_pos&&has_neg)printf("%lld\n",sum);
        else printf("%lld\n",sum-2*mn);
    }
    return 0;
}
```

---

## 作者：luogu10086 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9852)

### PART 1

题目大意：

有 $n$ 个整数围成一圈，每次操作可以让相邻的两个整数中的前一个整数减去后一个整数，得到一个新的整数。问只剩下一个整数时，这个整数最大是多少。



------------
### PART 2

整体思路：

我们先列出 3 种情况：只有负数，只有正数，正负数都有。

1. 只有负数：以 $-11,-4,-5,-45$ 为例，发现得数最大为： $57$。

2. 只有正数：以 $11, 4, 5, 45$ 为例，发现得数最大为： $57$。

3. 正负数都有：以 $-11 ,4,-5,45$ 为例，发现得数最大为： $65$。

我们发现，如果 $n$ 个数中正负数都有，输出的值即为所有数的绝对值之和；如果 $n$ 个数中只有正数或负数，那输出的数为所有数的绝对值之和，减去最小的绝对值的两倍。

------------

### PART 3

代码实现：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,num,x,y,ans,nmin;
int main(){
    cin>>T;
    while(T--){
	    cin >> n;
        if(n == 1){//特判
            cin >> num;
            cout << num << endl;
        }else{
            x = y = ans = 0;
    	    nmin = 1145141919810;
            for(ll i = 0;i < n;i++){
                cin >> num;
                if(num > 0)x=1;//判断有无正数
    		if(num < 0)y=1;//判断有无负数
                ans += abs(num);//加上绝对值
                nmin = min(nmin,abs(num));//找最小的绝对值
            }
            cout << (x + y == 2 ? ans : ans - 2 * nmin) << endl;//输出
        }
    }
}
```

$\texttt{\tiny{\color{#dfdfdf}猿神，栖洞！}}$

---

