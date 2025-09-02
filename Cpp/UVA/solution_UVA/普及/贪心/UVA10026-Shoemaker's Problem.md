# Shoemaker's Problem

## 题目描述

有 $n$ 个任务，每个任务从接手开始每分钟罚款 $S_i$ 元，直到完成任务为止。然而每个任务需要花 $T_i$ 的时间去完成。你只能把一件任务完成才能去做下一件事情，问如何安排任务处理顺序，使得总罚款最小。注意，每个任务在第 $0$ 时刻就全部交给了你。

## 样例 #1

### 输入

```
1
4
3 4
1 1000
2 2
5 5```

### 输出

```
2 1 3 4```

# 题解

## 作者：Otue (赞：2)

## 大致题意
有 $n$ 个任务，每个任务从接手开始每分钟罚款 $S_i$ 元，直到完成任务为止。然而每个任务需要花 $T_i$ 的时间去完成。问如何安排任务处理顺序，使得总罚款最小。注意，每个任务在第 $0$ 时刻就全部交给了你。
## 大致思路
使用贪心的邻项交换法可以快速解决此题。

设有两个任务编号为 $x,y$，那么如何安排顺序呢？

设之前任务处理时间为 $res$，那么先做 $x$ 再做 $y$ 的代价是：$res\times S_x+(res+T_x)\times S_y$。

同理，先做 $y$ 再做 $x$ 的代价为：$res\times S_y+(res+T_y)\times S_x$。

约掉同类项剩下 $T_y\times S_x$ 和 $T_x\times S_y$，于是按照这个顺序排序即可。
## 代码
```c++
#include <bits/stdc++.H>
using namespace std;

#define int long long
const int N = 2e4 + 5;
int t, n, l;

struct stu {
	int x, y, id;
}ed[N];

bool cmp(stu x, stu y) {
	if (x.x * y.y == x.y * y.x) return x.id < y.id;  // 排序
	return x.x * y.y < x.y * y.x;
}

signed main() {
	cin >> t;
	int g = t;
	while (t--) {
		l++;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> ed[i].x >> ed[i].y, ed[i].id = i;
		sort(ed + 1, ed + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			if (i == n) cout << ed[i].id;
			else cout << ed[i].id << ' ';   // 注意输出
		}
		if (l == g) puts("");  // 警告
		else puts(""), puts("");
	}
}
```

---

## 作者：saixingzhe (赞：1)

# 分析
我们发现，如果有两个任务 $a$ 和 $b$，此前经过了 $n$ 分钟，先做 $a$ 的罚款是 $n \times S_a+(n+T_a) \times S_b$，先做 $b$ 的罚款是 $n \times S_b+(n+T_b) \times S_a$，约掉同类项就变成了 $T_b \times S_a$ 和 $T_a \times S_b$，按照这个排序即可。

题外话：这题坑死了，文末不能有回车，句末不能有空格。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
struct Node{
	int t,s,id;
}a[10001];
bool cmp(Node a,Node b){
	return a.s*b.t==a.t*b.s?a.id<b.id:a.s*b.t>a.t*b.s;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d%d",&a[i].t,&a[i].s),a[i].id=i;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<n;i++) printf("%d ",a[i].id);
		printf("%d",a[n].id);
		if(T)	printf("\n\n");
		else printf("\n");
	}
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：0)

#这题的算法——贪心

首先我们要知道应该如何排序使得利益最大化。

```cpp
bool cmp(task x,task y) {
	return x.t*y.s==x.s*y.t?x.number<y.number:x.t*y.s<x.s*y.t;
}
```
代码如上，$T$ 为现在总时间，有两个任务，$x$ 与 $y$ 先做 $x$ 我们的代价为 。

$$T\times S_x+(T+T_x)\times S_y$$

而先做 $y$，则是。

$$T\times S_y+(T+T_y)\times S_x$$

将两式子化简一下就得到。

$T_y\times S_x$ 与 $T_x\times S_ y$ 比较。

现在我们只需要排序一下就可以出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct task{
    int t,s,number;
}a[1010];
bool cmp(task x,task y) {
	return x.t*y.s==x.s*y.t?x.number<y.number:x.t*y.s<x.s*y.t;
}
int read() {
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}//建议与下面快写一直放在自己代码里会快很多哦。
void write(int x) {
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
int main(){
    int T,n;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            a[i].t=read();
            a[i].s=read();
            a[i].number=i;
        }
        for(int i=1;i<n;i++){
            for(int j=1;j<n;j++){
                if(cmp(a[j+1],a[j]))swap(a[j],a[j+1]);//本人在推荐在没学快排前不要用 sort，老老实实冒泡。
            }
        }
        for(int i=1;i<=n;i++)
            write(a[i].number),putchar(' ');
        if(T==1)putchar('\n');
        else putchar('\n'),putchar('\n');//必须这样才可以过
    }
}
```


---

## 作者：yyyh_h (赞：0)

# 思路
令 $T_0$ 表示为前面处理任务所用的时间。

如果现有两个任务编号分别为 $a$ 和 $b$ ，那么先完成 $a$ 再完成 $b$ 所需的代价为：
$$
T_0×S_a+(T_0+T_a)×S_b
$$
同理，先完成 $b$ 再完成 $a$ 所需的代价为：
$$
T_0×S_b+(T_0+T_b)×S_a
$$
约掉同类项后，我们只需要按照 $T_b×S_a$ 和 $T_a×S_b$ 的大小作为依据来进行快排就可以了。
# 代码
```cpp
#include<bits/stdc++.h>//万能头，基本包含C++的所有常用库
using namespace std;
struct node
{
	int x,y,f;
}a[10001];//结构体
int T,q,l;
bool cmp(node a,node b)
{
	return a.y*b.x>a.x*b.y;
}//sort排序的依据
int main()
{
	scanf("%d",&T);//读入数据，下同
	l=T;
	while(T--)//循环T次
	{
		q++;
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].x);
			scanf("%d",&a[i].y);
			a[i].f=i;//对原先的序号做标记，方便后面的输出
		}
		sort(a+1,a+n+1,cmp);//对数组进行排序
		for(int i=1;i<=n;i++)
		{
			printf("%d",a[i].f);
			if(i<n)
			{
				printf(" ");
			}//当i==n时就不需要空格了
		}
		if(q==l) 
		{
			puts("");
		}
		else 
		{
			puts("");
			puts("");
		}//这一段十分重要，没有就无法AC
	} 
	return 0;//完结撒花
}
```

---

## 作者：4帅气的牛仔4 (赞：0)

~~# 本题貌似没有题解，我来水一波~~
# 正文
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX 1005
using namespace std;
struct node
{
    int a1;
    int a2;
    int a3;
}a[MAX];
bool cmp(node x,node y)
{
    return x.a1*y.a2>y.a1*x.a2;
}
int main()
{
    int t,n,i;
    scanf("%d",&t);
    while(t--)
    {
        cin>>n;
        for(i=0;i<n;i++)
        {
            cin>>a[i].a2>>a[i].a1;
            a[i].a3=i+1;
        }
        sort(a,a+n,cmp); 
        for(i=0;i<n;i++)
        printf("%d%s",a[i].a3,i==n-1?t?"\n\n":"\n":" ");
    }
    return 0;
}
```
~~好吧，我懒得写注释了，就这样吧！~~
###### ps：本题还没有题解呢，求管理大大给过，虽然有点简陋。

---

