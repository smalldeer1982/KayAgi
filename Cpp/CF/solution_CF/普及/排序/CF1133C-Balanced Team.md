# Balanced Team

## 题目描述

You are a coach at your local university. There are $ n $ students under your supervision, the programming skill of the $ i $ -th student is $ a_i $ .

You have to create a team for a new programming competition. As you know, the more students some team has the more probable its victory is! So you have to create a team with the maximum number of students. But you also know that a team should be balanced. It means that the programming skill of each pair of students in a created team should differ by no more than $ 5 $ .

Your task is to report the maximum possible number of students in a balanced team.

## 说明/提示

In the first example you can create a team with skills $ [12, 17, 15] $ .

In the second example you can take all students in a team because their programming skills are equal.

In the third example you can create a team consisting of a single student (and you cannot create a team consisting of at least two students).

## 样例 #1

### 输入

```
6
1 10 17 12 15 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
1337 1337 1337 1337 1337 1337 1337 1337 1337 1337
```

### 输出

```
10
```

## 样例 #3

### 输入

```
6
1 1000 10000 10 100 1000000000
```

### 输出

```
1
```

# 题解

## 作者：ysl1311 (赞：6)

这题很简单
~~暴力for就过了~~
然后一发发现TLE
仔细分析发现题目for2遍复杂度4e10
冷静分析发现我们可以对第二遍循环进行优化
```c
#include<cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 200005
int cmp(int x,int y) {
    return x>y;
}
int a[maxn];
int b[maxn];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        b[i]=0;
    }
    sort(a+1,a+n+1,cmp);
    int i,j=1;
    for(i=1; i<=n; i++) {
        while(a[i]-a[j]<=5&&j<=n) {
            j++;
        }
        b[i]+=(j-i);
        if (b[i]>=(n-i+1))
            break;
    }
    int max1=b[1];
    for( i=1; i<=n; i++)
        if (b[i]>max1)
            max1=b[i];
    printf("%d\n",max1);
    return 0;
}
```
然后一发
AC

---

## 作者：Rbu_nas (赞：3)

**题意简述**

有$n$名学生，$a_i$为第$i$名学生的能力值，一个团队中任意两队员的能力最大差值为5，求团队最多的学生人数。

$ $

思路很明显，先排序然后遍历队员，找到差值<=5长度的最大值。

考虑使用$\texttt{two-pointers}$，排过序后长度只会向后延伸，也就是说如果$a_1-a_5$区间内满足条件，那么$a_2$为起点的区间只可能是$a_2-a_n(n>=5)$

那么代码就很好写了

$ $

```cpp
#pr\
agma GCC optimize(2)
#include <cstdio>
#include <algorithm>
using namespace std;

#define gcc getchar
template <typename T> inline void read(T&x)
{
    x=0; bool f=true; char ck=gcc();
    for( ; ck<'0'||ck>'9'; ck=gcc()) if(ck == '-') f=false;
    for( ; ck>='0'&&ck<='9'; ck=gcc()) x=(x<<1)+(x<<3)+(ck^48);
    x=f?x:-x; return ;
}

#define N 200003
int n, a[N], res;

int main(void)
{
    read(n);
    for(int i=1; i<=n; ++i) read(a[i]);
    sort(a+1, a+n+1);
    int j=1;    //指针起点，因为最少也能有1名学生参赛
    for(int i=1; i<=n; ++i)
        while(j <= n && a[j] <= a[i]+5)    //不断更新a[i]~a[j]区间长度
        {
            res=max(res, j-i+1);
            //从a[i]-a[j]的区间长度为j-i+1
            ++j;
        }
    printf("%d", res);
    return 0;
}

```

---

## 作者：微分几何 (赞：2)

# 排序
先把这 $n$ 个数排序，因为选取的m个数一定是排序后长度为m的连续一段。

我们可以把上次求出来的 $r$ ，即最大区间的右端点保留。

在枚举的过程中，用 $a(i)$ 表示数组第 $i$ 个元素，因为 $a(r)-a(i)<=5$ ，所以 $a(r)-a(i+1)<=5$ 。


# 枚举 

继续寻找最大右端点，更新答案即可

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	int ans=0,r=1;
	for(int i=1;i<=n;i++)
	{
		while(r+1<=n&&a[r+1]-a[i]<=5)
		{
			r++;
		}
		ans=max(ans,r-i+1);
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：LlLlCc (赞：1)

发现CF（~~穿越火线~~）的题评分有点虚高，比如这题

------------
题意简洁明了，找出最多的数，并且这些数中极差（MAX-MIN）不超过5（其实把5改成未知数难度会略微提高，因为5只要每个数左右扫一遍有多少个不超过5的就好了）。

我们先排序一遍，用一个指针hed表示现在这些数的开始（i是结束）。因为是从小到大排好的，所以如果a[i]-a[hed]>5的话，那么a[i]-a[hed-1]>5也是成立的，这时把hed++就好了。

AC代码：
```
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int ans=1,n,hed=1,a[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for (int i=2;i<=n;i++){
		while (a[i]-a[hed]>5) hed++;
	    ans=max(ans,i-hed+1);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：InversionShadow (赞：0)

二分。

先对 $a$ 数组从小到大排序，再去二分 $m$，检查就从 $1 \sim (n-mid)$ 看有没有 $a_{i+mid}-a_i \le5$ 即可。

时间复杂度 $\mathcal{O(n \log n)}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 100;

int n, a[MAXN];

bool check(int mid) {  
  for (int i = 1; i <= n - mid; i++) {
    if (a[i + mid] - a[i] <= 5) {
      return 1;
    }
  }
  return 0;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  int l = 1, r = n;
  while (l < r) {
    //cout << l << ' ' << r << endl;
    int mid = l + r >> 1;
    if (check(mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  cout << l << endl;
  return 0;

```

---

## 作者：YuanZhizheng (赞：0)

这题难度其实不打，我们可以采用“双指针”的方法。

首先，我们先对整个序列排序，记得要用sort来。我不知道为什么我手写快排过不去？是我写的有问题吗？还是说sort对排序的优化比手写好很多。

挂个代码交流一下。

```
void Sort(int l,int r)
{
    if(l>=r)
        return;
    int i=l-1,j=r+1,x=a[(l+r)>>1];
    while(i<j)
    {
        while(a[++i]<x);
        while(a[--j]>x);
        if(i<j)
            swap(a[i],a[j]);
        else
            Sort(l,j),Sort(j+1,r);
    }
}
```
思路：

“双指针”。排序以后，i,j两个指针同时从队首开始，如果当前j指针和i指针所指位置相同或者a[j]-a[i]<=5符合题目条件的时候，j指针就往后移动。如果a[j]-a[i]>5，也就是不符合题目条件的时候，i指针就向后移动。

在这个过程中用一个maxx变量不断记录目前出现过最大j-i+1即可。

直接上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main()
{
    int n,i,j=1;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    int maxx=1;
    i=1,j=1;
    while(j<=n)
    {
        if(a[j]-a[i]<=5||j==i)
            j++;
        if(a[j]-a[i]>5)i++;
        if(j<=n)
           maxx=max(maxx,j-i+1);
    }
    printf("%d",maxx);
    return 0;
}
```

---

## 作者：lcc17 (赞：0)

**Solution:**

- 把整个数组从小到大排序，然后模拟一个类似队列的东西，如果队头和现在的值的差大于$5$，那么队头head++，直到差小于等于$5$。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int f=1,res=0;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-'0',c=getchar();}
	return f*res;
}
const int maxn=2e5+5;
int a[maxn],n,m,k,maxx,top,ans=0;
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);//排序
	top=1,maxx=1,ans=1;//maxx指现在共有连续几个差小于等于5的，ans表示总共中连续最大的
	for(int i=2;i<=n;i++){
		if(a[i]-a[top]<=5) maxx++;
		else {
			ans=max(ans,maxx);
			while(a[i]-a[top]>5) top++,maxx--;
			maxx++;
		}
	}
	ans=max(ans,maxx);//如果n不大于队头
	cout<<ans; 
	return 0;
}
```



---

