# A*B Problem

## 题目描述

给出一个数 $A$ ，你需要给出一个最小的数 $B$ ，使得 $A\times B$ 的结果只含有 $0$ 和 $1$ 。

## 说明/提示

样例说明：$6\times 185=1110$。

对于 $30\%$ 的数据，$0<A<20$。

对于 $50\%$ 的数据，$0<A<100$。

对于 $70\%$ 的数据，$0<A<1000$。

对于 $100\%$ 的数据，$0<A<10^4$。


## 样例 #1

### 输入

```
6```

### 输出

```
185 1110
```

# 题解

## 作者：唐一文 (赞：46)

## 前言
~~题解区里的方法都太深奥了，蒟蒻看不懂~~

------------

## 思路 && Code
受到[UVA1189](https://www.luogu.com.cn/problem/UVA1189)的启发，我们可以先求出$01$串，再算出$B$。

~~认为数据一定很水的我~~立马打了个$dfs$，开了个$longlong$准备水过去：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long minn=LONG_LONG_MAX;
void dfs(long long ans,int k){
    if(k==20){//超出long long范围
		return ;
	}
    if(ans>minn){//剪枝
		return ;
    }
    if(ans%n==0){
        minn=min(minn,ans);//求最小值
        return ;
    }
    dfs(10*ans,k+1);
    dfs(10*ans+1,k+1);
}
int main(){
    cin>>n;
    dfs(1,1);
    cout<<minn/n<<" "<<minn;
    return 0;
}
```
然而，是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/9r5frm9a.png)
$??!$  
还是老老实实打高精度吧

把高精度模板一套：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
inline int mod(string a1){//求余数
	register int i;
	int b=0,len=a1.size();
	for(i=0;i<len;++i){
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	return b;
}
inline string chu(string a1){//高精度除法
	register int i;
	int s[10001],b=0,len=a1.size();
	for(i=0;i<len;++i){
		s[i]=((b<<1)+(b<<3)+(a1[i]^48))/n;
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	i=0;
	while(!s[i] && i<len){
		++i;
	}
	a1="";
	while(i<len){
		a1+=s[i]+'0';
		++i;
	}
	return a1;
}
string minn;
inline bool pd(string x){//判断是否超过已找到的最小值
	int lx=x.size(),ly=minn.size();
	if(lx<ly){
		return false;
	}
	if(lx>ly){
		return true;
	}
	register int i;
	for(i=0;i<lx;++i){
		if(x[i]<minn[i]){
			return false;
		}
		else if(x[i]>minn[i]){
			return true;
		}
	}
	return false;
}
void dfs(string ans){
	if(pd(ans)){
		return ;
	}
	if(!mod(ans)){
		minn=ans;
		return ;
	}
	dfs(ans+"0");
	dfs(ans+"1");
}
int main(){
	register int i;
	scanf("%d",&n);
	for(i=1;i<37;++i){//1~9999中答案的最大值
    /*
    不难发现，n为9的倍数时，答案总是很大
    当n=9999时最大
    那么n=9*1111
    因为9|111111111
    有9个1
    而1111有4个1
    又因为4和9互质
    所以minn=111...111(4*9=36个1)
    */
		minn+="1";
	}
	dfs("1");
	cout<<chu(minn)<<" "<<minn;
	return 0;
}
```
内心想法：我终于又水过了一道~~水~~蓝题$!$
![](https://cdn.luogu.com.cn/upload/image_hosting/hc9ji1rf.png)
$What?$  
还会超时$?$

让我们重新看一下题目：  
给出一个数$A$，你需要给出一个**最小的**数$B$，使得$A$与$B$的乘积只含有$0$和$1$

在学搜索时，求**最小的答案**一般用$bfs$更快  
那么这题不就可以用$bfs$了吗

因为要求最小的，所以先插入$0$比先插入$1$更好  
找到的满足条件的第$1$个数就是$B$

把$dfs$改成$bfs$：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
inline int mod(string a1){
	register int i;
	int b=0,len=a1.size();
	for(i=0;i<len;++i){
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	return b;
}
inline string chu(string a1){
	register int i,j;
	int s[10001],b=0,len=a1.size();
	for(i=0;i<len;++i){
		s[i]=((b<<1)+(b<<3)+(a1[i]^48))/n;
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	i=0;
	while(!s[i] && i<len){
		++i;
	}
	a1="";
	while(i<len){
		a1+=s[i]+'0';
		++i;
	}
	return a1;
}
string p;
queue<string>q;
int main(){
	register int i;
	scanf("%d",&n);
    //以下代码为改动了一点的bfs模板
	p="1";
	q.push(p);
	while(!q.empty()){
		p=q.front();
		q.pop();
		if(!mod(p)){ 
			cout<<chu(p)<<" "<<p;
			return 0;
		}
		q.push(p+"0");
		q.push(p+"1");
	}
	return 0;
}
```
这次总能过了吧$?$
![](https://cdn.luogu.com.cn/upload/image_hosting/0xxsuiz3.png)
$Excuse\ me?$
![](https://cdn.luogu.com.cn/upload/image_hosting/1lp2xemc.png)
$MLE$是什么鬼$?!$

让我们手动模拟一下样例：
|$p$ |$mod$ |
| :----------: | :----------: |
|$1$ |$1$ |
|$10$ |$4$ |
|$11$ |$5$  |
|$100$  |$4$  |
|$101$  |$5$  |
|$110$  |$2$  |
|$111$  |$3$  |
|$1000$  |$4$  |
|$1001$  |$5$  |
|$1010$  |$2$  |
|$1011$  |$3$  |
|$1100$  |$2$  |
|$1101$  |$3$  |
|$1110$  |$0$  |
可以发现，有些数模$A$同余  
根据同余的性质可得，它们乘上同一个数后模$A$也同余  
因为要求最小的数，所以只要取这些数中最小的那一个数  
用一个$bool$数组即可实现

因为我们是从小到大搜索的  
所以第一个出现的数就是最小的那一个

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
inline int mod(string a1){
	register int i;
	int b=0,len=a1.size();
	for(i=0;i<len;++i){
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	return b;
}
inline string chu(string a1){
	register int i,j;
	int s[10001],b=0,len=a1.size();
	for(i=0;i<len;++i){
		s[i]=((b<<1)+(b<<3)+(a1[i]^48))/n;
		b=((b<<1)+(b<<3)+(a1[i]^48))%n;
	}
	i=0;
	while(!s[i] && i<len){
		++i;
	}
	a1="";
	while(i<len){
		a1+=s[i]+'0';
		++i;
	}
	return a1;
}
string p;
bool v[10005];//判断是否重复出现余数
queue<string>q;
int main(){
	register int i;
	scanf("%d",&n);
	p="1";
	q.push(p);
	while(!q.empty()){
		p=q.front();
		q.pop();
		if(!mod(p)){ 
			cout<<chu(p)<<" "<<p;
			return 0;
		}
        if(!v[mod(p+"0")]){//如果没有出现过这个余数
		    v[mod(p+"0")]=true;//这个数为最小的那一个，这个余数现在出现了，标记为true
            q.push(p+"0");
        }
        if(!v[mod(p+"1")]){//同上
            v[mod(p+"1")]=true;
		    q.push(p+"1");
        }
	}
	return 0;
}
```
（° - °)ノ✿ 完结撒花~

---

## 作者：zhouyuheng2003 (赞：32)

这道题只有一个P党的题解，那我就来一发C++的吧，习惯用指针，虽然代码可能写的不是很规范（变量想不好取什么名字），第一次写题解，请多见谅

本题刚看的时候想随便想个算法，然后发现

###要爆long long

写高精太麻烦，咋办，偷个懒，到最后再化成高精吧

一个**贪心**（贪心？也许不是）**假如有两个数模A余数相等，那就取小的那个**

所以理论状态小于10000

BFS一发，别忘了**最高位取0也要更新状态**，以便于到时候输出的时候能正确的回溯，输出

好吧，讲的不多，贴一波代码

```cpp
#include<cstdio>
const int max=100000;//数组随便开 
int A; 
int las[max+1],Hash[10000];//las记录第i位取1时模A的余数，Hash去重（相同的余数肯定取小的优） 
struct Kind
{
    int sum,num,rem;//当前位数，当前位取值，当前状态余数 
    Kind *bef;//方便输出，指向该状态从哪里来 
}Q[max];
int main()
{
    scanf("%d",&A);//输入 
    if(A==1)//特判A=1的情况 
    {
        printf("1 1");
        return 0;
    }
    las[1]=1;
    for(int i=2;i<=max;i++)
        las[i]=las[i-1]*10%A;//统计第i位取1时模A的余数
    int l=0,r=2;//BFS的队列指针 
    Q[1].num=0,Q[1].rem=0,Q[1].sum=1,Q[1].bef=&Q[0];//初始状态 
    Q[2].num=1,Q[2].rem=1,Q[2].sum=1,Q[2].bef=&Q[0];
    Hash[1]=1;//余数为一已经取到过 
    while(l<r)
    {
        l++;
        Kind u=Q[l],v=u;
        v.num=0,v.sum++,v.bef=&Q[l];
        Q[++r]=v;//最高位取0状态转移 
        v=u;
        v.num=1,v.sum++,v.bef=&Q[l],v.rem=(v.rem+las[v.sum])%A;//最高位取1 
        if(v.rem==0)//找到答案 
        {
            Kind *i=&v;
            int yu=0,fla=0;
            while(i->sum!=0)//回溯，类似于高精一样的除法然后输出 
            {
                yu=yu*10+i->num;
                if(yu/A!=0||fla)
                    printf("%d",yu/A,fla=1);
                yu%=A;
                i=i->bef;
            } 
            putchar(' ');
            i=&v;
            while(i->sum!=0)
            {
                printf("%d",i->num);//输出乘积 
                i=i->bef;
            } 
            return 0;
        }
        if(Hash[v.rem]==0)//余数不为0，且该余数之前未出现过 
        {
            Hash[v.rem]=1;
            Q[++r]=v;
        }
    }
    return 0;
}
```

---

## 作者：Pecco (赞：16)

怎么都是BFS？这个题其实可以DP的。

设 $A\times B=C$，我们知道$C\equiv0\pmod A$。分别考虑模$A$意义下 $1,10,100,\dots$ 的值，我们要做的就是从中选取若干个数，使它们加起来在模$A$意义下为0，并且要让这个数最小。

这个显然可以用dp来做，设`dp[i]`为模$A$意义下等于$i$的最小01串，那么只要我们一位一位推就一定能得到最小值（道理很简单：如果在千位就得到答案，那何必考虑万位）。同时，如果在考虑某一位时得到了一个解，那它一定就是最优解。

例如$A=7$时，一开始`dp`为`{0:0}`，因为$1\bmod 7=1$，所以插入`1:1`；因为$10\bmod7=3$，所以插入`3:10`和`4:11`；因为$100\bmod7=2$，所以插入`2:100`、`3:101`、`5:110`和`6:111`。然后$1000\bmod7=6$，发现与已有的`1:1`加起来模7为0，所以答案就是1000+1=1001。

本来以为要开高精，用Python写的，后来发现所有解都在128位整数范围内，就直接用int128过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
unordered_map<int, i128> dp{{0, 0}};
void print(i128 x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    int A, curm = 1;
    i128 cur = 1;
    cin >> A;
    for (;;)
    {
        vector<pair<int, i128>> v;
        for (auto pr : dp)
        {
            i128 x = pr.second + cur;
            int xm = (pr.first + curm) % A;
            if (xm == 0)
            {
                print(x / A), putchar(' '), print(x);
                return 0;
            }
            else if (!dp.count(xm))
                v.push_back(make_pair(xm, x));
        }
        for (auto &&p : v)
            dp.insert(p);
        cur *= 10, (curm *= 10) %= A;
    }
    return 0;
}
```

---

## 作者：F3_Dy (赞：7)

这道题真的是一道非常有趣的搜索题呢，非常适合使用迭代加深搜索来解决这个问题。

 **不过看到题解里没有人用迭代加深搜索方法来解这道题，那就我来介绍一下迭代加深搜索的写法!**

一般人都会想到这道题的一种搜索写法：枚举$a \times b$的最小值，然后据此输出$b$的数值，即可解决问题。但大家可以很明显的注意到，如果使用宽度优先搜索，很可能会有爆空间的风险；如果使用深度优先搜索，则因搜索深度无上限而不可行。

这时候，我们就可以考虑一下：

### 迭代加深搜索！

## 1.题意分析

对于本题而言：由于$a \times b$的规模有限，而且$a \times b$一定是由$0$和$1$两种数字组成，所以使用搜索时解答树并不会过于庞大。因为题意要求找到最小的$b$，而$a$为定值，则只要找到最小的$a \times b$时，$b$也会最小。

于是，我们可以将本题的题意改写为：找到一个最小的$a \times b$，使得$a \times b\ \% \ a =0$。

## 2.迭代加深搜索

所谓迭代加深搜索，就是一个对于深度优先搜索的一个优化。我们考虑从小到大枚举深度优先搜索的深度上限$maxd$，每次执行只考虑深度不超过$maxd$的结点。这样，只要解的深度有限，则一定可以在有限时间内枚举到。

## 3.一些优化

有了这样的思路，我们可以轻松拿到$80$分的好成绩。我们接下来考虑如何剪枝。我们可以对当前每一个搜索状态的当前成果进行研究：如果一个状态深度比当前深度浅，或者对应$a \times b$数值比当前小，且对$a$取模的数值相同，则当前状态不可能是最优解。

这样，我们可以写出如下代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,d;
int b[100010];
int m[10010];
int cnt(int x)
{
    if(!x) return 0;
    return cnt(x/10)+1;
}
int dfs(int dep,int o)
{
    if(dep>d)
    {
        if(o==0)
        {
            int f=0,c=0;
            for(int i=1;i<=d;i++)
            {
                c=c*10+b[i];
                if(c>=a)
                {
                    f=1;
                }
                if(f)
                {
                    printf("%d",c/a);
                }
                c%=a;
            }
            printf(" ");
            for(int i=1;i<=d;i++)
            {
                printf("%d",b[i]);
            }
            printf("\n",c/a);
            return 1;
        }
        return 0;
    }
    if(m[o]<=dep&&m[o])
    {
        return 0;
    }
    m[o]=dep;
    if(dep!=1)
    {
        b[dep]=0;
        if(dfs(dep+1,o*10%a))
        {
            return 1;
        }
    }
    b[dep]=1;
    return dfs(dep+1,(o*10+1)%a);
}
void iddfs()
{
    for(d=cnt(a);;d++)
    {
        fill(m,m+a,0);
        if(dfs(1,0))
        {
            break;
        }
    }
}
int main()
{
    cin>>a;
    iddfs();
    return 0;
}

```


---

## 作者：飞翔 (赞：5)

给我的博客打个广告~欢迎来踩~

[戳我哟](http://blog.csdn.net/qq\_31640513/article/details/52351702)

【分析】

首先想到的是穷举2进制01串，但这样肯定会超时。

可以根据二进制01串（作为十进制数运算）除以A的余数进行递推，因为如果两个位数相同的01串除以A的余数相同，则在它们的最高位前再加个1后，两个新的01串除以A的余数仍然相同。而题目求的是最小的01串，故只需记录值较小的01串即可。

再利用mod运算的两个性质：

(a\*b) mod n=(a mod n)×(b mod n) 

10^k mod n=(…(((10 mod n)×10) mod n)×10…) mod 10 

高精度运算就可以避免了。

```pascal
var
  i,n,k,len,r,tmpf,tmpl:longint;
    flag:boolean;
    long,father:array[0..10000]of longint;
begin
  read(n);
    if n=1 then begin write(1,' ',1);halt; end;
    fillchar(father,sizeof(father),0);
    fillchar(long,sizeof(long),0);
    long[1]:=1;
    r:=1;
    len:=1;
    while long[0]=0 do begin
      r:=r*10 mod n;
        inc(len);
        for i:=0 to n-1 do
          if (i=0) or (long[i]>0) and (long[i]<len) then begin
              k:=i+r;
                if k>=n then k:=k-n;
                if long[k]=0 then begin
                  long[k]:=len;
                    father[k]:=i;
                end;
            end;
    end;
    k:=father[0];
    tmpf:=k;
    tmpl:=len;
    father[0]:=-1;
    long[0]:=0;
    r:=0;
    flag:=true;
    while k>=0 do begin
      r:=r*10+1;
        if r div n>0 then begin
          write(r div n);
            flag:=false;
        end;
        if (r div n=0)and(flag=false) then write(0);
        r:=r mod n;
        for i:=len-1 downto long[k]+1 do begin
          r:=r*10;
            if r div n>0 then begin
              write(r div n);
                flag:=false;
            end;
            if (r div n=0)and(flag=false) then write(0);
            r:=r mod n;
        end;
        len:=long[k];
        k:=father[k];
    end;
    write(' ');
    k:=tmpf;
    len:=tmpl;
    father[0]:=-1;
    long[0]:=0;
    while k>=0 do begin
      write(1);
        for i:=len-1 downto long[k]+1 do write(0);
        len:=long[k];
        k:=father[k];
    end;
end.
```

---

## 作者：chenxuanting (赞：4)

当我看到这道题时，我第一个蹦出来的思路是：bfs01串

于是我用结构体记录每个数的数字和余数（因为可能有高精）

```
struct node
{
	string num;//数字串
	int remain;//余数
};
```

之后用bfs算出结果后，在写~~套~~上高精除低精模板即可

于是我兴高采烈的打完了代码然后提交了上去

（终极代码有注释）

```
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int a;
struct node
{
	string num;
	int remain;
};
queue<node> q; 
string ans;
int final[10005];
int use,use1,usage;
int main()
{
	cin>>a;
	if(a==1){
		cout<<"1 1";
		return 0;
	}
	q.push((node){"1",1});
	while(!q.empty()){
		node x=q.front();
		q.pop();
		if((10*x.remain)%a==0){
			ans=(x.num+"0");
			break;
		}
		if((10*x.remain+1)%a==0){
			ans=(x.num+"1");
			break;
		}
		q.push((node){x.num+"0",10*x.remain});
		q.push((node){x.num+"1",10*x.remain+1});
	}
	int n1=ans.size();
	for(int i=0;i<n1;i++){
		use*=10;
		use+=(ans[i]-48);
	    if((use/a)!=0){
		    use1+=1;
	    }
	    if(use1==0){
		    continue;
	    }
	    usage+=1;
	    final[usage]=(use/a);
	    use%=a;
	}
	for(int i=1;i<=usage;i++){
		cout<<final[i];
	}
	cout<<" "<<ans;
	return 0;
} 
```


看着一个个蹦出来的AC，心里想着：又要水过一道蓝题了

结果：5AC 5WA

[错误记录1](https://www.luogu.com.cn/record/31088115)

？？？？？？

什么玩意儿

于是我去问了老师

结果老师曰：自己慢慢找 最近在家待得脑壳疼. 

然后我自己找了半天终于，看到了一个可能有错的地方。

于是我改了然后提交了上去

```
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int a;
struct node
{
	string num;
	int remain;
};
queue<node> q; 
string ans;
int final[10005];
int use,use1,usage;
int main()
{
	cin>>a;
	if(a==1){
		cout<<"1 1";
		return 0;
	}
	q.push((node){"1",1});
	while(!q.empty()){
		node x=q.front();
		q.pop();
		if((10*x.remain)%a==0){
			ans=(x.num+"0");
			break;
		}
		if((10*x.remain+1)%a==0){
			ans=(x.num+"1");
			break;
		}
		q.push((node){x.num+"0",(10*x.remain)%a});//看这里
		q.push((node){x.num+"1",(10*x.remain+1)%a});//看这里
	}
	int n1=ans.size();
	for(int i=0;i<n1;i++){
		use*=10;
		use+=(ans[i]-48);
	    if((use/a)!=0){
		    use1+=1;
	    }
	    if(use1==0){
		    continue;
	    }
	    usage+=1;
	    final[usage]=(use/a);
	    use%=a;
	}
	for(int i=1;i<=usage;i++){
		cout<<final[i];
	}
	cout<<" "<<ans;
	return 0;
} 
```


于是

8AC 2MLE

~~掀桌~~

接着再改一下就过了

用appear数组表示这个余数是否出现过

出现过就下一个数

没出现过就入队，并标记这个appear为1

终极代码：

```
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int a;
struct node
{
	string num;//数字串
	int remain;//余数
};
queue<node> q; 
string ans;//最终答案01串
int final[10005];//表示b的数组
int use,use1,usage;
int appear[10005];
int main()
{
	cin>>a;
	if(a==1){//特判
		cout<<"1 1";
		return 0;
	}
	q.push((node){"1",1});
	appear[1]=1;
	while(!q.empty()){
		node x=q.front();
		q.pop();
		if((10*x.remain)%a==0){//如果余数为1
			ans=(x.num+"0");//记录答案
			break;
		}
		if((10*x.remain+1)%a==0){
			ans=(x.num+"1");
			break;
		}
		if(appear[(10*x.remain)%a]==0){//判断是否出现
			appear[(10*x.remain)%a]=1;//记录
			q.push((node){x.num+"0",(10*x.remain)%a});//入队
		}
		if(appear[(10*x.remain+1)%a]==0){
			appear[(10*x.remain+1)%a]=1;//记录
			q.push((node){x.num+"1",(10*x.remain+1)%a});//入队
		}
	}
   //下面是高精除单精
	int n1=ans.size();
	for(int i=0;i<n1;i++){
		use*=10;
		use+=(ans[i]-48);
	    if((use/a)!=0){
		    use1+=1;
	    }
	    if(use1==0){
		    continue;
	    }
	    usage+=1;
	    final[usage]=(use/a);
	    use%=a;
	}
	for(int i=1;i<=usage;i++){
		cout<<final[i];
	}
	cout<<" "<<ans;//输出01串
	return 0;
} 
```

圆满结束

莫抄袭，没了AC记录，空悲切

求求管理员通过一下吧

我已经有5篇题解没有通过了o(╥﹏╥)o



---

## 作者：比利♂海灵顿 (赞：4)

# P2841 A*B Problem

这是一篇高精度 DP 的题解。

## 题目大意

给一个数 $A$，找出最小的 $B$ 使得 $A*B$ 的十进制表示中只包含 $0$ 和 $1$。

## DP 设计

一看到这个题，想到的是从低位到高位确定 $B$，因为 $B$ 的高位无法影响 $A * B$ 的低位，积的低位和 $B$ 的高位无关恰恰就是 DP 无后效性的原则。

设计状态 $f_{i, j}$ 表示已经确定了 $B$ 最低的 $i$ 位，记作 $B'$，并且 $B'$ 满足 $A*B'$ 最低的 $i$ 位只有 $0$ 和 $1$，还满足 $\lfloor \frac {A*B'}{10^i} \rfloor = j$ 的最小的 $B'$。转移很显然：

$$
f_{i, \lfloor \frac {j + kn}{10}\rfloor} = \min_{(j + kn) \mod 10 < 2} f_{i - 1, j} + k10^i
$$

转移的意义是在保证第 $i$ 低位小于 $2$ 的前提下，尽可能最小化 $B'$. 每次 DP 完一个阶段 $i$, 寻找是否存在十进制表示是由 $0$ 和 $1$ 组成的 $j$, 满足 $f_{i, j} < \infin$。

## 代码实现

需要用到的高精计算是：高精度加法，高精乘低精，高精度比较。写一个大整数类解决之。

```cpp
struct BI {
  unsigned Len;
  char a[205];
  inline BI() { Len = 1; a[0] = 0; }
  inline void Prt() {
    for (unsigned i(Len - 1); ~i; --i) putchar('0' + a[i]);
  }
  inline void Big() { Len = 200, a[199] = 1; }
  inline void operator = (unsigned x) {
    a[0] = 0;
    for (Len = 1; x; x /= 10, ++Len) a[Len - 1] = x % 10;
    if (Len > 1)--Len;
  }
  const inline char operator <(const BI& x) {
    if (Len ^ x.Len) return Len < x.Len;
    for (unsigned i(Len - 1); ~i; --i) if (a[i] ^ x.a[i]) return a[i] < x.a[i];
    return 0;
  }
  inline BI operator +(const BI& x) {
    BI Rt(x);
    char Up(0);
    for (unsigned i(max(Len, Rt.Len) + 1); i >= Rt.Len; --i) Rt.a[i] = 0;
    Rt.Len = max(Len, Rt.Len) + 1;
    for (unsigned i(0); i < Len; ++i) {
      Rt.a[i] += a[i] + Up, Up = 0;
      while (Rt.a[i] >= 10) Rt.a[i] -= 10, ++Up;
    }
    for (unsigned i(Len); i < Rt.Len && Up; ++i) {
      Rt.a[i] += Up, Up = 0;
      while (Rt.a[i] >= 10) Rt.a[i] -= 10, ++Up;
    }
    while (Up) {
      Rt.a[Rt.Len] = Up, Up = 0;
      while (a[Rt.Len] >= 10) Rt.a[Rt.Len] -= 10, ++Up;
      ++(Rt.Len);
    }
    while ((!(Rt.a[Rt.Len - 1])) && (Rt.Len > 1)) --(Rt.Len);
    return Rt;
  }
  inline BI operator *(const unsigned& x) {
    BI Rt(*this);
    unsigned MuT(0);
    for (unsigned i(Len); i <= 200; ++i) Rt.a[i] = 0;
    for (unsigned i(0); i < Len; ++i) MuT += a[i] * x, Rt.a[i] = MuT % 10, MuT /= 10;
    while (MuT) Rt.a[(Rt.Len)++] = MuT % 10, MuT /= 10;
    return Rt;
  }
}f[2][10005], Ten[205], Ans;
inline BI Suf(unsigned x, unsigned y) {
  BI Rt;
  Rt.Len = y + 1;
  for (unsigned i(0); i <= y; ++i) Rt.a[i] = 0;
  Rt.a[y] = x;
  return Rt;
}
const unsigned Fin[2][10] = { {0, 9, 8, 7, 6, 5, 4, 3, 2, 1},{1, 0, 9, 8, 7, 6, 5, 4, 3, 2} };
unsigned D, t, n;
unsigned Cnt(0), Len(0);
set<unsigned long long> Tai[10];
bitset <10005> OK;
signed main() {
  n = RD(), OK[0] = 1, Ans.Big();
  for (unsigned i(1); i <= n; ++i) OK[i] = (OK[i / 10] & ((i % 10) < 2));
  if (OK[n]) { printf("1 %u\n", n);return 0; }
  for (unsigned i(0); i <= 200; ++i) Ten[i].Len = i + 1, Ten[i].a[i] = 1;
  for (unsigned i(0); i < 10; ++i) Tai[(n * i) % 10].insert(i);
  for (unsigned i(0); i <= n; ++i) f[0][i].Big();
  for (auto i : Tai[0]) f[0][i * n / 10] = i;
  for (auto i : Tai[1]) f[0][i * n / 10] = i;
  while (1) {
    for (unsigned i(1); i <= n; ++i) if (OK[i] & (f[Len & 1][i] < Ten[199])) if (f[Len & 1][i] < Ans) Ans = f[Len & 1][i];
    if (Ans < Ten[199]) break;
    ++Len;
    for (unsigned i(0); i <= n; ++i) f[Len & 1][i].Big();
    for (unsigned i(0); i <= n; ++i) {
      for (auto j : Tai[Fin[0][i % 10]]) {
        unsigned Des((j * n + i) / 10);
        BI Tmp(f[(Len & 1) ^ 1][i] + Suf(j, Len));
        if (Tmp < f[Len & 1][Des]) f[Len & 1][Des] = Tmp;
      }
      for (auto j : Tai[Fin[1][i % 10]]) {
        unsigned Des((j * n + i) / 10);
        BI Tmp(f[(Len & 1) ^ 1][i] + Suf(j, Len));
        if (Tmp < f[Len & 1][Des]) f[Len & 1][Des] = Tmp;
      }
    }
  }
  Ans.Prt(), putchar(' '), (Ans * n).Prt(), putchar(0x0A);
  return Wild_Donkey;
}
```

---

