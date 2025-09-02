# Adjust The Presentation (Easy Version)

## 题目描述

This is the easy version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ q=0 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line.

For the second test case, the following is a possible way to move members so that the presentation is good:

1. $ [1,2,3] $ , do not move member $ 1 $ .
2. $ [1,2,3] $ , move member $ 1 $ after member $ 3 $ .
3. $ [2,3,1] $ , move member $ 2 $ after member $ 3 $ .
4. $ [3,2,1] $ , do not move member $ 3 $ .
5. $ [3,2,1] $ , move member $ 3 $ after member $ 1 $ .
6. $ [2,1,3] $ , do not move member $ 2 $ .

## 样例 #1

### 输入

```
3
4 2 0
1 2 3 4
1 1
3 6 0
1 2 3
1 1 2 3 3 2
4 6 0
3 1 4 2
3 1 1 2 3 4```

### 输出

```
YA
YA
TIDAK```

# 题解

## 作者：chenxi2009 (赞：6)

本文为 Easy Version 题解。\
[Hard Verision 题解](https://www.luogu.com.cn/article/0stpmbmc)

# 题意简述

有一个长度为 $n$ 的**排列** $a$，你需要重复 $m$ 次操作，对于第 $i$ 次操作令 $c_i=a_1$，同时把 $a_1$ 删去并插入到 $a$ 的任意位置（可以仍为 $a_1$ 处）。你需要判断能否使 $c$ 与给定的长度为 $m$ 的数列 $b$ 完全相同。

# 思路

因为记录完 $a_1$**（以下简称队头）**$a_1$ 插入到任意位置均可，所以**当 $i$ 第一次被记录之后，它可以出现在 $c$ 的任意位置**。通俗地说，如果 $i$ 已经被记录了，那么后面无论记录多少次 $i$、在什么时候记录 $i$ 都是合法的。举个例子：如果 $b=(1,2,3,4)$ 是可行的，那么 $b=(1,2,2,2,3,3,3,4,1,3,2,4)$ 也是可行的。

如果归纳总结或是多举几个上面的例子，可以发现 $b$ 的合法性与 $b$ 中每个数字仅记录第一次出现得到的 $b'$ 等价。举个例子：就合法性而论，$(1,1,4,5,1,4,1,9,1,9,8,1)=(1,4,5,9,8)$。

而一个数字想要被记录，此时它在 $a$ 中必须是队头，前面不能有任何元素。也就是说，前面的数字必须先被移走。能够被移走显然就是被记录，所以**神奇地发现**，前段所述 $b'$ 必须得是 $a$ 的前缀，这样数字被记录从而得到“自由活动能力” 的顺序和原先在 $a$ 中的顺序相同。

如果你尝试着把 $a_i,b_i$ 用 $a_i,b_i$ 在 $a_i$ 中的位置去代替，就会发现 $a=(1,2,3,\cdots,n)$。所以 $b'$ 要合法就得满足 $b'=(1,2,3,\cdots,\max b_i)$。问题得到了解决，复杂度 $O(\sum n+m)$。

# 代码

由于 @[chenxi2009](https://www.luogu.com.cn/user/1020063) 不希望他的读者止步于此，所以他并没有放出 Easy Version 的代码。这篇题解其实很长一部分都在为 Hard Version 做铺垫，想要更进一步请在本题解的开头前往 Hard Version 题解。

---

## 作者：fish_love_cat (赞：2)

简单题，注意多测要把数据读完，不然就会像我一样当场升天。

---

注意到，曾经做过讲解的人一定有办法在重排后再次在需要的时间进行讲解。

设 $p_i$ 是第 $i$ 人在讲解序列中第一次出现位置。

设 $q_i$ 是第 $i$ 人在排队中第一次出现位置。

所以不合法的情况当且仅当 $q_i<q_j$ 且 $p_i>p_j$。

直接做即可。

代码不放了。

---

## 作者：Double_Light (赞：1)

容易发现当一个人讲完一张 PPT 之后可以安排到队列的任意位置，所以他下一次再讲哪一张 PPT 都可以做到。所以只需要让每个人第一次讲 PPT 时可以安排到合法的位置。

由于一开始的队列是固定的，所以编号 $a_i$ 的人第一次讲 PPT 如果比编号为 $a_j$ 的人第一次讲靠前，则 $i$ 一定小于 $j$。也就是说，$a$ 数组元素的顺序就是所有人第一次讲 PPT 的顺序。

最终只需要判断讲每张 PPT 的人第一次在 $b$ 中出现的下标相对顺序是否与 $a$ 中每个人的相对顺序相同即可。代码如下：

```cpp
#include<iostream>
using namespace std;
int T;
int n;
int m,q;
int maxn;
int a[200005],b[200005],p[200005];
int cnt;
int main(){
	cin>>T;
	while(T--){
		int f=1;
		int maxn=0;
		cnt=0;
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++)p[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[a[i]]=i;
		}
		for(int i=1;i<=m;i++){
			int x;
			cin>>x;
			if(!p[x])cnt++;
			if(!p[x]&&b[x]<maxn){
				f=0;
			}
			maxn=max(maxn,b[x]);
			p[x]=1;
			if(maxn!=cnt)f=0;
		}
		if(f)cout<<"YA\n";
		else cout<<"TIDAK\n";
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：1)

题意有点难懂，要好好理解一下。

条件一：如果这个人没有放过幻灯片（是第一次放），那么看看是否是按照 a 数组的顺序第一次出现，不是就非法；是的话就把未轮到的位置加一。

如果已经放过，那么不用管。因为，可以证明的是：**只要满足条件一，显然可以调整使得其满足数组 b 的顺序**。把这个想通了就能很容易做出来了。

## Code

[Link](https://codeforces.com/contest/2021/submission/284564944)

---

## 作者：_H17_ (赞：0)

## 题目分析

脑筋急转弯思维题：由于插入可以随便换到一个位置，所以只需要考虑 $b$ 中第一次出现的相对位置。

显然，和 $a$ 的相对位置相同时可以，否则不可以。

代码的话：本来想写 C2 所以写的挺复杂的，但是发现有事没时间了（所以参考性不强，还是扔一下）。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=2e5+1;
int T,n,m,q,a[N],b[N],head[N],tot,vis[N];
struct Line{
	int nxt,pos;
	Line(int nxt=0,int pos=0):nxt(nxt),pos(pos){}
}l[N];
void add(int pos,int val){
	l[++tot]=Line(head[val],pos),head[val]=tot;
	return;
}
void Main(){
	tot=0;
	memset(head,0,sizeof(head)),
	memset(vis,0,sizeof(vis));
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>b[i];
	for(int i=n;i>=1;i--)
		add(i,a[i]);
	int curmin=1;
	for(int i=1;i<=m;i++){
//		cerr<<b[i]<<' '<<vis[b[i]]<<' '<<curmin<<'\n';
		if(l[head[b[i]]].pos>curmin&&!vis[b[i]]){
			cout<<"TIDAK\n";
			return;
		}
		else if(!vis[b[i]])
			vis[b[i]]=1,curmin++;
	}
	cout<<"YA\n";
    return;
}
signed main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

赛时思路：

我们把这些人抽象成一个队列，先把 $a$ 中的每个数 push 进一个队列。

枚举到每个 $b_i$ 时，若 $b_i$ 已被 pop 掉了，那就合法，如果 $b_i$ 等于队头的数，那么把队头的数 pop 掉，也合法，否则直接判断不合法。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int t,n,m,c,a[N],b[N];
bool vis[N];
queue<int>q;
signed main(){
    cin>>t;
    while(t--){
        memset(vis,0,sizeof vis);
        while(q.size()) q.pop();
        cin>>n>>m>>c;
        for(int i=1;i<=n;i++) cin>>a[i],q.push(a[i]);
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int i=1;i<=m;i++){
            if(q.size()&&q.front()==b[i]){
                q.pop();
                vis[b[i]]=1;
                continue;
            }
            if(vis[b[i]]) continue;
            else{
                cout<<"TIDAK"<<endl;
                goto T3;
            }
        }
        cout<<"YA"<<endl;
        T3:;
    }
}
```

---

## 作者：Colinxu2020 (赞：0)

# 题意简述

有一个包含 $n$ 个人的队列，初始队列的第 $i$ 个元素是 $a_i$（$a$ 是排列），重复 $m$ 次，每次取出队头并放到队列的任意位置，要求第 $i$ 次取出的队头是 $b_i$，另有 $q$ 次修改（$q=0$） ，每次修改给定 $i,x$，要求 $b_i \gets x$，开始时和每次修改后求是否可行，可行输出 `YA`，不可行输出 `TIDAK`。

# 做法

## 推导过程

先把原题目加强一下，不仅要求输出是否有解，还要求构造方案。

一个直观的想法是对于每一个队头用完之后把他放到他下一次出现的地方，如果没有再出现则放到队尾，可能会有一些插入到中间时移动位置的小细节。

考虑这个构造方法何时不可行，假定前 $i-1$ 次都合法，若第 $i$ 次的队头为 $x$，$a_i$ 中 $x$ 的前一个是 $y$，移动除 $x$ 与 $y$ 之外的队头不影响 $x$ 与 $y$ 的相对位置，因此若 $x$ 之前 $y$ 没有出现过，则一定不可行，如果移动了 $y$，则此前 $y$ 一定出现过，与这个条件冲突，如果移动了 $x$，那么这个问题在上一次移动 $x$ 时就会被考虑，只需要注意一下细节，判定如果 $x$ 判定过就不再判定就也没有问题。

## 结论与证明

记 $x$ 在 $a_i$ 中的出现位置为 $ord_x$，。对于每一个 $i$，若 $ord_{b_i} \gt \max_{i=1}^{i-1} ord_{b_i}+1(i \neq 1)$ 那么无解，反之有解。

证明：

1. 证 $ord_{b_i} \gt \max_{i=1}^{i-1} ord_{b_i}+1$ 是无解的充分条件：此时 $a_{ord_{b_i}-1}$ 一定从未成为过队头（反证法，如果此条件不成立则 $\max_{i=1}^{i-1} ord_{b_i} \geq ord_{b_i}-1$，与已知不符），而无论如何安排队头的位置，一定不能使得 $a_{ord_{b_i}-1}$ 在 $b_i$ 之后出现（移动队头不影响其他元素的相对位置），因此若 $a_{ord_{b_i}-1}$ 从未出现过则 $b_i$ 不可能出现。

2. 证 $ord_{b_i} \gt \max_{i=1}^{i-1} ord_{b_i}+1$ 是无解的必要条件，反证 $ord_{b_i} \leq \max_{i=1}^{i-1}ord_{b_i}+1$ 是有解的充分条件：

   1. 证 $ord_{b_i} \leq \max_{i=1}^{i-1} ord_{b_i}$ 时一定有解，感性理解，将 $b_i$ 上一次用完后移动到 $i$ 的位置即可，若在上一次用完的位置与 $i$ 的位置之间插入则前移 $b_i$ 的位置；
   2. 证 $ord_{b_i} = \max_{i=1}^{i-1}ord_{b_i}+1$ 时一定有解，考虑对于前 $i-1$ 个用 2.1 的的方法构造，之后对于第 $i$ 个直接留在原位置即可完成。

证毕。

## 代码

```cpp
#include<iostream>
using namespace std;

const int maxn=2e5+10;
int t,n,m,q,ai[maxn],bi[maxn],mp[maxn];

int main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++)cin>>ai[i],mp[ai[i]]=i;
        for(int i=1;i<=m;i++)cin>>bi[i],bi[i]=mp[bi[i]];
        int mx=0; bool flag=0;
        for(int i=1;i<=m&&!flag;i++){
            if(bi[i]>mx+1){
                flag=1;
                cout<<"TIDAK"<<endl;
            }
            mx=max(mx, bi[i]);
        }
        if(!flag)cout<<"YA"<<endl;
    }
}
```

---

## 作者：kanzaki (赞：0)

## 思路
观察题目要求，发现在这种宽松的移动方法下唯一不能满足的情况就是当前要求放映的人排在还没有放映过幻灯片的人的后面。

因为如果在他之前出现了没有放映过幻灯片的人，不论怎么排他都无法下一次就放映幻灯片。

而放过幻灯片的人可以接在开头或任意一个人的后面，所以能够满足除了上面这一情况的所有情况。

一种快捷的判断方法就是把每个人的权值改为是第几个第一次在 $a$ 数组中出现的人。之后再从左往右判断 $b$ 数组中是否有一个数大于它之前的数的最大值 $+1$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
int t,n,m,a[maxn],b[maxn],c[maxn],q;
map<int,int> mp;
void solve(){
	cin>>n>>m>>q;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]=++cnt;
	}
	for(int i=1,x;i<=m;i++){
		cin>>x;
		b[i]=mp[x];
	}
	int mx=0;
	for(int i=1;i<=m;i++){
		if(b[i]>mx+1){
			cout<<"TIDAK\n";
			goto a;
		}
		mx=max(mx,b[i]);
	}
	cout<<"YA\n";
	a:;
	mp.clear();
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
}
/*
1 2 3 4 5 6 7
1 2 3 4 1 5 6
1 2 3 4 5 6 7

*/
```

---

