# Equalize Them All

## 题目描述

你被给了一个 _n_ 个元素的数组 _a_ ,对于一对（i,j）其满足|i-j|=1（即表示i,j相邻）,你现在有两种操作方式：


**1**操作：将a[i]变为a[i] + | a[i]-a[j] |


**2**操作：将a[i]变为a[i] - | a[i]-a[j] |


（其中 | a[i]-a[j] | 表示a[i]-a[j]的绝对值，举例：|-4|=4,|3|=3）。


你的任务是求出最小的操作次数使整个数组的值全部相等并把每一步输出出来。


数据保证总用方法使其经过若干次操作后全部相等


保证任意一次操作后数之都不会超过10^18

## 样例 #1

### 输入

```
5
2 4 6 6 6
```

### 输出

```
2
1 2 3 
1 1 2 
```

## 样例 #2

### 输入

```
3
2 8 10
```

### 输出

```
2
2 2 1 
2 3 2 
```

## 样例 #3

### 输入

```
4
1 1 1 1
```

### 输出

```
0
```

# 题解

## 作者：woshishei (赞：4)


### 题目大意

给定一个数列$a$，求出至少需要多少次**操作**才能使得$a$中的元素都相等。

在一次**操作**中，需要执行以下两种之一：

1. 对于**相邻的**两个元素$a_i, a_j$，使$a_i=a_i+|a_i-a_j|$；
2. 对于**相邻的**两个元素$a_i, a_j$，使$a_i=a_i-|a_i-a_j|$。

### 解题思路

既然操作次数最少，所以应该把所有元素都变成**出现次数最多的**数。

不难发现：

若$a_i>a_j$，则操作2可以使$a_i$变为$a_j$；

若$a_i<a_j$，则操作1可以使$a_i$变为$a_j$。

从前往后跑一遍，再从后往前跑一遍，以保证没有漏掉的情况。

### AC代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int n,a[200010],cnt[200010],mx=-1,mxd;//cnt[]储存每个数的出现次数，mxd记录出现次数最多的数
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		cnt[a[i]]++;
	}
	for(int i=0;i<=200000;i++)//注意数据范围：从0至200000
		if(cnt[i]>mx)
		{
			mx=cnt[i];
			mxd=i;
		}
	printf("%d\n",n-mx);
	for(int i=2;i<=n;i++)//从前往后
	{
		if(a[i-1]!=mxd)continue;
		if(a[i]>a[i-1])printf("2 %d %d\n",i,i-1);//大了就用2
		if(a[i]<a[i-1])printf("1 %d %d\n",i,i-1);//小了就用1
		a[i]=a[i-1];
	}
	for(int i=n-1;i>=1;i--)//再从后往前跑一遍
	{
		if(a[i+1]!=mxd)continue;
		if(a[i]>a[i+1])printf("2 %d %d\n",i,i+1);
		if(a[i]<a[i+1])printf("1 %d %d\n",i,i+1);
		a[i]=a[i+1];
	}
	return 0;
}
```

~~在比赛中我把一个0写成了1，结果FST了，本来能上expert，却掉了8分QwQ……**氟 铀 碳 钾**~~

---

## 作者：zk_y (赞：1)

这道题目不算太难，但是有很多小细节需要注意。

## 题目翻译

我们来看一下题目的这个条件：

  1 操作：将 $a[i]$ 变为 $a[i]+|a[i]-a[j]|$

  2 操作：将 $a[i]$ 变为 $a[i]-|a[i]-a[j]|$
  
我们可以把这个操作当成绝对值方程 ( 初中七年级的 )，稍微分类讨论，解出来后是这么一个结果：

对于操作 $1$：（这里不考虑等于的情况，由贪心可得。）
> 若 $a[i] >a[j]$ 则 $a[i]$ 将变为 $a[i]\times2-a[j]$（这什么东西……）
>
> 若 $a[i] <a[j]$ 则 $a[i]$ 将变为 $a[j]$（这才有用。）

对于操作 $2$：
> 若 $a[i] <a[j]$ 则 $a[i]$ 将变为 $a[i]\times2-a[j]$（这什么东西……）
>
> 若 $a[i] >a[j]$ 则 $a[i]$ 将变为 $a[j]$（这才有用。）

好了，那我们把两个有用的结论整合一下：（其实证明只用这两个结论就能使次数最少很简单，在这里就不证明了，请读者自行证明 ）。

操作 $1$：若 $a[i] <a[j]$ 则 $a[i]$ 将变为 $a[j]$ 

操作 $2$：若 $a[i] >a[j]$ 则 $a[i]$ 将变为 $a[j]$

我们知道，要使调整次数少，就要把他们都凑成在**数列中出现次数最多**的数。

那就很简单了，直接从前往后跑一遍，再从后往前跑一遍，不放心再跑一遍就可以了。

这题再查的时候还有一个小细节：统计最大数的时候需要从 $0$ 开始，否则你会错的（惨痛的教训）。

---

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,num[200005],t[200005],max_num,max_time,max_time_num;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&num[i]);
		t[num[i]]++;
		if(max_num<num[i])max_num=num[i];
	}
	for(int i=0;i<=max_num;i++){
		if(t[i]>max_time){
			max_time=t[i];	
			max_time_num=i;
		}
	}
	printf("%lld\n",n-max_time);
	if(!(n-max_time))return 0;
	for(int i=2;i<=n;i++){
		if(num[i-1]!=max_time_num)continue;
		if(num[i]>num[i-1])printf("%d %d %d\n",2,i,i-1);
		else if(num[i]<num[i-1])printf("%d %d %d\n",1,i,i-1);
		num[i]=num[i-1];
	} 
	for(int i=n-1;i>=1;i--){ 
		if(num[i+1]!=max_time_num)continue;
		if(num[i]>num[i+1])printf("%d %d %d\n",2,i,i+1);
		else if(num[i]<num[i+1])printf("%d %d %d\n",1,i,i+1);
		num[i]=num[i+1];
	} 
	return 0;
}
```


---

## 作者：Abeeel51 (赞：1)

#### 题目大意
根据两种操作使所有数都相等，求最小的操作次数

对于相邻的两个数的操作，分别是：

- 将 $a_i$ 变为 $a_i + \lvert a_i - a_j \rvert$

- 将 $a_i$ 变为 $a_i - \lvert a_i - a_j \lvert$

#### 解题思路
执行第一种操作，$a_i = 5 , a_{i+1} = 7 , a_i = 5 + \lvert 5-7 \rvert = 7$。

执行第二种操作，$a_i = 5 , a_{i+1} = 3 , a_i = 5 - \lvert 5-3 \rvert = 3$。

所以题中所给的操作就是将 $a_i$ 变为 $a_{i+1}$。很显然，我们最终要变的数就是出现次数最多的数。从这个数的位置开始向左向右模拟，累加，最终就可以得到结果。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int tong[200005];int a[200005];
int n,MAX=-0x7f7f7f7f,MAXi=0,MAXii=0;
int main(int argc, const char * argv[]) {
    // insert code here...
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        tong[a[i]]++;
        if(MAX<tong[a[i]]){
            MAX=tong[a[i]];
            MAXi=a[i];
            MAXii=i;
        }
    }
    if(MAX==n){
        printf("0");
    }else{
        printf("%d\n",n-MAX);
        for(int i=MAXii+1;i<=n;i++){
            if(a[i]==MAXi) continue;
            if(a[i]>MAXi) printf("2 %d %d\n",i,i-1);
            else printf("1 %d %d\n",i,i-1);
        }
        for(int i=MAXii-1;i>=1;i--){
            if(a[i]==MAXi) continue;
            if(a[i]>MAXi) printf("2 %d %d\n",i,i+1);
            else printf("1 %d %d\n",i,i+1);
        }
    }
    return 0;
}
```


---

## 作者：fanfansann (赞：1)

D. Equalize Them All

**题目大意**
给定一个数列a，求出至少需要多少次操作才能使得a中的元素都相等。
而操作共有两种：
1操作：将$a[i]$变为$a[i] + | a[i]-a[j] |$
2操作：将$a[i]$变为$a[i] - | a[i]-a[j] |$

--------
很明显这两种操作可以使得相邻不相等的数**直接变成相等的数**。也就是说只需要一次操作就可以使其相等。
题目中要求最少次数，贪心地想，肯定是让所有的数都变成出现次数最多的数最优。
然后就是找到出现次数最多的那一个，再正反跑两遍修改即可。
为什么要跑两遍呢，因为出现次数最大的那一个数不一定出现再哪里，正着跑一遍可以使最后都被修改，但是最前面的可能没有顾及到，所以需要再反着跑一遍。例如这个样例：

```cpp
6
246662
```
应该很清晰吧

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>

#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
#define lowbit(p) p&(-p)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;

const int N = 2e5+7;

int n,m;
int cnt[N];
int a[N],maxx,max_num;
int main()
{
    scanf("%d",&n);
    over(i,1,n){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    over(i,1,n)
        if(maxx < cnt[a[i]])
            maxx = cnt[a[i]],max_num = a[i];
    cout<<n - maxx<<endl;
    if(n == maxx)return 0;//顺手特判一下
    over(i,2,n)
        if(a[i-1] == max_num && a[i] != max_num)
            if(a[i]>a[i-1])
                printf("2 %d %d\n",i,i-1),a[i] = a[i-1];
            else printf("1 %d %d\n",i,i-1),a[i] = a[i-1];
    lver(i,n-1,1)
        if(a[i+1] == max_num && a[i] != max_num)
            if(a[i]>a[i+1])
                printf("2 %d %d\n",i,i+1),a[i] = a[i+1];
            else printf("1 %d %d\n",i,i+1),a[i] = a[i+1];
    return 0;
}

```

---

## 作者：da32s1da (赞：1)

发现从这两个操作中可以把两个不相等的数变成相等的。

若$x<y$，用$1$操作。若$x>y$，用$2$操作。

所以我们找到出现次数最多的数，把所有数都改成它即可。

```cpp
#include<cstdio>
const int N=2e5+50;
int n,x,y,a[N],cnt[N],mx,mxi;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]),cnt[a[i]]++;//统计出现次数
	for(int i=0;i<N;i++)
	if(mx<cnt[i])mx=cnt[i],mxi=i;//找到出现次数最多的数
	printf("%d\n",n-mx);//修改次数
	for(int i=1;i<=n;i++)
	if(a[i]==mxi){x=i;break;}
	for(int i=x-1;i>=1;i--)
	if(a[i]<a[x])printf("1 %d %d\n",i,i+1);
	else printf("2 %d %d\n",i,i+1);//第一段倒着改
    for(int i=x+1;i<=n;i++)
    if(a[i]<a[x])printf("1 %d %d\n",i,i-1);
    else if(a[i]>a[x])printf("2 %d %d\n",i,i-1);//然后扫一遍改其他的
}
```

---

## 作者：cloud2764scallop_eve (赞：0)

第一次看的时候确实被题面吓了一跳，没有好好思考就放弃了。其实题目还是蛮简单的。

## 题意
对于两种操作，我们可以进行分类讨论。  
#### 当 $a_i > a_j$ 时  
操作一：将 $a_i$ 变为了 $2 \times a_i - a_j$；  
操作二：将 $a_i$ 变为了 $a_j$。  
#### 当 $a_i \le a_j$ 时
操作一：将 $a_i$ 变为了 $a_j$；  
操作二：将 $a_i$ 变为了 $2 \times a_i - a_j$。

## 思路
观察上面的结果，我们可以发现不论 $a_i$ 和 $a_j$ 的大小关系如何，我们都可以通过两种操作 **直接** 将 $a_i$ 变为 $a_j$。

那么，为了将所有数字变为相同的，我们应该选择将所有数字转换为原数组中数量最多的数，所以这道题的做法其实就是找出这个数组的众数，再用 $n$ 将其减去，即为答案。  

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200005;
int n, cnt = 1, maxn = 0;
int mode, a[N], a2[N];
int main() {
//	freopen("equalize.in", "r", stdin);
//	freopen("equalize.out", "w", stdout);
	scanf("%d", &n);
	if (n == 1) {
		printf("0\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a2[i] = a[i];
	}
	sort(a + 1, a + n + 1);
//	for (int i = 1; i <= n; i++) {
//		cout << a[i] << endl;
//	}
	for (int i = 1; i < n; i++) {
		if (a[i] == a[i + 1]) cnt++;
		else cnt = 1;
		if (cnt > maxn) {
			mode = a[i];
			maxn = cnt;
		}
	}
	printf("%d\n", n - maxn);
//	cout << mode << endl;
	if ((n - maxn) == 0) return 0;
	for (int i = 2; i <= n; i++) {
		if (a2[i - 1] == mode) {
			if (a2[i] > a2[i - 1]) printf("2 %d %d\n", i, i - 1);
			else if (a2[i] < a2[i - 1]) printf("1 %d %d\n", i, i - 1);
			a2[i] = a2[i - 1];
		}
	}
	for (int i = n - 1; i >= 1; i--) {
		if (a2[i + 1] == mode) {
			if (a2[i] > a2[i + 1]) printf("2 %d %d\n", i, i + 1);
			if (a2[i] < a2[i + 1]) printf("1 %d %d\n", i, i + 1);
			a2[i] = a2[i + 1];
		}
	}
	return 0;
}

//a[i] > a[j]
// 1: 2*a[i]-a[j]
// 2: a[j]
//a[i] < a[j]
// 1: a[j]
// 2: 2*a[i]-a[j]
```
> 注意：在求众数时循环条件为 `i < n`，所以需要特判 `n == 1` 的情况

---

