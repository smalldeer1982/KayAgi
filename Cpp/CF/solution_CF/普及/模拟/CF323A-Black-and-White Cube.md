# Black-and-White Cube

## 题目描述

给你一个 $k\times k\times k$ 大小的立方体，它由 $k^3$ 个 $1\times 1\times 1$ 的立方体组成。两个单元立方体如果有共同的面孔，就被认为是相邻的。你的任务是绘制两种颜色(黑色或白色)中的每一个 $k\times k\times k$ 大小的单元立方体，这个立方体必须满足以下条件：
1. 每个白色立方体正好有两个相邻的白色立方体；
2. 每个黑色立方体正好有两个相邻的黑色立方体。

## 说明/提示

对于 $100\%$ 的数据，$1\le k\le100$。

---
Translated by [残阳如血](/user/726139)。

## 样例 #1

### 输入

```
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
bb
ww

bb
ww
```

# 题解

## 作者：gaoyangyang (赞：5)

### 题目翻译
做一道题最重要的便是理解题意，所以下方是输入样例，输出样例的翻译（题目描述的翻译题目自带了）。

输入格式：

第一行包含整数 $k$（$1 \le k \le 100$），这是立方体的大小。

输出格式：

如果没有解决方案，则打印 $-1$。

否则，按层打印所需的立方体绘画。在第一行中打印一个 $k \times k$ 矩阵，显示立方体的第一层应该如何绘制。在下面的 $k$ 行中，打印一个 $k \times k$ 矩阵依此类推到最后一层。请注意，立方体在空间中的方向并不重要。



用符号“ $w$ ”标记白色单位立方体，用符号“ $b$ ”标记黑色单位立方体。使用测试样本中给出的输出数据格式。您可以打印多余的空行，它们将被忽略。

### 题解
题目理解完了下面我们步入正题。

如题目中所说，这很明显这是要我们构建一个满足“一个白块旁只能有两个白块，一个黑块旁只能有两个黑块”的棱长为 $k$ 的正方体。

这时我们就要想三维的绝对不好做，但是二维的我们会做，所以我们可以将这个立方体化成多个正方形，每两个正方形为一组，且正方形每个点都不相同，这样我们只需要考虑两个正方形的样式并重复输出就可以了。

例子(这里的并不是最终输出，仅是帮助理解上段文字)：

```
//这里以4为例
//第一层：
wwww
wwww
wwww
wwww
//第二层：
bbbb
bbbb
bbbb
bbbb
//两层无论那个点都不相同。
```

但是仅做到这样就够了吗？

很明显不是，因为（如图）可以清楚的看出，单个正方形内并不符合要求，所以我们还要对其进行进一步操作。

假如，这不是一个正方形，而是一条线（且只有一种符合），我们可以清楚看到，在题目要求下，这条线只有头部和尾部不符合要求（周围相邻的只有1个）。

```
################
^              ^

```

我们为了使它符合规范只得将其首尾相接，就可以得到一个环。

其他方法是不符合规范的。

```
####
#  #
#  #
####
```

我们在用相同的方法向内扩展（每一层符号不得相同），就得到了一个“卷饼”，不同的符号一层夹着一层，同时我们也可以发现，当边长为**奇数**时是**无法组成**符合要求的正方体的。

```
//这是我们要构造单个正方形
########
#@@@@@@#
#@####@#
#@#@@#@#
#@#@@#@#
#@####@#
#@@@@@@#
########
```

思路有了，理论也出了，就差实践了，下面我们该如何用代码画出它呢？

其实很简单，我们可以想象这是一个金字塔，每个不同的符号就是一层，这样我们就可以将一个大正方形拆解成多个小正方形：

```
//这是原正方形：
####
#@@#
#@@#
####

//这是拆解后的
####
####
####
####

   
 @@ 
 @@ 
   
```

当这两个正方形组合在一起时，就可以变成符合要求的正方形，这是代码：


```
char a[1000][1000];
//起始x，起始y，边长，填充符号
void gz1(int x,int y,int c,char str)
{
	for (int i=x;i<=x+c-1;i++)
	{
		for (int j=y;j<=y+c-1;j++)
		{
			a[i][j]=str;
		}
	}
}
int main()
{
	int n;
	cin>>n;
	char str1[2]={'w','b'};//存储符号
	for (int i=1;i<=n/2;i++)
	{
		gz1(i-1,i-1,n-(i-1)*2,str1[i%2]);
      //将符号填充
	}
   return 0;
}

```

这就是单个正方形的绘制方法，接下来，我们再绘制一个每个点都与其不相同的正方形，再组合输出就可以了（注意边长为奇数时无法绘制，直接输出 $-1$ 就好了，前文有提到）。

参考代码：

```
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
char a[1000][1000],b[1000][1000];
void gz1(int x,int y,int c,char str)
{
	for (int i=x;i<=x+c-1;i++)
	{
		for (int j=y;j<=y+c-1;j++)
		{
			a[i][j]=str;
		}
	}
}
void gz2(int x,int y,int c,char str)
{
	for (int i=x;i<=x+c-1;i++)
	{
		for (int j=y;j<=y+c-1;j++)
		{
			b[i][j]=str;
		}
	}
}
int main()
{
	int n;
	cin>>n;
	if (n%2==1)
	{
		cout<<-1;
		return 0;
	}
	char str1[2]={'w','b'};
	char str2[2]={'b','w'};
	for (int i=1;i<=n/2;i++)
	{
		gz1(i-1,i-1,n-(i-1)*2,str1[i%2]);
	}
	for (int i=1;i<=n/2;i++)
	{
		gz2(i-1,i-1,n-(i-1)*2,str2[i%2]);
	}
	
	
	for (int z=0;z<n;z++)
	{
		if (z%2==0)
		{
			for (int i=0;i<n;i++)
			{
				for (int j=0;j<n;j++)
				{
					cout<<a[i][j];
				}
				cout<<endl;
			}		
		}
		else
		{
			for (int i=0;i<n;i++)
			{
				for (int j=0;j<n;j++)
				{
					cout<<b[i][j];
				}
				cout<<endl;
			}			
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：RayAstRa_ (赞：2)

目前为止的最优解，仅有 46ms，8kb。

### 题目大意

用黑白两色、边长为 $1$ 的正方体填满一个边长为 $k(1\leq k\leq 100)$的正方体，并保证每个正方体有恰好两个同颜色正方体与其相邻。

### 解题思路

首先观察题面，发现白块和黑块谁先谁后本质上没有区别，可以完全不考虑。

接着观察样例，很容易发现当 $k$ 为偶数时，只需要将同颜色的方块堆成 $2\times2\times1$ 的长方体，将不同颜色的长方体相邻放置，便可以填满整个正方体。

接下来便是研究当 $k$ 为奇数时的情况。

因为 $k$ 为奇数，所以 $k-1$ 为偶数，假设有合法的填充方案，则我们可以用偶数的填充规律首先使内部的边长为 $k-1$ 的正方体合法。那么我们只需要填充剩下的一层：

![](https://cdn.luogu.com.cn/upload/image_hosting/05m7dizh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，红色的是已知的合法正方体，黑色的是整个大正方体。

首先，我们从题面可以看出，对于每个红色正方体中的小正方体，已经有两个与之相邻的同色正方体了。

所以红色正方体正面右上角的小正方体相邻的三个不在红色正方体中的正方体为同一颜色。而我们又能找出三个在大正方体三条棱上的三个小正方体，它们均与与这三个同色正方体中的两个相邻，所以这三个小正方体也同色。但这三个小正方体又都与同一个小正方体（即大正方体右上角的一个）相邻，因此矛盾，无合法情况。

看不懂？看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ieyi4gyy.png)

如图，红色的正方体决定了三个黑色正方体的颜色，进而决定了三个灰色正方体的颜色，因此最后一个蓝色正方体无法填。

因此，当 $k$ 为奇数时，无合法填充情况。

最后我们得出结论：当 $k$ 为奇数时无合法情况，当 $k$ 为偶数时只需将同色小正方体摆为 $2\times2\times1$ 的长方体并交叉放置。

### Code

```cpp
#include<bits/stdc++.h>
#define reg register int
using namespace std;
template<class T>inline void read(T &k){
	char c=0;k=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))k=(k<<1)+(k<<3)+(c^48),c=getchar();
}//快读 
int k;
signed main(){
	read(k);
	if(k&1){//k为奇数特判 
		putchar('-');
		putchar('1');
		return 0;
	}
	for(reg i=0;i<k;i++){
		for(reg j=0;j<k;j++){
			for(reg l=0;l<k;l++){
				if((i&1)^((j>>1)&1)^((l>>1)&1))putchar('w');
				else putchar('b');
				//使用位运算节省时间,也可以开一个char数组先处理再输出 
			}
			if((i^(k-1))|(j^(k-1)))putchar('\n');
		}
		if(i^(k-1))putchar('\n');
		//因为本题末尾额外换行会WA，所以要判断是否为最后一行
	}
}

```

---

## 作者：LCGUO (赞：1)

#### 题意翻译

给你一个 $k\times k\times k$ 大小的立方体，它由单位立方体组成。两个单元立方体有公共面，就被认为是相邻的。你可以涂白和黑两个颜色，保证：

- 每个白色立方体正好有两个相邻的白色立方体；

- 每个黑色立方体正好有两个相邻的黑色立方体。

---

#### 题解

首先，我们可以证明，在奇数情况下，一定没有解，

因为在奇数条件下，如果把白色或黑色两两配对后，一定会多出一边，导致剩下的方块不能填涂颜色使条件满足。

所以我们只用考虑偶数的情况。

对于偶数的情况，我们可以构建一个类似于同心圆的情况，比如这样

```
wwwwwwww
wbbbbbbw
wbwwwwbw
wbwbbwbw
wbwbbwbw
wbwwwwbw
wbbbbbbw
wwwwwwww
```

这样就可以保证，构造的每一层都是符合要求的。

那么我们只要每一层的颜色和上一层的颜色取反，保证上下没有公共面就好了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9') s=(s<<1)+(s<<3)+(c^48),c=getchar();
    return f?s:-s;
}
int n,a[510][510];
int main(){
    n=read();
    if(n&1) puts("-1");
    else{
        for(rint p=1;p<=n;++p)
            for(rint i=p;i<=n-p+1;++i)
                for(rint j=p;j<=n-p+1;++j){
                    if(i==p||i==n-p+1) a[i][j]=p&1;
                    else if(j==p||j==n-p+1) a[i][j]=p&1;
                    else a[i][j]=(p&1)^1;
                }//构造第一层的情况
        for(rint k=1;k<=n;++k)
            for(rint i=1;i<=n;++i){
                for(rint j=1;j<=n;++j){
                    if(a[i][j]) putchar('w');
                    else putchar('b');
                    a[i][j]^=1;
                }//输出每一层的情况，并且取反
                putchar('\n');
            }
   	}
    return 0;
}
```





---

## 作者：玉树临风英俊潇洒 (赞：0)

这是一道构造题。

1. 当  $k$ 为奇数时，白色或黑色配对的时候，会多出一边，从而导致剩下的不能按题目条件填涂，所以无解。
   
2. 当  $k$ 为偶数时，先看看我手算的。
```
wwwwwwww
wbbbbbbw
wbwwwwbw
wbwbbwbw
wbwbbwbw
wbwwwwbw
wbbbbbbw
wwwwwwww
```
3. 如果把每一圈看为一层的话，那么每一层为相同的字母，同时，其下一层为与其相反的相同的字母，这样可以保证符合题意。这个做法可以保证不同层之间无同色相邻，同层之间每块都有两个相同颜色与自己相邻。

4. 时间复杂度也只是三次方。

---

## 作者：hgcnxn (赞：0)

## CF323A Black-and-White Cube题解

### 思路

对于每一个小立方体，它的边上恰有两个与它同色的立方体。也就是说，对于每一个立方体，沿着与它同色的立方体移动，最后会回到它自己。所以，**这些立方体会形成若干个环！**

不仅如此，如果你从一个立方体出发，经过移动回到了自身，那么你向上走了几步，就一定向下走了几步。同理，你向前走了几步，就一定向后走了几步；你向左走了几步，就一定向右走了几步。所以，你移动的步数一定是偶数。那么，**每个环的长度也是偶数。**

回到我们原本的问题。如果 $k$ 是奇数，那么以 $k$ 为边长的大立方体里面一定有奇数个小立方体。根据我们上面得出的结论，必有一个环的长度为奇数，此时一定无解。

下面给出 $k$ 为偶数的构造：

考虑在 $k\times k$ 的平面内进行构造。我们将最外层一圈染成黑色，次外圈染成白色，第三圈染成黑色 $\ldots$ 按层交替染色。例如，$k=6$ 时，我们如下染色：

```
bbbbbb
bwwwwb
bwbbwb
bwbbwb
bwwwwb
bbbbbb
```

接下去，我们再对于大立方体的每一层交替染色即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[102][102];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	if(n&1){
		cout<<-1;
		return 0;
	}
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)f[i][j]=min(min(i,j),min(n-i-1,n-j-1))&1;
	//预处理单层染色的结果 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++)cout<<(f[j][k]^(i&1)==0?"b":"w");
			cout<<"\n";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题属于**构造**题：

- 首先，当 $k$ 为奇数时，我们可以发现，当黑块与白块结合后，在角块上会出现无法填充的情况，因此无解。

- 当 $k$ 为偶数时，我们可以发现以下的填充规律是正确的：

```
wwwwww
wbbbbw
wbwwbw
wbwwbw
wbbbbw
wwwwww
```

上图的相邻层：

```
bbbbbb
bwwwwb
bwbbwb
bwbbwb
bwwwwb
bbbbbb
```

- 这个做法可以保证不同层之间无同色相邻，同层之间每块都有两个相同颜色与自己相邻。

- 代码实现不复杂，时间复杂度为 $O(k^3)$。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
char mp[N][N];
bool flag;
int k;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>k;
	if(k&1)//无解情况
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=k;i++)
	{
		if(!flag)//记录当前层应该怎样填充
		{
			for(int j=1;j<=k;j++)
			{
				for(int l=1;l<=k;l++)
				{
					if(min(min(j,l),min(k-j+1,k-l+1))%2==1)//判断其到边线的距离
					{
						mp[j][l]='b';
					}
					else
					{
						mp[j][l]='w';
					}
				}
			}
			flag=true;//下一轮需要变换填充方式
		}
		else
		{
			for(int j=1;j<=k;j++)
			{
				for(int l=1;l<=k;l++)
				{
					if(min(min(j,l),min(k-j+1,k-l+1))%2==1)//同上
					{
						mp[j][l]='w';
					}
					else
					{
						mp[j][l]='b';
					}
				}
			}
			flag=false;
		}
		for(int j=1;j<=k;j++)
		{
			for(int l=1;l<=k;l++)
			{
				cout<<mp[j][l];//构造好图形后输出
			}
			cout<<"\n";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目分析：
   - 这是一道模拟题。观察第二个样例，我们即可将一个边长为 $k$ 的立方体分为 $k^3 \div 2^3$ 个小立方体。
   
   - 模拟出 $k=4$ 的一种情况。
   
```
bbww
wwbb
bbww
wwbb

bbww
wwbb
bbww
wwbb

wwbb
bbww
wwbb
bbww

wwbb
bbww
wwbb
bbww
```
- 模拟出 $k=6$ 的一种情况。
 
```
bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww

bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww

wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb

wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb

bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww

bbwwbb
wwbbww
bbwwbb
wwbbww
bbwwbb
wwbbww
```
……


   - 可以发现构造的一种矩阵的规律是，第一层和第二层一模一样，第三层和第四层一模一样，而第一层和第三层完全相反……每一层左右相邻的 $2$ 个小立方体也是完全相反的；每一层的第一行小正方形和第二行小正方形是完全相同的，每一层的第二行小正方形和第三行小正方形是完全相同的……
   
   
   - 但需要注意的是，$k \bmod 2=1$，那么就将无解。因为最后一行的 `w` 和 `b`，只能满足每个白色立方体正好有一个相邻的白色立方体，每个黑色立方体正好有一个相邻的黑色立方体。

   
### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n%2==1)
	{
		cout<<-1;
		return 0;
	}
	for(int ci=0;ci<n/2;ci++)
	{
		for(int i=0;i<2;i++)
		{
			for(int hang=0;hang<n;hang++)
			{
				for(int lie=0;lie<n/2;lie++)
				{
					if(ci%2==0)
					{
						if(hang%2==0)
						{
							if(lie%2==0)
							{
								cout<<"bb";
							}
							else
							{
								cout<<"ww";
							}
						}
						else
						{
							if(lie%2==1)
							{
								cout<<"bb";
							}
							else
							{
								cout<<"ww";
							}
						}
					}
					else
					{
						if(hang%2==0)
						{
							if(lie%2==0)
							{
								cout<<"ww";
							}
							else
							{
								cout<<"bb";
							}
						}
						else
						{
							if(lie%2==1)
							{
								cout<<"ww";
							}
							else
							{
								cout<<"bb";
							}
						}
					}
				}
				cout<<endl;
			}
			cout<<endl;
	    }
    }
}


```

   
   



---

## 作者：zfw100 (赞：0)

# CF323A Black-and-White Cube 题解

## 题目大意

略，自认为题目已经很详细了。

## 题目分析

显然，当 $k$ 为奇数时，无解，直接输出 $-1$ 即可。

原因：当 $k$ 为奇数时，白色或黑色配对的时候，会多出一边，从而导致剩下的不能按题目条件填涂，所以无解。

那么，当 $k$ 为偶数时，应该怎么办呢？

手算几组之后可以发现，如果把每一圈看为一层的话，那么每一层为相同的字母，同时，其下一层为与其相反的相同的字母，这样可以保证符合题意，比如这样：

```cpp
wwwwwwwwww
wbbbbbbbbw
wbwwwwwwbw
wbwbbbbwbw
wbwbwwbwbw
wbwbwwbwbw
wbwbbbbwbw
wbwwwwwwbw
wbbbbbbbbw
wwwwwwwwww
bbbbbbbbbb
bwwwwwwwwb
bwbbbbbbwb
bwbwwwwbwb
bwbwbbwbwb
bwbwbbwbwb
bwbwwwwbwb
bwbbbbbbwb
bwwwwwwwwb
bbbbbbbbbb

```


然后就可以写代码了，代码不放了。

---

