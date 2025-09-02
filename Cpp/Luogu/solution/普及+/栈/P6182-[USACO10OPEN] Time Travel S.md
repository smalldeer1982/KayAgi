# [USACO10OPEN] Time Travel S

## 题目描述

Farmer John 买了台时光机，这使得他可以方便地管理自己的奶牛群。

他现在有 $N$ 个操作（$1 \leq N \leq 8 \times 10^4$），每次操作仅可能是如下三种之一：

1. `a x`：添加一头编号为 $x$ 的奶牛（$1 \leq x \leq 10^6$）。
2. `s`：卖掉最近添加的奶牛（保证此时至少有一头奶牛）。
3. `t x`：回到**第 $x$ 次操作前**的状态（保证第 $x$ 次操作存在）。

你需要在 FJ 执行每次操作后输出他拥有的最新的奶牛的编号。特别地，如果没有奶牛，输出 $-1$。

## 说明/提示

下面是样例解释，其中拥有的奶牛已经按添加顺序排好。

| 操作编号 | 操作  | 拥有的奶牛 | 输出 |
| -------- | ----- | ---------- | ---- |
| 1        | `a 5` | 5          | 5    |
| 2        | `a 3` | 5,3        | 3    |
| 3        | `a 7` | 5,3,7      | 7    |
| 4        | `s`   | 5,3        | 3    |
| 5        | `t 2` | 5          | 5    |
| 6        | `a 2` | 5,2        | 2    |
| 7        | `t 4` | 5,3,7      | 7    |
| 8        | `a 4` | 5,3,7,4    | 4    |
| 9        | `s`   | 5,3,7      | 7    |
| 10       | `t 7` | 5,2        | 2    |
| 11       | `s`   | 5          | 5    |
| 12       | `s`   | /          | -1   |

## 样例 #1

### 输入

```
12
a 5
a 3
a 7
s
t 2
a 2
t 4
a 4
s
t 7
s
s```

### 输出

```
5
3
7
3
5
2
7
4
7
2
5
-1```

# 题解

## 作者：RuntimeErr (赞：33)

这道题的标签是可持久化和栈，那我们就拿他们的思想来解这道题吧 QAQ 。

# 前置数组

- $num(i)$： 表示添加的第 $i$ 个奶牛编号。

- $t(i)$：表示第 $i$ 次操作最新的奶牛在 $num$ 数组中的位置（即 $top$ 值）。

- $pre(i)$：表示在 $num$ 数组中位置为 $i$ 的奶牛在其所对应的操作里前一个奶牛的位置（为 $s$ 操作服务）。

# 逐步解析

### 添加操作：

这个十分容易理解，用 $top$ 记录新增的奶牛位置，$t(i)$ 即为 $top$ ，$pre(i)$ 即为上一次操作的 $top$ 值。

代码段如下：

```cpp
if(ch=='a'){                 
    scanf("%d",&x);
    num[++top]=x;
    t[i]=top;pre[t[i]]=t[i-1];
}
```

### 跳转操作：

这里需要注意了，题目描述里面说的是回到第 $x$ 次操作 __前__ 的状态，即第 $x-1$ 次操作的结束状态。我们只需将第 $x-1$ 次操作的状态复制到当前即可。

代码段如下：

```cpp
if(ch=='t'){
    scanf("%d",&x);
    t[i]=t[x-1];
    //pre[t[i]]=pre[t[x-1]];（这一段等价直接省略）
}
```

### 删除操作：

这个操作非常简单 ~~（但因为想错重构了不下亿次）~~ ，$pre$ 数组的作用就来了。我们只需将上一次操作的最新奶牛的前一个奶牛的位置复制到当前即可。

代码段如下：

```cpp
if(ch=='s'){
  t[i]=pre[t[i-1]];
  //pre[t[i]]=pre[pre[t[i-1]]];（这一段也等价，可直接省略）
}
```

20行代码AC！

全段如下：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=8e4+10;
int n,num[N],t[N],pre[N],top;
int main(){
    scanf("%d",&n);
    char ch;int x;
    for(int i=1;i<=n;i++){
        scanf(" %c",&ch);
        if(ch=='a'){ 
          scanf("%d",&x);num[++top]=x;
            t[i]=top;pre[t[i]]=t[i-1];
        }else if(ch=='t'){
            scanf("%d",&x);t[i]=t[x-1];
        }else t[i]=pre[t[i-1]];
        printf("%d\n",t[i]?num[t[i]]:-1);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：11)

一开始我直接暴力栈，结果优秀的 _substack2_ 优秀爆了！

很明显，对于暴力存储每一个状态，空间是不够的。

##### 注意这题属于可持久化 ~~（虽然本蒟蒻不太会可持久）~~



------------


想一下，我们不能记录每一个状态，就要尝试动态更新一个状态。对于操作 _t_ 我们需要**回溯到之前的状态**，这是什么，这不是**树**吗！

于是就想到了我们可以维护一个树形结构，_t_ 操作就是将要回溯的点多连出一条边。可是怎么回溯呢？

对于 _add_ 操作，我们很自然地想到回溯到上一个点后 _pop_ 掉栈顶元素。对于 _s_ 操作，我们记录一个临时变量 _tmp_ 储存卖掉的牛的编号。回溯的时候，将记录的编号再插入栈中即可。

剩下，就只要深搜一下了，再记录一个当前的状态。于是，我考试时爆了的题就 _a_ 了。

参考代码如下：

```
#include <bits/stdc++.h>
using namespace std;

int n, x[80005], p[80005], ans[80005];
char o[80005] = {0};
vector<int> e[80005];
stack<int> s;

void srh(int k){
	int tmp;
	//更新 
	if (o[k] == 'a'){
		s.push(x[k]);
	}
	if (o[k] == 's'){
		tmp = s.top(), s.pop();
	}
	//输出与搜索 
	if (k != 0){
		ans[k] = (s.empty() ? -1 : s.top());
	}
	for (int i = 0; i < e[k].size(); i++){
		srh(e[k][i]);
	}
	//还原 
	if (o[k] == 'a'){
		s.pop();
	}
	if (o[k] == 's'){
		s.push(tmp);
	}
}

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> o[i];
		if (o[i] != 's'){
			cin >> x[i];
		}
		e[(o[i] == 't') ? x[i] - 1 : i - 1].push_back(i);
	}
	srh(0);
	for (int i = 1; i <= n; i++){
		cout << ans[i] << endl; 
	}
	return 0;
}
```


---

## 作者：JK_LOVER (赞：7)

## 题意
维护一个可持久的栈。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6182)
## 分析
如何可持久化，这显然得用可持久化数组。每次更改都只会更改 $\log n$ 个节点。那么栈和数组的实现没有任何区别，那么我们只需要记录一下栈的大小，那么就可以直接模拟，时间复杂度为 $O(n\log n)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1001100;
int read(){
	int x;scanf("%d",&x);return x;
}
int lc[N],rc[N],top[N],rt[N],val[N],n,size = 0;
int update(int u,int l,int r,int pos,int key)
{
	int p = ++size;
	lc[p] = lc[u];rc[p] = rc[u];
	if(l == r) {val[p] = key;return p;}
	int mid = l + r >> 1;
	if(pos <= mid) lc[p] = update(lc[u],l,mid,pos,key);
	else rc[p] = update(rc[u],mid+1,r,pos,key);
	return p;
}
int ask(int u,int l,int r,int pos)
{
	if(l == r) {return val[u];}
	int mid = l + r >> 1;
	if(pos <= mid) return ask(lc[u],l,mid,pos);
	else return ask(rc[u],mid+1,r,pos);
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i++)
	{
		char ch[5];
		scanf("%s",ch);
		
		if(ch[0] == 'a')
		{
			int x = read();
			top[i] = top[i-1] + 1;
			rt[i] = update(rt[i-1],1,n,top[i],x);
		}
		if(ch[0] == 's')
		{	
			top[i] = top[i-1];
			rt[i] = rt[i-1];
//			cout<<"top[i] "<<top[i]<<endl;
			rt[i] = update(rt[i-1],1,n,top[i],0);
			top[i]--;

			
		}
		if(ch[0] == 't')
		{
			int x = read();
			rt[i] = rt[x-1];top[i] = top[x-1];
		}
		printf("%d\n",top[i] == 0?-1:ask(rt[i],1,n,top[i]));
	}
}
```


---

## 作者：Alarm5854 (赞：5)

推销一下我的新博客（但图片可能显示不了）：https://yce3216037.github.io/post/luo-gu-p6182-ti-jie/

本人想看一下洛谷新增的题目，结果就被我切了，而且是本题首A。如果这一道题只有前两个操作，那么这道题目就是一道很水的模拟题，直接用栈就可以了。然而，有了第三个操作，那么就有点难了，这个我称它为“可持久化栈”。有一种朴素的做法，就是在前两个操作的时候，直接复制上一次的栈的结果，遇到第三种操作，就复制第 $x-1$ 次操作的结果，因为说的是第 $x$ 次操作前，而不是第 $x$ 次操作后，这样，样例模拟如下（为了方便，一开始来一个编号为 $-1$ 的奶牛）：
```
0 ：-1
1 ：-1 5
2 ：-1 5 3
3 ：-1 5 3 7
4 ：-1 5 3
5 ：-1 5
6 ：-1 5 2
7 ：-1 5 3 7
8 ：-1 5 3 7 4
9 ：-1 5 3 7
10：-1 5 2
11：-1 5
12：-1
```
但是，这样操作的时间复杂度为 $O(n^2)$，空间复杂度也为 $O(n^2)$，对于 $n\le 8\times 10^4$ 的数据来说，不管从时间还是从空间上来说，都会炸，所以，需要有一个更优的方法。这就要用到我新创的“可持久化栈”了。

如何实现这个“可持久化栈”呢？我画一个图来模拟一下（图略丑，且有点多，见谅），由于我是先画完再截图的，所以会有多余的线段：

初始状态（这时候为了减少边界条件判断，还需要再加一个虚拟奶牛，编号任意）：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ot01my7n.png)  
第1步，插入5号奶牛，直接在上一次的操作后添加一头5号奶牛即可：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ffzn8xsd.png)  
第2步，插入3号奶牛，和第1步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/m4fro19g.png)  
第3步，插入7号奶牛，和第1步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/bgbelfzn.png)  
第4步，去掉7号奶牛，将在上一次操作的倒数第二头奶牛加在该奶牛的前一个奶牛后面，这样即可去掉最后一头奶牛：  
![](https://cdn.luogu.com.cn/upload/image_hosting/m860k1tu.png)  
第5步，回到第4次操作前，将第2次操作后的队尾的奶牛加在该奶牛的前一个奶牛后面，即可忽略2至4步：  
![](https://cdn.luogu.com.cn/upload/image_hosting/4modz3tq.png)  
第6步，插入2号奶牛，和第1步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/cf1qgdta.png)  
第7步，回到第4次操作前，和第5步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/2tkhpdi3.png)  
第8步，插入4号奶牛，和第1步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/z9bnor14.png)  
第9步，去掉4号奶牛，和第4步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/kgoq0fb9.png)  
第10步，回到第7次操作前，和第5步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/42lyi87t.png)  
第11步，去掉2号奶牛，和第4步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/kd0dj7gt.png)  
第12步，去掉5号奶牛，和第4步类似：  
![](https://cdn.luogu.com.cn/upload/image_hosting/its7pw3n.png)  
由于我想~~给大家介绍一下指针版如何实现~~装X，我写一个指针版的。
### 代码如下：
```cpp
#include<cstdio>
using namespace std;
const int N = 80000 + 10;
FILE *fin, *fout;
inline int read(int &x) {//快读
	char c = 0; int f = x = 0;
	while (c < 48 || c > 57) {
		if (c == -1) return 0;
		if (c == '-') f = 1; c = fgetc(fin);
	}
	while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = fgetc(fin);
	if (f) x = -x; return 1;
}
inline int read(char &c) {
	c = 0; while (c == 32 || c == 10 || c == 13 || c == 0) c = fgetc(fin);
	if (c == -1) return 0; return 1;
}
inline int write(int x) {//快写
	if (x < 0) return fputc(45, fout), write(-x);
	if (x > 9) write(x / 10);
	return fputc((x % 10) | 48, fout), 1;
}
inline int write(char c) {
	return fputc(c, fout), 1;
}
template<class T, class... Args> inline int write(T x, Args... args) {
	return write(x) + write(args...);
}
struct node;
typedef node* list;//接下来写起来方便
struct node {
	int val; list last;//val为奶牛的编号，last为上一头奶牛的位置
	node(int val = 0, list last = 0): val(val), last(last){}//构造函数
};
char opt;
int n, x;
list a[N];
int main() {
	#ifdef ONLINE_JUDGE
	fin = stdin;
	fout = stdout;
	#else
	fin = fopen("P6182.in", "rb");
	fout = fopen("P6182.out", "wb");
	#endif
	a[0] = new node(3216037), a[read(n)] = new node(-1, a[0]), ++n;//a[0]甚至可以用1******7代替，read(n)的返回值为1，这里简写
	for (int i = 2; i <= n; ++i) {//为了方便操作，将n加1，并且i从2开始
		read(opt);
		if (opt == 's') a[i] = new node(a[i - 1]->last->val, a[i - 1]->last->last);//删除
		else {
			read(x); if (opt == 'a') a[i] = new node(x, a[i - 1]);//插入
			else a[i] = new node(a[x]->val, a[x]->last);//可持久化
		}
		write(a[i]->val, '\n');
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：4)

# 【可持久化栈】P6182 Time Travel

## Description

- 给定一个栈，要求支持插入删除和回到某个历史版本。
- 操作次数少于 $10^5$。

## Solution

~~再不写题解贡献分就掉没了~~。

可持久化栈的裸题，注意到栈可以通过一个数组和一个记录栈深度的变量来实现，因此只需要对维护栈的数组进行可持久化，然后单独记录每次操作后的栈深度即可。

然后就变成了[这道题](https://www.luogu.com.cn/problem/P3919)。

## Code

```cpp
const int maxn = 100005;

struct Node {
  int l, r, v;
  Node *ls, *rs;

  Node(const int L, const int R) : l(L), r(R), v(0) {
    if (L == R) {
      ls = rs = nullptr;
    } else {
      int M = (L + R) >> 1;
      ls = new Node(L, M);
      rs = new Node(M + 1, R);
    }
  }

  Node(Node *const pre, const int p, const int x) {
    *this = *pre;
    if (l == r) {
      v = x;
    } else {
      int m = (l + r) >> 1;
      if (p <= m) {
        ls = new Node(pre->ls, p, x);
      } else {
        rs = new Node(pre->rs, p, x);
      }
    }
  }

  int query(const int p) {
    auto u = this;
    for (int m = (u->l + u->r) >> 1; u->l != u->r; m = (u->l + u->r) >> 1) {
      if (p <= m) {
        u = u->ls;
      } else {
        u = u->rs;
      }
    }
    return u->v;
  }
};
Node *rot[maxn];

int n;
int top[maxn];

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  rot[0] = new Node(1, n);
  for (int x, y, i = 1, di = 0; i <= n; di = i++) {
    do x = IPT::GetChar(); while (!isalpha(x));
    if (x == 'a') {
      y = 0; qr(y);
      rot[i] = new Node(rot[di], top[i] = top[di] + 1, y);
    } else {
      if (x == 's') {
        y = di;
      } else {
        y = 0; qr(y);
        --y;
      }
      rot[i] = rot[y];
      top[i] = top[y] - (x == 's');
    }
    qw(top[i] ? rot[i]->query(top[i]) : -1, '\n', true);
  }
  return 0;
}
```



---

## 作者：critnos (赞：3)

既然 YCE3216037 神仙都发了题解那我也来发一篇吧。

首先这道题肯定可以用主席树/可持久化平衡树做（反正是可持久化数组是吧）。

但是我不想打怎么办啊。

当然是 STL 辣——rope。

这个数据结构神仙无比，可以 $\log n$ 支持大部分的 vector 操作。

最神奇的是——它可以支持可持久化！

就是 $O(1)$ copy 数组。

基于可持久化平衡树实现的。

然后就没什么难的咯，不知道 YCE 会不会来卡。

```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
rope<int> *a[80005];
int main()
{
	a[0]=new rope<int>(-1);
	int m,i,x;
	char opt[5];
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		a[i]=new rope<int>(*a[i-1]);
		scanf("%s",opt);
		if(opt[0]!='s') scanf("%d",&x);
		else a[i]->pop_back();
		if(opt[0]=='a') a[i]->push_back(x);
		if(opt[0]=='t') a[i]=a[x-1];
		printf("%d\n",a[i]->at(a[i]->size()-1));
	}
}
```
~~22 行切可持久化，舒服~~

---

## 作者：qzhwmjb (赞：3)

### 思路
---
模拟栈顶及所有点。  
思路图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/l05ngxlu.png)  
模拟图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/cicemx50.png)  
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,k;//循环使用 
int n,x;//题目内变量 
/*
if(c为'a'){
	压入
	前驱为i-1 
} else if (c为's') {
	卖栈顶
	输出当前栈顶 
} else {
	回溯至第x-i个 
}
*/ 
int a[80005],s[80005];
//a数组用于记录x,及对哪只奶牛执行操作 
//s数组类似于指针，指向前一个状态 
char c;
//题目内变量 
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n; 
	for(i=1;i<=n;i++){
  		cin>>c;
		if(c=='a'){
  			cin>>x;
  			a[i]=x;
 			//记录，下同  
			s[i]=i-1;
		}else if(c=='s'){
  			a[i]=a[s[i-1]];
  			// s返回一步
			// 指向位置减一 
			s[i]=s[s[i-1]];
		}else if(c=='t'){
  			cin>>x;
  			//第 xx 次操作前，前《--注意
			//假设输入2 
			//执行的是编号1的状态 
			a[i]=a[x-1];
			s[i]=s[x-1];
		}
		//如果奶牛还有 
		if(a[i]!=0){
  			cout<<a[i]<<endl;
		}else{
		  	cout<<"-1"<<endl;
		}
	} 
 	return 0;
}
/*
12 
a 5 
a 3 
a 7 
s 
t 2 
a 2 
t 4 
a 4 
s 
t 7 
s 
s  
*/ 
```

```cpp
2020/11/4 @qzhwlzy 友情提醒并加以修改 
2020/11/4 @qzhwlzy 友情提醒并加以修改 (不同处）
```


---

## 作者：L2_sheep (赞：2)

可以想到这是一个树形结构。不妨用并查集来维护（保存每次操作的父节点和权值），模拟一下即可。

```cpp


int main()
{		
	
	
	scanf("%d", &n);
	a[0] = -1, f[0] = 0, p = 0;
	for(i = 1; i <= n; i++){
		scanf("%s", o);
		if(o[0] == 'a'){
			scanf("%d", &x);
			a[i] = x;
			f[i] = p;
			printf("%d\n", x);
		}
		else if(o[0] == 's'){
			fp = f[p];
			printf("%d\n", a[fp]);
			p = f[fp];
			f[i] = p;
			a[i] = a[fp];
		}
		else{
			scanf("%d", &x);
			printf("%d\n", a[--x]);
			f[i] = f[x];
			a[i] = a[x];
		}
		p = i;
	}
			
	return 0;
}
```


---

## 作者：kkio (赞：0)

这道题相当于让你维护一个可持久化栈，我们可以通过建树实现。

将每个版本在树上的节点编号记下来，那么操作变成：

入栈：在当前节点上创建一个儿子，并且自己走到儿子上。

出栈：返回父亲。

返回之前版本：回到记下的节点上。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=8e4+10;
int val[maxn],fa[maxn],tot,n,now,pos[maxn];
vector<int> G[maxn];
int main()
{
	cin>>n;
	now=0;
	val[0]=-1;
	pos[0]=0;
	for(int i=1;i<=n;i++)
	{
		char c;int x;
		cin>>c;
		if(c=='a')
		{
			cin>>x;
			++tot;
			G[now].push_back(tot);
			val[tot]=x;
			fa[tot]=now;
			now=tot; 
		}
		else if(c=='s')
			now=fa[now];
		else 
		{
			cin>>x;
			now=pos[x-1];
		}
		pos[i]=now;
		printf("%d\n",val[now]);
	}
}

```


---

## 作者：xiezheyuan (赞：0)

[可能有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/p6182.html)

## 简要题意

你需要维护一个栈，有 $n$ 个操作，支持：

- 给定一个 $x$，将 $x$ 加入栈。
- 将一个元素出栈。
- 给定一个 $x$，将当前栈回退到 **第 $x$ 操作前**。

每一次操作结束后，你需要输出栈顶元素。如果当前栈是一个空栈，那么输出 $-1$。

数据保证操作合法，且 $1 \le n \le 8 \times 10^{4}$。

## 思路

据说本题存在 $O(n)$ 做法，但是我不会，这里有一个 $O(n\log n)$ 做法。

对于 **回退** 之类的字眼，我们肯定会想到可持久化，由于栈一般时用数组实现的，所以我们可以写一个可持久化数组。如果不会可持久化数组，请去做 [模板题](https://www.luogu.com.cn/problem/P3919)。

下面有一个用数组实现的栈的简要代码，对于分析很有帮助：

```cpp
int stk[114514],t;
void push(int v){
	stk[++t]=v;
}
void pop(){
	t--;
}
int top(){
	return (t==0)?(-1):(stk[t]);
}
```

我们可以考虑用可持久化数组来维护 `stk`，那么 $t$ 怎么办？我们发现，$t$ 需要是一个可持久化变量，可持久化变量不就是数组吗？于是我们直接使用数组 $T_i$ 来表示第 $i$ 次操作后栈顶指针 $t$。

整个代码时间复杂度和空间复杂度都是 $O(n\log n)$ 的（可持久化的开销）。

## 代码

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;

const int SIZE = 8e4+5;
struct{
	int l,r,v;
}t[SIZE*25];
int top;
int root[SIZE*25];
int n;

int newnode(int i){
	t[++top]=t[i];
	return top;
}

int update(int i,int l,int r,int p,int val){
	i=newnode(i);
	if(l==r){
		t[i].v=val;
		return i;
	}
	if(p<=mid){
		t[i].l=update(t[i].l,l,mid,p,val);
	}
	else{
		t[i].r=update(t[i].r,mid+1,r,p,val);
	}
	return i;
}

int query(int i,int l,int r,int p){
	if(l==r){
		return t[i].v;
	}
	if(p<=mid){
		return query(t[i].l,l,mid,p);
	}
	else{
		return query(t[i].r,mid+1,r,p);
	}
}

int stop[SIZE];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		root[i]=root[i-1];
		stop[i]=stop[i-1];
		char op;
		int x;
		cin>>op;
		if(op=='a'){
			cin>>x;
			root[i]=update(root[i-1],1,n,(++stop[i]),x);
		}
		else if(op=='s'){
			stop[i]--;
		}
		else{
			cin>>x;
			root[i]=root[x-1];
			stop[i]=stop[x-1];
		}
		if(stop[i]!=0){
			cout<<query(root[i],1,n,stop[i])<<'\n';
		}
		else{
			cout<<-1<<'\n';
		}
	}
	return 0;
}

```

跑了 $113$ 毫秒，比 $O(n)$ 的慢。

[AC Record](https://www.luogu.com.cn/record/86290107)

---

## 作者：Endt (赞：0)

# Time Travel-题解

标准做法是可持久化栈，时空均为 $O(n)$，但蒟蒻最近在练主席树，就用冗长的主席树过了这道题。

做法其它题解写得很明确了，这里给出主席树的代码。

```cpp
#include<bits/stdc++.h>

int n,a[80005];

class Node{
public:
    int l,r;
    int size;
};
class HJT{
public:
    int cnt;
    Node t[5000000];
    int rt[500005];
    int insert(int x,int L,int R,int k,int opt=1){
        int root=++cnt;
        t[root]=t[x];
        t[root].size+=opt;
        if(L==R)return root;
        int M=(L+R)/2;
        if(k<=M)t[cnt].l=insert(t[x].l,L,M,k,opt);
        else t[cnt].r=insert(t[x].r,M+1,R,k,opt);
        return root;
    }
    Node find(int x,int L,int R){
        if(L==R)return t[x];
        int M=(L+R)/2;
        if(t[t[x].r].size)return find(t[x].r,M+1,R);
        if(t[t[x].l].size)return find(t[x].l,L,M);
        return {0,0,-1};
    }
}t1,t2;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        char c;
        std::cin>>c;
        if(c=='a'){
            scanf("%d",&a[i]);
            t1.rt[i]=t1.insert(t1.rt[i-1],1,1000000,a[i]);
            t2.rt[i]=t2.insert(t2.rt[i-1],1,1000000,i,i);
        }
        if(c=='s'){
            Node to_sell=t2.find(t2.rt[i-1],1,1000000);
            t1.rt[i]=t1.insert(t1.rt[i-1],1,1000000,a[to_sell.size],-1);
            t2.rt[i]=t2.insert(t2.rt[i-1],1,1000000,to_sell.size,-to_sell.size);
        }
        if(c=='t'){
            int x;
            scanf("%d",&x);
            t1.rt[i]=t1.rt[x-1];
            t2.rt[i]=t2.rt[x-1];
        }
        Node ans=t2.find(t2.rt[i],1,1000000);
        if(ans.size<=0)printf("-1\n");
        else printf("%d\n",a[ans.size]);
    }
    return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

可持久化栈 .

首先 , 你应该学过可持久化线段树和可持久化 trie .

如果此题没有穿越操作的话 , 那么显然用栈维护 . 所以我们应发明可持久化栈 .

可持久化主要是优化空间 ( 不然开几个数组得了 ) . 

画个图理解一下 :

[![LPmtZF.md.png](https://s1.ax1x.com/2022/04/09/LPmtZF.md.png)](https://imgtu.com/i/LPmtZF)

每个时间点维护一个 $root$ , 作为栈顶 ; 每个节点维护一个 $son$ , 作为它下一个元素 .

插入时 , 应当新建一个节点 , 它的儿子是上一个 $root$ ; 删除时 , 新的 $root$ 是上一个 $root$ 的 $son$ ; 穿越的时候 , 直接复制 $root$ .

注意初始节点的编号应为 $-1$ .

代码极短 :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=8e4+10;
struct Stack {
	int id,son;
}st[MAXN];
int n,idx,root[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;st[0]={-1,0};
	ffor(i,1,n) {
		char ch;int x;cin>>ch;
		if(ch=='a') {cin>>x;root[i]=++idx,st[idx]={x,root[i-1]};}
		if(ch=='s') root[i]=st[root[i-1]].son;
		if(ch=='t') {cin>>x;root[i]=root[x-1];}
		cout<<st[root[i]].id<<'\n';
	}
	return 0;
}
```

---

