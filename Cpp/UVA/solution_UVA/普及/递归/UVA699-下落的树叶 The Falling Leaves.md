# 下落的树叶 The Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=640

[PDF](https://uva.onlinejudge.org/external/6/p699.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/735ce6ad24a18ffc8b70b3a6c28998f5211a95ce.png)

## 样例 #1

### 输入

```
5 7 -1 6 -1 -1 3 -1 -1
8 2 9 -1 -1 6 5 -1 -1 12 -1
-1 3 7 -1 -1 -1
-1```

### 输出

```
Case 1:
7 11 3
Case 2:
9 7 21 15```

# 题解

## 作者：Gary818 (赞：16)

# 作为这道题的资深受害者，是时候交一波题解了 #

## 【分析】 ##

非常明显，这道题考察的是二叉树，那么对于建树的操作，我们要从中间开始向两侧递归。根据题意，总要输入-1这个家伙，那我们对他“特殊照顾”一下就可以啦！  
像这样：
```cpp
void build(int p){ 
    int v;
    cin >> v;
    if(v == -1)return;
    sum[p] += v;
    build(p - 1);
    build(p + 1);   
}
```
非常好，接下来，该进行输入操作了。注意一点，这个二叉树的根节点放在中间是再合适不过了，这样的话，更容易进行数据处理。
like this:
```cpp
bool init(){
    int v;
    cin >> v;
    if(v == -1)return false;
    memset(sum,0,sizeof(sum));    
    int p = maxn/2;            
    sum[p] = v;
    build(p - 1);build(p + 1);   
    return 1;//一定要return 1！！！！！
    //在这里，刘汝佳老师忘记了bool函数的返回值，qwq卡了我好久
}
```
重点都OK了，下面AC代码献上附讲解
## 【标程】 ##
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int sum[maxn];

void build(int p){            //建树不多说
    int v;
    cin >> v;
    if(v == -1)	return;
    sum[p] += v;
    build(p - 1);
    build(p + 1);   
}

bool init(){               //输入
    int v;
    cin >> v;
    if(v == -1)	return false;
    memset(sum,0,sizeof(sum));    
    int p = maxn/2;          //树根的水平位置  
    sum[p] = v;
    build(p - 1);
    build(p + 1);   
    return 1;
}

int main(){
    int kase = 0;
    while(init()){
        int p = 0;
        while(!sum[p]) p++;  //向左找最左边的孩子
        cout << "Case " << ++kase << ':' << endl << sum[p++];
        //避免行末多余空格
        while(sum[p]) cout << " " << sum[p++];
        cout << endl << endl;//UVa的非正常输出2333     
    } 
    return 0;
}
```
我交了大概有几十遍，谢谢这位大佬指点  
@逆流之时 

本蒟蒻的第一篇题解到此结束，请大佬们多多指教，谢谢！


---

## 作者：StayAlone (赞：6)

这道题想清楚写出来超级少。题意是把一棵树的每一列的所有节点上的值相加，从左往右依次输出。  
输入的时候**递归**解决： 

函数 $build(idx)$ 将会：  
1. 输入根，且这个根在第 $idx$ 列 
2. 输入左子树
3. 输入右子树

由于输入时**前序遍历**，因此要以 **"根左右"** 的顺序输入。  
如果输入时遇到$-1$,则直接结束当前函数。

现定义一个 $a$ 数组。$a_i$ 表示第 $i$ 列的所有节点上的值的和。
则在输入过程中，可以直接将输入的根累加到 $a_{idx}$ 中。

我们在最开始调用时，可以使用 $build(1000)$ ，因为会输入左子树，因此这个$1000$必须保证即使所有的节点都在左子树，其列数也不会大于$1000$，也就是节点数量不大于$1000$。~~(其实是因为题目没告诉我们所以瞎写的1000)~~

在输出时，从下标几输出到下标几呢？因此，在函数里，仍然要在写一个 $l$ 和 $r$，在当前**这个节点存在时**，  $l$ 与当前的列数求 $\min$ 值，$r$ 与当前的列数取 $\max$ 值。

```cpp
bool build(int idx)
{
	int x; scanf("%d", &x);
	if (!~x) return false; // !~x 相当于 x == -1，其中~x表示 x != -1
	l = min(l, idx), r = max(r, idx); //这一行不能写到上一行前面，其原因就是因为要保证当前节点存在，否则l会比正常值小1，r会比正常值大1
	a[idx] += x;
	build(idx-1), build(idx+1);
	return true;
}
```

那这里为什么要加一个返回值呢？其实仔细观察会发现，这个返回值**在函数中**没有任何作用，因此这个返回值仅仅是为了判断输出结束的。因为只有**最开始就输入了**$-1$，$build$ 函数才会返回 $\texttt{false}$，也就结束输入。

记得**每次**输出后，**清空**数组 $a$，$l$ 和 $r$ 重新赋值为$1000$。  

[AC code记录](https://www.luogu.com.cn/record/50227260)

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, times, l = 1000, r = 1000, a[3010];

bool build(int idx)
{
	int x; scanf("%d", &x);
	if (!~x) return false;
	l = min(l, idx), r = max(r, idx);
	a[idx] += x;
	build(idx-1), build(idx+1);
	return true;
}

int main()
{
	while (build(1000))
	{
		printf("Case %d:\n", ++times);
		for (int i = l; i < r; ++i) printf("%d ", a[i]), a[i] = 0;
		printf("%d\n\n", a[r]), a[r] = 0;
		l = r = 1000;
	}
	return 0;
}
```


---

## 作者：ICE_Wol (赞：4)

这是一道相当容易的考察树的遍历的题

一边读入一边统计，关键在于对于子树的递归
 
废话不多说直接上代码，具体解析**参见注释**
```c
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100005;
int sum[maxn];
void build(int p){                ///建树的同时分治递归统计
    int v;
    cin >> v;
    if(v == -1)return;
    sum[p] += v;
    build(p - 1);build(p + 1);    ///左右子节点水平位置分别+1 -1
}

bool init(){
    int v;
    cin >> v;
    if(v == -1)return false;
    memset(sum,0,sizeof(sum));    ///清空上一次的数据
    int p = maxn/2;			   ///将正中作为树根
    sum[p] = v;
    build(p - 1);build(p + 1);    ///这样可以一次读一行
}

int main(){
    int kase = 0;
    while(init()){
        int p = 0;
        while(!sum[p]) p++;
        cout << "Case " << ++kase << ':' << endl << sum[p++];
        while(sum[p]) cout << " " << sum[p++];
        cout << endl << endl;     ///uva日常坑输出
    } 
    return 0;
}

```

---

## 作者：Megumi9 (赞：2)

# 题解 UVA699
## 思路：
#### 题意中，树是从上自下的建立的
#### 而输出是从左自右的。
#### 并且，题目中没有对树父子关系的需要
#### 因此，记录每一个结点在树从左自右的位置pos
#### 最后顺序输出pos即可.
## 提示：
#### 1.本题中，输入的是树的中序遍历顺序(根-左-右)，
####  用-1表示叶子
#### 2.注意在多组数据情况下应该memset使用过的数组
#### 3.注意毒瘤输出 
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int num=0;//结点数量 
int sum[100000];
void build(int pos)
{
	int s; 
	scanf("%d",&s);//根 
	if(s==-1)	return ;
	sum[pos]+=s;
	build(pos-1);//左子树 
	build(pos+1);//右子树 
}//建树(中序) 
int main()
{
	int n=0;
	while(++n)
	{
		memset(sum,0,sizeof sum);
		int p=5000;
		scanf("%d",&sum[p]);
		if(sum[p]==-1)	break;//特判 
		++num;		
		build(p-1);
		build(p+1);//建树 
		
		p=0;
		printf("Case %d:\n",n);
		while(!sum[++p]);
		printf("%d",sum[p]);
		while(sum[++p])	printf(" %d",sum[p]);//输出 
		printf("\n\n");
	}
	return 0;
```


---

## 作者：ljcljc (赞：2)

【分析】

很明显考察二叉树的构造，从根节点开始对于每个节点递归遍历其左孩子节点和右孩子节点，若该节点非空，则将此节点的权加到该节点所在列的总权中，这里我们可以巧妙的使用**数组存储**。

要注意的是，我们要将根节点放到中间位置而不是最左端位置，因为列数为0的左孩子的列数为-1，要进行特殊处理，所以**将根节点放在中间**是更为简单的

【AC代码】

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1000010;
int a[MAXN], k;
void build(int p) {
    int x;
    cin >> x;
    if(x == -1) return; //没有孩子就直接退出
    a[p] += x; //加权值
    build(p-1); //左孩子
    build(p+1); //右孩子
}
int main() {
    while(1) {
        int x;
        cin >> x;
        if(x == -1) { //根节点不能为0
            return 0;
        }
        memset(a, 0, sizeof(a));
        int p = MAXN/2; //取中间一个点作为根
        a[p] += x;  //加权值
        build(p-1); //左孩子
        build(p+1); //右孩子
        p = 0;
        //输出
        while (!sum[p])
            p++;
        printf("%d", sum[p++]);
        for (int i = p; sum[i]; i++)
            printf(" %d", sum[i]);
        printf("\n");
        printf("\n");
    }
    return 0;
}
```

---

## 作者：lmz_ (赞：0)

~~UVA 的题真的好卡格式呀。~~

首先我们定义 $p$ 和 $a_p$，$a_p$ 表示 $p$ 位置上的落叶总数，对于每一组输入，我们可以把它看成一棵树的前序遍历，按前序遍历的方式构建图。

对于一个节点 $x$，设 $x$ 的位置在 $p$ 的位置上，那么 $x$ 的左孩子在 $p-1$ 的位置上，右孩子则在 $p+1$ 的位置上。

然后我们就可以写出构造函数：
```cpp
void build(int p){
	int t;
	cin>>t;
	if(t==-1) return;
	sum[p]+=t;
	build(p-1);
	build(p+1);
}
```
我们在构造函数中预处理出`sum`后就可以写出主函数的代码了：
```cpp
int main(){
	int cnt=0;
	while(1){
		memset(sum,0,sizeof(sum));
		build(20000);
		if(sum[20000]==0) break;
		int x=0;
		printf("Case %d:\n",++cnt);
		while(sum[++x]==0);
		int p=x;
		while(sum[p]&&sum[p+1]!=0) cout<<sum[p++]<<' ';
		if(sum[p]) cout<<sum[p];//行末一定不要用空格！！！
		printf("\n\n");//两个换行！！！
	}
	return 0;
}
```
最后，有这几个容易犯的格式错误：

1.行末没有换行。

2.一组数据结束 $2$ 个换行。

---

## 作者：cslover (赞：0)

如果我们把这颗二叉树送左往右分成很多列的话（假设是 $p\sim q$），设每一列的所有层之和为 $sum_i$ ，题目要我们求的就是这个。

利用这个性质，发现：每个节点 $i$ ，就是其父亲节点的左儿子和右儿子；设其父亲节点所处的列是 $j$ ，那么其所属的列数要么是 $j-1$，要么是 $j+1$。

这样一来，就可以通过这样的编号方式去计算 $sum[]$ ，然后每次都可以在 $sum[]$ 中找到的连续的不为 $0$ 的一段 $[p,q]$ 。输出这段的 $sum$ 值就可以。

需要注意：

1. 行末不能有空格；
2. 两组 $\text{Case}$ 之间要有一个空行。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500050;
#define mid MAXN/2
int sum[MAXN];
void build(int p)
{
	int x;
	scanf("%d",&x);
	if(x==-1)return;
	sum[p]+=x;
	build(p-1);build(p+1);
	return ;
}
bool read()
{
	int x;
	scanf("%d",&x);
	if(x==-1)return false;
	memset(sum,0,sizeof(sum));
	sum[mid]+=x;
	build(mid-1);build(mid+1);
	return true;
}
int main()
{
	int t=0;
	while(read())
	{
//		memset(sum,0,sizeof(sum));
		int p=0;
		while(sum[p]==0)++p;
		printf("Case %d:\n%d",++t,sum[p++]);
		while(sum[p]!=0)printf(" %d",sum[p++]);
		puts("");puts("");
	}
	return 0;
}
```

---

## 作者：yoyiETO (赞：0)

思路：如果根节点的位置为$p$,则左子树根节点为$p-1$,右子树为$p+1$.初始化	根节点为$N/2$

定义$s[n]$存储各位置的树叶数量。用先序建树，递归求解。

build函数实现过程(假设参数为$p$)：

1. 每次输入一个先序遍历$r$
2. 如果为空(-1)则```return```
3. 位置$p$数量加$r$
4. 递归$p-1$和$p+1$.

**AC Code:**
```cpp
#include<bits/stdc++.h>//不要抄！！
using namespace std;
int t,r,s[200001];
void build(int p)
{
	cin>>r;
	if(r==-1) return;//空树
    s[p]+=r;
	build(p-1);//处理左子树
	build(p+1);//处理右子树
}
int main()
{
	int t=0;
	while(1)
	{
		memset(s,0,sizeof(s));//初始化
		int p=10000;
		build(p);
		if(!s[p]) break;
		p=0;
		while(s[p]==0) p++;//找最左边的
		cout<<"Case "<<++t<<":\n";
		while(s[p]!=0){
			cout<<s[p]<<' ';
			p++;
		}
		cout<<"\n\n";
	}
	return 0;
}
```

---

