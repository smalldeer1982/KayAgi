# Books Exchange (easy version)

## 题目描述

The only difference between easy and hard versions is constraints.

There are $ n $ kids, each of them is reading a unique book. At the end of any day, the $ i $ -th kid will give his book to the $ p_i $ -th kid (in case of $ i = p_i $ the kid will give his book to himself). It is guaranteed that all values of $ p_i $ are distinct integers from $ 1 $ to $ n $ (i.e. $ p $ is a permutation). The sequence $ p $ doesn't change from day to day, it is fixed.

For example, if $ n=6 $ and $ p=[4, 6, 1, 3, 5, 2] $ then at the end of the first day the book of the $ 1 $ -st kid will belong to the $ 4 $ -th kid, the $ 2 $ -nd kid will belong to the $ 6 $ -th kid and so on. At the end of the second day the book of the $ 1 $ -st kid will belong to the $ 3 $ -th kid, the $ 2 $ -nd kid will belong to the $ 2 $ -th kid and so on.

Your task is to determine the number of the day the book of the $ i $ -th child is returned back to him for the first time for every $ i $ from $ 1 $ to $ n $ .

Consider the following example: $ p = [5, 1, 2, 4, 3] $ . The book of the $ 1 $ -st kid will be passed to the following kids:

- after the $ 1 $ -st day it will belong to the $ 5 $ -th kid,
- after the $ 2 $ -nd day it will belong to the $ 3 $ -rd kid,
- after the $ 3 $ -rd day it will belong to the $ 2 $ -nd kid,
- after the $ 4 $ -th day it will belong to the $ 1 $ -st kid.

So after the fourth day, the book of the first kid will return to its owner. The book of the fourth kid will return to him for the first time after exactly one day.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
3
2 3 1
6
4 6 2 1 5 3
1
1
4
3 4 1 2
5
5 1 2 4 3
```

### 输出

```
1 1 1 1 1 
3 3 3 
2 3 3 2 1 3 
1 
2 2 2 2 
4 4 4 1 4 
```

# 题解

## 作者：_Harrisonwhl_ (赞：3)

楼下用的暴搜有点看不懂，楼下大佬在最后提到了并查集，我就来具体写个题解。

首先，如果从一个小朋友开始，一定有环且不会出现树形结构，所以如果一些小朋友在一个并查集里，说明一定是一个接着一个这样传下去的，形成有环图，所以这个集里有几个元素，就要传几次，因为从第一个穿到最后一个是元素数减$1$，再传给第一个，多了$1$次，总共次数就是元素个数。

# $Code$:
```cpp
#include <bits/stdc++.h>
using namespace std;
int tf[205];//存没个元素的负责人。
int fd(int x)//查找本元素的负责人。
{
    if (x == tf[x]) return x;
    return tf[x] = fd(tf[x]);
}
void mg(int x,int y)//合并
{
    int a1 = fd(x),a2 = fd(y);
    if (a1 != a2)
        tf[a1] = a2;//更改为同一个负责人，进入一个并查集。
}
int main()
{
    int T,n,t;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1;i <= n;i++)
            tf[i] = i;
        for (int i = 1;i <= n;i++)
        {
            cin >> t;
            mg(i,t);//合并
        }
        for (int i = 1;i <= n;i++)
        {
            int now = fd(i),cnt = 0;
            for (int j = 1;j <= n;j++)
                if (fd(j) == now) cnt++;//看看有此集几个元素，只要是一个负责人，就是同一个集。
            cout << cnt << " ";//输出
        }//实际上可以记忆化，不用重复查找，但是这样也可以通过。
        cout << endl;
    }
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

一共有$q$组询问，每组询问给定一个长度为$n$的排列$p$，节点$i$向$p_i$连边，求每个点所属的最小环的长度。

$\texttt{Data Range:}1\leq q\leq 200,1\leq n\leq 200$

### 题解

有一道与之类似的题，叫做[$\texttt{Fixed Point Theorem}$](https://www.luogu.org/problem/UVA13074)（话说这是在我板刷$\texttt{UVa}$时偶然碰到的）

首先我们把排列写成置换的形式，有

$$\begin{pmatrix}1&2&3&\cdots&n\\p_1&p_2&p_3&\cdots&p_n\end{pmatrix}$$

然后可以把置换拆解成循环，然后记录一下每个位置所在循环的大小即可。

时间复杂度$O(qn)$，比$\texttt{Tarjan}$常数小。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=1e6+51;
ll test,cnt,tot;
ll vis[MAXN],perm[MAXN],bel[MAXN],size[MAXN];
inline ll read() 
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll dfs(ll cur,ll cnt,ll tot)
{
	if(vis[cur])
	{
		return cnt;
	}
	vis[cur]=1,size[tot]++,bel[cur]=tot;
	return dfs(perm[cur],cnt+1,tot);
}
inline void solve()
{
	for(register int i=1;i<=cnt;i++)
	{
		if(!vis[i])
		{
			dfs(i,0,++tot);
		}
	}
	for(register int i=1;i<=cnt;i++)
	{
		printf("%d ",size[bel[i]]);
	}
	puts("");
}
int main()
{
	test=read();
	for(register int t=0;t<test;t++)
	{
		cnt=read();
		for(register int i=1;i<=cnt;i++)
		{
			perm[i]=read();
		}
		solve();
		tot=0,
		memset(vis,0,sizeof(vis)),memset(bel,0,sizeof(bel));
		memset(size,0,sizeof(size));
	}
}
```

---

## 作者：信息学carryHarry (赞：1)


### 思路

这道题，看到 $N$ 的范围，我们可以用 $O(N^2)$ 的算法，朴素的并查集。

- 元素个数就是总共传的次数（因为还要传给第一个），最后，每个 $i$ 的集合里有多少个元素，就是每个 $i$ 的天数。

### AC 代码：
```cpp
#include<bits/stdc++.h>

using namespace std;
const int N=205;
int t,n,a[N],fa[N];
int find(int x)//路径压缩
{
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y){//合并
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
	return ;
}
int main()
{
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
			unionn(i,a[i]);
		}
		for(int i=1;i<=n;i++){
			int tmp=find(i),cnt=0;
			for(int j=1;j<=n;j++){
				if(find(j)==tmp)
					cnt++;
			}
			cout<<cnt<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：minVan (赞：0)

**题目大意**

有 $n$ 个小朋友每人手里有一本书，给定一个排列 $a$，表示每一轮第 $i$ 个小朋友会把书给 $a_i$。求每个小朋友的书会在几轮后回到自己手里。

**解题思路**

很简单，实现一个简易的 $\texttt{DFS}$，就可以找出每个小朋友在第几轮可以拿回自己的书。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 205;
int t, n, a[N];
int dfs(int cur, int x, int y) {
	if(y == x && cur != 0) {
		return cur;
	}
	return dfs(cur + 1, a[x], y);
}
int main() {
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = 1; i <= n; i++) {
			cout << dfs(0, i, i) << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：盧鋅 (赞：0)

这题很想信息传递有没有

[P2661 信息传递](https://www.luogu.org/problem/P2661)

简单难度的话很明显可以写一个N^2的算法(每个点暴搜就好了)

困难的话对访问加个记忆即可（时间O(N)）

虽然这是一个简单题,我还是写较好的形式吧
```
int vis[300000];
int map[300000];
if(!vis[i]){
	int root=i,step=0;
	vis[i]=root;
	do{
		i=a[i];
		vis[i]=root;
		step++;
	}while(i!=root);
	map[i]=step;
}
```
岂不秒切

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[300000];
int vis[300000];
int map[300000];
signed main(){
	int q;
	cin>>q;
	while(q--){
		memset(a,0,sizeof(a));
		memset(vis,0,sizeof(vis));
		memset(map,0,sizeof(map));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)
		if(!vis[i]){
			int root=i,step=0;
			vis[i]=root;
			do{
				i=a[i];
				vis[i]=root;
				step++;
			}while(i!=root);
			map[i]=step;
		}
		for(int i=1;i<=n;++i)cout<<map[vis[i]]<<" ";
		cout<<endl; 
	}
}
```
当然还有另一种做法，并查集，然后求每一个集中的元素个数。

---

