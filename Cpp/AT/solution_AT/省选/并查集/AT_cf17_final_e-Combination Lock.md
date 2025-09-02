# Combination Lock

## 题目描述

有字符串 $S$，按照任意顺序进行任意次以下 $N$ 种操作：

- 操作 $i$：$ S $ 的第 $ l_i $ 个字母到第 $ r_i $ 个字母分别变为它们的下一个字母。(`a` 变成 `b`， `b` 变成 `c`・・・)；假设 `z` 的下一个字母是 `a`。

判断是否可以把 $S$ 变成回文。

## 说明/提示

- $ 1\ \leq\ |S|\ \leq\ 10^5 $
- $ S $ 只由小写字母组成。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ |S| $

样本解释 $\ 1$：

例如，按顺序进行操作，就会变成 `bixzja`→`bjyzja`→`bjzakb`→`bkaakb`，也就是变成回文字符串了。

## 样例 #1

### 输入

```
bixzja
2
2 3
3 6```

### 输出

```
YES```

## 样例 #2

### 输入

```
abc
1
2 2```

### 输出

```
NO```

## 样例 #3

### 输入

```
cassert
4
1 2
3 4
1 1
2 2```

### 输出

```
YES```

# 题解

## 作者：Enoch006 (赞：6)

### 题目简介：

有字符串 $S$，按照顺序多次进行以下 $N$ 种操作：

- 操作 $i$：$ S $ 的第 $ l_i $ 个字母到第 $ r_i $ 个字母分别变为它们的下一个字母。(`a` 变成 `b`， `b` 变成 `c`・・・)；假设 `z` 的下一个字母是 `a`。

判断是否可以把 $S$ 变成回文。

### 题目思路：
要把一个字符串变成回文串，也就是说要把关于中点对称两个字符变成一样的。进一步可推出要使关于中点对称两个字符之差为 $0$。

**考虑差分。**

把整个序列差分成数组 $a$，对序列进行的操作 $[l,r]$ 可以视为 $a[l]+1$，$a[r+1]-1$。最开始的 $a[l]+a[r+1]$ 是一个定值，进行了操作后他们的和没有变，也就是说此时可以任意确定 $a[l]+a[r+1]$ 的值。

同样的，如果进行两次操作 $[l_1,r]$，$[l_2,r]$ 也可以视为 $a[l_1]+1$，$a[l_2]+1$，$a[r+1]-2$。他们的和仍然没有变，可以任意确定 $a[l_1]+a[l_2]+a[r+1]$ 的值。

可以把每个字符的位置看为一个点，点 $i$ 的权值为 $a[i]$。**初始化时**，要将关于中点对称两点连边。**在每次操作** $[l,r]$ 时，可以将 $l$ 和 $r+1$ 两点连接一条边，将权值加在父结点上。考虑到差分的性质，当每一个连通的分量之和等于 $0$ 时（模 $26$ 意义下），则是有解的，反之亦然。

用**并查集**或者 **DFS** 都可以做，我这里选择用并查集。

一个例子：

```
bixzja
2
2 3
3 6
```

`bixzja`→`bjyzja`→`bjzakb`→`bkaakb`。

是可以构成回文串的。我们模拟一下过程：

首先计算出差分数组 $a=${$2,7,15,2,-16,-9,-1$}。

接着分别预处理连接 $0$ 到 $6$，$1$ 到 $5$，$2$ 到 $4$。对于两条操作，连接 $1$ 到 $3$，$2$ 到 $6$。

连接后，$0$、$2$、$4$ 和 $6$ 是一个连通的分量；$1$、$3$ 和 $5$ 是一个连通的分量。所以  $a[0]+a[2]+a[4]+a[6]=2+15-16-1=0$；$a[1]+a[3]+a[5]=7+2-9=0$。两个连通的分量之和都为 $0$。所以是可以构成回文串的。

### 题目代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 200005
using namespace std;
int n,m,len,l,r,d[maxm],fa[maxm];
bool flag=true;
string s;
void init(){
	for(int i=0;i<=len;i++){
		fa[i]=i;
		d[i]=s[i]-s[i-1];
	}
}
int getfa(int x){
	if(fa[x]==x)return x;
	return fa[x]=getfa(fa[x]);
}
void merge(int l,int r){
	int x=getfa(l);
	int y=getfa(r);
	if(x!=y){
		fa[x]=y;
		d[x]=d[y]=d[x]+d[y];
	}
	return;
}
signed main(){
	cin>>s;
	cin>>n;
	len=s.length();
	init();
	for(int i=0;i<=len;i++){
		merge(i,len-i);
	}
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		merge(l-1,r);
	}
	for(int i=0;i<=len;i++){
		if(d[i]%26==0||getfa(i)!=i)continue;
		flag=false;
	}
	if(flag==true)cout<<"YES\n";
	else cout<<"NO\n";
    return 0;
}
```

#### 代码较丑，请各位见谅。

~~题外话：强烈抗议校内普及组模拟考最后一题出成紫的。~~

---

## 作者：HEIMOFA (赞：1)

当我们操作区间 $[l,r]$ 时，相当于将这个区间每个字符 $+1$ 并且模 $26$，很容易想到**差分**。

很明显，如果想要让最后结果变为一个回文串，那就必须让 $S[i]=S[len-i+1]$（$len$ 为字符串 $S$ 的长度）。

为了让这个和差分数组扯上关系，我们让 $S[0]=S[len+1]='a'$，差分数组的长度也会变为 $len+1$。

由于 $S[0]=S[len+1]$，那如果要让 $S[1]=S[len]$，就需要 $(d[1]+d[len+1])\bmod 26=0$。

所以说，我们只需要满足 $(d[i]+d[len-i+2])\bmod 26=0(i\in [1,\lfloor \frac{len+1}{2} \rfloor])$，就说明 $S[i]=S[len-i+1]$（前提：$S[i-1]=S[len-i+2]$）。

对于差分，我们很容易发现 $d[l]+d[r+1]$ 是一个定值，但是 $d[l]$ 和 $d[r+1]$ 可以随意变换。

这时问题便转化成了：合理操作每一个 $d[l_i]$ 和 $d[r_i+1]$，使得 $d[l_i]+d[r_i+1]$ 始终不变且让 $(d[i]+d[len-i+2])\bmod 26=0$。

最难想到的来了，我们可以把 $d[i]+d[len-i+2]$ 抽象成一个点，其点权为 $d[i]+d[len-i+2]=S[i]-S[len-i+1]$（自己推）。

然后将 $d[l]$ 所对应的点与 $d[r+1]$ 所对应的点连边，假设连接了点 $A$ 与 点 $B$，那么它们各自的点权就相当于它们所需要的值。

例如，如果 $A$ 的点权大于 $B$ 的点权，那么减小 $d[l]$ 增大 $d[r+1]$，反之亦然。

这样每一个 $l$ 和 $r$ 都连接了一组连通块，如果每个连通块的和模 $26$ 都为 $0$ 的话，那么可以，否则不行。

>如果有一个连通块和模 $26$ 不为 $0$。
>
>这说明至少有一组连通块无法保证互相平衡，从而构不成回文串。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len;
const int N=1e5+5;
char s[N];
int d[N];
struct DSU{
	int fa[N];
	void init(){
		for(int i=1;i<=len+1;i++) fa[i]=i,d[i]=s[i]-s[i-1];
		return ;
	}
	int find(int x){
		if(fa[x]==x) return x;
		fa[x]=find(fa[x]);
		return fa[x];
	}
	void merge(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return ;
		d[fx]=d[fy]=d[fx]+d[fy];
		fa[fx]=fy;
	}
}check;
 
int main()
{
		scanf("%s",s+1);len=strlen(s+1);
		check.init();
		for(int i=1;i<len-i+2;i++) check.merge(i,len-i+2);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int l,r;scanf("%d%d",&l,&r);
			if(l>r) swap(l,r);
			check.merge(l,r+1);
		}
		for(int i=1;i<=len+1;i++){
			if(check.find(i)!=i) continue;
			if(d[i]%26==0) continue;
			printf("NO\n");
			return 0;
		}
		printf("YES\n");
	return 0;
}
```





---

## 作者：Ferdina_zcjb (赞：0)

题目要求将字符串变为回文串，即将字符串赋予对称性。之后可以推出要使**对称字符之差变为 $0$（模 $26$ 意义下）**。

为了更好的操作，我们考虑**差分**。

差分成数组 $cg$。对区间 $[l,r]$ 的操作可以看为 $cg_l+1$ 与   $cg_{r+1}-1$。其实可以看做任意更改 $cg_l+cg_{r+1}$ 的值。

自然的，对于区间 $[l_l,r]$ 与 $[l_r,r]$ 的操作可以看为任意更改 $cg_{l_l}+cg_{l_r}+cg_{r+1}$ 的值。

经过上述，题目可以简化为：

可以把每个字符的位置看为一个点，点 $i$ 的权值为即为差分数组 $cg_i$，最开始，将对称两点链、连接一条边。操作区间 $[l,r]$ 将 $l$ 与 $r+1$ 连边，权值继承到父节点的权值上。由于差分的性质，如果**所有连通分量的和为 $0$ 时**，就是有解的（模 $26$ 意义下）。所以，此题也是有图论性质的。

其实，用 dfs 和并查集都是可以的，并查集较好实现。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXM = 200001;
using namespace::std;
int n,m,dis[MAXM],fa[MAXM];
string s;
int find(int x){//并查集找父节点。
	if(fa[x]==x)
	    return x;
	return fa[x]=find(fa[x]);
}
void change(int x,int y){//操作区间[l,r]时的差分。
	int fx = find(x),fy = find(y);
	if(fx == fy){
	    return ;
	}
	dis[fx] = dis[fy] = dis[fx] + dis[fy];
	fa[fx] = fy;
}
signed main(){
	cin >> s >> n;
	int len = s.size();
	for(int i=0;i<=len;i++){
		fa[i]=i;
		dis[i] = s[i]-s[i-1];
	}
	for(int i =0;i <= len;i++)change(i,len-i);//初始化。
	for(int i = 1;i <= n;i++){
	    int l,r;//操作区间[l,r]。
		cin >>l >> r;
		change(l-1,r);
	}
	for(int i = 0;i <= len;i++){//判断连通分量的和是否是0。
		if(dis[i]%26 == 0)continue;
		else if(find(i) != i)continue;
		else{
		    cout << "NO";
		    return 0;
		}
	}
	cout<<"YES";
}
```


---

