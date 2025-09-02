# Tree-String Problem

## 题目描述

A rooted tree is a non-directed connected graph without any cycles with a distinguished vertex, which is called the tree root. Consider the vertices of a rooted tree, that consists of $ n $ vertices, numbered from 1 to $ n $ . In this problem the tree root is the vertex number 1.

Let's represent the length of the shortest by the number of edges path in the tree between vertices $ v $ and $ u $ as $ d(v,u) $ .

A parent of vertex $ v $ in the rooted tree with the root in vertex $ r $ $ (v≠r) $ is vertex $ p_{v} $ , such that $ d(r,p_{v})+1=d(r,v) $ and  $ d(p_{v},v)=1 $ . For example, on the picture the parent of vertex $ v=5 $ is vertex $ p_{5}=2 $ .

One day Polycarpus came across a rooted tree, consisting of $ n $ vertices. The tree wasn't exactly ordinary: it had strings written on its edges. Polycarpus positioned the tree on the plane so as to make all edges lead from top to bottom if you go from the vertex parent to the vertex (see the picture). For any edge that lead from vertex $ p_{v} $ to vertex $ v $ $ (1&lt;v<=n) $ , he knows string $ s_{v} $ that is written on it. All strings are written on the edges from top to bottom. For example, on the picture $ s_{7} $ ="ba". The characters in the strings are numbered starting from 0.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF291E/5987d6fa331503653665dfdb5083832d68b0b965.png)An example of Polycarpus's tree (corresponds to the example from the statement)Polycarpus defines the position in this tree as a specific letter on a specific string. The position is written as a pair of integers $ (v,x) $ that means that the position is the $ x $ -th letter of the string $ s_{v} $ ( $ 1&lt;v<=n $ , $ 0<=x&lt;|s_{v}| $ ), where $ |s_{v}| $ is the length of string $ s_{v} $ . For example, the highlighted letters are positions ( $ 2,1 $ ) and ( $ 3,1 $ ).

Let's consider the pair of positions $ (v,x) $ and $ (u,y) $ in Polycarpus' tree, such that the way from the first position to the second goes down on each step. We will consider that the pair of such positions defines string $ z $ . String $ z $ consists of all letters on the way from $ (v,x) $ to $ (u,y) $ , written in the order of this path. For example, in the picture the highlighted positions define string "bacaba".

Polycarpus has a string $ t $ , he wants to know the number of pairs of positions that define string $ t $ . Note that the way from the first position to the second in the pair must go down everywhere. Help him with this challenging tree-string problem!

## 说明/提示

In the first test case string "aba" is determined by the pairs of positions: (2, 0) and (5, 0); (5, 2) and (6, 1); (5, 2) and (3, 1); (4, 0) and (4, 2); (4, 4) and (4, 6); (3, 3) and (3, 5).

Note that the string is not defined by the pair of positions (7, 1) and (5, 0), as the way between them doesn't always go down.

## 样例 #1

### 输入

```
7
1 ab
5 bacaba
1 abacaba
2 aca
5 ba
2 ba
aba
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
1 ab
5 bacaba
1 abacaba
2 aca
5 ba
2 ba
bacaba
```

### 输出

```
4
```

# 题解

## 作者：Little_Biscuit (赞：3)

题目说树边上有小写字符串,可以看成从树根到一个叶子节点为原串,有多少个叶子节点就有多少原串,对所有这些字符串都进行kmp就可以计算匹配串出现次数

**那么就是在树上跑KMP**,具体跑kmp的方法看代码

ps:KMP要加优化,不加优化会被最后一个点卡

```c
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

int n;
struct node
{
    int to;
   string  s;
};
vector<node>bian[100005];
int ans;
char  a[100005];
int next1[100005];int lena;
void get_next(char *b)//求next数组
{
     next1[0]=-1;
    int k=-1;
    int lenb=strlen(b);
    for(int i=1;i<lenb;i++)
    {
        while(k>=0&&b[k+1]!=b[i])
        {
            k=next1[k];
        }
        if(b[k+1]==b[i])
            k++;
        if(b[i+1]==b[k+1])//kmp的优化
        next1[i]=next1[k+1];
        else next1[i]=k;
    }
}
void dfs(int now,int nowj,int fa)//跑kmp
{
    for(int i=0;i<bian[now].size();i++)
    {
        if(bian[now][i].to==fa)return;
        string temp=bian[now][i].s;
        int lens=temp.size();
        int j=nowj;
        for(int k=0;k<lens;k++)
        {
            while(j>=0&&a[j+1]!=temp[k])
            {
                j=next1[j];
            }
            if(a[j+1]==temp[k])j++;
            if(j==lena-1)
            {
               //cout<<temp;
               // printf(" now=%d to=%d  %d  %d\n",now,bian[now][i].to ,k+1,j+1);
                ans++;
                j=next1[j];
            }
        }
        dfs(bian[now][i].to,j,now);
    }
   
}

int main()
{
 ios_base::sync_with_stdio(0);//cin优化
    cin.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++)
    {
         int p;string temp;
         cin>>p;
         cin>>temp;
         bian[p].push_back(node{i,temp});
  
    }
    cin>>a;
    lena=strlen(a);
    get_next(a);
    dfs(1,-1,0);
    cout<<ans;
    return 0;
}

```


---

## 作者：peterwuyihong (赞：2)

题意：给你一棵树，每个边上有一个字符串，定义一个节点的字符串为 $1$ 到这个点字符串相连，最后给你一个串 $t$ ，求这个串在所有节点的字符串出现次数。

写这个题的原因：[这个](https://codeforces.com/blog/entry/44351)里找到的（雾

不会 $\text{dsu}$。。。

1.可以做一个前缀 $\text{Hash}$，**新到一个点就更新多了多少答案**。比如 $1-2-3$ 的路径，$1-2$ 上是 $aba$，$2-3$ 上是 $bab$，$t$ 是 $ab$。你做好 $2$ 的前缀 $\text{Hash}$，扩展到 $3$ 的时候就增加 $([a]b)(ab)$ 两个，$[]$ 表示上一个串的，复杂度 $O(|∑|+n)$。

2.可以做一个前缀 $\text{kmp}$，然后你新定义每个点的字符串为 $t+\#+$ 根到这个点路径上的字符串，对这个做 $\text{kmp}$，然后求有多少 $\pi$ 数组的长度为 $|t|$ 即可。

2 做法是口胡的，但是和 1 差不多，这里给出一个 1 的写法。

现在是 $10:56$，我开始写这个题。

现在是 $11:22$，我写完了。

```cpp
#define maxn 300010
using u64=unsigned long long;
int n;
int x;
string edge[maxn],t;
int len[maxn],mx;
int head[maxn],Next[maxn],tot,ver[maxn];
void add(int x,int y,string z){
	ver[++tot]=y;
	edge[tot]=z;
	len[tot]=z.size();
	mx+=len[tot];
	Next[tot]=head[x];
	head[x]=tot;
}
u64 pw[maxn];
int ans[maxn];
u64 Ans;
u64 f[maxn],G;
int top;
u64 H(int l,int r){
	return f[r]-f[l-1]*pw[r-l+1];
}
void dfs(int x){
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		for(auto j:edge[i]){
			top++;
			f[top]=f[top-1]*131+j-'a'+1;
			if(top-len[0]+1>=1)
				ans[y]+=H(top-len[0]+1,top)==G;
		}
		dfs(y);
		top-=len[i];
	}
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	rep(i,2,n)cin>>x>>t,add(x,i,t);
	cin>>t;
	len[0]=t.size();
	for(auto i:t)G=G*131+i-'a'+1;
	pw[0]=1;
	rep(i,1,mx)pw[i]=pw[i-1]*131;
	dfs(1);
	rep(i,2,n)Ans+=ans[i];
	cout<<Ans;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
我去，被++运算的优先级埋伏到了。。。我原来写的是 ```f[++top]=f[top-1]*131+j-'a'+1```

---

## 作者：yuzhechuan (赞：2)

不用什么kmp,ac自动机，倍增之类，一个hash直接解决

---

### 题解：

注意到字符数最多只有$3\times 10^5$，于是暴力拆开重新构树，从上往下dfs一遍，同时开一个栈记录一下各个深度的前缀hash值，在每个点上O(1)判断一下合不合法就好了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t,class ...A> inline void read(t &x,A &...a){
	read(x);read(a...);
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=3e5+5;
int pw,mod,aim,n,m,ha[N],ans;
char s[N],ch[N];
vector<int> g[N];

bool isprime(int x){
	for(int i=2;1ll*i*i<=x;i++) if(x%i==0) return 0;
	return 1;
}

bool check(int x){
	return (1ll*ha[x-m]*pw%mod+aim)%mod==ha[x]; //O1判断
}

void dfs(int x,int d){
	if(d) ha[d]=(233ll*ha[d-1]+ch[x])%mod; //开个栈记录
	if(d>=m) ans+=check(d);
	for(int y:g[x]) dfs(y,d+1);
}

signed main(){
	srand(time(NULL));
	for(mod=1e9+7+rand();!isprime(mod);mod++) ; //我用了随机模数
	read(n);
	for(int i=2,nn=n,fa;i<=nn;i++){
		read(fa);
		scanf("%s",s+1);m=strlen(s+1);
		for(int i=1,last=fa;i<m;i++) g[last].push_back(++n),ch[last=n]=s[i];
		ch[i]=s[m];
		g[m==1?fa:n].push_back(i);
	}
	scanf("%s",s+1);m=strlen(s+1);pw=1;
	for(int i=1;i<=m;i++) aim=(233ll*aim+s[i])%mod,pw=233ll*pw%mod;
	dfs(1,0);
	write(ans);
}
```

---

