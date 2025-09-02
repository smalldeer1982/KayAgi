# Arrays

## 题目描述

You are given two arrays $ A $ and $ B $ consisting of integers, sorted in non-decreasing order. Check whether it is possible to choose $ k $ numbers in array $ A $ and choose $ m $ numbers in array $ B $ so that any number chosen in the first array is strictly less than any number chosen in the second array.

## 说明/提示

In the first sample test you can, for example, choose numbers 1 and 2 from array $ A $ and number 3 from array $ B $ (1 < 3 and 2 < 3).

In the second sample test the only way to choose $ k $ elements in the first array and $ m $ elements in the second one is to choose all numbers in both arrays, but then not all the numbers chosen in $ A $ will be less than all the numbers chosen in $ B $ : ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF572A/8f3fbb0b873bf77b8e348f9f28840bbc5c624918.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 3
3 4 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
3 3
1 2 3
3 4 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 2
3 1
1 1 1 1 1
2 2
```

### 输出

```
YES
```

# 题解

## 作者：liuyifan (赞：3)

C++自认为比较简单的思路,切莫抄袭

直接a取最小的k个,b取最大的m个比较,简单贪心

code:
```cpp
#include<bits/std+.h>
#define reg register 
using namespace std;
int n,aa[1000000],bb[100000,a,b,x,y;
int main()
{
	scanf("%d%d%d%d",&a,&b,&x,&y);
	for(reg int i=1;i<=a;i++)scanf("%d",&aa[i]);
	for(reg int i=1;i<=b;i++)scanf("%d",&bb[i]);
	//因为保证升序所以不用sort
	puts(aa[x]<bb[b-y+1]?"YES":"NO");//如果满足输出YES 
	retur 
}
```
[My Blog](https://www.luogu.org/blog/liuyifan/)

---

## 作者：zilingheimei (赞：0)

蒟蒻来写题解了

先看题目：

[CF572A Arrays](https://www.luogu.com.cn/problem/CF572A)

------------

这题很简单，思路如下：

1. 取数列$A$中最第$k$大的数，与数列$B$中第$m$小的数比较。


2. 大于输出$NO$，小于输出$YES$。

```cpp
if(a[k]<b[n2-m+1]){
	cout<<"YES";
	return 0;
}
else {
	cout<<"NO";
	return 0;
}
```

3. 可以不用排序，因为数据保证升序数列

4. 注意$1 \leq nA,nB \leq 10^5$，数组不要定小了

------------

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,n2,k,m,a[10010],b[10010];
int main(){
	cin>>n1>>n2>>k>>m;
	for(int i=1;i<=n1;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n2;i++){
		cin>>b[i];
	}
	if(a[k]<b[n2-m+1]){
		cout<<"YES";
		return 0;
	}
	else {
		cout<<"NO";
		return 0;
	}
	return 0;
}

```



---

## 作者：Dimly_dust (赞：0)

- 这道题呢是像两位大佬一样说的：**不用sort!（题中有这样一句话：给定升序数列$A,B$）** 这样只会增加时间复杂度，如果竞赛就更不可能用了。

普及一下什么是**升序列($ascending\,sequence$)**：就是指所有$A_i>A_{i-1}$，比如序列$\{1,2,3,4\}$就是一个升序列。

**思路讲解：** 因为是升序的，则$A_k$是$A$序列中最大的数，$B$序列中最小的数是$B_{size-m+1}$(Size指$B$序列的长度)。

再就是简单的比较了，可以偷懒一下，用可以用三目运算符来判断$A_k$和$B_{size-m+1}$的大小。

**Ps:** 判断大小时慎用 **max** ，有$A_k =B_{size-m+1}$的情况要特判！

**代码如下：**

```cpp
#include<iostream>//建议不要用万能头，浪费内存还耗时间
using namespace std;//如果还想省空间 ，可以把这个去掉，之后则加std::(如：std::cin>>x;)
int a[1000000],b[100000],n,m,x,y;
int main()
{
    cin>>n>>m>>x>>y;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    for(int i=1; i<=m; i++)
        cin>>b[i];
    printf("%s",a[x]<b[m-y+1]?"YES":"NO");//简略形式，可拓展
    return 0;
}
```


---

