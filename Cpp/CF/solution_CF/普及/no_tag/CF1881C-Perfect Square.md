# Perfect Square

## 题目描述

Kristina有一个大小为$n \times n$的矩阵，里面填满了小写拉丁字母。$n$的值是偶数。

她想要改变一些字符，使得她的矩阵变成一个完美方阵。一个矩阵被称为完美方阵，如果它在顺时针旋转90度后仍然保持不变。

这是一个顺时针旋转矩阵90度的例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1881C/4b38bf84bcab0c377c4a504ebb049a6239821153.png)

在一次操作中，Kristina可以选择任意一个单元格，并将其值替换为字母表中的下一个字符。如果字符等于"z"，则它的值不会改变。

找出使得矩阵成为完美方阵所需的最小操作次数。

例如，如果$4 \times 4$的矩阵如下所示：

$ \begin{matrix} a & b & b & a \\ b & c & \textbf{b} & b \\ b & c & c & b\\ a & b & b & a \\ \end{matrix} $

那么只需要对加粗的字母b进行1次操作即可。

## 说明/提示

第一个测试用例在问题描述中已经解释过了。

## 样例 #1

### 输入

```
5
4
abba
bcbb
bccb
abba
2
ab
ba
6
codefo
rcesco
deforc
escode
forces
codefo
4
baaa
abba
baba
baab
4
bbaa
abba
aaba
abba```

### 输出

```
1
2
181
5
9```

# 题解

## 作者：liuyi0905 (赞：7)

## 题意：
给定一个 $n\times n$ 大小的矩阵，每次操作可以将一个字母变成字母表序中下一个字母。求最小操作次数使矩阵旋转 $90^\circ$ 仍保持不变。

注意：本题有多组数据。
## 思路：
要将点 $(i,j)$ 任意旋转 $90^\circ$ 的字母都保持不变，则要找到点 $(i,j)$ 的三个对应点：$(j,n-i+1)$、$(n-j+1,i)$、$(n-i+1,n-j+1)$。既然要将这四个点变为相同的点，则变成的字母一定是这四个点中字母表序最大的一个字符，其操作次数即为 $\max\{a_{i,j},a_{j,n-i+1},a_{n-j+1,i},a_{n-i+1,n-j+1}\}\times4-a_{i,j}-a_{j,n-i+1}-a_{n-j+1,i}-a_{n-i+1,n-j+1}$，其中 $a_{i,j}$ 表示从字符 `a` 变成第 $i$ 行第 $j$ 列的字符的操作次数。

设 $cnt_{i,j}$ 表示点 $i,j$ 的操作次数，则最后答案即为：
$$\sum\limits_{i=1}^{n/2}\sum\limits_{j=1}^{n/2}cnt_{i,j}$$
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,n,a[N][N],ans;
char c;
int main(){
	for(cin>>t;t;ans=0,t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)cin>>c,a[i][j]=c-'a';
		for(int i=1;i<=n/2;i++)
			for(int j=1;j<=n/2;j++){
				int maxi=max({a[i][j],a[n-j+1][i],a[j][n-i+1],a[n-i+1][n-j+1]});
				int cnt=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];
				ans+=maxi*4-cnt;//累加每个点的操作次数 
			}
		cout<<ans<<"\n";//多测换行不要用 endl，"\n" 快得多 
	}
	return 0;
}
```

---

## 作者：_anll_ (赞：4)

# 题目大意
给你个 $n \times n$ 的矩阵，让你操作，每次操作都可以将一个字母变成下一个字母，问你至少要操作多少次才能让这个矩阵旋转 $90\degree$ 之后仍是原矩形。

注：本题为多测，~~典型的 cf~~。

# 解题思路
~~挺简单粗暴的。~~ 我们先以样例为例，模拟一下。
$$
{\color{green}a} \hspace{0.5cm} {\color{blue}b} \hspace{0.5cm} {\color{red}b} \hspace{0.5cm} {\color{green}a} 
$$
$$
{\color{red}b} \hspace{0.5cm} c \hspace{0.5cm} b \hspace{0.5cm} {\color{blue}b}
$$
$$
{\color{blue}b} \hspace{0.5cm} c \hspace{0.5cm} c \hspace{0.5cm} {\color{red}b}
$$
$$
{\color{green}a} \hspace{0.5cm} {\color{red}b} \hspace{0.5cm} {\color{blue}b} \hspace{0.5cm} {\color{green}a}
$$
不难发现，以下我用同一个颜色标记的位置均是一个字母分别反转 $90\degree $，$180\degree$，$270\degree$，$360\degree$所对应的。

很容易得出，只有使这同色的四个位置的字母相同，才能让翻转后的矩阵一样。知道了这个关键点后，我们再推一下就可以把这四个位置表示出来啦~
$$
map[i][j]=map[n-j+1][i]=map[n-i+1][n-j+1]=map[j][n-i+1]
$$
# 代码部分
听我啰嗦了这么多，终于到了~~你们最期待的~~代码环节啦！
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int t,n,ans;
char map[3005][3005],vu[3005][3005],dy[5];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>map[i][j];
				vu[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(vu[i][j]==1) continue;
				vu[i][j]=1,vu[n-i+1][n-j+1]=1;
				vu[n-j+1][i]=1,vu[j][n-i+1]=1;//将同组的打上标记
				dy[1]=map[i][j],dy[2]=map[n-i+1][n-j+1];
				dy[3]=map[n-j+1][i],dy[4]=map[j][n-i+1];
				sort(dy+1,dy+5);
				for(int i=1;i<4;i++) ans+=dy[4]-dy[i];//累加每个点的操作次数
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
~~话说这是本蒟蒻写的第一篇题解欸，希望能过 QAQ。~~

~~都看到这里了，不妨点个赞+关注呗！~~

---

## 作者：1234567890sjx (赞：2)

一个矩阵是完美的当且仅当这个矩阵中任意的一个元素 $a_{i,j}$ 和她在矩阵分别旋转 $90^\circ$，$180^\circ$，$270^\circ$ 后所在的位置当前的元素的值相等。

因为 $2\mid n$，所以容易发现上面的四个位置分别在矩形的左上角，左下角，右上角和右下角。

枚举左上角的每一个位置，计算让她和另外三个位置的值全部相等需要的最小代价即可。

```cpp
void slv(int tc = 0) {
	if (tc) {
		cerr << "Test Case " << tc << '\n';
	}
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	int sum = 0;
	for (int i = 1; i <= n / 2; i++) {
		for (int j = 1; j <= n / 2; j++) {
			// (i, j) (j, n - i + 1) (n - j + 1, i) (n - i + 1, n - j + 1)
			int to = max({a[i][j], a[j][n - i + 1], a[n - j + 1][i], a[n - i + 1][n - j + 1]});
			int s = a[i][j] + a[j][n - i + 1] + a[n - j + 1][i] + a[n - i + 1][n - j + 1];
			sum += 4 * to - s;
		}
	}
	cout << sum << '\n';
}
```

---

## 作者：细数繁星 (赞：1)


[博客园体验更好！](https://www.cnblogs.com/2044-space-elevator/articles/17857938.html)
## 思路

简单滴很，对于每一组 $(i,j)$ 找出其对应的三个点，减一减就完了。

对应的点是哪三个呢？显然是 $(n-i+1,n-j+1)$，$(j,n-i+1)$ 以及 $(i,n-j+1)$ 嘛！

但如果你真的只是累加 $4\times m[i][j]-m[n-i+1][n-j+1]-m[i][j]-m[j][n-i+1]-m[i-j+1]$，恭喜你，没过样例！

## 哪里出问题了？

我们设这四个字母分别为 `e,c,d,f`，按照程序模拟一遍，可以得到为 $4$，这其实是因为你没法从 `f` 倒退到 `e`！这也是这个程序的错误之处。

所以我们只能从四个字母中选最大的，然后其他的三个字母一直加到最大的字母，所以我们可以得到正确的程序如下：

## 代码


```cpp
// Problem: Perfect Square
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1881C
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Coding by 2044_space_elevator

#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
using namespace std;

typedef long long ll;
typedef unsigned long long ull;


char _map[(int)1e3 + 5][(int)1e3 + 5];
void solve() {
	int n;
	cin >> n;
	rep(i, 1, n) {
		rep(j, 1, n) {
			cin >> (_map[i][j] -= 'a');
		}
	}
	int res = 0;
	rep(i, 1, n >> 1) {
		rep(j, 1, n >> 1) {
			initializer_list<int> tmp = {
				_map[i][j],
				_map[n - j + 1][i],
				_map[j][n - i + 1],
				_map[n - i + 1][n - j + 1]
			};
			res += max(tmp) * 4 - (accumulate(tmp.begin(), tmp.end(), 0));
		}
	}
	cout << res << endl;
}


int main() {
	int t; cin >> t; while (t--) solve();
	return 0;
}

```

> 解释一下：`initializer_list` 是我为了方便求值用的，其为函数中不定参数的类型。`accumulate` 为求和。



---

## 作者：wanghaoran00 (赞：1)

### 翻译
给定一个边长为 $n$ 的正方形字符矩阵，由小写字母组成，每次操作单个字母变为它的下一个字母，操作多少次后使其旋转九十度后不发生改变。（多测）

### 思路
将正方形分为相等的四块，以四角为例，左上旋转到右上角，以此类推，四角都应相等，找到四块中每一个对应点的最大值，作差即可

ACcode
```
#include <bits/stdc++.h>
using namespace std;
int t,n,ans,maxa,a[1005][1005];
char x;
signed main(){
    scanf("%d",&t);
    while(t--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>x;
                a[i][j]=x-'a';
            }
        }
        for(int i=1;i<=n/2;i++){
            for(int j=1;j<=n/2;j++){
                maxa=max({a[i][j],a[j][n-i+1],a[n-j+1][i],a[n-i+1][n-j+1]});
                ans+=maxa*4-a[i][j]-a[j][n-i+1]-a[n-j+1][i]-a[n-i+1][n-j+1];
		}
	 }
        cout<<ans<<endl;
    }
    return 0;
}


```

---

## 作者：Natori (赞：1)

>[CF1881C Perfect Square](https://www.luogu.com.cn/problem/CF1881C)

英文题面的 $\LaTeX$ 炸了。。。

![](https://cdn.luogu.com.cn/upload/image_hosting/ewaowig5.png)

边写英语作文边打这场 CF，结果 A 题交了九发才过，然后 C 题看错题，心态直接炸掉力！写这篇题解纪念我逝去的 $66$ 分。

~~甚至第二天英语作文还要重写，真的输麻力~~

------------
考虑一张 $6\times6$ 网格图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8smkyx0q.png)

用两条蓝线将整个网格图分成四块。由于保证 $n$ 是偶数，所以这样的线一定可以被画出来。

考察格子 $(3,2)$，发现它在顺时针旋转一次后会到格子 $(2,4)$，旋转两次后到达 $4,5$，旋转三次到达 $5,3$。显然可以将这四个格子分成两组，每组都关于中心点（也就是两条蓝线的交点）中心对称。

考虑枚举左上角这片区域的每一个点，这样可以覆盖到其他三片区域的每一个格子，且每组（四个对应的格子）之间互不影响。

对于左上角区域的一个格子 $(x,y)$，它经过一次旋转会到达 $(y,n+1-x)$ 处。这可以通过一组全等三角形证明：过坐标对应的格点向蓝线作垂线即可。同时可以通过中心对称求出任意一组格子的坐标。

然后考虑计算每组格子的贡献：求出四个格子中 ASCII 码最大的，然后加上与其它格子的差值即可。由于到 $\texttt{z}$ 后继续操作不会变成 $\texttt{a}$，所以只有这样做才能满足要求。~~赛时以为 z 可以变成 a，输麻力！~~

代码就不放了罢。

Bonus：如果 $\texttt{z}$ 能变成 $\texttt{a}$，并且 $n$ 再小一点，可能可以用类似 ABC320G 的做法。~~好好好，CF div3 C 上二分图匹配是吧~~

Update on 2023.11.7：关于 Bonus，wssb。

一个结论是：每组字符最后都会变成原来其中的一个字符。

因为如果变成原来四个字符之外的情况，相当于给它们都进行若干次操作，带来额外的开销。因此枚举目标是哪个字符，然后计算其它字符需要的操作次数，四种情况取 $\min$ 就行。

---

## 作者：yangmingshuo114514 (赞：1)

## 题意

给出一个由 $n\times n$ 个小写字母组成的矩阵，每次操作可以使一个单元的字母变为其在字母表里的下一个字母，特别地，z 的值不能变。求最少需要几次操作能使矩阵顺时针旋转 $90^\circ $ 后的矩阵和旋转前的矩阵相同。

## 思路

若定义矩阵左上角的点为 $(0,0)$，右下角的点为 $(n-1,n-1)$，一个原本在 $(i,j)$ 的字母顺时针旋转 $90^\circ $ 后在 $(j,n-i-1)$。一个点旋转 $4$ 次会回到原来的点。我们将旋转轨迹上的所有字母全变成在这 $4$ 个字母中最大的字母，此时操作数是最小的。由于一个点会在不同的轨迹中被重复计算 $4$ 次，最后答案也要 $\div 4 $。

## 代码

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int t,n,c;
string s[1005];
char x;
int main(){
	scanf("%d",&t);
	while(t--){
		c=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			cin>>s[i];
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				x=0;
				for(int k=0;k<4;k++){
					int t=i;
					i=j;
					j=n-t-1;
					x=max(x,s[i][j]);
				}//一次旋转求最大值
				for(int k=0;k<4;k++){
					int t=i;
					i=j;
					j=n-t-1;
					c+=x-s[i][j];
				}//二次旋转统计操作数
			}
		printf("%d\n",c/4);//去掉重复计算部分
	}
	return 0;
}

---

## 作者：Lvlinxi2010 (赞：0)

既然题目要求矩阵旋转后相同，那我们可以将矩阵分成相同的四块（题目保证 $n$ 是偶数）。

那我们研究在第一块的 $a_{i,j}(1 \le i,j\le n/2)$，它旋转后可以到达的对应点分别为 $a_{j,n-i+1}$，$a_{n-j+1,i}$，$a_{n-i+1,n-j+1}$。那我们要把这四个位置的字母变得相同，根据题目，我们只能把字母变成它的下一个字母，所以我们要找到四个位置中字母最大的那个，然后遍历第一块累加需要操作变成最大值的次数即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;

const int MAXN=1005;
char a[MAXN][MAXN];

int main(){
	int T;
	char maxx;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		FL(i,1,n){
			FL(j,1,n) scanf(" %c",&a[i][j]);
		}
		int ans=0;
		FL(i,1,n/2){
			FL(j,1,n/2){
				int maxx=max(a[i][j],max(a[j][n-i+1],max(a[n-j+1][i],a[n-i+1][n-j+1])));
				ans+=(maxx-a[i][j])+(maxx-a[j][n-i+1])+(maxx-a[n-j+1][i])+(maxx-a[n-i+1][n-j+1]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：lzj666_luogu (赞：0)

## 思路分析

这道题的难点主要是在将一个矩阵旋转 $90 \degree$ 以后的关系处理出来。

但是其实，我们可以按位置，一个一个进行枚举推测。

假设我们现在有一个矩阵：

$$
1 ⋅ ⋅ ⋅ ⋅ 2
$$

$$
\dots \dots
$$

$$
\dots \dots
$$

$$
4 ⋅ ⋅ ⋅ ⋅ 3
$$

那么我们就将 $4$ 移到 $1$，$1$ 移到 $2$，$2$ 移到 $3$，$3$ 移到 $4$。

然后依次往后顺延

$$
⋅ 1⋅ ⋅ ⋅ ⋅
$$

$$
⋅ ⋅ ⋅ ⋅ ⋅ 2
$$

$$
4 ⋅ ⋅ ⋅ ⋅ ⋅
$$

$$
⋅ ⋅ ⋅ ⋅ 3⋅
$$

接着将 $4$ 移到 $1$，$1$ 移到 $2$，$2$ 移到 $3$，$3$ 移到 $4$。

$$
\dots \dots
$$

如此往复，最终求出最后的矩阵。

所以可以通过转的方法，发现其实 $a_{i,j}$ 和 $a_{j,n-i+1}$ 是旋转后对应的，同理就可以得出最终 $a_{i,j},a_{j,n-i+1},a_{n-j+1,i},a_{n-i+1,n-j+1}$ 都是对应的。

所以就可以得出代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[1000+10][1000+10];
bool vis[1000+10][1000+10];
long long ans;
int main(){
	ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		ans=0;
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;++i) cin>>a[i]+1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(vis[i][j]) continue;
				vis[i][j]=vis[n-j+1][i]=vis[j][n-i+1]=vis[n-i+1][n-j+1]=1;
				int want=max({a[i][j],a[j][n-i+1],a[n-j+1][i],a[n-i+1][n-j+1]});
				for(char k:{a[i][j],a[j][n-i+1],a[n-j+1][i],a[n-i+1][n-j+1]}) ans+=want-k;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：paramecium_ (赞：0)

# 题目大意
给定一个 $n \times n$ 的矩阵，你可以进行若干次操作，每次操作可以将一个字母变成字母表序中下一个字母，问最少进行多少次操作可以使这个矩阵旋转 $90^\circ$ 后仍保持不变。
# 思路

要想使矩阵旋转 $90^\circ$ 后仍保持不变，我们必须使任意一点 $(i,j)$ ，所对应的 $(j,n-i-1)$，$ (n-j-1,i)$，$(n-i-1,n-j-1)$ 这三个点都相同，所以我们可以先取这四个点所对应值的字典序最大的字母，然后用得出的结果依次与四个点作差，最后累加起来就是这题的答案了。

# 时间复杂度

$O(n^2)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1005][1005];
int n;
signed main(){
	ios::sync_with_stdio(false);//关同步流，可省略
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		int ans=0;//注意清空 
		char s;
		cin>>n;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>s;
				a[i][j]=s-'a';//预处理 
			}
		}
		for(int i=0;i<n/2;i++){
			for(int j=0;j<n/2;j++){
				int maxi=max(max(a[i][j],a[j][n-i-1]),max(a[n-j-1][i],a[n-i-1][n-j-1]));//找四个数的最大值 
				ans=ans+((maxi*4)-(a[i][j]+a[j][n-i-1]+a[n-j-1][i]+a[n-i-1][n-j-1]));//作差 
			} 
		} 
		printf("%lld\n",ans);//多测不换行，爆零两行泪 
	} 
	return 0;
}


```

---

## 作者：Bc2_ChickenDreamer (赞：0)

# CF1881C Perfect Square 题解

## Problem Brief

给定一个 $n \times n$ 的矩阵，每次操作可以将一个字母变成下一个字母（如 $a \gets b$），求最小操作次数使得矩阵旋转 $90^\circ$ 仍保持不变。

## Sol

我们通过推理可以发现，旋转 $90^\circ$ 的 $4$ 个关键点为 $(i,\ i + j)$，$(i + j,\ n - i - 1)$，$(n - i - 1,\ n - i - j - 1)$，$(n - i - j - 1,\ i)$。**注意，此处 $i, j$ 从 $0$ 开始。**

所以，我们套一个两层循环，$i$ 的范围为 $[0, n \div 2 - 1]$，$j$ 的范围为 $[0, n - 2i - 1 - 1]$。设四个关键点为 $a, b, c, d$，答案加上这个点的操作次数，即为 $\max(a, b, c, d) - a + \max(a, b, c, d)  - b + \max(a, b, c, d)  - c + \max(a, b, c, d)  - d$。

循环完后即可得到答案。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

using ll = long long;

#define mtest for (cin >> t; t; -- t)

const int kMaxN = 1010, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

int n, a, b, c, d, ans = 0;
string s[kMaxN];
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  mtest { // 多组数据
    ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++ i) { // 输入
      cin >> s[i];
    }
    for (int i = 0; i < (n >> 1); ++ i) { 
      for (int j = 0, maxa; j < n - (i << 1) - 1; ++ j) {
        a = s[i][i + j], b = s[i + j][n - i - 1], c = s[n - i - 1][n - i - j - 1], d = s[n - i - j - 1][i]; // 将 4 个关键点赋值给 a, b, c, d
        maxa = max(a, max(b, max(c, d))); // 取 max
        ans += maxa - a, ans += maxa - b, ans += maxa - c, ans += maxa - d; // 更新答案
      }
    }
    cout << ans << '\n'; // 输出
  }
  return 0;
}
```

---

## 作者：huangmingyi (赞：0)

### 题目简化
给你一个 $n \times n$ 的矩阵你要使矩阵怎么转都能与原来一样，问操作次数。
### 题目分析
1. 要使矩阵怎么转都能与原来一样，那每个点的其他三个对应点一致。我们要要将这四个点变为相同的，则变成的一定是这四个点中字母最大的一个字符，那操作次数就是：

```
cnt+=max(a[i][j],max(a[n-j+1][i],max(a[j][n-i+1],a[n-i+1][n-j+1])))*4-(a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1])
```

那么可以每个点都判一次。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,a[N][N];//T组数据，b[N][N]来存这张表。 
signed main(){
	for(cin>>t;t;t--){
		int n,cnt=0;//一定要清零（我不会告诉你我前面调三小时才发现了是没清零） 
		cin>>n; 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				char c;
				cin>>c;//没啥好讲的 
				a[i][j]=c-'a';//应该都懂吧（就是变数字） 
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int maxn=max(a[i][j]/*自己*/,max(a[n-j+1][i]/*对应点1*/,max(a[j][n-i+1]/*对应点2*/,a[n-i+1][n-j+1]/*对应点3*/)));/*取最大字符的值*/
				int num=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];
				cnt+=maxn*4-num;//操作次数累加
			}
		}
		cout<<cnt<<"\n";//没啥好讲的
	}
	return 0;
}
```

可会 WA，原因可想而知。会重复计算，结果要除以四。其实还有一个办法，就是右半边和下半边不计算。就是直到 $n \div 2$。
## 注意统计的东西一定要清零！！！~~我不会告诉你我前面调三小时才发现了是没清零~~。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,a[N][N];//T组数据，b[N][N]来存这张表。 
signed main(){
	for(cin>>t;t;t--){
		int n,cnt=0;//一定要清零（我不会告诉你我前面调三小时才发现了是没清零） 
		cin>>n; 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				char c;
				cin>>c;//没啥好讲的 
				a[i][j]=c-'a';//应该都懂吧（就是变数字） 
			}
		}
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=n/2;j++){
				int maxn=max(a[i][j]/*自己*/,max(a[n-j+1][i]/*对应点1*/,max(a[j][n-i+1]/*对应点2*/,a[n-i+1][n-j+1]/*对应点3*/)));/*取最大字符的值*/
				int num=a[i][j]+a[n-j+1][i]+a[j][n-i+1]+a[n-i+1][n-j+1];
				cnt+=maxn*4-num;//操作次数累加
			}
		}
		cout<<cnt<<"\n";//没啥好讲的
	}
	return 0;
}
```

---

