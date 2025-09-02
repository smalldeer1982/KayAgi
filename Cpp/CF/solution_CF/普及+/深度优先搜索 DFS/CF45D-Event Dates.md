# Event Dates

## 题目描述

On a history lesson the teacher asked Vasya to name the dates when $ n $ famous events took place. He doesn't remembers the exact dates but he remembers a segment of days $ [l_{i},r_{i}] $ (inclusive) on which the event could have taken place. However Vasya also remembers that there was at most one event in one day. Help him choose such $ n $ dates of famous events that will fulfill both conditions. It is guaranteed that it is possible.

## 样例 #1

### 输入

```
3
1 2
2 3
3 4
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
2
1 3
1 3
```

### 输出

```
1 2 
```

# 题解

## 作者：Siyuan (赞：8)

## 本题思路：
1. 很显然，本题的思路为 **贪心**。
2. 每次选择 **左边界最小，次之为右边界最小** 的区间，以选择区间的$\ left$为标志，修改其他区间的$\ left$（如果大于选择区间的$\ left$则进行修改，相当于 **删除区间**）。
3. 重复以上步骤$\ n$次即可。

### 代码如下：

```
#include<cstdio>
using namespace std;

int n,l[101],r[101];
int ans[101];
bool vis[101];

inline bool check(const int &now,const int &cmp)
{
	if(l[cmp]>l[now])  return 1;
	else  return(l[cmp]==l[now]&&r[cmp]>r[now]);
}

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		scanf("%d%d",&l[i],&r[i]);
	l[0]=r[0]=0x3f3f3f3f;
	for(register int i=1;i<=n;i++)
	{
		register int k=0;
		for(register int j=1;j<=n;j++)
			if(!vis[j]&&check(j,k))  k=j;
		
		ans[k]=l[k];  vis[k]=1;
		register int p=ans[k]+1;
		
		for(register int j=1;j<=n;j++)
			if(l[j]<p)  l[j]=p;
	}
	for(register int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Jorisy (赞：2)

一道简单贪心。

---

类似于区间调度问题，先将每个区间按右端点从小到大排序（相同者按左端点），然后贪心选择区间中最小的数。

当然，如果这个数被取过了，则延后选择即可。

另外，排完序后原下标会被打乱，因此我们在结构体中需存入原下标。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int x,y,idx;//[x,y] 区间以及原下标 idx
}a[105];
int n,ans[105];
bool f[10000005];

bool cmp(node x,node y)
{
	return x.y==y.y?x.x<y.x:x.y<y.y;
}//排序比较

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].idx=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		int s=a[i].x;
		while(f[s++]);
		f[--s]=1;//由于 while() 循环后还会多一，因此减去一
		ans[a[i].idx]=s;//按原下标存答案
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<' ';
	}
 	return 0;
}
```

---

## 作者：ttwyzz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF45D)

贪心题。



------------
### 题目大意

给定 $\,n\,$ 个事件，每个事件有各自的左端点和右端点，然后每个点只能容纳一个事件，输出字典序最小的每一个事件可能发生的日期。

### Solution

- 按右端点排序，右端点一样，按左端点排序。
- 开个 bitset 记录每个点是否有过。
- 重复 $\,n\,$ 次操作。

最后输出答案。

### code：

------------


```
#include<bits/stdc++.h>
using namespace std;

struct N{
	int l,r,id;
}a[105];

bool cmp(N a,N b)
{
	if(a.r != b.r) return a.r < b.r;
	return a.l < b.l;
}
int ans[105];
int n;
bitset<10000007> v;
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id = i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i = 1; i <= n; ++i)
	{
		for(int j = a[i].l; j <= a[i].r; ++j)
		{
			if(!v[j])
			{
				v[j] = 1;
				ans[a[i].id] = j;
				break;
			}
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```


------------

 完结撒花 ！

---

## 作者：yangwenbin (赞：1)

# 题解 CF45D 【Event Dates】

贪心题，这很明显

所以要对内容排序

怎么排呢？

首先明确一开始翻译存在问题，题目要求任意一个解，而不是字典序最小的；
（~~被坑了好几次~~）

所以只要保证有解即可，既不能取值超过区间

n不大，直接贪心+模拟

从一个左日期到右日期模拟，所以保证有日期之前有值可取，所以以右日期为基准排序

右日期相同，左日期早的在前（尽量取得早不影响后面取值）

若不同则右日期越早越前，避免前边取完后边区间。

```
inline bool cmp(Event a,Event b){
	if (a.dateright == b.dateright){
		return a.dateleft < b.dateleft;
	}return a.dateright <  b.dateright;
}
```

之后直接模拟

1-n每个区间，左节点到右节点看有无值可取，如有记录，跳出。

```
for (int i = 0; i < n; ++i){
	int j=input[i].dateleft;
	while(vis[j] && j <= input[i].dateright){
		++j;
	}
	vis[j]=true;
	ans[input[i].index] = j;
}
```

# code


```
#include <bits/stdc++.h>
using namespace std;
int n;
struct Event{
	int dateleft,dateright,index;
}input[150];
inline bool cmp(Event a,Event b){
	if (a.dateright == b.dateright){
		return a.dateleft < b.dateleft;
	}return a.dateright <  b.dateright;
}
int ans[150];
bool vis[10000050];
int main(){
	scanf("%d",&n);
	for (int i = 0; i < n; ++i){
		scanf("%d %d",&input[i].dateleft,&input[i].dateright);
		input[i].index=i;
	}
	sort(input,input+n,cmp);
	for (int i = 0; i < n; ++i){
		int j=input[i].dateleft;
		while(vis[j] && j <= input[i].dateright){
			++j;
		}
		vis[j]=true;
		ans[input[i].index] = j;
	}
	for (int i = 0; i < n; ++i){
		printf("%d ",ans[i]);
	}
}
```


---

## 作者：Lee666666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF45D)

这道题的主要思路是**贪心**。

首先思路是对于每一个区间，去寻找一个日期使其不与我们之前遍历的区间选择的日期发生**冲突**。那么问题来了：怎样去规定一个合理的**顺序**，使得其解法一定最优呢？

正解是以**右端点**为**第一关键字**升序排列，以**左端点**为**第二关键字**升序排列，每一个区间**从左到右**选择日期。为什么不能反过来呢？左端点靠前最先选的日期不是就更靠前吗？更通俗的说：为什么偏要委屈**右端点靠后**的区间呢？

一个比较**抽象**的看法：如果你**先**选择了**右端点靠后**的区间，那么它选择的日期势必更加**靠前**，而因为我们对于每个区间是**从左到右**选择日期，所以在**宏观**上看，我们选择的所有日期也都是**从左到右**,所以这样会占用那些**右端点靠前**的区间的本就**所剩无几**的空间，浪费**右端点靠后**的更加**充裕**的空间，这就不够优秀。

设 $r_i-l_i=L$，时间复杂度 $O(nL)$，空间复杂度$O(n+L)$

实际时间复杂度似乎远不到 $O(nL)$，有没有精通计算时间复杂度以及贪心的大佬来解释一下QwQ

上代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
    int l, r, id;
    bool operator < (const node &rhs) const { // 排序
        if (r != rhs.r) {
            return r < rhs.r;
        }
        return l < rhs.l;
    }
} arr[115];

int n, date[115];
bool vis[10000015];

int main() {
    scanf("%d", &n);
    for (register int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].l, &arr[i].r);
        arr[i].id = i;
    }
    sort(arr, arr + n);
    for (register int i = 0; i < n; i++) {
        for (register int j = arr[i].l; j <= arr[i].r; j++) {
            if (!vis[j]) {
                vis[j] = 1; // 标记
                date[arr[i].id] = j;
                break;
            }
        }
    }
    for (register int i = 0; i < n; i++) {
        printf("%d ", date[i]);
    }
    return 0;
}
```


---

## 作者：きりと (赞：0)

### 题目大意

见中文翻译。

### 解题思路

考虑贪心乱搞，可以先按 $l_i$ 为第一关键字，$r_i$ 为第二关键字排序，然后挨个取。

此时发现一种糟糕的情况，如果有一个较大的日期区间在靠前的位置，那么靠前的日期有可能会被浪费，具体可见 CF 的`test 3`。

发现 $n$ 只有 $100$ 那就可以在之前贪心的基础上，每次取数以后把 $l[j]=l[i](i<j\le n )$ 的 $l[j]+1$ ，然后重新排序。

感性理解一下，对于一段长度较短的日期区间，我们把它尽量放前面，然后较长的放后面。如果在此日期区间后面还有一些更短且 $\ge 1$ 的日期区间，那我们肯定会让它们发生在其日期区间内最早的一段，正确性可以保证。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define forr(i,l,r) for(register int i=l;i<=r;i++)
#define ffor(i,r,l) for(register int i=r;i>=l;i--)
using namespace std;
const int N=105;
struct node{
    int l,r,id;
}a[N];
int ans[N];
bool cmp(node q,node p)
{
    if(q.l==p.l)
    {
        return q.r<p.r;
    }
    return q.l<p.l;
}
signed main()
{
    int n;
    cin>>n;
    forr(i,1,n)
    {
        cin>>a[i].l>>a[i].r;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    int cnt=0;
    forr(i,1,n)
    {
        if(a[i].l>cnt)
        {
            cnt=a[i].l;
        }
        else
        {
            cnt++;
        }
        ans[a[i].id]=cnt;
        forr(j,i+1,n)
        {
            if(a[j].l==cnt)
            {
                a[j].l++;
            }
        }
        sort(a+i+1,a+n+1,cmp);
    }
    forr(i,1,n)
    {
        cout<<ans[i]<<" ";
    }
    puts("");
    return 0;
}

```



---

