# Santa Claus and a Place in a Class

## 题目描述

Santa Claus is the first who came to the Christmas Olympiad, and he is going to be the first to take his place at a desk! In the classroom there are $ n $ lanes of $ m $ desks each, and there are two working places at each of the desks. The lanes are numbered from $ 1 $ to $ n $ from the left to the right, the desks in a lane are numbered from $ 1 $ to $ m $ starting from the blackboard. Note that the lanes go perpendicularly to the blackboard, not along it (see picture).

The organizers numbered all the working places from $ 1 $ to $ 2nm $ . The places are numbered by lanes (i. e. all the places of the first lane go first, then all the places of the second lane, and so on), in a lane the places are numbered starting from the nearest to the blackboard (i. e. from the first desk in the lane), at each desk, the place on the left is numbered before the place on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)The picture illustrates the first and the second samples.Santa Clause knows that his place has number $ k $ . Help him to determine at which lane at which desk he should sit, and whether his place is on the left or on the right!

## 说明/提示

The first and the second samples are shown on the picture. The green place corresponds to Santa Claus' place in the first example, the blue place corresponds to Santa Claus' place in the second example.

In the third sample there are two lanes with four desks in each, and Santa Claus has the fourth place. Thus, his place is in the first lane at the second desk on the right.

## 样例 #1

### 输入

```
4 3 9
```

### 输出

```
2 2 L
```

## 样例 #2

### 输入

```
4 3 24
```

### 输出

```
4 3 R
```

## 样例 #3

### 输入

```
2 4 4
```

### 输出

```
1 2 R
```

# 题解

## 作者：Ybocean_s (赞：3)

### 题意：

有一个$n * m$的教室，每个桌子有编号，给出编号 $ k $  ，输出在哪张桌子，什么位置。


其实这道题的翻译已经很明确，但需要注意的是。

![](https://cdn.luogu.com.cn/upload/image_hosting/jsguqtye.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

一个桌子有两个人！

本蒟蒻决定用循环。   ~~其实数据是水的~~ 。

按照图片的序号循环。

```cpp
for(int i=1;i<=n;i++)
               
for(int j=1;j<=m;j++)
```

接下来判断左右：
不难发现当序号是奇数时在左，是偶数时在右。

代码：

```
#include<iostream>
using namespace std;
int main()
{
	int n,m,k,js=0;
	cin>>n>>m>>k;//题目给出的变量。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int l=1;l<=2;l++){
				js++;//每个的序号。
				if(js==k){
					cout<<i<<" "<<j<<" ";
					if(js%2==0){
						cout<<"R";
						}else{
							cout<<"L";
						}
						return 0;
					}					
				}
			}
		}
	return 0;//这个没有太大必要。
}
```

---

## 作者：zplqwq (赞：2)

## [CF748A](https://www.luogu.com.cn/problem/CF748A)

Hello ! 我又来了，不要问我为什么这么高产~~我是不会告诉你我想上橙的~~

# Section 1 题目分析

## 算法：

​	· 没什么大的算法，主要是模拟找规律

## 找规律

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)

根据这张图，我们不难发现

1. 圣诞老人的坐标为：((k+1)/2)/m+1,((k+1)/2)%m+1;
2. 当k%2==1 时,输出L。否则，输出R；

## 坑点&附加建议

1. 找规律的时候注意考虑全面，一定要细心
2. 其实模拟问题不大，但是推荐这种办法

# Section 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;
//管理大大求过
//我爱洛谷
int n,m,k;

int main()
{
    cin>>n>>m>>k;
    int ans=(k+1)/2-1;//偷个懒
    if(k%2==1)//判断左右
	{
		cout<<ans/m+1<<" "<<ans%m+1<<" L"<<endl;//如我所解释
	}
    else //同理
	{
		cout<<ans/m+1<<" "<<ans%m+1<<" R"<<endl;
	}
    return 0;
}
```

~~管理大大求过~~



---

## 作者：Mysterious_bird (赞：2)

#### 题目解析：
这题其实就是一个二维矩阵，给你一个编号，让你输出这个编号所在的位置
#### 使用算法：
这题的范围：$ n,m,k.( 1<=n,m<=10000 , 1<=k<=2 * n* m ) $

所以这道题不能用二维数组直接来模拟，我自己在做的时候又想到了STL中的```vector```，然后，大大滴WA！

~~***放弃思考***~~

所以就想了一个简便一点的方法：不模拟出一个二维矩阵，直接查找编号

其核心就是三重循环

#### 代码实现：
```cpp
for(int i=1;i<=n;i++)	//模拟行数
{
    for(int j=1;j<=m;j++)	//模拟列数
    {
        for(int t=1;t<=2;t++)	//一列有两排
        {
            cnt++;	//用来记录当前编号
            if(cnt==k)
            {
                cout<<i<<" "<<j<<" ";   //输出横坐标和纵坐标
                if(t==1) cout<<'L';  //输出是左还是右
                else cout<<'R';
                putchar('\n');  //换行
                return 0;   //结束，return 0
            }
        }
    }
}
```
用三重循环的方式从行、列、每列的两排中查找



接着就是整段代码了
#### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,k;
    cin>>n>>m>>k;
    int cnt=0;  //一个计数器
    for(int i=1;i<=n;i++)      //第一重循环，模拟行
    {
        for(int j=1;j<=m;j++)   //第二重，模拟列
        {
            for(int t=1;t<=2;t++)   //第三重，模拟出每列的左右两边
            {
                cnt++;	//用来记录当前编号
                if(cnt==k)  //如果计数器的编号等于要找的编号，输出
                {
                    cout<<i<<" "<<j<<" ";   //输出横坐标和纵坐标
                    if(t==1) cout<<'L';  //输出是左还是右
                    else cout<<'R';
                    putchar('\n');  //换行
                    return 0;   //结束，return 0
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Chtholly_L (赞：1)

### 题意：

有一个 $n×m$ 的矩阵，矩阵上的每一个坐标上都有两个座位，每个座位上都有一个编号，从 $1$ 到 $n×m×2$ 。

现在给你一个编号，求出该点的坐标以及座位是在左边还是在右边。

---

### 分析：

这道题一看见有矩阵，就想到了开二维数组，但是这道题涉及到了一个坐标上有两个数据，会很复杂，再加上开二维数组可能会很慢（之前因此模拟赛爆零的痛苦记忆犹新啊），就否定了二维数组。

那么我们可以用设么方法？对，枚举，枚举出每个编号，在输出他的具体坐标就好了。用三重循环，依次枚举行、列、和左右。

---

### AC代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m,k,ans=0;  //ans 用于枚举编号
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)  //行
	{
		for(int j=1;j<=m;j++)  //列
		{
			for(int l=1;l<=2;l++)  //左右
			{
				ans++;
				if(k==ans)
				{
					cout<<i<<" "<<j;
				    if(l==1)cout<<" L";
				    else cout<<" R";
				    return 0;
				}
			}
		}
	}
}
```
---

再见！

---

## 作者：Creator_157 (赞：1)

~~蒟蒻来水一发模拟的题解~~


------------

### 题目大意(标号规则）
给你一个 $n$ 行 $2m$ 列的矩阵，矩阵的每个元素按从左到右、从上到下的顺序 从1~ $2mn$ 顺次标号。已知一个人的标号 $k$ ，求这个人在矩阵中的位置。


------------
### 思路
先创造一个空的座位表，按标号规则填座位表，直至填到 $k$ 为止，输出位置即可结束程序。


------------
### code
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n,m,k,o=1;
int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int l=1;l<=2;l++)
            {
                if(o==k)
                {
                    cout<<i<<" "<<j<<" ";
                    if(l%2==1)cout<<"L";
                    else cout<<"R";
                    return 0;
                }
                o++;
            }
        }
    }
    return 0;
}
```
~~求过~~

---

## 作者：4526_ (赞：1)

[题目链接](https://www.luogu.org/problem/CF748A)

紫题掉橙现场...

#### 主要思想：~~数论~~ 模拟？

大致思路：

1、显然直接由座位编号求行列数不方便，于是考虑由对应的桌子来求

2、根据题意把桌子编号，如下图所示

![无标题.png](https://i.loli.net/2019/09/07/LRcvWOGkpf58H7g.png)

3、由座位编号k求桌子编号pos：

k为偶数时，pos=k/2

k为奇数时，pos=(k+1)/2

若k为偶数，则k/2=(k+1)/2

综上，**pos=(k+1)/2**

4、由桌子编号求行列数（感觉翻译有点奇怪，以下行为横排(desk)，列为纵排(line)）

对于一般的桌子，**r=pos/n+1，d=pos%n**

但是这两个式子对于**pos==n的情况**并不适用，此时r=pos/n，d=n，按照上式算会到下一列的第0行

于是~~因为懒得写特判~~干脆将错就错，**pos-1**，解决了列的问题，而行都少了1，加回去即可

最后得到**pos=(k+1)/2-1，r=pos/n+1，d=pos%n+1**

5、至于位置的左右，显然k&1（k%2==1）为左，反之为右

AC代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int n,m,k,pos;

int main(){
    scanf("%d %d %d",&n,&m,&k);
    pos=(k+1)/2-1;
    printf("%d %d ",pos/m+1,pos%m+1);
    if(k&1) printf("L");
    else printf("R");
    return 0;
}
```

欢迎来[我的blog](https://www.luogu.org/blog/4526-Au/#)看看

---

## 作者：WNico (赞：1)

# [CF748A Santa Claus and a Place in a Class](https://www.luogu.org/problemnew/show/CF748A)

emmm。。一道紫色的水题

就是说座位按照这张图排列（不太好用文字形容。。）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)

两人一桌，告诉SantaClaus座号，一共的Desk、Lane数，回答Lane Desk 左/右。

稍微对着图推一下就能做出

------------

以下上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main(){
    std::ios::sync_with_stdio(false);//输出加速
    cin.tie(0);
    cin>>n>>m>>k;
    int s=(k+1)/2;					//桌子位置
    cout<<((s-1)/m+1)<<" "<<((s-1)%m)+1<<" "<<((k%2)?'L':'R');//Lane Desk L/R  写得比较凌乱
    return 0;
}
```

最后推一下[BLOG](https://a-wnico-blog.blog.luogu.org/#)~

---

## 作者：_Harrisonwhl_ (赞：0)

这道题可以不用 $O(nm)$ 的做法，有 $O(1)$ 的数学推理法。

首先，我们先看在左还是在右，也就是判断 $\dfrac{k}{2}$ 是否整除，如果余$1$，则在左，否则在右。

然后我们可以将他和他同桌的座位变成$1$个座位，看是第几个位置，如果 $k$ 是奇数，则这是第 $\dfrac{(k + 1)}{2}$ 在程序里也可表示为第`k / 2 + 1`个座位，如果是偶数，则为第 $\dfrac{k} {2}$ 个座位，我们将其命名为 $pos$。然后行数 $as1$ 应该是将 $pos$ 除以 $m$ 向上取整，列数 $as2$ 是 $pos-(as1-1)*m$。

可以得到代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,pos,as1,as2;
char as3;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    if (k % 2)
    {
    	pos = k / 2 + 1;
    	as3 = 'L';
    }
    else
    {
    	pos = k / 2;
    	as3 = 'R';
    }
    as1 = (int)ceil(pos * 1.0 / m);
    as2 = pos - (as1 - 1) * m;
    printf("%d %d %c",as1,as2,as3);
    return 0;
}
```

---

## 作者：南山不相逢 (赞：0)

# ~~本蒟蒻又双叒叕来水题解了~~
咳咳，废话不多说，直接进入今天的题解
[CF748A](https://www.luogu.com.cn/problem/CF748A)
~~说实话这题真的很水~~
### 题意
首先是输入，我们需要输入一行有n个桌子，一共有m行，以及圣诞老人的编号k即可。

其次是输入，输入他所在的坐标以及他是坐在左边（L）还是右边（R）就可以了，这道题还是很好理解的。~~翻译好评~~

### 本题思路
我在一开始做这道题的时候，首先想到的是用二维数组，但是经过一系列的尝试以后，发现用二维数组做这道题不太好做，于是我又换了一种思路——**模拟**。

没错，就是模拟，我们可以用一个循环嵌套来自己模拟一个二维矩阵，由于本题还需要判断圣诞老人座位的左右，所以需要用三重循环。
#### 主体代码（三重循环）：

```c	
for(int i=1;i<=n;i++) {//控制行 
        for(int j=1;j<=m;j++) {//控制列 
            for(int y=1;y<=2;y++) {//控制左右 
                sum++;//计数器
                if(k==sum) {
                    cout<<i<<" "<<j<<" ";
                    if(sum%2==1) {//判断左右并输出 
                        cout<<"L";
                    }
                    else {
                        cout<<"R";
                    }
                    return 0;//不要忘了结束 
                } 
            }
        }
    } 
```


在这个三重循环中，最外层控制行数，中间控制控制列数，最后控制左右，在这个程序中我们还需要一个计数器，每当循环一次，计数器就加一，当计数器与编号相等的时候，就可以输出圣诞老人的行、列了。最后，我们还需要在最后一个循环中用if判断左右，通过题意我们可以知道，当计数器为奇数的时候圣诞老人在左边，当计数器为偶数的时候圣诞老人在右边，判断以后直接输出“L”或者“R”就可以了。这道题还是很简单的。
### 最后，奉上本题的完整代码：

```c
#include<iostream>
#include<cstdio>
using namespace std;
int main() {
    int n,m,k,sum=0;//sum为计数器
    cin>>n>>m>>k;//简单的输入
    for(int i=1;i<=n;i++) {//控制行 
        for(int j=1;j<=m;j++) {//控制列 
            for(int y=1;y<=2;y++) {//控制左右 
                sum++;//计数器
                if(k==sum) {
                    cout<<i<<" "<<j<<" ";
                    if(sum%2==1) {//判断左右并输出 
                        cout<<"L";
                    }
                    else {
                        cout<<"R";
                    }
                    return 0;//不要忘了结束 
                } 
            }
        }
    } 
    return 0;//完结撒花 
}
```
~~感觉我的代码好丑~~

如果我的代码有什么问题或者可以改进的地方希望大家能够向我提出，谢谢大家啦！！！

~~管理大大求过~~

---

## 作者：Eason_AC (赞：0)

## Content
圣诞老人坐在一个桌子被摆成 $m$ 行 $n$ 列的教室里。每个桌子有两个座位，每个位置从左往右都有编号，依次为 $1,2,3,...,2\times n\times m$。已知圣诞老人坐在编号为 $k$ 的位置，求：

- 圣诞老人坐在第几列第几行。
- 圣诞老人的座位是在桌子的左边还是右边。

**数据范围：$1\leqslant n,m\leqslant 10000,1\leqslant k\leqslant 2\times 10^8$（$2\times n\times m$ 的最大值）。**
## Solution
首先，我们可以求出圣诞老人在第几列第几行。

我们不妨把一个桌子看成一个集体，然后这样编号：从第一列第一行开始，先从前往后，再从左往右，依次编号为 $1,2,3,...,n\times m$。那么，我们发现，圣诞老人此时的编号 $s$ 就是 $\left\lceil\dfrac{k}{2}\right\rceil$。然后我们可以根据这个来求出列数和行数，分别是 $\left\lceil\dfrac{s}{m}\right\rceil$，$\begin{cases}m&m\mid s\\s\mod m&m\nmid s\end{cases}$。

至于在左在右的问题，那就更简单了：如果 $k$ 是奇数，那么就应该坐在桌子的左边，否则就应该坐在桌子的右边。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int n, m, k, mm, r, l;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	mm = (int)ceil(k / 2.0);
	r = (int)ceil(mm * 1.0 / m), l = (mm % (m + 1) + 1);
	printf("%d %d %c", r, l, (k % 2 ? 'L' : 'R'));
}
```

---

## 作者：_Legacy (赞：0)

### 分析：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)
这题看起来比较麻烦，不仅有 XY 两个方位，一个点还分左右，其实用三层 for 循环就可以搞定了。
### 原理：
按照他的特点：每两个号数一桌，m 桌一列分成 i , j , k 


------------

### 上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,o,s=0;
int main(){
	cin >> n >> m >> o;//n是列，m是行，o是目标号数。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<2;k++){//k控制左右。
				s++;//s是记录号数。
				if(o==s){
					cout << i << " " << j << " ";
					if(k==1) cout << "R";
					else cout << "L";
				}
			}
		}
	}
}
//CF748A
```


------------

蒟蒻的第2篇题解，求过

---

## 作者：shenmadongdong (赞：0)

判断一下即可

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c,h,t;
    cin>>a>>b>>c;
    h=(c+1)/2;
    t=h%b;
    if (t==0) t=b;
    cout<<(h-1)/b+1<<' '<<t<<' ';
    if (c%2==0) cout<<"R"; else cout<<"L";
}

```

---

