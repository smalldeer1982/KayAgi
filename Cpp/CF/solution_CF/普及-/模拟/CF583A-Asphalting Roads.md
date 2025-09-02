# Asphalting Roads

## 题目描述

有一个边长为$n$的正方形的城市，一个小组要在这个城市的路上铺上柏油路。一共要进行$n^2$天，小组第$i$天要铺两条道路$h_i$和$v_i$。如果当天要铺的两条路道路都没被铺过则将这两条道路铺上柏油路，否则则什么都不干。根据施工的时间表，告诉这条道路将在哪几天里被铺上柏油路。

## 样例 #1

### 输入

```
2
1 1
1 2
2 1
2 2
```

### 输出

```
1 4 
```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
1 
```

# 题解

## 作者：䒛夢 (赞：2)

 **䒛夢又来水题解了**
#  先是题意
有 $n\times n$ 天，每天两个条道路，只要有一条道路已经修过了，那这一天就可以偷懒啦！
# 思路
既然只有每一条路都没有修过你才不会偷懒，所以直接判断你是不是要修路
# 附上代码
```
#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool hh[55],vv[55];//留着用作记录道路走过吗
int main()
{
	scanf("%d",&n);
	for(int i=1 ; i<=n*n ; ++i)//记住是$n*n$天
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(hh[a]==0&&vv[b]==0)如果都没走过就输出加标记
		{
			hh[a]=1;
			vv[b]=1;
			printf("%d ",i);
		}
	}
	return 0;
}
```

---

## 作者：smyslenny (赞：1)

**Description**：
> 给出两个数 $a$，$b$，如果这两个数都没在各自的集合里出现过，输出当前天数，并且放入集合，否则不做任何处理。


**Solution**

做法都写在题目里了，我们开两个数组，利用桶排序的思想，相当于开两个桶，$tong_i$ 表示 $i$ 这个数是否出现过，如果两个数都没出现过，输出当前天数，标记已经出现过，否则，就不要乱动了，题目中说了，啥也不用干。我们发现 $1\leq n\leq 50$，这么小的数据，完全不用担心数组会炸，放心的用就可以啦。在读入的时候就可以处理完了。

**Code**

```c++
#include<bits/stdc++.h> 
using namespace std;
const int M=1e3+5;
int n,mp_1[M],mp_2[M]; 
int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<=n*n;i++)
	{
		scanf("%d%d",&a,&b);
		if( !mp_1[a] && !mp_2[b]) mp_1[a]=1,mp_2[b]=1,printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

题目传送>>[CF583A](https://www.luogu.com.cn/problem/CF583A)  
### 题意简述:  
- 一城市道路铺设柏油，工期为 $n^2$ 天（给定 $n$），第 $i$ 天待铺设的两条道路为 $h_i$ 和 $v_i$，如当天的 $h_i$ 和 $v_i$ 都未被铺则施工，否则休假。求所施工当天天次。  
- $1\le n \le50$，$1\le h_i,v_i \le n$。  

### 题目分析:  
此题可直接根据题意模拟，开两个数组标记道路 $h_i$ 和 $v_i$ 的情况，起初将所有道路都初始化为未铺设，然后对每天待铺的 $h_i$ 和 $v_i$ 进行判断是否已铺，如都未被铺则施工（一定要注意是两条道路都未被铺），输出该天天次，同时转变标记当前道路为已铺，否则则休假。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int h[51]={0},v[51]={0};   //开数组标记两道路铺设状态，并初始化为0表示为未铺
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);      //加速cin输入和cout输出
	int n;   //定义正方形城市边长，即工期的算术平方根
	int t,hi,vi;   //定义工期，第i天待铺的hi和vi道路
	cin>>n;
	t=n*n;
	for(int i=1;i<=t;i++)
	{
		cin>>hi>>vi;
		if(!h[hi]&&!v[vi])   //第i天待铺的hi和vi道路都未被铺
		{
			cout<<i<<" ";   //输出铺路当天天次
			h[hi]=1,v[vi]=1;   //转换标记为已铺
		}
	}
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/wcctn54k.png)  
企鹅的题解到此结束，祝各位 OIers 进步++~

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15174487.html)

## 题意

给定 $n$,$n^2$ 为上级规定的工期，每条路有两条路等待修建，请你划定一个施工方案。

## 分析

发现 $n$ 的范围并不大，所以我们开两个桶记录是否被修建，如果修建过了，那么跳过；否则就铺路。

我们完全可以一边读入一边输出，因为其顺序未改变，可以跑到最优解 $\rm NO.2$。

```cpp
//2021/8/23

#include <iostream>

#include <cstdio>

#define debug(c) cerr<<#c<<" = "<<c<<endl

namespace Newstd
{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')f=-1;
			ch=getchar();
		}

		while(ch>='0' && ch<='9')
		{
			x=x*10+ch-'0';ch=getchar();
		}
		return x*f;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=55;

bool h[ma],v[ma];

int main(void)
{
	int n;
	
	scanf("%d",&n);
	
	for(register int i=1;i<=n*n;i++)
	{
		int H,V;
		
		scanf("%d%d",&H,&V);
		
		if(h[H]==false && v[V]==false)
		{
			printf("%d ",i);//如果没有修建就开始铺 
			
			h[H]=true;//标记 
			
			v[V]=true;//标记 
		}
	}
	
	return 0;
} 

```

---

## 作者：sysu_yzc (赞：0)

## 思路
开两个bool数组表示道路是否已经铺设，然后暴力模拟即可。
## 代码
```cpp
#include<iostream>
#define maxn 60
using namespace std;
bool A[maxn],B[maxn];
int main(){
	int n;
	cin>>n;
	n=n*n;
	int a,b;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(!A[a]&&!B[b]){
			cout<<i<<" ";
			A[a]=1;
			B[b]=1;
		}
	}
	return 0;
}
```

---

