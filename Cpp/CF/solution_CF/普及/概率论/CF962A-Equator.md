# Equator

## 题目描述

已知 Polycarp 共有 $n$ 天准备编程竞赛，他每天预计做的题数为 $a_i$，请问直到第几天能做完所有题目的一半或更多。

## 样例 #1

### 输入

```
4
1 3 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
2 2 2 2 2 2
```

### 输出

```
3
```

# 题解

## 作者：pigstd (赞：4)

思路：模拟

只要把应做的求出来，再一步一步加即可

c++代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=200005;
int a[M],n,s;

int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i],s+=a[i];
	s=(s+1)/2;//s是应做的题数，因为直接/2是向下取整，所以先加一 
	int sum=0;//sum是当前的做题数 
	for (int i=1;i<=n;i++)
	{
		sum+=a[i];
		if (sum>=s)
		{
			cout<<i;
			return 0;
        //如果大于，只要输出，然后直接return 0即可
		}
	}
}
```

---

## 作者：引领天下 (赞：2)

这题很简单啊，怎么没人发题解呢？

所以我来一发很简单的模拟

代码：（思路码里说）
```cpp
#include <cstdio>
int s,ans,a[200005],n;
int main(void){
    scanf ("%d",&n);//读入不解释
    for (int i=0;i<n;i++)scanf ("%d",&a[i]),s+=a[i];//求总共有多少题
    int i=0;
    for (;i<n;i++){ans+=a[i];if(ans>=s*1.0/2)break;}//注意！直接/2是下取整！所以要用double！
    printf ("%d",i+1);//0下标+1
}
```

---

## 作者：Register (赞：1)

# 水~
	第一步大家都知道，将所有天的题加起来就可以了
    接着通过奇偶性判断得出哪个数是题量的一半

	下一步就是让一个变量统计需要第几天
    只要没达到要求，就从记录一半的变量减掉这个元素
**最后输出记录一半的变量**

上代码：
```cpp
#include <iostream>
using namespace std;
int main(){
	int a[200001],n,half=0,day=0;//几个变量定义
	cin>>n;
	for(int i=1;i<=n;i++) {cin>>a[i];half+=a[i];}
	if(half%2) half=half/2+1;//一半处理1
	else half/=2;//一半处理2
	while(half>0) half-=a[++day];//不停地减，减到不够减
	cout<<day<<endl;//输出
	return 0;
}
```

---

## 作者：OdtreePrince (赞：1)

# -真心模拟-

只需将总和求出并求平均值，再用a数组统计到i的所有数字之和，如果大于平均值，输出并退出。完美AC！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],k,sum;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&k);
        a[i]=a[i-1]+k;
        sum+=k;
    }
    if(sum%2==0) sum/=2;
    else sum=sum/2+1;
    for(int i=1;i<=n;i++){
        if(a[i]>=sum){
            cout<<i;
            break;
        }
    }
    return 0;
}~~~

---

## 作者：一个低调的人 (赞：0)

## 我发现没有一个题解用二分的...

- 这道题目就是求一个最小的数 **k** ，使得第 **1** 到第 **k** 天做的题数的和大于等于总题数的一半。

- 一看要求和就用前缀和维护啊！每读入一个数就把它直接处理进前缀和中。

- 由于前缀和是单调递增的，故二分寻求答案即可！但需要注意的是，总题数有可能是奇数，整数除法是向下取整的，故在除之前给总题数+1，确保精度正确。

- 时间复杂度为 $O(n+\log_e n)$ ，具体细节详见 **代码** 。

## Code
```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
long long int n,sum[200001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){int x;cin>>x;sum[i]=sum[i-1]+x;}
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(sum[mid]>sum[n]/2)r=mid-1;
		else l=mid+1;
	}
	if(sum[l-1]>=(sum[n]+1)/2)l--;
	printf("%d",l);
	return 0;
}
```

---

## 作者：开心的猪 (赞：0)

这道题的思路就是模拟。

首先读入一个数组，求出这个数组所有项数之和。

接下来，逐个求出从第一天到第i(i<=n)天的题数之和，如果超过了所有题数之和的一半，就输出了。

下面是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int alpha;
	scanf("%d", &alpha);
	int a[alpha];
	for(int i=0; i<alpha; i++)
	{
		scanf("%d", &a[i]);
	}
	int all=0, sch=0;
	for(int i=0; i<alpha; i++)
	{
		all=all+a[i];
	}
	float alp=(float)all/2;
	for(int i=0; i<alpha; i++)
	{
		sch=sch+a[i];
		if(sch>=alp)
		{
			printf("%d", i+1);
			return 0;
		}
	}
}
```


---

