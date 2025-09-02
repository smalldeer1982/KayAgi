# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255```

### 输出

```
1
3
255```

# 题解

## 作者：gcwixsxr (赞：32)

看到这道题没多少题解，
本蒟蒻来凑个热闹

这是一道较为典型的搜索题目

其实思路就是二叉树+深度优先搜索（下面细讲）

#### [题目传送门  QAQ](https://www.luogu.com.cn/problem/UVA548)

### ~~~~~~~ ~~大量文字警告~~ ~~~~~~~


## 先来谈谈概念

![](https://cdn.luogu.com.cn/upload/image_hosting/17u6t0am.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（1）左子树：即根节点以左的子树，比如说A的左子树为BDE（右子树类似）;

（2）左孩子：在根节点左端的孩子，比如说A的左孩子为B（右孩子类似）;

（3）叶节点：没有孩子的节点

（4）根节点：没有父亲的节点

（5）中序遍历数组：按左孩子、根节点、右孩子的顺序遍历树的数组

（5）后序遍历数组：按左孩子、右孩子、根节点的顺序遍历树的数组

## 1.建树的过程 
### （1）先解释一下函数里装的什么东西吧

l1和r1指的是中序遍历数组的起止位置，相应的，l2和r2指的是后序遍历数组的起止位置

### （2）还有函数的大致原理

通过找该树的后序遍历数组的末位来确定根节点，然后再暴力搜寻根节点在中序遍历数组中的位置，根节点以左的就是这棵树的左子树，根节点以右的就是这棵树的右子树，再以这两棵子树的后序遍历数组和中序遍历数组向下递归，如此反复

### （3）实现过程

先来一次特判，如果右边界小于左边界，代表这是叶节点（没有孩子了），将该叶节点的孩子记为-1（即不存在）；然后用root记录这棵树的根节点，用while找根节点在中序遍历数组的位置，将它的左右孩子再次通过递归查找（原理相同）；最后返回值root，即返回根节点的值
```cpp
int build(int l1,int r1,int l2,int r2) {
    if (r1<l1) return -1;//叶节点判断
    int root = post_order[r2]; //记录这棵树的根节点
    int p = l1;  
    while(in_order[p] != root) p++; //根节点在中序遍历数组的位置
    int cnt = p-l1;
    lc[root] = build(l1, p-1, l2, l2+cnt-1); 
    rc[root] = build(p+1, r1, l2+cnt, r2-1);
    return root;//即返回根节点的值
}
```
## 2.深搜的过程
这个较简单，便略说一二

### 实现过程：
u代表当前根节点，sum代表当前的权值

当左右孩子都等于-1时（即为叶节点）,如果sum值比最小权值之和小，或者sum值虽然等于最小权值之和，但当前叶节点的权值小于以前搜索到的最小的叶节点权值，此时，更新最小权值之和以及最小的叶节点权值

然后分别搜索左孩子和右孩子，实现递归
```cpp
void dfs(int u, int sum) { 
    sum += u;//加权值
    if(lc[u]==-1 && rc[u]==-1) { 
        if(sum < _min || (sum == _min && u < ans)) { 
            ans = u; 
            _min = sum; //更新最小权值之和以及最小的叶节点权值
        }
     }
     if(lc[u]!=-1) dfs(lc[u], sum); 
     if(rc[u]!=-1) dfs(rc[u], sum); //然后分别搜索左孩子和右孩子
}
```

## 3.别忘了有多组数据，每次要清空原来的数据

# 下面是AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10000+5;
int n,_min=0x7fffffff,ans;
int lc[N],rc[N]; 
int in_order[N],post_order[N]; 
int build(int l1,int r1,int l2,int r2) {
    if (r1<l1) return -1;
    int root = post_order[r2]; 
    int p = l1;  
    while(in_order[p] != root) p++; 
    int cnt = p-l1;
    lc[root] = build(l1, p-1, l2, l2+cnt-1); 
    rc[root] = build(p+1, r1, l2+cnt, r2-1);
    return root;
}
void dfs(int u, int sum) { 
    sum += u;
    if(lc[u]==-1 && rc[u]==-1) { 
        if(sum < _min || (sum == _min && u < ans)) { 
            ans = u; 
            _min = sum; 
        }
     }
     if(lc[u]!=-1) dfs(lc[u], sum); 
     if(rc[u]!=-1) dfs(rc[u], sum); 
}
signed main(){//主函数
	char a[2];
	int t;char c;
	while(scanf("%d%c",&t,&c)!=-1)//输入
    {
        n=0;
        in_order[0]=t;
        while(c!='\n')scanf("%d%c",&in_order[++n],&c);
        for(int i=0;i<=n;i++)scanf("%d",&post_order[i]);
        build(0,n,0,n);
        dfs(post_order[n],0);
        printf("%d\n",ans);
        memset(in_order,0,sizeof(in_order));
        memset(post_order,0,sizeof(post_order));
        memset(lc,0,sizeof(lc));
        memset(rc,0,sizeof(rc));     
		_min=ans=0x7fffffff;//疯狂清空数据，重置数据   
    }
    return 0;//抄代码不是好习惯;
    
}

```
本蒟写题解用心，点个赞再走吧


---

## 作者：逆流之时 (赞：22)

帮刘汝佳完成递归同时完成统计最优解的代码(比原代码还简单)
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int lc[10010],rc[10010],n,t,zx[10010],hx[10010],idx,best;
char c;
int build(int l1,int r1,int l2,int r2,int sum)
{
	if(l1>r1)return 0;
	int root=hx[r2];
	int p=l1;
	while(zx[p]!=root)p++;
	int len=p-l1;
	sum+=root;//直接统计并递归
	lc[root]=build(l1,p-1,l2,l2+len-1,sum);
	rc[root]=build(p+1,r1,l2+len,r2-1,sum);
	if(!lc[root]&&!rc[root]&&((sum<best)||(sum==best&&root<idx))){best=sum;idx=root;}//直接从自己获取lc[root]与rc[root]与sum
	return root;
}
int main()
{
	while(scanf("%d%c",&t,&c)!=EOF)//一定要有!=EOF，不然很可能TLE
	{
		n=1;
		zx[1]=t;
		while(c!='\n')scanf("%d%c",&zx[++n],&c);
		for(int i=1;i<=n;i++)scanf("%d",&hx[i]);
		idx=best=0x7fffffff;//初始化为最大值
		build(1,n,1,n,0);
		printf("%d\n",idx);
	}
	return 0;
}
```


---

## 作者：星释宇 (赞：8)

唔，首先这题给出了中序遍历和后序遍历要求我们求出，

一个叶子节点到根的数值总和最小，且这个叶子节点是最小的那个

这题的难点在于如何运用中序遍历和后序遍历还原整棵树，

这里有两个方法：

1. 递归构造原树。
1. 运用链表构造一棵树。

我将要运用的是链表构造树。
```cpp
#include<bits/stdc++.h> 

using namespace std;

struct Node{
   int v;
   Node *left,*right;
};//首先利用结构体构造树的节点 

Node *root;//申请根节点 
Node *newnode() {return new Node();}//添加新的节点 

const int inf=0x7fffffff;//设定值最大 
const int maxn=10000+10;
int p[maxn],i[maxn],n,ok,b,best;
 
bool read(int *a)//读入数据，进行存储 
{
    string s;
    if(!getline(cin,s)) return false;//输入进树的节点数 
    stringstream tf(s);
    int x;n=0;
    while(tf>>x) a[n++]=x;
    return n>0;
}
 
Node* bulid(int l1,int r1,int l2,int r2)//构造树的节点 
{
    if(l1>r1) return NULL;//null==空，所以空数返回空 
    Node *t=newnode();//申请节点 
    t->v=p[r2];//运用链表 
    int p=l1;
    while(i[p]!=t->v) p++;//添加子树 
    int cnt=p-l1;
    t->left=bulid(l1,p-1,l2,l2+cnt-1);
    t->right=bulid(p+1,r1,l2+cnt,r2-1);//构造左右子树 
    return t;
}
 
void dfs(Node *t,int sum)//用深搜寻找最小值的终端叶子 
{
    sum+=t->v;
    if(!t->left&&!t->right){//检寻左右子树 
        if(sum<b||(sum==b&&t->v<best)){
              b=sum;best=t->v;
        }
    }
    if(t->left) dfs(t->left,sum);
    if(t->right) dfs(t->right,sum);//搜索回溯 
}
 
int main()
{
    while(read(i)){//输入 
        read(p);
        b=inf;best=inf;
        root=bulid(0,n-1,0,n-1);
        dfs(root,0);//从根节点开始搜 
        printf("%d\n",best);
	}
} 
```

就是这个样子啦！！！

---

## 作者：SkyLines (赞：3)

## Solution

前置知识：[树的遍历](https://oiwiki.com/graph/tree-basic/#%E4%BA%8C%E5%8F%89%E6%A0%91-dfs-%E9%81%8D%E5%8E%86)。

### 建树

显然，后序遍历的最后一个点就是根节点，然后在中序遍历中找到这个位置，左边即为左子树的中序遍历，右边即为右子树的中序遍历，递归左右子树即可。

```cpp
int build(int l1, int r1, int l2, int r2){
	if(r1 < l1) return -1;
	int now = B[r2], tmp = l1;
	while(A[tmp] != now) tmp++;
	edge[now].l = build(l1, tmp - 1, l2, l2 + (tmp - l1) - 1);
	edge[now].r = build(tmp + 1, r1, l2 + (tmp - l1), r2 - 1);
	return now;
}
```

### 求答案

如果找到了叶节点，更新答案。否则递归它的左右孩子。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int N = 1e4 + 5;
int a, n, A[N], B[N], minn, ans;
char s;
struct node{
	int l, r;
} edge[N];
int build(int l1, int r1, int l2, int r2){
	if(r1 < l1) return -1;
	int now = B[r2], tmp = l1;
	while(A[tmp] != now) tmp++;
	edge[now].l = build(l1, tmp - 1, l2, l2 + (tmp - l1) - 1);
	edge[now].r = build(tmp + 1, r1, l2 + (tmp - l1), r2 - 1);
	return now;
}
void dfs(int u, int s){
	s += u;
	if(edge[u].l == -1 && edge[u].r == -1){
		if(s < minn || (s == minn && u < ans)){
			ans = u;
			minn = s;
		}
		return ;
	}
	if(edge[u].l != -1) dfs(edge[u].l, s);
	if(edge[u].r != -1) dfs(edge[u].r, s);
	return ;
}
int main(){
	while(scanf("%d%c", &a, &s) != EOF){
		n = 0;
		minn = 1e9;
		ans = 1e9;
		for(int i = 0; i < N; i++){
			edge[i].l = -1;
			edge[i].r = -1;
		}
		A[0] = a;
		while(s != '\n') scanf("%d%c", &A[++n], &s);
		for(int i = 0; i <= n; i++) scanf("%d", &B[i]);
		build(0, n, 0, n);
		dfs(B[n], 0);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：_短笛无腔_ (赞：3)

# 前置芝士：树的遍历

树的遍历分三种：

* 先序遍历，是指以根->左->右形式遍历一颗树。

* 中序遍历，是指以左->根->右形式遍历一颗树。

* 后序遍历，是指以左->右->根形式遍历一颗树。

这三种遍历都有关联，比如根据先序遍历、后序遍历前后的不同，以及中序遍历分半的叶数量，求出左子树和右子树。

------------
# 正文

思路：我们只要在中序遍历里找到根，就知道左右子树的中序和后序遍历了。这样我们可以先把二叉树构造出来，然后再执行一次递归遍历，找最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxv 10005
//因为各节点权值不同且都是正整数，直接用权值作为节点编号
int io[maxv],po[maxv],lch[maxv],rch[maxv],n;
bool rl(int *a){
    string l;
    if(!getline(cin,l))return false;
    stringstream ss(l);
    n=0;
    int x;
    while(ss>>x)a[n++]=x;
    return n>0;
}
//把io[l1...r1]和po[l2...r2]建树，返回树根
int build(int l1,int r1,int l2,int r2){
    if(l1>r1)return 0;//是一颗空树
    int r=po[r2];
    int p=l1;
    while(io[p]!=r)p++;
    int cnt=p-l1;//左子树结点个数
    lch[r]=build(l1,p-1,l2,l2+cnt-1);
    rch[r]=build(p+1,r1,l2+cnt,r2-1);
    return r;
}
int b,bs;//最优解和权和
void dfs(int u,int s){
    s+=u;
    //叶子
    if(!lch[u]&&!rch[u]){
        //变量名而已，不是祖安……
        if(s<bs||(s==bs&&u<b)){
            b=u;
            bs=s;
        }
    }
    if(lch[u])dfs(lch[u],s);
    if(rch[u])dfs(rch[u],s);
}
int main(){
    while(rl(io)){
        rl(po);
        build(0,n-1,0,n-1);
        bs=1000000000;
        dfs(po[n-1],0);
        cout<<b<<endl;
    }
    return 0;
}
```


---

## 作者：__Unknown (赞：2)

#### 完全不同的建树方法哦，根据后序遍历的性质可以知道，一棵树的后序遍历构成大概是这样的：最左侧叶节点，左侧第二个叶节点，最左侧叶节点父亲，……，右右子树根，右子树根，树根。
#### 那么由此我们就可以发现，把后序遍历反过来就是依次从上至下（从根到叶），从右到左的子树的根，我们用一个k来不断地从后序遍历中得到子树的根，再在中序遍历中找到子树的部分就行啦！！
## ~~废话少说，放码过来~~
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
vector <int> edge[10005];
int n,a1[10005],a2[10005],val[10005];
int min1,min2;
long long k;
int build(int l,int r,int root){
	if(r<l) return -1;
	k++;int rt=1;
	int ll = a2[k];//这是父亲 
	while(a1[rt]!=a2[k]) rt++;//寻找子树的根在中序遍历中的位置 
	val[ll]+=ll;//累加 
	val[ll]+=val[root];//累加 
	if(l == r){//如果这是叶子节点
		if(val[ll]<min2||(val[ll] == min2&&min1>ll)){
			min2 = val[ll];
			min1 = ll;
		} 
		return a1[rt];
	}
	int t = build(rt+1,r,ll);//递归建树 
	if(~t){
	edge[ll].push_back(t);}
	t = build(l,rt-1,ll);
	if(~t){
	edge[ll].push_back(t);} 
	return ll;
}
int main()
{
	int t;char c;
	while(scanf("%d%c",&t,&c)!=EOF){//输入 
		memset(a1,0,sizeof a1);
		memset(a2,0,sizeof a2);
		min2=0;n=1;a1[n] = t;
		while(c!='\n'){
			scanf("%d%c",&t,&c);
			a1[++n]=t;
		}
		for(int i=1;i<=n;i++)
			cin>>a2[n-i+1];
		for(int i=0;i<=n;i++) 
			edge[i].clear();//初始化 
		min1 = 0x3f3f3f3f;
		min2 = 0x3f3f3f3f;
		k=0;memset(val,0,sizeof val);
		build(1,n,0);//建树 
		val[a2[1]] = a2[1];
		cout<<min1<<endl;
	}
	return 0;
 } 
```


---

## 作者：TwoJie (赞：1)

这是本蒟蒻的第1篇题解，如有任何格式错误或是思路含糊不清，请各位指正。

[原题链接](https://www.luogu.com.cn/problem/UVA548)

## 题意简述

给你一棵二叉树的中序和后序遍历，求出从根到叶子节点路径的数值总和，输出该叶子节点的值。

若有多条路径，输出最小值的叶子结点。

题目有多组数据，每组数据共2行，第1行是中序遍历，第2行是后序遍历。

## 题目分析

总的来说，我们需要先通过中序和后序遍历建好一棵二叉树，然后遍历一遍。

#### 预处理

因为题目没有给二叉树的节点个数，所以我们需要对输入进行一些处理。我的处理方法是：用字符串读入，然后将字符串转化成数字（这就写了大概50行）。

#### 建树思路

因为后序遍历的最后一个数是根，然后我们根据中序遍历找出它的左子树以及右子树，递归求解即可。

#### 遍历思路

与题目不同的是，我们不从叶子开始找，而是从根往下搜索，如果找到一个叶子，就更新答案，最后输出答案即可。

## 代码

AC代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
string s1,s2;
int a[N],b[N];//a是中序遍历 b是后序遍历 
int l[N],r[N];//使用左右儿子存储法 
int len,ansv,ans;
int solve1(int x,int t){//字符串转数字 
	int pos;//pos代表这个数字的最后一位在字符串中的位置 
	for (int i=x;i<s1.length();i++){
		if (s1[i]==' '){
			pos=i-1;
			break;
		}
		if (i==s1.length()-1){//最后一个数字后没有空格！ 
			pos=s1.length()-1;
			break;
		}
	}
	int temp=1;
	for (int i=pos;i>=x;i--){//字符转数字 
		int si=s1[i]-'0';
		a[t]+=(si*temp);
		temp*=10;
	}
	return pos;
}
int solve2(int x,int t){//同solve1 
	int pos;
	for (int i=x;i<s2.length();i++){
		if (s2[i]==' '){
			pos=i-1;
			break;
		}
		if (i==s2.length()-1){
			pos=s2.length()-1;
			break;
		}
	}
	int temp=1;
	for (int i=pos;i>=x;i--){
		int si=s2[i]-'0';
		b[t]+=(si*temp);
		temp*=10;
	}
	return pos;
}
int build(int l1,int r1,int l2,int r2){//建树 
	if (l1>r1) return 0;//递归边界 
	int pos,root=b[r2];//pos代表根在中序遍历中的位置 
	for (int i=l1;i<=r1;i++){//找到根在中序遍历中的位置，以确定其左右子树 
		if (a[i]==root){
			pos=i;
			break;
		}
	}
	l[root] = build(l1,pos-1,l2,l2+(pos-l1)-1);//递归求解 
	r[root] = build(pos+1,r1,l2+(pos-l1),r2-1);
	return root;
}
void search(int x,int v){//遍历 
	if (l[x]==0 && r[x]==0){//找到叶子 
		if (ansv>v){
			ans=x;//ans是叶子的值 
			ansv=v;//ansv是最短路径的数值总和 
		}
		if (ansv==v){
			ans=min(ans,x);
		}
		return;
	}
	if (l[x]!=0) search(l[x],v+l[x]);
	if (r[x]!=0) search(r[x],v+r[x]);
}
int main(){
	while (getline(cin,s1)){
		getline(cin,s2);//读入中序和后序遍历 
		len=0;ansv=1e8;//len表示现在存储节点个数 
		int j=0;
		while (j<s1.length()){
			len++;
			j=solve1(j,len)+2;
		}
		j=0;
		int len2=0;
		while (j<s2.length()){
			len2++;
			j=solve2(j,len2)+2;
		}
		build(1,len,1,len);
		search(b[len],b[len]);
		cout<<ans<<endl;
		s1="";s2="";//初始化 
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
	}
	return 0; //刚好100行 
}
```
祝您AC！

---

## 作者：AC基德 (赞：1)

### 方法：二叉树

分析：

后续遍历的第一个字符就是根，因此只需在中序遍历中找到他，就知道左右子树的中序遍历和后序遍历了。这样可以先把二叉树构造出来，然后再执行一次递归遍历，找到最优解。

和（第一篇题解）完全不同的解法，详见c++代码：

```c
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

//因为各个结点的权值各不相同且都是正整数，直接用权值作为结点编号
const int maxv = 10000 + 10;
int in_order[maxv], post_order[maxv], lch[maxv], rch[maxv];
int n;

bool read_list(int *a)
{
	string line;
	if(!getline(cin, line)) return false;
	stringstream ss(line);
	n = 0;
	int x;
	while(ss >> x) a[n++] = x;
	return n > 0;
}

//把in_order[L1..R1]和post_order[L2..R2]建成一颗二叉树，返回树根
int build(int L1, int R1,int L2, int R2)
{
	if(L1 > R1) return 0;//空树 
	int root = post_order[R2];
	int p = L1;
	while(in_order[p] != root) p++;
	int cnt = p - L1;//左子树的结点数
	lch[root] = build(L1, p-1, L2,L2+cnt-1); 
	rch[root] = build(p+1, R1, L2+cnt,R2-1); 
	return root;
} 

int best, best_sum;//目前为止的最优解和对应的权值

void dfs(int u, int sum)
{
	sum += u;
	if(!lch[u] && !rch[u])//叶子 
	{ 
		if(sum < best_sum || (sum == best_sum && u < best))
		{
			best = u;
			best_sum = sum;
		} 
	}
	if(lch[u]) dfs(lch[u], sum);
	if(rch[u]) dfs(rch[u], sum);
} 

int main()
{
	while(read_list(in_order))
	{
		read_list(post_order);
		build(0, n-1, 0, n-1);
		best_sum = 1000000000;
		dfs(post_order[n-1], 0);
		cout << best << "\n";
	} 
	return 0;
}
```
谢谢大家，若有不适，大佬轻喷。

---

## 作者：ncwzdlsd (赞：0)

后序遍历的第一个字符就是根，因此只需在中序遍历中找到它，就知道左右子树的中序和后序遍历了。这样可以先把二叉树构造出来，然后再执行一次递归遍历，找到最优解。

>给定二叉树的中序遍历和后序遍历，可以构造出这棵二叉树。方法是根据后序遍历找到树根，然后在中序遍历中找到树根，从而找出左右子树的结点列表，然后递归构造左右子树。

代码如下：
```cpp
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

const int maxv = 10000 + 10;
int in_order[maxv], post_order[maxv], lch[maxv], rch[maxv];
int n;

bool read_list(int* a) 
{
    string line;
    if(!getline(cin, line)) return false;
    stringstream ss(line);
    n = 0;
    int x;
    while(ss >> x) a[n++] = x;
    return n > 0;
}

int build(int L1, int R1, int L2, int R2) 
{
    if(L1 > R1) return 0; 
    int root = post_order[R2];
    int p = L1;
    while(in_order[p] != root) p++;
    int cnt = p-L1; 
    lch[root] = build(L1, p-1, L2, L2+cnt-1);
    rch[root] = build(p+1, R1, L2+cnt, R2-1);
    return root;
}

int best, best_sum;

void dfs(int u, int sum) 
{
    sum += u;
    if(!lch[u] && !rch[u]) 
    { 
        if(sum < best_sum || (sum == best_sum && u < best)) 
        { 
            best = u; 
            best_sum = sum; 
        }
    }
    if(lch[u]) dfs(lch[u], sum);
    if(rch[u]) dfs(rch[u], sum);
}

int main() 
{
    while(read_list(in_order)) 
    {
        read_list(post_order);
        build(0, n-1, 0, n-1);
        best_sum = 1000000000;
        dfs(post_order[n-1], 0);
        cout << best << "\n";
    }
    return 0;
}
```

---

## 作者：pengzy___ (赞：0)

**树的遍历有三种：**

[前序遍历](https://baike.baidu.com/item/%E5%89%8D%E5%BA%8F%E9%81%8D%E5%8E%86/757319)

[中序遍历](https://baike.baidu.com/item/%E4%B8%AD%E5%BA%8F%E9%81%8D%E5%8E%86/757281)

[后序遍历](https://baike.baidu.com/item/%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86/1214806)

### 化简题意：

给你一个二叉树的中序遍历和后序遍历，确定给定二叉树中的一个叶子节点，使从根到叶子路径上的节点权值之和最小。

## 分析：

本题输入二叉树的中序、后序序列，求解从根到叶子权值之和最小的叶子节点，如果有多个答案，则选择具有最小权值的叶子节点。首先根据二叉树的后序序列确定树根；然后根据中序序列划分左、右子树，还原二叉树；最后进行先序遍历，查找从根到叶子权值之和最小的叶子节点的权值。

### 算法代码：
```cpp
int createtree(int l1,int l2,int m) {//由遍历序列创建二叉树 
	if(m<=0)return 0;
	int root=postorder[l2+m-1],len=0;
	while(inorder[l1+len]!=root)len++;//计算左子树的长度 
	lch[root]=createtree(l1,l2,len);
	rch[root]=createtree(l1+len+1,l2+len,m-len-1);
	return root; 
}

bool readline(int *a) {//读入遍历序列，中间有空格 
	string line;
	if(!getline(cin,line))return false;
	stringstream s(line);
	n=0;
	int x;
	while(s>>x)a[n++]=x;
	return n>0;
}

void fingmin(int v,int sum) { 
	sum+=v;
	if(!lch[v]&&!rch[v])//叶子
	    if(sum<minsum||(sum==minsum&&v<minv))
		{
			minv=v;
			minsum=sum;
		} 
	if(lch[v])findmin(lch[v],sum);//v 有左子树 
	if(rch[v])findmin(rch[v],sum);//v 有右子树 
}

int main()
{
	while(readline(inorder)) {//读入中序遍历 
	    readline(postorder);//读入后序遍历
		createtree(0,0,n);
		minsum=0x7fffffff;
		findmin(postorder[n-1],0);
		cout<<minv<<endl; 
	}
	return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

程序大致流程：

输入中序遍历与后序遍历，之后根据中序与后续遍历将二叉树构造出来，之后执行一次 DFS，找到最优解并输出。

难点就在于如何将二叉树构造出来。

构造方法是根据后序遍历找到树根，然后在中序遍历中找到这个根，从而找出左右子树的结点列表，然后递归构造左右子树，直至子树为空就返回。

代码（细节见注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;

// best 为目前为止的最优解，best_sum 为对应的权和
int zhong[10050], hou[10050], n, best, best_sum;
struct node
{
    int v;
    node *left, *right;
    node() : v(0), left(NULL), right(NULL) {}
};

node *newnode() { return new node(); }

bool read_zhong()
{
    string line;
    if (!getline(cin, line)) return 0;
    stringstream ss(line);
    int elem, i;
    for (i = 1; ss >> elem; ++i) zhong[i] = elem;
    n = --i;
    return 1;
}

bool read_hou()
{
    string line;
    if (!getline(cin, line)) return 0;
    stringstream ss(line);
    int elem, i;
    for (i = 1; ss >> elem; ++i) hou[i] = elem;
    n = --i;
    return 1;
}

// 把 zhong[zhol...zhor] 和 hou[houl...hour] 建成一个二叉树，返回树根
node *construct(int zhol, int zhor, int houl, int hour)
{
    if (zhol > zhor) return NULL;
    node *fat = newnode();
    int root = hou[hour], idx;
    for (int i = zhol; i <= zhor; ++i)
        if (zhong[i] == root)
        {
            idx = i;
            break;
        }
    fat->v = root;
    fat->left = construct(zhol, idx - 1, houl, houl + idx - zhol - 1);
    fat->right = construct(idx + 1, zhor, houl + idx - zhol, hour - 1);
    return fat;
}

void dfs(node *u, int sum)
{
    if (u == NULL) return;
    sum += u->v;
    if (u->left == NULL && u->right == NULL &&    // 为叶子
        (sum < best_sum || (sum == best_sum && u->v < best)))
        {
            best = u->v;
            best_sum = sum;
        }
    dfs(u->left, sum);
    dfs(u->right, sum);
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    while (read_zhong())
    {
        best_sum = INT_MAX;
        read_hou();
        node *root = construct(1, n, 1, n);
        dfs(root, 0);
        cout << best << '\n';
    }
    return 0;
}
```


---

## 作者：abs20187 (赞：0)

# 题解

这道题输入有点难处理，必须要 ``` getline ``` 一行的字符然后再转化成数组。

难点在于建树。题目给了我们中序、后序遍历。通过后序遍历，我们可以知道根结点的值，再在中序遍历中找到。
此时根节点将中序遍历化成两块，左边的是左子树，右边的是右子树。
再拿左右子树继续以上操作，这道题就可以做了。

答案遍历一遍树即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int v[200005],u[200005];//记录中序、后序遍历
int l[200005],r[200005];//用于存储树
int build(int l1,int r1,int l2,int r2)
{
	if(r1-l1<0||r2-l2<0)
	{
		return 0;
	}
	int rt=0,key=u[r2];
	for(int i=l1;i<=r1;i++)
	{
		if(v[i]==key)
		{
			rt=i;
		}
	}
	int sizel=rt-l1;
	int sizer=r1-rt;
	l[rt]=build(l1,rt-1,l2,l2+sizel-1);
	r[rt]=build(rt+1,r1,l2+sizel,l2+sizel+sizer-1);
	return rt;
}
long long ans,k;
void dfs(int id,long long sum)
{
	sum+=v[id];
	if(id==0)
	{
		return ;
	}
	if(l[id]==0&&r[id]==0)//叶子节点
	{
		if(sum<ans)
		{
			ans=sum;
			k=v[id];
		}
		else if(sum==ans)
		{
			k=min(k,1ll*v[id]);
		}
	}
	dfs(l[id],sum);
	dfs(r[id],sum);
}
int main()
{
	string s1,s2;
	while(getline(cin,s1))
	{
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		memset(v,0,sizeof(v));
		memset(u,0,sizeof(u));//初始化
		
		getline(cin,s2);
		int n=1;
		for(int i=0;i<s1.size();i++)
		{
			if(s1[i]==' ')
			{
				n++;
			}
			else
			{
				v[n]=v[n]*10+s1[i]-'0';
			}
		}
		int m=1;
		for(int i=0;i<s2.size();i++)
		{
			if(s2[i]==' ')
			{
				m++;
			}
			else
			{
				u[m]=u[m]*10+s2[i]-'0';
			}
		}//字符串转数组
		int root=build(1,n,1,m);//建树
		ans=1e18;
		dfs(root,0);//求答案
		cout<<k<<"\n";
	}
	
	return 0; 
}
```

---

