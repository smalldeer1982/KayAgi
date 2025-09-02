# Li Hua and Chess

## 题目描述

This is an interactive problem.

Li Ming and Li Hua are playing a game. Li Hua has a chessboard of size $ n\times m $ . Denote $ (r, c) $ ( $ 1\le r\le n, 1\le c\le m $ ) as the cell on the $ r $ -th row from the top and on the $ c $ -th column from the left. Li Ming put a king on the chessboard and Li Hua needs to guess its position.

Li Hua can ask Li Ming no more than $ 3 $  questions. In each question, he can choose a cell and ask the minimum steps needed to move the king to the chosen cell. Each question is independent, which means the king doesn't actually move.

A king can move from $ (x,y) $ to $ (x',y') $ if and only if $ \max\{|x-x'|,|y-y'|\}=1 $ (shown in the following picture).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/56c04da34d7867634f352a46b9f12f7f08ae1115.png)The position of the king is chosen before the interaction.

Suppose you were Li Hua, please solve this problem.

## 说明/提示

In test case 1, the king is at $ (2,2) $ . It takes $ 1 $ step to move to $ (2,3) $ and $ 2 $ steps to move to $ (2,4) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/abf76b4ca2a66dfff2b7a8197cf3c1622c8fee3f.png)Note that the questions may not seem sensible. They are just a sample of questions you may ask.

## 样例 #1

### 输入

```
2
3 4

1

2

5 3

3

1

2```

### 输出

```
? 2 3

? 2 4

! 2 2

? 2 2

? 5 2

? 5 3

! 5 1```

# 题解

## 作者：zzhbpyy (赞：3)

首先考虑询问 $(1,1)$ 和 $(1,m)$ 点，将结果记为 $a$ 和 $b$。

分类讨论：

1. $a+b=m-1$：国王一定在纵坐标为 $a+1$ 的一条横行上，直接询问 $(1,a+1)$。

2. 否则，若 $a=b$：国王一定在横坐标为 $b+1$ 的一条纵列上，直接询问 $(a+1,1)$。

3. 否则可以唯一确定国王的位置：当 $a<b$ 时国王在 $(a+1,m-b)$，否则在 $(b+1,a+1)$。

## 完整代码

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,a,t,b,c,d,e,f;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		cout<<"? 1 1"<<endl;
		cin>>a;
		cout<<"? 1 "<<m<<endl;
		cin>>b;
		if(a+b==m-1){
			cout<<"? 1 "<<a+1<<endl;
			cin>>c;
			cout<<"! "<<c+1<<' '<<a+1<<endl;
			continue;
		}
		if(a==b){
			cout<<"? "<<a+1<<" 1"<<endl;
			cin>>c;
			cout<<"! "<<a+1<<' '<<c+1<<endl;
			continue;
		}
		if(a<b){
			cout<<"! "<<a+1<<' '<<m-b<<endl;
		}
		else cout<<"! "<<b+1<<' '<<a+1<<endl;
	}
}
```

---

## 作者：DE_aemmprty (赞：2)

### 1 题意

有一个 $n \times m$ 的网格。A 可以问 B 不超过 $3$ 个问题，每个问题为王从开始走到 $(x,y)$ 的最短距离是多少。你需要确定王的位置。

### 2 解题分析

VP 的时候自闭了很久。于是开始玩样例。

玩了一会样例，发现假设这个王离 $(x, y)$ 距离为 $k$，那么王的位置为以 $(x,y)$ 为中心画一个边长为 $2k + 1$ 的正方形。那么，先询问 $(1, 1)$ 和 $(1, m)$。假设答案为 $a, b$，那么会有很多种情况。

* $a + b + 1 > m$ 且 $a \neq b$。此时，两个正方形只有一个交点，算一下即可。

* $a + b + 1 > m$ 且 $a = b$。此时，两个正方形交于最下面的一行连续段，取其左端点或者右端点询问即可。

* $a + b + 1 = m$。此时，两个正方形交于一段竖的段，取最上面的点询问即可。

### 4 AC Code

只选了最重要的一段代码。

```cpp
void solve() {
    cin >> n >> m;
    printf("? %lld %lld\n", 1ll, 1ll);
    fflush(stdout);
    cin >> a;
    printf("? %lld %lld\n", 1ll, m);
    fflush(stdout);
    cin >> b;
    if (a == b && a + b + 1 > m) {
        printf("? %lld %lld\n", a + 1, (a < m ? m - a : 1)); fflush(stdout);
        cin >> c;
        printf("! %lld %lld\n", a + 1, (a < m ? m - a : 1) + c);
        fflush(stdout);
        return ;
    }
    if (a + b + 1 > m) {
        if (a > b)
            printf("! %lld %lld\n", b + 1, a + 1);
        else
            printf("! %lld %lld\n", a + 1, m - b);
        fflush(stdout);
        return ;
    }
    int x = 1;
    int y = a + 1;
    printf("? %lld %lld\n", x, y); fflush(stdout);
    cin >> c;
    printf("! %lld %lld\n", 1 + c, y);
    fflush(stdout);
}
```

---

## 作者：LinuF (赞：2)

~~vp的时候遇到的一个很有趣的交互题。~~
### 题目意思

**这是一道交互题。**

在棋盘上定义一个位置 $(x,y)$，移动可以向着八个方向移动一格。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/og1rbslb.png)

题目要求你找到一个位置 $(x,y)$。

你最多进行三次询问一个位置 $(x',y')$，交互库会告诉你从 $(x,y)$ 移动到 $(x',y')$ 的最短距离。 

### 思路

拿到题目应该会去思考边角和需要找到的那个位置的关系，通过模拟可以看出距离一个点距离为一个固定值 $k$ 在图上的表现是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/gu1m80qh.png)

在查询最左上角 $(1,1)$ 时，交互库会返回距离 $4$ 而对于这个距离，有可能的点只有上图蓝色部分。

这个时候我们可以再查询点 $(1,4)$ 得到的距离为 $4$ 那么此时我们就可以断定点的横坐标在 $4$ 上，我们再查询点 $(4,1)$ 就可以直接确定点的方位了。

通过模拟上述的过程我们就可以得到一种写法，首先查询点 $(1,1)$  获得距离 $t$ ，再查询点 $(1,1+t)$ 或者点 $(t+1,1)$ 这个要根据条件判断，然后这个时候就能够确定点的横坐标或者纵坐标，再查询这个一行或者这一列的第一个点，就能确定答案的坐标了。

这种做法就要考虑一下边界的问题，考虑返回的 $t$ 与 $n$ 和 $m$ 的关系，画个图就可以解决了。

### 代码

要注意交互题的格式。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;

int ask(int x,int y){
    cout<<"?"<<" "<<x<<" "<<y << endl;
    int t;
    cin>>t;
    return t;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int x,y;
        cin>>n>>m;
        int t1=ask(1,1);
        if(t1>=n){
            cout<<"? "<<1<<" "<<1+t1<< endl;
            int t2;
            cin>>t2;
            cout<<"! "<<1+t2<<" "<<1+t1<<endl;
        }
        else if(t1>=m){
            cout<<"? "<<1+t1<<" "<<1<<endl;
            int t2;
            cin>>t2;
            cout<<"! "<<1+t1<<" "<<1+t2<<endl;
        }
        else{
            cout<<"? "<<1+t1<<" "<<1<<endl;
            int t2;
            cin>>t2;
            cout<<"? "<<1<<" "<<1+t2<<endl;
            int t3;
            cin>>t3;
            cout<<"! "<<1+t3<<" "<<1+t2<<endl;
        }
    }
}
```


---

## 作者：abensyl (赞：2)

原题：[CF1797C Li Hua and Chess](https://www.luogu.com.cn/problem/CF1797C)。

中国出题组好评，出的题目质量确实也不错。

同时本题也是我赛时第一道交互题。

## 思路

- 随意询问一个点 $(x,y)$，如果国王的坐标为 $(a,b)$，则最少步数是多少呢？

> 这个问题很简单。由于国王是可以斜着走的，那么这个距离就是 $max(|x-a|,|y-b|)$。

- 所以说我们考虑询问每次都先两个固定点，$(1,1)$ 和 $(n,m)$。

而当我们知道了一个点的坐标 $(x,y)$ 以及这个点离国王的最小步数 $k$，那么我们就可以知道国王的运动轨迹，其运动轨迹理论上是一个正方形，其四个顶点则坐标分别是 $(x-k,y-k)$、$(x-k,y+k)$、$(x+k,y-k)$ 和 $(x+k,y+k)$。当然，这个正方形上有一些点已经跃出了棋盘，而国王不可能出现在那个位置。

但我们得到两个正方形以后，我们可以对两个正方形的交点进行讨论，两个正方形相交有三种情况，如下图所示：

![](https://www.mfstem.org/file/241/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-04-02%20135223.png)

> 1. 对于第一种情况，直接输出交点即可，两次询问解决问题。

> 2. 对于第二种情况，输出其中一个交点，如果距离为 $0$，则就是这个交点，否则是另一个交点，三次询问解决问题。

> 3. 对于第三种情况要麻烦一些，第一，重合的边有可能是数值或水平方向的，第二，边上有很多个点，不能直接排除法进行尝试。  
> 我们可以选择输出这条线段的一个端点，然后输出的结果 $k$ 就说明国王在这条线段上到这个端点距离为 $k$ 的点，直接输出即可，三次询问解决问题。

注意：询问时，**不能询问棋盘外的点**，否则就会 WA。

## 代码

```cpp
#include <iostream>
using namespace std;
inline void query(int x, int y) { cout << "? " << x << ' ' << y << endl; }
inline void getans(int x, int y) { cout << "! " << x << ' ' << y << endl; }
int main() {
  int TT;
  cin >> TT;
  while (TT--) {
    int n, m;
    cin >> n >> m;
    query(1, 1);
    int r1;
    cin >> r1;
    int sax = min(n, 1 + r1), say = min(m, 1 + r1);
    query(n, m);
    int r2;
    cin >> r2;
    int sbx = max(1, n - r2), sby = max(1, m - r2);
    if (sax == sbx && say == sby) {
      getans(sax, say);
    } else if (sax == sbx) {
      query(sax, min(say, sby));
      int zc;
      cin >> zc;
      getans(sax, min(say, sby) + zc);
    } else if (say == sby) {
      query(min(sax, sbx), say);
      int zc;
      cin >> zc;
      getans(min(sax, sbx) + zc, say);
    } else {
      query(sax, sby);
      int zc;
      cin >> zc;
      if (zc == 0)
        getans(sax, sby);
      else
        getans(sbx, say);
    }
  }
  return 0;
}
```
我的 [AC 记录](https://codeforces.com/contest/1797/submission/201336591)。

---

## 作者：hcywoi (赞：2)

## 题意

**这是一道交互题。**

定义一个位置 $(x, y)$，移动一步后的位置为 $(x\pm1,y\pm1)$。

你需要找到一个位置 $(x, y)$。

你至多进行 $3$ 次询问，每次询问格式为 `? a b`。

交互库会返回 $(x, y)\to (a, b)$ 的最小移动步数。

---

## 题解

还是比较有趣的一题。

不难发现，交互库返回的是 $\max\{\vert a-x\vert, \vert b-y\vert\}$。

我们先 `? 1 1`，则知道了 $d=\max\{a-1, b-1\}$ 即 $\max\{a, b\}=d+1$。

如果 $d+1\le n$ 且 $d+1\le m$ 则询问 `? d+1 d+1`，知道了 $d'=\max\{d+1-(d+1), d+1-\min\{x, y\}\}=d+1-\min\{x, y\}$，即 $\min\{x, y\}=d+1-d'$，接着继续询问 `? min{x, y} max{x, y}`，判断 $x=\min\{x, y\}$ 还是 $y=\min\{x, y\}$。

否则，直接特判即可。

[代码。](https://codeforces.com/contest/1797/submission/201667544)

---

## 作者：luan341502 (赞：0)

补一发题解。

对于每一组数据，考虑第一个询问。可以证明选四个顶点上的点最优。因为若选棱上的点，最劣情况下有三条线段上的点可能被取到，而中间的点最劣时可能有四条线段上的点被取到。询问顶点时，最多只有两条线段上的点被取到，这对我们接下来的询问有利。

方便起见，我们询问 $(1,1)$，得到的结果记为 $x$。

当 $x<m$ 并且 $x<n$ 即最劣情况下有两条线段上的点可以被取到，即 $(1,x+1)$ 到 $(x+1,x+1)$ 和 $(x+1,1)$ 到 $(x+1,x+1)$。可以发现两条线段交汇在 $(x+1,x+1)$ 上，因此我们询问 $(x+1,x+1)$ 的话，就可以将答案范围缩小到最多取到两个点。具体地，若将第二次询问得到的结果记为 $y$，答案就为 $(x+1,x-y+1)$ 和 $(x-y+1,x+1)$ 两点其中之一。我们询问其中一个点进行判断即可。

对于其他情况，只有一条线段上的点可取。类似地判断即可。

注意在询问的过程中若得到的结果为 $0$，需立即停止询问，输出答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005][1005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		cout<<"? 1 1"<<endl;
		fflush(stdout);
		int x;
		cin>>x;
		if(!x){
			cout<<"! "<<1<<" "<<1<<endl;
			continue;
		}
		if(x+1<=m&&x+1<=n){
			cout<<"? "<<x+1<<" "<<x+1<<endl;
			fflush(stdout);
			int y;
			cin>>y;
			if(!y){
				cout<<"! "<<x+1<<" "<<x+1<<endl;
				continue;
			}
			cout<<"? "<<x+1<<" "<<x+1-y<<endl;
			fflush(stdout);
			int z;
			cin>>z;
			if(!z) cout<<"! "<<x+1<<" "<<x-y+1<<endl;
			else cout<<"! "<<x-y+1<<" "<<x+1<<endl;
		}else if(x+1>m){
			cout<<"? "<<x+1<<" "<<m<<endl;
			fflush(stdout);
			int y;
			cin>>y;
			if(!y){
				cout<<"! "<<x+1<<" "<<m<<endl;
				continue;
			}
			cout<<"? "<<x+1<<" "<<m-y<<endl;
			fflush(stdout);
			int z;
			cin>>z;
			if(!z) cout<<"! "<<x+1<<" "<<m-y<<endl;
			else cout<<"! "<<x-y+1<<" "<<m<<endl;
		}else{
			cout<<"? "<<n<<" "<<x+1<<endl;
			fflush(stdout);
			int y;
			cin>>y;
			if(!y){
				cout<<"! "<<n<<" "<<x+1<<endl;
				continue;
			}
			cout<<"? "<<n-y<<" "<<x+1<<endl;
			fflush(stdout);
			int z;
			cin>>z;
			if(!z) cout<<"! "<<n-y<<" "<<x+1<<endl;
			else cout<<"! "<<n<<" "<<x-y+1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

考虑首先询问 $(1,1)$ 点。

设得到的答案是 $a$，那么 $\max(x,y)$ 的值一定是 $a+1$。所以 $x=a+1$ 或者 $y=a+1$。

然后考虑判断他是在哪一条线上，询问 $(1,a)$ 即可。

然后确定他的位置，询问 $(a,a)$ 即可。

---

