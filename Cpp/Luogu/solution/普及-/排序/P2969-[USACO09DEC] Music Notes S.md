# [USACO09DEC] Music Notes S

## 题目描述

FJ is going to teach his cows how to play a song. The song consists of N (1 <= N <= 50,000) notes, and the i-th note lasts for B\_i (1 <= B\_i <= 10,000) beats (thus no song is longer than 500,000,000 beats). The cows will begin playing the song at time 0; thus, they will play note 1 from time 0 through just before time B\_1, note 2 from time B\_1 through just before time B\_1 + B\_2, etc.

However, recently the cows have lost interest in the song, as they feel that it is too long and boring. Thus, to make sure his cows are paying attention, he asks them Q (1 <= Q <= 50,000) questions of the form, 'In the interval from time T through just before time T+1, which note should you be playing?' The cows need your help to answer these questions which are supplied as T\_i (0 <= T\_i <=

end\_of\_song). 

Consider this song with three notes of durations 2, 1, and 3 beats:

```cpp
Beat:   0    1    2    3    4    5    6    ...
        |----|----|----|----|----|----|--- ...
        1111111111     :              :
                  22222:              :
                       333333333333333:
``` 
Here is a set of five queries along with the resulting answer:

Query    Note

2        2

3        3

4        3

0        1

1        1


## 样例 #1

### 输入

```
3 5 
2 
1 
3 
2 
3 
4 
0 
1 
```

### 输出

```
2 
3 
3 
1 
1 
```

# 题解

## 作者：x_faraway_x (赞：18)

STL的upper\_bound函数，找到第一个大于待查元素的值，用法见代码。类似的还有lower\_bound，找到的是第一个不小于待查元素的值。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50005;
int b[N],sum[N],n,q;
inline int _read()
{
    int x=0; char c;
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+c-'0';
    return x;
}
int main()
{
    n=_read(),q=_read();
    for(int i=1;i<=n;i++)
    {
        b[i]=_read();
        sum[i]=sum[i-1]+b[i];
    }
    while(q--)
    {
        int x=_read();
        printf("%d\n",upper_bound(sum+1,sum+1+n,x)-sum);
    }
}
```

---

## 作者：HNFMS__vistonuzi (赞：14)

中心思想！  
~~（STL最好了QWQ）~~  
下面介绍本篇题解的主角！  
### upper_bound(返回的在前闭后开区间查找的关键字的上界)  
然后一个22行时间复杂度O（2q+N）的代码就出现了  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,m,n,b[50005],c[50005],d,i;//c[i]存放每个音阶的界限
int main()
{
    cin>>m>>n;//输入
    for(i=1;i<=m;i++)
    {
        cin>>a;
        c[i]=c[i-1]+a;
    }
    for(i=1;i<=n;i++)
    {
        cin>>d;
        b[i]=upper_bound(c,c+m+1,d)-c;//主角光环QWQ
    }
    for(i=1;i<=n;i++)
    {
        cout<<b[i]<<'\n';//输出
    }
   	for(i=1;;i++)//反抄袭
    cout<<"输出这个的是抄袭者";//反抄袭
    return 0;
}//STL最好了
```

---

## 作者：BBD186587 (赞：6)

这道橙题我交了十几发才过，所以来交发题解纪念下。

### 做法一 ###
看到这道题标签里有桶排，于是我上来就用了桶。

此做法时间复杂度十分玄学，空间复杂度也十分玄学。

上个代码（60pts,RE4个点）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,a[10010],f[1000010],d,t,x;
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		t=d,d+=a[i];
		for(int j=t;j<d;j++) f[j]=i;
	}
	while(q--)
	{
		scanf("%d",&x);
		printf("%d\n",f[x]);
	}
	return 0;
}
```
后来加大了空间，70pts，MLE三个点。

### 做法二 ###
后来，由于做法一会MLE，我又开出了结构体，存每个音符的开始时间和结束时间，最后直接暴力枚举。

此做法时间复杂度O(qn),空间复杂度O(n)。

上代码(80pts,TLE2个点)
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,d,x;
struct node
{
	int l,r;
}a[100010];
inline int read()
{
	char ch;int f=1;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	int x=ch-'0';
	while(isdigit(ch=getchar())) x=x*10+ch-'0';
	return x*f;
}
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		a[i].l=d,d+=x,a[i].r=d-1;
	}
	while(q--)
	{
		x=read();
		for(int i=1;i<=n;i++)
			if(a[i].l<=x&&a[i].r>=x) {printf("%d\n",i); break;}//暴力枚举
	}
	return 0;
}
```
### 做法三 ###
由于做法二会TLE，又考虑每个音符的开始时间和结束时间是有序的，所以考虑二分查找优化复杂度。

此做法时间复杂度O(qlogn),空间复杂度O(n)。

上代码(100pts)
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,d,x;
struct node
{
	int l,r;
}a[100010];
inline int read()
{
	char ch;int f=1;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	int x=ch-'0';
	while(isdigit(ch=getchar())) x=x*10+ch-'0';
	return x*f;
}//读入优化 此板子由某一巨佬那里搬来
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		a[i].l=d,d+=x,a[i].r=d-1;
	}
	while(q--)
	{
		x=read();
		int l=1,r=n,mid;
		while(1)
		{
			mid=(l+r)/2;
			if(a[mid].l<=x&&a[mid].r>=x) {printf("%d\n",mid); break;}
			else if(a[mid].l>x) r=mid;
			else l=mid+1;
		}//二分查找
	}
	return 0;
}
```
完结撒花~~

---

## 作者：Out_Land (赞：6)

看到有些大佬做的都是二分，我自己没去试，就索性替 P 党发个麻烦一点的做法吧~ ~~(去了快排也没多少)~~


------------

此题比较关键的一步就是把题目的 **一维区间** 看成 **几个点**，然后 **线性处理**。

我用的是 **前缀和** ：
_sum[i]_  表示第  _i_  个音阶的 **起始时间**

则  _sum[1]=0_ (边界) 且  _sum[i+1]=sum[i]+第 i 个音阶持续时间_ (递推式，只用推到 n+1 即可).

而为什么可以这样用前缀和来实现呢？ 就拿样例举例子(a[i] 为第 i 个音阶 **持续时间**)： 

	sum[1]=0；            //第1个音阶起始时间
    sum[2]=sum[1]+a[1]=2；//第2个音阶起始时间
    sum[3]=sum[2]+a[2]=3; //第3个音阶起始时间
    sum[4]=sum[3]+a[3]=6; (虚设的，下面有用）//第4个音阶起始时间

于是对于每个询问，我们可以判断 _Ti_  是否 **大于等于** 被标记音阶的下个音阶的 **起始时间**  (线性处理)：

 _**若是大于等于**_ ，则意味着超过此音阶敲击时间，于是我们就可以让标记 **跳到下个音阶的位置**，直到 **小于** 下个音阶的起始时间为止(想想为什么可以这样得到答案，为什么是大于等于，并想想为什么这里不用处理边界)；

** _若是小于_ ** ，不用怀疑，答案就是它！

时间复杂度：O(n^2);（最坏情况下）

------------


做完了！？  

大大的
## TLE 
送给你！！！ ~~（虽然我没试过~）~~

友情提醒：

#  _**数据范围**_ 

看了木有？？？ 

## 1<=n<= 50000 啊

稳稳的  _**TLE**_  到手！



------------


下面说说正解（咳咳，敲黑板）：

这么灰心干嘛？其实加个 **排序** 和一些 _小手 (shu) 段  (zu) _  就可以完成啦~！

既然每次都要归零重搜，还不如直接 **一遍搜完**。

什么？还可以一遍搜完？？？

那当然，不过一遍搜完的 最最最最最最···(此处省略一万个字) 常规方法就是 **排序** ！！！

当然，O(n^2) 的排序会超时，这里就要用 O(n log n) 的排序啦~ ~~(建议快排，因为可以 ctrl c + ctrl v)~~

按什么来排序呢？自己想！！！

由于排完序后编号会乱，所以一遍搜完后不能直接输出，而是运用 **小技(shu)巧(zu)** 存起来，然后按原序输出就可以啦~~~

------------

所以做完了吗？？？

## 并不！！！(时间复杂度自己算！)

是不是特别 **_崩溃_** ？（斜眼笑）

其实做完了。。。~~(我才没骗你呢~)~~

嘻嘻，我要谢谢你对我的滋瓷，念在你这么有耐心地看到这里，这次我没删部分代码，代码中也有注释~~(哪个代码中没有？)~~~~~(掌声)

废话不多说， _**Diu**_  代码！

------------

```pascal
var
        i,k,m,n:longint;
        a,b,c,d:array[0..1000001] of int64;
        //把 int64 改为 longint 好像也行，不过以防万一~
        //a 为计算前缀和的数组，即上文的 sum；
        //b 为每个询问的信息；
        //c 为每个询问快排后的的编号；
        //d 为每个询问的答案，但 d[i] 中的 i 是每个询问的原始编号。
procedure qsort(l,r:longint); //快排，不多说。
var
	i,j,x,y:longint;
begin
        i:=l;
        j:=r;
        x:=b[(l+r) div 2];
        repeat
           	while b[i]<x do inc(i);
           	while x<b[j] do dec(j);
           	if not(i>j) then
             	begin
                	y:=b[i];
                	b[i]:=b[j];
                	b[j]:=y;
                    y:=c[i]; //编号也要交换哦~
                    c[i]:=c[j];
                    c[j]:=y;
                	inc(i);
                	j:=j-1;
             	end;
        until i>j;
        if l<j then qsort(l,j);
        if i<r then qsort(i,r);
end;
begin
        readln(n,m);
        for i:=1 to n do //读入
        begin
                readln(k);
                a[i+1]:=a[i]+k; //前缀和，会一直算到 n+1 (想想)
        end;               
        for i:=1 to m do
        begin
                c[i]:=i; //每个询问的编号，现在赋值为原始编号，快排后会改变。
                readln(b[i]); //每个询问的信息，即 Ti
        end;
        qsort(1,m); //排序
        k:=1; //起始标记的位置
        for i:=1 to m do //对排序后的询问来寻找答案
        //由于询问是排过序的，所以后面询问的答案肯定在前面询问过的答案之后。
        //所以搜到第 k 个音阶时 不必再去搜前 k-1 个音阶
        begin
                while b[i]>=a[k+1] do inc(k); 
                //跳至符合的音阶，不必再从0跳了，因为前一个询问的答案便为此次询问的起始位置(想想)。
                d[c[i]]:=k; //记录答案。(c[i] 为编号)
        end;
        for i:=1 to m do
                writeln(d[i]);
                //i 即为原始询问的编号(想想)，按原始输入的顺序输出所记录的答案即可。
end.
```

---

## 作者：zhi_zhang (赞：4)

二分

但是存储方式和具体二分过程都和另一个c++手打二分不一样

存每个音符敲打时间的边界

然后二分时如果询问时间在区间内就输出返回

在左边就向左，在右边就向右，如果正好压到右边界直接输出下一个

Rein()是读入优化，为了看起来简洁些就删掉了，ctrl c v最少也打个快读再交吧

```
#include<cstdio>
using namespace std;
struct node{long long l,r;}ZMc[50010];
int N=Rein(),Q=Rein();
void Zfind(int x,int l,int r)
{
	int m=(l+r)/2;
	if(ZMc[m].l<=x&&x<ZMc[m].r) {printf("%d\n",m);return;}
	else if(x==ZMc[m].r) {printf("%d\n",m+1);return;}
	else if(x<ZMc[m].l) Zfind(x,l,m);
	else if(x>ZMc[m].r) Zfind(x,m+1,r);
}
int main()
{
	for(int i=1;i<=N;i++)
		ZMc[i].l=ZMc[i-1].r,
		ZMc[i].r=ZMc[i].l+Rein();
	while(Q--)	Zfind(Rein(),1,N);
	return 0;
}
```

---

## 作者：RiverHamster (赞：4)

##看很多人写的都是二分，来一发简单的C++排序做法

###思路：

**在输入每个音阶的用时时，计算好每个音阶的结束时间(所以最后的时间数组必定有序)**

**问题所询问的时间点也要经过排序，但是因为最后要根据问题的原始顺序输出，所以一定要定义一个id号，最后计算完毕后按照id号排序，还原**

**定义一个指针(不是指向内存地址的那种)，表示现在所在的音阶，如果现在所询问的时间在所指的结束时间点之前，说明这次询问的答案就是这个指针，否则指针++，继续尝试**

###代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int tim[50005];  //表示每个音阶的结束时间，time在评测机里会编译出错，切勿使用此变量名 
struct question{
    int id,tm,ans;  //id表示每个问题的初始位置，tm表示所询问的时间点，ans表示问题的答案 
}a[50005];

inline bool cmpid(question a,question b){  //按照id号排序（还原初始询问顺序） 
    return a.id<b.id;
}

inline bool cmptm(question a,question b){  //按照所询问的时间点排序 
    return a.tm<b.tm;
}

int main(){
    int n,q;  //音阶数量和问题数量 
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>tim[i],tim[i]+=tim[i-1];  //先输入每个音阶的耗时，在加上前面的耗时（类似递推） 
    for(int i=1;i<=q;i++){
        cin>>a[i].tm;  //输入询问的时间点 
        a[i].id=i;     //记录询问顺序 
    } 
    sort(a+1,a+1+q,cmptm);  //按照时间升序排列问题 
    int p=1;  //现在音阶的指针 
    for(int i=1;i<=q;i++){
        if(a[i].tm<tim[p]) a[i].ans=p;  //如果时间点在这个音阶里就记录答案 
        else p++,i--;  //如果时间点超过了就尝试下一个音阶,i--是抵消下次i++的效果 
    }
    sort(a+1,a+1+q,cmpid);  //按照询问顺序(id)还原问题顺序 
    for(int i=1;i<=q;i++){
        cout<<a[i].ans<<endl;  //按照询问顺序输出答案 
    }
    return 0;
}
```
#####By RiverHamster


---

## 作者：Cptraser (赞：3)

我打的是二分，从未想过桶排，内存不会炸吗？

》》
```cpp
var
  a,t:array[0..50005]of longint;
  n,q,i,j,k,x,y,z:longint;
 function ef(x:longint):longint;
   var i,j,k,mid:longint;
     begin
       i:=0;j:=n;
        while i<=j do
          begin
            mid:=(i+j)div 2;
            if x<a[mid] then j:=mid-1 else
            if x>=a[mid+1] then i:=mid+1 else
              begin
                ef:=mid;
                break;
              end;
          end;
     end;
  begin
    readln(n,q);
    a[1]:=0;
     for i:=1 to n do
       begin
         read(x);
         a[i+1]:=a[i]+x;
       end;
     for i:=1 to q do read(t[i]);
     for i:=1 to q do
       writeln(ef(t[i]));
  end.
//膜拜JYZ大神犇
```

---

## 作者：__int (赞：3)

大佬们都用了本蒟蒻看不懂的函数，但其实不用也可以。
输入数据的处理不复杂，就用a[i]标记敲击第i-1个音符的起始值。
然后对要查找的数据进行（结构体）排序，再按照原来的顺序输出结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct yf{
	int i,x,s;
}q[50005];
bool cmp(yf a,yf b)//按照时间排序
{
	return a.x<b.x;
}
bool c2(yf a,yf b)//按照输入顺序排序
{
	return a.i<b.i;
}
int n,q1,b,a[50005],p=1;
int main()
{
	cin>>n>>q1;
	for(int i=1;i<=n;i++)
	{	//敲击音符i的范围是区间[a[i-1],a[i]-1]内的整数
		cin>>b;
		a[i]=a[i-1]+b;
	}
	for(int i=1;i<=q1;i++)
	{
		cin>>q[i].x;
		q[i].i=i;//保存询问的输入次序
	}
	sort(q+1,q+1+q1,cmp);//按照时间排序
	for(int  i=1;p<=q1;i++)
	{	//用while而不是if是因为一个音符可以多次敲击
		while(q[p].x>=a[i-1]&&q[p].x<=a[i]-1)  q[p++].s=i;
	}
	sort(q+1,q+1+q1,c2);//按照输入顺序排序
	for(int i=1;i<=q1;i++)cout<<q[i].s<<'\n';
	return 0;
}
```


---

## 作者：Zhengsiwei (赞：2)

## 题解P2969 音符 Music Notes
这是[题目链接](https://www.luogu.com.cn/problem/P2969)。    
注： “在时间段区间t，T+1内，奶牛敲的是哪个音阶？”意思是说，输入数字 T，输出时刻 T 奶牛正在演奏哪个音阶。

---
下面是解题部分。如果你希望能立刻得到正解，请跳过“思路1”。  
- 思路1 ：  
    所用算法：模拟（我不确定）。  
    枚举所有音阶，直到找到 T 所在的音阶。
    优缺点：  
    -  优点：思路易想，易理解。代码简短。
    -  缺点：会超时。本题中，不算输入，Q 次查询，每次将音阶数组扫一遍，时间复杂度 $O(N)$，总时间复杂度 $O(QN)$，这个时间复杂度是不能被接受的。  

- 思路2 ：
    所用算法：前缀和、二分。  
    算法讲解（可跳过）：   
    前缀和。设某数组为 $a$,则建立一个数组 $pre$，$pre(i)=\sum_{n=0}^{i}a\left(i\right)=a(0)+a(1)+a(2)...+a(i)$。前缀和主要用于求和（$a(i)+a(i+1)+...+a(j-1)+a(j)=\sum_{n=i}^{j}a\left(n\right)=pre(j)-pre(i-1)$），不过这次它是用来记录音阶结束时刻的。前缀和数组生成代码：
    ```
    int pre[50100]={0};
    
    pre[0]=a[0];
    for(int i=1;i<=n;i++)
        pre[i]=pre[i-1]+a[i];
    ```
    二分。仅可用于有序序列。时间复杂度是 check 函数的时间复杂度乘以 $\log n$。详情你可以参考[它](https://wenku.baidu.com/view/e5c210b748649b6648d7c1c708a1284ac85005ff.html)。代码：
    ```
    int Binary(int start/*查找起始点*/,int end/*查找结束点*/, .../*此处填其余必要变量*/){
        int ans,mid;
        while(start<=end){
            mid=(start+end)/2;
            if(check(mid)/*check函数返回mid是否合法，合法返回 true，否则返回 false*/){
                ans=mid;
                end=mid-1;
            }
            else
                start=mid+1;
        }
        return ans;
    }
    ``` 
    言归正传。我们可以用前缀和储存音阶结束时刻，然后用二分算法找到答案。
    优缺点：  
    -  优点：时间复杂度低！本题中，不算输入，Q 次查询，$check()$ 是 $O(1)$ 的，总时间复杂度 $O(Q \log N)$,稳得很。
    -  缺点：？？

---
下面是我的代码。代码中有注释，希望你可以看懂！欢迎参考。
```cpp
//时间复杂度：O(Q log N)
//空间复杂度：O(N)
#include <bits/stdc++.h>
using namespace std;
int Binary_Search(int array[]/*待查找数组*/,int start/*查找起始点*/,int end/*查找结束点*/,int key/*键值*/){
	int ans,mid;
	while(start<=end){
		mid=(start+end)/2;
		if(array[mid]-1>key){
			ans=mid;
			end=mid-1;
		}
		else
			start=mid+1;
	}
	return ans;
}//二分查找非递归版，我没有用STL
int n,q,b[50100]/*变量名如题意*/,pre[50100]/*pre——前缀和*/,temp/*一个临时变量*/;
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		pre[i]=pre[i-1]+b[i];/*处理前缀和*/
	}/*输入数据*/
	for(int i=0;i<q;i++){
		cin>>temp;
		cout<<Binary_Search(pre,1,n,temp)<<endl;
	}/*回答询问*/
	return 0;
}
```
照例给一个[提交记录](https://www.luogu.com.cn/record/30549260)。  
欢迎提出意见。如有意见，请在评论区@我，或私信我。我会尽量作出回应（只是不保证回应速度）。

---

