# Bear and Forgotten Tree 3

## 题目描述

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges. Vertices are numbered $ 1 $ through $ n $ .

Limak is a little polar bear and Radewoosh is his evil enemy. Limak once had a tree but Radewoosh stolen it. Bear is very sad now because he doesn't remember much about the tree — he can tell you only three values $ n $ , $ d $ and $ h $ :

- The tree had exactly $ n $ vertices.
- The tree had diameter $ d $ . In other words, $ d $ was the biggest distance between two vertices.
- Limak also remembers that he once rooted the tree in vertex $ 1 $ and after that its height was $ h $ . In other words, $ h $ was the biggest distance between vertex $ 1 $ and some other vertex.

The distance between two vertices of the tree is the number of edges on the simple path between them.

Help Limak to restore his tree. Check whether there exists a tree satisfying the given conditions. Find any such tree and print its edges in any order. It's also possible that Limak made a mistake and there is no suitable tree – in this case print "-1".

## 说明/提示

Below you can see trees printed to the output in the first sample and the third sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639B/d620db1cf9f574a403a626cbbf75f44f3128c4d9.png)

## 样例 #1

### 输入

```
5 3 2
```

### 输出

```
1 2
1 3
3 4
3 5```

## 样例 #2

### 输入

```
8 5 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8 4 2
```

### 输出

```
4 8
5 7
2 3
8 1
2 1
5 6
1 5
```

# 题解

## 作者：fuxuantong123 (赞：3)

# CF639B Bear and Forgotten Tree 3 题解
## 思路
显然，$2 \times h < d$ 的树是不存在的，输出 $-1$。

对于 $n=2$ 的情况，只有 $h=1$，$d=1$ 时是可以的。

其余情况，先向根的一边连一条长度为 $h$ 的链，再向其另一边边连一条 $d-h$ 的链。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,h,d;
	scanf("%d%d%d",&n,&d,&h);
	if(2*h<d || (d==1 && n>=3 && h==1)){
		printf("-1");
		return 0;
	}
	for(int i=1;i<h;i++){
		printf("%d %d\n",i,i+1);
	}
	if(d>h){
		printf("1 %d\n",h+2);
		for(int i=h+2;i<=d;i++){
			printf("%d %d\n",i,i+1);
		}
	}
	for(int i=d+2;i<=n;i++){
		printf("%d %d\n",h,i); 
	}
return 0;
}
```


---

## 作者：樱雪喵 (赞：2)

要交不上作业了 /oh

## Description

给定 $n,d,h$，构造一棵有 $n$ 个点，直径为 $d$，高度为 $h$ 的树。  

$n\le 10^5$。

## Solution

首先 $d>2h$ 是无解的，$d=h=1$ 且 $n>2$ 的时候也无解。

对其它情况，先从根构造两条长度分别为 $h$ 和 $d-h$ 的链。  
剩下的点如果 $d=h$ 就随便挂在除根和叶子以外的位置上，$d\neq h$ 就挂在根上。

```cpp
const int N=1e5+5;
int n,d,h;
int main()
{
    n=read(),d=read(),h=read();
    if(d>2*h) {printf("-1\n");return 0;}
    if(d==1&&h==1&&n>2) {printf("-1\n");return 0;}
    for(int i=2;i<=h+1;i++) cout<<i-1<<" "<<i<<endl;
    for(int i=h+2;i<=d+1;i++) cout<<((i==h+2)?1:i-1)<<" "<<i<<endl;
    for(int i=d+2;i<=n;i++) cout<<((d==h)?2:1)<<" "<<i<<endl;
    return 0;
}
```

---

## 作者：OIerJiang_1017 (赞：1)

## [CF639B 题目传送门](https://www.luogu.com.cn/problem/CF639B)

## 题目大意
请你构造一棵包含 $n$ 个节点，其中节点编号从 $1$ 到 $n$，并以 $1$ 号节点为根节点，直径为 $d$，高度 $h$ 的树。其中树的直径为树上**两节点之间的最大距离**，树的高度指的是**根节点到其它节点的最大距离**。若满足，则按任意顺序输出每一条边，否则输出 $-1$。

## 解决方法
首先考虑特殊情况：
- 特判一：当 $n=2$ 时，只有 $h=1$ 且 $d=1$ 可以。
- 特判二：当 $2 \times h < d$ 时，因为无解，所以输出 $−1$。

其他情况正常考虑：构造一棵 $n$ 个点，深度 $h$，最长链长度为 $d$ 的树。先从根构造两条长度分别为 $d-h$ 和 $h$ 的链，然后剩下的点如果 $d\not=h$ 就挂在根上，输出 $1$ 即可，如果 $d=h$ 就随便挂在除根和叶子以外的位置上，输出 $2$ 即可。

## 代码展示
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, d, h;//建议scanf,更快
	scanf("%d%d%d", &n, &d, &h);
	if(d > (2 * h) || (d == h && h == 1 && n > 2))
	//1.通过样例可知d必须<=2h若不满足就输出-1
	//2.当d=h=1且n>2时，也输出-1
	{
		printf("-1\n");//建议printf,更快
		return 0;
	}
	for(int i = 2; i <= h + 1; i++)
		printf("%d %d\n", i-1, i);
	for(int i = h + 2; i <= d + 1; i++)
  //分类讨论
		if(i == h + 2) printf("1 %d\n", i);
		else printf("%d %d\n", i-1, i);
	for(int i = d + 2; i <= n; i++)
		if(d != h) printf("1 %d\n", i);
		else printf("2 %d\n", i);
	return 0;
}
``````

---

## 作者：zym20249_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF639B)
## 题意
你需要构造一个图，直径为 $d$ ，高度为 $h$，有n个节点，编号为 $1$ 到 $n$。其中直径为一个节点到另一个节点的最大距离，最大距离为根节点到某个节点的最大距离。\
问是否满足，满足则输出每一条边，顺序和样子随意。不满足则输出 $-1$。
## 思路
通过理解可以得知 $d \leq h \leq 2d$，有一个非常好实现的办法，首先特判排除特殊情况。先制作一条链，满足 $h$，如果 $d$ 不满足，则在另起一条链满足。其余的节点只需在任意一个节点，（非根节点和叶子结点）增加一条链，满足 $n$。
## code
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int n,h,d;//题目给出 
int main()
{
	scanf("%d%d%d",&n,&h,&d);//scanf更快 
	if(n-1<h||h>d*2) //特判 
	{
		puts("-1");//puts比printf更快，自带换行 
		return 0;
	}
	if(h==d)//如果h等于d，则无需增加一条连接根节点的链 
	{
		if(n-(h+1)>0&&h==1) //特判 
		{
			puts("-1");
			return 0;
		}
		for(int i=1;i<=h;i++)printf("%d %d\n",i,i+1);
		for(int i=h+2;i<=n;i++)printf("2 %d\n",i);//都连到节点2上面 
		return 0;
	}
	//其他情况 
	for(int i=1;i<=d;i++) printf("%d %d\n",i,i+1);
	for(int i=d+2,l=1;i<=h+1;i++) //一开始l=1，连接到根节点上，后面都连接到上一个点 
	    printf("%d %d\n",l,i),l=i;
	for(int i=h+2;i<=n;i++) printf("1 %d\n",i);
	return 0;
}
``````

---

## 作者：wgyhm (赞：1)

# 【构造记录】CF639B Bear and Forgotten Tree 3

## 题目大意

构造一棵 $n$ 个点，深度 $h$，最长链为 $d$ 的树。

$2\le n\le 10^5,1\le h\le d<n$



## 题解

不妨以 $1$ 为根节点。

显然对于 $d>2h$ 的树是不存在的。

1. 构造一条 $[1,h+1]$ 的链。保证树高符合题意。
2. 构造一条 $1->[h+2,d+1]$ 的链，保证直径符合题意。
3. 剩下的节点与 $h$ 相连，显然是符合题意的。

 但是，对于 $h=1,d=1$ 的情况，当前仅当 $n=2$ 。这点需要注意。

## Code:

```cpp
int n,h,d;
signed main(){
    rg int i;
    read(n);read(d);read(h);
    if (d>h*2) return puts("-1"),0;
    if (d==1&&h==1&&n>2) return puts("-1"),0;
	for (i=2;i<=h+1;i++) printf("%d %d\n",i-1,i);
	if (d>h) {
		printf("1 %d\n",h+2);
		for (i=h+3;i<=d+1;i++) printf("%d %d\n",i-1,i);
	}
	for (i=d+2;i<=n;i++) printf("%d %d\n",h,i);
    return 0;
}
```



---

## 作者：封禁用户 (赞：1)

这道题目。。。有蓝题？

瞎搞一下就好了嘛。。。

这道题目我们使用特判的方式来做，然后即能过掉此题。~~还不是因为有SPJ~~

那么，我们如何输出这棵树呢？

1. 深度×2<链长 或者 深度>链长

2. 节点数小于等于链长、深度

3. 链长、深度都为1，结点数>=3（结点只有2时才能满足条件）

截止至2019.02.06为全咕咕最快代码（ $1202ms,0\rm KB,0.56KB$ ）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,h,d;
int main()
{
	scanf("%d%d%d",&n,&h,&d);
	if (n-1<h||h>d*2) 
	{
		printf("-1\n");
		return 0;
	}
	if (h==d)
	{
		if (n-(h+1)>0&&h==1) 
		{
			printf("-1\n");
			return 0;
		}
		for (int i=2; i<=h+1; i++) printf("%d %d\n",i-1,i);
		for (int i=h+2; i<=n; i++) printf("2 %d\n",i);
		return 0;
	}
	for (int i=2; i<=d+1; i++) printf("%d %d\n",i-1,i);
	for (int i=d+2,lst=1; i<=h+1; i++) 
	  printf("%d %d\n",lst,i),lst=i;
	for (int i=h+2; i<=n; i++) printf("1 %d\n",i);
	return 0;
}
```

---

## 作者：longStone (赞：0)

# CF-639B题解

## 观察

这是一道构造题，让我们构造一棵树，这种题大多有SPJ，我们只需要选择一种简单的方式运算即可。

我们看一下第一个样例：```5 3 2```,就是有 $5$ 个节点 $n$，高度 $h$ 为 $2$，任意两点间最长距离 $d$ 为 $3$,观察图片左边那棵树，我们可以$2 \Rightarrow 1 \Rightarrow 3 \Rightarrow 4$ ($3$ 之后也可以到 $5$)。

然后是第三个样例：```8 4 2```，看图片右侧，我们可以选出一条 $3 \Rightarrow 2 \Rightarrow 1 \Rightarrow 8 \Rightarrow 4$ 的路径，长度 $d$ 为 $4$，的同时高度 $h$ 为 $2$。

注意：**$n$ 要求全部连接在树上，$d$ 和 $h$ 要求正好相等。**

![](https://cdn.luogu.com.cn/upload/image_hosting/7zg2q9fg.png)

## 思考

看懂了直径之后，我们发现：直径连接了最左边的节点，$1$，和右边的节点，所以当 $2 \times h > d$ 时，无论如何高度都会超出。还有一种情况，当直径限制为 $1$ 时，如果有至少 $3$ 个点，那么从第三个点开始，将无处可连，因为不管连在哪里都会让直径变为 $2$ 。

当高度限制 $h$ 为 $1$ 但是符合上述所有标准时，直径 $d$ 限制一定为 $2$，这时候我们只需要让 $1$ 连接 $2 \sim n$ 中的每一个值即可。

```c++
if(2 * h < d || (d == 1 && n >= 3))
{
    cout << -1 << endl;
    return 0;
}else if(h == 1)
{
    for(int i = 2;i <= n;i++)	cout << 1 << ' ' << i << endl;
    return 0;
}
```

为了让高度正好满足，优先从点 $1$ 开始先往一个方向填一直到 $h$ ，填满了之后再考虑另外一边。

```c++
for(i = h;i >= 1;i--)
{
    cout << i << ' ' << i + 1 << endl;
    tmp--;
}
```

接着分 2 种方案讨论：

1. 如果另外一边还需要填数，先填完。然后将剩下的点都与 $2$ 连接。
2. 否则所有剩下的点都和 $2$ 连接。

```c++
if(tmp && h + 2 <= n)
{
    cout << 1 << ' ' << h + 2 << endl;
    tmp--;
    for(i = h + 3;i <= n && tmp;i++)
    {
        cout << i << ' ' << i - 1 << endl;
        tmp--;
    }
    for(i;i <= n;i++)	cout << 2 << ' ' << i << endl;
}else	for(i = h + 2;i <= n;i++)	cout << 2 << ' ' << i << endl;
```

## 代码

```c++
#include "bits/stdc++.h"
using namespace std;
int n, d, h, tmp, i;
int main()
{
    cin >> n >> d >> h;
    tmp = d;//tmp记录在完成最长直径还要填多少个数
    if(2 * h < d || (d == 1 && n >= 3))
    {
        cout << -1 << endl;
        return 0;
    }else if(h == 1)
    {
        for(int i = 2;i <= n;i++)	cout << 1 << ' ' << i << endl;
        return 0;
    }
    for(i = h;i >= 1;i--)
    {
        cout << i << ' ' << i + 1 << endl;
        tmp--;
    }//填完了h + 1,接下来从h + 2开始
    if(tmp && h + 2 <= n)
    {
        cout << 1 << ' ' << h + 2 << endl;
        tmp--;
        for(i = h + 3;i <= n && tmp;i++)//h + 3 - 1 = h + 2
        {
            cout << i << ' ' << i - 1 << endl;
            tmp--;
        }
        for(;i <= n;i++)	cout << 2 << ' ' << i << endl;
    }else	for(i = h + 2;i <= n;i++)	cout << 2 << ' ' << i << endl;
    return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF639B)

一道有点难的构造题。

首先，当 $d > 2 \times h$ 时，树的直径要大于两倍的高，显然是不可以的。

其次，当 $d = 1$ 且 $h = 1$ 时，对于 $n > 2$ 的情况是无解的。

判断完这些特殊情况后，就可以开始构造了。

我们先弄出一条长为 $h$ 的链，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yfin23km.png)

此时会分两种情况：

1. 当 $d = h$ 时，此时的直径就是我们刚才构造的链，把剩下的节点接到 $h$ 上面即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2rxt7vl.png)

2. 当 $d > h$ 时，先从 $1$ 号节点下面搞一条长为 $(d - h)$ 的链，现在的直径是 $[h+1,d+1]$。再把剩下的节点接到 $h$ 上面。

![](https://cdn.luogu.com.cn/upload/image_hosting/whdxt7kf.png)

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, d, h;
int main(){
	scanf("%d%d%d", &n, &d, &h);
	if (d > h * 2 || d == 1 && h == 1 && n > 2){puts("-1"); return 0;}
	for (int i = 1; i <= h; i++) printf("%d %d\n", i, i + 1);
	if (d == h) for (int i = h + 2; i <= n; i++) printf("%d %d\n", h, i);
	else{
		printf("1 %d\n", h + 2);
		for (int i = h + 2; i <= d; i++) printf("%d %d\n", i, i + 1);
		for (int i = d + 2; i <= n; i++) printf("%d %d\n", h, i);
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

很显然，只用考虑特判然后是其余按常规做法就行。

- 特判一：当 $n=2$ 时，只有 $h=1$ 且 $d=1$ 可以。
- 特判二：当 $2 \times h < d$ 时，因为无解，所以输出 $-1$。

其他正常情况：

向一边连长度为 $h$ 的链，另一边连长度为 $d-h$ 的链就可以完结此题。

代码：
```c
	if(2*h<d){
		cout<<-1;return 0;
	}
	if(d==1&&n>=3&&h==1){
      cout<<"-1";return 0;
    }
	for(int i=1;i<h;i++)cout<<i<<" "<<i+1<<endl;
	if(d>h){
		printf("1 %d\n",h+2);
		for(int i=h+2;i<=d;i++)cout<<i<<" "<<i+1<<endl;
	}
	for(int i=d+2;i<=n;i++)cout<<h<<" "<<i<<endl; 
```

---

## 作者：zsyyyy (赞：0)

# CF639B题解 构造

## 题意

构造一棵 $n$ 个点，深度 $h$ ，最长链为 $d$ 的树。
 
## 思路

无法构造的情况有以下几种：

1. 最长链长度比深度的两倍还长（因为最长链长度显然最长为深度的两倍）

2. 点的个数比最长链长度小

3. 最长链长度比深度更小

4. 特判：最长链长度为$1$且点的个数不为$2$

用 $l$ 记录满足最长链为 $d$ 时最少的列数（注意此时需要让点数最少，所以除根节点外每个点只能有一个儿子）。

因为求 $l$ 时是向下取整，所以最后最长链长度可能比要求更小，在最后补在$1$的后面即可。

此时最长链和层数都已达到要求，只需把点数凑够。找一个非叶子节点把剩余的点都连在它后面，如果没有非叶子节点就把剩余的点都连在$1$后面。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=100005;
int n,d,h,l,cnt=1,tmp,book[MAX]/*记录每个点是否为叶子结点*/,flag;
signed main()
{
	scanf("%lld%lld%lld",&n,&d,&h);
	if(d>(h*2)||n<=d||d<h||(d==1&&n!=2)) //判断无法构造的情况
	{
		puts("-1");
		return 0;
	}
	l=d/h; //列数
	d-=l*h;
	for(int i=1;i<=l;i++)
	{
		for(int j=1;j<=h;j++)
		{
			if(j==1)
			{
				printf("%lld %lld\n",j,++cnt);
				book[j]=1;
			}
			else
			{
				printf("%lld %lld\n",cnt-1,++cnt);
				book[cnt-1]=1;
			}
		}
	}
	tmp=1;
	while(d) //没有达到最长链的长度
	{
		printf("%lld %lld\n",tmp,++cnt);
		d--;
		tmp=cnt;
	}
	for(int i=1;i<=n;i++)
	{
		if(book[i]&&i!=1)
		{
			flag=i; //找一个非叶子节点
			break;
		}
	}
	if(flag) //找到了非叶子节点
	{
		while(cnt<n)  printf("%lld %lld\n",flag,++cnt);
	}
	else  //没有非叶子节点
	{
		while(cnt<n)  printf("1 %lld\n",++cnt);
	}
	return 0;
}
```

---

## 作者：RainFestival (赞：0)

这道题居然没有题解！！！

我来发布一篇吧

题目大意只有一句话：构造一棵n个点，深度h，最长链为d的树

这道题时间内存都不紧，没关系

怎么造呢

题目说输出任意的树就可以啦

我们肯定要写代码简单的啦^_^

从1号结点开始

先造一条路径

再在另外一边造一条路径

两条链合起来总长为最大链长

剩余的结点都连在结点2上

为什么不连在结点1上？

那是因为如果h==l,那么会链长+1

但在h==1时，却要连在结点1上，不然h会加1

集中特殊条件需要-1

1、深度×2<链长 或者 深度>链长

2、节点数小于等于链长、深度

3、链长、深度都为1，结点数>=3（结点只有2时才能满足条件）

下面是代码（c++）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,h,l;
    cin>>n>>l>>h;
    if (h*2<l||n<=h||n<=l||(h==1&&l==1&&n>=3)||h>l)
    {
        cout<<-1<<endl;
        return 0;
    }
    int p=1;
    for (int i=1;i<=min(h,l);i++)
    {
        p++;
        cout<<p-1<<" "<<p<<endl;
    }
    if (p==n) return 0;
    if (p<l+1)
    {
        p++;
        cout<<1<<" "<<p<<endl;
    }
    while (p<l+1)
        {
        	p++;
            cout<<p-1<<" "<<p<<endl;
        }
    for (;p<n;p++)
        if (h==1) cout<<1<<" "<<p+1<<endl;
        else cout<<2<<" "<<p+1<<endl;
    
    return 0;
} 
```

时间5447ms,内存8KB,代码0.63KB

谢谢巨佬、大佬、神犇们的观赏！！！

---

