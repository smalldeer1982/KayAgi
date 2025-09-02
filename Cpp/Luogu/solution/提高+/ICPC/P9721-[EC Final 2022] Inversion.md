# [EC Final 2022] Inversion

## 题目描述

**这是一个交互式问题。**

有一个隐藏的排列 $p_1, p_2, \dots, p_n$，它是 $\{1, 2, \dots, n\}$ 的一个排列。你需要通过询问 $p_l,\ldots, p_r$ 的逆序数的奇偶性来找到它。

你可以以 ${?~l~r}$ 的格式进行查询，交互器将会返回 $ \left( \sum_{l\leq i < j\leq r} [p_i > p_j]\right) \bmod 2$。当 $p_i > p_j$ 时，$[p_i>p_j]$ 为 $1$，否则为 $0$。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3

0

0

1
```

### 输出

```

? 1 2

? 1 3

? 2 3

! 2 3 1```

# 题解

## 作者：itisover (赞：4)

新教练布置的题，挺有意思的。我的做法不太用预处理很多，常数挺小的，没人写过就写个题解。

首先考虑 $i-1$ 到 $i$ 的过程，本质上是要在原先确定好顺序的前 $1 \sim i-1$ 项中插入第 $i$ 项，即确定 $i$ 在前 $i-1$ 中是第几小。

很容易想到从第一小开始依次比较，但是至少 $n^2$ 问询，无法接受。于是想到可以二分找第 $k$ 小，得到了 $n \log_2 n$ 的做法。

问题来了，怎么通过题设交互方法实现任意位置 $i,j (i<j)$ 两数的大小比较？

- 两数在序列中相邻：`? i j` 返回的就是 `i>j` 是真是假。
- 两数不相邻：我有一个不一样的思路：
  >首先询问 `? i j` 和 `? i+1 j` 记结果为 $q1,q2$
  >
  >显然 $q1 $ 即为 $(q2 + \sum\limits^{j}_{k=i+1} [p_i>p_k] )\mod 2 = (q2 + \sum\limits^{j-1}_{k=i+1} [p_i>p_k] + [p_i>p_j])\mod 2$
  >
  >意思是 $i\sim j$ 的逆序对个数，等于 $i+1 \sim j$ 的逆序对个数，再加上 $i+1 \sim j$ 中比第 $i$ 项小的个数
  >
  >我们可以维护一个 `sum[i]`，表示第 $i$ 项到当前循环处理到的最后一项之间，有几个是小于第 $i$ 项的。维护就是：每加入一个数，只用把比他大的所有数的 `sum[i]` 增加 $1$ 即可。
  >
  >所以只需判断 `(q2 + sum[i]) % 2` 与 `q1` 的奇偶性是否发生了变化即可判断 $[p_i > p_j]$ 是否为真。

至此，题目迎刃而解，感觉思路还是挺自然的，不会很复杂，实现也挺简单，很小清新的题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=2005;
int n;
int sum[_],rk[_],id[_];
int main(){
    cin>>n;
    rk[1]=1;
    for(int i=2;i<=n;++i){
        int l=1,r=i-1,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            int q1,q2;
            cout<<"? "<<rk[mid]<<" "<<i<<endl;
            cin>>q1;
            if(rk[mid]==i-1){
                if(q1) r=mid-1;
                else ans=mid,l=mid+1;
            }
            else{
                cout<<"? "<<rk[mid]+1<<" "<<i<<endl;
                cin>>q2;
                if((q2+sum[rk[mid]])%2==q1) ans=mid,l=mid+1;
                else r=mid-1;
            }
        }
        for(int j=i;j>ans+1;--j) rk[j]=rk[j-1];
        rk[ans+1]=i;
        for(int j=ans+2;j<=i;++j) ++sum[rk[j]];
    }
    for(int i=1;i<=n;++i) id[rk[i]]=i;
    cout<<"! ";
    for(int i=1;i<=n;++i) cout<<id[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：Demeanor_Roy (赞：4)

- [原题链接](https://www.luogu.com.cn/problem/P9721)。

------------

看到交互题，直接根据次数限制猜做法。不难得出我们需要一个询问次数在 $n \log n$ 级别的做法。

又由于所求为原排列，亦即序列元素大小关系。不难得出一个朴素想法，从前往后考虑，实时维护当前元素大小关系，每插入一个新元素，二分出它该在的位置，插入即可。

这样做，我们需要 $\sum_{i=1}^{n}\lceil \log_2 i \rceil$ 次询问序列中两个数大小关系。现在考虑如何利用题目给出的询问，得到我们所求。

比较 $p_x,p_y(x<y)$ 的大小关系，即求 $x$ 位置与 $y$ 位置产生的逆序对数。考虑容斥，令 $f(l,r)$ 表示区间 $[l,r]$ 产生的逆序对数，则所求为：

$$f(x,y)-f(x-1,y)-f(x,y-1)+f(x+1,y-1)$$

但 $40000$ 次询问显然不支持我们如此奢侈，考虑优化。不难发现，当考虑到第 $x$ 个元素时，我们其实已经知道前 $x-1$ 个元素的大小关系，所以只要询问的右端点不为 $x$，那逆序对我们可以自己求，不用浪费询问次数。故每次比较我们只需要询问两次即可。

由于 $\sum_{i=1}^{4000}2\lceil \log_2 i \rceil \leq 40000$，故题目解决。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int n,w[N],ans[N];
bool vis[N];
map<int,int> mp[N];
vector<int> vec,now;
inline int query(int l,int r)
{
	if(mp[l][r]) return mp[l][r]-1;
	int x;
	printf("? %d %d\n",l,r);
	cout.flush();cin>>x;return (mp[l][r]=x+1)-1;
}
inline int D(int pos,int x)
{
	int val=query(pos,x);
	if(pos!=x-1)
	{
		val^=query(pos+1,x);
		val^=w[pos]^w[pos+1];
	}
	return val;
}
int main()
{
	scanf("%d",&n);
	vec.push_back(1);
	for(int i=2;i<=n;i++)		
	{		
		int l=0,r=i-1;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(D(vec[mid],i)) r=mid;
			else l=mid+1;
		}
		now.clear();
		for(int j=0;j<l;j++) now.push_back(vec[j]);
		now.push_back(i);
		for(int j=l;j<i-1;j++) now.push_back(vec[j]),vis[vec[j]]=true;
		vec.clear();
		for(auto x:now) vec.push_back(x);
		for(int j=i-1,cnt=0;j>=1;j--) cnt^=vis[j],vis[j]=false,w[j]^=cnt; 
	}
	for(int i=0;i<n;i++) ans[vec[i]]=i+1;
	printf("!");
	for(int i=1;i<=n;i++) printf(" %d",ans[i]);
	return 0;
}
```


---

## 作者：听取MLE声一片 (赞：4)

题目大意：交互题，有一个长度为 $n$ 的排列，每次询问可以得到一个区间的逆序对个数的奇偶性。

通过若干次询问得出一个排列，不难想到基于比较的排序。基于比较的排序首先需要比较两个数的大小。

通过判断这两个数是否组成一个逆序对，即可完成比较。

题目中给的询问是区间逆序对数，可以通过容斥来解决。位置 $l$ 和 $r$ 的数是否组成逆序对即为 $ask(l,r)\oplus ask(l+1,r)\oplus ask(l,r-1)\oplus ask(l+1,r-1)$。

但是这样每次比较都需要询问 $4$ 次，而基于比较的排序是 $O(n\log n)$，不能通过。

考虑使用二分优化的插入排序，从前到后插入每一个数，二分最早组成逆序对的位置。这样的好处是 $ask(l,r-1)$ 和 $ask(l+1,r-1)$ 可以通过前面已经排好序的结果求出，这样每次比较只需要 $2$ 次询问，可以通过此题。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2010;
int n,a[N],b[N],f[N][N];
int ask(int x,int y){
	if(x>y)return 0;
	if(x==y)return 0;
	if(f[x][y]!=-1)return f[x][y];
	cout<<"? "<<x<<' '<<y<<endl;
	fflush(stdout);
	int res=read();
	return f[x][y]=res;
}
int query(int x,int y){
	if(x+1==y)
		return ask(x,y);
	int res=ask(x,y)^ask(x+1,y)^ask(x,y-1)^ask(x+1,y-1);
	return res;
}
int main()
{
	memset(f,-1,sizeof(f));
	n=read();
	for(int i=1;i<=n;i++)
		f[i][i]=0;
	for(int i=1;i<=n;i++)
		a[i]=i;
	for(int i=2;i<=n;i++){
		int l=1,r=i-1,p=i;
		while(l<=r){
			int mid=(l+r)>>1;
			if(query(a[mid],i)){
				p=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		for(int j=i;j>p;j--)
			a[j]=a[j-1];
		a[p]=i;
		int res=0;
		for(int j=1;j<=i;j++)
		b[a[j]]=j;
		for(int j=i-1;j>=1;j--){
			if(b[j]>b[i])res^=1;
			f[j][i]=res^f[j][i-1];
		}
	//	for(int j=1;j<=i;j++)cout<<b[j]<<' ';cout<<'\n';
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)
		b[a[i]]=i;
	for(int i=1;i<=n;i++)
		cout<<b[i]<<' ';
	return 0;
}

```

---

## 作者：homo_snow (赞：0)

# OIer A的第一道交互题

只能说经验还是少了，简单题还是调了半天。

### 首先来考虑这道题的询问

题中表明：当给出 $[l,r]$ 时，会返回出原序列区间 $[l,r]$ 的逆序对的奇偶性。设这个询问结果为 $Q(l,r)$。

如果把这个区间收缩一下，就可发现 $[l,r-1]$ 与 $[l+1,r]$ 这两个区间要么少一个逆序对，要么不变。

再次收缩，变成 $[l+1,r-1]$，如果发现 $Q(l,r)$ 与 $Q(l+1,r-1)$ 的结果相同，也就知道，第 $l$ 与 $r$ 个元素存在大小关系。

这个时候再去看 $Q(l+1,r)$ 和 $Q(l,r-1)$ 的结果，如果二者结果不同，则说明 $p_l > p_r$。

反过来也是一个道理。

这样我们就得到了确认两个元素的大小关系的方法：

**$Q(l,r)\oplus Q(l+1,r)\oplus Q(l,r-1)\oplus Q(l+1,r-1) = 1$，就说明 $p_l > p_r$**。

### 具体做法

知道了元素间的大小关系，我们选择二分优化的插入排序来维护答案即可。

### 关于优化

这种方法一次就要 $4$ 个询问，太浪费次数了，考虑打表，把询问过的记录下来，避免重复询问。

同时动态维护答案序列，借助答案序列求出元素间的大小关系，也记录下来，高效减少问答次数。

然后就能愉快地水一道题啦！

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3+10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;

int n , a[N], book[N][N], ans[N];

int ask(int l,int r){
	if(l >= r) return 0;
	if(~book[l][r])return book[l][r];
 	printf("? %lld %lld\n",l,r);
	fflush(stdout);
	scanf("%lld",&book[l][r]);
	return book[l][r];
}

int cmp(int l,int r){
	int res = (ask(l,r) ^ ask(l+1,r) ^ ask(l,r-1) ^ ask(l+1,r-1));
	return res;
}

signed main(){
	scanf("%lld",&n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			book[i][j] = -1;
	for(int i = 1; i <= n; i++) book[i][i] = 0;
	a[1] = ans[1] = 1;
	for(int i = 2; i <= n; i++){
		int l = 1, r = i - 1,pos = i;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(cmp(a[mid],i)) r = mid - 1, pos = mid;
			else l = mid + 1;
		}
		for(int j = i; j > pos; j--) a[j] = a[j-1];
		a[pos] = i;
		for(int j = 1; j <= i; j++) ans[a[j]] = j;
		for(int j = i - 1; j >= 1; j--) book[j][i] = (book[j+1][i] ^ (ans[j] > ans[i]));
		for(int j = 1; j < i; j++) book[j][i] ^= book[j][i-1];
	}
	for(int i = 1; i <= n; i++) ans[a[i]] = i;
	printf("!");
	for(int i = 1; i <= n; i++) printf(" %lld",ans[i]);
	fflush(stdout);
	return 0;
}

```

---

## 作者：cryozwq (赞：0)


首先看交互次数不难猜出这题肯定带 $\log$。

考虑如何 $n^2$ 个区间的答案如果都知道咋做，考虑 $i$ 从小到大插入，注意到 $(j,i) \oplus (j+1,i)$ 即为 $[j+1,i-1]$ 中大于 $p_i$ 的值的数量奇偶性，所以一个变量 $j$ 从 $i-1$ 扫到 $1$，如果上面那个表达式的奇偶性和 $j+1$ 对应答案不同，则说明 $p_j > p_i$，否则 $p_j<p_i$。

事实上正解就已经出来了，按照上面的方法，我们只需要四次操作就能比较任意一对 $(i,j)$ 的大小，因此我们在插入的时候改为二分，即可将询问次数降为 $4 n\log n$，无法通过。但是当成功插入了 $i$ 之后，任意的 $(j,i)$ 的答案（$j\le i$） 都已经知道了，所以事实上比较一对的大小只需要两次操作，询问次数降为 $2 n\log n$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool mr[2005][2005];
int res[2005][2005];
inline int query(int x,int y){
//	assert(x<=n);assert(x>=1);
//	assert(y<=n);assert(y>=1);
	if(x==y)return 0;
	if(mr[x][y])return res[x][y];
	mr[x][y]=1;
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>res[x][y];
	return res[x][y];
}
inline bool cmp(int i,int j){
	if(i+1==j)return !query(i,j);
	return !(query(i,j)^query(i+1,j)^query(i+1,j-1)^query(i,j-1));
}
int pos[2005],tot,tmp[2005];
int ans[2005],bl[2005];
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	pos[++tot]=1;bl[1]=1;
	for(int i=2;i<=n;i++){
		int L=1,R=tot,ans=0;
		while(L<=R){
			int mid=(L+R)/2;
			if(cmp(pos[mid],i)){
				ans=mid;
				L=mid+1;
			}
			else R=mid-1;
		}
		int tt=0;
		for(int j=ans+1;j<=tot;j++){
			tmp[++tt]=pos[j];
		}
		tot=ans;
		pos[++tot]=i;bl[i]=tot;
		for(int j=1;j<=tt;j++)pos[++tot]=tmp[j],bl[tmp[j]]=tot;
		for(int j=i-1;j>=1;j--){
			bool fl=0;
			if(bl[j]>bl[i])fl=1;
			fl=fl^res[j][i-1]^res[j+1][i-1];
			res[j][i]=res[j+1][i]^fl;
			mr[j][i]=1;
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<bl[i]<<" ";
} 
```

---

## 作者：ducati (赞：0)

简单交互题。

## Description

[传送门](https://www.luogu.com.cn/problem/P9721)

## Solution

令 $Q(l,r)$ 为 $p[l,r]$ 的逆序对数量 $\bmod \ 2$，则
$$p_l > p_r \iff Q(l,r) \oplus Q(l,r-1) \oplus Q(l+1,r) \oplus Q(l+1,r-1) = 1$$

其中 $\oplus$ 表示异或。

---

考虑遍历 $i=1,2,3,\cdots,n$，维护 $p[1,i]$ 中所有元素的相对大小关系。

当新加入 $p_{i+1}$ 时，通过二分确定 $p_{i+1}$ 在 $p[1,i]$ 中的后继，然后插入进去。

令 $A = \sum_{i=1}^{n} \log_2(i)$，询问次数最大值约为 $4A$，无法通过。

---

注意到，判断是否有 $p_l > p_r$ 时，$p[l,r-1], p[l+1,r-1]$ 是已知的，不需要额外的查询。

递推出各段区间的逆序对数，询问次数最大值约为 $2A$，时间复杂度 $O(n^2)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2005;

int n,per[N],ord[N],ivs[N][N];
int Query(int l,int r){
	if (l>=r)  return 0;
	if (~ivs[l][r])  return ivs[l][r];

	cout<<"? "<<l<<' '<<r<<endl,fflush(stdout);
	return cin>>ivs[l][r],ivs[l][r];
}
int Compare(int l,int r){
	int num=Query(l,r)^Query(l,r-1)^Query(l+1,r)^Query(l+1,r-1);
	return num;
}
int main(){
	cin>>n,memset(ivs,-1,sizeof(ivs)),ord[1]=per[1]=1;
	for (int i=1;i<=n;i++)  ivs[i][i]=0;
	for (int i=2;i<=n;i++){
		int t=i-1,l=1,r=t,res=i;
		while (l<=r){
			int mid=(l+r)>>1;
			if (Compare(ord[mid],i))  res=mid,r=mid-1;
			else l=mid+1;
		}
		for (int j=t;j>=res;j--)  ord[j+1]=ord[j];
		ord[res]=i;

		for (int j=1;j<=i;j++)  per[ord[j]]=j;
		for (int j=t;j;j--)  ivs[j][i]=(ivs[j+1][i]^(per[j]>per[i]));
		for (int j=1;j<i;j++)  ivs[j][i]^=ivs[j][i-1];
	}
	cout<<"! ";
	for (int i=1;i<=n;i++)  cout<<per[i]<<' ';
	return fflush(stdout),0;
}
```


---

## 作者：HFanGDoDM (赞：0)

# 题意简述

**这是一道交互题。**

今有一长度为 $n$ 的 **未知排列** $p$。试通过不超过 $4\times10^4$ 次对区间 $[l,r]$ 的 **逆序对个数 $\displaystyle\sum_{l\leqslant i\lt j\leqslant r}[p_i\gt p_j]\bmod2$ 的值** 的询问，还原排列 $p$。

### 数据范围

$1\leqslant n\leqslant2000$。

# 解题思路

### 做法

为便于表述，以下记 $inv_{l,r}$ 表示区间 $[l,r]$ 的 **逆序对数量**。

从左往右确定 $p_i$ 在 $\{p_1,p_2,\dots,p_i\}$ 中的 **相对排名**。对于当前未知的 $p_i$，**二分** 其相对排名。设当前二分到的相对排名为 $rk$，且该排名对应的数的位置为 $pos$，则 **向交互库询问** 区间 $[pos,i],[pos+1,i]$，并 **直接调用** 出区间 $[pos,i-1]$ 和 $[pos+1,i-1]$ 的逆序对数 $inv_{pos,i-1}\bmod2$ 和 $inv_{pos+1,i-1}\bmod2$ 的值。

设 $f(l,r)=inv_{l,r}\bmod2$，则求出 $f(pos,i)-f(pos,i-1)-f(pos+1,i)+f(pos+1,i-1)$ 在模 $2$ 意义下的值，即 **求出了 $[p_{pos}\gt p_i]$**。根据这一大小关系，二分求出 $p_i$ 的相对排名，并 **更新以 $i$ 为右端点的区间逆序对数量**，将 $p_i$ 插入集合。

确定所有 $p_i$ 的相对排名后，即还原了原排列 $p$。

### 正确性证明

对于前面已经确定好排名的所有 $p_i$ 所构成的 **升序序列** $a$，根据题意，必然有当前的数 $p_i\not\in a$，且 $\exists j\in \{1,2,\dots,i-1\},\forall k\in \{1,2,\dots,j\},a_k\lt p_i\land\forall k\in\{j+1,j+2,\dots,i-1\},a_k\gt p_i$，因此这一 **关系满足单调性**，我们可以使用二分法求出 $p_i$ 在其中的相对排名。

由于有关逆序对数的询问答案需要模 $2$，而对于加减法而言，先模 $2$ 再进行加减，最后再模 $2$，和先进行加减，最后模 $2$ 是 **等价的**。因此，我们先不考虑取模，先记 $f(l,r)$ 表示区间 $[l,r]$ 的 **逆序对数**。

根据逆序对的定义，可以得到：$f(l,r)-f(l,r-1)=\displaystyle\sum_{i=l}^{r-1}[p_i\gt p_{r}]$。这样，我们只需要再令询问左端点为 $l+1$，就可以得到 $f(l+1,r)-f(l+1,r-1)=\displaystyle\sum_{i=l+1}^{r-1}[p_i\gt p_r]$，两者相减，即为 $\displaystyle\sum_{i=l}^{r-1}[p_i\gt p_r]-\displaystyle\sum_{i=l+1}^{r-1}[p_i\gt p_r]=[p_l\gt p_r]$，该值 **只可能为 $0$ 或 $1$**，与是否模 $2$ 无关，再加上模 $2$ 的限制也可以求出这个结果。于是就可以 **在 $4$ 次询问内得到两个数 $p_l$ 和 $p_r$ 的大小关系**。

若每次求大小关系进行 $4$ 次询问，则总询问次数在 $4n\log n$ 级别，由于 $n\leqslant2000$，因此询问次数上界会达到 $8\times10^4$ 左右，不合题意。

求一个序列的逆序对数量，我们只需要知道其中每个元素的 **相对排名**，不需要知道每个元素的具体值 $\implies$ 对于当前的位置 $i$，我们可以 **直接计算** 出 $f(pos,i-1)$ 和 $f(pos+1,i-1)$。求这个值，可以在求出 $p_{i-1}$ 的排名时，扫一遍，求出在 $i-1$ 左边且 **元素值大于 $p_{i-1}$ 的数的数量**，更新一遍所有以 $i-1$ 为右端点的区间逆序对数量。这样就可以直接求出 $f(pos,i-1)$ 和 $f(pos+1,i-1)$，可以在 $2$ 次询问内求出 $p_{pos}$ 和 $p_i$ 的大小关系。**询问次数降至 $2n\log n$ 级别**，满足了题目的 $4\times10^4$ 询问次数的限制。

在扫完整个序列后，由于每次插入都能保证其位置对应元素在已知序列中的相对排名是正确的，因此所有元素的相对排名也是正确的。由于原序列为一个 **排列**，因此最终 **一定能够确定原排列每个位置的每个元素**。

因此，这一思路是正确的。

### 具体实现

从 $1$ 枚举到 $n$，每次二分出当前位置元素 $p_i$ 在已知元素中的相对排名。此处的二分可以设置下界 $l=1$，上界 $r=i$。设二分出的相对排名为 $rk$，则将 **位置 $i$** 插入到已知升序序列的 $rk$ 位置，这里可以 **使用 `vector` 的 `insert` 函数实现**。

接着，枚举排名为 $rk+1$ 到 $i$ 的元素，并将其所在位置放上 $1$。从位置 $i-1$ 开始，求一遍 **后缀和**，位置 $L$ 处的后缀和 $suf_L$ 即为在 $[L,i-1]$ 区间内所有大于 $p_i$ 的数的数量，用 $inv_{l,r}$ 为区间 $[l,r]$ 的逆序对数量，则 **使用 $inv_{L,i}=inv_{L,i-1}+suf_L$ 递推**。

在二分时，直接向交互库询问 $f(pos,i)$ 和 $f(pos+1,i)$，即输出 `? pos i` 和 `? pos+1 i`，剩余两个值 **直接调用** $inv_{pos,i-1}$ 和 $inv_{pos+1,i-1}$ 即可。

扫完整个序列后，设 $pos_i$ 为排名（此时即为真实值）为 $i$ 的数对应序列中的位置，则使用 $p_{pos_i}=i$ 还原排列 $p$。

最后先输出一个 `!`，再输出整个排列。

注意 **每次输出完之后刷新缓冲区**。

### 时间复杂度分析

扫一遍序列，每一次需要先二分，其中求大小关系的复杂度为 $O(1)$，询问次数在 $2\log n$ 级别，故单次二分复杂度为 $O(\log n)$。然后，插入 $p_i$、更新区间逆序对数量，单次复杂度都为 $O(n)$。

总时间复杂度 $O(n^2)$，总询问次数约为 $2n\log n$，可以通过本题。

### 参考核心代码

```cpp
int Query(int l,int r){//向交互库询问
    printf("? %d %d\n",l,r);
    fflush(stdout);//注意不要忘记刷新缓冲区
    return R();//返回读入的答案
}
int Query1(int l,int r){
    return inver[l][r];//直接返回已经处理好的逆序对数
}
bool Check(int p,int now){
    if(p+1==now)
        return Query(p,now)==1;//特判两个位置相邻的情况，问1次即可
    return ((Query(p,now)-Query1(p,now-1)-Query(p+1,now)+Query1(p+1,now-1))%2+2)%2==1;//问4次，求出大小关系
    //其中Query是直接向交互库询问，Query1是调用计算好的逆序对数量
}
...
    //对于每个位置都这样做
    int l=0,r=i;
    while(l+1!=r){//二分出当前数的相对排名
        int mid=(l+r)>>1;
        if(Check(pos[mid],i))//满足这个数比当前前缀排名为mid的数小
            r=mid;//向小二分
        else
            l=mid;
    }
    //此时这个数比r对应的数小，比l对应的数大
    pos.insert(pos.begin()+r,i);//在r的位置插入
    vector<int>big(n+1);//临时数组，用于更新逆序对数
    for(j=r+1;j<=i;j++)
        big[pos[j]]=1;//先把所有大于rk的数的位置置1
    for(j=i-1;j>=1;j--)
        big[j]+=big[j+1];//求一遍后缀和
    for(j=i-1;j>=1;j--)
        inver[j][i]=inver[j][i-1]+big[j];//递推更新区间逆序对数量
...
    for(i=1;i<=n;i++)
        p[pos[i]]=i;//还原排列
    putchar('!');
    for(i=1;i<=n;i++)
        printf(" %d",p[i]);//输出答案
    puts(""),fflush(stdout);

---

