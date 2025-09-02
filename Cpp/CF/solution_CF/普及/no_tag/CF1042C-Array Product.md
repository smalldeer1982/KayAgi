# Array Product

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You can perform the following operations with it:

1. Choose some positions $ i $ and $ j $ ( $ 1 \le i, j \le n, i \ne j $ ), write the value of $ a_i \cdot a_j $ into the $ j $ -th cell and remove the number from the $ i $ -th cell;
2. Choose some position $ i $ and remove the number from the $ i $ -th cell (this operation can be performed no more than once and at any point of time, not necessarily in the beginning).

The number of elements decreases by one after each operation. However, the indexing of positions stays the same. Deleted numbers can't be used in the later operations.

Your task is to perform exactly $ n - 1 $ operations with the array in such a way that the only number that remains in the array is maximum possible. This number can be rather large, so instead of printing it you need to print any sequence of operations which leads to this maximum number. Read the output format to understand what exactly you need to print.

## 说明/提示

Let X be the removed number in the array. Let's take a look at all the examples:

The first example has, for example, the following sequence of transformations of the array: $ [5, -2, 0, 1, -3] \to [5, -2, X, 1, -3] \to [X, -10, X, 1, -3] \to $ $ [X, X, X, -10, -3] \to [X, X, X, X, 30] $ . Thus, the maximum answer is $ 30 $ . Note, that other sequences that lead to the answer $ 30 $ are also correct.

The second example has, for example, the following sequence of transformations of the array: $ [5, 2, 0, 4, 0] \to [5, 2, X, 4, 0] \to [5, 2, X, 4, X] \to [X, 10, X, 4, X] \to $ $ [X, X, X, 40, X] $ . The following answer is also allowed:

`<br></br>1 5 3<br></br>1 4 2<br></br>1 2 1<br></br>2 3<br></br>`Then the sequence of transformations of the array will look like this: $ [5, 2, 0, 4, 0] \to [5, 2, 0, 4, X] \to [5, 8, 0, X, X] \to [40, X, 0, X, X] \to $ $ [40, X, X, X, X] $ .

The third example can have the following sequence of transformations of the array: $ [2, -1] \to [2, X] $ .

The fourth example can have the following sequence of transformations of the array: $ [0, -10, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

The fifth example can have the following sequence of transformations of the array: $ [0, 0, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

## 样例 #1

### 输入

```
5
5 -2 0 1 -3
```

### 输出

```
2 3
1 1 2
1 2 4
1 4 5
```

## 样例 #2

### 输入

```
5
5 2 0 4 0
```

### 输出

```
1 3 5
2 5
1 1 2
1 2 4
```

## 样例 #3

### 输入

```
2
2 -1
```

### 输出

```
2 2
```

## 样例 #4

### 输入

```
4
0 -10 0 0
```

### 输出

```
1 1 2
1 2 3
1 3 4
```

## 样例 #5

### 输入

```
4
0 0 0 0
```

### 输出

```
1 1 2
1 2 3
1 3 4
```

# 题解

## 作者：lygmh (赞：2)

## 思路
贪心+分类讨论

### 要点
1. 负数为奇数个时去掉最大的负数，以保证所有负数相乘最大。
2. 有零时要将所有零合并之后去掉。
3. **综上所述，既有零而负数又为奇数个时，要先将所有零合并后，再与最大负数合并，最后把零去掉。**
4. 之后全部相乘即可。

### 坑点
1. 下标不会变化。
2. 只有一个负数和零时，或者只有零时，要保留零。

## 代码
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
int n,a[200005],s1[200005],s2[200005],s3[200005];
int zero,positive,negative;
bool cmp1(int x1,int x2){
    return a[x1]<a[x2];//索引排序
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]>0) s1[++positive]=i;
        else if(a[i]==0) s2[++zero]=i;
        else s3[++negative]=i;
    }
    sort(s1+1,s1+1+positive,cmp1);
    sort(s3+1,s3+1+negative,cmp1);//可以不用排序，找出负数最大值即可，此处是为了删除方便。
    if(zero>0){
        for(int i=zero;i>1;i--) printf("1 %d %d\n",s2[i],s2[i-1]);
        if(negative&1){
            printf("1 %d %d\n",s3[negative],s2[1]);
            negative--;
        } 
        if(positive>0||negative>0) printf("2 %d\n",s2[1]);//保留零
    }else{
        if(negative&1){
            printf("2 %d\n",s3[negative]);
            negative--;
        } 
    }
    for(int i=1;i<positive;i++){
        printf("1 %d %d\n",s1[i],s1[i+1]);
    }
    if(positive>0&&negative>0)printf("1 %d %d\n",s1[positive],s3[1]);
    for(int i=1;i<negative;i++){
        printf("1 %d %d\n",s3[i],s3[i+1]);
    }
    return 0;
}
```
PS：~~`sort`忘记加上`cmp`竟然过了6个点，证明了`CODEFORCES`的数据很水~~  
PPS:我觉得此前几篇题解的代码没我的好看，手动狗头。

---

## 作者：VenusM1nT (赞：1)

贪心。依然是一道细节题，弄得我有点痛不欲生……

做法其实非常简单，首先如果负数的个数是 偶数 的话，因为负负得正，所以肯定对答案是有贡献的，就不用管了。但如果负数的个数是 奇数，我们就需要去掉一个绝对值最小的负数，不然全部乘在一起会变成负数。

然后我们来考虑怎么处理 $0$。如果负数的个数是 偶数，那么我们只需要把所有 $0$ 都乘到一起，再删去即可；而如果负数的个数是 奇数，因为我们要删去一个绝对值最小的负数，所以我们把所有的 $0$ 乘到这个负数上，再删去即可。

最后把所有的数乘起来即可。

要注意的是 $a_i$ 和 $a_j$ 乘之后，$a_i$ 就被删除了，再输出 $i$ 就会判错。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
int n,sum,tot,a[MAXN],del;
bool fg[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<0) sum++;
	}
	if(sum&1)
	{
		int maxn=-2e9;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<0 && a[i]>maxn)
			{
				maxn=a[i];
				del=i;
			}
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			if(!a[i])
			{
				del=i;
				break;
			}
		}
	}
	fg[del]=1;
	for(int i=1;i<=n;i++)
	{
		if(i!=del && !a[i])
		{
			printf("1 %d %d\n",i,del);
			fg[i]=1;
			tot++;
		}
	}
	if(tot==n-1) return 0;
	if(del)
	{
		printf("2 %d\n",del);
		tot++;
	}
	if(tot==n-1) return 0;
	int pre=1,x=1;
	while(fg[x])
	{
		pre++;
		x++;
	}
	for(int i=x+1;i<=n;i++)
	{
		if(!fg[i])
		{
			printf("1 %d %d\n",pre,i);
			pre=i;
		}
	}
	return 0;
}
```

---

## 作者：Manjusaka丶梦寒 (赞：1)

我们可以想到我们需要先把所有的0，合为一个，然后判断负数两两配对是否多出一个(!%2)，两两配对后，两个负数相乘变为正数，正数当然越乘越大。

如果多出一个来，因为要让乘积最大，那么对于负数而言，我们需要删掉最大的负数，将这个最大的负数和0进行1操作，然后删除0(删除两个数的乘积)。

如果负数为偶数，那么我们直接把0的位置,删掉就好了，将剩下的的乘起来。

这样大体的思想就出来了，要注意一大堆细节问题：

1.如果全是0，那么我们只进行1操作(n-1)次就好，做完return 0；

2.没有0,。

3.没有负数。

4.没有正数。

上边的四种情况在代码中都有体现：

(情况分开讨论比较好理解，可能代码有点长)

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int cnt,cnt1,cnt2,n,x;
struct ahah
{
    int x,pos;
} a[200006],b[200006],c[200006];
bool cmp(ahah a,ahah b){ return abs(a.x)<abs(b.x); }
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&x);
        if(x==0)c[++cnt].pos=i;
        if(x<0)a[++cnt1].x=x,a[cnt1].pos=i;
        if(x>0)b[++cnt2].x=x,b[cnt2].pos=i;
    }
    sort(a+1,a+1+cnt1,cmp);
    sort(b+1,b+1+cnt2,cmp);
    int v=-1;
    if(cnt!=0)
    {
        v=c[1].pos;
        for(int i=2; i<=cnt; i++)
        {
            printf("1 %d %d\n",v,c[i].pos);
            v=c[i].pos;
        }
    }
    if(cnt==n)return 0;
    if(cnt1%2==0)
    {
        if(v!=-1)printf("2 %d\n",v),v=-1;
        if(cnt1!=0)
        {
            if(v==-1)v=a[1].pos;
            else printf("1 %d %d\n",v,a[1].pos),v=a[1].pos;
            for(int i=2; i<=cnt1; i++)
            {
                printf("1 %d %d\n",v,a[i].pos);
                v=a[i].pos;
            }
        }
        if(cnt2!=0)
        {
            if(v==-1)v=b[1].pos;
            else printf("1 %d %d\n",v,b[1].pos),v=b[1].pos;
            for(int i=2; i<=cnt2; i++)
            {
                printf("1 %d %d\n",v,b[i].pos);
                v=b[i].pos;
            }
        }
    }
    else
    {
        if(v==-1)v=a[1].pos;
        else printf("1 %d %d\n",v,a[1].pos),v=a[1].pos;
        if(cnt+1!=n)printf("2 %d\n",v),v=-1;
        else return 0;
        if(cnt1>1)
        {
            v=a[2].pos;
            for(int i=3; i<=cnt1; i++)
            {
                printf("1 %d %d\n",v,a[i].pos);
                v=a[i].pos;
            }
        }
        if(cnt2>0)
        {
            if(v==-1)v=b[1].pos;
            else printf("1 %d %d\n",v,b[1].pos),v=b[1].pos;
            for(int i=2; i<=cnt2; i++)
            {
                printf("1 %d %d\n",v,b[i].pos);
                v=b[i].pos;
            }
        }
    }
}
```

---

## 作者：ztz11 (赞：1)

## 一道贪心思路题

我们知道一点，任何一个0乘进来都没有什么用

因为任何一个数乘0都是0，一定不会最优

所以0是废物

同时负数呢？

负负得正

所以我们可以留下偶数个负数

如果负数是奇数个，那么很遗憾，为了不让最终结果是负数，必须要舍弃一个

乘积最大，所以要舍弃的，就是绝对值最小的那个

然后我们把要舍弃的先合并再舍弃

为什么呢？

比如说序列长为n，我的序列里全是0

如果你一个一个地删除，你就得删n次

而如果你两两合并呢？

答案是0，的确是最优情况了

Ok,不过细节不少，大家要多多注意

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int n,a[200005],cnt,bj[200005],wz,zero[200005],minx=2147483647,bnt;
int main()
{
	scanf("%d",&n);
	for(rii=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]==0)
		{
			bnt++;
			zero[bnt]=i;
			bj[i]=1;
		}
		if(a[i]<0)
		{
			cnt++;
			if(-1*a[i]<minx)
			{
				minx=-1*a[i];
				wz=i;
			}
		}
	}
	if(cnt%2==1)
	{
		bj[wz]=1;
		bnt++;
		zero[bnt]=wz;
	}
	sort(zero+1,zero+bnt+1);
	int pre=zero[1];
	for(rii=2;i<=bnt;i++)
	{
		printf("1 %d %d\n",pre,zero[i]);
		pre=zero[i]; 
	}
	if(bnt!=n&&bnt!=0)
	{
		printf("2 %d\n",pre);
	}
	for(rii=1;i<=n;i++)
	{
		if(bj[i]!=1)
		{
			pre=i;
			break;
		}
	}
	for(rii=pre+1;i<=n;i++)
	{
		if(bj[i]==0)
		{
			printf("1 %d %d\n",pre,i);
			pre=i;
		}
	}
}
```

---

