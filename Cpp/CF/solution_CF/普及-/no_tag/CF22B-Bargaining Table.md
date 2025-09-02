# Bargaining Table

## 题目描述

Bob wants to put a new bargaining table in his office. To do so he measured the office room thoroughly and drew its plan: Bob's office room is a rectangular room $ n×m $ meters. Each square meter of the room is either occupied by some furniture, or free. A bargaining table is rectangular, and should be placed so, that its sides are parallel to the office walls. Bob doesn't want to change or rearrange anything, that's why all the squares that will be occupied by the table should be initially free. Bob wants the new table to sit as many people as possible, thus its perimeter should be maximal. Help Bob find out the maximum possible perimeter of a bargaining table for his office.

## 样例 #1

### 输入

```
3 3
000
010
000
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 4
1100
0000
0000
0000
0000
```

### 输出

```
16
```

# 题解

## 作者：灵光一闪 (赞：5)

这是我的第……n篇题解！

 首先，看见了这个样例……，我就觉得我这个蒟蒻做不出来的……，然后……数据范围居然只有**25鸭鸭鸭鸭鸭鸭！！**，瞬间有了思路：
 # 暴力模拟
 然后，我就写了两个函数：
 ## checker:
 ```
 bool checker(int x1,int y1,int x2,int y2)//这个你们自己看，应该看得懂，如果不懂欢迎私信
{
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++)
            if(a[i][j]=='1')//如果有1就false
                return false;
    return true;//不然就true
}
 ```
 ## C(周长:
 ```
 int C(int x1,int y1,int x2,int y2)
{
    return ((x2-x1+1)+(y2-y1+1))*2;//周长公式，自己理解~
}
```
 ~~路人甲：源代码驾到！~~
 ```
 //#include<bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<string>
#include<cmath>
#include<map>

using namespace std;
char a[30][30];
bool checker(int x1,int y1,int x2,int y2)
{
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++)
            if(a[i][j]=='1')
                return false;
    return true;
}
int C(int x1,int y1,int x2,int y2)
{
    return ((x2-x1+1)+(y2-y1+1))*2;
}
int ans;
int n,m;
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>a[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<n;k++)
                for(int l=0;l<m;l++)
                    if(checker(i,j,k,l)&&i<=k&&j<=l)//如果既没有1又是个矩形
                        ans=max(ans,C(i,j,k,l));//更新一下
    cout<<ans;//cout
    return 0;//return
}
 ```
 源代码的AC记录：
 ![](https://cdn.luogu.com.cn/upload/pic/59731.png)

---

## 作者：封禁用户 (赞：3)

### 前言

二维前缀和我也调了半个小时，我越来越渣渣了！

### 分析

刚看到这题目想了很多，暴力、悬线法、二维前缀和 …… 然后想了一下，悬线法写起来比较麻烦，二维前缀和是个不错的选择毕竟，$n,m \le 25$ 那么这么小的数据范围 $O(n^4)$ 应该可以过的！

然后就是判断周长。

我思考了一下，手推出来了一个式子：$((x_1-x+1)+(y_1-y+1)) \times 2$，$x_1$ 和 $y_1$ 是右下角的坐标，$x$ 和 $y$ 是左上角的坐标。

```cpp
        scanf("%d %d\n",&n,&m);//读入 n 和 m。
        for (int i=1; i<=n; i++) {//读入和处理二维前缀和。
                for (int j=1; j<=m; j++) {
                        char ch=' ';
                        scanf("%c",&ch);//字符读入。
                        if (ch=='0') sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//如果是等于 0 ，那么就不用 +1。
                        else sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+1;//否则+1。
                }
                scanf("\n");//注意换行符要读掉！因为换行符也算是一个字符。
        }
```

至于前面的二维前缀和的建立，可以画个图来想想看。

```cpp
        for (int x=1; x<=n; x++)
                for (int y=1; y<=m; y++)
                        for (int x_=x; x_<=n; x_++)
                                for (int y_=y; y_<=m; y_++) {//暴力枚举四个坐标！
                                        if ((sum[x_][y_]-sum[x_][y-1]-sum[x-1][y_]+sum[x-1][y-1])==0) {//二维前缀和判断，是否这个矩阵全部都是 0 。 
                                                ans=max(((x_-x+1)+(y_-y+1))*2,ans);//套用计算周长式子来比较最大值。
                                                // printf("%d %d %d %d\n",x_,y_,x,y);
                                        }
                                }
        printf("%d\n",ans);//然后输出答案。
```

### 代码

放下完整代码，实际上如果你前面都读过了，那么这个完整代码是不用看的。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=27;
int n,m,sum[INF][INF],ans;
signed main()
{
        scanf("%d %d\n",&n,&m);
        for (int i=1; i<=n; i++) {
                for (int j=1; j<=m; j++) {
                        char ch=' ';
                        scanf("%c",&ch);
                        if (ch=='0') sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
                        else sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+1;
                }
                scanf("\n");
        }
        for (int x=1; x<=n; x++)
                for (int y=1; y<=m; y++)
                        for (int x_=x; x_<=n; x_++)
                                for (int y_=y; y_<=m; y_++) {
                                        if ((sum[x_][y_]-sum[x_][y-1]-sum[x-1][y_]+sum[x-1][y-1])==0) {
                                                ans=max(((x_-x+1)+(y_-y+1))*2,ans);
                                                // printf("%d %d %d %d\n",x_,y_,x,y);
                                        }
                                }
        printf("%d\n",ans);
        return 0;
}

```
### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：小恐 (赞：3)

~~恕我直言，这题数据实在太水！，有好多复杂度超高的算法都过了！~~

这里给出一个$O(n^2\times m)$的算法。

首先如果判断是都用$for$循环枚举前面是否都是1的话，复杂度又高了，所以求出每个字符在这一行里前面（包括它自己）有多少个连续的0，这样就不用每次枚举了。

然后枚举所有截取一行的方法，这样就相当于把从几列到几列定下来了。然后枚举每一行，如果它在从这列到这列都是0，就$dp=dp+1$，然后更新答案，否则$dp=0$。

好了，上代码吧：
```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
char a[30][30];
int qian[30][30];
int dp;
int ans;
int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i)
		scanf("%s",a[i]+1);           //读入 
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)        //求前面有多少个0
		{
			if(a[i][j]=='1')
				qian[i][j]=0;
			else
				qian[i][j]=qian[i][j-1]+1;
		}
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)   //枚举截取所有方法 
		{
			int len=j-i+1;//算出长度 
			dp=0;//初值 
			for(int k=1;k<=m;++k)//枚举每行 
			{
				if(qian[k][j]>=len)//如果都是0 
					dp+=1,ans=max(2*(dp+len),ans);//dp+1，更新答案 
				else
					dp=0;//到这停！重新开始！ 
			}
		}
	printf("%d",ans);
	return 0;
}
```

珍惜你的账号，抄题解会棕名的哦。

PS：2020-04-20：发现一点小错，现已更正

---

## 作者：ahawzlc (赞：3)

~~NOIO2 要来了，考前要练练暴力，要不挂了怎么办呢~~。

----

因为$1\le n,m \le 25$ 的数据范围，我们可以写一个暴力。枚举矩形的左上端点和右下端点，然后判断**边框**是否有```1```，如果合法就取$\max$，否则就```break```。

Tips：

1. 注意是判断边框即可。
2. 在判断边框的时，可以用 4 个 ```while``` 猛冲，如果中途结束，那么说明边框不合法。
3. 枚举左上端点$(x1,y1)$和右下端点$(x2,y2)$时注意$x2\ge x1,y2\ge y1$。

``` cpp
#include<bits/stdc++.h>
using namespace std;
char ch[30][30];
int ans;
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>ch[i][j];
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			for(int k=i;k<=n;k++) {
				for(int l=j;l<=m;l++) {
					int I=i,J=j;
					while(J<l&&ch[I][J]=='0') J++;
					if(J!=l) break;
					while(I<k&&ch[I][J]=='0') I++;
					if(I!=k) break;
					while(J>j&&ch[I][J]=='0') J--;
					if(J!=j) break;
					while(I>i&&ch[I][J]=='0') I--;
					if(I!=i) break;
					ans=max(ans,2*(k-i+1+l-j+1));
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：qzhwmjb (赞：2)

### 思路
---
本题暴搜即可，  
从左上角和右下角开搜，需要4个循环。  
从样例 $1$ 中可知：    
- 所指矩阵是没有要求实心的,如下图:  
![](https://cdn.luogu.com.cn/upload/image_hosting/mey25l9e.png)  
那我们在 $4$ 中再来 $4$ 个循环判断各个边上是否有 $1$。
- 有：$break$
- 没有：比较之前最大周长 $ans$ 和当前周长，取大值。
后输出即可。
### 代码
---
```
#include<Bits/stdc++.h>//防伪标记
using namespace std;
char c[30][30];
int ans;
int n,m;
int i,j,k,l;
int a,b;
int main() {
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			cin>>c[i][j];
		}
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			for(k=i;k<=n;k++) {
				for(l=j;l<=m;l++) {
					a=i,b=j;
					while(b<l&&c[a][b]=='0'){
						b++;
					}
					if(b!=l){
						break;
					}
					while(a<k&&c[a][b]=='0'){
						a++;
					}
					if(a!=k){
						break;
					}
					while(b>j&&c[a][b]=='0'){
						b--;
					}
					if(b!=j){
						break;
					}
					while(a>i&&c[a][b]=='0'){
						a--;
					}
					if(a!=i){
						break;
					}
					ans=max(ans,2*(k-i+1+l-j+1));
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



---

