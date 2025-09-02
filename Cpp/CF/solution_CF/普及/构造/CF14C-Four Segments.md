# Four Segments

## 题目描述

Several months later Alex finally got his brother Bob's creation by post. And now, in his turn, Alex wants to boast about something to his brother. He thought for a while, and came to the conclusion that he has no ready creations, and decided to write a program for rectangles detection. According to his plan, the program detects if the four given segments form a rectangle of a positive area and with sides parallel to coordinate axes. As Alex does badly at school and can't write this program by himself, he asks you to help him.

## 样例 #1

### 输入

```
1 1 6 1
1 0 6 0
6 0 6 1
1 1 1 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 0 0 3
2 0 0 0
2 2 2 0
0 2 2 2
```

### 输出

```
NO
```

# 题解

## 作者：qwerty12346 (赞：6)

# [题目传送门](https://www.luogu.com.cn/problem/CF14C)

## 题意

这题就是说给你四条线段的起点，终点坐标，四条线段平行或垂直坐标轴，而你要判断这四条线段能否构成矩形。

## 思路

用结构体存每一个端点的坐标。并判断每一条边是否平行于坐标轴，判断两个端点是否相同，判断是否只有两条边平行于同一坐标轴，判断一个点是否连接了两条以上的边或者只连接了一条边。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct X{//结构体
    int x,y,z;//z用来判断是否已经有相同的点
}f[1005];
int n,m,a,b,c,d,e,ret;
int main(){
    for(int i=1;i<=4;i++) 
    {
	cin>>a>>b>>c>>d;
	if((a==b&&c==d)||(a!=c&&b!=d))//判断
        {
	    cout<<"NO";
	    return 0;
	}
	if(a==c)n++; 
        if(b==d)m++; 
        f[++e].x=a;
        f[e].y=b;
        f[++e].x=c;
        f[e].y=d;
    }
    if(n!=2||m!=2)//判断
    {
	cout<<"NO";
	return 0;
    }
    for(int i=1;i<=e;i++) 
    {
	if(f[i].z)continue;//如果找到了相同的点就下一个
	ret=0;
	for(int j=i+1;j<=e;j++) 
        {
	    if(f[i].x==f[j].x&&f[i].y==f[j].y)
            {
	        ret++;
		f[j].z=1;
	    }
	}
	if(ret!=1)//判断
        {
	    cout<<"NO";
	    return 0;	
	}
    }
    cout<<"YES";
    return 0;
}

```


---

## 作者：晨·曦 (赞：4)

### - 题意

在平面直角坐标系内，给定四条线段的端点，问能不能围成一个**矩形**

### - 思路

用**结构体**存每一个端点的坐标。$\because$ 要围成一个矩形，$\therefore$ 只要判断每个端点是不是和**另一条**线段的一个端点重合即可。

##### 坑点

1. 判断每一条边是否平行于坐标轴；
2. 判断一条边是否变成了一个点，即两个端点相同；
3. 判断是否只有两条边平行于同一坐标轴
4. 判断一个点是否连接了两条以上的边或只连接了一条（这个点被卡了好久。。。）

这道题的坑点是真的多！

### - 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x;
	int y;
	bool b; //判断是否已经有相同的点
}a[114];
int ax,ay,l; //ax，ay是平行于x轴，y轴的边的数量
int main() {
	for(int i=1; i<=4; i++) {
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		if((x1==y1&&x2==y2)||(x1!=x2&&y1!=y2)) { //坑点1，2
			cout<<"NO";
			return 0;
		}
		if(x1==x2) ax++; 
                if(y1==y2) ay++; 
                a[++l].x=x1;
                a[l].y=y1;
                a[++l].x=x2;
                a[l].y=y2;
	}
	if(ax!=2||ay!=2) { //坑点3
		cout<<"NO";
		return 0;
	}
	for(int i=1; i<=l; i++) {
		if(a[i].b) continue; // 已经找到相同的点就跳过
		int p=0; //跟这个端点相同的点的数量
		for(int j=i+1;j<=l;j++) {
			if(a[i].x==a[j].x&&a[i].y==a[j].y) {
				p++;
				a[j].b=1;
			}
		}
		if(p!=1) { //坑点4
			cout<<"NO";
			return 0;	
		}
	}
	cout<<"YES";
	return 0;
}
```


---

## 作者：Mistybranch (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF14C)

给出四条线段的起终点坐标，四条线段平行或垂直坐标轴，问这四条线段能否构成矩形。橫，纵坐标的绝对值绝不超过 $10^9$。

一道简单的几何题，直接说思路：

- 检查每条边有没有退化成点（即为边的起终点横纵坐标有没有分别都相等）和是否垂直或平行于于坐标轴（即为边的起终点横纵坐标有没有都不相等）。

```cpp
if (x1 == x2 && y1 == y2 || x1 != x2 && y1 != y2) {
	ans = false;
}
```
- 检查每个方向的边是否都有两条（只用判断一个方向边的个数即可，因为总数是固定的）。

```cpp
int countY = 0;

if (x1 == x2){
	countY++;
}

if (countY != 2) {
	ans = false;
}
```

- 将四条边的八个起终点排序后，判断八个点是否两两重合。

```cpp
sort(pos + 1, pos + 8 + 1);

if (!(pos[1] == pos[2] && pos[3] == pos[4] && pos[5] == pos[6] && pos[7] == pos[8] && pos[2] != pos[3] && pos[4] != pos[5] && pos[6] != pos[7])) {
	ans = false;
}
```
完整代码：

```cpp


#include <bits/stdc++.h> 

using namespace std;

struct node {
	int x, y;
	
	bool operator < (const node & one) const {
		if (x == one.x) {
			return y < one.y;
		}
		
		return x < one.x; 
	}
	
	bool operator == (const node & one) const {
		return x == one.x && y == one.y; 
	}
	
	bool operator != (const node & one) const {
		return !(x == one.x && y == one.y); 
	}
}pos[19];

bool ans = true;

int main () {
	int countY = 0;
	
	for (int i = 1; i <= 4; i++) {
        scanf("%d %d %d %d", &pos[2 * i - 1].x, &pos[2 * i - 1].y, &pos[2 * i].x, &pos[2 * i].y);
		
		if (pos[2 * i - 1].x == pos[2 * i].x && pos[2 * i - 1].y == pos[2 * i].y || pos[2 * i - 1].x != pos[2 * i].x && pos[2 * i - 1].y != pos[2 * i].y) {
			ans = false;
		}
		
		if (pos[2 * i - 1].x == pos[2 * i].x) {
			countY++;
		}
	}
	
	if (countY != 2) {
		ans = false;
	}
	
	else if (ans) {
		sort(pos + 1, pos + 8 + 1);
		
		if (!(pos[1] == pos[2] && pos[3] == pos[4] && pos[5] == pos[6] && pos[7] == pos[8] && pos[2] != pos[3] && pos[4] != pos[5] && pos[6] != pos[7])) {
			ans = false;
		}
	}
	
	if (ans) {
		printf("YES\n");
	}
	
	else {
		printf("NO\n");
	}
	
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：2)

**[题解 【CF14C Four Segments】](https://www.luogu.com.cn/problem/CF14C)**    
# Solution  

先在大脑里画一个矩形。  
然后就有了对于解决这道题目的几个关键性质。  
- 1：对边平行，邻边垂直  
- 2：四条线段**首尾**拼接而成

好，接下来专门解决一些细节。  
题目中已经保证了输入数据与坐标轴平行，所以说可以不用判断这个问题，当然，判断一下更好。  
在保证上述条件的同时，第二个要做的事情就是判断是否由四条线段首尾拼接而成，这个只需要判断线段的每一个端点是否出现两次即可。  
最后判断一下这 4 条线段是否出现重合现象。  
这题就做完了，觉得评橙就差不多了。

# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

#define gc getchar
inline int read() {
	int c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

map <pair <int,int>,int>mp;

int a,b,c,d;
int x,y,cnt;

int main() {
	for(int i = 1;i <= 4;i++) {
		a = read(); b = read();
		c = read(); d = read();
		mp[make_pair(a,b)]++; mp[make_pair(c,d)]++;	//先存下所有的点，这样子就可以方便判重
		if(a != c && b != d) puts("NO"),exit(0);	//如果说输入不符合题目要求，肯定是不行的
		x += (a == c); y += (b == d);	//搞出来这是和什么轴平行的，易得有且只有两条线段会与同一轴平行
		cnt += (mp[make_pair(a,b)] == 2);	//判断有几个点重合，易得有且只有四个点会重合
		cnt += (mp[make_pair(c,d)] == 2);	//同上
	}
	if(x != 2 || y != 2 || cnt != 4) puts("NO"),exit(0);	//如果不满足以上条件，就输出不符合
	puts("YES");
	return 0;
}

```

---

## 作者：囧仙 (赞：2)

## 题目大意

> 给定四个点，询问它们能否组成笛卡尔坐标系上的面积不为 $0$ 的各边平行于坐标轴上的矩形。

## 题解

考虑直接枚举矩形的对角线上的点。由于目标矩形的四条边平行于坐标轴，因此可以求出组成该矩形的四条边。在读入的时候用个 $\text{map}$ 存下笛卡尔坐标系上有哪些边，然后判断即可。

注意在枚举对角线上的点时判一下这两个点的 $x$ 坐标和 $y$ 坐标是否存在相同。若相同则不合法。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef pair<int,int> pii;
const int INF =2147483647;
map<pair<pii,pii>,bool> M;
pii P[8]; int n;
int main(){
    up(0,3,i){
        int a,b,x,y; scanf("%d%d%d%d",&a,&b,&x,&y);
        P[n++]={a,b},P[n++]={x,y};
        M[{P[n-2],P[n-1]}]=M[{P[n-1],P[n-2]}]=true;
    }
    up(0,7,i) up(0,i+1,j){
        auto x=P[i],y=P[j],a=x,b=y;
        if(x.first==y.first||x.second==y.second) continue;
        a.second=y.second,b.second=x.second;
        if(M[{x,a}]&&M[{a,y}]&&M[{y,b}]&&M[{b,x}])
            puts("YES"),exit(0);
    }
    puts("NO"); return 0;
}
```

---

## 作者：Gogococoyoyo (赞：2)

总体思路就是判断直线所有端点出现的次数以及每条直线的状态

```cpp
#include <bits/stdc++.h>
using namespace std;
int tot,cntx,cnty,sum;

struct node{
	int x,y;
	bool used;
};
node a[10];

int main(){
	for(int i=1;i<=4;++i){
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		//把点加入a数组中 
		a[++tot]=(node){x1,y1};
		a[++tot]=(node){x2,y2};
		//统计平行于x轴 y轴的直线各有几条 如果出现斜线则输出NO 
		if(x1!=x2 && y1!=y2){
			puts("NO");
			return 0;
		}
		if(x1==x2)
			++cntx;
		if(y1==y2)
			++cnty;
	}
	if(cntx!=2 || cnty!=2){
		puts("NO");
		return 0;
	}
	//判断出现不同点的数量 暴力枚举两两不同的点 
	for(int i=1;i<=tot;++i){
		int cnt=0;
		if(a[i].used)
			continue;
		//遍历过了就跳 
		for(int j=i+1;j<=tot;++j)
			if(a[i].x==a[j].x && a[i].y==a[j].y){
				++cnt;
				a[j].used=true;
			}
		if(cnt!=1){
			puts("NO");
			return 0;
		}
		//每个点在正常情况下会被两条直线经过，所以除去第一次便利的点还有一组点和它相同 
		++sum;
	}
	if(sum==4)
		puts("YES");
	else
		puts("NO");
}
```


---

## 作者：yimuhua (赞：2)

## 题意：
给出四条线段，问这四条线段是否能构成矩形。线段都平行或垂直于垂直坐标轴。

## 思路：
对于合法的矩形，必定有且仅有四个点重合，并且分别有且仅有两条边垂直和平行于垂直坐标轴。

看到数据范围，想到我们可以使用 ```map``` 来维护点的重合，用两个变量来分别维护垂直于和平行于垂直坐标轴的线段数。注意输入时就要判断是否有既不平行也不垂直于垂直坐标轴的线段，有则直接输出 ```"NO"```

## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, cnt;
map<pair<int, int>, int> m; 
int main() {
    for(int i = 0, a, b, c, d; i < 4; i++) {
        cin >> a >> b >> c >> d, m[make_pair(a, b)]++, m[make_pair(c, d)]++;
        if(a != c && b != d) {
            cout << "NO";
            return 0;
        }
        x += a == c, y += b == d, cnt += m[make_pair(a, b)] == 2, cnt += m[make_pair(c, d)] == 2;
    }
    cout << ((x != 2 || y != 2 || cnt != 4) ? "NO" : "YES");
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

### 前言

这道题目看似很简单实际上还是有很多的细节要注意一下。

### 分析

题目就是说，有 $4$ 条线段，那么问这 $4$ 条是否可以构成一个矩阵。

但是题目没有说 **没有斜边**，**没有重边**，**没有重点**。

这 $3$ 个条件还是比较重要的。

怎么处理斜边呢？

那么我们用一个判断：

```cpp
if (x!=x_ && y!=y_) return 0&puts("NO");
```

如果说两个 $x,y$ 都不一样，那么证明是斜边。

重点怎么处理呢？

开个 map ，$x$ 和 $y$ 如果出现过了 $2$ 次那么就，tot +1，到最后判断一下 tot 是不是 $4$ ，如果是 $4$，那么证明没有 $4$ 个点，也就表示不能构成矩阵。

重边怎么处理呢？

重边我们可以发现一个特性，就是说呢，重边的两个 $x$ 和 $y$ 都是一样的，也就是说，$x$ 和 另一个 $x$ ，或者 $y$ 和 另一个 $y$ ，都是相同的。

上面的话如果读不懂可以多读几遍，或者在纸上模拟一下。

那么我们用几个个判断处理：

```cpp
                if (x==x_) tot_x++;
                if (y==y_) tot_y++;
                ...
                if (tot_x!=2 || tot_y!=2) return 0&puts("NO");//在普通的情况之下，tot_x 和 tot_y 都是 2。
```

如果是重边的话 tot_x 或者 tot_y 就是 $4$ 。

然后就 AC 了。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <map>
//头文件不多说。
using namespace std;
map< pair<int,int>,int> Map;
//map + pair 设定。
int tot_x,tot_y,tot;
//几个判重复的变量。
signed main()
{
        for (int i=1; i<=4; ++i) {
                int x=0,y=0,x_=0,y_=0;
                scanf("%d %d %d %d",&x,&y,&x_,&y_);
                //读入 4 个点。
                Map[make_pair(x,y)]++;
                Map[make_pair(x_,y_)]++;
                //这几个元素+1。
                if (x!=x_ && y!=y_) return 0&puts("NO");
                //如果是斜边那么，输出 "NO"。
                if (x==x_) tot_x++;
                if (y==y_) tot_y++;
                //判断重边。
                if (Map[make_pair(x,y)]==2) tot++;
                if (Map[make_pair(x_,y_)]==2) tot++;
                //判断重点。
        }
        if (tot_x!=2 || tot_y!=2) return 0&puts("NO");//如果是重边那么输出 "NO" 。
        if (tot==4) return 0&puts("YES");
        //如果说不是重点，那么就输出 "YES" 。
        // puts("ok");
        // printf("%lld\n",Map.size());
        return 0&puts("NO");//如果是重点那么 输出 "NO"。
}

```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF14C)

[Codeforces 链接](https://codeforces.com/problemset/problem/14/C)

题目大意：

这一个题让我们输入四个坐标 $(x,y)$，判断这四个点能否组成长方形，如果能输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

思路：

因为这一个题只需要我们判断是否能组成长方形，所以我们可以先判断这些东西：

1. 这些线段是否退化成了点（即线段的两个端点一样）；
1. 横着的线段和竖着的线段是否都只用两条（__注意：因为这些点总共才四条，所以我们只需要记录横着的__）；
1. 每个点是否只重复了两次。

用一个```bool```类型变量把是否有错误记录下来，按时输出就行了。

上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct node{
    int x, y;
}nd[9];

inline bool cmp(const node &a, const node &b){// 双关键字排序比较函数
    if (a.x != b.x){
        return a.x < b.x;
    }
    return a.y < b.y;
}

inline bool is_equal(const node &a, const node &b){// 判断两个坐标是否一样
    return a.x == b.x && a.y == b.y;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout加速
    bool flag = false;
    int cnt_x = 0, cnt_y = 0;
    for (int i = 1; i <= 4; i++){
        cin >> nd[(i << 1) - 1].x >> nd[(i << 1) - 1].y >> nd[i << 1].x >> nd[i << 1].y;
        if (is_equal(nd[(i << 1) - 1], nd[i << 1])){
            flag = true;// 如果这一条线退化成了点，就记录下来
        } else if (nd[(i << 1) - 1].x == nd[i << 1].x){
            cnt_x++;// 将横着的记录下来
        }
    }
    if (flag || cnt_x != 2){// 如果有错误或者横着的不是两条
        cout << "NO\n";// 那么输出并退出程序
        return 0;
    }
    sort(nd + 1, nd + 9, cmp);// 注意：要排序！
    if (!(is_equal(nd[1], nd[2]) && is_equal(nd[3], nd[4]) && is_equal(nd[5], nd[6]) && is_equal(nd[7], nd[8]) && !is_equal(nd[2], nd[3]) && !is_equal(nd[4], nd[6]) && !is_equal(nd[6], nd[7]))){// 判断这些点是否只重复了两次
        flag = true;
    }
    if (flag){// 输出
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
    return 0;
}
```

---

## 作者：Insouciant21 (赞：0)

#### 题意
给出四条线段的两个端点坐标，判断这四条线能否组成一个四边平行于坐标轴的长方形。

#### 分析

首先题目要求边平行于坐标轴，所以要如果有不平行于任一坐标轴的边时一定输出 `NO` 。

数据可能会出现 $x_1=x_2$ 并且 $y_1=y_2$ 的情况，此时该边退化为一点，不可能组成长方形，所以一定为 `NO` 。

一个满足要求的长方形，必有两边平行于同一条坐标轴，所以如果有更多的线平行于某一坐标轴时，不可能为长方形。

- 当 $y_1=y_2$ 且 $x_1 \neq x_2$ 时，该线段平行于x轴
- 当 $x_1=x_2$ 且 $y_1 \neq y_2$ 时，该线段平行于y轴

在去除以上情况后，可从一边出发，可发现必有一个端点重合，所以我们可以从一边出发，逐步向前推，当遇到多个点连接在同一条边时，不可能为长方形。

联通四条边后即这四条边可以组成长方形。

#### 代码

```
#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

struct Line {
    Point f[2]; 
} s[4];

int ax, ay;
bool use[4];

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d %d %d %d", &s[i].f[0].x, &s[i].f[0].y, &s[i].f[1].x, &s[i].f[1].y); // 一次读入一条边
        if (s[i].f[0].x == s[i].f[1].x)
            ax++; //平行于y轴
        if (s[i].f[0].y == s[i].f[1].y)
            ay++; // 平行于x轴
        if (s[i].f[0].y == s[i].f[1].y && s[i].f[0].x == s[i].f[1].x) { // 该边退化为点
            puts("NO");
            return 0;
        }
    }
    if (ax == ay && ax == 2) {
        Point now = s[0].f[1]; // 从第一条边开始找
        Point ftr = s[0].f[0];
        int sum = 0;
        int place = 0;
        int p = 0;
        use[0] = 1;
        while (sum != 3) {
            int cnt = 0;
            bool add = false;
            for (int i = 0; i < 4; i++) {
                if (use[i] || i == place)
                    continue;
                for (int j = 0; j < 2; j++) {
                    if (now.x == s[i].f[j].x && now.y == s[i].f[j].y) {
                        add = true;
                        cnt++;
                        ftr = s[i].f[!j];
                        p = i;
                    }
                }
            }
            if (cnt != 1) { // 判断是否只有一条边与该边连接
                puts("NO");
                return 0;
            }
            if (add && cnt == 1) {
                use[p] = 1;
                place = p;
                now = ftr;
                sum++;
            }
        }
        if (now.x == s[0].f[0].x && now.y == s[0].f[0].y) { // 与最后一个点是否能连接上
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

~~这道题不难，但是悲催的蒟蒻被坑了很久。~~

来总结一下有哪些**坑**吧。

## 1.判**斜线**

>一开始，我的程序没有写**斜线判断**,结果悲惨 WA 。

>发现 CF 有个这样的~~毒瘤~~数据（第九个点）：

```cpp
0 0 1 1
1 1 2 0
2 0 1 -1
1 -1 0 0
```

>只需要**这一行**，就可以判断斜线：

```cpp
if(sx!=ex&&sy!=ey)EXIT;
```

## 2.判**重边**

>~~坑爹的~~ CF 还有这样的一个数据：
```cpp
0 0 0 2
2 0 2 2
0 2 0 0
2 2 2 0
```

>明显发现，它是重边。只需要在程序里加上一个小小的判断即可。

>具体实现在程序里面有。

## 3.判重坐标

>这一步其实不难，排一下序再判断有没有互不相同的$4$个点即可。

## 4.上代码

```cpp
#include<bits/stdc++.h>
#define inf ((1<<30)-1)
#define linf ((1<<62)ll-1)
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define Fn(i,a) for(register int i=las[a];i;i=nex[i])
int Fl,Pn,SI=100;char mch=' ',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
#define EXIT {cout<<"NO";return 0;}
int cntx,cnty,sx,sy,ex,ey,siz,cnt;
struct poin{int x,y;}a[9];
bool cmp(poin a,poin b)//自己编写的排序比较函数
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
int main()
{
	Fu(i,1,4)
	{
		in(sx,sy,ex,ey);//输入
		a[++siz]={sx,sy};
		a[++siz]={ex,ey};//等会加进a数组里，再排序
		if(sx!=ex&&sy!=ey)EXIT;
		if(sx==ex)cntx++;//判断重复的x有多少个
		if(sy==ey)cnty++;//判断重复的y有多少个
	}
	if(cntx!=2||cnty!=2)EXIT;//判断重边,正常时x,y均为2
	stable_sort(a+1,a+9,cmp);//排一下序
	Fu(i,1,8)if(a[i]!=a[i-1])cnt++;//判断不同的有几个
    if(cnt==4)cout<<"YES";
    else cout<<"NO";
	return 0;
}
```

---

