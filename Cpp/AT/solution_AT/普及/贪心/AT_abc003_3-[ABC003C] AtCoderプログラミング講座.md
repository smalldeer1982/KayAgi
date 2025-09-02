# [ABC003C] AtCoderプログラミング講座

## 题目描述

【题意】

初始时 $C=0$ ，给出一个含 $n$ 个数的序列 $\{R\}$，取其中任意 $k$ 个数的排列 $R_1,R_2,\cdots R_k$，并依次运算 $C=(C+R_i)/2$ .你的任务是使得最终的 $C$ 尽可能大。

# 题解

## 作者：欢黎明陌 (赞：19)

一道贪心题，大致思路是先读入，然后从小到大排序（普遍思路），再按要求遍历并计算以求得 $C$ 的最大值，最后保留六位输出。

------------
下面是单调性的证明：

因为 有$C=(C+R_i)/2$；

且 $C$ 和 $R_i$ 都为正数；

所以 $C$ 会随着 $R_i$ 的增大而增大；

故 我们应当用 $R_i$ 最大的序列来求得 $C_{max}$。

------------
先上排序，对于这道题，冒泡排序未必是最好的，但它确确实实可以 $AC$ 这道题，并且在时间和空间上很有富余，若遇到 $TLE$ 可以再考虑用二分之类的。

```cpp
void bubble_sort(){
	for(int i = n; i >= 2;i --)
		for(int j = 1; j < i;j ++)
			if(R[j] > R[j + 1])
				swap(R[j], R[j + 1]);
	return ;
}
```

------------
然后就是怎样只选最大的 $R_i$ 中的元素了，我们只需要在排序结束之后，从后往前数到足够 $k$ 个元素，然后用它们对 $C$ 进行运算。

```cpp
for(int i = n - k + 1;i <= n;i ++) 
	c = ( c + R[i] ) / 2;
```

------------

别忘了给 $C$ 初始化哦~还有就是保留六位再输出。

下面是标程:

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int k , n , R[1001010];
double c;//有保留要求，理所应当用double 

void bubble_sort(){//冒泡排序 
	for(int i = n; i >= 2;i --)
		for(int j = 1; j < i;j ++)
			if(R[j] > R[j + 1])
				swap(R[j], R[j + 1]);
	return ;
}

int main()
{
	cin >> n >> k;
	for(int i = 1;i <= n;i ++) cin >> R[i];
	
	bubble_sort();
	for(int i = n - k + 1;i <= n;i ++) c = ( c + R[i] ) / 2;
	
	cout << fixed << setprecision(6) << c ;//等同于printf("%0.6f",c);
	return 0;
}
```

管理大大辛苦了。

打字不易，看到点个赞呗~



---

## 作者：zjyqwq (赞：8)

### AT795题解
本蒟蒻又来发题解了！Pas题解来一发。


------------
#### 题目解析
 本道题的翻译已经将整道题的真正意思翻了出来。

他让我们随便选择 $k$ 个数，使 $C$ 最大。

然而既然是最大，那么选数就要选最大。

既然选数要选最大，那么就要排序。

再此，便选用快排。


------------
#### 注意事项
- AT的输出要换行！！！
- 要保留六位小数。


------------
#### 问题 and 重点
但是还有一个重点。
我们拿样例 $1$ 来看。
```
2 2
1000 1500
```
如果我们先与 $1500$ 进行运算，再与 $1000$ 进行运算，我们会发现，算出来是 $875$ ，而样例输出却是
```
1000.000000
```
但如果我们先与 $1000$ 进行运算的话，我们会发现，他对了。

为什么呢？

因为每次原来的 $c$ 都会除以 $2$ ,那如果以前加的是大的数，就会变小，因为他会多除几个 $2$ 。

#### 结论
我们要先与小的运算，再与大的运算，排序后恰好可以处理了。


------------
#### 代码
```pascal
var
n,k,i:longint;
c:double;
a:Array[0..1000000]of longint;//定义
procedure sort(l,r:longint);//快排
var
i,j,mid,t:longint;
 begin
  i:=l;j:=r;mid:=a[(i+j)div 2];
  while i<=j do
   begin 
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
    begin 
     t:=a[i];
     a[i]:=a[j];
     a[j]:=t;
     inc(i);
     dec(j); 
    end;
   end;
  if j>l then sort(l,j);
  if i<r then sort(i,r);
 end;
 begin
  readln(n,k);
  for i:=1 to n do read(a[i]);
  sort(1,n);
  for i:=n-k+1 to n do//重点，要从小到大处理
    c:=(c+a[i])/2;
  writeln(c:0:6);//输出
 end.
```
结束了！！！

---

## 作者：ZepX_D (赞：4)

# 题意：
输入 $n$ 个数，取其中任意 $k$ 个数依次运算，使 $C$ 尽可能大。
# 分析
首先我们需要进行**排序**,排序之后**从最大数向后取 $k$ 个数**，这时问题来了，如果我们先选取最大的数进行运算，那么它的受益会大大折扣，因为它会**除以 $2^k$ **,就会导致它的收益越来越小，例： $((2+2)/2+4)/2>((2+4)/2+2)/2$ 所以我们应从**第 $k$ 大的数**开始选取进行运算。
# code
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>// sort 头文件

using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))// isdigit(x) 判断是否是数字字符，需调用 cctype 库
	{
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
} 
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
    int n,k;
    double c=0;//这里要用 double
    n=read();k=read();
    int a[n+1];//节省空间
    for (int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1,cmp);
    for (int i=k;i>=1;i--) c=(c+a[i])/2;//从第 k 大的数选取到最大的数
    printf("%.6lf\n",c);//保留小数点后六位
    return 0;//完美收官
}
```

# 总结
这个黄题并不难， sort 完全能过，我们只需要注意从第 $k$ 大的数开始选取进行运算，使最大值的收益最大化，这样才能使 $C$ 的值最大，然后就可以~~吊打~~  AC 这道题了
另：三次提交均为最优解，这里附上链接: [AC](https://www.luogu.com.cn/record/53601758)

三次记录 [AC](https://www.luogu.com.cn/record/list?pid=AT795&user=&page=1&orderBy=1&status=)



---

## 作者：JoseTony (赞：3)

#  思路与分析
我最近刚刚开始自学贪心算法，可以说这道题是一个入门贪心算法比较好的题目，贪心算法就是要找到局部的最优解来完成全局的最优解。根据题意我们得知，要使 $C$ 最大，我们就必须让   $R_i$ 尽可能的大，这样才可以使 $C+R_i$ 最大。根据小学的数学知识我们就可以得知，如果 $C+R_i$ 最大，那么它除以 $2$ 的商也是最大的。这就是我们在这道题中要达到的局部最优解。为了达成这个目标，我们又应该怎么做呢？很简单，用 `sort` 函数把输入的数组进行排序，再从 $n-k+1$ 开始遍历这个数组就可以了。这道题还有一个坑，**那就是要保留六位小数**。因此我们的变量要用`double`类型，最后输出的时候也不能忘记。代码如下。
# 代码
```cpp
#include<iostream>
#include<cstdio>//printf函数要用的头文件
#include<algorithm>//sort函数要用的头文件
using namespace std;
int a[1000001];
int main(){
    int n,k;
    double C;//C最后要保留六位小数，因此要用double
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序
	for(int i=n-k+1;i<=n;i++){//遍历
	    
	
		C=(C+a[i])/2;//计算C
	}
	printf("%.6lf",C);//保留六位小数
	return 0;//程序结束
}
```


---

## 作者：DreamBuilder (赞：1)

一道很水的贪心。

## 题意分析
~~没啥好分析的~~

就是题目大意。
## 思路
先把它从小到大排个序，在截取后 $k$ 个，从前往后进行运算。其实其中包含了两次贪心：第一次取此数列最大的 $k$ 个数；第二次是让这 $k$ 个数中小的先进行运算，这样可以让 $C$ 更大，证明：较大的数为 $x$, 较小的数为 $y$ ，若大的先，则结果为 $\frac{1}{4} x + \frac{1}{2} y$ ，若小的先，则结果为 $\frac{1}{4} y + \frac{1}{2} x$ ，又因为 $x ≥ y$ ， 所以较小的先更划算。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int a[maxn], n, k;
double c;
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);//从小到大排
	for(int i = n - k + 1; i <= n; ++i)//去后k个较大的
		c = (c + a[i]) / 2.0;//一定要除以2.0，不然就是整数了
	printf("%.6f", c);//保留小数点后六位
	return 0;
}
```
不喜勿喷。~~请看懂了再抄~~

---

## 作者：lxgw (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT795)
## 题意
输入两个数 n,k ，再给出有 n 个数 : $r_1$ ~ $r_n$ ， 从中选出 k 个数，对 c 进行右述操作：```c=(c+r[i])/2```

求 c 的最大值。

## 思路
因为要让 c 最大，所以所选出的 $r_i$ 要尽量的大，所以可以先把 r 数组排一遍；因为最先选出的 $r_i$ 要被除的次数最多（ k 次），所以要让大数排在靠后面，来减少损失。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005];
double c;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		cin>>a[i];//输入
	sort(a+1,a+n+1);//把 r 数组从小到大排。
	for(int i=n-k+1;i<=n;++i)
		c=(c+a[i])/2;//从第n-k+1大的元素开始计算公式
	printf("%0.6f",c);//输出
	exit(0);
}
```

完结撒花~

谢谢 qwq

---

## 作者：lsw1 (赞：0)

设使得最终的 $C$ 最大的 $\{R\}$ 为 $R_1, R_1,R_2,\cdots R_k$ ,则 $\begin{aligned}C&=((R_1\div2+R_2)\div2+R_3)\div2+\cdots\\&=R_1\div2^{k-1}+R_2\div2^{k-2}+\cdots+R_k\end{aligned}$

可以发现，要想最大化 $C$ ，要从 $\{R\}$ 中取最大的 $k$ 个，将其升序排序，即让 $R_k$ 最大，其次 $R_{k-1}$ , $\cdots$ ，因为先加进去的数除的次数越多，所以大数要尽量后加进去。
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXN = 1e2;
int a[MAXN + 5];
bool cmp(int a,int b)
{
	return a > b;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a + 1,a + n + 1,cmp);//挑出最大的k个
	sort(a + 1,a + k + 1);//把最大的k个升序排序
	double ans = 0;
	for(int i = 1;i <= k;i++)
	{
		ans = (ans + a[i]) / 2;
	}
	printf("%.6lf",ans);
	return 0;
}
```

---

## 作者：奥斯卡小冰人 (赞：0)

要使 $C$ 最大，就需要 $R$ 尽可能的大。所以在输入之后，用 $sort$ 进行排序，然后从最大的数加到第 $k$ 个数，最后用 $printf$ 保留6位小数。
~~别问为什么要从 $n - k$ 加到 $n$ 而不是直接从 $n$ 开始往下加 $k$ 个，问就是当时脑子没转过来。~~

$AC$ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k,r[100000];
    double c = 0;
    cin >> n >> k;//输入
    for(int i = 0;i < n;i++) cin >> r[i];
    sort(r,r + n);//排序
    for(int i = n - k;i < n;i++) c = (c + r[i]) / 2;//最大加到第k个
    printf("%.6lf\n",c);//输出
    return 0; 
}
```


---

## 作者：信守天下 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT795)
## 显然是一道贪心题
因为要使 $c$ 最大,而 $c$ 的值又与 $r$ 直接挂钩

所以这道题直接就变成了从数列中取出 $k$ 个最大的数，按公式计算答案

直接 $sort$ 排序就行了，~~STL大法好！~~

然后直接贪心,取尽量大的数

需要注意的是，大数要尽量后加进去，因为先加进去的数除的次数越多
## $code$
~~~cpp
#include <algorithm>     //sort排序
#include <iostream>      //cin and cout
using namespace std;
const int kMaxN = 100001;//常数，n的最大值 + 1，因为我习惯从1开始存
int n, k, a[kMaxN];      //定义变量
double c;                //答案
int main() {
  cin >> n >> k;         //读入n,k
  for (int i = 1; i <= n; i++) {
    cin >> a[i];         //读入数组
  }
  sort(a + 1, a + n + 1);               //把数组从小到大排序。
  for (int i = n - k + 1; i <= n; i++) {//从第n - k + 1大的元素开始计算答案,到最后刚好是k个元素
    c = (c + a[i]) / 2;                 //计算答案
  }
  printf("%0.6f", c);                   //输出
  return 0;                             //华丽的结束
}
~~~

---

## 作者：Lithium_Chestnut (赞：0)

又是一道水黄题。

题目大意就是说，给定数组 $r$，选出 $k$ 个数，需要使 $\frac{c+r_i}{2}$ 的值最大。

题意很简单，显然如果要求答案的值最大的话，我们要保证 $r_i$ 的值大于此前 $c$ 的值；换句话说，为了增加 $c$ 的值，我们需要让 $r_i$ 也变得更大，因此我们需要快排一下，使 $r$ 数组中较大的值排到更后面的位置上，这样前 $n-k$ 位就是我们要丢弃的小值，所以，从第 $n-k+1$ 位到第 $n$ 位是我们所需要的 $r_i$ 的最大值，然后依题意把这些位上的 $r_i$ 累加即可。

最后别忘了保留六位小数。

```
#include<bits/stdc++.h>
using namespace std;
double c;
int n,k,r[100001];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>r[i];
	sort(r+1,r+n+1);
	for(int i=n-k+1;i<=n;i++) c=(c+r[i])/2;
	printf("%.6lf\n",c);
	return 0;
}
```


---

## 作者：Daidly (赞：0)

由题可得：$C=\frac{C}{2}+\frac{R_i}{2}$

所以，当 $R_i>C$ 时 $C$ 的值会变大，每一次都要变大，所以要使得 $C<R_i<R_{i+1}$，那么排序（排序要从大往小排）加遍历（从第$k$个往前遍历$k$次）就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005];
double c=0;
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n>>k;
	for(int i=0;i<n;++i){
		cin>>a[i];
	}
	sort(a,a+n,cmp);
	for(int i=k-1;i>=0;--i){
		c=(c+a[i])/2;
	}
	cout<<fixed<<setprecision(6)<<c;
	return 0;
}

```

---

## 作者：Kevin_Zhen (赞：0)

题目链接 [AT795](https://www.luogu.com.cn/problem/AT795)。

### 贪心正确性推导
我们手玩一下 $n=3,k=3$ 的情况，看看这道题是如何贪心的。

设我有一个三个数的序列 $r_1,r_2,r_3$。  
模拟题意，$c$ 与这三个数依次运算，最终结果是 $\dfrac{\dfrac{\dfrac{c+r_1}{2}+r_2}{2}+r_3}{2}$。  
化简一下，最终变成 $\dfrac{c}{8}+\dfrac{r_1}{8}+\dfrac{r_2}{4}+\dfrac{r_3}{2}$。  

显然，$\dfrac{c}{8}$ 为定值，要想使这个式子的值最大，$r_1,r_2,r_3$ 应升序排列。  
将思路一般化，算上 $k\ne n$ 的情况时，即是求出序列 $r$ 最大的前 $k$ 项，按照升序依次与 $c$ 运算。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, k;
int r[100010];
double c = 0;

inline bool cmp(int a, int b) { return a > b; }

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &r[i]);
	sort(r + 1, r + 1 + n, cmp);
	for (int i = k; i; --i) c = (c + r[i]) / 2;
	printf("%.6lf\n", c);
	return 0;
}
```

### 感谢观赏！

---

## 作者：Level_Down (赞：0)

## 题意简述：
#####   ·给定n个数的数列a；
#####   ·依次选取k个数完成公式：
```
ans = (ans + a[i]) / 2;
```
#####   ·求ans的最大值。

## 方法：

1.要使ans值最大，肯定得要让选取的数保证是最大的一批。

2.钻研公式： ans = ans / 2  + a[i] / 2, a[i]/2这一项的值我们无法改变，

但是ans/2的值我们能改变，我们要让损失尽可能小，就要在最大的一批数中，由小到

大地做公式。

！！！

于是代码新鲜出炉：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[1000001],b[1000001];//数组b为选取的数组a中最大的一批
double ans = 0;
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++){cin >> a[i];}//输入
	sort(a+1,a+1+n);//排序
	for (int i = 1; i <= k; i++){b[i] = a[n - i + 1];}//将b[i]赋值为数组a中最大的一批
	for (int i = k; i >= 1; i--){ans = (ans + b[i]) / 2;}//从小到大按公式计算
	printf("%0.6lf\n",ans); //输出
	return 0;	
 } 
```

##### 又A了一道黄题！

---

## 作者：fls233666 (赞：0)

**2020年2月14日更新：修复题解排版问题**

--------

题目中要求最后结果的最大值，所以此题采用**贪心**算法。

想要求最大值，就要让 $(C+R)/2$ 尽可能大，就是要让 $C+R$ 的值尽可能大，那么如何做到这一点呢？

我们举个例子：

设有四个 $R$ 分别为 $R_{1}$、$R_{2}$、$R_{3}$、$R_{4}$，初始的速率是 $C$。

按顺序算每个 $R$。

得到最终速率为 $((((C+R_{1})/2+R_{2})/2+R_{3})/2+R_{4})/2$。

拆开括号化简得到：$\frac{C}{16}+\frac{R_{1}}{16}+\frac{R_{2}}{8}+\frac{R_{3}}{4}+\frac{R_{4}}{2}$。

我们观察发现：

**如果我们想要最终速率最大，我们就要使 $\frac{R_{1}}{16}+\frac{R_{2}}{8}+\frac{R_{3}}{4}+\frac{R_{4}}{2}$ 最大**。

显然，当 $R_{1}<R_{2}<R_{3}<R_{4}$ 时，这个式子有最大值。

那么我们推广到一般情况：

**当 $R_{1}<R_{2}<R_{3}<...<R_{N-1}<R_{N}$ 时，最终速率最大！**

我们要使所有的 $R$ 符合上面这个条件，这就是我们的贪心策略。

怎么做到呢？

排序啊！

把所有的 $R$ **从小到大排序**，然后按顺序把每个 $R$ 和 $C$ 运算一遍，就能得到最大的最终速率。

 AC 代码如下：
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int n,k;   
    scanf("%d%d",&n,&k);
    //读入n和k
  
    double r[n],c=0; 
    for(int i=0;i<n;i++)
        scanf("%lf",&r[i]);
    //读入每个r[i]
                         
    sort(r,r+n);  //排序，sort默认从小到大排序
    for(int i=n-k;i<n;i++)
        c=(r[i]+c)/2;   //运算
    printf("%0.6lf\n",c);   //输出
    return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

这道题目的思路，应该说还是很简单的。让$C$的值尽可能大就是让$C+R_i$的值尽可能大。现在我们要取$k$个数字，那么这$k$个数字也得是数组$R$中前$k$大的。  
这样子解法就出来了！  
```
#include <bits/stdc++.h>
using namespace std;
#define N 110000//我也不知道n有多大，但是开的大一点也没什么坏处
double ans=0.0;
double R[N];
int n,k;
namespace doit
{
	inline int read()//快读函数
	{
		int x=0,p=1;
		char c;
		c=getchar();
		while(c<'0'||c>'9')
		{
			if(c=='-')
				p=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			x=x*10+c-'0';
			c=getchar();
		}
		return x*p;
	}
	inline void Read()//读入
	{
		n=read();k=read();
		for(register int i=1;i<=n;i++)
			scanf("%lf",&R[i]);
	}
	inline void todo()//重要的部分来了
	{
		sort(R+1,R+n+1);//必须排序，否则你就得不到一个有序的数列
		for(register int i=n-k+1;i<=n;i++)//注意sort是从小到大排序的
			ans=(ans+R[i])*1.0/2;//套公式
		printf("%.6lf\n",ans);//注意输出六位小数并且换行
	}
}
int main()
{
	doit::Read();
	doit::todo();
}
```

---

## 作者：RioBlu (赞：0)

### 小小的贪心就过。

贪心思路：

**如果你从4个内选3个，你肯定选最大的3个，为什么？这样最大！**

**但是怎么排列？从小到大！**为什么：

R1你要除多少次？B次是不是

R2你要除多少次？B-1次是不是

R3你要除多少次？B-2是不是

那么可以理解为这个式子:$R1/2^{B-0}+R2/2^{B-1}+R3/2^{B-2}......$

那么把最小的放在前面损失小一点
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c[5000],d;
double now; 
int main()
{
	cin>>a>>b;
	for(int s=0;s<a;s++)cin>>c[s];
	sort(c,c+a);
	for(int s=a-b;s<a;s++)
	{
		now=(now+c[s])/(double)2;
	}
	printf("%.10lf\n",now);
}
```

---

