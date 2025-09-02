# Bus

## 题目描述

There is a bus stop near the university. The lessons are over, and $ n $ students come to the stop. The $ i $ -th student will appear at the bus stop at time $ t_{i} $ (all $ t_{i} $ 's are distinct).

We shall assume that the stop is located on the coordinate axis $ Ox $ , at point $ x=0 $ , and the bus goes along the ray $ Ox $ , that is, towards the positive direction of the coordinate axis, and back. The $ i $ -th student needs to get to the point with coordinate $ x_{i} $ ( $ x_{i}&gt;0 $ ).

The bus moves by the following algorithm. Initially it is at point 0. The students consistently come to the stop and get on it. The bus has a seating capacity which is equal to $ m $ passengers. At the moment when $ m $ students get on the bus, it starts moving in the positive direction of the coordinate axis. Also it starts moving when the last ( $ n $ -th) student gets on the bus. The bus is moving at a speed of 1 unit of distance per 1 unit of time, i.e. it covers distance $ y $ in time $ y $ .

Every time the bus passes the point at which at least one student needs to get off, it stops and these students get off the bus. The students need $ 1+[k/2] $ units of time to get off the bus, where $ k $ is the number of students who leave at this point. Expression $ [k/2] $ denotes rounded down $ k/2 $ . As soon as the last student leaves the bus, the bus turns around and goes back to the point $ x=0 $ . It doesn't make any stops until it reaches the point. At the given point the bus fills with students once more, and everything is repeated.

If students come to the stop when there's no bus, they form a line (queue) and get on the bus in the order in which they came. Any number of students get on the bus in negligible time, you should assume that it doesn't take any time. Any other actions also take no time. The bus has no other passengers apart from the students.

Write a program that will determine for each student the time when he got off the bus. The moment a student got off the bus is the moment the bus stopped at the student's destination stop (despite the fact that the group of students need some time to get off).

## 说明/提示

In the first sample the bus waits for the first student for $ 3 $ units of time and drives him to his destination in additional $ 5 $ units of time. So the student leaves the bus at the moment of time $ 3+5=8 $ .

In the second sample the capacity of the bus equals $ 1 $ , that's why it will drive the first student alone. This student is the same as the student from the first sample. So the bus arrives to his destination at the moment of time $ 8 $ , spends $ 1+[1/2]=1 $ units of time on getting him off, and returns back to $ 0 $ in additional $ 5 $ units of time. That is, the bus returns to the bus stop at the moment of time $ 14 $ . By this moment the second student has already came to the bus stop. So he immediately gets in the bus, and is driven to his destination in additional $ 5 $ units of time. He gets there at the moment $ 14+5=19 $ .

In the third sample the bus waits for the fourth student for $ 6 $ units of time, then drives for $ 5 $ units of time, then gets the passengers off for $ 1+[4/2]=3 $ units of time, then returns for $ 5 $ units of time, and then drives the fifth student for $ 1 $ unit of time.

## 样例 #1

### 输入

```
1 10
3 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2 1
3 5
4 5
```

### 输出

```
8 19
```

## 样例 #3

### 输入

```
5 4
3 5
4 5
5 5
6 5
7 1
```

### 输出

```
11 11 11 11 20
```

## 样例 #4

### 输入

```
20 4
28 13
31 13
35 6
36 4
52 6
53 4
83 2
84 4
87 1
93 6
108 4
113 6
116 1
125 2
130 2
136 13
162 2
166 4
184 1
192 2
```

### 输出

```
51 51 43 40 93 89 86 89 114 121 118 121 137 139 139 152 195 199 193 195
```

# 题解

## 作者：zhangyaiwei (赞：2)

## sol
纯模拟就好了

每来一个学生，就丢进小根堆里（按位置排序），如果满了 $m$ 个或到了末尾，就把学生按位置一组一组取出来，计算时间然后累加。然后也需要注意的好像也没什么了。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define f first
#define s second
#define mk make_pair
using namespace std;
priority_queue<pair<int,int> > q;
int n,m,t,x,NOWT,ts[111111];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>t>>x;
		q.push(mk(-x,i));
		if(q.size()==m||i==n){
			int nowx=0,nowt=max(NOWT,t);
			while(!q.empty()){
				nowt+=nowx-q.top().f;
				nowx=q.top().f;
				int top=q.top().f;
				vector<int> v;
				while(!q.empty()&&q.top().f==top) v.push_back(q.top().s),q.pop();
				for(int j=0;j<v.size();j++){
					ts[v[j]]=nowt;
				}
				nowt+=1+v.size()/2;
			}
			NOWT=max(NOWT,nowt-nowx);
		}
	}
	for(int i=1;i<=n;i++) cout<<ts[i]<<" ";
}
```

---

## 作者：zrzluck99 (赞：1)

其实就是一道比较恶心的纯模拟题。。

由于只要车上有 $m$ 个人或者第 $n$ 个人上车，所以我们可以分成每 $m$ 个人一块处理。

块内每次将人按目的地排序，统计每站下车人的个数，记录每个人下车时间，最后排序输出就好了。

具体实现见代码：

----

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f

template<class T> T Max(const T &x,const T &y){
    return x>y?x:y;
}

template<class T> T Min(const T &x,const T &y){
    return x<y?x:y;
}

inline ll read(){
    ll s=0,w=1; char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') w=-1; ch=getchar();}
    while (ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^'0'), ch=getchar();
    return s*w;
}

void write(ll s){
    if (s<0) putchar('-'), s=-s;
    if (s>9) write(s/10);
    putchar(s%10+'0');
}

void writeln(ll s){
    write(s); putchar('\n');
}

void writeln(){
    putchar('\n');
}

/* --- 以下正文 --- */

struct Person{ //记录每个人的信息
    ll arr,dest,ind,tm;
}p[1926817];

bool cmp(Person A,Person B){
    return A.dest<B.dest;
}

bool cmp2(Person A,Person B){
    return A.ind<B.ind;
}

ll a[1926817],b[1926817],tag[1926817],l[1926817],r[1926817],f[1926817];
ll n,m;

ll TIME = 0; //时间戳

int main(){
    ios::sync_with_stdio(false);
    n = read(); m = read();
    for (int i=0;i<n;i++){
        a[i] = read(), b[i] = read(); tag[i] = i/m;
        if (i%m==0) l[i/m] = i; if ((i+1)%m==0||i+1==n) r[i/m] = i;
    }
    const ll t = (n-1)/m;
    //读入+分块
    for (int i=0;i<=t;i++) f[i] = a[r[i]]; //记录每块第m个人到达时间
    for (int i=0;i<n;i++) p[i] = (Person){a[i],b[i],i,0}; //初始化
    for (int i=0;i<=t;i++) sort(p+l[i],p+r[i]+1,cmp); //块内排序
    for (int i=0;i<=t;i++){
        ll now = 0, cnt = 0;
        TIME = Max(TIME,f[i]); //注意：发车时间是公交车回来的时间和块内第m个人到达时间中的较大值
        for (int j=l[i];j<=r[i];j++){
            if (p[j].dest!=now){
                if (cnt) TIME += 1+cnt/2; TIME += p[j].dest-now;
                now = p[j].dest; cnt = 1;
            }else{
                cnt++;
            } //逐个处理每个人的状态，注意边界
            p[j].tm = TIME; //求出每个人下车时间
        }
        TIME += 1+cnt/2; TIME += p[r[i]].dest;
    }
    sort(p,p+n,cmp2);
    for (int i=0;i<n;i++) write(p[i].tm),putchar(' '); writeln();
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

这道题就是纯模拟题。

每次按照公交车拉人的顺序，选 $m$ 个人。一共会选 $\frac{m}{n}$ 次。为了使我们方便操作，每次我们就按照每块内的 $x$ 值排序，每次从 $x$ 最小的开始，向后扫，遇到相同的就全加上，用 $ans_i$ 表示第 $i$ 个人的下车时间。

但是记得输出答案的时候再按照原有的顺序 $\texttt{sort}$ 回去就行。每一次处理块的复杂度是 $O(m \log m)$，一共处理大约 $\frac{m}{n}$ 次。时间复杂度摊下来大约是 $O(n \log n)$，可以轻松通过。~~这么说来，这题很弱诶~~！

其他的就看代码能力了。

## 代码

代码的话其实就是用分块的思想，难度并不大。

```cpp
#include <bits/stdc++.h>
#define tem template
#define tpe typename
#define con const
#define ope operator
using namespace std;
tem<tpe T> inline void read(T &w)
{
	w=0;bool f=1;char ch=getchar();
	for(;ch<48 || ch>57;ch=getchar()) if(ch=='-')f=-1;
	for(;ch>47 && ch<58;ch=getchar()) w=(w<<1)+(w<<3)+(ch^48);
	w=f?w:-w;
}
tem<tpe T,tpe ...Arg> inline void read(T &w,Arg &...arg)
{
	read(w); read(arg...);
}
// （以上为快读，可以忽略）

struct Node
{
	int t,x,id;
}a[100005]; // t 和 x 的意思如题；id 是为了后面传递给 ans 数组。
struct N
{
	int x,id;
}ans[100005]; // x 记录的是离开时间，id 是为了最后输出方便排序。

inline bool cmp1(con Node &x,con Node &y){return x.x<y.x;} // 按照 x 排序
inline bool cmp2(con N &x,con N &y){return x.id<y.id;} // 按照初始顺序排序
int main()
{
	int n,m; read(n,m);
	for(int i=1;i<=n;i++)
		read(a[i].t,a[i].x),a[i].id=i;
   
	int p=ceil(n/double(m)),t=0; // 块数记得向上取整
	for(int i=1;i<=p;i++)
	{
		int st=(i-1)*m+1,en=min(i*m,n); // 因为最后一个块可能会超出 n 所以取 min
		t=max(t,a[en].t); // 公交车必须等最后一个人到了才能出发
		
		sort(a+st,a+en+1,cmp1); // 块内排序
		int lst=0,cnt=1;
		for(int j=st;j<=en;j++)
		{
			t+=(a[j].x-lst); // 公交车从上个位置移动到当前位置耗费的时间
			lst=a[j].x; // 记录上一个和 a[j] 位置不一样的坐标。
			ans[j].x=t; ans[j].id=a[j].id;
			while(j<en && a[j].x==a[j+1].x)
				j++,ans[j].x=t,ans[j].id=a[j].id,cnt++; // 相同位置下车的一起统计了
			t+=1+(cnt>>1);// 下车所用时间
 			cnt=1; // 重置 cnt，为下一次做准备
		}
		t+=a[en].x; // 从最后一个人下车的位置回到 0 点
	}
	sort(ans+1,ans+1+n,cmp2); // 得按照输入的顺序重排
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

$$ \large\text{----------- The end -----------}$$

$$ \text{thx for reading.}$$


完结撒花~ qwq

---

