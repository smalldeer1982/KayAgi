# Books Queries

## 题目描述

## 题意描述

### 您需要维护一个数据结构，支持以下三种操作：

* $L$ $id$：在现在序列的左边插一个编号为$id$的物品
* $R$ $id$：在现在序列的右边插一个编号为$id$的物品
* $?$ $id$：查询该点左面有几个元素，右面有几个元素，并取min输出

## 样例 #1

### 输入

```
8
L 1
R 2
R 3
? 2
L 4
? 1
L 5
? 1
```

### 输出

```
1
1
2
```

## 样例 #2

### 输入

```
10
L 100
R 100000
R 123
L 101
? 123
L 10
R 115
? 100
R 110
? 115
```

### 输出

```
0
2
1
```

# 题解

## 作者：Binary_Search_Tree (赞：7)

[题目传送门](https://www.luogu.org/problemnew/show/CF1066C)

【题意】：维护一个区间，支持三种操作：

1.**往左边加一个元素，编号为x**

2.**往右边加一个元素，编号为x**

3.**查询编号为x的元素左边元素个数和右边元素个数的最小值**

### 弱化一下题目，假设只有一端，应该怎么做？

用一个数组记录区间，每次修改就加进去一个元素（同时用桶记录它所在位置s[i]）,查询就输出当前数组长度-s[i]

### 那如果是两端呢？

如果还是用刚才的方法，那么数组左端不断-1会下溢出的

所以用一种~~很蠢的~~办法，把数组下标整体加上一个很大的数（如500000）即可

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int M=1000005;
const int MAXN=500000;
int q,L,R;//L为左端点，R为右端点
int a[M],s[M];//a[]为题目中的数组，s[x]表示编号为x的元素在a数组中的下标
int read(){//快读(数字)
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans;
}
char readc(){//快读(字符)
	char c=getchar();
	while (c!='L'&&c!='R'&&c!='?') c=getchar();
	return c;
}
int min(int u,int v){return u<v?u:v;}
int main(){
	q=read();
	L=MAXN+1,R=MAXN;//开始时L=R+1,数组为空
    while (q--){
		char c=readc();int now=read();
		if (c=='L') a[--L]=now,s[now]=L;
		if (c=='R') a[++R]=now,s[now]=R;
		if (c=='?') printf("%d\n",min(s[now]-L,R-s[now]));//输出最小值
	}
	return 0;
}

```

~~都看完了，不点个赞吗~~

---

## 作者：一个简单名字 (赞：3)

# CF1066C


## Solution

首先考虑双端队列，但是 $O(n)$ 的复杂度会超时，干脆接用数组模拟。
 
过程如下：

- 定义两个变量 $L$ 和 $R$，分别表示左右端点，$L$ 和 $R$ 初始化都为最大值。
- 如果左侧插入左端点向左移一位,右侧插入右端点向右移一位。
- 定义一个数组 $site$  用来储存每个 $id$ 的下标。
- 重点，第一次输入的 $site_{id}$ 为最大值,给左边预留出充足的空间。 

## code

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int m,site[2*maxn],L=maxn,R=maxn;
int main()
{
	std::ios::sync_with_stdio(0);
   cin.tie(0);cout.tie(0);//优化输入输出 
	cin>>m;
	for(int i=0; i<m; i++)
	{

		char s;
		int id;
		cin>>s>>id;
		if(!i)// 第一个点的位置是maxn 
		{
			site[id]=maxn;continue;
		}
		if(s=='L')
			site[id]=--L;
		else 
			f(s=='R')
				site[id]=++R;
		else
			cout<<min(R-site[id],site[id]-L)<<endl;//取前后最小值
	}
	return 0;
}

```

完结撒花✿✿ヽ(°▽°)ノ✿

work by Simon



---

## 作者：SunsetSamsara (赞：2)

### 前言：

刚看到这题的我:

好难呀！题面这么复杂！还是 提高+/省选- 的！不会要写 Splay 吧...

思索一会后的我：

这是逗我的吗？这不是双端队列模板吗?

然后，白蚁开始入侵机房，都猖狂地爬进同机房的 @EDqwq 的键盘里了。。。

**正文**：

这可以当成双端队列的基础应用。

我们记两个下标 $l,r$ ,作为队列的左右两端。

当在左边插入时就把 $l$ 减去 $1$,在队列里把下标 $l$ 的赋值为 $id$ 。

当在右边插入时就把 $r$ 加上 $1$,在队列里把下标 $r$ 的赋值为 $id$ 。

至于负下标嘛，我是直接暴力加上 $2\times {10^5}$ 。

下面放代码:

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int arr[500001];
int l,r;
int rev[200001];
int main(){
	l=200001,r=200000;
	int m;
	scanf("%d",&m);
	char ch[2];
	int id;
	for(int i=1;i<=m;++i){
		scanf("%s%d",ch,&id);
		switch(ch[0]){
			case 'L':{
				arr[--l]=id;
				rev[id]=l;
				break;
			}
			case 'R':{
				arr[++r]=id;
				rev[id]=r;
				break;
			}
			case '?':{
				printf("%d\n",min(rev[id]-l,r-rev[id]));
				break;
			}
		}
	}
}
```

---

## 作者：ncwzdlsd (赞：1)

题目要求我们维护一种数据结构，支持以下三种操作：

* `L id`：在现在序列的左边插一个编号为 `id` 的物品
* `R id`：在现在序列的右边插一个编号为 `id` 的物品
* `? id`：查询该点左面有几个元素，右面有几个元素，并取 $\min$ 输出

看到这道题，很容易想到可以用 STL 中的双端队列来解决问题，不过这个东西占用空间极大，于是乎我们明智地采用数组来模拟双端队列的操作。

用数组模拟 STL 容器的应用有很多，比如数组模拟栈、数组模拟队列等，感兴趣的可以自己尝试。

对于此题要求的 $3$ 种操作，代码实现如下：

```cpp
for(int i=1;i<=T;i++)
{
	char ch;int x;
	cin>>ch>>x;
	if (ch=='L') a[x]=--l;
	if (ch=='R') a[x]=++r;
	if (ch=='?') printf("%d\n",min(a[x]-l,r-a[x]));
}
```

---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1066C)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-cf1066c)

本题是简单的**双端队列**练手题。

## 思路

题意大致如下：

+ 执行双端队列 `push_front()` 操作。
+ 执行双端队列 `push_back()` 操作。
+ 查询 $\min\{mp_x - L, R  - mp_x\}$，其中 $mp_x$ 表示 $x$ 元素的对应下标。

由于 STL 配备的双端队列性能较差，使用数组模拟队列。

每次压元素时，记录 $mp_x$。输出直接依照上面的式子即可。

需要注意 `push_front()` 可能使得队列下标越界，解决方法是将 $L$ 与 $R$ 赋予较大值。

实际不需要实现队列，只需记录 $mp_x$。

## 代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
const int N = 2e5;
int mp[N << 1 + 5], l = N+1, r = N; //原本是 l=1 与 r=0，补后变为 l=N+1 与 r=N。 
int main()
{
	fastio();
	int Q;
	cin >> Q;
	while (Q--)
	{
		char op; int x;
		cin >> op >> x;
		if (op == 'L') mp[x] = --l;
		else if (op == 'R') mp[x] = ++r;
		else if (op == '?') cout << min(mp[x] - l, r - mp[x]) << '\n';
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：EDqwq (赞：1)

### 思路

由于值域非常小，所以对于每一个编号映射一下就好了。

然后呢，对于插入，搞两个变量 $l,r$ ，如果左边插入，$l$ 减一，如果右边插入，$r$ 加一。

由于可能会负数导致 RE ，所以我们需要把 $l,r$ 的初始值搞得非常非常大。

然后就愉快的通过啦~

***

### 代码：


```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;
int a[3000010];
int l,r;
int q[3000010];

signed main(){
	l = 1000001,r = 1000002;
	cin>>n;
	for(int i = 1;i <= n;i ++){
		char op;
		int x;
		scanf(" %c ",&op);
		x = read();
		if(op == 'L'){
			a[l] = x;
			q[x] = l;
			l --;
		}
		else if(op == 'R'){
			a[r] = x;
			q[x] = r;
			r ++;
		}
		else {
			printf("%lld\n",min(r - q[x] - 1,q[x] - l - 1));
		}
	}
}
```

---

## 作者：谦谦君子 (赞：1)

# 思路：

##### 开一个容器进行模拟即可，注意容器设置初始大小不然容易re。设置两个指针l,r。把容器当作桶，每一个桶都有一个编号表示位置，左边进入那么就是编号为l，右边一样。然后l--或者r++,l=r=0的初始值，第一个元素为0，然后同时l--,r++
## **代码见下**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    deque<int> vec(300000);
    int l=0,r=0;
    for (int i=0;i<n;i++)
    {
        string s;
        int id;
        cin>>s>>id;
        if (!i)
        {
            vec[id]=l;
            l--,r++;
        }
        else
        {
            if (s=="L")
            {
                vec[id]=l;
                l--;
            }
            if (s=="R")
            {
                vec[id]=r;
                r++;
            }
            if (s=="?")
            {
            	cout<<min(abs(vec[id]-l),abs(vec[id]-r))-1<<endl; 
            }
        }
    }
    return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## 题目大意

需要维护一个数据结构，支持以下三种操作：

- $L$ $id$：在现在序列的左边插一个编号为 $id$ 的物品；
- $R$ $id$：在现在序列的右边插一个编号为 $id$ 的物品；
- $?$ $id$：查询该点左面有几个元素，右面有几个元素，并取 min 输出；

### 具体思路

废话：一开始我想到了双端队列，天真的我准备切掉这一道题，但没想到 $O(N)$ 竟然过不了，我就“愉快的” TLE 了；

慢慢的，我发现可以用数组模拟双端队列这回事。

思路：定义左端点 $L$ 和右端点 $R$, 当想要在数组里存放物品时，只需要移动左右端点即可。

### 实现

当它想要在队列右边存储数值时，只需要移动右指针，再把数值放入指针所指的地址里，并保存指针即可，左边也是同样的道理。当需要询问最小值时，把当前数值的下标分别去减左右端点再取最小值即可。

不废话，上代码：

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
int L = 500001;
int R = 500000;
int a[N], s[N];
int main(){
  int t;
  cin >> t;
  while(t--){//t组数据
    char v;
    int nam;
    cin >> v >> nam;
    if(v == 'L'){//如果是左端点，L--，数组存放物品nam；
      a[--L] = nam;
      s[nam] = L;
    }
    if(v == 'R'){//如果是左端点，R++，数组存放物品nam；
      a[++R] = nam;
      s[nam] = R;
    }
    if(v == '?'){//询问位置；
      cout << min(s[nam]-L, R-s[nam]) << endl;//取最小值输出；
    }
  }
  return 0;
}

```
有任何疑问，可以私信本蒟蒻。

直接切掉！

---

## 作者：happybob (赞：0)

传送门：[CF1066C Books Queries](https://www.luogu.com.cn/problem/CF1066C)

这个题目是蓝的？

首先这个题目暴力模拟肯定不行，我们考虑一个数组 $a_i$ 代表值为 $i$ 的元素的位置在哪里，然后有两个指针 $l$，$r$ 表示当前左端点和右端点的值。

考虑每一个操作：

1. $L\,\, id$：在现在序列的左边插一个编号为 $id$ 的物品。

这个操作我们将 $a_{id}$ 设为 $l$，然后 $l \longleftarrow l - 1$。

2. $R\,\, id$：在现在序列的右边插一个编号为 $id$ 的物品。

这个操作我们将 $a_{id}$ 设为 $r$，然后 $r \longleftarrow r+ 1$。

3. $?\,\, id$：查询该点左面有几个元素，右面有几个元素，并取 $min$ 输出。

输出 `min(abs(l - a[x]), abs(r - a[x])) - 1` 即可。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1e6 + 5;
int place[N];

int main()
{
	int l = 1e4, r = 1e4 + 1;
	int n;
	cin >> n;
	while (n--)
	{
		char c;
		int x;
		cin >> c >> x;
		if (c == 'L')
		{
			place[x] = l;
			l--;
		}
		else if (c == 'R')
		{
			place[x] = r;
			r++;
		}
		else
		{
			cout << min(abs(l - place[x]), abs(r - place[x])) - 1 << "\n";
		}
	}
	return 0;
}
```


---

## 作者：爱滑稽的蒟蒻 (赞：0)

~~说实话我无法理解为什么这题是蓝的~~

大水题~~~

具体意思就是维护一个队列，支持双端插入或查询某个数字左边和右边数字个数的最小值

那么很容易想到的就是开一个数组，用l和r代表数组的左端点和右端点，用d数组表示某个数字在队列里的位置，方便处理。

没了~

看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(c<'0'||c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(f) x=-x;
	return x;
}//快读 
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}//快写 
int l=2e5,r=2e5+1;
int a[maxn],d[maxn];//a是队列,d是标记数组 
int main()
{
	int n=read();
	while(n--)
	{
		char c=getchar();
		while(c!='L'&&c!='R'&&c!='?')
			c=getchar();
		if(c=='L') a[l]=read(),l--,d[a[l+1]]=l+1;//左端插入 
		else if(c=='R') a[r]=read(),r++,d[a[r-1]]=r-1;//右端插入 
		else
		{
			int x=read();
			write(min(r-1-d[x],d[x]-(l+1)));//取min表示最优解 
			puts("");
		}
	}
}
```


---

## 作者：ztz11 (赞：0)

~~差点暴力上treap~~

水题一道

因为只有100000个数，所以我们可以维护一个大小为200000的数组以及$l$，$r$两个指针

第一个数放在100000这个位置，每次往左放就l--，反之r++

把数填进去，同时写一个映射，将$id$映射为位置

当前位置$-l$为左面的数的数量，$r-$当前位置为右面的数的数量

然后输出即可
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int l,r,now,ys[200005];
int q;
int main()
{
	scanf("%d\n",&q);
	for(rii=1;i<=q;i++)
	{
		char cz;
		int id;
		scanf("%c%d\n",&cz,&id);
		if(i==1)
		{
			ys[id]=100000;
			l=100000;
			r=100000;
			continue;
		}
		if(cz=='L')
		{
			l--;
			ys[id]=l;
		}
		if(cz=='R')
		{
			r++;
			ys[id]=r;
		}
		if(cz=='?')
		{
			printf("%d\n",min(ys[id]-l,r-ys[id]));
		}
	}
}
```

---

