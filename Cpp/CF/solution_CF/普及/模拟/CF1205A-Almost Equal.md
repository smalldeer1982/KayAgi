# Almost Equal

## 题目描述

You are given integer $ n $ . You have to arrange numbers from $ 1 $ to $ 2n $ , using each of them exactly once, on the circle, so that the following condition would be satisfied:

For every $ n $ consecutive numbers on the circle write their sum on the blackboard. Then any two of written on the blackboard $ 2n $ numbers differ not more than by $ 1 $ .

For example, choose $ n = 3 $ . On the left you can see an example of a valid arrangement: $ 1 + 4 + 5 = 10 $ , $ 4 + 5 + 2 = 11 $ , $ 5 + 2 + 3 = 10 $ , $ 2 + 3 + 6 = 11 $ , $ 3 + 6 + 1 = 10 $ , $ 6 + 1 + 4 = 11 $ , any two numbers differ by at most $ 1 $ . On the right you can see an invalid arrangement: for example, $ 5 + 1 + 6 = 12 $ , and $ 3 + 2 + 4 = 9 $ , $ 9 $ and $ 12 $ differ more than by $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1205A/9cba5ca83f08157cd471ad2c4144ebafdf1f05ac.png)

## 说明/提示

Example from the statement is shown for the first example.

It can be proved that there is no solution in the second example.

## 样例 #1

### 输入

```
3
```

### 输出

```
YES
1 4 5 2 3 6 ```

## 样例 #2

### 输入

```
4
```

### 输出

```
NO```

# 题解

## 作者：引领天下 (赞：7)

其实这个题就是个结论题=-=

~~然而我比赛的时候还是想了0.5h，还RE了一次~~

我们观察到在环上，**相对的两个数差为1**。

这意味着我们的每次递推必然产生两个数，于是很~~不~~自然的想到%2。

接下来就是大胆猜想不用证明的部分了：

 - 观察样例，发现当$n=1$时，则填出的数列为$1,2$，所以可以猜想枚举的过程中$i$&$1$的话则$a_{n+i}=a_i+1$
 - 既然$i$&$1$时为$a_{n+i}=a_i+1$，那么为了平衡，另一种情况我们就另$a_i=a_{n+i}+1$
 - 观察到样例给出的$n=4$是无解的，手动画图发现$n=2$也是无解的，于是大胆猜想$n$为偶数时都无解。
 
事实上以上的3条猜想都是正确的。

证明：我们既然要相隔$n$的两个数相差$1$，但是相邻数之和尽可能接近，易证小数和大数间隔放是一种可行策略，而且当$n$为偶数时不满足。

~~好像我的证明过程一样没啥卵用~~

于是给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],cnt;
int main(){
    scanf("%d",&n);
    if(!(n&1))return !printf("NO");
    puts("YES");
    for (int i=1;i<=n;i++)if(i&1)a[i]=++cnt,a[i+n]=++cnt;
    else a[i+n]=++cnt,a[i]=++cnt;
    for (int i=1;i<=n*2;i++)printf("%d ",a[i]);
}
```

---

## 作者：xuezhe (赞：4)

首先，要看透本质，由于它每次都只在环中选取长度为 $n$ 的子串，只要按照顺序，这题就有点像一道题：滑动窗口。

两题之间区别不小，但可以提取中一个整体思路：队列。

每滑动一次，队首出队，队尾进队。

此时我们便可以推出让相邻两个窗口的和相差不超过 1 的方法：让入队的元素和出队的元素相差不超过 $1$。

设出队的元素在第 $i$ 位，则入队的元素在第 $(i+n)$ 位。所以我们需要让第 $i$ 位和第 $(i+n)$ 位相差不超过 $1$。

由于两两之间相差不能超过 $1$，所以我们不能在两次滑动时连续加 $1$ 或连续减 $1$。当 $n$ 为偶数时无法满足这点，便无解。

设环拆开后形成的序列为 $A$，则可以得到：当 $i \mod 2 = 1$ 时，$A_i = 2i-1,A_{i+1} = 2i$；否则 $A_i = 2i,A_{i+1} = 2i-1$。

问题得解。

C++代码：
```cpp
#include <cstdio>
using namespace std;
void readInt(int &x){
	char c;
	while((c=getchar())<'0' || c>'9');
	x=(c^48);
	while('0'<=(c=getchar()) && c<='9'){
		x=x*10+(c^48);
	}
	return;
}
int a[200001];
int main(){
	int n;
	readInt(n);
	if(n&1){
		puts("YES");
		for(int i=1;i<=n;++i){
			if(i&1){
				a[i]=2*i-1;
				a[i+n]=2*i;
			}else{
				a[i]=2*i;
				a[i+n]=2*i-1;
			}
		}
		for(int i=1;i<=2*n;++i){
			printf("%d ",a[i]);
		}
		puts("");
	}else{
		puts("NO");
	}
	return 0;
}
```

---

## 作者：Awdrgysxc (赞：4)

## 【Analsis】
因为任意两个和相差最多为$1$,可以构造答案，比如

$n = 3$  -> $1, 4, 5, 2, 3, 6 $ 

$n$为奇数时 [小]，[大]，[小]，[大],$......$[小]，[大]  这样是可以的

$n$为偶数时 [小]，[大]，[小]，[大]，[小]$......$[大]，[小]可以发现这样不行，然后就做完了

## 【Code】
```cpp
#include <cstdio>
#include <set>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
 
namespace IO
{
    inline char gc()
    {
        static char s[1<<20|1]={0},*p1=s,*p2=s;
        return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
    }
//	inline char gc() { return getchar(); }
	inline long long read()
	{
		long long ret=0;bool flag=0;char c=gc();
		while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=gc();
		while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=gc();
		return flag?-ret:ret;
 	}
 	char OutputAns[1<<20|1],*OutputCur = OutputAns;
 	inline void output()
 	{
 		OutputCur -= fwrite(OutputAns,1,OutputCur - OutputAns,stdout);
	}
	inline void print(long long ans)
	{
		char s[20]={0};
		if (OutputCur - OutputAns + sprintf(s,"%I64d",ans) >> 20) output();
		OutputCur += sprintf(OutputCur,"%I64d",ans);
	}
	inline void printc(char c)
	{
		if (OutputCur - OutputAns + 1 >> 20) output();
		*(OutputCur++) = c;
	}
}
 
using IO::read;
using IO::print;
using IO::printc;
using IO::output;
 
const int M = 1e5 + 11;
 
int A[M<<1];
 
int n;
 
inline void Go1()
{
	puts("YES");
	printf("1 2\n");
	exit(0);
}
 
int main(void)
{
	n = read();
	if (n == 1) Go1(); 
	if (!(n & 1)) puts("NO");
	else
	{
		puts("YES");
		bool opt = 0;
		for (int i = 1;i <= n; ++i)
		{
			opt ^= 1;
			if (opt) A[i] = (i<<1) - 1, A[i + n] = i<<1;
			else A[i] = i<<1, A[i + n] = (i<<1) - 1; 
		}
		for (int i = 1;i <= (n<<1); ++i)
			print(A[i]), printc(' ');
		printc('\n'); output();
	} return 0;
}
```

---

## 作者：VinstaG173 (赞：2)

数学题。

我们要相隔$N$的两个数相差$1$，但是相邻数之和尽可能接近，很容易得到一种策略：小数和大数间隔放，如题目中样例顺时针方向的放置方法。但是我们会发现当$N$为偶数时条件无法满足，所以当$N$为奇数时模拟就可以了。

Code:

```cpp
#include<cstdio>
int N,mn,mx;
int a[200003];
int main()
{
	scanf(" %d",&N);
	if(N&1)//判断奇偶
	{
		printf("YES\n");mn=1,mx=N<<1;
		for(int i=0;i<N;++i)//放置
		{
			if(i&1)a[i]=mx,a[i+N]=mx-1,mx-=2;
			else a[i]=mn,a[i+N]=mn+1,mn+=2;
			printf("%d ",a[i]);
		}
		for(int i=0;i<N;++i)printf("%d ",a[i+N]);
	}
	else printf("NO\n");
	return 0;
}
```

---

## 作者：ZigZagKmp (赞：0)

本文同步于[CF1206总题解](https://www.luogu.org/blog/zhouzikai/cf1206round-580-div2-post)，欢迎各路神仙来踩。

## C Almost Equal
### 题意
将$1-2n$这$2n$个数按圆环排列，记每$n$个连续的数相加的和为$S_1,S_2,...,S_n$，要使得$\forall i,j\in[1,n],|S_i-S_j|\le 1$，求出一种合法的排列。
### 解法
1. 算法1

我们先考虑$|S_i-S_{i+1}|\le 1$

$S_i=a_i+a_{i+1}+...+a_{i+n-1}$

$S_{i+1}=\ \ \ \ \ a_{i+1}+a_{i+2}+...+a_{i+n}$

$|S_i-S_{i+1}|=|a_i-a_{i+n}|\le 1$

因为$1-2n$这些数互不相同，并且每$n$个数的和满足上述要求，所以在合法排列中（设为$a$），一定满足$|a_i-a_{i+n}|= 1$

我们再考虑$|S_i-S_{i+2}\le 1|$

$S_i=a_i+a_{i+1}+a_{i+2}+...+a_{i+n-1}$

$S_{i+2}=\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ a_{i+2}+a_{i+3}+...+a_{i+n+1}$

$|S_i-S_{i+2}|=|(a_i-a_{i+n})+(a_{i+1}-a_{i+n+1})|\le 1$

我们发现如果$(a_i-a_{i+n})$和$(a_{i+1}-a_{i+n+1})$都是1或者都是-1，是不满足上述不等式的。

因此$(a_i-a_{i+n})$应该是交替为1,-1。

如果$n$为偶数，（手玩几下）可以发现是无法做到1,-1交替出现，即无解。

如果$n$为奇数，那么按照这个思路去构造即可。

我们可以把$1-2n$个数字分成如下$n$对：$(1,2),(3,4)...(2n-1,2n)$，把最后的结果分成两部分(记为$A,B$)，交替地在$A$中插入每一对数字的第一个数字和第二个数字，同时在$B$中插入同一数字对的另一个数，最后直接将$B$接在$A$的后面。

上面写的比较抽象，我们举一个实例：$n=5$：

$A:1,4,5,8,9$

$B:2,3,6,7,10$

答案为$1,4,5,8,9,2,3,6,7,10$

2. 算法2（应该是实现方法2）

由观察得，上述填数过程有规律可循：还是分一半(我们还是记为$A,B$)，先在$A$中填一个1，然后到$B$中填$2,3$，然后再到$A$中填$4,5$……最后把$2n$填到$B$的最后。
### 代码实现
1. 算法1

同样，这里省略头文件，快速读入，输出，相信能看到这道题目的人应该都会这些东西。
```cpp
int A[100005],B[100005],ta,tb,n;
int main(){
	read(n);
    if(n&1){
    	puts("YES");
        for(int i=1;i<=n;i++){
        	if(i&1)A[++ta]=(i*2-1),B[++tb]=(i*2);
            else   A[++ta]=(i*2),B[++tb]=(i*2-1);
        }
        ...//输出
    }
    else{puts("NO");}
    return 0;
}

```

2. 算法2

```cpp
int A[100005],B[100005],ta,tb,n;
int main(){
	read(n);
    if(n&1){
    	puts("YES");
        A[++ta]=1;
        for(int i=1;i<n;i++){
        	if(i&1)B[++tb]=(i*2),B[++tb]=(i*2+1);
            else   A[++ta]=(i*2),A[++ta]=(i*2+1);
        }
        B[++tb]=2*n;
        ...//输出
    }
    else{puts("NO");}
    return 0;
}

```

---

## 作者：周子衡 (赞：0)

思路：数学+构造

不妨设环上的数依次为$a_1,a_2,...,a_{2n}$。

首先证明：$|a_{n+1}-a_1|=1$。

这个证明非常简单。根据题目要求，有$|\sum_{i=1}^na_i-\sum_{i=2}^{n+1}a_i|\leq 1 $,即$|a_{n+1}-a_1|\leq 1$。而$a_1\neq a_{n+1}$，故$|a_{n+1}-a_1|=1$。证毕。

同上，可以证明：$\forall i\in N,1\leq i\leq n,|a_{n+i}-a_i|=1$。

不失一般性，假设$a_{n+1}>a_1$。则$a_{n+1}-a_1=1$。

接下来我们证明：$a_{n+2}-a_2=-1$。

可以发现，刚刚的证明只用到了相邻两和之间的关系。我们拓展一下。同样由题得$|\sum_{i=1}^na_i-\sum_{i=3}^{n+2}a_i|\leq 1$。即$|a_1+a_2-a_{n+1}-a_{n+2}|\leq 1$。将$a_{n+1}-a_1=1$代入得$|a_2-a_{n+2}-1|\leq 1$。若$a_2-a_{n+2}=-1$，代入矛盾！故$a_2-a_{n+2}=1$，即$a_{n+2}-a_2=-1$。证毕。

同上，可以证明：$\forall i\in N,1\leq i\leq n,a_{n+i}-a_i=-(-1)^i$。

我们观察环的“接缝”处是否正确。可以发现这和$n$的奇偶性相关。若$n$为偶数，则$a_{2n}-a_n=-1,a_1-a_{n+1}=-1$，则$|\sum_{i=n}^{2n-1}a_i-(\sum_{i=n+2}^{2n}a_i+a_1)|=|a_n+a_{n+1}-a_1-a_{2n}|=|1+1|=2$。矛盾！此时输出$NO$。

若$n$为奇数，可以按上面方法检验发现可行。接着按上面的要求构造一组解即可。我是这样构造的：令$p$为填数的位置指针，初始时$p=1$。枚举$i=1...2n$，将$i$填在第$p$个位置上，同时判断下一个位置，如果$i$为奇数，就把$p$变为当前位置的对面（$+n$或$-n$），否则顺移一位（$+!$）。

代码：
```cpp
#include<cstdio>

using namespace std;

int a[200010];

int main()
{
	int n=0;scanf("%d",&n);
	if(!(n&1)){puts("NO");}
	else
	{
		puts("YES");
		int p=1;
		for(int i=1;i<=2*n;i++)
		{
			a[p]=i;
			if(i&1){if(p<=n)p+=n;else p-=n;}
			else{p++;}
		}
		for(int i=1;i<=2*n;i++)printf("%d ",a[i]);
	}
	return 0;
} 
```

---

## 作者：LCuter (赞：0)

我们可以想到一种构造方法，先使当前区间的和为$X$，则下一个区间之和为$X+1$，再使下一个区间之和为$X$，如此反复。

考虑区间$[A,B]$与区间$[A+1,B+1]$，他们的和之差只与$A$和$B+1$有关。因为$A$不等于$B+1$，所以这两个区间和不可能相同，那么说明构造方法唯一，便是上面的方法

所以我们想到这样一种方式，假设我们填到第$i$位

当$i$是奇数时，$a_i=2i-1,a_{i+n}=2i$

当$i$是偶数时，$a_i=2i,a_{i+n}=2i-1$

由于题目中要求的是一个环，我们发现当$n$为偶数时这种方法不成立，所以当$n$为偶数时无解(硬要解释的话，当我们检查第$n+1$位时，我们知道$a_1=1,a_{n+1}=2$，你会发现顺时针比的时候，他是相当于$n+1$得是偶数位，那么$n$就得是奇数了)

---

## 作者：若如初见 (赞：0)

新鲜出炉的CF比赛题~  

本蒟蒻虽然A了，但是没有想出结论的证明，等其他大佬补充吧。

### 题目大意：  

给出正整数$n$，求出一个$1$~$2n$的全排列并首位相连，满足在该全排列中任意选出两段连续$n$个数，这两段数的和的差的绝对值小于$1$.  

### 解题思路：  

大概是我太弱了，没有想到正解。于是试着先打个暴力找规律：  

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,a[100005];
inline int Abs(int x){
	return x<0?-x:x;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
		a[i]=i;
	do{
		bool flag=0;
		int b1=-1,b2=-1;
		for(int i=1;i<=2*n;i++){
			int sum=0;
			a[0]=a[2*n];
			for(int j=i;j<=i+n-1;j++)
				sum+=a[j%(2*n)];
			if(b1==-1) b1=sum;
			else if(b2==-1){
				if(Abs(sum-b1)>1){
					flag=1;
					break;
				}
				else b2=sum;
			} else if(sum!=b1&&sum!=b2){
				flag=1;
				break;
			}
		}
		if(!flag){
			for(int i=1;i<=2*n;i++)
				printf("%d ",a[i]);
			break;
		}
	}while(next_permutation(a+1,a+1+2*n));
	
	return 0;
}
```
暴力程序的时间复杂度是$O(n!\cdot n^2)$的（常数还巨大），当$n=7$的时候就有点跑不动了。不过借助着$n\in [1,6]$的结果（如下），还是能发现一些规律：

```
n=1
YES
1 2

n=2
NO

n=3
YES
1 4 5 2 3 6

n=4
NO

n=5
YES
1 4 5 8 9 2 3 6 7 10

n=6
NO
```

 - 当$n$为偶数时，无解；

 - 当$n$为奇数时，规律也很好发现：试试依次寻找1,2,3..的位置，不难得出，整数$i$出现的位置是：  

 - $\frac{i+1}{2}$，当$i\%4==1$；
 
 - $\frac{i+2n}{2}$，当$i\%4==2$；
 
 - $\frac{i+1+2n}{2}$，当$i\%4==3$；
 
 - $\frac{i}{2}$，当$i\%4==0$.
 

结合以上规律，我们就能得到本题的程序了。时间复杂度为$O(n)$，可以通过本题。  

代码如下（思路十分简单，就不加注释了）：

```cpp
#include <cstdio>
using namespace std;
int n,a[400005];
int main(){
	scanf("%d",&n);
	if(n%2==0){
		printf("NO\n");
		return 0;
	} else printf("YES\n");
	for(int i=1;i<=2*n;i++)
		if(i%4==1) a[(i+1)/2]=i;
		else if(i%4==2) a[(i+2*n)/2]=i;
		else if(i%4==3) a[(i+1+2*n)/2]=i;
		else a[i/2]=i;
	for(int i=1;i<=2*n;i++)
		printf("%d ",a[i]);
	return 0;
}
```



---

## 作者：览遍千秋 (赞：0)


本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF580DIV2)，欢迎来踩

---

通过大眼观察法，可以发现：

 - 当$n$为偶数时无解
 
 - 当$n$为奇数时遵循以下规则：
 
先在位置$1$填写$1$

之后到位置$n+1,n+2$填写$2,3$

之后到位置$2,3$填写$4,5$

……

总结出：

$1$一定填写在$1$位置

接下来每次换到对面写两个数。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;



template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=-1;ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

int n;
int ans[200005];
int p,cnt;

int main(){
	read(n);
	if(n%2==0){
		puts("NO");return 0;
	}
	ans[1]=1;p=n+1;
	for(register int i=2;i<=2*n;i++){
		ans[p]=i;i++;p++;ans[p]=i;
		if(p>n) p-=n;
		else p+=n;
	}
	puts("YES");
	for(register int i=1;i<2*n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[2*n]);
	return 0;
}
```

---

## 作者：Akaina (赞：0)

构造题,这道题一开始我毫无思路，再后来观察发现了一个性质，第i个数和第i+n个数的差一定等于1(不可能有两个数相等故不可能为0）

然后我用爆搜打了个表找规律

1: YES 1 2

2: NO

3: YES 1 4 5 2 3 6

4: NO

5: YES 1 4 5 8 9 2 3 6 7 10

6: NO

7: YES 1 4 5 8 9 12 13 2 3 6 7 10 11 14

然后规律就很明显了：

偶数输出NO

一个简单的证明是：

2n个数字的和为n*(2n+1)，如果n为偶数，那么和为偶数，能够被分成两个相等的和x

又因为第i个数和第i+1个数的差一定为1，则必定存在x+1和x-1两种和，不符合题意

奇数输出YES，然后你可以试着用数数的方法从1数到2*n找找规律你会发现前n个数和后n个数是大小交替排列


所以就很容易构造出答案了,时间复杂度：O（n）
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
int main()
{
    scanf("%d",&n);
    if(n%2==0)printf("NO\n");
    else
    {
        printf("YES\n");
        for(int i=1;i<=n;i++)//输出前n个数
        {
            if(i%2==1)//i是奇数
            {
                printf("%d ",i*2-1);
            }
            if(i%2==0)//i是偶数
            {
                printf("%d ",i*2);
            }
         }
         for(int i=1;i<=n;i++)//输出第n+1到第2*n个数
         {
             if(i%2==1)
             {
                 printf("%d ",i*2);
             }
             if(i%2==0)
             {
                 printf("%d ",i*2-1);
             }
         }
    }
    return 0;
}
```

---

