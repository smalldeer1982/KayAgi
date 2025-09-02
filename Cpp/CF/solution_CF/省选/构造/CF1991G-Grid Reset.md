# Grid Reset

## 题目描述

给定一个 $n$ 行 $m$ 列的格子矩阵，初始所有格子都是白色。另外给定一个整数 $k$。

你将执行如下两类操作共 $q$ 次：

- $\texttt H$（水平操作）：在格子矩阵中选择一个 $1$ 行 $k$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。
- $\texttt V$（纵向操作）：在格子矩阵中选择一个 $k$ 行 $1$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。

每次操作之后，如果任意一行或一列所有格子都被涂成了黑色，则这一行或一列的所有格子自动被重置成白色。特别的，如果某一个格子所在的行和列都被涂成了黑色，则该格子所处的行和列的所有格子也将自动被重置成白色。

现在，对于 $q$ 次操作中的每次操作，请指定一个矩阵，使得所有 $q$ 次操作都能够进行，或者报告无论如何指定矩阵都不能使得所有 $q$ 次操作都能够进行。

## 说明/提示

对于所有数据：

- $1\leqslant t\leqslant 1000$。
- $1\leqslant n,m\leqslant 100,\color{Red}1\leqslant k\leqslant \min\{n,m\}$。
- $1\leqslant q\leqslant 1000,\sum q\leqslant 1000$。

输入输出样例参见下文。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
1
4 5 3 6
HVVHHV```

### 输出

```
1 1
2 1
1 1
2 3
3 3
2 2```

# 题解

## 作者：zyh_helen (赞：11)

赛时 F 调了两小时没看，赛后一眼秒，心疼死了。

---
---
考虑横的和竖的分开用，最后再消，我们发现这样的构造策略。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ig1qylj.png)

即中间一个 $k\times k$ 的正方形，横的优先往正方形下面填，填满了之后再从正方形顶部到底部寻找第一个可以消掉右边的若干列的地方消掉，如果没有就放在顶部。列同理。

容易证明一定不会重合，因为正方形内放横的的时候一定是右边没有填满的时候，右边填满之后就会把横的消掉。

---
发现右边可以消掉的若干行一定是连续的，所以写的时候只需要记一个指针代表从该位置开始到底部我都没有消掉。列同理。

总时间复杂度 $O(\sum q)$。

---
---
个人认为代码实现非常困难。

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define ll long long
//#define double long double
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e5 + 20, inf = 2e9, M = 4e3 + 5;
//const double eps = 1e-14, pi = 3.1415926, kou = 0.577215669902;
const int mod = 1e9 + 7;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot = 1;
//	struct edge{
//		int t, f;
//		int d, fl;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, m, k, q;
bool mp[50][50], a[50], b[50];
char s[N];
void print(){
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	for(int i = 1;i <= n;i++){
		int f = 1;
		for(int j = 1;j <= m;j++){
			f &= mp[i][j];
		}
		if(f)a[i] = 1;
	}
	for(int i = 1;i <= m;i++){
		int f = 1;
		for(int j = 1;j <= n;j++){
			f &= mp[j][i];
		}
		if(f)b[i] = 1;
	}
	for(int i = 1;i <= n;i++){
		if(a[i])for(int j = 1;j <= m;j++)mp[i][j] = 0;
	}
	for(int i = 1;i <= m;i++){
		if(b[i])for(int j = 1;j <= n;j++)mp[j][i] = 0;
	}
	for(int i = 1;i <= n;i++, putchar('\n'))for(int j = 1;j <= m;j++)cout << mp[i][j];
}
signed main(){
//	freopen("1.out", "w", stdout);
	int T;
	cin >> T;
	while(T--){
		cin >> n >> m >> k >> q;
		int s1 = n - k, s2 = m - k, nw1 = 1, nw2 = 1, nw = 1, f = 0, f1 = 0, f2 = 0, nnw1 = 1, nnw2 = 1;
//		scanf("%s", s + 1);
		for(int i = 1;i <= q;i++){
			char c;
			cin >>c;
			if(c == 'H'){
				if(m == k){
					printf("%lld 1\n", n);
					continue;
				}
				if(nw1 < s1){
					printf("%lld 1\n", k + nw1++);
//		for(int j = 1;j <= k;j++)mp[k + nw1 - 1][j] = 1;
				}
				else if(nw1 == s1){
					printf("%lld 1\n", k + nw1++);
//		for(int j = 1;j <= k;j++)mp[k + nw1 - 1][j] = 1;
					f1 = 1;
					nnw1 = 1;
					if(f == 2){
						f = 0;
						nnw1 = nw;
						nw = 1;
					}
				}
				else {
					if(f2){
						printf("%lld 1\n", nnw2++);
//		for(int j = 1;j <= k;j++)mp[nnw2 - 1][j] = 1;
						if(nnw2 > k)nnw2 = 1, f2 = 0, nw = 1, nw2 = 1;
					}
					else {
						f = 1;
						printf("%lld 1\n", nw++);
//		for(int j = 1;j <= k;j++)mp[nw - 1][j] = 1;
						if(nw > k){
							nw = nnw1;
							f = 0;
							if(nw > 1)f = 2;
							nw1 = 1;
							f1 = 0;
						}
					}
				}
			}
			else {
				if(n == k){
					printf("1 %lld\n", m);
					continue;
				}
				if(nw2 < s2){
					printf("1 %lld\n", k + nw2++);
//		for(int j = 1;j <= k;j++)mp[j][k + nw2 - 1] = 1;
				}
				else if(nw2 == s2){
					printf("1 %lld\n", k + nw2++);
//		for(int j = 1;j <= k;j++)mp[j][k + nw2 - 1] = 1;
					f2 = 1;
					nnw2 = 1;
					if(f == 1){
						f = 0;
						nnw2 = nw;
						nw = 1;
					}
				}
				else {
					if(f1){
						printf("1 %lld\n", nnw1++);
//		for(int j = 1;j <= k;j++)mp[j][nnw1 - 1] = 1;
						if(nnw1 > k)nnw1 = 1, f1 = 0, nw = 1, nw1 = 1;
					}
					else {
						f = 2;
						printf("1 %lld\n", nw++);
//		for(int j = 1;j <= k;j++)mp[j][nw - 1] = 1;
						if(nw > k){
							nw = nnw2;
							f = 0;
							if(nw > 1)f = 1;
							nw2 = 1;
							f2 = 0;
						}
					}
				}
			}
//			cout << nnw1 << " " << f << " " << nw << endl;
//			print();
		}
	}
	return 0;
}

---

## 作者：山田リョウ (赞：9)

通过思考 $k|n$ 的情况发现，我们需要单独留出一个空间用于消方块。

于是考虑将矩阵划分为四个部分，分别是左上角的 $k\times k$ 的消消区和左下 $(n-k)\times k$、右上 $k\times(m-k)$ 的行/列正常摆放区域与右下 $(n-k)\times(m-k)$ 的废弃区。

不难发现如果我们在能在对应正常摆放区摆放的前提下往里填，否则填到消消区尽可能去消另一种摆放，则一定合法。

于是我们就有了一个构造方式，而大部分人似乎都是写的朴素枚举可选位置的做法，但是其实更优。

考虑对行和列各记一个下一次填的位置的指针，与一个记录在消消区的残留的指针，你可以每次 $O(1)$ 跳指针并进行判断更新了！具体细节见代码。

**注意特判 $n=k$ 或 $m=k$。**

```cpp
#include<stdio.h>
char s[1001];
int main(){
	int T,N,M,K,Q;
	for(scanf("%d",&T);T--;){
		scanf("%d%d%d%d %s",&N,&M,&K,&Q,s);
		if(N==K&&M==K){
			for(int i=0;i<Q;++i)puts("1 1");
		}else if(N==K){
			for(int i=0,p=0;i<Q;++i)
				if(s[i]=='H'){
					printf("%d 1\n",++p);
					if(p==N)p=0;
				}else printf("1 %d\n",M);
		}else if(M==K){
			for(int i=0,p=0;i<Q;++i)
				if(s[i]=='V'){
					printf("1 %d\n",++p);
					if(p==M)p=0;
				}else printf("%d 1\n",N);
		}else{
			int x=N,y=M,p=K,q=K;
			for(int i=0;i<Q;++i)
				if(s[i]=='H'){
					printf("%d 1\n",x--);
					if(!x){
						if(y<=K)q=y,y=M,x=K;
						else x=N;
					}else if(x==K)x=p,p=K;
				}else{
					printf("1 %d\n",y--);
					if(!y){
						if(x<=K)p=x,x=N,y=K;
						else y=M;
					}else if(y==K)y=q,q=K;
				}
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1991G)

**题目大意**

> 给定 $n\times m$ 矩阵，$q$ 次操作要求填入 $1\times k/k\times 1$，不能重叠，如果某行或某列被填满，则该行或该列会被清空，构造方案。
>
> 数据范围：$n,m\le 100,q\le 1000$。

**思路分析**

考虑贪心，竖块只填第一行，横块只填第一列，如果能产生消行就选择该位置，否则任选一个位置。

把棋盘分成左上角的 $k\times k$，右上角的 $k\times (m-k)$，左下角的 $(n-k)\times k$。

很显然任何时候每个子区域都是完整的若干行或若干列。

满足该条件时一定有解：假设一个横块填不了，那么左上角和左下角都必须是若干列，但在右下角是若干列的时候，一定是在左上角放了竖块引发的消行，从而左上区域不存在竖块，可以放横块。

时间复杂度 $\mathcal O(nmq)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int n,m,k,q;
string str;
bool a[MAXN][MAXN],ti[MAXN],tj[MAXN];
void fls() {
	fill(ti+1,ti+n+1,1),fill(tj+1,tj+m+1,1);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(!a[i][j]) ti[i]=tj[j]=0;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(ti[i]||tj[j]) a[i][j]=0;
}
void solve() {
	cin>>n>>m>>k>>q>>str;
	memset(a,0,sizeof(a));
	for(char op:str) {
		if(op=='H') {
			int x=0;
			for(int i=1;i<=n;++i) {
				bool ok=1;
				for(int j=1;j<=k;++j) ok&=!a[i][j];
				if(ok) x=i;
				for(int j=k+1;j<=m;++j) ok&=a[i][j];
				if(ok) break;
			}
			cout<<x<<" "<<1<<"\n";
			for(int j=1;j<=k;++j) a[x][j]=1;
		} else {
			int y=0;
			for(int j=1;j<=m;++j) {
				bool ok=1;
				for(int i=1;i<=k;++i) ok&=!a[i][j];
				if(ok) y=j;
				for(int i=k+1;i<=n;++i) ok&=a[i][j];
				if(ok) break;
			}
			cout<<1<<" "<<y<<"\n";
			for(int i=1;i<=k;++i) a[i][y]=1;
		}
		fls();
	}
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：wxzzzz (赞：0)

### 思路

将 $\tt H$ 全部放在左上角，$\tt V$ 全部放在右下角。

$$\begin{aligned}
11110000\\
11110000\\
00000111\\
00000111\\
00000111\\
00000111
\end{aligned}$$

横着和竖着的矩阵只要接触就必然使接触的行或列消失，看起来十分正确。

但这是错的。

考虑这样一种情况：

```
4 5 3 6
VVHHHV
```

上述方法会产生如下矩阵：

$\begin{aligned}
00000\\
00000\\
00000\\
00000\\
\end{aligned}\to\begin{aligned}
00000\\
00001\\
00001\\
00001\\
\end{aligned}\to\begin{aligned}
00000\\
00011\\
00011\\
00011\\
\end{aligned}\to\begin{aligned}
11100\\
00011\\
00011\\
00011\\
\end{aligned}\to\begin{aligned}
11100\\
11111\\
00011\\
00011\\
\end{aligned}\ \begin{aligned}
11100\\
00000\\
00011\\
00011\\
\end{aligned}\to\begin{aligned}
11100\\
11100\\
00011\\
00011\\
\end{aligned}\to\begin{aligned}
11100\\
11100\\
00011\\
00011\\
\end{aligned}$

最后一个 $\tt V$ 放不下了。

优化构造方案：每放置一个 $\tt H$，保证放入矩阵紧贴左边缘的前提下，优先取能消除一个 $\tt V$ 的位置，如有多个，取最靠上的位置，若没有，则取最靠上的能放的位置；每放置一个 $\tt V$，保证放入矩阵紧贴右边缘的前提下，优先取能消除一个 $\tt H$ 的位置，如有多个，取最靠下的位置，若没有，则取最靠右的能放的位置。

现在证明这样一定有解。

仅需证明每个 $\tt V$ 都能放下，$\tt H$ 同理。

1. 当前存在 $\tt V$ 最靠左的位置 $<m-k$。

   因为 $\tt H$ 都放在左上角，且它们的长度最多为 $k$，否则就消掉了。因此一定存在一个空列，直接放在最右的位置即可。

1. 当前存在 $\tt V$ 最靠左的位置 $>m-k$
  
    1. $\tt H$ 最靠下的位置 $\le n-k$

       此时仍有空位放。
           
    1. $\tt H$ 最靠下的位置 $>n-k$

       该情况不存在，否则 $\tt H,V$ 将重合。

1. 当前存在 $\tt V$ 最靠左的位置 $=m-k$

    因为此时存在 $\tt V$ 可被一个 $\tt H$ 消除一格，在该 $\tt V$ 产生之后的所有 $\tt H$ 必然都用来消除该 $\tt V$ 的一格，因此该 $\tt V$ 左边至少存在 $n-k+1\sim n$ 这些空格子，可用来放置一个新 $\tt V$，而该放置操作也符合上述构造方法。所有 $\tt H,V$ 分别都是连在一起的，若不连在一起一定是用来消除其他 $\tt H,V$ 了，自然不存在。因此该放置操作至少满足“若没有，则取最靠右的能放的位置”，而如果能消除行那自然是合法放置。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, k, q, px, py;
char op[1005];
bool cx[105], cy[105], a[105][105];
int main() {
    cin >> T;

    while (T--) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                a[i][j] = 0;

        cin >> n >> m >> k >> q >> op + 1;
        px = 1, py = m;

        for (int id = 1, t; id <= q; id++) {
            if (op[id] == 'H') {
                t = px;

                for (int i = px; i <= n; i++) {
                    bool ck = 1;

                    for (int j = 1; j <= k; j++)
                        ck &= !a[i][j];

                    for (int j = k + 1; j <= m; j++)
                        ck &= a[i][j];

                    if (ck) {
                        t = i;
                        break;
                    }
                }

                if (!t)
                    t = px;

                cout << t << " 1\n";

                for (int i = 1; i <= k; i++)
                    a[t][i] = 1;
            } else {
                t = py;

                for (int i = py; i >= 1; i--) {
                    bool ck = 1;

                    for (int j = n - k + 1; j <= n; j++)
                        ck &= !a[j][i];

                    for (int j = 1; j <= n - k; j++)
                        ck &= a[j][i];

                    if (ck) {
                        t = i;
                        break;
                    }
                }

                if (!t)
                    t = py;

                cout << n - k + 1 << ' ' << t << '\n';

                for (int i = n - k + 1; i <= n; i++)
                    a[i][t] = 1;
            }

            for (int i = 1; i <= n; i++)
                cx[i] = 1;

            for (int i = 1; i <= m; i++)
                cy[i] = 1;

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    cx[i] &= a[i][j];
                    cy[j] &= a[i][j];
                }
            }

            for (int i = 1; i <= n; i++) {
                if (!cx[i])
                    continue;

                for (int j = 1; j <= m; j++)
                    a[i][j] = 0;
            }

            for (int i = 1; i <= m; i++) {
                if (!cy[i])
                    continue;

                for (int j = 1; j <= n; j++)
                    a[j][i] = 0;
            }

            px = 1;

            while (1) {
                bool ck = 1;

                for (int i = 1; i <= k; i++)
                    ck &= !a[px][i];

                if (!ck)
                    px++;
                else
                    break;
            }

            py = m;

            while (1) {
                bool ck = 1;

                for (int i = n - k + 1; i <= n; i++)
                    ck &= !a[i][py];

                if (!ck)
                    py--;
                else
                    break;
            }
        }
    }

    return 0;
}
```

---

