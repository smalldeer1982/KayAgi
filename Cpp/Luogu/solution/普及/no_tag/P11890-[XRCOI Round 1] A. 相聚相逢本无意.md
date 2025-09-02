# [XRCOI Round 1] A. 相聚相逢本无意

## 题目背景

> 花开花落终有时，相聚相逢本无意。

## 题目描述

初见时，她给了小 S 一个可以为空的序列 $A$，长度为 $n$。

她定义了序列的**前缀 MEX 序列** $B$，满足 $B$ 的第 $i$ 项为 $\text{MEX}\{A_1,A_2,\dots,A_i\}$，对于一个由有限个非负整数组成的数列 $X$，我们定义 $\text{MEX}$ 为数列中**不包含的最小非负整数**。比如 $\text{MEX}\{1,2,3\}=0,\text{MEX}\{0,1,2,4\}=3$。

作为初见时的考验，小 S 需要构造一个**单调不降**的 $A$ 数组，使得其前缀 $\text{MEX}$ 数组 $B$ 满足一些约束。或者判定没有任何一种符合要求的 $A$ 存在。

具体的，$B$ 数组需要满足的限制形如 $k$ 个二元组 $(x,y)$，表示数 $x$ 在 $B$ 中**恰好**出现了 $y$ 次。

不需要最小化构造的 $A$ 数组的大小或者使构造满足其它没有给定的额外条件。

小 S 不会这个问题，所以他请你来帮忙了。

## 说明/提示

#### 样例解释

第一个样例中，构造出来的 $B=(1,2,2,2,3,4)$， 符合以上 $k$ 个二元组的要求。

更详细的，有：

$B_1=\text{MEX}\{A_1\}=\text{MEX}\{0\}=1$；

$B_2=\text{MEX}\{A_1,A_2\}=\text{MEX}\{0,1\}=2$；

$B_3=\text{MEX}\{A_1,A_2,A_3\}=\text{MEX}\{0,1\}=2$；

$B_4=\text{MEX}\{A_1,A_2,A_3,A_4\}=\text{MEX}\{0,1\}=2$；

$B_5=\text{MEX}\{A_1,A_2,A_3,A_4,A_5\}=\text{MEX}\{0,1,2\}=3$；

$B_6=\text{MEX}\{A_1,A_2,A_3,A_4,A_5,A_6\}=\text{MEX}\{0,1,2,3\}=4$。

第二个样例中，可以证明没有任何一个 $A$ 满足要求。

#### 数据规模与约定

**本题采用捆绑测试和子任务依赖并开启 Special Judge。**

你可以输出任意一组满足条件的情况，如果不存在合法情况输出 $-1$。

其中子任务 $0$ 为样例，记 $0$ 分。

| 子任务编号 | 分值 |     特殊性质      | 子任务依赖 |
| :--------: | :--: | :---------------: | :--------: |
|    $1$     | $30$ | $x\not=0,y\not=0$ |     无     |
|    $2$     | $30$ |     $x\not=0$     |     $1$      |
|    $3$     | $30$ |     $y\not=0$     |     $1$      |
|    $4$     | $10$ |    无特殊性质     |  $1,2,3$   |


对于 $100 \%$ 的数据，保证 $0\le k,x,y\le 100$，且给出的二元组中 $x$ 两两不同。

**不保证 $x$ 单调递增。**

## 样例 #1

### 输入

```
4
1 1
3 1
2 3
4 1```

### 输出

```
6
0 1 1 1 2 3 ```

## 样例 #2

### 输入

```
4
1 1
3 0
2 3
4 1```

### 输出

```
-1```

# 题解

## 作者：FeiYu32 (赞：29)

# 思路解析

这题有点过于抽象了，要考虑一堆特殊情况，将近四个小时才调出来，建议至少评黄。

有些特殊情况有点过于极端了，真的就是很难想到，下面我就逐个分析一下。

首先先看特殊性质，因为 $x\not=0,y\not=0$，所以可以直接构造，按顺序枚举从 $0$ 到最大的 $x$ 的每个数一遍，如果有 $y$ 的话就输出 $y$ 遍，否则就是 $1$ 遍，这样第一个子任务就可以过掉了。

然后我们再看第二个子任务，这里的特殊性质是 $x\not=0$ ，模拟一遍样例我们可以发现，如果一个 $x$ 的 $y$ 值为 $0$ 的话，就无法构造出符合要求的序列。但是为什么会 WA 几个点呢，因为如果这个 $x$ 的值大于其他 $y$ 值不等于 $0$ 的 $x$ 的最大值的话，那么这个 $x$ 就不需要考虑构造，直接忽略这个约束就行了。

然后我们再看第三个子任务，这里的特殊性质的 $y\not=0$ ，也就是说， $x$ 可以为 $0$。因为要求构造的序列都为非负数，那么如果 $x$ 为 $0$ 的话，序列开头只能是 $1$，而构造的序列想要满足其他约束，那么 $1$ 后就只能用 $0$，这就与题目要求的单调不降冲突了，所以如果有 $x$ 的值为 $0$，那么一定无解。

测试一下发现，依然有几个点 WA 了，为什么呢？因为如果一个特殊情况只有 $x$ 为 $0$ 没有其他约束的话，也可以构造出一个符合要求的序列，所以要单独考虑这种情况而写一个特殊的构造。

把一二三号子任务结合起来看第四个子任务，仍然会有 WA 的点。这里没有了特殊性质的限制。仔细思考后我们发现，把二三号子任务结合在一起看，如果有一个 $x$ 的值为 $0$ 且 $y$ 值不为 $0$，和一个 $x$ 值不为 $0$ 但 $y$ 值为 $0$ 的情况依然是有解的，因为后一个可以忽略不看，只满足前一个条件就行了。

再考虑一个新的特殊情况，如果有一个 $x$ 的值为 $0$ 且 $y$ 值不为 $0$，和一个 $x$ 值不为 $0$ 但 $y$ 值不为 $0$ 的情况，那么肯定是无解的，原因和子任务二的特殊情况相同。

找明白所有的特殊情况后，我们最终才能得出正确的思路。然后我们就可以开始写代码了。在这里，我使用一个桶数组记录每个数字应该输出多少次，而这些值初始都为一，经过输入限制后再进行修改，最后计算总输出次数然后分别输出即可，如果特判遇到上述所示的所有特殊情况则按要求进行构造或输出无解。这样，我们就完成了整道题目。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100009],ma=0,ans=0;
int main()
{
    cin>>n;
    for(int i=0;i<=1009;i++)
    {
        a[i]=1;
    }
    for(int i=1;i<=n;i++)
    {
        long long b,c;
        cin>>b>>c;
        a[b-1]=c;
        if(c!=0)ma=max(ma,b);
    }
    if(ma!=0&&a[-1]!=0)//这里的-1是为了记录x值为0的情况，如果出问题了可以把所有a数组下标右移一位再试
    {
        cout<<-1;
        return 0;
    }
    if(ma==0&&a[-1]!=0)
    {
        cout<<a[-1]<<endl;
        for(int i=1;i<=a[-1];i++)
        {
            cout<<1<<" ";
        }
        return 0;
    }
    for(int i=0;i<ma;i++)
    {
        if(a[i]==0)
        {
            cout<<-1;
            return 0;
        }
        ans+=a[i];
    }
    cout<<ans<<endl;
    for(int i=0;i<ma;i++)
    {
        for(int j=1;j<=a[i];j++)
        {
            cout<<i<<" ";
        }
    }
}

```

完结撒花！

---

## 作者：Pyrf_uqcat (赞：8)

赛时搞了好久，做法是将每个子任务逐个击破。

### 子任务一

子任务说明 $x\ne 0$ 且 $y\ne 0$。

无需考虑太多，当有 $y$ 个 $x$ 时，只需要在序列中放 $y$ 个 $x-1$ 就可以了，在前面把 $0$ 到 $x-2$ 都需要**至少**放 $1$ 个以保证 $\operatorname{MEX}$ 为 $x$。

可以拿下子任务一得到三十分。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+5;

int n,ans[N]={-1},k;

struct Node
{
	int x,y;
}a[N];

bool flag[N];

map<int,int> mp;

bool cmp(Node x,Node y)
{
	return x.x<y.x;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=ans[k]+1;j<a[i].x-1;j++)
		{
			ans[++k]=j;
		}
		while(a[i].y--) ans[++k]=a[i].x-1;
		if(k>2e5) cout<<-1<<endl,exit(0);
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

### 子任务二

现在 $y$ 可能会等于 $0$ 了。

当 $x$ 一个都没有时，说明不会出现 $x-1$。既然不会出现 $x-1$，则当有 $x$ 大于出现 $0$ 次的数时，这个序列无法构造出来。只需用一个变量进行标志是否出现过 $0$，即可实现优化。

通过子任务二拿到六十分。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+5;

int n,ans[N]={-1},k,flagg;

struct Node
{
	int x,y;
}a[N];

bool flag[N];

map<int,int> mp;

bool cmp(Node x,Node y)
{
	return x.x<y.x;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(flagg&&a[i].y) cout<<-1<<endl,exit(0);
		if(a[i].y==0)
		{
			flagg=1;
			continue;
		}
		for(int j=ans[k]+1;j<a[i].x-1;j++)
		{
			ans[++k]=j;
		}
		while(a[i].y--) ans[++k]=a[i].x-1;
		if(k>2e5) cout<<-1<<endl,exit(0);
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

### 子任务三

当要出现 $x=0$ 时，则说明第一个数不能是零。而这是一个不递减队列，说明后面永远不会出现 $0$，那么后面的所有 $\operatorname{MEX}$ 都等于 $0$。只有当后面所有的数都出现零次才行，所以再来一个变量进行标记是否出现过 $x=0$。

拿下子任务三得到九十分。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+5;

int n,ans[N]={-1},k,flagg,flaggg;

struct Node
{
	int x,y;
}a[N];

bool flag[N];

map<int,int> mp;

bool cmp(Node x,Node y)
{
	return x.x<y.x;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(flagg&&a[i].y) cout<<-1<<endl,exit(0);
		if(flaggg&&a[i].y) cout<<-1<<endl,exit(0);
		if(a[i].y==0)
		{
			flagg=1;
			continue;
		}
		if(a[i].x==0)
		{
			flaggg=1;
			continue;
		}
		for(int j=ans[k]+1;j<a[i].x-1;j++)
		{
			ans[++k]=j;
		}
		while(a[i].y--) ans[++k]=a[i].x-1;
		if(k>2e5) cout<<-1<<endl,exit(0);
	}
	if(flaggg)
	{
		cout<<a[1].y<<endl;
		for(int i=1;i<=a[i].y;i++)
		{
			cout<<1<<' ';
		}
		cout<<endl;
		return 0;
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

### 子任务四

经过前三个子任务但还是有几个点没过，这是因为漏了一个特殊的样例。当 $x=0$ 且 $y=0$ 时，这就和子任务一样了，可以理解为没有这一次输入，判断一下即可。

#### 赛时通过代码


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2e5+5;

int n,ans[N]={-1},k,flagg,flaggg;

struct Node
{
	int x,y;
}a[N];

bool flag[N];

map<int,int> mp;

bool cmp(Node x,Node y)
{
	return x.x<y.x;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[i].x==0&&a[i].y==0) continue;
		if(flagg&&a[i].y) cout<<-1<<endl,exit(0);
		if(flaggg&&a[i].y) cout<<-1<<endl,exit(0);
		if(a[i].y==0)
		{
			flagg=1;
			continue;
		}
		if(a[i].x==0)
		{
			flaggg=1;
			continue;
		}
		for(int j=ans[k]+1;j<a[i].x-1;j++)
		{
			ans[++k]=j;
		}
		while(a[i].y--) ans[++k]=a[i].x-1;
		if(k>2e5) cout<<-1<<endl,exit(0);
	}
	if(flaggg)
	{
		cout<<a[1].y<<endl;
		for(int i=1;i<=a[i].y;i++)
		{
			cout<<1<<' ';
		}
		cout<<endl;
		return 0;
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

题外：

这辈子写过最长的题解，四千多字符，同时也是写过的最复杂的方法。其实应该是可以直接推得结果的，但是赛时搞了好久每个子任务都错了一两个，只能使用这么不聪明的方法了。

![](https://cdn.luogu.com.cn/upload/image_hosting/oohpw8bl.png)

---

## 作者：gcx114514 (赞：7)

首先我们先特判掉两种情况，一种是 $\text{MEX}$ 限制不为 $0$ 的只有 $0$ 的，我们直接输出限制个极大值即可。另一种是 $\text{MEX}$ 限制不为零的除了 $0$ 还要别的数则一定不合法，因为要满足序列单调不降。

判断完这两种情况，我们考虑计算其他情况。由于要求 $a$ 单调不降，所以将输入序列按 $x$ 升序排列是显然的，当然，我们需要过滤掉末尾连续的 $y$ 为 $0$ 的限制，因为我们完全可以不去遍历。然后这样遍历限制，同时维护一个 $\text{MEX}$ 值，每次判断当前扫到的要求是不是小于 $0$ 即可。

（与出题人讨论了若干种细节，给出题人弄红温了。）

## Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;


inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

struct po{
	int x,y;
	po(int x=0,int y=0):
		x(x),y(y){;}
	bool operator <(const po a)const{
		return x<a.x;
	}
}a[Max];

vector<int>ans;

bool Med;
signed main(){
	int n=read();
	int z=0;
	for(int i=1;i<=n;++i){
		int x,y;
		x=read();
		y=read();
		if(y!=0)++z;
		a[i]=po(x,y);
	}
	sort(a+1,a+1+n);
	int j=0;
	if(a[1].x==0&&a[1].y!=0&&z==1){
		cout << a[1].y << '\n';
		for(int i=1;i<=a[1].y;++i){
			cout << "100000 ";
		}
		return 0;
	}
	if(a[1].x==0&&a[1].y>0&&z>1){
		cout << "-1\n";
		return 0;
	}
	for(int i=1;i<=n;++i){
		int z=0;
		for(int j=i;j<=n;++j){
			if(a[j].y){
				z=1;
				break;
			}
		}
		if(!z)break;
		if(j!=a[i].x){
			while(j<a[i].x){
				ans.push_back(j);
				++j;
			}
			--a[i].y;
		}
		if(a[i].y<0){
			cout << "-1\n";
			return 0;
		}
		while(a[i].y){
			ans.push_back(j-1);
			--a[i].y;
		}
	}
	cout << ans.size() << "\n";
	for(int i:ans){
		cout << i << ' ';
	}
	cout << "\n";
	
	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：3)

出题人题解。

首先要构造单调不降的 $A$ 数组，那么 $B$ 数组就应该满足一些性质：

- 如果 $B$ 数组中的最大值是 $x$，那么从 $1$ 到 $x$ 均至少在 $B$ 中出现过一次。

- 如果 $B$ 数组中出现 $0$，那么 $B$ 数组中只能出现 $0$。

然后注意题目要求的二元组是必须有还是必须没有，如果没有出现就代表都可以。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int x, y;
    friend bool operator<(Node x, Node y)
    {
        return x.x < y.x;
    }
};
vector<Node> vec;
int tmp = 0;
signed main()
{
    int k;
    cin >> k;
    int usd=0;
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        usd+=x*y;
        vec.push_back((Node){x, y});
    }
    sort(vec.begin(), vec.end());
    int now = 0;
    vector<int> ans;
    int ban = 0;
    for (auto x : vec)
    {
        if (x.x == 0 && x.y != 0)
        {
            if(usd)
            cout << -1 << endl;
            else
            {
                cout<<x.y<<endl;
                for(int i=1;i<=x.y;i++)
                {
                    cout<<1145141<<' ';
                }
                cout<<endl;
            }
            return 0;
        }
        if (x.x == 0)
            continue;
        if (x.y == 0)
        {
            ban = 1;
            continue;
        }
        if (ban)
        {
            cout << -1 << endl;
            return 0;
        }
        while(now<x.x-1)ans.push_back(now),now++;
        for(int i=0;i<x.y;i++)ans.push_back(x.x-1);
        now++;
    }
    cout<<ans.size()<<endl;
    for(auto x:ans)
    {
        cout<<x<<' ';
    }
    cout<<endl;
}
```

---

## 作者：粥2414 (赞：3)

比较水但是比较恶心的一道模拟题，需要很多的分类讨论和特判。
# 思路
## 性质
比较容易发现的性质是由于 $A$ 序列**单调不降**，所以 $B$ 序列也是单调不降的。（~~显然~~）

还有两个非常重要的性质：

1. $B$ 序列中**要么只有 $0$，要么不含 $0$**。
2. 当 $B$ 序列中不含有 $0$ 时，$B$ 序列去重后一定是一段从 $1$ 开始的**连续的正整数序列**。
## 证明
简单~~但不太严谨~~的证明：

性质 $1$：  
假设 $B$ 序列中含有 $0$，且同时含有 $x$，其中 $x\in{N^{*}}$，那么由 MEX 序列的定义，可得 $A$ 序列中一定含有从 $0$ 到 $x-1$ 中的所有自然数。且由于 $A$ 序列单调不降，所以 $0$ 一定为 $A$ 序列的第一项。那么 $B$ 序列的第一项就为 $1$，又因为 $B$ 序列单调不降，所以 $B$ 序列中不可能含有 $0$，与假设矛盾。证毕。

性质 $2$：  
假设 $B$ 序列中不含有 $x$，但含有 $x+y$，其中 $x,y\in{N^{*}}$。那么由 MEX 序列的定义，可得 $A$ 序列中一定含有从 $0$ 到 $x+y-1$ 中的所有自然数。所以 $A$ 序列中一定含有 $x-1$，那么该项对应的 $B$ 序列中的位置上一定为 $x$，与假设矛盾。证毕。

这时候就有巨佬要发问了，为什么 $B$ 序列不含 $0$ 时从 $1$ 开始呢？这个在在性质 $1$ 中已经证明过了，~~一看就没专心听讲，出去罚站~~。
## 做法
这题做法非常简单，我们只需要将要求按照 $x$ 的大小从小到大排序，然后用 vector 大力模拟加数即可。

时间复杂度 $O(n)$，$n$ 为构造出的序列 $A$ 的长度。  
为了使构建出的 $A$ 序列最短，最省时间，可以令 $A$ 序列也为连续的自然数序列。（贪心思想）

注意要特判非法情况。

非法情况有以下几种：

1. 要求数字 $0$ 的数量不为 $0$，且要求至少一个非 $0$ 数字的数量不为 $0$。（与性质 $1$ 矛盾）
2. 前后要求同一个数字的数量不同。（显然）
3. 要求非最大值且非 $0$ 的数的数量为 $0$。（与性质 $2$ 矛盾）

然后就可以愉快地 AC 啦！
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int sta_[100], stalen;
//char buf[1<<23],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline ll read() {
	int x = 0, f = 1;
	char ch;
	while ((ch = getchar()) < 48 || ch > 57) if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
inline void write(ll x, bool bo) {
	if (x < 0) putchar('-'), x = -x;
	do if (x || stalen == 0)sta_[++stalen] = x % 10, x /= 10;
	while (x || (putchar(sta_[stalen--] + '0'), stalen));
	putchar(bo ? '\n' : ' ');
}
ll INF = 10009;
vector<ll>v;
ll n;
struct NUM {
	ll x, y;
} a[1009];
ll top = -1;
ll sum;
ll maxx = -1;
ll MAX;
ll old;//要求某个数字数量为0的限制的数量
bool flag1, flag2;
inline bool cmp(NUM a, NUM b) {
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
int main() {
	n = read();
	for (register int i = 1; i <= n; i++) {
		a[i].x = read(), a[i].y = read();
		if (a[i].x == 0 && a[i].y != 0)flag1 = 1;
		if (a[i].x != 0 && a[i].y != 0)flag2 = 1;
		if (a[i].y == 0 && a[i].x != 0)old++;
		sum += a[i].y;
		MAX = max(a[i].x, MAX);
	}
	if (flag1 && flag2) {//情况1
		write(-1, 1);
		return 0;
	}
	sort(a + 1, a + n + 1, cmp);
	if (flag1 && !flag2) {//特判要求 B 序列中含有 0 的情况
		for (int i = 2; i <= n; i++) {
			if (a[i].x != 0)break;
			if (a[i].y != a[i - 1].y) {//情况2
				write(-1, 1);
				return 0;
			}
		}
		write(a[1].y, 1);
		for (int i = 1; i <= a[1].y; i++)write(INF, 0);
		return 0;
	}
	top = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].x == 0)continue;//特判
		if (a[i].y == 0 && (n - i + 1 != old)) {//情况3
			write(-1, 1);
			return 0;
		}
		if (a[i].y == 0)break;
		if (a[i].x == a[i - 1].x && a[i].y != a[i - 1].y && i - 1 != 0) {//情况2
			write(-1, 1);
			return 0;
		}
		if (a[i].x == a[i - 1].x) {
			continue;
		}
		while (maxx < a[i].x - 1) {//vector大力模拟
			v.push_back(++maxx);
			top++;
//			cout<<"dhw "<<maxx-1<<' ';
		}
		a[i].y--;
		for (int j = 1; j <= a[i].y; j++) {
			v.push_back(maxx);
			top++;
//			cout<<"lh "<<maxx<<' ';
		}
		a[i].y++;
	}
//	cout<<endl;
	write(top, 1);
	for (auto x : v) {
		write(x, 0);
	}
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：3)

题目传送门：[P11890 [XRCOI Round 1] A. 相聚相逢本无意](https://www.luogu.com.cn/problem/P11890)

一道~~特判~~构造题。

### 做题过程

简单讲下思路：开个桶存下所有约束条件，记 $s_x$ 为 $x$ 在 $B$ 数组中的限制。

1. 如果 $y$ 全是 $0$ 就直接给出空序列。

2. 如果限制里有 $s_0 \neq 0$，则无解。

3. 第二条是片面的，如果只有限制 $x=0$ 的那就输出 $s_0$ 个其它数。

4. 从 $0$ 遍历到 $\max\limits_{i=1}^{k}y -1$，如果当前限制 $s_i=0$ 则报告无解。

5. 否则在 $a$ 数组里添加 $s_{i+1}$ 个 $i$（如果没有关于 $i+1$ 的限制那就加一个）。

### 代码实现

```cpp
#include<iostream>
using namespace std;
int k,s[102],n,a[200005],mxd;
bool p,b;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>k;
    for(int i=0;i<=100;i++)s[i]=1;//初始化
    while(k--){
        int x;
        cin>>x;
        if(!x)p=1;
        cin>>s[x];
        if(s[x])b=1,mxd=max(mxd,x);
    }
    if(!b){//1
        cout<<0;
        return 0;
    }
    if(p&&s[0]){//2
        if(!mxd){//3
            cout<<s[0]<<'\n';
            while(s[0]--)cout<<1<<' ';
        }
        else cout<<-1;
        return 0;
    }
    for(int i=0;i<mxd;i++){
        if(i&&!s[i]){//4
            cout<<-1;
            return 0;
        }
        for(int j=0;j<s[i+1];j++)a[++n]=i;//5
    }
    cout<<n<<'\n';
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/208154844)。

---

## 作者：canwen (赞：2)

黄到绿，赛时第一眼简单题，接下来不对劲了，调了 $1.5$ h。

## 题目大意
你需要构造数列长度 $0\le n\le 2\times 10^5$ 的数列 $A$ 使得：

- 其**前缀 MEX 序列** $B$ 能够满足 $k$ 个二元组 $(x,y)$。

- 你构造的序列 $A$ 的元素，需满足 $0\le A_i\le 10^9$ 且 $\forall i\in[1,n-1],A_i\le A_{i+1}$。

前缀 MEX 序列和二元组 $(x,y)$ 的具体定义见提面，这里不赘述。
## Sol.
注意我们构造的数列 $A$ 应该是**单调不减**的，所以我们先对所有的 $(x,y)$ 按照 $x$ 升序排序。

从比较简单的子任务一出发，容易想出对于每一个 $1 \le i \le k, x_i > 0$ 构造 $y_i$ 个 $x_i-1$ 数即可满足，但是有时候数之间是不连续的，此时就可以在两个不连续的数字中间补上一些数使得数列 $A$ 满足要求。

其次，注意到样例三，要求构造 $0$ 个 $3$，这就说明在单调递增的数列 $A$ 中不能出现 $2$，而后面还要求构造 $1$ 个 $4$，这显然无解。

如何判断呢？为了免去写一些繁杂的判断，我们可以牺牲掉一部分线性的时间，即正常加数到数列 $A$ 中，最后去做一次扫描判断合法就可以。

接着考虑最为烦人的，即存在 $x_i = 0$ 的情况。

第一种，如果 $x_i = 0, y_{i} = 0$，第一个元素必然是 $0$，$B_{1}$ 也一定是 $1$，此时判断合不合法（注意 $n = 0$ 即啥也不构造的情况，详情见代码注释），如果合法那么就先给 $1$ 减少 $1$ 个出现次数。

第二种，$x_i = 0, y_{i} > 0$，由于 $A$ 应是单调不减的，那么 $0$ 在 $B$ 出现的个数大于 $0$ 的时候，其他数字在 $B$ 出现次数也都应是 $0$ 的时候才成立（想想为啥），所以判断合法即可。若合法，则输出 $y_{i}$ 个任意自然数。

最后回到对 $A$ 的长度和元素范围限制，由于 $k,x,y \le 100$，最多只会构造 $10^4$ 个元素左右，所以长度符合要求，其次我们构造的数也都在范围内，故是可行的。

复杂度 $O(k\log k+k+n)$，$n$ 是构造出来的数列 $A$ 的长度。
## Code
美味代码，欢迎 hack。

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#define const constexpr
using namespace std;
#define int long long
#define _rep(i,a,b) for(int i=a;i<=b;++i)
//#define getchar getchar_unlocked
//#define putchar putchar_unlocked
#define mk make_pair
#define pb emplace_back
#define pint pair<int,int>
#define i128 __int128
#define pc putchar('\n')
#define fst first
#define snd second
#define nowtime (double)clock()/CLOCKS_PER_SEC
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
int in() {
	char a = getchar();
	int k = 0, kk = 1;
	while(!isdigit(a)) {
		if(a == '-') kk=-1;
		a=getchar();
	}
	while(isdigit(a)) {
		k = k*10 + a - '0', a = getchar();
	}
	return k*kk;
}
void out(int a) {
	if(a < 0) putchar('-'),a=-a;
	if(a > 9) out(a/10);
	putchar(a%10+'0');
}
struct node{int x,y;}e[105];
bool cmp(node a,node b){return a.x < b.x;}
map <int,int> ti;
int k,now;
vector <int> ans;
void print_ans(){
	out(ans.size()), pc;
	for(auto i:ans) out(i), putchar(' ');
}
signed main() {
	k = in();
	_rep(i,1,k) e[i].x = in(), e[i].y = in();
	sort(e+1,e+1+k,cmp);
	int lmin = 1;
	if(e[1].x == 0 && e[1].y == 0) {
		ans.pb(0);// 要想让 0 出现 0 个，一定存在第一个元素是 1
		if(e[2].x == 1 && e[2].y == 0){
			// 当要求 1 也恰好出现 1 个，此时有两种结果
			// 有任意一个数字要求需要出现 > 1 次，则无解
			// 否则我们可以啥也不构造，即 0 个元素，输出 0 
			int flag = 0;
			_rep(i,1,k) if(e[i].y){out(-1);return 0;}
			cout << 0;return 0;
		}else if(e[2].x == 1 && e[2].y) e[2].y--,lmin = 2; // 要求 1 出现 > 1 个，此时第一个元素 0 已经贡献了 1 
	} else if(e[1].x == 0 && e[1].y) {
		// 由于是单调不减的，那么 0 在 B 出现的个数 > 0 的时候，其他数字出现次数都是 0 的时候才有可能 
		_rep(i,2,k) if(e[i].y != 0){cout << -1;return 0;}
		// 否则随便构造 0 的个数个正整数即可 
		out(e[1].y), pc;
		_rep(i,1,e[1].y) out(1), putchar(' ');
		return 0;
	}
	_rep(i,lmin,k){
		while(now < e[i].x-1) ans.pb(now++);
		_rep(j,1,e[i].y) ans.pb(e[i].x-1);
		now++;
	}
	int noww = 0;
	for(int i=0; i<ans.size(); ++i){
		if(ans[i] == noww) noww++;
		ti[noww]++;
	}
	if(lmin!=1) e[2].y++; // 之前减去的记得加回来 
	_rep(i,1,k)
		if(ti[e[i].x]!=e[i].y){cout << -1;return 0;}
	print_ans();
	return 0;
}
```

---

## 作者：Bright12077 (赞：2)

本文共 3910 字符，请放心食用（含本行）。

# 思路
拿到题目，发现是一道简单的构造题，因此代码不会很长，但需要注意的细节会比较多。

通过观察题面以及样例，不难发现以下的结论：若有一组数对 $(x,y)\ (x,y>0)$，则 $x-1$ 必定有 $y$ 个，$0\sim x-2$ 的区间中的数也必定有至少一个。

上面的结论也不难证明。我们可以假设约束条件仅有 $(x,y)$ 这一个，那么我们构造出来的序列 $A$ 一定会是这样的（其他方法无非就是将其它不影响结果的数字多增加几个）：

$$\begin{matrix}\begin{aligned}A=\{0,1,2,\cdots,&\underbrace{x-1,\cdots,x-1}\}\\&\quad \quad \quad y个\end{aligned}\end{matrix}$$

此时的 $B$ 序列的第 $1$ 到第 $x-2$ 项将分别是 $1\sim x-1$，最后 $y$ 个则会是 $x$，满足题目约束。

同样的，当有多个 $x$ 和 $y$ 不为 $0$ 的约束数对 $(x,y)$，出现的话，也只需要按照上面的方法依次构造（可参考样例 1）便能找到满足条件的解。

---

上述 $x,y$ 均不为 $0$ 的情况我们已经讨论过了，接下来我们需要讨论下面三种情况：
1. $x\not=0,y=0$
2. $x=0,y\not=0$
3. $x=0,y=0$

## 特殊情况 1
对于特殊情况 1（如样例 2），我们可以模仿上面的内容，构建一个仅有 $(x,0)$ 一组约束。显然的，因为 $x\not=0$，所以构造出来的序列 $A$ 的长度为 $0$，因此这是一种方案。

当有多个形如 $(x,0)\ (x\not=0)$ 的约束时，也有和上面相同的解。这里不再细说，原理同上。

接下来就该考虑特殊 1 和一般情况混合的情况了。从最简单的 $k=2$ 开始考虑，则对于一般情况的 $x_1$ 和特殊情况的 $x_2$ 会有下面两种关系：

1. $x_1<x_2$
2. $x_1\ge x_2$

还是来依次讨论：

### 特殊情况 1-1
当我们先按照一般情况的构造法构造出序列 $A$ 后，不难发现对于此时的序列 $B$ 内一定不会有 $x_2$，因为 $B$ 中的最大值为 $x_1$。

同样，我们也可以把它推广到更广泛的情况，即对于 $k$ 个约束数对，所有 $y=0$ 的数对对应的 $x$ 均大于 $y\not=0$ 的数对所对的 $x$ 时，仅需按照一般情况构造序列即可，甚至可以忽略那几个 $y=0$ 的数对（毕竟也没有影响）。

### 特殊情况 1-2
同样的，按照一般情况构建好 $A$，发现所对的 $B$ 中一定包含 $x_2$，因为 $B$ 会包含 $1\sim x_1$ 中的所有数，而 $x_2\le x_1$，自然也会出现。

因此这种情况直接无解。

---
因此我们可以对这一部分做一个总结，即：

**当所有特殊情况 1 的数对所对应的 $x$ 均大于一般情况的数对所对应的 $x$ 时，可忽略所有特殊情况 1 的数对并构造出一种解；否则无解**。

## 特殊情况 2
这种情况不难发现，除非输入数对仅对 $0$ 作出约束，仅需输出 $y$ 个大于 $0$ 的数，其余情况均无解。

因为当出现对 $0$ 的约束时，不难考虑像一般情况一样，构建 $y$ 个 $x-1$ 出来，但是很显然 $0-1$ 是非法的，因此只能通过抹去 $0$ 达成效果。

又因为 $A$ 序列是单调不降的，因此当 $A$ 的第一位选择用 $1$ 来达成有 $0$ 的条件时，$A$ 中后续的数字也一定不可以为 $0$，即整个 $A$ 中不再有 $0$。

但是 $\text{MEX}$ 要求的是序列中第一个没出现的自然数，而 $0$ 在序列 $A$ 中一直没有出现，因此 $\text{MEX}$ 一定会一直返回 $0$，也仅有 $0$，便无法达成其他效果。

## 特殊情况 3
要求 $0$ 不出现也很好办，只要按照正常情况构造序列，便可以满足。

# 代码
## 代码细节
讨论完思路，就要着手写代码了。

纵观全局，发现要讨论的代码细节还怪多的：
1. 输入
2. 特殊情况 1
3. 特殊情况 2+3
4. 序列构造

### 1. 输入
此处的 $x,y$ 数据规模较小，因此可以考虑开桶。

而这个数组 $b_x=y$ 的含义就等同于 $(x,y)$。

但是对于 $y=0$ 的条件也是需要被约束的，而它和没有约束的初值 $0$ 又是两个不同的东西，因此还需要使用标记数组 $a$ 标记该数是否被约束，以方便后续处理。

由于我们后续处理需要一个具体的区间，因此需要记录最大值。同样对于特殊情况 2 的有解判断也得记录总共约束的 $y$ 的出现个数。

代码：
```cpp
int k;
cin>>k;
int maxx=0,sum=0;
while(k--){
    int x,y;
    cin>>x>>y;
    a[x]=true;//标记
    b[x]+=y;//约束出现次数
    if(y!=0)maxx=max(maxx,x);//x 在最后的话是可以忽略的，详见特殊情况 1-1
    sum+=y;
}
```
### 2. 特殊情况 1
把那句总结搬过来看：**当所有特殊情况 1 的数对所对应的 $x$ 均大于一般情况的数对所对应的 $x$ 时，可忽略所有特殊情况 1 的数对并构造出一种解；否则无解**。

由于有解的情况我们在输入时已经处理过了，因此只需要判定无解即可，即判断是否在 $1\sim \text{maxx}$ 的范围内出现了形如 $(x,0)$ 的数对。

```cpp
for(int i=1;i<=maxx;i++)
    if(a[i]&&!b[i])cout<<-1,exit(0);//一定无解
```
### 3. 特殊情况 2+3
由于特殊 2 和 3 十分相像，就放在一起处理吧。

首先考虑有解情况，即当 $b_0=\text{sum}$ 时构建 $\text{sum}$ 个 $1$ 即可；若 $b_0=0$，无需特殊处理；否则无解。

转化为 C++ 便是：
```cpp
if(a[0]&&b[0]!=0&&b[0]!=sum)cout<<-1,exit(0);//无解
if(a[0]&&b[0]==sum){//特殊的有解情况
    cout<<sum<<'\n';
    while(sum--)cout<<1<<' ';exit(0);
}
```
### 4. 序列构造
由于最终序列与 $b$ 的相似度很高，便直接在 $b$ 上操作。

此时我们把 $b$ 数组的含义进行一个更改：$b_x=y$ 表示最终序列中第 $x-1$ 项出现 $y$ 次。因为在原来的定义中它表示的 $(x,y)$ 影响的就是 $x-1$。

由于特殊情况 1 的无解我们已经判定过了，因此在 $1\sim\text{maxx}$ 中，$b_i=0$ 的数所对的 $a_i$ 也为 ```false```。此时只需要找到 $b_i=0$ 的所有数并替换为 $1$ 即可。

同时也别忘了统计最终序列的长度。
```cpp
int n=0;
for(int i=1;i<=maxx;i++)
    b[i]=max(b[i],1),n+=b[i];
cout<<n<<'\n';
for(int i=1;i<=maxx;i++)
    while(b[i]--)cout<<i-1<<' ';
```

## 最终代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[114514];
int b[114514];
int main(){
    int k;
    cin>>k;
    int maxx=0,sum=0;
    while(k--){
        int x,y;
        cin>>x>>y;
        a[x]=true;
        b[x]+=y;
        if(y!=0)maxx=max(maxx,x);
        sum+=y;
    }

    if(a[0]&&b[0]!=0&&b[0]!=sum)cout<<-1,exit(0);
    if(a[0]&&b[0]==sum){
        cout<<sum<<'\n';
        while(sum--)cout<<1<<' ';exit(0);
    }
    for(int i=1;i<=maxx;i++)
        if(a[i]&&!b[i])cout<<-1,exit(0);

    int n=0;
    for(int i=1;i<=maxx;i++)
        b[i]=max(b[i],1),n+=b[i];
    cout<<n<<'\n';
    for(int i=1;i<=maxx;i++)
        while(b[i]--)cout<<i-1<<' ';
    return 0;
}
```

---

## 作者：zy567 (赞：1)

# 大意：
首先，注意题目中并没有说没有限制的数在 $B$ 中不能出现。

先考虑限制中有 $0$ 的情况。容易发现如果还限制了其它数的话就无解了。直接特判掉就好，这是平凡的。

考虑还有什么情况无解。显然对于限制中的一个 $x$，它要出现的话，如果限制中存在一个 $x<x’$，且 $ x ’$ 不能存在的话，此时无解。
# 代码：
```cpp
#include<bits/stdc++.h>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#define int long long
using namespace std;
const int N=2e5+5;
int n,ans[N]={-1},k;
struct Node{
	int x,y;
}a[N];
bool flag[N];
map<int,int>mp;
bool cmp(Node x,Node y){
	return x.x<y.x;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=ans[k]+1;j<a[i].x-1;j++){
			ans[++k]=j;
		}
		while(a[i].y--) ans[++k]=a[i].x-1;
		if(k>2e5) cout<<-1<<endl,exit(0);
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

本题是一道简单的构造题，但细节有点多，建议评黄。
## 题意理解
本题的核心在于理解 $\text{MEX}$ 运算的性质。注意题意要求生成序列**单调不降**！换句话说，我们可以研究 $\text{MEX}$ 序列在单调不降情况下的性质。由其定义，我们易知 $\text{MEX}\{a_1,a_2,a_3,\dots,a_n\}=k$ 的充要条件是对于任意 $m<k$（$m$ 为自然数），都存在 $a_i$（$i\le n$），使得 $a_i=m$，且不存在 $a_i=k$。再结合序列单调不降，我们惊异地发现，$\text{MEX}$ 序列也单调不降！
## 思路分析
进一步分析，我们发现，可以将约束条件中 $x$ 中有无零分情况讨论：  
1.需满足 $\text{MEX}$ 序列中零的数量不为零。此时我们发现原序列一定不含零（由于单调性反证易得），$\text{MEX}$ 序列由且只由 $0$ 构成。   
2. 对于序列中零的数量不必大于零，根据单调性逐数满足即可。（详见代码）

注意：当输入 $y=0$ 且 $x$ 不等于 $0$ 须注意：等同于 $\text{MEX}$ 序列被中断，要求仍有大于 $x$ 的数存在于 $\text{MEX}$ 序列就判断不可，否则忽略。

## Code
~~（判断 $y=0$ 部分有点丑）~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,q[200010],cnt[109];
struct Node{
 int x,y;
 bool operator<(const Node &a){
  return x<a.x;
 }
}a[120];
int main()
{cin>>k;
 if(k==0)
 {cout<<"0";
  return 0;
 }
 for(int i=1;i<=k;i++)
 cin>>a[i].x>>a[i].y;
 sort(a+1,a+1+k);
 for(int i=k;i>=1;i--)
 cnt[i]=cnt[i+1]+(a[i].y!=0);
 int j=0;
 if(a[1].x==0&&a[1].y!=0)
 {if(cnt[1]!=1)
  cout<<"-1\n";
  else
  {cout<<a[1].y<<'\n';
   for(int i=1;i<=a[1].y;i++)
   cout<<"1 ";
  }
  return 0;
 }
 a[0].x=0;
 
 for(int i=1;i<=k;i++)
 {if(a[i].x==0) continue;
  if(a[i].y==0&&cnt[i]!=0)
  {cout<<"-1\n";
   return 0;
  }
  if(a[i].y==0) 
  break;
  if(a[i].x!=a[i-1].x+1)
  {for(int ii=a[i-1].x;ii<a[i].x-1;ii++)
   q[++j]=ii;
  }
  for(int ii=1;ii<=a[i].y;ii++)
   q[++j]=a[i].x-1;
 }
 cout<<j<<'\n';
 for(int i=1;i<=j;i++)
 cout<<q[i]<<' ';
}
```

---

## 作者：01bit (赞：1)

~~好神金的一道题目，在场上被创到了。~~

按照 $x$ 将要求升序排列，再处理每个要求。

设 $A$ 中最大元素为 $k$，特别的，当 $A$ 为空时，规定 $k=-1$。

考虑以下四种情况：

1. $x=y=0$：对答案无影响，直接跳过。
2. $x=0,y\ne0$：向 $A$ 中添加 $y$ 个任意正整数（代码中选择添加 $1$），若之后的要求中有 $x\ne0,y\ne0$ 的，输出 $-1$；否则继续。（显然如果要满足其中 $x\ne0,y\ne0$ 的条件需要向 $A$ 中添加 $0$，但我们已经向 $A$ 中添加了正整数，而 $A$ 必须为单调不降的，所以无法满足条件。）
3. $x\ne0,y=0$：检查之后的要求中是否有 $y\ne0$ 的，如果有，则输出 $-1$；否则继续。（如果有这样的要求，$B$ 就必然会有至少一个 $x$，不符合我们处理的这个要求。）
4. $x\ne0,y\ne0$：检查是否能满足上面两种需要特判的要求，向 $A$ 中添加 $k+1$ 至 $x-2$ 的整数各一个，再添加 $y$ 个 $x-1$。

如果你的思路很清晰了，下面的代码也不难写出了。~~（其实很难）~~


```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
int read() {
    int v = 0, f = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v * f;
}
const int N = 2e5 + 5, M = 100 + 5;
int n = 0, m;
struct Node {
    int x, y;
} a[M];
bool cmp(const Node &x, const Node &y) { return x.x < y.x; }
int s[N], mx = -1;
bool zero = false, flag = false;
int main() {
    m = read();
    for (int i = 1; i <= m; i++)
        a[i].x = read(), a[i].y = read();
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        if (a[i].x == 0) {
            if (a[i].y == 0)
                continue;
            for (int j = 1; j <= a[i].y; j++)
                s[++n] = 1;
            mx = 1;
            zero = true;
            continue;
        }
        if (zero) {
            if (a[i].y == 0)
                continue;
            puts("-1");
            return 0;
        }
        if (a[i].y == 0) {
            flag = true;
            continue;
        }
        if (flag) {
            puts("-1");
            return 0;
        }
        for (int j = mx + 1; j < a[i].x - 1; j++)
            s[++n] = j;
        for (int j = 1; j <= a[i].y; j++)
            s[++n] = a[i].x - 1;
        mx = a[i].x - 1;
    }
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d ", s[i]);
    return 0;
}
```

---

## 作者：ZinfI_Sh (赞：1)

> 笑点解析：主观难度橙题，首 A 用时 12 分钟，我调了 2 个小时。

首先，很容易发现，想要出现一个数字 $x(x\not=0)$，我们只要把 $0\sim x-1$ 的数字构造出来就好了，现在我们考虑哪些情况会是无解的。

在下文中，我们用 $e_{i,x/y}$ 表示第 $i$ 个条件的 $x/y$。

1. $\exist e_{i},e_{j}(i\not=j)$，使得 $e_{i,y}=0,e_{j,y}\not= 0,e_{j,x}>e_{i,x}$ 时，无解。

这是因为，由于不能存在 $e_{i,x}$，那么就不能构造出 $e_{i,x}-1$，但有因为我们需要一个数字 $e_{j,x}$，且 $e_{j,x}>e_{i,x}$，也就是我们一定要构造出一个 $e_{j,x}-1$，但 $e_{i,x}\in [0,e_{j,x}-1]$，不符合需求，所以无解。

2. $\exist e_{i},e_{j}(i\not=j)$，使得 $e_{i,x}=0,e_{i,y}\not=0,e_{j,y}\not= 0,e_{j,x}>e_{i,x}$ 时，无解。

这是因为，想要构造一个 $0$，只能最先构造一个 $1$，而如果这时候还需要其他数字，那么就必须再构造一个 $0$ 来补足空位，但题目要求 $A$ 数组单调不降，所以无解。

其他的，若约束条件的最小 / 大值之内有没出现过的 $x$，那么就要默认有一个 $e_{*,y}=1$，$*$ 表示新的一项；若约束条件的最小值 $y_{\min}$ 大于 $1$，那么要补足 $0\sim y_{\min}-1$。

# AC 代码

笑点解析：机房同学 $30$ 多行，我 $100$ 多行。
```
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x & -x)
using namespace std;
const int DM[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1};
const int HASHMOD = 9223372036854775783;
const int HASHBASE = 131;
const int HASHITEM = 999997;
struct S
{
    int a, b;
} a[1001];
bool cmp(S a, S b)
{
    return a.a < b.a;
}
queue<int> q;
signed main()
{
    int n, p0 = 0;
    cin >> n;
    bool check = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].a >> a[i].b;
        if (a[i].b == 0 && a[i].a != 0)
        {
            if (!p0)
            {
                p0 = i;
            }
        }
    }
    sort(a + 1, a + n + 1, cmp);
    if (p0)
    {
        for (int i = p0; i <= n; i++)
        {
            if (a[i].b != 0)
            {
                check = 0;
                break;
            }
        }
    }
    if (!check)
    {
        cout << "-1";
        return 0;
    }
    // cout<<"check";
    if (a[1].a == 0 && a[1].b != 0)
    {
        for (int i = 2; i <= n; i++)
        {
            if (a[i].a != 0 && a[i].b != 0)
            {
                cout << -1;
                return 0;
            }
        }
        cout << a[1].b << '\n';
        for (int i = 1; i <= a[1].b; i++)
        {
            cout << "1 ";
        }
        return 0;
    }
    a[0].a = 0;
    int tmp = 0;
    for (int i = 2; i <= n; i++)
    {
        if (a[i].b == 0)
        {
            continue;
        }
        if (a[i].a != a[i - 1].a + 1)
        {
            for (int j = a[i - 1].a + 1; j <= a[i].a - 1; j++)
            {
                a[n + (++tmp)] = {j, 1};
            }
        }
    }
    n += tmp;
    sort(a + 1, a + n + 1, cmp);
    int tp = 1;
    while (a[tp].a == 0 && tp <= n)
    {
        tp++;
    }
    if (a[tp].a != 1 && tp <= n)
    {
        for (int i = 1; i < a[tp].a; i++)
        {
            q.push(i - 1);
            if (q.size() > 200000)
            {
                check = 0;
                break;
            }
        }
    }
    if (!check)
    {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i].b == 0)
        {
            continue;
        }
        for (int j = 1; j <= a[i].b; j++)
        {
            q.push(a[i].a - 1);
            if (q.size() > 200000)
            {
                check = 0;
                break;
            }
        }
    }
    if (!check)
    {
        cout << "-1";
        return 0;
    }
    cout << q.size() << '\n';
    while (q.size())
    {
        cout << q.front() << ' ';
        q.pop();
    }
    return 0;
}
```

---

## 作者：時空 (赞：1)

[In Luogu](https://www.luogu.com.cn/problem/P11890)

前言：比赛时随便看了眼，有点思路就写过了。前后大概 $20$ min，应该有黄。

注意，本题解不涉及部分分的做法。

首先，注意题目中并没有说没有限制的数在 $B$ 中不能出现。笔者因为这个问题浪费了很多时间。

先考虑限制中有 $0$ 的情况。容易发现如果还限制了其它数的话就无解了。直接特判掉就好，这是平凡的。

考虑还有什么情况无解。显然对于限制中的一个 $x$，它要出现的话，如果限制中存在一个 $x' < x$，且 $x'$ 不能存在的话，此时无解。

考虑一个限制二元组 $(x,y)$，这实际上需要使得在 $A$ 已经出现了 $0 \sim x-2$ 时，往 $A$ 中塞入 $y$ 个 $x-1$。这是很好理解的。

那么按照上述过程模拟即可。细节有点多？笔者不是很有感觉。

```cpp
// using ll = long long;

ll n;
pii p[N]; // pair <ll, ll>

ll key[N], V;

signed main()
{
	cin >> n;
	if (n == 0) { cout << "0\n"; return 0; }
	
	for (ll i = 0; i <= 100; ++ i ) key[i] = -1;
	for (ll i = 1; i <= n; ++ i ) 
	{
		cin >> p[i].first >> p[i].second;
		
		key[p[i].first] = p[i].second;
		if (p[i].second) V = max(V, p[i].first);
	}
	
	if (V == 0 && key[0] > 0)
	{
		cout << key[0] << '\n';
		while (key[0] -- ) cout << "1 "; cout << '\n';
		return 0; 
	}
	
	
	bool chk = false;
	for (ll i = 1; i <= V; ++ i )
	{
		if (key[i] == 0) { chk = true; break; }
	}
	if (chk || key[0] > 0) { cout << "-1\n"; return 0; }
	
	ll r0 = 0, lst = -1; vector <ll> oput;
	for (ll i = 1; i <= V; ++ i )
	{
		if (key[i] == -1) continue;
		
		for (ll j = lst + 1; j <= i - 2; ++ j ) oput.pb(j), ++ r0;
		lst = i - 1;
		
		r0 += key[i];
		while (key[i] -- ) oput.pb(i - 1);
	}
	cout << r0 << '\n';
	for (auto x : oput) cout << x << ' '; cout << '\n';
}
```

---

## 作者：ffffffu (赞：1)

# P11890 [XRCOI Round 1] A. 相聚相逢本无意

### 题目背景

话说追女孩应该靠自己吧，但是看在小S是我好哥们份上我就帮帮他（笑。

题目要求我们构造一个**单调不降**的序列 $$ A $$，让它的**前缀 MEX 序列** $$ B $$ 满足 $$ k $$ 个条件，每个条件是个二元组 $$ (x, y) $$，意思是 $$ B $$ 里 $$ x $$ 得恰好出现 $$ y $$ 次。如果实在构造不出来，就输出个 $$-1$$。数据范围上，$$ k \leq 100 $$，$$ x, y $$ 都是 $$ [0, 100] $$ 的非负整数。

**前缀 MEX 序列 $$ B $$**：对于 $$ A = [a_1, a_2, \ldots, a_n] $$，$$ B_i = \text{MEX}\{a_1, a_2, \ldots, a_i\} $$。比如 $$ A = [0, 1] $$，那 $$ B = [1, 2] $$。

### 思路分析

拿到这题，第一反应是得搞清楚 $$ A $$ 咋影响 $$ B $$。因为 $$ A $$ 单调不降（$$ a_i \leq a_{i+1} $$），咱们得从这个限制入手，看看能整出啥花样。

#### 观察一：$$ A $$ 不含 0 的情况

假如 $$ A $$ 从头到尾都不含 0，比如 $$ A = [1, 1, 2] $$：
- $$ B_1 = \text{MEX}\{1\} = 0 $$，
- $$ B_2 = \text{MEX}\{1, 1\} = 0 $$，
- $$ B_3 = \text{MEX}\{1, 1, 2\} = 0 $$，
- 结果 $$ B = [0, 0, 0] $$。

发现没？只要 $$ A $$ 里没 0，$$ B $$ 全是 0，长度跟 $$ A $$ 一样。这时候，如果输入要求 $$ y_0 > 0 $$，而且别的 $$ x > 0 $$ 都得出现 0 次（$$ y_x = 0 $$），那就好办了，直接造个 $$ A = [1, 1, \ldots, 1] $$，长度定成 $$ y_0 $$。但要是 $$ y_x > 0 $$（$$ x > 0 $$），就完蛋了，$$ B $$ 里塞不进正数。

#### 观察二：$$ A $$ 从 0 开始的情况

现在试试 $$ A $$ 以 0 开头，比如 $$ A = [0, 0, 1] $$：
- $$ B_1 = \text{MEX}\{0\} = 1 $$，
- $$ B_2 = \text{MEX}\{0, 0\} = 1 $$，
- $$ B_3 = \text{MEX}\{0, 0, 1\} = 2 $$，
- $$ B = [1, 1, 2] $$。

再试个 $$ A = [0, 1, 1, 2] $$：
- $$ B = [1, 2, 2, 3] $$。

有点规律了吧！如果 $$ A $$ 分成几段，每段是重复的数，依次递增：
- $$ A = [0, 0, 1, 1, 1, 2] $$（0 两遍，1 三遍，2 一遍），
- $$ B = [1, 1, 2, 2, 2, 3] $$，
- $$ B $$ 里 1 出现 2 次，2 出现 3 次，3 出现 1 次。

总结下：$$ A $$ 里放 $$ a $$（从 0 开始），重复 $$ c_a $$ 次，$$ B $$ 里就会有 $$ c_a $$ 个 $$ a + 1 $$。这不就是咱们想要的控制 $$ B $$ 出现次数的办法吗？

#### 分情况处理

根据输入的 $$ (x, y) $$，咱们分成两拨：

1. **$$ y_0 > 0 $$**：
   - $$ B $$ 里得有 $$ y_0 $$ 个 0，别的啥也不能有。
   - $$ A = [1] \times y_0 $$，$$ B = [0, 0, \ldots, 0] $$，完美。
   - 但得检查下：所有 $$ x > 0 $$ 的 $$ y_x $$ 必须是 0（或没给），不然矛盾。

2. **$$ y_0 = 0 $$ 或没给 $$ y_0 $$**：
   - $$ B $$ 里不能有 0（如果 $$ y_0 = 0 $$），所以 $$ A $$ 得从 0 开始。
   - 定义：
     - $$ S = \{ x \geq 1 \mid y_x > 0 \} $$：$$ B $$ 里得出现的数。
     - $$ T = \{ x \geq 1 \mid y_x = 0 \} $$：$$ B $$ 里不能出现的数。
   - $$ A $$ 得用 0 到某个 $$ m $$，让 $$ B $$ 覆盖 $$ S $$（从 1 到 $$ m + 1 $$），但不能碰到 $$ T $$。
   - 条件：$$ \max(S) \leq \min(T) $$（否则 $$ B $$ 会多出 $$ T $$ 里的数）。
   - 构造：$$ A $$ 里 $$ a $$ 重复 $$ c_a = y_{a+1} $$ 次（没给 $$ y_{a+1} $$ 就填 1），$$ m = \max(S) - 1 $$。

#### 啥时候无解？

- $$ y_0 > 0 $$ 且 $$ y_x > 0 $$（$$ x > 0 $$）：0 和正数不能共存。
- $$ \max(S) > \min(T) $$：$$ B $$ 会跑出禁区。

### 实现步骤

1. **读输入**：用 $$ \text{cnt}[x] $$ 存 $$ y_x $$，默认 -1（没给）。
2. **Case 1**：$$ \text{cnt}[0] > 0 $$ 时，检查 $$ x > 0 $$ 是否都 OK，输出 $$ [1] \times \text{cnt}[0] $$。
3. **Case 2**：
   - 找 $$ S $$ 和 $$ T $$，算 $$ \max(S) $$ 和 $$ \min(T) $$。
   - 判断可行性，构造 $$ A $$。
   - $$ S $$ 为空时，$$ A = [] $$ 就行。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;
    vector<int> cnt(101, -1); // -1 是没给
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        cnt[x] = y;
    }

    if (cnt[0] > 0) { // y_0 > 0 
        bool ok = true;
        for (int x = 1; x <= 100; x++) {
            if (cnt[x] > 0) ok = false; // 正数不能出现
        }
        if (ok) {
            cout << cnt[0] << "\n";
            for (int i = 0; i < cnt[0]; i++) {
                cout << 1 << (i == cnt[0] - 1 ? "\n" : " ");
            }
        } else {
            cout << -1 << "\n";
        }
    } else { // $$ y_0 \leq 0 $$ 或没给
        vector<int> S, T;
        for (int x = 1; x <= 100; x++) {
            if (cnt[x] > 0) S.push_back(x);
            if (cnt[x] == 0) T.push_back(x);
        }
        int m = T.empty() ? 101 : *min_element(T.begin(), T.end());
        int max_S = S.empty() ? 0 : *max_element(S.begin(), S.end());

        if (max_S > m) { // 冲突
            cout << -1 << "\n";
        } else if (S.empty()) { // 啥也不用干
            cout << 0 << "\n";
        } else { // 正常构造
            int M = max_S - 1;
            vector<int> A;
            for (int a = 0; a <= M; a++) {
                int c = (cnt[a + 1] > 0) ? cnt[a + 1] : 1;
                while (c--) A.push_back(a);
            }
            cout << A.size() << "\n";
            for (int i = 0; i < A.size(); i++) {
                cout << A[i] << (i == A.size() - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}
```
### 复杂度
时间：$$ O(k + 100) $$，输入处理和遍历常数级别。

空间：$$ O(100) $$，加上输出数组 $$ O(n) $$，但 $$ n $$ 有上限。

---

## 作者：fish_love_cat (赞：1)

T1 放这么多细节就是拿来降低区分度的吧，好题（赞赏）（笑脸）

硬控 90min。

---

首先可以按 $x$ 排序。

因为 $A$ 单调不降，所以 $B$ 显然单调不降且连续。

我们一个一个把 $B$ 堆上去，到了需要的位置就多停一会增加数量就行了。

这样是好做的。

但是特殊性质里给了一大堆关于 $0$ 的东西，所以我们有许多关于 $0$ 的细节分讨（咬牙切齿）

---

细节：

如果 $B$ 序列中有 $0$，那么就不会有除 $0$ 以外的数。这个很重要，因此你需要判一大堆东西。

如果 $[1,B_{max}]$ 间有不应该出现的数，那么无解。

如果没有限制，判出来特殊处理。

如果限制 $(0,0)$，无视。

如果只有 $(0,y)$ 是有效限制，判出来特殊处理。

以上把风铃草折磨疯了。

其他还有，看代码吧。

---

代码与[提交记录](https://www.luogu.com.cn/record/208139837)：

```cpp
#include<bits/stdc++.h>
#define int long long
//***king S**t ** C***f*****.
using namespace std;
struct fish{
    int x,sum;
}a[105];
bool cmp(fish x,fish y){
    return x.x<y.x;
}
vector<int>ans;
bool flag;
signed main(){
    int n;
    cin>>n;
    if(n==0){
        cout<<"0\n";
        return 0;
    }
    for(int i=1;i<=n;i++)
        cin>>a[i].x>>a[i].sum,flag|=(a[i].sum!=0&&a[i].x!=0);
    sort(a+1,a+1+n,cmp);
    
    if(a[1].x==0&&a[1].sum!=0){
        if(flag)cout<<-1;
        else{
            cout<<a[1].sum<<endl;
            for(int i=1;i<=a[1].sum;i++)
                cout<<"1 ";
        }
        return 0;
    }
    
    while(n&&a[n].sum==0)n--;
    int x=0;
    for(int i=1+(a[1].x==0&&a[1].sum==0);i<=n;i++){
        if(a[i].sum==0){
            cout<<-1;
            return 0;
        }
        for(;x<a[i].x-1;x++)ans.push_back(x);
        for(int j=1;j<=a[i].sum;j++)ans.push_back(x);
        x++;
    }
    
    cout<<ans.size()<<endl;
    for(int j=0;j<ans.size();j++)
        cout<<ans[j]<<' ';
    return 0;
}
```

这题橙？这题橙？

---

## 作者：Kayisama (赞：0)

题目难度不高，但是特判较多。

### 初步分析

首先我们考虑 $x\ne0$ 且 $y\ne0$ 的情况。我们假设 A 序列的末尾为 $x-2$ 我们会发现，对于 B 序列中存在 $y$ 个 $x$ 的这个要求，只需要把 $y$ 个 $x-1$ 放在 A 序列的末尾即可，因为对于这几个位置，前缀 $\operatorname{mex}$ 会始终为 $x$。

对于末尾不为 $x-2$ 的情况，我们可以把从 $\text{末尾元素}+1$ 到 $x-2$ 的所有元素都加入，我们考虑这样做的正确性：如果存在一个 $x_0$ 且 $x_0 \in [\text{末尾元素}+1,x-2]$，对于其对应的 $y_0$ 也有 $y_0 > 1$ 的话，那么显然这样会使得 $x_0$ 在 B 序列中出现的次数过少，使得构造失败，那么我们就需要一个方法去解决这个问题。注意到 $x_0 < x$ 那么我们对要求以 $x$ 为第一关键字排序之后从前往后处理，即可使这种影响消失。对于这方面的处理，有代码如下：


```cpp
sort(q.begin(),q.end());
a.push_back(-1);
for (auto& [x,y]:q){
  for (int i=a.back()+1;i<x-1;i++) a.push_back(i);
  while (y--) a.push_back(x-1);
}
```

其中 $q$ 为询问序列，里面以 pair 的形式存储着每个 $x$ 和 $y$，并且自带一个以 pair 内前者为关键字的比较函数，所以直接排序即可，而 $a$ 即为最终的答案序列，这里的复杂度是 $O(k \log k)$ 的。

（把 $-1$ 放入开头是我自己方便编写代码而进行的行为，原因不再赘述，读者在写的时候会自然发现）。

### 进一步思考

我们接下来对 $x=0$ 和 $y=0$ 的种种情况进行讨论（不是最终版本，在最终思考环节还会有改变，~~也就是有反转~~）。

1. $x=0$ 且 $y\ne0$：

   对于这种情况，可以发现除非我们使得 B 序列全部为 $0$，在 A 序列单调不降的情况下是不可能出现合法情况的，所以我们直接输出 $-1$。

2. $x\ne0$ 且 $y=0$：

   这种情况就等价于我们无法选择 $x-1$，也就代表着对于任意一个 $a(a>x-1)$ 都无法出现在 B 序列中，所以我们把要求排序之后，对于**后缀的 $y=0$ 的要求**进行删除后，如果序列中仍存在 $y=0$ 的要求，直接判无解，否则继续处理即可。

3. $x=0$ 且 $y=0$：

    $0$ 个 $0$ 是显然在任何情况下都成立的，直接跳过这个要求即可。
### 最终思考

在这里我们对一些特殊情况进行探讨。

1. 任何一步之后序列为空：

   显然的，如果要求序列为空，我们直接构造一个长度为 $0$ 的序列输出即可。

2. 有且仅有一个要求，并且 $x=0$ 且 $y=n$（$n$ 为任意正整数）：

    直接放 $y$ 个 $1$ 即可满足条件。
4. 存在一个 $x_a=0$ 且 $y_a=n$ （$n$ 为任意正整数），并且对于其余的 $x$ 和 $y$ 都保证 $x\ne0$ 且 $y=0$：

    我们发现删除 $y=0$ 的后缀之后，我们发现与最终思考中的情况 2 重合，我们直接和其用同样的处理方式即可。

5. 答案长度超过 $2 \times 10^5$：

    计算发现，就算是每个数字（除了 $0$）我们都要求要 $100$ 个，我们也只会出现 $100 \times 100=10^4$ 长度的答案，所以这种情况不必考虑。

最后算下来，复杂度为 $O(k \log k + \sum y)$。

### 代码环节

对于所有情况都考虑之后，我们就可以写出代码了，下面是我的代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
namespace MySpace{
    #ifdef ONLINE_JUDGE
    #define getchar getchar_unlocked
    #endif
    inline void read() {}
    template <typename T, typename... R>
    inline void read(T &x,R &... oth){
        x=0;T f=1;
        char c=getchar();
        while(c<'0' || c>'9') {
            if(c=='-') f=-1;
            c=getchar();
        }
        while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c&15),c=getchar();
        x*=f;
        read(oth...);
        return;
    }
}
using namespace MySpace;
int k;
vector<pair<int,int> > q;//用来存储询问
vector<int> a;//用来存储答案
signed main(){
	read(k);//输入k
	for (int i=1;i<=k;i++){
		int x,y;read(x,y);
		if (!(x==0 && y==0))//如果x=0 并且 y=0，这种情况可以直接忽略掉
			q.push_back({x,y});	
	}
	if (q.empty()) return printf("0"),0;//判空，下面每一句如这行的代码都是这个作用
	sort(q.begin(),q.end());//对要求按x排序
	while (!q.empty() && q.back().second==0) q.pop_back();//删除后缀的y=0的要求
	if (q.empty()) return printf("0"),0;
	if (q[0].first==0){//如果存在x=0的
		if (q.size()==1){//如果仅存在一个x=0的，那么直接全放1即可
			printf("%d\n",q[0].second);
			while (q[0].second--) printf("1 ");
			return 0;
		}else return printf("-1"),0;//否则不合法
	}
	for (int i=0;i<q.size();i++) if (q[i].second==0) return printf("-1"),0;//如果存在非后缀y=0的要求，则判定不合法
    	a.push_back(-1);//放入一个-1方便处理
	for (auto& [x,y]:q){//处理每一个要求
		for (int i=a.back()+1;i<x-1;i++) a.push_back(i);
		while (y--) a.push_back(x-1);
	}
	printf("%d\n",a.size()-1);//输出长度（去掉开头的-1）
	for (int i=1;i<a.size();i++) printf("%d ",a[i]);//输出答案（去掉开头的-1）
	return 0;
}




 
```

[AC记录](https://www.luogu.com.cn/record/208486544)。

祝大家写代码永远不挂！

---

## 作者：xuyifei0302 (赞：0)

这道题要判断一堆东西，所以赛时把部分分都拿了一遍。

这里让我们构造前缀 $MEX$，而且还要**单调不降**，这就使问题变得简单了一些。

我们要使得前缀 $MEX$ 中出现 $y$ 个 $x$。由前缀 $MEX$ 得性质可以发现一定是从小到大。

而且有一些数的出现次数为 $0$。所以如果一个数 $m$ 后面没有需要出现的数了，就可以停止构造。如果都可以不出现，就直接输出 $0$。

如果只有一个限制，且这个限制关于 $0$，那么就可以分为两种情况：出现次数为正数和出现次数为零。

对于出现次数为正数的情况，就可以直接输出对应个次数的 $1$ 及以上的数字。

对于出现次数为零的情况，就可以直接输出长度为 $0$ 的数组。

因为要单调不降，所以如果一个数字的出现次数要为 $0$，但是还有更大的数字要出先，则一定无法满足，输出 $-1$。

如果限制条件只有 $0$，且其余出现次数均为 $0$，则和只有一个限制，且这个限制关于 $0$ 的情况相同。

如果有不关于 $0$ 的限制，且出现次数大于 $0$，而且 $0$ 的限制条件所要求的出现次数大于 $0$，因为我们构造的 $a_i \ge 0$，所以一定无法满足，输出 $-1$。

特殊情况讨论完了，下面就是构造正常情况。

对于一个数 $kk$，如果 $kk$ 的出现次数为 $kk1$ 且 $kk1 > 0$，则输出 $kk1$ 个 $kk - 1$。如果 $kk$ 的出现次数为 $0$，则输出 $1$ 个 $kk - 1$。

下面是代码环节：


```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int x, y;
} b[10005];
int n, a[1000005], maxn, cnt, lll;
map<int, bool> mm;
map<int, int> mp;
bool cmp(Node x, Node y) {
	return x.x < y.x;
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		cin >> b[i].x >> b[i].y;
		if (b[i].y) {
			maxn = max(maxn, b[i].x);
		} else {
			lll ++;
		}
		mp[b[i].x] = b[i].y;
		mm[b[i].x] = true;
	}
	if (lll == n) {
		cout << 0;
		return 0;
	}
	if (n == 1 && b[1].x == 0) {
		if (b[1].y == 0) {
			cout << "0";
			return 0;
		}
		for (int i = 1; i <= b[1].y; i ++) {
			a[++cnt] = 1;
		}
		cout << cnt << "\n";
		for (int i = 1; i <= cnt; i ++) {
			cout << a[i] << " ";
		}
		return 0;
	}
	sort(b + 1, b + 1 + n, cmp);
	for (int i = 1; i <= n; i ++) {
		if (!mp[b[i].x] && mm[b[i].x] && b[i].x) {
			if (b[i].x < maxn) {
				cout << "-1";
				return 0;
			}
		}
	}
	if (lll == n - 1 && mp[0]) {
		for (int i = 1; i <= b[1].y; i ++) {
			a[++cnt] = 1;
		}
		cout << cnt << "\n";
		for (int i = 1; i <= cnt; i ++) {
			cout << a[i] << " ";
		}
		return 0;
	}
	if (mp[0]) {
		cout << "-1";
		return 0;
	}
	for (int i = 0; i < maxn; i ++) {
		if (!mp[i + 1] && !mm[i + 1]) {
			a[++cnt] = i;
		} else {
			for (int j = 1; j <= mp[i + 1]; j ++) {
				a[++cnt] = i;
			}
		}
	}
	cout << cnt << "\n";
	for (int i = 1; i <= cnt; i ++) {
		cout << a[i] << " ";
	}
	return 0;
}
```

---

## 作者：_zjzhe (赞：0)

首先对二元组 $(x,y)$ 进行排序，第 $i$ 项记作 $(x_i,y_i)$。如果要数 $x_i$ 在 $B$ 中恰好出现 $y_i$ 次，那么根据 $\text{MEX}$ 的定义，有 $[0, x_i-1]\subseteq A$ ，且 $x_i-1$ 在 $A$ 中出现了 $y_i$ 次。于是枚举每一条限制，用 $j$ 来表示当前 $A$ 中最大的数，先将 $[j+1, x_i-2]$ 中的数加入 $A$ 中，再加入 $y_i$ 个 $x_i-1$ 即可。

接下来考虑特殊情况：
1. 若 $x_1=y_1=0$ , 特判一下，不做处理。 
2. 若 $x_1=0$ 且 $y_1\neq0$ ，我们需要向 $A$ 中加入 $y_i$ 个任意正整数。因为 $0\notin A$ ，则若 $\exists i\in [2,n],\ y_i\neq0$，则不合法。
3. 若 $x_1\neq0$ 且 $y_1\neq0$ ，按上述过程模拟，过程中若遇到 $y_i=0$ 且 $i\neq n$ ，则需判断是否 $\exists i\in [i+1,n],\ y_i\neq0$，若存在则不合法。

还有一些实现上的细节，详见代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,s[N];
pair<int,int>p[N];
vector<int>a;
#undef int 
int main(){
#define int long long
    ios::sync_with_stdio(0);cin.tie(0);
    int i,j,k,l,r,x,y,z;
    cin>>n;
    for(i=1;i<=n;i++)cin>>p[i].first>>p[i].second;
    sort(p+1,p+n+1);
    for(i=n;i>=1;i--)s[i]=s[i+1]+p[i].second;
    if(p[1].first==0&&p[1].second!=0){
        for(i=1;i<=n;i++){
            if(p[i].first!=0&&p[i].second!=0)return cout<<"-1"<<'\n',0;
            for(k=1;k<=p[i].second;k++)a.push_back(1);
        }
    }else{
        for(i=1,j=0;i<=n;i++){
            if(p[i].first!=0&&p[i].second==0) {
                if(s[i]==0) break;
                if(i!=n) return cout<<"-1"<<'\n',0;
            }
            if(p[i].second==0) continue;
            for(;j<p[i].first-1;j++)a.push_back(j);
            for(k=1;k<=p[i].second;k++)a.push_back(j);j++;
        }
    }
    cout<<a.size()<<'\n';
    for(auto f : a)cout<<f<<' ';

    return 0;
}
```

---

