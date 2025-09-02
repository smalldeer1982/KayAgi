# Bombs

## 题目描述

You've got a robot, its task is destroying bombs on a square plane. Specifically, the square plane contains $ n $ bombs, the $ i $ -th bomb is at point with coordinates $ (x_{i},y_{i}) $ . We know that no two bombs are at the same point and that no bomb is at point with coordinates $ (0,0) $ . Initially, the robot is at point with coordinates $ (0,0) $ . Also, let's mark the robot's current position as $ (x,y) $ . In order to destroy all the bombs, the robot can perform three types of operations:

1. Operation has format "1 k dir". To perform the operation robot have to move in direction $ dir $ $ k $ ( $ k>=1 $ ) times. There are only $ 4 $ directions the robot can move in: "R", "L", "U", "D". During one move the robot can move from the current point to one of following points: $ (x+1,y) $ , $ (x-1,y) $ , $ (x,y+1) $ , $ (x,y-1) $ (corresponding to directions). It is forbidden to move from point $ (x,y) $ , if at least one point on the path (besides the destination point) contains a bomb.
2. Operation has format "2". To perform the operation robot have to pick a bomb at point $ (x,y) $ and put it in a special container. Thus, the robot can carry the bomb from any point to any other point. The operation cannot be performed if point $ (x,y) $ has no bomb. It is forbidden to pick a bomb if the robot already has a bomb in its container.
3. Operation has format "3". To perform the operation robot have to take a bomb out of the container and destroy it. You are allowed to perform this operation only if the robot is at point $ (0,0) $ . It is forbidden to perform the operation if the container has no bomb.

Help the robot and find the shortest possible sequence of operations he can perform to destroy all bombs on the coordinate plane.

## 样例 #1

### 输入

```
2
1 1
-1 -1
```

### 输出

```
12
1 1 R
1 1 U
2
1 1 L
1 1 D
3
1 1 L
1 1 D
2
1 1 R
1 1 U
3
```

## 样例 #2

### 输入

```
3
5 0
0 5
1 0
```

### 输出

```
12
1 1 R
2
1 1 L
3
1 5 R
2
1 5 L
3
1 5 U
2
1 5 D
3
```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF350C)

### 思路

先说如何求 $k$ 的值。机器人必须捡起一个炸弹后必须要返回 $(0,0)$ 点销毁炸弹，再去下一个点找炸弹。设第 $i$ 个点的坐标为 $(X_i,Y_i)$，若 $X_i\ne0$，$k\gets k+2$，这是一去一回的总和，否则 $k$ 不变；同理，若 $Y_i\ne0$，$k\gets k+2$。最后，还需要再操作一次 $k\gets k+2$，这是捡起和销毁炸弹的操作。

再说如何模拟机器人运动路线。由于机器人在路上不能碰到炸弹，我们可以用坐标 $(X_i,Y_i)$ 距离 $(0,0)$ 点的距离排序，即 $\lvert X_i\rvert+\lvert Y_i\rvert$。这样可以保证机器人路上不会碰到炸弹，因为假设机器人在一次查找的路上碰到了炸弹，那么这个炸弹距离 $(0,0)$ 点的距离一定更短，已经被销毁了。这样，我们可以依次移动两个坐标，到达目标点捡起炸弹，在以相反的方向回到 $(0,0)$ 点销毁炸弹。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
struct node{
	int x,y;
	friend bool operator<(const node cmp_x,const node cmp_y){
		int dis1=(int)abs(cmp_x.x)+(int)abs(cmp_x.y);
		int dis2=(int)abs(cmp_y.x)+(int)abs(cmp_y.y);
		return dis1<dis2;
	}
}a[N];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)
		a[i]={read(),read()};
	sort(a+1,a+n+1);
	int sum=0;
	for(int i=1;i<=n;++i)
		sum+=(bool)a[i].x*2+(bool)a[i].y*2+2;
	printf("%d\n",sum);
	for(int i=1;i<=n;++i){
		if(a[i].x<0)
			printf("1 %d L\n",-a[i].x);
		else if(a[i].x>0)
			printf("1 %d R\n",a[i].x);
		if(a[i].y<0)
			printf("1 %d D\n",-a[i].y);
		else if(a[i].y>0)
			printf("1 %d U\n",a[i].y);
		printf("2\n");
		if(a[i].x<0)
			printf("1 %d R\n",-a[i].x);
		else if(a[i].x>0)
			printf("1 %d L\n",a[i].x);
		if(a[i].y<0)
			printf("1 %d U\n",-a[i].y);
		else if(a[i].y>0)
			printf("1 %d D\n",a[i].y);
		printf("3\n");
	}
	return 0;
}
```

---

## 作者：jwsdy (赞：5)

# 题解：CF350C Bombs

~~其实是一道挺水的模拟题。~~

但是坑还是不少的。。。

## 题目分析

一个机器人位于 $(0,0)$ 号点，我们会给定几个炸弹的位置，机器人会用几个操作来将所有的炸弹炸掉。

**注意：**

1. 炸弹的位置下标可能出现负数。

2. 炸弹必须带回 $(0,0)$ 点才可以炸掉。

3. 机器人只能走直线。

我们先来分析需要的**总步数**：

首先这个机器人**拿取**和**摧毁**炸弹就至少需要 $2$ 次操作，如果炸弹与机器人在同一行或者同一列，则只需**来回两次**，而如果行和列互不相同，则需要行和列均来回两次，共四次。（去取炸弹，还需要回来炸炸弹，所以是一个来回），我们可以**根据距离原点由远到近的顺序来炸炸弹**，防止炸弹阻挡道路。

接下来我们分析每一个操作：

**操作一**

我们需要返回机器人移动的步数和方向。步数比较简单，就是炸弹的横坐标或者纵坐标（一次只能走一行或一列），方向的话我们分情况：

- 如果是横着走，由大数到小数是向左走，即 ```L``` 反之即往右走 ```R```。

- 如果是竖着走，由大数到小数是往下走，即 ```D``` 反之即往上走 ```U```。

**注意下标可能是负数，走的步数需要加绝对值。**

**操作二**

在操作一到达炸弹位置后实现拿取炸弹操作。

**操作三**

拿取炸弹后，再用操作一回到原点实现摧毁炸弹操作。

注意用操作一返回时，应**原路返回**，即如果来时先行后列，回去时应先列后行。

已经全部分析完了，现在奉上代码：

### code

```
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
template<typename T> void read(T&x){
	int s=1;
	x=0;
	char c;
	do{
		c=getchar();
		if(c=='-') s=-1;
	}while(!isdigit(c));
	do{
		x=x*10+c-'0';
		c=getchar();
	}while(isdigit(c));
	x*=s;
}
const int N=2e6+10;
int n;
struct re{
	int x,y;
}a[N];
int ans;
bool cmp(re a,re b){
	return abs(a.x)+abs(a.y)<abs(b.x)+abs(b.y);
}
signed main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i].x);
		read(a[i].y);
		if(a[i].x) ans+=2;
		if(a[i].y) ans+=2;
		ans+=2;
	}
	cout<<ans<<endl;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].x){
			cout<<1<<" "<<abs(a[i].x)<<" ";
			if(a[i].x<0) cout<<"L";
			else cout<<"R";
			cout<<endl;
		}
		if(a[i].y){
			cout<<1<<" "<<abs(a[i].y)<<" ";
			if(a[i].y<0) cout<<"D";
			else cout<<"U";
			cout<<endl;
		}
		cout<<2<<endl;
		if(a[i].y){
			cout<<1<<" "<<abs(a[i].y)<<" ";
			if(a[i].y<0) cout<<"U";
			else cout<<"D";
			cout<<endl;
		}
		if(a[i].x){
			cout<<1<<" "<<abs(a[i].x)<<" ";
			if(a[i].x<0) cout<<"R";
			else cout<<"L";
			cout<<endl;
		}
		cout<<3<<endl;
	}
	return 0;
} 
```
**完结撒花**！

---

## 作者：zhouchuer (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF350C)
### 思路
题面翻译没讲清楚，建议大家看看[这里](https://www.luogu.com.cn/article/6p4m6g2f)。

题目告诉我们机器人可以进行三种操作，第一种是移动，先输出 $1$，后面紧跟移动步数和移动方向，注意 `U` 代表上，`D` 代表下，`L` 代表左，`R` 代表右；第二种是在点上拾取炸弹，输出 $2$；最后就是将炸弹带回原点销毁，输出 $3$。

设机器人的横坐标为 $x_i$，纵坐标为 $y_i$，那么如果 $x_i=0$ 或 $y_i=0$，只需进行 $4$ 次操作：先移动到 $(x_i,y_i)$，拾取炸弹，移动回 $(0,0)$，销毁炸弹，否则就移动两次，拾取一次，移动两次回到原点，最后摧毁炸弹。

还有，我们要将坐标按绝对值排序，离机器人近的炸弹要先处理，因为机器人移动路线上是不能有炸弹的，因为我们要确保机器人走的步数是最少的，近处的炸弹会使机器人不能走最短路径。我们还要知道坐标可能是负数，所以要把 $x_i$ 的绝对值和 $y_i$ 的绝对值的和升序排列，按照顺序处理炸弹。这里我推荐结构体排序。

最后就是判断并输出了，这个部分代码比较长，主要是关于坐标正负的判断，负的坐标输出移动步数要记得转化为相反数，接下来就是按相反路径移动回原点并销毁炸弹，和捡炸弹的代码差不多。

为了防止大家抄代码，代码就不贴了，但是留下自己的[通过记录](https://cdn.luogu.com.cn/upload/image_hosting/x179wmz5.png)。

---

## 作者：andyli (赞：3)

将炸弹坐标按到原点的曼哈顿距离排序后依次处理。对于每个炸弹按照相应方向走即可。  

```cpp
int main() {
    dR(int, n);
    dRV(pi, a, n);
    std::sort(all(a), [&](auto&& x, auto&& y) {
        return std::abs(x.first) + std::abs(x.second) < std::abs(y.first) + std::abs(y.second);
    });
    auto f = [&](char t, int v) {
        return "1 " + std::to_string(v) + ' ' + t;
    };
    Vec<std::string> ans;
    for (auto&& [x, y] : a) {
        // 前往 (x, y)
        if (x < 0)
            ans.push_back(f('L', std::abs(x)));
        if (x > 0)
            ans.push_back(f('R', std::abs(x)));
        if (y < 0)
            ans.push_back(f('D', std::abs(y)));
        if (y > 0)
            ans.push_back(f('U', std::abs(y)));
        ans.push_back("2");
        
        // 返回 (0, 0)
        if (y < 0)
            ans.push_back(f('U', std::abs(y)));
        if (y > 0)
            ans.push_back(f('D', std::abs(y)));
        if (x < 0)
            ans.push_back(f('R', std::abs(x)));
        if (x > 0)
            ans.push_back(f('L', std::abs(x)));
        ans.push_back("3");
    }
    writeln(len(ans));
    io.displayArray(ans, '\n');
    return 0;
}
```

---

## 作者：OIerWu_829 (赞：2)

应该算是一道大模拟。我们可以比较每个炸弹距离原点的距离，按照从小到大的顺序摧毁炸弹。

然后算最小步数，首先拿起炸弹再摧毁需要 $2$ 步。如果这个炸弹的位置跟原点平行，那么走到炸弹的位置再走回来，还需要 $2$ 步。如果不平行，那么走到那里再走回来需要拐两次弯，还需要 $4$ 步，累加即可。

最后输出每一步的情况即可。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

struct node
{
    int x, y;
} p[N];

bool cmp(node a, node b)
{
    return (abs(a.x) + abs(a.y) < abs(b.x) + abs(b.y));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + n, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += 2;
        if (p[i].x != 0) ans += 2;
        if (p[i].y != 0) ans += 2;
    }
    cout << ans << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (p[i].x != 0) cout << "1 " << abs(p[i].x) << (p[i].x > 0 ? " R\n" : " L\n");
        if (p[i].y != 0) cout << "1 " << abs(p[i].y) << (p[i].y > 0 ? " U\n" : " D\n");
        cout << "2\n";
        if (p[i].x != 0) cout << "1 " << abs(p[i].x) << (p[i].x > 0 ? " L\n" : " R\n");
        if (p[i].y != 0) cout << "1 " << abs(p[i].y) << (p[i].y > 0 ? " D\n" : " U\n");
        cout << "3\n";
    }
    return 0;
}
```

---

## 作者：lrx___ (赞：2)

题目翻译没说清楚，完整的翻译如下。

**题意简述**

一个机器人在坐标为 $(0,0)$ 的位置。它要去摧毁 $N$ 个炸弹。共有 $3$ 中操作方式：

1. 格式为 $1,k,dir$。其中 $dir$ 表示方向，`U`，`D`，`L`，`R` 分别代表上，下，左，右。$k$ 表示移动距离。如果中途有炸弹，则不能进行此操作。

2. 格式为 $2$。表示拾取炸弹。如果机器人所在的位置没有炸弹或它还有拾取的炸弹没有摧毁，则不能拾取炸弹。

3. 格式为 $3$。表示摧毁炸弹。此操作只能在 $(0,0)$ 进行。如果没有拾取炸弹，则不能进行此操作。

求出它摧毁所有炸弹的最少操作步数和操作方式。

**输入格式**

第一行有一个整数 $N$。

接下来 $N$ 行，每行有两个整数 $X_i,Y_i$，表示第 $i$ 个炸弹的坐标。

**输出格式**

第一行有一个整数 $K$，表示最少操作步数。

接下来 $K$ 行为操作方式，如题意。

**思路**

距离近的炸弹可能会让机器人绕路到距离远的炸弹，所以要先处理距离近的炸弹。

可以定义一个结构体，存储没个炸弹的坐标位置，然后按它与原点的距离排序。

每个炸弹有两种情况：

1. 它有一个坐标的值为 $0$。此时只需要进行一次移动，一次拾取，一次移动，一次摧毁，共计 $4$ 次。

2. 它的两个坐标的值都不为 $0$。此时需要两次移动，一次拾取，两次移动，一次摧毁，攻击 $6$ 次。

于是就可以计算出 $k$ 的值了。

**代码**

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

using std::sort;

const int N=1e5+5;
struct node{
	int x,y;
}a[N];
bool cmp(node x,node y){
	return abs(x.x)+abs(x.y)<abs(y.x)+abs(y.y);
}
//自定义排序方式为距离原点的距离
int main(){
	int n,i,k=0;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	sort(a,a+n,cmp);
	for(i=0;i<n;i++){
		k+=(a[i].x!=0)*2+(a[i].y!=0)*2+2;
        //如果一个坐标不为0，就需要多进行两次移动操作。拾取和销毁一共有两次操作。
	}
	printf("%d\n",k);
	for(i=0;i<n;i++){
		if(a[i].x>0){
			printf("1 %d R\n",a[i].x);
		}else if(a[i].x<0){
			printf("1 %d L\n",-a[i].x);
		}
		if(a[i].y>0){
			printf("1 %d U\n",a[i].y);
		}else if(a[i].y<0){
			printf("1 %d D\n",-a[i].y);
		}
        // 移动到炸弹的位置
		puts("2");
        //拾取
		if(a[i].x>0){
			printf("1 %d L\n",a[i].x);
		}else if(a[i].x<0){
			printf("1 %d R\n",-a[i].x);
		}
		if(a[i].y>0){
			printf("1 %d D\n",a[i].y);
		}else if(a[i].y<0){
			printf("1 %d U\n",-a[i].y);
		}
        //移动回原点
		puts("3");
        //摧毁操作
	}
	return 0;
}
```

---

## 作者：LiJinLin_AFO (赞：1)

# CF350C 题解

我写的足够~~屎山~~长



------------
## 正文开始

拿到题目，观察一下输出的样例，我们会发现，机器人不会按照输入的顺序来寻找炸弹。所以，我们先排序。怎么排呢？很简单，用结构体存储坐标，排序函数就是比较两个坐标 $\displaystyle (x_1,y_1)$，$(x_2 , y_2)$ 坐标值的绝对值的大小，即公式为 $\displaystyle |x_1| + | y_1 | < | x_2 | + | y_2 |$。例：
```cpp
#include<cmath>//abs()函数所在头文件
struct r{
	int x,y;
}a[100005];//坐标结构体
bool cmp(r w,r e){
	return abs(w.x)+abs(w.y)<abs(e.x)+abs(e.y);
}//排序函数
```


------------
排完序，就可以分类枚举了。一共分为八种情况（见图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/x6xsesb9.png?x-oss-process=image/resize,m_lfit,h_510,w_500)

（注：情况 $\displaystyle 1 \sim 4$ 不包含坐标轴部分）

（补充：$\displaystyle 2$ 代表题目所述进行的操作 $\displaystyle 2$，$\displaystyle 3$ 代表题目所述进行的操作 $\displaystyle 3$，$\displaystyle U D L R$ 表示机器人的上下左右四个方向）

1. 第一象限：$\displaystyle R \Rightarrow U \Rightarrow 2 \Rightarrow L \Rightarrow D \Rightarrow 3$

2. 第四象限：$\displaystyle R \Rightarrow D \Rightarrow 2 \Rightarrow L \Rightarrow U \Rightarrow 3$

3. 第二象限：$\displaystyle L \Rightarrow U \Rightarrow 2 \Rightarrow R \Rightarrow D \Rightarrow 3$

4. 第三象限：$\displaystyle L \Rightarrow D \Rightarrow 2 \Rightarrow R \Rightarrow U \Rightarrow 3$

5. $x$ 轴正半轴：$\displaystyle R \Rightarrow 2 \Rightarrow L \Rightarrow 3$

6. $x$ 轴负半轴：$\displaystyle L \Rightarrow 2 \Rightarrow R \Rightarrow 3$

7. $y$ 轴正半轴：$\displaystyle U \Rightarrow 2 \Rightarrow D \Rightarrow 3$

8. $y$ 轴负半轴：$\displaystyle D \Rightarrow 2 \Rightarrow U \Rightarrow 3$

介绍完毕，上代码：

```cpp
#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;
int n,ans,out;
struct r{
	int x,y;
}a[100005];
struct answer{
	int dir;
	int first=0;
	int first_num;
	int second=0;
	int second_num;
}kkk[1000005];//输出部分
bool cmp(r w,r e);
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].x>0&&a[i].y>0){
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=a[i].x;
			kkk[ans].second=1;
			kkk[ans].second_num=a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=a[i].x;
			kkk[ans].second=3;
			kkk[ans].second_num=a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=3;
			++out;//情况1
		}
		else if(a[i].x>0&&a[i].y<0){
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=a[i].x;
			kkk[ans].second=3;
			kkk[ans].second_num=-a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=a[i].x;
			kkk[ans].second=1;
			kkk[ans].second_num=-a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况2
		else if(a[i].x<0&&a[i].y>0){
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=-a[i].x;
			kkk[ans].second=1;
			kkk[ans].second_num=a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=-a[i].x;
			kkk[ans].second=3;
			kkk[ans].second_num=a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况3
		else if(a[i].x<0&&a[i].y<0){
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=-a[i].x;
			kkk[ans].second=3;
			kkk[ans].second_num=-a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=-a[i].x;
			kkk[ans].second=1;
			kkk[ans].second_num=-a[i].y;
			out+=2;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况4
		else if(a[i].x>0&&!a[i].y){
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=a[i].x;
			++out;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=a[i].x;
			++out;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况5
		else if(a[i].x<0&&!a[i].y){
			kkk[++ans].dir=1;
			kkk[ans].first=4;
			kkk[ans].first_num=-a[i].x;
			++out;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=2;
			kkk[ans].first_num=-a[i].x;
			++out;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况6
		else if(!a[i].x&&a[i].y>0){
			kkk[++ans].dir=1;
			kkk[ans].first=1;
			kkk[ans].first_num=a[i].y;
			++out;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=3;
			kkk[ans].first_num=a[i].y;
			++out;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况7
		else if(!a[i].x&&a[i].y<0){
			kkk[++ans].dir=1;
			kkk[ans].first=3;
			kkk[ans].first_num=-a[i].y;
			++out;
			//-------------------
			kkk[++ans].dir=2;
			++out;
			//-------------------
			kkk[++ans].dir=1;
			kkk[ans].first=1;
			kkk[ans].first_num=-a[i].y;
			++out;
			//-------------------
			kkk[++ans].dir=3;
			++out;
		}//情况8
	}
	printf("%d\n",out);//总步数
	for(int i=1;i<=ans;i++){
		printf("%d ",kkk[i].dir);
		if(kkk[i].dir!=1){
			puts("");
			continue;
		}//拾取或摧毁
		printf("%d ",kkk[i].first_num);
		if(kkk[i].first==1) puts("U");
		if(kkk[i].first==2) puts("R");
		if(kkk[i].first==3) puts("D");
		if(kkk[i].first==4) puts("L");
		if(!kkk[i].second) continue;
		printf("%d ",kkk[i].dir);
		printf("%d ",kkk[i].second_num);
		if(kkk[i].second==1) puts("U");
		if(kkk[i].second==2) puts("R");
		if(kkk[i].second==3) puts("D");
		if(kkk[i].second==4) puts("L");
     		 //输出
	}
	return 0;
}
bool cmp(r w,r e){
	return abs(w.x)+abs(w.y)<abs(e.x)+abs(e.y);
}//排序
```
注：请勿抄袭！

---

## 作者：fyn1234 (赞：0)

### 题意

一道模拟题。题目翻译有点模糊，在这解释一下样例中的输出：第一行是最小操作数，即 $k$。剩下的类似 `1 1 R` 的表示移动，其中第一个 `1` 表示移动一步，第二个 `1` 表示移动一次，`R` 表示向右（类似的还有 `L` 表示向左，`U` 表示向上，`D` 表示向下）。单独一行的 `2` 表示拾取炸弹，单独一行的 `3` 表示销毁炸弹（必须在原点才可以）。

### 思路

首先求 $k$ 的值。设第 $i$ 个点的坐标为 $(X_i,Y_i)$，不难发现，当 $X_i$ 或者 $Y_i$ 等于 $0$ 时，那么就只需要执行四步：一次移动，一次拾取，一次移动，一次销毁。否则就要执行六步：两次移动，一次拾取，两次移动，一次销毁。于是就可以求出 $k$ 的值了。

接着就是具体的移动了，由于机器人在移动时不能碰到炸弹，所以要优先处理离原点近的炸弹。可以用结构体排序来处理。最后按照题目要求输出就是了。

### AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
struct node{
    int x,y;
}a[N];
bool cmp(node x,node y){
    return abs(x.x)+abs(x.y)<abs(y.x)+abs(y.y);
}
int main() {
    // just do it
    int n;
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }
    sort(a+1,a+1+n,cmp);
    int k = 0;
    for(int i = 1;i<=n;i++){
        k+=(a[i].x==0?0:2)+(a[i].y==0?0:2)+2;//计算k
    }
    cout<<k<<"\n";
    for(int i = 1;i<=n;i++){//处理移动并输出
        if(a[i].x>0){
            cout<<"1 "<<a[i].x<<" R\n";
        }
        else if(a[i].x<0){
            cout<<"1 "<<-a[i].x<<" L\n";
        }
        if(a[i].y>0){
            cout<<"1 "<<a[i].y<<" U\n";
        }
        else if(a[i].y<0){
            cout<<"1 "<<-a[i].y<<" D\n";
        }
        cout<<"2\n";
        if(a[i].x>0){
            cout<<"1 "<<a[i].x<<" L\n";
        }
        else if(a[i].x<0){
            cout<<"1 "<<-a[i].x<<" R\n";
        }
        if(a[i].y>0){
            cout<<"1 "<<a[i].y<<" D\n";
        }
        else if(a[i].y<0){
            cout<<"1 "<<-a[i].y<<" U\n";
        }
        cout<<"3\n";
    }
    return 0;
}
```

---

## 作者：xiaoxiongbinggan (赞：0)

# CF350C Bombs 题解

### 题目大意：

机器人初始时在 $(0,0)$ 位置处，平面内有 $n$ 个炸弹，让机器人拆除这 $n$ 个炸弹，询问最少的操作次数与实现方案，注意：当机器人此时所处的位置上与目的地之间有一个炸弹，则此次移动不能实现。

输入的第一行有一个 $n$ 代表炸弹的个数，以下 $n$ 行每行有两个整数，代表每个炸弹所处在平面中的位置。

输出第一行为最少的操作次数。以下为操作步骤，步骤分三种。

1. 先输出 $1$，表示此次操作为移动操作，而后输出移动的距离与方向，方向为：```U```代表上，```D```代表下, ```L```代表左, ```R```代表右。
2. 输出 $2$ 代表机器人将此时所处位置的炸弹拿起,只有当机器人此时所处的位置上有炸弹时才能够进行此操作。
3. 输出 $3$ 代表此时机器人将手中的炸弹销毁，仅当机器人在原点时才能实现此操作。

这是一道简单的模拟题，但有许多需要注意的点。

## 注意：

1. 当机器人行径路径上有其他炸弹时，不可以进行此次移动。
2. 机器人手中有炸弹时不能再次拿取炸弹。
3. 只有在原点才能销毁炸弹，就是说每一次拿取炸弹后都需要回到原点。
4. 坐标存在负数。

第二，三点都好说，但第一点如何解决呢？

听起来很复杂，其实很简单，只要我们将这些炸弹离原点的距离按照从小到大的顺序排好序，就可以了，为什么呢？

当一个点距离原点最近时，机器人行径道路上一定没有其他炸弹，若存在其他炸弹，那么距离原点最近的点就不是这个点了，我们假设离原点最近的点坐标为 $(x,y)$ 且 $x$ 与 $y$ 都为正数,当机器人从 $(0,0)$ 走到 $(x,y)$ 的道路之间存在有其他炸弹，则另一个炸弹的横坐标或纵坐标一定比 $(x,y)$ 的横纵坐标要小，那距离原点最近的点就不是 $(x,y)$ 了。

思路有了，代码如何实现呢？

每一个炸弹都需要拿取与销毁 $2$ 步，若此炸弹不在坐标轴上，则需要 $4$ 步，从原点到此点用 $2$ 步，再回到原点也需要 $2$ 步，若在坐标轴上，则只需 $2$ 步，再按照距离原点距离的远近输出横纵坐标**的绝对值**即可，要注意回来时的方向与出发时的方向正好相反。

最后奉上代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
struct qcl{
	int h,l;
}a[10000000];
bool cmp(qcl x,qcl y){
	return abs(x.h)+abs(x.l)<abs(y.h)+abs(y.l);//按照离原点的距离进行排序
}
int ans,n;//ans表示操作次数
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].h>>a[i].l;//炸弹的横纵坐标
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		ans+=2;
		if(a[i].h!=0){
			ans+=2;
		}
		if(a[i].l!=0){
			ans+=2;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(a[i].h>0){
			cout<<1<<" ";
			cout<<a[i].h<<" ";
			cout<<"R"<<endl;
		}else if(a[i].h<0){
			cout<<1<<" ";
			cout<<-a[i].h<<" ";
			cout<<"L"<<endl;
		}
		if(a[i].l>0){
			cout<<1<<" ";
			cout<<a[i].l<<" ";
			cout<<"U"<<endl;
		}else if(a[i].l<0){
			cout<<1<<" ";
			cout<<-a[i].l<<" ";
			cout<<"D"<<endl;
		}
		cout<<2<<endl;
		if(a[i].h>0){
			cout<<1<<" ";
			cout<<a[i].h<<" "; 
			cout<<"L"<<endl;
		}else if(a[i].h<0){
			cout<<1<<" ";
			cout<<-a[i].h<<" ";
			cout<<"R"<<endl;
		}
		if(a[i].l>0){
			cout<<1<<" ";
			cout<<a[i].l<<" ";
			cout<<"D"<<endl;
		}else if(a[i].l<0){
			cout<<1<<" ";
			cout<<-a[i].l<<" ";
			cout<<"U"<<endl;
		}
		cout<<3<<endl;
	}
	return 0;
}

```

---

## 作者：yaaaaaan (赞：0)

### 思路
首先先给每个炸弹它与原点的距离排序。

* 如果它有一个坐标的值为 0。此时只需要 $4$ 次，分别进行一次移动，一次拾取，一次移动，一次摧毁

* 如果它没有一个坐标的值为 0。此时只要多进行两次移动，共 $6$ 次。

然后对于每个炸弹按照相应方向走即可。

各位大佬的代码都写得很好了，就不放代码了。

---

## 作者：xutongwei (赞：0)


水题ing……

本题思路：

1.首先把所有炸弹排序，保证机器走的时候不会~~吃~~压到炸弹。
2.算出来一共走的路程，并按最短指令依次输出。

具体代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
struct node{
	int x, y;
};
node a[100010];

bool pai(node x1, node y1){
	return abs(x1.x) + abs(x1.y) < abs(y1.x) + abs(y1.y);//鬼畜的排序规则
}

int main( ){
	int n, sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i].x >> a[i].y;
		//算路径过程↓
		if(a[i].x != 0){
			sum += 2;
		}
		if(a[i].y != 0){
			sum += 2;
		}
		sum += 2;
	}
	sort(a + 1, a + n + 1, pai);
	cout << sum << endl;
	for(int i = 1; i <= n; i++){
		//指令过程↓
		if(a[i].x != 0){
			if(a[i].x < 0){
				printf("1 %d L\n", 0 - a[i].x);
			}else{
				printf("1 %d R\n", a[i].x - 0);
			}
		}
		if(a[i].y != 0){
			if(a[i].y < 0){
				printf("1 %d D\n", 0 - a[i].y);
			}else{
				printf("1 %d U\n", a[i].y - 0);
			}
		}
		cout << "2" << endl;
		if(a[i].y != 0){
			if(a[i].y < 0){
				printf("1 %d U\n", 0 - a[i].y);
			}else{
				printf("1 %d D\n", a[i].y - 0);
			}
		}
		if(a[i].x != 0){
			if(a[i].x < 0){
				printf("1 %d R\n", 0 - a[i].x);
			}else{
				printf("1 %d L\n", a[i].x - 0);
			}
		}
		cout << "3";
		if(i != n){
			cout << endl;//不知道有没有用，写了再说。
		}
	}
	return 0;//完美的结束
}
```


---

