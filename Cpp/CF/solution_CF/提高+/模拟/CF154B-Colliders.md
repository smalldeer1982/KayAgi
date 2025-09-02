# Colliders

## 题目描述

在2312年，宇宙中发现了 $n$ 台巨型对撞机，这些对撞机分别用 $1 \sim n$ 的自然数标识。科学家们不知道启动这些对撞机会发生什么危险事故，所以这些机器，刚开始都是出于关闭的状态。

随着科学家们的研究发现，第 $i$ 台对撞机启动是安全的，当且仅当其他已经启动的对撞机的标识数都跟这台对撞机标识数互质。（例如假设前面启动的对撞机标识数是 $j$，如果 $i$ 能启动，那么 $i,j$ 互质，即 $\gcd(i,j) = 1$）。如果两台对撞机的标识数不为互质数就启动，那么就会发生爆炸事故。

基于前面的研究，科学家们准备做各种启动和关闭对撞机的实验。为了确保科学家们的生命安全，你要设计一个远程遥控的软件。

刚开始，所有的对撞机都是关闭状态。你的程序将会收到许多询问，格式为“启动、关闭第 $i$ 台对撞机”。这个程序应该能处理这些询问（根据收到询问的先后顺序处理）。程序按照如下的格式输出处理结果。

如果询问为 `+ i`（表示启动第 $i$ 台对撞机），程序应该按照下面三种情况之一输出结果。

- `Success`，表示启动第 $i$ 台是安全的。
- `Already on`，表示第 $i$ 台在询问之前就已经启动了。
- `Conflict with j`，表示第 $i$ 台与前面已经启动的第 $j$ 台冲突。如果前面有多台对撞机跟 $i$ 冲突，那么只输出其中任何一台即可。

如果询问为 `- i`（表示关闭第 $i$ 台对撞机），程序应该按照下面两种情况之一输出结果。

- `Success`，表示关闭第 $i$ 台对撞机。

- `Already off`，表示第 $i$ 台对撞机在询问之前就已经关闭了。

## 说明/提示

$1 \le n,m \le 10^5$，$1 \le i \le n$。

## 样例 #1

### 输入

```
10 10
+ 6
+ 10
+ 5
- 10
- 5
- 6
+ 10
+ 3
+ 6
+ 3
```

### 输出

```
Success
Conflict with 6
Success
Already off
Success
Success
Success
Success
Conflict with 10
Already on
```

# 题解

## 作者：Engulf (赞：3)

## 题意

维护一个数字集合，要求集合中的数字**两两互质**，有以下两种操作：

- `+ i`
	- 若 $i$ 与集合中的数两两互质且未加入集合，将 $i$ 加入集合，输出 $\texttt{Success}$。
    - 若 $i$ 已加入集合，输出 $\texttt{Already on}$。
    - 若 $i$ 与集合中的数 $j$ 不互质，输出 $\texttt{Conflict with }j$。若 $j$ 有多个，输出任意一个。
- `- i`
	- 若 $i$ 在集合中，将 $i$ 从集合中删除。
    - 若 $i$ 不在集合中，输出 $\texttt{Already off}$。

## 分析

考虑到集合中的数两两互质，也就是说，这些数的因数都是互不相同的。那么考虑用两个 `std::set` 维护，一个维护数字集合，一个维护因数集合，同时还要开一个数组 $g_i$ 记录因数 $i$ 是哪个数的因数。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace fastIO
{
	template<typename T> inline void read(T &t)
	{
		T x = 0;
		int f = 0;
		char ch = getchar();
		while (!isdigit(ch)) f ^= !(ch ^ 45), ch = getchar();
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		t = f ? -x : x;
	}
	template<typename T, typename ... Args> inline void read(T &x, Args&... args)
	{
		read(x), read(args...);
	}
}
using namespace fastIO;

typedef pair<int, int> PII;
const int N = 1e5 + 10;
int factor[N];
set<int> s;
set<int> f;
vector<int> fac[N];
int g[N];
int n, m;

int main()
{
	read(n, m);
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j * j <= i; j ++ )
			if (i % j == 0)
			{
				if (j > 1) fac[i].push_back(j);
				if (j != i / j) fac[i].push_back(i / j);
			}
	while (m -- )
	{
		char p[2];
		int x;
		scanf("%s", p);
		read(x);
		if (p[0] == '+')
		{
			if (s.empty())
			{
				puts("Success");
				s.insert(x);
				for (auto d: fac[x]) f.insert(d), g[d] = x;
			}
			else if (s.count(x))
			{
				puts("Already on");
				continue;
			}
			else
			{
				bool flag = true;
				for (auto d: fac[x])
				{
					if (f.count(d))
					{
						printf("Conflict with %d\n", g[d]);
						flag = false;
						break;
					}
				}
				if (!flag) continue;
				puts("Success");
				s.insert(x);
				for (auto d: fac[x]) f.insert(d), g[d] = x;
			}
		}
		if (p[0] == '-')
		{
			if (!s.count(x))
			{
				puts("Already off");
				continue;
			}
			puts("Success");
			s.erase(x);
			for (auto d: fac[x]) f.erase(d), g[d] = 0;
		}
	}
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：2)

## CF154B Colliders 题解

### 解题思路

首先看这道题，一眼大模拟好题。

首先我们可以尝试最暴力的枚举大法，在加入时枚举所有已经加入的对撞机，确认每一个对撞机是否与新加入的对撞机冲突。

但是，时间复杂度是 $O(n\sqrt{n}m)$，而数据范围是 $1\le n,m\le 10^5$，肯定超时。

所以，我们要对这个算法进行优化。我们可以用一个桶将之前的对撞机装起来，实现 $O(1)$ 查询。此时，加入和删除对撞机的复杂度均为 $O(\sqrt{n})$，总复杂度为 $O(m\sqrt{n})$，可以通过此题。

#### 最后总结一下我们要执行的步骤：

**添加一个对撞机**：

- 已经有了：输出 $\texttt{“Already on”}$。
- 因数重复：输出 $\texttt{“Conflict with X”}$。
- 可以加入：输出 $\texttt{“Success”}$，并且在一个桶中**标记**这个数的所有因数。

**删除一个对撞机**：

- 还未加入：输出 $\texttt{“Already off”}$。
- 可以删除：输出 $\texttt{“Success”}$，并且在一个桶中**剔除**这个数的所有因数。

虽然这道题比较考验代码能力，但是我认为这道题的难度还是要比蓝题简单一点，估计在绿题水平左右。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct yinzi
{
	bool a;
	int b;
}b[100005];
int n , m , q;
char p;
bool a[100005];
bool yinshu(int t)
{
	if(b[t].a)
	{
		cout << "Conflict with " << b[t].b;
		return 0;
	}
	for(int i = 2 ; i * i <= t ; i++)
	{
		if(t % i == 0 && b[i].a)
		{
			cout << "Conflict with " << b[i].b;
			return 0;
		}
		if(t % i == 0 && b[t / i].a)
		{
			cout << "Conflict with " << b[t / i].b;
			return 0;
		}
	}
	b[t].a = 1;
	b[t].b = t;
	for(int i = 2 ; i * i <= t ; i++)
	{
		if(t % i == 0)
		{
			b[i].a = 1;
			b[i].b = t;
			b[t / i].a = 1;
			b[t / i].b = t;
		}
	}
	return 1;
}
void del(int t)
{
	b[t].a = 0;
	b[t].b = 0;
	for(int i = 2 ; i * i <= t ; i++)
	{
		if(t % i == 0)
		{
			b[i].a = 0;
			b[i].b = 0;
			b[t / i].a = 0;
			b[t / i].b = 0;
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin >> n >> m;
	while(m--)
	{
		cin >> p >> q;
		if(p == '+')
		{
			if(a[q])
			{
				cout << "Already on\n";
			}
			else if(yinshu(q))
			{
				cout << "Success\n";
				a[q] = 1;
			}
			else
			{
				cout << "\n";
			}
		}
		if(p == '-')
		{
			if(!a[q])
			{
				cout << "Already off\n";
			}
			else
			{
				del(q);
				cout << "Success\n";
				a[q] = 0;
			}
		}
	}
	return 0;
}
```
### 感谢阅读！

---

## 作者：hongshixiaobai (赞：1)

# CF154B Colliders 题解
[传送门](https://www.luogu.com.cn/problem/CF154B)
## 思路
如果直接按照题意暴力模拟，明显会 T，所以用**桶**记录一下这个数的因数有没有出现过就好了，每次 $O(\sqrt n)$ 遍历确定现在要开启的对撞机编号有没有因数与已开启的对撞机编号冲突即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,tmp;
struct _
{
	bool flag1;
	int flag2;
}flag1[100005];
bool flag2[100005],flag_; 
char c;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n>>m;
	for(int j = 1;j<=m;j++)
	{
		cin>>c>>tmp;
		if(c == '+')
		{
			if(flag2[tmp])
			{
				cout<<"Already on\n";
			}
			else if(tmp == 1 && !flag2[1])
			{
				cout<<"Success\n";
				flag2[1] = 1;
			}
			else
			{
				if(flag1[tmp].flag1)
				{
					cout<<"Conflict with "<<flag1[tmp].flag2<<'\n';
					continue;
				}
				for(int i = 2;i*i<=tmp;i++)
				{
					if(tmp%i == 0&&flag1[i].flag1)
					{
						cout<<"Conflict with "<<flag1[i].flag2<<'\n';
						flag_ = 1;
						break;
					}
					if(tmp%i == 0&&flag1[tmp/i].flag1)
					{
						cout<<"Conflict with "<<flag1[tmp/i].flag2<<'\n';
						flag_ = 1;
						break;
					}
				}
				if(!flag1[tmp].flag1&&!flag_)
				{
					cout<<"Success\n";
					flag2[tmp] = 1;
					for(int i = 1;i*i<=tmp;i++)
					{
						if(tmp%i == 0)
						{
							flag1[i].flag1 = 1;
							flag1[i].flag2 = tmp;
							flag1[tmp/i].flag1 = 1;
							flag1[tmp/i].flag2 = tmp;
						}
					}
				}
			}
		}
		else
		{
			if(!flag2[tmp])
			{
				cout<<"Already off\n";
			}
			else
			{
				cout<<"Success\n";
				flag1[tmp].flag1 = flag1[tmp].flag2 = 0;
				for(int i = 2;i*i<=tmp;i++)
				{
					if(tmp%i == 0)
					{
						flag1[i].flag1 = flag1[i].flag2 = 0;
						flag1[tmp/i].flag1 = flag1[tmp/i].flag2 = 0;
					}
				}
				flag2[tmp] = 0;
			}
		}
		flag_ = 0;
	}
} 
```

---

## 作者：yzy4090 (赞：1)

本题需要维护一个集合 $S$，并完成以下操作：  
- 给定一个数 $i$，在 $S$ 中寻找任意一个数 $j$ 使得 $\gcd(i,j)\neq1$；若不存在这样的数，则把 $i$ 插入 $S$。
- 在 $S$ 中删除数 $i$，若 $i\notin S$ 就忽略本次操作。   

$1\leq n\leq 10^5,1\leq i\leq n$。

插入 $i$ 时对 $\forall j\in S$ 计算 $O(\log(\max(i,j)))$ 的 $\ gcd(i,j)$ 可能会导致时间复杂度上升，我们可以考虑先对 $\forall 1\leq i\leq n$ 分解质因数，然后暴力模拟。代码如下（包含注释）：  
```
#include<iostream>
#include<vector>
using namespace std;
#define N 100005
int n,now,m,res;
bool vis[N];//vis[i] 标记 i 是否在 S 中 
char c;
vector<int>v[N],collide[N];//v[] 存储每个数的质因子，
						   //collide[i] 存储 i 是 S 中哪些数的质因子 
int judge_gcd(int now);
void init_prime(int n);
void Insert(int now);
void Remove(int now);
int main(){
    scanf("%d%d",&n,&m);
    init_prime(n);
    while(m--){
        cin>>c,scanf("%d",&now);
        if(c=='-'&&!vis[now]){
            puts("Already off");
            continue;
        }
        if(c=='-'&&vis[now]){
            vis[now]=false;
            puts("Success");
            Remove(now);
            continue;
        }
        if(c=='+'&&vis[now]){
            puts("Already on");
            continue;
        }
        if(c=='+'&&!vis[now]){
            res=judge_gcd(now);
            if(res==-1){
            	vis[now]=true;
				puts("Success");
            	Insert(now);
			}
            else printf("Conflict with %d\n",res);
        }
	}
    return 0;
}
void init_prime(int n){
	for(int i=1,k;i<=n;i++){
		k=i;
		for(int j=2;j*j<=i;j++){
			if(k%j==0){
				v[i].push_back(j);
				while(k%j==0)k/=j;
			}
		}	
		if(k>1)v[i].push_back(k);
	}
	return;
}//此处的质因数分解算法可以更优（如线性筛可以做到 O(n) 的复杂度） 
int judge_gcd(int now){
	for(int i=0;i<(int)v[now].size();i++)
		if(!collide[v[now][i]].empty())
			return collide[v[now][i]][0];
    return -1;
}
void Remove(int now){
	for(int i=0;i<(int)v[now].size();i++)
		for(int j=0;j<(int)collide[v[now][i]].size();j++)
			if(collide[v[now][i]][j]==now)
				collide[v[now][i]].erase(collide[v[now][i]].begin()+j);
	return;
}
void Insert(int now){
	for(int i=0;i<(int)v[now].size();i++)
		collide[v[now][i]].push_back(now);
	return;
}
//以上的三个函数均为对 collide[] 的暴力维护 
```

---

## 作者：Erotate (赞：1)

**题目大意：**

有 $n$ 台机器，每台机器的编号为 $1$ 到 $n$。如果要开启一台机器，那这台机器的编号必须和已开启的机器的编号互质。现在有两种操作：

- `+ id` 意思为开启一台机器

	如果已经开启了，输出 `Already on`。
   
   如果不能开启，输出 `Conflict with j`，$j$ 为导致这台机器不能开启的机器的编号
   
   如果能开启，输出 `Success`。
   
- `- id` 意思为关闭一台机器

	如果已经关闭了，输出 `Already off`。
    
   如果成功关闭，输出 `Success`。

---
那么，因为要判断编号是否互质，我们可以预处理 $1$ 到 $n$ 中每个数的因数，把它们加入到一个 vector 容器里：

```cpp
//g[i] 记录第 i 个数的所有因数
for(int i=1;i<=n;++i)
	for(int j=1;j*j<=i;++j)
		if(i%j==0){
			if(j!=1) g[i].push_back(j);
			if(j!=i/j) g[i].push_back(i/j);
		}
```
我们使用 C++ 中 STL 里的 set 容器，来记录已经开启的机器的编号和已开启的机器的编号的因数。

```cpp
set<int>s1 //记录编号
set<int>s2 //记录编号的因数
```

1. 当输入为 `+` 号时，我们分类讨论：

- 没有开启任何机器，直接开启。

```cpp
if(!s1.size()){
	s1.insert(x);//插入编号
	for(int i=0;i<g[x].size();++i){//循环插入因数
		s2.insert(g[x][i]);
		d[g[x][i]]=x;//这里 d 数组记录每个因数对应的数
	}
	printf("Success\n");
	continue;
}
```

- 已经开启了这台机器。

```cpp
if(s1.count(x)){// s1.count 表示在 s1 里查找 x
	printf("Already on\n");
	continue; 
}
```

- 剩下的情况就需要判断当前编号是否与之前的编号互质了。

```cpp
int f=1;
for(int i=0;i<g[x].size();++i)//判断是否互质
	if(s2.count(g[x][i])){
		f=0;
		printf("Conflict with %d\n",d[g[x][i]]);//不互质就输出因数对应的数
		break;
	}
if(f){//如果互质，就把当前数和数的因数加进 set
	s1.insert(x);
	for(int i=0;i<g[x].size();++i){
		s2.insert(g[x][i]);
		d[g[x][i]]=x;
	}
	printf("Success\n");
}
```

2. 当输入为 `-` 号时，如果在 set 里找不到要关闭的机器的编号，就说明已经关闭了；否则就把编号和编号对应的因数删除。

```cpp
if(s1.count(x)){
	s1.erase(x);
	for(int i=0;i<g[x].size();++i){
		s2.erase(g[x][i]);//s1.erase 表示 在 s1中删除 x
		d[g[x][i]]=0;
	}
	printf("Success\n");
}else printf("Already off\n");
```

---
总代码：
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,d[N];
set<int>s1,s2;
vector<int>g[N];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j*j<=i;++j)
			if(i%j==0){
				if(j!=1) g[i].push_back(j);
				if(j!=i/j) g[i].push_back(i/j);
			}
	for(int i=1,x;i<=m;++i){
		char c[2];
		scanf("%s%d",c,&x);
		if(c[0]=='+'){
			if(!s1.size()){
				s1.insert(x);
				for(int i=0;i<g[x].size();++i){
					s2.insert(g[x][i]);
					d[g[x][i]]=x;
				}
				printf("Success\n");
				continue;
			}
			if(s1.count(x)){
				printf("Already on\n");
				continue; 
			}
			int f=1;
			for(int i=0;i<g[x].size();++i)
				if(s2.count(g[x][i])){
					f=0;
					printf("Conflict with %d\n",d[g[x][i]]);
					break;
				}
			if(f){
				s1.insert(x);
				for(int i=0;i<g[x].size();++i){
					s2.insert(g[x][i]);
					d[g[x][i]]=x;
				}
				printf("Success\n");
			}
		}else{
			if(s1.count(x)){
				s1.erase(x);
				for(int i=0;i<g[x].size();++i){
					s2.erase(g[x][i]);
					d[g[x][i]]=0;
				}
				printf("Success\n");
			}else printf("Already off\n");
		}
	}
	return 0;
}
```


---

## 作者：OIerZhang (赞：0)

# [CF154B Colliders](https://www.luogu.com.cn/problem/CF154B)

这道题根本没有 `*1600` 的难度，不过是一个模拟而已。

## 思路

刚刚已经提到了，这道题我们只需要依题意模拟即可，不需要高深的算法。

背景知识：[STL queue](https://baike.baidu.com/item/queue/4511093?fromModule=lemma_sense-layer#viewPageContent)

### $O(n^3)$ 做法

最无脑的一种做法，只有三个简单步骤。

1. 输入。
2. 循环所有已经启动的对撞机的标识数。
3. 循环枚举因数来判断是否互质。

这个做法不需要任何高深算法、数据结构和数学知识，当然大家肯定看出了很多优化空间。

通过数据范围：$n \le 400$。

### $O(n^2 \sqrt n)$ 做法

众所周知，除了完全平方数以外所有数的因数都是成对出现，而完全平方数有一个未成对的因数 $\sqrt x$。

那么在原来做法的基础上，因数的枚举范围只需要枚举从 $2$ 到 $\sqrt n$ 的数了，另一个数便可以求出来。

通过数据范围：$n \le 1500$。

### $O(n^2)$ 做法

既然 $O(n^2 \sqrt n)$ 的做法通不过题目，那么说明一定有优化的空间。

观察开头的三个步骤，我们每输入一次，都要循环所有对撞机，效率十分低下。

而这道题最大的标识数也只有 $10^5$，不妨使用桶去记录所有标识数的因数，这样就可以省去循环所有对撞机的过程。

但是当发生冲突时，要输出与它冲突的对撞机标识号，仍需一个单独的循环枚举，时间复杂度为 $O(n^2)$。

通过数据范围：$n \le 10^4$。

### $O(n \sqrt n)$ 正解

我们发现，$O(n^2)$ 做法的瓶颈在于发生冲突时，循环枚举与它冲突的对撞机标识号。既然可以用桶去记录所有标识数的因数，那为什么不能用桶记录因数对应的对撞机标识号呢？

可是如果直接记录的话，原来的标识号就会被覆盖，无法正确输出标识号，这时背景知识中的 queue 就派上用场了。

我们每记录一个因数，就顺便将这个因数对应的标识号入队，输出时只用输出队头即可。删除时，如果队头不是要删除的，那就把队头放到队尾。由于这个操作一共至多做 $m$ 次，所以不会影响时间复杂度。

虽然常数不小，但仍能以 800ms 的速度通过本题。

## 代码

```cpp
#include <iostream>
#include <queue>
#define ios ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int vis[100005];
bool f[100005];

queue <int> num[100005];

signed main()
{
    ios;
    char op;
    int n, m, x;
    cin >> n >> m;
    while (m--)
    {
        cin >> op >> x;
        if (op == '+')
        {
            bool flag = true;
            int id = -1;
            for (int i = 2; i * i <= x; i++)
            {
                if (x % i == 0)
                {
                    if (vis[i])
                    {
                        flag = false;
                        id = num[i].front();
                        break;
                    }
                }
                if (x % (x / i) == 0)
                {
                    if (vis[x / i])
                    {
                        flag = false;
                        id = num[x / i].front();
                        break;
                    }
                }
            }
            if (vis[x] && !f[x])
                flag = false, id = num[x].front();
            if (f[x])
                flag = true;
            if (flag)
            {
                if (!f[x])
                {
                    cout << "Success\n";
                    f[x] = true;
                    for (int i = 2; i * i <= x; i++)
                    {
                        if (x % i == 0)
                            vis[i]++, num[i].push(x);
                        if (x % (x / i) == 0)
                            vis[x / i]++, num[x / i].push(x);
                    }
                    vis[x]++, num[x].push(x);
                }
                else
                    cout << "Already on\n";
            }
            else
                cout << "Conflict with " << id << endl;
        }
        else if (op == '-')
        {
            if (f[x])
            {
                cout << "Success\n";
                f[x] = false;
                for (int i = 2; i * i <= x; i++)
                {
                    if (x % i == 0)
                    {
                        vis[i]--;
                        int cur = num[i].front();
                        while (cur != x)
                            num[i].pop(), num[i].push(cur), cur = num[i].front();
                        num[i].pop();
                    }
                    if (x % (x / i) == 0)
                    {
                        vis[x / i]--;
                        int cur = num[x / i].front();
                        while (cur != x)
                            num[x / i].pop(), num[x / i].push(cur), cur = num[x / i].front();
                        num[x / i].pop();
                    }
                }
                vis[x]--;
                int cur = num[x].front();
                while (cur != x)
                    num[x].pop(), num[x].push(cur), cur = num[x].front();
                num[x].pop();
            }
            else
                cout << "Already off\n";
        }
    }
    return 0;
}

```

---

## 作者：liuli688 (赞：0)

### 思路：
将问题抽象一下：维护一个数字集合，使集合内的数字两两互质。

再转化一下，就相当于每输入一个数字，就往集合里加入它的约数（不包括 $1$），使集合内数字不重复。所以我们想到了预处理每个数字的约数。

预处理最朴素的方法是试除法，即用 $O(n \sqrt n)$ 的复杂度挨个试 $j$ 能否被 $i$ 整除。伪代码如下：
```
//特判 0 1 2
for i := 3 to n:
	for j := 2 to sqrt(n):
		if j mod i = 0:
			不是质数
	是质数
```

但是我做了一点优化：用倍数法，对于每个 $i$，标记每个 $i$ 的倍数不是质数。这样只需 $O(n \log n)$ 的复杂度即可筛完。

剩下的操作便是用一个数组记录每个约数被哪台机器占用了，依次判断这台机器的约数是否被占了，如果是就输出该被占用格子里的数。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define reg register
#define pb push_back

template <typename T>
inline void read(T &x)//快读函数
{
    char c;
    do
        c = getchar();
    while(c == ' ' || c == '\n');
    x = 0;
    int w = 1;
    if(c == '-')
    {
        w = -1;
        c = getchar();
    }
    do
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }while (c != ' ' && c != '\n');
    x *= w;
}
template <typename T>
inline void write(T arg)//快写函数
{
	T x = arg;
	if(x < 0)
    {
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
inline void writel(string x)//快写字符串的函数
{
    reg int i;
    int len = x.length();
    for(i = 0;i < len;++i)
    	putchar(x[i]);
}

typedef long long ll;
const int MAX = 1e5 + 1;
int n,m,a,k[MAX];//k 为记录被占用的约数的数组
char op;
bool flag;
vector<int> f[MAX];//预处理约数的数组
bitset<MAX> open;//记录机器的开关状态

inline void init(int n)//预处理约数
{
    reg int i,j;
    for(i = 2;i <= n;++i)
        for(j = 1;j <= n / i;++j)
            f[i*j].pb(i);
}

signed main()
{
    read(n);
    read(m);
    init(n);
    while(m--)
    {
        op = getchar();
        getchar();
        read(a);
        if(op == '+')//处理增加操作
        {
            if(open[a])//在询问之前就已经启动了
            {
                writel("Already on\n");
                continue;
            }
            flag = true;
            for(reg auto i : f[a])
            {
                if(k[i])
                {
                    writel("Conflict with ");
                    write(k[i]);
                    putchar('\n');
                    flag = false;
                    break;
                }
            }
            if(!flag)
                continue;
            for(reg auto i : f[a])//占领因数
                k[i] = a;
            open[a] = true;//打开机器
            writel("Success\n");
        }
        else
        {
            if(!open[a])
            {
                writel("Already off\n");
                continue;
            }
            open[a] = false;//关闭机器
            writel("Success\n");
            for(reg auto i : f[a])//取消占领因数
                k[i] = 0;
        }
    }
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

可以考虑维护现有的因数集合。

然后每次插入的时候枚举因数，然后判断当前是否有有这个因子的数即可。

而删除时不直接删除，打个标记，等访问到已经被删的元素时再删即可，这样就用 `vector`，然后只要当前因子对应的编号已经被删除，那么就一直 `pop_back` 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> t[100010];
bool is_in[100010];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		char opt[2]; int s;
		scanf("%s%d", opt, &s);

		if (opt[0] == '+') {
			if (is_in[s]) puts("Already on");
			else {
				int id = -1;

				for (int j = 1; j <= s / j; ++j) {
					if (s % j == 0) {
						// cout << j << ' ' << s / j << endl;
						while (t[j].size() && !is_in[t[j].back()]) t[j].pop_back();

						if (j != 1 && t[j].size() != 0) {
							id = t[j].back();
						}

						t[j].push_back(s);

						if (s / j != j) {
							// cout << j << endl;
							while (t[s / j].size() && !is_in[t[s / j].back()]) t[s / j].pop_back();

							if (t[s / j].size() != 0) {
								id = t[s / j].back();
							}
	
							t[s / j].push_back(s);
						}
					}
				}

				if (id == -1) puts("Success"), is_in[s] = true;
				else {
					is_in[s] = false;
					for (int j = 2; j <= s / j; ++j) {
						if (s % j == 0) {
							while (t[j].size() && !is_in[t[j].back()]) t[j].pop_back();

							if (s / j != j) while (t[s / j].size() && !is_in[t[s / j].back()]) t[s / j].pop_back();
						}
					}

					printf("Conflict with %d\n", id);
				}
			}
		} else {
			if (!is_in[s]) puts("Already off");
			else {
				puts("Success");
				is_in[s] = false;
			}
		}
	}

	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先我们将两种操作分开讨论：

## Part 1 加入操作

那么，我们可以用一个数组 $vis_i = 0/1$ 表示 $i$ 是 关闭/开启 状态，$p_i$ 表示因数有 $i$ 的数。

如果 $vis_x =1 $，说明此机器在之前已经启动过了，输出 `Success`。

然后，对 $x$ 分解质因数，将质因数全部塞进一个集合 $a$ 里面。

如果对于任意一个 $i \in |a|$，$p_i = 0$ 那么表示启动 $x$ 是合法的，然后更新 $p_{a_i}$ 为 $x$，输出 `Success`。（注意还需要更新 $vis_x$）

否则，就随便找到一个 $p_{a_i} \neq 0$，即可。

## Part 2 删除操作

与加入操作同理。

如果 $vis_x = 0$，说明此机器已经处于关闭状态，输出 `Already off`。

然后还是分解质因数，更新 $p_i$ 的值即可。（注意还需要更新 $vis_i$ 的值）

时间复杂度为 $\Theta(n \sqrt n)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,q;
int p[N];
bool vis[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	q = read();
	while (q--){
		char op[10];
		int x;
		scanf("%s",op);
		x = read();
		if (op[0] == '+'){
			if (vis[x]) puts("Already on");
			else{
				int ans = 0,val = x;
				bool ok = true;
				vector<int> v;
				for (re int i = 2;i * i <= x && ok;i++){
					if (x % i == 0){
						if (p[i]){
							ok = false;
							if (p[i]) ans = p[i];
							else ans = p[x / i];
						}
						else{
							v.push_back(i);
							while (x % i == 0) x /= i;
						}
					}
				}
				if (x != 1){
					if (p[x]){
						ok = false;
						ans = p[x];
					}
					else v.push_back(x);
				}
				if (ok){
					vis[val] = true;
					for (auto num:v) p[num] = val;
					puts("Success");
				}
				else printf("Conflict with %d\n",ans);
			}
		}
		else{
			if (!vis[x]) puts("Already off");
			else{
				vis[x] = false;
				for (re int i = 2;i * i <= x;i++){
					if (x % i == 0){
						p[i] = 0;
						while (x % i == 0) x /= i;
					}
				}
				if (x != 1) p[x] = 0;
				puts("Success");
			}
		}
	}
	return 0;
}
```

---

## 作者：OcTar (赞：0)

# CF154B题解

## 题目链接

[CF154B Colliders](https://www.luogu.com.cn/problem/CF154B)

## 题意简述

给定 $m$ 次操作，可以启动或关闭。启动时，要满足：

- 该机器之前是关闭的；

- 该机器的编号 $i$ 与此前已经开启的所有机器编号都互质。

关闭操作就很简单了，不再赘述。

## 题目解析

一眼模拟题。想到一个朴素的做法：维护一个标记数组表示每台机器的状态，在操作时判断即可。重点还是启动操作，朴素代码核心如下：

```cpp
for (int i = 1; i <= n; i++) {
	if (status[i] && __gcd(x, i) != 1) {//两个条件：已经启动了并且不互质，此时会冲突。
		printf("Conflict with %d\n", i);
		return;
	}
}
```
显然我们无法接受这么高的复杂度，于是它超时了，但能获得 $80$ pts。

现在考虑如何优化。我们发现朴素做法最耗时的部分是判断互质，如果能够预处理那就好了。不难想到预处理出 $1-n$ 每个数的因数，判断互质时枚举编号 $i$ 的所有因数，判断是否使用过即可。如果能成功启动，记得要把 $i$ 的因数标记一下。

另外要注意在关闭时，假设要关闭的机器编号为 $i$，则还要把 $i$ 的因数的使用情况清零。完整代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1e5 + 5;
int n, m;
bool status[maxn];//机器的状态
int used[maxn];判断某个因数是否使用过，以及使用了的编号是多少
vector<int> tab[maxn];//每个数的因数表
void init() {//预处理因数表
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= i; j++) {
			if (i % j == 0) {
			    if (j != 1) {
			        tab[i].push_back(j);
			    }
				if (j * j != i) {//这里是为了避免完全平方数的因数被加入两次
					tab[i].push_back(i / j);
				}
			}
		}
	}
}
void judge(char opt, int x) {
	if (opt == '+') {
		if (status[x]) {
			printf("Already on\n");
			return;
		}
		for (int i = 0; i < tab[x].size(); i++) {
			if (used[tab[x][i]]) {
				printf("Conflict with %d\n", used[tab[x][i]]);
				return;
			}
		}
		status[x] = 1;
		printf("Success\n");
        //标记，表示这些因数已经被 x 使用过了
		for (int i = 0; i < tab[x].size(); i++) {
			used[tab[x][i]] = x;
		}
		return;
	} else {
		if (!status[x]) {
			printf("Already off\n");
			return;
		}
		status[x] = 0;
		printf("Success\n");
        //注意关闭时把因数使用情况清零
		for (int i = 0; i < tab[x].size(); i++) {
			used[tab[x][i]] = 0;
		}
		return;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	init();
	while (m--) {
		char opt[2];
		int x;
		scanf("%s%d", opt, &x);
		judge(opt[0], x);
	}
	return 0;
}
```

---

## 作者：Shanganze (赞：0)

### 分析：
既然要开启对撞机时需要判断两数是否互质那么我们就可以从互质的性质来入手。

判断两个数是否互质，就是看两数是否有公因数，也就是两个数互质时，没有公共质因子。

我们可以用一个数组来存储质因子是否出现过。用欧拉筛提前预处理出质数，记录下一个数最小质因子，不断相除就做到了质因数分解。

若开启一个对撞机，先判断其质因子是否标记过，若可以正常开启，就将其质因子都标记上，反之关闭时就将其质因子标记删去。

还有一个就是怎样找出与其冲突的对撞机的编号，我们可以在标记时，把质因子标记成原对撞机编号，判断时直接输出标记即可。

具体实现可以根据代码来理解。

### AC  Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int k[1000001],v[1000001],p[1000001],vv[1000001];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}
int main()
{
	int n,m,l=0;
	scanf("%d%d",&n,&m);
	for(int q=2;q<=n;q++)
	{
		if(k[q]==0)
		{
			p[++l]=q;
		}
		for(int w=1;p[w]<=n/q&&w<=l;w++)
		{
			k[p[w]*q]=1;
			if(q%p[w]==0)break;
		}
	}
	memset(k,0,sizeof(k));
	for(int q=1;q<=l;q++)
	{
		for(int w=1;w<=n/p[q];w++)
		{
			if(k[p[q]*w]==0)
			{
				k[p[q]*w]=p[q];
			}
		}
	}
	for(register int q=1;q<=m;q++)
	{
		char a;int b;
		cin>>a;b=read();
		if(a=='+')
		{
			if(vv[b]==1)
			{
				cout<<"Already on\n";
				continue;
			}
			else
			{
				
				int o=b,i=b,mm=0;
				while(b!=1)
				{
					if(v[k[b]]!=0)
					{
						cout<<"Conflict with "<<v[k[b]]<<endl;
						mm=1;
						break;
					}
					b/=k[b];
				}
				if(mm==0)
				{vv[o]=1;
					v[o]=i;
					while(o!=1)
					{
						v[k[o]]=i;
						o/=k[o];
					}
					cout<<"Success\n";
				}
			}
		}
		if(a=='-')
		{
			if(vv[b]==0)
			{
				cout<<"Already off\n";
			}
			else
			{
				vv[b]=0;
				int o=b;
				v[b]=0;
				while(b!=1)
				{
					v[k[b]]=0;
					b/=k[b];
				}
				cout<<"Success\n";
			}
		}
	}
	return 0;
}
```



---

