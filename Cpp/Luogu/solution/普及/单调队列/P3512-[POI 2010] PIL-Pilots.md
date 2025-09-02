# [POI 2010] PIL-Pilots

## 题目描述

In the Byteotian Training Centre, the pilots prepare for missions requiring extraordinary precision and control.

One measure of a pilot's capability is the duration he is able to fly along a desired route without deviating too much -    simply put, whether he can fly steadily. This is not an easy task, as the simulator is so sensitive that it registers    even a slightest move of the yoke1.

At each moment the simulator stores a single parameter describing the yoke's position.

Before each training session a certain tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.1.png) is set.

The pilots' task then is to fly as long as they can in such a way that all the yoke's position measured during the    flight differ by at most ![](http://main.edu.pl/images/OI17/pil-en-tex.2.png). In other words, a fragment of the flight starting at time ![](http://main.edu.pl/images/OI17/pil-en-tex.3.png) and ending at time ![](http://main.edu.pl/images/OI17/pil-en-tex.4.png)    is within tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.5.png) if the position measurements, starting with ![](http://main.edu.pl/images/OI17/pil-en-tex.6.png)-th and ending with ![](http://main.edu.pl/images/OI17/pil-en-tex.7.png)-th,    form such a sequence ![](http://main.edu.pl/images/OI17/pil-en-tex.8.png) that for all elements ![](http://main.edu.pl/images/OI17/pil-en-tex.9.png) of this sequence, the inequality ![](http://main.edu.pl/images/OI17/pil-en-tex.10.png) holds.

Your task is to write a program that, given a number ![](http://main.edu.pl/images/OI17/pil-en-tex.11.png) and the sequence of yoke's position measurements,    determines the length of the longest fragment of the flight that is within the tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.12.png).

给定 $n, k$ 和一个长度为 $n$ 的序列，求最长的最大值最小值相差不超过 $k$ 的子段。

## 说明/提示

样例解释：$5, 8, 6, 6$ 和 $8, 6, 6, 9$ 都是满足条件长度为 $4$ 的子段。

## 样例 #1

### 输入

```
3 9
5 1 3 5 8 6 6 9 10```

### 输出

```
4```

# 题解

## 作者：alksdjhfg (赞：29)

n<=3000000，单调队列。

因为要同时维护最大值和最小值，所以需要两个单调队列，记录序号和最大最小值，然后

从左往右枚举一遍O(n)的复杂度即可。

单调队列的实现以最大值为例，当队列非空且队尾的数没有现在枚举到的这个数大时，就

让队尾的数出队，因为在接下来的情况中它们永远不会是一个区间的最大值。最小值的队列同理。把当前位置加入最大最小值队列。然后比较最大值队列的队首即最大值和最小值，如果它们的差超过了k，就看一下最大值和最小值的队首哪个的序号更小，让序号更小的出队，同时更新当前队列的最前节点的位置，继续比较两个的队首，直到最大最小值的差小于等于k时，用当前位置减去当前队列的最前节点的位置再加一，就是目前的符合条件的序列长度，与最长值比较即可。

当前队列的最前节点的位置初始值为1.

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
ll k,n,a[3000005],q_mx[3000005],q_mn[3000005];
ll head_mx,head_mn,tail_mx,tail_mn,len,pre;
int main(){
//    freopen("1.in","r",stdin);
    scanf("%lld%lld",&k,&n);
    len=0;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    q_mx[1]=1;q_mn[1]=1;pre=1;
    head_mx=1;tail_mx=1;head_mn=1;tail_mn=1;
    for(int i=2;i<=n;i++){
        while(head_mx<=tail_mx&&a[q_mx[tail_mx]]<a[i])tail_mx--;
        while(head_mn<=tail_mn&&a[q_mn[tail_mn]]>a[i])tail_mn--;
        q_mx[++tail_mx]=i;q_mn[++tail_mn]=i;
        while(a[q_mx[head_mx]]-a[q_mn[head_mn]]>k){
            if(q_mx[head_mx]<q_mn[head_mn]){pre=q_mx[head_mx]+1;head_mx++;}
            else {pre=q_mn[head_mn]+1;head_mn++;}
        }
        //pre=min(q_mx[head_mx],q_mn[head_mn]);
        len=max(len,i-pre+1);
    }
    printf("%lld",len);
}
```

---

## 作者：天梦 (赞：10)

# P3512

[链接](https://www.luogu.com.cn/record/52272024)

限制与最大值最小值有关，所以我们考虑维护最大值最小值。

可以用双指针，但同时需要维护最大值最小值出现次数，但我们并维护不了任意区间内的最大值最小值。

考虑单调队列。

因为单调队列只能维护一个最值，所以我们开两个队列，一个维护最大值，一个维护最小值。

用 $last$ 维护最左边合法位置的前一个是多少。

然后每当遇见不合法状态，我们就更新答案。
遇见不合法状态时，显然两个队列中肯定有一个队列只有一个元素，我们不断删除另一个队列的对头知道符合题目要求，然后更新 $last$ 即可。

时间复杂度 $O(n)$ 

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 3000100
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

ll n,k,a[N],qmin[N],lmin,rmin,ans,last,qmax[N],lmax,rmax;

int main(){
    read(k);read(n);
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=n;i++){
        while(lmax<rmax&&a[qmax[rmax]]<a[i]) rmax--;
        while(lmin<rmin&&a[qmin[rmin]]>a[i]) rmin--;
        qmax[++rmax]=i;qmin[++rmin]=i;
        if(a[qmax[lmax+1]]-a[qmin[lmin+1]]>k){
            ans=max(ans,i-1-last);
            if(lmax+1==rmax){
                while(a[i]-a[qmin[lmin+1]]>k) lmin++;last=qmin[lmin];
            }
            if(lmin+1==rmin){
                while(a[qmax[lmax+1]]-a[i]>k) lmax++;last=qmax[lmax];
            }
        }
    }
    ans=max(n-last,ans);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Godzilla (赞：6)

### 题目大意：

给定一个序列，求出一个最长的序列 $(i,j)$ ，使得其中最大值与最小值的差不超过 $k$ 。

---

### 前置知识：

1.单调队列 。

---

### 思路：

这道题是一个区间问题，可以采用枚举左端点，快速查找右端点的思路。

由于 $n \le 3000000$ ，~~所以，我们可以猜测，这道题是 $O(n)$ 的做法。~~

那么 $O(n)$ ，枚举左端点，$O(1)$ 查找右端点，最常用的方法，是什么呢？

就是单调队列！

根据这道题的规定，不管有没有用，可以 $O(1)$ 处理出每个点右边的上升序列和下降序列。

考虑如何处理出右端点。

不能盲目查找，这时候，又一个区间常用策略来了，单调性。

对于一个以 $i$ 为左端点，$j$ 为满足规定的最长的以 $i$ 为左端点的序列，那么对于 $(i+1)$ ，左端点不需要 $< j$ ，

因为 $i$ 都已经不满足规定了，而集合的增大不会减小最大值，增大最小值，从而最大值与最小值的差永远 $>k$ 。

假设上升序列的对首为 $s1$ ，下降序列为 $s_2$ ，假如 $a_{s_2}-a_{s_1}>k$ ，是移动 $s_1$ ，还是移动 $s_2$ 呢 ?

想到规定当中的最长序列，那么假设 $s_2$ 的位置 $>$ $s_1$ 的位置，那么肯定是移动 $s_2$ 最优，反之，同理。

---

### 代码：

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int kMax=3e6+5;
const int kInf=1e9;

int k,n;
int a[kMax];
int ans;

int s1[kMax],s2[kMax],t1,t2,h1=1,h2=1;//s1递减,s2递增

int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;++i){scanf("%d",&a[i]);}
	for(int i=1;i<=n;++i){
		bool flag=1;
		while(t1>=h1&&a[s1[t1]]<=a[i]){t1--;}	
		s1[++t1]=i;
		while(t2>=h2&&a[s2[t2]]>=a[i]){t2--;}
		s2[++t2]=i;
		while(a[s1[h1]]-a[s2[h2]]>k){
			if(h1<t1&&s1[h1]<s2[h2]){h1++;}
			else if(h2<t2){h2++;}
			else{flag=0;break;}
		}
		if(flag){ans=max(ans,i-max(s1[h1-1],s2[h2-1]));}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：raincity (赞：5)

## 题意简述
给定$n$,$k$和一个长度为$n$的序列，求最长的最大值最小值相差不超过k的序列。

## 分析
这是一道单调队列的好题！

首先，数据范围$n$<=3000000=3e6。大概能猜到算法时间复杂度为$O(n)$或者是$O(n\log(n))$。

这题当然可以用二分做：

可以二分答案，并用单调队列检查每一个区间内最大最小值的差是否不大于k。时间复杂度是$O(n\log(n))$

当然，这里讲的是$O(n)$做法。

我们可以依次枚举以每一个点作为区间的终点，并维护最大最小值的单调队列，有以下三种情况：

1. 不更新最小值，也不更新最大值。加进去后仍然满足条件。
1. 更新最小值，则最大值队列要一直pop到最大值与最小值之差不大于$k$。同时，记录队首为pop掉的位置+1，之后遇到位置小于队首位置的元素就pop掉。
1. 更新最大值。类似于更新最小值。

代码实现即可。作为一个懒人，我用了STL。

## 解答
直接上代码：

```cpp
#include<iostream>
#include<deque>
#include<cstdio> 
using namespace std;

const int N=3000005;
int k,n,head=1,ans=1;//ans至少是1,head表示当前队首 
struct node{
	int data;//值 
	int pos;//位置 
}a[N];
deque<node> maxdq,mindq;//维护最大最小值的单调队列 

int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].data);
		a[i].pos=i;
	}
	for(int i=1;i<=n;i++){
		bool upmin=a[i].data<mindq.front().data;//是否更新最小值 
		bool upmax=a[i].data>maxdq.front().data;//是否更新最大值 
		while(!maxdq.empty()&&maxdq.front().pos<head) maxdq.pop_front();//在head之前，pop掉 
		while(!mindq.empty()&&mindq.front().pos<head) mindq.pop_back();//在head之前，pop掉
		while(!maxdq.empty()&&maxdq.back().data<a[i].data) maxdq.pop_back();//不满足单调性，pop掉 
		while(!mindq.empty()&&mindq.back().data>a[i].data) mindq.pop_back();//不满足单调性，pop掉 
		maxdq.push_back(a[i]);mindq.push_back(a[i]);//将a[i]入队 
		if(upmin==false&&upmax==false)//既没有更新最小值，也没有更新最大值 
			ans=max(ans,i-head+1);//仍然可行，更新答案 
		else if(upmin){//更新了最小值 
			while(!maxdq.empty()&&maxdq.front().data-a[i].data>k){//不满足条件，需要减短队列 
				head=maxdq.front().pos+1;//更新队首 
				maxdq.pop_front();//弹出队首 
			}
			ans=max(ans,i-head+1);//更新答案 
		}
		else{
			while(!mindq.empty()&&a[i].data-mindq.front().data>k){//不满足条件，需要减短队列
				head=mindq.front().pos+1;//更新队首
				mindq.pop_front();//弹出队首 
			}
			ans=max(ans,i-head+1);//更新答案 
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

## THE END

---

## 作者：LightningUZ (赞：4)

我比较懒，由于怕爆格式，直接贴了[blog](https://blog.csdn.net/LightningUZ)上的链接。

代码（~~先把你们最想要的的贴出来~~）：
```cpp
//我的码风清奇，想抄要改好久
#include<bits/stdc++.h>
#define N 3001000
#define int long long
using namespace std;

int k,n;
int a[N];
void Input()
{
    scanf("%lld%lld",&k,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
}

int Qx[N],Qn[N];
int hx,tx,hn,tn,h,t;
void Solve()
{
    hx=tx=hn=tn=h=t=1;
    Qx[1]=Qn[1]=1;
    int ans=1,pre=1;
    for(int i=2;i<=n;i++)
    {
        while(hx<=tx and a[Qx[tx]]<a[i]) tx--;
        Qx[++tx]=i;
        while(hn<=tn and a[Qn[tn]]>a[i]) tn--;
        Qn[++tn]=i;

        #define Fn (Qn[hn])
        #define Fx (Qx[hx])
        while(a[Fx]-a[Fn]>k)
        {
            if (Fx<Fn)
            {
                pre=Fx+1;
                hx++;
            }
            else
            {
                pre=Fn+1;
                hn++;
            }
        }
        ans=max(ans,i-pre+1);
    }
    printf("%lld\n",ans);
}
main()
{
    Input();
    Solve();
    return 0;
}
```

。。。

然后是详细的解释：[Link](https://blog.csdn.net/LightningUZ/article/details/89161242)

---

## 作者：Durancer (赞：3)

### 前置知识

- 单调队列

### 思路

单调队列可以线性时间内解决区间内的最值问题，我们分析题目给定的数据范围，正常人想到的会是 $O(n)\ \ \text{or} \ \ O(n\log n)$。涉及到最值问题所以就考虑用单调队列解决。

因为涉及到最小值和最大值，那么就开两个单调队列，一个维护最小值，一个维护最大值。

利用双指针和单调队列中的队头比较差值来寻找符合条件的区间即可。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<vector>
#include<map>
#define int long long 
using namespace std;
const int N=3e6+9;
const int M=3e6+9;
int a[N];
int n,k,ans;
int q1[N],head1,tail1;
int q2[N],head2,tail2; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar(); }
	return f*x;
}
void DP()
{
	int l=1,r=0;
	head1=head2=1;
	while(r+1<=n)
	{
		r++;
		while(head1<=tail1 and a[q1[tail1]]<=a[r])
			tail1--;
		while(head2<=tail2 and a[q2[tail2]]>=a[r])
			tail2--;
		q1[++tail1]=r;
		q2[++tail2]=r;
		
	    while(a[q1[head1]]-a[q2[head2]]>k and l<=r)
	    {
	    	l++;
	    	while(head1<=tail1 and q1[head1]<l)
	    		head1++;
	    	while(head2<=tail2 and q2[head2]<l)
	    		head2++;
		}
		
		if(a[q1[head1]]-a[q2[head2]]<=k)
			ans=max(ans,r-l+1);
			//printf("%d-%d+1 = %d\n",r,l,r-l+1);
	}
}
signed main()
{
	k=read();
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	DP();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：盧鋅 (赞：2)

## ~~单调队列实锤~~
其实单调队列~~维护了一个什么东西呢，那就是一个数，在哪个区间产生贡献~~；（纯个人的yy）

然后我们来看这个题，他让求最大差值不超过k的最大区间。

假如大家没有做过滑动窗口，那么劝退，先做下那个题；

这题和那题的最大区别是最大值和最小值之间是相互影响的，所以我们应该考虑下让谁的队头元素出队列；

很明显的是标号越小的越难满足决策，所以让标号较小的队头出队

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>
using namespace std;
#define I inline
#define R register
#define inf 1073742823
#define FOR(i,begin,end) for(R int i=begin;i<=end;++i)
#define ROF(i,begin,end) for(R int i=begin;i>=end;--i)
#include <queue>
namespace IO{
    char buf[1<<21],*pa=buf,*pb=buf;
    char buffer[1<<21];int p1=-1;const int p2=(1<<21)-1; 
    I char gc(){return pa==pb&&(pb=(pa=buf)+fread(buf,1,1<<21,stdin),pa==pb)?EOF:*pa++;}
    template<class T>I void read(T &x){
        x=0;R int y=0;R char ch=gc();
        for(;!isdigit(ch);ch=gc())y=ch=='-';
        for(;isdigit(ch);ch=gc())x=(x<<3)+(x<<1)+(ch^48);
        (y)&&(x=-x);return;}
    I void flush(){fwrite(buffer,1,p1+1,stdout);p1=-1;return;}
    I void pc(int ch){if(p1==p2)flush();buffer[++p1]=ch;return;}
    template<class T>I void write(T x){
        static char buf[20];static int len =-1;
        if(x>=0){do buf[++len]=(x%10)^48,x/=10;while(x);}
        else{pc('-');do buf[++len]=(-(x%10))^48,x/=10;while(x);}
        while(len>=0)pc(buf[len--]);
        return;}
}
using namespace IO;
const int maxn = 3000010;
int ans=1,n,k,a[maxn],pre=0;
signed main(){
    read(k),read(n);
    FOR(i,1,n)
        read(a[i]);
    deque<int>mi;
    deque<int>mx;
    for(int i=1;i<=n;++i){
        while(!mi.empty()&&a[i]<a[mi.back()])mi.pop_back();
        mi.push_back(i);
        while(!mx.empty()&&a[i]>a[mx.back()])mx.pop_back();
        mx.push_back(i);
        while(a[mx.front()]-a[mi.front()]>k){
			int a=mi.front(),b=mx.front();
			if(a<b)pre=a,mi.pop_front();
			else pre=b,mx.pop_front(); 
		}  
        ans=max(ans,i-pre);
    }
    IO::write(ans);
    IO::flush();
    return 0;
}

```


---

## 作者：7KByte (赞：1)

你谷评测姬$O(Nlog_2N)$能过$3*10^6$的数据啦


---------

通过观察题面我们可以发现随着区间长度$len$的增大，区间最大值$-$区间最小值单调不增，所以我们可以二分区间长度$len$


问题转化为

>求所有长度为$len$的区间的最大值减最小值 /(断句) 的最小值

显然我们可以用两个单调队列分别维护区间最大值和最小值（滑动窗口）

程序的时间复杂度是$O(Nlog_2N)$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[3000005];
deque<int>mn,mx;
bool check(int l){
	while(!mn.empty())mn.pop_front();
	while(!mx.empty())mx.pop_front();
	register int i;
	for(i=1;i<l;i++){
		while(!mn.empty()&&a[mn.back()]>=a[i])mn.pop_back();
		while(!mx.empty()&&a[mx.back()]<=a[i])mx.pop_back();
		mn.push_back(i);mx.push_back(i);
	}
	for(i=l;i<=n;i++){
		while(!mn.empty()&&mn.front()+l<=i)mn.pop_front();
		while(!mx.empty()&&mx.front()+l<=i)mx.pop_front();
		while(!mn.empty()&&a[mn.back()]>=a[i])mn.pop_back();
		while(!mx.empty()&&a[mx.back()]<=a[i])mx.pop_back();
		mn.push_back(i);mx.push_back(i);
		if(a[mx.front()]-a[mn.front()]<=k)return true;
	}
	return false;
}
int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int l=1,r=n,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```
代码使用大量$STL$,实测$O2$有$5-8$倍的优化效果

---

## 作者：x122 (赞：1)

## 单调队列+二分

### 前置芝士

[单调队列](https://www.luogu.org/problem/P1886)

二分答案

本题求区间最大值与最小值的差，显然要用单调队列。但本题没有给定区间范围，因此我们二分区间大小。

当然在 $1<=n<=3000,000$ 的范围下单调队列+二分好像过不去~~ （大雾），但由于~~洛谷的数据太水~~，导致此算法可以卡过（实测总耗时 $2.53$ 秒），因此 本题解不支持 $Hack$

### 具体思路：

首先二分区间大小，用单调队列维护最大值和最小值，如果对某一段区间存在最大值减最小值$<=k$ ,则二分更小区间 $;$ 若没有区间存在合法情况，二分更大区间。

### $code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,n,a[3000001],f[3000001],g[3000001];
bool judge(long long mid) {
	memset(f,0,sizeof(f)); //注意清零
	memset(g,0,sizeof(g));
	long long left=1,right=0,head=1,tail=0;
	for(long long i=1;i<=n;i++) { //单调队列
		while(head<=tail && f[head]<=i-mid) head+=1;
		while(head<=tail && a[f[tail]]<a[i]) tail--;
		f[++tail]=i;  //维护最大值
		while(left<=right && g[left]<=i-mid) left+=1;
		while(left<=right && a[g[right]]>a[i]) right-=1;
		g[++right]=i;  //维护最小值
		if(a[f[head]]-a[g[left]]<=k && i>=mid) return true;//判断差值是否小于等于k
	}
	return false;
}
int main(){
	scanf("%lld%lld",&k,&n);
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
	long long l=0,r=n+1;
	while(l<r) {   // 二分
		long long mid=(l+r)>>1;
		if(judge(mid)==1) l=mid+1;
		else r=mid;
	}
	printf("%lld\n",l-1);
	return 0;
}
```



---

## 作者：zhengrunzhe (赞：1)

这个是个要开O2的题解，主要是提供一个思路

这里用$TwoPointers$

因为决策具有单调性

比较显然的性质:

$1.max \left \{a[l,r+1] \right \}>=max \left \{a[l,r] \right \}$

$2.min \left \{b[l,r+1] \right \}<=min \left \{b[l,r] \right \}$

$3. \text {综合1.2.可得} max \left \{a[l,r+1] \right \}-min \left \{b[l,r+1] \right \}>=max \left \{a[l,r] \right \}-min \left \{b[l,r] \right \}$

也就是$r$指针拓展差值不降

然后就可以尺取，每次$r$指针跳到不能跳为止，然后比较答案，然后$l$指针挪一格

但由于区间最大最小值我用了对顶堆，使用stl的优先队列

时间复杂度$O(nlogn)$，不开$O2$是过不去的
```cpp
#include<queue>
#include<cstdio>
using std::vector;
using std::greater;
using std::priority_queue;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const type min(const type &a,const type &b)
{
	return a<b?a:b;
}
const int N=3e6+2,inf=2e9+10;
struct heap_greater
{
	int sz;
	priority_queue<int>s,t;
	inline void pop(int x){t.push(x);--sz;}
    inline void push(int x){s.push(x);++sz;}
    inline void pre(){while(t.size()&&s.top()==t.top())s.pop(),t.pop();}
    inline int top(){return pre(),sz?s.top():0;}
}mx;
struct heap_less
{
	int sz;
	priority_queue<int,vector<int>,greater<int> >s,t;
	inline void pop(int x){t.push(x);--sz;}
    inline void push(int x){s.push(x);++sz;}
    inline void pre(){while(t.size()&&s.top()==t.top())s.pop(),t.pop();}
    inline int top(){return pre(),sz?s.top():-inf;}
}mn;
int n,a[N],k,ans;
inline const void add(int x)
{
	if (!x)return;mn.push(x);mx.push(x);
}
inline const void del(int x)
{
	mn.pop(x);mx.pop(x);
}
int main()
{
	read(k);read(n);
	for (int i=1;i<=n;i++)read(a[i]);
	int l=1,r=0;
	mn.push(inf);mx.push(0);
	while (r<=n)
	{
		while (mx.top()-mn.top()<=k&&r<=n)add(a[++r]);
		ans=max(ans,r-l);
		del(a[l++]);
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：兮水XiShui丶 (赞：1)

自己刚刚学完单调栈，就写了这道题，有些概念理解的不太好的话希望理解qwq  

这道题我选择的是用单调栈的思想来维护一个单调队列。  

首先，这道题的题意是要求你去求一个最长的最大值与最小值的差不超过$t$的一个序列的长度。所以我们根据单调栈的思想，我们可以枚举每一个位置，把这一个位置当做目前序列中的最小值，就可以分别求出$lmax[i],rmax[i]$，最后的答案就是$max(lmax[i]+rmax[i])$。  

然后我们就可以分别向左和向右求出比它这个数大且差值不超过$t$的数了。  

但是只是这么做的话，我们遇到一个问题： 
我们在进行单调栈的过程中，如果一个数位于栈底的话，那么这个数在目前的栈中一定是最早被加进来的，那么如果我们只是比较栈顶的话，我们不免会忽略掉这个数。  

要解决这个问题，其实我们只要把单调栈换成单调队列就可以了。每次判断一下队头和队尾是不是应该被换掉。   

代码丑，请见谅QAQ  

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define  int long long

using namespace std;

const int N = 3e6 + 10;

int t , n;
int num[N];

int queue[N] , head , tail;
int rmax[N] , lmax[N];

signed main ( void ) {
    ios :: sync_with_stdio ( false );
    cin.tie ( 0 );
    cin >> t >> n;
    for ( int i = 1 ; i <= n ; i++ ) 
        cin >> num[i];
    head = 1 , tail = 1;
    queue[head] = 1;
    for ( int i = 2 ; i <= n + 1 ; i++ ) {
        while ( head <= tail && ( num[queue[head]] > num[i] || num[i] - num[queue[head]] > t ) )
            rmax[queue[head++]] = i - 1;
        while ( head <= tail && ( num[queue[tail]] > num[i] || num[i] - num[queue[tail]] > t ) )
            rmax[queue[tail--]] = i - 1;
        queue[++tail] = i;
    }
    head = 1 , tail = 1;
    queue[head] = n;
    for ( int i = n ; i >= 0 ; i-- ) {
        while ( head <= tail && ( num[queue[head]] > num[i] || num[i] - num[queue[head]] > t ) )
            lmax[queue[head++]] = i + 1;
        while ( head <= tail && ( num[queue[tail]] > num[i] || num[i] - num[queue[tail]] > t ) )
            lmax[queue[tail--]] = i + 1;
        queue[++tail] = i;
    }
    for ( int i = 1 ; i <= n ; i++ ) {
        rmax[i] = rmax[i] - i;
        lmax[i] = i - lmax[i] + 1;
    }
    int ans = 0;
    for ( int i = 1 ; i <= n ; i++ ) 
        ans = max ( ans , rmax[i] + lmax[i] );
    cout << ans << endl;
    return 0;
}
```


---

## 作者：attack (赞：1)

静态区间最大最小值问题


不难想到单调队列


对于区间长度我们可以进行二分


这样我们就可以轻松的拿到80分了


    

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<deque>
using namespace std;
const int MAXN=3000010;
inline void read(int &n)
{
    char c=getchar();n=0;bool flag=0;
    while(c<'0'||c>'9')    c=='-'?flag=1,c=getchar():c=getchar();
    while(c>='0'&&c<='9')    n=n*10+c-48,c=getchar();flag==1?n=-n:n=n;
}
struct node
{
    int pos,val;
    node(){pos=val=0;}
    node(int a,int b)    {    pos=a;val=b;    }
};
int a[MAXN];
int n,k;
int check(int mid)
{
    deque<node>qmax;// 升 
    deque<node>qmin;// 降
    for(int i=1;i<=n;i++)
    {
        while(qmax.size()>0&&qmax.front().pos<=(i-mid))    qmax.pop_front();    
        while(qmin.size()>0&&qmin.front().pos<=(i-mid))    qmin.pop_front();
        while(qmax.size()>0&&a[i]>qmax.back().val)    qmax.pop_back();
        qmax.push_back(node(i,a[i]));    
        while(qmin.size()>0&&a[i]<qmin.back().val)    qmin.pop_back();
        qmin.push_back(node(i,a[i]));    
    //    printf("%d %d\n",qmax.front().val,qmin.front().val);
        if(i>=mid&&qmax.front().val-qmin.front().val<=k)    
            return 1;
    }
    return 0;
}
int main()
{
    read(k);read(n);
    for(int i=1;i<=n;i++)    read(a[i]);
    int l=1,r=n;
    int ans=0;  
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid))    ans=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d",ans);
    return 0;
}
```
仔细想一想

我们其实是用不到二分的，


只要在枚举的时候协调一下对头和队尾的元素就好

    
        

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<deque>
using namespace std;
const int MAXN=3000010;
inline void read(int &n)
{
    char c=getchar();n=0;bool flag=0;
    while(c<'0'||c>'9')    c=='-'?flag=1,c=getchar():c=getchar();
    while(c>='0'&&c<='9')    n=n*10+c-48,c=getchar();flag==1?n=-n:n=n;
}
struct node
{
    int pos,val;
    node(){pos=val=0;}
    node(int a,int b)    {    pos=a;val=b;    }
};
int a[MAXN];
int n,k;
int t=1;
int main()
{
    read(k);read(n);
    for(int i=1;i<=n;i++)    read(a[i]);
    deque<node>qmax;// 升 
    deque<node>qmin;// 降 
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        while(qmax.size()>0&&a[i]>=qmax.back().val)    qmax.pop_back();
        qmax.push_back(node(i,a[i]));    
        while(qmin.size()>0&&a[i]<=qmin.back().val)    qmin.pop_back();
        qmin.push_back(node(i,a[i]));    
        while(qmax.front().val-qmin.front().val>k)
        {
            if(qmax.front().pos>qmin.front().pos)    t=qmin.front().pos+1,qmin.pop_front();
            else t=qmax.front().pos+1,qmax.pop_front();
        }
        ans=max(ans,i-t+1);
    }
    printf("%d",ans);
    return 0;
}
```
PS:此题有点小卡常，stl在主站是过不了的，只有在大牛分站上才能过

---

## 作者：Fan_Tuan (赞：0)

## 题意
给定 $k$，和一个长度为 $n$ 的序列，求最大值与最小值之差不大于 $k$ 的最长连续子序列。
## 思路
考虑两个单调队列，一个维护最大值，一个维护最小值。

如果当前维护的区间最大值与最小值之差合法，那么更新 $ans$ 的最大值。

否则每次将两个单调队列中队首序号较小的移出队列，**这样可以保证当前维护的区间左端点是最优的**，直到维护的区间合法。最后输出 $ans$。

## 代码
```cpp
//dbq
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<iostream>
#include<algorithm>
// #define int long long
using namespace std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 3e6 + 10;
int k, n, qm[maxn], qn[maxn], frontm = 1, frontn = 1, backm, backn, a[maxn], qmid[maxn], qnid[maxn];  // qm, qn 为维护区间最值的单调队列， qmid, qnid 维护的为区间最值的坐标。

signed main() {
	k = read(), n = read();
	int ans = 0, id = 1;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) {
		while (frontn && frontn <= backn && a[i] < qn[backn]) --backn;
		while (frontm && frontm <= backm && a[i] > qm[backm]) --backm;
		qn[++backn] = a[i], qm[++backm] = a[i], qnid[backn] = i, qmid[backm] = i;
		while (qm[frontm] - qn[frontn] > k) {
			if (qnid[frontn] < qmid[frontm]) id = qnid[frontn] + 1, ++frontn;
			else id = qmid[frontm] + 1, ++frontm;
		}
		ans = max(ans, i - id + 1);
	}
	print(ans);
	return 0;
}
```

---

## 作者：HoshiuZ (赞：0)

$n\le 3\times 10^6$ ，嗯，应该是 $O(n)$ 的算法。

考虑维护一个队列和两个单调队列。队列维护的是序列中连续的子序列，两个单调队列一个维护单调递增，一个维护单调递减。这样，选取的子序列中的最大值与最小值就是两个单调队列的队头元素。

据此维护即可。

长度即为队列的队尾减队头加一。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define N 3000010

using namespace std;

inline ll read() {
	ll w=1,x=0;
	char ch=0;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return w*x;
}

int n,que_max[N],que_min[N],que_id[N],ans=0;
ll k,a[N];

int main(){
    k=read(),n=read();
    for(int i=1;i<=n;i++) a[i]=read();

    int hmax=1,tmax=0,hmin=1,tmin=0,hid=1,tid=0;
    for(int i=1;i<=n;i++) {
        while(hid<=tid&&max(a[que_max[hmax]],a[i])-min(a[que_min[hmin]],a[i])>k) {
            if(que_id[hid]==que_max[hmax]) hmax++;
            if(que_id[hid]==que_min[hmin]) hmin++;
            hid++;
        }
        que_id[++tid]=i;
        while(hmax<=tmax&&a[i]>a[que_max[tmax]]) tmax--;
        que_max[++tmax]=i;
        while(hmin<=tmin&&a[i]<a[que_min[tmin]]) tmin--;
        que_min[++tmin]=i;
        ans=max(ans,tid-hid+1);
    }

    printf("%d\n",ans);

    return 0;
}
```

---

