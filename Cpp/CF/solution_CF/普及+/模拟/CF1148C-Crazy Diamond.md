# Crazy Diamond

## 题目描述

You are given a permutation $ p $ of integers from $ 1 $ to $ n $ , where $ n $ is an even number.

Your goal is to sort the permutation. To do so, you can perform zero or more operations of the following type:

- take two indices $ i $ and $ j $ such that $ 2 \cdot |i - j| \geq n $ and swap $ p_i $ and $ p_j $ .

There is no need to minimize the number of operations, however you should use no more than $ 5 \cdot n $ operations. One can show that it is always possible to do that.

## 说明/提示

In the first example, when one swap elements on positions $ 1 $ and $ 2 $ , the array becomes sorted.

In the second example, pay attention that there is no need to minimize number of swaps.

In the third example, after swapping elements on positions $ 1 $ and $ 5 $ the array becomes: $ [4, 5, 3, 1, 2, 6] $ . After swapping elements on positions $ 2 $ and $ 5 $ the array becomes $ [4, 2, 3, 1, 5, 6] $ and finally after swapping elements on positions $ 1 $ and $ 4 $ the array becomes sorted: $ [1, 2, 3, 4, 5, 6] $ .

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
1 2```

## 样例 #2

### 输入

```
4
3 4 1 2
```

### 输出

```
4
1 4
1 4
1 3
2 4
```

## 样例 #3

### 输入

```
6
2 5 3 1 4 6
```

### 输出

```
3
1 5
2 5
1 4
```

# 题解

## 作者：Fading (赞：2)

这是一个上界为$3n$且比标程更优的解法，而且是我的第一反应...

考虑把序列分成两段，一段是$[1,\frac n2]$，另一段是$[\frac n2+1,n]$。

注意到我们可以利用$1,n$两个位置。因为一个点都可以到达$1$或$n$。

所以思路就来了。我们先填$(\frac n2,\frac n2+1)$，再填$(\frac n2-1,\frac n2+2)$，以此类推，最后填$(1,n)$。

然后就可以分类讨论了，假如我们要把$x(\leq \frac n2)$这个数归位至位置$x$，

如果它所在的段为右，且他可以直接和位置$x$的数交换，那么直接交换，花费$1$。

如果它所在的段为右，且他不可以直接和位置$x$的数交换，那么利用位置$1$，先和位置$1$交换，再和位置$n$交换，最后再和位置$x$交换，花费$3$。

如果它所在的段为左，那么显然他不可以直接和位置$x$的数交换，那么先和位置$n$交换，再和位置$x$交换，花费$2$。

$x\geq \frac n2+1$同理。

~~是不是碾压标算呢？标算是1-3-3-5我是1-2-3~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,a[1010101],pos[1010101];
vector<pair<int,int> > dl;
inline void myswap(int x,int y){
	swap(a[x],a[y]);swap(x,y);
	pos[a[y]]=y;pos[a[x]]=x;
	dl.push_back(make_pair(y,x));
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++){
		a[i]=read();pos[a[i]]=i;
	}
	if (n==2){
		if (a[1]!=1){
			puts("1");
			puts("1 2");
		}else{
			puts("0");
		}
		return 0;
	}
	for (int i=n/2;i;i--){
		if (a[i]!=i){
			if (pos[i]<=i){
				myswap(pos[i],n);
				myswap(i,n);
			}else{
				if (abs(pos[i]-i)>=n/2)	myswap(pos[i],i);
				else{
					myswap(pos[i],1);
					myswap(pos[i],n);
					myswap(pos[i],i);
				}
			}
		}
		if (a[n-i+1]!=n-i+1){
			if (pos[n-i+1]>=n-i+1){
				myswap(pos[n-i+1],1);
				myswap(n-i+1,1);
			}else{
				if (abs(pos[n-i+1]-(n-i+1)>=n/2)) myswap(pos[n-i+1],n-i+1);
				else{
					myswap(pos[n-i+1],n);
					myswap(pos[n-i+1],1);
					myswap(pos[n-i+1],n-i+1);
				}
			}
		}
	}
	cout<<(int)dl.size()<<endl;
	for (auto x:dl){
		printf("%d %d\n",min(x.first,x.second),max(x.first,x.second));
	}
	return 0;
}

```


---

## 作者：_此去经年 (赞：2)

# Crazy Diamond

这题没有紫题难度吧。。。

第一步是~~靠自己强大的英语功底~~读懂题目

注意到操作次数限制在$n*5$

$5$是什么东西? ~~不会了~~

这时掏出我们的灵魂三问：暴力怎么写?搜索怎么写?~~正解怎么写?~~

考虑时间复杂度不做限制的情况：

我们对于第$i$个阶段，将$i$元素归位，这样n个阶段就可以做完题目

那么，对于每个阶段，我们的操作次数不大于5次便可以~~完美的水过这道水题~~

我们定义操作的当前阶段要归位的元素定义为$x$，占用了$x$原本位置的元素定义为$y$，它们之间的距离设为$dis$，区间总长为$len$，区间中点为$mid$

接下来是分类讨论：

当：1. $dis(x,y) >= len/2$ ~~直接交换就行了啊~~

2. $dis(x,y) < len/2(x<mid,y>mid)$

   我们注意到不管x左区间的什么位置，都有区间右端点到$x$的距离大于等于$len/2$，$y$亦然。所以操作时如下图一样换换就好，正好是五次

   ![1.png](https://i.loli.net/2019/08/12/UyqzAIZxaMwdo4i.png)

3. $dis(x,y) < len/2(x<mid,y<mid)$

   和上面的情况大差不差

   ![2.png](https://i.loli.net/2019/08/12/pfQctbNUG4gS2aT.png)

就做完了！~~代码实现应该不是很难，不如自己试着写写看？~~

---

## 作者：FiraCode (赞：0)

## 思路：
可以依次从小到大考虑归位。

对于第 $i$ 大，若它原本的位置和它要在的位置满足题目中给出的关系那么直接交换即可。

若它原本的位置和它要在的位置相等直接跳过即可。

否则在这个数的后面或前边一定有一部分中数的个数是 $\ge \frac n 2$。

*	若这个数的后边数的个数 $\ge \frac n 2$，那么可以考虑直接跳到 $n$，然后再跳到它应在的位置。
*	若这个数的前边数的个数 $\ge \frac n 2$，那么可以考虑先于第一个数交换，然后若于它应在的位置距离满足条件就直接跳，否则就先跳到 $n$，再跳到应该在的位置，然后再将第一个数换回去。

然后最多的交换次数就是这个数前面的数的个数 $\ge \frac n 2$ 且跳到 $1$ 之后要再跳到 $n$，再跳回应在的位置，所以最多的交换次数为 $4n$，低于上界可行。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int a[300010];
pair<int, int> b[300010];
int di[300010];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		b[i] = {a[i], i};
	}

	sort(b + 1, b + 1 + n);
	for (int i = 1; i <= n; ++i) {
		di[i] = b[i].second;
	}

	vector<pair<int, int>> opt;

	for (int i = 1; i <= n; ++i) {
		// cout << i << ' ' << a[1] << "---\n";
		// printf("QAQWQ\n");
		// for (int j = 1; j <= n; ++j) printf("%d ", a[j]);
		// puts("");
		if (di[i] == i) continue;
		else if (2 * abs(di[i] - i) >= n) {
			opt.push_back({i, di[i]});
			swap(di[a[i]], di[i]);
			swap(a[i], a[di[a[i]]]);
		} else {
			if (n - di[i] >= n / 2) {
				opt.push_back({di[i], n});
				swap(di[i], di[a[n]]);
				swap(a[di[a[n]]], a[n]);
				opt.push_back({i, n});
				swap(di[a[n]], di[a[i]]);
				swap(a[i], a[n]);
			} else {
				opt.push_back({1, di[i]});
				swap(di[a[1]], di[i]);
				swap(a[1], a[di[a[1]]]);
				// cout << a[1] << endl;
				if (i - 1 >= n / 2) {
					opt.push_back({1, i});
					swap(di[a[1]], di[a[i]]);
					swap(a[1], a[di[a[1]]]);
					opt.push_back({1, di[1]});
					swap(di[a[1]], di[1]);
					swap(a[1], a[di[a[1]]]);
				} else {
					opt.push_back({1, n});
					swap(di[a[1]], di[a[n]]);
					swap(a[1], a[n]);
					// cout << a[1] << "---\n";
					opt.push_back({i, n});
					swap(di[a[i]], di[a[n]]);
					swap(a[i], a[n]);
					// cout << a[1] << "---\n";
					opt.push_back({di[1], 1});
					// cout << di[1] << ' ' << a[1] << ' ' << di[a[1]] << a[di[a[1]]] << endl;
					swap(di[1], di[a[1]]);
					swap(a[1], a[di[a[1]]]);
				}
			}
		}
	}

	printf("%d\n", opt.size());
	for (auto v : opt) {
		printf("%d %d\n", v.first, v.second);
	}

	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

**CF1148C**

原题的数据范围过松。有点糟蹋这道题了。

$\text 3 \text n$ 即构造一种 $\text {Swap(x,y)}$，只需要操作 $\text 1,\text n$ 两个节点暴力交换即可，即我们从 $\text 1 \sim \text n$
 暴力扫，逐步满足前缀的需求。称该种方法为构造 $\text 1$。
 
 一种 $\text 2.25 \text n$ 的做法是我们考虑设置左右端点 $\text l,\text r$ 令 $\text l = \frac{\text n}{\text 2},\text r = \frac{\text n}{\text 2} + \text 1$，我们让 $\text l,\text r$ 一起向左右跳，每次对于端点执行构造 $\text 1$，直到满足 $\text r - \text l + \text 1 = \frac{\text n}{\text 2}$ 为止。这一部分的贡献是 $\frac{\text 3 \text n}{\text 2}$。然后我们分两次处理 $[\text 1,\text l)$ 和 $[\text r + \text 1,\text n]$ 的位置，称两段数分别是“左边的数”和“右边的数”。以处理左边的数为例，我们每次找到一个置换环满足所有数都在左边，若在这个过程出现了指向右边的数，直接暴力交换；对于每个环从任意一个点 $\text s_{\text 1}$ 作为起点，执行 $\text {swap}(\text s_{\text i},\text n)$，最后再执行一次 $\text {swap}(\text s_{\text 1,\text n})$ 即可完成对这个环的操作，即贡献的代价是“环数加点数”，注意到这里的环只有大小至少为 $\text 2$ 的环，贡献即 $\frac{\text 3 \text n}{\text 4}$，总的代价就是 $\text {2.25} \text n$ 的。
 
一种 $\text 2 \text n$ 的做法是考虑每个环，直接找到一个环从任意节点开始遍历。每一次先跳到它能跳到的 $\text 1,\text n$ 中的一个端点，然后看下一次要跳的节点能不能被端点跳到，否则跳到另一个端点去，就做到了 $\text 2 \text n$。

因为降智了，考场上我本来是想写 $\text {2.25} \text n$ 的，不过现写出来好像是上界 $\text 3.5 \text n$ 的，寄。

这份代码就图一乐吧。

```cpp
/*
考虑如何实现交换任意两个位置的元素
发现可以做到，完成。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,p[Len],a[Len],now[Len],w[Len];
struct mp
{
	int x,y;
	mp(){x = y = 0;}
	mp(int X,int Y){x = X , y = Y;}
}Pt[Len << 2];int len;
inline void Swap(int x,int y)
{
	if(x == y) return;
	if(x <= n / 2 && y <= n / 2)
	{
		int R = n;
		swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
		swap(now[a[y]] , now[a[R]]) ; swap(a[y] , a[R]) ; Pt[++ len] = mp(y , R);
		swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
		return;
	}
	if(x > n / 2 && y > n / 2)
	{
		int R = 1;
		swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
		swap(now[a[y]] , now[a[R]]) ; swap(a[y] , a[R]) ; Pt[++ len] = mp(y , R);
		swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
		return;
	}
	swap(now[a[x]] , now[a[y]]) ; swap(a[x] , a[y]) ; Pt[++ len] = mp(x , y);
}
inline int Iabs(int x){if(x < 0) x = -x;return x;}
int main()
{
	//freopen("project.in","r",stdin);
	//freopen("project.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&w[i]);
		p[w[i]] = i;
		a[i] = i;
		now[i] = i;
	}
	int i;
	int l = n / 2 , r = n / 2 + 1;
	while(l >= 1 && r <= n)
	{
		i = l;
		int x = p[i];
		if(now[x] != i) 
		{
			if(Iabs(i - now[x]) * 2 >= n || (now[x] <= n / 2 && i <= n / 2) || (now[x] > n / 2 && i > n / 2)) Swap(now[x] , i);
			else
			{
				int nm = now[x];
				if(i <= n / 2) 
				{
					Swap(nm , 1);
					Swap(1 , i);
					//Swap(nm , 1);
				}
				else
				{
					Swap(nm , n);
					Swap(n , i);
					//Swap(nm , n);
				}
			}
		}
		l --;
		i = r;
		x = p[i];
		if(now[x] != i) 
		{
			if(Iabs(i - now[x]) * 2 >= n || (now[x] <= n / 2 && i <= n / 2) || (now[x] > n / 2 && i > n / 2)) Swap(now[x] , i);
			else
			{
				int nm = now[x];
				if(i <= n / 2) 
				{
					Swap(nm , 1);
					Swap(1 , i);
					//Swap(nm , 1);
				}
				else
				{
					Swap(nm , n);
					Swap(n , i);
					//Swap(nm , n);
				}
			}
		}
		r ++;
	}
	printf("%d\n",len);
	for(int i = 1 ; i <= len ; i ++) printf("%d %d\n",Pt[i].x,Pt[i].y);
	return 0;	
} 
```

---

## 作者：Ousmane_Dembele (赞：0)

构造题………………

思路见上，说的真的非常明确了，图也画得很好，不过没有代码

不过这题还是有一些细节需要维护的

看代码

```
#include<iostream>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[1000002],b[1000001];
int ans[1000002][4],cnt;
int abs(int u,int v){
    if(u>v)return u-v;
    else return v-u;
}
void get(int x,int y){//交换(x,y)的值并记录
    b[a[x]]=y;
    b[a[y]]=x;
    swap(a[x],a[y]);
    ans[++cnt][1]=x;
    ans[cnt][2]=y;
}
void get1(int x,int y){//x>mid,y>mid
    get(1,x);
    get(1,y);
    get(1,x);
}
void get2(int x,int y){//x<mid,y<mid
    get(y,n);
    get(x,n);
    get(y,n);
}
void get3(int x,int y){//x<mid,y>mid但y-x<n/2
    get(1,y);
    get(x,n);
    get(1,n);
    get(1,y);
    get(x,n);
}

void solve(int u,int v){
    if(u==v)return;//本身就在位置上的不用改了
    if(u>v)swap(u,v);
    if(abs(u,v)*2>=n)get(u,v);//abs(x,y)>=mid
    else if(u*2>n)get1(u,v);
    else if(v*2<=n)get2(u,v);
    else get3(u,v);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[a[i]]=i;//记录a[i]出现的位置
    }
    for(int i=1;i<=n;i++){
        solve(i,b[i]);
    }
    cout<<cnt<<endl;//按照要求输出
    for(int i=1;i<=cnt;i++)
        cout<<ans[i][1]<<" "<<ans[i][2]<<endl;
}

```


---

