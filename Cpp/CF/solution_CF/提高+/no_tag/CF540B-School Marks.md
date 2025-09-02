# School Marks

## 题目描述

Little Vova studies programming in an elite school. Vova and his classmates are supposed to write $ n $ progress tests, for each test they will get a mark from 1 to $ p $ . Vova is very smart and he can write every test for any mark, but he doesn't want to stand out from the crowd too much. If the sum of his marks for all tests exceeds value $ x $ , then his classmates notice how smart he is and start distracting him asking to let them copy his homework. And if the median of his marks will be lower than $ y $ points (the definition of a median is given in the notes), then his mom will decide that he gets too many bad marks and forbid him to play computer games.

Vova has already wrote $ k $ tests and got marks $ a_{1},...,a_{k} $ . He doesn't want to get into the first or the second situation described above and now he needs to determine which marks he needs to get for the remaining tests. Help him do that.

## 说明/提示

The median of sequence $ a_{1} $ , ..., $ a_{n} $ where $ n $ is odd (in this problem $ n $ is always odd) is the element staying on $ (n+1)/2 $ position in the sorted list of $ a_{i} $ .

In the first sample the sum of marks equals 3 + 5 + 4 + 4 + 1 = 17, what doesn't exceed 18, that means that Vova won't be disturbed by his classmates. And the median point of the sequence {1, 3, 4, 4, 5} equals to 4, that isn't less than 4, so his mom lets him play computer games.

Please note that you do not have to maximize the sum of marks or the median mark. Any of the answers: "4 2", "2 4", "5 1", "1 5", "4 1", "1 4" for the first test is correct.

In the second sample Vova got three '5' marks, so even if he gets two '1' marks, the sum of marks will be 17, that is more than the required value of 16. So, the answer to this test is "-1".

## 样例 #1

### 输入

```
5 3 5 18 4
3 5 4
```

### 输出

```
4 1
```

## 样例 #2

### 输入

```
5 3 5 16 4
5 5 5
```

### 输出

```
-1
```

# 题解

## 作者：OIer_Hhy (赞：1)

~~这蓝题也太水了吧……~~

这道题，我们用贪心。

既然要让中位数尽量大，又要让总和尽量小，我们就让中位数正好为 $y$。

首先我们判断总司令的情况：总和超过 $x$，直接输出 $-1$。

其次，我们用一个变量 `sum` 维护当前的和，用 `cnt` 维护现在有多少个数 $\ge y$。

我们知道，当 $n$ 为奇数时，中位数 $y$ 左边和右边的数是一样多的。

如果 $a$ 中 $\ge y$ 的数很少，两边数的个数就不能保持平衡，也直接输出 $-1$。

我们在左边添加 $1$，右边添加 $y$，即可让 $y$ 成为中位数。

于是我们可以先算出中位数的下标 `mid`，再计算两边需要添加的数的数量。

当和 $>x$ 时，无解。

否则输出 一串 $1$ 和一串 $y$。

My code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,k,p,x,y,a[N],sum,cnt;
int main(){
	cin>>n>>k>>p>>x>>y;
	for(int i=1;i<=k;i++){
		cin>>a[i],sum+=a[i],cnt+=a[i]>=y;
	}
	if(sum+(n-k)>x){ // 无解
		puts("-1");
		return 0;
	}
	int mid=(n+1)>>1;
	if(cnt+(n-k)<mid){ // 无解
		puts("-1");
		return 0;
	}
	int t=max(0,mid-cnt);
  	// 求两边添加 1 和 y 后的总和
	for(int i=1;i<=n-k-t;i++)sum+=1;
	for(int i=1;i<=t;i++) sum+=y;
	if(sum>x){ // 无解
		puts("-1");
		return 0;
	}
	// 输出
	for(int i=1;i<=n-k-t;i++)cout<<1<<" ";
	for(int i=1;i<=t;i++)cout<<y<<" ";
	puts("");
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

## 思路

首先求出整个数列中应要大于等于中位数（ 也就是 $y$ ）的数字数量 $cnt=\dfrac{n+1}{2}$ 。

接着，可以用 $now$ 这个变量表示前 $k$ 个数中大于等于中位数的数字数量。

1. 如果后面不管怎么填都不可能会有至少 $cnt$ 个数大于等于中位数（ 也就是 $now+n-k<cnt$ ），无解。

2. 如果可以，则用一个变量 $res$ 表示后面应该填补的大于等于中位数的数字数量，那么 $res=\max(0,cnt-now)$ 。

为了使得总和最小，我们只需要将后面 $res$ 个数字填补成 $y$ ，其它数字填成 1 就可以了。

如果最后总和超过了 $x$ ，无解。如果没有超过，输出答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1000;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,k,p,x,y,cnt,now,sum;
int a[Maxn+5];

int main()
{
    n=read(),k=read(),p=read(),x=read(),y=read(),cnt=(n+1)/2;
    for(register int i=1;i<=k;++i)
    {
        a[i]=read();
        if(a[i]>=y) now++;
    }
    if(now+n-k<cnt) // 数字数量不够
    {
        printf("-1");
        return 0;
    }
    int res=max(0,cnt-now);
    for(register int i=k+1;i<=k+res;++i) // 填补中位数
        a[i]=y;
    for(register int i=k+res+1;i<=n;++i) // 填补最小数 1
        a[i]=1;
    for(register int i=1;i<=n;++i)
        sum+=a[i];
    if(sum>x) printf("-1");
    else
        for(register int i=k+1;i<=n;++i)
            printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：A_zjzj (赞：1)

### 一道贪心题

为了让这个序列达到中位数且总和最小，那么肯定是中位数越小越好，就让他是 $y$ 。

因为中位数是从小到大排序之后第 $\lfloor\frac{n}{2}\rfloor+1$ 个数，所以比中位数小的数一共有 $\lfloor\frac{n}{2}\rfloor$ 。

那么为了让总和最小，就让这些比中位数小的数是 $1$ ，不比中位数小的数是 $y$ ，就可以了。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,p,x,y,a[1000],sum,tot;
int main(){
	scanf("%d%d%d%d%d",&n,&k,&p,&x,&y);
	for(int i=1;i<=k;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
		if(a[i]<y)tot++;
	}
	if(x-sum<n-k||n/2<tot)return printf("-1"),0;
	if(sum+min(n/2-tot,n-k)+y*max(n-n/2+tot-k,0)>x)return printf("-1"),0;
	for(int i=1;i<=max(n-n/2+tot-k,0);i++)printf("%d ",y);
	for(int i=1;i<=min(n/2-tot,n-k);i++)printf("1 ");
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

贪心，先新建两个变量，$sum$ 和 $cnt$，分别表示当前序列的总和，和当前有多少个数不小于 $y$，$sum$ 的用处很明显，那 $cnt$ 是干什么用的呢？因为想要使中位数不小于 $y$，那么序列中不小于 $y$ 的数就必须得大于等于 $\lceil \frac{n}{2} \rceil$，所以还需要统计序列中不小于 $y$ 的数的个数。

首先我们要知道一件事，要使这个序列的总和小于等于 $x$，那么肯定要使得这个序列的总和越小越保险，所以这个序列除了给出的 $k$ 项，其它的 $a_i$ 都只填 $1$ 或 $y$。（也可以填更大的，但没必要）

接着，给出如下代码：
```cpp
if(sum+(n-k)>x)
{
    printf("-1");
    return 0;
}
```
这个代码的意思是如果剩余的序列都填 $1$ 的话（$1$ 是这个序列能填的最小值），综合还是会超过限制，那么输出无解。

接下来又是一份代码：
```cpp
    int mid = n+1>>1;//表示 ceil(n/2.0)，也可以写成 int mid = ceil(n/2.0);
	if(cnt+n-k<mid)
	{
		printf("-1");
		return 0;
	}
	int t = max(0,mid-cnt);
	for(int i = 1;i<=n-k-t;i++)
	{
		sum++;
	}
	for(int i = 1;i<=t;i++)
	{
		sum+=y;
	}
```
我们来解释一下这段代码在干什么,首先上面我们说了，**“因为想要使中位数不小于 $y$，那么序列中不小于 $y$ 的数就必须得大于等于 $\lceil \frac{n}{2} \rceil$”**，那么如果连剩下的数全部填 $y$ 都无满足 $cnt \ge y$ 的话，那么就无解，这就是代码中第一个 if 的意思，然后我们又创建了一个变量 $t$，这个 $t$ 代表我们还要填多少个 $y$ 才能满足 $cnt \ge y$ 的需求。接下来的两个 for 循环就是在模拟填数没什么好说的。

最后一段代码：
```cpp
  if(sum>x)//容易理解吧
	{
		printf("-1");
		return 0;
	}
  //模拟填数过程（这次是要输出）
	for(int i = 1;i<=n-k-t;i++)
	{
		printf("1 ");
	}
	for(int i = 1;i<=t;i++)
	{
		printf("%d ",y);
	}
```
这个就没什么好说的了。

给出全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int a[N];
signed main()
{
	int sum = 0;
	int cnt = 0; 
	int n,k,p,x,y;
	scanf("%d %d %d %d %d",&n,&k,&p,&x,&y);
	for(int i = 1;i<=k;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
		cnt+=a[i]>=y;
	}
	if(sum+(n-k)>x)
	{
		printf("-1");
		return 0;
	}
	int mid = n+1>>1;
	if(cnt+n-k<mid)
	{
		printf("-1");
		return 0;
	}
	int t = max(0,mid-cnt);
	for(int i = 1;i<=n-k-t;i++)
	{
		sum++;
	}
	for(int i = 1;i<=t;i++)
	{
		sum+=y;
	}
	if(sum>x)
	{
		printf("-1");
		return 0;
	}
	for(int i = 1;i<=n-k-t;i++)
	{
		printf("1 ");
	}
	for(int i = 1;i<=t;i++)
	{
		printf("%d ",y);
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
没想明白怎么贪心。

那就模拟。
## 分析。
首先我们考虑填充。既然题目告诉了我们 $y$ 为中位数，那么我们就能找到所有大于等于这个中位数的 $a_i$ 都有可能是中位数。那么我们只需要统计一下个数，然后**从后往前**补充，直到中位数是 $k$ 为止，其余的数用 $1$ 来填充。毕竟根据数据范围来看 $1$ 的取舍不会影响到中位数。

那么这样简单的模拟就可以了。但是无解情况呢？稍微复杂一些了。无解情况有一下三种：
- 我们凑的 $y$ 的数目比能填充的数量 $\left(n-k\right)$ 还要多，此时无解。
- 我们凑的 $y$ 的数目，剩下填充 $1$ 的数目，和原先序列的总和加起来大于 $x$ 此时不满足题意中的，总和不大于 $x$ 这一条件，所以无解。
- 还有一个 $n-k$ 的数目加上原先序列的总和的结果。此时肯定是最小的和，但如果比 $x$ 小那么显然无解。

其实就是综合考虑 $x$ 的大小决定的上边界和下边界，还有总数问题即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,k,p,x,y,a;
int tot,sum;
int mid,last,add;
int main(){
	cin>>n>>k>>p>>x>>y;
	mid=(n+1)/2;//记录中位数的位置。 
	last=n-k;//rem
	for (int i=1;i<=k;i++){
		cin>>a;
		if (a>=y) tot++;
		sum+=a;
	}
	add=mid-tot;
	if(add>last||add*y+(last-add)+sum>x||n-k+sum>x){
		cout<<"-1\n";
	}
	else{
		if(add<0) add=0;
		for (int i=0;i<add;i++){
			cout<<y<<" ";
		}
		for (int i=0;i<last-add;i++){
			cout<<"1 ";
		}
	}
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Wf_yjqd (赞：0)

模拟赛被 hack 了。。

------------

考虑统计比 $y$ 小的数的个数，最终一定有 $\lfloor\frac{n}{2}\rfloor$ 个。

剩下的用 $1$ 补上，仍然剩下的要大于等于 $y$，所以都填 $y$ 就行。

如果小于的个数已经大于 $\lfloor\frac{n}{2}\rfloor$ 或最终的总和大于 $x$，无解。

注意一种情况，当中位数为最小值时，应比中位数小的个数和总的剩下的个数取 $\max$。

------------
不是很长。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,p,x,y,a,sum,ans[1688],cnt,cntt;
int main(){
    scanf("%d%d%d%d%d",&n,&k,&p,&x,&y);
    for(int i=1;i<=k;i++){
        scanf("%d",&a);
        sum+=a;
        if(a<y)
            cntt++;
    }
    if(cntt>int(n/2)){
        puts("Sherry");
        return 0;
    }
    for(int i=cntt+1;i<=min(int(n/2),cntt+n-k);i++){
        ans[++cnt]=1;
        sum++;
    }
    cntt=n-k-cnt;
    for(int i=1;i<=cntt;i++){
        ans[++cnt]=y;
        sum+=y;
    }
    if(sum>x){
        puts("Sherry");
        return 0;
    }
    for(int i=1;i<=cnt;i++)
        printf("%d Sherry\n",ans[i]);
    return 0;
}
```


---

## 作者：ylch (赞：0)

# CF540B School Marks题解

[题目传送门](https://www.luogu.com.cn/problem/CF540B)

当看到题目翻译中“中位数”三个字的时候，我就知道这道题不简单（~~有迹可循~~）。

## 题目补充

### 输入格式

第一行：$n,p,k,x,y$。

第二行：$a$ 数组。

### 数据范围

$1\leq n\leq999$，$n$ 是奇数，$0\leq k$，$1\leq p\leq1000$，$n \leq x\leq n\cdot p$，$1\leq y\leq p$。

### 样例解释

序列 $a_1\dots a_n$，当 $n$ 是奇数时（在这个问题中 $n$ 总是奇数）中位元素是排序序列中的 $(n+1)\div2$ 位置。

在第一个样本中，分数之和等于 $3+5+4+1=17$，不超过 $18$，这意味着 Vova 不会受到同学的干扰。序列 $[1,3,4,4,5]$ 的中点等于 $4$，不小于 $4$，所以他的妈妈让他玩电脑游戏。

请注意，您不必最大化分数总和或中值分数。第一次测试的任何答案：$[42,24,51,15,41,14]$ 都是正确的。

在第二个样本中，Vova 得到了三个 $5$ 分，因此即使他得到了两个 $1$ 分，分数之和也将是 $17$，这超过了要求的 $16$。因此，这个测试的答案是 $-1$。

## 中位数介绍
先给大家科普一下中位数的有关知识：

中位数 (median) 是将一组数据按照从小到大的顺序排列（或者从大到小的顺序也可以）之后处在数列中点位置的数值，是典型的位置平均数，不受极端变量值的影响。中位数主要用于顺序数据，也可用数值型数据，但不能用于分类数据。


如果数列长度是奇数，中位数等于最中间的数；如果长度数列是偶数，中位数等于中间两个数的平均数。对于一组数据来说，中位数是唯一的。比如，有一组数据是：$1,2,5,9,11$，还有一组数据是 $2,5,9,11,12$。他们分别的中位数如下示意图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/e46eubp0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/njqwmq2x.png)

图中箭头所指的位置就是各自的中位数所在的位置。左侧一组数据的中位数所在位置是：从小到大数的第个数，故中位数是 $5$。右侧一组数据中位数所在位置是：从小到大数的第个和第个数之间，故中位数是 $\dfrac{(9+11)}{2}$。

中位数有关公式如下，

中位数：

$$m = a[(len+1)\div2]$$

或

$$m = \dfrac{(a[len\div2]+a[len\div2+1])}{2}$$

因为中位数和长度与数的大小有关，所以要使该数在中间位置，数列中要大于等于中位数数字数量：

$$s = \dfrac{(len+1)}{2}$$



## 解题思路

这题是一道**贪心**的题目。

首先肯定要从中位数入手，设现在大于等于中位数的数有 $num$ 个，同时通过以上的第二个公式：整个数列中应要大于等于中位数（也就是 $y$）的数字数量为 $sum = \dfrac{n+1}{2}$。

接下来我们开始填充数组，中位数肯定要选最小的 $y$，因为加和要小。为了保证中位数就是 $y$，我们可以借助前面求出的 $sum$ 和 $num$，$n-sum$ 为要填充 $1$ 的个数，$\max(0,sum-num)$ 为要填充 $y$ 的个数（中位数数量不可能为负数）。

那么什么情况下会无法完成任务呢？

1. 大于等于中位数的数量无法凑齐（$num+n-k<sum$）。

2. 加和大于 $x$（$ans>x$）。

## 代码

```cpp
#include <bits/stdc++.h>
#define NOTOK return puts("-1"), 0;
using namespace std;

int n,k,p,x,y;
int a[1000];
int num,sum,ans,sum_y;

int main()
{
	cin >> n >> k >> p >> x >> y;
	for (int i=1; i<=k; i++)
	{
		cin >> a[i];
		if (a[i] >= y)	num++;
		ans += a[i];
	}
	sum = (n+1) / 2;
	if (num+n-k < sum)	NOTOK
	int t = max(0, sum-num);
	for (int i=1; i<=n-k-t; i++)	ans += 1;
	for (int i=1; i<=t; i++)	ans += y;
	if (ans > x)	NOTOK
	for (int i=1; i<=n-k-t; i++)	cout << 1 << " ";
	for (int i=1; i<=t; i++)	cout << y << " ";
	cout << endl;
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/113707094)

~~78 个数据点真的香~~

管理员大大辛苦啦~谢谢大家！

我们一起学习，一起进步，一起 $rp++$！

---

