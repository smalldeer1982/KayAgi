# Nicholas and Permutation

## 题目描述

Nicholas has an array $ a $ that contains $ n $ distinct integers from $ 1 $ to $ n $ . In other words, Nicholas has a permutation of size $ n $ .

Nicholas want the minimum element (integer $ 1 $ ) and the maximum element (integer $ n $ ) to be as far as possible from each other. He wants to perform exactly one swap in order to maximize the distance between the minimum and the maximum elements. The distance between two elements is considered to be equal to the absolute difference between their positions.

## 说明/提示

In the first sample, one may obtain the optimal answer by swapping elements $ 1 $ and $ 2 $ .

In the second sample, the minimum and the maximum elements will be located in the opposite ends of the array if we swap $ 7 $ and $ 2 $ .

In the third sample, the distance between the minimum and the maximum elements is already maximum possible, so we just perform some unnecessary swap, for example, one can swap $ 5 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
4 5 1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
1 6 5 3 4 7 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1
```

### 输出

```
5
```

# 题解

## 作者：chl123123 (赞：2)



###  思路：
这道题其实比较简单，只要找到最大值的下标（max）与最小值的下标（min），然后比较四种情况,找出最大值。

四种情况如下
1.max-1，
2.min-1，
3.n-max，
4.n-min。

### 代码：

```cpp
#include <bits/stdc++.h>//min1表示最小值
using namespace std;//max1表示最大值 z1表示最小值的坐标
int a[100+10];//z2表示最大值的坐标
int main()
{
    int n,i,min1=999999,max1=-1,z1,z2;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]<min1)
        {
             min1=a[i];
             z1=i;//记录最小值坐标
        }
        if(a[i]>max1)
        {
             max1=a[i];
             z2=i;//记录最大值坐标
        }
    }
    cout<<max(max(z2-1,n-z2),max(z1-1,n-z1));//比较四种情况的大小
    return 0;
}
```


---

## 作者：Cult_style (赞：2)

按题意模拟即可，规律不难找到，我们要把最大值或最小值和最靠左或最靠右的的数交换，经过思考，得出下面的式子：

```
	ans=abs(tmi-tma);
	if(tmi>tma)ans=max(ans+tma-1,ans+n-tmi);
	else ans=max(ans+tmi-1,ans+n-tma);
```
其中,$tmi$表示最小值的位置,$tma$表示最大值的位置。总的来说其实就是枚举把最小值移动到最左边或者最右边，和把最大值移动到最左边或者最右边这几种方案的值都列出来，找到最优策略，输出即可。

---

## 作者：q779 (赞：1)

先用$c$记录最大值位置，$d$记录最小值位置

然后取$4$种情况中绝对值最大的

第$1$种，$d$与第$1$个元素交换

第$2$种，$d$与第$n$个元素交换

第$3$种，$c$与第$1$个元素交换

第$4$种，$c$与第$n$个元素交换

代码实现还是比较简单的
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
int n,k,a=-1,b=INT_MAX,c,d;//最大值初始化为-1，最小值初始化为很大的数(2147483647)
signed main()
{
    scanf("%d",&n);
    for(R int i=0; i<n; i++)
    {
        scanf("%d",&k);//无需数组存
        if(k>a)a=k,c=i;
        if(k<b)b=k,d=i;
    }
    printf
    (
        "%d\n",
        max
        (
            max(d,abs(d-(n-1))),
            max(c,abs(c-(n-1)))
        )
    );//此处是为了方便阅读
    return 0;
}
```

---

## 作者：hswfwkj_ (赞：1)

### 对于本题，首先我们要找到最大值和最小值的位置，然后有四种情况：

#### 1.最大值挪到最左边：
```cpp
最小值的位置-1
```
#### 2.最大值挪到最右边：
```cpp
n-最小值的位置
```
#### 3.最小值挪到最左边：
```cpp
最大值的位置-1
```
#### 4.最小值挪到最右边:
```cpp
n-最大值的位置
```
 

只要在这些情况中取最大值就行啦！

贴上完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i,a,Max=-1,Min=999999999,position2,position1;//position1代表最大值位置，position2代表最小值位置
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		if(Max<a){
			Max=a;position1=i;
		}
		if(Min>a){
			Min=a;position2=i;
		}
	}
	cout<<max(max(position2-1,n-position2),max(position1-1,n-position1));//在上述四种情况中取最大值
	return 0;
}
```
如果你觉得这篇题解对你有帮助，那就留下个赞再走吧！你的点赞就是对我最大的鼓励！

---

## 作者：WinterRain208 (赞：0)

CF676A Nicholas and Permutation 

### 题意概述

给你$n$个数，交换任意两个数的位置，使数列中最大的数距离最小的数最远。

### 做法

贪心，如果要满足条件必须换到队首或队尾，记最大数为$a$，最小数为$b$。情况一共有四种。

$a$换到队首，$a$换到队尾，$b$换到队首，$b$换到队尾。

分别枚举这四种情况产生的距离取最大值即可。

放下代码：

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)
using namespace std;

int n,p,x,y,M1=-1,M2=101,ans;
int main(){
	scanf("%d",&n);
	F(i,1,n){
		scanf("%d",&p);
		if(p>M1)M1=p,x=i;
		if(p<M2)M2=p,y=i;
	}
	ans=max(x-1,max(y-1,max(n-x,n-y)));
	printf("%d",ans);
	return 0;
} 
```

点赞再走？

---

## 作者：happybob (赞：0)

~~这道题我很久前做的，思路呢我也差不多忘了……~~

如果差距的绝对值已经最大，那就是答案。

不然把大的移到左边，或者小的另一边，取最大值即可。

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Max
{
	public:
		int xb, value;
		Max();
};

class Min
{
	public:
		int xb, value;
		Min();
};

Max::Max()
{
	xb = -1;
	value = 0;
}

Min::Min()
{
	xb = -1;
	value = 0x7fffffff;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	Max MMax;
	Min MMin;
	for (register int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if (x > MMax.value)
		{
			MMax.value = x;
			MMax.xb = i;
		}
		if (x < MMin.value)
		{
			MMin.value = x;
			MMin.xb = i;
		}
	}
	if ((MMin.xb == 1 && MMax.xb == n) || (MMin.xb == n && MMax.xb == 1))
	{
		cout << n - 1 << endl;
	}
	else
	{
		cout << max(max(MMax.xb - 1, MMin.xb - 1), max(n - MMax.xb, n - MMin.xb)) << endl;
	}
	//system("pause");
	return 0;
}
```


---

## 作者：CZQ_King (赞：0)

### 这道题还算简单，用几个$max(,)$函数就行了。
#### 用了$2$个结构体。。。

------------
代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b[100];
struct aa{
    int mi=0x7FFFFFFF;//int_max
    int x;//用于下标
}minn;//最小值的结构体
struct bb{
    int ma=(-1)*0x7FFFFFFF;//-int_max
    int x;//
}maxx;//最大值的结构体
int main(){
    cin>>a;
    for(int i=0;i<a;i++){
        cin>>b[i];
        if(maxx.ma<b[i]){
            maxx.ma=b[i];
            maxx.x=i;
        }//判断最大值，并把下标i记下
        if(minn.mi>b[i]){
            minn.mi=b[i];
            minn.x=i;
        }//判断最小值，并把下标i记下
    }
    cout<<max(max(abs(minn.x-a+1),minn.x),max(abs(maxx.x-a+1),maxx.x))<<endl;//输出距离大的
    return 0;//结束
} 
```

---

## 作者：RioBlu (赞：0)

数据非常非常的小

同时本题也非常非常的简单
```
#include<bits/stdc++.h>
using namespace std;
int a,b[105],s,mins,minn=9999,maxs,maxx=-1;
int main()
{
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>b[s];
		if(minn>b[s])//最小
		{
			minn=b[s];
			mins=s;
		}
		if(maxx<b[s])//最大
		{
			maxx=b[s];
			maxs=s;
		}
	}
	cout<<max(max(abs(mins-0),abs(mins-(a-1))),max(abs(maxs-0),abs(maxs-(a-1))))<<endl;//看看下面哪种情况最大：把最大的挪到第一位；把最大的挪到最后一位；把最小的挪到第一位；把最小的挪到最后一位
}
```

---

