# Angry Monk

## 题目描述

To celebrate his recovery, k1o0n has baked an enormous $ n $ metres long potato casserole.

Turns out, Noobish\_Monk just can't stand potatoes, so he decided to ruin k1o0n's meal. He has cut it into $ k $ pieces, of lengths $ a_1, a_2, \dots, a_k $ meters.

k1o0n wasn't keen on that. Luckily, everything can be fixed. In order to do that, k1o0n can do one of the following operations:

- Pick a piece with length $ a_i \ge 2 $ and divide it into two pieces with lengths $ 1 $ and $ a_i - 1 $ . As a result, the number of pieces will increase by $ 1 $ ;
- Pick a slice $ a_i $ and another slice with length $ a_j=1 $ ( $ i \ne j $ ) and merge them into one piece with length $ a_i+1 $ . As a result, the number of pieces will decrease by $ 1 $ .

Help k1o0n to find the minimum number of operations he needs to do in order to merge the casserole into one piece with length $ n $ .

For example, if $ n=5 $ , $ k=2 $ and $ a = [3, 2] $ , it is optimal to do the following:

1. Divide the piece with length $ 2 $ into two pieces with lengths $ 2-1=1 $ and $ 1 $ , as a result $ a = [3, 1, 1] $ .
2. Merge the piece with length $ 3 $ and the piece with length $ 1 $ , as a result $ a = [4, 1] $ .
3. Merge the piece with length $ 4 $ and the piece with length $ 1 $ , as a result $ a = [5] $ .

## 样例 #1

### 输入

```
4
5 3
3 1 1
5 2
3 2
11 4
2 3 1 5
16 6
1 6 1 1 1 6```

### 输出

```
2
3
9
15```

# 题解

## 作者：Garry_HJR (赞：4)

## 题意

给定 $k(1\le k \le 10^5)$ 个正整数 $a_1,a_2,\dots,a_k$。

你可以进行无限次的操作。每次操作可从下面两项中任选一项。

1. 选择一个数 $a(a>1)$，将其分成 $1$ 和 $a-1$。

2. 选择一个 $1$ 和一个数 $b$，合并为 $b+1$。

要求把这 $k$ 个数全都并为 $1$ 个，求最少操作次数。

## 思路分析
### 若 $k=2$
我们发现，对于两个数 $A,B$，设 $C=\min(A,B)$，它们可以合起来的最少步数是 $2\times C -1$。

考虑证明：根据题意，我们可以发现一个数想要合并只能和 $1$ 合并。

那么没有 $1$ 怎么办？我们拆。

拆的话一定是拆比较小的。设 $A<B$。

那么拆 $A$ 需要 $A-1$ 次，而拆 $B$ 要 $B-1$ 次，$A<B$，因此拆 $A$ 更合适。

现在 $A$ 被拆成了 $A$ 个 $1$。

那么接下来只需要把 $A$ 同这 $A$ 个 $1$ 合并就可以了，这也需要 $A$ 步。

因此，答案就是 $A+(A-1)=2 \times A -1$。
### 推广
前面 $k=2$ 的时候我们考虑的是把最大的留下，拆小的。

到了 $k>2$ 时，也是如此。

我们直接先把 $a$ 从小到大排序。

然后把 $a_k$ 留下，把其他的全拆了。

那么拆这些需要 $a_1-1+a_2-1+a_3-1+\dots+a_{k-1}-1=a_1+a_2+a_3+\dots+a_{k-1}-(k-1)$ 步。

那么 $a_1$ 被拆成了 $a_1$ 个 $1$，$a_2$ 被拆成了 $a_2$ 个 $1$，如此下去，$a_{k-1}$ 被拆成了 $a_{k-1}$ 个 $1$。

现在我们要做的就是把这些 $1$ 加起来，那么这需要 $a_1+a_2+a_3+\dots+a_{k-1}$ 步。

所以答案就是把这两部分加起来，即 $a_1+a_2+a_3+\dots+a_{k-1}-(k-1)+a_1+a_2+a_3+\dots+a_{k-1}=2 \times (a_1+a_2+a_3+\dots+a_{k-1})-(k-1)$。

得解。

## 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
int a[100005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=k;i++)cin>>a[i];
		sort(a+1,a+k+1);
		long long ans=0;
		for(int i=1;i<k;i++)ans+=(a[i]-1);
		for(int i=1;i<k;i++)ans+=a[i];
		cout<<ans<<endl;
	}
}
```

---

## 作者：__zyq_666_kpzc__ (赞：3)

### [中文题面](https://vjudge.net.cn/problem/CodeForces-1992B#author=GPT_zh)
### 思路分析
已知：将一个长度为 $k$ 的土豆烩块全部切开，再全部合并到大土豆烩块上一共需要 $2n-1$ 的操作步数。

根据题意，我们可以得出要在尽量少的操作次数中获得尽量大的土豆烩，必定是以最大的那一块土豆烩块为基础，在上面叠加其余的土豆烩块即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[100005],ans=0;
void w(){
    int ma=-1e9;
	ans=0;
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i],ma=max(ma,a[i]);
	}
	n-=ma;
	for(int i=1;i<=k;i++){
		if(n==0)break;
		if(a[i]==ma){
			ma=0;
			continue; 
		}
		if(n-a[i]<0){
			ans+=n*2;
			break;
		} 
		ans+=a[i]*2-1;
		n-=a[i];
	}
	cout<<ans<<"\n";
} 
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
  	int T;
	cin>>T;
	while(T--){
		w();
	} 
	return 0;
} 
```

---

## 作者：shiziyu111 (赞：1)

~~我以为这道题很简单，可是它成功的把我拖了半小时~~。
## 题目巨意
一个总长度为 $n$ 的饭菜被分成了 $k$ 段，第 $i$ 块长度为 $a_i$，现可以进行以下操作。

1. 把一个长度 $\ge 2$ 的片段中一个长度为 $1$ 的片段分解出去（即分解成 $a_i-1$ 和 $1$）。
1. 把一个片段与另一个长度为 $1$ 的片段组合（即将 $a_i$ 和 $1$ 组合成 $a_i+1$）。

求把他们组合成一个片段的最少次数。
## 分析

由于我们只能将 $a_i$ 和 $1$ 进行组合，所以我们只能将除一个片段以外的所有片段进行分解。

那么我们应该保留那个片段呢？由于我们求的是最少次数，所以我们应该保留最大片段。

那么我们该如何统计操作次数呢？不妨设我们保留的最大片段为 $maxx$。

先计算组合次数，我们只需求出 $n-maxx$ 的值就行了。

再计算分解次数，我们知道，片段次数为 $k-1$，即 $k-1$ 个长度为 $1$ 的片段不用被分解出去，剩下的片段长度是 $n-maxx$，因此分解次数为 $(n-maxx)-(k-1)$。

在分析完之后，就到了我们最喜欢的：
## 我爱打代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		int n,zz,m,maxx=0;
		cin>>n>>m;
		for(int j=1;j<=m;j++)
		{
			cin>>zz;
			maxx=max(maxx,zz);
		}
		cout<<(n-maxx)+((n-maxx)-(m-1))<<endl;
	}
	return 0;
}
```

---

## 作者：luckyqwq (赞：1)

# CF1992B Angry Monk 题解

### 大致思路：

首先我们知道，将一个数字 $x$ 拆分成多个 $1$，再一次拼接到另一个数字上总共需要花费 $x × 2 - 1$ 的时间。显然最优情况下，肯定是把 $k$ 个数字，按照上述操作，直接拼接到同一个数字上是最优的，这是我们可以分类讨论，考虑两种极端情况：

- 假设把序列中所有数字拼接到最小的那个数上，那么需要花费的时间为 $\sum_{i = 1}^{k}a_i × 2 - 1$ 减去最小的那个数进行拆解，拼接操作所需要的花费时间。

- 假设把序列中所有数字拼接到最大的那个数上，那么需要花费的时间为 $\sum_{i = 1}^{k}a_i × 2 - 1$ 减去最大的那个数进行拆解，拼接操作所需要的花费时间。

显然第二种情况最优，所以按照方案二贪心即可。

### 代码实现：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int P = 1e9 + 7;
const int N = 1e5 + 10;
int T, n, k, a[N];
signed main()
{
    cin >> T;
    while (T --)
    {
        int res = 0;
        cin >> n >> k;
        for (int i = 1;i <= k; ++ i) cin >> a[i];
        sort(a + 1, a + k + 1);
        for (int i = 1;i < k; ++ i)
        {
            res += (a[i] * 2 - 1);
        }
        cout << res << "\n";
        
    }
}
```

这样这道题目就完成啦！！！

---

## 作者：xcms (赞：0)

# CF1992B Angry Monk

为了使操作次数最小，肯定要使最大的数作为那个合并其它 $1$ 的数。不然就需要把最大的数分解成几个 $1$，然后再把这些 $1$ 合并，这显然不是最优的。

本题思路：首先把数组 $a$ 从大到小排序，来确定最大值。然后把除最大值以外剩下的数分解成一些 $1$，每个 $a_i$ 需要 $a_i-1$ 次。最后把这些 $1$ 合并，总共需要 $\sum_{i=2}^{k} a_i$ 次，所以最后输出的数为 $\sum_{i=2}^{k} a_i\times2-1$。

主要代码如下。

```cpp
for(int i=1;i<=k;i++){
	cin>>a[i];
	ans+=a[i]*2-1;
}
sort(a+1,a+1+k,greater<int>());
ans=ans+1-a[1]*2;1]*2;
```

---

## 作者：__DayLight__ (赞：0)

## 前言
[原题机翻。](https://www.luogu.com.cn/paste/qkkbdlcl)

## 思路

由题目描述的操作可知：

- 合并操作中的两块土豆块至少有一块长 $1$ 米。

所以我们只能留下**一块**长度超过 $1$ 的土豆块，否则合并操作将无法实现。

步骤如下：
1. 为了保证操作次数最少，所以便留下长度最长的土豆块，通过输入的同时打擂台实现。

1. 将其他土豆块通过分块操作分成 $a_i$ 块长度为 $1$ 的土豆块，每块土豆块的操作次数为 $a_i-1$。

1. 将分出来的土豆块与最长的土豆块合并，操作次数为长度为 $1$ 的土豆块的数量。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int K=2e5+5;
int t,n,k,a[K];
signed main(){
 	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
 	while(t--)
 	{
 		cin>>n>>k;
 		int maxx=0,maxi;
 		for(int i=1; i<=k; i++)
 		{
 			cin>>a[i];
 			if(a[i]>maxx)maxx=a[i],maxi=i;//找最长的土豆块，记录下标。 
 		}
 		int ans=0,sum=0;
 		for(int i=1; i<=k; i++)
 			if(i!=maxi)
			{
				ans+=a[i]-1;//分块。
				sum+=a[i];//记录长度为 1 的土豆块的数量。 
			} 
 		cout<<ans+sum<<'\n';
 	}
	return 0;
}
```

---

## 作者：coding_goat (赞：0)

因为每一个块都要分成 $1$ 再合并，因此只保留最大的块，剩下的块全都拆成 $1$ 再进行合并，若块的大小为 $x$，则会有 $2\times x - 1$ 的步数让他合到最大的块。

可以考虑排序将最大值丢在最后，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 200050

int n,k,a[maxn];

void work()
{
	n=read(),k=read();
	for(int i=1;i<=k;i++)
		a[i]=read();
	sort(a+1,a+k+1);
	int ans=0;
	for(int i=1;i<k;i++)
		ans+=(a[i]*2)-1;
	cout<<ans<<'\n';
}

signed main()
{
	int _=read();
	while(_--) work();
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# CF1992B Angry Monk
## 题目大意
~~完全看不懂，身为蒟蒻的我好帕帕~~。有 $k$ 根小棒，给出每根小棒的长度 $a _ {i}$ 和总长度 $n$，可以执行两种操作：截下一个长度为 $1$ 的片段，或将一个长度为 $1$ 的片段与另一个片段合并。求使所有小棒合并成一根的最小操作次数。
## 思路分析
由于最后要合并成一根小棒，所以考虑贪心，将所有小棒合并到最长的那一根上，可以使操作数量最小。    
一根长度为 $x$ 的小棒，需要操作 $x-1$ 次才能全部分成长度为 $1$ 的小棒。而所有小棒都分完后，总共需要合并 $n-maxn$ 次（ $maxn$ 表示最长的小棒长度）。
## AC Code
```cpp
#include <bits/stdc++.h> 
using namespace std;
long long t,n,k,a[100005];
int main(){
    cin>>t;
    while (t--){
        long long ans=0,maxn=-1;
        cin>>n>>k;
        for (int i=1;i<=k;i++) {cin>>a[i];maxn=max(a[i],maxn);}
        ans+=(n-maxn);
        for (int i=1;i<=k;i++){
            if (a[i]==maxn) maxn=-1;
            else ans+=a[i]-1;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
### 更新日志
2024年7月17日：更正了标点符号的错误。

---

## 作者：_ayaka_ (赞：0)

### 题意
给出两个数 $n$ 与 $k$，并给出一个有 $k$ 个数的数列 $a$，满足 $\sum_{i=1}^{k} a_i =n$。

你可以进行以下操作：

1. 将一个数 $a_i$ 拆解为 $a_i-1$ 与 $1$ 两项。
1. 将两个数 $a_i$ 与另一个数 $a_j=1$ 合并成 $a_i+1$ 一项。

求需要多少次操作才能让 $a$ 这个序列中的项仅剩一个。

### 思路

我们需要将数列合并成一项，而合并这个操作就只有操作 $2$ 能实现，那我们只能利用操作 $2$ 来合并了。而操作 $2$ 合并的条件就是需要另一项为 $1$，那我们的方法便只有留下一个项，将其他项全部拆解为 $1$ 并依次与留下的项进行合并。为了次数最优，留下的需是数列中的最大值。

直接模拟是不行的，因为 $n$ 极大，会超时。但很明显，这个方法是有规律可循的，我们假设最大的项为 $maxa$，那答案就可以这样计算：

- 首先合并操作，需要进行 $n-maxa$ 次；（因为拆完会有 $(n-maxa)$ 个 $1$）
- 其次是分解操作，需要进行 $n-maxa-(k-1)$ 次；（在合并的次数基础上，我们可以视为由第一个项分出了 $k-1$ 个项）
- 最后相加，所需的次数就为 $2\times(n-maxa)-(k-1)$ 次。

时间复杂度 $O(k)$。（只有输入耗时）

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,a,maxa;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		maxa=0;//记得清零
		for(int i=1;i<=k;i++){
			cin>>a;
			maxa=max(a,maxa);//打擂台都会吧ama
		}
		cout<<2*(n-maxa)-(k-1)<<"\n";
	}
	return 0;
}

```

---

## 作者：Infinite_Loop (赞：0)

# CF1992B
## 题意
给定 $k$ 根棒子，第 $i$ 根棒子的长度为 $a_{i}$，并且 $\sum_{i=1}^k a_{i}=n$。

现在可以进行若干次操作：

- 如果 $a_{i}\ge2$，那么可以将 $a_{i}$ 分为 $1$ 和 $a_{i}-1$。
- 如果有 $a_{i}$ 和 $a_{j}$ 保证 $i \ne j$ 且 $a_{j}=1$，那么可以将它们合并成 $a_{i}+1$。

问将所有元素合并为一个元素至少需要的操作次数。
## 思路
本题考虑找规律。

看几组样例即可发现最优的方案：

- 先找到数组中最大的数字 $x$。
- 然后将除最大值以外的数全部分解成 $1$，操作数为 $n-x$。
- 最后将所有数合并，$a_{i}$ 需要 $a_{i}-1$ 个操作（$a_{i} \ne x$）。

最后输出总共的操作数即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,k,a[N];
void solve(){
	cin>>n>>k;
	int mx=0;
	for(int i=1;i<=k;i++){
		cin>>a[i];
		mx=max(mx,a[i]);
	}
	long long ans=n-mx,flag=1;
	for(int i=1;i<=k;i++){
		if(a[i]==mx&&flag){
			flag=0;
			continue;
		}
		ans+=a[i]-1;
	}
	cout<<ans<<'\n';
}
int main(){
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 形式化题意
有 $k$ 根总长为 $n$ 的块，可以执行以下操作：
- 如果有一个长度为 $a_i$ 的块且 $a_i \ge 2$，可以将 $a_i$ 分出一个长度为 $1$ 的块。
- 将任意块和一个长度为 $1$ 的块合并为一个新的块。

你需要输出所有块合并的最小操作步数。
## 思路
其他题解似乎没有步骤，我讲一下：

最优解是把最大值外的所有块分成 $1$。为什么呢？因为如果你想要合并两堆需要有一堆是 $1$，所以你要让把最大值外的所有块分成 $1$，然后合并到最大值里，如果分解最大值一定不优。可以用优先队列模拟，但会超时。

考虑计算公式，已给出总和 $n$，用 $n$ 减去最大值 $maxans$，得出分割的花费，然后合并花费相同花费，注意有 $k-1$ 块分割时多出了一次花费，所以减去 $k-1$。总花费：

$$2(n-m)-(k-1)$$
## 代码
复杂度 $O(Tk)$，应该是最优解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,x;
int main(){cin>>T;
    while(T--){cin>>n>>k;int maxans=0;
        for(int i=1;i<=k;i++){
            cin>>x;maxans=max(maxans,x);
        }cout<<2*(n-maxans)-(k-1)<<endl;
    }
    return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

我们要做“合并”，但根据规则必须要是 $x+1+1+1+\dots +1$。

尽可能少的操作，需要最大化 $x$。

于是从小到大排序 $a$，我们现在让 $x=a_k$ 这样只要把 $a_1 \sim a_{k-1}$ 分成全 $1$。

长度为 $l$ 的段，分成 $1$ 要 $l-1$ 次。把 $k$ 个段合并要 $k-1$ 次。

于是我们用 $[\sum_{i=1}^{k-1} (a_i -1)] +(\sum_{i=1}^{k-1} a_i)$ 即可得到答案（建议自己化简一下）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,k,a[100001],ans;
signed main(){
    for(cin>>T;T;--T){
        cin>>n>>k;
        for(int i=1;i<=k;i++)
            cin>>a[i];
        ans=0;
        sort(a+1,a+k+1);
        for(int i=1;i<k;i++)
            ans+=a[i]+a[i]-1;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

因为合并只能将一段与长为 $1$ 的合并，所以我们需要把 $n-1$ 段分成长为 $1$ 的段在合并到没切的段。为了让操作数尽小，所以切的段就要尽小。所以最长的段不切，其余的切。

AC 代码：
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int t,n,k,a[200005];
int main(){//'_' T_T ^_^
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&k,&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=1;i<n;i++) ans+=(a[i]-1)+a[i];
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

显而易见的一个贪心策略是：把非最大值的数不断分解到 $1$，然后让最大值与这些 $1$ 合并即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
void solve (){
	int n , k ;
	int arr[200100] ;
	cin >> n >> k;
	int maxn = 0 ;
	for ( int i = 1 ; i <= k ; i++ ){
		cin >> arr[i] ;
		maxn = max ( arr[i] , maxn ) ;
	}
	int ans = 0 ;
	bool ok = 0 ;
	for ( int i = 1 ; i <= k ; i++ ){
		if ( arr[i] == maxn && (!ok)){
			ok = 1 ;
			continue ;
		}
		if ( arr[i] == 1 ) ans++ ;
		else {
			ans += ( arr[i] - 1 ) ;
			ans += arr[i] ;
		}
	}
	cout << ans << '\n' ;
	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF1992B](https://www.luogu.com.cn/problem/CF1992B) || [CodeForces 1992 B](https://codeforces.com/contest/1992/problem/B)

### 简要题意

有一个长度为 $k$ 的序列 $a1,a2,\dots,a_k$，且 $\sum_{i=1}^ka_i=n$，并进行以下两种操作：

* 如果第 $i$ 元素满足 $a_i\geq2$，那么可以将这个元素分为 $1$ 与 $a_i-1$，新元素位于旧元素之后。
* 将 $a_i$ 和 $a_j=1$ 的两个元素合并为 $a_i+1$（$i\neq j$）。

求将序列合并至**只有一项**所需的最少操作次数。

### 思路

从样例可以看出，想要最优操作，我们需要做的只有以下几步：

1. 求出序列中的最大值 $m$。
2. 把除最大值之外的所有 $k-1$ 个元素分裂为若干个 $1$。在操作结束后，序列为（假设将最大值移至第一项） $m,\underbrace{1,1,\cdots,1}_{n-m\text{个}1}$。
3. 将所有元素合并。

综上，一共需要 $2(n-m)-(k-1)=2n-2m-k+1$ 次操作。

```cpp
#include <iostream>
using namespace std;
signed main(){
  int t;
  cin >> t;
  while(t--){
    int n,k,m=0,a;
    cin >> n >> k;
    for(int i=0;i<k;++i)
      cin >> a, m = max(m,a);
    cout << 2*n-2*m-k+1 << '\n';
  }
}

```

---

## 作者：tzzl3035 (赞：0)

# CF1992B 题解
### 题目大意
有 $t$ 组数据，每组给出 $k$ 根棒子，第 $i$ 根长度为 $a_i$，且棒子总长度为 $n$。有两种操作，一种是从一根满足 $a_i\geq1$ 的棒子上切下一根长度为 $1$ 的棒子，一种是将一根长度为 $1$ 的棒子合并到另一根棒子上。问要把所有棒子合并至少需要几次操作。
### 思路
研究样例后即可发现，正解为找出**一根最长的**棒子，将其它棒子按第一种操作拆分成若干根长度为 $1$ 的棒子后，按第二种操作合并到最长的棒子上即可。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using namespace std;
using i64 = long long;
 
void solve() {
 	// 输入
	i64 n, k;
	cin >> n >> k;
	i64 ans = 0, a[100002]={0}, omax = 0;
	for(int i = 0; i < k; i++) {
		cin >> a[i];
		omax = max(omax, a[i]); // 找最大值
	}
	ans = n - omax; // 计算合并次数
	for(int i = 0; i < k; i++) {
		// 跳过最大值
		if(a[i] == omax) {
			omax = -1;
			continue;
		}
		ans += a[i] - 1; // 计算拆分次数
	}
	cout << ans << '\n'; // 输出
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
 
	int t;
	cin >> t;
 	// 挨组处理
	while(t--) {
		solve();
	}
	
	return 0;
}
```
### [RESULT](https://codeforces.com/contest/1992/submission/270571014)

---

## 作者：Common_Wolf (赞：0)

### 题意

有个长度 $n$ 和 $k$ 个片段，问 $k$ 个片段拼接成 $n$ 的最小操作次数。 

- 操作1：合并两个片段（必须有一个片段长度为1）； 

- 操作2：分解为两个片段（分解为长度为1和长度为-1的两个片段）。

### 题解

贪心。

最长的片段作为基础片段，其他长度的片段都要经历分解+组合两种操作（除长度为1的片段外），直接计数即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
    	int n,k;
    	cin>>n>>k;
    	long long ans=0;
    	int mx=0;
    	vector<int> a(k);
    	for (int i=0;i<k;++i){
    		cin>>a[i];
    		mx=max(mx,a[i]);
    	}
    	bool ok=1;
    	for(int i=0;i<k;++i){
    		if(a[i]==mx&&ok==1) ok=0;
    		else ans+=(a[i]-1)+a[i];
    	}
    	cout<<ans<<'\n';
    }
	return 0;
}
```
### 记录

[CF1992B](https://www.luogu.com.cn/record/166047894)

---

