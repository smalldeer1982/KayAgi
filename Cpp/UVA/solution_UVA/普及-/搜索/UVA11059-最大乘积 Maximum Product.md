# 最大乘积 Maximum Product

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2000

[PDF](https://uva.onlinejudge.org/external/110/p11059.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/65771c7c6d1492d75695a5505a88282671afede0.png)

## 样例 #1

### 输入

```
3
2 4 -3
5
2 5 -1 2 -1```

### 输出

```
Case #1: The maximum product is 8.

Case #2: The maximum product is 20.```

# 题解

## 作者：meowla (赞：14)

这道题用O(n3)可以做，但是可以一步步简化，简化到O(n)

先说O(n3)做法：枚举两个项i,j，算出i,j之间的乘积和，复杂度O(n3)

首先从O(n3)简化到O(n2)，可以用预处理

S[i]为1到i项乘积和。那么i,j之间就是S[j]/S[i-1]。这样是O(n2)，但是会有严重的bug，也就是如果数列中间出现0，那么S[j]和S[i-1]都是0，这个等会儿再讨论。

再从O(n2)简化到O(n)。我们可以只枚举j，不枚举i。
我们观察公式：S[j]/S[i-1]，如果S[j]>0，那么我们希望S[i-1]=1，这样可以得到最大值，然而S[i-1]肯定可以取到1的，就是从头乘到j。如果S[j]<0，我们希望得到S[i-1]<0，且abs(S[i-1])最小。让k=刚才这个S[i-1]，因此，我们只要记录之前的k就行了。如何更新这个k呢？每次如果S[j]<0，那么k=max(k,S[j])。但是我们k的初值=1。这样在找到负数之前，k不会影响结果。

还有0的情况会出bug。其实如果中途有0，我们可以把它看成把两边分成了两个序列，两个序列的maxn的最大值，就是答案。因此遇到0，我们就初始化k和S。k=1，S重新计数。

在我的代码里面a数组就是S，recordnega就是k

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[19];
int main()
{
	int t=0;
	int n;
	while(cin>>n)
	{
		t++;
		long long temp;
		a[0]=1;
		for(int i=1;i<=n;i++){
			scanf("%lld",&temp);
			a[i]=a[i-1]*temp;
			if(a[i-1]==0)	a[i]=temp;//遇到0，A(就是我说的S)初始化 
			
		}
		long long maxn=0;
		long long recordnega=1;//目前绝对值最小负数 
		for(int i=1;i<=n;i++){
			maxn=max(maxn,a[i]/recordnega);
			maxn=max(maxn,a[i]);
			if(a[i]<0)	recordnega=max(a[i],recordnega);
			if(a[i]<0 && recordnega==1)	recordnega=a[i];
			if(a[i]==0)	recordnega=1;//遇到0，recordnega(就是我说的k)初始化 
		}
		printf("Case #%d: The maximum product is %lld.\n\n",t,maxn);
	}	
	return 0;
}
```




---

## 作者：星释宇 (赞：9)

## **题意**

给一串整数S，你需要找到其连续子序列中乘积最大的那个，输出其乘积。如果找到的答案不是正数，那么输出0，表示无解。

另外注意：每组输入后面都有一行空格，每组输出后面也应该有一行空格。输入以EOF结束。

然后，按照UVa中的数据范围，它不是很大，差不多就是：
1<=n<=18,-10<=s[i]<=10;

本人思路：

因为是最大乘积+连续子序列，所以这就是一个连乘题目
当然首先的一个思路就是暴力如下：

那么在这么小的数据范围内，一个longlong即可，因为数内有负数，所以我们可以先搜索一遍是否拥有负数，若没有，就把整个S数组乘起来，或者负数的个数共有偶数个也可以乘起来

### such as this：```ans*=s[i]```

若有负数且不为偶数个，那么就暴力搜索子序列中乘积最大的值，然后输出正解即可，这里的这个你可以认为是~~前缀和变成前缀乘~~

~~（那啥，这个代码我没写我用的是另一种思路，上面这个比较好理解）~~
 
 另一种思路：
 
 直接暴力（~~本人走暴力流~~）      
 连续子序列的两种要素：起点和终点。
 
 这里和上面的第二部有些类似，需要枚举起点和终点的位置即所有连续子序列。对于其中元素来说，只需要枚举出全部连续子序列然后计算乘积比较就行。
 
 对于其中的乘积不会超过10^18，所以爆搜加一个longlong就可以解决问题
 
 释放代码（~~蠢蠢欲动的代码~~）
 
 ```
#include<iostream>
#include<cstdio>
#include<algorithm> 

using namespace std;

long long s[105];//数组，来存的 

int main(){
	int n;
	int cnt=0;//这个是用来计算第几个解的 
	while(cin>>n){	
		long long ans=0;
		for (int i=0;i<n;++i)
			cin>>s[i];
		for (int i=1;i<=n;++i){
			for (int j=0;j+i<=n;++j){
			//这里的j是子序列的起点，从0开始找 
				long long jishu=1;//这个计数器是用来比较连续子序列乘积与ans原数的大小 
				//相当于计算器里的 M+ （笑） 
				for (int k=j;k<j+i;++k){
				//确定不同的终点 
					jishu*=s[k];//连乘 
					//尝试输出jishu，你就可以知道运行多少次
					//cout<<jishu<<endl;(不用谢) 
				}
				ans=max(ans,jishu);//开始比较，并且换上较大的数到ans中 
			}
		}
		printf("Case #%d: The maximum product is %lld.\n\n",++cnt,ans);//我认为这个输出比较麻烦
		//不要忘记\n 
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：6)

**2020年2月14日更新：修正题解排版格式问题**

---------

首先我们可以发现这题的数据范围很小：

$1 \le N \le 18,-10 \le S_i \le 10$

显然，这是可以用时间复杂度为 $O(n^2)$ 的**枚举**过掉的。

如何枚举？

我们可以枚举子序列的起始位置 $i$ 和终止位置 $j$，在枚举的过程中累乘。累乘时再与当前找到的最大乘积 $\texttt{ans}$ 比较一下,更新 $\texttt{ans}$ 的值，最后输出 $\texttt{ans}$ 即可。

但是我们发现还有一个问题没有解决：如何连续读入数据？

而且肯定还有人会问：$\color{blue} What \  is \ EOF? $

先科普一下什么是 $\texttt{EOF}$：

![对EOF的解释](https://cdn.luogu.com.cn/upload/pic/66155.png)

在读入数据失败时，读入指令会返回一些特殊值。下面介绍一下常见的 cin 和 scanf 在读入失败时返回的值以及连续读入数据的实现：

对于 cin，可以像这样写：

	//读入失败时返回0
    while(cin>>n){
    	//code
    }
    
对于 scanf，可以像这样写：

	//读入失败时返回-1
    while(scanf("%d",&n)!=-1){
    	//code
    }
    
对上述步骤整理归纳，得到如下代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,num[20],ans,test=1;
  //test记录测试数据点数
    while(cin>>n){
        ans=0;   //重置ans值
        for(int i=0;i<n;i++)
            cin>>num[i];   //读入数列
        for(int i=0;i<n;i++)
            for(int s=1,j=i;j<n;j++){
                s*=num[j];  //枚举并更新答案
                ans=max(s,ans);
            }
        printf("Case #%d: The maximum product is %d.\n\n",test,ans);
        test++;   //输出并更新test
    }
	return 0;
}
```

评测结果：

![评测结果1](https://cdn.luogu.com.cn/upload/pic/66172.png)

-----------

？？？？？

我的第一个反应是我的输出格式错了。

打开PDF原题面：

![输入输出样例](https://cdn.luogu.com.cn/upload/pic/66174.png)

【每组数据之后有一行空行要注意啊！】

输出格式没有问题。

于是我又拿出那个数据范围：

$1 \le N \le 18,-10 \le S_i \le 10$

它的答案真的像这个数据范围一样小吗？

于是我决定自己构造一些数据来测试。

自己构造数据时，要构造以下两种数据：

- 数据范围中的极端数据。
- 数据范围中的特殊值数据。（例如0，1，-1）

我造了一个$N=18$，每个$S_i$都是$10$的数据（测试答案的最大值）：

	18
	10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
    
这个程序在洛谷IDE上跑出来的结果：

	Case #1: The maximum product is 1874919424.
    
显然是错的！

正确的答案应该是 $10^{18}$，这个答案爆了 int。

开个 long long int 就可以解决问题了。

下面的代码就是 AC 代码了：

```cpp
#include<iostream>
#include<cstdio>
#define llt long long int
using namespace std;
int main()
{
  /*此代码除了int改成long long int
  cin读入改成scanf读入之外
  与上文代码基本无区别，所以不再注释*/
	llt n,num[20],ans,test=1;
    while(scanf("%lld",&n)!=-1){
        ans=0;
        for(llt i=0;i<n;i++)
            scanf("%lld",&num[i]);
        for(llt i=0;i<n;i++)
            for(llt s=1,j=i;j<n;j++){
                s*=num[j];
                ans=max(s,ans);
            }
        printf("Case #%lld: The maximum product is %lld.\n\n",test,ans);
        test++;
    }
	return 0;
}
```


---

## 作者：Snowlanuck (赞：4)

感觉题解都把问题给说复杂了,其实不需要判断是否含有负数的情况,也不需要多加一个连乘计数器

就是双重循环遍历答案即可,用一个long long类型存最大值(乘法可能会超int类型范围)

i遍历所有项,j从i+1开始遍历所有项,将相乘结果保存起来比较即可,另外要注意可能不乘任何数就是最大数,所以j循环外面要额外判定一次i下标对应的值

参考代码:

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n, cnt = 0;
	while (cin >> n)
	{
		vector<int> Nums(n); long long Res = 0, t = 0;
		for (int i = 0; i < n; i++) { cin >> Nums[i]; }
		for (size_t i = 0; i < Nums.size(); i++) {
			if ((t = Nums[i]) > Res) { Res = t; }
			for (size_t j = i + 1; j < Nums.size(); j++)
				if ((t *= Nums[j]) > Res) { Res = t; }
		}
		printf("Case #%d: The maximum product is %lld.\n\n", ++cnt, Res);
	}
	return 0;
}
```


---

## 作者：efgh123 (赞：3)

## 题目
题目描述

给定一个整数序列S={S1，S2。，Sn}，您应该确定包含S的连续项的最大正积。如果找不到正序列，您应该考虑0作为最大乘积的值。

输入

每个测试用例从1≤N≤18开始，即序列中的元素数。各元素Si是使−10≤Si≤10的整数。下一行将有N个整数，表示每个整数的值序列中的元素。每个测试用例后面都有一个空行。输入在结束时终止文件（EOF）。

输出

对于每个测试用例，必须打印消息：“case#M:the maximum product is P.”，其中M是测试用例的编号，从1开始，P是最大乘积的值。之后每个测试用例都必须打印一个空白行
## 方法步骤
![](https://cdn.luogu.com.cn/upload/image_hosting/usdvkxme.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/9wv4jt2q.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/v4m5apdg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/enfxssej.png)
## 世界上没有免费的午餐，代码自己敲

---

## 作者：PC_DOS (赞：2)

本题只需要直接枚举所有可能的起点和终点，计算其中所有元素的积并求最大即可。由于题目要求如果最大积为负数则输出0，因此应该让存放最大值的变量默认为0。

### 注意，累乘器默认值应为1，最大值输出后要初始化为0

此外还请注意格式，输出完毕要多换一行。

代码:
```
#include <iostream>
#include <vector>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long iMultiply = 1, iMax = 0, nCount, iInput, iCaseID=1; //iMultiply-积；iMax-最大值；nCount-元素个数；iInput-暂存输入的变量；iCaseID-测试情况编号
	vector<int> arrNums; //存放数字的动态数组
	register int i, j, k; //循环计数器
	while (cin >> nCount){ //循环读入个数
		for (i = 1; i <= nCount; ++i){ //读入数据
			cin >> iInput; //读入数字
			arrNums.push_back(iInput); //放入动态数组
		}
		for (i = 0; i < nCount; ++i){ //枚举累乘器起点
			for (j = i; j < nCount; ++j){ //枚举累乘器终点
				iMultiply = 1; //初始化累乘器
				for (k = i; k <= j; ++k){ //求积
					iMultiply *= arrNums[k];
				}
				iMax = max(iMax, iMultiply); //计算最大值
			}
		}
		cout << "Case #" << iCaseID << ": The maximum product is " << iMax << ".\n\n"; //输出
		++iCaseID; //编号加一
		arrNums.clear(); //清空动态数组
		iMax=0; //初始化最大值
	}
	return 0; //结束
}
```

---

## 作者：ZBAA_MKC (赞：1)

因为这题的数据很小，所以可以直接 $O(n^2)$ 暴力枚举。对于枚举的所有答案，只要比当前的最大值 $ans$ 大，就把他更新进去。

注意这题的输出有一个坑点：**每组输出之间要隔一行。**

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[20];
int main()
{
	int n;
	int cnt = 1; //记录当前是第几组数据
    while (cin >> n)
	{
		ll ans = 0; //不开long long见祖宗
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i]; //输入
		}
		for (int i = 1; i <= n; i++) //枚举
		{
			for (int j = i; j <= n; j++)
			{
				ll tmp = 1; //同，也要开long long
				for (int k = i; k <= j; k++)
				{
					tmp *= (ll)a[k];
				}
				ans = max(ans, tmp);
			}
		}
		printf("Case #%d: The maximum product is %lld.\n\n", cnt, ans); //输出（注意格式）
		cnt++; //数据组数++
	} 
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

看到下边一大片的前缀乘，于是我来了一个区间动归。

首先，将数列存入数组 $a$，$a_i$ 表示第 $i$ 个数（从 $1$ 开始编号）。

我们可以设一个数组 $s$，$s_{i,j}$ 表示从第 $i$ 个数乘到第 $j$ 个数的乘积，则可以得到方程：

$$s_{i,i}=a_i$$

当 $i<j$ 时：

$$s_{i,j}=s_{i,j-1}\times a_j$$

接下来就是计算动归数组的元素的值。将 $i$ 从 $1$ 枚举到 $n$，再将 $j$ 从 $i$ 枚举到 $n$，计算 $s_{i,j}$。

然后，取 $s$ 数组里的最大值，若都是负数，输出 $0$。

### 2 代码与记录

```cpp
#include<cstdio>
const int max_n=18;
int n;
long long a[max_n+2];
long long s[max_n+2][max_n+2];//s[i][j]代表从i乘到j的积
long long m;
int ca=0;
long long maxl(long long a,long long b){
    return ((a>b)?a:b);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA11059_1.in","r",stdin);
	freopen("UVA11059_1.out","w",stdout);
	#endif
    while(scanf("%d",&n)!=EOF){
        ++ca;
        //if(ca>1)printf("\n");
        for(int i=1;i<=n;++i){
            scanf("%lld",a+i);
        }
		for(int i=1;i<=n;++i){
			s[i][i]=a[i];
			for(int j=i+1;j<=n;++j){
				s[i][j]=s[i][j-1]*a[j];
			}
		}
        m=0;
        for(int i=1;i<=n;++i){
            for(int j=i;j<=n;++j)
            {
                m=maxl(m,s[i][j]);
            }
        }
        printf("Case #%d: The maximum product is %lld.\n\n",ca,m);
    }
    return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51904488)

By **dengziyue**

---

## 作者：Kacho (赞：1)

题意就不赘述了:简单说吧，就是把一串整数中连续乘积最大的数输出。

这道题的关键在于对于负数的判断，同时需要前缀和的思想进行辅助。

# 前缀和思想以及负数的判断
这道题可以说是一道很基础的前缀和，但是笔者很蒻，所以卡了很久，甚至自己都造不出 hack。

什么叫做前缀和呢？

最简单的前缀和是在输入时，对于 $a$ 数组，用另一个 $b$ 数组，将其前几个 $a$ 数组中的数的值和这个这个数的值加在一起，存入当前这一下标的 $b$ 数组，而 $b$ 数组就是用于存储所累计的值，例如这样子：
```cpp
for(int i = 1; i <= T; i++){
	cin >> a[i];
    	b[i] = a[i] + b[i - 1];
}
```

前缀和的题目大多都要求一个最大值或者最小值，那么这个 $\max$ 操作也是非常简单的，只要对于 $b$ 数组进行 $\max$ 操作就可以了，简单代码如下：
```cpp
for(int i = 1; i <= T; i++){
    cin >> a[i];int temp ,ans;
    temp += a[i];
    ans = max(temp, ans);//此处用到的累加法，大多数情况下效果与数组相同。
}
```

这是最简单的前缀和思想以及 $\max$ 操作，而我们这一题所要用到的是将加法化为乘法的做法，思路大致相同，那代码就不在此处呈现了，在下文讲完负数内容后会给出。

对于这一题我们的累乘器应当从每一位开始从头累乘以及进行 $\max$ 操作，也就是对于 $j$ 来说，要把每个位置作为前缀和的起始位置开始遍历一遍。

为什么呢？我们如果不以每个位置作为起点进行累乘操作以及 $\max$ 操作，例如：
```cpp
for(int i = 1; i <= T; i++){
    cin >> a[i];
    ans[i] = ans[i - 1] * a[i];
}//累乘器

for(int i = 1; i <= T; i++) as = max(as, ans[i]);//max操作
```

那么我们很容易可以得出一组 hack 数据。

例如下面这组：

```cpp
3
-1 4 2
```

如果累乘器不从每一位进行遍历，那么输出的结果就会是：
```cpp
Case #1: The maximum product is 0.
```

然而，正解是：
```cpp
Case #1: The maximum product is 8.
```

这里的原因就是：不从每一位开始，如果遇上了第一位是负数且只有一个负数的数据，那么此时累乘器里面的值，就会全为负数，这样显然与可求得的连续区间的最大乘积的最终答案不符合，所以是一个错误的算法。

现在注意到了这个问题，那么考虑问题就可以变得全面了。

我们需要的累乘器不能够被负数所拖累，那很简单啊！把数组从 $i$ 位置开始从头累乘，并且在累乘的过程中加入 $\max$ 操作，这样累乘器就不会再被仅第一个数为负数的数据所 hack 了。因为此时，我们会在对从第 $1$ 到第 $T$ 位的数据进行累乘，也会继续从第 $2$ 位到第 $T$ 位开始累乘，同时用 $\max$ 操作进行更新 $ans$ 的值，一直进行到第 $T$ 位的位置结束累乘操作和 $\max$ 操作。那么放上前缀和部分的代码:

```cpp
for(int i = 1; i <= T; i++)
   for(int as = 1, j = i; j <= T; j++){
      as *= a[j];
      ans = max(as, ans);
   }
```


所以，只要知道了这个核心代码，这道题就被您爆切了。

当然，要开longlong。

# 总结

这道题还是挺水的，可以作为前缀和的入门题目。

只需要注意累乘器所需要累乘开始的位置以及所做的次数就能完成此题了。

放上两份代码，大家要是没有读懂上面的内容可以针对第一份错解以及对照第二份正解一起食用，效果更佳。

```cpp
#include<bits/stdc++.h>
#define int long long

const int N = 1000005;

using namespace std;

int cnt,ans[N] = {1};
int T,a[N];
int as;

signed main (){

    while(scanf("%lld ", &T) != EOF){
        for(int i = 1; i <= T; i++){
            cin >> a[i];
            ans[i] = ans[i - 1] * a[i];
        }

        for(int i = 1; i <= T; i++) as = max(as, ans[i]);

        printf("Case #%lld: The maximum product is %lld.\n\n", ++cnt, as);

    }

    system("pause");

    return 0;
}
```
以及下面这份：

```cpp
#include<bits/stdc++.h>
#define int long long

const int N = 1000005;

using namespace std;

int cnt,ans;
int T,a[N];

signed main (){

    while(scanf("%lld ", &T) != EOF){
        ans = 0;
        for(int i = 1; i <= T; i++) cin >> a[i];
         
        for(int i = 1; i <= T; i++)
            for(int as = 1, j = i; j <= T; j++){
                as *= a[j];
                ans = max(as, ans);
            }

        printf("Case #%lld: The maximum product is %lld.\n\n",++cnt, ans);

    }

    system("pause");

    return 0;

}
```

祝您AC大吉。
















---

## 作者：Ezis (赞：1)

### 题意：
确定一个 $l,r$ ,使 $\prod_{i=l}^r s_i$ 最大。

**思路**

我们可以枚举每一个左节点和右节点，求这段区间的和，最后取 $\max$ 即可。

注意：

$ans$ 初始化为 $1$。

输入到 $EOF$ 为止。

**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot;
long long ans,a[20];
int main(){
	while(scanf("%d",&n)!=EOF){
		ans=0;	//初始化
		tot++;
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)	//左节点
			for(int j=i;j<=n;j++){	//右节点
				long long sum=1;
				for(int k=i;k<=j;k++)
					sum*=a[k];	//求积
				ans=max(ans,sum);	//ans与sum取max
			}
		printf("Case #%d: The maximum product is %lld.\n\n",tot,ans);	//输出
	}
	return 0;
}
```


---

