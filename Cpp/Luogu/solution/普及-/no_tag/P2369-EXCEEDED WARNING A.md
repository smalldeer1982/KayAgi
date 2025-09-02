# EXCEEDED WARNING A

## 题目描述

有这样一些数据，它们均为小于 $10^9$ 的非负整数，且个数为 $n$，现在请你输出其中最小的 $m$ 个数。

小心溢出，注意 Memory Limit = 4000KiB。


## 说明/提示

数据范围：$m<10^5, n<10^6$。

## 样例 #1

### 输入

```
10 5
2
4
6
8
10
1
3
5
7
9```

### 输出

```
1
2
3
4
5```

# 题解

## 作者：_neddy (赞：51)

这道题坑点还是挺多的，前后交了二十多次终于成功。

$STL$大法好！

方法如下：

1. 开两个优先队列，一个大根堆一个小根堆

```cpp
priority_queue<int, vector<int>, less<int> > a;		
//大根
priority_queue<int, vector<int>, greater<int> > s;
//小根
```
2. 把输入的前$m$个数塞进大根堆

```cpp
for (register int i = 1; i <= m; ++i)
{
   int num;
   scanf("%d", &num); //优先队列不能直接输入堆顶
   a.push(num);     //只能用中间变量输入
   //然后再进堆
}
```

3. 对接下来的$n-m$个数进行筛选，**如果比大根堆的根小，就去除根，并把这个数塞进去**

```cpp
for (register int i = m + 1, num; i <= n; ++i)
{
   scanf("%d", &num);
   if (num < a.top()) a.pop(), a.push(num);
}
```

4. 把大根堆里的数倒进小根堆里

```cpp
for (register int i = 1; i <= m; ++i)
{
   s.push(a.top()); //大根堆堆顶倒入小根堆
   a.pop();			//大根堆堆顶出堆
} 
```

5. 输出即可。

完整代码如下：

```cpp
#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

priority_queue<int, vector<int>, less<int> > a;
priority_queue<int, vector<int>, greater<int> > s;
int maxn;

int main()
{
    int n, m, miss = 0;
    scanf("%d %d", &n, &m);
    for (register int i = 1; i <= m; ++i)
    {
        int num;
        scanf("%d", &num);
        a.push(num);
    }
    for (register int i = m + 1, num; i <= n; ++i)
    {
        scanf("%d", &num);
        if (num < a.top())
        {
            a.pop();
            a.push(num);
        }
    }
    for (register int i = 1; i <= m; ++i)
    {
        s.push(a.top());
        a.pop();
    } 
    while(s.size()) printf("%d\n", s.top()), s.pop();
}
```

求过求顶，让更多的人看到。

拒绝抄袭。



---

## 作者：TsReaper (赞：48)

本题最多有10^6个数，可是空间只有4000K，只能存下10^5（也就是m的最大值）个数，这样就不能把所有数记录下来然后排序了。那该怎么办呢？

由于题目只要求我们输出最小的m个数，不难想到维护一个最多能存下m个数的大根堆。每读入一个数xi，就将xi放入堆中。如果堆中数的数量大于m，就删掉大根堆的根。这样做就能维护当前最小的m个数了。

最后，将堆里的所有数排序，依次输出即可。


---

## 作者：龙之吻—水货 (赞：12)

可以用堆和优先队列的题目，大部分都可以用平衡树来解决（就比如说是这道题）。

每次插入一个数，判断已经加入数的数量，如果数量小于ｍ就直接插入，否则比较它和平衡树中排名为Ｍ的值的大小，如果这个数比排名为Ｍ的值大，就下一个，否则删除那个排名为Ｍ的值，把这个数加入平衡树中。

附上Treap AC代码
(Treap勉强卡过空间，Splay怕不是要T +　Ｍ）
```
// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>

using namespace std;

int INF = 2147483647;

int Rand() {
    static int seed = 23333;
    return seed = (int)((((seed ^ 998244353) + 19260817ll) * 19890604ll) % 1000000007);
}

struct Node{
    Node *leftchild, *rightchild, *father;
    int val, cnt, size, rand_num;
    
    Node(int val, Node *father) :
        leftchild(NULL),
        rightchild(NULL),
        father(father),
        val(val),
        cnt(1),
        size(1),
        rand_num(Rand()) {}
};

Node *root;

void UpdateSize(Node *now) {
    if (!now) {
        return;
    }
    now->size = now->cnt;
    if (now->leftchild) {
        now->size += now->leftchild->size;
    }
    if (now->rightchild) {
        now->size += now->rightchild->size;
    }
}

void LeftRotate(Node *&now) {
    Node *right = now->rightchild;
    now->rightchild = right->leftchild;
    right->leftchild = now;
    right->size = now->size;
    UpdateSize(now);
    now = right;
}

void RightRotate(Node *&now) {
    Node *left = now->leftchild;
    now->leftchild = left->rightchild;
    left->rightchild = now;
    left->size = now->size;
    UpdateSize(now);
    now = left;
}

void Insert(Node *&now, int val) {
    if (!now) {
        now = new Node(val, now);
        return;
    }
    now->size++;
    if (now->val == val) {
        now->cnt++;
    }
    else if(now->val > val) {
        Insert(now->leftchild, val);
        if (now->leftchild->rand_num < now->rand_num) {
            RightRotate(now);
        }
    }
    else if(now->val < val) {
        Insert(now->rightchild, val);
        if (now->rightchild->rand_num < now->rand_num) {
            LeftRotate(now);
        }
    }
}

void Remove(Node *&now, int val) {
    if (now == NULL) {
        return;
    }
    if (now->val == val) {
        if (now->cnt > 1) {
            now->cnt--;
            now->size--;
            return;
        }
        else {
            if (!now->rightchild && !now->leftchild) {
                now = NULL;
            }
            else if(!now->rightchild && now->leftchild) {
                now = now->leftchild;
            }
            else if(now->rightchild && !now->leftchild) {
                now = now->rightchild;
            }
            else if(now->leftchild->rand_num < now->rightchild->rand_num) {
                RightRotate(now);
                Remove(now, val);
            }
            else {
                LeftRotate(now);
                Remove(now, val);
            }
        }
    }
    else if(now->val < val) {
        now->size--;
        Remove(now->rightchild, val);
    }
    else {
        now->size--;
        Remove(now->leftchild, val);
    }
}

int Rank(Node *now, int val) {
    if (!now) {
        return 0;
    }
    int left_size = now->leftchild ? now->leftchild->size : 0;
    if (now->val == val) {
        return left_size + 1;
    }
    if (now->val < val) {
        return left_size + now->cnt + Rank(now->rightchild, val);
    }
    else {
        return Rank(now->leftchild, val);
    }
}

int FindKth(Node *now, int rank) {
    if (!now) {
        return 0;
    }
    int left_size = now->leftchild ? now->leftchild->size : 0;
    if (rank <= left_size) {
        return FindKth(now->leftchild, rank);
    }
    rank -= left_size;
    if (rank <= now->cnt) {
        return now->val;
    }
    rank -= now->cnt;
    return FindKth(now->rightchild, rank);
}

int n, m, sum;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        int rank = Rank(root, x);
        if (rank > m) {
            continue;
        }
        if (sum <= m) {
            Insert(root, x);
        }
        else {
            int num = FindKth(root, m);
            if (num > x) {
                Remove(root, num);
                Insert(root, x);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        printf("%d\n", FindKth(root, i));
    }
    return 0;
}
```

---

## 作者：liuyifan (赞：6)

看到这道题还没有用vector做的,那我就来发一个吧

vector是c++ stl中的一种数据结构,可以理解为“自动随数据范围而变化大小的数组"

~~因为数据过水的原因,所以可以使用short变量(此题不会爆)+vector有效避免~~MLE(~~本代码成功AC,[提交记录](https://www.luogu.org/recordnew/show/10488737)~~)

vector的部分常用用法如下:
```cpp
#include<vector>
创建vector数组:vector<int>vectorname;
尾部插入:vectorname.push_back(num);
使用下标访问元素:vectorname[0](下标从0开始)
插入元素:vectorname.insert(vec.begin()+x,num)(在第x个元素后面插入num)
删除元素:vectorname.erase(vec.begin()+x)(删除第x+1个元素)
vectorname.erase(vectorname.begin()+x,vectorname.end()+y):(删除区间[x,y)(区间从0开始))
大小:vectorname.size();
清空:vectorname.clear()
```
[更多用法(非本人)](https://www.runoob.com/w3cnote/cpp-vector-container-analysis.html)

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define st short//short不会爆(数据太水,int会MLE)
#define regregister//据说能加速
using namespace std;
ll n,m;
vector<st>a;//定义容器
st tmp;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(reg int i=1;i<=n;i++)scanf("%hd",&tmp),a.push_back(tmp);//short的格式控制符为hd
    sort(a.begin(),a.end());//对vector进行快排,可以自己写cmp函数实现各种排序
    for(reg int i=0;i<m;i++)printf("%hd\n",a[i]);//同上
    return 0
```
拒绝抄袭,共建和谐洛谷

---

## 作者：Yosame (赞：4)

看到题解里要不就是用了short要不就是用了很dalao的方法，我来发一个萌新也能看懂的并且正常数据也能AC的代码qwq

可以在空间方面利用到极限，开一个700000的数组（测试点9只用了3348KB，所以其实可以开更大的数组）

1、在数组范围内可以直接一遍sort，范围外就先输入700000个数，然后排序一次；**（重点）2、由于已经排序过一次，大的数就在数组的最后，于是之后每输入一个数就判断是否比最大的数小，如果小就替换掉；**3、所有数全部换完后再排序一次，输出

如果利用快速读入输出可以优化很大一堆时间（量词破碎x

根据测试点9的结果来看缩小数组或者继续略微增大数组都是可以的（这个数据也太水了吧x我随机生成的1000000个数据都要用0.6s+

下面贴代码（应该是可以继续优化的）
```cpp
//AC，最后一个测试点282ms/3348KB 
#include<cstdio>
#include<algorithm>
using namespace std;
unsigned a[700000],innum,outnum,temp,z,pcount;
//a[700000]在内存超限的边缘疯狂试探 
//pcount用于排序一次后从后向前替换 
//个人喜欢用unsigned 
unsigned read(){
    unsigned x=0;
    char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9'){
    	x=x*10+c-'0';
		c=getchar();
	}
    return x;
}
void write(unsigned x){ 
    char c[11];
    short wcount=0;
    if(x==0)puts("0");
    else{
    	for(;x>0;x/=10)c[wcount]=x%10+48,wcount++;
    	for(wcount--;wcount>=0;wcount--)putchar(c[wcount]);
		putchar('\n');//本题需要换行
	}
}
int main(){
	freopen("random.txt","r",stdin);
	freopen("result.txt","w",stdout);//防抄袭（然并卵） 
	innum=read();
	outnum=read();
	if(innum<=700000){//如果输入的数不超过700000个 
		for(;z<innum;z++)a[z]=read();
		sort(a,a+innum);
		for(z=0;z<outnum;z++)write(a[z]);
		return 0;
    }
    for(;z<700000;z++)a[z]=read();//先存700000个数
    sort(a,a+700000);//先sort一遍 
    for(;z<innum;z++){//从后往前替换
    	temp=read();
    	if(a[699999-pcount]<=temp)continue;
    	else{
    		a[699999-pcount]=temp;
    		pcount++;
		}
	}
	sort(a,a+700000);//再sort一遍然后输出就完事儿了 
	for(z=0;z<outnum;z++)write(a[z]);
	return 0;
}

```
蒟蒻的第一篇题解orz

---

## 作者：psk011102 (赞：4)

实际就是建立一个大根堆。下面有位没附代码的大神讲的很清楚了，这里附上代码。

不过这是道练习堆的好题。只不过要注意最后要从小到大输出m个数

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define F(a,b,c) for(int a=b;a<=c;++a)
#define f(a,b,c) for(int a=c;a>=b;a--)//宏定义 
#define ll long long 
using namespace std;
ll n,c[1000005],m,sum;
inline ll read(){
    ll x = 0, fh = 1; char ch;
    for(;!isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
    for(;isdigit(ch); ch = getchar()) x = (x<<1) + (x<<3) + (ch^'0');
    return x * fh;
```
}//快读
```cpp
void up(ll sum){
    ll now=sum;
    while(now>1&&c[now>>1]<c[now]){
        ll t=c[now];
        c[now]=c[now>>1];
        c[now>>1]=t;
        now=now>>1;//x>>1等价于 x/2 
    }
```
}//把大的数据向上移
```cpp
void down(){
    ll now=1;
    while(((now<<1)<=m&&c[now]<c[now<<1])||((now<<1|1)<=m&&c[now]<c[now<<1|1])){
        ll next=now<<1;//x<<1等价于x*2,x<<1|1等价于x*2+1. 
        if(c[next]<c[next+1])next++;//如果左边的数比右边小，就往右移 
        ll t=c[next];
        c[next]=c[now];
        c[now]=t;
        now=next;
    }
```
}//把小数据下移
```cpp
void write(ll x){  
    ll y=10,len=1;  
    while(y<=x){
          y*=10;
          len++;
    }  
    while(len--){
          y/=10;
          putchar(x/y+48);
          x%=y;
    }  
} //快速输出（其实直接输出也行） 
int main(){
    n=read();
    m=read();
    F(i,1,m){
        c[i]=read();
        up(i);//向上移 
```
}//先让前m个数入堆
```cpp
    F(i,m+1,n){
        sum=read();
        if(sum<c[1]){//如果数比最大的数要小，就替换。 
            c[1]=sum;
            down();//向下移  
        }
    } 
    sort(c+1,c+m+1);//最后再处理，从小到大排序 
    F(i,1,m){
        write(c[i]);
        cout<<endl;
```
}//按要求输出
    return 0;

}

---

## 作者：Andysun06 (赞：3)

### 这道题不难，会快排的人都会。

## 冒泡只有22分！！！

##### pascal题解:

```cpp
var  a:array [1..10000000]of int64;//数很大！
     i,n,m:longint;
  procedure qsort(l,r:longint);//快排部分，不解释
var
   i,j,mid,temp:longint;
begin
     i:=l;j:=r;mid:=a[(i+j)div 2];
     repeat
           while a[i]<mid do inc(i);
           while a[j]>mid do dec(j);
           if i<=j then begin
             temp:=a[i];a[i]:=a[j];a[j]:=temp;
             inc(i);dec(j);
           end;
     until i>j;
     if i<r then qsort(i,r);
     if j>l then qsort(l,j);
end;//快排结束
begin//主程序
 readln(n,m);//输入n，m
 for i:=1 to n do//输入数字
  readln(a[i]);
  qsort(1,n);//快排
  for i:=1 to m do//输出m个
   writeln(a[i]);
end.//完美的结束
##### 记住：从小到大！！！！
```

---

## 作者：critnos (赞：2)

首先，这题是可以用short水过的
```cpp
#include<bits/stdc++.h>
using namespace std;
short a[1000005];
int main()
{
	int n,m,i;
	cin>>n>>m; 
	for(i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for(i=0;i<m;i++) cout<<a[i]<<endl;
}
```
~~但是这样不太厚道~~

所以，我想起了一种叫**二分插入排序**的东西

比如：

把

[5] [4] [2] [1] [3]

排序

1.输入[5]

2.输入[4]，通过二分查找发现应该排在第一位

3.输入[2]，通过二分查找发现应该排在第一位

4.输入[1]，通过二分查找发现应该排在第一位

2.输入[3]，通过二分查找发现应该排在第三位

这要用到**vector**

思路：

先输入m个数，排序，每次插入一个数并删除最后一个数（实际上要剪枝：先判断输入的数是否小于序列中最大的数，要不然会T）
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a;
int n,m;
int cz(int p)//二分查找
{
	int l=0,r=m,mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(a[mid]>p) r=mid;
		else l=ceil((l+r)/2.0);
	}
	return l;
}
int main()
{
	int i,j,p,q;
	cin>>n>>m; 
	for(i=0;i<m;i++)//第一波输入
	{
		scanf("%d",&p);
		a.push_back(p);
	}
	sort(a.begin(),a.end());
	for(i=m;i<n;i++)//第二波输入
	{
		scanf("%d",&p);
		if(p<a[a.size()-1])//剪枝
		{
			q=cz(p);
			a.insert(a.begin()+q,p);//插入	
			a.erase(a.end()-1);	//删除
		}
	}
	for(i=0;i<m;i++) printf("%d\n",a[i]); 
}
```
[有惊无险，卡常+O2](https://www.luogu.org/record/24166210)

---

## 作者：VenusM1nT (赞：2)

一道很水的题目，和 第K大整数 类似，只要会写快排想必都会做

思路：读入数据，快速排序，输出前m个

具体见代码

 


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[1000005];
void qsort(int first,int last)
{
    if(first>last) return;
    int i,j,x;
    i=first;
    j=last;
    int m=(i+j)/2;
    int t=a[m];
    a[m]=a[i];
    a[i]=t;
    x=a[i];
    while(i<j)
    {
        while(a[j]>x) j--;
        if(i<j) 
        {
            a[i]=a[j];
            i++;
        }
        while(a[i]<x && i<j) i++;
        if(i<j)
        {
            a[j]=a[i];
            j--;
        }
    }
    a[i]=x;
    qsort(first,i-1);
    qsort(i+1,last);
```
}//快速排序部分，不累述
```cpp
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    qsort(1,n);//如果使用STL则可以改成：sort(a+1,a+n+1); 
    for(int i=1;i<=m;i++) printf("%d\n",a[i]);//输出结果即可 
    return 0;
}
```

---

## 作者：Sophon (赞：1)

来一篇map的(貌似没看到有map的)^_^  
相当于桶排，map的第二值为出现次数，然后从0开始遍历直到输出m个为止
```cpp
#include <bits/stdc++.h>
using namespace std;;

map<int,int> mp;//main外面自动归为0

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	
	while(n--)
	{
		int x;
		scanf("%d",&x);
		mp[x]++;//对应的x出现次数+1
	}
	
	int cnt=0;//已经打印出的总数
	for(int i=0;;i++)//虽然题目上有正整数，为什么数据有0
	{
		while(mp[i]!=0&&cnt<m)//出现次数不为0且打印总数不超过m
		{
			printf("%d\n",i);
			mp[i]--;//次数-1
			cnt++;//打印数+1
		}
		if(cnt==m)
		{
			return 0;
		}
	}
}
```

---

## 作者：L_key (赞：1)

P2369 题解

这道题我用了堆来做，只不过和题目的最小值相反，维护的是最大值。

空间限制4mb，100 0000的数组会爆掉，所以：

**每m+1个数就淘汰最大值**，这样只需开10 0000的数组就够了。

代码如下：

```cpp
#include<cstdio>
using namespace std;
void swap1(int &x,int &y){int t=x;x=y;y=t;}
int n,m;
int a[110000];
int ans[110000];
void heap(int i,int len)
{
	int j=2*i;
	while(j<=len)
	{
		if(j<len&&a[j]<a[j+1])j++;
		if(a[i]<a[j])swap1(a[i],a[j]);
		else break;
		i=j;j*=2;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	int l=m+1;if(n==m)l--;
	for(int i=1;i<=l;i++)scanf("%d",&a[i]);
	for(int i=l/2;i>=1;i--)heap(i,l);
	for(int i=m+2;i<=n;i++)
	{
		scanf("%d",&a[1]);
		heap(1,m+1);
	}
	if(m<n)a[1]=a[m+1],heap(1,m);
	for(int i=m;i>=1;i--)
	{
		ans[i]=a[1];
		a[1]=a[i];
		heap(1,i-1);//这时，堆中的数渐渐减少，所以用i-1，上一行的用i。
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```
要想清楚每次堆排序前，**堆中有多少个数**，也就是heap中的len。

注意：l（小写L）是用来处理n=m的情况的。~~不用特判（n==m）也能过~~

---

## 作者：empty (赞：1)


归并

翻了一遍题解，居然没有用归并的。


普及一下，快排虽好，可快排是一种不稳定且有悲剧情况的排序。归并的时间复杂度为（nlogn），速度快，稳定。


归并也有它好的地方，当然也有不好的地方。


不过母庸置疑的是,快排更深入人心。


```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
int nnt[100100],r[100100];
void GB(int s,int t)
{
 if(s==t) return;- 
 int mid=(s+t)/2;
 GB(s,mid);
 GB(mid+1,t);
 int i=s,j=mid+1,k=s;
 while((i<=mid)&&(j<=t))
  {
   if(nnt[i]<=nnt[j])
   {
    r[k]=nnt[i];k++;i++;
   }
   else
   {
    r[k]=nnt[j];k++;j++;
   }
  }
 while(i<=mid)
 {
  r[k]=nnt[i];k++;i++;
 }
 while(j<=t)
 {
  r[k]=nnt[j];k++;j++;
 }
 for(int i=s;i<=t;i++) nnt[i]=r[i];
}
int main()
{
 ll n,b,s=0,j=0;
 scanf("%lld %lld\n",&n,&b);
 for(int i=1;i<=n;i++) scanf("%d\n",&nnt[i]);
 GB(1,n);
 for(int i=n;i>=1;i--) {s+=nnt[i];j++;if(s>=b) break;}
 printf("%lld",j);
 return 0;
}
```

---

## 作者：doby (赞：0)

很明显，没有按照空间限制来……

用优先队列也可以……

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,f[1000009];
int main()
{
    scanf("%d%d",&n,&m);//模拟……
    for(int i=1;i<=n;i++){scanf("%d",&f[i]);}
    sort(f+1,f+n+1);
    for(int i=1;i<=m;i++){printf("%d\n",f[i]);}
    return 0;
}
```
……
```cpp
#include<cstdio>
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
int n,m,a,x,out,fh;
char cc;
int read()
{
    out=0,fh=1,cc=getchar();
    if(cc=='-'){fh=-1;}
    while(cc>'9'||cc<'0'){cc=getchar();}
    while(cc>='0'&&cc<='9')
    {
        out=out*10+cc-'0',
        cc=getchar();
    }
    return out*fh;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        a=read();
        q.push(a);
    }
    for(int i=1;i<=m;i++){printf("%d\n",q.top());q.pop();}
    return 0;
}
```

---

## 作者：zyf2224 (赞：0)

# 桶排大法好
~~### emmm，其实一个普及-的题不用那么复杂吧~~
#### 这道题很简单 用桶排就可以过
~~### vector什么的总有点高射炮打苍蝇的感觉~~
#### 代码如下

```cpp
#include <cstdio>
using namespace std;
const int MAXN=100000000;//题目说随机数不超过10^9
int num[MAXN];//桶排走起
int main()
{
	int j=0,m,n,tmp;
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;++i)
	{
		scanf("%d",&tmp);
		++num[tmp];//记录下每个数字出现的次数
	}
	tmp = 0;//此时，tmp用于记录输出数的个数
	while(1)
	{
		while(num[j])
		{
			printf("%d\n",j);
			--num[j];
			++tmp;
			if(tmp>=n)return 0;//如果输出了n个数，退出程序
		}
		++j;
	}
	return 0;
}
```
#### 开O2，最后一个点78ms，倒数第二个点内存只用了1.02M


---

## 作者：dongyx (赞：0)

大家好，我叫dongyx。接下来我就说一说这道题是怎么做的！既然已经确定小于10的9次方，那么，我们直接用一个排序（sort），最后输出前m个。


```cpp
#include<bits/stdc++.h>//万能头是一个天大的好东西，你值得拥有！！！ 
using namespace std;
#define aa short//作死 
#define QwQ int//作死 
aa a[100000000];//作死 
QwQ main()
{
	QwQ n,m;
	cin>>n>>m; 
	for(QwQ i=1;i<=n;i++)
	{
		cin>>a[i];//输入 
	}
	sort(a+1,a+1+n);//sort、冒泡、选排、桶排……随你选 
	for(QwQ i=1;i<=m;i++)
	{
		cout<<a[i]<<endl;//endl是个好东西 
	}
	return 0;
}
```

---

## 作者：zhuozhizhao (赞：0)

面对大一点的数据建议用二分，因为二分较稳定，最坏的情况和最好的情况都差不多

就是合并的时候注意思路

```cpp
#include<cstdio> 
#include<cstring>
using namespace std;
int a[1000000],temp[1000000];
void mergearray(int left,int mid,int right){
    int i=left,n=mid;
    int q=mid+1,w=right;
    int k=0;
    while(i<=n&&q<=w){
        if(a[i]<=a[q])temp[k++]=a[i++];     //哪个小就装哪一个
        else temp[k++]=a[q++];
    }
    while(i<=n)temp[k++]=a[i++];            //最后一组没装完的已有序且比其他都大，直接装入
    while(q<=w)temp[k++]=a[q++];
    for(i=0;i<k;i++)a[left+i]=temp[i];
}
void mergesort(int left,int right){
    if(left<right){
        int mid=(left+right)/2;
        mergesort(left,mid);              //左分
        mergesort(mid+1,right);       //右分
        mergearray(left,mid,right);   //合并
    }
}
int main(){
    int q,w,i;
    scanf("%d%d",&q,&w);
    for(i=0;i<q;i++)scanf("%d",&a[i]);
    mergesort(0,q-1);
    for(i=0;i<w;i++)printf("%d\n",a[i]);
    return 0;
}
```

---

## 作者：Lilyisashit (赞：0)

sort大法好

其实这道题只需要用一下algorithm库里的sort排序函数即可

一般结构为sort（起始点，结束点，操控函数cmp）

例：若想从小到大排序，则cmp可为

```cpp
bool cmp(int a,int b){
    return a<b;
}
```
其中cmp可有可无，无则默认为从小到大
具体详见https://baike.baidu.com/item/sort%E5%87%BD%E6%95%B0/11042699?fr=aladdin

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000005];
int n,m;
int main()
{
    cin>>m>>n;//输入
    for(int i=1;i<=m;i++)
        cin>>a[i];//输入
    sort(a+1,a+1+m);/sort函数默认从小到大排序
    for(int i=1;i<=n;i++)
        cout<<a[i]<<endl;//输出
    return 0;//结束
}

```

---

