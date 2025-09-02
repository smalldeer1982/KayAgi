# Workout plan

## 题目描述

Alan decided to get in shape for the summer, so he created a precise workout plan to follow. His plan is to go to a different gym every day during the next N days and lift $ X[i] $ grams on day $ i $ . In order to improve his workout performance at the gym, he can buy exactly one pre-workout drink at the gym he is currently in and it will improve his performance by $ A $ grams permanently and immediately. In different gyms these pre-workout drinks can cost different amounts $ C[i] $ because of the taste and the gym's location but its permanent workout gains are the same. Before the first day of starting his workout plan, Alan knows he can lift a maximum of $ K $ grams. Help Alan spend a minimum total amount of money in order to reach his workout plan. If there is no way for him to complete his workout plan successfully output $ -1 $ .

## 说明/提示

First example: After buying drinks on days 2 and 4 Alan can finish his workout plan. Second example: Alan cannot lift 40000 grams on day 2.

## 样例 #1

### 输入

```
5 10000
10000 30000 30000 40000 20000
20000
5 2 8 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 10000
10000 40000 30000 30000 20000
10000
5 2 8 3 6
```

### 输出

```
-1
```

# 题解

## 作者：DarkShadow (赞：4)

# CF1218F（贪心）

## 题目大意：

给出 $N$ 个目标和 $N$ 种方案，每种方案可以花费一定代价使分数增加 $A$，第 $i$ 次可以选择前 $i$ 种方案，求每次分数都达到目标的最小代价。

## 思路分析：

由于每种方案增加的分数都相同，所以可以考虑贪心，每一次都用当前花费最少的一种方案来增加分数。

可以维护一个小根堆，每次将方案放进堆里，如果当前分数小于目标就用当前堆顶的方案。

如果堆已经空了还没有达到目标就判断无解。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int n,a,x[N],c[N],cnt,ans;
priority_queue<int,deque<int>,greater<int>> q;//小根堆
int main(){
	scanf("%d%d",&n,&cnt);
	for(int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	scanf("%d",&a);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++){
		q.push(c[i]);//每次将方案放进堆里
		while(cnt<x[i]&&!q.empty()){
			cnt+=a,ans+=q.top();//贪心选取方案
			q.pop();
		}
		if(cnt<x[i]){
			printf("-1");
			return 0;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Victory_Defeat (赞：3)

一道比较水的题（好奇为什么是F题）

题目大意：

给定$n$，$x_i$表示第$i$个目标，$c_i$表示第$i$处提高能力值花费代价，初始有一个能力值$k$，每次提升$a$点能力值，求出最小代价

不难看出是一道贪心题，具体见注释

直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
#define reg register
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define input(a){a=0;char c=gc();int f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+(c&15);c=gc();}a*=f;}
static char buf[1<<21],*p1=buf,*p2=buf;
char bu[1<<21],cha[20];int p,pp=-1;
#define flush(){fwrite(bu,1,pp+1,stdout),pp=-1;}
#define output(x){if(pp>1<<20)flush();if(x<0)bu[++pp]=45,x=-x;do{cha[++p]=x%10+48;}while(x/=10);do{bu[++pp]=cha[p];}while(--p);}
#define Endl bu[++pp]='\n'
#define Space bu[++pp]=' '
#define pc(c) bu[++pp]=c
//忽略本注释以上部分
const int N=100010;
int x[N],n,k,a;
ll ans;
priority_queue<int,vector<int>,greater<int> >q;
//利用优先队列，是将最小值放在前面的堆
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>x[i];
	cin>>a;
    //读入
	for(int c,i=1;i<=n;++i)
	{
		cin>>c;
		q.push(c);
        //将当前费用入队
		while(k<x[i])//只要不能完成任务
		{
			if(q.empty())
			{
				printf("-1\n");//用完所有提高能力值的机会仍不够
				return 0;
			}
			k+=a;//能力值提高
			ans+=q.top();//答案更新，用最小代价
			q.pop();//将这一个机会消除
		}
	}
	printf("%lld\n",ans);//输出
	return 0;
}
```

---

## 作者：wyc0607 (赞：0)

### 算法
典型的贪心，每遇到一瓶饮料就放进队列里，一遇到大于可举起重量的目标即~~氪金~~（大误）买饮料，直到达成目标为止。
如果队列为空（没有饮料了）而又达不到目标，就输出$-1$，即无法完成）。

$N$ 为锻炼计划的天数，$K$ 表示 Alan 在开始他的锻炼计划之前可以举起多少公斤。

$A$ 数组代表 Alan 在第 $i$ 天想要举起多少克，$up$ 代表一瓶饮料能给举重成绩带来的增长量。$c$ 代表在他第 $i$ 天拜访的体育馆饮料的价格。

~~-----------------------代码分割线------------------------~~

[AC 记录](https://www.luogu.com.cn/record/169414199)


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[100005],c[100005],up,ans=0;
priority$queue<int,vector<int>,greater<int> >q;//优先队列，最小值在前。
main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>up;
	for(int i=1;i<=n;i++){
		int c;
		cin>>c;
		q.push(c);//放入队列中 
		while(1){
			if(k>=a[i]) break;//如果达成了目标就可以退出了。 
			if(q.empty()){//代表没有饮料买了。 
				cout<<-1;//就视为无法完成。
				return 0;
			}
			k+=up;//买一瓶。 
			ans+=q.top();//买最便宜的。 
			q.pop(); //踢出队列。 
		}
	}
	cout<<ans;//输出答案。 
}
```

---

## 作者：RioFutaba (赞：0)

# 思路

贪心。对于第 $i$ 天，如果无法达到，就一直用前 $i$ 天没用过的最小的 $c_i$ 去补。如果全部用完了仍然未能达到目标便是无解。

这一过程用优先队列实现。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int maxn=1e5+5;
int n;
ll k,x[maxn],a,c[maxn],ans;
int main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> x[i];
	cin >> a;
	for(int i=1;i<=n;i++) cin >> c[i];
	priority_queue<int,vector<int>,greater<int>> q;//小根堆
	for(int i=1;i<=n;i++){
		q.push(c[i]);//入队
		while(k<x[i] && !q.empty()){
			int p=q.top();//每次取最小
			q.pop();
			ans+=p;
			k+=a;
		}
		if(k<x[i]){//用完了还没能达到目标
			ans=-1;
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## CF1218F Workout plan 题解
### 分析
贪心。

循环枚举 $c_i$。每扫到一个 $c_i$ 就将其放入小根堆中，接下来用 `while` 循环，只要 $k$ 小于 $x_i$，就执行一下判断和操作：

1. 若小根堆已空，说明次数用完还没有完成目标，按题意输出 `-1`，结束程序。

2. 反之能力值 $k$ 加上 $A$，$ans$ 加上优先队列（小根堆）队首元素，弹出队首。

循环结束后输出 $ans$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n, k, a[N], A, ans, c[N];
struct node
{
    int val;
    bool operator<(const node &b)const
    {
        return val>b.val;
    }
};
priority_queue<node> q;
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    cin>>A;
    for(int i=1;i<=n;i++)
    {
        cin>>c[i];
    }
    for(int i=1;i<=n;i++)
    {
        q.push((node){c[i]});
        while(k<a[i])
        {
            if(q.empty())
            {
               cout<<"-1";
               return 0;
            }
            k+=A;
            ans+=q.top().val;
            q.pop();
        }
        
    }
    cout<<ans;
}
```

---

## 作者：_soul_ (赞：0)

用小根堆维护所有的分数，并且记录当前的分数，如果当前小于目标，则将小根堆中的元素加入，如果小根堆为空并且当前的分数还是小于目标则输出-1
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long long ll;
const int N=100005;
priority_queue<int,vector<int>,greater<int> > Q;
int a[N],b[N],n,K,now;
ll ans;
int main(){
	cin >> n >> now;
	for (int i=1;i<=n;++i) cin >> a[i];
	cin >> K;
	for (int i=1;i<=n;++i) cin >> b[i];
	for (int i=1;i<=n;++i){
		Q.push(b[i]);
		while(now<a[i]){
			if(Q.empty()){
				puts("-1");
				return 0;
			}
			now+=K;
			ans+=Q.top();
			Q.pop();
		}
		if(now<a[i]){
			puts("-1");
			return 0;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：leo120306 (赞：0)

## 题目翻译
[翻译](https://www.luogu.com.cn/paste/yeaxnu6l)

都是我自己手翻的，应该比机翻好一点吧，如果有什么问题还请指教。

## 思路
贪心即可。能不买饮料就不买饮料，如果第 $i$ 天一定要买，找到第 $i$ 天及以前没买过饮料的店中最便宜的一家买饮料，直到超过第 $i$ 天的目标。如果之前所有店都买过了，就是无解。此算法的正确性可以感性理解。

这个过程可以使用小根堆来优化。发现其他题解都是优先队列，那我就手写堆吧。

## 代码及细节
- 考虑到极限情况下，答案 $=\sum C_i\leq 10^{14}$，所以答案要开 long long。
- 手写堆不要打错了，（个人认为）比某区间数据结构还难调。
```cpp
#include <cstdio>
using namespace std;

char chrd;
#define read(x){ \
	x=0;\
	chrd=getchar();\
	while(chrd<'0'||chrd>'9') chrd=getchar();\
	while(chrd>='0'&&chrd<='9'){\
		x=(x<<3)+(x<<1)+(chrd^48);\
		chrd=getchar();\
	}\
}
int tsw;
#define swap(x,y){tsw=x;x=y;y=tsw;}

// 以上是一些宏定义

int h[100005],sizh;
inline void add(int x){
	h[++sizh]=x;
	int now=sizh;
	while(now){
		if(h[now>>1]>h[now])swap(h[now],h[now>>1])
		else break;
		now>>=1;
	}
}

inline void pop(){
	swap(h[sizh],h[1]);sizh--;
	int now=1;
	while((now<<1)<=sizh){
		int son=now<<1;
		if(son+1<=sizh&&h[son+1]<h[son])son++;
		if(h[son]<h[now])swap(h[now],h[son])
		else break;
		now=son;
	}
}

// 以上是堆 

int x[100005],c[100005];

int main(){
	int n,k,a;
	read(n);read(k);
	for(int i=1;i<=n;i++) read(x[i]);
	read(a);
	for(int i=1;i<=n;i++) read(c[i]);
	long long sum=0;
	for(int i=1;i<=n;i++){
		add(c[i]);
		while(k<x[i]){
			if(sizh==0){
				printf("-1\n");
				return 0;
			}
			k+=a;
			sum+=h[1];
			pop();
		}
	}
	printf("%lld",sum);
	return 0;
}
```

---

