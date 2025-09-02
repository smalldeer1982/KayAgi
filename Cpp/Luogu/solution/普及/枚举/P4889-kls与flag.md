# kls与flag

## 题目背景

kls毒奶非常厉害。

## 题目描述

有$n$个OI选手，每个人插了一个flag。有一天因为某种原因，flag都被触发了，所以地上有一排$n$根竹竿，竹竿的间距均为一个单位长度，高度在$1\sim m$之间。

kls看到这些竹竿，感觉不好看，于是准备把它们全部放倒。

在这之前，kls想到了一个数学问题。每根竹竿可以往左倒或者往右倒。如果两根竹竿在选择方向放倒之后，它们的顶端可以重合，那么称它们是优秀的。现在kls想要知道，有多少对竹竿是优秀的。

## 说明/提示

### 样例解释

![法法](https://cdn.luogu.com.cn/upload/pic/25795.png)

- 1号和2号向左倒可以顶端重合
- 4号和5号向右倒可以顶端重合
- 1号向右，5号向左可以顶端重合

### 数据范围

对于30%的数据，满足$n\le 2000$，$m\le 5000$；

对于60%的数据，满足$n\le 200000$，$m\le 500000$；

对于100%的数据，满足$n \le 200000$，$m \le 10^9$。

## 样例 #1

### 输入

```
5 5
2 3 3 3 2```

### 输出

```
3```

# 题解

## 作者：Viston (赞：47)

运用了不用map的方法   
即把每个杆子可能落到的位置存进数组   
运用sort排序一遍    
$O(N)$扫一遍即可    
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c[200002],d[400002],e=0,i,j,k,l;
int main(){
    ios::sync_with_stdio(false);
    cin>>a>>b;            //O(NlogN),放心用cin
    for(i=1;i<=a;i++){
        cin>>c[i];e+=2;      
        d[e-1]=i-c[i];d[e]=i+c[i];   //入数组
    }
    sort(d+1,d+e+1);         //排序
    for(i=1;i<=2*a;i++){  
        if(d[i]!=d[i-1])       //如果不在这个点了
            k=0;
        else k++,l+=k;         //如果在，就加一下
    }
    cout<<l;                 //输出最后答案
}
```

---

## 作者：醉梦未苏 (赞：27)

#### 洛谷月赛加赛的题，怀着敬畏之心奉上题解一篇题解

思路大概如下(使用STL的map)
- 定义函数$f(x)$,代表$1+2+...+x-1$的和

---
1. 输入竹竿高度$k$  ,$map[k]++$,所以$map[k]$表示k处有几根竹竿顶重合
2. 遍历map,对于$ans=ans+f(i\text{的值})$

---

对于$f(x)$,不难理解,一个点有x个竿重合,两两配对,显然是$(1+2+...+x-1)$次

map用来统计哪些点被几根竹竿覆盖,(如数据较小可以用数组)

---
话不多说，上代码!

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m; //注意开long long,否则30分
map<long long,long long> mmp; //定义map
long long val(long long x) //f(x)
{
	if(x<2) return 0; //竹竿不能盖在一起
	return x*(x-1)/2; //等差数列公式
}
int main()
{
	cin>>n>>m; //输入
	for(long long i=1;i<=n;i++)
	{
		long long k;
		scanf("%lld",&k);
		mmp[k+i]++;	//向右倒竹竿顶落在的点
		mmp[i-k]++;	//向左倒竹竿顶落在的点
	}
	long long ans=0; //计数器
    
    //遍历map
	for(map<long long,long long>::iterator  i=mmp.begin();i!=mmp.end();i++) 
	{
    	//i->second表示该点有（i->second）个竿重合
	    ans+=val(i->second);//统计
	}
	cout<<ans;//输出
	return 0;
}


```

第一次给月赛写题解,求过,求赞

---

## 作者：Fuyuki (赞：9)

map模板练习题，唯一要注意的是判断map的键值是否存在，还有就是题目中的那个m完全没用。
```cpp
#include<iostream>
#include<map>
using namespace std;
int i,n,m;
long long ans;
map<int,int>a;
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>m;
		if(a.count(i-m)==0)a[i-m]=0;//没有的话创造一个点
		if(a.count(i+m)==0)a[i+m]=0;
		ans+=a[i-m]+a[i+m],a[i-m]++,a[i+m]++;//和已有节点配对
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：空の軌跡 (赞：4)



~~好吧，我又来写题解了，其实这道题很水，尽管是个绿题~~

如有不正，请通知本人予以更正
# 变量说明:

vector <int> eve  表示求出的左右端点，其实可以不用vector，我就是图个方便~~
  
sum 表示有多少个数字相等

ans 表示答案个数

b 为了一个机动变量，随时调用，很多用处，也可以使用多个变量来代替 b ,影响不大

# 思路：

求有多少个杆子向左或右倒后顶端的位置有多少对相等，所以我们把顶端位置弄出来，排序后挨个算有多少对就行


1.首先把每个杆子的向左或右倒的位置计算出来并压入数组

```
	for(int i=1;i<=a;i++)	   //题目给的最高高度我直接无视了，没啥用
    {
        cin>>b;				
        eve.push_back(i-b);    //这两行就是求出左右端点并压入数组
        eve.push_back(i+b);
    }
```

2.将求出的位置排序，这样才能将该点的杆的个数计算出来

3.把数组遍历一遍，从中使用组合数公式求出个数并增加如ans并持续遍历

（可以上网百度一下组合数的公式，变形后就是  sum*(sum-1)/2  了）

所以我们现在的工作就是求出有多少个相等的数字并套入公式计算
```


sum=1 是因为eve[i]与前方不相等并计算，则上一段计算完了，
而现在只有一个数也就是eve[i]在下一段了


```

我这里给下代码


```

	b=eve.size();		   	 //把空间求出来，这样也许比较快
	for(int i=1;i<b;i++)		 //从eve[1]开始比较，eve[0]无需与前一个进行比较，直接作为本段的开始
    {
        if(eve[i]==eve[i-1]) 	//如果与上一个相等就sum++并判断下一个位置eve[i+1]
        {
            sum++;continue;	  //sum 计算本段有多少数字相等，当不等时则计算并重置，并开始表示下一段
        }
        ans+=(sum*(sum-1)/2);	//否则计算这一段的组合数并加入ans
        sum=1;				   //sum设为1 是因为eve[i]为新的一段的第一个
    }
    ans+=(sum*(sum-1)/2);		//遍历完后可能还剩余一段未计算，进行计算
  
   ```

4.long long 保平安

------------


# 代码

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<long long>eve;
int main()
{
    long long a,b,sum=1,ans=0;
    cin>>a>>b;				    
    for(int i=1;i<=a;i++)
    {
        cin>>b;
        eve.push_back(i-b);
        eve.push_back(i+b);
    }
    sort(eve.begin(),eve.end());
    b=eve.size();
    for(int i=1;i<b;i++)
    {
        if(eve[i]==eve[i-1])
        {
            sum++;continue;
        }
        ans+=(sum*(sum-1)/2);
        sum=1;
    }
    ans+=(sum*(sum-1)/2);
    cout<<ans;
}
```

---

## 作者：Ricardo_Y_Li (赞：3)

思路很简单，开一个map，用来记录对于一个点$x$，有多少竹竿可以倒在这里

跟楼下几个用map的不同的是，每次输入一个高度将能到的点预处理完之后，直接重新扫一遍每个竹竿向左或向右倒到达的点加进答案里，但是要注意的是，每一次添加答案要减去$1$，因为会把自己算进去，另外最后的答案要除以$2$，因为在添加答案的时候每一对竹竿算了两遍

注意开long long 

~~好像map支持负数下标，但我还是没有这么做~~

代码
```cpp
#include<cstdio>
#include<map>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
using namespace std;

const int N=2e5+10;
const int M=1e9+10;
typedef long long LL;
map<LL,LL>cnt;
LL n,m,ans=0;
int h[N];

inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0' || c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9' && c>='0'){x=(x<<3)+(x<<1)+(int)(c-'0');c=getchar();}
	return x*f;
}

int main(){
	n=read(),m=read();
	rep(i,1,n){
		h[i]=read();
		cnt[i-1+m-h[i]]++;
		cnt[i-1+m+h[i]]++;
	}
	rep(i,1,n)
		ans+=cnt[i-1+m-h[i]]-1+cnt[i-1+m+h[i]]-1;
	ans>>=1;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：贞白铁战逸 (赞：3)

**相比于其他大佬，我用的是多重集合multiset（是不是很惊讶。。。）**

**我的月赛爆的极惨， 回头重新做反而更有感觉。**

**这题其实就是TLE你的， 朴素算法很好想。**

```
#include <iostream>
#include <cstdio>
using namespace std;
long long n, m, a[200005], ans = 0;
int main()
{
    int i, j, k, l;
    scanf("%lld %lld", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j < i; j++)
        {
            if (a[i] - a[j] == i - j || a[i] - a[j] == j - i || a[i] + a[j] == i - j) ans++;
        }
    }
    cout << ans;
}
```
**这是30分。。。**

**如何优化呢？**

**对于每个元素x， 将x - i存入一个集合， x + i 存入另一个集合。**

**只需算出 一集合中一元素与另一集合一元素互为相反数的对数 +** **各集合重复的数的两两组合种数（有点拗口。。。）**

**以下是代码（个人觉得还是和大佬们差得蛮远）**

```
#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
long long n, m, ans = 0;
multiset <long long> q, w;
multiset <long long> :: iterator ite;
int main()
{
    long long i, j, x, y, s1, s2;
    scanf("%lld %lld", &n, &m);
    for (i = 1; i <= n; i++)
    {
        scanf("%lld", &x);
        q.insert(x - i);
        w.insert(x + i);
    }
    for (ite = q.begin(); ite != q.end(); ite++)
    {
        j = w.count(-*ite);//计算相反数对数 
        ans += j;//累加 
    }
    while(!q.empty() || !w.empty())
    {
        if (!q.empty())
        {
            x = *q.begin();
            s1 = q.count(x);
            if (s1 > 1) ans += ((s1 - 1) * s1) >> 1;//n个相同的数取两个有n * （n - 1） / 2 种方案 
            q.erase(x);
        }
        if (!w.empty())
        {
            y = *w.begin();
            s2 = w.count(y);
            if (s2 > 1) ans += ((s2 - 1) * s2) >> 1;//同上 
            w.erase(y);
        }
    }
    cout << ans;//愉快输出 
}
```
**谢谢大家！**

---

## 作者：Owen_codeisking (赞：3)

# [更好的阅读体验戳这里](https://www.cnblogs.com/owencodeisking/p/9693337.html)

这道题还挺搞笑的，$map$常数贼大还是把它水过了。

可以发现这道题求的是 $(j>i)j-i=h_i+h_j,j-i=|h_i-h_j|$的对数。

那么显然，因为高度大于$0$，所以一个数对不可能同时满足两条式子，所以可以分开算。

那么进行分类讨论：

- $(1)$ $j-i=h_i+h_j$,等价于$h_i+i=j-h_j$,那么开一个$map$,存下所有值的个数，每次都更新答案

- $(2)$ $j-i=h_j-h_i$,等价于$j-h_j=i-h_i$,同$(1)$

- $(3)$ $j-i=h_i-h_j$,等价于$h_i+i=h_j+j$,同$(1)$

那么如何保证$j>i$呢？倒序不就好了吗！

具体详见代码。

$Code\ Below:$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=200000+10;
int n,m,a[maxn];
long long ans;
map<int,int> mp;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	mp[n-a[n]]=1;
	for(int i=n-1;i>=1;i--){//情况1
		ans+=(long long)mp[a[i]+i];
		mp[i-a[i]]++;
	}
	mp.clear();
	mp[a[n]-n]=1;
	for(int i=n-1;i>=1;i--){//情况2
		ans+=(long long)mp[a[i]-i];
		mp[a[i]-i]++;
	}
	mp.clear();
	mp[a[n]+n]=1;
	for(int i=n-1;i>=1;i--){//情况3
		ans+=(long long)mp[a[i]+i];
		mp[a[i]+i]++;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：gtsdguo (赞：2)

（**如果你~~不会~~不想用任何高级数据结构·····**）


看了两位MAP**julao**的题解；

本蒟蒻表示；

真的不需要map；

 **思路：**
 
 每根竹竿可以向左倒也可以向右倒，要求有多少对竹竿倒下后顶端可以重合；
 
 考虑维护每一个点可以有几根竹竿落下；
 
 看了一眼m：

**1e9**；

很好；

我们只要开到（1e9+2e5）*2就好了；

继续观察；

我们发现；

只有200000根竹竿；

所以最多只有400000个点可以有竹竿落下；

而我们开了（1e9+2e5）*2；

怎么办；

怎么办；

hash？；

map？；

本蒟蒻并不会。。。。。；

**所以**

我们这样做：

建立一个大小为4e5的数组；

记录竹竿可以落在哪儿；

显然；

若竹竿的位置为i，高度为h；

那么它就可以落在**i+h**和**i-h**；

所以；

（**~~前方高能~~**）

我们将每个i-h和i+h记录之后sort一遍；

看每个数有几个；

答案就加上（n-1）+（n-2）+···+1；

所以；

没有hash 没# 有map 没有线段树；
 没有图 没有堆 **没有 任何高级数据结构**；

我们 通过了这道题；

（**~~记得开longlong 我是不会告诉你们我是因为没开longlong才95分的~~**）；

（**~~不许嘲笑我的代码~~**）；

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m,cu,uu,a[400010],b[400010];
int main()
{
	cin>>n>>m;
	for(long long i=1;i<=n;i++)
	{
		cin>>uu;
		a[++cu]=i+uu;
		a[++cu]=i-uu;
	}
	for(long long  i=2;i<=400004;i++)	b[i]=i-1+b[i-1];
	sort(a+1,a+n*2+1);
	n*=2;
	long long ans1=1,ans=0;
	for(long long i=2;i<=n;i++)
	{
		if(a[i]==a[i-1])
		  ans1+=1;
		if(a[i]!=a[i-1]||i==n) 
		{
			ans+=b[ans1];
			ans1=1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```






---

## 作者：453xzz (赞：2)

####  P党的第二篇题解，~~Pascal的回光返照~~
#### 作为蒟蒻，不会写高端的代码。而Pascal又没有map的库（呜呜呜）
#### 所以，只能用最原始的方法做


但是不是爆搜这种原始方法：复杂度为n2(必爆)
***
### 思想：
  
####   可以把所有杆向左倒和向右倒到达的点用一个数组储存起来，排序，然后用O（n）过一遍，找出倒下后相同的点

***
注意：longint会爆！要用int64（也就是c++的longlong）
### 上代码！
```pascal
var
  a:array[0..400004] of int64;
  n,m,i,tem,tp,ans,x:int64;

procedure qp(p,q:longint);// 排序
var mid,l,r,t:longint;
begin
  l:=p;
  r:=q;
  mid:=a[(l+r) div 2];
  repeat 
    while a[l]<mid do inc(l);
    while a[r]>mid do dec(r);
    if l<=r then begin
      t:=a[l];
      a[l]:=a[r];
      a[r]:=t;
      inc(l);
      dec(r);
    end;
  until l>r;
  if l<q then qp(l,q);
  if r>p then qp(p,r);
end;

begin
  readln(n,m);
  for i:=1 to n do begin
    read(x);
    a[i*2-1]:=i-x;
    a[i*2]:=i+x;
  end;//记录倒下后点的位置
  qp(1,n*2);
  tem:=1;ans:=0;
  while tem<n*2 do begin//寻找倒下后位置相同的点
    tp:=0;
    while a[tem+tp]=a[tem+tp+1] do inc(tp);
    if tp>0 then ans:=ans+tp*(tp+1)div 2;
    tem:=tem+tp+1;
  end;
  writeln(ans);
end.
```
### 纪念~~我因学业繁忙而错过的~~洛谷月赛

---

## 作者：论之铭 (赞：2)

其实这道题按照题意模拟即可  
考虑以 $count[i]$ 记录向左或向右放倒后端点在 $i$ 处的点的个数  
考虑到 $i$ 可能出现负数，并且 $m$ 的范围是 $1e9$ 不便于用数组储存，所以对 $i$ 进行离散化后再储存  
现在我们统计好了在每一个点处的端点个数，那么就可以$O(1)$计算出在该点处端点重合的旗杆对数  
那么最终的 $ans =\sum_{i=1}^{n} \sum_{j=1}^{count[i]-1}j = \sum_{i=1}^{n} \frac{count[i]*count[i-1]}{2}$  

AC代码如下
```cpp
#include <bits/stdc++.h>

namespace IO {
    int read() {
        register char c = getchar(); register int x = 0; register bool flag = 0;
        while(c < '0' || c > '9') (c == '-') && (flag = 1), c = getchar();
        while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
        (flag) && (x = -x);
        return x;
    }

    void write(long long x) {
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0'); 
    }

    void file() {
        #ifndef ONLINE_JUDGE
        freopen("testdata.in", "r", stdin);
        //freopen("testdata1.out", "w", stdout);
        #endif
    }
} using namespace IO;

const int N = 400009;
int n, m, *rnk;
int num[N];
long long count[N];
long long ans;

int *Dis(int *num,int n)
{
    int *tmp = new int [n+10];
    for (int i = 0; i < n; i++) tmp[i] = num[i];
    std::sort(num, num + n);
    m = std::unique(num, num + n) - num;
    for (int i = 0; i < n; i++) tmp[i] = std::lower_bound(num, num + m, tmp[i]) - num + 1;
    return tmp;
}

int main() {
    n = read(), read();
    for (int i = 0; i < n; i++) {
        int x = read();
        num[i << 1] = i - x + 1, num[i << 1 | 1]= i + x + 1;
    }
    rnk = Dis(num, n << 1);
    for (int i = 0; i < n << 1; i++) count[rnk[i]]++;
    for (int i = 1; i <= m; i++) ans += count[i] * (count[i] - 1) >> 1;
    write(ans);
    delete(rnk);
    return 0;
}
```

~~这年头没个sigma都不好意思写题解了~~

---

## 作者：liulif (赞：2)

# 其实这就是个模拟题

设每根杆子的初始坐标为$i$,高度为$a_i$,则每根杆子向左右分别放倒后顶点的坐标$l_i=i-a_i,r_i=i+a_i$，由于每根杆子向左右放倒后的顶点坐标是不同的，那么两个相同的顶点坐标一定是由两根不同的杆子形成的，即一对相同的顶点坐标对应一对优秀的杆子。因此可以把$l_i$和$r_i$并为一个数组，排序后累加答案。

下面上代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=200000+10;
int n,m,t,a[maxn],s[maxn*2];
long long cnt,ans;
inline void read(int &x)	//没有判负的快读
{
    x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-48;ch=getchar();} 
} 
int main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++)
    {
        read(a[i]);
        s[i]=i-a[i];s[n+i]=i+a[i];
    }
    sort(s+1,s+2*n+1);	//排序后相同的坐标会变为相邻元素
    cnt=1; 	
    for(int i=2;i<=2*n;i++)
    	if(s[i]==s[i-1]) cnt++;	//cnt为当前相同坐标的个数
    	else 
    	{
            ans+=(cnt-1)*cnt/2;	//遇到不相同的坐标就累加答案，cnt个点贡献了(cnt-1)*cnt/2对优秀flag
            cnt=1;	//重置为1
        }
    ans+=(cnt-1)*cnt/2;	//注意还要加上最后一组
    printf("%lld",ans);
}
```


---

## 作者：人殇物已非 (赞：1)

看到这个题被恶意评分评到了**提高+/省选-**后，有点愤愤不平，明明是**普及-**的题，被一群人不知道怀着怎么样的心态搞这么高难度。

所以我来发一篇代码量极短也好理解的题解为这个题正名。

首先，我们可以很简单地想到，假如一个点可以被某个竹竿的顶端覆盖，那么我们把这个点记下，后面如果再能被某个竹竿的顶端覆盖，那么答案就加一。

怎么实现呢？可以用$Hash$或$map$记一下当前这个点被覆盖了几次（根据值域，若用桶显然爆空间），看了一眼数据范围，$2e5$，有点小呢，那就直接$map$就好了。

$code$:
```
#include<bits/stdc++.h>
using namespace std;
map<int,int> ma;
int main(){
	int n,m;
	cin>>n>>m;
	long long ans=0;//很明显只有ans需要开long long，其他的最大只有1e9在int以内
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		ans+=ma[i-x]+ma[i+x];//当前这根向左倒能找到几对，向右能找到几对。统计到答案里。
		ma[i-x]++,ma[i+x]++;//向左倒的位置的覆盖数++，向右倒的位置的覆盖数++；
	} 
	cout<<ans;//温馨提示：若是用printf别忘了唯一的这一个lld；
	return 0;
}
```

有人说需要排列组合一下因为答案是有几对，（？？？）完全不需要啊！$map[i]$是有几根竹竿在可以覆盖当前位置，那么每次新的一根与之配对，$map[i]$不就正好是能配对当前这一根的个数嘛。而且由于是“对数”，所以谁在前谁在后完全无所谓，找到了一根就找到了一对。

---

## 作者：Cutest_Junior (赞：1)

## 题解 P4889 【kls与flag】

### 题意

+ $n$ 个竹竿；
+ 每个竹竿可以向左或向右倒，求有多少对竹竿可以满足竹竿倒下后顶端重合；
+ $n\le200005$。

### 做法

1. 用一个 map 数组保存 坐标->倒下后顶端在这个坐标的竹竿的个数；
2. 统计重合的个数；
3. 注意用 long long。

细节请看代码。

### 代码

```cpp
# include <iostream>
# include <map>

using namespace std ;

# define int long long

map < int , int > ma ; // 坐标->倒下后顶端在这个坐标的竹竿的个数

signed main ( )
{
    int n , m ;
    cin >> n >> m ;
    
    int ans = 0 ;
    
    for ( int i = 1 ; i <= n ; ++ i )
    {
        int x ;
        cin >> x ;
        
        ans += ma [ i + x ] + ma [ i - x ] ; // 统计重合的个数
        
        ma [ i + x ] += 1 ; // 改变个数
        ma [ i - x ] += 1 ;
    }
    
    cout << ans ;
}
```

---

## 作者：Drinkkk (赞：1)

[题面](https://www.luogu.org/problemnew/show/P4889) 。

最近比较心累......很少写题解，刚好看到洛谷有月赛加赛就来看了下......于是就有了这篇题解。

去看了一下@wthhhhhhh 的题解中的60分代码，其中有一段话是这样的：

“O(m+n)的RE算法

听说用stl中的map就能过，但本蒟蒻表示不会……

但是m<10^9,数组开不了辣么大……

当然了这个程序里有许多的空间浪费，很多数组都是0”

于是我们就可以想到**离散化**（蒟蒻我太菜了不会用map），然后就有了下面的这段代码（表示这是第一次同时用这么多的编译优化），总用时450ms左右（不加的话800ms左右）：

```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
long long x[1000001],a[1000001],b[1000001];
long long ta[1000001],tb[1000001];
long long na[1000001];
long long lenna=0,lennb=0;
long long max(long long x,long long y)
{
    return x>y?x:y;
}
void px(long long l,long long r,long long f[])
{
    long long x=l,y=r,mid=f[(l+r)/2];
    while(x<=y)
    {
        while(f[x]<mid)
        {
            x++;
        }
        while(f[y]>mid)
        {
            y--;
        }
        if(x<=y)
        {
            long long t=f[x];
            f[x]=f[y];
            f[y]=t;
            x++;
            y--;
        }
    }
    if(l<y)
    {
        px(l,y,f);
    }
    if(x<r)
    {
        px(x,r,f);
    }
}
long long find(long long x)
{
    long long l=1,r=lenna;
    while(l<r)
    {
        long long mid=(l+r)/2;
        if(na[mid]<x)
        {
            l=mid+1;
        }
        else
        {
            r=mid;
        }
    }
    return l;
}
int main()
{
    long long max1=0,max2=0,ans=0;
    long long lenta=0,n=0,m=0;
    scanf("%lld %lld",&n,&m);
    for(long long i=1;i<=n;i++)
    {
        scanf("%lld",&x[i]);
        ta[++lenta]=i+x[i];
        if(i-x[i]>=0)
        {
            ta[++lenta]=i-x[i];
        }
        else
        {
            ta[++lenta]=x[i]-i;
        }
    }
    px(1,lenta,ta);
    for(long long i=1;i<=lenta;i++)
    {
        if(ta[i]==ta[i-1])
        {
            ta[i-1]=-1;
        }
    }
    for(long long i=1;i<=lenta;i++)
    {
        if(ta[i]!=-1)
        {
            na[++lenna]=ta[i];
        }
    }
    for(long long i=1;i<=n;i++)
    {
        long long dq=find(i+x[i]);
        a[dq]++;
        max1=max(max1,dq);
        if(i-x[i]>=0)
        {
            a[find(i-x[i])]++;
        }
        else
        {
            dq=find(x[i]-i);
            b[dq]++;
            max2=max(max2,dq);
        }
    }
    for(long long i=0;i<=max1;i++)
    {
        ans+=a[i]*(a[i]-1)/2;
    }
    for(long long i=1;i<=max2;i++)
    {
        ans+=b[i]*(b[i]-1)/2;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Mizuhara (赞：1)

看了题解发现自己想的十分复杂。

现在来说一下不一样的方法。

题目要求放倒后可以重合的竹竿的对数，

自然会想到去研究：两个什么样的竹竿可以重合。

设第$i$个竹竿是的高度为$l[i]$，

那么对于任意的$1<=i<j<=n$，

它们倒地重合有三种情况：

1. 一起倒在中间:$l[i]+l[j]=j-i$，这等价于$l[i]+i=-(l[j]-j)$。

1. 一起倒在左边:$l[j]-l[i]=j-i$，这等价于$l[i]-i=l[j]-j$。

1. 一起倒在左边:$l[i]-l[j]=j-i$，这等价于$l[i]+i=l[j]+j$。

以上等价转化用到了大家在高中学习中做导数题经常用到的构造函数思想。

对于$2,3$，我们可以将$l[i]+i,l[i]-i$存进$A$,$B$数组，

若有$k$个$i$满足$l[i]+i$或$l[i]-i$相等，

则显然对应着$k*(k-1)/2$对优秀的竹竿。

扫一遍即可算出答案。这里是$O(n)$的。

而对于$1$，我们可以将$-(l[i]-i)$存进$C$数组，

再遍历一遍$l[i]+i$的$A$数组，

对于每个$i$，二分查找$A[i]$在$C$数组中出现的左界与右界$l,r$

那么就对应了$r-l+1$对优秀的竹竿。

这一过程是$O(nlogn)$。

而对于两个竹竿，最多满足$1,2,3$中的一项，故以上计算不重不漏。

总计时间复杂度是$O(nlogn)$。

```

#include<algorithm>
#include<iostream>
#include<cstdio>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=200020;

int n,m,l[maxn],a[maxn],b[maxn];
int worrk1(){
    int Ans=0;
    rep(i,1,n)
    rep(j,i+1,n)
    if(l[i]+l[j]==j-i||l[i]-l[j]==j-i||l[j]-l[i]==j-i)Ans++;
    return Ans;
}
int main(){
    long long Ans=0;
    scanf("%d%d",&n,&m);
    rep(i,1,n){
        scanf("%d",&l[i]);
        a[i]=l[i]+i;
        b[i]=l[i]-i;
    }
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    long long ji=0;a[0]=2000000000;
    rep(i,1,n){
        if(a[i]==a[i-1])ji++;
        else {
            Ans+=ji*(ji-1)/2;
            ji=1;
        }
    }
    Ans+=ji*(ji-1)/2;
    ji=1;
    
    b[0]=2000000000;
    rep(i,1,n){
        if(b[i]==b[i-1])ji++;
        else {
            Ans+=ji*(ji-1)/2;
            ji=1;
        }
    }
    Ans+=ji*(ji-1)/2;
    
    rep(i,1,n)b[i]=-b[i];
    sort(b+1,b+n+1);
    //rep(i,1,n)cout<<a[i]<<' '<<b[i]<<endl;
    rep(i,1,n){
        int key=a[i];
        long long ll,rr;
        int l,r,mid;
        l=1,r=n;
        while(l<r){
            mid=(l+r)>>1;
            if(b[mid]<key)l=mid+1;
            else r=mid;
        }
        ll=l;
        
        l=1,r=n;
        while(l<r){
            mid=(l+r+1)>>1;
            if(b[mid]>key)r=mid-1;
            else l=mid;
        }
        rr=r;
        
        if(b[ll]==key&&b[rr]==key&&ll<=rr)Ans+=rr-ll+1;
    }
    cout<<Ans;
    return 0;
}

```

---

## 作者：Misaka19280 (赞：1)

月赛的T2，难度不算大

我们考虑每个竹竿砍倒以后向左和向右的坐标，存入数组中，如果某两个竹竿砍倒后的坐标相等，则他们就是优秀的竹竿。

sort一下，然后就可以找有多少个相同的坐标，如果有n个相同的坐标，则ans+=n*(n-1)/2

贴代码

```
Var
	a:array[1..400010]of int64;
	n,i,j,x,top:longint;
	ans,qwq:qword;
	
Procedure qsort(l,r:longint);
var
	i,j:longint;
	e,f:int64;
begin
	i:=l;
	j:=r;
	e:=a[(l+r) div 2];
	repeat
		while a[i]<e do inc(i);
		while a[j]>e do dec(j);
		if i<=j then
			begin
				f:=a[i];
				a[i]:=a[j];
				a[j]:=f;
				inc(i);
				dec(j);
			end;
	until i>j;
	if i<r then qsort(i,r);
	if l<j then qsort(l,j);
end;

Begin
	readln(n);
	top:=0;
	for i:=1 to n do
		begin
			read(x);
			inc(top);
			a[top]:=i+x; //砍倒后倒向左边的坐标
			inc(top);
			a[top]:=i-x; //砍倒后倒向右边的坐标
		end;
	qsort(1,top);
	i:=1;
	while i<=top do
		begin
			j:=i;
			while a[j+1]=a[i] do inc(j); //有多少个相同的坐标
			qwq:=j-i+1;
			qwq:=qwq*(qwq-1) div 2;
			ans:=ans+qwq;
			i:=j+1;
		end;
	writeln(ans);
End.
```

什么？看不懂Pascal？

真讨厌= =

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n,m,i,a[400010];
	long long ans;
	cin>>n>>m;
	for (i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		a[i*2-1]=i+x;
		a[i*2]=i-x;
	}
	n*=2;
	sort(a+1,a+n+1);
	cout<<endl;
	i=1;
	ans=0;
	while (i<=n)
	{
		int j=i;
		long long qwq;
		while (a[j+1]==a[i]) j++;
		qwq=j-i+1;
		qwq=qwq*(qwq-1)/2;
		ans+=qwq;
		i=j+1;
	}
	cout<<ans;
}
```

---

## 作者：Zechariah (赞：1)

其实挺简单的一道题  

思路：每根杆子要么往左倒，要么往右倒，所以每根杆子顶端只可能落在两个位置，那么我们可以记录下每根杆子倒下后可能的两个位置，这些位置如果有重复，就说明有杆子优秀的。显然如果这个位置有n个杆子顶端，那么这个位置产生的优秀杆子对数就是1+2+3...+(n-1)，用等差数列求和很容易就能O(1)求出。（可能说的有点乱，下面说说具体怎么做）

1.对于第i根杆子，记录下他倒下的左右端点，也就是i-h[i]和i+h[i]  
2.对于记录下的这一个数组，排序，方便找重复的点  
3.找出每一个位置有多少个重复的点，记录答案(注意开long long)  

下面上代码
```cpp
#include <bits/stdc++.h>
#define N 500000
using namespace std;
inline long long read()
{
    register long long num=0;
    register bool flag=false;
    register char ch;
    while ((ch=getchar())==' '||ch=='\n'||ch=='\r');
    if (ch=='-')flag=true;else num=ch^48;
    while ((ch=getchar())!=' '&&ch!='\n'&&ch!='\r'&&~ch)
        num=num*10+(ch^48);
    if (flag)return -num;return num;
}
long long num[N],tot;
int main()
{
    register int n=read(),m=read();
    for (register int i=1;i<=n;++i)
    {
        register int x=read();
        num[++tot]=i-x;
        num[++tot]=i+x;
    }
    sort(num+1,num+tot+1);
    register int loc=1;
    register long long ans=0;
    while (loc<=tot)
    {
        register long long tmp=0;
        while(num[loc]==num[loc+1]){++loc,++tmp;}
        if (tmp)
        ans+=(1+tmp)*tmp/2;
        ++loc;
    }
    printf("%lld",ans);
    return 0;
}

```

---

## 作者：基础不牢 (赞：1)


## 主要思路

在这里使用$map$实在是再好不过的选择了。可以不用费心思处理负数的情况（$map$的下标允许是负数）。

每次输入，标记这个点向左倒顶部的位置和向右倾倒顶部的位置。

例如，编号为$i$，长度为$a$的竹竿：

    i-a//向左倾倒
    i+a//向右倾倒

当发现有两个（及以上）的点能倒在该处时，至少有一对竹竿在这个点成为一对“优秀”的竹竿。

当有$n$个点倒在该处时，组合情况为：

	n=2: [12] num=1;
    n=3: [12][13][23] num=3;
    n=4: [12][13][23][14][24][34] num=6;
    
我们发现，只要在上一个统计的答案的基础上让所有的点都与新来的点进行组合就行了。

这个题就这样解决了

## 代码

	#include<iostream>
	#include<cstdio>
	#include<map>
	using namespace std;
	map<long long,long long>b;
	long long n,m,a,ans,i;
	int main()
	{
    	cin>>n>>m;
    	for(i=1;i<=n;i++)
    	{
        	cin>>a;
        	b[i-a]++;
        	b[i+a]++;
        	ans+=b[i-a]-1;
        	ans+=b[i+a]-1;
    	}
    	cout<<ans;
    	return 0;
	}

---

## 作者：蒟蒻CGZ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P4889)


### 思路

首先，每一个flag都只有可能向左或向右倒

我们管flag倒了之后，两个在地上的顶端叫**落点**

那么，题目就转化成了：

### 在所有可能的落点中，有多少对重合

~~容我稍稍滥用一下标题字体~~

so，我们完全可以把每一个可能的落点都算出来，将这些坐标存入一个数组中，排个序，接着对于每一段连着相等的落点坐标，计算其对答案的贡献。
 
 - 对于长度为 $ 1 $ 的连续段，不用管，因为不可能产生重合的点对，对答案没有任何贡献
 - $ \geq 2$ 的情况，举个例子，如果这一段的长度为 $5$，那么产生的点对数量就是 $\frac {5 * (5 - 1)}{2}$，其实就是等差数列：`1 + 2 + 3 + 4`
 
 ### 代码
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10; 
int n, m, a[N << 2], cnt = 0; // cnt可能的落点数量
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') f = -f;
		ch = getchar(); 
	}
	while(isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar(); 
	}
	return x * f; 
}
inline int work(int n) {
	return n * (n - 1) / 2;
}
int main() {
	n = read(); m = read();
	for (int tmp, i = 1; i <= n; ++ i) {
		tmp = read();
		a[++ cnt] = i + tmp;
		a[++ cnt] = i - tmp;
	}
	sort(a + 1, a + 1 + cnt);
	int ans = 0;
	for (int i = 1; i <= cnt; ++ i) {
		int res = i;
		while(a[res] == a[res + 1]) {
			res ++;
		}
		ans += work(res - i + 1);
		i = res;
	}
	printf("%d\n", ans);
	return 0;

```

~~十年OI一场空，不开longlong见祖宗~~


---

## 作者：ljc20020730 (赞：0)

本题STL中的map做法

显然我们只需要知道每根木头倒下去的两种可能他们的顶点在哪里就行

假设处在i位置木条高为u显然这两个位置是
$$i+u$$

$$i-u$$

我们只需要在这个标记上+1就行

然后遍历整个map发现每个有标记的点打的标记是s那么就是在s中任取2根都可以头碰头就是$$C^{2}_{s}=(s-1)s$$然后求个和，除以2就是答案（每根木条出现2遍）

```
# include <bits/stdc++.h>
# define ll long long
using namespace std;
map<int,int>mp;
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	int  u;
	for (int i=1;i<=n;i++) {
		scanf("%d",&u);
		mp[i-u]++;mp[i+u]++;
	}
	map<int,int>::iterator it;
	ll ans=0ll;
	for (it=mp.begin();it!=mp.end();it++) {
	   ans+=(ll)(it->second-1)*(it->second);
	}
	printf("%lld\n",ans/2ll);
	return 0;
}
```

---

## 作者：糖hhhh？ (赞：0)

# **还望dalao们指教**

## 30分做法：

暴力求解
```
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
int n,inf,ans;
int a[200001];
int main()
{
    scanf("%d%d",&n,&inf);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    for(int j=i+1;j<=n;j++)
    if(abs(a[i]-a[j])==j-i||a[i]+a[j]==j-i)
    ans++;
    printf("%d\n",ans);
    return 0;
}
```

O(n^2)的TLE算法，目测……优化不了

而且也没有用到题目中的最大高度

所以，**怎么用空间换时间呢**

## 60分做法：

数组记录某一点倒下的杆子数量

扫一遍

永远记得long long的痛[扎心了]
```
#include <cstdio>
#include <cmath>
#include <iostream>
#define in long long
using namespace std;
in n,inf,ans;
int a[700001]={0};
int b[700001]={0};
in jkl(in x)
{//组合数x个里选两个
    if(x%2==0)
    return x/2*(x-1);
    else
    return (x-1)/2*x;//只是因为胆小
}
int main()
{
    int max1=0,max2=0;//用来减少后期枚举量
    int x;
    cin>>n>>inf;
    for(int i=1;i<=n;i++){
        cin>>x;
        a[x+i]++,max1=max(max1,i+x);
        if(i-x>=0)
        a[i-x]++;
        else b[x-i]++,max2=max(max2,x-i);//数组下标貌似不能为负……
    }
    for(int i=0;i<=max1;i++)
    ans+=jkl(a[i]);//扫一遍
    for(int i=1;i<=max2;i++)
    ans+=jkl(b[i]);//扫一遍
    cout<<ans<<endl;
    return 0;
}
```
O(m+n)的RE算法

听说用stl中的map就能过，但本蒟蒻表示不会……

但是m<10^9,数组开不了辣么大……

当然了这个程序里有许多的空间浪费，很多数组都是0

# 100分做法：
感谢cfy大佬orzorz
```
#include <bits/stdc++.h>
#define in long long
using namespace std;
in n,inf,ans;
int a[1000005]={0};
int b[1000005];
in jkl(in x)
{//组合数x个里选两个
    if(x%2==0)
    return x/2*(x-1);
    else
    return (x-1)/2*x;//只是因为胆小
}
int main()
{
	int x,y,maxx=0;
	scanf("%lld%lld",&n,&inf);
	for(int i=0;i<=1000004;i++)b[i]=1<<30;//注意不要赋0或-1
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		x+=i;//往右倒
		y=max(x,-x)%1000000;
        maxx=max(maxx,y);
		for(;;y++)
		{
			if(b[y]==1<<30||b[y]==x)//是否存入？
			{
				if(b[y]==x)a[y]++;//若已经存入，个数+1
				else//若未存入，，那就存吧……
				{
					a[y]=1;
					b[y]=x;
				}
				break;
			}
		}
		x=2*i-x;//往左倒
		y=max(x,-x)%1000000;//ctrl+c
        maxx=max(maxx,y);
		for(;;y++)
		{
			if(b[y]==1<<30||b[y]==x)
			{
				if(b[y]==x)a[y]++;
				else
				{
					a[y]=1;
					b[y]=x;
				}
				break;
			}
		}
	}
	for(int i=0;i<=maxx;i++)
	ans+=jkl(a[i]);
	printf("%lld\n",ans);
	return 0;
}
```

# 洛谷月赛真是好题

---

## 作者：Stella_Yan (赞：0)

这一题难度其实不大，我一开始是用的$O(N^2)$暴力枚举,枚举每两根竹竿是否倒下来能重合，但是只有30分。

之后我想出了$O(N)$算法：输入完数据后，扫一遍，定义一个$l$数组，$l[i]$代表有几根竹竿倒下来能倒在$i$点。但是竹竿可以往左倒啊，有一些竹竿就倒在负的点上了，所以我们把它加上$m$。每一根竹竿还没倒的时候先统计一下它倒到的这个点之前有几根竹竿倒下来也可以砸到，这一根竹竿倒下去之后可以和之前的每一根组成“优秀的竹竿”，所以把它累加到答案。但是$m$太大会爆空间，所以只有60分。

再后来，我把$l$数组改为$map$，满分过。

贴上代码：

---

```
#include<iostream>
#include<cstdio>
#include<map>//各种头文件
using namespace std;
long long sum=0;//有多少对竹竿可以重合
int a[200010];//竹竿长度
map<int,int> l;//统计每一个点有多少根竹竿倒下来可以砸到
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);//这里的m可以不要，因为map好像支持负数下标
    for(int i=1;i<=n;i++){//读入
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){//从头到尾扫一遍
        sum+=l[i+a[i]];//右边累加答案
        			   //记住要先累加，再倒，因为如果先倒再累加的话
                       //那么自己和自己会多算一次
        l[i+a[i]]++;//往右倒
        sum+=l[i-a[i]];//左边累加
        l[i-a[i]]++;//往左倒
    }
    printf("%ld",sum);//输出
    return 0;//结束
}
```

---

~~第一次写月赛+绿题题解，求过~~

---

## 作者：yummy (赞：0)

简单的题目，我也不知道为什么会标上提高+难度的标签。

我没有使用传说中的STL——map  ~~反正我也不懂呀…~~

于是我就采用了一种小学生级别的办法，叫做STL——sort

首先，每个flag都可以向左倒或者向右，我们把这2种情况都统计入一个数组，再进行排序，然后找出重复的数量。

换句话说，我们把所有的端点记录下来，然后如果有倒在同一个端点的，那么一定是来自不同的竹竿，那么它们就产生了一对“优秀的竹竿”。

举个栗子，对于这个数据：
```
6 5
2 3 4 2 2 1
```
那么储存的结果就是这样的：
- $-1,-1,-1,2,3,5$ //向左倒
- $3,5,7,6,7,7$ //向右倒
- $-1,-1,-1,2,3,3,5,5,6,7,7,7$ //合起来排个序

于是，答案很明显了：
- 3个-1 3对$C^2_3=3$
- 2个3  1对$C^2_2=1$
- 2个5  1对$C^2_2=1$
- 3个7  1对$C^2_3=1$
- 合计  6对

感觉不是很好讲，希望你们能理解

速度根本不是一个数量级啊！

[我的代码](https://www.luogu.org/record/show?rid=11077511)

[和某题解的对比](https://www.luogu.org/recordnew/show/11086196)

因此，难度=PJ-

接下来，上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,t=0;
int a[400005];//a数组用于记录所有端点
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int p;
        cin>>p;
        a[i]=i+p;//right!
        a[i+n]=i-p;//left!
    }
    sort(a+1,a+2*n+1);//找重复的
    int j=1;
    for(int i=2;i<=2*n;i++)//统计
        if(a[i]==a[i-1])
        {
            t+=j;
            j++;
        }
        else
            j=1;
    cout<<t;
    return 0;
}
```

---

## 作者：Cobalt (赞：0)

### 平衡树写法
对于每一个flag，记录下它向左/右倒之后顶端的位置。

那么对于第i个flag，高度为h，能和它顶端重合的竹竿（不算自己）个数为：
- 
#### 顶端位置为(i-h)的flag个数   + 顶端位置为(i+h)的flag个数 -2 

#### 一些细节：
1. 因为计算重合flag时包含了自己所以要减去2 

2. 因为不考虑顺序，所以最后要将答案除2

用FHQ-Treap来实现特定位置点个数的查询

```cpp
#include<iostream>
#include<algorithm>
#define N 200010
using namespace std;
long long val[N*2];
int rnd[N*2],son[N*2][2],size[N*2],sz;
int n,x,y,temp,root=0;
long long h[N],ans,a,m;
inline int newnode(long long x){
    size[++sz]=1;
    val[sz]=x;
    rnd[sz]=rand();
    return sz;
}
inline void update(int x){
    size[x]=size[son[x][0]]+size[son[x][1]]+1;
}
void split(int x,int &l,int &r,long long k){
    if(!x)
        l=r=0;
    else{
        if(val[x]<=k){
            l=x;
            split(son[x][1],son[x][1],r,k);
        }
        else{
            r=x;
            split(son[x][0],l,son[x][0],k);
        }
        update(x);
    }
}
int merge(int x,int y){
    if(!x||!y)
        return x+y;
    if(rnd[x]<rnd[y]){
        son[x][1]=merge(son[x][1],y);
        update(x);
        return x;
    }
    else{
        son[y][0]=merge(x,son[y][0]);
        update(y);
        return y;
    }
}
inline void add(long long t){
    split(root,x,y,t);
    root=merge(merge(x,newnode(t)),y);
}

inline int getans(long long t){
	//核心操作，获取顶端为t的flag个数
    int res;
    split(root,x,y,t);
    split(x,x,temp,t-1);
    res=size[temp];
    root=merge(merge(x,temp),y);
    return res-1;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a;
    	h[i]=a;
    	add(i-a);//向左倒 
    	add(i+a);//向右倒 
    }
    for(int i=1;i<=n;i++){
        ans+=getans(i-h[i]);//i向左倒后能和i顶端重合的 
        ans+=getans(i+h[i]);//i向右倒后能和i顶端重合的 
    }
    ans/=2;//因为不考虑顺序，所以要除2 
    cout<<ans;
    return 0;
}
```


---

## 作者：x义x (赞：0)

我们对于每个杆子都记录其放倒后的左端点和右端点，如果有$k$个点都是$x$，那么我们可以从这$k$个里面随便选两个都算是一对吧？那么它对答案的贡献就是$C^2_k=\tfrac {k*(k-1)} 2$。

对于找出重复的点这一操作，并不需要和楼上两位一样使用map，而是直接排序即可。

代码如下。

```
#include<bits/stdc++.h>
using namespace std;

int N,M;

int A[500005];
long long ANS;

int main(){
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		int t;cin>>t;
		A[2*i-1]=i-t;A[2*i]=i+t;
	}
	sort(A+1,A+2*N+1);
	int i=1;
	for(;i<=2*N;){
		int j=i;
		while(A[j+1]==A[i] && j<2*N) j++;
		ANS+=(long long)(j-i)*(j-i+1)/2; 
		i=j+1;
	} 
	cout<<ANS;
} 
```

---

## 作者：猫粮寸断 (赞：0)

~~因为把long long写成int而只过三个点的蒟蒻~~

其实这道题并没有那么难，我们可以很自然地想到，我们只需要预处理这样一个东西

s[i]表示第i个点将有多少根竹竿倒在这个点，这样的话答案就是ΣC(s[i],2)

但是问题在于m的数量级很大，直接开数组会炸掉，那么怎么办呢？

~~我会map！我会hash！~~

只要排序一下就可以解决啦~~

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int s[400010];
int main()
{
	int n,m,h,i;
	long long ans=0,now=1;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	 {
	 	cin>>h;
	 	s[i]=i-h;
	 	s[i+n]=i+h;
	 }
	sort(s+1,s+2*n+1);
	s[0]=-234234;
	for(i=2;i<=2*n;i++)
	{
		if(s[i]!=s[i-1])
		{
			ans+=now*(now-1)/2;
			now=1;
		}
		else
		 now++;
	}
	ans+=now*(now-1)/2;
	cout<<ans;
	return 0;
}
```

---

## 作者：天羽 (赞：0)

对于一个普及组的人，做到这条提高組級別的题真的吓到我了....

**那么讲一讲这道题我是怎样想的**：

因为每根竹竿都只能向左或向右倒，所以每一杆竹杆都能求出它们顶端倒下的位置。那么如果两根竹杆倒下的位置的相同的，答案就加1。

但是如果是一根一根地去检查，时间复杂度大概是O（N²），200000的数据肯定会爆的。

所以我们可以先对数据进行排序，然后再进行处理。

而要怎样处理呢：首先我们要把倒在同一个位置的竹杆找出来，由于我们己经排好序了，所以只要用O（N）的时间寻找;

而如果我们找到了有N根竹杆倒在同一位置呢，我們假设它們的竹杆编号为1,2，...，N。1号竹杆会和2到Ñ编号的竹杆组成一对优秀的竹杆，就会有N-1对优秀的竹杆，而2号竹杆就会和除了自己以外的竹杆组成优秀的竹杆，但是由于2号和1号己经组成过优秀的竹杆，所以有N-2对优秀的竹杆。

到了最后，就是N-1号和N号的竹杆组成一对优秀的竹杆。所以这N根竹杆会组成1 + 2 + 3 + ... + N-2 + N-1对优秀的竹杆。

那题目所给的最高竹杆高度有什么用呢？可能那些大牛可以用到，但是我这样小牛是用不到的OuO。

最后附上代码：
```cpp
#include <iostream>
using namespace std;
long long int a[400005]//竹桿倒下的地方;
int qs(int start,int end)
{
	int left=start,right=end,mid;
	mid=(a[left]+a[right])/2;
	while(left<=right)
	{
		while(a[left]<mid)left++;
		while(a[right]>mid)right--;
		if(left<=right)
		{
			swap(a[left],a[right]);
			left++;
			right--;
		}
	}
	if(right>start)qs(start,right);
	if(end>left)qs(left,end);
}
int main(){
	long long int n,m,b[200005]//竹桿高度,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)//寻找竹杆向左向右倒下的地方

	{
		a[i*2-1]=i-b[i];
		a[i*2]=i+b[i];
	}
	qs(1,n*2);
	int d=1;
	for(int i=1;i<=n*2;i++)
	{
		//cout<<a[i]<<" ";
		if(a[i]==a[i+1])
		{
			ans+=d;//如果前面己经有d个相同位置的竹杆，再加一根的话就优秀的竹杆的对数就会加d对。
			d++;
		}
		else
		{
			d=1;
		}
	}
	cout<<ans;
}
```

---

## 作者：z3475 (赞：0)

容易发现我们可以用一个数组记录flag向左/向右倒下后头部相同坐标的数量，简单点说就是按照桶排序的思路来统计

然后? 对于每一个数按照C(2,n)=n*(n-1)/2,求和即为答案

但是m高达1e9,这个数组绝对会爆,我们需要用数据结构来存储,这里我用的是~~Treap~~ ~~Splay~~ hash表,熟用stl处理冲突只需5行代码超简单

顺便提一下hash怎么做

```cpp 
vector<pair<int,int>> hash[N]
```

简单的hash函数-除一个常数M（这样冲突能控制到O(M)时间复杂度

但是向左倒下可能有负数,这样我们+一个表示正负数界线的常数L

考虑N的值,存入最大1e9+2e5,M当然越小越好,这里我取M为5000,N就是(1e9+2e5)/5000*2=400080（正负数要乘2）,保险一点N取402000,L就是201000

Tips:其实M还可以更小的
```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
template<typename T=int>T gi(){
    register T i(0);register bool f(false);
    register char c=getchar();
    while (!isdigit(c)) f=c=='-'?true:false,c=getchar();
    while (isdigit(c)) i=c-'0'+(i<<3)+(i<<1),c=getchar();
    return f?-i:i;
}
#define N 200010
#define pii pair<int,int>

int n,m;
int a[N];

#define M 5000
#define L 201000
vector<pii> ha[402000];

void add(ri i){
    vector<pii> &v=ha[L+i/M];
    vector<pii>::iterator j=lower_bound(v.begin(),v.end(),pii(i,0));
    if (j!=v.end()&&j->first==i) j->second++;
    else v.insert(j,pii(i,1));
}

int main(){
    n=gi();m=gi();
    for(ri i=0;i!=n;i++){
    	ri t=gi();
        add(i+t);add(i-t);
    }
    long long ans=0;
    for (vector<pii> *i=ha;i!=ha+402000;i++)
        for(vector<pii>::iterator j=i->begin();j!=i->end();j++)
			ans+=((ll)j->second*(j->second-1)>>1);
    printf("%lld\n",ans);
}
```

---

## 作者：EarringYYR (赞：0)

题解里面一堆用map的，这里提供一个不用map的思路。
对于每一个竿子，你都可以记录下他倒下的点的位置。到这里的思路还是差不多的。但是我们并不需要将每个杆子倒下的位置作为下标来存入数组，而是直接放在数组尾部。当记录完所有杆子后，将他们倒下的位置排一下序，再从头到尾遍历一遍，就可以找出倒下的位置相同的竿子有多少个了。因为两个竿子不可能有两种放倒的方式使他们的顶点重合（显然），因此不会重复。
更具体的见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,sum,a[200005],num[400005];
long long ans;
int main()
{
    cin>>n>>m;
    for(long long i=1;i<=n;++i)
    {
        cin>>a[i];
        num[++sum]=i-a[i];
        num[++sum]=i+a[i];//将倒下的位置记入数组
    }
    sort(num+1,num+sum+1);//排序
    long long nu=0;
    for(long long i=1;i<=sum;++i)
    {
        if(num[i]!=num[i-1])//当前倒下的位置已经没有竿子了
        {
            ans+=nu*(nu-1)/2;//将倒下位置相同的竿子两两配对
            nu=0;
        }
        nu++;//记录倒在相同位置的竿子有多少个
    }
    ans+=nu*(nu-1)/2;//还剩下最后一个倒下的位置没有判定
    cout<<ans;
    return 0;
}
```

---

