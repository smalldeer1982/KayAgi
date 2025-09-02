# Coach

## 题目描述

A programming coach has $ n $ students to teach. We know that $ n $ is divisible by $ 3 $ . Let's assume that all students are numbered from $ 1 $ to $ n $ , inclusive.

Before the university programming championship the coach wants to split all students into groups of three. For some pairs of students we know that they want to be on the same team. Besides, if the $ i $ -th student wants to be on the same team with the $ j $ -th one, then the $ j $ -th student wants to be on the same team with the $ i $ -th one. The coach wants the teams to show good results, so he wants the following condition to hold: if the $ i $ -th student wants to be on the same team with the $ j $ -th, then the $ i $ -th and the $ j $ -th students must be on the same team. Also, it is obvious that each student must be on exactly one team.

Help the coach and divide the teams the way he wants.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
3 2 1 
```

## 样例 #2

### 输入

```
6 4
1 2
2 3
3 4
5 6
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
3 2 1 
```

# 题解

## 作者：lava__44 (赞：4)

## CF300B Coach 题解

### 闲话

调了好一会，甚至还重构了一次代码才对，但是还是很喜欢并查集，并查集可爱捏。

***

### 题意省流

$n$ 个学生分成 $3$ 人一组，要满足 $m$ 个条件，每个条件给出两个数 $x,y$，要求 $x$ 和 $y$ 必须在一个组里。

### 正文

要使学生三人一组，一眼使用并查集。

首先考虑无解（输出 $-1$ ）的情况：

- 给出的限制条件中有大于 $3$ 个人组队的情况。
- 有一人或两人落单。

第二种情况的数据：

```
6 4
1 2
3 4
5 6
```

此时没有能够凑出 $3$ 人一队的方案，输出 $-1$。

对于合法的情况可以分三种情况：

1. 组中已经有三人，可以直接成组。
2. 组中有两人，需要找落单一人。
3. 仅有一人，可以与两人组成组或另找两个单人成组。



### 贴码

没有使用技巧，~~人傻常数大~~，但是在 $3\leq n\leq 48$ 的情况下其实不是很要紧。

其实是因为没有精神再去打更好的具体实现了。

```c++
#include<bits/stdc++.h>
#define MAXN 10010
using namespace std;
int n,m,fa[MAXN],ans,ton[MAXN];
int akali[MAXN],num[MAXN],cnt;
bool vis[MAXN],Vis[MAXN];
queue<int> q[MAXN];
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		int fau=find(u),fav=find(v);
		fa[fau]=fav;
	}
	for(int i=1;i<=n;i++) ton[find(i)]++;
	for(int i=1;i<=n;i++){
		if(ton[fa[i]]>=4){
			cout<<-1;
			return 0;
		}
		q[fa[i]].push(i);
		if(!Vis[fa[i]]){
			Vis[fa[i]]=1;
			num[++cnt]=fa[i];
		}
		akali[fa[i]]++;
	}
	for(int i=1;i<=cnt;i++){/*处理 2+1 的情况*/
		if(akali[num[i]]==2){
			for(int j=1;j<=cnt;j++){
				if(i==j) continue;
				if(akali[num[j]]==1){
					akali[num[j]]=0;
					q[num[i]].push(num[j]);
					fa[num[j]]=num[i];
					break;
				}
			}
		}
	}
	for(int i=1;i<=cnt;i++){/*处理 1+1+1 的情况*/
		if(akali[num[i]]==1){
			for(int j=i+1;j<=cnt;j++){
				if(akali[num[j]]==1){
					akali[num[j]]=0;
					q[num[i]].push(num[j]);
					fa[num[j]]=num[i];
					for(int k=1+j;k<=cnt;k++){
						if(akali[num[k]]==1){
							akali[num[k]]=0;
							q[num[i]].push(num[k]);
							fa[num[k]]=num[i];
							break;
						}
					}
					break;
				}
			}
			akali[num[i]]=3;
		}
	}
	for(int i=1;i<=n;i++){
		if(q[fa[i]].size()!=3){/*若有不能成组的则无解*/
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[fa[i]]){
			vis[fa[i]]=1;
			while(!q[fa[i]].empty()){
				cout<<q[fa[i]].front()<<" "; q[fa[i]].pop();
			}
			cout<<"\n";
		}
	}
	return 0;
}
```



---

## 作者：wuyixiang (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF300B)

题目大意：$n$ 个学生分组，每组三人，第 $a_i$ 个学生必须与第 $b_i$ 个学生在同一组，问怎么分才能满足条件。

算法分析：看到“组”，自然想到并查集。可以先用并查集去判断归并完后的每组人数情况，我们发现：如果一个组有三人，可以直接独立；如果是两人，需在和一个一人组组成三人组；如果一个组有一人，可以和两个一人组组成三人组，也可以和一个两人组组成三人组，直接用代码判断即可。

## AC code:

```cpp
#include <iostream>
using namespace std;
int f[10004],n,m,x,y,b[1004][1004],ans[1004][4],qo[1004],liedui1[1005][2],liedui2[1005],cnt,cnt2,cnt3;
int find(int x)//并查集
{
    if(f[x] == x)return x;
    else return f[x] = find(f[x]);
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)f[i] = i;
    for(int i = 1;i <= m;i ++)
    {
        cin >> x >> y;
        int w = find(x),w2 = find(y);
        if(w != w2)f[w] = w2;
    }
    for(int i = 1;i <= n;i ++)b[find(i)][++qo[find(i)]] = i;//记录人数及编号
    for(int i = 1;i <= n;i ++)
    {
        if(qo[i] == 0)continue;
        else if(qo[i] == 3)ans[++cnt][1] = b[i][1],ans[cnt][2] = b[i][2],ans[cnt][3] = b[i][3];//三人组，独立成队
        else if(qo[i] == 2)
        {
            if(cnt3)ans[++cnt][1] = b[i][1],ans[cnt][2] = b[i][2],ans[cnt][3] = liedui2[cnt3],cnt3 --;
            else liedui1[++cnt2][1] = b[i][1],liedui1[cnt2][2] = b[i][2];
        }//两人组，如果有一人组，直接合成三人组；否则进入队列等待一人组
        else if(qo[i] == 1)
        {
            if(cnt2)ans[++cnt][1] = b[i][1],ans[cnt][2] = liedui1[cnt2][1],ans[cnt][3] = liedui1[cnt2][2],cnt2 --;
            else liedui2[++cnt3] = b[i][1];
        }//一人组。如果有两人组直接合成三人组，否则进入队列等待两人组
    }
    while(cnt3 >= 3)ans[++cnt][1] = liedui2[cnt3--],ans[cnt][2] = liedui2[cnt3--],ans[cnt][3] = liedui2[cnt3--];//可以三个一人组合成三人组
    if(cnt != n / 3)cout << -1;//如果没有n/3个三人组，不满足条件
    else
        for(int i = 1;i <= n / 3;i ++)cout << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;//否则输出答案
}
```

---

## 作者：EdenSky (赞：4)

# [CF300B Coach](https://www.luogu.com.cn/problem/CF300B)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/16988472.html)

## 题意
给定 $n$ 个数，保证 $n \mid 3$，要将这 $n$ 个数分配到 $\dfrac{n}{3}$ 个三元组，有 $m$ 个要求 $a,b$，每个要求表示 $a,b$ 要在同一个三元组里，求最后的分组，若无解则输出 `-1`。
## 正文

**准备知识：并查集**

**最坏时间复杂度：$\mathcal{O}(n+m)$**

我们可以利用并查集来处理两个人要在同一组的情况，下面是并查集板子（在下文中，并查集中的每一个区块被称为一棵树）：

```cpp
//板子，不做解释
int ufs[20000];
void init(){
	for(int i=1;i<=n;i++) ufs[i]=i;
}
int fd(int x){
	if(ufs[x]==x)	return x;
	return ufs[x]=fd(ufs[x]);
}
void uoin(int x,int y){
	ufs[fd(x)]=fd(y);
}
```

但这只是第一步，根据题意，当并查集中存在超过 3 个结点的树，那么这是绝对无解的。那么这要怎么弄呢？我们可以开一个 `vector` $S_{i,j}$ 来储存以 $i$ 为根节点的树的节点数 $j$，因此我们得到以下代码：

```cpp
#define pb push_back
vector<vector<int>> s(20000);
for(int i=1;i<=n;i++)	s[fd(i)].pb(i);//插入节点
for(auto &i: s)//判断是否有超过3个节点的树
	if(i.size()>3)	cout<<-1,exit(0);
```

我们还要考虑如何分组，这是蒟蒻的思路，仅供大佬借鉴。经过上面的无解判定，可以保证并查集中剩下的树只有 1 至 3 个节点。而三个节点的树正好是所需的三元组，无需再分。将有 1 个节点和有 2 个节点的树分别装入不同的 `vector` $sj,so$，可以很好地发现，我们只要将 $sj$ 中的某一项和 $so$ 的某一项合并，即可得到一个新的三元组（因为两棵树没有任何要求）。

于是有下面的代码：

```cpp
vector<vector<int>> sj,so,ans;
for(auto &i: s)
	if(i.size()==3)	ans.pb(i);//3个节点的树
	else if(i.size()==2)	so.pb(i);//2个节点的树
	else if(i.size()==1)	sj.pb(i);//1个节点的树
while(!sj.empty()&&!so.empty())
	sj.front().insert(sj.front().begin(),//将so首项插入sj首项末
		so.front().begin(),so.front().end()),
	so.erase(so.begin()),//删去so首项
	ans.pb(sj.front()),//将合并后的sj插入ans末
	sj.erase(sj.begin());//删去sj首项
```

但，这就完了吗？不！

可以看一下第一个样例：`3 0`，没错，如果按照上面的代码，所有节点都会被放入 $sj$ 中而无法合并，因此我们还要在 $sj$ 和 $so$ 合并完后，若 $sj$ 还有残余且数量大于 3，我们可以每三项每三项合并，于是有：

```cpp
while(!sj.empty()&&sj.size()>=3){
	int a,b,c;
	auto i=sj.begin();//得到sj首项
	a=i->front(),i=sj.erase(i),//依次将sj的前三项赋值给a，b，c
	b=i->front(),i=sj.erase(i),
	c=i->front(),i=sj.erase(i);
	ans.push_back({a,b,c});
}
```

当然，如果谨慎些的话，我们还要加上 $sj$ 和 $so$ 的判断，若仍有残余，则无解。（为什么不合并 $so$？因为它合并就超过 3 个节点了。）

```cpp
if(so.size()>0)	cout<<-1,exit(0);
if(sj.size()>0)	cout<<-1,exit(0);

```

最后是输出。

```cpp
for(auto &i: ans){
	for(auto &j: i)
		cout<<j<<' ';
	cout<<'\n';
}
```

完整 CODE：

```cpp
//不注解，前面已做讲解，不懂评论区问/私聊
#include<iostream>
#include<vector>
#define pb push_back
using namespace std;
int ufs[20000],n,m;
vector<vector<int>> s(20000),sj,so,ans;
void init(){
	for(int i=1;i<=n;i++) ufs[i]=i;
}
int fd(int x){
	if(ufs[x]==x)	return x;
	return ufs[x]=fd(ufs[x]);
}
void uoin(int x,int y){
	ufs[fd(x)]=fd(y);
}
int main(){
	cin>>n>>m,init();
	int a,b;
	for(int i=1;i<=m;i++)	cin>>a>>b,uoin(a,b);
	for(int i=1;i<=n;i++)	s[fd(i)].pb(i);
	for(auto &i: s)
		if(i.size()>3)	cout<<-1,exit(0);
		else if(i.size()==3)	ans.pb(i);
		else if(i.size()==2)	so.pb(i);
		else if(i.size()==1)	sj.pb(i);
	while(!sj.empty()&&!so.empty())
		sj.front().insert(sj.front().begin(),
			so.front().begin(),so.front().end()),
		so.erase(so.begin()),
		ans.pb(sj.front()),
		sj.erase(sj.begin());
	if(so.size()>0)	cout<<-1,exit(0);
	while(!sj.empty()&&sj.size()>=3){
		int a,b,c;
		auto i=sj.begin();
		a=i->front(),i=sj.erase(i),
		b=i->front(),i=sj.erase(i),
		c=i->front(),i=sj.erase(i);
		ans.push_back({a,b,c});
	}
	if(sj.size()>0)	cout<<-1,exit(0);
	for(auto &i: ans){
		for(auto &j: i)
			cout<<j<<' ';
		cout<<'\n';
	}
}
```

[提交记录](https://www.luogu.com.cn/record/97449157)，完美结束。

---

## 作者：推翻暴政 (赞：2)

# CF300B Coach 题解

## 题目大意

$n$ 个学生满足 $m$ 条要求，每一条要求使得 $2$ 个学生必须在一个队，一个队 $3$ 个人，问是否存在一种合法分队方案，若存在输出其中一种方案，若不存在输出 $-1$。

## 思路

首先容易想到并查集，初始化每个人都是一个连通块，对于每条要求合并连通块，最后查询每个连通块大小，大小为 $3$ 就直接输出该连通块的所有元素，大小小于 $3$ 就多个连通块凑成元素数量为 $3$ 再输出，大小大于 $3$ 就直接判断无解。

现在难点在于如何凑大小小于 $3$ 的连通块。咱的方法是先遍历每一个大小为 $2$ 的连通块，为每一个匹配一个大小为 $1$ 的连通块，然后每三个大小为 $1$ 的连通块匹配在一起。如果大小为 $2$ 的连通块数量多于大小为 $1$ 的连通块或是匹配完后大小为 $1$ 的连通块不是 $3$ 的倍数咱就直接判断无解。

时间复杂度在处理并查集处为 $O(m\alpha(n))$，在后续匹配都为 $O(n)$，故整体复杂度为 $O(m\alpha(n))$。（虽然这个题 $n\leq48$ 这么优化完全无意义就是了）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=50;
int n,m,fa[MAXN],siz[MAXN];
bool vis[MAXN];
vector<int> c[MAXN],v1,v2,v3;
inline int find(int x){//并查集的查询
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y){//并查集的合并
    x=find(x),y=find(y);
    if(x==y)  return;
    if(siz[x]<siz[y])  swap(x,y);
    fa[y]=x;
    siz[x]+=siz[y];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){//初始化并查集
        fa[i]=i;
        siz[i]=1;
    }
    for(int i=1;i<=m;i++){//处理并查集
        int x,y;
        scanf("%d%d",&x,&y);
        merge(x,y);
    }
    for(int i=1;i<=n;i++){//根据连通块大小分类连通块
        c[fa[i]].push_back(i);
        if(!vis[fa[i]]){
            vis[fa[i]]=1;
            if(siz[fa[i]]==2)  v2.push_back(fa[i]);
            else if(siz[fa[i]]==3)  v3.push_back(fa[i]);
            else if(siz[fa[i]]==1)  v1.push_back(fa[i]);
            else{
                puts("-1");
                return 0;
            }
        }
    }
    if(v2.size()>v1.size()){//大小为 2 的连通块数量多于大小为 1 的连通块则无解
        puts("-1");
        return 0;
    }
    if((v1.size()-v2.size())%3!=0){//匹配完后大小为 1 的连通块不是 3 的倍数则无解
        puts("-1");
        return 0;
    }
    for(int i:v3){//输出大小为 3 的连通块中的元素
        for(int k:c[i]){
            printf("%d ",k);
        }
        puts("");
    }
    for(int i=0;i<v2.size();i++){//匹配大小为 2 和大小为 1 的连通块并输出
        for(int k:c[v2[i]]){
            printf("%d ",k);
        }
        for(int k:c[v1[i]]){
            printf("%d ",k);
        }
        puts("");
    }
    for(int i=v2.size();i<v1.size();i++){//剩余大小为 1 的连通块每三个匹配输出
        for(int k:c[v1[i]]){
            printf("%d ",k);
        }
        i++;
        for(int k:c[v1[i]]){
            printf("%d ",k);
        }
        i++;
        for(int k:c[v1[i]]){
            printf("%d ",k);
        }
        puts("");
    }
    return 0;
}
```



---

## 作者：staygone (赞：2)

拿到这道题，一看到“组”这个字，本人就很敏感地想到了并查集。

**题目分析**

我们可以知道，在比赛之前，学生们必须组队，而且是 $3$ 个 $3$ 个组，然后还有 $m$ 个组队要求，教练必须按照组队要求组队，问可不可以满足以上条件，若可以,输出 $n \div 3$ 个小组，其中包含 $3$ 个成员的编号；若不可以，输出 $-1$ 。

**具体思路**

肯定在输入组队要求时，根据要求把两人放进同一个并查集里面，同时判断当前并查集的总人数是否大于 $3$ ，如果大于则不满足条件，输出 $-1$ 。

把每个人放入对应的并查集后，我们就应该考虑那些没有要求的人了，首先为了能更好的满足条件，我们应该先去拿没有要求的人去填充 $2$ 人小组，再去填充 $1$ 人小组。最后再判断一下是否符合条件就行了。

具体思路就是这样，让我们来看一下详细代码吧。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int flag[20005]; 
int size[10005]; // 并查集内节点个数 
int fa[10005]; // fa[x] = y 表示 y 是 x 的 father（把 x 接到 y 上） 
int Find_Set (int x) {
	if (fa[x] == x) return x;
	else return fa[x] = Find_Set (fa[x]);
}
void Union_Set (int x, int y) {
	int a = Find_Set (x);
	int b = Find_Set (y);
	if (a != b) {
		fa[a] = b;
		size[b] += size[a];
	}
}
int main () {
//	freopen ("coach.in", "r", stdin);
//	freopen ("coach.out","w",stdout);
	cin >> n >> m;
	for (int i = 1; i <= n + 5; i ++) {
		fa[i] = i;
		size[i] = 1;
	}
	// 初始化（MakeSet） 
	for (int i = 1; i <= m; i ++) {
		int a, b;
		scanf ("%d %d", &a, &b);
		Union_Set (a, b); // 加入并查集 
		if (size[Find_Set(b)] > 3) {
			puts ("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i ++) 
		if (size[Find_Set(i)] == 2)  // 两人 
			for (int j = 1; j <= n; j ++) 
				if (size[Find_Set(j)] == 1) { // 一人 
					Union_Set (i, j);
					break;
				}
	// 两人的填充完，还剩一人的 
	for (int i = 1; i <= n; i ++) 
		if (size[Find_Set(i)] == 1) 
			for(int j = i + 1; j <= n; j ++) {
				if (size[Find_Set(j)] == 1) Union_Set (i, j); // 继续 
				if (size[Find_Set(i)] == 3) break; // 填充完 
			}
	for (int i = 1; i <= n; i ++) 
		if (size[Find_Set(i)] != 3) {
			puts ("-1");
			return 0;
		} 
	// 判断条件 
	for (int i = 1; i <= n; i ++)
		if (flag[i] == 0) {
			printf ("%d ", i);
			for (int j = i + 1;j <= n; ++j)
				if (Find_Set (i) == Find_Set(j) && flag[j] == 0) {
					printf ("%d ", j);
					flag[j] = 1;
				}
			puts ("");
		}
	// 输出 
}
```


---

## 作者：Oscar12345 (赞：2)

[题目地址](http://codeforces.com/problemset/problem/300/B)

A programming coach has n students to teach. We know that n is divisible by 3. Let's assume that all students are numbered from 1 to n, inclusive.

Before the university programming championship the coach wants to split all students into groups of three. For some pairs of students we know that they want to be on the same team. Besides, if the i-th student wants to be on the same team with the j-th one, then the j-th student wants to be on the same team with the i-th one. The coach wants the teams to show good results, so he wants the following condition to hold: if the i-th student wants to be on the same team with the j-th, then the i-th and the j-th students must be on the same team. Also, it is obvious that each student must be on exactly one team.

Help the coach and divide the teams the way he wants.

Input
The first line of the input contains integers n and m (3 ≤ n ≤ 48, . Then follow m lines, each contains a pair of integers ai, bi (1 ≤ ai < bi ≤ n) — the pair ai, bi means that students with numbers ai and bi want to be on the same team.

It is guaranteed that n is divisible by 3. It is guaranteed that each pair ai, bioccurs in the input at most once.

Output
If the required division into teams doesn't exist, print number -1. Otherwise, print  lines. In each line print three integers xi, yi, zi (1 ≤ xi, yi, zi ≤ n) — the i-th team.

If there are multiple answers, you are allowed to print any of them.

Example
Input
3 0
Output
3 2 1 
Input
6 4
1 2
2 3
3 4
5 6
Output
-1
Input
3 3
1 2
2 3
1 3
Output
3 2 1 

题目翻译：现在有n个人和m组关系（意思就是这两个人必须在一组），现在问你可不可以在满足这m组关系的情况下将他们分成n/3组（题目保证n可以被3整除）

解法：一共有两种，本人是第二种，第一种是网上大佬的。
解法一：并查集（真是一个好东西）
用到并查集。关于并查集的博客，我看了几个，觉得最通俗易懂的还是这个博客：[并查集-简单易懂](http://www.xluos.com/index.php/archives/606)。并查集确定每组人的个数和代表。然后遍历，如果出现个数超过三个的组，就直接输出-1，都小于等于3的话，接下来考虑2个的组个数是否大于一个的，因为2个人的组肯定要和一个人的组搭档，超出的话就肯定不满足条件了，剩下的情况就都是满足条件的。 

AC代码现场奉上：
```
#include<stdio.h>
//rang[i] 以i为代表的组人的个数 flag[i]表示第i个是否被输出过 pre[i]第i个的代表
int pre[100], rank[100],flag[100];
void unite(int x, int y);
int find(int x);
int main()
{
    int n, m,i,a,b,j,s=0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
    {
        pre[i] = i;
        rank[i] = 1;
        flag[i] = 1;
    }
    for (i = 0; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        unite(a, b);
    }
    int x = 0, y = 0;
    for (i = 1; i <= n; ++i)
    {
        if (find(i) == i)
        {
            if (rank[i] > 3) {
                printf("-1\n");
                return 0;
            }
            else if (rank[i] == 2)x++;
            else if (rank[i] == 1)y++;
        }
    }
    if (x > y) {
        printf("-1\n");
        return 0;
    }
    for (i = 1; i <= n; i++)
    {
        if (rank[i] == 3) 
        {
            printf("%d ", i);
            s++;
            flag[i] = 0;
            for (j = 1; j <= n; j++)
            {
                if (find(j) == i&&flag[j])
                {
                    s++;
                    if(s!=3)
                    printf("%d ", j);
                    else printf("%d\n", j);
                    flag[j] = 0;
                }
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (rank[i] == 2)
        {
            printf("%d ", i);
            flag[i] = 0;
            for (j = 1; j <= n; j++)
            {
                if (find(j) == i&&flag[j])
                {
                    printf("%d ", j);
                    flag[j] = 0;
                }
            }
            for(j=1;i<=n;j++)
                if (find(j) == j&&rank[j]==1&&flag[j])
                {
                    printf("%d\n", j);
                    flag[j] = 0;
                    break;
                }
        }
    }
    j = 0;
    for (i = 1; i <= n; ++i)
    {
        if (find(i) == i&&rank[i] == 1 && flag[i])
        {
            if (j != 2)
            {
                printf("%d ", i);
                j++;
            }
            else
            {
                j = 0;
                printf("%d\n", i);
            }
        }
    }
    return 0;
}
//合并函数  两组合并 人数少的合并到多的 成为人数多的子树
void unite(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        if (rank[fx] >=rank[fy])
        {
            pre[fy] = fx;
            rank[fx] += rank[fy];
        }
        else
        {
            pre[fx] = fy;
            rank[fy] += rank[fx];
        }
    }
}
//查找函数
int find(int x)
{
    if (pre[x] != x)
        pre[x] = find(pre[x]);  //压缩路径 一个组内的直接指向代表
    return pre[x];
}
```

解法二：（我也不知道是什么算法，~~也许乱搞出了奇迹？！~~ ）
  我的思路是

 1：先选出可以3个人相互组队的（就是三个人相互喜欢的），存在结构体out中；

 2：然后选出只有两个人相互喜欢的，然后把那些没有提及想和谁一队的人看成是和谁组队都行的人。再对他们进行组队。

 3：然后剩下和谁组队都行的人（就是2中我们标注的），对他们进行组队。

 依次进行玩以上的步骤后，发现AC不了，其实这就是这道题的坑点，如果存在一个人想和两个以上的人组队，那么直接输出-1。

注释：这个不是正解，纯粹乱搞，可能是数据比较水才AC

代码：
```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
int vis[50];
int g[50][50];
int used[50];
set<int> pp;
struct node{
  int x;
  int y;
  int z;
};
node out[50];
int cishu[50];
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF)
    {
        memset(vis, 0,sizeof(vis));
        memset(g   , 0,sizeof(g));
        memset(used, 0,sizeof(used));
        memset(cishu, 0,sizeof(cishu));
        int a,b;
        for(int i=1; i<=m; i++)
        {
            scanf("%d %d",&a,&b);
            vis[a] = vis[b] = 1;
            cishu[a]++;
            cishu[b]++;
            g[a][b] = g[b][a]=1;
        }
        int flag = 1;
        for(int i=1; i<=n; i++)
        {
          if(cishu[i] > 2){flag=0;break;}
        }
        if(flag==0){printf("-1\n");continue;}
        int w = 0;
        for(int i=1; i<=n; i++)
        {
           if(!(used[i]==0&&vis[i]==1))continue;
           for(int j=i+1; j<=n; j++)
           {
              if(g[i][j]==0) continue;
              if(!(used[j]==0&&vis[j]==1))continue;
              for(int k=j+1; k<=n; k++)
              {
                  if(!(used[k]==0&&vis[k]==1))continue;
                  if(g[i][k]==1&&g[j][k]==1){used[i]=used[j]=used[k]=1;++w;out[w].x=i;out[w].y=j;out[w].z=k;break;}
              }
              if(used[j]==1)break;
            }
        }
        if(w<n/3)
        for(int i=1; i<=n; i++)
        {
            if(!(vis[i]==1&&used[i]==0))continue;
            for(int j=1; j<=n; j++)
            {
              if(i==j)continue;
              if(!(vis[j]==1&&used[j]==0))continue;
              if(g[i][j]==0)continue;
              for(int k=1; k<=n; k++)
              {
                  if(i==j || i==k)continue;
                  if(vis[k]==0&&used[k]==0)
                  {used[i]=used[j]=used[k]=1;++w;out[w].x=i;out[w].y=j;out[w].z=k;break;}
              }
            }
        }
        int ko = 0;
        if(w<n/3)
        {
            pp.clear();
            for(int i=1; i<=n; i++)
            {
                if(vis[i]==0&&used[i]==0){pp.insert(i);}
            }
            ko = pp.size()/3;
        }
        if(w+ko<n/3)printf("-1\n");
        else
        {
            for(int i=1; i<=w; i++)
            {
                printf("%d %d %d\n",out[i].x, out[i].y, out[i].z);
            }
           for(set<int>::iterator it=pp.begin(); it!=pp.end(); ++it)
           {
               cout << *it << " "; ++it;
               cout << *it << " "; ++it;
               cout << *it << endl;
           }
        }
     }
   return 0;
}

```
ok，就酱。

---

## 作者：MINECRAFT_eternal (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF300B)
这道题是一道并查集。

首先，这道题只需要并查集的基础操作（初始化，查询，合并）。

------------
### 题目分析
按照并查集的基础操作，首先我们需要将两个想组队的 ~~蒟蒻~~ 合并到一个小组里：
```cpp
void unionset(int x,int y){
	father[y]=x;
   r[x]+=r[y];     //别忘了累加人数
}     //合并两个学生到一个集合
```

当然，如果集合内有超过三名成员就不能满足要求，所以我们还需要加 ~~亿~~ 些判断：
```cpp
for(int i=1;i<=m;i++){
	scanf("%d%d",&a,&b);
	int x=findset(a),y=findset(b);
	if(x!=y){
		if(r[x]+r[y]>3){     //超员了
			printf("-1");     //无法满足要求
			return 0;
		}
		unionset(x,y);      //合并
	}
}
```
于是就有了上面这段代码。

至于其它并查集的基础操作（初始化，查询，合并等），直接套模板就可以了（虽然这道题并不是模板题）。

# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b;
int father[2000];
int r[2000];
bool f[2000]={0};
for(int i=1;i<=x;i++){
	father[i]=i;
	r[i]=1;
}    //并查集初始化
int findset(int x){
	if(father[x]==x)
	  return x;
	else
	  return father[x]=findset(father[x]);
}     //并查集查询
void unionset(int x,int y){
	father[y]=x;
   r[x]+=r[y];
}     //并查集合并
int main(){
	scanf("%d%d",&n,&m);
	makeset(n);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		int x=findset(a),y=findset(b);
		if(x!=y){
			if(r[x]+r[y]>3){     //人满了
				printf("-1");     //不能满足要求
				return 0;
			}
			unionset(x,y);     //没满就合并
		}
	}
   //接下来是一大段处理输出（高能！）
   /*
   输出分两种情况处理：
   第一种是有没有组到三个人的队伍；
   第二种是组满了三个人的队伍。
   至于没有在输入中提及的人，则自动补到没有组满的队伍中。
   */
	int cnt=0,c=0;
	for(int i=1;i<=n;i++){
		if(f[i]==1||r[findset(i)]==1)
		  continue;
		f[i]=1;
		c++;
		if(r[findset(i)]==2){
			int k1=0,k2=0,s=0;
			for(int j=1;j<=n;j++){
				if(s==2)
				  break;
				if(k1==0&&f[j]==0&&i!=j&&r[findset(j)]==1){
					f[j]=1;
					k1++;
					s++;
					c++;
				}
				if(k2==0&&f[j]==0&&i!=j&&findset(i)==findset(j)){
					f[j]=1;
					k2++;
					s++;
					c++;
				}
			}
		}
		if(r[findset(i)]==3){
			int s=0;
			for(int j=1;j<=n;j++){
				if(s==2)
				  break;
				if(f[j]==0&&i!=j&&findset(i)==findset(j)){
					f[j]=1;
					s++;
					c++;
				}
			}
		}
		if(cnt==n)
		  break;
		cnt+=3;
		if(c<3){
			printf("-1");
			return 0;
		}
		c=0;
	}
	memset(f,0,sizeof(f));     //亲身经历：OIer们别忘了初始化
	cnt=0;
	for(int i=1;i<=n;i++){
		if(f[i]==1||r[findset(i)]==1)
		  continue;
		printf("%d ",i);
		f[i]=1;
		if(r[findset(i)]==2){
			int k1=0,k2=0,s=0;
			for(int j=1;j<=n;j++){
				if(s==2)
				  break;
				if(k1==0&&f[j]==0&&i!=j&&r[findset(j)]==1){
					f[j]=1;
					printf("%d ",j);
					k1++;
					s++;
				}
				if(k2==0&&f[j]==0&&i!=j&&findset(i)==findset(j)){
					f[j]=1;
					printf("%d ",j);
					k2++;
					s++;
				}
			}
			cnt+=3;
			printf("\n");
		}
		if(r[findset(i)]==3){
			int s=0;
			for(int j=1;j<=n;j++){
				if(s==2)
				  break;
				if(f[j]==0&&i!=j&&findset(i)==findset(j)){
					f[j]=1;
					printf("%d ",j);
					s++;
				}
			}
			cnt+=3;
			printf("\n");
		}
		if(cnt==n)
		  break;
	}
	c=0;
	for(int i=1;i<=n;i++){
		if(f[i]==0){
			printf("%d ",i);
			c++;
		}
		if(c==3){
			printf("\n");
			c=0;
		}
	}     //一轮输出终于结束了
	return 0;
}
```

---

## 作者：Sakuya_maid (赞：0)

# CF300B Coach题解


题意想必都是了解的了，那么我直接给出我的思路了
 

思路：


1：暴力建边处理，将同学的需求转化为建边

```c
    for(int i = 1; i <= m; ++ i)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
        vis[u] = true;
        vis[v] = true;
    }
```


2：处理哪些同学没需求

```c
     memset(vis, 0, sizeof vis);

     for(int i = 1; i <= m; ++ i)
     {
         int u, v;
         cin >> u >> v;
         g[u].push_back(v), g[v].push_back(u);
         vis[u] = true;
         vis[v] = true;
     }

     for(int i = 1; i <= n; ++ i)
     if(!vis[i])c[++ hh] = i;
```



3：处理各个连通块，处理出每个连通块又哪些同学

```c
    memset(st, 0, sizeof st);

    for(int i = 1; i <= n; ++ i)
    {
        if(vis[i] && !st[i])
        {
            ++ cnt;  
            dfs(i, cnt);
        }
    }
                     
    void dfs(int u, int cnt)
    {
    	st[u] = true;
    	ans[cnt].push_back(u);

      for(auto v : g[u])
      {
          if(!st[v])
          {
              dfs(v, cnt);
          }
      }
    }
```



4：发现当前连通块大小如果>3则直接输出no

```c
    bool flag = true;

    for(int i = 1; i <= cnt; ++ i)
    {
        if(ans[i].size() > 3)flag = false;
    }

    if(!flag || cnt > n / 3)
    {
        cout << -1 << '\n';
        return;
    }
```
5：先处理各个连通块分组，如果只有两个一组就从前面没有跟别人建边的孤点同学取一个，三个的话刚好输出，如果连通块遍历完了，就全部从孤点同学取

```c
    int j = 1;

    for(int i = 1; i <= n / 3; ++ i)
    {
        int res = 0;
        
        if(j <= cnt)
        {
            for(auto v : ans[j])
            {
                res ++;
                cout << v << ' ';
            }
            ++ j;
        }

        if(res == 3)cout << '\n';
        else
        {
            while(res < 3)
            {
                cout << c[hh] << ' ';
                hh --;
                res ++;
            }
            cout << '\n';
        }
    }
```
完整代码：

```c
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 2e5 + 5, mod = 998244353;

vector<int>g[N], v;

bool vis[N], st[N];

int n, m, hh, cnt;

vector<int>ans[N];

int c[N];

void dfs(int u, int cnt)
{
    st[u] = true;
    ans[cnt].push_back(u);

    for(auto v : g[u])
    {
        if(!st[v])
        {
            dfs(v, cnt);
        }
    }
}

void Sakuya()
{
    cin >> n >> m;

    cnt = 0;

    memset(vis, 0, sizeof vis);
    memset(st, 0, sizeof st);

    for(int i = 1; i <= m; ++ i)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
        vis[u] = true;
        vis[v] = true;
    }

    for(int i = 1; i <= n; ++ i)
    if(!vis[i])c[++ hh] = i;
    
    for(int i = 1; i <= n; ++ i)
    {
        if(vis[i] && !st[i])
        {
            ++ cnt;  
            dfs(i, cnt);
        }
    }

    bool flag = true;

    for(int i = 1; i <= cnt; ++ i)
    {
        if(ans[i].size() > 3)flag = false;
    }

    if(!flag || cnt > n / 3)
    {
        cout << -1 << '\n';
        return;
    }

    int j = 1;

    for(int i = 1; i <= n / 3; ++ i)
    {
        int res = 0;
        
        if(j <= cnt)
        {
            for(auto v : ans[j])
            {
                res ++;
                cout << v << ' ';
            }
            ++ j;
        }

        if(res == 3)cout << '\n';
        else
        {
            while(res < 3)
            {
                cout << c[hh] << ' ';
                hh --;
                res ++;
            }
            cout << '\n';
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int T;
    // for (cin >> T; T -- ; )
        Sakuya();

}
```

[提交链接](https://codeforces.com/contest/300/submission/226159477)
谢谢各位巨佬观看本蒟蒻的第一篇题解：）



---

## 作者：封禁用户 (赞：0)

## 题目描述

[Coach](https://www.luogu.com.cn/problem/CF300B)

### 注意事项

本题用了并查集，不会的同学先看看[这个](https://blog.csdn.net/weixin_38279101/article/details/112546053)。

## 算法思路

#### 算法：并查集

先用并查集确定每组人的个数和领头人。然后遍历，如果某组人数大于 $3$，就输出 $-1$。否则考虑每个人是不是没分配而且还能增加组数，就把这个人加入新的组中，然后把好友也加入组中。如果某一组的人数少于 $3$，就把没加入组的人加入这组，最后输出即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
struct st
{
	ll now,len;//now记录值，len记录长度 
	bool operator < (const st &u)const//重载运算符 
	{
		return now<u.now;
	}
};
const ll N=100010;
ll n,m,power[N],tmp,l,r,ans;
st a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	power[0]=1;
	for(int i=1;i<=18;i++)//求10的幂次 
	{
		power[i]=power[i-1]*10;
	}
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].now;
		tmp=a[i].now;
		while(tmp)//求长度 
		{
			a[i].len++;
			tmp/=10;
		}
	}
	sort(a+1,a+n+1);//sort排序 
	l=1;
	r=n;
	while(l<r)//双指针two-pointer 
	{
		tmp=a[l].now*power[a[r].len]+a[r].now;//合并 
		if(tmp<m)//可行 
		{
			ans+=r-l;//答案加上 
			l++;
		}
		else//不可行 
		{
			r--;
		}
	}
	l=1;
	r=n;
	while(l<r)//反正再做一遍 
	{
		tmp=a[r].now*power[a[l].len]+a[l].now;
		if(tmp<=m)
		{
			ans+=r-l;
			l++;
		}
		else
		{
			r--;
		}
	}
	cout<<ans<<"\n";//输出
	return 0;
}
```

---

## 作者：Limury (赞：0)

###  基本思路

首先看题，教练想把所有学生分成三人一队。看到一队，就想到了用并查集来维护。如果用并查集，只需将每组意愿的人放入并查集，然后判断人数，就能完成此题。

###  具体思路

我们可以定义一个数组，表示此并查集的成员个数。在初始化并查集时要将这个数组置为一，因为开始时每个并查集中只有它本身。

在合并两并查集时，我们就不仅要将一并查集树根接在另一树根上，还要将新树根加上原树的成员个数，这样就求到了新树的成员数。

在处理完合并后，也就是判断没有任何要求的同学时，就可枚举每一并查集，如个数不满三，就可把没有任何要求的同学加入此并查集中。

最后，一层循环枚举每一并查集，存储下成员数是三的并查集个数判断就可以了。

###  完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[100005],si[100005];
bool f[100005];

void MakeSet(int n){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        si[i]=1;
    }
}

int FindSet(int a){
    if (fa[a]==a){
        return a;
    } else {
        return fa[a]=FindSet(fa[a]);
    }
}

void UnionSet(int a,int b){
    int l=FindSet(a),r=FindSet(b);
    if(l==r){
        return;
    }
    fa[l]=r;
    si[r]+=si[l];
}

int main(){
    scanf("%d%d",&n,&m);
    int a,b;
    MakeSet(n);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        UnionSet(a,b);
        if(si[FindSet(b)]>3){
            puts("-1");
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(si[FindSet(i)]==2){
            for(int j=1;j<=n;j++){
                if(si[FindSet(j)]==1){
                    UnionSet(i,j);
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(si[FindSet(i)]==1){
            for(int j=i+1;j<=n;j++){
                if(si[FindSet(j)]==1){
                    UnionSet(i,j);
                }
                if(si[FindSet(i)]==3){
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(si[FindSet(i)]!=3){
            puts("-1");
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(!f[i]){
            printf("%d ",i);
            for(int j=i+1;j<=n;j++){
                if(FindSet(i)==FindSet(j)&&!f[j]){
                    printf("%d ",j);
                    f[j]=1;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
```




---

