# [ABC358F] Easiest Maze

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc358/tasks/abc358_f

すぬけくんは、AtCoder Land の新たな目玉アトラクションとして迷路を建設しようと考えています。 迷路は縦 $ N $ 行・横 $ M $ 列のグリッドとして表され、右上のマスの上端が入口、右下のマスの下端が出口です。 すぬけくんは、隣接するマスの間に適切に壁を配置することで迷路を作ります。

すぬけくんは簡単な迷路が大好きなので、入口から出口までの道順は枝分かれを一切持たずにちょうど $ K $ マスを通るようなものにしたいです。 そのような迷路を作ることが可能か判定し、可能ならば $ 1 $ つ構築してください。

例えば以下の図では、$ N=3,M=3 $ であり、実線で書かれているところに壁が配置されています（入口と出口を除く外周部には必ず壁が配置されるものとします）。 このとき、入口から出口までの道順は枝分かれを一切持たずにちょうど $ 7 $ マスを通っています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc358_f/d85661fe106644e674beb089fb17a5f2eabae979.png)

厳密には以下の通りです。

縦 $ N $ 行・横 $ M $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と表記します。 あなたは、辺で隣接する任意の $ 2 $ マスの間それぞれについて壁を置くか置かないか決めることができます。 壁を置く場所をうまく定めることで以下の条件を満たすことができるか判定し、できるならば実際に $ 1 $ つ構築してください。

> $ NM $ 頂点からなる無向グラフ $ G $ を考える。$ G $ の各頂点は $ 2 $ つの整数の組 $ (i,j)\ (1\leq\ i\leq\ N,\ 1\leq\ j\leq\ M) $ によって互いに相異なるラベルが付けられている。 相異なる $ 2 $ 頂点 $ (i_1,j_1),(i_2,j_2) $ は、$ |i_1-i_2|+|j_1-j_2|=1 $ かつグリッド上の $ 2 $ マス $ (i_1,j_1),(i_2,j_2) $ の間に壁が置かれていない場合、またその場合に限り辺で結ばれている。
> 
> 条件：$ K $ 頂点からなり $ 2 $ 頂点 $ (1,M),(N,M) $ を結ぶような単純パスが存在し、また $ 2 $ 頂点 $ (1,M),(N,M) $ を含む連結成分はこのパスのみからなる。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 100 $
- $ 1\leq\ M\ \leq\ 100 $
- $ 1\leq\ K\leq\ NM $
- 入力は全て整数

### Sample Explanation 1

問題文中の図と同じ壁の配置です。

## 样例 #1

### 输入

```
3 3 7```

### 输出

```
Yes
+++++S+
+o.o.o+
+.+-+-+
+o.o.o+
+-+-+.+
+o.o|o+
+++++G+```

## 样例 #2

### 输入

```
3 3 2```

### 输出

```
No```

## 样例 #3

### 输入

```
4 1 4```

### 输出

```
Yes
+S+
+o+
+.+
+o+
+.+
+o+
+.+
+o+
+G+```

# 题解

## 作者：xxgirlxx (赞：13)

### 更新日志

2023 年 9 月 16 日：使用了更加精细的图片，修改了部分描述。

2023 年 9 月 20 日：添加了能走过的总格子数的证明。

2023 年 10 月 9 日：再次更改部分描述。

2024 年 1 月 13 日：修订了一些细节，加了点~~废话~~题外话。

## 题外话

本人赛时一直认为本题的无解是输出 `-1`。结果虚空调试一小时，成功成为小丑，后来看 kenkoooo 的评分有黄（$\color{C0C000}{2098}$），痛失黄 perf。

后来看 [AT_abc387_e](https://www.luogu.com.cn/problem/AT_abc387_e) 的时候发现有人认为这题更简单，但我其实认为这两题差不多（~~反正都是一眼秒了然后因奇葩原因没场切~~），kenkoooo 上的评分其实也几乎一样（本题是 $\color{C0C000}{2098}$，[AT_abc387_e](https://www.luogu.com.cn/problem/AT_abc387_e) 是 $\color{C0C000}{2097}$）。

## 题目大意

给你一个长为 $n$，宽为 $m$ 的格子图，要求你给出一个路径，经过的格子数正好为 $k$ 个。

## 题目思路

首先，注意到最短路径是一条直线，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y72x62ds.png)

然后尝试将路径的长度加大，然后注意到路径扩出去了是需要回来的，所以所加大的部分的格子数量一定是偶数，所以整个路径的奇偶性是不会变的。如图：红色是出去的路，绿色是回来的路，蓝色是原来的路。

![](https://cdn.luogu.com.cn/upload/image_hosting/o12131fn.png)

所以说，无解有三种情况：

一：要求格子数大于能走过的总格子数。

二：要求格子数小于最短路径格子数。

三：要求格子数的奇偶性与**能走过的总格子数**的奇偶性不同。

然后我们还要判断是否能走遍全部格子。

经过一系列的手模样例，成功发现一条规律：若 $n$ 为奇数，$m$ 为偶数，会出现有一个格子无法到达的情况，为什么呢？

这就需要请出染色大法了。

观察 $n$ 为奇数，$m$ 为偶数情况下染色（固定左上角为绿色）后的棋盘：

![](https://cdn.luogu.com.cn/upload/image_hosting/bpw5x7ud.png)

可以观察到红格子一定会踏入绿格子，绿格子一定会踏入红格子，所以路径一定是红绿交错的，但是会发现：开头和结尾已经被固定为红色了，所以绿色的数量必定会比红色少一个，但是绿色在图中又是跟红色有一样数量的格子。所以不管怎么走，在 $n$ 为奇数，$m$ 为偶数的情况下肯定是会有一个格子走不到的。

所以具体的最多格子走法为：

![](https://cdn.luogu.com.cn/upload/image_hosting/o039fhy7.png)

其他情况同理：

$n$ 为奇数，$m$ 为奇数的情况：

开头为绿，结束为绿，但是绿色格子比红色格子多一个，所以可以走遍所有格子。具体走法为：

![](https://cdn.luogu.com.cn/upload/image_hosting/vz68inx6.png)

$n$ 为偶数，$m$ 为奇数的情况：

开头为绿，结束为红，绿色格子跟红色格子一样多，所以可以走遍所有格子。具体走法为：

![](https://cdn.luogu.com.cn/upload/image_hosting/wa15y29u.png)

$n$ 为偶数，$m$ 为偶数的情况：

开头为红，结束为绿，绿色格子跟红色格子一样多，所以可以走遍所有格子。具体走法为：

![](https://cdn.luogu.com.cn/upload/image_hosting/wbz8uuwx.png)

无解的情况判完了，我们就可以放心的延长路径了。

先计算出路径需要延张几次：即要求格子数减去最短路径格子数的差除以二。

接下来我们就可以扩张了，先横着扩张，一边扩张还要一边判断需要的扩张次数到了没有。

横着扩充完了，再竖着扩张，虽然竖着扩张是 $n$ 为奇数独有的，但是因为无解的已经排除完了，剩下的都是有解的，所以 $n$ 为偶数的情况需要的扩张次数应该在横着扩张那里就到了。

这边建议先将整个路径用方向在数组中记录下来，然后再在迷宫地图上开路，最后输出迷宫数组即可。

最后我们将路径转化为迷宫输出即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[101][101],num,dx[10]={0,-1,0,1,0},dy[10]={0,0,1,0,-1};
char ans[202][202];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k,num=(k-n)/2;//计算需要扩张的次数 
	if(k<n||k>n*m||k%2!=n%2||k>n*m-n%2+m%2){cout<<"No\n";return 0;}//特判无解的情况 
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)a[i][m]=3;//先把最短路径填入 
	for(int i=1;i<n&&num>0;i+=2)for(int j=m-1;j>=1&&num>0;j--,num--)a[i+1][j]=2,a[i][j]=3,a[i][j+1]=4;//横着扩张 
	if(m%2==0)for(int i=1;i<m-1&&num>0;i+=2,num--)a[n-1][i]=3,a[n][i]=2,a[n][i+1]=1;//竖着扩张 
	else for(int i=1;i<m&&num>0;i+=2,num--)a[n-1][i]=3,a[n][i]=2,a[n][i+1]=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans[i*2+dx[a[i][j]]][j*2+dy[a[i][j]]]='.';//将通路在迷宫上标记出来，1表示上，2表示右，3表示下，4表示左
	for(int i=1;i<=n*2;i+=2){
		for(int j=1;j<=m*2;j+=2){
			ans[i][j]='+',ans[i+1][j+1]='o';//标记点以及给不相通的点之间加墙 
			if(ans[i+1][j]!='.')ans[i+1][j]='|';
			if(ans[i][j+1]!='.')ans[i][j+1]='-';
		}
	}
	for(int i=1;i<=n*2+1;i++)ans[i][m*2+1]='+',ans[i][1]='+';//围最外圈的墙 
	for(int i=1;i<=m*2+1;i++)ans[n*2+1][i]='+',ans[1][i]='+';
	ans[1][m*2]='S',ans[n*2+1][m*2]='G';//标记起点和终点 
	for(int i=1;i<=n*2+1;i++){
		for(int j=1;j<=m*2+1;j++)cout<<ans[i][j];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Register_int (赞：10)

最简单的情况就是直着一条走下来，此时的步数是 $n$。容易发现你能构造出的步数在 $n$ 到 $nm$ 之间，且奇偶性与 $n$ 相同。这是因为你多走一步还得把多走的还回来，所以多走的步数必定为偶数步。

考虑增量构造，从直线开始，我们有一种每次让长度 $+2$ 的方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/11aaev6j.png)

容易发现这样要用到两行。那只剩一行了怎么办呢？我们可以：

![](https://cdn.luogu.com.cn/upload/image_hosting/s1f97bzf.png)

那么就做完了，时间复杂度 $O(nm)$。

# AC 代码 

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;
const int mod = 998244353;

int n, m, x, r[MAXN][MAXN], c[MAXN][MAXN];

int main() {
	scanf("%d%d%d", &n, &m, &x);
	if (x < n || x > n * m) return puts("No"), 0;
	if ((x & 1) != (n & 1)) return puts("No"), 0; puts("Yes");
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) r[i][j] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) c[i][j] = 1;
	}
	x -= n;
	for (int i = 1; i < n; i += 2) {
		int w = min(x / 2, m - 1); x -= w * 2;
		for (int j = m - 1; j >= m - w; j--) c[i][j] = c[i + 1][j] = 0;
		r[i][m - w] = r[i + 1][m] = 0;
	}
	if (x) {
		for (int i = 1; i <= x; i += 2) {
			r[n - 1][i] = r[n - 1][i + 1] = 0;
			c[n - 1][i] = 1, c[n][i] = 0;
		}
	}
	for (int i = 1; i <= 2 * m - 1; i++) putchar('+'); puts("S+");
	for (int i = 1; i < n; i++) {
		printf("+o"); for (int j = 1; j < m; j++) printf("%co", c[i][j] ? '|' : '.'); puts("+");
		printf("+"); for (int j = 1; j <= m; j++) printf("%c+", r[i][j] ? '-' : '.'); puts("");
	}
	printf("+o"); for (int j = 1; j < m; j++) printf("%co", c[n][j] ? '|' : '.'); puts("+");
	for (int i = 1; i <= 2 * m - 1; i++) putchar('+'); puts("G+");
}
```

---

## 作者：Exp10re (赞：2)

构造好玩。

## 解题思路

主要介绍一下构造思路，根据思路构造地图并不复杂但细节多，故不赘述。

注意到 $k$ 与 $n$ 不同奇偶无解，$k\lt n$ 无解，否则有解。

考虑先把地图设置成所有格子四周都有墙，我们就可以考虑根据我们构造的路线去拆墙。

对于 $k$ 奇数或偶数的情况，都有一种通用解法：

![](https://cdn.luogu.com.cn/upload/image_hosting/waveq512.png)

按照靠右的一条蓝线走过 $n$ 个格子，如果格子总数没有到达 $k$ 就在每一行按照靠左的蓝线走来尝试经过额外的格子。

如图红线即为 $n=5,m=7,k=21$ 的一个解。

该构造方法适用于 $n$ 为偶数或者 $n$ 为奇数且 $k \leq n(m-1)$ 的情况。对于 $k \gt n(m-1)$ 的情况 还要特殊考虑：

![](https://cdn.luogu.com.cn/upload/image_hosting/ot3xx6gy.png)

正常 $k=n(m-1)$ 的情况是按照绿线走的，如果 $k\gt n(m-1)$ 那么就尝试在倒数第二行将一次向右走替换成向下右上走，以此增加两个经过的格子。

容易证明以上两种构造思路能够覆盖全部有解的情况。按照构造思路构造地图即可。

---

## 作者：Milthm (赞：2)

diff：$2098$。

感谢这道题救了我的 rating。

____

我有一个比较复杂的做法，但是思路和官方题解是一样的。

首先我们从起点到终点最少也需要 $n$ 格，所以 $k<n$ 不可能。

其次我们发现无论怎么拐弯，走的格子数和 $n$ 的奇偶性一定是一样的，不一样就不可能。

剩下的情况就是有解了，你可以先画一个竖着走的路线，然后往上面增加类似这样的回路：

![](https://cdn.luogu.com.cn/upload/image_hosting/iqde43sa.png)

这样不停加下去，$n$ 为偶数是可以满足的，但是 $n$ 为奇数只能填到倒数第二行，剩下的就需要再换种走法了：

![](https://cdn.luogu.com.cn/upload/image_hosting/ytev2w3v.png)

我们可以把后两行全部清除，然后再用上图的方法进行填充。

至于实现，我采用了一种抽象的方法，我先用我自己的符号表示出这个迷宫，输出的时候再复原它，反正有点难写，但是很好调。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 505
using namespace std;
int n,m,k;
char a[N][N],ans[N][N];
signed main(){
	cin>>n>>m>>k;
	if(k%2!=n%2||k<n)return cout<<"No",0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)a[i][j]='.'; 
	}
	for(int i=1;i<=n;++i)a[i][m]='|';k-=n;
	int st=0;
	if(n%2)st=1;
	for(int i=1;i<=n-st;i+=2){
		int now=m-1;
		while(k>=2&&now>=1){
			k-=2;a[i][m]='<';a[i+1][m]='v';
			a[i][now]='v';a[i+1][now]='>';
			if(now!=m-1)a[i][now+1]=a[i+1][now+1]='-';--now;
		}
	}
	if(k&&n%2){
		for(int i=1;i<=m;++i)a[n-1][i]=a[n][i]='.';
		a[n-1][1]='v';a[n][1]='>';
		for(int i=2;i<m;++i)a[n][i]='-';a[n][m]='v';
		for(int i=2;i<=m;i+=2){
			if(k>=2){
				k-=2;
				a[n][i]='^';a[n-1][i]='>';a[n-1][i+1]='v';a[n][i+1]='>';
			}
		}
		a[n][m]='v';
	}
	cout<<"Yes\n";
	//for(int i=1;i<=n;++i){
	//	for(int j=1;j<=m;++j)cout<<a[i][j];cout<<'\n';
	//}
	//for(int i=1;i<=n;++i){
	//	for(int j=1;j<=m;++j)ans[i][j]='.';
	//}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int x=i*2,y=j*2;
			ans[x][y]='o';
			if(a[i][j]=='^')ans[x-1][y]='.';
			if(a[i][j]=='v')ans[x+1][y]='.';
			if(a[i][j]=='<')ans[x][y-1]='.';
			if(a[i][j]=='>')ans[x][y+1]='.';
			if(a[i][j]=='-')ans[x][y-1]=ans[x][y+1]='.';
			if(a[i][j]=='|')ans[x-1][y]=ans[x+1][y]='.';
		}
	}
	for(int i=1;i<=2*n+1;++i)ans[i][1]=ans[i][2*m+1]='+';
	for(int i=1;i<=2*m+1;++i)ans[1][i]=ans[2*n+1][i]='+';
	for(int i=1;i<=2*n+1;++i){
		for(int j=1;j<=2*m+1;++j){
			if(i%2&&j%2)ans[i][j]='+';
		}
	}
	for(int i=1;i<=2*n+1;++i){
		for(int j=1;j<=2*m+1;++j){
			if(!ans[i][j]){
				if(ans[i+1][j]=='o')ans[i][j]='-';
				else ans[i][j]='|';
			}
		}
	}
	ans[1][2*m]='S';ans[2*n+1][2*m]='G';
	for(int i=1;i<=2*n+1;++i){
		for(int j=1;j<=2*m+1;++j)cout<<ans[i][j];cout<<'\n';
	}
	return 0;
}

```

这就是模拟给我的自信！

---

## 作者：rhn7 (赞：1)

赛时被 G 骗了，导致这题连看都没看。

我们发现最短路是一直往下走，经过 $n$ 个格子，所以要多走 $k-n$ 个格子。

怎么多走呢？往下一格可以变成先往左走 $x$ 格，再向下一格，最后向右走 $x$ 格，这样就多走了 $2x$ 格。显然多走的格子总数只能是偶数，所以 $k-n$ 是奇数时无解。

构造时画一个弓字形。设 $s$ 为剩下要多走的格子个数，若 $s \ge 2×(m-1)$，说明能走到最左侧再往下，令 $x=m-1$，否则就把 $s$ 走光，令 $x=\frac{s}{2}$。

输出格式比较恶心，建议求出 $r$ 和 $c$ 数组后再按题意输出。

![](https://cdn.luogu.com.cn/upload/image_hosting/vrnylsw9.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[105],c[105][105],r[105][105];
int main(){
	cin>>n>>m>>k;
	if((n-k)%2||k>n*m||k<n) return !(cout<<"No");//最多走n*m格，最少走n格 
	cout<<"Yes\n";
	int sum=k-n;
	for(int i=1;i<n;i+=2){
		if(sum>=2*(m-1)) sum-=2*(m-1),a[i]=m-1;
		else{a[i]=sum/2;break;}
	}
	for(int i=1;i<n;i+=2){//求r,c 
		for(int j=m-1;j>=m-a[i];j--) c[i][j]=1;
		r[i][m-a[i]]=1;r[i+1][m]=1;
		for(int j=m-a[i];j<m;j++) c[i+1][j]=1; 
	}
	//按题意输出 
	for(int i=1;i<2*m;i++) cout<<"+";
	cout<<"S+\n";
	for(int i=2;i<=2*n;i++){
		if(i%2){
			cout<<"+";
			for(int j=1;j<=m;j++) cout<<"-."[r[i/2][j]]<<"+";
		}else{
			cout<<"+o";
			for(int j=1;j<m;j++) cout<<"|."[c[i/2][j]]<<"o";
			cout<<"+";
		}
		cout<<"\n";
	}
	for(int i=1;i<2*m;i++) cout<<"+";
	cout<<"G+\n";
	return 0;
}
```

~~本篇题解结束~~

你以为这就完了？虽然 AT 上能过，但 Register_int 巨佬提供了一组 hack：`3 3 9`，上述代码会经过 $7$ 个格子，这是不对的。

我们发现当 $n$ 是奇数时，最后一行的前 $m-1$ 个格子到不了，所以 $k>(n-1)×m+1$ 时用弓字构造不出来。

怎么改变构造方法呢？前 $n-1$ 行仍然使用弓字，在 $(n-1,1)$ 正要往右走时，改变一下方向，往下走，再往右走一格到达 $(n,2)$。如果再往右走到达 $(n,m)$，就总共经过了 $(n-1)×m+1$ 的格子，关键是现在 $k>(n-1)×m+1$，所以要多走 $k-(n-1)×m-1$ 格。怎么多走呢？可以发现旋转之后就变成了问题本身，走趴着的弓字形即可。行数又为奇怎么办？之前在 $(n-1,1)$ 会往下走，现在往右走停在 $(n-1,2)$，然后走到 $(n-1,m-1)$，这时行数就是 $m-2$ 是偶数，再往右往下到达 $(n,m)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4x056m7c.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[105],c[105][105],r[105][105];
int main(){
	cin>>n>>m>>k;
	if((k-n)%2||k>n*m||k<n) return !(cout<<"No");
	cout<<"Yes\n";
	if(n%2&&k>(n-1)*m+1){
		for(int i=1;i<n;i+=2){
			for(int j=1;j<m;j++) c[i][j]=1;
			r[i][1]=1;
			if(i==n-2) break;
			r[i+1][m]=1;
			for(int j=1;j<m;j++) c[i+1][j]=1;
		}
		if(m%2==0){
			int sum=k-(n-1)*m-1;
			for(int i=2;i<m-1;i+=2){
				c[n-1][i-1]=1;
				if(sum){
					r[n-1][i]=c[n][i]=1;
					r[n-1][i+1]=1;
					sum-=2;
				}else c[n-1][i]=1;
			}
			c[n-1][m-1]=r[n-1][m]=1;
		}else{
			r[n-1][1]=1;
			int sum=k-(n-1)*m-1;
			for(int i=2;i<m;i+=2){
				c[n][i-1]=1;
				if(sum){
					c[n-1][i]=r[n-1][i]=1;
					r[n-1][i+1]=1;
					sum-=2;
				}else c[n][i]=1;
			}
		}
	}else{
		int sum=k-n;
		for(int i=1;i<n;i+=2){
			if(sum>=2*(m-1)) sum-=2*(m-1),a[i]=m-1;
			else{a[i]=sum/2;break;}
		}
		for(int i=1;i<n;i+=2){
			for(int j=m-1;j>=m-a[i];j--) c[i][j]=1;
			r[i][m-a[i]]=1;r[i+1][m]=1;
			for(int j=m-a[i];j<m;j++) c[i+1][j]=1; 
		}
	}
	for(int i=1;i<2*m;i++) cout<<"+";
	cout<<"S+\n";
	for(int i=2;i<=2*n;i++){
		if(i%2){
			cout<<"+";
			for(int j=1;j<=m;j++) cout<<"-."[r[i/2][j]]<<"+";
		}else{
			cout<<"+o";
			for(int j=1;j<m;j++) cout<<"|."[c[i/2][j]]<<"o";
			cout<<"+";
		}
		cout<<"\n";
	}
	for(int i=1;i<2*m;i++) cout<<"+";
	cout<<"G+\n";
	return 0;
}
```

---

## 作者：formu1 (赞：1)

## 题意

给定一个 $N$ 行 $M$ 列的空白方格地图，你可以在相邻格子中适当放置墙壁，以组成一个迷宫。你需要求出是否存在从右上角到右下角，经过 $K$ 个方格的**无分支**路径，如果存在，输出这个迷宫地图。

例如，以下就是一个在 $N=3$ 列 $M=3$ 行，经过 $K=7$ 个方格的**无分支**路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/5lu7gnyr.png)

~~别问我为什么贴个样例在这。~~

## 思路&做法

**我们可以把“在格子边插墙”转化为“寻找路径，再沿路径边缘插墙”**，这样就只需要求出路径即可。

容易得出，该程序有以下几个步骤：

1. 判断是否存在路径。

2. 存在，则计算路径。

3. 按题目方式输出。

### 判断是否存在路径

若存在从右上角到右下角的路径，应满足以下条件：

- $K \geq N$

- $K \leq N \cdot M$

- $K \equiv N \pmod 2$

对于第一和第二个条件，是显而易见的。（~~你都不够格子贴边走，或者塞都塞不下，怎么能行~~）

而对于第三个，我们可以用棋盘染色来证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/rpwnw5cc.png)

容易看出，每走一个格子，颜色就会切换。

如果一个路线是可行的，它最终到达的位置应该与原路线（从起点一路向下到终点）一致。（~~废话~~）

也就是说，它终点的颜色应该与原路线终点的颜色一致。

所以只有在每次增加 $2$ 格的情况下，即该路线多经过了一个“黑白矩阵”，然后又回到原路线的黑白排列，该路线才可行。

### 计算路径

> ~~不要管他那构式输出，自己建一个不香吗。~~

我们可以按 `_map[x][y]=L R U D` 的方式建图，建完后再考虑放墙。

在满足条件，每次增加两个格子的情况下，容易得出，我们需要往原线路左侧部分**扩展** $2$ 的若干倍个格子。

------------


那么怎么扩展呢？~~Mindustry 启动！~~

![](https://cdn.luogu.com.cn/upload/image_hosting/urwa81y6.png)

这是一个 $5 \times 10$ 的迷宫，我们可以在第 $1$、$2$ 行“兜弯”，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qs4o2swo.png)

我们需要两行一起处理，并在在适当时候调整方向，形成闭合路段。

兜到下面，有可能会出现这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/orriycho.png)

欸不是怎么没地方了，没关系我们可以在最后一行做文章

![](https://cdn.luogu.com.cn/upload/image_hosting/y2amh0f6.png)

如图，每次再扩展 $2$ 格，就可以适应所有情况。

这就是基本的思想。因为 $K \leq N \cdot M$，所以直接循环 $K$ 次即可。

------------


此段代码：

```cpp
//先将地图右侧原路径设为向下
for(int i=1;i<=n;++i){
  _map[i][m]=D;
}

int x=-1,y=0;//初始坐标，进入循环后立即修正
int i=1;//i表示当前是第几轮添加转弯的
for(;i<=(k-n)/2;++i){//总共有(k-n)/2个需要添加
  if(y<1){//本行已满
    x+=2;
    y=m-1;
    if(x+1>n) break;//如果现在只有最后一行有空位，另外计算
    _map[x][y+1]=L;//往左扭，以添加转弯
    //_map[x+1][y+1]=D;
    //这句是废话，上面已经初始化了
  }
  _map[x][y]=(y==1)?(D):(L);//往左扭
  //如果说本行已满，那么形成闭合路段
  _map[x+1][y]=R;//往右扭
  y-=1;//继续添加
}
if(x!=-1) _map[x][y+1]=D;//形成闭合路段，避免越界
if(i<=(k-n)/2){//只有最后一行空位
  x=n,y=1;
  for(;i<=(k-n)/2;++i){
    _map[x-1][y]=D;
    _map[x][y]=R;
    _map[x][y+1]=U;
    y+=2;
  }
}
```

此段代码运行过程：（~~应该没问题吧~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/hhqwhiuk.png)

### 输出

~~这下不得不管了。~~

输出方式：

上图中墙壁用 `+` 代替，方格用 `o` 代替。起点，终点用 `S` 和 `G`。如果说两个方格之间有路线连接，就用 `.` 表示（即平地）。没有路线连接，也就是原文的“墙”，就用 `|` 或 `-` 表示（当然，如果是上下无连接，是 `-`，另一种就是 `|`）。

样例 $1$ 即是上图第 $4$ 步，可以对着参照一下。

------------


那么，怎么输出呢？

显而易见，输出第一行，是 $2M-1$ 个 `+`、$1$ 个 `S`、$1$ 个 `+` 连接起来的。最后一行同理，把 `S` 替换成 `G` 即可。

而对于中间部分，先输出 $1$ 个 `+`，然后分两种情况处理：

- 方格行：`o`、`|` 或 `.` 交叉排列。对于夹在两个 `o` 之间的 `|` 或 `.`，看左边、右边的方格是否有一个指向它，然后二选一。

- 墙壁行：`-` 或 `.`、`+` 交叉排列。对于夹在两个 `+` 之间的 `-` 或 `.`，看上边、下边的方格是否有一个指向它，然后二选一。

判断这两种情况、交叉排列只需要 mod 一下即可。

输出看完整代码解释。

至此，这道题就做完了。

### 几个小细节

1. `L R U D` 的表示不要牵扯到 `0`，这会造成支路。

2. 记得将 `if(x!=-1) _map[x][y+1]=D;` 加上，也就是将没有闭合的地方调整好。

3. 小心越界与 `x`、`y`、`i`、`j` 的处理。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define L 1
#define R 2
#define U 3
#define D 4
using namespace std;
const int maxn=105;
int n,m,k;
int _map[maxn][maxn];
void output(){
	//开头第一行
	for(int i=1;i<=2*m-1;++i) printf("+");
	printf("S+\n");
	for(int i=1;i<2*n;++i){
		if(i%2==1){//方格行
			printf("+");//当头一棒
			for(int j=1;j<2*m;++j){
				if(j%2==1) printf("o");//方格
				else{
					if(_map[(i+1)/2][j/2]==R||_map[(i+1)/2][j/2+1]==L) printf(".");
					else printf("|");
					//如果有连接，即为平地，否则即为墙壁
				}
			}
			printf("+\n");//致命一击
		}
		else{//墙壁行，同上
			printf("+");
			for(int j=1;j<=2*m;++j){
				if(j%2==1){
					if(_map[i/2][(j+1)/2]==D||_map[i/2+1][(j+1)/2]==U) printf(".");
					else printf("-");
				}
				else printf("+");//因为墙壁行最后的加号与中间部分一致，所以不用特判
			}
			puts("");
		}
	}
	for(int i=1;i<=2*m-1;++i) printf("+");
	printf("G+\n");
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(k<n||k>(n*m)||(k-n)%2!=0){
		printf("No\n");
		return 0;
	}
	else printf("Yes\n");
	
	//下面不再赘述
	for(int i=1;i<=n;++i){
		_map[i][m]=D;
	}
	int x=-1,y=0;
	int i=1;
	for(;i<=(k-n)/2;++i){
		if(y<1){
			x+=2;
			y=m-1;
			if(x+1>n) break;
			_map[x][y+1]=L;
			_map[x+1][y+1]=D;
		}
		_map[x][y]=(y==1)?(D):(L);
		_map[x+1][y]=R;
		y-=1;
	}
	if(x!=-1) _map[x][y+1]=D;
	if(i<=(k-n)/2){
		x=n,y=1;
		for(;i<=(k-n)/2;++i){
			_map[x-1][y]=D;
			_map[x][y]=R;
			_map[x][y+1]=U;
			y+=2;
		}
	}
	output();
	return 0;
}
```

The end.

---

## 作者：EllinY (赞：0)

一道模拟题。
# 思路
最短的路线是直接竖着走下来，经过 $n$ 个格子，所以 $k$ 最小是 $n$。如果想要延长路线，可以采用九转大肠的形状，就像这样：$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/ucagxp6n.png)
$\\$ 可以发现，每次向左走之后都必须走回来，所以每次新经过的格子数是偶数，得到 $k-n$ 是偶数才有可行的方案。$\\$ 首先，把整张图表的初始状态设为如下形式（即每个格点都是独立的）：
```
+++++S+
+o|o|o+
+-+-+-+
+o|o|o+
+++++G+
```
将 $k$ 先减去必要的格点数 $n$。两行为一组进行考虑，如果此时 $k\ge2(m-1)$ 就意味着可以走到最左边再折回去，于是将两行之间第一列的连接处设为“.”。否则令 $t=k/2$，把从右往左第 $t+1$ 列的两行之间的连接处设为“.”。还有，不要忘记把一行里面左右相邻的格子连接处设为“.”，最后一列通往下一行（下一组的第一行）的连接处也要设为“.”。每次标完之后要将 $k$ 减去增加的格点数：$max(2(m-1),k)$。$\\$ 如果行数是奇数并且 $k$ 不为 $0$，那么最后一行需要特殊考虑，可以通过如下图的形式继续延长道路长度：$\\$
![](https://cdn.luogu.com.cn/upload/image_hosting/gse3kisi.png)
$\\$ 原本的迷宫长这样：$\\$
![](https://cdn.luogu.com.cn/upload/image_hosting/7p5yxley.png)
$\\$ 此时两列一组考虑，但是最后一列必须空出来，确保通往出口的通道。所以当考虑到一个 $2\times2$ 的方形（跨越第 $n-1$ 行和第 $n$ 行）并且 $k>0$ 时，要做的事情：
1. 在第一行第一列和第一行第二列之间插入一块板子“|”。
2. 把其余的连接处都设成“.”。

这样每次可以把道路的长度延长两个格子（$k$ 减去 $2$），并走回第 $n-1$ 行。但是如果列数是偶数，最后一列又要走到第 $n$ 行出迷宫，那么分组时就会多出倒数第二列。所以并不是每个格子都走得到，奇数行偶数列的迷宫里会有一个格子（程序里默认是第 $n$ 行第 $m-1$ 列）无法走到（即 $k\le nm-1$）。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/b0nnmig9.png)
# 代码实现
就是多画几张图，把输出矩阵中的行号和列号与实际迷宫中的行号和列号对应起来。本人考场上没有考虑最后剩下一行的情况，WA 三个点。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxk (n-1)*m+1
#define mink n
int n,m,k;
char ans[300][300];
void pre(){
	for(int i=1;i<=2*m+1;i++){
		if(i==2*m) ans[1][i]='S',ans[2*n+1][i]='G';
		else ans[1][i]=ans[2*n+1][i]='+';
	}
	for(int i=1;i<=2*n+1;i++) ans[i][1]=ans[i][2*m+1]='+';
	for(int i=2;i<=2*n;i++)
		for(int j=2;j<=2*m;j++){
			if(i%2==0){
				if(j%2==0) ans[i][j]='o';
				else ans[i][j]='|';
			}
			else{
				if(j%2==0) ans[i][j]='-';
				else ans[i][j]='+';
			}
		}
}
int main(){
	cin>>n>>m>>k;
	if(k<mink||(k-n)%2){
		cout<<"No"<<endl;
		return 0;
	}
	pre();
	k-=n;
	for(int i=1;i<=n;i+=2){
		if(i==n) break;
		if(k>=2*(m-1)){
			for(int j=3;j<=2*m-1;j+=2){
				ans[2*i][j]='.';
				ans[2*i+2][j]='.';
			}
			k-=2*(m-1);
			ans[2*i+1][2]='.';
		}
		else{
			for(int j=2*m-1;j>=2*m-(k-1);j-=2){
				ans[2*i][j]='.';
				ans[2*i+2][j]='.';
			}
			ans[2*i+1][2*m-k]='.';
			k=0;
		}
		if(2*i+3<2*n+1) ans[2*i+3][2*m]='.';
	}
	if(k){
		if(m%2==0&&k==m-1){
			cout<<"No"<<endl;
			return 0;
		}
		int i=n-1;
		for(int j=1;j<n-1&&k;j+=2){
			ans[i*2][j*2+1]='|';
			ans[i*2+1][j*2]=ans[i*2+1][j*2+2]=ans[i*2+2][j*2+1]='.';
			k-=2;
		}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=2*n+1;i++){
		for(int j=1;j<=2*m+1;j++)
			cout<<ans[i][j];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC358F] Easiest Maze

**Upd 24-08-12**，[原题解](https://www.luogu.com.cn/paste/orkl6a61)。

当 $n$ 为奇数且 $k\gt(n-1)\times m+1$ 时原题解输出有误[^1]，原题解赛时可过[^2]，赛后 AtCoder 加强数据之后不能过[^3]。

[^1]: [Hack 帖](https://www.luogu.com.cn/discuss/836631)
[^2]: [赛时提交记录](https://atcoder.jp/contests/abc358/submissions/54601658)
[^3]: [赛后提交记录](https://atcoder.jp/contests/abc358/submissions/54927324)

在 $n$ 为奇数且 $k\gt(n-1)\times m+1$ 这种情况下，需要将后三行一起考虑，构造出路径为：

```plaintext
. . ↓ ← ← ← ←
. . ↓ → ↓ → ↓
. . → ↑ → ↑ ↓
```

其中 `.` 可能为这样形状的填充，也可能是不经过。

完整代码见[最新提交记录](https://atcoder.jp/contests/abc358/submissions/56629392)。

原题解错误的原因是最后强制两行两行考虑，最后一行不能操作。所以为了解决上述情况，需要将最后一行和倒数二、三行一起考虑进行构造。

---

## 作者：Hope888 (赞：0)

恶心的格式输出让我赛时没调出来。

# 思路

首先最短的方案是从起点向下直接走到终点，总长为 $n$。

### 考虑如何使经过格子的数量增加：

一种明显的做法是每次从路径中选出**两排**长度相同的路径，每次把它们的宽度扩大，这样可以每次使用 $2$ 个格子去增加 $2$ 的路径长度。

Like this->

```
+++++S+
+o.o.o+
+.+-+-+
+o.o.o+
+++++G+
```

但是可能会出现总列数为奇数的情况，这样会导致有一列无法使用，可以最后两排用**蛇形**的路线，这样就可以不浪费最后两排。

Like this->

```
+++++S+
+o.o.o+
+.+-+-+
+o|o.o+
+.+.+.+
+o.o|o+
+++++G+
```

### 无解判断

根据上述做法描述，明显对于：

1. 需要构建的路径长度小于排的个数
2. 需要构建的路径长度大于格子总数
3. 需要构建的路径长度与每排个数的奇偶性不同
4. 在总列数为奇数且路径长度与格子总数相等时且排的个数为偶数（由于无法在蛇形路线结束后刚好从 $G$ 离开）

这些情况无解。

### Code
代码实现较为麻烦，如果有调不出来的可以看看讨论区中我发的对拍程序。对于代码有问题的可以在讨论区提问。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	cin>>n>>m>>k;
	if(k>n*m||k<n||k%2!=n%2||n%2==1&&m%2==0&&k>=n*m)
	{
		cout<<"No";
		return 0;
	}
	cout<<"Yes"<<endl;
	int num=(k-n)/2;
		for(int i=1;i<=m*2+1;i++)
		{
			if(i==m*2)cout<<'S';
			else cout<<'+';
		}
		cout<<endl;
		for(int i=1;i<=n/2;i++)
		{
			int now;
			if(num>=m-1)
			{
				now=m-1;
				num-=m-1;
			}
			else
			{
				now=num;
				num=0;
			}
			if(i!=1)
			{
				cout<<'+';
				for(int i=1;i<=m;i++)
				{
					if(i==m)cout<<'.';
					else cout<<'-';
					cout<<'+';
				}
				cout<<endl;
			}
			cout<<'+';
			for(int i=m;i>=1;i--)
			{
				cout<<'o';
				if(now==i-2&&now!=m)cout<<'|';
				else if(i!=1)cout<<'.';
			}
			cout<<'+'<<endl<<'+';
			for(int i=m;i>=1;i--)
			{
				if(now+1==i)cout<<'.';
				else cout<<'-';
				cout<<'+';
			}
			cout<<endl;
			cout<<'+';
			if(i==n/2&&num)
			{
				int temp=num;
				for(int i=1;i<=m;i++)
				{
					cout<<'o';
					if(temp&&i%2==1&&i!=m)
					{
						cout<<'|';
						--temp;
					}
					else if(i!=m)cout<<'.';
				}
				cout<<'+'<<endl;
				continue;
			}
			for(int i=m;i>=1;i--)
			{
				cout<<'o';
				if(now==i-2&&now!=m)cout<<'|';
				else if(i!=1)cout<<'.';
			}
			cout<<'+'<<endl;
		}
		if(k&1)
		{
			cout<<'+';
			if(num)
			{
				int temp=num*2;
				for(int i=1;i<=m;i++)
				{
					if(temp||i==m)
					{
						cout<<'.';
						--temp;
					}
					else cout<<'-';
					cout<<"+";
				}
			}
			else
			{
				for(int i=1;i<=m;i++)
				{
					if(i==m)cout<<'.';
					else cout<<'-';
					cout<<'+';
				}
			}
			cout<<endl<<'+';
			if(num)
			{
				for(int i=1;i<=m;i++)
				{
					cout<<'o';
					if(num>0&&i%2==0||i==m-1)
					{
						cout<<'|';
						--num;
					}
					else if(i!=m)cout<<'.';
				}
			}
			else
			{
				for(int i=m;i>=1;i--)
				{
					cout<<'o';
					if(i==2)cout<<'|';
					else if(i!=1)cout<<'.';
				}
			}
			cout<<'+'<<endl;
		}
		for(int i=1;i<=m*2+1;i++)
		{
			if(i==m*2)cout<<'G';
			else cout<<'+';
		}
}
```

---

## 作者：fire_and_sweets (赞：0)

我们考虑按照矩阵的行数进行分类。

如果是偶数行的话，我们直接从上到下蛇形构造。

如果是奇数行的话，分两种情况考虑：
- 如果 $k$ 比较小，我们仍然用偶数行的方法构造，最后一行留空白。
- 否则，我们先用偶数行的方法构造前 $n-2$ 行，剩余行竖着进行蛇形构造。

具体细节（例如 $-1$ 的判断等）见代码。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 500;

int n, m, k;
char f[N][N];

void work_even()
{
	if (m == 1)
	{
		cout << "+S+" << endl;
		for (int i = 1; i < 2 * n; i ++ )
		{
			if (i & 1) cout << "+o+";
			else cout << "+.+";
			cout << endl;
		}
		cout << "+G+" << endl;
		exit(0);
	}
	k = (k - n) / 2;
	int H = 1, L = 1;
	for (int i = 1; i <= k / (m - 1); i ++ ) {
		for (int t = 1; t <= m - 1; t ++ )
			if (4 * i + 1 <= 2 * n) f[4 * i + 1][2 * t] = '-';
		H = 4 * i + 1;
		for (int t = 1; t <= m - 1; t ++ )
			if (4 * i - 1 <= 2 * n) f[4 * i - 1][2 * m + 1 - 2 * t + 1] = '-';
	}
	if (k % (m - 1) != 0)
	{
		for (int t = 1; t <= k % (m - 1); t ++ )
			if (H + 2 <= 2 * n) f[H + 2][2 * m + 1 - 2 * t + 1] = '-', L = 2 * m + 2 - 2 * t;
		H += 2;
		f[H - 1][L - 3] = '|';
		f[H + 1][L - 3] = '|';
		for (int t = L - 2; t <= 2 * m - 2; t += 2)
			if (H + 2 <= 2 * n && t >= 2) f[H + 2][t] = '-';
		H += 2;
	}
	for (int i = H + 1; i <= 2 * n; i += 2)
		f[i][2 * m + 1 - 2] = '|';
} 

void work_odd()
{
	if (k <= (n - 1) * m + 1)
	{
		work_even();
		return;
	}
	for (int i = 1; i <= n / 2; i ++ )
	{
		if (4 * i + 1 <= 2 * n + 1 && i != n / 2) for (int t = 1; t <= m - 1; t ++ )
			f[4 * i + 1][2 * t] = '-';
		if (4 * i - 1 <= 2 * n + 1) for (int t = 1; t <= m - 1; t ++ )
			f[4 * i - 1][2 * m + 1 - 2 * t + 1] = '-';
	}
	k -= (n - 2) * m + 2 + (m - 1);
	k /= 2;
	int h = 2 * n + 1 - 3, maxL = -1;
	for (int i = 1, L = 3; i <= k; i ++ , L += 4)
	{
		if (h >= 2) f[h][L] = '|'; 
		if (L + 4 < 2 * m + 1) f[h][L + 4] = '|';
		f[h + 2][L + 2] = '|';
		maxL = L;
	}
//	cout << maxL << endl;
	for (int i = maxL + 5; i < 2 * m + 1; i += 2)
		if (h + 1 >= 2 && h + 1 <= 2 * n) f[h + 1][i] = '-';
}

void work() {
	puts("Yes");
	memset(f, '.', sizeof f);
	int tn = n, tm = m;
	n = 2 * n + 1, m = 2 * m + 1; 
	for (int i = 1; i <= m; i ++ )
		f[1][i] = f[n][i] = '+';
	for (int i = 1; i <= n; i ++ )
		f[i][1] = f[i][m] = '+';
	for (int i = 1; i <= n; i += 2)
		for (int j = 1; j <= m; j += 2)
			f[i][j] = '+';
	for (int i = 2; i <= n; i += 2)
		for (int j = 2; j <= m; j += 2)
			f[i][j] = 'o';
	f[1][m - 1] = 'S'; f[n][m - 1] = 'G';
	n = tn, m = tm;
	if (k % 2 == 1) work_odd();
	else work_even(); 
	for (int i = 1; i <= 2 * n + 1; i ++ , cout << endl)
		for (int j = 1; j <= 2 * m + 1; j ++ )
			cout << f[i][j];
}

signed main()
{
//	freopen("r1.in", "r", stdin);
//	freopen("t1.txt", "w", stdout);
	cin >> n >> m >> k;
	if (k < n || k > n * m || ((k+1)&1) == (n&1)) puts("No");
	else if (n % 2 == 1 && m % 2 == 0 && k == n * m) puts("No");
	else if (n == 1 && k > 1) puts("No"); 
	else work();
	return 0;
}
```

---

## 作者：Targanzqq (赞：0)

主要算法：模拟。
### 思路：
首先判断无法完成的情况：我们考虑从右上角到右下角，最理想的路径如下图的形式：
![](https://cdn.luogu.com.cn/upload/image_hosting/28o0ixdq.png)
或者这种形式：
![](https://cdn.luogu.com.cn/upload/image_hosting/fmzyoi0v.png))
易证明任何满足条件的路径长度都可以采用这种形式。

但是显然对于其中任意一种，在**除最右一列经过的点个数都是偶数**，且当路径长度 $k$ 小于 $n$ 时，无法走到终点，所以无法构造的条件为 $k$ 与 $n$ 奇偶性不同，或 $k<n$。

接下来开始构造。

首先我们考虑所有使用符号的优先级问题。优先级最高的符号为 “+”，其次为 “-” 和 “|”，最低为 “.”，“o”不影响。所以我们将所有格子初始化为 “.”，然后进行模拟，最后填入 “+” 和 “o”。

我们考虑上面两种情况，显然第一种更便于模拟，主要分为**填满**和**填不满**两种情况，以下为主要模拟方法：

（请注意，以下的**行**和**列**除特殊说明以外均为构造图中的行和列。）

设 $p=\lfloor\frac{k-n}{2(m-1)}\rfloor$，$q=k-n-2(m-1)p$，则此时 $p$ 表示**填满**的**组数**，共 $2p$ 行，$q$ 表示**填不满**的行中在**原图中第 $m$ 列**左侧的方格**个数**。

在第一张图中，$p=1$，$q=2$。然后我们不难发现，对于第 $i$ 个填满的组中第 $2$ 和第 $4$ 行需要从左数第二行到最右每隔一行填满 “-”，每组第 $2$ 行左数第二列为 “.”，每组第 $4$ 行右数第 $2$ 列为 “.”。

对于填不满的行，我们就按以上的方法从右往左填 $q$ 个即可，特殊的 “.” 位置与上面相同。然后再填不满的行第 $1$，$3$ 列左侧填入 “|”。

填完之后，我们需要在填不满的行结尾到终点之间建立路径，即从填不满的行下面的一行开始，在从右往左数第二列，每两行填一个 “|”。

除此以外，还有一种特殊情况，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/8gwjzgze.png)
这种情况下，我们应使用最开始两图中的第二种进行模拟，但是因为这种情况比较特殊，所以模拟起来也相对简单。

我们算出 $p$ 之后，从 $1$ 到 $p-1$ 组按上面的操作，然后我们重定义 $q$ 为 $nm-k$，即不经过的格子数。我们在倒数第 $3$ 行，对于所有 $i\le q$，我们将这一行的第 $i$ 列填入 “-”，然后对于倒数第 $4$ 行，我们从第 $4q-1$ 列开始到最右一列之前，每隔 $4$ 列填入 “|”，对于倒数第 $2$ 行，我们从第 $4q-3$ 列开始，到最右之前填入 “|”。这样就完成了这种特殊情况的模拟。

### 源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,k,N,M;
char a[1001][1001]; 

void solve2(){
	int q=n*m-k;
	for(int i=1;i<n/2;i++){
		for(int j=2;j<=m;j++){
			a[4*i-1][2*j]='-';
		}
		for(int j=1;j<m;j++){
			a[4*i+1][2*j]='-';
		}
    }
    for(int j=2;j<=m;j++){
		a[4*(n/2)-1][2*j]='-';
	}
	for(int j=1;j<=q;j++){
		a[N-2][2*j]='-';
	}
	for(int i=2*q+3;i<M;i+=4){
		a[N-3][i]='|';
	}
	for(int i=2*q+1;i<M;i+=4){
		a[N-1][i]='|';
	}
}

void solve(){
	int p=0,q=0;
	if(m==1)goto Next;
	if(k>n/2*2*m+1){
		solve2();
		goto next2;
	}
	p=(k-n)/(2*(m-1));
	q=(k-n)%(2*(m-1))/2;
	//cout<<p<<" "<<q<<endl;
	for(int i=1;i<=p;i++){
		for(int j=2;j<=m;j++){
			a[4*i-1][2*j]='-';
		}
		for(int j=1;j<m;j++){
			a[4*i+1][2*j]='-';
		}
    }
	if(q>0){
		a[4*p+2][M-2-2*q]='|';
        a[4*p+4][M-2-2*q]='|';
	}
    for(int i=1;i<=q;i++){
	    a[4*p+3][M+1-2*i]='-';
	    a[4*p+5][M-1-2*i]='-';
	}
	Next:
	for(int i=4*(p+(q>0))+2;i<N;i++){
		a[i][M-2]='|';
	}
	next2:
		int homo=114514;
}

signed main(){
	//ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	//cout<<"No";return 0;
	if(k%2!=n%2||k<n){
		cout<<"No";return 0;
	}
	cout<<"Yes"<<endl;
	N=2*n+1;
	M=2*m+1; 
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			a[i][j]='.';
		}
	}
	solve();
	for(int i=1;i<=N;i++){
		a[i][1]='+';
		a[i][M]='+';
	}
	for(int j=1;j<=M;j++){
		a[1][j]='+';
		a[N][j]='+';
	}
	a[1][M-1]='S';a[N][M-1]='G';
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[2*i][2*j]='o';
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			a[2*i+1][2*j+1]='+';
		} 
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			cout<<a[i][j];
		}
		cout<<"\n";
	}
}

```

---

## 作者：_Weslie_ (赞：0)

什么时候 ABC 也开始构造了……

### Idea

先判断无解。

显然最少走 $n$ 步才能到终点，最多途径 $n\times m$ 个格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/ig8zotj0.png)

上图中红色为最短的路径，蓝色为稍微绕一点路的路径，不难看出，无论我们怎么绕，都得多走至少 $2$ 个格子回到原来的最短路上。

![](https://cdn.luogu.com.cn/upload/image_hosting/j1lzqnfb.png)

红线是我们的最短路径，而蓝线是最长的。我们考虑从最短路上每次加 $2$ 个点，最后可能加到 $k$ 个点。

因为最短路在最右边，我们只需往左加即可。如果加到最左边了，就启用下一行。

但是有可能 $k$ 和 $n$ 在模 $2$ 的意义下不同余，这样无解。

但是有可能 $n$ 为奇数，这样会出现下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ngwp85r.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/scw7vnpl.png)

这时上图的绿线是利用率最高的。不难看出，我们在倒数第二行与最后一行之间作了许多弯曲。

所以只需在代码里判断一下这种情况就解完了。

**注意本题特殊的输出格式。**

### Code

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
char ans[205][205];
void sol(){
	k=k-n;
	int x=2,y=2*m;
	k/=2;
	while(k){
		ans[x][y-1]='.';
		ans[x+1][y-2]='.';
		ans[x+2][y-1]='.';
		ans[x+1][y]='-';
		y-=2;
		k--;
		if(y<=2){
			y=2*m;
			x+=4;
		}
		if(x>=2*n)break;
	}
	if(k==0)return;
	x=2*n;y=2;
	while(k){
		k--;
		ans[x-1][y]='.';
		ans[x][y+1]='.';
		ans[x-1][y+2]='.';
		ans[x-2][y+1]='|';
		y+=4;
	}
	return;
}
int main(){
	cin>>n>>m>>k;
	if(k<n){
		cout<<"No";
		return 0;
	}
	else if(k>n*m){
		cout<<"No";
		return 0;
	}
	else if(k%2!=n%2){
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=2*n+1;i++){
		for(int j=1;j<=2*m+1;j++){
			if(i==1||i==2*n+1){
				ans[i][j]='+';
				if(j==2*m){
					if(i==1)ans[i][j]='S';
					else ans[i][j]='G';
				}
			} 
			else if(i%2==0){
				if(j==1||j==2*m+1)ans[i][j]='+';
				else{
					if(j%2)ans[i][j]='|';
					else ans[i][j]='o';	
				}
			}
			else{
				if(j%2)ans[i][j]='+';
				else if(j==m*2)ans[i][j]='.';
				else ans[i][j]='-';
			}
		}
	}
	sol();
//	ans[n*2-1][m*2]='.';
	ans[n*2+1][m*2]='G';
	for(int i=1;i<=2*n+1;i++){
		for(int j=1;j<=2*m+1;j++){
			cout<<ans[i][j];
		};
		cout<<endl;
	}
	return 0;
}
 ```

---

