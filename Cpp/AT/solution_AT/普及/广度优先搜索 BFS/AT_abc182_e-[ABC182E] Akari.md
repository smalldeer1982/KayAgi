# [ABC182E] Akari

## 题目描述

有一个 $H$ 行 $W$ 列的网格，定义 $(i,j)$ 是第 $i$ 行 $j$ 列的方格。

这个网格上有 $N$ 个灯泡和 $M$ 个障碍物，第 $i$ 个灯泡在 $(A_i,B_i)$ 处，第 $i$ 个障碍物在 $(C_i, D_i)$ 处。每个方格保证最多只有一个灯泡或障碍物。

每一个灯泡都会将光照向上下左右四个方向延伸，直至遇到障碍物或到达边界。灯泡所在的方格也会有光照。

请你计算，被光照照到且没有障碍物的方格有多少。

## 样例 #1

### 输入

```
3 3 2 1
1 1
2 3
2 2```

### 输出

```
7```

## 样例 #2

### 输入

```
4 4 3 3
1 2
1 3
3 4
2 3
2 4
3 2```

### 输出

```
8```

## 样例 #3

### 输入

```
5 5 5 1
1 1
2 2
3 3
4 4
5 5
4 2```

### 输出

```
24```

# 题解

## 作者：fangyicheng1216 (赞：2)

本蒟蒻第一次发题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc182_e)

# 首先说思路

 我们可以先定义一个数组，用来表示每个位置当前的情况。因为它有灯，障碍物，光照三种情况，所以我们可以定义一个结构体。然后将三种情况定为“假”。
 
 然后将灯的位置存起来，一个个枚举。将它扫过上下左右四个方向，再遍历一遍就行了。
 
 如果没看懂，代码内有注释可以看。
 
由此我们可以写出代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct st{
	bool za=false/*判断有没有障碍物*/,d=false/*判断有没有灯*/,gz=false/*判断有没有光照*/;
}dt[1501][1501];
int h,m,n,w,deng[10001][2]/*灯的位置*/;
signed main(){
	cin>>h>>w>>n>>m;
	for(int i=0;i<n;i++){
		cin>>deng[i][0]>>deng[i][1];//输入灯的位置 
		dt[deng[i][0]][deng[i][1]].d=true; 
		dt[deng[i][0]][deng[i][1]].gz=true;
		//把这里的灯和光照变成有 
	}
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;//输入障碍物的位置 
		dt[x][y].za=true;
		//把障碍物的判断变成有 
	}
	for(int i=0;i<n;i++){
		//将灯向右照射 
		for(int j=deng[i][0];j<=w;j++){
			if(dt[j][deng[i][1]].za==true) break;
			dt[j][deng[i][1]].gz=true;
		}
		//将灯向左照射 
		for(int j=deng[i][0];j>0;j--){
			if(dt[j][deng[i][1]].za==true) break;
			dt[j][deng[i][1]].gz=true;
		}
		//将灯向下照射 
		for(int j=deng[i][1];j<=h;j++){
			if(dt[deng[i][0]][j].za==true) break;
			dt[deng[i][0]][j].gz=true;
		}
		//将灯向上照射 
		for(int j=deng[i][1];j>0;j--){
			if(dt[deng[i][0]][j].za==true) break;
			dt[deng[i][0]][j].gz=true;
		}
	}
	int ans=0;//ans表示被光照到的地方 
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			//遍历 
			if(dt[i][j].gz==true) ans++;//如果被光照到，ans++ (由于上面没有把障碍物的位置判为有光，所以不需要判断有没有障碍物) 
		}
	}
	cout<<ans;//输出 
	return 0;
}
```
但我发现，这个遍历似乎可以省掉。

所以，最终代码为：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct st{
	bool za=false/*判断有没有障碍物*/,d=false/*判断有没有灯*/,gz=false/*判断有没有光照*/;
}dt[1501][1501];
int h,m,n,w,deng[10001][2]/*灯的位置*/;
signed main(){
	cin>>h>>w>>n>>m;
	for(int i=0;i<n;i++){
		cin>>deng[i][0]>>deng[i][1];//输入灯的位置 
		dt[deng[i][0]][deng[i][1]].d=true; 
		dt[deng[i][0]][deng[i][1]].gz=true;
		//把这里的灯和光照变成有 
	}
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;//输入障碍物的位置 
		dt[x][y].za=true;
		//把障碍物的判断变成有 
	}
	int ans=n;//ans表示被光照到的地方 
	for(int i=0;i<n;i++){
		//将灯向右照射 
		for(int j=deng[i][0];j<=w;j++){
			if(dt[j][deng[i][1]].za==true) break;
			if(dt[j][deng[i][1]].gz==false){//这个和下面的if是省去遍历的关键 
				ans++;
				dt[j][deng[i][1]].gz=true;
			}
		}
		//将灯向左照射 
		for(int j=deng[i][0];j>0;j--){
			if(dt[j][deng[i][1]].za==true) break;
			if(dt[j][deng[i][1]].gz==false){
				ans++;
				dt[j][deng[i][1]].gz=true;
			}
		}
		//将灯向下照射 
		for(int j=deng[i][1];j<=h;j++){
			if(dt[deng[i][0]][j].za==true) break;
			if(dt[deng[i][0]][j].gz==false){
				ans++;
				dt[deng[i][0]][j].gz=true;
			}
		}
		//将灯向上照射 
		for(int j=deng[i][1];j>0;j--){
			if(dt[deng[i][0]][j].za==true) break;
			if(dt[deng[i][0]][j].gz==false){
				ans++;
				dt[deng[i][0]][j].gz=true;
			}
		}
	}
	cout<<ans;//输出 
	return 0;
}
```

~~所以，这道题其实很简单。~~

---

## 作者：hellolin (赞：2)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_abc182_e)

[题面(AtCoder)](https://atcoder.jp/contests/abc182/tasks/abc182_e)

## 思路

拿到这题的第一个想法是打暴力模拟，对每个灯泡都上下左右扫一遍，直至障碍物或者边界，最后得出答案。但时间复杂度是 $O((H+W)\cdot N)$ 级别的，一定会 TLE。

考虑一个简单的优化，既然灯泡只能向上下左右发出光亮，那干脆沿着灯泡发出光亮的方向扫就可以了。

一次扫一个方向，四次扫四个方向，遇到灯泡就准备标记，遇到障碍物就准备停止标记，很好地避免了单独计算灯泡浪费时间的问题。如果不考虑读入，时间复杂度 $O(HW)$。

## 代码

``` cpp
// Coder          : Hellolin
// Time           : 2023-01-25 19:40:17
// Problem        : [ABC182E] Akari
// Contest        : Luogu
// URL            : https://www.luogu.com.cn/problem/AT_abc182_e
// Time Limit     : 2500 ms
// Memory Limit   : 1 GiB

#include <iostream>

const int MAX=1900;
// h, w, n 和 m 意义如题，p 数组存放网格图，x 和 y 用作读入灯泡/障碍物坐标
int h, w, n, m, p[MAX][MAX], x, y, ans;
// z 数组存放每个方格灯光照射情况
bool z[MAX][MAX], f;
int main()
{
    // 加速输入输出
    std::ios::sync_with_stdio(false);

    std::cin>>h>>w>>n>>m;
    
    for(int i=1; i<=n; i++)
    {
        std::cin>>x>>y;
        p[x][y]=1;
    }
    for(int i=1; i<=m; i++)
    {
        std::cin>>x>>y;
        p[x][y]=-1;
    }
    
    // 对于每一行，向右照射灯光
    for(int i=1; i<=h; i++)
    {
        f=0; // 初始没有光
        for(int j=1; j<=w; j++)
        {
            if(p[i][j]==1) f=1; // 有灯泡
            else if(p[i][j]==-1) f=0; // 有障碍物
            
            if(f&&(!z[i][j])) // 可以被光照到但未标记
            {
                z[i][j]=1; // 标记
                ++ans;
            }
        }
    }
    // 对于每一行，向左照射灯光
    for(int i=1; i<=h; i++)
    {
        f=0;
        for(int j=w; j>=1; j--)
        {
            if(p[i][j]==1) f=1;
            else if(p[i][j]==-1) f=0;
            
            if(f&&(!z[i][j]))
            {
                z[i][j]=1;
                ++ans;
            }
        }
    }
    // 对于每一列，向下照射灯光
    for(int j=w; j>=1; j--)
    {
        f=0;
        for(int i=1; i<=h; i++)
        {
            if(p[i][j]==1) f=1;
            else if(p[i][j]==-1) f=0;
            
            if(f&&(!z[i][j]))
            {
                z[i][j]=1;
                ++ans;
            }
        }
    }
    // 对于每一列，向上照射灯光
    for(int j=w; j>=1; j--)
    {
        f=0;
        for(int i=h; i>=1; i--)
        {
            if(p[i][j]==1) f=1;
            else if(p[i][j]==-1) f=0;
            
            if(f&&(!z[i][j]))
            {
                z[i][j]=1;
                ++ans;
            }
        }
    }
    
    // 输出答案
    std::cout<<ans<<std::endl;
    
    return 0;
}

```


---

## 作者：Code_Fish_GoodBye (赞：1)


#### [题目链接](https://www.luogu.com.cn/problem/AT_abc182_e)

## 思路

说实话，这道题其实算模拟，还是挺简单的那种。我们可以定一个 int 类型的二维数组，表示网格。通过不同的数字来表示该方格内不同的类型。然后，使用枚举法模拟网格内灯泡从**上、下、左、右**四个方向模拟光线的运动过程，在过程中增加可被照射到的格子数量，最后输出即可。

------------

## 坑点：
- 灯泡所在的方格也会有光照。
- 被光照照到且没有障碍物的方格有多少。

参考代码（请勿抄袭）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cv[1510][1510],h,w,n,m; //对于cv数组内的每一个数，如果值为0，则代表当前是没有照的空地，如果是1，代表是被照的空地，如果是2，代表灯泡，如果是3，代表是障碍物。
bool flag=false;
long long outp=0;

int main(){
	memset(cv,0,sizeof(cv));//假设全是空地
	scanf("%d%d%d%d",&h,&w,&n,&m);//输入
	outp+=n;//灯泡也算 
	for(int i=1;i<=n;i++){//灯泡 
		int xi,yi;
		scanf("%d%d",&xi,&yi);
		cv[xi][yi]=2;
	}
	for(int i=1;i<=m;i++){//障碍 
		int xi,yi;
		scanf("%d%d",&xi,&yi);
		cv[xi][yi]=3;
	}
	for(int i=1;i<=h;i++){//往右走 
		flag=false;//初始化·不能继续
		for(int j=1;j<=w;j++){
			if(cv[i][j]==2) flag=true;//可以继续（有灯泡）	
			else if(cv[i][j]==3) flag=false;//不可以继续（遇到障碍物）
			if(flag==true&&cv[i][j]==0){//可以照并且未被照 
				cv[i][j]=1;
				outp++;
			}
		} 
	}
	for(int i=1;i<=h;i++){//往左走 
		flag=false;//初始化·不能继续
		for(int j=w;j>=1;j--){
			if(cv[i][j]==2) flag=true;//可以继续（有灯泡）	
			else if(cv[i][j]==3) flag=false;//不可以继续（遇到障碍物）
			if(flag==true&&cv[i][j]==0){//可以照并且未被照 
				cv[i][j]=1;
				outp++;
			}
		} 
	}
	for(int j=w;j>=1;j--){//往上走 
		flag=false;//初始化·不能继续
		for(int i=h;i>=1;i--){
			if(cv[i][j]==2) flag=true;//可以继续（有灯泡）	
			else if(cv[i][j]==3) flag=false;//不可以继续（遇到障碍物）
			if(flag==true&&cv[i][j]==0){//可以照并且未被照 
				cv[i][j]=1;
				outp++;
			}
		} 
	}
	for(int i=w;i>=1;i--){//往下走 
		flag=false;//初始化·不能继续
		for(int j=1;j<=h;j++){
			if(cv[j][i]==2) flag=true;//可以继续（有灯泡）	
			else if(cv[j][i]==3) flag=false;//不可以继续（遇到障碍物）
			if(flag==true&&cv[j][i]==0){//可以照并且未被照 
				cv[j][i]=1;
				outp++;
			}
		} 
	}
	printf("%d",outp);//输出结果
	return 0;
}
```

---

## 作者：Swirl (赞：0)

# 思路简述

**本题是一道比较基础的模拟题**。

考虑到直接暴力枚举会超时，这里我们将暴力的代码优化一下。

建立一个地图二维数组 $a$ ，具体的值代表的意义详见代码注释。

我们可以用 $4$ 次双重循环，进行扫描，方向分别向上、下、左、右。

如果遇到障碍物，当前方向的灯光就会被阻止；

如果遇到灯光，当前方向的灯光就会发出（前提是之前没有灯光发向这边或被阻挡）；

否则遇到空地就可以将当前的灯的状态赋值给空地的状态了。

思路部分完结。

# 代码及注释

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1505][1505];
/*a代表地图数组，
  0代表黑的空位，
  1代表灯泡，
  2代表障碍物,
  3代表亮的空位。
 */
int n, m;
int q1, q2;

int main() {
	int ans = 0;
	cin >> n >> m >> q1 >> q2;
	while (q1--) {
		int x, y;
		cin >> x >> y;
		a[x][y] = 1;
		ans++;
	}
	while (q2--) {//输入障碍物位置
		int x, y;
		cin >> x >> y;
		a[x][y] = 2;
	}
	bool haveLight = false;//使用haveLight变量记录是否有光
	for (int i = 1; i <= n; i++) {//向右扫
		haveLight = false;
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 2) {
				haveLight = false;
				continue;
			}
			if (a[i][j] == 1) {
				haveLight = true;
				continue;
			}
			if (a[i][j] == 3) continue;
			if (haveLight && a[i][j] == 0) a[i][j] = 3, ans++;
		}
	}
	for (int i = 1; i <= n; i++) {//向左扫
		haveLight = false;
		for (int j = m; j >= 1; j--) {
			if (a[i][j] == 2) {
				haveLight = false;
				continue;
			}
			if (a[i][j] == 1) {
				haveLight = true;
				continue;
			}
			if (a[i][j] == 3) continue;
			if (haveLight && a[i][j] == 0) a[i][j] = 3, ans++;
		}
	}
	for (int j = 1; j <= m; j++) {//向下扫
		haveLight = false;
		for (int i = 1; i <= n; i++) {
			if (a[i][j] == 2) {
				haveLight = false;
				continue;
			}
			if (a[i][j] == 1) {
				haveLight = true;
				continue;
			}
			if (a[i][j] == 3) continue;
			if (haveLight && a[i][j] == 0) a[i][j] = 3, ans++;
		}
	}
	for (int j = 1; j <= m; j++) {//向上扫
		haveLight = false;
		for (int i = n; i >= 1; i--) {
			if (a[i][j] == 2) {
				haveLight = false;
				continue;
			}
			if (a[i][j] == 1) {
				haveLight = true;
				continue;
			}
			if (a[i][j] == 3) continue;
			if (haveLight && a[i][j] == 0) a[i][j] = 3, ans++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：0)

# [原题](https://www.luogu.com.cn/problem/AT_abc182_e)
我的代码好慢……

---
### 分析&思路

一个最暴力的思路是枚举每一个灯泡，并标记上它四周能照亮的位置，最后统计，时间复杂度是 $O((H + W) \times N)$，或许不会 TLE（毕竟这题时限足足有 2.5s），但这毕竟是暴力做法，我们还是来谈一谈优化。

既然我们可以枚举每个灯泡，那么，何不枚举每种方向呢？

因此优化方案可以是枚举每种灯泡可照亮的方向，每次用一个变量记录当前遍历到的行（列）是否要标记（有灯泡且未遇到石头），有就将此处标记，并将变量设为要，若此处是石头，则将变量设为不要。最后再统计一遍被标记的位置，累加即可。

这样可以将时间复杂度降到 $O(HW)$，可以通过此题。

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int h , w , n , m , a , b , c , d , mp[1505][1505] , ans;
int main()
{
    cin >> h >> w >> n >> m;
    for (int i = 1 ; i <= n ; i++) {cin >> a >> b; mp[a][b] = 1;}
    for (int i = 1 ; i <= m ; i++) {cin >> c >> d; mp[c][d] = 2;}

    for (int i = 1 ; i <= w ; i++)
    {
        bool flag = false;
        for (int j = h ; j >= 1 ; j--)
        {
            if (mp[j][i] == 1) flag = true;
            else if (mp[j][i] == 2) flag = false;
            else if (flag) mp[j][i] = 3;
        }
    }
    
    for (int i = 1 ; i <= w ; i++)
    {
        bool flag = false;
        for (int j = 1 ; j <= h ; j++)
        {
            if (mp[j][i] == 1) flag = true;
            else if (mp[j][i] == 2) flag = false;
            else if (flag) mp[j][i] = 3;
        }
    }

    for (int i = 1 ; i <= h ; i++)
    {
        bool flag = false;
        for (int j = w ; j >= 1 ; j--)
        {
            if (mp[i][j] == 1) flag = true;
            else if (mp[i][j] == 2) flag = false;
            else if (flag) mp[i][j] = 3;
        }
    }

    for (int i = 1 ; i <= h ; i++)
    {
        bool flag = false;
        for (int j = 1 ; j <= w ; j++)
        {
            if (mp[i][j] == 1) flag = true;
            else if (mp[i][j] == 2) flag = false;
            else if (flag) mp[i][j] = 3;
        }
    }

    for (int i = 1 ; i <= h ; i++)
        for (int j = 1 ; j <= w ; j++)
            if (mp[i][j] == 3 || mp[i][j] == 1) ++ans;
    cout << ans;
    return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/114390081)

---

## 作者：Dehydration (赞：0)

### 前言:

挺水一道题，但是看起来题解里面没有我这个思路，我的思路感觉最好理解。

[problem](https://www.luogu.com.cn/problem/AT_abc182_e)。


### 思路：

题目挺好理解，$\mathcal O(WHN)$ 的算法也好理解，就是模拟一遍，但显然会 TLE。

考虑 $\mathcal O(WH)$ 算法，一共搜 $4$ 遍，从左到右，右到左，上到下和下到上。

例举从左到右方法：从开头遍历到结尾，如果格子左边有灯泡且中间无障碍物，就将此点标记为可用。判断左边有无灯泡方法：用 $flag$ 记录，详见代码。

其它同理。

最后答案就是可用格子数量。

### 代码：


从左到右如果不理解可以看代码注释，有专门解释。
```
#include<bits/stdc++.h>
using namespace std;
int H,W,N,M,x,y,ans=0;
int a[15005][15005],ok[15005][15005];//定义，好像数组开大了 
int main()
{
	cin.tie(0);cout.tie(0);
	cin>>H>>W>>N>>M;
	for(int i=1;i<=N;i++)//灯泡 
	{
		cin>>x>>y;
		a[x][y]=1;
	}
	for(int i=1;i<=M;i++)//石子 
	{
		cin>>x>>y;
		a[x][y]=2;
	}
	for(int i=1;i<=H;i++)//遍历从左到右，从右到左 
	{
		int flag=0;
		//详细解释从左到右 
		for(int j=1;j<=W;j++)
		{
			if(a[i][j]==0)//如果没有找到过 
			{
				ok[i][j]|=flag;//相当于 if(ok[i][j]||flag)ok[i][j]=1; 标记 
			}else
			if(a[i][j]==1)//否则这是灯泡 
			{
				flag=1;//flag表示左边有灯泡 
				ok[i][j]|=flag;
			}else
			flag=0;//a[i][j]==2，表示有障碍物/kk 
		}
		flag=0;
		for(int j=W;j>=1;j--)
		{
			if(a[i][j]==0)
			{
				ok[i][j]|=flag;
			}else
			if(a[i][j]==1)
			{
				flag=1;
				ok[i][j]|=flag;
			}else
			flag=0;
		}
	}
	for(int j=1;j<=W;j++)//遍历从上到下，从下到上 
	{
		int flag=0;
		for(int i=1;i<=H;i++)
		{
			if(a[i][j]==0)
			{
				ok[i][j]|=flag;
			}else
			if(a[i][j]==1)
			{
				flag=1;
				ok[i][j]|=flag;
			}else
			flag=0;
		}
		for(int i=H;i>=1;i--)
		{
			if(a[i][j]==0)
			{
				ok[i][j]|=flag;
			}else
			if(a[i][j]==1)
			{
				flag=1;
				ok[i][j]|=flag;
			}else
			flag=0;
		}
	}
	for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)ans=ans+ok[i][j];//统计 
	cout<<ans;
}
```
完美撒花！

---

## 作者：liaiyang (赞：0)

如果暴力直接扫的话，时间复杂度为$O((H+W)N)$，会T掉

我们每次向一个方向扫，每一行遇见灯泡就开始，遇见障碍物就终止，扫四个方向，时间复杂度为$O(HW)$
```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=1510;
int h,w,n,m; 
int a[N][N];
int flag,ans;
main(){
	cin>>h>>w>>n>>m;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[x][y]=1;
	} 
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		a[x][y]=-1;
	}
	for(int i=1;i<=h;i++){
		flag=0; 
		for(int j=1;j<=w;j++){
			if(a[i][j]==1) flag=2;
			if(a[i][j]==-1) flag=0;
			if(a[i][j]==0) a[i][j]=flag;
		}
	} 
	for(int j=1;j<=w;j++){
		flag=0;
		for(int i=1;i<=h;i++){
			if(a[i][j]==1) flag=2;
			if(a[i][j]==-1) flag=0;
			if(a[i][j]==0) a[i][j]=flag;
		}
	}
	for(int i=1;i<=h;i++){
		flag=0;
		for(int j=w;j>=1;j--){
			if(a[i][j]==1) flag=2;
			if(a[i][j]==-1) flag=0;
			if(a[i][j]==0) a[i][j]=flag;
		}
	}
	for(int j=1;j<=w;j++){
		flag=0;
		for(int i=h;i>=1;i--){
			if(a[i][j]==1) flag=2;
			if(a[i][j]==-1) flag=0;
			if(a[i][j]==0) a[i][j]=flag;
		}
	}
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) if(a[i][j]==1||a[i][j]==2) ans++;
	cout<<ans<<endl;
	return 0;
}
```

---

