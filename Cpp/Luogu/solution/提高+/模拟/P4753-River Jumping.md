# River Jumping

## 题目描述

有一条宽度为 $N$ 的河上，小 D 位于坐标为 $0$ 的河岸上，他想到达坐标为 $N$ 的河岸上后再回到坐标为 $0$ 的位置。在到达坐标为 $N$ 的河岸之前小 D 只能向坐标更大的位置跳跃，在到达坐标为 $N$ 的河岸之后小 D 只能向坐标更小的位置跳跃。在河的中间有 $M$ 个岩石，小 D 希望能跳到每个岩石上恰好一次。由于小 D 的跳跃能力太强，小 D 的跳跃长度有个下限 $S$，但没有上限。现在请你判断他是否能够完成他的目标。

## 说明/提示

对于全部数据，保证 $1 \le N,S \le 100000$，$0 \le M < N$，$1 \le w_i < N$。

## 样例 #1

### 输入

```
6 1 3
3```

### 输出

```
YES
1 2 0```

## 样例 #2

### 输入

```
6 2 2
2 4```

### 输出

```
YES
2 3 1 0```

## 样例 #3

### 输入

```
5 2 3
2 3```

### 输出

```
NO```

# 题解

## 作者：FlierKing (赞：17)

首先我们考虑最靠近开头和最靠近结尾的两块岩石，如果他们离开头/结尾的距离小于 $S$，那么这块岩石将不可能被跳到，从而导致无解。

对于三个连续的岩石 $i,i+1,i+2$，如果$w_{i+2}-w_i<S$ ，由于我们只能来回一次，且每次跳到其中的一个石头上时必然不可能跳到另一个石头上，所以这种情况也会导致无解。

那么有解时我们只需要贪心地能跳就选择一个距离不小于 $S$ 的且最近的跳就可以了。

时间复杂度 $O(N)$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAXN 100005
using namespace std;
    int n,m,s,p,cnt;
    int a[MAXN],f[MAXN];
    bool u[MAXN];
int inline read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    n=read(),m=read(),s=read();
    for (int i=1;i<=m;i++)
        a[i]=read();
    sort(a+1,a+m+1);
    a[0]=0,a[m+1]=n;
    for (int i=1;i<=m+1;i++)
        if (a[i]-p>=s)
        {
            f[++cnt]=i;
            p=a[i];
            u[i]=true;
        }
    if (p!=a[m+1])
    {
        puts("NO");
        return 0;
    }
    for (int i=m;i>=0;i--)
        if (!u[i]&&p-a[i]>=s)
        {
            f[++cnt]=i;
            p=a[i];
            u[i]=true;
        }
    if (cnt<m+2)
        puts("NO");
    else
    {
        puts("YES");
        for (int i=1;i<=m+2;i++)
            printf("%d%c",f[i],i==m+2?'\n':' ');
    } 
    return 0;
}
```

---

## 作者：Vermouth_1412 (赞：8)

本人（蒻）第一篇题解，谨以此纪念此题提交20多次。
感谢以下大佬

1.[暮雪﹃紛紛](https://www.luogu.org/space/show?uid=20782)2.[Rorshach](https://www.luogu.org/space/show?uid=59303)
------------
这是并不华丽的分割线，言归正传，下面是本题的讲解。
相信这道题会被dalao们吊着捶，而我被这道题吊着捶（~~好吧，又说无关的了~~）。嗯，其实这道题就是一道模拟题。

对，就是各种模拟判断有没有解。

第一种情况，**最靠近开头和最靠近结尾的两块岩石，如果他们离开头/结尾的距离小于s ，那么这块岩石将不可能被跳到，从而导致无解**。

第二种情况**，第i+2块石头与第i块石头距离只差小于s，因为来回最多只能跳到这3块石头中的2块，因而无解**。

这，就够了吗？hhhh。我就是因为到此为止交了20多遍，**因为m可能等于0**（然而聪明的你们早就想到了，~~然后我遭到了无情的嘲讽~~）。
另外，**还要考虑因n<s进而无解的情况。**

好了，剩下的都是有解的了，方法**模拟贪心**随便挑。嗯，代码如下：
(被注释掉的是贪心思路)

```c
#include<cstdio>
using namespace std;
int n,m,s,xy,num;
int w[100005],team[100005];
bool exam[100005];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=m;++i)
    scanf("%d",&w[i]);
    if(n<s)
    {
    	printf("NO");
	   	return 0;
    }
    if(m!=0)
    {
    	if(w[1]<s)
	    {
	    	printf("NO");
	   	    return 0;
	    }
	    if(s>(n-w[m]))
	    {
	    	printf("NO");
	    	return 0;
	    }
	    for(int i=1;i+2<=m;++i)
	        if((w[i+2]-w[i])<s)
	        {
	            printf("NO");
	            return 0;
	        }
    }
    printf("YES\n");
    for(int i=1;i<=m;i+=2)
        printf("%d ",i);
    printf("%d ",m+1);
    for(int i=m-(m&1);i>=1;i-=2)
    printf("%d ",i);
    printf("0");
    /*xy=0;
    for(int i=1;i<=m;++i)
    {
            if((xy+s)<=w[i])
            {
                xy=w[i];
                ++num;
                team[num]=i;
                exam[i]=true;
            }
    }
    ++num;
    team[num]=m+1;
    for(int i=m;i>=1;--i)
    {
        if(!exam[i])
        {
            ++num;
            team[num]=i;
        }
    }
    ++num;
    team[num]=0;
    for(int i=1;i<=num;++i)
        printf("%d ",team[i]);*/
    return 0;
}
```
最后祝大家++RP(据说++RP跑的比较快)

---

## 作者：y2823774827y (赞：4)


祭此题一直WA一个点

典型的贪心，每次从现在所处的点，每次找离该点最近的点(按来去方向),如果距离不小于跳跃下限则加入数组，反之则跳过

上AC代码
```cpp
# include<cstdio>
# include<cstring>
using namespace std;
typedef long long LL;
LL L,n,u,xian,num=0;
LL a[100100],cun[100100],f[100100];
int main(){
	scanf("%lld%lld%lld",&L,&n,&u);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	a[0]=0; a[n+1]=L;  //首尾 
	cun[0]=0; 
	xian=L-u;//只有小于L-u才能保证到达此点后能跳到河岸 
	//-----------------------------------------------------------------
	for(int i=1;i<=n;++i)
		if(a[i]<=xian&&a[i]-a[cun[num]]>=u){
			cun[++num]=i;  
			f[i]=1; //记录已经走过的点 
		} 
	cun[++num]=n+1;//记录河岸 
	for(int i=n;i>=0;--i)
	    if(!f[i]&&a[cun[num]]-a[i]>=u) 
		    cun[++num]=i;
	//------------------------------------------------------------------
	if(num!=n+2){//没有到达所有的点 
		printf("NO"); return 0;
	}
	else{
		printf("YES\n");
		for(int i=1;i<=n+2;++i) printf("%lld ",cun[i]);
		return 0;
	}
}
```
再发一下96分的，（返回起点的代码）
```cpp
for (int i=m;i>=1;i--)
        if (a[i]>=s&&!u[i]&&a[f[cnt]]-a[i]>=s)
            f[++cnt]=i;
    f[++cnt]=0;
```
这样为什么会WA一个点？

解释一下（最好先自己想想）:当跳跃下限大于河岸距离,这样的代码会直接记录起点和终点而没有判断距离，本应该是NO结果输出了YES（想了很久只想到这种情况，太蒻了。。）

---

## 作者：Viston (赞：3)

首先，~~这题不是普及－的题吗~~  

~~咋就成了绿题了~~
____
然后，这题不是一明显的贪心吗【总感觉A题难多了】  

因为这位大侠跳跃长度有一个最小值，所以每次在标记一个离最小值最近的，到终点再看看能否跳回去，弄一遍，看看是否全部被标记不就行了...  
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d[100005],e[100005],f[100005],i,j,k;
int main()
{
    cin>>a>>b>>c;
    for(i=1;i<=b;i++)
    cin>>d[i];
    d[0]=0;
    d[b+1]=a;
    for(i=0;i<=b+1;i++)
    if(d[i]-d[k]>=c&&f[i]==0)//如果未被标记
    {
        k=i;
        e[j]=i;
        f[i]=1;
        j++;
    }//贪心找下一个
    //现在跳到对面啦！
    for(i=b+1;i>=0;i--)
    if(d[k]-d[i]>=c&&f[i]==0)//傻不愣登的跳回去
    {
        k=i;
        e[j]=i;
        f[i]=1;
        j++;
    }
    if(j!=b+2)//看看是否全部跳过
    cout<<"NO\n";
    else
    {	cout<<"YES\n";
    	for(i=0;i<=j-1;i++)
            cout<<e[i]<<' ';
    }
    return 0;
}
```

---

## 作者：Happy_Orca (赞：1)

如果想要完成目标，最好的情况是两次跳的线路交错，即每条线路的石头不相邻。如果有相邻的，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vhgzna94.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们可以选择将其中任意一个与边上的交换顺序，并对后面的取反，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o43k2n22.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们只需要判断任意两个不相邻的点之间的距离是否小于 $S$ 就行了

输出时记得把两岸也算上

```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,m,s,a[maxn],q[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
int main(){
	n=read(),m=read(),s=read();
	for(int i=1;i<=m;i++) a[i]=read();
	if(m==0){if(n>=s){printf("YES\n1 0");return 0;}else{printf("NO\n");return 0;}}
	if(a[1]<s){printf("NO\n");return 0;}//如果你将两岸也看做石头的话是不需要处理第一块的
	else{
		int h=0,t=1;q[1]=a[1];
		for(int i=2;i<=m;i++){
			while(a[i]-s>q[h]&&h<t) h++;
			q[++t]=a[i];
			if(t-h+1==3){printf("NO\n");return 0;}
		}
	}
	printf("YES\n");
	for(int i=2;i<=m;i+=2) printf("%d ",i);printf("%d ",m+1);
	for(int i=m-!(m&1);i>=1;i-=2) printf("%d ",i);printf("%d\n",0);
	return 0;
}
```


---

## 作者：星0a0空 (赞：1)

{P党前来报到！}

标准贪心=。=
--


——————————————————————————————————

首先根据题意，每块石头都必须要踩，且只能踩一次

所以可以从起点向终点跳两次，不必跳到终点再返回

推荐同时跳，让两个点同时从0开始跳

如果下一石头有一个点能过让该点跳过去，否则如果两个点都不行则输出No（这个石头无法被踩）

附上代码
```pascal
var
  a,aa:array[0..130000] of longint;
  b,c,d,i,j,k,t,n,m,x,y,s1,s2:longint;
begin
  readln(n,m,b);
  s1:=0;
  s2:=0;
  c:=0;
  d:=0;
  for i:=1 to m do
  begin
    read(x);
    if s1+b<=x then begin d:=d+1; a[d]:=i; s1:=x; end else
    if s2+b<=x then begin c:=c+1; aa[c]:=i; s2:=x; end else
    begin k:=1; break; end;
  end;
  if ((s1+b>n) or (s2+b>n)) then k:=1 else begin d:=d+1; a[d]:=m+1; end;
  if k=1 then writeln('NO') else
  begin
    writeln('YES');
    for i:=1 to d do
    write(a[i],' ');
    for i:=c downto 0 do
    write(aa[i],' ');
  end;
end.
```



---

## 作者：Acfboy (赞：1)

**本蒟蒻第一次发布题解，写得不好请多多谅解。**

---
### 总体思路
这道题看到的第一眼就是对于到达的每个石块搜寻下面第一个可以到达的点，把这点记录。

当然，这是对于可行的情况，那怎么样是不可行呢？看了看第三个样例，原来是跳的时候直接跳到了对岸以后，所以呢，我就写了个判断，如果跳出了河就直接输出‘NO’并退出。

于是，我的主要代码就变成了这么个样子：
```pascal
 t:=0;
  f[n]:=1; id[n]:=m+1;//id[i]表示坐标为i的石块的编号
  f[0]:=1; //把所有有石块的坐标在f里记为1
  while t<n do//这是前往对岸的时候，t表示现在所在的坐标
  begin
    i:=-1;//这是为了判断必须跳到终点以后的情况，如果下面的循环没有执行（下界大于上界）则i为-1
    for i:=t+s to n do//找到下一个可行的坐标
      if (f[i]=1) then
        break;

    t:=i;
    if t<0 then//判断是否跳了出去
      begin
        write('NO');
        exit;
      end;
    f[t]:=0;//跳过的不能再跳了
    inc(tail);
    ans[tail]:=id[t];//把编号加入答案数组
  end;
  while t>0 do//从对岸回来的时候，思路和上面一样
  begin
    i:=-1;
    for i:=t-s downto 0 do
      if f[i]=1 then
        break;
    t:=i;
    if t<0 then
      begin
        write('NO');
        exit;
      end;
    f[t]:=0;
    inc(tail);
    ans[tail]:=id[t];
  end;
```
可是一提交，发现WA了，咦？这是怎么回事？
### 改进
莫非还有一些情况没有考虑到？

由于每次找的是下面刚好符合的第一个，这样确保了如果小D能完成，那么一定可以输出正解，那么应该是NO的情况没有考虑到。

头和尾出现的跳出都已考虑到了，那么难道是中间出了问题？

经过仔细思考，我发现有可能中间会漏掉一些点，但仍能到达头和尾，这种情况我们的程序会输出YES而实际上答案是NO。

举个例子吧，比如
> 10 3 3
>
> 3 4 5

我们的程序会先跳到3，然后跳到10，回来时先跳到5，再跳到0，中间漏掉了4.

那么这个情况怎么解决呢，看了看楼上的题解，发现都归纳出了一个规律，我作为蒟蒻可没有那么大的本事，于是我有一种暴力的判断方法：

**前面的程序运行完直接判断一下f数组中还有没有1**

这样中间没跳到的石子都能被我们找出来，反正只要有一个没跳到，就输出NO了事！

附上代码（我是第一个pascal吧）
```pascal
  var
  n,m,s,i,t,tail,x:longint;
  f,ans,id:array[0..100005]of longint;
begin
  read(n,m,s);
  for i:=1 to m do
  begin
    read(x);
    f[x]:=1;
    id[x]:=i;
  end;
  t:=0;
  f[n]:=1; id[n]:=m+1;
  f[0]:=1; 
  while t<n do
  begin
    i:=-1;
    for i:=t+s to n do
      if (f[i]=1) then
        break;

    t:=i;
    if t<0 then
      begin
        write('NO');
        exit;
      end;
    f[t]:=0;
    inc(tail);
    ans[tail]:=id[t];
  end;
  while t>0 do
  begin
    i:=-1;
    for i:=t-s downto 0 do
      if f[i]=1 then
        break;
    t:=i;
    if t<0 then
      begin
        write('NO');
        exit;
      end;
    f[t]:=0;
    inc(tail);
    ans[tail]:=id[t];
  end;
  for i:=1 to n do//枚举所有坐标
    if f[i]=1 then//判断有没有没到的石子
      begin
        write('NO');
        exit;
      end;
  writeln('YES');
  for i:=1 to tail do
    write(ans[i],' ');
end.

```
------
感谢您的阅读

最后给自己的博客打个广告[unsmart的博客](http://unsmart.pw/)

---

## 作者：wweiyi (赞：0)

# 【解题报告】洛谷 P4753 River Jumping

### 原题链接

https://www.luogu.com.cn/problem/P4753

### 题目大意

一条宽度为 $n$ 的河上，有 $m$ 块石头，每块石头距离起点（坐标为0）有一个距离，我们要从起点跳到终点，通过一些方法使得跳到每个石头上一次，最终回到起点，每次跳的距离有一个下限 $s$ ,输出一种可能的方案

### 思路

看到这道题目，我们首先关注到的是一个下限 $s$ ，为什么我们要关注这个呢？因为，我们可以发现，如果你想跳的石头与你的距离 $d \ge s$ 你是不是就可以随便跳？

于是我们自然而然地想，我们是不是可以使用贪心算法？

每次跳，跳到一个距离自己第一个 $\ge s$ 的石头上，一直向右，到右边了之后，我们再向左重复上述过程。因为在**能完成的情况下**我们跳到最右边的时候，离左边的距离一定大于 $s$ ，所以我们可以跳过去，然后再跳回来，反复横跳，最后就能完成了

那么，我们还要处理**不能完成**的情况，那么我们什么情况不能完成呢？

-  最左边的石头和 $0$ 距离小于 $s$  ，或者最右边的石头和 $n$ 的距离小于 $s$
- 有连续三个石头之间的距离小于 $s$ ，因为这样总有一个石头跳不到
- $0$ 和 $n$ 的距离小于 $s$ ，实际上这个是严格被第一个不能完成的条件包含的

这样，我们找到了所有不能完成的情况

接着，我们进行一个暴力，从 $0$ 开始跳，每次判断是否能跳，如果能跳的话，标记一个 `vis=true` 表示已经访问过了，如果已经访问过了，那就访问下一个石头能不能跳.跳到 $n$ 之后反过来向 $0$ 跳.对于这个过程使用一个 `while` 循环就可以了，我们每次循环开头判断一下是否每个石头都走了，如果都走了，那我们退出循环

至于输出的话，一定要记得不要先输出 $0$ ，它永远都是最后一个，然后我们把输出放在循环里面边跳边输出就可以了

这道题目我昨天干了两个多小时，一直被不能完成的条件所困，**请大家一定要注意条件！！！**


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
const int maxn=100005;
int n,m,s;
int w[maxn];
int cnt=0;
bool vis[maxn];
bool flag=false;
bool check()
{
	for(int i=0;i<=m+1;i++)
	if(!vis[i])
	return false;
	return true;
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	cin>>n>>m>>s;
	
	for(int i=1;i<=m;i++)
	{
		cin>>w[i];
		if(w[i]-w[i-1]<s)
		cnt++;
		else
		cnt=0;
		if(cnt>=3) flag=true;
	}
	w[0]=0;w[m+1]=n;
	
	if(n<s)
	{
		cout<<"NO"<<'\n';
		return 0;
	}
	
	if(m!=0&&(w[1]<s||n-w[m]<s))
	{
		cout<<"NO"<<'\n';
		return 0;
	}
	/*if(m==2)
	{
		if(w[m]-w[m-1]<s)
		{
			cout<<"NO"<<'\n';
			return 0;
		}
	}*/
	if(flag)
	{
		cout<<"NO"<<'\n';
		return 0;
	}
	cout<<"YES"<<'\n'; 
	int last=0;
	int tot=1;
	while(!check())
	{
		for(int i=1;i<=m+1;i++)
		{
			if(w[i]-w[last]>=s&&!vis[i])
			{
				cout<<i<<" ";
				vis[i]=true;
				last=i;
			}
			else continue;
		}
		for(int i=last;i>=0;i--)
		{
			if(w[last]-w[i]>=s&&!vis[i])
			{
				cout<<i<<" ";
				vis[i]=true;
				last=i;
			}
		}
	}
	
	return 0;
}
```



---

## 作者：UperFicial (赞：0)

# 贪心

### 前言

贡献了四五遍提交，原因是把变量看反了/ll

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/P4753)

### 题意简述

有 $m$ 个岩石，坐标为 $w_1,w_2,w_3,\cdots,w_m$，终点为 $n$，你需从位置 $0$ 到达位置 $n$，若从位置 $i$ 跳跃到位置 $j$ 需要满足：

- $j$ 未被跳过。

- 两点距离相差不小于 $s$。

求从起点到达终点再回到起点经过哪些岩石。

### 题目分析

不难发现我们每次只要跳到离当前点最近的且合法的位置就可以了。

然后顺着找一遍，反过来再找一遍，最终按顺序记录下经过的点，就是最终的答案。

而不合法的情况就是若最终记录的点的总数不等于 $m+2$，则无解，因为你来回跳的石头的总数就是 $m+2$，也必须为 $m+2$ 个。

然后就做完了。

代码就不给了，做法都有了，而且代码也肥肠好些。

[$\text{AC}$ 记录](https://www.luogu.com.cn/record/50138787)

时空复杂度：$O(n)$。

$$\texttt{The End.by UF}$$



---

## 作者：hkr04 (赞：0)

~~论我为什么会把这么简单的贪心写成搜索 自省中~~  
首先整理一下题目给出的条件：
1. 弹跳只有下限S   
2. 必须把每一块石头都跳过一次  
3. 只有往返两次的跳跃  

那么答案数组中所存储的信息就可以分为两段：  
1. 从起点到终点  
2. 从终点回到起点  

我一开始的想法是直接进行搜索（这也太傻了吧），然后估计一些细节部分没处理好，有WA的也有TLE的，得分是40。  
脑残代码：（完全可以直接往下拉跳过）
```cpp
#include <cstdio>
#define Go true
#define Return false
const int maxn=100000+10;
int w[maxn],ans[maxn];
int n,m,s;
bool vis[maxn];
bool dfs(int pos,int tot,bool flag)//pos为当前位置，tot记录当前跳到的石头是第几个，flag代表前进或返回
{
    if (pos==0&&flag==Return)//跳回起点了
        return 1;
    if (pos==m+1)//跳到终点，开始返回
        flag=Return;
    if (vis[pos])
        return 0;
    vis[pos]=1;
    ans[tot]=pos;
    bool find=0;
    if (flag==Go)
        for (int i=pos+1;i<=m+1;i++)
            if (w[i]-w[pos]>=s&&dfs(i, tot+1, Go))
            {
                find=1;
                break;//找到合法的解即可退出
            }
    else
        for (int i=pos-1;i>=0;i--)
        {
            if (w[pos]-w[i]>=s&&dfs(i, tot+1, Return))
                find=1;
            else if(!vis[i]&&w[pos]-w[i]<s)//如果要跳到的点没有合法路径(不是已经被跳过）或无法跳到，说明当前点没有合法路径，直接跳出循环
             	break;
        }
    vis[pos]=0;//回溯前消除影响
    return find;
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for (int i=1;i<=m;i++)
        scanf("%d",&w[i]);
    w[0]=0;
    w[m+1]=n;
    if (dfs(0, 0, Go))
    {
        printf("YES\n");
        for (int i=1;i<m+2;i++)
            printf("%d ",ans[i]);
        printf("0\n");
    }
    else
        printf("NO\n");
    return 0;
} 
```
事实上，这道题用贪心来做又快码量又小  

怎么个贪心法呢？  
首先，前面提到，若有解，则可分为**前往**和**返回**两个阶段  
我们将石头和河岸简化为点来描述  

**对于前往**  
设前往路程上任意两个距离大于S的相邻点，较近点为x，较远点为y  
设若这两点距离为dis。  
**当dis>S时**，小D若跳至y点，则回来时绝对不可能跳回x点（因为y已经离x最近了）；  
**当dis<S时**，小D若跳至y点，回来时**有可能**可以跳到x点，若跳至x点，回来时**也有可能**可以跳至y点。  
但是在<S的情况下你必须选择至少一个来跳，否则这两个点将有一个跳不到（举个例子：你回来的时候跳到了一个到y的距离是3的点，S为2，你为了跳完必须要先跳到y上，但是跳到y以后由于x与y的距离为1小于S无法跳跃，跳不到x；如果你跳到了x，也同样没法往回跳，跳不到y）  
**当dis==y时**，跳哪个都不会对解造成影响（我不想举例了，这个画画图或者感性理解就好）  
综上所述，我们每一次跳到离当前位置大于S且最近的点就不会对解的存在产生影响 

好了，如果我们能成功的这样跳到对岸，我们就成功了一半了。如果发现不能这样跳到对岸，说明肯定无解  

**对于返回**  
返回时已经没有回路了！所以如果找到最近的没跳过的点距离小于S，好了，完了，跳不过去,直接输出NO吧。如果路上还没走过的每一个点之间的距离都大于s，一定就能走回去  

上AC代码吧：
```cpp
#include <cstdio>
const int maxn=100000+10;
int w[maxn];
int n,m,s;
bool vis[maxn];
int ans[maxn];
int cnt=0;
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for (int i=1;i<=m;i++)
        scanf("%d",&w[i]);
    w[0]=0;
    w[m+1]=n;
    int p=0;//p为当前所在位置
    for (int i=1;i<=m+1;i++)
        if (w[i]-p>=s)//找到第一个距离当前位置大于S的点
        {
            ans[++cnt]=i;//存储答案
            p=w[i];//更新当前位置
            vis[i]=1;//标记为已经跳过
        }
    if (p!=n)//去的时候就已经跳不到对岸了，无解
    {
        printf("NO\n");
        return 0;
    }
    for (int i=m+1;i>=0;i--)
    {
        if(p-w[i]>=s&&!vis[i])//找到下一个没被跳过且距离大于S的点
        {
        	ans[++cnt]=i;//存储答案
            p=w[i];//更新当前位置
    		  		//这里的标记可以不用打，因为不会再跳回来了
        }
        else if (!vis[i])//如果考虑的点距离小于S且没被跳过，说明没有办法跳到它了，无解
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for (int i=1;i<=m+2;i++)
    printf("%d%c",ans[i],i==m+2?'\n':' ');
    return 0;
}
```
感谢题解区各位大佬给予的参考

---

## 作者：刘子钧 (赞：0)

纯贪心，比2015跳石头简单多了。
怎么贪：想想看，在一个石头，如果不跳最近的能跳的石头，那么回来的时候就会有可能出现两个更近的。
例如：1可以跳3.4.5，如果不去3去了5，那么回来就会有可能34被卡。
所以，。。。。。
```c
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
//typedef vector<int>mp;
//mp a[200005];
int a[100005];
int b[100005];
int c[100005];
int n,m,s,t;
int main()
{
//freopen("1text.in.txt","r",stdin);
//freopen("","w",stdout);
cin>>n>>m>>s;
for(int i=1;i<=m;i++)
{
 cin>>t;
 a[t]=1;
 b[t]=i;
}
t=0;
vector<int>ans;
a[n+1]=1;
int t1;
while(t+=s)
{
	if(t>=n)
	{
		t=t1;
		break;
	}
	t1=t;
	while(a[t]==0)t++;
	a[t]=2;
	if(t<n)
	ans.push_back(b[t]);
}
if(n-t<s)
{
cout<<"NO";	
return 0;
}
t=1;
for(int i=1;i<=n;i++)
{
	if(a[i]==1)
	{
		c[t]=i;
		t++;
	}
}
c[t]=n;
t++;
for(int i=0;i<t-1;i++)
{
	if(c[i+1]-c[i]<s)
	{
		cout<<"NO";
		return 0;
	}
}
cout<<"YES"<<endl;
for(int i=0;i<ans.size();i++)
{
	cout<<ans[i]<<" ";
}
cout<<m+1<<" ";
for(int i=n;i>0;i--)
{
	if(a[i]==1)
	cout<<b[i]<<" ";
}
cout<<"0";
	return 0;
}

/*
50000 5 3
4 6 8 78 10000
*/
```

---

## 作者：Trinity (赞：0)

# 题目：P4753 River Jumping 2018 洛谷7月月赛 T2
## 题目描述
$\ \ \ \ \ \ $有一条宽度为 $N$ 的河上，小$D$位于坐标为 $0$ 的河岸上，他想到达坐标为 $N$ 的河岸上后再回到坐标为 $0$ 的位置。在到达坐标为 $N$ 的河岸之前小$D$只能向坐标更大的位置跳跃，在到达坐标为 $N$ 的河岸之后小$D$只能向坐标更小的位置跳跃。在河的中间有 $M$ 个岩石，小$D$希望能跳到每个岩石上恰好一次。由于小$D$的跳跃能力太强，小D的跳跃长度有个下限 $S$ ，但没有上限。现在请你判断他是否能够完成他的目标。   
$\ \ \ \ \ \ $如果小$D$可以完成他的目标，第一行输出$YES$, 下一行输出踩石头的编号 。**如果有多种解法，允许输出任意一种。**  
$\ \ \ \ \ \ $如果小$D$不能完成他的目标，第一行输出$NO$。
## 分析
$1$ . 看完题目，你极可能想起某NOIP提高组跳石头，你会想起贪心和二分算法，但是很明显，本题不符合二分的单调条件，所以应使用贪心 ( 这个题的贪心思想只是黄题水平）。  
$2$ . 我们不太好处理去和回两次走，应该想出一种策略，使去或回尽量偏向一方。     
$3$ .输入的 $w$ 序列有序。(但是出题人的题解$sort$了一遍)  
## 解答
$1$ . 首先啊，我们要把 $w_0$ 赋成 $0$, $w_{m+1}$赋成 $n$ ,也就是方便我们接下来的处理。  
$2$ . 细节，我们发现，如果离起点最近的石头距离起点( 即$w_1$ )小于 $s$ ,或者离终点最近的石头距离终点( 即$w_m$ )小于 $s$ ,那么可以直接判成$NO$。因为在这种情况下，去时无法踩到离起点最近的石头，回时也踩不了离终点最近的石头，就会有石头遗漏, 即:  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ if(w[1]<s\ or\ n-w[m]<s)\ then\ NO$  
$3$ . 细节$again$, 数据范围中有一种毒瘤的情况 ( $m=0$ ), 那么如果最短跳跃距离小于了河宽，那么简单输出即可， 反之就输出$NO$, 即:  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ if(m=0\ and\ n<s)\ then\ YES$  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ else\ then \ NO$  
$4$ . 我们的策略：去时跳所有离我们最近的可跳的石头，剩下没跳时就回时跳，如果回时跳不了，就是 $NO$ 的情况。其正确性，简单可证，假如我们一定能跳上所有的石头，就需要去和回各跳一部分，我们去时尽量放缓步伐，跳尽量多的石头，回时就能大跨步，迅速完成问题，如果回时跳不了，那么去时就应该多跳几个，一直影响到去时的最后一次，就必定$N)$。  
$5$ . 我们用两个指针 $l$ , $r$ 来实现，一个指向现在脚下的石头的编号，另一个指向下一次我们要尝试的石头编号 , 将满足条件 $ w_l-w_r<s$ 时记下标号，那是我们回时要踩的石头，不满足，也记下，这是去时的石头，具体看代码。
```cpp
int n,m,s,w[N],go[N],cnt_1,come[N],cnt_2,l,r;//指针初始为0。
bool flag=false;
int main()
{
  n=read(),m=read(),s=read();
  for(int i=1;i<=m;i++)w[i]=read();
  w[0]=0,w[m+1]=n;
  if(w[1]<s||n-w[m]<s||(m==0&&n<s)){printf("NO\n");return 0;}//对应着分析2，3。
  else if(m==0&&n>=s){printf("YES\n1 0");return 0;}
  while(r<=m+1)//限制循环，记住可以模拟到最后一位(当然也可以枚举解决问题)
  {
    if(w[r]-w[l]>=s){go[++cnt_1]=r;l=r;r++;}//对应着解答5，先更新l到r，在把r向后移动。
    else {come[++cnt_2]=r;r++;}//记下回来时(其实可以优化)
  }
  for(int i=cnt_2;i>=2;i--)
    if(w[come[i]]-w[come[i-1]]<s){flag=true;break;}//回来时，判定临近两点间的距离是否成立，打标退出。
  if(flag){printf("NO\n");return 0;}
  //有些同学的代码还要输出m+1和0，上面从0开始推避免了这个问题，回的序列中一定有个0(因为l==r==0)
  printf("YES\n");
  for(int i=1;i<=cnt_1;i++)printf("%d ",go[i]);//正序输出去。
  for(int i=cnt_2;i>=1;i--)printf("%d ",come[i]);//倒序输出回。
  return 0;
```
但是，就如我所说，其实可以小小优化，但数据范围太小，题也比较水，其实没什么必要，但还是说一下。
```cpp
while(r<=m+1)
{
  if(w[r]-w[l]>=s){go[++cnt_1]=r;l=r;r++;}
  else {come[++cnt_2]=r;r++;}
  if(cnt_2>=2&&w[come[cnt_2]]-w[come[cnt_2-1]]<s){printf("NO\n");return 0;}//优化在此，处理时就可以比较，得出结论，少一个循环，虽然复杂度On没有变。
}
```
## 总结
$1$ .题目是真的水，不管是思想还是代码，但是我在比较时 $come[cnt]$ 没有套上 $w$ ,调了一上午。  
$2$ .这个故事告诉我们，贪心时尽量使用下标，思路清晰，不易错。

---

## 作者：dasxxx (赞：0)

# 洛谷七月月赛 T2 River Jumping题解
### 并不难的T2（为什么是蓝题orz）

#### 首先根据题目考虑，因为每一次跳至少要跳s，并且每个点都要访问到，并且从头到尾再回到头，**所以距离第一块石头距离0号石头的距离大于等于s**，**第m块石头距离第m+1块石头的距离大于等于s**，否则无解。

#### 其次，考虑中间的节点，若两个点之间的距离小于s了，那么它们一定不能在同方向跳到，而**如果它们中间还有一个节点，它们都无法跳到这个节点**，那么无解。

#### 根据以上两个判断后，剩下序列一定有解。所以只要贪心出最终正向序列，然后剩下的倒序输出即可

### ac代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,s;
int a[100010];
bool vstd[100010];
int main(){
    scanf("%d%d%d",&n,&m,&s);
    a[0]=0;
    a[m+1]=n;
    for (int i=1;i<=m;i++)
        scanf("%d",a+i);
    if (a[1]-a[0]<s||a[m+1]-a[m]<s){
        printf("NO");
        return 0;
    }
    for (int i=1;i<=m;i++)
        if (a[i+1]-a[i-1]<s){
            printf("NO");
            return 0;
        }
    printf("YES\n");
    vstd[0]=true;
    int k=0;
    for (int i=1;i<=m;i++)
        if (a[i]-k>=s){
            printf("%d ",i);
            vstd[i]=true;
            k=a[i];
        }
    printf("%d ",m+1);
    for (int i=m;i>0;i--)
        if (!vstd[i])
            printf("%d ",i);
    printf("0");
    return 0;
}
```

---

## 作者：Dream_It_Possible (赞：0)

~~比赛来迟了，9:34过的这题，9:30比赛停了TT~~

### **算法：** 
贪心

### **思路：**
将终点变为最后一块石头，起点变为第一块石头，第一轮先将所有能跳的石头跳过，跳到终点， **_vis[a[i]]_** 打标记，表示此石头已经跳过，并记录跳过的下标，第二轮往回跳，已经跳过的石头不能再跳，并记录跳过的下标。最后看所有点是否跳过，没有，就输出NO，否则输出YES,并输出记录跳过的下标的数组。
### **代码：**
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
int a[100005],v[100005],dl[100005];
int main()
{
	int n,m,s,i,j,k=0;
	cin>>n>>m>>s;
	for (i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);
	}
	if (n<s)//若河宽小于跳跃下限，直接“NO”
	{
		cout<<"NO"<<endl;
		return 0;
	}
	int qs=0;
	a[m+1]=n;
	a[0]=0;
	for (i=1;i<=m+1;i++)
	{
		if (a[i]-qs>=s)
		{
			qs=a[i];
			v[a[i]]=1;
			dl[++k]=i;
		}
	}
	int zz=n;
	for (i=m;i>=0;i--)
	{
		if (zz-a[i]>=s&&v[a[i]]==0)
		{
			zz=a[i];
			v[a[i]]=1;
			dl[++k]=i;
		}
	}
	for (i=0;i<=m+1;i++)
	if (v[a[i]]==0)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	for (i=1;i<=k;i++)
	{
		cout<<dl[i]<<" ";
	}
	return 0;
} 
```

---

## 作者：破壁人五号 (赞：0)

~~为了获得一模一样的阅读体验，~~欢迎访我的[博客](https://wallbreaker5th.github.io/2018/%E9%A2%98%E8%A7%A3-LGR-049-T2-River%20Jumping/)。

当时看了半天觉得十分不可做，然后看到排行榜里面一群人AC了T2，就准备乱写一个。

写了一半觉得有问题，又没有写了。

之后发现后面的题目更加不可做，把这个程序补完了，WA了一遍之后莫名其妙就A了。

下面进入正文：

题目链接：[https://www.luogu.org/problemnew/show/P4753](https://www.luogu.org/problemnew/show/P4753)

题目大意：数轴上有$m+2$个点，坐标分别为$0,w_1,w_2,...,w_m,n$，
要求把这些点分成2份，使得每一份里面任意两点距离不小于$s$，$0$与$n+1$算2次。

当时第一反应：一跳到对岸，再一跳会来，不就不重复了吗？

然后突然发现要求每个点都恰好一次。

然后瞬间蒙了……

然后开始乱打一波：

首先，为了让每个点都恰好经过一次，去时没有跳到的点返回时必须跳。

由于小D跳跃长度没有限制，所以回来时的石头必须尽可能稀疏。
那么去的时候石头需要尽可能密集。

于是我乱写了一个记搜，记录从0到每个石头**最多**跳多少步（以及每个点的前一个点）。

去的时候就选最多的，回来的时候 就选剩下的。

~~不要问我状态转移方程，我也不知道我是怎么AC的。~~

时间复杂度：$O(\text{能过})$

算法正确性：不知道。如果有人有hack数据请务必洛谷私信我（U37676）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int getint(){
    int ans=0;
    char c=getchar();
    int f=1;
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
    }
    do{
        ans=ans*10+c-'0';
        c=getchar();
    }while(c>='0'&&c<='9');
    return ans*f;
}

int w[100010];
int pre[100010],len[100010];
int n,m,s;

void ss1(int x){
	if(x==0){
		len[0]=0;
		return;
	}
	for(int i=x-1;i>=0;--i){//先考虑近的
		if(len[i]<len[x]&&len[i]!=-1)break;//乱剪枝
		if(w[x]-w[i]<s)continue;//跳不到
		if(!~len[i])ss1(i);//如果没有被搜到
		if(~len[i]&&len[i]+1>len[x]){//如果不是-1（有可能i号石头离河岸太近，到不了，是-1）并且可以更新
			len[x]=len[i]+1;
			pre[x]=i;
            //更新
		}
	}
	//cout<<x<<" "<<len[x]<<endl;
}

bool vis[100010];
int all[100010],tot=0;



int main(){
	n=getint(),m=getint(),s=getint();
	for(int i=1;i<=m;i++){
		w[i]=getint();
	}
	w[m+1]=n;
	memset(pre,0xff,sizeof(pre));
	memset(len,0xff,sizeof(len));
	//int ii=0;
	//->
	ss1(m+1);
	int ii=m+1; 
	while(ii){
		vis[ii]=1;
		all[tot++]=ii;
		ii=pre[ii];
	}
	int lst=m+1;
	for(int i=m+1;i>=0;--i){
		if(!vis[i]){
			if(w[lst]-w[i]<s){
				//cout<<">"<<i<<" "<<lst<<" "<<w[i]<<" "<<w[lst]<<endl;
				puts("NO");
				return 0;
			}
			lst=i;
		}
	}
	puts("YES"); 
	for(int i=tot-1;i>=0;--i){
		printf("%d ",all[i]);
	}
	for(int i=m+1;i>=0;--i){
		if(!vis[i])printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：陈曦 (赞：0)

# **小蒟蒻题解**

这道神奇的模拟题，带一点贪心，其实蛮水的，仔细思考就能ac。

首先我们模拟一下样例2

发现其实答案0 1 2 3也可以，仔细观察题目，我们发现了一句有意思的话
![](https://cdn.luogu.com.cn/upload/pic/23499.png)

所以就可使用xjb算法，复杂度为O（玄学）（~~逃~~

我们假装有两个小D；一个从0开始跳；一个从n开始跳；
只要距离大于s且没被跳过就跳，之所以说是贪心是因为
我们尽可能让小D1号多跳一点石头，小D2号少跳一点（当然可以反过来），最后扫一遍，如果有石头没跳，就输出“NO”，反之就输出“YES”，然后再按小D1号再到小D2号的顺序输出，核心如下

```cpp
 for(int i=0;i<=n;i++)
    if(i-pos>=s&&flag[i]==1)
    {flag[i]=0;ans[now]=a[i];now++;pos=i;}
    pos=n;
    for(int i=n;i>=0;i--)
    if(pos-i>=s&&flag[i]==1)
    {flag[i]=0;ans[now]=a[i];now++;pos=i;}
```

值得一提的是，起点0和终点n也算石头，但是0最后输出，详见代码。
```cpp
#include<iostream>
#include<bits/stdc++.h>//万能头文件，noip不能用
#include<cstdio>
#define maxn 100010
using namespace std;
int a[maxn],ans[maxn];//a记录石头序号，ans记录跳的顺序（即跳的石头序号）
bool flag[maxn];//记录可不可以跳
inline void read(int &x){//快读
    x=0;int f=1; 
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1; 
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }x*=f;
}
int main(){
    //memset(flag,0,sizeof(flag));
    int n,m,s,x,pos=n,now=1;//pos是当前位置，now是已跳石头个数
    read(n);read(m);read(s);
    for(int i=1;i<=m;++i)
    {read(x);flag[x]=1;a[x]=i;}//flag==1代表可以跳
    flag[0]=1;flag[n]=1;
    a[0]=0;a[n]=m+1;//初始化，0和n也算石头
    for(int i=0;i<=n;i++)
    if(i-pos>=s&&flag[i]==1)
    {flag[i]=0;ans[now]=a[i];now++;pos=i;}
    pos=n;
    for(int i=n;i>=0;i--)
    if(pos-i>=s&&flag[i]==1)
    {flag[i]=0;ans[now]=a[i];now++;pos=i;}//上已讲解
    for(int i=0;i<=n;i++)
    if(flag[i]==1) {printf("NO");return 0;}//有石头没跳
    printf("YES\n");
    for(int i=1;i<=now-1;i++)
    printf("%d ",ans[i]);
}
```

---

## 作者：qwerta (赞：0)



**O(n) 贪心**

把一个人来回跳 看作两个青蛙一起跳。

设两只青蛙所在的坐标为 xa , xb。

```cpp
 我们先假设青蛙已经跳了一段路程，且设xa < xb ，面前的最近石块坐标为x
那么有且仅有3种情况：
1: x - xa< s(a青蛙踩不到x)，此时 x - xb < s，那么x石块怎样都踩不到，输出NO。
2:x - xa > s 且 x - xb < s(a能踩 b不能踩)，那么a青蛙跳到x石块，xa = x 。
3:x - xa > s且 x - xb > s(a,b都能踩)，此时可以跳a也可以跳b，但把青蛙a保留在xa 而让b跳到x，比保留b 而让a跳到x对未来有更大的潜力（因为xa < xb，所以xa能跳到的区间比xb大）

```


那么思路就清晰了：

初始时xa=xb=0。扫描坐标w，对于一个新扫入的坐标值，判定以上三种情况并作出相应决策，把两只青蛙经过的坐标分别存储为 a , b数组。

输出时假装a青蛙正着跳，b青蛙反着跳（实际上该谁踩的石头还是它踩），0坐标和河对岸手动输出。

注意以上的假设基于 xa < xb的前提，写代码的时候不要思维僵化。

AC代码：

```
#include<iostream>
#include<cstdio>
using namespace std;
#define R register
inline int read()
{
    char ch=getchar();
    int x=0;bool s=1;
    while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return s?x:-x;
}
int a[100007];
int b[100007];
int toa=0,tob=0;
int main()
{
    int n=read(),m=read(),s=read();
    int xa=0,xb=0;//一开始都在河岸这边
    for(R int i=1;i<=m;++i)
    {
        int x=read();
        if(xa<xb)//如果xa<xb
        {
            if(x-xa<s){cout<<"NO";return 0;}//case 1
            else if(x-xb<s){a[++toa]=i;xa=x;}//case 2
            else {b[++tob]=i;xb=x;}//case 3
        }
        else//如果xb<=xa
        {
            if(x-xb<s){cout<<"NO";return 0;}//case 1
            else if(x-xa<s){b[++tob]=i;xb=x;}//case 2
            else {a[++toa]=i;xa=x;}//case 3
        }
    }
    if(n-xa<s&&n-xb<s){cout<<"NO";return 0;}//有青蛙跳不上对岸 输出NO
    cout<<"YES"<<endl;
    for(R int i=1;i<=toa;++i)
    cout<<a[i]<<" ";//a正跳
    cout<<m+1<<" ";
    for(R int i=tob;i;--i)
    cout<<b[i]<<" ";//b反跳
    cout<<0;
    return 0;
}
```

~~应该算不上蓝题 而且数据范围好小~~

[~~偷偷放广告~~](https://blog.csdn.net/qq_41007369/article/details/81055927)

---

