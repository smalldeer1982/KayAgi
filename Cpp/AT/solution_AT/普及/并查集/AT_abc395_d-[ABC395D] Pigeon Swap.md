# [ABC395D] Pigeon Swap

## 题目描述

有 $N$ 只鸽子（编号 $1,2,\ldots,N$）和 $N$ 个巢（编号 $1,2,\ldots,N$）。初始时，鸽子 $i$（$1 \leq i \leq N$）位于巢 $i$ 中。

接下来对鸽子进行 $Q$ 次操作，操作分为以下三种类型：

- **类型 1**：给定整数 $a,b$（$1 \leq a \leq N$，$1 \leq b \leq N$）。将鸽子 $a$ 从当前所在的巢中取出，放入巢 $b$。
- **类型 2**：给定整数 $a,b$（$1 \leq a < b \leq N$）。将巢 $a$ 中所有鸽子移动到巢 $b$，同时将巢 $b$ 中所有鸽子移动到巢 $a$。这两个移动操作是同时进行的。
- **类型 3**：给定整数 $a$（$1 \leq a \leq N$）。报告鸽子 $a$ 当前所在的巢的编号。

请输出所有类型 3 的操作的结果。

## 说明/提示

### 约束条件
- $1 \leq N \leq 10^6$
- $1 \leq Q \leq 3 \times 10^5$
- 所有操作均符合题目描述中的参数范围。
- 输入中至少包含一个类型 3 操作。
- 输入均为整数。

### 样例解释 1
操作过程中鸽子的移动如图所示（图片链接略）。类型 3 操作应报告的巢编号依次为 $4,5,2,5$，因此输出四行：`4`、`5`、`2`、`5`。

### 样例解释 2
在类型 1 操作中，可能存在将鸽子取出后又放回原巢的情况。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 8
1 2 4
1 3 6
3 2
2 4 5
3 2
1 4 2
3 4
3 2```

### 输出

```
4
5
2
5```

## 样例 #2

### 输入

```
1 2
1 1 1
3 1```

### 输出

```
1```

## 样例 #3

### 输入

```
30 15
3 3
2 8 30
2 12 15
2 2 17
1 19 1
2 7 30
3 12
3 8
2 25 26
1 13 10
1 16 10
2 16 29
2 1 21
2 6 11
1 21 8```

### 输出

```
3
15
7```

# 题解

## 作者：Little_x_starTYJ (赞：19)

## 题目大意
这里有 $n$ 个鸽巢和 $n$ 只鸽子，一开始第 $i$ 只鸽子在第 $i$ 个鸽巢里面。

现有 $q$ 次操作，操作分三种类型：
- `1 a b`，将第 $a$ 只鸽子移动到鸽巢 $b$。
- `2 a b`，将第 $a$ 个鸽巢里面的所有鸽子与第 $b$ 个鸽巢里面的所有鸽子交换。、
- `3 a`，询问第 $a$ 个鸽子在第几个鸽巢里。

## 解题思路
笑死，被并查集硬控了，最后也是不写并查集了好吧。
### 思路 1
并查集，由于蒟蒻~~懒~~不会，所以没有代码，各位大佬可以在评论区附上代码（膜膜膜）。

#### 前置定义
定义 $s_i$ 为鸽子 $i$ 的大王鸽王（为了方便理解，我们强制随机一个鸽子作为鸽王），$f_i$ 为鸽王 $i$ 所在的鸽巢，$p_i$ 为鸽巢 $i$ 中的鸽王。

#### 理论思路：

首先对于操作 $1$，我们先从鸽子 $a$ 原本的鸽巢 $s_a$ 里面删除 $a$，再将它添加到鸽巢 $b$ 里面去。

对于操作 $2$，我们 $swap(f_{p_a}, f_{p_b})$ 即可。

对于操作 $3$，我们输出 $f_{s_a}$ 即可。

是不是很简单？需要注意的是，操作 $1$ 需要分类讨论（个人想法），如果鸽子 $a$ 不是鸽王我们先路径压缩一波再直接更改父节点即可，如果是鸽王就需要使用并查集的删除操作了。

$s_i$ 并不能直接求到、存储，我们仍需要通过并查集的 `find` 操作，这里只是方便理解。

CODE：QWQ。
### 思路 2
类似思路 $1$，我们首先让 $flag_i = i$，即第 $i$ 个位置上对应着鸽巢 $flag_i$，之后我们每一次操作就只用交换对应位置上的鸽巢即可。$id$ 数组不太好描述，直接看代码吧。

---
**$2025$ 年 $3$ 月 $6$ 日 $14$ 时 $22$ 分 $44$ 秒更新：**

之前思路 $2$ 讲得不太详细，看到 @[zhx20081129](https://www.luogu.com.cn/user/914572) 大佬的回复后忽然就大概明白怎么描述了。

我们并不想将鸽子一个一个交换，因为这样很浪费时间，所以我们可以直接交换鸽巢。那么就存在一个问题，原来 $i$ 号鸽巢在第 $i$ 个位置上，在进行一次交换鸽巢 $a,b$ 的操作后，那么就变成了第 $b$ 个位置上对应鸽巢 $a$，第 $a$ 个位置上对应鸽巢 $b$。

这时，$id_a$ 就存的是 $b$，表示鸽巢 $a$ 现在位于位置 $b$，$flag_x$ 就表示位置 $x$ 上现在是哪一个鸽巢。于是我们就可以愉快地解决这道题啦！


CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 10;
int sett[N], id[N], flag[N];   //sett 表示鸽子 $a$ 所属鸽巢，
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		sett[i] = i, flag[i] = i, id[i] = i;
	}
	while (q--) {
		int op, a, b;
		cin >> op >> a;
		if (op == 1) {
			cin >> b;
			sett[a] = id[b];
		} else if (op == 2) {
			cin >> b;
			swap(flag[id[a]], flag[id[b]]);
			swap(id[a], id[b]);
		} else {
			cout << flag[sett[a]] << "\n";
		}
	}
	return 0;
}
```

---

## 作者：da_ke (赞：16)

> fyy 是一个珂愛的女孩子，有一天她购得 $N$ 只珂愛的 da_ke。
>
> 她初始将编号 $i$ 的 da_ke 放置在 $i$ 号笼子里。
>
> 随后，她进行 $Q$ 次操作，操作分为 $2$ 类
>
> 1. 将 $a$ 号 da_ke 放入 $b$ 号笼子
> 2. 将 $a$ 号笼子和 $b$ 号笼子里的所有 da_ke 互换。
>
> fyy 可以在任意时刻问妳某个 da_ke 在哪个笼子里。
>
> fyy 非常喜欢 da_ke，于是她买了很多只，于是妳要使用一种非常高效的算法来回答她的问题。

「珂愛的我」（下简记为我）想到，对于操作 $1$ 是容易的，经常刷题的朋友都知道，对于操作 $2$ 不容易**单个处理**，必须**整体处理**。

对于操作 $2$，我想到将笼子 $a$ 和笼子 $b$ **整体交换**。但这将导致 $a$ 和 $b$ 的位置改变，da_ke 的位置也将改变，如何处理呢？

问题过于抽象，为了更加形象（笔者赛时也是这么想的），我将问题形象化。

将笼子和 da_ke 一起放在数轴上。为了语言描述，我常用「da_ke 本身」和「笼子本身」这两个短语。

- 对于所有操作 $1$，我们只需挪动 da_ke 本身的位置即可。
- 对于所有操作 $2$：
    - **保证 da_ke 本身的位置不变**（解题的关键）。
    - 只交换笼子本身达到效果。
    - 更新笼子本身的位置。

以上是一些感性认识，我们现在将其转换为形式化语言。

记笼子 $i$ 的坐标位置为 $S_i$，坐标位置 $i$ 的笼子为 $E_i$，编号为 $i$ 的 da_ke 目前被关在**坐标位置为 $H_i$ 的笼子**里。

- 对于操作 $1$，$H_a \leftarrow S_b$。
- 对于操作 $2$：
  - $a$ 的位置将被 $b$ 占用，$b$ 同理，于是有 $E_{S_a}\leftarrow b,E_{S_b}\leftarrow a$。
  - 将 $a,b$ 的坐标位置互换，达到 $S_a'=S_b,S_b'=S_a$ 的效果。

代码是简单的。

```cpp
int main()
{
    int N,Q;
    cin>>N>>Q;
    vector<int> st(N+1),ed(N+1),home(N+1); // st 为某个巢的坐标位置，ed 为某个坐标位置的巢。 
    rep(i,1,N) st[i]=i,ed[i]=i,home[i]=i;
    rep(i,1,Q)
    {
        int o;
        cin>>o;
        // 操作时应保证，鸽子是不动的。
        if(o==1)
        {
            int a,b;
            cin>>a>>b;
            home[a]=st[b];
        }
        /*
        .....a.....b....
        .....b.....a....
        */
        if(o==2)
        {
            int a,b;
            cin>>a>>b;
            ed[st[a]]=b,ed[st[b]]=a;
            swap(st[a],st[b]);
        }
        if(o==3)
        {
            int a;
            cin>>a;
            cout<<ed[home[a]]<<endl;
        }
    }
}

// 路虽远行则将至，事虽难做则必成。
```

[AC 记录](https://atcoder.jp/contests/abc395/submissions/63297018)

---

## 作者：Revitalize (赞：9)

赛时糊的抽象做法。
### 题面
有 $N$ 只标有 $1, 2, \ldots, N$ 的鸽子和 $N$ 个标有 $1, 2, \ldots, N$ 的鸽巢。  
最初，鸽子 $i$ 在 $(1 \leq i \leq N)$ 巢中。 $(1 \leq i \leq N)$ 在巢 $i$ 中。  
 $Q$ 次操作，有三种：  
- 给定整数 $a$ 和 $b$ 。 $(1 \leq a \leq N, 1 \leq b \leq N)$ .将鸽子 $a$ 从当前巢中取出，移到巢 $b$ 中。
- 给你整数 $a$ 和 $b$ 。 $(1 \leq a,b \leq N)$ .将巢 $a$ 中的所有鸽子移动到巢 $b$ ，并将巢 $b$ 中的所有鸽子移动到巢 $a$ 。这两次移动是同时进行的。
- 给你一个整数 $a$ $(1 \leq a \leq N)$ ，输出鸽子 $a$ 所在的巢的编号。
### 解法
考虑对于每个巢，维护一个什么结构，那么它应该满足插入一个数，删除一个数，且两个结构可以迅速互换。  
平衡树显然可以。  
所以就可以开 $N$ 棵平衡树。  
每棵平衡树中，再定义一个 $rt$ 的父亲 $id$，表示这棵平衡树所代表的巢的序号。  
操作一就是插入操作加删除操作，复杂度均摊 $O(\log n)$。  
操作三就是从 $a$ 开始一直向上跳到它所在的平衡树的 $id$，返回，复杂度均摊 $O(\log n)$。  
操作二就是让两棵平衡树的 $rt$ 互换父亲，复杂度 $O(1)$。  
总复杂度 $O(q\log n)$。    
因为 FHQ Treap 不记录 $fa$，所以用 Splay。（太菜了只会这两种）  
在 Splay 时旋到这棵树 $id$ 的下面就可以了。  
插入的时候就以节点编号作为关键字在树上插入即可。  
最后 $id$ 所对应的节点因为是巢的编号，所以要与鸽子节点区分开，所以不妨令 $i+n$ 号节点代表 $i$ 号巢。
### 代码  
压行严重，不喜勿喷。  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Opshacom{
    const int N=3e6+5;
    int fa[N],ch[N][2],n,q;
    inline int getrt(int x){while(1){if(fa[x]>n)return x; x=fa[x];}}
    inline bool get(int x){return (x==ch[fa[x]][1]);}
    inline void rotate(int x){
        int f=fa[x],gf=fa[f],lr=get(x);
        ch[f][lr]=ch[x][lr^1];
        if(ch[x][lr^1]) fa[ch[x][lr^1]]=f;
        ch[x][lr^1]=f,fa[f]=x,fa[x]=gf;
        if(gf) ch[gf][f==ch[gf][1]]=x;
    }
    inline void splay(int x){
        int goal=fa[getrt(x)];
        while(fa[x]!=goal){
            int f=fa[x],g=fa[fa[x]];
            if(g!=goal){if(get(f)==get(x)) rotate(f);else rotate(x);}
            rotate(x);
        }
    }
    inline int pr(int x){
        int now=ch[x][0];
        if(!now) return now;
        while(ch[now][1]) now=ch[now][1];
        splay(now);
        return now;
    }
    inline void del(int x){
        splay(x);
        if(!ch[x][0]&&!ch[x][1]){ch[fa[x]][0]=0;fa[x]=0;return ;}
        if(!ch[x][0]){ch[fa[x]][0]=ch[x][1];fa[ch[x][1]]=fa[x];ch[x][1]=fa[x]=0;return;}
        if(!ch[x][1]){ch[fa[x]][0]=ch[x][0];fa[ch[x][0]]=fa[x];ch[x][0]=fa[x]=0;return;}
        int now=x,f=fa[x],tmp=pr(x);
        //cout<<now<<" "<<f<<" "<<tmp;
        fa[ch[now][1]]=tmp,ch[tmp][1]=ch[now][1];
        ch[f][0]=tmp,fa[now]=ch[now][0]=ch[now][1]=0;
    }
    inline void insert(int id,int x){
        if(!ch[id][0]){ch[id][0]=x;fa[x]=id;return ;}
        int now=ch[id][0],f=id;
        while(true){
            f=now,now=ch[now][now<x]; 
            if(!now){
                fa[x]=f,ch[f][f<x]=x;
                splay(x);break;
            }
        }
    }
    inline void work(){
        cin>>n>>q;
        for(int i=1;i<=n;i++) fa[i]=i+n,ch[i+n][0]=i;
        while(q--){
            int op,x,y;cin>>op;
            if(op==1) cin>>x>>y,del(x),insert(y+n,x);
            if(op==2)cin>>x>>y,fa[ch[x+n][0]]=y+n,fa[ch[y+n][0]]=x+n,swap(ch[y+n][0],ch[x+n][0]);
            if(op==3)cin>>x,cout<<fa[getrt(x)]-n<<"\n";
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    //cin.tie(0),cout.tie(0);
    return Opshacom::work(),0;
}
```

---

## 作者：lfxxx_ (赞：8)

我们考虑开三个数组，$f_i$ 表示鸽子 $i$ 所在的巢穴所在的位置，$id_i$ 表示位置为 $i$ 的巢穴的编号，$p_i$ 表示编号为 $i$ 的巢穴的位置。

对于操作一，我们令 $f_i \gets p_y$ 即可。

对于操作二，我们交换 $id_x$ 和 $id_y$，同时交换 $p_x$ 和 $p_y$。

对于操作三，答案就是 $id_{fa_x}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int fa[N],id[N],p[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;++i)
        fa[i]=id[i]=p[i]=i;
    while(q--)
    {
        int op,x,y;
        cin>>op>>x;
        if(op==1)
        {
            cin>>y;
            fa[x]=p[y];
        }
        if(op==2)
        {
            
            cin>>y;
            swap(id[p[x]],id[p[y]]);
            swap(p[x],p[y]);
        }
        if(op==3)
            cout<<id[fa[x]]<<'\n';
    }
}
```

---

## 作者：Clover_Lin (赞：7)

## 前言
https://blog.csdn.net/ArmeriaLeap/article/details/145954559

> 在谎言中迷茫，试图躲避瓶颈。
> 可惜细节太多，浪费五发罚时。
> 一个绿名用户，被出题人卡住。
> 八十六分钟多，才看见一抹绿。

本题解 $\LaTeX$ 格式可能不太美观，以内容为主。
## 题目大意
[有一群鸽子和它们的窝，三种操作，你要在第三种的时候输出一个数。题面很简单，没有太多的文字游戏，自行阅读吧。这篇题解不提供题目翻译。](https://atcoder.jp/contests/abc395/tasks/abc395_d)
## 思路
想一想暴力，为什么会超时？正解需要对哪里进行优化？

观察第二种操作，发现它太吃操作了，是这道题的时间复杂度瓶颈。本文将介绍一种时间复杂度为 $O(Q)$ 的做法。对于第二种操作，显然不能暴力模拟——为了不超时，我们绝对不能交换鸽子！作为口是心非的 OIer，让我们充分发扬人类智慧：做个记号，下面算答案的时候注意一下即可。

具体地，我们要维护三个数组：
$$
a_i表示第i只鸽子在哪个窝里；\\
b_i表示“第i个窝”里的鸟儿实际上被换到了哪个窝；\\
c_i表示第i个窝现在用谁表示。
$$
有点绕，好好理解一下。~~毕竟我调了近一个小时，这肯定不是什么简单的东西。~~

现在来说一下三种操作的实现。

- 第一种操作——单只鸽子 $x$ 搬到 $y$ ：`a[x]=c[y];`
- 第二种操作——$x$ 和 $y$ 两个窝集体交换：`swap(b[c[x]],b[c[y]]); swap(c[x],c[y]);`
- 第三种操作——输出 $x$ 在哪里：`cout << b[a[x]] << endl;`
## 代码实现
[Submission #63299010](https://atcoder.jp/contests/abc395/submissions/63299010)

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, q;
int a[1000010];
int b[1000010];
int c[1000010];

int main()
{
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		a[i] = b[i] = c[i] = i;
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x, y;
			cin >> x >> y;
			a[x] = c[y];
		}
		else if (op == 2)
		{
			int x, y;
			cin >> x >> y; 
			int cx = c[x];
			int cy = c[y];
			b[cx] = y; c[y] = cx;
			b[cy] = x; c[x] = cy;
		}
		else
		{
			int x; cin >> x;
			cout << b[a[x]] << endl;
		}
	}
	return 0;
}
```

---

## 作者：Hero_Broom (赞：5)

[AT\_abc395\_d \[ABC395D\] Pigeon Swap 题目链接](https://atcoder.jp/contests/abc395/tasks/abc395_d)

## 题目大意

有标有 $1, 2, \ldots, N$ 的 $N$ 只鸽子和标有 $1, 2, \ldots, N$ 的 $N$ 个鸟巢。

最初，鸽子 $i (1\leq i\leq N)$ 位于鸟巢 $i$ 中。

你将对这些鸽子执行 $Q$ 次操作。

有三种类型的操作：

- 操作 $1$：你将得到整数 $a$ 和 $b(1\leq a\leq N, 1\leq b \leq N)$。将 $a$ 号鸽子移至 $b$ 号鸟巢。

- 操作 $2$：你将得到整数 $a$ 和 $b (1 \leq a \leq b \leq N)$。将鸟巢 $a$ 中的所有鸽子与鸟巢 $b$ 中的所有鸽子交换。

- 操作 $3$：你将得到一个整数 $a(1\leq a \leq N)$。输出鸽子 $a$ 目前所在巢穴的编号。

按操作顺序打印每个操作 $3$ 的结果。

## 题解

### 思路

首先我们很容易想到通过一个数组 `in` 来记录每只鸽子所在的鸟巢，这样子对于每个操作 $1$，我们只需要将 `in[a]` 的值设为 `b` 即可。

但是如果只使用这么一个 `in` 数组，对于操作 $2$，我们就需要遍历每一个在 $a$ 巢和 $b$ 巢的鸽子，但对于如此大的数据，这样显然会超时。

所以我们可以考虑将他们巢的编号交换，这样就可以将时间优化到 $\Theta(n)$ 了。

具体的，我们可以通过样例来看：

```
6 8
1 2 4
1 3 6
3 2
2 4 5
3 2
1 4 2
3 4
3 2
```

在这里，第 $4$ 个操作将 $4$ 号鸟巢和 $5$ 号鸟巢交换。

我们将定义以下两个数组：

- $act_{i}$ 表示 $i$ 个存储空间记录了 $act_{i}$ 号鸟巢；

- $to\_act_{i}$ 表 $i$ 号鸟巢所在的存储空间。

这么说可能有点抽象，我们结合例子来讲解：

```
6 2
2 4 5
2 4 6
3 6
```

对于这组数据：

|         存储空间编号        | $1$ | $2$ | $3$ |  $4$  | $5$ | $6$ |
| :-------------------: | :-: | :-: | :-: | :---: | :-: | :-: |
|          初始值          |  1  |  2  |  3  |   4   |  5  |  6  |
| 第 $1$ 次操作（实际上对应的鸟巢编号） |  1  |  2  |  3  |   5   |  4  |  6  |
|       第 $2$ 次操作       |  1  |  2  |  3  |   6   |  4  |  5  |
|       第 $3$ 次操作       |  1  |  2  |  3  | **6** |  4  |  5  |

所以最后应该输出 `4`，因为 $6$ 号鸽子在鸟巢 $4$ 里面。

#### 第 $1$ 次操作

我们需要交换 $4$ 号巢和 $5$ 号巢，所以现在 $4$ 号存储空间应该存着 $5$ 号巢。相同地，$5$ 号存储空间存着 $4$ 号巢：

$act_{4}=5, act_{5}=4$

接下来更新 $to\_act$ 数组。现在 $4$ 号巢被存在了 $5$ 号存储空间，$5$ 号巢被存在了 $4$ 号存储空间：

$to\_act_{4}=5, to\_act_{5}=4$

---

#### 第 $2$ 次操作

现在我们需要交换 $4$ 号巢和 $6$ 号巢。此时 $4$ 号巢的数据被存在了 $to\_act_{4}=5$ 号存储空间，所以我们实际上需要交换的是 $5$ 号存储空间和 $6$ 号存储空间。

那么这时 $5$ 号存储空间存储的就是 $6$ 号巢的数据，$6$ 号存储空间存储的就是 $4$ 号巢的数据：

$act_{to\_act_{4}}=6, act_{to\_act_{6}}=4$

也就等同于：

$act_{5}=6, act_{6}=4$

接下来，$4$ 号巢的存储空间和 $6$ 号巢的存储空间交换：

$to\_act_{4}=6, to\_act{6}=5$

---

**上面的过程比较绕，建议多看几遍。**

所以我们就可以~~很轻松地~~得到操作 $2$ 的代码：

```cpp
scanf("%d%d",&y,&z);
act[to_act[y]]=z;
act[to_act[z]]=y;
swap(to_act[y],to_act[z]);
```

理解了上面的思路之后，操作 $1$ 和操作 $3$ 的代码就很好实现了，这里就不赘述了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int in[1000010],act[1000010],to_act[1000010],n,q,x,y,z,tmp;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) in[i]=act[i]=to_act[i]=i;//注意初始化
	while(q--){
		scanf("%d",&x);
		if(x==1){
			scanf("%d%d",&y,&z);
			in[y]=to_act[z];
		}else if(x==2){
			scanf("%d%d",&y,&z);
			act[to_act[y]]=z;
			act[to_act[z]]=y;
			swap(to_act[y],to_act[z]);
		}else{
			scanf("%d",&y);
			printf("%d\n",act[in[y]]);
		}
	}
    return 0;
}
```

---

## 作者：Moya_Rao (赞：5)

# 题目大意
给出 $n$ 个球和 $n$ 个盒子，都分别编号为 $1 \sim n$。一开始，球 $i$ 在盒子 $i$ 中。

现在有 $Q$ 次操作，每次操作分如下三种情况：
- 输入 `1 x y`，表示将球 $x$ 从当前盒子中拿出，放进盒子 $y$ 中。
- 输入 `2 x y`，表示互换盒子 $x$ 与盒子 $y$ 中的球。
- 输入 `3 x`，表示询问球 $x$ 当前所处的盒子编号。

现在给出这 $Q$ 次操作，请针对每次询问输出答案。

$1 \le x,y \le n \le 10^6$，$1 \le Q \le 3 \times 10^5$。

更加详细的题面请看[原题](https://atcoder.jp/contests/abc395/tasks/abc395_d)。

# 思路
一看到数据范围就知道只支持 $O(1)$ 或 $O(\log{n})$ 时间回答，所以暴力模拟肯定是行不通的。

咋办？看到这种题我总会想到并查集，看上去，这道题目的确可以用并查集做。但是，仔细想想就会发现，针对操作 $1$，万一我们要拿出来的那个球 $a$ 是它原本待的那个盒子的“代表值”呢？肯定不能直接让它指向盒子 $b$ 那个集合的某个值吧，那就把它原本那个盒子里的球也全部扯过去了。  
那就只能考虑换个点作为“代表值”，可是为了减少并查集的复杂度，一般都是将其建成菊花图的，修改“代表值”的话所有值都得改，那样时间复杂度好像又会爆啊。

怎么办？考虑到“菊花图”的特性，我们干脆用一个不存在的点，比方说 $i+n$ 吧，来表示某个盒子对应的那个集合的“代表值”。不过这个“代表值”可能是假的，也就是说，我们展示出来的“代表值”只是它的一个名称而已，真正的值存在另外一个数组里边。

能理解吗？如果不能，那就来看一下数组的定义吧。

我们定义了三个数组，$now$、$txt$ 以及 $dui$。  
$now_x$ 表示球 $x$ 所待的那个盒子对应的集合的“代表值”的名称；  
$txt_x$ 表示盒子 $x$ 所对应的那个集合的“代表值”的名称；  
而 $dui_x$ 和 $txt_x$ 恰恰相反，表示的是名字为 $x$ 的那个代表值所对应的那个盒子的编号。

定义确实有点绕，但实现起来却非常简单了。接下来接下来我们分析一下每种操作我们都要做什么吧。

首先来看操作 $1$，这种很方便，只需要将球 $x$ 所待的盒子对应的集合的“代表值”名称修改为盒子 $y$ 所对应的那个集合的“代表值”的名称就行了。容易发现其实只是需要将 $now_x$ 的值修改为 $txt_y$。是的，就是这么简单！

那么操作 $2$ 呢？简答简单，我们首先交换两个盒子所对应的那个集合的“代表值”的名称就搞定啦。也就是说，我们需要交换 $txt_x$ 和 $txt_y$。只有这一个步骤吗？不，还有一步。因为 $txt$ 和 $dui$ 一直是相对应的，而我们修改了 $txt_x$ 和 $txt_y$ 的值，因此我们还需要更新 $dui_{txt_x}$ 的值为 $x$，$dui_{txt_y}$ 的值为 $y$。这样就好啦。

操作 $3$ 那可就很轻松了，答案就是球 $x$ 所待的那个盒子所对应的集合的“代表值”对应的真正盒子编号呀！对对对，只需要输出 $dui_{now_x}$ 就行！

嘿嘿，是不是非常简单？相信大家都不需要看代码了吧，哈哈！

# 代码
无论如何我还是会放上代码的，你们想看就看，不过不要抄袭哟。  
别担心，我的代码没有问题，肯定是能够 AC 的，这里是[提交记录](https://atcoder.jp/contests/abc395/submissions/63263806)，这下你非信不可咯。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int n,Q,now[N],txt[N],dui[N];
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++)
        now[i]=i+n,now[i+n]=i+n,txt[i]=i+n,dui[i+n]=i;
    while(Q--){
        int opt,x,y;
        cin>>opt>>x;
        if(opt==1){
            cin>>y;
            now[x]=txt[y];
        }
        else if(opt==2){
            cin>>y;
            swap(txt[x],txt[y]);
            dui[txt[x]]=x,dui[txt[y]]=y;
        }
        else{
            cout<<dui[now[x]]<<"\n";
        }
    }
    return 0;
}
```

如果本篇题解对你有帮助，请你留下一个小小的赞，万分感谢！

---

## 作者：littlebug (赞：4)

太困难了。

不过写场祭的时候突然发现自己错哪了，然后就赛后 7min 过了，也是逆天的。

## Solution

很自然地想到要用一个 dsu 状物，~~然后在 dsu 板子上改了半天发现好像不是 dsu 了~~。

开 $3$ 层点，最底下一层对应的是每只鸽子，第二层层是鸽子对应的**原本的**笼子，第三层是每个笼子在 swap 后所对应的真实笼子。然后记录一个 $t_i$ 表示第三层对应的第二层的点，于是（题面中的 $a,b$ 在这里是 $x,y$）：

- 操作二（swap）：在第三层找点 $x,y$，对应到第二层 $t_x,t_y$ 之后对于这两个点进行重新连边。

- 操作一：先从第三层找 $y$ 对应的点 $t_y$，然后把 $x$ 的边连到 $t_y$ 上。  
注意**不可以**直接第一层向第二层连边，因为在有了 swap 操作之后，这个对应关系是错的。

- 操作三：直接找第一层的点对应的第三层的点即可。

~~看到 $t_y$ 立马想到了天依，没救了，不过也不想有救嘻嘻。~~

## Code

```cpp
int n,q;

class __dsu
{
private:
    int n,fa[MAXN<<2],t[MAXN<<2];

public:
    il void init()
    {
        rep(i,1,n) fa[i]=i+n;
        rep(i,n+1,n<<1) fa[i]=i+n;
        rep(i,(n<<1)+1,n*3) fa[i]=i,t[i]=i-n;
    }
    il void init(int _n) {n=_n,init();}

    il int find(int x) {return x==fa[x] ? fa[x] : find(fa[x]);}

    il void insert(int x,int y)
    {
        fa[x]=t[y+(n<<1)];
    }

    il void swapp(int x,int y)
    {
    	int qwq=t[x+(n<<1)],qaq=t[y+(n<<1)];
    	fa[qwq]=y+(n<<1),fa[qaq]=x+(n<<1);
    	swap(t[x+(n<<1)],t[y+(n<<1)]);
    }
    
    il int q(int x)
    {
        return find(x)-(n<<1);
    }
} d;

signed main()
{
    read(n);

    d.init(n);

    read(q);
    int op,x,y;
    while(q--)
    {
        read(op);
        
        if(op==1) read(x,y),d.insert(x,y);
        else if(op==2) read(x,y),d.swapp(x,y);
        else read(x),write(d.q(x),'\n');
    }

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：2011hym (赞：4)

### 题目理解

我们有 $N$ 只鸽子和 $N$ 个巢。初始时，第 $i$ 只鸽子在第 $i$ 个巢中。接下来会进行 $Q$ 次操作，操作分为三种类型：

- **类型1**：将鸽子 $a$ 从当前巢移动到巢 $b$。
- **类型2**：交换巢 $a$ 和巢 $b$ 中的所有鸽子。
- **类型3**：查询鸽子 $a$ 当前所在的巢的编号。

我们需要对 $Q$ 次操作进行处理，并在每次类型 3 操作时输出鸽子 $a$ 所在的巢的编号。

### 解题思路

直接模拟是必然会爆炸的。为了优化，我们可以引入“标签鸽子”的概念，将问题转化为对标签鸽子的操作。

具体来说，我们可以维护以下三个数组：

1. $v1$：表示每个巢中当前标签鸽子的编号。
2. $v2$：表示每个标签鸽子当前所在的巢的编号。
3. $v3$：表示每只鸽子当前所在的巢的编号。

通过这种方式，我们可以将每次操作转化为对标签鸽子的操作，从而减少更新的次数。

### 操作处理

1. **操作1**：将鸽子 $a$ 移动到巢 $b$。
   - 更新 `v3[a]` 为 `v2[b]` ，即将鸽子 $a$ 所在的巢更新为巢 $b$ 中标签鸽子所在的巢。

2. **操作2**：交换巢 $a$ 和巢 $b$ 中的所有鸽子。
   - 交换 `v2[a]` 和 `v2[b]` ，即交换两个巢中的标签鸽子。
   - 同时更新 `v1` 数组，确保巢 $a$ 和巢 $b$ 中的标签鸽子信息正确。

3. **操作3**：查询鸽子 $a$ 当前所在的巢的编号。
   - 通过 `v3[a]` 找到鸽子 $a$ 所在的巢，然后通过 `v1` 找到该巢中标签鸽子的编号，即为鸽子 $a$ 所在的巢的编号。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
long long N,Q;
int main() {
    cin >> N >> Q;
    vector<long long> v1(N), v2(N), v3(N);
    iota(begin(v1), end(v1), 0U);
    iota(begin(v2), end(v2), 0U);
    iota(begin(v3), end(v3), 0U);//复制粘贴赏心悦目
    for (long long q = 0; q < Q; ++q) {
        long long t;
        cin >> t;
        if (t == 1) {
            long long p, to;
            cin >> p >> to;
            v3[p - 1] = v2[to - 1];
        } else if (t == 2) {
            long long l0, l1;
            cin >> l0 >> l1;
            swap(v2[l0 - 1], v2[l1 - 1]);
            swap(v1[v2[l0 - 1]], v1[v2[l1 - 1]]);
        } else {
            long long p;
            cin >> p;
            cout << v1[v3[p - 1]] + 1 << '\n';
        }
    }
    cout << flush;//这玩意是刷新缓冲区用的
    return 0;
}
```

### 复杂度分析

- **时间复杂度**：每次操作的时间复杂度为 $O(1)$，总时间复杂度为 $O(Q)$。
- **空间复杂度**：使用了三个大小为 $N$ 的数组，空间复杂度为 $O(3N)$。

---

## 作者：niuqichongtian (赞：2)

# blog 内食用更佳
### 思路
> 预提不会先暴力，模拟上来猜题亿。
> 
对于这个题目，首先可以写出一段模拟的代码。但对于操作 2，暴力模拟会超时。  
尝试第一个优化。把每一个巢穴中有哪些鸽子用一个 `vector<int> b[maxn]` 存储，鸽子的位置使用 `int a[maxn]` 存储。超时，发现此时仅将操作 2 时无用的更新优化，继续下一步。  
此时发现 `vector<int>` 对时空消耗比较大，并且删除时（操作一）无法精确定位元素位置，于是替换为 `unordered_set<int>`。  
此时发现应该使用一对关联数组 `int id[maxn], p[maxn]`，其中 `id[i]` 代表 `b[i]` 的真实编号。但此时发现虽然将操作 2 的时间优化了（`swap(id[u], id[v])`），但操作一中我们对鸽子所要去的巢穴在 `b[]` 中的位置无法确定。此时可以用 `p[]` 作为 `id[]` 的逆数组，则完美解决。

### 实现要点
+ 在使用 `vector<int> b[maxn]` 超时后，本蒟蒻第一时间想到了用 `map`，但是又不能 `map<int, void>`，于是使用了 `unordered_set`，注意非必要不使用 `set` 和 `map`，应加上 `unordered` 优化时空复杂度。
+ 注意在最终的优化过后，`a[]` 数组的意义不在于鸽子的真实位置，而是鸽子所在的 `set` 在 `b[]` 中的索引。
  + 如此一来，输出操作时应输出 `id[a[u]]`，而操作 1 时应该把鸽子移到 `b[p[v]]` 中而非 `b[v]`。
+ 注意操作 2 时我们仅对实际位置进行改动而不改动 `b[]`，所以 `id[]` 和 `p[]` 都应该更新状态。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1e6+7;
int n, q;
int a[maxn];
unordered_set<int> b[maxn];
int id[maxn];
int p[maxn];

signed main(signed argc, char const * argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int op, u, v;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        p[i] = id[i] = a[i] = i, b[i].insert(i);
    while (q--) {
        cin >> op >> u;
        if (op == 3)
            cout << id[a[u]] << endl;
        else {
            cin >> v;
            if (op == 1) {
                b[a[u]].erase(u);
                a[u] = p[v];
                b[a[u]].insert(u);
            }
            else {
                swap(  id[p[u]] ,   id[p[v]] );
                swap(p[id[p[u]]], p[id[p[v]]]);
            }
        }
    }
    return 0;
}
```

---

## 作者：Hughpig (赞：1)

发现直接维护编号变化不是很容易。

考虑记录数组 $from$ 表示当前编号的鸽笼在最初的编号，数组 $to$ 表示最初编号的鸽笼目前的编号，数组 $fa$ 表示某只鸽子所在鸽笼在最初的编号。

操作 $1$ 要把鸽子 $a$ 移到鸽笼 $b$，那么鸽子 $a$ 接下来所在的鸽笼最初的编号就是 $from_b$。直接 $fa_a\leftarrow from_b$ 即可。

操作 $2$ 要交换鸽笼 $a$ 和 $b$，那么鸽笼 $a$ 初始编号接下来映射的目前的编号就是 $b$，鸽笼 $b$ 初始编号接下来映射的目前的编号就是 $a$。然后还要交换鸽笼 $a$ 和 $b$ 的初始编号。

对于操作 $3$ 要查询一只鸽子的所在鸽笼，直接输出它所在的鸽笼的最初编号映射到当前编号即可，即 $from_{fa_i}$。

注意一开始要初始化所有的 $from_i=to_i=fa_i=i$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)

constexpr int N=1e6+9;

ll n,q,to[N],from[N],fa[N],op,a,b;

int main()

	cin>>n>>q;
	up(1,n,i)from[i]=to[i]=fa[i]=i;
	while(q--){
		cin>>op>>a;
		if(op==1){
			cin>>b;
			fa[a]=from[b];
		}
		else if(op==2){
			cin>>b;
			to[from[a]]=b,to[from[b]]=a;
			swap(from[a],from[b]);
		}
		else cout<<to[fa[a]]<<'\n';
	}
	return 0;
}
```

---

## 作者：PDAFX (赞：1)

## 题目大意

鸽子 $1,$ 鸽子 $2,\ldots,$ 鸽子 $N$ 的 $N$ 羽毛鸽子和巢 $1,$ 巢 $2,\ldots,$ 巢 $N$ 有 $N$ 个巢。

有三种操作：

\- 类型 $1$：给出整数 $a,b$ $(1\leq a\leq N,1\leq b\leq N)$。将鸽子 $a$ 从巢中取出，移至巢 $b$。

\- 类型 $2$：给出整数 $a,b$ $(1\leq a\lt b\leq N)$。将巢 $a$ 内的鸽子全部移到巢 $b$，将巢 $b$ 内的鸽子全部移到巢 $a$。这些 $2$ 的移动是同时进行的。

\- 类型 $3$：给出整数 $a$ $(1\leq a\leq N)$。鸽子 $a$ 报告现在所在的巢的编号。

问结果。

## 思路

起初，我们很容易想到一种错误的做法，给每个巢穴设立一个真实巢穴，这个的反例也很简单，第三组样例就会错。

例如，
28->30
30->7

当你按照上述思路时，会输出 30，正确应当输出 7。

所以，我们设置第二个映射，记录下第二个标签鸽子的巢号。按照上述步骤即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,opt,x,y,m,fa[1000001],fa1[1000001],fa2[1000001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		fa[i]=fa1[i]=fa2[i]=i;
	}
	cin>>m;
	while(m--)
	{
		cin>>opt>>x;
		if(opt==1)
		{
			cin>>y;
			fa[x]=fa1[y];
//			fa1[x]=fa1[y];
		}
		if(opt==2)
		{
			cin>>y;
//			xiu[fa1[x]]=xiu[fa1[y]]=m;
			swap(fa1[x],fa1[y]);
			swap(fa2[fa1[x]],fa2[fa1[y]]);
		}
		if(opt==3)
		{
			cout<<fa2[fa[x]]<<endl;
		}
	}
}
```

---

## 作者：jackson_cao (赞：1)

## 题目大意
有 $n$ 只鸽子和 $n$ 个鸽巢，初始时第 $i$ 只鸽子在第 $i$ 个鸽巢里，要你实现以下操作：     
1.把第 $a$ 只鸽子放到第 $b$ 个鸽巢里。  
2.交换第 $a$ 个鸽巢和第 $b$ 个鸽巢里的鸽子。  
3.查询第 $a$ 只鸽子在哪个巢中。   
## 解题思路
赛时我第一时间想到的是开一个数组 $p$ 来存储每个鸽子在哪个鸽巢中。但很明显，这样搞操作2的时间复杂度为 $O(n)$ ，对于 $10^6$ 的数据范围肯定是无法接受的。  
这个时候，我就灵机一动，我们可以使用映射的方式来解决操作2的问题。  
我们开一个数组 $xu$ （数组名不是重点），$xu_i$ 表示标号为 $i$ 的“虚巢”对应了编号为 $xu_i$ 的“实巢”。这样速度快到飞起，可以在 $O(1)$ 的时间复杂度内轻松完成操作2，具体实现也很简单，只要交换原本对应 $a$ 号巢和 $b$ 号巢的“虚巢”就行了。  
当然，为了方便操作，我们还需要建立一个数组 $shi$ (数组名不是重点)， $shi_i$ 表示编号为 $shi_i$ 的“虚巢”对应了编号为 $i$ 的“实巢”。
## 代码实现
废话不多说，直接上代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
int n,q;
int p[MAXN],shi[MAXN],xu[MAXN];
//要注意这里p[i]存的是虚巢编号
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        p[i]=i;
        shi[i]=i;
        xu[i]=i;
    }
    for(int i=1,opt,a,b;i<=q;i++){
        cin>>opt>>a;
        if(opt==1){
            cin>>b;
            p[a]=shi[b];
        }
        if(opt==2){
            cin>>b;
            swap(xu[shi[a]],xu[shi[b]]);
            swap(shi[a],shi[b]);
            //注意这里shi[]的数据也要修改
        }
        if(opt==3) cout<<xu[p[a]]<<"\n";
    }
    return 0;
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc395_d [ABC395D] 交换鸽子 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc395_d)

### 题目大意

$N$ 只鸽子 $N$ 个巢，三种操作：

- 把 $a$ 鸽子放入 $b$ 巢。

- 交换 $a$、$b$ 两巢内所有鸽子。

- 问 $a$ 鸽子在那个巢。

### 思路

第一和第三操作可以用 `home` 数组直接记录和维护，二操作如果暴力进行势必超时。注意到二操作和一三没有直接影响，可以在 `home` 之后再加一个映射，并添加对应的反映射。

唯一需要注意的是二操作不要把自己绕晕了，因为已经交换的两个有可能会交换，所以不要惯性认为一开始映射都是直的这里也写成原数了，要用反映射回去。

比如把 $a$ 和 $b$ 的映射交换，先找到映射到 $b$ 的，将之指向 $a$，再把映射到 $a$ 的，指向 $b$，并维护数组即可。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, Q, op, a, b;
int home[1000005], remap[1000005], bamap[1000005];
int main()
{
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
	{
		home[i] = i;
		remap[i] = i;
		bamap[i] = i;
	}
	for (int i = 1; i <= Q; i++)
	{
		scanf("%d%d", &op, &a);
		if (op == 1)
		{
			scanf("%d", &b);
			home[a] = bamap[b];
		}
		else if (op == 2)
		{
			scanf("%d", &b);
			remap[bamap[b]] = a;
			int tmp = bamap[a];
			bamap[a] = bamap[b];
			remap[tmp] = b;
			bamap[b] = tmp;
		}
		else
			printf("%d\n", remap[home[a]]);
	}
	return 0;
}
```

---

## 作者：guaidaokenan (赞：0)

## 题目大意
有 $n$ 个鸽子和鸽子的巢穴，第 $i$ 号在第 $i$ 个巢穴中。现在有三种操作：第一种：将鸽子 $a$ 从当前巢中取出，移到巢 $b$ 中；第二种：将巢 $a$ 中的所有鸽子移动到巢 $b$，并将巢 $b$ 中的所有鸽子移动到巢 $a$。这两次移动同时进行。第三种：给你一个整数 $a$。$1 \le a \le n$ 鸽子 $a$ 报告它目前所在巢的标签。
## 大体思路
第一种和第三种都很容易想到怎么维护（用数组来直接记录即可），只有第二种较为特殊。如果第二种采用暴力的话肯定会超时！！！发现第二种是将两个巢穴中的所有鸽子交换，就可已将巢穴的编号交换，比如将 $1$ 号和 $2$ 号交换，既可以将 $1$ 号巢穴的编号设为 $2$，同理将 $2$ 号的编号设为 $1$。现在就能用常数级的时间复杂度来解决本题目。
## 给出代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1000005];
int b[100005];
int s[1000005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++){
		a[i]=i;
		s[i]=i;
		b[i]=i;
	}
	for(int i=1; i<=m; i++){
		int p;
		int x,y;
		scanf("%d",&p);
		if(p==1){
			scanf("%d%d",&x,&y);
			s[x]=b[y];//改变位置 
		}
		else if(p==2){
			scanf("%d%d",&x,&y);
			a[b[x]]=y;
			a[b[y]]=x;
			swap(b[x],b[y]);//对编号进行交换 
		}
		else{
			scanf("%d",&x);
			printf("%d\n",a[s[x]]);
		}
	}
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

似乎有些水的一道 D 呢。
### 思路
考虑用一些数组进行维护。

定义 $w_i$ 为第 $i$ 只鸽子现在在哪个笼子。

观察操作可以发现，操作 $1$ 是改变一只鸽子现在的位置，而操作 $2$ 是将两个笼子里的鸽子交换。如果只用 $w_i$ 进行维护的话，进行操作 $2$ 时会非常麻烦。那么，我们可以将“第 $i$ 个笼子”和“编号为 $i$ 的笼子”分开。

这么说可能有点抽象，解释一下：假设一开始第 $i$ **个**笼子的编号为 $i$。定义 $x_i$ 为第 $i$ **个**笼子现在的编号，$now_i$ 为编号为 $i$ 的笼子现在是第几个。

- 在进行操作 $1$ 时，我们不将 $w_a$（即被操作的那只鸽子）指向第 $b$ 个笼子，而是指向编号为 $b$ 的笼子，即 $w_a = now_b$。

- 在进行操作 $2$ 时，直接将编号为 $a$ 和 $b$ 两个笼子的编号交换，即交换 $now_a$ 和 $now_b$。注意 $now_a$ 和 $now_b$ 在 $x$ 中对应的值也要交换。

- 进行操作 $3$ 时，求 $w_a$ 指向的笼子的编号，即求 $x_{w_a}$。

tip：$w_i$、$x_i$、$now_i$ 的初始值都为 $i$。

然后这道题就解决了。
### 代码
```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=1e6+5,INF=1e9;
int n,q,op,a,b,wh[N],x[N],now[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		wh[i]=i,x[i]=i,now[i]=i;
	}
	while(q--){
		cin>>op;
		if(op==1){
			cin>>a>>b;
			wh[a]=now[b];
		}else if(op==2){
			cin>>a>>b;
			swap(now[a],now[b]),swap(x[now[a]],x[now[b]]);//now 和 x 都需要交换，想想为什么
		}else{
			cin>>a;
			cout<<x[wh[a]]<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Ybw0731 (赞：0)

## 前言
本人在赛时被思维定式，导致没做出来。
## 思路
首先，我们对于操作一可以直接用一个数组映射每个鸽子所在的鸽笼，接下来对于操作二。我们只需要再用一个数组表示每个映射的鸽笼，但这样新的问题又出现了，又得去找一遍所有的去找对应的鸽笼，这样时间复杂度再次变高。


这该怎么办呢？


我们这时应该再开一个数组，来吧映射的数组反过来存，这样就可以避免操作二时间复杂度变高的问题。


对于操作三，我们就可以根据映射的来就行了。


[AC 代码](https://atcoder.jp/contests/abc395/submissions/63336331)

---

## 作者：The_foolishest_OIer (赞：0)

一道很绕的题，借助草稿纸画几下就出来了。

定义 `from[a]` 表示鸽子 $a$ 的所属鸽笼，`id[a]` 表示鸽笼 $a$ 实际是哪个鸽笼，`now[a]` 表示真正的鸽笼 $a$ 在第几个鸽笼。

Q：为什么要定义这些东西。

A：注意到操作二，如果暴力修改复杂度最坏可达到 $O(n)$。

对于第一种操作，直接使 `from[a] = now[b]` 即可。

对于第二种操作，交换两个 `id` 和 `now` 即可。

对于第三种操作，输出 `id[from[a]]`。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define endl '\n'
const int N = 1e6 + 10;
const int inf = 1e16;
const int mod = 1e9 + 7;
int n,q;
int id[N],from[N],now[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> n >> q;
	for (int i = 1 ; i <= n ; i++){
		id[i] = i;
		now[i] = i;
	}
	for (int i = 1 ; i <= n ; i++) from[i] = i;
	while (q--){
		int op;
		cin >> op;
		if (op == 1){
			int a,b;
			cin >> a >> b;
			from[a] = now[b];
		}else if (op == 2){
			int a,b;
			cin >> a >> b;
			swap(id[now[a]],id[now[b]]);
			swap(now[a],now[b]);
		}else{
			int a;
			cin >> a;
			cout << id[from[a]] << endl;
		}
	}
	return 0;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc395_d)

[AtCoder 题目传送门](https://atcoder.jp/contests/abc395/tasks/abc395_d)

### 题目大意
有 $N$ 只标有 $1, 2, \ldots, N$ 的鸽子和 $N$ 个标有 $1, 2, \ldots, N$ 的鸽巢。

最初，鸽子 $i$ 在巢 $i$ 中，我们现在对这些鸽子执行 $Q$ 操作。

操作有三种：

- 类型 $1$：将鸽子 $x$ 从当前鸽巢中取出，并将其移至鸽巢 $y$。
- 输入 $2$：将巢 $x$ 中的所有鸽子移动到巢 $y$，并同时将巢 $y$ 中的所有鸽子移动到巢 $x$。
- 输入 $3$：给你一个整数 $x$。输出鸽子 $x$ 目前所在巢的编号。

### 解题思路
注：
- 下文所提到的“逻辑巢穴编号”为：每个鸽子看到的虚拟巢穴编号。
- 下文所提到的“物理巢穴编号”为每个逻辑巢穴对应的实际巢穴编号。

由于数据规模较大，直接模拟每个操作会导致时间复杂度过高，因此我们需要采用**间接映射**的方法来优化。

我们定义 $a$ 数组为当前每个鸽子所在的逻辑巢穴编号，$b$ 数组为每个逻辑巢穴对应的物理巢穴编号。

现在对于每种操作就很容易了：

类型1：将鸽子移动到目标逻辑巢穴，即 `a[x]=y`。

类型2：交换两个逻辑巢穴对应的物理巢穴，也就是 `swap(b[x],b[y])`。

类型3：输出鸽子的实际物理位置 `b[a[x]]`。

这种方法将所有操作的时间复杂度降为 $\mathcal O(1)$，总时间复杂度 $\mathcal O(q)$，满足题目的要求。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int n,q,a[N],b[N],op,x,y;
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) a[i]=b[i]=i;
    while(q--){
        cin>>op;
        if(op==1){
            cin>>x>>y;
            a[x]=y;
        }
		if(op==2){
            cin>>x>>y;
            swap(b[x],b[y]);
        }
		if(op==3){
            cin>>x;
            cout<<b[a[x]]<<endl;
        }
    }
}
```

---

## 作者：cyq32ent (赞：0)

现在我们有 $N$ 只鸽子，下面我们进行两种操作之一：

- 把第 $i$ 只鸽子移到 $j$ 笼子；
- 交换 $i$ 和 $j$ 两只笼子。

这看起来是一个数据结构题，但是实际上——你不用真的交换两只笼子。

考虑一个简单得多的问题：现在你在写寒假作业，在答题纸上抄参考答案的时候把两道题写反了，应该怎么做？显然，只要把题号改掉即可。同理，我们遇到第二种操作的时候，只需要把笼子的编号交换一下就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,Q,n[1001010],p[1001010],m[1001010];
int main(){
	cin>>N>>Q;
	for(int i=1;i<=N;i++)p[i]=n[i]=m[i]=i;
	for(int op,a,b;Q--;){
		cin>>op>>a;
		if(op!=3)cin>>b;
		if(op==1)p[a]=n[b];
		if(op==2){
			int i=n[a],j=n[b];
			swap(m[i],m[j]),n[m[i]]=i,n[m[j]]=j;
		}
		if(op==3)cout<<m[p[a]]<<endl;
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

熟悉的题目......

菜死了，赛时 T 了两发！菜死了，赛时 T 了两发！菜死了，赛时 T 了两发！

考虑使用前缀和进行维护。

首先考虑操作一：发现，其实并不需要直接更换，用前缀和数组记录即可。

考虑操作二：找到数组中下标 $a$ 的位置，找到数组中下标 $b$ 的位置，使用 `swap` 交换即可。

考虑操作三：输入直接输出对应的位置。

### 代码实现

```cpp
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

#define unmap unordered_map
#define unset unordered_set
#define muset multiset
#define ll long long
#define unint unsigned int
#define ull unsigned ll
#define please return
#define AC 0
#define il inline
#define cst const
#define db double
#define ld long db
#define pii pair<int,int>
#define pll pair<ll,ll>

#define str string


#define int long long

using namespace std;

cst ll INF = 9223372036854775807;
cst int inf = 2147483647;
cst int xinf = 0x3f3f3f3f;
cst ll XINF = 0x3f3f3f3f3f3f3f3fll;
cst db pi = acos (-1.0), eps = 1e-12;

cst int MAXN = 50 + 10;
cst int mod = 11;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)

il int _abs (int a) { if (a < 0) return -a; return a; }
il int _pow (int a, int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }

int read () { int sum = 0, f = 1; char ch; ch = getchar (); while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar ();} while (ch >= '0' && ch <= '9') {  sum = sum * 10 + ch - '0'; ch = getchar ();} return sum * f;}
void print (int x) { if (x < 0) { putchar ('-'); x = -x;} if (x > 9) print (x / 10); putchar (x % 10 + '0'); return ;}


// ------------------------------
signed main () {
    
    
    int N, Q;
    cin >> N >> Q;
    
    vector <int> base (N + 1), tau (N + 1), iv (N + 1);
    
    rep(i, 1, N) base[i] = tau[i] = iv[i] = i;     
    
   while (Q --) {
        int type;
        cin >> type;
        if (type == 1) { 
            int a, b;
            cin >> a >> b;
            base[a] = iv[b];
        } 
		else if (type == 2) { 
            int a, b;
            cin >> a >> b;

            int p = iv[a], q = iv[b];
            swap (tau[p], tau[q]);
            swap (iv[a], iv[b]);
        } 
		else if (type == 3) { 
            int a;
            cin >> a;
            cout << tau[base[a]] << endl; 
        }
    }    
    
	please AC;
}
```

---

## 作者：__youzimo2014__ (赞：0)

# 思路

首先这道题如果没有操作 $2$，那么只需要存储每一只鸽子所在的巢穴即可。

问题来了，怎么进行操作 $2$？

朴素算法：把每一只在 $a$ 巢穴的鸽子所在巢穴编号改为 $b$，在 $b$ 巢穴的鸽子同理。

把每一只在 $a$ 巢穴的鸽子所在巢穴编号改为 $b$，你会想到什么？

没错，指针。

我们只需要把每一个鸽子指向一个巢穴，在交换的时候将两个巢穴的编号交换即可。

我们还需要维护每一个编号所对应的巢穴指针。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct Nest {
    int id;
    Nest(int id_) {
        id = id_;
    }
};
Nest *nests[N]; // nests[i] 表示第 i 个巢穴。
Nest *where[N]; // where[i] 表示第 i 只鸽子所在的巢穴。
int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        nests[i] = where[i] = new Nest(i);
    }
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int a, b; cin >> a >> b;
            where[a] = nests[b];
        } else if (op == 2) {
            int a, b; cin >> a >> b;
            nests[a] -> id = b;
            nests[b] -> id = a;
            swap(nests[a], nests[b]);
        } else {
            int a; cin >> a;
            cout << where[a] -> id << endl;
        }
    }
    return 0;
}
```

---

