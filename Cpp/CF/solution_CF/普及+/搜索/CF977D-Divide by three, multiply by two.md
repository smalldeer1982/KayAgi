# Divide by three, multiply by two

## 题目描述

有一个长度为 $n$ 的数列 $a_i$，要求你将这个数列重排成一个排列 $p_i$，使得对于任意的 $p_i(1 \le i < n)$：

- $p_i \times 2 = p_{i+1}$，或者
- 当 $p_i$ 可以被 $3$ 整除时，$p_i \div 3 = p_{i+1}$。

保证答案存在。

## 说明/提示

在第一个样例中，一种可能的合法排列为 $[9,3,6,12,4,8]$。

## 样例 #1

### 输入

```
6
4 8 6 3 12 9
```

### 输出

```
9 3 6 12 4 8 
```

## 样例 #2

### 输入

```
4
42 28 84 126
```

### 输出

```
126 42 84 28 
```

## 样例 #3

### 输入

```
2
1000000000000000000 3000000000000000000
```

### 输出

```
3000000000000000000 1000000000000000000 
```

# 题解

## 作者：yuzhechuan (赞：9)


~~楼下的最长路惊到了我~~

其实这是一道脑筋急转弯。。。

思路如下：

每个数都有2,3两种因子，/3减少因子3的个数，x2增加因子2的个数

因为/3和x2是分块的，而/3决定了这条序列能走多远，所以这里考虑3的因子个数

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
struct STR
{
	long long a,b;
}A[110];//.a存原数，.b存因数3的个数
int cmp(STR m,STR n)
{
	if(m.b!=n.b)return m.b>n.b;//主关键字按因数3的个数降序排
	return m.a<n.a;//相同时，就按升序排，因为要用*2来将将序列救起
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>A[i].a;
		long long k=A[i].a;
		while(k%3==0&&k!=0)
		{
			A[i].b++;
			k/=3;
		}//记录下各数字中因数3的个数
	}
	sort(A+1,A+1+n,cmp);
	for(int i=1;i<=n;i++)
		cout<<A[i].a<<" ";//输出
}
```

---

## 作者：Islauso (赞：9)

这道题我一看，按一定要求排列一个序列，这不就是我刚刚学的拓扑排序吗？

再一看题解里全都是搜索，于是我就高兴地来写这篇题解了。

关于拓扑排序，如果不了解的，可以康一康我这篇[博客](https://xiao-lin52.github.io/2020/02/05/【笔记】图论-拓扑排序/)。

**我的思路：**

先用两个循环，找出所有符合题目要求的数对（比如两个数分别为$a_i$和$a_j$，如果$a_i\times 2=a_j$或$a_j\times 3=a_i$即为符合要求），连有向边（在上面那个例子中就是连一条从$a_i$到$a_j$的边），然后跑一边裸的拓扑，完事。

看上去很简单对不对？但我在写代码的时候突然想到一个问题。

**拓扑排序只能处理 DAG（有向无环图），如果这个东西有环怎么办？**

于是我又开始证明在这道题中按我刚才的想法建图不可能存在环，过程如下：

设$u$为当前点的值,$n,m$为任意值。

如果图中存在环，当且仅当有下面两种情况：

$$\dfrac{2^n}{3^m}\cdot u=\dfrac{1}{2}\cdot u$$

$$\text{或}$$

$$\dfrac{2^n}{3^m}\cdot u=3\cdot u$$

注：$\dfrac{2^n}{3^m}\cdot u$其实就是经过$n$次乘$2$和$m$次除$3$
后所得到的值。

我们一个一个来证明。

第一种：

$$\because \dfrac{2^n}{3^m}=\dfrac{1}{2}$$

$$\therefore 2^{n+1}=3^m$$

$$\because 2^{n+1} \bmod 2=0,3^m \bmod 2 \ne 0$$

$$\therefore \text{原式无解}$$

第二种：

$$\because \dfrac{2^n}{3^m}=3$$

$$\therefore 2^n=3^{m+1}$$

$$\text{同上，原式无解}$$

综上所述，本题所建的图中不可能有环。

既然没有环，那我们就可以快乐地跑拓扑了！

**AC代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot,in[101],ans[101],edge[101][101];
long long a[101];
queue<int> q;
void topo()//拓扑
{
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans[++tot]=u;//这里我的ans数组是存的下标
		for(int i=1;i<=n;i++)
			if(edge[u][i])
			{
				in[i]--;
				if(!in[i])
					q.push(i);
			}
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",a[ans[i]]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if((a[i]*2==a[j])||(a[i]%3==0&&a[i]/3==a[j]))//按照上面所说的方法建图
			{
				edge[i][j]=1;
				in[j]++;
			}
	topo();
	return 0;
}
```

整个过程其实还是很简单的，主要是要证明没有环。

---

## 作者：black_trees (赞：4)

题目链接（没读题自行读题再返回）：[LINK](https://www.luogu.com.cn/problem/CF977D)

---------

### 思路：

这道题是要你把一个序列维护成一定的顺序，拓扑排序是很容易想到的。

不过为了给不会拓扑的同学一些体验，我提供一种 $dfs$的做法。

题目要求可以近似地看成不重复的填数（只是这里要满足特殊的要求）。

先可以很快的打出一个填数的板子：

~~~cpp
void dfs(int step){
	if(step>n){//填完n个数，输出
		print();
	}
	for(register int i=1;i<=n;++i){
		if(vis[i]==false){//没用过
			vis[i]=true;//标记
			res[step]=a[i];//保存结果
			dfs(step+1);//递归继续搜索
			vis[i]=false;//回溯
		}
	}
}
~~~

到这里是不是很轻松？

只要学过 $dfs$ 应该是可以理解的.

题目里说：

对于排出来的序列 $p$ ,$p_i$ 满足：

+ $p_i \times 2 =p_{i+1}$

+ 若 $p_i \mod 3 =0 ,p_{i+1} \times 3 =p_i$

所以只要在 $dfs$ 里加一行：

`if(res[step-1]*2==a[i]||a[i]*3==res[step-1])`

不就可以 $AC$ 了吗？

$dfs$ 完整代码（数据比较大所以开`unsigned long long`）:


```
void dfs(unsigned long long step){
	if(step>n){
		print();
	}
	for(register unsigned long long i=1;i<=n;++i){
		if(vis[i]==false){
			if(res[step-1]*2==a[i]||a[i]*3==res[step-1]){
				vis[i]=true;
				res[step]=a[i];
				dfs(step+1);
				vis[i]=false;
			}
		}
	}
}
```

完整代码就不放了，自己理解了是可以写出来的。

-----



---

## 作者：KillerXu (赞：3)

不妨理解题意为把原数列按照要求放进新数列中。

那么直接搜索每一步放什么就可以了，只要上一步乘$2$等于这一步或者这一步乘$3$等于上一步就可以放。

## Code
```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define N 105
#define ll long long 

using namespace std;

ll a[N] , ans[N];//记得开long long，ans就是答案数组，即新数列
int n , vis[N];//vis数组记录原数列中的数是否已经放到了新数列中
int flag = 0;//flag记录是否已有解

void print(){
	for(int i = 1; i <= n; i++) printf("%lld " , ans[i]);//输出
}

void dfs(int x , int step){
	if(step == n && !flag){//如果放完了且之前没有可行解就输出
		flag = 1;
		print();
		return;
	}
	
	vis[x] = 1;//打上标记，表示已经搜过了
	for(int i = 1; i <= n; i++){ 
		if(!vis[i] && (ans[step] * 2 == a[i] || a[i] * 3 == ans[step])){//一定要注意搜过的不能再搜了
			ans[step + 1] = a[i];//向新数列中填充数
			dfs(i , step + 1);//继续搜
		}
	}
	vis[x] = 0;//回溯
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++){
		ans[1] = a[i];
		memset(vis , 0 , sizeof(vis));//初始化为0
		dfs(i , 1);
	}
	
	return 0;
}
```

---

## 作者：Tweetuzki (赞：2)

我是用最长路解决的这道题……

首先可以推出一个结论：输入数据中不会有两个相同的数。因为从一个数开始，每乘一个 $2$，就会增加一个双数，而无论除掉多少次的 $3$，都不可能把这个 $2$ 的因子给除掉。

动态规划。设 $dp_i$ 表示到 $i$ 号点时的最长路长度。那么 $dp_i$ 可以由任意满足 $a_i \div 3 = a_j$ 或 $a_i \times 2 = a_j$ 的 $j$ 转移而来（$dp_i = dp_j + 1$）。

$dp$ 的转移可以通过建图的方法来解决。注意到，如果这一个数是 $x$，那么它的下一个数，要么是 $x \div 3$，要么是 $ x \times 2 $。所以我可以任意连向值为 $x \div 3$ 或 $ x \times 2$ 的点，然后这个点可以继续转移。寻找的过程可以使用 `map` 优化到 $\log n$ 的复杂度。（当然也可以哈希）

根据以上的结论，这一定是一张有向无环图，于是可以在上面跑拓扑排序，来顺便进行动态规划的转移。在每次的转移后，记录前驱节点，以方便之后打印方案的路径还原。这里的复杂度是 $O(n)$ 的。

这样，时间复杂度是 $O(n \log n)$ 的。但是总共复杂度的瓶颈在于 `map` 的查找，那么如果用哈希来替代，就可以跑到 $O(n)$ 的复杂度了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

typedef long long llt;
typedef vector<llt>::iterator vit;

const int MaxN = 100000 + 5;

int N;
vector <llt> A;
int pre[MaxN], dp[MaxN];
int ind[MaxN];
queue <int> que;
stack <int> st;
map <llt, int> mp;
vector <int> G[MaxN];

inline llt read() {
    llt x = 0; char c;
    do c = getchar(); while ( c < '0' || c > '9' );
    do x = ( x << 1 ) + ( x << 3 ) + c - '0', c = getchar(); while ( c >= '0' && c <= '9' );
    return x;
}

void init() {
    scanf( "%d", &N );
    A.resize( N );
    for ( int i = 0; i < N; ++i ) A[i] = read();
}

// 拓扑排序
void top_sort() {
    for ( int i = 1; i <= N; ++i )
        if ( ind[i] == 0 ) {
            que.push( i );
            dp[i] = 1;
        }
    while ( !que.empty() ) {
        int u = que.front(); que.pop();
        for ( int i = 0; i < G[u].size(); ++i ) {
            int v = G[u][i];
            if ( dp[u] + 1 > dp[v] ) {
                dp[v] = dp[u] + 1;
                pre[v] = u;
            }
            ind[v]--;

            if ( ind[v] == 0 ) que.push( v );
        }
    }
}

void solve() {
    // 使用 map 来进行查找
    for ( int i = 0; i < N; ++i )
        mp[ A[i] ] = i + 1;
    for ( int i = 0; i < N; ++i ) {
        int u = i + 1, v = 0;
        if ( A[i] % 3 == 0 ) {
            v = mp[ A[i] / 3 ];
            if ( v != 0 ) {
                //printf( "add edge from %d to %d\n", u, v );
                G[u].push_back( v );
                ind[v]++;
            }
        }
        v = mp[ A[i] * 2 ];
        if ( v != 0 ) {
            //printf( "add edge from %d to %d\n", u, v );
            G[u].push_back( v );
            ind[v]++;
        }
    }

    top_sort();
}

void print() {
    // 路径还原，打印答案
    for ( int i = 1; i <= N; ++i ) {
        if ( dp[i] == N ) {
            for ( int v = i; v != 0; v = pre[v] ) st.push( v - 1 );
            while ( !st.empty() ) {
                printf( "%lld ", A[ st.top() ] );
                st.pop();
            }
            break;
        }
    }
}

int main() {
    init();
    solve();
    print();
    return 0;
}
```

---

## 作者：Tyyyyyy (赞：2)

## 不知道为啥要搞那么复杂...~~明明就是个暴搜~~
这题题意很好理解~因此我们的第一个想法就是按着题意来。
看一下数据范围：2$\leqslant$n$\leqslant$100，那么暴力算法是可以的。

这里科普一下：一般来说，只要循环次数不超过$10^8$就不会超时~~~不排除特殊情况，出题人故意卡暴力~~

所以暴力算法还是很好写的啦~AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[101],j=1;
long long a[101],p[101];//注意数据范围！int会炸
bool can=0;//是否找到了方案
void dfs(int x,int s)//x表示目前数值，s表示目前位置
{
	if(s==n&&!can)//如果找到了方案便输出
	{
		can=1;//标记已经找到方案
		for(int j=1;j<=n;j++)printf("%lld ",p[j]);
		printf("\n");
		return;
	}
	vis[x]=1;//查过就标记一下，不要重复查浪费时间
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]&&(p[s]*2==a[i]||p[s]==a[i]*3))
		{
			p[s+1]=a[i];
			dfs(i,s+1);//符合题目要求就置入答案数组
		}
	}
	vis[x]=0;//不可或缺的回溯
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		p[1]=a[i];//从a数组的每一项开始尝试
		memset(vis,0,sizeof(0));//每次都要初始化
		dfs(i,1);//搜索符合要求的答案
	}
	return 0;
}
```
更改于：2020.7.26：用LaTeX公式修改了数据范围。

---

## 作者：zhangyuhan (赞：1)

~~啦啦啦又是一道大爆搜~~

搜索的套路非常简单，让我来讲一讲。

首先，我们需要记录答案的$p$数组和搜索时填充$p$数组的指针$t$。

我们先思考终点状态：

假设我们的$t$是从$1$开始的，如果$t>n$(想一想，为什么？)时，也就是已经全部填完时，我们需要输出整个$p$数组，并且由于题目中说只要输出其中一种方案，我们就可以设一个$bool$型变量$flag$，一开始为$false$，如果已经找到满足条件的排列，就改为$true$。

代码实现很简单：

```cpp
if(t>n){
	print();
	flag=true;
	return ;
}
```

$print$函数也很简单

```cpp
void print(){
	for(int i=1;i<=n;i++)
		cout<<p[i]<<" ";
	cout<<endl;
}
```

下面思考如何搜索。首先搜索的条件基于还未找到方案，即$flag=false$时。接着遍历整个$a$数组。令$i$为循环变量，能填充到$p$数组的条件如下：

$1.$ $a_i$还未放入$p$数组里

$2.$ $a_i$可以是$p$数组前一个数的两倍

$3.$ $p$数组前一个数可以整除$3$并且除以$3$是$a_i$

其中$1$必须满足，$2$、$3$中只要有一个满足即可。

对于$1$来讲，我们定义$bool$型数组$used$，一开始都为$false$，如果$used_i=false$，就表明没用过。

对于$2$来讲，稍微提一下：$p$数组前一个数就是$p_{t-1}$。因为当前是第$t$个，前面一个就是第$t-1$个。那么这个条件形式化地讲就是$p_{t-1}*2=a_i$

对于$3$来讲，形式化地讲，就是$p_{t-1} \mod 3=0$ && $p_{t-1}÷3=a_i$

如果满足条件，标记（即$used_i=true$），放数（即$p_t=a_i$），继续搜（即$dfs(t+1)$），回溯（即$used_i=false$）

代码实现较为简单（不过我写条件时有些混乱，请见谅）

```cpp
if(!flag)
	for(int i=1;i<=n;i++){
		if(!used[i]&&(t==1||(p[t-1]*2==a[i]||(p[t-1]%3==0&&p[t-1]/3==a[i])))){
			used[i]=true;
			p[t]=a[i];
			dfs(t+1);
			used[i]=false;
		}
	}
```

拼一下$dfs$就出来了

```cpp
void dfs(int t){
	if(t>n){
		print();
		flag=true;
		return ;
	}
	if(!flag)
		for(int i=1;i<=n;i++){
			if(!used[i]&&(t==1||(p[t-1]*2==a[i]||(p[t-1]%3==0&&p[t-1]/3==a[i])))){
				used[i]=true;
				p[t]=a[i];
				dfs(t+1);
				used[i]=false;
			}
		}
}	
```

最后一个坑点：**p数组和a数组要开long long！！！**

$AC$ $Code$

```cpp
#include <iostream>
using namespace std;

int n;

long long p[110],a[110];

bool flag,used[110];

void print(){
	for(int i=1;i<=n;i++)
		cout<<p[i]<<" ";
	cout<<endl;
}

void dfs(int t){
	if(t>n){
		print();
		flag=true;
		return ;
	}
	if(!flag)
		for(int i=1;i<=n;i++){
			if(!used[i]&&(t==1||(p[t-1]*2==a[i]||(p[t-1]%3==0&&p[t-1]/3==a[i])))){
				used[i]=true;
				p[t]=a[i];
				dfs(t+1);
				used[i]=false;
			}
		}
}	

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	dfs(1);//从一开始，便于填充
	return 0;//完结撒花！
}
```

---

## 作者：outis_crypt (赞：0)

这题我的思路比较简单：

主要用到了搜索

C++可以使用STL里的 **binary_search()**

Python可以使用 **in** 来判断

既然题目要求生成一个新排列，且存在一定规则。那么我们就先找出这个新排列的第一个数作为**start**。

**start**应当满足以下要求：

1、如果这个数是偶数，那么原数列中应当**不存在** start/2 ， 和 start*3

2、如果是奇数， 原数列中应当**不存在** start*3

举个例子：

原数列 : 4 8 6 3 12 9

满足条件的只有9, 所以 start=9

好了，既然新排列的头找到了，后面按照题目的规则生成就行了


生成思路如下:

1、如果start为偶数, 分两种情况:

      1.如果 start%3==0 并且 start/3 存在于原数列，输出start/3。 更新start/=3, continue
            
      2.如果start*2存在于原数列，输出start*2。 更新start*=2, continue
2、如果start为奇数， 同上：

      1. 如果start*2存在于原数列，输出start*2。 更新start*=2, continue
      
      2.如果start/3 存在于原数列，输出start/3。 更新start/=3, continue
     
还是上述的例子:  start=9

start下一个数满足条件的只有3， 更新start=3, 再去查找

3之后应该是 6 , 6之后应该是 12 , 12之后是4， 4之后是8


Python代码如下：
```python
n=eval(input())
a=input().split()
length=n
start=0
for i in a:
    if int(i)%2 ==0:
        if not (str(eval(i)*3) in a) and not (str(eval(i)//2) in a):
            start=eval(i)
            break
    else:
        if not str(eval(i)*3) in a:
            start=eval(i)
            break
print(start, end=" ")
while length:
    length-=1
    if start%2==0:
        if start%3==0:
            x=start//3
            if(str(x) in a):
                start=x
                print(start,end=" ")
                continue
        x=start*2
        if(str(x) in a):
            print(x, end=" ")
            start=x
    else:
        x=start*2
        if str(x) in a:
            print(x, end=" ")
            start=x
            continue
        y=start//3
        if str(y) in a:
            print(y,end=" ")
            start=y


```





---

## 作者：BeyondStars (赞：0)

## 题目描述
有一个长度为 $n$ 的数列 $a_i$，要求你将这个数列重排成一个排列 $p_i$，使得对于任意的 $p_i(1 \le i < n)$：

- $p_i \times 2 = p_{i+1}$，或者
- 当 $p_i$ 可以被 $3$ 整除时，$p_i \div 3 = p_{i+1}$。

保证答案存在。

## 输入输出格式

**输入格式：**

输入包含两行。

第一行一个整数 $n(2 \le n \le 100)$，表示数列中的元素个数。  
第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n (1 \le a_i \le 10^{18})$，描述这个数列。

**输出格式：**

输出应包含 $n$ 个整数 $p_1, p_2, \dots, p_n$，表示你的答案。

## 说明

在第一个样例中，一种可能的合法排列为 $[9,3,6,12,4,8]$。
#解答
不知道为什么楼下做的那么复杂，明明搜索就A了的题而已。。。。
##法1：乱搞
就是取2个随机数，然后把这两个随机数所代表的的位置的数交换，每交换一次就判断一下是不是符合题意。这样可以过3个点。大概就是小于20左右的数据范围可以过吧。多了就过不了啦
代码：
```cpp
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n;
long long a[101];
bool judge(){
    for(int i = 1;i<n;i++){
        if(!(a[i]*2ll==a[i+1]||a[i+1]*3ll==a[i])){
            return false;
        }
    }
    return true;
}
void work(){
    int x=0,y = 0;
    srand((int)time(0));
    while(!judge()){
        x=0,y = 0;
        while(x==y) {
            while (x == 0||x==y)x = rand()%(n+1);
            while (y == 0||x==y)y = rand()%(n+1);
        }
        swap(a[x],a[y]);   //as
        x = y = 0;
    }
}
int main(void){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
    }
    work();
    for(int i = 1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}
```
##法2：老实地搜索吧
没有什么难度，复杂度也很低，直接搜就行
```cpp
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n;
long long a[101];
int used[101];
long long ans[101];
inline void print(){
    for(int i = 1;i<=n;i++)cout<<ans[i]<<' ';
    exit(0);
}
void dfs(int pos){
    if(pos>n){
        print();
    }
    for(int i = 1;i<=n;i++){
        if(!used[i]){
            if(a[i]==ans[pos-1]*2||a[i]*3==ans[pos-1]){
                used[i] = true;
                ans[pos] = a[i];
                dfs(pos+1);
                used[i] = false;
            }
        }
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
    }
    for(int i = 1;i<=n;i++){
        ans[1] = a[i];
        used[i] = true;
        dfs(2);
        used[i] = false;
    }
    return 0;
}
```

---

