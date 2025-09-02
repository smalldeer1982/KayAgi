# Riverside Curio

## 题目描述

Arkady decides to observe a river for $ n $ consecutive days. The river's water level on each day is equal to some real value.

Arkady goes to the riverside each day and makes a mark on the side of the channel at the height of the water level, but if it coincides with a mark made before, no new mark is created. The water does not wash the marks away. Arkady writes down the number of marks strictly above the water level each day, on the $ i $ -th day this value is equal to $ m_{i} $ .

Define $ d_{i} $ as the number of marks strictly under the water level on the $ i $ -th day. You are to find out the minimum possible sum of $ d_{i} $ over all days. There are no marks on the channel before the first day.

## 说明/提示

In the first example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/ad72072688b34b2729139a36473993902a371313.png)Note that on day $ 3 $ , a new mark should be created because if not, there cannot be $ 3 $ marks above water on day $ 4 $ . The total number of marks underwater is $ 0+0+2+0+3+1=6 $ .

In the second example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/193fbf53ff0eac39a568b94979481249f6765c97.png)

## 样例 #1

### 输入

```
6
0 1 0 3 0 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
0 1 2 1 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
0 1 1 2 2
```

### 输出

```
0
```

# 题解

## 作者：Wf_yjqd (赞：2)

一堆单调栈的，不是很理解（大佬轻喷），写篇通俗易懂的题解。

------------

此题翻译很不友好，读了一遍又一遍还是不懂。

一句话解释一下（搬的）：每天在当前水位刻一条线，如果这个水位上以前已经刻过了就不用重复再刻，输入的 $m_i$ 是每天水位以上有多少条刻线（第一天开始的时候保证是没刻线的），问 $n$ 天里水位以下刻线的总数的最小值。

显然，水位以上的个数都给出，以下的个数和取决于总个数和。

又由于刻线个数是单调不减的，只需要尽可能多重复，就可以让总个数和取最小值。

很快就能想到，个数每天最多增加 $1$，于是倒序维护第 $i$ 天可能的最少个数 $f_i=\max(m_i,f_{i+1}-1)$。

前文提到，刻线个数是单调不减的，所以再求前缀最大值。

具体地说就是，正序枚举 $i$，更新 $f_i$ 为 $\max(f_i,f_{i-1})$。

最后，水位以下的刻线个数等于总个数减去水位以上的个数，即 $d_i=f_i-m_i$。

输出答案 $\sum_{i=1}^{n}d_i$。

------------

这么简单的代码应该没有人看吧。

不过记得看数据范围。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//不开long long见祖宗
const ll maxn=2e5;
ll n,ans,a[maxn],f[maxn];
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        ans-=a[i];
    }
    for(ll i=n;i>=1;i--)
        f[i]=max(a[i],f[i+1]-1);
    for(ll i=1;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
        ans+=f[i];
    }
    printf("%lld\n",ans);
    return 0;
}//tjnlyy
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1700}$
---
### 解题思路：

容易发现划线的思路就是让重合的线尽可能多，如果重合的线一样多，则尽可能把线往前放。

对于一个要求 $m_i$ 条不一样的线的位置，在其前面能够重合的线的数量为 $i-1-m_i$，想到直接求出哪些位置是可以重合的，最后直接计算。

维护一个栈，内部存储所有的在当前限制下可以重合的位置，对于一个新的位置，用这个位置的限制决定前一个位置是否可以放进栈内，或者是应当从栈中弹出若干元素以满足限制。

需要注意的是如果当前位置的线被划在了最下面，则这个位置在之后不能被考虑重合。边界上注意如果最后一个位置可以被考虑重合，则重合一定更优。

思路比较简单，细节还挺麻烦的。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=100005;
int n,m[MAXN],x[MAXN],tot,v[MAXN],now=1,ans,sum;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&m[i]);
		if(v[i-1]==1)x[++tot]=i-1;
		tot=min(tot,i-1-m[i]);
		v[i]=(m[i]<i-1-tot);
	}
	if(v[n])x[++tot]=n;
	for(int i=1;i<=n;i++){
		if(x[now]==i&&now<=tot){
			now++;
			ans+=sum-m[i]-1;
			continue;
		}
		ans+=sum-m[i];
		sum++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：尹昱钦 (赞：0)

## 解题思路
**贪心**：很显然的结论是，要**尽可能多的重复**。

但是也不能每次都重复：

假设第 $i$ 天 $m_i=4$，那么到第 $i$ 天至少要保证已经有四条线，也就是说前 $i-1$ 天最多重复 $i-5$ 条。

所以我们用一个**单调栈**维护一个最长的 $(i-m[i])$ **上升后缀**，这也就求出了每一段区间的重复的条数。

最后统计答案即可。

细节还是很多的。

## AC代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
const int maxn=100005;
int n,a[maxn],b[maxn],c[maxn],num,res,cnt;
long long ans;
stack<int> s;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
    	if(s.empty()){
    		s.push(i);
    		continue;
		}
		while((!s.empty())&&(s.top()-a[s.top()]>=i-a[i])) s.pop();
		s.push(i);
	}
	while(!s.empty()){
		b[++cnt]=s.top();
		c[cnt]=b[cnt]-a[b[cnt]]-1;
		s.pop();
	}
	res=cnt;
	for(int i=1;i<=n;i++){
		if(res>1&&i>b[res]) res--;
		if(i-num>c[res]) num++;
		ans=ans+(num-a[i]-1);
	} 
	cout<<ans;
    return 0;
}
```


---

## 作者：C20203030 (赞：0)

## 一、题目
[点此看题](https://www.luogu.com.cn/problem/CF924C)
## 二、解法
玄学警告⚠，由于线上的数量是定值，转而求线的数量已推知线下数量。

设$t[i]$为$i$时刻线的数量，$d[i]$为线下的数量，易知 $t[i]=m[i]+d[i]+1$，有这样一些限制：
- $t[i]\geq t[i-1]$，即线的数量单调递增
- $t[i]\geq m[i]$，这个看定义吧
- $t[i]-1\leq t[i-1]$，即每天只能画一条线

前两个限制取最大值，第三个限制从后往前扫，把$t[i]$和$t[i+1]-1$取$max$，最后扫一遍就可以算出答案，时间复杂度$O(n)$。

那么这个算法的正确性如何推知呢？我的理解是我们尽可能贴着$1,2$限制的边界也就是尽量把线画重，因为线的数量越少越好，后面我们要扫回来的原因是我们贴着边界画不一定画的出来合法解，我们需要把以前画重的线拆开，以满足后面的需要。

```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int M = 100005;
int read()
{
 int x=0,flag=1;char c;
 while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
 while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
 return x*flag;
}
int n,ans,m[M],t[M];
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
        t[i]=max(t[i-1],(m[i]=read())+1);
    for(int i=n-1;i>=1;i--)
        if(t[i+1]-1>t[i])
            t[i]=t[i+1]-1;
    for(int i=1;i<=n;i++)
        ans+=t[i]-m[i]-1;
    printf("%lld\n",ans);
}

```



---

