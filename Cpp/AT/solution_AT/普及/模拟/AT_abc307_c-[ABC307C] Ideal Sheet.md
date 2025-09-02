# [ABC307C] Ideal Sheet

## 题目描述

高桥有两张由方格组成的薄片，每个方格可能是透明的或黑色的。第一张的高 $H_A$ 宽 $W_A$ 个格子, 第二张高 $H_B$ 宽 $W_B$ 个格子。现在高桥将它们通过平移重叠在一起（不能旋转翻转），相对位置任意，想要得到图形 $X$ (高宽$H_X$,$W_X$)，请输出是否可能。用`.`表示透明格子，`#`表示黑色格子。

## 说明/提示

$1\leq$ 所有薄片高、宽 $\leq 10$ 
### 样例解释
Sample Explanation $2$ 
不能旋转薄片，因此不能得到 $X$ 。

## 样例 #1

### 输入

```
3 5
#.#..
.....
.#...
2 2
#.
.#
5 3
...
#.#
.#.
.#.
...```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
#.
.#
2 2
#.
.#
2 2
##
##```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1
#
1 2
##
1 1
#```

### 输出

```
No```

## 样例 #4

### 输入

```
3 3
###
...
...
3 3
#..
#..
#..
3 3
..#
..#
###```

### 输出

```
Yes```

# 题解

## 作者：xht (赞：6)

主要思路就是枚举两张图的相对位置，然后合并起来。

Trick 1：转化为坐标，这样就只是在数上加减，也不用考虑数组负数下标的问题。

Trick 2：保证所有有效部分顶在最上和最左。

```cpp
int main() {
    auto in = [&]() {
        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        for (auto &a : s) cin >> a;
        int u = n, v = m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (s[i][j] == '#')
                    u = min(u, i), v = min(v, j);
        set<pi> st;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (s[i][j] == '#')
                    st.insert(mp(i - u, j - v));
        return st;
    };
    set<pi> sa = in(), sb = in(), sx = in();
    for (int dx = -10; dx <= 10; dx++)
        for (int dy = -10; dy <= 10; dy++) {
            set<pi> sy;
            for (auto o : sa)
                sy.insert(mp(o.fi - min(dx, 0), o.se - min(dy, 0)));
            for (auto o : sb)
                sy.insert(mp(o.fi + max(dx, 0), o.se + max(dy, 0)));
            if (sx == sy) return cout << "Yes" << endl, 0;
        }
    cout << "No" << endl;
	return 0;
}
```

---

## 作者：vectorxyz (赞：3)

一道大模拟。

#### 思路

首先，我们想要解决一个问题：我们设想一个最坏情况，如果第一个图形的最后一个点正好与第二个图形的第一个点重合，如下图，那么这个数组将会出现负数，所以我们可以先将他们整体位移一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/b56hby5k.png)

解决完这个问题后，我们要做的就是不断每举数组 $a$ 的 $1$ 和 $1$ 点的坐标，然后将后面的也填充进去，数组 $b$ 同理，再和 $c$ 比对一下，如果一样就退出，不一样继续找。

#### Code
[Link.](https://www.luogu.com.cn/record/137701089)

---

## 作者：hanyu0722 (赞：2)

### 题目链接    

[AT_abc307_c](https://www.luogu.com.cn/problem/AT_abc307_c)

### 题目思路

#### part 1 复杂度分析
首先看到题目说薄片的宽高都小于等于十，据此来思考正解代码的时间复杂度大致为多少。  
能分析出本题的时间复杂度中不太可能出现 $2^n$ 或 $n!$，因此看到最大范围为十，可以直接考虑打暴力。

#### part 2 我的思路

题目中说我们要把两张卡片通过平移重叠在一起，于是可以想到选择 A 卡片的某个坐标与 B 卡片的某个坐标重合，并生成一张新的卡片，再将这张卡片与 X 卡片进行比较。

#### part 3 该思路的问题

这个思路有一个hack from [here](https://www.luogu.com.cn/discuss/622747)  
具体来说，就是我们只考虑了将 A 放在 B 上或将 B 放在 A 上，没有考虑到它们之间含有空隙的情况

可以发现最终我们只是比较黑色格子，透明格子因为看不见所以是无效的。于是我们可以在 A 卡片周围加上一圈透明格，而不会对答案造成影响。

### 代码时间

[code](https://www.luogu.com.cn/paste/r1p47u4c)

[link](https://www.luogu.com.cn/record/200022197)

---

## 作者：c20231020 (赞：2)


> [Problem C is sh*t.](https://codeforc.es/blog/entry/117577?#comment-1040340)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc307_c)

[atcoder](https://atcoder.jp/contests/abc307/tasks/abc307_c)

### 题目大意

上方链接。

### 思路

固定 $A$，枚举 $B,X$ 的位置，暴力匹配、统计黑色块数量即可。

具体来说，为了防止坐标出现负数，假设有一个大的 $50 \times 50$ 的大纸，$A$ 固定在左上角坐标为 $(21,21)$ 的位置，然后枚举 $B$ 的左上角坐标（两维的范围都是 $[1,41]$），$X$ 同理。

时间复杂度 $O(41^4\cdot HW)$，但是~~仅仅~~跑了 368ms！

#### code（省略缺省源）
```cpp
int na,ma,nb,mb,nx,mx;
char a[20][20],b[20][20],x[20][20],w[60][60];
void solve(){
	cin>>na>>ma;
	For(i,1,na)cin>>(a[i]+1);
	cin>>nb>>mb;
	For(i,1,nb)cin>>(b[i]+1);
	cin>>nx>>mx;
	For(i,1,nx)cin>>(x[i]+1);
	For(ib,1,41){
		For(jb,1,41){//B 的位置
			int r=0;
			For(i,1,50)For(j,1,50)w[i][j]='.';
			For(i,1,na)For(j,1,ma)w[i+20][j+20]=a[i][j];//固定 A
			For(i,ib+1,ib+nb)For(j,jb+1,jb+mb){
				if(w[i][j]=='#')continue;
				w[i][j]=b[i-ib][j-jb];//与 B 求交
			}
			For(i,1,50)For(j,1,50)r+=w[i][j]=='#';
			For(ix,1,41){
				For(jx,1,41){//X 的位置
					int f=1,num=0;
					For(i,1,nx){
						For(j,1,mx){
							if(w[i+ix][j+jx]!=x[i][j]){
								f=0;//匹配
							}
							num+=w[i+ix][j+jx]=='#';
						}
					}
					if(f&&r==num){//注意判断黑色块是否用完
						cout<<"Yes\n";
						return;
					}
				}
			}
		}
	}
	cout<<"No\n";
	return;
}
```

---

## 作者：Lovely_Sun (赞：1)

首先，要切割的 $C$ 区域是可以固定的，因为它与 $X$ 能否得到无关。

因此，我们首先在网格 $C$ 中定义一个坐标系。设 $(0,0)$ 为要切割的 $(H_X\times W_X)$ 区域的左上角正方形，用 $(a,b)$ 表示下面的第 $a$ 行和右边的第 $b$ 列中的正方形。如果 $a$ 或 $b$ 为负，则分别表示上面的 $\lvert a\rvert$ 和左边的 $\lvert b\rvert$。在这里，我们切出由 $(i,j)$ 正方形组成的网格，这样 $0\leq i\leq a-1$ 和 $0\leq j\leq b-1$。设该区域为 $D$。

#### 解决方案 $1$

考虑粘贴网格 $A$ 的区域。网格 $A$ 包含一个黑色正方形，区域 $D$ 包含 $A$ 中的所有黑色正方形，因此要粘贴网格 $A$ 的区域和区域 $D$ 必须共享至少一个正方形。因此，将网格 $A$ 的左上角正方形粘贴到 $C$ 上的可能正方形是 $(i,j) (-H_A+1\leq i\leq H_X-1, -W_A+1\leq i\leq W_X-1)$。类似地，将网格 $B$ 的左上角正方形粘贴到网格 $C$ 上的可能正方形是 $(i,j) (-H_B+1\leq i\leq H_X-1, -W_B+1\leq i\leq W_X-1)$。



当每个网格的位置确定后，可以通过检查 $H_A\times W_A$ 和 $H_B\times W_B$ 网格中的所有黑色方块都粘贴到区域 $D$ 上，并且 $H_X\times W_X$ 网格与寻找的网格 $X$ 重合来检查问题语句中的两个条件是否满足。



粘贴 $A$ 和 $B$ 的位置有 $19\times 19$ 个候选位置，需要检查 $3\times(10\times 10)$ 个方格来检查条件，总共需要 $(19\times 19)^2\times 300$ 次操作，足够快，可以在限定时间内完成。这样，问题就解决了。



实现可以通过以下想法来简化（取决于方法）：



-在许多语言中，数组的索引是非负的，因此让截断区域的左上角为 $(10,10)$。

-为了使代码独立于网格的尺寸，扩展表 $A$，$B$ 和 $X$，使它们 $10\times 10$，必要时添加透明的正方形。



#### 解决方案 $2$



对于每一个表 $A$、$B$ 和 $X$，让我们称一个黑色方块为“好”，如果它属于黑色方块中最上面的行，如果它属于那一行中最左边的列。然后，当裁出的板材满足条件时，将板材 $A$ 或板材 $B$ 的好方块粘贴到板材 $X$ 的好方块上。由于为了匹配好的黑色方块而粘贴的位置是唯一确定的，因此检查它与网格 $A$ 匹配的情况以及与网格 $B$ 匹配的情况就足够了，同时强制所有位置候选粘贴其他网格。（在下面的示例代码中，为了实现目的，我们还定义了右下角的正方形也是好的。）



在这个解决方案中，执行 $2\times (19\times 19)\times 300$ 比较，速度更快。

---

## 作者：LHW_Cosset_Idiot (赞：1)

### 复述题意
题目的意思是，是否可以将两个薄片 $a$ 和 $b$ 合并到薄片 $x$ 上。通过枚举将薄片 $a$ 和 $b$ 移动到 $x$ 的不同位置，并检查合并后的结果是否等于原薄片 $x$ 。
### 简化题意
简化一下题目，可以理解为：两张幻灯片重叠，能否组成第三张的摸样。
### 分析做法
分析题目可以得出，这题可以用暴力！！！
复杂度分析可以 [看这](https://www.luogu.com.cn/article/1cojhrno)。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(int)(n); i++)
#define all(x)(x).begin(),(x).end()
using ll=long long;
struct Sheet{ //结构体，用于表示一个薄片
	int h,w;
	vector<string> s; //二维字符数组
	void input(){ //输入
		cin>>h>>w;
		s=vector<string>(h);
		rep(i,h) cin>>s[i];
	}
	void clear(){ //清空薄片内容，全部设置为'.'
		rep(i, h) rep(j, w) s[i][j]='.'; //遍历每个位置并清空
	}
	//尝试将薄片a复制到当前薄片的指定位置
	bool copy(Sheet a,int di,int dj){
		rep(i,a.h) rep(j,a.w){
			if(a.s[i][j]=='.'){
				continue; //如果当前字符是'.'，跳过
			}
			int ni=i+di,nj=j+dj; //计算复制位置
			if(ni<0 || h<=ni || nj<0 || w<=nj){
				return false; //越界则复制失败
			}
			s[ni][nj]=a.s[i][j]; //复制字符到新位置
		}
		return true; //复制成功
	}
};
int main()
{
	Sheet a,b,x;
	a.input(); //读取薄片a的内容
	b.input(); //读取薄片b的内容
	x.input(); //读取薄片x的内容
	//遍历薄片a和b可以放置的位置，尝试将它们合并到薄片x上
	for(int ai=-a.h; ai<x.h; ai++){
		for(int aj=-a.w; aj<x.w; aj++){
			for(int bi=-b.h; bi<x.h; bi++){
				for(int bj=-b.w; bj<x.w; bj++){
					Sheet y=x; //复制薄片x
					y.clear(); //清空薄片y
					//尝试将薄片a复制到位置(ai, aj)
					if(!y.copy(a, ai, aj)){
						continue; //如果复制失败，跳过
					}
					//尝试将薄片b复制到位置(bi, bj)
					if(!y.copy(b, bi, bj)){
						continue; //如果复制失败，跳过
					}
					//如果最终的薄片y和原始薄片x相同，说明可以合并成功
					if(x.s==y.s){
						cout<<"Yes"<<endl; //输出
						return 0;
					}
				}
			}
		}
	}
	cout<<"No"<<endl; //输出
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：1)

## 解题思路：
模拟题，步骤如下：

将矩阵 $X$ 与 $30\times30$ 单元格的 $(10,10)$ 粘贴到左上角。将图纸 $A$ 和图纸 $B$ 粘贴到不同的位置。粘贴的范围是左上角坐标的 $20\times20$。

粘贴图纸 $A$ 和 $B$：$(20\times20\times20\times20)$。

检查它是否与图纸 $X$ 的 $(30×30)$ 匹配。

将 $(10,10)$ 设置为左上角，并确认矩阵 $X$ 的范围。如果它们不匹配，则组合不可以。

如果矩阵 $X$ 的范围之外有井号，则此组合也不可以。

最后判断是否有可以的组合。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll n,m,nn,mm,nnn,mmm; 
bool flag;
int main(){
	cin>>n>>m;
	vector<string> a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	cin>>nn>>mm;
	vector<string> b(nn);
	for(int i=0;i<nn;i++)cin>>b[i];
	cin>>nnn>>mmm;
	vector<string> x(nnn);
	for(int i=0;i<nnn;i++)cin>>x[i];
	vector<vector<char>> s(30, vector<char>(30));
	for(int ia=0;ia<20;ia++){
		for(int ja=0;ja<20;ja++){
			for(int ib=0;ib<20;ib++){
				for(int jb=0;jb<20;jb++){
					for(int i=0;i<30;i++){
						for(int j=0;j<30;j++){
							s[i][j]='.';
						}
					}
					for(int i=0;i<n;i++){
						for(int j=0;j<m;j++){
							if(a[i][j]=='#'){
								s[ia+i][ja+j]='#';
							}
						}
					}
					for(int i=0;i<nn;i++){
						for(int j=0;j<mm;j++){
							if(b[i][j]=='#'){
								s[ib+i][jb+j]='#';
							}
						}
					}
					bool flagg=1;
					for(int i=0;i<30;i++){
						for(int j=0;j<30;j++){
							if((10<=i)&&(i<10+nnn)&&(10<=j)&&(j<10+mmm)){
								if(s[i][j]!=x[i-10][j-10])flagg=0;
							}
							else if(s[i][j]=='#')flagg=0;
						}
					}
					if(flagg)flag=1;
				}
			}
		}
	}
	if(flag)cout<<"Yes";
	else cout<<"No";
}

```

---

## 作者：wangchai2009 (赞：1)

### ABC307C Ideal Sheet

[Link](https://www.luogu.com.cn/problem/AT_abc307_c)

题意很简单，是一道简单的模拟题。

本题解侧重代码的实现。

#### 前置知识

1. C++ 中[基于范围的 for 循环](https://oiwiki.org/lang/new/#%E5%9F%BA%E4%BA%8E%E8%8C%83%E5%9B%B4%E7%9A%84-for-%E5%BE%AA%E7%8E%AF)。

2. C++ 中 [vector](https://oiwiki.org/lang/csl/sequence-container/#vector) 的使用，以及二维 vector 的读入与遍历。

3. C++ 中[引用](https://oiwiki.org/lang/reference/)的基本应用。

在了解这些知识后，我们尝试使用 vector 来读入一个 $n$ 行 $m$ 列的二维地图。

```cpp

int n, m;
scanf("%d%d", &n, &m);

vector <vector<char>> A(n);

for (auto &v : A)
{
    v.resize(m);
    for (auto &c : v)   scanf(" %c", &c);
}

```

可以将上述代码中容器 A 的定义理解为定义了 $n$ 个 vector 容器。在外层循环中每次取出一个 vector，并调整这个 vector 的大小，相当于遍历地图的每一行。然后在内层循环中每次取出一个 char 类型的元素读入。

在自定义函数中传递 vector 可以用引用。接下来我们来看具体实现。

#### 实现思路

首先观察到所有的薄片的长宽都很小，考虑创建一个 $30 \times 30$ 的空白地图 $C$，行列下标都从 $0$ 起始。我们将高桥最终想要的地图固定在地图中央，即图形 $X$ 的左上角位于 $C$ 的 $(10, 10)$ 处。

接着考虑枚举 $A$ 和 $B$ 薄片左上角在 $C$ 中的位置，最终判断是否合法即可。

读入时，由于三个薄片的读入格式相同，可以用一个 `read` 函数来减少码量，具体实现如下。

```cpp
void read(int &h, int &w, vector <vector <char>> &M)
{
	scanf("%d%d", &h, &w);
	M.resize(h);
	for (auto &s : M)
	{
		s.resize(w);
		for (auto &c : s)	scanf(" %c", &c);
	}
}
```

接着枚举 $A$ 和 $B$ 左上角在 $C$ 中的位置。在每次枚举时都要初始化 $C$，代码如下，其中 $N$ 为常量，代表 $C$ 的大小。

```cpp
void init(vector <vector <char>> &C)
{
	C.resize(N);
	for (auto &s : C)
	{
		s.resize(N);
		for (auto &c : s)	c = '.';
	}
}
```

再将 $A$ 和 $B$ 分别粘贴到 $C$ 中，可以写一个 `fill` 函数减少码量。其中 `p` 和 `q` 是要粘贴的小薄片左上角在 $C$ 中的位置。 

```cpp
void fill(int p, int q, vector <vector <char>> M, vector <vector <char>> &C)
{
	int h = M.size(), w = M[0].size();
	for (int i = p; i < p + h; i++)
		for (int j = q; j < q + w; j++)
		{
			if (C[i][j] == '#' && M[i - p][j - q] == '.')	continue;//当前粘贴的小方格是透明的且当前要粘贴的位置已经粘贴过黑色的格子了，如果再运行下面一行就会出错		
			C[i][j] = M[i - p][j - q];	
		}
}
```

最后再写 `check` 函数判断合法性即可。其中 $MID$ 是常量，代表高桥想要的地图左上角在 $C$ 中的位置。

```cpp
bool check(vector <vector <char>> X, vector <vector <char>> C)
{
	int h = X.size(), w = X[0].size();
	for (int i = MID; i < MID + h; i++)
		for (int j = MID; j < MID + w; j++)
		{
			if (X[i - MID][j - MID] != C[i][j])	return false;
			C[i][j] = '*';//修改 C 中黑色格子方便判断 A 和 B 中的黑格子是否用完
		}
	for (auto &s : C)
		for (auto &x : s)
			if (x == '#')
				return false;
	return true;
}
```

[完整代码](https://atcoder.jp/contests/abc307/submissions/46278430)。

---

## 作者：yuhong056 (赞：0)

# 题解：AT_abc307_c [ABC307C] Ideal Sheet
本题解提供一个较为好写的思路。
## 思路
明显，$N$ 只有 $10$，因此直接暴力。

我们可以枚举第一个薄片拼接左上点，以及第二个薄片拼接左上点。

但是，薄片有可能拼接到负数下标，会出现很多细节问题。

因此，我们可以让薄片坐标全部偏移 $10$，这样子就不会出现负数下标了。

具体实现可见代码注释。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;

int a[5][3 * MAXN + 2][3 * MAXN + 2];
// a[0] 代表薄片 1，a[1] 代表薄片 2，a[2] 代表要拼成的最终薄片，a[3] 代表临时拼接起来的薄片

void read(int o, int add) { // 读入薄片 o，有 add 的偏移量
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			a[o][i + add][j + add] = (c == '#');
		}
	}
}

void copy(int o, int px, int py) { // 将 o 薄片从左上角 (px, py) 复制到临时薄片 a[3]
	for (int i = 1; i <= MAXN; i++) {
		for (int j = 1; j <= MAXN; j++) {
			a[3][px + i][py + j] |= a[o][i][j];
		}
	}
}

void Clear() { // 清空临时薄片
	for (int i = 1; i <= 3 * MAXN; i++) {
		for (int j = 1; j <= 3 * MAXN; j++) {
			a[3][i][j] = 0;
		}
	}
}

bool Check() { // 判断临时薄片是否为要拼成的最终薄片
	for (int i = 1; i <= 3 * MAXN; i++) {
		for (int j = 1; j <= 3 * MAXN; j++) {
			if (a[2][i][j] != a[3][i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int main() {
	read(0, 0), read(1, 0), read(2, MAXN); // 输入薄片
	for (int ax = 1; ax <= 2 * MAXN; ax++) {
		for (int ay = 1; ay <= 2 * MAXN; ay++) {
			for (int bx = 1; bx <= 2 * MAXN; bx++) {
				for (int by = 1; by <= 2 * MAXN; by++) { // 枚举第一个薄片拼接左上点，以及第二个薄片拼接左上点
					Clear();
					copy(0, ax, ay), copy(1, bx, by); // 将两片薄片叠在临时薄片上
					if(Check()){
						cout << "Yes";
						return 0;
					}
				}
			}
		}
	}
	cout << "No";
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

又是赞美出题人的题。
### 思路
最大就 $10 \times 10$ 直接暴力。考虑相对位置，把 $a$ 放中间，这样最大就是 $50 \times 50$ 少一点，因为最大可用的就 $10 \times 10$，就是 $40 \times 40$ 左右。最后枚举 $b$ 就可以。

最后还要枚举 $x$ 然后计算总和。

模拟题细节看代码吧。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int na,nb,ma,mb,nx,mx;
char a[80][80],b[80][80],x[80][80],c[80][80];
signed main()
{
	cin>>na>>ma; for(int i=1;i<=na;i++) for(int j=1;j<=ma;j++) cin>>a[i][j];
	cin>>nb>>mb; for(int i=1;i<=nb;i++) for(int j=1;j<=mb;j++) cin>>b[i][j];
	cin>>nx>>mx; for(int i=1;i<=nx;i++) for(int j=1;j<=mx;j++) cin>>x[i][j];
	for(int ib=1;ib<=41;ib++)//枚举 b 左上角的位置
		for(int jb=1,r=0;jb<=41;jb++,r=0)
		{
			for(int i=0;i<=50;i++) for(int j=0;j<=50;j++) c[i][j]='.'; //先初始化
			for(int i=1;i<=na;i++) for(int j=1;j<=ma;j++) c[i+20][j+20]=a[i][j];//直接把 a 放在中间 
			for(int i=ib+1;i<=ib+nb;i++) for(int j=jb+1;j<=jb+mb;j++)
				c[i][j]=min(b[i-ib][j-jb],c[i][j]); //把 b 叠在上面
			for(int i=1;i<=51;i++) for(int j=1;j<=51;j++) r+=(c[i][j]=='#'?1:0);//在整个画布中统计 # 的数量
			for(int ix=1;ix<=41;ix++)
				for(int jx=1,f=1,num=0;jx<=41;jx++,f=1,num=0)
				{//枚举 x 的位置
					for(int i=1;i<=nx&&f!=0;i++) 
						for(int j=1;j<=mx&&f!=0;j++)
						{//计算当前区域下的 # 总和 和 是否对应
							if(c[i+ix][j+jx]!=x[i][j]) f=0;
							num+=(c[i+ix][j+jx]=='#'?1:0);
						}
					if(f&&num==r) 	return cout<<"Yes",0; //所有的 # 都要使用
				}
			
		}
	cout<<"No";
	return 0;
}
```
不得不膜拜楼上还是楼下结构体。

---

## 作者：guoxinda (赞：0)

## 简化题意
就是说给你两个薄片，能不能通过平移组成第三个薄片，并且涵盖了所有黑格（只要有一个黑格那么这个区域就是黑的）。
## 思路
暴力求解。发现不用枚举 $a,b$ 两个薄片的下标，只需要固定一个，再枚举另一个的下标即可。\
然后遍历数组看有几个黑格（因为有可能两个黑格重叠），再枚举薄片 $x$ 的位置能不能涵盖所有黑格且与这片区域形状相同。\
注意，只要有一个位置符合要求就行了。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100][100],b[100][100],c[100][100],f[100][100],n,m,x,y,q,w,sum;
char k,bl[100][100];
bool check(int x,int y,int ss){
	int s=0;
	for(int i=1;i<=q;i++){
		for(int j=1;j<=w;j++){
			if(c[i][j]!=f[i+x][j+y])return 0;
			if(bl[i+x][j+y]){
				s++;
			}
		} 
	}
	if(s==ss)return 1;//覆盖了所有黑格  
	return 0;
}
int main(){ 
	cin>>n>>m; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>k;
			if(k=='#')a[i][j]=1;
		}
	}
	cin>>x>>y; 
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			cin>>k;
			if(k=='#')b[i][j]=1;
		}
	}
	cin>>q>>w; 
	for(int i=1;i<=q;i++){
		for(int j=1;j<=w;j++){
			cin>>k;
			if(k=='#')c[i][j]=1;
		}
	}//输入 
	for(int i=1;i<=41;i++){
		for(int j=1;j<=41;j++){//模拟b[1,1]的位置 
			for(int ax=1;ax<=61;ax++){
				for(int ay=1;ay<=61;ay++){
					f[ax][ay]=0;
					bl[ax][ay]=0;
				}
			}
			sum=0;//初始化 
			for(int ax=1;ax<=n;ax++){
				for(int ay=1;ay<=m;ay++){
					if(a[ax][ay]){
						f[ax+20][ay+20]=1;//a的位置 
						if(!bl[ax+20][ay+20]){//标记
							bl[ax+20][ay+20]=1;
							sum++;
						}
					}
				}
			}
			for(int ax=1;ax<=x;ax++){
				for(int ay=1;ay<=y;ay++){
					if(b[ax][ay]){
						f[ax+i-1][ay+j-1]=1;//b[i][j]的位置，因为我的遍历是从一开始的，所以要-1 
						if(!bl[ax+i-1][ay+j-1]){//标记
							bl[ax+i-1][ay+j-1]=1;
							sum++;
						}
					}
				}
			}
			for(int ax=0;ax<=41-q;ax++){
				for(int ay=0;ay<=41-w;ay++){//图形X的起点 
					if(check(ax,ay,sum)){
						cout<<"Yes";
						return 0;//不用继续了 
					}
				}
			}
		}
	}
	cout<<"No";//不能实现
	return 0; 
} 
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc307_c)

这是一道比较简单的模拟题。

首先考虑最坏的情况：如果**第一个图形的最后一个点**和**第二个图形的第一个点**重合，那么这个数组就必定会有负数，所以要先把它们全部位移一下。然后，就要不断枚举 $a_1$ 和 $1$ 点的坐标，把后面的也填进去，数组 $b$ 也一样，最后再和数 $c$ 比对一下，一样就退出，输出 `YES`，不一样就继续找。如果到最后都没有找到一样的，就输出 `NO`。

一道模拟，自己写吧，不给代码了。

---

## 作者：syxmz (赞：0)

### 1 题目大意
问：一个矩阵可不可以通过其他两个矩阵的覆盖得到。
### 2 解法分析
首先考虑到数据范围是 $[1,10]$，可以暴力，因此此题解采用最暴力的方法。

$A$，$B$ 的存图可以简单的存，但是 $C$ 却需要向右平移 $10$ 再存入数组，因为在枚举 $A$ 与 $B$ 的位置时我们显然不想要下标变成负的。

接下来就是枚举所有的可能性，首先使用 $O(20^4)$ 的时间枚举所有的 $A$ 与 $B$ 的位置。
接着就是用 $O(3\times10^2)$ 暴力更新并判断合法性。

时间复杂度刚好压线，且在 AtCoder 评测机上跑出了 [109ms 的优异成绩](https://atcoder.jp/contests/abc307/submissions/42944912)。

这题无论从代码难度还是思维难度看上去都不是很难，看来 AtC 最难的还是阅读理解。
### 3 AC Code
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define fep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define N 37
using namespace std;

string s;
int ans[N][N];
int ha, wa, hb, wb, hc, wc;
int a[N][N], b[N][N], c[N][N];

int main() {
	scanf("%d%d", &ha, &wa);
	rep(i, 1, ha) {
		cin >> s;
		fep(j, 0, wa)
			a[i][j + 1] = (s[j] == '#');
	}
	scanf("%d%d", &hb, &wb);
	rep(i, 1, hb) {
		cin >> s;
		fep(j, 0, wb)
			b[i][j + 1] = (s[j] == '#');
	}
	scanf("%d%d", &hc, &wc);
	rep(i, 1, hc) {
		cin >> s;
		fep(j, 0, wc)
			c[10 + i][11 + j] = (s[j] == '#');
	}
	rep(i, 1, hc + 10)
		rep(j, 1, wc + 10)
			rep(k, 1, hc + 10)
				rep(l, 1, wc + 10) {
					memset(ans, 0, sizeof ans);
					rep(p, 1, ha)
						rep(q, 1, wa)
							if (a[p][q])
								ans[i + p - 1][j + q - 1] = 1;
					rep(p, 1, hb)
						rep(q, 1, wb)
							if (b[p][q])
								ans[k + p - 1][l + q - 1] = 1;
					int f = 1;
					rep(p, 1, 30)
						rep(q, 1, 30)
							if (ans[p][q] != c[p][q])
								f = 0;
					if (f)
						return puts("Yes"), 0;
			}
	puts("No");
	return 0;
}
```

---

