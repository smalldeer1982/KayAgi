# Timofey and rectangles

## 题目描述

One of Timofey's birthday presents is a colourbook in a shape of an infinite plane. On the plane $ n $ rectangles with sides parallel to coordinate axes are situated. All sides of the rectangles have odd length. Rectangles cannot intersect, but they can touch each other.

Help Timofey to color his rectangles in $ 4 $ different colors in such a way that every two rectangles touching each other by side would have different color, or determine that it is impossible.

Two rectangles intersect if their intersection has positive area. Two rectangles touch by sides if there is a pair of sides such that their intersection has non-zero length

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF763B/1e56315d730703e37fe416b7a434283dfefe0bca.png)The picture corresponds to the first example

## 样例 #1

### 输入

```
8
0 0 5 3
2 -1 5 0
-3 -4 2 -1
-1 -1 2 0
-3 0 0 5
5 2 10 3
7 -3 10 2
4 -2 7 -1
```

### 输出

```
YES
1
2
2
3
2
2
4
1
```

# 题解

## 作者：YCE__22 (赞：4)

题意：给出n个矩形的左下角和右上角的坐标定点，并保证矩形边长为奇数，给矩形涂色并保证相接触的矩形颜色不同，问能否用四种不同的颜色完成

分析：根据四色定理知道，四种颜色一定能完成染色。 （表示对四色定理毫不知情~Orz）

因为所有矩形的边长均为奇数，所以可以根据矩形左下角纵横坐标的奇偶性来把矩形分为四类（奇奇，偶偶，奇偶，偶奇） 
偶偶涂1号色，偶奇涂2号色，奇偶涂3号色，奇奇涂4号色

代码：
```cpp
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,a,b,c,d;
    scanf("%d",&n);
    printf("YES\n");
    while(n--)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        printf("%d\n",2*(abs(a)&1)+(abs(b)&1)+1);
    }
    return 0;
}

```
ps：我这种智商弱爆了的真是不适合做这种题啊~Orz

---

## 作者：WRuperD (赞：2)

神仙题

第一篇题解太简略了，本篇题解作为补充。

首先，根据四色定理，必有解。于是考虑如何构造出答案。

注意到，**矩形的所有边的长度都是奇数**。

发现，对于两个矩形左下角坐标 $(x_i,y_i)$ 和 $(x_j,y_j)$，若满足 $x_i$ 和 $x_j$ 奇偶性相等且 $y_i$ 和 $y_j$ 奇偶性相等，则这两个矩形必定互不相邻，可以为同种颜色。这就一共有四类了，输出即可。

代码：

```cpp
// Problem: Timofey and rectangles
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF763B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)


#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")

const int MAX = 5e5+10;
const int MAX2 = 1e9;
int dx[MAX], dy[MAX], ex[MAX], ey[MAX];

void solve(){
	puts("YES");
	int n = read();
	for(int i = 1; i <= n; i++){
		int dx = read(), dy = read(), ex = read(), ey = read();
		if(dx % 2 and dy % 2)	puts("4");
		else if(dx % 2)	puts("3");
		else if(dy % 2)	puts("2");
		else puts("1");	
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```


---

## 作者：_Winham_ (赞：0)

题目意思：

题目给的也比较清晰，但我还是讲一下吧。

就是一个平面上有 $n$ 个矩形，其中这些矩形是我们输入的。其中每个矩形最多只能相邻，不能相交。现在我们要给这些矩形涂上 $1$、$2$、$3$ 和 $4$ 四种颜色，得让相邻的矩形颜色不同。

---

思路：

很简单，根据四色定理，就能知道所有的方案都是对的，而四色定理就是说在不引起混淆的情况下一张地图只需四种颜色来标记就行了。

而由于 `矩形的所有边的长度都是奇数` 我们就能把矩形第一个下标来分析奇偶性。分为以下几部分：

- $x_{i}$ 与 $x_{y}$ 都为偶数，输出 $1$。
- $x_{i}$ 与 $x_{y}$ 中 $x_{i}$ 为偶数，$x_{y}$ 为奇数，输出 $2$。
- $x_{i}$ 与 $x_{y}$ 中 $x_{i}$ 为奇数，$x_{y}$ 为偶数，输出 $3$。
- $x_{i}$ 与 $x_{y}$ 都为奇数，输出 $4$。

---

代码

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int n,ans[2][2]={{1,2},{3,4}};
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n;
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(!(a&1)&&!(b&1))cout<<ans[0][0]<<endl;
		if(!(a&1)&&(b&1))cout<<ans[0][1]<<endl;
		if((a&1)&&!(b&1))cout<<ans[1][0]<<endl;
		if((a&1)&&(b&1))cout<<ans[1][1]<<endl;
	}
	return 0;
}


```

---

