# [ABC383B] Humidifier 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc383/tasks/abc383_b

AtCoder社のオフィスは $ H $ 行 $ W $ 列のマス目で表されます。上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と表します。

各マスの状態は文字 $ S_{i,j} $ で表され、 $ S_{i,j} $ が `#` のときそのマスは机、`.` のときそのマスは床です。床のマスは $ 2 $ つ以上存在することが保証されます。

あなたは床のマスから異なる $ 2 $ マスを選び、加湿器を設置します。

加湿器が設置されたとき、あるマス $ (i,j) $ は加湿器があるマス $ (i',j') $ からのマンハッタン距離が $ D $ 以下であるとき、またその時に限り加湿されます。 なお、マス $ (i,j) $ からマス $ (i',j') $ までのマンハッタン距離は $ |i-i'|+|j-j'| $ で表されます。 ここで、加湿器が置かれた床のマスは必ず加湿されていることに注意してください。

加湿される **床のマス** の個数として考えられる最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 10 $
- $ 1\ \leq\ W\ \leq\ 10 $
- $ 2\ \leq\ H\ \times\ W $
- $ 0\ \leq\ D\ \leq\ H+W-2 $
- $ H,W,D $ は整数
- $ S_{i,j} $ は `#` または `.` である $ (1\ \leq\ i\ \leq\ H,\ 1\ \leq\ j\ \leq\ W) $
- 床のマスは $ 2 $ つ以上存在する
 
### Sample Explanation 1

マス $ (1,1) $ とマス $ (1,5) $ に加湿器を置いた時: - マス $ (1,1) $ の加湿器によってマス $ (1,1),(2,1) $ の $ 2 $ マスが加湿されます。 - マス $ (1,5) $ の加湿器によってマス $ (1,5) $ の $ 1 $ マスが加湿されます。 よって、合計 $ 3 $ マス加湿されています。また、$ 4 $ マス以上加湿するような加湿器の置き方は存在しないため、答えは $ 3 $ です。

### Sample Explanation 2

マス $ (2,4) $ とマス $ (5,3) $ に加湿器を置いた時、$ 15 $ 個の床のマスが加湿されます。

## 样例 #1

### 输入

```
2 5 1
.###.
.#.##```

### 输出

```
3```

## 样例 #2

### 输入

```
5 5 2
.#.#.
.....
.#.#.
#.#.#
.....```

### 输出

```
15```

## 样例 #3

### 输入

```
4 4 2
....
.##.
.##.
....```

### 输出

```
10```

# 题解

## 作者：Ray_yi (赞：1)

### 思路：

看完题目和数据范围，不会超时，直接暴力枚举。

先记录第一个加湿器的坐标，可以用两个循环来分别枚举 $i$ 和 $j$，也就是第一个加湿器的横坐标和纵坐标。接着记录第二个加湿器的坐标，再用两个循环来分别枚举 $x$ 和 $y$，为第二个加湿器的横坐标和纵坐标。

最后，枚举地板数，分别判断以 $i$ 和 $j$ 为第一个加湿器坐标和以 $x$ 和 $y$ 为第二个加湿器坐标时，可以加湿的空地数，结果取最大值输出。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,d,ans=-1;
char a[100][100];
int f(int x,int y,int lr){
	int l=0,t[100][100];
	if(lr){
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
				t[i][j]=0;//清0 
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if((abs(i-x)+abs(j-y))<=d&&a[i][j]!='#'&&t[i][j]==0) l++,t[i][j]=1;
			//加湿器可以加湿当前位置 
		}
	}
	return l;//返回答案 
}
int main(){
	cin>>h>>w>>d;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>a[i][j];
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(a[i][j]=='#') continue;//如果这一格是桌子 
			for(int x=1;x<=h;x++){
				for(int y=1;y<=w;y++){
					if(a[x][y]=='#'||i==x&&j==y) continue;//不合格的情况 
					ans=max(ans,f(i,j,1)+f(x,y,0));//记录答案 
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：JCT_addyi (赞：0)

### 题意：
有 $H$ 行 $W$ 列的网格，有桌子和空地，只有桌子上能放加湿器，只能放两个加湿器，每个加湿器可以将与它的曼哈顿距离小于等于 $d$ 的空地加湿包括加湿器放置的空地，公式题目有提，问最多可以加湿多少空地。

### 思路：

看完题目和范围发现可以暴力，我们可以先给桌子做个标记，再两个桌子之间暴力求距离，再标记一下每次可以被加湿的空地，每次枚举之后清空，最终取最大值。

### 代码：

详细看代码，还是很好理解的。


```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,d,sum=0;
bool a[20][20],b[20][20];//a是标记桌子，b是标记合法的空地 
char q;
void z(int i,int j,int i1,int j1){//暴力求距离 
	for(int ii=1;ii<=h;ii++)
		for(int jj=1;jj<=w;jj++)
			if(abs(ii-i)+abs(jj-j)<=d||abs(ii-i1)+abs(jj-j1)<=d) //套公式，曼哈顿距离定义
				if(a[ii][jj]==0) b[ii][jj]=1;//距离小于d且不是桌子的标记
}
int s(){
	int ans=0;
	for(int ii=1;ii<=h;ii++)
		for(int jj=1;jj<=w;jj++)
			if(b[ii][jj]==1) ans++;//暴力求被标记的数量 
	return ans;
}
int main(){
	cin>>h>>w>>d;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){
			cin>>q;
			if(q=='#') a[i][j]=1;//标记桌子 
		}
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			for(int i1=1;i1<=h;i1++)
				for(int j1=1;j1<=w;j1++)//四层循环暴力 
					if((j1!=j||i!=i1)&&(a[i][j]==0&&a[i1][j1]==0)){//不是桌子 
						z(i,j,i1,j1);//求距离 
						sum=max(sum,s());//求最大值 
						for(int ii=1;ii<=h;ii++)
		                    for(int jj=1;jj<=w;jj++)
		 	                        b[ii][jj]=0;//每次清空 
					}	
	cout<<sum;	
    return 0;
}

```

谢谢大家！

---

## 作者：Jayfeather2012 (赞：0)

## 思路
暴力出奇迹~~  
暴力枚举万岁~~  
观察到 $1\leq H \leq10$ 且 $1\leq W \leq10$ ，$O(n^8)$ 都不会炸，于是考虑暴力枚举。  
先枚举第一个加湿器的位置 $(i,j)$，再枚举第二个加湿器的位置 $(k,l)$，接着遍历地板，找出当第一个加湿器的位置为 $(i,j)$，第二个加湿器的位置为 $(k,l)$ 时加湿的空地数，所有情况取最大值后输出。  
时间复杂度 $O(n^6)$。  
具体细节看代码吧！
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pp pair<int,int>
using namespace std;
int n,m,d,ans;
char a[15][15];
int sum(int xa,int ya,int xb,int yb){
	return abs(xa-xb)+abs(ya-yb);
}
//计算曼哈顿距离 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>d;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)cin>>a[i][j];
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			//枚举第一个加湿器位置 
			if(a[i][j]=='#')continue;
			//不是地板，不继续 
			for(int k=1;k<=n;++k){
				for(int l=1;l<=m;++l){
					//枚举第二个加湿器位置 
					if(a[k][l]=='#'||k==i&&l==j)continue;
					//不是地板，不继续 
					//两个加湿器位置相等，不继续 
					int s=0;
					for(int x=1;x<=n;++x){
						for(int y=1;y<=m;++y){
							//遍历地板 
							if(a[x][y]=='#')continue;
							//不是地板，不继续 
							if(sum(i,j,x,y)<=d||sum(k,l,x,y)<=d)++s;
							//若曼哈顿距离小于d，增加加湿的空地数 
						}
					}
					ans=max(ans,s);//取最大值 
				}
			}
		}
	}
	cout<<ans<<"\n"; 
	return 0;
}

```

---

