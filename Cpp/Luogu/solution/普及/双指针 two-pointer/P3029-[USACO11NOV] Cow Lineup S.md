# [USACO11NOV] Cow Lineup S

## 题目描述

### 问题描述

农民约翰雇佣了一位专业摄影师来拍摄他的一些奶牛。由于约翰的奶牛代表了多种不同的品种，他希望照片中至少包含他牛群中每种不同品种的一头奶牛。

约翰的 $N$ 头奶牛都站在一条线上的不同位置，每头奶牛的位置由一个整数（即其 $x$ 坐标）和一个整数品种 ID 描述。约翰计划拍摄一段连续的奶牛范围。该照片的成本等于其大小——即照片中奶牛的最大和最小 $x$ 坐标之间的差。

请帮助约翰计算出一张照片的最小成本，其中至少包含约翰牛群中每种不同品种的一头奶牛。

## 说明/提示

有 $6$ 头奶牛，位置分别为 $25$、$26$、$15$、$22$、$20$、$30$，品种 ID 分别为 $7$、$1$、$1$、$3$、$1$、$1$。

从 $x=22$ 到 $x=26$ 的范围（总大小为 $4$）包含了约翰的牛群中每种不同的品种 ID：$1$、$3$ 和 $7$。

## 样例 #1

### 输入

```
6 
25 7 
26 1 
15 1 
22 3 
20 1 
30 1 
```

### 输出

```
4 
```

# 题解

## 作者：糪眾脦颰罷 (赞：37)

# ~~**STL大法好！**~~

# 感谢机房大佬 @S_AKM 提供的思路——尺取

其实我们可以不用hash,用map存种类就行了。（~~虽然比较慢~~）

此外，大致思路与其他题解相同。

贴代码
```
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x;
    int p;
};
node s[70000];
int ans=2e9,sum,n,z,tail;
map<int,int>t;
map<int,bool>pan;
bool cmp(node a,node b){
    return a.x<b.x;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>s[i].x>>s[i].p;
    	if(pan[s[i].p]==false){
    		sum++;
    		pan[s[i].p]=true;//预处理一波，记录奶牛的种类总数
		}
	}
    sort(s+1,s+n+1,cmp);
    tail=1;
    t[s[1].p]++;
    z=1;
    for(int i=1;i<=n;i++){//以下思路与其他题解类似，就是用tail尾指针和头指针i不断查找更新答案
        while(z<sum&&tail<n){
            tail++;
            t[s[tail].p]++;
            if(t[s[tail].p]==1)z++;
        }
        if(z==sum)ans=min(ans,s[tail].x-s[i].x);
        t[s[i].p]--;
        if(t[s[i].p]==0)z--;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Priori_Incantatem (赞：18)

**update 2020/1/18，修改了一些小细节**

双倍经验：[P2564 [SCOI2009]生日礼物](https://www.luogu.com.cn/problem/P2564)

#### 不需要STL队列！不需要手写队列！不需要双端队列！直接用双指针！

首先，将所有牛按照坐标升序排列，并把他们那又臭又长的ID利用 map 换成一个连续的ID  
数组 $c[]$ 维护当前区间 $[l,r]$ 中每种牛出现的次数，$sum$ 记录当前区间内牛的种类总数，$tot$ 为总共牛的种数，最开始 $l=1,r=0$ 

接下来开始枚举：

若当前区间$sum<tot$，说明牛的种数还不够，就把区间往右扩展 `++r`  并维护 $c[id[r]],sum$  
然后，将区间最左边的多余的牛弹掉。也就是如果 $c[id[l]]>1$ `++l`。**注意：** 如果弹掉了牛一定要更新$c[]$和$sum$  

最后，如果还是 $sum<tot$，重复上面操作。如果 $sum=tot$ 就更新答案并且`++l`

**代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
const int Maxn=50000+20,inf=0x3f3f3f3f;
map <int , int> vis;
int a[Maxn],id[Maxn],c[Maxn];
struct cow{
	int x,d;
}srt[Maxn];
int n,ans=inf,tot;
inline bool cmp(cow u,cow v)
{
	return u.x<v.x;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int calc(int x)
{
	if(!vis[x])vis[x]=++tot;
	return vis[x];
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	{
		srt[i].x=read();
		int tmp=read();
		srt[i].d=calc(tmp);
	}
	sort(srt+1,srt+1+n,cmp); //结构体仅用来排序
	for(int i=1;i<=n;++i)
	a[i]=srt[i].x,id[i]=srt[i].d;
	
	int l=1,r=0,sum=0;
	while(r<n)
	{
		++r,c[id[r]]++; //记得统计c[]和sum！
		if(c[id[r]]==1)++sum;
		while(c[id[l]]>1)
		{
			c[id[l]]--;
			if(!c[id[l]])--sum;
			++l;
			if(l>r)break; //如果区间里已经没东西了就 break
		}
		if(sum==tot)
		{
			ans=min(ans,a[r]-a[l]); //更新答案
			c[id[l]]--; //记得统计c[]和sum！
			if(!c[id[l]])--sum;
			++l;
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：__JR_飘摇__ (赞：14)

咦~dalao们怎么不写单调队列？不是也很短吗？

------------
- 发现牛站的位置是无序的，简单，肯定要排序啦~~
- 一个sort的事情！！
- 刚看到题目时发现，怎么x,d这么大？难道数组要开到几亿吗？dalao们都用hash，然而本蒟蒻认为一个map就能实现离散化了，不想写得那么累~~
- 剩下的就是单调队列了：
- 既然已经处理了x和d，那么这就简单了/
- 用c[i]表示head~tail中第i品种的数量；
- 如果q[head]中牛的品种i使得c[i]>1；
- 那么这个就是多余的啦！！
- 没用的就删了，head++；
- 每次走完判断一下距离，本题的题解就出来啦~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,num,minn=1000000000,kc,ff,c[50001],t,w;
map<int,int> a;
struct node
{
	int k,id;
}f[50001],q[50001];
int comp(const node&a,const node&b){return a.k<b.k;}
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)//离散化，将牛的品种转为一串有序的数 
	{
	  scanf("%d%d",&f[i].k,&kc);
	  if(!a.count(kc)) ff++,a[kc]=ff;//ff表示牛的品种总数 
	  f[i].id=a[kc];
    }
	sort(f+1,f+n+1,comp);
	q[1].k=f[1].k;q[1].id=f[1].id;
	c[f[1].id]++;num=1;t=1;w=1;//num表示head(t)~tail(w)中牛的总数 
	for(i=2;i<=n;i++)
	{
		if(!c[f[i].id]){num++;c[f[i].id]=1;}
		else c[f[i].id]++;
		w++;
		q[w].k=f[i].k;q[w].id=f[i].id;//入队处理 
		while(c[q[t].id]>1){c[q[t].id]--;t++;}//出队处理 
		if(num==ff) minn=min(minn,q[w].k-q[t].k); 
	}
	printf("%d",minn);
} 
```

---

## 作者：zoelxy (赞：13)

这种方法应该算比较简单易懂的了~~（连我这种蒟蒻都会了~~）
利用stl中的map函数


  ```
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<iostream>
#include<map>
using namespace std;
struct Node{
	int x,id;
}cow[50005],que[50005];//结构体 
map<int,int>mp; //stl中的map（映射） 
bool cmp(Node p,Node q){
	return p.x<q.x;
}
int main(){
	int n,sum=0,ans=2147483647;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&cow[i].x,&cow[i].id);
		mp[cow[i].id]++;
		if(mp[cow[i].id]==1)sum++;//计算奶牛种数 
	}
	sort(cow+1,cow+n+1,cmp);
	mp.clear();//清空 
	int l=1,r=0,tot=0;//tot:照片中的奶牛种数 l左端点 r右端点 
	for(int i=1;i<=n;i++){
		if(!mp[cow[i].id])//如果cow[i].id不在mp中 
			mp[cow[i].id]=1,tot++;
		else 
			mp[cow[i].id]++;
		que[++r]={cow[i].x,cow[i].id};
		while(mp[que[l].id]>1)//去重 
			--mp[que[l++].id];//l++左端点右移一位 
		if(tot==sum)//照片中奶牛种数等于一共的奶牛种数 
			ans=min(ans,que[r].x-que[l].x);
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：winmt (赞：6)

我来发第一个题解！此题比较水！！！

首先将牛的位置从小到大排序，方便处理。然后L指针指向最左的牛，R指针也指向最左的牛。然后R一直往右移动，直到区间包含所有种类的牛，然后再移动L指针，若某一时刻此区间不包含所有牛了，那么就移动R指针，重复以上步骤，直到R到达N号位置为止！详见代码：




    
    
    
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<deque>
#include<utility>
#include<map>
#include<set>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<sstream>
#include<cstring>
#include<bitset>
#include<stack>
using namespace std;
int n,ans,cnt,mn=2147483647;
struct sdt
{
    int x,id;
}a[50005];
map<int,int>mp;
map<int,bool>vis;
bool cmp(sdt x,sdt y)
{
    return x.x<y.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].id);
        if(vis.find(a[i].id)==vis.end())
        {
            vis[a[i].id]=1;
            cnt++;
        }
    }
    sort(a+1,a+n+1,cmp);
    /*for(int i=1;i<=n;i++)
    {
        cout<<a[i].id<<" "<<a[i].x<<endl;
    }*/
    int l=1,r=1,kkk=0;
    bool f=0;
    kkk++;
    if(kkk==cnt)
    {
        mn=a[1].x-1;
        f=1;
    }
    mp[a[1].id]++;
    while(r<=n)
    {
        if(f==0)
        {
            if(r==n)break;
            r++;
            if(mp.find(a[r].id)==mp.end() || mp[a[r].id]==0)kkk++;
            mp[a[r].id]++;
            if(kkk==cnt)
            {
                mn=min(mn,a[r].x-a[l].x);
                //cout<<a[r].x<<" "<<a[l].x<<endl;
                f=1;
            }
        }
        else 
        {
            l++;
            if(mp[a[l-1].id]==1)
            {
                kkk--;
                f=0;
            }
            if(f==1)mn=min(mn,a[r].x-a[l].x);
            //if(f==1)cout<<a[r].x<<" "<<a[l].x<<endl;
            mp[a[l-1].id]--;
        }
    }
    printf("%d\n",mn);
    return 0;
}
```

---

## 作者：两年打铁 (赞：5)

我比较菜，写了一发双端队列。

先记录总共有几个id

然后按照位置从小到大排一遍序；

每次读到一个id我们直接用一个STL的map来记录当前id出现的次数~~（原谅我懒）~~

然后就可以开始弹队首，直到队首的id只剩下1并且队中的id数已经等于给定的id数时，我们更新答案。

答案是要满足队列中每一个id至少出现一次，用这个队列就可以保证这是在一段不断向后的连续的区间里我们不断地更新答案，这个答案的最小值肯定是会在队首弹掉后被更新的，也就是说可以保证这个答案是最小的。

```
#include<bits/stdc++.h>
using namespace std;
struct dd 
{
    int x;
    int id;
}a[1000001],q[1000001];
int n; 
int head=1,tail=0;
int ans=1410065408;
int num;
int ff;
map<int,bool>gg;
map<int,int>ll;
map<int,int>c;
map<int,bool>mp2;
inline bool cmp(const dd &x,const dd &y)
{
    return x.x<y.x;
}
void read(int &x)
{
    x=0;
    char ch=getchar();
    int pd=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            pd=-pd;
        }
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=pd;
}
void write(const int &x)
{
    char f[100001];
    int s=0;
    int tmp=x;
    if(tmp<0)
    {
        tmp=-tmp;
        putchar('-');
    }
    while(tmp>0)
    {
        f[s++]=tmp%10+'0';
        tmp/=10;
    }
    while(s>0)
    {
        putchar(f[--s]);
    }
}
int main()
{
    read(n);
    for(register int i=1;i<=n;++i)
    {
        read(a[i].x);
        read(a[i].id);
        if(!gg[a[i].id])
        {
            gg[a[i].id]=1;//有些老哥可以在这个时候就可以离散化，但是我太懒了（可能是菜）就没有写，加了离散化更快，这里我就不写了。
            num++;
        }
    }
//	cout<<num;
    sort(a+1,a+n+1,cmp);
    q[1]=a[1];
    ff=1;
    c[a[1].id]++;
    head=tail=1; 
    for(register int i=2;i<=n;++i)
    {
        q[++tail]=a[i];
        if(!c[a[i].id])
        {
            ++ff;
            c[a[i].id]++;
        }
        else 
        {
            c[a[i].id]++;
        }
        while(c[q[head].id]>1&&head<=tail)
        {
            c[q[head].id]--;
            head++;
            
        }//一定要先弹掉队首再更新，不然会爆蛋。
        if(ff==num)
        {
            ans=min(ans,q[tail].x-q[head].x);
        }
    }
    write(ans);
}
```


---

## 作者：luaddict (赞：4)

先按位置排序，用一个hash表示编号。然后用【i，remain】表示所选的区间，每次将i++，然后remain向后走，直到整个区间包括所有种类的牛。这种方法叫尺取法，整个过程分为4布：


1.初始化左右端点


2.不断扩大右端点，直到满足条件


3.如果第二步中无法满足条件，则终止，否则更新结果


4.将左端点扩大1，然后回到第二步

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct ss
{
    int pos,num;
}s[70000];
int f[70000][2],t[70000],ans=-1,cnt,n;
int find(int x)
{
    int i=x%65841;
    while(f[i][0]!=x&&f[i][0])
    {
        i++;
        i%=65841;
    }
    if(!f[i][0])
    {
        f[i][1]=++cnt;
        f[i][0]=x;
        return cnt;
    }
    return f[i][1];
}
bool cmp(ss a,ss b)
{
    return a.pos<b.pos;
}
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&s[i].pos,&s[i].num);
        s[i].num=find(s[i].num);
    }
    sort(s+1,s+n+1,cmp);
    int z=0,remain=1;
    t[s[1].num]++;
    z=1;
    for(i=1;i<=n;i++)
    {
        while(z<cnt&&remain<n)
        {
            remain++;
            t[s[remain].num]++;
            if(t[s[remain].num]==1)
            z++;
        }
        if((ans==-1||ans>s[remain].pos-s[i].pos)&&z==cnt)
        ans=s[remain].pos-s[i].pos;
        t[s[i].num]--;
        if(!t[s[i].num])
        z--;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：狸狸养的敏敏 (赞：4)

这道题是一个单调队列的裸题

其实说单调队列也不是很确切，因为并没有从队头弹出再插入的操作

可以近似的看成**贪心**算法

### 贪心思路

首先，我们先把第一个元素压入队列

然后，对于每一个要进入队列的元素，在进入后，我们进行如下操作

1.将该元素代表的种类出现次数+1

2.如果队尾元素代表的种类出现了一次以上，我们就可以把队尾的元素舍弃掉，重复此操作直到队尾元素只出现了一次

3.如果队列内出现的所有种类都出现过了，更新答案

我们对上述操作逐个进行分析：

操作1，不用多讲

操作2，为什么队尾出现一次以上就可以弹掉？举个例子

下面是一个序列：（设pos = i）

`1,2,3,1,2`

最优的选法肯定是选择$[2,4]$或$[3,5]$

也就是说，后面进来的数将会给结果带来可能的更小值，而留在队尾的元素相当于拖累了答案的更新

### 为什么每一个数不进行判断就压入队列？

原因是一样的，越后面进入的数，就更有可能带来更小的结果

操作3，这个操作可以保证答案的正确性，使得我们的操作2不会舍弃掉某些中间出现的更优的答案

代码如下：
```
//Copyright (c) 2019 by xiao_mmQF. All Rights Reserved.
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
#pragma GCC optimize(3)
#define inl inline
#define reg register
#define db long double
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
using namespace __gnu_pbds;
const int MAXN=50050;
inl int read(){ int x=0,f=0; char ch=0; while(!isdigit(ch))f|=(ch=='-'),ch=getchar(); while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar(); return f?-x:x; }
inl void Ot(reg int x) { if(x<0)putchar('-'),x=-x; if(x>=10)Ot(x/10); putchar(x%10+'0'); }
inl void Print(reg int x,char til='\n'){Ot(x);putchar(til);}
inl int Max(reg int x,reg int y){return x>y?x:y;}
inl int Min(reg int x,reg int y){return x<y?x:y;}
inl int Abs(reg int x){return x<0?-x:x;}
map<int,int>mark;
map<int,bool>mk;
deque<int>que;
int n,tot,ans=INF;
struct Node{
    int pos;
    int typ;
    bool operator<(const Node &rhs)const{
        return pos<rhs.pos;
    }
}cow[MAXN];
signed main() {
    n=read();
    for(reg int i=1;i<=n;i++)
    {
        cow[i].pos=read(),cow[i].typ=read();
        if(!mk[cow[i].typ])mk[cow[i].typ]=1,tot++;//统计共有多少种不同的种类数
    }
    // printf("%lld\n",tot);
    sort(cow+1,cow+n+1);//按照pos进行排序
    for(reg int i=1,ret=0;i<=n;i++)
    {
        if(!mark[cow[i].typ])ret++;//如果是第一次出现，说明出现了一种新的种类，让种类数+1
        mark[cow[i].typ]++;//该位置代表的种类数+1
        que.push_front(i);//将当前位置推入队列
        while(que.size()&&mark[cow[que.back()].typ]>1)mark[cow[que.back()].typ]--,que.pop_back();//如果队尾的元素出现了1次以上，直接舍弃
        if(ret==tot)ans=Min(ans,cow[que.front()].pos-cow[que.back()].pos);//更新答案，维护过程中出现的可行解
        // if(!que.empty())
        // printf("(%lld,%lld) %lld\n",que.front(),que.back(),ret);
    }
    Print(ans);
    return 0 ;
}

```

---

## 作者：Celebrate (赞：3)

[我的博客](https://blog.csdn.net/zsyzClb/article/details/84672077)

刚刚看到这一题，觉得不是很难，但是一做起来，就感觉束手无策，看了一下数据范围，我感觉做法应该是O（n)或者是O(n^logn)

因为这一道题必须要排序，所以直接排除O(n）的做法

因为品种数量很大，所以要给di离散一下，可以省掉map

我想了想，决定用两个指针，分别指向左右两端，左指针for循环，右指针指向刚刚好能满足条件的那个点，并且多次记录最大值

查找时间为O（n），加上快排O（nlogn)

也可能是我看到xi<=10^9的原因吧，我竟然用了一个二分，查找时间是O（30n），因为30是常数所以时间还是O(N),

代码

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=0;char s=getchar();
    while(!isdigit(s))f|=s=='-',s=getchar();
    while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
    return !f?x:-x;
}
const int N=5e4+20;
struct node{
    int x,d;
    inline bool operator<(const node &k)const{
        return x<k.x;
    }
}a[N];int n;
struct LSnode{
    int x,z,p;
    inline bool operator<(const LSnode &k)const{
        return x<k.x;
    }
}b[N];
int bk[N];
inline bool check(int x){
    memset(bk,0,sizeof(bk));
    int p2=1,ans=1;bk[a[1].d]=1;
    for(int p1=1;p1<=n;p1++){
        if(p2==n)break;	
        while(a[p2+1].x-a[p1].x<=x&&p2<n){
            p2++;bk[a[p2].d]++;
            if(bk[a[p2].d]==1)ans++;
        }
        if(ans==b[n].z)return 1;
        bk[a[p1].d]--;
        if(!bk[a[p1].d])ans--;
    }
    return 0;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i].x=read();a[i].d=read();
        b[i].x=a[i].d;b[i].p=i;
    }
    sort(b+1,b+n+1);//离散化 
    b[1].z=1;
    for(int i=2;i<=n;i++)b[i].z=b[i-1].z+(b[i].x==b[i-1].x?0:1);
    for(int i=1;i<=n;i++)a[b[i].p].d=b[i].z;
    sort(a+1,a+n+1);
    int l=0,r=1e9,mid,ans=-1;//二分 
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}

```
打完二分以后突然发现里面的check似乎可以直接用来求最小值，于是我又打了一个不用二分的程序

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=0;char s=getchar();
	while(!isdigit(s))f|=s=='-',s=getchar();
	while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
	return !f?x:-x;
}
const int N=5e4+20;
struct node{
	int x,d;
	inline bool operator<(const node &k)const{
		return x<k.x;
	}
}a[N];int n;
struct LSnode{
	int x,z,p;
	inline bool operator<(const LSnode &k)const{
		return x<k.x;
	}
}b[N];
int bk[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();a[i].d=read();
		b[i].x=a[i].d;b[i].p=i;
	}
	sort(b+1,b+n+1);
	b[1].z=1;
	for(int i=2;i<=n;i++)b[i].z=b[i-1].z+(b[i].x==b[i-1].x?0:1);
	for(int i=1;i<=n;i++)a[b[i].p].d=b[i].z;
	sort(a+1,a+n+1);
	int p2=1,ans=1;bk[a[1].d]=1;
	int minn=1e9+10;
	for(int p1=1;p1<=n;p1++){
		while(p2<n&&ans<b[n].z){
			p2++;bk[a[p2].d]++;
			if(bk[a[p2].d]==1)ans++;
		}
		if(ans<b[n].z)break;
		minn=min(minn,a[p2].x-a[p1].x);
		bk[a[p1].d]--;
		if(!bk[a[p1].d])ans--;
	}
	printf("%d\n",minn);
	return 0;
}

```



---

## 作者：RikoHere (赞：3)

大家好，我是STL选手，我非常喜欢STL水题目

对于优先队列，也可以在$O(NlogN)$之内的时间之内解决这个问题
对于队列中的任意一个包含全部奶牛的区间$[L, R]$，设其中编号为$C_i$的奶牛存在$x$只，若$x \leq 2$那么如果除开排最左边的奶牛，会有两种结果:
 1. **该奶牛在区间最左侧，更新左边界，可能得到的答案减小**
 2. 区间大小不变
 
而且非常显然，**编号为$C_i$的奶牛若数量大于两只且存在某一只位于区间最左侧，则可以更新区间左侧，排除这只不必要的奶牛**
对于任意一个$R$，显然要更新答案我们则要取得最大的$L$，则可以通过统计区间内同种奶牛的数量来更新，在最后这个区间最左侧的奶牛显然在区间内没有其他任何一只同种奶牛

这个时候就可以使用优先队列来帮忙维护了，好写易懂，当$R$由$i-1$推进至$i$时，我们将$C_i$的统计数组加一，然后从优先队列中取出区间最左侧奶牛，若该奶牛符合退出队列的条件则将其退出队列，更新区间左边界，直到不能出队为止，计算左右距离...然后把$C_i$号奶牛入队，优先队列会自动帮我们维护它的信息在队列内的顺序...

那么很显然我们只要从头开始枚举，每枚举一个位置维护一下队列更新一下答案就完事儿了。特别的，若当前区间还未集齐所有奶牛则不更新答案(指开头的一部分)

当然本题非常easy，建议各种方法花式虐一遍，至于离散...可以百度一下.....

```
//2019/7/26->Riko->AtNCU->luoguP3029
#include<bits/stdc++.h>

namespace Rikopack {
	bool digit (int ch) { return (ch <= '9' and ch >= '0');}
	inline int in () {
		int x = 0, ch = getchar(), base = 1;
		while (!digit(ch)) {
			if (ch == '-') base = -1;
			ch = getchar();
		}
		while (digit(ch)) x = x*10+ch-'0', ch = getchar();
		return x*base;
	}
	template <class T> inline void smin (T& x, T y) { if (x > y) x = y;}
	const int MAXINT = 2123456789, MININT = -2123456789;
}
using namespace std;
using namespace Rikopack;

const int N = 50500;
struct node {
	int type, location;
	friend bool operator < (node x, node y) {
		return x.location > y.location;
	}
} Cows[N];
int n, ans = MAXINT, kinds;
int tmp[N], screened[N], numinheap[N], tag[N];
priority_queue <node> q;

void work () {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		node x = Cows[i];
		if (!screened[x.type]) ++cnt, screened[x.type] = true;
		numinheap[x.type]++;
		q.push(x);
		if (cnt >= kinds) {
			while (numinheap[q.top().type] > 1) {
				numinheap[q.top().type]--; q.pop();
			}
			smin(ans, x.location-q.top().location);
		}
	}
	printf("%d", ans);
}
void prepare () {
	n = in();
	for (int i = 1; i <= n; ++i) {
		Cows[i].location = in();
		tmp[i] = Cows[i].type = in();
	}
	sort(Cows+1, Cows+n+1);
	reverse(Cows+1, Cows+n+1);
	sort(tmp+1, tmp+n+1);
	int len = unique(tmp+1, tmp+n+1)-tmp-1;
	for (int i = 1; i <= n; ++i) {
		int& P = Cows[i].type;
		P = lower_bound(tmp+1, tmp+len+1, P)-tmp;
		if (!tag[P]) tag[P] = true, ++kinds;
	}
	work();
} 
int main () { prepare();}
```


---

## 作者：1saunoya (赞：2)

$\text{单调队列裸题}$

单调队列里的元素全部是单调上升/下降的。

根据这个性质我们可以考虑排序
如果出现了相同的数字 那么我们把 l ++ 即 pop 前面的数字

$\mathcal Code$

```cpp
#include<bits/stdc++.h>
using namespace std ;

int n ;
const int N = 100000 + 5 ;
struct node {
	int pos ;
	int id ;
	bool operator < (const node & _Other) const {
		return pos < _Other.pos ;
	}
}f[N] , q[N] ;

map < int , int > cnt ;
map < int , int > b ;
signed main() {
	ios :: sync_with_stdio(false) ;
	cin >> n ;
	int num = 0 ;
	for(register int i = 1 ; i <= n ; i ++) {
		cin >> f[i].pos >> f[i].id ;
		b[f[i].id] ++ ;
		if(b[f[i].id] == 1) ++ num ;
	}
	sort(f + 1 , f + n + 1) ;
	int ans = INT_MAX ;
	int l = 1 , r = 0 , tot = 0 ;
	for(register int i = 1 ; i <= n ; i ++) {
		if(! cnt[f[i].id]) {
			cnt[f[i].id] = 1 ;
			tot ++ ;
		}
		else {
			cnt[f[i].id] ++ ;
		}
		q[++ r] = {f[i].pos , f[i].id} ;
		while(cnt[q[l].id] > 1) {
			-- cnt[q[l ++].id] ;
		}
		if(num == tot) ans = min(ans , q[r].pos - q[l].pos) ;
	}
	cout << ans << endl ;
	return  0;
}

---

## 作者：关怀他人 (赞：2)

## 二分+主席树(毒瘤做法）

~~貌似还没有这样做的题解(逃~~

由于种类数比较大，所以要先进行**离散化**。

因为右端点具有**单调性**（较小的右端点能满足条件,那么较大的右端点也一定能满足条件），所以我们可以**枚举左端点，二分右端点**。

但是在check时会有问题，那就是如何迅速求出一个区间内不同种类的数的个数呢？
#### 于是就可以想到处理区间种类个数的神器———— **主席树**

不会的可以先去看下[[SDOI2009]HH的项链](https://www.luogu.org/problemnew/show/P1972), 求区间不同种类数的模板题

于是这道题就做完了，总时间复杂度$O(nlog^2n)$

**下面给出代码**
```cpp
/*
Problem : luogu P3029
Algorithm : 主席树+二分
Status : AC
*/
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int INF = 0x3f3f3f3f;
const int MAXN = 50005;

int n,m,tot,cnt,ans = INF;
int last[MAXN * 2],root[MAXN],pos[MAXN],type[MAXN];
map<int,bool> used;

struct Tree{
	int l,r;
	int val;
} tree[MAXN * 40];

struct Node{
	int pos,type;
	friend bool operator < (const Node &x,const Node &y){
		return x.pos < y.pos;
	}
} a[MAXN];


int build(int l,int r){
	int now = ++tot;
	if(l == r)
	    return now;
	int mid = (l + r) / 2;
	tree[now].l = build(l,mid);
	tree[now].r = build(mid + 1,r);
	return now;
}

int insert(int pre,int l,int r,int x,int v){ //主席树的插入
	int now = ++tot;
	tree[now].l = tree[pre].l;
	tree[now].r = tree[pre].r;
	if(l == r){
		tree[now].val = tree[pre].val + v;
		return now;
	}
	int mid = (l + r) / 2;
	if(x <= mid)
	    tree[now].l = insert(tree[pre].l,l,mid,x,v);
	else
	    tree[now].r = insert(tree[pre].r,mid + 1,r,x,v);
	tree[now].val = tree[tree[now].l].val + tree[tree[now].r].val;
	return now;
}

int query(int pre,int l,int r,int x){ //主席树的查询
	if(l == r)
	    return tree[pre].val;
	int mid = (l + r) / 2;
	if(x <= mid)
	    return query(tree[pre].l,l,mid,x) + tree[tree[pre].r].val;
	else
	    return query(tree[pre].r,mid + 1,r,x);
}

bool check(int l,int r){
	return query(root[r],1,n,l) == cnt; //判断l,r这个区间是否包含所有种类的牛
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
	   scanf("%d%d",&a[i].pos,&a[i].type);
	   if(!used[a[i].type]){
	        used[a[i].type] = 1;
	    	type[++cnt] = a[i].type; //cnt : 种类总数
	   }
	}
	sort(type + 1,type + 1 + cnt); //对牛的种类进行离散化
	for(int i = 1;i <= n;i++)
	    a[i].type = lower_bound(type + 1,type + 1 + cnt,a[i].type) - type;
	sort(a + 1,a + 1 + n); //按坐标排序
	/*
	for(int i = 1;i <= n;i++)
	    cout << i << " : " << a[i].pos << " " << a[i].type << endl;
	*/
	memset(last,-1,sizeof(last));
	root[0] = build(1,n);
	for(int i = 1;i <= n;i++){
		int x = a[i].type;
		if(last[x] == -1)
		        root[i] = insert(root[i - 1],1,n,i,1);
		else{
			int t = insert(root[i - 1],1,n,last[x],-1);
			root[i] = insert(t,1,n,i,1);
		}
		last[x] = i;
	} //构造主席树
	for(int i = 1;i <= n;i++){
		int l = i,r = n,tmp = 0;
		while(l <= r){ //二分
			int mid = (l + r) / 2;
			if(check(i,mid)){
				tmp = mid;
				r = mid - 1;
			}else
			        l = mid + 1;
		}
		if(tmp != 0){
	            //cout << tmp << " " << i << endl;
		    ans = min(ans,a[tmp].pos - a[i].pos); //统计答案
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

**对于牛的编号，我们发现牛的编号最大会到1亿，但对于那么大的数值，我们就不能利用桶来判断所有编号的牛是否都被拍在这张照片里了。所以，我们要通过hash来缩小牛的编号，在这里，我对于数值hash的值为6000，当然，也可以是其他值。**

**当然，你也发现，牛的位置是无序的，你想到了什么？当然是一个快排！**

**然后，我们用一重循环来枚举这张照片的左端点的牛，另外还有一个变量记录这张照片的右端点。这个右端点肯定不能一次次从第一头牛开始往后扫，我们要沿着上一次到达的牛继续往后扫，知道满足题目的条件为止。**

```cpp
var n,s,i,x,y,ans:longint;
     a,b:array[1..50005]of longint;
    f:array[0..70000,0..1]of longint;//为hash服务
    t:array[0..70000]of longint;//这是一个桶，用来统计当前的牛的头数，这对于后面的计算有多少头牛在这张照片里面是十分重要的。
procedure qsort(l,r:longint);//快排
var i,j,mid,t,t1:longint;
begin
  i:=l;j:=r;mid:=(i+j)div 2;
  t:=a[mid];t1:=b[mid];
  a[mid]:=a[l];b[mid]:=b[l];
  while i<j do
    begin
      while (i<j)and(a[j]>t) do dec(j);
      if i<j then
        begin
          a[i]:=a[j];b[i]:=b[j];inc(i);
        end;
      while (i<j)and(a[i]<t) do inc(i);
      if i<j then
        begin
          a[j]:=a[i];b[j]:=b[i];dec(j);
        end;
    end;
  a[i]:=t;b[i]:=t1;
  if i+1<r then qsort(i+1,r);
  if i-1>l then qsort(l,i-1);
end;
function hash(x:longint):longint;//hash处理
var j:longint;
begin
  j:=x mod 60000;
  while f[j,0]<>x and f[j,0] do
    begin
      j:=j+1;
      j:=j mod 60000;
    end;
  if f[j,0]=0 then
    begin
      s:=s+1;f[j,1]:=s;f[j,0]:=x;
    end; 
  exit(f[j,1]);
end;
begin
  readln(n);
  for i:=1 to n do 
    begin
      readln(a[i],b[i]);
      b[i]:=hash(b[i]);//牛的编号进行hash处理
    end;
  qsort(1,n);//对于牛的位置进行排序
  x:=1;y:=1;inc(t[b[1]]);ans:=-1;//预处理
  for i:=1 to n do
    begin
      while (x<s)and(y<n) do//所有种数的牛还没有都在这张照片并且我们还没有枚举完所有的奶牛。
        begin
          inc(y);inc(t[b[y]]);//加上这头牛的种类
          if t[b[y]]=1 then inc(x);//如果这头牛在这张照片第一次出现，说明这张照片中有出现一种新的奶牛。
        end;
      if ((ans=-1)or(ans>a[y]-a[i]))and(x=s) then//如果ans是-1，或者当前的照片的长度比我们以前求出的最优值小，并且所有种类的牛都出现在这张照片中，就立即更新。
        ans:=a[y]-a[i];
      dec(t[b[i]]);//把当前最左端的牛从这张照片中去除。
      if t[b[i]]=0 then dec(x);//如果最左端的这种牛在照片中没了，不同的牛数就-1。
    end;
  writeln(ans);
end.
```

---

## 作者：RainFestival (赞：0)

这道题我们可以使用类似[P1638](https://www.luogu.org/problemnew/show/P1638)的方法，但是请注意 
## 1≤ID_i≤1,000,000,000

这是什么意思？？

我们不能用普通方法做，必须离散化一下

不过我用了一种牺牲了正确性的方法，确实AC了

先将每个id %(mod)10e7+7

再按照普通方法做

就AC了

因为N<=50000,冲突的可能性很小

下面附代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int x[50005],d[50005],q[50005],a[10000050];
int n;
void qsort(int l,int r)
{
    int i=l;
    int j=r;
    long long x1=x[(i+j)/2];
    do
    {
        while (x[i]<x1) i++;
        while (x[j]>x1) j--;
        if (i<=j) 
        {
            long long t;
            t=x[i];
            x[i]=x[j];
            x[j]=t;
            t=d[i];
            d[i]=d[j];
            d[j]=t;
            i++;
            j--;
        }   
    }while (i<=j);  
    if (l<j) qsort(l,j);
    if (i<r) qsort(i,r);
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&d[i]);
    qsort(1,n);
    int s=0;
    for (int i=1;i<=n;i++)
    {
        q[i]=d[i]%(10000007);
        a[q[i]]++;
        if (a[q[i]]==1) s++;
    }
    int s1=0;
    for (int i=0;i<=(10000007);i++) a[i]=0;
    int j=0,ans=2000000000;
    for (int i=1;i<=n;i++)
    {
        a[q[i]]++;
        if (s1<s) if (a[q[i]]==1) s1++;
        if (s1==s)
        {
        	while (a[q[j+1]]-1>0)
        	{
        		j++;
        		a[q[j]]--;
            }
            ans=min(ans,x[i]-x[j+1]);
        }
    }
    printf("%d",ans);
    return 0;  
}
```


时间660ms,空间40234KB,代码长度1.12kb

谢谢观赏

---

## 作者：Red_w1nE (赞：0)

Solution Notes:

This is a somewhat interesting problem since there are several nice algorithmic ways to approach its solution. The problem can be solved in O(N log N) time due to the need to sort the cows by x coordinate as a preprocessing step.

One nice method (perhaps not the simplest, but worth mentioning) is the following:

we sort scan through the cows from left to right (i.e., by x coordinate) keeping track of the most recent occurrence of each ID in a data structure. For example, if we are visiting a cow at (x,ID) = (10,17), our data structure might tell us that the most recent previous occurrence of a cow with breed ID 17 was at x=3, at which point we would then update the record in the data structure to x=10 and continue scanning (for IDs that have not yet occurred, we keep track of the value -infinity).

Now as we scan over a particular coordinate x, let us suppose x is the right endpoint of a photograph window; we can compute the best possible matching left endpoint by simply taking the minimum of all the "most recent occurrence" x values in our data structure, so if we use an appropriate data structure like a heap, we can determine this minimum very quickly, making the entire scan take only O(N log N) time. During the scan, we simply remember the largest window we have seen.


A slightly simpler approach involves scanning both the left and right endpoint of the photograph window in a monotonic fashion in lock step. We start with left = right = the leftmost cow. We then advance the right pointer whenever we notice that not every type of breed ID is present in the window; otherwise we advance the left pointer (noting the size of the window in this case, so we can return the largest over the entire scan). We can tell whether every breed ID exists within our window by storing a count of each breed ID within the window in a data structure like a map or multiset (or even a simple array would work, if we first sort the IDs and then map them down to integers in the range 0...N-1 as a preprocessing step). The breed ID counts are incremented whenever we advance the right pointer and decremented whenever we advance the left pointer.

【参考程序】




```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef struct {
  int loc, id;
} Cow;
int sort_cows(const void* v1, const void *v2) {
  Cow *c1 = (Cow*)v1, *c2 = (Cow*)v2;
  return c1->loc>c2->loc;
}
//写一个cmp()函数，按位置排序
```
/\*
```cpp
int cmp(Cow a, Cow b)
{
    return a.loc < b.loc;
}
```
\*/
   
   
   



      


  
```cpp
int main() {
   freopen("lineup.in", "r", stdin); 
freopen("lineup.out", "w", stdout);
   int num_IDS, N, i, num_in_map = 0, A[50000], IDS[50000];
int start, end, min;
   Cow cows[50000];
   map<int, int> breeds;
   set<int> ID_set;
   scanf("%d", &N);
for(i=0; i<N; i++) {
      scanf("%d %d", &cows[i].loc, &cows[i].id);
      ID_set.insert(cows[i].id);
      breeds[cows[i].id] = 0;
   }
   sort(cows, N, sizeof(Cow), sort_cows);
   // sort(cows, cows+n, cmp);  按位置排序
   num_IDS = ID_set.size();
   start = 0;
   end = 0;
   min = 1<<30;    // minv, 左移运算
   while(1) {
      while(num_in_map!=num_IDS && end<N) {
         if(breeds[cows[end].id]==0)   num_in_map++;
         breeds[cows[end].id]++;
end++;
      }
      if(end==N && num_in_map!=num_IDS)  break;
      while(breeds[cows[start].id]>1)
      {
         breeds[cows[start].id]--;
start++;
      }
     if(cows[end-1].loc-cows[start].loc<min) 
min = cows[end-1].loc-cows[start].loc;
     breeds[cows[start].id]--;   //什么意思？
     start++;
     num_in_map--;
  }
  printf("%d\n", min);
  return 0;
}

```

---

