# Heist

## 题目描述

昨晚有一家电子商店被抢劫了。

昨天在商店里的所有键盘都是从$x$开始按升序编号的。例如，如果$x=4$，并且商店中有$3$个键盘，那么编号就为$4,5,6$；如果$x=10$，并且有$7$个键盘，那么编号就为$10,11,12,13,14,15,16$。

在抢劫之后，只有$n$个键盘仍然存在，他们的编号分别为$a_1,a_2,\dots ,a_n$。计算被盗的键盘的最小可能数量。工作人员不记得$x$也不记得商店里原来有几个键盘。

## 样例 #1

### 输入

```
4
10 13 12 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
7 5 6 4 8
```

### 输出

```
0
```

# 题解

## 作者：been_apart (赞：3)

这题不难，算最小被窃数，不过是让你算次数列最少该有多少元素。只需求出最大值和最小值，相减加一就是最少应有多少元素，减去剩余值便是答案。
下面是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);//排序，当然，在读入是就找出最大最小值更简单。
    cout<<a[n-1]-a[0]+1-n<<endl;//输出结果
    return 0;
}
```

---

## 作者：dblark (赞：3)

这道题目，很水，恐怕又是恶评……

很简单，输入这个数组，然后把$max-min+1$算出来，也就是原来最少有几个键盘，减去$n$就行了。

主要还是题目描述烦。

奉上垃圾Pascal代码：
```pascal
{CF1041A}
var
  a:array[1..1000]of longint;
  n,i,s,min,max:longint;
begin
  read(n);
  min:=maxlongint;
  max:=0;
  for i:=1 to n do
  begin
    read(a[i]);
    if a[i]<min then
      min:=a[i];
    if a[i]>max then
      max:=a[i];
  end;
  writeln(max+1-min-n);
end.
```

---

## 作者：FCBM71 (赞：3)

$\text{CF div 2}$ 的水题一道，所以讲得详细一点

简单说一下思路，既然要最少，那么所给出的键盘序号序列中，最小的那个就一定是 $x$ 号键盘，最大的那一个就一定是  $x+n-1$ 号。 之后，我们知道了键盘序号的最大值和最小值，就可以算出被盗前键盘的个数。再用被盗前的个数减去现在的个数就是答案了。

所以就先`sort`一遍（当然两个`for`循环也可以），取出最大值和最小值。结果便是 `a[n]-a[1]-n+1`

---
贴上代码：

```
#include<bits/stdc++.h>
int a[1000],i,n;
int main(){
	scanf("%d",&n); 
	for(i=1;i<=n;++i)scanf("%d",&a[i]); //读入
	std::sort(a+1,a+n+1);   //排序
	printf("%d",a[n]-a[1]-n+1);  //计算结果
	return 0;
}
```

---

## 作者：piggymichael (赞：1)

所有键盘的编号是一段连续的数，肯定包括所有现有的键盘的编号。被盗数量=所有-现有，现有一定，所以所有越小，被盗数量越少。所有中x最大是现有的最小，最后一个最小是现有的最大。求出所有键盘的最少的数量再减去现在的数量就是答案。

上代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a,minn=0x3f3f3f3f,maxn=0;//minn先是最大值，max最小
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a;
		minn=min(a,minn);//记录最小
		maxn=max(a,maxn);//记录最大
	}
	cout<<maxn-minn+1-n<<endl;//输出，maxn-minn+1是所有的最小值
	return 0;
}
```
其实不用排序，也不用开数组呀。

---

## 作者：xsssg666 (赞：1)

**~~怎么会有这么水的黄题~~
~~就像某些大佬说的，难在看英文~~
首先化简题意，实际上就是给你一些数，求最大和最小数中间有几个没有出现过**
```
#include<iostream>
using namespace std;
int n;
long long int a[10001];
int sum=0;
long long int maxn=0;
long long int minn=11000000000;//初始化；
int b[10001];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        maxn=max(maxn,a[i]);//求最大值；
        minn=min(minn,a[i]);//求最小值；
    }
    sum=maxn-minn-n+1;//
    cout<<sum;
    return 0;
}
```


---

## 作者：Arghariza (赞：0)

其实这题主要考的是排序。

为什么呢？我们想一想。

设```max{a}```为数组a的最大值，```min{a}```为数组a最小值

我们可以得知：生成一个数列从```min{a}```到```max{a}```，从里面筛选出数组a没有的数字。

不过后面这一步可以忽略掉，因为数组a的长度n是固定的，所以最后只用输出```max{a} - min{a} - n + 1```即可。

咋求最大，最小值呢？我们可以在输入中来加上两行语句：

```
maxx = max(maxx, a[i]);
minn = min(minn, a[i]);
```

但是我感觉太麻烦了，所以我们可以使用排序。

本题从大到小或者从小到大没有关系，我选择的是从大到小使用STL中的sort和```#include <functional>```头文件中的```greater<int> ()```自带比较函数来写（很方便有木有）：

```
sort(a + 1, a + n + 1, greater<int> ());
```

所以排完序，就到了最后一步输出（刚刚讲过哈）：

```
cout << a[1] - a[n] - n + 1;
```

所以整个代码就出来了：

```
#include <iostream>   				//输入输出头文件
#include <algorithm>  				//STL排序头文件
#include <functional> 				//greater头文件
using namespace std;  				//命名空间

int n, a[100001];     				//初始定义a数组

int main() {
    cin >> n;                                   //输入n
    for (int i = 1; i <= n; i++) cin >> a[i];   //输入数组
    sort(a + 1, a + n + 1, greater<int> ());    //排序函数
    cout << a[1] - a[n] - n + 1;                //输出答案
    return 0;
}
```

---

## 作者：fls233666 (赞：0)

**2020年2月14日更新：按要求修复题解排版**

--------

初看此题，我们发现键盘的编号是**连续的**并且是**升序的**。

再详细阅读后，我们可以简化一下题意：

原有一个从数$x$开始的升序的连续数列。

现在数列缺失了一些数，只剩下了 $n$ 个数，剩下的数为 $a_1,a_2,a_3...a_n$。

求数列**最少**缺失的数的数量。

然后我们可以从样例中发现一件事：

给出的 $a_1,a_2,a_3...a_n$ **不一定是有序的！**

显然，要做的第一件事就是对剩下的这些数**排序**。

然后我们要知道，什么时候求得的缺失的数的数量是最少的。

我们发现，如果我们设数列中最小的数为 $a_{min}$，最大的数为 $a_{max}$，那么这些数能形成的最小的数列应该是**从 $a_{min}$ 开始到 $a_{max}$ 的升序连续数列**。

然后，请注意，这个数列的数是**连续的**。

也就是说，这个数列中**两个相邻的数相减得到的值应该是 $1$**。

那么，则有：

- 数 $a_1$ 与 $a_2$ 之间缺失的数个数为 $a_2-a_1-1(a_2>a_1)$；
- 数 $a_2$ 与 $a_3$ 之间缺失的数个数为 $a_3-a_2-1(a_3>a_2)$；
- 数 $a_3$ 与 $a_4$ 之间缺失的数个数为 $a_4-a_3-1(a_4>a_3)$；

......

- 数 $a_{n-1}$ 与 $a_n$ 之间缺失的数个数为 $a_{n}-a_{n-1}-1(a_n>a_{n-1})$。

所以，我们只要**循环遍历一遍排序后的数组**，循环中**计算 $a_{i}-a_{i-1}-1(a_i>a{i-1})$ 的值**，并**把计算得到的值累加到一个变量中**。最终累加完得到的这个变量的值就是我们要求的答案。

代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,s=0;  //s记录累加答案
    cin>>n;
    int num[n];
    for(int i=0;i<n;i++)
        cin>>num[i];
  //读入数据
  
    sort(num,num+n);  //排序（sort默认从小到大排序）
    for(int i=1;i<n;i++)
        s+=num[i]-num[i-1]-1;  //计算&累加
    cout<<s;  //输出
    return 0;
}
```


---

## 作者：小闸蟹 (赞：0)

```cpp
// 排序然后遍历一遍即可
#include <iostream>
#include <algorithm>
#include <array>

using ll = long long;

int main()
{
    constexpr auto MaxN = 1000 + 5;
    std::array<int, MaxN> Arr{ 0 };

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> Arr[i];
    }
    std::sort(Arr.begin(), Arr.begin() + n);

    ll Sum = 0;
    for (int i = 1; i < n; ++i)
    {
        if (Arr[i] - Arr[i - 1] != 1)   // 找到不连续的数字（相差大于一），就加上它们中间缺少的那些
        {
            Sum += Arr[i] - Arr[i - 1] - 1;
        }
    }
    std::cout << Sum << std::endl;

    return 0;
}
```

---

## 作者：C_Zn (赞：0)

这个题是一场div2的A题，这个题呢比较水，比较简单，基本看了都会了。

我来说一下这个题的意思：有很多电脑，都是一些连续的整数，一晚上丢了一点电脑，找有多少个电脑可能丢了。

这个题有很多做法，我来说一下最暴力的办法，就是sort一遍，然后找一下里面丢了多少个，代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[10001];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=2;i<=n;i++)
	  ans+=(a[i]-a[i-1]-1);
	cout<<ans<<endl;
	return 0;
}
```

接下来是最优解，最优解呢就是记录一下最大的数和最小的数，再减去n，代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int n;
    int maxn=-1e9,minn=1e9;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        maxn=max(maxn,x);
        minn=min(minn,x);
    }
    cout<<maxn-minn+1-n;
    return 0;
} 
```

---

## 作者：ezoixx130 (赞：0)

### 题意：
有许多的键盘，这些键盘的编号连续，但是某些键盘被偷了，现在给你剩下的键盘的编号，求被偷的键盘数量的最小值。

### 题解：

由于键盘编号连续，那么最少的键盘数量就一定是最大的键盘编号减去最小的键盘编号再加一。

所以只需统计出所有键盘的编号的最大值$maxn$和最小值$minn$，输出$maxn-minn+1-n$即可。

时间复杂度：$O(n)$

空间复杂度：$O(n)$或$O(1)$

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[1001],maxn,minn=2147483647;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",a+i),maxn=max(maxn,a[i]),minn=min(minn,a[i]);
    printf("%d\n",maxn-minn+1-n);
}
```

---

