# [NERC 2018] Easy Chess

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) E 题。

## 题目描述

Elma 正在学习象棋。

Elma 是个新手，她还不特别了解象棋是如何下的，所以，为了更好地让她了解象棋，她的奶奶让她从一个棋盘（如下图）中进行 $n$ 次移动，每次移动只能是水平或垂直地移动若干个格子的，且每个点只能到达一次，使得从 a1 到 h8 处。

![](https://cdn.luogu.com.cn/upload/image_hosting/zlooykdb.png)

## 说明/提示

对于所有数据保证 $2 \leq n \leq 63$ 且保证存在至少一种合法方案。

## 样例 #1

### 输入

```
4```

### 输出

```
a1 f1 c1 c8 h8```

# 题解

## 作者：Spark_King (赞：6)

# P9795 [NERC2018] Easy Chess题解

我们直入主题——

## 算法

看到题目，我首先能想到的是 **DFS（深度优先搜索）**。

### 关于深搜

这是一种对状态空间进行枚举，通过穷举来找到最优解，或者统计合法解的个数的算法，能够用来求解这道题。

## 思路

具体思路就是对当前棋子可以走的方向和距离进行搜索并**保存和更新答案**，当**步数超过要求时返回**，直到搜索到在规定步数内到达目的地时输出答案并结束程序。

##  _**AC CODE**_ 

```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗（doge
using namespace std;
int n;
bool mp[10][10];//表示是否访问过
int cnt, step[70][5];//记录答案
bool flag;//标记结束
int dx[5] = {0, 0, 0, 1, -1}, dy[5] = {0, 1, -1, 0, 0};
void dfs(int x, int y) {
	if (x == 8 && y == 8 && cnt == n) {
		for (int i = 1; i <= n; i++) {//输出答案
			char c = 'a' + (char)(step[i][1] - 1);
         		//因为答案中我们存储的是整型，所以要转化为相应字符
			cout << c << step[i][2] << " ";
		}
		flag = 1;//标记已经找到答案，也可以使用 exist(0)
		return;
	}
	if (cnt == n) return;//当步数超过时返回
   	//这个十分重要，本人因此被卡了十分钟
	for (int i = 1; i <= 4; i++) {//枚举方向
		for (int j = 1; j <= 7; j++) {//枚举移动长度
			int kx = x + dx[i] * j, ky = y + dy[i] * j;
			if (kx > 8 || kx < 1 || ky > 8 || ky < 1) continue;//排除越界情况
			if (mp[kx][ky] == 0) {//没有被访问
				mp[kx][ky] = 1;
				cnt++;
				step[cnt][1] = kx, step[cnt][2] = ky;
				dfs(kx, ky);
				cnt--;
				mp[kx][ky] = 0;
				if (flag == 1) return;//已经找到答案，可以继续返回
			}
		}
	}
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);//快读
	cin >> n;
	cout << "a1 ";//先输出第一个位置
	mp[1][1] = 1;//注意预处理第一个位置
	dfs(1, 1);
	return 0;
}
```

---

## 作者：Tjaweiof (赞：4)

# P9795 题解
[题目传送门](https://www.luogu.com.cn/problem/P9795)

一个数学 + 打表的做法。

先在前面几列走 $S$ 形，即，先从 a1 走到 a8，再从 b8 走到 b1……当只剩 $2$ 步的时候，就先走到最后一列，然后去 h8。其它情况特判即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, x = 1, y = 1;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	if (n == 63){
		cout << "a1 a2 a3 a4 a5 a6 a7 a8 b8 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 c8 d8 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 e8 f8 f7 f6 f5 f4 f3 f2 f1 h1 g1 g2 h2 h3 g3 g4 h4 h5 g5 g6 h6 h7 g7 g8 h8";
		return 0;
	}
	cout << "a1 ";
	while (n > 2){
		if (x == 7){
			break;
		}
		if (x & 1){
			if (y == 8){
				x++;
			} else {
				y++;
			}
		} else {
			if (y == 1){
				x++;
			} else {
				y--;
			}
		}
		cout << (char)(x - 1 + 'a') << y << " ";
		n--;
	}
	if (x == 7){
		if (n <= 8){
			for (int i = 1; i < n; i++){
				cout << "h" << i << " ";
			}
			cout << "h8";
		} else if (n == 9){
			cout << "h1 h2 g2 g3 h3 h4 h6 h7 h8";
		} else if (n == 10){
			cout << "h1 h2 g2 g3 h3 h4 h5 h6 h7 h8";
		} else if (n == 11){
			cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h7 h8";
		} else if (n == 12){
			cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 h7 h8";
		} else if (n == 13){
			cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 g6 g8 h8";
		} else if (n == 14){
			cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 g6 g7 g8 h8";
		}
	} else if (y == 8){
		cout << (char)(x + 'a') << "8 h8";
	} else {
		cout << "h" << y << " h8";
	}
	return 0;
}

```

---

## 作者：sherry_lover (赞：3)

# P9795 [NERC2018] Easy Chess 题解

[题目传送门](https://www.luogu.com.cn/problem/P9795)

看到了各位巨佬发的 DFS 题解，本蒟蒻不会 DFS（其实是懒得写），就用打表过了这一题。

主要思路是把走到 $h$ 列前面的步数耗掉（固定），最后剩几步再循环输出。如果步数 $>52$，最后两列规律不多，故直接打表即可。

目前最优解，[提交记录](https://www.luogu.com.cn/record/163778840)。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin >> n;
	cout << "a1 ";
	if(n <= 8){
		for(int i = 1;i <= n-2;i++) cout << char('a'+i) << "1 ";
		cout << "h1 h8";
	}
	else if(n <= 14){
		cout << "b1 c1 d1 e1 f1 g1 h1 ";
		for(int i = 1;i <= n-8;i++) cout << 'h' << 1+i << " ";
		cout << "h8";
	}
	else if(n <= 20){
		cout << "a2 b2 b1 c1 c2 d2 d1 e1 e2 f2 f1 g1 g2 h2 ";
		for(int i = 2;i <= n-14;i++) cout << 'h' << 1+i << " ";
		cout << "h8";
	}
	else if(n <= 26){
		cout << "a2 a3 b3 b2 b1 c1 c2 c3 d3 d2 d1 e1 e2 e3 f3 f2 f1 g1 g2 h2 ";
		for(int i = 2;i <= n-20;i++) cout << 'h' << 1+i << " ";
		cout << "h8";		
	}
	else if(n == 27) cout << "a2 a3 a4 a5 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 h5 h6 h8 ";
	else if(n <= 34){
		cout << "a2 a3 a4 b4 b3 b2 b1 c1 c2 c3 c4 d4 d3 d2 d1 e1 e2 e3 e4 e5 f5 f4 f3 f2 f1 g1 h1 ";
		for(int i = 1;i <= n-28;i++) cout << 'h' << 1+i << " ";
		cout << "h8";		
	}	
	else if(n <= 40){
		cout << "a2 a3 a4 a5 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 d6 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 f6 f5 f4 f3 f2 f1 g1 h1 ";
		for(int i = 1;i <= n-35;i++) cout << 'h' << 1+i << " ";
		cout << "h8";			
	}
	else if(n <= 46){
		cout << "a2 a3 a4 a5 a6 a7 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 f7 f6 f1 g1 h1 ";
		for(int i = 1;i <= n-40;i++) cout << 'h' << 1+i << " ";
		cout << "h8";				
	}
	else if(n <= 52){
		cout << "a2 a3 a4 a5 a6 a7 a8 b8 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 c8 d8 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 e8 f8 f7 f6 f5 f1 g1 h1 ";
		for(int i = 1;i <= n-47;i++) cout << 'h' << 1+i << " ";
		cout << "h8";	
	}
	else if(n <= 62)
	{
		cout << "a2 a3 a4 a5 a6 a7 a8 b8 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 c8 d8 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 e8 f8 f7 f6 f5 f4 f3 f2 f1 g1 ";
		if(n == 53) cout << "h1 h2 h3 h4 h8";
		else if(n == 54) cout << "h1 h2 h3 h4 h5 h8";
		else if(n == 55) cout << "h1 h2 h3 h4 h5 h6 h8";
		else if(n == 56) cout << "h1 h2 h3 h4 h5 h6 h7 h8";
		else if(n == 57) cout << "h1 h2 g2 g3 h3 h4 h5 h6 h8";
		else if(n == 58) cout << "h1 h2 g2 g3 h3 h4 h5 h6 h7 h8";
		else if(n == 59) cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 h8";	
		else if(n == 60) cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 h7 h8";	
		else if(n == 61) cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 g6 g8 h8";	
		else if(n == 62) cout << "h1 h2 g2 g3 h3 h4 g4 g5 h5 h6 g6 g7 g8 h8";	
	}
	else cout << "a2 a3 a4 a5 a6 a7 a8 b8 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 c8 d8 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 e8 f8 f7 f6 f5 f4 f3 f2 f1 h1 g1 g2 h2 h3 g3 g4 h4 h5 g5 g6 h6 h7 g7 g8 h8";
	return 0;
}
```

---

## 作者：lilong (赞：2)

由于题目保证有解并且只需要找到一组解，因此可以直接爆搜，记录经过的点并判断是否到达终点即可。枚举时先枚举上下移动，再枚举左右移动，可以尽快到达终点，优化复杂度。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int n,m,x[110],y[110],ansx[110],ansy[110],vis[11][11],flag;
void dfs(int a,int b,int k){
    if(flag)return;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=7;j++){
            int c=a+dx[i]*j,d=b+dy[i]*j;
            if(c<1||c>8||d<1||d>8)continue;
            if(vis[c][d])continue;
            vis[c][d]=1;
            x[k]=c,y[k]=d;
            if(k==n){
                if(x[n]==8&&y[n]==8){
                    flag=1;
                    for(int l=1;l<=n;l++)
                        ansx[l]=x[l],ansy[l]=y[l];
                }
            }
            else dfs(c,d,k+1);
            vis[c][d]=0;
        }
    }
}
int main(){
    cin>>n;
    vis[1][1]=1;
    dfs(1,1,1);
    cout<<"a1 ";
    for(int i=1;i<=n;i++)
        cout<<char(ansx[i]+'a'-1)<<ansy[i]<<' ';
    return 0;
}
```

---

## 作者：lbh666 (赞：2)

看到题解区的各位大佬各显神通，本蒟蒻也来发一篇数学和蛇形方阵的做法。

### 思路分析

总共分三种情况讨论：

**情况一**：$2 \le n \le 56$。

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/x21thxom.png)

我们根据蛇形方阵在每一行走 $S$ 型路线，上图红色为从左往右的路线，蓝色为从右往左的路线。

在红色与蓝色的路线上，每个位置都可以用两步抵达终点。例如上图绿色路线，从 f3 出发，经过中转点 f8 抵达终点 h8。

h3 虽然和 h8 在同一列上，但仍然可以通过中转点 h5 再到达终点（如上图粉色路线）。

- 经上述分析，$2 \le n \le 56$ 的情况可简化为先用 $n - 2$ 步在蛇形方阵上走，再用 $2$ 步抵达终点。

但是蛇形方阵走到第 $8$ 行时，方向是由右往左的。这时我们不能再使用上述方法，否则终点就会被提前经过，结论就不成立了。所以我们要**分类讨论**。

**情况二**：$57 \le n \le 62$。

这种情况下，第 $7$ 行在蛇形方阵中只能走一格，也就是走到 a7。

因为如果第 $7$ 行走满，第八行就很有可能被用上，违背结论。若没走满且走了大于一格，那么第 $8$ 行的空间就会被浪费，在 $n = 62$ 的情况下无法构造出来。

接着考虑如何走。手动模拟发现，再竖着做一个蛇形方阵，除 h7 外的空间都能利用上，构造成功，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/tpdcc0qx.png)

在 $n = 62$ 时，蛇形方阵最多走到 g7，不能再走了。在第 $7$ 行与第 $8$ 行中的红蓝路线上，每个位置也都可以通过两步抵达终点。

又因为走到 a7 的蛇形方阵有 $48$ 步，再经上述分析得，$57 \le n \le 62$ 的情况可简化为先用 $48$ 步走到 a7，再竖着走蛇形方阵，走 $n - 48 - 2$ 步后再用 $2$ 步抵达终点。

**情况三**：$n = 63$。

如下图所示，因为只有一种情况，直接打表输出即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/z8ndhdk3.png)

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;

int n,m;
int x=1,y=1;
bool flag=0;

void print(int x,int y){
	cout<<(char)(y-1+'a')<<x<<" ";
}

void solve(){
	while(m--){
		if(!flag)y++;//通过flag变换方向 
		else y--;
		if(y>8)y=8,flag=1,x++;//边界，如果越界，说明方向要换了 
		if(y<1)y=1,flag=0,x++;
		print(x,y);//调用打印函数 
	}
} 

signed main(){
	cin>>n;
	m=n-2;
	printf("a1 ");//起点 
	if(n==63){
		m=48;
		solve();//前48步蛇形方阵 
		cout<<"a8 b8 b7 c7 c8 d8 d7 e7 e8 f8 f7 h7 g7 g8 h8";//直接打表输出 
		return 0;
	}
	if(n>=57 && n!=63){//57<=n<=62的情况 
		m=48;
		int k=n-m-2;//竖着的蛇形方阵需要走几步 
		solve();//前48步蛇形方阵 
		while(k--){//n-m-2步竖着的蛇形方阵 
			if(!flag){
				if(x==8)x--;
				else x++; //根据实际情况变换 
			}
			if(flag)y++;
			flag=!flag; //方向转换 
			print(x,y);
		}
		if(x==7){//剩下两步的特判 
			print(x,8);
			cout<<"h8\n";
		}else{
			print(x,y+1);
			cout<<"h8\n";
		}
		return 0;
	}
	//2<=n<=56的情况 
	solve(); 
	if(y==8){//剩下两步的特判 
		print(x+1,y);
		cout<<"h8\n";
	}else{
		print(8,y);
		cout<<"h8\n";
	}
	return 0;
}
```

**结尾语**：感谢管理员的用心审核，完结撒花！

---

## 作者：lutaoquan2012 (赞：2)

### 思路：
这道题一样看过去是一个几乎模拟版的 DFS。

我们这道题他的数据点无论怎么都是有解的，所以指数要一直遍历就行了，直到找到有解的方案。

每次把这个 DFS 按照方向的位置和步数去遍历，如果出界了那么跳过这个点，不然看他有没有来过，题目中说明**每个点只能到达一次**，所以如果没有来过的话就进行深搜并记录，返回时再进行回溯。

### 代码：
```cpp
//
// Created by 55062 on 2024/1/11.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, step_x[100], step_y[100], Map[100][100];
int dx[10] = {1, -1, 0, 0}, dy[10] = {0, 0, 1, -1};//方向数组

//step_x、step_y记录第几步到了那个位置，map记录这个点有没有到过。
void dfs(ll x, ll y, ll t) {
    if (x == 8 && y == 8 && t == n) {//已经到达了h8这个点
        for (int i = 1; i <= n; i++) {//输出
            char a = char(step_x[i] - 1) + 'a';
            cout << a << step_y[i] << " ";
        }
        exit(0);//这个是在任何地方如果运行了，就直接结束程序
    }
    if (t == n) return;//如果步数超过了给的值，那么跳出
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 7; j++) {//枚举移动的步数
            ll nx = x + dx[i] * j, ny = y + dy[i] * j;
            if (nx >= 9 || nx <= 0 || ny >= 9 || ny <= 0) continue;
            if (Map[nx][ny] == 0) {//没有来过，题目说明一个点这能走过一次
                Map[nx][ny] = 1;
                step_x[t + 1] = nx, step_y[t + 1] = ny;
                dfs(nx, ny, t + 1);
                Map[nx][ny] = 0;
                //这里不用再次清空step_x,step_y，因为这个地方以后会被覆盖掉
            }
        }
    }
}

int main() {
    cin >> n;
    cout << "a1 ";
    Map[1][1] = 1;
    dfs(1, 1, 0);
    return 0;
}
```

---

## 作者：ganyu1 (赞：2)

# P9795 Easy Chess题解
# [题目传送门](https://www.luogu.com.cn/problem/P9795)
## 前置知识
* DFS 全称是 Depth First Search，中文名是深度优先搜索，是一种用于遍历或搜索树或图的算法。所谓深度优先，就是说每次都尝试向更深的节点走。

* 模板：
```cpp
DFS(v) // v 可以是图中的一个顶点，也可以是抽象的概念，如 dp 状态等。
  在 v 上打访问标记
  for u in v 的相邻节点
    if u 没有打过访问标记 then
      DFS(u)
    end
  end
end
```



详情参考 OI WIKI : [DFS](https://oi-wiki.org/graph/dfs/)
## 分析
实际上这是一道很水的 DFS，本题数据范围不大，可以随意枚举。只需在 DFS 模板中加一个枚举棋子步数的循环，便可以轻松 AC。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[100][2];//ans记录答案 
int vis[10][10];//存储走过的地方 
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
void dfs(int x,int y,int step){
	if(x==8&&y==8&&step>n){
		for(int i=1;i<=n;i++) cout<<char(96+ans[i][1])<<ans[i][2]<<" ";//输出 
		exit(0);//找到了一种办法直接exit(0)跑路 
	}
	if(step>n) return ;//很重要，蒟蒻忘写差点噶 
	for(int i=0;i<4;i++){//四个方向 
		for(int j=1;j<=7;j++){//枚举棋子步数 
			int sx=x+dx[i]*j; 
			int sy=y+dy[i]*j;//将dx和dy定义为0,1,-1目的是为了这里方便乘步数，方便快捷 
			if(sx>8||sx<1||sy>8||sy<1||vis[sx][sy]) continue;//判断 
			vis[sx][sy]=1;//标记 
			ans[step][1]=sx;
			ans[step][2]=sy;//记录答案 
			dfs(sx,sy,step+1);
			vis[sx][sy]=0;// 回溯 
		}
	}
	return ;//可写可不写 
}
int main(){ 
	cin>>n;
	n++;//加上第一步初始位置 
	ans[1][1]=ans[1][2]=1;//将第一步录入ans 
	vis[1][1]=1;//初始位置标记 
	dfs(1,1,2);//step为1时就是初始位置，所以直接把step初始为2 
	return 0;
}
//完结撒花 
```
## 后记
### 码风奇怪，不喜勿喷。

---

## 作者：tangzirui1016 (赞：0)

来篇不一样的题解。

大部分的题解都是 dfs，但是这题显然可以找规律。

![](https://i.imgs.ovh/2025/08/14/tJMF0.webp)

显然对于 $n\le 56$，前 $n-2$ 步可以这么走，最后剩下两步走到这一列的顶部，再走到终点。特殊的，如果前 $n-2$ 步走到最后一列，那么第 $n-1$ 步就走到终点下面一格，再走到终点。

![](https://i.imgs.ovh/2025/08/14/tJP9Y.webp)

对于 $n>56$，显然可以这么走，一直走到浅蓝色的箭头，用掉 $56$ 步，最后在顶部转一下再去终点即可。

代码也比较好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,c,step;
int main(){
	cin>>n;
	for(i=1,c=0;i<=8&&step<min(n,55)-1;i++,c^=1){
		if(!c){
			for(j=1;j<=8&&step<min(n,55)-1;j++,step++)
				cout<<char('a'+j-1)<<i<<' ';
			j--;
		}
		else{
			for(j=8;j>=1&&step<min(n,55)-1;j--,step++)
				cout<<char('a'+j-1)<<i<<' ';
			j++;
		}
	}
	if(n==56) cout<<"g7 ",j++;
	if(n<=56){
		cout<<char('a'+j-1)<<(j==8?7:8)<<' ';
		cout<<"h8";
	} 
	else{
		n-=56; step=0;
		cout<<"h7 g7 g8 ";
		for(j=6;j>=1&&step<n-1;j--,step++) 
			cout<<char('a'+j-1)<<"8 ";
		cout<<"h8";
	}
	return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P9795)
# 思路
这道题可以直接使用 DFS 来写。

每一次枚举棋子的方向和走动的距离，当步数超过 $n$ 时跳过，直到棋子**恰好** $n$ 步走到目的地时结束。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int cnt=0;
int n;
const int N=8+5;
int box[N*N][2];
bool vis[N][N];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
void dfs(int x,int y)
{
	if(x==8 && y==8 && cnt==n)
	{
		for(int i=1;i<=cnt;i++)
		{
			char c=box[i][1]+'a'-1;
			cout <<c<<box[i][2]<<' ';
		}
		exit(0);
	}
	if(cnt==n) return;
	for(int i=0;i<4;i++)
	{
		for(int len=1;len<=7;len++)
		{
			int nx=x+dx[i]*len;
			int ny=y+dy[i]*len;
			if(nx>8 || nx<1 || ny>8 || ny<1) continue;
			if(vis[nx][ny]) continue;
			
			vis[nx][ny]=1;
			cnt++;
			
			box[cnt][1]=nx;
			box[cnt][2]=ny;
			
			dfs(nx,ny);
			
			vis[nx][ny]=0;
			cnt--;
		}
	}
}
signed main()
{
	cin >>n;
	cout <<"a1"<<' ';
	vis[1][1]=1;
	dfs(1,1);
	return 0;
}

```

---

## 作者：Liuliuliuliuliu (赞：0)

# 思路

做题好习惯：先看数据范围。发现 $2 \le n \le 63$。哎，再一看题，国际象棋，很容易联想到八皇后问题（用 dfs 解决）。因此顺着这个思路想下去，发现 dfs 好像真的可以解决。

接下来考虑怎样 dfs。肯定是从 a1 出发 h8 结束。初始位置和结束位置都有了，那么接下来就是中间位置。发现只能往上、下、左、右四个方向移动（一次可以移动 $k(1 \le k \le 7)$ 次）。于是遍历中间位置的代码也就出来了。

```
const int fx[][2]={{-1,0},{1,0},{0,-1},{0,1}};//方向数组
for(int i=0;i<4;i++){
  do something...
  for(int l=1;l<=7;l++){//枚举上文中的 k
    int dx=x+fx[i][0]*l,dy=y+fx[i][1]*l;//下一个位置
    then do something...
  }
}
```

# code
```
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long 
#define INF 0x3f3f3f3f
inline int Read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int N=70;
const int fx[][2]={{-1,0},{1,0},{0,-1},{0,1}}; //方向数组
int n;
int stx[N],sty[N],tot=0;//答案数组
int vis[N][N];//标记每个点是否被找到过
bool fl=0;//记录是否已经找到答案
void dfs(int x,int y,int cnt){
	if(cnt==n&&x==8&&y==8){//到终点并且满足步数条件
		for(int i=1;i<=n;i++){
			cout<<(char)(stx[i]+'a'-1)<<sty[i]<<" ";
		}
		fl=1;
		return ;
	} 
	if(fl) return ;
	if(cnt==n) return ;//*
	for(int i=0;i<4;i++){
		if(fl) return ;//因为不放心所以多加了几个
		for(int l=1;l<=7;l++){
			int dx=x+fx[i][0]*l,dy=y+fx[i][1]*l;
			if(dx<1||dy<1||dx>8||dy>8||vis[dx][dy]) continue;
			vis[dx][dy]=1;
			stx[++tot]=dx;sty[tot]=dy;
			dfs(dx,dy,cnt+1);
			vis[dx][dy]=0;
			--tot;
			if(fl) return ;
		}
	}
	if(fl) return ;
}
signed main(){
	n=Read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=0;
	vis[1][1]=1;
	cout<<"a1 ";
	dfs(1,1,0); 
	return 0;
} 
```

---

## 作者：_XXX_ (赞：0)

本蒟蒻的第一篇题解，管理员大大求过 awa 
## 前置知识： OI Wiki [DFS](https://oi-wiki.org/graph/dfs/)
## [题目传送门](https://www.luogu.com.cn/problem/P9795)

# 题目大意

给定一个 $8 \times 8$ 的棋盘，要从 $(1,1)$ 走到 $(8,8)$ ，每次可垂直或水平移动若干格，并且每格只能走一次。求恰好走 $n$ 步时的一种可行路径（输入数据保证至少有一种解）。

# 思路

求一种可行路径，显然是一道很水的 DFS 题，几乎是模版。  
废话不多说，直接看代码。

# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};//方向数组
//ps:写方向数组的时候千万要注意！！！不信你可以改成{0,1,0,-1}和{1,0,-1,0}试试
int n,ans_x[100],ans_y[100];//记录所走的点
bool vis[10][10];//标记某点是否被访问过
inline void dfs(int x,int y,int t){
    if(x==8&&y==8&&t==n){//到了终点而且步数刚好用完
        for(int i = 1;i <= n;i++)//输出答案
            cout << char(ans_x[i]-1+'a') << ans_y[i] << " ";
        exit(0);//输出一种可行解后结束程序，省去不必要的时间
    }
    if(t>=n)return ;//若步数超过就返回
    for(int i = 0;i < 4;i++){//枚举方向
        for(int j = 1;j < 8;j++){//枚举步长
            int nx=x+dx[i]*j,ny=y+dy[i]*j;
            if(nx>=1&&nx<=8&&ny>=1&&ny<=8&&!vis[nx][ny]){//若该点不越界且未访问过
                vis[nx][ny]=1;//标记
                ans_x[t+1]=nx,ans_y[t+1]=ny;//记录答案
                dfs(nx,ny,t+1);
                vis[nx][ny]=0;//回溯
                //ans_x和ans_y不需要修改，因为会被覆盖的
            }
        }
    }
    return ;
}
int main(){
    cin >> n;
    //先把第一格占了
    cout << "a1 ";
    vis[1][1]=1;
    dfs(1,1,0);
    return 0;
}
``````

---

## 作者：aaa_lvzekai (赞：0)

## 题面

[CLOCKS - The Clocks](https://www.luogu.com.cn/problem/SP7216)

## 做法

看到 $2 \leq n \leq 63$，肯定是暴力 **DFS**，每次枚举方向 $i$ 和步数 $j$，表示往 $i$ 方向走 $j$ 步。考虑一些细节：

- 当步数超出 $n$ 时，记得不管如何都得 **返回**。

**DFS** 介绍：

深度优先搜索（Depth-First Search，简称 DFS）是一种常用的图遍历算法，常用于解决与图相关的问题。DFS 从起始节点开始，沿着路径尽可能深入图中的顶点，直到无法继续前进，然后回溯到上一个节点，继续探索其他路径，直到遍历完整个图。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=110;
ll n,dx[]={1,-1,0,0},dy[]={0,0,1,-1},ans[N][N],step;
bool vis[N][N];
void dfs(ll x,ll y)
{
	if(step==n+1)
	{
		if(x==8&&y==8)
		{
			for(int i=1;i<=n+1;i++)
			{
				cout<<(char)(ans[i][1]+'a'-1)<<ans[i][2]<<" ";
			}
			cout<<"\n";
			exit(0);
		}
		else
		{
			return;
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<=7;j++)
		{
			ll mx=x+dx[i]*j,my=y+dy[i]*j;
			if(mx>=1&&mx<=8&&my>=1&&my<=8&&!vis[mx][my])
			{
				vis[mx][my]=true;
				step++;
				ans[step][1]=mx,ans[step][2]=my;
				dfs(mx,my);
				step--;
				vis[mx][my]=false;
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	vis[1][1]=true;
	ans[1][1]=1,ans[1][2]=1,step=1;
	dfs(1,1);
	return 0;
}
```

**警示后人：**

一定要这么写：

```cpp
dx[]={1,-1,0,0},dy[]={0,0,1,-1}
```

如果这么写：

```cpp
dx[]={0,1,0,-1},dy[]={1,0,-1,0}
```

你只会得 20 分。

---

## 作者：keepwatcher_kensap (赞：0)

## Part 1 题意

有一个 $8 \times 8$ 的棋盘，你将从 $(1,1)$ 走到 $(8,8)$，每次可以水平或垂直移动若干格，要求**恰好**走 $n$ 步并且走的路径中**不能**重复经过同一格。要求编程给出一种走法。

## Part 2 思路

鉴于只需要求出其中一种方法即可，并且要在若干种可能的情况中找到其中一种符合要求的情况，所以考虑使用**深度优先搜索算法**。

每次都搜索下一格的位置，当下一格符合要求的时候就考虑下一格的情况。当检测到步数为 $n$ 的时候就判断是否符合要求。若符合则输出并停止程序，否则回溯并搜索其他种情况。

## Part 3 代码

```
#include <bits/stdc++.h>
using namespace std;
int fx[10]={0,1,-1,0,0};
int fy[10]={0,0,0,1,-1};
int n,resultx[105],resulty[105];
bool vis[105][105],empty=false;
inline void found(int s,int x,int y)
{
	if (empty) return ;
	if (s==n+1)
	{
		if (x==8 && y==8)
		{
			for (int i=1;i<=n;i++) cout<<char('a'+resultx[i]-1)<<resulty[i]<<" ";
			empty=true;
		}
		return ;
	}
	for (int i=1;i<=4;i++) for (int j=1;j<=7;j++)
	{
		int nx=x+fx[i]*j,ny=y+fy[i]*j;
		if (nx<1 || nx>8 || ny<1 || ny>8 || vis[nx][ny]) continue;
		vis[nx][ny]=true,resultx[s]=nx,resulty[s]=ny;
		found(s+1,nx,ny),vis[nx][ny]=false;
	}
	return ;
}
int main()
{
	cin>>n;
	cout<<"a1 ";vis[1][1]=true;
	found(1,1,1);
	return 0;
}
```

---

## 作者：kinglf (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P9795)
## 题意分析：

进行 $n$ 次移动，每次移动只能是水平或垂直地移动若干个格子的，且每个点只能到达一次，使得从 a1 到 h8 处。

## 思路：
先看数据范围，惊奇地发现，$n\le 63$，且棋盘始终为 $8\times 8$，可以暴力枚举方案，直接用 dfs 秒掉。

## 代码 code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,cnt,ans[105],vis[15][15];
ll dx[]={0,1,-1,0,0};
ll dy[]={0,0,0,-1,1};//位移数组 
void print(){
	for (ll i=1;i<=n;i++)
		cout<<char('a'-1+ans[i]%105)<<ans[i]/105<<" ";//输出 
}
void dfs (ll x,ll y,ll step){
	if (x==8&&y==8&&step>n){//判断是否满足条件 
		print();
		exit(0);//直接结束搜索 
	}
	if (step>n) return ;
	for (ll i=1;i<=4;i++){//四个方位 
		for (ll j=1;j<=7;j++){//最多可以走7格 
			ll nx=x+dx[i]*j; 
			ll ny=y+dy[i]*j;
			if (nx<=8&&nx>=1&&ny<=8&&ny>=1&&!vis[nx][ny]){//判断是否越界或走过 
				vis[nx][ny]=1;//标记走过 
				ans[step]=nx*105+ny;//记录答案 
				dfs (nx,ny,step+1);
				ans[step]=0;
				vis[nx][ny]=0;//回溯 
			}
		}
		
	}
}
int main(){
	scanf ("%lld",&n);
	n++; 
	ans[1]=1*105+1;//起点加入答案 
	vis[1][1]=1;//标记起点走过 
	dfs (1,1,2);//快乐搜索 
	


	return 0;
}
```


---

## 作者：niuzh (赞：0)

### 思路

不难的一个深搜题，只要根据题意进行 dfs 即可。

重点在于方向转移需要按类似于上下左右的顺序枚举，否则会超时。

比如若 $n=63$ 的时候路径就要把每一个点都走一遍，而若方向转移是按顺序枚举类似于上右下左。会先枚举出阶梯状，让后进行多个回溯才可以给出答案，而按类似于上下左右的顺序枚举时则第一次就会给出除去最后两行较为正确的路径，时间会大大减少。

### 代码

```cpp
/*
 * @FilePath: P9795 Easy Chess.cpp
 * @Author: niu-zh
 */
#include <bits/stdc++.h>
using namespace std;
const int dx[]= {1,-1,0,0},dy[]= {0,0,1,-1};//方向转移
struct node
{
	int x,y;
} ans[64];//记录答案的数组
int n,cnt;
bool flag,f[9][9];//flag 用来表示是否已到达终点
void dfs(int d,int x,int y)
{
	if (d!=n&&x==8&&y==8)
	{
		return;
	}
	if (d==n)
	{
		flag=true;
		return;
	}
	for (int i=0; i<4; i++)
	{
		for (int j=1; j<8; j++)//4个方向，每个方向可以走1到7个格子
		{
			int nx=x+dx[i]*j,ny=y+dy[i]*j;
			if (nx>8||nx<1||ny>8||ny<1||(d==n-1&&(nx!=8||ny!=8))||f[nx][ny]||(d!=n-1&&nx==8&&ny==8))//特判
			{
				continue;
			}
			f[nx][ny]=true;//记录已走过
			dfs(d+1,nx,ny);
			f[nx][ny]=false;//回溯
			if (flag)
			{
				ans[++cnt].x=x;//记录答案
				ans[cnt].y=y;
				return;
			}
		}
	}
}
int main()
{
	cin>>n;
	f[1][1]=true;//第一个点永远走过
	dfs(0,1,1);
	for (int i=n; i>=1; i--)
	{
		cout<<char('a'+ans[i].x-1)<<ans[i].y<<" ";//输出答案
	}
	cout<<"h8";
	return 0;
}
```

---

## 作者：Yuki_Ever (赞：0)



# 洛谷 P9795

#### 前置知识：DFS 相关知识



------------
## Solution
直接进行 dfs，函数参数设置为当前位置的横纵坐标与已经走过的步数。每次递归分别枚举本次往哪个方向走、走几步即可。边界条件考虑位置是否合法，是否到达步数。

此外，题目要求输出一条合法路径。可以这样考虑：定义一个布尔类型的数 $flag$，初始化为 0，当 dfs 成功后，将 $flag$ 改为 1 并立刻返回函数，在函数返回处后增加判断，如果 $flag$ 为 1，记录当前位置，在函数返回到主函数后逆向打印即可。

另外，注意判断一个点是否已经到达。我们定义一个函数来判断。将边界条件的判断放在修改此函数前的位置，这样，只需要在函数末尾返回时“复原现场”，进行回溯。

最后，在主函数中，用一个 char 数组把记录位置的数组换成字符。

具体详见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
bool flag=0;  //判断是否成功 
bool f[20][20]; //判断是否去过，注意开大一点，避免数组越界 
int rec[65][2]; //位置记录数组 
int tot=0; //rec数组的指针 
void dfs(int dep,int x,int y){
	//边界判断 
	if(f[x][y]==1){return;}
	if(x>8||y>8)return;
	if(x<=0||y<=0)return;
	if(dep==n&&(x!=8||y!=8))return;
	f[x][y]=1;
	//判成功与否 
	if(dep==n){flag=1;return;}
	//枚举方向和步数 
	for(int i=1;i<=8;i++){
		dfs(dep+1,x+i,y);
		if(flag==1){rec[tot][0]=x-1,rec[tot++][1]=y;return;}
		dfs(dep+1,x-i,y);
		if(flag==1){rec[tot][0]=x-1,rec[tot++][1]=y;return;}
		dfs(dep+1,x,y+i);
		if(flag==1){rec[tot][0]=x-1,rec[tot++][1]=y;return;}
		dfs(dep+1,x,y-i);
		if(flag==1){rec[tot][0]=x-1,rec[tot++][1]=y;return;}
	}
	//回溯，还原数组 
	f[x][y]=0;
}

int main() {
	scanf("%d",&n);
	dfs(0,1,1);
	char c[n];
	//将数字转成字符 
	for(int i=0;i<tot;i++)c[i]='a'+rec[i][0];
	//打印方案 
	for(int i=tot-1;i>=0;i--)cout<<c[i]<<rec[i][1]<<" ";
	//由于未记录末尾地即h8，补打印 
	cout<<"h8"<<endl;
	return 0;
}
```



------------
题目时间不紧，使用此法无需其他优化，在写 dfs 时，考虑好如何最优化、最简化程序，可减少码量，减少出错与卡时的可能性。



---

## 作者：哈哈人生 (赞：0)

# 思路
直接 dfs 即可，所有路径全都搜一遍。dfs 有三个参数，分别是当前所在行、当前所在列、步数。如果步数到了 $n$，就所在点是否为终点，这样的思路时间不会炸完全是因为棋盘较小。由于一个点不能重复走，所以用数组标记，一个简简单单的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[105],y[105],book[105][105];
void dfs(int xx,int yy,int bs){
	if(bs==n+1){
		if(xx==8&&yy==8){
			cout<<"a1 ";
			for(int i=1;i<=n;i++){
				cout<<char(x[i]+'a'-1)<<y[i]<<" "; 
			}
			exit(0);
		}
		return;
	}
    //四个方向搜
	for(int i=1;xx+i<=8;i++){
		if(book[xx+i][yy])continue;
		book[xx+i][yy]=1;
		x[bs]=xx+i,y[bs]=yy;
		dfs(xx+i,yy,bs+1);
		book[xx+i][yy]=0;
	}
	for(int i=1;xx-i>=1;i++){
		if(book[xx-i][yy])continue;
		book[xx-i][yy]=1;
		x[bs]=xx-i,y[bs]=yy;
		dfs(xx-i,yy,bs+1);
		book[xx-i][yy]=0;
	}
	for(int i=1;yy+i<=8;i++){
		if(book[xx][yy+i])continue;
		book[xx][yy+i]=1;
		x[bs]=xx,y[bs]=yy+i;
		dfs(xx,yy+i,bs+1);
		book[xx][yy+i]=0;
	}
	for(int i=1;yy-i>=1;i++){
		if(book[xx][yy-i])continue;
		book[xx][yy-i]=1;
		x[bs]=xx,y[bs]=yy-i;
		dfs(xx,yy-i,bs+1);
		book[xx][yy-i]=0;
	}
}
int main(){
	cin>>n;
	book[1][1]=1;
	dfs(1,1,0);
	cout<<-1;//这个不会被执行，因为题目保证有解
	return 0;
}
```
这样就可以获得 $98$ 分的高分。由于只超时了 $n=63$ 的一个测试点，所以考虑特判。当 $n=63$ 的时候，就意味着每个点都走一遍，我们可以先把前六行完，在从第七行开始直接输出。特判具体实现请看代码。满分代码送上：

## 满分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[105],y[105],book[105][105];
void dfs(int xx,int yy,int bs) {
	if(bs==n+1) {
		if(xx==8&&yy==8) {
			cout<<"a1 ";
			for(int i=1; i<=n; i++) {
				cout<<char(x[i]+'a'-1)<<y[i]<<" ";
			}
			exit(0);
		}
		return;
	}
	for(int i=1; xx+i<=8; i++) {
		if(book[xx+i][yy])continue;
		book[xx+i][yy]=1;
		x[bs]=xx+i,y[bs]=yy;
		dfs(xx+i,yy,bs+1);
		book[xx+i][yy]=0;
	}
	for(int i=1; xx-i>=1; i++) {
		if(book[xx-i][yy])continue;
		book[xx-i][yy]=1;
		x[bs]=xx-i,y[bs]=yy;
		dfs(xx-i,yy,bs+1);
		book[xx-i][yy]=0;
	}
	for(int i=1; yy+i<=8; i++) {
		if(book[xx][yy+i])continue;
		book[xx][yy+i]=1;
		x[bs]=xx,y[bs]=yy+i;
		dfs(xx,yy+i,bs+1);
		book[xx][yy+i]=0;
	}
	for(int i=1; yy-i>=1; i++) {
		if(book[xx][yy-i])continue;
		book[xx][yy-i]=1;
		x[bs]=xx,y[bs]=yy-i;
		dfs(xx,yy-i,bs+1);
		book[xx][yy-i]=0;
	}
}
int main() {
	cin>>n;
	if(n==63) {
		for(int i=1; i<=6; i++) {
			if(i&1) {
				for(int j=1; j<=8; j++)cout<<char('a'+j-1)<<i<<" ";
			} else {
				for(int j=8; j>=1; j--)cout<<char('a'+j-1)<<i<<" ";
			}
		}
		cout<<"a7 a8 b8 b7 c7 c8 d8 d7 e7 e8 f8 f7 h7 g7 g8 h8";
		return 0;
	}
	book[1][1]=1;
	dfs(1,1,0);
	cout<<-1;
	return 0;
}
```
点个赞呗。

---

## 作者：qzmoot (赞：0)

# 题目大意
给你一个车在左下角，其他位置没有任何棋子，然后让你在 $n$ 步之内走到右上角。每个位置只能经过一次，且输出该位置的坐标。
# 分析
我看到这题，直接就想到了 dfs，咔咔咔敲完。
```cpp
#include<bits/stdc++.h>
#define mk(x,y) make_pair(x,y)
using namespace std;
typedef pair<int,int> pii;
int n;
bool book[10][10],flag;
vector<pii> ans;
void dfs(int x,int y,int step)
{
    if(flag)
		return;
    if(step>n)
		return;
    if(step==n && x==8 && y==8)
	{
		flag=1;
		return;
	}
    for(int i=1;i<=8;i++)
    {
        if(!book[i][y])
        {
            ans.push_back(mk(i,y));
			book[i][y]=1;
            dfs(i,y,step+1);
            if(flag)
				return;
            ans.pop_back();
			book[i][y]=0;
        }
        if(!book[x][i])
        {
            ans.push_back(mk(x,i));
			book[x][i]=1;
            dfs(x,i,step+1);
            if(flag)
				return;
            ans.pop_back();
			book[x][i]=0;
        }
    }
}
int main()
{
	cin>>n;
    ans.push_back(mk(1,1));
	book[1][1]=1;
    flag=0;
	dfs(1,1,0);
    for(int i=0;i<ans.size();i++)
    {
        if(i>0)
			printf(" ");
        printf("%c%d",'a'+ans[i].first-1,ans[i].second);
    }
    return 0;
}
```
直接 [TLE](https://www.luogu.com.cn/record/132055658)。

既然在 $n=57$ 时间超限，那我们就直接找到 $n=56$ 的最优策略再对于最后的地点小小地特判不就行了？

```cpp
#include<bits/stdc++.h>
#define mk(x,y) make_pair(x,y)
using namespace std;
typedef pair<int,int> pii;
int n;
bool book[10][10],flag;
vector<pii> ans;
void dfs(int x,int y,int step)
{
    if(flag)//到步数限制了，并且到了 
		return;
    if(step>n)
		return;
    if(step==n && x==8 && y==8)
	{
		flag=1;
		return;
	}
    for(int i=1;i<=8;i++)
    {
    	//不同的方向 
        if(!book[i][y])//向左右 
        {
            ans.push_back(mk(i,y));
			book[i][y]=1;
            dfs(i,y,step+1);
            if(flag)
				return;
            ans.pop_back();
			book[i][y]=0;
        }
        if(!book[x][i])//向上下 
        {
            ans.push_back(mk(x,i));
			book[x][i]=1;
            dfs(x,i,step+1);
            if(flag)
				return;
            ans.pop_back();
			book[x][i]=0;
        }
    }
}
int main()
{
	cin>>n;
    if(n<=56)
    {
        ans.push_back(mk(1,1));
		book[1][1]=1;
        flag=0;
		dfs(1,1,0);
        for(int i=0;i<ans.size();i++)
        {
            if(i>0)
				printf(" ");
            printf("%c%d",'a'+ans[i].first-1,ans[i].second);
        }
    }
    else
    {
    	//开始打表 
        for(int i=1;i<=6;i++)
        {
            if(i%2==0)
                for(int j=8;j>=1;j--)
					printf("%c%d ",'a'+j-1,i);
            else
                for(int j=1;j<=8;j++)
					printf("%c%d ",'a'+j-1,i);
        }
        printf("a7 a8 b8 b7 c7 c8 d8 d7 ");
        if(n==57)
        	printf("h7 h8");
        if(n==58)
        	printf("e7 h7 h8");
		if(n==59)
			printf("e7 f7 h7 h8");
		if(n==60)
			printf("e7 f7 g7 h7 h8");
		if(n==61)
			printf("e7 e8 f8 f7 h7 h8");
		if(n==62)
			printf("e7 e8 f8 f7 g7 h7 h8"); 
		if(n==63)
			printf("e7 e8 f8 f7 h7 g7 g8 h8"); 
    }
    return 0;
}
```
点个小赞再走

---

## 作者：BugGod (赞：0)

注意题意：只能到一次的是单个点，不包含路径上的点。一个简单的构造思路：假设现在在 $a1$，则方案为：$h1\ g1\ f1\ \cdots\ b1\ b2$。然后 $h2\ g2\ f2\ \cdots\ c2\ a2\cdots\cdots$，奇数为方案一，偶数为方案二。如果剩余步数 $\le 7$，就去顶层，“消磨时间”。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x=1,y=1,vis[10][10];
void print(int x,int y)//打印步数
{
	cout<<(char)(x+'a'-1)<<y<<" ";
}
int main()
{
	cin>>n;
	vis[1][1]=vis[8][8]=1;
	print(1,1);
	for(int i=1;i<n;i++)
	{
		if(n-i+1<=7&&x!=8&&y!=8)y=8;//“消磨步数”
		else
		{
			int flag=0;
			for(int j=8;j>=1;j--)//按方案倒序来
			{
				if(vis[j][y]==0)
				{
					x=j;
					flag=1;
					break;
				}
			}
			if(!flag)y++;
		}
		print(x,y);
		vis[x][y]=1;
	}
	print(8,8);
	return 0;
}
```

---

## 作者：linyukun (赞：0)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
首先，这是一道思维题。  
在很难找到通用解的情况下，分类讨论显然更加简单。  
还要明确的一点是，因为步长任意，还可能是极限值，所以每次走一格更加便于考虑。
### 情况一： $2 \le n \le 50$
此时，我们的策略是这样的。
+ 首先，前七行前七列有 $49$ 个格子，可以消耗 $48$ 步。
+ 它们中任何一个都可以在两步之内到达终点。（来到第八行，走到终点）
+ 于是，前 $n-2$ 步我们选择在这个范围里蛇形往复行走，最后 $2$ 步用来到达终点。  

图解：
![](https://cdn.luogu.com.cn/upload/image_hosting/gfj2utml.png)  
### 情况二： $51 \le n \le 56$  
此时，我们的策略是与情况一一脉相承的。
+ 我们在上次的结尾，向上移动到 $g8$，使用第八行。
+ 前八行前七列有 $56$ 个格子，可以消耗 $55$ 步。
+ 它们中任何一个都只能一步到达终点。
+ 于是，前 $n-1$ 步我们选择在这个范围里蛇形往复行走，最后 $1$ 步用来到达终点。  

图解：  
![](https://cdn.luogu.com.cn/upload/image_hosting/yfqxtblm.png)
### 情况三： $57 \le n \le 63$
此时，我们需要利用所有格子，并且还要在第八行调控。
+ 蛇形遍历前七行，但是跳过 $g7$，最后遍历，然后跳到第八行去。
+ 前七行前八列有 $56$ 个格子，可以消耗 $56$ 步。
+ 第八行上消耗剩余步数，它们中任何一个都只能一步到达终点。
+ 于是，前 $n-1$ 步我们选择在这个范围里蛇形往复行走到第八行后前进，最后 $1$ 步用来到达终点。  

图解：
![](https://cdn.luogu.com.cn/upload/image_hosting/1kbip85t.png)
## 3. 提示要点：
* 注意每种情况要在消耗步数的同时**预留移动到终点所需的最后步数**。

## 4. 代码写作：
理论存在，实践开始。  

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1[60]={"鸡你太美","a1","b1","c1","d1","e1","f1","g1","g2","f2","e2","d2","c2","b2","a2","a3","b3","c3","d3","e3","f3","g3","g4","f4","e4","d4","c4","b4","a4","a5","b5","c5","d5","e5","f5","g5","g6","f6","e6","d6","c6","b6","a6","a7","b7","c7","d7","e7","f7","g7"};
int n;
int main(){
	cin>>n;
	if(n<=50){
		for(int i=1;i<=n-1;i++){
			cout<<s1[i]<<" ";
		}
		cout<<s1[n-1][0]<<"8 h8";
	}
	else if(n<=56){
		for(int i=1;i<=49;i++){
			cout<<s1[i]<<" ";
		}
		cout<<"g8 ";
		n-=50;
		for(int i=1;i<=n;i++){
			cout<<char('g'-i)<<"8 ";
		}
		cout<<"h8";
	}
	else{
		for(int i=1;i<=6;i++){
			if(i&1){
				for(int j='a';j<='h';j++){
					cout<<char(j)<<i<<" ";
				}
			}
			else{
				for(int j='h';j>='a';j--){
					cout<<char(j)<<i<<" ";
				}
			}
		}
		cout<<"a7 b7 c7 d7 e7 f7 h7 g7 g8 ";
		n-=57;
		for(int i=1;i<=n;i++){
			cout<<char('g'-i)<<"8 ";
		}
		cout<<"h8";
	}
	return 0;
}
```

## 5. 总结鸣谢：
**本题是一道考验思维的模拟，难度适中。**  
**另：还有感谢管理大大的的审核。**

---

