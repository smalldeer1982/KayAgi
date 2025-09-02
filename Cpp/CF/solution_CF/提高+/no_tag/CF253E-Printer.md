# Printer

## 题目描述

Let's consider a network printer that functions like that. It starts working at time 0. In each second it can print one page of a text. At some moments of time the printer receives printing tasks. We know that a printer received $ n $ tasks. Let's number the tasks by consecutive integers from 1 to $ n $ . Then the task number $ i $ is characterised by three integers: $ t_{i} $ is the time when the task came, $ s_{i} $ is the task's volume (in pages) and $ p_{i} $ is the task's priority. The priorities of all tasks are distinct.

When the printer receives a task, the task goes to the queue and remains there until all pages from this task are printed. The printer chooses a page to print each time when it either stops printing some page or when it is free and receives a new task. Among all tasks that are in the queue at this moment, the printer chooses the task with the highest priority and next second prints an unprinted page from this task. You can assume that a task goes to the queue immediately, that's why if a task has just arrived by time $ t $ , the printer can already choose it for printing.

You are given full information about all tasks except for one: you don't know this task's priority. However, we know the time when the last page from this task was finished printing. Given this information, find the unknown priority value and determine the moments of time when the printer finished printing each task.

## 说明/提示

Let's consider the first test case. Let's assume that the unknown priority equals 4, then the printer's actions for each second are as follows:

- the beginning of the 1-st second (time 0). The queue has task 2. The printer prints the first page of this task;
- the beginning of the 2-nd second (time 1). The queue has tasks 2 and 3. The printer prints the first page of task 3;
- the beginning of the 3-rd second (time 2). The queue has tasks 2 and 3. The printer prints the second page of task 3;
- the beginning of the 4-th second (time 3). The queue has tasks 2 and 3. The printer prints the third (last) page of task 3. Thus, by the end of the 4-th second this task will have been printed;
- the beginning of the 5-th second (time 4). The queue has tasks 2 and 1. The printer prints the first page of task 1;
- the beginning of the 6-th second (time 5). The queue has tasks 2 and 1. The printer prints the second page of task 1;
- the beginning of the 7-th second (time 6). The queue has tasks 2 and 1. The printer prints the third (last) page of task 1. Thus, by the end of the 7-th second this task will have been printed;
- the beginning of the 8-th second (time 7). The queue has task 2. The printer prints the second (last) page of task 2. Thus, by the end of the 8-th second this task will have been printed.

In the end, task number 1 will have been printed by the end of the 7-th second, as was required. And tasks 2 and 3 are printed by the end of the of the 8-th and the 4-th second correspondingly.

## 样例 #1

### 输入

```
3
4 3 -1
0 2 2
1 3 3
7
```

### 输出

```
4
7 8 4
```

## 样例 #2

### 输入

```
3
3 1 2
2 3 3
3 1 -1
4
```

### 输出

```
4
7 6 4
```

# 题解

## 作者：AThls123 (赞：2)

远古题居然没有人发题解，那我发一篇。

## 做法一(大众做法)
二分 $p[x]$ 的值然后用优先队列模拟就好了，思路还是很好想的。

## 做法二（本人的做法）
### 1. 若没有 $p[x] = -1$

考虑把每个时刻连成一段区间，时刻看成一个个整点，设开始时间为初始值，将所需要的时间变为所需要的整点数量，所以题目意思就可以转换为有 $n$ 个结构体，这 $n$ 个结构体有一个初始值和所需要的整点数量，你要从 $[x+1,\infty ]$ 中选取一些点，点的位置越小越好，其次还要考虑优先度，优先度大的先选点，优先的小的后选点，求每结构体的最后所选点的位置。

做法如下：

先将点按优先度大小排个序，然后把所有 $[1,\infty ]$ 上的点权设为一，如果用过了就设为零，然后找点填入就好了，实现用线段树上二分即可。

### 2. 若有 $p[x] = -1$ 

为了简单表述题意，我将 $p[x] = -1$ 的结构体设为目标结构体。

按照上面的做法，但要加一条查询的操作，看当前状态下的目标结构体是否能成立，如果成立就可以寻找目标的优先度了。

首先优先度一定是比上一次操作的要小，比下一次涉及到目标所选区间的操作要大，这样就直接枚举就好了，比如说上一次操作优先度大小减一，当然特殊情况要特殊判断。


注意：如果要开整整一棵线段树的话明显就会爆空间，所以我们要用动态开点的线段树。
```cpp
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<iostream>
using namespace std;
long long read(){char c;int sign=1;
    while((c=getchar())<'0'||c>'9')if(c=='-')sign=-1;long long res=c-'0';
    while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';return res*sign;
}
const int N=5e4+7;
int n,m;
long long ans[N];
struct node{
    long long t,s,p; int id;
    bool operator < (const node &other){return p<other.p;}
} task[N];
long long id,maxs,sum;int rt;
struct Tree{
    long long tr[N*160];
    int ls[N*160],rs[N*160],cnt;
    long long len(long long l,long long r){return r-l+1;}
    void pushup(int k,long long l,long long r){
        if(tr[k]==0)return ;// 用过了的点就不要让他在用了
        long long mid=(l+r)/2,ans1=0,ans2=0;
        if(!ls[k]) ans1=len(l,mid);
        if(!rs[k]) ans2=len(mid+1,r);
        tr[k]=tr[ls[k]]+tr[rs[k]]+ans1+ans2;
    }
    long long query(int &k,long long l,long long r,long long x,long long y){
        if(!k){
            k=++cnt;
            tr[k]=len(l,r);
        }
        if(tr[k]==0)return 0;
        if(l>=x&&r<=y)return tr[k];
        long long mid=(l+r)/2,ans=0;
        if(x<=mid&&(!ls[k]||tr[ls[k]]!=0))ans+=query(ls[k],l,mid,x,y);
        if(mid<y&&(!rs[k]||tr[rs[k]]!=0))ans+=query(rs[k],mid+1,r,x,y);
        return ans;
    }
    void change_0(int &k,long long l,long long r,long long x,long long y){
        if(l>y||r<x)return ;
        if(!k){ k=++cnt; tr[k]=len(l,r); }
        if(l==r){ tr[k]=0; ans[id]=l; return ; }
        long long mid=(l+r)/2;
        if(l>=x&&r<=y){ tr[k]=0; return ; }
        if(x<=mid)change_0(ls[k],l,mid,x,y);
        if(mid<y)change_0(rs[k],mid+1,r,x,y);
        pushup(k,l,r);
    }
    void change(int &k,long long l,long long r,long long x,long long y,long long v,int id){
        if(!k){ k=++cnt; tr[k]=len(l,r); }
        if(l==r){ tr[k]=0; ans[id]=l; return ; }
        if(v==0){ ans[id]=l; tr[k]=0; return ; }
        long long mid=(l+r)/2;
        long long ssum=query(ls[k],l,mid,x,y);
        if(ssum<v){
            change_0(ls[k],l,mid,x,y);
            change(rs[k],mid+1,r,x,y,v-ssum,id);
        }
        if(ssum>=v) change(ls[k],l,mid,x,y,v,id);
        pushup(k,l,r);
    }
}Tr; // 线段树部分应该很好理解的吧
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    n=read();
    for(int i=1;i<=n;++i){
        task[i].id=i;
        task[i].t=read();
        task[i].s=read();
        task[i].p=read();
        sum+=task[i].s+task[i].t;//选取范围
    }
    long long T=read();
    bool flag=true;//用来判断目标结构体是否已经被选过了
    sort(task+1,task+1+n);//按照优先度排序
    for(int i=n;i>1;--i){
        if(flag){
            if(Tr.query(rt,1,sum,task[1].t+1,T)==task[1].s){//如果当前刚刚好满足条件，就可以寻找 p[x] 的值了
                if(i==n) task[1].p=task[n].p+1;//特殊情况
                else {
                    for(int j=i;j>1;--j){
                        if(task[j].p!=task[j+1].p-1){
                            task[1].p=task[j+1].p-1;
                            break;
                        }
                    }
                }
                Tr.change(rt,1,sum,task[1].t+1,sum,task[1].s,task[1].id);//线段树上二分
                flag=false;
            }
        }
        Tr.change(rt,1,sum,task[i].t+1,sum,task[i].s,task[i].id);//线段树上二分
    }
    if(flag){
        if(task[2].p)task[1].p=task[2].p-1;
        else task[1].p=1;
        ans[task[1].id]=T;
    }//到最后了如果还没有就直接写答案，优先度什么的直接就可以出来了，可能不需要这样写，但我还是要写
    printf("%lld\n",task[1].p);
    for(int i=1;i<=n;++i)printf("%lld ",ans[i]);puts("");
    return 0;
}

```


---

## 作者：Imerance1018 (赞：0)

### Description

[传送门](https://codeforces.com/problemset/problem/253/E)

### Solution


不妨设 $p$ 值未知的任务编号为 $pos$。

那么随着 $p_{pos}$ 的增大，完成任务的时刻 $res_{pos}$ 单调不上升。

所以考虑对 $pos$ 进行二分答案。

对于每个二分出的答案 $mid$，使用优先队列模拟打印过程，再将结果 $res_{pos}$ 与输入的 $T$ 比较。

总复杂度 $O(n \log^2 n)$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+10;
int n,T,pos,ans,res[N];
struct node
{
	int t,s,p,num;
}a[N],b[N];
bool cmp(node x,node y)
{
	return x.t<y.t;
}
struct Node
{
	int num,val;
	bool operator <(const Node &x)const
	{
		return val<x.val;
	}
};
priority_queue<Node>q;
bool judge(int x)//直接模拟，但要注意细节（我感觉 2200 分就是因为这个模拟难写）
{
	int now=0;
	for(int i=1;i<=n;i++)res[i]=0,b[i]=a[i];
	for(int i=1;i<=n;i++)
	{
		now=b[i].t;
		if(b[i].num==pos)b[i].p=x;
		q.push((Node){i,b[i].p});
		if(i==n)break;
		while(!q.empty())
		{
			int tmp=q.top().num;
			q.pop();
			if(b[tmp].s+now-1<b[i+1].t)
			{
				res[b[tmp].num]=b[tmp].s+now;
				now=b[tmp].s+now;
			}
			else
			{
				b[tmp].s-=(b[i+1].t-now);
				q.push((Node){tmp,b[tmp].p});
				now=b[i+1].t;
				break;	
			}
		}
	
	}
	while(!q.empty())
	{
		int tmp=q.top().num;
		q.pop();
		res[b[tmp].num]=b[tmp].s+now;
		now=b[tmp].s+now;
	}
	return res[pos]>=T;
}
signed main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].t>>a[i].s>>a[i].p;
		a[i].num=i;
		if(a[i].p==-1)pos=i;
	}
	cin>>T;
	sort(a+1,a+n+1,cmp);//注意 a[i].t 为乱序
	int L=1,R=1e9;
	while(L<=R)
	{
		int mid=(L+R)/2;
		if(judge(mid))ans=mid,L=mid+1;
		else R=mid-1;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i].p==ans)
		{
			ans--;
			break;
		}
	}//此处是因为 p 各不相同
	cout<<ans<<endl;
	judge(ans);
	for(int i=1;i<=n;i++)cout<<res[i]<<" ";
	return 0;
}
``````

---

