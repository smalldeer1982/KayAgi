# Rochambeau

## 题目描述

$N$ 个小朋友（编号为 $0,1,2,…,N−1$）一起玩石头剪子布游戏。

其中一人为裁判，其余的人被分为三个组（有可能有一些组是空的），第一个组的小朋友只能出石头，第二个组的小朋友只能出剪子，第三个组的小朋友只能出布，而裁判可以使用任意手势。

你不知道谁是裁判，也不知道小朋友们是怎么分组的。

然后，孩子们开始玩游戏，游戏一共进行 $M$
 轮，每轮从 $N$ 个小朋友中选出两个小朋友进行猜拳。

你将被告知两个小朋友猜拳的胜负结果，但是你不会被告知两个小朋友具体使用了哪种手势。

比赛结束后，你能根据这些结果推断出裁判是谁吗？

如果可以的话，你最早在第几轮可以找到裁判？

## 说明/提示

$1 \le N \le 500$，$1 \le M \le 2000$。

## 样例 #1

### 输入

```
3 3
0<1
1<2
2<0
3 5
0<1
0>1
1<2
1>2
0<2
4 4
0<1
0>1
2<3
2>3
1 0```

### 输出

```
Can not determine
Player 1 can be determined to be the judge after 4 lines
Impossible
Player 0 can be determined to be the judge after 0 lines
```

# 题解

## 作者：lym2022 (赞：11)

### 思路
本题的每个小朋友都有三种情况，要么是石头要么是剪刀要么是布，并且石头赢剪刀，剪刀赢布，布赢石头，和[食物链](https://www.luogu.com.cn/problem/P2024)中的 A 吃 B，B 吃 C，C 吃 A 十分相似，考虑用扩展域并查集，开三倍大小的并查集维护每个小朋友的情况。

每一局中都有一位裁判，枚举裁判是谁，将当前枚举的裁判设为 $p$，裁判可以出任意的手势，赢输平局都有可能，所以包含 $p$ 的这一局就没有任何意义了，
#### 所以在枚举裁判时，只要这局中包含 $p$ 就忽略这一对局，
如果遍历完所有对局，发现对局的情况与并查集中记录的情况不符，那么就证明 $p$ 不是裁判。

在枚举时统计一个合法裁判数量 $sum$，枚举完所有 $p$ 时：

如果 $sum$ 等于 $0$，就说明每一个人都不是合法裁判。

如果 $sum$ 等于 $1$，就说明裁判是唯一的，可以确定谁是裁判，如何寻找确定裁判的最小轮次呢，可以在每次枚举时，统计推出矛盾的时间，最大值就是可以确定裁判的最小轮次。

如果 $sum$ 大于 $1$，就说明合法裁判不止一个。

在读入关系时，可以将 $a$ 输给了 $b$ 转化为 $b$ 赢了 $a$，这样就只有两种情况了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e3 + 5;

int n,m,fa[N];    // 1 到 n 是一类，n + 1 到 n * 2 是一类，n * 2 + 1 到 n * 3 是一类 

struct node {
	int x,y,op;    //x，y 是两个小朋友的编号，op 记录是赢还是平 
};

node a[N];   //记录每一条关系 

int find(int x) {       //并查集模板 
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void unionn(int x,int y) {
	x = find(x);
	y = find(y);
	if(x == y) return;
	fa[x] = y; 
}

void solve() {
	for(int i = 1;i<=m;i++) {
		char c;
		cin >> a[i].x >> c >> a[i].y;
		if(c == '<') {
			a[i].op = 1;          //转化关系 
			swap(a[i].x,a[i].y);
		}
		if(c == '=') a[i].op = 2; //op 是 2 代表平 
		if(c == '>') a[i].op = 1; //op 是 1 代表赢 
	}
	int player = 0,round = 0,sum = 0;  //player 记录合法裁判是谁，round 记录最小轮次，sum 记录有几个合法裁判 
	for(int p = 0;p<n;p++) {        //枚举当前裁判 
		for(int i = 0;i<=3*n;i++) fa[i] = i; //初始化 
		int flag = true;
		for(int i = 1;i<=m;i++) {   //遍历每一条条件 
			if(a[i].x == p || a[i].y == p) continue;   //包含裁判就跳过 
			if(a[i].op == 1) {         //如果是赢 
				if(find(a[i].x) == find(a[i].y) || find(a[i].x) == find(a[i].y+n)) {   //判断是否矛盾 
					round = max(round,i);   //记录轮次 
					flag = false;   //当前裁判不成立 
					break;  //矛盾就不用看后面了，直接枚举下一个裁判 
				}else {
					unionn(a[i].x+n,a[i].y);     //不矛盾就说明 a[i].x > a[i].y，和食物链那道题一样记录 
					unionn(a[i].x,a[i].y+2*n);
					unionn(a[i].x+2*n,a[i].y+n);
				}
			}else {    //如果平局 
				if(find(a[i].x) == find(a[i].y+n) || find(a[i].x+n) == find(a[i].y)) {   //判断是否矛盾 
					round = max(round,i); 
					flag = false;
					break;
				}else {
					unionn(a[i].x,a[i].y);    //说明当前两个同类
					unionn(a[i].x+n,a[i].y+n);
					unionn(a[i].x+2*n,a[i].y+2*n);
				}
			}
		}
		if(flag) {   //如果当前裁判成立 
			sum++;   //合法裁判数 + 1 
			player = p;  //记录合法裁判 
		}
	}
	if(sum == 0) cout << "Impossible\n";   //没有合法裁判 
	if(sum == 1) cout << "Player " << player << " can be determined to be the judge after " << round << " lines\n";  //只有 1 个合法裁判 
	if(sum > 1) cout << "Can not determine\n";    //有多个合法裁判 
}

int main() {
	ios::sync_with_stdio(false);  //优化输入 
	cin.tie(0);
	while(cin >> n >> m) solve();
	return 0;
} 
```
如果对你有帮助就点个赞吧 owo。

---

## 作者：Jerrycyx (赞：10)

## 思路

根据题面，由于裁判可以随便出招，所以若 $p$ 是~~作弊者~~裁判，所以关于 $p$ 的所有对局都没有意义，无法得到任何有效信息。那么，**如果确定 $p$ 为裁判，则关于 $p$ 的所有对局都可以忽略**。

因此，~~再根据 $\sout{N \le 500}$ 的数据~~，可以考虑枚举裁判 $p$。根据题意，没有裁判的时候所有对局都应当是合法的，所以**在忽略与 $p$ 相关的所有对局以后，若还能发现不合法的对局，则在此时可证明 $p$ 不是裁判**。

枚举所有的 $p$ 以后，若合法的裁判数量为 $0$，即没有合法的裁判，不可能完成所有对局，输出 `Impossible`。

如果合法的裁判数量大于 $1$，此时无法确定裁判到底是谁，输出 `Can not determine`。

如果合法的裁判数量刚好为 $1$，此时有且仅有一个人可能是裁判，输出 `Player x can be determined to be the judge after y lines`，$x$ 为这个合法的裁判，$y$ 为确定这个合法裁判所需的最小游戏轮数，其求法会在接下来讲到。

如何确定唯一的合法裁判？很明显，当你**排除掉其他所有人选**以后，这个唯一合法裁判自然就确定了。所以，**确定唯一合法裁判所需最小游戏轮数就是证明最后一个人不是裁判的时间**。

## 算法

首先读入所有数据并储存。

枚举每一个 $p \in [1,n]$。对于每一个 $p$，依次扫描所有对局，若对局双方有 $p$，则直接跳过 ~~（作弊者打的比赛不算数）~~。

对于每一个对局，如果为 `a>b`，那么 `swap(a,b)`，把它转为 `a<b`。这样，对局就只剩下 `a=b` 和 `a<b`。

本题中小朋友被分为 $A, B, C$ 三部分，其中 $A<B, B<C, C<A$，和 [P2024 食物链](https://www.luogu.com.cn/problem/P2024) 中的“$A$ 吃 $B$，$B$ 吃 $C$，$C$ 吃 $A$”很像，所以可以**开一个三倍大小的种类并查集**来维护三部分之间的关系。

`a=b` 和 `a<b` 可以类比 [P2024 食物链](https://www.luogu.com.cn/problem/P2024) 中的“$x,y$ 时同类”和“$x$ 吃 $y$”两种情况，用种类并查集的敌对和朋友关系维护并判断矛盾。

一旦发现矛盾，证明 $p$ 不是裁判，记录发生矛盾的时间。

如果扫完所有对局以后还没有发现矛盾，$p$ 就是一个合法的裁判，累加裁判数量并记录 $p$ 以备输出所用。

枚举完所有的 $p$ 以后，

+ 如果裁判数量等于 $0$，输出 `Impossible`
+ 如果裁判数量等于 $1$，输出 `Player x can be determined to be the judge after y lines`，其中 $x$ 为刚才记录的 $p$，$y$ 为**所有发生矛盾时间的最大值**
+ 如果裁判数量大于 $1$，输出 `Can not determine`

## AC 代码（附注释）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=505,M=2005;
int n,m;
struct Peter{
	int p1,p2;
	int res; //0表示p1=p2; 1表示p1<p2; 3表示p1>p2;
}game[M];

int ufa[N*3]; //并查集模板，注意开空间和初始化时是三倍 
inline void uInit()
{
	for(int i=1;i<=n*3;i++)
		ufa[i]=i;
	return;
}
int uget(const int x)
{
	if(ufa[x]==x) return x;
	else return ufa[x]=uget(ufa[x]);
}
inline void umerge(const int x,const int y)
{
	ufa[uget(y)]=uget(x);
	return;
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=m;i++) //记录所有的对局 
		{
			int x,y; char op;
			scanf("%d%c%d",&x,&op,&y);
			if(op=='=') game[i]={x,y,0};
			if(op=='<') game[i]={x,y,1};
			if(op=='>') game[i]={x,y,2};
		}
		uInit();
		int possible_judge=0,judge=0,last=0;
		for(int p=1;p<=n;p++)
		{
			uInit();
			int contract=0x3f3f3f3f;
			for(int i=1;i<=m;i++)
			{
				int x=game[i].p1+1,y=game[i].p2+1,res=game[i].res;
				if(x==p||y==p) continue; //忽略带有 p 的对局 
				if(res==2) swap(x,y); //x>y 转 x<y 
				if(res==0) //x=y
				{
					if(uget(x)==uget(y+n)||uget(x+n)==uget(y)) contract=min(contract,i); //记录矛盾发生时间，下同 
					else if(uget(x+n)==uget(y+n+n)||uget(x+n+n)==uget(y+n)) contract=min(contract,i);
					else if(uget(x+n+n)==uget(y)||uget(x)==uget(y+n+n)) contract=min(contract,i);
					else umerge(x,y),umerge(x+n,y+n),umerge(x+n+n,y+n+n);
				}
				else //x<y
				{
					if(uget(x)==uget(y)||uget(x+n)==uget(y+n)||uget(x+n+n)==uget(y+n+n)) contract=min(contract,i);
					else if(uget(x+n)==uget(y)||uget(x+n+n)==uget(y+n)||uget(x)==uget(y+n+n)) contract=min(contract,i);
					else umerge(x,y+n),umerge(x+n,y+n+n),umerge(x+n+n,y);
				}
			}
			if(contract==0x3f3f3f3f) possible_judge++,judge=p; //未发现矛盾 
			else last=max(last,contract); //发现矛盾 
		}
		if(possible_judge==0) printf("Impossible\n");
		else if(possible_judge==1) printf("Player %d can be determined to be the judge after %d lines\n",judge-1,last);
		else printf("Can not determine\n");
	}
}
```

---

## 作者：LiJunze0501 (赞：4)

# 涉及知识点
枚举，种类并查集。
# 细节
## 声明
下面内容会出现以下变量，在此做出解释。  
- $p$：枚举每个成员，$p\in [0,n-1]$。
- $k$：即原题中的 $m$，输入的条件个数。
- $i$（特指枚举部分）：枚举每个条件，$i\in [1,k]$。
- $md$：“矛盾”拼音首字母，每次循环开始时初值为 2001（或更大）。记录一次循环中是什么时候排除 $p$ 当裁判的情况的。
- $amd$：所有矛盾，初值为 0。在所有条件判断完后，如果有矛盾，$amd$ 更新为 $amd$ 和 $md$ 的更大值，看**最晚**排除的裁判是什么时候排除的。如果 $p$ 中只有一个裁判合法，那么输出最晚排除的裁判排除的时间，即 $amd$。
- $caipan$：裁判个数。
- $cp$：“裁判”拼音首字母，记录谁可以是裁判。
- $rlt$：数组，记录种类。
## 枚举
- 第一重枚举：枚举 $p$。  
假如 $p$ 为裁判，那么所有和 $p$ 有关的所有记录都可以不进行判断（假如裁判对战出石头那一组（也可以是其他组），那么 ta 出石头、剪刀、布的结果分别是平、输、赢，是不确定的），所以要判断其他条件是否矛盾，这是**种类并查集**的工作，下面会说。
- 第二重枚举：枚举 $i$。  
通过并查集判断是否有矛盾，循环到 $i$ 时出现矛盾，$md$ 取 $i$ 和 $md$ 的更小值，循环结束后，如果有矛盾，$amd$ 更新为 $amd$ 和 $md$ 的更大值。
- 代码（去除并查集部分）。
```cpp
cp=0,caipan=0,amd=0;
for(int p=0;p<n;p++){
	md=2001;
	//并查集
	//并查集
	for(int i=1;i<=k;i++){
		int d=gx[i].f,x=gx[i].a,y=gx[i].b;
		if(x==p||y==p) continue;//跳过有裁判的条件
		//并查集
		//并查集条件
			if(/*并查集*/){
				md=min(md,i);
				continue;
			}
		//并查集
	}
	if(md==2001) caipan++,cp=p;
	else amd=max(amd,md);
}
```
## 种类并查集
用一个数组记录每个成员的种类，那么这道题用 3 个种类记录，那么首先就是要判断条件是否合法。  
这道题目我们设置的是 2 赢 1，1 赢 0，0 赢 2。那么这里的判断时就可以这么写 `(rlt[y]-rlt[x]+3)%3!=d`，分析如下：
- 如果相同，$(0+3)\bmod 3=3\bmod3=0$，条件对应的 $f$ 也是 0。
- 如果不相同，$(2-1+3)\bmod 3=(1-0+3)\bmod 3=(0-2+3)\bmod 3=1\bmod3=1$，条件对应的 $f$ 也是 1。

相反的就要记录矛盾，如上枚举的部分。
- 代码  
补充枚举部分的代码。
```cpp
int find(int x){
	if(fa[x]==x) return x;
	else{
		int c=find(fa[x]);
		rlt[x]=(rlt[x]+rlt[fa[x]])%3;
		return fa[x]=c;
	}
}
void uni(int x,int y,int rx,int ry,int d){
	rlt[ry]=(rlt[x]-rlt[y]+d+3)%3;
	fa[ry]=rx;
}
//下面是主函数部分
cp=0,caipan=0,amd=0;
for(int p=0;p<n;p++){
	md=2001;
	memset(rlt,0,sizeof(rlt));
	for(int i=0;i<n;i++) fa[i]=i;
	for(int i=1;i<=k;i++){
		int d=gx[i].f,x=gx[i].a,y=gx[i].b;
		if(x==p||y==p) continue;
		int rx=find(x),ry=find(y);
		if(rx==ry)
			if((rlt[y]-rlt[x]+3)%3!=d){
				md=min(md,i);
				continue;
			}
		uni(x,y,rx,ry,d);
	}
	if(md==2001) caipan++,cp=p;
	else amd=max(amd,md);
}
```
# 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct pss{
	int a,b,f;//0是=,1是< 
}gx[2005];
int rlt[501],fa[501],n,k,caipan,cp,md,amd;
int find(int x){
	if(fa[x]==x) return x;
	else{
		int c=find(fa[x]);
		rlt[x]=(rlt[x]+rlt[fa[x]])%3;
		return fa[x]=c;
	}
}
void uni(int x,int y,int rx,int ry,int d){
	rlt[ry]=(rlt[x]-rlt[y]+d+3)%3;
	fa[ry]=rx;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while(cin>>n>>k){
		for(int i=1,a,b;i<=k;i++){
			char qm;
			cin>>a>>qm>>b;
			if(qm=='=') gx[i]=(pss){a,b,0};
			if(qm=='>') gx[i]=(pss){b,a,1};
			if(qm=='<') gx[i]=(pss){a,b,1};
		} 
		cp=0,caipan=0,amd=0;
		for(int p=0;p<n;p++){
			md=2001;
			memset(rlt,0,sizeof(rlt));
			for(int i=0;i<n;i++) fa[i]=i;
			for(int i=1;i<=k;i++){
				int d=gx[i].f,x=gx[i].a,y=gx[i].b;
				if(x==p||y==p) continue;
				int rx=find(x),ry=find(y);
				if(rx==ry)
					if((rlt[y]-rlt[x]+3)%3!=d){
						md=min(md,i);
						continue;
					}
				uni(x,y,rx,ry,d);
			}
			if(md==2001) caipan++,cp=p;
			else amd=max(amd,md);
		}
		if(caipan==0) cout<<"Impossible\n";
		if(caipan==1) cout<<"Player "<<cp<<" can be determined to be the judge after "<<amd<<" lines\n";
		if(caipan>1) cout<<"Can not determine\n";
	}
}
```

---

## 作者：lzdll (赞：4)

其它三篇题解都是扩展域并查集，所以来写一篇边带权并查集的题解。

## 分析

注意到 $n$ 非常小，所以，我们就可以枚举谁是裁判。在每一局中，如果有一方是裁判，那么这一局无参考价值，直接跳过。剩下的对局没有矛盾，那这个人是裁判。

然后，我们写并查集，$d_i$ 表示节点 $i$ 到父节点的距离，它模 $3$ 之后的值，就表示它和父节点的关系。如果是 $0$ 就说明他们平局，$1$ 和 $2$ 对应输和赢。

但 $1$ 对应输 $2$ 对应赢和 $2$ 对应输 $1$ 对应赢之间没有本质上的差别。

如果两个点没合并，就合并。否则判断矛盾。如果把每一局遍历完之后都没有矛盾，说明一开始枚举的这个人可以作为裁判。

最后，如果没有人可以当裁判，输出 impossible，如果大于一个人可以当裁判，输出 Can not determine。

## 路径压缩

和一般的路径压缩差不多，只是要注意取模。
```cpp
int Find(int x){
	if(x!=fa[x]){
		int fx=fa[x];
		fa[x]=Find(fa[x]);
		d[x]=(d[x]+d[fx])%3;
	}return fa[x];
}
```

## 合并

如果是把新点和已知点合并，那么就非常简单。但是，如果是两个已知点合并，该怎么办？

画个图：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/z5qj0az4.png?x-oss-process=image/resize,m_lfit,h_370,w_500)

我们现在要连这条蓝色的边，边权应该是 $2$。

其实就相当于 $1$ 到 $5$ 连一条边权为 $2-2=0$ 的边。

思考一下，得出：

这里要从 $a$ 向 $b$ 连边权为 $c$ 的边。先更新 $a$ 的根的 $d$ 的值，再把它连到 $b$ 底下。
```cpp
d[Find(a)]=c-d[a];
d[Find(a)]=(d[Find(a)]+300)%3;
fa[Find(a)]=b;
```

## 判矛盾

如果 $a$ 和 $b$ 本来就知道胜负关系，现在就只需要看是否矛盾。$d_a-d_b$ 就是他们以前算出的胜负关系，$c$ 是现在又给的胜负关系。

```cpp
if((d[a]-d[b]+300)%3!=c){
	flag=0;
	as=max(as,i);
	break;
}
```

在枚举其他人是不是裁判时，出现冲突的时间最大值就时确定其他人都不是裁判的时间，可以判出裁判。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 50005
using namespace std;
int n,m;
int fa[N],d[N],sz[N];
int Find(int x){
	if(x!=fa[x]){
		int fx=fa[x];
		fa[x]=Find(fa[x]);
		d[x]=(d[x]+d[fx])%3;
	}return fa[x];
}
struct node{
	int a,b,c;
}q[2005];
signed main(){
	while(cin>>n>>m){
		for(int i=1;i<=m;++i){
			char c;
			cin>>q[i].a>>c>>q[i].b;
			if(c=='=')q[i].c=0;
			else if(c=='<')q[i].c=2;
			else q[i].c=1;
		}
		int cnt=0,ans=-2010,as=0;
		for(int k=0;k<n;++k){
			for(int i=0;i<n;++i){
				fa[i]=i,d[i]=0,sz[i]=1;
			}
			//meiju who is judger
			bool flag=1;
			for(int i=1;i<=m;++i){
				if(q[i].a==k||q[i].b==k)continue;
				int a=q[i].a,b=q[i].b,c=q[i].c;
				if(Find(a)!=Find(b)){
					d[Find(a)]=c-d[a];
					d[Find(a)]=(d[Find(a)]+300)%3;
					fa[Find(a)]=b;
				}else{
					if((d[a]-d[b]+300)%3!=c){
						flag=0;
						as=max(as,i);
						break;
					}
				}
			}
			if(flag){
				++cnt;
				ans=k;
			}
		}
		if(cnt==0){
			cout<<"Impossible\n";
		}else if(cnt==1){
			cout<<"Player "<<ans<<" can be determined to be the judge after "<<as<<" lines\n";
		}else{
			cout<<"Can not determine\n";
		}
	}
	return 0;
}
```

---

## 作者：syzyc (赞：2)

[更好的阅读体验](https://blog.csdn.net/m0_72761451/article/details/143704732)

# 思路
不难看出此题具有要求我们进行分类的的特点，这一般就是并查集了。

### 一、先考虑什么情况下一个人可以是裁判： 
可以肯定的是，如果有裁判，由于他可以出任意手势，所以他会带来矛盾，即：他必须至少被同时归到两个组中。

因此我们采取枚举的方法，先认定 $u$ 是一个裁判，然后忽视所有与他相关的对局，再看是否会出现矛盾。

1. 如果出现矛盾，就有这几种可能：
(1) $u$ 是“假裁判”，即：实际上 $u$ 就不是裁判；
(2) $u$ 是“真裁判”，同时也存在另外一个“真裁判”。

很显然对于后者要输出 Impossible。而对于前者，我们让程序继续运行下去就好了。

2. 如果不出现矛盾，就有这几种可能：
(1) $u$ 是“真裁判”；
(2) $u$ 是“假裁判”，因为忽略一个非裁判的人的对局是不会对判断产生影响的。

对于**不出现矛盾的这个大情况**，我们可以先认定 $u$ 就是裁判。
如果后来又有 $v$ 也出现了不矛盾这个大情况，那就说明裁判人选有多个，需要输出 Can not determine ；
如果后续**都出现矛盾了**，那就说明 $u$ 就是“真裁判”，输出先前记录的即可。

### 二、现在考虑用并查集实现：
**注意**：这里的并查集并不是用来记录分类的，而是用来判断两个节点的关系是否已经确认。

我们选择**记录距离的带权并查集**。

$d[u]$ 表示节点 $u$ 与所在并查集根节点的关系，

若节点等于根，那 $d[u] = 0$;

若节点小于根，那 $d[u] = 1$;

若节点大于根，那 $d[u] = 2$。

在判断过程中，
若两个节点的关系之前从未判断（即：两个节点所在并查集不同），那就合并；

若之前判断过（是在一个并查集里），那就看是否出现矛盾，出现了就记录出现矛盾的是第几个语句，并退出。

# 代码
```cpp
#include <bits/stdc++.h>

#define mkpr make_pair

using namespace std;


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

const int maxn = 5e5 + 7;
const int maxm = 5e5 + 7;
const int inf  = 0x3f3f3f3f;

int n, m;
struct Query {
	int x, y, op;
} q[maxn];
int ans, line;

int fa[maxn], d[maxn];
int find(int x) {
	if (x != fa[x]) {
		int rtx = find(fa[x]);
		d[x] = (d[x] + d[fa[x]]) % 3;
		fa[x] = rtx;
	}
	return fa[x];
}

void init() {
	for (int i = 0; i < n; ++i) 
	    fa[i] = i, d[i] = 0;
}
int check(int u) {
    init();
    
    int turn = 0;
    for (int i = 1; i <= m; ++i) {
    	int x = q[i].x, y = q[i].y, op = q[i].op;
    	int fx = find(x), fy = find(y);
    	if (x == u || y == u) continue;
        
        if (fx != fy) {
        	fa[fx] = fy;
        	d[fx] = (op + d[y] - d[x] + 3) % 3;
		} else {
			if ((d[x] - d[y] + 3) % 3 != op) {
				turn = i;
				break;
			}
		}
	}
	
	// 没有矛盾
	if (turn == 0) {
	    // u 可能是裁判，先记录上
		if (ans == -1) {
			ans = u;
			return 1;
		}
		
		// 之前已经记录过一个可能的裁判
		// 而这个也可以是，那就输出 Can not determine
		return 0;
	}
	
	// 取 max 的原因：
	// (这里我们只讨论只有一个裁判的情况，因为其他情况用不上这个变量)
	// 若只有一个裁判，那 turn 非零时记录的值就是判断出裁判的语句
	// 唯一的 turn 等于 0 的情况就是，u 就是那个唯一的裁判
	// 因为此时忽略与他有关的语句就不会出现矛盾，turn 就等于 0
	line = max(line, turn);
	return 1;
}
void sol() {
	
	ans = -1, line = 0;
	for (int i = 1; i <= m; ++i) {
		int x, y; char c;
		scanf("%d%c%d", &x, &c, &y);
		q[i] = Query{x, y, (c == '=' ? 0 : (c == '<' ? 1 : 2))};
	}
	
	// 判断 i 是不是裁判 
    for (int i = 0; i < n; ++i) {
    	if (!check(i)) {
    		printf("Can not determine\n");
    		return ;
		}
	}
	// 一直出现矛盾
	// 即：只 ban 掉任意一个人，都会有矛盾
	// 此时裁判不只有一个
	if (ans == -1) printf("Impossible\n");
	
	// 存在过没出现矛盾的时刻，而且是唯一的时刻
	// 因为若出现多次【没有矛盾的时候】
	// 就已经输出 Can not determine 并退出了
	else printf("Player %d can be determined to be the judge after %d lines\n", ans, line);
}
int main() {
    while (~scanf("%d%d", &n, &m)) sol();
	return 0;
}

```

---

## 作者：i_wzy (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P10686)

 Acwing上有翻译，可以点此处查看：[翻译](https://www.acwing.com/problem/content/260/)

 也可以看讨论区的的某位 ~~dalao~~ 提供的翻译：[翻译](https://www.luogu.com/article/v97xrv8a)

---------------


# 题目分析


------------

首先我们读题，读完题后发现所给的关系 $ a > b $，$ a = b $，$ a < b $ 与 [[NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024) 比较类似，~~没写过这道题的的同学可以先看看这道题~~。

就是相当于当 $ a = b $ 的时候，$a$ 和 $b$ 是同类，记为关系一；当 $ a > b $ 的时候，$a$ 吃 $b$，记为关系二；当 $ a < b $ 的时候，$b$ 吃 $a$，记为关系三。而本题只是在 [NOI2001] 食物链的基础上多加了一个关系。关系三我们则可以通过 `swap(a,b)` 来将其转换为关系二。

此时，我们就可以使用食物链这道题的方法——**种类并查集**，我们设置一个**拓展域**，若 $a$ 是小朋友的编号，那 $a$ 则代表小朋友出的布，$a + n$ 则代表小朋友出的剪刀，$a + 2 \times n$ 则代表小朋友出的石头。最后我们再**枚举**裁判，并把包含他的关系跳过，推出其他关系会不会矛盾，如果没有矛盾，则说明这个人可能是裁判。如果存在的裁判大于 1，那么就输出 `Can not determine`；如果裁判只有一个，那么这就是唯一的裁判，则输出他；其他情况则输出 `Impossible`。

于是这道题就可以完美解决啦！


---------

## 注意：

- 记得初始化！！！
- 数组开大一点，别忘了种类并查集的拓展。

---



如果还有不理解的，就看看代码吧：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
const int N=5e6+10;
struct T{
	int a,b,c;
}t[N];
int n,m,fa[N],ans1,ans2,ansnum;//ans1是裁判，ans2是轮数，ansnum是统计裁判的个数 
inline void init(){//初始化并查集 
	for(int i=1;i<=3*n;i++)	fa[i]=i;
}
inline int find(int x){//查询 
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void noin(int x,int y){//合并 
	fa[find(x)]=find(y);
}
int main(){
	while(cin>>n){
		cin>>m;
		ans1=0,ans2=0,ansnum=0;
		init();
		if(m==0){	printf("Player 0 can be determined to be the judge after 0 lines\n");continue;}//特判一下 
		for(int i=1;i<=m;i++){
			char s;
			cin>>t[i].a>>s>>t[i].b;
			t[i].a++,t[i].b++;//去掉小朋友为0的情况
			if(s=='>') t[i].c=1;
			if(s=='=') t[i].c=2;
			if(s=='<'){//统一 成'>' 
				t[i].c=1;
				swap(t[i].a,t[i].b);
			}
		}
		for(int i=1;i<=n;i++){//枚举裁判 
			int flag=1;//记录是否存在裁判 
			init();//初始化 
			for(int j=1;j<=m;j++){
				if(t[j].a==i||t[j].b==i)	continue;
				if(t[j].c==2){//平局 
//					if(t[j].a==t[j].b)	continue;//要不要都一样的(*/ω＼*)
					if((find(t[j].a)==find(t[j].b+n))||(find(t[j].a+n)==find(t[j].b))){
						flag=0;//没有裁判 
						ans2=max(ans2,j);break;//记录轮数 
					} 
					noin(t[j].a,t[j].b);
					noin(t[j].a+n,t[j].b+n);
					noin(t[j].a+2*n,t[j].b+2*n);
				}
				if(t[j].c==1){//'>'的情况(已处理过'<'的情况了) 
					if((find(t[j].a)==find(t[j].b))||(find(t[j].a)==find(t[j].b+n))){
						flag=0;//没有裁判 
						ans2=max(ans2,j);break;//记录轮数 
					}
					noin(t[j].a,t[j].b+2*n);
					noin(t[j].a+n,t[j].b);
					noin(t[j].a+2*n,t[j].b+n);
				}
			}
			if(flag==1) ansnum++,ans1=i;//存在裁判，就记录答案
		//	cout<<ansnum<<'\n';
		}
		if(ansnum==1)	printf("Player %d can be determined to be the judge after %d lines\n",ans1-1,ans2);//因为我们最开始把小朋友多加了 1，所以此时还原减 1
		else if(ansnum>1)	printf("Can not determine\n");//存在多个裁判
		else	printf("Impossible\n");//找不到裁判
	}
	return 0;
}
```

---

## 作者：CMY2013 (赞：2)

# P10686

~~本蒟蒻第一次写题解~~，码风不好，希望各位大佬不喜勿喷。

看到各位大佬都用的扩展域并查集，那本蒟蒻就写一篇带权并查集的题解吧。

这道题的大意就是一群小朋友，他们之间玩石头剪刀布，其中有一名裁判，他可以出三种手势，而其他小朋友只能出一种手势（可能互不相等）。现在题目给定我们一些小朋友之间的猜拳结果，让我们根据这些条件来判断谁是裁判。如果有多个裁判或者没有一个人能当裁判，则输出特定语句。

这道题我们可以用带权并查集来做，在一个并查集内则代表两个人可以确定关系，创建一个数组 $d$ 来维护每个结点与其根节点的关系（$’1’$ 代表小于根节点，$’2’$ 代表等于根节点，$’3’$ 代表大于根节点），在输入的时候只将节点与其父节点的关系记录下来，然后再调用 $find$ 函数（也就是查询根节点）的时候维护 $d$ 数组。

接着我们来思考如何判断哪个人是裁判，因为 $n$ 很小，所以我们可以通过遍历每个人来判断他是不是裁判。每次遍历的时候，我们就初始化一下并查集,然后遍历 $m$ 次猜拳结果，如果两个人中有一个人是裁判，因为裁判可以出三种手势，所以这两个人的关系无法确定，则这次结果可以直接省去。否则如果猜拳的两个人在一个并查集内（这代表这两个人之间可以确定关系，公式为 
$((d[lx]-d[ly])+3)\bmod3$ ,（ $lx$ 代表着第一个人， $ly$ 代表着第二个人），至于为什么这样写，请各位读者们自己思考（提示：表示输赢关系的数只有 $0$，$1$，$2$ 三个数）)，如果通过并查集算出的关系和实际情况不符，则第 $i$ 号人不能当裁判（因为现实情况出现了矛盾），将这是第几个条件记录下来，并和原来记录的条件编号进行比较，取较大值（这样做的原因是题目让我们在输出谁是裁判时还要输出在判断完第几个条件后得出的结果，如果 $i$ 号人符合所有情况且其他 $n-1$ 个人都不符合情况，则 $i$ 号人就是裁判，这时候其他 $n-1$ 个人中不符合情况的编号最大的那个编号就是”判断完第几个条件后得出的结果“的答案），并退出循环。如果两个人不在一个并查集内，则将两个人的根节点合并，并根据公式 
$
d[fx]=((d[ly]-d[lx]+lp+3)\bmod3
$ ，（ $lx$ 和 $ly$ 意义同上， $lp$ 代表着 $lx$ 和  $ly$ 之间的关系， $fx$ 代表着 $lx$ 在并查集中的根节点），（至于为什么这样写，请各位读者们自己思考（提示：表示输赢关系的数只有 $0$，$1$，$2$ 三个数））算出 $fx$ 节点和 $fy$ （ $fx$ 意义同上， $fy$ 代表着 $ly$ 在并查集中的根节点）节点之间的关系，记录下来。如果 $m$ 个条件都遍历完了且中途没有退出循环，则代表 $i$ 号人可能成为裁判，将成功人数加 $1$，并将 $i$ 记录下来。

遍历完 $n$ 个人后，特判一下，如果  $m$ 是 $0$
，则所有人都有可能是裁判。如果成功人数大于一个，则输出 
Cannotdetermine。
如果没有一个人能成为裁判，则输出 
Impossible。
如果题目给定的条件都满足，则输出正确答案。
  ## CODE(含注释)
```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int n,m,f[510],d[510],x[2010],y[2010],p[2010];
// f数组记录着每个节点的父节点，x 数组记录着每次猜拳的第一个人，y 数组记录着每次猜拳的第二个人，p  数组记录着每次猜拳的结果
void init() // 初始化 
{
	for(int i=0;i<n;i++)
	{
		f[i]=i;
		d[i]=0;
	}
}

int find(int x) // 并查集模板，寻找根节点
{
	if(x==f[x]) return x;
	int fn=find(f[x]); // 路径压缩
	d[x]=(d[x]+d[f[x]])%3; // 因为前面一行代码已经递归过了，所以这里可以直接运算，来求这个节点和根节点的关系
	f[x]=fn;
	return f[x];
}

int main()
{
	while(cin>>n>>m)
	{
		int ans=0,cnt=0,l=0;
		for(int i=1;i<=m;i++)
		{
			char c;
			cin>>x[i]>>c>>y[i];
			if(c=='<') p[i]=1; // 带权并查集赋边权
			else if(c=='=') p[i]=0;
			else p[i]=2;
		}
		for(int i=0;i<n;i++) // 因为题目规定了小朋友的编号是从 0 号开始，所以我们枚举也从零号开始。
		{
			init(); // 先对并查集进行初始化
			for(int j=1;j<=m;j++) // 枚举每一个条件
			{
				int lx=x[j],ly=y[j],lp=p[j];
				int fx=find(lx),fy=find(ly); // 寻找根节点
				if(lx!=i && ly!=i)// 如果两个人中有一个人是裁判，则这组条件是无效的
				{
					if(fx==fy) // 如果两个人在同一集合里
					{
						if(((d[lx]-d[ly])+3)%3!=lp) // 如果两个人之间的关系不符合题目给的条件，则 i 号人不能当裁判
						{
							l=max(l,j);// 算出违规条件中编号最大的条件的编号
							break;
						}
					}
					else
					{
						f[fx]=fy; // 如果两个人不在一个集合里，则将两个人所在的集合合并
						d[fx]=(d[ly]-d[lx]+lp+3)%3; // 运用公式算出来两个人的根节点的关系
					}
				}
				if(j==m) // 如果所有条件都满足
				{
					cnt++; // 将成功人数加一
					ans=i; // 将答案赋成裁判的编号
				}
			}
		}
		if(m==0) cnt=n;// 如果一个条件都没有，则所有人都有可能是裁判
		if(cnt>1) cout<<"Can not determine"<<endl; // 如果成功人数大于一个，则输出 ”Can not determine“
		else if(cnt==0) cout<<"Impossible"<<endl; // 如果没有一个人能成为裁判，则输出 ”Impossible“
		else cout<<"Player "<<ans<<" can be determined to be the judge after "<<l<<" lines"<<endl;// 输出答案
	}
	return 0; 
}
```

---

## 作者：OpheebopZ (赞：2)

## 思路
枚举每个人 $k$ 为裁判，若除去所有关于他的对局后，剩下的对局没有冲突，则 $k$ 可以是裁判。

记合法裁判的人数为 $num$。

- 若 $num = 0$，则在仅有一个裁判的情况下无法完成所有回合，输出 `Impossible`。
- 若 $num > 1$，则裁判的人选多于 $1$ 个，则输出 `Can not determine`。
- 若 $num = 1$，则有且仅有一个人可能是裁判，则输出 `Player x can be determined to be the judge after y lines`，其中 $x$ 为唯一的除去所有关于他的对局后，剩下的对局没有冲突的人。

思考如何获得 $y$，想到只要能确定其他的人都不是裁判，就能确定剩下的那个人一定是裁判。

在枚举不是裁判的人 $k$ 时，统计其出现冲突的时间，其最大值就时确定其他的人都不是裁判的时间，即确定裁判的时间 $y$。

## 实现
这里使用扩展域的并查集实现。

将每个小朋友 $x$ 拆成 $3$ 个节点：石头域 $x _ {roc}$，剪刀域 $x _ {sci}$，布域 $x _ {pap}$。

则可以仿照 [[NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024) 的方法，分别对不同的三种情况合并能互相推出的域，注意去除和裁判有关的对局，并记录可能的裁判数量、确定其发生冲突的时间。按照 $num$ 的情况输出即可。

## AC 代码
很丑，见谅。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXM = 2005;

int n, m;
int fa[3 * MAXN], ign, ans;
int ju, rnd[MAXN];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
bool query(int x, int y) { return get(x) == get(y); }
void merge(int x, int y) { fa[get(x)] = get(y); }

struct Win {
	int op, x, y;
} a[MAXM];

int toint(string s) {
	int res = 0, mul = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		res += mul * char(s[i] - '0');
		mul *= 10;
	}
	return res;
}

void solve() {
	for (int i = 0; i <= 3 * n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		op = a[i].op, x = a[i].x, y = a[i].y;
		if (x == ign || y == ign) continue;
		int x_pap = x, x_sci = x + n, x_roc = x + 2 * n; // 三个域
		int y_pap = y, y_sci = y + n, y_roc = y + 2 * n;
		if (op == -1) { // 输的情况
			if (query(x_roc, y_roc) || query(x_roc, y_sci)) {
				rnd[ign] = i;
				return ;
			}
			merge(x_roc, y_pap); merge(x_sci, y_roc); merge(x_pap, y_sci);
		} 
		else if (op == 0) { // 平局的情况
			if (query(x_roc, y_pap) || query(x_roc, y_sci)) {
				rnd[ign] = i;
				return ;
			}
			merge(x_roc, y_roc); merge(x_sci, y_sci); merge(x_pap, y_pap);
		} 
		else { // 赢的情况
			if (query(x_roc, y_roc) || query(x_roc, y_pap)) {
				rnd[ign] = i;
				return ;
			}
			merge(x_roc, y_sci); merge(x_sci, y_pap); merge(x_pap, y_roc);
		}
	}
	ans++;
	ju = ign;
}

int main() {
	while (cin >> n >> m) {
		if (n == 1) { // 特判 n = 1 可以直接出结果
			cout << "Player 0 can be determined to be the judge after 0 lines" << endl; 
			continue; 
		}
		for (int i = 1; i <= m; i++) {
			string res;
			cin >> res;
			int op, x, y;
			for (int j = 0; j < res.size(); j++)
				if (!isdigit(res[j])) { op = j; break; }
			x = toint(res.substr(0, op)), y = toint(res.substr(op + 1, res.size() - op - 1));
			op = res[op] == '<' ? -1 : (res[op] == '=' ? 0 : 1);
			a[i].x = x, a[i].y = y, a[i].op = op;
		}
		ans = 0; int r = 0;
		for (ign = 0; ign < n; ign++) { // 枚举每个人为裁判
			solve();
		}
		for (int i = 0; i < n; i++) // 确定裁判的时间
			if (i != ju) r = max(r, rnd[i]);
		if (ans == 0) cout << "Impossible" << endl;
		else if (ans != 1) cout << "Can not determine" << endl;
		else cout << "Player " << ju << " can be determined to be the judge after " << r << " lines" << endl;
	}
	return 0;
}
```

---

## 作者：qcf2010 (赞：1)

可以先尝试做[P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)。然后你就会发现，那一题和本题是等价的。

# 思路

在读入数据时做一些修改，若读到 `a<b`，则改为 `b>a`，这样就只有两种情况了：要么是 $a$ 与 $b$ 平局，要么是 $a$ 赢了 $b$。相当于[P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)中的 $a$ 与 $b$ 同类以及 $a$ 捕食 $b$。

依次枚举每个小朋友，假设他是裁判。接着枚举每一轮对局情况，将对局情况拆成三种情况，分别对应出的是剪刀、石头、布，将三种情况在种类并查集里分别进行合并。每一次合并前，先检查会不会出现矛盾，如果出现矛盾，证明当前枚举的小朋友不是裁判，换下一个小朋友。特别地，如果发现当前要进行操作的对局情况中有一个选手是裁判，则直接跳过不进行操作。因为裁判什么都可以出，没有意义。

记录满足条件的裁判以及个数。若裁判个数为 $1$，则表示找到唯一裁判；若裁判个数为 $0$，则表示无解；否则裁判不唯一。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e3+10;

int n,m;
string s;
int a[N],b[N];
char res[N];

int fa[3*N];

int Get(int x){
	if(x==fa[x]) return x;
	return fa[x]=Get(fa[x]);
}

void Merge(int x,int y){
	fa[Get(x)]=Get(y);
}

int Get_value(int l,int r){
	int ans=0;
	for(int i=l;i<=r;++i) ans=ans*10+(s[i]-'0');
	return ans;
}

void Read(){
	for(int i=1;i<=m;++i){
		cin>>s;
		int id;
		for(int j=0;j<s.size();++j){
			if(!('0'<=s[j]&&s[j]<='9')){
				id=j;
				break;
			}
		}
		if(s[id]=='<'){
			b[i]=Get_value(0,id-1);
			res[i]='>';
			a[i]=Get_value(id+1,s.size()-1);
		}else{
			a[i]=Get_value(0,id-1);
			res[i]=s[id];
			b[i]=Get_value(id+1,s.size()-1);			
		}
	} 
	
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	while(cin>>n>>m){
		Read();
		int cnt=0,who=0,which=0;
		for(int i=0;i<n;++i){
			for(int j=0;j<=3*n;++j) fa[j]=j;
			bool f=1;
			for(int j=1;j<=m;++j){
				int a_self=a[j],a_win=a[j]+n,a_lose=a[j]+n*2;
				int b_self=b[j],b_win=b[j]+n,b_lose=b[j]+n*2;
				if(i==a_self||i==b_self) continue;
				if(res[j]=='='){
					if(Get(a_win)==Get(b_self)||Get(a_self)==Get(b_win)){
						which=max(which,j);
						f=0;
						break;
					}
					Merge(a_self,b_self);
					Merge(a_win,b_win);
					Merge(a_lose,b_lose);
				}else{
					if(Get(a_self)==Get(b_self)||Get(a_self)==Get(b_win)){
						which=max(which,j);
						f=0;
						break;
					}
					Merge(a_win,b_self);
					Merge(a_self,b_lose);
					Merge(a_lose,b_win);					
				}
			}
			if(f){
				++cnt;
				who=i;
			}
		}
		if(cnt==1) cout<<"Player "<<who<<" can be determined to be the judge after "<<which<<" lines\n";
		else if(cnt>1) cout<<"Can not determine\n";
		else cout<<"Impossible\n";
	}

	return 0;
}

```

---

## 作者：Naive_nzr (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10686)

 闲话：本题和 [[NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024) 非常像，感兴趣的也可以试试。

---
## 思路
题意概述如下，有 $A$,$B$,$C$ 三组，他们满足$A>B$,$B>C$,$C>A$的相互克制的关系。但是存在裁判，他的分组是不确定的，题目想要求判断情况（可/否），裁判个数（一/多），以及在可判断仅一个裁判的前提下，裁判序号和最早判断位置。
    
我们考虑建立并查集，因为并查集能够快速建立和查找归属关系，符合本题的分组条件。但是还需要体现每组之间的输赢关系，所以我们考虑建立一种特殊的并查集--**种类并查集**。

具体来讲我们需要建立一个大小为 $3n$ 的并查集 $f$数组，在存储序号为 $a$ 的个体的关系时，把 $a$ 和同类放在一起，$a+n$ 和 $a$ 的手下败将放在一起，把 $a+2n$ 和打败 $a$ 的人放到一起，建立一个完整的关系网，这样关系就很清晰明了了。

根据输赢不同代码实现如下（`tie(a,b)` 表示平局；`win(a,b)`表示 $a$ 赢了 $b$)：

```cpp
void tie(int a,int b){
	f[find(a)]=find(b);
	f[find(a+n)]=find(b+n);
	f[find(a+2*n)]=find(b+2*n);
}
void win(int a,int b){
	f[find(a+n)]=find(b);//a+n和a的败手连在一起 
	f[find(a+2*n)]=find(b+n);//a+2n和a的胜手连在一起 
	f[find(b+2*n)]=find(a); //a和同类连在一起 
}
```
而对于查询并判断两个人的关系，我的经验是找相等关系，去判断 $a$ , $a+n$ 或 $a+2n$ 与 $b$ 的关系，可能有很多种符合逻辑的式子，只要你前面的关系网建的正确，只要判断其中一个就可以。
代码实现如下：

```cpp
int check(int a,int b){
	if(find(a)==find(b)) return 0;
	else if(find(a+n)==find(b)) return 1;//a赢
	else if(find(a+2*n)==find(b)) return -1;//b赢
	else return 2;//没关系 
}
```
以上就是种类并查集的基本操作了，接下来是针对本题的很烦人的点：
1. 对于裁判的选定：如果发生了一次矛盾，我们无法确定两个对手谁才是裁判，同样的，如果两个人发生多次矛盾，那我们也都无法判断谁是裁判，选择裁判的标准是一个人同时与两个不同对手发生矛盾。
2. **找到的裁判只有最先找到的有效**，因为围绕已经出现的裁判已经产生了既定的关系，而这些关系很多因为裁判的加入是错误的，可能导致选手被误判为裁判。
3. 所以要进行**两次枚举**，第一次枚举要找确定的裁判，第二次枚举要将该裁判排除，重新建立关系，再判断符合哪种情况，如果正常，就输出 `Player x can be determined to be the judge after y lines` ，如果在排除裁判之后又出现矛盾，说明应该不止一个裁判，就输出`Impossible`,如果两次枚举始终没有找到确定的裁判，就输出`Can not determine`。

最后捋一遍过程：
- [ ] 建立种类并查集及基本操作（别忘了并查集初始化。
- [ ] 两次枚举。

---
## AC代码（应该是目前最快的了，但内存稍大了些）

```cpp
#include<bits/stdc++.h>
using namespace std;
//动物园的翻版 
int n,m;
int t[1600],f[1600];//三个领域 1赢2 2赢3 3赢1 1是原始域 
int find(int a){
	if(f[a]==a) return a;
	else return f[a]=find(f[a]);
} 
void tie(int a,int b){
	f[find(a)]=find(b);
	f[find(a+n)]=find(b+n);
	f[find(a+2*n)]=find(b+2*n);
}
void win(int a,int b){
	f[find(a+n)]=find(b);//a+n和a的败手连在一起 
	f[find(a+2*n)]=find(b+n);//a+2n和a的胜手连在一起 
	f[find(b+2*n)]=find(a); //a和同类连在一起 
}
int check(int a,int b){
	if(find(a)==find(b)) return 0;
	else if(find(a+n)==find(b)) return 1;//a赢
	else if(find(a+2*n)==find(b)) return -1;//b赢
	else return 2;//没关系 
}
int p1[2005],p2[2005],v[2005],u[2005]; 
char c; 
int main(){
	int ju,len;
	while(cin>>n){
		scanf("%d",&m);
		if(n==1,m==0){
			puts("Player 0 can be determined to be the judge after 0 lines");
			continue;
		}		
		ju=-1;
		for(int i=0;i<=3*n;i++)
			f[i]=i,t[i]=0;
		//第一遍在线循环 负责寻找裁判 
		for(int i=1;i<=m;i++){
			scanf("%d%c%d",&p1[i],&c,&p2[i]);
			if(c=='>') u[i]=1;
			if(c=='=') u[i]=0;
			if(c=='<') u[i]=-1;
			if(ju>=0) continue;			
			v[i]=check(p1[i],p2[i]);
			if(v[i]==2){
				if(u[i]==0) tie(p1[i],p2[i]);
				if(u[i]==1) win(p1[i],p2[i]);
				if(u[i]==-1) win(p2[i],p1[i]);
			}
			else if(v[i]!=u[i]){
				if(t[p1[i]]&&t[p2[i]]&&t[p1[i]]==t[p2[i]]) continue;
				if(t[p1[i]]){
					ju=p1[i];
					len=i;
				}
				else if(t[p2[i]]){
					ju=p2[i];
					len=i;
				}
				t[p1[i]]++,t[p2[i]]++;
			}
		}
		for(int i=0;i<=3*n;i++)
			f[i]=i;
		//第二遍负责消除裁判的影响 
		for(int i=1;i<=m;i++){
			if(p1[i]==ju||p2[i]==ju) continue; 
			v[i]=check(p1[i],p2[i]);
			if(v[i]==2){
				if(u[i]==0) tie(p1[i],p2[i]);
				if(u[i]==1) win(p1[i],p2[i]);
				if(u[i]==-1) win(p2[i],p1[i]);
			}
			else if(v[i]!=u[i]){//一旦出现问题 就意味着不只有一个裁判
				ju=n;
				break; 
			}
		}
		if(ju==-1) puts("Can not determine");
		else if(ju==n) puts("Impossible");
		else printf("Player %d can be determined to be the judge after %d lines\n",ju,len);
	}
	return 0;
}
```

---

## 作者：myxRUC (赞：0)

# 思路

作为经典的并查集问题，按照剪刀石头布分为三类，但是本题关键并不在于每个人属于哪一类，而是在于两个人的关系。这个关系我们可以用边权来记，由于规则分为平局和非平局，所以边权很容易用 $0、1$ 来表示。因此读入数据的时候我们把输赢统一为一种情况，赢者在后

```cpp
for (int i = 1; i <= m; i++) {
	cin >> pl[i].a >> pl[i].c >> pl[i].b;
	if (pl[i].c == '>') {
		swap(pl[i].a, pl[i].b);//交换顺序
	}
}
```
所以对于每个人，先初始化，**（$d$ 作为到达根节点的距离，很好的衡量两个人的胜负或者平局关系）**
```cpp
for (int i = 1; i <= n; i++)f[i] = i;
memset(d, 0, sizeof(d));//d表示到根节点的距离
```
当我们考虑每组数据的时候，由于 $N$ 不超过 $500$,不妨枚举每个人作为裁判，然后判断 $M$ 次游戏结果存不存在矛盾，**（遇到裁判参与游戏就跳过，因为情况一定合理，裁判可以随意出）**，如果存在，说明这个人不是裁判；否则是裁判。

并查集函数
```cpp
int dfs(int x) {
	if (x == f[x])return f[x];
	int t = dfs(f[x]);
	d[x] = d[x] + d[f[x]];
	return f[x] = t;
}
```


下面讨论对每局游戏的判断，假设是 $x1$ 和 $x2$，递归寻找 $x1$ 和 $x2$ 所属的集合，并根据 $x1$ 和 $x2$ 的关系确定距离 $dis$。
```cpp
int x1=pl[i].a, x2=pl[i].b, dis = 0;
char c=pl[i].c;
if (x1 == k || x2 == k)continue;//裁判参与就不判断，因为一定不矛盾
int a = dfs(x1), b = dfs(x2);
if (c == '<'||pl[i].c=='>')dis = 1;
if (c == '=')dis = 0;
```
下面判断两种情况，就是两个人在不在一个集合以内
```cpp
if (a == b)
{
      if (((d[x1] - d[x2]) % 3 + 3) % 3 != dis){
        ok = false;
        tp = min(tp, i);//记录判断裁判的位置
      }
}
else
{
      f[a] = b;
      d[a] = ((d[x2] - d[x1] + dis) % 3 + 3) % 3;
}
```
# 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 505, M = 2005;
int f[N], d[N];
int cnt = 0, n = 0, m = 0;
struct node {
	int a, b;
	char c;
}pl[M];
int dfs(int x) {
	if (x == f[x])return f[x];
	int t = dfs(f[x]);
	d[x] = d[x] + d[f[x]];
	return f[x] = t;
}
int main(void) {
	while (cin >> n >> m) {
		int cnt = 0, num = 0, tp = 0, pos = 0;
		if (n == 1 && m == 0) {
			num = 0, pos = 0;
		}
		for (int i = 1; i <= m; i++) {
			cin >> pl[i].a >> pl[i].c >> pl[i].b;
			if (pl[i].c == '>') {
				swap(pl[i].a, pl[i].b);
			}
		}
		for (int k = 0; k < n; k++) {
			tp = 2001;
			for (int i = 0; i < n; i++)f[i] = i;
			memset(d, 0, sizeof(d));
			bool ok = true;
			for (int i = 1; i <= m; i++) {
				int x1=pl[i].a, x2=pl[i].b, dis = 0;
				char c=pl[i].c;
				if (x1 == k || x2 == k)continue;
				int a = dfs(x1), b = dfs(x2);
				if (c == '<'||c=='>')dis = 1;
				if (c == '=')dis = 0;
				if (a == b) {
					if (((d[x1] - d[x2]) % 3 + 3) % 3 != dis) {
						ok = false;
						tp = min(tp, i);
					}
				}
				else {
					f[a] = b;
					d[a] = ((d[x2] - d[x1] + dis) % 3 + 3) % 3;
				}
			}
			if (tp == 2001) cnt++, num = k;
			else pos = max(pos, tp);
		}
		if (cnt == 0) {
			cout << "Impossible" << endl;
		}
		else if (cnt > 1) {
			cout << "Can not determine" << endl;
		}
		else {
			cout << "Player " << num << " can be determined to be the judge after " << pos << " lines\n";
		}
	}
	return 0;
}
```

---

