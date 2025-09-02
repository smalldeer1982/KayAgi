# New Year Permutation

## 题目描述

## 题意翻译

用户 ainta 有一个排列 $p_1,p_2,...,p_n$ 。新年到了，他希望把他的排列变得尽可能漂亮。

当且仅当存在整数 $k$（$1 \le k \le n$）使 $a_1=b_1,a_2=b_2,\ldots,a_{k-1}=b_{k-1}$ 和 $a_k<b_k$ 都成立，排列 $a_1,a_2,...,a_n$ 比  $b_1,b_2,...,b_n$ 更漂亮。

排列 $p$ 非常敏感，只可以通过交换两个不同的元素来修改它。但是交换两个不同的元素比你想象得要难。给出一个 $n\times n$ 的二进制矩阵 $A$ ，当且仅当 $A_{i,j}=1$ 时，用户 ainta 可以交换两个元素 $p_i,p_j (1<=i,j<=n,i\neq j)$ 的值。

给定排列 $p$ 和矩阵 $A$ ，用户 ainta 想知道他能得到的最漂亮的排列。

## 样例 #1

### 输入

```
7
5 2 4 3 6 7 1
0001001
0000000
0000010
1000001
0000000
0010000
1001000
```

### 输出

```
1 2 4 3 6 7 5
```

## 样例 #2

### 输入

```
5
4 2 1 5 3
00100
00011
10010
01101
01010
```

### 输出

```
1 2 3 4 5
```

# 题解

## 作者：zhanghzqwq (赞：3)

这道题题意就是：给你一个1~n的数列和交换规则，让你把这个数列变成字典序最小。

看见好多大佬都用的并查集，不过我~~太懒~~用的是无脑的Floyd的传递闭包。结果两分钟写完传递闭包，在求字典序最小时调了半天。。。

代码如下：

```cpp
#include<iostream>
using namespace std;
const int MAXN=305;
int p[MAXN];
int adj[MAXN][MAXN];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){//把p数列输入
		cin>>p[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char ch;
			cin>>ch;
			adj[i][j]=ch-'0';//建边不解释
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				adj[i][j]=adj[i][j]||(adj[i][k]&&adj[k][j]);//Floyd传递闭包的核心
			}
		}
	}
	for(int i=1;i<=n;i++){
		int index=i;//index初始化一定是i
		for(int j=i+1;j<=n;j++){//找一下字典序最小且可以交换
			if(adj[i][j]){
				if(p[j]<p[index]){
					index=j;//找到了，重置一下index
				}
			}
		}
		int t=p[i];//这三行是交换
		p[i]=p[index];
		p[index]=t;
	}
	for(int i=1;i<=n;i++){//输出不解释
		cout<<p[i]<<" ";
	}
	cout<<endl;//换行是个信仰
	return 0;//完结撒花
}
```


---

## 作者：SymphonyOfEuler (赞：2)

这道题是一个很简单的Floyd闭包问题。

送$Floyd$一首打油诗：

### 三个破变量，一共就十行。

### 编程三分钟，运行一晚上。

题目给你$n$个ainta有的permutation，接下来$n*n$  $0,1$构成的一个矩阵，如果$Aij$ 为1，那么可以交换这两个元素，否则不能。从这里可以看出可以用Floyd的传递闭包。 

- 因为这道题的$n$不算大 $n ( 1<=n<=300 )$，所以可以用$O(n^3)$的Floyd，但是最短路问题一般需要用$Dijkstra$ 或者是 $Bellman-Ford (SPFA)$，不然一定会超时（不是卡常那回事）。

## 思路：

- 先把ainta已有的permutation输入进来。

- 然后输入进来矩阵

- 处理一下传递闭包的d数组

- Floyd传递闭包

- 最后处理字典序（注意读题！！！）

- 结束。


**我们康康这个代码。**

```
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int n,d[305][305],w[305][305];
int p[305];
int main () {
    cin>>n;
    for (int i = 1; i <= n; ++i) {//输入ainta已有的permutation
        cin>>p[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j =1 ; j <= n; ++j) {//输入进来矩阵
            char qaq;
            cin>>qaq;
            d[i][j]=qaq-'0';
        }
    }
    /*for (int i = 1; i <= n; ++i) {//处理传递闭包
        for (int j = 1; j <= n; ++j) {
            if (i == j) d[i][j] = 0;
            else if (w[i][j]) d[i][j] = w[i][j];
            else d[i][j] = 0x3f;
        }
    }*/
    for (int k = 1; k <= n; ++k) {//传递闭包
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = d[i][j]||(d[i][k]&&d[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {//处理字典序
        int dex=i;
        for (int j = i+1; j <= n; ++j) {
            if(d[i][j]){
                if(p[j]<p[dex]) dex=j;
            }
        }
        int t=p[i];
        p[i]=p[dex];
        p[dex]=t;
    }
    for (int i = 1; i <= n; ++i) {//输出
        cout<<p[i]<<" ";
    }
    return 0;
}
```






---

## 作者：叶枫 (赞：1)

不用$Floyd$,可以用**并查集**维护连通性，从左往右从连通块中每次取出最小的

没啥好讲的

```cpp
#include<bits/stdc++.h>
#define inf 1000000000
#define int long long 
using namespace std;
int read()
{
    ll x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n;
int a[305],fa[305];
char ch[305];
inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        scanf("%s",ch+1);
        for(int j=1;j<=n;j++)
            if(ch[j]=='1'){
                int p=find(i),q=find(j);
                if(p!=q) fa[p]=q;
            }
    }
    for(int i=1;i<=n;i++){
        int t=i;
        for(int j=i+1;j<=n;j++)
            if(find(j)==find(i)&&a[j]<a[t]) t=j;
        swap(a[i],a[t]);
    }
    for(int i=1;i<=n;i++) printf("%d ”,a[i]);
    return 0;
}
```

---

## 作者：Sol1 (赞：1)

Goodbye 2014 的一道~~水~~题，我在Floyd之后用的是Dfs来求解最短路。

Floyd不用说了吧。。。把状态转移方程改成$ dp_{i,j}=dp_{i,j}|(dp_{i,k} \& dp_{k,j})\ for\ all\ i,j,k \leq n$就可以求出哪些元素之间可以交换而哪些元素之间不可以交换了。

而后面的DFS则需要讲解一下：

~~(毕竟本蒟蒻还是谈字典序色变……)~~

因为构造排列时有一个非常之重要的性质为较小的数越靠前，排列字典序就越靠前。比如排列1,2,5,4,3 > 排列1,2,4,5,3。

因此可以构造出一个显然正确的贪心算法：从小到大枚举1~N之间的每一个数，把当前数尽量往前放，放完N个后就得到答案了。

然而这里为什么要用DFS呢？因为有些数的位置会被可以换到这里的数占掉，所以需要回溯。

最后注意一下读入要用string。。。刚开始直接读入结果它把一行认定为一个数，然后就不出结果。。。导致我以为死循环了然后调试了30min。。。。。。

代码来袭————————————————————

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 305;
int p[N], n, ans[N];
bool dis[N][N];
string mtx[N];

void Read() {
    scanf("%d", &n);
    for (int i = 1;i <= n;i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 1;i <= n;i++) {
        cin >> mtx[i];
    }
}

void Prefix() {
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            dis[i][j] = mtx[i][j - 1] - '0';
        }
    }
    for (int k = 1;k <= n;k++) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                dis[i][j] |= dis[i][k] & dis[k][j];
            }
        }
    }
}

void Solve(int step) {
    if (step == n + 1) {
        return;
    }
    int k;
    for (int i = 1;i <= n;i++) {
        if (p[i] == step) {
            k = i;
            break;
        }
    }
    for (int i = 1;i <= k;i++) {
        if (!ans[i] && (i == k || dis[i][k])) {
            ans[i] = step;
            swap(p[i], p[k]);
            Solve(step + 1);
            swap(p[i], p[k]);
        }
    }
}

int main()
{
    Read();
    Prefix();
// 	for (int i = 1;i <= n;i++) {
// 		for (int j = 1;j <= n;j++) {
// 			cout << dis[i][j];
// 		}
// 		cout << endl;
// 	}
    Solve(1);
    for (int i = 1;i <= n;i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：0)

~~楼上的题解太深奥了,本蒟蒻竟然看不懂~~⊙▽⊙!
于是自己开始打代码~~

首先这道题难度系数还可以,但技巧性很强.需要FLOYD等算法的支撑.
Floyd什么东东呢？我简单介绍一下。

这运用了DP的思维，用三个变量来回的倒。
k为中间变量，ij为两个节点。也就是说：i到k的距离+k到j的距离的和比i到j的直接距离要来的小的话，就更新。

这道题要直靠Floyd去判断联通分量——i能到k且k能到j，那么i定能到j

```cpp
using namespace std;

#define REP(i,n) for(int (i)=0; i<(int)(n); i++)

const int MAXN = 310;
bool dist[MAXN][MAXN]
int p[MAXN];

int main(void) {
	int N;
	cin >> N;
	REP(i,N) cin >> p[i];
	REP(i,N) {
		string tmp;
		cin >> tmp;
		REP(j,N) dist[i][j] = tmp[j]=='1'||i==j;//初始化
	}
	REP(k,N) REP(i,N) REP(j,N)//天坑,一定是k,i,j!Floyd开始了
		if(dist[i][k] && dist[k][j]) dist[i][j] = true;
	REP(i,N) for(int j=i+1; j<N; j++)
		if(dist[i][j] && p[j]<p[i]) swap(p[i], p[j]);//交换
	REP(i,N) cout << p[i] << ' ';
	cout << endl;
	return 0;
}

```
当然也可以通过DFS来实现,代码就不展示了


---

## 作者：ModestCoder_ (赞：0)

怎么说呢，输入就需要$O(n^2)$的题目有点那个了。。

祭出一个基础算法——并查集！！！

仿照缩点（强连通分量）的想法，如果一个点的集合，对于集合中的每一个点都能找到另一个集合中的点可以与之交换

那么这个点的集合可看成一个点，用并查集维护一下连通性

对于每一个位置，找当下$(vis=0)$最小的并且与这个位置联通的点输出

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 310
using namespace std;
struct data{
	int x, id;
}a[maxn];
int f[maxn], vis[maxn], n;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp(data x, data y){ return x.x < y.x; }
int getf(int k){ return k == f[k] ? k : f[k] = getf(f[k]); }

int get(){
	char c = getchar();
	for (; c != '0' && c != '1'; c = getchar());
	return c == '1';
}

void Union(int i, int j){
	int x = getf(i), y = getf(j);
	if (x != y) f[x] = y;
}

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = (data){read(), i}, f[i] = i;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (get()) Union(i, j);
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (!vis[a[j].id] && getf(i) == getf(a[j].id)){
				vis[a[j].id] = 1, printf("%d ", a[j].x); break;
			}
	return 0;
}
```


---

## 作者：moye到碗里来 (赞：0)

emmm这道题求你字典序最小就贪心呗。。。floyd传递闭包，然后就越靠前越小就行。。。没啥特别需要注意的点
```
#include<bits/stdc++.h>
using namespace std;
int n,f[305][305];
int num[305];
int use[305];
int newnum[305];
int main()
{
	scanf("%d",&n);
	memset(newnum,0x3f,sizeof(newnum));
	for(int i = 1; i <=  n; ++i)
	{
		scanf("%d",&num[i]);newnum[i] = num[i];
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			scanf("%1d",&f[i][j]);
		}
	}
	for(int k = 1; k <= n; ++k){
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				f[i][j] = (f[i][j] | (f[i][k] & f[k][j]));
			}
		}
	}
	int cnt = 0;
	for(int i = 1; i <= n; ++i){
		cnt = i;
		if(use[i] == 1)newnum[i] = 0x3f3f3f;
		for(int j = 1; j <= n; ++j){
			if(f[i][j] && !use[j])
			if(num[j] < newnum[i]){
				newnum[i] = num[j];cnt = j;
			}
		}
		use[cnt] = 1;
	}
	for(int i = 1; i <= n; ++i)printf("%d ",newnum[i]);
}
```


---

