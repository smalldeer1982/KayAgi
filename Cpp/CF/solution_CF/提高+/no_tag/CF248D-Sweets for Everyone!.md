# Sweets for Everyone!

## 题目描述

For he knew every Who down in Whoville beneath, Was busy now, hanging a mistletoe wreath. "And they're hanging their stockings!" he snarled with a sneer, "Tomorrow is Christmas! It's practically here!"

Dr. Suess, How The Grinch Stole Christmas



Christmas celebrations are coming to Whoville. Cindy Lou Who and her parents Lou Lou Who and Betty Lou Who decided to give sweets to all people in their street. They decided to give the residents of each house on the street, one kilogram of sweets. So they need as many kilos of sweets as there are homes on their street.

The street, where the Lou Who family lives can be represented as $ n $ consecutive sections of equal length. You can go from any section to a neighbouring one in one unit of time. Each of the sections is one of three types: an empty piece of land, a house or a shop. Cindy Lou and her family can buy sweets in a shop, but no more than one kilogram of sweets in one shop (the vendors care about the residents of Whoville not to overeat on sweets).

After the Lou Who family leave their home, they will be on the first section of the road. To get to this section of the road, they also require one unit of time. We can assume that Cindy and her mom and dad can carry an unlimited number of kilograms of sweets. Every time they are on a house section, they can give a kilogram of sweets to the inhabitants of the house, or they can simply move to another section. If the family have already given sweets to the residents of a house, they can't do it again. Similarly, if they are on the shop section, they can either buy a kilo of sweets in it or skip this shop. If they've bought a kilo of sweets in a shop, the seller of the shop remembered them and the won't sell them a single candy if they come again. The time to buy and give sweets can be neglected. The Lou Whos do not want the people of any house to remain without food.

The Lou Whos want to spend no more than $ t $ time units of time to give out sweets, as they really want to have enough time to prepare for the Christmas celebration. In order to have time to give all the sweets, they may have to initially bring additional $ k $ kilos of sweets.

Cindy Lou wants to know the minimum number of $ k $ kilos of sweets they need to take with them, to have time to give sweets to the residents of each house in their street.

Your task is to write a program that will determine the minimum possible value of $ k $ .

## 说明/提示

In the first example, there are as many stores, as houses. If the family do not take a single kilo of sweets from home, in order to treat the inhabitants of the first house, they will need to make at least one step back, and they have absolutely no time for it. If they take one kilogram of sweets, they won't need to go back.

In the second example, the number of shops is equal to the number of houses and plenty of time. Available at all stores passing out candy in one direction and give them when passing in the opposite direction.

In the third example, the shops on the street are fewer than houses. The Lou Whos have to take the missing number of kilograms of sweets with them from home.

## 样例 #1

### 输入

```
6 6
HSHSHS
```

### 输出

```
1
```

## 样例 #2

### 输入

```
14 100
...HHHSSS...SH
```

### 输出

```
0
```

## 样例 #3

### 输入

```
23 50
HHSS.......SSHHHHHHHHHH
```

### 输出

```
8
```

# 题解

## 作者：Chaniaq_awa (赞：2)

在这里讲一下我对这道题的理解: 

先讲一下这题的过程，再详细解释一下各部分：
二分开始手里拿的糖，验证时就是贪心，取能发完糖的最少时间然后和题目给的比大小。

首先，为什么是二分，因为开始拿的糖满足单调性，也就是开始糖拿的越多成功的可能越大，所以显而易见是二分

然后思考贪心策略，我们分成两个思路来想：


- 手里还有糖，那肯定给出去
- 手里没有糖，那这时候我们可以想到一种策略，就是经过房子的时候先欠着糖，等手里有足够的糖了的一瞬间再还回去。那么我们想，怎么证明这样是对的呢，因为如果我们继续往前走，往前走没有拿到任何糖然后再折返，那么肯定是会比刚刚那种策略差的。那我们再思考，如果往前拿到了糖呢？仔细思考可以知道，第一种策略不会比继续往前更差。如果我们还糖那么从你现在拿完糖了到欠糖的那一步需要往返，也就是这段路程走了两次，然后就可以继续走了。那如果我们继续往前走呢，那和这个策略一样，都是一段路程走了两次。所以证明这种策略是最优的。

这时候代码就很容易写了，细节都在代码里了



```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t;
string s;
int sum;
bool check(int x) { //x为带的糖数  
    int num_H = 0;      // 已收集的H数量
    int fir = 0;     // 第一个未处理的H的位置
    int las = 0;     // 最后一个未处理的H的位置
    int cnt = 0;      // 需要额外往返的时间
    int lt = t;        // 剩余时间
    for(int i = 1;i <= n;i++) {
        if (num_H == sum && x >= 0)
            return lt >= min(i - fir, cnt);
        lt--; // 移动一步消耗时间
        if(s[i] == 'H') {
            if(!x) {
                if(!fir) fir = i;
                las = i;
            }
            x--;
            num_H++;
        }
        else if (s[i] == 'S') {
            x++;
            if (!x) {
                cnt += i - las; //不会有比这更优的策略 
                if (num_H != sum) cnt += i - las; // 往返路径
            }
        }
    }
    return lt >= min(n - fir, cnt) && x >= 0;
}
int main() {
    cin >> n >> t; cin >> s;
    s = " " + s;
    for (int i = 1; i <= n; i++)
        sum += (s[i] == 'H');
    int l = 0,r = sum;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if(check(l)) cout << l << endl;
    else cout << -1;
    return 0;
}
```
```

---

## 作者：lgswdn_SA (赞：2)

> 给定一个一维地图，`H` 表示一户人家（遇到可以送糖果或者不送），`S` 表示一个糖果（遇到可以捡起或者不捡），`.` 表示空地，走过一格需要一单位时间。问从第一格左边开始，最少提前准备多少糖果才能在 $t$ 时间内给每户人家都有一份糖果。

先上 useful binary search。

Observation：糖一定捡，并且一定送。

有两种决策。第一种，走过去然后走回来。第二种情况，先没有糖走过去然后拿到糖了立马回来送。

这种情况可以这样理解：我先把糖欠着，然后一旦糖够了立马还回来。可以发现这样的决策在决定走 S 形（去+回+去）的方法上是最优的。

当然你也可以不还。但实际上，一旦你在第 $i$ 户做出决定要全部赖账然后跑回来再还，那你就在之后不可能再做上述决定了。所以我们在按上述决策跑的同时，每一步都看一下，如果剩下的要跑过去然后跑回来要花多少时间。每次最远到达的那个点必然是固定的，所以求出来后直接做就好了。

```cpp
const int N=5e5+9;

int n,t,tot,st;
int p[N],suf[N];
char s[N];

bool check(int x) {
	int pos=0,curt=0,endp=0;
	int cnt=x;
	while(endp<n&&cnt<tot) cnt+=(s[++endp]=='S');
	while(endp<n&&suf[endp+1]) endp++;
	if(cnt<tot) return 0;
	rep(i,1,endp) {
		curt++;
		if(s[i]=='S') {
			x++;
			if(x==0) {
				if(suf[i]==0) curt+=(i-pos);
				else curt+=2*(i-pos);
				pos=0;
			}
		} else if(s[i]=='H') {
			x--;
			if(x<0&&!pos) {
				pos=i;
				int nt=curt+2*(endp-i);
				if(nt<=t) return 1;
			}
		}
	}
	return curt<=t;
}

signed main() {
	n=read(), t=read();
	scanf("%s",s+1);
	rep(i,1,n) tot+=(s[i]=='H'), st+=(s[i]=='S');
	per(i,n,1) suf[i]=suf[i+1]+(s[i]=='H');
	int l=max(0ll,tot-st),r=n,ans=-1;
	while(l<=r) {
		int mid=(l+r)/2;
		if(check(mid)) r=mid-1, ans=mid;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：smoothset (赞：1)

[原文链接](https://blog.csdn.net/qq_43537070/article/details/107563752)
#### 这是一道二分加贪心题
#### 题意
在一条路上有若干个店和房子，每个房子要放一个糖果，每经过一个商店可以得到一个一个糖果。
现在我们开始可以携带$k$个糖果，要求在$t$时间内完成，求这个$k$的最小值。
#### 思路
在这个题中，我们可以二分这个$k$值，然后考虑怎么验证可行性。
首先一定是有糖肯定会给，然后再看如果当没有糖果时，是采取拿到满足之前的糖果数后就返回送糖果，还是最后一口气拿到足够的再返回。
如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724162403524.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTM3MDcw,size_16,color_FFFFFF,t_70)
~~画图技巧有限，望海涵~~
那么在$check()$中考虑这两个情况，可以知道一定只有一次会选择走到底再走回去。
所以直接二分这个方法修改点，就ok了
#### 代码
具体实现见代码
~~~cpp
bool check(int x)
{
    int cnt = 0, pos1 = 0, pos2 = 0, sub = 0, s = t;
    for (int i = 1; i <= n; i++)
    {
        if (cnt == sum && x >= 0)
            return s >= min(i - pos1, sub);
        s--;
        if (str[i] == 'H')
        {
            if (!x)
            {
                if (!pos1)
                    pos1 = i;
                pos2 = i;
            }
            x--;
            cnt++;
        }
        else if (str[i] == 'S')
        {
            x++;
            if (!x)
            {
                sub += i - pos2;
                if (cnt != sum)
                    sub += i - pos2;
            }
        }
    }
    return s >= min(n - pos1, sub) && x >= 0;
}
int main()
{
    rd(n), rd(t);
    scanf ("%s", str + 1);
    for (int i = 1; i <= n; i++)
        sum += str[i] == 'H';
    int l = 0, r = sum;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    if (check(l))
        pt(l);
    else
        pt(-1);
    return 0;
}
~~~
#### 谢谢

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
有一些商店和一些居民在一排上，某人要从起点开始对全部居民发放 $1$ 千克糖果，每一个商店能够能够且仅能够买一次 $1$ 千克糖果，每向前或向后走以单位须要 $1$ 时间单位，求在 $t$ 时间内发完所以的居民最少须要自身带多少千克糖果。
## 分析
明显就是二分，二分答案。然后从边界開始判可行。这题的可行还是有点难判。首先糖果手中充足，遇到一个居民就发放 $1$ 千克。当糖果不充足的时候。仅仅能有两种决策，直接跑到尽头再回来。或者继续往前走，知道糖果数已经集够所需再回来。

差分后的序列来说就是，当 $sum_i=-1$ 并且 $sum_{i-1}=0$ 时。直接跑到尽头，或者继续走到 $sum_i=0$ 并且 $sum_{i-1}=-1$ 的位置，再回去，再回来。
## 代码

```cpp
#include <bits/stdc++.h>
#define SZ(x) ((int)(x).size())
#define ALL(v) (v).begin(), (v).end()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
#define reveach(i, v) for (__typeof((v).rbegin()) i = (v).rbegin(); i != (v).rend(); ++ i)
#define REP(i,n) for ( int i=1; i<=int(n); i++ )
#define rep(i,n) for ( int i=0; i< int(n); i++ )
using namespace std;
typedef long long ll;
#define X first
#define Y second
typedef pair<int,int> pii;
template <class T>
inline bool RD(T &ret) {
    char c; int sgn;
    if (c = getchar(), c == EOF) return 0;
    while (c != '-' && (c<'0' || c>'9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ?
 0 : (c - '0');
    while (c = getchar(), c >= '0'&&c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
template <class T>
inline void PT(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) PT(x / 10);
    putchar(x % 10 + '0');
}
const int N = 5e5+100;
int n,lim,MAX;
int sum[N];
int a[N];
char s[N];


bool ok(int x,int maxx){
        int cnt = x;
        int cur = 0;
        int tmp = 0x3f3f3f3f;
        int pos,last = 0;
        REP(i,n) {
                if( s[i] == 'H') cnt--;
                else if( s[i] == 'S') cnt++;
                if( cnt == 0 && last == -1) maxx = max(maxx,i);
                last = cnt;
        }
        cnt = x , last = 0;
        for(int i = 1; i <= maxx; i++){
                cur ++;
                if( s[i] == 'H') cnt--;
                else if( s[i] == 'S') cnt++;
                if( last == 0 && cnt == -1) {
                        tmp = min(tmp,cur + 2*(maxx-i));
                        pos = i;
                }if( last == -1 && cnt == 0){
                         cur += 2*(i-pos);
                }
                last = cnt;
        }
        return min(tmp,cur) <= lim;
}
int main(){


	scanf("%d%d%s",&n,&lim,s+1);
	int ch = 0,cs = 0;
	REP(i,n){
                if( s[i] == 'H') MAX = i,ch++;
                else if( s[i] == 'S') cs++;
	}
	int lb = max(0,ch-cs)-1;
	int ub = 0x3f3f3f3f;
	if(MAX > lim){
                puts("-1");
                return 0;
        }
	while(ub-lb > 1){
		int mid = (lb+ub)/2;
		if( ok(mid,MAX) ) ub = mid;
		else lb = mid;
	}
	printf("%d\n",ub);
}
```

---

## 作者：开始新的记忆 (赞：0)

**题目大意**（翻译是我手打的，语文不太好，见谅）

圣诞节到了！你现在想去给每家每户分糖果。‘H’表示这里有一户人家，‘S’表示这里有一家超市，‘.’表示这里为空地，当你经过超市时，可以买1kg糖果（如果之前来买过，则当空地看）。现在有n个地方，因为要筹备圣诞节，你只有t的时间来完成这些任务，问能否让每户人家都分到1kg糖果。因为时间原因，你需要提前准备一些糖果，如果可以完成上述要求，输出最少需要提前准备多少个糖果，如果不行则输出-1.

大致思路：经过一系列的手推发现，当到达了一户人家且糖果没有了时，只有两种情况可导致最优解产生：1.往后继续走，直到遇见第一个超市就折返回来；2.一直走到底，再返回。

但是如果暴力的话肯定会T的，而又只需要求出糖果数量，则可以二分答案（从0~n一直二分）

具体代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,sw[100010],l=0,r=0;
string a;

bool judge(int va)
{   
	int num=va,ans,end=0,last;
    for(int i=0;i<n;i++)
	{
        if(a[i]=='H')
		{
            end=i;
            num--;
        }
        else if(a[i]=='S')
		{
            num++;
            if(num==0)
                end=i;
        }
    }
    if(num<0)
        return 0;
    ans=0;last=-1;num=va;
    for(int i=0;i<=end;i++)
	{
        ans++;
        if(a[i]=='H')
		{
            num--;
            if(num==-1)
			{
                if(ans+((end-i)*2)<=t)
                    return 1;
                last=i;
            }
        }
        else if(a[i]=='S')
		{
            num++;
            if(num==0)
			{
                ans+=(i-last)*2;
                last=-1;
            }
        }
    }
    if(ans<=t)
        return 1;
    return 0;
}

int main()
{	int l,r;
	cin>>n>>t>>a;
    l=0;r=n;
    while(l<r)
    {
    	int mid=(l+r)/2;
		if(judge(mid))
			r=mid;
		else
		    l=mid+1;
	}
	if(judge(l))
	    cout<<l<<endl;
	else
		cout<<-1<<endl;
	return 0;
}
```


---

