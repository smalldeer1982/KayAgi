# [ABC357C] Sierpinski carpet

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_c

非負整数 $ K $ に対して、以下のようにレベル $ K $ のカーペットを定義します。

- レベル $ 0 $ のカーペットは黒いマス $ 1 $ 個のみからなる $ 1\times\ 1 $ のグリッドである。
- $ K\ >\ 0 $ のとき、レベル $ K $ のカーペットは $ 3^K\times\ 3^K $ のグリッドである。 このグリッドを $ 3^{K-1}\times\ 3^{K-1} $ のブロック $ 9 $ 個に分割したとき、
  - 中央のブロックはすべて白いマスからなる。
  - 他の $ 8 $ 個のブロックは、レベル $ (K-1) $ のカーペットである。
 
非負整数 $ N $ が与えられます。  
 レベル $ N $ のカーペットを出力の形式に従って出力してください。

## 说明/提示

### 制約

- $ 0\leq\ N\ \leq\ 6 $
- $ N $ は整数
 
### Sample Explanation 1

レベル $ 1 $ のカーペットは次のような $ 3\times\ 3 $ のグリッドです。 !\[\](https://img.atcoder.jp/abc357/78b18b1b75ea7862c1c216499221b9e8.png) これを出力形式にしたがって出力すると出力例のようになります。

### Sample Explanation 2

レベル $ 2 $ のカーペットは $ 9\times\ 9 $ のグリッドとなります。

## 样例 #1

### 输入

```
1```

### 输出

```
###
#.#
###```

## 样例 #2

### 输入

```
2```

### 输出

```
#########
#.##.##.#
#########
###...###
#.#...#.#
###...###
#########
#.##.##.#
#########```

# 题解

## 作者：LuukLuuk (赞：5)

# 题解：AT_abc357_c [ABC357C] Sierpinski carpet

### 题目大意

要求你输出一个 $3N \times 3N$ 的矩阵，正中心有一个由字符 `.` 组成的 $N \times N$ 矩阵，其他地方递归填入 $N \times N,\frac{N}{3}\times \frac{N}{3},...,1 \times 1$ 的矩阵，当矩阵大小为 $1 \times 1$，无中空部分。

例如 $N=3$ 时，矩阵就是这样：（直接贴的话太大了）

![](https://cdn.luogu.com.cn/upload/image_hosting/1g7xoj5e.png)

另外，$1 \le N \le 6$。

---
### 题解

看到这个数据范围，硬算就是了，从 $3N \times 3N$ 的矩阵开始递归，每次标记中间空的部分，不管实心部分，四周递归处理直到矩阵大小为 $1 \times 1$。

不多说，看代码吧：
```

#include <cmath>
#include <cstdio>
using namespace std;

int mp[10010][10010];//数组开到3^6+1
int n;

void dfs(int a, int b, int k) {
	//a,b表示起始位置坐标，k表示现在第几轮，从N到0
	if (k == 0)	return ;
   	//为0时相当于1*1，没有中空部分
	int len = pow(3, k - 1);
   	//预处理长度（本来应该在外预处理，因为数据小，也就不怕了
	
	for (int i = a + len; i < a + 2 * len; ++i) {
		for (int j = b + len; j < b + 2 * len; ++j) {
			mp[i][j] = 1;
		}
	}
   	//将中部空心部分标记
	
	dfs(a, b, k - 1);
	dfs(a + len, b, k - 1);
	dfs(a + 2 * len, b, k - 1);
	//枚举第一列
    
	dfs(a, b + len, k - 1);
	dfs(a + 2 * len, b + len, k - 1);
	//第二列
    
	dfs(a, b + 2 * len, k - 1);
	dfs(a + len, b + 2 * len, k - 1);
	dfs(a + 2 * len, b + 2 * len, k - 1);
    //第三列
}

int main() {
	scanf("%d", &n);
	dfs(1, 1, n);//从1，1的位置开始，大小为3N*3N
	for (int i = 1; i <= pow(3, n); ++i) {
		for (int j = 1; j <= pow(3, n); ++j) {
			if (mp[i][j] == 1) {//如果标记输出空心
				printf(".");
			} else {//没有标记输出实心
				printf("#");
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：stripe_python (赞：3)

比较简单的一道小模拟。

题意是明显的递归定义，所以我们令 `fill(x, y, k)` 表示在 $(x,y)$ 为左上角的区域内填充 $k$ 级地毯。直接在八个小正方形内再次填充即可。边界是 $0$ 级地毯。

```cpp
#include <bits/stdc++.h>
using namespace std;

int x;
char s[2005][2005];

void fill(int x, int y, int k) {
	if (k == 0) return s[x][y] = 1, void();
	int t = k / 3;
	fill(x, y, t);
	fill(x + t, y, t);
	fill(x + t * 2, y, t);
	fill(x, y + t, t);
	fill(x, y + t * 2, t);
	fill(x + t, y + t * 2, t);
	fill(x + t * 2, y + t, t);
	fill(x + t * 2, y + t * 2, t);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> x;
	if (x == 0) return cout << "#", 0;
	int t = pow(3, x);
	fill(1, 1, t);
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= t; j++) cout << (s[i][j] == 0 ? '.' : '#');
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：XXh0919 (赞：2)

### 解法

比较简单的一道深搜题（题目中的极小数据就是告诉你要用深搜的）。如何进行深搜呢，因为它是一个 $3^N\times 3^N$ 的一个矩阵，所以搜索的上限就是 $3^N$。根据题意，我们要创造一个 $3^{k-1}\times 3^{k-1}$ 的矩阵，所以我们在进行深搜时递归到下一层的上限就是 $3^{k-1}$。当然我们还要进行计数，因为矩阵级别不可能为负，所以当级别减到 $0$ 时我们就要返回。

可以根据代码进行理解。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+15,M=1e3+15;

int n;
char C[M][M];

void dfs(int k,int x1,int y1,int xx,int yy){
	if(k==0){//到底了
		C[x1][y1]='#';//变成黑色
		return;
	}
	for(int i=x1;i<=xx;i+=pow(3,k-1)){
		for(int j=y1;j<=yy;j+=pow(3,k-1)){
			if(i!=x1+pow(3,k-1)||j!=y1+pow(3,k-1))
			   dfs(k-1,i,j,i+pow(3,k-1)-1,j+pow(3,k-1)-1);//k-1 就是一次计数
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	memset(C,'.',sizeof C);//先全部初始化成白色
	cin>>n;
	int m=pow(3,n);
	dfs(n,1,1,m,m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			cout<<C[i][j];
		}
		cout<<endl;	
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：1)

~~被降智了，赛时调了八十多分钟。~~

## 题意

定义 $K$ 级地毯，被分成 $9$ 块：中间块为白色，其他 $8$ 块为 $(K-1)$ 级地毯。

其中，$0$ 级地毯仅有 $1$ 个黑色格子。

输出 $N$ 级地毯。

## 做法

考虑递归，从第 $N$ 级地毯的中间块开始处理，每次转移到其他 $8$ 块地毯的中心。

那么移动距离是多少呢？

观察一下样例：

第 $1$ 次移动 $4$，第 $2$ 次移动 $1$，第 $3$ 次移动 $0$。

再推一下小数据，得出结论：每次移动 $3^k$ 格。

加的时候，在原数组的基础上乘上 $3^k$ 就好了。

## Code

[Link](https://atcoder.jp/contests/abc357/submissions/54374304)

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑递归处理，先将初始全部赋值为 `.`，故我们只需要处理 `#` 的情况。

我们可以记录以下状态 $n,x,y$ 表示以 $(x,y)$ 为左上角放置一个 $n$ 级地毯，令 $l=3^{n-1}$，故可以缩小为以下 $8$ 个子问题（只用考虑 `#`）：

- $(n-1,x,y),(n-1,x+l,y),(n-1,x+2l,y)$。

- $(n-1,x,y+l),(n-1,x+2l,y+l)$。

- $(n-1,x,y+2l),(n-1,x+l,y+2l),(n-1,x+2l,y+2l)$。

那么递归处理即可。

时间复杂度为 $O(3^{2n})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const int N = 1005;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
char ans[N][N];
void dfs(int n, int x, int y) {
    if (n == 0) {ans[x][y] = '#'; return ;}
    int l = pow(3, n - 1);
    dfs(n - 1, x, y);
    dfs(n - 1, x + l, y);
    dfs(n - 1, x + 2 * l, y);
    dfs(n - 1, x, y + l);
    dfs(n - 1, x + 2 * l, y + l);
    dfs(n - 1, x, y + 2 * l);
    dfs(n - 1, x + l, y + 2 * l);
    dfs(n - 1, x + 2 * l, y + 2 * l);
}
int main() {
    memset(ans, '.', sizeof(ans));
    int n;
    cin >> n;
    dfs(n, 1, 1);
    for (int i = 1; i <= pow(3, n); i ++) {
        for (int j = 1; j <= pow(3, n); j ++)   
            cout << ans[i][j];
        cout << endl;
    }  
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

这次的 C 题挺水的，感觉和[赦免战俘](https://www.luogu.com.cn/problem/P5461)比较像。

题意很明了：对于一个 $3^n \times 3^n$ 的矩阵，把它平分成九部分，中间的为空白，其他的继续分。很明显，这是一道分治题。这里面有明显的反复调用，所以使用递归实现。

对于每次递归，把中间部分设置为空，然后递归操作其他部分。借用赦免战俘的思路，每次递归存储左上角的坐标和管辖范围。复杂度 $O(3^n \times 3^n)$，轻松跑过。

[AC代码](https://atcoder.jp/contests/abc357/submissions/54376199)

---

## 作者：Harrylzh (赞：0)

```
#########
#.##.##.#
#########
###...###
#.#...#.#
###...###
#########
#.##.##.#
#########
```

以上为 $n=2$ 时的情况。把大正方形分成九个小正方形，可以得到：

- 第一排和第三排是三个小正方形，直接输出三个小正方形即可。

- 第二排左边和右边是两个小正方形，中间添点。

考虑输出方法：对于每一排，得到这排分别是大小 $3\times 3,3^2 \times 3^2 \ldots 3^k \times 3^k$ 的正方形中的第几排，再递归输出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long pth[100000+5];
long long b3[100000+5];
void print(long long cs)
{
	if(cs==0)
	{
		printf("#");
		return;
	}
	if(pth[n-cs]==1||pth[n-cs]==3)
	{
		print(cs-1);
		print(cs-1);
		print(cs-1);
	}
	else
	{
		print(cs-1);
		for(long long i=1;i<=b3[cs-1];i++)printf(".");
		print(cs-1);
	}
}
void meiju(long long step)
{
	if(step>n-1)
	{
		print(n-1);
		printf("\n");
		return;
	}
	for(long long i=1;i<=3;i++)
	{
		pth[step]=i;
		meiju(step+1);
	}
}
int main()
{
	b3[0]=1;
	for(long long i=1;i<=20;i++)
	{
		b3[i]=b3[i-1]*3;
	}
	scanf("%lld",&n);
	n++;
	meiju(1);
	printf("\n");
	return 0;
}
```

---

## 作者：Red_river (赞：0)

### 题目大意
给定一个非负整数 $K$ 定义了一个级别为 $K$ 的地毯。级别为0的地毯只有一个黑色的方块。

当 $K$ 大于零时，级别为 $K$ 的地毯是一个 $k^3 \times k^3$ 的网格。当将这个网格分成 $9 \times (k-1)^3 \times (k-1)^3$ 的块时，中间的块全部由白色方块组成，其他块为级别为 $K-1$ 的地毯。

给定一个非负整数 $N$ 输出级别为 $N$ 的地毯。

#### 一句话题意：给你一个 $N$ 求一个类似于递归的*地毯*。

### 思路

其实我们可以直接用循环来解决，首先求出 $3^k$ 再接着枚举每个位置，具体如何枚举，可参考代码及注释。

## code
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 2005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,jk,ans,sum,num,cnt,tot;
int dis[N][N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

int pow(int a, int i) {
	int sum=1;
	for(int j=1;j<=i;j++) sum*=a;
	return sum;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
	read(n);jk=pow(3,n);
	for(int i=1;i<=jk;i++)
		for(int j=1;j<=jk;j++)//枚举每个位置。
		{
			int f=0;
			for(int k=0;k<=6;k++)
			{
				if((i-1)/pow(3,k)%3==1&&(j-1)/pow(3,k)%3==1) f=1;//判断是否属于在k级状态下是否属于某个块的中心。
				if(f) break;
			}
			if(f) continue;
			dis[i][j]=true;
		}//输出。
	for(int i=1;i<=jk;i++)
	{
		for(int j=1;j<=jk;j++)
		{
			if(dis[i][j]) printf("#");
			else printf(".");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

模拟题。

考虑对于一个 $3^n\times 3^n$ 的矩阵，可以将其分割为 $9$ 个 $3^{n-1}\times 3^{n-1}$ 的矩阵，其中这 $9$ 个矩阵又构成了 $3\times 3$ 的大矩阵。

因此直接计算出 $9$ 个矩阵的左上角和右下角的坐标，然后除了中间的一个矩阵以外其他的矩阵继续递归处理即可。

时间复杂度为 $O(3^{2n})$。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
const int N = 1000100;
int a[N], n;
char s[5999][5999];
void dfs(int n, int x = 1, int y = 1) {
    if (n == 0) {
        s[x][y] = '#';
    } else {
        int key = 1;
        for (int i = 1; i < n; i++) {
            key = key * 3;
        }
        dfs(n - 1, x, y);
        dfs(n - 1, x + key, y);
        dfs(n - 1, x + key + key, y);
        dfs(n - 1, x, y + key);
        dfs(n - 1, x + key + key, y + key);
        dfs(n - 1, x, y + key + key);
        dfs(n - 1, x + key, y + key + key);
        dfs(n - 1, x + key + key, y + key + key);
    }
}
signed main() {
    cin >> n;
    if (!n) {
        cout << "#\n";
    } else {
        int key = 1;
        for (int i = 0; i < n; i++) {
            key *= 3;
        }
        for (int i = 1; i <= key; i++) {
            for (int j = 1; j <= key; j++) {
                s[i][j] = '.';
            }
        }
        dfs(n);
        for (int i = 1; i <= key; i++, cout << '\n') {
            for (int j = 1; j <= key; j++) {
                cout << s[i][j];
            }
        }
    }
}

```

---

