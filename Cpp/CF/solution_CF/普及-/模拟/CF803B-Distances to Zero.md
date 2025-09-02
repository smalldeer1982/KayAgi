# Distances to Zero

## 题目描述

You are given the array of integer numbers $ a_{0},a_{1},...,a_{n-1} $ . For each element find the distance to the nearest zero (to the element which equals to zero). There is at least one zero element in the given array.

## 样例 #1

### 输入

```
9
2 1 0 3 0 0 3 2 4
```

### 输出

```
2 1 0 1 0 0 1 2 3 ```

## 样例 #2

### 输入

```
5
0 1 2 3 4
```

### 输出

```
0 1 2 3 4 ```

## 样例 #3

### 输入

```
7
5 6 0 1 -2 3 4
```

### 输出

```
2 1 0 1 2 3 4 ```

# 题解

## 作者：tryrtj (赞：2)

第一眼看到数据，n^2时间复杂度承担不起啊，然后冷静下来想了一下，好像只有左右两个方向，那两边枚举好像就行了，代码如下

```
#include<iostream>
#include<algorithm>//min函数要用
using namespace std;
int a[200005],b[200005];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];//读入
		b[i]=0x7fffffff;//初始为无穷大
	}
	int q=-1;
	for(int i=0;i<n;i++){
		if(a[i]==0){
			q=i;//找左边最近的点
		}
		if(q!=-1)b[i]=i-q;//赋值
	}
	q=-1;
	for(int i=n-1;i>=0;i--){
		if(a[i]==0){
			q=i;//找右边最近的点
		}
		if(q!=-1){
			b[i]=min(b[i],q-i);//赋值
		}
	}
	for(int i=0;i<n;i++){
		cout<<b[i]<<' ';//输出
	}
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的序列 $a_1,a_2,a_3,...,a_n$，求每个数与它最近的 $0$ 的距离（$0$ 的距离为 $0$）。

**数据范围：$1\leqslant n\leqslant 2\times 10^5,-10^9\leqslant a_i\leqslant 10^9$。**
## Solution
距离的方向要么往左，要么往右，所以我们先往右遍历，再往左遍历，一边再更新 $0$ 出现的位置和位置 $i$ 到最近的 $0$ 的距离。
## Code
#### 声明：今后放代码只放主体代码。
```cpp
int n, a[200007], ans[200007], tmp;

int main() {
	memset(ans, 0x3f, sizeof(ans));
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	_for(i, 1, n) {
		if(!a[i])	ans[i] = 0, tmp = i;
		else if(tmp)	ans[i] = min(ans[i], i - tmp);
	}
	int flag = 0;
	_rep(i, n, 1) {
		if(!a[i])	ans[i] = 0, tmp = i, flag = 1;
		else if(flag)	ans[i] = min(ans[i], tmp - i);
	}
	_for(i, 1, n)	writeint(ans[i]), putchar(' ');
	return 0;
}
```

---

## 作者：KazamiHina (赞：0)

这题让我们求的是每个数字到$0$的距离，所以我们可以枚举找$0$，然后通过这个$0$进行扩展

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int ans[2000005];
int n,a[2000005];

void R(int & x){
	x=0;char ch=getchar();
	while((ch<'0') || (ch>'9'))ch=getchar();
	while((ch>='0') && (ch<='9')){
		x=(x*10)+(ch-'0');
		ch=getchar();
	}
}

int main(){
	R(n);
	for(int i=1;i<=n;i++)R(a[i]),ans[i]=123456789;//ans数组要初始化很大
	for(int i=1;i<=n;i++){
		if(a[i]==0){//找0
			for(int l=i-1;;l--){//向左扩展
				if(a[l]==0)break;//如果左边已经是0了，那么就没必要向左扩展了
				ans[l]=min(ans[l],i-l);//更新到0的距离
			}
			for(int r=i+1;;r++){//向右扩展
				if(a[r]==0)break;
				ans[r]=min(ans[r],r-i);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",(ans[i]==123456789?0:ans[i]));//如果这个数的距离没有被更新，那么它就是0
	return 0;
}
```

$qwq$

---

## 作者：q_sum (赞：0)

这是本蒟蒻用快读（因为数据量较大，将近了$2$*$10^5$）写的第一篇题解，不喜勿喷。

这道题思路很简单，主要就是用两个数组$l$和$r$,$l$存放的是离$i$点位最近的左边的$0$的位置，$r$存放的是离$i$点位最近的右边的$0$的位置，然后再循环一遍，求对于每个$i$，判断左边的$0$近还是右边的$0$近。

下面，放代码吧（文中留了两处$?$号，后文有解析，供读者理解）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001],l[200001],r[200001];
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);//这里是快读，注意用位运算速度会更快
        ch=getchar();
    }
    return x*f;
}
int main()
{
	memset(l,127,sizeof(l));
	memset(r,127,sizeof(r));//首先得赋成最大值，今天我来教大家一种新的写法，数字127虽然没有INT_MAX大，但是接近INT_MAX
	n=read();
	for (int i=1;i<=n;++i)
	   a[i]=read();//使用快读
	for (int i=1;i<=n;++i)
	{
	   int j=?;
	   if(a[i]==0)
	   	l[0]=i;//判断当前的数是否为0，如果是，那么将l[0]替换成当前数的下标
	   if(a[?]==0)
	   	r[0]=j;
	   l[i]=l[0];
	   r[j]=r[0];
	}
	for (int i=1;i<=n;++i)
		cout<<min(abs(i-l[i]),abs(i-r[i]))<<' ';//输出，判断，左边的$0$近还是右边的$0$近，这里用了min函数
	return 0;
}
```




是时候揭晓答案了：
- $1$.$n-i+1$
- $2$.$j$

布吉岛大家有没有理解了呢?赶紧$A$了这道题吧！

---

## 作者：jzh817 (赞：0)

题目要求每个数到0的距离，很容易想到可以从前往后，从后往前分别搜索每个数与它之前的0和之后的0的距离，最后再取一个min就行了

用b数组存储答案，x表示当前位置的最小值，x碰到0就变成0，否则+1

注意！b数组和x都要初始化为0，尤其是x！

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
int n,x=1e9,a[200005],b[200005];
int main(){
	memset(b,0x3f,sizeof(b));
	n=read();
	for(int i=0;i<n;i++)
		a[i]=read();
	for(int i=0;i<n;i++){
		if(a[i]==0)x=0;
		b[i]=x,x++;
	}
	x=1e9;
	for(int i=n-1;i>=0;i--){
		if(a[i]==0)x=0;
		b[i]=min(x,b[i]),x++;
	}
	for(int i=0;i<n;i++)
		printf("%d ",b[i]);
	return 0;
}
```

---

