# Column Swapping

## 题目描述

如果一个表格每行都单调不降，称它为好的。  
给你 $t$ 个 $n_i$ 行 $m_i$ 列的表格，对于每个表格，询问是否能通过调换某两列 **（不一定不同）** 使得这个表格是好的（这样的操作需要且仅能执行一次）。如果可以，输出两列的编号；不可以，输出 $-1$。

## 说明/提示

$1\le t\le 100$  
$1\le n,m\le 2\times 10^5$  
$\sum n\times m\le 2\times 10^5$  
表格中的每一个数不超过 $10^9$  

**样例解释**  
**第一个**表格原本就是好的，因此可以将第一列和自己对调。  

**第二个**表格中，对调第 $1$ 和第 $2$ 列，会变成  
$$1,4$$  
$$3,2$$  
不是好的。如果对调任意一列和它自己，就是原本的表格，不是好的。因此输出`-1`。  

**第三个**表格中，对调第 $1$，$2$ 列，表格变为  
$$1,2$$
$$1,1$$
是好的。因此输出`1 2`。  

**第四个**表格中，调换第 $1$，$3$ 列，表格变为  
$$1,2,6$$  
$$3,4,5$$  
表格变为好的。输出 `1 3`  

**最后一个**表格中，每一行只有一个数，是单调不降的，但是只有一列，所以需要将这一列和自己对调。

## 样例 #1

### 输入

```
5
2 3
1 2 3
1 1 1
2 2
4 1
2 3
2 2
2 1
1 1
2 3
6 2 1
5 4 3
2 1
1
2```

### 输出

```
1 1
-1
1 2
1 3
1 1```

# 题解

## 作者：fuxuantong123 (赞：6)

# CF1684C Column Swapping 题解
## 简化题意
给你一个 $n \times m$ 的表格，问调换哪两列 **（不一定不同，并且所有行都要一块换）** 可以使表格每一行都单调不降，无解输出 $-1$。

## 思路方法
首先，找出每行需要交换的错点，如果错点数大于 $2$，则肯定是无解。

如果错点数为 $0$，则代表这行已经不降。

求错点也很简单，把每行按升序排个序，再和原数组比对，同一位置两数不同，则此位置就是错点。

因为只是把原数组排序，所以错点不可能为 $1$。

把当前的错点位置和之前记录下的错点位置比对，如果不匹配，也是无解。

如果之前或现在错点数为 $0$ 则另需特判（见代码）。
## 代码

这题细节还挺多的，我用 vector 时忘了从 $0$ 开始，卡了好久。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
vector<int> c[200010];
int b[200010];
vector<int> s;
vector<int> x;
bool check(int w){
	if(w==1){
		return 1;
	}
	for(int i=1;i<w;i++){
		if(c[i][x[0]-1]!=c[i][x[1]-1]){
			return 0;
		}
	}
	return 1;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		x.clear();
		s.clear();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			c[i].clear();
		}
		int flag=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[j]);
				b[j]=a[j];
			}
			for(int j=1;j<=m;j++){
				c[i].push_back(a[j]);
			}
			x.clear();
			if(m==1){
				flag=0;
				continue;
			}
			if(flag){
				continue;
			}
			sort(b+1,b+m+1);
			for(int j=1;j<=m;j++){
				if(b[j]!=a[j]){
					x.push_back(j);
				}
			}
			if(x.size()>2){
				flag=1;
				continue;
			}
			if(x.size()==0){//特判，如果当前错点数为零，则需之前错点数也为0，或当前数组允许按照之前的错点位置交换（a[s[0]]==a[s[1]]）
				if(s.size()==0){
					continue;
				}
				if(a[s[0]]==a[s[1]]){
					continue;
				}
				flag=1;
				continue;
			}
			if(s.size()==0){//同上，check是检查之前的数组是否允许按照现在的错点位置交换
				if(check(i)){
					s.push_back(x[0]);
					s.push_back(x[1]);
					continue;
				}
				else{
					flag=1;
					continue;
				}
			}
			for(int j=0;j<x.size();j++){
				if(s[j]!=x[j]){
					flag=1;
					break;
				}
			}
		}
		if(m==1){
			flag=0;
		}
		if(flag==1){
			printf("-1\n");
			continue;
		}
		if(s.size()==0){
			printf("1 1\n");
			continue;
		}
		printf("%d %d\n",s[0],s[1]);
	}
return 0;
}
```


---

## 作者：legend_cn (赞：4)


## **1 简化题意**

给你一个矩阵 $gra$，问需要互换那两行可以让矩阵里的每一行都大于等于上一行。

## **2 思路**

这道题不涉及一点算法思路，是一道需要考虑多种情况的分类讨论模拟题。

首先，如果每一行都是单调不降的，我们可以直接输出 $1$ $1$ 代表无需调换。

题目中提到了“不一定不同”。换个说法也就是可以相同，意味着根本不互换也是一种方案。

 ### **情况 1：**

如果一个表格对于全部的 $gra_{i,j}$，若同时满足以下两个条件：
+ $j>1$
+ $g_{i,j}>g_{i,j-1}$

就可以交换任意一列和它本身了。这道题中只能让第 $1$ 列与它本身互换，不然其它列可能不存在。

### **情况 2：**

首先需要赋值 $a_0=-∞$，$a_n+1=+∞$

如果有两列 $i$，$j$，若同时满足以下两条件：
+ $a_i-1 \leq a_j \leq a_i+1$
+ $a_j-1 \leq a_i \leq a_j+1$

互换后即可满足局部单调不降。

如果将 $a$ 排序得到 $b$，满足 $a_i \ne b_i$ 的，那么 $i$ 这一列就需要被换走。

### **综上：**

+ 如果行内需要被换走的超过两列，就输出 $-1$。（因为只能换一次）
+ 如果行内需要被换走的等于两列，再分为两种情况：
   - a.“不可以被交换”，就输出 $-1$；
	- b.“可以被交换”，并且已经记录的 $i$，$j$ 和它不一样，就输出 $-1$；否则，继续判断下一行。如果所有行都没有，就更新记录的坐标。
+ 不可能出现行内需要被换走的只有一列，因为 $a$ 一定是由 $b$ 交换两个数得到。这就像连线题一错至少两个一样。
+ 如果行内没有需要被换走的，就不记录。

+ 如果没有记录过，表格就满足题目要求。

## **3 AC 代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[200005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		int y=-1,_y=-1;
		bool flag=1;
		vector<int>a[200005];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				int k;
				cin>>k;
				a[i].push_back(k);
				b[j]=k;
			}
			if(!flag)
				continue;
			sort(b,b+m);
			int x=-1,_x=-1;
			for(int j=0;j<m;j++)
			{
				if(a[i][j]!=b[j])
				{
					if(!~x||x==j)
						x=j;
					else if(!~_x||_x==j)
						_x=j;
					else
					{
						flag=0;
						break;
					}
				}
			}
			if(!~y)
			{
				y=x;
				_y=_x;
			}
			else
			{
				if(~x)
				{
					if(x!=y||_x!=_y)
						flag=0;
				}
				else if(a[i][y]!=a[i][_y])
					flag=0;
			}
		}
		if(~y)
		{
			for(int i=0;i<n;i++)
			{
				if(a[i][y]<a[i][_y])
				{
					flag=0;
					break;
				}
			}
		}
		if(flag)
		{
			if(!~y)
				cout<<"1 1\n";
			else
				cout<<y+1<<" "<<_y+1<<"\n";
		}
		else
			cout<<"-1\n";
	}
}
```


---

## 作者：Marxistdzy (赞：1)

注意！这是一篇 Python 题解！用 Python 真的很简洁。（确信确信）
### 题意简述
给一个表格，问调换哪两个**不一定不同**的列可以使表格每一行都单调不降。如果无解则输出 $-1$。
### 思路方法
- 首先，根据题意，易得如果每一行都是单调不降的，我们可以直接输出 ```1 1``` 代表无需调换。
- 排序之后，原序列跟排序后对应位置不同的位置即为需要更改的，即 ```bad``` 数组的长度（在 Python 中用 ```len``` 函数求出）。如果 len(bad)$ > 2$，则无解。
- 如果不属于以上两种情形，就可以判断每列是否满足要求，记录输出即可。
- 特别地，判断时，发现如果记录过的有不一样的，即 ```check=False```，仍然无解。

#### AC代码：
```python
def solve(arr):
#使用自定义slove函数
    bad = []
    for i in range(len(arr)):
        b = list(arr[i])
        b.sort()
        for j in range(len(b)):
            if arr[i][j] != b[j]:
                bad.append(j)
        if len(bad)>0:
            break
    if len(bad)==0:
        print(1,1) #输出 1 1 代表无需调换
    elif len(bad)>2:
        print(-1) #输出-1，即无解
    else:
        for i in range(n):
            arr[i][bad[0]],arr[i][bad[1]] = arr[i][bad[1]],arr[i][bad[0]]
        check = False
        for i in range(n):
            if arr[i] !=sorted(arr[i]):
                check = True
                break
        if check:
            print(-1)
        else:
            print(bad[0]+1,bad[1]+1)

for i in range(int(input())):
    n,m = map(int,input().split())
    lis=[]
    for i in range(n):
        lis.append(list(map(int,input().split())))
    solve(lis)
```
如有不当之处敬请各位神犇指出！人生苦短，我用 Python！

---

## 作者：fast_photon (赞：1)

**0. 前言**  
[这题](https://www.luogu.com.cn/problem/CF1684C)分类讨论有点多，如果漏分类了欢迎 hack~  
分析中 $g$ 指的是表格，而 $a$ 表格中的任意一行。

**1. 题意**  
给一个表格，问调换哪两列 **（不一定不同）** 可以使表格每一行都单调不降，无解输出 $-1$。  

**2. 分析**  
我们首先解析题目中这个(not necessarily different)，也就是不一定不同。  
不一定不同，那就是可以相同，进而就是可以不交换。  
如果一个表格本来是好的（判断很简单，对于全部 $g_{i_j}$，如果 $j>1$，那么满足 $g_{i_j}>g_{i_{j-1}}$ ，这个表格就是好的），那么直接交换第 $1$ 列与它自身就可以了。注意 **不要** 作死写你的幸运数字，因为那一列不一定存在。  
什么样的两列 $i,j$ 可以被交换呢？  
对于任何一行，满足 $a_{i-1}\le a_j\le a_{i+1}$ 并且 $a_{j-1}\le a_i\le a_{j+1}$ 即可。（此处默认 $a_0=-\infty $ 且 $a_{n+1}=\infty$），即互换后局部单调不降。  
什么样的一列 $i$ 需要被换走呢？   
将 $a$ 排序得到 $b$，满足 $a_i\ne b_i$ 的。  
1. 如果行内需要被换走的超过两列，那么无解（因为只能换一次）  
2. 如果行内需要被换走的恰好两列。  
   1. 但是不“可以被交换”，那么无解。  
   2. 而且“可以被交换”，并且已经记录的 $i,j$ （如果有的话）和它不一样，无解。一样，继续判断下一行。如果没有，那么记录这一对。
3. 不可能出现行内需要被换走的只有一列，因为 $a$ 一定是由 $b$ 交换两个数得到。这就像连线题一错至少两个一样。  
4. 如果行内没有需要被换走的，不进行记录。  
最后就是愉快地看最终结论了。如果没有记录过，表格本来就是好的。  

如果记录过的 $i,j$ 都一样，**不能直接输出**，而是要判断是否每一行的 $i,j$ 都“可以被交换”，如果是那么输出，不是无解，否则就会像样例2一样，把一行变成好的但是打乱了另一行。  
如果记录过的有不一样的，无解。  
**只要有一次无解直接输出 `No Solution` 并且进入下一组数据。**  

**3. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define maxn 200005

using namespace std;

int t, n, m;
int b[maxn], y1 = -1, y2 = -1;
vector<int> a[maxn];
bool flag;

int main() {
	scanf("%d", &t);
	while(t--) {
		y1 = y2 = -1;
		flag = true;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) a[i].clear();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int k;
				scanf("%d", &k);
				b[j] = k;
				a[i].push_back(k);
			}
			if(a[i].size() != m) return 0;
			if(!flag) continue; 
			sort(b, b + m);
			int x1 = -1, x2 = -1;
			for(int j = 0; j < m; j++) {
				if(a[i][j] != b[j]) {
					if(!~x1 || x1 == j) {
						x1 = j;
						if(t == 0) {
							//printf("%d %d\n", a[i][j], b[j]);
						}
					}
					else if(!~x2 || x2 == j) {
						x2 = j;
					}
					else {
						flag = false;
						break;
					}
				}
			}
			if(!~y1) {
				y1 = x1, y2 = x2;
			}
			else {
				if(~x1) {
					if(x1 != y1 || x2 != y2) {
						flag = false;
					}
				}
				else if(a[i][y1] != a[i][y2]) flag = false;
			}
			//printf("%d %d\n", x1, x2);
		}
		if(~y1)
		for(int i = 0; i < n; i++) {
			if(a[i][y1] < a[i][y2]) {
				flag = false;
				if(t == 2) {
					//printf("%d %d %d %d\n", y1, y2, a[i][y1], a[i][y2]);
				}
				break;
			}
		}
		if(flag) {
			if(!~y1) {
				printf("1 1\n");
			}
			else printf("%d %d\n", y1 + 1, y2 + 1);
		}
		else printf("-1\n");
	}
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

$3$ 分 $55$ 秒开始。

![](bilibili:BV15U4y127QD)

### 2 思路

设第 $i$ 行第 $j$ 列的数为 $a[i][j]$。

很明显，如果每一行都是单调不降的，我们可以直接输出 `1 1` 代表啥都不动。

设 $i$ 使得第 $i$ 行是无序的，但前面的所有行都是单调不降的。

那么，我们将第 $i$ 行排一下序，原序列跟排序后对应位置不同的位置即为需要更改的。如果这种位置的数量大于 $2$，就直接无解；

否则，设这 $2$ 个位置分别为 $l$，$r$，我们要判断，如果选定 $l$ 和 $r$，其他行是否满足要求。输出即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define max_n 200000
int t;
int n;
int m;
vector<int>v[max_n+2];
int a[max_n+2];
int b[max_n+2];
int c[max_n+2];
int ans[2];
bool ok(){
	for(int i=1;i<m;++i)if(a[i]>a[i+1])return false;
	return true;
}
bool ok2(){
	for(int i=1;i<=m;++i)b[i]=a[i];
	sort(b+1,b+m+1);
	int cnt=0;
	for(int i=1;i<=m;++i){
		if(a[i]!=b[i])c[++cnt]=i;
	}
	return cnt<=2;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)v[i].clear();
		ans[0]=ans[1]=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				scanf("%d",a+j);
				v[i].push_back(a[j]);
			}
			if(ans[0]==-1)continue;
			if(ans[0]==0){
				if(ok())continue;
				if(ok2()){
					ans[0]=c[1];
					ans[1]=c[2];
					swap(a[ans[0]],a[ans[1]]);
					for(int j=1;j<i;++j){
						if(v[j][c[1]-1]!=v[j][c[2]-1]){
							ans[0]=-1;
							break;
						}
					}
					if(!ok()){
						ans[0]=-1;
						continue;
					}
				}
				else{
					ans[0]=-1;
					continue;
				}
			}
			else{
				swap(a[ans[0]],a[ans[1]]);
				if(!ok()){
					ans[0]=-1;
					continue;
				}
			}
		}
		if(ans[0]==0){
			printf("1 1\n");
			continue;
		}
		if(ans[0]==-1){
			printf("-1\n");
			continue;
		}
		printf("%d %d\n",ans[0],ans[1]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76116348)

By **dengziyue**

---

