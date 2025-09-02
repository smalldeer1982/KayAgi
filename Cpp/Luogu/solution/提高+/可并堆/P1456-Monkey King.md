# Monkey King

## 题目描述

曾经在一个森林中居住着 $N$ 只好斗的猴子。在最初他们我行我素，互不认识。但是猴子们不能避免争吵，且两只猴子只会在不认识对方时发生争吵，当争吵发生时，双方会邀请它们各自最强壮的朋友并发起决斗（决斗的为各自最强壮的朋友）。当然，在决斗之后两只猴子和他们各自的伙伴都认识对方了（成为朋友），虽然他们曾经有过冲突，但是他们之间绝不会再发生争吵了。

假设每只猴子有一个强壮值，强壮值将在一场决斗后减少为原先的一半（例如  $10$ 会减少到  $5$，而  $5$ 会减少到  $2$，即向下取整）。

我们也假设每只猴子都认识它自己（是自己的朋友）。即当他是他朋友中最强壮的，他自己就会去决斗。

## 说明/提示

$N,M\leq 100000$，$s_{i}\leq 32768$

## 样例 #1

### 输入

```
5
20
16
10
10
4
5
2 3
3 4
3 5
4 5
1 5
```

### 输出

```
8
5
5
-1
10
```

# 题解

## 作者：George1123 (赞：50)

[${\color{#ee8800}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.com.cn/blog/Wendigo/)

[P1456 【Monkey King】](https://www.luogu.com.cn/problem/P1456)

### 此题算法:左偏树(可并堆)

[左偏树手画图解](https://www.luogu.com.cn/blog/Wendigo/zuo-pian-shu-ke-bing-dui-tu-xie)

**首先要理解正确题目：**

有若干个猴盟，最强的猴子当大王。

刚开始猴子互不相识，每只猴子都是自己盟大王。

后来两只猴子起矛盾，**各找大王**来打架。

打完后大王被削，能力为原来的**一半(下取整)**。

打完后两猴群**合并为同盟并从新选大王**

此时输出**新大王能力**。

>(手画勿吐槽)

![猴子.jpg](https://i.loli.net/2019/12/14/ohwtgEYMOlrFx7m.jpg)

此题用到**左偏树**，就是**可并堆**。

每**盟**猴子都是一个堆。

每次打架，先**双方取大王**。

然后，把两个大王削掉。

削完后选新大王(**削一个大王如下**)。

```cpp
int weak(int x){//x为大王
	v[x]>>=1; //v[x]/=2;
	int rt=merge(ls[x],rs[x]); //合并子树，新根为rt
	ls[x]=rs[x]=dep[x]=0; //独立x
	return f[rt]=f[x]=merge(rt,x); //加入x，新根和x的祖先为总根
}

```
特殊情况，**矛盾生于同盟间，不打，输出$-1$。**

否则，将连个盟合并，**皆大欢喜**。

```cpp
if(x==y) puts("-1"); //化解矛盾
else {
	int l=weak(x),r=weak(y); //大王:为啥受伤的总是我
	f[l]=f[r]=merge(l,r); //推举新王
	printf("%d\n",v[f[l]]); //输出新王
}
```
**此外为了加速，$f[]$数组是祖先数组，类似并查集的路径压缩。**


## 以下是代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
int ls[N],rs[N],f[N];
int v[N],dep[N];
int find(int x){ //路径压缩并查集find函数
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int merge(int x,int y){
	if(!x||!y) return x^y; //x+y x|y 都可以
	if(v[x]<v[y]) swap(x,y);
	rs[x]=merge(rs[x],y);
	f[rs[x]]=x;
	if(dep[ls[x]]<dep[rs[x]]) //左偏
		swap(ls[x],rs[x]);
	dep[x]=dep[ls[x]]+1;
	return x;
}
int weak(int x){//x为大王
	v[x]>>=1; //v[x]/=2;
	int rt=merge(ls[x],rs[x]); //合并子树，新根为rt
	ls[x]=rs[x]=dep[x]=0; //独立x
	return f[rt]=f[x]=merge(rt,x); //加入x，新根和x的祖先为总根
}
void solve(){
	dep[0]=-1;
	for(int i=1;i<=n;i++){
		ls[i]=rs[i]=dep[i]=0;
		scanf("%d",v+i),f[i]=i; //并查集一样的初始化
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		x=find(x),y=find(y);
		// printf("%d %d\n",x,y);
		if(x==y) puts("-1");
		else {
			int l=weak(x),r=weak(y);
			f[l]=f[r]=merge(l,r);
			printf("%d\n",v[f[l]]);
		}
	}
}
int main(){
	while(scanf("%d",&n)==1) //多种测试数据
		solve();
	return 0;
}
```

题目中文翻译是孙悟空。

**写题解不易，喜欢就点个赞吧。**

谢谢大家! !




---

## 作者：lolte (赞：45)

大家好，我是GD初一最弱蒟蒻 $lolte$。[洛谷博客](https://www.luogu.org/blog/luoyuexiu/solution-p1456)

终于从悲惨的学校集训中解放啦(⁎˃ᴗ˂⁎)，正好这几天在刷数据结构，也在学左偏树（左式堆），然后写完模板就来敲这道$Monkey$ $King$ 啦。

~~话说好像跑题了~~

下图就是一棵左偏树啦。**npl值(null path length)，零路径和，就是一个点到离它最近的非满节点的路径长度**（可以参考下图）。在左偏树里，右儿子的npl值小于等于左儿子的npl值。一个节点的npl值为右儿子npl值+1。非满节点的npl值为0，为了方便计算，0的npl值为-1。

在这题里，我们要维护一个大根堆，能力值大的在上。
![](http://www.z4请更换图床a.net/images/2018/07/24/IMG_20180724_123303.md.jpg)
然后这题差不多是左偏树模板啦。

有$n$只猴子，就是$n$棵左偏树咯，然后有$m$个操作，将两棵左偏树中的根节点（就是能力值最高的）能力值减半，然后合并这两棵树。减半之后，直接将根节点挪下去不太好做，于是就分别将两棵树的根节点先减半，然后做个**删除**，之后**合并左右子树**，再将根节点**合并**回来，再将这两棵树合并就好啦。

### 下面这两张图模拟了这道题的操作过程:
![](http://www.z4请更换图床a.net/images/2018/07/24/IMG_20180724_124338.md.jpg)
![](http://www.z4请更换图床a.net/images/2018/07/24/IMG_20180724_124349.md.jpg)

细节就请见代码和注释吧qwq

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h> 
using namespace std;
inline int read(){//读入优化 
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
const int maxn=100010;//n的最大值 
int n,m,L[maxn],R[maxn],key[maxn],npl[maxn],fa[maxn];
//L为左子树编号，R为右子树编号，key为能力值，npl请见上面，fa为并查集数组 
inline int getf(int o) { 
    return o==fa[o] ? o : fa[o]=getf(fa[o]);
    //路径压缩更快 
}
inline int join(int a,int b) {
	//合并函数 
    if (!a) return b;//判断是否为空 
    if (!b) return a;
    if (key[a]<key[b]) swap(a,b);//维护堆性质 
    R[a]=join(R[a],b);//将b合并到a的右子树 
    if (npl[R[a]]>npl[L[a]]) swap(L[a],R[a]);
	//维护左偏树性质，npl[r]<=npl[l] 
    npl[a]=npl[R[a]]+1;//获得npl值 
    return a;//返回新根编号 
}
inline void work(int a,int b) {
    a=getf(a);b=getf(b);//找根 
    if (a==b) {//已经是朋友 
        puts("-1");
        //不打了 
        return;
    }
    int rt,art,brt;
    //a所属的左偏树的操作 
    key[a]>>=1;//减半 
    rt=join(L[a],R[a]);//合并左右子树 
    L[a]=R[a]=npl[a]=0;//将根节点断掉 
    art=join(rt,a);//重新合并旧根
    fa[rt]=fa[a]=art; 
    //为了路径压缩，要将旧根和子树合并的根都指向新根 
    key[b]>>=1;
    rt=join(L[b],R[b]);
    fa[L[b]]=fa[R[b]]=rt;
    L[b]=R[b]=npl[b]=0;
    brt=join(rt,b);
    fa[rt]=fa[b]=brt;
    //同a的操作 
    rt=join(art,brt);//合并两棵左偏树 
    fa[art]=fa[brt]=rt;
    //将两个旧根指向新根 
    printf("%d\n",key[rt]);
}
int main(){
    while (~scanf("%d",&n)) {//多组数据 
        npl[0]=-1;//特殊处理 
        for (register int i=1;i<=n;++i) {
        	//初始化 
            L[i]=R[i]=npl[i]=0;
            fa[i]=i;
            key[i]=read();
        }
        m=read();
        for (register int i=1;i<=m;++i) 
            work(read(),read());//猴子打架 
    }
}
```

### 评测记录：
![](http://www.z4请更换图床a.net/images/2018/07/24/a1cd3c8b7bb82888d8d05f012ff37c1b.md.png)

#### 祝大家OI rp++!!!

---

## 作者：asd_a (赞：17)

## 膜拜手写可并堆的大佬们  
本蒟蒻只会用一个十分偷懒的办法  
~~（但似乎复杂度不那么优秀）~~  
应该没人知道在 ext/pb_ds/priority_queue.hpp
里面有可并堆的STL吧，这里讲一下最优秀的配对堆  
（pairing_heap)
```
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
priority_queue<int,std::less<int>,pairing_heap_tag> q[100005];
```
支持join,pop,top,push……操作（总之左偏树能用的，都能用）  
(＾Ｕ＾)ノ~Ｙ  
~~手写可并堆被抛弃了~~  
用并查集维护一下所在堆就好了  
然而有多组数据，只能放弃复杂度了，预处理pop一遍  
code:
```
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
typedef priority_queue<int,std::less<int>,pairing_heap_tag> heap;
using namespace std;
heap q[100005];
int fa[100005],n,m;
inline int fd(int x)
{
	if(fa[x]!=x) fa[x]=fd(fa[x]);
	return fa[x];
}
void work()
{
	int x,y,fx,fy,xx,yy;
	for(int i=1;i<=n;i++)
		while(!q[i].empty())q[i].pop();
	for(int i=1;i<=n;i++)
		fa[i]=i,cin>>x,q[i].push(x);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		fx=fd(x),fy=fd(y);
		if(fx==fy)
		{
			cout<<-1<<endl;
			continue;
		}
		xx=q[fx].top(),yy=q[fy].top();
		q[fx].pop(),q[fy].pop();
		xx/=2,yy/=2;
		q[fx].push(xx),q[fy].push(yy);
		q[fx].join(q[fy]);
		fa[fy]=fx;
		cout<<q[fx].top()<<endl;
	}
	return ;
}
int main()
{
	while(scanf("%d",&n)!=EOF) work();
	return 0;
}
```

---

## 作者：福州周圣力 (赞：15)

##标签：左偏树&并查集

##思路来源：

Q1：为什么用并查集？

A1：因为要判断两队猴子是否认识，在此处使用并查集可以便于维护两队猴子间的关系。

Q2：为什么用堆？

A2：因为每次对战都需要查找当前两队猴子中能力值最大的猴子，这里使用堆可以便于选出首领。

Q3：用什么样的堆？

A3：因为需要在两队猴子争执之后将两队猴子合并，并且不能破坏堆，所以要使用可并堆。

Q4：用什么可并堆？

A4：左偏树，斐波那契堆都是不错的可并堆，这里我使用的是左偏树。

##具体做法：

-使用并查集维护两队猴子之间的关系，在争执前先特判两队猴子已经认识的情况。

-根据题目要求，用左偏树模拟合并过程即可。

**参考代码**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

struct monkey {
    int lson;//用下标模拟地址 
    int rson;//用下标模拟地址 
    int power;//能力值 
    int dist;//节点到离它最近的外节点的距离（备注：外节点为叶节点或只有左（右）子树的节点） 
}m[100005];

int f[100005];

int ff(int ele) {//并查集-路径压缩 
    if (ele==f[ele]) {
        return ele;
    }
    return f[ele]=ff(f[ele]);
}

int merge(int ele1,int ele2) {//合并两个左偏树，并返回新树的根节点 
    if (ele1==0) {//如果有一棵待合并的树为空树，则合并结果为另一棵树 
        return ele2;
    }
    if (ele2==0) {//同上 
        return ele1;
    }
    if (m[ele1].power<m[ele2].power) {//保证第一棵树的能力值<第二颗树 
        swap(ele1,ele2);
    }
    m[ele1].rson=merge(m[ele1].rson,ele2);//将较小的树合并到较大树的右子树中 
    f[m[ele1].rson]=ele1;
    if (m[ele1].rson==0) {//更新根节点到离它最近的外节点的距离 
        m[ele1].dist=0;
    }
    else {
        m[ele1].dist=m[m[ele1].rson].dist+1;
    }
    if (m[m[ele1].lson].dist<m[m[ele1].rson].dist) {//根据左偏树的性质，当左侧的长度>右侧的长度时，要交换左右子树 
        swap(m[ele1].lson,m[ele1].rson);
    }
    return ele1;
}

int main() {
    int n,t,x,y,p,q,root,newx,newy;
    while (scanf("%d",&n)!=EOF) {
        for (register int i=1;i<=n;++i) {
            scanf("%d",&m[i].power);
        }
        for (register int i=1;i<=n;++i) {//在最初的时候，每只猴子独立形成一个群体 
            m[i].lson=0;
            m[i].rson=0;
            f[i]=i;
        }
        scanf("%d",&t);
        while (t--) {
            scanf("%d%d",&x,&y);
            p=ff(x);//找出各自的首领，这部分用并查集维护 
            q=ff(y);
            if (p==q) {//按题目要求，两只本来就认识的猴子不会发生争执 
                printf("-1\n");
                continue;
            }
            m[p].power/=2;//更新首领在争执后剩余的能力值 
            root=merge(m[p].lson,m[p].rson);//先合并原首领的左右子树 
            m[p].lson=0;//将首领孤立 
            m[p].rson=0;
            newx=merge(root,p);//让首领归队，这部分用左边数维护，以便选出首领 
            m[q].power/=2;//同上 
            root=merge(m[q].lson,m[q].rson);
            m[q].lson=0;
            m[q].rson=0;
            newy=merge(root,q);
            root=merge(newx,newy);//将争执后的两队猴子合并 
            f[newx]=root;//更新并查集 
            f[newy]=root;
            printf("%d\n",m[root].power);//输出新首领的能力值 
        }
    }
    return 0;
}
```

---

## 作者：cjh20090318 (赞：14)

（上一次更新： 2022-06-02 19:40 ，修改了乱加空格的问题，以及函数 merge 的命名）

大家好，我是 CQ-FZOIer，C2024 级蒟蒻 CJH。[洛谷博客](https://www.luogu.com.cn/blog/Chen-Jinhui/solution-p1456)

最近我们学了堆，接着学了并查集，老师就为我们布置了这一道题目 [Monkey King](https://www.luogu.com.cn/problem/P1456) 了。 ~~我们还没有学左偏树，所以看不懂各位大佬的左偏树题解。~~ 我决定换一种更浅显的方式，也就是……

**堆+并查集**的方法来 AC 此题！！！

下面……

### 开始切入正题，分析题目：

1. 有 $N$ 只猴子，于是我们就要创建 $N$ 个大根堆。

2. 还需要长度为 $N$ 的 father 数组，用来储存猴子的根，$fa_i$ 表示第 $i$ 个猴子的根。

3. 当两只猴子打斗时，可以通过并查集的**找根**（find）来查找猴子的根：

```cpp
int find(int x){//找猴子x的根
	//循环查找
	/*while(x!=fa[x]){
		x=fa[x];
	}
	return x;*/
	//递归查找
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
```
4. 根据题意，如果根相等（也就是互相认识），则输出 $-1$；否则从两只猴子的团队中取出（top&pop）强壮最大值（堆顶），分别除以 $2$ 后再放回堆中（push）。

5. 接着用并查集进行**按秩合并**（merge）：

```cpp
void merge(int x,int y){//合并x,y
	int f1=find(x),f2=find(y);//找到两只猴子的根
	if(f1==f2)//如果为同一个根
		printf("-1\n");
	else{
		int at=a[f1].top(),bt=a[f2].top();
		a[f1].pop();a[f2].pop();
		at/=2;bt/=2;//按照题目要求减少一半
		a[f1].push(at);a[f2].push(bt);//放回原堆中
		if(a[f1].size()<a[f2].size()){//按秩合并，减少循环次数。
			//合并
			fa[f1]=f2; 
			//将一对元素全部移至f2
			while(!a[f1].empty()){
				int tmp=a[f1].top();
				a[f1].pop();
				a[f2].push(tmp);
			}
			//输出最大值
			printf("%d\n",a[f2].top());
		}
		else{
			//同上
			fa[f2]=f1;
			while(!a[f2].empty()){
				int tmp=a[f2].top();
				a[f2].pop();
				a[f1].push(tmp);
			}
			printf("%d\n",a[f1].top());
		}
	}
}
```
### 注意事项

题目可能有**多组数据**！！！所以我们应该一直读入至**文件结束符 EOF**。

### 具体详见代码（请勿抄袭！！！）：

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
int n,m;
int fa[100001];//存储每只猴子的根
priority_queue <int> a[100001];//维护的堆
//函数都在后面！！！
int find(int x);//找根
void merge(int x,int y);//合并
int main(){
	while(scanf("%d",&n)!=EOF){//有多组数据，需要一直读入到文件结束符EOF
		//需要清空堆！
		for(int i=0;i<=100000;i++){
			while(!a[i].empty())
				a[i].pop();
		}
		//将根先设为自己
		for(int i=1;i<=n;i++) fa[i]=i;
		//读入实力值，存储至堆中
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			a[i].push(x);
		}
		//进行打斗
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			merge(x,y);//合并
		}
	}
	return 0;
}
int find(int x){
	//循环找根
	/*while(x!=fa[x]){
		x=fa[x];
	}
	return x;*/
	//递归找根
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int f1=find(x),f2=find(y);//找到两只猴子的根
	if(f1==f2)//如果为同一个根
		printf("-1\n");
	else{
		int at=a[f1].top(),bt=a[f2].top();
		a[f1].pop();a[f2].pop();
		at/=2;bt/=2;//按照题目要求减少一半
		a[f1].push(at);a[f2].push(bt);//放回原堆中
		if(a[f1].size()<a[f2].size()){//按秩合并，减少循环次数。
			//合并
			fa[f1]=f2; 
			//将一对元素全部移至f2
			while(!a[f1].empty()){
				int tmp=a[f1].top();
				a[f1].pop();
				a[f2].push(tmp);
			}
			//输出最大值
			printf("%d\n",a[f2].top());
		}
		else{
			//同上
			fa[f2]=f1;
			while(!a[f2].empty()){
				int tmp=a[f2].top();
				a[f2].pop();
				a[f1].push(tmp);
			}
			printf("%d\n",a[f1].top());
		}
	}
}

```
如有错误，欢迎*批评指正*，本人将**尽快修改**。

*谢谢查看！*

此题是本人 AC 的**第一道紫题**，更是本人写的**第一篇题解**！

---

## 作者：Clever_Jimmy (赞：9)

个人认为，这题可以用更好写的 **启发式合并** 来水过。

说是“水”，但其实复杂度 $O(n\log^2 n)$ 也是正解。

题目所说的操作很简单，支持很多个大根堆的合并以及修改最大值。

1. 对于每个合并操作，我们按照 **堆的大小** 为 $\text{rank}$ 启发式合并。

   可以证明，每次合并最小的堆的大小至少会变为原来的 $2$ 倍，因此这个操作是**均摊** $O(\log^2 n)$ 的。
   
2. 对于每个删除操作，使用二叉堆（或是 `std::priority_queue`）来实现是 $O(1)$ 的。

3. 对于每个插入操作，显然是 $O(\log n)$ 的。

综上所述，我们利用启发式合并堆来解决这道题是合情合理的，时间复杂度为 **均摊** $O(n \log n + m\log^2n)$。

代码实现：

```cpp
#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m;

std::priority_queue <int> h[N];

struct DSU {
	static const int MS = N;
	int fa[MS], siz[MS];
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void join(int a, int b) {
		int pa = find(a), pb = find(b);
		if(pa == pb) return;
		if(siz[pa] < siz[pb]) std::swap(pa, pb);
		fa[pb] = pa, siz[pa] += siz[pb];
	}
	int size(int x) { return siz[ find(x) ]; }
	void build(int x) {
		for(int i = 1; i <= x; ++i) fa[i] = i, siz[i] = 1;
	}
} dsu;

int main() {
	while(scanf("%d", &n) != EOF) {
		dsu.build(n);
		for(int i = 1; i <= n; ++i) {
			int v;
			scanf("%d", &v);
			while(!h[i].empty()) h[i].pop();
			h[i].push(v);
		}
		scanf("%d", &m);
		for(int i = 1; i <= m; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			int fx = dsu.find(x), fy = dsu.find(y);
			if(fx == fy) { puts("-1"); continue; }
			else {
				int vx = h[fx].top(), vy = h[fy].top();
				h[fx].pop(), h[fy].pop();
				if(dsu.size(fx) < dsu.size(fy)) std::swap(fx, fy);
				while(!h[fy].empty()) {
					int tmp = h[fy].top(); h[fy].pop();
					h[fx].push(tmp);
				}
				dsu.join(fx, fy);
				h[fx].push(vx / 2), h[fx].push(vy / 2);
				printf("%d\n", h[fx].top());
			}
		}
	}
	return 0;
}
```


---

## 作者：xht (赞：7)

题目地址：[P1456 Monkey King](https://www.luogu.org/problemnew/show/P1456)

一道~~挺模板的~~左偏树题

不会左偏树？看[论文](https://wenku.baidu.com/view/20e9ff18964bcf84b9d57ba1.html)打[模板](https://www.luogu.org/problemnew/show/P3377)，完了之后再回来吧

~~然后你发现看完论文打完模板之后就可以A掉这道题不用回来了~~

细节见代码

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 6;
int n, m, f[N], a[N], l[N], r[N], d[N];

//类并查集路径压缩
int get(int x) {
	if (x == f[x]) return x;
	return f[x] = get(f[x]);
}

//左偏树合并
inline int merge(int x, int y) {
	if (!x || !y) return x + y;//x或y为0则返回另一个的简写
	if (a[x] < a[y]) swap(x, y);//保证堆性质
	r[x] = merge(r[x], y);
	f[r[x]] = x;
	if (d[l[x]] < d[r[x]]) swap(l[x], r[x]);//保证左偏树性质
	d[x] = d[r[x]] + 1;
	return x;
}

//删除堆顶，注意语句顺序
inline void pop(int x) {
	f[l[x]] = l[x], f[r[x]] = r[x];
	f[x] = merge(l[x], r[x]);
	l[x] = r[x] = 0;
}

//多组数据单独写一个函数
inline void work() {
	d[0] = -1;//0的“距离”为-1
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		f[i] = i;
		d[i] = l[i] = r[i] = 0;//多组数据清空数组
	}
	cin >> m;
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		int fx = get(x), fy = get(y);//找堆顶
		if (fx == fy) puts("-1");//若在同一个堆中输出-1
		else {
			pop(fx), pop(fy);//删除堆顶
			a[fx] >>= 1, a[fy] >>= 1;
			f[fx] = merge(fx, f[fx]), f[fy] = merge(fy, f[fy]);//将新值插入堆顶
			fx = get(fx), fy = get(fy);
			printf("%d\n", a[merge(fx,fy)]);//输出堆顶，注意堆中存的是下标而不是数
		}
	}
}

int main() {
	while (cin >> n) work();
	return 0;
}
```

---

## 作者：RiverFun (赞：7)

广告：[$\texttt{BLOG}$](https://stevebraveman.github.io/)

我看这道题没有人用手写配对堆过的，那我就交一发用手写配对堆的题解。

这道题比较麻烦的操作就是修改操作，我主要讲一下修改操作。

我是这么做的：

如果这个堆的大小是1，那么直接修改。

如果不是，则将最大权值的节点删除，新建一个节点，权值为被删除节点的权值的一半，再与之前的节点合并。

最后将两个堆合并就行了。

### Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 2000010
struct Heap {
	int v, id;
	int s, xd;
}h[MAXN];
int fa[MAXN], a[MAXN], siz[MAXN];
bool ifd[MAXN];
int merge(int a, int b) {
	if (h[a].v == 0) return b;
	if (h[b].v == 0) return a;
	if (h[a].v < h[b].v || (h[a].v == h[b].v && a < b)) std::swap(a, b);
	h[b].xd = h[a].s;
	h[a].s = b;
	return a;
}
int merges(int a) {
	if (h[a].v == 0 || h[h[a].xd].v == 0) return a;
	int p = h[a].xd, q = h[p].xd;
	h[a].xd = h[p].xd = 0;
	return merge(merge(a, p), merges(q));
}
int del(int a) {
	h[a].v = -1;
	return merges(h[a].s);
}
int find(int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}
bool un(int x, int y) {
	fa[y] = x;
	return 1;
}
int head[MAXN], x, y, n, m, cnt;
void push(int a, int &p) {
	cnt++;
	head[cnt] = cnt;
	h[cnt].v = a;
	h[cnt].id = cnt;
	h[cnt].s = h[cnt].xd = 0;
	fa[cnt] = cnt;
	siz[cnt] = 1;
	p = merge(cnt, p);
}
char op[5];
int main() {
	while (scanf("%d", &n) != EOF) {
		// scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			fa[i] = i;
		}
		h[0].v = 0;
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			head[i] = i;
			h[i].v = a[i];
			h[i].id = i;
			h[i].s = h[i].xd = 0;
			siz[i] = 1;
		}
		cnt = n;
		scanf("%d", &m);
		while (m--) {
			scanf("%d%d", &x, &y);
			int _x = find(x), _y = find(y);
			if (_x == _y) {
				puts("-1");
				continue;
			}
			bool fl1 = 0, fl2 = 0;
			if (siz[head[_x]] == 1) {
				h[head[_x]].v /= 2;
				fl1 = 1;
			}
			if (siz[head[_y]] == 1) {
				h[head[_y]].v /= 2;
				fl2 = 1;
			}
			if (!fl1) {
				int f = h[head[_x]].v;
				head[_x] = del(head[_x]);
				push(f / 2, head[_x]);
			}
			if (!fl2) {
				int g = h[head[_y]].v;
				head[_y] = del(head[_y]);
				push(g / 2, head[_y]);
			}
			un(_x, _y);
			head[_x] = merge(head[_x], head[_y]);
			siz[head[_x]] += siz[head[_y]];
			printf("%d\n", h[head[_x]].v);
		}
	}
}
```

---

## 作者：cheeseYang (赞：7)

写了一个折磨我两天的左偏树。。。合并的地方搞了我很久啊，具体注释看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
int n,m,f[maxn],dis[maxn];
struct node{
    int v,l,r;
}a[maxn];
int merge(int x,int y){
    if(x==0 || y==0)return x+y;//如果有一个子树为0就返回另一个
    if(a[x].v<a[y].v)    
        swap(x,y);//我们要保证是小根堆
    a[x].r=merge(a[x].r,y);//递归实现每次将两个要合并的堆比较，a[x].r是一个堆的右子树，y是另一个堆
    f[a[x].r]=x;
    if(dis[a[x].r]>dis[a[x].l])//要保证左偏树，所以左边的距离一定要大于等于右边
        swap(a[x].r,a[x].l);    
    if(a[x].r==0)dis[x]=0;    //这里牵扯到左偏树的距离的概念，因为他没有右子树了，所以他的距离就是0
    else dis[x]=dis[a[x].r]+1;    //否则距离为他右子树的距离加1
    return x;    //返回x
}
int r(int &x){
    char c=getchar();x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
int find(int x){
    return f[x]==x?x:find(f[x]);    
}
int del(int x){
    int l=a[x].l,r=a[x].r;    
    f[l]=l,f[r]=r;//因为删掉了根节点，所以根节点的两个孩子的父亲都变成自己
    a[x].l=a[x].r=dis[x]=0;//删除根节点
    return merge(l,r);
}
void work(int x,int y){
    a[x].v/=2,a[y].v/=2;//打斗以后权值减半
    int left,right;
    left=del(x);
    right=del(y);//前两个left和right是处理要合并的两个堆的，因为要把他们的根节点都删掉（因为已经打斗过了，值发生了变化）然后合并成一个新堆
    left=merge(left,x);
    right=merge(right,y);//这两个left和right是把他们变化过的根节点重新放进去，堆和点合并，也可以看成两个堆合并
    left=merge(left,right);//最后再合并这两个堆
    printf("%d\n",a[left].v);
}
int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;++i){    
            f[i]=i;
            a[i].r=a[i].l=0;
            dis[i]=0;
```
}//多组数据所以每次都要初始化
```cpp
        for(int i=1;i<=n;++i)r(a[i].v);//读入权值
        r(m);
        for(int i=1;i<=m;++i){
            int x,y;
        r(x),r(y);
            //cout<<"---";
            int fx=find(x),fy=find(y);
            if(fx==fy){
                printf("-1\n");
                continue;    
            }
            work(fx,fy);
        }
    }
    return 0;
}
```

---

## 作者：wjy666 (赞：5)

pbds库的配对堆，简单易懂，代码绝对很短(论pbds的优越性~)

```cpp
#include<cstdio>
#define N 100005
#include<algorithm>
#define For(i,j,k) for(int i=j;i<=k;i++)
#include<ext/pb_ds/priority_queue.hpp> //头文件
using namespace std;
using namespace __gnu_pbds; //开pbds库
int read(){
    int l=1,x=0; char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') ch=getchar(),l=-1;
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*l;
}
__gnu_pbds::priority_queue<int> h[N]; //声明，默认大根堆配对堆
int fa[N];
int find(int x){
    if (fa[x]==x) return x;
    fa[x]=find(fa[x]); return fa[x]; //这几行是并查集，标记每个猴子属于哪个堆
}
int main(){
    int n,m,k,k0,fx,fy,x,y;
    while(scanf("%d",&n)!=EOF){
        For(i,1,n) h[i].push(read()),fa[i]=i; //刚开始一个猴子一个堆
        m=read();
        For(i,1,m){
            x=read(),y=read();
            fx=find(x); fy=find(y); //并查集寻找2个猴子属于哪个堆
            if (fx==fy) printf("-1\n"); //属于同一个堆输出-1
            else{
                k=h[fx].top(); h[fx].pop(); k=k/2; h[fx].push(k);
                k=h[fy].top(); h[fy].pop(); k=k/2; h[fy].push(k); //两个堆根节点也就是最大的减半
                fa[fx]=fy; h[fy].join(h[fx]); //合并2个堆，一个join就行了，是不是很简单~
                printf("%d\n",h[fy].top()); //输出合并后的堆顶
            }
        }
        For(i,1,n) h[i].clear(); //多组数据，处理完一组要清空
    }
    return 0;
}
```

---

## 作者：Justin_N_Wu (赞：4)

这题一看就是左偏树（Leftist  Tree），貌似没有什么其它奇奇怪怪的做法了吧？如果不会的同学自行百度。

这里简单介绍一下左偏树：

左偏树一颗二叉树，且满足堆的所有性质（根节点是整棵树中最小或最大的），但相比于堆，它是极度不平衡的，顾名思义，整棵树都是向左倾斜的，这也是左偏树区别于普通堆的一个重要性质：

**对于每一个节点，其左儿子的距离大于等于右儿子的距离**

这里的距离定义为：该节点到其子树的叶子节点最少进过的边数。其中叶子节点（也称外节点）的距离为0，空节点为-1。

有的人可能会问，那每次插入复杂度岂不是很高？

并不是这样，我们可以利用上面的性质，每次插入都归到右边，复杂度反而会小于普通的堆（节点都在左边了）。

对于左偏树，最重要的意义是可以在LogN的时间里实现堆的合并（具体的自行百度吧，与堆一样比较易懂，代码难度也不高）。

假设你已经会左偏树了，结合这道题，我们的问题就是如何快速的得出当前节点属于哪棵树（堆）。

这里就有一个类似于并查集的方法：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
struct TreeNode{
    int w,dis,l,r;
    inline void clear(){ dis=l=r=0;}
} node[maxn];
int fa[maxn],n,m;
inline int read(){
    int ret=0; char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9')
        ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
    return ret;
}
inline int get_fa(int x){
    return fa[x]==x?x:fa[x]=get_fa(fa[x]);
}
inline int merge(int x,int y){
    if (!x) return y; if (!y) return x;
    if (node[x].w<node[y].w) swap(x,y);
    node[x].r=merge(node[x].r,y);
    int lc=node[x].l,rc=node[x].r;
    fa[rc]=x;       //这里尤为注意，把右子树的根节点给x
    if (node[lc].dis<node[rc].dis) swap(node[x].l,node[x].r);
    if (node[x].r) node[x].dis=node[node[x].r].dis+1;
    else node[x].dis=0;
    return x;
}
inline int Delete(int x){
    int lc=node[x].l,rc=node[x].r;
    node[x].clear(),fa[lc]=lc,fa[rc]=rc;   //当前根节点被删，则左右子树的根节点就为其本身。
    return merge(lc,rc);    //弹出当前两个子树合并后新的树的根节点
}
int main(){
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    while (scanf("%d",&n)!=EOF){
        for (int i=1;i<=n;i++)
            node[i].w=read(),node[i].clear(),fa[i]=i;
        m=read();
        for (int i=1;i<=m;i++){
            int x=read(),y=read();
            x=get_fa(fa[x]),y=get_fa(fa[y]);
            if (x==y){ printf("%d\n",-1); continue;}
            node[x].w/=2,node[y].w/=2;
            int left=Delete(x),right=Delete(y);   //分别存左右子树根节点
            left=merge(left,x),right=merge(right,y);
            left=merge(left,right);
            printf("%d\n",node[left].w);
        }
    }
    return 0;
}
```

---

## 作者：gyh20 (赞：3)

因为这道题涉及到多次查找最小值，自然会想到用堆。
但这道题不仅需要查找最小值，还需要合并，自然会想到——
## 可并堆
可并堆有很多种，这里我选用左偏树。

所谓左偏树，就是通过一些~~玄学~~方法使一棵树左边的节点合理地多，合并时合并到右子树既可降低复杂度。

再加上并查集维护每个点所属堆。


代码如下：
```c
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 100002
using namespace std;
int a[N],b,n,c,m,k,l,ls[N],rs[N],fa[N],dis[N],u,v,t;
inline int read(){
    char v=getchar();
    long long s=0;
    while(v<'0'||v>'9')v=getchar();
    while(v>='0'&&v<='9'){
        s=(s<<3)+(s<<1)+v-'0';
        v=getchar();
    }
    return s;
}
int merge(int x,int y){
	if(!x||!y)return x|y;
	if(a[x]<a[y])swap(x,y);
	rs[x]=merge(rs[x],y);
	if(dis[ls[x]]<dis[rs[x]])swap(ls[x],rs[x]);
	if(!rs[x])dis[x]=0;
	else dis[x]=dis[rs[x]]+1;
	return x;
}
int root(int s){
	if(fa[s]==s)return s;
	fa[s]=root(fa[s]);
	return fa[s];
}
int main(){
while(scanf("%d",&n)!=EOF){
memset(ls,0,sizeof(ls));
memset(rs,0,sizeof(rs));
for(int i=1;i<=n;++i)a[i]=read();
m=read();
for(int i=1;i<=n;++i)fa[i]=i;
for(int i=1;i<=m;++i){
	u=read();
	v=read();
	u=root(u);
	v=root(v);
	if(u==v){
		printf("-1\n");
		continue;
	}
	fa[v]=merge(ls[v],rs[v]);
	ls[v]=0;
	rs[v]=0;
	fa[u]=merge(ls[u],rs[u]);
	ls[u]=0;
	rs[u]=0;
	a[u]>>=1;
	a[v]>>=1;
	t=merge(fa[u],fa[v]);
	t=merge(t,u);
	t=merge(t,v);
	fa[t]=fa[u]=fa[v]=t;
	printf("%d\n",a[t]);
}}
 
 
}

```


---

## 作者：5ab_juruo (赞：2)

一看到合并，很快啊，啪的一下就拍了一个线段树上去。

每个猴子建一个维护值域的线段树，每次进行决斗，就删掉两棵线段树中值最大的节点，再插入一个值减一半的节点，然后合并。

有一点要注意的是如果有两个猴子 $s_i$ 相同时，还要维护当前节点有多少个 $s_i$，只有删掉最后一个 $s_i$ 的时候才删掉这个节点。

同时要一个并查集维护当前节点所在的线段树的根。

可以用经典结论证明这是 $\mathcal{O}(n\log \max s_i)$。

空间要开大一点。为了节省空间可以开栈回收。

```cpp
/* name: Luogu1456
 * author: 5ab
 * created at: 22-08-22 20:43
 */
#include <iostream>
#include <numeric>
using namespace std;

typedef long long ll;
const int max_lgv = 17, max_s = 32768, max_n = 100000;

struct nd
{
	int l, r, mx, mxc;
}
tr[max_lgv*max_n*2];
int stk[max_lgv*max_n*2], ptr[max_n], dsu[max_n], *stp;

inline int nnode(int x)
{
	int tmp = *(--stp);
	tr[tmp].l = tr[tmp].r = -1, tr[tmp].mx = x, tr[tmp].mxc = 1;
	return tmp;
}

inline void delnode(int x)
{
	*(stp++) = x;
}

int build(int l, int r, int pos)
{
	if (l == r)
		return nnode(l);
	int mid = (l + r) >> 1, ret = nnode(pos);
	if (pos <= mid)
		tr[ret].l = build(l, mid, pos);
	else
		tr[ret].r = build(mid + 1, r, pos);
	return ret;
}

inline void chmax(int& a, int b) { if (a < b) a = b; }
inline void pushup(int x)
{
	tr[x].mx = -1;
	if (tr[x].l != -1)
		chmax(tr[x].mx, tr[tr[x].l].mx);
	if (tr[x].r != -1)
		chmax(tr[x].mx, tr[tr[x].r].mx);
}

void rmnode(int& id, int l, int r, int pos)
{
	if (l == r)
	{
		tr[id].mxc--;
		if (!tr[id].mxc)
		{
			delnode(id);
			id = -1;
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		
		if (pos <= mid)
			rmnode(tr[id].l, l, mid, pos);
		else
			rmnode(tr[id].r, mid + 1, r, pos);
		
		if (tr[id].l == -1 && tr[id].r == -1)
		{
			delnode(id);
			id = -1;
		}
		else
			pushup(id);
	}
}

int query(int id, int l, int r)
{
	if (l == r)
		return l;
	int mid = (l + r) >> 1;
	
	if (tr[id].r != -1)
		return query(tr[id].r, mid + 1, r);
	return query(tr[id].l, l, mid);
}

void merge(int &x, int y, int l, int r)
{
	if (x == -1 || y == -1)
	{
		x = x + y + 1;
		return;
	}
	if (l == r)
	{
		tr[x].mxc += tr[y].mxc;
		return;
	}
	int mid = (l + r) >> 1;
	merge(tr[x].l, tr[y].l, l, mid);
	merge(tr[x].r, tr[y].r, mid + 1, r);
	pushup(x);
}

int fnd(int x)
{
	return dsu[x] = (dsu[x] == x ? x : fnd(dsu[x]));
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m, ptc;
	
	while (cin >> n)
	{
		ptc = n * max_lgv * 2;
		iota(stk, stk + ptc, 0);
		iota(dsu, dsu + n, 0);
		stp = stk + ptc;
		
		for (int i = 0, x; i < n; i++)
		{
			cin >> x;
			ptr[i] = build(0, max_s, x);
		}
		
		cin >> m;
		for (int i = 0, x, y, rx, ry, cx, cy; i < m; i++)
		{
			cin >> x >> y;
			rx = ptr[fnd(--x)], ry = ptr[fnd(--y)];
			if (rx == ry)
			{
				cout << "-1\n";
				continue;
			}
			
			cx = query(rx, 0, max_s), cy = query(ry, 0, max_s);
			rmnode(rx, 0, max_s, cx), rmnode(ry, 0, max_s, cy);
			merge(rx, build(0, max_s, cx / 2), 0, max_s), merge(ry, build(0, max_s, cy / 2), 0, max_s);
			merge(rx, ry, 0, max_s);
			dsu[fnd(y)] = fnd(x), ptr[fnd(x)] = rx;
			
			cout << query(rx, 0, max_s) << "\n";
		}
	}
	
	return 0;
}
```

---

## 作者：fzwfzwfzw (赞：2)

# 这一道题就是使用的正常的可并堆

##  可并堆就是可以合并的堆

在合并前后都可以保持堆的性质，可以是小根堆也可以是大根堆。


### so

我们要使用一些神奇的数据结构来维护这些堆

## 目前可以维护可并堆的有：左偏树，斜堆……

其实还有很多我就不一一介绍了

今天我们来探讨一下左偏树

### 这道题题面意思是给每个猴子和他认识的人一起维护一个大根堆；
然后每一次修改就是将两个大根堆的堆顶取出，并将战斗力除以二，

插入合并的两个堆中；

所以我们需要维护左偏树。

```c
int hebing (int a,int b)
{
	if(!a)return b;//如果有一个是空堆就返回
	if(!b)return a;
	if(key[a]<key[b])swap(a,b);//保持左偏树性质
	rc[a]=hebing(rc[a],b);//迭代向下合并
	if(date[rc[a]]>date[lc[a]])swap(lc[a],rc[a]);//继续维持性质
	date[a]=date[rc[a]]+1;//进行合并
	return a;//返回合并后的一共大小
}
```
这是左偏树的核心代码

十分明（通）了（俗）简（易）洁（懂）；

```c
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int lc[maxn],rc[maxn],date[maxn],key[maxn],fa[maxn];
int hebing (int a,int b)
{
	if(!a)return b;//如果有一个是空堆就返回
	if(!b)return a;
	if(key[a]<key[b])swap(a,b);//保持左偏树性质
	rc[a]=hebing(rc[a],b);//迭代向下合并
	if(date[rc[a]]>date[lc[a]])swap(lc[a],rc[a]);//继续维持性质
	date[a]=date[rc[a]]+1;//进行合并
	return a;//返回合并后的一共大小
}
int ff(int x)//寻找父亲
{
	return (fa[x]==x)?x:ff(fa[x]);
    /*
    	相当于
    	if(fa[x]!=x)return ff(fa[x]);
        else return x;
    */
}
inline int read(){//读入优化
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
void work(int a,int b)//根据题目来完成输出
{
	if((a=ff(a))==(b=ff(b)))//特判
	{
		cout<<"-1"<<endl;
		return ;
	}
    //合并
    //只要看懂核心代码就可以明白
	fa[b]=a;
	int art;
	int rt;
	int brt;
	key[a]>>=1;
	rt=hebing(lc[a],rc[a]);
	lc[a]=rc[a]=date[a]=0;
	art=hebing(a,rt);
	fa[rt]=fa[a]=art;
	key[b]>>=1;
	rt=hebing(lc[b],rc[b]);
	lc[b]=rc[b]=date[b]=0;
	brt=hebing(b,rt);
	fa[rt]=fa[b]=brt;
	rt=hebing(art,brt);
	fa[art]=fa[brt]=rt;
	printf("%d\n",key[rt]);
}
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{for(int i=1;i<=n;i++)
	{
		lc[i]=rc[i]=date[i]=0;
		fa[i]=i;
		key[i]=read();
	}
	int m=read();
	for(int i=1;i<=m;i++)
	{
		work(read(),read());
	}
	}
	return 0;
}
```


这道题就这样完成了
# 祝大家 AK IOI


---

## 作者：Mr_浓氨 (赞：2)

这道题，我看了半天都是一道NP问题啊（当时我没学数据结构QAQ）

自从学了左偏树之后顿时打开了一扇新的大门，这道题左偏树模板体，就是能力值减半有点麻烦，那么就把这个节点直接脱离出来减半后再重新merge就行了阿（我是不会说我想了很久的）

就像这样

```cpp
tree[xx].val/=2;
ll root=merge(tree[xx].lc,tree[xx].rc);
tree[xx].lc=0;
tree[xx].rc=0;
ll newx=merge(root,xx);
tree[yy].val/=2;
root=merge(tree[yy].lc,tree[yy].rc);
tree[yy].lc=0;
tree[yy].rc=0;
ll newy=merge(root,yy);
root=merge(newx,newy);
tree[newx].fa=root;
tree[newy].fa=root;
printf("%lld\n",tree[root].val);
```

剩下的就是纯模板体了

直接上代码（不要在意del是什么，我是敲完了模板后来敲得这个QAQ）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
	ll val,lc,rc,dis,fa;
}tree[10000001];
int cnt;
int n,m;
inline ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
inline ll merge(ll x,ll y)
{
	if(x==0)
	{
		return y;
	}
	if(y==0)
	{
		return x;
	}
	if(tree[x].val<tree[y].val||(tree[x].val==tree[y].val&&x>y))
	{
		swap(x,y);
	}
	tree[x].rc=merge(tree[x].rc,y);
	tree[tree[x].rc].fa=x;
	if(tree[tree[x].rc].dis>tree[tree[x].lc].dis)
	{
		swap(tree[x].rc,tree[x].lc);
	}
 	if(tree[x].rc==0)
	{
		tree[x].dis=0;
	}
	else
	{
		tree[x].dis=tree[tree[x].rc].dis+1;
	}
	return x;
}
inline void del(ll x)
{
	ll l=tree[x].lc,r=tree[x].rc;
	tree[x].fa=tree[x].lc=tree[x].rc=tree[x].dis=0;
	tree[x].val=-20030711;
	tree[l].fa=l,tree[r].fa=r;
	merge(l,r);
	return;
}
inline ll find(ll x)
{
	ll xx=x;
	while(xx!=tree[xx].fa)
	{
		xx=tree[xx].fa;
	}
	return xx;
}
ll a[1000001];
int main()
{
	while(cin>>n)
	{
		for(int i=0;i<=n;i++)
		{
			tree[i].lc=tree[i].rc=tree[i].dis=0;
			tree[i].fa=i;
		}
		for(int i=1;i<=n;i++)
		{
			tree[i].val=read();
		}
		m=read();
		for(int i=1;i<=m;i++)
		{
			ll x=read(),y=read();
			ll xx=find(x),yy=find(y);
			if(xx==yy)
			{
				printf("-1\n");
			}
			else
			{
				tree[xx].val/=2;
				ll root=merge(tree[xx].lc,tree[xx].rc);
				tree[xx].lc=0;
				tree[xx].rc=0;
				ll newx=merge(root,xx);
				tree[yy].val/=2;
				root=merge(tree[yy].lc,tree[yy].rc);
				tree[yy].lc=0;
				tree[yy].rc=0;
				ll newy=merge(root,yy);
				root=merge(newx,newy);
				tree[newx].fa=root;
				tree[newy].fa=root;
				printf("%lld\n",tree[root].val);
			}
		}
	}
	return 0;
}

```

---

## 作者：ViXpop (赞：1)

刚自学完一波左偏树，发现这题比较像板子就来做一发

如果有对左偏树不太了解的神仙，请往[这边](https://www.luogu.org/problemnew/show/P3377)走

#### 实际上这题只需要用一个可合并的堆就行，不一定非要是左偏树

例如斐波那契堆也是可行的（蒟蒻表示不会qwq），又比如pd_ds（就是一个自动的可合并堆）

这题的输入比较duliu，对于喜欢快读的蒟蒻很不友好......

### 思路很简单，打完架直接更新树然后输出即可

更新的过程简单说明一下：

两边阵营打完架之后，原本最强的猴子战斗力减半，然后寻找出当前最强的猴子作为这边的根，再处理一下父亲节点和子节点的关系，另一边也进行同样的操作

最后将两个堆进行合并，更新结束

#### 下面上代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#define mem(i,j) memset(i,j,sizeof(i))
#define Endl printf("\n")
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e6+5;
int n,m,val[N],ch[N][2],fa[N],dis[N],roox,rooy,root;
//val存点权，dis存距离（关于距离的定义请移步模板题解处）
int merge(int x,int y){//左偏树合并
    if(!x||!y)return x+y;
    if(val[x]<val[y])swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    fa[ch[x][1]]=x;
    if(dis[ch[x][0]]<dis[ch[x][1]])swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}
int findf(int x){//并查集判断双方是否认识
    if(fa[x]==x)return x;
    fa[x]=findf(fa[x]);
    return fa[x];
}
void init(){
    mem(dis,0),mem(ch,0);
    root=0,roox=0,rooy=0;
}
int main(){
    while(scanf("%d",&n)!=EOF){//就是这里卡快读qaq
        init();//多测不清空，爆零两行泪
        for(register int i=1;i<=n;i++)fa[i]=i,val[i]=read();
        m=read();
        for(register int i=1;i<=m;i++){
            int l=read(),r=read(),fl=findf(l),fr=findf(r);
            if(fl==fr){//如果两个猴子本来就认识
                write(-1);Endl;continue;
            }
            //更新
            val[fl]/=2;
            roox=merge(ch[fl][0],ch[fl][1]);
            ch[fl][0]=ch[fl][1]=0;
            fa[ch[fl][0]]=fa[ch[fl][1]]=roox;
            roox=merge(roox,fl);
            val[fr]/=2;
            rooy=merge(ch[fr][0],ch[fr][1]);
            ch[fr][0]=ch[fr][1]=0;
            fa[ch[fr][0]]=fa[ch[fr][1]]=rooy;
            rooy=merge(rooy,fr);
            root=merge(roox,rooy);
            fa[roox]=fa[rooy]=root;
            write(val[root]),Endl;
        }
    }
    return 0;
}

```


---

## 作者：Jμdge (赞：1)

刚做完板子就把(bei)这题cao掉了(调了一会儿, CE*1, 没有秒过, 道行尚浅.)

不废话了...讲题

这就是道70%的板子题，没有删除，有的是修改+维护~~+套路~~
```
每次打架前先并查集(无路径压缩)得到 x 和 y 的 father ,
然后 key[fx]>>=1, key[fy]>>=1, 维护一下所在的堆,
再将两个新的堆合并，输出新堆的根的key
```

```cpp
//by Judge
#include<algorithm>
#include<cstring>
#include<cstdio>
#define swap(a,b) (a)^=(b)^= a^=b
const int M=1e5+11;
int n,m,i;
int key[M],dis[M],f[M],son[M][2];
int find(int x){ return f[x]?find(f[x]):x; }  无合并并查集
int merge(int u,int v){  //合并, 板子就不解释了
	if(!u || !v) return u|v; if(key[u]<key[v]) swap(u,v);
	int &ul=son[u][0],&ur=son[u][1]; ur=merge(ur,v),f[ur]=u;
	if(dis[ul]<dis[ur]) swap(ul,ur); dis[u]=dis[ur]+1; return u;
}
inline int change(int u){
	key[u]>>=1; int ul=son[u][0], ur=son[u][1];
	f[ul]=f[ur]=son[u][0]=son[u][1]=0;  //先暂时删除与 u 有关的全部信息
    ul=merge(ul,ur),u=merge(u,ul); return u; //然后合并 u 的两个孩子, 再合并 u 和 之前合并得到的根ul, 返回新堆的根编号
}
int main(){
	int i,x,y,fx,fy;
	while(~scanf("%d",&n)){
		for(i=1;i<=n;++i) //注意清零, dis不用
			f[i]=son[i][0]=son[i][1]=0;
		for(i=1;i<=n;++i) scanf("%d",key+i);
		for(scanf("%d",&m),i=1;i<=m;++i){
			scanf("%d%d",&x,&y),
            fx=find(x),fy=find(y); //并查集 get father
            if(fx==fy){  //判断 fx 和 fy 关系,如题
            	puts("-1"); continue; 
            }
			fx=change(fx),fy=change(fy), //更新两个堆
            fx=merge(fx,fy),printf("%d\n",key[fx]); //合并两个堆,输出新堆中根的key
		}
	} return 0;
}
```

---

## 作者：安好 (赞：1)

/\*
每次给出要争吵的猴子a和b，用并查集判断如果他们是朋友输出-1

如果不是，找出a，b在的堆的根A，B，分别合并A，B的左右孩子，再合并一下。

之后把A，B的数据更改一下：权值除以2，左右孩子设为0，再插入到堆中即可。

最后输出堆顶。

\*/






```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100005;
int m,n;
int set[N];
struct node
{
    int l,r,dis,key;
}tree[N];
int find(int x) {return set[x] == x ? x : set[x] = find(set[x]);}
int merge(int a,int b)
{
    if(!a)
        return b;
    if(!b)
        return a;
    if(tree[a].key < tree[b].key)//大堆
        swap(a,b);
    tree[a].r = merge(tree[a].r,b);
    set[tree[a].r] = a;//并查
    if(tree[tree[a].l].dis < tree[tree[a].r].dis)
        swap(tree[a].l,tree[a].r);
    if(tree[a].r)
        tree[a].dis = tree[tree[a].r].dis + 1;
    else
        tree[a].dis = 0;
    return a;
}
int pop(int a)
{
    int l = tree[a].l;
    int r = tree[a].r;
    set[l] = l;//因为要暂时删掉根，所以左右子树先作为根
    set[r] = r;
    tree[a].l = tree[a].r = tree[a].dis = 0;
    return merge(l,r);
}
int nextint()
{
    char c;
    int ret = 0;
    while((c = getchar()) > '9' || c < '0')
        ;
    ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9')
        ret = ret * 10 + c - '0';
    return ret;
}
void print(int a)
{
    if(!a)
        return;
    print(a/10);
    putchar(a%10 + '0');
}
int main()
{
    int a,b,i;
    while(~scanf("%d",&n))
    {
        for(i = 1;i <= n;i ++)
        {;
            tree[i].key = nextint();
            set[i] = i;
            tree[i].l = tree[i].r = tree[i].dis = 0;
        }
        m = nextint();
        while(m --)
        {
            a = nextint();
            b = nextint();
            int ra = find(a);
            int rb = find(b);
            if(ra == rb)
                printf("-1\n");
            else
            {
                int rra = pop(ra);//ra左右子树合并
                tree[ra].key /= 2;
                ra = merge(rra,ra);//重新插入ra 找到合适的位置
                int rrb = pop(rb);
                tree[rb].key /= 2;
                rb = merge(rrb,rb);
                print(tree[merge(ra,rb)].key);
                putchar(10);
            }
        }
    }
    return 0;
}
```

---

## 作者：1234KID (赞：0)

             
              
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
struct node{  
    int v,l,r;  //v能量值，l表示左指数，r 表示右指数 
};  
struct node a[100000+10];  
int m,n,f[100000+10],dist[100000+10];  //dist表示距离,f表示父亲节点 
int mg(int x,int y){  
    if(x==0)return y; //一个节点为空，输出另一个节点 
    if(y==0)return x;  
    if(a[y].v>a[x].v){  //要将y放入x中则,则y的能量值小 
        int tmp;tmp=x;x=y;y=tmp;  
    }  
    a[x].r=mg(a[x].r,y);  //将一个y树接在x的右子树上 
    f[a[x].r]=x; //将x为首领。==合并 
    if(a[x].r==0)dist[x]=0;  //距离 
    else dist[x]=dist[a[x].r]+1;//运用左偏树的性质  
    if(dist[a[x].r]>dist[a[x].l]){  
        int tmp;  
        tmp=a[x].r;a[x].r=a[x].l,a[x].l=tmp;  //当左边大于右边，交换 
    }  
    return x;  
}  
int find(int x){  
    if(f[x]==x)return x;  
    else return f[x]=find(f[x]);   
}  
int main(){  
    while(scanf("%d",&n)!=EOF){  //输入 
        for(int i=1;i<=n;i++)a[i].l=a[i].r=0;//每个都独立  
        for(int i=1;i<=n;i++)f[i]=i;  //首领为自己 
        for(int i=1;i<=n;i++)scanf("%d",&a[i].v); //输入每只猴子的能量值 
        scanf("%d",&m);  //m次战斗的机会 
        for(int i=1;i<=m;i++){  
            int x,y;  
            scanf("%d%d",&x,&y);  //第几个猴群与第几个战斗 
            int fx,fy;  
            fx=find(x);fy=find(y);  //找首领 
            if(fx==fy){  
                printf("-1\n");continue;  //同一群 
            }    
            int tmp;  
            a[fx].v/=2;  //第一个首领 
            tmp=mg(a[fx].l,a[fx].r);//合并 
            a[fx].r=a[fx].l=0;  //将首领孤立 
            int nx=mg(tmp,fx);  //首领重新放入数组，重新选首领 
            a[fy].v/=2;  //另一个 
            tmp=mg(a[fy].l,a[fy].r);//合并 
            a[fy].r=a[fy].l=0;  //将首领拿出 
            int ny=mg(tmp,fy);  //重新放入左偏树中 
            tmp=mg(nx,ny);  //合并两堆猴子 
            f[nx]=f[ny]=tmp;  //tmp为新首领 
            printf("%d\n",a[tmp].v);  //输出新首领的能量值 
        }  
    }     
}
```

---

