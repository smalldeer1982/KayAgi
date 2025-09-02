# Print Check

## 题目描述

小澳最近迷上了考古，他发现秦始皇的兵马俑布局十分有特点，热爱钻研的小澳打算在电脑上还原这个伟大的布局。
他努力钻研，发现秦始皇布置兵马俑是有一定规律的。兵马俑阵总共有n行m列，秦始皇在布置的时候每次会指定一行或一列，然后指定一个兵种，使得这一行或者这一列上全部放上这一个兵种。如果这一行上以前放过其它的兵种，那么他会拔掉以前的兵种改成现在他命令的兵种。
小澳从秦朝的文献中找到了布置这个方阵的操作顺序，他希望你能告诉他布局完成后整个兵马俑阵是什么样子的。

## 样例 #1

### 输入

```
3 3 3
1 1 3
2 2 1
1 2 2
```

### 输出

```
3 1 3 
2 2 2 
0 1 0 
```

## 样例 #2

### 输入

```
5 3 5
1 1 1
1 3 1
1 5 1
2 1 1
2 3 1
```

### 输出

```
1 1 1 
1 0 1 
1 1 1 
1 0 1 
1 1 1 
```

# 题解

## 作者：RE_Prince (赞：5)

# CF631B Print Check

[link](https://www.luogu.com.cn/problem/CF631B)

吐槽一下翻译：人家题面是染色，翻译后成兵马俑了…


## Sol


看见题解区里没有我这种比较暴力的做法，来一发。

### 最基础的算法——暴力


大体思路就是按照题目要求一次一次操作地做，但是，这种复杂度应该是 $\mathcal O(nmk)$ 的，显然会 T，所以我们要优化。


### 进阶——优化暴力


我们回头看一下以前做过的题：[P1003](https://www.luogu.com.cn/problem/P1003)


那道题思路是什么？不就是倒着枚举然后找到最上面的地毯吗？因此，我们这道题也可以运用相同思路，将操作存在 $x_i,y_i,z_i$ 三个数组中，统一离线处理。

思考一下，最后染的颜色一定是那个格子最后的颜色（毫无疑问）。我们将枚举方向反一下，就能瞬间求出一个格子最终的颜色。


### 终极——暴力正解



上面这种方法应该（我没试过）也过不了这道题。但是，当我们看到 $n\times m\le10^5$ 这个条件时，就发现前面那个 $n,m\le5000$ 实际上是假的。再进行一次深入思考，并再次读题，可以得出一个结论：既然它的操作都是操作行列的，那么我们可以再反着跑时记录每行每列是否被整体染过色，如果是，那么直接进入下一层循环，因为前面怎么染都会被后面的颜色覆盖掉。


实现：用 $mpc_i,mpr_i$ 来记录每列，行是否被整体染色。


当然，注意一个小细节：当枚举的格子**没被染色**时，才能赋成当前颜色。

为了减小复杂度，可以就枚举这一行或列的格子，没必要整个矩阵全部枚举，然后判断。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,x[100009],y[100009],z[100009];
unordered_map<int,int> mpr,mpc;//懒得开数组了，用map
int a[5009][5009];
signed main()
{
	int f;
	cin>>n>>m>>f;
	for(i=1;i<=f;i++) cin>>z[i]>>x[i]>>y[i];//存储，离线操作
	for(k=f;k>=1;k--)
	{
		if(z[k]==1)
		{
			if(mpr[x[k]]) continue;//如果这一行已经被整体染色，continue。
			mpr[x[k]]=1;//否则标记
			for(i=1;i<=m;i++) if(!a[x[k]][i]) a[x[k]][i]=y[k];//时间的一个优化
		}
		else//列同理
		{
			if(mpc[x[k]]) continue;
			mpc[x[k]]=1;
			for(i=1;i<=n;i++) if(!a[i][x[k]]) a[i][x[k]]=y[k];
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++) cout<<a[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：1)

# 题意


------------
一个 $n \times m$ 的初始全为零的矩阵，给定 $k$ 次操作，按顺序给某行或某列染色，求 $k$ 次染色后的矩阵。


------------
# 思路


------------
首先考虑暴力，每次操作都暴力地更新一行或者一列颜色，最后将矩阵输出，时间复杂度 $O(nk+nm)$  ，然而 $k \le 100000 $ 和 $n,m\le 5000$ 明显会超时。

考虑优化，从暴力算法中可以看出，在暴力更新每行每列的过程中，同一行可能会被更新多次，这大大浪费了我们的时间，我们可以在一行和一列开头的位置标记上此行或此列的颜色，如果此行或此列已经有了一种颜色，就按先后顺序覆盖。

我们先讨论行的情况，这种情况比较简单，按照先后顺序覆盖颜色就行了，在所有行的操作执行完后用  $O(nm)$  的复杂度更新每一个格子的颜色。

接下来是列的情况，列的情况与行大致相同，但是我们执行完行的情况会发现原先操作的顺序被我们打乱了！怎么解决呢？我们可以将原先的顺序记录在每个操作的结构体里面，在最后更新每一列的颜色的时候看一下该次操作的顺序，看一下颜色有没有被覆盖就行了。


------------
# AC 代码


------------
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,mm,q;
int a[5005][5005];
struct node{
	int x;
	int bj;
	int pri;
	int w;
}m[1000005];
inline int read(){
	int w=1,ans=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
bool cmd(node a,node b){
	if(a.bj==b.bj){
		return a.pri<b.pri;
	}
	return a.bj<b.bj;
}
bool cmd1(node a,node b){
	return a.pri<b.pri;
}
int ans;
int main(){
	n=read();
	mm=read();
	q=read();
	for(int i=1;i<=q;i++){
		m[i].bj=read();
		m[i].x=read();
		m[i].w=read();
		m[i].pri=i;
	}
	sort(m+1,m+1+q,cmd);
	for(int i=1;m[i].bj==1;i++){
		a[m[i].x][0]=m[i].pri;
		ans=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			a[i][j]=a[i][0];
		}
	} 
	for(int i=ans+1;i<=q;i++){
		a[0][m[i].x]=m[i].pri;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			a[i][j]=max(a[i][j],a[0][j]);
		}
	}
	sort(m+1,m+1+q,cmd1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			printf("%d ",m[a[i][j]].w);
		}
		printf("\n");
	}
	return 0;
}

```








---

## 作者：linxuanrui (赞：1)

### 思路

显然，如果暴力的话，时间复杂度为 $O(nmq)$，显然会超时。

这里就可以采用类似 [P1003](https://www.luogu.com.cn/problem/P1003) 的方法。既然题目说了每次操作会把每一行或每一列都赋值为一个相同的数，所以我们可以采用离线操作，对那一行或那一列打上标记，等到最后的时候再处理。

我们可以定义两个数组 $h$ 和 $l$，$h_i$ 存储第 $i$ 行整体被赋的值，以及是在第几个操作被赋的值，$l_i$ 同理，不过是存储列的。有人可能会问，为什么要存储是在第几个操作被赋的值呢？因为如果一个有个节点行和列同时被赋了值，那么较晚赋值的行或列就是这个节点的值。实在不懂，我们可以举个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dkbmmb3.png)

在这个例子中，第一列被赋值成了 $1$，第一行被赋值成了 $2$。因为第一行比第一列晚赋值，因此第一行第一列是 $2$。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;
ll n,m,q,x,y,z; 
pair<int,int> h[5001],l[5001];
//h[i].first 表示第 i 行整体被赋的值，h[i].second 表示是在第几个操作被赋的值，l[i] 同理
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= q;i++){
		cin >> x >> y >> z;
		if(x == 1)h[y] = {i,z};
		else l[y] = {i,z};
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++)cout << (h[i].first > l[j].first ? h[i].second : l[j].second) << " ";
		cout << endl;
	}
}
```

---

## 作者：Palace (赞：1)

[走你](https://www.luogu.org/problemnew/show/CF631B)

## 思路：

如果在q次操作中直接修改会T到飞起。这种情况让我们想起线段树等等，他们都用了一个叫做懒惰标记的东西，我们也可以把这种思想运用到这个题。

对于每一次操作，我们都用tag记录下行（或列）需要染上的颜色和这次染色的时间，到最后输出的时候，我们只需要比较当前位置行的tag和列的tag哪个修改的时间靠后，就输出哪个（因为之前的操作可能被之后的操作覆盖）

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5010
using namespace std;
struct haha{
	int val,tm;
}tagl[N],tagh[N];
int n,m,q;
int a[N][N];
int read(){
	char ch;
	bool f=false;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-') f=true;
	int res=ch-48;
	while((ch=getchar())>='0'&&ch<='9')
	res=res*10+ch-48;
	return f?res+1:res; 
}
int main(){
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	n=read();m=read();q=read();
	for(int i=1;i<=q;i++){
		int x,y,z;
		x=read();y=read();z=read();
		if(x==1){
			tagh[y].val=z;
			tagh[y].tm=i;
		}
		if(x==2){
			tagl[y].tm=i;
			tagl[y].val=z;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(tagh[i].tm>tagl[j].tm)
				a[i][j]=tagh[i].val;
			else if(tagh[i].tm<tagl[j].tm)
				a[i][j]=tagl[j].val;
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：HadrianZhang (赞：0)

# 思路

首先，暴力会超时，上正解。

用一个结构体表示某一行或某一列最后上的颜色及顺序。第 $i$ 行用 $col_i$ 表示，第 $j$ 列用 $row_j$ 表示。

当有一次行当染色操作时，直接覆盖以前该行的颜色，并标上编号。列同理。

输出时，由于一个格子 $(i,j)$ 只能被 $col_i$ 记录的颜色或 $row_j$ 记录的颜色影响，所以只需比较 $col_i$ 的顺序与 $row_j$ 的顺序。若 $col_i$ 的顺序靠后，说明 $col_i$ 记录的颜色比 $row_j$ 记录的颜色后染，所以该格子染 $col_i$ 记录的颜色。反之也同理。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
struct node
{
	int c,idx;
}col[5005],row[5005];
int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=t;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1) col[x]={y,i};
		else row[x]={y,i};
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cout<<(col[i].idx>row[j].idx?col[i].c:row[j].c)<<" \n"[j==m];
	return 0;
}
```

---

## 作者：achjuncool (赞：0)

# 思路

首先，纯暴力肯定超时。

我们考虑用两个数组分别表示一整行与一整列的颜色。

这样就有一个问题：如果一个格子被重复染色，该怎么办呢？

题目里说了，如果一个格子已经被染色了，那就覆盖。

我们自然地想到标记一个染色时间，输出时直接比较行列的染色时间即可。

~~（写完才发现翻译是兵马俑，懒得改了）~~

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll n, m, k, op, r, x;
struct node{
	ll val, id = -1; //id 初始值设为 -1 便于没有染色的格子的比较
} a[5005], b[5005];
ll f(node p, node q){
	if(p.id > q.id) return p.val;
	if(p.id < q.id) return q.val;
	return 0; //没有染过色
}
int main(){
	qwq;
	cin >> n >> m >> k;
	for(ll i = 1; i <= k; i++){
		cin >> op >> r >> x;
		if(op == 1){
			a[r].val = x;
			a[r].id = i;
		} else {
			b[r].val = x;
			b[r].id = i;
		}
	}
	for(ll i = 1; i <= n; i++){
		for(ll j = 1; j <= m; j++) cout << f(a[i], b[j]) << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# CF631B Print Check 题解

## 题意回顾

你需要维护一个 $ n $ 行 $ m $ 列的矩阵，需要支持整行赋值和整列赋值两种操作共 $ q $ 次，最后输出整个矩阵。

$ n \times m \le 10^5, k \le 10^5 $。

## 正解

我们发现对于一个格子，只有所在行列的操作会对其进行影响。而对于一行或一列的所有操作，只有最后一次对此行/此列的操作可能产生影响。

因此，我们只需要维护对于每一行和每一列最后一次操作的操作时间和操作效果，对于每个格子考虑哪个操作最后发生那个操作的颜色就是最后的颜色。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
int T;
int n, m, q;
struct node {
    int tim;
    int col;
};
node make(int ti0, int co0) {
    node res;
    res.tim = ti0;
    res.col = co0;
    return res;
}
node hang[N];
node lie[N];
int main() {
    T = 1;
    int op, x, c, tmp;
    for(int ti = 1; ti <= T; ti++) {
        scanf("%d%d%d", &n, &m, &q);
        for(int i = 1; i <= n; i++) {
            hang[i] = make(0, 0);
        }
        for(int i = 1; i <= m; i++) {
            lie[i] = make(0, 0);
        }
        for(int i = 1; i <= q; i++) {
            scanf("%d%d%d", &op, &x, &c);
            if(op == 1) {
                hang[x] = make(i, c);
            } else {
                lie[x] = make(i, c);
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(hang[i].tim >= lie[j].tim) {
                    tmp = hang[i].col;
                } else {
                    tmp = lie[j].col;
                }
                printf("%d", tmp);
                if(j != m) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
```

## 总结与评价

这题评绿就挺离谱的。

建议将春测出题人禁止出题一年（2 个重题）。

---

## 作者：technopolis_2085 (赞：0)

~~这题好像就是春测T1~~

分析：

如果一个一个地布置，肯定会超时。

考虑优化。

由于后布置的会覆盖之前布置的，所以考虑记录每次布置的时间点。

然后就做完了。

输出时判断这个格子是先布置的列还是先布置的行，输出后布置的兵种。

```cpp

#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int row[maxn],col[maxn];
int lrow[maxn],lcol[maxn];

int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	
	for (int i=1;i<=q;i++){
		int op,x,c;
		scanf("%d%d%d",&op,&x,&c);
		if (op==1){
			row[x]=c;
			lrow[x]=i;
		}else{
			col[x]=c;
			lcol[x]=i;
		}
	}
	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (lrow[i]>lcol[j]) printf("%d ",row[i]);
			else printf("%d ",col[j]);
		}
		printf("\n");
	}
    return 0;
}
```


---

## 作者：Binary_Lee (赞：0)

## [题面传送门](https://www.luogu.com.cn/problem/CF631B)

### 解决思路：

首先考虑到，一个点最终的情况只有三种可能：不被染色，被行染色，被列染色。

若一个点同时被行、列染色多次，显示出的是最后一次被染色的结果。所以我们可以使用结构体，对每一行、每一列记录下其最后一次被染色的颜色和时间。因为同行或同列反复染只有最后一次有影响，所以后来的直接覆盖之前的即可。

一个点的最终结果：若最后一次染行晚于最后一次染列，则显示最后一次染行的颜色，反之显示最后一次染列的颜色。

然后程序就很简单了。

### AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,op,a,b;
struct node{
	int val,time;
}x[5005],y[5005];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>op>>a>>b;
		op==1?x[a]={b,i}:y[a]={b,i};
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<(x[i].time<y[j].time?y[j].val:x[i].val)<<' ';
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：fengxiaoyi (赞：0)

## 解法一（模拟）
### 思路
输入 $x,y,z$，判断（其中 $mp_{i,j}$ 表示第 $i$ 行第 $j$ 列的兵种）：

- 若 $x=1$:
```cpp
for(int j=1;j<=m;j++){
	mp[y][j]=z;
}
```
- 若 $x=1$：
```cpp
for(int j=1;j<=n;j++){
	mp[j][y]=z;
}
```

最后依次输出 $mp_{i,j}$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int mp[5010][5010];
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		int x,y,z;
		cin>>x>>y>>z;
		if(x==1){
			for(int j=1;j<=m;j++){
				mp[y][j]=z;
			}
		}
		else{
			for(int j=1;j<=n;j++){
				mp[j][y]=z;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<mp[i][j]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```
加上去，TLE 了，要怎么优化呢？
## 解法二
可以对解法一进行一个优化。
### 思路
定义一个结构体 $v$，这个结构体包含两个变量：$a,t$。其中 $a$ 表示兵种，$t$ 表示时间。

用 $v$ 来定义两个数组：$l[5010],h[5010]$。$l$ 表示列，$h$ 表示行。

最后在输出时，做个判断（$i$ 表示第 $i$ 行，$j$ 表示第 $j$ 列）：
```cpp
if(h[i].t>l[j].t){
	cout<<h[i].a<<' ';
}
else{
	cout<<l[j].a<<' ';
}
```
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
struct{
	int a,t;
}l[5010],h[5010];
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		int x,y,z;
		cin>>x>>y>>z;
		if(x==1){
			h[y].a=z;
			h[y].t=i;
		}
		else{
			l[y].a=z;
			l[y].t=i;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(h[i].t>l[j].t){
				cout<<h[i].a<<' ';
			}
			else{
				cout<<l[j].a<<' ';
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

# 题意分析：

其实翻译说的还行，题目链接[走这里](https://www.luogu.com.cn/problem/CF631B)。只不过我还有一点小提示：

- 其实你只需要把它看成对一个矩阵进行染色就行了。

- 并不需要文件读写，翻译里说的是错的。（其实我在原文中真的没有发现要用文件读写！）

# 思路分析：

## Solution 1(TLE in 23th):

我们可以直接发现暴力是一种十分简单粗暴的方法，我们可以简单地运用一下。我们直接对涂色过程进行模拟，最大时间复杂度大概是 $O(k\max(m, n))$，但由于 $1 \leq m,n \leq 5000,1 \leq k \leq 100000$，所以最大时间是可以被卡到 $5 \times 10 ^ 8$ 的，所以很明显会被卡掉。代码见下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, flag, x, y, mp[5005][5005];
signed main()
{
	memset(mp, 0, sizeof(mp));
	cin >> n >> m >> k;
	while(k--)
	{
		cin >> flag >> x >> y;
		if(flag == 1)
			for(int i = 1; i <= m; i++)
				mp[x][i] = y;
		else
			for(int i = 1; i <= n; i++)
				mp[i][x] = y;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			cout << mp[i][j] << " ";
		cout << endl;
	}
	return 0;
}
```
## Solution 2(AC!!!):

于是我们要对算法进行优化。我们可以发现，每次操作不需要直接赋值，可以将操作的信息和时间存下来，在输出时输出最后一个覆盖到这个点的操作。这样时间复杂度就只有 $O(k + mn)$，完美通过评测。具体代码见下（没看懂的可以看注释）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5000 + 50;
int n, m, k, flag, x, y;
struct node
{
	int num, time;//存每次操作更改的数和时间
	node()
	{
		num = 0, time = -1;//初始化
	}
}l[N], h[N];//分别定义用于存行，列的更改信息。
inline int read()//没什么用的快读
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
void print(int x)//和没什么用的快输
{
	if(x < 0) x = -x;
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
signed main()
{
	n = read(), m = read(), k = read();
	for(int i = 1; i <= k; i++)
	{
		flag = read(), x = read(), y = read();
		if(flag == 1)
			h[x].num = y, h[x].time = i;//如果是行操作就更新到这一行的信息
		else
			l[x].num = y, l[x].time = i;//是列操作就更新这一列的信息
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			if(h[i].time > l[j].time)//如果行后覆盖这一个点，就输出行的更改信息。
				print(h[i].num), putchar(' ');
			else
				print(l[j].num), putchar(' ');//否则输出列的
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个 $n\times m$ 的网格图，你可以对其执行 $k$ 次操作，有以下两种：

- `1 r a`：将第 $r$ 行涂成颜色 $a$。
- `2 c a`：将第 $c$ 列涂成颜色 $a$。

如果有格子在涂色之前就已经被涂色了，那么原来的颜色将会被覆盖。

求最后所有格子上的颜色。

**数据范围：$1\leqslant n,m\leqslant 5000$，$1\leqslant n\times m\leqslant 10^5$，$1\leqslant k\leqslant 10^5$，$1\leqslant r\leqslant n$，$1\leqslant c\leqslant m$，$1\leqslant a\leqslant 10^9$。**
## Solution
直接暴力模拟肯定是不可取的，如何优化呢？我们不妨将整行和整列的信息存储，这些信息包含其被涂成的颜色和**被涂成该颜色时的操作编号**。

然后，在输出每一个格子的颜色时，我们就看是该格子所在的行是最后被涂色的还是该格子所在的列是最后被涂色的，这样就可以进一步确定该格子的颜色了。注意特判都没有涂色的情况。
## Code
```cpp
namespace Solution {
	const int N = 5007;
	int n, m, q, op, x, y;
	pii ansr[N], ansc[N];
	
	iv Main() {
		read(n, m, q);
		F(int, i, 1, n) F(int, j, 1, m) ansr[i] = ansc[j] = mp(0, 0);
		F(int, i, 1, q) {
			read(op, x, y);
			if(op == 1) ansr[x] = mp(y, i);
			else ansc[x] = mp(y, i);
		}
		F(int, i, 1, n) F(int, j, 1, m) {
			if(!ansr[i].fi && !ansc[j].fi) write(0);
			else if(ansr[i].se > ansc[j].se) write(ansr[i].fi);
			else write(ansc[j].fi);
			putchar(" \n"[j == m]);
		}
		return;
	}
}
```

---

