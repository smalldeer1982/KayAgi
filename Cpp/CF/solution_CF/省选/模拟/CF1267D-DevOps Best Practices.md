# DevOps Best Practices

## 题目描述

Daisy 是 RainyDay, LLC 的一名高级软件工程师。她刚刚在产品中实现了三个新功能：第一个功能使产品能够正常运行，第二个功能提升了产品的速度，第三个功能确保产品的正确性。公司希望对新功能进行一定的测试，因此 Daisy 指派实习生 Demid 为这些功能编写测试案例。

有趣的是，这三个功能在 Demid 的开发服务器（编号为 1）上通过了所有测试，但可能会在其他服务器上失败。

完成开发后，Daisy 让你负责将这三个新功能部署到公司所有 $n$ 台服务器上。每个功能 $f$ 和每台服务器 $s$，Daisy 都告诉你是否需要将功能 $f$ 部署到服务器 $s$ 上。如果 Daisy 希望部署，则无论功能 $f$ 在服务器 $s$ 上是否通过测试都必须进行部署。如果她不需要部署，你就不能在该服务器上执行部署。

你的公司有两种重要工具来实现新功能的部署：持续部署（CD）和持续测试（CT）。CD 可以在几对服务器之间建立连接，形成一个有向图。CT 可以在某些服务器上进行设置。

如果服务器 $s_1$ 对服务器 $s_2$ 进行了 CD 配置，那么每当 $s_1$ 接收到一个新功能 $f$ 时，系统将启动以下部署过程：

- 如果功能 $f$ 已部署在服务器 $s_2$ 上，则无需操作。
- 否则，如果服务器 $s_1$ 上未设置 CT，则直接将功能 $f$ 从服务器 $s_1$ 部署到服务器 $s_2$，无需进行测试。
- 否则，服务器 $s_1$ 将运行功能 $f$ 的测试。如果测试失败，不做任何操作。如果测试通过，则将功能 $f$ 部署到服务器 $s_2$。

你需要配置 CD/CT 系统，然后 Demid 在其开发服务器上部署所有三个功能。你的配置必须确保每个功能精准地部署到 Daisy 规定的服务器上。

公司计算资源有限，因此你最多允许在 264 对服务器之间建立 CD。

## 样例 #1

### 输入

```
3
1 1 1
1 0 1
1 1 1
1 1 1
0 0 0
1 0 1
```

### 输出

```
Possible
1 1 1
2
3 2
1 3
```

## 样例 #2

### 输入

```
2
1 1 1
0 0 1
1 1 1
1 1 0
```

### 输出

```
Impossible
```

# 题解

## 作者：lzqy_ (赞：1)

给出一种构造上界为 $(n+2)$ 的构造方法，应该是最优的构造方法了。


构造题还是先手玩找性质。

设点 $x$ 需要的 feature 状态为 $s_x$，装上 CT 之后能转移出去的 feature 状态为 $t_x$（$t_x$ 是 $s_x$ 的子集），最终状态下能转移出去的 feature 状态为 $f_x$（有 $f_x=s_x$ 或 $t_x$）。

- 每个点的入度 $\le 2$ 不会使答案变劣。

	首先肯定只连有贡献的边。因为只有三个值，所以入度肯定 $\le 3$。当入度为 $3$ 的时候，说明该点需要所有的 feature，此时直接将点 $1$ 连向该点更优。
    
- 对于入度为 $1$ 的点，使用 CT 不会使答案变劣。
	
  对于入度为 $1$ 的点 $v$，连向它的点 $u$ 满足 $f_u=s_v$。若不装CT（$f_v=s_v$），那么点 $v$ 的贡献一定可以被点 $u$ 全部覆盖，所以使用 CT 不会变劣。
  
- 对于入度为 $2$ 的点，不使用 CT 不会使答案变劣。

	首先入度为 $2$ 点 $x$ 所需的 feature 数一定为 $2$，连向它的点分别贡献一个 feature。所以 $s_x$ 的所有**真**子集都已经出现过，又因为 $t_x$ 是 $s_x$ 的子集，所以让 $f_x=s_x$ 不会变劣。
    
   
如果将入度为 $2$ 的点看做从已有点集中连出一条边权为 $2$ 的边，那么这就是一个求生成树的过程，考虑用 Prim 模拟：


从点集 $S=\{1\}$ 出发，每次贪心地选取入度可以为 $1$ 的点（由一个点就可以转移的点）加入点集，若没有，再选择入度可以为 $2$ 的点加入点集。最后判断是否每个点都加进点集。因为上文已经分析过每个点是否使用 CT，所以点集 $S$ 中的 $f_x$ 种类是固定的。

-----

因为两个入度为 $2$ 的点的状态要么相同可以互相转移，要么不同都不能转移，所以不会出现下图的情况。所以 Prim 这里运用在有向图上是正确的。

![](https://cdn.luogu.com.cn/upload/image_hosting/qorhngwv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

-------

由上文可知，入度为 $2$ 的点的 $s_x$ 最多有 $3$ 种，所以入度为 $2$ 的点也最多有 $3$ 个，所以边的上界是 $(n-1)+3=n+2$ 。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define il inline
using namespace std;
const int maxn=310;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
pair<int,int>ans[maxn];
bool vis[maxn];
int Ans[maxn];
int s1[maxn],s2[maxn];
int Id[8],n,m,S,cn;
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=0;j<3;j++)
			if(read()) s1[i]|=(1<<j);
	for(int i=1;i<=n;i++)
		for(int j=0;j<3;j++)
			if(read()) s2[i]|=(1<<j);
	for(int i=1;i<=n;i++) Ans[i]=1,s2[i]&=s1[i];
	vis[1]=1,Id[7]=1,S|=(1<<7);
	bool fl=1; 
	while(fl){
		fl=0,cn++;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(S&(1<<s1[i]))){
				ans[++m]=mp(Id[s1[i]],i);
				vis[i]=1,fl=1,Id[s2[i]]=i;
				S|=(1<<s2[i]);
				break;
			}
		if(fl) continue;
		for(int i=1;i<=n&&!fl;i++){
			if(vis[i]) continue;
			for(int j=1;j<8&&!fl;j<<=1)
				if(S&(1<<j))for(int k=1;k<8;k<<=1)
					if(S&(1<<k)) if((j|k)==s1[i]){
						ans[++m]=mp(Id[j],i);
						ans[++m]=mp(Id[k],i);
						vis[i]=1,fl=1,Id[s1[i]]=i;
						S|=(1<<s1[i]),Ans[i]=0;
						break;
					}
		} 
	}
	if(cn<n) return printf("Impossible\n"),0;
	printf("Possible\n");
	for(int i=1;i<=n;i++)
		printf("%d ",Ans[i]);
	printf("\n%d\n",m);
	for(int i=1;i<=m;i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
} 
```

---

