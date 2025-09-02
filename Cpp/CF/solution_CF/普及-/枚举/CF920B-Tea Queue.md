# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3
```

### 输出

```
1 2 
1 0 2 
```

# 题解

## 作者：__LiChangChao__ (赞：2)

## 思路
这道题直接**模拟**时间计数器，计算每一个人接水时的时间就可以了。

注：由于题目保证了 $l_{i-1}\le l_i$，所以我们并**不需要排序**。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
long long n,t,l[maxn],r[maxn];
int main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld%lld",&l[i],&r[i]);
		int ans=0;//ans代表当前的时间
		for(int i=1; i<=n; i++) {
			if(ans<=l[i]) ans=l[i]+1,printf("%lld ",l[i]);//来了一个人
			else if(r[i]>=ans) printf("%lld ",ans),ans++;//这个人正在等
			else printf("0 ");//这个人跑了
		}
		printf("\n");
	}
}
```

---

## 作者：ryf_loser (赞：2)

一道模拟题。

看到楼上几位大佬的程序，看的我瑟瑟发抖。

思路就是用一个变量去枚举时间，它记录的是已经经过了多长时间。

枚举时间，看那个人是否能够喝到茶。如果可以，输出并时间加一增加时间，否则离开。

具体一点：就是当 $l\ge c$ 时，把时间完后推一下，即 $c\leftarrow l$，但如果大于等待时间，不做任何操作。

最容易错的地方在于不能把没喝到茶的学生算到总时间中。

AC 代码

```cpp
#include<cstdio>
using namespace std;
int main(){
    int t;
    scanf ("%d",&t);//读入数据组数
        while(t--){
            int n;
            scanf ("%d",&n);int c=1;//读入几位同学， c  为当前时间
            for(int i=1;i<=n;i++){
                int l,r;
                scanf ("%d%d",&l,&r);//读入两个时间
                if(l>=c)//特判
                c=l;
                if(r<c&&i!=1){printf ("0 ");continue;}//根据题意如果大于等待时间输出 0
                else{printf ("%d ",c);c++;}否则输出学生喝到茶的时间
    }
    printf ("\n");//记得换行
    }
}
```


---

## 作者：Great_Influence (赞：1)

直接按题意开堆模拟即可。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&k^'-')k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file(void){
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
}
const int MAXN=1011;
#define Chkmax(a,b) a=a>b?a:b
static struct people
{
    int l,r,id;
    friend bool operator<(people a,people b)
    {return a.l<b.l;}
}p[MAXN];
static int ans[MAXN],n;
inline void init()
{
    read(n);
    Rep(i,1,n)read(p[i].l),read(p[i].r),p[i].id=i;
}
priority_queue<int,vector<int>,greater<int> >G;
inline void solve()
{
    static int pos;pos=1;
    memset(ans,0,sizeof ans);
    Rep(i,1,5000)
    {
        while(pos<=n&&p[pos].l==i)G.push(p[pos++].id);
        while(!G.empty()&&p[G.top()].r<i)G.pop();
        if(!G.empty()){ans[G.top()]=i,G.pop();}
    }
    Rep(i,1,n)printf("%d ",ans[i]);puts("");
}
int main(void){
	file();
    static int _;
    read(_);
    while(_--)
    init(),
    solve();
	return 0;
}

```

---

## 作者：drop (赞：0)

## 思路

 `time` 为当前时间，通过它的变化来判断是否出队。
 
 **重点：** 

 1. 如果这一项出队则 `time` 不变。
 2. 需要判断 `time` 的初始值。
 3. 第一项不用判断是否出队，可以直接接水。
 
## 代码

``` c++
#include<bits/stdc++.h>
using namespace std;
int t,n;

int main(){
	cin>>t;
	while(t--){
		int time=1;
		cin>>n;
		for(int i=1;i<=n;i++){
			int l,r;
			cin>>l>>r;
			if(time<l) time=l;
			if(r<time&&i!=1) cout<<0<<" ";
			else cout<<time++<<" ";
		}
		cout<<endl;
	} 
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF920B)

一道**模拟**好题。

思路：用一个计数器记录时间，把时间调为最早的时间 $l_1$，然后根据题意模拟即可。

建议在循环里建造计数器，不会忘记清空。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l,r;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		int c=1;
		for(int i=1;i<=n;i++)
		{
			cin>>l>>r;
			if(l>=c)//从最早开始 
				c=l;
			if(r<c&&i!=1)
			{
				cout<<0<<" ";
				continue;
			}
			else
			{
				cout<<c<<" ";
				c++;
			}//根据题意进行模拟 
		}
		cout<<endl;
	}
	return 0;
}
```




---

## 作者：御坂御坂 (赞：0)

 [官方题解](http://codeforces.com/blog/entry/57516)

但并不需如此，直接暴力模拟都可以0ms

全部用STL

因为要考虑离开队伍的人，即要从队列中删除元素

于是便使用STL的list双向链表

cango[t].first 记录的是当时间是t时要出队的人在队伍中的位置（迭代器）

cango[t].second 记录的是当时间是t时要出队的人的ID

其他见注释

```cpp
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#define RI register int

using namespace std;

typedef long long LL;

const int INF = 99999999;

inline int Abs(int x) {
    return x ? x : -x;
}

inline int Max(int x, int y) {
    return (x > y) ? x : y;
}

inline int Min(int x, int y) {
    return (x < y) ? x : y;
}

int T, N, l[1005], r[1005], ans[1005];
list<int> Q;
vector<pair<list<int>::iterator, int> > cango[5005];
list<int>::iterator last() { //返回队伍最后一个人的迭代器 就是Q.end()前面一个
    list<int>::iterator it = Q.end();
    return --it;
}
int main() {
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N;
        int endtime = 0;
        for (RI i = 1; i <= N; ++i) cin >> l[i] >> r[i], endtime = Max(endtime, r[i]);
        int now = l[1] - 1, nowcur = 1;
        Q.clear();
        for (RI i = now; i <= endtime; ++i) cango[i].clear();
        memset(ans, 0, sizeof(ans));
        while ((++now) <= endtime) {
            while (nowcur <= N && l[nowcur] == now)
                Q.push_back(nowcur++), cango[r[nowcur - 1] + 1].push_back(make_pair(last(), Q.back()));//当前时间的人加入队列并且处理cango[]
            if (!Q.empty()) {//注意在访问或者修改Q前必须注意Q是否为空
                for (vector<pair<list<int>::iterator, int> >::iterator it = cango[now].begin(); it != cango[now].end(); ++it)
                    if (!ans[it->second]) Q.erase(it->first);//移除不能再等的人
                if (!Q.empty()) if (l[Q.front()] <= now) ans[Q.front()] = now, Q.pop_front();//如果喝到茶了，出队并记录答案
            }
        }
        for (int i = 1; i <= N; ++i) cout << ans[i] << " ";
        cout << endl;
    }
    //fclose(input);
    //fclose(output);
    return 0;
}
```

---

