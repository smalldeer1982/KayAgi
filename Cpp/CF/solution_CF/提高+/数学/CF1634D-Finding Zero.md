# Finding Zero

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1634D/74895b22455b2b459cd8609f4caa3df7273f47e6.png)This is an interactive problem.

We picked an array of whole numbers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) and concealed exactly one zero in it! Your goal is to find the location of this zero, that is, to find $ i $ such that $ a_i = 0 $ .

You are allowed to make several queries to guess the answer. For each query, you can think up three distinct indices $ i, j, k $ , and we will tell you the value of $ \max(a_i, a_j, a_k) - \min(a_i, a_j, a_k) $ . In other words, we will tell you the difference between the maximum and the minimum number among $ a_i $ , $ a_j $ and $ a_k $ .

You are allowed to make no more than $ 2 \cdot n - 2 $ queries, and after that you have two tries to guess where the zero is. That is, you have to tell us two numbers $ i $ and $ j $ and you win if $ a_i = 0 $ or $ a_j = 0 $ .

Can you guess where we hid the zero?

Note that the array in each test case is fixed beforehand and will not change during the game. In other words, the interactor is not adaptive.

## 说明/提示

Array from sample: $ [1, 2, 0, 3] $ .

## 样例 #1

### 输入

```
1

4

2

3

3

2```

### 输出

```
? 1 2 3

? 2 3 4

? 3 4 1

? 4 1 2

! 2 3```

# 题解

## 作者：I_am_Accepted (赞：9)

### Preface

自己想出来感觉好爽。

感觉本片题解比官方题解简单太多了……OvO

### Analysis

**对于集合 $S$ 极差定义：$\max\limits_{x\in S}x-\min\limits_{x\in S}x$**

**以下 $\text{que}(x,y,z)$ 表示一次询问（三个下标），并返回值。**

最后输出两个猜测的值，且每次询问只给三个数的极差。设序列最大值为 $mx$（并假设只有一个取到最大值），发现如果 $a_i:=mx-a_i$，每次询问给出的极差是不变的，而你仍然需要输出，且包含 $0$。这说明我们最后要输出整个序列的最大和最小值的下标（若多个随意，因为 $0$ 就一个）。

如果维护好了前 $i-1$ 个数的最大、最小值的下标 $x,y$（不知道具体对应关系）和 $len=|a_x-a_y|$，再随便选一个 $1\le z\le i-1$ 使得 $z$ 与 $x,y$ 不同。这时必定有 $\min(a_x,a_y)\le a_z\le\max(a_x,a_y)$。设 $dx=\text{que}(x,z,i),dy=\text{que}(y,z,i)$，这时如果 $\max(dx,dy)\le len$ 显然极差没有被更新。否则设 $dx\ge dy$，也就是说这时大小关系为 $a_x\le a_z\le a_y<a_i$ 或者全部反过来，那么将 $y:=i,len:=dx$ 即可。

发现这样每个位置询问两次正好，但是我们怎么起头（$i\le 4$）？

观察前四个，选三个数 $\text{que}$ 共 $4$ 次。设 $b1,b2,b3,b4$ 为 $1,2,3,4$ 的排列使得 $a_{b1}\le a_{b2}\le a_{b3}\le a_{b4}$ 这时取 $4$ 个 $\text{que}$ 的最大值为 $len$，$len$ 必定出现两次及以上（$\text{que}(b1.b2,b4),\text{que}(b1,b3,b4)$），就可以推出 $b1,b4$ 的值，$x=b1,y=b4,z=b2$ 或 $b3$ 即可。

前四个 $\text{que}$ 共 $4$ 次，后 $n-4$ 个共 $2(n-4)$ 次，共 $2n-4$ 次，比官方的最坏情况少两次。

### Code

[Link](https://codeforces.com/contest/1634/submission/145560281)

---

## 作者：RedLycoris (赞：6)

**Warning：可能比官方题解复杂的多，思维难度估计要上紫，但推出来了能有很好的训练效果**

$\color{white}\text{~~然后你们知道为啥 div2 rank1 的 YuezhengLing 最后才过D了吧~~}$

---

令 $x$ 为隐藏的数组。

这个方法的大体思路就是，通过两次全数组的询问，得到两个数的位置（$0$  和最大的数），然后上传这两个位置。

我们考虑这么询问:

固定前两个数 $(1,2)$ 不动，询问 $(1,2,i)$，记得到的序列为 $a$。询问 $n-2$ 次。记最大的 $a_i$ 的下标 $i$ 为 $pos_1$。

然后固定 $(1,pos_1)$ 不动，询问 $(1,pos_1,i)$，记得到的序列为 $b$。询问 $n-2$ 次。记最大的 $b_i$ 的下标 $i$ 为 $pos_2$。

显然，$pos_1 \neq pos_2$，因为我们 $b$ 询问不会询问 $(1,pos_1,pos_1)$ 

然后我们来想，如何利用 $a$ 数组和 $b$ 数组，来推断出答案。

我赛时的注释：

```
//now if both x[1] and x[2] isn't 0 this is okay
//if x[2] is 0? what will happen?
//a[i] will be x[i]. How to ensure it?
//we can ask(2,pos1,pos2) to check
//if x[1] is 0: it is smaller than either a[pos1] or a[pos2] we can return [1,1]
//if x[2] is 0: this returns a[pos1 or pos2] then we can return [2,pos1 or pos2]
//otherwise we can return [pos1,pos2]
//oops,there still can be x[1] is max and pos1 is zero

```

我们要分类讨论（如何判断是哪一类待会儿讲）：

+  $0$ 和最大的数都不在 $1$ 和 $2$ 两个位置上

显然，对于这种情况，我们求得的 $pos_1$ 和 $pos_2$ 就可以做为答案上传。因为，如果 $x_1$ 和 $x_2$ 都不是 $0$ 或最大值的话，第一遍求得的 $pos_1$ 肯定是 $0$ 或 最大值。（如果想不明白的话，画个数轴看看就知道了）

然后第二遍询问，因为询问的东西带上了 $pos_1$，故得到的 $pos_2$ 一定是另外一个极值。（因为这样的话 $max-min$ 才会最大）

+ $b_i$ 的值全相同

我们的 $pos_1$ 肯定是一个极值（排除 $x_1,x_2$ 均为极值的情况），然后就可以肯定 $(1,pos_1)$ 为两个极值，上传。

+ $a_i$ 的值全相同

有可能 $x_1$ 是极值，所以我们需要用一次询问来特判这种情况。

询问$(1,pos_1,pos_2)$，返回值记为 $tmp$。

如果说，$tmp$ 大于任意 $a_i$ 的话，我们可以直接返回 $(1,2)$，感性理解容易。

+ Otherwise

通过不断的尝试，我发现此时询问 $(2,pos_1,pos_2)$ 可以有很大的用处：

我们令这次询问的返回值为 $rt$。

+ （$rt < a_{pos_1}$ 且 $rt \le a_{pos_2}$）或（$rt \le a_{pos_2}$ 且  $rt < a_{pos_1}$）

注意，一个是严格小于，另一个是小于等于。

这种情况对应了 $x_1$ 或 $x_2$ 为 $0$，因为：

$a_{pos_2}$ 查询的是 $(1,2,pos_2)$，$rt$ 查询的是 $(2,pos_1,pos_2)$

两者的区别就在于，一个是 $1$，一个是 $pos_1$。

然而，此时的 $rt$ 小于 $a_{pos_1}$，就说明，$x_1$ 会更往极端走一些。

然后到了这里，我们似乎发现了一个漏洞：$x_1$ 也许是最大值呀？

但这里我们之前已经排除这种情况了（$a$ 数组全部相同的情况），故排除。

但上述讨论都是基于 $x_2$ 不为 $0$ 的情况。保险起见，我们上传 $(1,2)$ 做为可能的答案。

+ $rt=a_{pos_1}$

通过比较 $a_pos1$ 和 $rt$ 查询的内容可以发现，在这种情况下，$x_2$ 和 $x_{pos_1}$ 中必然有一个是 $0$。应为此时的 $pos_2$ 也应该是向着极值发展的，然而改变后并没有使 $rt$ 和 $a_{pos_1}$ 变得不同，故 $x_2$ 和 $x_{pos_1}$ 为两个极值，上传 $(2,pos_1)$

+ $rt=a_{pos_2}$

同理，上传 $(2,pos_2)$

+ Otherwise


平凡情况，上传 $(pos_1,pos_2)$

---

次数：

询问次数为 $2n-3$ 或 $2n-2$ 次，符合要求。

---

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define reg register
const int mxn=1e3+3;
int n;
int a[mxn],b[mxn];
inline int ask(int x,int y,int z){
	cout<<"? "<<x<<' '<<y<<' '<<z<<endl;
	fflush(stdout);
	int rt;cin>>rt;
	return rt;
}
inline void print(int x,int y){
	cout<<"! "<<x<<' '<<y<<endl;
	fflush(stdout);
	return;
}
inline void solve(){
	cin>>n;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int pos1=1;
	int allsame=1;
	int lst=-1;
	for(int i=3;i<=n;++i){
		a[i]=ask(1,2,i);
		if(a[i]>a[pos1])pos1=i;
		if(lst==-1)lst=a[i];
		else{
			if(a[i]!=lst){
				lst=a[i];
				allsame=0;
			}
		}
	}
	int allsame2=1,lst2=-1;
	int pos2=1;
	for(int i=2;i<=n;++i){
		if(i==pos1)continue;
		b[i]=ask(1,i,pos1);
		if(b[i]>=b[pos2])pos2=i;
		if(lst2==-1)lst2=b[i];
		else if(lst2!=b[i])allsame2=0;
	}
	if(pos2==2)++pos2;   //当n较小的时候可能会出现pos2=2的阴间情况，需手动更改
	if(pos2==pos1)++pos2;
 
	if(allsame==1){//this can all be x[1]-x[2]
		int t=ask(1,pos1,pos2);
		if(t<lst){
			print(1,2);
			return;
		}
	}
	//now if both x[1] and x[2] isn't 0 this is okay
	//if x[2] is 0? what will happen?
	//a[i] will be x[i]. How to ensure it?
	//we can ask(2,pos1,pos2) to check
	//if x[1] is 0: it is smaller than either a[pos1] or a[pos2] we can return [1,1]
	//if x[2] is 0: this returns a[pos1 or pos2] then we can return [2,pos1 or pos2]
	//otherwise we can return [pos1,pos2]
	//oops,there still can be x[1] is max and pos1 is zero
	if(allsame2==1){
		print(1,pos1);
		return;
	}
	int t=ask(2,pos1,pos2);
	if((t<a[pos1] and t<=a[pos2]) or (t<=a[pos1] and t<a[pos2])){
		print(1,2);
		return;
	}
	if(t==a[pos1]){
		print(2,pos1);
		return;
	}
	if(t==a[pos2]){
		print(2,pos2);
		return;
	}
 
	print(pos1,pos2);
	return;
}
int main(){
	int T=1;
	cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

## 作者：2021CHD (赞：5)

## 注意事项
 
**这是一道交互题，注意刷新缓存区。**

（C++）推荐使用 `endl` 换行以刷新缓存区。

本题解包含 $2$ 种做法，其中第二种做法较优。

本题解中，“问”是动词，“询问”是名词，“回答”是名词，指交互库对于程序做出的询问的反馈，“答案”指可以作为最终结果的位置。
 
## 题目大意

已知正整数 $n$。 

有一个长为 $n$ 非负整数数列 $a$，**其中恰有一个数是 $0$**。

每个询问可以问三个数并得到这三个数的最大值减最小值之差。

要求在至多 $2n-2$ 个询问中求得**两个位置，其中至少有一个位置的数是 $0$**。

有 $t$ 组测试数据。

满足 $1\le t\le500$，$4\le n\le1000$，$0\le a_i\le10^9$，$4\le\sum n\le3000$。

## 解法一（标算）

考虑从 $n=4$ 开始解决。 

对于 $n=4$，可以问所有的不同的 $4$ 种询问，同时包含最大值和最小值时回答一定是最大的，并且最大值至少有两个（因为同时包含最大值和最小值的三元组至少有两个）。 

那么，对于任意的 $n$ 可以做若干次 $n=4$ 的情况解决，具体地，每 $4$ 次询问可以排除 $2$ 个不是答案的位置。

如果 $n$ 是偶数，则通过 $2n-4$ 次询问后刚好剩下 $2$ 个答案。

如果 $n$ 是奇数，则通过 $2n-6$ 次询问后剩下 $3$ 个可能的答案，此时可以再随便用一个位置凑齐 $4$ 个位置，再做一次 $n=4$ 即可。那么我们需要做 $2n-2$ 次询问，恰好满足限制。 

**注意：如果一个区间的最小值超过 $1$ 个，那么做一次 $n=4$ 的情况不一定能返回任何一个最小值，但是此时最小值一定不会是 $0$**（因为 $0$ 只有 $1$ 个）**，所以这样做的正确性是有保证的。**

时间复杂度：$O(\sum n)$。空间复杂度：$O(1)$。单个测试数据所需询问数量：$2(n+n\bmod2)-4$。

代码略。

## 解法二

考虑优化解法一。

我们知道，对于 $n=4$，所有不同的 $4$ 种询问中，至少有**两个最大值**。

所以我们可以随便问 $3$ 次，如果 $3$ 个回答中的最大值只有 $1$ 个，那么我们没有问的那一次的回答也会是最大值。如果 $3$ 个回答中的最大值至少有 $2$ 个，那么我们已经找到了 $2$ 个最大值（我们没有问的那一次的回答不会超过这个最大值，否则最大值就只有 $1$ 个了）。

**所以，$3$ 个询问足以解决 $n=4$ 的情况。**

对于 $n$ 为偶数，可以直接套用解法一。

对于 $n$ 为奇数，可以套用解法一至只剩下 $3$ 个可能的答案的时候。

这 $3$ 个可能的答案一定有 $2$ 个是上一轮 $n=4$ 的时候留下的，那么就一定至少做过一次包含这两个数的询问，我们取那一个询问的第 $3$ 个数补齐 $4$ 个数就可以节约 $1$ 次询问。 

例如：$n=5$，我们分别进行了 `? 1 2 3`，`? 1 2 4`，`? 1 3 4` 这 $3$ 次询问，排除了 `1` 和 `3`，还剩 `2 4 5` 是可能的答案，那么我们可以补入 `1`，形成 `1 2 4 5` 的 $4$ 个位置，其中 `? 1 2 4` 已经问过了，没有必要再问了，于是我们只需再问 `? 1 2 5` 和 `? 1 4 5` 就可以解决问题。

时间复杂度：$O(\sum n)$。空间复杂度：$O(1)$。单个测试数据所需询问数量：$\lceil\frac{3}{2}n\rceil-3$。

通过的记录：[洛谷](https://www.luogu.com.cn/record/141460938)，[Codeforces](https://codeforces.com/contest/1634/submission/239597849)。

参考代码如下（不含注释）。

```
#include<iostream>
using namespace std;
int T,I,n,i,j,k,x,y,last,lastx,q[5],s[5],t;
main()
{
	cin>>T;
	for(I=1;I<=T;I++)
	{
		cin>>n;
		x=1;
		y=2;
		if(n%2==0)
		for(i=3;i<=n-1;i=i+2)
		{
			for(j=1;j<=3;j++)
			s[j]=j;
			cout<<"? "<<x<<" "<<y<<" "<<i<<endl;
			cin>>q[1];
			cout<<"? "<<x<<" "<<y<<" "<<i+1<<endl;
			cin>>q[2];
			cout<<"? "<<x<<" "<<i<<" "<<i+1<<endl;
			cin>>q[3];
			for(j=1;j<=3;j++)
			for(k=j+1;k<=3;k++)
			if(q[j]>q[k])
			{
				t=q[j];
				q[j]=q[k];
				q[k]=t;
				t=s[j];
				s[j]=s[k];
				s[k]=t;
			}
			if(q[2]!=q[3])
			if(s[3]==1)
			{
				x=y;
				y=i;
			}
			else if(s[3]==2)
			{
				x=y;
				y=i+1;
			}
			else
			{
				x=i;
				y=i+1;
			}
			else if(s[1]==1)
			y=i+1;
			else if(s[1]==2)
			y=i;
		}
		else
		{
			for(i=3;i<=n-2;i=i+2)
			{
				for(j=1;j<=3;j++)
				s[j]=j;
				cout<<"? "<<x<<" "<<y<<" "<<i<<endl;
				cin>>q[1];
				cout<<"? "<<x<<" "<<y<<" "<<i+1<<endl;
				cin>>q[2];
				cout<<"? "<<x<<" "<<i<<" "<<i+1<<endl;
				cin>>q[3];
				for(j=1;j<=3;j++)
				for(k=j+1;k<=3;k++)
				if(q[j]>q[k])
				{
					t=q[j];
					q[j]=q[k];
					q[k]=t;
					t=s[j];
					s[j]=s[k];
					s[k]=t;
				}
				if(q[2]!=q[3])
				{
					lastx=x;
					last=q[3];
					if(s[3]==1)
					{
						x=y;
						y=i;
					}
					else if(s[3]==2)
					{
						x=y;
						y=i+1;
					}
					else
					{
						x=i;
						y=i+1;
					}
				}
				else if(s[1]==1)
				{
					lastx=y;
					if(s[2]==2)
					last=q[2];
					else
					last=q[3];
					y=i+1;
				}
				else if(s[1]==2)
				{
					lastx=y;
					if(s[2]==1)
					last=q[2];
					else
					last=q[3];
					y=i;
				}
				else
				{
					lastx=i;
					if(s[2]==1)
					last=q[2];
					else
					last=q[3];
				}
			}
			q[1]=last;
			cout<<"? "<<lastx<<" "<<x<<" "<<n<<endl;
			cin>>q[2];
			cout<<"? "<<lastx<<" "<<y<<" "<<n<<endl;
			cin>>q[3];
			for(i=1;i<=3;i++)
			s[i]=i;
			for(i=1;i<=3;i++)
			for(j=i+1;j<=3;j++)
			if(q[i]>q[j])
			{
				t=q[i];
				q[i]=q[j];
				q[j]=t;
				t=s[i];
				s[i]=s[j];
				s[j]=t;
			}
			if(q[2]==q[3])
			{
				if(s[1]==1)
				x=n;
			}
			else if(s[3]==2)
			y=n;
			else if(s[3]==3)
			x=n;
		}
		cout<<"! "<<x<<" "<<y<<endl;
	}
}
```

---

## 作者：zcxxnqwq (赞：4)

可能自认为是分类讨论比较简单的做法？

首先由于我们只能询问序列里三个数之间的极差，所以我们是无法确定 $0$ 的位置的，但发现我们可以通过找到极差最大的三元组，找到序列里的最大值和最小值，而最小值一定是 $0$，所以我们最后只要输出两个极值的位置即可。

那么现在的问题就是如何利用规定的 $2n-2$ 次询问获得极值的信息。对于每次询问的三元组 $(i,j,k)$，固定 $i$ 和 $j$（假设 $i=1$，$j=2$ ），枚举 $k$ 来做 $n-2$ 次询问，设询问得到的最大值为 $mx1$，此时 $k=pos1$，那么理想状态下，我们得到的 $pos1$ 就是序列的最大值/最小值所在位置。此时固定 $i$ 为 $pos1$，再任意指定一个 $j$，理想状态下，我们再做 $n-2$ 次询问去求 $mx2$ 和 $pos2$，$pos2$ 就是序列的最小值/最大值，输出 $pos1$ 和 $pos2$ 即可。

问题在于实际情况不一定能达到理想状态。

对特殊情况进行分类讨论：

- $1$ 和 $2$ 就是两个极值的位置。

若这种情况成立，我们做第一组询问的时候每次得到的值一定是不变的，但每次查询值不变并不能推出 $1$ 和 $2$ 就是极值，详见样例。我们再考虑加上第二组询问：如果 $1$ 和 $2$ 是极值，那么固定另外两个节点得到的结果 $mx2$ 一定不大于 $mx1$。根据这两个性质我们就可以特判掉这种情况。

- 第二次任意指定的固定点 $j$ 就是除 $pos1$ 外另一个极值位置。

这个就更好判断了，排除上一种情况后，若第二组询问每次得到的值都不变，那么就是这种情况。

然后这道题就做完了 qwq
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
#define qk fflush(stdout)
const int N=1005;
int n,a[N];
inline void solve(){
	qk;
	scanf("%d",&n);
	printf("? 1 2 3\n"),qk;
	int mx1,flag1=1,pos=3;
	scanf("%d",&mx1);
	ff(i,4,n){
		printf("? 1 2 %d\n",i),qk;
		int tmp;
		scanf("%d",&tmp);
		if(tmp!=mx1) flag1=0;
		if(tmp>mx1) mx1=tmp,pos=i;
	}
	int ans1=pos,flag2=1,mx2=0;
	pos=(pos==n)?n-1:pos+1;
	int ans2=pos;
	ff(i,1,n) if(i!=ans1&&i!=pos){
		printf("? %d %d %d\n",ans1,pos,i),qk;
		int tmp;
		scanf("%d",&tmp);
		if(mx2&&tmp!=mx2) flag2=0;
		if(tmp>mx2) mx2=tmp,ans2=i;
	}
	if(flag1&&mx1>=mx2) printf("! %d %d\n",1,2);
	else if(flag2) printf("! %d %d\n",ans1,pos);
	else printf("! %d %d\n",ans1,ans2);
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```


---

## 作者：Rushroom (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/jax4sn8m.png)

良题。![qq_emoji: qiang](https://xn--9zr.tk/qiang)![qq_emoji: qiang](https://xn--9zr.tk/qiang)![qq_emoji: qiang](https://xn--9zr.tk/qiang)

[传送门](https://www.luogu.com.cn/problem/CF1634D)

#### 本题解共提供 2 种做法。

## 做法·壹

官方题解提供的做法。

### Hint 1

先考虑 $n=4$ 的情况。

设提问除了 $i$ 以外的 3 个数，得到的结果是 $\bar{i}$，我们可以提问四次，得到 $\bar{1},\bar{2},\bar{3},\bar{4}$。

不妨设 $a_1 \geq a_2 \geq a_3 \geq a_4$，所以 $a_4=0$，易得：

$\begin{cases}\bar{1}=a_2-a_4=a_2\\\bar{2}=a_1-a_4=a_1\\\bar{3}=a_1-a_4=a_1\\\bar{4}=a_1-a_3\end{cases}$

$\because a_1 \geq a_2 \geq a_3 \geq a_4$

$\therefore \bar{2}= \bar{3}\geq\bar{1},\bar{4}$

综上，我们可以确定，对于最大的两个 $\bar{i}$，$a_i \ne 0$。

所以排除了两个，还剩两个，问题解决。

### Hint 2

思考：还是 $n=4$ 的情况，如果这四个数中没有 0，上述结论是否仍然成立？

容易发现，只要将上面前三只柿子的最后一步化简去掉就可以了。

其实，结论是仍然成立的，不信可以自己算一算。

### Solution

现在考虑 $n>4$ 的情况。

其实也很简单，就是每次选出 4 个还没被排除的数，然后进行一次上述操作，排除掉 2 个。最后就只剩下 2 个了。

**这时候有可能就有小伙伴要问了：如果 $n$ 是奇数怎么办啊？**

把之前已经排除的一个数补到最后面就行了。

这个做法相当于每次用 4 次询问排除 2 个数，所以可以算出，需要的询问次数刚刚好是 $2 \cdot n -2$ 次。

### Code

由于本人没有用这种做法，并且十分的懒惰，所以没有参考代码。

## 做法·贰

本人十分推荐的算法！

~~但是在赛时没有做出来~~

可怜人 の Submissions:

![](https://cdn.luogu.com.cn/upload/image_hosting/d1cljlqg.png)

### Hint 1

确定最大的数是哪个。

首先，我们**假设** $a_1$ 和 $a_2$ 不是最大的和最小的，然后对于每一个 $3 \leq i \leq n$ 我们询问 ```? 1 2 i```。

~~容易~~发现，回答最大的 $x$，$a_x$ 要么是最大的，要么是 0。

我们可以形象化的想一想，询问 ```? i j k``` 的答案就相当于是：最短的包含在数轴上分别表示 $a_i,a_j,a_k$ 的三个点的线段的长度。

**这时候有可能就有小伙伴要问了：如果 $a_1$ 和 $a_2$ 刚好就是最大的和最小的怎么办啊？**

别急，我们待会来回答。

### Hint 2

我们先把这个数放在答案的第一个位置，这样就只需要考虑这个数是最大数的情况了。

我们再**假设** $a_1 \ne 0$，对于每一个 $i \ne 1,x$，询问 ```? 1 x i```。

~~容易~~发现，回答最大的 $y$，$a_y=0$。道理很简单：回答的最大值肯定是提问中包含 0 和最大值。

#### 现在回答上面那个小伙伴的问题。

如果 $a_1$ 和 $a_2$ 刚好就是最大的和最小的，那么得出的 $x,y$ 一定不是最大的和最小的。我们只需要随便找除了 $1,x,y$ 以外的一个数 $z$，查询 ```? x y z```。

如果得出的结果等于之前回答的最大值，那么可以确定，答案就是 $x$ 或 $y$。

**这时候有可能又有小伙伴要问了：如果是小于呢？**

我们发现，之前有两个假设。所以一定是下面两种情况之一：

>$a_1$ 和 $a_2$ 刚好就是最大的和最小的
>
>$a_1 = 0$

容易发现，不管是哪种情况，$a_1$ 一定是最大的或最小的。

我们只需要询问 ```? 1 x z``` 和 ```? 1 y z```（$z$ 的意义同上）。如果前者大，则输出 ```! 1 x```，否则输出 ```! 1 y```。

### 一个小 trick

我们发现，```? 1 2 x``` 其实被询问了两次（第一轮和第二轮中都有），所以可以少询问一次，总询问次数为 $2 \cdot n-3$ 次。

~~建议加强题目~~

### Code

用上面的小 trick 优化过后的代码。

```cpp
/*
 * @Description: I want to be the weakest vegetable in the world!
 * @Author: CGBoy
 * @Date: 2022-02-06 23:27:17
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, a[1010], mx, id, id2, st, x, y;
bool suc;
void solve() {
    cin >> n;
    forr(i, 3, n) {
        cout << "? 1 2 " << i << endl;
        cout.flush();
        cin >> a[i];
    }
    mx = 0;
    forr(i, 3, n) {
        if (a[i] > mx)mx = a[i], id = i;
    }
    a[2] = a[id];
    repp(i, n) {
        if (i != id && i != 1) {
            if (i != 2) {
                cout << "? " << id << ' ' << 1 << ' ' << i << endl;
                cout.flush();
                cin >> a[i];
            }
        }
        else a[i] = -1;
    }
    mx = 0;
    repp(i, n) {
        if (a[i] > mx)mx = a[i], id2 = i;
    }
    int o = 2;
    while (o == id || o == id2)o++;
    cout << "? " << id << ' ' << id2 << ' ' << o << endl;
    cout.flush();
    cin >> x;
    if (x == mx) {
        cout << "! " << id << ' ' << id2 << endl;
        cout.flush();
        return;
    }
    cout << "? " << id << ' ' << o << ' ' << 1 << endl;
    cout.flush();
    cin >> x;
    if (x == mx) {
        cout << "! " << id << ' ' << 1 << endl;
        cout.flush();
        return;
    }
    cout << "! " << id2 << ' ' << 1 << endl;
    cout.flush();
    return;
}
int main() {
    T_ = 1;
    cin >> T_;
    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}
```

## QAQ

什么时候洛谷能加入 Hint 功能啊。

![qq_emoji: qq](https://xn--9zr.tk/qq)![qq_emoji: qq](https://xn--9zr.tk/qq)![qq_emoji: qq](https://xn--9zr.tk/qq)

---

## 作者：_ReClouds_ (赞：2)

[更好的阅读体验](https://reclouds.github.io/post/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91CF1634D%20Finding%20Zero%20%E9%A2%98%E8%A7%A3.html)

-   注意：本文与官方题解不同，为笔者自己想到的做法，题解区如有雷同，纯属巧合。

### 题意

交互库中存在一个非负整数数列 $a_i$，给定其长度 $n~(n \ge 4)$，每次可以选择询问三个不同的位置 $i,j,k$，交互库会返回数列中对应的三个数的极差，即 $\max(a_i, a_j, a_k) - \min(a_i, a_j, a_k)$。现保证数列中恰好存在一个 $0$，请用最多 $2n-2$ 次询问求出 $0$ 的位置，回答时可以回答两个位置，只要有一个位置正确即可。

------

### 题解

我们知道，整个序列是非负的，并且恰好存在一个 $0$，说明 $0$ 是数列的最小值。换句话说，$0$ 是数列的极值。

同时，我们在回答时可以回答两个位置，这启发我们：如果我们已经知道数列中有两个位置分别对应了数列的两个极值（这里特指一个最大值和一个最小值），那么我们回答这两个位置即可。

所以算法的大致框架就出来了：确定数列的极值位置。

------

首先，我们可以先固定两个位置（下文以 $1,n$ 为例），询问它们和其它所有位置 $i$ 的值（即所有的 $\max(a_1, a_n, a_i) - \min(a_1, a_n, a_i)$）。这一步一共用去了 $n-2$ 次询问。

得到了所有位置的值之后，我们就需要分情况讨论了。

$\mathcal{A}.$ 所有值中的最大值和最小值相等

最大值和最小值相等，其实就说明了所有数都相等。

也就是说，$a_1$ 和 $a_n$ 两个位置有可能直接对应了最大值和最小值，因为无论怎样询问，得到的答案都是 $|a_1 - a_n|$。

但这是唯一的情况吗？显然不是，因为还存在另外一种情况：

如果把所有数放在数轴上，发现它们最多只有 $4$ 个本质不同的数（且至少有 $3$ 个本质不同的数），并且 $a_{2 \sim n - 1}$ 这些数关于一个数的位置或者两个数正中间的位置轴对称，那么 $a_1$ 和 $a_n$ 也可能对应了这个对称轴所对应的一个数或者两个数。

举两个例子（分别对应一个数和两个数做为对称轴的情况）：
$$
\begin{matrix}
a_i: 1,2,0,2,1
\\
a_i: 1,3,0,3,2
\end{matrix}
$$
第一个例子中，$1$ 即为对称轴，并且 $a_1=a_n=1$，可以发现只出现了 $3$ 个本质不同的数，并且每一个位置的值都相等。

第二个例子中，$1$ 和 $2$ 正中间的位置即为对称轴，并且有 $a_1 = 1,a_n=2$，可以发现只出现了 $4$ 个本质不同的数，并且同样可以发现每一个位置的值都相等。

在这一种情况中，$a_1,a_n$ 并非极值，但是它满足了前提条件 $\mathcal{A}$。然而，单凭前 $n-2$ 次询问并不能区分这两种情况。

所以这个时候，我们再次拿出两个位置 $2$ 和 $n - 1$，再做 $n - 2$ 次询问得到每个位置的值（因为 $n\ge 4$，所以选择这两个位置不会有问题）。

这个时候，我们就得继续分情况讨论了。

$\alpha.$ 所有值中的最大值和最小值仍然相等

上面我们讨论了，如果两个位置做 $n - 2$ 次询问得到的所有值都相等，那么只会对应上述的两种情况。

并且，我们可以发现一个十分巧妙的结论：$a_1,a_n$ 和 $a_2,a_{n - 1}$ 这两对数，一定分别对应这两种情况。

证明：

如果两个位置分别对应了一个最大值和一个最小值，由于最小值为 $0$ 且只有一个，所以另一对数一定不会对应这种情况。

如果两个位置分别对应了对称轴所对应的一个或两个数，由于对称轴上不会出现除这两个位置之外的任何位置（否则最小值就为 $0$，由于所有的 $a_i$ 不会全部相等，那么其必然小于最大值），所以另一对数也不会对应这种情况。

证毕。

所以，如果我们能区分这两种情况，那么就可以得到极值的两个位置。

区分它们很简单：如果做 $n - 2$ 次询问后，一对数所得到的值大于另一对得到的值（没有歧义，因为两对数得到的所有值分别是相等的），说明前者是极值的位置，反之说明后者是极值的位置。

理由很简单：整个序列的极差一定会大于等于子序列的极差，而等于的情况在这里一定不会出现。

$\beta.$ 所有值中的最大值和最小值不相等

这里我们也得分情况讨论：

1. $1,n$ 两个位置对应的是最大值和最小值，而 $2,n - 1$ 两个位置对应了任意两个不属于 $\mathcal{A}-\alpha$ 情况的两个数；

2. $1,n$ 对应的是对称轴所对应的一个或两个数，而 $2,n - 1$ 两个位置对应了两个最大值。

对于第一种情况，我们直接输出 $1,n$ 两个位置即可。

对于第二种情况，我们找到 $2,n-1$ 两个位置询问 $n - 2$ 次后获得的最大值所对应的位置，这个位置即为 $0$ 所在的位置。

区分也很简单，我们直接通过 $\mathcal{A}-\alpha$ 情况中得出的结论来区分即可：如果做 $n - 2$ 次询问后，$a_2,a_{n-1}$ 这对数获得的最大值大于 $1,n$ 获得的最大值，那么为情况 $\mathcal{A}-\alpha-2$，否则为情况 $\mathcal{A}-\alpha-1$。

$\mathcal{B}.$ 所有值中的最大值和最小值不相等

这个情况就显得简单一些了，因为它没有那么多的分类讨论。

我们把所有值中的最大值所对应的位置拿出来，可以发现它一定对应了一个极值。我们设这个位置为 $p$。

接着，我们拿 $1,p$ 这两个位置再询问 $n - 2$ 次，然后分情况讨论。

$\alpha.$ 所有值中的最大值和最小值相等

由于 $p$ 已经确定是一个极值了，因此 $1$ 一定也是一个极值，我们回答这两个位置即可。

$\beta.$ 所有值中的最大值和最小值不相等

我们再把这个最大值对应的位置拿出来，设其为 $q$，那么 $p,q$ 分别对应了最大值和最小值，我们回答这两个位置即可。

------

上述分讨的每一种情况询问次数均为 $n \cdot 2-4$，可以通过本题。

---

## 作者：tommymio (赞：2)

先说结论。

以下记 $M = \max(a_1, a_2, \cdots, a_n)$。令 $p_1$ 为取得询问 $(1,i,n)$ 最大值的 $i$，$p_2$ 为取得询问 $(1,p_1,i)$ 最大值的**最右端**的 $i$。则 $0$ 只会在 $1,p_1,p_2$ 这些位置上，可以通过简单的分类讨论得出，以下将会给出简单的讨论过程。

于是只需要 $2(n - 2)$ 次询问即可。

讨论如下：

- 若 $\min(a_1, a_n) = 0, \max(a_1, a_n) = M$
  - 询问 $(1, i, n)$ 取得相同的值
  - $p_2 = n$
  
- 若 $\min(a_1, a_n) = 0, \max(a_1, a_n) < M$
  - $a_{p_1} = M$
  - 对于询问 $(1, p_1, i)$ 
    - 若 $a_1 = 0$，询问 $(1, p_1, i)$ 取得相同的值
    - 若 $a_n = 0$，则 $p_2 = n$
  
- 若 $\min(a_1,a_n) > 0, \max(a_1,a_n) = M$
  - $a_{p_1} = 0$
  - 对于询问 $(1, p_1, i)$
    - 若 $a_1 = M$，询问 $(1, p_1, i)$ 取得相同的值
    - 若 $a_n = M$，则 $p_2 = n$

- 若 $\min(a_1, a_n) > 0, \max(a_1, a_n) < M$

  这是最复杂的部分，需要讨论一下 $\max(a_1, a_n)$ 与 $M - \min(a_1, a_n)$ 的关系，最后可以得到无论这两者大小关系如何，$0$ 都一定在位置 $p_1$ 或者 $p_2$ 上。

综上所述，$0$ 只会在 $1,p_1,p_2$ 这些位置上，具体情况根据必要条件直接判断即可。

（这个 markdown 渲染好烦啊，不支持多个缩进的。。。）

**Code**

```c++
#include<cstdio>
inline int getQuery(int i,int j,int k) {
	printf("? %d %d %d\n",i,j,k);
	fflush(stdout); 
	int x; scanf("%d",&x);
	return x;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n; scanf("%d",&n);
		if(n==2) {printf("! 1 2\n"); fflush(stdout); continue;} 
		int pos=-1,mx=0,tot=0;
		for(int i=2;i<n;++i) {
			int val=getQuery(1,n,i);
			if(val>mx) {
				mx=val;
				pos=i;
				tot=1;
			}
			else if(val==mx) {
				++tot;
			}
		}
		int pos2=-1,mx2=0,tot2=0;
		for(int i=2;i<=n;++i) {
			if(i==pos) continue;
			int val=getQuery(1,pos,i);
			if(val>mx2) {
				mx2=val;
				pos2=i;
				tot2=1;
			}
			else if(val==mx2) {
				pos2=i;
				++tot2;
			} 
		}		
		if(pos2==n&&tot==n-2) {printf("! 1 %d\n",n); fflush(stdout); continue;}      
		if(tot2==n-2) {printf("! 1 %d\n",pos); fflush(stdout); continue;}
		if(mx2>=mx) {printf("! %d %d\n",pos,pos2); fflush(stdout); continue;}//always satisfied
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：1)

## 前言

$$\texttt{SHALL WE PLAY A GAME?}$$

这场 $D\geq F$ 吧。

你可以把这一篇题解看作对某一篇远古题解的解释，至于是哪一篇就不挂了。

把这一篇题解写出来收获很大的说。

## 解题思路

注意到固定两个位置 $(a,b)$，然后使用 $n-2$ 次查询该两个位置与其他所有位置，即查询 $(a,b,x),x\ne a,b$。

若开头固定的两个位置不各自为极小极大值，则先前 $n-2$ 次查询得到的结果最大值中必定有一个 $x$ 为极值，记为 $p_1$。这三个数记为 $(a,b,p_1)$，该次询问值为 $m_1$。

我们考虑用另外 $n-2$ 次询问确定另一个极值的位置。另外钦定一个与 $a,b,p_1$ 都不同的位置 $d$，然后查询 $(p_1,d)$ 与其他所有位置，即查询 $(p_1,d,y),y\ne p_1,d$。

若 $d$ 不为极值，则查询 $(p_1,d,y)$ 得到的结果最大值中查询的三个数必定有一个极值 $y$，记为 $p_2$，该次询问值为 $m_2$。

于是我们开始分类讨论：
为方便表述，以下“$x$ 为 $y$”一类的表述均表示 $a_x=y$。

- 若 $m_2$ 小于等于 $m_1$，前 $n-2$ 次询问所有结果相等，则 $a,b$ 当中必定存在一个 $0$。
    - 必要性显然，但充分性如何证明？
    - 考虑前 $n-2$ 次询问所有结果相等带来的信息：由于询问至少会进行两次，若 $a,b$ 当中不存在 $0$ 则必定不存在最大值，原因是：若 $a,b$ 当中存在最大值而不存在 $0$，则必定有且仅有一个询问满足 $x=0$，其余询问的结果都必定小于这个询问，与条件冲突。
    - 整理上述结果可以得知：若 $a,b$ 当中存在最大值，则另外一个一定是 $0$，否则其中一定不存在最大值。
    - 接下来另外一个条件带来的影响：$m_2\gt m_1$。不难注意到，在上述的搜索策略下，若 $a,b$ 当中不存在极值，则 $p_1$ 必定为极值，而 $p_2$ 必定为另一个极值。由于固定两个值，询问其他值的最大结果为数列最大值的充分必要条件是固定值中有一个极值，且 $m_2$ 为数列最大值，所以当 $m_2\gt m_1$ 时，$a,b$ 当中无极值。
    - 两个条件同时满足的情况仅有 $a,b$ 都为极值以及 $a,b$ 当中存在一个 $0$ 的情况，此时查询 $(a,b)$ 必定有一个 $0$。
- 否则，若后 $n-2$ 次询问的结果均相等，则 $p_1,d$ 当中必定存在一个 $0$。
    - 沿用上述证明可以得知：在满足该条件的情况下，最大值不可能在没有 $0$ 的情况下单独存在。
    - 而 $p_1$ 又为一个极值，则可能的情况只有以下两种：$p_1$ 为最大值且 $d$ 为 $0$，或 $p_1$ 为 $0$。
    - 无论哪一种情况，$p_1,d$ 当中都有一个 $0$，即，此时查询 $(p_1,d)$ 必定有一个 $0$。
- 否则，$a,b,p_1,d$ 当中没有 $0$，由于 $p_2$ 为另一个极值，故查询到的 $p_2$ 必定为 $0$。

如此就完成了询问，查询次数 $2n-4$。

---

## 作者：DaiRuiChen007 (赞：1)

# CF1634D 题解



## 思路分析

同样的序列交互找特殊位置的问题，感觉上和 [1762D](https://codeforces.com/contest/1762/problem/D) 有点相似，那么考虑能否借鉴这道题的思路来求解。

在 1762D 中，我们每次用 $2$ 个询问来在 $3$ 个元素中排除掉 $1$ 个必然不为 $0$ 的元素，并且实时维护可能为答案的 $(x,y)$，那么在这个题目中，显然每次不能选 $3$ 个元素进行排除，考虑每次在 $4$ 个元素中排除 $2$ 个元素。

那么由于操作限制为 $2n-2$，因此对于每次排除可以进行 $4$ 个询问，所以我们可以求出对于其中任意三个元素进行询问得到的答案。

此时考虑进行排除的四个数 $a,b,c,d$，不妨设 $a<b<c< d$，显然只有 $a$ 可能为 $0$ 那么对于任何一个操作，我们能够得到：

- $\max(a,b,c)-\min(a,b,c)=c-a$
- $\max(a,b,d)-\min(a,b,d)=d-a$
- $\max(a,c,d)-\min(a,c,d)=d-a$
- $\max(b,c,d)-\min(b,c,d)=d-b$

观察到结果中有两个 $d-a$，而且我们知道 $d-a>c-a$ 且 $d-a>d-b$，因此四个结果中的最大值出现过两次，找到这两次对应的询问，而在两次询问中都出现的 $2$ 个元素即为 $a,d$，那么排除掉剩下的 $2$ 个即可。

不过由于题目不保证非 $0$ 的 $a_i$ 两两不等，因此我们实际上要考虑 $a\le b\le c\le d$，注意到只有 $a=0$ 时排除操作有意义，所以实际上 $a<b$ 依然成立，因此 $d-a>d-b$，又因为在剩下的 $3$ 个三元组 $(a,b,c),(a,b,d),(a,c,d)$ 中任取 $2$ 个的交都包含 $a$，因此这个解决方案是可行的。

不过由于我们每次排除 $2$ 个元素，假如 $2\nmid n$，那么有一个数会没有被考察过，我们可以在剩下的数中任取一个拿进来一起排除即可。

计算一下操作次数：

- $2\mid n$ 时：操作次数为 $4\times\dfrac{n-2}2=2n-4$。
- $2\nmid n$ 时：操作次数为 $4\times\left(1+\dfrac{n-3}2\right)=2n-2$。

因此这个策略是可以通过本题的。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
inline int read(int i,int j,int k) {
	cout<<"? "<<i<<" "<<j<<" "<<k<<endl;
	int ret; cin>>ret; return ret;
}
inline pii upd(int i,int j,int k,int l) {
	int a=read(i,j,k);
	int b=read(i,j,l);
	int c=read(i,k,l);
	int d=read(j,k,l);
	int x=max(max(a,b),max(c,d));
	if(a==x&&b==x) return make_pair(i,j);
	if(a==x&&c==x) return make_pair(i,k);
	if(a==x&&d==x) return make_pair(j,k);
	if(b==x&&c==x) return make_pair(i,l);
	if(b==x&&d==x) return make_pair(j,l);
	if(c==x&&d==x) return make_pair(k,l);
	return make_pair(0,0);
}
inline void solve() {
	int n;
	cin>>n;
	pii ans=make_pair(1,2);
	for(int i=3;i<n;i+=2) ans=upd(ans.first,ans.second,i,i+1);
	if(n%2==1) {
		for(int i=1;i<n;++i) {
			if(i!=ans.first&&i!=ans.second) {
				ans=upd(ans.first,ans.second,i,n);
				break;
			}
		}
	}
	cout<<"! "<<ans.first<<" "<<ans.second<<endl;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

从题目要求给出的结果入手，可以输出的两个其实是一个最大的一个最小的（也就是 $0$）。

从小的问题入手，先通过四组询问找出前四个的最值。这里直接取出较大的两个三元组中的共同部分，比较显然，不赘述。

然后就是在已经知道了之前一段的最大值和最小值如何拓展到一个新的位置，也就是更新两个最值。

---
不妨设两个最值为 $x$ 和 $y$，当前数 $i$。

询问 $(x,i,u)$ 和 $(y,i,u)$（$u$ 是之前已经确定的在最值中间的数，可以发现：如果新的数是一个新的最值，则 $u$ 不会对结果造成影响，否则也没有更新数据的必要，造成影响也无所谓。）如果这两个值都没有超过之前的答案，则新的数 $i$ 被夹在两个数中间，不需要更新。反之则有两个新的最值为两个答案中较大的一个中的那一个最值和新位置 $i$。

由此一直更新下去，在第四个位置以后的每一个位置都会有两次询问，第四个位置之前一共有 $4$ 次询问，总询问次数为 $4+2\times(n-4)$，也就是 $2n-4$，比要求的 $2n-2$ 小，满足条件。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a,b,c,d,maxn,x,y,ans,ans1;
int dif(int x,int y){
	if(x==1&&y==2)return 3;
	if(x==1||y==1)return 2;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		a=b=c=d=maxn=x=y=ans=0;
		scanf("%d",&n);
		printf("? 1 2 3\n");fflush(stdout);scanf("%d",&a);
		printf("? 2 3 4\n");fflush(stdout);scanf("%d",&b);
		printf("? 1 3 4\n");fflush(stdout);scanf("%d",&c);
		printf("? 1 2 4\n");fflush(stdout);scanf("%d",&d);
		maxn=max(max(a,b),max(c,d));
		if(maxn==a&&maxn==b)x=2,y=3;
		if(maxn==a&&maxn==c)x=1,y=3;
		if(maxn==a&&maxn==d)x=1,y=2;
		if(maxn==b&&maxn==c)x=3,y=4;
		if(maxn==b&&maxn==d)x=2,y=4;
		if(maxn==c&&maxn==d)x=1,y=4;
		for(int i=5;i<=n;i++){
			printf("? %d %d %d\n",y,i,dif(x,y));
			fflush(stdout);
			scanf("%d",&ans);
			
			printf("? %d %d %d\n",x,i,dif(x,y));
			fflush(stdout);
			scanf("%d",&ans1);
			
			if(ans>=ans1&&ans >maxn)x=i,maxn=ans;
			if(ans1>=ans&&ans1>maxn)y=i,maxn=ans1;
		}
		printf("! %d %d\n",x,y);fflush(stdout);
	}
	return 0;
}
```


---

## 作者：hh弟中弟 (赞：0)

跟 CF1762D 差不多是一个套路，下文中 $(a,b,c)$ 表示询问 $a,b,c$ 三个位置的结果，$x$ 位置的值记作 $x$。\
还是考虑排除不合法情况，如果三个数中有 $0$ 那么返回的数一定最大，考虑四个位置 $a,b,c,d$，钦定一下 $a\le b\le c\le d$，$(a,b,c)=c-a,(a,b,d)=d-a,(a,c,d)=d-a,(b,c,d)=d-b$，发现有两个 $d-a$ 且 $d-a\ge c-a,d-a\ge d-b$，所以一定有两个询问结果相等，且他们是最大值。\
如果有两个结果相等，那么 $a<b<c<d$，可以找到相应的两个询问，这两个询问不共有的两个位置一定对应着 $b,c$，可以直接排除。如果三个相等，那么 $a<b<c=d$ 或者 $a=b<c<d$，剩下的一个询问中的位置对应着 $b,c,d$，直接排除。如果四个相等，那么 $a=b=c=d$，全部都排除掉。经过上述分析，每四次询问可以至少排除两个位置，最后剩下两个，保证了询问次数。

---

## 作者：int_R (赞：0)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18103963/CF1634D)

每日一题系列。

在做过 [CF1762D GCD Queries](https://www.luogu.com.cn/problem/CF1762D) 后发现这个题跟那个 trick 一模一样，所以切了，尽管做那道的时候没有想出来。

----

每次任意选出四个数 $a,b,c,d$，规定 $a\leq b\leq c\leq d$。考虑询问这四个数中所有组合。然后仅保留可能为 $0$ 的位置，剩下的删掉。

$f(a,b,c)=c-a,f(a,b,d)=d-a,f(a,c,d)=d-a,f(b,c,d)=d-b$。

发现 $d-a\geq c-a$，当 $c=d$ 时取等；$d-a\geq d-b$，当 $a=b$ 时取等；所以这四个结果中会有 $2\sim 4$ 个最大值。

当最大值个数为 $2$，此时 $a\not=b,c\not=d$。我们的目的是保留 $a$，因为 $a$ 最小，只有 $a$ 有可能是 $0$。实际我们无法分辨 $a$ 和 $d$，所以均保留，即保留在这两个最大值对应情况中都出现的数。

当最大值个数为 $3$，此时有两种情况。当 $a=b,c\not=d$。因为 $0$ 只有一个，所以 $a$ 也不会是 $0$，我们不需要保留任何数。当 $a\not=b,c=d$。我们的目的仍是保留 $a$，此时 $a$ 是在三个最大值对应情况中都出现的数。实际我们无法分辨到底是哪两个数相等，所以无论究竟是哪种情况都保留在三个最大值对应情况中都出现的数。

当最大值个数为 $4$，此时 $a=b,c=d$，一个都不需要保留。

所以总结起来就是每次保留在**每个不**为最大值对应情况中**没**出现的数。每次最少删掉两个，最多操作步数为 $\lceil\dfrac{n-2}{2}\rceil\times 4$，刚好卡上界。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=3010;
int T,n,p[MAXN],tot;
inline void add(int k)//加回来一些数直到够 k 个
{
    for(int i=1;tot<k;++i)
    {
        bool flag=true;
        for(int j=1;j<=tot;++j)
            flag&=(p[j]!=i);
        if(flag) p[++tot]=i;
    }
}
inline void work()
{
    cin>>n;tot=n;
    for(int i=1;i<=n;++i) p[i]=i;
    while(tot>2)
    {
        int a[5],b[5],MAX=-1;add(4);//不够 4 个要加到 4 个
        for(int i=1;i<=4;++i) a[i]=p[tot--];
        for(int i=1;i<=4;++i)
        {
            cout<<"? ";
            for(int j=1;j<=4;++j)
                if(j!=i) cout<<a[j]<<' ';
            cout<<endl;cin>>b[i];MAX=max(MAX,b[i]);
        }
        for(int i=1;i<=4;++i)
            if(b[i]!=MAX) p[++tot]=a[i];
    }
    add(2);cout<<"! "<<p[1]<<' '<<p[2]<<endl;
}
int main()
{
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：Seauy (赞：0)

## 题目大意

- 有一个长度为 $n$ 的非负整数数列 $\{a_i\}$。

- 有且仅有一个 0。

- 每次询问操作选取三个不一样的下标 $i,j,k$，交互库回答 $\max(a_i,a_j,a_k)-\min(a_i,a_j,a_k)$。

- 回答两个可以一样的下标 $i,j$，满足 $a_i,a_j$ 中至少有一个 0。

- $1 \leq n \leq 10^3$，询问最多 $2n-2$ 次。

# 一. 思路

回答的下标有两个，大胆猜测一个是 0，另一个是序列中的最大值。一开始对序列一无所知，不妨先询问 $(1,2,3)$，之后只移动一个下标，比如把 3 遍历到 $n$。

设 $f(i,j,k)=\max(a_i,a_j,a_k)-\min(a_i,a_j,a_k)$，如果一开始 $a_i\leq a_k \leq a_j$，并且改变 $k$ 后 $f(i,j,k)$ 变大了（只能变大或不变），说明要么 $a_k<a_i$ 或者 $a_j<a_k$。

我们取使 $f(1,2,k)$ 最大的 $k$，如果最大最小值不在 $a_1,a_2$ 中，$a_k$ 此时就是整个序列的最大或者最小值，也就是说 $a_1,a_2,a_k$ 肯定至少包含序列中最大/最小值中的一个。

那我们继续把 2 遍历到 $n$ 取最大值得到 $j$，我们就同时有了最大或最小值，他们是 $a_1,a_j,a_k$ 中的某两个。注意到如果 $a_i$ 不是极值，那么改变 $i$ 不会改变 $f(i,j,k)$。我们就改变 $1,j,k$ 中的某一个，如果询问结果不变 0 就在另两个下标中。

移动 $k$ 消耗 $n-2$ 次询问，移动 $j$ 用了 $n-3$ 次，最后确定答案最多再用 $2$ 步，最差的时候查询 $2n-3$ 次能通过此题。

# 二. 代码

```cpp
/*
	动了一个位置没变，说明最大值在另两个中
	变大了，说明新位置大于或小于另两个值 
*/
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e3;

int n,maxn;
int A,B,C;

int Query(int a,int b,int c)
{
	printf("? %d %d %d\n",a,b,c),fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}

void Ans(int a,int b) {printf("! %d %d\n",a,b),fflush(stdout);}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		maxn=-1;
		for(int i=3;i<=n;i++)//n-2
		{
			int ret=Query(1,2,i);
			if(ret>maxn) maxn=ret,C=i;
		}
		B=2;
		for(int i=3;i<=n;i++)//n-3
		{
			if(i==C) continue;
			int ret=Query(1,i,C);
			if(ret>maxn) maxn=ret,B=i;
		}
		A=1;
		bool OK=0;
		for(int i=1;i<=n;i++)
		{
			if(A==i || B==i || C==i) continue;
			if(maxn==Query(i,B,C)) {Ans(B,C),OK=1;break;}
			else break;
		}
		if(OK) continue;
		for(int i=1;i<=n;i++)
		{
			if(A==i || B==i || C==i) continue;
			if(maxn==Query(A,i,C)) {Ans(A,C),OK=1;break;}
			else break;
		}
		if(OK) continue;
		Ans(A,B);
	}
	return 0;
}
```


---

## 作者：IvanZhang2009 (赞：0)

[CF1634D](https://www.luogu.com.cn/problem/CF1634D)

## 题意
**这是一道交互题**

有一个未知的长度为 $n$ 的数组 $a$，其中 **有且仅有一个** $0$。最多可以做 $2\cdot n-2$ 次询问，询问内容 `? i j k`，返回 $\max(a_i,a_j,a_k)-\min(a_i,a_j,a_k)$。之后猜测 $0$ 的位置，输出 `! x y`。若 $a_x=0$ 或 $a_y=0$，则答案正确。

## 解法
先考虑 $n=4$ 时的解法。

询问 $\texttt{? 2 3 4}$，得到 $x_1$。

询问 $\texttt{? 1 3 4}$，得到 $x_2$。

询问 $\texttt{? 1 2 4}$，得到 $x_3$。

询问 $\texttt{? 1 2 3}$，得到 $x_4$。

若数组 $a$ 为 $\{0,1,2,3\}$，则返回的 $x_1=2$，$x_2=3$，$x_3=3$，$x_4=2$，容易发现询问的四组中，等于四个结果中最大值的 $x_i$，4 个数中除了 $a_i$ 的三个数必然有一个是 0，所以 $a_i$ 必然不是 0。

这时使用排除法，选出可能是 0 的两个数，输出。

当 $n\ge5$ 的时候呢？

先从前 4 个数开始操作，每次再往后选 2 个数，加上前面选出的可能是 0 的两个数进行 $n=4$ 时的操作，选出新的可能是 0 的两个数。
 
如果 $n$ 是奇数，则选择前面一个不可能为 0 的加在最后一位，将 $n$ 作为偶数操作。而此时需要注意的是询问时编号不能是 $n+1$。

若 $n$ 为偶数，则操作次数为 $2\cdot n-4$;若 $n$ 为奇数，则操作次数为 $2\cdot n-2$，都符合要求。

## 代码
```cpp
int a[3005];   //询问使用的数组（好像不用开数组……）
pii ans={1,2};  //可能的答案
void aSk(int x,int y,int z,int &v){ //询问，输入在 v 中
	cout<<"? "<<x<<' '<<y<<' '<<z<<endl;
	cout.flush();
	cin>>v;
}
void chans(int A,int b,int c,int d){  //更新答案
	int mx=max({a[A],a[b],a[c],a[d]});
	if(a[A]==mx&&a[b]==mx)ans={c+1,d+1};
	if(a[c]==mx&&a[b]==mx)ans={A+1,d+1};
	if(a[A]==mx&&a[c]==mx)ans={b+1,d+1};
	if(a[A]==mx&&a[d]==mx)ans={b+1,c+1};
	if(a[d]==mx&&a[c]==mx)ans={A+1,b+1};
	if(a[b]==mx&&a[d]==mx)ans={A+1,c+1};
}
void total_ask(int o,int p,int q,int r){ //每一次操作
	aSk(o,p,q,a[r-1]);
	aSk(o,p,r,a[q-1]);
	aSk(o,r,q,a[p-1]);
	aSk(r,p,q,a[o-1]);
	chans(o-1,p-1,q-1,r-1);
}
void Main() {
	int n;
	cin>>n;
	total_ask(1,2,3,4);
	for(int i=4;i<n-1;i+=2) total_ask(ans.first,ans.second,i+1,i+2);
	if(n&1){
		int v=1;
		while(v==ans.first||v==ans.second)v++;
		total_ask(ans.first,ans.second,n,v);
	}
	cout<<"! "<<ans.first<<' '<<ans.second<<endl;
}
```

---

