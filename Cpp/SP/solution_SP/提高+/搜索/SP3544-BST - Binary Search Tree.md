# BST - Binary Search Tree

## 题目描述

众所周知，二叉搜索树是一棵树，其中每个节点最多具有两个子节点（左子节点和右子节点）。

二叉搜索树的每个节点都有一个权值。对于每个节点如果存在一个权值$X$，则其左子树中的权值小于$X$，右子树中的权值大于$X$.

现在给你一个$1$~$N$（包括$N$）之间的整数序列，其中保证每个数字在序列中只出现一次。

请你将序列建成一颗二叉搜索树，我们规定将第一个数字的值存在根节点中，并按给定的序列顺序插入其他数字。

换句话说，你需要对每个插入的数字运行函数$insert(X$，$root)$：

该函数伪代码如下：

	插入（编号X，节点N）

 		将计数器C增加1      

    	 if X小于节点N中的权值        

        	if N没有左子节点           

            	创建一个权值为X的新节点，并将其设置为节点N的左子节点          
        	else insert（X，节点N的左子节点） 
    	 else if （X大于节点N中的权值） 

        	if N没有右子节点              

            	创建一个权值为X的新节点，并将其设置为节点N的右子节点      

        	else insert（X，节点N的右子节点） 

请你编写一个程序，计算在依次插入每个数字后计数器$C$的值并输出。计数器$C$最初为$0$。

## 样例 #1

### 输入

```
8
3
5
1
6
8
7
2
4```

### 输出

```
0
1
2
4
7
11
13
15```

# 题解

## 作者：___new2zy___ (赞：14)

## 题解 SP3544 【BST - Binary Search Tree】

题目传送门：

https://www.luogu.org/problemnew/show/SP3544

这题。。。题目迷惑性很大

不得不说是一道够毒的题。。。但是脑洞还是很大的

================================================================

先扯一些没用的东西。。。

这题是我们同学没事闲的跳到的。。。然后就开始尝试切掉

可能是我太$pupil$了，一上来就按着题目的“指示”打了个$BST$，结果$T$到死$233$

本来以为是个$BST$的板子题，来练练手，结果我的一下午就这样过去了233

~~（我不会告诉你我把我同学的做法卡下去了嘿嘿嘿）~~

那就来讲一下如何做吧

这题上来就丢给我们一个$BST$的$insert$函数的板子

之后就问我们（其实也是**题目大意**）：

向一个最初为空的$BST$中依次插入一个给定的数列，其中每一次调用$insert$函数都给计数器$C$加上$1$，试求每次插入完数之后计数器$C$的值

$emmm$。。。看完题发现好像可以模拟？（想必大部分人都是我这么想的吧）

我们直接模拟一下题面里的$insert$函数交上去，会发现完美地$T$掉了

其实仔细想一下都可以知道，这题肯定没有这么简单

~~（怎么能让你简简单单地过掉一道题呢QAQ）~~

我们知道对于一个普通的$BST$，当向其中**插入一个有序数列**时，$BST$会退化成一条链，因此它的$insert$函数的单次时间复杂度会变成$O(n)$的，那么插入$n$个数最后就是$O(n^2)$的，又因为$n<=300000$，于是$O(n^2)$是妥妥的$T$掉了

不妨。。。换个思路？

换位思考一下，我们何必维护一颗$BST$呢 

对于一颗$BST$，可以证明的是，对于要插入的数$x$

**$x$只会最终接在$x$的前驱或后继的下一层**，这是十分显然的 

而且**$x$最终一定是这两者中深度较大的那一个的儿子节点上**

况且对于$x$的前驱和后继，**$x$的前驱一定是$x$的后继的祖先 **
    
那么我们就不必建立一颗$BST$去模拟过程 

而是可以**每次二分$O(logn)$的寻找$x$的前驱和后继 **

找到$x$的**前驱和后继二者深度最大的那个**，**其深度$+1$即为$x$的深度**  

**对答案的贡献其实就是这个深度**，**累加**起来即可

可以直接建立$map$，在$map$内存上每个数的$dep$和值$(key)$

之后在$map$内$lower$_$bound$查找就行了

又由于$lower$_$bound$单次复杂度是$O(logn)$的 

那么最终插入完整个序列则是$O(nlogn)$的 

写完之后发现好像有点不太好。。。可能数据稍微大一些就死了

但是总感觉这个过程可以用别的方法来写

或许还有$O(n)$做法吧。。。可是我太菜了想不出。。。

也许等我想出了$O(n)$做法就来更新一下题解233

到这里大概也就讲完了。。。

如果不会$c++ map$自带的$lower$_$bound$请去问度娘

~~（我也没有什么好的链接233）~~

下面放两个代码，第一个是最开始做的时候的代码（比较慢），第二个是（丧心病狂）卡完常之后的代码

本人代码丑，各位$dalao$不喜勿喷

code1:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
//const int maxn=3e5+3;
int n;
ll ans;
map <int,int> dep;
map <int,int>::iterator it;
int main()
{
	/*（以下是我写题的时候的心路历程）
	分析：
	可以发现这题直接模拟是肯定会挂的
	因为n<=300000,而数据又是不一定的
	可能出现一个有序序列使得每次插入元素都是O(n)的 
	那么累加起来就是个O(n^2)的模拟算法
	显然复杂度不可接受 
	
	那么不妨换位思考一下 
	我们何必维护一颗二叉搜索树呢 
	由于这是一颗BST
	可以证明的是,对于一个序列中的要插入的数x 
	它只会最终接在x的前驱或后继的下一层,这是十分显然的 
	而且x最终一定是这两者中深度较大的那一个的儿子节点上
	况且对于x的前驱和后继,一定有x的前驱是x的后继的祖先 
	
	那么我们其实就不必建立一颗BST去模拟过程 
	而是每次在map中O(logn)的寻找x的前驱和后继 
	找到一个二者深度最大的位置+1即为x的深度
	
	对答案的贡献其实就是这个深度,累加起来即可
	那么直接建立map,之后在map内lower_bound查找就行了
	lower_bound单次复杂度是O(logn)的 
	那么最终插入完整个序列则是O(nlogn)的 
	
	可能还有O(n)做法吧。。。可是我太菜了想不出。。。 
	*/
	n=read();
	for(int i=1;i<=n;i++)
		{
			int x=read(),pos=0,new_dep1,new_dep2;
			it=dep.lower_bound(x);//找到第一个>=x的数 
			if(it!=dep.end())//存在一个第一个>=x且已经插入了的数 
				{
					new_dep1=it->second+1;
					pos=max(pos,new_dep1);
//					printf("\nQAQ %d\n",it->first);
				}
			if(it!=dep.begin())//找不到一个>=x的数,则找第一个<x的数的位置 
				{
					new_dep2=(--it)->second+1;
					pos=max(pos,new_dep2);
//					printf("\nQWQ %d\n",it->first);
				}
			dep[x]=pos,ans+=pos;
			//在较深的位置插入节点,并累加新的深度贡献 
			printf("%lld\n",ans);
		}
	return 0;
}
```

code2:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
#define re register
using namespace std;
typedef long long ll;
char IN[1<<17],*SS=IN,*TT=IN;
inline char gc(){return (SS==TT&&(TT=(SS=IN)+fread(IN,1,1<<17,stdin),SS==TT)?EOF:*SS++);}
inline int read()
{
	int now=0,f=1;re char c=gc();
    for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
    for(;isdigit(c);now=now*10+c-'0',c=gc());
    return now*f;}
int n;
ll ans;
map <int,int> dep;
map <int,int>::iterator it;
int main()
{
	n=read();
	for(re int i=1;i<=n;i++)
		{
			int x=read(),pos=0;
			it=dep.lower_bound(x);
			if(it!=dep.end())pos=max(pos,it->second+1);
			if(it!=dep.begin())pos=max(pos,(--it)->second+1);
			dep[x]=pos,ans+=pos;
			printf("%lld\n",ans);
		}
	return 0;
}
```

大概。。。这题就到这里了吧。。。

=================================================================

### 前方高能预警！

$upd$：2018年9月28日（其实就是做完之后1个半小时以后233）

上面的$map$做法写完之后我又回去思索了一下

大概想了想优化。。。最开始感觉没啥可以优化的

但是总觉得$O(nlogn)$有点扯，数据大真的会挂

毕竟在$SPOJ$上我的$O(nlogn)$都进不了$rk$前$20$

所以滚回来再想一想优化方法。。。

仔细想了一想（大概又过了1个半小时吧）发现好像可以$O(n)$

我上面也说可能有一种$O(n)$的方法，但是当时没想出来，所以写的是$O(nlogn)$的

但是现在，$O(n)$做法终于搞完辣！

先公布一下好结果：$O(n)$做法在$SPOJ$上杀到了$c++4.3.2$的$rk$ $1!$

（我的$SPOJ$用户名:$new2zy$）

其实自己都没想到能$rk$ $1$的。。。

行了，不说没用的了，直接开讲

上面的思路很清晰了，对于每一个要插入的数找到前驱和后继就行了

但是发现$map$的$lower$_$bound$是$O(nlogn)$的，我们想能不能改进一下，使它的效率能大大提高，甚至变成$O(1)$的

而对于找前驱和后继的问题，貌似也就只能想到平衡树了233

可能我是因为我不会平衡树的原因~~（我还是太菜了）~~，我想到了另外一种东西：**链表**

因为链表是一个链状结构，每一个节点都有一个前驱节点和后继节点

发现正好符合上面的要求：**对于一个数要找前驱和后继**

那么我们不妨换个思路，**倒着来 **

（我用了数组模拟链表）

对于一个初始有$n$个节点的链表，我们要在其中**删除数 **

删除一个数（所在节点）后，它原位置的前驱和后继的指针会随之更新 

那么**在删除前它的前驱和后继肯定也是固定的**

我们只需**要倒序删掉所有数**,同时**记下每个数前驱后继就行了**

**最后正着**还是按$depth[i]=max(depth[pre],depth[nex])+1$算就行了 

也是**累加贡献**，即为每一次的答案

考虑一下这个算法的**时间复杂度**：

由于每个元素在链表中只被删除一次，所以复杂度是$O(n)$的 

那么。。。这就是改进之后的算法了

这样就再也不用效率低的$map$了

可能自己又口胡了一个神奇做法？结果神奇的过掉了233

下面还是放两个代码，一个是我写的第一个优化（带注释版），另一个是过掉之后的卡常版

还是那句话，本人代码丑，各位dalao不喜勿喷

code3:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=1e9+7;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
const int maxn=300003;
int n,opt[maxn],L[maxn],R[maxn],dep[maxn],pre[maxn],nex[maxn];
ll ans;
int main()
{
    /*
    分析：上一次写的用了map
    效率比较低(主要是SPOJ不给开O2所以很慢233) 
    这次又想到一个貌似是O(n)的算法,再来改造一下。。。 
    
    思考发现,对于一个数肯定要找前驱和后继
    那么我们不妨换个思路,倒着来 
    对于一个初始的链表,我们在其中删除数 
    它原位置的前后指针会随之更新 
    那么在删除前它的前驱和后继肯定也是固定的
    我们只需要倒序删掉所有数,同时记下前驱后继就行了
    最后正着还是按depth[i]=max(depth[pre],depth[nex])+1算就行了 
    最终也是累加贡献
    由于每个元素在链表中只被删除一次,所以复杂度是O(n)的 
    */
    n=read();
    for(int i=1;i<=n;i++)//初始化链表 
        {
            opt[i]=read();
            L[i]=i-1,R[i]=i+1;
        }
    L[1]=0,R[n]=0,dep[0]=-1;
    for(int i=n;i>=1;i--)//逆序删除数字 
        {
            pre[opt[i]]=L[opt[i]];
            nex[opt[i]]=R[opt[i]];
            //记下每个删除的数的前驱和后继 
            R[L[opt[i]]]=R[opt[i]];
            L[R[opt[i]]]=L[opt[i]];
            //在链表中删除这个数 
        }
    for(int i=1;i<=n;i++)
        {
            dep[opt[i]]=max(dep[pre[opt[i]]],dep[nex[opt[i]]])+1;
            ans+=dep[opt[i]];//更新深度,累加贡献 
            printf("%lld\n",ans);
        }
    return 0;
}
```
code4:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define re register
using namespace std;//register吼啊 
typedef long long ll;
const int inf=1e9+7;
char IN[1<<17],*SS=IN,*TT=IN;
inline char gc(){return (SS==TT&&(TT=(SS=IN)+fread(IN,1,1<<17,stdin),SS==TT)?EOF:*SS++);}
inline int read()//fread一发入魂 
{
    int now=0,f=1;re char c=gc();
    for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
    for(;isdigit(c);now=now*10+c-'0',c=gc());
    return now*f;}
const int maxn=300003;
int n,opt[maxn],L[maxn],R[maxn],dep[maxn],pre[maxn],nex[maxn];
ll ans;
int main()
{
    n=read();
    for(re int i=1;i<=n;i++)
        {
            opt[i]=read();
            L[i]=i-1,R[i]=i+1;
        }
    L[1]=0,R[n]=0,dep[0]=-1;
    for(re int i=n;i>=1;i--)
        {
            pre[opt[i]]=L[opt[i]];
            nex[opt[i]]=R[opt[i]];
            R[L[opt[i]]]=R[opt[i]];
            L[R[opt[i]]]=L[opt[i]];
        }
    for(re int i=1;i<=n;i++)
        {
            dep[opt[i]]=max(dep[pre[opt[i]]],dep[nex[opt[i]]])+1;
            ans+=dep[opt[i]];
            printf("%lld\n",ans);
        }
    return 0;
}
```

或许到这里这题就真的没什么了吧。。。我是真的想不出其他做法了233

最后来对比一下两种做法卡完常前后：

$code2:620ms, 12288KB$

$code4:200ms, 9932KB$

果然。。。$STL$要慎用啊。。。真的慢到家了

希望有人把我的$code4$卡下去，至少到2018年9月28日还是$luogu$和$SPOJ$的$rk$ $1$

最后，做完发现，这题的脑洞其实还是挺大的。。。希望大家能好好做

还有就是。。。不要让题目迷惑了双眼QAQ

还要注意算法效率的改进和提升！

最后，感谢你的阅读！

最后的最后。。。~~无耻的~~推一波我的blog：

https://www.luogu.org/blog/new2zy/

拜拜~~~



---

## 作者：Emplace (赞：5)

## 算法
我们可以用链表来做这道题。

## 化简问题
我们可以对于一个数，找比它小的与编号与他最近。和比他大的与他编号最近的。然后对于这个数，一定是插在这两个数中深度最深的那个。
## 解决问题
我们可以先建一条链表，然后把每个数都连起来,设第 $i$ 数的右指针为 $ rt_i $，左指针为 $ lt_i $，而比它小并与他编号最近的为 $ l_i $ 而比它大并与他编号最近的为 $ r_i $，而每个数为 $ a_i$。然后倒着枚举每个数，对于第 $ i $ 个数，$l_{a_i}=lt_{a_i}$，$r_{a_i}=rt_{a_i}$。这点很好理解。然后我们可以删除掉 $a_i$，因为它的任务就是帮助 $l_i$，与 $r_i$ 赋值，现在它任务完成了自然可以删除了。删除后，我们可以把 $lt_i$ 与 $rt_i$ 连起来。最后答案肯定是每个点的答案就是他的深度，设第 $i$ 个深度为 $d_i$，那么   $d_{a_i}=\max(d_{l_{a_i}},d_{r_{a_i}})+1$。第一个数答案为 $0$，后面第 $k$ 个数，答案为 $ \sum_{i = 1}^{k} \ d_{a_i} $。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[400000],r[400000],lt[400000],rt[400000],n,x,a[400000],d[400000],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		lt[i]=i-1;
		rt[i]=i+1;
	}
	rt[n]=0;
	for(int i=n;i>=1;i--){
		l[a[i]]=lt[a[i]];
		r[a[i]]=rt[a[i]];
		rt[lt[a[i]]]=rt[a[i]];
		lt[rt[a[i]]]=lt[a[i]];
	}
	d[1]=-1;
	cout<<ans<<endl;
	for(int i=2;i<=n;i++){
		d[a[i]]=max(d[l[a[i]]],d[r[a[i]]])+1;
	}
	for(int i=2;i<=n;i++){
		ans+=d[a[i]];
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：laeva (赞：3)

看到这题，首先想到当然是模拟了，但是考虑到300000的数据范围，当然是不可能过，众所周知~~（众所周：我不知）~~二叉查找树时间复杂度可以退化到$n^2$，所以我们需要用一些玄学做法做到$logn$时间内找出计数器增加的值

#### 怎么做呢？

如果我们将第一个加入二叉搜索树点的深度设为$1$，我们应该可以看出，对于剩下加入的点，计数器C增加的值为他父亲节点的深度，例如样例：

![](https://cdn.luogu.com.cn/upload/pic/34585.png)

证明应该很容易吧，某个点被加入树中的时候，将ta到根的之间的点全部经过一遍，也就恰好是ta父亲节点的深度

现在问题变成了我们如何知道一个点的父亲节点的深度呢？

经过~~画了很多的图之~~冷静分析后，我们发现一个点插入到树是，一定是插入在比ta大的节点中最小的一个或者比ta小的节点中最大的一个（即ta的前驱或后继）

考虑插入的数为$x$，插入后$x$是$n$的左儿子也就有$x < n$

如果存在点$y$使得$x < y < n$

分成三种情况：

1. 若$y$是$n$的祖先，则$n$一定在$y$的右子树中，而插入的时候$x$会先遇到$y$，则此时会向$y$的左子树中递归，$x$一定不会成为$n$的子节点，与假设矛盾

2. 若$n$是$y$的祖先，则$y$一定在$n$的左子树中，那么$x$不可能是$n$的左儿子，与假设矛盾

3. 若$y$和$n$在不同的子树中，同理于1，在插入$x$时，会先遇到$lca(n, y)$，会向$lca(n, y)$左子树递归，而$n$在$lca(n, y)$的右子树中，与假设矛盾

综上可知，插入的数为$x$，插入后$x$是$n$的左儿子，则$n$一定是$x$的后继

证明插入后$x$是$n$的右儿子同理

这样我们就只需要查找$x$的前驱或后继就行了，这可以用C++里STL中的set轻松实现，以后的部分应该就很简单了（注意特判插入时$x$是$set$最大或最小的值的情况）

## 奇丑无比的代码：
```cpp
//#include <iostream>
#include <cstdio>
#include <set>

#define MAXN 1000010
#define mod 1000000007
#define INF 2147483600
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define foi(i, a, b) for(register int i = a; i >= b; i--)
typedef long long ll;

namespace Own_math_temp{
template<class _Tp> inline _Tp max(_Tp x, _Tp y) { return x > y ? x : y; }
template<class _Tp> inline _Tp min(_Tp x, _Tp y) { return x < y ? x : y; }
template<class _Tp> inline _Tp abs(_Tp x) { return x > _Tp(0) ? x : _Tp(0) - x; }
}

//using Own_math_temp::max;
//using Own_math_temp::min;
//using Own_math_temp::abs;
using std::set;

/*template<class _Tp> _Tp*/
int read() {
    /*_Tp*/int ans = 0; char ch = getchar(), t = ch;
    while (ch < '0' || ch > '9') { t = ch; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { ans = ans * 10 + ch - '0'; ch = getchar(); }
    /*if (ch == '.') {
        int l = 0.1; ch = getchar();
        while (ch >= '0' && ch <= '9') {
            ans = ans + (ch - '0') * l;l *= 0.1; ch = getchar();
        }
    }*/
    if (t == '-') ans = -ans; return ans;
}

set<int>Q;
set<int>::iterator it, it1, it2;
int deep[MAXN], l[MAXN], r[MAXN];
//deep表示深度，l、r分别表示有无左右儿子但是好像没什么用…… 

int main() {
/*	freopen(".in", "r" ,stdin);
    freopen(".out", "w" ,stdout);*/
    int n = read();
    ll cnt = 0;
    if (n == 1) { printf("0"); return 0; }
    if (n == 2) { printf("1"); return 0; }
    int x = read(); Q.insert(x); deep[x] = 1; printf("0\n"); 
    rep(i, 2, n) {
        x = read(); Q.insert(x);
        it = Q.find(x);
        it1 = it2 = it;
        it1--; it2++;//it1是前驱,it2是后继 
        if (it == Q.begin()) {//特判 
            cnt += 1ll * deep[*it2];
            deep[x] = deep[*it2] + 1;
            l[*it2] = 1; printf("%lld\n", cnt); continue;
        }
        if (it2 == Q.end()) {//特判 
            cnt += 1ll * deep[*it1];
            deep[x] = deep[*it1] + 1;
            r[*it1] = 1; printf("%lld\n", cnt); continue;
        }
        if ((deep[*it1] < deep[*it2] && !r[*it1]) || l[*it2]) { 
            cnt += 1ll * deep[*it1];
            deep[x] = deep[*it1] + 1;
            r[*it1] = 1; printf("%lld\n", cnt); continue;
        }
        else {
            cnt += 1ll * deep[*it2];
            deep[x] = deep[*it2] + 1;
            l[*it2] = 1; printf("%lld\n", cnt); continue;
        }
    }
    return 0;
}
```

---

## 作者：Ericzc (赞：3)

### 题目分析

前面看见很多大佬用单调栈做这道题，可蒟蒻不会，于是就想到用链表，可本蒟蒻还是不会 QWQ ，因此便向大家分享一种蒟蒻的数组模拟的链表的做法。

这道题呢难点就在于怎么用 $O(N)$ 的时间复杂度求出每个插入节点的深度。

为了解决这个难题我们不妨画个图来看一下:

![图演示](https://ykj.cpolar.cn/file/1226/link/6412.jpg)

通过这张图我们不难发现每次插入的深度是当前插入节点中与要插入的节点相邻的两个节点中深度最大的那个节点的深度 $+1$（也就是作为这个节点的子节点）。

照这个思路我们就能开始写代码了。

### Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 10;
int n;
int a[maxn];
int l[maxn];	//第i个节点的左边相邻的数
int r[maxn];	//第i个节点的右边相邻的数
bool vis[maxn];	//标记第i个节点有没有用过
int sc[maxn];	//节点i的深度
long long ans;

int main()
{
	scanf("%d",&n);
	r[0] = n + 1;	//首尾相连
	l[n + 1] = 0;
	sc[0] = -1;		//初始化首尾深度
	sc[n + 1] = -1;
	vis[0] = vis[n + 1] = true;	//首尾打标记
	for(int i = 1;i <= n;i ++)
	{
		scanf("%d",a + i);
	}
	for(int i = 1;i <= n;i ++)
	{
		int k = 1;
		while(!vis[a[i] - k] && !vis[a[i] + k])		//找到与a[i]绝对值最小的节点
		{
			k ++;
		}
		//插入链表
		if(vis[a[i] - k])
		{
			l[a[i]] = a[i] - k;
			r[a[i]] = r[a[i] - k];
		}
		else
		{
			l[a[i]] = l[a[i] + k];
			r[a[i]] = a[i] + k;
		}
		vis[a[i]] = true;	//打标记
		r[l[a[i]]] = a[i];
		l[r[a[i]]] = a[i];
		sc[a[i]] = max(sc[l[a[i]]],sc[r[a[i]]]) + 1;	//记录深度
		ans += sc[a[i]];		//根据题意深度累加
		printf("%lld\n",ans);
	}
	return 0;
}
``` 

看完这个代码，虽然能 AC 但仍是 `for` 套 `while`，那能不能继续优化呢？是可以的。有一句古话叫做“正难则反”，没错，这题我们可以反着做。具体是先将 $0 \sim n+1$ 排列好，在逆序删除节点，这样就可以省去 `while` 循环了，码量比上面这个代码还少，时间复杂度也更小。

---

## 作者：Yxy7952 (赞：2)

## 题目大意
现在有一个 $1\sim n$ 的排列 $a$，将序列中的元素依次放进一个 BST 里，求 BST 中插入函数的执行次数。

注意：第一个数已经作为 BST 的根。

## 思路
暴力模拟肯定会超时，根据二叉搜索树的性质：

>设第 $i$ 个节点的权值 $x$，则其左子树中的权值都小于 $x$，右子树中的权值都大于 $x$。

思考一下可以发现我们每次只需要找到**小于第 $i$ 个数的最大值**，和**大于第 $i$ 个数的最小值**。这时候，这两个数一定是编号为 $i$ 的左右孩子。

因为单调栈刚好可以处理这种问题（‌找到某个数的左右边比它大/小的最近的数‌），所以可以考虑用它解决这道题。又由于 $1\le a_{i}\le n$，$a_{i}$ 互不相同，所以数字可以从 $1$ 开始模拟到 $n$，找到第 $i$ 个数左边比它小的数的最大值，再从 $n$ 开始模拟到 $1$，找到第 $i$ 个数右边比它大的最小值。

**注意**：由于找第 $i$ 个数右边比它大的最小值不能是还没有输入的，所以我们应该找第 $i$ 个数左边比它大的最小值。

干完这一切之后，发现计数器跟深度（从这个节点到根节点的最长路径）有关系，所以只需处理它的深度并输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int i,top,n,stck[maxn],id[maxn],a[maxn],L[maxn],R[maxn],dep[maxn];
long long ans=0;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i],id[a[i]]=i; //id[i]:数i的位置
	a[0]=id[0]=top=stck[top]=0;
	for(i=n;i>=1;i--){//按数值从大到小处理，位置入栈，
		while(top>=0){
			if(stck[top]>id[i]) top--;
			else break;
		}
		R[i]=a[stck[top]];
		stck[++top]=id[i];
	}
	top=0;
	dep[0]=-1;
	for(i=1;i<=n;i++){//按数值从小到大处理，位置入栈
		while(top>=0){
			if(stck[top]>id[i]) top--;
			else break;
		}
		L[i]=a[stck[top]];
		stck[++top]=id[i];
	}//栈里的位置值从小到大
	for(i=1; i<=n; i++) {
		dep[a[i]]=1+max(dep[L[a[i]]],dep[R[a[i]]]);
		ans=ans+dep[a[i]];
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：2)

#### 题意
现在有一个 $1\sim n$ 的排列 $a$，将序列中的元素依次放进一个 BST 里，求 BST 中插入函数的执行次数。

注意：第一个数已经作为 BST 的根。

#### 思路

暴力模拟肯定会超时，根据二叉搜索树的性质，思考一下可以发现**我们每次只需要找到小于第 $i$ 个数的最大值和大于第 $i$ 个数的最小值。**

所以可以考虑用单调栈解决这道题，又由于 $1\le a_i\le n$，$a_i$ 互不相同，所以数字可以从 $1$ 开始模拟到 $n$，找到第 $i$ 个数左边比它小的数的最大值，再从 $n$ 开始模拟到 $1$，找到第 $i$ 个数右边比它大的最小值。

#### 注意：由于找第 $i$ 个数右边比它大的最小值不能是还没有输入的，所以我们应该找第 $i$ 个数左边比它大的最小值。

干完这一切之后，只需计算它的深度即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn = 300005;
int n,k,dep[maxn],l[maxn],r[maxn],a[maxn],x[maxn],d[maxn],cnt = 1;
long long ans;
int main()
{
//   freopen(".in","r",stdin);
//   freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) 
	{
		scanf("%d",&x[i]);
		a[x[i]] = i; 
	} 
	for(int i = 1;i <= n;i++)
	{
		while(a[i] < d[cnt] && cnt > 1) cnt--;
		l[i] = x[d[cnt]];
		d[++cnt] = a[i];
	}
	int cnt = 1;
	for(int i = n;i >= 1;i--)
	{
		while(a[i] < d[cnt] && cnt > 1) cnt--;
		r[i] = x[d[cnt]];
		d[++cnt] = a[i];
	}
	cout << 0 << endl;
	for(int i = 2;i <= n;i++) 
	{
		dep[x[i]] = 1 + max(dep[l[x[i]]],dep[r[x[i]]]);
		ans += dep[x[i]];
		printf("%lld\n",ans);
	}
    return 0;
}
```

---

## 作者：__Ship_ (赞：1)

## 闲话
此题的好兄弟：[BST](https://www.luogu.com.cn/problem/P6412)，同样一道题，没有 SPOJ 的兄弟有福了。

1.**暴力**

题目中直接给出了，所以如下（本人没有写暴力，借了一位同志的）。

[这位同志就是很好的照着写的模板](https://www.luogu.com.cn/record/118616252)

我们发现直接照着写会超时（~~不然为什么是道蓝，直接写模板不就行了~~）。

所以我们来看优化。

2.**单调栈**

因为我们是按照左子树小，右子树高来做，所以左右子树具有单调性。

所以按照从小到大和从大到小做一遍，在记录最大深度位置就是答案。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,id[maxn],a[maxn],l[maxn],r[maxn],dep[maxn],st[maxn];
long long ans=0;
int main(){
//	freopen("bst.in","r",stdin);
//	freopen("bst.out","w",stdout);
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
   		scanf("%d",&a[i]);
		id[a[i]]=i;//id[i]:数i的位置 
    }
    a[0]=0;
    id[0]=0;
    int top=0;
    st[top]=0;
    for(int i = n ; i >= 1 ; i--){
	   //按数值从小到大处理，位置入栈 
        while(top>=0) {
       		if(st[top]>id[i]){
       			top--;
			} 
			else break;
	    }
	    r[i]=a[st[top]];
        st[++top]=id[i];	
    }
    top=0;
   	dep[0]=-1;
   	for(int i = 1 ; i <= n ; i++){
	    //按数值从大到小处理，位置入栈 
	    while(top>=0){
	    	if(st[top]>id[i]){
	    		top--;
			}  
			else break;
		}
		l[i]=a[st[top]];
        st[++top]=id[i];	
   	}
	//栈里的位置值从小到大
   	for(int i = 1 ; i <= n ; i++){ 
	   	dep[a[i]]=1+max(dep[l[a[i]]],dep[r[a[i]]]);
	    ans=ans+dep[a[i]];//计数器C的累加
	    printf("%lld\n",ans);
   	}
	return 0;
}
```

---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/SP3544)

这道题的重点在于 insert 操作的性质。

由于二叉搜索树的性质，新的叶子节点必定会接在第一个比它小的节点或者第一个比它大的节点上，因为第一个比它小的节点要走的路径它都必须走，而如果遇到了第一个比它小的节点的右儿子有节点了，此时我们会走到它的右儿子上面去，会发现最后遇到第一个比它大的节点时，新插入的节点会成为它的左儿子。

由于所有节点值合在一起是一个全排列，不多不少，所以可以保证上述操作的正确性。

维护每个值的第一个比它小的值和第一个比它大的值可以用平衡树来维护，当然，这道题目可以用 map 卡一卡。

时间复杂度 $O(n\log n)$

代码如下：


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<int, int>
#define ll long long
#define vi vector<int>
using namespace std;

const int N = 1e6 + 10;

int n;

map<int, int> mp;

int ls[N], rs[N]; ll ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	L(i, 1, n) {
		int u; cin >> u;
		if(i == 1) {
			mp[u] = 0;
			cout << ans << '\n';
			continue;
		}
		auto y = mp.lower_bound(u);
		pii x = *y, t = *y;
		if(y != mp.begin()) {
			y--;
			x = *y;
			if(!rs[x.first]) {
				rs[x.first] = u;
				ans += x.second+1;
				mp[u] = x.second+1;
				cout << ans << '\n';
				continue;
			}
		}
		x = t;
		ls[x.first] = u;
		ans += x.second+1;
		mp[u] = x.second+1;
		cout << ans << '\n';
	}
	return 0;
}

```

---

## 作者：AC_love (赞：0)

我们知道，BST 的中序遍历一定是一个有序序列，那么我们每次插入一个数的时候，只有可能是插到这个数前驱的右儿子或者这个数后继的左儿子上。

一个重要结论是：一个数的前驱的右儿子和后继的左儿子一定只会存在一个。

如果两个同时存在，那么这个数无处可插。如果两个同时不存在，那么这个数两个地方随便插。这都是不符合 BST 性质的。因此这两个必定只存在一个，找到另一个空缺的位置插进去就行。

代码实现：一个不错的方法是用权值线段树来维护所有节点的数值以及它们有没有左右儿子。同时我们发现权值线段树也非常适合用来找前驱后继。

代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
#define tpl t[p].l
#define tpr t[p].r
#define tpd t[p].dep
#define tph t[p].have
#define tpx t[p].maxn
#define tpn t[p].minn
#define tps t[p].size
#define tpls t[p].leftson
#define tprs t[p].rightson
#define t2pl t[p*2].l
#define t2pr t[p*2].r
#define t2pd t[p*2].dep
#define t2ph t[p*2].have
#define t2px t[p*2].maxn
#define t2pn t[p*2].minn
#define t2ps t[p*2].size
#define t2pls t[p*2].leftson
#define t2prs t[p*2].rightson
#define t2p1l t[p*2+1].l
#define t2p1r t[p*2+1].r
#define t2p1d t[p*2+1].dep
#define t2p1h t[p*2+1].have
#define t2p1x t[p*2+1].maxn
#define t2p1n t[p*2+1].minn
#define t2p1s t[p*2+1].size
#define t2p1ls t[p*2+1].leftson
#define t2p1rs t[p*2+1].rightson
using namespace std;

const int N = 3e5 + 3e4;
const int Null = 1919810;

struct tree
{
	int l;
	int r;
	int dep;
	int size;
	int maxn;
	int minn;
	int leftson;
	int rightson; 
	// ls 记录一个区间最左侧的左儿子
	// rs 记录一个区间最右侧的右儿子 
	bool have;
};

tree t[N * 4];

void pushup(int p)
{
	tph = t2ph || t2p1h;
	tpd = t2pd + t2p1d;
	tps = t2ps + t2p1s;
	tpls = min(t2prs, t2p1rs);
	tprs = max(t2prs, t2p1rs);
	tpx = max(t2px, t2p1x);
	tpn = min(t2pn, t2p1n);
}

void build(int p, int l, int r)
{
	tpl = l;
	tpr = r;
	tpls = Null;
	tprs = -Null;
	tpn = Null;
	tpx = -Null;
	if(l == r)
		return;
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
}

void root(int p, int x)
{
	if(tpl == tpr && tpl == x)
	{
		tph = 1;
		tps = 1;
		tpx = x;
		tpn = x;
		return;
	}
	int mid = (tpl + tpr) / 2;
	if(mid >= x)
		root(p * 2, x);
	else
		root(p * 2 + 1, x);
	pushup(p);
}

bool L, R;
int Findmax(int p, int x)
{
	if(tpl == tpr)
	{
		if(tprs == -Null)
			R = 1,
			tprs = x;
		return tpd;
	}
	if(t2p1n < x)
		return Findmax(p * 2 + 1, x);
	else
		return Findmax(p * 2, x);
	pushup(p);
}

int Findmin(int p, int x)
{
	if(tpl == tpr)
	{
		if(tpls == Null)
			L = 1,
			tpls = x;
		return tpd;
	}
	if(t2px > x)
		return Findmin(p * 2, x);
	else
		return Findmin(p * 2 + 1, x);
	pushup(p);
}

void insert(int p, int x, int dep)
{
	if(tpl == tpr)
	{
		tpd = dep;
		tpx = x;
		tpn = x;
		tph = 1;
		tps = 1;
		return;
	}
	int mid = (tpl + tpr) / 2;
	if(mid >= x)
		insert(p * 2, x, dep);
	else
		insert(p * 2 + 1, x, dep);
	pushup(p);
}

void ins(int x)
// 首先找前驱和后继
// 然后插到前驱和后继中间即可 
// 一定可以证明前驱和后继里一定有且只有一个有至多一个儿子
{
	L = 0;
	R = 0;
	int mx = Findmax(1, x);
	int mn = Findmin(1, x);
	if(L)
	// 插到了后继的左儿子
		insert(1, x, mn + 1);
	else
		insert(1, x, mx + 1);
}


void inslef(int x)
{
	int mn = Findmin(1, x);
	insert(1, x, mn + 1);
}

void insrig(int x)
{
	int mx = Findmax(1, x);
	insert(1, x, mx + 1);
}

int n, node;
int minn, maxn;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	build(1, 1, n);
	cin >> node;
	minn = node;
	maxn = node;
	root(1, node);
	cout << t[1].dep << "\n";
	for(int i = 2; i <= n; i = i + 1)
	{
		cin >> node;
		if(node < minn)
			minn = node, 
			inslef(node);
		else if(node > maxn)
			maxn = node,
			insrig(node);
		else
			ins(node);
//		cout << "     ";
		cout << t[1].dep << "\n";
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

容易发现对于插入 $x$，如果我们找到了 $x$ 的前驱 $p$ 和后继 $n$，那么 $x$ 一定位于 $p$ 或 $n$ 的某个儿子上。

仔细观察，发现 $x$ 会位于 $p$ 和 $n$ 中深度较大的一个的儿子上。

于是我们依次插入每个数，查前驱后继，并且更新深度。

然后可以直接用 `set` 做，然而我写了个 Splay，结果跑得比 `set` 还慢。

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <climits>
#include <string>
using namespace std;

const int N = 3e5 + 5;
long long dep[N];

class Splay
{
public:
	int rt, idx;
	struct Node
	{
		int son[2], fa, sz, cnt, val;
	}tr[N];
	void pushup(int u)
	{
		tr[u].sz = tr[tr[u].son[0]].sz + tr[tr[u].son[1]].sz + tr[u].cnt;
	}
	int get(int u)
	{
		return u == tr[tr[u].fa].son[1];
	}
	void rotate(int x)
	{
		int y = tr[x].fa, z = tr[y].fa;
		int chkx = get(x), chky = get(y);
		tr[y].son[chkx] = tr[x].son[chkx ^ 1];
		if (tr[x].son[chkx ^ 1]) tr[tr[x].son[chkx ^ 1]].fa = y;
		tr[x].son[chkx ^ 1] = y;
		tr[y].fa = x;
		tr[x].fa = z;
		if (z) tr[z].son[chky] = x;
		pushup(y);
		pushup(x);
	}
	void splay(int x)
	{
		for (int f = tr[x].fa; f = tr[x].fa, f; rotate(x))
		{
			if (tr[f].fa) rotate(get(f) == get(x) ? f : x);
		}
		rt = x;
	}
	void ins(int x)
	{
		if (!rt)
		{
			rt = ++idx;
			tr[rt].val = x;
			tr[rt].cnt = 1;
			pushup(rt);
			return;
		}
		int u = rt, f, last;
		while (true)
		{
			if (tr[u].val == x)
			{
				tr[u].cnt++;
				pushup(u);
				pushup(f);
				splay(u);
				return;
			}
			if (!u)
			{
				u = ++idx;
				tr[u].fa = f;
				tr[u].val = x;
				tr[u].cnt = 1;
				tr[f].son[last] = u;
				pushup(u);
				pushup(f);
				splay(u);
				return;
			}
			f = u;
			last = x > tr[u].val;
			u = tr[u].son[last];
		}
	}
	int rank(int k)
	{
		int res = 0, u = rt;
		while (true)
		{
			if (tr[u].val > k)
			{
				u = tr[u].son[0];
			}
			else if (tr[u].val == k)
			{
				res += tr[tr[u].son[0]].sz;
				splay(u);
				return res + 1;
			}
			else
			{
				res += tr[tr[u].son[0]].sz + tr[u].cnt;
				u = tr[u].son[1];
			}
		}
	}
	int pre()
	{
		int u = tr[rt].son[0];
		if (!u) return 0;
		while (tr[u].son[1]) u = tr[u].son[1];
		splay(u);
		return tr[u].val;
	}
	int nxt()
	{
		int u = tr[rt].son[1];
		if (!u) return 0;
		while (tr[u].son[0]) u = tr[u].son[0];
		splay(u);
		return tr[u].val;
	}
	void CLEAR(int u)
	{
		tr[u].cnt = tr[u].fa = tr[u].son[0] = tr[u].son[1] = tr[u].sz = tr[u].val = 0;
	}
	void del(int x)
	{
		rank(x);
		int u = rt;
		if (tr[u].cnt > 1)
		{
			tr[u].cnt--;
			pushup(u);
			return;
		}
		if (!tr[u].son[0])
		{
			tr[tr[u].son[1]].fa = 0;
			rt = tr[u].son[1];
			CLEAR(u);
			return;
		}
		if (!tr[u].son[1])
		{
			tr[tr[u].son[0]].fa = 0;
			rt = tr[u].son[0];
			CLEAR(u);
			return;
		}
		pre();
		tr[rt].son[1] = tr[u].son[1];
		tr[tr[u].son[1]].fa = rt;
		pushup(rt);
		CLEAR(u);
	}
}tr;

int n;
long long c;

int main()
{
	tr.ins(INT_MIN);
	tr.ins(INT_MAX);
	scanf("%d", &n);
	int rn = n;
	while (n--)
	{
		int x;
		scanf("%d", &x);
		long long tp = 0LL;
		tr.ins(x);
		if (n == rn - 1)
		{
			printf("%lld\n", c);
			continue;
		}
		int p = tr.pre();
		tr.rank(x);
		int nx = tr.nxt();
		if (p != INT_MIN)
		{
			tp = dep[p];
		}
		if (nx != INT_MAX)
		{
			tp = max(tp, dep[nx]);
		}
		dep[x] = tp + 1LL;
		c += tp + 1LL;
		printf("%lld\n", c);
	}
	return 0;
}
```


---

