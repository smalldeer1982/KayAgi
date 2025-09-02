# Tree Construction

## 题目描述

During the programming classes Vasya was assigned a difficult problem. However, he doesn't know how to code and was unable to find the solution in the Internet, so he asks you to help.

You are given a sequence $ a $ , consisting of $ n $ distinct integers, that is used to construct the binary search tree. Below is the formal description of the construction process.

1. First element $ a_{1} $ becomes the root of the tree.
2. Elements $ a_{2},a_{3},...,a_{n} $ are added one by one. To add element $ a_{i} $ one needs to traverse the tree starting from the root and using the following rules: 
  1. The pointer to the current node is set to the root.
  2. If $ a_{i} $ is greater than the value in the current node, then its right child becomes the current node. Otherwise, the left child of the current node becomes the new current node.
  3. If at some point there is no required child, the new node is created, it is assigned value $ a_{i} $ and becomes the corresponding child of the current node.

## 说明/提示

Picture below represents the tree obtained in the first sample.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675D/81b08320b33046f6dd8d383835aa5713076f0650.png)

Picture below represents the tree obtained in the second sample.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675D/a69a26d019b1bf51600e9935b0aa85fc4fdf5e99.png)

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
5
4 2 3 1 6
```

### 输出

```
4 2 2 4
```

# 题解

## 作者：Erusel (赞：5)

本题为 $\text{Trees-Tag}$

---

原题要求每个节点在构造的二叉排序树上的父亲节点

很容易发现为前驱后继中出现较后的一个

可以使用 ```map``` 来解决这个问题

```map``` 的 ```lower_bound``` 不是只能找后继吗？

只要在插入的时候，以权值作下标，修改之前的值就行啦

时间复杂度 $O(nlogn)$

Code:

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define inf 1e9+1

using namespace std;

int n;
map<int,int>s;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int main()
{
	rd(n);int x;rd(x);s[inf]=s[x]=x;	
	for(int i=2;i<=n;i++)
	{
		rd(x);auto it=s.lower_bound(x);
		printf("%d ",(*it).second),s[x]=(*it).second=x;
	}

    return 0;
}


```

---

## 作者：花园Serena (赞：4)

这道题目是在考试的时候写到的...当时没有写出来，改正的时候想到了写法

首先，我们有一棵二叉排序树。

什么是二叉排序树呢，就是说他的中序遍历是一个从小到大的数列。

# 那么，我们就可以来做一些事情.

借用题目中的数据，我们来发现一些有趣的东西

![](https://cdn.luogu.com.cn/upload/image_hosting/qbths8b8.png)


```
这棵树的中序遍历是 1 2 3 4 6

```
而每个点的父节点不是他的前驱就是他的后继...

### 为什么呢？

因为中序遍历是以 **左 根 右**的顺序遍历的，所以他的父节点一定是他的前驱或者后继。

我们考虑排序后建一个链表（本人太弱用的数组）,用红色表示访问的节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/l8wo3rkv.png)


接着我们查询他前驱和后继。


### 但是 ，我们怎么知道前驱和后继谁是他的父节点呢？

我的想法是寻找最后一个被加入的节点


![](https://cdn.luogu.com.cn/upload/image_hosting/tauozwho.png)

那么他的父亲就是他的前驱后继中较为后加入的那个。

而每当我们在链表中找到一个节点的父亲，就将它删除，避免影响后来的节点。

具体代码实现如下

```c
#include <bits/stdc++.h>
using namespace std;
struct node {
	int data, pos;
	int next, front;//前驱后继
}a[100000 + 10];
int ans[100000 + 10];//保存答案
int last[100000 + 10];//保存第i个被插入树中的数在排序后的位置
bool cmp (node x, node y) {
	if(x.data == y.data) return x.pos > y.pos;
	return x.data < y.data;
}
int main ()  {
	int n; scanf("%d" ,&n);
	for(register int i = 1; i <= n; i ++) {
		scanf("%d", &a[i].data);
		a[i].pos = i;
	}
	sort(a + 1, a + n + 1, cmp);//排序
	for(register int i = 1; i <= n; i ++) {
		last[a[i].pos] = i;  //处理指针
		a[i].next = i + 1;
		a[i].front = i - 1;
	}
	for(register int i = n; i >= 2; i --) {
		int u = last[i];
		if(a[a[u].front].pos > a[a[u].next].pos) {
			ans[a[u].pos] = a[a[u].front].data;
		}//寻找前驱后继中较大的
		else {
			ans[a[u].pos] = a[a[u].next].data;
		}
		a[a[u].front].next = a[u].next;
		a[a[u].next].front = a[u].front;
	}
	for(register int i = 2; i <= n; i ++)
		printf("%d ", ans[i]);//输出！！！
	return 0;
}
```
### 感谢您的阅读，如有错误或不明确出，请评论或私信指出

---

## 作者：CrazyEagle (赞：2)

吐槽翻译一句，输出的应是父结点的值，而不是编号。

我来给大家伙整个活。

可以想到的是暴力构建一棵朴素的二叉搜索树。但是一个升序或降序的数列就可以使二叉搜索树退化成长链而慢到飞起。

人们在应用二叉搜索树的时候，发现了它的效率问题，于是发明了各种平衡树来保证树高为 $\log{n}$ 左右。很常见的一种方式是旋转，而旋转操作是可逆的。所以，可以先建立一棵用旋转操作保证时间复杂度的平衡树，然后再一步步倒着转回来。

代码里使用的是 Splay。

```cpp
#include<iostream>
using namespace std;
int oplist[3000006],ocnt;//记录需要rotate的结点 
class Splay
{
public:
	struct Node{int son[2]={0,0},v=0,f=0;}t[100005];
	int rt=0,cnt=0;
	int gt(int s){return t[t[s].f].son[1]==s;}
	void rotate(int p,bool add=true)
	{
		int f=t[p].f,ch=gt(p);
		if(add)oplist[++ocnt]=f;
		if(t[f].f)
			t[t[f].f].son[gt(f)]=p;
		t[p].f=t[f].f;
		t[f].son[ch]=t[p].son[ch^1];
		if(t[p].son[ch^1])
			t[t[p].son[ch^1]].f=f;
		t[p].son[ch^1]=f;
		t[f].f=p;
	}
	void splay(int p)
	{
		for(int f=t[p].f;f!=0;)
		{
			if(t[f].f)rotate(gt(f)==gt(p)?f:p);
			rotate(p);
			f=t[p].f;
		}
		rt=p;
	}
	void insert(int v)
	{
		int p=rt,f=0;
		while(true)
		{
			if(!p)
			{
				p=++cnt;
				t[p].f=f;
				t[p].v=v;
				if(f)t[f].son[t[f].v<v]=p;
				splay(p);
				return;
			}
			f=p;
			if(v>t[p].v)
				p=t[p].son[1];
			else
				p=t[p].son[0];
		}
	}
}tree;//Splay,只要插入操作即可 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1,a;i<=n;++i)
	{
		cin>>a;
		tree.insert(a);
	}
	while(ocnt)//倒序操作回来 
	{
		tree.rotate(oplist[ocnt],false);
		--ocnt;
	}
	for(int i=2;i<=n;++i)
		cout<<tree.t[tree.t[i].f].v<<' ';
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface

~~范浩强太强了！~~

# problem

[题目传送门](/problem/CF675D)

题面真的坑，再说一下：

给你一个序列，按如下规则构建二叉搜索树：

1. **根节点**为 $1$。

2. 从 $2$ 到 $n$ 依次插入到二叉搜索树中。

求每个结点的父结点的**值**。

# solution

这道题暴力构建肯定不行，不如找找规律：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675D/a69a26d019b1bf51600e9935b0aa85fc4fdf5e99.png)

插入 $2$：父结点为 $4$。

插入 $3$：父结点为 $2$。

插入 $1$：父结点为 $2$。

插入 $6$：父结点为 $4$。

发现了吗？每个结点的父结点都是**前驱**或者**后继**，但怎么判断父结点是前者还是后者呢？

注意，在每个结点插入前，它的前驱的后继必它的后继，它的后继的前驱必为它的前驱，不难吧（~~就是绕口~~）。

所以，每个结点的前驱和后继在二叉搜索树必然相邻！

接下来就简单了，看一下前驱是后继的父结点还是后继是前驱的父结点就行了，因为结点只能插在深度更深的下面。什么？你还不会判断谁更深！因为先插入二叉搜索树的已经板上钉钉了，它不可能变化，所以只能后插入的更深，所以看前驱后插入还是后继后插入就行了。

求前驱和后继可以使用强大的 Fhq-Treap，这题做完了。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, ans[100005];
vector<pair<int, int> > v;
struct fhqtreap {
  struct node {
    int ch[2], val, pri, sz, cnt;
    node() { ch[0] = ch[1] = pri = sz = cnt = 0; }
    node(int x) {
      val = x;
      pri = rand();
      sz = cnt = 1;
      ch[0] = ch[1] = 0;
    }
  } tr[1000005];
  int root, tot;
  fhqtreap() {
    root = 0;
    tot = 0;
    srand(time(0));
    insert(LONG_LONG_MIN);
    insert(LONG_LONG_MAX);
  }
  void change(int x) { tr[x].sz = tr[tr[x].ch[0]].sz + tr[tr[x].ch[1]].sz + tr[x].cnt; }
  void split(int x, int k, int &l, int &r) {
    if (!x) {
      l = r = 0;
      return;
    }
    if (tr[x].val <= k) {
      l = x;
      split(tr[x].ch[1], k, tr[l].ch[1], r);
      change(l);
    } else {
      r = x;
      split(tr[x].ch[0], k, l, tr[r].ch[0]);
      change(r);
    }
  }
  int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tr[x].pri > tr[y].pri) {
      tr[x].ch[1] = merge(tr[x].ch[1], y);
      change(x);
      return x;
    } else {
      tr[y].ch[0] = merge(x, tr[y].ch[0]);
      change(y);
      return y;
    }
  }
  void insert(int val) {
    int x, y, z;
    split(root, val - 1, x, y);
    split(y, val, y, z);
    if (y) {
      tr[y].cnt++;
      change(y);
    } else {
      y = ++tot;
      tr[y] = node(val);
    }
    root = merge(x, merge(y, z));
  }// 插入
  int query_pre(int val) {
    int x, y;
    split(root, val - 1, x, y);
    int pos = x;
    while (tr[pos].ch[1]) pos = tr[pos].ch[1];
    root = merge(x, y);
    return pos;
  }// 求前驱
  int query_suf(int val) {
    int x, y;
    split(root, val, x, y);
    int pos = y;
    while (tr[pos].ch[0]) pos = tr[pos].ch[0];
    root = merge(x, y);
    return pos;
  }// 求后继
} tree;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> x;
  tree.insert(x);
  for (int i = 2; i <= n; i++) {
    cin >> x;
    cout << tree.tr[max(tree.query_pre(x), tree.query_suf(x))].val << ' ';
    tree.insert(x);
  }
  return 0;
}
```

---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF675D)

首先我们看一下样例：

> 4 2 3 1 6

![](https://cdn.luogu.com.cn/upload/image_hosting/v15sc12g.png)

我们现在来看一下所有节点的前驱，后继，与父节点：

| 节点（按顺序） | 前驱 | 后继 | 父节点 |
|:-:|:-:|:-:|:-:|
| $4$ | $-inf$ | $inf$ | $Null$ |
| $2$ | $-inf$ | $4$ | $4$ |
| $3$ | $2$ | $4$ | $2$ |
| $1$ | $-inf$ | $2$ | $2$ |
| $6$ | $4$ | $inf$ | $4$ |

我们发现每个节点的父节点是前驱与后继中编号较大的（较后加入的），如果前驱或后继是 $inf$ 与 $-inf$，它的父节点就是不为 $inf$ 与 $-inf$ 的那个节点，主意根节点没有父节点（我们可以先直接插入根节点）。

为什么呢？因为一个二叉排序树的中序遍历一定是从小到大的，如样例的中序遍历为：

> 1 2 3 4 6

假设有一个节点 $v$，由于中序遍历是根据左-根-右的顺序遍历的，那么就一定是这个节点的前驱与后继中的一个，那一定是与 $v$ 插入顺序相近的一个。

考虑到这里，我们可以用平衡树来解决它，那么每次的父节点的求法如下：

```cpp
int Query (int value) {

    int pre = Find(_root, GetPre(_root, value));
    int next = Find(_root, GetNext(_root, value));

    if (pre == -2147483648) {
        return next;
    }

    if (next == 2147483647) {
        return pre;
    }

    if (_valueArray[pre]._index < _valueArray[next]._index) {
        return _valueArray[next]._value;
    }
    
    return _valueArray[pre]._value;

}
```

别忘了开头需要插入根节点：

```cpp
Insert(_root, 1, value);
```


### Code：

[代码](https://www.luogu.com.cn/paste/7h80oet9)


---

## 作者：Xeqwq (赞：1)

### FHQ-Treap 题解  
手动推一下原理吧。  
可以把每次插入节点的过程想成一个节点从树的顶端滑到所在位置。  
所以它的父节点必定是它插入的时候树上有的前驱或者后继。  
设现在要插入 $x$，此时在树上有 $x$ 的前驱 $pre$ 和后继 $nxt$，则此时 $pre$ 的后继为 $nxt$, $nxt$ 的前驱为 $pre$。  
若 $pre$ 比 $nxt$ 先插入到树上，则 $nxt$ 是 $pre$ 的右孩子。再沿着它们中间向下面插入 $x$，则会把 $x$ 作为 $nxt$ 的右孩子插入到树上。  
若 $pre$ 比 $nxt$ 后插入到树上，则相反。  

---

因此我们大概就能想出来这道题的思路：记录下来每个点插入的时间，每次插入点之前先求出它的前驱和后继，然后判断哪个的插入时间更靠后，答案就是哪个点了。  
显然这个过程可以用平衡树维护。  
附：FHQ-Treap 代码实现：  
```cpp
#include <iostream>
#include <utility>
#include <ctime>
#include <cstdlib>
using namespace std;
const int Maxn=1000005,inf=2147483647;//当时Maxn1e5+5的时候RE了，怒改1e6+5AC
int n,m,cnt,root;
int val[Maxn],ch[2][Maxn],rd[Maxn],siz[Maxn];
inline void pushup(int p)
{
	siz[p]=siz[ch[0][p]]+siz[ch[1][p]]+1;
}
pair<int,int> split(int p,int k)
{
	if(!p) return make_pair(0,0);
	if(val[p]<k)
	{
		pair<int,int> t=split(ch[1][p],k);
		ch[1][p]=t.first;
		pushup(p);
		return make_pair(p,t.second);
	}
	else
	{
		pair<int,int> t=split(ch[0][p],k);
		ch[0][p]=t.second;
		pushup(p);
		return make_pair(t.first,p);
	}
}
int merge(int p,int q)
{
	if(!p||!q) return p+q;
	if(rd[p]<rd[q])
	{
		ch[1][p]=merge(ch[1][p],q);
		pushup(p);
		return p;
	}
	else
	{
		ch[0][q]=merge(p,ch[0][q]);
		pushup(q);
		return q;
	}
}
void ins(int k)
{
	pair<int,int> t=split(root,k);
	val[++cnt]=k;rd[cnt]=rand();siz[cnt]=1;
	root=merge(merge(t.first,cnt),t.second);
}
int findrank(int k)
{
	pair<int,int> t=split(root,k);
	int ret=siz[t.first]+1;
	root=merge(t.first,t.second);
	return ret; 
}
int findnum(int p,int rk)
{
	if(rk==siz[ch[0][p]]+1) return p;
	if(rk<=siz[ch[0][p]]) return findnum(ch[0][p],rk);
	return findnum(ch[1][p],rk-siz[ch[0][p]]-1);
}
int pre(int k){return findnum(root,findrank(k)-1);}
int nxt(int k){return findnum(root,findrank(k+1));}
int main()
{
	srand(time(0));
	ins(inf);ins(-inf);
	int x;
	cin>>n>>x;
	ins(x);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		printf("%d ",val[max(nxt(x),pre(x))]);
		ins(x);
	}
}
```

---

## 作者：da32s1da (赞：1)

很明显一个点的父亲一定是**比它大的最小的数**和**比它小的最大的数**中较后出现的数字，于是**Splay**可以解决这个任务！
```
#include<cstdio>
const int N=1e5+50;
const int inf=2e9+7;
struct spaly{
	int siz[N],val[N],cnt[N],ch[N][2],fa[N];
	int tot,rot;
	void update(int x){
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];
	}
	void rotate(int x){
		int y=fa[x],z=fa[fa[x]],opt=(ch[fa[x]][1]==x);
		ch[z][ch[z][1]==y]=x;
		fa[x]=z;
		ch[y][opt]=ch[x][opt^1];
		fa[ch[x][opt^1]]=y;
		ch[x][opt^1]=y;
		fa[y]=x;
		update(y);update(x);
	}
	void splay(int x,int Aim){
		while(fa[x]!=Aim){
			int y=fa[x],z=fa[fa[x]];
			if(z!=Aim)
			((ch[y][0]==x)^(ch[z][0]==y))?rotate(x):rotate(y);
			rotate(x);
		}
		if(!Aim)rot=x;
	}
	void insert(int x){
		int u=rot,v=0;
		while(u&&x!=val[u]){
			v=u;
			u=ch[u][x>val[u]];
		}
		if(u)++cnt[u];
		else{
			u=++tot;
			if(v)ch[v][x>val[v]]=u;
			fa[u]=v;
			ch[u][0]=ch[u][1]=0;
			siz[u]=cnt[u]=1;
			val[u]=x;
		}
		splay(u,0);
	}
	void find(int x){
		if(!rot)return;
		int u=rot;
		while(x!=val[u]&&ch[u][x>val[u]])
		u=ch[u][x>val[u]];
		splay(u,0);
	}
	int Next(int x,int op){
		find(x);
		if(val[rot]>x&&op)return rot;
		if(val[rot]<x&&!op)return rot;
		int u=ch[rot][op];
		while(ch[u][op^1])u=ch[u][op^1];
		return u;
	}
}s;
inline int max(int u,int v){return u>v?u:v;}
int main(){
	int n,x;
	s.insert(inf);
	s.insert(-inf);//插入两个极大值点
	scanf("%d%d",&n,&x);
	s.insert(x);//插入第一个数
	for(int i=1;i<n;i++){
		scanf("%d",&x);
		printf("%d ",s.val[max(s.Next(x,0),s.Next(x,1))]);
        //查询前驱和后继中编号大的并输出
		s.insert(x);//别忘了插入
	}
}
```

---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF675D)

这道题目考察了二叉搜索树的性质，每个之前未被插入的节点在插入的父亲只会是已插入的节点中权值第一个比它小的或者第一个比它大的。

考虑用平衡树维护序列权值，查询需求为前驱后继，无删除操作。为了节省代码，本人用无旋的 Treap。

整个操作时间复杂度为 $O(n \log n)$。

代码如下：


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<int, int>
#define ll long long
#define vi vector<int>
using namespace std;

const int N = 1e5 + 10;
#define ls (tr[p].L)
#define rs (tr[p].R)
struct FHQ {
	int L, R, rd, sz, val;
}tr[N];

int rt, n, tot; mt19937 wxy(1314);

map<int, int> l, r;

void push(int p) {	tr[p].sz = tr[ls].sz + tr[rs].sz + 1; }

void spl(int p, int v, int &x, int &y) {
	if(!p) return x=y=0, void();
	if(tr[p].val <= v) spl(rs, v, tr[x=p].R, y);
	else spl(ls, v, x, tr[y=p].L);
	push(p);
}

int mer(int x, int y) {
	if(!x || !y) return x|y;
	if(tr[x].rd > tr[y].rd) return tr[x].R = mer(tr[x].R, y), push(x), x;
	else return tr[y].L = mer(x, tr[y].L), push(y), y;
}

int xj(int v) {
	tr[++tot] = {0, 0, (int)wxy(), 1, v};
	return tot;
}

void ins(int v) {
	int x=0, y=0;
	spl(rt, v-1, x, y);
	rt = mer(mer(x, xj(v)), y);
}

int pre(int x) {
	int p = rt, ans = 0;
	while(1) {
		if(!p) return ans;
		if(tr[p].val >= x) p = ls;
		else ans = tr[p].val, p = rs;
	}
}

int suc(int x) {
	int p = rt, ans = INT_MAX;
	while(1) {
		if(!p) return ans;
		if(tr[p].val <= x) p = rs;
		else ans = tr[p].val, p = ls;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	L(i, 1, n) {
		int x; cin >> x;
		if(i > 1) {
			int pr = pre(x);
			int sc = suc(x);
//			cout << pr << ' ' << sc << '\n';
			if(pr != 0) {
				if(r[pr] == 0) {
					r[pr] = x;
					cout << pr << ' ';
				}
			}
			if(r[pr] != x) 
			  l[sc] = x, cout << sc << ' ';
		}
		ins(x);
	}
	return 0;
}

```

---

## 作者：Wilderness_ (赞：0)

看到题目名称 Tree Construction 就知道它和树形数据结构有非常大的关系。看题面翻译后发现是 BST（即 [二叉搜索树 Binary Search Tree](https://oi-wiki.org/ds/bst/)），直接使用 FHQ Treap 过了这道题。

注：FHQ Treap 的写法见 [FHQ treap](https://oi-wiki.org/ds/treap/#%E6%97%A0%E6%97%8B-treap)。

FHQ Treap 支持查找前驱和后驱的操作，而一个节点的父亲节点不是其前驱就是其后驱。

对于求 $x$ 的前驱操作，我们可以将这一棵树先分裂成值域在 $[1,x-1]$ 和 $[x,n]$ 两棵树，然后在左树（即值域在 $[1,x-1]$ 的树）上找最大值，就是 $x$ 的前驱。

对于求 $x$ 的后驱操作，我们可以将这一棵树先分裂成值域在 $[1,x]$ 和 $[x+1,n]$ 两棵树，然后找到左树最大值（即 $x$），然后找到其后一位，就是 $x$ 的后驱。

我们只需要前驱和后驱哪一个插入时间的更靠后，答案就是那个位置上的值。

### code
```
#include<bits/stdc++.h>
#define ll long long
#define INF 2147483647
using namespace std;
ll tot,rt,n;
struct node
{
    ll v,size,key,l,r;
}p[1145141];
void combine(ll k)
{
    p[k].size=p[p[k].l].size+p[p[k].r].size+1;
}
ll new_node(ll val)
{
    p[++tot].v=val;
	p[tot].key=rand()*rand()%INF+1;
    p[tot].l=p[tot].r=0;
	p[tot].size=1;
    return tot;
}
void split(ll k,ll val,ll &l,ll &r)
{
    if(!k){l=r=0;return;}
    if(p[k].v<val)
	{
		split(p[k].r,val,p[k].r,r);
		combine(k);
		l=k;
    }
    else
	{
        split(p[k].l,val,l,p[k].l);
        combine(k);
		r=k;
    }
}
ll merge(ll l,ll r)
{
    if(!l||!r)return l+r;
    if(p[l].key<p[r].key)
	{
        p[l].r=merge(p[l].r,r);
        combine(l);
        return l;
    }
    else
	{
        p[r].l=merge(l,p[r].l);
        combine(r);
        return r;
    }
}
void insert(ll val)
{
    ll l,r;
    split(rt,val,l,r);
    rt=merge(merge(l,new_node(val)),r);
}
ll find_r(ll val)
{
    ll x,y,ans;
    split(rt,val,x,y);
    ans=p[x].size+1;
    rt=merge(x,y);
    return ans;
}
ll find_v(ll tmp,ll k)
{
	if(tmp==p[p[k].l].size+1) return k;
	if(tmp<=p[p[k].l].size) return find_v(tmp,p[k].l);
	return find_v(tmp-p[p[k].l].size-1,p[k].r);
}
ll find_pre(ll val)
{
	return find_v(find_r(val)-1,rt);
}
ll find_nxt(ll val)
{
	return find_v(find_r(val+1),rt);
}
int main()
{
	srand(time(0));
	insert(INF);insert(-INF);
	ll x;
    scanf("%lld%lld",&n,&x);
	insert(x);
	for(ll i=2;i<=n;i++)
	{
		scanf("%lld",&x);
		printf("%lld\n",p[max(find_pre(x),find_nxt(x))].v);
    	insert(x);
	}
    return 0;
}
```

---

