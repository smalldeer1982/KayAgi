# Queen

## 题目描述

You are given a rooted tree with vertices numerated from $ 1 $ to $ n $ . A tree is a connected graph without cycles. A rooted tree has a special vertex named root.

Ancestors of the vertex $ i $ are all vertices on the path from the root to the vertex $ i $ , except the vertex $ i $ itself. The parent of the vertex $ i $ is the nearest to the vertex $ i $ ancestor of $ i $ . Each vertex is a child of its parent. In the given tree the parent of the vertex $ i $ is the vertex $ p_i $ . For the root, the value $ p_i $ is $ -1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/767631fbfbd5e834691c335a1beebc4c83722771.png)An example of a tree with $ n=8 $ , the root is vertex $ 5 $ . The parent of the vertex $ 2 $ is vertex $ 3 $ , the parent of the vertex $ 1 $ is vertex $ 5 $ . The ancestors of the vertex $ 6 $ are vertices $ 4 $ and $ 5 $ , the ancestors of the vertex $ 7 $ are vertices $ 8 $ , $ 3 $ and $ 5 $ You noticed that some vertices do not respect others. In particular, if $ c_i = 1 $ , then the vertex $ i $ does not respect any of its ancestors, and if $ c_i = 0 $ , it respects all of them.

You decided to delete vertices from the tree one by one. On each step you select such a non-root vertex that it does not respect its parent and none of its children respects it. If there are several such vertices, you select the one with the smallest number. When you delete this vertex $ v $ , all children of $ v $ become connected with the parent of $ v $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/fa2af41e1e599c9e51ca9e3edafbee94d578e807.png)An example of deletion of the vertex $ 7 $ .Once there are no vertices matching the criteria for deletion, you stop the process. Print the order in which you will delete the vertices. Note that this order is unique.

## 说明/提示

The deletion process in the first example is as follows (see the picture below, the vertices with $ c_i=1 $ are in yellow):

- first you will delete the vertex $ 1 $ , because it does not respect ancestors and all its children (the vertex $ 2 $ ) do not respect it, and $ 1 $ is the smallest index among such vertices;
- the vertex $ 2 $ will be connected with the vertex $ 3 $ after deletion;
- then you will delete the vertex $ 2 $ , because it does not respect ancestors and all its children (the only vertex $ 4 $ ) do not respect it;
- the vertex $ 4 $ will be connected with the vertex $ 3 $ ;
- then you will delete the vertex $ 4 $ , because it does not respect ancestors and all its children (there are none) do not respect it ([vacuous truth](https://en.wikipedia.org/wiki/Vacuous_truth));
- you will just delete the vertex $ 4 $ ;
- there are no more vertices to delete.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/ebd0eb4e79b93258618d042cf4204608334ae632.png)In the second example you don't need to delete any vertex:

- vertices $ 2 $ and $ 3 $ have children that respect them;
- vertices $ 4 $ and $ 5 $ respect ancestors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/301d90419aa6803a28893c2a81f56219871e0793.png)In the third example the tree will change this way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1143C/7676abdd5b6383c016cad416ee32ca622873b718.png)

## 样例 #1

### 输入

```
5
3 1
1 1
-1 0
2 1
3 0
```

### 输出

```
1 2 4 
```

## 样例 #2

### 输入

```
5
-1 0
1 1
1 1
2 0
3 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8
2 1
-1 0
1 0
1 1
1 1
4 0
5 1
7 0
```

### 输出

```
5 
```

# 题解

## 作者：Zq_water (赞：6)

很简单，我们用 $a$ 数组来记录子节点是否尊重他，用 $b$ 数组来记录他是否尊重父节点。

先将标记初始化为 $0$。输入时，要判断一下 $x \neq -1$ 防止数组越界，然后维护两个数组。输出时只需要遍历一遍，当第 $i$ 项同时满足 $a_i$ 和 $b_i$ 的时候，输出 $i$，同时将标记修改为 $1$，若最后标记为 $0$，则没有节点满足条件，输出 $-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n,f,a[100005],b[100005];

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) a[i]=1;
	
	for(ll i=1,x,y;i<=n;i++){
		scanf("%lld %lld",&x,&y);
		if(x!=-1) a[x]&=y,b[i]=y;
	}
	for(ll i=1;i<=n;i++) if(a[i]&b[i]) printf("%lld ",i),f=1;
	
	if(!f) printf("-1");
	return 0;
}
```

---

## 作者：bigclever (赞：6)

## 思路：
因为我们需要输出不尊重父节点且子节点都不尊重它的节点，所以我们用 $a$ 数组来维护它的**所有子节点是否尊重它**，$b$ 数组维护**尊不尊重它的父节点**。维护 $a$ 数组只要将它所有儿子是否尊重它的值全部进行**与运算**，$b$ 数组直接赋值即可。最后若两个条件都满足，则输出。若一个满足所有条件的数都没有，记得输出 $-1$。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++)a[i]=1;//a数组一开始全部赋值为1，不然按位与出的都是0
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		if(x!=-1)a[x]&=y,b[i]=y;
	}
	bool ok=false;
	for(int i=1;i<=n;i++)
		if(a[i]&&b[i])cout<<i<<' ',ok=true;
	if(!ok)cout<<-1;
	return 0;
}
```

---

## 作者：EdenSky (赞：6)

# [CF1143C Queen](https://www.luogu.com.cn/problem/CF1143C)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/16816905.html)

## 正文

**最坏时间复杂度：$\mathcal{O}(n)$**

思维题，不需要建树。

设数组 $a$ 记录每一个节点是否尊重它的父节点，数组 $b$ 记录**是否有节点尊重它**，特别的，叶子节点必然不被尊重。

对于每次的输入数据 $x,y$。若 $y$ 等于 1（即不尊重它的父节点），那 $a_i \leftarrow 1$；若 $y$ 等于 0，那 $b_a\leftarrow 1$，最后遍历一遍，如果 $a_i=1,b_i\ne 1$，那么代表这个节点既不尊重它的父节点，也没有子节点尊重它，输出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
pair<bool,bool> a[(int)1e5+5];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int f,b;
		cin>>f>>b;
		if(b==0)
			a[f==-1?0:f].second=true;
		else	a[i].first=true;
	}
	bool flag=true;
	for(int i=1;i<=n;i++){
		if(a[i].first and !a[i].second){
			flag=false;
			cout<<i<<' ';
		}
	}
	if(flag)	cout<<-1;
}
```

[提交记录](https://www.luogu.com.cn/record/90198380)，华丽结束。

---

## 作者：ys_kylin__ (赞：5)

## 题解：Queen
当我第一眼看到这一题时，我心想：现在的蓝题那么水吗？！这不就是一道简单的不能再简单的图论吗？（甚至不用图来做也行），结果因为英文题目没翻译完导致我完美零分（答案为负一时没考虑到）。。

对于每一个 $a _ {i}$，都查看是否被尊重，若 $b$ 为 $1$（不尊重）则用一个向量把 $i$ 进行 `push_back` 操作，同时用一个数组记下每个节点的子节点个数，再用一个数组记下每个节点是否尊重它的父节点。最后对于每一个节点判断，判断条件为：

`if(ve[i].size()==b[i] && fl[i]>=1)` 

（此处 $fl _ {i}$ 为计算编号为 $i$ 的节点是否尊重他的父节点，$b _ {i}$ 为第 $i$ 个节点的子节点数）。

然后若查询到满足条件的编号就输出，这道题就这样完成了。。。？

no，一定记得处理无输出情况，如果没有满足条件的数，一定要输出 $-1$！

我就是这样五连 wa 的 QAQ。

好了，上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],fl[100005];//a数组为读入，b数组为每个节点的子节点个数
vector <int> ve[100005];
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		int y;
		scanf("%d%d",&a[i],&y);
		if(y==1 && a[i]!=-1) {
			ve[a[i]].push_back(i);
			fl[i]=1;
		}
		b[a[i]]++;
	}
	int fll=0;
	for(int i=1;i<=n;i++) {
		if(ve[i].size()==b[i] && fl[i]>=1) {
			printf("%d ",i);
			fll=1;
		}
	}
	if(!fll) printf("-1");
	return 0;
}
```

---

## 作者：songhongyi (赞：4)

题意：给定一颗树，求所有不尊重父亲且所有儿子都不尊重的点

分析&解法：很容易发现题目树的给法根本不需要建树。我们对每个节点定两个布尔值 $a,b$。$a$ 表示该节点是否不尊重父亲，是题目给出的；$b$ 表示**是否所有儿子都不尊重它**，显然该值成立当且仅当它的所有儿子都不尊重它，所以该值为所有儿子 $a$ 值的逻辑且。

代码就很简单了
```cpp

// Problem: CF1143C Queen
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1143C
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstring>
#include <iostream>
using namespace std;
bool a[ 100010 ], b[ 100010 ];
int main()
{
    int n;
    cin >> n;
    memset( a, 1, sizeof( a ) );
    for ( int i = 1; i <= n; i++ )
    {
        int x, y;
        cin >> x >> y;
        if ( x != -1 )
        {
            a[ x ] &= y;
            b[ i ] = y;
        }
    }
    bool flag = false;
    for ( int i = 1; i <= n; i++ )
    {
        if ( b[ i ] && a[ i ] )
        {
            flag = true;
            cout << i << " ";
        }
    }
    if ( !flag )
    {
        cout << -1;
    }
    cout << endl;
}
```

---

## 作者：囧仙 (赞：2)

## 题目大意

> $n$ 个节点构成了一棵树，每个节点都会尊重或者不尊重它的所有祖先。现在按照编号从小到大删除每一个**不尊重祖先且它的 _直接_ 儿子不尊重它**的节点。输出所有被删除的节点，或者输出 $-1$ 。  
特别地，根节点必定尊重它的祖先。

**注**：题面上的翻译省略了删点这个过程。虽然可以证明删点不会对答案造成任何影响，但是这么做思维难度直接没了……

## 题解

并不是一道很难的题，评蓝有些高了……

考虑一个节点被删除后对答案可能造成的影响。事实上，它不会造成任何影响。这个结论可以算是本题的关键。考虑如何证明。

一个节点被删除的充要条件是：

- $1.$ 它的直接儿子都不尊重祖先（或者没有儿子）。
  
- $2.$ 它不尊重祖先（尽管它可能没有祖先）。

显然由于根节点必定尊重祖先，所以根节点不会被删除。考虑删除一个不是根节点的节点。为了叙述方便，设它为 $u$ ，它的父节点为 $fa$ 。

- 假设 $fa$ 本来就要被删除，那么删除 $u$ 后，新接上去的节点肯定也不尊重 $fa$ （由条件 $1$ ），于是不会改变 $fa$ 的定性。

- 假设 $fa$ 本来不要被删除，那么删除 $u$ 后也不会使 $fa$ 变得要删除（由条件 $2$ ，$u$ 肯定不尊重 $fa$ ，于是 $fa$ 有其他的直接儿子尊重它）。

于是我们证明了删除一个节点不会产生任何影响。那么做起来就很简单了：枚举每个节点，看它直接儿子是不是都不尊重它，再看这个节点是否尊重祖先，就能决定是否删除它了。由于一共只有 $n-1$ 条边，于是枚举的总时间花费应该是 $\mathcal O(n)$ 的。

关于最后的从小到大输出。事实上，我们直接枚举序号 $1,2,\cdots n$ 就行了，甚至不需要排序。

什么？你觉得遍历一遍边常数太大了？事实上，我们完全不需要建图。由于本题输入了每个节点的父节点，于是只要另开一个 $\text{bool}$ 数组用于存储每个节点直接儿子是否都不尊重它就行了。常数再次缩小……

**时间复杂度**： $\mathcal O(n)$ 。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e5+3;
bool I[MAXN],J[MAXN],f; int n;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(),memset(J,1,sizeof(bool)*(n+1));
    up(1,n,i){
        int t=qread(); I[i]=qread(); if(t!=-1) J[t]&=I[i];
    }
    up(1,n,i) if(I[i]&&J[i]) printf("%d ",i),f=true;
    if(!f) puts("-1");
    return 0;
}
```

---

## 作者：feiji_code (赞：1)

这道题很简单，坑点是翻译里没给出**在没有一个满足条件的节点的情况下要输出** **$-1$**。

我们建 $2$ 个数组，用来存是否尊重父节点和子节点是否尊重它，并将 $f$ 数组初始化，方便与运算，最后符合条件的输出。
### 废话不多说，上代码。
### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int f[100001],f2[100001];
int flag=0;
void chushihua() {
	for(int i=1; i<=n;i++){
		f[i]=1;
	}
}
int main() {
	cin>>n;
	chushihua();
	for(int i=1; i<=n; i++) {
		cin>>a>>b;
		if(a!=-1) {
			f2[i]=b;
			f[a]&=b;
		}
	}
	for(int i=1; i<=n; i++) {
		if(f[i]&f2[i]) {
			cout<<i<<' ';
			flag=1;
		}
	}
	if(flag==0) {
		cout<<-1;
	}
	return 0;
}

```
###### （第一次提交题解，望过。）


---

## 作者：OldVagrant (赞：1)

## 题意
给定一个 $n$ 个点的有根树，节点 $i$ 的父节点为 $p_i$（根节点的 $p_i$ 为 $-1$），每个节点有一个值 $b_i$，如果 $b_i$ 为 $0$ 表示这个节点尊重其所有祖先节点，为 $1$ 则表示这个节点不尊重其任何一个祖先节点。	   

对于一个节点 $x$，如果 $b_x=1$ 且对于 $x$ 的任意一个儿子 $son_x$ 都有 $b_{son_x}=1$，那么称节点 $x$ 为一个 ``Queen`` 节点。   

现在，我们要进行若干次操作，每次操作会删除当前树上的一个 ``Queen`` 节点 $v$（如果有多个则选择那个编号最小的），删除之后将 $v$ 的所有儿子 $son_v$ 与 $v$ 原本的父亲 $fa_v$ 相连（如果没理解这句话的话建议看题目描述里给的那个图），直到树上不存在任何一个 ``Queen`` 节点。请按顺序输出每次操作所删除的节点的编号，如果无法进行任何一次操作，输出 ``-1``。
## Solution
翻译其实给的不太好，相当于是把这个题化简了，只剩一个简单的模拟。
	
这道题的关键就在于，每次删点之后，没有任何节点会成为新的  ``Queen`` 节点，也没有任何 ``Queen`` 节点会变为非 ``Queen`` 节点。所以只需要按编号升序输出最开始树上的所有 ``Queen`` 节点即可。
 
假设现在我们删去了点 $v$，然后要将 $v$ 的所有儿子与 $fa_v$ 相连。因为 $v$ 是 ``Queen`` 节点，这代表着 $b_v=1$ 且 $\forall x\in son_v,b_x=1$。于是，这个操作相当于让 $fa_v$ 少了一个 $b_i=1$ 的儿子，多了若干个 $b_i=1$ 的儿子。如果原来 $fa_v$ 就是 ``Queen`` 节点，那操作之后仍然是；如果原来不是的话那么操作之后也不会变成 ``Queen`` 节点。

那么现在只需要找出最初树上的所有 ``Queen`` 节点了。实现这个连树都不需要建，时空复杂度均为 $O(n)$。
 
我们需要维护的是每个节点的 $b_i$，以及其子节点内是否有任何一个节点的 $b_i=0$。
开两个 ``bool`` 数组，每次读入时同步修改即可，如果读入的 $b_i=1$，则在另一个数组里将 $p_i$ 标记为 $1$。读入完之后遍历一遍 $1\sim n$，如果遇到了 ``Queen`` 节点就输出。 
 
## Code
```
#include <bits/stdc++.h>
using namespace std;
bool f[100001],p[100001];
int read(){
	int x=0,y=1;
	char ch=gc();
	while(ch<48||ch>57){
		if(ch=='-') y=0;
	 	ch=gc();
	}while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return y?x:-x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
signed main(){
	int n=read(),cnt=0;
	for(int i=1,x;i<=n;i++){
		x=read(),p[i]=read();
		if(!p[i]) f[x]=1;
	}for(int i=1;i<=n;i++) if(p[i]&&!f[i]) write(i),pc(' '),cnt++;
	if(!cnt) cout<<-1;
	return 0;
}
```


---

## 作者：sto_5k_orz (赞：0)

终于可以切蓝了。

考虑 $y$ 尊不尊重父节点，则对于每一个节点 $x$，看 $y$ 尊不尊重他就可以了，这个东西开个数组 $b$ 记录，$b_x=1$ 表示 $x$ 尊重父节点。

然后对于每个 $x$，只需要看是否每个 $y$ 都尊重它，于是对于每个 $x,y$，如果 $y=0$，则 $a_x=0$。

最后，$a_i=1,b_i=1$ 的就是答案了。

注意无解输出 $-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010; int a[N], b[N], n;
signed main() {
	cin >> n; for(int i = 1; i <= n; i++) a[i] = 1; bool f = 0;
	for(int i = 1; i <= n; i++) {int x, y; cin >> x >> y; if(~x) a[x] &= y, b[i] = y;}
	for(int i = 1; i <= n; i++) {if(a[i] & b[i]) cout << i << ' ', f = 1;} if(!f) cout << -1;
	return 0;
}
```

---

## 作者：Composite_Function (赞：0)

$$\text{思路}$$

翻译里没有体现有删除，但实际是有选完一个点就删除。

如果要把一个节点给删除，那么充要条件是：

1. 不存在尊敬它的儿子节点。
2. 它不尊敬它的祖先节点。

考虑一节点被删除的影响，会发现能影响到的只有它的父节点，分两种情况：

1. 它的父节点要被删除，则删除它的子节点也不尊敬它的父节点，还会删除。
2. 它的父节点不被删除，那么依旧。

所以，**被删除根本不会有影响**。

于是，若一个节点不尊敬祖先节点，也没有子节点尊敬它，它就被删除，时空均为 $O(n)$。

------------


---

## 作者：Abeeel51 (赞：0)

#### 题目大意
给一棵树，每个节点都有一个值( $0$ 或 $1$ )，输入 $a$ 和 $b$ ，若 $a$ 所有的儿子节点为 $1$ ，且 $a=1$ ， $a$ 节点就不尊重。求所有不尊重的节点。若没有不尊重的节点则需要输出 $-1$ 。
#### 解题思路
看到与树有关，没仔细读题，想要建树形，~~但是不会~~。

接着来倒推：

如果当前节点为 $0$ ，则当前节点一定尊重，其父亲节点也一定尊重。

所以，在所有 $b$ 为 $0$ 的节点，标记 $vis_i$ （ $i$ 是输入的第几组 $a$ 与 $b$ ），如果 $a \ge 0$ ，标记 $vis_a$ 。

最后输出所有不尊重的节点。
#### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool fa[100005];
int main(){
    ll n;
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        ll a,b;
        scanf("%lld%lld",&a,&b);
        if(b==0){
            fa[i]=true;
            if(a>=0) fa[a]=true;
        }
    }
    bool flag=true;
    for(ll i=1;i<=n;i++){
        if(fa[i]==false){
            flag=false;
            printf("%lld ",i);
        }
    }
    if(flag) puts("-1");
    else puts("");
    return Accepted;
}
```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/09/01/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces1143C%20Queen/)

### Solution

我们统计出每一个父结点儿子的数量和不尊重父亲结点的数量，如果相等就全是不尊重父亲的结点，就是答案，所以我们统计完之后只需要枚举每一个点，条件为：

1. 儿子的数量等于不尊重父亲结点的数量

2. 父结点不为根节点

3. 自己也是不尊重父亲结点

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 100005;
int n, p[MAXN], c[MAXN], son_size[MAXN], son_disrespect[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i], &c[i]);
        son_size[p[i]]++;//统计儿子的总数
        son_disrespect[p[i]] += c[i];//统计不尊重父亲结点的数量
    }
    bool flag = 0;
    for (int i = 1; i <= n; i++) {
        if (son_size[i] == son_disrespect[i] && ~p[i] && c[i]) {//条件
            printf("%d ", i);
            flag = 1;
        }
    }
    if (!flag) printf("-1\n"); else printf("\n");
    return 0;
}
```

---

## 作者：世末OIer (赞：0)

打模拟赛是随便瞎想的办法(不是正解!!!)

1.先处理出根节点

2.从根开始dfs出深度(深度决定一切)

3.按照深度排序

4.按照排序完的顺序的方式dfs2()判断是否可以删除即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int col[100005];
bool use[100005];
vector<int> v[100005];
int par[100005],n,root;
set<int> ans;
int b[100005];
int dep[100005];
inline void dfs(int x,int d){
	dep[x]=d;
	for(int i=0;i<v[x].size();++i) dfs(v[x][i],d+1);
}
inline bool cmp(int x,int y){
	return dep[x]<dep[y];
}
inline void go(int x){
	use[x]=1;
	bool ok=1;
	for(int i=0;i<v[x].size();++i) if(col[v[x][i]]==1) go(v[x][i]);else ok=0;
	if(ok and x!=root) ans.insert(x);
}
int main(){
	cin>>n;
	int i,j,x,y;
	for(i=1;i<=n;++i){
		cin>>x>>y;
		par[i]=x;
		if(x!=-1) v[x].push_back(i);
		else root=i;
		col[i]=y;
	}
	dfs(root,0);
	for(i=1;i<=n;++i) b[i]=i;
	sort(b+1,b+n+1,cmp);
	for(i=1;i<=n;++i) if(!use[b[i]] and col[b[i]]==1) go(b[i]);
	if(ans.size()==0) cout<<"-1\n";
	else for(auto it:ans) cout<<it<<' ';
	cout<<endl;
	return 0;
}
```

---

