# Indirect Sort

## 题目描述

给定一个长度为 $n$ 的排列 $a_1, a_2, \ldots, a_n$，其中每个整数 $1$ 到 $n$ 恰好出现一次。

你可以进行如下操作任意次（也可以不进行操作）：

- 选择任意三个下标 $i, j, k$（$1 \le i < j < k \le n$）。
- 如果 $a_i > a_k$，则将 $a_i$ 替换为 $a_i + a_j$。否则，交换 $a_j$ 和 $a_k$ 的值。

请判断是否可以通过若干次操作将数组 $a$ 变为非递减有序。

## 说明/提示

在第一个测试用例中，$[1,2,3]$ 已经是非递减有序。

在第二个测试用例中，可以选择 $i = 1, j = 2, k = 3$。由于 $a_1 \le a_3$，交换 $a_2$ 和 $a_3$，数组变为 $[1,2,3]$，已经是非递减有序。

在第七个测试用例中，可以依次进行如下操作：

- 选择 $i = 5, j = 6, k = 7$。由于 $a_5 \le a_7$，交换 $a_6$ 和 $a_7$，数组变为 $[1,2,6,7,4,5,3]$。
- 选择 $i = 5, j = 6, k = 7$。由于 $a_5 > a_7$，将 $a_5$ 替换为 $a_5 + a_6 = 9$，数组变为 $[1,2,6,7,9,5,3]$。
- 选择 $i = 2, j = 5, k = 7$。由于 $a_2 \le a_7$，交换 $a_5$ 和 $a_7$，数组变为 $[1,2,6,7,3,5,9]$。
- 选择 $i = 2, j = 4, k = 6$。由于 $a_2 \le a_6$，交换 $a_4$ 和 $a_6$，数组变为 $[1,2,6,5,3,7,9]$。
- 选择 $i = 1, j = 3, k = 5$。由于 $a_1 \le a_5$，交换 $a_3$ 和 $a_5$，数组变为 $[1,2,3,5,6,7,9]$，已经是非递减有序。

在第三、第四、第五和第六个测试用例中，可以证明无法将数组变为非递减有序。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
3
1 2 3
3
1 3 2
7
5 3 4 7 6 2 1
7
7 6 5 4 3 2 1
5
2 1 4 5 3
5
2 1 3 4 5
7
1 2 6 7 4 3 5```

### 输出

```
Yes
Yes
No
No
No
No
Yes```

# 题解

## 作者：zhang_kevin (赞：11)

# Solution

首先可以想到，这道题无论如何 $j,k$ 都不能取到 $1$。因此，$a_1$ 不能被交换，只能被增加。

这里可以讨论两种情况：$a_1=1$ 与 $a_1>1$。

当 $a_1=1$ 时，显然，可以通过交换使它单调递增。

当 $a_1>1$ 时，这个排列永远无法单调递增，因为第一个数无法取到 $1$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int tt;
    cin >> tt;
    while(tt--){
        int n, a, b;
        cin >> n >> b;
        for(int i = 2; i <= n; i++) cin >> a;
        if(b == 1) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
```

---

## 作者：Steven_Gerrard (赞：4)

题意简述前面几篇题解已经提到，这里不再赘述。
## 主要思想
我们进行讨论后，可以区分两种情况 $\left\{\begin{matrix}
 a_1=1 \\
 a_1>1
\end{matrix}\right.$ 。   
当 $a_1=1$ 时，因为另外任选一个数，都不可能小于 $1$，所以这个时候即可对剩下的数列进行排序直至成为一个非降序的数列。         
当 $a_1>1$ 时，此时总会有一个数 $a_k=1$，此时无论选择任意一个数 $a_i$ ，都无法使 $a_i<a_k$ ，此时由于 $a_j$ 始终大于 $1$ ，所以 $a_i$ 只会越来越大，而 $a_k$ 始终无法排到数组最前面，所以这个数列永远不会成为非降序的数列。
## Std
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11];
int read()
{
	register int f=1,x=0;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
		if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())
		x=x*10+ch-'0';
	return f*x;
}
void solve()
{
	int n;
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	if(a[1]==1)printf("Yes\n");
	else printf("NO\n");
}
int main()
{
	int T;
	T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：_H17_ (赞：2)

## 题目大意

首先这道题意思是输入 $T$，表示有 $T$ 组测试数据。

每一组数据输入 $n$ 和一个由 $1\sim n$ 的全排列 $a$。

定义一组操作为：选定三个数 $i,j,k$（$1 \le i < j < k\le n$）若 $a_i > a_k$ 将 $a_i$ 加上 $a_j$，否则交换 $a_j,a_k$。

问你是否可以通过操作使这个 $a$ 单调递增。

## 思路分析

我们首先看 $a_1$，首先 $j,k$ 肯定不是 $1$，我们可以利用这一性质推出：

$\begin{cases}
   a_1=1 & \texttt{可以通过交换后面单调递增。} \\
   a_1\ne1 & a_1\space\texttt{只能增加不能交换，所以}\space a_1 \texttt{不可能变成}\space 1\texttt{。}
\end{cases}
$

## 代码

```cpp
#include<bits/stdc++.h>
//#include<管理员最帅>
using namespace std;
int T,n,k;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    //输入输出加速
    cin>>T;
    for(;T;--T){
        cin>>n>>k;
        puts(k==1?"Yes":"No");
        //输出
        for(int i=2;i<=n;i++)
            cin>>k;
        //完成剩下没用的读入
    }
    return 0;
}
```

---

## 作者：ShanCreeperPro (赞：2)

## CF1750A Indirect Sort 題解

### 题意

给定 $T$ 组数据，每组数据给定 $n$ 以及长度为 $n$ 的排列 $a$，可以进行若干次操作，每次操作可以选择三个数 $i,j,k \ (1 \le i < j < k \le n)$，若 $a_i > a_k$ 将 $a_i$ 加上 $a_j$，否则交换 $a_j,a_k$，问是否能使排列单调递增。

### 解析

很有意思的一题。

先来看 $i,j,k$ 的数据范围：$1 \le i < j < k \le n$，看到这你就要敏感了，说明只有 $i$ 能取的到 $1$。

从这入手，分析操作，可以发现我们选的 $a_i$ **只能被增加**，不能被交换，这意味着什么？

我们知道，一个单调递增的排列通常为：$1,2,3,4,5 \cdots$，其 $a_1$ 恒等于 $1$。

结合刚刚我们发现的只有 $i$ 能取到 $1$，不难得到：

- 如果 $a_1 ≠ 1$，这个排列永远无法单调递增，因为 $a_i$ 只能增加且 $i$ 能取到 $1$。它将无法通过操作变成 $1$。
- 如果 $a_1 = 1$，那么把 $i$ 取 $1$，剩下的 $a_2$ 到 $a_n$ 可以通过交换使其单调递增。

### 核心代码

```Go
for i = 1; i <= T; i++{
	fmt.Scan(&n, &b)
    for j = 1; j <= n - 1; j++{
    	fmt.Scan(&a)
    }
    if b == 1{
    	fmt.Println("Yes")
    }
    else{
    	fmt.Println("No)
    }
}
```



---

## 作者：Dangerou (赞：2)

## 分析：

题目要求我们对输入进行排序，而且限制了两种方法：

1. 交换 $a_j$ 与 $a_k$
2. 将 $a_i$ 加上 $a_j$

我们会发现，无论怎么操作，第一个数无法改变它的位置也没有办法减小其值。

因为原始序列中 $1$ 到 $n$ 出现一次，当 $1$ 不在数列的开始时，会形成一个非常尴尬的局面——第一个数不会变成 $1$，$1$ 也没有办法向前移动或增加（因为 $a_j$ 只能向后移动且 $a_i$ 只有在比 $a_k$ 大的时候才会增加。

然而当 $1$ 位于序列的第一个数时，后面的所有数都会比 $1$ 大从而对后面所有的数随意进行移动，总是能排好序。

### Code
```
#include<iostream>
#include<cstdio>
using namespace std;
int T,n;
int a[15];
void work()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(a[1]==1) printf("Yes\n");
	else printf("No\n");
	return;
}
int main()
{
	scanf("%d",&T);
	while(T--) work();
	return 0;
}
```

---

## 作者：晴空一鹤 (赞：2)

~~第一眼看有点吓人。~~

### Solution

观察样例，容易发现，有解时 $1$ 都在序列最前端，再分析一下， $1$ 在最前端，则我们可选 $i=1$，$j$，$k$ 任选，由于 $a_i$ 互不相同，此时必将交换 $a_j$ 和 $a_k$，变成冒泡排序，必然有解。

必要性？由 $a_i\le n$ 可知，序列中必然存在 $1$，若 $1$ 不在最首位，则他既无法交换回首位，又由于是最小的，无法使得 $a_i>a_k$，因此加不上任何一个数，这种情况就无解了。

#### CODE

```
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y;
void inline solve()
{
cin>>n;
cin>>x;
for(int i=2;i<=n;i++)
cin>>y;
if(x==1)
printf("YES\n");
else
printf("NO\n");
}

int main()
{
cin>>t;
while(t--)
solve();
}
```


---

## 作者：sw2022 (赞：1)

## 题意简析

给定一个排列 $a\ (|a|=n,a>0)$，可以进行任意次以下操作：

1. 选择三个序号 $i,j,k\ (1\le i<j<k\le n)$；
2. 如果 $a_i>a_k$，将 $a_i$ 加上 $a_j$；否则，交换 $a_j$ 和 $a_k$。

判断能否使这个排列变成一个单调不减的序列。

可以发现，无论如何选择 $i,j,k$，$a_i$ 的值不能被交换，只能被增加。因此可以得出：

- 当 $a_1=1$ 时，由于任意时刻 $a_1$ 都是这个排列的最小值，所以可以一直令 $i=1$ 来交换 $a_j$ 和 $a_k$，一定能使最终排列单调递增。
- 当 $a_1>1$ 时，任意时刻一定存在一个 $a_i=1$ 小于序列中其他任意一个元素且无法被增加，又因为 $a_1$ 只能被增加，所以任意时刻都有 $a_1>a_i\ (a_i=1$ 且 $1<i\le n)$，无法使得最终序列单调不减。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,a,b,i;
    cin>>t;
    while(t--)
    {
        cin>>n>>b;
        for(i=2;i<=n;i++)
        cin>>a;
        printf(b==1?"Yes\n":"No\n");
    }
    return 0;
}
```

---

## 作者：zhangzinan1224 (赞：1)

当且仅当 $a_1 = 1$ 时，我们可以对数组进行排序。

**必要性**

我们可以注意到，$a_1$ 不会受到任何交换操作的影响。

让我们看看 $a_1$ 会发生什么变化。根据操作的定义，它可以增加，也可以交换。为了增加，必须存在一些 $k$ 使 $a_k < 1$，但由于 $1$ 是可能的最小值，它永远不会为真，因为数组 $a$ 中的其他值也只能增加。由于 $a_1$ 不受交换操作的影响，且 $a_1 > 1$，因此我们得出结论：如果 $a_1 \ne 1$，则答案为 $\texttt{No}$。

**充分性**

让我们关注第二次操作。因为我们有 $a_1 = 1$，我们总是可以选择 $i = 1$，然后操作就变成了选择一对 $2 \le j < k \le n$，并交换 $a_k$ 和 $a_j$。我们总是可以用这样的操作进行排序。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[109];
inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0'){
        if (ch == '-'){
        	w = -1;
        }
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0'){
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}
int main(){
    t = read();
    while (t--){
        n = read();
        for (int i = 1; i <= n; i++) a[i] = read();
        if(a[1] == 1){
        	puts("Yes");
        }else{
        	puts("No");
        }
    }
    return 0;
}
```


---

## 作者：Paris_Commune (赞：0)

### 思路

当 $a_1=1$ 时，没有小于 $1$ 的数，所以对剩下的数进行排序即可。 

当 $a_1>1$ 时，无论如何选择 $i,j,k$ ，$a_i$ 的值只能被增加。序列中总会有一个数 $a_i=1$，因为没有小于 $1$ 的数，任意一个 $a_j$ 都无法使 $a_j<a_k$ ，又因为 $a_i$ 只能增加，所以永远不会成为非降序数列。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
    	int a,b;
        cin>>a>>b;
        for(int i=2;i<=a;i++)cin>>a;
        if(b==1)cout<<"Yes\n";
		else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：lmy_2011 (赞：0)

### 题目大意：
$n$个数，用$a_1,a_2,\cdots,a_{n-1},a_n$

- $a_i>a_k$，则$a_i=a_i+a_j$。
- $a_i\leq a_k$，则$swap(a_j,a_k)$。



确定是否可以使数组$a$按非降序排序。



### 思想：
这题乍一看上去十分简单，好像只需模拟即可，只需根据题目条件即可，用一个三重循环枚举：
```cpp
for(int i=1;i<=n;i++)
   for(int j=i+1;j<=n;j++)
    	for(int k=j+1;k<=n;k++)
    		if(a[i]>a[k]) a[i]+=a[j];
    		else if(a[i]<=a[k]) swap(a[j],a[k]);
```

然后预处理一个数组，将此数组排完序后与 $a$ 数组做对比，出现就输出$\mathtt{NO}$，否则输出$\mathtt{YES}$:
```cpp
sort(b+1,b+1+n);
bool flag=false;
for(int i=1;i<=n;i++)
   if(a[i]!=b[i]){
    	cout<<"NO\n";
    	flag=true;
    	break;
   }
   if(!flag)
	cout<<"YES\n";
```




但其实我们忽略了一个重要信息，就是题目中的这句话： $\mathtt{possibly, zero}$ （可以为0）意思就是可以不操作，只要使数组有序不下降即可，所以我们只需在作 ```if(a[i]>a[k])``` 之前特判，如果当前的三个数是有序不下降，就直接跳过。

### 一些小细节：
有些人会问：会不会超时？

答案是：不会。

让我们算一下时间：

整个程序最慢的地方是 $\mathtt{for}$ 循环，$n$ 的上限为 $10$，$t$ 的上限为 $5000$，三重循环的最大执行次数为 $n^3-2$，复杂度省略常数，也就是 $n^3$ 等于 $1000$，$5000\times1000\times4=2\times10^6<10^8$，所以勉强通过，是可行的。


---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1750A)
## 题意
给定一个长度为 $n$ 的排列 $a$。你可以进行任意次下面的操作：

- 选择三个下标 $1\le i < j < k \le n$。
- 如果 $a_i>a_k$，将 $a_i$ 替换成 $a_i+a_j$。否则交换 $a_j,a_k$。

请你判断，能否通过若干次操作，让数组变成非减的。
## 分析
我们发现，如果**序列第一个元素为 $1$**，则一定是整个序列最小的数，所以就可以一直交换 $a_j$ 和 $a_k$，那么我们肯定是能够将序列转变为不降序列的。如果序列第一个元素不为 $1$，则最小的元素一定在后面（除了第一个位置的任意位置），那么我们是不可能通过操作将1放在第一个位置上的，因此就不能实现不降序列。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,a[11];
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(a[1]==1) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：隐仞Mrsu (赞：0)

# 题意
给定一个 $n$ 长的排列，询问是否可以通过以下操作使排列变为不下降的。

取序号 $1\le i < j < k\le n$，进行操作：
- 若 $a_i>a_k$，则将 $a_i$ 改为 $a_i+a_j$；
- 若 $a_i\le a_k$，则将 $a_j$ 与 $a_k$ 交换。


# 分析

观察上述操作，发现排列中**第一个数永远无法变小**。

因为若 $i=1$，当 $a_1>a_k$ 时，$a_1$ 会变为 $a_1+a_j$，又因为排列中每个数都是大于零的，所以此时 $a_1$ 会变大；当 $a_1\le a_k$ 时，交换的是 $a_j$ 和 $a_k$，与 $a_1$ 无关，所以 $a_1$ 永远无法变小。

而不下降的排列中，第一个数肯定是 $1$，所以如果输入的排列第一个数字 不是 $1$，由于上述 $a_1$ 永远无法变小的结论，输出答案就为否。

当输入的排列里，第一个数字为 $1$ 的时候，必然可以通过上述操作实现不下降排列。

因为如果令 $i=1$，由于排列每个元素不重复的性质，后面的数字都比 $1$ 要大，所以**只能做第二个操作**。这样一来，我们取要调整的数字所在位置为 $k$，要将其调整到达的位置为 $j$，这样就可以实现 $a_j$ 与 $a_k$ 的交换，即除了第一个元素，后面的元素想怎么交换位置就怎么交换，所以此时一定可以交换出我们想要的序列。


# 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6+6;
LL _,n,a[N];
void work(){
	cin>>n;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
	}
	if(a[1]!=1){
		cout<<"NO\n";
	}
	else cout<<"YES\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
} 
```


---

## 作者：二叉苹果树 (赞：0)

## 题意

给出长度为 $n$ 的一个排列 $a$，判断其能否通过如的若干次操作，使得原排列单调递增。

- 选择任意三个数 $i,j,k(1\le i<j<k\le n)$.
- 若 $a_i>a_k$，将 $a_i$ 赋值为 $a_i+a_j$，否则，交换 $a_j$ 和 $a_k$ 的值.

## 做法

对于操作第二步中的第一种情况，即 $a_i \to a_i+a_j$，实际上是使得 $a_i$ 变得更大了，而我们要求 $a$ 变得单调递增。所以这一种情况实际上不在考虑范围之内。

而第二种情况，并不会改变 $a_i$ 的值。也就是说，给出的 $a$ 必须满足 $a_1=1$。否则没有操作能使得 $a_1=1$，进而没有操作能够满足题意。

再来考虑 $a_1=1$ 的情况，对于任意一对 $j,k$，有 $a_j>a_k$，我们都可以选择 $i=1$，然后进行操作的第二种情况，使得 $a_j<a_k$。经过若干次操作后，可以使得原序列中一定不存在逆序对，也就满足了 $a$ 单调递增。

```cpp
#include<bits/stdc++.h>

int main()
{
    int t;
    std::cin>>t;
    while(t--)
    {
        int n,x,y;
        std::cin>>n>>x;
        n--; while(n--)
            std::cin>>y;
        if(x!=1)
            std::cout<<"NO"<<std::endl;
        else
            std::cout<<"YES"<<std::endl;
    }
    return 0;
}
```


---

