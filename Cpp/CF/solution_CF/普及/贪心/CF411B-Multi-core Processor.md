# Multi-core Processor

## 题目描述

The research center Q has developed a new multi-core processor. The processor consists of $ n $ cores and has $ k $ cells of cache memory. Consider the work of this processor.

At each cycle each core of the processor gets one instruction: either do nothing, or the number of the memory cell (the core will write an information to the cell). After receiving the command, the core executes it immediately. Sometimes it happens that at one cycle, multiple cores try to write the information into a single cell. Unfortunately, the developers did not foresee the possibility of resolving conflicts between cores, so in this case there is a deadlock: all these cores and the corresponding memory cell are locked forever. Each of the locked cores ignores all further commands, and no core in the future will be able to record an information into the locked cell. If any of the cores tries to write an information into some locked cell, it is immediately locked.

The development team wants to explore the deadlock situation. Therefore, they need a program that will simulate the processor for a given set of instructions for each core within $ m $ cycles . You're lucky, this interesting work is entrusted to you. According to the instructions, during the $ m $ cycles define for each core the number of the cycle, during which it will become locked. It is believed that initially all cores and all memory cells are not locked.

## 样例 #1

### 输入

```
4 3 5
1 0 0
1 0 2
2 3 1
3 2 0
```

### 输出

```
1
1
3
0
```

## 样例 #2

### 输入

```
3 2 2
1 2
1 2
2 2
```

### 输出

```
1
1
0
```

## 样例 #3

### 输入

```
1 1 1
0
```

### 输出

```
0
```

# 题解

## 作者：Cure_Wing (赞：1)

### 题目描述
[CF411B ](https://www.luogu.com.cn/problem/CF411B)[Multi-core Processor](https://codeforces.com/problemset/problem/411/B)

有 $n$ 个处理器和 $k$ 个单元，每个处理器会发送 $m$ 个信号，第 $i$ 个处理器会在第 $j$ 时刻发送信号 $x_{i,j}$。当 $x_{i,j}=0$ 时，表示不向任何一个单元发送信号；当 $x_{i,j}\not=0$ 时，表示向单元 $x_{i,j}$ 发送信号。如果有多个处理器在同一时刻发送给同一单元信号，那么这些处理器和这个单元将会被冻结。被冻结的处理器不能再发送信号，被冻结的单元不能再接受信号。如果未被冻结的处理器向冻结的单元发送信号，那么该处理器也将会被冻结。现在你知道了处理器将会发送的信号，请计算出每个处理器被冻结的时刻。如果不会被冻结则返回 $0$。

### 解析
看到 $n,m,k\le100$，直接大模拟，注意细节。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
int n,m,k,a[111][111],c1[111],vis[111],c2[111];//vis统计单元接受到的处理器个数，c1统计处理器被冻结的时间，c2统计单元被冻结的时间
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>a[i][j];
	for(int i=1;i<=m;++i){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;++j){
			if(c1[j]||!a[j][i]) continue;//被冻结的处理器不能再发送信号。
			if(c2[a[j][i]]) c1[j]=i;//如果未被冻结的处理器向冻结的单元发送信号，那么该处理器也将会被冻结。
			else ++vis[a[j][i]];//统计单元接受到的处理器个数。
		}
		for(int j=1;j<=n;++j){
			if(c1[j]) continue;//被冻结的处理器不能再发送信号
			if(vis[a[j][i]]>1) c1[j]=c2[a[j][i]]=i;//如果有多个处理器在同一时刻发送给同一单元信号，那么这些处理器和这个单元将会被冻结。
		}
	}
	for(int i=1;i<=n;++i) cout<<c1[i]<<'\n';
    return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF411B)

## 题意
有编号从 $1$ 到 $n$ 的 $n$ 个处理器和编号从 $1$ 到 $k$ 的 $k$ 个存储单元，一共有 $1$ 到 $m$ 的 $m$ 个时间段，第 $i$ 个处理器会在第 $j$ 个时间段给存储单元 $x_{i,j}$ 发送信号，如果 $x_{i,j}=0$ 表示处理器 $i$ 在第 $j$ 号时间段没有发送信号。如果有多个处理器在同一时间段给同一存储单元发送信号，则这些处理器和这个存储单元都将会被锁定。被锁定的处理器不能再发送信号，被锁定的单元不能再接收信号。如果未被锁定的处理器向锁定的存储单元发送信号，则该处理器也会被锁定。给定每个处理器在各个时间段发送信号的目标存储单元编号，请你计算出每个处理器被锁定的时间段。如果不会被锁定则返回 $0$。

## 思路
这题数据非常低，可以直接大模拟枚举，分别看每个处理器单元收到的指令数并判断处理器和单元的状态是否被锁定，需要注意一些细节。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
int a[maxn][maxn],cpu[maxn],cnt[maxn],i,j,n,k,m; 
bool x[maxn];
int main()
{
    ios:sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)cin>>a[i][j];
	for(i=1;i<=m;i++)
	{
		memset(cnt,0,sizeof(cnt));
		for(j=1;j<=n;j++)
		{
			if(cpu[j]||a[j][i]==0)continue;
			if(x[a[j][i]])
			{
				cpu[j]=i;
				continue;
			}
			cnt[a[j][i]]++;
		}
		for(j=1;j<=n;j++)
		{
			if(cpu[j])continue;
			if(cnt[a[j][i]]>=2)
			{
				cpu[j]=i;
				x[a[j][i]]=1;
			}
		}		
	}
	for(i=1;i<=n;i++)cout<<cpu[i]<<endl;
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF411B)  
[CodeForces 传送门](http://codeforces.com/problemset/problem/411/B)

模拟。主要考虑一下两点：

- 如果有多个处理器在同一时刻发送给同一单元信号，那么这些处理器和这个单元将会被冻结。
- 如果未被冻结的处理器向冻结的单元发送信号，那么该处理器也将会被冻结。

首先考虑第一点。我们统计每一时刻各个单元接受的信号总数，如果总数 $\ge2$ 则冻结向该单元发送信号的所有处理器，并记录当前的时刻作为答案即可。

其次考虑第二点。对于那些未被冻结的处理器，如果它向冻结的单元发送信号则冻结其自身，并记录当前的时刻作为答案即可。

最后输出。  
注意第一点需多测清空。

```cpp
int a[110][110];
int cnt[110];
bool f[110];
int ans[110];
signed main()
{
	int n,m,k;
	rd(n,m,k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			rd(a[i][j]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		memset(cnt,0,sizeof(cnt));
		for(int j=1;j<=n;j++)
		{
			if(!ans[j])
			{
				cnt[a[j][i]]++;
			}
		}
		for(int j=1;j<=k;j++)
		{
			if(cnt[j]>=2)
			{
				f[j]=1;
				for(int l=1;l<=n;l++)
				{
					if(!ans[l]&&a[l][i]==j)
					{
						ans[l]=i;
					}
				}
			}
		}
		for(int j=1;j<=n;j++)
		{
			if(!ans[j]&&f[a[j][i]])
			{
				ans[j]=i;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		wtl(ans[i]);
	}
	return 0;
}
```

---

## 作者：PvbeLLN (赞：0)

### 思路

纯粹大模拟，注意到 $1 \le n,m,k \le 100$，数据范围很小，故可以对当前时刻进行枚举，分别统计每个处理器单元收到的指令数并判断处理器和单元的状态（是否被锁定），不需担心超时的问题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m;
int a[105][105],cpu[105],cnt[105];   //cpu数组统计每个处理器的锁定时间，初始值为0
                                     //cnt数组统计每个时刻各个单元所接收到的来自不同处理器的指令数 
bool cell[105]; //记录单元是否被锁定 

int main()
{
	cin>>n>>m>>k;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			cin>>a[i][j]; //按照题意读入 
	for (int i=1;i<=m;i++) //枚举时刻 
	{
		memset(cnt,0,sizeof(cnt)); //时刻更新，cnt数组清零 
		for (int j=1;j<=n;j++)
		{
			if (cpu[j]||a[j][i]==0) continue; //处理器被锁定或没有发出指令 
			if (cell[a[j][i]]) {cpu[j]=i; continue;} //处理器向已锁定的单元发送指令 
			cnt[a[j][i]]++; //统计每个单元接收到的指令数 
		}
		for (int j=1;j<=n;j++)
		{
			if (cpu[j]) continue; //处理器已锁定，跳过 
			if (cnt[a[j][i]]>=2)  //有多个处理器同时向某个单元发送指令 
			{
				cpu[j]=i;
				cell[a[j][i]]=1;  //单元和处理器均被锁定 
			}
		}		
	}
	for (int i=1;i<=n;i++) cout<<cpu[i]<<"\n";
	return 0;
}

```


---

## 作者：OIer6666 (赞：0)

暴力都能过的水题。

从时刻遍历。

- 将被接受过信号的单元标记一次。如果处理器指向了这一刻接收过信号的单元，将这个单元冻结，将所有在这一刻指向这个单元的处理器冻结，并记录下被冻结的那一刻。
- 处理器是指向了已经被冻结的单元，将处理器冻结，记录下冻结的时间。

在这一刻结束时将只被指过 $1$ 次的单元的标记擦除。

## AC Code
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define ll long long
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
int n,m,k;
int coldk[1005],coldc[1005];
int clodtime[1005];
int x[1005][1005];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>x[i][j];
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(coldc[i]==2||x[i][j]==0)
				continue;
			if(coldk[x[i][j]]==1){
				coldc[i]=1;
				continue;
			}
			if(coldk[x[i][j]]==2){
				coldk[x[i][j]]=1;
				for(int v=1;v<=n;v++){
					if(x[i][j]==x[v][j]&&coldc[v]!=2){
						coldc[v]=1;
					}
				}
			}else{
				coldk[x[i][j]]=2;
			}
		}
		for(int i=0;i<=100;i++)
			if(coldk[i]==2)
				coldk[i]=0;
		for(int i=1;i<=n;i++){
			if(coldc[i]==1){
				clodtime[i]=j;
				coldc[i]=2;
			}
		}
	}
	for(int i=1;i<=n;i++)
		cout<<clodtime[i]<<endl;
	return 0;
}
```

---

