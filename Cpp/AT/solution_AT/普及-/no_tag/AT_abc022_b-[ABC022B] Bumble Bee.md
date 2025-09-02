# [ABC022B] Bumble Bee

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc022/tasks/abc022_b

高橋君はマルハナバチ(Bumblebee)という種類のミツバチです。

今日も花の蜜を求めて異なる $ N $ 個の花を訪れました。

高橋君が $ i $ 番目に訪れた花の種類は $ A_i $ です。

$ i $ 番目の花は、$ i\ >\ j $ かつ $ i $ 番目の花の種類と $ j $ 番目の花の種類が同じになるような $ j $ が存在すれば受粉します。

高橋君が訪れた $ N $ 個の花の種類の情報が与えられるので、そのうちいくつの花が受粉したか求めてください。

なお、高橋君以外による受粉や自家受粉を考える必要はありません。

## 说明/提示

### Sample Explanation 1

$ 4 $ 番目と $ 5 $ 番目の花が受粉します。

## 样例 #1

### 输入

```
5
1
2
3
2
1```

### 输出

```
2```

## 样例 #2

### 输入

```
11
3
1
4
1
5
9
2
6
5
3
5```

### 输出

```
4```

# 题解

## 作者：ShineEternal (赞：15)

这题挺水的。。。
```
#include<bits/stdc++.h>//万能头
using namespace std;
long long a,c,ans;//保险起见
bool b[200000];//节省空间
int main()
{
	scanf("%lld",&a);
	while(a--)//while输入法
	{
		scanf("%lld",&c);
		if(b[c]==1)ans++;
		else b[c]=1;//判断的核心部分，有了就++,没有呢——这个就是
	}
	printf("%d\n",ans);//输出结果别忘换行
	return 0;
}
```

---

## 作者：ruler✘_梦 (赞：4)

这道题思路挺好想的

真不明白其他dalao为什么要用sort，桶排，甚至去重

这题按照思路来就可以了

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,a[100002],ans=0;//定义数组方便统计
int main(){
	cin>>n;
	int i;
	for(i=1;i<=n;i++){
		int x;
		cin>>x;//做题编号
		a[x]++;//做了几次
		if(a[x]>1) ans++;//如果超过一次就ans++
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

（于8.3修改）

### 思路

先排序，再统计。

归根结底就是去重。。

说到排序，个人认为用sort 更省事。

那么就是：
```cpp
sort(a+1,a+n+1);
```


因为现在$a$ 数组是有序的，那么只要循环$a_2$ 到$a_n$ ，如果$a_i=a_{i-1}$，则认为是“无用功”。

解释一下，因为排序之后第一次肯定不是“无用功”，所以循环变量$i$ 是从$2\sim n$。



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
    	cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++)
		if(a[i]==a[i-1])
        	ans++;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Coding的欢乐 (赞：2)

其实这题就是一个小小的去重
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans,b[100010];//定义好所需的变量,B数组是记录有没有重复
int main()
{
    cin>>n;//输入题目数量
    for(int i=1;i<=n;i++)
    {
    	cin>>a;//输入题号
    	if(b[a]!=0)ans++;//一旦是“无用功”，就计数器++
    	else
    	b[a]++;//否则B数组就记录下a
	}
    cout<<ans<<endl;//输出，别忘回车
	
	
    return 0;
}
```


---

## 作者：USACO_CHENWJ (赞：1)

这题本意就是去重  
~~挺水的...~~   
用用我小学时的做法:   
1.输入时先计数
```cpp
for(i=1;i<=n;i++)
{
   cin>>x;
   a[x]++;//数组计数
}
```    
2.如果计数数组内有大于等于二的，sum++   
```cpp
for(i=1;i<=n;i++)
{
   if(a[i]>=2)//就是说有重复的AC题，sum就++
    sum++;
} 
```    
3.输出 **(岛国题要换行)**    
总代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,i,j,a[100000],sum;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>x;
        a[x]++;
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]>=2)
          sum++;
    }
    cout<<sum<<endl;
}
```
望各位大佬指出错误，并私信，谢谢

---

## 作者：RioBlu (赞：1)

# 对于本题，有两种方法


------------

### 一号方案

N大，但是A数组的最大值小

#### 桶排，时间小，空间大

make by RioBlu
```
#include<bits/stdc++.h>
using namespace std;
long long a,c,ans;
bool b[200000];
int main()
{
	cin>>a;
	while(a--)
	{
		cin>>c;
		if(b[c]==1)ans++;//如果AC过，ans++
		else b[c]=1;//没有AC，标记一下
	}
	cout<<ans<<endl;
}
```


------------
### 二号方案

N小，但是A数组的最大值大，超出了long long或者是一个字符串

#### 快排，时间较大，空间较小

make by RioBlu里约布鲁
```
#include<bits/stdc++.h>
using namespace std;
long long a,b[100005],ans;//如果超过long long,请把b定义为string
int main()
{
	cin>>a; 
	for(int s=0;s<a;s++)
	{
		scanf("%lld",&b[s]);
	}
	sort(b,b+a);
	for(int s=1;s<a;s++)
	{
		if(b[s]==b[s-1])ans++;//和之前一个相同，ans++
	}
	cout<<ans<<endl;
}
```

---

## 作者：YZ_hang (赞：0)

## 类似桶排思想
这题我用的是易懂，简单的桶牌思想，算法非常简单

首先开一个桶b[100001]，用来计数每一个a[i]出现的次数，也就是这道题的AC次数

然后一个输入循环，把a[i]一个一个放进桶里，这种思路应该很容易想到吧

最后把b[i]逐个用ans计数就好了

~~说来说去也就是去重~~

然而我没用排序，所以比较暴力，代码看上去稍稍长一点
```
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[100001],b[100001],ans;//变量是什么意思我上面已经讲了
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[a[i]]++;//把a[i]放进桶里以计数
	}
	for(int i=1;i<=100000;i++)//注意这个100000也很重要，虽然很容易想到，但多定1也会影响结果
	if(b[i]>=2)ans+=b[i]-1;//如果a[i]这题出现了不止一次，就把次数加到ans里，但要扣除第一次AC
	printf("%d\n",ans);
	return 0; 
}
```


---

## 作者：Egg_eating_master (赞：0)

# STL大法好~

1.前言

这题用set不好吗？

set是STL中一个自动去重（其实还能排序，但对此题没用）的容器，用在此题简直简单得不能再简单了！

2.set中的函数
  
1）insert(x)：表示将元素x放进集合set中，并自动去重。

2）size()：返回集合set当中的元素数量。

3.代码（~~其实就这里有用~~）
```
#include<bits/stdc++.h>
using namespace std;
set<int>s;//定义一个元素类型为int的自动去重的容器
int n;
int x;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;//按题意输入
		s.insert(x);将x插入集合s并自动去重
	}
	cout<<n-s.size()<<endl;
    //由于有一对重复的数，元素个数就会减少1，
    //因此用应有个数减去现有个数就是减少的数量，
    //也就是最终的答案。
	return 0;//Happy ending~
}

---

