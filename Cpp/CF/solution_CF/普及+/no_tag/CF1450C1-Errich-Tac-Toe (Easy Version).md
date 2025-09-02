# Errich-Tac-Toe (Easy Version)

## 题目描述

The only difference between the easy and hard versions is that tokens of type O do not appear in the input of the easy version.

Errichto gave Monogon the following challenge in order to intimidate him from taking his top contributor spot on Codeforces.

In a Tic-Tac-Toe grid, there are $ n $ rows and $ n $ columns. Each cell of the grid is either empty or contains a token. There are two types of tokens: X and O. If there exist three tokens of the same type consecutive in a row or column, it is a winning configuration. Otherwise, it is a draw configuration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450C1/39afc6239351b009b5f556b0fc6f685f7842a873.png) The patterns in the first row are winning configurations. The patterns in the second row are draw configurations. In an operation, you can change an X to an O, or an O to an X. Let $ k $ denote the total number of tokens in the grid. Your task is to make the grid a draw in at most $ \lfloor \frac{k}{3}\rfloor $ (rounding down) operations.

You are not required to minimize the number of operations.

## 说明/提示

In the first test case, there are initially three 'X' consecutive in the second row and the second column. By changing the middle token to 'O' we make the grid a draw, and we only changed $ 1\le \lfloor 5/3\rfloor $ token.

In the second test case, we change only $ 9\le \lfloor 32/3\rfloor $ tokens, and there does not exist any three 'X' or 'O' consecutive in a row or column, so it is a draw.

In the third test case, we change only $ 3\le \lfloor 12/3\rfloor $ tokens, and the resulting grid is a draw.

## 样例 #1

### 输入

```
3
3
.X.
XXX
.X.
6
XX.XXX
XXXXXX
XXX.XX
XXXXXX
XX.X.X
XXXXXX
5
XXX.X
.X..X
XXX.X
..X..
..X..```

### 输出

```
.X.
XOX
.X.
XX.XXO
XOXXOX
OXX.XX
XOOXXO
XX.X.X
OXXOXX
XOX.X
.X..X
XXO.O
..X..
..X..```

# 题解

## 作者：Rainy7 (赞：10)

- **分析**

  考虑对矩阵**染色**。

  对于 $s_{i,j}$ 染色为 $(i+j) \mod 3$ 。
  
  显然，不可能存在连续 3 个（不包括斜边）格子同颜色。
  
  所以只要将同种颜色的格子改为 $\text{O}$ 就可以直接平局。
  
  设不为空的格子数量为 $m$ 。
  
  若翻转颜色为 $0$ 要翻转 $c_0$ 次，颜色为 $1$ 要翻转 $c_1$ 次，颜色为 $2$ 要翻转 $c_2$ 次。、
  
  因为 $c_0+c_1+c_2=m$ 。
  
  故 $\min(c_0,c_1,c_2)=\left\lfloor\dfrac{m}{3}\right\rfloor$
  
  所以对于本题，对于不为空的格子，**选择出现次数最小的颜色所对应的非空格子全部改为** $\text{O}$ 即可解决本题。
  
  最后，**多测不清空，爆零两行泪** （没错说的就是我这个屑）。
  

------------

  
- **代码**

``` cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int T,n;
char s[305][305],s2[305][305],s3[305][305];
int main()
{	scanf("%d",&T);
	while(T--)
	{	scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{	scanf("%s",s[i]+1);
			for(int j=1;j<=n;j++)
				s2[i][j]=s3[i][j]=s[i][j];
		}
		int m=0,cnt=0,cnt2=0,cnt3=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{	if(s[i][j]!='X')continue;
				m++;
				if((i+j)%3==0)cnt++;
				if((i+j)%3==1)cnt2++;
				if((i+j)%3==2)cnt3++;
			}
		int x=min(cnt,min(cnt2,cnt3));
		if(x==cnt)
		{	for(int i=1;i<=n;i++)
			{	for(int j=1;j<=n;j++)
				{	if(s[i][j]!='X')printf(".");
					else if((i+j)%3==0)printf("O");
					else printf("X");
				}
				printf("\n");
			} 
		}
		else if(x==cnt2){
			for(int i=1;i<=n;i++)
			{	for(int j=1;j<=n;j++)
				{	if(s[i][j]!='X')printf(".");
					else if((i+j)%3==1)printf("O");
					else printf("X");
				}
				printf("\n");
			} 
		}
		else if(x==cnt3){
			for(int i=1;i<=n;i++)
			{	for(int j=1;j<=n;j++)
				{	if(s[i][j]!='X')printf(".");
					else if((i+j)%3==2)printf("O");
					else printf("X");
				}
				printf("\n");
			} 
		}
	}
	return 0;
}
```

------------

$$\text{by Rainy7}$$

---

## 作者：2huk (赞：4)

> 给定 $n \times n$ 的网格，由 $\texttt X$ 和 $\texttt .$ 组成。请构造一种方案，将其中 $\le \lfloor k/3 \rfloor$ 个 $\texttt X$ 改成 $\texttt O$，其中 $k$ 是 $\texttt X$ 的总数，使得每行、每列中都不存在连续的三个 $\texttt X$。

考虑对棋盘染色。将 $(i, j)$ 染成 $(i+j) \bmod 3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/g7tvzdbn.png)

那么每行、每列的任意连续 $3$ 个格子的颜色都不同。

同时注意到，三种颜色中，一定存在至少一种颜色的出现次数 $\le \lfloor k / 3 \rfloor$。

令这种颜色为 $x$。那么只要把棋盘中，所有颜色为 $x$ 的，且字符为 $\texttt X$ 改成 $\texttt O$，就是一种合法方案。

<https://codeforces.com/contest/1450/submission/291151910>

---

## 作者：fishing_cat (赞：2)

### 思路

读完题，可以发现和传统五子棋获胜条件不一样，额，三子棋。这道题不考虑斜着会获胜的情况。所以可以直接将棋子每一斜列改变，然后去破坏获胜状态。考虑选那几列最优，首先中间没有间隔一定是不可行的，在中间隔一列改一次的话，也完全没隔两列优。自然隔三列以上一定是不可行的。最终，隔两列改一次是最优的。

那么问题就转变为了，有一个三色的棋盘，长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/eekj1m4a.png)

然后有三种操作方案。将红色位置的棋子都替换掉，假设一共需要换 $$R$$ 个；或者将蓝色位置的棋子都替换掉，假设需要换 $$B$$ 个；或者将黄色位置的棋子都替换掉，假设需要换 $$Y$$ 个。

最后考虑满足题目中要求的次数上限 $$\left \lfloor \frac{k}{3} \right \rfloor $$。因为 $$R + B + Y = k$$ 是一定会成立的，所以 $$\min(R,B,Y)$$ 一定是小于等于 $$\left \lfloor \frac{k}{3} \right \rfloor $$ 的。所以只要选择三方案中修改次数最小的就可以了。

代码一想就不难写，模拟就完了。

### code

```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
const ll N = 320;
const ll inf = 2e18;
using namespace std;
/*快读省了*/
ll t, n, mp[N][N], ans, kkk;
char s;

il void get(ll head) {
	ll res = 0, lp = head;
	for (int i = 1; i <= n; i++) {
		for (int j = head; j <= n; j+=3) // 跑斜向
			if (mp[i][j] == 1) res++;
		head = head % 3 + 1;	
	}	
	if (res < ans) kkk = lp; // 更新最优解
	ans = min(ans, res);
}

int main() {
	read(t);
	while (t--) {
		read(n);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= n; j++) {
				cin >> s;
				if (s == '.') mp[i][j] = 0;
				else mp[i][j] = 1;
			}

		ans = inf; 
		get(1); get(2); get(3); // 3种情况
		for (int i = 1; i <= n; i++) { // 更新答案
			for (int j = kkk; j <= n; j+=3) 
				if (mp[i][j] == 1) mp[i][j] = 2;
			kkk = kkk % 3 + 1;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (mp[i][j] == 0) printf(".");
				if (mp[i][j] == 1) printf("X");
				if (mp[i][j] == 2) printf("O");
			} puts("");
	}
	return 0;// 完结撒花~~~
}
```

---

## 作者：nztyz (赞：2)

对于每个格子按照$(i+j)\%3$分成$0,1,2$三组,      

而如果将其中一组中的$X$改为$O$,这样一定能保证不存在连续的$3$个$X$

设$cnt_i$为每一组中$X$的数量,则$cnt_0 + cnt_1 + cnt_2 == K$,

因此一定会有一个值满足$cnt_i <= k/3$
所以找到cnt值最小的那个组,然后将其改为$O$就行

```c
#include <bits/stdc++.h>
using namespace std;
string s[400];
int n,m;
void solve()
{
    cin >> n;
    int cnt[3] = {0};
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(s[i][j] == 'X') {
                cnt[(i+j)%3]++;
            }
        }
    }
    int val = min_element(cnt,cnt+3) - cnt;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(s[i][j] == 'X' && (i+j)%3 == val)
            s[i][j] = 'O';
        }
    }
    for(int i = 0; i < n; i++) {
        cout << s[i] << endl;
    }
}
int main(){
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
对矩阵进行 $(i+j)\bmod3$ 编号，只要改变其中一种颜色的所有 X 棋子就不会出现连续 $3$ 个行列同色。

记得选最小的，最小的那个肯定 $\le\lfloor\frac k3\rfloor$。
# 代码
```cpp
# include <bits/stdc--.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
# define print(a) for (int i = 0; i < n; ++ i) cout << a[i] << '\n'; //我懒
int t, n, tot1, tot2, tot3;
string a[305], b[305], c[305];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		tot1 = tot2 = tot3 = 0;
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i];
			c[i] = b[i] = a[i];
			for (int j = 0; j < n; ++ j)
				if (a[i][j] == 'X')
					if ((i + j) % 3 == 0)
						a[i][j] = 'O', ++ tot1;
					else if ((i + j) % 3 == 1)
						b[i][j] = 'O', ++ tot2;
					else
						c[i][j] = 'O', ++ tot3;
		}
		if (tot1 <= tot2 && tot1 <= tot3)
			print (a)
		else if (tot2 <= tot1 && tot2 <= tot3)
			print (b)
		else
			print (c)
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：1)

由于只有 `X`，那么只需要替换成 `O` 即可。

贪心地，两个 `O` 之间应该是有两个 `X` 的，也就是说，如果 $(i,j)$ 选择，那么我们下次选择应该是 $(i,j+3)$ 和 $(i+3,j)$，发现它们 $\bmod3$ 的结果都是 $(i+j)\bmod3$。

因为数量 $\le\lfloor\dfrac{k}{3}\rfloor$，那么我们只需要把 $(i+j)\bmod3=0$ 的 `X` 变成 `O` 即可。

---

## 作者：Graph_Theory (赞：0)

### 思路

题目中要求删去的数量要小于等于 $ \left \lfloor \frac{k}{3} \right \rfloor $，不难发现，将所有连续大于 $2$ 的删除任意一个都满足，但是新增的圆圈也会连续大于 $2$ 个，也就是说我们应尽量斜着摆放圆圈。

而由于我们需要在连续大于 $2$ 个的位置至少摆放一个，所以我们考虑对图做如下的标记。

![](https://www.helloimg.com/i/2025/01/14/67865bb6de835.png)
我们对每一个位置都计算他的 $i+j$ 此时斜着的所有数都是一样的数，再往右边的斜线与原来的 $i+j$ 正好多一，最后在对 $3$ 取模就可以得到下面图中的标记。
![无标题.png](https://www.helloimg.com/i/2025/01/14/67865efa387c1.png)

不难发现，对于纵向或者横向的三连块，必定包括这三种颜色，由于这张图的特性，必定有一种颜色的数量小于等于 $ \left \lfloor \frac{k}{3} \right \rfloor $ 所以我们就可以在这三种颜色中任选一种填充为圆圈，这里我选择了叉最少的颜色。




### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

char a[400][400];
int sum[4],n;

void todo()
{
	memset(sum,0,sizeof(a));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='X') sum[(i+j)%3+1]++;
		}
	}
	int tmp=(sum[3]<sum[(sum[2]<sum[1]?2:1)]?3:(sum[2]<sum[1]?2:1));
	for (int i=1;i<=n;i++) 
	{
		for (int j=1;j<=n;j++) 
		{
			if((i+j)%3+1==tmp&&a[i][j]=='X') a[i][j]='O';
			cout <<a[i][j];
		}
		cout<<endl;
	}
}
int main(){int T;cin>>T;while(T--){todo();}return 0;}
```

---

## 作者：1234567890sjx (赞：0)

考虑将格子做三色染色，$(i,j)$ 格子的颜色为 $(i+j)\bmod 3$。根据鸽巢原理可以知道肯定存在一种颜色使得该颜色的格子数不超过 $\frac{k}{3}$。显然把所有该种个颜色的格子全部染色后，不存在连续长度为 $3$ 的序列使得三个格子全都是 `o`。因此时间复杂度为 $O(nm)$，可以通过。

```cpp
char s[2010][2010];
void run() {
    int T = read();
    while (T--) {
        int n = read(), buc[3] = {0, 0, 0};
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                cin >> s[i][j];
                if (s[i][j] == 'X')
                    ++buc[(i + j) % 3];
            }
        int id = 0;
        for (int i = 1; i < 3; ++i)
            if (buc[i] < buc[id]) id = i;
        for (int i = 1; i <= n; ++i, cout << '\n')
            for (int j = 1; j <= n; ++j)
                if ((i + j) % 3 == id) {
                    if (s[i][j] == 'X') cout << "O";
                    else cout << s[i][j];
                } else cout << s[i][j];
    }
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

如果去考虑 `O` 的摆放，再考虑那些改为 `X`，这样不好思考，实现也很不好写，所以我们可以考虑构造一种通解。

![](https://cdn.luogu.com.cn/upload/image_hosting/0j3enxyq.png)

如果将上图所有标红的位置都放上 `X`，那么无论 `O` 如何放，都不可能胜利，而 `X` 因为原本就没有，所以摆上后也不可能胜利。

不过，因为更改的次数不能超过棋子总数的 $\frac 1 3$，所以这种方案不一定满足条件（比如 `O` 全放在红格子上，那么更改次数就是总棋子数）。

实际上，图中的方式只是一种，整体向上挪一格和挪两个也是一种方式，如果一格棋子的位置是 $(i,j)$，那么可以根据 $(i+j)\bmod 3$ 的值，分为三类，将一类的棋子全部改为 `X` 就是一种通解。

显然，三种更改方式可以覆盖所有的棋子，那么根据抽屉原理，至少有一种方式，更改的棋子少于总棋子的 $\frac 1 3$。

所以我们只需要直接统计三种方式各需要改多少个棋子，然后选择一种符合条件的即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,num[3],sum,xz;
char ch[305][305];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),num[0]=num[1]=num[2]=sum=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%s",ch[i]+1);
			for(int j=1;j<=n;++j) if(ch[i][j]=='X') ++num[(i+j)%3],++sum;//统计每种方式需要改的棋子
		}
		if(num[0]<=sum/3) xz=0;
		if(num[1]<=sum/3) xz=1;
		if(num[2]<=sum/3) xz=2;
		for(int i=1;i<=n;++i){for(int j=1;j<=n;++j) if((i+j)%3==xz&&ch[i][j]=='X') printf("O");else printf("%c",ch[i][j]);puts("");}//对应改即可
	}
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：0)

### 思路

只会出现一种棋子，而且只算横着和竖着的 $3$ 个，而且操作次数只需要 $\le \lfloor \frac{k}{3} \rfloor$，那么可以考虑将整个矩阵切成 $3$ 部分，将一个部分的 `X` 全部改成 `O`，但是怎么分呢？

显然，横着竖着都有可能切不到一个可判定胜利的情况，那么考虑直接斜着切，切成一条一条的，由于有三个部分，改一个部分，留下两个部分，每一条之间最多隔了两个棋子，不可能胜利，而且分为三个部分，总操作数为 $k$，那么操作次数最少的部分的操作次数一定满足 $\le \lfloor \frac{k}{3} \rfloor$。


### 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
const int maxn=305;
int t,n,cnt[3];
char c[maxn][maxn];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",c[i]+1);
		}
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][j]!='.')cnt[(i+j)%3]++;
			}
		}
		int id=0,ans=INT_MAX;
		for(int i=0;i<3;i++){
			if(ans>cnt[i]){
				id=i;
				ans=cnt[i];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][j]!='.'&&(i+j)%3==id){
					if(c[i][j]=='X')putchar('O');
					else 			putchar('X');
				}else 				putchar(c[i][j]);
			}
			puts("");
		}
	}
}
```

---

