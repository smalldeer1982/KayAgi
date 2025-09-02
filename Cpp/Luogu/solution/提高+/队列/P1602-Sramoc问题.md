# Sramoc问题

## 题目描述

话说员工们整理好了筷子之后，就准备将快餐送出了，但是一看订单，都傻眼了:订单上没有留电话号码,只写了一个  $sramoc(k,m)$ 函数，这什么东西？什么意思？于是餐厅找来了资深顾问团的成员，YQ，SC，HQ，经过大量的查阅，大家获得了一些信息，$sramoc(k,m)$ 表示用数字 $0,1,2,\dots k-1$ 组成的正整数中能被 $m$ 整除的最小数。例如 $k=2,m=7$ 的时候，$sramoc(2,7)=1001$。自然电话号码就是 $1001$，为了尽快将快餐送出，电脑组的童鞋们埋头算起了这个齐葩的号码。。。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$2\le k\le10$，$1\le m\le 10^3$。

## 样例 #1

### 输入

```
2 7
```

### 输出

```
1001```

# 题解

## 作者：zjh111111 (赞：18)

### ##  _看看大家写的都是BFS，本蒟蒻来一发~~废了九牛二虎之力才做出来DFS的思路~~。_ 

## 【题意】

### 求m的倍数中最小的k进制数。也就是求m的倍数中只有0~k-1的数组成的最小数。

## 【思路】

### 一开始我想到的是纯暴力，枚举m的倍数，然后每次判断一下是否为k进制，是的话输出，显然这样的方法过于慢。
### 下面是这种方法的TLE程序（当然数据大也会炸范围）：### 
```pascal
var
  k,m:longint;
  ans:qword;
function judge(x:qword):boolean;
begin
  while x>0 do
    begin
      if x mod 10>=k then exit(false);//分解数，不符合条件就退出
      x:=x div 10;
    end;
  exit(true);//符合条件
end;
begin
  read(k,m);
  repeat
    ans:=ans+m;//一倍一倍加上去，ans一开始=M的原因是第一次M就有可能符合条件
    while ans mod 10>=k do ans:=ans+m;//最优化
    if judge(ans) then break;//找到立刻退出循环
  until 1 xor 2 < 3;//=until false，装逼的写法PS：1 xor 2 = 01 xor 10 = 3
  write(ans);//输出
end.
```
### 后来换了一种思路，可以DFS啊，每次枚举0~k-1的数，和之前的合并再每次判断一下如果是m的倍数则符合题意，输出。但是会TLE，后来在费凡（FF）巨佬的指点下做了最优化剪枝，但是发现有漏洞，后来完美解决。详见画图注释：

#### ~~乱画一通的~~Picture：
![](https://cdn.luogu.com.cn/upload/pic/24435.png)

### 显然上图是BFS搜索树，数字就是搜到的顺序，所以BFS第一次搜到符合题意的必定是最优解（这里设定深度越低越优）。所以求最优解的时候一般用BFS。（我就用DFS照样0ms）

![](https://cdn.luogu.com.cn/upload/pic/24452.png)

### 这当然就是DFS搜索树了，一次性搜到底，再进行回溯。

## 那么问题来了，我放这些图有啥用？

## 因为我的剪枝第一次就是栽在这了...详见代码吧。

#### Code:（本人P党）
```
var
  k,m,x,L,i:longint;
  ss:string;
  f:array[0..1000] of string;//用来存余数为i的最优解
function stri(s1:string):boolean;
var
  j:longint;
begin
  for j:=1 to length(s1) do
    if s1[j]>'0' then
      begin
        L:=j; exit(true);
      end;
  exit(false);
end;//去除答案前导0
function strj:boolean;
var
  j:longint;
begin
  for j:=1 to length(ss) do
    if ord(ss[j])-48>=k then exit(false);
  exit(true);
end;//判断是否符合题意
procedure dfs(ac:byte;num:longint;s:string;p:boolean);
//ac是当前还有多少层可以拓展，num即当前模M的余数，s为当前拓展出来的数，p见下文
//这里用到了dfsid，即迭代加深搜索，不懂的Baidu上都有
var
  i,j:longint;
begin
  if (p) and (strj) then//第一次的M就是答案
    begin
      write(ss); halt;
    end;
  if (num=0) and (stri(s)) then//找到答案了
    begin
      for i:=L to length(s) do write(s[i]);//前导0不输出
      halt;
    end;
  if (ac=0) or ((f[num]<s) and (length(f[num])=length(s)) or (length(f[num])<length(s))) then exit;//超过x层或是当前数余数已经有比他更优的解则退出
  f[num]:=s;//保存
  for i:=0 to k-1 do
    dfs(ac-1,(num*10+i) mod m,s+chr(ord(i+48)),false);//进行下一次调用
end;
begin
  read(k,m);
  x:=1;
  str(m,ss);
  for i:=0 to m do//一开始赋值为正无穷
    f[i]:='999999999999999999999999999';
  x:=length(ss);
  repeat
    dfs(x,m,'',true);
    inc(x);//此处的x相当于给当前要构造的树制定一个最大深度，超过的直接剪掉。在此题中为数的长度限制。
  until false;//直到找到答案为止
end.
```

## DFSID每次都要重新搜索一遍，所以复杂度略低，约为BFS的两倍。

## 完美撒花

### 不懂的请私信，或者加我QQ：2242579009，备注姓名。

# 欢迎各位大佬巨佬前来拍砖！

# 珍爱生命 拒绝抄袭

# 在此再次感谢费凡巨佬的精心辅导！

## ~~By wan'jiang装逼集团~~

---

## 作者：吾王美如画 (赞：14)

# 唔姆

（隔了好久没写过题解，可能不会写了23333）


------------
- 首先看问题，利用0～k-1这k个数构成最小的可以整除m的数
- 接着我们就想到了暴搜，使用bfs每次往现有的数字后加一位，因为dfs的性质，所以最先找到的数一定是最小的。（显然这样是过不了的
- 但是我们可以发现 a$\equiv$b(mod m)，那么显然a×10+c$\equiv$b×10+c(mod m)。而我们又只需要最小的答案，所以当一个数的模数曾经出现过，我们就不需要这个数了。

根据上文我们得到这样一个代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int k,m;
int mod[15000];
queue<long long>q;
long long bfs(){
	while(!q.empty()){
		long long now=q.front();
		q.pop();
		for(int i=0;i<k;i++){
			long long to=now*10+i;
			if (mod[to%m]==0){
				mod[to%m]=1;
				q.push(to);
				if (to%m==0)return to;
			}
		}
	}
}
int main(){
	cin>>k>>m;
	for(int i=1;i<k;i++){
		q.push(i);
		mod[i%m]=1;
	}
	if (k==2&&m==999)printf("111111111111111111111111111");
	else cout<<bfs();
	return 0;
} 
```

因为最后一个点超大，所以longlong也会爆。（我看好多人都这样直接打表过的

所以我们进一步想，由之前提到的a$\equiv$b(mod m)而a×10+c$\equiv$b×10+c(mod m)，我们没有必要把整个数放入队列，只需放对m的模数就ok，最后为了输出，保存每个数的father和这时选的是哪个数，反向输出就OK。

（代码完全体
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int k,m;
int mod[15000],fa[15000],which[15000];
queue<int>q;
void out(int now){
    if (now==-1)return;
    out(fa[now]);
    cout<<which[now];
}
void bfs(){
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=0;i<k;i++){
			int to=(now*10+i)%m;
			if (mod[to]==0){
				mod[to]=1;
                which[to]=i;
                fa[to]=now;
				q.push(to);
				if (to==0){
                    out(to);
                    return;
                }
			}
		}
	}
}
int main(){
	cin>>k>>m;
    memset(fa,-1,sizeof(fa));
	for(int i=1;i<k;i++){
		q.push(i%m);
		mod[i%m]=1;
        which[i%m]=i;

	}
	bfs();
	return 0;
} 
```


---

## 作者：洛容MX (赞：7)

本蒟蒻的第一篇题解...

如有不足或错误，请在评论中指出或私信告诉我 ~~能憋着最好憋~~着 

## 话不多说，进入正题


---------------------------------------------*我是分割线*---------------------------------------------

### 方法一： _DFS_  

一看到这道题，相信许多人和我一样，第一想法都是**暴力**。通过深搜枚举每一位上可能的数，如果找到答案就输出，否则就向下一位搜索。

这种方法十分容易理解且代码不长 ~~然而我仍然打了40分钟~~ 。但缺点也显而易见——因为深搜时每一位上都要枚举k个数，所以时间代价是非常高的。 _ 只能过八到九个点_。

这时，我们就需要 ~~特判~~ **更好的做法**。

-------------------------------------------*我又是分割线*-------------------------------------------

### 方法二—1： _BFS_

(为了下文叙述方便，我将满足**每一数位上的数都在0~k-1的数**定义为**S数**）

显而易见，在正整数范围内，S数是无穷无尽的。在搜索时，对于每一坨除以m同余的S数中，我们只需要考虑最小的那个 ( 另一篇题解有详细证明过程，这里就不再赘述 ~~才不是因为懒呢，哼QWQ~~ ) 。那么如何找最小的S数呢？

由于在枚举数位时是从小到大枚举，又根据广搜的特性，对于取余m一个相同的模数mod，越小的S数一定是越早搜到的（实在不知道为啥的可以手动模拟一下 ），据此，**我们只需考虑第一次广搜到的除以m余M的S数，以后再搜到的除以m余M的数都可跳过不处理，_与DFS相比，大大减少时间代价_**.

另外，由于答案可能会非常大，所以需要**将答案的每一数位存储下来**，最后再输出

贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,m;
bool b[10010];
struct syzs{
    int mod,val,fro;//a[i].mod表示编号为i的S数除以m的余数，a[i].val表示编号为i的S数的个位数，a[i].fro表示上一个数的编号，存储fro和val方便递归输出结果
}a[10010];
inline void out(int x){//递归输出答案：不断找到上一个编号，输出其存储的值 
    if(!x) return;
    out(a[x].fro);
    if(a[x].fro)/*防止输出时出现首位0*/ printf("%d",a[x].val);
}
int main(){
    scanf("%d%d",&k,&m);
    int r=1;
    int h=1;
    while(r<=h){
        for(int i=0;i<k;i++) if(!b[((a[r].mod*10)%m+i)%m]/*判断之前又没有搜过相同的余数*/&&(r!=1||h!=1||i)/*判断是不是首位，如果是，则跳过0*/){
            int now=((a[r].mod*10)%m+i)%m;
            h++;
            a[h].mod=now;
            b[now]=1;
            a[h].val=i;
            a[h].fro=r;//更新，将新节点加入队列 
            if(!(a[h].mod%m)){
                out(h);//输出 
                return 0;//找到答案即结束 
            }
        }
		r++;
    }
}
```

此方法是可以AC的，那么，有没有**别的写法呢？**

** 当然有！**

-------------------------------------------*我还是分割线*-------------------------------------------

### 方法二—2：用queue（容器适配器）实现广搜！
   众所周知，广搜的本质是队列，而STL库中给出的queue正好可以实现队列中的功能。所以我们可以**用queue实现广搜**。
   
   事实上，方法二-1与方法二-2的区别并不大，只是由于queue的特性，在-2**需要维护的东西**就跟-1**有所差距**，**本质上两者是相同的**
   ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,an[100002];
struct mmtz{
    int mod,val;//与上一篇代码不同，a[i].mod表示除以m余i的S数的上一个S数除以m的余数，a[i].val表示除以m余i的S数的个位数 
} a[1002];
queue<mmtz> syzs;
void out(){
    mmtz x;  
    x.mod=0;
    int op=0;
    while(a[x.mod].val!=-1){
    op++;
    an[op]=a[x.mod].val;//存储答案(也可以用递归) 
    x.mod=a[x.mod].mod;//寻找上一个 
    if(!x.mod) break;//判断首位&&防止死循环 
    }
    for(int i=op;i>0;i--) printf("%d",an[i]);//因为是倒着存储的，所以输出时也要倒着输出 
}
int main(){
    scanf("%d%d",&m,&n);
    memset(a,-1,sizeof(a));//初始化，方便判断由于个位有可能是0，所以不能初始化为0,通过此种初始化手段可以少开一个数组 
    syzs.push((mmtz){0,0});//初始化压入队列 
    while(!syzs.empty()){
        mmtz fir=syzs.front();
        syzs.pop();
        for(int k=0;k<m;k++)if(a[(fir.mod*10+k)%n].val==-1&&(k||fir.mod||fir.val)){//与上一篇意义相同
            mmtz d;
            d.mod=(fir.mod*10+k)%n;
            a[d.mod].mod=fir.mod;
            a[d.mod].val=k;//更新节点 
            syzs.push((mmtz) d);
            if(!d.mod){
            	out();
            	return 0;
            }
        }
    }
} 
```

-----------------------------------------*我仍然是分割线*-----------------------------------------

 * 关于优先队列优化广搜，个人认为对于这题是画蛇添足的做法，因为本身在BFS中，我们只需要考虑最小的那个，由于最先搜索到的就是最小的，所以我们不需要将其排序。
 
 就这样吧......




---

## 作者：我很低调 (赞：6)

# **放题目：**[P1602](https://www.luogu.com.cn/problem/P1602)

看完之后，诡异的想到：~~翻翻小蓝书吧~~是不是要枚举捏？
看了看数据范围，电话号码是0~9，看来不需要用什么ABC

M≤1000，有滴个大，好像已经是鲲之大，longlong存不下级别了，那我有什么办法呢？上网一查，都说是要用：高精度+(\_\_int128)(\*\_\_int128前面有两条下划线）

数据输出还有一个要求：仅1行，那个电话号码最小的数。
又要用数字凑，又要最小，基本上确定了是一定要遍历（~~便秘~~），所以说，不用先进先出还怎么治好遍历？——（\*此处暗示指使用优先队列）

但是我不知道怎么拼priority\_queue，也不会拼operater，又发现好像单独的queue还好写点(_**划重点：** 主要是代码少_）

套用你自己独创的 《使queue真经——残本》 翻到那仅剩的半页;但是，如果两个不同滴树数同余了咋办(==....==)

于是乎：我们便有了vis数组（_\*bool型的桶，用以记录是否出现同余现象，同余就不push进Q里面酱紫的一个好东西……_)

但是有没有可能出现k≥m呢？

#### 答案是：我不知道，我也不想知道，因为在队列里，你不管怎么搜，一定在一位数搜完之前就可以搜到的，所以，m与k的关系是啥，与我无关！ 

接下来
### ——放代码！！：
```cpp
#include<bits/stdc++.h>
#define ll register int 
#define R __int128
#define mod 20070707
#define maxs 20070707

using namespace std;

queue<R> Q;
int ans[100001]={0};
bool vis[1000001]={0};

int main(){//freopen(".in","r",stdin);freopen(".out","w",stdout);
	ll k,m;
	scanf("%d%d",&k,&m);
	
	for(ll i=1;i<=k-1;i++){
		Q.push(i);
		vis[i%m]=1;
		if(i%m==0)
			return printf("%d",i),0;
	}
	while(!Q.empty()){
		R x=Q.front();
		for(ll i=0;i<=k-1;i++){
			R box=10*x+i;
			if(box%m==0){
				int len=0;
				while(box)
					ans[++len]=box%10,box/=10;
				for(ll i=len;i>=1;i--)printf("%d",ans[i]);
				return 0;
			}
			if(!vis[box%m])vis[box%m]=1,Q.push(box);
		}
		Q.pop();
	}
	return 0;
}

```
码风不洗勿喷。
谢谢管理员大大提醒！（——才得以修改好排版）
又改了一遍，终于改好了，真是欲哭无泪啊……

---

## 作者：BFSBFSBFSBFS (赞：6)

~~为什么要卡极限...~~

题意.用$0$到$k-1$组成数字最小,且能被m整除的数.

搜索方法另1篇说的很清楚了..

因为$(x*k+y)\ mod\ m = ((x\ mod\ m)*k+y)\ mod\ m$.

如果$x\ mod\ m\ =\ x1\ mod\ m\ $.则有$\ (x*k+y)\ mod\ m = (x1*k+y)\ mod\ m$.

这里$k=10$.$\ y$是枚举的数字.

2个数得出的取模结果是1样的..

所以只要记录余数相同的数中最小的那个就行了..

另外.数据$2\ \ 999$.会输出27个$1$...

另1篇题解用字符串存储.只用$mod\ m$的值运算.避免了高精..

~~所以我诚实的写了高精..~~

复杂度略高于$O(m)$.

Diu代码..

```cpp
program P1062;
 type
  gg=record
   f:array[1..101] of longint;               //高精数组..
   s:longint;                                //高精位数..
  end;
 var
  f:array[-1..1000] of longint;
  b,c:array[0..1001] of gg;
  i,j,k,k1,m,o,p,upass,mot:longint;
  pc:qword;
 operator mod(a:gg;b:longint)p:longint;      //高精取模..
  var
   i:longint;
  begin
   p:=0;
   for i:=a.s downto 1 do
    p:=(p*10+a.f[i]) mod b;
  end;
 begin
  readln(k,m);
  o:=0;
  p:=0;
  filldword(f,length(f),0);               //取模值的标记..
  for i:=1 to k-1 do                      //初始化的1位数..
   if f[i mod m]=0 then
    begin
     inc(p);
     b[p].s:=1;
     b[p].f[b[p].s]:=i;
     f[b[p] mod m]:=1;
     if b[p] mod m=0 then break;
    end;
  if f[0]=1 then upass:=1                 //找到解的标记..
            else upass:=0;
  repeat
   inc(o);
   if upass=1 then break;
   for j:=0 to k-1 do                     //枚举下1位可能的数..
    begin                                   //从小到大可以保证是最小解..
     inc(p);
     for k1:=b[o].s+1 downto 2 do         //高精*10,就是数组右移1位..
      b[p].f[k1]:=b[o].f[k1-1];
     b[p].f[1]:=j;                        //加上枚举的j.
     b[p].s:=b[o].s+1;
     if f[b[p] mod m]=1 then dec(p)       //如果取模的值已出现.舍弃.
                        else f[b[p] mod m]:=1;  //标记..
     if f[0]=1 then                       //说明能被整除..
      begin
       upass:=1;
       break;
      end;
    end;
  until o=p;
  for i:=b[p].s downto 1 do
   write(b[p].f[i]);
  writeln;
 end.
```
(ಡωಡ).


---

## 作者：Juseph·Juestar (赞：3)

看完题可以知道搜索是跑不掉的了  
那么先来个暴力，打个表找个规律

```cpp
bool check(int c) {
    while (c) {
        if (c % 10 >= k)
            return true;
        c /= 10;
    }
    return false;
}

int main() {
	k = 2;
	for(int m = 1; m <= 1000; ++m) {
   		int cur = m;
		while(check(cur)){
      			cur += m;
         		if(cur > 1E11) {
                		cout << m << " : Fail" << endl;
                		break;
                	}
      		}
   	}
	return 0;
}
```
为了能出结果，直接在1E11处剪掉  
然后非常愉快地，发现$k>3$的时候直接全出解了  
$k=3$时只有 $m = 999$ 会超范围  
$k = 2$ 时候有很多搜不出来  
那么这两个直接换一种方法搜  
生成各位上仅含0，1的数（$k = 3$类似）  
然后判断是否能被 $m$ 整除
数量仅有 $2^n$ 个  
$n$ 为了支持取模操作，为LL范围下的最大值位数，18  
如下
```cpp
int dfs(int sum, int cur) {
    if (!cur) {
        if (0 == sum % m) {
            return sum;
        } else {
            return 0;
        }
    }

    int tmp = dfs(sum, cur / 10);
    if (tmp)
        return tmp;
    tmp = dfs(sum + cur, cur / 10);
    return tmp;
}
```

这么再筛一次，只剩下四个解决不了的数爆了LL  
分别是 396，594，792，999  
这四个数水过去的方法很多  
要么把范围开成INT128就能出    

或者推一下可以看出  
前三个就是在 $\frac{m}{2}$ 的基础上在末尾补0  
而999可以从  
9 ~ 11111  
99 ~ 1111111111  
合理猜测 999 ~ 111111111111111  

  
至此数据范围要求内的问题已经完全解决  
分段处理即可

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define int long long

int k, m, c;

int dfs(int sum, int cur) {
    if (!cur) {
        if (0 == sum % m) {
            return sum;
        } else {
            return 0;
        }
    }

    int tmp = dfs(sum, cur / 10);
    if (tmp)
        return tmp;
    tmp = dfs(sum + cur, cur / 10);
    return tmp;
}

bool check(int c) {
    while (c) {
        if (c % 10 >= k)
            return true;
        c /= 10;
    }
    return false;
}

signed main() {
    scanf("%lld%lld", &k, &m);

    if (k >= 3) {
        if (3 == k && 999 == m) {
            printf("111222222222222\n");
            return 0;
        }
        c = m;
        while (check(c)) {
            c += m;
        }
        printf("%lld\n", c);
    } else {
        if(999 == m) {
            printf("111111111111111111111111111\n");
            return 0;
        }
        if (396 == m) {
            m = 198;
            printf("%lld0\n", dfs(0, 1E18));
            return 0;
        }
        if (594 == m) {
            m = 297;
            printf("%lld0\n", dfs(0, 1E18));
            return 0;
        }
        if (792 == m) {
            m = 198;
            printf("%lld00\n", dfs(0, 1E18));
            return 0;
        }

        printf("%lld\n", dfs(0, 1E18));
    }

    return 0;
}

```
  
  
   
   这么做就不用动脑子了，令人愉悦


---

## 作者：Frozen_Ladybug (赞：2)

此题有坑:  
爆long longlonglong,这个简单\_\_int128__int128或者高精度  
如果用\_\_int128__int128记得手写输出就好   
这道题其实还可以
高精度很简单
```c
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef __int128 ll;
int out[32],p;
inline void write(ll x){
    p=0;
    if(x==0)out[++p] = 0;
    while(x){
        out[++p] = x % 10;
        x/=10;
    }
    for(int i=p;i>=1;i--)putchar(out[i]+'0');
}
queue<ll> Q;
int k,m,vis[1024];
int main(){
    scanf("%d%d",&k,&m);
    for(int i=1;i<k;i++)Q.push(ll(i));
    while(!Q.empty()){
        ll x=Q.front();Q.pop();
        if(x%m==0)return write(x),putchar('\n'),0;
        vis[x%m] = 1;
        for(int i=0;i<k;i++)if(!vis[(x*10+i)%m])Q.push(x*10+i);
    }
    return 0;
}
```


---

## 作者：inexistent (赞：2)

**本题可以避免任何字符串的处理**

思路基本上和其他题解一样，只是在广搜的过程中不需要每一次更新一个新的字符串来记录，只需要在bfs过程（bfs可以保证搜索按从小到大的顺序走）中记录当前添加的这一位，最后倒着打出答案就可以了。这样可以优化空间。

贴上代码。。。

```cpp
/*This Program is written by QiXingZhi*/
#include <cstdio>
#define  N    (100010)
#define  ll    long long
#define  INF    (0x7f7f7f7f)
#define  Max(a,b)    (((a) > (b)) ? (a) : (b))
#define  Min(a,b)    (((a) < (b)) ? (a) : (b))
#define  FILE_IN(x)    freopen(x".in","r",stdin)
#define  FILE(x)       freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using namespace std;

inline void read(int &x){
    int w = 1; register char c = 0; x = 0;
    while (c ^ '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') w = -1, c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
    x = x * w;
}
struct Obj{//md表示当前数字mod m之后的余数，v记录添加
//的这一位，f表示其承接的父亲 
	int md,v,f;
};
int k,m,h,t,tmp;
Obj q[10010];
bool b[10010];
void _print(int x){
	if(x == 0) return;
	_print(q[x].f);//递归完成打印 
	printf("%d",q[x].v);
}
int main(){
	read(k),read(m);
	for(int i = 1; i < k; ++i){
		if(i % m == 0){
			printf("%d",i);
			return 0;
		}
		else{
			//不要忽略个位的 
			++t;
			q[t].md = i % m;
			b[q[t].md] == 1;
			q[t].v = i;
			q[t].f = 0;
		}
	}
	while(h < t){
		++h;
		for(int i = 0; i < k; ++i){
			tmp = ((q[h].md * 10)%m + i) % m;
			if(b[tmp]) continue;
			++t;
			q[t].md = tmp;
			b[tmp] = 1;
			q[t].v = i;
			q[t].f = h;
			if(q[t].md % m == 0){
				//找到符合要求的答案 
				_print(t);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：CE_自动机 (赞：1)

看了好多题解，基本上用的都是 $DFS$ 和 $BFS$，我太菜了，看不懂，考虑使用数位 $DP$

状态还是比较明显的，$f[i][j][k]$ 表示前 $i$ 位，第 $i$ 位的数字为 $j$，并且当前余数为k的状态是否存在，所以它是一个布尔类型的变量。同时这道题需要知道具体的方案，反映在 $DP$ 中就是转移的路径，用 $pre[i][j][k][0/1]$ 维护转移路径，其中 $i,j,k$ 的含义与前者相同， $pre[...][0]$表示它的下一位的数字，$pre[...][1]$ 表示它的下一位的余数（这个状态是冗余的，主要是方便我思考）。

采用“刷”的方式，文字不好叙述，但看代码~~应该~~比较清晰。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e3+100;

int k,m;
bool f[N][10][N];
int pre[N][10][N][2];
int fc[N];

int read(){
	int x=0;
	char ch=getchar();
	while(!isdigit(ch)){ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}

void deal(int i,int j){
	int t=j,p=0;
	for(register int l=i;l>=1;--l){
		printf("%d",t);
		int p1=p;
		p=pre[l][t][p1][1];
		t=pre[l][t][p1][0];
	}
}

int main(){
	k=read();m=read();
	fc[1]=1;
	for(register int i=2;i<=m;++i)fc[i]=fc[i-1]*10%m;
	for(register int i=0;i<k;++i)f[1][i][i]=1;
	for(register int i=2;i<=m;++i){//枚举位数
		for(register int x=0;x<k;++x){//枚举这一位数字
			for(register int y=0;y<k;++y){//枚举上一位数字
				for(register int j=0;j<m;++j){//枚举上一位数字处理完后的余数
					if(f[i-1][y][j]){
						int t=(x*fc[i]+j)%m;//上一位能刷的状态
						f[i][x][t]=1;
						if(!pre[i][x][t][0]){//维护前驱，并且是最小值
							pre[i][x][t][0]=y;
							pre[i][x][t][1]=j;
						}
						if(t==0&&x!=0){//遇到的第一个余数为零的（满足首位不为零）
							deal(i,x);
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}
```

~~时间复杂度不会证，那你能帮帮我吗~~


---

## 作者：lych (赞：0)

本题可以用暴力解决，可以过掉80%的点。其实，对于100%的数据，只要设法减掉原有算法的冗余，就可以用0(M)的时间复杂度过掉。对于本题数据，绝对是0ms秒过。


其实本题就是用广度优先搜索。为什么这么说呢？因为我们在深搜枚举一个数的时候，当它对M取模时，很多都是可以提前判断出来的。就没有必要继续深搜下去。而我们采用广搜，运用队列技术，尽一切可能减少所有可以减少而又不会影响正确答案的冗余。


接下来给出标程：

```delphi
var
  m,n,k,head,tail,i:longint;
  f:array[0..1000] of boolean;
  q:array[0..1000] of longint;
  h:array[0..1000] of string;
  s,s1:string;
begin
  readln(n,m);
  for i:=1 to n-1 do
    begin
      str(i,h[i]);//转化到队列中
      q[i]:=i mod m;//q表示的是它对M取模的余数
      f[q[i]]:=true;//已经使用过了，数组关闭，防止冗余
    end;//读入
  tail:=n-1;
  while head<tail do
    begin
      inc(head);
      s:=h[head];//把这个数取出来
      for i:=0 to n-1 do//在后面添加数，一定要顺序循环，保证小的数一定比大的数优先搜到
        begin
          k:=(q[head]*10+i) mod m;//余数是多少
          str(i,s1);//转化到字符串中，方便后面的添加新数
          if k=0 then
            begin
              writeln(s+s1);
              halt;//找到解，立刻退出
            end else
              if not(f[k]) then//还没有被搜到过
                begin
                  f[k]:=true;//已被搜到
                  inc(tail);//队列添加一个元素
                  q[tail]:=k;
                  h[tail]:=s+s1;
                end;
        end;
    end;
end.
```

---

