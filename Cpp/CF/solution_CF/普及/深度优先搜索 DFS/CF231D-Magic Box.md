# Magic Box

## 题目描述

One day Vasya was going home when he saw a box lying on the road. The box can be represented as a rectangular parallelepiped. Vasya needed no time to realize that the box is special, as all its edges are parallel to the coordinate axes, one of its vertices is at point $ (0,0,0) $ , and the opposite one is at point $ (x_{1},y_{1},z_{1}) $ . The six faces of the box contain some numbers $ a_{1},a_{2},...,a_{6} $ , exactly one number right in the center of each face.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)The numbers are located on the box like that:

- number $ a_{1} $ is written on the face that lies on the ZOX plane;
- $ a_{2} $ is written on the face, parallel to the plane from the previous point;
- $ a_{3} $ is written on the face that lies on the XOY plane;
- $ a_{4} $ is written on the face, parallel to the plane from the previous point;
- $ a_{5} $ is written on the face that lies on the YOZ plane;
- $ a_{6} $ is written on the face, parallel to the plane from the previous point.

At the moment Vasya is looking at the box from point $ (x,y,z) $ . Find the sum of numbers that Vasya sees. Note that all faces of the box are not transparent and Vasya can't see the numbers through the box. The picture contains transparent faces just to make it easier to perceive. You can consider that if Vasya is looking from point, lying on the plane of some face, than he can not see the number that is written on this face. It is enough to see the center of a face to see the corresponding number for Vasya. Also note that Vasya always reads correctly the $ a_{i} $ numbers that he sees, independently of their rotation, angle and other factors (that is, for example, if Vasya sees some $ a_{i}=6 $ , then he can't mistake this number for $ 9 $ and so on).

## 说明/提示

The first sample corresponds to perspective, depicted on the picture. Vasya sees numbers $ a_{2} $ (on the top face that is the darkest), $ a_{6} $ (on the right face that is the lightest) and $ a_{4} $ (on the left visible face).

In the second sample Vasya can only see number $ a_{4} $ .

## 样例 #1

### 输入

```
2 2 2
1 1 1
1 2 3 4 5 6
```

### 输出

```
12
```

## 样例 #2

### 输入

```
0 0 10
3 2 3
1 2 3 4 5 6
```

### 输出

```
4
```

# 题解

## 作者：封禁用户 (赞：2)

## CF231D Magic Box 题解
### 解题思路
这道题的思路很简单，就是分别去判断你能不能看到某一个面。

![1](https://cdn.luogu.com.cn/upload/image_hosting/qfslp6w0.png)

借用一下 [$3$ 楼](https://www.luogu.com.cn/article/go0tvds1)的图片。

我们可以按照上面这幅图标注的顺序，一个一个判断。

#### 下面，我列出这六个面的判断条件，其中 $(x,y,z)$ 为左上角的坐标，$(s_x,s_y,s_z)$ 为你的坐标。
1. 如果 $s_y < 0$，则代表第 $1$ 面的数字可以看到。
1. 如果 $s_y > y$，则代表第 $2$ 面的数字可以看到。
1. 如果 $s_z < 0$，则代表第 $3$ 面的数字可以看到。
1. 如果 $s_z > z$，则代表第 $4$ 面的数字可以看到。
1. 如果 $s_x < 0$，则代表第 $5$ 面的数字可以看到。
1. 如果 $s_x > z$，则代表第 $6$ 面的数字可以看到。

按照这种思路，列出判断条件，很轻松就可以 $\text{AC}$ 了。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	int x , y , z;
}s , t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7;
int ans , a , b , c , d , e , f;
int main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin >> s.x >> s.y >> s.z >> t7.x >> t7.y >> t7.z >> a >> b >> c >> d >> e >> f;
	t0.x = t0.y = t0.z = t1.x = t1.y = t2.y = t2.z = t3.y = t4.x = t4.z = t5.x = t6.z = 0;
	t2.x = t3.x = t6.x = t7.x;
	t4.y = t5.y = t6.y = t7.y;
	t1.z = t3.z = t5.z = t7.z;
	if(s.y < t0.y)
	{
		ans += a;
	}
	if(s.y > t4.y)
	{
		ans += b;
	}
	if(s.z < t2.z)
	{
		ans += c;
	}
	if(s.z > t7.z)
	{
		ans += d;
	}
	if(s.x < t1.x)
	{
		ans += e;
	}
	if(s.x > t6.x)
	{
		ans += f;
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

### 题意

一个立方体，它的一个顶点在原点，它的每个面上有一个数字，给出它的边长和你所在的位置的坐标，问你能看到的数字和是多少？

### 分析

~~这道题虽然是道黄题，但我觉得只有红题难度。~~

我们先要搞清楚顺序。

然后呢，我们需要亿点点立体几何思维。

如果可以看到 ZOX 那么你的 y 轴要小于 $0$。

如果可以看到 ZOX 的背面，那么你的 y 轴要大于 $y_1$。

同理，如果可以看到 XOY 那么你的 z 轴要小于 $0$。

如果可以看到 XOY 的背面，那么你的 z 轴要大于 $z_1$。

如果可以看到 YOZ 那么你的 x 轴要小于 $0$。

如果可以看到 YOZ 的背面，那么你的 x 轴要大于 $x_1$。

### 代码

代码其实放不放无所谓，那还是放一下吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[8];
int main(){
	int x,y,z,x1,y1,z1,sum=0;
	cin>>x>>y>>z>>x1>>y1>>z1;
	for(int i=1;i<=6;i++) cin>>a[i];
	if(y<0) sum+=a[1];
	if(y>y1) sum+=a[2];
	if(z<0) sum+=a[3];
	if(z>z1) sum+=a[4];
	if(x<0) sum+=a[5];
	if(x>x1) sum+=a[6];
	cout<<sum;
	return 0;
}
```
完结撒花！

---

## 作者：naroto2022 (赞：1)

# CF231D题解

### 题意

给你一个长方体的长，宽，高，再给你一个观测坐标和每一面的上面的数字，问在这个观测点看到的数字之和是多少？

### 输入顺序

1. 观测的坐标（$x$，$y$，$z$）。
2. 长方体的长，宽，高。（$x$ 轴边长，$y$ 轴边长，$z$ 轴边长）
3. 长方体每个面上的数（ZOX，ZOX 的对面，XOY，XOY 的对面，YOZ，YOZ 的对面）

(上述中的坐标轴参考下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/fqnum5ya.png)

### 思路

本题思路~~很简单~~。其实就是一面一面的判断是否可以看到这面的数字，看得到 $ans$（答案）就加一。

那接下来就要想该如何判断是否可以看到某一面。见下：

1. 要是 $x$ 轴坐标小于 $0$，则看到 YOZ 面上的数字。
2. 要是 $x$ 轴坐标大于 $x$ 轴的边长，则看到 YOZ 的对面上的数字。

其余的以此类推，那这题就解出来了！

### 总结
1. 搞清楚输入顺序。
2. 搞清楚坐标轴。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int cnt[10],ans;//ans为答案（你看到的数字之和），cnt为每一面上的数。 
int x,y,z;//你所处的坐标。
int s1,s2,s3;//长，宽，高。 
int main(){
	scanf("%d %d %d %d %d %d",&x,&y,&z,&s1,&s2,&s3);
	for(int i=1; i<=6; i++) scanf("%d",&cnt[i]); 
	if(y<0) ans+=cnt[1];//看到了ZOX。
	if(y>s2) ans+=cnt[2];//看到了ZOX的对面。
	if(z<0) ans+=cnt[3];//看到了XOY。
	if(z>s3) ans+=cnt[4];//看到了XOY的对面。 
	if(x<0) ans+=cnt[5];//看到了YOZ。 
	if(x>s1) ans+=cnt[6];//看到了YOZ的对面。 
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Vibration886 (赞：1)

# [CF231D Magic Box](https://www.luogu.com.cn/problem/CF231D)

首先，输入的顺序要理清楚：

- 第一行：Vasya 所处的坐标（$x$，$y$，$z$）

- 第二行：立方体的边长（$x$ 轴边长，$y$ 轴边长，$z$ 轴边长）

- 第三行：立方体每个面上的数（ZOX，ZOX 对面，XOY，XOY 对面，YOZ，YOZ 对面）

接下来，判断能看到一个面的条件。举个例子：

如果想看到 ZOX 面，那么 Vasya 所处的 $y$ 轴坐标必须小于 $0$；如果想看到 ZOX 的对面，那么 Vasya 所处的 $y$ 轴坐标必须大于 $y$ 轴的边长。其余的面同理。

注意，如果正好贴着某一个面是看不到这个面的！

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[7],sum;
int main()
{
	int x,y,z;//坐标 
	int V1,V2,V3;//边长 
	cin>>x>>y>>z;
	cin>>V1>>V2>>V3;
	for(int i=1;i<=6;i++)
	{
		cin>>s[i];//每一面上的数 
	}
	if(x<0) sum+=s[5];
	if(x>V1) sum+=s[6];
	if(y<0) sum+=s[1];
	if(y>V2) sum+=s[2];
	if(z<0) sum+=s[3];
	if(z>V3) sum+=s[4];
	cout<<sum;
	return 0;
}
```

恭喜，你又水了一道黄题！

---

## 作者：我送送送送 (赞：1)

从题目中可以知道，此题要输入正方体的边长，观测正方体时的观测坐标和正方体 $6$ 个面的数字，求出在观测坐标中能看到的数字之和。

此题可以用```if```语句分别判断 $6$ 个数字所在面是否可以被观测到，如果可以就将答案 + $1$ ，否则就不加。

下面奉上 AC 代码:

```
#include<iostream>
using namespace std;
int main(){
    int x, y, z, nx, ny, nz;
    cin>>x>>y>>z>>nx>>ny>>nz;
    int a[6];
    for(int i=0;i<6;i++)cin>>a[i];
    int ans=0;
    if(x<0)ans+=a[4];
    if(x>nx)ans+=a[5];
    if(y<0)ans+=a[0];
    if(y>ny)ans+=a[1];
    if(z<0)ans+=a[2];
    if(z>nz)ans+=a[3];
    cout<<ans;
    return 0;
}
```

完美结束。

---

## 作者：Lan_yan (赞：0)

没人写这道题？我来占个坑。

## 题目

有一个长方体，给出长宽高和一个人的坐标和六个面的数字。

一个人不开透视地看这个长方体，能看到多少的数字和。

## 思考

首先，根据题目所提供的图片，我们不难推断出：

如果你的 $x$ 坐标小于原点，那么恭喜你可以看到 ZOY 面。

如果你的 $x$ 坐标大于长方体的长 $x$，那么你可以看到 ZOY 的对立面。

如果你的 $y$ 坐标小于原点，那么你可以看到 ZOX 面。

如果你的 $y$ 坐标大于长方体的宽 $y$，那么你可以看到 ZOX 的对立面。

如果你的 $z$ 坐标小于原点，那么你可以看到 XOY 面。

如果你的 $z$ 坐标大于长方体的高 $z$，那么你可以看到 XOY 的对立面。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,z,a,b,c,p[10],ans=0;
int main()
{
	int i;
	scanf("%d%d%d",&x,&y,&z);
	scanf("%d%d%d",&a,&b,&c);
	for(i=1;i<=6;i++)scanf("%d",&p[i]);
	if(x<0)ans+=p[5];
	if(x>a)ans+=p[6];
	if(y<0)ans+=p[1];
	if(y>b)ans+=p[2];
	if(z<0)ans+=p[3];
	if(z>c)ans+=p[4];
	printf("%d",ans);
	return 0;
}
```
## 总结

这题难度大概在中位橙到下位黄之间，根据 CF 的特性，放黄也是可以接受的。

---

## 作者：lixuanxi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF231D)

# 题意理解

给你一个观测坐标，再给你一个长方体的长，宽，高和每一面的上面的数字，问在这个观测点看到的数字之和是多少。

# 题目思路

本题需要一些几何空间想象能力。

设长方体的六面分别为 XOY，YOZ，ZOX，和三面的反面。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)

看此图，要想看到 ZOX，$$y$$ 轴必须小于 $0$。

同理，要想看到 ZOX 的反面，$$y$$ 轴必须大于 $$x1$$。

要想看到 XOY，$$z$$ 轴必须小于 $0$。

要想看到 XOY 的反面，$$z$$ 轴必须大于 $$y1$$。

要想看到 YOZ，$$x$$ 轴必须小于 $0$。

要想看到 YOZ 的反面，$$x$$ 轴必须大于 $$z1$$。

于是……
# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],ans; 
int x,y,z;
int s1,s2,s3;
int main(){
	scanf("%d%d%d%d%d%d",&x,&y,&z,&x1,&y1,&z1);
	for(int i=1;i<=6;i++)scanf("%d",&a[i]); 
	if(y<0)ans+=a[1];
	if(y>y1)ans+=a[2];
	if(z<0)ans+=a[3];
	if(z>z1)ans+=a[4];
	if(x<0)ans+=a[5];
	if(x>x1)ans+=a[6];
    //判断以YZX的顺序，是因为输入顺序
	printf("%d",ans);
	return 0;
}
```

---

## 作者：qw1234321 (赞：0)

一眼盯真，红题一道。

就是模拟每个面是否能够看到，设 Vasya 的坐标为 $(x,y,z)$，Box 的坐标为 $(box_x,box_y,box_z)$，即：

- 若 $x<0$，则能看见 YOZ 面。
- 若 $x>box_x$，则能看见 YOZ 的对面。
- 若 $y<0$，则能看见 ZOX 面。
- 若 $y>box_y$，则能看见 ZOX 的对面。
- 若 $z<0$，则能看见 XOY 面。
- 若 $z>box_z$，则能看见 XOY 的对面。

然后就做完了。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int ans, a[N];
struct Space{
	int x, y, z;
}my, box;

void work(){
	cin >> my.x >> my.y >> my.z >> box.x >> box.y >> box.z;
	for (int i = 1; i <= 6; i++) cin >> a[i];
	if (my.y < 0) ans += a[1];
	if (my.y > box.y) ans += a[2];
	if (my.z < 0) ans += a[3];
	if (my.z > box.z) ans += a[4];
	if (my.x < 0) ans += a[5];
	if (my.x > box.x) ans += a[6];
	cout << ans;
}

signed main(){
	int t = 1;
	//  cin >> t;
	while(t--) work();
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 这道题涉及**分支语句**与**立体几何**：

- 首先，我们分开讨论 $x1,y2,z3$ 坐标。

- 当 $x_1$ 坐标 $<0$ 或 $>x$ 时，我们分别可以观察到平面 `YOZ` 及其平行面。

- 当 $y_1$ 坐标 $<0$ 或 $>y$ 时，我们分别可以观察到平面 `XOZ` 及其平行面。

- 当 $z_1$ 坐标 $<0$ 或 $>z$ 时，我们分别可以观察到平面 `XOY` 及其平行面。

- 综上所述，我们可以将其转化为分支语句分类讨论。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[3],y[3],z[3],a[10],ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(int i=1;i<=2;i++)
	{
		cin>>x[i]>>y[i]>>z[i];
	}
	for(int i=1;i<=6;i++)
	{
		cin>>a[i];
	}
	if(x[1]>x[2])
	{
		ans+=a[6];
	}
	if(y[1]>y[2])
	{
		ans+=a[2];
	}
	if(z[1]>z[2])
	{
		ans+=a[4];
	}
	if(x[1]<0)
	{
		ans+=a[5];
	}
	if(y[1]<0)
	{
		ans+=a[1];
	}
	if(z[1]<0)
	{
		ans+=a[3];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Morax2022 (赞：0)

# CF231D Magic Box 题解
**先读题**

- 输入的第一行为我观测的位置。
- 第二行为正方形的长宽高即 $x, y, z$。
- 第三行顺序是 ZOX 面，ZOX 的对面，XOY 面，XOY 的对面，YOZ 面，YOZ 面的对 (如下图)

![正方体](https://cdn.luogu.com.cn/upload/image_hosting/qfslp6w0.png)

由于正方形有一个顶点在原点，所以当我的坐标小于 $0$ 时就可以看到对应面的数字， 第二种情况则是我的坐标大于对应正方形顶点的坐标，这样也可以看到该面数字。

#  AC Code
```c
#include <bits/stdc++.h>
using namespace std;
int dir[7];
int main()
{
	int x, y, z, bx, by, bz, sum = 0;
	cin >> x >> y >> z >> bx >> by >> bz;
	for (int i = 1; i <= 6; i++) cin >> dir[i];//输入起始点，盒子xyz与每面数字 
	if (x > bx) sum += dir[6]; if (x < 0) sum += dir[5];//右和左
	if (y > by) sum += dir[2]; if (y < 0) sum += dir[1];//上和下 
	if (z > bz) sum += dir[4]; if (z < 0) sum += dir[3];//前和后 
	cout << sum;//输出看到面的数字之和 
}
```
这是本蒟蒻的第二篇题解，希望能给大家带来帮助！

---

## 作者：Amm_awa (赞：0)

在题目中讲到，一个长宽高分别为  $ a $、$ b $ 和 $h $  的立方体每个面有一个数，“我”的坐标分别在  $ x $、$ y $ 和 $ z $，问“我”能看到数的和为多少。

我们只要输入要求的数，再判断是否能看到这个数，能看到的加入答案，最后输出，就能 AC 了

[题目传送门](https://www.luogu.com.cn/problem/CF231D)

代码如下
 
 ```
#include<bits/stdc++.h>
using namespace std;
inline int read()//在本题中不是必须的，但会让你的代码快很多
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int f[10],ans;
int main()
{
    int a,b,h,x,y,z;
    a=read();
    b=read();
    h=read();
    x=read();
    y=read();
    z=read();
    for(int i=1;i<=6;i++)f[i]=read();//输入每个面的数
    //判断
    if(b<0)ans+=f[1];
    if(b>y)ans+=f[2];
    if(h<0)ans+=f[3];
    if(h>z)ans+=f[4];
    if(a<0)ans+=f[5];
    if(a>x)ans+=f[6];
    //输出
    printf("%d",ans);
    return 0;
}
``` 


---

## 作者：_HiKou_ (赞：0)

思路很简单，感觉不至于评黄。

先纠正一下输入输出：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)

- 第一行三个数输入的是你在的坐标。
- 第二行三个数输入的是立方体的边长。分别代表立方体在 $x,y,z$ 轴的边长。
- 第三行六个数的输入顺序：ZOX 面，ZOX 的对面，XOY 面，XOY面的对面，YOZ 面，YOZ 面的对面。

知道这些就很容易解决了。只要逐一判断自己的坐标和这个面的关系即可。

另外，如果在的位置贴着一个面好像是看不到这个面的。请注意。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[14],i,ans;
int main(){
	int a,b,c;//边长
	int x,y,z;//坐标
	scanf("%d%d%d",&x,&y,&z);
	scanf("%d%d%d",&a,&b,&c);
	for(i=1;i<=6;i++)scanf("%d",&s[i]);
	if(y<0)ans+=s[1];
	if(y>b)ans+=s[2];
	if(z<0)ans+=s[3];
	if(z>c)ans+=s[4];
	if(x<0)ans+=s[5];
	if(x>a)ans+=s[6];
	printf("%d",ans);
	return 0;
}
```

---

## 作者：流绪 (赞：0)

模拟！

一个立方体，它的一个顶点在原点，它的每个面上有一个数字，给出它的边长和你所在的位置的坐标，问你能看到的数字和是多少？

我们观察图可以发现每个面想要被看到都要满足一个条件，比如 XOZ 面要想被看到，那么我们必须有 y<0 才行，其他的面同理。因此我们用我们位置的坐标和六个面分别进行判断，可以看到的话就加上。

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
ll a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int x,y,z;
	cin >> x >> y >>z;
	int x1,y1,z1;
	cin >> x1 >> y1 >> z1;
	for(int i=1;i<=6;i++)
		cin >> a[i];
	int sum = 0;
	if(y < 0)
		sum+=a[1];
	if(y > y1)
		sum +=a[2];
	if(z < 0)
		sum+=a[3];
	if(z > z1)
		sum +=a[4];
	if(x < 0)
		sum+=a[5];
	if(x > x1)
		sum +=a[6];//判断能不能被看到
	cout << sum; 
	return 0; 
}  
```


---

## 作者：lzdqwq (赞：0)

### 思路：

设长方体的六面分别为 XOY，YOZ，ZOX，以及这三面的反面。

分情况讨论：

- 看到 ZOX，$y1$  $<$ $0$。

- 看到 ZOX 的反面，$y1$ $>$ $x2$。

- 看到 XOY，$z1$ $<$ $0$。

- 看到 XOY 的反面，$z1$ $>$ $y2$。

- 看到 YOZ，$x1$ $<$ $0$。

- 看到 YOZ 的反面，$x1$ $>$ $z2$。

具体地，可以参照这幅图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF231D/891b16d62b99e19e4dbbcc1ffa7c6345c322e404.png)


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
inline ll read(){
    ll s=0;
    bool f=0;
    char ch=' ';
    while(!isdigit(ch)){
        f|=(ch=='-'); ch=getchar();
    }
    while(isdigit(ch)){
        s=(s<<3)+(s<<1)+(ch^48); ch=getchar();
    }
    return (f)?(-s):(s);
}
inline void write(ll x){
    if(x<0){
        putchar('-'); x=-x;
    }
    if(x<10){
        putchar(x+'0'); return;
    }
    write(x/10);
    putchar((x%10)+'0');
    return;
}
int a,b,c,x,y,z,cnt[14],ans=0;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>x>>y>>z>>a>>b>>c;
	for(int i=1;i<=6;i++) cin>>cnt[i];
	if(y<0) ans+=cnt[1];
	if(y>b) ans+=cnt[2];
	if(z<0) ans+=cnt[3];
	if(z>c) ans+=cnt[4];
	if(x<0) ans+=cnt[5];
	if(x>a) ans+=cnt[6];
	cout<<ans;
	return 0;
}

```

---

