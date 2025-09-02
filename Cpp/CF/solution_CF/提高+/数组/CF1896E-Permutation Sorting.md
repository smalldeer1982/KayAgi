# Permutation Sorting

## 题目描述

给定一个长度为 $n$ 的排列 $a$。我们称下标 $i$ 是“好”的，如果满足 $a_i = i$。每经过一秒钟，我们将所有不是“好”的下标对应的元素整体向右轮转一位。具体来说：

- 设 $s_1, s_2, \ldots, s_k$ 是所有不是“好”的下标，按从小到大排列。即 $s_j < s_{j+1}$，且如果下标 $i$ 不是“好”的，则存在 $j$ 使得 $s_j = i$。
- 对于每个 $i$ 从 $1$ 到 $k$，同时执行 $a_{s_{(i \bmod k)+1}} := a_{s_i}$。

对于每个 $i$ 从 $1$ 到 $n$，求出下标 $i$ 第一次变为“好”的时刻。

$^\dagger$ 排列是指由 $1$ 到 $n$ 的 $n$ 个互不相同的整数组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$，但数组中有 $4$）。

## 说明/提示

在第一个测试用例中，$2$ 和 $5$ 已经在正确的位置，因此下标 $2$ 和 $5$ 在第 $0$ 秒就变为“好”。经过 $1$ 秒后，对 $s=[1, 3, 4]$ 进行循环右移，得到数组 $a=[1, 2, 3, 4, 5]$。此时下标 $1$、$3$ 和 $4$ 在第 $1$ 秒变为“好”。

在第二个测试用例中，$5$ 已经在正确的位置，因此下标 $5$ 在第 $0$ 秒变为“好”。经过 $1$ 秒后，对 $s=[1, 2, 3, 4, 6]$ 进行循环右移，得到数组 $a=[3, 2, 1, 4, 5, 6]$。此时下标 $2$、$4$ 和 $6$ 在第 $1$ 秒变为“好”。经过 $2$ 秒后，对 $s=[1, 3]$ 进行循环右移，得到数组 $a=[1, 2, 3, 4, 5, 6]$。此时下标 $1$ 和 $3$ 在第 $2$ 秒变为“好”。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
3 2 4 1 5
6
2 1 4 6 5 3```

### 输出

```
1 0 1 1 0 
2 1 2 1 0 1```

# 题解

## 作者：do_it_tomorrow (赞：6)

[更好的阅读体验](https://doittomorrow.xyz/post/cf1896e-permutation-sorting-de-ti-jie/)
# 题目描述
给定一个有 $1$ 至 $n$ 组成的排列 $a_1,a_2,\cdots ,a_n$。如果下标 $i=a_i$，则认为这个下标是好下标。现在每秒将不好的下标循环右移一位，求下标为 $1$ 至 $n$ 变为好下标的最早时刻。

# 思路
因为移动有环，所以将数组破环为链。

![](https://cdn.luogu.com.cn/upload/image_hosting/qg8aow2a.png)


接着将对应点与目标点连线。

![](https://cdn.luogu.com.cn/upload/image_hosting/idsvfdiu.png)

设 $x$ 的最终移动位置为 $s_x$，那么在 $x\to s_x$ 的过程中已经有 $y \to s_y$ 到达了位置，那么 $x$ 的移动次数就会减少 $1$，因为在 $x$ 移动到 $s_y$ 这个位置是就直接跳过了。注意，在连线的时候，不光要处理 $s_x<n$ 的连线，序列复制的部分也要处理。因此，对于 $x$ 移动到 $s_x$，就是 $x$ 到 $s_x$ 的距离减去 $x\to s_x$ 之间包含的区间的个数。

所以题目就转化成为了求解 $n$ 个区间内包含的区间数，即满足 $x<y$ 且 $s_x>s_y$ 的 $y$ 数量，也就是一个二位偏序问题。所以将 $x$ 作为下标，将 $s_x$ 作为具体值放入树状数组中进行求解。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define lowbit(x) x&-x
const int N=2e6+6;
int n,a[N],s[N],l[N],r[N],x[N],ans[N];
void updata(int x){
	for(int i=x;i<=n*2;i+=lowbit(i)) s[i]++;
}int sum(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)) ans+=s[i];
	return ans;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		l[i]=i;
		if(a[i]<i) r[i]=a[i]+n,r[i+n]=2e6;
		else r[i]=a[i],r[i+n]=a[i]+n;
	}//for(int i=2*n;i>=1;i--) cout<<r[i]<<" ";cout<<endl;
	for(int i=n*2;i>=1;i--){
		//cout<<sum(x[i])<<" ";
		//cout<<r[i]<<" "<<i<<endl;
		if(i<=n) ans[a[i]]=r[i]-l[i]-sum(r[i]);
		//cout<<sum(r[i])<<" "<<r[i]<<endl;
		updata(r[i]);
	}for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<endl;
	for(int i=1;i<=n*2;i++) a[i]=s[i]=l[i]=x[i]=ans[i]=0;
}signed main(){
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：729hao (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1896E)  
作为你谷[目前最劣解](https://www.luogu.com.cn/record/156007016)，我觉得可以写一篇题解~~突出自己是蒟蒻的事实~~。

------------
## 思路
发现题目是在环中进行移位，所以我们先破环成链。  
令数字 $a_i$ 在链中要到达的的位置为 $b_i$，则有：
$$
b_i=\begin{cases}
a_i&i\le a_i\\
a_i+n&i>a_i\\
\end{cases}
$$
以样例的第二组数据为例：
| $i=$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $a_i=$ | $2$ | $1$ | $4$ | $6$ | $5$ | $3$ |
| $b_i=$ | $2$ | $7$ | $4$ | $6$ | $5$ | $9$ |


我们发现，**如果 $i$ 与 $b_i$ 中间的数对 $a_i$ 没有影响**，则 $a_i$ 需要移位 $b_i-i$ 次才能变“好”……吗？

观察上表，可以发现没有 $b_i=8$ 的数 $i$，相当于 $b_i=8$ 
的位置为空，那么它之前的数移位时就不应该移到 $b_i=8$ 的位置上来。（因为这个位置本来没有数，而每个数移位只会到移位前有数的位置）

所以，我们可以稍稍改变对 $b$ 数组的定义，在原定义的基础上，增加一条：如果有 $i>n$ 时 $b_i$ 的值为空，则其之后所有 $j>i$ 的 $b_j$都前移一位。（简单讲就是把 $i>n$ 时所有空的 $b_i$ 去掉，保留有值的 $b_i$）  
> 这个时候就有人要问了：  
> 为什么有限制 $i>n$？  
> 因为根据 $b$ 的定义，如果把 $i\le n$ 时的空 $b_i$ 也去掉，则可能出现 $b_i<i$ 的情况，导致最后的答案为负数。

此时，则有：
| $i=$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $a_i=$ | $2$ | $1$ | $4$ | $6$ | $5$ | $3$ |
| $b_i=$ | $2$ | $7$ | $4$ | $6$ | $5$ | $\color{red}8$ |

------------

以上的思路都是在“如果 $i$ 与 $b_i$ 中间的数对 $a_i$ 没有影响”的情况下考虑的，所以现在考虑 $i$ 与 $b_i$ 中间的数对 $a_i$ 的影响。  
可以发现，能对 $a_i$ 造成影响的数 $a_j$ 满足两个条件：
1. $a_j$ 的原位置在 $a_i$ 的原位置后面，$a_i$ 的要到达的位置的前面。（即 $i<j<b_i$）
2. $a_j$ 要到达的位置在 $a_i$ 的要到达的位置的前面。（即 $b_j<b_i$）

> 为什么是满足这两个条件？  
> 因为如果同时满足这两个条件，则 $a_j$ 一定比 $a_i$ 先变“好”。而当 $a_i$ 移位至 $b_j-1$ 时，下次移位一定会到 $b_j+1$，使 $a_i$ 减少一次移位就可以到达 $b_i$。

所以，$a_i$ 所需的移位次数 $=b_i-i-$ 满足上述条件的 $j$ 的个数。  
而这个“个数”，就是所有 $i+1\le j\le b_i-1$ 的 $j$ 中，$b_j<b_i$ 的个数。  
于是，原问题就转化为“求区间中比 $x$ 小的数的个数”。
## 线段树
线段树肯定不能维护区间桶，时空都要炸，所以干脆直接维护区间的升序排列，如果进行询问时扫到这一区间，则二分搜索找 $x$ 在区间中的前缀。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000000;
int T,n,a[N+5],b[N+5],flag[2*N+5],ans[N+5];
struct tree{
	int l,r;
	vector<int>v;//这一区间的数 
	bool f;//此区间是否排序 
}Tree[4*N+5];
int erfind(int l,int r,int id,int x){//二分求前缀 
	int mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(Tree[id].v[mid]==x)return mid;
		if(Tree[id].v[mid]<x)l=mid+1;
		else r=mid-1;
	}
	return l;
}
void Pushup(int id){
	for(int i=0;i<Tree[id*2].v.size();i++){
		Tree[id].v.push_back(Tree[id*2].v[i]);
	}
	for(int i=0;i<Tree[id*2+1].v.size();i++){
		Tree[id].v.push_back(Tree[id*2+1].v[i]);
	}
}
void Build(int id,int L,int R){
	Tree[id].l=L;
	Tree[id].r=R;
	Tree[id].v.clear();
	Tree[id].f=0;
	if(L==R){
		Tree[id].v.push_back(b[L]);
		Tree[id].f=1;
		return;
	}
	int mid=(L+R)>>1;
	Build(id*2,L,mid);
	Build(id*2+1,mid+1,R);
	Pushup(id);
}
int Ask(int id,int L,int R,int d){
	if(Tree[id].l>R||Tree[id].r<L)return 0;
	if(Tree[id].l>=L&Tree[id].r<=R){
		if(!Tree[id].f){//如果此区间没有排序，则先排序 
			Tree[id].f=1;
			sort(Tree[id].v.begin(),Tree[id].v.end());
		}
		return erfind(0,Tree[id].v.size()-1,id,d);
	}
	return Ask(id*2,L,R,d)+Ask(id*2+1,L,R,d);
}
int main(){
	scanf("%d",&T);
	int t;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++){
			flag[i]=0;
		}
		for(int i=1;i<=n;i++){//处理b数组 
			scanf("%d",&a[i]);
			b[i]=a[i];
			if(b[i]<i)b[i]+=n;
			flag[b[i]]=i;
		}
		t=0;
		for(int i=n+1;i<=2*n;i++){
			if(!flag[i]){
				t++;
				continue;
			}
			b[flag[i]]-=t;
		}
//		for(int i=1;i<=n;i++){
//			printf("%d ",b[i]);
//		}
//		printf("\n");
		Build(1,1,n);
		for(int i=1;i<=n;i++){
			if(b[i]==i){//如果已经在终点，则无需移位 
				ans[a[i]]=0;
				continue;
			}
			if(b[i]==i+1){//如果下一个位置为终点，则一定会且只会移位1次 
				ans[a[i]]=1;
				continue;
			}
			ans[a[i]]=b[i]-i-Ask(1,i+1,b[i]-1,b[i]);
		}
		for(int i=1;i<=n;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
/*
input:
2
7
1 2 3 4 5 6 7
7
4 1 5 7 2 6 3
output:
0 0 0 0 0 0 0
3 3 3 3 2 0 2
*/
```
时间复杂度 $O(nlog^2n)$，空间复杂度 $O(nlogn)$，满足题目要求。

---

## 作者：Register_int (赞：6)

先来考虑如果数没被固定咋做。答案为当前点到目标位置的距离，即：

$$
f_i=
\begin{cases}
a_i-i&i\le a_i\\
n-i+a_i&i>a_i
\end{cases}
$$

再来计算实际的答案。实际答案显然会小于等于 $f_i$，原因是循环的路上已经有数被固定了，也就是被直接跳过的。先设这个数组是循环的，由于没有固定的数之间的相对位置不变，所以 $a_i$ 能跳过的数必须满足：

- 初始位置在 $i$ 后面，在 $a_i$ 前面。
- 终点在 $i$ 后面，在 $a_i$ 前面。

也就是说，这个数 $a_j$ 必须满足 $i<j<i+f_i$ 与 $i<j+f_j<i+f_i$。这是一个二维数点问题，可以直接树状数组解决。时间复杂度为 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e6 + 10;

int c[MAXN], n;

inline void add(int k) { for (int i = k; i <= 2 * n; i += i & -i) c[i]++; }
inline int ask(int k) { int res = 0; for (int i = k; i; i &= i - 1) res += c[i]; return res; }

int t, a[MAXN], r[MAXN], ans[MAXN];

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= 2 * n; i++) c[i] = r[i] = 0;
		for (int i = 1; i <= n; i++) {
			if (i <= a[i]) r[i] = a[i], r[n + i] = n + a[i];
			else r[i] = n + a[i];
		}
		for (int i = 2 * n; i; i--) {
			if (!r[i]) continue;
			if (i <= n) ans[a[i]] = r[i] - i + ask(i - 1) - ask(r[i]); add(r[i]);
		}
		for (int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
	}
}
```

---

## 作者：MaxBlazeResFire (赞：5)

来个代码不到 $\rm 1k$ 的。

记 $pos_i$ 表示 $i$ 出现的位置，以样例举例。首先倍长数列成 $\{2,1,4,6,5,3,2,1,4,6,5,3\}$，然后考虑两种本质不同的移动目标：

* $pos_i\leq i$，我们建出两个区间 $[pos_i,i],[pos_i+n,i+n]$。容易发现它们是本质相同的。

* $pos_i>i$，建出区间 $[pos_i,i+n]$。

我们发现，循环右移就是在这个数列上每个不满足要求的数向右走。**并且对于两个还没有达到目标位置的数，它们在移动过程中相对位置是不变的**。而一个数能减少其走的步数当且仅当它移动的过程中，到达终点之前有其它在它路线上的点到达了终点。说人话就是，**一个数能减少的步数就是它的区间所完整包含其它数的区间个数**。

举个例子，数 $1$ 的区间为 $[2,7]$，被它完整包含的区间有数 $4$ 的区间 $[3,4]$，数 $5$ 的区间 $[5,5]$，数 $6$ 的区间 $[4,6]$，用 $2$ 到 $7$ 的距离 $5$ 减去 $3$ 就是答案。

用树状数组维护，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 2000005

int n,a[MAXN],pos[MAXN],tr[MAXN + 5],Ans[MAXN];

inline void add( int x , int k ){ for( ; x <= 2 * n ; x += x & -x ) tr[x] += k; }
inline int sum( int x ){ int ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }

inline void solve(){
	scanf("%lld",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]),pos[a[i]] = i;
	for( int r = 1 ; r <= n ; r ++ ) if( pos[r] <= r ) add( pos[r] , 1 );
	for( int r = 1 ; r <= n ; r ++ ){
		int pre = pos[r] <= r ? n + pos[r] : pos[r];
		Ans[r] = n + r - pre;
		Ans[r] -= sum( n + r ) - sum( pre );
		add( pre , 1 );
	}
	for( int i = 1 ; i <= n ; i ++ ) printf("%lld ",Ans[i]); puts("");
	for( int i = 1 ; i <= 2 * n ; i ++ ) tr[i] = 0;
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：樱雪喵 (赞：3)

设 $pos_i$ 表示数 $i$ 在 $a$ 序列里的位置。

将 $pos_i$ 向 $i$ 连边，一次操作就相当于让所有边的起点移到最近的下一个不是自环的点。

考虑连向 $i$ 的边的起点 $u$ 移到 $j$ 的时候 $j$ 是不是自环，其实就是比较 $pos_i$ 和 $pos_j$ 谁离 $j$ 更近。设 $dis(x,y)$ 表示不考虑自环，$x$ 移动到 $y$ 的距离。  
那么进一步考虑总贡献，$pos_i$ 移到 $i$ 的过程中跳过的自环数就是 $dis(pos_j,j)<dis(pos_i,j)$ 的 $j$ 的个数。

左边那一半对于每个 $j$ 来说是定值，右边根据 $j$ 和 $pos_i$ 的位置关系分类讨论一下是个公差为 $1$ 的等差数列。

那么问题就是对于给定的序列 $c_i=dis(pos_i,i)$，令 $b_{l,\dots,r}=x,x+1,\dots,x+r-l+1$，求 $\sum\limits_{i=l}^r [c_i < b_i]$。把定义改为 $c_i=dis(pos_i,i)-i$，二维数点即可。

```cpp
const int N=2e6+5;
int T,n,a[N],pos[N],dis[N],ans[N];
struct node{int k,tp,id;};
vector<node> q[N];
il void add(int l,int r,int x,int id) {q[l-1].push_back({x-(l),-1,id}),q[r].push_back({x-(l),1,id});}
struct BIT
{
    int tr[N];
    il void clear() {for(int i=1;i<=n+n+1;i++) tr[i]=0;}
    il void add(int x,int k) {for(;x<=n+n+1;x+=x&(-x)) tr[x]+=k;}
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
    il int ask(int l,int r) {return query(r)-query(l-1);}
}tr;
void solve()
{
    for(int i=1;i<=n;i++)
    {
        tr.add(dis[i]-(i)+n+1,1);
        for(auto x:q[i]) ans[x.id]+=x.tp*tr.ask(x.k+n+1,n+n+1);
    }
    for(int i=0;i<=n;i++) q[i].clear();
}
int main()
{
    T=read();
    while(T--)
    {
        n=read(); tr.clear();
        for(int i=1;i<=n;i++) ans[i]=0;
        for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i;
        for(int i=1;i<=n;i++) dis[i]=(i>=pos[i])?i-pos[i]:(n+i-pos[i]);
        for(int i=1;i<=n;i++)
        {
            int x=pos[i],ans=0;
            if(pos[i]<=i) add(pos[i],i-1,0,i);
            else add(pos[i],n,0,i),add(1,i-1,n-pos[i]+1,i);
        }
        solve();
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：1)

这是一篇口胡题解。

# 题目链接

[CF1896E Permutation Sorting](https://www.luogu.com.cn/problem/CF1896E)

# 解题思路

写一个题解区没有的做法。

首先有结论，每个点最多操作 $n$ 次。

为啥呢？你发现对于一个序列 $a$，若你执行了 $n$ 次，此时最多形成一个大小为 $n$ 的置换环，此时操作 $n$ 次，每个点必定能到达他应该到达的位置，否则每个环单独考虑，次数显然更小。

那么一个经典的套路，在后缀建立 $n$ 个点，前缀建立 $n$ 个虚点，那么此时每次操作等价于将最右边的不满足要求的点往左移动至最右侧没有数字的虚点，注意及时删去满足要求的点，此时线段树维护即可。

时间复杂度 $O(n \log n)$。

---

## 作者：eastcloud (赞：1)

如果所有数都不会停止移动，那么每个数第一次走到与自己相同的下标所消耗的时间是容易求出的，我们考虑加上这个条件之后会对答案造成什么影响。

我们先断环为链，观察一个数 $a$ 的移动过程，可以发现如果存在一个数 $b$ 及其目标点都在 $a$ 的移动路径上，那么 $b$ 一定会先到自己的对应点，从而使 $a$ 的答案减一，因此我们直接二维数点求出 $b$ 的个数即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 2000005
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x/10)write(x/10);
	putchar(x%10+'0');
}
struct inter{
	int l,r;
	inter(int l,int r):l(l),r(r){}
};
bool cmp(inter x,inter y){
	return x.l>y.l;
}
struct BIT{
	int K[N];
	int lowbit(int x){return x&(-x);}
	void add(int x,int val){while(x<N){K[x]+=val;x+=lowbit(x);}}
	int ask(int x){int ans=0;while(x){ans+=K[x];x-=lowbit(x);}return ans;}
}T;
int a[N],ans[N];
vector<inter> Q;
void solve(){
	int n=read();Q.clear();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<i)Q.push_back(inter(i,a[i]+n));
		else Q.push_back(inter(i,a[i])),Q.push_back(inter(i+n,a[i]+n));
	}
	sort(Q.begin(),Q.end(),cmp);
	for(auto q:Q){
		int l=q.l,r=q.r;
		if(l<=n)ans[a[l]]=r-l+T.ask(r)-T.ask(l-1);
		T.add(r,-1);
	}
	for(int i=1;i<=n;i++)write(ans[i]),putchar(' ');
	putchar('\n');
	for(auto q:Q)T.add(q.r,1);
}
int main(){
	int t=read();while(t--)solve();
}
```


---

## 作者：meyi (赞：1)

题意：给定一个序列 $a$，若 $a_i=i$ 则认为 $i$ 这个位置是好的，每次操作将所有不好的位置之间向右循环移一位，对每个位置 $i$ 问至少操作几次才能让 $i$ 变为好的。

先考虑 $i<a_i$ 的情况，若是直接移显然需要 $a_i-i$ 次，不妨令 $b_{a_i}=i,d_{a_i}=a_i-i$，考虑 $i$ 会跳过哪些点 $j$，显然有 $j\in (i,a_i)$，其次 $j$ 一定在 $i$ 移动到 $j$ 前就已经是好的了，否则 $i$ 不会跳过 $j$，因此有 $j-i>d_j$，不考虑 $(i,j)$ 之间是否会跳过其他点的原因是：若 $b_j<i$，则 $b_j$ 也会跳过这个点，若 $b_j>i$，则 $d_j=j-b_j<j-i$。因此只需求出 $(i,a_i)$ 内有多少 $j$ 满足 $j-d_j>i$，这是一个典型的二维数点，可以扫描线解决。

对于 $i>a_i$ 的情况，将 $(i,n]$ 与 $i<a_i$ 相同处理，而 $[1,a_i)$ 其实也只是将式子改写为 $n-i+j>d_j$，也即 $j-d_j>i-n$，注意这里 $i-n\le 0$，若使用树状数组则需要对下标进行处理。

给出一个时间复杂度 $O(n\log n)$ 的实现供参考，注意它是 0-indexed 的：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(),v.end()
#define For(i,_) for(int i=0,i##end=_;i<i##end;++i) // [0,_)
#define FOR(i,_,__) for(int i=_,i##end=__;i<i##end;++i) // [_,__)
#define Rep(i,_) for(int i=(_)-1;i>=0;--i) // [0,_)
#define REP(i,_,__) for(int i=(__)-1,i##end=_;i>=i##end;--i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
#define fi first
#define se second
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},inf=0x3f3f3f3f,mod=1e9+7;
const ll infl=0x3f3f3f3f3f3f3f3fll;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int init=[](){return cin.tie(nullptr)->sync_with_stdio(false),0;}();
/*
i<a[i]
i<j<a[i] d[j]<j-i
query at i and a[i]-1 for j-d[j]>i

i>a[i]
i<j<n d[j]<j-i
query at i and n-1 for j-d[j]>i
0<=j<a[i] d[j]<n-i+j
query at a[i]-1 for j-d[j]>i-n
*/
int main(){
	int t_case=1;
	scanf("%d",&t_case);
	while(t_case--){
		int n;
		scanf("%d",&n);
		V<int>a(n),b(n),ans(n);
		V<V<array<int,2>>>evt(n);
		For(i,n){
			scanf("%d",&a[i]),--a[i];
			if(i<a[i]){
				ans[a[i]]=b[a[i]]=a[i]-i;
				if(i+1<a[i]){
					evt[i].pb({i,-1});
					evt[a[i]-1].pb({i,1});
				}
			}
			if(i>a[i]){
				ans[a[i]]=b[a[i]]=n-i+a[i];
				if(i+1<n){
					evt[i].pb({i,-1});
					evt[n-1].pb({i,1});
				}
				if(a[i]){
					evt[a[i]-1].pb({i-n,1});
				}
			}
		}
		V<int>c(n<<1|1);
		For(i,n){
			for(int j=(i-b[i]+1)+n;j;j&=j-1)++c[j];
			for(const auto &j:evt[i]){
				int sum=0;
				for(int k=(j[0]+1)+1+n;k<c.size();k+=k&-k)sum+=c[k];
				ans[a[j[0]+(j[0]<0?n:0)]]-=j[1]*sum;
			}
		}
		For(i,n)printf("%d%c",ans[i]," \n"[i+1==n]);
	}
	return 0;
}

```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给你一个长度为 $n$ 的排列 $a$。每一个时刻会将所有没有归位（即 $i\neq a_i$）的位置循环向右移一位。求每个数字归位的时刻。

$T$ 组数据。

$1\leq \sum n\leq 10^6$。

## 思路

也许是今年最后一次写题解了。

首先看到循环移位，套路地破环成链。

刚拿到题目没有思路，我们可以使用第二组样例画一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/c7zhlhb0.png)

- 黑色数字表示编号。
- 红色数字表示原排列。
- 黄色竖线为复制的两份排列的分界线。
- 蓝色线段表示至少一端在左侧的线段。
- 绿色线段表示两端均在右端的线段。

这里线段指的是一个数归位所经过的线段。

然后我们观察并且手模每一个数归位的过程，可以发现如果 $i$ 的归位线段包含在 $j$ 的归位线段中，则 $j$ 归位的时候一定会跳过 $i$。这个条件是充要的，也就是必须满足这个条件才会跳过。

先证明充分性。如果 $i$ 包含在 $j$ 中，则 $i$ 归位所需要的时刻一定比 $j$ 小（等价于线段长度的大小比较），这是显然的。所以 $i$ 归位的时候，$j$ 此时一定在 $i$ 前面，所以 $j$ 一定会跳过 $i$。

再证明必要性。考虑反证法，首先如果这两段线段无交，显然不会有跳过的关系。如果线段有交但不包含，假设 $i$ 的线段为 $[l_i,r_i]$，$j$ 的线段为 $[l_j,r_j]$，且 $l_i\leq l_j\leq r_i \leq r_j$。首先 $i$ 一定不会跳过 $j$ 因为 $i$ 移动的时候一定在 $j$ 的后面，同理 $j$ 也不会跳过 $i$。由于逆否命题与原命题等价，所以必要性就证明了。

于是我们有结论：一个点的答案，等于对应线段的起终点的距离，减去被它包含的线段数量。

显然对于包含线段问题，这个是二维偏序。由于我突然发现自己降智不会写二维偏序了，所以还是记一下：如果 $[l_i,r_i]$ 包含在 $[l_j,r_j]$ 中，则 $l_j\leq l_i\leq r_i\leq r_j$。拆成 $l_j\leq l_i,r_j\geq r_i$，一维排序一维树状数组。由于这道题 $n$ 个线段的左端点恰好为 $1\sim i$，所以写起来比较简便，不需要排序。

注意一定要记得处理图中的绿色线段，这一部分也是要数进去的。我处理的方法是我们先将右边处理一遍，然后如果线段涉及到了右边的排列，则需要额外减去这一部分的贡献。

处理贡献的代码大概长这样：

```cpp
update(r[i], 1);
ans[a[i]] = r[i] - i - query(r[i] - 1) - \
	(a[i] >= i ? 0 : query(a[i] - 1))
```

时间复杂度 $O(n\log n)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x)&-(x))
using namespace std;

const int N = 2e6+5;
int n,t[N],a[N];

void update(int p, int v){
    while(p <= (n << 1)) t[p] += v, p += lowbit(p);
}

int query(int p){
    int ans = 0;
    while(p) ans += t[p], p -= lowbit(p);
    return ans;
}

int r[N], ans[N];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) r[i] = a[i] >= i ? a[i] : a[i] + n;
    for(int i=n;i;i--){
        if(r[i] <= n) update(r[i] + n, 1);
    }
    for(int i=n;i;i--) update(r[i], 1), ans[a[i]] = r[i] - i - query(r[i] - 1) - (a[i] >= i ? 0 : query(a[i] - 1));
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}

void clear(){
    for(int i=1;i<=(n<<1);i++) ans[i] = t[i] = r[i] = 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--) solve(), clear();
    return 0;
}
```

---

## 作者：BINYU (赞：1)

## 题意

给一个 $n$ 阶全排列 $a$，每次把不满足 $a_i = i$ 的 $a_i$ 向右循环移位一位，问从移位多少次后起所有 $i \in [1,n]$ 都满足 $a_i = i$。

## 思路

先断环成链后再复制一次，可以发现此时的移位等价于向右移位。发现一条性质：若 $i < j$，则在 $a_j$ 停止移位时，$a_i$ 一定在 $a_j$ 后面，反证法易证。而在 $a_j$ 停下后，若 $a_i > j$，显然 $a_i$ 移动时会跨过 $j$，让答案减一。所以如果把每一个数的起点和终点看做一段区间，则该数的答案为区间长度减去包含的区间个数。

在具体实现时，我们可以从 $2n$ 向 $1$ 枚举左端点，如果该区间右端点大于 $2n$ 直接跳过，则一个区间 $i$ 会受到**已经遍历过**的区间 $j$ 的影响当且仅当 $r_i < r_j$（$r$ 为区间右端点），使用线段树、树状数组、set 等实现即可。

---

## 作者：DE_aemmprty (赞：1)

这里说一下官方解法。

因为一次操作本质上相当于一个环上的所有点向右移一位，所以考虑破环成链，将 $a$ 数组复制一遍到后面。

设 $h_i$ 表示下标为 $i$ 的元素的目标位置，这里要保证 $h_i \ge i$（比如当 $n=4$ 时，$a_1=4,h_1=4$；$a_3=2,h_3=5$）。

考虑如何用 $h_i$ 算出答案。假设我们要计算 $i$ 的答案，容易发现，在数组不断位移的过程中，有一些满足 $i < j < h_i$ 和 $i < a_j < h_i$ 的下标 $j$ 会提前成为一个好下标，使得 $i$ 位移次数减少 $1$。所以 $i$ 真正的答案应该是 $h_i - \sum_{1\leq j \leq 2 \times n}[i<j<h_i \ \text{并且} \ i < a_j < h_i]$。于是这个问题就变成了一个二维数点。

具体实现有一个比较简单的方法。先按照 $h_i$ 从小到大排序，然后从小到大遍历 $i$，这样可以保证前面的所有 $h_j < h_i$。又由于 $h_j \ge a_j$，所以当 $i < a_j < h_i$ 满足时，$i < h_j < h_i$ 也一定满足。然后就是一个很板的树状数组了。

核心代码如下，**注意要开两倍空间**：

```cpp
void solve() {
    n = read();
    for (int i = 1; i <= n; i ++) {
        a[i] = read();
        tar[i] = (i <= a[i] ? a[i] : a[i] + n);
    }
    for (int i = n + 1; i <= 2 * n; i ++)
        tar[i] = tar[i - n] + n;
    BIT::init(n);
    int tot = 0;
    for (int i = 1; i <= 2 * n; i ++)
        seg[++ tot] = {tar[i], i};
    sort(seg + 1, seg + tot + 1);
    for (int i = 1; i <= tot; i ++) {
        if (seg[i].second <= n) {
            ans[a[seg[i].second]] = seg[i].first - seg[i].second 
                        - BIT::getsum(seg[i].second, seg[i].first);
        }
        BIT::update(seg[i].second, 1);
    }
    for (int i = 1; i <= n; i ++)
        printf("%d ", ans[i]);
    printf("\n");
}
```

---

## 作者：Mashu77 (赞：0)

一道比较容易看出来的诈骗题。

对于这种循环移位的情况，我们的直觉就是破环为链。显然，破环为链之后每个数的起始点和终点形成了一个个区间，考虑观察这些区间的关系。

例如第二个样例可以画成如下的图：

可以发现，到达的次序是有“优先级”的，首先是步数最少的，然后是步数第二少的……这就形成了区间的包含关系（步数大的肯定包含步数小的），所以我们考虑从计算区间走完的个数来统计答案。

由于肯定是小的区间先走完，所以当一个区间走完的时候，被它包含的区间一定都走完了，所以就会造成若干次“加速”，也就是说如果在走这个区间的任意时刻，这个区间的子区间同时走完了，那么就会使得那个子区间的左端点满足要求了，当走到左端点时，就会自动跳过，也就是会减少一次的跳跃，跳跃的次数显然就是包含其他区间的个数。

所以每一个区间要跳完的步数就可以计算了，设 $s_l,s_r$
  表示左端点和右端点，$c n t $ 表示包含的区间数量，那么步数就是 $s_r-s_l-cnt$，显然区间左端点的答案就是区间的步数。

---

## 作者：wusixuan (赞：0)

一道比较容易看出来的诈骗题。

对于这种循环移位的情况，我们的直觉就是破环为链。显然，破环为链之后每个数的起始点和终点形成了一个个区间，考虑观察这些区间的关系。

例如第二个样例可以画成如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tzoi53fp.png)

可以发现，到达的次序是有“优先级”的，首先是步数最少的，然后是步数第二少的……这就形成了区间的包含关系（步数大的肯定包含步数小的），所以我们考虑从计算区间走完的个数来统计答案。

由于肯定是小的区间先走完，所以当一个区间走完的时候，被它包含的区间一定都走完了，所以就会造成若干次“加速”，也就是说如果在走这个区间的任意时刻，这个区间的子区间同时走完了，那么就会使得那个子区间的左端点满足要求了，当走到左端点时，就会自动跳过，也就是会减少一次的跳跃，跳跃的次数显然就是包含其他区间的个数。

所以每一个区间要跳完的步数就可以计算了，设 $s_l,s_r$ 表示左端点和右端点，$cnt$ 表示包含的区间数量，那么步数就是 $s_r-s_l-cnt$，显然区间左端点的答案就是区间的步数。

---

## 作者：Maverik (赞：0)

##### Statement

给定一个长度为 $n$ 的排列 $a$。我们称一个下标 $i$ 是“好”的当且仅当 $a_i=i$。每一秒，我们把所有**不**“好”的下标上的数向右循环移位。对于每个 $i\in[1,n]$，输出第一次 $i$ 变“好”的时间。$1\le \sum n\le 10^6$。

##### Solution

水个题解。对于每个数 $x$ ，考虑 $a_x=x$ 前 $a_x$ 出现多少数。不考虑循环的移位，假设 $x<a_x$，等效于 $i\in [x,a_x]$，满足 $a_i>a_x$ 的 $i$ 个数，简单扫描线就好了。循环移位的话就把排列复制一份接到后面一样做就行。复杂度 $O(n\log n)$。

```cpp 
struct fenwick
{
	int c[maxn];
	inline int lowbit(int x){return x&(-x);}
	inline void add(int x,int y){for(;x<=2*n;x+=lowbit(x))c[x]+=y;}
	inline int query(int x){int res=0;for(;x;x-=lowbit(x))res+=c[x];return res;}
	inline int qsum(int l,int r){return query(r)-query(l-1);}
}tr;
inline void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=i,a[i+n]=a[i],b[i+n]=b[i]+n;
	for(int i=1;i<=n;i++)
		if(b[i]<i) vis[i]=1,b[i+n]=b[i]+n;
		else if(b[i]>i) vis[i+n]=1,b[i+n]=b[i],tr.add(b[i]+n,1);
	for(int i=2*n;i>=1;i--)
	{ if(vis[i]) ans[(i-1)%n+1]=tr.qsum(b[i],i); tr.add(b[i],1); }
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<'\n';
	for(int i=1;i<=2*n;i++) vis[i]=ans[i]=tr.c[i]=0;
}
```



---

