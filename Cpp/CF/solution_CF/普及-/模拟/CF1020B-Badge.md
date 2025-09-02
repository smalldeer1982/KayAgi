# Badge

## 题目描述

在一所学校，如果一个学生表现不好，老师就会在他的徽章上打一个洞。今天，老师逮到了n名学生在搞恶作剧。

这些学生从1到n编号。老师先逮到了a学生然后在他的徽章上打了个洞。但是这个学生说带头的是另一个学生pa。

于是老师又抓住学生pa在他的徽章上也打了个洞。这个学生又说其实是学生ppa在带头搞恶作剧。

这个过程一直持续了好一会儿，不过因为这些学生是有限的，最后老师抓住了一个徽章上已经有一个洞的学生。

在给这个倒霉孩子的徽章上又打了个洞以后，老师觉得有点累，需要蒸个桑拿于是他就不再继续了。

你不知道谁是老师逮到的第一个学生，但是你知道所有的数字pi。对于每一个a，如果第一个被逮到的学生是a，你的任务是找到谁会是徽章上面有两个洞的学生。

## 说明/提示

![图片](http://codeforces.com/predownloaded/e6/2f/e62f6279b291a91d10dcf8b13b483a9dc5659758.png)

当a = 1, 老师的打洞顺序是1->2->3->2，输出2（2的徽章上会有俩洞）；

当a = 2, 老师的打洞顺序是 2->3->2，输出2； 当a = 3，老师的打洞顺序是3->2->3，输出3。

对于第二个样例，不管老师先逮到谁，这个第一个被老师逮到的倒霉孩子将会得到两个洞。

## 样例 #1

### 输入

```
3
2 3 2
```

### 输出

```
2 2 3 
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
1 2 3 
```

# 题解

## 作者：dalao_see_me (赞：4)

我们可以把题目想象成一个有n个点的有向图（每个点出度为 $1$ ），让你从一个点开始遍历，直到遍历到一个被遍历过的点。

然后呢？就dfs跑呗，直到找到一个被遍历过的数就输出该数。时间复杂度 $O(n^2)$，可过。

贴上我奇丑无比的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f;
int fa[10086],vis[10086];
inline void dfs(int k)
{
	if(vis[k])f=k;
	if(f)return;
	vis[k]=1;
	dfs(fa[k]);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>fa[i];
	for(int i=1;i<=n;i++)
	{
		f=0;
		memset(vis,0,sizeof(vis));
		dfs(i);
		cout<<f<<' ';
	}
	return 0;
}
```

---

## 作者：LiRewriter (赞：3)

为什么建图$O(n)$乱搞会比$O(n^2)$暴力慢呢 不开心

我们关注到，每个点的出度是1.如果将$v$与$p[v]$连边，一定可以形成一个基环树森林。

然后对每一颗基环树考察，如果某个点在环上，答案一定是这个点本身。

如果某个点不在环上，那么答案一定是最近的能到达的环上的点。

所以我们可以先拓扑排序一遍，预处理出来所有环上的点，之后就可以$O(n)$的求解出来外向树上的点。

我是用dfs实现的，不过感觉好像按拓扑序逆向处理一下也行的样子……

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node{
	int nxt, to;
};
//qaq 
node E[1003];

int head[1003], cnt = 1, deg[1003], p[1003], n, ans[1003], degree[1003];

bool on_circ[1003];

inline void add_edge(int fr, int to) {
	E[cnt].to = to; E[cnt].nxt = head[fr]; head[fr] = cnt++; 
	degree[to] += 1;
} 

void findcirc() {
	queue<int> q;
	for(int i = 1; i <= n; ++i) if(!degree[i]) q.push(i);
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		for(int p = head[cur]; p; p = E[p].nxt) {
			int nx = E[p].to;
			degree[nx]--;
			if(!degree[nx]) q.push(nx);
		}
	}
	for(int i = 1; i <= n; ++i) if(degree[i]) on_circ[i] = 1;
}

int dfs(int x) {
	if(ans[x]) return ans[x];
	for(int i = head[x]; i; i = E[i].nxt) {
		ans[x] = dfs(E[i].to);
	}
	return ans[x];
}

void getans() {
	for(int i = 1; i <= n; ++i) 
		if(on_circ[i]) ans[i] = i;
	for(int i = 1; i <= n; ++i) {
		if(!ans[i]) dfs(i);
	}			
} 

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
	for(int i = 1; i <= n; ++i) add_edge(i, p[i]);
	//for(int i = head[1]; i; i = E[i].nxt) cout<<E[i].to<<" ";
	findcirc();
	getans();
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
}
```

---

## 作者：RiceFruit (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1020B)

# 题目大意：

给你 $n$ 个学生，每个学生都指向另一个学生，要你求从每一个学生出发，沿着他指向的学生走，第一个出现两次的学生编号。
    
# 题目思路：

我们考虑到朴素算法，每次都暴力跑一边，时间复杂度为 $O(N^2)$，而 $N\le5000$ ,不会超时。

# 代码：

这道题实现非常简单，没有太多的细节，可以作为递归基础题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2001;
int n;
int a[N+1];
bool b[N+1];
int h(int x){//表示当前递归到的学生编号
	if(b[x])return x;//如果已经出现了一次，则直接返回
	b[x]=1;//打标记，表示出现了一次
	return h(a[x]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		memset(b,0,sizeof(b));//将标记清空
		printf("%d ",h(i));
	}
	return 0;
}

```


---

## 作者：virtualman (赞：2)

我的做法是纯模拟，这道题可以想象成一个链表，坏同学指向另一个坏同学，然后顺着链表走一遍，任何一个同学走遍历了两遍时，停止遍历，并输出该同学的编号即可！

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;
int p[1005];
int book[1005]={0};
int pan(int x)
{
    memset(book,0,sizeof(book));
    int now=x;
    while(1)
    {
        book[now]++;
        now=p[now];
        if(book[now]==2)return now;
    }
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
    }
    for(int i=1;i<=n;i++)
    {
        cout<<pan(i)<<" ";
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

## 分析

很简单，模拟即可。

我们开个标记数组，记录每个学生是否被打洞过。若再次跳到这个学生时，这个学生已经被打过，则这个学生就是第一个有两个洞的人，输出即可。注意，对于每一个 $i$，我们都需要清空数组哦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,bool> vis;
int n;
const int N=1e6+10;
int a[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		vis.clear();
		int now=a[i];
		vis[i]=1;
		while(1)
		{
			if(vis[now])
			{
				cout<<now<<" ";
				break;
			}
			else vis[now]=1,now=a[now];
		}
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 分析

很简单，模拟即可。

我们开个标记数组，记录每个学生是否被打洞过。若再次跳到这个学生时，这个学生已经被打过，则这个学生就是第一个有两个洞的人，输出即可。注意，对于每一个 $i$，我们都需要清空数组哦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,bool> vis;
int n;
const int N=1e6+10;
int a[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		vis.clear();
		int now=a[i];
		vis[i]=1;
		while(1)
		{
			if(vis[now])
			{
				cout<<now<<" ";
				break;
			}
			else vis[now]=1,now=a[now];
		}
	}
	return 0;
}
```


---

## 作者：knsg251 (赞：0)

## 题目意思
老师不停询问，第一个被问了两次的同学要叫家长，请求出是谁。
## 题目分析
这道题可以写暴力，按着题目的意思来就行。用一个数组标记有没有被询问过，被询问到的同学就直接标记，如果标记了两次就直接输出即可。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans;
int a[200005];
bool f[200005];//标记 
int main(){
	cin>>n;	
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);//输入 
	for(int i=1;i<=n;i++){
		ans = i;//给ans赋值 
		memset(f,0,sizeof f);//清空 
		while(1){
			if(f[ans]) break;//如果已经被标记过就输出 
			f[ans] = 1;//标记 
			ans = a[ans];//重新赋值 
		}
		printf("%d ",ans);//输出 
	}
	return 0;//over 
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

题目分析：

由 $n$ 个数字组成的有向图，求当起点为 $n_i$ 时，第一个第二次经过的值。

正解应为链表，但考虑到此题时间限制不高，故暴力模拟即可。

（好像可以记忆化优化，但我懒得改了）代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n[1010];
int l[1010];
void dfs(int a){
	if(l[a]==1){
		cout<<a<<' ';
		return;
	}else{
		l[a]=1;	
	}
	dfs(n[a]);
}
int main(){
	int a;
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>n[i];
	}
	for(int i=1;i<=a;i++){
		memset(l,1010,sizeof(l));//一定要初始化，不然会WA+TLE
		dfs(i);
	}
	return 0;
} 
```


---

## 作者：Mabangjie6789 (赞：0)

## 题目简述

有一个有向图，每个点的出度均为 $1$，现在让你从每个点开始遍历，问第一个被遍历两次的点。

## 题目思路

首先我们能看出这是一道简单图论题。

题目要求我们对于每个学生，找出徽章上面有两个洞的学生。

我们从这个学生开始，遍历整张图，每到一个点就把这个点标记一次，找到第一个被标记两次的学生，这个学生就是答案。由于每个点只指向一个点，这道题甚至不用建图。

我们发现 $n \le 1000$，而这道题的时间复杂度是 $O(n^2)$，完全可以通过时间限制。

### 我的方法

- 记录每个学生 $i$ 指向的学生 $p_i$。
- 对于每个学生 $i$：
	1. 把是否标记的数组 `vis[]` 清空；
   1. 用函数 `fnd()` 找到第一个被遍历两次的学生。

其他细节见程序的注释。

## 代码

```cpp
#include <cstring>
#include <iostream>
using namespace std;

int n, p[1005];
bool vis[1005];
int fnd(int x){
	if (vis[x])
		return x;//如果被标记过了，就是他
	vis[x] = 1;//标记
	return fnd(p[x]);//继续往后
}
int main(){
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= n; i++){
		memset(vis, 0, sizeof(vis));//要记得把数组清零
		cout << fnd(i) << " ";
	}
	cout << endl;
	return 0;
}
```

---

## 作者：MYFJWHR (赞：0)

## 思路

首先看范围：$1 \le N \le 10^3$。

范围特别小，最简单的方式就是暴力，所以就直接模拟加递归，如果当前的号码已经被标记了，那么直接返回当前号码；否则，就标记当前号码，再继续进行递归。

因为每次递归的层数不超过 $N$ 层，每次初始化数组也需要 $O(N)$ 的时间复杂度，一共有 $N$ 次初始化和递归，所以这样的做法的时间复杂度就为 $O(N^2)$。

## AC Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],f[10005];
int find(int i){
	if(f[i]==1) return i;
	else{
		f[i]=1;
		return find(a[i]);
	} 
}
void fou(){
	for(int i=1;i<=n;i++) f[i]=0;
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		printf("%d ",find(i));
		fou();
	}
	return 0;
}
```



---

## 作者：_lgh_ (赞：0)

# 思路：模拟
使用 $bool$ 数组存储是否被抓过，初始为 $0$ ，如果被抓后分类讨论：还未被抓过（即为 $0$ ）更改为 $1$ ，如果是 $1$ 直接输出然后跳出循环。

## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int stu,ppp;//stu是人数，ppp就是学生当前指认的人
int a[1005];
bool b[1005];//bool数组
int main() {
  cin>>stu;//输入
  for(int i=1; i<=stu; i++) cin>>a[i];//还是输入
  for(int i=1; i<=stu; i++) {
    ppp=i;//第一个被抓的需要从一开始枚举
    memset(b,0,sizeof(b));//防止上一次的1没有清除
    while(1){
      if(b[ppp]){//如果被抓到过
        cout<<ppp<<' ';//输出
        break;//退出
      }
      b[ppp]=1,ppp=a[ppp];//被抓了一次，他指认了输入时的那个人
    }
  }
  return 0;
}
```


---

## 作者：Indulge_myself (赞：0)

## 前言及算法点明：
大概看了一下，发现很多大佬都是用图论来解决的。就连最水的一篇题解也是用到了链表的思想。

其实，这道题就是一个大~~暴力~~模拟。

# 思路：
我们只需要按照题目意思模拟就好。

输入 $ n $ 之后，首先我们定义数组 $ p_{n} $ 来存储学生间互相“告状”的情况。定义数组 $ ch_{n} $ 来记录第 $ i $ 个学生的徽章的打孔数。

在这里就有了两个问题。


------------
一、看到题目里的 $ p_{p_{a}} $ 了吗？如果有更多的嵌套，我们难不成还要定义一个数组来记录每一个 $ p_{a} $?

二、因为条件是只要有任意一个学生的打孔数达到 2，那么就必须结束。难道我们还需要在每一次操作后再 $ O(n) $ 地去扫一遍？

其实，完全不需要。

# 解法：
我们优先考虑第一个问题。其实，解决第一个问题的方法很简单。我们定义一个 $ js $ 变量来记录当前的 $ p_{a} $，之后每循环一次就更新一次。

因为这道题并不需要我们时刻记录 $ js $ 的值，所以保存 $ js $ 并没有什么用。

当我们更新完 $ js $ 的值后，其实我们也可以顺便解决第二个问题。

因为有 2 个孔的学生必然是在被打完第一个孔之后又被打上了第二个，所以当我们模拟打完第 $ i $ 个学生的一个孔时，就可以直接判断 $ ch_{i} $ 是不是已经变成了 2。如果是直接输出即可。

# Code：
```cpp
#include<cstring>
#include<iostream>
using namespace std;
int p[100001],ch[100001]; 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>p[i];
	for(int i=1;i<=n;i++)
	{
		memset(ch,0,sizeof(ch));
		int js=i;
		while(true)
		{
			ch[js]++;
			if(ch[js]==2)
			{
				cout<<js<<" ";
				break;
			}
			js=p[js];
		}
	}
	return 0;
}
```

感谢大家的阅读及管理大大的审核！如果有错误欢迎指出！

---

## 作者：zzh_han (赞：0)

## 题意

有 $n$ 个点现在输入 $a[i]$ 表示点 $n$ 和 $a[i]$ 之间有一条连边，再不同点为起点来走一边看这个点是否来过如果来过就输出这个点的坐标并退出。

## 做法

做法其实就是一个模拟每次从不同的点出发如果到达的点已经来过那直接输出就可以了。上代码!!!!

```c++
#include <bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=10;
int f[1005],vis[1005],sum,b=0;
void dfs(int n)
{
	if(b==1)
		return;//如果找到答案就退出循环
	if(vis[n]==1)
	{
		b=1;//来判断是否找到答案
		sum=n;//如果这个点来过把sum改成这个点的下标
		return;
	}
	else
		vis[n]=1;//赋值成1表示n这个点来到过
	dfs(f[n]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	for(int i=1;i<=n;i++)
	{
		sum=0;
		b=0;
		memset(vis,0,sizeof(vis));//判断这个点是否来过
		dfs(i);
		printf("%d ",sum);
	}
} 
```



求点赞qwq

---

## 作者：Trilliverse (赞：0)

### 题目分析：
- 每个人都记录下个人的编号是谁，我们可以通过不断的循环来找到第一次某编号次数为2的那个点，输出然后 break 即可。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
  
int p[1005],cnt[1005]; 

int main() {
	int n;
	cin >> n;
	for(int i=1;i<=n;i++) cin >> p[i];
	for(int i=1;i<=n;i++) {
		mem(cnt,0);//注意每找一次都要清空数组
		int nxt = i;
		while(1) {
			cnt[nxt]++;
			if(cnt[nxt] == 2) {
				cout << nxt << " ";
				break;
			}
			nxt = p[nxt];//指向下一个人
		}
	}
	return 0;
}
```
### 本题其实还有一种思路：
- 线性做法，根据数据建一条单向边，因为一定会出现某一个点的次数为2，所以这个图一定存在环，那么如果第一个找的人在环上，那么答案一定就是自己的编号（因为绕换一圈又绕回到自己），如果不在环上，那答案就是第一次入环的那个点的编号。

~~大佬们有兴趣可以尝试下**图论**做法，本蒟蒻用的**模拟**~~


---

## 作者：David_H_ (赞：0)

这一题的话，模拟就完事了。

本题主要是对于链表进行一次大模拟。

读入的话，直接输入`to[i]`就可以了，然后对于每一个`i`，指向下一个`pi`（也就是`to[i]`）。

期望时间复杂度$O(n^2)$，对于$n=1000$还是绰绰有余的。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
bool vis[1005];
int n;
int to[1005];
int i, j;
int main(void) {
	scanf("%d", &n);
	for(i = 1; i <= n; i++) {
		scanf("%d", &to[i]);
	}
	for(i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		for(j = i; !vis[j]; j = to[j]) vis[j] = true;
		printf("%d ", j);
	}
	return 0;
}
```

已AC：

![](https://cdn.luogu.com.cn/upload/image_hosting/w7xzdzen.png)

---

