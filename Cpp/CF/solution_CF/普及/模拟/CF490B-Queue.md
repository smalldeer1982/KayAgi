# Queue

## 题目描述

During the lunch break all $ n $ Berland State University students lined up in the food court. However, it turned out that the food court, too, has a lunch break and it temporarily stopped working.

Standing in a queue that isn't being served is so boring! So, each of the students wrote down the number of the student ID of the student that stands in line directly in front of him, and the student that stands in line directly behind him. If no one stands before or after a student (that is, he is the first one or the last one), then he writes down number 0 instead (in Berland State University student IDs are numerated from $ 1 $ ).

After that, all the students went about their business. When they returned, they found out that restoring the queue is not such an easy task.

Help the students to restore the state of the queue by the numbers of the student ID's of their neighbors in the queue.

## 说明/提示

The picture illustrates the queue for the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF490B/08daf79334436a27cb8cf554f27be1c975002c35.png)

## 样例 #1

### 输入

```
4
92 31
0 7
31 0
7 141
```

### 输出

```
92 7 31 141 
```

# 题解

## 作者：Edmundino (赞：3)

# 题意

给出每个人前一个人和后一个人的编号，求完整的队列。

**数据范围**

$2\le n\le 2\times10^5,a_i,b_i\le 10^6$。

# 分析

首先我们把$a_i,b_i$给记录起来，

可以发现：只有第一个编号和最后一个编号只出现了一次。

（这个条件很重要）

接着，我们可以把每个$a_i$所对应的$b_i$存起来

就是说:$lat_{a_i}=b_i$。

存好以后，

我们可以从$lat_0$开始，$lat_0$其实是第二个数的编号，

然后$lat_{lat_0}$是第四个数的编号……

以此类推，知道$lat=0$时停止，

这样，我们就搞定了偶数的队列，

接下来是奇数，

首先要找到第一个数：

即，我在上面说的`只有第一个编号和最后一个编号只出现了一次`。

第一个编号和最后一个编号的区别就是第一个编号的$lat$是不等于$0$的。

找到第一个数，按照偶数的方式，就能求出奇数的队列了。

# 代码

**查找编号的部分**


```cpp
void jie(int o,int x)
{
	while(o>0)
	{
		ans[x]=o;
		x=x+2;
		o=lat[o];
	}
}

```


**$AC$代码**

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

const int N=1e6+50;

int n,lat[N],a,b,ans[N],tot[N],maxs;

void jie(int o,int x)
{
	while(o>0)
	{
		ans[x]=o;
		x=x+2;
		o=lat[o];
	}
}

int main()
{
   cin>>n;
   memset(lat,-1,sizeof(lat));
   for(int i=1;i<=n;i++)
   {
   	cin>>a>>b;
   	lat[a]=b;
   	tot[a]++;
   	tot[b]++;
   }
   jie(lat[0],2);
   for(int i=1;i<=N;i++)
   {
   	if(tot[i]==1&&lat[i]>=0)
    {
    	jie(i,1);
    	break;
	}
   }
   for(int i=1;i<=n;i++)
   {
   	cout<<ans[i]<<" ";
   }
   cout<<endl;
   return 0;
}
```


---

## 作者：Y_QWQ_Y (赞：2)

个人认为，这道题评高了。~~不过没关系，又水一道黄题。~~

### 题面补充
题目中没有给出数据范围，范围是：$2\le n\le2\times10^5,0\le a_i,b_i\le10^6$。$a_i,b_i$ 为某一个数的前驱和后继。

### 解题思路
既然题目给出了前驱与后继，那么我们直接按照链表来做，定义 $nxt_i,pre_i$ 来记录数字 $i$ 的前驱与后继。那么，$nxt$ 和 $pre$ 数组需要开到 $10^6$ 以上。

我们知道，一个数的前驱为 $0$，则该数为 $a_1$，那么它的后继必然是 $a_2$，而 $a_2$ 的后继是 $a_4$，以此类推，即可知道所有 $a_{2k}$。

接下来，我们要求下标为奇数的 $a$，因为我们可以通过 $a_1$ 来计算整个下标为奇数的 $a$，而 $a_1$ 没有前驱，所以只需要随便找到一个没有被计算出来的 $a$，它的下标必然是奇数，然后不断取它的前驱，直到没有前驱，就找到了 $a_1$。

当然，也有更快的方法，在初始化时把 $pre$ 全都初始化为 $-1$，直接在出现过的 $a_i,b_i$ 之中找到一个 $pre$ 为 $-1$ 的，就是 $a_1$。

找到了 $a_1$，同上，可求出所有 $a_{2k+1}$。

### 代码部分
在我不断地修改下，代码可以说是最短的。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, nxt[N], pre[N], ans[N];
bool v[N];
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
	memset (pre, -1, sizeof (pre));
	for (int i = 1; i <= n; ++ i)
	{
		int a, b;
		cin >> a >> b;
		nxt[a] = b;
		pre[b] = a;
		v[a] = 1, v[b] = 1;//记录出现
	}
	int i = 0, j = 2;
	while (nxt[i])//求出所有 a[2k]
	{
		ans[j] = nxt[i];
		i = nxt[i];
		j += 2;
	}
	int rt;
	for (i = 1; i <= N; ++ i)if (pre[i] == -1 && v[i])//找 a[1]
	{
		rt = i;
		break;
	}
	j = 1;
	while (rt)//求出所有 a[2k+1]
	{
		ans[j] = rt;
		rt = nxt[rt];
		j += 2;
	}
	for (int i = 1; i <= n; ++ i)cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：YangXiaopei (赞：2)

## 题目补充：

数据范围：

$2 \le n \le 2 \times 10 ^ 5, a_i, b_i \le 10 ^ 6$

## 题目大意：

给出你每个人的前后是谁（没人用 $0$）表示，求完整的队列。

## Solution:

我们不难看出，给出每个人的前后，就可以在通过把一个人的后面当成一个人的人的前面，从而找出一条隔一个是一个队列。

那我们不是就可以找出以第一项开头的和以第二项开头的两条队列，使其轮流放入一个新的队列，就构成了答案要求的完整的队列了。

但现在有两个难点：

* 如何找出前两项是谁。

* 如何在不二重循环暴力枚举的情况下找出每一条队列。

先来看较好解决第一个问题。

很容易发现，第一项它是没有前面的。所以我们就可以通过找谁的前面是 $0$ 从而确定第一项。

而第二项，只有他前面是第一项，而没有谁后面是第一项。所以可以找，那个只出现过一次。

点又会有一个问题：最后一项也只出现一次。

所以，还需判断它是否出现在一个位置的前一项（先输入的），这样就能找到第二项的编号了。

再看第二个问题。

我们可以用一个 `map` 存下每个先驱所对应的编号。

假设我们推到了编号 $pos$，我们可以通过 `mp[y[pos]/*这个编号的后继*/]/*以这个编号为前驱的编号*/` 来访问下一个点。

但接着又会出现一个新的问题：我们知道了每个编号位于完整队列是第几个，但我们不知道他是几啊。

此时，我们就可以让以第一项开头的队列全部变为他的后继（若人数为奇数个，就最后一项舍去），以第二项开头的队列也变成他的前驱（若人数为奇数个，还要加入最后一项的后继），这样不就相当于用以第二项开头的队列推出了奇数号组成的队列，而用以第一项开头的队列推出了偶数号组成的队列了吗？

有了这个，就奇偶轮流输出即可。

## 代码：

个人写的可能有点复杂，各位神犇们看懂了自己写即可。本人代码仅作参考。

再次提醒您：~~规则千万条，诚信第一条。写题不规范，封号两行泪~~。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n, x[200005], y[200005], vis[200005];//
unordered_map/*哈希map*/<int, int > mp, mq;//分别记录每个前驱对应的编号和用来记录每个编号出现个数的
vector<int> v, g;//分别存奇数队列和偶数队列。
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> x[i] >> y[i];
		mq[x[i]]++;//存点的出现个数，方便找第二项。
		mq[y[i]]++;
		mp[x[i]] = i;//记录每个前驱对应的编号。
	}
	int pos = mp[0];//
	while(mp.count(y[pos]) && y[pos] != 0){//找第一项开头的队列，并对应到后继。
		v.push_back(y[pos]);
		vis[pos] = 1;
		pos = mp[y[pos]];
	}
	vis[pos] = 1;
	if(mp.count(y[pos]) == 0){//最后一点的判断。
		v.push_back(y[pos]);
	}
	for(int i = 1; i <= n; i++){
		if(vis[i] == 0 && mq[x[i]] == 1){//寻找第二项
			pos = i;
		}
	}
	g.push_back(x[pos]);
	while(mp.count(y[pos]) && y[pos] != 0){//找第二项开头的队列，并对应到前驱。
		g.push_back(y[pos]);
		vis[pos] = 1;
		pos = mp[y[pos]];
	}
	vis[pos] = 1;
	if(mp.count(y[pos]) == 0){
		g.push_back(y[pos]);
	}
	if(n & 1){//分奇偶输出，因为奇数个奇数号的队列会多一个
		for(int i = 0; i < v.size(); i++){
			cout << g[i] << " " << v[i] << " ";
		}
		cout << g[g.size() - 1];//
	}
	else{
		for(int i = 0; i < v.size(); i++){
			cout << g[i] << " " << v[i] << " ";
		}
	}
	return 0;//完美结束。
}
```

---

## 作者：DPair (赞：2)

题解连更计划第7篇
## 【数据】
这道题。。。似乎题面锅了，于是我就上官网找来了数据范围：
$2 <= n <= 2*10^5,a_i,b_i<=10^6$
## 【思路】
水题，评下去！

这道题真的没什么思维含量。

对于一个数列：
$$a_1,a_2,a_3......a_{n-1},a_n$$
显然每个人看到的一定是$a_{k-1},a_{k+1}$，一定是数。

也就是说，出现$0$作为前面人时，此人一定是$a_1$，于是就得出了$a_2$。

然后可以根据$a_2$，推出$a_4,a_6,a_8......a_{2k}$

然后再找**只出现在某人前面**的人，这种人显然只能是$a_1$（因为$a_2,a_3$这些都会同时被前面与后面的人看到，只有$a_1$前面没人）。

然后可以根据$a_1$，推出$a_3,a_5,a_7......a_{2k - 1}$

然后显然可以得出整个数列。

整体思想就是分别找到所有下标为奇数的数的开头（$a_1$），和所有下标为偶数的数的开头（$a_2$），然后向后遍历，遍历方法我就不赘述了，直接记录每个数的后继，输出当前数后把自己变为后继即可。

## 【代码】
题目很水，所以根本没在意复杂度，有更优做法的欢迎在评论中提出。
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x)
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x)
{
    if(x < 0)
    {
        putchar(45);
        x = -x;
    }
    if(x > 9)
    {
        fprint(x / 10);
    }
    putchar(x % 10 + 48);
}
int n;
int a[1000010], ans[200010], cur[2];
bool b[1000010];
int main()
{
	read(n);
	for (register int i = 1;i <= n;i ++)
	{
		int u, v;
		read(u);read(v);
		a[u] = v;
		if(v == 0) a[u] = -1;
		b[v] = true;
	}
	for (register int i = 1;i <= 1000000;i ++)
	{
		if(a[i] && !b[i])
		{
			cur[1] = i;
			break;
		}
	}
	cur[0] = a[0];
	for (register int i = 1;i <= n;i ++)
	{
		fprint(cur[i & 1]);
		cur[i & 1] = a[cur[i & 1]];
		putchar(32);
	}
} 
```

---

## 作者：jiangruibo (赞：1)

### 思路：
- 首先每个人的**前面**与**后面**的关系存好。

- 然后枚举找到**初始位置**与**结束位置**，去循环一个一个放，记着要**按顺序放**，类似奇数和偶数**交替放**。

### 代码：
```
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
typedef long long LL;
using namespace std;

map<int,int> mp1;
map<int,int> mp2;
int fa[1000010];
int ans[200010];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		fa[x]=y;
		mp1[x]++;
		mp2[y]++;
	}
	int top=0;
	int back=0;
	for(int i=1;i<=2000000;i++)
	{
		if(mp1[i]==0&&mp2[i]==1) back=i;
		if(mp1[i]==1&&mp2[i]==0) top=i;
		if(top!=0&&back!=0) break;
	}
	ans[1]=top;
	ans[n]=back;
	for(int i=2;i<=n-1;i++) 
	{
		ans[i]=fa[ans[i-2]];
	}
	for(int i=1;i<=n;i++) 
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}	 			 	
/*
*/
```

---

## 作者：TheSky233 (赞：1)

## Description
给定 $n$ 个点的前驱和后继，求整个数列。
## Solution
### 主要思路
分析一下样例，发现 $a_1$ 的后继为 $a_2$，而 $a_2$ 的后继恰好为 $a_4$ 的前驱，$a_4$ 的后继又为 $a_6$ 的前驱，以此类推，我们就可以推出整个序列**下标为偶数**的数。

同理，$a_1$ 的后继为 $a_3$ 前驱，$a_3$ 后继又为 $a_5$ 的前驱，以此类推，我们就可以推出整个序列**下标为奇数**的数。
### 思路实现
定义 $pre$ 数组存储读到的数的前驱和后继, $ans1$ 数组为奇数序列，$ans2$ 数组为偶数序列。

要推出下标为偶数的序列很简单，只需要看哪个数的前驱为 $0$，然后通过循环不断扫过当前数的后继，并把后继赋给这个数即可。

不难发现，$a_1$ 只在 $a_2$ 的前驱中出现过 $1$ 次，所以可以在读入时用 ```map``` 和 ```set``` 统计前驱和后继出现次数。读入完时扫一遍 ```set```，如果在 ```set``` 中的数只被统计了一次，说明这个数一定是 $a_1$。

### Code
```cpp
#include <iostream>
#include <set>
#include <map>
using namespace std;

const int N=2e6+5;

int ans1[N],ans2[N],pre[N];
int n,a,b,cnt1=1,cnt2=2,pos;
map<int,int> m;
set<int> s;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		pre[a]=b;
		m[a]++; m[b]++;
		s.insert(a);
	}
	for(int i=0;pre[i]!=0;i=pre[i]) ans1[cnt1]=pre[i],cnt1++;//先找偶数序列
	set<int>::iterator it;
	for(it=s.begin();it!=s.end();it++) if(m[*it]==1) break;
	pos=*it;
	ans2[1]=pos;//找a[1]，并赋值给奇数序列的第一个
	for(int i=pos;pre[i]!=0;i=pre[i]) ans2[cnt2]=pre[i],cnt2++;//找奇数序列
	int op=0,l1=1,l2=1;
	for(int i=1;i<=n;i++){//交替着输出
		if(op) {cout<<ans1[l1]<<' ';l1++;}
		else {cout<<ans2[l2]<<' ';l2++;}
		op^=1;
	}
	return 0;
}
```
## Conclusion
实践起来还是挺难做的，一堆细节等着处理
## [AC](https://www.luogu.com.cn/record/68147574)

---

## 作者：FutaRimeWoawaSete (赞：1)

题意：$n$ 个人排成一列，现在给出每个人前后人的标号问你这 $n$ 个人怎么排的。              

考虑我们可以通过开头是 $0$ 的标号找出第一个人是哪条信息；         

然后我们知道第一个人只会在所有数中出现一次并且他还是在一个人的前面，可以找到第一个人是谁；               

接着我们就知道了第二个人是谁，再根据他前面是第一个人那么他的信息也可以找到，以此类推找完所有人。              

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
int n,m,cnt[Len],fir,to[Len],head[Len];
struct node
{
	int a,b;
}Sec[Len];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d %d",&Sec[i].a,&Sec[i].b);
		cnt[Sec[i].a] ++ , cnt[Sec[i].b] ++;
		head[Sec[i].a] = i;
	}
	int nowused1,nowused2;
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(cnt[Sec[i].a] != 2){fir = Sec[i].a , nowused1 = i;}
		if(!Sec[i].a) nowused2 = i;
	}
	printf("%d ",fir);
	int cnt = n - 1;
	while(cnt)
	{
		printf("%d ",Sec[nowused2].b);
		int suf = head[Sec[nowused2].b];
		nowused2 = nowused1;
		nowused1 = suf;
		cnt --;
	}
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

## 思路
这道题可先用数据结构存储每个数字作为头和尾的数量，找到**起点和终点**。

再记录前后关系，因为一个是前面的人，一个是后面的人，则**跳两个依次放入答案数组**即可。

最后输出，顺利 **AC**。
## code

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optmize(3)
using namespace std;
map<int,int> mpt,mpw;
int g[2000005];
int a[2000005];
int n;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		g[x]=y;
		mpt[x]++;
		mpw[y]++;
	}
	for(int i=1;i<=1000000;i++)
	{
		if(mpt[i]==0&&mpw[i]) a[n]=i;
		if(mpw[i]==0&&mpt[i]) a[1]=i;
	}
	for(int i=2;i<=n-1;i++)
	{
		a[i]=g[a[i-2]];
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 用 $mp$，和 $mp1$ 数组记录**相隔的两个数**。
- 先找到**排头**和**排尾**。
1. 找排头：因为排头只会出现一次，且只会在那一对输入数据的左边。所以可以用 $mp$ 记录每对数右边数是标记了的，再循环判断每对数左边数是否标记，若没有，它就是排头。

2. 找排尾：（同排头）因为排尾只会出现一次，且只会在那一对输入数据的右边。所以可以用 $mp1$ 记录每对数左边数是标记过的的，再循环判断每对数右边数是否标记，若没有，它就是排尾。

- 在用 $go$ 数组记录相隔的两个数，最后分奇偶赋值给 $ans_{i}$ 即可。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=5*10e5+1000;

int n,root;
int go[N];
int ans[N];
map<int,bool> mp;
map<int,bool> mp1;
struct node{
	int l,r;
}a[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		go[a[i].l]=a[i].r;
		mp[a[i].r]=true;
		mp1[a[i].l]=true;
	}
   //排头只会在左边出现
	for(int i=1;i<=n;i++){
		if(mp[a[i].l]){
			continue;
		}
		root=a[i].l;
		break;
	}
	ans[1]=root;
	for(int i=3;i<=n;i+=2){
		ans[i]=go[ans[i-2]];
	}
	for(int i=2;i<=n;i+=2){
		if(i==2){
			ans[i]=go[0];
		}
		else{
			ans[i]=go[ans[i-2]];
		}
	}
   //排尾只会在右边出现
	for(int i=1;i<=n;i++){
		if(mp1[a[i].r]){
			continue;
		}
		root=a[i].r;
		break;
	}
	ans[n]=root;
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：追梦之鲸 (赞：0)

本蒟蒻的第$017$篇题解。

[经典回顾CF490B](https://www.luogu.com.cn/problem/CF490B)

06-14 17:14:02 纪念最优解

### 思路

本蒟蒻用的是链表。

我把没一组数都把它当一条线连起来，那么最后会长成这个样子（图中的数为所在队列里位置的名次，$0$ 除外）：

![](https://bj.bcebos.com/im-cs/5eba6d219caae5c06d3d942c403a9083.PNG)

看到这个，你是否有思路了？没错，$0$ 后面的数在队列里排名分别是 $\text{2、4、6、8…}$，前面的数在队列里排名分别是 $\text{1、3、5、7…}$然后我们只需从 $0$ 往后搜一次再往后搜一次就干完了，
**但是这只适用于 $n$ 是偶数！**
那我们看看 $n$ 是奇数时链表会连成什么熊样子（同上）：

![](https://bj.bcebos.com/im-cs/6248a7d4caf99efeea74d10b2c382dff.PNG)

排名为偶数的可以向上面那样办，但是奇数好像有点麻烦，但我们可以这么干：在所有数中找到一个前面没数但后面有数的数，那么这个数就是最前面的数（因为偶数部分是一个环），
**但是这样找出来的数也包括在队列中第二个数！**
因为第二个数的前面那个数是 $0$，我被这个坑了一次，所以我们搜之前把第二个数修改一下就完事了。

### Code：
```c
#include<bits/stdc++.h>//本人马蜂有问题，请见谅
#define ull unsigned long long
#define ll long long
#define ri register
#define SOR(wqq,wqw,qwq) for(wqq=wqw;wqq<qwq;wqq++)
#define FOR(iee,eei,eie) for(iee=eei;iee<=eie;iee++)
#define DOR(eii,iie,iei) for(eii=iie;eii<=iei;++eii)
#define ROR(qww,wwq,wqw) for(qww=wwq;qww>=wqw;qww--)
using namespace std;
template <class O>
inline void read(O &x) {ri char c = getchar();x=0;for (; !isdigit(c); c = getchar());for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);return;}
//快读
const int N=200010;
const int M=1000010;
struct qwq{
	int next;
	int from;
}f[M];//链表
int n,a,b,x[N],top;
int main()
{
	int i,j;
	read(n);
	FOR(i,1,n){
		read(a);read(b);
		f[a].next=b;
		f[b].from=a;
	}
	i=0;top=2;
	f[f[i].next].from=-1;//一定要修改！
	while(f[i].next){
		x[top]=f[i].next;
		i=f[i].next;
		top+=2;
	}
	i=0;
	if(n%2){//n=奇数
		top=1;
		FOR(j,1,M){
			if(f[j].from==0&&f[j].next!=0){//不要把“&&f[j].next!=0”给忘了！
				i=j;
				break;
			}
		}
        //查找第一个数
		while(i){//注意这里不是f[i].next，要算上第一个数
			x[top]=i;
			i=f[i].next;
			top+=2;
		}
	}
	else {//n=偶数
		top=n-1;
		while(f[i].from){
			x[top]=f[i].from;
			i=f[i].from;
			top-=2;
		}
	}
	FOR(i,1,n)printf("%d ",x[i]);
	return 0;
}
```

---

## 作者：Insouciant21 (赞：0)

因为在这道题上面栽了几次，所以就跑过来写题解了（（（

数据范围为 $ 2\leq n\leq2\times10^5, 0\leq a_{i},b_{i}\leq10^6$

这道题直接暴力算肯定TLE，所以要考虑更简单的方法：

对于队列中的第一个和最后一个，即 $ans_{1}, ans_{n}$ ，可以发现他们在整个输入中各只出现过了一次

如样例

```
输入：			输出：
4			92 7 31 141  
92 31
0 7
31 0
7 141
```

$92$ 和 $141$ 各只出现一次，$92$为前面看到的数，故 $92$ 为第一个， $141$ 为最后一个

由此可以得到队列中的第二个数为前面看到的为 $0$ 的那个数，即 $ans_{2}=f_{0}$

再向后推 第三个数前面看到的是第一个数，即有 $ans_{3}=f_{1}$

可发现规律 
$$ ans_{i}=f_{ans_{i-2}}
$$

AC代码如下：

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e6) + 10;

int n;
int f[maxn];
int usea[maxn];
int useb[maxn];
int ans[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        f[l] = r;
        usea[l]++, useb[r]++; // 出现次数统计
    }
    for (int i = 1; i <= int(1e6); i++) { // 筛出开头和结尾
        if (usea[i] == 1 && useb[i] == 0)
            ans[1] = i;
        if (useb[i] == 1 && usea[i] == 0)
            ans[n] = i;
        if (ans[1] && ans[n])
            break;
    }
    for (int i = 2; i <= n; i++) ans[i] = f[ans[i - 2]]; // 如上式子
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}
```

---

