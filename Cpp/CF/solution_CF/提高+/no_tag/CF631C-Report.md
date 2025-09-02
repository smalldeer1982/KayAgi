# Report

## 题目描述

Each month Blake gets the report containing main economic indicators of the company "Blake Technologies". There are $ n $ commodities produced by the company. For each of them there is exactly one integer in the final report, that denotes corresponding revenue. Before the report gets to Blake, it passes through the hands of $ m $ managers. Each of them may reorder the elements in some order. Namely, the $ i $ -th manager either sorts first $ r_{i} $ numbers in non-descending or non-ascending order and then passes the report to the manager $ i+1 $ , or directly to Blake (if this manager has number $ i=m $ ).

Employees of the "Blake Technologies" are preparing the report right now. You know the initial sequence $ a_{i} $ of length $ n $ and the description of each manager, that is value $ r_{i} $ and his favourite order. You are asked to speed up the process and determine how the final report will look like.

## 说明/提示

In the first sample, the initial report looked like: 1 2 3. After the first manager the first two numbers were transposed: 2 1 3. The report got to Blake in this form.

In the second sample the original report was like this: 1 2 4 3. After the first manager the report changed to: 4 2 1 3. After the second manager the report changed to: 2 4 1 3. This report was handed over to Blake.

## 样例 #1

### 输入

```
3 1
1 2 3
2 2
```

### 输出

```
2 1 3 ```

## 样例 #2

### 输入

```
4 2
1 2 4 3
2 3
1 2
```

### 输出

```
2 4 1 3 ```

# 题解

## 作者：Su_Zipei (赞：5)

## 分析

　　这题其实不是很难，用了一个贪心思想，蒟蒻的我都一眼找出了规律，首先，它不管是顺着排序还是倒着排序，如果某次操作比前边的一次操作范围大，那么前边的那次操作其实是无效的，另外，如果操作中最大的右端点到r，那么r再往后的区间是不会被修改的。因为操作的时候是修改1到r，所以前边的区间会被多次修改，而后边的区间则只会被最后那次不重叠的修改，如下图。

 ![](https://cdn.luogu.com.cn/upload/image_hosting/xp9cobva.png?x-oss-process=image/resize,m_lfit,h_00,w_600)

 假如从1到i有很多次操作，从i到j有且仅有一次操作，那么我区间(i,j]的值就能确定，如果是由大到小排，那么j的位置一定是1，反之亦然，所以定义一个头指针和尾指针，倒着扫描一遍整个序列就好。
 
 ```
 #include<iostream>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int a[N],ans[N],idx[N],typ[N];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int mx=0;
    for(int i=1;i<=m;i++){
        int t,r;
        cin>>t>>r;
        idx[r]=i;
        typ[r]=t;
        mx=max(mx,r);
    }
    sort(a+1,a+mx+1);
    int flag,now=0,hh=1,tt=mx;
    for(int i=mx;i;i--){
        if(now<idx[i]){
            now=idx[i];
            flag=typ[i];
        }
        if(flag==1)
            ans[i]=a[tt--];
        else ans[i]=a[hh++];
    }
    for(int i=1;i<=mx;i++)
        cout<<ans[i]<<" ";
    for(int i=mx+1;i<=n;i++)
        cout<<a[i]<<" ";
    return 0;
}
 ```

---

## 作者：wwlw (赞：3)

[Link](https://www.luogu.com.cn/problem/CF631C)
--------------   

### Solution
注意到每次排序的   是一个前缀。而若先排一个较短的前缀，之后又排一    个大点的前缀，那么显然这个小的会被覆盖，等价于没有排序。将所有这样的无用排序删除，最终会得到一个长度严格单调下降的操作序列（可以用单调栈维护）。考虑栈内相邻的两个操作，前缀长度分别为 $x$、$y$，且           $x<y$，那么中间的 $x-y$ 个数一定是确定的。可以发现其一定是连续的一段最大值或最小值（因为是排序），所以可以用优先队列维护。

```cpp
#include<stdio.h>
#include<queue>
using namespace std;
#define N 200007

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Op{
    int op,x;
}sta[N];

struct Node1{
    int x,pos;
    bool operator <(const Node1 &X) const{return x<X.x;}
};

struct Node2{
    int x,pos;
    bool operator <(const Node2 &X) const{return x>X.x;}
};

bool vis[N];
int n,m,top=0,a[N],ans[N];

priority_queue<Node1> Q1;
priority_queue<Node2> Q2;

int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    Op t;
    for(int i=1;i<=m;i++){
        t.op=read(),t.x=read();
        while(top&&t.x>=sta[top].x) top--;
        sta[++top]=t;
    }
    for(int i=n;i>sta[1].x;i--) ans[i]=a[i];
    for(int i=1;i<=sta[1].x;i++)
        Q1.push((Node1){a[i],i}),Q2.push((Node2){a[i],i});
    int pos=1;
    for(int i=sta[1].x;i;i--){
        if(pos<top&&i<=sta[pos+1].x) pos++;
        if(sta[pos].op==1){
            while(!Q1.empty()&&vis[Q1.top().pos]) Q1.pop();
            Node1 now=Q1.top(); Q1.pop();
            vis[now.pos]=1,ans[i]=now.x;
        }else{
            while(!Q2.empty()&&vis[Q2.top().pos]) Q2.pop();
            Node2 now=Q2.top(); Q2.pop();
            vis[now.pos]=1,ans[i]=now.x;
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}
```

### Tips
好像可以不用堆，排序就可以了，做题的时候瓜了……

---

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF631C)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf631c)内食用可能更佳吧。

~~集训时神仙数据点水过的题，赶快来补篇题解。~~
## 思路分析
首先非常浅显的暴力肯定都能想到，既然题目让我们排序，那我们就直接暴力排序前面的数。（当然，肯定过不了。）

接着我们就想到了一个优化：前面要排序的那么多个数，如果最后来了一个要排序的长度更长的。那就会覆盖掉前面所有的，所以我们先找到这个最长的。接着暴力操作后面的排序。（集训时也是成功这样水过去了。）

接着我们就想到了正解：因为最长的前面都是被覆盖的，所以还是先找到最长的，接着后面的操作我们考虑每一次操作的右端点。从后往前枚举右端点，如果这个右端点是有一个操作而且在目前的操作之后的，那就更新当前操作为这个操作。否则就继续当前的操作。对于每一个位置 $i$，因为从后往前枚举次次更新，所以这个 $a_i$ 在这一次操作更新后就不会再有更改了，只要得到这次操作中他的值便可以了。

描述起来有点难，听起来也有点难懂，对着样例画两张图就好理解多了。（推荐尝试）
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,maxx;
int a[200010],ans[200010];
int id[200010],op[200010];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
signed main()
{
	n=read();q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,opt,r;i<=q;i++)
	{
		opt=read(),r=read();
		id[r]=i;op[r]=opt;maxx=max(maxx,r);//找到最长的那次操作
	}
	sort(a+1,a+1+maxx);
	int mq,now=0,dt=1,dw=maxx;
	for(int i=maxx;i>=1;i--)
	{
		if(now<id[i]) now=id[i],mq=op[i];//如果这个端点的操作在现在执行 操作之后就更换成这个操作。
		if(mq==1) ans[i]=a[dw--];//如果是从小到大排序，拿出后面的
		else ans[i]=a[dt++];//否则拿出前面的
     //因为前面已经有一个最长的了，所以后面的操作都是在一个已经排序好了的数列上操作的
	}
	for(int i=1;i<=maxx;i++) printf("%lld ",ans[i]);
	for(int i=maxx+1;i<=n;i++) printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：free_fall (赞：2)

# 题目大意
给定 $n$ 个整数组成的序列和 $m$ 个操作，每个操作给定 $t_i$ 和 $r_i$，操作分为两种：
- $t_i$ 为 $1$，则将前 $r_i$ 个数按照连续不减序（从小到大）排列；
- $t_i$ 为 $2$，则将前 $r_i$ 个数按照连续不增序（从大到小）排列。

求 $m$ 次操作过后的序列。
# 思路
先看数据范围，果断排除 $O(n^2)$ 的写法。

~~知周所众~~，能够离线就不要在线处理，把每一次的操作记下来，我们就能够发现有些情况完全没有必要排序：

1. $t_i$ 相同，$r_i$ 比 $r_{i-1}$ 小时，已经处于有序状态，不需要排序，直接忽略这种情况。
2. $r_i$ 比 $r_{i-1}$ 大时，排完序后将前一种情况覆盖了，也可以将前一种情况忽略。

**所以最后我们得到的操作是一个 $r_i$ 单调递减的数组**，可以用单调栈来维护这个数组。最后用一个 $ans$ 数组记录答案，注意，此时可以不用 ```sort``` 来将每一次操作都排序，会时间超限。
# 代码
```
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+5;
int n,m,a[N],top,ans[N];
struct kk{
	int t,r;
};
kk st[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		int t,r;
		scanf("%d%d",&t,&r);
		while(top&&st[top].r<=r)top--;
		st[++top]={t,r};
	}
	sort(a+1,a+st[1].r+1);
	int now=1,l=0,r=st[1].r+1;
	for(int i=r;i<=n;i++){
		ans[i]=a[i];
	}
	for(int i=r-1;i>=1;i--){
		if(i<=st[now+1].r&&now+1<=top)now++;
		if(st[now].t==1)ans[i]=a[--r];
		if(st[now].t==2)ans[i]=a[++l];
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：ggtmjts (赞：2)

    这题用到的是单调栈，举个例子：
    1 3 
    2 4
    这2种操作，我们可以发现1 3这个操作会被2 4这个操作覆盖掉
    相当于白做，我们可以用这个思路用单调栈删去没用的操作
    来加快时间。另外，如果进栈时两种操作一样，这个进栈操作
    也是浪费时间，不用进。
    再举个例子，假设单调栈做完后的操作是：
    2 4 
    1 2 
    2 1
    我们可以分段，分成4 3 放最小的，2放最大的，1放最小的
    所以用到了排序，加个l、r指针指向最小和最大
    注意有些数没有进行操作过，可以直接输出。
    具体看代码。
    代码：
    var n,m,i,x,y,t,l,r,w,o:longint;
     a,b,c,f:array[0..300000]of longint;
	procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
	begin
	readln(n,m);
   	for i:=1 to n do read(a[i]);
	 for i:=1 to m do
	  begin
	  read(x,y);
	  while(t>0)and(b[t]<=y)do dec(t);//单调栈删去没用的操作
	  if c[t]<>x then   //判断2种操作是不是一样的
	   begin
	   inc(t);
	   c[t]:=x;b[t]:=y;
	   end;
 	 end;
	sort(1,b[1]);        //排序
	l:=1;r:=b[1];      //lr指针
	w:=1;b[t+1]:=0;     //w指向下一个操作  
	for i:=b[1]downto 1 do
 	 begin
	  if i=b[w]then    //目前这个操作做完了
	    begin
	    o:=c[w];inc(w); //保持指令
	    end;
 	 if o=1 then
	    begin
	    f[i]:=r;     //放最大的位置
	    dec(r);
 	    end
	  else
        begin         //放最小的位置
	    f[i]:=l;
	    inc(l);
	    end;
 	  end;
	for i:=1 to b[1]do write(a[f[i]],' ');  //输出操作过的数
	for i:=b[1]+1 to n do write(a[i],' ');  //输出没操作过的
	end.

---

## 作者：EuphoricStar (赞：1)

## 思路

题目肯定不会让你真去维护个什么支持排序的数据结构。

手玩几组数据我们会发现，如果存在 $i,j$（$i < j$），满足 $r_i \le r_j$，那么操作 $i$ 是不起作用的。

于是我们弄一个单调栈，每次弹出前面所有 $r_j$ $\le$ 当前 $r$ 的元素，最终就形成了一个从栈底到栈顶 $r_i$ 严格递减的栈。因为 $r_i$ 是严格递减的，所以可以很轻松地实现排序了，使用 STL 的 `priority_queue` 或者 `multiset` 都可以完成。

## 代码

[code](https://pastebin.ubuntu.com/p/9nSVXYyv2B/)

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF631C)

# 思路

首先会想到暴力排序的做法，然后你会得到几个优美的 TLE，我们思考离线算法。因为每次排序会覆盖一段序列，假设当前枚举到 $ r_i $，如果 $ r_{i-1} \lt r_i $，我们就不用考虑，按照当前的 $ r_i $ 进行排序就行，最后处理的 $ r_i $ 是单调的，直接用数组模拟栈维护单调性，最后数组存储输出就行。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+10; 
struct node{
	int first,second;
}st[N];//first存储当前操作编号，second存储操作目标，这个就是模拟的单调栈 
int n,m,a[N],ans[N],tmp,l,r,counter;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++){
		int t,r;
		cin>>t>>r;//读入 
		while(tmp && st[tmp].second<=r) //判断r[i]的单调性 
			tmp--;
		st[++tmp]={t,r};//放进栈里 
	}
	r=st[1].second+1;
	counter=1;
	sort(a+1,a+r);//先将数组排序 
	for(int i=r-1;i>=1;i--){//从r[i]-1开始遍历栈 
		if(i<=st[counter+1].second && counter+1<=tmp) 
			counter++;//边界 
		if(st[counter].first==1)
			ans[i]=a[--r];//操作1 
		else
			ans[i]=a[++l];//操作2 
	}
	for(int i=1;i<=st[1].second;i++)
		cout<<ans[i]<<" ";//前r[i]个排序后的情况 
	for(int i=st[1].second+1;i<=n;i++)
		cout<<a[i]<<" ";//后面没有被排序的情况 
	//用离线算法减少了每次排序带来的时间复杂度，找到r[i]的单调性后直接维护即可 
	return 0;
}
```


---

## 作者：ZCETHAN (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF631C)

## 题目大意
给出一个长度为 $n$ 的序列 $a$，并且有 $m$ 个操作，每个操作包含一个 $t_i$ 和 $r_i$。若 $t_i=1$，则将 $a$ 中前 $r_i$ 个从小到大排序。若 $t_i=2$，则将 $a$ 中的前 $r_i$ 个从大到小排序。

求最终的序列 $a$。
## Solution
首先有一个显而易见的结论，如果某个操作之后有一个 $r$ 大于等于该操作，那么当前操作相当于白给，因为之后会被覆盖。（这与 $t$ 无瓜）

因此，我们总是可以将任意序列转化成一个 $r$ 单调降序的序列。这个只要用单调栈维护就可以了，这里不再赘述，复杂度 $O(n)$。

然后考虑任意相邻的两个操作 $op_i$ 和 $op_{i+1}$。显然，前者的 $r$ 一定是大于后者的，那么在它们之间的区间内，其单调性必然是依赖于 $op_i$ 的 $t$ 的。就可以用优先队列维护。

这么说比较抽象，所以来看图吧。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210501094043608.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW5nY2hpemM=,size_16,color_FFFFFF,t_70)

每次操作我们只需要维护右图中黑色部分就可以了，显然，这部分就是整段的最大部分，而要维护最大还是最小是与操作的 $t$ 相关的。比如上图就是给出了 $op_i$ 的 $t$ 是 $1$ 而 $op_{i+1}$ 的 $t$ 是 $2$ 的情况。

因此需要一个大根堆和小根堆来维护。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
#define INF 1ll<<60
using namespace std;
int read(){
	int w=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=w*10+c-'0';c=getchar();}
	return w*f;
}
const int MAXN=2e5+10;
struct node{
	int t,r;
	void input(){
		t=read();r=read();
	}
}stk[MAXN];
int top,a[MAXN];
priority_queue<int> ge;
priority_queue<int,vector<int>,greater<int> > le;
int main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++){
		node tmp;tmp.input();
		while(top&&stk[top].r<=tmp.r) top--;
		stk[++top]=tmp;//单调栈维护严格下降序列
	}
	for(int i=1;i<=stk[1].r;i++)
		le.push(a[i]),ge.push(a[i]);//由于只有前最大的 r 个数会参与，所以优先队列只存前 stk[1].r 个
	int p=stk[1].r;
	stk[top+1].r=0;
	for(int i=1;i<=top;i++){
		int T=stk[i].r-stk[i+1].r;
		while(T--){
			if(stk[i].t==1)
				a[p]=ge.top(),ge.pop();//选取最大的填入
			else a[p]=le.top(),le.pop();
			p--;
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：HH_Halo (赞：0)

[另一种食用方式](https://www.cnblogs.com/hhhhalo/p/13802999.html)

## 思路分析
* 题面翻译的非常简洁明了又准确。~~不知道有多少人像我一样只优化了一丢丢就开始sort~~
* 然后应该基本上都会想到这个很显然的性质：如果前面的修改操作的右端点小于后面操作的右端点，那么这次操作其实就是无效的，因为会被覆盖掉
* 所以就很容易挑选出有效的操作次数，而被筛选操作是这样的：**编号越小的修改所覆盖的区间越大**，也就是覆盖区间的长度是**单调递减**的。如果不满足单调递减，那么前面一定会有操作会被覆盖。
* 那么这个性质怎么用？其实上面说了，就是因为 `sort` 太多了所以 $TLE$ 掉了，而这时候在这个性质下，完全不必 `sort`，而是可以直接赋值的。方法就是先排序，然后两次被挑选出的操作的端点之间直接赋值。在上面的性质的下，这样的正确性是有保证的

详见代码

## $Code$
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define R register
#define N 200010
using namespace std;
inline int read(){
	int x = 0,f = 1;
	char ch = getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,a[N],c[N],flag[N];
struct data{
	int opt,pos;
}b[N];
inline bool cmp(int x,int y){return x>y;}
int main(){
	n = read(),m = read();
	for(R int i = 1;i <= n;i++)a[i] = read();
	for(R int i = 1;i <= m;i++){
		b[i].opt = read(),b[i].pos = read();
	}
	int mx = 0;
	for(R int i = m;i;i--){//倒序处理出每次操作的后面的操作覆盖的最大区间
		flag[i] = mx;
		mx = max(mx,b[i].pos);
	}
	for(R int i = 1;i <= mx;i++)c[i] = a[i];//c数组用于下面原数组的赋值
	sort(c+1,c+1+mx,cmp);
	int l = 1,r = mx;
	for(R int i = 1;i <= m;i++){
		if(flag[i]>=b[i].pos)continue;
		if(b[i].opt==1){
			for(R int j = 0;b[i].pos-j>flag[i];j++){//从右端点开始赋值，一直到下一次操作的端点
				a[b[i].pos-j] = c[l++];//从大的开始拿
			}
		}else{
			for(R int j = 0;b[i].pos-j>flag[i];j++){
				a[b[i].pos-j] = c[r--];//从小的开始拿
			}
		}
	}
	for(R int i = 1;i <= n;i++)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：zythonc (赞：0)

### 【分析过程】
先看数据范围：200000，排除 $O(n^2)$

然后仔细看题，我们会发现几个很有趣的地方：

- 对序列操作不是对 $[l,r]$ 这个区间操作，而是对 $[1,r]$ 操作
- 这个操作不是区间翻转，区间加法或其他操作，而是**排序**

容易发现当有两次操作
```
t1 r1
t2 r2
```
时

如果 $r_2\geq r_1$

那么显然第一次的操作是没有任何用的

**因为不管第一次怎么排序，第二次操作都会将其覆盖掉**

至此，我们可以发现这些操作可以用一个单调栈来维护

最后栈中就会是这样一个样子：
```
t1 r1
t2 r2
......
ti ri
```
其中 $r_1>r_2>\dots>r_i$

对于栈中的两个**连续**二元组 $(t_1,r_1),(t_2,r_2)$

其中 $r_1>r_2$

我们按照 $t_1$ 所对应的排序法则排序，然后 $(r_2,r_1]$ 的每个位置对应的数就确定了

因为直接排序复杂度较高，这里我们用两个变量 $le,re$ 作为左右指针来使用

### 【代码实现】
```
#include<iostream>
#include<algorithm>
#define N 500001
using namespace std;
struct Node{
	int t,r;
}stk[N];
int in[N],n,m,t,r,top,ans[N],le,re,now;
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>in[i];
	for(int i=1;i<=m;i++){
		cin>>t>>r;
		while(top&&stk[top].r<=r) top-=1;
		stk[++top]={t,r};
	}
	re=stk[1].r+1;now=1;
	sort(in+1,in+re);
	for(int i=re-1;i>=1;i--){
		if(i<=stk[now+1].r&&now+1<=top) now+=1;
		if(stk[now].t==1)
			ans[i]=in[--re];
		else
			ans[i]=in[++le];
	}
	for(int i=1;i<=stk[1].r;i++)
		cout<<ans[i]<<" ";
	for(int i=stk[1].r+1;i<=n;i++)
		cout<<in[i]<<" ";
}
```

---

## 作者：Level_Down (赞：0)

### 题意简述

给定 $n$ 和 $n$ 个数，$m$ 次操作，每次操作给定 $li$ 和 $ri$。

若 $li$ 为1，则将前 $ri$ 个数从小到大排列；

若 $li$ 为2，则将前 $ri$ 个数从大到小排列；

输出最终数列。

### 方法

首先暴力不可能，正解方法我也是在看了题解后想到的，所以方法大致和其他题解相同，但代码的实现换了比其他题解更好理解的方法。

再输入后的第一步，我们要先筛选出有用的操作，比如：

```
1 3
2 4
```
中的 `1 3` 就是没用的，会被 `2 4` 覆盖掉。

可以发现能从后往前，对于每个 $ri$，往前遍历，删除所有 $rj$ 小于 $ri$ 的操作。

代码实现：

```cpp
for (int i = m; i >= 1; i)
		{
			int j = i - 1;
			while(tt[i] >= tt[j]) j--;//tt就是上文提到的r，但由于不是最终答案，所以用tt暂存。
			x[++cnt].l = t[i],x[cnt].r = tt[i],i = j;//x.l和x.r就是最终答案。
		}
```

第二步，我们需要先将 $l$ 和 $r$ 按 $r$ 的大小从大到小排序。

我们发现，我们可以将答案序列切成 $cnt + 1$ 个部分，最右边的部分，也就是从头到尾没有排过序的部分保持不动。

剩下 $cnt$ 个部分，每部分长度是 $x[i + 1].r + 1$ ~ $x[i].r$ 如果 $x[i].l$ 值为1，那这部分选取剩下的原数组的数中最大的那些，反之选最小的，存入答案数组当中。

代码实现：

```cpp
	sort(x + 1,x + 1 + m,cmp);
	for (int i = x[1].r + 1; i <= n; i++) ans[i] = a[i];
	sort(a + 1,a + 1 + x[1].r);
   //注意是a + 1 + x[1].r，x[1].r 之后的部分不改动所以不需要。
	p = 1,q = x[1].r;//指针。
	for (int i = 1; i <= cnt; i++)//如上所述。
		{
			for (int j = x[i].r; j > x[i + 1].r; j--)
				{
					if (x[i].l == 1)
						{
							ans[j] = a[q],q--;
						}
						else
							{
								ans[j] = a[p],p++;
							}
				}
		}
```

第三步，输出（不讲了不讲了）。

至此，可以AC本题，速度全洛谷第二（当时是的）。

[完整代码](https://www.luogu.com.cn/paste/6na940k6)

---

