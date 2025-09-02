# multiset

## 题目背景

ZHY 有很多集合。集合多了，也就成了多重集合。

## 题目描述

给定一个 **多重集合**（集合中元素可重复）$S$，请求出一个最大的多重集合 $T$，满足 $T$ 是 $S$ 的一个 **真子集**，且对于 $T$ 中的每一个元素 $i$，要么 $i$ 在 $S$ 中没有前驱，要么 $i$ 在 $S$ 中的前驱 $\in T$。若有多个大小相同的集合满足条件，则 $T$ 为所有元素之和最大的一个。请输出 $T$ 的大小和其中元素之和。

---

一个数 $x$ 在一个集合 $S$ 中的前驱的定义为所有在 $S$ 中且 $<x$ 的元素 $y$ 的最大值。

## 说明/提示

**样例 $1$ 解释**

$T$ 为 $\{5,1,4\}$。

**样例 $2$ 解释**

$T$ 为 $\{1,4,2,5,7\}$。

### 数据范围

对于 $30\%$ 的数据，$n \le 15$。

对于 $100\%$ 的数据，$2 \le n \le 10^5$，$1 \le S$ 中的元素 $\le 10^9$。

## 样例 #1

### 输入

```
4
4 5 1 4```

### 输出

```
3 10```

## 样例 #2

### 输入

```
6
1 4 2 8 5 7```

### 输出

```
5 19```

# 题解

## 作者：Night_sea_64 (赞：6)

如果 $T$ 是 $S$ 的真子集，则 $T$ 是由 $S$ 删除**至少一个**元素得到的。

容易发现，这题集合中的元素都是正整数，所以我们加上一个元素一定会使元素和更大，所以第一问的答案一定是 $n-1$。

我们肯定需要让 $T$ 恰好是 $S$ 删除一个元素得到的，而且删除的数需要尽量小才可以保证和最大。

而我们通过 *“对于 $T$ 中的每一个元素 $i$，要么 $i$ 在 $S$ 中没有前驱，要么 $i$ 在 $S$ 中的前驱 $\in T$。”* 这句话可以看出，一个 $S$ 中的元素 $x$ 可以不在 $T$ 中需要满足下面两个条件之一：

1. $x$ 是 $S$ 中最大值。这样的话就不会有元素的前驱是 $x$ 了。
2. $x$ 在 $S$ 中出现不止一次，并且在 $T$ 中出现至少一次。这样的话如果有元素的前驱是 $x$，也会在 $T$ 中出现。

然后我们就找 $S$ 中满足这两个条件之一的最小的元素删掉就可以了。注意开 long long。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int a[100010];
int main()
{
    cin>>n;
    long long s=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        s+=a[i];
    }
    sort(a+1,a+n+1);
    bool flag=0;
    for(int i=1;i<=n;i++)
        if(a[i]==a[i-1])
        {
            flag=1;
            s-=a[i];
            break;
        }
    if(!flag)s-=a[n];
    cout<<n-1<<" "<<s<<endl;
    return 0;
}
```

---

## 作者：Galex (赞：6)

容易发现第一问答案总是 $n-1$，因为把最大的数删掉不会有任何影响。其次，删掉重复的数也不会有影响。于是，第二问答案就是总和减去最小的重复的数。若没有重复的数，则删掉最大的数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, sum = 0;
int a[100005];

signed main() {
	n = read();
	for (int i = 1; i <= n; i++)
		sum += a[i] = read();
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; i++)
		if (a[i] == a[i - 1] || i == n) {
			sum -= a[i];
			break;
		}
	cout << n - 1 << ' ' << sum << endl;
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：4)

### 思路

#### 题目题意

就是有个存在重复元素的集合，让你定义一个 $S$ 的[真子集](https://baike.baidu.com/item/%E7%9C%9F%E5%AD%90%E9%9B%86/105715?fr=aladdin) $T$。其中，集合 $T$ 的元素必须满足任意一个条件：

- 是集合 $S$ 里面最小的一个值；
- 比自己小的值中最大的，也在集合 $T$ 中。

#### 解题方法

最开始，我是想到模拟，~~都怪最近蓝桥杯的题刷多了~~。

但是仔细读一下样例，再加上自己模拟一下，就会发现 $T$ 的大小总是为 $n-1$。

~~因为再大的话就不是真子集了。~~

那集合 $T$ 的元素和应该是多少呢？

首先，集合 $T$ 就是 $S$ 删除一个元素。

根据我先前自己的模拟，为了使集合 $T$ 合法，只有两种删除方法：

1. 删除重复的元素；
2. 删掉最大的元素。

那我们肯定是优先删除最小重复的元素，如果不存在，就删除最大的元素。

完结撒花！

### 代码

记得，十年 OI 一场空，不开 long long 见祖宗。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100005;

int n,s[N];
int sum,del;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n;
    cout << n-1 << " ";
    for(int i = 1; i <= n; i++){
        cin >> s[i];
        sum += s[i];
    }
    
    sort(s+1,s+1+n);
    
    del = s[n];
    for(int i = 2; i <= n; i++){
        if(s[i-1] == s[i]){
            del = s[i];
            break;
        }
    }
    
    cout << sum-del << endl;
    
    return 0;
}
```

---

## 作者：hycqwq (赞：3)

开始之前先说一句：我校大佬出的题我必须做！

## 前置知识

真子集：若集合 $B$ 是集合 $A$ 的子集且 $A \ne B$，则称 $B$ 为 $A$ 的真子集。

## 思路

### 前置定义

令 $|X|$ 为集合 $X$ 的元素个数。

设 $S = \{s_1, s_2, \cdots, s_n\}$ 且 $s_1 \le s_2 \le \cdots \le s_n$。

设 $T = \{t_1, t_2, \cdots, t_{|T|}\}$ 且 $t_1 \le t_2 \le \cdots \le t_{|T|}$。

### 思路推导

由于题目要求 $T$ 是 $S$ 的**真**子集，所以 $T \ne S$，于是我们需要去掉至少一个数，但在这里，我们要的是最大的 $T$，所以我们只需要去掉一个数，即 $|T| = n - 1$。

首先，我们要知道，直接把 $S$ 中的最大值去掉（即 $T = \{s_1, s_2, \cdots, s_{n - 1}\}$）是符合条件的，但可能不是最小。

我们要使 $T$ 中元素的和最大，那么我们去掉的数肯定是越小越好，但是如果我们去掉了一个在 $S$ 中只有一个的数（设其为 $s_i$），就会导致另外一个以它为前驱的数在 $S$ 中有前驱，但在 $T$ 中没有，是不符合题目条件的，所以我们去掉的数应该是最小的有重复的数。

那如果 $S$ 中没有重复的数呢？那我们去掉的数应该不是任何数的前驱，而只有最大的那个数（即 $s_n$）符合条件。

### 总结

显然对于第一问，$|T| = n - 1$。

第二问有以下两种情况：

- 若存在整数 $i < j$ 使 $s_i = s_j$，则 $\sum\limits_{a = 1}^{|T|}t_a = (\sum\limits_{b = 1}^{n}s_b) - s_i$。
- 否则 $\sum\limits_{a = 1}^{|T|}t_a = \sum\limits_{b = 1}^{n - 1}s_b$.

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int n, s[100005];
long long sum = 0;//不开long long见祖宗

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i], sum += s[i];
    sort(s + 1, s + n + 1);//按从大到小排序，否则不好确定是否有重复以及元素的最大值
    for (int i = 2; i <= n; i++)
        if (s[i] == s[i - 1] || i == n)//减去重复的或最大的
        {
            sum -= s[i];
            break;//取了一个直接结束
        }
    cout << n - 1 << " " << sum << endl;//由于只去掉一个元素，所以T的大小为n - 1
    return 0;
}
```

提交记录：[R106306487](https://www.luogu.com.cn/record/106306487)。

---

## 作者：Furina_Hate_Comma (赞：2)

## Problem 1

输出 $n-1$ 即可。

证明：

1. 所有数是正整数，所以加上一个数会变大。

2. 真子集不能是原集合。

## Problem 2

去掉重复元素，如果没有就去掉最大元素。

证明：

1. 删掉最大值没有影响。

1. 重复的元素也没有影响。

十年 OI 一场空，不开 long long 见祖宗！

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[114514];
signed main(){
	int n;
	cin>>n;
	cout<<n-1<<" ";
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	bool flag=0;
	int sum=0;
	for(int i=1;i<=n;i++){
		if(!flag&&a[i]==a[i-1]){
			flag=1;
			continue;
		}
		sum+=a[i];
	}
	if(!flag)
		sum-=a[n];
	cout<<sum;
} 
```


---

## 作者：lbdontknow (赞：1)

## 算法分析
首先，第一问问的是多重集合 $T$ 的长度，根据真子集的定义，多重集合 $T$ 的长度最长为 $n-1$，并且我们能够发现，将最大的数删去，剩下的数就是最长的多重集合 $T$，所以第一问的答案为 $n-1$。  
我们发现，多重集合 $T$ 的元素不止可以删去最大数，还可以删去一个重复数。因为要使得多重集合 $T$ 尽量大，所以我们删去一个最小的重复数，如果没有，则删去最大数，然后求和。
### 注意事项
由于 $1 \leq S$ 中的元素 $\leq 10^9$，所以我们需要开一手 ```long long```，不然只能得到 $50$ 分。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1919810],sum,i;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	cout<<n-1<<' ';
	for(i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+1+n);
	for(i=2;i<=n;i++){
		if(a[i-1]==a[i]){
			sum-=a[i];
			break;
		}
	}
	if(i==n+1){
		sum-=a[n];
	}
	cout<<sum<<endl;
	return 0;
} 
```

---

## 作者：I_am_AKed_by_NOI (赞：1)

显然，如果把 $S$ 中的最大值去掉，是完全符合题意的。所以第一题的答案就是 $n-1$。

同时我们发现，如果 $S$ 中有两个元素相同，那么删除他们其中一个也符合题意。为了让答案最优，我们选择将最小的且重复的数字删除，然后统计剩下的答案即可。若是没有相同的值，那就删除最大值。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,sum,a[N],tmp;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1])
		{
			tmp=a[i]; //找到相同的值 
			break;
		}
	}
	if(tmp==0) tmp=a[n]; //没有相同的选最大的。 
	cout<<n-1<<" "<<sum-tmp;
	return 0;
}
```


---

## 作者：Pwtking (赞：0)

首先先读题。

读题后我们发现，因为题目中要求我们选的数要尽量大，并且选的数最多为 $n-1$，我们当然是选的数越多越好，所以答案 $T$ 的大小一定是 $n-1$，同时，若要满足这 $n-1$ 个数的总和最大，则将原数列排序后找到最小的重复的数并减掉它即可。

最后记得开 long long。

AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
ll n,num[100001],ans,f=inf;
inline ll in() {
    char a=getchar();
	ll t=0,f=1;
	while(a<'0'||a>'9') {if (a=='-') f=-1;a=getchar();}
    while(a>='0'&&a<='9') t=(t<<1)+(t<<3)+a-'0',a=getchar();
    return t*f;yinw
}
signed main() {
	n=in();
	for (ll i=1;i<=n;++i) num[i]=in();
	sort(num+1,num+1+n);
	for (ll i=1;i<=n;++i) {
		if (num[i-1]==num[i]) f=min(f,num[i]);
		ans+=num[i];
	}
	if (f==inf) printf("%lld %lld",n-1,ans-num[n]);
	else printf("%lld %lld",n-1,ans-f);
	return 0;
}
```



---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P9160)

题目大意：

给你一个集合 $S$，其中有 $n$ 个元素。定义 $x$ 的“前驱”为 小于 $x$ 的数 $y\in S$ 的最大值。求 $S$ 的真子集 $T$，使得 $S$ 的所有元素要么没有前驱，要么它的前驱 $\in T$。

思路：

显然删掉 $S$ 的所有元素中的最大值不受影响，所以第一问的答案是 $n-1$。不仅删掉最大值没有影响，我们还可以删掉重复的元素。这样，第二问的答案就是 $S$ 的所有元素之和再减去所有重复元素的和的值。

细节全部都在代码里。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[100001];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        sum += a[i];
    }
    sort(a + 1, a + n + 1);// 排序
    // 接下来减去重复的元素
    for (int i = 1; i <= n; i++){
        if (a[i] == a[i + 1] || i == n){
            sum -= a[i];
            break;
        }
    }
    cout << n - 1 /*第一问*/ << " " << sum /*第二问*/ << "\n";
    return 0;
}
```

---

## 作者：G__G (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P9160)

## 题目描述

给定一个 **多重集合**（集合中元素可重复）$S$ ，请求出一个最大的多重集合 $T$ ，满足 $T$ 是 $S$ 的一个 **真子集** ，且对于 $T$ 中的每一个元素 $i$ ，要么 $i$ 在 $S$ 中没有前驱，要么 $i$ 在 $S$ 中的前驱 $\in T$ 。若有多个大小相同的集合满足条件，则 $T$ 为所有元素之和最大的一个。请输出 $T$ 的大小和其中元素之和。

---

一个数 $x$ 在一个集合 $S$ 中的前驱的定义为所有在 $S$ 中且 $<x$ 的元素 $y$ 的最大值。

## 解题过程

首先我们可以知道 $T$ 的值总是 $n-1$ (减去最大值的情况)。

而 $T$ 的所有元素之和要分两种情况。

1. 有重复数字时：减去最小的重复数字。

2. 没有重复数字时：减去最大值。

所以我们只需要判断序列是否有重复数字来分类计算。

## [$AC$](https://www.luogu.com.cn/record/105867855)代码

```
#include<bits/stdc++.h>//万能头
using namespace std;
long long a[1234567]={0},sum=0,n;
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];//求和
	}
	sort(a+1,a+n+1);
	long long i;
	for(i=2;i<=n;i++){
		if(a[i]==a[i-1]||i==n){//判断重复数字与是否是最大值
			sum-=a[i];
			break;
		}
	}
	cout<<n-1<<" "<<sum<<endl;//输出
	return 0;
} 
```




---

