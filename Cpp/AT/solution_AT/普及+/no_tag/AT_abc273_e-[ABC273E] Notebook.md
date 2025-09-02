# [ABC273E] Notebook

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_e

整数列 $ A $ とノートがあります。ノートには $ 10^9 $ 枚のページがあります。

$ Q $ 個のクエリが与えられます。各クエリは下記の $ 4 $ 種類のいずれかです。

> ADD $ x $ : 整数 $ x $ を $ A $ の末尾に追加する。

> DELETE : $ A $ の末尾の要素を削除する。ただし、$ A $ が空である場合は何もしない。

> SAVE $ y $ : ノートの $ y $ ページ目に書かれている数列を消し、代わりに現在の $ A $ を $ y $ ページ目に書き込む。

> LOAD $ z $ : $ A $ をノートの $ z $ ページ目に書かれている数列で置き換える。

はじめ、$ A $ は空列であり、ノートのすべてのページには空列の情報が書かれています。 その初期状態から、$ Q $ 個のクエリを与えられる順に実行し、各クエリの実行直後における $ A $ の末尾の要素を出力してください。

なお、入出力の量が多くなる場合があるので、高速な方法で入出力を行うことを推奨します。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ x,\ y,\ z\ \leq\ 10^9 $
- $ Q,\ x,\ y,\ z $ は整数
- 与えられるクエリは問題文中の $ 4 $ 種類のいずれか

### Sample Explanation 1

はじめ、$ A $ は空列、すなわち $ A\ =\ () $ であり、ノートのすべてのページには空列の情報が書かれています。 - $ 1 $ 番目のクエリによって、 $ A $ の末尾に $ 3 $ が追加され、$ A\ =\ (3) $ となります。 - $ 2 $ 番目のクエリによって、ノートの $ 1 $ ページ目に書かれた数列が $ (3) $ になります。$ A $ は変わらず $ A\ =\ (3) $ です。 - $ 3 $ 番目のクエリによって、 $ A $ の末尾に $ 4 $ が追加され、$ A\ =\ (3,\ 4) $ となります。 - $ 4 $ 番目のクエリによって、ノートの $ 2 $ ページ目に書かれた数列が $ (3,\ 4) $ になります。$ A $ は変わらず $ A\ =\ (3,\ 4) $ です。 - $ 5 $ 番目のクエリによって、 $ A $ がノートの $ 1 $ ページ目に書かれた数列 $ (3) $ で置き換えられ、$ A\ =\ (3) $ となります。 - $ 6 $ 番目のクエリによって、 $ A $ の末尾の要素が削除され、$ A\ =\ () $ となります。 - $ 7 $ 番目のクエリでは、$ A $ がすでに空であるので何もしません。$ A $ は変わらず $ A\ =\ () $ です。 - $ 8 $ 番目のクエリによって、 $ A $ がノートの $ 2 $ ページ目に書かれた数列 $ (3,\ 4) $ で置き換えられ、$ A\ =\ (3,\ 4) $ となります。 - $ 9 $ 番目のクエリによって、ノートの $ 1 $ ページ目に書かれた数列が $ (3,\ 4) $ になります。$ A $ は変わらず $ A\ =\ (3,\ 4) $ です。 - $ 10 $ 番目のクエリによって、 $ A $ がノートの $ 3 $ ページ目に書かれた数列 $ () $ で置き換えられ、$ A\ =\ () $ となります。 - $ 11 $ 番目のクエリによって、 $ A $ がノートの $ 1 $ ページ目に書かれた数列 $ (3,\ 4) $ で置き換えられ、$ A\ =\ (3,\ 4) $ となります。

## 样例 #1

### 输入

```
11
ADD 3
SAVE 1
ADD 4
SAVE 2
LOAD 1
DELETE
DELETE
LOAD 2
SAVE 1
LOAD 3
LOAD 1```

### 输出

```
3 3 4 4 3 -1 -1 4 4 -1 4```

## 样例 #2

### 输入

```
21
ADD 4
ADD 3
DELETE
ADD 10
LOAD 7
SAVE 5
SAVE 5
ADD 4
ADD 4
ADD 5
SAVE 5
ADD 2
DELETE
ADD 1
SAVE 5
ADD 7
ADD 8
DELETE
ADD 4
DELETE
LOAD 5```

### 输出

```
4 3 4 10 -1 -1 -1 4 4 5 5 2 5 1 1 7 8 7 4 7 1```

# 题解

## 作者：liangbowen (赞：9)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc273_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17117322.html)

很简单的一道题，强行在英语课的时候想到做法。

存储方式与其他题解稍有不同。本题解着重讲是怎么想到这个做法的。

## 思考过程

首先考虑**暴力**。用 $n$ 个数组（或者 vector 等方式）记录不同版本，每次要保存或更改成版本，直接把 vector 粘贴过来当前列表即可，时间复杂度 $O(q^2)$。

我们考虑是什么地方导致花销巨大：是存档操作。

我们发现，所有存档之间有一定联系。尝试用一个 $pos_i$ 去记录第 $i$ 个存档的位置。假设当前是在 $cur$ 位置，备份直接 $pos_i = cur$ 即可，然后直接做。

但是这样有一个明显的缺点：载入完后啥都做不了了啊！

## 正解

考虑下面的解决方法。

 ![](https://cdn.luogu.com.cn/upload/image_hosting/gbn200r9.png)

事实上，想到用树的方式存储，这题就做完了：

+ 对于 $\texttt{ADD}$ 操作，只需要新建节点，并往当前的 $cur$ 后面接儿子。然后跳过去。
+ 对于 $\texttt{DEL}$ 操作，我们可以在 $\texttt{ADD}$ 的时候记录一下，每一个节点的前一个节点是多少。直接跳 $cur = fa_{cur}$。
+ 对于 $\texttt{SAVE}$ 操作，直接 $pos_i = cur$。
+ 对于 $\texttt{LOAD}$ 操作，直接 $cur = pos_i$。

每次输出 $cur$ 的值即可。注意 $pos_x$ 中的 $x$ 可能会很大。可以离散化或者用更简单的 map 存储。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;
const int N = 5e5 + 5;
map <int, int> pos;
int fa[N], val[N];
vector <int> son[N]; //存储儿子 
int main()
{
	ios::sync_with_stdio(false);
	int T, cur = 0, idx = 0; //根节点是0 
	cin >> T;
	while (T--)
	{
		string op; int x;
		cin >> op;
		if (op != "DELETE") cin >> x;
		
		if (op == "ADD") son[cur].push_back(++idx), val[idx] = x,  fa[idx] = cur, cur = idx;
		else if (op == "DELETE") cur = fa[cur];
		else if (op == "SAVE") pos[x] = cur;
		else if (op == "LOAD") cur = pos[x];
		printf("%d ", val[cur] == 0 ? -1 : val[cur]); //注意空的时候输出 -1 而不是 0
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Empty_Dream (赞：4)

## 题意

有一个初始为空的当前列表，和一个版本保存系统，共 $10^9$ 个版本

进行 $q$ 次操作，有四种类型的操作：

- `ADD x`：在当前列表的末尾添加 $x$
- `DELETE`：如果当前列表非空，把当前列表的末尾最后一个数删除。否则，什么也不做。
- `SAVE x`：把当前列表保存至第 $x$ 版本（保存后当前列表不清空）
- `LOAD x`：把当前列表变成第 $x$ 版本（直接赋值，保存后第 $x$ 版本不清空）。

求每次操作后当前列表的末尾最后一个数（若当前列表为空输出 $-1$）。

## 分析

考虑暴力，把每一个版本都存一次，肯定炸。肯定是用一个数组去维护当前版本，很多个数组去维护这些保存的版本。

很明显当前版本是一个链表，用数组模拟链表，一个 $val$ 数组表示这个元素的值，$fa$ 数组表示这个链表上一个元素的位置，当前列表最后一个数位置为 $now$。

添加和删除操作都是在尾部进行的不会影响到前面的值，那么我们的存档操作可以直接记录 $now$，然后读档时直接更新 $now$ 到保存的位置上。

这又引出一个问题，如何处理删除操作又不影响当前列表？不难想到直接更改 $now$ 就好了，因为在添加的时候是将新来的数挂在 $now$ 后面的，直接把前面删去的数覆盖了（虽然此时可能又多个数的 $fa$ 是 $now$，但是在添加操作的时候只会把 $now$ 更新到最新的数上，保存也只会保存到 $now$，和那些 $fa$ 相同的无关）。

最后输出部分，我们的下标都是从 $1$ 开始的，而且所有输入的值都是大于 $1$ 的，只要判断 $val_{now}$ 是否大于 $0$。

注意，存档时的 $x$ 高达 $1 \times 10^9$，需要使用 map 去存是哪一个存档对应的位置。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, x, pos, now;
int val[500005], fa[500005];
string opt;
map<int, int> save;

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> opt;
		if (opt == "ADD"){
			cin >> x;
			fa[++pos] = now;//类似链表的加入
			val[pos] = x;
			now = pos;//跳到最新的上面
		}
		if (opt == "DELETE") now = fa[now];//只需要挪动now就行
		if (opt == "SAVE"){
			cin >> x;
			save[x] = now;//存档时只需要存位置
		}
		if (opt == "LOAD"){
			cin >> x;
			now = save[x];
		}
		cout << ((val[now] == 0) ? -1 : val[now]) << endl;//判断是否为空
	}
	return 0;
}
```



---

## 作者：heaksicn (赞：2)

## 1 题意

给你一个序列 $a$，初始为空，有 $q$ 次操作。

- ADD $x$：将 $x$ 加到 $a$ 的末尾。

- DELETE：将 $a$ 的末尾从 $a$ 中删除。

- SAVE $x$：将 $a$ 加入到编号为 $x$ 的版本中。

- LOAD $x$：用编号为 $x$ 的版本覆盖 $a$。

每次操作后输出序列末尾的数，如果没有输出 $-1$。

## 2 思路

从这四种操作中，我们发现都很符合 trie 的性质。

所以我们尝试吧序列变成 $trie$。

我们假设当前节点为 $u$。

对于第一个操作，我们可以将 $u$ 新增一个儿子 $x$，并将指针转移到 $x$。

对于第二个操作，吧指针转移到 $fa_u$ 即可。

对于第三个操作，我们可以开一个 map，将点 $u$ 放到编号为 $x$ 的 map 中。

对于第四个操作，将 指针转移到 $map_x$ 即可。

## 3 code

```cpp
//Man always remember love because of romance only!
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int ans[500001];
char s[500001];
int fa[500001];
int val[500001];
map<int,int> mp;
int main(){
	int q=read();
	int tp=0;
	int cnt=0,now=0;
	while(q--){
		tp++;
		scanf("%s",s);
		if(s[0]=='A'){
			int x=read();
			fa[++cnt]=now;
			val[cnt]=x;
			now=cnt;
		}else if(s[0]=='D'){
			now=fa[now];
		}else if(s[0]=='S'){
			int x=read();
			mp[x]=now;
		}else{
			int x=read();
			now=mp[x];
		}
		if(now==0) ans[tp]=-1;
		else ans[tp]=val[now];
	}
	for(int i=1;i<=tp;i++){
		write(ans[i]);
		printf(" ");
	}
	return 0;
}
```


---

## 作者：Saint_ying_xtf (赞：1)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

当你保存了一个版本，相当于暂停在此刻，然后我们可以开一个动态的数组，存储着第 $i$ 个版本最后的点是什么，每一次更新到这个数组当中，然后存储一下网上跳是什么点，很显然可以大概建一个 $fa_i$ 这样的数组，虽然代码中并不是这个名字，但是可以抽象理解。所以说：对于每一个版本让我们想到一种类似字典树的形式，虽然不一样，但感觉其实很像。差不多就是一个树来维护。

具体细节需要动态维护现在在这颗“树”上的哪一个点，然后实现起来比较简单，见代码：[link](https://atcoder.jp/contests/abc273/submissions/49165071)。

---

## 作者：彭俊皓123 (赞：1)

# AT_abc273_e 题解

这题虽然题目说是可持久化，但细想一下就会发现根本用不着。

## 题意

一共 $n$ 个操作，共分为 $4$ 种：

1.当前末尾加上一个数；

2.当前末尾删去一个数；

3.将当前状态保存到位置 $x$；

4.从位置 $x$ 取出一个状态作为当前状态。

每次操作完后输出当前状态的最后一个数。

## 分析

仔细观察操作，会发现这些操作只对当前末尾和倒数第二个数产生影响。

而倒数第二个数，可以转化为当前状态的上一个状态的结尾

于是问题转化为对当前状态及其上一个状态进行操作。

设当前末尾为 $y$，$last_y$ 表示当前状态的上一个状态，$save_i$ 表示保存的 $i$ 号状态，

则四个操作分别为：

1.$last_y=y,y=x$；

2.$last_y=last_{last_y},y=last_y$；

3.$save_x=y$；

4.$y=save_x$。

由于 $i\in[1,10^9]$，因此要用map进行离散化。

以下是代码（快读快写可忽略）：
```cpp
#include<iostream>
#include<unordered_map>
using namespace std;
const int MAXN=500005;
int a,b,c,tot=0;
int last[MAXN],now[MAXN],saved[MAXN];
unordered_map<int,int> p;
inline int read(){
	char x=getchar();int t=0;
	while(!isdigit(x))x=getchar();
	while(isdigit(x))t=(t<<3)+(t<<1)+(x^48),x=getchar();
	return t;
}
char buf[1024];int q=0;
inline void pc(char x){buf[q++]=x;if(q==1024)fwrite(buf,1,1024,stdout),q=0;}
inline void print(int x){
	short stk[15],to=0;
	if(x<0)pc('-'),x=-x;
	while(x)stk[++to]=x%10,x/=10;
	while(to)pc(stk[to--]+'0');
	pc(' ');
}
int main()
{
	a=read();
	for(int i=1;i<=a;++i){
		char x;int y;x=getchar();
		switch(x){
		case 'A':y=read();now[i]=y,last[i]=i-1;break;
		case 'D':while(x!='\n')x=getchar();now[i]=now[last[i-1]],last[i]=last[last[i-1]];break;
		case 'S':y=read();now[i]=now[i-1],last[i]=last[i-1];if(!p[y])p[y]=++tot;saved[p[y]]=i;break;
		case 'L':y=read();if(!p[y])p[y]=++tot;now[i]=now[saved[p[y]]],last[i]=last[saved[p[y]]];break;
		}
	print(now[i]?now[i]:-1);
	}
	fwrite(buf,1,q,stdout);fflush(stdout);
	return 0;
}

```

---

## 作者：BlackPanda (赞：1)

*[problem](https://www.luogu.com.cn/problem/AT_abc273_e)*

------------
## Description

维护一个序列，初始为空，有 $q$ 次操作，操作可能包含：

- $\verb!ADD x!$：将 $x$ 加到序列末尾。

- $\verb!DELETE!$：删除序列的末尾元素，如果序列为空，则不进行操作。

- $\verb!SAVE x!$：将序列备份为第 $x$ 个版本。

- $\verb!LOAD x!$：恢复序列备份到第 $x$ 个版本。

在每次操作后输出序列的末尾元素，特别的，如果序列为空，则输出 $\verb!-1!$。

------------
## Solution

序列中最多有 $5 \times 10^5$ 个元素，并且最多有 $10^9$ 个版本，所以暴力模拟肯定会超时。

可以考虑用链式结构模拟，每次操作只更新指向序列末尾元素的指针 $p$。

每次操作更新如下：

- 对于操作 1：指针后移一位，同时更新当前节点的值和前驱。

- 对于操作 2：使指针更新成它的前驱。

- 对于操作 3：可以用 $\verb!map!$ 来存序列当前的指针。

- 对于操作 4：指针恢复到 $map_x$。

------------
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
        int s = 0, w = 1; char ch = getchar();
        while (ch < '0' || ch > '9') {if (ch == '-') w = -1; ch = getchar();}
        while (ch >= '0' && ch <= '9') {s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar();}
        return s * w;
}

const int N = 5e5 + 10;

int n;
string op;
int x, c;
int Point;
map<int, int> val;
int k[N], m[N];

void solve()
{
        n = read();
        while (n -- )
        {
                cin >> op;
                if (op == "ADD")
                {
                    x = read();
                    k[++c] = Point;
                    Point = c;
                    m[c] = x;
                }
                else if (op == "DELETE")
                {
                    Point = k[Point];
                }
                else if (op == "SAVE")
                {
                    x = read();
                    val[x] = Point;
                }
                else
                {
                     x = read();
                     Point = val[x];
                }
                if (Point <= 0) cout << "-1 ";
                else    cout << m[Point] << " ";
        }
}

int main()
{
	int _ = 1;
	while (_ -- )
		solve();
   return 0;
}
```


---

## 作者：Siegerkranz_2735 (赞：1)

## 解决方案

### 分析

首先分析一下题目。题目要求要保留版本，同时数据的出入顺序是先进的数据后出，不难想到可以用可持久化和栈。

### 解析

#### ADD $x$ 操作

这个十分容易理解,首先是总数（新数据的位置）更新，然后再用 $t_i$ 记录当前的最新数据，最后用 $pervipus$ 记录上一个最新的数据。

```cpp
if(st=="ADD"){
	scanf("%d",&x);
	num[++now]=x;
	t[i]=now;
	previous[t[i]]=t[i-1];
}
```
#### DELETE 操作

这个操作非常简单,是需要复制 $previous$ 就可以了。不过不要忘记，如果当前列表为空，什么都不做。

```cpp
if(st=="DELETE"){
	if(previous[t[i-1]])
		t[i]=previous[t[i-1]];
}
```
#### SAVE $x$ 操作

这里是备份操作，只需要 $vers$ 存上当前的情况就可以了。不过要注意，这里的 $x$ 的范围极大，数组装不下，但是可以用 ```map``` 储存。

```cpp
if(st=="SAVE"){
	scanf("%d",&x);
	vers[x]=i-1;
	t[i]=t[i-1];
}
```
#### LOAD $x$ 操作

这里直接复制备份的 $vers$ 即可。

```cpp
if(st=="LOAD"){
	scanf("%d",&x);
	t[i]=t[vers[x]];
}
```

#### 注意

在执行 SAVE 的时候，由于没有改变，所以一定不要忘记记录当前最新数据的位置为上一次的，蒟蒻写代码的时间不连贯，导致这里出了错一直找不到为什么。

不难得到如下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,num[N],t[N],previous[N],now,x;string st;
map<int,int> vers;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>st;
        if(st=="ADD")scanf("%d",&x),num[++now]=x,t[i]=now,previous[t[i]]=t[i-1];
		else if(st=="LOAD")scanf("%d",&x),t[i]=t[vers[x]];
        else if(st=="DELETE"){if(previous[t[i-1]])t[i]=previous[t[i-1]];}
		else if(st=="SAVE")scanf("%d",&x),vers[x]=i-1,t[i]=t[i-1];
        printf("%d ",t[i]?num[t[i]]:-1);
    }
    return 0;
}
```

---

## 作者：Shunpower (赞：1)

## 思路

发现有版本的问题，所以考虑主席树乱草。

现在主席树维护一个长度 $5\times 10^5$ 的数列 $a$，一开始全空（全为 $0$），我们先来考虑笔记本相关操作。

### `SAVE x`

发现笔记本的页数可以非常大，所以考虑 $\texttt{map}$，只需要把目前的根放进 $x$ 映射的位置就行了，而且题目正好要求覆盖之前的内容。本操作没有修改，因此目前的版本直接继承上一个版本即可。

### `LOAD x`

直接拿下来 $x$ 映射的位置的根当成目前的根用就行了。

### `ADD x`

首先我们考虑如何得到最后要加在哪个位置，容易发现只需要维护一下线段树上每个节点的子树内有多少非 $0$ 叶子然后线段树上二分就行了，只要右儿子的计数器不是 $0$ 就往右儿子走，否则就走左儿子。当走到叶子（也就是 `l==r`）的时候返回一下这个位置就行了。不妨假设这个位置是 $d$。

然后在上个版本基础上往目前的根里面 $d$ 的位置插入一个 $x$ 就行了。顺便维护一下叶子节点的值以及二分的时候要用的计数器。

### `DELETE`

同样先线段树上二分出来末尾，然后在上个版本的基础上把这个位置改成 $0$ 即可，修改的时候要减计数器。

### 单点查询

同样线段树上二分末尾在哪，二分到叶子节点直接返回我们之前维护的叶子节点的值就行了。如果整个线段树上都没有非 $0$ 的叶子节点就返回 $-1$。

然后你就做完了，复杂度 $O(n\log n)$ 带主席树的巨大常数。这里线段树上二分是单 $\log$ 的，因为是直接在全局搞。

## 代码

除了主席树的 `insert`，其他都是线段树的基础操作。

```cpp
//Author:Zealous_YH / Cream_H
//Su Chanzi & Xiao Bao
//Hey Left
//Just enjoy the loneliness
//Open a personal party always stay
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=5e5+10;
const int M=5e5;
int Q;
int rt[N];
map <int,int> p;
string s;
int x;
int tnt;
vector <int> ans;
#define mid ((l+r)>>1)
struct Chairman_Segment_Tree{
	int sum[N*50],ls[N*50],rs[N*50],val[N*50];
	void insert(int &p,int las,int l,int r,int d,int v,int v2){
		if(!p){
			tnt++;
			p=tnt;
		}
		sum[p]=sum[las]+v;
		if(l==r){
			val[p]=v2;
			return;
		}
		if(d<=mid){
			insert(ls[p],ls[las],l,mid,d,v,v2);
			rs[p]=rs[las];
		}
		else{
			insert(rs[p],rs[las],mid+1,r,d,v,v2);
			ls[p]=ls[las];
		}
	}
	int binary_query(int p,int l,int r){
		if(l==r){
			return l;
		}
		if(sum[rs[p]]){
			return binary_query(rs[p],mid+1,r);
		}
		else if(sum[ls[p]]){
			return binary_query(ls[p],l,mid);
		}
		return 0;
	}
	int query(int p,int l,int r){
		if(l==r){
			return val[p];
		}
		if(sum[rs[p]]){
			return query(rs[p],mid+1,r);
		}
		else if(sum[ls[p]]){
			return query(ls[p],l,mid);
		}
		return -1;
	}
} T;
#undef mid
int main(){
	cin>>Q;
	fr1(i,1,Q){
//		rt[i]=rt[i-1];
		cin>>s;
		if(s[0]=='A'){
			cin>>x;
			int d=T.binary_query(rt[i-1],1,M);
//			cout<<d<<endl;
			T.insert(rt[i],rt[i-1],1,M,d+1,1,x);
		}
		else if(s[0]=='D'){
			int d=T.binary_query(rt[i-1],1,M);
			if(d==0){
				ans.pb(-1);
				continue;
			}
			T.insert(rt[i],rt[i-1],1,M,d,-1,0);
		}
		else if(s[0]=='S'){
			cin>>x;
			rt[i]=rt[i-1];
			p[x]=i;
		}
		else if(s[0]=='L'){
			cin>>x;
			rt[i]=rt[p[x]];
//			cout<<"!"<<p[x]<<endl;
//			cout<<
		}
		ans.pb(T.query(rt[i],1,M));
//		cout<<<<" ";
	}
//	fr1(i,1,Q){
//		cout<<rt[i]<<" ";
//	}
//	cout<<endl;
	fv(i,ans){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji, Lin, Hao, Shun, Hang and You.
```

[AC 记录](https://www.luogu.com.cn/record/91898923)

---

## 作者：_zhx (赞：0)

# AT_abc273_e [ABC273E] Notebook 题解

## 题目大意

有一个系统，有 $10^9$ 个版本，每个版本初始都是空列表。

给定 $q$ 次操作，每次操作是以下四种操作之一，求每次操作后的当前列表的末尾最后一个数，若数组为空输出 $−1$。

有四种操作：
 
- `ADD x`：在当前列表末尾加上 $x$；

- `DELETE`：如果当前列表为空，什么也不做；否则把当前列表的末尾最后一个数删除；

- `SAVE x`：把当前列表保存至第 $x$ 版本;

- `LOAD x`：把当前列表变成第 $x$ 版本。注意：是**直接赋值**，**而不是添加**，而且保存后第 x 版本**不清空**

### 题目思路

如果只有前两种操作，那么非常简单。

但后两种方法，用耗时，还耗空间。

但是，`ADD` 就是继续往下，而 `DELETE` 就是返回，这就是一棵树。

不放设当前在 $p$ 节点，共有 $e$ 个节点。

初始从 $0$ 开始遍历。

- `ADD x`：给 $p$ 建立一个儿子节点 $e+1$，并节点记录的数为 $x$，$e$也加 $1$，并将 $p$ 设为 $e$；

- `DELETE`：将 $p$ 给为 $p$ 的父亲节点；

- `SAVE x`：给第 $x$ 个系统记录一个存档的节点编号 $p$。

- `LOAD x`：将 $p$ 设为第 $x$ 个系统记录的存档节点编号。

为了方便，我们可以用 `map` 存储每个系统的存档节点的编号，和一个 `pair` 来记录节点和节点总数。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
pair<int,int>a[N];
map<int,int>m;
int main()
{
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	int q,e=0,p=0;
	a[0]={0, -1};
	cin>>q;
	while(q--)
	{
		string s;int x;
		cin>>s;
		if(s[0]=='A')
		{
			cin>>x;
			a[++e]={p,x};
			p=e;
		}
		else if(s[0]=='D') p=a[p].first;
		else if(s[0]=='S')
		{
			cin>>x;
			m[x]=p;
		}
		else if(s[0]=='L')
		{
			cin>>x;
			p=m[x];
		}
		cout<<a[p].second<<' ';
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution

我们可以发现最终的序列一定是一棵树，所以考虑在树上操作。

1. 对于 `ADD`，将 $u$ 的儿子增加一个变为 $x$，并记录 $x$ 的父亲为 $u$。

2. 对于 `DEL`，将 $u$ 走向它的父亲即可。

3. 对于 `SAV`，将 $u$ 用一个 `map` 存起来，以后用的时候直接取出来即可。

4. 对于 `LOA`，直接取出 $mp_x$ 即可。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=5e5+10,INF=1e9+7;  
int n; 
int tr[N]; 
int ans[N]; 
int lst[N]; 
map<int,int> mp; 
struct Mind{ 
	bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
signed main(){ 
	n=read(); int cnt=0,now=0; 
	for(int i=1;i<=n;i++){ 
		string opt; int x; 
		cin>>opt; if(opt[0]!='D') x=read(); 
		if(opt=="ADD") ++cnt,tr[cnt]=x,lst[cnt]=now,now=cnt; 
		else if(opt=="DELETE") now=lst[now]; 
		else if(opt=="SAVE") mp[x]=now; else now=mp[x]; 
		ans[i]=tr[now];  
	} for(int i=1;i<=n;i++) printf("%d ",ans[i]==0?-1:ans[i]); puts(""); 
	return 0;
} /* */ 
```


---

## 作者：wnsyou (赞：0)

# [Notebook](https://www.luogu.com.cn/problem/AT_abc273_e)
## 题意
有 $q$ 次操作。

现在你有一个空序列 $a$ 和一本 $10^9$ 页的笔记本，每页纸上都有一个空序列。

每次操作是以下四种中的一种：

- `ADD x`，表示在 $a$ 的末尾插入一个整数 $x$。
- `DELETE`，表示删除 $a$ 的末尾的一个数，如果 $a$ 序列为空则什么也不干。
- `SAVE y`，表示将第 $y$ 页纸上的序列替换为 $a$。
- `LOAD z`，表示将 $a$ 换成第 $z$ 页纸上的序列。

对于每次操作，你需要输出操作完后的 $a$ 序列的最后一个数，如果 $a$ 为空则输出 `-1`，输出用空格分隔。
## 思路
如果只有 `ADD` 和 `DELETE`，应该都会做，栈模拟。

经过观察，我们可以发现：`SAVE` 和 `LOAD` 两种操作既耗时间又耗空间，但两种操作**都与原序列有些关联！**

`ADD` 就相当于往下 `dfs`，`DELETE` 就相当于回溯，欸，这不就是 `dfs` 树吗？考虑把序列建成一个树。

假设现在考虑的节点编号为 $now$，节点数量为 $n$。

$now$ 初始可以设为 $0$。

- `ADD x`，就是给 $now$ 建立一个儿子节点 $n + 1$，节点记录的数为 $x$，并将 $now$ 设为 $n + 1$。
- `DELETE`，就是将 $now$ 改为 $now$ 的父亲节点编号。
- `SAVE y`，给第 $y$ 页纸记录一个存档的节点编号，这个编号也就是 $now$。
- `LOAD z`，将 $now$ 设为第 $z$ 张纸记录的存档节点编号。

由于页数有 $10^9$，所以要用 `map` 存储每页纸存储的存档节点编号。
### 复杂度
- 时间：$O(q \log q)$。
- 空间：$O(q)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int Q = 5e5 + 10;

struct ID {
  int x, fa; // x 记录数值，fa 记录父亲节点编号
} a[Q];

int q, x, n, now;
string s;
map<int, int> mp; // 每页纸上记录的存档的节点编号

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  a[0].x = -1;
  for (cin >> q; q; q--) {
    cin >> s;
    if (s[0] != 'D') {
      cin >> x;
    }
    if (s == "DELETE") { // 回溯
      now = a[now].fa;
    } else if (s == "ADD") { // 新建节点
      a[++n] = {x, now}, now = n;
    } else if (s == "SAVE") { // 存档
      mp[x] = now;
    } else { // 取档
      now = mp[x];
    }
    cout << a[now].x << ' ';
  }
  return 0;
}
```

---

