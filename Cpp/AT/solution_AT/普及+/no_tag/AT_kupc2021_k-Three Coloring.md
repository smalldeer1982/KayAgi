# Three Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2021/tasks/kupc2021_k

$ N $ 個の壁があります。各壁を赤、緑、青のいずれか $ 1 $ 色で塗ることを考えます。

$ M $ 個の条件が与えられます。$ i $ 番目の条件は、整数 $ a_i,b_i $ と文字 $ x_i,y_i $ が与えられ、

- 壁 $ a_i $ を 色 $ x_i $ で塗ったとき、壁 $ b_i $ を 色 $ y_i $ で塗ってはならない

ことを表しています。ただし、 $ x_i,y_i $ はそれぞれ文字 `R` , `G` , `B` のいずれかであり、 `R` のとき赤を、`G` のとき緑を、 `B` のとき青を表しています。

$ M $ 個全ての条件を満たす色の塗り方が何通りあるかを答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 22 $
- $ 0\ \leq\ M\ \leq\ 9\ \times\ \frac{N(N-1)}{2} $
- $ 1\ \leq\ a_i\ <\ b_i\ \leq\ N $
- $ x_i,y_i $ はそれぞれ文字 `R` , `G` , `B` のいずれかである。
- $ i\ \neq\ j $ のとき、$ (a_i,x_i,b_i,y_i)\ \neq\ (a_j,x_j,b_j,y_j) $
- $ N,M,a_i,b_i $ はいずれも整数

### Sample Explanation 1

壁 $ 1 $ を赤色で塗る場合、壁 $ 2 $ は緑色または青色で塗ることができます。 壁 $ 1 $ を緑色で塗る場合、壁 $ 2 $ は緑色または青色で塗ることができます。 壁 $ 1 $ を青色で塗る場合、壁 $ 2 $ は赤色または青色で塗ることができます。 よって、合計で $ 6 $ 通りの塗り方があります。

### Sample Explanation 2

壁 $ 1 $ をどの色で塗っても条件を満たします。

### Sample Explanation 3

オーバーフローに注意してください。

## 样例 #1

### 输入

```
2 3
1 R 2 R
1 G 2 R
1 B 2 G```

### 输出

```
6```

## 样例 #2

### 输入

```
1 0```

### 输出

```
3```

## 样例 #3

### 输入

```
22 0```

### 输出

```
31381059609```

## 样例 #4

### 输入

```
4 12
2 R 3 R
1 B 2 B
2 R 3 B
3 R 4 R
1 B 4 G
1 R 3 B
3 G 4 B
2 G 3 G
1 B 2 R
1 G 2 R
1 R 3 G
1 G 3 B```

### 输出

```
13```

# 题解

## 作者：happy_dengziyue (赞：0)

### 1 题意

你要给 $N$ 个格子涂上红、绿、蓝之一，有 $M$ 条限制，第 $i$ 条形如：第 $a_i$ 个格子不能为颜色 $x_i$ **或** 第 $b_i$ 个格子不能为颜色 $y_i$。求有多少种合法的涂色方式。

$1\le N\le22$

$0\le M\le\dfrac{9N(N-1)}{2}$

$1\le a_i<b_i\le N$

### 2 思路

这个题可以用 meet-in-middle 或者各种高妙算法做掉。这里写一个**暴搜剪枝**的做法。

首先考虑最朴素的方法：枚举每个格子的颜色，最后统一 check。时间复杂度 $\Theta(3^N M)$ 显然是不能通过的。

但是我们注意到，如果我们枚举到格子 $u$ 的颜色为 $col_u$，准备进行下一步的枚举，这个颜色不与前面格子冲突，又不存在任何一个操作使得 $a_i=u$ 且 $x_i=col_u$，那么当前 $col_u$ 一定不会与后面格子冲突。

我们还发现：如果一个格子存在 $2$ 或 $3$ 个颜色满足上述条件，那么具体选哪个是无所谓的；那么 dfs 到最后就把答案加上形如 $2^i3^j$ 即可。

### 3 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
long long pw2[32];
long long pw3[32];
int n;
int m;
struct P{int x,a,y,b;}p[3002];
int id[32];
vector<pair<int,int>>g[32][4];
vector<pair<int,int>>gxy[32][32];
int gc[32];
int col[32];
long long ans=0;
inline void dfs(int x,int now3,int now2){
	if(x>n){ans+=pw3[now3]*pw2[now2]; return;}
	bool have[4]={0,0,0};
	bool can[4]={1,1,1};
	for(int w=0;w<=2;++w){
		if(!((gc[x]>>w)&1)){can[w]=false; continue;}
		for(auto u:g[x][w]){
			if(x<u.first)have[w]=true;
			else if(col[u.first]==u.second)can[w]=false;
		}
	}
	if(!have[0]&&!have[1]&&!have[2]&&can[0]&&can[1]&&can[2]){
		dfs(x+1,now3+1,now2); return;
	}
	for(int i=0;i<=2;++i){
		for(int j=i+1;j<=2;++j){	
			if(!have[i]&&!have[j]&&can[i]&&can[j]){
				dfs(x+1,now3,now2+1); can[i]=can[j]=false;
			}
		}
	}
	for(col[x]=0;col[x]<=2;++col[x]){
		if(can[col[x]])dfs(x+1,now3,now2);
	}
	col[x]=-1;
}
int main(){
	srand(time(0)); pw2[0]=pw3[0]=1;
	for(int i=1;i<=30;++i){pw2[i]=pw2[i-1]*2; pw3[i]=pw3[i-1]*3;}
	scanf("%d%d",&n,&m);
	int opw[500]; opw['R']=0; opw['G']=1; opw['B']=2;
	for(int i=1;i<=m;++i){
	    char opx[6],opy[6];
		scanf("%d%s%d%s",&p[i].x,opx,&p[i].y,opy);
		p[i].a=opw[opx[0]]; p[i].b=opw[opy[0]];
	}
	for(int i=1;i<=n;++i)id[i]=i;
	random_shuffle(id+1,id+n+1);
	for(int i=1;i<=m;++i){p[i].x=id[p[i].x]; p[i].y=id[p[i].y];}
	for(int i=1;i<=m;++i){
		g[p[i].x][p[i].a].push_back({p[i].y,p[i].b});
		g[p[i].y][p[i].b].push_back({p[i].x,p[i].a});
		gxy[p[i].x][p[i].y].push_back({p[i].a,p[i].b});
	}
	for(int i=1;i<=n;++i)gc[i]=7;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			int resl=0,resr=0;
			for(int a=0;a<3;++a){
				for(int b=0;b<3;++b){
					bool fl=true;
					for(auto p:gxy[i][j]){
						if(a==p.first&&b==p.second){fl=false; break;}
					}
					if(fl){resl|=1<<a; resr|=1<<b;}
				}
			}
			gc[i]&=resl; gc[j]&=resr;
		}
	}
	memset(col,-1,sizeof(col));
	dfs(1,0,0);
	printf("%lld\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/187057153)

---

