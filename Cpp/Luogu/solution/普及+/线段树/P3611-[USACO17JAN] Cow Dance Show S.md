# [USACO17JAN] Cow Dance Show S

## 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。

## 样例 #1

### 输入

```
5 8
4
7
8
6
4```

### 输出

```
4
```

# 题解

## 作者：Strong_Jelly (赞：29)


先来介绍一下二分答案，**二分答案是从一个区间内取一个中间值，判断是否符合题意（这里就先算要求最小值吧），符合则向更优的方向缩小范围（r = mid - 1），不符合则向能有可能的方向缩小范围（l = mid + 1）。** 我们在这道题中需要二分k（及舞台上**最多能跳多少牛**），k越小结果就越优，所以当mid满足条件时，l就应该不变，r就应该 = mid - 1。



那么看代码吧（代码里注释有**核心思路**）（不会**堆**的看[这里](https://www.luogu.org/blog/qqq1112/dui-shuo-ju-jie-gou)）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, q[1000001];
inline bool f(int x)//这里x就是题目中的k 
{
	int y = 0;//y存的是上一头牛跳舞的结束时间 
	int ans = 0;//ans存时间和 
	priority_queue < int, vector < int >, greater < int > > pru;//堆的元素存的是牛的结束时间 
	for(register int i = 1; i <= x; ++i)//先把前k个跳舞的时间push进小根堆中 
	{
		pru.push(q[i]);//注意：只有这里是时间(不是结束时间) 
	}
	for(register int i = x + 1; i <= n; ++i)
	{
		ans += pru.top() - y;//这头牛的结束时间 - 上头牛的结束时间 = 又多用的时间 
		y = pru.top();//改为这头牛的结束时间 
		pru.pop();//弹出已经跳完舞的牛 
		pru.push(q[i] + y);//注意：要加上y才是这头牛的结束时间(上头牛的结束时间 + 这头牛跳舞需要的时间 = 这头牛的结束时间) 
		if(ans > m)//不能大于最大值 
		{
			return false;
		}
	}
	while(x--)//还差k个没有跳舞(加上跳舞时间) 
	{
		ans += pru.top() - y;//这些和上面相同 
		y = pru.top();
		pru.pop();
		//pru.push(q[i] + y);这里不能加，因为已经没有牛还在等待跳舞了(上面的循环他们都跳完了，现在所有牛不是在跳舞就是已经跳完了) 
		if(ans > m)
		{
			return false;
		}
	}
	return ans <= m;//其实这里直接return true就好了 
}
inline int half()//二分 
{
	int l = 0;
	int r = 100000;//开大点 
	int ans = 0;//最后的答案 
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(f(mid))
		{
			ans = mid;//mid可行 
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	return ans;
}
int main()
{
	scanf("%d %d", &n, &m);
	for(register int i = 1; i <= n; ++i)
	{
		scanf("%d", &q[i]);
	}
	//sort(q + 1, q + n + 1);这里不要排序，因为题目中说必须按牛在舞蹈中出现的顺序跳舞(1 ~ n) 
	printf("%d", half());
	return 0;
}
```


---

## 作者：VPYEKINDAR (赞：24)

emmmm这题虽然没其他USACO题难，但是黄的真的好吗。。 步入正题，这一题明显有k越大同时间处理的牛牛就越多，所以采用二分法，对于check函数捏，我们可以先手模拟一遍，诶你就发现，先是1-k最小的数出来，1-k其他数再减去它，再以后往下加。。 所以很明显可以维护一个小根堆，那么问题来了，如何快速把堆里元素维护出来呢？(建议做过蚯蚓这一题的往后自己实现) 暴力地想(我有个同学就是这么想的)一个一个把堆里东西pop出来再减去放回去，一定超时了啦！所以我们实际上是要维护这种小根堆的关系的同时减去，发现那种做法冗余操作的比较多的都是以前在堆里的元素，所以我们反着想，对加进去的元素加堆里元素要减的数，就可以维护这种关系了，此时相当于我们把这个递增的堆同时加了一个数，之后再减回去 就OK啦~
~~
```
#include <bits/stdc++.h>
using namespace std;
int n,t;
int a[100010];
int check(int x){
	int f=0;
	priority_queue<int,vector<int>,greater<int> > q;
	for(int i=1;i<=x;i++){
	q.push(a[i]);}
	if(f>t)return 0;
	int z=x+1,c=0;
	for(int i=z;i<=n;i++){
		f+=q.top()-c;
		c=q.top();q.pop();
		if(f>t)return 0;
		q.push(a[i]+c);
	}
	for(int i=1;i<=x;i++){
		f+=q.top()-c;
		c=q.top();q.pop();
		if(f>t)return 0;
	}
	//cout<<f<<endl;
	return 1;
}
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int l=0,r=n;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	cout<<l;
}//lyx之父多多著```

---

## 作者：从不再见 (赞：18)

### [P3611](https://www.luogu.org/problem/P3611)题解

  问题是最大中的最小，所以可以定解法为二分答案，所以去二分T_max最大时K的最小。可是，二分的难点在check函数中，我的思路如下：
  
  check最终去判断舞台大小为k所用的时间是否超过T_max。这一思路去模拟奶牛的上台，当一头奶牛跳完时，下一头奶牛上台,开始时间为cow[i]+之前奶牛的时间和，这里我用优先队列维护，在舞台中最先跳完的最先下台，我也不再过多赘述，代码如下：
  ```
#include<bits/stdc++.h>
using namespace std;
const int N=10000+5;
int n,t_max;
int cow[N];
bool check(int x){
	priority_queue<int, vector<int>, greater<int> > dance;//维护舞台上舞蹈的牛，小->大 
	for(register int i=1;i<=x;i++)
		dance.push(cow[i]);
	for(register int i=x+1;i<=n;i++){
		int cur=dance.top();	//下台了的牛 
		dance.pop();
		dance.push(cur+cow[i]);//读入下一头牛 
	}
	int cur;
	while(!dance.empty()){	//取出最终的用时 
		cur=dance.top();
		dance.pop();
	}
	return cur<=t_max; 
}
int main(){
	cin>>n>>t_max;
	for(register int i=1;i<=n;++i){
		cin>>cow[i];
	}
	int l=0,r=n+1;
	while(l+1<r){//二分舞台大小 
		int mid=l+((r-l)>>1);
		if(check(mid)){//用时小于上限,减小舞台大小 
			r=mid;
		}
		else{//增加舞台大小 
			l=mid;
		}
	}
	cout<<r;//已知最优的值存在r中,输出r 
	return 0;
}

```

#### 祝大家早日AC该题



---

## 作者：zy小可爱ღ (赞：14)

楼下dalao不是P党就是优先队列，看的我作为一个新手蒟蒻好慌啊。。。

这题用二分加冒泡（你没有看错，用sort反而会超时）

先用二分决定k的值，然后判断这个k可不可行，然后继续二分，重复刚才操作

具体解释看代码：



```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,tmax,t,l,r;
int a[10005],b[10005];//变量就不过多介绍了，大家自己看
int shu(int k){//函数，判断当前k是否可行
    for(int i=1;i<=k;i++){
            b[i]=a[i];
```
}//前k个奶牛
sort(b+1,b+1+k);//排序，因为当前数组是无序的，所以用sort


```cpp
    for(int i=k+1;i<=n;i++){
        if(b[k]>tmax)return tmax+1;//如果当前已经超过了，就直接退出循环
        b[1]+=a[i];//定向思维是减去最小的时间，但未必必须这样做
        for(int j=2;j<=k;j++){//传说中的冒泡粉墨登场~~~此处用sort真的会超时，不信你们自己去试试
            if(b[j]>=b[j-1]){//如果已经在合适的位置，就退出循环
                break;
            }
            int x=b[j];//否则交换
            b[j]=b[j-1];
            b[j-1]=x;
        }
    }
    return b[k];//返回最大的时间
}
int main(){
    freopen("cowdance.in","r",stdin);
    freopen("cowdance.out","w",stdout);//这两句话当废话处理，是我在USACO主网站上交的时候加上去的
    scanf("%d%d",&n,&tmax);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
```
}//读入
l=1,r=n;//二分的准备活动（- 一二三四，二二三四）

while(l<r){//二分开始，在left小于（**等于**）right的时候执行

```cpp
        int mid=(l+r)/2;//取中间值
        if(shu(mid)>tmax)l=mid+1;//如果当前k不满足要求，增大k的值
        else r=mid-1;//反之缩小
    }
    printf("%d\n",l);//输出
    return 0;
}
```
嘿嘿~~~
如果你们Ctrl C+Ctrl V的话，会发现一个很神奇的现象：我的程序不能AC！！！

仔细看看注释，我相信你可以改出来的哦~~~


---

## 作者：Histone (赞：12)

这是一道**优先队列+二分**的题

要选出最优的$K$，满足时间小于$T_{max}$

我们要在区间 **$[ 1 , n ]$** 里二分答案

大致流程很简单：

- 二分一个 $K$

- 利用优先队列模拟跳舞流程，判断$K$是否合理

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,num[10005];
bool c(int x){
	/*利用优先队列模拟跳舞情况*/ 
	int at = 0;//当前k的耗时
	priority_queue < int,vector<int>,greater<int> > q;
	for(int i=1;i<=x;i++)q.push(num[i]);
	for(int i=x+1;i<=n;i++){
		int temp = q.top();q.pop();
		q.push(temp+num[i]);
	}
	while(!q.empty()){
		at = q.top();q.pop();
	}
	return at<=t;
}
int main(void){
	/*输入不解释*/
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>num[i];
	
	/*二分答案*/	
	int l=0,r=n,mid;
	while(l<=r){
		mid = (l+r)>>1;
		if(c(mid))r = mid-1;
		else l = mid+1;
	}
	cout<<l;
	return 0;
}
```

当然，如果大家觉得二分太麻烦的话。

$K$值直接从$1$枚举到$n$也是可以的

[测试详情](https://www.luogu.com.cn/record/31867554)

直接枚举的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,num[10005];
bool c(int x){
	/*这里其实就是利用优先队列模拟跳舞情况*/ 
	int at = 0;
	priority_queue < int,vector<int>,greater<int> > q;
	for(int i=1;i<=x;i++)q.push(num[i]);
	for(int i=x+1;i<=n;i++){
		int temp = q.top();q.pop();
		q.push(temp+num[i]);
	}
	while(!q.empty()){
		at = q.top();q.pop();
	}
	return at<=t;
}
int main(void){
	/*输入不解释*/
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>num[i];
	int ans = 0;
    /*直接暴力枚举！*/
	for(int i=1;i<=n;i++){
		if(c(i)){
			ans = i;break;
		}
	}
	cout<<ans;
	return 0;
}
```

当然，~~这题数据较水~~

结束

各位看官，如果觉得还可以的话，点个赞吧~



---

## 作者：MessiYT (赞：8)

#首先这一题是一道二分的题目（最大值中求最小，最小值中求最大都可以用二分）

##既然是二分就涉及到怎么去check答案

###那么每次都是队列中最小的牛先跳完，因此我很自然就想到了小根堆。代码附上（小根堆应该不需要解释吧，有不懂可以私信哦！）

```cpp
var
  n,tmax,i,ans,l,r,m,len,time:longint;
  d,heap:array[0..10005] of longint;
  procedure put(x:longint);
  var
    son,t:longint;
  begin
    inc(len);
    heap[len]:=x;
    son:=len;
    while (son<>1) and (heap[son]<heap[son shr 1]) do
    begin
      t:=heap[son];
      heap[son]:=heap[son shr 1];
      heap[son shr 1]:=t;
      son:=son shr 1;
    end;
  end;
  function get:longint;
  var
    son,fa,t:longint;
  begin
    get:=heap[1];
    heap[1]:=heap[len];
    dec(len);
    fa:=1;
    while fa*2<=len do
    begin
      if (fa*2=len) or (heap[fa*2]<heap[fa*2+1]) then son:=fa*2
                                                 else son:=fa*2+1;
      if heap[fa]<heap[son] then break;
      t:=heap[son];
      heap[son]:=heap[fa];
      heap[fa]:=t;
      fa:=son;
    end;
  end;
  function check(m:longint):boolean;
  var
    i,j:longint;
  begin
    len:=0;
    time:=0;
    for i:=1 to m do put(d[i]);
    j:=i+1;
    while j<>n+1 do
    begin
      time:=get;
      if time+d[j]>tmax then exit(false);
      if j=n then exit(true);
      put(time+d[j]);  //将之前用的总时间加上第j头牛的时间，塞入堆中
      inc(j);
    end;
    exit(true);
  end;
begin
  readln(n,tmax);
  for i:=1 to n do readln(d[i]);
  l:=1;
  r:=n;
  ans:=maxlongint;
  while l<=r do  //二分答案
  begin
    m:=(l+r) shr 1;
    if check(m) then begin r:=m-1; ans:=m; end
                else l:=m+1;
  end;
  writeln(ans);
end.
```

---

## 作者：封禁用户 (赞：7)

### ~~作为一个线段树的狂热爱好者，看到这题第一反应就是线段树……~~

首先这个题的k显然具有可二分性（题目上都非常明确地说了“保证K=N时表演会按时完成”，“显然，K的值越大，T就越小”，就差没说“您需要用二分答案来完成这个题”了……），然后我们来想如何判定。

判定很简单，我们只需要模拟找出在这个大小的平台的表演时间，然后和Tmax比较即可。

这个模拟过程便是：

①找出台上的剩余时间最小的牛。

②让这头牛下台，并把剩下的牛的剩余时间都相应减小，并且把这个时间添加到答案中。

③让台下的下一头牛到走了的那头牛的位置上，如果没有下一头奶牛，那就把这个位置设为$∞$，重复模拟过程。

然后这个有整体最大值还有整体的加减，显然就是线段树来维护。~~众人：这不是堆吗？我：堆是个啥？那个据说叫“堆”的玩意我都是手写线段树实现的。……~~

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int get(){
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
typedef struct _n{
	int left;int right;int minn;int adds;int pos;
}node;node memchi[1000001];int gn=1;
int ints[100001];
inline void down(int tree){
	int ls=memchi[tree].left,rs=memchi[tree].right,cjr=memchi[tree].adds;
	if(cjr!=0){memchi[tree].adds=0;
		memchi[ls].minn+=cjr;memchi[rs].minn+=cjr;memchi[ls].adds+=cjr;memchi[rs].adds+=cjr;
	}
}
inline void up(int tree){
	int ls=memchi[tree].left,rs=memchi[tree].right;
	if(memchi[ls].minn<memchi[rs].minn){
		memchi[tree].minn=memchi[ls].minn;
		memchi[tree].pos=memchi[ls].pos;
	}else{
		memchi[tree].minn=memchi[rs].minn;
		memchi[tree].pos=memchi[rs].pos;
	}
}
int build(int l,int r){
	int tree=gn;gn++;memchi[tree].adds=0;
	if(l==r){
		memchi[tree].minn=ints[l];memchi[tree].pos=l;
	}else{
		int mid=(l+r)>>1;memchi[tree].left=build(l,mid);
		memchi[tree].right=build(mid+1,r);up(tree);
	}return(tree);
}
int pt,num;
void setpt(int l,int r,int tree){
	if(l==r){
		memchi[tree].minn=num;return;
	}
	down(tree);int mid=(l+r)>>1;
	if(pt<=mid)setpt(l,mid,memchi[tree].left);
	else setpt(mid+1,r,memchi[tree].right);
	up(tree);
}int n,t;
inline bool check(int mid){gn=1;
	int ptr=mid+1,root=build(1,mid);long long tot=0;
	for(register int i=1;i<=n;i++){
		if(ptr>n){
			tot+=memchi[root].minn;pt=memchi[root].pos;
			int me=memchi[root].minn;memchi[root].minn-=me;memchi[root].adds-=me;
			num=0x7fffffff;setpt(1,mid,root);
		}else{
			tot+=memchi[root].minn;pt=memchi[root].pos;
			int me=memchi[root].minn;memchi[root].minn-=me;memchi[root].adds-=me;
			num=ints[ptr];setpt(1,mid,root);
			ptr++;
		}
	}
	return(tot<=t);
}
int cmp(const int &a,const int &b){
	return(a>b);
}
int main(){
	n=get(),t=get();for(register int i=1;i<=n;i++)ints[i]=get();
	//sort(ints+1,ints+1+n,cmp);
	int ans=0,l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;r=mid-1;
		}else l=mid+1;
	}
	cout<<ans<<endl;
	return(0);
}
```

---

## 作者：Hongse_Fox (赞：6)

[原题链接](https://www.luogu.org/problem/P3611)

题目中十分好心地给了这样一句话：

显然，K的值越大，T就越小。由于表演不能拖太长，你得知了指定T的最大可能值的上限T-max。请根据这个约束，确定K的最小值。

看到求最大值，又看到要满足某个东西不超过某个值，这难道不就是在把二分答案的标签写在题目上吗！？

~~（说最小费用最大流的就不要在这里切水题了）~~

没错，这道题就是一道非常典型的二分答案

我们可以先二分一下K值，对于每一个K，我们可以模拟一下是否合法

K个舞台，如果按时间来考虑的话，每一头牛都要找到end时间最早的地方然后补那个空位

想找最早end的舞台，也就相当于在这K个数中找最值啊！

这像极了什么？

这像极了 ~~爱情~~ 堆！

因此我们可以用一个优先队列，每轮到一头牛就把时间最短的舞台出队，让那头牛进去跳

最后再把耗时最长的舞台搞出来与T-MAX比较即可

那么最后请上代码：
```cpp
#include<cstdio>
#include<cctype>
#include<queue>
using namespace std;
inline int R(){												//快读 
    int r=0;char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return r;
}
int n,tmax,d[10005],l,r;
struct node{
    int val;
    friend bool operator < (node a,node b){					//结构体内重载运算符，让时间从小到大排 
        return a.val>b.val;
    }
};
priority_queue <node> q;									//用STL里面的优先队列 
inline bool check(int a){
    for(register int i=1;i<=a;i++) q.push((node){0});		//先把那k个容器给入队 
    for(register int i=1;i<=n;i++){
        node u=q.top();										//去除耗时最少的舞台 
        q.pop();
        u.val+=d[i];
        q.push(u);											//让牛跳之后再入队 
    }
    node tot;
    while(!q.empty()) tot=q.top(),q.pop();					//不停出队找到最大值 
    if(tot.val>tmax) return 0;								//如果不可行就返回0 
    return 1;												//否则返回1 
}
int main(){
    n=R();tmax=R();
    for(register int i=1;i<=n;i++) d[i]=R();
    l=1,r=n;
    while(l<r){												//二分 
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d\n",l);
    return 0;
}
```
最后提醒大家二分部分的代码一定不能打错

找到自己喜欢的打法就不要变了，不然很容易炸的

---

## 作者：zhaimingshuzms (赞：4)

#二分答案

对于每个二分的结果，进入判断函数判断其最大时间是否超过时限，用一个优先队列，每次把要下台的那只奶牛看成在台上又表演了下一只要上台的奶牛那么长时间，不断更新，在更新时如果已经超过时限就直接跳出，否则进入最后的统计，tmax和t\_max进行比较，返回值；

时间复杂度O（n(logn）^2）；

其实我本来使用链表维护的，但是链表修改时（不是简单的修改，而是修改之后再排序的操作）严重超时，偶然想到了修改弹出都是logn的优先队列，就AC了这道题；

#########################################################

```cpp
%:pragma GCC optimize(3)
#include<cstdio> 
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int N=10001;
int t[N],n,t_max;
priority_queue<int,vector<int>,greater<int> >q;
bool b(int k)
{
    int tmax=0,op,tt;
    for (int i=1; i<=k; i++) q.push(t[i]);
    for (int i=k+1; i<=n; i++)
    {
        op=q.top();  
        q.pop();
        op+=t[i];
        if (op>t_max) return 0;
        q.push(op);
    }
    for (int i=1; i<=k; i++) 
    {
        tt=q.top();
        if (tt>tmax) tmax=tt;
        q.pop();
    }
    return tmax<=t_max;
}
int main()
{
    scanf("%d%d",&n,&t_max);
    for (int i=1; i<=n; i++) scanf("%d",&t[i]);
    int ans=n;
    for (int l=1,r=n,mid=(l+r)>>1; l<=r; mid=(l+r)>>1)
    if (b(mid)) {ans=mid; r=mid-1;} else l=mid+1;
    printf("%d",ans);
    return 0;
}
```
#################################################################
本蒟蒻代码写的不好，勿喷


---

