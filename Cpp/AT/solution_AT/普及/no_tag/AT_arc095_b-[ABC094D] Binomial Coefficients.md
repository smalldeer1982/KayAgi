# [ABC094D] Binomial Coefficients

## 题目描述

从 $n$ 个物品中不考虑顺序地选出 $r$ 个的情况数记为 ${\rm comb}(n, r)$。请从 $n$ 个非负整数 $a _ 1, a _ 2, \ldots, a _ n$ 中选择 $2$ 个数 $a _ i > a _ j$，使得 ${\rm comb}(a _ i, a _ j)$ 最大化。如果有多个组合可以达到最大值，可以选择任意一个。

## 样例 #1

### 输入

```
5
6 9 4 2 11```

### 输出

```
11 6```

## 样例 #2

### 输入

```
2
100 0```

### 输出

```
100 0```

# 题解

## 作者：_Weslie_ (赞：2)

## [洛谷：题目传送门](https://www.luogu.com.cn/problem/AT_arc095_b)

## [AT：题目传送门](https://atcoder.jp/contests/arc095/tasks/arc095_b)

## 思路

众所周知，$C_m^n=\dfrac{m!}{n!(m-n)!}$

通过找规律，发现对于数列中的数，最大的数作为 $m$，最接近 $\frac{m}{2}$ 的数作为 $n$ 时 $C_m^n$ 最大。

## 代码实现

$\texttt{sort}$ 一下，然后枚举找出最接近 $\frac{m}{2}$ 的数。

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[100001],n,t;
double minn=2147000000,mid;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	mid=a[n]*1.0/2;
	for(int i=1;i<=n;i++){
		if(a[i]<mid){
			if(mid-a[i]<minn){
				t=a[i];
				minn=mid-a[i];
			}
		}
		else{
			if(a[i]-mid<minn){
				t=a[i];
				minn=a[i]-mid;
			}
		}
	}
	cout<<a[n]<<' '<<t;
	return 0;
}
```

提示：如果洛谷交不上去可以尝试去原网站提交。

---

## 作者：dthythxth_Huge_Brain (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_arc095_b)


------------

## 题目分析

由于 $C_{x}^y=\frac{A_{x}^y}{y!}=\frac{n!}{y!(n-m)!}$，而且 $C_{x}^y=C_{x}^{x-y}$，所以当 $x$ 最大时，并且 $y$ 尽可能接近 $x/2$ 时， $C^{y}_{x}$ 就是最大值。

------------


## 参考题解:
```
def main():
    # 输入一个整数n
    n = int(input())
    # 输入一个包含n个整数的列表
    f = list(map(int, input().split()))
    # 对列表f进行排序
    f.sort()

    # x是列表中的最大数
    x = f[-1]

    # y是尽可能接近x/2的数，但必须满足y<=x
    y = min(f, key=lambda num: abs(num - x / 2))

    print(x, y)

# 调用主函数
if __name__ == "__main__":
    main()
```


---

## 作者：lemon_qwq (赞：1)

我们知道组合数 $\tbinom{n}{m}$ 表示杨辉三角形第 $n$ 行第 $m$ 列的数。

根据杨辉三角形的性质，越靠近中间的数越大，所以让 $m=\lfloor\frac{n}{2}\rfloor$ 即可。

---

## 作者：Milthm (赞：0)

## AT_arc095_b 题解

### 前置知识

- 数学

### 题目解法

首先，在 $y$ 相等，$x>y$ 的情况下，$x$ 尽量要往大里取，才能使 $C_x^y$ 最大（你从 $50$ 个里选 $3$ 个肯定比从 $5$ 个里选 $3$ 个方案多）。所以 $x$ 即为序列的最大值。

然后，因为 $C_n^m=C_n^{n-m}$，所以在 $x$ 相等的情况下，最接近 $\frac{x}{2}$ 的 $y$ 能使组合数最大。

然后本题就结束了。

### AC 代码

题解区怎么一堆 $O(n \log n)$，这个东西明明可以 $O(n)$ 做。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,a[100005],maxn=-1,ans;
double qwq=2e9;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		maxn=max(maxn,a[i]);//最大值
	}
	double mid=maxn/2.0;//最大值的一半
	for(int i=1;i<=n;++i){
		if(a[i]!=maxn&&abs(a[i]-mid)<qwq){//记得特判 a[i]!=maxn
			ans=a[i];//更新答案
			qwq=abs(a[i]-mid);
		}
	}
	cout<<maxn<<" "<<ans;
	return 0;
}

```





---

## 作者：Crasole (赞：0)

## 题意

给你一个长度为 $n$ 的序列 $a_1 , a_2 , a_3 , ... , a_n$，从中选出两个数，使得 $C_{x} ^ {y}$ 最大。

## 思路

$C_{x} ^ {y}$ 是组合数数的意思。也就等于：
$$
\frac{n!}{m!(n - m)!}
$$
同时，$C_{x} ^ {y} = C_{x} ^ {x-y}$，所以，只有 $y$ 为 $x$ 的 $\frac{1}{2}$ 时，$C_{x} ^ {y}$ 是最大的。

所以，我们的 $x$ 可以取 $a$ 数组中最大的，$y$ 取与 $x$ 的 $\frac{1}{2}$ 最近的数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);//排序
	int t=0,minn=0x7fffffff;
	for(int i=1;i<=n;i++){
		int vl=abs(a[i]*2-a[n]);//a[i]-a[n]/2 = a[i]*2-a[n]
		if(vl<minn)//更新最小值
			minn=vl,t=a[i];//记录当前的最接近值
	}
	cout<<a[n]<<' '<<t<<endl;
	return 0;
}
```

---

## 作者：asas111 (赞：0)

## 思路
当 $x$ 为序列中最大值，且 $y$ 为序列中最接近 $\frac{x}{2}$ 的值时 $C_{x}^{y}$ 最大。

证明：显然 $C_{x-1}^{y}<C_{x}^{y}$，所以 $x$ 越大，$C_{x}^{y}$ 越大。

对 $y$ 进行分类讨论：

- 当 $y\le\lfloor\frac{x}{2}\rfloor$ 时，因为 $C_{x}^{y}=C_{x-1}^{y}+C_{x-1}^{y-1}$，所以当 $y=\lfloor\frac{x}{2}\rfloor$ 时，$C_{x}^{y}$ 最大。

- 当 $y\geq\lceil\frac{x}{2}\rceil$ 时,由于 $C_{x}^{y}=C_{x}^{x-y}$，所以令 $z=x-y$，就和上面的情况一样，$z=\lfloor\frac{x}{2}\rfloor$ 时，$C_{x}^{z}$ 最大，此时 $y=\lceil\frac{x}{2}\rceil$。

序列中不一定会有 $\frac{x}{2}$ 这样的数，所以只需要在序列中找到最接近 $\frac{x}{2}$ 的值就可以了。

时间复杂度 $O(n\log n)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100009];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	int x=a[n],y=0,mi=0x3f3f3f3f;
	for(int i=1;i<=n;i++){//找中位数
		int f=abs(2*a[i]-x);//x/2可能是浮点数，所以就把差乘以2
		if(f<mi)mi=f,y=a[i];
	}
	cout<<x<<" "<<y;
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

$\tt{ARC 095B}$

$(^y_x)=\frac{y!}{x!(y-x)!}$

所以我们先让 $y$ 最大，然后找一个 $x$ 接近 $\frac{y}{2}$ 就好了。

我们先对整个序列排序，然后选定 $y$ 为最大的一个。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
int n,f[100005],x;
int solve(int x,int y){return std::max(x-y,y-x);}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]);
	std::sort(f+1,f+n+1);
	x=1;
	for (int i=1;i<=n;i++)
	    if (solve(f[i]*2,f[n])<solve(f[x]*2,f[n])) x=i;
	printf("%d %d\n",f[n],f[x]);
	return 0;
}
```

---

