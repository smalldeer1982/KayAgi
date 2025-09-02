# [JLOI2008] CODES

## 题目描述

给定 $n$ 个 $\texttt{01}$ 编码串 $S_1,S_2,\dots,S_n$，你的任务是寻找一个编码串 $T$，使得它至少可以被分解为两种不同的 $S_i$ 的排列。

例如：

给定 $5$ 个 $\texttt{01}$ 编码串：$S_1=\texttt{0110},S_2=\texttt{00},S_3=\texttt{111},S_4=\texttt{001100},S_5=\texttt{110}$。那么一个符合要求的编码串 $T$ 是：$\texttt{001100110}$，它有以下两种分解方法：

$\texttt{00}+\texttt{110}+\texttt{0110} (S_2+S_5+S_1)$ 或 $\texttt{001100}+\texttt{110} (S_4+S_5)$

而 $0110110$ 就不符合要求，它只有一种分解方法 $\texttt{0110}+\texttt{110} (S_1+S_5)$。

你要寻找长度最短的符合要求的编码串 $T$。若有多个符合要求的最短编码串 $T$，则输出字典顺序最小的。

## 说明/提示

- $n\le 20$

## 样例 #1

### 输入

```
5
0110
00
111
001100
110
```

### 输出

```
9
001100110
```

# 题解

## 作者：Forever1507 (赞：6)

爆搜就行了，对，就是爆搜。

考虑此时你手上有俩字符串 $s_1,s_2$（不妨设前者更长），那么要是能够继续往后拼答案，$s_2$ 必须是 $s_1$ 的前缀，因为长度只有 $20$，直接暴力匹配。

然后设 $s'$ 为在 $s_1$ 前面砍掉 $s_2$ 之后的答案，那么这个东西就显然是另一个字符串的前缀，或者另一个字符串是它的前缀，$n$ 只有 $20$，枚举即可。

那么，只要在最开始枚举两个串，使得其中一个是另一个的前缀，以它们为 $s_1$ 和 $s_2$ 开搜，答案取最小即可，搜到相等之后维护答案。

当然直接这么搜会寄，加一个比较强的剪枝：

当前的这两个串的长度若超过已有最小值，停下来，不搜了，反正对答案没贡献。

还有一个细节，初始答案设 $10^9$ 会爆栈+超时，虽然不会证明，但是答案很难给你构造得超过所有串的总长（即 $400$），不行的话你设 $10^3$ 都行，最大差不多开到 $9000$ 都没事。（所以这个做法之后也有可能被 hack，或者谁要是能提供严谨证明麻烦私一下）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[25];
string ans;
int len=400;
bool cmp(string s1,string s2){
	return s1.size()>s2.size();
}
void dfs(string s1,string s2){//s1长
	if(s1.size()>len||s2.size()>len)return;//大力剪枝
	if(s1.size()==s2.size()){
		if(len>s1.size()){
			len=s1.size();//更新答案
			if(ans==""||ans.size()>s1.size())ans=s1;
			else ans=min(ans,s1);
		}
		return;
	} 
	if(s1.size()<s2.size())swap(s1,s2);//保证s1更长
	int m=s1.size()-s2.size();
	for(int i=1;i<=n;++i){
		if(s[i].size()>=m){//s'是s[i]的前缀
			string _s="";
			for(int i=s2.size();i<s1.size();++i)_s+=s1[i];
			if(s[i].substr(0,m)==_s)dfs(s1,s2+s[i]);
		}
		else{//反之
			if(s1.substr(s2.size(),s[i].size())==s[i])dfs(s1,s2+s[i]);
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>s[i];
	sort(s+1,s+n+1,cmp);//按长度排序，不然substr会挂
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(s[i].substr(0,s[j].size())==s[j]){
				dfs(s[i],s[j]);
			}
		}
	}
	cout<<len<<'\n'<<ans;
	return 0;
}
```


---

## 作者：GNAQ (赞：3)

大概我的做法比较丑TAT  下面那位小哥0.8k暴虐我2.1k

首先考虑我们可以DP，设状态 `dp[i][j]` 表示 第 $i$ 个字符串 还需要匹配长度为 $j$ 的前缀 可以得到的最短答案。

## 转移：

转移就是枚举一个字符串 $i_0$ 来与之匹配。记忆化搜索非常好写。注意讨论两种情况：

1. $i_0$ 比当前前缀长

2. $i_0$ 比当前前缀短

用 `dp[i0][?]` +   _匹配长度_ 去更新`dp[i][j]`。(?是因为我懒得讨论了……代码里有）

数据范围很小，暴力匹配即可。

## 注意事项：

**第一个细节就是字符串可以重复利用**

**第二个细节是让 $dp[i][0]=0$ ，其余为 $+\infty $ **

**第三个细节就是最后统计答案和DP过程中别忘记比较字典序**

## 字典序：

令 `answ[i][j]` 保存当前 `dp[i][j]` 对应的具体方案

更新 `dp[i][j]` 顺便更新 `answ[i][j]` 即可。

每次遇到 `dp[i0][?]+len` 与 `dp[i][j]` 相等的情况，判定字典序，然后更新 `answ[i][j]` 即可。

最后的答案是 `dp[i][len[i]]`

$O(\text{跑得过})$

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
using namespace std;

char wd[21][21]={0};
int n=0,len[21]={0},dp[21][21]={0};
char answ[21][21][200]={0};

int vis[21][21][2]={0};

inline bool judgex(int a,int b,int pa,int pb,int l)
{
    for (int i=1;i<=l;i++) if (wd[a][pa+i-1]!=wd[b][pb+i-1]) return false;
    return true;
}
inline bool lex(int a,int b,int c,int d,int l)
{
    for (int i=1;i<=l;i++) if (answ[a][b][i]!=answ[c][d][i]) 
        return (answ[a][b][i]>answ[c][d][i]);
}
inline int minx(int now,int pos,int val,int p,int q)
{
    if (val>2*1e9) return min(dp[now][pos],val);
    if ((dp[pos][now]==val && lex(now,pos,p,q,dp[p][q])) || dp[now][pos]>val) 
    {
        for (int i=1;i<=dp[p][q];i++) answ[now][pos][i]=answ[p][q][i];
        for (int i=dp[p][q]+1;i<=val;i++) answ[now][pos][i]=wd[p][q+i-dp[p][q]];
    }
    return min(dp[now][pos],val);
}

inline int _dp(int now,int pos,int sgn)
{
    if (dp[now][pos]!=2*1e9) return dp[now][pos];
    for (int i=1;i<=n;i++) if (now!=i || pos!=len[i])
    {
        if (len[i]<=pos && !vis[now][pos-len[i]][sgn] && judgex(now,i,pos-len[i]+1,1,len[i]))//i is the suffix of A
        {
            vis[now][pos-len[i]][sgn]=1;
            dp[now][pos]=minx(now,pos,_dp(now,pos-len[i],sgn)+len[i],now,pos-len[i]);
            vis[now][pos-len[i]][sgn]=0;
        }
        if (len[i]>pos && !vis[i][len[i]-pos][sgn^1] && judgex(now,i,1,len[i]-pos+1,pos))//i coverd A
        {
            vis[i][len[i]-pos][sgn^1]=1;
            dp[now][pos]=minx(now,pos,_dp(i,len[i]-pos,sgn^1)+pos,i,len[i]-pos);
            vis[i][len[i]-pos][sgn^1]=0;
        }
    }
    return dp[now][pos];
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%s",wd[i]+1),len[i]=strlen(wd[i]+1);
    for (int i=1;i<=20;i++) for (int j=1;j<=20;j++) dp[i][j]=2*1e9;
    int ans=2*1e9,p;
    for (int i=1;i<=n;i++)
    {
        vis[i][len[i]][0]=1;
        if (_dp(i,len[i],0)<ans) { ans=dp[i][len[i]]; p=i; }
        else if (ans!=2*1e9 && _dp(i,len[i],0)==ans && lex(p,len[p],i,len[i],ans)) p=i;
        vis[i][len[i]][0]=0;
    }
    printf("%d\n",ans);
    for (int i=1;i<=ans;i++) printf("%c",answ[p][len[p]][i]); printf("\n");
    return 0;
}
```

---

## 作者：Colinxu2020 (赞：1)

考虑模拟构造两个相同的串。不妨考虑在构造两个串时，我们实际上在干什么，不妨假设我们有两个串 $x,y$，满足 $\lvert x \rvert < \lvert y \rvert$，那么我们实际上希望的是给 $y$ 拼接上一个新的字符串 $S$，来和 $x$ 匹配，因此 $y$ 一定是 $x$ 的前缀，又因为如果我们这一次拼接匹配上了多个串，我们完全可以倒转一下 $x+S,y$，所以不妨钦定每次最多匹配一个串，所以我们只关心两个串中较长的那个的最后一个字符串。

不妨设 $f_{i,j}$ 代表当前构造的两个串中，较长的串的最后一个字符串是 $i$，这个串剩余长度为 $j$ 的后缀没有被匹配，所有这样的串中长度最小，如果长度相同则字典序最小的串。
		
转移的关系就是在当前的较短串中拼接一个字符串，与较长字符串匹配，因为前面都已经匹配好，所以我们不关心前面的串，不妨直接暴力枚举这个字符串。同时注意处理一下匹配后两个串的长度关系翻转的情况。

用广义的 Dijkstra 解决了，因为只有 $n^2$ 种状态，和 $n^3$ 个转移边，考虑到字符串比较的复杂度 $O(n^2)$，总体复杂度为 $O(n^5+n^3 \log n)=O(n^5)$，我不知道为什么有些题解分析出来 $O(n^5 \log n)$，如果不要求字典序最小可以做到 $O(n^3 \log n)$。

```cpp
#include<iostream>
#include<string>
#include<queue>
using namespace std;

const int maxn=20+1;
int n;
string dis[maxn][maxn]; 
string si[maxn];
bool vis[maxn][maxn];

bool cmp(string a, string b){
    if(a.size()&&!b.size())return true;
    if(a.size()!=b.size())return a.size()<b.size();
    return a<b;
}
bool cmp2(string a, string b){
    if(a.size()!=b.size())return a.size()>b.size();
    return a>b;
}
bool prefix(string a, string b){ return b.substr(0,a.size())==a; }
struct qnode{
    string s;
    int pos,len;
    bool operator>(const qnode other)const{ return cmp2(s,other.s); }
};

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>si[i];
    priority_queue<qnode, vector<qnode>, greater<qnode>> pq;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&prefix(si[i],si[j])){
        dis[j][si[j].size()-si[i].size()]=si[j];
        pq.push({si[j],j,(int)si[j].size()-(int)si[i].size()});
    }
    while(pq.size()){
        auto frt=pq.top(); pq.pop();
        if(!frt.len){
            cout<<frt.s.size()<<endl;
            cout<<frt.s<<endl;
            break;
        }
        if(vis[frt.pos][frt.len])continue;
        vis[frt.pos][frt.len]=true;
        auto suf=si[frt.pos].substr(si[frt.pos].size()-frt.len,frt.len);
        for(int i=1;i<=n;i++){
            if(si[i].size()<=frt.len&&prefix(si[i],suf)&&cmp(dis[frt.pos][frt.len], dis[frt.pos][frt.len-si[i].size()])){
                dis[frt.pos][frt.len-si[i].size()]=dis[frt.pos][frt.len];
                pq.push({dis[frt.pos][frt.len],frt.pos,frt.len-(int)si[i].size()});
            }
            if(si[i].size()>frt.len&&prefix(suf,si[i])&&cmp(dis[frt.pos][frt.len]+si[i].substr(frt.len),dis[i][si[i].size()-frt.len])){
                dis[i][si[i].size()-frt.len]=dis[frt.pos][frt.len]+si[i].substr(frt.len);
                pq.push({dis[i][si[i].size()-frt.len],i,(int)si[i].size()-frt.len});
            }
        }
    }
    //cout<<dis[1][3]<<endl;
}
```

---

## 作者：Mikefeng (赞：1)

## 题意

给定几个 $01$ 串，求一个最短的 $01$ 串，要求该串至少有两种方法分解为给定 $01$ 串的组合。

## 做法

考虑同时构造两个 $01$ 串，枚举较长 $01$ 串最后选的一个 $01$ 串是什么，以及它相比另一个 $01$ 串多了多少位，然后枚举用哪个 $01$ 串去填补另一个字符串。

由于要求求出最短的合法 $01$ 串，我们可以利用 dijkstra的思想，优先转移长度较短的状态，由于保证有合法串，时间复杂度最大是严格的 $O(n^5\log n)$，如果不要求最小字典序，还可以做到 $O(n^3\log n)$，并且由于数据强度暴搜能过，所以能跑到最优解第一页。

## 代码
```cpp
const int N=25;
const int inf=0x3f3f3f3f;
int n,ans=inf;
int len[N];
char c[N][N];
bool vis[N][N][N];
inline bool check(int i,int j,int k){
	if(i==j&&!k) return 0;
	F(l,1,min(len[i]-k,len[j])) if(c[i][l+k]!=c[j][l]) return 0;
	return 1;
}
struct node{
	int id,len,dis;
	bool operator < (const node &x)const{
		return dis>x.dis;
	}
};
priority_queue<node> q;
int dis[N][N];
bool ok[N][N];
string s[N][N],s1;
inline void dij(){
	memset(dis,inf,sizeof dis);
	F(i,1,n){
		dis[i][0]=len[i];
		F(j,1,len[i]) s[i][0]+=c[i][j];
		q.push({i,0,len[i]});
	}
	while(!q.empty()){
		node tmp=q.top();q.pop();
		int i=tmp.id,l=tmp.len;
		if(tmp.dis>ans) return;
		if(tmp.dis==ans) s1=min(s1,s[i][l]);
		if(ok[i][l]) continue;
		ok[i][l]=1;
		if(l==len[i]){
			ans=dis[i][l];
			s1=s[i][l];
			continue;
		}
		F(j,1,n){
			if(!vis[i][j][l]) continue;
			if(len[j]>=len[i]-l){
				if(dis[j][len[i]-l]>dis[i][l]-len[i]+len[j]+l){
					dis[j][len[i]-l]=dis[i][l]-len[i]+len[j]+l;
					s[j][len[i]-l]=s[i][l];
					F(k,len[i]-l+1,len[j]) s[j][len[i]-l]+=c[j][k];
					q.push({j,len[i]-l,dis[j][len[i]-l]});
				}else if(dis[j][len[i]-l]==dis[i][l]-len[i]+len[j]+l){
					string s1=s[i][l];
					F(k,len[i]-l+1,len[j]) s1+=c[j][k];
					if(s1<s[j][len[i]-l]) s[j][len[i]-l]=s1;
				}
			}else{
				if(dis[i][l+len[j]]>dis[i][l]){
					dis[i][l+len[j]]=dis[i][l];
					s[i][l+len[j]]=s[i][l];
					q.push({i,l+len[j],dis[i][l+len[j]]});
				}else if(dis[i][l+len[j]]==dis[i][l]) s[j][l+len[j]]=min(s[i][l],s[j][l+len[j]]);
			}
		}
	}
}
int main(){
	n=read();
	F(i,1,n){
		scanf(" %s",c[i]+1);
		len[i]=strlen(c[i]+1);
	}
	F(i,1,n) F(j,1,n) F(k,0,len[i]) vis[i][j][k]=check(i,j,k);
	dij();
	printf("%d\n",ans);
	printf("%s\n",s1.c_str());
	return 0;
}
```

---

