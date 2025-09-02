# [NWRRC 2016] King’s Heir

## 题目描述

国王去世了，国王万岁！在国王 Fert XIII 突然去世后，平面王国的人民将迎接新国王。不幸的是，出现了一个问题，Fert 有太多的儿子。

实际上，他有 $n$ 个儿子，并且他对每个新儿子的爱都超过了他之前所有的儿子。可能是因为他们的坏行为，他不再爱他的儿子们。无论如何，在新儿子出生后，Fert 制定了新的遗嘱，宣布新出生的儿子将成为继承人。

然而，问题在于，只有在国王去世时年满 $18$ 岁的国王儿子才能成为新国王。现在，政府的部长们正在努力寻找正确的新国王，但他们似乎失败了。请帮助他们！

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
22 10 2016
7
28 2 1999
22 7 1995
21 10 1998
23 10 1998
3 9 2000
1 4 2013
17 12 2004
```

### 输出

```
3
```

## 样例 #2

### 输入

```
22 10 2016
1
28 2 1999
```

### 输出

```
-1
```

# 题解

## 作者：rui_er (赞：5)

最近 kkk 传了好多题啊，然后就随便挑了一个（也就是目前编号最大的）来做，拿到了首 A ~~（虽然好像没啥用~~ 。

---

题意：国王有 $n$ 个儿子，他想要把王位传给年龄**超过 $18$ 岁的中最小的**儿子。题目保证不存在两个儿子在同一天出生。假设所有年份的 $2$ 月均为 $28$ 天。

考虑先根据生日将所有儿子排序，然后枚举并计算与国王生日的差即可。排序时可以写比较函数，根据年、月、日三个关键字排序。那么怎么计算两个日期之间的间隔呢？

分两种情况：在同一年或不在同一年。

对于在同一年的，我们枚举两个月之间的完整月，将结果加上该月的天数，再通过简单推导计算出两侧零散月的天数即可。

对于不在同一年的，枚举中间年份加上 $365$，然后枚举两侧零散年按照上面类似方法计算即可。

我写的比较暴力，但也很容易理解，因为数据很小就没卡这里的常数。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int N = 105, mx = 18 * 365;
const int month[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int n;
struct Node {
	int d, m, y, id;
	Node(int a=0, int b=0, int c=0, int d=0) : d(a), m(b), y(c), id(d) {}
	~Node() {}
	void read() {scanf("%d%d%d", &this->d, &this->m, &this->y);}
	friend bool operator < (const Node &a, const Node &b) {
		if(a.y != b.y) return a.y < b.y;
		if(a.m != b.m) return a.m < b.m;
		return a.d < b.d;
	}
}king, son[N];

int calc(const Node &a, const Node &b) {
	int res = 0;
	if(a.y == b.y) {
		if(a.m == b.m) return b.d - a.d + 1;
		for(int i=a.m+1;i<b.m;i++) res += month[i];
		res += month[a.m] - a.d + 1 + b.d;
		return res;
	}
	for(int i=a.y+1;i<b.y;i++) res += 365;
	for(int i=a.m+1;i<=12;i++) res += month[i];
	for(int i=1;i<b.m;i++) res += month[i];
	res += month[a.m] - a.d + 1 + b.d;
	return res;
}

int main() {
	king.read();
	scanf("%d", &n);
	for(int i=1;i<=n;i++) son[i].read(), son[i].id = i;
	sort(son+1, son+1+n);
	for(int i=n;i;i--) if(calc(son[i], king) > mx) return printf("%d\n", son[i].id), 0;
	puts("-1");
	return 0;
}
```

---

## 作者：血色黄昏 (赞：1)

简单模拟题，只要将岁数从小到大排序，找出第一个满18的就好了

我用的是$O(nlogn)$的写法，因为个人感觉写起来会简便一点?(后来发现可能没有?本题O(n)做法也很简单，一个一个判断就行了，但由于数据小，我的$O(nlogn)$代码开$O2$竟然跑了目前的最优解/fad

解释在程序里了，自行观看

```
#include<bits/stdc++.h>
using namespace std;
int b, c, d, n;//b,c,d存日，月，年 
struct life{//结构体存出生日期 
	int d, m, y, tag;
}a[100010];
bool cmp(life a, life b)//比较函数，将出生最晚的放在最前面 
{
	if(a.y > b.y)return true;
	if(a.y == b.y)
	{
		if(a.m > b.m)return true;
		if(a.m == b.m)
		{
			if(a.d > b.d)return true;
		}
	}
	return false;
}
int main()
{
	cin>>b>>c>>d;
	cin>>n;//输入 
	for(int i = 0;i < n;i ++)cin>>a[i].d>>a[i].m>>a[i].y,a[i].tag = (i + 1);//tag从1开始 
	sort(a, a+n, cmp);//排序 
	for(int i = 0;i < n;i ++)
	{
		if(d-a[i].y > 18)//判断，如果18岁以上就输出 
		{
			cout<<a[i].tag<<endl;
			return 0;
		}
		else if(d-a[i].y==18 and a[i].m < c)
		{
			cout<<a[i].tag<<endl;
			return 0;
		}
		else if(d-a[i].y==18 and a[i].m == c and a[i].d <= b)
		{
			cout<<a[i].tag<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;//都没18输出-1 
	return 0;
}
```

祝大家CSP rp++

---

## 作者：ZBAA_MKC (赞：0)

这题不难，但细节很多。

#### 思路分析

输入后按出生日期从晚到早排序，排序完后和老国王去世的时间比较，如果满 $18$ 周岁就输出，否则就继续。如果一直到最后都没找到，就输出 $-1$。

代码时间复杂度：$O(n^2)$


#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int y[105], m[105], d[105], id[105];
int main()
{
    int yy, mm, dd;
    cin >> dd >> mm >> yy;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) //输入
    {
    	cin >> d[i] >> m[i] >> y[i];
    	id[i] = i + 1;
	}
	for (int i = 1; i < n; i++) //冒泡排序
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (y[j] < y[j + 1])
			{
				swap(y[j], y[j + 1]);
				swap(m[j], m[j + 1]);
				swap(d[j], d[j + 1]);
				swap(id[j], id[j + 1]);
			}
			else if (y[j] == y[j + 1])
			{
				if (m[j] < m[j + 1])
				{
					swap(y[j], y[j + 1]);
					swap(m[j], m[j + 1]);
					swap(d[j], d[j + 1]);
					swap(id[j], id[j + 1]);
				}
				else if (m[j] == m[j + 1])
				{
					if (d[j] < d[j + 1])
					{	
						swap(y[j], y[j + 1]);
						swap(m[j], m[j + 1]);
						swap(d[j], d[j + 1]);
						swap(id[j], id[j + 1]);
					}
				}	
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (yy - y[i] == 18) //判断并输出
		{
			if (m[i] < mm)
			{
				cout << id[i];
				return 0;
			}
			else if (m[i] == mm)
			{
				if (d[i] <= dd)
				{
					cout << id[i];
					return 0;
				}
			}
		}
		else if (yy - y[i] > 18)
		{
			cout << id[i];
			return 0;
		}
	}
	cout << -1;
	return 0;
}
```


---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/P7041)

## Analysis
按年龄从大到小排序，然后按顺序找一遍，发现满足条件直接输出

## Code
```cpp
#include<map>
#include<ctime>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define M 500010
#define int long long
inline int Readint(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;
}
struct Node{
	int year,month,day,idx;
	bool operator<(const Node &x)const{
		if(year==x.year){
			if(month==x.month)
				return day>x.day;
			return month>x.month;
		}
		return year>x.year;
	}
}son[M];
int day,month,year,n;
signed main(void){
	day=Readint();month=Readint();year=Readint();
	n=Readint();
	for(int i=1;i<=n;i++){
		cin>>son[i].day>>son[i].month>>son[i].year;
		son[i].idx=i;
	}
	sort(son+1,son+1+n);
	for(int i=1;i<=n;i++){
		if(year-son[i].year>18){
			cout<<son[i].idx;
			return 0;
		}
		if(year-son[i].year==18){
			if(month>son[i].month){
				cout<<son[i].idx;
				return 0;
			}
			else if(month==son[i].month&&day>=son[i].day){
				cout<<son[i].idx;
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}

```


---

## 作者：Doubeecat (赞：0)

> K.King's Heir
> 在国王去世的那一天，国王会让年龄最小但已满十八周岁的儿子继承国王，求哪一个儿子继承了国王，若没有儿子满足条件，则输出-1。保证国王不会有双胞胎。
> $n \leq 100$

签到题，~~场上看到number第一反应就是有几个人导致挂了两发~~

直接扫一遍，这里用了一个比较巧妙的处理方法，注意到每个人的出生日期实际上是可以转化为 `yyyy/mm/dd` 的形式，我们可以用一个类似 `hash` 的办法把每个日期都化成一个整数，先判断是否满足条件，满足条件直接取最大值（出生日期最晚年龄最小）即可。

```cpp
int n;

int a[N],b[N],c[N],x,y,z,ans,tmp;

signed main() {
    read(x,y,z,n);
    for (int i = 1;i <= n;++i) {
        read(a[i],b[i],c[i]);
        if (z - c[i] > 18) {
            int now = c[i] * 10000 + b[i] * 100 + a[i];
            if (now > tmp) {
                tmp = now,ans = i;
            }
        }
        else if (z - c[i] == 18) {
            if (b[i] < y) {   
                int now = c[i] * 10000 + b[i] * 100 + a[i];
                if (now > tmp) {
                    tmp = now,ans = i;
                }
            }
            else if (b[i] == y) {
                if (a[i] <= x) {        
                    int now = c[i] * 10000 + b[i] * 100 + a[i];
                    if (now > tmp) {
                        tmp = now,ans = i;
                    }
                }
            }
        }
    }
    if (ans) cout << ans;
    else cout << -1;
	return 0;
}
```


---

## 作者：ztjp13 (赞：0)

不得不说，ACM的题水起来是真的水，这题同样如此/

其实这题只要把几个儿子年龄从小到大排序，找第一个符合要求的就行了

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int dday,dmonth,dyear//老王的死亡年月日,n;
struct node{
	int day,month,year,th;//儿子出生的年月日及顺序
}q[1000005];
//空行，好码风
bool cmp(node a,node b){
	if(b.year<a.year) return true;
	if(b.year==a.year){
		if(b.month<a.month) return true;
		if(b.month==a.month)
			if(b.day<a.day) return true;
	}
	return false;
}//基于三个参数的比较

int main(){
	cin>>dday>>dmonth>>dyear;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>q[i].day>>q[i].month>>q[i].year;
		q[i].th=i+1;
	}
	sort(q,q+n,cmp);//排序
	for(int i=0;i<n;i++){
		if(dyear-q[i].year>18){
			cout<<q[i].th<<endl;
			return 0;
		}
		else if(dyear-q[i].year==18&&q[i].month<dmonth){
			cout<<q[i].th<<endl;
			return 0;
		}
		else if(dyear-q[i].year==18&&q[i].month==dmonth&&q[i].day<dday){
			cout<<q[i].th<<endl;
			return 0;//找到直接退出
		}
	}
	cout<<-1<<endl;//不行输出-1
	return 0;
} 

```


---

## 作者：Eason_AC (赞：0)

## Content
给出现在的日期，请从 $n$ 个人当中选出一个人，使得他是所有成年人（$\geqslant 18$ 岁的人）中年龄最小的。 

**数据范围：设日期为 $yy/mm/dd$，则有 $1\leqslant n\leqslant 100,1\leqslant yy\leqslant 9999,1\leqslant mm\leqslant 12,1\leqslant yy\leqslant 31$。**
## Solution
我们可以先把所有年龄小于 18 岁的人在输入的时候就把他给剔除掉，然后在按照出生日期从晚到早排序，最后直接输出第一个人的编号就好了。

注意特判一下没有符合条件的人时的情况。 
## Code
```cpp
int y, m, d, n, cnt;
struct son {
	int ye, mo, da, id;
	bool operator < (const son& cz) {
		if(ye != cz.ye) return ye > cz.ye;
		if(mo != cz.mo) return mo > cz.mo;
		return da > cz.da;
	}
}a[107];

int main() {
	d = Rint, m = Rint, y = Rint, n = Rint;
	F(i, 1, n) {
		a[++cnt].da = Rint, a[cnt].mo = Rint, a[cnt].ye = Rint, a[cnt].id = i;
		if(a[cnt].ye + 18 > y) a[cnt--] = (son){0, 0, 0, 0};
		else if(a[cnt].ye + 18 == y) {
			if(a[cnt].mo > m) a[cnt--] = (son){0, 0, 0, 0};
			else if(a[cnt].mo == m) {
				if(a[cnt].da > d) a[cnt--] = (son){0, 0, 0, 0};
			}
		}
	}
	if(!cnt) return printf("-1"), 0;
	sort(a + 1, a + cnt + 1);
	printf("%d", a[1].id);
	return 0;
}
```

---

## 作者：Alarm5854 (赞：0)

这道题目求的是年龄最小但又满十八周岁的儿子的编号，可以假设在国王去世的那一天的十八年前出生了一个虚拟儿子（不会被选），然后直接模拟，如果年龄大于等于虚拟儿子的年龄且比目前选中的儿子年龄小的话，就选现在的儿子。
```cpp
#include<cstdio>
using namespace std;
const int N = 100 + 7;
int n, d, m, y, ans, sd[N], sm[N], sy[N];
int isolder(int u, int v) {//比较年龄大小
	if (sy[u] < sy[v]) return 1;
	if (sy[u] > sy[v]) return 0;
	if (sm[u] < sm[v]) return 1;
	if (sm[u] > sm[v]) return 0;
	return sd[u] <= sd[v];
}
int main() {
	scanf("%d%d%d%d", &d, &m, &y, &n), sd[0] = d, sm[0] = m, sy[0] = y - 18, ans = -1;//虚拟儿子的编号为0，便于之后比较
	for (int i = 1; i <= n; ++i) scanf("%d%d%d", sd + i, sm + i, sy + i);
	for (int i = 1; i <= n; ++i)
	if (isolder(i, 0) && (!~ans || isolder(ans, i))) ans = i;
	return 0 & printf("%d", ans);
}
```

---

