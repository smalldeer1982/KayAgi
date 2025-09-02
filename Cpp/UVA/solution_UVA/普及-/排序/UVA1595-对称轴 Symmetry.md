# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)

# 题解

## 作者：Viva_Hurricane (赞：11)

```
其实这题挺简单的，只是判断点是否对称而已。
对称轴一定是最左边和最右边点的中点所在竖线。
所以我们可以找最左边和最右边的点。
即横坐标最小和最大。
主要思想就是把点的横坐标排序，然后判断左边的第n个点和右边的第n个点是否关于对称轴对称。

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
struct point1{//用结构体会好写一点。
//为了把横坐标相等的点的纵坐标升序和降序排序（至于为什么大家自己思考一下，反正不排会错），用两个结构体。
	double x;
	double y;
};
point1 p1[1010];
struct point2{
	double x;
	double y;
};
point2 p2[1010];

bool cmp1(point1 l,point1 r){//当然也要两个比较函数。
	if(l.x==r.x)
		return l.y<r.y;
	else
		return l.x<r.x;
}
bool cmp2(point2 l,point2 r){
	if(l.x==r.x)
		return l.y>r.y;
	else
		return l.x<r.x;
}

int main(){
	cin>>n;
	for(int t=0;t<n;t++){//有n组数据。
		bool f=0;
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>p1[i].x>>p1[i].y;
			p2[i].x=p1[i].x;
			p2[i].y=p1[i].y;
		}
		sort(p1+1,p1+m+1,cmp1);
		sort(p2+1,p2+m+1,cmp2);
		double mid=(p1[1].x+p1[m].x)/2;
		int l=1,r=m;
		while(l<=r){//从两头开始判断。
			if(mid-p1[l].x!=p1[r].x-mid||p1[l].y!=p2[r].y){
				cout<<"NO"<<endl;
				f=1;
				break;
			}
			l++;
			r--;
		}
		if(f==0)
			cout<<"YES"<<endl;
	}
	return 0;
}
十分简单，给个入门难度。
```

---

## 作者：GVNDN (赞：3)

多谢大佬@metaphysis，没有他我这题绝对做不出来。

多个点关于一条平行于y轴的直线对称需要满足如下条件：
在（最左边的点, 最右边的点）、（倒数第二左的点, 倒数第二右的点）、（倒数第三左的点, 倒数第三右的点）……（最中间的两个点或一个点）的元组内部，两点的横坐标相等，且两点横坐标之和除以2与其他每个元组内的两点横坐标除以2相等。

即(x1 + x4) / 2 == (x2 + x3) / 2 && (y1 == y4 && y2 == y3)
![](https://cdn.luogu.com.cn/upload/image_hosting/cyserhrd.png)
故需先将横坐标排序（才能确定谁是最左边、最右边、倒数第二左、倒数第二右……的点）然后按刚才所说的条件判断即可。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>    //用于复制排序后的数组，然后再反着排一遍，易于比较
using namespace std;
const int maxn = 1010;

struct dot{
	double x;
	double y;
}d1[maxn], d2[maxn];

bool cmp1(dot a, dot b){
	if(a.x == b.x) return a.y < b.y;
	else return a.x < b.x;
}

bool cmp2(dot a, dot b){
	if(a.x == b.x) return a.y < b.y;
	else return a.x > b.x;
}

int main(){
	int n; 
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int m, f = 1, ok = 1;
		double cur_sym, sym;
		scanf("%d", &m);
		for(int j = 0; j < m; j++){
			scanf("%lf", &d1[j].x);
			scanf("%lf", &d1[j].y);
		}
		sort(d1, d1 + m, cmp1);    //将点以横坐标降序排列
		memcpy(d2, d1, sizeof(d2));
		sort(d2, d2 + m, cmp2);    //将点以横坐标升序排列
//		printf("d1\n");
//		for(int j = 0; j < m; j++){
//			printf("dot%d: x = %f; y = %f;\n", j, d1[j].x, d1[j].y);
//		}
//		printf("d2\n");
//		for(int j = 0; j < m; j++){
//			printf("dot%d: x = %f; y = %f;\n", j, d2[j].x, d2[j].y);
//		}
		for(int j = 0; j < m; j++){
			cur_sym = (d1[j].x + d2[j].x) / 2;    //计算各点当前的对称轴，用于与标准对称轴比较
//			printf("sym = %f\n", sym);
//			printf("cur_sym = %f\n", cur_sym); 
			if(f) {f = 0; sym = cur_sym; continue;}    //如果是第一组比较的点，先存储当前对称轴为标准对称轴
			if(cur_sym != sym || d1[j].y != d2[j].y) {ok = 0; break;}    //如果当前对称轴与标准对称轴不等，或是纵坐标的值不等，退出循环，ok为0
		}
		if(!ok) printf("NO\n");
		else printf("YES\n");
//		printf("\n");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

```
人生苦短，我写暴力

开两个结构体数组，
一个按照先x升序后y降序排
一个按照先x降序后y降序排
然后从0扫到(n/2+1)就好
判x之和是否相等和y坐标是否相等即可

因为很简单就直接贴代码啦
#include<cstdio>
#include<algorithm>

class Solver{//解题的类
public:
	struct Point{//点的结构体
		int x,y;
		
		Point(){}//无参构造函数
		
		Point(int x,int y){//构造函数
			this -> x = x;
			this -> y = y;
		}
	};
	
	static bool cmp1(Point a,Point b){//x升序后y降序排
		return a.x < b.x || (a.x == b.x && a.y > b.y);
	}
	static bool cmp2(Point a,Point b){//x降序后y降序排
		return a.x > b.x || (a.x == b.x && a.y > b.y);
	}
	
	void main(){
		const int L = 1000 + 6;
		
		Point p1[L],p2[L];
		
		int n;
		scanf("%d",&n);
		
		int d1,d2;
		for(int i = 0;i < n;i++){
			scanf("%d %d",&d1,&d2);
			
			p1[i].x = p2[i].x = d1;//输入
			p1[i].y = p2[i].y = d2;
		}
		
		std::sort(p1,p1 + n,cmp1);//sort
		std::sort(p2,p2 + n,cmp2);
		
		int axis = p1[0].x + p2[0].x;//求对称轴，这样排序后，两个数组第一个就是最左和最右的同y的点
		
		bool running = true;//开始判断
		for(int i = 0;i < n / 2 + 1;i++){
			if(p1[i].x + p2[i].x != axis || p1[i].y != p2[i].y){//如果不在对称轴上，或者两点y不等
				running = false;
				break;
			}
		}
		
		printf("%s\n",running ? "YES" : "NO");//输出
	}
};

int main(){
	int n;
	scanf("%d",&n);//总输入
	
	while(n--){
		(new Solver) -> main();
	}
	
	return 0;
}
```

---

## 作者：Wi_Fi (赞：1)

题意：大白话，不解释。

很显然，如果这些点要能找到一条对称轴，那么根据 $x$ 的值排序后，下标左右对称的每一组点，对称轴一定都是重合的，所以我们需要确定对称轴。

由于如果对称每组对称轴都是一样的，所以我们找一组最简单的，即第 $1$ 个和第 $n$ 个，对称轴为 $\frac{x_1+x_n}{2}$，我们令它为基准线。

然后我们再来判断 $y$ 的值。由于是对称，所以如果对称轴左侧的点在 $x$ 的值相同的情况下 $y$ 的值是递增的，那么对称轴右侧的点 $y$ 的值相同的情况下 $y$ 的值就是递减的。所以这时一个排序函数就不够了，我们写两个排序函数，分别对应上面的两种情况。

然后再依次判断每一组点的 $x$ 值的平均值是否与基准线的 $x$ 值相等，两个点的 $y$ 的值是否相等即可。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1005;
struct po
{
	double x,y;
}a[N],aa[N];
bool yf(po a,po b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
bool yl(po a,po b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y>b.y;
}
int i,n,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		sort(a+1,a+n+1,yf);
		for(i=1;i<=n;i++)aa[i].x=a[i].x,aa[i].y=a[i].y;
		sort(aa+1,aa+n+1,yl);
		double dx=(a[1].x+a[n].x)/2;
		int flag=1;
		for(i=1;i<=n;i++)
		{
			if((a[i].x+a[n-i+1].x)/2!=dx||a[i].y!=aa[n-i+1].y)
			{
				cout<<"NO\n";
				flag=0;
				break;
			}
		}
		if(flag==1)cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：STrAduts (赞：1)

不难看出如果有对称轴，则对称轴一定为 $x = k$，$k$ 为所有的点的横坐标的中位数。

那么我们就可以将对称轴先确定下来，遍历每个点，逆用中点公式 $x_{mid} \times 2 = x_1 + x_2$，算出该点关于对称轴对称点，然后判断是否存在于给定点中即可。

具体实现使用 `pair` 和 `map`。时间复杂度为：$O(n \log n)$

```cpp
#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define con(a, b) make_pair(a, b)
// 便于快速使用 pair。
using namespace std;

// 华丽的模板开头。
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }
int Abs(int x) { return x < 0 ? -x : x; }

int read() {
    int k = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char s) {
    write(x);
    putchar(s);
}
// 华丽的模板结尾。

const int MAXN = 1e3 + 5;

struct node {
	int x, y;
	node() {}
	node(int X, int Y) {
		x = X;
		y = Y;
	}
} q[MAXN];
// 存储点的信息的结构体。

int num[MAXN];
// 单独保存横坐标。

map<pair<int, int>, bool> vis;
// 记录该点是否存在。

int main() {
	int t = read();
	while(t--) {
		int n = read();
		for(int i = 1; i <= n; i++) {
			q[i].x = read(), q[i].y = read();
			vis[con(q[i].x, q[i].y)] = true;
			num[i] = q[i].x; // 保存横坐标。
		}
		sort(num + 1, num + n + 1); // 排序，便于计算中位数。
		int len = unique(num + 1, num + n + 1) - num - 1; // 去重。
		if(len & 1) { // 分奇偶性计算，但其实这里写复杂了。
			int t = num[(len + 1) / 2];
			bool flag = true;
			for(int i = 1; i <= n; i++)
				if(!vis[con((t << 1) - q[i].x, q[i].y)]) { // 判断是否存在。
					flag = false;
					break;
				}
			if(flag)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
		else { // 同理。
			int t = (num[len / 2] + num[len / 2 + 1]);
			bool flag = true;
			for(int i = 1; i <= n; i++)
				if(!vis[con(t - q[i].x, q[i].y)]) {
					flag = false;
					break;
				}
			if(flag)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;				
		}
		vis.clear();
	}
	return 0;
}
```

---

## 作者：liupei (赞：0)

## 题意
有 $kase$ 组数据。

每组第一行一个 $n$ 表示有 $n$ 个点。

接下来 $n$ 行输入这些点($x$ , $y$)。

要你判断每组点是否左右对称。

## 解析
先用 `vector` 存点，然后 `sort` 一下找到中心对称轴。

然后用 `map` 法来判断是否对称：具体而言，将对称轴左侧的点视为正标记，右侧的点视为负抵消，维护这样一个 $flag$ 在 `map` 中，最后看是否所有点能恰好完全抵消，是的话说明对称，否则不对称。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define mp make_pair
using namespace std;
int kase, n;
vector<pair<int, int> > node;
map<pair<int, int>, int> flag;

int main() {
    cin >> kase;
    while(kase --) {
        node.clear(), flag.clear();
        cin >> n;
        while(n --) {
            int x, y;
            cin >> x >> y;
            node.push_back(mp(x, y));
        }
        sort(node.begin(), node.end());
        int d_mid;
        if(node.size() % 2) d_mid = node[node.size() / 2].first * 2;
        else d_mid = (node[node.size() / 2 - 1].first + node[node.size() / 2].first);
        for(auto p : node) {
            if(p.first * 2 < d_mid) flag[p] ++;
            else if(p.first * 2 > d_mid) {
                flag[mp(d_mid - p.first, p.second)] --;
            }
        }
        bool ok = 1;
        for(auto p : flag) if(p.second != 0) {
            ok = 0;
            break;
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
}
```

---

