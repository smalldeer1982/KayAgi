# Build the Permutation

## 题目描述

You are given three integers $ n, a, b $ . Determine if there exists a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ , such that:

- There are exactly $ a $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} < p_i > p_{i+1} $ (in other words, there are exactly $ a $ local maximums).
- There are exactly $ b $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} > p_i < p_{i+1} $ (in other words, there are exactly $ b $ local minimums).

If such permutations exist, find any such permutation.

## 说明/提示

In the first test case, one example of such permutations is $ [1, 3, 2, 4] $ . In it $ p_1 < p_2 > p_3 $ , and $ 2 $ is the only such index, and $ p_2> p_3 < p_4 $ , and $ 3 $ the only such index.

One can show that there is no such permutation for the third test case.

## 样例 #1

### 输入

```
3
4 1 1
6 1 2
6 4 0```

### 输出

```
1 3 2 4
4 2 3 1 5 6
-1```

# 题解

## 作者：activeO (赞：13)

## 题意

~~题面翻译的有一小点问题~~

给出 n,a,b，构造一个包含 1 至 n 的数列 $ p_1,p_2,...,p_n $ 使得：

- 刚好有 a 项 $ p_i(2 \leq i \leq n-1) $ 满足 $ p_{i-1} < p_i > p_{i+1} $

- 刚好有 b 项 $ p_i(2 \leq i \leq n-1) $ 满足 $ p_{i-1} > p_i < p_{i+1} $

若无解则输出 -1,多组数据。

## 思路

首先考虑无解的情况，如果 $ \left| a-b \right| >1 $ 或 $ a + b > n - 2 $ 显然无解，直接输出 -1。

然后考虑制造一个“峰”（如果需要的话）。定义 $ l=1,r=n $ ，那么制造一个“峰”就会是 lrl 或 rlr 的形式，很显然我们可以在还没有把“峰”制造完时交替的制造，就定义一个 t，当 $ t=1 $ 时输出 l，$ t=0 $ 时输出 r。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

int main(){
	
	int t;
	
	scanf("%d",&t);
	
	while(t--){
		int n,a,b;
		scanf("%d %d %d",&n,&a,&b);
		if(abs(a-b)>1||a+b>n-2){
			puts("-1");
			continue;
		}
		int l=1,r=n,t=(a>b);
		for(int i=1;i<=n;i++){
			if(t) printf("%d ",l++);
			else printf("%d ",r--);
			if(i<=a+b) t^=1;//如果还需要“峰”
		}
		puts("");
	}
	
	return 0;
}


```


---

## 作者：IYSY2009I (赞：3)

A 题题解没赶上，所以我来写 B 篇了。

这里先纠正一个错误：
- 刚好有 $a$ 项 $p_i (2 \leqslant i \leqslant n-1)$ 
- 刚好有 $b$ 项 $p_i (2 \leqslant i \leqslant n-1)$

而非至少（英文不好的我考场上差点没写出来）。

然后我们就来想一想。

首先我们先来想一下无解判定，我把答案放在底下，看看是否和大伙想的一样。

```cpp
if(!(abs(a-b)<=1&&a+b<=n-2)){
		printf("-1\n");
		return;
	}
```


至于为什么，接下来再说。

然后我们想，如果我们想要制造一个高谷或者低谷（懒得打字了，以下将 $p_{i-1} < p_i >p_{i+1}$ 简称为高谷，$p_{i-1} > p_i < p_{i+1}$ 简称为低谷 ）我们可以选取目前可以选取的最高/最低值放在两侧，把目前可以选取的最低/最高值放在中间。所以我们还要声明两个变量 $\_max,\_min$，存储目前可以选取的最高、最低值。

然后我们来思考一个问题：如何用最少的材料（数字）来建立至少 $a$ 个高谷和 $b$ 个低谷。

首先我们来知道一点：不管如何构造，在 $n \le 2$ 时都肯定无法构造出来一个低谷或一个高谷这是显而易见的。

这个时候大家应该打开画图软件，查找一下规律。

我们来看一下以下两个例子。

- 高 低 高 低 高 低
- 低 高 低 高 低 高

我们可以发现，这是制造高谷/低谷所用最少的方法

|  | 可以创造几个高/低谷 | 可以附带几个高/低谷 | 结尾 |
| :----------: | :----------: | :----------: | :----------: |
| 第一个点为高 | 2个高谷 | 2个低谷 | 高谷 |
| 第一个点为低 | 2个低谷 | 2个高谷 | 低谷 |

我们可以使用以上方案创造个对应的谷。

为了避免逻辑混乱，我们先创造 $a,b$ 之间更大的数对应的谷。

我们来找一个可爱样例举一个例子：

```
6 1 2
```

首先我们看到，$a<b$，所以我们先创造低谷：

```
高 低 高 低 
```

然后我们就完成了前半部分，我们真棒！

那么后半部分怎么办呢？

我们可以看到，不管接下来安置低或高，都会创建一个低谷，同时我们要避免创建高谷，所以接下来我们只需要构造一个不上升子序列即可。

反之亦然。

相信大家看到这里时都一脸懵，因为我写到这里都一脸懵。所以我提几个不正确的构造方法（还是以 $a<b$ 为例）

- 为什么我的代码那么长

emmm....在比赛的时候我不放心，加了很多特判。

- 如果先创建高谷会怎样？

我们可以来试一下：

还是这组样例

```
6 1 2
```

先创造高谷：

```
低 高 低 高
```

这个时候，我们发现我们创造不下去了，因为前文提到过，我们不管如何创造，都会创造一个高谷，使该方案不可行。

综上所述，我们需要先创造低谷。

- 无解判定之 $\operatorname{abs}(a-b)<=1$

为了探究为什么 $\operatorname{abs}(a-b)<=1$ 可能有解，我们需要探究 $\operatorname{abs}(a-b)>1$ 为什么没有解。

假如 $\operatorname{abs}(a-b)>1$ 那么我们先创造高谷，就会创造出 $a$ 个高谷和 $a$ 个低谷，还剩下 $b-a$ 个高谷没有创造。

这个时候我们引入一个结论：在两个高谷之间，一定有一个低谷。

为什么？

一个高谷肯定长得像这样：

```
高 低 高
```

因为“高”指的是当前能取到的最大数字，所以接下来取的数字肯定没有“高”大，我们如果不想有低谷，我们必须一直创建比上一个数字小的数字（大家可以自己试一试），但这样我们也创造不出来高谷

所以，$\operatorname{abs}(a-b)>1$ 没有解就显而易见了。

- 无解判定之 $a+b<=n-2$

这个就比较容易解释了。在填进去两个数后，我们可以填入一个数字创造一个谷，所以如果我们希望创造 $a+b$ 个谷，我们至少需要有 $a+b+2$ 个数字。

最后就是代码了，我自认为讲得很明白，不需要给注释了，祝大家 AC 愉快！

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read(),a=read(),b=read();
	int nn=n,aa=a,bb=b;
	int _max=n,_min=1;
	if(aa==0&&bb==0){
		for(int i=1;i<=nn;i++)
			printf("%d ",i);
		printf("\n");
		return;
	}
	if(!(abs(a-b)<=1&&a+b<=n-2)){
		printf("-1\n");
		return;
	}
	if(a==b){
		for(int i=1;i<=a;i++){
			printf("%d %d ",_max,_min);
			_max--;
			_min++;
		}
		printf("%d ",_max);
		_max--;
		for(int i=1;i<=n-2*b-1;i++){
			printf("%d ",_max);
			_max--;
		}
		printf("\n");
		return;
	}
	if(a<b){
		for(int i=1;i<=a+1;i++){
			printf("%d %d ",_max,_min);
			_max--;
			_min++;
		}
		for(int i=1;i<=b-a-1;i++){
			printf("%d %d ",_min,_max);
			_max--;
			_min++;
		}
		printf("%d ",_min);
		_min++;
		for(int i=1;i<=n-2*b-1;i++){
			printf("%d ",_min);
			_min++;
		}
		printf("\n");
		return;
	}
	if(a>b){
		for(int i=1;i<=b+1;i++){
			printf("%d %d ",_min,_max);
			_max--;
			_min++;
		}
		for(int i=1;i<=a-b-1;i++){
			printf("%d %d ",_max,_min);
			_max--;
			_min++;
		}
		printf("%d ",_max);
		_max--;
		for(int i=1;i<=n-2*a-1;i++){
			printf("%d ",_max);
			_max--;
		}
		printf("\n");
		return;
	}
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：Jerrlee✅ (赞：2)

## 题意
给定 $n,a,b$，构造一个包含 $1$ 至 $n$ 的数列 $p_1,p_2,...,p_n$ 使得：

- 刚好有 $a$ 项 $p_i (2 \leqslant i \leqslant n-1)$ 满足 $p_{i-1} < p_i > q_{i+1}$。（可以理解为有 $a$ 项“峰”）
- 刚好有 $b$ 项 $p_i (2 \leqslant i \leqslant n-1)$ 满足 $p_{i-1} > p_i < q_{i+1}$。（可以理解为有 $b$ 项“谷”）

无解输出 $-1$。
## 思路
无解情况：

- 当峰数或谷数大于 $(n-1)/2$ 时，无解。

- 峰数、谷数差大于 $1$ 时无解，在做到峰谷差为 $1$ 后，每多产生一个峰或谷都会导致多增加一个谷或峰。

然后分类 $a=b$ 和 $a-b=\pm 1$ 三种情况即可。

1. $a-b=1$ 时，先满足 $a$ 的条件，再输出降序序列；

2. $b-a=1$ 时，先满足 $b$ 的条件，再输出升序序列；

3. $a=b$ 时，先满足 $a$ 的条件，再输出降序序列（约等于第 $1$ 种方法）。

## 代码
```cpp
#include<iostream>
using namespace std;
#define int long long
void fun(int a,int mn,int mx){
   while(a--){
		cout<<mn<<" "<<mx<<" ";
		mn++,mx--;
	}
	for(int i=mx;i>=mn;i--) cout<<i<<" ";
	cout<<endl;
}
void fun1(int b,int mn,int mx){
   while(b--){
		 cout<<mx<<" "<<mn<<" ";
		 mn++,mx--;
	}
	for(int i=mn;i<=mx;i++) cout<<i<<" ";
	cout<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,a,b;
		cin>>n>>a>>b;
		if(a-b<-1||a-b>1||a+b+2>n) cout<<"-1\n";
		  else{
		  	if(a-b==1){
		  		  int mn=1,mx=n;
		  		  fun(a,mn,mx);
		  	}
		  	if(a-b==0){
		  		  int mn=1,mx=n-1;
		  		  cout<<n<<" ";
		  		  fun(a,mn,mx);
		  	}
		  	if(a-b==-1){
		  		  int mn=1,mx=n;
		  		  fun1(b,mn,mx);
		  	}
		  }
	}
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/64861184)

[AC记录（CF）](https://codeforces.com/contest/1608/submission/138821897)

顺便说一句，大家调试时注意下格式！（我打比赛时就是因为格式 WA 的

---

## 作者：enucai (赞：1)

~~**前言：这道题这个蒟蒻在考场上写了 10 分钟。**~~

## 题意简述

给你三个数 $n$，$a$，$b$，要你构造一个长度为 $n$ 的序列，要求这个序列有 $a$ 个单峰与 $b$ 个单谷。

单峰的定义是：称 $i$ 为单峰当且仅当满足 $1\le i \le n-1$ 且 $q_{i-1}<q_i>q_{i+1}$。

单谷的定义是：称 $i$ 为单峰当且仅当满足 $1\le i \le n-1$ 且 $q_{i-1}>q_i<q_{i+1}$。

其中 $q$ 为你构造的序列。如果无法构造出这样的序列，那么输出 `-1`。

## 思路简述

首先很容易观察出一个性质：

- 任意两个单峰之间都有且只有一个单谷。

- 任意两个单谷之间都有且只有一个单峰。

因为任意两个单峰之间一定只有一个转折点，而这个转折点就是单谷。第二条同理。

因此，我们发现 $|a-b|\le 1$。还要注意单峰与单谷的总和最多只有 $n-2$ 个，所以还要满足 $a+b\le n-2$。

因此我们得出了答案为 `-1` 的条件：$|a-b|>1$ 或 $a+b>n-2$。

然后就是简单的分类讨论了，我们称单峰为 $\texttt{U}$，单谷为 $\texttt{D}$。

- $a=b+1$：我们从第二个数开始以 $\texttt{UDU\dots DU}$ 的顺序填充数组。

- $a=b$：我们从第二个数开始以 $\texttt{UDUD\dots UD}$ 的顺序填充数组。

- $a=b-1$：我们从第二个数开始以 $\texttt{DUD\dots UD}$ 的顺序填充数组。

在后面就直接将剩下的数从小到大塞进去就好了，这样就不会在后面再产生单峰或单谷了。

## 蒟蒻代码

**Talk is cheap, show me the code.**

```cpp
int n,a,b;
int ans[100010];
void work(){
	n=read(),a=read(),b=read();
	if(a+b>n-2||abs(a-b)>1){
		puts("-1");
		return;
	}
	if(a>b){
		int l=1,r=n;
		For(i,1,2*a){
			if(i%2==1) ans[i]=l++;
			else ans[i]=r--; 
		}
		For(i,2*a+1,n) ans[i]=r--;
	}else if(a<b){
		int l=1,r=n;
		For(i,1,2*b){
			if(i%2==1) ans[i]=r--;
			else ans[i]=l++;
		}
		For(i,2*b+1,n) ans[i]=l++;
	}else if(a==b){
		int l=1,r=n;
		For(i,1,2*a+1){
			if(i%2==1) ans[i]=l++;
			else ans[i]=r--;
		}
		For(i,2*a+2,n) ans[i]=l++;
	}
	For(i,1,n) printf("%d ",ans[i]);
	puts("");
}
```
~~这代码这么丑，还有人要看？~~

---

## 作者：heaksicn (赞：0)

## 1 题意
给出 $n,a,b$ ，构造一个数列 $a$，使得序列满足：
- 恰好有 $a$ 个 $i$ ，满足 $p_{i-1}<p_i>p_{i+1}$  
- 恰好有 $b$ 个 $i$ ，满足 $p_{i-1}>p_i<p_{i+1}$  
多组数据。
## 2 分析
首先，为了尽量满足条件，我们需要使每个满足要求的 $i$ 尽量紧凑。  
假设一个数列 $[1,4,2,3] $ ，我们发现 $1<4>2,4>2<3$。  
所以，当出现一个数列 $a$ 中存在 $i$ ，使得 $p_{i-1}<p_i>p_{i+1}<p_{i+2}$ ，那个这个序列就可以同时为 $a$ 和 $b$ 贡献一个。  
所以，每个满足 $a$ 的 $i$ 必然存在一个满足 $b$ 的 $i+1$ 或 $i-1$。  
所以，如果 $abs(a-b)\geq 2$ ，无解。   
同时，如果整个数列都构造不出来，也无解。  
那么，对于每一组数据，尝试构造一个序列 $[1,n,2,n-1,3,n-2,\cdots,i,n-i+1]$ ，这样就会存在 $i-1$ 组 $a$ 和 $b$。  
如果 $abs(a-b)=1$ ，在尾部进行相应构造。  
剩余的数在尾部递增或递减即可。  
时间复杂度 $O(Tn)$。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,t,a,b; 
int main(){
	t=read();
	while(t--){
		n=read(),a=read(),b=read();
		if((n%2==1&&a>=n/2&&b>=n/2)||(n%2==0&&(a>=n/2||b>=n/2))||abs(a-b)>=2){//无解情况
			cout<<-1<<endl;
			continue;
		} 
		if(a==0&&b==0){//特判
			for(int i=1;i<=n;i++) cout<<i<<" ";
			cout<<endl;
			continue;
		}
		int i;
		if(a>b){
			for(i=1;i<=a;i++){//构造
				cout<<i<<" "<<n-i+1<<" ";  
			}
			int lst=i;
			for(i=n-i+1;i>=lst;i--) cout<<i<<" ";//递增
		}else if(a<b){//同上
			for(i=1;i<=b;i++){
				cout<<n-i+1<<" "<<i<<" ";
			}
			int lst=n-i+1;
			for(;i<=lst;i++) cout<<i<<" ";
		}else{
			for(i=1;i<=a;i++){
				cout<<i<<" "<<n-i+1<<" ";
			}
			int lst=n-i+1;
			for(;i<=lst;i++) cout<<i<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：SalomeJLQ (赞：0)

### 题目翻译

- 多组测试数据。
- 每组测试数据给出 $n,a,b$，要求输出一个 $1\sim n$ 的排列，使得排列中正好有 $a$ 个极大值和 $b$ 个极小值。
- 即 $a$ 个 $p_{i-1}<p_i>p_{i+1}$ 的 $p_i$ 和 $b$ 个 $p_{i-1}>p_i<p_{i+1}$ 的 $p_i$。

------------
首先考虑无解的条件。

显然极大值和极小值必然是交替出现的。因此其个数相差最多为 $1$。因此判掉 $|a-b|>1$ 的情况。

其次，两端的两个数不可能是极大值或极小值。因此若 $a+b>n-2$ 则显然做不到，判掉。

然后考虑如何确定这个排列。

由于极大值和极小值交替出现，因此我们不妨将它们全部堆到左边，然后剩下的数单调递增或递减地排到右边。

例如 $n=9$，分类讨论：

- $a>b$，例如 $a=3,b=2$，则 `6 7 5 8 4 9 3 2 1`。`7,8,9` 为极大值，`4,5` 为极小值。
- $a=b$，例如 $a=2,b=2$，则 `7 6 8 5 9 4 3 2 1`。`8,9` 为极大值，`5,6` 为极小值。
- $a<b$，例如 $a=2,b=3$，则 `6 1 5 2 4 3 7 8 9`。`4,5` 为极大值，`1,2,3` 为极小值。

综上所述，可以写出如下代码：

```cpp
void Build_the_Permutation()
{
	n=read(),x=read(),y=read();
	if(abs(x-y)>1){printf("-1\n");continue;}
	if(x+y>n-2){printf("-1\n");continue;}
	int s=x+y;
	if(x==y)
	{
		int l=n-s,r=n;
		while(l<r)printf("%d ",r),r--,printf("%d ",l),l++;
		if(l==r)printf("%d ",r);
		for(int i=n-s-1;i;i--)printf("%d ",i);
	}
	if(x>y)
	{
		int l=n-s,r=n;
		while(l<r)printf("%d ",l),l++,printf("%d ",r),r--;
		if(l==r)printf("%d ",l);
		for(int i=n-s-1;i;i--)printf("%d ",i);
	}
	if(x<y)
	{
		int l=1,r=s+1;
		while(l<r)printf("%d ",r),r--,printf("%d ",l),l++;
		if(l==r)printf("%d ",r);
		for(int i=s+2;i<=n;i++)printf("%d ",i);
	}
	printf("\n");
}
```

---

## 作者：清烛 (赞：0)

## Description
构造一个长度为 $n$ 的 $[1, n]$ 的排列，要求恰有 $a$ 个“波峰”和 $b$ 个“波谷”。

一个波峰是如下定义的：若 $p_{i - 1} < p_i > p_{i + 1}$，则称其为一个“波峰”。波谷的定义反之亦然。

## Solution
一个小清新构造。

首先我们思考一下波峰和波谷的性质。可以发现一个波峰肯定是对应一个波谷，因为遇到一个波峰之后肯定是下降，要么降到最右边，要么就要重新回升产生一个波谷。

即，有解的一个必要条件是 $|a - b|\le 1$。多出来的那一个是放在排列的首端或尾端的。

另外，我们满打满算，波峰和波谷加起来一定不超过 $n - 2$ 个，因为排列的首端和尾端是构不成波峰/波谷的。所以有解的另一个必要条件是 $a + b \le n - 2$。

综上，有解的充要条件是 $|a - b|\le 1$ 且 $a + b\le n - 2$，必要性上面已证，下面通过直接构造解的方式说明充分性。

### $a = b$ 的情况
先从这个最好考虑的情况开始。

我们发现需要的是 $a$ 个波峰和 $b$ 个波谷。故不难发现我们可以在一开始反复横跳将方案构造出来，即 谷-\[峰-谷\]-单调上升。第一个谷不会被计算在内，因此峰和谷的数量相等。

我们拿 $[1, 2n + 2]$ 出来构造这 $a$ 个波峰/波谷，后面的数字让他单调上升，故这一部分的代码如下：

```cpp
if (a == b) {
    FOR(i, 1, a + 1) ans[i * 2 - 1] = i;
    FOR(i, 1, a) ans[i * 2] = i + a + 1;
    FOR(i, 2 * a + 2, n) ans[i] = i;
}
```

### $a - b = 1$ 的情况
波峰比波谷多一个，可以发现我们可以构造出 谷-\[峰-谷\]-峰-单调下降 的形式，第一个谷不会被计算在内，因此峰会比谷刚好多一个。这部分的代码如下：

```cpp
else if (a > b) {
    FOR(i, 1, b + 1) ans[i * 2 - 1] = i;
    FOR(i, 1, a - 1) ans[i * 2] = i + b + 1;
    ans[a * 2] = n;
    FOR(i, a * 2 + 1, n) ans[i] = n - (i - a * 2);
}
```

### $b - a = 1$ 的情况
像上面一样，只需要构造出 峰-\[谷-峰\]-谷-单调上升 的形式，第一个峰不会被计算在内，代码如下：

```cpp
else if (a < b) {
    FOR(i, 1, b) ans[i * 2] = i;
    FOR(i, 1, a + 1) ans[i * 2 - 1] = i + b;
    FOR(i, 2 * b + 1, n) ans[i] = i;
}
```

于是代码不难实现，充要性得证。

---

