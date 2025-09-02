# Sakurako, Kosuke, and the Permutation

## 题目描述

Sakurako's exams are over, and she did excellently. As a reward, she received a permutation $ p $ . Kosuke was not entirely satisfied because he failed one exam and did not receive a gift. He decided to sneak into her room (thanks to the code for her lock) and spoil the permutation so that it becomes simple.

A permutation $ p $ is considered simple if for every $ i $ $ (1\le i \le n) $ one of the following conditions holds:

- $ p_i=i $
- $ p_{p_i}=i $

For example, the permutations $ [1, 2, 3, 4] $ , $ [5, 2, 4, 3, 1] $ , and $ [2, 1] $ are simple, while $ [2, 3, 1] $ and $ [5, 2, 1, 4, 3] $ are not.

In one operation, Kosuke can choose indices $ i,j $ $ (1\le i,j\le n) $ and swap the elements $ p_i $ and $ p_j $ .

Sakurako is about to return home. Your task is to calculate the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 说明/提示

In the first and second examples, the permutations are already simple.

In the fourth example, it is sufficient to swap $ p_2 $ and $ p_4 $ . Thus, the permutation will become $ [2, 1, 4, 3] $ in $ 1 $ operation.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
5
5 4 3 2 1
5
2 3 4 5 1
4
2 3 4 1
3
1 3 2
7
2 3 1 5 6 7 4```

### 输出

```
0
0
2
1
0
2```

# 题解

## 作者：zhouruoheng (赞：4)

## E

置换环问题，将 $i$ 和 $p_i$ 连边，那么最后肯定会出现小于等于 $n$ 个环，例如 `2 3 1 5 6 7 4 8 9`：

![](https://cdn.luogu.com.cn/upload/image_hosting/47thhpzr.png)

这样的话，就是要求每个环的个数小于等于 $2$。考虑最优交换策略。  
如上图四个节点的环这个环，交换环上任一节点的左右节点，比如交换 $6$ 左右的两个 $p_5$ 和 $p_7$，$5$ 是指向 $6$ 的，交换就能使 $7$ 指向 $6$，而原本 $6$ 是指向 $7$ 的，$5$ 指向 $7$ 指向的 $4$，就将 $6$ 和 $7$ 独立出去了，接下来继续看环剩下的，直到大小不超过 $2$。

也就是说每次操作都能保证消掉两个，那么对于一个环 $x$ 来说，需要操作的次数即为 $(size_x-1)/2$。

用并查集统计环的大小。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=1e6+5;

int n;
int a[N];
int fa[N],siz[N];
bool v[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    x=find(x),y=find(y);
    if(x!=y) siz[x]+=siz[y],fa[y]=x;
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,v[i]=0;
    for(int i=1;i<=n;i++) merge(i,a[i]);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x=find(i);
        if(!v[x]) ans+=(siz[x]-1)/2;
        v[x]=1;
    }
    cout<<ans<<'\n';
}
int main ()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}

```

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF2033E Sakurako, Kosuke, and the Permutation](https://www.luogu.com.cn/problem/CF2033E)

## 题意简述

我们将 $p_i=i$ 称为长度为 $1$ 的环，将 $p_{p_i}=i$ 称为长度为 $2$ 的环，将 $p_{p_{p_i}}=i$ 称为长度为 $3$ 的环，以此类推。

题目的目标是通过最少的交换次数，使所有环的长度不超过 $2$。

## 解题思路

如果交换两个不同环中的元素，会将它们合并为更大的环。因此，只有在每个环的内部进行交换，才能减少环的长度。

对于长度为 $k$ 的环，单次操作可以交换环内的两个元素。因此，至少需要 $\frac{k-1}{2}$ 次交换操作来使得该环的长度不超过 $2$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=1000005;
int a[N];
bool vis[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			vis[i]=0;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(vis[i])continue;
			int now=i,cnt=0;
			while(!vis[now])
			{
				vis[now]=1;
				now=a[now];
				cnt++;
			}
			ans+=cnt-1>>1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：2)

## 题意

给定长度为 $n$ 的排列 $p$，每次可以选择 $i,j$，交换 $p_i,p_j$，使得对于所有的 $i$，都满足 $p_i=i$ 或 $p_{p_i}=i$。

## 思路

手玩一下样例，发现 $p_{p_i}=i$ 这种情况总是成对出现。对于不满足的某个 $i$，交换 $p_{p_i}$ 和 $i$ 这两个数就可以满足。如何快速得到 $i$ 的下标呢？可以对 $p$ 建反向数组，即 $b_i$ 记 $i$ 在 $p$ 中的下标，这样可以用 $\mathcal{O(1)}$ 得到。维护两个数组即可。注意维护过程中可能会出现两个数组不能同时改，需要提前记某些值。复杂度 $\mathcal{O(n)}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c,d) for(int a=b;a<=c;a+=d)
#define R(a,b,c,d) for(int a=b;a>=c;a-=d)

using namespace std;
const int N=1e6+5,M=998244353;

void solve();
int T,n,a[N],b[N],ans;

signed main(){
  scanf("%d",&T);
  while(T--) solve();
  return 0;
}

void solve(){
  scanf("%d",&n);
  L(i,1,n,1){
    scanf("%d",a+i);
    b[a[i]]=i;
  }
  ans=0;
  L(i,1,n,1){
    if(a[i]==i) continue;
    else{
      if(a[a[i]]==i) continue;
      else{
        int x=a[i],z=a[a[i]];
        swap(a[a[i]],a[b[i]]);
        int y=b[i];
        b[i]=x;
        b[z]=y;
        ans++;
      }
    }
  }
  printf("%d\n",ans);
}
```

---

## 作者：ZhaoV1 (赞：1)

要使得所有元素满足：
- $p_i=i$
- $p_{p_i}=i$

我们可以举以下一个例子来探索规律：
![](https://cdn.luogu.com.cn/upload/image_hosting/lty52msh.png)
让我们关注条件 $p_i=i$，将每个数指向它应该在的位置，画出以下线索：
![](https://cdn.luogu.com.cn/upload/image_hosting/uo2sj5nf.png)
显然，这些数字形成某些独立的循环，此时我们关注第二个条件 $p_{p_i}=i$，如果存在以下形式，则该数列满足排列形式。
![](https://cdn.luogu.com.cn/upload/image_hosting/v027wsxp.png)
所以目标已经非常明确了——只需要尽可能少的调换次数，使得不合要求的数字彼此指向对方，即在独立循环中打破循环，从而使得数字互指，比如：
![](https://cdn.luogu.com.cn/upload/image_hosting/170voxa7.png)
（仅为方案的一种）显然，调换次数是 $\lfloor\frac{\lambda-1}{2}\rfloor$（其中 $\lambda$ 为某个独立循环中元素的个数）。

AC Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5;
int t,n,m;
int a[N];
bool b[N];

void solve(){
	int res = 0;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		b[i] = false;//init
	}
	for(int i=1;i<=n;i++){
		if(a[i] == i || a[a[i]] == i){//已经符合条件的
			b[i] = true;
			continue;
		}

		int last = a[a[i]];
		b[a[i]] = true;
		int cnt = 0;
		while(last != a[i] && !b[last]){
			b[last] = true;
			last = a[last];
			cnt++;
		}
		res += cnt/2;
	}
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

~~VP 12min 切了。~~
# 思路
显然如果把排列看成一个有向边集，并将所有 $i$ 向 $p_i$ 连边，发现这可以形成若干个环。满足条件 $p_i=i$，就是一个自环；满足 $p_{p_i}=i$，就是一个大小为 $2$ 的环。

发现每次操作可以从一个大环里面拆出一个大小为 $1$ 或 $2$ 的环（可以自己画图模拟一下），显然后者更优，于是统计不同大小的环的数量直接拆就可以了。下图展示了从一个大环中拆出一个小环的构造方案。
```
//a->b->c->d->e
//^           |
//|           |
//-------------
//swap(b,e)
//a->b  c->d->e
//^  |  ^     |
//|  |  |     |
//----  -------
```

时间复杂度 $O(\sum n)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,p[1000001],cnt[1000001],ans;
bool g[1000001];
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			cnt[i] = 0,g[i] = false;
			scanf("%d",&p[i]);
		}
		for(int i = 1;i <= n;i ++){
			if(!g[i]){//不在环中，开始找环
				g[i] = true;
				int tmp = 1,j = p[i];
				while(!g[j]){
					tmp ++,g[j] = true,j = p[j];//标记环中的点
				}
				cnt[tmp] ++;//统计对应大小的环数
			}
		}
		for(int i = n;i > 2;i --){
			cnt[i - 2] += cnt[i];//每个环都拆出 2 个点
			ans += cnt[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个长度为 $n$ 的数列，每次可以交换其中的两个，求最少的操作次数使得对于 $\forall 1\le i\le n$，有 $a_i=i$ 或 $a_{a_i}=i$。

### 2. 思路

见到这种数组元素的值与下标相联系的题第一时间想到建边。

我们考虑把 $i$ 与 $a_i$ 建边，这样一定会形成环。

题目要求的实际上就是使得所有环的大小不超过 $2$ 的最小操作次数。

显然我们不能将两个不同的环中的点交换，否则会使环变大。

因此我们考虑环内交换。

可以发现每交换一次环的大小就会减少 $2$，因此对于每一个环，我们所需的操作次数就是 $\dfrac{size_x-1}{2}$。

而找环的操作就可以使用 while 循环。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1000010],cnt,flag[1000010],ans;
signed main(){
	cin>>t;
	while(t--){
		ans=0;
		memset(flag,0,sizeof flag);
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(!flag[i]){
				cnt=0;
				int x=a[i];
				flag[i]=1;
				while(!flag[x]){
					flag[x]=1;
					x=a[x];
					cnt++;
				}
				ans=ans+cnt/2;
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}
```

---

