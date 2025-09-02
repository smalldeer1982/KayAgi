# [ICPC 2016 WF] Ceiling Function

## 题目描述

高级天花板制造商（ACM）正在分析其新系列的极其防坍塌天花板（ICPC）的特性。一个 ICPC 由 $n$ 层材料组成，每层都有不同的抗坍塌值（以正整数表示）。ACM 想要进行的分析将把各层的抗坍塌值存储在一个二叉搜索树中，并检查该树的形状是否与整个结构的质量相关。因为，为什么不呢？

具体来说，ACM 将从顶层到底层依次获取各层的抗坍塌值，并将它们逐一插入到树中。插入值 $v$ 的规则是：

如果树是空的，则将 $v$ 作为树的根。

如果树不为空，将 $v$ 与树的根进行比较。如果 $v$ 较小，则将 $v$ 插入到根的左子树中，否则插入到右子树中。

ACM 有一组天花板原型，它想通过尝试坍塌它们来进行分析。它想将具有相同树形状的天花板原型分组并一起分析。

例如，假设 ACM 正在考虑五个具有三层的天花板原型，如样例输入 1 所述并如图 1 所示。注意，第一个原型的顶层抗坍塌值为 2，中间层的值为 7，底层的值为 1。第二个原型的层的抗坍塌值为 3、1 和 4——然而这两个原型产生了相同的树形状，因此 ACM 将一起分析它们。

给定一组原型，您的任务是确定它们产生了多少种不同的树形状。

![](https://cdn.luogu.com.cn/upload/image_hosting/xvdteesl.png)

图 1：样例输入 1 中天花板原型所产生的四种树形状。

## 说明/提示

时间限制：5000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2016。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 3
2 7 1
3 1 4
1 5 9
2 6 5
9 7 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4
3 1 2 40000
3 4 2 1
33 42 17 23
```

### 输出

```
2
```

# 题解

## 作者：a___ (赞：4)

先按题意建出二叉搜索树，在按照每次是走向左儿子还是右儿子，可以将每个位置状压成唯一对应的数。然后哈希成 $\sin$ 和，最后输出不同 $\sin$ 和个数就好。    

```cpp
#include<cstdio>
#include<cmath>
#include<unordered_set>
const int N=22;
int q,n,son[N][2],val[N],cnt,rt,now;
std::unordered_set<long long>st;double sum;
void insert(int &rt,int x)
{
	if(!rt)return (void)(val[rt=++cnt]=x,son[rt][0]=son[rt][1]=0,sum+=sin(now));
	now<<=1;now|=x>=val[rt];insert(son[rt][x>=val[rt]],x);
}
int main()
{
	int i,x;scanf("%d%d",&q,&n);
	while(q--)
	{
		rt=cnt=sum=0;
		for(i=1;i<=n;i++)scanf("%d",&x),now=1,insert(rt,x);
		st.insert((long long)(sum*1e6));
	}
	printf("%d\n",st.size());
	return 0;
}
```

---

## 作者：MaiJingYao666 (赞：1)

# P6919 [ICPC 2016 WF] Ceiling Function 题解  
### 解题思路  
不妨发现这是一颗二叉搜索树，那么我们根据初赛的知识又能得到一颗二叉树的前序遍历和中序遍历确定唯一的树的形态，那么我们可以把树权离散化，由于中序遍历一定一样，即统计前序遍历的个数，用一个 `set` 就可以搞定了。是不是很简单？  
### AC 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
map<vector<int>,int> m;//什么？为什么我用map？
int ans;
int a[25],b[25];
int root;
int ch[25][2];
void dfs(int p,int x){//模拟过程
	while(1){
		if(x<p){
			if(!ch[p][0]){
				ch[p][0]=x;
				return;
			}
			p=ch[p][0];
		}
		else{
			if(!ch[p][1]){
				ch[p][1]=x;
				return;
			}
			p=ch[p][1];
		}
	}
}
vector<int> tmp;
void dfs2(int p){//统计前序
	tmp.push_back(p);
	if(ch[p][0]) dfs2(ch[p][0]);
	if(ch[p][1]) dfs2(ch[p][1]);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		for(int i=1;i<=k;i++){
			cin>>a[i];
			b[i]=a[i];
		}
		sort(b+1,b+k+1);
		for(int i=1;i<=k;i++){
			for(int j=1;j<=k;j++){//幽默N^2离散化
				if(b[i]==a[j]){
					a[j]=i;
					break;
				}
			}
		}
		root=a[1];
		memset(ch,0,sizeof ch);
		for(int i=2;i<=k;i++){
			dfs(root,a[i]);
		}
		tmp.clear();
		dfs2(root);
		if(!m[tmp]) ans++;
		m[tmp]++;
	}
	cout<<ans;
}
```

---

## 作者：__Ginka__ (赞：0)

#### 树的形状

树的形状由节点的连接方式决定，与节点的值无关。

通过序列化（将树的结构转化为字符串）可以判断两棵树的形状是否相同。

#### 步骤

初始化一个空的 BST。

将每层的抗塌值依次插入 BST。

序列化 BST，得到形状的字符串表示。

检查当前形状是否已经存在：如果不存在，将其加入集合。

#### 时间复杂度

插入操作：每次插入的时间复杂度为 $O(\log k)$，总插入复杂度为 $O(k \log k)$。

序列化操作：遍历整棵树，时间复杂度为 $O(k)$。

总体复杂度：$O(n \cdot k \log k)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
//定义二叉树节点结构
struct N
{
    int v;//节点的值
    N* l;//左子节点
    N* r;//右子节点
    N(int x):v(x),l(0),r(0){}//构造函数，初始化节点
};
int n,k,i,j,x,m;//n为原型数量，k为层数，i/j为循环变量，x为输入值，m为临时变量
N* rt;//定义根节点指针
vector<string> vs;//存储所有树的形状的字符串表示
string s;//存储当前树的形状
//将值v插入到树中
void ins(N*& r,int v)
{
    if(!r)
    {
        r=new N(v);
        return;
    }
    if(v<r->v)
    {
        ins(r->l,v);
    }
    else
    {
        ins(r->r, v);
    }
}
//将二叉搜索树序列化为字符串
string ser(N* r)
{
    if(!r)//如果当前节点为空，返回空字符串
    {
        return "";
    }
    string a=ser(r->l);
    string b=ser(r->r);
    return "L"+a+"R"+b;
}
//释放树的内存
void ft(N* r)
{
    if(!r)
    {
        return;
    }
    ft(r->l);
    ft(r->r);
    delete r;
}
int main()
{
    cin>>n>>k;
    for(i=0;i<n;i++)
    {
        rt=0;
        for(j=0;j<k;j++)
        {
            cin>>x;
            ins(rt,x);//插入
        }
        s=ser(rt);
        m=0;
        while(m<vs.size())
        {
            if(vs[m]==s)//如果找到相同的形状，跳出循环
            {
                break;
            }
            m++;
        }
        if(m==vs.size())//如果未找到相同的形状，将其加入vs
        {
            vs.push_back(s);
        }
        ft(rt);//释放 
    }
    cout<<vs.size();
    return 0;
}
```

---

## 作者：Tsz1024_AK (赞：0)

### 题意解析
对于每棵树，我们可以建好它的二叉搜索树，用字符表示这个节点的状态：`a` 表示它是叶子节点，`b` 表示它只有左儿子，`c` 表示它只有右儿子，`d` 表示它左右儿子都有，起初每个点的状态都是叶子节点。
### 题目思路
从一个树形得到一个这样的四进制数，可以确定一个树形，这是因为每一位存了当前结点的儿子信息，则当前结点的儿子情况是唯一确定的，且下一步走到哪个结点（即下一位存的是哪个节点的信息）也是唯一确定的。
### 核心代码
```cpp
if(arr[h].x>=arr[w].x){
		if(arr[w].r==0){
			arr[w].r=h;
			if(arr[w].l==0){
				arr[w].c='c';
			}else{
				arr[w].c='d';
			}
		}else{
			dfs(arr,arr[w].r,h);
		}
	}else if(arr[h].x<arr[w].x){
		if(arr[w].l==0){
			arr[w].l=h;
			if(arr[w].r==0){
				arr[w].c='b';
			}else{
				arr[w].c='d';
			}
		}else{
			dfs(arr,arr[w].l,h);
		}
	}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6919)
## 思路
对于每棵树，我们可以先建好它的二叉搜索树，用字符表示这个节点的状态。`a` 表示它是叶子节点，`b` 表示它只有左儿子，`c` 表示它只有右儿子，`d` 表示它左右儿子都有，起初每个点的状态都是叶子节点。
## 做法
对每一次读入进行建树，并在建树时修改每个点的状态。最后 dfs 求出由每个点的状态组成的中序遍历顺序，丢进 map 里，如果当前字符串没出现过，答案加一，打上标记。
## AC code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I n,k,a[30],len[50],ans;
map<string,I>r;
string tmp;
struct node{
	I x,l,r;
	char c;
}c[50][40];
void dfs(node a[],I where,I who){//把节点加进去 
	if(a[who].x >= a[where].x){//放进左边还是右边
		if(a[where].r == 0){//没有右儿子，补上 
			a[where].r = who;
			if(a[where].l == 0){//左儿子没有的话，状态是 c 
				a[where].c = 'c';
			}else{//否则就补全了，状态为 d 
				a[where].c = 'd';
			}		
		}else{//已经有右儿子了，继续遍历 
			dfs(a,a[where].r,who);
		}
	}else if(a[who].x < a[where].x){
		if(a[where].l == 0){//没有做儿子，补上左儿子 
			a[where].l = who;
			if(a[where].r == 0){//没有右儿子，状态是 b 
				a[where].c = 'b';
			}else{//两个都有，状态是 d 
				a[where].c = 'd';
			}
		}else{//有左儿子了，继续遍历 
			dfs(a,a[where].l,who);
		}
	}
}
void gf(node a[],I root){//求出中序遍历 
	if(root == 0) return;//及时退出 
	tmp += a[root].c;//加上当前状态 
	if(a[root].l){//遍历儿子 
		gf(a,a[root].l);
	}
	if(a[root].r){
		gf(a,a[root].r);
	} 
}
I main(){
	scanf("%d%d",&n,&k);
	for(;n--;){
		for(I i = 1;i <= k;i++){
			I x;
			scanf("%d",&x);
			len[n]++;
			c[n][len[n]].c = 'a';
			c[n][len[n]].x = x;
			if(len[n] != 1) dfs(c[n],1,len[n]);//加入节点 
		}
		tmp.clear();//清空，不然会继承上一次操作的值 
		gf(c[n],1);
		if(!r[tmp]){//查重 
			r[tmp]++;
			ans++;
		}
		//cout<<tmp<<endl;/*调试代码*/
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：whhsteven (赞：0)

按题意建出 BST 并数出有多少种树形即可。

这里有一种存树形时不丢失信息的实现：

设一个结点 是叶子 / 只有左儿子 / 只有右儿子 / 左右儿子均有 分别表示为 $0/1/2/3$，这样按先序遍历顺序依次记录每一个结点的状态，就可以用一个四进制数表示整棵树的形态。

从一个树形显然可以唯一得到一个这样的四进制数，而易见从一个合法的四进制数也可以唯一确定一个树形，这是因为每一位存了当前结点的儿子信息，则当前结点的儿子情况唯一确定，且下一步走到哪个结点（即下一位存的是哪个节点的信息）也唯一确定。

本题中 BST 的结点数不超过 $20$，则存树形所需的四进制数值不超过 $4^{20}-1 = 1,099,511,627,775$，用 long long 就可以存下。

---

