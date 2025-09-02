# [Algo Beat Contest 002 B] Bicycle Competition

## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|   $\text{B - Bicycle Competition}$    | $200$ |   [AFO_orchardist](https://www.luogu.com.cn/user/347582)   |  [zhoumurui](https://www.luogu.com.cn/user/305928)    |  [zhoumurui](https://www.luogu.com.cn/user/305928)    |   [DHeasy](https://www.luogu.com.cn/user/528325)   | [Link](https://www.luogu.com.cn/article/bm2d69jz) by [zhoumurui](https://www.luogu.com.cn/user/305928) |

南极洲企鹅语学校的自行车大赛要开始了！

## 题目描述

比赛共有 $N$ 位企鹅参与，每位选手当前的排名为 $A_i$。比赛中有 $Q$ 个事件发生：

`1 x`：编号为 $x$ 的选手超过了前面一位选手。如果该选手此时已经是第一名，则忽略该操作。

`2 x`：询问排名为 $x$ 的选手编号。

`3 x`：询问编号为 $x$ 的选手排名。

## 说明/提示

**【数据范围】**

- $1\le N,Q\le 2 \times 10^5$。
- $A_i$ 是 $1$ 到 $N$ 的一个排列。
- 对于每个操作，$op\in\{1,2,3\},1\le x \le N$。

## 样例 #1

### 输入

```
4 7
2 1 4 3
2 1
1 1
3 3
2 1
1 1
1 4
3 4
```

### 输出

```
2
4
1
2
```

# 题解

## 作者：weifengzhaomi (赞：5)

题目意思不讲了。

## 思路

我们用两个数组分别记录第几名是第几号选手和第几号选手是第几名。

有三种操作。

对于第一种，如果这个选手已经是第一名，直接跳过。

否则，把他与前一名选手调换位置。

对于第二种，输出第一个数组的值。

对于第三种，输出第二个数组的值。

所以，直接模拟即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],b[200010],n,t,op,x,y;
int main(){
	scanf("%d%d",&n,&t);
	for (int i = 1;i <= n;i++) scanf("%d",&a[i]),b[a[i]] = i;
	while (t--){
		scanf("%d%d",&op,&x);
		if (op == 1){
			if (a[x] == 1) continue;
			y = a[x],swap(b[y],b[y - 1]),a[b[y]] = y,a[b[y - 1]] = y - 1;
		} else if (op == 2) printf("%d\n",b[x]);
		else printf("%d\n",a[x]);
	}
}
```

---

## 作者：zhoumurui (赞：5)

### 题面展示

自行车比赛中有 $N$ 位选手，每位选手当前的排名为 $A_i$。比赛中有 $Q$ 个事件发生：

`1 x`：编号为 $x$ 的选手超过了前面一位选手。如果该选手此时已经是第一名，则忽略该操作。

`2 x`：询问排名为 $x$ 的选手编号。

`3 x`：询问编号为 $x$ 的选手排名。

### 解题思路

考虑维护排名为 $i$ 的选手编号 $P_i$。

在修改操作时，如 $A_x = 1$，什么都不用改，我们在接下来的推导中假设 $A_x > 1$。注意到可以 $O(1)$ 得到给出编号的选手**前面**那位选手的编号，那就是 $P_{A_x-1}$。

那么直接交换一下，然后更新两名选手的排名。

查询随便查。


### 代码展示

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],p[200005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    for (int i=1;i<=n;i++)cin>>a[i],p[a[i]]=i;
    while (q--){
        int op,x;
        cin>>op>>x;
        if (op==1){
            if (a[x]==1)continue;
            int rnk=a[x];
            swap(p[rnk],p[rnk-1]);
            a[p[rnk]]=rnk;
            a[p[rnk-1]]=rnk-1;
        }
        else if (op==2){
            cout<<p[x]<<"\n";
        }
        else{
            cout<<a[x]<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12715)
## 前言
没打比赛，前来水题解。
## 思路
模拟题，按题意模拟即可。

需要注意的点：

- 如果编号为 $x$ 选手此时已经是第一名，则忽略 $op=1$ 的操作。
- 操作 $2$ 和操作 $3$ 的内容不一样，一个输出“排名为 $x$ 的选手编号”，一个输出“编号为 $x$ 的选手排名”。

所以，我们要开一个 $id$ 数组来保存编号。

定义 $id_i$ 表示排名为 $i$ 的选手的编号。

最后模拟即可。

操作 $2$ 和操作 $3$ 单纯输出，就不讲了。

操作 $1$ 其实就是把编号为 $x$ 的选手的排名与他前一个选手的**排名**交换，所以会有些繁琐。但也很简单，把这两个选手的编号和排名都更新一下就可以了。

直接写代码吧。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,a[N],id[N];
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",a+i),id[a[i]]=i;//id[i] 用来保存排名为 i 的选手的编号 
	while(q--){//操作 
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1){
			//需要更新 a[] 和 id[]
			int pm=a[x];//记录排名 
			if(pm==1) continue;//排名第一不用操作 
            swap(id[pm],id[pm-1]);//交换排名 
            a[id[pm]]=pm;
            a[id[pm-1]]=pm-1; 
		}
		else if(op==2) printf("%d\n",id[x]);
		else printf("%d\n",a[x]);
	}
	return 0;
}
```
撒花。

---

## 作者：LiJunze0501 (赞：4)

先读题：  
三个操作  
`1 x`：编号为 $x$ 的选手超过了前面一位选手。如果该选手此时已经是第一名，则忽略该操作。  
`2 x`：询问排名为 $x$ 的选手编号。  
`3 x`：询问编号为 $x$ 的选手排名。  
这里定义两个数组，$rti_i$ 表示排名第 $i$ 名的选手，$itr_i$ 表示第 $i$ 名选手的排名。  

---
先看后两个操作：  
`2 x`：直接输出 $rti_x$；  
`3 x`：直接输出 $itr_x$；  
再看第一个操作：  
用 $rkx$ 记录一下换之前 $x$ 的排名 $itr_x$，如果 $rkx$ 是 1，跳过。和他换的人的排名就是 $rkx-1$，记为 $rky$。那 $y$ 的就是 $rti_{rky}$。  

---
然后进行交换：  
* $x$ 的排名就是 $rky$；  
* 排在 $rky$ 名的就是 $x$；  
* $y$ 的排名就是 $rkx$；  
* 排在 $rkx$ 名的就是 $y$；  
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int rti[200005]/*排名第 i 名的选手*/,itr[200005]/*第 i 名选手的排名*/;
int main(){
    cin>>n>>q;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        itr[i]=x;
        rti[x]=i;
    }
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            int rkx=itr[x];
            if(rkx==1) continue;
            int rky=rkx-1;
            int y=rti[rky];
            itr[x]=rky;
            rti[rky]=x;
            itr[y]=rkx;
            rti[rkx]=y;
        }
        if(op==2) cout<<rti[x]<<"\n";
        if(op==3) cout<<itr[x]<<"\n";
    }
}
```

---

## 作者：封禁用户 (赞：2)

# [P12715 [Algo Beat Contest 002 B] Bicycle Competition](https://www.luogu.com.cn/problem/P12715)
## 题目介绍
1. 输入原来排名。
2. 输入事件，一共三种。
3. 如果是一事件，上升排名。
4. 二事件，输出编号即可。
5. 三事件，输出排名即可。

## 思路
二三事件很简单，重要的是一事件。

可以新建一个数组 $b$，用来保存排名。

在开始一事件后，交换在他前面一人的排名。但是注意 $a$ 与 $b$ 两个数组都需要改动。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q, op, x;

const int N = 200010;

int a[N], b[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[a[i]] = i;
	}
	while (q--) {
		cin >> op >> x;
		if (op == 1){//一事件
            if (a[x] == 1) {
            	continue;
			}
			int xy = a[x];
            swap(b[xy], b[xy-1]);
            a[b[xy]] = xy;
            a[b[xy - 1]] = xy - 1;
        }
        else if (op == 2){//二事件
            cout << b[x] << endl;
        }
        else {//三事件
            cout << a[x] << endl;
        }
	}
	return 0;
}
```
谢谢观看，求过。

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[P12715 [Algo Beat Contest 002 B] Bicycle Competition](https://www.luogu.com.cn/problem/P12715)

### 解题思路

我们维护 $a_x$ 代表第 $x$ 位选手的排名，$p_x$ 代表排名为 $x$ 的选手编号，则可以 $O(1)$ 回答两种询问。

怎么修改呢？假设选手 $x$ 前面的是选手 $y$，则发现 $y=p_{a_x-1}$。如果 $a_x \neq 1$ 则交换 $a_x,a_y$ 与 $p_x,p_y$，相当于把他们的位置调换了。

### 代码实现

```cpp
#include<iostream>
using namespace std;
int n,q,a[200005],p[200005];
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        p[a[i]]=i;
    }
    while(q--){
        short op;
        int x,y;
        cin>>op>>x;
        if(op==1){
            if(a[x]==1)continue;
            y=p[a[x]-1];
            swap(a[x],a[y]);
            swap(p[a[x]],p[a[y]]);
        }
        else if(op==2)cout<<p[x]<<'\n';
        else cout<<a[x]<<'\n';
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/219728474)。

---

## 作者：GeorgeDeng (赞：2)

调了半天。

## Solution

这里为了方便查询操作，我们使用两个数组 $rk1$ 和 $rk2$ 记录排名。$rk1_i$ 表示排名为 $i$ 的编号，$rk2_i$ 表示编号为 $i$ 的排名。

一开始，输入的是最开始第 $i$ 名选手的排名，也就是 $rk2$，我们计算 $rk1$ 的时候就是 $rk1_{rk2_i} \larr i$，这里应该不用讲了。

对于每次操作：

- 操作一：修改操作，输入 $x$ 之后，我们先算出来他的前一个是哪个人，然后根据定义修改。这里比较迷糊，因为比较抽象，但是写纸上就比较清晰。
- 操作二：查询操作，输入 $x$ 之后，输出 $rk1_x$ 就可以了。
- 操作三：查询操作，输入 $x$ 后，输入 $rk2_x$ 就可以了。

整体而言，这道题有点抽象，具体参考代码。

## code

```cpp
#include <iostream>
using namespace std;

int n,q;
int rk1[200005];
int rk2[200005];
void change(int x){//单独写一个函数
    int front_id = rk1[rk2[x]-1];//计算出前一个人的编号
    rk1[rk2[x]] = front_id;//更改原来排第 rk2[x] 的人变成 front_id
    rk1[rk2[front_id]] = x;//同上
    rk2[front_id]++;//排名更换
    rk2[x]--;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i = 1;i<=n;i++){
        cin>>rk2[i];
        rk1[rk2[i]] = i;
    }
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            if(rk2[x]==1) continue;//注意特判
            change(x);
        }else if(op==2){
            cout<<rk1[x]<<endl;//直接输出
        }else{
            cout<<rk2[x]<<endl;//直接输出
        }
        /*for(int i = 1;i<=n;i++){
        	cout<<rk2[i]<<' ';
		}
		cout<<endl;*/
    }
    return  0;
}
```

---

## 作者：zhouxiaodong (赞：2)

# 思路
为了解决这个问题，我们可以使用一个数组来存储每个选手的排名，以及一个数组来存储每个排名对应的选手编号。这样，我们就可以根据事件的类型和参数，快速地进行相应的操作和查询。

读取选手数量 $N$ 和事件数量 $Q$。读取每个选手的初始排名，并根据排名初始化两个数组：一个用于存储每个选手的排名（$rank$），另一个用于存储每个排名对应的选手编号（$id$）。

对于每个事件，根据事件类型进行相应的操作：
如果事件类型为 $1$，表示某个选手超过了前一名选手。我们需要更新该选手和前一名选手的排名，以及相应的数组。
如果事件类型为 $2$，表示询问某个排名的选手编号。我们可以直接从 $id$ 数组中获取答案。
如果事件类型为 $3$，表示询问某个选手的排名。我们可以直接从 $rank$ 数组中获取答案。
# AC Code
``````````cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,q;
	cin>>n>>q;
	int rank[n],id[n];// 定义两个数组来存储排名和选手编号
	for(int i=0;i<n;i++)
	{
		cin>>rank[i];
		rank[i]--;// 将排名转换为0-based索引
		id[rank[i]]=i+1;// 将选手编号转换为1-based索引
	}
	while(q--)
	{
		int op,x;
		cin>>op>>x;
		if(op==1)
		{
			if(rank[x-1]==0)// 如果选手已经是第一名，则忽略该操作
			{
				continue;
			}
			int prev=rank[x-1]-1;// 前一名选手的排名
		    rank[x-1]=prev;// 更新选手的排名
		    rank[id[prev]-1]++;// 更新前一名选手的排名
			int temp=id[prev];// 交换选手编号
			id[prev]=id[prev+1];
			id[prev+1]=temp;
		}
		else if(op==2)
		{
			cout<<id[x-1]<<endl;// 输出排名为x的选手编号
		}
		else if(op==3)
		{
			cout<<rank[x-1]+1<<endl;// 输出选手x的排名，并转换为1-based索引
		}
	}
    return 0;
}
``````````

---

## 作者：Cake_W (赞：1)

# 洛谷P12715题解
[题目传送门](https://www.luogu.com.cn/problem/P12715)
## 思路
我们可以模拟整个过程。定义一个结构体数组，分别存储排名和编号。当 $op=1$ 时，先判断 $x$ 是否等于一，如果不是，就根据题意来模拟，将两数交换位置并更新排名即可。其他情况直接输出答案即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node{
	int p,idx;
}a[N];
int n,q;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].p;
		a[a[i].p].idx=i; 
	}
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		if(x==1)
		{
			if(a[y].p!=1)
			{
				swap(a[a[y].p].idx,a[a[y].p-1].idx);//交换两数位置 
				a[a[a[y].p].idx].p=a[y].p;//更新排名 
				a[a[a[y].p-1].idx].p=a[y].p-1;//更新排名 
			}
		}
		else if(x==2)
		{
			cout<<a[y].idx<<endl;//输出排名为x的选手编号 
		}
		else
		{
			cout<<a[y].p<<endl;//输出编号为x的选手排名 
		}
	}
	return 0;
} 
```

---

## 作者：AFO_Lzx (赞：0)

根据题意模拟即可，建议评橙。

考虑维护当前第 $i$ 个选手的排名 $a_i$，当前第 $i$ 个选手的排名 $b_i$。则：

- 当输入 `2 x` 时输出 $b_x$。
- 当输入 `3 x` 时输出 $a_x$。

考虑修改操作如下：

- 当 $a_x=1$ 时忽略不计。
- 否则将 $b_{a_x}$ 与 $b_{a_{x-1}}$ 交换，即为将排名为 $a_x$ 和 $a_{x+1}$ 的两个选手交换一下，最后利用 $b$ 数组再更新一下 $a$ 数组即可。

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;

const int N = 2e5 + 5;
int n, q, a[N], b[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = x;
		b[x] = i;
	}

	while (q--) {
		int op, x;
		cin >> op >> x;
		if (op == 1) {
			int rk = a[x];
			if (rk == 1) continue;
			swap(b[rk], b[rk - 1]);
			a[b[rk]] = rk;
			a[b[rk - 1]] = rk - 1;
		} 
		else if (op == 2) cout << b[x] << '\n';
		else cout << a[x] << '\n';
	}
	
	return 0;
}
```

---

## 作者：_seven_7k_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12715)
## 思路
这是一道比较简单的模拟题。我们可以定义一个数组 $a$，$a[i]$ 意义为第 $i$ 位选手的排名。我们再定义一个数组 $b$，$b[i]$ 的意义为排名第 $i$ 的选手编号。这样，我们就可以很轻松实现交换排名和找到对应选手排名或找到对应选手编号。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001];
int main(){
	int n,m;
	cin>>n>>m;
	int i;
	for(i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=i;
	}
	for(i=1;i<=m;i++){
		int u,x;
		cin>>u>>x;
		if(u==1 && a[x]!=1){
			a[x]-=1;
			a[b[a[x]]]+=1;
			
			b[a[x]+1]=b[a[x]];
			b[a[x]]=x;
		}
		else if(u==2){
			cout<<b[x]<<endl;
		}
		else if(u==3){
			cout<<a[x]<<endl;
		}
	}
	return 0;
}

```

---

## 作者：glass_goldfish (赞：0)

水题。
### 解题思路
考虑维护两个数组，$a_i$ 代表第 $i$ 位选手的排名，$f_i$ 代表排在第 $i$ 位的选手的编号。

读入的显然是 $a$ 数组，$f$ 数组也很好处理，$f_{a_i}=i$。对于操作 $2$ 和 $3$，直接输出即可。对于操作 $1$，就需要动点脑子了。

首先，如果 $a_x=1$，即当前选手排在第 $1$ 名，则不管（跳过）；否则，进入下一步。

然后，查找出排在第 $x$ 号选手前面的选手，因为第 $x$ 号选手的排名是 $a_x$，所以获取 $f_{a_x-1}$ 即可，记 $gg=f_{a_x-1}$。

最后，赋值（改动）。当前的 $f_{a_x}$ 变成了 $gg$，当前的 $f_{a_x}-1$ 变成了 $x$。最后，$a_x$ 减 $1$（排名更靠前了），$a_{gg}$ 加 $1$（排名更靠后了）。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1145141919810
using namespace std;
int n,q,a[350001],f[350001];//个人习惯开大亿点
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i],f[a[i]]=i;//读入+初始化
	while(q--){
		int op,x;
		cin>>op>>x;
		if(op==1){
			if(a[x]==1)continue;//第一名
			int gg=f[a[x]-1];//找出前面的选手
			f[a[x]]=gg,f[a[x]-1]=x;//开始赋值
			a[x]--,a[gg]++;//还是赋值
		}
		else if(op==2)cout<<f[x]<<"\n";
		else cout<<a[x]<<"\n";
	}
	return 0;
}
```

---

## 作者：medal_dreams (赞：0)

## 思路
题意中拥有前进一名，输出编号排名，输出排名编号三个操作，若直接 $O(n)$ 遍历查找，铁定会 TLE。考虑用离散化或者数组来表示排名编号，编号排名。而 C++ 中正好有一个 STL 支持存储操作，它就是 map。  
定义两个 map 变量 $m,mm$，其中 $m$ 表示编号对应的排名，$mm$ 表示排名对应的编号，他们都在读入时存储。对于每一次前进一名操作，将两个变量交换（我也不知道 map 能不能用 swap，所以使用了用变量存储）。
## std
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T> inline void rd(T &x)
{
	x = 0;char c;int f = 1;
	do{c = getchar();if(c == '-') f = -1;}while(!isdigit(c));
	do{x = x * 10 + c - '0';c = getchar();}while(isdigit(c));
	x *= f;
}
const int N = 2e5 + 66;
int n,ans,a[N],q;
map<int,int> m,mm;//m 记录编号排名 mm 排名编号 
int main()
{
	rd(n),rd(q);
	for(int i = 1;i <= n;i ++) rd(a[i]),m[i] = a[i],mm[a[i]] = i;//在读入时存储排名和编号 
	for(int i = 1;i <= q;i ++)
	{
		int op,x;
		rd(op),rd(x);
		if(op == 1)
		{
			if(m[x] != 1)//因为对第一没影响，所以判断不是第一时 
			{
				//m[x] 就是编号 x 的排名，那么 m[x] - 1 就是它前一名 
				int y = mm[m[x] - 1];//记录前一名的编号 
				mm[m[x] - 1] = x;//将前一名修改为 X 
				m[x] = m[x] - 1;//将编号 x 的排名修改 
				mm[m[x] + 1] = y;//那么此时修改后的 m[x] + 1 就是 x 原来排名，将 y 放入 
				m[y] = m[x] + 1;//将 y 的排名修改为 x 原来的排名 
			}
		}
		else if(op == 2)
			cout << mm[x] << endl;//输出排名的编号 
		else
			cout << m[x] << endl;//输出编号的排名 
	}
	return 0;	
}
```
## 外话
其实对于给出的性质 $a_i$ 是 $1$ 到 $N$ 的排列也可以用桶去做存储。

---

## 作者：UNNN (赞：0)

## 题意

 有一个由 $n$ 个连续正整数组合成的数列，进行操作 $1$ 可以将数列中值为 $x$ 和 $x - 1$ 的数交换位置。操作 $2$ 为查询排名为 $x$ 的编号。操作 $3$ 为查询编号为 $x$ 的排名。

## 思路

 刚看到这题还以为是平衡树，后面仔细想了一想这道题其实不需要很复杂的数据结构，需要一点思维即可。

 我们可以定义两个数组 $a$ 和 $p$，对于正整数 $i \in [1, n]$，$a_i$ 的含义为编号为 $i$ 的企鹅排名为 $a_i$，$p_i$ 的含义为编号为 $p_i$ 的企鹅排名为 $i$。简单来说，$a$ 用于存储排名，下标为编号，$p$ 用于存储编号，下标为排名。

 对于操作 $1$，我们可以先在排名 $p$ 中查询编号为 $x$ 的企鹅，编号为 $x$ 的企鹅排名为 $a_x$，那么对应的，这个企鹅在 $p$ 中的位置便是 $p_{a_x}$，那么排在它前一位的企鹅在 $p$ 中的位置便是 $p_{a_x - 1}$。由于前者超过了后者，因此直接将二者交换位置即可。

 随后，我们还要更新 $a$ 数组。编号为 $x$ 的企鹅在 $a$ 中位置为 $a_x$，排在前一位的企鹅的编号可以先通过 $p$ 查询，它的编号为 $p_{a_x - 1}$，因此它在 $a$ 中的位置就是 $a_{p_{a_x - 1}}$。将两者交换位置即可。

 对于排名为 $1$ 的企鹅，题目中说明了需要直接忽略，因此我们直接判断 $p_1$ 的值是否为 $x$ 或者 $a_x$ 的值是否为 $1$，如果是那么执行 `continue` 语句即可。

 对 $a$ 交换时要注意一点，因为 $p$ 已经交换过了，$p_{a_x - 1}$ 已经不是原来的值，因此直接使用 `swap(a[x], a[p[a[x] - 1]]);` 交换会出现错误。所以我们要预先存储 $p_{a_x - 1}$ 的值，再进行交换。

 对于操作 $2$，问的是编号，对 $p$ 查询即可。

 对于操作 $3$，问的是排名，对 $a$ 查询即可。

 由题意得，我们输入时输入的是排名，因此直接将数据输入进 $a$ 数组即可。

## Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 2e5 + 5;
int n, q, a[MAXN], p[MAXN];
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1;i <= n;i++){
        scanf("%d", &a[i]); // 下标为编号，值为排名
        p[a[i]] = i; // 初始化 p 数组
    }
    while(q--){
        int op, x;
        scanf("%d%d", &op, &x);
        if(op == 1){
            if(p[1] == x) continue; // 排名为 1，忽略
            int book = p[a[x] - 1]; // 预先存储 p[a[x] - 1] 的值
            swap(p[a[x]], p[a[x] - 1]); // 对 p 交换
            swap(a[x], a[book]); // 对 a 交换
        }
        else if(op == 2) printf("%d\n", p[x]); // 查询编号
        else if(op == 3) printf("%d\n", a[x]); // 查询排名
    }
    return 0; // 结束 (｡･ω･｡)
}

```

---

## 作者：fjtMESSI10 (赞：0)

## 思路
这题我们可以先定义两个数组分别存当前的排名和排名当前的值，再判断如果输入的是 $1$，那么我们就交换输入的数和排名在输入的数前一位的数的排名，再分别更新它们的排名记录，最后查询的时候输出对应的数组中输入的数的值就行了。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N]; 
int b[N];  
int main() {
    int n,q;
cin>>n>>q;
    for (int i=1; i<=n;i++) {
        int x;
       cin>>x;
        a[x]=i;
        b[i]=x;
    }
    while (q--) {
        int op,x;
        cin>>op>>x;
        if (op==1) {
            int r=b[x];
            if (r==1)
                continue;    
            int t=a[r-1];
            a[r-1]=x;
            a[r]=t;
            b[x]=r-1;
            b[t]=r;
        } 
        else if (op==2) {
          cout<<a[x]<<endl;
        } 
        else if (op==3) {
         cout<<b[x]<<endl;
        }
    }
    
    return 0;
}
```

---

