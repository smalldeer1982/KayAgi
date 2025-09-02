# Maxmina

## 题目描述

You have an array $ a $ of size $ n $ consisting only of zeroes and ones and an integer $ k $ . In one operation you can do one of the following:

- Select $ 2 $ consecutive elements of $ a $ and replace them with their minimum (that is, let $ a := [a_{1}, a_{2}, \ldots, a_{i-1}, \min(a_{i}, a_{i+1}), a_{i+2}, \ldots, a_{n}] $ for some $ 1 \le i \le n-1 $ ). This operation decreases the size of $ a $ by $ 1 $ .
- Select $ k $ consecutive elements of $ a $ and replace them with their maximum (that is, let $ a := [a_{1}, a_{2}, \ldots, a_{i-1}, \max(a_{i}, a_{i+1}, \ldots, a_{i+k-1}), a_{i+k}, \ldots, a_{n}] $ for some $ 1 \le i \le n-k+1 $ ). This operation decreases the size of $ a $ by $ k-1 $ .

Determine if it's possible to turn $ a $ into $ [1] $ after several (possibly zero) operations.

## 说明/提示

In the first test case, you can perform the second type operation on second and third elements so $ a $ becomes $ [0, 1] $ , then you can perform the second type operation on first and second elements, so $ a $ turns to $ [1] $ .

In the fourth test case, it's obvious to see that you can't make any $ 1 $ , no matter what you do.

In the fifth test case, you can first perform a type 2 operation on the first three elements so that $ a $ becomes $ [1, 0, 0, 1] $ , then perform a type 2 operation on the elements in positions two through four, so that $ a $ becomes $ [1, 1] $ , and finally perform the first type operation on the remaining elements, so that $ a $ becomes $ [1] $ .

## 样例 #1

### 输入

```
7
3 2
0 1 0
5 3
1 0 1 1 0
2 2
1 1
4 4
0 0 0 0
6 3
0 0 1 0 0 1
7 5
1 1 1 1 1 1 1
5 3
0 0 1 0 0```

### 输出

```
YES
YES
YES
NO
YES
YES
YES```

# 题解

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 蒟蒻 CJH。

难度：入门。

标签：模拟，贪心。

## 题意

你有一个大小为 $n$ 的数组 $a$，只由 $0$ 和 $1$ 组成，还有一个整数 $k$。在一次操作中，你可以做以下其中一个。

- 选择 $a$ 中的 $2$ 个连续元素，替换为它们的最小值。

- 选择 $a$ 中的 $k$ 个连续元素，替换为它们的最大值。

判断是否有可能在几次（可能是 $0$）操作后将 $a$ 变成 $[1]$。

## 分析

因为题目只需要将 $a$ 留下 $1$，所以我们这里只需要把其它的所有数字都替换为最小值且仅留下至少 $1$ 个 $1$，将序列的长度变为 $k$ 后在取最大值。

这也就意味着 $a$ 中至少需要有 $1$，才能让 $a$ 变为 $1$。

所以我们只需要对输入的数字按位或来判断是否有 $1$，就可以了。

## 代码

```cpp
//the code is from chenjh
#include<iostream>
#include<cstdio>
int main(){
    int t,n,k;scanf("%d",&t);
    while(t--){
    	scanf("%d%d",&n,&k);
        bool a,b=0;
        for(int i=0;i<n;i++)  std::cin>>a,b|=a;
        //输入 0 或 1 后按位或。
        puts(b?"YES":"NO");
    }
    return 0;
}										
```

时间复杂度 $O(tn)$。

*谢谢大家！*

---

## 作者：Awsdkl (赞：3)

[原题传送门](https://codeforces.com/contest/1746/problem/A)  
# 分析  
题目要求我们找到是否有让只包含 $0$ 或 $1$ 数组变为 $[1]$ 的解法。  

有两种操作：  
第一种是将两个并列的数替换为它们当中的最小值（长度会减小 $1$ ）；  
第二种是将一段长度为 $k$ 的子串替换为它们当中的最大值（长度会减小 $k-1$ ）。  

在第二种方法中，当子串中有 $1$ 时，则总会将这个子串替换为 $1$ 。所以当原数组中有 $1$ 时，我们就可以将数组变为 $[1]$。  
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n,k;
int a;

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int len1 = 0,len0 = 0;
		scanf("%d%d",&n,&k);
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&a);
			if(a) len1++;
			else len0++;
		}
		if(len1 >= 1)
		{
			printf("YES\n");
		}
		else printf("NO\n");
	}
	
	return 0;
}
```


---

## 作者：Rnfcr (赞：2)

## 题意
给定一个只含 $0$ 和 $1$ 的序列，可以将一些连续的数变为他们的最大值或最小值，请问能不能将这个序列变为只剩下 $1$。
## 分析
如果这个序列中没有 $1$，那么不会有一种方法使这个序列变为 $1$；

如果这个序列中有 $1$，那么只需要一直用第二种操作取最大值便可使这个序列中只剩下 $1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,num,k;
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		bool one=false;//判定有没有1
		for(int i=1;i<=n;i++){
			cin>>num;
			if(num) one=true;
		}
		if(one) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Larryyu (赞：2)

## _Description_
给定一个只包含 $\texttt{0}$ 和 $\texttt{1}$ 的数串，你可以执行下列两组操作：
- 将 $a_i,a_{i+1}$ 替为 $\min (a_i,a_{i+1})$
- 将 $a_i,a_{i+1}\dots a_{i+k}$ 替为 $\max (a_i,a_{i+1}\dots a_{i+k})$

问能否通过执行上述操作若干次后，使数串中只有 $\texttt{1}$（执行零次也算可以）。
## _Solution_
第一种操作没有任何用处，因为只要有 $\texttt{0}$ 在操作范围内，$\min(a_i,a_{i+1})=0$。

因为 $k\ge2$，所以只要原串中有 $\texttt{1}$，就能通过第二种操作使得操作范围内只有 $\texttt{1}$。即使 $k$ 不是很大，也能通过若干次实现要求。但前提是原串中至少要有一个 $\texttt{1}$，直接遍历一遍原串查找即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int n,k;
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
    n=read();
    k=read();
    bool f=0;
    for(int i=1;i<=n;i++){
        int x=read();
        if(x==1){
            f=1;
        }
    }
    if(f==1){
        cout<<"YES"<<endl;  //只要有1就一定能满足要求
    }else cout<<"NO"<<endl;
}
int main(){
    t=read();
    while(t--){
        solve();
    }
    return 0;
}
```
#### _完结撒花！！_

---

## 作者：zhangzinan1224 (赞：0)

## 步骤1:

很明显，如果在所有的 $1 \le i \le n$ 中，$a_i = 0$ ，输出 “NO” 。

## 步骤2:

如果至少有一个 $1 \le i \leq n$ 中，$a_i = 1$ ，我们证明答案是 “YES” 。

## 步骤3:

如果 $a$ 的大小等于 $k$ ，只使用第二类运算一次，我们就完成了。

## 步骤4:

否则(如果 $\left\vert a\right\vert > k$ )，将有三种情况：(假设 $a_j = 1$  )

- 如果 $j > 2$ ，则可以对第一个和第二个元素使用第一类操作并将 $a$ 减 $1$ 。

- 否则，如果 $j < \left\vert a\right\vert - 1$ ，则可以对最后一个元素和倒数第二个元素使用第一种操作，并将 $a$ 减 $1$ 。

- 对于另外的情况，可以很容易地证明 $\left\vert a\right\vert = 3, k = 2$  ，所以我们可以使用第二类运算两次，把 $a$ 变成 $1$ 。

在第一种和第二种情况下，你可以继续减小 $a$ 的大小，直到 $\left\vert a \right\vert = k$ (或达到第三种情况)，你可以使用第二种操作来达到你的目标。

## 步骤5:

因此，我们证明了答案是 “YES” ，在 $a_i = 1$ 时，对于至少一个 $1 \leq i \le n$ 。或者换句话说，当 $\sum_{i=1}^n a_i > 0$ 时。

Code:
```cpp
#include <iostream>
 
using namespace std;
 
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        int sum = 0;
        for(int i = 0 ; i < n ; i++){
            int a;
            cin >> a;
            sum += a;
        }
        if(sum > 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```


---

## 作者：LeTu_Jun (赞：0)

## 题意

简化版题意已经有了。

## 思路

因为串中只有 $0$ 和 $1$，最后又希望剩下的数字是 $1$，所以这个求最小的操作**跟没有一样**。

这个操作只能消除 $1$，我们又需要 $1$，那这个操作有啥用呢？

再想一想，因为 $k \le n$，也就是说每次操作至少可以干掉序列中的一个数字，又因为这个操作取得是最大值，所以：

**只要序列中有一个 $1$**，在经过若干次操作后，一定可以将序列变为一个满足题目要求的序列。

怎么判断序列中有没有 $1$ 呢？读入的时候顺便扫一遍就行啦。

事实上完全不需要开数组将数组存下来，直接用一个变量记录有没有 $1$ 就行了。

注意事项：

- 多组数据；

- 建议使用较快的输入输出方式；

- 注意 `YES` 和 `NO` 均需大写。

----

*code*

```cpp
#include<bits/stdc++.h>
int t,n,k;
bool is_1;
int main ()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		is_1=false;
		for(int i=1,tmp=0;i<=n;i++){
			scanf("%d",&tmp);
			if(tmp==1)
			{
				is_1=true;
			}
		}
		if(is_1)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
```


---

## 作者：mark0575 (赞：0)

## 题目大意：

给定一串01序列，可以对这个01序列作出以下操作：

1. 将 $a_{i}$ 和 $a_{i+1}$ 合并成 $\min(a_{i}, a_{i+1})$
1. 将 $a_{i}$ 到 $a_{i+k-1}$ 合并成 $\max(a_{i}, a_{i+1}...a_{i+k-2}, a_{i+k-1})$

问我们能否经过若干次合并让序列变为$1$。

## 题目思路

由于题目数据样例不大，我们可以先研究一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/vhb00apc.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8xz96qmd.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/zqsm09j5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/410236ny.png)
（这里讲一下为什么在全都是 $1$ 的情况下可以使用操作 $1$ ，而在有 $0$ 的情况下不建议用操作 $1$ 。我们看一下操作 $1$ ，它是把两个数合并成一个较小数。当这两个数中出现$0$是，合并出来的数一定是 $0$ 。当所有数都是 $1$ 时，不管怎么选取两个相邻的数，合并出来的数一定是1，一次可以放心使用操作 $1$ 。而在有 $0$ 的情况下，有可能会因为合并后把1全都变没了，导致最后得到错误答案）

通过观察样例，我们可以发现，当序列全为 $0$ 时，答案为 "NO" ，否则就为 "YES" 。为什么全为 $0$ 时答案为 "NO" 呢？我们可以发现，如果当前序列没有 $1$ 或 $0$ ,不管怎么操作，一定不会出现 $1$ 或 $0$。所以，我们只需要判断一下这个序列里有没有 $1$ 就好了！

## Ac code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		bool b=false;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==1)//判断序列是否有1
			{
				cout<<"YES\n";
				b=true;
				break;
			}
		}
		if(b==false)
		{
			cout<<"NO\n";
		}
	}
    	system("shutdown -s");//防抄袭
	return 0;
}

```


---

## 作者：p924874163 (赞：0)

### 题目大意
  
题目要求的是判断经过若干次操作后是否能使 $n=1$ 且 $a_1=1$，有两种操作：

1. 选定一个 $i\in[1,n-1]$，将 $a_i$ 和 $a_{i+1}$ 这两个数替换为它们的最小值。进行此操作后，序列的长度 $n$ 减少 $1$。

2. 选定一个 $i\in[1,n-k+1]$，将 $a_i$ 到 $a_{i+k-1}$ 这 $k$ 个数替换为它们的最大值。进行此操作后，序列的长度 $n$ 减少 $k-1$。

### 分析
  
其实，无论数组如何，只要其中有 $1$ 就输出 `YES`，否则输出 `NO`。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[60],k;
int main()
{
	cin>>t;
	while(t--)
	{
		int flag=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)	
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=0)
				flag=1;	
		}	
		if(flag)
			puts("YES");
		else puts("NO");	
	}
	return 0;
}

```


---

## 作者：小明小红 (赞：0)

# CF1746A题解
**先放结论**：显而易见的，由于 $( 2 \leq k≤50 )$，只要数列中有一个数为一，就能使所有为一。

**没看懂看这里**：由于每次能将连续 $k$ 个变为最大，若其中有一个一，就可以把连续这一串都变成一，以此类推，得到结论。
# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n,a,flag=0,m;
string s;
int main()
{
	cin>>T;
	while(T--)//T组数据 
	{
		cin>>n>>m;
		flag=0;
		for(ll i=1;i<=n;i++)
		{
			cin>>a;
			if(a==1)//判断是否有1 
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			cout<<"YES"<<endl; 
		}
		else
		{
			cout<<"NO"<<endl;
		}
		
	}
	return 0; 
}
```


---

## 作者：zfx_VeXl6 (赞：0)

### 题意

#### 题目描述

给定一个长度为 $n$ 的只包含 $0$ 和 $1$ 的序列 $a$ 和一个数字 $k$，可以进行如下的操作各若干次：

- 选定一个 $i\in[1,n-1]$，将 $a_i$ 和 $a_{i+1}$ 这两个数替换为它们的最小值。进行此操作后，序列的长度 $n$ 减少 $1$。

- 选定一个 $i\in[1,n-k+1]$，将 $a_i$ 到 $a_{i+k-1}$ 这 $k$ 个数替换为它们的最大值。进行此操作后，序列的长度 $n$ 减少 $k-1$。

判断经过若干次操作后是否能使 $n=1$ 且 $a_1=1$。

#### 输入

$t$ 组数据，每组数据第一行输入两个整数 $n$ 和 $k$，第二行输入 $n$ 个整数 $a_i$。

#### 输出

若可以，输出 `YES`，否则输出 `NO`。

### 思路

可以证明只要序列中里有 $1$ 就可以把序列变成单独一个 $1$。

若序列中有 $1$，输出 `YES`，否则输出 `NO`。

代码简单，就不放了。

---

## 作者：what_else (赞：0)

显然这题只要判断是否有 $1$ 即可。

因为 $k\le n$，最优的方案应该是尽可能先取相邻两个数最小值，直到剩下 $k$ 个数时取最大值。

所以我们只要在 $a$ 中留下一个 $1$，剩下的 $1$ 或 $0$ 全消去即可。这道题就演变成了 $a$ 中有没有 $1$，$k$ 明显与答案无关。

代码过于简单，故不予显示。

---

## 作者：sw2022 (赞：0)

## 题意简析

给定一个 01 序列 $a\ (|a|=n,n>0$ 且 $\forall i\in [1,n]$，$a_i\in[0,1])$ 和一个整数 $k\ (2\le k\le n)$，有两种操作：
- 选择一个长度为 $2$ 的子段，用它们的较小值替换；
- 选择一个长度为 $k$ 的子段，用它们的最大值替换；

问这个序列能否在执行一定数量的操作后变成 $\{1\}$。

考虑两种情况：
1. 这个序列的元素全部为 $0$。则无论留下哪一个元素，这个序列最后一定为 $\{0\}$，无解。
2. 这个序列的元素中含有 $1$。因为 $k\le n$，所以一种通解就是选定一个长度为 $k$、含有 $1$，且对于所有能与这个 $1$ 执行第一种操作（即与这个 $1$ 相邻）的元素，都在这个子段中的子段后，对于剩下的 $n-k$ 个元素使用第一种操作将它们全部删除（可以证明，对于任意一个 01 序列，只使用第一种操作一定能将它们变成 $\{0\}$（如果这个序列的元素中含有 $0$）或 $\{1\}$（如果这个序列的元素全部为 $1$），然后与选定子段中在原序列对应的相邻元素执行第一种操作即可删除）。然后对这个长度为 $k$ 的子段执行第二种操作。因为这个序列含有没有被第一种操作删除过的 $1$，所以执行第二种操作后序列一定为 $\{1\}$，有解。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,k,a,i;
    bool f;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;f=false;
        for(i=1;i<=n;i++)
        {
            cin>>a;
            if(a) f=true;
        }
        printf(f?"YES\n":"NO\n");
    }
    return 0;
}
```

---

