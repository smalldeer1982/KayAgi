# Restoration of the Permutation

## 题目描述

Let $ A={a_{1},a_{2},...,a_{n}} $ be any permutation of the first $ n $ natural numbers $ {1,2,...,n} $ . You are given a positive integer $ k $ and another sequence $ B={b_{1},b_{2},...,b_{n}} $ , where $ b_{i} $ is the number of elements $ a_{j} $ in $ A $ to the left of the element $ a_{t}=i $ such that $ a_{j}>=(i+k) $ .

For example, if $ n=5 $ , a possible $ A $ is $ {5,1,4,2,3} $ . For $ k=2 $ , $ B $ is given by $ {1,2,1,0,0} $ . But if $ k=3 $ , then $ B={1,1,0,0,0} $ .

For two sequences $ X={x_{1},x_{2},...,x_{n}} $ and $ Y={y_{1},y_{2},...,y_{n}} $ , let $ i $ -th elements be the first elements such that $ x_{i}≠y_{i} $ . If $ x_{i}&lt;y_{i} $ , then $ X $ is lexicographically smaller than $ Y $ , while if $ x_{i}&gt;y_{i} $ , then $ X $ is lexicographically greater than $ Y $ .

Given $ n $ , $ k $ and $ B $ , you need to determine the lexicographically smallest $ A $ .

## 样例 #1

### 输入

```
5 2
1 2 1 0 0
```

### 输出

```
4 1 5 2 3 ```

## 样例 #2

### 输入

```
4 2
1 0 0 0
```

### 输出

```
2 3 1 4 ```

# 题解

## 作者：_int123_ (赞：4)

题目：

## Restoration of the Permutation

### 题意：

给定正整数 $n,k$ 和序列 $B$，需要找到一个 $n$ 的全排列 $A$，使得 $B_i$ 可以表示，在 $A$ 中的元素 $i$ 的左边，满足 $a_j\geq i+k$ 的元素 $a_j$ 的个数。输出字典序最小的排列 $A$。



------------

### 主要思路：

首先，找出 $b$ 数组中第一个 $0$ 出现的位置（我们将此位置记为 $q$），然后将 $q$ 存入 $a$ 数组中，最后在每次操作后更新 $b$ 数组即可。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int a[1005],b[1005];
int n,k;
int main()
{
	scanf("%d%d",&n,&k);//输入 
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);//输入 
    for(int i=1;i<=n;i++)
    {
        int q=1;//定义一个 q 来记录 b 数组中非 0 个数 
        while(b[q]!=0) q++;//循环得到 q 
        a[i]=q;//存入数组 a 中 
        b[q]--;
        for(int j=1;j+k<=q;j++) b[j]--;//根据题目中的条件更新 b 数组 
    }
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return 0;
}
```

完结，撒花！！！

---

## 作者：2024sdhkdj (赞：3)

**[题目输送门](https://www.luogu.com.cn/problem/CF67B)**
## 题目大意：
~~题目有一些生涩难懂，读了好久~~ ，大概就是说给你 $n$ 和 $k$ 和一个序列 $b$，要你找到**另一个**序列 $a$ 表示 $a$ 中的 下标小于元素 $i$ 的下标的元素 中满足 $i+k \le a_j$ 的元素的个数。
## 算法分析：
我们可以先找到原数组 $b$ 中 $0$ 第一次出现的的位置 $wz$，已记录其中非零元素个数，然后将 $wz$ 存入答案数组 $a$ 中，那有些人会问了，为什么不直接输出而存入数组，这不是浪费空间吗？**注意：因为后面还要处理 $a[i+1]$ 的结果，如果直接输出循环后面的操作都不会记录**！！！最后，记得更新 $b$ 数组的值即可。
## 代码：
~~~
#include<bits/stdc++.h>
using namespace std;
int n,k,wz;
int a[10010],b[10010];
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//快读快写
    cin>>n>>k;
    for(int i=1;i<=n;i++)//输入
		cin>>b[i];
    for(int i=1;i<=n;i++){
    	wz=1;
        while(b[wz])//找非负元素的个数（wz）
			wz++;
        a[i]=wz;//处理
        b[wz]--;
        for(int j=1;j+k<=wz;j++)//每轮更新b数组
			b[j]--;
    }
    for(int i=1;i<=n;i++)//输出
		cout<<a[i]<<" "; 
    return 0;
}
~~~
[AC记录](https://www.luogu.com.cn/record/121663312)

~~[推广一下我的blog](https://www.luogu.com.cn/blog/hsb0507/)~~


---

## 作者：btng_smith666 (赞：3)

# 前言 ：

[CF67B题面传送门](https://www.luogu.com.cn/problem/CF67B)

[博客食用效果更佳](https://www.luogu.com.cn/problem/CF67B)

一道 $CodeForces$ 有趣的灰题（是的，什么题都很有意思）

# 主要思路 ：

此题就是定义两个序列 $A$ 和 $B$（也就是数组 $a$ 和数组 $b$ ），然后给出序列的长度 $n$ 和正整数 $k$ ，满足 $a_j \ge (i+k)$ ，经过一系列操作输出最小“词典”序列（读好题，不是字典序）。

本篇代码的主要做法就是定义一个用来执行操作的 $qwq$ ，用其先找到输入中数组 $b$ 中 $0$ 的位置，将 $0$ 前面的部分存到 $a$ 数组中，经过几次**简单的**循环判断和数字处理，每次 $qwq$ 的值存入 $a$ 数组中即可，详细的处理过程见下面的 $AC$ 代码

# Code :

```cpp
#include<bits/stdc++.h>//by btng_smith666 juruo
using namespace std;
int n,k,a[1001],b[1001],qwq;//qwq 的 qwq 
string fang_wei666="oh,i is a english men";//防抄袭 
int main()
{
    scanf("%d%d",&n,&k);//一些输入 
    for(int i=1;i<=n;i++)
    	scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)//主要部分 
    {
    	qwq=1;//注意 qwq 初始化为 1 ，与 i 的初始化是一样的 
        while(b[qwq]!=0)//循环判断 b[qwq] ，如果不是零，就累加 qwq  
            qwq++;//记录 b 数组非零个数 
        a[i]=qwq;//记录数组 a ，注意这里绝对不能把 qwq 直接输出，因为后面还要继续处理 a[i+1] 的结果，如果直接输出循环后面的操作都不会记录  
        b[qwq]--;//先-1 
        for(int j=1;qwq>=j+k;b[j]--,j++);//题目中的判断，累减数组 b[j] ，注意 b[j]-- 要在 j++ 前面 
    }
    for(int i=1;i<=n;i++)//输出答案 
    	printf("%d ",a[i]);
    return 0;
}
```

本篇题解到这里就结束啦，留下一个赞再去愉快地 $A$ 掉此题吧 qwq ！

---

## 作者：qwerty12346 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF67B)

## 题意

输出字典序最小的排列 $A$。

## 思路

这题就是定义两个数组 $a$ 和 $b$。然后给出数组的长度 $n$ 和正整数 $m$。满足 $a_{j}≥(i+k)$，经过一些操作输出最小词典数组 $a$。

循环里就是定义一个用来执行操作的 $ret$，用它先找到输入中，数组 $b$ 中 $0$ 的位置，将 $0$ 前面的部分存到数组 $a$ 中，再经过一些判断和处理，记得每次 $ret$ 的值都要存入数组 $a$ 中，最后在循环外面输出数组 $a$ 就可以了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10005],b[10005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++) 
    {
    	int ret=1;
        while(b[ret]!=0)ret++;
        a[i]=ret;//ret存入数组a中
        b[ret]--;
        for(int j=1;ret>=j+m;j++)b[j]--;
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<" "; 
    return 0;
}
```


---

## 作者：nightwatch.ryan (赞：1)

## 思路
定义两个数组 $(a,b)$，数组 $a$ 是最小词典数组（输出），数组 $b$ 输入。给定序列的长度 $n$ 和正整数 $k$，满足	$a_j≥(i+k)$。经过一些操作输出最小词典数组。循环里是
一个执行操作的 $res$，用 $res$ 先找到输入中数组 $b$ 中 $0$  的位置，将 $0$ 前面存到数组 $a$ 中，再经过一些判断和处理，每次 $res$ 的值都存入数组 $a$ 中，最后在循环外输出数组 $a$ 就可以了。
## 代码
```cpp
#include<iostream>
#define itn int 
#ifndef ONLINE_JUDGE
    freopen("Restoration of the Permutatio,in","r",stdin);
    freopen("Restoration of the Permutatio","w",stdout);
#endif
int main(){
	std::ios::sync_with_stdio(false);
	int n,k; std::cin>>n>>k;
	int a[10001],b[10001];
	for(int i=1;i<=n;i++){
		std::cin>>b[i];
	}
	for(itn i=1;i<=n;i++){
		int res=1;
		while(b[res]!=0){//判断b数组有几个非零的数 
			res++;//res+1 
		}
		a[i]=res;b[res]--;//把res存入数组a中，b[res]-1 
		for(int j=1;res>=j+k;j++){
			b[j]--;
		}
	}
	for(int i=1;i<=n;i++){//输出 
		std::cout<<a[i];
		std::cout<<" ";
	}
}
```

---

## 作者：谦谦君子 (赞：1)


**在b中第一个0出现的位置，放在a[1],这时候放b中最小的满足条件的值为1的值放在a[2]中,在程序中实现时更新b中得值，使满足aj>=i+k的b的下标cur(cur=aj)中得值减1就行了。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],b[1001];
int main()
{
    int n,k;
    while (scanf("%d%d",&n,&k)==2)
    {
        for (int i=1;i<=n;i++)
        {
            cin>>b[i];
        }
        for (int i=1;i<=n;i++)
        {
            int cur=1;
            while (b[cur]!=0)
            {
                cur++;
            }
            a[i]=cur;
            b[cur]--;
            for (int j=1;j+k<=cur;j++)
            {
                b[j]--;
            }
        }
        for (int i=1;i<=n-1;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<a[n]<<endl;
    }
    return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

比较水的构造题，难度在于读题。~~吐槽一下翻译。~~

------------

### 题目大意

给定正整数 $n,k$ 和序列 $B$，需要构造一个字典序最小的序列 $A$，满足 $B_{A_i}$ 为 $A_i$ 左边的所有数 $\ge i+k$ 的数量。

### 思路

注意到每次将 $B$ 中第一个 $0$ 的位置放入 $A$ 是满足条件且会使得字典序更小的，所以贪心的放置 $B$ 中的 $0$，在放置完后将 $B$ 更新即可。

### code

~~好像代码都大差不差所以不用看这份码风奇丑的代码。~~

```cpp
int n,k;
int b[1086];
std::queue<int>a;
int main(){
	std::cin>>n>>k;
	for(int i=1;i<=n;i++)
		std::cin>>b[i];//常规输入
	while(a.size()<n){//a的长度不超过n
		int point=1;//表示B中第一个0的位置
		while(b[point])
			point++;//寻找0。
    // while(b[point++]);千万不要压行写成这样qwq
		a.push(point);//找到了就扔到A里去
		b[point]=-114514;//打上特♂殊♂的♂标♂记，防止下次又找到这个
		for(int i=1;i+k<=point;i++)
			b[i]--;//更新B
	}
	while(not a.empty()){
		int x=a.front();
		a.pop();
		std::cout<<x<<" ";//常规输出
	}
	return 0;//撒花
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF67B)

# 题意

给你一个 $b$ 数组，让你求一个长度为 $n$ 的 $a$ 数组，满足在 $a_i$ 左边，有 $b_i$ 个数满足 $a_j \le i+k$。

# 思路

其实，只需要找 $b$ 数组中第一个 $0$ 出现的位置，然后存入 $a$ 数组中，并每次更新 $b$ 数组即可。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, a[1005], b[1005], pos, k;
int main(){
	scanf ("%lld %lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf ("%lld", &b[i]);
	for (int i = 1; i <= n; i++){
		pos = 1;
		while (b[pos]) pos++;
		a[i] = pos;
		b[pos]--;
		for (int j = 1; j + k <= pos; j++) b[j]--;
	}
	for (int i = 1; i <= n; i++) printf ("%lld ", a[i]);
	return 0;
}

```

---

## 作者：zhu_wen (赞：0)

# 主要题意
正着不好求，我们可以根据样例反过来找关系，题目告诉了我们一种规则从 a 数组变成 b 数组。

看看 a 数组中有几个满足 $b_{cnt}\leqslant  i+k  $ 满足数的个数即为 b 的值。

- 求 $b_1$ 时，先找到 1 在 a 数组中得位置，得到 1 左边的数 4，$4\ge 1+2$,满足条件的就有 1 个数，因此 $b_1$ 为 1。
- 求 $b_2$ 时，先找到 2 在 a 数组中得位置，得到 1 左边的数 4 1 5，$4\ge 1+2$ 和 $5\ge 1+2$,满足条件有 2 个数，因此 $b_1$ 为 2。

## 思路
当题目是给我们 b 数组，要我们求最小得字典序的 a 数组。
 
在 b 中第一个 0 出现的位置，放在 $a_1$,这时候放 b 中最小的满足条件的值为 1。

在更新 b 数组时，使满足 $b_{cnt}\leqslant  i+k$ 的 b 的下标 cnt 的值减一。

## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int n;
int k;
int a[N], b[N];

signed main()
{
    fst;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int cnt = 1;
        while (b[cnt] != 0)
        {
            cnt++;
        }
        a[i] = cnt;
        b[cnt]--;
        for (int j = 1; j + k <= cnt; j++)
        {
            b[j]--;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
```


---

## 作者：zjhzs666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF67B)


# 题意


给你一个长度为 $n$ 的 $a$ 数组以及正整数 $k$，需要你构建一个长度为 $n$ 的 $b$ 数组，使得 $a_i$ 可以表示为在 $b$ 数组中位于元素 $i$ 的左边满足 $i+k\le b_j$ 的元素 $b_j$ 的个数。


# 思路
循环构建 $b$ 数组的 $n$ 个元素，每次查找 $a$ 数组中非 $0$ 元素的个数并记录在 $s$ 中，此时 $s$ 的值就是我们需要构建的元素 $b_i$，直接输出，最后将将 $a_s$ 的值以及 $a_1$ 到     $a_{s-k}$ 都减去 $1$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1001],s;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    for(int i=1;i<=n;i++){
    	s=1;
        while(a[s])
            s++;
        cout<<s<<' '; 
        a[s]--;
        for(int j=1;j<=s-k;j++)a[j]--;
    }
    return 0;
}
```


---

## 作者：lizulong (赞：0)

## 题意
给定正整数，$n,k$ 和序列 $B$，需要找到一个 $n$ 的全排列 $A$，使得 $B_i$ 可以表示，在 $A$ 中的元素 $i$ 的左边，满足 $a_j \ge i+k$ 的元素 $a_j$ 的个数。输出字典序最小的排列 $A$。
## 思路
定义一个用来执行操作的变量 $k$ ，找到输入中数组 $b$ 中 $0$ 的位置，将 $0$ 前面的部分存到 $a$ 数组中，经过几次循环判断和处理，每次 $k$ 的值存入 $a$ 数组中。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long 
#define o 0
using namespace std;
int n,m,k,a[10005],b[10005];
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++){
    	k=1;
        while(b[k]!=0) k++;//找数组b中0的位置
        a[i]=k,b[k]--;
        for(int j=1;k>=j+m;j++) b[j]--;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<" "; 
    return o;
}
```

---

