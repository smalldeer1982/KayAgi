# [USACO3.1] 形成的区域 Shaping Regions

## 题目描述

$n$ 个不同颜色且不透明的长方形被放在一张宽为 $a$ 长为 $b$ 的白纸上。它们的边于白纸的边缘平行，且所有的长方形都放置在白纸内。

现在将他们重叠，重叠后会出现不同形状的各种颜色，你需要求出每种颜色的面积。

白纸的左下角的坐标为原点 $(0,0)$，且坐标轴平行于白纸边缘。

## 说明/提示

**样例输入输出 1 解释**

白纸经过各层覆盖后，各种颜色的面积分别为 $91,84,187,38$。

---

**数据规模与约定**

对于 $100\%$ 的数据，$1 \leq n \leq 10^3$，$1 \leq a,b \leq 10^4$，$1 \leq llx,lly,urx,ury \leq a,b$，$1 \leq color \leq n+1$。

## 样例 #1

### 输入

```
20 20 3
2 2 18 18 2
0 8 19 19 3
8 0 10 19 4```

### 输出

```
1 91
2 84
3 187
4 38```

# 题解

## 作者：Lithium_Chestnut (赞：12)

自己贡献的题，自己发一波题解！

这道题和铺地毯想法比较类似。我是用 $\text{dfs}$ 来解。每次循环枚举找到图形的边界点（四边形的四个角），以便求面积。然后开二维数组进行枚举每个图形，最后输出。

还算比较裸的 $\text{dfs}$ 题，适合 $\text{dfs}$ 新手们来切，当然 $\text{dfs}$ 只是一种较简单的写法，别的方法当然也可以切掉这道题。好了，挂上代码！

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][5],area[1001],n;
void dfs(int x1,int y1,int x2,int y2,int color,int deep)
{
	while(deep<=n and (x1>=a[deep][2] or y1>=a[deep][3] or x2<=a[deep][0] or y2<=a[deep][1])) deep++;
	if(deep>n)
    {
    	area[color]+=(x2-x1)*(y2-y1);
    	return;
    }
	if(x1<a[deep][0]) dfs(x1,y1,a[deep][0],y2,color,deep+1),x1=a[deep][0];
	if(y1<a[deep][1]) dfs(x1,y1,x2,a[deep][1],color,deep+1),y1=a[deep][1];
	if(x2>a[deep][2]) dfs(a[deep][2],y1,x2,y2,color,deep+1),x2=a[deep][2];
	if(y2>a[deep][3]) dfs(x1,a[deep][3],x2,y2,color,deep+1),y2=a[deep][3];
}
int A,B,i,j,k;
int main()
{
	scanf("%d%d%d",&A,&B,&n);
	for(i=1;i<=n;i++) scanf("%d%d%d%d%d",&a[i][0],&a[i][1],&a[i][2],&a[i][3],&a[i][4]);
	dfs(0,0,A,B,1,1);
	for(i=1;i<=n;i++) dfs(a[i][0],a[i][1],a[i][2],a[i][3],a[i][4],i+1);
	for(i=1;i<=1000;i++)
    {
		if(area[i]) printf("%d %d\n",i,area[i]);
	}
    return 0;
}
```

---

## 作者：汽水长颈鹿 (赞：5)

这是我第一次发题解，不对的地方请大家指出????

看到这道题觉得和[P2745窗体面积](https://www.luogu.com.cn/problem/P2745)很相似，算是它的弱化版。我用了P2745里学来的方法，可以参考P2745的题解

![分割方块](https://cdn.luogu.com.cn/upload/image_hosting/qcmi41qc.png)
内部的矩形是当前新加入的。枚举原有的矩形，图中即为外围的矩形。一次最多将原有的矩形分成如图四个。分割时如果没有意义就不要分了（体现在if上）。具体的实现在代码中（跑得不是很快，但这题数据量很小也没什么区别）。
## 鄙人的代码
```cpp
#include <tits/stdc++.h>
#define N 1123
using namespace std;

int a,b,n,c,area[N];

struct Rect{
    int xl,yl,xr,yr,cr;
    int area(void){return (xr-xl)*(yr-yl);}
}r[N<<2],rn;

int main(int argc, const char * argv[]) {
    scanf("%d%d%d",&a,&b,&n);
    r[c++]={0,0,a,b,1};
    for(int i=0;i<n;i++,r[c++]=rn){
        scanf("%d%d%d%d%d",&rn.xl,&rn.yl,&rn.xr,&rn.yr,&rn.cr);
        for(int j=0,C=c;j<C;j++)
            if(r[j].cr){
                int &cr=r[j].cr,xl=r[j].xl,yl=r[j].yl,xr=r[j].xr,yr=r[j].yr;
                int x=max(xl,rn.xl),y=max(yl,rn.yl),X=min(xr,rn.xr),Y=min(yr,rn.yr);
                if(x<X&&y<Y){
                    if(x!=xl)r[c++]={xl,y,x,yr,cr};
                    if(y!=yl)r[c++]={xl,yl,X,y,cr};
                    if(X!=xr)r[c++]={X,yl,xr,Y,cr};
                    if(Y!=yr)r[c++]={x,Y,xr,yr,cr};
                    r[j].cr=false;//丢弃
                }
            }
    }
    for(int i=0;i<c;i++)
        area[r[i].cr]+=r[i].area();
    for(int i=1;i<=n+1;i++)
        if(area[i])printf("%d %d\n",i,area[i]);
    return 0;
}

```
就酱

---

## 作者：ZBAA_MKC (赞：4)

首先想要吐槽一下搬题人，实在是太坑了，数据范围与题目完全不符，被卡了很久。

数据范围中写的矩形坐标都不超过纸张的大小，然而事实上第 $2$  组数据和第 $5$ 组数据都出现了矩形范围超过纸张范围的情况，此情况下**纸张外有颜色的部分需要统计，而没颜色的不统计**。一开始我就是因为没考虑这种情况导致 WA $60$ 分。

接下来说解法，由于这道题数据范围不大，再加上数据也非常水，于是可以采用纯暴力方法，开一个 $11000\times11000$ 大的数组（多开 $1000$ 主要是为了处理上面的情况),然后每输入一个举行就在数组上模拟覆盖，最后在遍历整个矩阵，输出答案。

模拟数组使用 `char` 数组，因为用 `int` 会 MLE，而 `char` 数组所占空间为 $115.4$ MB，可以通过本题。

代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;

char c[11001][11001];
int cnt[1002];
int main()
{
	int a, b, n;
	cin >> a >> b >> n;
	for (int i = 0; i < 11000; i++)
	{
		for (int j = 0; j < 11000; j++)
		{
			c[i][j] = '0';//超过纸张范围全部标记为0
		}
	}
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			c[i][j] = '1';
		}
	}
	//上面为初始化
	for (int i = 1; i <= n; i++)
	{
		int x1, y1, x2, y2, op;
		cin >> x1 >> y1 >> x2 >> y2 >> op;
		for (int j = x1 ; j < x2; j++)
		{
			for (int k = y1; k < y2; k++)
			{
				c[j][k] = op + '0';
			}
		}
	}
	for (int j = 0; j < (a + 1000); j++)
	{
		for (int k = 0; k < (b + 1000); k++)
		{
			cnt[c[j][k] - '0']++;
		}
	}
	for (int i = 1; i <= n + 1; i++)
	{
		if (!cnt[i])
		{
			continue; //跳过没有面积的颜色
		}
		printf("%d %d\n", i, cnt[i]);
	}
	return 0;
}
```

---

## 作者：wangyihao0411 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6432)

### 前言

[博客戳这里](https://www.luogu.com.cn/article/hgn7d10p)  
这道题的数据范围不是特别大，因此我们可以考虑使用暴力枚举。

### 思路

显而易见，可以用深搜。  
循环枚举找到四边形的四个顶点，然后求出面积，并开二维数组储存起来。  
面积统计在涂色时解决，**故各点仅需涂色，无需知道具体颜色。**  
最后输出 $color$ 的编号以及所对面积即可。

### 代码

大家最爱的代码来啦！
```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[1001][5],c[1001],ai,bi,i,j,k;
void dfs(int x1,int y1,int x2,int y2,int zh,int xi){
	while(xi<=n&&(x1>=a[xi][2]||y1>=a[xi][3]||x2<=a[xi][0]||y2<=a[xi][1]))
	{
		xi++;
	}
	if(xi>n)
	{
    	c[zh]+=(x2-x1)*(y2-y1);
    	return;
    }
	if(x1<a[xi][0]) 
		dfs(x1,y1,a[xi][0],y2,zh,xi+1),x1=a[xi][0];
	if(y1<a[xi][1]) 
		dfs(x1,y1,x2,a[xi][1],zh,xi+1),y1=a[xi][1];
	if(x2>a[xi][2]) 
		dfs(a[xi][2],y1,x2,y2,zh,xi+1),x2=a[xi][2];
	if(y2>a[xi][3]) 
		dfs(x1,a[xi][3],x2,y2,zh,xi+1),y2=a[xi][3];
}
int main(){
	cin >> ai >> bi >> n;
	for(i=1;i<=n;i++) 
		cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
	dfs(0,0,ai,bi,1,1);
	for(i=1;i<=n;i++) 
		dfs(a[i][0],a[i][1],a[i][2],a[i][3],a[i][4],i+1);
	for(i=1;i<=1000;i++)
		if(c[i]) 
			cout << i << " " << c[i] << endl;
    return 0;
}
```

### update

$2024/6/3$：发布该题解

---

## 作者：小老虎3018 (赞：1)

上来先看数据规模，个数 $n$ 和坐标 $a,b$ 最大值乘积 $10^{11}$

如果不求完美解决，就可以考虑暴力了。

再分析内存空间，不离散化并放置颜色信息，直接存 `short` 的大小约为 190.8 MBytes，超空间。

再次分析题意，考虑优化：**直接从最后一个放的长方形遍历，涂色块计数在涂色时解决，故各点仅需涂色却无需知道具体颜色。**

开O2的话，就可以放心使用`bitset`代替原始数组了。


```cpp
#include<cstdio>
#include<bitset>
#include<iostream>
std :: bitset<10000> f[10000];
int cnt[1002];
short p[1001][5];

int main()
{
    short a, b, n;
    scanf("%hd%hd%hd", &a, &b, &n);
    cnt[1] = a * b;
    for(int i = 1; i <= n; ++ i)
    {
        scanf("%hd%hd%hd%hd%hd", &p[i][0], &p[i][1], &p[i][2], &p[i][3], &p[i][4]);
    }
    for(int i = n; i; -- i) // 从最后一个往前遍历
    {
        for(int j = p[i][0] + 1; j <= p[i][2]; ++ j) // 从样例数据可以看出来区间半开半闭，似乎选一边开都行
        {
            for(int k = p[i][1] + 1; k <= p[i][3]; ++ k){
                if(!f[j][k])
                    f[j][k] = 1,
                    ++ cnt[p[i][4]],
                    (j <= a && k <= b) ? -- cnt[1] : 0; // ***
            }
        }
    }
    for(int i = 1; i <= 1001; ++ i)
        if(cnt[i])
            printf("%d %d\n", i, cnt[i]);
    return 0;
}
```

>$*$ 如果怕被卡，就不要把白纸（颜色 $1$ ）遍历涂色，而是如上求差。可以发现若还有颜色为 $1$ 的矩形覆盖，也不影响计算。（思考颜色为 $1$ 的矩形为何不能特判，不进行涂色遍历）

>**`(j <= a && k <= b)` 是因为 `且所有的长方形都放置在白纸内`这个描述是错的，有矩形跑出白纸了。**

过了？要强一点的数据可以看 [URAL-1147](https://vjudge.net/problem/URAL-1147)

---

## 作者：125125A (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6432)
# 思路
先根据输入覆盖，然后统计每种颜色的数量。

特殊的，纸是可能覆盖到底部白纸外面的，所以数组要开大一点。
[血的教训](https://www.luogu.com.cn/record/176590824)
```
# include <bits/stdc++.h>
using namespace std;

char arr[11001][11001];
int Count[1002];
int a, b, n;

int main (void){
	
	cin >> a >> b >> n;
	
	for (int i = 0; i < 11000; i++){
		for (int j = 0; j < 11000; j++){
			arr[i][j] = '0'; //初始化
		}
	}
    
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			arr[i][j] = '1'; //初始化
		}
	}
	
	for (int i = 1; i <= n; i++){
		int llx, lly, urx, ury, color;
		
		cin >> llx >> lly >> urx >> ury >> color;
		
		for (int j = llx ; j < urx; j++){
			for (int k = lly; k < ury; k++){
				arr[j][k] = color + '0'; //面积覆盖 
			}
		}
	}
	
	for (int i = 0; i < a + 500; i++){
		for (int j = 0; j < b + 500; j++){
			Count[arr[i][j] - '0']++; //统计面积
		}
	}
	
	for (int i = 1; i <= n + 1; i++){
		if (Count[i] == 0){
			continue; //如果该面积没有值，就跳过 
		}

		cout << i << " " << Count[i] << endl;
	}
	
	return 0;
}// 如有错误，请私信
```


当然深搜也能做，~~不过我样例都没过~~。

---

## 作者：a18981826590 (赞：0)

# [P6432 [USACO3.1] 形成的区域 Shaping Regions](https://www.luogu.com.cn/problem/P6432)
## 题意描述
$n$ 个不同颜色且不透明的长方形被放在一张宽为 $a$ 长为 $b$ 的白纸上。它们的边于白纸的边缘平行，且所有的长方形都放置在白纸内。

现在将他们重叠，重叠后会出现不同形状的各种颜色，你需要求出每种颜色的面积。

白纸的左下角的坐标为原点 $(0,0)$，且坐标轴平行于白纸边缘。

根据样例，纸的范围应该为左闭右开。
## 解题思路
1. 先把白纸初始化为 $1$，每读入一张纸就把这张纸范围内改为这张纸的颜色，这样后面的纸就会覆盖前面的纸，最后再遍历一遍白纸，记录下每种颜色的面积。不幸的是，白纸大小最大为 $10^{8}$，开成 `int` 会超过空间限制。
2. 我们可以改进一下做法，把白纸定为 `bool` 类型，用于记录是否已被覆盖，初始为 `false`，优化空间。先把每张纸记录下来，再从最后一张纸开始往前，把这张纸范围内没有被覆盖的部分加到答案中，并把这部分定为已覆盖。最后扫一遍白纸，把仍为 `false` 的部分加到答案 $1$ 中，即没有被任何彩纸覆盖的白纸（不能用白纸总面积减去彩纸答案之和，否则会只有 $60$ 分，会 `WA` 在第二、五个测试点，但我不知道为什么，如果有人知道请在评论区回复一下，谢谢）。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,d[1010],e[1010],f[1010],g[1010],h[1010],m,n,s[1010];
bool c[10010][10010];
int main(){
	ios::sync_with_stdio(0);
	cin>>a>>b>>n;
	for(int i=0;i<n;i++) cin>>d[i]>>e[i]>>f[i]>>g[i]>>h[i];
	for(int i=n-1;i>=0;i--){
		for(int j=d[i];j<f[i];j++){
			for(int k=e[i];k<g[i];k++){
				if(!c[j][k]){
					c[j][k]=1;
					s[h[i]]++;
				}
			}
		}
	}
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(!c[i][j]) s[1]++;
		}
	}
	for(int i=1;i<n+2;i++){
		if(s[i]>0) cout<<i<<' '<<s[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：Cccsk03 (赞：0)

## 解题思路

这道题的数据范围不是特别大，因此我们可以考虑使用暴力枚举，不过这里还是用比较规范的深搜。

循环枚举找到四边形的四个顶点，然后求出面积，并开二维数组储存起来。

最后枚举每个图形，最后输出每个图形的编号和颜色面积即可。


## 代码部分
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1001][5],yuyi[1001],A,B,i,j,k;//定义变量
void dfs(int x1,int y1,int x2,int y2,int zhujunhao,int xiaogan){//深搜部分
	while(xiaogan<=n&&(x1>=a[xiaogan][2]||y1>=a[xiaogan][3]||x2<=a[xiaogan][0]||y2<=a[xiaogan][1])) 
		xiaogan++;
	if(xiaogan>n){
    	yuyi[zhujunhao]+=(x2-x1)*(y2-y1);
    	return;
    }
	if(x1<a[xiaogan][0]) 
		dfs(x1,y1,a[xiaogan][0],y2,zhujunhao,xiaogan+1),x1=a[xiaogan][0];
	if(y1<a[xiaogan][1]) 
		dfs(x1,y1,x2,a[xiaogan][1],zhujunhao,xiaogan+1),y1=a[xiaogan][1];
	if(x2>a[xiaogan][2]) 
		dfs(a[xiaogan][2],y1,x2,y2,zhujunhao,xiaogan+1),x2=a[xiaogan][2];
	if(y2>a[xiaogan][3]) 
		dfs(x1,a[xiaogan][3],x2,y2,zhujunhao,xiaogan+1),y2=a[xiaogan][3];
}
int main(){
	cin>>A>>B>>n;
	for(i=1;i<=n;i++) 
		cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3]>>a[i][4];
	dfs(0,0,A,B,1,1);
	for(i=1;i<=n;i++) 
		dfs(a[i][0],a[i][1],a[i][2],a[i][3],a[i][4],i+1);
	for(i=1;i<=1000;i++)
		if(yuyi[i]) 
			cout<<i<<" "<<yuyi[i]<<endl;//输出
    return 0;
}
```


---

