# [NOISG 2018 Finals] Collecting Mushrooms

## 题目背景

译自 [NOISG 2018 Finals A. Collecting Mushrooms](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/collectmushrooms)。

## 题目描述

螃蟹 Lim Li 在她的花园里打造了一个蘑菇种植园。这个蘑菇种植园可以看成一个 $R$ 行 $C$ 列的网格，其中每一格要么是空的，要么有一朵蘑菇，要么有一个洒水器。

举个例子，一个 $R=5,C=5$ 的蘑菇种植园可能是长这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/qqn2ssqx.png)

一朵蘑菇和一个洒水器之间的距离被定义为它们的横坐标差的绝对值与纵坐标差的绝对值的较大值。换句话说，假设一朵蘑菇位于 $X_m$ 行 $Y_m$ 列，一个洒水器位于 $X_s$ 行 $Y_s$ 列，那么它们之间的距离为 $\max(|X_m-X_s|,|Y_m-Y_s|)$。

一个洒水器只能浇到距离自己不超过 $D$ 的蘑菇。下图展示了 $D=1$ 时洒水器可以浇到的区域：

![](https://cdn.luogu.com.cn/upload/image_hosting/sr5w3lov.png)

一朵蘑菇如果可以被至少 $K$ 个洒水器浇到，则我们称它是**好蘑菇**。你需要帮 Lim Li 计数在她的蘑菇种植园里有多少朵**好蘑菇**。

## 说明/提示

### 样例 #1 解释

所有洒水器可以浇到的距离范围都是 $1$，也就是每个洒水器都能且仅能洒到与自己八连通的格子。只有位于 $(2,2)$ 的蘑菇可以被浇到水。

这组样例满足子任务 $3,4,6$。

### 样例 #2 解释

唯一的洒水器可以浇到的距离范围是 $4$，所以可以浇到所有蘑菇。

这组样例满足子任务 $1,2,4,6$。

### 样例 #3 解释

所有蘑菇都需要被两头的洒水器浇到才能成为**好蘑菇**。因为洒水器可以浇到的距离范围都是 $5$，所以只有从左往右第二朵和第三朵蘑菇满足**好蘑菇**的要求。

这组样例满足子任务 $4,5,6$。

### 样例 #4 解释

因为洒水器可以浇到的距离范围都是 $2$，所以只有位于 $(2,2)$ 和 $(5,4)$ 的蘑菇可以同时被两个洒水器浇到。

这组样例满足子任务 $4,6$。

### 子任务

对于 $100\%$ 的数据，$2\le RC\le 5\times 10^5$，$1\le D\le \max(R,C)$，$1\le K\le RC$。保证种植园中至少有一朵蘑菇和一个洒水器。

| 子任务 | 得分 | 数据范围及特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $9$ | $1\le R,C\le 100$，$D=\max(R,C)$，$K=1$ |
| $2$ | $10$ | $1\le R,C\le 100$，$D=\max(R,C)$ |
| $3$ | $18$ | $1\le R,C\le 100$，$D=1$，$K=1$ |
| $4$ | $23$ | $1\le R,C\le 500$，洒水器和蘑菇的数量均少于 $500$ |
| $5$ | $19$ | $R=1$ |
| $6$ | $21$ | 无特殊限制 |


## 样例 #1

### 输入

```
5 5 1 1
....M
.M...
..S..
.S...
...M.```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4 4 1
....
.M..
..MM
...S```

### 输出

```
3```

## 样例 #3

### 输入

```
1 8 5 2
SM..MM.S```

### 输出

```
2```

## 样例 #4

### 输入

```
5 5 2 2
....M
.M...
..S..
.S...
...M.```

### 输出

```
2```

# 题解

## 作者：Linyijun_ (赞：7)

首先这个题目用暴力去写肯定拿不了满分（会超时）。


---

对于如何求正解，我们知道洒水器的位置，以及范围，就可以使用二维差分来求解（具体的可参考[ P3397 地毯](https://www.luogu.com.cn/problem/P3397)），只不过这个矩形的左下角和右下角需要我们自己去算（还要注意边界）。


---

这个题目还要注意个令人无语的点，就是数组的设置，建议输完长宽后再建立，再加初始化就行。


---

下面是我的代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,d,k,ans;
int main(){
	cin>>r>>c>>d>>k;
	int a[r+10][c+10];
	char p[r+10][c+10];
	memset(a,0,sizeof(a));//初始化 
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>p[i][j];
			if(p[i][j]=='S'){
				int x1,y1,x2,y2;
				x1=max(1,i-d);
				x2=min(r,i+d);
				y1=max(1,j-d);
				y2=min(c,j+d);//防超边界 
				a[x1][y1]++;
				a[x1][y2+1]--;
				a[x2+1][y1]--;
				a[x2+1][y2+1]++;//二维差分 
			}
		}
	}for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
			if(p[i][j]=='M'&&a[i][j]>=k)ans++;//求答案 
		}
	}cout<<ans;
	return 0;
}
```
这是本~~蒟蒻~~第一次写题解，不喜勿喷。

---

## 作者：__SSY__ (赞：5)

**[P11594 题目传送门](https://www.luogu.com.cn/problem/P11594)**
## 说点闲话:
本篇思路参考了其他大佬的题解，~~毕竟我只是个蒟蒻~~。\
蒟蒻第一次写题解，有哪些不完善的地方望各位大佬海涵。\
**感谢 [GLr137](https://www.luogu.com.cn/user/1027540)、[axy2414fujingze](https://www.luogu.com.cn/user/1365329) 两位大佬的指导。**
## 题意：
给你一个包含蘑菇和洒水器的花园地图，求出有多少朵蘑菇能被 $k$ 个洒水器浇到。
## 思路:
   - 方案 1 —— 暴力（60pts）：
  
     这样过不了，CODE 就不放了。
  - 方案 2 —— 二维差分（正解）：

    利用**二维差分 + 前缀和**实现一个数组，存放每个位置被浇到过多少次，如果这个位置被浇到过大于等于 $k$ 次，且这里有蘑菇，那么答案加一。

  ### AC CODE：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int ans=0;
  int main(){
  	int r,c,d,k;
  	cin>>r>>c>>d>>k;
  	char a[r+1][c+1];//这里知道了r和c之后再创建数组避免a[50000][50000]报RE
  	int sum[r+1][c+1];//同上
      memset(sum,0,sizeof(sum));//差分数组初始化
  	for(int i=1;i<=r;i++)
  		for(int j=1;j<=c;j++){
  			cin>>a[i][j];//读入地图
  			if(a[i][j]=='S')//差分设置
  				sum[i][j]=1;
  		}
  	for(int i=1;i<=r;i++)
  		for(int j=1;j<=c;j++)
  			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//前缀和
  	for(int i=1;i<=r;i++)
          for(int j=1;j<=c;j++)
          	if(a[i][j]=='M'){
              	int x1=max(i-d,1),y1=max(j-d,1),x2=min(i+d,r),y2=min(j+d,c);//与边界取min，max防止数组越界 
      			int s=sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];	//当前位置被浇的次数
                  if(s>=k)
                  	ans++; //满足条件答案加一
  	        }
  	cout<<ans;
  	return 0;
  }
```

---

## 作者：_Punainen_ (赞：3)

~~卡了我半天的一道题，幸好中途升黄了。~~

---

## 解题思路

当我们看到题目中的 $r \times c$，以及 $d$ 范围，便容易知道暴力明显不是正解（暴力时间复杂度大约为 $O(rcd^2)$, 在这种情况下明显会超时），预估得分仅为 $60$。

对于正解，通过~~结合算法标签~~谨慎的思考，题目中的范围可以转换为求蘑菇范围内的洒水器个数，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rzepj7fr.png)

我们容易想到，将暴力的 $O(d^2)$ 的时间复杂度转换为 $O(1)$ 即可通过，用前缀和优化即可。

对于本题最恶心的地方，$r$ 和 $c$ 并没有给出各自的范围，而是给出了它们的乘积，如果我们开一个 $O(r^2d^2)$ 的数组，$25 \times 10^{10}$ 空间爆得彻彻底底。所以我们采用动态数组维克托的方式解决 ~~(我才不用低级的主函数创建数组呢 Owo)~~。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a[500000],s[500000];
int main(){
	int r,c,d,k,sum=0;int ans=0;
	char ch;
	cin>>r>>c>>d>>k;
    for(int j=1;j<=c;j++)a[0].push_back(0);
	for(int i=1;i<=r;i++){
        a[i].push_back(0);
		for(int j=1;j<=c;j++){
			cin>>ch;
			if(ch=='M')a[i].push_back(1);
			else if(ch=='S')a[i].push_back(2);
            else a[i].push_back(0);
		}
    }
    for(int j=0;j<=c;j++)s[0].push_back(0);
	for(int i=1;i<=r;i++){
        s[i].push_back(0);
        for(int j=1;j<=c;j++)s[i].push_back(s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(a[i][j]==2));
    }//洒水器数量前缀和 
    //for(int i=0;i<=n;i++,cout<<endl)for(int j=0;j<=n;j++)cout<<a[i][j]<<" ";
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(a[i][j]==1){//前缀和计算范围内的洒水器个数 
				int sum=s[min(r,i+d)][min(c,j+d)]+s[max(0,i-d-1)][max(0,j-d-1)]-s[max(0,i-d-1)][min(c,j+d)]-s[min(r,i+d)][max(0,j-d-1)];//左上右下 
				if(sum>=k){
					ans++;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

~~又臭又长~~。

---

## 作者：niuniudundun (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P11594)

# 题目大意

在 $R$ 行 $C$ 列的字符数组中计算距离为 $D$ 中 `S` 数量大于 $K$ 的个数。

# 解法

考虑二维前缀和，如果你不会前缀和，可以去搜百度，或点[这里](https://www.luogu.com.cn/article/w0c4dobn)。

显然 $RC\le 5\times 10^5$ 不能开数组，否则会有个点 MLE，只能知道 $R,C$ 后开数组。

如果暴力计算洒水器的个数复杂度 $O(D^2RC)$，会 TLE。使用前缀和优化。

设地图为 $a$，有一个前缀和数组 $s$。在输入时如果 $a_{i,j}=\texttt{S}$，那么令 $s_{i,j}$ 为 $1$，否则为 $0$。

随后跑一遍 $s$。对于每个 $s_{i,j}$ 加上以 $(i,j)$ 左下角的矩阵和，公式如下：$s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}$。如何计算呐？可以去搜百度。

随后遍历数组 $a$，如果 $a_{i,j}$ 是蘑菇，则计算以 $(i-d,j-d)$ 到 $(i+d,j+d)$ 的矩阵和。这时便用上了二维前缀和：

定义四个坐标，令 $x_1=\max(i-d,1),y_1=\max(j-d,1),x_2=\min(i+d,r),y_2=\min(j+d,c)$，使用公式 $s_{x_2,y_2}-s_{x_1-1,y_2}-s_{x_2,y_1-1}+s_{x_1-1,y_{1}-1}$（点[这里](https://www.luogu.com.cn/article/w0c4dobn)），可以 $O(1)$ 计算这个矩阵和，随后计算这个矩阵和是否大于 $K$，大于说明有好蘑菇，计数器加一。

代码：

复杂度：$O(RC)$。

```cpp
#include<iostream>
using namespace std;
const int maxn=10000;
int r,c,d,k;
int ans=0;
int main(){
	cin>>r>>c>>d>>k;
	char a[r+1][c+1];
	long long s[r+1][c+1];
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>a[i][j];
			if(a[i][j]=='S'){
				s[i][j]=1;
			}else{
				s[i][j]=0;
			}
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(a[i][j]=='M'){
				int x1=max(i-d,1),y1=max(j-d,1),x2=min(i+d,r),y2=min(j+d,c);//min 和 max 主要是为了不越界
				int sum=s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
				if(sum>=k){
					ans++;
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：GLr137 (赞：3)

难度约为中位橙。

我们可以轻易发现，每一个洒水器的喷洒范围是以洒水器为中心的边长为 $ 2D + 1 $ 的正方形，我们建立一个二维数组，模拟蘑菇种植园，令第 $ i $ 行第 $ j $ 列为这一个点位能被多少个洒水器洒到。再遍历每一个洒水器，将洒水器的喷洒范围内每一个位置都增加 $ 1 $，但是时间复杂度太高。但是我们发现增加时每一个点的增加值是一样的，并且喷洒范围是一个正方形，所以我们自然可以用到二维差分，每次将差分数组的左上一格、左下再向下一格、右上再向右一格、右下再向右下一格的位置分别进行加一、减一、减一、加一的操作，最后求出差分数组前缀和再依次判断每个蘑菇即可。

不知道差分和前缀和的可以点[这里](https://oi-wiki.org/basic/prefix-sum/)，不知道二维差分的可以点[这里](https://zhuanlan.zhihu.com/p/439268614)。注意本题没有具体给出 $ R $ 和 $ C $ 的上限，所以我们可以使用动态数组，也可以等读入后再建立数组。

```cpp
# include <bits/stdc++.h>
using namespace std;
int r, c, d, k, x, ans;
char ch;
vector <char> sz[500005];
int main (){
    cin >> r >> c >> d >> k;
    int sz2[r + 5][c + 5];
    memset(sz2, 0, sizeof(sz2));
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            cin >> ch;
            sz[i].push_back(ch);
        }
    }
    for (int i = 1; i <= r; i++){
        x = 0;
        for (auto l : sz[i]){
            x++;
            if (l == 'S'){
                sz2[max(1, i - d)][max(1, x - d)] += 1;
                sz2[max(1, i - d)][min(c, x + d) + 1] -= 1;
                sz2[min(r, i + d) + 1][max(1, x - d)] -= 1;
                sz2[min(r, i + d) + 1][min(c, x + d) + 1] += 1;
            }
        }
    }
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            sz2[i][j] = sz2[i][j] + sz2[i - 1][j] + sz2[i][j - 1] - sz2[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= r; i++){
        x = 0;
        for (auto j : sz[i]){
            x++;
            if (j == 'M' && sz2[i][x] >= k){
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Kun_is_Me (赞：2)

### 首先审题。

简化后的题意：给定一个 $R\times C$ 的网格及 $K$，每个格子有可能为 `.`，$M$ 或 $S$，且给定每一个 $S$ 的覆盖范围 $D$，试求出有多少个 $M$ 能被至少 $K$ 个 $S$ 覆盖到。

~~似乎更复杂了呢。~~

### 给出解法

首先我们必须知道，暴力肯定会超时。（这不废话吗。）

对于每一个洒水器能覆盖到的范围，我们只要知道每一个洒水器的坐标以及覆盖范围，就可以使用二维差分进行求解。

二维差分不简简单单嘛，看到这道题的应该都会吧。（~~不会的也不会看到这道题~~）

需要注意的坑点：

1. 注意矩阵的边界及左上、右下顶点的坐标
2. 数组设置。建议是输入完 $R,C$ 以后再建立。
3. 由 2，我们还需要注意到数组的初始化以及大小。在 `main` 函数中建立数组一定要记得初始化，而且主函数内存栈非常小，尽量开到 $[R+1][C+1]$ 就好，不要像我这样，数据范围 1e5 但是作死开 114514 的数组 :)

下面给出 AC 代码。（伏笔！）
```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,d,k,ans=0;
int main()
{
	ios::sync_with_stdio(false);//装杯使用，可以加快 cin 和 cout 的速度，不会的还是用 scanf 和 printf 吧 
	cin.tie(0),cout.tie(0);//同上 
	cin>>r>>c>>d>>k;
	int a[r+1][c+1];//数组开小点，能塞得下就好，不要太大 
	memset(a,0,sizeof(a));//记得初始化！ 
	char mp[r+1][c+1];//记录网格 
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			cin>>mp[i][j];
			if(mp[i][j]=='S')
			{
				int x1,y1,x2,y2;
				x1=max(1,i-d);
				x2=min(r,i+d);
				y1=max(1,j-d);
				y2=min(c,j+d);
				a[x1][y1]++;
				a[x1][y2+1]--;
				a[x2+1][y1]--;
				a[x2+1][y2+1]++;//简单的二维差分 
			}
		}
	for(int i=1;i<=r;i++) for(int j=1;j<=c;j++){a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];if(mp[i][j]=='M'&&a[i][j]>=k)ans++;}
	cout<<ans;//老校长都懂的输出 
	return 0;//华美结束 
}
```

今天的题解就......

欸停停停。等我一下，这里有一个小问题。

直接复制上面那篇代码交了的举一下手我看看。

没猜错的话你们应该得到了下面的结果：

[《五彩斑斓》](https://www.luogu.com.cn/record/200555517)

实际上还有一个小问题：$[R+1][C+1]$ 的数组还是太小了！

那么我们就可以开到 $[R+10][C+10]$，反正内存也不会爆。

真正的 AC 代码就是上面那一篇改一下数组大小，这里就不放了。

[附上 AC 记录](https://www.luogu.com.cn/record/200555790)，免得你们又在说这代码有问题。觉得有问题的自行比对查看，我开了代码公开计划。

今天的题解就到这里，我要去赶作业 ddl 了。Bye!

---

## 作者：longyitongxue (赞：2)

这道题我们先要考虑数组可不可以建立一个 $(5\times10^5)\times(5\times10^5)$ 的数组。题目的空间大小是 $\text{512MB}$，一个 `char` 字符的空间是 $\text{1B}$，最后算出来的答案是二十万兆左右。这很显然会炸。所以我们需要用 `map<int,map<int,char>>` 类型。

接下来就是题目该怎么做了。

找到所有蘑菇，找周围洒水器，找到一个 $+1$，最后判断洒水器数量是否比 $K$ 大，有的话就是好蘑菇。当然，还要优化，不然会导致 TLE。我们发现，数周围洒水器数量可以用二维前缀和替代，二维前缀和数组用 `map<int,map<int,int>>` 类型。

上代码：

```cpp
#include<iostream>
#include<map>
using namespace std;
map<int,map<int,char>> a;
map<int,map<int,int>> sum;
int main(){
    int n,m,d,k,ans=0;
    cin>>n>>m>>d>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            sum[i][j]=(a[i][j]=='S')+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='M'){
				if(sum[min(i+d,n)][min(j+d,m)]-sum[max(i-d,1)-1][min(j+d,m)]-sum[min(i+d,n)][max(j-d,1)-1]+sum[max(i-d,1)-1][max(j-d,1)-1]>=k){ 
					ans++;
				}
			}
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```
好心的管理员你就通过一下吧！

---

## 作者：syx_2014 (赞：2)

位于 $a_{x,y}$ 洒水器能浇灌在左上为 $a_{x-d,y-d}$，右下为 $a_{x+d,y+d}$ 的矩阵里的所有蘑菇，那位于 $a_{x,y}$ 蘑菇也能被在左上为 $a_{x-d,y-d}$，右下为 $a_{x+d,y+d}$ 的矩阵里的所有洒水器浇灌。

我们可以求以 $a_{x,y}$，也就是以蘑菇位置为中心的左上为 $a_{x-d,y-d}$，右下为 $a_{x+d,y+d}$ 的矩阵里有多少个洒水器。

暴力肯定是不行的，既然是对矩阵求和，那就可以想出二维前缀和。

枚举数组中每个位置，如果是 $\mathtt{M}$ 那就求出以它为中心的左上为 $a_{x-d,y-d}$，右下为 $a_{x+d,y+d}$ 的矩阵里的水壶的数量。

所以我们把水壶位置设为一，其他的位置设为零即可。

### 二维前缀和

求 $a_{i,j}$ 二维前缀和就是求：

$$
a_{1,1}+a_{1,2}+\cdots + a_{1,j}+
$$
$$
a_{2,1}+a_{2,2}+\cdots + a_{2,j}+
$$
$$
a_{3,1}+\cdots
$$
$$
\vdots
$$
$$
a_{i,1}+a_{i,2}+\cdots + a_{i,j}
$$

求 $a_{i,j}$ 的二维前缀和可以用 ```s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];``` 求。

而左上为 $a_{i1,j1}$，右下为 $a_{i2,j2}$ 的矩阵的和就可以用 ```s[i2][j2]-s[i1-1][j2]-s[i2][j1-1]+s[i1-1][j1-1];``` 求啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,d,k; 
int main(){
	cin>>r>>c>>d>>k;
// 如果事先知道 r 和 c 的数据范围那就可以直接开在主函数外，一般还是建议开在主函数外的。
	char mapx[r+110][c+110];
	int a[r+110][c+110];
	int sum[r+110][c+110];
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>mapx[i][j];
			if(mapx[i][j]=='S') a[i][j]=1;
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+a[i][j];
		}
	}
	int cnt=0;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(mapx[i][j]=='M'){
				int i1=min(i+d,r),i2=max(i-d,1),j1=min(j+d,c),j2=max(j-d,1);
				long long summ=sum[i1][j1]-sum[i1][j2-1]-sum[i2-1][j1]+sum[i2-1][j2-1];
				if(summ>=k) cnt++;
			}
		}
	}
	cout<<cnt<<'\n';
	return 0;
}
```

---

## 作者：John2014 (赞：1)

# P11594 [NOISG2018 Finals] Collecting Mushrooms 题解

## 思路

暴力就是找到所有洒水器，然后把洒水器周围的蘑菇被浇水的次数 $+ 1$，暴力代码就不用放了吧。

我们反着思考，暴力是找洒水器周围的蘑菇，那我们可不可以找蘑菇周围的洒水器，然后判断周围的蘑菇周围的洒水器数量是否 $\ge k$。

不加优化这么做也是不行的，我们发现，数周围洒水器数量这里可以用二维前缀和替代。

这道题还有个坑点，就是 $2 \le RC \le 5 \times 10^5$，直接开 `a[500010][500010]` 是不行的，我们可以开 `map<int,map<int,char>> a`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,k; 
map<int,map<int,char>> a; //用 map 防止 MLE
map<int,map<int,int>> sum; //前缀和数组 
int ans;
int main(){
	cin>>n>>m>>d>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j]; //输入数据 
			sum[i][j]=(a[i][j]=='S')+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]; //计算前缀和 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='M'){
				if(sum[min(i+d,n)][min(j+d,m)]-sum[max(i-d,1)-1][min(j+d,m)]-sum[min(i+d,n)][max(j-d,1)-1]+sum[max(i-d,1)-1][max(j-d,1)-1]>=k){ //周围洒水器大于等于 k
					ans++;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11594 [NOISG2018 Finals] Collecting Mushrooms
[题目传送门](https://www.luogu.com.cn/problem/P11594)
## 思路

给定一个 $$ R \cdot C $$ 的网格，网格中的格子有可能是：
  - 蘑菇 $M$：需要被洒水器浇灌的地方。
  - 洒水器 $S$：能够影响周围格子的格子。
  - 空格 `.`：无需考虑的格子。
  
- 需要统计所有能够被至少 $K$ 个洒水器浇到的蘑菇。

- 对于每个洒水器，计算它能够影响的区域，并记录每个蘑菇受到多少个洒水器的影响。
- 最终统计有多少蘑菇的影响次数不小于 $K$。

知道了这些之后呢，我们就可以遍历网格，查找所有蘑菇，并检查其洒水器影响数量是否满足 $k$，如果满足则认为它是一个好蘑菇，然后 $ans$ 计数即可。

**时间和空间复杂度均为** $O(RC)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r, c, d, k, ans;
char ch; 
int main(){
    char ch;
    scanf("%d%d%d%d", &r, &c, &d, &k);  
    char g[r + 5][c + 5];
    int p[r + 5][c + 5];
    for (int i = 0; i <= r; i++) {
        for (int j = 0; j <= c; j++) {
            p[i][j] = 0;
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            scanf(" %c", &ch); 
            g[i][j] = ch;
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (g[i][j] == 'S') {
                p[max(1, i - d)][max(1, j - d)] += 1;
                p[max(1, i - d)][min(c, j + d) + 1] -= 1;
                p[min(r, i + d) + 1][max(1, j - d)] -= 1;
                p[min(r, i + d) + 1][min(c, j + d) + 1] += 1;
            }
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            p[i][j] = p[i][j] + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (g[i][j] == 'M' && p[i][j] >= k) {
                ans++;
            }
        }
    }
    printf("%d", ans); 
    return 0;
}
```

---

## 作者：DFM_O (赞：0)

## [P11594 题目](https://www.luogu.com.cn/problem/P11594)

### 解题思路
我们不一定要枚举洒水器来计数，也可以枚举每个蘑菇，用二维前缀和算出以蘑菇为中心，边长为 $2\times d+1$ 的正方形中有多少个洒水器，若个数不小于 $k$，则此蘑菇为好蘑菇。

注意由于我们只知道 $R\times C$ 的范围，而不知道 $R$ 和 $C$ 各自的范围，所以前缀和数组应用向量实现，时间复杂度 $O(nm)$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> a[500001],s[500001];
signed main()
{
	ios::sync_with_stdio(false);
	int n,m,d,k;
	cin>>n>>m>>d>>k;
	for(int i=1;i<=m;i++)
		s[0].push_back(0);
	for(int i=1;i<=n;i++)
	{
		a[i].push_back(0),s[i].push_back(0);
		for(int j=1;j<=m;j++)
		{
			a[i].push_back(0),s[i].push_back(0);
			char ch;
			cin>>ch;
			if(ch=='M')
				a[i][j]=-1;
			if(ch=='S')
				a[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==1)
			{
				s[i][j]=s[i][j-1]+(a[i][j]==1);
				continue;
			}
			if(j==1)
			{
				s[i][j]=s[i-1][j]+(a[i][j]==1);
				continue;
			}
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(a[i][j]==1);
		}
	}
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==-1)
			{
				int gsh=s[min(n,i+d)][min(m,j+d)]-s[min(n,i+d)][max(0LL,j-d-1)]-s[max(0LL,i-d-1)][min(m,j+d)]+s[max(0LL,i-d-1)][max(0LL,j-d-1)];
				if(gsh>=k)
					ss++;
			}
		}
	}
	cout<<ss;
	return 0;
}
```

---

