# Parking Lot

## 题目描述

Nowadays it is becoming increasingly difficult to park a car in cities successfully. Let's imagine a segment of a street as long as $ L $ meters along which a parking lot is located. Drivers should park their cars strictly parallel to the pavement on the right side of the street (remember that in the country the authors of the tasks come from the driving is right side!). Every driver when parking wants to leave for themselves some extra space to move their car freely, that's why a driver is looking for a place where the distance between his car and the one behind his will be no less than $ b $ meters and the distance between his car and the one in front of his will be no less than $ f $ meters (if there's no car behind then the car can be parked at the parking lot segment edge; the same is true for the case when there're no cars parked in front of the car). Let's introduce an axis of coordinates along the pavement. Let the parking lot begin at point 0 and end at point $ L $ . The drivers drive in the direction of the coordinates' increasing and look for the earliest place (with the smallest possible coordinate) where they can park the car. In case there's no such place, the driver drives on searching for his perfect peaceful haven. Sometimes some cars leave the street and free some space for parking. Considering that there never are two moving cars on a street at a time write a program that can use the data on the drivers, entering the street hoping to park there and the drivers leaving it, to model the process and determine a parking lot space for each car.

## 样例 #1

### 输入

```
30 1 2
6
1 5
1 4
1 5
2 2
1 5
1 4
```

### 输出

```
0
6
11
17
23
```

## 样例 #2

### 输入

```
30 1 1
6
1 5
1 4
1 5
2 2
1 5
1 4
```

### 输出

```
0
6
11
17
6
```

## 样例 #3

### 输入

```
10 1 1
1
1 12
```

### 输出

```
-1
```

# 题解

## 作者：wz20201136 (赞：1)

~~评级和评分都恶意啊~~，感觉也就 1400/黄题，不用数据结构，暴力即可。
### 题解
模拟。

$book_i$ 表示第 $i$ 个位置的状态，记录每辆车的起点和终点，停车的时候暴力枚举停车位置的终点 $r+f$，检查时维护上一个被占用的位置。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int L,n,x,u,b,f,l[105],r[105]/*第i次停车的起点终点*/,flag[105]/*第i次是否顺利停车*/;
bool book[100005];
int main()
{
	cin>>L>>b>>f>>n;
	for(int cnt=1;cnt<=n;cnt++)
	{
		cin>>u>>x;
		if(u==1)//停车
		{
			int ma=-1;//上一个被占用的位置
			for(int i=0;i<=L+f-1/*枚举r+f*/;i++)
			{
				if(book[i])
				{
					ma=i;
					continue;
				}
				if(ma==-1&&i>=f+x-1)//特判第一辆车
				{
					l[cnt]=0,r[cnt]=x-1;
					flag[cnt]=1;
					for(int j=l[cnt];j<=r[cnt];j++) book[j]=1;
					break;
				}
				if(i-ma>=b+f+x)
				{
					l[cnt]=ma+b+1,r[cnt]=ma+b+x;
					flag[cnt]=1;
					for(int j=l[cnt];j<=r[cnt];j++) book[j]=1;
					break;
				}
			}
			if(!flag[cnt]) puts("-1");
			else cout<<l[cnt]<<endl;
		}
		else//出车
		{
			if(!flag[x]) continue;
			for(int i=l[x];i<=r[x];i++) book[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：Mint_Flipped (赞：1)

没有用线段树，就是开个map模拟一下 ~~我太菜了，做了一下午，wa了一下午~~

map<int,int> m, 前者代表车子从...开始停，后者代表...从哪里结束。

我们只要去游历每两辆车，看看当中能否停下一辆车，我们要初始化下map，

最多从0开始停，车子最多停到n，那么假设有两辆车，从-b开始停，车长0，

间隔0，那么下一辆车可以从0开始停...... 最后用map容器自带的函数erase删

去开走的车的数据即可。

至于游历，设置两个迭代器，相差一，游历即可（代表前后两辆车）。

代码如下：

```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=2e5+5;
const int mod=1e9+7;
const double eps=1e-9;
map <int,int> m;
int m1[105];
int main()
{
    int n,b,f,t;
    cin>>n>>b>>f>>t;
    fo2(k,t){
        int o,p;
        scanf("%d%d",&o,&p);
         m[-b]=-b;m[n+f]=n+f;
        if(o==1){
            m1[k]=-1;
            for(auto l=m.begin(),r=++m.begin();r!=m.end();++l,++r) {
                if(fir(r)-sec(l)>=b+p+f) {
                    m1[k]=sec(l)+b;
                    m[m1[k]]=m1[k]+p;
                    break;
                }
            }
        printf("%d\n",m1[k]);
        }
        else
        m.erase(m1[p]);
    }
    return 0;
}
```


---

## 作者：Scean_Tong (赞：0)

本题解主要介绍二分答案+贪心算法，想详尽了解也可以到博客中查看。

首先，给定的题目不提供类似于的图示，需要自己动手画来分析题意。

为了方便，我们建立一个二元组 $<x,y>$ 表示二维坐标系上的一个点，$x$ 表示停车位置，$y$ 表示索引值。可以发现，第一个样例输入可以转化为：

$$I=\{<0,1>,<6,2>,<11,3>,<17,4>,<23,5>,<30,6>\}$$

这六个点，是所有可停车位置的集合。

对于输入指令，根据定义，我们可以暂时只处理第二个整数，剩下的可以套用题目中给的公式算出。因此第一个指令等价于：停车位置为 $0$ 的车，输入“停车”操作，在 $1$ 时刻。

综上，我们需要维护两个主要的信息：

可停车的位置集合 $I$，即所有可以停车的安全距离范围；

每一个停进去的车的靠左边的位置，或者取反后，靠右边的位置，以此来快速协助判断可用的停车位置。

**接下来就是贪心算法的重头戏了！**

首先，我们不难发现，当现在停进来的车数量为奇数时，我们应该将其停靠在集合中的最中间位置，当然，为了防止误差所带来的问题，我们可以求得中位数作为标准。而当需要停进来的车数量为偶数时，我们应该让最靠左（或者最靠右）的车停靠在中位数左侧（右侧），而那辆车之后的车停靠在中位数右侧（左侧）。如果没有车取反靠右边的位置，则一律遵守前述规则。

在得到类似于样例输入的数据之后，我们将停车指令操作一条条处理，并针对操作类型进行分别处理：

对于停车操作，需要寻找到一个足够大的空区，使当前车能够完全停进去。因此，我们可以在 $I$ 集合中二分寻找相应的位置进行停车。

对于开车操作，我们需要维护每一个车停在哪一个位置，以便于计算可用停车位数量。并且对于当前车右侧的第一个车辆，如果它停在了集合中标准的位置，我们需要对此进行调整。


---

## 作者：Last_kiss_Snow_Dog6 (赞：0)

这里用线段树维护区间最多能停多长的车（包括前距和后距）。找其实点时，先判断能否放在起点，此时它要放的长度只需 $ lth $，如果可以，就找到了。否则要放的长度需要 $ lth+b+f $（当放在末尾时，其实不需要 $ +f $，但为了方便，我们可以将区间延长 $ b+f $，然后对求出的起始点判断是否可行即可），如果求出结果可行，就以该起点到车的末尾成段更新，否则输出 $ -1 $。

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <string.h>
#include <queue>
#define msc(X) memset(X,-1,sizeof(X))
#define ms(X) memset(X,0,sizeof(X))
typedef long long LL;
using namespace std;
const int MAXN=1e5+1050;
#define lson tn<<1,l,mid
#define rson tn<<1|1,mid+1,r
struct _Tree
{
    int len,lmax,rmax,amax,lazy;
}tree[MAXN<<2];
void PushUp(int tn)
{
    tree[tn].lmax=(tree[tn<<1].lmax==tree[tn<<1].len?
        (tree[tn<<1].len+tree[tn<<1|1].lmax):tree[tn<<1].lmax);
    tree[tn].rmax=(tree[tn<<1|1].rmax==tree[tn<<1|1].len?
        (tree[tn<<1].rmax+tree[tn<<1|1].len):tree[tn<<1|1].rmax);
    tree[tn].amax=max(tree[tn<<1].amax,tree[tn<<1|1].amax);
    tree[tn].amax=max(tree[tn].amax,tree[tn<<1].rmax+tree[tn<<1|1].lmax);   
}
void build(int tn,int l,int r)
{
    tree[tn].len=tree[tn].lmax=
    tree[tn].rmax=tree[tn].amax=r-l+1;
    tree[tn].lazy=-1;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
}
void PushDown(int tn)
{
    if(tree[tn].lazy!=-1){
        int flg=tree[tn].lazy;
        tree[tn<<1].lazy=tree[tn<<1|1].lazy=flg;
        tree[tn<<1].amax=tree[tn<<1].lmax
            =tree[tn<<1].rmax=(flg?0:tree[tn<<1].len);
        tree[tn<<1|1].amax=tree[tn<<1|1].lmax
            =tree[tn<<1|1].rmax=(flg?0:tree[tn<<1|1].len);
        tree[tn].lazy=-1;
    }
}
int query(int tn,int l,int r,int len)
{

    if(l==r) return l;
    PushDown(tn);
    int mid=(l+r)>>1;
    if(tree[tn<<1].amax>=len)
        return query(lson,len);
    else if(tree[tn<<1].rmax+tree[tn<<1|1].lmax>=len)
            return mid-tree[tn<<1].rmax+1;
    else return query(rson,len);
}
void update(int tn,int l,int r,int x,int y,int flg)
{
    if(x<=l&&r<=y){
        tree[tn].lazy=flg;
        tree[tn].amax=tree[tn].lmax
            =tree[tn].rmax=
            (flg?0:tree[tn].len);
        return;
    }
    PushDown(tn);
    int mid=(l+r)>>1;
    if(x<=mid) update(lson,x,y,flg);
    if(y>mid) update(rson,x,y,flg);
    PushUp(tn);
}
struct _Query
{
    int frm,to;
}qry[110];
int main(int argc, char const *argv[])
{
    int L,b,f;
    scanf("%d %d %d",&L,&b,&f);
    build(1,1,L+b+f);
    ms(qry);
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int typ,lth;
        scanf("%d %d",&typ,&lth);   
        if(typ==1){
            if(lth+b+f>tree[1].amax) {puts("-1");
            continue;}
            int pos=query(1,1,L+b+f,lth+f);//特殊处理
            if(pos==1){
                pos--;
                if(pos+lth<=L){
                update(1,1,L+b+f,pos+1,pos+lth,1);
                printf("%d\n",pos );
                qry[i].frm=pos+1,
                qry[i].to=pos+lth;
                }
            }
            else {
                pos=query(1,1,L+b+f,lth+b+f);
                if(pos!=-1){
                    pos+=b-1;
                    if(pos+lth<=L){
                    update(1,1,L+b+f,pos+1,pos+lth,1);
                    printf("%d\n",pos );
                    qry[i].frm=pos+1,
                    qry[i].to=pos+lth;
                    }
                    else puts("-1");
                }
                else puts("-1");
            }
        }
        else 
         update(1,1,L+b+f,qry[lth].frm,qry[lth].to,0);
    }
    return 0;
}

```


---

## 作者：May_Cry_ (赞：0)

**1. 思路**

这题第一眼线段树，但观察到 $ n $ 数据范围很小，所以考虑直接暴力模拟。我们可以开一个 ``map``，记录每次操作的右端点，开一个 $ a $ 数组记录每次操作的左端点，最开始插入 $ - b $ 和 $ L + f$（这里必须插入 $ 2 $ 个元素，不然无法遍历），插入操作直接遍历 ``map``，当符合要求时，直接给当前 $ a_i $ 赋值为上一辆车的右端点加 $ b$(注意这里要加 $ b$，因为第一个元素是 $ -b$），``map[a[i]]`` 的值就为 $ a_i + x$，删除操作直接用 `erase` 函数，细节见代码。

**2. 代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n ,b ,f ,m;
int a[100000] ,cnt;
map <int, int> mp;
inline int read();
int main(){
	n = read();b = read();f = read();
	m = read();
	mp[- b] = - b;mp[n + f] = n + f;
	while(m --){
	    int op = read() ,x = read();cnt ++;
	    if(op == 1){
	    	a[cnt] = -1;
	    	for (auto last = mp.begin() ,t = ++ mp.begin();t != mp.end();++ t ,++ last){
//	    		cout << last -> first << " " << t -> second << endl;
	    		if(t -> first - last -> second >= x + b + f){
	    			a[cnt] = last -> second + b;	
	    			mp[a[cnt]] = a[cnt] + x;
	    			break;
				}
//				last = t;
			}
			cout << a[cnt] << endl;
		} 
		else mp.erase(a[x]);
	}
}
inline int read(){
	int x = 0 ,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
```
~~写的有点恶心，凑活着看~~


---

