# Steps

## 题目描述

One day Vasya went out for a walk in the yard but there weren't any of his friends outside and he had no one to play touch and run. But the boy didn't lose the high spirits and decided to play touch and run with himself. You may ask: "How did he do that?" The answer is simple.

Vasya noticed that the yard is a rectangular $ n×m $ field. The squares have coordinates $ (x,y) $ ( $ 1<=x<=n,1<=y<=m $ ), where $ x $ is the index of the row and $ y $ is the index of the column.

Initially Vasya stands in the square with coordinates ( $ x_{c},y_{c} $ ). To play, he has got a list of $ k $ vectors $ (dx_{i},dy_{i}) $ of non-zero length. The game goes like this. The boy considers all vectors in the order from $ 1 $ to $ k $ , and consecutively chooses each vector as the current one. After the boy has chosen a current vector, he makes the maximally possible number of valid steps in the vector's direction (it is possible that he makes zero steps).

A step is defined as one movement from the square where the boy is standing now, in the direction of the current vector. That is, if Vasya is positioned in square $ (x,y) $ , and the current vector is $ (dx,dy) $ , one step moves Vasya to square $ (x+dx,y+dy) $ . A step is considered valid, if the boy does not go out of the yard if he performs the step.

Vasya stepped on and on, on and on until he ran out of vectors in his list. Ha had been stepping for so long that he completely forgot how many steps he had made. Help the boy and count how many steps he had made.

## 说明/提示

In the first sample Vasya is initially positioned at square $ (1,1) $ and makes $ 3 $ steps by the first vector $ (1,1) $ . So, he consecutively visits the squares $ (2,2),(3,3),(4,4) $ . Then he makes $ 0 $ steps by the second vector $ (1,1) $ . He makes $ 1 $ more step by the third vector $ (0,-2) $ and he ends up in square $ (4,2) $ . Overall, Vasya makes $ 4 $ steps.

In the second sample Vasya is initially positioned in square $ (1,2) $ and makes $ 0 $ steps by vector $ (-1,0) $ , as the square with coordinates $ (0,2) $ is located outside the yard.

## 样例 #1

### 输入

```
4 5
1 1
3
1 1
1 1
0 -2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 10
1 2
1
-1 0
```

### 输出

```
0
```

# 题解

## 作者：zlqwq (赞：3)

## 思路：

直接模拟。

只要当前的路径还可以走就接着走。

将横坐标和纵坐标可以走的步数取 $\min$ 作为最终可以走的步数，然后把这个数加在答案里。

完了吗？没有！


不开 long long 见祖宗。


```cpp
#include<iostream>
#include<cmath>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18
using namespace std;

int n,m,k,x,y,t; 
int ans;
signed main() {
	cin >> n >> m >> x >> y >> k;
	for(int i = 1;i <= k;++i) {
		int dx,dy;
		cin >> dx >> dy;
		t = inf;
		if(dx > 0) {
			int nx = n - x;
			t = min(t,nx / dx);
		}
		else if(dx < 0) {
			int nx = 1 - x;
			t = min(t,nx / dx);
		}
		if(dy > 0) {
			int ny = m - y;
			t = min(t,ny / dy);
		}
		else if(dy < 0) {
			int ny = 1 - y;
			t = min(t,ny / dy);
		}
		x += t * dx;
		y += t * dy;
		ans += t;
	}
	cout << ans;
	return 0;
}

```

---

## 作者：_Maverick_ (赞：1)

## 思路
这道题就是模拟每次取出一个向量能走的最大的步数。需要注意的是要考虑 $d_x$，$d_y$ 的符号问题，所以需要分情况讨论。
## ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x, y, k, a, b ;
long long n, m, sum, i ;
int main() {
	cin >> n >> m;
	cin >> x >> y;
	cin >> k;
	for (i = 0 ; i < k ; i ++) {
		cin >> a >> b;
		int p, q ;
		if (a < 0) {
			p = (1 - x) / a ;
		} else if (a > 0) {
			p = (n - x) / a ;
		} else {
			p = 1000000000 ;
		}
		if (b < 0) {
			q = (1 - y) / b ;
		} else if (b > 0) {
			q = (m - y) / b ;
		} else {
			q = 1000000000 ;
		}
		long long w = min(p, q) ;
		sum += w ;
		x += a * w ;
		y += b * w ;
	}
	cout << sum << endl ;
	return 0 ;
}
```

---

## 作者：tzjahinie (赞：1)

### 题目链接：[CF152B](https://www.luogu.com.cn/problem/CF152B)

### 题目大意：

有一个长为 $n$，宽为 $m$ 的矩形。Vasya 初始在 $(x_c,y_c)$ 的方格上。有 $k$ 种走法，可以依次按照第 $i$ 种走法移动。在第 $i$ 种走法中，每次会移动往 $x$ 轴移动 $dx_i$ 步，往 $y$ 轴移动 $dy_i$ 步，一直走到无法继续移动（即不能越界）。求最终会走多少步。

### 题目思路：

如果有能以此种走法行走，则走到无法行走为止，接着以下一种走法行走。比较 $x$ 轴能走的步数与 $y$ 轴能走的步数取最小值。注意无论是 $x$ 轴和 $y$ 轴，往正方向的走法和反方向走法的边界是不一样的。其余直接模拟即可，但要一步到位，不然会超时。小提示：不开 long long 见祖宗。

### 提交记录

因为你古的 RemoteJudge 爆了，于是展示一下 CF 上的提交记录。

![提交记录](https://cdn.luogu.com.cn/upload/image_hosting/iqp10xn0.png)

![同上](https://cdn.luogu.com.cn/upload/image_hosting/sbk5xcje.png)

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x,y,t,dx,dy,ans;
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&x,&y,&k);
	for (int i=1;i<=k;i++){
		scanf("%lld%lld",&dx,&dy);
		t=0x3f3f3f3f;
			 if(dx>0)t=min(t,(n-x)/dx);
		else if(dx  )t=min(t,(1-x)/dx);
			 if(dy>0)t=min(t,(m-y)/dy);
		else if(dy  )t=min(t,(1-y)/dy);
		x+=t*dx,y+=t*dy;ans+=t;
	}
	printf("%lld",ans);
}
```

---

## 作者：OIer6666 (赞：1)

## 题目大意：

[题目传送门](https://www.luogu.com.cn/problem/CF152B)

给你一个 $n$ 行 $m$ 列的场地，再给你初始坐标，再给你 $k$ 个方位向量，从第 $1$ 个开始，按照向量走到场地边缘，走不了了，换下一个向量。求一共能走多少步。

## 解题思路：

按照题目模拟就行了。
1. 遍历向量数组，算横坐标和纵坐标能走多少步，取其最小值，即为可以移动的步数；
2. 进行移动，给答案加上步数。

**重要的事情说三遍！**

不开 `long long` 见祖宗！不开 `long long` 见祖宗！不开 `long long` 见祖宗！

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 1145141919810LL
#define int long long
int n,m,x,y,k,ans;
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>x>>y>>k;
    while(k--){
        int tx,ty;cin>>tx>>ty;
        int lx=0,ly=0;
        if(tx>0){
            int l=n-x;
            lx=l/tx;
        }else if(tx<0){
            tx=-tx;
            int l=x-1;
            lx=l/tx;
            tx=-tx;
        }else
            lx=INF;
        if(ty>0){
            int l=m-y;
            ly=l/ty;
        }else if(ty<0){
            ty=-ty;
            int l=y-1;
            ly=l/ty;
            ty=-ty;
        }else
            ly=INF;
        ans+=min(lx,ly);
        x=x+min(lx,ly)*tx,y=y+min(lx,ly)*ty;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：1)

# 题解：CF152B Steps
 [题目传送门](https://www.luogu.com.cn/problem/CF152B)
## 思路：
模拟一个，贪心，只要这条路能走，就要一直走下去，走搭没路为止。
## 算法：
  定一个函数，判断是往哪里走，走什么方向，求横坐标和纵坐标里所有可以通过的数的路，用循环 $stepsX$ 和 $stepsY$ 的最小值，最后将结果加到 $ans$ 中，最后输出即可。  

## 注意：
不开  long long 见祖宗！
## 完整代码

```cpp
#include<iostream>
#include<cmath>
#define int long long
#define inf 1e18
using namespace std;

// 计算在某个方向上能移动的步数
int cal(int c, int t, int dir) {
    int steps;
    if (dir > 0) {
        int r = t - c;
        steps = r / dir;
    } else if (dir < 0) {
        int r = 1 - c;
        steps = r / dir;
    }
    return steps;
}

int n, m, k, x, y, t;
int ans;

signed main() {
    cin >> n >> m >> x >> y >> k;
    //循环计算最小值
    for (int i = 1; i <= k; ++i) {
        int dx, dy;
        cin >> dx >> dy;
        t = inf;
        int stepsX = cal(x, n, dx);
        int stepsY = cal(y, m, dy);
        t = min(min(stepsX, stepsY), t);
        x += t * dx;
        y += t * dy;
        ans += t;
    }

    cout << ans;

    return 0;
}
```
我的的一篇题解，希望管理员通过，谢谢！

---

## 作者：forever516 (赞：0)

# 题意
自见题目。

# 解法
按题意模拟即可。

按当前的路一直走。

将横坐标和纵坐标可以走的步数取最小加在答案里即可。

代码如下。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAX 1e9
using namespace std;
ll n,m,k,x,y,t,ans=0,dx,dy;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m >> x >> y >> k;
	for(int i = 1;i <= k;++i) {
		cin >> dx >> dy;
		t = MAX;
		if(dx > 0)t = min(t,(n-x) / dx);
		else if(dx < 0)t = min(t,(1-x) / dx);
		if(dy > 0)t = min(t,(m - y) / dy);
		else if(dy < 0)t = min(t,(1 - y) / dy);
		x += t * dx;
		y += t * dy;
		ans += t;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

十年 OI 一场空，不开 ```long long``` 见祖宗。

模拟即可，当模拟到第 $i$ 种走法时，如果能以此种走法行走，则走到无法行走为止，接着以下一种走法行走。设 $x$ 轴共有 $x$ 种走法，$y$ 轴共有 $y$ 种走法，最后取 $ \min ( x ,y )$ 即可。但是注意无论是 $x$  轴和  $y$  轴，往正方向的走法的边界和反方向走法的边界是不一样的。

还有就是如果用 ```#define int long long``` 的话一定要用 ```signed main()``` 或者直接写成 ```main()```。

---

