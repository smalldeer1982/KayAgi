# Order book

## 题目描述

我们来考虑某只股票的一个简化版订单簿。订单簿是一个订单（报价）列表，每个订单代表有人想以某个价格买入或卖出一单位该股票。每个订单由方向（BUY 或 SELL）和价格描述。

在任意时刻，所有 SELL 报价的价格都高于所有 BUY 报价的价格。

在本题中，任意两个曾经存在过的订单都不会有相同的价格。

最低价的 SELL 订单和最高价的 BUY 订单被称为最优报价，如下图中用黑框标出。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1028D/413fddcebb561deb1348fbeb910f4e1fa1dc550e.png)

如图所示，某人以价格 $12$ 卖出产品，这是最优的 SELL 报价，因为另外两个 SELL 报价价格更高。最优的 BUY 报价价格为 $10$。

在这个订单簿中有两种可能的操作：

1. 有人以某个方向和价格添加一个新订单。
2. 有人以最优的 SELL 或 BUY 报价成交（达成交易）。只能接受最优的 SELL 或 BUY 报价（即以最优价格成交），不能以更差的价格成交。成交后，该订单会从订单簿中永久移除。

只允许添加价格低于当前最优 SELL 报价的 BUY 订单（如果你想以更高的价格买入，则应直接接受最优 SELL 报价而不是添加新订单）。同理，也不能添加价格小于等于当前最优 BUY 报价的 SELL 订单。例如，如果已经有 "BUY $20$" 或 "BUY $25$" 的订单，则不能再添加 "SELL $20$" 的订单——此时应直接接受最优 BUY 报价。

你有一份损坏的订单簿日志（初始时订单簿为空）。每个操作有两种类型：

1. "ADD $p$" 表示以价格 $p$ 添加一个新订单，但方向未知。该订单不能与当前订单簿中尚未移除的订单矛盾。
2. "ACCEPT $p$" 表示以价格 $p$ 接受一个已存在的最优报价，但方向未知。

所有操作的方向信息都丢失了。日志中的信息并不总能完全确定这些方向。请你计算有多少种方式可以为所有 ADD 操作正确恢复方向，使得在任意时刻所有描述的条件都被满足。由于答案可能很大，请输出对 $10^9+7$ 取模的结果。如果无法正确恢复方向，则输出 $0$。

## 说明/提示

在第一个样例中，每个订单都可以是 BUY 或 SELL。

在第二个样例中，价格为 $1$ 的订单必须是 BUY，价格为 $3$ 的订单必须是 SELL。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
ADD 1
ACCEPT 1
ADD 2
ACCEPT 2
ADD 3
ACCEPT 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
ADD 1
ADD 2
ADD 3
ACCEPT 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
ADD 1
ADD 2
ADD 3
ADD 4
ADD 5
ACCEPT 3
ACCEPT 5
```

### 输出

```
0
```

# 题解

## 作者：木易、 (赞：3)

本题题意很好理解，维护两个集合，完成插入和删除两种操作，那局势就很明朗了。（倘若本篇题解不好理解，建议全部看完后回来理解不懂的）。

本蒟蒻的做法是维护一个 ```set```，和两个指针 left,right。left 代表的是能作为 $A$ 的最大值的元素中最小的， right 代表的是能作为 $B$ 的最小值的元素中最大的（在某种意义上，left 已经被放到 $A$ 里，right 已经被放到 $B$ 里）。具体做法为不管三七一十一，把读入的元素插入集合内，然后规定一个缓冲区，里面的数满足比 left 大且比 right 小，也就是说，它们既可以被放到A里，也可以被放到 $B$ 里。

下面以一组数据对我的操作进行模拟。

```
10

ADD 0

ADD 3

ADD 5

ACCEPT 3

ADD 7

ADD 4

ADD 2

ACCEPT 2

ADD 11

ADD 1

```

输出： ```8``` 

对于这组数据，首先先在集合中插入一个极大值和一个极小值作为当前的 left 和right，防止下面删除数后 $A,B$ 两个集合有一个是空的，即找不到 left 和 right，下面比较判断被删除元素是否在 left 和 right 之间的时候会判断错误。（例：本题样例 $1$，若未插入极值，则插入 $1$，删除 $1$ 后 left 和 right 取不到值，再插入 $2$，删除 $2$ 时就会判断 $2$ 不在 left 和 right 之间）定义 ans 初始值为 $1$，毕竟除了不成立的那种可能外，至少会有一种满足要求。

然后插入 ```0 3 5``` 三个元素到集合中，此时 left 和 right 之间有 ```0 3 5 ``` 三个元素，三者有以下几种情况：
- 1. ```0 3 5``` 在  $A$ 中；
- 2. ```0 3``` 在 $A$ 中，```5``` 在 $B$ 中；
- 3. ```0``` 在 $A$ 中，```3 5``` 在 $B$ 中；
- 4. ```0 3 5``` 在 $B$ 中。

那么下一步的删除 ```3``` 就会将情况确定为 ```0``` 在 $A$ 中而 ```5``` 在 $B$ 中，则 ```0``` 为新的 left，```5``` 为新的 right。要注意的是，```3``` 的位置没有被确定，而根据题意，```3``` 可以作为 $A$ 的最大值或 $B$ 的最小值，两种情况，那作为方案数的 $ans$ 自然就乘 ```2```。可将其一般化为如果删除操作成立，则$ans=ans\times 2$。

然后是插入 ```7``` ，注意此时 $A$ 的最大值和 $B$ 的最小值是范围确定的，又发现```7``` 大于 ```5```，也就是 ```7``` 比 $B$ 的最小值要大，那自然就在 $B$ 中。

而对于后面两个操作，插入 ```4``` 和 ```2```，```4``` 和 ```2``` 就在 left 和 right 之间了。```4``` 和 ```2``` 的位置目前还不能确定，也就是既可能在 $A$ 中也可能在 $B$ 中。

对于下一个操作，删除 ```2```，就把目前在缓冲区内的元素规定了位置，也就是 ```4``` 为新的 right ，而 left 不变，仍然是 ```0``` 。同样的，发现 ```2``` 的位置不确定，有在 $A$ 中和在 $B$ 中两种可能性，则$ans=ans\times 2$。

后面的插入 ```11``` 操作与插入 ```7``` 是相似的，一定在 $B$ 中。

最后一步插入 ```1``` 与插入 ```4``` 和 ```2``` 是相似的，可能在 $A$ 中也可能在 $B$ 中。

那么所有操作结束，仍有一个元素 ```1``` 可以被放在 $A$ 或 $B$ 中，两种可能性，$ans=ans\times 2$。可将其一般化为如果操作结束，仍有 $cnt$ 个元素在缓冲区内，则$ans=ans\times (cnt+1)$。

下面是我滴代码（含注释）。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#define int long long
using namespace std;
const int mod=1e9+7;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int n;
set <int> sss;
int cnt=1;
int ans=1;
signed main()
{
	int left=-2e9-7,right=2e9+7;//left为amax的最小值，right为bmin的最大值 
	sss.insert(left),sss.insert(right);//防止插入的x被全删完以后，集合中没有元素，会输出0 
	n=read();
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		int x=read();
		if(s=="ACCEPT")
		{
			cnt=1;
			if(x<left||x>right)//小于a的max或大于b的min，无法删除 
			{
				cout<<0;
				return 0;
			}
			if(x>left&&x<right)//如果x在集合中，且在集合sss的left和right之间，即不是left和right，可以是新的amax或新的bmin 
			{
				ans=(ans*2)%mod;//x可以插入在A或B中，故此处乘2 
			}
			set <int> ::iterator www;
			www=sss.find(x);//www为x在集合sss中的位置 
			www--;
			left=*(www);//此时的left应被更换为www左侧的第一个元素 
			www++,www++;
			right=*(www);//此时的right应被更换为www右侧的第一个元素 
			www--;
			sss.erase(www);
			//cout<<left<<" "<<right<<endl;
		}
		if(s=="ADD")
		{
			sss.insert(x);
			if(x>left&&x<right)//只有被插入到left和right之间的才可能在A或B中，若不在，则一定在A、B其一里 
			{
				cnt++;
			}
		}
	}
	ans=(ans*cnt)%mod;//最后一个ACCEPT后的ADD，可按顺序随意插入A或B，故此处乘cnt 
	cout<<ans;
	return 0;
}
```


---

## 作者：Hoks (赞：1)

## 前言
duel 到的好题，没想到还有老师的题解。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
看看题面，感觉 $1$ 操作而言，把哪个数放哪一组很难办？

那就先不管，反正 $1$ 操作间互不影响，我等到最后再一并分组即可。

那么考虑 $2$ 操作是如何影响 $1$ 操作的。

不难发现 $2$ 操作其实就是把所有数，以删去的数为基准，分成两堆。

因为删去的数肯定是小堆最大或者大堆最小。

也就是比他小的数全在小堆，比他大的数全在大堆，在这个时候再决定每个数在那一堆即可。

那么我们便可以确定出当前的小堆最大和大堆最小，如果新删除的数不在这个范围为内就肯定寄了。

当然也有可能存在情况最后中间插入了一堆数没有删除，这个时候的方案数就是 $x+1$，其中 $x$ 表示中间有多少个数。

因为分组可以分为：$(0,x),(1,x-1),\dots,(x,0)$。总计 $x+1$ 种。

对于删除的数，如果他未被分组，那么有可能在小堆里，有可能在大堆里，额外定义一个变量乘二记录即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,ans=1;char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='e'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='*'||c=='/'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read();int mx=-INF,mn=INF,ss=0;set<int>a;a.insert(INF),a.insert(-INF);
    for(int i=1,x,l;i<=n;i++)
    {
        l=0;rd(s,l);x=read();
        if(s[2]=='D')
        {
            if(x>=mx&&x<=mn) ss++;
            a.insert(x);
        }
        else
        {
            ss=0;if(x>mn||x<mx) return put("0\n");
            if(x!=mx&&x!=mn) ans=ans*2%mod;
            mn=*(++a.lower_bound(x));
            mx=*(--a.lower_bound(x));
            a.erase(x);
        }
    }print(ans*(ss+1)%mod);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
小清新思维题，可以当做一个集合的练习题。

话说这个题的数据范围好奇怪啊。
## 分析。
集合的基本性质就不再赘述。由集合的性质，我们发现因为所有的元素都不相等，所以如果我们删除边界的话只有一种选择。

这个题目显然是让我们建立两个集合，其中一个集合只维护较大值，另一个只维护较小值，同时要求维护较大值的那个集合中的元素要比维护较小值的那个集合中的元素小。

显然我们不能说是一个操作就是直接进行，因为操作 $2$ 的要求过于苛刻了，但是我们发现，其实这个操作 $2$ 我们不妨看做是一个分割集合的操作。具体来说，就是在最后一个操作 $2$ 结束之前每一个进行的操作 $1$ 其实都是固定的，严格来说，每次的操作 $1$ 其实相当于加到一个集合中，至于在哪一个集合中我们并不关心。这样我们可以将最后一次操作 $2$ 之前的操作 $1$ 看做每次往一个大集合中填上这个数。如果出现操作 $2$ 我们再划分集合成为两个。此时我们前面的操作 $1$ 中的数 $x$ 事实上必然在大集合中的某一个位置，而此时要删除的数也必然在大集合中，那根据删除的要求，我们不难看出，一旦进行操作 $2$ 则比 $x$ 小的数就等价于到了一个集合中，而比 $x$ 大的数则到了另一个集合中，那么这其实就是表明，两个集合 $A$ 和 $B$ 中的最大值和最小值也就确定下来了。

同理，我们接下去的操作 $1$ 就是填数，操作 $2$ 就是进行合并两个集合然后再进行划分，重新更新最大值和最小值，如果不是无解的情况，或者 $x$ 恰好是最大值和最小值的边界，那么直接考虑在哪一个集合中删除即可。因为在进行最后一次操作 $2$ 时，前面的操作 $1$ 事实上没有明确的划分，所以乘上那些操作 $1$ 的选择即可。

代码如下，仅供参考：
```
#include<iostream>
#include<set>
#define mod 1000000007
#define inf 0x3f3f3f3f3f3f
using namespace std;
long long n,x;
long long maxx=-inf,minn=inf,sum,ans=1;
char opt[10];
set<long long> big_s;
set<long long>::iterator it;
int main(){
    big_s.insert(inf);
	big_s.insert(-inf);
    it=big_s.begin();
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>opt>>x;
        if(opt[1]=='D'){
            if(x>=maxx&&x<=minn){
			    sum++;
			}
            big_s.insert(x);    
        }
        else{
            sum=0;//注意清零。 
            if(x>minn||x<maxx){
                cout<<"0\n";
                return 0;
            }
            else if(x!=maxx&&x!=minn){
			    ans=ans*2%mod;
			}//这就是本文开头提到的边界特判。 
            it=big_s.lower_bound(x);
            it++;
			minn=*it;
            it--;
            it--;
			maxx=*it;
            it++;
			big_s.erase(it);
        }
    }
    cout<<ans*(sum+1)%mod<<"\n";
	return 0;    
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：MujinH (赞：0)

看到题目，我们首先考虑模拟出一个表，使得元素是单调的，就像题面中给出的表一样，不管这个元素是 SELL 还是 BUY , 一定满足这个性质。

那么接下来我们讨论单个元素的类型，我们把 BUY 与 SELL 之间的分界线叫做**缓冲区**，对于 ACCEPT 操作，可以确定一些元素的类型。但有些元素从始至终都无法确定，这便会产生两种类型都能满足的情况，那么总方案数就翻 $1$ 倍。

我们需要维护的就是缓冲区，用两个变量 $l$ 与 $r$ 表示。

出现 ACCEPT 操作，我们就更新 $l$ 与 $r$，分别为删除元素的左边第一个元素和右边第一个元素。

还需要特判最后一次 ACCEPT 操作后出现了多少次 ADD 操作，因为这些 ADD 是没有约束的，可以在保证元素顺序的情况下对答案产生额外贡献。

最后考虑如何判 $0$，只要题目中出现删除 $l$ 与 $r$ 区间之外的元素，那么出现矛盾，直接判掉。

### Code

```cpp
#include<iostream>
#include<cstdio>
#include<set>

using namespace std;
using ll=long long;
const int N=363304+50,mod=1e9+7;

int n;
ll l=-4e10,r=4e10,cnt=1,ans=1;
//cnt表示最后一次ACCEPT操作后出现了多少次ADD操作
set<ll> s;

int main(){
	cin.tie(0),cout.tie(0);
	cin>>n;
	s.insert(l);s.insert(r);//防止迭代器越界
	for(int i=1;i<=n;i++){
		string opt;ll p;
		cin>>opt>>p;
		if(opt=="ADD"){
			s.insert(p);
			if(l<p&&p<r) cnt++;
		}else{
			if(l<=p&&p<=r){//特别注意,虽然题目中保证不会出现重复元素,但查找是能取等的
				if(l<p&&p<r) ans=(ans*2)%mod;//特别判断如果是等于l或r是不能对答案产生贡献的
				cnt=1;
				set<ll>::iterator it=s.find(p);
				it--;l=*it;//左边的元素为新的l
				it++;it++;r=*it;//右边的元素为新的r
				it--;s.erase(it);//从集合中删除元素p
			}else{
				cout<<"0\n";
				return 0;
			}
		}
	}
	cout<<ans%mod*cnt%mod;
	return 0;
}
```


---

