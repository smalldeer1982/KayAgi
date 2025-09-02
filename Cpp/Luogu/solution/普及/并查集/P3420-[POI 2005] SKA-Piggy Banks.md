# [POI 2005] SKA-Piggy Banks

## 题目描述

Byteazar the Dragon 拥有 $N$ 个小猪存钱罐。每一个存钱罐能够用相应的钥匙打开或者被砸开。Byteazar 已经将钥匙放入到一些存钱罐中。现在已知每个钥匙所在的存钱罐，Byteazar 想要买一辆小汽车，而且需要打开所有的存钱罐。然而，他想要破坏尽量少的存钱罐，帮助 Byteazar 去决策最少要破坏多少存钱罐。

## 样例 #1

### 输入

```
4
2
1
2
4```

### 输出

```
2```

# 题解

## 作者：李尧 (赞：32)

其实这题很简单的

~~所以你第一次为什么TLE90分~~

在此忠告大家，一定要在过程中更新fa[x]的值（我相信你们写的都是并查集）

现在288ms，感觉自己棒棒哒~

这个题目主要的难点在于如何判定破哪个罐子。其实不难想，如果出现环形，那么一定要破掉一个罐子。

那么，什么时候会出现环形呢？

想一下，如果一个罐子i的钥匙为j，而我们已知只要打开i就能打开j（即find（j）==i），那么我们必须破开i，或者破开j，暂时我选择破开i。

放代码喽，不要直接复制哦~
```
#include <bits/stdc++.h>
using namespace std;
int n,a[1000007],ans;
int fa[1000007];
int find(int x){
	if(fa[x]==x) return x;
	int a=find(fa[x]);
	return fa[x]=a;
}//在寻找fa[x]的过程中更新fa[x]的值，减短下一次寻找的线路，防止TLE
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) fa[i]=i;//初始化
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);	
		if(find(a[i])==i){//判定是否构环
			fa[i]=i;ans++;//如果构环，则破掉i号存钱罐
		}
		else fa[i]=a[i];//反之，把i的“父亲”赋为a[i]
	}
	printf("%d",ans);//输出破掉的次数
    return 0; 
}
```

---

## 作者：Tarsal (赞：15)

蒟蒻的第二篇题解

嗯，直接进入正题

先告诉你们这是并查集，好吧，标签上面有，再来分析这为什么是并查集。

根据题意：

```
每一个存钱罐能够用相应的钥匙打开或者被砸开，Byteazar已经将钥匙放入到一些存钱罐中
```

我们可以理解成：

如果这是一个联通块的“祖先”（也可以称为根吧，蒟蒻不知道该怎么称呼）那么就把它砸破，这样整个联通块就都可以取出；

如果不是的话，就不管它；

从后面句话就可以很明显的推出他们之间有从属关系（如果要砸的数目最小），这是并查集的思想，是吧；

好，既然我们已经知道了它要用并查集做；

那么，就是一个模板呀，上模板就可以了，最后输出联通块的个数；

OK，上代码，代码中也有注释：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 1000010
int n, ans, x, fa[maxn];

/*
//三目运算符版本 
int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x)'
}
*/

//普通的呐 
int find(int x)
{
	if(fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i)
		fa[i] = i;//最开始，每个人都是自己的祖先； 
	for(int i = 1; i <= n; ++ i)
	{
		scanf("%d", &x);
		fa[find(i)] /*找祖先*/ = find(x)/*找它的儿子的祖先*/;
		//就是合并两个集合呐 
	}
	for(int i = 1; i <= n; ++ i)
		if(fa[i] == i)//求联通块的个数 
			++ ans;
	printf("%d", ans);
	return 0;
}
```



---

## 作者：oscar (赞：5)

【POI补全计划#4 POI2005 SKA】

楼下好多人都说要用并查集，实际上是想复杂了

看到“每个（储钱罐）的钥匙在另**一个**（储钱罐）里面”就应该想到这是多棵环套树（证明见IOI2008 Island的题解）

所以只需要DFS一遍，数一下有多少个环就好了（显然其它点一定能从环上到达）

**数组开100000不够**

其它没什么好说的了，上代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1000010;
int vis[MAXN],pa[MAXN];
int n,ans;
inline void dfs(int x,int type)
{
    if(type==1)
    {
        if(vis[x]==1)
        {
            ++ans;
            return;
        }
        else if(vis[x]==2)return;
    }
    else
    {
        if(vis[x]==2)return;
    }
    vis[x]=type;
    dfs(pa[x],type);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&pa[i]);
    }
    for(int i=1;i<=n;++i)
    {
        if(!vis[i])
        {
            dfs(i,1);
            dfs(i,2);
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

Last solution.

（就算是吧

---

这题怕不是个并查集板子。。

不会并查集请[出门左转](https://www.luogu.com.cn/blog/CM0/bingchaji)。

~~如果你已经成功AC 并查集板子，那么恭喜你，这题就可以秒切了。~~

还是说一下思路吧。

我们知道并查集维护的是集合/连通块信息。

根据题意就可以知道此题要求求的是有多少个连通块（可以认为若两个零钱罐有钥匙关系，则两者在同一连通块）。

那么，就只要求出$n$ 个零钱罐有多少个不同祖先。

Code

```cpp
#include<cstdio>
using namespace std;
int n,w[1000001],x,num;
bool pd[1000001];//记录不同祖先
int find(int q)
{
    if(w[q]==q)
        return q;
    return w[q]=find(w[q]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        w[i]=i;//初始化
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        w[find(i)]=find(x);//建立钥匙关系
    }
    for(int i=1;i<=n;++i)
        pd[find(w[i])]=true;
    for(int i=1;i<=n;++i)
        if(pd[i])
            ++num;//num即不同祖先的个数
    printf("%d\n",num);//输出答案
    return 0;
}
```

Goodbye.

---

## 作者：LlLlCc (赞：2)

这题容易让人产生一个错误的想法（~~可能就我想错了~~）。

读完题，**X要在Y之前打开**，很明显的层次关系（先后顺序），然后果断的写了一个拓扑，然后样例都过不了。（错误示范）

------------
## 正解：
因为每个点都有入度和出度，所以可能会有一团互相影响，其中只要有一个打开了，其他的都会打开，这样，我们会很自然的就往并查集上面去想。

我们只要把两个相连的点，连在一起，用并查集计录有几个集合，就知道答案了。（因为每个集合只需打破一个即可全部打开，所以我们只要统计有几个集合就好了）

AC代码：
```
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n,x,fa[maxn],ans,a[maxn];
bool vis[maxn];
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
    while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
    n=read();
    for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=n;i++){
		a[i]=x=read();
		int fx=getfa(x),fy=getfa(i);
	    if (fx!=fy) fa[fy]=fx;
	}
	for (int i=1;i<=n;i++){
		x=getfa(a[i]);
		if (!vis[x]) ans++;
		vis[x]=1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：sunyt (赞：2)

###P3420思路

详解请戳博客<http://blog.csdn.net/stockholm\_sun/article/details/78444273>

做这个题有两个思路，第一个就是并查集，但是我一开始并没有想到这种解法。这里我重点讲讲第二种我一开始就想到的一个解法。

思路是这样的：通过题意中一个存钱罐中的钥匙能够打开另一个（或者自己本身）存钱罐的关系，我们不难想出这些存钱罐之间的关系可以用一张图来表示，所以我们发现这是一张有向图。那么图中入度为0的所有节点一定需要被砸。

接下来考虑一种特殊情况，就是如果这张有向图中有环，那么这个环就必须有一个需要被打开，然后环内的所有罐都能被打开，所以我们就用Tarjan算法来缩点，将强连通分量做出来，然后会形成一张新图，对于这张新图，我们只需要计算入度为0的节点个数即可，因为入度不是0的节点就一定可以通过砸开它的前驱，取到钥匙并打开来得到更优的解。

还有一点细节，就是对缩点之后的新图中自环的处理，如果出现了自环，那么我们就不统计这一条边（自环）。


###代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<deque>
#include<cstring>
#define MAXX 1000001
using namespace std;
int i,j,m,n,k; 
int temp,hd[MAXX],col[MAXX],colorn,b[MAXX];
int deep[MAXX],dfn[MAXX],low[MAXX],num;
int sta[MAXX],rd[MAXX],top;
struct data
{
    int v;
    int nxt;
}a[MAXX];

int r()
{
    int ans=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ans*=10;
        ans+=ch-'0';
        ch=getchar();
    }
    return ans*f;
}

void add(int x,int y)
{
    a[++temp].nxt=hd[x];
    a[temp].v=y;
    hd[x]=temp;
}

void tarjan(int x)
{
    int son;
    dfn[x]=low[x]=++num;
    b[x]=1;
    sta[++top]=x;
    for(int p=hd[x];p;p=a[p].nxt)
    {
        son=a[p].v;
        if(!dfn[son])
        {
            tarjan(son);
            low[x]=min(low[x],low[son]);
        }
        else if(b[son])
        {
            low[x]=min(low[x],dfn[son]);
        }
    }
    if(dfn[x]==low[x])
    {
        b[x]=0;
        col[x]=++colorn;
        while(sta[top]!=x)
        {
            col[sta[top]]=colorn;
            b[sta[top--]]=0;
        }
        top--;
    }
}

int main()
{
    n=r();
    int xx;
    for(i=1;i<=n;i++)
    {
        xx=r();
        add(xx,i);
    }
    
    for(i=1;i<=n;i++)
    if(!col[i])
    tarjan(i);
    
    for(i=1;i<=n;i++)
    for(int p=hd[i];p;p=a[p].nxt)
    {
        if(col[a[p].v]!=col[i])
        rd[col[a[p].v]]++;
    }
    int ans=0;
    for(i=1;i<=colorn;i++)
    if(!rd[i])
    ans++;
    cout<<ans;
    return 0;
}
/*
5
2
3
3
3
3
*/
```

---

## 作者：AuroraIris (赞：2)

并查集中的联通快（像家庭问题）

```cpp
var n,i,x,r1,r2,ans:longint;
father:array[0..100000] of longint;
a:array[0..100000] of boolean;
function find(x:longint):longint;//寻找父节点，合并
begin
if father[x]<>x then father[x]:=find(father[x]);
find:=father[x];
end;
begin
readln(n);
for i:=1 to n do
father[i]:=i;//每一个的初始父亲就是自己
for i:=1 to n do
begin
readln(x);
r1:=find(i);
r2:=find(x);
if r1<>r2 then father[r2]:=r1;//优化，将单链合并
end;
for i:=1 to n do
a[find(i)]:=true;//查找每一个点的父节点（所以总共的家庭数就是父节点数）
for i:=1 to n do
if a[i] then inc(ans);将父节点数累计
write(ans);
end.
```
连通块不难
没人做应该是题目看不懂


byteazar有存钱罐。每个存钱罐都可以用相应的钥匙打开。byteazar已经把钥匙放在了存钱罐中。byteazar打算买一辆汽车，他需要获得所有的存钱罐中的钱。然而，他想打开的储蓄罐尽可能少。帮助byteazar确定需要打碎多少储蓄罐。


标准输入的第一行是一个整数n，这是byteazar拥有的存钱罐的数量。

接下来，有n行，第i行有一个整数a[i],表示a[i]储蓄罐的钥匙被放置在第i个储蓄罐中。


标准输出只有一行包含一个整数——为了获得所有的存钱罐，要打碎的最小的存钱罐数。


简化一下就是求家庭数。


---

## 作者：Trafford1894 (赞：1)



### Problem

求出能打开所有存钱罐的情况下，需要破坏的存钱罐的最少数量


### Solution

这道题让你求出连通块的个数。而将一个存钱罐钥匙放在另一个存钱罐十分像并查集中的合并。所以这道题可以用并查集做。

1：初始化并查集

```cpp
void Init () {
	for (int i = 1; i < _maxNum + 1; i++) {
		_father[i] = i;//每个人的初始父亲都是他自己
	}
}
```
2：查找

```cpp
int Find (int x) {
	while (_father[x] != x) {
		x = _father[x] = Find(_father[x]);//递归，路径压缩
	}
	
	return x;
}
```
3：合并

```cpp
void Merge (int one, int two) {
    _father[Find(one)] = Find(two);//将两个节点合并到一起
}
```

4：查找连通块

```cpp
for (int i = 1; i < _maxNum + 1; i++) {
	if (_father[i] == i) {
		_ans++;//如果找到了结果加一
	}
}
```
然后，我们就可以愉快的AC了

### ACCode

```cpp


#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>

using namespace std;

int _maxNum;
int _father[1000009];
int _ans = 0;

int Find (int x) {
	while (_father[x] != x) {
		x = _father[x] = Find(_father[x]);
	}
	
	return x;
}

void Init () {
	for (int i = 1; i < _maxNum + 1; i++) {
		_father[i] = i;
	}
}

void Merge (int one, int two) {
    _father[Find(one)] = Find(two);
}

void ParseIn () {
	int curInt;
	scanf("%d", &_maxNum);
	Init();
	
	for (int i = 1; i < _maxNum + 1; i++) {
		scanf("%d", &curInt);
		Merge(curInt, i);
	}
}

void Core () {
	for (int i = 1; i < _maxNum + 1; i++) {
		if (_father[i] == i) {
			_ans++;
		}
	}
}

void CWriteOut () {
	printf("%d\n", _ans);
}

int main () {

	ParseIn();
	Core();
	CWriteOut();

	return 0;
}
```



---

## 作者：Sober_Clever (赞：1)

并查集可做

若箱子i中装着j钥匙，则从i到j引一条单向边

统计一共有多少个联通块即可

由于每个节点有且仅有一个入度


所以一个联通块不可能有多个环（两个环无法连在一起）

即每个联通块有且仅有一个环（包括自环）

而只有环才需要打破箱子

所以打破箱子的数量就是联通块的数量
```cpp
#include<cstdio>
using namespace std;
const int MAXN=1000000 + 7;
int fa[MAXN];
int getf(int x)
{
    if(x==fa[x]) return x;
    return fa[x]=getf(fa[x]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        int a=getf(x),b=getf(i);
        if(a!=b) fa[a]=b;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(getf(i)==i) ans++;
    printf("%d\n",ans);
    return 0;
}

```


---

## 作者：Yuno (赞：1)

仔细观察题目，不难发现：  
**如果j号罐子的钥匙在i号罐子里，而k号罐子的钥匙在j号罐子里，那么砸破i号罐子，即可打开j号罐子和k号罐子。**  
看到这个有没有想到什么？  
对  
# 并查集。
知道了要用并查集做，就简单了。  
~~乱搞一下就可以了。~~  
**Code**：
```cpp
#include<iostream>
using namespace std;
int ans,pre[1000001];
int find(int x){return pre[x]==x?x:pre[x]=find(pre[x]);}
//并查集的“查”+路径压缩
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) pre[i]=i;
	for (int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if (x!=i)//貌似这句话不写也可以，但还是写着吧
		pre[find(i)]=find(x);//合并两个集合
	}
	for (int i=1;i<=n;i++)
	if (pre[i]==i) ans++;//有几个独立的集合
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这道题其实很简单，只要钥匙对应的罐子和它所在罐子union一下，最后统计一下答案即可，附蒟蒻代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,a[1000100],fa[1200000];
int find(int k)
{
    if(fa[k]==k) return k;
    else return fa[k]=find(fa[k]);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(find(i)!=find(a[i]))
        {
            fa[find(i)]=fa[find(a[i])];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]==i) ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：27531zsz (赞：0)

其实这道题还好，就是范围要开大点，其实就是用并查级来找，代码实现如下，附赠题解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,ans,fa[1000005];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
    //如果fa[x]=x,就return x，反之继续找。 
} 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    fa[i]=i;//每个都打上自己的值，便于判断是否找过。 
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        int p=find(i),q=find(x);//查找 
        if(p!=q)
        fa[q]=p;//找过的打上其他的值 
    }
    for(int i=1;i<=n;i++)
    if(fa[i]==i)//如果还是原来的数，就表示这个存钱罐要砸开，里面有钥匙。 
    ans+=1;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：VinstaG173 (赞：0)

一道很有趣的并查集/连通块的题目。
基本思想：按题目要求，初始化使得对于每个i，f[i]=i。
将第i个存钱罐钥匙所在的存钱罐设为第f[i]个。
然后发现满足f[i]=i的i就是无法用钥匙打开的存钱罐，需要砸开。
代码如下：

```cpp
#include<cstdio>
int n,a,x=0,f[1000001];
int gf(int i)//“找爸爸”
{
	if(f[i]!=i)f[i]=gf(f[i]);
	return f[i];
}
void un(int i,int j)//按题目要求连接函数
{
	int s=gf(i),t=gf(j);
	if(s!=t)f[t]=s;
}
int main()
{
	scanf(" %d",&n);
	for(int i=1;i<=n;i++)//初始化
	{
		f[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		scanf(" %d",&a);
		un(i,a);//调用函数按要求连接
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==i)x++;//判断，统计
	}
	printf("%d",x);
	return 0;
}
```
                         
谢谢！

---

## 作者：wangxuezhu (赞：0)

稍有常识的人不难看出，本题是一道并查集的裸题。砸开一个罐子后，会有一连串的罐子被打开，可以把它们看做联通块，然后用并查集求出联通快个数。。。。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,x,y,fa[1001000],ans;
int find(int k)
{
    if(k==fa[k])
    return k;
    else
    return fa[k]=find(fa[k]);
}
int main()
{
    int i;
    cin>>n;
    for(i=1;i<=n;i++)
    fa[i]=i;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x);
        x=find(x);
        y=find(i);
        fa[x]=y;
    }
    for(i=1;i<=n;i++)
    if(fa[i]==i)
    ans++;
    cout<<ans;
    return 0;
}
```

---

