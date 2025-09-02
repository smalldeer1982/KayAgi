# Bmail Computer Network

## 题目描述

Once upon a time there was only one router in the well-known company Bmail. Years went by and over time new routers were purchased. Every time they bought a new router, they connected it to one of the routers bought before it. You are given the values $ p_i $ — the index of the router to which the $ i $ -th router was connected after being purchased ( $ p_i < i $ ).

There are $ n $ routers in Boogle in total now. Print the sequence of routers on the path from the first to the $ n $ -th router.

## 样例 #1

### 输入

```
8
1 1 2 2 3 2 5
```

### 输出

```
1 2 5 8 ```

## 样例 #2

### 输入

```
6
1 2 3 4 5
```

### 输出

```
1 2 3 4 5 6 ```

## 样例 #3

### 输入

```
7
1 1 2 3 4 3
```

### 输出

```
1 3 7 ```

# 题解

## 作者：A_Đark_Horcrux (赞：3)

首先，如果从1往下找的话，肯定是比较麻烦的。

所以我们不妨逆向思考：用一个变量模拟从n走到1的过程，记录走到1的路径，然后反向输出

由于每个节点的父节点是确定的，而最终一定会走到根节点1，所以这个方法是正确的qwq

```cpp
#include<cstdio>
using namespace std;
const int N=2e5+10;
inline int read()
{
	int s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if (c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s*b;
}//快读
int n,now,l,i,fa[N],a[N];
int main()
{
	n=read(); now=n;//now是我们用来模拟的变量
	for(i=2;i<=n;i++) fa[i]=read();//输入每个节点的父节点
	do a[++l]=now,now=fa[now]; while(now!=1);//只要还没走到1，那就先记录，然后将now更新为他的父节点
	printf("1 "); for(i=l;i>=1;i--) printf("%d ",a[i]);//倒序输出，注意记录路径时没有加入1，所以要先在前面输出1
	return 0;//完结撒花awa
}

```


---

## 作者：asasas (赞：2)

这题用到了一个用来存树的数据结构：**父数组**

顾名思义，父数组是用来存结点的父亲的数组。

你们是不是想到了另一个数据结构？没错！并查集就用到了这个数据结构。

这题求得是1到$n$的路径。由于是有向边，所以我们从n开始，一直访问它的父亲节点，直到父亲为1为止。最后**倒序**输出访问过程中经过的节点即可。

代码：
```cpp
#include <algorithm> 
using namespace std;
int fa[1000005],ans[1000005];
int main(){
	int n;
	scanf("%d",&n);
	fa[1]=1;//1的父亲就是1
	for (register int i=2;i<=n;i++){
		int x;
		scanf("%d",&fa[i]);
	}
	int now=n,cnt=0;//now从n开始往下递归
	while(now!=1){
		ans[++cnt]=now;//记录当前节点
		now=fa[now];//访问它的父亲结点
	}
	sort(ans+1,ans+1+cnt);//倒序
	printf("1 ");//由于now=1就停止了
	for (register int i=1;i<=cnt;i++) printf("%d ",ans[i]);
}
```


---

## 作者：Paranoia__zzy (赞：1)

这题其实非常简单：
- 先用b[i]记录每个点的编号，
- 再用i记录每个点的父节点的下标

**举个例子**：

8
1 1 2 2 3 2 5

| 编号 | 1 |2  |3  | 4 | 5 | 6 | 7 |8  |
| :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- |
|父节点  |1  |1  |1  |2  |2  | 3 |2  |5 | 

1. b[1] 记录节点（8），i记录父节点5的下标（5）。
2. b[2] 记录节点（5），i记录父节点2的下标（2）。
3. b[3] 记录节点（2），i记录父节点1的下标（1）。
4. b[4] 记录节点（1），打印。
- **注意：节点1的父节点还是1，不注意会出现死循环。**

 _**接着上代码：**_ 
```c
#include <cstdio>
int n,a[200005],b[200005],z=1;
int main() {
	scanf("%d",&n);
	a[1]=1;
	for(int i=2; i<=n; i++)
    scanf("%d",&a[i]);
	for(int i=n; i>1; i=a[i])//i=a[i]用来记录每个点对应数的下标
    	b[z++]=i;//记录编号，因为是倒着做的并且要正的输出，所以本蒟蒻开了一个数组
	b[z]=1;这里单独处理b[z]是为了防止出现第一个指向第一个而产生死循环
	for(int i=z; i>=1; i--)
    printf("%d ",b[i]);//倒着输出
	return 0;
}
```


---

## 作者：午尘 (赞：1)

这题还是挺基础的qwq……

方法：记录父节点，不断往上搜。

------------

这是代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,i,j,k,fa[1000001],t,qwq,b[1000001];
int main(){
	scanf("%d",&n);
	for (i=2;i<=n;i++) scanf("%d",&fa[i]);
	j=0;qwq=n;
	fa[1]=0;//方便判断是否搜完了 
	while (fa[qwq]!=0){
		j++;
		b[j]=qwq;  //记录 
		qwq=fa[qwq];  //往父节点上搜 
	}
	cout<<1<<" ";//qwq==1时退出了，没有在b数组 
	for (i=j;i>=1;i--) cout<<b[i]<<" ";  //b数组是n->1,所以要倒序输出 
	return 0;
}

```



---

## 作者：gary2005 (赞：1)

这题真的不复杂

就是顺着最下面往上走就行了

dfs到根时退出

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,up[200005];
void dfs(int now){
	if(now!=1) dfs(up[now]);
	cout<<now<<" ";
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>up[i];
	dfs(n);
	return 0;
}
```

---

## 作者：damage (赞：0)

# 题解

正向思维看起来比较难，树上$DFS$，当作一个图搜索，跑$SPFA$，枚举每种走法？

但是我这种蒟蒻怎么可能会呢，于是我们要**逆向思维**！

很容易就能想到路径就是从$n$往上爬，把爬的路程反向输出即可。

~~$\sout{LCA}$！~~

因为是反向输出，所以要记录路程，可以用数组记录。但是现在可是科技化的时代，当然要用~~$\sout{C}$++的外挂~~$STL$了！

本蒟蒻想到的可以选择的：

1. $vector$向量：

 1. 使用```push_front()```函数，但是众所周知$vector$用的是一段连续的内存，所以使用一次```push_front()```函数的时间复杂度实际上却是$O(k)$，其中$k$为此时向量中的元素。所以复杂度为$O(n^{2})$，会超时。
 
 2. 使用```push_back()```函数（正常插入），输出时使用```back()```函数，再用```erase(v.end()-1)```删除，可行。
 
2. $deque$双端队列
 - 正常从队尾插入，再从队尾向前遍历，类似$vector$中的第二种方法。
 
3. $stack$栈
 - 各位大佬应该能够立刻想到的数据结构。因为是$FILO$（先进后出）的数据结构，所以它的正常操作即可以满足题目的要求（本蒟蒻用的方法）。
 
### 注意一开始的时候要把$n$（最后走到的终点节点）给```push()```进去
 
---
 
# 代码
 
```cpp
#include<stdio.h>
#include<stack> //栈的头文件
using namespace std;
int n,p[200010];
stack<int> path; //栈
int main()
{
    scanf("%d",&n);
    for(register int i=2;i<=n;++i) scanf("%d",&p[i]); //输入父亲节点
    path.push(n); //记得先push(n)
    while(n!=1) //从终点开始反向遍历直到起点
    {
        n=p[n]; //到父节点
        path.push(n); //保存路径
    }
    while(!path.empty()) //输出路径
    {
        printf("%d ",path.top());
        path.pop();
    }
    return 0;
}
```

---

