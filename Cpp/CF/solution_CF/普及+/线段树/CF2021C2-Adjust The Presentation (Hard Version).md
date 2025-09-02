# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA```

# 题解

## 作者：chenxi2009 (赞：9)

**Upd 25.5.7：被赛后 Hack RE 了，修改了代码。**

[Easy Version 题解](https://www.luogu.com.cn/article/hlp27bkv)\
本文为 Hard Version 题解。

## 形式化题意

有一个长度为 $n$ 的**排列** $a$，你需要重复 $m$ 次操作，对于第 $i$ 次操作令 $c_i=a_1$，同时把 $a_1$ 删去并插入到 $a$ 的任意位置（可以仍为 $a_1$ 处）。你需要判断能否使 $c$ 与给定的长度为 $m$ 的数列 $b$ 完全相同。

烦人的~~出题人~~你的老板决定对 $b$ 进行修改，每次指定 $s,t$，令 $b_s\leftarrow t$。该操作是永久的，需要保留。每次修改后仍需进行上述判断。

## 思路

## 前情提要

如果对下文内容感到疑惑，请在本文开头进入 Easy Version 题解，其中有部分铺垫内容。

在 Easy Version 的题解中，我们令 $b_i\leftarrow pos_{b_i}$，其中 $pos_i$ 表示 $i$ 在 $a$ 中的下标（出现的位置），再对 $b$ 进行去重，**只保留第一次出现的每个数字**，得到 $b'$。发现 $b$ 合法，等价于 $b'=(1,2,3,\cdots,\max b)$。

现在加入了修改操作，那怎么解决呢？

首先我们要能快速得到 $b'$。我们需要保存一个数字出现的所有位置，能调取位置的最小值，能插入和删去其中指定值的元素，这不就是~~平衡树~~ set 么？\
定义集合数组 $S$，$S_i$ 保存 $i$ 出现的位置。`*S[i].begin()` 可以调取 $S_i$ 中最小的元素。插入和删除是 set 的基本操作不再赘述。

此时程序复杂度未得到提升，需要思考如何 $O(\log n)$ 修改。

发现如果 $b$ 不合法，那么

$$
\exists 1\le i\le m,b_i\ne 1,\sum_{j=1}^{i-1}[b_j=b_i-1]=0
$$

也就是说，$b'$ 中 $b_i$ 之前没有出现 $b_{i}-1$ 且 $b_i\ne 1$。**显然这等价于 $b'$ 中 $b_i-1$ 在 $b_i$ 之后，即**

$$
\min S_{b_i-1}>\min S_{b_i}
$$

再考虑用 $prb$ 存储所有存在上述问题的 $b_i$，$prb$ 为空时 $b$ 合法。

每次修改的时候，需要判断 $b_s,b_s+1,t,t+1$ 是否在 $prb$ 中。额外判断一下即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar
#ifndef DEBUG
#define debug
#endif
using namespace std;
template<typename T>void read(T &x){x = 0;int f = 1;char c = gc();while(!isdigit(c)){if(c == '-') f = -1;c = gc();}while(isdigit(c)) x = x * 10 + c - '0',c = gc();x *= f;}
const int N = 300000;
int T,n,m,Q,a[N],b[N],s,t;
map<int,int>mp;//用于进行操作 b_i <- pos_{b_i} 
set<int>st,q[N];//st 存储 b' 中不合法的 b_i，q_i 存储 i 在 b 中出现的位置 
int main(){
	read(T);
	while(T --){
		mp.clear(),st.clear();
    read(n),read(m),read(Q);
		for(int i = 1;i <= n;i ++) read(a[i]),mp[a[i]] = i,q[i].clear();
		for(int i = 1;i <= m;i ++) 
			read(b[i]),q[b[i] = mp[b[i]]].insert(i);
		for(int i = 2;i <= n;i ++)
			if(q[i].size() && (q[i - 1].empty() || *q[i - 1].begin() > *q[i].begin()))  
				st.insert(i);//i 出现在 i-1 之前，不合法，记录
    
		if(st.empty()) printf("YA\n");
		else printf("TIDAK\n");

		for(int i = 1;i <= Q;i ++){
			read(s),read(t),t = mp[t]; 
			q[b[s]].erase(s);// b[s] 改变，q[b[s]] 不再记录 b[s]
      
			if(q[b[s]].empty() || (q[b[s] - 1].size() && *q[b[s] - 1].begin() < *q[b[s]].begin())) 
				st.erase(b[s]);//q[b[s]] 空或 b[s] 合法，记得判断空集 

			if(b[s] < n && q[b[s] + 1].size() && (q[b[s]].empty() || *q[b[s]].begin() > *q[b[s] + 1].begin()))//特判越界
				st.insert(b[s] + 1);//b[s]+1 不合法

			b[s] = t,q[t].insert(s);//s 记录 t
			if(t != 1 && (q[t - 1].empty() || *q[t - 1].begin() > *q[t].begin())){// 特判越界 
				st.insert(t);//t 不合法 
			}
			if(q[t + 1].empty() || q[t].size() && *q[t].begin() < *q[t + 1].begin()){//t+1 变得合法 
				st.erase(t + 1);
			}
			if(st.empty()) printf("YA\n");
			else printf("TIDAK\n");
		}
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：5)

请先做 C1。

容易得到 C1 的结论：记录 $f_i$ 为 $i$ 第一次在 $b$ 中出现的位置，则 $\forall i\in[1,n),f_{a_i}\leq f_{a_{i+1}}$ 时合法。

考虑记录每次修改后的 $f_i$ 并判断 $\forall i\in[1,n),f_{a_i}\leq f_{a_{i+1}}$ 是否成立。可以把每个 $a_i$ 映射到 $i$ 处理，判断 $f_i\leq f_{i+1}$，下标连续会更好处理。

显然一次修改只会修改两个 $f_i$，可以使用一个数据结构维护 $f$，操作进行单点修改、全局查询是否单调不降。可以考虑线段树维护它，然后就做完了。

---

## 作者：Day_Tao (赞：3)

差点场切，但是没调出来/ll。

题目可以转化为给定一个长为 $n$ 的排列 $a$ 和一个长为 $m$ 的序列 $b$，满足 $b$ 中每种出现过的数字按照第一次出现的位置从小到大排序，最终是 $a$ 的一段前缀。hard vertion 要求可以修改 $b$。

不难想到对于每次操作维护一个 $cnt$，在 $cnt$ 为特定值的时候可行，否则不行。接下来考虑 $cnt$ 来表示什么。容易发现如果对于“一段前缀”处理起来比较棘手，但是由于 $a$ 排列的性质，我们就可以将 $a$ 中的元素重新映射，使排列升序。这样问题就转化成了 $b$ 中每种出现过的数字按照第一次出现的位置从小到大排序，对应的数字是一个 $1,2,\cdots,k$ 的数列。这样我们就可以维护 $n+1$ 个 `set`，第 $i$ 个记录数字 $i$ 在 $b$ 中出现的所有位置。为了方便比较，第 $0$ 个 `set` 和第 $n+1$ 个 `set` 初始分别插入 $0$ 和 $m+1$，对于 $1\cdots n$ 的 `set` 都插入 $m+1$ 表示没有出现过，这样就不用判一车 `begin` 和 `end` 的边界条件了。在插入完 $b_i$ 之后，不难发现上面的条件就等价于需要保证 `S[i].begin()` 的递增，所以我们的 $cnt$ 就用来维护 `S[i].begin()>S[i+1].begin()` 的数量，当 $cnt=0$ 时合法，$cnt\neq0$ 时不合法。在修改的时候就对应更新一下 $cnt$ 即可，可以参考代码部分。

时间复杂度 $O(n\log n)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int T,n,m,q,cnt,a[N],b[N],p[N];
set<int>S[N];
inline void SOLVE()
{
	n=read(),m=read(),q=read(),cnt=0;
	for(int i=1;i<=n+1;i++)S[i].clear(),S[i].insert(m+1);
	for(int i=1;i<=n;i++)a[i]=read(),p[a[i]]=i;
	for(int i=1;i<=m;i++)b[i]=p[read()],S[b[i]].insert(i);
	for(int i=2;i<=n;i++)if(*S[i-1].begin()>*S[i].begin())cnt++;
	puts(cnt?"TIDAK":"YA");
	while(q--)
	{
		int x=read(),y=p[read()],v=b[x];
		bool L=*S[v].begin()<*S[v-1].begin(),
			 R=*S[v].begin()>*S[v+1].begin();
		S[v].erase(x), // 比较删除前和删除后的，所以先记录下删除前的大小关系
		cnt+=(*S[v].begin()>*S[v+1].begin()&&!R),
		cnt-=(*S[v].begin()<=*S[v+1].begin()&&R),
		cnt+=(*S[v].begin()<*S[v-1].begin()&&!L),
		cnt-=(*S[v].begin()>=*S[v-1].begin()&&L),
		L=*S[y].begin()<*S[y-1].begin(),
		R=*S[y].begin()>*S[y+1].begin(),
		b[x]=y,S[y].insert(x),
		cnt+=(*S[y].begin()>*S[y+1].begin()&&!R),
		cnt-=(*S[y].begin()<=*S[y+1].begin()&&R),
		cnt+=(*S[y].begin()<*S[y-1].begin()&&!L),
		cnt-=(*S[y].begin()>=*S[y-1].begin()&&L),
		puts(cnt?"TIDAK":"YA");
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T=read();S[0].insert(0);while(T--) SOLVE();system("pause");return 0;
}
```

---

## 作者：linjunye (赞：2)

### 题目描述
有一个长度为 $n$ 的排列 $a$，每次从 $a$ 中取出第一个数 $a_1$，再然后将这个数放到数列中一个任意的位置。

它有 $q$ 次修改操作，每次操作给定 $x$ 和 $y$，将 $a_x$ 改成 $y$。注意，修改是永久性的。

对于每次修改后与初始状态，你需要判断：执行 $m$ 次操作后，可不可以得到一种出队列的次序数列，与数组 $b$ 相同。

若可以，输出 `YA`，否则输出 `TIDAK`。

$1\le n,m\le 2\times 10^5$。

$0\le q\le 2\times 10^5$。
### 初步思路
注意到它可以放到任意位置，这一点很烦，我们需要想一种性质，使得实现时与放的位置关联性不大。

那么，该如何设计呢？

我们发现，每个数有两种状态：

- 未取出。

- 取出了。

#### 未取出（不考虑放回去）
这个很简单，比如我们就用一个队列，每次弹出，如果第 $i$ 次弹的这个数不是 $b_i$ 的话，就输出 `TIDAK`。
#### 取出了（不考虑未取出）
我们发现，若所有元素都取出过了，那么它们总有一种方法，可以使得第 $i$ 次弹的这个数与 $b_i$ 相等。

为什么呢？就像我们继续弄，结果发现：有一处地方不一样了啊！

那么，动用“时光回溯”，回溯回来，将现在弹出的这个数改掉位置。

这里有点抽象，建议画图思考。
#### 综和
结合在一起，我们用一个队列，每次弹出，如果第 $i$ 次弹的这个数不是 $b_i$ 的话，就输出 `TIDAK`。

弹出的数就不放回去，因为取出的数总有一种方法，可以使得后面都相等。

那么，我们写出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,_,a[200010];
int H[200010];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>_;
		for(int i=1;i<=n;i++)H[i]=1;
		queue<int>q;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			q.push(x);
		}
		for(int i=1;i<=m;i++)cin>>a[i];
		int f=1;
		for(int i=1;i<=m;i++){
			if(H[a[i]]==1&&q.front()!=a[i]){
				cout<<"TIDAK\n";
				f=0; 
				break;
			}
			else if(H[a[i]]==1&&q.front()==a[i]){
				q.pop();
				H[a[i]]=0;
			}
			else if(H[a[i]]==0)continue;
		}
		if(f)cout<<"YA\n";
	}
	return 0;
}
```
然后就可以愉快的过掉 [C1](https://www.luogu.com.cn/problem/CF2021C1) 啦。
### 深入思考
这样的做法一次是 $O(n)$ 的，总复杂度为 $O(qn)$，对这道题不利。

队列操作是不好优化的，那么我们想想能否换一种表现方式。

我们发现，第一次出现的数才是决定结果是否合法的关键。

先看一组例子：
```
3 6 0
1 2 3
1 2 1 3 3 2
```
首先，我们针对 `1 2 1 3 3 2` 进行分析。

容易发现有两个 `1`，`2`，`3`。其实，只有第一个才有用，第二个决定不了结果的合法性。

似乎，我们只取第一次出现的数，就是这样：

`1 2 3`。

然后，判断一下是否为 `1 2 3` 的前缀即可（可能从来没出现一个数）。

但是这不好判断啊，别急，如果就像这组例子，$a$ 是升序，会怎么样？

似乎，我们把每个数的位置放到对应的 `set` 中，判断合法性只需要比较 `*set[i-1].begin()<=*set[i].begin()` 即可。

还是对接下来的操作不利，我们计满足 `*set[i].begin()>*set[i].begin()` 的有 $cnt$ 个，那么，只需判断 $cnt$ 是否等于 $n-1$ 即可。

这样就对修改有利了，每次修改时，发现 $a_x$ 的 `set` 变了，$y$ 的 `set` 也变了，那么会影响到这些数周围的条件，只需重新计算即可。

这里有点难理解，看一下代码：
```cpp
void cal(int x,int f){//f表示修改的编号
	for(int i=x;i<=x+1;i++){//这个数的影响范围
		if(i==1)continue;
		int x=1e9,y=1e9;//细节
		if(s[i-1].size())x=*s[i-1].begin();
		if(s[i].size())y=*s[i].begin();
		cnt+=(x<=y)*f;
	}
	return;
}
...
cal(b[x],-1);//先回来
s[b[x]].erase(x);//删除
cal(b[x],1);//记录新的cnt
b[x]=y;
cal(b[x],-1);//先回来
s[b[x]].insert(x);//删除
cal(b[x],1);//记录新的cnt
```
那么 $a$ 不有序呢？

这个很简单，我们把它变成有序的不就好了！

那么：

1. 重排 $a$ 数组。

2. 计算初始 $cnt$。

3. 进行修改。

总算是完成了！
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int T;
int n,m,q;
int cnt;
int a[N];
int b[N];
int p[N];
set<int>s[N];
int x,y;
void cal(int x,int f){
	for(int i=x;i<=x+1;i++){//影响范围 
		if(i==1)continue;
		int x=1e9,y=1e9;//细节 
		if(s[i-1].size())x=*s[i-1].begin();
		if(s[i].size())y=*s[i].begin();
		cnt+=(x<=y)*f;
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			p[a[i]]=i;//重拍 
		}
		for(int i=1;i<=n;i++)a[i]=p[a[i]];
		for(int i=1;i<=m;i++)cin>>b[i];
		for(int i=1;i<=m;i++)b[i]=p[b[i]];
		for(int i=1;i<=m;i++)s[b[i]].insert(i);
		cnt=0;
		for(int i=2;i<=n;i++){
			int x=1e9,y=1e9;//细节 
			if(s[i-1].size())x=*s[i-1].begin();
			if(s[i].size())y=*s[i].begin();
			cnt+=(x<=y);
		}
		if(cnt==n-1)cout<<"YA\n";
		else cout<<"TIDAK\n";
		while(q--){
			cin>>x>>y;
			y=p[y];//细节 
			cal(b[x],-1);
			s[b[x]].erase(x);
			cal(b[x],1);
			b[x]=y;
			cal(b[x],-1);
			s[b[x]].insert(x);
			cal(b[x],1);
			if(cnt==n-1)cout<<"YA\n";
			else cout<<"TIDAK\n";
		}
		for(int i=1;i<=n;i++)s[i].clear();
	}
	return 0;
}
/*
1
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2
*/
```

---

## 作者：MightZero (赞：2)

### Solution

首先，设 $fp_i$ 为 $a_i$ 在 $b$ 中第一次出现的位置（若不存在则设为 $+\infin$）；根据 C1 中得到的结论，我们可以知道对于 $a$ 中的每个数，只有当它们在 $b$ 中第一次出现的位置单调不减，即 $fp$ 单调不减时才满足题意。

证明：若存在 $a_i=b_p$ 且 $fp_i=p$，注意到 $a_i$ 能在第 $p$ 个位置出队当且仅当 $a_i$ 前的所有元素都已经出过队（并且被重新安排到队列中合适的位置），否则若有 $a_j=b_q$ 且 $fp_j=q,j>i,q<p$，则可以说明一定无法在 $a_i$ 在第 $p$ 个位置出队前移走 $a_j$。

可以将数组 $a$ 看作排名数组，根据 $a$ 的排列顺序得到每个数在 $a$ 中的排名 $rk$，即 $rk_{a_i}=i$。

对于给定的 $fp$ ，如何快速得到其是否单调递增？可以考虑将 $fp$ 差分，若差分数组所有值非负则当前状态合法；注意到每次修改操作**至多只会改变一个 $fp_i$**，因此修改差分数组的操作次数也是 $O(1)$ 的。对于差分数组的维护，可以用 `multiset` 快速插入和删除，若 `multiset` 中的最小值非负则当前状态满足题意。

接下来考虑如何修改 $fp$。可以维护一个类似双向链表的结构，设 $pre_i$ 为与 $b_i$ 值相同的前一个元素的位置（称为前驱位置），$nxt_i$ 为与 $b_i$ 值相同的后一个元素的位置（称为后继位置），若对应元素不存在则设为 $0$；那么就可以用类似双向链表的修改方式修改对应的关系。

对于一个操作 $b_p\gets x$，先移除旧的 $b_p$，将 $p$ 的前驱位置和后继位置对应的 $pre$ 与 $nxt$ 直接相连；若 $pre_p$ 不存在，即 $b_p$ 为某个第一次出现的数，则需要把 $fp_{rk_{b_p}}$ 修改为 $p$ 的后继位置（若不存在则设为 $+\infin$）；修改 $fp$ 之前要把与修改的 $fp$ 相关的差分值从 `multiset` 中删除，修改 $fp$ 后要将新的差分值插入 `multiset`。

插入新的值时，由于直接找当前位置的前驱和后继比较困难，可以对每种元素开一个 `set` 维护该种元素出现的所有位置，查找时直接 `lower_bound` 即可。插入新值的具体操作类似删除的逆向操作，需要简单分类讨论，细节请看代码实现。

设 $n,m$ 同阶，则总体时间复杂度约为 $O(T(n+q)\log n)$。

最后，**多测要清空**！！！

### Code

~~赛时写的码风比较魔怔请见谅~~
```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
const ll N=2e5+5,INF=1e18;
ll n,m,q;
ll a[N],b[N];
ll nx[N],pr[N];//前驱、后继位置
ll rk[N],fp[N];//排名、第一次出现位置
map<ll,ll> mp;
multiset<ll> tr;//差分数组
set<ll> app[N];//每种元素出现位置
void solve()
{
    n=read(),m=read(),q=read();
    mp.clear();
    tr.clear();
    loop(i,1,n)
    {
        a[i]=read(),fp[i]=INF;
        app[i].clear();
        rk[a[i]]=i;
    }
    loop(i,1,m)b[i]=read(),pr[i]=nx[i]=0;
    loop(i,1,m)
    {
        if(!mp[b[i]]) fp[rk[b[i]]]=i;
        else nx[mp[b[i]]]=i,pr[i]=mp[b[i]];
        mp[b[i]]=i,app[b[i]].insert(i);
    }
    loop(i,1,n-1)
        tr.insert(fp[i+1]-fp[i]);
    if(*tr.begin()>=0)puts("YA");
    else puts("TIDAK");
    while(q--)
    {
        ll p=read(),x=read();
        // 删除旧元素
        if(nx[p])pr[nx[p]]=pr[p];
        if(pr[p])nx[pr[p]]=nx[p];
        else
        {
            if(rk[b[p]]!=1)tr.erase(tr.lower_bound(fp[rk[b[p]]]-fp[rk[b[p]]-1]));
            if(rk[b[p]]!=n)tr.erase(tr.lower_bound(fp[rk[b[p]]+1]-fp[rk[b[p]]]));
            fp[rk[b[p]]]=nx[p]?nx[p]:INF;
            if(rk[b[p]]!=1)tr.insert(fp[rk[b[p]]]-fp[rk[b[p]]-1]);
            if(rk[b[p]]!=n)tr.insert(fp[rk[b[p]]+1]-fp[rk[b[p]]]);
        }
        app[b[p]].erase(p);
        pr[p]=nx[p]=0;

        //添加新元素
        if(!app[x].size())//x从未出现过
        {
            if(rk[x]!=1)tr.erase(tr.lower_bound(fp[rk[x]]-fp[rk[x]-1]));
            if(rk[x]!=n)tr.erase(tr.lower_bound(fp[rk[x]+1]-fp[rk[x]]));
            fp[rk[x]]=p;
            if(rk[x]!=1)tr.insert(fp[rk[x]]-fp[rk[x]-1]);
            if(rk[x]!=n)tr.insert(fp[rk[x]+1]-fp[rk[x]]);
        }
        else
        {
            auto it=app[x].lower_bound(p);
            if(it==app[x].end())//p在最后一个位置之后
            {
                nx[*app[x].rbegin()]=p;
                pr[p]=*app[x].rbegin();
            }
            else if(!pr[*it])//p在第一个位置之前
            {
                nx[p]=*it;
                pr[*it]=p;
                if(rk[x]!=1)tr.erase(tr.lower_bound(fp[rk[x]]-fp[rk[x]-1]));
                if(rk[x]!=n)tr.erase(tr.lower_bound(fp[rk[x]+1]-fp[rk[x]]));
                fp[rk[x]]=p;
                if(rk[x]!=1)tr.insert(fp[rk[x]]-fp[rk[x]-1]);
                if(rk[x]!=n)tr.insert(fp[rk[x]+1]-fp[rk[x]]);
            }
            else
            {
                ll pre=pr[*it];
                nx[p]=*it,pr[*it]=p;
                nx[pre]=p,pr[p]=pre;
            }
        }
        b[p]=x;app[x].insert(p);
        if(*tr.begin()>=0)puts("YA");
        else puts("TIDAK");
    }
}
signed main()
{
    ll T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：Locix_Elaina_Celome (赞：2)

[link.](https://codeforces.com/contest/2021/problem/C2)

首先 C1 有一个结论：保留 $b$ 数组每个元素第一次出现的位置，设剩下的东西是 $b'$，如果 $b'$ 是 $a$ 的一个前缀，那么这个 $b$ 是合法的。

C2 带修，一个数组要是另一个的前缀，考虑维护 $b'$ 的哈希值。

首先可以对于每个值 $i$ 维护一个 $s_i$ 表示这个值出现的位置的集合，这样就能很好地找到每个值第一次出现的位置。

然后考虑怎么维护哈希值。

很显然可以用平衡树，修改的时候先把原本的东西删除，再把涉及的两个值的第一次出现的位置重新插入平衡树。但是这样会有一点麻烦。

线段树稍微方便点，维护哈希值的同时维护一个 $cnt_u$，表示 $u$ 这个区间内有多少个有值的地方。合并哈希值的时候 $h_u=h_{2u}p^{cnt_{2u+1}}+h_{2u+1}$。

但是这题卡了 $p=998244353$，会死在 pretest3，但是不会 FST，但是别的 $p$ 就没卡，1145141919 都可以。当然双哈希最保险。

反正最后得到 $b'$ 的哈希值之后再看是否存在一个 $a$ 的前缀哈希值和它相等就好了。

时间复杂度 $O(n\log n)$

```cpp

int n,m,q;
int a[N];
int b[N];
ULL p[N];
ULL p2[N];
struct st{
	ULL h[N<<2];
	ULL h2[N<<2];
	int cnt[N<<2];
	void modify(int u,int l,int r,int i,LL c){
		if(i<l||r<i)return;
		if(l==r){
			h[u]=h2[u]=c;
			cnt[u]=1;
			if(c==0)cnt[u]=0;
			return ;
		}
		int mid=(l+r)>>1;
		modify(u<<1,l,mid,i,c),modify((u<<1)|1,mid+1,r,i,c);
		h[u]=h[u<<1]*p[cnt[u<<1|1]]+h[(u<<1)|1];
		h2[u]=h2[u<<1]*p2[cnt[u<<1|1]]+h2[(u<<1)|1];
		cnt[u]=cnt[u<<1]+cnt[u<<1|1];
	}
}t;
set<pair<ULL,ULL> > ss;
set<int> s[N];
int main(){
	int T;
	read(T);
	while(T--){
		read(n);
		read(m);
		read(q);
		for(int i=0;i<=(Max(n,m)<<2);i++)t.h[i]=t.h2[i]=t.cnt[i]=0;
		ss.clear();
		p[0]=p2[0]=1;
		for(int i=1;i<=Max(n,m);i++)p[i]=p[i-1]*P,p2[i]=p2[i-1]*P2,s[i].clear();
		pair<ULL,ULL> sm={0,0};
		for(int i=1;i<=n;i++){
			read(a[i]);
			ss.insert({sm.first=sm.first*P+a[i],sm.second=sm.second*P2+a[i]});
		}
		for(int i=1;i<=m;i++)read(b[i]),s[b[i]].insert(i);
		for(int i=1;i<=n;i++){
			if(!s[i].size())continue;
			t.modify(1,1,m,*s[i].begin(),i);
		}
		puts(ss.count({t.h[1],t.h2[1]})?"YA":"TIDAK");
		for(int i=1;i<=q;i++){
			int id,x;
			read(id);
			read(x);
			t.modify(1,1,m,*s[b[id]].begin(),0);
			s[b[id]].erase(id);
			if(s[b[id]].size())t.modify(1,1,m,*s[b[id]].begin(),b[id]);
			
			if(s[x].size())t.modify(1,1,m,*s[x].begin(),0);
			s[x].insert(id);
			t.modify(1,1,m,*s[x].begin(),x);
			
			b[id]=x;
			puts(ss.count({t.h[1],t.h2[1]})?"YA":"TIDAK");
		}
	}
	return 0;
}


```

---

## 作者：GY程袁浩 (赞：1)

### 前言

个人认为这题线段树用的很精妙。

### 解法

容易发现有以下结论：

**对于所有在 $a$ 中的元素在 $b$ 中的编号递增，幻灯片的播放效果是良好的。**

考虑如果第一次出现不递增那么必然不良好，因为他前面的人必须放映完毕才能到他。然后对于已经播放过的人，在 $b$ 中不管出现在哪都是合理的，因为他可以随便插入队列中的任何位置。

因此，只要知道 $a$ 中的元素在 $b$ 中第一次出现的编号是否递增即可。

目前的思路已经够你做简单版了。

如果我们想要做困难版，还需要应对老板的 $q$ 次针对 $b$ 的修改。也就是变成要维护 $a$ 中的元素在 $b$ 中第一次出现的编号是否递增，我们需要维护 $a$ 中的元素第一次在 $b$ 中出现的编号。

我们要支持对于一个 $a$ 中的元素，快速查询最小的在 $b$ 中出现的编号，以及快速删去和加入一个在 $b$ 的中编号（对应老板的操作），这些都可以用可以用容器集合实现。

接下来，考虑怎么样才能得知目前 $a$ 中的元素在 $b$ 中第一次出现的编号是否递增。首先绝对不能暴力，就算查询是 $O(1)$ 的，也需要 $O(n)$ 的时间复杂度。所以探究是否可以从每次修改的影响下手。发现每次修改我们最多改变两个的元素在 $b$ 中的位置，所以实际上可以通过讨论每次对于不合法数量的影响来做这题。

但是这样太麻烦了，还容易漏情况，做不出来。想想有没有什么无脑的方法？想想好用的线段树？有了，发现我们一段数的单调性容易由两个小的区间合并，我们只需要知道分成的两个区间是否有序以及两个区间的最大最小值即可得知大的区间是否具有单调性。由于是单点修改，也容易维护，因此用线段树来维护 $a$ 中的元素在 $b$ 中第一次出现的编号是否递增即可。

### CodeForces 通过代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,INF=0x3f3f3f3f;
int a[N],b[N];
set<int> pls[N];
map<int,int> p;
int tt,n,m,q;
struct node {
	int l,r,maxn,minn;
	bool ok;
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define maxn(x) tr[x].maxn
	#define minn(x) tr[x].minn
	#define ok(x) tr[x].ok
};
struct segment {
	node tr[N*4];
	void pu(int x) {
		ok(x)=(ok(x*2)&&ok(x*2+1)&&maxn(x*2)<=minn(x*2+1));
		maxn(x)=max(maxn(x*2),maxn(x*2+1));
		minn(x)=min(minn(x*2),minn(x*2+1));
	}
	void build(int x,int l,int r) {
		l(x)=l,r(x)=r;
		if(l==r) {
			minn(x)=maxn(x)=(*pls[l].begin());
			ok(x)=1;
			return;
		}
		int mid=l+r>>1;
		build(x*2,l,mid),build(x*2+1,mid+1,r);
		pu(x);
	}
	void change(int x,int pl,int k) {
		int l=l(x),r=r(x);
		if(pl==l&&l==r) {
			maxn(x)=minn(x)=k;
			return;
		}
		int mid=l+r>>1;
		if(pl<=mid) change(x*2,pl,k);
		else change(x*2+1,pl,k);
		pu(x);
	}
	bool qry(int x) {return ok(x);}
}tree;
signed main() {
	cin>>tt;
	while(tt--) {
		for(int i=1;i<=n;i++) pls[i].clear();
		p.clear();
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++) pls[i].insert(INF);
		for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
		for(int i=1;i<=m;i++) cin>>b[i],pls[p[b[i]]].insert(i);
		tree.build(1,1,n);
		if(tree.qry(1)) puts("YA");
		else puts("TIDAK");
		while(q--) {
			int x,y;cin>>x>>y;
			if(b[x]==y) {
				if(tree.qry(1)) puts("YA");
				else puts("TIDAK");
				continue;
			}
			int tmp=b[x];
			pls[p[b[x]]].erase(x);
			pls[p[y]].insert(x);
			b[x]=y;
			tree.change(1,p[tmp],(*pls[p[tmp]].begin()));
			tree.change(1,p[y],(*pls[p[y]].begin()));
			if(tree.qry(1)) puts("YA");
			else puts("TIDAK");
		}
	}
	return 0;
}
```

---

## 作者：__Floze3__ (赞：1)

来一发线段树 + set 的题解。

## 思路

我们容易发现一个 $b$ 序列合法的充要条件为：在只保留每个数第一次出现的位置后，剩下的序列为 $a$ 序列的一个前缀。因此，我们考虑用每个数在 $a$ 序列中出现的位置来给它们重新赋值，那么条件转变为：剩下的 $b$ 序列是一个从 $1$ 开始的，公差为 $1$ 的等差数列。我们可以使用 set 方便的维护每个数第一次出现的位置，但如何判断合法性？我们可以维护这样一个序列，每个位置上的值是这个数第一次出现的位置（如果没有出现则为极大值），那么 $b$ 序列合法的要求即为这个序列单调不降，我们可以使用线段树来维护这一点，那么我们就在 $O((n + q) \log n)$ 的时间复杂度内解决了这个问题。

## 代码

```cpp
#include <bits/stdc++.h>

#define il inline

constexpr int N = 2e5 + 5;
constexpr int inf = 0x3f3f3f3f;

int n, m, q, a[N], b[N], p[N];

std::set<int> pos[N];

struct node {
  int l, r, lv, rv;
  bool able;

  #define ls (p << 1)
  #define rs (p << 1 | 1)
  #define mid (t[p].l + t[p].r >> 1)
} t[N << 2];

il void pushup(int p) {
  t[p].lv = t[ls].lv, t[p].rv = t[rs].rv;
  t[p].able = t[ls].able && t[rs].able && t[ls].rv <= t[rs].lv;
  return ;
}

void build(int p, int l, int r) {
  t[p].l = l, t[p].r = r;
  if (l == r) {
    t[p].lv = t[p].rv = inf, t[p].able = true;
    return ;
  }
  build(ls, l, mid), build(rs, mid+ 1, r);
  return pushup(p);
}

void update(int p, int pos, int v) {
  if (t[p].l == t[p].r) {
    t[p].lv = t[p].rv = v;
    return ;
  }
  pos <= mid ? update(ls, pos, v) : update(rs, pos, v);
  return pushup(p);
}

il void solve() {
  std::cin >> n >> m >> q; for (int i = 1; i <= n; ++i) pos[i].clear();
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i], p[a[i]] = i;
  for (int i = 1; i <= m; ++i)
    std::cin >> b[i], b[i] = p[b[i]], pos[b[i]].insert(i);
  build(1, 1, n);
  for (int i = 1; i <= n; ++i) {
    if (pos[i].size()) update(1, i, *pos[i].begin());
  }
  std::cout << (t[1].able ? "YA" : "TIDAK") << '\n';
  while (q--) {
    int x, y; std::cin >> x >> y; y = p[y];
    update(1, b[x], inf);
    pos[b[x]].erase(x);
    if (pos[b[x]].size()) update(1, b[x], *pos[b[x]].begin());
    if (pos[y].size()) update(1, y, inf);
    pos[y].insert(x);
    b[x] = y;
    update(1, y, *pos[y].begin());
    std::cout << (t[1].able ? "YA" : "TIDAK") << '\n';
  }
  return ;
}

signed main() {
  std::cin.tie(nullptr) -> sync_with_stdio(false);
  int _; std::cin >> _;
  while (_--) solve();
  return 0;
}
```

---

## 作者：2020kanade (赞：0)

考虑手动模拟操作：注意到 PPT 队列的队头出队后可以安排到任意位置，则每个元素只要第一次出队时合法，那么剩下的若干次出队一定合法。

考虑不带修，我们让人员序列的每个人依次和 PPT 队列中每个人依次从前到后匹配，并在 PPT 队列中忽略已经被匹配过的人的后续出现，只要 PPT 队列能被匹配完就是合法的。

更具体一点，把 PPT 队列中的每个人的第一次出现构成的子序列提取出来构成一个新的序列（下面称为“生成序列”），若生成序列是人员序列的一个前缀，则此时 PPT 队列合法。修改操作则可以转化为对生成序列的一次删除和一次插入。

对于维护每个点是否在生成序列中，考虑每种颜色开一个 ```std::set```，里面存其出现的下标，这样就好搞了。

容易想到将序列视为字符串进行哈希。对于生成序列的哈希维护，可以考虑进制哈希的本质把 PPT 队列上线段树，对于叶子结点，若其不在生成序列中，这个位置视作空串，其哈希值和长度都为 $0$；否则视作正常字符，其哈希值按照进制哈希进行合并即可，线段树只需要实现单点信息改和全局信息和。

亲测这题没卡自然溢出，当然出于保险和对自己负责，自己实现时请自行更换靠谱的字符串哈希。

时间复杂度 $\Theta(n+(m+q)\log m)$。

赛时做法，但是哈希取模写挂了，赛后三天一怒之下换了自然溢出竟然过了。


```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
using ull=unsigned ll;
int t,n,k,m,q;
set<int> col[N];
vector<int> b,lst;
static constexpr long long mod=(1ull<<61)-1,md1=mod/2;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> dit(md1 , mod-1ull);
const ull z = 19260817;
ull fpm(ll x,ll y)
{
    ull ans=1;x=x%mod;
    for(;y;y>>=1,x=(x*=x)%mod) if(y&1) ans=(ans*=x)%mod;
    return ans;
}
ull xp[N];
//hs[i]=hs[i-1]*_x+1ull*NTR[i];
ull hs1[N];
ull ghs(int l,int r)
{
	return  (hs1[r]-(hs1[l-1]*xp[r-l+1]));
}
struct info
{
	ull val,sz;
	info():val(0),sz(0) {}
	info(ull val,ull sz):val(val),sz(sz) {}
};
info operator +(const info &a,const info &b)
{
	ull nval=((a.val*xp[b.sz])+b.val);
	ull nsz=a.sz+b.sz;
	return info(nval,nsz);
}
info sum[N*2];
int ls[N*2],rs[N*2],cnt,rt;
void change(int _x,int l,int r,int q,ull rv,int sv)
{
	if(l==r)
	{
		sum[_x]=info(rv,1ull*sv);
		return;
	}
	int mid=(l+r)/2;
	if(q<=mid) change(ls[_x],l,mid,q,rv,sv);
	else change(rs[_x],mid+1,r,q,rv,sv);
	sum[_x]=sum[ls[_x]]+sum[rs[_x]];
}
void c0nst(int &x,int l,int r)
{
	x=++cnt;
	if(l==r) return;int mid=(l+r)/2;
	c0nst(ls[x],l,mid);c0nst(rs[x],mid+1,r);
	sum[x]=sum[ls[x]]+sum[rs[x]];
}
void clr_seg()
{
	for(int i=0;i<=cnt;++i) sum[i]=info{0,0},ls[i]=rs[i]=0;
	cnt=rt=0;
}
void change(int x,int y)
{
	int ncol=b[x];
	if(col[ncol].size()>1&&(*col[ncol].begin())!=x)
	{
		col[ncol].erase(x);
	}
	else
	{
		change(rt,1,m,x,0,0);
		col[ncol].erase(x);
		if(col[ncol].size())
		{
			int nps=*col[ncol].begin();
			change(rt,1,m,nps,ncol,1);
		}
	}
	if(!col[y].size())
	{
		change(rt,1,m,x,y,1);
	}
	else if((*col[y].begin())>x)
	{
		int nps=*col[y].begin();
		change(rt,1,m,nps,0,0);
		change(rt,1,m,x,y,1);
	}
	col[y].insert(x);
	b[x]=y;
}
void solve()
{
	cin>>n>>m>>q;
	c0nst(rt,1,m);
	vector<int> a(n+3,0);
	b=vector<int>(m+3,0);
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) hs1[i]=((hs1[i-1]*z)+1ull*a[i]);
	for(int i=1;i<=m;++i) cin>>b[i],col[b[i]].insert(i);
	for(int i=1;i<=m;++i) if((*col[b[i]].begin())==i) change(rt,1,m,i,b[i],1);
	ull xsh=sum[rt].val;int sz=sum[rt].sz;
	bool ok=xsh==ghs(1,sz);
	cout<<((!ok)?"TIDAK":"YA")<<endl;
	for(int i=1;i<=q;++i)
	{
		int ix,iy;
		cin>>ix>>iy;
		change(ix,iy);
		xsh=sum[rt].val;sz=sum[rt].sz;
		ok=xsh==ghs(1,sz);
		cout<<((!ok)?"TIDAK":"YA")<<endl;
	}
	clr_seg();
	for(int i=1;i<=n;++i) hs1[i]=0,col[i].clear();b.clear();
}
int main()
{
	xp[0]=1;
	for(int i=1;i<=500001;++i) xp[i]=(xp[i-1]*z);
 	t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

