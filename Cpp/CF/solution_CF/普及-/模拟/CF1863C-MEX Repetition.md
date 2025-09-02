# MEX Repetition

## 题目描述

You are given an array $ a_1,a_2,\ldots, a_n $ of pairwise distinct integers from $ 0 $ to $ n $ . Consider the following operation:

- consecutively for each $ i $ from $ 1 $ to $ n $ in this order, replace $ a_i $ with $ \operatorname{MEX}(a_1, a_2, \ldots, a_n) $ .

Here $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_m $ is defined as the smallest non-negative integer $ x $ which does not occur in the collection $ c $ . For example, $ \operatorname{MEX}(0, 2, 2, 1, 4) = 3 $ and $ \operatorname{MEX}(1, 2) = 0 $ .

Print the array after applying $ k $ such operations.

## 说明/提示

In the first test case, here is the entire process:

1. On the first operation, the array changes from $ [1] $ to $ [0] $ , since $ \operatorname{MEX}(1) = 0 $ .
2. On the second operation, the array changes from $ [0] $ to $ [1] $ , since $ \operatorname{MEX}(0) = 1 $ .

Thus, the array becomes $ [1] $ after two operations.

In the second test case, the array changes as follows during one operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 1, 3] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 3] \rightarrow [2, 0, {\mkern3mu\underline{\mkern-3mu {\bf 3}\mkern-3mu}\mkern3mu}] \rightarrow [2, 0, 1] $ .

In the third test case, the array changes as follows during one operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 2] \rightarrow [1, {\mkern3mu\underline{\mkern-3mu {\bf 2}\mkern-3mu}\mkern3mu}] \rightarrow [1, 0] $ . And during the second operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 0] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}] \rightarrow [2, 1] $ .

## 样例 #1

### 输入

```
5
1 2
1
3 1
0 1 3
2 2
0 2
5 5
1 2 3 4 5
10 100
5 3 0 4 2 1 6 9 10 8```

### 输出

```
1
2 0 1
2 1
2 3 4 5 0
7 5 3 0 4 2 1 6 9 10```

# 题解

## 作者：Aisaka_Taiga (赞：2)

### 题意

多组数据。

给你一个长度为 $n$ 的序列，里面是互不相同的 $0\sim n$ 的整数，定义一次操作为：

对于序列里的每一个数 $a_{i}$，将他替换成序列中最小的未出现的自然数。

然后求进行 $k$ 次操作后的序列。

### Solution

我们手模一下样例里的 `0 1 3`。

发现进行一次操作后是 `2 0 1`。

进行第二次操作后是 `3 2 0`。

进行第三次操作后是 `1 3 2`。

进行第四次后就是 `0 1 3`。

我们发现是循环的，我们把 $2$ 加到一开始的里面，得到：

```
0 1 3 2
2 0 1 3
3 2 0 1
1 3 2 0
0 1 3 2
```

循环起来了，而且都往右平移了一位。

具体细节看代码：

```cpp
/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-08-30 23:47:51
 * @LastEditTime: 2023-08-30 23:48:03
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\CFC.cpp
 * 心比天高，命比纸薄。
 */
#include <bits/stdc++.h>

#define int long long
#define N 1000100

using namespace std;

int t, n, m, a[N], ans[N], vis[N];

signed main()
{
    cin >> t;
    while(t --)
    {
        cin >> n >> m;
        m %= n + 1;
        int cao = -1;
        for(int i = 0; i <= n; i ++) vis[i] = 0;
        for(int i = 1; i <= n; i ++) cin >> a[i], vis[a[i]] ++;
        for(int i = 0; i <= n; i ++) if(!vis[i]) cao = i;
        a[n + 1] = cao;
        for(int i = 1; i <= n + 1; i ++) ans[(m + i) % (n + 1)] = a[i];
        for(int i = 1; i <= n ; i ++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

乍一看，感觉无从下手，于是就先列举了几个例子：

```
02
10
21
02
 
013
201
320
132
013
 
12345
01234
50123
45012
34501
23450
12345
```

容易发现周期是 $n+1$，下面解释理由：

首先因为数量 $n$，且两两各不相同，而值域是 $[0,n]$，所以在 $[0,n]$ 中，每个数最多存在一个，且有一个数是不存在的，我们假设是 $p$。

那么对于 $a_1$，第一次一定变为 $p$，于是这个数列中不存在的数就变成原来的 $a_1$ 了，所以 $a_2$ 就会变成原来的 $a_1$，以此类推，第一次操作后，等于是把数组最后一位删去，整体往后挪一位，然后把第一位变成 $p$。

就这样不断地操作，经过 $n$ 次，$p$ 就会被挪到最后一位，然后下一次就会变为原样，所以周期是 $n+1$。

但是发现直接暴力还是会 TLE，所以做法肯定还要文雅些，既然都在之前找到规律了，我们就可以用上面的规律。

假设 $k$ 是取模后的 $k$，那么第 $k$ 为一定是 $p$，对于 $k$ 前面的位置，应该就是原数组的后半段，比如，第 $k-1$ 就是 $a_n$，所以可以直接计算得到原数组的位置，对于 $k$ 后面的位置，也可以同理推出对应的原数组的位置。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k,a[100005];
set<int>s;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k),k%=n+1;
		for(int i=0;i<=n;++i) s.insert(i);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]),s.erase(a[i]);
		auto i=s.begin();int p=*i;
		if(!k){for(int i=1;i<=n;++i) printf("%d ",a[i]);puts("");}
		else
		{
			for(int i=1;i<=n;++i)
			{
				if(i<k) printf("%d ",a[n-k+i+1]);
				else if(i==k) printf("%d ",p);
				else printf("%d ",a[i-k]);
			}
			puts("");
		}
		s.erase(p);
	}
	return 0;
}
```

---

## 作者：11514zbs (赞：0)

看到题目，貌似没什么头绪，所以拿样例来找找规律：

```
1 2 3 4 5
0 1 2 3 4
5 0 1 2 3
4 5 0 1 2
3 4 5 0 1
2 3 4 5 0
1 2 3 4 5

```

虽然变成了一个循环，但看起来还是没有什么规律，于是我们把 $\operatorname{mex}(a_1, a_2, \cdots , a_n)$ 加到循环的开头：

```
0 1 2 3 4 5
5 0 1 2 3 4
4 5 0 1 2 3
3 4 5 0 1 2
2 3 4 5 0 1
1 2 3 4 5 0
0 1 2 3 4 5

```

这时候我们就会发现，每进行 $1$ 次操作，所有的数会往右移 $1$ 位，而最右边的数会移到最左边。

又因为每移动 $n + 2$ 次就是不变的，所以我们把 $k$ 对 $n + 1$ 取模得到的结果是不变的。

最后，我们只要按照以下几个步骤写就可以了！

1. 把 $k$ 对 $n + 1$ 取模。

2. 把桶清空，用来统计 $\operatorname{mex}(a_1, a_2, \cdots, a_n)$ 的值。

3. 输入并统计哪些数是出现过的。

4. 寻找 $\operatorname{mex}(a_1, a_2, \cdots, a_n)$ 。

5. 用推出的式子直接将 $a_i$ 赋值给存储答案的数组。

6. 输出存储答案的数组。

```cpp
#include <cstdio>

long long T, b, n, k, m[1000005], s[1000005], v[1000005];

int main()
{
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld %lld", &n, &k);
		b = -1;
		k %= n + 1;
		for (long long i = 0; i <= n; i++) // 不能用 memset ，不然会 TLE 
		{
			v[i] = 0;
		}
		for (long long i = 1; i <= n; i++)
		{
			scanf("%lld", &m[i]);
			v[m[i]] = 1;
		}
		for (long long i = 0; i <= n; i++)
		{
			if (!(v[i]))
			{
				b = i;
				break; 
			}
		}
		m[n + 1] = b;
		for (long long i = 1; i <= n + 1; i++)
		{
			s[(k + i) % (n + 1)] = m[i]; // 是对 n + 1 取模，而不是 n + 2 ！
		}
		for (long long i = 1; i <= n; i++)
		{
			printf("%lld ", s[i]);
		}
		printf("\n");
	}
	return 0;
}

```

> 我讲的这么详细你们应该听得懂吧。

 ~~本蒟蒻的第二篇题解awa~~

---

## 作者：___nyLittleT___ (赞：0)

[题目传送门](luogu.com.cn/problem/CF1863C)  

## 明确
- $\operatorname{MEX}$ 是什么？在区间内未出现过的最小整数。


## 结论
用 $\operatorname{MEX}$ 替换 $n+1$ 次后序列会变回原来的样子。  

## 证明
在值域 $[0,n]$ 内没有重复的数，不妨设现在的 $\operatorname{MEX}$ 值为 $x \in [0,n]$。  
替换后变成 $[x,a_2,a_3,...,a_n]$，$\operatorname{MEX}$ 值为 $a_1$。  
再次替换后变成 $[a_n,x,a_2,...,a_{n-1}]$，值变为 $a_2$。  
再次替换后变为 $[a_{n-1},a_n,a_1,...,a_{n-2}]$，值变为 $a_3$。  

以此类推，替换第 $n+1$ 次后就会回到原样。  

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
ll t,n,m;
ll a[N],ans[N],cnt[N];
int main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld%lld",&n,&m);
		m%=n+1;
		int pos=-1;
		for(int i=0; i<=n; i++) cnt[i]=0;
		for(int i=1; i<=n; i++) scanf("%lld",&a[i]),cnt[a[i]]++;
		for(int i=0; i<=n; i++) if(!cnt[i]) pos=i;
		a[n+1]=pos;
		for(int i=1; i<=n+1; i++) ans[(m+i)%(n+1)]=a[i];
		for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1863C)

# 思路：

看到题目，让我们先来模拟一下。

$
\begin{array}{c}
\left \{1,2,3,4,5 \right\} \\
\left \{0,1,2,3,4 \right\} \\
\left \{5,0,1,2,3 \right\} \\
\left \{4,5,0,1,2 \right\} \\
\left \{3,4,5,0,1 \right\} \\
\left \{2,3,4,5,0 \right\} \\
\left \{1,2,3,4,5 \right\} \\
\end{array}
$
 
很容易知道，我们在替换时，第一个数总是在上次没出现的数。然后没出现的数就变成了刚才被替换掉的数。假设经过第 $i$ 次替换的序列中第 $j$ 个数是 $a_{i,j}$，那么有 $a_{i,1} = a_{i-2,n}$，$\forall j \in [2,n]$，$a_{i,j} = a_{i - 1,j - 1}$。

虽然我们推出了规律，但这玩意是 $O(nk)$ 的，会 TLE。但我们可以尝试找一找规律，如下。

$\begin{array}{c}
\left \{1,2,3,4,5,(0) \right\} \\
\left \{0,1,2,3,4,(5) \right\} \\
\left \{5,0,1,2,3,(4) \right\} \\
\left \{4,5,0,1,2,(3) \right\} \\
\left \{3,4,5,0,1,(2) \right\} \\
\left \{2,3,4,5,0,(1) \right\} \\
\left \{1,2,3,4,5,(0) \right\} 
\end{array}$
 
发现其实每次的只是相当于上一次平移了一下，因为当前没有的就是刚被替换掉的。于是只需要找到起始的数字就可以了。由于每次移动一个，初始的位置就是 $(1 - k) \bmod (n + 1)$。负数取模自行处理。答案从起始位置输出 $n$ 个就可以了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,k,a[N],b[N];
signed main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[a[i]]=1;
        }
        for(int i=0;i<=n;i++){
            if(!b[i]){
                a[0]=i;
                break;
            }
        }
        int s=(n+2-(k%(n+1)))%(n+1);
        for(int i=1;i<=n;i++,s++){
            cout<<a[s%(n+1)]<<" ";
        }
        cout<<endl;
        for(int i=0;i<=n;i++){
            b[i]=0;
        }
    }
    return 0;
}
```

---

## 作者：_czy (赞：0)

## 分析

由于值域 $[0,n]$ 且没有重复元素，又给出了 $n$ 个数，显然 $\operatorname{mex}=x$，$x$ 在 $[0,n]$。

当 $n=3$ 时：

序列初始为 $a_1,a_2,a_3$，所以 $\operatorname{mex}=x$。

替换得到 $x,a_2,a_3$，所以 $\operatorname{mex}=a_1$。

替换得到 $x,a_1,a_3$，所以 $\operatorname{mex}=a_2$。

所以第一次操作后序列为 $x,a_1,a_2$。

同理第二次为 $a_3,x,a_1$，第三次为 $a_2,a_3,x$。

第四次后变回 $a_1,a_2,a_3$，开始循环。

所以我们利用规律即可。

---

## 作者：Laisira (赞：0)

### 题面
给你一个长度为 $n$ 的序列，保证值域 $[0,n]$ 并且没有重复元素。

考虑一种操作：

- 从 $1$ 到 $n$ 对每个 $i$ 用数列最小的未出现的自然数换掉 $a_i$。

求操作 $k$ 次后的序列。


### 思路
容易想到，对于一个数列 $a$，每一次修改我们都是用没有的数依次替换每个数，即第一个被用没有的换，第二个被第一个换，以此类推。也就是说，每次修改后得到的数列是将没用的数连上 $1$ 到 $n-1$ 的数，剩下的一个是 $a_n$ 上一次操作的数。

因为换了 $n+1$ 次后第一个又回到了原来的数，后面的也是，及这是一个循环，循环节是 $n+1$。

然后按循环做就行啦，因为循环节 $n+1$，第 $k$ 次操作后的数列相当于第 $k \bmod (n+1)$ 次操作后。设想有无限个数列相连，显然每次移动相当于使用他编号加上的 $n+1-(k\bmod (n+1))$，也可以说减去 $k\bmod (n+1)$，求出来模一下就是在原数组的位置。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005 
using namespace std;
int a[Maxn],b[Maxn];
int main()
{
    int t,n,k;
    cin>>t;
    while(t--) {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
            cin>>a[i],b[i] = a[i];
        sort(b+1,b+1+n); b[0] = -1; b[n+1] = n+1;
        for(int i=0;i<=n;i++) if(b[i+1]-b[i] != 1) {
            a[0] = b[i]+1; break;
        } for(int i=1;i<=n;i++)cout<<a[(n+1-(k)%(n+1)+i)%(n+1)]<<" ";cout<<"\n";
    }
    return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 题意：
对于序列里的每一个数 $a_i$，将它换成 $MEX(a_1,a_2,\dots,a_n)$，$MEX$ 指不在数组中的最小非负整数。求操作 $k$ 次后的序列。
### 思路：
没思路？手玩样例！

把输入输出样例暴力一下。

注：分隔线是用来分隔题面要求计算的情况和不需计算的情况的。注意前面标`.`的情况。

**#1:**

* $k = 0$：$[1]$

  $k = 1$：$[0]$

* $k = 2$：$[1]$

**#2:**

* $k = 0$：$[0,1,3]$

  $k = 1$：$[2,0,1]$

  ------------

  $k = 2$：$[3,2,0]$

  $k = 3$：$[1,3,2]$

* $k = 4$：$[0,1,3]$

**#3:**

* $k = 0$：$[0,2]$

  $k = 1$：$[1,0]$

  $k = 2$：$[2,1]$
  
  ------------
  
  $k = 3$：$[0,2]$
  
**#4:**

* $k = 0$：$[1,2,3,4,5]$

  $k = 1$：$[0,1,2,3,4]$
  
  $k = 2$：$[5,0,1,2,3]$
  
  $k = 3$：$[4,5,0,1,2]$
  
  $k = 4$：$[3,4,5,0,1]$
  
  $k = 5$：$[2,3,4,5,0]$
  
  ------------

* $k = 6$：$[1,2,3,4,5]$

**#5：**

* $k = 0$：$[5,3,0,4,2,1,6,9,10,8]$

  $k = 1$：$[7,5,3,0,4,2,1,6,9,10]$
  
  ------------
  注：$10 + 1 = 11$，由于 $100 \bmod 11 = 1$，所以在这里分隔。
  
  $k = 2$：$[8,7,5,3,0,4,2,1,6,9]$
  
  $k = 3$：$[10,8,7,5,3,0,4,2,1,6]$
  
  $k = 4$：$[9,10,8,7,5,3,0,4,2,1]$
  
  $k = 5$：$[6,9,10,8,7,5,3,0,4,2]$
  
  $k = 6$：$[1,6,9,10,8,7,5,3,0,4]$
  
  $k = 7$：$[2,1,6,9,10,8,7,5,3,0]$
  
  $k = 8$：$[4,2,1,6,9,10,8,7,5,3]$
  
  $k = 9$：$[0,4,2,1,6,9,10,8,7,5]$
  
  $k = 10$：$[3,0,4,2,1,6,9,10,8,7]$
  
* $k = 11$：$[5,3,0,4,2,1,6,9,10,8]$

可知，$MEX$ 有一个循环，周期为 $n + 1$。所以实际计算的 $k$ 是 $k \bmod (n + 1)$。设它为 $len$。

找规律：
- 若 $len = 1$，则先输出 $MEX$，再输出 $a_1,a_2,\dots,a_{n - 1}$。
- 若 $len = n$，则先输出 $a_2,a_3,\dots,a_n$，再输出 $MEX$。
- 否则先输出 $a_{n - len + 2},a_{n - len + 3},\dots,a_n$，再输出 $MEX$，最后输出 $a_1,a_2,\dots,a_{n - len}$。

找到规律后，代码就很容易写了。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,k,len,i,a[100000];
bool bk[100001];//bk是在求 MEX 时用的标记数组
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//防 T 技巧（实际上也不一定会用）
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        memset(bk,false,sizeof(bk));//把标记数组重置
        for(i = 0;i < n;i++)
        {
            cin >> a[i];
            bk[a[i]] = true;//记录一下是否出现
        }
        for(i = 0;i <= n;i++)
            if(!bk[i])
            {
                m = i;//m 就是 MEX 的结果
                break;//防 T
            }
        len = k % (n + 1);//len 同上
        if(len == 1)//特判 len = 1
        {
            cout << m << ' ';
            for(i = 0;i < n - 1;i++)
                cout << a[i] << ' ';
            cout << '\n';
        }
        else if(len == n)//特判 len = n
        {
            for(i = 1;i < n;i++)
                cout << a[i] << ' ';
            cout << m << '\n';
        }
        else//按上面处理
        {
            for(i = n - len + 1;i < n;i++)//输出前半部分
                cout << a[i] << ' ';
            cout << m << ' ';
            for(i = 0;i < n - len;i++)//输出后半部分
                cout << a[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
```

---

## 作者：hfjh (赞：0)

# C. MEX Repetition

## 题意

给你一个长度为 $n$ 的序列，保证值域 $[0,n]$ 并且没有重复元素。

考虑一种操作：

- 从 $1$ 到 $n$ 对每个 $i$ 用 $\operatorname{MEX}(a_1,a_2,...,a_n)$ 换掉 $a_i$。

求操作 $k$ 次后的序列。

$n\le10^5,k\le10^9$ 。

## 题解

我们先手玩一下发现好像是循环的。

我们写个暴力打标出来发现真的是循环的。

![](https://cdn.luogu.com.cn/upload/image_hosting/33jsjcyz.png)

具体来说就是 $n+1$ 的排列，$p_{n+1}$ 位补上那个 $[1,n+1]$ 里面没出现过的数，每次整体向右移动一格。发现一个循环节长度 $n+1$，操作次数 $k \bmod (n+1)$。

证明如下：

每一次操作 $p_1$ 会被替换成没有出现过的数，然后 $p_2$ 又被替换成当前没出现过的数，也就是 $p_3$，依次替换 $p_3 \leftarrow p_2,p_4 \leftarrow p_3...$。

也就是整体向右移动一格。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, k, a[N], t[N], T;
void input(){
	cin>> n >> k;
	for(int i = 1; i <= n; ++i) cin>>a[i], t[a[i]] = 1;
	for(int i = 0; i <= n; ++i) if(!t[i]) a[n + 1] = i;
	++n;
	for(int i = 1; i <= n; ++i) a[i + n] = a[i];
	k = n - k % n + 1;
}
int main(){
	cin>>T;
	while(T--){
		for(int j = 0; j <= n; ++j) t[j] = 0;
		input();
		for(int i = 1; i <= n - 1; ++i) cout<<a[i + k - 1]<<' ';
		putchar('\n');
	}
}

```

---

## 作者：KeatonBinary (赞：0)

# Solution？
规律题，我们只需要找规律。~~证明留给 System Test~~
以样例二为例，我们记录下每次操作后的序列：$[0,1,3]\to[2,0,1]\to[3,2,0]\to[1,3,2]\to[0,1,3]$，发现**第一条规律**：变化具有周期性。但是为了在时限内通过此题，显然仅有这一条规律是不够的。我们再仔细观察一下变化的过程，发现前一次结果的开头部分与后一次结果的末尾部分完全一致，那么我们试着连起来：$0,1,3,2,0,1,3$，发现也是有周期性的，并且很容易就能得到**第二条规律**：变化本质是在这个结果序列上类似滑动窗口每次左移一个。如此一来就可以解决此题了。
# Code！
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int a[N], c[N];

int main() {
  int t, n, k, mex;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k), mex = 0;
    for (int i = 0; i <= n; ++i) c[i] = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i), c[a[i]] = 1;
      if (a[i] == mex)
        while (c[++mex])
          ;
    }
    a[0] = mex;
    k %= n + 1;
    for (int i = (1 - k + n + 1) % (n + 1), ii = 0; ii < n; ++ii) {
      printf("%d ", a[i++]);
      if (i > n) i = 0;
    }
    puts("");
  }
  return 0;
}
```

---

## 作者：NightmareAlita (赞：0)

## 简要题意

给定一个 $n$ 个元素的序列 $a$，其中的元素由小于等于 $n$ 的自然数构成且元素之间两两不同。现在定义一种操作，该操作会将第 $i$ 个位置的元素 $a_i$ 替换为该序列中当前没有的最小自然 数。每一轮操作都会从 $1$ 位置一直替换到 $n$。给定整数 $n,k$ 和序列 $a$，其中 $k$ 表示要进行 $k$ 轮操作，要求输出操作后的序列。

## 策略分析

题目中其实有一个诈骗条件。因为序列中的 $n$ 个元素包含小于等于 $n$ 的自然数且两两相同，所以我们可以发现，如果把原序列增加 $1$ 个元素，那么这个序列就变成了 $0 \sim n$ 的一个排列。而我们要替换用的那个数其实就是原序列中没有出现的那个数。我们发现，每当我们替换了一个数字，那么我们必然要用替换下来的这个数字去替换下一个数字，因为被替换下来的这个数字变成了当前序列中缺少的那个数。我们将最开始序列中缺少的那个数放在第 $n + 1$ 个位置。然后我们就可以显然地发现，每次操作实质上就是用第 $i$ 个位置的元素去替换第 $i+1$ 个位置的元素，推广到递推形式就是：
$$
a_{(i+1) \bmod (n+1)}= a_{i \bmod(n+1)}
$$
现在我们就知道了替换的方法，但是如果我们按照这个递推式进行模拟显然是行不通的，所以我们需要对这个做法进行优化。我们发现，每一轮操作结束后，都相当于把这个序列滚动一次，我们以下面的输入为例：

```
5 5
1 2 3 4 5
```

我们把没有出现的元素放在第 $n+1$ 个位置，然后我们每次进行一轮操作并记下来：

```
1 2 3 4 5 0
0 1 2 3 4 5
5 0 1 2 3 4
4 5 0 1 2 3
3 4 5 0 1 2 
2 3 4 5 0 1
1 2 3 4 5 0
```

于是我们就发现了，这种操作具有循环节，每一轮循环次数等于 $n+1$。原序列的元素顺序也没有太大的改变，所以我们就可以先确认没有第一次操作前没有出现的那个元素的位置，不难发现这个元素的位置等于 $k \bmod (n+1)$。那么我们就可以直接做了。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

namespace SHAWN {
    const int N = 1e5 + 7;
    int a[N];
    bool chk[N];
    int T, n, k;
    int work()
    {
        cin >> T;
        while (T--) {
            cin >> n >> k;
            for (int i = 1; i <= n; ++i) {
                cin >> a[i];    
                chk[a[i]] = true;
            }
            int fir;
            for (int i = 0; i <= n; ++i) {
            // 不想写二分了所以直接 O(n) 查
                if (!chk[i]) {
                    fir = i;
                    break;
                }
            }
            a[++n] = fir;
            int xh = k % n, cnt = n - 1;
            int idx = n - xh + 1;
            while (cnt--) {
                if (idx > n) { idx = 1; }
                cout << a[idx++] << ' ';
            }
            cout << '\n';
            memset(chk, 0, sizeof(chk));
        }
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```





---

