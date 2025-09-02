# Fractal

## 题目描述

**题目背景**

自从著名的柏林抽象主义者卡莱维奇听说分形后，他就把分形作为自己油画的主题。每天早上，他拿着一张绘图纸，开始制作他未来画布的模型。


给出染色正方形的边长n，并给出染色的方法，执行k次操作（即正方形图纸的边长为n^k），每次操作将图放大，按给出的方法将图涂黑，下一步再将图中的每块白色正方形部分按给出的方法染黑

## 样例 #1

### 输入

```
2 3
.*
..
```

### 输出

```
.*******
..******
.*.*****
....****
.***.***
..**..**
.*.*.*.*
........
```

## 样例 #2

### 输入

```
3 2
.*.
***
.*.
```

### 输出

```
.*.***.*.
*********
.*.***.*.
*********
*********
*********
.*.***.*.
*********
.*.***.*.
```

# 题解

## 作者：ahawzlc (赞：6)

思路：暴力模拟。

------

看到题解大多是从大到小分析位置输出答案，这里特别提供一种简洁易懂的暴力模拟涂色方法。

根据题目上的涂色方式，我们可以想到一种模拟：对于原图每一个白块，我们可以在新图上把它替换成单位正方形；对于原图每一个黑块，我们可以在新图上把它替换成 $ n \times n $ 的全黑正方形。

![1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF36B/e8422806af6330609da67545ef59f385e8f81169.png)

具体实现，我们需要开最多五层数组，每次从当前图向下一层图涂色时，注意当前色块放大后在新图的位置。具体来讲，对于原图的色块 $(i,j)$ ，当 n=2 时，它在新图中的位置是 $ (i\times 2-1,j\times 2-1)$~$ (i,j) $ 的正方形，当 n=3 时，它在新图中的位置是 $ (i\times 3-2,j\times 3-2)$~$ (i,j) $ 的正方形。

剩下的就没有什么技术含量了，具体见代码。

Code：

```c++
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
inline int read() {
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}
int n,k,m=1;
char ans[6][300][300];
int main() {
    freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	n=read(),k=read();
	for(int i=1; i<=n; i++) scanf("%s",ans[1][i]+1);
	for(int p=1; p<k; p++) {//涂色的层数，因为单位正方形是第一轮涂色，所以 <k 。
		m*=n;//m=n^p
		for(int i=1; i<=m; i++)
			for(int j=1; j<=m; j++) {
				if(ans[p][i][j]=='.') {
					if(n==2) {//对于 n=2 的情况暴力涂色。
						ans[p+1][i*n-1][j*n-1]=ans[1][1][1];
						ans[p+1][i*n][j*n-1]=ans[1][2][1];
						ans[p+1][i*n-1][j*n]=ans[1][1][2];
						ans[p+1][i*n][j*n]=ans[1][2][2];
					} else {//对于 n=3 的位置暴力涂色。
						ans[p+1][i*n-2][j*n-2]=ans[1][1][1];
						ans[p+1][i*n-1][j*n-2]=ans[1][2][1];
						ans[p+1][i*n][j*n-2]=ans[1][3][1];
						ans[p+1][i*n-2][j*n-1]=ans[1][1][2];
						ans[p+1][i*n-1][j*n-1]=ans[1][2][2];
						ans[p+1][i*n][j*n-1]=ans[1][3][2];
						ans[p+1][i*n-2][j*n]=ans[1][1][3];
						ans[p+1][i*n-1][j*n]=ans[1][2][3];
						ans[p+1][i*n][j*n]=ans[1][3][3];
					}
				} else {//全黑涂法
					if(n==2) {
						ans[p+1][i*n-1][j*n-1]='*';
						ans[p+1][i*n][j*n-1]='*';
						ans[p+1][i*n-1][j*n]='*';
						ans[p+1][i*n][j*n]='*';
					} else {
						ans[p+1][i*n-2][j*n-2]='*';
						ans[p+1][i*n-1][j*n-2]='*';
						ans[p+1][i*n][j*n-2]='*';
						ans[p+1][i*n-2][j*n-1]='*';
						ans[p+1][i*n-1][j*n-1]='*';
						ans[p+1][i*n][j*n-1]='*';
						ans[p+1][i*n-2][j*n]='*';
						ans[p+1][i*n-1][j*n]='*';
						ans[p+1][i*n][j*n]='*';
					}
				}
			}
	}
	for(int i=1; i<=m*n; i++) printf("%s\n",ans[k][i]+1);
	return 0;
}
```

---

## 作者：xiaozeyu (赞：6)

**我们可以直接开始在最后的画中填，而不是由原图慢慢画出结果**

**~~似乎也没什么太大区别？~~**

**这道题还有一个坑！！！！！**

**错了好几遍才发现要：：：**

freopen("input.txt","r",stdin);

freopen("output.txt","w",stdout);

上代码

------------

    
```
#include <bits/stdc++.h>
using namespace std;
char c[305][305],ans[305][305];//定义范围
int n,m;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);//别忘了！！！
	cin>>n>>m;//输入小画范围
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin>>c[i][j];//输入小的画
	int s=pow(n,m);//先求出最后大小
	for(int i=0;i<s;++i)
	{
		for(int j=0;j<s;++j)//循环整个大的画
		{
			int x=i;
			int y=j;//记录一下ij
			int cnt=0;//判断用的
			for(int k=0;k<m;++k)//小的范围
			{
				if (c[x%n][y%n]=='*')//小的中找
				{
					cnt=1;//是
					break;//返回
				}
				x/=n;
				y/=n;//进行减小
			}
			cout<<((cnt)?'*':'.');//通过cnt的值判断是哪个
		}
		cout<<endl;
	}
}
```


---

## 作者：jxbe6666 (赞：2)

看见别的题解的代码太过于复杂，我就自己来写了。  
这道题可以在原来给你的图上画，不用新开一个二维数组了，可能省了一些时间吧。

 ### 一定要加 $\text{freopen}$，否则就会全部 WA。
 
 AC Code：
 ```cpp
#include <bits/stdc++.h>
using namespace std;
string s1[305], ans[305];
int n, m;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
            cin >> s1[i];
    int s = pow(n, m);//先求出最后大小
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < s; ++j) //循环整个大的画
        {
            int x = i;
            int y = j;//记录一下i,j
            int cnt = 0;
            for (int k = 0; k < m; ++k)
            {
                if (s1[x % n][y % n] == '*') //小的中找*
                {
                    cnt = 1;
                    break;
                }
                x /= n;
                y /= n;
            }
            cout << ((cnt) ? '*' : '.'); //通过cnt的值判断是哪个
        }
        cout << '\n';
    }
}

```



---

## 作者：zhmzhuhanming (赞：1)

# [题目传送器](https://www.luogu.com.cn/problem/CF36B)

在前面几篇题解之后，再强调一遍：本题坑坑的地方是要加：

# freopen! freopen!! freopen!!!

幸运的是本人看到了，所以没有冤冤地 WA 掉 

好了，正式开始题解：

再次概括题目大意：给出一个 $ n * n $ 的矩阵，进行 $m$ （ 题目中是 $k$ ）次操作，每次操作将每个“ . ”换成输入的 $ n * n $ 矩阵，而 “ * ”则换成 $ n * n $ 的 星号 矩阵

提醒一下，还没操作时，矩阵相当于只是一个 $ 1 * 1 $ 的 “ . ”，一次操作后就变成了题目给出的矩阵，所以如果直接在题目给出矩阵进行操作的话，只要进行 $m-1$ 次就行了

具体解释请看代码注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char s[10][1000][1000];//题中说操作次数不大于5，本人就定义为第k次的矩阵为s[k][1~n][1~m]，k也可以特别小
int n,m;
signed main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//最后一遍提醒：freopen！！！
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>s[1][i][j];  //输入的是第一个矩阵，所以存储到s[1][i][j]
		}
	}
	for(int k=1;k<=m;k++){    
		for(int i=1;i<=pow(n,k);i++){		//第k次操作后矩形边长为n^k
			for(int j=1;j<=pow(n,k);j++){
				if(s[k][i][j]=='.'){		//如果当前位置为“.”，那就换成题目给出的矩阵
					for(int i1=1;i1<=n;i1++){
						for(int j1=1;j1<=n;j1++){
							s[k+1][i1+(i-1)*n][j1+(j-1)*n]=s[1][i1][j1];
						}
					}		//i1和j1遍历的是s[1][i][j]———将要变成的矩阵
				}
				else if(s[k][i][j]=='*'){
					for(int i1=(i-1)*n+1;i1<=i*n;i1++){
						for(int j1=(j-1)*n+1;j1<=j*n;j1++){
							s[k+1][i1][j1]='*';
						}
					}		//遍历与刚刚的差不多，只是这里全部变成“ * ”
				}
			}
		}
	}
	for(int i=1;i<=pow(n,m);i++){
		for(int j=1;j<=pow(n,m);j++){
			cout<<s[m][i][j]; 		//输出第m个矩阵，就是第m次操作后的
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：1)

这道题的题意就是根据一块小的构造一个大的分形。

>分形，具有以非整数维形式充填空间的形态特征。通常被定义为“一个粗糙或零碎的几何形状，可以分成数个部分，**且每一部分都（至少近似地）是整体缩小后的形状”**——摘自百度百科

粗体的字很重要，它提示了我们这道题的解法——递归。

因为递归是在重复地做相似的操作。

所以这道题的核心代码步骤：

1. 将目标图分为$n^2$块，对于每块（设为$s_{i,j}$）：
2. 先将其填充与模板图（设为$a_{i,j}$）一样的字符。
3. 若 $a_{i,j}=$ `.`，即为该区块是空白字符，需对该区块再次递归。
4. 若非，进行下一个区块的操作。

具体定位每一个区块时，发现每一个区块的左上角的坐标都为 $(x+k_0\cdot \frac{len}{n},y+k_1\cdot \frac{len}{n})$（len为区块总长度）

Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k,l=1;
char init[3][3];//初始模版图
char ans[243][243];//目标图
void input();
void draw(int,int,int);
void output();
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//千万别忘
	input();//输入
	draw(0,0,l);//递归
	output();//输出
	return 0;
}
void input(){
	cin>>n>>k;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
		cin>>init[i][j];
	for(int i=1;i<=k;i++) l=l*n;
	return;
}
void draw(int sx,int sy,int len){ 
            //分别为区块的x,y值
	int slen=len/n;//每一个区块的长度
	if(len==1) {return;}//递归边界条件
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=sx;k<sx+slen;k++)
				for(int l=sy;l<sy+slen;l++)	
				ans[k][l]=init[i][j];
			if(init[i][j]=='.') draw(sx,sy,slen);//继续递归
			sy+=slen;
		}
		sx+=slen;
		sy-=slen*n;//这错误我调了好久（菜鸡一个）
	}
}
void output(){
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++) putchar(ans[i][j]);
		puts("");
	}
	return;
}
```


---

## 作者：xgwpp6710 (赞：0)

嗯，这题数据量不大，思路也不复杂，那对于本蒟蒻来说，就用暴力解题吧。

直接去模拟操作过程即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char paint[1005][1005],b[1005][1005],hb[1005][1005];//b 是备用的 
int n,k,l=1;//l 是目前操作的边长
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//注意一定要加上这两条！！！
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>hb[i][j];
	paint[1][1]=b[1][1]='.';//初始化 其中b数组是为了方便记录paint当前状态，更新时使用
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=l;j++)
			for(int r=1;r<=l;r++)//枚举当前画布的所有像素点
			{
				if(b[j][r]=='.')//白色像素点
				{
					for(int p=1;p<=n;p++)
						for(int q=1;q<=n;q++)
						{
							paint[p+(j-1)*n][q+(r-1)*n]=hb[p][q];//这行作用是把原来的像素点(p,q)放大成一个子分形，放缩规则按照题目输入的矩阵
						}
				}
				else
				{
					for(int p=1;p<=n;p++)
						for(int q=1;q<=n;q++)
						{
							paint[p+(j-1)*n][q+(r-1)*n]='*';//否则直接全黑
						}
				}
			}
		l*=n;//更新画布边长
		for(int p=1;p<=l;p++)
			for(int q=1;q<=l;q++) b[p][q]=paint[p][q];//更新备份数组b
	}
	for(int i=1;i<=l;i++)
	{
		for(int j=1;j<=l;j++) cout<<paint[i][j];
		cout<<endl;
	}
}
```

---

## 作者：ctq1999 (赞：0)

## 题目简述

给定 $n$、$k$ 和 一个 $n\times n$ 由 `*` 和 `.` 组成的矩形。要求输出一个 $n^k\times n^k$ 的矩形，其组成的方式要与给定的矩形相似。具体看题目要求。

## 思路

算法：分型。

[P5461 赦免战俘](https://www.luogu.com.cn/problem/P5461) 的升级版。

记给定的矩形为 $sta$，输出的矩形为 $a$，`*` 为 $1$，`.` 为 $0$。$a$ 原先全是 $0$。

设当前处理的矩形是 $n^{now}$ （$now\neq 1$）的，那么这个矩形可以分成 $n\times n$ 个矩形分别处理，这些矩形下标分别为 $(1,1),\cdots,(1,n),(2,1),\cdots,(n,n)$。

分成后的子矩形的下标为 $(i,j)$。

- 如果 $sta(i,j)$ 的值为 $1$，那么这个子矩形都要变为 $1$。

- 否则要递归，处理 $n^{now-1}$ 的矩形。

因为要更改，递归的同时要记录当前处理的矩形的左上角的下标。

若 $now=1$ 时，直接把当前处理的矩形变为 $std$ 即可。

时间复杂度 $O(n^2k)$。

注意这题要加上这个：

```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```
我也不知道为啥。

## 代码

运用了一下快速幂，其实没啥必要。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define y1 caibictq
#define P pair<int, int>
#define fi first
#define se second

using namespace std;

const int MAXN = 1010;
const int MAXM = 200010;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, k;
int tot, cnt, ans;

int read() {
	int f = 1, s = 0;
	char ch = getchar();
	while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while ('0' <= ch && ch <= '9') {s = (s << 1) + (s << 3) + ((int)ch ^ 48); ch = getchar();}
	return s * f;
}

int a[MAXN][MAXN], sta[MAXN][MAXN];

int qp(int x, int y) {
	int res = 1, base = x;
	while (y) {
		if (y & 1) res *= base;
		base = base * base;
		y >>= 1;
	}
	return res;
}

void dfs(int x, int y, int now) {
	if (now == 1) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				a[x + i - 1][y + j - 1] = sta[i][j];
			}
		}
		return;
	}
	int base = qp(n, now - 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!sta[i + 1][j + 1]) dfs(x + i * base, y + j * base, now - 1);
			else {
				for (int i1 = 0; i1 < base; i1++) {
					for (int j1 = 0; j1 < base; j1++) {
						a[x + i * base + i1][y + j * base + j1] = 1;
					}
				}
			}
		}
	}
	return;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c;
			cin >> c;
			if (c == '*') sta[i][j] = 1;
		}
	}
	dfs(1, 1, k);
	for (int i = 1; i <= qp(n, k); i++) {
		for (int j = 1; j <= qp(n, k); j++) {
			if (a[i][j]) printf("*");
			else printf(".");
		}
		puts("");
	}
	return 0;
}

```


---

## 作者：CrTsIr400 (赞：0)

这道题，**分形**直接搞过。

$1\le  n \leq 3$ , $1 \leq m \leq 5$

也就是**循环枚举**在最后（大）图形中**哪个该为对应小图形的字符**。

比如说这个图形：

```
3 2
.**
..*
*..
```

首先，先把**粗糙的**大图形弄出来(这一步不难)。

```
...******
...******
...******
......***
......***
......***
***......
***......
***......
```

然后，再细化（**已经变成大方块的不要动，在没有动过的小方块上细化**）。

```
.##******
..#******
#..******
.##.##***
..#..#***
#..#..***
***.##.##
***..#..#
***#..#..
```

(图中`#`部分是被第二次细化的像素点)

一直细化 $m$ 次，最后输出这个图，就可以了。

**代码：**

**不贴了，自己思考。（代码的实现较简单，不会难到哪里去）**

---

