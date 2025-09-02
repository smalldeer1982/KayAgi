# [COCI 2019/2020 #2] Slagalica

## 题目背景

## 本题征集 SPJ。但若您写的是正解，即，输出了字典序最小解，仍可获得 AC 的评测结果。


小斌喜欢玩拼图。

## 题目描述

小斌得到了一个由 $n$ 个部分组成的一维拼图游戏。他很快意识到每块拼图都属于以下类型之一：

![](https://cdn.luogu.com.cn/upload/image_hosting/vkiyrjd5.png)

另外，已知在这 $n$ 片拼图中，恰好有一个 $5$ 号拼图或 $6$ 号拼图（左边框）和一个 $7$ 号拼图或 $8$ 号拼图（右边框）。

小斌希望将所有块排列成一行，以使第一个（最左边的）拼图类型为 $5$ 号拼图或 $6$ 号拼图，而最后一个（最右边的）拼图类型为 $7$ 号拼图或 $8$ 号拼图。如果有两块拼图，则可以彼此相邻放置，并且仅当它们的相邻边框的形状不同时，即一个边框具有凹凸，而另一个边框具有一个凸出才可以相邻放置。

对于小斌来说，这个问题太简单了，因此他决定在每个部分上写一个唯一的正整数。现在，他想要寻找出字典序最小的方案。

注意：拼图不能旋转！


## 说明/提示

#### 样例 #1 解释
只有 $2$ 种解法，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/lnprd06v.png)

可以看出，第二种解法的字典序较小，所以输出 `1 3 7 5 4`。



#### 数据规模及约定

对于 $100\%$ 的数据，$2 \le n \le 10^5, 1 \le x_i \le 8, 1 \le a_i \le 10^9$。

没有给出字典序最小解而只构造一组解可以得到 $40\%$ 的分数。

#### 说明

**本题分值按 COCI 原题设置，满分 $70$。**

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #2](https://hsin.hr/coci/archive/2019_2020/contest2_tasks.pdf) *T2 Slagalica*。**

## 样例 #1

### 输入

```
5
1 5
2 7
2 3
8 4
6 1
```

### 输出

```
1 3 7 5 4```

## 样例 #2

### 输入

```
3
5 1
7 2
4 3
```

### 输出

```
1 3 2```

## 样例 #3

### 输入

```
5
2 5
2 7
2 3
8 4
6 1
```

### 输出

```
-1```

# 题解

## 作者：yxy666 (赞：6)

看懂题目后，我们可以发现我们需要判断当前这个拼图的种类是根据上一块拼图的种类而决定的。

如果上一块拼图的右边是凸进去的，那么我们就将有两个选择：3 号拼图和  4 号拼图。如果其中一种拼图用完了，那就用另外一种拼图呗。如果两种拼图都有，那么就看一下哪个编号小咯。但是选 4 号拼图的时候一个条件：得有 1 号拼图为它擦屁股；为什么呢？对于一开始凸的形状，如果最后不能还原成凸的形状，那么最后一块就无法装了。

如果上一块拼图的右边是凹进去的，那么我们就将有两个选择：1 号拼图和 2 号拼图。如果其中一种拼图用完了，那就用另外一种拼图呗。如果两种拼图都有，那么就看一下哪个编号小咯。但是选 1 号拼图的时候一个条件：得有 4 号拼图为它擦屁股。为什么呢？对于一开始凹的形状，如果最后不能还原成凹的形状，那么最后一块就无法装了。

还有一个问题：我们应该如何取每种拼图的最小编号呢？集合或者小根堆啊！

code :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,L,R,flg,cnt=1,hep[5][maxn],size[5],ans[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void put(int id,int x){
	hep[id][++size[id]]=x;int son=size[id];
	while(son>1&&hep[id][son]<hep[id][son/2])swap(hep[id][son],hep[id][son/2]),son/=2;
}
int get(int id){
	int x=hep[id][1];int fa=1,son;hep[id][1]=hep[id][size[id]--];
	while(fa*2<=size[id]){
		if(fa*2+1>size[id]||hep[id][fa*2]<hep[id][fa*2+1])son=fa*2;else son=fa*2+1;
		if(hep[id][son]<hep[id][fa])swap(hep[id][son],hep[id][fa]),fa=son;else break;
	}
	return x;
	
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),w=read();
		if(x==5)ans[1]=w,L=0;
		else if(x==6)ans[1]=w,L=1;
		else if(x==7)flg=w,R=1;
		else if(x==8)flg=w,R=0;
		else put(x,w);
	}
	while(1){
		if(L){
			if(!size[1]&&!size[2])break;
			else if(size[1]&&!size[2])ans[++cnt]=get(1),L=1-L;
            else if(!size[1]&&size[2])ans[++cnt]=get(2);
			else{
				if(!size[4]||(size[4]&&hep[2][1]<hep[1][1]))ans[++cnt]=get(2);
				else ans[++cnt]=get(1),L=1-L;
			}
		}
		else{
			if(!size[3]&&!size[4])break;
			else if(!size[4]&&size[3])ans[++cnt]=get(3);
			else if(!size[3]&&size[4])ans[++cnt]=get(4),L=1-L;
			else{
				if(!size[1]||(size[1]&&hep[3][1]<hep[4][1]))ans[++cnt]=get(3);
				else ans[++cnt]=get(4),L=1-L;
			}
		}
	}
	if(L==R&&!size[1]&&!size[2]&&!size[3]&&!size[4]){
		ans[++cnt]=flg;
		for(int i=1;i<=cnt;i++)printf(i==cnt?"%d\n":"%d ",ans[i]);
	}
	else printf("-1\n");
	return 0; 
}
```


---

## 作者：tyx9192596 (赞：3)

观察后发现，拼图 1 和拼图 4 必然交替出现，在中间分情况插入拼图 2 和拼图 3 即可。  
输出字典序最小的需要最开始排序，中间拼图 2 和拼图 3 再与拼图 1 和拼图 4 比较插入。**记得最后要插入剩下的。**

代码：（请勿复制，维护社区风气）
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> x[9];
int l[9],n,a,b,i,j,k;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		x[a].push_back(b);
		l[a]++;
	}
	if(l[5]+l[6]>1||l[7]+l[8]>1){
		printf("-1");
		return 0;
	}
	for(int p=1;p<=8;p++)sort(x[p].begin(),x[p].end());
	if(l[5]==l[8]){
		if(l[1]!=l[4]){
			printf("-1");
			return 0;
		}
		if(l[5]==1){
			if(!l[1]){
				if(l[2]>0){
					printf("-1");
					return 0;
				}
				printf("%d ",x[5][0]);
				for(;i<l[3];i++){
					printf("%d ",x[3][i]);
				}
				printf("%d",x[8][0]);
			}else{
				printf("%d ",x[5][0]);
				for(;i<l[1];i++){
					for(;j<l[3];j++){
						if(x[3][j]>x[4][i])break;
						printf("%d ",x[3][j]);
					}
					printf("%d ",x[4][i]);
					for(;k<l[2];k++){
						if(x[2][k]>x[1][i])break;
						printf("%d ",x[2][k]);
					}
					if(i+1==l[1]){
					for(;k<l[2];k++){
							printf("%d ",x[2][k]);
						}
					}
					printf("%d ",x[1][i]);
					if(i+1==l[1]){
						for(;j<l[3];j++){
							printf("%d ",x[3][j]);
						}
					}
				}
				printf("%d",x[8][0]);
			}
		}else{
			if(l[1]==0){
				if(l[3]>0){
					printf("-1");
					return 0;
				}
				printf("%d ",x[6][0]);
				for(;i<l[2];i++){
					printf("%d ",x[2][i]);
				}
				printf("%d",x[7][0]);
			}else{
				printf("%d ",x[6][0]);
				for(;i<l[1];i++){
					for(;j<l[2];j++){
						if(x[2][j]>x[1][i])break;
						printf("%d ",x[2][j]);
					}
					printf("%d ",x[1][i]);
					for(;k<l[3];k++){
						if(x[3][k]>x[4][i])break;
						printf("%d ",x[3][k]);
					}
					if(i+1==l[1]){
						for(;k<l[3];k++){
							printf("%d ",x[3][k]);
						}
					}
					printf("%d ",x[4][i]);
					if(i+1==l[1]){
						for(;j<l[2];j++){
							printf("%d ",x[2][j]);
						}
					}
				}
				printf("%d",x[7][0]);
			}
		}
	}else if(l[5]==l[7]){
		if(l[5]==1){
			if(l[4]-l[1]!=1){
				printf("-1");
				return 0;
			}
			printf("%d ",x[5][0]);
			for(;j<l[3];j++){
				if(x[3][j]>x[4][0])break;
				printf("%d ",x[3][j]);
			}
			if(!l[1]){
				for(;j<l[3];j++){
					printf("%d ",x[3][j]);
				}
			}
			printf("%d ",x[4][0]);
			for(;i<l[1];i++){
				for(;k<l[2];k++){
					if(x[2][k]>x[1][i])break;
					printf("%d ",x[2][k]);
				}
				printf("%d ",x[1][i]);
				for(;j<l[3];j++){
					if(x[3][j]>x[4][i+1])break;
					printf("%d ",x[3][j]);
				}
				if(i+1==l[1]){
					for(;j<l[3];j++){
						printf("%d ",x[3][j]);
					}
				}
				printf("%d ",x[4][i+1]);
			}
			for(;k<l[2];k++){
				printf("%d ",x[2][k]);
			}
			printf("%d",x[7][0]);
		}else{
			if(l[1]-l[4]!=1){
				printf("-1");
				return 0;
			}
			printf("%d ",x[6][0]);
			for(;j<l[2];j++){
				if(x[2][j]>x[1][0])break;
				printf("%d ",x[2][j]);
			}
			if(!l[4]){
				for(;j<l[2];j++){
					printf("%d ",x[2][j]);
				}
			}
			printf("%d ",x[1][0]);
			for(;i<l[4];i++){
				for(;k<l[3];k++){
					if(x[3][k]>x[4][i])break;
					printf("%d ",x[3][k]);
				}
				printf("%d ",x[4][i]);
				for(;j<l[2];j++){
					if(x[2][j]>x[1][i+1])break;
					printf("%d ",x[2][j]);
				}
				if(i+1==l[4]){
					for(;j<l[2];j++){
						printf("%d ",x[2][j]);
					}
				}
				printf("%d ",x[1][i+1]);
			}
			for(;k<l[3];k++){
				printf("%d ",x[3][k]);
			}
			printf("%d",x[8][0]);
		}
	}
}
```

---

## 作者：Fool_Fish (赞：3)

和大众的做法都不太一样，思路比较简单，实现。。。也比较简单

这题部分分真的能提示很多（为什么洛谷上没有部分分），考场上本来在想怎么拿部分分，然后看了一下部分分，想了一下他们的性质，然后。。。就想出正解了。。。~~但是不会实现嘤嘤嘤~~

---

首先我们看看编号为 $2$ 和 $3$ 的块的性质：他们按规则接在某一个块后面，是不会改变这个块的突出情况的

比如：$5$ 的右边原本是凸出的，我们把 $3$ 接在 $5$ 后面以后，整个块的右边还是凸出的

换句话说，当我们在全部给出的块中去除所有 $2$ 和 $3$ 的块，求出字典序最小的，然后再把 $2$ 和 $3$ 的块插进去就行了

而当 $2$ 和 $3$ 的去掉后，能在中间部分的就只有 $1$ 和 $4$ 了，发现这两个只能交替出现，并且谁先谁后是固定的（可以根据起始块和末尾块的形状确定），然后又由于有一个字典序最小的要求，拍一个序后再放就行了

插 $2$ 和 $3$ 也就简单了，具体的话看代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int MAXN=1e5+5;
struct date{
	int id,v;
	bool vis;
	date(){}
	date(int ID,int V){
		vis=0,id=ID,v=V;
	}
};
int n;
int road[MAXN];
priority_queue<int,vector<int>,greater<int> > q[10];
bool check(){
	bool flag=0;
	for(int i=1;i<=4;i++){
		if(q[i].size()){
			flag=1;
		}
	}
	return flag;
}
int main(){
	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++){
		int a,v; 
		scanf("%d %d",&a,&v);
		q[a].push(v);
		if(a==1) ans+=2;
		if(a==4) ans-=2;
		if(a==5) ans++;
		if(a==6) ans--;
		if(a==7) ans++;
		if(a==8) ans--;
	}
	if(ans!=0){
		printf("-1");
		return 0;
	} 
	if(q[5].size()){
		int step=0;
		road[++step]=q[5].top();
		q[5].pop(); 
		int l,r;
		if(q[7].size()){
			l=1;
			r=0;
		}
		else{
			l=0;
			r=1;
		}
		while(check()){
			while(q[3].size()&&(q[4].size()==l||(q[3].top()<q[4].top()))){
				road[++step]=q[3].top();
				q[3].pop();
			}
			if(q[4].size()){
				road[++step]=q[4].top();
				q[4].pop();
			}
			while(q[2].size()&&(q[1].size()==r||(q[2].top()<q[1].top()))){
				road[++step]=q[2].top();q[2].pop();
			}
			if(q[1].size()){
				road[++step]=q[1].top();
				q[1].pop();
			}
		}
		if(q[7].size()){
			road[++step]=q[7].top();
		}
		else{
			road[++step]=q[8].top();
		}
	}
	else{
		int step=0;
		road[++step]=q[6].top();
		q[6].pop();
		int l,r;
		if(q[7].size()){
			l=0;
			r=1;
		}
		else{
			l=1;
			r=0;
		}
		while(check()){
			while(q[2].size()&&(q[1].size()==l||(q[2].top()<q[1].top()))){
				road[++step]=q[2].top();
				q[2].pop();
			}
			if(q[1].size()){
				road[++step]=q[1].top();
				q[1].pop();
			}
			while(q[3].size()&&(q[4].size()==r||(q[3].top()<q[4].top()))){
				road[++step]=q[3].top();
				q[3].pop();
			}
			if(q[4].size()){
				road[++step]=q[4].top();
				q[4].pop();
			}
		}
		if(q[7].size()){
			road[++step]=q[7].top();
		}
		else{
			road[++step]=q[8].top();
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",road[i]);
	}
return 0;
}
```

---

## 作者：Dangerou (赞：1)

## 分析：
对于同一位置放同样拼图的情况，放 $a_i$ 值较小的解更优，所以需要对同一种类的拼图按照 $a_i$ 的值从小到大进行排序。

当前放置什么样的拼图与前一个拼图的右端的凸凹情况有关。也就是说：当上一块拼图为第 $1$、$3$、$5$ 种时，当前需要在第 $3$、$4$ 种拼图中选择；当上一块拼图为第 $2$、$4$、$6$ 种时，当前需要在第 $1$、$2$ 种拼图中选择。至于选择哪一种，当然是根据 $a_i$ 的大小决定。

考虑能放就放的策略。

当前能放第 $1$ 种拼图时：

1. 当第 $4$ 种拼图的数量大于 $0$ 时，继续放置即可。
2. 当第 $4$ 种拼图的数量等于 $0$ 且以第 $8$ 种拼图结尾时，需满足第 $2$ 种拼图的数量也为 $0$，才能放置。

当前能放第 $2$、$3$ 种拼图时：由于不会改变已有的凸凹情况，所以根据 $a_i$ 的值能放就放。

当前能放第 $4$ 种拼图时：

1. 当第 $1$ 种拼图的数量大于 $0$ 时，继续放置即可。
2. 当第 $1$ 种拼图的数量等于 $0$ 且以第 $7$ 种拼图结尾时，需满足第 $3$ 种拼图的数量也为 $0$，才能放置。

当某一位置不满足以上任意一种情况时，则无解，输出 $-1$。

## 解释
为什么考虑能放就放？

因为即使当前就能判断出无解，但一直放下去一定会出现某一位置没有拼图可放的情况。既然有简单的判断方式，又何必选复杂的呢。

为什么放置第 $1$ 种拼图时，当第 $4$ 种拼图的数量等于 $0$ 且以第 $8$ 种拼图结尾的情况一定要求第 $2$ 种拼图数量也为 $0$ 呢？

由于第 $4$ 种拼图的数量为零，所以在放置第 $1$ 种拼图之后，凹凸情况将不会再发生改变，即右端将一直维持凸的情况，若此时还有第 $2$ 种拼图，则无法放置。

放置第 $4$ 种拼图时，当第 $1$ 种拼图的数量等于 $0$ 且以第 $7$ 种拼图结尾的情况一定要求第 $3$ 种拼图数量也为 $0$ 的原因与上述情况类似。

### Code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
int n;
int x,a;
int las,en;//las记录上一个拼图的种类，en记录末尾拼图种类
int id,minn;
vector<int> g[10];
int ans[100005];//存答案
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&a);
		if(x==5||x==6) ans[1]=a;//记录第一块拼图的a
		else if(x==7||x==8) ans[n]=a;//记录最后一块拼图的a
		g[x].push_back(a);
		if(x==5) las=5;
		else if(x==6) las=6;
		else if(x==7) en=7;
		else if(x==8) en=8;
	}
	for(int i=1;i<=8;i++) sort(g[i].begin(),g[i].end());//对每一种拼图按照a的值从小到大排序
	for(int i=2;i<n;i++)//循环内容详情见分析
	{
		id=0;minn=INF;
		if(las==1||las==3||las==5)
		{
			if(g[3].size())
			{
				if(minn>g[3][0])
				{
					id=3;
					minn=g[3][0];
				}
			}
			if(g[4].size())
			{
				if(g[1].size()||(en==7&&g[1].size()==0&&g[3].size()==0))
				{	
					if(minn>g[4][0])
					{
						id=4;
						minn=g[4][0];
					}
				}
			}
		}
		if(las==2||las==4||las==6)
		{
			if(g[1].size())
			{
				if(g[4].size()||(en==8&&g[4].size()==0&&g[2].size()==0))
				{
					if(minn>g[1][0])
					{
						id=1;
						minn=g[1][0];
					}	
				}
			}
			if(g[2].size())
			{
				if(minn>g[2][0])
				{
					id=2;
					minn=g[2][0];
				}
			}
		}
		if(id==0)//如果没有拼图可放，则无解
		{
			printf("-1\n");
			return 0;
		}
		las=id;
		ans[i]=minn;//记录答案
		g[id].erase(g[id].begin());//删除，vector删除开头元素后，第二个元素将成为新的开头，所以每次判断大小都用g[id][0]
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

大分讨。

首先，我们知道 $2$ 和 $3$ 不会影响凸起关系，所以这里默认屏蔽掉 $2$ 和 $3$。

我们可以知道同种拼图可以互换，所以每种拼图排个序。

然后我们知道 $1$ 和 $4$ 应该是轮着放的。

所以，我们按照字典序最优的方法，把 $2$ 和 $3$ 插入进去。也就是当前 $3$ 的编号比当前 $4$ 的编号小的就插进去；当前 $1$ 的编号比当前 $2$ 的编号小的就插进去。

特别的，如果没有 $1$ 和 $4$ 还有一些情况：

如果是 $5$ 和 $8$，那就不能有 $2$。

如果是 $6$ 和 $7$，那就不能有 $3$。

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		f|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return f?-res:res;
}
const int maxn=1e5+5;
int n,q[10][maxn],siz[10],tot[10];
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		int x=read(),a=read();
		q[x][siz[x]++]=a;
	}
	for(int i=1;i<=8;++i)
		stable_sort(q[i],q[i]+siz[i]);
	if(!siz[1]&&!siz[4]){
		if(siz[5]){
			if(siz[7]){
				puts("-1");
				return 0; 
			} else if(siz[2]){
				puts("-1");
				return 0;
			}
		} else{
			if(siz[8]){
				puts("-1");
				return 0;
			} else if(siz[3]){
				puts("-1");
				return 0;
			}
		}
	} 
	if(siz[5]){
		if(siz[7]){
			if(siz[4]-siz[1]!=1){
				puts("-1");
				return 0;
			}
		} else{
			if(siz[1]-siz[4]){
				puts("-1");
				return 0;
			}
		}
		printf("%d ",q[5][0]);
		if(siz[4]^siz[1]){
			for(int i=0;i<siz[1];++i){
				while(tot[3]<siz[3]&&q[3][tot[3]]<q[4][i]){
					printf("%d ",q[3][tot[3]]);
					++tot[3];
				}
				printf("%d ",q[4][i]);
				while(tot[2]<siz[2]&&q[2][tot[2]]<q[1][i]){
					printf("%d ",q[2][tot[2]]);
					++tot[2];
				}
				printf("%d ",q[1][i]);
			}
			while(tot[3]<siz[3]){
				printf("%d ",q[3][tot[3]]);
				++tot[3];
			}
			printf("%d ",q[4][siz[4]-1]);
			while(tot[2]<siz[2]){
				printf("%d ",q[2][tot[2]]);
				++tot[2];
			}
		} else{
			for(int i=0;i<siz[1];++i){
				while(tot[3]<siz[3]&&q[3][tot[3]]<q[4][i]){
					printf("%d ",q[3][tot[3]]);
					++tot[3];
				}
				printf("%d ",q[4][i]);
				while(tot[2]<siz[2]&&q[2][tot[2]]<q[1][i]){
					printf("%d ",q[2][tot[2]]);
					++tot[2];
				}
				if(i==siz[1]-1){
					while(tot[2]<siz[2]){
						printf("%d ",q[2][tot[2]]);
						++tot[2];
					}
				}
				printf("%d ",q[1][i]);
			}
			while(tot[3]<siz[3]){
				printf("%d ",q[3][tot[3]]);
				++tot[3];
			}
		}
	} else{
		if(siz[7]){
			if(siz[1]-siz[4]){
				puts("-1");
				return 0;
			}
		} else{
			if(siz[1]-siz[4]!=1){
				puts("-1");
				return 0;
			}
		}
		printf("%d ",q[6][0]);
		if(siz[1]^siz[4]){
			for(int i=0;i<siz[4];++i){
				while(tot[2]<siz[2]&&q[2][tot[2]]<q[1][i]){
					printf("%d ",q[2][tot[2]]);
					++tot[2];
				}
				printf("%d ",q[1][i]);
				while(tot[3]<siz[3]&&q[3][tot[3]]<q[4][i]){
					printf("%d ",q[3][tot[3]]);
					++tot[3];
				}
				printf("%d ",q[4][i]);
			}
			while(tot[2]<siz[2]){
				printf("%d ",q[2][tot[2]]);
				++tot[2];
			}
			printf("%d ",q[1][siz[1]-1]);
			while(tot[3]<siz[3]){
				printf("%d ",q[3][tot[3]]);
				++tot[3];
			}
		} else{
			for(int i=0;i<siz[4];++i){
				while(tot[2]<siz[2]&&q[2][tot[2]]<q[1][i]){
					printf("%d ",q[2][tot[2]]);
					++tot[2];
				}
				printf("%d ",q[1][i]);
				while(tot[3]<siz[3]&&q[3][tot[3]]<q[4][i]){
					printf("%d ",q[3][tot[3]]);
					++tot[3];
				}
				if(i==siz[4]-1){
					while(tot[3]<siz[3]){
						printf("%d ",q[3][tot[3]]);
						++tot[3];
					}
				}
				printf("%d ",q[4][i]);
			}
			while(tot[2]<siz[2]){
				printf("%d ",q[2][tot[2]]);
				++tot[2];
			}
		}
	}
	if(siz[7])
		printf("%d",q[7][0]);
	else
		printf("%d",q[8][0]);
	return 0;
}
```

---

## 作者：tkdqmx (赞：0)

可以发现拼图 1 和 2、3 拼起来还是拼图 1，拼图 4 和 2、3 拼起来也还是拼图 4，这两种拼图还都不能和自己拼，所以我们可以看作只有拼图 1 和拼图 4 来做。

对于边界拼图分别是 5、7 的情况，只有形如 414，41414 的情况可以拼进去，所以如果拼图 4 的数量不等于拼图 1 的数量 +1 就无解。

其它情况可以类推：边界是 5、8 就应该形如 41，4141；边界是 6、7 就应该形如 14，1414；边界是 6、8 就应该形如 141，14141。

考虑如何让字典序最小，很明显对于拼图 1、2、3、4，我们应该分别把四种拼图各自从小到大排序。

接下来以边界为 5、7 来举例，根据上面所说的，第一块应该放 4，而 4 前面可以放任意块 3，最后得到的拼图还是 4。

所以可以先把拼图 3 中所有小于 4 中最小值的先拼上，然后再拼上一块 4。

同理，因为接下来要拼 1，而 1 前面可以放任意块 2，所以可以先把拼图 2 中所有小于 1 中最小值的先拼上，然后再拼上一块 1。

接下来就循环到拼完就可以了，4 前面拼 3，1 前面拼 2 的这一步，可以用等同于归并排序的方式来完成。

值得注意的是拼到最后一块 4 的时候，前后要分别把 3、2 全部都给拼上去，这就是唯一有点坑的点、地方了。

边界是其它拼图的情况就以此类推了，具体可以看下面的代码。

代码写的略显臃肿，有的地方其实可以写函数的，但我比较懒，所以贴的代码看着玩就行了：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[5];
int n,l,r,ls,rs,now2,now3,sz[5];
void work(int x,int y,int &i,int j){
    while(i<sz[x]&&v[x][i]<v[y][j])  printf("%d ",v[x][i++]);
    printf("%d ",v[y][j]);
}
int main(){
	scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        if(x==5||x==6)  l=x,ls=y;
        if(x==7||x==8)  r=x,rs=y;
        if(x<=4)  v[x].push_back(y),sz[x]++;
    }
    for(int i=1;i<=4;i++)  sort(v[i].begin(),v[i].end());
    if(l==5&&r==7){
        if(sz[1]+1!=sz[4])  return printf("-1"),0;
        printf("%d ",ls);
        for(int i=0;i<sz[1];i++)  work(3,4,now3,i),work(2,1,now2,i);
        while(now3<sz[3])  printf("%d ",v[3][now3++]);
        printf("%d ",v[4][sz[1]]);
        while(now2<sz[2])  printf("%d ",v[2][now2++]);
    }
    if(l==5&&r==8){
        if(sz[1]!=sz[4])  return printf("-1"),0;
        printf("%d ",ls);
        for(int i=0;i<sz[1]-1;i++)  work(3,4,now3,i),work(2,1,now2,i);
        if(sz[1]){
            work(3,4,now3,sz[4]-1);
            while(now2<sz[2])  printf("%d ",v[2][now2++]);
            printf("%d ",v[1][sz[1]-1]);
            while(now3<sz[3])  printf("%d ",v[3][now3++]);
        }
        else{
            while(now3<sz[3])  printf("%d ",v[3][now3++]);
            while(now2<sz[2])  printf("%d ",v[2][now2++]);
        }
    }
    if(l==6&&r==7){
        if(sz[1]!=sz[4])  return printf("-1"),0;
        printf("%d ",ls);
        for(int i=0;i<sz[1]-1;i++)  work(2,1,now2,i),work(3,4,now3,i);
        if(sz[1]){
            work(2,1,now2,sz[1]-1);
            while(now3<sz[3])  printf("%d ",v[3][now3++]);
            printf("%d ",v[4][sz[4]-1]);
            while(now2<sz[2])  printf("%d ",v[2][now2++]);
        }
        else{
            while(now2<sz[2])  printf("%d ",v[2][now2++]);
            while(now3<sz[3])  printf("%d ",v[3][now3++]);
        }
    }
    if(l==6&&r==8){
        if(sz[1]!=sz[4]+1)  return printf("-1"),0;
        printf("%d ",ls);
        for(int i=0;i<sz[4];i++)  work(2,1,now2,i),work(3,4,now3,i);
        while(now2<sz[2])  printf("%d ",v[2][now2++]);
        printf("%d ",v[1][sz[4]]);
        while(now3<sz[3])  printf("%d ",v[3][now3++]);
    }
    printf("%d\n",rs);
}
~~~

---

