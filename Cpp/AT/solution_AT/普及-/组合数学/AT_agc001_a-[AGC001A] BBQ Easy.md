# [AGC001A] BBQ Easy

## 题目描述

Snuke 在参加一个户外烧烤派对，他要将 $2n$ 份食材两两配对组成 $n$ 份。  
每个食材有一个价值，为 $L _ i$。一份食物的价值是其两个食材中较小的那个。  
问最大总价值是多少。

## 说明/提示

$1 \le n \le 100, 1 \le L_i \le 100$。保证 $L_i$ 是整数。

## 样例 #1

### 输入

```
2
1 3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
5
100 1 2 3 14 15 58 58 58 29```

### 输出

```
135```

# 题解

## 作者：初音Miku (赞：5)

看着题目第一眼还以为是贪心，后来发现哪有那么麻烦。。。不需要太高大上的算法。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//sort头文件
using namespace std;
int a[10001],ans=0,bns=0,n;//乱入了1个打酱油的变量。
int main()
{
	scanf("%d",&n);//读入数据
	for(int i=1;i<=2*n;i++)//题目说的是2n，别一顺手就打错了。
	{
		scanf("%d",&a[i]);//循环读入
	}
	sort(a+1,a+1+2*n);    //所有数据排序
	for(int i=1;i<=2*n;i+=2)
	{
		bns+=a[i];//根据题意分析，我们只需要逐个跳着加和即为所求。
	} 
	printf("%d\n",bns);//AT通性，换行
	return 0;//结束
}

```

---

## 作者：Instudy (赞：3)

首先我们分析一下题意：

  就是求出一个数列中两两配对中的最小值的和，貌似很麻烦~~明明是我讲的麻烦~~，我们来分析一下样例：
  
  ```
5
100 1 2 3 14 15 58 58 58 29
```
拿这个看起来很强的样例举例吧：

难道我们要把$ (100,1) $配对？？这样就浪费了$ 100 $这个这么大的价值，不划算。

于是我们将数列从小到大排序一遍，每两个数为一个二元组，求出这两个数中的最小值的和即可。

~~这好像很显然不需要证明~~

核心代码：

```cpp

	for(int i=1;i<=2*n;i++)scanf("%d",&l[i]);//注意读入的是2n长度
	sort(l+1,l+2*n+1);//排序也要2n长度
	for(int i=2;i<=2*n;i+=2)//我们从2枚举，因为我们排序好了，所以最小值一定是前面那个
	 	ans+=l[i-1];
```

~~最近不怎么喜欢放完整代码啊抄袭者可以走了~~

---

## 作者：No_Au_No_Name (赞：1)

### 模拟

~~这题评橙高了吧。~~ 就是快排搞下就行了。主要坑点在于，题面里写的是 $2 \times n$，所以在代码里搞了个变量 $p$，表示 $2 \times n$，输入、快排、输出都用它。

那这题就考察的是**快排**。简单跟大家讲一下快排函数的用法。快速排序是基于 `C++` 中 `STL` 函数的调动用法，名字为 `sort`。`sort` 函数内每次装 $2$ 个值，中间用逗号隔开。这两个值左面的表示你要排序的开始位置，右面的则表示结束位置，调用函数后，在这个数组里的开始位置到结束位置内的所有数都会排序呈现，所以不得不说，`STL` 函数真的是非常方便了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10001],ans,p;
int main()
{
	cin>>n;
	p=n*2;
	for(int i=1;i<=p;i++) cin>>a[i];
	sort(a+1,a+p+1);
	for(int i=1;i<=p;i+=2) ans+=a[i];
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Times_New_man (赞：0)

# 题解 AT1979
~~这题仿佛是一个年份~~

废话少说,现在进入题目。  
为了使总价值浪费的最少,我们必须让两两配对的食物价值差最小。  
因此,我们总是将相邻价值的两个食材放在一起烤。  
为了计算方便,我们首先需要排序,然后再进行~~烧烤~~计算。
时间复杂度$O(n_{log}n),$瓶颈在快速排序。

下面是代码。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

long long n,a[10000],ams;
//n:烤串总数
//a:存储食材
//ams:记录总价值,也就是输出的答案

int main()
{
	ios::sync_with_stdio(0);		//输入输出加速
	 cin>>n;						//输入烤串总数
	 n*=2;							//×2变为食材总数
	 for(int i=1;i<=n;i++)			//枚举输入
	 	cin>>a[i];
	 sort(a+1,a+n+1);				//按食材的价值从小到大排序
	 for(int i=1;i<n;i+=2)			//两两配对,所以从1开始枚举,枚举到n,每次加2
	 	ams+=a[i];					//由于是从小到大排序,所以可以直接加上a[i]。不太懂的同学可以写ams+=min(a[i],a[i+1]);
	 cout<<ams;						//输出总价值
	return 0;						//程序退出
}
```

---

## 作者：tony123456 (赞：0)


这道题是很基础的贪心算法

看完题之后，可以发现总价值sum=(Sum-a)/2,其中Sum为输入数之和，a为每组的差之和。所以，当差值最小时，总价值可以取到最大值，这样浪费的食材就会少。而一个经过排序的数组刚好可以满足相邻两项之差最小，所以我们可以在输入之后用sort排序一下，之后记录奇数项之和，即为总价值的最大值。

附带码：
```cpp
#include<iostream> //头文件，下同
#include<algorithm> 
using namespace std;
int a[110];
int main(){
    int n;
    cin>>n;
    n=n*2; //因为输入的数量是n*2，所以要把n乘2
    for(register int i=1;i<=n;i++){
        cin>>a[i];//输入
    }
    sort(a+1,a+n+1);//排序，上面说原因了
    int sum=0;
    for(register int i=1;i<=n;i+=2){
        sum+=a[i];//把奇数项数字和求出来
    }
    cout<<sum<<endl;//输出
    return 0; //返回 0
}
```

请不要恶意抄袭代码，不然会变成作弊者！

---

## 作者：King丨帝御威 (赞：0)

读完题目，可以发现当两数差最小的时候，那么大的数就不会被浪费掉，那么这个时候我们可以将原数组排一遍序，然后隔着累加答案就好了。。


~~附奇丑无比的代码~~：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#define maxn 200+1       
using namespace std;
int n,a[maxn],ans;      
int main()
{
	scanf("%d",&n);
	int md=n<<1;                //右移一位，相当于2*n。
	for(int i=1;i<=md;++i)
	{
		scanf("%d",&a[i]);
	}
    sort(a+1,a+1+md);           //对a数组排序。
    for(int i=1;i<=md;i+=2)
    { 
        ans+=a[i];             //当两数差最小时，ans才会最大，所以隔一个加一次。
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：查无此人j (赞：0)

# ~~BIG WATER QUESTRION~~

------------
## 言归正传，只需要分析一下此题便能解

题意——一共有2n个数，随机两数中最小数为价值，求最大价值。

### 那么此题的解法应该就是小的排一起，大的放一块。

再看样例

输入 2

输入 1 3 1 2

输出 3

则排列应为

1，1

2，3

解得2+1=3
### 思路正确，看代码
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//日常
typedef long long LL;
/*NOIP常出大数据，要有用longlong的好习惯*/
LL a[1000000],n,sum=0;//a为数，sum为累计
int main(){//主程序
    cin>>n;//输入
    for(int i=0;i<n*2;i++){
        cin>>a[i];//输入
    }
    sort(a,a+n*2);//sort从小到大排序
    for(int i=0;i<n*2;i++){//隔位加
        sum+=a[i];
        i++;
    }
    cout<<sum<<endl;//输出，AT题尽量换行
    return 0;//OK
}
```
# ~~庄哥最帅~~

---

