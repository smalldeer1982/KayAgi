# Effective Approach

## 题目描述

Once at a team training Vasya, Petya and Sasha got a problem on implementing linear search in an array.

According to the boys, linear search works as follows. The array elements in a pre-selected order are in turn compared with the number that you need to find. Once you find the array element that is equal to the required one, the search ends. The efficiency of the algorithm is the number of performed comparisons. The fewer comparisons the linear search has made, the more effective it is.

Vasya believes that a linear search would work better if it sequentially iterates through the elements, starting with the $ 1 $ -st one (in this problem we consider the elements of the array indexed from $ 1 $ to $ n $ ) and ending with the $ n $ -th one. And Petya says that Vasya is wrong: the search will need less comparisons if it sequentially iterates the elements starting from the $ n $ -th and ending with the $ 1 $ -st one. Sasha argues that the two approaches are equivalent.

To finally begin the task, the teammates decided to settle the debate and compare the two approaches on an example. For this, they took an array that is a permutation of integers from $ 1 $ to $ n $ , and generated $ m $ queries of the form: find element with value $ b_{i} $ in the array. They want to calculate for both approaches how many comparisons in total the linear search will need to respond to all queries. If the first search needs fewer comparisons, then the winner of the dispute is Vasya. If the second one does, then the winner is Petya. If both approaches make the same number of comparisons, then Sasha's got the upper hand.

But the problem is, linear search is too slow. That's why the boys aren't going to find out who is right before the end of the training, unless you come in here. Help them to determine who will win the dispute.

## 说明/提示

In the first sample Vasya's approach will make one comparison (it starts with the $ 1 $ -st element and immediately finds the required number), and Petya's approach makes two comparisons (first he compares with the $ 2 $ -nd array element, doesn't find the search item and compares with the $ 1 $ -st element).

In the second sample, on the contrary, Vasya's approach will need two comparisons (first with $ 1 $ -st element, and then with the $ 2 $ -nd), and Petya's approach will find the required value in one comparison (the first comparison with the $ 2 $ -nd element).

## 样例 #1

### 输入

```
2
1 2
1
1
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
2
2 1
1
1
```

### 输出

```
2 1
```

## 样例 #3

### 输入

```
3
3 1 2
3
1 2 3
```

### 输出

```
6 6
```

# 题解

## 作者：123456zmy (赞：1)

题意：  
给你 $n$ 个数，有 $m$ 次查询，问顺序查找和逆序查找需要的比较次数。
___
~~题目里面都说了是T掉才来问你的所以暴力肯定过不了。~~

既然暴力过不了就用 STL。要在一堆数里面找到一个，可以想到用 map 建立一个值到序号的对应关系，然后知道序号就可以求出顺序查找和逆序查找的次数，加入答案最后输出。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b;
long long ans1,ans2;
map<int,int>a;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b);
		a[b]=i;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b);
		ans1+=a[b];
		ans2+=n-a[b]+1;
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}
```

---

## 作者：_lzy_ (赞：0)

## 题目大意:
给出你 $n$ 个数，再给你 $m$ 次询问。要你求出 $m$ 次讯问中每次询问的数在这 $n$ 个数中的顺序查找次数与逆序查找次数之和。
## 解题思路：
用一个桶来存储 $n$ 次输入中每次输入的数，最后在 $m$ 次询问中就可以直接求出顺序查找次数与逆序查找次数，最后再输出和就行了。
## 代码：
```cpp
#include<bits/stdc++.h>
#define N 100001
#define ll long long
using namespace std;
int n,m;
int flag[N];
ll ans1=0,ans2=0;
void clear(){
	for(int i=1;i<=n;i++)flag[i]=0;
}
int main()
{
	ios::sync_with_stdio(false);
	int x;
	cin>>n;
	clear();//数组初始化。
	for(int i=1;i<=n;i++){
		cin>>x;
		flag[x]=i;//将输入的数存在桶里面。
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>x;
		ans1+=flag[x];//求顺序查找次数与逆序查找次数。
		ans2+=n-flag[x]+1;
	}
	cout<<ans1<<" "<<ans2;
	return 0; 
} 
```


---

## 作者：zwy__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF227B)
### 题意
给出 $n$ 个数，然后有 $m$ 个询问，每个询问让你找出的是顺序查找这个数和逆序查找这个数的次数，最后让你输出两种查找的总次数。
### 思路
这题范围比较大，我们可以用数组计数。不过，值得注意的是，题目说数据有可能重复，所以，我们要用两个数组来存不同数的位置，在用两个变量分别存不同查找方式总共的次数。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a,s1,s2;
int b[100005],c[100005];
int main()
{
	cin>>n;
	fill(b+1,b+1+100000,2100000000);//赋初值，fill是一个比memset更厉害的函数
	fill(c+1,c+1+100000,-2100000000);
	for(int i=1; i<=n; i++)
	{
		cin>>a;
		b[a]=min(i,b[a]);
		c[a]=max(i,c[a]);
	}
	cin>>m;
	for(int i=1; i<=m; i++)
	{
		cin>>a;
		s1+=b[a];
		s2+=n-c[a]+1;
	}
	cout<<s1<<" "<<s2;
	return 0;
}
```


---

