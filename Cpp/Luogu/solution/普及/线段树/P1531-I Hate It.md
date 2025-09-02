# I Hate It

## 题目背景

很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。这让很多学生很反感。


## 题目描述

不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。


## 样例 #1

### 输入

```
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5```

### 输出

```
5
6
5
9
```

# 题解

## 作者：JOHNKRAM (赞：55)

最基本的线段树。

用线段树求最值、动态更新值应该都会吧？？？

可以当做线段树练手题。


---

## 作者：JeffWang2019 (赞：46)

## 这题找好方法是很简单的

不过遇上读入字符的时候尽量用cin，否则会发生命案（~~就像本人刚刚开始做的时候一样~~）

题目的思路也比较清晰，处理时写个for循环，先判断第一个字符是Q还是U

如果是Q的话：

```cpp
        if(c[i]=='Q')
        {
            int t=-2006;
            for(int j=a[i];j<=b[i];j++)//挨个检查
            {
                if(s[j]>t)//如果比t大
                {
                    t=s[j];
                }
            }
            cout<<t<<endl; //打印，换行
        }
```

t就随便取一个负值，再与区间内的数逐个比较，并实时更新最大值，最后打印

如果是U，就更新学生的分值

```cpp
        else//接前面，如果不是Q就是U
        {
            if(s[a[i]]<b[i])//简单判断一下
            {
                s[a[i]]=b[i];
            }
        }
```

## 下面附上AC代码：

```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
int a[5005],b[5005],s[200005];//a和b表示输入指令内容，s表示成绩
char c[5005]; //指令类型
int n,m;
int main()
{
    cin>>n>>m;//输入n，m
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];//输入学生成绩
    }
    for(int i=1;i<=m;i++)
    {
        cin>>c[i]>>a[i]>>b[i];//输入每一条指令
    }
    //前面都是读入，下面是重点
    for(int i=1;i<=m;i++)//枚举每一条指令的for循环
    {
        //前面已经给出此处思路所以不再重复
    	if(c[i]=='Q')//如果是Q
        {
            int t=-2006;//随便起哪一个负值都可以
            for(int j=a[i];j<=b[i];j++)//比较判断大小的for循环
            {
                if(s[j]>t)
                {
                    t=s[j];
                }
            }
            cout<<t<<endl;//打印，记得换行，注意格式
        }
        else//如果是U
        {
            //同样前面已经给出思路不再重复
            if(s[a[i]]<b[i])
            {
                s[a[i]]=b[i];
            }
        }
	}
    return 0;//完美的结束
}
```

# 来个赞呗，深夜辛辛苦苦写的

---

## 作者：iamzq (赞：45)

# ~~此题甚水~~
我这个今年才想去普及组的小蒟蒻突然觉得自己好强

最近心情不好，就去找一道线段树的题做做，看到这题心情大好

不用lazy表，就正正常常的单点修改，区间询问，正是给我改码风的最佳机会

不废话了

刚才说过，就是单点修改，区间询问，类似于模板题

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001], tree[800001];
void pushup(int rt)
{
	tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}
void build(int rt, int l, int r)//建树
{
	if (l == r)
	{
		tree[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
void modify(int rt, int l, int r, int x, int y)//单点修改
{
	if (l == r)
	{
		if (tree[rt] < y) tree[rt] = y;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify(rt << 1, l, mid, x, y);
	else modify(rt << 1 | 1, mid + 1, r, x, y);//找询问的点在哪个节点上
	pushup(rt);
}
int query(int rt, int l, int r, int x, int y)//区间询问
{
	if (x <= l && r <= y) return tree[rt];
	int mid = (l + r) >> 1, ans = -1e9;
	if (x <= mid) ans = max(ans, query(rt << 1, l, mid, x, y));//询问的一部分在左儿子的管辖范围内
	if (y > mid) ans = max(ans, query(rt << 1 | 1, mid + 1, r, x, y));//一部分在右儿子范围内
	return ans;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		char ope[100];
		int x, y;
		scanf("%s%d%d", ope, &x, &y);
		if (ope[0] == 'Q') printf("%d\n", query(1, 1, n, x, y));
		else modify(1, 1, n, x, y);
	}
 } 


```


---

## 作者：da32s1da (赞：45)

这个题是线段树不错，但是树状数组也可以做出来！！
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,m,a[200001],d[200001],b,c,ans;
char cc;
inline void rad(long long &noi)    //快读 
{
    bool mark=false;
    static char ch;
    while(ch=getchar(),ch<'0'||ch>'9') if(ch=='-') mark=true;
    noi=ch-'0';
    while(ch=getchar(),ch<='9'&&ch>='0') noi=(noi<<3)+(noi<<1)+ch-'0';
    if(mark) noi=-noi;
}
int main()
{
    rad(n);rad(m);
    for(int i=1;i<=n;i++)
    {
        rad(a[i]);            //读入学生成绩 
    	for(int j=i;j<=n;j+=(j&(-j)))
    	d[j]=max(d[j],a[i]);        //存放最大值 
    }
    for(int i=1;i<=m;i++)
    {
    	cin>>cc;
    	if(cc=='U')             //改学生成绩 
    	{
    		rad(b);rad(c);a[b]=max(a[b],c);
    		for(int j=b;j<=n;j+=(j&(-j)))
    		d[j]=max(d[j],c);            //修改最大值 
    	}
    	else
    	{
    		rad(b);rad(c);ans=0;
    		//重点！！！！！ 
    		while(b<=c)                //起点小于终点的时候停止 
            {
                while(c-(c&(-c))>=b)    //若终点减去lowbit仍然大于起点 
                {
                    ans=max(ans,d[c]);  //更新ans和终点位置 
                    c-=c&(-c);
                }                     //做完while，终点减去lowbit小于起点 
                ans=max(ans,a[c]);c--;   //重点！！终点-1，避免减去lowbit小于起点 
            }
            printf("%lld\n",ans);
    	}
    }
    return 0;
}
```
~~听说有人说树状数组不能修改查询最大值~~
#### **下面我们来模拟一下，假如要求$2-15$之间的最大值。**
- $c=15$
- $c=14$
- $c=12$
- $c=8 $

------------
此时$while$退出，$c-1=7$

------------

- $c=7$
- $c=6$
- $c=4$

------------
此时$while$退出，$c-1=3$

------------
- $c=3$
- $c=2$
 

------------
#### 结束!!
树状数组跑的还挺快，不加氧气$100ms$，加入氧气氧化$50ms$。希望对大家能有所帮助。


---

## 作者：斯茂 (赞：31)

# 模拟是个好东西
有人说这题线段树？树状数组？

其实模拟就能过了，此方法时间复杂度O(mn)，但是过了，可能是数据太水了吧......

下面是代码：
```
#include <iostream>
using namespace std;
struct stu
{
  int n, s;
};
stu s[200005];
int find(int l, int r)
{
  int i, max = -1;
  for(i = l; i <= r; i++)
    if(s[i].s > max)
      max = s[i].s;
  return max;
}
int main(int argc, char** argv) {
	int m, n, i;
	char t;
	int t1, t2;
	cin >> n >> m;
	for(i = 1; i <= n; i++)
	{
	  cin >> s[i].s;
	  s[i].n = i;
	}
	while(m--)
	{
	  cin >> t >> t1 >> t2;
	  if(t == 'Q')
	    cout << find(t1, t2) << endl;
      else
        if(s[t1].s < t2)
          s[t1].s = t2;
	}
	return 0;
}
```


---

## 作者：Snoaple (赞：11)

一道线段树，区间查询+单点更新，相对[【P3372】](https://www.luogu.org/problemnew/show/P3372)的线段树模板还简单一些

------------

### 题意

首先，不得不说，这是一个十分~~令人讨厌且~~认真负责的老师，既要查分数，又要改分数...

童鞋个数N，命令条数M，再输入一个数列，代表N个童鞋的初始分数，之后再输入M条命令的具体内容

每次输入一个命令，我们就要干以下两件事的一件

1. 输出A到B(包括A,B)的童鞋中最高的分数
2. 讲第A位童鞋的分数改为B和原来的分数的最高的一个

------------

### 思路

没什么特别的思路，基础的线段树，套两个模板即可。

1. ### 区间查询

2. ### 单点更新

正确使用模板即可AC

### 注意

单点更新的方法，是取一个最大值，并不是覆盖，所以要用判断取出一个max值

### 代码

献上P党蒟蒻的AC代码

```pascal
uses math;
var
  n,m,i,n1,n2,j:longint;
  c:char;
  a:array[1..400000] of longint;
  sum:array[1..1000000] of longint;
  procedure pushup(x:longint);
    begin
      sum[x]:=max(sum[x*2],sum[x*2+1]);
    end;
  procedure try(h,t,num:longint);
    var
      m:longint;
    begin
      if h=t then begin
       sum[num]:=a[h];exit;end;
      m:=(h+t) div 2;
      try(h,m,num*2);
      try(m+1,t,num*2+1);
      pushup(num);
    end;
  procedure update(re,tt,l,r,num:longint);
    var
      m1:longint;
    begin
      if l=r then begin
       sum[num]:=tt;exit;end;
      m1:=(l+r) div 2;
      if re<=m1 then update(re,tt,l,m1,num*2)
       else update(re,tt,m1+1,r,num*2+1);
      pushup(num);
    end;
  function query(l1,r1,l2,r2,num:longint):longint;
    var
      m2,ans:longint;
    begin
      if (l1<=l2) and (r2<=r1) then
       exit(sum[num]);
      m2:=(l2+r2) div 2;
      ans:=0;
      if l1<=m2 then ans:=max(ans,query(l1,r1,l2,m2,num*2));
      if r1>m2 then ans:=max(ans,query(l1,r1,m2+1,r2,num*2+1));
      exit(ans);
    end;
begin
  while not(eof) do
   begin
   fillchar(sum,sizeof(sum),0);
   readln(n,m);
   for i:=1 to n do
    read(a[i]);
   try(1,n,1);
   readln;
   for j:=1 to m do
    begin
     read(c);
     if c='U' then
      begin
       readln(n1,n2);
       update(n1,n2,1,n,1);
      end;
     if c='Q' then
      begin
       readln(n1,n2);
       writeln(query(n1,n2,1,n,1));
      end;
    end;
  end;
end.
```

------------

广告时间~~

[个人主页](https://www.luogu.org/space/show?uid=52724)

---

## 作者：多多良假伞 (赞：10)

[题目链接](https://www.luogu.org/problemnew/show/P1531)



## 题目背景

很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。这让很多学生很反感。

## 题目描述

不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩

## 输入输出格式

#### 输入格式：

第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。学生ID编号分别从1编到N。第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。当C为'U'的时候，表示这是一条更新操作，如果当前A学生的成绩低于B，则把ID为A的学生的成绩更改为B，否则不改动。

#### 输出格式：

对于每一次询问操作，在一行里面输出最高成绩



## 题解

根据题目要求我们可以发现，这道题要求我们维护一个数据结构，来支持单点修改和区间查询最值，于是我想到用线段树来实现。

~~我的线段树跟其他题解中不太一样，是动态开点~~

~~只是修改了一下建树操作，管理求给过~~

对于题目中的要求

> 如果当前A学生的成绩低于B，则把ID为A的学生的成绩更改为B，否则不改动。

#### 我们可以考虑在单点修改操作中用以下方式维护

```cpp
void Insert(int &now,int l,int r,int x,int k){
	if(now==0)
		now=++cnt;
	if(l==r){
		Seg[now].sum=max(Seg[now].sum,k);//按照题目要求维护线段树
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		Insert(Seg[now].L,l,mid,x,k);
	else
		Insert(Seg[now].R,mid+1,r,x,k);
	Seg[now].sum=max(Seg[Seg[now].L].sum,Seg[Seg[now].R].sum);
    //维护线段树，以使每个节点都等于它子节点的最大值
}
```

#### 对于查询操作，我们可以考虑这样维护

```cpp
int Query(int now,int l,int r,int x,int y){
	if(x<=l && r<=y)
		return Seg[now].sum;
    //如果要查询的区间比子节点代表的区间还小，直接返回子节点区间
	int mid=(l+r)>>1;
	int maxL=0,maxR=0;
	if(x<=mid)
		maxL=max(maxL,Query(Seg[now].L,l,mid,x,y));//维护查询最大值
	if(y>mid)
		maxR=max(maxR,Query(Seg[now].R,mid+1,r,x,y));//维护查询最大值
	return max(maxL,maxR);//维护查询最大值
}
```

#### 以下是完整代码

```cpp
#include<iostream>//I Hate It!!!!
#include<cstdio>
using namespace std;

struct Tree{
	int L;
	int R;
	int sum;
}Seg[800010];
int n,m,cnt,root;
int a[200010];
char C;

void Build(int &now,int l,int r){//传址调用实现动态开点
	if(now==0)
		now=++cnt;//某种意义上是动态开点核心操作了
	if(l==r){
		Seg[now].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(Seg[now].L,l,mid);
	Build(Seg[now].R,mid+1,r);
	Seg[now].sum=max(Seg[Seg[now].L].sum,Seg[Seg[now].R].sum);
    //在建树操作中维护最大值
}

void Insert(int &now,int l,int r,int x,int k){
	if(now==0)
		now=++cnt;
	if(l==r){
		Seg[now].sum=max(Seg[now].sum,k);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		Insert(Seg[now].L,l,mid,x,k);
	else
		Insert(Seg[now].R,mid+1,r,x,k);
	Seg[now].sum=max(Seg[Seg[now].L].sum,Seg[Seg[now].R].sum);
}

int Query(int now,int l,int r,int x,int y){
	if(x<=l && r<=y)
		return Seg[now].sum;
	int mid=(l+r)>>1;
	int maxL=0,maxR=0;
	if(x<=mid)
		maxL=max(maxL,Query(Seg[now].L,l,mid,x,y));
	if(y>mid)
		maxR=max(maxR,Query(Seg[now].R,mid+1,r,x,y));
	return max(maxL,maxR);
}

int main(){
	//freopen("IHate.in","r",stdin);
	//freopen("IHate.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
    Build(root,1,n);
	for(int i=1;i<=m;i++){
		cin>>C;
		if(C=='Q'){
			register int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",Query(root,1,n,x,y));
		}
		else{
			register int x,k;
			scanf("%d%d",&x,&k);
			Insert(root,1,n,x,k);
		}
	}
	return 0;
}
```

~~感觉动态开点非常好理解为什么没人用呢~~


---

## 作者：张の德天 (赞：9)

这题一看就是个线段树+单点修改。注意这里：“则把ID为A的学生的成绩更改为B，否则不改动。”调了两个小时就是wa50分，最后重看了一下题目才发现。还有一点TLE的可能是内存开太小了，~~别问我为什么，实践出真知~~。
然后贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int u,v,val;
}t[4000001];
int a[200001];
int tot = 0;
void made(int kk,int x,int y)//建树
{
	tot = max(tot,kk);
	if(x == y)
	{
		t[kk].u = x;
		t[kk].v = y;
		t[kk].val = a[x];
		return;	
	}
	int mid = (x+y)/2;
	made(kk*2,x,mid);
	made(kk*2+1,mid+1,y);
	t[kk].u = x;
	t[kk].v = y;
	t[kk].val = max(t[kk*2].val,t[kk*2+1].val);
	return;
}
int ans(int x,int y,int u)//询问
{
	if(y >= t[u].v && x <= t[u].u) return t[u].val;
	if(t[u].u > y||t[u].v < x) return 0;//优化，不然询问nlogn
	return max(ans(x,y,u*2),ans(x,y,u*2+1));
}
void change(int u,int k,int b)//修改
{
	if(k == t[u].u && k == t[u].v)
	{
		t[u].val = max(t[u].val,b);
		return;
	}
	change(u*2+(k > t[u*2].v),k,b);
	t[u].val = max(t[u*2].val,t[u*2+1].val); 
	return;
}
int main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("testdate.txt","w",stdout);
	int n,m;
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
	}
/*	for(int i = 1;i <= n;i++)
	{
		printf("%d ",a[i]);
	}*/
	made(1,1,n);
	/*for(int i = 1;i < tot;i++)
	{
		printf("%d %d %d\n",t[i].u,t[i].v,t[i].val);
	}*/
	for(int i = 1;i <= m;i++)
	{
		char C;
		cin >> C;
		if(C == 'Q')
		{
			int from,to;
			scanf("%d%d",&from,&to);
			printf("%d\n",ans(from,to,1));
		}
		else if(C == 'U')
		{
			int k,b;
			scanf("%d%d",&k,&b);
			change(1,k,b);
		}
	}
	return 0;
}
```

---

## 作者：冽酒灬忄 (赞：9)

这个题超级超级超级裸的线段树~~（线段树是个好东西）~~

因为不会用树状数组，所以本蒟蒻来一手线段树~~（大佬勿喷）~~

史上最好懂的线段树~~之一~~

```cpp
//by zzl
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long aa[500001],k,n,m;
long long init(int n_)
{
    n=1;//为了方便，将叶节点数扩大到2的幂
    while(n<=n_){n=n*2;}
}
long long add(int k,int x)
{
    k=k+n-1;
    aa[k]=x;//将第k个叶节点修改成x
    while(k>0)
    {
        k=k/2;//向上修改最大值
        aa[k]=max(aa[k*2],aa[k*2+1]);
    }
}
long long check(int a,int b,int k,int l,int r)//a,b是所求区间范围，k是当前节点编号，l，r是第k号节点的所管区间
{
    //注意：根节点为1
    if(r<a||l>b)
        return 0;//如果该节点所管区间与要求区间不重合，返回0
    if(a<=l&&r<=b)
        return aa[k];//如果该节点所管区间完全包含于所求区间，返回该节点的值。
    else
    {
        long long maxl=check(a,b,k*2,l,(l+r)/2);//左孩子
        long long maxr=check(a,b,k*2+1,(l+r)/2+1,r);//右孩子
        return max(maxl,maxr);//返回两个孩子的最大值
    }
}
int main()
{
    cin>>n>>m;
    int nn=n;
    init(n);//初始化
    for(int i=1;i<=nn;i++)
    {
        int x;
        cin>>x;
        add(i,x);
    }    
    for(int i=0;i<m;i++)
    {
        char b;
        cin>>b;
        int l,r;
        cin>>l>>r;
        if(b=='U')//修改
        {
            if(aa[l+n-1]<r)
                add(l,r);
        }
        if(b=='Q')//查询
            cout<<check(l,r,1,1,n)<<endl;//要从根节点开始搜索
    }
    return 0;
}
```

---

## 作者：KenLi (赞：8)

**这题就是普通线段树的模板，区间查询+单点修改的，外加一个特判。**

貌似没有看到有人用zkw线段树的，我来发一篇。

什么是zkw线段树？

简单来说，就是非递归式线段树，由清华大学神犇zkw（张昆玮）发明，并在ppt《统计的力量中》发表.

众所周知，递归式线段树的常数很大，经常被卡。而zkw线段树的常数很小，而且有足够大的优化空间 ，~~比如让你理解到怀疑人生的位运算~~（详细测评见[洛谷日报第46期](https://baijiahao.baidu.com/s?id=1611019207439457255&wfr=spider&for=pc)）

zkw线段树无论是建树、查询、修改都与递归式线段树相反，是自底向上的，而且空间直接开到大于等于2倍maxn的二的次幂。

具体来说，就是先把线段树填充成满二叉树（堆式存储），之后就可以直接找到叶节点，然后回溯上去了

听起来好像很简单QwQ

~~其实真的很简单QwQ~~

建树：

```cpp
inline void print(){
    for(bit=1;bit<=n+1;bit<<=1);//bit就是树的最底层的起始位置
    for(register int i=bit+1;i<=bit+n;++i){
        cin>>tree[i];
    }//直接从bit位置开始输入，初始数据存在最底层
	for(register int i=bit-1;i;--i){
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
        //i<<1等价于i/2，i<<1|1等价于i/2+1
    }
}
```

单点修改：

```cpp
inline void update(int ind,int val){
    tree[bit+ind]=val;//直接从最底层修改
    for(register int i=(bit+ind)>>1;i;i>>=1){//从它的父节点开始自底向上修改
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
    return;
}
```

区间查询的代码有点费解，如下图：

![](https://ss0.baidu.com/6ONWsjip0QIZ8tyhnq/it/u=2016267690,634916127&fm=173&app=25&f=JPEG?w=640&h=244&s=01B46D321F8548431CFD1DCC0000B0B2)

要查询区间[2,7]的值，先把他变成开区间，如下图中的s和t：
![](https://ss0.baidu.com/6ONWsjip0QIZ8tyhnq/it/u=1929268662,309943542&fm=173&app=25&f=JPEG?w=640&h=244&s=4194ED331F8548431CDD9DDC0000B0B1)

接着不断将s,t移动到对应节点的父节点处，直到s,t指向的节点的父节点相同时停止：

![](https://ss1.baidu.com/6ONXsjip0QIZ8tyhnq/it/u=127265425,3249937611&fm=173&app=25&f=JPEG?w=640&h=244&s=4194ED321F8548435ED99CC8020090B1)

在这期间，如果：

s指向的节点是左儿子，那么ans=max(ans,右儿子的值)

t指向的节点是右儿子，那么ans=max(ans,左儿子的值)

直到s和t互为兄弟节点为止

（图片转载自[洛谷日报第46期](https://baijiahao.baidu.com/s?id=1611019207439457255&wfr=spider&for=pc)）

区间查询代码：

```cpp
inline int query(int left,int right){
    int ans=-0x7fffffff;
    for(left+=bit-1,right+=bit+1;left^right^1;left>>=1,right>>=1){
    	//第一个分号前的就是将闭区间转换成开区间,相当于上面的s和t,加上bit是因为从最底层开始
		//left^right^1就是判断它们是否互为兄弟节点 
        if(~left&1){//判断它指向的节点是否为左儿子 
            ans=max(ans,tree[left^1]);
            //满足条件的情况下left^1等价于left+1 
        }
        if(right&1){//判断它指向的节点是否为右儿子
            ans=max(ans,tree[right^1]);
            //满足条件的情况下right^1等价于right-1 
        }
    }
    return ans;
}
```

以下是完整代码（不要忘了加特判）：

```cpp
#include<bits/stdc++.h>
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
int n,m,tree[1048576],bit;
inline void build(int n){
    for(bit=1;bit<=n+1;bit<<=1);
    for(register int i=bit+1;i<=bit+n;++i){
        cin>>tree[i];
    }
    for(register int i=bit-1;i;--i){
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}
inline void update(int ind,int val){
    tree[bit+ind]=val;
    for(register int i=(bit+ind)>>1;i;i>>=1){
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
    return;
}
inline int query(int left,int right){
    int ans=-0x7fffffff;
    for(left+=bit-1,right+=bit+1;left^right^1;left>>=1,right>>=1){
        if(~left&1){
            ans=max(ans,tree[left^1]);
        }
        if(right&1){
            ans=max(ans,tree[right^1]);
        }
    }
    return ans;
}
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>m;
    build(n);
    for(register int i=1;i<=m;++i){
    	char c;
        int a,b;
        cin>>c>>a>>b;
        switch(c){//switch和case纯粹是我个人喜好，实在不习惯可以改成if
            case'Q':{
                cout<<query(a,b)<<endl;
                break;
            }
            case'U':{
            	if(tree[bit+a]<b){//特判在这里qwq
            		update(a,b);
				}
                break;
            }
            default:{
                break;
            }
        }
    }
    return 0;
}
```

吸了氧能达到78ms（递归式线段树196ms）

~~自认为码风很好Orz~~

---

## 作者：wwq123 (赞：8)

1.这是我第一次没看题解写出线段树（虽然是裸得）所以发篇题解纪念一下

2.这题做法多样，树状数组也可以做，但还是推荐线段树

3.先用buildtree建树，然后update更新，query则用来查询

4.函数中的 l 表示左边界，r 表示右边界，x 则是当前节点

5.代码在线段树中算是比较短的，可放心食用

下面是代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=800000+2;
struct edge{
    int l,r,mx;
}tree[MAXN];
int a[MAXN];
int n,m;
void buildtree(int x,int l,int r){
    tree[x].l=l;
    tree[x].r=r;
    if(l==r){
        tree[x].mx=a[l];
        return;
    }
    buildtree(x*2,l,(l+r)>>1);
    buildtree(x*2+1,1+((l+r)>>1),r);
    tree[x].mx=max(tree[x*2].mx,tree[x*2+1].mx);
}
void update(int x,int l,int r,int k){
    if(tree[x].l>=l && tree[x].r<=r){
        tree[x].mx=max(tree[x].mx,k);
        return;
    }
    if(tree[x].l>r || tree[x].r<l) return;
    update(x*2,l,r,k);
    update(x*2+1,l,r,k);
    tree[x].mx=max(tree[x*2].mx,tree[x*2+1].mx);
}
int query(int x,int l,int r){
    if(tree[x].l>=l && tree[x].r<=r) return tree[x].mx;
    if(tree[x].l>r || tree[x].r<l) return 0;
    int ans=0;
    ans=max(query(2*x,l,r),query(2*x+1,l,r));
    return ans;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    buildtree(1,1,n);
    for(int i=1;i<=m;i++){
        char pd;
        int x,y; 
        cin>>pd;
        if(pd=='Q'){
            cin>>x>>y;
            cout<<query(1,x,y)<<endl;
        }
        else{
            cin>>x>>y;
            update(1,x,x,y);
        }
    }
    return 0;
}
```

---

## 作者：111l (赞：6)

# 这道题线段树才是正解！！！只有线段树才是正义的！！！

~~然而我只会树状数组，怎么办呢？~~

首先，这确实是一道线段树裸题，但我这个人就是比较懒，线段树码量太大啦！

于是我们来尝试一下树状数组......


------------
关于树状数组的功能，我也不多说~~，能做这道题的人肯定也A了BIT模板嘛~~，无非就两个：前缀和，单点加值。

但是，我们~~伟大~~的树状数组能做到的不止这些，具体看代码。


------------

```cpp
#include<cstdio>
int n,m,a[211111];
int c[211111];//c为树状数组
char ch;
inline int max(int a,int b){return a>b?a:b;}//题目要求取大
inline int lowbit(int x){return x&-x;}//lowbit函数：求某一个数的二进制下最低的一位1
void build(int x){//建树，存放学生的成绩最大值
	for(int i=1;i<=x;i++){
		c[i]=a[i];
		int t=lowbit(i);
		for(int j=1;j<t;j<<=2){
			c[i]=max(c[i],c[i-j]);
		}
	}
}
void add(int pos,int x){//修改学生的成绩
	a[pos]=x;
	while(pos<=n){
		c[pos]=a[pos];
		int t=lowbit(pos);
		for(int j=1;j<t;j<<=1){
			c[pos]=max(c[pos],c[pos-j]);
		}
		pos+=lowbit(pos);
	}
}
int getmax(int l,int r){//找区间最大值
	int res=-(1<<30);
	if(!r) return res;
	int i=r;
	while(i>=l){
		int j=i-lowbit(i)+1;
		if(j>=l){
			res=max(res,c[i]);
			i=j-1;
		}
		else{
			res=max(res,a[i]);
			--i;
		}
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	build(n);
	for(int i=1;i<=n;i++){
		int l=i-lowbit(i)+1,r=i-1;
		scanf("%d",&a[i]);
		c[i]=max(a[i],getmax(l,r));
	}
	for(int x,y;m;m--){
		ch=getchar();
		while(ch<'A'||ch>'Z') ch=getchar();//小技巧：一个一个地读，读到字母为止
		scanf("%d%d",&x,&y);
		switch(ch){//此处你也可以写成if的形式，应该都差不多
			case 'Q':{
				printf("%d\n",getmax(x,y));
				break;
			}
			case 'U':{
				if(y<=a[x]){
					break;//太高了就不改了
				}
				add(x,y);//改分
				break;
			}
		}
	}
}
```
最后推荐你一篇文章：[传送门](https://www.luogu.org/blog/Chanis/super-BIT)

本代码参考了这篇文章。

---

## 作者：decoqwq (赞：6)

qwq~~我特别喜欢暴力分块~~，给大家介绍一下此题的分块做法

首先是分块这种算法，时间复杂度是$O(\sqrt n)$级别的，不是很快也不是很慢 ~~代码短最适合我这种懒人了~~

首先是如何分块

```cpp
block=sqrt(n);
for(int i=1;i<=n;i++)
{
	scanf("%d",&a[i]);
	belong[i]=(i-1)/block+1;//每个数属于哪一块
	maxn[belong[i]]=max(maxn[belong[i]],a[i]);//每一块维护最大值
}
```
这一题只需要维护每一块最大值即可

而查询操作主要是这样的：
```cpp
序列：1 2 3 4 5 
查询：[2,5]间最大值
可知1 2是一块，3 4是一块，5是一块
maxn[1]=2,maxn[2]=4,maxn[3]=5//每块最大值
先查询第一个不完整的块[2,2]，暴力查询最大值为2
再查询一个整块[3,4]，最大值为maxn[2]=3
最后查询不完整的快[5,5]，暴力查询最大值为5
所以[2,5]最大值为2
```
查询代码：
```cpp
int query(int x,int y)
{
	int ans=-0x3f3f3f3f;
	for(int i=x;i<=min(belong[x]*block,y);i++)//处理左边不完整块
	{
		ans=max(ans,a[i]);
	}
	if(belong[x]!=belong[y])//如果不在同一块
	{
		for(int i=(belong[y]-1)*block+1;i<=y;i++)//处理右边不完整块
		{
			ans=max(ans,a[i]);
		}
	}
	for(int i=belong[x]+1;i<belong[y];i++)//处理完整块
	{
		ans=max(ans,maxn[i]);
	}
	return ans;
}
```
因为暴力查询的点肯定小于$2 \sqrt n$，查询的块个数也小于等于$\sqrt n$，故每次查询时间复杂度为$O(\sqrt n)$，总时间复杂度$O(n \sqrt n)$

然后是修改操作，我们每一次如果进行了修改（当前数字小于被修改成的数字），判断修改后的数是否大于之前它所在块最大值，不大于就退出，大于就修改最大值即可

修改代码：
```cpp
void update(int x,int y)
{
	if(a[x]<y)//需要修改
	{
		a[x]=y;
	}
	else//不需要
	{
		return ;
	}
	if(y>maxn[belong[x]])//需要更新最大值
	{
		maxn[belong[x]]=y;
	}
	return ;
}
```

最后上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int block,n,m;
int a[200010],belong[200010],maxn[500];
void update(int x,int y)
{
	if(a[x]<y)
	{
		a[x]=y;
	}
	else
	{
		return ;
	}
	if(y>maxn[belong[x]])
	{
		maxn[belong[x]]=y;
	}
	return ;
}
int query(int x,int y)
{
	int ans=-0x3f3f3f3f;
	for(int i=x;i<=min(belong[x]*block,y);i++)
	{
		ans=max(ans,a[i]);
	}
	if(belong[x]!=belong[y])
	{
		for(int i=(belong[y]-1)*block+1;i<=y;i++)
		{
			ans=max(ans,a[i]);
		}
	}
	for(int i=belong[x]+1;i<belong[y];i++)
	{
		ans=max(ans,maxn[i]);
	}
	return ans;
}
int main()
{
	memset(maxn,-0x3f3f3f3f,sizeof(maxn));
	cin>>n>>m;
	block=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		belong[i]=(i-1)/block+1;
		maxn[belong[i]]=max(maxn[belong[i]],a[i]);
	}
	char opt[3];
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0]=='U')
		{
			update(x,y);
		}
		else
		{
			printf("%d\n",query(x,y));
		}
	}
} 
```

---

## 作者：Apro1066 (赞：4)

没有用树状数组的？其实和[P2880](https://www.luogu.org/problem/P2880)就是差不多的啊。这里写了一个树状数组求最值的板子。
```cpp
#include <stdio.h>
#include <iostream>
#include <memory.h>
using namespace std;
int n,m,a[200001],maxn[200001],minx[200001],s;
inline int lowbit(int x)
{
	return x&-x;
}
inline void update(int x,int k)//区间[x,n]修改最值 
{
	while(x<=n)
	{
		maxn[x]=max(maxn[x],k);
		x+=lowbit(x);
	}
}
inline int query(int l,int r)//区间[l,r]查询最值 
{//对比一下树状数组的查询区间和，其实还是很像的 
	register int mx(-2e9-7);
	while(l<=r)
	{
		while(r-lowbit(r)>=l)//如果右区间-lowbit还大于起点 
		{
			mx=max(mx,maxn[r]); 
			r-=lowbit(r);//更新右区间 
		}
		mx=max(a[r],mx);
		r--;//为了避免-lowbit小于左区间，所以减一 
	}
	return mx;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	memset(minx,2E9+7,sizeof(minx));
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		update(i,a[i]);//单点修改 
	}
	for(i=1;i<=m;i++)
	{
		register int l,r;
		char c;
		cin>>c>>l>>r;
		if(c=='U')//单点改 
		{
			a[l]=max(a[l],r);//把学生成绩a[l]改为r 
			update(l,r);
		}
		else//区间最值 
		{
			cout<<query(l,r)<<endl;//区间查询最值 
		}
	}
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：4)

题解 by:redbag


线段树维护最大值,还是很裸的

注意:当分数大于B的时候不要改

```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
char ch;
int a[2001000];
int i;
int n,m;
int A,B;
struct node
{
    int l,r;
    int ma;
}
t[5001000];
void bt(int l,int r,int u)//建树,一边建树一边读入
{
    t[u].l=l;
    t[u].r=r;
    if (t[u].l==t[u].r)
    {
        int aa;
        scanf("%d",&aa);
        t[u].ma=aa;
        //t[u].mi=aa;
        return;
    }
    bt(l,(l+r)/2,u*2);//左子树
    bt((l+r)/2+1,r,u*2+1);//右子树
    t[u].ma=max(t[u*2].ma,t[u*2+1].ma);//维护max
    //t[u].mi=min(t[u*2].mi,t[u*2+1].mi);
    //cout<<t[u].l<<" "<<t[u].r<<"\n";
}
void xg(int l,int r,int u,int d)
{
    if (t[u].l==l&&t[u].r==r)
    {
        t[u].ma=max(d,t[u].ma);//嗯就是这个修改的地方不能直接赋值
        return;
    }
    int mid=(t[u].l+t[u].r)/2;
    if (r<=mid) xg(l,r,u*2,d); else//左子树
    if (l>mid) xg(l,r,u*2+1,d); else//右子树
    {//两边
        xg(l,mid,u*2,d);
        xg(mid+1,r,u*2+1,d);
    }
    t[u].ma=max(t[u*2].ma,t[u*2+1].ma);//更新最大值
}
int qmax(int l,int r,int u)//求max
{
    if (t[u].l==l&&t[u].r==r)
    {
        return t[u].ma;
    }
    int mid=(t[u].l+t[u].r)/2;
    if (r<=mid) return qmax(l,r,u*2); else 
    if (l>mid) return qmax(l,r,u*2+1); else
    {
        return max(qmax(l,mid,u*2),qmax(mid+1,r,u*2+1));
    }
}
int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        bt(1,n,1);//建树
        for (i=1;i<=m;i++)//读入询问
        {
            cin>>ch>>A>>B;
            if (ch=='Q')
            {
                int hh=qmax(A,B,1);
                printf("%d\n",hh);
            }
            if (ch=='U')
            {
                xg(A,A,1,B);
            }
        }
    }
    return 0;
}
```

---

## 作者：土间太平 (赞：3)

线段树的基础模板

解法：单点更新&区间查询


------------


# 此题虽然和杭电的那题一样，却有些不同，注意洛谷上说的是成绩比原来大的时候做修改，我和好多同学一样被坑了好多次。。。



------------


看下面P党的好少，贴上~~个人认为简洁优美的~~Pas代码，希望你们且行且珍惜！


```pascal
uses math;
var a:array[1..200000]of longint;
    sum:array[1..800000]of longint;
    n,m,l,p,q:longint;
    c:char;
procedure pushup(rt:longint);
begin
 sum[rt]:=max(sum[(rt shl 1)],sum[(rt shl 1) or 1]);
end;
procedure build(l,r,rt:longint);
var mid:longint;
begin
 if l=r then
  begin
   sum[rt]:=a[l];
   exit;
  end;
 mid:=(l+r) shr 1;
 build(l,mid,rt shl 1);
 build(mid+1,r,(rt shl 1)or 1);
 pushup(rt);
end;
function query(x,y,l,r,rt:longint):longint;
var mid,ansl,ansr:longint;
begin
 if (x<=l)and(r<=y) then exit(sum[rt]);
 mid:=(l+r) shr 1;
 ansl:=0;ansr:=0;
 if x<=mid then ansl:=query(x,y,l,mid,rt shl 1);
 if y>mid then ansr:=query(x,y,mid+1,r,(rt shl 1) or 1);
 exit(max(ansr,ansl));
end;
procedure update(p,c,l,r,rt:longint);
var mid:longint;
begin
 if l=r then
  begin
   sum[rt]:=max(sum[rt],c);
   exit;
  end;
 mid:=(l+r) shr 1;
 if p<=mid then update(p,c,l,mid,rt shl 1)
 else update(p,c,mid+1,r,(rt shl 1)or 1);
 pushup(rt);
end;
begin
 readln(n,m);
 for l:=1 to n do
  read(a[l]);
 readln;
 build(1,n,1);
 for l:=1 to m do
  begin
   readln(c,p,q);
   if c='Q' then writeln(query(p,q,1,n,1))
   else update(p,q,1,n,1);
  end;
end.
```

~~帅气的管理员大大给个通过吧~~

---

## 作者：ysner (赞：3)

这题有那么难吗？？？

此题并不需要线段树这类的数据结构啊（虽然可能是此题数据过水或数据范围过小）

我模拟大法一遍过

这个故事告诉我们，就算学习了高深一点的算法和数据结构，那些基础和最实用的东西也千万千万不能忘掉。

上代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int a[200001]={};
int main()
{
    int i,j,k,n,m,total,l;
    char c;
    cin>>n>>m;
    for(i=1;i<=n;i++)
      cin>>a[i];
    for(i=1;i<=m;i++)
    {
        cin>>c>>j>>k;
        if(c=='Q')
        {
          //if(j<1) j=1;
          //if(k>m) k=m;//其实我也不知道为什么不能帮数据判错，打了这两行会全WA
          int mann=0;
          for(l=j;l<=k;l++)
            mann=max(mann,a[l]);
          cout<<mann<<endl;
        }
          else 
            a[j]=max(a[j],k);
    }
    return 0;
}
```

---

## 作者：卫宫 (赞：2)

思路简单。建树，树的节点上放区间最大值。至于改值，实在是水，比模板还简单（结果我看成了A节点和B节点交换233）（想要节点值交换的沙雕代码可以私我~~话说没人会在意这个吧~~）。还有个问题是怎么找A在树中所对应的下标，~~好像是有公式的可我忘了~~我写了个函数来求它。本质和区间求值差不多。

上代码：（为防抄袭刻意留了个小bug~~谁不知道archer就是少侠啊~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000010;//开小了会RE
long long a1,a2,a3,a4,a[maxn+2];
long long ans[maxn+2],i,n,m,lans;
char c;
struct tree{
    long long l,r;
	int pre;
}t[4*maxn+2];

void build(long long p,long long l,long long r){
    t[p].l=l;t[p].r=r;
    if(l==r){
        t[p].pre=a[l];
        return;
    }
    long long mid=(l+r)>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    t[p].pre=max(t[p*2].pre,t[p*2+1].pre);
}
void spread(long long p){
	long long mid=p>>1;
	long long emiya=max(t[mid*2].pre,t[mid*2+1].pre);//月厨的个人素养（因为实在想不出变量名）
    if (t[mid].pre<shiro){
		t[mid].pre=shiro;
		spread(mid);
    }
}//维护最大值

int ask(long long p,long long x,long long y){
    if (x<=t[p].l&&y>=t[p].r) return t[p].pre;
    long long mid=(t[p].l+t[p].r)>>1;
    int ans=0;
    if (x<=mid) ans=max(ans,ask(p*2,x,y));
    if (y>mid) ans=max(ans,ask(p*2+1,x,y));
    return ans;
}//查找最值
long long ask1(long long p,long long x){
    if (x==t[p].l&&x==t[p].r) return p;
    long long mid=(t[p].l+t[p].r)>>1;    
    long long ans=0;
    if (x<=mid) ans=ask1(p*2,x);
    if (x>mid) ans=ask1(p*2+1,x);
    return ans;
}//找A在树中所对应的下标
void change(long long p,long long x,long long y){
    if (ask(1,x,x)<y){
    	t[ask1(1,x)].pre=y;
    	spread(ask1(1,x));
        return;
    }
	
}
int main(){
    cin>>n>>m;
    for (i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for (i=1;i<=m;i++){
        cin>>c;
        if (c=='Q') {
            cin>>a2>>a3;
            lans++;
            ans[lans]=ask(1,a2,a3);
        }
        else{
           cin>>a2>>a3;
       		change(1,a2,a3);
        }
}
    for (i=1;i<=lans;i++){
        printf("%d\n",ans[i]);       
    }
}
```


---

## 作者：封禁用户 (赞：2)

1.建树

原问题：[l..r]的树的根结点为p

子问题1：[l..Mid]的树的根结点为p+p

子问题2：[Mid+1..r]的树的根结点为p+p+1

基本情况：l==r时，tree[p]=a[l];

合并：tree[p]=max(tree[p+p],tree[p+p+1]);

2.区间取最大值

原问题：[l..r]的树的根结点为p，找[x..y]中的最大值

子问题1：[l..Mid]的树的根结点为p+p，找[x..y]中的最大值

子问题2：[Mid+1..r]的树的根结点为p+p+1,找[x..y]中的最大值

子问题3：[l..Mid]的树的根结点为p+p,找[x..Mid]中的最大值

子问题4：[Mid+1..r]的树的根结点为p+p+1,找[Mid+1..y]中的最大值

基本情况：l==x&&r==y时，rturn tree[p];

合并：y<=Mid时，return 子问题1；x>Mid时，return 子问题2

否则 return max(子问题3,子问题4)

3.改变

原问题：[l..r]的树的根结点为p,找x叶结点将其改为max(y,tree[x]);

子问题1：[l..Mid]的树的根结点为p+p,找x叶结点将其改为max(y,tree[x]);

子问题2：[Mid+1..r]的树的根结点为p+p+1,找x叶结点将其改为max(y,tree[x]);

基本情况：l==r时，tree[p]=max(y,tree[x]);

合并：tree[p]=max(tree[p+p],tree[p+p+1]);

```cpp
#include <bits/stdc++.h>   //万能头文件

#define Maxn 200000  

using namespace std;

int n,m,a[Maxn+5],tree[Maxn*4+5];

void Build(int p,int l,int r)   //建树 

{
	
 if(l==r)
 
 {
 	
 	tree[p]=a[l];
 	
 	return;
 	
 }
 
 int Mid=(l+r)/2;   //有兴趣的可以去证明一下 
 
 Build(p+p,l,Mid);  //"+"比"*"快，所以我用"+"。不过你用什么，我才不管呢(滑稽)
  
 Build(p+p+1,Mid+1,r);
 
 tree[p]=max(tree[p+p],tree[p+p+1]);   //合并 
 
}

int getmax(int p,int l,int r,int x,int y)   //求区间最大 

{
	
 if(l==x&&r==y)
 
 {
 	
 	return tree[p];
 	
 }
 
 int Mid=(l+r)/2;
 
 if(y<=Mid)   //如果都在[l...Mid]区间里的话... 
 
 	return getmax(p+p,l,Mid,x,y);
 	
 else if(x>Mid)   //如果都在[Mid+1,r]区间里的话... 
 
 	return getmax(p+p+1,Mid+1,r,x,y);
 	
 else   //如果不都在[l...Mid]区间里，也不都在[Mid+1,r]区间里的话... 
 
 	return max(getmax(p+p,l,Mid,x,Mid),getmax(p+p+1,Mid+1,r,Mid+1,y));
 	
}

void change(int p,int l,int r,int x,int y)   //改变 

{
	
 if(l==r)
 
 {
 	
 	tree[p]=max(tree[p],y);
 	
 	return;
 	
 }
 
 int Mid=(l+r)/2;
 
 if(x<=Mid) change(p+p,l,Mid,x,y);
 
 else change(p+p+1,Mid+1,r,x,y);
 
 tree[p]=max(tree[p+p],tree[p+p+1]);   //更新 
 
}

int main()

{
	
 cin>>n>>m;  //输入 
 
 for(int i=1;i<=n;i++)
 
 	cin>>a[i];
 	
 Build(1,1,n);   //建树 
 
 for(int i=1;i<=m;i++)
 
 {
 	
 	int x,y;
 	
 	char s;
 	
 	cin>>s>>x>>y;
 	
 	if(s=='Q')   //如果c=='Q' 
 	
 		cout<<getmax(1,1,n,x,y)<<endl;
 		
 	else
 	
 		change(1,1,n,x,y);
 		
 }
 
 return 0;
 
}
```


---

## 作者：huangjunqi1 (赞：2)

##splay

这道题可以有很多种做法：线段数，还有分块……我是把它当作splay的区7间查询的模板题做的。

首先，将每个数按其编号大小插入树中。

查询时，将l-1旋转到树根，将r+1旋转到根的右子树。则根右子树的左子树就是要找的区间。

因为这个字树一定大于l-1，小于r+1，（即l~r）

要修改时，将要修改的那个值转到根再修改即可。

另外，还要维护以第i个节点为根的子树的最大值。

代码：

'''cpp
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int maxs[300000],fa[300000],a[300000],tr[300000][3],root,tree[300000];
void pushup(int k) //这一步很重要，维护以k为根的子树的最大值。
{
    maxs[k]=max(a[k],maxs[tr[k][0]]);
    maxs[k]=max(maxs[k],maxs[tr[k][1]]);
}
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if (tr[y][0]==x) l=0;
    else l=1;
    r=l^1;
    if (y==k) k=x;
    else
    {
        if (tr[z][0]==y) tr[z][0]=x;
        else tr[z][1]=x;
    }
    fa[x]=z,fa[y]=x;
    fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];
    tr[x][r]=y;
    pushup(y);  
    pushup(x);//因为此时x是y的父亲，所以先更新y在更新x
}
void splay(int x,int &k)
{
    while (x!=k)
    {
        int y=fa[x],z=fa[y];
        if (y!=k)
        {
            if ((tr[y][0]==x)^(tr[z][0]==y))
                rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
void insert(int x)
{
    fa[root]=x;
    tree[x]=x;
    tr[x][0]=root;
    root=x;
}
void dfs(int k)
{
    if (tr[k][0])
    {
        dfs(tr[k][0]);
        maxs[k]=max(maxs[tr[k][0]],a[k]);
    }
    else maxs[k]=a[k];
}
int find(int key,int k)
{
    if (!k) return fa[k];
    if (tree[k]==key) return k;
    if (tree[k]<key)
        return find(key,tr[k][1]);
    else return find(key,tr[k][0]);
}
int query(int l,int r,int n)
{
    if (l==r)
    {
        int x=find(l,root);
        return a[x];
    }
    int x=find(l,root);
    int y=find(r,root);
    splay(x,root);
    splay(y,tr[root][1]);
    int sum=max(maxs[tr[y][0]],a[x]);
    sum=max(sum,a[y]);
    return sum;
}
void modify(int k,int x)
{
    if (a[k]>=x) return;
    a[k]=x;
    int k1=find(k,root);
    splay(k1,root);
    pushup(k1);
}
int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        root=0;
        memset(tr,0,sizeof(tr));
        memset(fa,0,sizeof(fa));
        memset(tree,0,sizeof(tree));
        memset(maxs,0,sizeof(maxs));
        memset(a,0,sizeof(a));
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            insert(i);
        }
        insert(n+1);
        dfs(root);
        char ch[5];
        while (m--)
        {
            scanf("%s",ch);
            if (ch[0]=='U')
            {
                int l,x;
                scanf("%d%d",&l,&x);
                modify(l,x);
            }
            else
            {
                int l,r;
                scanf("%d%d",&l,&r); 
                int ans=query(l,r,n);
                printf("%d\n",ans);
            }
        }
    }
    return 0;//代码有点丑
}
```
'''

---

## 作者：Amphetamine (赞：2)

具体思想，线段树。

此题与P1816唯一的区别就是要改动。（1816巨简单）

热后，说一下改动的方法；

！！！！！！注意啦，读好题！！！！ 改变的 B 为分数，而不是编号为B的人的分数

具体方法：再开一个数组记录第i个同学在线段树中的位置k，然后套模板即可。

修改的时候判断一下，需要修改再改，省时。

...

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m;
struct T{
    int l,r;
    ll max;
}tree[1000001];
ll ans=0;
ll a[1000001];
int k=0;
void pushup(int x){
    int t=x<<1;
    tree[x].max=max(tree[t].max,tree[t+1].max);
}
void build(int l,int r,int x){
    tree[x].l=l;
    tree[x].r=r;
    if(l==r){
        cin>>tree[x].max;
        a[++k]=x;
        return ;
    }
    int t=x<<1;
    int mid=(l+r)>>1;
    build(l,mid,t);
    build(mid+1,r,t+1);
    pushup(x);
}
void query1(int l,int r,int x){
    if(l>tree[x].r||r<tree[x].l)return ;
    if(l<=tree[x].l&&tree[x].r<=r){
        ans=max(ans,tree[x].max);
        return ;
    }
    int t=x<<1;
    int mid=(tree[x].l+tree[x].r)>>1;
    if(mid<l)query1(l,r,t+1);
    else if(mid>=r)query1(l,r,t);
    else {
        query1(l,mid,t);
        query1(mid+1,r,t+1);
    }
}
void update1(int x){
    if(x==1)return ;
    if(x%2==1){
        if(tree[x].max>tree[x-1].max){
            int t=(x-1)>>1;
            tree[t].max=tree[x].max;
            update1(t);
        }
    }
    else {
        if(tree[x].max>tree[x+1].max){
            int t=x>>1;
            tree[t].max=tree[x].max;
            update1(t);
        }
    }
}
int main(){
    cin>>n>>m;
    build(1,n,1);
    ll x,y;
    char c;
    for(int i=1;i<=m;i++){
        cin>>c;
        if(c=='Q'){
            cin>>x>>y;
        query1(x,y,1);
        cout<<ans<<endl;
        ans=0;
        }
        else {
            cin>>x>>y;
            if(tree[a[x]].max<y){
                tree[a[x]].max=y;
                update1(a[x]);
            }
        }
    }
}
...
```

---

## 作者：HohleFeuerwerke (赞：1)

[P1531【I Hate it】](https://www.luogu.org/problem/P1531)

#### 前言

先看数据范围：

> n<=200000 且 0<m<5000

所以我们得出一个伟大的结论：

这题不卡$O(mn)$做法！

#### 题意

维护一个长度为$n$的数据结构，支持update和question两种操作共$m$次

要求算法复杂度在$O(mn)$

#### 我的做法

~~暴力总是不能碾标算的~~

自然而然地，我们能想到一种简单的数据结构：数组

数组的update是$O(1)$的，question是$O(m)$

所以即使全是复杂度较高的question我们也可以轻松过去。

```cpp
#include<bits/stdc++.h>//万能头文件
#define MAXN 200005//最大数据结构长度
#define MAXM 5005 //最大询问次数
using namespace std;//
int n,m;//如题
struct question{//将每次询问存为一个结构体
	char mov;//进行的操作
	int l,r;//读入的两个数 可能是update操作也有可能是question操作
}q[MAXM];//
int stu[MAXN];//每个学生的成绩
int main()
{
	ios::sync_with_stdio(false);//
	cout.tie(0);cin.tie(0);//和前一行通常连用，是cin和cout的读入优化，有时候会比快读快写快一丢丢
	cin>>n>>m;//读入
	for(int i=1;i<=n;i++)//
		cin>>stu[i];//读入
	for(int i=1;i<=m;i++)//
	{
		cin>>q[i].mov>>q[i].l>>q[i].r;//读入询问
		if(q[i].mov=='Q')//是question操作
		{
			int maxSc=-1e9;//定义最大分数maxScore
			for(int j=q[i].l;j<=q[i].r;j++)
			{
				maxSc=max(maxSc,stu[j]);//遍历q[i].l到q[i].r并比较求最大分数
			}
			cout<<maxSc<<endl;//输出
		}
		else//是update操作
			if(stu[q[i].l]<q[i].r)//是需要更新的情况
				stu[q[i].l]=q[i].r;//则更新
	}
	return 0;
}
```

就这样，这题其实挺水的，本来想练线段树，但还是偷懒写了模拟。

---

## 作者：dashuai (赞：1)

一道很简单的线段树裸题，要注意以下几点：

1.数组大小，貌似4倍maxn是不够的。内存允许，开大点没坏处

2.注意题目要求：如果当前A学生的成绩低于B，则把ID为A的学生的成绩更改为B，否则不改动。

3.行首字符（Q or U）的读入，可以当做一个字符串读入，这样就可以自动忽略行末回车。


注释比较详细，自己看吧。





```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
const int maxn=210005;//数组一定别开小了！！！ 
const int maxm=5005;
int a[maxn];//各个同学的成绩 
int l[maxn*4],r[maxn*4],maxnum[maxn*4];
//l[k]、r[k]:储存标号为k的区间（也就是一个线段树上的节点）的左右儿子的标号 
int n,m;
int root,tot;//root：根结点（也就是区间[1..n])的标号；tot:结点总数 
void pushup(int k){//更新节点信息，这里是求区间最大值 
    maxnum[k]=max(maxnum[l[k]],maxnum[r[k]]);
}
int build(int s,int t){//建树 ，在区间[s..t]上建树，并返回该节点的编号 
    int now=++tot;//新建一个节点，节点总数加一 ，记为当前节点 
    int mid=(s+t)>>1;//mid：区间中点 
    if(s==t){//s==t,到达叶子结点(区间长度为一），更新该节点，退出 
        maxnum[now]=a[s];
        return now;
    }
    l[now]=build(s,mid);//建立左子树
    r[now]=build(mid+1,t);//建立右子树 
    pushup(now);//左右子树建完后，就可以确定该节点的信息 
    return now;//返回区间的节点编号 
}
//目标：询问[ql..qr]这个区间的最大值 
//途径：查找[s..t]这个区间，其编号为rt 
int query(int ql,int qr,int s,int t,int rt){
    if(ql<=s&&qr>=t)return maxnum[rt];//如果区间[s..t]在要询问的区间[ql..qr]中，直接返回该节点（区间[r..t]）的最大值 
    int mid=(s+t)>>1;
    int ans=-0x7ffffff;
    if(ql<=mid)ans=max(ans,query(ql,qr,s,mid,l[rt]));//如果区间[ql..qr]与区间[r..t]（节点rt）的左半部分（节点左子树）有交集 ，返回该部分的和最大值 
    if(qr>/*这里没有“=”*/mid)ans=max(ans,query(ql,qr,mid+1,t,r[rt]));
    return ans;
}
// a[L]->C;
//L：要更改的学生ID; C:将学生L的成绩改为C；
//s,t,rt:要寻找的区间左右端点及该区间的编号  
void updata(int L,int C,int s,int t,int rt){
    if(s==t){
        a[s]=C;//到达叶子结点，也就是L 
        maxnum[rt]=C;//更改这个区间的信息 
        return ;
    }
    int mid=(s+t)>>1;
    if(L<=mid)updata(L,C,s,mid,l[rt]);//L在该区间（节点）的左半部分（节点左子树） 
    else updata(L,C,mid+1,t,r[rt]);
    pushup(rt);//更改叶子树信息后，递归返回，向上更新信息
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    root=build(1,n);
    for(int i=1;i<=m;i++){
        char k[4];//竟然要这样读入行首字符，长见识了 
        int A,B;
        scanf("%s%d%d",k,&A,&B);
        if(k[0]=='Q'){
            int ans=query(A,B,1,n,root);
            printf("%d\n",ans);
        }else{
            if(a[A]<B)updata(A,B,1,n,root);//注意题目要求：如果当前A学生的成绩低于B，则把ID为A的学生的成绩更改为B，否则不改动。 
        }
    }
    return 0;
}
//节点？结点？傻傻分不清^?^
```

---

## 作者：重回巅峰！ (赞：1)

标准的PASCAL线段数模版COPY，写给江山二中的校友们。。。。。。。同时也为P党在这里留个参考程序

var
node:array[0..100000]of record

```cpp
                           value,left,right:longint;
                         end;// node 数组记录节点信息。 value记录这个点的最大值，LEFT和RIGHT表示这个点代表的线段的左端点和右端点
  a:array[0..200000]of longint;//记录初始的单个元素的值
  n,m,i,j,ans,b,x,y:longint;
  std,ch:char;
function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;
procedure build(u,left,right:Longint);
var mid:longint;
begin
  node[u].left:=left; node[u].right:=right;
  if left=right then
  begin
    node[u].value:=a[left];  //叶子节点的最大值为本身
    exit;
  end;
  mid:=(left+right) div 2;
  build(u*2,left,mid);
  build(u*2+1,mid+1,right);
  node[u].value:=max(node[u*2].value,node[u*2+1].value);
end;
procedure update(u,x,k:longint);
begin
  if (x<=node[u].right)and(x>=node[u].left) then  //如果X位于U代表的线段中，那么就尝试更新最大值
                        node[u].value:=max(node[u].value,k)
                        else exit;
  update(u*2,x,k)；//继续二分，更新下面的子树
  update(u*2+1,x,k);
end;
function query(u,left,right:longint):longint;
begin
  if (node[u].right<left)or(node[u].left>right) then exit(0);
  if (node[u].right<=right)and(node[u].left>=left) then exit(node[u].value);
  exit(max(query(u*2,left,right),query(u*2+1,left,right)));
end;
begin
  readln(n,m);
  for i:=1 to n do read(a[i]); readln;
  build(1,1,n);
  for i:=1 to m do
  begin
    readln(ch,x,y);
    if ch='Q' then writeln(query(1,x,y))
               else update(1,x,y);
  end;
end.

```

---

## 作者：infinityedge (赞：1)

线段树裸题一枚，就是更新区间最大值。

我的代码的gai()函数可以改低于原成绩的成绩。

另外 线段树数组大小是重中之重，开小了会wa掉（Too Many Or Too Few Lines）而不是re

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define mininf -99999
using namespace std;
int dt[1000005],n,m,itmp[200005];//数组一定要开大！！！ 
void init(int k,int l,int r){//初始化线段树，存储上每个学生初试成绩 
    if(r-l==1){
        dt[k]=itmp[l];
        //printf("%d %d\n",l,r);
    }else{
        //printf("%d %d\n",l,r);
        int chl=k*2,chr=k*2+1;
        init(chl,l,(l+r)/2);
        init(chr,(l+r)/2,r);
        dt[k]=max(dt[chl],dt[chr]);
        //printf("%d %d %d %d\n",dt[k],l,(l+r)/2,r);
    }
}
void gai(int a,int x,int k,int l,int r){//修改函数 
    if(a<l||a>=r)return;
    //dt[k]+=x;
    if(r-l==1){    
        dt[k]=x;
        return;    
    }
    //printf("%d %d\n",l,r);
    int chl=k*2,chr=k*2+1;
    gai(a,x,chl,l,(l+r)/2);
    gai(a,x,chr,(l+r)/2,r);
    dt[k]=max(dt[chl],dt[chr]);
            
}
int query(int a,int b,int k,int l,int r){//查询函数 
    if(b<=l||a>=r)return 0;
    if(a<=l&&b>=r){
        //printf("%d %d\n",k,dt[k]);
        return dt[k];
    }
    if(r-l!=1){
        int chl=k*2,chr=k*2+1;
    
        int res=max(query(a,b,chl,l,(l+r)/2),query(a,b,chr,(l+r)/2,r));
            //printf("%d %d %d %d\n",res,l,(l+r)/2,r);
        return res;
    }    
}
int main(){
        memset(dt,0,sizeof(dt));
        memset(itmp,0,sizeof(itmp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&itmp[i]);
        }
        init(1,1,n+1);        
        string st;
        int x,y;        
        for(int i=1;i<=m;i++){
            cin>>st;
            scanf("%d%d",&x,&y);
            if(st=="Q"){
                printf("%d\n",query(x,y+1,1,1,n+1));
            }
            if(st=="U"){
                if(query(x,x+1,1,1,n+1)<y)gai(x,y,1,1,n+1);//当大于时更新 
            }    
        }        
    return 0;
}
```

---

## 作者：fl_334 (赞：1)


```cpp
//给出核心代码
void update(int before,int over,int l,int r,int rt){           //更新值
    if (l==r){
        sum[rt]=over;
        return;    
    }else{
        int m=(l+r) div 2;
        if (before<=m) update(before,over,l,m,rt*2);           //更新左娃娃
        else update(before,over,m+1,r,rt*2+1);       //更新右娃娃
        pushup(rt);          //向上更新，虽然此处没给，但想想就很容易想出来吧
    }
}
int query(int ll,int rr,int l,int r,int rt){
    if ((ll<=l)&&(r<=rr))
    {
        return sum[rt];           //返回sum[rt],sum[rt]表示的是在rt号节点中表示的线段树范围中的最大值(ps.不是应该叫maxn么）
}
    int m=(l=r) div 2;
        if (ll<=m){
        tt=query(ll,rr,l,m,rt*2);         //左娃
        ttt=max(ttt,tt);
    }
    if (rr>m) 
    {
        tt=query(ll,rr,m+1,rt*2+1);        //右娃
        ttt=max(ttt,tt);       //更新
    }
    return ttt;
}

```

---

## 作者：Shirο (赞：1)

看到题解里面没有zkw~~重口味~~线段树的，

所以决定水一发，大家可以看一下[P3865 【模板】ST表](https://www.luogu.org/problemnew/show/P3865)

这道题目与他类似，所以可以参考我这篇题解[这里](https://www.luogu.org/blog/woshisb/solution-p3865)

那么为什么zkw能跑得比普通线段树快呢？

因为zkw神犇用循环代替了递归

这道题目是区间查询和单点修改，并没有lazy的运用

所以zkw自然比普通线段树好一点

下面来欣赏我这位蒟蒻的代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6+10;
int tree[4*maxn];//内存要4倍比较保险
void maintain(int x) {tree[x]=max(tree[x<<1],tree[x<<1|1]);}
//这里是一个构造函数，表示取区间最大值
//注解 x<<1=2*x,x<<1=2*x+1
int N,M=1;
void build()//三行建树
{
    //把树看成满二叉树，即为2的k次幂
    //将m运行到大于n的2^k
    for(M;M<N;M<<=1);
    for(int i=M+1;i<=M+N;i++) scanf("%d",&tree[i]);
    for(int i=M-1;i;--i) maintain(i);
 } 
 void update(int pos,int v)
 {
 	pos+=M;
 	if(tree[pos]<v)
 	{
 		tree[pos]=v;
		 for(pos>>=1;pos;pos>>=1)maintain(pos);	
	}
	 else return;
 }
 //短，真短，真鸡鹅短！非常轻松愉快地完成了Update操作。
 //并且Zkw线段树在Update上的效率要比普通线段树优秀
 //因为Zkw线段树寻找叶子的复杂度是 O(1) 
 //而传统线段树是 O(logN) 。所以如果某个题有频繁的单点修改，Zkw会是一个非常好的选择。
 int Max(int l,int r)
 {
    int ans=0;//记得初始化
    // l=l+M-1->将查询区间改为L-1，r=r+M+1->将查询区间改为R+1
    // l^r^1 -> 相当于判断l与r是否是兄弟节点
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) ans=max(tree[l^1],ans);
        if(r&1) ans=max(tree[r^1],ans);
    }
    return ans;
 }
 int main()
 {
    int k,x,y,o,p;
    char c; 
    N=read(),k=read();
    build();
    for(int i=0;i<k;i++)
    {
        cin>>c;
        o=read(),p=read();//快读
        if(c=='Q')
        {
        	printf("%d\n",Max(o,p));
		}
		else 
		{
			update(o,p);
		}
        
     }
 }
```
后面主程序都应该看得懂吧

zkw主要在于理解

最后广告一下自己的博客

最近专门研究线段树的题目

[这里](https://www.luogu.org/blog/woshisb/)

---

## 作者：宁海金城武 (赞：1)

采用结构体就很简单了！！

```cpp
#include<stdio.h>
struct ins    //定义结构体 
{
    char a[3];    //Q或者U 
    int former;   //第一个数字 
    int latter;   //第二个数字 
};
struct ins in[5005];  //结构体数组 
int num[200005],n,m;  //成绩数组和n，m 
int main()
{
    int i,max=0,j;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
    }
    for(i=1;i<=m;i++)
    {
        scanf("%s %d %d",in[i].a,&in[i].former,&in[i].latter);
    }
    for(i=1;i<=m;i++)
    {
        if(in[i].a[0]=='Q')  //如果第一个是Q的话 
        {
            for(j=in[i].former;j<=in[i].latter;j++)//找出最大值 
            {
                if(num[j]>max)
                {
                    max=num[j];
                }
            }
            printf("%d\n",max); //输出 
            max=0;  //别忘了将max还原成0 
        }
        else   //如果第一个是U的话 
        {
            if(num[in[i].former]<in[i].latter) //判断后面的数字是不是比前面的序号对应的成绩大 
            {
                num[in[i].former]=in[i].latter;
            }
        }
    }
    return 0;
}
```

---

## 作者：lzk的新欢 (赞：1)

看大家这么多线段树   我就也来一波分块吧


//block 块的大小 num 分成几块 belong[i] 第i个元素属于第几块 r[i],l[i] 第i块的左右端点

    
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define maxn 2000007
int belong[maxn],num,r[maxn],l[maxn],n,m,block,a[maxn],Max[maxn];
void build()
{
    block=sqrt(n);
    num=n/block;if(n%block)num++;
    for(int i=1;i<=num;i++)
    {
        l[i]=(i-1)*block+1;r[i]=block*i;
    }
    r[num]=n;
    for(int i=1;i<=n;i++)
    {
        belong[i]=(i-1)/block+1;
    }
    for(int i=1;i<=num;i++)
      for(int j=l[i];j<=r[i];j++)
        Max[i]=max(Max[i],a[j]);
}
void modify(int pos,int data)
{
    if(a[pos]<data)
    {
        a[pos]=data;
        Max[belong[pos]]=max(a[pos],Max[belong[pos]]);
    }
}
int query(int x,int y)
{
    int ans=0;
    if(belong[x]==belong[y])
    {
        for(int i=x;i<=y;i++)
          ans=max(ans,a[i]);
          return ans;
    }
    for(int i=x;i<=r[belong[x]];i++)
    ans=max(ans,a[i]);
    for(int i=belong[x]+1;i<belong[y];i++)
    ans=max(ans,Max[i]);
    for(int i=l[belong[y]];i<=y;i++)
    ans=max(ans,a[i]);
    return ans;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    build();
    while(m--)
    {
        int x,y;
        char id;
        cin>>id>>x>>y;
        if(id=='Q')
        cout<<query(x,y)<<endl;
        else 
        modify(x,y);
    }
    return 0;
}
```

---

## 作者：s_a_b_e_r (赞：1)

###线段树模板

build不用说了

ask我用的是只有坐标相等才返回

XG代表修改的点的坐标

然后二分修改区间（原以为会很慢）

注意\*后面的公式“tr[k].ma=max(tr[k\*2].ma,tr[k\*2+1].ma)”是错的\*(自己想一下就明白了吧。。)

希望能带来思路

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define IN 9999999
using namespace std;
const int maxx=200100;
int n,m,A,B,ssr;
char C;
int a[maxx+10];
struct SABER{
int l,r;
int ma;
int lazy;
}tr[maxx*4];
void build(int k,int i,int j){
     tr[k].l=i;tr[k].r=j;
     if(i==j){tr[k].ma=a[i];return ;}
     int mid=(i+j)/2;
     build(k*2,i,mid);
     build(k*2+1,mid+1,j);
     tr[k].ma=max(tr[k*2].ma,tr[k*2+1].ma);
}
int ask(int k,int i,int j){
    int l=tr[k].l,r=tr[k].r,ans=0;
    if(i==l&&j==r){return tr[k].ma;}
    int mid=(l+r)/2;
    if(j<=mid){ans=ask(k*2,i,j);}
    else if(i>mid){ans=ask(k*2+1,i,j);}
    else {
         ans=max(ask(k*2,i,mid),ask(k*2+1,mid+1,j));
         }
    return ans;
}
void X(int k,int XG,int B){
     int l=tr[k].l,r=tr[k].r;
     if(XG==l&&XG==r){tr[k].ma=B;return;}
     int r1=tr[k*2].r,l1=tr[k*2].l;
     if(l1<=XG&&XG<=r1){X(k*2,XG,B);tr[k].ma=max(tr[k].ma,tr[k*2].ma);}
     else {X(k*2+1,XG,B);tr[k].ma=max(tr[k].ma,tr[k*2+1].ma);}
     //tr[k].ma=max(tr[k*2].ma,tr[k*2+1].ma);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=m;i++){
    cin>>C>>A>>B;
    if(C=='Q')cout<<ask(1,A,B)<<endl;
    else 
    {if(B>a[A])X(1,A,B);}
    }
    return 0;
}
```

---

## 作者：sunyt (赞：1)

说实话做这个题的时候我搞错了两点，于是在第三次提交时才AC。

首先我没注意这个题的数据范围，没看清所以开小了，RE了三个，WA了一个，得了60,。

结果我兴致勃勃的改掉之后发现还有大trouble，本来的姹紫嫣红变成了绿肥红瘦，RE全变成了WA，还是60。因为忘记了这样一件事情：改后的成绩与原成绩是不一样的，所以如果要改第二次，就必须先找到再比较，再修改。这种zz的错误竟然也犯了，无语。。。

然后这道题是一道线段树的问题。（HDU1754有一道题与这个差不多，样例数据也相同，只是有一个条件放宽了，就是不需要比较直接更改）

261ms /  25.71MB 1.22KB C++

上代码（来自中犇的弱代码）：





            
            
    
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int i,j,n,m,aa,bb,maxx;
char ord;
struct data
{
    int a,b,sum;
}t[800001];
int b[200001];
void make(int x,int y,int root)
{
    if(x==y)
    {
    t[root].sum=b[x];
    t[root].a=x;
    t[root].b=x;
    }
    else
    {
        make(x,(x+y)/2,root*2);
        make((x+y)/2+1,y,root*2+1);
        t[root].a=x;t[root].b=y;
        t[root].sum=max(t[root*2].sum,t[root*2+1].sum);
    }
}
void chg(int x,int y,int num)
{
    if(t[num].a==t[num].b)
    {t[num].sum=max(t[num].sum,y);
    return;}
    else
    {
        int mid=(t[num].a+t[num].b)/2;
        if(x<=mid)
        chg(x,y,num*2);
        else
        chg(x,y,num*2+1);
        t[num].sum=max(t[num*2].sum,t[num*2+1].sum);
    }
}
void query(int x,int y,int num)
{
    if(t[num].a==x&&t[num].b==y)
    {maxx=max(maxx,t[num].sum);
    return;}
    else
    {
        int mid=(t[num].a+t[num].b)/2;
        if(mid>=y)
        query(x,y,num*2);
        if(mid<x)
        query(x,y,num*2+1);
        if(mid<y&&mid>=x)
        {
            query(x,mid,num*2);
            query(mid+1,y,num*2+1);
        }
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    cin>>n>>m;
    for(i=1;i<=n;i++)
    cin>>b[i];
    make(1,n,1);
    for(i=1;i<=m;i++)
    {
        cin>>ord>>aa>>bb;
        if(ord=='U')
        chg(aa,bb,1);
        if(ord=='Q')
        {maxx=0;
        query(aa,bb,1);
        cout<<maxx<<endl;}
    }
}
```

---

## 作者：Dreamboat (赞：1)

```cpp
//线段树模板
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;  
const int INF=200005;
struct data {int l,r,INF;}node[3*INF];  
int score[INF];
void creat(int left,int right,int u)  
{  
    node[u].l=left;  
    node[u].r=right;  
    if(left==right)  node[u].INF=score[left];  
    else  
    {  
        creat(left,(left+right)/2,2*u);  
        creat(((left+right)/2)+1,right,2*u+1);  
        node[u].INF=max(node[2*u].INF,node[2*u+1].INF);  
    }  
}  
void up(int x,int y,int u)  
{  
    node[u].INF=max(y,node[u].INF);  
    if(node[u].l==node[u].r) return;   
    if(x<=node[2*u].r) up(x,y,2*u);  
    else up(x,y,2*u+1);  
}  
int que(int left,int right,int u)  
{  
    if(node[u].l==left&&node[u].r==right) return node[u].INF;  
    if(right<=node[2*u].r) return que(left,right,2*u);  
    if(left>=node[2*u+1].l) return que(left,right,2*u+1);  
    int mid=(node[u].l+node[u].r)/2;  
    return max(que(left,mid,2*u),que(mid+1,right,2*u+1));  
}  
int main()  
{  
    int N,M;  
    while(scanf("%d%d",&N,&M)!=EOF)  
    {  
        int i;  //n个数表示线段树一开始的数据，建树 
        for(i=1;i<=N;i++) scanf("%d",&score[i]);  
        getchar();
        char c;  
        int s,k;  
        creat(1,N,1);
        for(i=0;i<M;i++)
        {  
            scanf("%c%d%d",&c,&s,&k);//U表示把s数值修改为e Q表示在一个s~e中查询最小值         
            getchar();
            if(c=='U') up(s,k,1);  
            if(c=='Q') printf("%d\n",que(s,k,1));  
        }  
    }  
    return 0;  
}
```

---

## 作者：Nero_Claudius (赞：1)

这道题明明是裸的线段树，蒟蒻却80分了五六次。。。


------------

根据题意，显然是维护一棵单点修改区间查询的线段树，于是直接套区间修改的代码。。。

结构体，即为树上的节点。
```cpp
struct node{
	int l, r;
	int val;
} tree[maxn * 4];
```
建树，注意：将读入放到这里来！！原本是在main里面读入然后储存到stu数组中，结果就一直80分！!
```cpp
void Build(int l, int r, int pos) { //
	tree[pos].l = l;
	tree[pos].r = r;
	if(l == r) {
		int a;
		a = read();
		tree[pos].val = a;
	}
	else {
		int mid = (l + r) >> 1;
		Build(l, mid, pos * 2);
		Build(mid + 1, r, pos * 2 + 1);
		tree[pos].val = max(tree[pos * 2].val, tree[pos * 2 + 1].val);
	}
}
```
区间修改函数：
	1. 如果直接是要求的区间，直接修改即可。
    2. 反之则分配到左右子树上面去。
    3. 回溯。
```cpp
void Update(int l, int r, int d, int pos) {
	if(tree[pos].l == l && tree[pos].r == r) {
		tree[pos].val = max(d, tree[pos].val);
		return ;
	}
	int mid = (tree[pos].l + tree[pos].r) >> 1;
	if(r <= mid) Update(l, r, d, pos * 2);
	else if(l > mid) Update(l, r, d, pos * 2 + 1);
	else {
		Update(l, mid, d, pos * 2);
		Update(mid + 1, r, d, pos * 2 + 1);
	}
	tree[pos].val = max(tree[pos * 2].val, tree[pos * 2 + 1].val);
}
```
区间查询函数：

其实流程和修改挺像的。
```cpp
int Query(int l, int r, int pos) {
	if(tree[pos].l == l && tree[pos].r == r) {
        return tree[pos].val;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if(r <= mid) return Query(l, r, pos * 2); 
    else if(l > mid) return Query(l, r, pos * 2 + 1); 
	else {
        return max(Query(l, mid, pos * 2), Query(mid + 1, r, pos * 2 + 1));
    }
}
```
主要处理部分：

read()是快速读入函数，然后要注意因为本题是单点修改，所以Update函数的l,r两个参数其实是一样的。
```cpp
scanf("%s", &op);
		l = read(); r = read();
		if(op == 'Q') printf("%d\n", Query(l, r, 1));
		else Update(l, l, r, 1);
```


------------

emmm....大概就这么多了。

代码64ms，氧化后36ms。

---

## 作者：teafrogsf (赞：1)

联赛期间复习一下分块。

[日常宣传lofter。](http://teafrog26.lofter.com/)

**分块算法是一种~~用于暴力骗分的~~比较高效的算法，经常用于解决各种区间问题。**~~当然nsqrt(n)毕竟还是没有nlogn的线段树快，但是好打不是么~~

其实现方式是把数组分成sqrt(n)（经均值不等式证明一般题型这样分时间效率最高）块，每块储存块内的数值。

于是遍历就只需要sqrt(n)了。

注意查询区间的边角不一定是个完整的块，这部分使用暴力解决。

此外，本题请使用cin，毕竟玄学输入。

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#define neko 200010
#define chkmin(a,b) ((a)<(b)?(a):(b))
#define chkmax(a,b) ((a)>(b)?(a):(b))
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
int n,m,blk,a[neko],bl[neko],Max[neko];
using std::cin;
void split()
{
    f(i,1,n)
    {
        bl[i]=(i-1)/blk+1;
        Max[bl[i]]=chkmax(Max[bl[i]],a[i]);
    }
}
void update(int tag,int x)
{
    if(a[tag]<x)a[tag]=x,Max[bl[tag]]=chkmax(Max[bl[tag]],a[tag]);//仅一行的update
}
int query(int l,int r)
{
    int tmp=0;
    f(i,l,chkmin(bl[l]*blk,r))tmp=chkmax(tmp,a[i]);
    if(bl[l]!=bl[r])f(i,bl[l]+1,bl[r]-1)tmp=chkmax(tmp,Max[i]);
    f(i,chkmax((bl[r]-1)*blk+1,l),r)tmp=chkmax(tmp,a[i]);
    return tmp;
}
int main()
{
    std::ios::sync_with_stdio(false);
    char c;int x,y;
    cin>>n>>m,blk=sqrt(n);
    f(i,1,n)cin>>a[i];
    split();
    f(i,1,m)
    {
        cin>>c>>x>>y;
        if(c=='Q')printf("%d\n",query(x,y));
        else update(x,y);
    }return 0; 
}
```

---

## 作者：夏色祭 (赞：1)

##P的题解依旧少得可怜，20篇里只有2篇，那我来补一发吧

线段树的入门题。。不会zjoi那些很（e）难（xin）的线段树，所以只能来水水题了。。。。

先建树，然后每次单点修改或是区间查询

要注意的是如果>，才去修改

而且这题连标记下放都不用

献上没有66666a代码丑陋的代码：


```cpp
uses math;
type
  tree=record
  sum,l,r:longint;
end;
var
  tt:array[0..200001]of longint;
  a:array[0..1000001]of tree;
  n,m,i,x,y:longint;
  c:char;
procedure build(k,l,r:longint);
var
  mid:longint;
begin
  a[k].l:=l; a[k].r:=r;
  if l=r then 
    begin
      a[k].sum:=tt[l];
      exit;
    end;//叶子节点
  mid:=(l+r) >> 1;
  build(k*2,l,mid);
  build(k*2+1,mid+1,r);
  a[k].sum:=max(a[k*2].sum,a[k*2+1].sum);
end;//建树
procedure change(k,l,r,zz:longint);
begin
  if (a[k].l>r)or(a[k].r<l) then exit;
  if (l=a[k].l)and(r=a[k].r) then 
    begin
      a[k].sum:=max(a[k].sum,zz);//在原先的值和要修改的值找个max
      exit;
    end;
  change(k*2,l,r,zz);
  change(k*2+1,l,r,zz);
  a[k].sum:=max(a[k*2].sum,a[k*2+1].sum);
end;//单点修改
function query(k,l,r:longint):longint;
begin
  if (a[k].l>r)or(a[k].r<l) then exit(0);
  if (a[k].l>=l)and(a[k].r<=r) then exit(a[k].sum);
  exit(max(query(k*2,l,r),query(k*2+1,l,r)));
end;//区间查询
begin
  readln(n,m);
  for i:=1 to n do read(tt[i]);
  readln;
  build(1,1,n);
  for i:=1 to m do 
    begin
      readln(c,x,y);
      if c='Q' then writeln(query(1,x,y));
      if c='U' then change(1,x,x,y);
    end;
end.
```

---

## 作者：不是憨憨 (赞：1)

我觉得线段树模版还是要又快又整洁才好。。。

加读优48ms(dalao勿喷)

线段树功能：update：单点替换 query：区间最值

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define g getchar()
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn =222222;
int MAX[maxn<<2];
inline int read() {
    int x=0,f=1;char ch=g;
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=g;}
    while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+(ch^'0'),ch=g;
    return x*f;
}
void PushUP(int rt) {
    MAX[rt]= max(MAX[rt<<1] , MAX[rt<<1|1]);
}
void build(int l,int r,int rt) {
    if(l == r) {
        MAX[rt] = read();
        return;
    }
    int m =(l + r)>>1;
    build(lson);
    build(rson);
    PushUP(rt);
}
void update(int p,int sc,int l,int r,int rt) {
    if(l == r) {
        MAX[rt]= max(sc,MAX[rt]);
        return;
    }
    int m =(l + r)>>1;
    if(p <= m) update(p , sc , lson);
    else update(p , sc , rson);
    PushUP(rt);
}
int query(int L,int R,int l,int r,int rt) {
    if(L <= l && r <= R) {
        return MAX[rt];
    }
    int m =(l + r)>>1;
    int ret =0;
    if(L <= m) ret = max(ret , query(L , R , lson));
    if(R > m) ret = max(ret , query(L , R , rson));
    return ret;
}
int main() {
    int n = read(), m = read();
    build(1 , n , 1);
    while(m --) {
        char op[2];
        scanf("%s",op);
        int a = read(), b = read();
        if(op[0]=='Q')printf("%d\n",query(a , b , 1 , n , 1));
        else update(a , b , 1 , n , 1);
    }
    return 0;
}
```

---

## 作者：Mr_Li (赞：1)

裸的线段树题，至于不知道什么是线段树的小盆友，就去网上查查吧~

**特别的，[color=red]当且仅当B>score[A](score[i]表示第i名同学当前的分数)，语句U A B才会将A的学生的成绩更改为B[/color]。（所以关注讨论列表也是很重要的）**


---

## 作者：Isshiki_Hugh (赞：0)

1.指针线段树万岁，然而天下线段树竟都是数组，指针这么清晰它不香么？

2.由于这道题只是单点修改，所以我们没必要先把点找到了再修改，同时维护数组和线段树，比较数组中第A个和B的大小，如果满足条件就单点修改。

3.要注意，修改的时候一定要判断边界等于A！直接写左右边界相等的只有我一个就够了orz(果然还是我太菜



#### code

```cpp

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
//int[1e7] ll[5*1e6]
typedef long long ll;
typedef unsigned long long ull;
using std::cin;using std::cout;

int n,m,a[200010],cnt,now,nown,L,R;

struct node{
    node * ls , * rs;
    int l,r,max;
}tree[400010];

inline node * create(){return & tree[++cnt];}

inline void pushup(node * cur){
    if(cur->ls->max > cur->rs->max){
        cur->max = cur->ls->max;
    } else {
        cur->max = cur->rs->max;
    }
}

inline void build(node * cur , int l , int r){
    if(l == r){
        cur->l = cur->r = l , cur->max = a[l] ;
        return;
    }
    cur->l = l , cur -> r = r;
    cur->ls = create() , cur->rs = create();
    build(cur->ls,l,(l + r) >> 1) , build(cur->rs,((l + r) >> 1 ) + 1 , r);
    pushup(cur);
    return;
}

inline int query(node * cur){
    if(cur->l > R || cur->r < L) return 0;
    if(cur->l >= L && cur->r <= R) return cur->max;
    return std::max(query(cur->ls),query(cur->rs));
}

inline void make(node * cur){
    if(cur->l == cur->r && cur->l == nown){
        cur->max = now;
        return;
    }
    if(nown < cur->l || nown > cur->r) return;
    make(cur->ls) , make(cur->rs);
    pushup(cur);
}

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("in.in", "r", stdin);
    cin >> n >> m;
    for(register int i = 1; i <= n;++i){
        cin >> a[i];
    }
    
    //建树
    node * root = create();
    build(root,1,n);

    for(register int i = 1; i <= m;++i){
        char opt;
        cin >> opt;
        if(opt == 'Q'){
            cin >> L >> R;
            cout << query(root) << "\n";
        } else {
            cin >> nown >> now;
            if(now <= a[nown]) continue;//直接比较数组
            else make(root);//线段树中单点修改
            if(now > a[nown]) a[nown] = now; //数组中单点修改同时维护
        }
    }
    return 0;
}
```

---

## 作者：TLE自动机 (赞：0)

  
  我看下面题解没有zkw ~~（重口味）~~ 线段树的，再加上刚刚学，写篇题解巩固一下。

zkw线段树就是把普通线段树的递归过程改成了循环，常数优化了很多。本题是单点修改+区间查询，zkw可以很方便的实现。节点i（A,B) 表示从第A个到第B个的最大值。

#### 1.单点修改 

其实就是把叶节点对应的更新，维护一下父节点即可。

#### 2.区间查询

对于区间（s,t),只需不断往上回溯，求构成（s,t)中，每个区间的最大值。

我的码风应该还是比较好懂吧QwQ~

```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int read(){
	int x=0;char ch=getchar();bool pos=1;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') pos=0;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return pos?x:-x;
}//快读
int n,m,k=1,d[800001];
inline void build(){
	for(;k<=n+1;k<<=1); for(int i=k+1;i<=k+n;i++) d[i]=read();
	for(int i=k-1;i>=1;i--) d[i]=max(d[i<<1],d[i<<1|1]);
}//建树
inline void change(int now,int w){
	d[now+k]=w; for(now=((k+now)>>1);now;now>>=1) d[now]=max(d[now<<1],d[now<<1|1]);
}//update，d[i+k]表示每个叶节点的值，从第一个父节点开始
inline int ask(int s,int t){
	int ans=-999999;
	for(s=s+k-1,t=t+k+1;s^t^1;s>>=1,t>>=1){if(~s&1) ans=max(ans,d[s^1]); if(t&1) ans=max(ans,d[t^1]);}
	return ans;
}//s^t^1表示父节点不一样
int main(){
	n=read();m=read();
	build();
	char q;
	for(int i=1;i<=m;i++){
		cin>>q;
		if(q=='Q'){
			int a=read(),b=read();
			cout<<ask(a,b)<<endl;
		}
		else if(q=='U'){
			int a=read(),b=read(),w1,w2;
			w1=d[k+a]; w2=b;
			if(w1<w2) {
				change(a,w2);
			} 
		}
	}
	return 0;
}
```


---

