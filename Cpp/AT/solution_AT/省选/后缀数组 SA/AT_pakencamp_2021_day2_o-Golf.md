# Golf

## 题目描述

给定一个字符串 $S$。定义子串 $S[i:j]$ 表示从字符串 $S$ 的第 $i$ 个字符到第 $j$ 个字符组成的子串。

如果子串 $T$ 满足以下条件，则称其为一个「好字符串」：

- 长度在 1 到 $|S|$ 之间，即 $1 \leq |T| \leq |S|$
- 恰好存在唯一一个整数 $i$，使得 $S[i:i+|T|-1]$ 与 $T$ 相等

例如，若字符串 $S$ 为 `abcbabc`，那么 `cb`、`abcb` 和 `abcbabc` 都是「好字符串」，但 `abc` 和 `zyx` 不是。

接下来有 $Q$ 个查询。对于第 $i$ 个查询，给出两个整数 $L_i$ 和 $R_i$，满足 $1 \leq L_i \leq R_i \leq |S|$，然后解决以下问题：

- 寻找两个整数 $l$ 和 $r$，使得 $1 \leq l \leq L_i$ 且 $R_i \leq r \leq |S|$，并使得子串 $S[l:r]$ 是一个「好字符串」。然后计算 $r-l+1$ 的最小可能值。

## 说明/提示

- 字符串 $S$ 仅由小写英文字母组成。
- $1 \leq |S| \leq 200,000$
- $1 \leq Q \leq 200,000$
- 对于每个 $i$，满足 $1 \leq L_i \leq R_i \leq |S|$

### 样例解释

对于第一个查询，我们可以取 $l=2, r=4$，此时 $r-l+1=3$，这是最小值。注意 `bc` 不是「好字符串」，所以不能取 $l=2, r=3$。在第二个查询中，取 $l=2, r=5$，得到 $r-l+1=4$，是最小值。在第三个查询中，我们取 $l=1, r=7$，则 $r-l+1=7$，这是最小值。值得注意的是，字符串 $S$ 本身是一个「好字符串」。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
abcbabc
5
2 3
2 5
1 7
4 4
6 6```

### 输出

```
3
4
7
2
3```

## 样例 #2

### 输入

```
yyxxzzyyxx
5
3 3
1 1
10 10
5 5
7 7```

### 输出

```
3
5
5
2
2```

## 样例 #3

### 输入

```
qprrrrrpprqrrppq
20
7 8
6 8
4 7
7 12
6 7
5 5
6 8
4 6
4 4
2 3
7 11
8 9
6 7
11 12
11 15
5 6
4 5
13 13
9 13
5 7```

### 输出

```
4
4
5
6
4
4
4
5
3
3
5
3
4
2
5
4
4
3
5
4```

# 题解

## 作者：Miss_SGT (赞：1)

后缀自动机做法。

询问给出了一个前缀和后缀分别作为左端点和右端点的范围。

当我们固定 $i$ 作为右端点时，一定有一个 $l_i$ 使得当 左端点小于等于 $l_i$ 时子串只出现过一次，反之左端点大于 $l_i$ 时字串出现过不只一次，否则 $i$ 不能作为右端点。

假如我们求出了所有 $l_i$，那么询问 $(L_j,R_j)$ 的答案就是 

  $$\min \limits_{i \ge R_j}(i-\min(l_i,L_j))$$

扫描线可以轻松完成。

用 SAM 求 $l_i$ 是简单的。令 $sz_x$ 为其 $endpos$ 集合大小，$top_x$ 为 $parent$ 树上 $x$ 的祖先节点中从下往上第一个 $sz$ 大于 1 的点。则 $l_i = i - len_{top_x}$，$x$ 是代表前缀 $i$ 的节点。

正确性显然，跳父亲就是不断在将左端点变大，$sz$ 本身就是出现次数。


```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
char s[N];
int n,q,ed[N];
int tot=1,id[N<<1],c[N<<1],sz[N<<1],top[N<<1];
struct SAM{int son[26],fa,len;}t[N<<1];
inline void insend(int x,int &p){
	int now=++tot;
	t[now].len=t[p].len+1;
	for(;p&&!t[p].son[x];p=t[p].fa) t[p].son[x]=now;
	if(!p) t[now].fa=1;
	else{
		int q=t[p].son[x];
		if(t[q].len==t[p].len+1) t[now].fa=q;
		else{
			int k=++tot;
			t[k]=t[q],t[k].len=t[p].len+1;
			t[now].fa=t[q].fa=k;
			for(;p&&t[p].son[x]==q;p=t[p].fa) t[p].son[x]=k;
		}
	}p=now;
}
struct node{int l,r,i;}a[N];
inline bool cmp(node x,node y){return x.r>y.r;}
int t1[N],t2[N],ans[N];
inline void add1(int x,int y){for(;x<=n&&t1[x]>y;x+=x&-x) t1[x]=y;}
inline int query1(int x){
	int ans=1<<30;
	for(;x;x-=x&-x) ans=min(ans,t1[x]);
	return ans;
}
inline void add2(int x,int y){for(;x&&t2[x]>y;x-=x&-x) t2[x]=y;}
inline int query2(int x){
	int ans=1<<30;
	for(;x<=n;x+=x&-x) ans=min(ans,t2[x]);
	return ans;
}
int main(){
	n=readstr(s+1)-s-1;
	for(int i=1,p=1;i<=n;++i) insend(s[i]-='a',p),sz[p]=1,ed[i]=p;
	for(int i=1;i<=tot;++i) ++c[t[i].len];
	for(int i=1;i<=n;++i) c[i]+=c[i-1];
	for(int i=1;i<=tot;++i) id[c[t[i].len]--]=i;
	for(int i=tot;i;--i) sz[t[id[i]].fa]+=sz[id[i]];
	for(int i=1;i<=tot;++i){
		int p=id[i];
		top[p]=(sz[p]>=2?p:top[t[p].fa]);
	}
	read(q);
	for(int i=1;i<=q;++i) read(a[i].l),read(a[i].r),a[i].i=i;
	sort(a+1,a+q+1,cmp);
	for(int i=1;i<=n;++i) t1[i]=t2[i]=1<<30;
	for(int i=n,j=1;i;--i){
		if(sz[ed[i]]==1){
			int l=i-t[top[ed[i]]].len;
			add1(l,i-l+1),add2(l,i+1);
		}
		for(;j<=q&&a[j].r==i;++j) ans[a[j].i]=min(query1(a[j].l),query2(a[j].l)-a[j].l);
	}
	for(int i=1;i<=q;++i) print(ans[i]),pc('\n');
	flush();
	return 0;
}
```

---

