# Petya and Catacombs

## 题目描述

A very brave explorer Petya once decided to explore Paris catacombs. Since Petya is not really experienced, his exploration is just walking through the catacombs.

Catacombs consist of several rooms and bidirectional passages between some pairs of them. Some passages can connect a room to itself and since the passages are built on different depths they do not intersect each other. Every minute Petya arbitrary chooses a passage from the room he is currently in and then reaches the room on the other end of the passage in exactly one minute. When he enters a room at minute $ i $ , he makes a note in his logbook with number $ t_{i} $ :

- If Petya has visited this room before, he writes down the minute he was in this room last time;
- Otherwise, Petya writes down an arbitrary non-negative integer strictly less than current minute $ i $ .

Initially, Petya was in one of the rooms at minute $ 0 $ , he didn't write down number $ t_{0} $ .

At some point during his wandering Petya got tired, threw out his logbook and went home. Vasya found his logbook and now he is curious: what is the minimum possible number of rooms in Paris catacombs according to Petya's logbook?

## 说明/提示

In the first sample, sequence of rooms Petya visited could be, for example $ 1→1→2 $ , $ 1→2→1 $ or $ 1→2→3 $ . The minimum possible number of rooms is $ 2 $ .

In the second sample, the sequence could be $ 1→2→3→1→2→1 $ .

## 样例 #1

### 输入

```
2
0 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
0 1 0 1 3
```

### 输出

```
3
```

# 题解

## 作者：Noby_Glds (赞：3)

大佬的树链剖分，统计叶子节点我都看不懂，只好自己写了个代码。
### 思路：
神鱼写下的数字有两种，一种是第一次来到该位置乱写的随机数，一种是上一次来到该位置的时间。

想要让这张图的点最少,就得让随机数最少，时间更多。

我们用 $vis$ 数组记录神鱼写下的数字是否可能为上一次来到该位置的时间。

假如神鱼在时间点 $t$ 写下了数字 $i$，但 $vis(i)$ 等于 $0$，那么这张图的点数加一，同时 $vis(t)$ 改为 $1$，因为 $t$ 未来可能为上一次来到该位置的时间。

那 $vis(i)$ 如果等于 $1$ 呢？这张图的点数就不增加，但 $vis(i)$ 改为 $0$，因为上一次来到该位置的时间变成 $t$ 了。

还有一个要注意的地方是，一开始 $vis(0)$ 是等于 $1$ 的，因为神鱼一开始就在点上。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,vis[200010],p;
int main(){
	scanf("%d",&n);
	vis[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&p);
		if(vis[p]==0) ans++;
		else vis[p]=0;
		vis[i]=1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Soojin2012 (赞：3)

这题第一眼：好像挺难的。想到思路后：水题啊！
### 题目思路：
我们可以用数组记录数字有没有可能是上次次来到该位置的时间，数组设为 $a$，答案为 $ans$。

数字有两种：第一种是头一次来到位置所写的随机数，另一种是上次来到位置的时间。

为使图的点最少，必定得让随机数最少。

最开始 $a[0]=1$，由于一分钟只可能在一个房间，也就是说这些 $a[i]$ 两两都不相等。如有重复，那么说明来到了一个全新的节点，就可以 $ans$ 加一了。
### 代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[200005];//数组定义
int main(){
   int n,ans=1,m;//起点也是点
   ios::sync_with_stdio(false);//优化，可写可不写
	cin>>n;//输入(废话×1)
	a[0]=1;
	for(int i=1;i<=n;i++){
		cin>>m;
		if(a[m]==0) ans++;//来到全新节点，答案加一
		else a[m]=0;
		a[i]=1;
	}
	cout<<ans;//输出(废话×2)
	return 0;
}
```


---

## 作者：_775spacing747_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF886C)
# 1 思路
首先用数组记录上次来到该位置的时间，我们可以假设每个时间点都是上一次神鱼来过的时间，由于神鱼一分钟内只可能在一个房间，也就是说这些时间点都不相等。如果有两个重复了，说明来到了一个新的节点，要把答案加一。
# 2 代码
```cpp
#include<bits/stdc++.h>//万能头yyds 
using namespace std;
int a[200005],n,ans=1,m;
int main()
{
	a[0]=1;//初始化！！！！！ 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		if(a[m]==0)ans++;//来到了新节点 
		else a[m]=0;//否则赋0 
		a[i]=1;//设为1 
	}
	cout<<ans;//输出 
	return 0;//完美结束(^_^) 
}
```
### [AC 记录](https://www.luogu.com.cn/record/133470135)

---

## 作者：Forever_LYD (赞：1)

我又来了写水题题解了，感谢各位好心人给我提供可以写题解的水题！

一眼看上去就认为是二叉树，当然可以实现，但我没有用什么高精的算法，就是普普通通的分析。

题目大意:给定你一棵树，再给你几个关于这棵树的父亲，求至少可以分成几链。

题目分析:通过读题可以发现神鱼写下的数字要么是上一次的时间，要么是随机数，那么最优解肯定是让随机数更少，时间更长即可，也就是说，每一次记录下神鱼到的位置，再经过上述处理，即为解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn =1e6+5;
int a[maxn],tot;
int main(){
    int n;
	cin>>n;
	for(int i=0;i<=n;i++)a[i]=1;
	for(int i=1;i<=n;i++){
		int sc;
        cin>>sc;
		if(!a[sc])tot++;
		else a[sc]=0;
		a[i]=1;
	}
	cout<<tot+1<<endl;
	return 0;
}
```


---

## 作者：lianchanghua (赞：1)

#### 题目大意

给你一个 $n$ 和 $n$ 个 $t_i$。

其中，$t_i$ 表示：
- 如果走到的是一个新点，写下任意一个严格小于当前时刻数的非负整数。
- 如果以前来过，写最近一次到这里的时间。

#### 思路

其实 $t_i$ 可以直接理解为它出现的时间。

由于一个时间内只能访问一个点，且同一个点输出的是它们第一次被访问的时间，所以，我们就可以使用一个标记数组来记录这个 $t_i$ 曾经是否出现过，如果没有，我们就让答案加一。

**注意：答案最后要加 $1$，因为他开始时的起点也是一个点。**

#### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
bool a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;i++){
    	int x;
        cin>>x;
        if(a[x]) 	cnt++;
        else 		a[x]=1;
    } 
    cout<<cnt+1;
    return 0;
}
```

---

## 作者：FS_qwq (赞：1)

## 题目大意

每一分钟神鱼会选一条边，走到和她的位置相邻的点（也可以不走）。第 $i$ 分钟神鱼写下数字 $t_i$（第 $0$ 分钟时，神鱼不会写下数字），这个数遵循如下规则：

* 如果当前神鱼走到了以前没走到过的点，那么她会写下一个严格小于当前时刻的非负整数。
* 如果当前神鱼走到了以前走到过的点，那么她会写下她最近一次来到该点的时间。

现在已知 $t_1,t_2,\ldots,t_n$，他想知道这个图**最少**有几个点。

## 题目解答

既然需要得出**最少**的点数，那么就要使神鱼以前来过该节点的概率更大。首先神鱼第 $0$ 秒就已经在某个点上了，所以初始时答案为 $1$。可以假设每个 $t_i$ 都是上一次神鱼来过的时间，由于神鱼一分钟内只可能在一个房间，也就是说这些 $t_i$ 两两都不想等。但是如果有两个重复了，那么说明神鱼肯定来到了一个新的节点，就可以把答案加一了。

[代码](https://codeforces.com/contest/886/submission/222725234)

---

## 作者：MornEveGlow (赞：1)

由于新房间的随机数都小于i, 我们可以将当前的随机数仍然**看作走过来的时间点(即入边)**. 然后在计算时每个时间点最多只留**一条出边**.

所以每个房间的所有时间点可以看做一条**链**. 

所以就有:

## 题意简化

	给出一棵树, 输入每个点的父亲, 求树最少被分割成多少条链.

如果还是没搞懂题意简化的话, 可以看图. (样例二图解, 分割方式为样例二解释中的例子)

![](https://cdn.luogu.com.cn/upload/pic/70198.png)

做过这种原题的人可以直接跳过了.

## 思路

~~既然是树上的链, 我们可以想到树链剖分.~~ 正当我在想树链剖分怎么做这题时, 同学说:

	"不是统计一下有多少个叶子节点就可以了吗?"

...

诶对对对, 统计一下叶子结点. 我先证明一下:

由于链是不能拐弯的(链上节点深度均不同), 所以一条链不可能出现两个叶子节点, 最多出现一个, 而且作为链的下端点. 则**链的下端点个数大于等于叶子节点个数**.

而除了叶子节点外, 每个节点都至少有一个儿子, 则这些节点都能从任意一个儿子连上链, 所以不必作为链的下端点(即一条链中深度最深的点). 则**链的下端点个数不大于叶子节点个数**.

所以**叶子节点个数等于链的下端点个数**, 易知链的下端点个数即为链的个数, 则**求出叶子节点个数即求出链的个数**.

所以标记一遍有儿子的点(比如i时输入a, 则BJ[a]=true), 最后扫一遍无儿子节点个数就好了.

## 代码(这个输入也很良心啊):

```cpp
#include<cstdio>
using namespace std;
const int N=2e5+5;
int n,a,ans,A[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a);
		++A[a];
	}
	for(int i=1;i<=n;++i)
		if(!A[i])++ans;
	printf("%d\n",ans);
}
```


---

## 作者：fkcufk (赞：0)

## 解析
[题目传送门](https://www.luogu.com.cn/problem/CF886C)

我们可以定义数组 $a$ 记录每个时间是否符合要求，初始时将 $a$ 数组初始化为 $1$（因为神鱼在哪里都来到了一个地方），再定义变量 $cnt$，由于 $a_0$ 为初始地方，已经被访问过了，所以 $cnt\gets1$。

如果神鱼没有来过，即 $a_{tmp}=0$，则神鱼来到了新的地方，$cnt\gets cnt+1$。如果已经来过了，即 $a_{tmp}=1$，则将 $a_{tmp}$ 设为 $0$。

## 代码
```cpp
#include <bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
using namespace std;
typedef long long ll;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void write(int x){
    if(x<0){x=-x;putchar(45);}
    if(x>9) write(x/10);
    putchar(x%10+48);
    return;
}

int n;
int a[200005];
int cnt = 1;

int main() {
    FastIO; // cin cout 优化
    cin >> n;
    memset(a, 1, sizeof a); // 初始化
    for (int i = 1; i <= n; i++) { // 遍历
        int tmp;
        cin >> tmp;
        if (a[tmp] == 0) cnt++;
        else a[tmp] = 0;
    }
    cout << cnt;
    // Code...

    return 0;
}
```


---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/CF886C)
## 题目理解
这道题要求我们确定根据 Petya 的日志，求出巴黎地下墓穴中房间的最小的可能数量。
## 题目思路
我们可以用一个 bool 数组 $vis$ 表示每个时间是否有对应的新房间。$vis_0$ 表示初始房间，所以设置为 true 并且增加房间数 $ans$。对于每个时间点 $i$，如果 Petya 写下的数字 $t_i$ 还没有被访问过（!$vis_i$），那么就代表 Petya 访问了一个新的房间，我们就增加 $ans$。如果数字 $t_i$ 已经被访问过了，就代表一个之前已经存在的房间的时间，所以我们就不用增加 $ans$。无论 $t_i$ 是否被访问过，我们都会将 $vis_i$ 设置为 true，因为怎么样 Petya 都在 $i$ 时进入了一个房间。
***
## Code
```cpp
#include<iostream>
using namespace std;
const int maxn = 1e5 * 2 + 10;
int n, ans;
bool vis[maxn];
int main(){
    cin >> n;
    vis[0] = true;
    ans++;
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        if(!vis[x]) ans++;
        else vis[x] = false;
        vis[i] = true;
    }
    cout << ans << "\n";
    return 0;
}
```
时间复杂度：$O(n)$，空间复杂度 $O(n)$，可以通过本题。


---

## 作者：yhx0322 (赞：0)

## 题目简述
神鱼在图上游走。每一分钟会随机选一条边，走到与其相邻的一个点（可以不动）。

第 $i$ 分钟神鱼会写下一个数字 $t_i$：

- 如果走到的是一个新点，写下任意一个小于当前时刻的非负整数。
- 如果以前来过，写最近一次到这里的时间。

现在已知 $t_1,\ldots,t_n$，他想知道这张图最少有几个点。

## 思路
首先我们分析出一个性质：

要想使得图中点的数量最少，就**必须使得写下的随机数字尽可能的少。**

令 $f_i$ 表示第 $i$ 个神鱼是否可能为上一次来到该位置的时间，$num$ 表示这张图最少有几个点。

每次输入，就分两种情况讨论：
- $f_i = 0$，$num$ 加 $1$，$f_t = 1$，表示可能成为上一次来到这里的时间。
- $f_i = 1$，把 $f_i$ 更改为 $0$。

**注意：$num$ 的初始值要设为 $1$，因为神鱼本来就在某一个点上。**
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int f[N], n, num = 1, x;

int main() {
	ios::sync_with_stdio(false); // 输入输出流优化
	cin.tie(0), cout.tie(0);
	cin >> n;
	f[0] = 1; // 边界情况
	for (int i = 1; i <= n; i++) {
		cin >> x;
		if (!f[x]) num++;
		else f[x] = 0;
		f[i] = 1;
	}
	cout << num;
	return 0;
}
```

---

## 作者：IOI_can_AK_lsr (赞：0)

# CF886C 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF886C)

[CodeForces传送门](https://codeforces.com/contest/886/problem/c)

[更好的阅读体验](https://www.luogu.com.cn/blog/910468/CF886c-tijie)

## 废话

第一眼：题面里有边和点，是二叉树/图论？

第二眼：普通做法就行，出题人真良心……

废话不多说，进入正题。

## 思路

这题正解肯定是二叉树或者图论，但因为作者实在是太蒻了，所以只能想出这个用 bool 数组的方法。

- 首先，我们需要知道，$vis_0$ 一定是等于 $1$ 的（因为“神鱼”一开始就踩在一个点上），所以我们将“神鱼”走过的点数设为 $1$。
 
- 然后，题目想要“神鱼”踩到的点最少，就是要尽可能多的踩以前踩过的点（即上次来过的时间更多，而写下的新数字最少）

 最后，我们就可以来看下面的解析啦。
 
##  解析

- 考虑定义一个 bool 类型的 vis 数组记录下“神鱼”写下数字的时间。

- 我们设“神鱼”在时间点 $x$ 写下了数字且 $vis_x=0$，则 $vis_x$ 改为 $true$ ,并且将“神鱼”走过的点数加 $1$;

如果 $vis_x$ 已经为 $true$ 的状态了，则将 $vis_x$ 设为 $false$ 的状态（因为“神鱼”已经来过这里了）。

最后在每次循环中都会将一个点标记为“神鱼来过”（即 $vis_i=1$），这道简单到极致的题也就做完了。

[代码&&AC记录见此处](https://codeforces.com/contest/886/submission/222894927)

请不要抄袭本篇题解&&代码（虽然我知道洛谷rmj已经坏了）


---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 · CF886C Petya and Catacombs](https://www.luogu.com.cn/problem/CF886C) 

~~挑战一波最短代码~~

### 题目简要：
现在有一个大小未知的图，给你一些数字，这些数字有一些规律
1. 如果神鱼来到的是一个全新的点，神鱼会在这里随机写一个数字，然后**写下的这个数是小于当前分钟 $i$ 的任意整数**（这是一个较为关键的信息）。
2. 如果神鱼之前来过这个房间，那么他会写下最近一次到这里的时间。

现在通过已有的数字判断这个图到底有多少个节点。

------------

### 题意分析
这道题中输入的数字只有两种情况，如果让点最少，我们新增的点就要最少，写下的随机数最少~~这不是废话吗~~。

我们假设 $t _ i$ 都是神鱼到达的**上个**节点，那么我们这一串数字的每一个数字都应该不一样，因为上一次的时间与这一次的时间是不同的，如果有，那么只有一种可能：出现了新的节点，所以输出的答案加 $1$。

------------
## 代码 
```cpp 
#include <bits/stdc++.h>
using namespace std;
int yt[200020],n,m,ans=1,i;
int main(){
    cin>>n;
    for(i=1;i<=n;i++){
    	cin>>m;
    	if(yt[m]) ++ans;
    	else yt[m]++;
	} 
	cout<<ans;
	return 0;
}//by·yutong_Seafloor 
``` 


------------

**这里要注意：**
我们输出的答案要加上 $1$，因为神鱼在第 $0$ 分钟是在节点上的但是没有写数字，如果不加 $1$ 就会少一个节点

 [AC！](https://www.luogu.com.cn/record/122027714)

请勿抄袭谢谢。

---

## 作者：sssscy_free_stdio (赞：0)

欢迎观看本蒟蒻写的题解！

本题就是输入每个点的父亲，求出这棵树最少能分割成几条链。

因为是求最少，因此一条链要一路连到叶子节点，因此直接统计一下叶子节点就行了。

实现方法：

每次输入一个变量 $fa$，就将 $fa$ 的儿子个数加 $1$，最后再枚举一遍，统计有多少节点的儿子数量为 $0$ 就行了。

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,fa,ret,son_cnt[200010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&fa);
		son_cnt[fa]++;//fa的儿子数量加1
	}for(int i=1;i<=n;i++){
		if(son_cnt[i]==0){//i为叶子节点
			ret++;//数量加1
		}
	}printf("%d",ret);
	return 0;
}
```

---

## 作者：Not_lazy (赞：0)

题意：给出一棵树, 输入每个点的“父亲”, 求树最少被分割成多少条链。

神鱼写下的数字有两种，一种是第一次来到该位置乱写的随机数，一种是上一次来到该位置的时间。

想要让这张图的点最少,就得让随机数最少，时间更多。

用数组来储存神鱼到过的点 。

注意，一开始 $a(0)$ 是等于 $1$ 的，因为神鱼一开始就在点上。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1,a[200010],m;
int main(){
	scanf("%d",&n);
	a[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&m);
		if(a[m]==0) ans++;
		else a[m]=0;
		a[i]=1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：BlackPanda (赞：0)

*[Problem](https://www.luogu.com.cn/problem/CF886C)*

------------
## *Description*

有 $n$ 个互相两两相通的房间，Petya 每分钟都会随机选择一个房间，走到与其相通的房间。

第 $i$ 分钟 Petya 会写下数字 $t_i$，遵循以下规则：

- 如果 Petya 以前走过这个房间，他会写下他上次到这个房间的时间。

- 否则，Petya 会写下严格小于当前分钟的任意非负整数。

Petya 第 $0$ 分钟不会写下数字 $t_0$。

现在你知道了 $t_1,\ldots,t_n$，请你求出是多少？

------------
## *Solution*

由题意可得，要想使房间数量最小，那么就得让第二种情况出现次数尽可能少（Petya 写下任意整数的次数尽可能少），写下上次到此房间的时间的次数尽可能多。

可以先假设 $t_i$ 全部是 Petya 上次到达此房间的时间，因为每个单位时间不会重复，只会出现一次，所以如果 $t_i$ 重复出现过，就说明这个 $t_i$ 是第二种情况写下的任意非负整数，答案累加 $1$。

**注意**：因为 Petya 第 $0$ 分钟会在一个房间里且不会写下数字 $t_0$，所以最后的房间数要加 $1$。

------------
## *Code*

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int t, res;
map<int, int> mp;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> t;
        if (mp.find(t) != mp.end())
        {
            res ++ ;    
        }
        else
        {
            mp[t] = 1;
        }
    }
    cout << res + 1;
    return 0;
}
```

---

## 作者：Kedit2007 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF886C)

**在我写这篇题解的时候，题目翻译漏掉了一个信息：每次写下的随机数大小大于零且小于当前时间。**

## 思路

当我们拿到一个输入时，有两种情况：

- 这是一个随机数。
- 这是之前的一个时间。

我们希望让访问过的房间尽量少，也就是说我们希望尽量多地把输入看成先前的一个时间。

此时又分两种情况：

- 在之前没有出现过这个数。
- 之前出现过这个数。

如果没有出现过，那么由于 Petya 随机写的数总是小于当前时间，我们可以放心假设 Petya 之前来过这个房间，即这个输入是上次来这个房间的时间。

如果之前出现过，那么由于我们上面的假设，这个输入只能是随机写出的（因为上次出现时会把“上次访问”的时间设成一个不可能随机写出的数），这时将房间数加一。

注意一开始 Petya 也在一个房间，所以每次写到 $0$ 的时候肯定是随机写出的。

## 参考代码

```cpp
int main()
{
    unordered_map<int, bool> mapp{};
    mapp[0] = true;

    int n;
    cin >> n;

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if (mapp[t])
        {
            ans++;
        }
        else
        {
            mapp[t] = true;
        }
    }

    cout << ans;

    return 0;
}

```

---

