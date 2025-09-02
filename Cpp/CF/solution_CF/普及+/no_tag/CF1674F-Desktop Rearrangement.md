# Desktop Rearrangement

## 题目描述

Ivan 让你帮他重新安排他的桌面。桌面可以表示为一个大小为 $n \times m$ 的矩形矩阵，由字符 "." （表示桌面的空单元格）和 "*" （表示图标）组成。

如果桌面上的所有图标都占据一些完整列的前缀，并且可能占据下一列的前缀（并且在该图之外没有图标），则该桌面是"良好"的。
换句话说，一些列将被图标填充，并且下一列（在最后一个完整列之后）的一些单元格也将被图标填充（并且桌面上的所有图标都属于这个图），则该桌面是"良好"的。
这与现实生活中的图标排列几乎相同。

在一次移动中，你可以将一个图标移动到桌面上的任何空白单元格。

Ivan 喜欢在他的桌面上添加一些图标或将其删除，因此他要求你回答 $q$ 个问题：添加或删除一个图标后，使桌面变得良好所需的最少移动次数是多少？

请注意，查询是永久性的，会更改桌面的状态。

## 样例 #1

### 输入

```
4 4 8
..**
.*..
*...
...*
1 3
2 3
3 1
2 3
3 4
4 3
2 3
2 2```

### 输出

```
3
4
4
3
4
5
5
5```

## 样例 #2

### 输入

```
2 5 5
*...*
*****
1 3
2 2
1 3
1 5
2 3```

### 输出

```
2
3
3
3
2```

# 题解

## 作者：OJ_killer (赞：3)

[CF1674F](https://www.luogu.com.cn/problem/CF1674F)

模拟好题

我们可以用预处理的方法出在初始状况下共有多少个 $1(cn t)$，以及有多少个 $1(count)$ 处于不需要操作的范围内，则最终答案为 $cnt−count$，由此所有询问可以通过 $O(1)$ 的时间复杂度解决。

**主要考虑两个问题**：


------------

$1.$ 添加或删除操作的点是否在不需要操作的范围内（需要首先更新范围）。

$2.$ 增加或删除操作后对排列范围的末尾是否有影响。对于问题 $2$，进行删除操作和增加操作时需要在范围更改前判断。

$ code $
```cpp
#include <bits/stdc++.h> //万能头
using namespace std;

char op;
int n, m, q, cnt;
int t[1001][1001];

signed main() {
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> op;
			if (op == '.')
				t[i][j] = 0;
			else
				t[i][j] = 1, cnt++;
		}
	}
	int a = cnt / n;
	int b = cnt % n;
	if (b == 0 && a != 0) {
		a--;
		b = n;
	}
	a++;
	int count = 0;
	for (int j = 1; j < a; j++)
		for (int i = 1; i <= n; i++)
			if (t[i][j])
				count++;
	for (int i = 1; i <= b; i++)
		if (t[i][a])
			count++;
	for (int i = 1; i <= q; i++) {
		int x, y;
		cin >> x >> y;
		if (t[x][y]) { //删除操作
			cnt--;
			if (t[b][a])
				count--;
			t[x][y] = 0;
			b--;
			if (b == 0) {
				b = n;
				a--;
			}
			if (y < a || (y == a && x <= b))
				count--;
		} else { //增加操作
			cnt++;
			b++;
			if (b == n + 1) {
				b = 1;
				a++;
			}
			if (t[b][a])
				count++;
			t[x][y] = 1;
			if (y < a || (y == a && x <= b))
				count++;
		}
		cout << cnt - count << endl;
	}
	return 0;
}//完美结束

---

## 作者：I_am_Accepted (赞：3)

### Preface

「看起来恐怖」的题。

### Analysis

若将桌面按**从左到右，从上到下**的顺序标号，则最终被放图标的位置一定是**前缀**.

所以动态维护**图标个数**和**不在此前缀的图标个数**即可，答案为后者。

还是说具体一点吧……

若当前新加入一个图标，位置为 $y$，当前归位前缀为 $[1,x]$，当前答案为 $ans$。

步骤依次进行：

1. 若 $y>x$，则 $ans$ 加 $1$。

2. $x$ 加 $1$。

3. 若 $x$ 位置有图标，则 $ans$ 减 $1$。

删掉一个图标与之类似；

1. 若 $y>x$，则 $ans$ 减 $1$。

1. 若 $x$ 位置有图标，则 $ans$ 加 $1$。

2. $x$ 减 $1$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define N 1002
int n,m,q,tot=0,a[N*N],ans=0;
char ch;
inline int num(int x,int y){return (y-1)*n+x;}
signed main(){IOS;
	cin>>n>>m>>q;
	For(i,1,n){
		For(j,1,m){
			cin>>ch;
			a[num(i,j)]=(ch=='*');
			tot+=a[num(i,j)];
		}
	}
	For(i,tot+1,n*m) ans+=a[i];
	int x,y,z;
	while(q--){
		cin>>x>>y;
		z=num(x,y);
		a[z]^=1;
		if(a[z]){//add
			if(z>tot) ans++;
			tot++;
			if(a[tot]) ans--;
		}else{//del
			if(z>tot) ans--;
			if(a[tot]) ans++;
			tot--;
		}
		cout<<ans<<endl;
	}
return 0;}
```

---

## 作者：CGDGAD (赞：2)

## CF1674F Desktop Rearrangement

模拟题。

### 算法

问题相当于询问有几个图标需要移动。首先求出原状态下有几个需要移的，接下来考虑变化。

- 如果是从没有变成有的：
    - 在操作**后**的边界上的那个点（如果存在）不用移了，答案减一（如果操作的就是这个点，**忽略**这一条，对答案没有影响）。
    - 另外如果改变的这个点超过了操作**后**的边界，那么就需要费力气移它，答案加一。

- 如果是从有变成没有的：
    - 操作**前**的守门员（如果存在）被踢了，需要移的加一（如果操作的就是这个点，**忽略**这一条，对答案没有影响）。
    - 如果本来就超出了操作**前**的范围，需要移的减一，否则不变。

由上分类讨论可见，`.` 变 `*` 和 `*` 变 `.` 对答案的影响是不同的，尤其体现在操作前边界或是操作后边界的区别。

### 实现

考虑将矩阵转为序列，在序列上操作方便得多。

```cpp
#define trans(i, j) (((j) - 1) * n + (i))
int n, m, q;
char map[1000001];

int main() {
    std::cin >> n >> m >> q;
    int cnt = 0;
    for (int i = 1, k = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> map[trans(i, j)];
            if (map[trans(i, j)] == '*') ++cnt;
        }
    }
    int ans = cnt;
    for (int i = 1; i <= cnt; ++i)
        if (map[i] == '*')
            --ans;

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        int idx = trans(x, y);
        if (map[idx] == '.') {
            ++cnt;
            if (map[cnt] == '*') --ans;
            if (idx > cnt) ++ans;
            map[idx] = '*';
        } else {
            map[idx] = '.';
            if (idx > cnt) --ans;
            if (map[cnt] == '*') ++ans;
            --cnt;
        }
        std::cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF1674F](https://www.luogu.com.cn/problem/CF1674F)

* **【解题思路】**

我们考虑将桌面的格子竖着编号：

$$
\begin{matrix}
1&n+1&2n+1&\cdots&(m-1)n+1\\
2&n+2&2n+2&\cdots&(m-1)n+2\\
3&n+3&2n+3&\cdots&(m-1)n+3\\
\vdots&\vdots&\vdots&\ddots&\vdots\\
n&2n&3n&\cdots&mn
\end{matrix}
$$

设当前桌面上有 $n$ 个图标（显然容易维护），我们的目标就是把图标移到编号为 $1\sim n$ 的格子里。显然已经在这个范围里的 $x$ 个就不用动，还有 $n-x$ 个要移动，即答案为 $n-x$。空格看做 $0$，有图标的格子看做 $1$，则 $x$ 即为 $1\sim n$ 的前缀和。

于是就是一个树状数组的板子。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<int,1000001> tree_arr;
array<array<char,1000>,1000> grid;

void update(int idx,int lim,int val)
{
	while(idx<=lim)
		tree_arr[idx]+=val,idx+=idx&-idx;
}

int prefix_sum(int idx)
{
	int result=0;
	while(idx)
		result+=tree_arr[idx],idx-=idx&-idx;
	return result;
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int line,row,cnt,total=0;
	cin>>line>>row>>cnt;
	for(int i=0;i<line;i++)
		for(int j=0;j<row;j++)
			cin>>grid[i][j],grid[i][j]=='*'&&(update(j*line+i+1,line*row,1),++total);
	while(cnt--)
	{
		int targ_x,targ_y;
		cin>>targ_x>>targ_y;
		if(grid[targ_x-1][targ_y-1]=='*')
			grid[targ_x-1][targ_y-1]='.',--total,update(targ_y*line-line+targ_x,line*row,-1);
		else
			grid[targ_x-1][targ_y-1]='*',++total,update(targ_y*line-line+targ_x,line*row,1);
		cout<<total-prefix_sum(total)<<'\n';
	}
	return 0;
}


```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1674F)

## 思路

这题可以用树状数组模拟实现。

因为树状数组处理一维很方便，而本题又不涉及二维的查询，那么我们直接开一维的树状数组即可。

注意本题是要求第一**列**排满后再进第二**列**，所以我们考虑把这个图旋转。把二维坐标 $(i,j)$ 转化为一维坐标 $(j-1)\times n+i$。

读入数据后，如果这个位置是 `*`，那么将这个位置的标记设为 $1$，计数器**增加**后把树状数组的同位置 $+1$。

每次查询时分类讨论：

- 如果这个点是 `*`，那么将这个位置的标记设为 $1$，计数器**增加**后把树状数组的同位置 $+1$。

- 否则，将这个位置的标记设为 $0$，计数器**减少**后把树状数组的同位置 $-1$。

每次查询时输出总计数器（图标）数量减去从 $(1,1)$ 开始的**题意中先向下再向右**的图标数量即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,m,q,a[N*N],c[N*N],x,y,cnt,pos;
char ch;
int lowbit(int x){return (x&-x);}
void add(int x,int k){
	for(int i=x;i<=n*m;i+=lowbit(i))c[i]+=k;
}
int find(int x){
	int sum=0;
	for(int i=x;i>0;i-=lowbit(i))sum+=c[i];
	return sum;
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>ch;
			if(ch=='*'){
				++cnt;
				pos=(j-1)*n+i;//转换坐标。
				a[pos]=1;
				add(pos,1);
			}
		}
	}
	while(q--){
		scanf("%d%d",&x,&y);
		pos=(y-1)*n+x;//转换坐标。
		if(a[pos]){//有图标，删除。
			cnt--;
			add(pos,-1);
			a[pos]=0;
		}
		else{//没图标，添加。
			cnt++;
			add(pos,1);
			a[pos]=1;
		}
		printf("%d\n",cnt-find(cnt));
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/103882134)

---

## 作者：yeshubo_qwq (赞：0)

思路：

题意很清晰，但要注意添加和删除文件的操作会一直保留，而移动文件位置的操作则不会保留。

计算答案也很简单，应该存在文件的位置有几处空的，答案就是几。

接着，你或许想到了暴力。[代码](https://www.luogu.com.cn/paste/w3wvhgdl)。

然后……[超时！](https://www.luogu.com.cn/record/75151245)

观察代码，发现每次求答案的地方非常慢，对每一列做前缀和，进行优化。

不要忘记更新前缀和。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,i,j,tot,s1,ans,f[1005][1005],x,y;
char a[1005][1005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>T;
	for (i=1;i<=n;i++) cin>>a[i]+1;
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++)
			if (a[j][i]=='*') f[i][j]=f[i][j-1]+1,tot++;
			else f[i][j]=f[i][j-1];
	}
	while (T--){
		cin>>x>>y;
		if (a[x][y]=='.'){
			tot++;a[x][y]='#';
			for (j=x;j<=n;j++)
				f[y][j]++;
		}
		else{
			tot--;a[x][y]='.';
			for (j=x;j<=n;j++)
				f[y][j]--;
		}
		s1=tot;ans=0;
		for (i=1;i<=m;i++)
			if (n<s1){
				s1-=n;
				ans+=(n-f[i][n]);
			}
			else{
				ans+=(s1-f[i][s1]);
				break;
			}
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

