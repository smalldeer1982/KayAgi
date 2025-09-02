# Chores

## 题目描述

彼佳和瓦西亚是兄弟。今天对他们来说是个特殊的日子，因为他们的父母把他们独自留在家里，让他们做家务。每个杂务都有一个单一的参数——它的复杂度。第$i$个杂务的复杂度等于$h_{i}$

由于彼佳年纪较大，他想要承担那些复杂的家务$(h_{i}>x)$，把较为简单的家务留给瓦西亚。$(h_{i}<=x)$。兄弟俩已经决定，彼佳做$a$个家务，瓦西亚做$b$个家务$(a+b=n)$。

有多少种方法可以让他们选择一个整数$x$，使得满足上述条件的情况下，彼佳正好做a个家务，瓦西亚正好做$b$个家务？

## 说明/提示

在第一个样例中，$x$ 可能为3，4，5

## 样例 #1

### 输入

```
5 2 3
6 2 3 100 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7 3 4
1 1 9 1 1 1 1
```

### 输出

```
0
```

# 题解

## 作者：我和鱼过不去 (赞：4)

显然，彼佳所做的 $a$ 件家务中最简单的家务的复杂度，和瓦西亚所做的 $b$ 件家务中最难的家务的复杂度之差，就是 $x$ 。
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int f[2005];
int a,b;
int main()
{
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)
    {
        cin>>f[i];
    }
    sort(f+1,f+1+n);
    cout<<f[b+1]-f[b]<<endl;
    return 0;
}
```
### Python
```python
s = input().split()
n = int(s[0])
a = int(s[1])
b = int(s[2])
s = input().split()
for i in range(len(s)):
    s[i] = int(s[i])
s.sort()
print(s[b]-s[b-1])
```


---

## 作者：xiaomuyun (赞：3)

# CF169A Chores 题解
**蒟蒻们看过来，这里有详解！**~~最优解来炫耀了~~

[题目传送门](https://www.luogu.com.cn/problem/CF169A)

我觉得这题应该是道橙题。
## 题意分析
题目中有这样一句话：

> 由于 Petya 年纪较大，他想要承担那些复杂的家务 $(h_i>x)$，把较为简单的家务留给 Vasya $(h_i\leq x)$。兄弟俩已经决定，Petya 做 $a$ 个家务，Vasya 做 $b$ 个家务 $(a+b=n)$。

因此我们要使输入的这个数组有序，这样才能知道复杂的家务和较为简单的家务分别是什么。因为我们并不需要维护每个家务的编号，只需要维护每个家务的复杂度，所以可以用 C++ 标准库中的 $\operatorname{sort}$ 直接排序。

因为 Petya 做的是复杂度前 $a$ 大的家务，而 Vasya 做的是复杂度后 $b$ 大的家务，所以我们需要定一个分界线（也就是题目问的，不过题目求的是满足条件的分界线的数量），并且要保证复杂度前 $a$ 大的家务的复杂度都比这个分界线大，而剩下的 Vasya 做的 $b$ 个家务都**不大于**这个分界线。
## 具体算法
先输入，然后**从大到小排序**（从小到大也行，但是处理就要变一下），最后输出复杂度前 $a$ 大的元素中最小的（即 $h_a$），与复杂度后 $b$ 大的元素中最大的（即 $h_{n-b+1}$，也就是 $h_{a+1}$）之差即可。
## $AC$ 代码
```cpp
#include<algorithm>
#include<cstdio>

using namespace std;

int n,a,b,h[2002];

bool cmp(int A,int B){//注意是从大到小排序，sort如果不写cmp是从小到大排序的
	return A>B;
}

int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i) scanf("%d",&h[i]);
	sort(h+1,h+1+n,cmp);
	printf("%d\n",h[a]-h[a+1]);
	return 0;
}
```
## 总结
一道 $\operatorname{sort}$ 的练手题。请大家点个赞吧，制作不易！

---

## 作者：Tune_ (赞：2)

这道题呢，其实很简单QAQ

~~只用了12行就解决了~~

不得不说，sort好用的很~

sort后，前b个是瓦西亚做，后a个是彼佳做。

而第b个是瓦西亚所做的最复杂的，第b+1个是彼佳做的最简单的，它们的差就是x的个数。（相等就是0）

所以只需要排序后输出第b个和第b+1个的差就好啦~

以下是代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,s[2005]; 
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	sort(s+1,s+n+1);
	cout<<s[b+1]-s[b];
	return 0;
}
```
给蒟蒻点个赞吧QWQ[卖萌]

---

## 作者：林聪 (赞：2)

本题题意：有俩人Petya和Vasya,他们有n件事要去做,Petya做a件,vasya做b件（a+b=n）。每件事有一定的复杂度h[i],其中复杂度小于等于x的vasya做,大于x的petya做,现在让我们去求x有多少个不同的取值。 思路：首先先将这些事的复杂度从小到大排序，接着因为vasya做b件事，所以剩下的n-b件事由petya来做。也就是说，h[b]是一个分界点，复杂度在h[b]及以前的事由vasya来做，复杂度在h[b]之后的事由petya来做。 故我们只需判断一下h[b+1]是不是比h[b]大就行。比它大x就能取到h[b+1]-h[b]个值，不比它大就取不到值了，因为只有大于x的petya才会去做，如果分界值相等就找不出这样的x了。 代码如下:

```cpp
include<cstdio>
include<algorithm>
using namespace std;
int n,a,b,h[3000];//与题目中含义一样
int main()
{
  scanf("%d%d%d",&n,&a,&b);
  for(int i=1;i<=n;i++) scanf("%d",&h[i]);//读入
  sort(h+1,h+n+1);//排序不解释
  int k=h[b+1]-h[b];//找到临界值的差值
  if(k<=0) printf("0");//相等或小于就找不出x了（其实不会小于的。。）
  else printf("%d",k);//不然就把这个差值输出出来，这就是x能取到的值的数量
  return 0;
}
```


ps：第一次发题解，求通过。。

---

## 作者：封禁用户 (赞：1)

这道题还算简单，切入正题！
# 题目讲解

其实这道题要求的就是第一段中的最大与第二段中的最小的差

这道题其实就是一个简单 sort ，排序后我们只需要求 $arr_{b+1}-arr_b$ 即可

其中， $arr_{b+1}$ 为第二段中最小的， $arr_b$ 为第一段最大的。

上代码！
```cpp
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long l;

l arr[2005];

int main() {
    l n, a, b;
    cin >> n >> a >> b;
    for (l i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + n);
    cout << arr[b + 1] - arr[b] << endl;
    return 0;
}

```
另附一句话：抄啊抄题解，留啊留棕名！

---

## 作者：3a51_ (赞：0)

### 题目大意

给定一个序列 $h$，将其分为前后两段，第一段长 $b$，第二段长 $a$。现在求两段的分割值有几种可能。

### 思路

很明显分割值只要比第一段中最大的大，且比第二段中最小的小，就可以了。

所以我们可以对序列 $h$ 排个序，就能得到答案 $h_{b+1}-h_b$。

### code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a,b,h[2005];
int main()
{
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)
		cin>>h[i];
    sort(h+1,h+1+n);
    cout<<h[b+1]-h[b]<<endl;
    return 0;
} 
```

---

## 作者：违规用户名gAGt8$%z (赞：0)

## 题目简化
通过题面，显然看出，波佳做的家务是最难的 $a$ 个,而瓦西亚做的家务是剩下的 $b$ 个，而答案就是两个人家务复杂度总和的差的绝对值。


------------

## 解题思路
首先，先读入，然后从小到大排序，$h_{b}$ 和 $h_{b+1}$ 之差就是答案。



------------
上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int a[2005];
int main(){
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    cout<<a[y+1]-a[y]<<endl;
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
两兄弟要分担 $n$ 件家务，第 $i$ 件家务有一个复杂度 $h_i$。兄弟俩以一个数 $x$ 为界。所有满足复杂度 $>x$ 的家务都给哥哥做，其余的给弟弟做。他们想找到一个数 $x$，使得哥哥刚好做 $a$ 件家务，弟弟刚好做 $b$ 件家务。试求出所有可能的 $x$ 的个数。

**数据范围：$2\leqslant n\leqslant 2000,a,b\geqslant 1,a+b=n,1\leqslant h_i\leqslant 10^9$。**
## Solution
我们先将所有的家务按照复杂度从小到大排序，然后只需要看复杂度第 $k$ 小的家务的复杂度是否和复杂度第 $k+1$ 小的家务的复杂度之间的数值关系就好，如果没有方案答案就是 $0$，否则答案就是复杂度第 $k$ 小的家务的复杂度是否和复杂度第 $k+1$ 小的家务的复杂度之间的差值。
## Code
```cpp
int a, b, n, h[2007], ans;

int main() {
	getint(n), getint(a), getint(b);
	_for(i, 1, n)	getint(h[i]);
	sort(h + 1, h + n + 1);
	writeint(ans = h[b + 1] - h[b]);
	return 0;
}
```

---

