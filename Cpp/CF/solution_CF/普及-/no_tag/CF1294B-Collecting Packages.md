# Collecting Packages

## 题目描述

There is a robot in a warehouse and $ n $ packages he wants to collect. The warehouse can be represented as a coordinate grid. Initially, the robot stays at the point $ (0, 0) $ . The $ i $ -th package is at the point $ (x_i, y_i) $ . It is guaranteed that there are no two packages at the same point. It is also guaranteed that the point $ (0, 0) $ doesn't contain a package.

The robot is semi-broken and only can move up ('U') and right ('R'). In other words, in one move the robot can go from the point $ (x, y) $ to the point ( $ x + 1, y $ ) or to the point $ (x, y + 1) $ .

As we say above, the robot wants to collect all $ n $ packages (in arbitrary order). He wants to do it with the minimum possible number of moves. If there are several possible traversals, the robot wants to choose the lexicographically smallest path.

The string $ s $ of length $ n $ is lexicographically less than the string $ t $ of length $ n $ if there is some index $ 1 \le j \le n $ that for all $ i $ from $ 1 $ to $ j-1 $ $ s_i = t_i $ and $ s_j < t_j $ . It is the standard comparison of string, like in a dictionary. Most programming languages compare strings in this way.

## 说明/提示

For the first test case in the example the optimal path RUUURRRRUU is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294B/e4c36c660714086e3ff8d4a648ef3d91b10cec02.png)

## 样例 #1

### 输入

```
3
5
1 3
1 2
3 3
5 5
4 3
2
1 0
0 1
1
4 3```

### 输出

```
YES
RUUURRRRUU
NO
YES
RRRRUUU```

# 题解

## 作者：_QyGyQ_ (赞：3)

## 大意:
你是一个机器人，给你一些点，问你是否能只通过上或右经过所有点。
## 思路:
因为你在去到一个点时，可以顺手将沿途上的点经过。那么可以排下序。在进行模拟，用两个变量来模拟当前坐标。如果到达下一点需要向下或向左，则无法全部到达。
## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+7;
int n;
struct node{
	int x,y;
}a[N];
bool cmp(node a,node b){
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		string ans="";
		int nowx=0,nowy=0;//当前坐标 
		bool f=true;
		for(int i=1;i<=n;i++){
			cin>>a[i].x>>a[i].y;
		}
		sort(a+1,a+n+1,cmp);//排序 
		for(int i=1;i<=n;i++){
			if(nowx<a[i].x){
				for(int j=1;j<=a[i].x-nowx;j++){
					ans+='R'; 
				}
				nowx=a[i].x;//x移动到当前x 
			}
			if(nowy<a[i].y){
				for(int j=1;j<=a[i].y-nowy;j++){
					ans+='U';
				}
				nowy=a[i].y;//y移动到当前y 
			}
			if(nowx>a[i].x||nowy>a[i].y){
				f=false;//没有答案，退出
				break;
			}
		}
		if(f){
			puts("YES");
			cout<<ans<<"\n";
		}
		else puts("NO");
	}
	return 0;
}
```



---

## 作者：ChrisWangZi (赞：2)

# CF1294B Collecting Packages 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF1294B)

## 题目大意

机器人只能向上、右移动，问可不可以到达沿途上的所有点。如果能，给出一种方法。

## 思路

模拟。

先排序（$x$ 轴为第一关键字， $y$ 轴为第二关键字），再循环枚举每个点。（对于 $i,j(1 \le i,j \le n)$，当有 $x_i \le x_j,y_i \ge y_j$ 时才不可行，具体见下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/16iogsbv.png)

## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct pos{
public:
	int x,y;
};
pos a[1005];
bool cmp(pos c,pos d){
	if(c.x!=d.x){
		return c.x<d.x;
	}
	else{
		return c.y<d.y;
	}
}
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		sort(a+1,a+1+n,cmp);
		string ro="";
		int hr=0;
		bool f=true;
		a[0].x=0,a[0].y=0;
		for(int i=1;i<=n;i++){
			if(a[i].y<hr){
				cout<<"NO\n";
				f=false;
				break;
			}
			else{
				for(int j=a[i-1].x+1;j<=a[i].x;j++){
					ro.append("R");
				}
				for(int j=a[i-1].y+1;j<=a[i].y;j++){
					ro.append("U");
				}
				hr=a[i].y;
			}
		}
		if(f){cout<<"YES\n";cout<<ro<<endl;}
	} 
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# 思路
一道模拟题。

首先很容易想到要先对这些位置排个序，离原点越近的就先走，否则就后走。然后考虑模拟，如果在不后退的情况下能到达，那么就一直往右走，走不动了就往上走，以此类推；如果到达不了下一个点，则直接输出 ```NO```。

具体细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1100;
struct pos{
	int x,y;
}a[N];
bool cmp(pos a,pos b){//排序，标准为离原点的远近
	return a.x+a.y<b.x+b.y;
}
int T,n;
int main(){
	cin>>T;
	while(T--){//多组数据
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		sort(a+1,a+1+n,cmp);
		string ans="";
		int x=0,y=0;
		for(int i=1;i<=n;i++){
        //贪心
			if(x<=a[i].x&&y<=a[i].y){//可以到达
				for(int j=x+1;j<=a[i].x;j++){//一直向右走
					ans+='R';//更新答案
				}
				for(int j=y+1;j<=a[i].y;j++){//一直向上走
					ans+='U';//更新答案
				}
			}else{//到达不了
				ans="NO";//直接退出
				break;
			}
			x=a[i].x,y=a[i].y;//更新当前位置
		}
		if(ans!="NO")cout<<"YES"<<endl;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：QWQ_SenLin (赞：0)

思路比较直接，因为要到达所有的点且路径最短，因此考虑让机器人优先离自己近的点，然后依次走过这些点。

所以我们可以先按照每个点离原点的距离排序，然后模拟机器人的行动，最后输出路径即可。

接下来我们来想下机器人不能完成的情况，发现机器人只能向上或右移动，因此设当前机器人在 $(x_1,y_1)$ 这个位置上，如果有其他包裹（输入的点）有一个的坐标 $(x_2,y_2)$ 满足 $x_2 < x_1$ 或者 $y_2 < y_1$ 机器人就一定无法取到这个包裹。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int T , n;
struct Point{
    int x , y;
    bool operator < (const Point &b) const {
        //按照离原点的距离排序
        return x + y < b.x + b.y;
    }
}qwq[1005];

int main(void){
    scanf("%d" , &T);
    while(T--){
        char ans[100005]; int cnt = 0;
        scanf("%d" , &n);
        for(int i = 1;i <= n;i++)
            scanf("%d%d" , &qwq[i].x , &qwq[i].y);
        sort(qwq + 1 , qwq + 1 + n);
        int xx = 0 , yy = 0; //初始在原点
        int now = 1;
        bool flag = false;
        while(now <= n){
            if(qwq[now].y < yy || qwq[now].x < xx){ 
                //下一个点在下面，无法走到
                puts("NO");
                flag = true;
                break;
            }
            while(xx < qwq[now].x){
                ans[++cnt] = 'R';
                xx++;
            }
            while(yy < qwq[now].y){
                ans[++cnt] = 'U';
                yy++;
            }
            now++;
        }
        ans[++cnt] = '\0';
        if(flag)
            continue;
        puts("YES");
        printf("%s\n" , ans + 1); //我这里从1开始存
    }
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，只允许向右和向上移动。所以，我们可以对输入的坐标以 $x_i$ 为第一关键字，以 $y_i$ 为第二关键字按升序排序，这样就可以确保 $x_i\le x_{i+1}$。对于任何 $x_i\le x_{i+1}$ 且 $y_i>y_{i+1}$ 的情况，明显无法两个点都到达，所以输出 `NO`。而对于可以到达的情况，就输出 `YES`，设置原点为当前坐标，遍历排序后的坐标列表为下一个坐标，先输出当前坐标向右要走多远到下一个坐标，再输出当前坐标向上要走多远到下一个坐标，最后把当前坐标更新为下一个坐标，继续下一次遍历。
## 代码
```python
a=int(input())
for b in range(a):
    c=int(input())
    d,f=sorted([list(map(int,input().split())) for e in range(c)],key=lambda x:(x[0],x[1])),0
    for e in range(len(d)-1):
        if d[e][1]>d[e+1][1]:
            f=1
            print('NO')
            break
    if f==0:
        print('YES')
        g,h=0,0
        for i in d:
            print('R'*(i[0]-g),end='')
            print('U'*(i[1]-h),end='')
            g,h=i[0],i[1]
        print()
```

---

## 作者：ZHANGyutao123 (赞：0)

题目传送门：[CF1294B Collecting Packages](https://www.luogu.com.cn/problem/CF1294B)

# 题意

在一个平面上，有 $n$ 个点，现在有一只机器人在坐标 $(0,0)$，每次只能朝上或者朝右走。

现在请你输出一种收集所有点的方法，使得其代价最小，如果有多种方案则输出字典序最小的一种。代价为机器人走的步数。

# 思路

题目要求输出一种收集点的方法，使得其代价最小，同时还要按字典序排序。因为机器人只能向上或向右走，所以肯定是将所有点按照横纵坐标的和来排序，这样除了第一个点 $(0,0)$ 以外，其余每一个点的横纵坐标的和都大于前一个点，使得机器人肯定能从前一个点到达这个点。

如果我们将点按照横纵坐标的和进行排序，那么对于这个点 $(x_i,y_i)$：

- 如果 $x_i>x_{i-1}$，那么肯定是机器人先向右再向上，直到到达 $(x_i,y_i)$；
- 如果 $y_i>y_{i-1}$，那么肯定是机器人先向上再向右，直到到达 $(x_i,y_i)$。

那么只需要按照横纵坐标之和递增的顺序选择每个点，判断它能否按照上述规则到达即可。注意，如果存在一个点不满足，那么就无解。

最后，如果成功收集所有的点，就输出对应方案。

时间复杂度：$O(n\log n)$。

# 注意事项

- 为了满足字典序最小的要求，我们可以选择尽量先向右走，后向上走。
- 单组数据输出完毕后要换行，否则会被认为是输出不正确。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

// 定义一个结构体存储每个点的横纵坐标
struct Node {
    int x, y;
} a[MAXN];

// 排序函数，按照横纵坐标之和递增的顺序排序
bool cmp(Node x, Node y) {
    return x.x + x.y < y.x + y.y;
}

int main() {
    // 输入数据组数
    int t;
    cin >> t;
    while (t--) {
        // 定义一个字符串用于存储结果
        string ans = "";
        // 输入点的个数
        int n;
        scanf("%d", &n);
        // 输入每个点的横纵坐标
        for (int i = 0; i < n; ++i) {
            cin >> a[i].x >> a[i].y;
        }
        // 按照排序函数排序
        sort(a, a + n, cmp);
        // 初始化机器人当前的位置为 (0,0)
        int x = 0, y = 0;
        // 遍历所有点
        for (int i = 0; i < n; ++i) {
            // 如果从上一个点能够直接垂直走到当前点
            if (x <= a[i].x && y <= a[i].y) {
                // 先向右走一段距离，距离为当前点的横坐标减去机器人的横坐标
                ans += string(a[i].x - x, 'R');
                // 再向上走一段距离，距离为当前点的纵坐标减去机器人的纵坐标
                ans += string(a[i].y - y, 'U');
                // 更新机器人的位置为当前点
                x = a[i].x;
                y = a[i].y;
            } else {
                // 如果从上一个点无法到达当前点，则直接退出循环，输出 "NO" 
                ans = "NO";
                break;
            }
        }
        // 输出结果
        cout << (ans != "NO" ? "YES\n" + ans + "\n" : "NO\n");
    }
    return 0;
}
```



---

## 作者：GoldenFishX (赞：0)

### 主要思路
- 首先按照 $x_i$ 与 $y_i$ 的和排序(显然是从近的开始走)。按照 $x_i$ 与 $y_i$ 的和排序是因为从 $(0,0)$ 走到 $(x,y)$ 一共需要 $x_i+y_i$ 步。

- 然后开始按照排序后的数组走，如果 $X \le x_i$ 且 $Y \le y_i$ 说明这个点就可以到达。( $X$ 和 $Y$ 是当前的位置)

- 从 $(x_i,y_i)$ 走到 $(x_{i+1},y_{i+1})$, 一共要向右走 $x_{i+1}-x_i$ 步（ $x$ 轴的距离）,向右走 $y_{i+1}-y_i$ 步（ $y$ 轴的距离）。

- 当有点到不了时，把ans设成 ```NO``` 再退出循环即可

### 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000 + 5;
struct Node { //开个结构体存要到达的点方便排序
  int x, y;
}a[MAXN];
int n;
bool cmp(Node x, Node y) {
  return x.x + x.y < y.x + y.y; //根据x和y的和从小到大排序
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    string ans = "";//初始化，防止后面出问题
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
      cin >> a[i].x >> a[i].y;
    }
    sort(a, a + n, cmp); //排序
    int x = 0, y = 0; //当前的坐标
    for(int i = 0; i < n; i++) {
      if(x <= a[i].x && y <= a[i].y) {//可以到达
        for(int j = 0; j < a[i].x - x; j++) { //x轴的距离
          ans += 'R';
        }
        for(int j = 0; j < a[i].y - y; j++) { //y轴的距离
          ans += 'U';
        }
        x = a[i].x; //更新当前的位置
        y = a[i].y;
      } else { //无法到达这个点
        ans = "NO";
        break;
      }
    }
    if(ans != "NO") { //输出答案
      cout << "YES\n" << ans << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}

```

---

## 作者：YooLc407 (赞：0)

## 题目大意

给定 $n$ 个包裹的坐标 $(x,y)$ ，将其按照字典序排序，如果能够从第 $1$ 个走到第 $n$ 个，那么输出 ``YES`` 并给出最短路径，否则输出 ``NO``。

其中字典序是先比较 $x_i$ 的大小，如果相等再比较 $y_i$ 的大小，保证 $(0,0)$ 没有包裹，且每个点包裹只有一个。机器人只能向上走（输出``U``）或向右走（输出``R``）

## 思路

先对包裹进行排序，考虑到机器人不能向下走，那么每个包裹的 $y_i$ 值一定是单调不减小的，也就是 $y_i \ge y_{i-1}\ ,2\le i\le n$ ，检查即可。

如果确定有解，那么输出路径，只要是排过序在挨个走肯定是最短路径，我是按照样例里的来，先向右后向上走。

## 部分代码

```cpp
void solve()
{
	memset(a, 0, sizeof(a));
	int n, flag = 1;
	n = rd();
	for(int i = 1; i <= n; ++i)
	{
		a[i].x = rd();
		a[i].y = rd();
	}
	sort(a + 1, a + 1 + n, cmp); 
	// cmp 函数请自己写，或者在结构体里重载 <
	for(int i = 2; i <= n; ++i)
	{
		if(a[i].y < a[i - 1].y)
		{
			flag = false; // 检查是否不能走通
		}
	}
	if(flag)
	{
		puts("YES");
		int curx = 0, cury = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(a[i].x != a[i - 1].x)
			{
				int dis = a[i].x - curx;
				for(int j = 1; j <= dis; ++j) putchar('R');
                // 话说python里可以直接输出 (a[i] - curx) * "R" 的
				curx = a[i].x;
			}
			if(a[i].y != a[i - 1].y)
			{
				int dis = a[i].y - cury;
				for(int j = 1; j <= dis; ++j) putchar('U');
				cury = a[i].y;
			}
		}
		putchar('\n');
	}
	else puts("NO");
}
```

---

