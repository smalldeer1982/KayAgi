# Piotr's Ants

## 题目描述

一根长度为$L$厘米的木棍上有$n$只蚂蚁，每只蚂蚁要么向左爬，要么向右爬，速度为$1$厘米/秒。当两只蚂蚁相遇时，它们同时掉头（时间忽略不计）。给出每只蚂蚁的初始位置和朝向，请计算$T$秒后每只蚂蚁的位置。

　

## 样例 #1

### 输入

```
2
10 1 4
1 R
5 R
3 L
10 R
10 2 3
4 R
5 L
8 R```

### 输出

```
Case #1:
2 Turning
6 R
2 Turning
Fell off

Case #2:
3 L
6 R
10 R```

# 题解

## 作者：Suiseiseki (赞：10)

这一题我们可以分析得知：
- 蚂蚁掉头和互换编号一样
- 蚂蚁前后的相对位置不改变

相对位置不改变，我们就可以想到排序后计算，优化了很多。

实际上就是排序计算后再还回去，但是细节很多，这里也不必赘述，具体就看代码吧。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct P{
	int id;
	long long x;
	int fx;
	bool turn;
}a[10005],now[10005];//a数组用于保存，now数组用于计算
char s[2];
bool cmp(P p,P q){//排序还回去
	return p.id<q.id;
}
bool cmp2(P p,P q){//按照位置排序
	return p.x<q.x;
}
int main(){
	int test_number;
	int l,t,n;
	scanf("%d",&test_number);
	for(int k=1;k<=test_number;k++){
		scanf("%d%d%d",&l,&t,&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%s",&a[i].x,s);//读入
			if(s[0]=='L'){
				a[i].fx=-1;
			}
			else{
				a[i].fx=1;
			}
			a[i].turn=0;
			a[i].id=i;
		}
		for(int i=1;i<=n;i++){
			now[i]=a[i];
			now[i].x+=now[i].fx*t;//计算每只蚂蚁的位置
		}
		sort(a+1,a+1+n,cmp2);
		sort(now+1,now+1+n,cmp2);
		for(int i=1;i<=n;i++){
			if(i+1<=n&&now[i].x==now[i+1].x){
				now[i].turn=now[i+1].turn=1;
			}
			a[i].turn=now[i].turn;
			a[i].x=now[i].x;
			a[i].fx=now[i].fx;
		}//根据相对位置不改变来进行还原
		sort(a+1,a+1+n,cmp);
		printf("Case #%d:\n",k);
		for(int i=1;i<=n;i++){
			if(a[i].turn){
				printf("%lld Turning\n",a[i].x);
			}
			else if(a[i].x>l||a[i].x<0){
				puts("Fell off");
			}
			else if(a[i].fx==1){
				printf("%lld R\n",a[i].x);
			}
			else{
				printf("%lld L\n",a[i].x);
			}
		}//判断四种情况
		puts("");
	}
	return 0;
}

```
应该是不用long long的，但我为了保险（~~其实是Debug找不出错乱改的~~），还是用了。

---

## 作者：noall (赞：3)

输出样例其实是：
```
Case #1:
2 Turning
6 R
2 Turning
Fell off

Case #2:
3 L
6 R
10 R
```

#### 思路

这题的思路非常清奇。

在木棍上的蚂蚁其实可以看成一个个小点，而当其中两个相撞时，看起来就像两个点**对穿而过**一样。

所以，假设有一只蚂蚁1号初始为$(1,R)$，那么$2s$过后，一定有一只蚂蚁为$(3,R)$，但这只蚂蚁却不一定是蚂蚁1号。

所以，我们只需要计算出蚂蚁保持原运动状态在$T​$时刻时的位置，然后搞清楚“谁是谁”就行了。

画个图，仔细观察一下，发现其实蚂蚁运动前与运动后的相对顺序是不变的。例如，运动前从左到右的蚂蚁编号为$1,2,3$，运动后依然肯定还是$1,2,3$。

所以我们只需要将所有的运动前与运动后的**位置**进行排序，运动前的位置对应运动后的位置，即确定蚂蚁“谁是谁”的问题。

因为题目输入不一定是按从左到右的顺序输入，所以我们需要用一个数组$order[i]$来记录顺序。

#### code

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int maxn=1e4+7;
const char di[][10]={"L","Turning","R"};
 
struct date{
	int id,p,d;//输入顺序；位置；朝向，-1为左，0为Turning，1为右
	bool operator < (const date& num1)const{
		return p<num1.p;
	}
}before[maxn]/*运动前*/,after[maxn]; /*运动后*/
 
int N,l,t,n,order[maxn];
 
int main(){
	int temp1,cnt;char temp2;
	scanf("%d",&N);cnt=N;
	while(cnt--){
		printf("Case #%d:\n",N-cnt);
		scanf("%d%d%d",&l,&t,&n);
		for(int i=1;i<=n;i++){
			int tt;
			scanf("%d %c",&temp1,&temp2);//注意空格
			before[i]=(date){i,temp1,(temp2=='L'?-1:1)};
			after[i]=(date){0,temp1+(temp2=='L'?-1:1)*t,(temp2=='L'?-1:1)};//记录运动后的位置。注意，此时不知道“谁是谁”，所以id=0。
		}
		sort(before+1,before+1+n),sort(after+1,after+1+n);
		for(int i=1;i<=n;i++) order[before[i].id]=i;//记录顺序
		for(int i=1;i<n;i++)
            if(after[i].p==after[i+1].p)
                after[i].d=after[i+1].d=0;//若位置重合，指定为Turning
		for(int i=1;i<=n;i++){
			temp1=order[i];
			if(after[temp1].p>l||after[temp1].p<0) printf("Fell off\n");//如果不在木棍上，输出Fell off
			else printf("%d %s\n",after[temp1].p,di[after[temp1].d+1]);
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：邓布利多6 (赞：3)

### 题目大意
一根长度为 $L$ 厘米的木棍上有 $n$ 只蚂蚁，每只蚂蚁要么向左爬，要么向右爬，速度为 $1$ 厘米/秒。当两只蚂蚁相遇时，它们同时掉头（时间忽略不计）。给出每只蚂蚁的初始位置和朝向，请计算 $T$ 秒后每只蚂蚁的位置。

### 题目分析

- 考虑两个蚂蚁相遇调头的运动，在不考虑蚂蚁编号交换的情况下，等价于两只蚂蚁直接穿过对方继续走。

- 对于每个蚂蚁来说，每次蚂蚁的结束位置不一定为直接穿过到达的位置。我们发现，蚂蚁们相遇后就会调头，发现其实蚂蚁运动前与运动后的相对顺序是不变的。

**结论：** 只需要将所有的**运动前与运动后的位置**进行排序，确定蚂蚁 **“谁是谁”。**

$Notice$：注意木棍的范围为$0∼L$

### 代码
```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 10001;
int T, l, t, n, x, now[N];
struct node{
	 int id, num, to;
	 bool operator < (const node &a) const
	 {
		  return num < a.num;
	 }
}ant[N], ant2[N];
char c;
string s[] = {"L", "Turning", "R"};
int main()
{
	 cin >> T;
	 for(int opt = 1; opt <= T; opt++)
	 {
          if(opt != 1) cout << endl;
		  cin >> l >> t >> n;
		  for(int i = 1; i <= n; i++)
		  {
			   cin >> x >> c;
			   ant[i] = (node){i, x, (c == 'L' ? -1 : 1)}; 
			   ant2[i] = (node){i, x + t * ant[i].to, (c == 'L' ? -1 : 1)};
		  } 
		  sort(ant + 1, ant + n + 1);
		  sort(ant2 + 1, ant2 + n + 1);
		  for(int i = 1; i <= n; i++)
			   now[ant[i].id] = i;
		  for(int i = 1; i < n; i++)
			   if(ant2[i].num == ant2[i + 1].num) ant2[i].to = ant2[i + 1].to = 0;
		  cout << "Case #" << opt << ":\n";
		  for(int i = 1; i <= n; i++)
			   if(ant2[now[i]].num > l || ant2[now[i]].num < 0) cout << "Fell off\n";
					else cout << ant2[now[i]].num << ' ' << s[ant2[now[i]].to + 1] << endl;
	 }
	 return 0;
}
```

---

## 作者：封禁用户 (赞：2)

先上源代码：
```
/*
防伪标识
作者：electrodynamix
语言：C++
结果：AC
*/
/*
    只考虑初始位置和末位置，初始时在最左边的蚂蚁，
    往右走，碰撞然后折回来，还是在最左边；中间蚂蚁
    也是在一个范围内来回走，相对位置不变！
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 10005 /最大值
struct node{
    int id;
    int p;
    int dir;
};

int cmp(node a,node b)
{
    return a.p<b.p;
}

node a[N],b[N];
int ord[N];
char to[][10] = {"L", "Turning", "R"};/三种状态
int main()
{
    int t,cas=1;
    char s[3];
    scanf("%d",&t);
    while(t--)
    {
        int l,t,n;
        scanf("%d%d%d",&l,&t,&n);
        int q;
        for(int i=0;i<n;i++){
            scanf("%d%s",&q,s);
            int f=(s[0]=='R'?1:-1);
            a[i].id=i;  a[i].p=q;       a[i].dir=f;
            b[i].p=q+t*f;   b[i].dir=f;
        }
        sort(a,a+n,cmp);
        for(int i=0;i<n;i++) ord[a[i].id]=i;/相对位置 不变！
        sort(b,b+n,cmp);
        for(int i=0;i<n;i++)
            if(b[i].p==b[i+1].p)
            b[i].dir=b[i+1].dir=0;/位置相同置为0
        printf("Case #%d:\n",cas++);
        for(int i=0;i<n;i++)
        {
            int k=ord[i];/获取相对位置顺序
            if(b[k].p<0||b[k].p>l)printf("Fell off\n");
            else printf("%d %s\n",b[k].p,to[b[k].dir+1]);
        }
        printf("\n");

    }
}
```
主要是逐步的去推理，每秒钟变换一次就是了（不是说要等一秒才能算出变换后结果）（滑稽）


还有，你们想复制么？对此，我没有任何想法。只要你们喜欢棕名就行！

---

## 作者：小元勋 (赞：0)

- 考虑两个蚂蚁相遇调头的运动，如果从很远的地方看，总体上来说，等价于直接穿过直接走。

- 但对于每个蚂蚁来说，每次蚂蚁的结束位置不一定为直接穿过到达的位置。我们发现，蚂蚁们相遇后就会调头，所以他们之间的相对距离关系不会改变，所以到达后每个蚂蚁的位置对应初始蚂蚁的位置。

- 先计算出每个蚂蚁直接走的结束的位置，排序后，再处理结束时正在碰撞的情况。然后将原来的蚂蚁的位置排序，记录下读入的下标，记录下答案。

- 注意木棍的范围为$0\sim{L}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 10050

int n,L,T,CA,cnt = 0;
char c;
struct Ant {
	int x,id,d;
}A[maxn],B[maxn],ans[maxn];

inline int read_() {
	int x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

inline bool cmp_(Ant aa,Ant bb) {
	return aa.x < bb.x;
}

void readda_() {
	CA = read_();
	while(CA--) {
		L =read_();T = read_();n = read_();
		for(int i=1;i<=n;++i) {
			A[i].x = read_();B[i].x = A[i].x;
			A[i].id = i;B[i].id = 0;
			cin >> c;
			A[i].d = ( c=='L' ? -1 : 1 );
			B[i].d = A[i].d;
			B[i].x += B[i].d * T;
		}
		sort(B+1,B+1+n,cmp_);
		for(int i=1;i<n;++i) {
			if(B[i].x==B[i+1].x) {
				B[i].d = 2;
				B[i+1].d = 2;
			}
		}
		sort(A+1,A+1+n,cmp_);
		for(int i=1;i<=n;++i) {
			ans[A[i].id].x = B[i].x;
			ans[A[i].id].d = B[i].d;
		}
		printf("Case #%d:\n",++cnt);
		for(int i=1;i<=n;++i) {
			if(ans[i].x<0||ans[i].x>L) printf("Fell off\n");
			else {
				printf("%d ",ans[i].x);
				if(ans[i].d==-1) printf("L\n");
				else if(ans[i].d==1) printf("R\n");
				else printf("Turning\n");
			}
		}
		printf("\n");
	}
}

int main() {
	//freopen("a.txt","r",stdin);
	//freopen("ac.txt","w",stdout);
	readda_();
	return 0;
}
```


---

