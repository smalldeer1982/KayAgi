# Tennis Rackets

## 题目描述

Professional sport is more than hard work. It also is the equipment, designed by top engineers. As an example, let's take tennis. Not only should you be in great shape, you also need an excellent racket! In this problem your task is to contribute to the development of tennis and to help to design a revolutionary new concept of a racket!

The concept is a triangular racket. Ant it should be not just any triangle, but a regular one. As soon as you've chosen the shape, you need to stretch the net. By the time you came the rocket had $ n $ holes drilled on each of its sides. The holes divide each side into equal $ n+1 $ parts. At that, the $ m $ closest to each apex holes on each side are made for better ventilation only and you cannot stretch the net through them. The next revolutionary idea as to stretch the net as obtuse triangles through the holes, so that for each triangle all apexes lay on different sides. Moreover, you need the net to be stretched along every possible obtuse triangle. That's where we need your help — help us to count the number of triangles the net is going to consist of.

Two triangles are considered to be different if their pictures on the fixed at some position racket are different.

## 说明/提示

For the following picture $ n=8 $ , $ m=2 $ . White circles are the holes for ventilation, red circles — holes for net stretching. One of the possible obtuse triangles is painted red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF309D/5d9eb90db15e7284257442b91590b3953ad87f5e.png)

## 样例 #1

### 输入

```
3 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 0
```

### 输出

```
24
```

## 样例 #3

### 输入

```
10 1
```

### 输出

```
210
```

## 样例 #4

### 输入

```
8 4
```

### 输出

```
0
```

# 题解

## 作者：听取MLE声一片 (赞：1)

因为一个钝角三角形只有一个钝角，所以可以枚举钝角的位置。

三条边本质相同，所以只需要跑一条边。

每条边上也有对称性，所以只需要跑前一半，特判一下中点。

判断钝角可以用余弦定理，钝角也就是其余弦值为负。

因为公式上分母必然为正，所以只需要判断分子的正负性。

已知三条边上点取的位置，就可以分别表示出三条边长度的平方，再乘一个系数就能在整数范围内判断。

这样就可以对于每个位置用指针找出对应为钝角的位置，求和即可。

时间复杂度为 $O(n^2)$。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,m,ans,k,a[N];
int F(int x){
	if(x<0)x=-x;
	return x*x;
}
int check(int a,int b,int c){
	int res=F(2*a-b)+3*F(b)+F(2*k-2*a-c)+3*F(c)-F(2*k-b-c)-3*F(b-c);
	if(res<0)return 1;
	return 0;
}
signed main()
{
	for(int i=0;i<N;i++)a[i]=i*i;
	n=read(),m=read();
	k=n+1;
	for(int i=m+1;i<=n-m;i++){
		if(2*i>n+1)break;
		int p=n-m,s=0;
		for(int j=m+1;j<=n-m;j++){
			while(!check(i,j,p)&&p>=m+1)p--;
			s+=p-m;
		}
		if(2*i==n+1)ans+=s;
		else ans+=2*s;
	}
	ans*=3;
	cout<<ans;
	return 0;
}

```

---

