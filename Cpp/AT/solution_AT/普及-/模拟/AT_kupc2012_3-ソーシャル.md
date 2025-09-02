# ソーシャル

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2012/tasks/kupc2012_3



# 题解

## 作者：POYE (赞：4)

# Part 1 Preparation
先用一个 $a$ 数组，$a[i]$ 表示 $i$ 所属的集合，和一个 $t$ 数组，用于记录一个数有没有被计算过，再用一个变量 $ans$ 统计最后答案即可。

# Part 2 Solution
第一轮输入时，第 $i$ 行即为第 $i$ 个集合，所以后面输入的数的 $a$ 值都赋为 $i$。第二轮输入时，就判断 $x$ 与 $y$ 是否属于同一集合，若属于，且没被统计过，则累加，并打上标签，表示已统计过。

# Part 3 Code
```cpp
#include<iostream>
using namespace std;
int n,k,r,ans,a[55];
bool t[55];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		int num;
		cin>>num;
		for(int j=1;j<=num;j++)
		{
			int x;
			cin>>x;
			a[x]=i;//数x属于集合i
		}
	}
	cin>>r;
	for(int i=1;i<=r;i++)
	{
		int x,y;
		cin>>x>>y;
		if(a[x]==a[y])//判断是否在同一集合
		{
			if(!t[x]) ans++;//没被标记过才了累加
			if(!t[y]) ans++; 
			t[x]=t[y]=1;//将已统计过的x与y都打上标记
		}
	}
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：cff_0102 (赞：2)

#### C++题解。

[我们先看题面](https://www.luogu.com.cn/problem/AT198)。

看完之后发现这道题很水。

1. 我们可以存下每一个数字所在的集合。

1. 因为翻译中说 “在 $x$ **所属的集合内**至少有一个其它的数与其相关” ，所以我们要在输入有联系的数时进行比较，看他们是否在同一集合。

1. 如果是，那么给用来标记的数组打上标记。如果这个数已经被标记过，答案就不需要再加 $1$ 。

那么代码就出来了。注意可以对照理解，不要抄袭。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55];//每个数所属集合 
bool f[55];//标记数组 
int main(){
	ios::sync_with_stdio(false);//这是用来给cin/cout加速的 
	int n,k,r/*题目中的变量*/,cnt=0/*最后的答案*/;cin>>n>>k;//数据范围还是挺小的
	for(int i=0;i<k;i++){//输入数集 
		int m;cin>>m;
		for(int j=0;j<m;j++){
			int t;cin>>t//临时存储第i个集合里的第j个数;
			a[t]=i;//存储t所属的集合 
		}
	}
	cin>>r;//嫑忘了r是在这里输入
	for(int i=0;i<r;i++){
		int x1,x2;cin>>x1>>x2;//题中说的数x，用来临时输入有联系的2个数 
		if(a[x1]==a[x2])/*在同一个集合内*/{
			if(!f[x1]){//x1还没被标记
				f[x1]=1,cnt++;//x1也满足题目的条件 
			}if(!f[x2]){
				f[x2]=1,cnt++;//同理 
			}
		}
	}
	cout<<cnt;//不要忘了输出
	cout<<endl;//这一行单独说，AtCoder的题一定要输出换行！ 
	return 0;
}/*
```
这道题也不会用到什么公式，望管理能过。

---

## 作者：atarashiTLE (赞：1)

### 思路：
因为题目说了读入的都是有关系的，所以我们可以存储每个数所在的数集，最后在输入时判断是否为同一数集且去重即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std; 
bool c[51];
int n,k,l,s,tmpp,tmp,st[51];
int main(){
	int n;
	cin>>n>>k;
	for(int i=0;i<k;i++){
		cin>>l;
		for(int j=0;j<l;j++){
			cin>>tmpp;
			st[tmpp]=i+1;
		}
	}
	cin>>k;
	for(int i=0;i<k;i++){
		cin>>tmp>>tmpp;
		if(st[tmp]==st[tmpp]){
			if(!c[tmp])
				s++;
			if(!c[tmpp])
				s++;
				c[tmp]=c[tmpp]=true;
		}
	}
	cout<<s<<endl;
	return 0;
}```

---

## 作者：FwbAway (赞：0)

我们把每次输入的集都存在数组里，然后用桶思想把 $a[t]=1$，最后输出的时候也不用在去判断去重了。

注意：我们在输出的时候答案就是标记的那个数字。

也可以这样：因为题目已经说了读入的都是有关联的，所以直接判断是不是在同一数集内。如果是的话，输出就行了。



---

## 作者：Nygglatho (赞：0)

我们可以把每一个数集里所有元素标上**相同的**标记（但是不同数集元素应该**不同**）。

一种比较好理解的办法是把第 $i$ 个数集所有元素标记为 $i$。这样，就可以区分数集了。

```cpp
for (int i = 1; i <= k; i++) {
	int x, q;
	scanf ("%d", &q);
	for (int j = 1; j <= q; j++) {
		scanf ("%d", &x);
		set[x] = i;
	}
}
```
接下来，就可以直接读入 $x$ 与 $y$，因为题目说了读入的都是有关系的，所以可以直接判断是不是在同一数集内。

那么，$x$ 也有至少一个满足条件的另一个数据，$y$ 也是，可以直接把它们在一个数组里标记上去，最终答案即为标记了的个数。
```cpp
for (int i = 1; i <= r; i++) {
	int x, y;
	scanf ("%d%d", &x, &y);
	if (set[x] == set[y]) {
		tf[x] = true;
		tf[y] = true;
	}
}
```
注意，不能直接用 $s$ 加上去，因为可能会有重复。 

---

