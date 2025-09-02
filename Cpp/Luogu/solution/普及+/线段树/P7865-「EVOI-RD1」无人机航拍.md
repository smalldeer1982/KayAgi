# 「EVOI-RD1」无人机航拍

## 题目背景

T 市举行活动需要拍摄高空俯瞰图，找来了一个无人机机队负责拍摄工作。 [一E孤行](https://www.luogu.com.cn/user/229919) 是队伍的队长，他根据广场的规模来安排无人机的位置。

## 题目描述

有一个广场，可以看做是一个 $n \times m$ 的矩形；一E孤行 一共有 $s$ 架无人机，每架无人机的拍摄范围也可以看做是一个矩形，无人机机队的拍摄范围为所有无人机拍摄范围的并。

一E孤行 负责安排无人机的位置，而总负责人 WuuTue 要验收~~她~~他的方案。WuuTue 的验收方法是列举出 $L$ 个重要的区域，每个重要区域也是一个矩形。 一E孤行 方案的优秀程度取决于有多少个重要区域完全在无人机机队的拍摄范围中。

因此，对于每一个重要区域， 一E孤行 想知道它是否完全在无人机机队的拍摄范围中。

## 说明/提示

**样例说明**

如下图所示，区域 $A,B,C$ 分别是某某安排的无人机能够覆盖的范围，区域 $D,E$ 是 WuuTue 要验收时列举的重点区域，区域 $D$ 能够被完全覆盖，区域 $E$ 不能被全部覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/60pq06qo.png)   

**数据规模与约定**

**本题采用捆绑测试。**

对于 $40\%$ 的数据：$1 \le n \le 1000$，$1 \le s \le 100$ 。  
对于 $100\%$ 的数据：

- $1 \le n, m \le 3 \times 10^{3}$。 
- $1 \le s,L \le 10^6$。
- $1 \le x_1 < x_2 \le n$。
- $1 \le r_1 < r_2 \le n$。
- $1 \le y_1 < y_2 \le m$。
- $1 \le c_1 < c_2 \le m$。


## 样例 #1

### 输入

```
9 9 
3 
2 1 4 4 
2 5 4 9 
5 2 7 6 
2 
3 3 6 6 
5 6 8 8```

### 输出

```
Yes 
No```

# 题解

## 作者：冷月葬T魂 (赞：6)

首先可以发现 $n,m$ 较小，故考虑将无人机能覆盖的所有格子记录在一个二维数组 $a$ 中。  
具体来说，将每个无人机覆盖的范围 $(x_1,y_1,x_2,y_1)$ 分解为两个“事件”：“开始覆盖”$(x_1,y_1,y_2,1)$ 和 “结束覆盖”$(x_2+1,y_1,y_2,-1)$。然后将所有事件按 $x$ 排序，用扫描线算法，维护一个树状数组 $T$，记录当前 $x$ 一行（或列，看你怎么理解坐标 $(x,y)$）中哪些方格被覆盖，依次处理每个事件，由于 $x$ 变化的总数为 $n$，故这一步的时间复杂度为 $O(nm \log m)$。  
然后预处理出二维数组 $a$ 的二维前缀和，对于每个询问，判断 $a$ 中对应子矩阵的元素和是否等于询问的总面积即可（这等价于 $a$ 中对应子矩阵的每个元素都是 $1$，注意 $a$ 中存储的是格子**是否**被覆盖而不是覆盖多少次）。  

代码如下：

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define clr(a,v) memset(a,v,sizeof(a))
//#define int long long
using namespace std;

const int N=3e3+5,M=2e6+5;

class FTree{
	int n,c[N*4];
	int lowbit(int x)
	{
		return x&(-x);
	}
public:
	void init(int _n)
	{
		n=_n;
		clr(c,0);
	}
	void poke(int p,int x)
	{
		while(p<=n){
			c[p]+=x;
			p+=lowbit(p);
		}
	}
	int peek(int p)
	{
		int res=0;
		while(p){
			res+=c[p];
			p-=lowbit(p);
		}
		return res;
	}
};

struct cpdd{
	int x,y1,y2,type;
	bool operator< (const cpdd& cp) const
	{
		return x<cp.x;
	}
}cp[M];

int n,m,s,a[N][N],sum[N][N];
FTree T;

int area(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}

inline int read()
{
	register char Charlie;
	while((Charlie=getchar())<'0'||Charlie>'9') ;
	register int Vinnie=Charlie-'0';
	while((Charlie=getchar())>='0'&&Charlie<='9') Vinnie=(Vinnie<<3)+(Vinnie<<1)+Charlie-'0';
	return Vinnie;
}

signed main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	
//	cin>>n>>m;
	n=read();
	m=read();
	
//	cin>>s;
	s=read();
	For(i,1,s){
		int x1,y1,x2,y2;
//		cin>>x1>>y1>>x2>>y2;
		x1=read();
		y1=read();
		x2=read();
		y2=read();
		cp[i*2-1]=(cpdd){x1,y1,y2,1};
		cp[i*2]=(cpdd){x2+1,y1,y2,-1};
	}
	
	sort(cp+1,cp+1+s*2);
	
	int cur=1;
	
	T.init(m+1);
	
	For(i,1,s*2){
		while(cur<cp[i].x){
			For(j,1,m){
				a[cur][j] = T.peek(j)>0 ? 1 : 0;
			}
			cur++;
		}
		if(cp[i].type==1){
			T.poke(cp[i].y1,1);
			T.poke(cp[i].y2+1,-1);
		}
		else{
			T.poke(cp[i].y1,-1);
			T.poke(cp[i].y2+1,1);
		}
	}
	
	while(cur<=n){
		For(j,1,m){
			a[cur][j] = T.peek(j)>0 ? 1 : 0;
		}
		cur++;
	}
	
//	For(i,1,n){
//		For(j,1,m){
//			if(a[i][j]) cout<<'#';
//			else cout<<'.';
//		}
//		cout<<endl;
//	}
//	cout<<endl;
	
	For(i,1,n){
		For(j,1,m){
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+a[i][j];
		}
	}
	
	int Q;
//	cin>>Q;
	Q=read();
	
	while(Q--){
		int x1,y1,x2,y2;
//		cin>>x1>>y1>>x2>>y2;
		x1=read();
		y1=read();
		x2=read();
		y2=read();
		if(area(x1,y1,x2,y2)==(x2-x1+1)*(y2-y1+1)) puts("Yes");
		else puts("No");
	}
	
	return 0;
}

```

---

## 作者：CharlesZiy (赞：5)

## 写在前面

这篇题解主要讲述了二维前缀和的知识。

看到这道题有个“线段树”标签，本蒟蒻认为，用线段树切掉这题属实是杀鸡用牛刀了。这题的数据给的很善良：

$1 \leq n, m \leq 3000$。

这样的数据，无论是空间和时间复杂度，二维前缀和+差分都绰绰有余。

那么，建立了思路，让我们来研究一下细节。

***

## 二维前缀和&差分

关于二维前缀和，建议大家去切掉[这题](https://www.luogu.com.cn/problem/P2280)，是一道标准的二维前缀和，那里的题解也写得很详细。

标准的二维前缀和是（要求一个矩阵内的数字和）：

我们设前缀和矩阵是 `sum` 二维数组，其中要求的矩阵左上角坐标是 `[i][j]`，右下角坐标是 `[k][l]`。

于是，这个矩阵的数字和就是 `sum[k][l] + sum[i][j] - sum[i - 1][l] - sum[k][j - 1]`。

大家在草稿纸上模拟一下，会发现还是很有容斥原理的味道的。

***

关于二维差分，建议大家去切掉[这题](https://www.luogu.com.cn/problem/P3397)，很有帮助。

标准的二维差分（假设要把一个矩阵内同时加上 $w$）：

令差分矩阵是 `b` 二维数组，其中要维护的矩阵左上角坐标是 `[i][j]`，右下角坐标是 `[k][l]`。

于是，处理差分矩阵的过程是：

```cpp
b[i][j] += w;
b[k + 1][l + 1] += w;
b[i][l + 1] -= w;
b[k + 1][j] -= w;
```

大家也可以模拟一下。

***

接下来，要解决这题，还有一个重要的性质：

**前缀和和差分（不管是几维）互为逆运算。**

想到这里，各位读者是否露出了笑容？

***

## 思路

先在输入的时候把差分矩阵处理好。

接下来用前缀和（差分的逆运算）还原矩阵，再跑一遍循环扫一遍矩阵，统计哪些地方被无人机覆盖到了（没覆盖记为 $0$，覆盖了记为 $1$）。

接下来，让我们想想这件事情：如果一个矩阵内数字和就是它的面积，能否说明它全部被覆盖了？

答案是肯定的。

于是，对于 $L$ 组询问，依次使用前缀和算出矩阵内数字和即可。

***

## 代码

警告：洛谷拥有强大的反作弊系统。

**有一个细节需要注意，本题给你的坐标是左下角和右上角，直接使用上面说的套路会WA，需要进行一些细节的修改。**

```cpp
#include <iostream>
#include <algorithm>
#define MAXN 3005
#define MAXM 3005
#define MAXS 1000005
using namespace std;

int n, m, s, l;
int squ[MAXN][MAXM]; // 使用一个矩阵即可

int main()
{
	std::ios::sync_with_stdio(false);
	
	cin >> n >> m >> s;
	
	for (int i = 1; i <= s; i++)
	{
		int a1, b1, a2, b2;
		cin >> a1 >> b1 >> a2 >> b2;
		
		squ[a1][b1]++;
		squ[a2 + 1][b2 + 1]++;
		squ[a2 + 1][b1]--;
		squ[a1][b2 + 1]--;
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			squ[i][j] += squ[i - 1][j] + squ[i][j - 1] - squ[i - 1][j - 1];
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (squ[i][j]) squ[i][j] = 1;
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			squ[i][j] += squ[i - 1][j] + squ[i][j - 1] - squ[i - 1][j - 1];
		}
	}
	
	cin >> l;
	
	for (int i = 1; i <= l; i++)
	{
		int r1, c1, r2, c2;
		cin >> r1 >> c1 >> r2 >> c2;
		
		int sum = squ[r2][c2] - squ[r1 - 1][c2] - squ[r2][c1 - 1] + squ[r1 - 1][c1 - 1];
		if (sum >= (r2 - r1 + 1) * (c2 - c1 + 1)) cout << "Yes" << endl; // 为了保险，用了大于等于
		else cout << "No" << endl;
	}
}
```

2022-07-24 upd：更改了一处笔误  
2022-10-14 upd：感谢 @int_R，更改了二维差分介绍处的错误

---

## 作者：Buried_Dream (赞：3)

对之前的注释进行补充，求过qwq。

### 先说一下我的第一眼看到这题的暴力思路:

定义一个 `bool` 数组，初始化为 $0$；

将无人机能看到的地方都标记为 $1$；

然后去判断一下在他所给的 $L$ 个范围里是不是完全是 $1$；

如果不是完全是 $1$，就输出 `no`，反之输出 `yes`。

## 40分 Code
```c
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 3001
#define il inline
#define re register

using namespace std;

int read() {
	char ch = getchar();
	int x = 0, f = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int n,m;
int s,L;
bool vis[maxn][maxn];//定义在主函数外，默认值为false； 

signed main() {
	n=read();
	m=read();
	s=read();//读入 
	for(int i=1,x1,x2,y1,y2; i<=s; i++) {
		x1=read();
		y1=read();
		x2=read();
		y2=read();
		for(int k=x1; k<=x2; k++) {
			for(int j=y1; j<=y2; j++) {
				vis[k][j]=true;//将无人机能拍到的地方标记为true； 
			}
		}
	}
	L=read();
	bool flag=0;
	for(int i=1,x1,x2,y1,y2; i<=L; i++) {
		flag=0;
		x1=read();
		y1=read();
		x2=read();
		y2=read();
		for(int k=x1; k<=x2; k++) {
			for(int j=y1; j<=y2; j++) {//判断是否完全是1 
				if(vis[k][j]==false) {
					cout<<"No"<<endl;
					flag=1;
					break;
				}
			}
			if(flag==1) break;
		}
		if(!flag) cout<<"Yes"<<endl;
	}
	return 0; 
}
```
## 赛后想出的正解：

### 前置芝士：  
差分和前缀和。

链接：[知识点](https://oi-wiki.org/basic/prefix-sum/)


## **思路：**



先用差分，如果只差分横向，$3e9$ 会把你卡死，所以横向纵向都做差分，具体就如下图：

![
](https://cdn.luogu.com.cn/upload/image_hosting/7v37evzv.png)


将矩形四个点分别设为 $1$ 、$-1$ 、$1$、$-1$ 进行横向差分，纵向差分；将进行差分后的矩阵染色成 $1$，然后预处理二维数组的二维前缀和，将染色的面积同给定区域的面积比较是否相等就可以，这也是为什么染色成 $1$ 的原因。

具体注释在代码里。

## AC code

```c
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define int long long
#define il inline
#define re register
#define inf 0x3f3f3f3f
#define maxn 100010
using namespace std;

inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-'){w = -1;}ch = getchar();}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s*w;
}
int f[3001][3001]; 
int n, m, s, l;
signed main(){
	n = read(), m =read() , s = read();;
	for(int i = 1 ,a,b,c,d;i <= s; i++) {
		a = read(), b = read(), c = read(), d = read();
		f[a][b]++,f[c+1][b]--,f[a][d+1]--,f[c+1][d+1]++;//进行差分的点，设置为1，1，-1，-1； 
	} 
	for(int i  = 1 ; i <= n ; i++ ) {
		for (int  j =  1; j <= m; j++ ) {
			f[i][j] = f[i][j] + f[i - 1][j];//进行纵向差分 
		}
	}
	for(int i  = 1 ; i <= n ; i++ ) {
		for (int  j =  1; j <= m; j++ ) {
			f[i][j] = f[i][j] + f[i][j - 1 ];//进行纵向差分 
		}
	}
	for(int i = 1;i <= n; i++) {
		for( int j = 1 ;j <= m; j++) {
			if(f[i][j] > 0) f[i][j] = 1;//矩阵赋值为1,比较面积的时候好算 
		}
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1 ;j <= m; j++) {
			f[i][j] = f[i-1][j] + f[i][j - 1] -f[i - 1][j - 1]+ f[i][j]; //二维前缀和
		}
	}
	l =  read();
	for(int i = 1,a,b,c,d; i <=l; i++) {
		a = read(), b = read(), c = read(), d = read() ;
		int sum = f[c][d] - f[c][b - 1] - f[a - 1][d] + f[a - 1][b - 1],res = (abs(a-c) + 1) *(abs(b - d)+1);//res计算用两边周长计算面积，sum计算赋值成1面积 
		if(sum == res) cout<<"Yes\n";//相等为完全覆盖 
		else cout<<"No\n"; 
	} 
	return 0;
}

```


---

## 作者：happy_dengziyue (赞：2)

### 1 思路

##### 大体思路

本题使用二维差分，不使用树状数组。

首先输入航拍范围。

设矩形两个点的坐标分别为 $(x_1,y_1)$，$(x_2,y_2)$。

设 $++$ 为自增 $1$，$--$ 为自减 $1$。则：

```
++a[x_1][y_1]
++a[x_2+1][y_2+1]
--a[x_2+1][y_1]
--a[x_1][y_2+1]
```

然后跑一遍二维前缀和，使 $a[i][j]$ 表示坐标 $(i,j)$ 上空有多少无人机。

然后对于每个元素，取 `bool` 值，代表上面有没有无人机。

再跑一遍二维前缀和。

很明显，对于每个提问，设矩形两个点的坐标分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$，则，如果满足要求：

$$\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}a[i][j]=(x_2-x_1+1)\times(y_2-y_1+1)$$

判断前缀和即可。

##### 时间复杂度

时间复杂度：

1. 差分预处理：$\operatorname{O}(S)$

2. 计算单点无人机数量：$\operatorname{O}(n\times m)$

3. 取 `bool` 值：$\operatorname{O}(n\times m)$

4. 预处理前缀和：$\operatorname{O}(n\times m)$

5. 回答：$\operatorname{O}(L)$

总复杂度为：

$$\operatorname{O}(n\times m\times3+S+L)$$

极限数据时间复杂度为：

$$\operatorname{O}(1.1\times10^7)$$

比树状数组快 $\dfrac{1}{3}$。

### 2 代码与记录

```
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 3000
int n;//行数
int m;//列数
int s;//无人机数
int l;//任务数
int a[max_n+2][max_n+2];//矩阵
bool ans;//答案
int main(){
	#ifndef ONLINE_JUDGE
	freopen("c_1.in","r",stdin);
	freopen("c_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	scanf("%d",&s);
	for(register int i=1,x1,y1,x2,y2;i<=s;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		++a[x1][y1];//左上
		++a[x2+1][y2+1];//右下
		--a[x2+1][y1];//左下
		--a[x1][y2+1];//右上
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			if(a[x][y])a[x][y]=1;
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	scanf("%d",&l);
	for(register int i=1,x1,y1,x2,y2;i<=l;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1]>=(x2-x1+1)*(y2-y1+1))puts("Yes");
		else puts("No");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57530635)

By **dengziyue**

---

## 作者：Daniel_xu (赞：0)

# 题意转换
给出一个 $n*m$ 的矩阵，给出 $s$ 次修改，把给定矩阵内的数设为 $1$。再给出 $L$ 次询问，查询给定矩阵内是否均为 $1$。
# 大致思路
由于题目要求区间修改，且不强制在线，可以使用二维差分、前缀和。如果这两个知识点不是很熟练，建议做一下 [P2004 领地选择](https://www.luogu.com.cn/problem/P2004) 和 [P3397 地毯](https://www.luogu.com.cn/problem/P3397)。
# 具体实现
1. 差分记录下所有无人机的覆盖范围。
2. 前缀和得到修改后的数组（为避免重叠，大于 $1$ 的元素统一设为 $1$）。
3. 得到修改后数组的前缀和。
4. 查询时，看给定矩阵内原数组中所有数的和是否等于给定矩阵的元素个数，如果相等，则输出 `Yes`，否则输出 `No`。
# AC代码
注意：不要直接使用 cin 或 cout 进行输入输出，否则一个样例点会 TLE。\
具体实现细节请看代码。

```cpp
#include<iostream>
using namespace std;
const int N=3e3+5;
int d[N][N];//差分数组 
int s[N][N];//前缀和数组 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	//输入 
	int n,m,k;
	cin>>n>>m>>k;
	while(k--){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		//进行差分处理 
		d[x1][y1]++;
		d[x1][y2+1]--;
		d[x2+1][y1]--;
		d[x2+1][y2+1]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			//差分数组的前缀和，得到修改后的数组 
			d[i][j]+=d[i-1][j]+d[i][j-1]-d[i-1][j-1];
			if(d[i][j]){//有覆盖 
				s[i][j]=1;
			}else{//无覆盖 
				s[i][j]=0;
			}
			//原数组的前缀和 
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
	//查询 
	int q;
	cin>>q;
	while(q--){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		//给定矩阵中覆盖的个数 
		int s1=s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
		//给定矩阵应覆盖个数（矩阵元素个数） 
		int s2=(x2-x1+1)*(y2-y1+1);
		if(s1==s2){//全覆盖 
			puts("Yes");
		}else{//未全覆盖 
			puts("No");
		}
	} 
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 思路
$n$ 和 $m$ 只有 $3 \times 10^3$，并不大，$O(nm)$ 是能跑过的。

很容易想到二维差分。每次把 $(a_1,b_1)$ 到 $(a_2,b_2)$ 这个范围内全部 $+1$ 即可。

然后构造差分数组的前缀和（设为 $a$），也就是把它还原成正常的数组。此时 $a(i,j)$ 表示 $(i,j)$ 被覆盖的次数。然而我们只关心它是否被覆盖，所以把 $a$ 转换成 $01$ 数组，$0$ 表示没有覆盖，$1$ 表示有。

但我们要求的一个区间是否被覆盖，而不是一个单点。  
于是再构造 $a$ 的前缀和（还是叫 $a$），此时 $a(i,j)$ 表示 $(1,1)$ 到 $(i,j)$ 这个范围内被覆盖的点的数量。  
这样就能求一个区间的和了。

```cpp
#include <cstdio>
using namespace std;

const int maxn=3e3+5,maxm=3e3+5;
int n,m,a[maxn][maxm];
int s,L;
int main(){
	scanf("%d%d%d",&n,&m,&s);
	while(s--){
		int a1,b1,a2,b2;
		scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
		a[a1][b1]++;
		a[a2+1][b1]--;
		a[a1][b2+1]--;
		a[a2+1][b2+1]++;//二维差分
	}
	scanf("%d",&L);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//恢复成正常的数组
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=(bool)a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//构建前缀和数组
	while(L--){
		int r1,c1,r2,c2;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		int sum=a[r2][c2]-a[r1-1][c2]-a[r2][c1-1]+a[r1-1][c1-1];
		if(sum==(c2-c1+1)*(r2-r1+1)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
这题可以使用二维差分和二维前缀和来解决。我们可以利用差分统计每个点被多少架无人机覆盖，这就相当于得到了每个点是否被无人机覆盖，若被覆盖则记 $1$，若不被覆盖则记 $0$，然后再求一下前缀和，对于每个重要区域，只需要看一下这个区域的区间和与其面积是否相等即可。
# 参考代码
```cpp
#include<iostream>
using namespace std;
int n,m,s,l,p[(int)3e3+5][(int)3e3+5],q[(int)3e3+5][(int)3e3+5];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	cin>>s;
	int a1,b1,a2,b2;
	for(int i=1;i<=s;i++){
		cin>>a1>>b1>>a2>>b2;
		p[a1][b1]++,p[a1][b2+1]--,p[a2+1][b1]--,p[a2+1][b2+1]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			p[i][j]=p[i][j]+p[i][j-1]+p[i-1][j]-p[i-1][j-1];
			if(p[i][j]) q[i][j]=1;
			q[i][j]=q[i][j]+q[i][j-1]+q[i-1][j]-q[i-1][j-1];
		}
	}
	cin>>l;
	int r1,c1,r2,c2;
	for(int i=1;i<=l;i++){
		cin>>r1>>c1>>r2>>c2;
		if(q[r2][c2]-q[r2][c1-1]-q[r1-1][c2]+q[r1-1][c1-1]==(r2-r1+1)*(c2-c1+1)) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}

```

---

## 作者：liushuaishuai (赞：0)

## 题目大意

在 $x1, x2 \sim y1, y2$ 地方有无人机拍摄，求 $x1, x2 \sim y1, y2$ 地方是否都有无人机拍摄，符合输出 `yes`，不符合输出 `no`。

## 思路

### 思路一

直接把每个点无人机标记为 $1$，之后暴力枚举范围内的每个点，看是否为 $1$。

时间复杂度 $O(nm(l + s))$。

预计得分：$40$。

### 思路二

用二维差分和二维前缀和优化。

#### 二维差分

```cpp
wrj[x1][y1]++;
wrj[x2 + 1][y1]--;
wrj[x1][y2 + 1]--;
wrj[x2 + 1][y2 + 1]++; //差分 
```

和一维前缀一样，就差不多是个容斥原理，题目可参考 [P3397](https://www.luogu.com.cn/problem/P3397)

#### 二维前缀和

```cpp
for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j]; //二维前缀和预处理 
```

二维预处理。

```cpp
	while (l--){ 
		cin >> x1 >> x2 >> y1 >> y2;
		int sum = wrj[x2][y2] - wrj[x1 - 1][y2] - wrj[x2][y1 - 1] + wrj[x1 - 1][y2 - 1]; //二维前缀和求和
        cout << sum << endl;
	} 
```

二维前缀和求和，题目参考 [P2280](https://www.luogu.com.cn/problem/P2280)。

#### 注意

* 开了万能头就不能使用变量名 $y2$。
* 用二维预处理后，有些下标可能大于 $1$，所以先要把大于 $1$ 的数都标记为 $1$，再进行一次预处理（不然会影响二位前缀和求和的结果）。
* 算某个区间应有无人机的数量可以用 $(x2 - x1 + 1) \times (y2 - y1 + 1)$ 来计算。

## 代码

```cpp
#include <bits/stdc++.h>

#define N 3010

using namespace std;

int n, m, s, l, r1, r2, r3, r4, wrj[N][N];

int main(){
	cin.tie(), cout.tie(); //读入读出优化 
	
	cin >> n >> m >> s;
	for (int i = 1; i <= s; i++){
		cin >> r1 >> r2 >> r3 >> r4;
		wrj[r1][r2]++;
		wrj[r3 + 1][r2]--;
		wrj[r1][r4 + 1]--;
		wrj[r3 + 1][r4 + 1]++; //差分 
	} 
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			wrj[i][j] += wrj[i - 1][j] + wrj[i][j - 1] - wrj[i - 1][j - 1]; //二维前缀和 
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (wrj[i][j]) wrj[i][j] = 1;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			wrj[i][j] += wrj[i - 1][j] + wrj[i][j - 1] - wrj[i - 1][j - 1]; //再次统计数量
	
	cin >> l;
	
	while (l--){ 
		cin >> r1 >> r2 >> r3 >> r4;
		int sum = wrj[r3][r4] - wrj[r1 - 1][r4] - wrj[r3][r2 - 1] + wrj[r1 - 1][r2 - 1]; //二维前缀和求和
		
		if (sum == (r3 - r1 + 1) * (r4 - r2 + 1)) cout << "Yes\n"; //是否达到数量 
		else cout << "No\n";
	} 
	return 0;
}
```


---

## 作者：Union_Find (赞：0)

# P7865 「EVOI-RD1」无人机航拍 题解

这道题是道好题，码量不大，但思维量不小。

# First 前置知识

不多，先切了 [这题](https://www.luogu.com.cn/problem/P2280) 和 [这题](https://www.luogu.com.cn/problem/P3397) 再说。

# Second 暴力 + 40 Code

我们先想暴力。那么我们可以用一个数组标记每个点是否被无人机覆盖，然后询问时再枚举是否有点没被覆盖。

这样子时间复杂度为：放置无人机 $O(sn^2)$，查询 $O(Ln^2)$，稳稳的40分。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, m, s, t, a, b, c, d, sum[3005][3005];
int main(){
	scanf ("%lld %lld %lld", &n, &m, &s);
	while (s--){
		scanf ("%lld %lld %lld %lld", &a, &b, &c, &d);
		for (int i = a; i <= c; i++) for (int j = b; j <= d; j++) sum[i][j] = 1;
	}
	scanf ("%lld", &t);
	while (t--){
		scanf ("%lld %lld %lld %lld", &a, &b, &c, &d);
		bool flag = 1;
		for (int i = a; i <= c; i++) for (int j = b; j <= d; j++) if (sum[i][j] == 0) flag = 0;
		if (flag) puts("Yes");
		else puts("No");
	}
	return 0;
}
 
```

# Third 正解 + AC Code

那么上面的代码如何优化呢？可以发现，其实上面代码只做了两件事：二维区间加和二维区间求和。那么就可以用二维差分和前缀和来做了。

二维差分不用多说，值得一提的是二维前缀和部分，求出该部分的和之后，要和面积去比较大小，而且差分完一定要把数组转成 `01矩阵` 再前缀和。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, m, s, t, a, b, c, d, sum[3005][3005];
int main(){
	scanf ("%lld %lld %lld", &n, &m, &s);
	while (s--){
		scanf ("%lld %lld %lld %lld", &a, &b, &c, &d);
		sum[a][b]++, sum[c + 1][d + 1]++;
		sum[a][d + 1]--, sum[c + 1][b]--;
	}
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) sum[i][j] = (bool)(sum[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	scanf ("%lld", &t);
	while (t--){
		scanf ("%lld %lld %lld %lld", &a, &b, &c, &d);
		ll k = sum[c][d] + sum[a - 1][b - 1] - sum[a - 1][d] - sum[c][b - 1];
		if ((c - a + 1) * (d - b + 1) == k) puts("Yes");
		else puts("No");
	}
	return 0;
}

```

---

## 作者：Sternenlicht (赞：0)

思路：

因为 $n,m\le3000$，所以容易想到用二维前缀和与二维差分维护无人机拍摄的覆盖范围。

具体解题步骤：

1. 在读入时，建立二维差分矩阵。

2. 用前缀和将矩阵还原，然后统计被无人机覆盖的地方（覆盖标记为 $1$，没覆盖标记为 $0$）。

3. 对于每组询问，判断矩阵内的数字和是否等于矩阵面积。若相等，则输出 ``Yes``；若不相等，则输出 ``No``。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

const int N = 3e3+100;
int sum[N][N],n,m,s,l;
int main(){
	n=read(),m=read(),s=read();
	for (int i=1,a1,b1,a2,b2;i<=s;i++){
		a1=read(),b1=read(),a2=read(),b2=read();
		sum[a1][b1]++;
		sum[a2+1][b2+1]++;
		sum[a1][b2+1]--;
		sum[a2+1][b1]--;//二维差分 
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)//二维前缀和 
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (sum[i][j])
				sum[i][j]=1;//矩阵赋值为1
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)//二维前缀和 
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	l=read();
	for (int i=1,r1,c1,r2,c2;i<=l;i++){
		r1=read(),c1=read(),r2=read(),c2=read();
		int ans=sum[r2][c2]-sum[r1-1][c2]-sum[r2][c1-1]+sum[r1-1][c1-1];
		if (ans==(r2-r1+1)*(c2-c1+1))puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

