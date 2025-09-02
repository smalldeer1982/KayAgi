# [ABC294D] Bank

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc294/tasks/abc294_d

銀行に人 $ 1 $, 人 $ 2 $, $ \dots $, 人 $ N $ が並んでいます。  
 $ Q $ 個のイベントが発生します。イベントは次の $ 3 $ 種類のいずれかです。

- `1` : 受付に呼ばれていない人のうち、最も小さい番号の人が受付に呼ばれる。
- `2 x` : 人 $ x $ が初めて受付に行く。(ここで、人 $ x $ はすでに 1 回以上受付に呼ばれている。)
- `3` : すでに受付に呼ばれているが受付に行っていない人のうち、最も小さい番号の人が再度呼ばれる。
 
$ 3 $ 種類目のイベントで受付に呼ばれる人の番号を呼ばれた順に出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 2\ \leq\ Q\ \leq\ 5\ \times\ 10^5 $
- 全ての人が 1 回以上呼ばれているときに $ 1 $ 種類目のイベントが発生することはない
- $ 2 $ 種類目のイベントについて、人 $ x $ はすでに 1 回以上受付に呼ばれている
- $ 2 $ 種類目のイベントについて、人 $ x $ が 2 回以上受付に行くことはない
- 呼ばれている人が全員すでに受付に行っているときに $ 3 $ 種類目のイベントが発生することはない
- $ 3 $ 種類目のイベントは少なくとも 1 回発生する
- 入力される値はすべて整数
 
### Sample Explanation 1

$ i\ =\ 1,\ 2,\ \dots,\ Q $ について、$ i $ 番目のイベントが起こる前の時点での、受付に呼ばれたが受付に行っていない人の集合を列挙すると次のようになります。 - $ i=1 $ : $ \lbrace\ \rbrace $ - $ i=2 $ : $ \lbrace\ 1\rbrace $ - $ i=3 $ : $ \lbrace\ 1,2\rbrace $ - $ i=4 $ : $ \lbrace\ 1,2\rbrace $ - $ i=5 $ : $ \lbrace\ 2\rbrace $ - $ i=6 $ : $ \lbrace\ 2,3\rbrace $ - $ i=7 $ : $ \lbrace\ 2\rbrace $ - $ i=8 $ : $ \lbrace\ 2\rbrace $ - $ i=9 $ : $ \lbrace\ 2,4\rbrace $ - $ i=10 $ : $ \lbrace\ 4\rbrace $ $ 3 $ 種類目のイベントは $ i=3,7,10 $ のときに発生しているので、その時点での集合のうち番号が最小の人である $ 1,\ 2,\ 4 $ を出力します。

## 样例 #1

### 输入

```
4 10
1
1
3
2 1
1
2 3
3
1
2 2
3```

### 输出

```
1
2
4```

# 题解

## 作者：lottle1212 (赞：13)

# [原题传送门](https://www.luogu.com.cn/problem/AT_abc294_d)
## Part0：
先简要概述一下题意。

- 银行里有 $N$ 个人，有 $Q$ 次叫人操作。
- 操作 `1` 表示前台叫到当前未叫到的人中编号最小的人，且这个人没去前台。
- 操作 `2 x` 表示编号为 $x$（$x$ 已经被叫到过，即已被执行操作 `1`）的人去了前台。
- 操作 `3` 表示已被叫到过的人中编号最小的人再次被叫到，输出该人的编号。

~~样例很简单，我就不解释了。~~
## Part1：
由于此题涉及插入、删除，且对于最小值需要频繁查询，因此用 `STL` 库中的容器 `set` 来做就再合适不过了。

我们可以用两个容器 $pre$ 和 $q$ 来表示未叫到的人和已被叫到但未去前台的人。

接下来就是大模拟。

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
set<ll>pre,q;//定义set
ll n,T,i,op,x;
ll rd(){
	ll f=1,s=0;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=(s<<1)+(s<<3)+(ch^48);
		ch=getchar();
	}
	return s*f;
}//快读
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	n=rd();T=rd();
	for(i=1;i<=n;i++) pre.insert(i);
	while(T--){
		op=rd();
		if(op==1){
			q.insert(*pre.begin());
			pre.erase(pre.begin());
		}
		else if(op==2){
			x=rd();
			q.erase(x);
		}else{
			cout<<*q.begin()<<'\n';
		}//模拟
	}
	return 0;
}

```


---

## 作者：Jasoncwx (赞：6)

## 题目思路
首先定义 `set` 容器 `s`。

对于操作 $1$，定义全局变量 `l` 表示最后叫到的人的编号，初始值为 $0$。每次操作前，$l\larr l+1$。在 `s` 中插入 `l`，即 `s.insert(l)`。

对于操作 $2$，从 `s` 中清除输入的数 $x$，即 `s.erase(x)`。

对于操作 $3$，输出已被叫到的编号最小的人，即 `cout<<*begin(x);`。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,q,l=0;
    cin>>n>>q;
    set<int>s;
    while(q--){
    int op,x;
    cin>>op;
    if(op==1)l++,s.insert(l);
    else if(op==2)cin>>x,s.erase(x);
    else cout<<*begin(s)<<endl;
   }
}
```

---

## 作者：Pengzt (赞：4)

[ABC294D](https://www.luogu.com.cn/problem/AT_abc294_d)

题意：给定数组 $a$ 满足 $a_i=i$ 和空数组 $b$，要求支持 $3$ 种操作：

1. 删除 $a$ 中最小的元素，并将其加入 $b$ 数组。
2. 删除 $b$ 中值为 $x$ 的元素，保证存在。
3. 输出 $b$ 中的最小值。

数组长度为 $n$，有 $m$ 次询问，$n, m\le 5\times 10^5$

求最小，删除一个数，可以用 $\texttt{set}$ 解决，用两个 $\texttt{set}$ 维护即可。

时间复杂度：$\mathcal{O}(q\log n)$

[评测记录](https://www.luogu.com.cn/record/105361365)

---

## 作者：_dijkstra_ (赞：3)

提供一种线性的，不用 set 的做法。

## 思路

注意到顾客的编号只能是 $1 \sim n$。考虑用 $vis_i$ 表示一个顾客是否有来报到过。

然后就是一个性质：**答案单调不降**。

因为如果 $i$ 是答案，就能说明 $\forall 1 \le j < i, vis_j = 1$。那么答案只会变大，不会变小。

于是这题就很好做了：维护一个 $ans$，一直增大直到 $vis_{ans} = 0$。输出 $ans$ 即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 5e5 + 5;
bool vis[N];
int main()
{
	int n, q, pos = 0, ans = 1;
	scanf("%d%d", &n, &q);
	while (q--)
	{
		int op;
		scanf("%d", &op);
		if (op == 1) pos++;
		else if (op == 2)
		{
			int x;
			scanf("%d", &x);
			vis[x] = true;
		}
		else
		{
			for (; ans <= pos; ans++)
				if (!vis[ans])
				{
					printf("%d\n", ans);
					break;
				}
		}
	}
	return 0;
}
```

---

## 作者：I_am_kunzi (赞：3)

# AT_abc294_d 题解

### 闪现
[洛谷 abc294d](https://www.luogu.com.cn/problem/AT_abc294_d) | [AtCoder abc294c](https://atcoder.jp/contests/abc294/tasks/abc294_d)

### 题目大意

有 $ N $ 个人去银行办理事务，编号分别为 $ 1 , 2 , 3 , ... , N$，现在有 $ Q $ 次事情，每次事情有以下三种可能。

+ $ 1$，表示又来了一个人；
+ $ 2$，表示标号为 $ x $ 的人离开了；
+ $ 3$，表示现在排队的人当中最小编号的人被叫到。

你需要输出所有第 $ 3 $ 种情况中被叫到的人的编号，以换行隔开。

### 题目分析

由题意可知，这道题我们需要 set 函数（见下一段）以及存储人数和事情的数量的变量 $ N , Q $ 还有描述事件编号的变量 $ opt $ 和当 $ opt $ 的值为 $ 2 $ 的时候离开的人的编号 $ z $ 还有当 $ opt $ 得值为 $ 1 $ 的时候来的人的编号 $ nextpeople$。

这道题就是模拟了一些人排队的情形，我们可以用 set 来完成，这道题主要用到了 set 函数的这些功能。

+ ``` set <int> q ```，表示建立一个队列，名称为 $ q$，里面的数据的类型为 int；
+ ``` q.insert(a) ```，表示在队列 $ q $ 中，在最后插入一个数 $ a$；
+ ``` q.erase(a) ```，表示把 $ a $ 这个数从 $ q $ 这个队列中删除；
+ ``` q.begin() ```，返回队列 $ q $ 中第一个数，但是使用时要把它写成 ``` * (q.begin())```。

根据以上分析，我们可以写出以下代码。

因为代码太长，所以把代码和通过截图放在 [代码和通过截图](https://www.luogu.com.cn/paste/nprygjzo) 里。

---

## 作者：xuyiyang (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_abc294_d)

#### 题目分析
首先一看题，就知道使用堆或者平衡树 set 来维护比较方便
所以就简单了，模板直接就过去了

堆的写法:
首先要手写堆, STL 的优先队列不支持删除 x 的操作
然后按题意模拟即可

set 的写法:
要知道 set 中的最小值(假设当前 set 变量名为 a)为 `*a.begin()`,然后模拟

手写平衡树的写法:
写出插入，删除，查找最小值的操作，直接模拟

当然，为了提高代码难度，~~蒟蒻特地用手写平衡树来写~~(这里使用最好懂的 Treap)

#### $Code1:$
用 set
```
#include <bits/stdc++.h>

using namespace std;

int n, m;
set<int> a, b;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) a.insert(i); //插入1~n
	
	while (m -- )
	{
		int op;
		scanf("%d", &op);
		
		if (op == 1)
		{
			int res = *a.begin(); //最小值
			
			a.erase(res);
			b.insert(res);
		}
		else if (op == 2) 
		{
			int x;
			scanf("%d", &x);
			
			b.erase(x);
		}
		else printf("%d\n", (*b.begin()));
	}
	
	return 0;
}

```

#### $Code2:$

手写平衡树代码
```
#include <bits/stdc++.h>

using namespace std;

const int N = 500010, INF = 0x3f3f3f3f;

struct Node
{
	int l, r;
	int key, val;
	int cnt;
	int size;
};

struct Treap //Treap,也可以用Splay,AVL等
{
	Node tr[N];
	int idx, root;
	
	int get_node(int key)
	{
		idx ++ ;
		tr[idx].key = key;
		tr[idx].val = rand();
		tr[idx].cnt = tr[idx].size = 1;
		
		return idx;
	}
	
	void pushup(int u)
	{
		tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
	}
	
	void zig(int &p) //右旋
	{
		int q = tr[p].l;
		tr[p].l = tr[q].r, tr[q].r = p, p = q;
		pushup(tr[p].r), pushup(p);
	}
	
	void zag(int &p) //左旋
	{
		int q = tr[p].r;
		tr[p].r = tr[q].l, tr[q].l = p, p = q;
		pushup(tr[p].l), pushup(p);
	}
	
	void build()
	{
		get_node(-INF), get_node(INF);
		root = 1;
		
		tr[1].r = 2;
		
		if (tr[root].val < tr[tr[root].r].val) zag(root);
		//不满足堆性质，左旋
	}
	
	void insert(int &p, int key)
	{
		if (!p) p = get_node(key);
		else if (key == tr[p].key) tr[p].cnt ++ ;
		else if (key < tr[p].key)
		{
			insert(tr[p].l, key);
			if (tr[p].val < tr[tr[p].l].val) zig(p);
        //不满足堆性质，旋转
		}
		else
		{
			insert(tr[p].r, key);
			if (tr[p].val < tr[tr[p].r].val) zag(p);
		}
		
		pushup(p); //不要忘记pushup
	}
	
	void remove(int &p, int key)
	{
		if (!p) return ;
		
		if (tr[p].key == key)
		{
			if (tr[p].cnt > 1) tr[p].cnt -- ;
			else
			{
				if (tr[p].l || tr[p].r) //不是叶子节点
				{
					//旋转至叶子节点后删除
					if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
					{
						zig(p);
						remove(tr[p].r, key);
					}
					else
					{
						zag(p);
						remove(tr[p].l, key);
					}
				}
				else p = 0;
			}
		}
		else key < tr[p].key ? remove(tr[p].l, key) : remove(tr[p].r, key);
		
		pushup(p);
	}
	
	int get_val_by_rank(int p, int rank) //根据二叉搜索树的性质
	{
		if (!p) return INF;
		
		if (tr[tr[p].l].size >= rank) return get_val_by_rank(tr[p].l, rank);
		else if (tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
		else return get_val_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
	}
};

Treap a, b;

int n, m;

int main()
{
	scanf("%d%d", &n, &m);
	a.build(), b.build();
	for (int i = 1; i <= n; i ++ ) a.insert(a.root, i);
	
	while (m -- )
	{
		int op;
		scanf("%d", &op);
		
		if (op == 1)
		{
			int key = a.get_val_by_rank(a.root, 2);
			b.insert(b.root, key);
			a.remove(a.root, key);
		}
		else if (op == 2)
		{
			int x;
			scanf("%d", &x);
			
			b.remove(b.root, x);
		}
		else printf("%d\n", b.get_val_by_rank(b.root, 2));
	}
	
	return 0;
}

```

---

## 作者：FinderHT (赞：1)

### 题目传送门：
### [AtCoder](https://atcoder.jp/contests/abc294/tasks/abc294_d) | [洛谷](https://www.luogu.com.cn/problem/AT_abc294_d)

**题意简述**

有 $N$ 个人在银行前排队，编号分别为从 $1$ 到 $N$ ，现在有 $Q$ 次事情，每次事情有以下三种可能：

$1$ 叫编号最小的未被叫号的人。

$2$ 已被叫号但未找出纳员的人 $x$ 去找出纳员。

$3$ 叫编号最小的已被叫号但未找出纳员的人。

你需要输出所有第 $3$ 种情况中被叫到的人的编号，以换行隔开。

**题目分析**

一个布尔数组就能搞定。

首先，我们可以用一个数组 $f$ 来标记已叫号但未找出纳员的人。

对于事件 $1$ ，我们新建变量 $minx$，即未被叫到的编号最小的人，每次执行把 $minx$ 加 $1$ ，把 $f$ 数组中下标为 $minx$ 的位置标记为 $1$ 。

对于事件 $2$ ，我们把 $f$ 数组中下标为 $x$ 的位置标记为 $0$ 即可。

对于事件 $3$ ，我们从第一次执行时从 $1$ 开始遍历 $f$ 数组，直到发现某个位置被标记为 $1$ 时，输出这个位置。之后的每次执行从上一次停止执行的位置开始继续遍历。

### 代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=1e6+5;
bool f[MAXN];//定义bool数组f用来标记
int main(){
	int minx=1;//因为人的编号是从1开始的，所以minx=1
    int come=1;
	int n,q;
	cin>>n>>q;
	while(q--){
		int opt;//事件的编号
		cin>>opt;
		if(opt==1){
			f[minx++]=1;//把编号最小的人标记为1
		}
		if(opt==2){
			int x;
			cin>>x;
			f[x]=0;//把编号为x的人标记为0
		}
		if(opt==3){
			while(!f[come])come++;//遍历f数组，找到编号最小的已被叫号但未找叫号员的人
			cout<<come<<endl;//注意换行输出
		}
	}
	return 0;
}
```


------------

## 完结撒花！

---

## 作者：zajasi (赞：1)

## 题意
现在有三个操作。

* `1`：呼叫最小编号还没呼叫过的人。
* `2 x`：编号为 $x$ 的人来了。 
* `3`：二次呼叫已经经过 $1$ 呼叫但还没来的最小编号。

请输出 $3$ 所呼叫的人。
## 解题思路
看到最小编号，第一反应——set。

运用两个 set，第一个维护所有未被 $1$ 叫过的人。第二个维护所有被 $1$ 叫过但没被 $3$ 叫过的人。对于每一个 $2$ 操作，删除所对应在第二个 set 中的元素。

由于此题没有重复元素，所以 set 足以。multiset 也没事。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(2)
set<int> s1,s2;
int n,m;
int op,x;
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        s1.insert(i);
    }
    for(int i=1;i<=m;i++){
        cin>>op;
        if(op==1){
            s2.insert(*s1.begin());
            s1.erase(*s1.begin());
        }
        else if(op==2){
            cin>>x;
            s2.erase(x);
        }
        else{
            cout<<*s2.begin()<<"\n";//对于 3 直接输出了咩
        }
    }
    return 0;
}

```

---

## 作者：xwh_Marvelous (赞：1)

简单开 stl 的 map 模拟即可。

map，本质上是平衡树，集成了插入，查找，删除，取头尾指针等操作，同时里面数据是按第一关键字排序的。

我们将叫了第一遍的插入 map。对于 $2$ 操作，直接查找删除一条龙。$3$ 操作跟据数据有序的特性取头指针的数据即可。

其实这题 set 做同理。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y,i=1;
map<int,int>mp;
int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		scanf("%d",&x);
		if(x==1)mp[i++]=1;
		if(x==2)scanf("%d",&y),mp.erase(mp.find(y));
		if(x==3)printf("%d\n",mp.begin()->first);
	}
	return 0;
}
```


---

## 作者：As_Snow (赞：0)

## 题目大意

有 $N$ 个人在排队办理事情，编号为 $1$,$2$,$\dots$,$N$。

有 3 个操作：

- `1`：叫队列里编号最小的人去前台。
- `2 x`：编号为 x 的人去前台办理事情然后离开（已经被叫去前台至少一次）
- `3`：输出已经被叫去前台但还没有去的人的编号中最小的一个。

## 思路

用 `set` 储存所有被叫去前台但还没有去的人。

对于 1 操作，我们可以用一个变量 `now` 指向当前最小编号。由于编号是连续的，在最小编号进入 `set` 后，新的 `now` 显然为之前的 `now`+1。

对于 2 操作，可以使用 `set` 的 `erase` 函数，直接删除 `x`。

对于 3 操作，由于 `set` 本身有序，直接输出头指针即可。

## 代码

时间复杂度上界 $\mathcal O(Q\log n)$，但很松。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Q,now=1;//指向还没被叫去前台的最小编号
set<int>wait;//维护被叫到前台但还没去的人
signed main(){
    cin>>n>>Q;
    int opt,x;
    while(Q--){
        cin>>opt;
        if(opt==1){
            wait.insert(now++);
        }if(opt==3){
            cout<<*wait.begin()<<endl;
            //由于有序，输出头指针
        }if(opt==2){
            cin>>x;
            wait.erase(x);
            //直接移出
        }
    }
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**题意**

有个银行，$n$ 人正在排队，编号为 $1,2,3,\dots,n$，有 $q$ 次询问，每次询问包含以下操作：
1. 形式：`1`，操作：银行呼叫编号最小的未呼叫过的人。
2. 形式：`2 x`，操作：编号为 $x$ 的人过去。（保证这个人被叫过且对于一个 $x$ 至多出现 $1$ 次 $2$ 操作。）
3. 形式：`3`，操作：银行呼叫编号最小的呼叫过没过去的人。（对于每一个 $3$ 操作，保证会有这样的人，且至少出现一次 $3$。）

现在让你输出所有 $3$ 操作都是在呼叫编号为几的人。

**分析**

当时赛场上不知名原因 RE 了，后来回来改了一下，就 AC 了，做法挺朴素的，最坏复杂度应该是 $O(nq)$，不过实际上是到不了那么大的~~因为我 AC 了~~。

这题直接开一个大小为 $5\times 10^5$ 的数组 $a$，模拟每个人的状态，$0$ 表示没被叫到，或是叫到了也过去了；$1$ 表示被叫到但没过去。接下来定义一个变量 $p_1$，表示当前的被叫号到的编号，也就是每一次操作 $1$ 叫的人，每次出现 $1$ 操作就加一并把原来的 $a_{p_1}$ 设为 $1$。对于每一次 $2$ 操作，只需要 `a[x]=0` 即可。最后对于每一个 $3$ 操作，我们定义变量 $p_3$（$p_2$ 原本是有的，后来发现用不上，这里为了和代码一致，就写了 $p_3$）表示上一次 $3$ 叫的人，初值为 $1$，每出现操作 $3$，我们就让 $p_3$ 加一直到 $a_{p_3}=1$ 为止，然后输出 $p_3$。

**AC Code**
```
#include <iostream>
using namespace std;
int s[int(5e5+10)];
int main()
{
	int n,q,opt,x,p1=1,p3=1;
	cin>>n>>q;
	while(q--)
	{
		cin>>opt;
		if(opt==1)//操作1
		{
			s[p1]=1;
			p1++;
		}
		if(opt==2)//操作2
		{
			cin>>x;
			s[x]=0;
		}
		if(opt==3)//操作3，也就是反复找到那个没去的人，整个代码复杂度高的造成者，最坏情况要执行n次，但是没有这样的数据
		{
			for(int i=p3;;i++)
			{
				if(s[i])
				{
					cout<<i<<endl;
					p3=i;
					break;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：An_Aholic (赞：0)

## AT_abc294_d 题解
----------

##### "为啥好多大佬都用的 set，就我是两个 queue，一个 map 水过去的吗……" ----@Saint_ying_xtf
----
#### "为啥好多大佬都用的 set,两个 queue，一个 map 就我是啥也不用水过去的吗……" ----@SKB_Konnyaku



感觉比较简单的~就是一个模拟而已~ ~~（还错那么多遍）~~ 

我们看下题，总共有 $3$ 种操作：

第 $1$ 种操作:呼叫目前还没有呼叫的 ID 最小的人。

第 $2$ 种操作:曾经被呼叫的 ID 为 $x$ 的人前来报道。

第 $3$ 种操作:呼叫目前还被呼叫过而没有来的 ID 最小的人，并输出其 ID。



所以思路就很简单了：

先用一个变量 $v$ , 记录当前我们 ID 最小的人的 ID。


对于第 $1$ 种操作:根本就不用操作。

对于第 $2$ 种操作:曾经被呼叫的 ID 为 $x$ 的人前来报道, 然后一个个看过去后面的 ID，找到了就是一个新的最小 ID 者。

对于第 $3$ 种操作:并输出 $v$。

贴代码:

```

#include<bits/stdc++.h>
using namespace std;
int n, q;
bool hj[1000010];  // 记录当前 ID 的是否报到了 
int cnt = 0, v = 1;  // 注意：v = 1！ 因为当前的最小 ID 者是 1 
int main() {
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= q; i++) {  // q次事件 
		int opt, x;
		scanf("%d", &opt);
		// 第一种不用操作 
		if (opt == 2) {
			scanf("%d", &x);
			hj[x] = 1;  // 1 是已来报道，所以接下来的最小 ID 就要接着找了 
			if (x == v)
				while (hj[v])
					v++;
		} else if (opt == 3) {
			printf("%d\n", v);
		}
	}
}


```



---

## 作者：Qinzh (赞：0)

# ABC294D

## 题意

原版：

现在有 $ n $ 个人， 编号为 $ 1, 2, 3, ... ,n $。

有以下 $ q $ 种操作：

$1.$ 柜员呼叫未被呼叫过的编号最小的人。

$2.$ 编号为 $ x $ 的人来找柜员（保证他已经被叫过至少一次）。

$3.$ 柜员再次呼叫已被叫过但没来的人中编号最小的一个，输出此人编号。


~~有点懵是不是（我当时看了半天）~~

形式化：


现在有 $ n $ 个元素 $ 1, 2, 3, ... ,n $。

有以下 $ q $ 种操作：

$1.$ 将不在队列中的最小元素加入队尾。

$2.$ 将队列中 $ x $ 元素删除。

$3.$ 输出队列中最小元素。

这下懂了吧qwq

## 分析

就是一模拟，不过加个小根堆和映射即可。

细节见代码注释

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define gt getchar
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=gt();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}
	return x*f;}//快读
priority_queue <int, vector <int >, greater <int > > heap;//小根堆
map <int, int > m;//map映射
int cnt = 1;//存未入队的最小元素
int main(){
	int n = read(), q = read();
	while(q--){
        int f = read();
        if (f == 1) {
            heap.push(cnt);//加入最小元素
            m[cnt] = 1;//表示cnt在队列中
            ++cnt;//更新未入队最小元素
        }
        else if (f == 2) m[read()] = 0;//删除x元素
        else{
            while (m[heap.top()] == 0) heap.pop();//从头搜最小元素，顺便踢出队列
            cout << heap.top() << endl;//输出
        }
    }
	return 0;
}

```

---

## 作者：Hyh_111 (赞：0)

## **题意**

有 $n$ 个人在银行，分别编号为 $1,2,\dots,n$。他们和收银员要进行 $q$ 次操作，操作类型有三种：

1. 收银员呼叫当前还没被呼叫过的人中编号最小的人。

2. 编号为 $x$ 的人来找收银员，并离开银行。

3. 收银员呼叫当前被呼叫过但还没来的人中编号最小的人。

对于每次操作，若是第三种操作，则输出收银员呼叫的人的编号。

## **思路**

考虑存储没被呼叫过和被呼叫过但还没来的人，并这样应对三种操作：

1. 在没被呼叫过的人的列表中取出编号最小的人，并将其放到被呼叫过但还没来的人的列表中。

2. 在被呼叫过但还没来的人的列表取出编号为 $x$ 的人。

3. 输出被呼叫过但还没来的人的列表中最小的编号。

## **代码**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
set<int> nevcal;//没被呼叫过
set<int> cbdnc;//被呼叫过但还没来的人
set<int>::iterator it;

signed main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) nevcal.insert(i);//一开始所有人都没被呼叫过
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{ 
			it = nevcal.begin();//取出最小编号
			cbdnc.insert(*it);
			nevcal.erase(*it);
		}
		else if (op == 2)
		{
			int x;
			cin >> x;
			cbdnc.erase(x);
		}
		else
		{
			it = cbdnc.begin();//取出最小编号
			printf("%d\n",(*it));
		} 
	}
	return 0;
}
```

---

## 作者：Butterfly___qwq (赞：0)

# 简述
本蒟蒻太弱了，题意也看不懂，只好看样例隐隐约约是个优先队列的基本操作。
# 思路
优先队列的板子，但是又不一样，我们要满足以下操作：
- $O(1)$ 删除指定元素
- $O(1)$ 添加指定元素
- $O(\log n)$ 添加元素

后两个很好办，但第一个不好做，所以可以开两个队列，一个是数据，一个是待删数据，当 `top()` 元素相同时，删除两个 `top()` 元素。代码实现：
```cpp
struct Queue{
    priority_queue<int, vector<int>, greater<int> >p,q;
    //小根堆
    void _push(int x) {p.push(x);}
    void _clear(int x) {q.push(x);}
    bool _empty() {return p.empty();}
    int _top(){
        while(!q.empty()&&p.top()==q.top())
            q.pop(),p.pop();
        if(p.empty())
            return 0;
        else
            return p.top();
    }
    void _pop(){
        if(p.top()==q.top()){
            p.pop(),q.pop();
        }
        else
            p.pop();
    }
};
```
里面封装了很多函数，全部相对应，直接使用即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct st{
	int val,id;
}s[1000001];
bool cmp(st a,st b){
	return a.val<b.val;
}
struct Queue{
    priority_queue<int, vector<int>, greater<int> >p,q;
    void _push(int x) {p.push(x);}
    void _clear(int x) {q.push(x);}
    bool _empty() {return p.empty();}
    int _top(){
        while(!q.empty()&&p.top()==q.top())
            q.pop(),p.pop();
        if(p.empty())
            return 0;
        else
            return p.top();
    }
    void _pop(){
        if(p.top()==q.top()){
            p.pop(),q.pop();
        }
        else
            p.pop();
    }
};
int main(){
	Queue pq;
	int n,m,cnt=1;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int opt;
		cin>>opt;
		if(opt==1){
			pq._push(cnt);
			cnt++;
		}
		else if(opt==2){
			int x;cin>>x;
			pq._clear(x);
		}
		else if(opt==3){
			cout<<pq._top()<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Loser_Syx (赞：0)

为啥好多大佬都用的 `set`，就我是两个 `queue`，一个 `map` 水过去的吗……

## 思路

由于它本来就是从小到大排队的，并不需要用到优先队列，最普通的队列即可。

我们一开始先将所有排队的人从 $1 \sim n$ 放在一个队列（暂且叫它队列 $q1$ 吧）里。

然后对于每一次操作 $1$，将 $q1$ 队列队首一刀另一个队列（暂且叫其 $q2$）里，移出 $q1$ 队首。

对于操作 $2$，再输入一个数，然后我们用 `map` 标记一下这个数已经办理过事情了。方便等会操作 $3$。

对于操作 $3$，先看 $q2$ 队列的队首有没有办理好事情了，如果有，则移出，没有就输出这个数。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
#define FUCK_CCF return 0;
inline int read(){
	register int x = 0, s = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9) write(x / 10);
	putchar((x % 10) + '0');
}
queue<int> q;
queue<int> wait;
map<int, int> MAP;
signed main(){
	int n = read(), Q = read();
	f(i, 1, n, 1){
		q.push(i);
	}
	while(Q--){
		int op = read();
		if(op == 1){
			wait.push(q.front());
			q.pop();
		}else if(op == 2){
			int x = read();
			MAP[x]++;//标记
		}else{
			while(MAP[wait.front()] > 0) wait.pop();//如果map里标记了这个数，就将其移出队列
			write(wait.front());
			puts("");
		}
	}
	return 0;
}
```

---

