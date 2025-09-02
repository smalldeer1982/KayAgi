# Little Artem

## 题目描述

Young boy Artem tries to paint a picture, and he asks his mother Medina to help him. Medina is very busy, that's why she asked for your help.

Artem wants to paint an $ n \times m $ board. Each cell of the board should be colored in white or black.

Lets $ B $ be the number of black cells that have at least one white neighbor adjacent by the side. Let $ W $ be the number of white cells that have at least one black neighbor adjacent by the side. A coloring is called good if $ B = W + 1 $ .

The first coloring shown below has $ B=5 $ and $ W=4 $ (all cells have at least one neighbor with the opposite color). However, the second coloring is not good as it has $ B=4 $ , $ W=4 $ (only the bottom right cell doesn't have a neighbor with the opposite color).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333A/34674661541310c7b0f570cbf7d03ed451c5851a.png)Please, help Medina to find any good coloring. It's guaranteed that under given constraints the solution always exists. If there are several solutions, output any of them.

## 说明/提示

In the first testcase, $ B=3 $ , $ W=2 $ .

In the second testcase, $ B=5 $ , $ W=4 $ . You can see the coloring in the statement.

## 样例 #1

### 输入

```
2
3 2
3 3```

### 输出

```
BW
WB
BB
BWB
BWW
BWB```

# 题解

## 作者：Warriors_Cat (赞：4)

### $Description:$

构造一个 $n\times m$ 的黑白块，使得有白格子相邻的黑格子数量比有黑格子相邻的白格子数量多 $1$。

### $Solution:$

首先，对于一个 $n\times m$ 的矩阵，我们构造如下：

```cpp
BWBW......BWBW(B)
WBWB......WBWB(W)
..............
..............
BWBW......BWBW(B)
WBWB......WBWB(W)
(BWBW......BWBW(B))
```

简单来说，就是黑色和白色交替构造。

很显然，当 $n\equiv1$ 且 $m\equiv1\mod 2$ 时，直接成立。

但，当上面不成立时，我们可以发现，$B$ 和 $W$ 就相等了。

此时，我们可以考虑将一个为 ``W`` 的角改成 ``B``，此时 $B$ 就比 $W$ 多 $1$ 了。

代码如下：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t, n, m;
char s[110][110] ;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		if((n & 1) && (m & 1)){
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= m; ++j){
					if(((i - 1) * n + j) & 1) printf("B");
					else printf("W");
				}
				printf("\n");
			}
			continue;
		}//如果两个均为奇数
		else{
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= m; ++j){
					if((i & 1) ^ (j & 1)) s[i][j] = 'W';
					else s[i][j] = 'B';
				}
			}//先构造
			if(s[1][2] == 'B') s[1][1] = 'B';
			else if(s[1][m - 1] == 'B') s[1][m] = 'B';
			else if(s[n][2] == 'B') s[n][1] = 'B';
			else if(s[n][m - 1] == 'B') s[n][m] = 'B';//判断
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= m; ++j){
					printf("%c", s[i][j]);
				}
				printf("\n");
			}//输出
		}
	}
	return 0;
} 
```


---

## 作者：yangrunze (赞：3)

蒟蒻第一次熬夜打(diao)C(ra)F(ting)呢……发篇题解纪念一下吧QAQ


------------

这个题的要求是这样的：

- 题目描述：

给你一块 $n\times m$ 的木板，每一个格子都要涂成黑色或者白色。

设这个黑板的 $B$ 值为**相邻的格子有至少一个白色格子的黑色格子的个数** ，$W$ 值为**相邻的格子有至少一个黑色格子的白色格子的个数**。

现在让你输出一种涂色方案，使这个方案的 $B=W+1$，数据保证有解，如有多种方案，输出任意一种即可

- 输入输出格式及数据范围：

**本题输入含有多组数据**

第一行输入一个整数 $t(1\le t\le 20)$表示数据组数

对于每组数据，输入两个整数 $n,m(2\le n,m \le 100)$，表示木板的行数和列数，含义见题目描述

- 样例解释：

第一组数据的输出中，$B=3,W=2$，符合 $B=W+1$

第二组数据的输出中，$B=5,W=4$，符合条件


------------

### Solution:

CF最有特色的就是**构造题**，对于这种带Special Judge的题目，这里我来告诉大家一个小小的经验：

>考虑**特殊情况**，得到**简单答案**

那什么是特殊情况呢？

比如……全是白的？

此时$B=0,W=0$

那我们再慢慢把它涂黑？

把左上角变成黑的，此时$B=1,W=2$

好像正好和要求反过来了……那咱就**把左上角涂成白的，其它全涂成黑的**

这样的话不管$n$和$m$到底是多少，都满足$B=2,W=1$，自然就满足$B=W+1$的题目要求啦！！！

~~（我才不告诉你本蒟蒻是看到了卫生间的白瓷砖才有了思路）~~

代码我就不贴了，在这里我要给大家推荐另一道巧妙的构造题：[CF1312B Bogosort](https://www.luogu.com.cn/problem/CF1312B)

也是一个巧妙的构造题，按照我们刚才的分析，得出合理的特殊情况吧！

如果你不会，可以看`vectorwyx`大佬的题解

[膜拜大佬去~](https://www.luogu.com.cn/blog/yuan-xin/solution-cf1312b)

最后，祝愿大家以后CF能涨Rating哦QωQ



---

## 作者：xrdrsp (赞：3)

这是本人的第 $005$ 篇题解。

本题是一个规律题。手玩几个样例以后能发现一些有意思的东西。比如对于 $n$、$m$ 任意的图，都有一种固定的选取方法可以满足条件。比如这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/9odlxf6i.png)

图中黑色格子表示被染黑的部分，白色格子表示白色部分。（废话）

数字表示计数。即**在 $6 \times 6$ 的方格里，只需要把 $i = 1$ *或* $j = 1$ 的格子染黑，就是一个合法的方案了。**（注意：$(1, 1)$（左上角的格子）不算。）

对于 $n$、$m$ 任意的图也一样。读者可以自己画画看。

即：在这样的情况下，$B = n + m - 2$，$W = (n - 1) + (m - 1) - 1 = n + m - 3$，可得 $B = W + 1$。

所以就可以写代码了。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == 1 || j == 1) {
                    puts("B");
                } else {
                    puts("W");
                }
            }
        }
    }
}
```

---

## 作者：gyh20 (赞：2)

简要题意：构造一个 $n\times m$ 的矩阵使得其中有白色方格相邻的黑色方格比有黑色方格相邻的白色方格多一个。

可以发现，$n,m$ 都 $>1$，这样我们可以使最左边的一行全部为白，右边全部为黑，这样黑 $=$ 白，然后将其中的一个白改为黑那么黑的答案不变，白的答案 $-1$，所以黑 $=$ 白 $+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,a,b,m,t;
int main(){
	t=read();
	while(t--){
		n=read();m=read();
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=m;++j){
				if(j==1&&i!=n)putchar('W');
				else putchar('B');
			}puts("");
		}
	}
}
```


---

## 作者：yhx0322 (赞：1)

## 题目简述
给你一个 $n \times m$ 的方格，构造一个方案，使得方案中 $B = W + 1$。

$B$：相邻的格子有至少一个白色格子的黑色格子的个数。

$W$：相邻的格子有至少一个黑色格子的白色格子的个数。

## 思路
分奇偶讨论。

- $n \times m$ 是偶数：构造一张黑、白相间的矩阵，**左上角填为白色**，黑色方块的数量相同。

- $n \times m$ 是奇数：构造一张黑、白相间的矩阵，**左上角填为黑色**，黑白快数量相同。

## 代码
```c++
#include <bits/stdc++.h>

using namespace std;

int T, n, m;

int main() {
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if((n & 1) && (m & 1)) {
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if((i + j) & 1) printf("%c", 'W');
					else printf("%c", 'B');
				}
				puts("");
			}
		}
		else {
			printf("%c", 'B');
			for(int i = 2; i <= m; i++) {
				if((i + 1) & 1) printf("%c", 'B');
				else printf("%c", 'W');
			}
			puts("");
			for(int i = 2; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if((i + j) & 1) printf("%c", 'B');
					else printf("%c", 'W');
				}
				puts("");
			}
		}
	}
	return 0;
}


```

---

## 作者：zhangboyong (赞：1)

## 题意简述：

有一块 $n \times m$ 的木板，每个格子要涂成黑色或白色，使得有白色格子相邻的黑色格子数比有黑色格子相邻的白色格子数多 $1$，输出一种合法的方案。

## 思路：

这是一道构造题，只需要输出一种合法方案即可。

我们需要一种满足条件的黑色格子比满足条件的白色格子多 $1$ 的方案。在这之前，我们不妨先想一想如何让所有的黑色或白色格子都满足条件。

显然，让黑色格子与白色格子不断交替出现就可以都满足条件，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5qlssovd.png)

不难发现，按照这样填充，如果格子数为偶数，此时 $B = W$；而如果格子数是奇数，按先黑后白涂色，此时的 $B = W + 1$，满足了题目的要求，所以在格子数为奇数时可以直接按这种方式输出。

**那么如何在格子数为偶数时构造呢？**

我们只需要将其中一个白色的格子染为黑色即可！

![](https://cdn.luogu.com.cn/upload/image_hosting/hkqqpbcp.png)

此时，$W$ 值减少 $1$，而 $B$ 值因为新增的黑格子周围没有白格子不变，所以此时 $B = W + 1$。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,t;
int main(){
	cin >> t;
	while(t--){
		cin >> n >> m;
		if(n%2==0||m%2==0){
			for(int i = 1;i<=n;i++){
				for(int j = 1;j<=m;j++){
					if(i==1&&j==1){
						cout << "B";
						continue;
					}
					if(i%2==1){
						if(j%2==0) cout <<"B";
						else cout << "W"; 
					}else{
						if(j%2==0) cout << "W";
						else cout << "B";
					}
				}
				cout << endl;
			} 
		}else{
			for(int i = 1;i<=n;i++){
				for(int j = 1;j<=m;j++){
					if(i%2==1){
						if(j%2==1) cout <<"B";
						else cout << "W"; 
					}else{
						if(j%2==1) cout << "W";
						else cout << "B";
					}
				}
				cout << endl;
			} 
		}
	}
   return 0;
}

```


---

## 作者：dead_X (赞：1)

## 1 题意简述
~~又是神仙构造题~~

给出 $n,m$ ，输出一个由 $W,B$ 组成的 $n\times m$ 矩阵，使得上下左右至少有一个 $W$ 的 $B$ 数量比至少有一个 $B$ 的 $W$ 数量多 $1$ 。 
## 2 思路简述
分 类 讨 论

如果一共是奇数，直接弄一个黑白相间的图，左上角是黑，则黑比白多 $1$ 个，符合。

如果一共是偶数，还是弄一个黑白相间的图，但是这次左上角是白，则黑白块数量相同。

考虑到如果左上角的黑变成白，那么少一个白块，那么黑就比白多 $1$ 个，也符合。
## 3 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),m=read();
		if((n&1) && (m&1))
		{
			for(int i=1; i<=n; i++)
			{
				for(int j=1; j<=m; j++) if((i+j)&1) printf("W"); else printf("B");
				printf("\n"); 
			}
		}
		else
		{
			printf("B");
			for(int i=2; i<=m; i++) if((i+1)&1) printf("B"); else printf("W");
			printf("\n");
			for(int i=2; i<=n; i++)
			{
				for(int j=1; j<=m; j++) if((i+j)&1) printf("B"); else printf("W");
				printf("\n"); 
			}
		}
	}
	return 0;
}

```
## 4 总结
最近构造题好 多 啊

---

## 作者：tuzhewen (赞：1)


### 题目意思
现在有一个$n\times m$的方格图，每个方格可以涂上黑色（字符'B'）或者白色（字符'W'）。定义好矩阵就是**有白色方块相邻的黑色方块**比**有黑色方块相邻的白色方块**多一个，现在让你输出这个矩阵，多解输出任意一个解。

### 思路
~~能有什么思路！完全是虐spj好不好（滑稽）~~

我们把所有方块填成黑色，然后留$mp[n][m]$给白色就行了。

举个栗子：

$input:$

`
3 4
`

$output:$

`
BBBB
`

`
BBBB
`

`
BBBW
`

我们看输出，只有$2$行$4$列和$3$行$3$列的'B'紧邻唯一的一个'W'，所以'B'的实际个数就是$2$，'W'实际也只有$1$个，所以说这么解是什么情况都满足的~

$ACcode$
```
#include<bits/stdc++.h>
using namespace std;
#define F(i,l,r) for(int i=l;i<=r;i++)
//学会define省码量！
int T,n,m;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		F(i,1,n-1) {//最后一行先不处理！
			F(j,1,m) {
				printf("B");//一直输出B
			}
			puts("");
		}
		F(j,1,m-1) printf("B");//最后一行输出m-1个B
		printf("W\n");//i最后一个字符是W，不要忘记换行！
	}
	return 0;//好习惯
}
```

---

## 作者：帝千秋丶梦尘 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1333A)

$B$值为相邻的格子有至少一个白色格子的黑色格子的个数 ；

$W$值为相邻的格子有至少一个黑色格子的白色格子的个数。

因为要求$B$较大

那我们先假设：

所有的格子都为$B$。

那么，我们要放$W$进去；而每放入一个，$W$的值必定加1

如果放在中间，那么就有上下左右的四个$B$加进去

如果放在边界，那么就会多另外三边的$B$

如果放在角落，那么只有两边的$B$会加进去了

诶？！答案一下就出来了

只要在角落放入一个$W$，那么$B$就会加进两个

就满足了$B=W+1$的条件了

因为行数列数都一定大于等于2，所以不用考虑只有一行或一列的情况了

CODE：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register
using namespace std;
int t,x,y;
signed main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
		cin>>x>>y;
		for(ri int i(1);i<=x;++i)	
		{
			for(ri int j(1);j<=y;++j)
			{
				if(i==1&&j==1)
				cout<<"W";
				else cout<<"B";
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_jimmywang_ (赞：0)

CF的题，写写题解

直接分类讨论啦

## 1.$n*m$%$2==0$

这样，我们保证$B$与$W$左右上下相间，最后一行最后一个与最后一行倒数第二个都为$B$就行了

伪代码：

```
char c[2]={'B','W'};

if(n*m%2==0){
    f(i,1,n){
        f(j,1,m){
            if((n%2==0&&m%2==1)||(n%2==1&&m%2==0)){
                if(i==n&&j==m)cout<<c[(i%2+(j-1)%2)%2];
                else cout<<c[(i%2+j%2)%2];
            }
            else{
                if(i==n&&j==m)cout<<c[(i%2+(j-1)%2+1)%2];
                else cout<<c[(i%2+j%2+1)%2];
            }
        }
        cout<<endl;
    }    
}
```
## 2.$n*m$%$2==1$

直接$B$开头，一路$BW$相间，就完事了

伪代码：

```
f(i,1,n){
    f(j,1,m)
        cout<<c[(i%2+j%2)%2];
    cout<<endl;
}
```
完整代码：
```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll T;
ll n,m;
char c[2]={'B','W'};
int main(){
    T=d;
    while(T--){
        n=d,m=d;
        if(n*m%2==0){
            f(i,1,n){
                f(j,1,m){
                    if((n%2==0&&m%2==1)||(n%2==1&&m%2==0)){
                        if(i==n&&j==m)cout<<c[(i%2+(j-1)%2)%2];
                        else cout<<c[(i%2+j%2)%2];
                    }
                    else{
                        if(i==n&&j==m)cout<<c[(i%2+(j-1)%2+1)%2];
                        else cout<<c[(i%2+j%2+1)%2];
                    }
                }
                cout<<endl;
            }    
        }
        else{
            f(i,1,n){
                f(j,1,m)
                    cout<<c[(i%2+j%2)%2];
                cout<<endl;
            }
        }
    }
    return 0;
}


```


---

## 作者：do_while_true (赞：0)

简单构造

有一个 $n*m$ 个格子的板子，给每个格子涂色，黑色或者白色。

定义 $B$ 为有黑方格相邻的白方格数，定义 $W$ 为有白方格相邻的黑方格数。构造一个涂色方案使得 $B=W+1$

首先如果 $n*m$ 是奇数，只需要按顺序交替涂色，黑白黑白...白黑就能满足$B=W+1$。

如果不是的话，我们可以先黑白黑白...黑白涂色，然后改变一个地方使得 $B=W+1$ ，也就是直接把角里的白色涂成黑即可。也就是这样:

| 黑 | 黑 |
| :----------: | :----------: |
| **黑** | 白 |

这时候我们很容易发现当 $n=1$ 或者 $m=1$ 时无解

## $\mathcal{Code}$
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,m,cnt;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		cnt=0;
		if(n*m%2==1)
		{
			cnt=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					printf("%c",cnt%2==1?'W':'B');
					cnt++;
				}
				puts("");
			}
			continue;
		}
		if(n%2==0)
		{
			for(int i=1;i<n;i++)
			{
				if(i%2)
					for(int j=1;j<=m;j++)
						printf("%c",j%2==1?'B':'W');
				else
					for(int j=1;j<=m;j++)
						printf("%c",j%2==1?'W':'B');
				puts("");
			}
		}
		else{
			for(int i=1;i<n;i++)
			{
				if(i%2)
					for(int j=1;j<=m;j++)
						printf("%c",j%2==1?'W':'B');
				else
					for(int j=1;j<=m;j++)
						printf("%c",j%2==1?'B':'W');
				puts("");
			}
		}
		printf("B");cnt=0;
		for(int i=2;i<=m;i++){
			printf("%c",cnt%2==0?'B':'W');
			cnt++;
		}
		puts("");
	}
}
```


---

## 作者：AutumnKite (赞：0)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

首先我们考虑将所有格子填上黑色，此时 $B=W=0$。

我们尝试将一个格子变成白色，可以发现将一个格子变成白色会使得 $W$ 变成 $1$，$B$ 变成这个格子上下左右的黑色格子数量。

我们的目标是使得 $B=2,W=1$，那么我们只要选择角落上的格子变成白色即可。

### 代码

```cpp
void solve() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i == n && j == m) {
				putchar('W');
			} else {
				putchar('B');
			}
		}
		putchar('\n');
	}
}
```

---

