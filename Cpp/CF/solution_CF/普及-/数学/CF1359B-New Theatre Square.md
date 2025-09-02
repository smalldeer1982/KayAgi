# New Theatre Square

## 题目描述

You might have remembered Theatre square from the [problem 1A](https://codeforces.com/problemset/problem/1/A). Now it's finally getting repaved.

The square still has a rectangular shape of $ n \times m $ meters. However, the picture is about to get more complicated now. Let $ a_{i,j} $ be the $ j $ -th square in the $ i $ -th row of the pavement.

You are given the picture of the squares:

- if $ a_{i,j} =  $ "\*", then the $ j $ -th square in the $ i $ -th row should be black;
- if $ a_{i,j} =  $ ".", then the $ j $ -th square in the $ i $ -th row should be white.

The black squares are paved already. You have to pave the white squares. There are two options for pavement tiles:

- $ 1 \times 1 $ tiles — each tile costs $ x $ burles and covers exactly $ 1 $ square;
- $ 1 \times 2 $ tiles — each tile costs $ y $ burles and covers exactly $ 2 $ adjacent squares of the same row. Note that you are not allowed to rotate these tiles or cut them into $ 1 \times 1 $ tiles.

You should cover all the white squares, no two tiles should overlap and no black squares should be covered by tiles.

What is the smallest total price of the tiles needed to cover all the white squares?

## 说明/提示

In the first testcase you are required to use a single $ 1 \times 1 $ tile, even though $ 1 \times 2 $ tile is cheaper. So the total price is $ 10 $ burles.

In the second testcase you can either use two $ 1 \times 1 $ tiles and spend $ 20 $ burles or use a single $ 1 \times 2 $ tile and spend $ 1 $ burle. The second option is cheaper, thus the answer is $ 1 $ .

The third testcase shows that you can't rotate $ 1 \times 2 $ tiles. You still have to use two $ 1 \times 1 $ tiles for the total price of $ 20 $ .

In the fourth testcase the cheapest way is to use $ 1 \times 1 $ tiles everywhere. The total cost is $ 6 \cdot 3 = 18 $ .

## 样例 #1

### 输入

```
4
1 1 10 1
.
1 2 10 1
..
2 1 10 1
.
.
3 3 3 7
..*
*..
.*.```

### 输出

```
10
1
20
18```

# 题解

## 作者：伟大的王夫子 (赞：3)

dp 水题一道。

首先，我们明显可以将网格分成 $n$ 行，每一行分别进行处理，然后相加答案。令 $f_i$ 表示当前行前 $i$ 列所需最小花费。

我们用字符串 $a$ 来存储当前行的黑白格子的情况。转移一共有三种情况。

1. 当 $a_i$ 为黑格子时，$f_i = f_{i-1}$
1. 当 $a_i$ 为白格子时，$f_i = \min(f_i,f_{i-1}+x)$
1. 当 $a_i$ 与 $a_{i-1}$ 都为白格子时，$f_i=\min(f_i,f_{i-2}+y)$

注意，以上三种转移互相独立，互不影响。（也就是说，一个状态 $f_i$ 很有可能被更新多次。）

注意每次 dp 时要给 $f$ 数组赋一个很大的初值。

~~这样就可以避免贪心想不出来并且写起来麻烦的烦恼了。~~

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
int n, m, f[1005], x, y, ans;
char a[1005];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		scanf("%d%d%d%d", &n, &m, &x, &y);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", a + 1);
			f[0] = 0, f[1] = a[1] == '.' ? x : 0;
			for (int j = 2; j <= m; ++j) {
				f[j] = 0x3f3f3f3f;
				if (a[j] == '*') f[j] = f[j - 1];
				if (a[j] == '.') f[j] = min(f[j], f[j - 1] + x);
				if (a[j] == '.' && a[j - 1] == '.') f[j] = min(f[j], f[j - 2] + y);
			}
			ans += f[m];
		}
		printf("%d\n", ans);
	}
}
```

---

## 作者：江户川·萝卜 (赞：3)

## 题解 [题解 CF1359B 【New Theatre Square】](https://www.luogu.com.cn/problem/CF1359B)

[博客食用更佳](https://www.luogu.com.cn/blog/258085/solution-cf1359b)

补充：这里1*2的砖必须横向放置。

------
因为两个1×1的砖可以拼成1×2的砖，所以分两种情况：

$1.\ 2x\le y$

$2.\ 2x>y$

第一种情况就只摆1×1的砖就行了。

第二种情况对于每一行从左往右判断，如果有连续的 `.` 则 $\text{lcnt}++$，如果是个 `*` 则更新 $\text{xcnt,\ ycnt}$，并将 $\text{lcnt}$ 清零。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,n,m,x,y,xcnt,ycnt;//xcnt, ycnt分别是1*1、1*2需要摆的瓷砖个数
    char c;
    cin>>t;
    while(t--){
        cin>>n>>m>>x>>y;
        xcnt=ycnt=0;
        if(x*2<=y){
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++){
                    cin>>c;
                    if(c=='.') xcnt++;
                }
            cout<<xcnt*x<<endl;
        }
        else{
            int lcnt=0;//存储连续'.'个数
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    cin>>c;
                    if(c=='.') lcnt++;
                    else ycnt+=lcnt/2,xcnt+=lcnt%2,lcnt=0;
                }
                ycnt+=lcnt/2,xcnt+=lcnt%2,lcnt=0;
            }
            cout<<xcnt*x+ycnt*y<<endl;
        }
    }
}
```

---

## 作者：Pethly_Cat (赞：1)

**题意补充：1×2  的瓷砖只能横着放**

线性 dp 练手题。

定义 $f_{i,j}$ 表示第 $i$ 行，前 $j$ 列的最小花费，显然答案就是 $\sum_{i=1}^nf_{i,m}$ 。

由题面知，我们的状态有以下两种情况：

- 当前格与前一格合起来放一块 $1×2$  的瓷砖：$f_{i,j}=f_{i,j-2}+y$

- 当前格放一块 $1×1$  的瓷砖：$f_{i,j}=f_{i,j-1}+x$

综上所述，$f_{i,j}=\min{(f_{i,j-2}+y,f_{i,j-1}+x)}$

另外有一点要注意的是，若之前一格为黑色或 $j=1$，则必须跳过第一种情况；若当前一个为黑色，则显然 $f_{i,j}=f_{i,j-1}$。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,f[105][1005];
 //P.S:由于每一行互不影响，所以此处 f 数组可压成一维
char a[105][1005];
int main(){
	int t; cin>>t;
	while(t--){
		cin>>n>>m>>x>>y;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(a[i][j]=='*'){
					f[i][j]=f[i][j-1];
					continue;
				}//转移方程
				f[i][j]=2e9;
				if(j>1&&a[i][j-1]!='*') f[i][j]=f[i][j-2]+y;
				f[i][j]=min(f[i][j],f[i][j-1]+x);
			}
		int cnt=0;//统计结果
		for(int i=1;i<=n;i++)
			cnt+=f[i][m];
		cout<<cnt<<endl;
	}
	return 0;
}
```


---

## 作者：CSP_Sept (赞：1)

容易看出有两种铺砖方法：

- 全铺 $1\times 1$ 的砖。
- 尽量多铺 $1\times 2$ 的砖。

对于方法 1，解释略，对于方法 2：

处理每一行矩阵，用 $lian$ 实时更新连着的 `.` 个数。当出现 `*` 时处理剩下的 $lian$ 再清零。当 $lian=2$ 时答案加上 $y$ 再将 $lian$ 清零。

注意开大数组。

代码：

```cpp
#include <cstdio>

using namespace std;
#define int long long
int t;
int n,m,x,y;
char s[1010];
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld%lld%lld",&n,&m,&x,&y);
        int ans=0,ans2=0;//ans 指方法 2, ans2 指方法 1
        for(int i=0;i<n;i++){
            scanf("%s",s);
            int lian=0;
            for(int j=0;j<m;j++){
                if(s[j]=='.'){lian++;ans2+=x;}
                if(lian==2){ans+=y;lian=0;}
                if(s[j]=='*'){
                    if(lian==1){
                        ans+=x;
                    }
                    lian=0;
                }
            }
            if(lian==1) ans+=x;
        }
        printf("%lld\n",ans<ans2?ans:ans2);
    }
    return 0;
}
```

---

## 作者：Werner_Yin (赞：1)

# 题意
有一个 $n×m$ 的广场，其中一部分要铺地砖，地砖有两种，$ 1 × 1$ 和 $1×2$ 的，后者只能横着铺，其中，$ 1 × 1$的单价为$ x$ ,$ 1 × 2$ 的单价为 $y$ , 输入这个广场，"."表示要铺地砖，求最少花费。注意，地砖不可重合，也不可覆盖在已铺地砖区域。
# 思路
这显然是贪心，分别计算全铺 $ 1 × 1$ 的方案价钱和尽量多铺 $ 1 ×  2$ 的方案价钱，最后将最小的输出，因为只能横铺，方向固定，所以十分简单。
# 代码 $\downarrow$ 
具体细节见注释
```cpp
#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=(a);i<(b);i++)
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define floor Fl //好像floor是关键字？于是我宏定义了一下
#define lol long long
#define re read()
using namespace std;
const int MAXN=1e3+10;
int read(){
	#define ge getchar()
	int x=0,sgn=1;char ch=ge;
	for(;!isdigit(ch);ch=ge)if(ch=='-')sgn=-1;
	for(;isdigit(ch);ch=ge)x=(x<<1)+(x<<3)+(ch^48);
	return x*sgn;
}
int T,n,m,x,y;
int floor[MAXN][MAXN];
int main (){
	T=re;
	while(T--){
		n=re;m=re;x=re;y=re;int tot1=0,tot2=0;
		_rep(i,1,n){
			_rep(j,1,m){
				char ch=ge;
				while(ch!='.'&&ch!='*')ch=ge;
				if(ch=='.'){
					floor[i][j]=1;
					tot1++;
                    //tot1表示除了被铺1*2的，可铺多少1*1的地砖
					if(floor[i][j-1]&&floor[i][j])floor[i][j-1]=0,floor[i][j]=0,tot1-=2,tot2++;
                    //tot2表示可以最多铺多少1*2 的地砖
				}
				else floor[i][j]=0;
			}
		}
		lol ans1=tot1*x+tot2*y,ans2=tot1*x+tot2*2*x;
		//计算方案，lol:long long
        printf("%lld\n",min(ans1,ans2));
	}
	return 0;
}
```


---

## 作者：zjr0330 (赞：0)

看到好多大佬用的是 DP，~~可我这个蒟蒻不会~~，便写了篇模拟。

首先，我们看到它只有两种情况：

- 有 $1\times1$ 的砖块，需要 $x$ 元。
- 有 $1\times2$ 的砖块，需要 $y$ 元。（注意 $1\times2$ 的砖块要横着放）

然后因为没有竖着放的砖块，所以我们可以分行判断。

在分行判断时，还要先判断是那个跟实惠：

- 如果 $1\times1$ 的砖块的 $2$ 倍 $\le1\times2$ 的砖块，那么我们就只需判断有多少个砖块，再乘上 $x$；
- 如果上面的条件不成立，我们就判断是否有两个连起来的，如果有，将他们打上记号，并将 $ans$ 加上 $y$ 即可。

具体看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;    //有多少组数据 
	cin >> t;
	while (t--) {
		int a, b, c, d, ans = 0;    //a为行数,b为列数,c为1*1的砖块所要的钱,d为1*2的砖块的钱,ans为总钱数。 
		cin >> a >> b >> c >> d;
		char n[b + 1];
		while (a--) {    //有几行，每行分行判断 
			for (int i = 0; i < b; i++)cin >> n[i];    //输入一行的黑白砖块 
			if (c * 2 <= d) {    //如果1*1的砖块的两倍比1*2的砖块所用的价格少，就用1*1的 
				for (int i = 0; i < b; i++) {
					if (n[i] == '.')ans += c;    //再循环里就加上 
				}
			} else {    //否则用1*2的 
				for (int i = 0; i < b; i++) {
					if (i + 1 < b) {
						if (n[i] == '.' && n[i + 1] == '.')
							n[i] = '*', n[i + 1] = '*', ans += d;    //注意打记号 
						else if (n[i] == '.')
							n[i] = '*', ans += c;
					} else {
						if (n[i] == '.')ans += c;    //最后一个砖块的特判 
					}
				}
			}
		}
		cout << ans << endl;    //输出 
	}
	return 0;
}
```


---

## 作者：haokee (赞：0)

### 补充题目

- 对于 $1\times 2$ 的瓷砖，你不可以竖着放（即 $2\times 1$ 的形式）；
  
- 有可能全部铺 $1\times 1$ 的瓷砖会更优。
  

### 思路

看到不可以竖着放，我们会很自然地使用贪心。

对于每一行，我们都单独处理。每两个相邻的字符 `.`，我们都可以使用 $1\times 2$ 或者是 $1\times 1$ 的瓷砖来填充，取 $\min$ 值即可。如果只剩下了一个 `.`，我们就使用 $1\times 1$ 的瓷砖。

### 贪心正确性判断

- 对于偶数个连续的 `.`，我们可以全部分成一节节的两个字符的组合，取 $\min$ 值；
  
- 对于奇数个连续的 `.`，我们可以拆分成偶数个连续的 `.` 加上一个 `.`（$1\times 1$）。
  

因此这个贪心完全正确。

### 代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int t, n, m, x, y, ans;
string s;

int main() {
    for (cin >> t; t; --t) {
        cin >> n >> m >> x >> y, ans = 0;
        for (int i = 1; i <= n; ++i) {  // 将矩阵分行处理
            cin >> s, s += ' ';  // 尾随空格，防止当i=m-1的时候i+1越界
            for (int i = 0; i < s.size(); ++i) {
                bool o = s[i] == '.' && s[i + 1] == '.'; // 判断是否能铺1*2的瓷砖
                if (o) { // 如果可以
                    s[i] = s[i + 1] = '*' /*不管怎么样，最后都会被铺满*/, 
                    ans += min(2 * x, y); // 只需取1*1和1*2的最小值
                } else if (s[i] == '.') {
                    s[i] = '*', ans += x; // 不行的话就直接铺1*1的瓷砖
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}  
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
翻译的意思并不完整，原意还应加上这句话：$1 \times 2$ 的瓷砖只能横着放。  

观察题目，不难得出题目的意思为覆盖所有白色格子的最小代价，我们可以分为两种情况讨论：  

+ $2x \leq y$，所有白色格子都用 $1 \times 1$ 的瓷砖。

+ $2x>y$，在同一行且连续的白色格子用 $1 \times 2$ 的瓷砖，其余白色格子都用 $1 \times 1$ 的瓷砖。

## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x,y,sum,cnt,s1,s2;
char ch[105][1005]; 
int main(){
	cin>>t;
	while(t--){
		sum=0;
		cin>>n>>m>>x>>y;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>ch[i][j];
				if(ch[i][j]=='.'){
					sum++;
				}
			}
		}
		if(2*x<=y){
			cout<<sum*x<<endl;
			continue;
		}
		s1=0;
		s2=0;
		cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(ch[i][j]=='.'){
					cnt++;
				}
				else{
					s1+=cnt/2;
					s2+=cnt%2;
					cnt=0;
				}
			}
			s1+=cnt/2;
			s2+=cnt%2;
			cnt=0;
		}
		cout<<s1*y+s2*x<<endl;
	}
	return 0;
}
```


---

## 作者：跳跳谷hj (赞：0)

[配合博客食用更佳](https://www.luogu.com.cn/blog/tiaotiaoguhj/solution-cf1359b)

早上测试时刚好做到这题，写个题解加深印象

补充：$1*2$ 的格子必须横向放置

由于两个 $1*1$ 的砖也可以拼成一个 $1*2$ 的砖，所以我们用一个变量 flag 来记录两个 $1*1$ 的砖的价格是否比一块 $1*2$ 的砖的价格要便宜，如果是， $y=2*x$ ，同时，因为每一块砖都必须横向放置，所以可以一行一行地扫描，用一个变量 js 来记录有几个点没铺砖，当 $js = 2$ 时， $ans\gets ans+y$。

因为一块地方只有两种状态，所以，我们可以用一个 bool 数组来记录这块砖的状态，在输入完毕以后 $m\gets m+1$ ，将每一行第 $m$ 行的状态设为黑砖以方便处理。
在处理时，只要有连续两个的砖 $ans\gets ans+y$ ，遇到黑砖以后，由于连续两个的白砖已经被处理了，所以只用 $ans\gets ans+x$ 。   

附上 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,ans,js;
bool blk[110][1010],flag;
void runi(int a,int b){
	for(int i=1;i<=n;i++){
		js=0;
		for(int j=1;j<=m;j++){
			if(!blk[i][j])js++;
			if(js==2){
				ans+=b;
				js=0;
			}if(blk[i][j]){
				ans+=js*x;
				js=0;
			}
		}
	}
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
    	memset(blk,0,sizeof(blk));
    	ans=0;
        scanf("%d%d%d%d",&n,&m,&x,&y);
        flag=0;
        if(2*x<=y)flag=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char ch;
                cin>>ch;
                if(ch=='*')blk[i][j]=1;
            }
	    }m++;for(int i=1;i<=n;i++)blk[i][m]=1;
	    if(flag)runi(x,2*x);
        else runi(x,y);
	    printf("%d\n",ans);
    }return 0;
}

```



---

## 作者：liuyongle (赞：0)

#### 思路分析

注意到行可以完全彼此分开地求解。每个图块占用一个或两个正方形，但始终位于同一行。

我们看一下单行。点字符序列由一些星号分隔，这些序列中的每一个都可以独立于其他序列求解。

因此，我们得到了这些 $1 \times k$ 的空正方形，它们在求解时可以总计为整个答案。

有两种情况，取决于 $1 \times 2$ 是否比两个 $1 \times 1$ 瓷砖便宜。

如果是这样，那么我们想尽可能多地使用 $1 \times 2$ 瓦片。因此给定 $k$，我们可以放置 $\lfloor \dfrac{k}{2} \rfloor$ 个 $1 \times 2$ 瓦片，并用 $1 \times 1$ 瓦片覆盖其余的 $k - 2 \cdot \lfloor \dfrac{k}{2} \rfloor$ 个正方形。

如果是另一种情况，那么我们考虑用 $1 \times 1$ 的瓷砖覆盖所有面积，而不是 $1 \times 2$ 的瓷砖。因此所有 $k$ 应为 $1 \times 1$。

以 $y$ 和 $2 \cdot x$ 的最小值更新 $1 \times 2$ 瓷砖的价格。如果 $1 \times 2$ 的瓷砖不比两个 $1 \times 1$ 的瓷砖便宜，第一种算法将产生与第二种算法完全相同的结果。

时间复杂度为 $O(n \cdot m)$。

代码：

```python
t = int(input())
for _ in range(t):
	n, m, x, y = map(int, input().split())
	ans = 0
	y = min(y, 2 * x)
	for __ in range(n):
		s = input()
		i = 0
		while i < m:
			if s[i] == '*':
				i += 1
				continue
			j = i
			while j + 1 < m and s[j + 1] == '.':
				j += 1
			l = j - i + 1
			ans += l % 2 * x + l // 2 * y
			i = j + 1
	print(ans)
```

---

