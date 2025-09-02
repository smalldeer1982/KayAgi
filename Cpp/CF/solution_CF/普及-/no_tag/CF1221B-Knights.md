# Knights

## 题目描述

You are given a chess board with $ n $ rows and $ n $ columns. Initially all cells of the board are empty, and you have to put a white or a black knight into each cell of the board.

A knight is a chess piece that can attack a piece in cell ( $ x_2 $ , $ y_2 $ ) from the cell ( $ x_1 $ , $ y_1 $ ) if one of the following conditions is met:

- $ |x_1 - x_2| = 2 $ and $ |y_1 - y_2| = 1 $ , or
- $ |x_1 - x_2| = 1 $ and $ |y_1 - y_2| = 2 $ .

Here are some examples of which cells knight can attack. In each of the following pictures, if the knight is currently in the blue cell, it can attack all red cells (and only them).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221B/52d6b0891a161fbd4258da7a11dd1ce54ed8afcb.png)A duel of knights is a pair of knights of different colors such that these knights attack each other. You have to put a knight (a white one or a black one) into each cell in such a way that the number of duels is maximum possible.

## 说明/提示

In the first example, there are $ 8 $ duels:

1. the white knight in ( $ 1 $ , $ 1 $ ) attacks the black knight in ( $ 3 $ , $ 2 $ );
2. the white knight in ( $ 1 $ , $ 1 $ ) attacks the black knight in ( $ 2 $ , $ 3 $ );
3. the white knight in ( $ 1 $ , $ 3 $ ) attacks the black knight in ( $ 3 $ , $ 2 $ );
4. the white knight in ( $ 1 $ , $ 3 $ ) attacks the black knight in ( $ 2 $ , $ 1 $ );
5. the white knight in ( $ 3 $ , $ 1 $ ) attacks the black knight in ( $ 1 $ , $ 2 $ );
6. the white knight in ( $ 3 $ , $ 1 $ ) attacks the black knight in ( $ 2 $ , $ 3 $ );
7. the white knight in ( $ 3 $ , $ 3 $ ) attacks the black knight in ( $ 1 $ , $ 2 $ );
8. the white knight in ( $ 3 $ , $ 3 $ ) attacks the black knight in ( $ 2 $ , $ 1 $ ).

## 样例 #1

### 输入

```
3
```

### 输出

```
WBW
BBB
WBW
```

# 题解

## 作者：dthythxth_Huge_Brain (赞：5)

## 题目分析

> 在一个 $n \times n$ 的棋盘上放置黑马和白马，请给出一个放置方式，使得黑马和白马之间的冲突数最多（即可以互相攻击）

![](https://cdn.luogu.com.cn/upload/image_hosting/e28ykli9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由于马只能走日，我们可以将棋盘一黑一白染色，如图，每当马走一步后，它脚下的颜色一定会发生改变。只要把黑马和白马交错开来，就可以使之间冲突数最多。

## 参考题解

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> board(n, string(n, 'B'));  // 初始化棋盘，所有格子都放置黑马

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {  // 偶数行从第一个位置开始放置白马
            for (int j = 0; j < n; j += 2) {
                board[i][j] = 'W';
            }
        } else {  // 奇数行从第二个位置开始放置白马
            for (int j = 1; j < n; j += 2) {
                board[i][j] = 'W';
            }
        }
    }

    // 输出棋盘
    for (int i = 0; i < n; i++) {
        cout << board[i] << endl;
    }

    return 0;
}

```


---

## 作者：wmrqwq (赞：5)

# 原题链接

[CF1221B Knights](https://www.luogu.com.cn/problem/CF1221B)

# 题目简述

在一个 $n \times n$ 的棋盘上放置黑马和白马，给出一个放置方式，使得黑马和白马之间的冲突数最多。

# 解题思路

这道题是一道贪心构造题，因为马每一步有 $8$ 种移动方案，而我们假设将这个棋盘进行黑白交替染色，则会得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/26kfcxxj.png)

不难得出结论，如果马在黑色的格子上，则下一步必定会走到白色的格子上，如果马在白色的格子上，则下一步必定会走到黑色的格子上，所以，我们要将黑马放在同色的格子上，白马也要放在与黑马放置的格子的相反颜色的格子里，不难发现，我们设每个格子的横轴为 $x$，纵轴为 $y$，则如果```(x+y)%2==0```，那么这个格子就为黑色的格子，否则这个格子就为白色的格子。


# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0
long long n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)%2==0)//如果为黑色格子，就放黑色的马 
				cout<<"B";
			else //否则放白色的马
				cout<<"W";
		}
		cout<<endl;
	}
	QwQ;//华丽的结束
}

```


---

## 作者：Dws_t7760 (赞：5)

看到好多大佬都是直接推结论的，那我就写一个暴力深搜的方法，更适合新手。

我们首先开一个字符二维数组，将其所有元素都定义为 `B`，防止出现某个节点无法遍历的情况。

我们把第一行第一列的元素定义为 `W`，从第一行第一列开始暴力深搜。

深搜思路：对于某个已经确认马的颜色的格子，将其能攻击到的格子都定义为与其颜色相反的，并开始下一轮深搜。

AC代码：

```cpp
#include<iostream>
using namespace std;
int n,s,nextx[8]={-2,-2,-1,-1,1,1,2,2},nexty[8]={-1,1,-2,2,-2,2,-1,1};
char a[110][110];
bool v[110][110];
bool inn(int x,int y) {
	if(x<0||x>=n||y<0||y>=n) return 0;
	return 1;
}
void dfs(int x,int y,char t) {
	if(s==n*n) return;
	a[x][y]=t,v[x][y]=1,s++;
	int xx,yy;
	char tt=(t=='W'?'B':'W');
	for(int i=0;i<8;i++) {
		xx=x+nextx[i],yy=y+nexty[i];
		if(inn(xx,yy)&&!v[xx][yy]) dfs(xx,yy,tt);
	}
}
int main() {
	cin>>n;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) a[i][j]='B';
	dfs(0,0,'W');
	for(int i=0;i<n;i++) cout<<a[i]<<endl;
	return 0;
}
```


---

## 作者：Tachibana27 (赞：4)

## 题目大意

在 $n\times n$ 的棋盘上放置黑马与白马，输出冲突数量最多的方案。

## 提要

在国际象棋中，马走“日”，且没有中国象棋中“撇脚”的规则。

## 思路

如果一匹马在 $(x,y)$ 的位置上，那么会引起冲突的位置有：

$(x+2,y+1),(x+2,y-1),(x+1,y+2),(x+1,y-2),(x-1,y+2),(x-1,y-2),(x-2,y+1),(x-2)$ 

我们不难发现，$x$ 和 $y$ 的奇偶性是不同的，所以我们只需枚举棋盘上的每一个格子。格子横纵坐标之和为偶数放置白马，反之放置黑马。

## 代码(已做防抄袭处理）

```cpp
-#include<bits/stdc++.h>
-using namespace std;
-int n;
-int main(){
-  	 cin>>n;
-	 for(int i=1;i<=n;i++,cout<<"\n")
-		 for(int j=1;j<=n;j++)//枚举棋盘的格子
-			 if(!((i+j)%2))//偶数
-  			     cout<<"W";//放置白马
-			 else
-			     cout<<"B";//放置黑马
-	 return 0;//完结撒花！！！
-}

```

~~蒟蒻第一次写题解，求过~~

---

## 作者：幽界の冥神 (赞：3)

本题很简单，代码尤其短

设一个点$(x, y)$，不难发现$(x + 1, y), (x, y + 1),(x -1,y),(x, y - 1)$，都不会被$(x, y)$攻击。

进一步思考，可以确定以这种放置方式可以使棋盘的格子利用率达到最高，那么就不难知道如何放置可以得到答案。

但此时代码仍然很复杂，仔细观察发现只要对于$(x, y)$，$2|x + y$时输出$W$,否则输出$B$即可。

上代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int n;

int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			putchar (((i + j) & 1) ? 'B' : 'W');
		cout << endl;
	}
	return 0;
}
```

完结撒花~~

---

## 作者：封禁用户 (赞：3)

# 题目大意

在一个 $n\times n$ 的棋盘上放置黑马和白马，求怎样才能使得黑马和白马之间的冲突数最多。

# 题目解析

假设棋盘上有一个点 $(x,y)$，可以发现只有 $(x+1,y)$，$(x-1,y)$，$(x,y-1)$，$(x,y+1)$ 这四个点不会被攻击，而另外八个点比如 $(x+1,y+2)$，$(x-2,y-1)$ 都能被攻击到，可以发现，$x$ 坐标与 $y$ 坐标的奇偶性完全不同，所以将横纵坐标之和为奇数的位置放黑马，反之放白马即可。

代码如下：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if((i+j)&1)
				cout<<"B";
			else
				cout<<"W";
			}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Light_az (赞：1)

## 模拟

这道题很简单，由题意得：想要黑马和白马之间的冲突数最多，那么他们必须互相间隔。也就是说黑马的上下左右都不能是黑马，白马也是同。那么我们只需要循环嵌套一下：处于奇数行，奇数列的位置为 W，处于奇数行，偶数列的位置为 B，处于偶数行，奇数列的位置为 B，处于偶数行，偶数列的位置为 W，这样就能保证 W 和 B 相互间隔，下面是完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i%2==1){//奇数行 
            	if(j%2==1){//奇数列
            		cout<<"W";
				}
				else{//偶数列 
					cout<<"B";
				}
			}
			else{//偶数行 
            	if(j%2==0){//偶数列 
            		cout<<"W";
				}
				else{//奇数列 
					cout<<"B";
				}
			}
        }
        cout<<endl;
    }
}
```


---

## 作者：Big_Brain (赞：1)

按照惯例，先上[题目传送门](https://www.luogu.com.cn/problem/CF1221B)

# 题意简述

给定一个大小为 $n^{2}$ 的象棋棋盘，在上面放上黑、白两种“马”棋子。问最多能使多少白马与黑马可以互相冲突。

# 思路总结

~~众所周知~~，如果现在马的位置为 $(i,j)$，那么在移动之后，马的位置只有可能是这 $8$ 种：$(i+1,j+2)$，$(i-1,j+2)$，$(i-1,j+2)$，$(i-1,j-2)$，$(i+2,j+1)$，$(i+2,j-1)$，$(i-2,j+1)$ 和 $(i-2,j-1)$。

接下来，我们拟定一个 $5 \times 5$ 的棋盘，将整个棋盘黑白相间得染色，得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/j4ob75ol.png)

不难发现，如果有马在 $(3,3)$ 的位置（也就是在一个黑色的格子），那么经过上文提到的所有移动情况，马一定会出现在一个白色的格子中。所以，如果想要让黑马和白马发生冲突，就需要把每一个黑马和白马都分别放在不同颜色的格子中。根据上图，如果是黑色格子，就放上黑马；如果是白色格子，就放上白马。这样，每一只白马和黑马都会发生冲突，一定是最优解之一。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){ //快读模板
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar())if(!(c^45))f=1;
    for(;c>='0'&&c<='9';c=getchar())t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x,char s='\n'){ //输出模板
    static int t[25];int tp=0;if(x==0)return(void)(putchar('0'));
    else if(x<0){putchar('-');x=-x;}while(x){t[tp++]=x%10;x/=10;}
    while(tp--){putchar(t[tp]+48);}putchar(s);return ;
}
int main(){
    int n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int sum=i+j;
            if(sum%2==0)putchar('B'); //判断格子是黑色格子还是白色格子
            else putchar('W');
        }
        puts("");
    }
}
```

[AC 记录](https://www.luogu.com.cn/record/117575109)

---

## 作者：zk_y (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1221B)
## 题目解释

我们要使冲突最多，就要使**每匹马能攻击的地方都是敌方的马**。

## 解决问题

那我们来看看马都能走到哪里。

下面是国际象棋的棋盘：

![](https://ts1.cn.mm.bing.net/th/id/R-C.f6f09ddc2db32140229f09d51264483b?rik=40QU0gi4lm5Hbw&riu=http%3a%2f%2fwww.51wendang.com%2fpic%2fcbf960bb496eee518f871639%2f1-600-png_6_0_0_236_87_790_767_1262.879_892.979-600-0-0-600.jpg&ehk=w050i2ajMZxvH4q8vt%2bNNF0pm75ajCepA6XnUaj8rhY%3d&risl=&pid=ImgRaw&r=0)

我们把马放在 $6c$ 这个点上，那就是题目上的那个图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221B/52d6b0891a161fbd4258da7a11dd1ce54ed8afcb.png)

我们把这两幅图对比一下，我们就能发现每匹马：

> 1.从黑色到白色
> 
> 2.从白色到黑色

我们就知道马每次攻击一次都要走到另一种颜色的格子。

所以我们就可以把所有黑色的格子都放上一种马，所有白色的格子放上一种马就行了。

我们只需成功染色就可以了，这也很简单，白色的格子的 $x$ , $y$ 的差值能被 $2$ 整除，而黑色的不行，那代码就出来了。

## 代码实现 
```cpp
#include<bits/stdc++.h>//头文件 
using namespace std;
int n;
bool maap[105][105];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(abs(i-j)%2==0)printf("B");//如果是白色的 
			else printf("W");//如果是黑色的 
		}
		printf("\n");//换行 
	}
	return 0;
}
```


---

## 作者：tmp_get_zip_diff (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1221B)。

## 思路

~~大水题~~

看到马，不妨要说一说他的路线。

看另一道关于马的题：[P1443](https://www.luogu.com.cn/problem/P1443)，当然，那是一道 BFS，这题更简单。

我们看一下马移动一步的位置变化：

```cpp
int dx[]={1,1,2,2,-1,-1,-2,-2};
int dy[]={2,-2,1,-1,2,-2,1,-1};
```

可以看出 $x$ 和 $y$，一个`2`，一个`1`，奇偶性不同，因此只要让横坐标与纵坐标相加，偶数和奇数放置不同颜色的马即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)%2==0) //要打括号 
				cout<<"W";
			else
				cout<<"B";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

欢迎提问！

---

## 作者：czxQQQ (赞：0)

## 思路
众所周知，马走日。假设一个马的坐标为 $(x,y)$，那么可以攻击到它的格子有：

$(x+2,y+1)$，$(x+1,y+2)$，$(x+2,y-1)$，$(x+1,y-2)$，$(x-2,y+1)$，$(x-1,y+2)$，$(x-2,y-1)$，$(x-1,y-2)$

不难看出，$x$ 和 $y$ 的奇偶是不同的。因此可以遍历一遍，如果 $i+j$ 是偶数则是白马，否则是黑马。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==0) cout<<"W";
			else cout<<"B";
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：Neilchenyinuo (赞：0)

## Solution:
- 马走的为日字格，设一匹马在 $(x, y)$，明显可看出，$(x-2, y-1)$，$(x-2,y+1)$，$(x-1,y-2)$，$(x-1,y+2)$，$(x+2,y-1)$，$(x+2,y+1)$，$(x+1,y-2)$，$(x+1,y+1)$ 这八个点可攻击到 $(x,y)$。

可以发现，$x$ 坐标与 $y$ 坐标的奇偶性完全不同，所以将横纵坐标之和为奇数的位置放黑马，偶数放白马即可。
## Code:
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)&1)
				cout<<"B";
			else
				cout<<"W";
		}
		cout<<"\n";
	}
	return 0;
}
```
### 完结撒花。

---

## 作者：YangXiaopei (赞：0)

## Solution:
马走的为日字格，设一匹马在 $(x, y)$， 明显可看出， $(x - 2, y - 1)$，$(x - 2, y + 1)$，$(x - 1, y - 2)$，$(x - 1, y + 2)$，$(x + 2, y - 1)$，$(x + 2, y + 1)$，$(x + 1, y - 2)$，$(x + 1, y + 1)$ 这八个点可攻击到 $(x, y)$ 

再找一下规律，八个点的横竖坐标之和均与马的位置坐标之和奇偶不同，所以推结论：坐标和为奇数放白马，坐标和为偶数放黑马。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main () {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j){
			if((i + j) & 1){
			    cout << "B";
			}
			else{
			    cout << "W";
			}
		}
		cout << "\n";
	}
	return 0;
}
```
### 完结撒花。

---

## 作者：Allanljx (赞：0)

## 思路
首先，对于一个马在点 $(x,y)$，它所能攻击到的点有 $8$ 个，分别是 $(x-2,y-1)$,$(x-2,y+1)$,$(x-1,y-2)$,$(x-1,y+2)$,$(x+1,y-2)$,$(x+1,y+2)$,$(x+2,y-1)$ 和 $(x+2,y+1)$。不难发现，这 $8$ 个点横纵坐标之和的奇偶性都与点 $(x,y)$ 不同。所以我们可以将横纵坐标之和为奇数的位置放黑马，反之放白马。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if((i+j)%2) cout<<"B";
            else cout<<"W";
        }
        cout<<endl;
    }
}
```


---

## 作者：zct_sky (赞：0)

### Solution:
-----
如果我们将每个格点与它能攻击到的点连一条边，那么显然构成了一张二分图。

然后将这张二分图染色，并根据颜色输出 $B$ 或 $W$ 即可。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*y;
}
const int N=1e5+7;
int n,m,head[N],nxt[N<<1],from[N<<1],to[N<<1],tot,col[N]; 
void add(int u,int v){
	from[++tot]=u;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
void dfs(int p,int fp){
	for(int i=head[p];i;i=nxt[i]){
		if(i==fp)continue;
		if(col[to[i]]==0){
			col[to[i]]=3-col[p];
			dfs(to[i],p);
		}
	}
}
int hs(int i,int j){
	return (i-1)*n+j;
}
const int fx[][2]={{1,2},{1,-2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,-1},{-2,1}};
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			for(int k=0;k<8;k++){
				int ii=i+fx[k][0];
				int jj=j+fx[k][1];
				
				if(ii>0&&ii<=n&&jj>0&&jj<=n)
					add(hs(i,j),hs(ii,jj));
			}
		} 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!col[hs(i,j)]){
				col[hs(i,j)]=1;
				dfs(hs(i,j),0);
			}
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			if(col[hs(i,j)]==1)putchar('B');
			else putchar('W'); 
	return 0;
}
```

---

