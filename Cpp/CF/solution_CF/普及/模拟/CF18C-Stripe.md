# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
0 0
```

### 输出

```
1
```

# 题解

## 作者：zhangyuhan (赞：6)

在[这篇文章](https://www.luogu.org/blog/zhangyuhanjuruo/solution-at2412)里我曾详细介绍过前缀和，在此我不再赘述。

这里用到的前缀和知识只有一点：**i到j区间的和为s[j]-s[i]**

所以，我们尝试枚举这个序列的“切割点”，再比较这两个区间的和是否一样，一样的话，答案++。


时间复杂度：由于在求出前缀和之后，区间的和只需要$O(1)$就可以算出来，所以总时间复杂度只有$O(n)$

$AC$ $Code$

```cpp
#include<iostream>
using namespace std;

int n,a[100010],s[100010];//s为记录前缀和的数组

int ans;//记录答案

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }//读入+统计前缀和
    for(int i=1;i<=n-1;i++){
        if(s[i]==s[n]-s[i])//比较两个区间的和是否一样
            ans++;//如果一样，答案++
    }
    cout<<ans<<endl;//输出答案
    return 0;//完结撒花！
}

```

---

## 作者：_FILARET_ (赞：3)

## 这道题用到了什么？

如果不知道前缀和怎么用的话，你可能会嵌套四层循环，从而导致TLE，RE等玄学事件。由于这道题是前缀和的基础题目，那就先讲一下前缀和吧~

## 前缀和是什么？

前缀和其实是一种预处理方法，其目的为用O(1)的方法来求出一个数组内的区间和。献上一段前缀和的预处理代码碎片。

数组中每一个元素的sum值都代表那个元素和那个元素之前的元素之和。

具体解释在如下代码中。

```cpp
for(int i=1;i<=N;i++) //循环要从1开始，不然会出现溢出的情况
{
	cin>>a[i]; //操作可以直接在输入中进行
    s[i]=s[i-1]+a[i]; //求出a[1...i]的和，存在s数组中，但它一般要开ll或ull，取决于题目给的范围限制，如果没有负数建议用ull。
}
```

## 本题思路
先求出整个数组的和，然后通过前缀和的s数组来决定从哪里“切”开。

详细解释在代码中，但是千万不要在理解代码前抄这个代码。

```cpp
#include <iostream>
using namespace std;
const int MAXN=100005;
//题目中数组最大限制
int N;
long long a[MAXN]={0};
long long s[MAXN]={0};
//前缀和数组
long long sum=0;
//所有数的和，其实这个也可以用s[N]代替
int ans=0;
//记录答案
int main()
{
	cin>>N;
	for(int i=1;i<=N;i++) //要从1开始循环，不然会数组溢出
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
        //处理前缀和，即将上一个数的前缀和加上目前的数
		sum+=a[i];
        //加和
			//cout<<s[i]<<" ";
        //调试用品，没有什么用
	}
	for(int i=1;i<N;i++)
	{
		if(s[i]*2==sum)
		{
       		//这里使用if(sum/s[i]==2)会炸
        	//判断是否符合条件
			ans++;
            //如果符合条件，就将ans++
		}
	}
	cout<<ans;
    //输出
	return 0;
    //回家领糖吃咯
}
```

## 做完这道题之后该做什么？

- P3131 [USACO16JAN]子共七Subsequences Summing to Sevens
- P2280 [HNOI2003]激光炸弹
- P1083 借教室 （需使用二分不然会TLE）
- P4231 三步必杀 （需使用差分不然也会TLE）
- P3406 海底高铁
- CF1000C Covered Points Count
- CF702C Cellular Network

最后，无耻安利一下我的lj[博客](filaret.ml)

---

## 作者：lxzy_ (赞：1)

写篇题解纪念第一道在$Ugoul$上$\color{green}\text{AC}$的$CodeForces$真(jia)$\color{yellow}\text{黄题}$

这题还是很简单，~~不简单的题我不会写题解的~~，以下是几种~~自己想出的~~解题方法。

---

## $\text{方法1：暴力求和}$

这个方法特别简单，~~也是我第一个想到的办法~~，设定变量$i$，$i$从第$1$个数开始，一直循环到第$n-1$个数，每循环一次，就将$1--i$中所有的$a_i$加起来，再将$i--n$中所有的$a_i$加起来，两两进行比较即可。

代码也很简单：

```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];
int n;//定义长度为100000+50的数组

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }//输入
    
    int ans=0;//统计答案的变量
    for(int i=1;i<=n-1;i++)
    {
        int tot1=0;//统计前段的和的计数器
        int tot2=0;//统计后段的和的计数器

        for(int j=1;j<=i;j++)
        {
            tot1+=a[j];
        }//统计前段的和
        
        for(int j=i+1;j<=n;j++)
        {
            tot2+=a[j];
        }//统计后段的和
        
        if(tot1==tot2)
        {
            ans++;
        }//两段的和相等，则答案加1
        
    }
    
    printf("%d",ans);//完美输出~
    return 0;
}
```


好的，提交！

好的，$\text{Running on test 1}$

嗯，$\text{Running on test 8}$

是不是要A了，窝又成功卡了一道黄题？

$\text{Running on test 18}$

A了，马上A了。。。

$\color{blue}\text{Time limit exceeded on test 19}$

~~太精彩了，鼓掌！OvO~~

窝们来康康这种做法的时间复杂度：

~~显然地：~~


$O(N^2)$

内层的两个循环加起来是$O(N)$，外层的循环是$O(N)$，合起来就是$O(N^2)$

数据范围是：$1 \leq N \leq 10^5$，肯定过不了。~~不过尼可以试试卡常，可以得到更高的分数~~

---

## $\text{方法2：动态求和}$

~~这个方法也特别简单~~，上面这种暴力做法，在循环中计算了非常多重复的东西，致使时间复杂度大大增加，窝们可以去除掉这些无用的计算。

这里所说的重复的东西，就是每便利一个$i$，都要重新计算一次前段数列与后段数列的和。**我们可以试着将求和的操作的复杂度降至$O(1)$。**

## 怎么优化呢？

> ~~留作习题答案略，读者自证不难~~

窝们在一开始定义两个变量$tot1$和$tot2$。$tot1$的初值为$a_1$，$tot2$的初值为$\sum \limits_{i=2}^{n}a_i$。他俩分别记录当前状态下前段数列的和与后段数列的和，然后**从$2$循环到$n-1$**，当每更新$i$的时候，**窝们将$tot1$加上$a_i$，将$tot2$减去$a_i$，这样就可以在$O(1)$的时间内求出当前前段数列与后段数列的和了。**

这样窝们求和的时间复杂度就会降到$O(1)$，而总复杂度则会降到$O(1)$

就是这么简单~

```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];
int n;//定义数组，废话

int tot2;
int tot1;//定义存储当前前段数列和与后段数列和的变量

int ans=0;//定义储存答案的变量

int main()
{
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(i>1)
        {
           tot2+=a[i];//将1以后的数都加进tot2里面，作为第一个后段数列。
        }
    }
    
    if(n==1)
    {
        printf("0");
        return 0;
    }
    tot1+=a[1];//将a[1]加进tot1里面，作为第一个前段数列。
    
    if(tot1==tot2)//得预先判断第一个前段数列与后段数列是否相等，不判断会很精彩
    {
        ans++;
    }
    
    for(int i=2;i<=n-1;i++)//判断过了第一个，那就从第2个开始
    {
        tot1+=a[i];//每次循环tot1加上a[i]，以获得当前前段数列的和
        tot2-=a[i];//每次循环tot2减去a[i],已获得当前后段数列的和
        
        if(tot1==tot2)//如果两者相等
        {
            ans++;//累加
        }
    }
    printf("%d",ans);//完美输出~
    return 0;
}
```

好的，再提交！

$\text{Running on test 13}$

$\text{Running on test 20}$

$\text{Running on test 38}$

$\color{green}\text{Accepted}$

~~终于AC了~~

---

## $\text{方法3：前缀和}$

[前缀和是神马](https://blog.csdn.net/qq_41661809/article/details/86727017)

介个方法许多大佬都讲了，与方法二类似，只是在输入时将求出的每一个数的前缀和放入$s_i$，对于每次循环，前段数列的和就是$s_i$，后段前缀和就是$s_n-s_i$，非常简单的做法，代码如下：

```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];//定义数组，废话
int s[N];//定义前缀和数组
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];//求前缀和
    }

    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(s[i]==s[n]-s[i])//如果当前前段数列的和等于后段数列的和
        {
            ans++;//累加
        }
    }

    printf("%d",ans);//完美~
    return 0;
}
```


~~所以说这一道假黄题成功地被我讲的像一道蓝题似的。~~

## 最后，预祝大家CSP-j取得优异成绩！

---

## 作者：06ray (赞：1)

这道题比较水，思路十分简单，用一个前缀和进行模拟即可AC。

首先定义一个数组为s，例如:s[i]表示从第1个输入的数到第i个输入的数之和。

接着就从1到n-1开始枚举，如果s[i]它等于第i项后面数字之和（第i项后面数字之和就是s[n]-s[i],这其实是前缀和中一个重要的思想，大家可以想想为什么），那么答案就加一。

最后即可输出计算的结果。

如果不用前缀和每次直接暴力求和，复杂度为O(n^2)，而用前缀和复杂度为O(n)。

下面是一段非常简短的代码（一共只有24行）。

```cpp
#include <iostream>//头文件 
using namespace std;//名字空间 
int s[110000];//定义前缀和数组 
int main()
{
	int n;
	cin>>n;//读入n 
	for(int i=1; i<=n; i++)
	{
		int a;
		cin>>a;
		s[i]=s[i-1]+a;//从第1项到第i项之和=第1项到第i-1项之和+第i项元素 
	}
	int ans=0;//初始ans为0 
	for(int i=1; i<=n-1; i++)//注意，i要从1遍历到n-1 
	{
		if(s[i]==s[n]-s[i])//如果第1项到第i项之和=第i项后面数字之和
		{
			ans++;//ans加一 
		}
	}
	cout<<ans;//输出ans 
	return 0;//结束程序 
}
```




---

## 作者：fls233666 (赞：0)

**2020年2月14日更新：修正题解排版**

----------

看到要求出所有的方案，就想到能切割的点不止一个。这时，就可以通过**枚举**切割点，进而得到全部分割的可能方案，然后判断十分合法。最后统计出合法方案的数量即可。

再看题目，可得：当分割成的两个部分的数字之和相等时，此分割方案合法。

如果枚举出分割点后再去逐个求和，最终会使时间复杂度为 $O(n^2)$。对于此题的数据范围 $(1 \le n \le 10^5)$，这样的做法是过不了的。怎么办？

**可以预处理啊！**

我们可以用预处理前缀和来解决问题。我们开一个数组 $s$，$s_{i,0}$ 表示 $[1,i]$ 之间所有数字的和，$s_{i,1}$ 表示 $[i,n]$ 之间所有数字的和。这样，当枚举出切割点 $f$ 时，只需要判断 $s_{f,0}=s_{f+1,1}$ 是否成立即可。

时间复杂度&实现流程梳理：

1. 用 $O(n)$ 把 $s$ 数组全部预处理出来；
2. 枚举切割点。复杂度 $O(n)$；
3. 每次检验枚举出来的切割点方案是否合法，如果合法，统计入变量 $\texttt{ans}$ 中。复杂度 $O(1)$；
4. 输出 $\texttt{ans}$ 的值，总时间复杂度为 $O(n)$。

以下是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int n,ans=0;
	scanf("%d",&n);
    int a[n+2],s[n+2][2];
    memset(s,0,sizeof(s));
  //s数组全部设为0
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    //读入数列
    for(int i=1,j=n;i<=n&&j>=1;i++,j--){
        s[i][0]=s[i-1][0]+a[i];
        s[j][1]=s[j+1][1]+a[j];
    }//对于s数组的预处理（标准的前缀和操作）
  //以上为数据读入与预处理部分
  
  //以下为数据处理和输出部分
    for(int f=1;f<n;f++)  //枚举切割点
        if(s[f][0]==s[f+1][1])
            ans++;   //找到一个合法方案
    printf("%d",ans);   //输出合法方案数
	return 0;
}
```


---

## 作者：loi_hjh (赞：0)

# 枚举+暴力居然是O（n）

真的超简单

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[1000001],p,q,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		q+=a[i];//相当于下面这个循环i=0 
	}
	for(int i=1;i<=n-1;i++){
		p+=a[i];//i及及其左边的和 
		q-=a[i];//右边的和（总和减左边） 
		if(p==q) ans++;
	}
	printf("%d",ans);
    return ~~(0-0);
}
```

---

