# Sea and Islands

## 题目描述

A map of some object is a rectangular field consisting of $ n $ rows and $ n $ columns. Each cell is initially occupied by the sea but you can cover some some cells of the map with sand so that exactly $ k $ islands appear on the map. We will call a set of sand cells to be island if it is possible to get from each of them to each of them by moving only through sand cells and by moving from a cell only to a side-adjacent cell. The cells are called to be side-adjacent if they share a vertical or horizontal side. It is easy to see that islands do not share cells (otherwise they together form a bigger island).

Find a way to cover some cells with sand so that exactly $ k $ islands appear on the $ n×n $ map, or determine that no such way exists.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
YES
SSSSS
LLLLL
SSSSS
LLLLL
SSSSS
```

## 样例 #2

### 输入

```
5 25
```

### 输出

```
NO
```

# 题解

## 作者：x1489631649 (赞：2)

## 题目解析

先输入正方形海域，再输入岛屿数目（上下左右相邻算一个岛屿），输出这个海域。
    
## 重点分析

因为要使正方形海域岛屿数目最多，所以必为每个岛屿占一格且间隔排放（最简单的做法）。
        
## 注意点

判断是否可以有这么多岛屿，``` for ``` 循环遍历，先赋值再输出（也可以直接输出）。
    
# 代码
``` cpp
#include<bits/stdc++.h>//万能头文件。 
using namespace std;
char a[10000][10000];
int main()
{
	int n,k;// n 为正方形海域边长， k 为岛屿数目。 
	cin>>n>>k;
	if(k>ceil(n*n*1.0/2))//注意：是 > 而不是 >= 一试便知。 
	{
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]='S';
	int s=0;// 已赋值岛屿数。 
	for(int i=1;i<=n;i++)
	{
		if(i%2==1) 
		{
			for(int j=1;j<=n;j+=2)
			{
				if(s<k)//因为 s 是从 0 开始。 
				{
					a[i][j]='L';
					s++;
				}
			}
		}		
		else{
			for(int j=2;j<=n;j+=2)
			{
				if(s<k)
				{
					a[i][j]='L';
					s++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++) // 输出正方形海域。 
	{
		for(int j=1;j<=n;j++)
			cout<<a[i][j];
		cout<<endl;
	}
    return 0;//养成好习惯。 
}
```

---

## 作者：_byta (赞：2)

我来发一篇方便思考且码量较短的代码。

首先我们可以发现当岛屿数量超过空地数量的一半时不可能放满。直接判掉。

接下来考虑能放下岛屿的情况，我们发现，每隔一个空放一个岛屿时能放最多岛屿。所以我们可以每隔一个空放一个岛屿，当岛屿放满时放湖泊就行了。

其他详见代码注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, cnt;
int main() 
{
	scanf("%d%d", &n, &k);
	if (k > ceil(n * n / 2.0))//特判无解情况
	{
	   printf("NO\n");
	   return 0;
    }
	cout<<"YES"<<endl;否则有解
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= n; j++) 
		{
			if (cnt < k && !((i + j) % 2)) 当此处可以放岛屿时就放岛屿
			{
			   putchar('L');
			   cnt++;
		    }
			else putchar('S');否则放湖泊
		}
		puts("");
	}
	return 0;
}

```




---

## 作者：过氧化氢_syq0057 (赞：1)

挺不错的题，我觉得应该是红题呀（/youl

这样例挺坑人的 qwq

题目中有一句话是 ```You should not maximize the sizes of islands.``` 也就是说你不需要最大化岛屿大小。

那不就简单啦~

显然，岛屿最多能填 $\lfloor \frac{n^2+1}{2} \rfloor$ 个，如果 $k$ 大于这个值，那么肯定不行，输出 ```NO``` ，否则输出 ```YES``` 。

然后考虑一下方案

既然不需要最大化岛屿大小，那么是不是可以隔一个 ```S``` 填一个 ```L``` ，然后一个 $cnt$ 记录填了多少个岛，如果大于 $k$ 就可以不用填 ```L``` 了，剩下的全是 ```S``` 。

用一个 $cur$ 记录当前应该填 ```L``` 还是 ```S``` ，每次异或一下。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int n, k;
int cnt;
int main() {
	scanf("%d%d", &n, &k);
	if (((n * n + 1) >> 1) < k) {
		printf("NO\n");
		return 0;
	}//判NO
	printf("YES\n");
	int cur = 1;//表示填L还是R
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			if (cur && cnt < k) cnt++, printf("L");
			else printf("S");
			cur ^= 1;
		}
		if (!(n & 1)) cur ^= 1;//注意这里，如果n是偶数，那么下次循环开始填的时候会从第一个开始填L，和上一次的在一列，会变成一个岛（被坑了一下qwq
		puts("");
	}
	return 0;
}
```

完啦qaq

---

## 作者：knsg251 (赞：0)

## 题目分析
首先特判：岛屿最多只能占到地图的**一半**，如果比一半多，那么就**无解**，否则一定有解。

所以我们直接每隔一个空，放入一个小岛，当小岛放满时再放湖泊，就这样去模拟即可。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	cin>>n>>k;
	if((n * n + 1) / 2 < k){//特判 
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;//第一问 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(k > 0 && (i + j) % 2 == 0){//判断放岛屿还是湖泊 
				k--;
				printf("L");//输出 
			}else{
				printf("S");//输出 
			}
		}
		printf("\n");//记得换行 
	}
	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF544B)
## 题面：
给出一个 $n$，求出 $n$ 行 $n$ 列的矩阵中能否摆放出 $k$ 个四连通块，连通块用 $L$ 表示。不能输出 `NO`，否则输出 `YES`，并输出这个矩阵。
## Solution
我们可以发现，如果要摆放连通块的个数比矩阵面积的一半多，就直接特判无解，否则一定有解。接下来，我们开始摆放连通块。我们必须摆放的尽可能多，所以每个连通块只能有一个元素，每隔一个非连通块就摆放一个连通块，并且上下不能是连通块。
```
   1 2 3 4 
1  S L S L
2  L S L S
3  S L S L
4  L S L S
```
通过观察，我们可以发现，在最优策略下，连通块都摆放在**奇数行奇数列**或**偶数行偶数列**。所以，枚举每一个点，如果满足条件就放连通块，否则就放非连通块。

---

## 作者：ImNot6Dora (赞：0)

首先考虑无解情况，可以发现，如果存在一个岛屿，那么必定会存在至少一个与其相对应的海域。也就是说，岛屿最多只能占到地图的一半，如果比一半多，那么就无解，否则一定有解。

```cpp
if(k>(n*n+1)/2){//如果岛屿的数量大于地图方格数量的一半则无解
	cout<<"NO\n";
	return 0;
}
```
接下来我们来考虑该如何摆放岛屿，由于斜着的两个`L`不算同一块岛屿，我们就可以交叉摆放岛屿，即奇数行的奇数列和偶数行的偶数列上摆放岛屿，当岛屿摆放完毕之后，我们就摆放海洋就好了。
# AC C++ CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k;
	cin>>n>>k;
	if(k>(n*n+1)/2){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(k==0){//当岛屿摆放完了
				cout<<'S';//摆放海洋
				continue;
			}
			if(i%2==1){
				if(j%2==1){//奇数行的奇数列摆放岛屿
					cout<<'L';
					k--; 
				}else cout<<'S';
			}else{
				if(j%2==1)cout<<'S';
				else{//偶数行的偶数列摆放岛屿
					cout<<'L';
					k--;
				}
			}
		}
		cout<<endl;
	}
	return 0;
}

```
By ImNot6Dora

---

## 作者：zwy__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF544B)
### 题目大意
有一个 $n \times n$ 的正方形矩阵，并有一个变量 $k$，你要在这个矩阵上填出 $k$ 个岛，可不可以做到？如不可以，输出 NO，否则输出 YES，并输出其中一种方案（ $L$ 和 $S$ 分别代表岛和海，上下左右相邻的岛被看作一个岛。）。
### 题目思路
PS：只需要输出最简单的一个解就可以了。

根据题目描述，最小的岛占了一个单位。而要想要这个岛最小，周围只能是海。所以，根据以上结论，最多可以有 $ \left\lfloor \dfrac{n^2}{2} \right\rfloor $ 个岛，那我们就可以进行判断，不符合的提前输出。

我们先来看一下下面这个表格。

 $n:5$
 
 $k:12$
 

| L | S | L| S | L | 
| :----------: | :----------: | :----------: | :----------: | :----------: |
| S |  L| S |  L|  S|
|  L|  S|  L| S | L |
| S |  L| S |  L|  S|
|  L|  S|  L| S | L |
可以看到，只要保证 $L$ 和 $S$ 交替出现，那么就可以保证答案正确。我们只需要进行一些周期判断，并输出 $k$ 个答案就行了，无需考虑其他情况。
### 上代码
保证代码正确。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,s;
int main()
{
	cin>>n>>k;
	s=k;
	//特判 
	if(n%2==0&&k>n*n/2)
	{
		cout<<"NO"<<endl; 
		return 0;
	}
	if(n%2==1&&k>n*n/2+1)
	{
		cout<<"NO"<<endl; 
		return 0;
	}
	cout<<"YES"<<endl;
	//交替输出即可，只需输出最简单的解 
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(i%2==1)
			{
				if(s==0)cout<<"S";
				else
				{
					if(j%2==1)
					{
						s--;
						cout<<"L";
					}
					else cout<<"S";
				} 
			}
			else
			{
				if(s==0)cout<<"S";
				else
				{
					if(j%2==0)
					{
						s--;
						cout<<"L";
					}
					else cout<<"S";
				}
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：PeaceSunset (赞：0)

这题适合**刚入门**的新手拿来练习写代码。

#### 思路：

首先，根据题目，我可以整理一个 S 与 L 相通交错的表格（格式渲染有问题，没办法显示出来）。

根据这个表，我们不难发现，一个 $n\times n$ 的矩阵最多只能放下 $\frac{n^2+1}{2}$ 个岛。

那么当 $k>\frac{n^2+1}{2}$ 时，就不能放得下岛，所以这种情况直接输出 NO。

反之，当 $k\le\frac{n^2+1}{2}$ 时，就可以开始放岛了。怎么放呢？

如上图，我们需要判断每个位置的上方和左方是否没有岛，就可以放了。用一个变量记录当前放了几个岛。

如果这个变量达到了岛数量的上限，那么剩下的位置都放水就行了。

#### 思路讲完，代码贴上：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
char a[105][105];
signed main(){
	cin>>n>>k;
	if(k>(n*n+1)/2){
		cout<<"NO";
	}
	else{
		int all=0;//记录放了几个岛
		cout<<"YES\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i-1][j]!='L'&&a[i][j-1]!='L'&&all<k){
					a[i][j]='L';
					cout<<'L'; // 边遍历边输出
					all++;
				}
				else {
				    a[i][j]='S'; // 同上
				    cout<<'S';
				}
			}
			cout<<"\n";
		}
	}
   // 其实可以在此处输出
	return 0;
} 
```

---

## 作者：wenlebo (赞：0)

## 题意

题意：给定 $n$ 和 $k$，求在 $n$ $\times$ $n$ 的矩阵中能否填出 $k$ 座岛，如果可以则输出摆法（$S$ 表示海，$L$ 表示岛，上下左右相邻的 $L$ 算作一个岛）。

## 思路

为了最大化岛屿数量，只需交替放置 $L$ 与 $S$ 即可。

## 注意

  - 判断无解要把能放岛数向上取整。
  
  - 记录你放了多少岛或还应该放多少，不要多放。
  
  - 先放岛屿后放海洋，这样可以岛屿最大化，否则像“$5$ $13$”这样的数据会错。

  
##  AC代码

```cpp

//感谢管理的提醒!!

#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	if(k>ceil(n*n/2.0)){//判无解
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	for(int f=0;f<n;f++){
      bool now=f%2;
		for(int y=0;y<n;y++){
			if(k!=0&&now==0){
				cout<<"L";
         		k--;
			}else{
				cout<<"S";
        	}
      	  now=!now;
		}
		cout<<endl;
	}
	return 0;
} 

```


---

## 作者：cxy000 (赞：0)

### 分析：
首先我们看到此题第一个要想的就是怎么判断是否可以放置这么多的岛屿。

然后我们可以列出一个大概的图：

| 1 | 2 | 3 | 4 |
| -----------: | -----------: | -----------: | -----------: |
 L | S | L | S |
 S | L | S | L |
 L | S | L | S |
 S | L | S | L |

这样我们可以看到，最多放置的岛屿就是每隔一个放一个。

这样一共可以放置 $\lfloor \frac {n^2+1}{2} \rfloor$ 个。（当然要向下取整啊）

于是我们可以进行特判。

在最后用我们上面的方式输出完所有的岛屿再全部输出湖泊即可。

### $code$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	if(m>(n*n+1)/2){
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==0 && m>0){
				m--;
				cout<<"L";
			}
			else cout<<"S";
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：OoXiao_QioO (赞：0)

# 前言

这道题非常有思维含量，我足足 $\verb!WA!$ 了三次才 $\verb!AC!$！！！

# 题目描述

给定 $n$ 和 $k$，求在 $n\times n$ 的矩阵中能否填出 $k$ 座岛。$S$ 表示海，$L$ 表示岛，当一个或多个 $L$ 被 $S$ 围起来就叫做一个岛。

# 思路

还是那句话，不要被样例迷惑了！！！

我们可以先根据 $n$ 和 $k$ 来判断是否可以填出 $k$ 个岛。

岛的个数越大越好，要保证最大，我们可以交替来填充。

画个图来找找规律：

当 $n$ 为奇数

例如 $n = 5$：

我们可以画出下面这张图

LSLSL

SLSLS

LSLSL

SLSLS

LSLSL

注意：以下式子如果不懂可直接跳至“发现的规律”一段。

发现一三五行 $L$ 的数量为 $3$，也就是 $5/2+1$。

一共有三行的 $L$ 的数量为 $3$，也就是 $5/2+1$。

结合起来，也就是 $(5/2+1) \times (5/2+1)$。



发现二四行 $L$ 的数量为 $2$，也就是 $5/2$。

一共有两行的 $L$ 的数量为 $2$，也就是 $5/2$。

结合起来，也就是 $(5/2) \times (5/2)$。

把二者相加，就是 $9+4 = 13$。


再举个例子吧，例如 $n = 7$：

根据我们的公式，容易得出 $L$ 的个数为 $25$。


当 $n$ 为偶数

例如 $n = 4$：

我们可以画出下面这张图

LSLS

SLSL

LSLS

SLSL



发现每行 $L$ 的个数都为 $2$，也就是 $4/2$。

一共有 $n$ 行，那么 $L$ 的个数轻松得出来是 $2n$，也就是 $8$。



再举个例子吧，例如 $n = 6$：

根据我们的公式，容易得出 $L$ 的个数为 $18$。


发现的规律？


如果 $n$ 为偶数时，发现每行都有 $n/2$ 个 $L$ 和 $n/2$ 个 $S$，所以当 $n$ 为偶数时，$L$ 的个数为 $n^2/2$。

如果 $n$ 为奇数时，发现除去最后一个字符，其他字符两两一组，每个小组里都有一个 $L$ 和一个 $S$，例如下图：

LSL

SLS

LSL

第一二个字符一组，第三四个字符一组，第五六个字符一组，第七八个字符一组，第九个字符单独一组。

所以当 $n$ 为奇数时，$L$ 的个数为 $n^2/2+1$。



于是我们可以轻松判断是否能填充出 $k$ 个岛屿。

如何实现填充岛屿？

我们可以定义一个 $cnt$，表示现在填充了多少个岛屿。

定义一个 $t$，表示现在该填充海还是岛屿。

如果 $t$ 是偶数，就填充一个岛屿，否则填充海。

注意行与行之间的判断。

# 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	 
	int n,k,i,j,cnt,t,is;
	
	//输入
	 
	cin>>n>>k;
	
	//判断是否能填充 k 个岛屿，推导过程在前文。 
	is = (n%2==0)?n*n/2:n*n/2+1;
	if(k>is)//如果超出了填充限制,输出 NO。 
		return printf("NO\n"),0;
	else//否则输出 YES，并开始填充。 
	{
		printf("YES\n");
		//这两个变量意义参见前文。 
		cnt = 0;
		t = 1;
		for(i=1;i<=n;i++)
		{
			t += (n%2==0);//注意此时的判断，不然就无法达到两行交替输出的需求，参见下面
			/*问题的严重性 
			LSLSL
			LSLSL
			LSLSL
			LSLSL
			LSLSL
			*/ 
			for(j=1;j<=n;j++)
			{
				t++; // t 每次加一，交替的输出。 
				if(t%2==0&&cnt<k)//如果要填岛且还能继续填
					printf("L"),cnt++;//填充一个岛屿，且 cnt + 1。
				else//否则要不是填满了，要不是本该填充海 
					printf("S");//不管什么原因，都填充海洋。 
				
			}
			puts("");//换行 
		}
	}
	return 0;
}
```

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
我们先看看 $5\times 5$ 的矩阵最多能放多少个岛：

| $L$ | $S$ | $L$ | $S$ | $L$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $S$ | $L$ | $S$ | $L$ | $S$ |
| $L$ | $S$ | $L$ | $S$ | $L$ |
| $S$ | $L$ | $S$ | $L$ | $S$ |
| $L$ | $S$ | $L$ | $S$ | $L$ |

一共可以放 13 个岛，可以发现最多放的数量为 $\dfrac{(n^2+1)}{2}$。那么就可以直接判断能不能放下了。

第二问直接照规律模拟即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,t;
    cin>>n>>k;
    if(k<=(n*n+1)/2) cout<<"YES\n";//判断
    else{
        cout<<"NO";
        return 0;
    }
    t=k;
    for(int i=1;i<=n;i++){//直接模拟
        if(i%2==1){
            for(int j=1;j<=n;j++){
                if(j%2==1){
                    if(t!=0) {cout<<"L";t--;}
                    else cout<<"S";
                }
                else cout<<"S";
            }
        }
        else{
            for(int j=1;j<=n;j++){
                if(j%2==0){
                    if(t!=0) {cout<<"L";t--;}
                    else cout<<"S";
                }
                else cout<<"S";
            }
        }
        cout<<endl;
    }
}
```

---

## 作者：Na2_CuCl4 (赞：0)

题意敲到机翻里面翻译了一下，发现了最后一句提示：你不应该最大化岛屿的大小。所以思路就很清晰了，首先先分两种情况：

### 一、放得下岛

首先，我们先令 $n=5$,发现最多放下 $13$ 个岛，再试试 $n=4$ ,发现最多放下 $8$ 个。因此推出公式：只要 $k\le(n^2+1)/2$ ，就可以满足要求。

那怎么操作呢？因为这道题是 $SPJ$ ,所以我们输出最简单的方法就行了，就是从 $(0,0)$ 开始，~~一米线间隔就坐~~按棋盘黑白格那样排列。

即有代码：

```cpp
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		if (k && !((i + j) % 2)) {
			k--;
			cout << "L" ;
		} else
			cout << "S" ;
	}
	cout << endl;
}
```

实时更新k的值，在岛数量够了以后就不再填了。

### 二、那要是放不下呢

这有什么可想的，直接输出 ```NO ``` 就可以了。

综上，上代码：

```cpp
#include <iostream>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	if (k > (n * n + 1) / 2) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (k && !((i + j) % 2)) {
				k--;
				cout << "L" ;
			} else
				cout << "S" ;
		}
		cout << endl;
	}
	return 0;
}
```



---

## 作者：ZhanPJ (赞：0)

题目传送门：[CF544B Sea and Islands](https://www.luogu.com.cn/problem/CF544B)

---

题意简述：

已知有一个 $n \times n$ 的取余，要塞下 $k$ 个小岛，求能不能塞下这 $k$ 座岛屿。

---

算法：

贪心，模拟。

时间复杂度：
- 在不能塞下 $k$ 座岛屿时，时间复杂度为 $O(1)$。
- 在能塞下 $k$ 座岛屿时，时间复杂度为 $O(n^2)$。（实际上就是输出要这么长时间）

---
思路：

我们可以发现，判定这个岛屿是否能够被塞下可以这么看。

在 $n=3,k=5$ 时，岛屿可以这样塞下：
```
LSL
SLS
LSL
```
在 $n=3,k=6$ 时，岛屿不可以塞下。

可以发现在 $k > \frac{n^2+1}{2}$ 时，不可以塞下，即最优方案是以斜角去放下所有岛屿。

在我们放岛屿的时候，还有一点需要注意：当已经放的岛屿数量够了，那就不需要继续放岛屿了。

---
AC 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	if((n*n+1)/2<k)printf("NO\n");
	else{
		printf("YES\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!k)printf("S");
				else if(!(i%2)){//这是个人的偷懒，在 C++ 中，整形变量不是 0，返回值就是 true。
					if(!(j%2))printf("L"),k--; 
					else printf("S");
				}else{
					if(j%2)printf("L"),k--; 
					else printf("S");
				}
			}
			printf("\n");
		}
	}
	
	return 0;
} 
```

---

## 作者：HuZHUNZHUN (赞：0)

~~这道题很㵘诶~~

显而易见：

斜着放放的岛屿最多，即：

$\left \lceil \dfrac{n^2}{2} \right \rceil$ 个岛屿。

因此，如果 $k>\left \lceil \dfrac{n^2}{2} \right \rceil$ 的话，就爆掉了。

我们把岛屿一个一个地填进去，如果填够了就不填了。

无注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	if(k>(n*n+1)/2)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	else
	{
		cout<<"YES"<<endl;
		int num=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(num<k && i%2==j%2)
				{
					num++;
					cout<<"L";
				}
				else
				{
					cout<<"S";
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Error_Eric (赞：0)

### 前言

我来发一篇更方便思考，且代码更短的代码。

### 正文

显然湖泊越小越好，陆地越小越好。

所以如下排列时为最优解： ![](https://ss0.bdstatic.com/70cFvHSh_Q1YnxGkpoWK1HF6hhy/it/u=555718934,1097464798&fm=26&gp=0.jpg)

暴力模拟一下，如果最终总数小于 $k$ 就输出 ``NO``,不然输出 ``YES`` 直接输出结果即可。

### Code

```python
n,k=map(int,input().split());ans=[];cnt=0
for i in range(n):
    ans.append("")
    for j in range(n):
        if (i+j)%2==0 and cnt<k:
            ans[i]=ans[i]+'L';cnt=cnt+1
        else :
            ans[i]=ans[i]+'S'
if cnt>=k: 
    print("YES")
    for i in range(n):
        print(ans[i])
else :
    print("NO")
```

---

## 作者：龙翔凤翥 (赞：0)

## 题意：构造n*n矩形，使得存在k个L不相连。
### sol:
按照题意膜你即可。
### code：
```#include<bits/stdc++.h>
#define RN register int 
using namespace std;
inline int read() {
    int x=0,o=1;
    char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9'))
		ch=getchar();
    if(ch=='-')
		o=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=getchar();
    return x*o;
}
int n,k,ret;
int main()
{
	n=read(),k=read();
    if (k>(n%2?(n+1)/2+(n-1)/2*n:n*n/2)) puts("NO");
    else
    {
        puts("YES");
        for (RN i=1;i<=n;i++)
        {
            for (RN j=1;j<=n;j++)
            {
                if(i%2==j%2)
                {
                    if (k)
						cout<<"L",k--;
					else
						cout<<"S";
                }
                else cout<<"S";
            }
			puts("");
        }
    } 
    return 0;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现当我们把岛屿都错开放时，岛屿数是最多的，所以当 $k>\left\lceil \frac{n^2}{2} \right\rceil$ 时，无解。接着我们在**奇数行的奇数列和偶数行的偶数列**放置岛屿即可。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum;
int main(){
	cin>>n>>k;
	if(k>ceil(n*n/2.0)){
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(sum<k&&(i+j)%2==0){
				cout<<"L";
				sum++;
				continue;
			}
			cout<<"S";
		}
		cout<<endl;
	}
	return 0;
} 
```


---

