# [ABC255F] Pre-order and In-order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_f

$ 1,\ 2,\ \ldots,\ N $ と番号づけられた $ N $ 個の頂点を持つ**二分木**を考えます。 ここで、二分木とは各頂点が高々 $ 2 $ 個の子を持つ根付き木です。より具体的には、二分木の各頂点は高々 $ 1 $ 個の**左の子**と高々 $ 1 $ 個の**右の子**を持ちます。

頂点 $ 1 $ を根とする二分木であって、下記の条件を満たすものが存在するかを判定し、存在する場合はその一例を示してください。

- すべての頂点を深さ優先探索における[**行きがけ順**](https://ja.wikipedia.org/wiki/%E6%9C%A8%E6%A7%8B%E9%80%A0_(%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0)#.E6.B7.B1.E3.81.95.E5.84.AA.E5.85.88.E6.8E.A2.E7.B4.A2)（pre-order）で並べた列が $ (P_1,\ P_2,\ \ldots,\ P_N) $ である。
- すべての頂点を深さ優先探索における[**通りがけ順**](https://ja.wikipedia.org/wiki/%E6%9C%A8%E6%A7%8B%E9%80%A0_(%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0)#.E6.B7.B1.E3.81.95.E5.84.AA.E5.85.88.E6.8E.A2.E7.B4.A2)（in-order）で並べた列が $ (I_1,\ I_2,\ \ldots,\ I_N) $ である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数
- $ (P_1,\ P_2,\ \ldots,\ P_N) $ は $ (1,\ 2,\ \ldots,\ N) $ の順列
- $ (I_1,\ I_2,\ \ldots,\ I_N) $ は $ (1,\ 2,\ \ldots,\ N) $ の順列

### Sample Explanation 1

次の画像に示す、頂点 $ 1 $ を根とする二分木が問題文中の条件を満たします。 !\[\](https://img.atcoder.jp/abc255/b51399e8953ae1723d1d9e83617f9be9.png)

### Sample Explanation 2

問題文中の条件を満たすような頂点 $ 1 $ を根とする二分木は存在しません。よって $ -1 $ を出力します。

## 样例 #1

### 输入

```
6
1 3 5 6 4 2
3 5 1 4 6 2```

### 输出

```
3 6
0 0
0 5
0 0
0 0
4 2```

## 样例 #2

### 输入

```
2
2 1
1 2```

### 输出

```
-1```

# 题解

## 作者：program_xwl (赞：3)

## 思路：
我们需要用前序遍历知道子树的根是哪个，中序遍历来划分子树。设一棵二叉树的前序遍历结果为 `ABDECFG` 中序遍历结果为  `DEBACFG` ，我们一起来模拟一下这个求二叉树的过程。

我们知道，前序遍历的顺序是 “根左右”，第一个肯定是根节点，我们就知道了最关键的信息根节点。而中序的根是在中间的，那么我们在中序遍历序列中找到那个根，不就可以划分左右子树了吗？解法就是这样，如图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/5fn0byba.png)

划分完成后，我们还得到了一个关键信息：两个子树的节点数。得到了这个信息，我们就可以在前序遍历结果中找到对应的左右子树了，这时候，我们就知道了两子树的前序和中序遍历。你可能已经想到了，递归。没错，正确解法就是递归，我们不断将这个子树的前序中序遍历结果拆分，拆分，直到不能拆为止。

## 代码（记得看注释）：
>莫复制，棕了你的名，空悲切！
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {int l,r;} tree[200005];//用来存储答案
int n,a[200005],b[200005],mp[200005];//a数组用于存储树的前序遍历，b数组用于存储树的中序遍历，mp用于记录a的元素在b数组中的对应点。

void dfs(int l1,int r1,int l2,int r2)//从左到右的依次为当前a数组左端点，当前a数组右端点，当前b数组左端点，当前b数组右端点。
{
	if(l1 >= r1) return;//只有一个元素说明到叶子节点了
	int root = mp[a[l1]],sizl = root-l2,sizr = r2-root;//root代表在b数组中当前子树的根的位置，sizl是左子树大小，sizr是右子树大小
	if(root < l2 || root > r2)//说明前序和中序遍历不对应，无解
	{
		cout << -1;
		exit(0);
	}
	tree[a[l1]] = {a[l1+1],a[l1+sizl+1]};//更新答案
	if(sizl == 0) tree[a[l1]].l = 0;//如果左子树为空就设为0
	if(sizr == 0) tree[a[l1]].r = 0;//如果右子树为空也设为0
	dfs(l1+1,l1+sizl,l2,root-1);//递归左子树
	dfs(l1+sizl+1,r1,root+1,r1);//递归右子树
	return;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	if(a[1] != 1)//题目说树的根节点必须是1，所以如果前序遍历的第一项（根）不是1，无解
	{
		cout << "-1\n";
		return 0;
	}
	for(int i = 1;i <= n;i++) mp[b[i]] = i;//找对应点
	dfs(1,n,1,n);
	for(int i = 1;i <= n;i++) cout << tree[i].l << ' ' << tree[i].r << '\n';
	return 0;
}
```

---

## 作者：Tsawke (赞：2)

# [[ABC255F] Pre-order and In-order](https://www.luogu.com.cn/problem/AT_abc255_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC255F)

## 题面

给定一棵二叉树的先序遍历和中序遍历，请构造一棵以 $ 1 $ 节点为根的二叉树。第 $ i $ 行输出节点 $ i $ 的左右儿子，儿子为空则输出 $ 0 $。无解输出 `-1`。

## Solution

也是一道水题，考虑先序和中序的意义即可。

众所周知，先序遍历的顺序是根、左子树、右子树。中序遍历是左子树、根、右子树。

于是不难发现，在当前的先序遍历中取第一个数即为当前的根，然后在中序遍历中找到根的位置，其左侧即为整个左子树，右侧为整个右子树。于是不难想到 dfs 即可，参数维护当前的整个子树属于先序遍历的 $ [lp, rp] $，属于中序遍历的 $ [li, ri] $，然后需要记录每个数的位置，通过中序遍历根和左右之间的数的个数，可计算左右子树的大小，以此即可确定先序遍历左右子树的下一个区间，以此递归下去即可。

考虑无解的情况，要么先序遍历的第一个值不为 $ 1 $，说明二叉树根不为 $ 1 $。要么就是在递归过程中，确定先序的第一位为根之后，根在中序中的位置超出了当前的限制位置，在这两种特殊情况记录一下无解即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
int Pre[210000], In[210000];
int posP[210000], posI[210000];
pair < int, int > son[210000];

int dfs(int lp = 1, int rp = N, int li = 1, int ri = N){
    // printf("In dfs(%d ~ %d, %d ~ %d)\n", lp, rp, li, ri);
    if(lp > rp)return 0;
    int rt = Pre[lp];
    if(posI[rt] < li || posI[rt] > ri)puts("-1"), exit(0);
    if(lp == rp)return rt;
    int lsiz = (posI[rt] - 1) - li + 1;
    son[rt].first = dfs(lp + 1, lp + lsiz, li, posI[rt] - 1);
    son[rt].second = dfs(lp + lsiz + 1, rp, posI[rt] + 1, ri);
    return rt;
}

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)posP[Pre[i] = read()] = i;
    for(int i = 1; i <= N; ++i)posI[In[i] = read()] = i;
    if(Pre[1] != 1)puts("-1"), exit(0);
    dfs();
    for(int i = 1; i <= N; ++i)printf("%d %d\n", son[i].first, son[i].second);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_07 初稿

---

## 作者：ATION001 (赞：0)

## 题目描述
给定一棵**二叉树**的前序遍历和中序遍历，请输出这棵树的结构，第 $i$ 行输出节点 $i$ 的左右儿子，如果儿子不存在输出 $0$。若无解则输出 $-1$。
## 思路
~~其实这道题只是树的基础题而已。~~

本题特殊的地方在于数据有不合法的情况。

这时候我们需要特判。

先考虑有解的情况：根据前序遍历求出树的根节点，用中序遍历求出根节点的左右子树。

对于无解的情况：如果先序遍历的第一个值不为 $1$（题目已明确说明树的根节点为 $1$），或者在遍历过程中，确定子树的根节点时，根在中序遍历中的位置已经超出我们设定的范围（即给定的范围找不到），直接输出 $-1$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[200005],r[200005],qian[200005],zhong[200005],mp[200005];
int dfs(int l1,int r1,int l2,int r2){
	if(l1>r1){
		return 0;
	}
	int P=mp[qian[l1]];
	if(P<l2||P>r2){
		cout<<-1;
		exit(0);
	}
	l[qian[l1]]=dfs(l1+1,l1+(P-l2),l2,P-1);
	r[qian[l1]]=dfs(l1+(P-l2)+1,r1,P+1,r2);
	return qian[l1];
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>qian[i];
	}
	for(int i=1;i<=n;i++){
		cin>>zhong[i];
		mp[zhong[i]]=i;
	}
	if(qian[1]!=1){
		cout<<-1;
		return 0;
	}
	dfs(1,n,1,n);
	for(int i=1;i<=n;i++){
		cout<<l[i]<<' '<<r[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：LastKismet (赞：0)

*考前攒RP*

# 思路
个人写的代码不是最常见的版本，但鉴于较为简短直观 ~~（个人意见，毕竟是自己写的hhh）~~，还是发出来供参考。

首先假设合法，我分别储存了前序在中序中的位置以及中序在前序中的位置，用以备用。

每次递归建树时都储存当前子树在中序中的区间，那么就可以通过当前节点中序得到左右子树的大小，从而直接获取左右子节点，递归建树。

然后考虑不合法的情况，一种就是两个序列不匹配，每次看当前节点中序是否在对应子树区间内即可。另一种是根节点不为一，特判即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;

struct node{
	int l,r;
}ns[N];

int n;
int pro[N],ino[N],plc[N],ord[N];//中序，前序 

bool grow(int id,int l,int r){
	if(plc[id]<l||plc[id]>r)return false;
	int lsize=plc[id]-l,rsize=r-plc[id];
	if(lsize!=0){
		ns[id].l=pro[ord[id]+1];
		if(!grow(ns[id].l,l,plc[id]-1))return false;
	}
	if(rsize!=0){
		ns[id].r=pro[ord[id]+lsize+1];
		if(!grow(ns[id].r,plc[id]+1,r))return false;
	}
	return true;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>pro[i];
		ord[pro[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>ino[i];
		plc[ino[i]]=i;
	}
	
	if(pro[1]!=1||!grow(1,1,n)){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cout<<ns[i].l<<" "<<ns[i].r<<endl;
	}
	return 0;
} 
```

---

## 作者：Ascnbeta (赞：0)

# ABC255F
## 题面大意
给出一棵二叉树的先序遍历和中序遍历，要求你重新构造出这棵二叉树。这是 CSP-J 初赛前 $15$ 题必有的一类题型，只不过这次要求我们用程序完成这一过程。

## 思路分析
根据先序遍历的定义，我们很容易知道，先序遍历的第一个字母就是当前树的根节点。（所以由于题面要求 $1$ 必为根节点，如果我们读入先序遍历的第一个结点不为 $1$ 的话直接输出 $-1$ 即可。

而通过中序遍历，我们可以把一棵大树分为左右子树，因为在中序遍历中，根节点一定在左右两棵子树的中间。所以我们可以读取先序遍历的第一个节点获取当前树的根节点，然后在中序遍历中找到这个节点所在位置，把当前树分为左右两棵子树，接着**递归**地处理左右两棵子树，直到区间内仅有一个点为止。

至于无解情况，除了上文第一段所提到的情况外，当我们在中序遍历的序列中寻找我们在先序遍历所获得的根节点的位置时，如果在**当前区间内**没有找到这个根节点的编号，说明序列不合法，同样输出 $-1$ 即可。

~~其实就是你考场上做这种题的过程，应该不会不知道吧~~

## 具体实现
本蒟蒻的 dfs 传入了 $4$ 个参数，分别是：

* $l,r$。这两个参数是用来表示当前所求解的**中序遍历**的区间左端点和右端点，是下标。
* $p$。这个参数是当前所求解的子树的根节点在**前序遍历**中的位置，是下标。
* $lst$。这个参数用来表示当前子树的父节点在**中序遍历**中的位置，也是下标。由于题目中最后要求我们输出的是每个节点的孩子节点，所以使用这个变量可以帮我们存储每个节点的孩子都是谁。同时也可以判断当前求解的子树是其父亲节点的左子树还是右子树。~~（其实个人感觉这个没必要传递，在每一步递归前判断应该也可以？）~~

dfs 的核心就是在当前子树的中序遍历中寻找子树的根节点在中序遍历中的位置，然后把中序遍历断成两份，分别求解，知道序列都被断成长为 $1$ 的序列为止。

但是需要注意的是，如果我们直接在 dfs 中遍历区间去寻找当前子树根节点在中序遍历的位置，会 TLE 多个点。由于序列中都是节点编号，而这些编号一定是互异的，所以我们在读入中序遍历的时候就可以把每个编号所在的位置储存好，在 dfs 中直接查询并判断位置是否在区间中即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+3;
int n;
int x[N],y[N],pos,yp[N];// x 是先序，y 是后序，yp 是下标元素所在位置。
int ch[N][3];//每个节点的孩子，1 左 2 右。
void dfs(int l,int r,int p,int lst) {
    if (lst != 0) {
        if (r < lst) {
            ch[y[lst]][1] = x[p];
        }else if (l > lst) {
            ch[y[lst]][2] = x[p];
        }//判断左右子树
    }
    if (l == r) return;
    int root = yp[x[p]]; //直接查询，防止 TLE。
    if (root < l || root > r) {
        cout << -1 << endl;
        exit(0);
    }//如果不在区间内说明序列非法。
    if (root != l) {
        dfs(l,root-1,p+1,root);
    }
    if (root != r) {
        dfs(root+1,r,p+root-l+1,root);
    }//判断的目的是防止序列出现 l > r 情况。需要注意的是第三个参数（被分开的子树其根节点在前序遍历中位置）的变化公式，可以自己动手推一下，很明显。
}
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        if (x[1] != 1) {
            cout << -1 << endl;
            return 0;//判断 1 位置。
        }else{
            pos = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> y[i];
        yp[y[i]] = i;//存储位置。
    }
    dfs(1,n,pos,0);
    for (int i = 1; i <= n; i++) {
        cout << ch[i][1] << ' ' << ch[i][2] << '\n';
    }
    return 0;
}
```

---

## 作者：feizhu_QWQ (赞：0)

## 前置芝士

[P1030 \[NOIP2001 普及组\] 求先序排列](https://www.luogu.com.cn/problem/P1030)，
很类似，是以这道题加强的。

## 算法指导

[可适当观看](https://www.luogu.com.cn/article/oce0zr3y)，手写文章，可以对本题的理解程度更高哦！

# 回到本题

[题目传送门](https://www.luogu.com.cn/problem/AT_abc255_f)\
这道题其实是 P1030 的加强版。\
相信打过初赛的小竹子们一定对这种题很熟悉，不过这道题从求遍历变成了求树。\
  给你一棵树的先序或后序，中序，让你求另一个的题型很简单，我们可以通过递归实现。怎么实现呢？\
首先，我们知道，先序遍历的第一个节点一定是这棵子树的根，那我们就可以在中序遍历中找到这个节点，然后，这个节点左边的一系列节点就是他的左子树，他右边的就是他的右子树，这是我们根据先序和中序的性质推出来的，然后我们继续把这个节点的左子树继续递归下去，右子树也同样。\
这里的部分我前面的算法指导也可以参考一下。\
注：在中序遍历中找根的时候不能循环，否则会触发第一个隐藏彩蛋：TLE。\
所以我们用一个数组来记录每个节点在中序遍历中的位置。\
接着按先序或后序的顺序在递归里输出就行了。
这就是普通问题的思路，可怎么求树呢？\
也比较简单，我们每次找到这个子树的根，就在递归结束后递归回去，让他的父节点把他加入自己的子树。\
还有，如果递归的时候发现已经没有数字了，就返回 $0$，代表没有左儿子或右儿子。\
最后，我们还需要在函数开头判断是否越界，否则会触发第二个隐藏菜彩蛋：RE。\
还有，如样例二，我们也需要在主函数里判断，如果先序遍历的第一个数不是 $1$，无解。\
核心代码：

```cpp
int dfs(int l1,int r1,int l2,int r2)//参数需要记录这段遍历的起点终点，1是先序，2是中序
{
	if(r1-l1+1<=0||l1<=0||l2<=0||r1<=0||r2<=0||r1>n||r2>n)//防RE的判断
	{
		return 0;//万万不可忘记
	}
	int a=x[l1];
	int pos=id[a];
	if(y[pos]!=a)
	{
		cout<<-1;//无解，在中序遍历中找不到根节点
		exit(0);
	}
	op[a].push_back(dfs(l1+1,l1+(pos-l2),l2,pos-1));
	op[a].push_back(dfs(l1+(pos-l2)+1,r1,pos+1,r2));
	if(op[a].size()>2)
	{
		cout<<-1;//无解，多次来到一个节点
		exit(0);
	}
	return a;//返回值
}
```

ヾ (￣▽￣) Bye Bye\~

---

## 作者：Meickol (赞：0)

在天梯赛练习题库中做过类似的题。

本题不难，但需要先了解二叉树先中后三种遍历顺序，若不会请先自行查阅学习，在此不做解释。

我们知道，给出一个中序序列，再给出一个先序或后序即可确定一颗二叉树。

但是如果只给出先序序列或后序序列，不给出中序序列，则无法确定一颗二叉树。

本题即已给出先序序列和中序序列，让我们确定是否构造出来的二叉树是以 $1$ 为根节点，显然好做。

直接递归解决即可，但要注意剪枝，否则递归层数过多会爆栈。

代码简洁清晰，应该挺好理解的，就不多解释了。

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=2e5+5;
int n;
int preorder[N],inpos[N];
unordered_map<int,int> tr_l,tr_r;
int build(int il,int ir,int fl,int fr){ //参数依次为中序左右指针、先序左右指针
	int root=preorder[fl];
	int rootpos=inpos[root];
	if(il>rootpos || ir<rootpos){ //此时已无法完整构造，剪枝结束
		cout<<-1;
		exit(0);
	}
	if(il<rootpos){ //递归左子树
		tr_l[root]=build(il,rootpos-1,fl+1,fl+1+(rootpos-1)-il);
	}
	if(ir>rootpos){ //递归右子树
		tr_r[root]=build(rootpos+1,ir,fl+1+(rootpos-1)-il+1,fr);
	}
	return root;
}
void solve(){
	cin>>n;
	rep(i,1,n) cin>>preorder[i]; //先序序列
	rep(i,1,n){
		int x;
		cin>>x;
		inpos[x]=i; //编号为 x 的结点在中序序列中的位置
	}
	int root=build(1,n,1,n);
	if(root!=1) cout<<-1;
	else rep(i,1,n) cout<<tr_l[i]<<" "<<tr_r[i]<<endl;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析

对于先序遍历，其规则是：根左右；对于中序遍历，其规则是：左根右。不难发现，如果我们以 $x$ 为一棵子树的根，那么其子节点们都应该在 $x$ 的先序遍历位置之后，中序遍历两边。

所以，我们可以用递推来写，每次记录这棵子树的最远的两个叶节点在两种遍历之中的位置与这棵子树的根。找到这个根在中序遍历中的位置，那么这个位置到最左边的位置就是该子树的左子树，反之同理。此时我们就可以求出这个子树的左右子树的根，因为我们知道左右子树中节点的数量。而又根据先序遍历的性质，该子树的左子树的根就是离该子树的根最近的那个点，该子树的右子树的根就是减去左子树的节点数量再减去 $1$（该子树的根）的第一个点。继续递推即可。

但是，一棵树可能只有右子树没有左子树，或者只有左子树没有右子树。所以我们需要加一些判断，看是否拥有左右子树（分析见注释）。

简化分析：模拟与特判，运用先序与中序遍历的性质解题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N=4e6+10;
map<int,int> where,xian,zhong;
//where[i]是节点i在中序遍历中的下标 
struct tree{
	int l,r;
}tr[N];//存每个点的左右子节点 
int ans;//用来记录遍历到的点的数量 
void dfs(int l,int r,int L,int R,int imp)
//先序遍历区间，中序遍历区间，根节点 
{
	if(l==r||L==R||l>r||L>R) return;//叶节点||越界 
	int i=where[imp];//根节点在中序遍历中的下标 
	if(tr[imp].l||tr[imp].r) return;//有值，不用再计算（不可能出现这种情况） 
	if(where[xian[l+1]]<i)//有左子树 
	{
		if(l+(i-L)<=r&&i-1<=R&&l+1<=r)
		//左子树的所有点都在区间内 
		{
			ans++,tr[imp].l=xian[l+1],dfs(l+1,l+(i-L),L,i-1,xian[l+1]);
			//更新左子树编号，继续递推 
			if(l+(i-L)+1!=l+1&&r!=l+(i-L)&&l+(i-L)+1<=r&&l+(i-L)+1>=l&&i+1<=R&&i+1>=L)
			//右子树的根与左子树的根不重合（有右子树），右子树的所有点都在区间内 
				ans++,tr[imp].r=xian[l+(i-L)+1],dfs(l+(i-L)+1,r,i+1,R,xian[l+(i-L)+1]);
				//更新右子树编号，继续递推 
		}
	}
	else
	{
		if(where[xian[l+1]]>i&&l+1<=r&&i+1<=R&&i+1>=L)
		//没有左子树，但是有右子树，且全在区间内 
		{
			ans++,tr[imp].r=xian[l+1],dfs(l+1,r,i+1,R,xian[l+1]);
			//更新右子树编号，继续递推 
		}
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>xian[i];
	for(int i=1;i<=n;i++) cin>>zhong[i],where[zhong[i]]=i;
	if(xian[1]!=1) return cout<<"-1",0;//先序遍历的第一个点必为1，因为1必须是根 
	dfs(1,n,1,n,1);
	if(ans!=n-1) return cout<<"-1",0;//除了1以外没有遍历完点，即无法构成树 
	else for(int i=1;i<=n;i++) cout<<tr[i].l<<" "<<tr[i].r<<endl;//可以，输出 
	return 0;
}
//注：这里使用where数组来存下标，是为了减少时间复杂度。如果不用，需要另加一层循环来寻找下标。 
```

---

