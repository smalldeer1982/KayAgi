# [USACO09OCT] Allowance G

## 题目描述

作为创造产奶纪录的回报，Farmer John 决定开始每个星期给Bessie 一点零花钱。

FJ 有一些硬币，一共有 $N (1 \le N \le 20)$ 种不同的面额。每一个面额都能整除所有比它大的面额。

他想用给定的硬币的集合，每个星期至少给 Bessie 某个零花钱的数目 $C (1 \le C \le 100000000)$。请帮他计算他最多能支付多少个星期的零花钱。


## 样例 #1

### 输入

```
3 6
10 1
1 100
5 120```

### 输出

```
111```

# 题解

## 作者：ButterflyDew (赞：36)

一开始的贪心很容易想到要每次先给大钱，如果不够一步步拿小钱补充。

但最后小钱用完了可能产生浪费，万一大钱浪费一下可以更少呢。又看了看数据范围$N(1<=N<=20)$，心想怕不是个搜索。憋了一会儿搜索写不出来。最后看了题解才知道是贪心。

先说说这个题贪心的思维导向性在哪，没错就是这句话**“每一个面额都能整除所有比它大的面额”**，是不是感觉又奇怪又违和，感觉用不上？？

一般来讲，遇到这种看起来比较怪的条件，可以尝试这向贪心的方面想一想。哪怕证不出来也没关系，骗点分总不亏撒

------------

下面正题，贪心策略及证明

### 策略
每一次给钱时，从大钱开始给，但**每次给到要浪费钱的一次**就不给了，用小一些的钱给。
给到已经没有小钱了以后，再给怎么也会产生浪费，就从小到大给，用**面值尽可能小的钱产生浪费**。

总结起来就是一句话：**当需要产生浪费时，用面值尽可能小的钱产生**

### 证明
命题：大钱产生的浪费一定不比小钱小

证明：
任取两个面值的钱分别为$ka,a$，$k$是正整数，在当前次还需要支付零用钱至少$X$

(1) 当浪费大钱$ka$时
设$X=b*ka+r$①

则浪费的钱数为$f=ka-r$②

(2)当浪费小钱$a$时
用掉一定的$ka$却不浪费当前次还需要支付的零用钱为$X'=r$
设$X'=b'*a+r'$③

则浪费的钱数为$f'=a-r'$④

两者做差，$f-f'=(k-1)*a+r'-r$

由③得，$r'-r=-b'*a$

则$f-f'=(k-b'-1)*a$

因为$k,b'$均为正整数且$k>b'$，所以$f-f'>=0$

命题得证。

------------
当然，我们肯定不能一次次的枚举每一周的给钱方案，否则会$T$两组。

考虑对情况进行加速，说是加速，其实也就是存储每周在某种情况下每个钱用了多少张，然后直接统计这种用钱情况可以重复多少次而已。

写的时候注意细节

[露迭月喵~](https://www.cnblogs.com/ppprseter/)


---

## 作者：kkxhh (赞：16)

思路最顶上的题解已经说得很清楚了，不过看样子并没有题解是按照顶上那篇题解说的在计算的时候加速一下，于是我就写了一下

要改的地方不多，只要额外**加一个数组记录一下当前的方案每种硬币用了多少，最后除一下取最小的**就好了

~~速度果然快了很多~~

代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef struct coin {int v,b;}coin;

coin cn[30];
int n,c,sum=0,k=0;

bool cmp(coin a,coin b) {return a.v<b.v;}

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?-1:k,c=getchar();
    while(c>='0' && c<='9') num=(num<<3)+(num<<1)+c-'0',c=getchar();
    return num*k;
}

int main() {
    n=read(); c=read();
    for(int i=1;i<=n;i++){
        int v=read(),b=read();
        if(v>=c) {sum+=b; continue;}
        cn[++k].v=v; cn[k].b=b;
    }
    sort(cn+1,cn+k+1,cmp);
    while(true){
        int x=c,v[30]={0};
        for(int i=k;i>=1;i--){
            if(cn[i].b<=0 || cn[i].v>x) continue;
            if(cn[i].b>=x/cn[i].v) v[i]+=x/cn[i].v,x=x%cn[i].v;
            else v[i]+=cn[i].b,x-=cn[i].b*cn[i].v;
        }
        for(int i=1;i<=k;i++){
            if(x<=0) break;
            if(cn[i].b-v[i]<=0 || x>cn[i].v) continue;
            x-=cn[i].v; v[i]++;
        }
        if(x>0) break;
        int ans=1000000000;
        for(int i=1;i<=k;i++) if(v[i]) ans=min(ans,cn[i].b/v[i]);
        for(int i=1;i<=k;i++) cn[i].b-=ans*v[i];
        sum+=ans;
    }
    printf("%d",sum);
    return 0;
}
```

---

## 作者：Super_Cube (赞：6)

# 题目大意：

你手上有 $n$ 种硬币，每种硬币的面值为 $V_i$，数量为 $B_i$，且这些硬币的面值满足面值大的硬币总能整除面值小的硬币。现在问你用这些硬币能够支付出几次 $\ge C$ 的面值。

---

# 思路：

注意到这句话：**面值大的硬币总能整除面值小的硬币**。

什么意思呢？就是你可以**用小面值硬币凑出大面值硬币的面值**。

这样我们这道题就可以用**贪心**的思路求解了。

经过对上面的分析，不难看出**浪费面值大的硬币比浪费面值小的划算**（因为大面值可以用小面值凑出来）。所以，我们对所有的硬币进行以 $V_i$ 来降序排列。

对于 $V_i \ge C$ 的这部分硬币，直接把它们对应的数量加在答案里（每一次用一个硬币就可以满足 $\ge C$ 的条件）。

对于 $V_i < C$ 的这部分硬币，根据上面的结论，我们先用面值大的尽可能凑出 $C$，如果凑完还不够 $C$，就再从面值小的中找到第一个**大于等于**需要的面值的硬币，用它凑出与前面的大面值硬币一起凑出 $\ge C$ 面值。

可我要是没找到呢？那没办法，说明肯定是凑不出来了，直接输出答案结束程序。

---

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> >v;
int n,m,k,x,y,ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>x>>y;
		if(x>=m)ans+=y;
		else v.push_back(make_pair(x,y));
	}stable_sort(v.begin(),v.end(),greater<pair<int,int> >());//按面值从大到小
	while(1){
		k=m;
		for(int i=0;i<v.size();++i){
			while(k>0&&v[i].second&&k>=v[i].first){
				--v[i].second;k-=v[i].first;
			}//用面值大的凑
		}
		if(k>0){
			for(int i=v.size()-1;i>=0;--i){
				if(v[i].second&&v[i].first>=k){
					--v[i].second;k-=v[i].first;break;
				}//找到第一个可以凑出剩余面值的硬币
			}
		}if(k>0)break;//没找到qwq
		++ans;
	}cout<<ans;
	return 0;
}
```

---

## 作者：wuzhoupei (赞：5)

这道题才一个题解；

我来写一个；

这道题是个贪心，怎么说是贪心呢，就是先选大的，后考虑小的；

千万不要把上句话的意思理解歪了，一开始我就理解歪了，然后华丽丽地TLE了；

其实就是for，然后如果当前这个值可以被选，就选到不能再选这个值为止；

还有一个小技巧，就是我们定义一个值，等于c，然后用这个值减，知道小于等于0，这样子比一直加到c好处理多了；

一开始我是加到c，太难处理了；

然后就是while和for就好了；

cpp
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define II int
#define B bool
#define R register
#define I 123456
using namespace std;


struct node {
    II buy,nu;
}aa[I];

II n,c,ans;

B maP(node a1,node a2) { return a1.buy>a2.buy; }


int main()
{
    freopen("1.in","r",stdin);
    
    scanf("%d%d",&n,&c);
    for(R II i=1;i<=n;i++)
    {
        scanf("%d%d",&aa[i].buy,&aa[i].nu);
    } 
    
    sort(aa+1,aa+n+1,maP);
    
    R II now=1, en=n;
    while (aa[now].buy>=c) {
        ans+=aa[now].nu;
        now++;
    }
    
    while (1) {
        R II ka=c;
        // 小技巧; 
        for(R II i=now;i<=n;i++)
        // 所谓的从大到小贪心就是这个枚举顺序了; 
        {
            while (ka>=aa[i].buy&&aa[i].nu&&ka>0) {
                ka-=aa[i].buy;
                aa[i].nu--;
            }
            // 一直减到不能再减为止，然后换下一个值;
        } 
        if(ka>0) for(R II i=n;i>=now;i--) {
            if(aa[i].buy>=ka&&aa[i].nu) {
                aa[i].nu--;
                ka-=aa[i].buy;
                break ;
            }
        }
        // 找一个大于剩余值且最小的, 补全; 
        if(ka>0) break ;
        // 如果还不行，证明剩下的组不成c了，结束; 
        ans++;
    }
    
    printf("%d\n",ans);
    exit(0);
}
```

---

## 作者：zhuozhizhao (赞：4)

原文链接：<http://blog.csdn.net/love\_phoebe/article/details/76831019>

要使每个月的钱都大于常数C，就要使每次花的冤枉钱最少

1，输入时便不记录那些大于C的面额，直接加

[cpp] view plain copy

```cpp
cin>>N>>C;  
for(int i=0,lin=0;i<N;i++){  
    int l1,l2;  
    cin>>l1>>l2;  
    if(l1>=C)sum+=l2;  
    else{s[lin].a=l1,s[lin].b=l2;lin++;}  
    }  
```
2,剩下的记录在数组s中的便全是小于C的面额；
利用sort函数按面值从小到大排列

整个过程在while(1)中进行

从大的开始找，在s[i].b>0&&x>=s[i].a的情况下x-=s[i].a;

如C=13，s[i].a=4，就减三次，剩下1；

如果 s[i].a=10，就减两次，无剩余

[cpp] view plain copy

```cpp
int x=C;  
for(i=lin-1;i>=0;i--){  
    if(s[i].b>0&&x>=s[i].a){  
        for(;s[i].b>0&&x>=s[i].a;){  
            x-=s[i].a;  
            s[i].b--;  
        }  
    }  
}  
```
3，如果x>0(还有剩余)
从小的里面挑大于x的去减；

[cpp] view plain copy

```cpp
if(x>0)for(i=0;i<lin;i++){  
    if(s[i].b>0&&x<=s[i].a){  
        x-=s[i].a;  
        s[i].b--;  
        break;  
    }  
}  
```
4，最后sum++，如果x还大于0正面已经无法满足，结束循环
[cpp] view plain copy

sum++;  

if(x>0)break;  

完成代码如下：

[cpp] view plain copy

```cpp
#include<iostream>  
#include<cstring>  
#include<cstdlib>  
using namespace std;  
const int M=10000000;  
struct lin{  
    int a;  
    int b;  
}s[30];  
int cmp(const void*x,const void*y){  
    struct lin*x1=(lin*)x;  
    struct lin*x2=(lin*)y;  
    return x1->a-x2->a;  
}  
int main(){  
    int i,N,C,lin=0,sum=0;  
    cin>>N>>C;  
    for(i=0;i<N;i++){  
        int l1,l2;  
        cin>>l1>>l2;  
        if(l1>=C)sum+=l2;  
        else{s[lin].a=l1,s[lin].b=l2;lin++;}  
    }  
    qsort(s,lin,sizeof(s[0]),cmp);  
    while(1){  
        int x=C;  
        for(i=lin-1;i>=0;i--){  
            if(s[i].b>0&&x>=s[i].a){  
                for(;s[i].b>0&&x>=s[i].a;){  
                    x-=s[i].a;  
                    s[i].b--;  
                }  
            }  
        }  
        if(x>0)for(i=0;i<lin;i++){  
            if(s[i].b>0&&x<=s[i].a){  
                x-=s[i].a;  
                s[i].b--;  
                break;  
            }  
        }  
        if(x>0)break;  
        sum++;  
    }  
    cout<<sum;  
    return 0;  
}
```

---

## 作者：夏色祭 (赞：3)

##没有P的，我来补一发

其实一开始自己的代码有点小bug，但是最后还是A掉了~~打表了两个~~

然后看了cghAndy大佬发的题解，一下子茅塞顿开。。。~~这是最骚的~~

对于每天要给的C元，最终给的钱当然越近越好。

凑钱要先从大钱开始凑~~贪心策略~~，所以我们对于读入的数据，单价>=C的就直接删掉，最终答案加上这种硬币的数量，否则这把这个零钱加入数组，然后使这个数组有序（根据单价排）。

然后一个一个从大到小先凑，即对于第i个硬币，剩下还需要给的钱最多能付几个这样的硬币。

这样的话最后会有两种情况：

1、剩下还需要的钱>0

那么从小到大如果第i种硬币还能付则在付一个，如果当前钱<=0就直接推出，然后转2

2、剩下的还需要的钱<=0

那么说明钱够了，否则说明所有钱加起来都不够付一天的了，直接推出

如果不退出，则去找这n种硬币中可以**支付C的个数**（注意是C的个数，即数量 div 需要付的数量）最少的，因为选大的话，可能小的硬币的数量就不够了

最后给最终答案+支付C的个数最少的

并把每个硬币数量减去对应的

丑陋的代码：



```cpp
uses math;
var
  a,b,zz:array[0..21]of longint;
  i,j,n,t,m,r,sum,ans,x,y,minn:longint;
begin
  readln(t,m);
  for i:=1 to t do 
    begin
      readln(x,y);
      if x>=m then inc(ans,y)
        else begin inc(n);a[n]:=x;b[n]:=y; end;
    end;//读入
  for i:=1 to n-1 do 
    for j:=i+1 to n do 
      if a[j]<a[i] then 
        begin
          a[0]:=a[i];a[i]:=a[j];a[j]:=a[0];
          b[0]:=b[i];b[i]:=b[j];b[j]:=b[0];
        end;//排序
  r:=n;
  while true do 
    begin
      sum:=m;
      for i:=r downto 1 do 
        begin
          x:=min(b[i],sum div a[i]);
          dec(sum,x*a[i]);
          zz[i]:=x;
        end;
      if sum>0 then 
        for i:=1 to r do 
          begin
            if sum<=0 then break;
            if zz[i]<b[i] then 
              begin 
                inc(zz[i]);
                dec(sum,a[i]);
              end;
          end;
      if sum<=0 then 
        begin
          minn:=maxlongint;
          for i:=1 to r do
            if zz[i]>0 then minn:=min(minn,b[i] div zz[i]);
          inc(ans,minn);
          for i:=1 to r do 
            if zz[i]>0 then dec(b[i],minn*zz[i]);
        end
        else break;
    end;//上面我想应该说的十分十分的清楚了。。。懒得写注释了 ~~妖怪吧~~
  writeln(ans);
end.

```

---

## 作者：miss_A (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P2376)

[博客食用效果更佳](https://blog.csdn.net/m0_71452979/article/details/132403932?spm=1001.2014.3001.5501)

题目想要求出能够支付零花钱的最大星期数，而每种硬币的面额和数量都是固定的，那么就要使浪费尽可能少，所以贪心应该是这道题的正确思路。

### 贪心策略

1. 在输入时判断硬币面额
   - 如果面额**大于**每星期需支付的最小零花钱，那么就说明一枚这种硬币就可以**独立**支付一个星期的零花钱，就不需要和其他硬币共同支付。这样的话，要使浪费尽可能少，每次就应该**只支付一枚**这种硬币。所以**能支付的星期数 + 这种硬币的数量**。
   - 如果面额**小于等于**每星期需支付的最小零花钱，那么就说明一枚这种硬币**无法独立**支付一个星期的零花钱，因此需要和其他硬币一起支付。我们先将这种硬币的面额和数量存进一个**结构体**，后续进行判断。
2. 对于每一个星期
   - 因为当前剩余的所有硬币面额都小于最小零花钱，因此不存在独立支付的情况。
   - 当不一定会产生浪费时：因为小面额硬币能够整除所有比它大的面额，所以小面额可以凑出大面额。因此为了避免后续不必要的浪费，我们优先使用大面额硬币。
   - 当浪费无可避免时（即本周空缺小于所有面额时）：为了使浪费最小，我们优先使用小面额。
   - 如果无论如何都无法凑出大于等于最小零花钱的面额，就说明手中剩下的钱无法再支付一个星期的零花钱，结束贪心。

### AC代码（含注释）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
int n, least_num;//面额数，每星期最少零花钱数目
int ans, cnt;

struct money
{
    int value;//面额
    int num;//数量
}coin[21];

bool cmp(money a, money b){
    return a.value > b.value;
}

int main(){

    //freopen("code.in", "r", stdin);
    //freopen("code.out", "w", stdout);

    cin >> n >> least_num;
    for(int i = 1; i <= n; i++){
        int a, b;
        cin >> a >> b;
        if(a >= least_num){//面额大于最小零花钱的硬币，可以独立支付一个星期的零花钱
            ans += b;
            continue;
        }
        else {//面额小于最小零花钱的硬币需要和其他硬币一起支付，所以先存起来后续再判断
            coin[++cnt].value = a;
            coin[cnt].num = b;
        }
    }
    sort(coin + 1, coin + 1 + cnt, cmp);//降序排列

    while(1){//无限循环，等到不足以支付了就主动跳出
        int k = least_num;
        for(int i = 1; i <= cnt; i++){//先用大面额
            //当仍需要新的硬币才能支付本周零花钱时
            while(k > 0 && coin[i].num && k >= coin[i].value){
                k -= coin[i].value;
                --coin[i].num;
            }
        }
        for(int i = cnt; i >= 1; i--){//如果一定会产生浪费，那就用尽量小的面额
            if(k > 0 && coin[i].num && coin[i].value >= k){
                --coin[i].num;
                k -= coin[i].value;
            }
        }
        if(k > 0)break;//如果无法凑出大于等于k的值，就说明手中剩下的钱无法再支付一个星期的零花钱
        else ans++;//可以凑出k的值，这个星期正常支付
    }

    cout << ans;
    return 0;
}
```



---

## 作者：ethan0328 (赞：2)

## 思路

观察到**每一个面额都能整除所有比它大的面额**，所以考虑贪心。

因为大的可以由小的凑成，所以我们尽量先用面值大的去凑 $c$。

具体的，先从大到小让所有 $a_i \le c$ 的都用掉（这里的 $c$ 每次要减掉 $a_i$），在从小到大找到第一个 $a_i \ge c$，把它减掉（这里的 $c$ 也是减过之后的）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50;
struct coin
{
	int v,b;
	bool operator <(const coin x) const
	{
		return v>x.v;
	}
};
int n,c,ans;
coin a[N];
int main()
{
	int x;
	cin>>n>>c;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].v>>a[i].b;
	}
	sort(a+1,a+1+n);
	while(true)
	{
		x=c;
		for(int i=1;i<=n;i++)
		{
			while(a[i].v<=x&&a[i].b>0)
			{
				x-=a[i].v;
				a[i].b--;
			}
		}
		if(x>0)
		{
			for(int i=n;i;i--)
			{
				if(a[i].v>=x&&a[i].b>0)
				{
					x-=a[i].v;
					a[i].b--;
					break;
				}
			}
		}
		if(x>0)
		{
			break;
		}
		ans++;
	}
	cout<<ans;
}
```


---

## 作者：haotian1234 (赞：2)

## 题意暗示
- 每一个面额都能整除所有比它大的面额，说明每一种大面额的金额，都能用小面额的金额兑换。
- 至少说明了给杀马特的零钱可以超过 $C$ 
## 题目分析
1. 先将所有面值超过 $C$ 的金额总数相加，得到最少的星期数
1. 从大的面额开始枚举，这样可以用小的面额弥补大的面额与 $C$ 的差值。若大的面额与 $C$ 的差值超过了这个面额。那么就用面值比这个小的来弥补。（至于如何找到比这个面额小的，可以用一个双关键排序）
1. 当连最小的面额加上目前给的零花钱都超过了 $C$，那就只好用最小的面额了。
## 题目坑点
- 面额有用的上限，不能无限用。
- 给的钱可以超过 $C$。

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,ans,j;
struct no{
    int x,y;
}a[100100];
bool cmp(no x,no y){
    return x.x>y.x;
}//双关键排序
int main(){
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+1+n,cmp);
    for (i=1;i<=n;i++)
        if (a[i].x>m) ans+=a[i].y;
        else break;//先将所有面值超过C的金额总数相加，得到最少的星期数
    for (;i<=n;i++){
        while (a[i].y>0){//不用完所有钱不罢休
            int mm=m;
            while (a[i].y>0&&mm>=a[i].x) mm-=a[i].x,a[i].y--;
            if (mm>0)
                for (j=i+1;j<=n;j++)
                    while (mm-a[j].x>=0&&a[j].y>0)
                        mm-=a[j].x,a[j].y--;//用面值比这个小的来弥补
            if (mm>0)
                for (j=n;j>=i;j--)
                    while (a[j].y>0&&mm>0)
                        mm-=a[j].x,a[j].y--;//当连最小的面额加上目前给的零花钱都超过了C，那就只好用最小的面额
            if (mm<=0)
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
 
```


---

## 作者：NightmareAlita (赞：1)

## 简要题意

给你 $n$ 种面值的货币，其中货币中面值小的货币的面值可以整除面值大的货币的面值，给你每种面值货币的数量。每周都要给贝茜发至少 $c$ 元的工资，问最多能发多少周。

## 策略分析

首先对于面值大于 $c$ 的货币，显然我们每周给出一张就行了，没有其它办法，所以可以直接把它们的数量加在答案中。接下来是对于面值小于 $c$ 的货币，我们先对所有货币按照面值降序排序，每次选取能够选的最大的，然后再用最小的去填补剩下的那一点点价格缝隙，因为我们有小面值货币面值是大面值货币面值因数这个条件，所以最大配最小这种做法一定会产生最小的浪费，从而得到最优解。如果这一次凑不出来了，那显然是钱不够了，那么所有情况就统计完毕，输出答案即可。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define PII pair<int, int>
using namespace std;

namespace SHAWN {
    vector<PII> v;
    //v.first 代表面值，v.second 代表货币数量
    int n, c, ans; 
    bool cmp(PII x, PII y) { return x.first > y.first; }
    int work()
    {
        cin >> n >> c;
        for (int i = 1, val, b; i <= n; ++i) {
            cin >> val >> b;
            if (val >= c) { ans += b; }
            else { v.push_back({val, b}); }
        }
        sort(v.begin(), v.end(), cmp);
        while (true) {
            int tmp = c;
            for (int i = 0; i < v.size(); ++i) {
                while (tmp && v[i].second && tmp >= v[i].first) {
                    tmp -= v[i].first; 
                    --v[i].second;
                }
            }
            if (tmp > 0) {
                for (int i = v.size() - 1; i >= 0; --i) {
                    if (v[i].second && v[i].first >= tmp) {
                        tmp -= v[i].first;
                        --v[i].second;
                        break;
                    }
                }
            }
            if (tmp > 0) { break; }
            ++ans;
        }
        cout << ans << '\n';
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：cghAndy (赞：1)

让我~~不~~愉快地来水一波题解

智障の我不会贪心啊 QAQ

有一个很重要的条件 大面值是所有小面值的整数倍

首先肯定多的越少越好

然后你肯定从大到小来贪嘛

如果不能刚好满足 再拿最小的让他超过那个值

代码在blog有 ~~快来刷访问量吧~~ http://blog.csdn.net/cgh\_andy/article/details/53168600


---

## 作者：VCVCVCFop_zz (赞：0)

此题贪心，因为大的容易浪费，所以尽可能用大的，再填小的

大致思路是这样：

先一直用最大的，然后当超过需要的时候，删除一个最大的，再从最小的面额的地方往后搜，直至搜到一个大于剩余需求的面额，这就是当前的最优解。

当所有钱币用完时，ans记录的就是最优答案

TIP：还有一个小优化，超过需求的面额可以直接累加数量到答案中，应该很容易理解不再赘述，不过这个优化的常数优化效果是非常好的。。

                   
```cpp
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
#include <cmath>
using namespace std;
struct data{
    int v,k;
}e[30];
 inline bool cmp(const data& lhs,const data& rhs)
   {
         return lhs.v>rhs.v;
        }
        int kao,i,j,n,m,ans,c,v,k,cha;
int main()
{
  scanf("%d%d",&n,&c);
  m=n;
  n=0;
  ans=0;
     for (i=1;i<=m;i++)
     {
        scanf("%d%d",&v,&k);
          if (v>=c)  ans=ans+k;
          else {
                e[++n].v=v; e[n].k=k;
          }
     }
     sort(e+1,e+1+n,cmp);
    while(1)
     {
        cha=c;
          for (i=1;i<=n;i++)
             if (e[i].k>0&&cha>=e[i].v)
                 for (;e[i].k>0&&e[i].v<=cha;)
                   {
                        cha=cha-e[i].v;
                        e[i].k--;
                    }
          if (cha>0)
            for (i=n;i>0;i--)
               if (e[i].v>=cha&&e[i].k>0) 
               {
                    cha=cha-e[i].v;
                    e[i].k--;
                     break;
                }    
                if (cha>0) break;
                ans++; 
     }  
    printf("%d",ans);
return 0;
}
```

---

