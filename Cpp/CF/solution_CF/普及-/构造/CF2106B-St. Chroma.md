# St. Chroma

## 题目描述

给定一个长度为 $n$ 的排列$^{\text{∗}}$ $p$，其中包含从 $0$ 到 $n-1$ 的所有整数，以及一条包含 $n$ 个单元格的彩带。圣·克罗玛会将彩带的第 $i$ 个单元格涂成颜色 $\operatorname{MEX}(p_1, p_2, ..., p_i)$ $^{\text{†}}$。

例如，假设 $p = [1, 0, 3, 2]$。那么，圣·克罗玛会按照以下方式为彩带的单元格上色：$[0, 2, 2, 4]$。

现在给定两个整数 $n$ 和 $x$。由于圣·克罗玛特别喜爱颜色 $x$，请构造一个排列 $p$，使得彩带中被涂成颜色 $x$ 的单元格数量最大化。

$^{\text{∗}}$ 长度为 $n$ 的排列是指包含从 $0$ 到 $n-1$ 所有整数且每个整数恰好出现一次的序列。例如，$[0, 3, 1, 2]$ 是一个排列，但 $[1, 2, 0, 1]$ 不是（因为 $1$ 出现了两次），$[1, 3, 2]$ 也不是（因为缺少 $0$）。

$^{\text{†}}$ 序列的 $\operatorname{MEX}$ 定义为该序列中缺失的最小非负整数。例如，$\operatorname{MEX}(1, 3, 0, 2) = 4$，而 $\operatorname{MEX}(3, 1, 2) = 0$。

## 说明/提示

第一个样例已在题目描述中解释。可以证明，$2$ 是被涂成颜色 $2$ 的单元格的最大可能数量。注意，另一个正确的答案可以是排列 $[0, 1, 3, 2]$。

在第二个样例中，排列给出的涂色结果为 $[0, 0, 0, 4]$，因此有 $3$ 个单元格被涂成颜色 $0$，这可以被证明是最大值。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
4 2
4 0
5 0
1 1
3 3
1 0
4 3```

### 输出

```
1 0 3 2
2 3 1 0
3 2 4 1 0
0
0 2 1
0
1 2 0 3```

# 题解

## 作者：Clare613 (赞：1)

~~马上满了？~~
## 思路
因为题目要求 $ \operatorname{MEX}(p_1,p_2,p_3,\dots,p_i) = x $，所以我们要把 $0$ 至 $x-1$ 的值放前面，后面要记得把 $x$ 的值放最后面，因为 $\operatorname{MEX}$ 的定义是**第一个**不在数组中出现的非负整数，其余的数，即 $x+1$ 至 $n$ 的值顺序没有强制要求，原因是**第一个**不在数组中出现的非负整数一定是 $x$，后面的数不管再怎么齐也是无用功。
## code:
前面说了$x+1$ 至 $n$ 的值顺序没有强制要求，所以这里给两个 AC 代码来证明前面的理论。
### code $1$：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
    	int n,x;
        cin>>n>>x;
        for(int i=0;i<x;i++){
            cout<<i<<" ";
        }
        for(int i=x+1;i<=n-1;i++){
            cout<<i<<" ";
        }
        if(x!=n)cout<<x<<"\n";
        else cout<<"\n";
    }
    return 0;
}
```
### code $2$：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
    	int n,x;
        cin>>n>>x;
        for(int i=0;i<x;i++){
            cout<<i<<" ";
        }
        for(int i=n-1;i>=x;i--){
            cout<<i<<" ";
        }
		cout<<"\n";
    }
    return 0;
}
```

---

## 作者：wwwidk1234 (赞：1)

## 题目
有一个长为 $n$ 的一维数组（下标为 $1 \sim n$），第 $i$ 格涂有颜色 $\operatorname{MEX}(p_1,p_2,\dots,p_i)$。

给定 $x$，要求构造一个长度为 $n$，包含 $0 \sim n-1$ 的数的排列 $p$，使得满足一维数组中颜色为 $x$ 的格子数最大。

## 思路

首先，对于 $x$ 的大小可分为两种情况：

1. 当 $x=n$ 时，显然不管怎么安排 $p$ 的顺序，满足条件的 $k$ 的个数都只能为 $1$，颜色 $x$ 只能在最后一个格子中出现。

2. 当 $x<n$ 时，首先把 $0 \sim x-1$ 全部用掉，此时下一个格子的颜色就应该涂上颜色 $x$。这时，如果在后面插入一个大于 $x$ 的数，那么后面格子就只能涂上颜色 $x$。最后将 $x$ 放在排列 $p$ 的最后面即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=2e5+7;
inline void solve()
{
    int n,x;
    cin>>n>>x;
    if(x==n) for(int i=0;i<n;i++) cout<<i<<' ';
    else
    {
        int c=0;
        for(int i=0;i<n;i++)
        {
            if(i==x)
            {
                c++;
                continue;
            } 
            else cout<<c<<' ';
            c++;
        }
        cout<<x;
    }
    cout<<'\n';
}
int main()
{
//	freopen("neuvillette.in","r",stdin);
//	freopen("neuvillette.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
	return 0;
}
```

[Codeforces Submission.](https://codeforces.com/contest/2106/submission/317004460)

---

## 作者：InfiniteRobin (赞：1)

## 题目大意
[CF 题目传送门](https://codeforces.com/contest/2106/problem/B)  

给定正整数 $n,x$，要求构造一个长度为 $n$，包含 $[0,n-1]$ 的每个数的序列 $p$，使得满足 $\operatorname{MEX}(p_1,p_2,\cdots,p_i) = x$ 的 $i$ 的个数最大化。

## 分析
考虑贪心。
- 首先，我们为了使得序列的 $\operatorname{MEX}$ 值等于 $x$，我们必须首先将 $[0,x-1]$ 这几个数放在序列 $p$ 开头（当然，若 $x=0$ 就不用放），这样可以最早满足题目要求。
- 其次，为了让 $x$ 出现次数尽可能大，我们可以考虑将 $x$ 放在序列 $p$ 的末尾。
- 这样，对于 $\max(x,1) \le i \le n-1$，就满足 $\operatorname{MEX}(p_1,p_2,\cdots,p_i)=x$。这里取 $\max$ 的原因是 $x$ 可能为 $0$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int t,n,x;
    cin>>t;
    while(t--){
        cin>>n>>x;
        for(int i=0;i<x;i++){
            cout<<i<<" ";
        }
        for(int i=n-1;i>=x;i--){
            cout<<i<<" ";
        }
        cout<<"\n";
    }

    return 0;
}
```

[洛谷 RMJ 炸了，所以 CF。](https://codeforces.com/contest/2106/submission/317344095)

---

## 作者：yulinOvO (赞：1)

### 题意：
构造一个长度为 $n$ 的排列 $p$，需要包含 $0$ 到 $n-1$ 的所有整数，使得在计算每个位置 $i$ 的 $MEX(p_1,p_2,...,p_i)$ 时，$x$ 出现次数的最大化。
### 思路：
分类讨论：
- $x=0$：排列为 $[1, 2, ..., n-1, 0]$ ， 前 $n-1$ 个位置的 $MEX$ 都是 $0$。  
- $x=n$：排列必须包含所有数字 $0$ 到 $n-1$，且 $MEX=n$ 只能出现在最后一个位置（最大出现次数为 $1$）。  
- $1≤x≤n-1$：  
   - 开头放 $0, 1, ..., x-1$，使前 $x$ 个位置的 $MEX$ 从 $1$ 递增到 $x$。  
   - 接着插入一个大于 $x$ 的数来固定 $MEX=x$。  
   - 最后插入剩余的数。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--)
	{
        cin >> n >> x;
        vector<int> res;
        if(x==0)//将0放在最后，前面放其他数
		{
            for(int i=1;i<n;i++) res.push_back(i);
            res.push_back(0);
        }
		else if(x==n)//只能出现在最后一个位置
		{
            for(int i=0;i<n;i++) res.push_back(i);
        }
		else
		{
            for(int i=0;i<x;i++) res.push_back(i);
			for(int i=x+1;i<n;i++) res.push_back(i);
			res.push_back(x);
        }
        for(int i=0;i<n;i++) cout << res[i] << " ";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Noah03 (赞：1)

本题第一篇题解。

### 题意

---

序列的 $\operatorname{MEX}$ 定义为序列中第一个不出现的非负整数。
长度为 $n$ 的排列是指只由 $0$ 到 $n-1$ 中每个元素且每个元素恰好只在序列中出现一次的序列。

现在要求你构造一个排列，使在 $\forall i(1 \le i \le n)$ 中 $\operatorname{MEX}(Per_i)=x$ 的数量最大，其中 $Per_i$ 为长度为 $i$ 的排列。

~~题面怎么没有翻译啊还要用 CodeForces Better 翻译。~~

### 分析

---

从题面可以看出，这是一道构造题。考虑分类讨论：

- $x=0$

  只需要把 $0$ 放在最后面即可，前面随便排（因为如果不含 $0$，未出现的非负整数一定最小为 $0$）。

- $x=n$

  可以得到数量最多为 $1$，把 $n$ 放在最后面即可。

- $x \neq 0 \ \land x \neq n$

  结论：先跳过 $x$，最后输出 $x$。

  证明：在 $0 \le i \lt x$ 时，只有 $i=x-1$ 时数量为 $1$。在 $x \lt i \le i$ 时，对于 $\forall i$ 数量均为 $1$。可以得到此时是最优的。

### 代码

---

**请勿抄袭。**

此为赛时代码（除了注释）。

Code:
```cpp
//The Code is From @Noah03(Luogu User Name),@Noah0333(CodeForces User Name),Do not copy;
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,x;
		scanf("%d %d",&n,&x);
        //分类讨论
		if (!x){
			for(int i=1;i<n;i++) printf("%d ",i);
			putchar('0');
		}
		else if (x==n){
			for(int i=0;i<n;i++) printf("%d ",i);
		}
		else{
			for(int i=0;i<x;i++) printf("%d ",i);
			for(int i=x+1;i<n;i++) printf("%d ",i);
			printf("%d",x);
		}
		puts("");
	}
	return 0;
}
```

代码的时间复杂度为 $O(T \times n)$，空间复杂度为 $O(1)$。



**The End.**

---

## 作者：TLE_qwq (赞：0)

## 题目描述
让我们构造一个 $0$ 到 $n-1$ 的排列，使得前缀 MEX 序列中出现 $x$ 的次数最多。

## 解题思路
这道题可以分三种情况处理：

1.  $x=0$ 时 
     - 将 $0$ 放在排列的最后。
     - 前面依次放置 $1$ 到 $n-1$。 
     - 这样前 $n-1$ 个前缀的 MEX 都是 $0$。 

2.  $x=n$ 时  
     - 任意排列均可。
     - 因为只有整个排列的 MEX 会是 $n$ （出现 $1$ 次）。

3. 其他情况  
    - 前 $x$ 个位置放 $0$ 到 $x-1$。 
   - 后面从 $n-1$ 倒序放置到 $x$。
   - 这样第 $x$ 个前缀的 MEX 是 $x$，且后续不会更小。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, n, x;
    cin >> t;
    while (t--) {
        cin >> n >> x;
        if (x == 0) {
            for (int i = 1; i < n; i++) cout << i << " ";
            cout << "0\n";
        } else if (x == n) {
            for (int i = 0; i < n; i++) cout << i << " \n"[i==n-1];
        } else {
            for (int i = 0; i < x; i++) cout << i << " ";
            for (int i = n - 1; i >= x; i--) cout << i << " \n"[i==x];
        }
    }
    return 0;
}

---

## 作者：Alice2012 (赞：0)

## Description

给定 $n,x$，构造长度为 $n$ 的序列 $a$ 为 $0\sim n-1$ 的排列。另有长度为 $n$ 的序列 $p$，$p_i=\text{MEX}(a_1,a_2,\dots,a_i)$。试构造最优的 $a$ 使得有最多的 $p_i=x$。

## Solution

设定 $a,p$ 的下标都从 $1$ 开始。考虑贪心。

- 首先在 $i\in[1,x]$ 内设定 $a_i=i-1$，这样可以最早的满足 $p_i=x$。当 $i=x$ 时，已经满足 $p_i=x$。
- 在 $i\in[x+1,n-1]$ 内设定 $a_i=i$，这样在 $a_1,a_2,\dots,a_i$ 中始终不存在 $x$，且始终存在 $0,1,\dots,x-1$，那么 $\text{MEX}$ 值始终是 $x$。
- 将最后一个数填为 $x$。

易证在这样的策略下 $p_i=x$ 的数量是最多的。

但是需要注意一个边界处理的小细节：当 $x=n$ 时，第一步已经会将 $0\sim n-1$ 填满，这时不需要操作第三步的策略。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>x;
        for(int i=0;i<x;i++)cout<<i<<" ";
        for(int i=x+1;i<n;i++)cout<<i<<" ";
        if(x!=n)cout<<x<<"\n";
        else cout<<"\n";
    }
    return 0;
}
```

---

## 作者：Noah2022 (赞：0)

### 题意
> 给你两个整数 $n$，$x$，要你构造一个序列 $a$ 为 $0 \sim n-1$ 的排列组合，使得序列 $p$ 中的 $x$ 元素最多。$p_i=\operatorname{MEX}(a_1,a_2,\dots,a_i)$。
### 思路
很明显，我们先把 $0 \sim x-1$ 设置为 $a$ 的前 $x$ 个数，那么 $p_x=x$，因为我们如果放了 $x$，那么 $p_k > x $。所以我们只需要将 $x$ 最后放即可。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,x;
int main(){
    cin>>q;
    while(q--){
        cin>>n>>x;
        for(int i(0);i<x;++i)cout<<i<<" ";
        for(int i(n-1);i>=x;--i)cout<<i<<" ";
        cout<<'\n';
    }
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2106B)
# 思路
不难看出，本题要分为两种情况。

1. 当 $x<n$ 时，不难看出只有小于 $x$ 的数全部输出时 $\operatorname{mex}$ 才为 $x$。所以我们只需要将 $x$ 放到整个排列的最后面即可，可以得到这种情况是最优的。
   
    ```cpp
    for(int i=0;i<x;i++) cout <<i<<" ";
    for(int i=x+1;i<n;i++) cout <<i<<" ";
    cout <<x;
    ```
3. 当 $x=n$ 时，我们可以得到 $\operatorname{mex}$ 的数量最多为 $1$，所以直接循环输出 $0 \sim n-1$ 即可。
   
    ```cpp
    if(x==n)
    {
      for(int i=0;i<n;i++) cout <<i<<' ';
    }
    ```
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		int n,x;
		cin >>n>>x;
		if(x==n)
		{
			for(int i=0;i<n;i++) cout <<i<<' ';
		}
		else
		{
			for(int i=0;i<x;i++) cout <<i<<" ";
			for(int i=x+1;i<n;i++) cout <<i<<" ";
			cout <<x;
		}
		cout <<'\n';
	}
	return 0;
}

```

---

