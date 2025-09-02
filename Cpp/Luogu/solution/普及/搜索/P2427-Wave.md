# Wave

## 题目描述

波在不同的介质中的传播速度是不一样的。真空中波速都是 $3\times {10}^8$ m/s，而在液体介质中的波速会比真空中的波速小，并且在不同的液体介质中波速不一样。我们将一个液体表面分成 $N \times M$ 块相同大小的正方形格子，每个格子中只包含一种液体介质。现在我们想知道，从某个波源传出去的波能以不变的波速延伸到多大的以波源为中心的大正方形内。假定所有大正方形的边都是平行于坐标轴的。

## 说明/提示

对于 $30\%$ 的数据，有 $1 \le N,M \le 50$，$1 \le Q \le 500$；

对于 $100\%$ 的数据，有 $1 \le N,M \le 1000$，$1 \le Q \le 10000$。

## 样例 #1

### 输入

```
5 5 3
abbaa
abbaa
aaaaa
aaaaa
aaaaa
1 2
1 4
3 2
```

### 输出

```
1
1
3
```

# 题解

## 作者：Link_Cut_Y (赞：12)

[传送门](https://www.luogu.com.cn/problem/P2427)

- 题目分析：
	
	在一个仅有小写字母组成的矩阵中，规定源点 $(x, y)$，求一个满足以下条件的正方形的最大边长是多少。
    
    正方形需要满足的条件：
    
    1. 正方形的边长为整数（~~废话~~）。
    1. 在整个正方形中，包含且只包含一种小写字母。
    1. 正方形的中心为$(x, y)$
    1. 正方形中的四个顶点都不超过矩阵的边缘。（在矩阵内部）
    
   题目有多组数据。
   
- 做法分析：
	
	**Tips: 请先了解[二维前缀和](https://www.acwing.com/problem/content/798/)**
    
   暴力做法：
   
   ```
  int res = 1;
  for (int i = 1; i <= l; i ++ )
  {
      int tx = x + i, ty = y + i;
      int fx = x - i, fy = y - i; // 枚举起点和终点的横纵坐标
      for (int w = 0; w < 26; w ++ ) // 循环枚举每个小写字母 
      {
          int cnt = 0;
          for (int j = fx; j <= tx; j ++ ) 
              for (int k = fy; k <= ty; k ++ ) // 循环遍历整个正方形 
                  if (g[j][k] - 'a' == w) cnt ++ ;

          if (cnt == (tx - fx + 1) * (tx - fx + 1)) res = max(res, tx - fx + 1); // 如果整个正方形内有且只有 w + 'a' 这一种小写字母，那么更新答案 
      }
  }
  ```
	时间复杂度：无法估计的高（~~是我不会算~~）
    
   现在我们来看一下，基于暴力做法，怎样才能优化一下这个问题;
  
  	第一层循环——没什么好改的。
   第二、三、四层循环...... 没错，就是二维前缀和！
   我们用一个 $s[x, y, k]$ 数组来记录从 $(1, 1)$ 到 $(x, y)$ 中字符 $k$ 出现的次数, 然后，我们的 $cnt$ 就不需要使用两层循环来计算了
   	
    $cnt = s[x + i][y + i][type] - s[x - i - 1][y + i][type] - s[x + i][y - i - 1][type] + s[x - i - 1][y - i - 1][type];$
    
    （其中$x, y, type$ 分别表示源点的横坐标，源点的纵坐标，源点的小写字母是什么，$ x + i, y + i, x - i, y - i$ 分别表示正方形右上顶点的横、纵坐标， 左下顶点的横、纵坐标）
    
    代码如下：
  ```
      int type = g[x][y] - 'a', res = 1;
      int l = min(min(n - x, x - 1), min(m - y, y - 1));
      if (l == 0) return 1;

      for (int i = 1; i <= l; i ++ )
      {
          int cnt = s[x + i][y + i][type] - s[x - i - 1][y + i][type] - s[x + i][y - i - 1][type] + s[x - i - 1][y - i - 1][type];
          if (cnt == (2 * i + 1) * (2 * i + 1)) res = max(res, 2 * i + 1);
          else break;
      }
      return res;
  ```
  
- **Coding**

```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;
char g[N][N];
int s[N][N][26];
int n, m, T;

void init()
{
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			for (int k = 0; k < 26; k ++ )
				s[i][j][k] = s[i - 1][j][k] + s[i][j - 1][k] - s[i - 1][j - 1][k] + (g[i][j] - 'a' == k ? 1 : 0);
}

int Biggest_square(int x, int y)
{
	int type = g[x][y] - 'a', res = 1;
	int l = min(min(n - x, x - 1), min(m - y, y - 1));
	if (l == 0) return 1;
	
	for (int i = 1; i <= l; i ++ )
	{
		int cnt = s[x + i][y + i][type] - s[x - i - 1][y + i][type] - s[x + i][y - i - 1][type] + s[x - i - 1][y - i - 1][type];
		if (cnt == (2 * i + 1) * (2 * i + 1)) res = max(res, 2 * i + 1);
		else break;
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &T);
	
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			cin >> g[i][j];
	
	init();
	while (T -- )
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x += 1, y += 1;
		printf("%d\n", Biggest_square(x, y));
	}
	
	return 0;
}
```

---

## 作者：冰桨 (赞：6)

这道题的思路不太好想。
如果你把以此为中心的最大正方形找到，那么次正方形必须和中心字母相同，可以想到每次让边长加上1个，然后进行从上到下，从左到右的判断，如果有一个不成立，就跳出，反之就dfs下一个边长，然而这样会超时，毕竟每次dfs都要重复前面几次的点，比如边长为5就把边长为3的重复搜了一遍，这显然是多余的，所以可以只判断边缘上的。
奉上代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2010;
int n,m,q;
char sym;
//int dx[8]={0,0,1,-1,1,1,-1,-1};
//int dy[8]={1,-1,0,0,1,-1,1,-1};
char map[N][N];
int dfs(int x,int y,int step){
	for(int i=x-step;i<=x+step;i++)
	if(map[i][y-step]!=sym||map[i][y+step]!=sym)
	return step;
	for(int i=y-step;i<=y+step;i++)
	if(map[x-step][i]!=sym||map[x+step][i]!=sym)
	return step;
	dfs(x,y,step+1);
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>map[i][j];
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		sym=map[x+1][y+1];
		printf("%d\n",2*(dfs(x+1,y+1,1))-1);
	}
	return 0;
}
```


---

## 作者：Zhou_yu (赞：5)

## 题目描述：
### [P2427 题目传送门](https://www.luogu.com.cn/problem/P2427)
本题解适合刚学搜索的朋友们放心食用。
## 所用算法：

1. 搜索（**暴力**深搜）。

2. 模拟。

## 算法思路：
从题目入手，感人的数据范围可以推出这是一道：

### 大暴搜！
为什么？
1. 数据范围对于时间范围较小。

2. 是求**最优解或方案数**类问题。

3. 可以进行对每个子问题（每一步）的**单独**分析。

综上，我们可以遍历一遍被波及的范围（如题，上下左右**各拓展 $dep$ 格**），如有不同，结束搜索，**如都相同，扩大范围接着搜！**

## 蒟蒻の AC 代码
[AC 记录](https://www.luogu.com.cn/record/126125676)

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,q,ans;
char a[1005][1005];
void work(int dep,int x,int y)
{
	bool f=1;
	for(int i=x-dep;i<=x+dep&&f;i++)
	if(a[i][y-dep]!=a[x][y]||a[i][y+dep]!=a[x][y])f=0;//上下遍历
	for(int i=y-dep;i<=y+dep&&f;i++)
	if(a[x-dep][i]!=a[x][y]||a[x+dep][i]!=a[x][y])f=0;//左右遍历
	if(f)
	{
		ans=dep*2+1;//更新
		if(x-dep>=1&&y-dep>=1&&x+dep<=n&&y+dep<=m)//不能越界
		work(dep+1,x,y);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>a[i][j];
	while(q--)
	{
		int x,y;	
		cin>>x>>y;
		ans=1;
		work(1,x+1,y+1);//因为从0~n-1,0~m-1,而我习惯用1~n,1~m,所以将坐标x,y各加1得新坐标
		cout<<ans<<'\n';
	}
	return 0;
}
```
## 总结
~~推翻前缀和暴政，世界属于暴搜！~~

暴搜即是真理！

---

## 作者：Aisaka_Taiga (赞：1)

## 基本思路

本题题意就是给你一副由字符组成的图，你需要以他给你的坐标点为中心，问和中心的字符一样的最大正方形的边长。

首先要明确题目中说的行列是从 0 开始的，所以如果存的图从一开始的话要给询问的行列都加一。

其次，我们需要从中心开始向外扩大正方形，这里用中心到边的距离（不计中心点）会比较好实现，搜索的时候只要不断加一就可以实现扩大，而在判断有没有和中心不一样的字符时，只需要扫一遍新扩大的一圈就好了，毕竟之前的已经判断过了，再扫一遍太浪费时间，如果当前的不符合，就直接返回当前中心到边的长度，然后根据小学的知识点把长度乘二减一就好了。

不知道为什么厌氧，开 o2 一直没过，直到有一次忘开 o2 AC 了才明白是怎么回事。

## code
```cpp
#include<bits/stdc++.h>
#define map MAP//由于万能头所以用一下define 
using namespace std;
int n,m,q;//nm存字符图的行列，q存放访问次数
char s,map[2010][2010];//map存放图里面的字符，s是要查找的字符 
int dfs(int x,int y,int cnt)//cnt是当前中心到边的距离 
{
	for(int i=x-cnt;i<=x+cnt;i++)//对比外面两列的字符 
	if(map[i][y-cnt]!=s||map[i][y+cnt]!=s)//如果当前有不是查找的字符时 
	return cnt;//返回当前cnt的值 
	for(int i=y-cnt;i<=y+cnt;i++)//同理对比横着的两行字符 
	if(map[x-cnt][i]!=s||map[x+cnt][i]!=s)
	return cnt;
	dfs(x,y,cnt+1);//如果全符合就再递增一个单位长度继续找 
}
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    cin>>map[i][j];//输入图 
	for(int i=1;i<=q;i++)//访问 
	{
		int x,y,ans;//ans存放正方形边长 
		cin>>x>>y;
		s=map[x+1][y+1];//题目中从0开始，要加一 
		ans=2*(dfs(x+1,y+1,1))-1;//计算ans的值 
		cout<<ans<<endl;//输出
	}
	return 0;//好习惯 
}
```


---

## 作者：hfyzw (赞：1)

算法二：

由于只有26个字母，因此我们可以前缀和记录每个字母出现情况，已知中心点和正方形边长，O（1）即求得该区域有多少个某字母，每次询问枚举答案即可



```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define N 1001
char a[N][N];
int f[26][N][N];                                                                                                   //f是前缀和数组，但这里内存有些危险
int main()
{
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=0;i<n;i++){
        cin>>a[i];
        for(int j=0;j<m;j++){
            for(int k=0;k<26;k++){
                if(i>0)f[k][i][j]+=f[k][i-1][j];
                if(j>0)f[k][i][j]+=f[k][i][j-1];
                if(i>0&&j>0)f[k][i][j]-=f[k][i-1][j-1];
            }
             f[a[i][j]-'a'][i][j]++;                                                                                          //计算每个位置某字母出现情况
        }
    }
    for(int i=0;i<q;i++){
        int x,y;
        cin>>x>>y;
        int j=1;
        for(;j<=n;j++)
            {
                if(!(x-j>=0&&y-j>=0&&x+j<n&&y+j<m))break;                                                       //边界
                if(f[a[x][y]-'a'][x+j][y+j]-f[a[x][y]-'a'][x-j-1][y+j]-f[a[x][y]-'a'][x+j][y-j-1]+f[a[x][y]-'a'][x-j-1][y-j-1]<(2*j+1)*(2*j+1))
                    break;                                                                                                                  //区域不全是同一字母
            }
        cout<<2*j-1<<endl;                                                                                                        //直到不行才退出，输出2*j-1
    }
    return 0;
}
```

---

## 作者：H_space (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2427)

## 题目简述
输入三个整数 $N$, $M$, $Q$。


其中 $N$ 代表矩阵宽度，$M$ 代表矩阵长度， $Q$ 代表询问次数。


要求求得以坐标 $(x,y)$ 为中心的最大正方形的边长，且该正方形中的每个字符应相等。

## 思路
本题可以考虑利用**深搜**解决，即从坐标 $(x,y)$ 开始，用**变量** $k$ 记录搜索次数。


起初 $k = 1$, $k$ 每增加 $1$ 次都需要先判断正方形四个角的坐标是否**越界**,之后再判断正方形的最外围的字符是否与中心坐标 $(x,y)$ **一样**，如果符合条件，则可以利用  $ans$ 进行记录。


这里不难看出，$ans = k \times 2 + 1 $。


注意：题目要求输入的 $x$，$y$ 是以二维数组**下标为** $0$ 的情况，所以将录入的 $x$，$y$ 均 $+1$ 之后再搜。


下面就可以用代码实现：
```cpp
#include<iostream>
using namespace std;

int n,m,q,ans;//ans要初始化 
char a[1005][1005];

void dfs(int x, int y, int k){
	if(!(1 <= x - k && x + k <= n && 1 <= y - k && y + k <= m))return;//是否四个角坐标越界
	for(int i = x - k; i <= x +k; i++)if(a[i][y-k] != a[x][y])return;//是否正方形下边长字符与中心相同
	for(int i = x - k; i <= x +k; i++)if(a[i][y+k] != a[x][y])return;//是否正方形上边长字符与中心相同
	for(int i = y - k; i <= y +k; i++)if(a[x-k][i] != a[x][y])return;//是否正方形左边长字符与中心相同
	for(int i = y - k; i <= y +k; i++)if(a[x+k][i] != a[x][y])return;//是否正方形右边长字符与中心相同
	ans=k*2+1;//记录答案
	dfs(x,y,k+1);//继续往下搜
	return;
}
int main(){
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];//二维数组的输入 
	while(q--){
		ans = 1;//ans要初始化 
		int x, y;	
		cin >> x >> y;
		dfs( x + 1, y + 1, 1);//注意题面要求输入的x，y是以二维数组下标为0的情况，所以此处+1之后再搜
		cout << ans << "\n";
	}
	return 0;//华丽结束
}
```






---

## 作者：hexz01 (赞：0)

# P2427 Wave 题解

## 1 理解题意

[题目传送门](https://www.luogu.com.cn/problem/P2427)

### 题目大意
给定一个仅由小写字母组成的矩阵。

有 $Q$ 个询问，每次给定波的源点 $(x, y)$，输出一个**最大的**，以 $(x,y)$ 为**中心**的**正方形**，要求正方形在矩阵内，并且正方形中**有且仅有**一种小写字母（其实就是源点处的字母啊喂）。

## 2 暴力
很显然，我们可以从大往小枚举扩散距离，然后遍历正方形验证，第一个满足要求的就是答案。

最大扩散距离就是 $\min(\min(n-x, x-1), \min(m-y, y-1))$，不懂看图：
```
b是源点
aaaaaaaa    aaaa|aaa
aaaaaaaa    aaaa|aaa
aaaabaaa -> ----b--- 也就是min(min(n-x, x-1), min(m-y, y-1))
aaaaaaaa    aaaa|aaa
aaaaaaaa    aaaa|aaa
```

**code**
```cpp
int solve(int x, int y){
	int maxl=min(min(n-x, x-1), min(m-y, y-1));
	for(int l=maxl;l>=1;l--){
		bool f=1;
		int x1=x-l, y1=y-l, x2=x+l, y2=y+l;
		for(int i=x1;i<=x2;i++)
			for(int j=y1;j<=y2;j++)
				if(a[i][j]!=a[x][y])
					f=0;
		if(f)
			return 2*l+1;
	}
	return 1;
}
```
复杂度 $O(n^3)$，成功得到 $30$ 分（写得好能得 $40$）。

## 3 正解
### 3.1 前置芝士
[二维前缀和](https://oi-wiki.org/basic/prefix-sum/)
### 3.2 改变思路
按照刚才的思路，似乎已经无法再优化了。

但仔细想想，我们可以换一个方式判断：
小正方形范围内的字母都是源点处的字母，那也就是说小正方形范围内有小正方形面积个字母与源点处的字母相同。

**code**
```cpp
#include <iostream>
#include <string>
using namespace std;
const int N=1007;
int n, m, q;
char a[N][N];
string s;
int solve(int x, int y){
	int maxl=min(min(n-x, x-1), min(m-y, y-1));
	for(int l=maxl;l>=1;l--){
		int cnt=0;
		int x1=x-l, y1=y-l, x2=x+l, y2=y+l;
		for(int i=x1;i<=x2;i++)
			for(int j=y1;j<=y2;j++)
				if(a[i][j]==a[x][y])
					cnt++;
		if(cnt==(2*l+1)*(2*l+1)){
			return 2*l+1;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=m;j++){
			a[i][j]=s[j-1];
		}
	}
	while(q--){
		int x, y;
		cin>>x>>y;
		x++;y++;
		cout<<solve(x, y)<<endl;
	}
	return 0;
}
```
复杂度和思路一相同。

### 3.3 正解
我们来思考上述代码哪里可以优化：
- 第一维循环：枚举扩散范围，不能优化。
- 第二、三维循环：遍历小正方体，计算与源点处字母相同的字母个数。

第二、三维循环好像可以优化？

我们可以利用二维前缀和，预处理 $pre_{x,y,c}$ 表示 $(1,1)$ 到 $(x,y)$ 小正方形里，字母 $c$ 的个数。

如何计算 $pre$ 数组呢？

每次计算只会新增 $(x,y)$ 处的字母。

那么我们来看图：（蓝色区域是计算过的，红色区域是重复的，黄色是当前计算的）

![](https://cdn.luogu.com.cn/upload/image_hosting/2rr367lw.png)

那么 $pre_{x,y,c}=pre_{x-1,y,c}+pre_{x,y-1,c}-pre_{x-1,y-1,c}+(a_{x,y}==c)$。

那问题又来了，怎么利用前缀和计算指定正方形中与源点处字母相同的字母个数呢？

我们又来看一张图：（蓝色是要减去的，黄色是要计算的，红色是重复的）

![](https://cdn.luogu.com.cn/upload/image_hosting/keagvlug.png)

所以 $pre_{x_2,y_2,c}-pre_{x_2,y_1,c}-pre_{x_1,y_2,c}+pre_{x_1, y_1, c}$ 就是正方形内与源点处字母相同的字母个数。

**AC code**
```cpp
#include <iostream>
#include <string>
using namespace std;
const int N=1007;
int n, m, q;
char a[N][N];
int pre[N][N][30];
string s;
void init(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int c=0;c<26;c++)
				pre[i][j][c]=pre[i-1][j][c]+pre[i][j-1][c]-pre[i-1][j-1][c]+((a[i][j]-'a')==c);
}
int solve(int x, int y){
	int maxl=min(min(n-x, x-1), min(m-y, y-1));
	int c=a[x][y]-'a';
	for(int l=maxl;l>=1;l--){
		int x1=x-l, y1=y-l, x2=x+l, y2=y+l;
		int cnt=pre[x2][y2][c]-pre[x2][y1-1][c]-pre[x1-1][y2][c]+pre[x1-1][y1-1][c];
		if(cnt==(2*l+1)*(2*l+1)){
			return 2*l+1;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=m;j++){
			a[i][j]=s[j-1];
		}
	}
	init();
	while(q--){
		int x, y;
		cin>>x>>y;
		x++;y++;
		cout<<solve(x, y)<<endl;
	}
	return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/P2427)

## 题目简述

给定 $N \times M$ 的字符矩阵，有 $Q$ 次询问，对于每次询问给出 $x,y$，求以 $(x,y)$ 为中心的最大正方形**边长**且正方形中字符均**相同**。

## 思路

看到**数据范围较小**，可以考虑**深搜**解决，约掉常数的时间复杂度**最坏**为 $O(q \times \min(n,m))$，**勉强可以通过**。（不过代码跑的飞快，数据还是有点水的。）

考虑深搜的实现，以 $(x,y)$ 为中心开始搜，每次**边长增加** $2$，即距 $(x,y)$ 的距离 $d$ 每次增加 $2$。对于每次增加，**判断四周的字符**是否与中心 $(x,y)$ 相同，**不相同终止搜索**即可，记得每次增加完边长后，**实时更新** $ans$！

下面是代码实现：

```cpp
#include<iostream>
using namespace std;
#define MAXN 1005 // 数组大小。

int n, m, q, ans = 0, x, y; // 题目给定变量及辅助变量。
char mp[MAXN][MAXN]; // 存储字符矩阵。

// 开搜，传入中心坐标及距中心距离 date。
void dfs(int x, int y, int date) {
	if(!(y - date >= 1 && y + date <= m && x - date >= 1 && x + date <= n)) return; // 出现越界，直接终止。
   // 分别搜索上、下、左、右四个边。
	for(int i = y - date; i <= y + date; i ++)
		if(mp[x - date][i] != mp[x][y]) return;
	for(int i = x - date; i <= x + date; i ++)
		if(mp[i][y - date] != mp[x][y]) return;
	for(int i = y - date; i <= y + date; i ++)
		if(mp[x + date][i] != mp[x][y]) return;
	for(int i = x - date; i <= x + date; i ++)
		if(mp[i][y + date] != mp[x][y]) return;
	ans = date * 2 + 1; // 更新 ans 的值。
	dfs(x, y, date + 1); // 接着搜。
	return;
}

int main() {
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i ++) 
		for(int j = 1; j <= m; j ++) 
			cin >> mp[i][j];
	while(q --) {
		scanf("%d %d", &x, &y);
		x ++, y ++, ans = 1; // 因为题目中下边从 0 开始，所以都先自加 1，另外初始化 ans。
		dfs(x, y, 1); // 深搜。
		printf("%d\n", ans); // 输出答案，记得换行。
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/124395212)

$$\texttt{The End!}$$

---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/P2427)

## 题意简述：

给定一个字符矩阵每次询问给出 $x$ 和 $y$，求以 $(x,y)$ 为中心的最大每个字符相同的正方形的边长是多少。

## 思路分析：

我们可以以 $x,y$ 为起点，做深搜操作，每次扩大一圈，即正方形边长增加 $2$，上下左右四个方向搜一遍，如果遇到不相同的就直接结束。如果搜完一圈都相同了，就在扩大一圈继续搜，直到不相同为止。注意要判断越界，且输入数据中下标从 $0$ 开始。

## 代码：

```cpp
#include<iostream>
using namespace std;
int n,m,q,ans;//ans记录答案 
char a[1003][1003];//存矩阵 
void dfs(int x,int y,int d){//d为当前圈数，即d=当前边长/2 
	if(y-d>=1&&y+d<=m&&x-d>=1&&x+d<=n){//判断越界 
	}else{
		return;
	}
	for(int j=y-d;j<=y+d;j++){//上边 
		if(a[x-d][j]!=a[x][y]){
			return;
		}
	}
	for(int i=x-d;i<=x+d;i++){//左边 
		if(a[i][y-d]!=a[x][y]){
			return;
		}
	}
	for(int j=y-d;j<=y+d;j++){//下边 
		if(a[x+d][j]!=a[x][y]){
			return;
		}
	}
	for(int i=x-d;i<=x+d;i++){//右边 
		if(a[i][y+d]!=a[x][y]){
			return;
		}
	}
	ans=d*2+1;//计算答案 
	dfs(x,y,d+1);//继续搜，d+1 
	return;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//输入 
		}
	}
	int x,y;
	while(q--){//q次询问 
		scanf("%d%d",&x,&y);
		x+=1,y+=1,ans=1;//注意题中下标从0开始 
		dfs(x,y,1);
		cout<<ans<<"\n";//输出答案 
	}
	return 0;
}
```

---

## 作者：Archy_ (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/P2427)

### 题目简述：

输入三个整数 $N$，$M$，$Q$。$N$ 和 $M$ 表示长度，$Q$ 为询问次数。求出以坐标 $(x,y)$ 为中心的最大正方形的边长。

**注意：**
 
1. 题目中二维数组下标是从 $0$ 开始读入的。

2. 正方形中的每个字符应相等。

## 思路：

本题可以考虑**深搜**，从坐标 $(x,y)$ 开始，用 $step$ 记录搜索次数。

刚开始 $step = 1$，$step$ 每加 $1$ 判断一下正方形的四个角的坐标是否**越界**，其次再判断正方形的最外围的字符是否与中心**相等**，如果都满足将正方形边长记录到 $ans$。

其中，**正方形边长** $a = step \times 2 + 1$。

下面是深搜代码实现：

```cpp
#include<iostream>
using namespace std;
int n,m,q,ans;
char a[1005][1005];
void dfs(int x,int y,int step){
	if(!(1<=x-step&&x+step<=n&&1<=y-step&&y+step<=m))return;//是否四个角坐标越界
	for(int i=x-step;i<=x+step;i++)if(a[i][y-step]!=a[x][y])return;//是否正方形下边长字符与中心相同
	for(int i=x-step;i<=x+step;i++)if(a[i][y+step]!=a[x][y])return;//是否正方形上边长字符与中心相同
	for(int i=y-step;i<=y+step;i++)if(a[x-step][i]!=a[x][y])return;//是否正方形左边长字符与中心相同
	for(int i=y-step;i<=y+step;i++)if(a[x+step][i]!=a[x][y])return;//是否正方形右边长字符与中心相同
	ans=step*2+1;//记录答案
	dfs(x,y,step+1);//继续往下搜
	return;
}
int main(){
	ios::sync_with_stdio(0);//ios快读
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];//读入数据
	while(q--){
		ans=1;//初始化
		int x,y;	
		cin>>x>>y;
		dfs(x+1,y+1,1);//由于题面输入的x，y是以二维数组下标为0的情况，所以此处+1之后再搜
		cout<<ans<<"\n";//输出答案
	}
	return 0;
}
```

---

## 作者：ztdxwsys (赞：0)

**（第一次写这种题解哈，也不知道审核能不能通过），这道题它看上去是个模拟（当然它实际上就是模拟），所以我们可以暴力一点做**。
	
_大概原理是什么呢，假设我们读入的坐标对应的字符是‘a’，把我们在枚举的它能往外延的值叫”延伸值“。那么我们从0开始枚举它，就是0的时候：1个a，1的时候9个a，2的时候25个a，具体实现的话可看看下面的check函数，也就是把正方形的外围框切成八份来做（说起来，和二分答案有点像）。_ 
    
**下面是代码**。
    
    #include<bits/stdc++.h>
	using namespace std;
	inline int read()
  	{
      	int x=0,f=1;	
      	char c=getchar();
      	while((c<'0'||c>'9')&&c!='-')c=getchar();
      	if(c=='-')f=-1,c=getchar();	
      	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
      	return f*x;
  	}//快读板子
    inline char zifu()
    {
        char c=getchar();
        while(c<'a'||c>'z')c=getchar();
        return c;
    }//（临时）字符读入的函数
    char a[1001][1001];
    int n,m,q;
    bool check(int x,char se,int u,int v)
    {
        for(int i=1;i<=x;++i)
            {
                if(a[u+x][v-i]!=se)return 0;
                if(a[u+x][v+i]!=se)return 0;
                if(a[u-x][v-i]!=se)return 0;
                if(a[u-x][v+i]!=se)return 0;
                if(a[u+i][v+x]!=se)return 0;
                if(a[u-i][v+x]!=se)return 0;
                if(a[u+i][v-x]!=se)return 0;
                if(a[u-i][v-x]!=se)return 0;
            }
            return 1;
    }
    int main(){
        n=read();
        m=read();
        q=read();
        for(register int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)a[i][j]=zifu();
        for(register int i=1;i<=q;++i)
        {
            int x=read();	
            int y=read();
            x++;
            y++;//这里考虑到题目中行与列的标号是从0～n-1和0～m-1，我们把读入的坐标变成我们的1～n的行号和1～m的列号。
            char se=a[x][y];
            int r=min(x-1,y-1);
            r=min(n-x,r);
            r=min(m-y,r);//从该点出发，到矩阵四边界的距离的最小值，就是从该点的最大延伸值（因为不可能到矩阵外面去嘛）
            int k;
            for(int l=0;l<=r;++l)//这里从0开始枚举延伸值代表的就是从里往外检查新加的正方形外框符不符合题目要求，如果符合的话，就加上这个外框，使之成为一个新正方形，不符合的话，最大延伸值就是上一个
            {
                if(!check(l,se,x,y))break;
                k=l;
            }//找最大延伸值
            printf("%d\n",2*k+1);//记住要输出的是最大边长（不是延伸值）
        }
        return 0;
    }


---

