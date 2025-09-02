# Optimal Point on a Line

## 题目描述

给你 $n$ 个点，为数轴上的点。找到一个 $x$，到所有数的距离的和最小。

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
2
```

# 题解

## 作者：sxtm12138 (赞：1)

这道题的方法相信大家都知道了：将给出数据排序后，输出他们的中位数（偶数为第n/2个数），我只是在此基础上把奇数和偶数的情况合并了一下而已。n为奇数时，位置为第（n/2+1）个点，由于n+1为偶数，故(n+1)/2=n/2+1；n为偶数时，位置为第n/2个数，而n/2=(n+1)/2，故两式可以合并为：**(n+1)/2**。

 _代码如下：_ 

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005],n;//不用longlong也能过
int main()
{cin>>n;
 for(int i=1;i<=n;i++) cin>>a[i];//读入
 sort(a+1,a+n+1);//题目没说升序输出，所以要排序
 cout<<a[(n+1)/2];//使用合并后的公式
}

```

---

## 作者：RBI_GL (赞：0)

### 题意：

给定$n$个数，请你找到一个数，

**使得这个数与那$n$个数差的绝对值之和的取到最小值。**

-----

### 推导

如果数轴上有两个数 $a，b$，要求找到一个数$n$，使得$n$到 $a,b$的距离最短。

简单画一个图，我们可以得到结论：

**只要取 $a≤n≤b$ ，得到的都是最小值。**

所以：如果有多个数，要求找到 $n$ ，那么 $n$ 只要取**这些数总小到大排序后的中位数即可。**


----
### 思路：

1.读入数据

2.将数组进行**sort**从小到大快排

3.输出排序后数组的中位数（**位置的标号在最中间的那个数**）


Code：
-
```cpp
#include <bits/stdc++.h>
using namespace std;
int n; 
int a[300005];
int main()
{
    cin>>n; //读入数据个数 
    for(int i=1;i<=n;i++) {
    	cin>>a[i];//读入数据 
	} 
    sort(a+1,a+n+1); //快排 
    if (n%2 == 0) {
    	cout<<a[n/2]; //输出中位数 
	}
	else {
		cout<<a[n/2+1]; //输出中位数 
	} 
    return 0;
}
```



---

## 作者：__白衣渡江__ (赞：0)

短代码福利。

首先，肉眼观察就知道是求中位数。

所以可以直接排序，就好了。

```python
n=int(input())#读入
print(sorted(map(int,input().split()))[(n-1)//2])
```

解释一下第二行：

`input().split()` 用来读入一行并分割，但还都是字符串。

`map(int,input().split())` 可以返回一个上述列表全部转为整数的新列表。

`sorted(map(int,input().split()))` 可以返回一个排序后的上述新列表。

`(n-1)//2` 是中位数位置。

Over.

祝大家AC！

---

## 作者：_cmh (赞：0)

典型的求中位数

本题直接读入，排序，输出中位数

那么中位数的求法就是用n/2+n%2求出

## sort大法好！！！

看到dalao们没有介绍sort

我来介绍一下sort

sort是属于STL里的一种~~作弊~~工具

格式（数组从0开始存）：sort(数组名,数组名+数组长度);

格式（数组从1开始存）：sort(数组名+1,数组名+1+数组长度);

用到的头文件：``` #include<algorithm> ```

sort默认的排序方式是从小到大排序

好了，sort就介绍到这了

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>//头文件 
using namespace std;
int n,a[300001];//定义n和所有数 
int main(){
    cin>>n;//读入有几个数 
    for(int i=1;i<=n;i++) cin>>a[i];//读入数 
    sort(a+1,a+n+1);//排序，用C++STL里的sort 
    cout<<a[n/2+n%2];//输出中位数 
    return 0;
}
```

## 求赞！！！

~~（蒟蒻已经逃跑了，没法和泥萌说再见了）~~

---

## 作者：BB2655 (赞：0)

这是一道~~小学~~数学题

假设所有数从小到大在数轴中排列，那么哪一个点是符合题意的？

如果$n$不是$2$的倍数，那么就是最中间的一个

如果$n$是$2$的倍数，那么在$n/2$和$n/2+1$之间的数都满足；由于题目要求最小，故为$n/2$的值

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()  //快读
{
	int ret=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int a[300005];  //大的数组最好开在外面
int main()
{
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);  //读入数据并排序
	if(n%2==1)  printf("%d",a[n/2+1]);
	else printf("%d",a[n/2]);
	return 0;
}
```

---

## 作者：Strange_S (赞：0)

### 大水题
其实这题很简单，不要想得太复杂。

因为是求离所有数的距离总和最小的点，所以可以知道，最中间那个点肯定是最优的点（初一的应该知道）。只要排序，然后选出最中间的点就可以了。

#### 备注：
不知道为什么，不能插入代码，这是cpp的代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,x[300005],ans,sum=0x3f3f3f3f;
int main(){
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++){    //输入
		cin>>x[i];
	}
	int k;
	sort(x+1,x+n+1);    //排序
	if(n%2==1){       //算出最小点
		n=n/2;
		n+=1;
		ans=x[n];
	}else{
		n=n/2;
		ans=x[n];
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：liuyifan (赞：0)

## 题意：给你n个数,求它们的中位数

顾名思义:中位数:排序后中间的那个数

So code:
```
#include<bits/stdc++.h>/万能头
#define ll long long//这样加一行之后可以将下文所有的ll替换为long long,方便快捷
#define reg register
using namespace std;
ll x[1000000],n;//long long防爆
int main()
{
    scanf("%lld",&n);
    for(reg int i=1;i<=n;i++)scanf("%lld",&x[i]);
    sort(x+1,x+n+1);//快排,默认从小到大
    printf("%lld",n&1?x[n/2+1]:x[n/2]);//中位数的求法
    return 0;
}
```

---

