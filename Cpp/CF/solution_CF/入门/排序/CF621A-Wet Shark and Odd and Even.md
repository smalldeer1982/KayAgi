# Wet Shark and Odd and Even

## 题目描述

Today, Wet Shark is given $ n $ integers. Using any of these integers no more than once, Wet Shark wants to get maximum possible even (divisible by $ 2 $ ) sum. Please, calculate this value for Wet Shark.

Note, that if Wet Shark uses no integers from the $ n $ integers, the sum is an even integer $ 0 $ .

## 说明/提示

In the first sample, we can simply take all three integers for a total sum of $ 6 $ .

In the second sample Wet Shark should take any four out of five integers $ 999999999 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
6```

## 样例 #2

### 输入

```
5
999999999 999999999 999999999 999999999 999999999
```

### 输出

```
3999999996```

# 题解

## 作者：cq_loves_Capoo (赞：2)

这题运用一个小学知识就可以做对：    
奇数+奇数=偶数。   
偶数+偶数=偶数。   
偶数+奇数=奇数。 
那么我们就把所有数加出来，如果答案为奇数，那么就减去最小奇数。         
解题思路：    
1.把所有数加起来，同时求出最小奇数。        
2.判断和是否为奇数，如果为奇数，减去最小奇数。   
3.输出。    
代码如下：   
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,mi,sum;//一定要开long long,因为数据范围累加起来大于int。 
int main()
{
	mi=9999999999;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
    {
		scanf("%lld",&s);
		sum+=s;//算出累加和 
		if(s%2==1) mi=min(mi,s);//找出最小奇数 
	}
	if(sum%2==1) sum-=mi;//如果和为奇数，减去最小奇数 
	printf("%lld",sum);//输出
	return 0;//好习惯 
}
```


---

## 作者：CZQ_King (赞：1)

#### 这篇题解对于楼下那位大佬来说比较简单易懂，思路是差不多的。对于代码我有一些优化。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
long long ans;//只是答案需要开long long，100000*1000000000已经超过了int
int j[100005],n,a,js;//这些可以用int
bool k;//最后循环达到的次数
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a;//输入可以只用一个变量，节省空间
        if(a%2==1){//如果是奇数
            j[js]=a;//存入到数组
            js++;//下标++
        }
        else ans+=a;//偶数就直接加上
    }
    sort(j,j+js);//排序
    if(js%2==1)k=1;//判断奇数的个数是否为奇数
    for(int i=js;i>=k;i--)ans+=j[i];//把偶数个奇数加上
    /*同等于for(int i=js;i>=js-(js/2)*2);i++)*/
    cout<<ans<<endl;//然后输出答案
    return 0;//结束
}
```

---

## 作者：RioBlu (赞：1)

O(N)算法

本题需要数组吗？不需要

空间也非常非常的小
```
#include<bits/stdc++.h>
using namespace std;
long long a,dan,minn=99999999999,ans,l;//minn：最小的奇数
int main()
{
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>l;
		ans+=l;//先加上去
		if(l%2==1)//l是奇数
		{
			dan++;//奇数个数
			minn=min(minn,l);
		}
	}
	if(dan%2==1)ans-=minn;//好像可以是ans%2==1，对于答案是奇数，减去掉一个最小的奇数
	cout<<ans<<endl; 
}
```

---

## 作者：小水滴 (赞：1)

题目大意：给定N个数（$N<=100000$），在这N个数中选若干个数，要求这些数的和为偶数且最大。

思路：首先，偶数+偶数=偶数，所以如果有偶数，就直接选上。再来说奇数，如果有偶数个奇数，那么是可以全部选上的，否则必须舍弃一个。所以，读入时将所有奇数保存到一个数组里面，排序（从大到小）以后判断能否全部选上，如果不行丢弃最小的，就可以解决问题了。

参考代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,h;
long long a[100001],sum,b[100001];
//虽然每个数不会超过10^9，但是还是开long long保险
bool cmp(long long &_1,long long &_2)
{
    return _1>_2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        if(a[i]%2==0) sum+=a[i];//偶数直接加上
        else b[++h]=a[i];//将奇数保存到另一数组中
    }
    sort(b+1,b+h+1,cmp);//从大到小排序
    for(int i=1;i<=((h%2==0)?h:(h-1));i++) sum+=b[i];//将奇数加上
    printf("%lld\n",sum);
    return 0;
}
```

---

