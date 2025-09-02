# Largest Submatrix

## 题目描述

现在你有一个有 $n$ 行，$m$ 列的矩阵，它的每个元素都是 `a`，`b`，`c`，`w`，`x`，`y`，`z`，中的一个。现在你可以进行无限次如下操作：

- 将 `w` 替换为 `a` 或 `b`。
- 将 `x` 替换为 `b` 或 `c`。
- 将 `y` 替换为 `a` 或 `c`。
- 将 `z` 替换为 `a` 或 `b` 或 `c`。

在你操作结束后，这个矩阵最大的全部元素都相同的子矩阵的元素个数最多是多少？

## 样例 #1

### 输入

```
2 4
abcw
wxyz```

### 输出

```
3```

# 题解

## 作者：ycy1124 (赞：4)

### 题意
有一个 $n \times m$ 的字符矩阵，所有的字符都可以转化为 $\tt a,b,c$ 这三种字符的任意两种或三种，求转换后所有元素全部相同的子矩阵的最大大小。
### 思路
~~不难看出，这题其实就是把 [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)跑三遍~~。

其实这题就是单调栈求最大子矩阵的板子题。

由于 $\tt x,y,z,w$ 都可以变成至少 $\tt a,b,c$ 其中的两个，所以不难知道，将所有的 $\tt x,y,z,w$ 都变成 $\tt a,b,c$ 的答案一定不会更劣。

我们可以先对于每一个位置，求出从这个位置往下延伸，分别能得到多少个连续的 $\tt a,b,c$，用 $h_{i,j}$ 来表示。

这样分别得到三个矩阵后，我们就可以考虑分别求出所有元素是 $\tt a,b,c$ 的最大子矩阵了。

首先了解一下单调栈的定义：单调栈就是指栈内所有元素都是单调递增或单调递减的。例如 ```1 2 5 10 100 1000``` 就是一个单调递增的数列。（单调递增与单调不降是有区别的，注意区分）

对于单调栈求最大子矩阵，我们用的是单调递增的栈。我们对于每一行遍历一遍 $j$，然后对于每个 $h_{i,j}$，重复执行这个操作直到栈中没有大于等于它的元素：首先弹出栈顶，将栈顶的宽度累加到 $js$ 上，然后更新一遍答案为栈顶的高度 $\times js$，当所有大于等于 $h_{i,j}$ 的弹完了以后，将 $h_{i,j}$ 与 $js+1$ 一起压入栈中。代码如下：
```cpp
int js=0;
while(!q.empty()&&h[i][j]<=q.top().h){
    ans=max(ans,q.top().h*(js+q.top().w));
    js+=q.top().w;
    q.pop();
}
q.push({h[i][j],1+js});
```
这段代码实现的是：对于栈中的每一个高度，假如当前压入栈中的高度比它低，那么以它为高的最大矩形是一定无法继续向后延伸的，于是就可以将它弹出，计算一遍以它为高的矩阵大小，然而进去的小的高度的矩形是可以向高的下面延伸的，所以宽度要增加上以高的高度为高的矩形的宽度，也就是累加的 $js$。

最后跑三遍单调栈分别求出全为 $\tt a,b,c$ 的子矩阵的最大大小，取个 $max$ 输出就行了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001][1001];
int h1[1001][1001];
int h2[1001][1001];
int h3[1001][1001];
struct Node{
	int h,w;
};
stack<Node>q;
int ans=0;
int main(){
	int n,m;
	while(cin>>n>>m){
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				h1[i][j]=h2[i][j]=h3[i][j]=0;
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){//统计往下延伸的数组
			for(int j=1;j<=m;j++){
				if(h1[i][j]==0&&a[i][j]!='x'&&a[i][j]!='b'&&a[i][j]!='c'){
					int js=0;
					int x=i;
					int y=j;
					while(a[x][y]!='x'&&x>=1&&a[x][y]!='b'&&a[x][y]!='c'){
						h1[x][y]=++js;
						x--;
					}
				}
			} 
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(h2[i][j]==0&&a[i][j]!='y'&&a[i][j]!='a'&&a[i][j]!='c'){
					int js=0;
					int x=i;
					int y=j;
					while(a[x][y]!='y'&&x>=1&&a[x][y]!='a'&&a[x][y]!='c'){
						h2[x][y]=++js;
						x--;
					}
				}
			} 
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(h3[i][j]==0&&a[i][j]!='w'&&a[i][j]!='b'&&a[i][j]!='a'){
					int js=0;
					int x=i;
					int y=j;
					while(a[x][y]!='w'&&x>=1&&a[x][y]!='b'&&a[x][y]!='a'){
						h3[x][y]=++js;
						x--;
					}
				}
			} 
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(q.empty()||h1[i][j]>q.top().h){//跑单调栈
					q.push({h1[i][j],1});
				}
				else{
					int js=0;
					while(!q.empty()&&h1[i][j]<=q.top().h){
						ans=max(ans,q.top().h*(js+q.top().w));
						js+=q.top().w;
						q.pop();
					}
					q.push({h1[i][j],1+js});
				}
			}
			int js=0;
			while(!q.empty()){
				ans=max(ans,q.top().h*(js+q.top().w));
				js+=q.top().w;
				q.pop();
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(q.empty()||h2[i][j]>q.top().h){
					q.push({h2[i][j],1});
				}
				else{
					int js=0;
					while(!q.empty()&&h2[i][j]<=q.top().h){
						ans=max(ans,q.top().h*(js+q.top().w));
						js+=q.top().w;
						q.pop();
					}
					q.push({h2[i][j],1+js});
				}
			}
			int js=0;
			while(!q.empty()){
				ans=max(ans,q.top().h*(js+q.top().w));
				js+=q.top().w;
				q.pop();
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(q.empty()||h3[i][j]>q.top().h){
					q.push({h3[i][j],1});
				}
				else{
					int js=0;
					while(!q.empty()&&h3[i][j]<=q.top().h){
						ans=max(ans,q.top().h*(js+q.top().w));
						js+=q.top().w;
						q.pop();
					}
					q.push({h3[i][j],1+js});
				}
			}
			int js=0;
			while(!q.empty()){
				ans=max(ans,q.top().h*(js+q.top().w));
				js+=q.top().w;
				q.pop();
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
``````
[AC 记录](https://www.luogu.com.cn/record/179117055)。

---

## 作者：e_zhe (赞：1)

### 题目链接

<https://www.luogu.com.cn/problem/P10965>

### 分析

和 [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147) 一题很像。

易于想到，给定矩阵最大的全部元素都相同的子矩阵的元素个数最多时，矩阵中一定只存在 ```a``` 或 ```b``` 或 ```c```。分别处理使 ```a``` 或 ```b``` 或 ```c``` 数量最多时的情况。

那么对于矩阵中的每一个位置，可以分别求出从当前位置向上全为相同字母的最大高度，记为 $maxheight_i$。处理完一行的高度后，还可以用单调栈求出每个位置左侧和右侧第一个高度小于当前高度的位置，记作 $posl_i, posr_i$。

那么就可以形成从 $posl_i + 1$ 到 $posr_i - 1$，高度为 $maxheight_i$ 的矩阵，即贡献为 $(posr_i - posl_i + 1) \times maxheight_i$。

在所有位置的贡献中取最大值即为答案。

细节内容见代码注释。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1005;
int n, m, pos_l[N], pos_r[N], max_ht[N][N][3]; char mp[N][N];

deque<int> que;

int main()
{
//	freopen(".in", "r", stdin), freopen(".out", "w", stdout);

	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

	for (; cin >> n >> m; )
	{
		for (int i = 1; i <= n; ++ i) cin >> mp[i] + 1;

		memset(max_ht, 0, sizeof max_ht); // 多测清空
		for (int i = 1; i <= n; ++ i) for (int j = 1; j <= m; ++ j) switch(mp[i][j])
		{
			// 分别处理每种情况，'a' -> 0，'b' -> 1，'c' -> 2
			case 'a': { max_ht[i][j][0] = 1 + max_ht[i - 1][j][0]; break; }
			case 'b': { max_ht[i][j][1] = 1 + max_ht[i - 1][j][1]; break; }
			case 'c': { max_ht[i][j][2] = 1 + max_ht[i - 1][j][2]; break; }
			case 'w': { max_ht[i][j][0] = 1 + max_ht[i - 1][j][0], max_ht[i][j][1] = 1 + max_ht[i - 1][j][1]; break; }
			case 'x': { max_ht[i][j][1] = 1 + max_ht[i - 1][j][1], max_ht[i][j][2] = 1 + max_ht[i - 1][j][2]; break; }
			case 'y': { max_ht[i][j][0] = 1 + max_ht[i - 1][j][0], max_ht[i][j][2] = 1 + max_ht[i - 1][j][2]; break; }
			case 'z': { max_ht[i][j][0] = 1 + max_ht[i - 1][j][0], max_ht[i][j][1] = 1 + max_ht[i - 1][j][1], max_ht[i][j][2] = 1 + max_ht[i - 1][j][2]; break; }
		}

		int ans = 0;
		for (int num = 0; num < 3; ++ num) for (int i = 1; i <= n; ++ i)
		{
			// 单调栈处理右侧
			max_ht[i][m + 1][num] = -1;
			for (int j = 1; j <= m + 1; ++ j)
			{
				for (; !que.empty() && max_ht[i][j][num] < max_ht[i][que.back()][num]; pos_r[que.back()] = j, que.pop_back());
				que.push_back(j);
			}

			// 单调栈处理左侧
			max_ht[i][0][num] = -1;
			for (int j = m; 0 <= j; -- j)
			{
				for (; !que.empty() && max_ht[i][j][num] < max_ht[i][que.back()][num]; pos_l[que.back()] = j, que.pop_back());
				que.push_back(j);
			}

			// 计算贡献
			for (int j = 1; j <= m; ++ j) ans = max(ans, max_ht[i][j][num] * (pos_r[j] - pos_l[j] - 1));
		}

		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：M_CI (赞：1)

### Part 0. 前言

今天老师上课讲这题，我们全机房看题时经过了如下情感变化：

第一眼：什么玩意儿，这么难。。

第二眼：woc，这不是简单题吗！！

我谔谔。

---

### Part 1. 正文

显然的，这题最后的答案一定是经过修改后由 `a` 或 `b` 或 `c` 的任意一种组成的矩阵的字符个数，因为本题中同种字符构成的最大矩阵只可能是如下 $2$ 种情况：

1. 矩阵直接由 `a` 或 `b` 或 `c` 组成。

2. 矩阵由 `w` 或 `x` 或 `y` 或 `z` 组成，则此时一定可以将该矩阵内的这些字符，甚至往外延伸一个矩阵的这些字符改为 `a` 或 `b` 或 `c` 得到更大的满足上一条的矩阵。

有[玉蟾宫](https://www.luogu.com.cn/problem/P4147)既视感了吧。

下为玉蟾宫的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,f[1010][1010],l[1010][1010][2],r[1010][1010][2],lt[1010][1010],ans;

int main () {
	cin>> n>> m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			char c;
			cin>> c;
			f[i][j]=c=='F'? 1: 0;
			r[0][j][1]=m+1;
		}
	r[0][m+1][1]=m+1;
	for (int i=1;i<=n;i++) {
		int cur=0;
		for (int j=1;j<=m;j++) {
			if (f[i][j]) l[i][j][0]=cur;
			else {
				l[i][j][1]=0;
				cur=j;
			}
		}
		cur=m+1;
		for (int j=m;j>=1;j--) {
			if (f[i][j]) r[i][j][0]=cur;
			else {
				r[i][j][1]=m+1;
				cur=j;
			}
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			if (f[i][j]) {
				lt[i][j]=lt[i-1][j]+1;
				l[i][j][1]=max (l[i-1][j][1],l[i][j][0]+1);
				r[i][j][1]=min (r[i-1][j][1],r[i][j][0]-1);
				ans=max (ans,(r[i][j][1]-l[i][j][1]+1)*lt[i][j]);
			}
		}
	cout<< 3*ans;
	return 0;
}
```

那我们是不是可以修改上述代码细节来做这一题呢？

没错，我们只用将上题中“将为 `F` 的位置标为 $1$ ，其余位置标为 $0$” 改为“将可以为 `a` 或 `b` 或 `c` 的位置标为 $1$，其余位置标为 $0$”，其余不变即可。

下为本题代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,f[1010][1010],l[1010][1010][2],r[1010][1010][2],h[1010][1010];
char c[1010][1010];

int get (char ct,char ca,char cb,char cc) {
	memset (f,0,sizeof (f));
	memset (l,0,sizeof (l));
	memset (r,0,sizeof (r));
	memset (h,0,sizeof (h));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			f[i][j]=c[i][j]==ct||c[i][j]==ca||c[i][j]==cb||c[i][j]==cc? 1: 0;
			r[0][j][1]=m+1;
		}
	r[0][m+1][1]=m+1;
	for (int i=1;i<=n;i++) {
		int rs=0;
		for (int j=1;j<=m;j++) {
			if (f[i][j]) l[i][j][0]=rs;
			else {
				l[i][j][1]=0;
				rs=j;
			}
		}
		rs=m+1;
		for (int j=m;j>=1;j--) {
			if (f[i][j]) r[i][j][0]=rs;
			else {
				r[i][j][1]=m+1;
				rs=j;
			}
		}
	}
	int rs=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			if (f[i][j]) {
				h[i][j]=h[i-1][j]+1;
				l[i][j][1]=max (l[i-1][j][1],l[i][j][0]+1);
				r[i][j][1]=min (r[i-1][j][1],r[i][j][0]-1);
				rs=max (rs,(r[i][j][1]-l[i][j][1]+1)*h[i][j]);
			}
		}
	return rs;
}

int main () {
	while (cin>> n>> m) {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				cin>> c[i][j];
		cout<< max ({get ('a','w','y','z'),get ('b','w','x','z'),get ('c','x','y','z')})<< "\n";
	}
	return 0;
}
```

---

### Part2. 后记

好题。

---

## 作者：z_yq (赞：1)

# 题面意思
题面讲的很清楚了，这里不想再多说了。
# 思路
这道题目的思路很简单，~~我们的目标是题解区最短~~，首先我们可以看我们要使那个字母成为最大的矩阵。我们肯定不是 `w,x,y,z` 因为这几个字母都可以替换成基本字母，即 `a,b,c` 所以我们可以枚举把所有的 `w,y,z` 全都替换成 `a`，同时其他字母同理，这样我们就可以枚举到底是哪个字母的子矩阵最大了。由于 $n$ 不大，所以我们可以直接单调栈，即[玉蟾宫](https://www.luogu.com.cn/problem/P4147)这道题目了，剩下的照着板子写就可以了。
# 代码
这道题目的代码实现很简单，就不放出来了。

---

## 作者：mirance2025 (赞：0)

废话不说勒，先把题目读 3 遍。
### Solution
最大子矩阵法，即悬线法。
与单调栈做法相比，悬线法对新手更为友好。另外，本题为蓝书 dp 一章的练习题，比起单调栈，悬线法更符合该章主题。

容易想到的思路是把 $w, x, y, z$ 均替换为其能够替换的字母，让矩形中只有 $a, b, c$ 三种颜色，然后跑悬线法模板即可。

但容易证明这种思想是不够严谨的。

可以发现，本题中字符的相等关系不具有传递性。例如对单个字符进行比较时，$w = x, x = y$，但是当 $wxy$ 在矩形中连续出现时，三者就不可能全都相等。样例输入中就出现了这种情况。

因此考虑在传统悬线法的基础上做一些改进。不妨将每一个待扩展的 $w, x, y, z$ 先后作为 $a, b, c$ 使用并扩展，比较将当前字符替换为哪一个字符时，可以令扩展出的面积最大化。

换一种说法，我们可以增加悬线的数量，将悬线由一条扩充至三条，对每个字符，分别记录将其作为 $a, b, c$ 能向上扩展的最大高度，并分别按传统悬线法的方式扩展记录 $l, r$。时间复杂度 $O(nm)$。

### 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[1010][1010],b[1010][1010],c[1010][1010],ans,n,m,l[1010],r[1010];
char C;
int Max(int a,int b){return a>b?a:b;}
char getch(){
    char ch=getchar();
    while(ch!='a'&&ch!='b'&&ch!='c'&&ch!='w'&&ch!='x'&&ch!='y'&&ch!='z')
        ch=getchar();
    return ch;
}
bool LarMat(){
    ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            C=getch();
            if(C=='a'||C=='w'||C=='y'||C=='z')a[i][j]=a[i-1][j]+1;
            else a[i][j]=0;
            if(C=='b'||C=='x'||C=='w'||C=='z')b[i][j]=b[i-1][j]+1;
            else b[i][j]=0;
            if(C=='c'||C=='x'||C=='y'||C=='z')c[i][j]=c[i-1][j]+1;
            else c[i][j]=0;
        }
        a[i][0]=a[i][m+1]=-1;
        for(int j=1;j<=m;j++){
            l[j]=j;
            while(a[i][l[j]-1]>=a[i][j])l[j]=l[l[j]-1];
        }
        for(int j=m;j>=1;j--){
            r[j]=j;
            while(a[i][r[j]+1]>=a[i][j])r[j]=r[r[j]+1];
            ans=Max(ans,(r[j]-l[j]+1)*a[i][j]);
        }
        b[i][0]=b[i][m+1]=-1;
        for(int j=1;j<=m;j++){
            l[j]=j;
            while(b[i][l[j]-1]>=b[i][j])l[j]=l[l[j]-1];
        }
        for(int j=m;j>=1;j--){
            r[j]=j;
            while(b[i][r[j]+1]>=b[i][j])r[j]=r[r[j]+1];
            ans=Max(ans,(r[j]-l[j]+1)*b[i][j]);
        }
        c[i][0]=c[i][m+1]=-1;
        for(int j=1;j<=m;j++){
            l[j]=j;
            while(c[i][l[j]-1]>=c[i][j])l[j]=l[l[j]-1];
        }
        for(int j=m;j>=1;j--){
            r[j]=j;
            while(c[i][r[j]+1]>=c[i][j])r[j]=r[r[j]+1];
            ans=Max(ans,(r[j]-l[j]+1)*c[i][j]);
        }
    }
    printf("%d\n",ans);
    return true;
}
int main(){
    while(cin>>n>>m)LarMat();
}
```

---

