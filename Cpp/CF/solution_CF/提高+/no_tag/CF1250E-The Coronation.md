# The Coronation

## 题目描述

The coronation of King Berl XXII is soon! The whole royal family, including $ n $ daughters of Berl XXII, will be present.

The King has ordered his jeweler to assemble $ n $ beautiful necklaces, so each of the princesses could wear exactly one necklace during the ceremony — and now these necklaces are finished. Each necklace consists of $ m $ gems attached to a gold chain. There are two types of gems used in the necklaces — emeralds and sapphires. So, each necklace can be represented by a sequence of $ m $ gems (listed from left to right), and each gem is either an emerald or a sapphire. Formally, the $ i $ -th necklace can be represented by a binary string $ s_i $ of length $ m $ ; if the $ j $ -th character of $ s_i $ is 0, then the $ j $ -th gem in the $ i $ -th necklace is an emerald; otherwise, this gem is a sapphire.

Now, looking at the necklaces, the King is afraid that some of his daughters may envy the other daughters' necklaces. He wants all necklaces to look similar. Two necklaces are considered similar if there are at least $ k $ positions where these necklaces contain the same type of gems.

For example, if there is a necklace represented by a sequence 01010111 and a necklace represented by a sequence 01100000, then there are $ 3 $ positions where these necklaces contain the same type of gems (both first gems are emeralds, both second gems are sapphires, and both fifth gems are emeralds). So if $ k = 3 $ , these necklaces are similar, and if $ k = 4 $ , they are not similar.

The King thinks that if two of his daughters notice that their necklaces are not similar, then they may have a conflict — and, obviously, he doesn't want any conflicts during the coronation! So Berl XXII wants to tell some of his daughters to wear their necklaces backward. If a necklace is worn backward, then the sequence of gems in this necklace is reversed. For example, if a necklace is represented by a sequence 01100, then, if worn backward, it would be represented by a sequence 00110. The King wants to find the minimum number of necklaces to be worn backward during the coronation so that there are no conflicts.

Berl XXII is too busy with preparation for the coronation, so he ordered you to resolve this issue for him. Help him — and he will give you a truly royal reward!

## 样例 #1

### 输入

```
5
5 7 2
1010100
0010101
1111010
1000010
0000101
6 9 3
011111110
100111000
111100000
000111111
110100111
111110111
3 4 2
0001
1000
0000
3 4 4
0001
1000
0000
2 4 3
0001
1000
```

### 输出

```
2
1 3 
1
3 
0

-1
1
1 
```

# 题解

## 作者：GavinZheng (赞：4)



[ The Coronation](https://codeforces.com/contest/1250/problem/E)

又是一道并查集。。。最近做的并查集咋这么多。。。

## 思路

首先，维护元素间关系的题想到并查集。

因为这里涉及到“翻转”操作。所以我们把反转过后的点$i$设为$i'$，令$i'=i+n$。然后使用拆点并查集来计算。

我们把需要同时满足的条件放入一个并查集。然后对于任意两个串，都有四种情况：

1. 两个串无论转不转都不相似，显然无解，直接输出-1即可。
2. 两个串无论转不转都相似，因为这两个串之间没有相互牵制的限制，所以不管。
3. 两个串相似当且仅当其中一个翻转。那么这时候将$i,j+n$合并，将$j,i+n$合并。（代表了如果取$i$ , $j+n$必须取，反之亦然）
4. 两个串相似当且仅当没有一个翻转，那么这时候将$i,j$合并，将$i+n,j+n$合并。（理由同上）

这样我们就维护了并查集之间的关系。而题目求的就是在满足上述条件情况下，把所有字母代表的点都取到，形如$i'$的字母取的最少。我们可以给并查集加权来维护这个东西。

又因为对于$i$处于的集合，这个集合和$i'$所在的集合的唯一区别是所有字母取反($i$变成$i'$，$i'$变成$i$)。

所以对于这两个集合，无论取哪个，能取到的字母都是一样的。而同种字母$i$和$i'$只能取一个。所以取哪个集合效果等价，那我们就贪心的取权值最小的那个集合。

具体看代码实现吧。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
int map[55][55],size[105],n,m,k,fa[105];
bool visit[105];
char s[55];//i=keep i'=i+n=reverse
vector<int>ans;
int check(int u,int v) {
    int flag=0;int m1=0,m2=0;
    for(int i=1;i<=m;i++){if(map[u][i]^map[v][i])flag++;}
    if(flag<=k){m1=1;}
    flag=0;
    for(int i=1,j=m;i<=m;i++,j--){if(map[u][i]^map[v][j])flag++;}
    if(flag<=k){m2=1;}
    if(m1&&m2)return 0;
    else if(m1&&!m2)return 2;
    else if(!m1&&m2)return 1;
    else return -1;
}
int get(int x){return (fa[x]==x)?x:(fa[x]=get(fa[x]));}
void uni(int x,int y){size[get(y)]+=size[get(x)];fa[get(x)]=get(y);}
void solve() {
    ans.clear();
    memset(map,0,sizeof(map));
    memset(size,0,sizeof(size));
    memset(visit,0,sizeof(visit));
    scanf("%d%d%d",&n,&m,&k);k=m-k;
    for(int i=1;i<=n;i++) {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)map[i][j]=(s[j]=='1')?1:0;
    }
    for(int i=1;i<=2*n;i++)fa[i]=i;
    for(int i=n+1;i<=2*n;i++)size[i]=1;
    for(int i=1;i<=n;i++) {
        for(int j=i+1;j<=n;j++) {
            int tmp=check(i,j);
            if(tmp==-1){printf("-1\n");return;}
            else if(tmp==1){
                if(get(i)==get(i+n)||get(j)==get(j+n)){printf("-1\n");return;}
                if(get(i)!=get(j+n)){uni(i,j+n);}
                if(get(j)!=get(i+n)){uni(j,i+n);}
            }
            else if(tmp==2){if(get(i)!=get(j))uni(i,j);if(get(i+n)!=get(j+n))uni(i+n,j+n);}
        }
    }
    for(int i=1;i<=n;i++) {
        if(get(i)==get(i+n)){printf("-1\n");return;}
        else if(visit[get(i)])continue;
        else if(visit[get(i+n)]){ans.push_back(i);continue;}
        else if(size[get(i)]>size[get(i+n)]){visit[get(i+n)]=1;ans.push_back(i);}
        else {visit[get(i)]=1;}
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++)printf("%d ",ans[i]);
    printf("\n");
}
int main() {
    int t;scanf("%d",&t);
    while(t--)solve();
}
```



## Tips

对于这类维护元素间两两关系（改变一个会同时改变其他的），很容易使用拆点并查集维护。需要注意的是每当我们得到一个信息。我们需要把这个信息能得到的**所有**关系都体现在并查集中。也就是说要把开出来的虚点当作实际点来处理。举个例子，如果上面的第四种情况只合并了$i,j$没有合并$i+n,j+n$。会得到WA11的好成绩。

---

## 作者：CDFLS_mao_zx (赞：0)

## $\text{CF1250E}$

### 吐槽：

不知道为啥你谷就是抓不会记录，然后大家都 $\text{UKE}$ ，$\text{stO GVZ Orz}$ （楼上奆佬）

### 题意：

定义两个 $\text{01}$ 串 $a,b$ 相似为满足 $k\leq\sum_{1}^{len}{[a_i=b_i]}$，其中 $\text{[a_i=b_i]}$ 表示当 $a_i==b_i$ 为 $\text{ture}$ 时取 $\text{1}$ 否则取 $\text{0}$ ,给定 $n$ 个串，可以对串进行翻转，问最少需要多少次翻转才能使得所有串**两两相似**。

翻转操作就是倒过来读。

### 思路：

我们发现每个串有两种状态，且要求串两两相似，所以我们可以考虑使用二分图，$\text{TwoSet}$ 一类善于处理选择的算法，$\text{TwoSet}$ 的话，楼上 $\text{GVZ}$ 奆佬有很详细的讲解 ，所以我们考虑二分图。  

不难想到可以将一个串视作两个点，然后，对每两个**不相似**的点连一条边，最后再将一个串的两个点连上边，最后做一次黑白染色，就可以得出一种合法的方案。

我们发现每一种合法的方案实际上也对应着二分图中的一种染色方式，也就是说，染色方式和合法方案是一一对应的，所以我们可以直接使用染色出来的结果。

当然，如果无法完成黑白染色，那么就不可以得出合法的方案，输出 $\text{-1}$ 。如果可以，对于二分图中的每一个连通块，我们可以取黑白任意一个部分，当然取代价较小的一部分就可以了，输出方案的方式将在代码中讲解。

### 代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
inline void read(int &x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')
	ch=getchar();
	
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
int i,j,k,m,n,t,ans,flag;
const int N=110;
vector<int> a[N];
int val[N][N],col[N],rk[N],p[N],s[2];
void dfs(int u)
{
	if(u>n)//一定是翻转了的才统计
	s[col[u]]++;
	
	rk[u]=t;//记录该点属于哪一个连通块
	for(int v:a[u])
	{
		if(col[v]!=-1)
		{
			if(col[v]==col[u])
			flag=1;
			continue;
		}
		col[v]=col[u]^1;
		dfs(v);
	}
}
signed main()
{
	int tot;read(tot);
	while(tot--)
	{	
		ans=t=flag=0;
		memset(col,-1,sizeof(col));//多测清空
		read(n),read(m),read(k);
		for(i=1;i<=n;i++)
		{
			a[i].clear(),a[i+n].clear();//边也需要清空
			char ch[N];
			scanf("%s",ch+1);
			for(j=1;j<=m;j++)
			val[i+n][m-j+1]=val[i][j]=ch[j]-'0';
		}
		for(i=1;i<=n;i++)
		for(j=1;j<=2*n;j++)
		{
			if(i==j||(j<i)||(j-n<i&&j>n))
			continue;
			if(j==i+n)
			{
				a[i].push_back(j);
				a[j].push_back(i);
				continue;
			}
			int cnt=0;
			for(int k=1;k<=m;k++)
			if(val[i][k]==val[j][k])
			cnt++;
			
			if(cnt>=k)
			continue;
			a[i].push_back(j);
			a[j].push_back(i);
		}
		for(i=1;i<=n;i++)
		if(col[i]==-1)
		{
			s[0]=s[1]=0;t++;col[i]=1;//分别统计黑白块数，选择较小的
			dfs(i);
			ans+=min(s[0],s[1]);
			p[t]=(s[0]<s[1]);//我们记录这一个连通块选择的部分
		}
		if(flag)
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n",ans);
		for(i=n+1;i<=2*n;i++)
		if(p[rk[i]]^col[i])
		printf("%d ",i-n);
		
		printf("\n");
	}
	return 0;
}


```







  

---

