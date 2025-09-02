# Mocha and Hiking

## 题目描述

The city where Mocha lives in is called Zhijiang. There are $ n+1 $ villages and $ 2n-1 $ directed roads in this city.

There are two kinds of roads:

- $ n-1 $ roads are from village $ i $ to village $ i+1 $ , for all $ 1\leq i \leq n-1 $ .
- $ n $ roads can be described by a sequence $ a_1,\ldots,a_n $ . If $ a_i=0 $ , the $ i $ -th of these roads goes from village $ i $ to village $ n+1 $ , otherwise it goes from village $ n+1 $ to village $ i $ , for all $ 1\leq i\leq n $ .

Mocha plans to go hiking with Taki this weekend. To avoid the trip being boring, they plan to go through every village exactly once. They can start and finish at any villages. Can you help them to draw up a plan?

## 说明/提示

In the first test case, the city looks like the following graph:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/c2e581af2a9a8a7c84fbcdcb044c393f08812267.png)

So all possible answers are $ (1 \to 4 \to 2 \to 3) $ , $ (1 \to 2 \to 3 \to 4) $ .

In the second test case, the city looks like the following graph:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/50cae05bb483d2eef22f0fe8c5bad7425f443436.png)

So all possible answers are $ (4 \to 1 \to 2 \to 3) $ , $ (1 \to 2 \to 3 \to 4) $ , $ (3 \to 4 \to 1 \to 2) $ , $ (2 \to 3 \to 4 \to 1) $ .

## 样例 #1

### 输入

```
2
3
0 1 0
3
1 1 0```

### 输出

```
1 4 2 3 
4 1 2 3```

# 题解

## 作者：thhxxx (赞：3)

# 分析

分析题意，我们知道一共有 $n + 1$ 座城市，而 1 到 $n$ 号城市必然连同。

不难得出有三种情况

1. $n + 1$ 号城市可通向 1 号城市。
2. $n$ 号城市可通向 $n + 1$ 号城市。
3. 某座编号 $k$ 的城市能通向 $n + 1$ 号城市，且 $n + 1$ 号城市能通向 $k + 1$ 号城市。

于是得出以下代码。最坏情况时间复杂度为 $O(n)$。

# AC 代码

```
#include <iostream>

using namespace std;

int rd[10010];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--)
	{
		int n;
		cin >> n;

		for (int i = 1; i <= n; i++)
		{
			cin >> rd[i];
		}

		if (rd[1] == 1)
		{
			cout << n + 1 << ' ';
			for (int i = 1; i < n; i++) cout << i << ' ';
			cout << n << '\n';
		}

		else if (rd[n] == 0)
		{
			for (int i = 1; i <= n; i++) cout << i << ' ';
			cout << n + 1 << '\n';
		}

		else
		{
			int pos = 0;
			for (int i = 1; i < n; i ++)
			{
				if (rd[i] == 0 && rd[i + 1] == 1)
				{
					pos = i;
					break;
				}
			}

			for (int i = 1; i <= pos; i++) cout << i << ' ';
			cout << n + 1 << ' ';
			for (int i = pos + 1; i < n; i++) cout << i << ' ';
			cout << n << '\n';
		}
	}
}
```

---

## 作者：sunzz3183 (赞：1)

# CF1559C Mocha and Hiking

## 题意

给你 $n$ 个点，$1→2→...→n$ 都有一条无向路径，还有一个点 $n+1$ ， $1$ 到 $n$ 的点都对 $n+1$ ，有一条有向边，边可能是入边，也有可能是出边。现在，你要从任意一点出发，到任意一点，途中你必须走过每一个点，并且每一个点只能走一次。

## 思路

看题我们发现，只有三种路：

1. $n+1→1→2→3→...→n$

2. $1→2→3→...→n→n+1$

3. $1→2→3→...→i→n+→i+1→...→n$

那如和判断呢？

有如果 $n+1 →1$ ，则第一种路可走（即 $a_1=1$ ）。

有如果 $n →n+1$ ，则第二种路可走（即 $a_n=0$ ）。

有如果 $i →n+1→i+1$ ，则第三种路可走（即 $a_i=0$ 并且 $a_{i+1}=1$ ）。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int T,n,a[10010];
string c;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		bool qwq=1;
		if(a[1]==1){//第一种路
			cout<<n+1<<" ";
			for(int i=1;i<=n;i++)
				cout<<i<<" ";
			cout<<"\n";
			continue;
		}
		if(a[n]==0){//第二种路
			for(int i=1;i<=n;i++)
				cout<<i<<" ";
			cout<<n+1<<"\n";
			continue;
		}
		for(int i=1;i<n;i++){
			if(a[i]==0&&a[i+1]==1){//第三种路
				for(int j=1;j<=i;j++)
					cout<<j<<" ";
				cout<<n+1<<" ";
				for(int j=i+1;j<=n;j++)
					cout<<j<<" ";
				qwq=0;
				break;
			}
		}
		if(qwq){
			cout<<"-1\n";
		}
	}
	return 0;
} 
```




---

## 作者：江户川·萝卜 (赞：1)

### 题意
给定一张有向图，$n+1$ 个点和 $2n-1$ 条边，其中 $n-1$ 条边是 $i\to i+1(1\le i <n)$，另外 $n$ 条边由 01 序列 $a$ 给出。

- 若 $a_i=0$ 则这条边是 $i\to n+1$。
- 若 $a_i=1$ 则这条边是 $n+1 \to i$。

---
首先，如果 $a_1=1$  说明 $n+1$ 可以走向 $1$，而 $1\to 2\to3 \to \cdots \to n$ 所以直接输出：

```
n+1 1 2 3 ... n
```

否则，找到第一个 $a_i=0 \&\& a_{i+1}=1 (1\le i <n)$，说明在 $i$ 的部分可以直接走到 $n+1$ 再回来 $i+1$。所以输出：

```
1 2 3 ... i n+1 i+1 ... n
```

最后，如果 $a_n=0$ 就可以从 $n\to n+1$。所以输出

```
1 2 3 ... n n+1
```

容易发现没有 `-1` 情况。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[10005];
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		if(!a[1]){
			bool win=0;int d;
			for(int i=1;i<n;i++)if(!a[i]&&a[i+1]) win=1,d=i;
			if(!win&&a[n]) puts("-1");
			else{
				if(!win) d=n;
				for(int i=1;i<=d;i++) printf("%d ",i);
				printf("%d ",n+1);
				for(int i=d+1;i<=n;i++) printf("%d ",i);
				puts("");
			}
		}
		else{
			printf("%d ",n+1);
			for(int i=1;i<=n;i++) printf("%d ",i);
			puts(""); 
		}
	}
} 
```

---

## 作者：到底几只鱼呢 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1559C)

废话：

这题感觉上是一个细节多 ~~主要我粗心~~ 的构造，然后稍不注意这题就跟 A 题一样了。

正文：

为了方便描述，我们把连接 $1-n$ 的 $n-1$ 条边称之为 A 型边，把与 $n+1$ 号点连接的边叫 B 型边。

题目的给定信息可以用一个 **01串** 描述，对于一个给定的串，容易发现：

- 若存在形如 `01` 这样的一个子串，我们可以先走 A 型边到达这个信息为 `0` 的点，再跳到 $n+1$ 号点上，然后通过一条反着连向信息为 `1` 的点的 B 型边回到 A 型边直至到达 $n$ 号点。

- 若不存在，那么只有三种情况：

 	+ 没有 `0` 的信息，即串形如：`111111...`。
    
   + 只在结尾有 `0` 的信息，即串形如：`1111...110`。
   
   + 只有 `0` 的信息，即串形如：`000000...`。
   
  对于这三种情况，前两种我们可以合并，即都按 $n+1,1,2,...,n$ 的顺序遍历，对于第三种，我们可以直接按 $1,2,...,n,n+1$ 的顺序遍历。
  
  于是特判这三种情况就好 ~~(注意细节)~~。
  
##   Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace DCM{
    const int maxn=2e4+10;
    int T,n,a[maxn];
    void work() {
        cin>>T;
        while(T--) {
            cin>>n; 
            int id=-1;
            for(int i=1;i<=n;i++) cin>>a[i];
            if(n==1&&a[1]==0) {
            	cout<<"1 2\n";continue;
			}
			if(n==1&&a[1]==1) {
            	cout<<"2 1\n";continue;
			}
            for(int i=1;i<n;i++) if(a[i]==0&&a[i+1]==1) id=i;
            if(~id) {
	            for(int i=1;i<=id;i++) cout<<i<<' ';
	            cout<<n+1<<' ';
	            for(int i=id+1;i<=n;i++) cout<<i<<' ';
	            cout<<'\n';
	            continue;
			}
            else if(a[1]==1) {
            	cout<<n+1<<' ';
            	for(int i=1;i<=n;i++) cout<<i<<' ';
            	cout<<'\n';
            	continue;
			}
			else {
				for(int i=1;i<=n+1;i++) cout<<i<<' ';
            	cout<<'\n';
			}
        }
    }
}
int main() {
    return DCM::work(),0;
}
```

---

## 作者：zhanghengrui (赞：0)

考虑第一个从 $n+1$ 到 $u$ 的边对应的结点 $u$

如果存在，方案就是 $1 \to \cdots \to u-1 \to n+1 \to u \to \cdots \to n$，因为要么 $u-1$ 不存在要么 $u-1$ 到 $n+1$ 有边

如果不存在，说明所有边都是从 $i$ 到 $n+1$，方案就是直接 $1 \to \cdots \to n+1$；假设 $u = n+1$，我们会发现这种情况和上面几乎是一样的

代码写起来还算简洁，并不需要各种分类讨论  
~~而且行末不会有多的空格，不怕强迫症~~

```cpp
unsigned short n, index;
std::vector<unsigned short> a;
std::cin >> n;
a.resize(n);
for (unsigned short i = 0; i < n; ++i)
  std::cin >> a[i];
// 注意下标从 0 开始，所以 index 实际上是 u - 1
// std::find 在没有找到的情况下会返回 end，此时 index = n
index = std::find(a.begin(), a.end(), 1) - a.begin();
for (unsigned short i = 1; i <= index; ++i)
  std::cout << i << ' ';
std::cout << n + 1;
for (unsigned short i = index + 1; i <= n; ++i)
  std::cout << ' ' << i;
std::cout << '\n';
```

---

## 作者：sycqwq (赞：0)

__思路__

方案分为三种情况

1.$a_1=1$，即从 $n+1$ 号城市有一条到 $1$ 号城市的边，就从 $n+1$ 号城市前往 $1$ 号城市，然后再前往 $3$ 号城市

2.$a_n=0$，即从 $n$ 到 $n+1$ 有一条边，就可以从 $1$ 出发，然后到达 $n$，再去 $n+1$

3.从 $1$ 出发，找一个城市 $x$，满足 $a_x=0$并且 $a_{x+1}=1$，即可以从 $1$ 到 $x$ ,然后再到 $n+1$,然后到 $x+1$，最好再到 $n$，就行了

__代码__

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[10005];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n;
        cin>>n;
        for(int j=1;j<=n;j++)
            cin>>a[j];
        if(a[1]==1)
        {
            cout<<n+1<<' ';
            for(int i=1;i<=n;i++)
                cout<<i<<' ';
            cout<<endl;
            continue;
        }
        if(a[n]==0)
        {
            for(int i=1;i<=n+1;i++)
                cout<<i<<' ';
            cout<<endl;
            continue;
        }
        for(int j=1;j<=n;j++)
        {
            if(a[j]!=a[j+1]&&j!=n)
            {
                for(int k=1;k<=j;k++)
                    cout<<k<<' ';
                cout<<n+1<<' ';
                for(int k=j+1;k<=n;k++)
                    cout<<k<<' ';
                cout<<endl;
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

对于 $i\ (i\in[1,n-1])$，如果 $i$ 要走到 $i+1$，只有 $2$ 种路径：

$$i\to i+1$$

和：

$$i\to n+1\to i+1$$

且不可能有 $i+1\to i$ 的路径。

那么，我们可以规划出可能的路径：

$$1\to2\to3\to...\to i\to n+1\to i+1\to i+2\to......\to n\ (i\in[0,n])$$

有点难理解是吧，那么可以细分为 $3$ 种：

+ $n+1$ 开始，依次经过 $1$ 到 $n$；

+ $1$ 开始，经过某个点 $i\ (i\in[1,n-1])$ 的时候前往 $n+1$，又回到 $i+1$，继续依次走到 $n$；

+ $1$ 开始依次走到 $n+1$。

也就是说，只要满足一下 $3$ 个条件的至少一种，就可以有路径；否则没有：

+ $a[1]=1$；

+ 存在 $i\in([1,n-1])$，使得 $a[i]=0$ 且 $a[i+1]=1$；

+ $a[n]=0$

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 10000
int t;
int n;
int a[max_n+20];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1559C_1.in","r",stdin);
	freopen("CF1559C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1,k;ca<=t;++ca){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		a[0]=0;
		a[n+1]=1;
		for(k=0;k<=n;++k){
			if(a[k]==0&&a[k+1]==1)break;
		}
		if(k>n){
			printf("-1\n");
			continue;
		}
		if(k==0){
			printf("%d",n+1);
			for(int i=1;i<=n;++i)printf(" %d",i);
			printf("\n");
			continue;
		}
		for(int i=1;i<=n;++i){
			printf("%d ",i);
			if(i==k)printf("%d ",n+1);
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56080891)

By **dengziyue**

---

## 作者：Doubeecat (赞：0)

> 有一张有 $n+1$ 个点和 $2n-1$ 条有向边的图，边有以下两种：
>
> 1. 对于所有 $1 \leq i < n$，有 $n-1$ 条从 $i$ 到 $i+1$ 的边
> 2. 对于所有 $1 \leq i \leq n$，有 $n$ 条 $i$ 与 $n+1$ 的单向边，若 $a_i = 0$，为从 $i$ 到 $n+1$ 的边，反之则为从 $n+1$ 到 $i$ 的边。
>
> 现在请你求出这张图的一个哈密顿回路，若不存在输出 $-1$
>
> $T\leq 20,n \leq 10^4$ 

思维题。

首先我们考虑怎样经过 $n+1$​ 这个点，因为其他点都可以直接走到。我们考虑如果有 $a_i = 0,a_{i+1} = 1$​ 即一个走到 $n+1$ 一个走回来，那我们必然可以从 $i$ 走到 $n+1$​​ 然后再走到 $i+1$，这样就能遍历完整张图了。

最开始我单纯考虑了这种情况，然后贡献了三发罚时。

我们发现，若 $a_1 = 1$，实际上我们可以从 $n+1$ 出发遍历整张图，若 $a_n = 0$ 我们可以直接从 $n$ 到 $n+1$。

关于无解，实际上通过上面的方法我们可以证明出这张图必定存在一条哈密顿回路。所以本题直接按照上面的方法构造就行了。

时间复杂度 $O(n)$

## 代码

```cpp
void solve() {
    read(n);
    for (int i = 1;i <= n;++i) read(a[i]);
    int pos = 0,pos1 = 0;
    if (!a[n]) {
        for (int i = 1;i <= n+1;++i) printf("%d ",i);
        puts("");
        return ;
    }
    bool flag = 0;
    for (int i = 1;i <= n;++i) {
        if (a[i] == 0) {
            pos = i;flag = 1;
        }
    }
    if (!flag) {
        printf("%d ",n+1);
        for (int i = 1;i <= n;++i) printf("%d ",i);
        puts("");
        return ;
    }
    for (int i = 1;i <= pos;++i) printf("%d ",i);
    printf("%d ",n+1);
    for (int i = pos+1;i <= n;++i) printf("%d ",i); 
    puts("");
}
```

---

## 作者：Refined_heart (赞：0)

题目大意：给定一条 $1\to n$ 的链，并且每个点与 $n$ 都有向外或者向内连的边，问有没有一种方案可以走过所有点并且只经过一次。

考虑如何利用 $n+1$ 连接的点的性质。

显然如果第一个点可以从 $n+1$ 到达就直接构造解。

如果有两个相邻的点满足一个进 $n+1$ 一个出 $n+1$ 也是可以的。

也可能从某个点走过去再经过 $n+1$ 回来把剩下的点走完。

这些情况足以。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
const int N=2e4+10;
int head[N],tot,n,m;
int a[N];
int main(){
    scanf("%d",&T);while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        int sum=0,pos=-1;
        for(int i=1;i<=n;++i)sum+=a[i];
        for(int i=1;i<n;++i){
            if(a[i]==0&&a[i+1]==1){
                pos=i;
                break;
            }
        }
        if(a[1]==1){
            printf("%d ",n+1);
            for(int i=1;i<=n;++i)printf("%d ",i);
            puts("");
            continue;
        }
        if(a[1]==0&&a[2]==1){
            printf("%d %d ",1,n+1);
            for(int i=2;i<=n;++i)printf("%d ",i);
            puts("");
            continue;
        }
        if(a[n]==0){
            for(int i=1;i<=n+1;++i)printf("%d ",i);
            continue;
        }
        if(pos){
            for(int i=1;i<=pos;++i)printf("%d ",i);
            printf("%d ",n+1);
            for(int i=pos+1;i<=n;++i)printf("%d ",i);
            continue;
        }
        puts("-1");
    }
    return 0;
}
```

---

