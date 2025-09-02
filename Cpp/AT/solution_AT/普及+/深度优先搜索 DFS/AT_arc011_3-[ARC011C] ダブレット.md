# [ARC011C] ダブレット

## 题目描述

你正在玩一个单词接龙游戏。

一个单词可以变换为另一个单词，当且仅当这两个单词恰有一个字母不同。

给定起始单词 $first$ 和目标单词 $last$，以及一个含有 $N$ 个单词的 **可重** 词集 $\{s_0,s_1,...,s_{N-1}\}$。请回答，在只使用词集中的词进行变换的情况下，从 $first$ 变换到 $last$ 最少需要多少步 **（所使用的词集中的词的个数）**，并给出一组方案。

特别地：

- 若 $first$ 和 $last$ 相同，则步数为 $0$；
- 若无法完成变换，仅输出一行 `-1` 即可；
- **若 $first$ 只经过一次变换即可得到 $last$，则步数也为 $0$。（这段话原题没写）**

## 说明/提示

- $1\le N\le 1\ 000$；
- 词集中可能含有重复的单词，也可能含有 $first$ 和 $last$；
- 输入的每个单词长度都相同，且该长度 $L$ 满足 $1\le L\le 30$；
- 每个单词仅由英文小写字母 `a-z` 构成。

# 题解

## 作者：SamHH0912 (赞：0)

题目传送门：

[Luogu](https://www.luogu.com.cn/problem/AT_arc011_3) | [AtCoder](https://atcoder.jp/contests/arc011/tasks/arc011_3)

### 思路

考虑建一张无向图。这张无向图中有 $(N+2)$ 个点，编号 $0\sim N+1$。其中点 $0\sim N-1$ 依次代表 $s_0,s_1,...,s_{N-1}$，点 $N$ 代表 $first$，点 $(N+1)$ 代表 $last$。

现在在图中进行连边。无向图中的边都是双向的，表示既可以从 $a$ 到 $b$，也可以从 $b$ 到 $a$，且两种方法经过的路程相同。在本题中，我们在图中的两个点之间连边当且仅当两个字符串**恰有一个位置上的字母不同**，并钦定每条边的边权都为 $1$。

建完图之后，我们发现最少所需的**变换次数**（不是步数）就是图中 $N$ 点到 $(N+1)$ 点的最短路长度。因为每条边的边权都为 $1$，所以直接跑广搜就好了。

然而，**步数**的定义是变换过程中**使用的中间词个数**，而非变换次数。根据我们小学就学过的植树问题可知，在本题中一个长为 $len$ 的路径会经过 $(len+1)$ 个点，其中有 $(len-1)$ 个中间点（掐首去尾）。所以，最终所需的**步数**就为**变换次数 $-1$** 所得的值。可以通过将起点的 $dis$ 值设为 $-1$，直接取终点 $dis$ 值作为答案的方式处理，或将起点的 $dis$ 置为 $0$，最后将终点的 $dis$ 减去一算出。

时间复杂度 $\mathcal{O}(N^2\times L)$，瓶颈在建图。

### 参考代码

仅供参考，请勿抄袭！


```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 1007
#define L 32
char fi[L],la[L],s[N][L];//起始、终止、中间

inline bool check(char a[],char b[]){//检查是否能连边
	bool fl=0;
	for(int i=0;a[i];i++)
		if(a[i]!=b[i]){
			if(fl) return 0;
			fl=1;
		}
	return fl;
}

//链式前向星存图
int cnt,head[N];
struct qwq{int v,nxt;}edge[N*N*2];
inline void AddE(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}

//步数、前一个字符串编号
int dis[N],pre[N];
bool vis[N];

//在最终输出时使用
int stk[N],t;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>fi>>la;//输入首尾
	bool sa=1;//首尾相同
	for(int i=0;fi[i];i++)
		if(fi[i]!=la[i]) {sa=0;break;}
	if(sa||check(fi,la)){//0步到位的特判
		cout<<0<<'\n';
		cout<<fi<<'\n';
		cout<<la<<'\n';
		return 0;
	}
	int n;//字符集大小
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s[i];
		if(check(fi,s[i])) AddE(n,i);//由 first 变换得到
		if(check(la,s[i])) AddE(i,n+1);//变换得到 last
		for(int j=0;j<i;j++) if(check(s[j],s[i])) AddE(i,j),AddE(j,i);//互相转换
	}
	
	queue<int>que;//广搜队列
	while(!que.empty()) que.pop();//防止玄学事件发生
	vis[n]=1,dis[n]=-1,que.push(n);//初始化
	while(!que.empty()){//广搜
		int u=que.front();que.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(vis[v]) continue;
			vis[v]=1,pre[v]=u,dis[v]=dis[u]+1,que.push(v);
		}
	}
	
	if(!vis[n+1]){//无解
		cout<<-1<<'\n';
		return 0;
	}
	cout<<dis[n+1]<<'\n';//步数
	int now=n+1;
	while(now!=n) stk[++t]=now,now=pre[now];//从终点回溯到起点
	cout<<fi<<'\n';//有始
	while(t>1) cout<<s[stk[t--]]<<'\n';//栈，后进先出
	cout<<la<<'\n';//有终
	
	return 0;
}

```


谢谢阅读！

---

