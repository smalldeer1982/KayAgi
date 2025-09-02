# [USACO07JAN] Problem Solving G

## 题目描述

在较为轻松的日子里，Farmer John 的奶牛们没有任何问题。然而，如今它们却有许多问题，确切地说，它们有 $P$ 个问题，其中 $1 \leq P \leq 300$。它们已经停止提供牛奶，并像其他好公民一样找了常规工作。实际上，在一个正常的月份里，它们可以赚取 $M$ 的钱，其中 $1 \leq M \leq 1000$。

然而，它们的问题非常复杂，以至于必须雇佣顾问来解决。顾问不是免费的，但他们很有能力：顾问可以在一个月内解决任何一个问题。每个顾问要求两次付款：一次是在开始解决问题的月份开始时支付的预付款（$1 \leq \text{payment} \leq M$），另一次是在问题解决后的下个月开始时支付的尾款（$1 \leq \text{payment} \leq M$）。因此，每个月奶牛们可以用上个月赚的钱来支付顾问的费用。奶牛们是挥霍无度的，它们无法从一个月到下个月存钱；未使用的钱会浪费在牛糖果上。

由于要解决的问题之间存在依赖关系，它们必须大部分按顺序解决。例如，问题 3 必须在问题 4 之前解决，或者与问题 4 在同一个月解决。

确定解决所有奶牛问题并支付解决费用所需的月份数。



## 说明/提示

|      | 可用 | 问题  | 预付款  | 尾款   | 糖果  |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 月份 | 钱   | 解决  | 支付    | 支付   | 钱    |
| 1    | 0    | -无-  | 0       | 0      | 0     |
| 2    | 100  | 1, 2  | 40+60   | 0      | 0     |
| 3    | 100  | 3, 4  | 30+30   | 20+20  | 0     |
| 4    | 100  | -无-  | 0       | 50+50  | 0     |
| 5    | 100  | 5     | 40      | 0      | 60    |
| 6    | 100  | -无-  | 0       | 40     | 60    |（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
100 5
40 20
60 20
30 50
30 50
40 40```

### 输出

```
6```

# 题解

## 作者：whyl (赞：5)

这道题一眼一看感觉像是一个贪心

结果将贪心算法写上去之后WA掉了

只拿到了30分的部分分

很尴尬

于是考虑了动态规划

定义状态为f[i][j]为到i题下个月要花费多少钱

方程				f[i][sum2[i]-sum2[j-1]]=min(f[j-1][k]+1,f[i][sum2[i]-sum2[j-1]]);


if(j==0) 			f[i][0]=min(f[i][0],mi+1);


进行转移即可

附代码

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	int x=0,f=1;
	char p=getchar();
	while(!isdigit(p)){
		if(p=='-') f=-1;
		p=getchar();
	}
	while(isdigit(p)) x=(x<<3)+(x<<1)+(p^48),p=getchar();
	return x*f;
}

#define int long long

const int maxn=305;

int m,p,v1[maxn],v2[maxn],f[maxn][1005],sum1[maxn],mi;
int sum2[maxn];

signed main(){
	freopen("data.in","r",stdin);
	freopen("man.txt","w",stdout);
	m=read();p=read();
	for(int i=1;i<=p;i++) v1[i]=read(),v2[i]=read();
	for(int i=1;i<=p;i++) sum1[i]=sum1[i-1]+v1[i];
	for(int i=1;i<=p;i++) sum2[i]=sum2[i-1]+v2[i];
	for(int i=0;i<=p;i++) for(int j=0;j<=m;j++) f[i][j]=1e7;
	f[0][0]=0;
	for(int i=1;i<=p;i++){
		for(int j=i;j>=1;j--){
			if(sum2[i]-sum2[j-1]>m) break;
			mi=1e7;
			for(int k=0;k+sum1[i]-sum1[j-1]<=m;k++){
				f[i][sum2[i]-sum2[j-1]]=min(f[j-1][k]+1,f[i][sum2[i]-sum2[j-1]]);
				mi=min(mi,f[i][sum2[i]-sum2[j-1]]);
			}
			f[i][0]=min(f[i][0],mi+1);
		}
	}
	int ans=1e7;
	for(int i=0;i<=m;i++) ans=min(ans,f[p][i]);
	cout<<ans+2<<endl;
	return 0;
}


```


---

## 作者：ysner (赞：5)

感觉我的状态和楼下不一样啊.

我设f[i][j]表示第i个任务完成时的那个月共切j题,满足这个条件的最小天数.

然后枚举完成第几个任务(i),那个月切了几道题(j),上个月切了几道题(因为这个月要还上个月的债).接下来讨论"切题+还债"与"只还债"两种策略即可.

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
#define il inline
#define lson (now<<1)
#define rson (now<<1|1)
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
int n,p,q[350]={},h[350]={},f[350][350]={},ans;//f[i][j]表示第i个任务完成时的那个月共切j题时的最小天数
il int gi()
{
    re int x=0;
    re int t=1;
    re char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*t;
}
int main()
{
    n=gi();p=gi();
    memset(f,0x3f3f3f,sizeof(f));
    f[1][1]=1;f[0][0]=0;f[1][0]=2;//初始化第一天
    fp(i,1,p) q[i]=gi(),h[i]=gi();
    fp(i,1,p) q[i]+=q[i-1],h[i]+=h[i-1];//前缀和
    fp(i,2,p)//枚举完成第几个任务
    {
        fp(j,1,i)//枚举这个月共完成几题
            fp(k,0,i-j)//枚举还k道题的债(即上个月做k题)
            if((q[i]-q[i-j])+(h[i-j]-h[i-j-k])<=n)//还得起上个月债+切题
                f[i][j]=min(f[i][j],f[i-j][k]+1);
        fp(j,1,p)
            if(h[i]-h[i-j]<=n) f[i][0]=min(f[i][0],f[i][j]+1);//只还债
    }
    ans=f[p][0]+1;//+1是因为第一个月要赚钱，没得花
    fp(i,1,p)
        if(h[p]-h[i-p]<=n) ans=min(ans,f[p][i]+2);//还要还钱...
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：sarail (赞：4)

emmmmm思路和楼下两位大佬不太一样，不过可能比较好理解一些。。

我们用数组f[i][j]表示在第i月时付完j道题的首付时对下一个月所产生的最下影响（下个月所需支付的最小费用），于是我们可以得到dp方程：

   f[i][j+k]=min(pay（j+1,k,m-f[i][j]）) 0<=k<=p-j
   
   pay（j+1,k,m-f[i][j]）表示用m-f[i][j]块钱从j开始选k道题的对下个月产生的影响（当然前提是可以选）
   
   具体细节看代码。不过这个dp方程在时间上会慢一些，但不要在意这些细节qaq
   
   ```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+50,maxp=300+50;

int f[maxp][maxn],suma[maxp],sumb[maxp];
int m,p,x,y;

inline int pay(int beg,int l,int res){
	//用来计算剩余x块钱时，从beg开始能否支付l道题目的费用。
	//如果能，返回下对下个月的影响；如果不能，返回-1 
	res-=suma[beg+l-1]-suma[beg-1];
	if(res<0)return -1;
	int tot=sumb[beg+l-1]-sumb[beg-1];
	return tot;
}

int main(){
	cin>>m>>p;
	for(int i=1;i<=p;i++){
		scanf("%d%d",&x,&y);
		suma[i]=suma[i-1]+x;
		sumb[i]=sumb[i-1]+y;
	}
	memset(f,0x3f3f3f,sizeof(f));
	//初始化 
	for(int i=0;i<p;i++){
		int t=pay(1,i,m);
		if(t==-1) break; //如果连i道题都支付不起，i+1道题肯定也支付不起 
		f[1][i]=t;
	}
	for(int i=2;;i++){ //枚举月份 
		for(int j=0;j<p;j++) //枚举所放物品数 
			for(int k=0;j+k<=p;k++) if(f[i-1][j]<=m) { //枚举本月可放物品数 
				int t=pay(j+1,k,m-f[i-1][j]);
				if(t==-1)break;	   //同上 
				f[i][j+k]=min(t,f[i][j+k]);
				
			}
		if(f[i][p]<=m){ cout<<i+2<<endl;break; }//由于牛们在没月的月末才拿到工资，在付完最后的尾款才算结束，所以加上2 
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

**这道题目我们要用DP来解决，如果使用贪心，答案会错误的。**

**先一组数据证明贪心是错的**

**50 5**

**40 10**

**10 40**

**10 5**

**10 3**

**10 2**

**我们利用DP做出来的答案是4，而使用贪心做出来的答案却是5。**

```cpp
var m,p,i,j,x,y,z,ans:longint;
    a,b:array[0..305]of longint;
    f,f1:array[0..305]of longint;//f[i]是用来记录前i题所花费最少时间，而f1[i]则是用来判断，当f[i]最小时，我们所要花费的最少费用。
begin
  readln(m,p);
  for i:=1 to p do readln(a[i],b[i]);
  ans:=maxlongint;f[0]:=1;
  for i:=1 to p do//枚举每道题目。
    begin
      f[i]:=maxlongint div 4;//先假定时间花费为maxlongint div 4。
      x:=a[i];y:=b[i];//当前这道题目所要花费的费用。
      j:=i-1;//从i-1开始向前寻找以j为将1..i分割开来的最优值。
      while (j>=0)and(x<=m)and(y<=m) do//当前的需费用和下个月的需费用都不能超过工资的上限。
        begin
          z:=f[j]+2;//先假定我们需要用(f[j]+2)天的时间。
          if f1[j]<=m-x then z:=z-1;//如果1..j题所要花费的钱可以在今日支付掉的话，就可以省去一天时间。
          if (z<f[i])or(z=f[i])and(f1[i]>y) then//如果时间比原来的值优或是一样并且所要花费的钱比原来少的话，就替换掉。
            begin
              f[i]:=z;f1[i]:=y;//更新成优值。
            end;
          x:=x+a[j];y:=y+b[j];j:=j-1;//x加上当前所要的费用，y加上下个月所要的费用，让j循环下去。
        end;
    end;
  writeln(f[p]+1);//前p题所要的时间加上第一天(第一天没有工资，啥活也干不了，所以要加上这一天)
end.
```

---

## 作者：kkxacj (赞：3)

#### 思路

由于要求满足要求的最小月份，很自然的想到可以设一个 `dp`，我们需要的东西有三个，分别为**解决多少任务、下个月要花多少钱、用时几个月**。 

随便选两个出来做转移，记的值为剩下那一个的最优值即可，当然前提是可以转移才能设，要是设一个状态都不能转移的就没救了。

我这里设 $f_{i,j}$ 表示的是解决了 $i$ 个问题，下个月要少用 $j$ 元至少要几个月，答案显然是 $f_{P,0}$，转移我是**用已知推未知**，即枚举一个 $z$，记 $sum$ 为 $i+1$ 到 $z$ 的 $a$ 和，记 $o$ 为 $i+1$ 到 $z$ 的 $b$ 和，若 $j+sum \le M$ ，则 $f_{z,o} = \min\left(f_{z,o},f_{i,j}+1\right)$。

**注意**：$f_{i,0} = \min\left(f_{i,0},f_{i,j}+1\right)$，$j \le m$，原因是可以花一个月不执行任务只给之前没给的钱。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 310,M = 1010;
int n,m,a[N],b[N],f[N][M],ans,o,o1;//解决j个问题，上个月有z要付款至少要几个月 
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(m),read(n);
	for(int i = 1;i <= n;i++) read(a[i]),read(b[i]);
	for(int i = 0;i <= n;i++)
		for(int j = 0;j <= m;j++)
			f[i][j] = 1e9+7; 
	f[0][0] = 1;
	for(int i = 0;i <= n;i++)
		for(int j = 0;j <= m;j++)
			if(f[i][j] != 1e9+7)
			{
				o = m-j,o1 = 0;
				for(int z = i+1;z <= n;z++)
				{
					o -= a[z],o1 += b[z];
					if(o < 0 || o1 > m) break;
					f[z][o1] = min(f[z][o1],f[i][j]+1);
					f[z][0] = min(f[z][0],f[z][o1]+1);
				}
			} ans = f[n][0];
	print(ans); flush();
	return 0;
}
/*

*/
```

---

## 作者：toolong114514 (赞：0)

# P2876 [USACO07JAN] Problem Solving G 题解
## 解题思路
考虑 DP。

问题的解决是按输入顺序进行的，所以定义 $f_{i,j}$ 为对于前 $i$ 个问题，最后一个月解决了 $j$ 个问题所花费的最少月数。

我们发现，每个月要解决的任务需要付一笔钱，而上一个月被解决的任务也要在这个月付一笔钱。

想要判断花费是否合法（即小于 $m$），就需要枚举上一个月解决了多少个任务。

那么得到以下初步的状态转移方程：

$$f_{i,j}=\min_{\sum_{t=i-j+1}^{i}b_t+\sum_{t=i-j-k+1}^{i-j}a_t\le m }f_{i-j,k}+1$$

注：$a,b$ 均为原题面的含义。

但我们注意到，对于 $f_{i,0}$ 这个状态并没有得到较好的处理。

$f_{i,0}$ 的实际意义是，最后一个月没有问题被解决，只支付了前一个月的剩余费用。

显然，对 $f_{i,0}$ 的转移可以这么做：

$$f_{i,0}=\min_{j\neq0,\sum_{k=i-j+1}^{i}\le m}f_{i,j}+1$$

那么最后的答案是 $f_{n,0}+1$，因为第一个月没发工资，无法付费去解决问题。

时间复杂度约为 $O(n^3)$，可以通过本题。
## 参考代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f;
int a[305],b[305],f[305][305];
int n,m,ans=INF;
int main(){
	memset(f,0x3f,sizeof(f));
	ios::sync_with_stdio(false);
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		a[i]+=a[i-1],b[i]+=b[i-1];
	}
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=0;k<=i-j;k++){
				if(a[i]-a[i-j]+b[i-j]-b[i-j-k]<=m) f[i][j]=min(f[i][j],f[i-j][k]+1);
			}
		}
		for(int j=1;j<=i;j++){
			if(b[i]-b[i-j]<=m) f[i][0]=min(f[i][0],f[i][j]+1);
		}
	}
	cout<<f[n][0]+1;
	return 0;
}
```
[本代码可以通过洛谷评测。](https://www.luogu.com.cn/record/175836470)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/9/4.

---

