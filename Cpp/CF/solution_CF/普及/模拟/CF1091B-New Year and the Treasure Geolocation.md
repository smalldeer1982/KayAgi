# New Year and the Treasure Geolocation

## 题目描述

Bob is a pirate looking for the greatest treasure the world has ever seen. The treasure is located at the point $ T $ , which coordinates to be found out.

Bob travelled around the world and collected clues of the treasure location at $ n $ obelisks. These clues were in an ancient language, and he has only decrypted them at home. Since he does not know which clue belongs to which obelisk, finding the treasure might pose a challenge. Can you help him?

As everyone knows, the world is a two-dimensional plane. The $ i $ -th obelisk is at integer coordinates $ (x_i, y_i) $ . The $ j $ -th clue consists of $ 2 $ integers $ (a_j, b_j) $ and belongs to the obelisk $ p_j $ , where $ p $ is some (unknown) permutation on $ n $ elements. It means that the treasure is located at $ T=(x_{p_j} + a_j, y_{p_j} + b_j) $ . This point $ T $ is the same for all clues.

In other words, each clue belongs to exactly one of the obelisks, and each obelisk has exactly one clue that belongs to it. A clue represents the vector from the obelisk to the treasure. The clues must be distributed among the obelisks in such a way that they all point to the same position of the treasure.

Your task is to find the coordinates of the treasure. If there are multiple solutions, you may print any of them.

Note that you don't need to find the permutation. Permutations are used only in order to explain the problem.

## 说明/提示

As $ n = 2 $ , we can consider all permutations on two elements.

If $ p = [1, 2] $ , then the obelisk $ (2, 5) $ holds the clue $ (7, -2) $ , which means that the treasure is hidden at $ (9, 3) $ . The second obelisk $ (-6, 4) $ would give the clue $ (-1,-3) $ and the treasure at $ (-7, 1) $ . However, both obelisks must give the same location, hence this is clearly not the correct permutation.

If the hidden permutation is $ [2, 1] $ , then the first clue belongs to the second obelisk and the second clue belongs to the first obelisk. Hence $ (-6, 4) + (7, -2) = (2,5) + (-1,-3) = (1, 2) $ , so $ T = (1,2) $ is the location of the treasure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091B/f03c880711f7b9805001588cb705f046f5d5dbf6.png)In the second sample, the hidden permutation is $ [2, 3, 4, 1] $ .

## 样例 #1

### 输入

```
2
2 5
-6 4
7 -2
-1 -3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
4
2 2
8 2
-7 0
-2 6
1 -14
16 -12
11 -18
7 -14
```

### 输出

```
9 -12
```

# 题解

## 作者：installb (赞：1)

把n个坐标与另外n个坐标以某种排列一一对应 使每一组对应的坐标x,y分别相加得到的新坐标$ (T_x,T_y) $是一样的  
对于任意一组对应的坐标$ (x_1,y_1) $ $ (x_2,y_2) $都有$ x_1+x_2=T_x;y_1+y_2=T_y$  
所以只要把所有x,y分别加起来并除以n就可以了

**If there are multiple answers, you may print any of them**  
这句话其实是迷惑人的 结果不可能有多种   
### **一定要开 long long !**  
$ 10^3(10^6+2*10^6)=3*10^9>2147483647 $  
## code:
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define LL long long // 一定要开long long
using namespace std;
LL x,y,X = 0,Y = 0;
int main(){
	register LL n;
	cin >> n;
	for(int i = 1;i <= n + n;i ++){
		cin >> x >> y;
		X += x; 
		Y += y; // X,T 分别为Tx Ty 不用管题目里的xyab 直接把所有坐标加起来
	}
	cout << X / n << " " << Y / n << endl; // 除以n 出答案
	return 0;
}
```

---

## 作者：woshishei (赞：1)

我看完这道题的时候的第一反应竟然是**枚举$p$的排列**…… $O(n!)$，不用多说了。

**代码：**（TLE on test 7）
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
struct node
{
	int x,y;
}a[1010],b[1010];
int n,p[1010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&a[i].x,&a[i].y);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&b[i].x,&b[i].y);
	for(int i=1;i<=n;i++)
		p[i]=i;
	do
	{
		bool f=true;
		int tmpx=a[1].x+b[p[1]].x,tmpy=a[1].y+b[p[1]].y;
		for(int i=2;i<=n;i++)
			if(a[i].x+b[p[i]].x!=tmpx||a[i].y+b[p[i]].y!=tmpy)//查询宝藏的坐标是否相等
			{
				f=false;
				break;
			}
		if(!f)
			continue;
		printf("%d %d",tmpx,tmpy);
		return 0;
	}while(next_permutation(p+1,p+n+1));
}
```

------------

分割菌，以下为正解

------------

因为$T$的坐标是固定的，所以可以把其中一个坐标按升序排列，另一个按降序排列。

时间复杂度：$O(nlog_2n)$

**代码：**
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
struct node
{
	int x,y;
}a[1010],b[1010];
int n;
bool cmp1(node _,node __){return _.x==__.x?_.y<__.y:_.x<__.x;}
bool cmp2(node _,node __){return _.x==__.x?_.y>__.y:_.x>__.x;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&a[i].x,&a[i].y);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&b[i].x,&b[i].y);
	sort(a+1,a+n+1,cmp1);//升序
	sort(b+1,b+n+1,cmp2);//降序
	printf("%d %d",a[1].x+b[1].x,a[1].y+b[1].y);
	return 0;
}
```
我在比赛中竟然想了20分钟。。。

然而，还有更简单的代码吗？

**有的！**

$T$的坐标是$(x_i+a_{p_i}, y_i+b_{p_i})$，从而可以推出$n$个$T$的坐标之和是$(\sum_{i=1}^n(x_i+a_i),\sum_{i=1}^n(y_i+b_i))$，答案就是前面的结果除以$n$。

**代码：**
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int n,x,y;
ll sumx=0,sumy=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
	{
		scanf("%d %d",&x,&y);
		sumx+=x;
		sumy+=y;
	}
	printf("%lld %lld",sumx/n,sumy/n);
	return 0;
}
```

---

## 作者：National_Studying (赞：0)

方法一：

因为需要得到一个公共坐标，所以不能两个大的坐标相加，两个小的坐标相加。可得一个大的坐标加一个小的坐标。时间复杂度：$\Omicron(n\log_2{n})$。

正解：

转换成求坐标平均值，可得 $n$ 个 $T$ 的坐标之和是 $(\sum ^n _{i = 1} (x_i + a_i) , \sum ^n _ {i = 1} (y_i + b_i))$，则 $ans$ 就是前面的值 $\div n$。

code：

```
#include <bits/stdc++.h>
typedef int intt;
#define int long long

using namespace std;
int ans_x,ans_y;
intt main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	
	int n;
	cin >> n;
	for (int i = 1;i <= n * 2;i++){
		int a,b;
		cin >> a >> b;
		
		ans_x += a,ans_y += b;
	}
	cout << ans_x / n << " " << ans_y / n;
	return 0;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1091B)

直接讲思路，当所有的 $(x+a,y+b)$ 一样的时候，$n(x+a)=\sum xi+\sum ai$ 对于 $(y+b)$ 同理，问题就解决了。

直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,sx,sy;
int main()
{
	cin>>n;
	for(long long i=1;i<=2*n;i++)
	{
		cin>>x>>y;
		sx+=x;
		sy+=y;
	} 
	cout<<sx/n<<" "<<sy/n<<endl;
	return 0;
}
```

---

## 作者：Suiseiseki (赞：0)

**这道题要开$long$ $long$吗？答案是：不要！**

每一个点的范围都是$-2 \cdot 10^6 \le x,y \le 2 \cdot 10^6$，那么，最后的答案就一定$-4 \cdot 10^6 \le ans \le 4 \cdot 10^6$，根本就不需要！

那么，应该怎么做呢？

可以考虑一下，如果我们不给$y$，只给$x$，那么这个答案是不是很简单？

将$x$中的最大值与最小值相加，就是结果。

这一道题保证有解，那么对于$y$，做相同的操作就可以了。

```cpp
#include <cstdio>
#define Maxn 2000
struct Point{
	int x,y;
}a[Maxn+5];
int mx(int a,int b){
	return a>b?a:b;
}
int mn(int a,int b){
	return a<b?a:b;
}
int main(){
	int n;
	scanf("%d",&n);
	int max_x=(-1<<30),max_y=(-1<<30),min_x=(1<<30),min_y=(1<<30);
	for(int i=1;i<=(n<<1);i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		max_x=mx(max_x,a[i].x);
		min_x=mn(min_x,a[i].x);
		max_y=mx(max_y,a[i].y);
		min_y=mn(min_y,a[i].y);
	}
	printf("%d %d\n",max_x+min_x,max_y+min_y);
	return 0;
}

```

---

## 作者：little_sun (赞：0)

# 题解 CF1091B 【New Year and the Treasure Geolocation】

打cf时网速感人qwq

容易想到一个$O(n^3)$的做法：枚举每一对$(x,y)$与每一对$(a,b)$配对，再判断是否满足条件，满足就输出

但是这样会超时，怎么办？

可以发现我们只要把每一个$(x,y)$与第一个$(a,b)$配对即可

原因？因为每一对$(x,y)$与每一对$(a,b)$配对都要导致第一个$(a,b)$与某一个$(x,y)$配对，而任意一对这样的配对即可唯一确定$T$的位置，故只要枚举一遍每一个$(x,y)$与第一个$(a,b)$配对就能遍历所有情况。

时间复杂度$O(n^2)$

```cpp
# include <bits/stdc++.h>
# define p std::pair<int, int> 

p pos[1010], change[1010];

std::map<p, int> m, tmp;

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &pos[i].first, &pos[i].second);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &change[i].first, &change[i].second), m[change[i]]++;
    for(int i = 1; i <= n; i++)
    {
        p T;
        T.first = pos[i].first + change[1].first;
        T.second = pos[i].second + change[1].second;
        tmp = m;
        int flag = true;
        for(int j = 1; j <= n; j++)
        {
            p tem;
            tem.first = T.first - pos[j].first;
            tem.second = T.second - pos[j].second;
            if(!tmp[tem])
                flag = false;
            --tmp[tem];
        }
        if(flag)
            return 0 * printf("%d %d\n", T.first, T.second);
    }
    return 0;
}
```

---

## 作者：zsc2003 (赞：0)

### CF1091B 2018.12.30

#### 题目大意:

读入一个正整数$n$

接下来读入$n*2$行

一共$n*2$个向量

保证存在一个向量，定于$v$，使得$n*2$个向量两两相加，加出来的$n$个向量等于$v$

#### 思路

从$2$~$n*2$枚举与$1$组合，作为最终向量

接下来从枚举每一个向量，如果存在一个向量可以与之相加得到最终向量，则合并(判断方式：提前用map映射一下)

如果不行则退出，找下一个最终向量

详细细节见代码

下面附上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
inline int read()//读入优化
{
    int r,s=0,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
const int N=1010;
struct node
{
    int x,y;
}a[N<<1];
int n,fx,fy,x,y;
map<pair<int,int>,int> mp1,mp2;
int main()
{
    bool flag;
    n=read();
    n<<=1;
    for(int i=1;i<=n;i++)
        a[i].x=read(),a[i].y=read(),mp1[mp(a[i].x,a[i].y)]++;
    for(int i=2;i<=n;i++)
    {
        flag=0;
        fx=a[1].x+a[i].x,fy=a[1].y+a[i].y;
        mp2=mp1;//将map重新改成之前的
        mp2[mp(a[1].x,a[1].y)]--;
        mp2[mp(a[i].x,a[i].y)]--;
        for(int j=2;j<=n&&(!flag);j++)
            if(mp2[mp(a[j].x,a[j].y)])
            {
                mp2[mp(a[j].x,a[j].y)]--;
                x=fx-a[j].x,y=fy-a[j].y;
                if(mp2[mp(x,y)])
                    mp2[mp(x,y)]--;
                else
                    flag=1;
            }
        if(!flag)
        {
            printf("%d %d\n",fx,fy);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：小黑AWM (赞：0)

此题不难想到$O(n^2)$的做法，即将所有的$(x,y)$和$(a,b)$一一配对，用map统计每种$(x+a,y+b)$出现的次数，出现n次的即为答案。

但是我用这个做法莫名第八点RE
```cpp
#include <cstdio>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10;
int n, x[maxn], y[maxn], a, b;
pair<int, int> storage[maxn];
int top;
map<pair<int, int>, int> func;
int main(){
    cin >> n;
    for(int i = 1 ; i <= n; i++)
        cin >> x[i] >> y[i];
    for(int i = 1 ; i <= n; i++){
        cin >> a >> b;
        for(int j = 1; j <= n; j++){
            func[make_pair(x[j]+a, y[j]+b)]++,
            storage[++top] = make_pair(x[j]+a, y[j]+b);
            if(func[make_pair(x[j]+a, y[j]+b)] == n){
                cout << x[j]+a << " " << y[j]+b << endl;
                return 0;
            }
        }
    }
    return 0;
}
```

那就得想其他做法，我们不难发现，
 _当所有的(x+a,y+b)一样的时候，$n(x+a) = \sum{xi}+\sum{ai}$_ 对于$(y+b)$同理，那么问题迎刃而解。
 
 需要注意的是，当我们求和的时候要开long long因为最大的时候是(1e6+2e6)*1e3 = 3e9刚刚好爆了int，而Pretest里是没有这样的数据的（~~所以我被hack了~~
 ```cpp
#include <cstdio>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10;
long long n, x, y, sumx, sumy;
int main(){
    cin >> n;
    for(int i = 1 ; i <= 2*n; i++)
        cin >> x >> y,
        sumx += x,
        sumy += y;
    cout << sumx/n << " " << sumy/n << endl;

    return 0;
}
```

---

