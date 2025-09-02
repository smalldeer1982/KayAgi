# [USACO10DEC] The Trough Game S

## 题目描述

Farmer John and Bessie are playing games again. This one has to do with troughs of water.

Farmer John has hidden N (1 <= N <= 20) troughs behind the barn, and has filled some of them with food. Bessie has asked M (1 <= M <= 100) questions of the form, 'How many troughs from this list (which she recites) are filled?'.

Bessie needs your help to deduce which troughs are actually filled.

Consider an example with four troughs where Bessie has asked these questions (and received the indicated answers):

1) 'How many of these troughs are filled: trough 1' -->  1 trough is filled

2) 'How many of these troughs are filled: troughs 2 and 3' -->  1 trough is filled

3) 'How many of these troughs are filled: troughs 1 and 4' -->  1 trough is filled

4) 'How many of these troughs are filled: troughs 3 and 4' -->  1 trough is filled

From question 1, we know trough 1 is filled.

From question 3, we then know trough 4 is empty. 

From question 4, we then know that trough 3 is filled. 

From question 2, we then know that trough 2 is empty. 

Farmer John 和 Bessie 在玩一个游戏。

Farmer John 准备了 $n$ 个槽（$1\le n\le20$），其中一些槽中藏有食物。Bessie 为了知道哪些槽中有食物，会询问 $m$ 个形如“第 $x_1\cdots x_k$ 号槽中是否有食物？”的问题（$1\le m\le100,1\le k\le n$）。

请你帮忙求出哪几个槽中有食物。




## 说明/提示

### 样例解释
四个序列分别表示如下对话：

1. 问：在第一个槽中有多少个槽里有食物？——答：$1$ 个。
2. 问：在第二个和第三个槽中有多少个槽里有食物？——答：$1$ 个。
3. 问：在第一个和第四个槽中有多少个槽里有食物？——答：$1$ 个。
4. 问：在第三个和第四个槽中有多少个槽里有食物？——答：$1$ 个。

从第一个问题可以知道，第一个槽是有食物的。

从第三个问题可以知道，第四个槽是没有食物的。

从第四个问题可以知道，第三个槽是有食物的。

从第二个问题可以知道，第二个槽是没有食物的。

## 样例 #1

### 输入

```
4 4 
1000 1 
0110 1 
1001 1 
0011 1 
```

### 输出

```
1010 
```

# 题解

## 作者：Mobius127 (赞：4)

[传送门](https://www.luogu.com.cn/problem/P3005)

[$link$](https://www.luogu.com.cn/record/list?pid=P3005&user=341102)

什么叫暴力出奇迹啊(狗头

看到$N \leqslant20$ 直接暴力$Food$ $Filled$，填完之后$O(nm)$检查是否可行即可。

## 主程序：

```
void dfs(int k){
	if(k>n){
		bool flag=true;
		int s=0;
		for(int i=1; i<=m; i++){
			s=0;
			for(int j=1; j<=n; j++){
				if(str[i][j]=='1'){
					s+=u[j];
				} 
			}
			if(s!=sum[i]) flag=false;
		}
		if(flag){
			ans++;
			for(int i=1; i<=n; i++) Ans[i]=u[i];
		} 
		return ;
	}
	dfs(k+1);u[k]=1;dfs(k+1);u[k]=0;
} 
```

交完仔细分析，欸这复杂度不对啊。

$O(2^n*nm)=O(2^{20}*20*100)> O(10^{9})$ 妥妥的超时。

~~bfs~~思考了一会儿后，找到了这个东西：

```
exit(0);
```

能直接结束整个程序的运行。

### 好东西啊！

可还是超时了。~~别打~~

思考剪枝，只要有1个不符合匹配，就可以直接$break$。

于是复杂度就大大降低了。

## AC Code:

```cpp
#include <stdio.h>
#include <algorithm>
#define N 1005
using namespace std;
int n, m, u[N], ans, Ans[N];
char str[N][N];int sum[N];
void dfs(int k){
	if(k>n){
		bool flag=true;
		int s=0;
		for(int i=1; i<=m; i++){
			s=0;
			for(int j=1; j<=n; j++){
				if(str[i][j]=='1'){
					s+=u[j];
				} 
			}
			if(s!=sum[i]){
				flag=false;
				break;
			} 
		}
		if(flag){
			ans++;
			if(ans>1){
				printf("NOT UNIQUE");
				exit(0);
			}
			for(int i=1; i<=n; i++) Ans[i]=u[i];
		} 
		return ;
	}
	dfs(k+1);u[k]=1;dfs(k+1);u[k]=0;
} 
int main(){
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; i++) scanf("%s%d", str[i]+1, &sum[i]);
	dfs(1);
	if(ans==0) printf("IMPOSSIBLE");
	else for(int i=1; i<=n; i++) printf("%d", Ans[i]);
	return o;
} 
```


---

## 作者：brealid (赞：1)

什么是 C++ 的精髓？
1. 是面向对象
2. 是指针
3. 是完善的各种库函数

那么我们今天的主角是：库函数 ``__builtin_popcount``

## 读题 · 方法
初读题，看见 $n\le20$，你想起了什么？  
我想起的是状态压缩。

这题的 $n\le20$ 还让你想到了什么？  
$\Theta(2^n)$ 的枚举是不会超时的。

（所以从数据范围上可以容易猜出算法）

### Part 1 状态压缩

题目所给的形式很好进行状态压缩。  
然后，为防各种换行的奇怪问题，我没有使用 ``getchar()``，而选用了这种读入方式：
```cpp
char str[20 + 7];
for (int i = 1; i <= m; i++) {
    scanf("%s", str);
    cnt[i] = read<int>();
    for (int j = 0; j < n; j++) 
        if (str[j] & 1) type[i] |= (1 << j);
}
```
熟悉位运算的同学应该很容易看懂。  
不熟悉的……右转百度搜索“状压DP”

### Part 2 模板函数 ``__builtin_popcount``

这个函数的作用，是计算出 ``__builtin_popcount(x)`` 中 ``x`` 在二进制下 ``1`` 的位数。  
基层实现：将一个 ``unsigned int(32 bit)`` 拆成 4 个 ``8 bit`` 然后 $O(1)$ 查表（这个表大小为 $2^8$）  

在本题中，``__builtin_popcount`` 有什么妙用？  

#### Part 2.1 奇奇怪怪的位运算
首先假设现在状态枚举到了 $i$ （$i$ 经过二进制压缩），正在检验第 $j$ 条限制条件，该限制条件表示对于状态为 $type[j]$ 的情况，其中有 $cnt[j]$ 个槽装了草。  
那么，有一个很妙的东西就出现了。  
若 ``__builtin_popcount(i & type[j]) == cnt[j]`` 则该条限制条件得到满足。  
这个东西很难用语言解释，意会即可。

## 代码
```
// 已省去不必要的代码
#include <需要的文件>
// read : 快读函数
// read<int> : 读入一个 int 型整数

#define bitCount(x) __builtin_popcount(x)

int n, m;
char str[27];
int type[107], cnt[107];
bool fail, succeeded = false;
int success_status;

int main()
{
    n = read<int>();
    m = read<int>();
    for (int i = 1; i <= m; i++) {
        scanf("%s", str);
        cnt[i] = read<int>();
        for (int j = 0; j < n; j++) 
            if (str[j] & 1) type[i] |= (1 << j);
    }
    for (int i = 0; i < (1 << n); i++) {
        fail = false;
        for (int j = 1; j <= m; j++) {
            if (bitCount(i & type[j]) != cnt[j]) {
                fail = true;
                break;
            }
        }
        if (!fail) {
            if (succeeded) {
                puts("NOT UNIQUE");
                return 0;
            }
            succeeded = true;
            success_status = i;
        }
    }
    if (!succeeded) puts("IMPOSSIBLE");
    else for (int i = 0; i < n; i++) 
        putchar((success_status & (1 << i)) ? '1' : '0');
    putchar(10);
    return 0;
}
```

最后说一句，实际上这个算法的复杂度 $\Theta(2^nm)≈10^8$ 是不太对的，正解可能更优秀。但是题目的特性注定这道题目不会跑满复杂度。  
（尤指 $1\dots m$ 的枚举检验）  
还有，``__builtin_popcount`` 的复杂度是 $O(1)$，但常数较大，大约为 $4$ 。  
不过这个值还是比其他 STL 的常数要小得多了。

---

## 作者：万万没想到 (赞：1)

[原题传送门：P3005 [USACO10DEC]槽的游戏The Trough Game](https://www.luogu.com.cn/problem/P3005)

题目大意：

给出 $n$ 个元素，每个元素可以是 $0$ 或 $1$，有 $m$ 个限制条件，每个限制条件对第$1-n$个元素赋值，第 $i$ 个元素若为 $1$ 表示此限制条件包含第 $i$ 个元素，同时给出 $w_i$ 表示此条件中为 $1$ 的元素真正为 $1$ 的个数。

如果满足方案的唯一性，输出方案具体内容，如果不唯一，输出NOT UNIQUE，如果不存在方案，输出IMPOSSIBLE。

数据范围：
- $1 \leq n \leq 20,1 \leq m \leq 100$

题目思考过程：

看到题目中的小数据，首先必定是穷举，枚举每一个元素的 $0$ 或 $1$ ，再对每一种情况进行每一位暴力判断，是否满足情况。如果不满足情况，立刻退出，如果对所有限制条件都满足情况，进行答案计数。遍历完所有情况后，判断方案的存在性、唯一性，时间复杂度为 $O(2^nnm)$ ，理论上是会超时的，不排除数据过小的情况。

接下来改进穷举，看到 $n \leq 20$ 这个小范围的数据，我们会想到状态压缩，因为同时每个元素只可能是 $0$ 或 $1$ ，所以将每一个元素的状态压成二进制下的一位，将 $n$ 个元素的每一个状态压成不同的二进制数，预处理出每一个数二进制下 $1$ 的个数，再对初识的 $m$ 个限制条件状态压缩，穷举判断即可。时间复杂度为 $O(2^nm)$ ，理论上可以通过本题。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,val[1100005],w[105],war[105],print[105],len,ans;
string s;
inline void dfs(register int size,register int num,register int position){
	if(position>=n){
		val[num]=size;
		return;
	}
	dfs(size,num,position+1);
	dfs(size+1,num+(1<<position),position+1);
}
int main(){
	cin>>n>>m;
	for(register int i=1;i<=n;++i){
		cin>>s>>w[i];
		for(register int j=0;j<s.size();++j){
			if(s[j]=='1')war[i]=war[i]+(1<<(n-j-1));
		}
	}
	dfs(0,0,0);
	len=(1<<n)-1;
	register int temp=0;
	for(register int i=0;i<=len;++i){
		temp=1;
		for(register int j=1;j<=m;++j){
			if(val[i&war[j]]!=w[j]){
				temp=0;
				break;
			}
		}
		if(temp){
			temp=i;
			for(register int j=1;j<=n;++j){
				print[j]=(temp&1);
				temp>>=1;
			}
			++ans;
			if(ans>1){
				cout<<"NOT UNIQUE"<<endl;
				return 0;
			}
		}
	}
	if(ans==1){
		for(register int i=n;i>=1;--i){
			cout<<print[i];
		}
		cout<<endl;
		return 0;
	}
	cout<<"IMPOSSIBLE"<<endl;
	return 0;
}
```


---

## 作者：Zory (赞：1)

那个，推广一下个人网站。。http://zory.cf/2017-12/槽的游戏.html


## 来源和评测点

USACO10DEC Gold


[Luogu3005](https://daniu.luogu.org/problemnew/show/3005)

## 题目

**【题目大意】**

农夫约翰在谷仓里藏起来了N（1<=N<=20）个槽，并且他已经把其中的一些装上了食物。

贝西以“在这个表里（表由贝西提供）有多少个槽里有食物？”的形式

问了M（1<=M<=100）个问题。现在，贝西想知道，哪几个槽里有食物？

**【输入格式】**

第一行是N、M

后面M行，

每行一个长度为N的01串，表示一个询问是否包含这个槽

然后是一个数字，表示回答

**【输出格式】**

如果可行，输出长度为N的01串，表示槽的状态

如果没有满足的方案，输出'IMPOSSIBLE'

如果方案不唯一，输出'NOT UNIQUE'

**【输入样例】**

4 4
1000 1
0110 1
1001 1
0011 1
**【输出样例】**

1010

## 分析1

这题一看数据输入输出就想到矩阵乘法

提问（m×n）（只有0、1）

真实（n×1）（只有0、1）

回答（m×1）

假如提问\*真实=回答，则可行，

然后暴力搜索枚举出真实状况，然而这只能拿60分


## 代码1

这是TLE的，供参考

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct matrix
{
    int row,col;
    int a[120][120];
    matrix()
    {
        memset(a,0,sizeof(a));
    }
};
matrix cheng(matrix a,matrix b)
{
    matrix c;
    c.row=a.row;c.col=b.col;
    for(int i=1;i<=c.row;i++)
        for(int j=1;j<=c.col;j++)
            for(int k=1;k<=a.col;k++)
                c.a[i][j]+=a.a[i][k]*b.a[k][j];
    return c;
}
bool same(matrix a,matrix b)
{
    if(a.row!=b.row) return 0;
    if(a.col!=b.col) return 0;
    for(int i=1;i<=a.row;i++)
        for(int j=1;j<=a.col;j++)
            if(a.a[i][j]!=b.a[i][j])
                return 0;
    return 1;
}
int n,m;
matrix a,b,c,d,ans;
bool ero;
void dfs(int x)
{
    if(ero) return;
    if(x>n)
    {
        d=cheng(a,b);
        if(same(c,d))
        {
            if(ans.row>0) ero=1;
            else ans=b;
        }
        return;
    }
    b.a[x][1]=0;dfs(x+1);
    b.a[x][1]=1;dfs(x+1);
}
char s[30];
int main()
{
    ero=0;
    
    scanf("%d%d",&n,&m);
    a.row=m;a.col=n;
    b.row=n;b.col=1;
    c.row=m;c.col=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=n;j++) a.a[i][j]=s[j]-'0';
        scanf("%d",&c.a[i][1]);
    }
    dfs(1);
    if(ero) printf("NOT UNIQUE");
    else if(ans.row==0) printf("IMPOSSIBLE");
    else for(int i=1;i<=n;i++) printf("%d",ans.a[i][1]);
}
```

## 分析2

接下来考虑剪枝：

根据提问中最后一个需要的槽状态排序

（所以一旦决定了那个槽，就能验证是否满足这个提问），

从而边枚举边乘，达到剪枝目的


注意因为排序内容比较多，我手写了一个二分排序


A了之后忽然想到

可以预处理出每添加一个槽状态所能多判断的提问区间，

每次判断哪些区间的提问就好了，这样时间复杂度会少非常多。

然而我懒得改了，所以代码里面是从1到最后的


至于什么高斯消元……并不会


## 代码2

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int a[110][30],b[30],c[110];
int lt[110];//提问需要最末尾槽状态

int ans[30];bool ha=0;

bool ero;
bool cheng(int x)//被我改良后的矩阵乘法，x是确定了的槽编号
{
    int i=1;
    while(lt[i]<=x and i<=m)//区间限制
    {
        int t=0;
        for(int k=1;k<=x;k++) t+=a[i][k]*b[k];
        if(t!=c[i]) return 0;
        i++;
    }
    return 1;
}
void dfs(int x)
{
    if(ero) return;//多个答案
    if(x>1 and !cheng(x-1)) return;//边做边判断
    if(x>n)
    {
        if(ha>0) ero=1;
        else {memcpy(ans,b,sizeof(b));ha=1;}
        return;
    }
    b[x]=0;dfs(x+1);
    b[x]=1;dfs(x+1);
}
void sort2(int l,int r)//手写二分排序
{
    int x=l,y=r,mid=lt[(l+r)>>1];
    while(x<=y)
    {
        while(lt[x]<mid and x<m) x++;
        while(lt[y]>mid and y>1) y--;
        if(x>y) break;
        swap(lt[x],lt[y]);//都要交换
        swap(a[x],a[y]);
        swap(c[x],c[y]);
        x++;y--;
    }
    if(l<y) sort2(l,y);
    if(x<r) sort2(x,r);
}
char s[30];
int main()
{
    ero=0;
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=n;j++)
        {
            a[i][j]=s[j]-'0';
            if(a[i][j]==1) lt[i]=j;//记录
        }
        scanf("%d",&c[i]);
    }
    
    sort2(1,m);
    dfs(1);
    
    if(ero) printf("NOT UNIQUE");
    else if(ha==0) printf("IMPOSSIBLE");
    else for(int i=1;i<=n;i++) printf("%d",ans[i]);
}
```

---

## 作者：D10s (赞：1)

主要思路其实就是爆搜，不过剪枝方法也算挺好（xuan）玩（xue）的……

将表中的一个个询问看做二进制数储存并排序，然后枚举第x位为零或为一。

容易想到，当判断到x位时，前x-1位必定满足条件限制，而涉及x+1及之后的询问又无法判断，所以只需要判断“询问的最大编号恰为x的询问”是否满足即可（排序就是这个用途）。

不知道是剪枝强还是数据比较水，剪完之后本站24ms大牛12ms，大概是目前跑的最快的了。（毕竟还是naive逃）

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
struct que{
    int range,val;
    friend bool operator <(que a,que b) {return a.range<b.range;}
}q[105];
int a[25],ans[25],n,m;
int calc(int x)
{
    int ret=0;
    for(int i=1;x;i++,x/=2)
    if(a[i]&&(x&1)) ret++;
    return ret;
}
int pd(int x)
{
    for(int i=1;i<=m;i++)
    {
        if(q[i].range<(1<<(x-1))) continue;
        if(q[i].range>=(1<<x)) break;
        if(calc(q[i].range)!=q[i].val) return 0;
    }
    return 1;
}
void search(int x)
{
    if(!pd(x-1)) return;
    if(x>n)
    {
        if(ans[1]!=-1) {printf("NOT UNIQUE\n");exit(0);}
        memcpy(ans,a,sizeof(ans));
        return;
    }
    a[x]=0;search(x+1);
    a[x]=1;search(x+1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        string s;
        cin>>s;
        int t=0;
        for(int j=0;j<n;j++) t=t*2+s[j]-'0';
        q[i].range=t;
        cin>>q[i].val;
    }
    memset(ans,-1,sizeof(ans));
    sort(q+1,q+m+1);
    search(1);
    if(ans[1]==-1) printf("IMPOSSIBLE");
    else for(int i=n;i;i--) printf("%d",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：rechenz (赞：0)

首先看到这道题的数据范围就可以想到是枚举暴力。

而对于枚举我们有两种方法，一种是 $\texttt {DFS}$，而另一种是通过二进制来进行枚举（~~反正我用的 $\texttt {DFS}$~~）。

而这题有两种情况的翻译并没有给出，一种是无解输出 $\texttt{IMPOSSIBLE}$，另一种是解法不唯一输出 $\texttt {NOT UNIQUE}$。

而对于 $\texttt{IMPOSSIBLE}$ 我们只需要判断 $\texttt {DFS}$ 后是否找到了一种解就好了。

对于 $\texttt {NOT UNIQUE}$ 情况我们也只需要在判断是否找到了不唯一的合法解就可以了。

复杂度 ${\rm O}(2^{n}m)$，不完全估计 ${\rm O}(104857600)$，$\texttt{1s}$ 肯定是能过的啦。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,t[25],ans[25];
bool flag=false,judge;
struct Query{
    int a[25];
    int num;
}q[105];

bool check(){//判断解是否合法的函数
    for(int i=1;i<=m;i++){
        int temp=0;
        for(int j=1;j<=n;j++){
            if(q[i].a[j]&&t[j]){
                temp++;//记录搜到的结果的有草料的个数
            }
        }
        if(temp!=q[i].num){//不符合条件直接返回
            return false;
        }
    }
    for(int i=1;i<=n;i++){
        ans[i]=t[i];
    }
    if(flag==true){//是否有过合法解
        judge=true;
    }
    return true;
}

void DFS(int dep){
    if(dep==n){//搜完n个就检查是否合法
        if(check()){
            flag=true;
        }
        return;
    }
    t[dep+1]=1;//枚举每一种情况
    DFS(dep+1);
    // if(flag) return;
    t[dep+1]=0;
    DFS(dep+1);
    // if(flag) return;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            char s;
            cin>>s;
            if(s==' '||s=='\n'){//防止玄学字符串出锅
                j--;
                continue;
            }
            q[i].a[j]=s-'0';
        }
        scanf("%d",&q[i].num);
    }
    //搜索
    t[1]=1;
    DFS(1);
    t[1]=0;
    DFS(1);
    if(!flag){
        printf("IMPOSSIBLE");
        return 0;
    }
    if(judge){
        printf("NOT UNIQUE");
        return 0;
    }
    for(int i=1;i<=n;i++){
        printf("%d",ans[i]);
    }
    return 0;
}
```


---

## 作者：dingshengyang (赞：0)

- $\text{step -1：为什么做这题}$

  因为看到了 @happydef 的博客，说这题可以暴力碾标算。

  然而我的做法与他的不同（我没用 dfs）。

- $\text{step 0：读题+猜测算法}$

  $\because n  \le 20$

  $\therefore$ 算法大概为状态压缩动态规划或状态压缩或爆搜。

  然而这题跟 DP 很明显没半毛钱关系。

  爆搜似乎也不好做。


  果断——状态压缩！

- $\text{step 1：状态定义}$
  
  **本题解中，为了方便，自动将题面中的 $[1,n]$ 区间偏移置 $[0,n-1]$ 区间！！！**

  如果这一位有食物，令二进制下这一位为 $1$，否则为 $0$。

- $\text{step 2：判断是否合法}$

  对于每一次给出的条件，累加题目中所有 $1$ 的位的实际食物个数（有点绕，见下数学 $\text{LaTex}$ 公式）。

  令：上面那个绕来绕去的东西为 $C$；题目中的条件为二进制集合 $subset$，$0$ 表示没有在集合中，$1$ 表示有，当前准备判断是否合法的方案集合为 $set$；集合的第 $i$ 位用 $\text{xxx}_i$ 表示（为 $0$ 或 $1$），其中 $\text{xxx}$ 是集合名称。

  则：$C=\sum_{i\in subset}set_i$。

  如果 $C$ 与 Farmer John 给出的答案不同，说明这个方案不可信，应该筛掉。

  然而，时间复杂度：$O(2^nnm)$，危险。

  然后加上一些玄学优化（在候选集合中删掉被筛去的答案），然后就跑不满，然后就过了。
```cpp
  #include<bits/stdc++.h>
using namespace std;
set<int> possible;
int n,m;
int main(){
    cin >> n >> m;
    for(int i = 0;i < 1<<n;i ++){
        possible.insert(i);
    }
    while(m --){
        string str;
        int c;
        cin >> str >> c;
        vector<int> killer;
        for(auto x:possible){
            int C = 0;
            for(int i = 0;i < n;i ++){
                if(str[i] == '1'){
                    C += (x>>i)&1;
                }
            }
            if(c != C){
                killer.push_back(x);
            }
        }
        for(auto x:killer){
            possible.erase(x);
        }
    }
    if(possible.empty()){
        cout << "IMPOSSIBLE" << endl;
    }else if(possible.size()>1){
        cout << "NOT UNIQUE" << endl;
    }else{
        for(int i = 0;i < n;i ++){
            if(((*possible.begin())>>i)&1){
                cout << "1";
            }else{
                cout << "0";
            }
        }
        cout << endl;
    }
    return 0;
}
```

~~change log：眼瞎忘记换行了。~~

---

## 作者：aSunnyDay (赞：0)

LaTeX fixed.

~~随便跑的居然上了最优解~~

这题暴力比高斯消元法都要快，但是如果数据一大，还是奉劝各位用消元法，或者使用线性基。

剪枝：

如果已经不满足某些询问的要求的话，就直接退出。

我只采用了：若当前的状态超过了某些询问所规定的值外，就退出。

实际上还有一些剪枝方法，比如说，计算第 $i$ 个询问在第 $j$ 个槽以后还有几个会被算进去的槽。如果后面的这些槽全都填还是不能满足要求，就可以剪掉了。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=109;
ll n,m,now[N],b[N],a[N][N],ans[N],cnt=0,lst[N];//now[i]指到pos为止，第i行所指示的槽里有多少个食物 
bool ok(){
	for(ll i=1;i<=m;++i) if(now[i]^b[i]) return 0;
	return 1;
}
void dfs(ll pos){//pos代表要填的位置
	if(pos==n+1){
		if(ok()){
			for(ll i=1;i<=n;++i) lst[i]=ans[i];
			++cnt;
		}
		return;
	}
	dfs(pos+1);//啥也不填
	ans[pos]=1;
	bool ok=1; 
	for(ll i=1;i<=m;++i){
		if(a[i][pos]) ++now[i];
		if(now[i]>b[i]&&ok)
			ok=0;
	}
	if(!ok){
		for(ll i=1;i<=m;++i)
			if(a[i][pos]) --now[i];
		ans[pos]=0;
		return;
	}
	dfs(pos+1);
	ans[pos]=0;
	for(ll i=1;i<=m;++i)
		if(a[i][pos]) --now[i];
}
int main(){
	cin>>n>>m;
	for(ll i=1;i<=m;++i){
		for(ll j=1;j<=n;++j){
			char c;
			cin>>c;
			a[i][j]=(c^48);
		}
		cin>>b[i];
	}
	dfs(1);
	if(!cnt) cout<<"IMPOSSIBLE";
	else if(cnt-1)cout<<"NOT UNIQUE";
	else
		for(ll i=1;i<=n;++i)
			cout<<lst[i];
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

这题是一道很好的搜索剪枝题。

暴力搜索 $n$ 个槽的状态，对于每一种状态，我们判定当前状态跟 $m$ 个条件是否合法，并记录合法的状态和状态数。

时间复杂度： $O(2^nnm)$ 。

这样的复杂度显然会是超时的，我们需要加上以下剪枝：

$1.$ 对于每一种状态，如果已经找到不满足的条件，直接退出循环。

$2.$ 如果当前合法状态数大于等于 $2$ ，则直接结束搜索。

这样就可以通过本题。

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[21],q[101][21],s[101],ans[21],top;
char ch;
bool check()
{
	for(int i=1;i<=m;i++){
		int cnt=0;
		for(int j=1;j<=n;j++) if(q[i][j]) cnt+=a[j];
		if(cnt!=s[i]) return false;
	}
	return true;
}
void dfs(int now)
{
	if(top==2) return;
	if(now==n+1){
		if(check()){
			top++;
			if(top==1) for(int i=1;i<=n;i++) ans[i]=a[i];
		}
		return;
	}
	a[now]=1;
	dfs(now+1);
	a[now]=0;
	dfs(now+1);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>ch;
			q[i][j]=ch-'0';
		}
		cin>>s[i];
	}
	dfs(1);
	if(top==1) for(int i=1;i<=n;i++) cout<<ans[i];
	else if(!top) cout<<"IMPOSSIBLE";
	else cout<<"NOT UNIQUE"; 
	return 0;
}
```

---

## 作者：lytqwq (赞：0)

### 大师法（DFS）+剪枝即可

~~然鹅我发现我跑的还行，也许不用剪枝？~~

爆搜思路：对每个槽有没有食物进行DFS，然后最后判断满不满足贝西提的所有问题的答案。

然后我想了两个剪枝：

1.取每个问题的最后一个1，当dfs到这里的时候判断前面能不能让答案正确。

2.当dfs时如果想让这个槽有食物，看看会不会让任意一个问题答案过大


虽然思路很好想，但代码还是有点多的 ~~（码风问题？）~~：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 21
#define M 101
int n,m;
int a[M],b[M],c[M];
int sum,ans[N],otans[N];
int flag=0;
vector<int> qwq[N];
void dfs(int x)
{
	if(sum>=2)
	{
		return ;
	}
	if(x==n+1)
	{
		for(int i=1;i<=m;i++)
		{
			if(b[i]==a[i])
			{
				
			}
			else
			{
				return ;
			}
		}
		sum++;
		for(int i=1;i<=n;i++)
		{
			otans[i]=ans[i];
		}
		return ;
	}
	int ok=1,ok2=1;
	for(int i=0;i<qwq[x].size();i++)
	{
		b[qwq[x][i]]++;
		if(a[qwq[x][i]]<b[qwq[x][i]])
		{
			ok=0;
		}
	}
	if(ok==0)
	{
		for(int i=0;i<qwq[x].size();i++)
		{
			b[qwq[x][i]]--;
			if(c[qwq[x][i]]==x&&b[qwq[x][i]]!=a[qwq[x][i]])
			{
				ok2=0;
			}
		}
		if(ok2==1)
		{
			ans[x]=0;
			dfs(x+1);	
		}
		
	}
	else
	{
		ans[x]=1;
		dfs(x+1);
		for(int i=0;i<qwq[x].size();i++)
		{
			b[qwq[x][i]]--;
			if(c[qwq[x][i]]==x&&b[qwq[x][i]]!=a[qwq[x][i]])
			{
				ok2=0;
			}
		}
		if(ok2==1)
		{
			ans[x]=0;
			dfs(x+1);	
		}
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	char ch;
	for(int i=1;i<=m;i++)
	{
		for(int o=1;o<=n;o++)
		{
			cin>>ch;
			if(ch=='1')
			{
				qwq[o].push_back(i);
				c[i]=o;
			}
		}
		
		scanf("%d",&a[i]);
	}
	dfs(1);
	if(sum==1)
	{
		for(int i=1;i<=n;i++)
		{
			printf("%d",otans[i]);
		}
		printf("\n");
	}
	if(sum>=2)
	{
		printf("NOT UNIQUE\n");
	}
	if(sum==0)
	{
		printf("IMPOSSIBLE\n");
	}
}
/*
5 1
00000 1

*/
```



---

## 作者：45dino (赞：0)

槽的游戏……听起来很神奇的亚子。

这题的难度最多绿，不可能是蓝。

考虑枚举 $n$ 个槽食物的分布情况（状压成 $n$ 位的二进制数），对于每一种情况，计算是否满足这 $m$ 个要求。

复杂度为 $O(2^n\times m)$ 。

可以用位运算实现进行计算，学过状压DP的小朋友应该很熟悉位运算。

关键代码：
```
	for(int i=0;i<(1<<n);i++)//枚举所有情况
	{
		bool flag=0;//表示能否都通过
		for(int l=1;l<=m;l++)
		{
			int tot=0;
			for(int j=0;j<que[l].size();j++)
				if((1<<(n-que[l][j]))&i)//que[i]存的是第i个问题和哪些槽有关
					tot++;//tot求和
			if(tot!=res[l])
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			if(ans!=-1)//如果这不是第一个满足条件的话，即不止一种情况满足条件。
			{
				cout<<"NOT UNIQUE";
				return 0;
			}
			ans=i;	
		}
	}
```

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> que[101];
int n,m,ans=-1,res[101];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		string s;
		cin>>s;
		for(int l=0;l<s.size();l++)
			if(s[l]=='1')
				que[i].push_back(l+1);
		int x;
		scanf("%d",&x);
		res[i]=x;
	}
	for(int i=0;i<(1<<n);i++)
	{
		bool flag=0;
		for(int l=1;l<=m;l++)
		{
			int tot=0;
			for(int j=0;j<que[l].size();j++)
				if((1<<(n-que[l][j]))&i)
					tot++;
			if(tot!=res[l])
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			if(ans!=-1)
			{
				cout<<"NOT UNIQUE";
				return 0;
			}
			ans=i;	
		}
	}
	if(ans==-1)
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	for(int i=n-1;i>=0;i--)
		if(ans&(1<<(i)))
			cout<<1;
		else
			cout<<0;
} 
```


---

## 作者：Starria的脑残粉 (赞：0)

对不起我拉低了这题的通过率qnq。。。

开始想打一个高斯消元，，然后细节好多啊

就开心的去打爆搜了

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[2000000],a[1000],b[1000],sum;
bool kk;
char c;
bool pd(int y){
        bool ff=true,fk=true;
        for (int i=1;i<=m;i++){
            ff&=(f[a[i]&y]==b[i]);
            fk&=(f[a[i]&y]<=b[i]);
        }if (ff){
            if (sum!=y&&kk){cout<<"NOT UNIQUE"<<endl;exit(0);}//搜到两个的话，，
            kk=true;sum=y;
        }
        if (fk)return true;else return false;
    }
inline void dfs(int x,int y){
    if (x==n){pd(y);return;}
    dfs(x+1,y);
    if (pd(y+(1<<x)))dfs(x+1,y+(1<<x));
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;for (int i=1;i<=1<<20;i++)f[i]=f[i-(i&(-i))]+1;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++)cin>>c,a[i]=a[i]*2+c-'0';//状压
        cin>>b[i]; 
    }dfs(0,0);if (!kk){cout<<"IMPOSSIBLE"<<endl;return 0;}//搜不到。。
    for (int i=n-1;i>=0;i--)
        if (sum&(1<<i))cout<<'1';else cout<<'0';
}
```

---

