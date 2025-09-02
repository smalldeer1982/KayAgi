# Cat Party (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

Shiro's just moved to the new house. She wants to invite all friends of her to the house so they can play monopoly. However, her house is too small, so she can only invite one friend at a time.

For each of the $ n $ days since the day Shiro moved to the new house, there will be exactly one cat coming to the Shiro's house. The cat coming in the $ i $ -th day has a ribbon with color $ u_i $ . Shiro wants to know the largest number $ x $ , such that if we consider the streak of the first $ x $ days, it is possible to remove exactly one day from this streak so that every ribbon color that has appeared among the remaining $ x - 1 $ will have the same number of occurrences.

For example, consider the following sequence of $ u_i $ : $ [2, 2, 1, 1, 5, 4, 4, 5] $ . Then $ x = 7 $ makes a streak, since if we remove the leftmost $ u_i = 5 $ , each ribbon color will appear exactly twice in the prefix of $ x - 1 $ days. Note that $ x = 8 $ doesn't form a streak, since you must remove exactly one day.

Since Shiro is just a cat, she is not very good at counting and needs your help finding the longest streak.

## 说明/提示

In the first example, we can choose the longest streak of $ 13 $ days, since upon removing the last day out of the streak, all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ will have the same number of occurrences of $ 3 $ . Note that the streak can also be $ 10 $ days (by removing the $ 10 $ -th day from this streak) but we are interested in the longest streak.

In the fourth example, if we take the streak of the first $ 6 $ days, we can remove the third day from this streak then all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ will occur exactly once.

## 样例 #1

### 输入

```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```

### 输出

```
13```

## 样例 #2

### 输入

```
5
10 2 5 4 1
```

### 输出

```
5```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
1```

## 样例 #4

### 输入

```
7
3 2 1 1 4 5 1
```

### 输出

```
6```

## 样例 #5

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
5```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF1163B1)

### 思路

我们发现题面中的 $u_i\le10$，数据十分小，可以利用这一点解题。我们用 $C_x$ 表示 $x$ 总共出现的次数，再用 $S_y$ 表示 $y$ 在 $C_x$ 中的次数。

然后，用循环变量 $i$，遍历 $u$，先将 $S$ 与 $C$ 按照新的 $u_i$ 更新。然后判断 $S$ 中的第 $1$ 个点，第 $i$ 个点，以及 $C_{u_i}$ 中的最大值 $M$ 以及 $M-1$ 的点是否满足题目条件即可。

### 过程

读入 $n$，$u_i$。

循环变量 $i$ 遍历 $1$ 到 $n$：

> 更新 $S$ 与 $C$，即：$S_{C_{u_i}}\gets S_{C_{u_i}}-1$，$C_{u_i}\gets C_{u_i}+1$，$S_{C_{u_i}}\gets S_{C_{u_i}}-1$。
>
> 然后更新最大值 $M$：$M=\max(M,C_{u_i})$。
>
> 判断，如果满足以下任意一条，则将答案更新为 $i$：
> - $S_i=1$ 或 $S_1=i$；
> - $S_1=1$ 且 $S_M\times M=i-1$；
> - $S_M=1$ 且 $S_{M-1}\times(M-1)+M=i$；
> 

输出答案。

**注意事项**

- 注意特判 $i=1$ 的情况。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
int a[N],sum[N],cnt[20];
int main(){
	int n=read();
	if(n==1)
		return printf("1\n"),0;
	for(int i=1;i<=n;++i)
		a[i]=read();
	--sum[cnt[a[1]]],++cnt[a[1]],++sum[cnt[a[1]]];
	int maxx=cnt[a[1]],ans=0;
	for(int i=2;i<=n;++i){
		--sum[cnt[a[i]]],++cnt[a[i]],++sum[cnt[a[i]]];
		maxx=max(maxx,cnt[a[i]]);
		if(sum[i]==1||sum[1]==i||sum[1]==1&&sum[maxx]*maxx==i-1||sum[maxx]==1&&sum[maxx-1]*(maxx-1)+maxx==i)
			ans=i;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1163B1)

## 思路

我们可以将可选的前缀分为以下情况：
1. 每种数都只有 $1$ 个。
2. 有一种数只有 $1$ 个，其他数出现的数量一样。
3. 有一种数比其他数多出现 $1$ 次，其他数出现的的次数一样。

而且以上三种情况可以分别转化为以下三种：
1. 出现数量最多的数出现了 $1$ 次。
2. 出现数量最多的数每种数的数量与出现数量最多的数有多少种的乘积为 $k - 1$（剩下的那个是只出现了一次的那个数）。
3. 出现数量第二多的数每种数的数量与出现数量第二多的数有多少种的乘积加上出现数量最多的数每种数的数量为 $k$。

我们可以发现转化后的三种情况的非常数值只有：出现数量最多的数每种数的数量、出现数量最多的数有多少种、出现数量第二多的数每种数的数量、出现数量第二多的数有多少种、$k$。

## 具体过程

每输入一个数就进行以下操作：
* 分别判定断 $a_{i}$ 在 $[1, i - 1]$ 中出现的数量 $cnt_{a_{i}}$ 是否等于最大出现数量 $mx$ 或第二大出现数量 $mx2$，如果是则将其对应的种数 $cntmx$ 或 $cntmx2$ 减 $1$。
* 将 $cnt_{a_{i}}$ 加 $1$（统计上第 $i$ 个数 $a_{i}$）。
* 分别判断 $a_{i}$ 在 $[1, i]$ 中出现的数量 $cnt_{a_{i}}$ 是否等于最大出现数量 $mx$ 或第二大出现数量 $mx2$，如果是则将其对应的种数 $cntmx$ 或 $cntmx2$ 加 $1$。
* 判断 $cnt_{a_{i}}$ 是否要替换 $mx$ 或 $mx2$，如果是则替换并更新 $cntmx$ 与 $cntmx2$。
* 判断是否可以让 $k = i$，以下三种情况时可以：
  1. $mx = 1$。
  2. $mx \cdot cntmx + 1 = i$。
  3. $mx2 \cdot cntmx2 + mx = i$。

输出最大的 $k$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const int maxn = 1e5 + 10;
const int maxval = 1e5 + 10;

int n;
int a[maxn];

int mx, cntmx, mx2, cntmx2, ans;
int cnt[maxval], cntcnt[maxn];

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {
		scanf("%i", &a[i]);
		
		if (cnt[a[i]] == mx) {
			--cntmx;
		}else if (cnt[a[i]] == mx2) {
			--cntmx2;
		}
		cnt[a[i]]++;
		if (cnt[a[i]] == mx) {
			++cntmx;
		}else if (cnt[a[i]] == mx2) {
			++cntmx2;
		}
		if (cnt[a[i]] > mx) {
			mx2 = mx;
			cntmx2 = cntmx;
			mx = cnt[a[i]];
			cntmx = 1;
		}else if (cnt[a[i]] < mx && cnt[a[i]] > mx2) {
			mx2 = cnt[a[i]];
			cntmx2 = 1;
		}
		if (mx == 1/*每种数只有一个*/ || cntmx*mx == i - 1/*一个种只有一个*/ || cntmx2*mx2 + mx == i/*一种多一个*/) {
			ans = i;
		}
	}
	
	printf("%i", ans);
}
```

---

## 作者：czh___ (赞：0)

题意：有最多 $10$ 种颜色，要求一个最大的 $x$，使得在前 $x$ 个颜色中移除某个颜色，所有出现过的颜色出现次数相等。

题解：数组标记法。

用 $a$ 数组标记条纹出现的次数，$b$ 数组标记出现次数的次数，当 出现次数乘出现次数的次数等于循环时的 $i$ 时，所求的最大 $x$ 便是下一个 $i$；当出现次数乘出现次数的次数等于上一个循环的 $i$，所求的最大 $x$ 便此时的 $i$。

代码：

```cpp
#include<bits/stdc++.h>
const int manx=1e5+5;
using namespace std;
long long a[manx],b[manx];
int main(){
    int n,x;
    cin>>n;
    long long ans=1;
    for(int i=1;i<=n;i++){
        cin>>x;
        a[x]++;
        b[a[x]]++;
        if(a[x]*b[a[x]]==i&&i!=n) ans=i+1;
        if(a[x]*b[a[x]]==i-1) ans=i;
    }
    cout<<ans;
    return 0;
}
```

[改编于](https://blog.csdn.net/JiangHxin/article/details/90383018?ops_request_misc=&request_id=&biz_id=102&utm_term=CF1163B1%20Cat%20Party%20(Easy%20Editi&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90383018.142^v101^pc_search_result_base7&spm=1018.2226.3001.4187)

---

## 作者：yyycj (赞：0)

## 原题跳转
[CF1163B1 Cat Party (Easy Edition)](http://codeforces.com/problemset/problem/1163/B1)

## 题目简述
给定序列 $u$，要求 $u_{1} \sim u_{x}$ 在**必须**去掉一个元素后，使所有的数字出现次数相同，求 $x$ 的最大值。

## 主要思路
首先，先要明确可以满足条件的四种序列：
- **所有**元素均相同。
- **所有**元素各不相同。
- **只有一个**元素的出现次数为一，其他全部相同。
- 所有元素的出现次数均相同，**只有一个**比其他出现次数大一。

要判断这些情况，可以用一个计算每个元素出现次数和一个统计每种出现次数的出现次数的 `map`（这里可能有些绕，主要意思是假如有三个 $1$ 和三个 $2$，那么 `map` 中的键为 $3$，对应的值为 $2$，表示出现次数为 $3$ 的元素有 $2$ 个），`map` 的好处就是自动排序且可以获得长度。

### 处理数组和 `map`
由于是从第一个元素开始，所以可以边读入边操作。

每次多增加一个元素，那么这个元素在增加之前的出现次数的出现次数就会少 $1$。  

但是如果这个元素是第一次出现，那么元素出现次数 $0$ 的出现次数就会被减少，所以需要特判；或者在删除后，如果这个元素增加之前的出现次数的出现次数等于 $0$ 的话，就需要在 `map` 中删除，这两种情况如果不判断会让长度出现问题。  

随后将元素出现个数增加后出现次数的出现次数加 $1$。

### 判断所有元素是否均相同
如果出现了这种情况，就说明输入的 $i$ 个元素全部相同，那么 `map` 的长度一定为 $1$，且唯一的元素的键为 $i$，值为 $1$（值无需判断），表示出现次数为 $i$ 的数有 $1$ 个。

### 判断所有元素是否各不相同
如果出现了这种情况，那么 `map` 的长度也为 $1$，且唯一的元素的键为 $1$，值为 $i$（值无需判断），表示出现次数为 $1$ 的数有 $i$ 个。

### 判断是否只有一个元素的出现次数为一，其他全部相同
如果出现了这种情况，那么 `map` 的长度一定为 $2$，且由于 `map` 自动排序的特性，第一个元素的键和值一定都为 $1$，表示有出现次数为 $1$ 的有 $1$ 个。

### 判断是否所有元素的出现次数均相同，只有一个比其他出现次数大一
如果出现了这种情况，那么 `map` 的长度也为 $2$。由于 `map` 自动排序的特性，第二个元素的键一定比第一个元素的键大 $1$，且值为 $1$，表示比其他元素出现次数大 $1$ 的有 $1$ 个。

## [AC Code](https://www.luogu.com.cn/paste/e9ami387)

---

## 作者：dingzj2022 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1163B1)

## 思路：
列出所有的情况，然后依次归纳一下就好了。

只有一个数字时，那么结果就是 $1$。

利用 $sum$ 数组记录数字出现的次数，用 $cnt$ 记录 $sum$ 出现的次数。

## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long//不开long long 见祖宗，虽然这里好像不用开 
using namespace std;
const int N=1e6+10;
int a[N],sum[20],cnt[N];
signed main(){
	int n,ans,mx;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[sum[a[i]]]--;
		sum[a[i]]++;
		cnt[sum[a[i]]]++;
		if(i==1) mx=sum[a[i]];
		else mx=max(mx,sum[a[i]]);
		if(i==1) ans=i;
		else if(cnt[i]==1 || cnt[1]==i) ans=i;
		else if(cnt[1]==1 && cnt[mx]*mx==i-1) ans=i;
		else if(cnt[mx]==1 && (mx-1)*cnt[mx-1]+mx==i) ans=i;
	}
	cout<<ans;
	return 0;
}
```
~~不喜勿喷~~谢谢观看！

---

## 作者：___nyLittleT___ (赞：0)

# CF1163B1	Cat Party (Easy Edition) 题解 
[题目传送门](https://www.luogu.com.cn/problem/CF1163B1/)
## 思路
分析一下题目，如果是一个满足要求的序列，那么应满足以下几个要求中的一个：  
- 只有 $1$ 个数出现次数为 $1$，其余的出现次数均相同，比如 `1 2 2 3 3`，只要删去出现次数为 $1$ 的那一个数。  
- 只有一个数的出现次数比其他的出现次数多 $1$，比如 `1 1 1 2 2 3 3`，只要删去一个多的数。  
- 出现次数均为 $1$，比如 `1 2 3 4 5 6 7`，不管删哪个数都不会影响。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,ans,maxm=-0x7f7f7f7f;
int u[maxn];   //题意所示
int cnt[maxn]; //记录出现次数
int del[maxn]; //删除分类讨论 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&u[i]); //读入
		del[cnt[u[i]]]--;     
		del[++cnt[u[i]]]++;//记录次数
		maxm=max(maxm,cnt[u[i]]);
		if(maxm==1||del[maxm]*maxm+1==i||(del[(maxm-1)]+1)*(maxm-1)+1==i) ans=i;
	} 
	printf("%d",ans);
	return 0;
}
```   

---

## 作者：Ag2WO4 (赞：0)

考虑以下几种可行的结构：

1. 所有数都一样，此时删除任意一个都不影响（其他数都是零个）。
2. 有一个数只有一个（其他数的个数都一样，无论是一个还是多个），删除它即可。
3. 有一个数比别的数多一个，删除它即可。

接下来，考虑可行的数据结构：统计每个数的数量，再统计数量的数量。这里用 Python 3 的字典来实现。然后分析：

1. 若数量多于三种，那显然不可能。
2. 若数量为两种，考虑第二种情况和第三种情况。由于字典只有两项，分别提取，看有没有某一项的值是一，以及这一项是不是一或比另一项多一。
3. 若数量为一种，考虑第一种和第二种情况的特例（每种数都只有一个）。此时，要么项为当前前缀的长度（第一种），要么项为一（第二种）。

通过统计数量和数量的数量的数据结构是可以做到 $O(n)$ 的。
#### 代码
```python
input();b={};c={};x=y=0
for i in map(int,input().split()):
    x+=1
    if i in b:
        c[b[i]]-=1
        if c[b[i]]==0:del c[b[i]]
        b[i]+=1
        if b[i]in c:c[b[i]]+=1
        else:c[b[i]]=1
    else:
        b[i]=1
        if 1 in c:c[1]+=1
        else:c[1]=1
    if len(c)==1:
        if 1 in c:y=x
        elif x in c:y=x
    if len(c)==2:
        if 1 in c:
            if c[1]==1:y=x
        d,e=c.keys()
        if d==e+1 and c[d]==1:y=x
        elif e==d+1 and c[e]==1:y=x
print(y)
```

---

## 作者：_little_Cabbage_ (赞：0)

# CF1163B1 Cat Party (Easy Edition)题解
~~[博客观看食用更佳](https://www.luogu.com.cn/blog/958804/solution-cf1163b1)~~

这题其实非常水。

根据题意，我们可以知道在子序列 $[1,x]$ 中，要满足**其中任一元素后每个数出现的次数相同**这个条件，有如下三种情况：
- 所有元素出现次数都为 $1$，如序列 $[1,2,3,4,5]$
- 除了一个出现次数为 $1$ 的元素，其他元素的出现次数都相等，如序列 $[1,2,2,3,3,4,4,5,5]$
- 除了一个出现次数比其他数的出现次数多 $1$ 的元素，其他元素的出现次数都相等，如序列 $[1,1,2,2,3,3,4,4,4,5,5]$

为什么呢？

让我们来分析一下：
- 对于第一种情况，以序列 $[1,2,3,4,5]$ 为例，删除其中任何一个数以后都能满足**其中任一元素后每个数出现的次数相同**
- 对于第二种情况，以序列 $[1,2,2,3,3,4,4,5,5]$ 为例，删除 $1$ 以后就能满足**其中任一元素后每个数出现的次数相同**
- 对于第三种情况，以序列 $[1,1,2,2,3,3,4,4,4,5,5]$ 为例，删除任意一个 $4$ 以后就能满足**其中任一元素后每个数出现的次数相同**

这样就很容易写出AC代码了。

AC代码：
```cpp
#include<bits/stdc++.h>
#define caozuo ret[cnt[u[i]]]--;cnt[u[i]]++;ret[cnt[u[i]]]++;
using namespace std;
int cnt[100010],ret[100010],u[100010];
int main()
{
	int n;
	scanf("%d",&n);
	int ans=0;
	int mx=INT_MIN;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&u[i]);
		caozuo
		mx=max(mx,cnt[u[i]]);
		if(mx==1)
		{
			ans=i;
			continue;
		}
		if(ret[mx]*mx==i-1)
		{
			ans=i;
			continue;
		}
		if((ret[(mx-1)]+1)*(mx-1)==i-1)
		{
			ans=i;
			continue;
		}
	}
	printf("%d",ans);
}
```
[AC记录](https://www.luogu.com.cn/record/135890517)

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1163B1)

### 题意
给定一个长度为 $n$ 的序列，从这个序列的第一项开始，长度为 $x$ 的子序列满足去掉其中任一元素后每个数出现的次数相同，求 $x$ 的最大值。

### 分析

序列的子序列 $[1,x]$ 中，去掉其中任一元素后每个数出现的次数相同，很显然分为 $3$ 种情况：

- 每一种元素均出现了 $1$ 次

- 元素中有一种元素出现了 $1$ 次，其余出现的次数相同

- 元素中有其他元素出现次数相等，一种元素比其他元素次数多 $1$ 次

下面对这三种情况进行分析：

#### 每一种元素均出现了 $1$ 次

从 $1$ 遍历到 $n$，每次输入统计子序列 $[1,i]$ 每种元素出现的次数，然后统计所有颜色次数的最大值，如果为 $1$，就符合题意，更新答案为当前序列的长度。

#### 元素中有一种元素出现了 $1$ 次，其余出现的次数相同

统计每一种颜色出现的次数，再统计其中的最小值，如果为 $1$ 且其他相等那么符合题意，更新答案为当前序列的长度。

#### 元素中有其他元素出现次数相等，一种元素比其他元素次数多 $1$ 次

统计每一种颜色出现的次数，再统计其中的最大值，如果其他相等，而且最大值比其他的大 $1$，那么符合题意，更新答案为当前序列的长度。

那么，我们可以写出本题的 AC 代码。

### 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/wfvgjutb)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,maxinum = -10,x = 0,a[100010],b[100010],u[100010],i;
    cin >> n;
    for(i = 1;i <= n;i++)                                                            
	{
		cin >> u[i];
	} 
    for(i = 1;i <= n;i++)
    {
        int p = b[u[i]];
        a[p] -= 1;
        b[u[i]] += 1;
        p += 1;
        a[p] += 1;
        maxinum = max(b[u[i]],maxinum);
        if (((maxinum == 1) || (a[maxinum] * maxinum == i - 1)) || (((maxinum - 1) * (a[maxinum - 1] + 1)) == i - 1)) x = i;
    }
    cout << x << endl;
    return 0;
}

```




---

## 作者：_Fontainebleau_ (赞：0)

我们发现， $x$ 若要满足题目条件，则 $[1,x]$ 中，要么所有颜色出现次数全为 $1$ ；要么只有一个颜色出现次数为 $1$ ，其余都相等；要么其余出现次数相等，只有一个颜色出现次数比其余颜色出现次数大 $1$ 。

我们不妨用 $cnt_i$ 表示颜色 $i$ 出现次数， $num_i$ 表示出现了 $i$ 次的颜色共几种，然后一边读入，一边做。
```cpp
//1:全为1
//2:只有一项为1，其他都相等
//3：其他出现次数相等，最高出现次数比其他大1 
#include<bits/stdc++.h>
using namespace std;
int n;
int cnt[100005],num[100005];//cnt[x]->x当前出现次数,num[x]->出现次数为x的出现次数 
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int main()
{
    n=read();
    int mx=-2e9,p=0;
    for(int i=1;i<=n;i++)
    {
        int x=read();
        num[cnt[x]++]--;
        num[cnt[x]]++;
        mx=max(mx,cnt[x]);
        if(mx==1)   p=i;//case 1
        else if((num[mx-1]+1)*(mx-1)==i-1)  p=i;//case 3这里建议好好想想为什么
        else if(num[mx]*mx==i-1)    p=i;//case 2
    }
    printf("%d\n",p);
    return 0;
}
```
 

---

