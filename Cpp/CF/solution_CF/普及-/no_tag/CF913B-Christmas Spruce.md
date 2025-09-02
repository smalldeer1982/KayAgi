# Christmas Spruce

## 题目描述

Consider a rooted tree. A rooted tree has one special vertex called the root. All edges are directed from the root. Vertex $ u $ is called a child of vertex $ v $ and vertex $ v $ is called a parent of vertex $ u $ if there exists a directed edge from $ v $ to $ u $ . A vertex is called a leaf if it doesn't have children and has a parent.

Let's call a rooted tree a spruce if its every non-leaf vertex has at least $ 3 $ leaf children. You are given a rooted tree, check whether it's a spruce.

The definition of a rooted tree can be found [here](https://goo.gl/1dqvzz).

## 说明/提示

The first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/3d87b6a6cda0ba6f4ad05908fb42ae8248c8369b.png)

The second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/bd0b03933e2dbb274b2b58b0c7a13d930c39c80b.png)

It is not a spruce, because the non-leaf vertex $ 1 $ has only $ 2 $ leaf children.

The third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/a9d72240b2a5e338c43541d320aabfb5ee526dff.png)

## 样例 #1

### 输入

```
4
1
1
1
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
7
1
1
1
2
2
2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
8
1
1
1
1
3
3
3
```

### 输出

```
Yes
```

# 题解

## 作者：吴思诚 (赞：3)

## CF913B Christmas Spruce
[题目传送门](https://www.luogu.com.cn/problem/CF913B)

**如果一颗有根树的每个非叶结点至少有三个是叶结点的孩子，这棵树是一棵云杉**

此为关键。于是考虑从树根开始搜索，遇到叶子节点回溯。每次把这个节点的孩子节点中不是叶子节点的统计出来。把这个值设为 $cnt$，把他的所有孩子节点设为 $len$，即每次必须满足 $len-cnt>3$。如果始终满足条件，则是云杉。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[10001],ans,x;
vector<int>g[10001];
void dfs(int x){
	int len=g[x].size();
	int cnt=0;
	if(!len)
		return;
	for(int i=0;i<len;i++){
		int v=g[x][i];
		if(g[v].size())
			cnt++;
	}
	if(len-cnt<3){
		cout<<"No";
		exit(0);
	}
	for(int i=0;i<len;i++){
		int v=g[x][i];
		dfs(v);
	}
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		g[x].push_back(i);
	}
	dfs(1);
	cout<<"Yes";
	return 0;
}
```


---

## 作者：nalemy (赞：0)

## 题目分析

这道题的目标是判断**是否每个非叶子节点都有至少三个叶子节点孩子**

那么我们的想法就很明确啦！

首先用一个数组$lf$记录是否是叶子节点。

由于要遍历节点检查自己的孩子，就要把自己的孩子存起来。这里我们使用 vector（也就是邻接表存树）

## AC代码

```C++
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define N 1000
using namespace std;

int n;
bool lf[N];
vector<int> g[N];
bool inline check_node(int u) {
    int cnt = 0;
    for (int i=0, sz=g[u].size(); i<sz; i++) {
        if (lf[g[u][i]]) cnt++;
        if (cnt == 3) return true;
    }
    return false;
}
bool inline check_tree() {
    for (int u=0; u<n; u++)
        if (!lf[u] && !check_node(u))
            return false;
    return true;
}
int main() {
    cin >> n;
    memset(lf, 1, sizeof(lf));
    for (int v=1, u; v<n; v++)
        cin >> u, g[u-1].push_back(v), lf[u-1] = false;
    cout << (check_tree() ? "Yes" : "No");
    return 0;
}
```



---

## 作者：wenkaijie (赞：0)

### 思路：将每个节点的编号、父节点、子节点放进一个结构体中，然后循环判断每个节点是否至少有3个子叶节点。
#### 直接上代码：
```cpp
# include <stdio.h>
# include <iostream>
# include <string.h>
# include <string>
# include <algorithm>
# include <math.h>
# include <queue>//本蒟蒻知道的所有头文件
using namespace std;
struct node//节点的结构体
{
	int id,father,numk,kid[1001];//id：编号，father：父节点，numk：子节点的个数，kid：子节点
}tree[1001];//树
bool three_leaves(int xx)//判断函数
{
	node x=tree[xx];
	if(x.numk==0)
		return 1;//叶节点不用判断
	if(x.numk<3)//如果子节点个数<3，就直接废了
		return 0;
	int cnt=0;//cnt用来记录子叶节点的个数
	for(int i=1;i<=x.numk;i++)
		if(tree[x.kid[i]].numk==0)
			cnt++;
	return cnt>=3;//返回cnt是否>3
}
int main()
{
	int n;
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&tree[i].father);
		tree[tree[i].father].kid[++tree[tree[i].father].numk]=i;
     //这里解释一下：tree[tree[i].father]是i号节点的父节点，先把它的子节点数量++，再赋值。
	}
	for(int i=1;i<=n;i++)//x循环判断
		if(!three_leaves(i))
		{
			cout<<"No";//有一个不成立就不是云杉
			return 0;
		}
	cout<<"Yes";//全成立就是云杉
	return 0;//开心的结束
}
```


---

## 作者：judgejudge (赞：0)

# 用二维数组代替树形结构
因为我的树形结构学的不是很好，所以这里用二维数组。

首先我们把题目给的条件**用二维数组储存起来**，如样例1：
```cpp
4
1
1
1
```
那么我们可以令二维数组的列定义为第几个顶点，后面用于记录孩子是谁，再用一个一维数组记录长度。
| 顶点 | 孩子1 | 孩子2 | 孩子3 |孩子数  |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 |  2| 3 | 4 | 3 |
|  2| 0 | 0 | 0 | 0 |
| 3 |0  |0  |0  | 0 |
|  4| 0 | 0 | 0 | 0 |
这样我们可以**根据长度是否为0来判断是否是叶结点**。

#### 如果不是叶结点：
那么我们用函数来查找它有几个是叶结点的孩子，如果不满足要求直接输出No，结束程序。

如果全部满足要求输出Yes。

AC代码：
```cpp
#include <iostream>
using namespace std;
int a[1001][1001];//二维数组，分别记录顶点和孩子
int l[1001];//长度：记录孩子数
int dp(int n){
	if(l[n]==0)return 1;//根据长度判断是否是根结点
	else return 0;
}
int f(int n){
	int i,j,k=0;
	if(l[n]<3)return 0;//优化：如果本身根结点小于3，直接结束
	else{
		for(i=1;i<=l[n];i++)
		if(dp(a[n][i])>0)k++;//看孩子是否是根结点，记录个数
	}
	if(k<3)return 0;//判断是否满足要求
	else return 1;
}
int main(){
	int i,j,k,n;
	cin>>n;
	for(i=1;i<n;i++){
		cin>>k;
		l[k]++;//长度++
		a[k][l[k]]=i+1;//及该顶点的第几个孩子是谁
	}
	for(i=1;i<=1000;i++)
	if(l[i]>0){//如果长度大于0，说明是非根结点
		if(f(i)==0){//f函数判断孩子个数是否满足要求
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
} 
```



---

## 作者：06ray (赞：0)

这道题算式数据结构树中一个比较简单的题目了，没有什么树的遍历，只考了一个树的存储方式，模拟一遍就OK了。首先定义两个数组，分别为father数组和kids数组。father[i]表示第i个节点的父亲编号；kids是一个bool类型的数组，kids[i]表示第i个节点它是否有孩子，有就是true，木有就是false。

接下来开始读入并建树。先读入n，再读入每个节点用node，这时候就要建树了，怎么建呢？很简单，进行以下操作：father[i]=node;kids[node]=true;

建好树之后，就开始枚举每个节点了，首先判断它是否为非叶子节点，再判断它是否满足题意中的条件，即有三个是叶结点的孩子，（这里用一个循环，我用了一个函数），如果它是非叶子节点，但不满足条件，那就输出No,直接退出程序。

最后结束循环，就可以输出Yes。

总体思路就是这样，还是比较好理解的。

下面贴上简短的代码。（有注释）

```cpp
#include <iostream>//头文件
using namespace std;
int father[10000];//表示每个节点的父亲编号
bool kids[10000];//表示每个节点是否有孩子。
int n;
bool pd(int node)//判断函数
{
	int sum=0;
	for(int i=1; i<=n; i++)
	if(node!=i&&father[i]==node&&!kids[i])//如果第i个节点是它的儿子且这个节点是叶子节点
	{
		sum++;//sum加1
	}
	return sum>=3;//最后判断sum是否大于3
}
int main()
{
	cin>>n;//读入n
	for(int i=2; i<=n; i++)//读入每个数，注意i要从2开始
	{
		int node;
		cin>>node;//读入第i个节点编号
		father[i]=node;//第i个节点的父亲为node
		kids[node]=true;//node已经有孩子了
	}
	for(int i=1; i<=n; i++)//枚举每个节点
	{
		if(kids[i]&&!pd(i))//如果它是非空节点且不满足条件
		{
			cout<<"No";//输出No
			return 0;//结束程序
		}
	}
	cout<<"Yes";//可以放心大胆地输出Yes
	return 0;
}
```

---

## 作者：zythonc (赞：0)

**~~看了各位大佬的题解，我都不敢发自己的题解了~~**
# 进入正文，CF913B题解
## 先介绍一下我的思路：非法逻辑强制中断算法+纯模拟树（数组表示）
**[萌萌的算法介绍链接](https://www.luogu.org/blog/zythonc/solution-p1115)**

**这里再介绍一下**

        非法逻辑强制中断就是在得到冗余数据时及时暂停循环线程，并使其进入下一阶段运算，从而防止TLE的情况发生。
~~没错，就是剪枝~~

## 这道题的大意：判断一颗有根树的每个非叶结点是不是至少有三个叶结点

**明白大意后，就是过程与剪枝。（过程在代码里，直接说剪枝）**
## 剪枝：

**剪枝一：节点非零且小于3，输出No**

剪枝二：叶子小于3，输出No（严格来说，这个其实不算剪枝）

**剪枝三：是叶节点的，不用判断**

```
#include<iostream>
using namespace std;
struct tree					//建树，结构体包含三个数据。r是根，这里用不到注释掉；jsq就是计数器，这里表示孩子的个数；c数组是每个孩子。
{
	//int r;
	int jsq=0;				//初始化0，建议大家不要在结构体里初始化
	int c[1001];
}d[1001];
int main()					//主程序，数据先生开始闯关了！！！
{
	int a,b,leaf=0;
	cin>>a;
	for(int i=2;i<=a;i++)	//根节点是1，不用输入，所以从2开始
	{
		cin>>b;				//输入孩子的根
		//d[i].r=b;			//注释掉
		d[b].c[d[b].jsq]=i;	//这里要慢慢理解了：d[b]是孩子的根，c[~~]是孩子的根的孩子数据，jsq是现有的孩子个数
		d[b].jsq+=1;		//生了一个孩子（邪恶）
	}
	for(int i=1;i<=a;i++)
	{
		leaf=0;				//根的叶节点初始为0
		if(d[i].jsq==0)		//为零的是一个叶节点，不用判断
			continue;
		else if(d[i].jsq<3)	//孩子个数都小于3了，那叶节点肯定不会大于3
		{
			cout<<"No";		//输出
			return 0;		//结束
		}
		else
		{
			for(int o=0;o<d[i].jsq;o++)	//遍历孩子
			{
				if(d[d[i].c[o]].jsq==0)	//孩子的孩子个数如果为零
					leaf+=1;			//那他就有一片叶子了
			}
			if(leaf<3)					//叶子小于3
			{
				cout<<"No";				//不用遍历了，结束吧
				return 0;
			}
		}
	}
	cout<<"Yes";						//以上情况都没有杀死数据，就算他闯关成功了！！！
}
```

**[又是萌萌的链接](https://www.luogu.org/blog/zythonc/)**

**写这么多注释累成狗。。。**

# 感谢阅读本蒟蒻的题解


------------

### 点个赞再走呗~~~

---

