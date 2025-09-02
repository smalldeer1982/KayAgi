# [ABC196D] Hanjo

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc196/tasks/abc196_d

縦 $ H $ メートル、横 $ W $ メートルの長方形の部屋があります。  
 この部屋に $ 2 $ メートル $ × $ $ 1 $ メートルの区別できない畳 (長方形のタイル) $ A $ 枚と、$ 1 $ メートル $ × $ $ 1 $ メートルの区別できない半畳 (正方形のタイル) $ B $ 枚を敷き詰めます。 $ 2 $ メートル $ × $ $ 1 $ メートルの畳は縦長にも横長にも使うことができます。  
 敷き詰める方法は何通りあるでしょうか？  
 なお、$ 2A\ +\ B\ =\ HW $ であることが保証されます。 また、回転や反転を行うことで初めて一致するような敷き詰め方は区別します。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =\ H,\ W $
- $ HW\ <\ =\ 16 $
- $ 0\ <\ =\ A,\ B $
- $ 2A\ +\ B\ =\ HW $

### Sample Explanation 1

以下の $ 4 $ つです。 !\[\](https://img.atcoder.jp/ghi/d01b63c75c91bd87a73e9a4cc43dda28.png)

### Sample Explanation 2

以下の $ 6 $ つと、これらを回転させたものが含まれます。 !\[\](https://img.atcoder.jp/ghi/b7a492abe22e30683e8f9a7b309acd52.png)

## 样例 #1

### 输入

```
2 2 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 4 1```

### 输出

```
18```

## 样例 #3

### 输入

```
4 4 8 0```

### 输出

```
36```

# 题解

## 作者：ht__QAQ__ (赞：4)

## 题意：

给定一个 $H\times W$ 的矩形，求把这个矩形分割成 $A$ 个 $2\times 1$ 的小矩形和 $B$ 个 $1\times 1$ 的小矩形的方案数。


------------
## 思路：
先建函数：

```cpp 
void dfs(int i,int bit,int a,int b) ;
```

> 其中，$i$ 表示当前搜索到的格子编号，从 $0$ 开始；$bit$ 表示当前状态，第 $i$ 位为 $1$ 表示第 $i$ 个格子已经被覆盖，为 $0$ 表示未被覆盖；$a$ 表示还剩下多少个 $2\times 1$ 的矩形可以放置；$b$ 表示还剩下多少个 $1\times 1$ 的矩形可以放置。

------------

```cpp
if(i==h*w){ans++;return;}
```
- 如果 $i=h\times w$，则说明当前状态是可行的，将 $ans$ 加 $1$，然后直接返回。

------------
```cpp
if(b)dfs(i+1,bit|(1<<i),a,b-1); 
```

- 考虑放置一个 $1\times 1$ 的矩形。如果可以，那么将当前格子和下一个格子都标记为已覆盖，接着继续搜索下一个格子。

-------------
```cpp
if(a){
        if(i%w!=w-1&&!(bit&(1<<(i+1))))dfs(i+2,bit|(1<<i)|(1<<(i+1)),a-1,b);
        if(i+w<=h*w&&!(bit&(1<<(i+w))))dfs(i+1,bit|(1<<i)|(1<<(i+w)),a-1,b);
}
```
- 接着放置一个 $2\times 1$ 的矩形的情况。判断是否横向放置还是纵向放置，接着标记，继续搜索。

------------

## Code：

```cpp
void dfs(int i,int bit,int a,int b){
    if(i==h*w){ans++;return;}
    if(bit&(1<<i))dfs(i+1,bit,a,b);
    if(b)dfs(i+1,bit|(1<<i),a,b-1);
    if(a){
        if(i%w!=w-1&&!(bit&(1<<(i+1))))dfs(i+2,bit|(1<<i)|(1<<(i+1)),a-1,b);
        if(i+w<=h*w&&!(bit&(1<<(i+w))))dfs(i+1,bit|(1<<i)|(1<<(i+w)),a-1,b);
    }
}
```



---

## 作者：sybs1145 (赞：2)

# [[ABC196D] Hanjo](https://www.luogu.com.cn/problem/AT_abc196_d) 题解
## 思路
数据范围不大，简单 dfs 即可（甚至不需要什么剪枝）。

直接从前往后，从上往下搜。

搜索时分情况来考虑：
1. 边界
- **搜完整个矩阵**，更新答案即可。
- **搜完当前一行**，搜下一行。
2. 分割
- **如果 $A$ 不为 0**，考虑竖着放 $1\times 2$ 的格子或横着放 $1\times 2$ 的格子。
- **如果 $B$ 不为 0**，考虑放 $1\times 1$ 的格子。

途中用一个数组记录当前格子是否被使用。

dfs 时当前格子不需要标记，因为不会走回头路，只要把放 $1\times 2$ 的格子时额外占用的格子标记了就行。
## AC code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int h, w, A, B, ans;
bool vis[25][25];
void dfs(int x, int y)
{
    if (x > h) //搜完了
    {
        ans++;
        return;
    }
    if (y > w) //搜完这一行了
    {
        dfs(x + 1, 1);
        return;
    }
    if (vis[x][y])
    {
        dfs(x, y + 1);
        return;
    }
    if (A > 0) //放1*2的格子
    {
        A--;
        if (y < w && !vis[x][y + 1]) //横着放
        {
            vis[x][y + 1] = 1;
            dfs(x, y + 1);
            vis[x][y + 1] = 0;
        }
        if (x < h && !vis[x + 1][y]) //竖着放
        {
            vis[x + 1][y] = 1;
            dfs(x, y + 1);
            vis[x + 1][y] = 0;
        }
        A++;
    }
    if (B > 0) //放1*1的格子
    {
        B--;
        dfs(x, y + 1);
        B++;
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> h >> w >> A >> B;
    dfs(1, 1);
    cout << ans << '\n';
    return 0;
}
```
## UPD：2025.1.30 修正了一处笔误。

---

## 作者：Hog_Dawa_IOI (赞：2)

题意：给定一个 $n\times m$ 的矩形，求把这个矩形分割成 $a$ 个 $2\times 1$ 的小矩形和 $b$ 个 $1\times 1$ 的小矩形的方案数。       
由数据范围 $1 \le n \times m \le 16$ 可知这道题可以使用暴搜解决。对于每一个格子判断放哪种小矩形并标记（有时候放置了 $2 \times 1$ 的小矩形会覆盖到别的格子，标记后就可以直接跳过了）。需要注意小矩形可以横着放也可以竖着放。   
```cpp
#include<cstdio>
using namespace std;
int n,m,a,b,ans,f[20][20];
void dfs(int x,int y,int wh1,int wh2,int num)
{
	if(x==0&&y==0) {ans++;return;}
	if(f[wh1][wh2]) dfs(x,y,wh1+wh2/m,wh2%m+1,num);
	if(y&&f[wh1][wh2]==0) f[wh1][wh2]=num,dfs(x,y-1,wh1+wh2/m,wh2%m+1,num+1),f[wh1][wh2]=0;
	if(x&&wh1<n&&f[wh1][wh2]==0&&f[wh1+1][wh2]==0)
	f[wh1][wh2]=f[wh1+1][wh2]=num,dfs(x-1,y,wh1+wh2/m,wh2%m+1,num+1),f[wh1][wh2]=f[wh1+1][wh2]=0;
	if(x&&wh2<m&&f[wh1][wh2]==0&&f[wh1][wh2+1]==0)
	f[wh1][wh2]=f[wh1][wh2+1]=num,dfs(x-1,y,wh1+wh2/m,wh2%m+1,num+1),f[wh1][wh2]=f[wh1][wh2+1]=0;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&a,&b);
	dfs(a,b,1,1,1),printf("%d",ans);
}
```

---

## 作者：loser_seele (赞：2)

观察到 $ H,W $ 都很小，所以可以考虑暴力搜索。

开一个数组 $ used_{i,j} $ 表示第 $ i $ 行第 $ j $ 列当前是否被使用过，$ dfs(i,j,a,b) $ 表示当前坐标，还有 $ a $ 个 $ A $ 以及 $ b $ 个 $ B $，然后对所有合法情况转移即可。

可以猜想合法的方案不会很多，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int H,W;
bool used[16][16];
long long dfs(int i,int j,int a,int b)
{
    if(a<0||b<0)
    return 0;
    if(j==W)
    j=0,i++;
    if(i==H)
    return 1;
    if(used[i][j])
    return dfs(i,j+1,a,b);
    long long res=0;
    used[i][j]=1;
    res+=dfs(i,j+1,a,b-1);
    if(j+1<W && !used[i][j+1])
    {
        used[i][j+1]=1;
        res+=dfs(i,j+1,a-1,b);
        used[i][j+1]=0;
    }
    if(i+1<H && !used[i+1][j])
    {
        used[i+1][j]=1;
        res+=dfs(i,j+1,a-1,b);
        used[i+1][j]=0;
    }
    used[i][j]=0;
    return res;
}
int main() 
{
    cin>>H>>W;
    int a,b;
    cin>>a>>b;
    cout<< dfs(0,0,a,b);
}
```


---

## 作者：lin_A_chu_K_fan (赞：1)

先上[题目传送门](https://www.luogu.com.cn/problem/AT_abc196_d)

# 题意
给定一个 $h \times w$ 的矩形，求用 $A$ 个 $1 \times 1$ 的矩形**和**$B$ 个 $1 \times 2$ 的矩形铺满大矩形的方案数。
# 思路
显然，是个 DFS 深搜，每次深搜是基于已有来搜索下一个矩形所有可能的大小及位置，若碰到一下两种情况则返回：
- 只剩 $1$ 个格子和 $1$ 个 $1 \times 2$ 的矩形。
- 所有格子全部铺满。
否则每一种情况都分别计数，记得排除重复。

虽然思路很简单，但代码细节比较多，~~蓝桥杯的味道~~。

为了禁止抄袭，代码就不放了。

求关~

---

## 作者：hjyowl (赞：1)

### 题目大意

给定一个 $h\times w$ 的棋盘，要求使用 $1\times 1$ 的小方块和 $1\times 2$ 的多米诺。

### 思路

由于 $h\times w$ 非常非小，可以考虑深搜，每次对于对于已经有了的矩阵进行下一步的搜索。

细节多，但是算法很基础的典型题。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int a[N][N];
int h,w;
int x,y;
int dfs(int x,int y,int u,int v){
	//oo
	//__
	if (u < 0 || v < 0){
		return 0;
	}
	if (x == h + 1){
		if (u == 0 && v == 0){
			return 1;
		}
		return 0;
	}
	if (y > w){
		return dfs(x + 1,1,u,v);
	}
	int t = 0;
	if (!a[x][y]){
		a[x][y] = 1;
		t += dfs(x,y + 1,u,v - 1);
		a[x][y] = 0;
	}
	if (!a[x][y] && !a[x][y + 1] && y + 1 <= w){
		a[x][y] = a[x][y + 1] = 1;
		t += dfs(x,y + 1,u - 1,v);
		a[x][y] = a[x][y + 1] = 0;
	}
	if (!a[x][y] && !a[x + 1][y] && x + 1 <= h){
		a[x][y] = a[x + 1][y] = 1;
		t += dfs(x,y + 1,u - 1,v);
		a[x][y] = a[x + 1][y] = 0;
	}
	if (a[x][y]){
		t = dfs(x,y + 1,u,v);
	}
	return t;
}
int main(){
	cin >> h >> w >> x >> y;
	int res = dfs(1,1,x,y);
	cout << res;
	return 0;
} 
```

---

## 作者：zk_y (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc196_d)

我们先来看看这道题目的数据范围，$H,W\le16$ 我们可以考虑暴搜。但是由于暴搜复杂度太大，所以我们需要考虑优化，可以设定一个 ``vis`` 数组，判断是否访问过这个点。

如果访问过了，那么我们就需要跳过这个点，直接搜索下一个点就可以了。

由于我们从左往右，从上往下，所以我们只需要设置向下，向右的偏移量数组就可以了。（但是这里我还是设置了 $4$ 个方向发偏移量数组）

---
# AC代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
bool vis[20][20];
int dx[10]={0,0,0,-1,1};
int dy[10]={0,1,-1,0,0};
int h,w,a,b,ans;
void dfs(int x,int y,int ta,int tb){
	if(x<1)return;if(y<1)return;//跳出dfs
	if((x>=h||y>=w)&&ta==a&&tb==b){//检测是否满足条件
		ans++;
		return;
	}
	if(vis[x][y]){
		if(y<w)dfs(x,y+1,ta,tb);//接着搜索
		if(y==w)dfs(x+1,1,ta,tb);//换一行搜索
		return;
	}
	if(ta<a){
		for(int i=1;i<=4;i++){//设置偏移量
			int now_x=x+dx[i];
			if(now_x<1||now_x>h)continue;
			int now_y=y+dy[i];
			if(now_y<1||now_y>w)continue;
			if(vis[now_x][now_y])continue;
			vis[now_x][now_y]=1;
			vis[x][y]=1;
			if(now_y<w)dfs(x,y+1,ta+1,tb);
			if(now_y==w)dfs(x+1,1,ta+1,tb);
			vis[now_x][now_y]=0;
			vis[x][y]=0;
		}
	}
	if(tb<b){
		vis[x][y]=1;
		if(y<w)dfs(x,y+1,ta,tb+1);
		if(y==w)dfs(x+1,1,ta,tb+1);
		vis[x][y]=0;
	}
}
int main(){
	scanf("%d%d%d%d",&h,&w,&a,&b);
	dfs(1,1,0,0);//开始dfs
	printf("%d",ans);
	return 0;
}


```

---

## 作者：D_xbang (赞：0)

## 题意：
给出一个 $H \times W$ 的矩阵，求分割成 $A$ 个 $2 \times 1$ 的小矩形和 $B$ 个 $1 \times 1$ 的小矩形的方案数。
## 思路：
观察样例 $HW\le16$，数据范围小，所以直接 DFS 暴搜即可。

DFS 每行每行的搜，因为 $B$ 个 $1 \times 1$ 的小矩形只要有空位就可以分割，所以先考虑 $2 \times 1$ 的矩形，搜完了后回溯即可。

最后输出即可。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int h, w, a, b, ans;
bool vis[20][20];
void dfs(int x, int y) {
	if (x > h){ ans++; return; }
	if (y > w){ dfs(x + 1, 1); return; }
	if (vis[x][y]){ dfs(x, y + 1); return; }
	if (a > 0){
		a--;
		if (y < w && !vis[x][y + 1]) { vis[x][y + 1] = 1; dfs(x, y + 1); vis[x][y + 1] = 0; }
		if (x < h && !vis[x + 1][y]) { vis[x + 1][y] = 1; dfs(x, y + 1); vis[x + 1][y] = 0; }
		a++;
	}
	if (b > 0){ b--; dfs(x, y + 1); b++; }
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> h >> w >> a >> b;
	dfs(1, 1);
	cout << ans;
	return 0;
}
```

---

## 作者：Alice2012 (赞：0)

发现数据范围很小，考虑暴力搜索填充。

具体的，考虑以从上到下、从左到右的顺序遍历每个格子，如果当前格子没被覆盖过，则考虑如何在其上放置。如果当前 $A\neq0$，考虑在其上摆放横着的或者竖着的 $1\times 2$ 矩形，同理如果 $B\neq0$，在其上放置 $1\times 1$ 格子同样也是一种方案。对于每种可行的方案向下搜索即可。

格子是否被覆盖过可以用标记数组 `vis` 记录。如果最后遍历到了最后一个格子，那么该方案是合法的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int n,m,A,B,cnt,vis[N][N];//vis:标记是否被填充 
void DFS(int x,int y){//当前所在格子 (x,y) 
	if(x>n){cnt++;return;}//表示所有格子都填充完毕 
	if(y>m)DFS(x+1,1);//这一行搜完了所以进入下一行继续搜索 
	if(vis[x][y])DFS(x,y+1);//当前格子已经被填充过了,进入下一个格子搜索 
	if(A){//可能可以填1x2的格子 
		if(y+1<=m&&!vis[x][y+1])A--,vis[x][y+1]=1,DFS(x,y+1),vis[x][y+1]=0,A++;//横着放合法,可以尝试填充并向下搜索 
		if(x+1<=n&&!vis[x+1][y])A--,vis[x+1][y]=1,DFS(x,y+1),vis[x+1][y]=0,A++;//同理竖着放合法,继续搜索
		//注意回溯!!! 
	}
	if(B)B--,DFS(x,y+1),B++;//填一个格子合法 
	return;
}
signed main(){
	cin>>n>>m>>A>>B;
	DFS(1,1),cout<<cnt;
	return 0;
}
```

---

## 作者：LeavingAC (赞：0)

**begin**

[AT_abc196_d [ABC196D] Hanjo](https://www.luogu.com.cn/problem/AT_abc196_d)

# 分析

一看数据范围，$H,W \le 16 $，直接暴力 dfs 就 ok 了。

# 思路

一行一行搜，搜到底了 $ans+1$，然后回溯回来。

因为这道题我们不用走回头路，所以只需要标记 $2 \times 1 $ 的方块另外一个多余的格子就行了，最后注意一下回溯细节就搞定了，总体来说还是比较水的。

# Code


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define gc() getchar()
#define pc(a) putchar(a)
#define sqrt(a) __builtin_sqrt(a)
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a/__gcd(a,b)*b
#define y1 fuck_cmath
using namespace std;
const int M=1e5+10;
// 以上全是板子

ll h,w,a,b,ans; // 高 宽 2*1 1*1 答案
bool vis[20][20]; // 是否被访问

void dfs(ll x,ll y) // 当前格子的坐标
{
    // 边界
    if (x>h){ans++;return;}
    if (y>w){dfs(x+1,1);}

    if (vis[x][y]) dfs(x,y+1); // 特殊情况

    if (a) //2*1
    {
        a--;
        if (y+1<=w && !vis[x][y+1]) // 横着放
        {
            vis[x][y+1]=1;
            dfs(x,y+2); // 下下列（因为下一列已经被标记了 dfs下一列没意义）
            vis[x][y+1]=0; // 回溯
        }
        if (x+1<=h && !vis[x+1][y]) // 竖着放
        {
            vis[x+1][y]=1;
            dfs(x,y+1); // 下一列
            vis[x+1][y]=0; // 回溯
        }
        a++; // 回溯
    }
    if (b) // 1*1
    {
        b--;
        dfs(x,y+1); // 下一列
        b++; // 回溯
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>h>>w>>a>>b;
    dfs(1,1);
    cout<<ans;
    return 0;
}
```

**end**

---

## 作者：nightwatch.ryan (赞：0)

### 思路
这道题我们可以使用搜索来做。搜索函数的 $x$ 和 $y$ 表示当前搜到的坐标，接下来我来讲一下搜索函数的逻辑：

- 如果搜到了最后一行，合法的情况就多了一种，答案 $+1$。
- 如果搜到了最后一列，那么就去搜下一行的第一个格子。
- 如果 $a$ 还没有完成，那么向下和向右搜索。
- 如果 $b$ 还没有完成，当前的 $y$ 还没有到最后一列，那么搜索下一列；当前的 $y$ 到了最后一列，就去搜索下一行。

最后输出结果。
### 代码
```cpp
#include<iostream>
int h,w,a,b,result;
int vis[20][20];
void dfs(int x,int y){
	if(x==h){//搜到了最后一行
		result++;//合法答案+1 
		return; 
	} 
	if(y==w){//搜到了最后一列 
		dfs(x+1,0);//去搜下一行 
		return; 
	} 
	if(vis[x][y]){//如果当前格子使用过了 
		dfs(x,y+1);//搜索下一列
		return; 
	}
	if(a>0){
		a--;
		if(x<h-1&&!vis[x+1][y]){
			vis[x+1][y]=true;//标记为使用过
			dfs(x,y+1);
			vis[x+1][y]=false;//回溯 
		}
		if(y<w-1&&!vis[x][y+1]){
			vis[x][y+1]=true;
			dfs(x,y+1);
			vis[x][y+1]=false;
		} 
		a++; 
	}
	if(b>0){
		b--;
		if(y<w-1)dfs(x,y+1);
		if(y==w-1)dfs(x+1,0);
		b++;
	}
}
int main(){
	std::cin>>h>>w>>a>>b;
	dfs(0,0);
	std::cout<<result;
}
```

---

## 作者：small_lemon_qwq (赞：0)

由于 $h\times w$ 非常小，可以考虑 dfs。

思路是在 $h\times w$ 的网格中填入 $1\times 2$ 的长方形，那么剩下的一定可以用 $1\times1$ 的填满。

注意最后要除以 $A!$，因为这些 $1\times 2$ 的长方形顺序不重要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int h,w,x,y,vis[20][20],ans;
void dfs(int k){
	if(k==0){
		ans++;
		return;
	}
	--k;
	for(int i=1;i<=h-1;i++){
		for(int j=1;j<=w;j++){
			if(vis[i+1][j]==0&&vis[i][j]==0){
				vis[i][j]=1;
				vis[i+1][j]=1;
				dfs(k);
				vis[i][j]=0;
				vis[i+1][j]=0;
			}
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w-1;j++){
			if(vis[i][j]==0&&vis[i][j+1]==0){
				vis[i][j]=1;
				vis[i][j+1]=1;
				dfs(k);
				vis[i][j]=0;
				vis[i][j+1]=0;
			}
		}
	}
}
int fun(int x){
	if(x==0)return 1;
	return fun(x-1)*x;
}
signed main(){
	cin>>h>>w>>x>>y;
	dfs(x);
	cout<<ans/fun(x);
	return 0;
}
```

---

