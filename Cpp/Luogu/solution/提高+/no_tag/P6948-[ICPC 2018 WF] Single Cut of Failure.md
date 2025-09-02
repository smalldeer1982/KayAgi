# [ICPC 2018 WF] Single Cut of Failure

## 题目描述

入侵与犯罪预防公司 (the Intrusion and Crime Prevection Company, 简称 ICPC) 为家庭和商业公司建立了入侵检测系统。国际大学生编程竞赛 (the International Collegiate Programming Contest, 碰巧也简称 ICPC) 正在考虑雇佣该公司来确保下一年 World Finals 的题目文件的储藏房间的安全。

比赛工作人员希望防止过去几年发生的入侵尝试，例如在大楼的外部垂直速降然后从窗户进入，从排气管道爬进来，冒充 Bill Poucher （译者注：某知名计算机科学教授，ACM-ICPC 的执行董事），以及创造性地使用攻击潜艇。正因如此，题目文件将被储藏在仅有一扇门而没有任何其他出入口的房间里。

ICPC （指公司）建议在门的四边安装传感器，每对传感器由电线连接。如果有人打开了门，任何连接的一对传感器将检测到这个动作并引起警报声。

然而这个系统存在一个设计缺陷。入侵者可以在开门之前剪断这些电线。为了评估这个系统的安全性，你需要使用最少的线段剪断所有电线。下图展示了两种具有不同电线分布的门（对应于两个样例）以及最少的与所有电线相交的线段。

![图](https://cdn.luogu.com.cn/upload/image_hosting/iat1ibs7.png)

## 样例 #1

### 输入

```
4 4 6
0 1 4 4
0 5 2 0
0 3 3 6
2 6 4 2
```

### 输出

```
1
0 4 4 3
```

## 样例 #2

### 输入

```
5 4 6
0 2 2 0
0 3 2 6
1 6 3 0
1 0 4 4
3 6 4 2
```

### 输出

```
2
0 4 4 4.5
0 1 4 1
```

# 题解

## 作者：LastKismet (赞：1)

发现古早写过这题，于是补一发题解。

# 思路

首先一个性质是两条对角线必然可行，所以只需要考虑特判一条线行不行即可。

那么这就是个经典问题：对于一条直线上的一些区间，希望你构造一个连续区间，使你构造的区间中包含给出所有区间的**一个**端点。

如何把原问题转化成这个经典问题呢？把这个框从一个顶点处断开然后展开成直线即可。类似于破环成链。

那么考虑双指针解决这个问题即可。实现细节见代码。

# 古早代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<double,double> pdd;
typedef pair<int,int> pii;

const int N=1e6+5;

int n;
int w,h;
int ans;

struct dot{
    int loc,id;
}ds[N*2];
int nums[N];

inline int get_loc(int x,int y){
    if(y==0)return x;
    if(x==w)return y+w;
    if(y==h)return w+h+w-x;
    if(x==0)return w+h+w+h-y;
}

inline pdd ret_loc(int x){
	if(x<=w)return {x-0.1,0};
	if(x<=h+w)return {w,x-w-0.1};
	if(x<=w+h+w)return {w-(x-w-h-0.1),h};
	if(x<=h+w+h+w)return {0,h-(x-w-h-w-0.1)};
}

inline void print(double a,double b,double c,double d){
    printf("%lf %lf %lf %lf\n",a,b,c,d);
}

inline void ed(){
    cout<<2<<endl;
    print(0,0.1,w,h-0.1);
    print(0,h-0.1,w,0.1);
}

bool cmp(dot a,dot b){
    return a.loc<b.loc;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>w>>h;
    for(int i=1;i<=n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        ds[i*2-1].id=i;
        ds[i*2-1].loc=get_loc(a,b);
        ds[i*2].id=i;
        ds[i*2].loc=get_loc(c,d);
    }
    sort(ds+1,ds+1+n*2,cmp);
    for(int i=1,j=1;i<=n*2;i++){
        nums[ds[i].id]++;
        if(nums[ds[i].id]==2){
        	double a=ds[j].loc,b=ds[i].loc;
        	pdd res1=ret_loc(a),res2=ret_loc(b);
            if(ans==n){
                cout<<1<<endl;
                print(res1.first,res1.second,res2.first,res2.second);
                return 0;
            }
        	while(nums[ds[i].id]==2){
	            nums[ds[j].id]--;
                ans--;
	            j++;
			}
        }
        ans++;
    }
    ed();
    return 0;
}
```

---

## 作者：Needna (赞：0)

本题解思路来源于  Aguin 和一位学长。

拿到本题我们发现两条对角线一定可以满足任意情况，所以只用考虑答案是否为 1 即可这里用一个奇妙的做法，我们把这个矩形从一个顶点断开并沿边缘展开，那么原本的线段就变成了若干个区间。我们发现两条线段有交等价于现在的两个区间有交且不包含。而且发现无论从那个顶点断开都不影响两条直线相交的判断。

于是我们只需要判断能够找到一个区间与所有区间都相交。这一步好像做法很多。一种是，相交的必要条件是 左端点在 右端点左边， 右端点在 左端点右边。那么找到所有区间右端点最小值和左端点最大值，作为找到的区间，再判断是否有包含即可。另一种是，我们只需要找到一个区间恰好包含所有的属于不同区间的端点，用双指针扫一遍也可以。
```cpp
#include <bits/stdc++.h>
namespace Fread { const int SIZE = (1 << 18); char buf[SIZE], * p1 = buf, * p2 = buf; inline char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SIZE, stdin), p1 == p2) ? EOF : *p1++); } }
namespace Fwrite { const int SIZE = (1 << 18); char buf[SIZE], * S = buf, * T = buf + SIZE; inline void flush() { fwrite(buf, 1, S - buf, stdout), S = buf; }  struct NTR { ~NTR() { flush(); } }ztr; inline void putchar(char c) { *S++ = c; if (S == T) flush(); } }
namespace Fastio {
	struct Reader { template <typename T> Reader& operator >> (T& x) { char c = Fread::getchar(); bool f = false; while (c < '0' or c > '9') { if (c == '-') f = true; c = Fread::getchar(); } x = 0; while (c >= '0' and c <= '9') { x = (x << 1) + (x << 3) + (c ^ 48); c = Fread::getchar(); } if (f) x = -x; return *this; }Reader& operator>>(char& c) { c = Fread::getchar(); while (c == '\n' || c == ' ' || c == '\r')c = Fread::getchar(); return *this; }Reader& operator>>(char* str) { int len = 0; char c = Fread::getchar(); while (c == '\n' || c == ' ' || c == '\r')c = Fread::getchar(); while (c != '\n' && c != ' ' && c != '\r')str[len++] = c, c = Fread::getchar(); str[len] = '\0'; return *this; }Reader() {} }cin;
	struct Writer { template <typename T> Writer& operator << (T   x) { if (x == 0) return Fwrite::putchar('0'), * this; if (x < 0) Fwrite::putchar('-'), x = -x; static int sta[45], top = 0; while (x)  sta[++top] = x % 10, x /= 10; while (top)  Fwrite::putchar(sta[top] + '0'), --top; return *this; } Writer& operator<<(char c) { Fwrite::putchar(c); return*this; }Writer& operator<<(const char* str) { int cur = 0; while (str[cur])Fwrite::putchar(str[cur++]); return *this; }Writer() {} }cout;
}
#define cin  Fastio :: cin
#define cout Fastio :: cout
using namespace std;
const int maxn = 1e6 + 10;
typedef pair<int, int> pii;
bool vis[maxn];
vector<pii> v;
int n, w, h;
inline int cal(int x, int y) {
     if(x == 0) return y;
    if(y == h) return h + x;
     if(x == w) return 2 * h + w - y;
     return 2 * (h + w) - x;
 }
 
inline void get(double t, double& x, double& y) {     
    if(t <= h) x = 0, y = t;
    else if(t <= h + w) x = t - h, y = h;
    else if(t <= 2 * h + w) x = w, y = 2 * h + w - t;
    else x = 2 * (h + w) - t, y = 0;
}
 
int main() {
    cin>>n>>w>>h;
    for(int i = 0; i < n; ++i) {         
	int X1, Y1, X2, Y2;
         cin>>X1>>Y1>>X2>>Y2;
         v.push_back(pii(cal(X1, Y1), i));
         v.push_back(pii(cal(X2, Y2), i));
    }
    sort(v.begin(), v.end());
    int sz = int(v.size()), p = 0, cnt = 0, one = 0;
    for(int i=0;i<sz;++i) {
         if(p == i)vis[v[i].second]=true,++p,++cnt;
       while(!vis[v[p].second])vis[v[p].second]=true,p=(p+1)%sz,++cnt;
        if(cnt == n) {
             double ax1, ay1, ax2, ay2;
             get(v[i].first - 0.5, ax1, ay1);
             get(v[p].first - 0.5, ax2, ay2);
             printf("1\n%.8f %.8f %.8f %.8f\n", ax1, ay1, ax2, ay2);
             one = 1; break;
         }
        vis[v[i].second] = false, --cnt;
     }
    if(!one) printf("2\n0.5 0 %.8f %.8f\n0 %.8f %.8f %.8f\n", w - 0.5, 1.0 * h, h - 0.5, 1.0 * w, 0.5);
     return 0;
 }
```

---

## 作者：Elma_ (赞：0)

好题啊。

首先有一个 key observation，因为所有给定电线都连接门的不同两边，所以切割门的两条对角线就一定能够切断所有电线，因此最多只需要切割两次。于是我们只需要判断是否能够只切割一次就切断所有电线。

接下来要干的事情可以称之为魔法...我们可以把门的四边沿着 x 轴展开形成一条线段，给出的电线就可以看成是这条线段上的区间，问题就转化成了能否在这条线段上找到一个区间使得这个区间中包含 $n$ 个属于不同电线的端点。直接 Two-Pointer 扫描一遍即可。

要注意输出方案时因为不能与四个角落以及任意电线断电重合，因此还要加上 / 减去一个偏离值，代码中是 $0.1$。还有要注意的就是给定的点到展开后的线段上的点的互相转化需要一个有点恶心（？）的讨论。

时间复杂度 $O(n \log n)$。

```cpp
#include <map>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
    int x, pos;
    bool operator < (const node p) const {
        return x < p.x;
    } 
} a[maxn << 1];
int n, w, h, vis[maxn];

inline int getPos(int x,int y){
	return !y ? x : x == w ? w + y : y == h ? (w << 1) + h - x : (w << 1) + (h << 1) - y;
}
inline void print(double x) {
    if (x < w) printf("%.1f %d ", x, 0);
    else if (x < w + h) printf("%d %.1f ", w, x - w);
    else if (x < (w << 1) + h) printf("%.1f %d ", (w << 1) + h - x, h);
    else printf("%d %.1f ", 0, (w << 1) + (h << 1) - x);
}

int main() {
    n = read(), w = read(), h = read();
    for (int i = 1, X1, X2, Y1, Y2;i <= n;i++) {
        X1 = read(), Y1 = read(), a[(i << 1) - 1] = (node){getPos(X1, Y1), i};
        X2 = read(), Y2 = read(), a[(i << 1)] = (node){getPos(X2, Y2), i};
    }
    a[(n << 1) + 1].x = (w << 1) + (h << 1);
    sort(a + 1, a + (n << 1) + 1);
    for (int head = 1, tail = 1;tail <= (n << 1);head++) {
        while (tail <= (n << 1) && !vis[a[tail].pos]) vis[a[tail].pos] = 1, tail++;
        if (tail - head == n) return puts("1"), print(a[head].x - 0.1), print(a[tail].x - 0.1), 0;
        vis[a[head].pos] = 0;
    }
    printf("2\n%.1f %d %.1f %d\n%d %.1f %d %.1f\n", 0.1, 0, w - 0.1, h, w, 0.1, 0, h - 0.1);
	return 0; 
}
```


---

