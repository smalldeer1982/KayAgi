# Oath of the Night's Watch

## 题目描述

### 简要翻译

- 给定 $n$ 个非负整数 $a_{1 \ldots n}$。
- 你需要求出有多少个 $a_i$，满足：存在正整数 $j, k$，使得 $a_j < a_i$ 且 $a_k > a_i$。
- $1 \leqslant n \leqslant 10^5$；$\forall 1 \leqslant i \leqslant n$，有 $0 \leqslant a_i \leqslant 10^9$。


“长夜将至，我从今开始守望，至死方休。我将不娶妻，不封地，不生子。我将不戴宝冠，不争荣宠。我将尽忠职守，生死于斯。我是黑暗中的利剑，长城上的守卫，抵御寒冷的烈焰，破晓时分的光线，唤醒眠者的号角，守护王国的坚盾。我将生命与荣耀献给守夜人，今夜如此，夜夜皆然。”——《守夜人誓言》

琼恩·雪诺的守夜开始了。他被派去守护管家。

这次他需要守护 $n$ 个管家。每个管家都有他自己的力量值 $a$。琼恩喜欢守护一个管家，当且仅当存在至少一个力量值严格小于这个管家的管家，且存在至少一个力量值严格大于这个管家的管家。

你知道琼恩喜欢守护多少管家吗？

## 说明/提示

#### 样例解释

- 样例 $1$ 解释：琼恩既不喜欢守护力量值为 $1$ 的管家，也不愿意守护力量值为 $5$ 的管家；因为没有任何一个管家的力量值小于 $1$，也没有任何一个管家的力量值大于 $5$。
- 样例 $2$ 解释：琼恩喜欢守护力量值为 $2$ 的管家，因为既有力量值小于 $2$ 的管家，也有力量值大于 $2$ 的管家。


- $1 \leqslant n \leqslant 10^5$。
- $\forall 1 \leqslant i \leqslant n,0 \leqslant a_i \leqslant 10^9$。

## 样例 #1

### 输入

```
2
1 5
```

### 输出

```
0```

## 样例 #2

### 输入

```
3
1 2 5
```

### 输出

```
1```

# 题解

## 作者：_xbn (赞：3)

一句话题意：求给定数列中既不是最小值也不是最大值的数的个数。

对此，我们只要先遍历一遍序列，求出它的最大最小值，再遍历一遍，把等于最大或最小值的数减去即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100002;
int n,m,k,p,q=0x7fffffff,ans,sun,tot,cnt,a[N],b[N],c[N];
int main()
{
	cin>>n;
	ans=n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		p=max(p,a[i]);
		q=min(q,a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==p||a[i]==q)ans--;
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：Houraisan_Kaguya (赞：1)

- 有个很显然的思路：用 $n$ 减去最小值数量与最大值数量之和，即为答案。其他题解空间复杂度均为 $\operatorname O(n)$，但本题有一种空间复杂度 $\operatorname O(1)$ 的做法。

- 考虑求最小值。求最小值的经典方法也是最优秀的方法就是“打擂台”，即：记录一个最小值，遇到比记录最小值更小的数时更新。显然“打擂台”的空间复杂的可以做到 $\operatorname O(1)$。

- 那么考虑在求最小值时记录最小值数量。假设输入流中新输入的数为 $a_{new}$，已知最小值为 $min$。
	- 如果 $a_{new} > min$，过滤掉即可；
    - 如果 $a_{new} = min$，将最小值数量增加 $1$；
    - 如果 $a_{new} < min$，将 $min$ 设为 $a_{new}$，将最小值数量设为 $1$。

- 最大值同理即可。

- 需要注意的一点是：如果最小值与最大值相等，那么就意味着每个数都相等，都被既当成最大值又当成最小值，计算了两遍，所以只减一遍输出即可。

代码：

```cpp
enum Max { A = (unsigned int)1e9 }; enum Inf { Inf = A };
unsigned int inline read(); void const inline write(unsigned int const);
unsigned int const n(read());
unsigned int min(Inf), mincnt(0), max(0), maxcnt(0);

signed int main() {
    for (unsigned int register i(1); i <= n; ++i) {
        unsigned int const a(read());
        if (a <= min) {
            if (a < min) min = a, mincnt = 1;
            else ++mincnt;
        }
        if (a >= max) {
            if (a > max) max = a, maxcnt = 1;
            else ++maxcnt;
        }
    }
    write(n - (min == max ? mincnt : mincnt + maxcnt));
    return 0;
}

# include <cctype>
# include <cstdio>
unsigned int inline read() {
    unsigned char t;
    while (not isdigit(t = getchar()));
    unsigned int r(0);
    while (r = r * 10 + (t - '0'), isdigit(t = getchar()));
    return r;
}
void const inline write(unsigned int const a) {
    unsigned int t(10);
    while (t <= a) t *= 10;
    while (t /= 10) putchar(a / t % 10 + '0');
}
```

---

## 作者：Quit (赞：0)

### 题意简化：

给出一个数列，共有$n$个数。求出其中有多少个数既不是这个数列的最小值，也不是这个数列的最大值。

### 方法：

去掉所有的最大值和最小值，因为它们可能各有多个。最后再出剩下的数有多少个即可。

我们需要先将这个数列。看了一下数据范围，$n$ $∈$ [$1$ , $10^{5}$],  用$sort()$ 函数没问题，时间复杂度为$O(nlogn)$，不会$TLE$，之后将数组的最大值$x_{n}$记为$maxx$，最小值$x_{1}$记为$minx$。$($因为我的数组下标是$1......n$$)$再使用$while$循环分别去重最大值与最小值。

### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[100005],ans,minx,maxx;
int main()
{
	cin>>n;
	ans=n;
	for(int i=1;i<=n;i++)cin>>x[i];
	sort(x+1,x+n+1);//排序
	minx=x[1];	//数列最大值
	maxx=x[n];	//数列最小值
	if(minx==maxx) {
		cout<<0<<endl;
		return 0;
	}   
	//这里需要特判，否则ans可能会是负数
	int l=1,r=n;
	while(x[l]==minx){
		ans--;
		l++;
	}	//最小值去重
	while(x[r]==maxx){
		r--;
		ans--;
	}	//最大值去重
	cout<<ans<<endl;	//输出答案
	return 0;
}
```

谢谢朋友们！

---

## 作者：零殇 (赞：0)

#### 题意：

给你$n$个数据，当存在数据$A<$数据$B$以及数据$A>$数据$C$，我们就说数据$A$是合法的。求有多少个数据合法。

#### 思路

因为一个合法数据必定有大于它的数据和小于它的数据，也就是说，只有最大的数据和最小的数据不合法。

对于最大值和最小值，我用$sort$进行判断。（当然暴力对比也是可以的）。

那么，我们只需要判断一个数据是不是最大值或最小值就好了。如果是，就累加。（当然也可以用$n$减去最大值和最小值的总数）。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
long long a[200000];
int main()
{
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a,a+n+1);
	int maxn=a[n],minn=a[1];//最大值和最小值
    for(int i=1;i<=n;i++)
        if(a[i]!=maxn&&a[i]!=minn)//判断
            ans++;
	cout<<ans;
	return 0;
}
```
完结撒花~


---

## 作者：Colead (赞：0)

# CF768A

这又是一道CF的A题，方法也多种多样，这里给大家介绍两种。

## 1、排序

看到这个数据范围：

$1<=n<=10^5$

一下子就觉得排序是可以过的。

然而由于这个数据也不算很小，所以不是所有的排序都能过。

比如冒泡排序，$O(n^2)$一秒直接超时；

再比如计数排序（不过也没人用这个）：$a[i]$的范围太大。

于是$sort$脱颖而出。

$O(nlogn)$可以考虑。

```
#include<bits/stdc++.h>
using namespace std;
int a[1000005]={};
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,less<int>());
	int tot=0;
	for(int i=2;i<n;i++)
	{
		if(a[i]>a[i-1]&&a[i]<a[i+1])
		  tot++;
	}
	cout<<tot<<endl;
	return 0;
}
```

### WA

仔细分析，发现只要大于最小的，小于最大的即可。

```
#include<bits/stdc++.h>
using namespace std;
int a[1000005]={};
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,less<int>());
	int tot=0;
	for(int i=2;i<n;i++)
	{
		if(a[i]>a[1]&&a[i]<a[n])
		  tot++;
	}
	cout<<tot<<endl;
	return 0;
}
```

### AC

## 2、打擂台求最大

一个更快的算法，扫两遍，先求最大最小，第二遍把所有之间的计数即可。

代码就不放了。

我是WT20071112，再见啦~


---

## 作者：Kalium (赞：0)

# CF768A Oath of the Night's Watch题解

最近打线段树很自闭，刷点水题调养身心

进入正题

## 题意：

$N$ 个数，要求你求出既不是最大也不是最小的数字有几个

## 思路：

真不知道说什么好

用 $maxx$ 表示最大值，$minn$ 表示最小值

然后遍历一遍寻找即可

## 代码：

# CODE：

```cpp
#include <iostream>
#define inf 0x3f3f3f3f

const int N = 1e5 + 7;

using namespace std;

int n, a[N], ans;

int maxx = -inf, minn = inf;

inline int read() {
	int n = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -f;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		n = (n << 3) + (n << 1) + (c ^ '0');
		c = getchar(); 
	}
	return n * f;
}

inline int maxa(int a, int b) {
	if (a > b)
		return a;
	return b;
}

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

int main() {
	n = read();
	for (int i = 1; i <= n; i ++) {
		a[i] = read();
		maxx = maxa(maxx, a[i]);
		minn = mina(minn, a[i]); 
	}
	for (int i = 1; i <= n; i ++) {
		if (a[i] != minn && a[i] != maxx)
			ans ++;
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Forever1507 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF768A)

后缀既然是 $A$ 那么思维难度应当不大，很明显可以分两种思路进行：
1. 打擂台，取得最大及最小值，将最大值和最小值的数量进行统计并用总量相减即可，难度不大

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int maxi=0,mini=1e9;//最大值取最小，最小值取最大
int num=0;//等于最大或最小值的数量
int a[100005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
		cin>>a[i];
   		if(a[i]>maxi)//经典打擂台操作
		   maxi=a[i];
   		if(a[i]<mini)
		   mini=a[i]; 
    }
    for(int i=1;i<=n;i++){
   		if(a[i]==maxi||a[i]==mini)//统计数量
	   		num++; 
    }
   cout<<n-num<<endl; 
   return 0;
} 
```
2. 排序，数据范围为100000，那么只能选取$O(n*logn)$复杂度的排序方法，但是$sort$已经烂大街了，所以我们使用~~稍微高大上一点点的~~平衡树！！！

接下来请熟悉$Treap$的神犇们跳过，直达$Code$

What is 平衡树?

百度上的描述如下：

`平衡树(Balance Tree，BT) 指的是，任意节点的子树的高度差都小于等于1。常见的符合平衡树的有，B树（多路平衡搜索树）、AVL树（二叉平衡搜索树）等。平衡树可以完成集合的一系列操作, 时间复杂度和空间复杂度相对于“2-3树”要低，在完成集合的一系列操作中始终保持平衡，为大型数据库的组织、索引提供了一条新的途径。 
设“2-3 树”的每个结点存放一组与应用问题有关的数据, 且有一个关键字 (>0的整数) 作为标识。关键字的存放规则如下:对于结点X, 设左、中、右子树均不空, 则左子树任一结点的关键字小于中子树中任一结点的关键字;中子树中任一结点的关键字小于结点X的关键字;而X的关键字又小于右子树中任一结点的关键字, 称这样的“2-3树”为平衡树。`

说白了就是利用类似离散化的操作给每一个数据提供一个优先值，存入二叉树（规则如上），再利用中序遍历输出或存储。

那么可以得出$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[100005],sum;
struct node{
    int x,w;//值和优先级 
    struct node *h,*r,*l;//父亲，左儿子，右儿子 
    node(){
        x=0;w=0;h=r=l=NULL;
    }
};
node *root;//根节点 
void zrg(node *u,node *v){
//右旋 
    node *t=u->h;//提出u的父节点 
    u->l=v->r;//u的左儿子是v的右儿子 
    if(v->r!=NULL)v->r->h=u;//v的右儿子的父亲是u 
    u->h=v;//u的父亲是v 
    v->r=u;//v的右儿子是u 
    v->h=t;//v的父亲是原来u的父亲 
    if(t!=NULL){    
        if(t->l==u)t->l=v;
        else t->r=v;
    }//更新父亲节点 
    else root=v;//如果是根节点直接覆盖 
}
void zlg(node *u,node *v){
    node *t=u->h;
    u->r=v->l;
    if(v->l!=NULL)v->l->h=u;
    v->l=u;
    u->h=v;
    v->h=t;
    if(t!=NULL){    
        if(t->l==u)t->l=v;
        else t->r=v;
    }
    else root=v;
}
void out(node *u){
    if(u!=NULL){
        out(u->l);
    	sum++;
        ans[sum]=u->x;
        out(u->r);
    }
    //中序遍历 ，存入数组
}
void insert(node *u,node *v){
    //u是现有的树，从根节点开始插,v是新建的节点 
    if(u==NULL)return;
    if(v->x>u->x){
        //如果数值大于当前节点的数值，那就应该插在它的右边 
        if(u->r==NULL){
            u->r=v;
            v->h=u;
            //插入 
            while(v->h!=NULL && v->w<v->h->w){
                if(v==v->h->r)zlg(v->h,v);
                else zrg(v->h,v);
            }
            //从v当前所在的位置往上找，直到根节点，如果父亲的优先级更大，那就应该旋转，如果v是右儿子就左旋，左儿子就右旋            
        }
        else insert(u->r,v);
        //如果右儿子不为空，就向右儿子插入          
    }else{
        if(u->l==NULL){
            u->l=v;v->h=u;
            while(v->h!=NULL && v->w<v->h->w){
                if(v==v->h->r)zlg(v->h,v);
                else zrg(v->h,v);
            }           
        }else insert(u->l,v);   
    }
}

int main(){
    int i,j,k,m,n,t;
    node *p,*q;
    cin>>n; 
    cin>>k;
    srand(time(0));//随机化，让数据变得“友好”
    root=new node;
    root->x=k;
    root->w=rand();
    for(i=2;i<=n;i++){
        cin>>k;
        q=new node;
        q->x=k;
        q->w=rand();    
        //新建节点，插入节点 
        insert(root,q);         
    }   
    out(root);//存入数组
    int cnt=0;//统计数量
    for(int i=1;i<=n;i++){
    	if(ans[i]==ans[1]||ans[i]==ans[n]){
    		cnt++;
		}
	}
	cout<<n-cnt;
    return 0;
}
```
~~码字不易，留赞再走~~

---

## 作者：123456Mm (赞：0)

 本题可使用“打擂台”的方法先求出最大值和最小值，再算出值最大值和最小值的元素数量num。答案即为总数量减去num。
 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long MAX=0,MIN=pow(10,9);
int num=0;
int main(){
	int n;
	cin>>n;
	long long a[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>MAX)MAX=a[i];
		if(a[i]<MIN)MIN=a[i]; 
	}
	for(int i=1;i<=n;i++){
		if(a[i]==MAX||a[i]==MIN)num++;
		 
	}
	cout<<n-num<<endl; 
	return 0;
} 
```


---

## 作者：sysu_yzc (赞：0)

## 思路
如果$n==1$则输出$0$，否则进行排序。

如果全部数都一样，即$a[0]==a[n-1]$，则输出$0$，

否则将排序后的数组前面相等的数的数量和后面相等的数的数量记为$t$，输出$n-t$。
## 上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010];
int main(){
    int n;
    cin>>n;
    if(n==1){
        cout<<0;
        return 0;
    }
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    if(a[0]==a[n-1]){
        cout<<0;
        return 0;
    }
    int ans=n-2;
    for(int i=1;a[i]==a[i-1];i++) ans--;
    for(int i=n-2;a[i]==a[i+1];i--) ans--;
    cout<<ans;
    return 0;
}
```

---

