# Hamster Farm

## 题目描述

Dima有$n$ 只仓鼠，有$k$ 种盒子，每种盒子编号为1~k，可以装$a_i$ 只仓鼠，所有盒子都要装满仓鼠，剩下的仓鼠不装，Dima想让剩下的仓鼠最少，求应选盒子和盒子总数，如果有多种情况，输出任意一种。

## 样例 #1

### 输入

```
19 3
5 4 10
```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
28 3
5 6 30
```

### 输出

```
1 5
```

# 题解

## 作者：Thomas_Cat (赞：4)

### 挑战本篇最短代码。

这道题我们的思路是：

- 输入
- 在输入的时候计算这个盒子如果装仓鼠的话会留下多少（剩下）
- 然后在下一次输入之前看一下这一次是否是最小，如果是，替换，否则，相反
- 输出最后答案

> 注意：这道题目CF~~很毒瘤~~，ta设置了很长的数据，这里判断的时候，应该先把MIN设为 $10^{18}$（这里用 `pow()` 函数完成任务，注意这里有单独的头文件，但这里用万能头文件替代），然后所有的定义建议使用 `unsigned long long` 否则会挂。

代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//using不多说
int main(){
	unsigned long long n,k,MIN=pow(10,18),code,number,a;
    /*
    n,k不多说
    MIN：这里说过，要设最大值，数据很毒瘤
    code：代表盒子的编码
    number：表示需要盒子的数量
    a：每次输入的数据
    */
	cin>>n>>k;//输入
	for(unsigned long long i=1;i<=k;i++){//这里最好大一点
    	cin>>a;
    	if(n%a<MIN)//判断
			MIN=n%a,code=i,number=n/a;//如果小，替换
	}
	cout<<code<<' '<<number;//输出答案
	return 0;//华丽结束
}

```

## 管理大大求过qaq

---

## 作者：OdtreePrince (赞：3)

# -纯模拟-

求min值是简单的，要想所剩最少，很显然就是——

$\color{blue}\texttt{余数最小。}$

那么问题就迎刃而解了，上代码。

~~~
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,a,b;
int main(){
    ll minn=1000000000000000001,num,l;
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=k;i++){
        scanf("%lld",&a);
        b=n%a;
        if(b<minn){
			num=i;
            l=n/a;
            minn=b;
        }
    }
    cout<<num<<' '<<l;
    return 0;
}~~~

---

## 作者：Pkixzx (赞：1)

模拟大法好！

我们每次输入一个数，判断这个数剩下的仓鼠数和要的笼子数，最后输出这些数中剩下的仓鼠数**最少**的就可以了。

但是，这道题有一个坑点，就是数据非常大，所以，统计最小数的这个数要开到**10的18次方**。

明白坑点后，代码就好写了：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m,i,j,k,t=1000000000000000010,t1=0,t2=0;
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		cin>>k;
		if(n%k<t)
		{
			t1=n/k;//求盒子个数
			t2=i;//求盒子的编号
			t=n%k;
		}
	}
	cout<<t2<<" "<<t1;
}
```


---

## 作者：洛谷亿亿岁 (赞：1)

注释详见代码

```
#include<iostream>
using namespace std;
long long now,a,b,k,minn=1000000000000000001,minm=1000000000000000001,minans=1000000000000000001; //now用来计算当前的余数，b,k和a是根据题意来的，minn,minm,minans分别存储最小的余数时的编号，数量和余数值
int main(){
	cin>>b>>k;//输入
	for(long long i=1;i<=k;i++){//共有k个循环
		cin>>a;//输入
		now=b%a;//计算余数
		if(now<minans)//如果余数比当前答案的余数小
		minm=i,minn=b/a,minans=now;//交换
	}
	cout<<minm<<" "<<minn;//输出答案
}
    
```


---

## 作者：yizimi远欣 (赞：1)

### 题目分析
实质上就是求余数，找到n mod a[i] 的最小值，然后把 i 与 n/a[i] 输出。就是一道纯粹的模拟题，不过因为翻译，要注意隐隐约约有10e18的数据范围，一定要小心，用long long才行（一开始吓得我想用高精~~（雾）~~）。

### 主要思路

枚举出每一个 a[i] 然后让 n mod a[i] ，去找最小值。

### 代码实现

#### 第一种方法：（有点像楼上dalao的）

PS：这个可以被优化为第二种方法

时间复杂度O(k),空间复杂度O(k);

```
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long    
//long long打起来有点费劲（偷懒
#define mn 100010
#define go(i,j,n,k) for(register ll i=j;i<=n;i+=k)//循环偷懒
inline ll read(){//读入优化
	ll x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const ll inf=9223372036854775807;//初始化最小值用的
ll n,k,a[mn],mi,mii;//n 仓鼠的总数 k 笼子种数 
//a[]记录所有笼子可装仓鼠的只数 mi 记录最佳的笼子剩余的只数
//mii 记录最佳笼子的编号
int main(){
	n=read();k=read();
	go(i,1,k,1){
		a[i]=read();
	}//读入
	mi=inf;//初始化最小值（最佳）
	go(i,1,k,1){
		if(n%a[i]<mi){//更新最佳笼子
        	mii=i;
			mi=n%a[i];
		}
	}
	cout<<mii<<" "<<n/a[mii];//输出最佳笼子编号与所需的笼子个数
	return 0;
}
```

#### 第二种方法：（简单的优化）

（理论）

时间复杂度：O(k) 空间复杂度：O(1);

重复的就不多讲了，以下主要讲优化

```
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define mn 100010
#define go(i,j,n,k) for(register ll i=j;i<=n;i+=k)
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const ll inf=9223372036854775807;
ll n,k,a,m,mi,mii;//a 变为了单个的变量 m 记录当前最佳笼子的a的值
int main(){
	n=read();k=read();
	mi=inf;
	go(i,1,k,1){//变为一个循环
		a=read();//读入不变
		if(n%a<mi){//读入后直接判断
			mi=n%a;
			m=a;//记录下来最佳（否则就会被覆盖掉）
			mii=i;
		}
	}
	cout<<mii<<" "<<n/m;//n/m则为笼子个数
	return 0;
}
```

#### 后记

不知为什么优化后占用内存还会这么多，，，

第二次发题解请大佬多多指教，，，


---

