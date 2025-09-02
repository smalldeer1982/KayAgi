# Hemose Shopping

## 题目描述

Hemose was shopping with his friends Samez, AhmedZ, AshrafEzz, TheSawan and O\_E in Germany. As you know, Hemose and his friends are problem solvers, so they are very clever. Therefore, they will go to all discount markets in Germany.

Hemose has an array of $ n $ integers. He wants Samez to sort the array in the non-decreasing order. Since it would be a too easy problem for Samez, Hemose allows Samez to use only the following operation:

- Choose indices $ i $ and $ j $ such that $ 1 \le i, j \le n $ , and $ \lvert i - j \rvert \geq x $ . Then, swap elements $ a_i $ and $ a_j $ .

Can you tell Samez if there's a way to sort the array in the non-decreasing order by using the operation written above some finite number of times (possibly $ 0 $ )?

## 说明/提示

In the first test case, you can't do any operations.

In the second test case, the array is already sorted.

In the third test case, you can do the operations as follows:

- $ [5,1,2,3,4] $ , $ swap(a_1,a_3) $
- $ [2,1,5,3,4] $ , $ swap(a_2,a_5) $
- $ [2,4,5,3,1] $ , $ swap(a_2,a_4) $
- $ [2,3,5,4,1] $ , $ swap(a_1,a_5) $
- $ [1,3,5,4,2] $ , $ swap(a_2,a_5) $
- $ [1,2,5,4,3] $ , $ swap(a_3,a_5) $
- $ [1,2,3,4,5] $

(Here $ swap(a_i, a_j) $ refers to swapping elements at positions $ i $ , $ j $ ).

## 样例 #1

### 输入

```
4
3 3
3 2 1
4 3
1 2 3 4
5 2
5 1 2 3 4
5 4
1 2 3 4 4```

### 输出

```
NO
YES
YES
YES```

# 题解

## 作者：sunzz3183 (赞：8)

# CF1592B Hemose Shopping

## 题意

给你一个长度为 $n$ 的无序序列 $a$ ，你每次只能交换距离 $ \geq x $ 的两个数，问你能否用非递减顺序对序列 $a$ 进行排序。

## 分析

因为距离没有上限，所以 $a_i$ 可以和 $a_{i+x},a_{i+x+1},a_{i+x+2},...,a_n (i\leq n-x)$ 交换，同理 $a_j$ 可以和 $a_{j-x},a_{j-x-1},a_{j-x-2},...,a_1 (j\geq x+1)$ 交换。

这时，我们把序列 $a$ ，看成一条线，可以互相交换的地方我们称作**被覆盖**：

![](https://cdn.luogu.com.cn/upload/image_hosting/18jp3tml.png)

当 $(n-x)×2 > n $ 既 $ x×2 < n$ 时，可以全部被覆盖：

![](https://cdn.luogu.com.cn/upload/image_hosting/krhcfbcb.png)

当 $(n-x)×2 = n $ 既 $ x×2 = n$ 时，可以全部被覆盖：

![](https://cdn.luogu.com.cn/upload/image_hosting/40j24ntk.png)

当 $(n-x)×2 < n $ 既 $ x×2 > n$ 时，不可以全部被覆盖：

![](https://cdn.luogu.com.cn/upload/image_hosting/l0qziauj.png)

所以当 $x×2 \leq n$ 时，输出 YES 。

那 $ x×2 > n$ 时呢？

我们只要把序列 $a$ 排序一遍，判断没被覆盖的部分是否和排序后一样即可（因为未被覆盖的不能被排序）。

## 代码

```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int t,n,x;
int a[N],b[N];
bool qwq(){
	for(int i=n-x+1;i<=x;i++)
		if(a[i]!=b[i])
			return 0;
	return 1;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i];
		}
		if(x*2<n){
			cout<<"YES\n";
			continue;
		}
		sort(b+1,b+n+1);
		if(qwq())
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：5)

一个经典问题：给定一个数组，每次可以从给定的位置对中选择一对位置并交换这两项，问能否使这个数组不降。

建图连边，每个连通块均可以自由重排，暴力把每个连通块对应的元素排序再放回原数组，然后判断是否满足要求。

回到本题，所有满足 $|a-b|\ge x$ 的 $a,b$ 都会有一条连边，手模一下就会发现只有 $[n-x+1,x]$ 这段区间的点是孤零零的，其余的点构成了一个整的连通块。因此只需要判断原数组的 $[n-x+1,x]$ 和排序后的数组是否一致（如果 $n-x+1>x$ 那么肯定有解）。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1e6+5;
int a[N],b[N],n,x;

void solve(){
	cin>>n>>x;
	fo(i,1,n) a[i]=read(),b[i]=a[i];
	sort(b+1,b+1+n);
	if(x*2<=n){
		puts("YES");
		return;
	}
	fo(i,n-x+1,x) if(a[i]!=b[i]){
		puts("NO");
		return;
	}
	puts("YES");
	return;
}

int main(){
	int T=read();
	while(T--) solve(); 
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：Marsrayd (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1592B)

## 题意简述：

$t$ 组数据。

每组数据给定一个数 $x$ 以及一个长度为 $n$ 的数列 $a_1,a_2,…,a_n$

当 $|j-i|>=x(1\le i,j\le n)$ 时，你可以交换 $a_i,a_j$。

问你能否将这个序列变为从小到大的。

## $\texttt{SOLUTION}$

当 $2\times x\le n$ 时，答案一定是 ```YES```

因为我们可以通过 $a_1,a_n$ 当中转或直接交换排列中的任意两个数字。

我来举个例子：

如果 $n=6,x=3$

$a={1\ 6\ 3\ 5\ 2\ 4}$

- 目标：交换 $3\ 2$
- 操作：
	- 交换 $3\ 4$
   - 交换 $2\ 1$
   - 交换 $2\ 3$
   - 交换 $2\ 4$
   - 交换 $3\ 1$
- 目标：交换 $6\ 4$
- 操作：
	- 交换 $6\ 4$

当 $2\times x\geq n$ 时，我们只能通过上述相同方法任意交换 $a_1,a_2,…,a_{n-x}$ 和 $a_{x+1},a_{n-x+2},…,a_n$。

而 $a_{n-x+1},a_{n-x+1},…,a_{x}$ 无法移动。

设将 $a$ 从小到大排序后为 $s$。

所以如果答案为 ```YES```， $a_{n-x+1},a_{n-x+1},…,a_{x}$ 一定与 $s_{n-x+1},s_{n-x+1},…,s_{x}$相同。

否则答案就为 ```NO```。

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=100010;
int read()
{
	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int n,x,a[MAX],s[MAX];
bool check(int l,int r)
{
	for(int i=1;i<=n;i++) s[i]=a[i];
	sort(s+1,s+n+1);
	for(int i=l;i<=r;i++) if(a[i]!=s[i]) return 0;
	return 1;
}
int main()
{
	int t=read();
	while(t--)
	{
		n=read(),x=read();
		for(int i=1;i<=n;i++) a[i]=read();
		if(2*x<=n) puts("YES");
		else puts(check(n-x+1,x)?"YES":"NO");
	}
	return 0;
}
```




---

## 作者：NiLu (赞：2)

## 分析
如果是 $n>=2*x$ ，答案总是"Yes"因为你可以按照你想要的顺序重新排列数组。否则，你可以交换前 $n-x$ 个元素和后 $n-x$ 个元素，所以你可以按你想要的重新排列它们，但其余的必须保持在它们在已排序数组中的位置。因此，如果原始数组的子数组 $[n-x+1,x]$ 中的元素在排序后处于相同的位置，那么答案是Yes，否则是No。


## 总结
这道题看起来挺复杂，其实还好，代码不必重构

---

## 作者：_Gakki_ (赞：0)

思路：对于任意一个位置 $i$ ，如果它可以被交换那么他一定可以被交换到位置 $1$ 或者 $N$ 
而且 $1$ 和 $N$ 一定也是可以相互交换的(可以用反证法证明如果 $1$ 和 $N$ 不能交换就根本不存在可以交换的元素)，同时任何一个位置 $j$ 它也一定可以和 $1$ 或者 $N$ 交换也就是说对于所有可以交换的位置实际上他们可以任意交换。  
于是只需要判断不可交换的位置的元素摆放是否正确。

```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define pii pair<int,int>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10,maxm = maxn*maxn*4,mod = 1e9+7,inf = 0x3f3f3f3f;
const double pi = acos(-1),eps = 1e-8;

int T;
int n,k;
int a[maxn],b[maxn];


bool solve(){
    sort(b+1,b+1+n);
    for(int i = 1;i <= n;i++){
        if(i-k < 1 && i+k > n){
            if(a[i] != b[i]) return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("in.in","r",stdin);
    //freopen("out.out","w",stdout);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i = 1;i <= n;i++){
            cin>>a[i];
            b[i] = a[i];
        }
        if(solve()) cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}
```


---

## 作者：vvauted (赞：0)

## Description

给出序列 $a$ ，你每次可以交换 $a_i,a_j(|i-j|\geq x)$ ，不限次数，求能不能使序列单调不降。

## Solution
当 $n = 5,x=3$ 时，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gn0goyvz.png)

$1,2,4,5$ 号节点都可以互相自由交换，而只有中间那个动不了，实际上动不了的是一个区间，两端点为：

+ $n-k+1$ （最右边的节点 $n$ 能向左交换的最右节点的下一个）

+ $k$ （最左边的节点 $1$ 能向右交换的最左节点的前一个）


那么则有一个结论：如果这个不能动区间已经是排序后的顺序了，则整体可以排好序，否则就排不好。

那么我们只需要判断这一些不能动区间和排序后的相同与否即可。

具体实现是还要特判：

如果 $x>n$ ，那么我们无法对序列进行操作，则有：

如果原序列已经排好序了，那么为 Yes，否则为 No。

如果 $2x\leq n$ ，那么整个序列都能被操作，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qv7311wa.png)

那么则一定能成功，是 Yes




## Code

```cpp
#include <stdio.h>
#include <algorithm>
#define Maxn 100005
using namespace std;
 
int a[Maxn], b[Maxn];
 
int main() {
	int T, n, x, tag;
	scanf("%d", &T);
	while(T --) {
		tag = 0;
		scanf("%d%d", &n, &x);
		for(int i = 1; i <= n; ++ i) 
			scanf("%d", &a[i]), b[i] = a[i];// 存两遍，另一遍排序
		if(n <= x) {//如果整体不能动
			for(int i = 1; i <= n; ++ i) {
				if(a[i] < a[i - 1]) {//如果全部排好序就可以，否则不行
					tag = 1;
					break;
				}
			}
			if(tag) printf("NO\n");
			else printf("YES\n");
			continue;
		} else if(n >= 2 * x) {//如果全部都能动
			printf("YES\n");
			continue;
		}
		sort(b + 1, b + n + 1);

		for(int i = n - x + 1; i <= x; ++ i) 
			if(a[i] != b[i]) {
				tag = 1;
				break;
			}
		if(tag) printf("NO\n");
		else printf("YES\n");
	}
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先输入 $n$，$x$ 和数列。

设这个数列为 $a$。

很明显，这个数列所能操作的位置，有 $2$ 部分：

$$a[1\to n-x]$$

$$a[x+1\to n]$$

比如，当 $n=5$ 且 $x=4$ 时，能操作的位置只有 $a[1]$ 和 $a[5]$。

这 $2$ 部分能够操作的位置是可以随意交换的，但是，可能中间缺了一部分，这部分是固定的。

那么，如果这部分在排序前和排序后完全吻合，就满足要求，否则不满足要求。

### 2 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_n 100000
int t;
int n;
int k;
int a[max_n+2];
int b[max_n+2];
int l,r;
bool check(){
	l=n-k+1;
	r=k;
	for(int i=l;i<=r;++i){
		if(a[i]!=b[i])return false;
	}
	return true;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1592B_1.in","r",stdin);
	freopen("CF1592B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			b[i]=a[i];
		}
		sort(b+1,b+n+1);
		if(check())puts("YES");
		else puts("NO");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59199260)

By **dengziyue**

---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1592/B)  
[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/15368294.html)  
题目大意：有一个长度为 $n$ 的序列 $a$ 和数字 $x$ ，我们每次可以选定两个数 $i,j$ 满足 $x\le |i-j|$ ，然后交换 $a_i,a_j$ 。请问经过若干次操作是否能让序列 $a$ 递增。  
题目解析：  
我们发现当 $x\le \lfloor \frac{n}{2} \rfloor$ 的时候显然是成立的，因为我们可以通过第三个数字造作三次来交换任意两个数字。  
当然如果序列 $a$ 是递增的话肯定能满足条件。  

所以我们只要考虑 $x>\lfloor \frac{n}{2} \rfloor$ 并且序列 $a$ 不是单调递增的情况。这是我们发现有序列中间一部分的序列是不能动的，而其他部分的序列是可以随意交换的，方法类似于上面的方法的。  
我们发现，这个时候序列中 $a_{n-x+1},a_{n-x+2},\dots,a_x$ 这一段是不能移动的，而其他的都能任意交换。  
所以需要不能移动的部分递增，能任意移动的部分可以通过移动保证序列递增就可以了。我们只需要统计能移动的部分小于等于 $a_{n-x+1}$ 和大于等于 $a_x$ 的数字的个数就可以了。当然注意考虑一下 $a_{n-x+1}=a_x$ 的情况。  

代码（去除了快读&一堆没用的宏定义&头文件）：
```cpp
int T,n,x,a[maxn];
int checkup(){
	for(RI i=1;i<n;i++) if(a[i]>a[i+1]) return 0;
	return 1;
}
int check(){
	if(x<=(n>>1)) return 1; if(x>=n) return checkup();
	RI i,cnt1=0,cnt2=0,minx=INF,maxx=-INF; x=n-x;
	for(i=x+1;i<=n-x;i++){
		maxx=max(maxx,a[i]); minx=min(minx,a[i]);
		if(i!=n-x&&a[i]>a[i+1]) return 0;
	}
	for(i=1;i<=x;i++)
		{ if(a[i]<minx) cnt1++; if(a[i]==minx) cnt2++; if(minx<a[i]&&a[i]<maxx) return 0; }
	for(i=n-x+1;i<=n;i++)
		{ if(a[i]<minx) cnt1++; if(a[i]==minx) cnt2++; if(minx<a[i]&&a[i]<maxx) return 0; }
	if(minx==maxx) return cnt1+cnt2>=x && cnt1<=x;
	return cnt1+cnt2==x;
}
int main(){
	T=read(); while(T--){
		n=read(); x=read(); for(RI i=1;i<=n;i++) a[i]=read();
		if(check()) puts("YES"); else puts("NO");
	}
	return 0;
}
```

---

