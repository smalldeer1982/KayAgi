# Kefa and First Steps

## 题目描述

Kefa decided to make some money doing business on the Internet for exactly $ n $ days. He knows that on the $ i $ -th day ( $ 1<=i<=n $ ) he makes $ a_{i} $ money. Kefa loves progress, that's why he wants to know the length of the maximum non-decreasing subsegment in sequence $ a_{i} $ . Let us remind you that the subsegment of the sequence is its continuous fragment. A subsegment of numbers is called non-decreasing if all numbers in it follow in the non-decreasing order.

Help Kefa cope with this task!

## 说明/提示

In the first test the maximum non-decreasing subsegment is the numbers from the third to the fifth one.

In the second test the maximum non-decreasing subsegment is the numbers from the first to the third one.

## 样例 #1

### 输入

```
6
2 2 1 3 4 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
3
2 2 9
```

### 输出

```
3```

# 题解

## 作者：happybob (赞：2)

这题要注意的是不下降子段相邻两个数对比相等也是不下降。

总体来讲一点都不难……

看AC代码：
```cpp
#include <iostream>//输入输出流
using namespace std;

int main()
{
    int n, cnt = 1, ans = 1;//注意cnt和ans都要赋值为1，第一次ans写了0第9个测试点没过
    //为什么cnt是1？
    //任何一串数字都有至少一个不下降子段
    //比如：
    // 1 0 -1 -2 -3 -4 -5
    //那1也是一个不下降子段的数字
    //所以一开始也要赋值为1

    //那ans为什么也要是1？
    //如果ans = 0
    //继续用 1 0 -1 -2 -3 -4 -5举例
    //先看下面循环
    //按照循环会判断 0 是否 >= 1
    //肯定进入else
    //后面判断全else
    //所以输出0
    //但实际上0就是一个不下降子段，应该输出1
    
    cin >> n;
    int num[n];//开数组，尽量要多大开多大吧，不要浪费空间
    //int num[100001]
    //这么些也行，多出的空间就没用了
    for(int i = 0; i < n; i++)
    {
        cin >> num[i];//循环输入
    }
    for(int i = 0; i < n - 1; i++)//注意循环次数 < n - 1
    {
        if(num[i + 1] >= num[i])//如果不下降
        {
            cnt++;//计数器自增1
            ans = cnt > ans ? cnt : ans;//三目运算
            //如果cnt > ans，ans = cnt。
            //否则，ans 还是 ans。
        }
        else
        {
            cnt = 1;//如果不下降，cnt变为1
        }
    }
    cout << ans << endl;
    return 0;
}
```
AC链接:[AC](https://www.luogu.com.cn/record/35350785)

---

## 作者：Jinyeke (赞：2)

#### 题目：求一个序列中的最长不下降子段的长度。
#### 代码(pascal):
```
var
 n,i,s,max:longint;
 a:array[1..100000] of longint;
begin
 readln(n);
 for i:=1 to n do 
  read(a[i]);//输入
 max:=-maxlongint;//max一开始可以定小一点
 s:=1;
 for i:=1 to n-1 do
  if (a[i]<=a[i+1]) then inc(s)//如果没有下降（即前一个数小于或等于后一个数
    else if s>max then begin max:=s;s:=1;end//不然的话判断s是否大于目前最长的不下降子段的长度，大于的话，s赋值给max，并s为1（由于它本身也是一个数，所以就是1
   else s:=1;//s为1
 if s>max then max:=s;//最后再判断一下最后的那个s是不是大于max
 write(max);//输出最长不下降子段的长度。
end.
```
### 求过！
### 共建文明洛谷，请勿Ctrl+C！


---

## 作者：REAL_曼巴 (赞：1)

 此题题意言简意赅，我不解释了。此题最重要的点是判断上升的连续。方法如下：

循环判断如果当前项比下一项大，那就就符合要求，计数器加一。接下来就是不符合的时候，我们要先将目前计数器里的数与当前最大值比较，如果比他大，那么他就更新成最大的，在将计数器清零。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,cnt,sum=1,ans;
int main(){
    cin>>n>>a
    last=a;
    for(int i=2;i<=n;i++){
        cin>>a;
        if(a>=cnt) sum++;
        else ans=max(ans,sum),sum=1;
        cnt=a;
    }
    ans=max(ans,sum);
    cout<<ans;
    return 0;
}
```





---

## 作者：FR_qwq (赞：1)

一道最长不降子序列（题目也给我们说好了），直接判断一个数是不是比它前面的低，若是，目前的长度+1，不是，则判断目前长度是不是最长，目前长度清零。

__AC CODE__：
```pascal
uses math;//引用PAS的math库，因为里面有max函数（自己打也行）
var i,n,maxx,sum:longint;
a:array[1..100005]of longint;//定义，数组珂以开大点
begin
readln(n);
for i:=1 to n do read(a[i]);//读入
for i:=2 to n do
  if(a[i]>=a[i-1])then inc(sum)//判断是否没有下降
  else begin maxx:=max(maxx,sum+1);sum:=0;end;//求最大，长度清零
writeln(max(maxx,sum+1));//注意，输出前还得求个最大，否则第二个样例会输出0
end.//完美结束
```

__C党看这__：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//头文件，也可以用万能头
using namespace std;
int maxx,n,a[100001],sum,i;//定义，注意：如果把sum定到main函数里去的话，一定要先初始化为0
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);//读入
	for(i=2;i<=n;i++)if(a[i]>=a[i-1])sum++;/*判断*/else maxx=max(sum+1,maxx),sum=0;//求最大并清零
	printf("%d\n",max(maxx,sum+1));//最后求最大，输出
	return 0;//完美结束
}
```

---

## 作者：封禁用户 (赞：1)

# 本~~大佬~~蒟蒻又来写题解啦！

这道题要求一个序列中的最长不下降子段的长度，所以当我们找到一个数小于前面一个数的时候，就取最大的长度即可。

然后我们看一下数据范围：1<=n<=10的5次方（即100000）

为了保险起见，我们还是用scanf吧……

我直接用一个for完成了~~（因为懒得打那么多……）~~

## 话不多说，直接上代码！


```
#include<iostream>
#include<cstdio>//scanf需要用到
#include<cmath>//max需要用到

using namespace std;
int n,a,t,g=1,d;//我们待会儿要从第二个数枚起，g开始定为1，t用来存储a
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(i>1)//如果已经输入了第2个数，就进行判断
		{
			if(a<t)d=max(g,d),g=1;//若a小于上一个数t，用d存储最大值，而现在的a已经属于另一个子串，所以g应该赋值1
			else g++;
		}
		t=a;//t储存为a，以进行后面的比较
	}
	cout<<max(d,g)；//最后d可能为0，输出最大值
	
	return 0;
}
```

---

## 作者：_Qer (赞：1)

本题要求最长不下降**子段**（要求连续）

因此可以只用一个循环，在输入同时判断，压缩时间复杂度

判断第i个数时只用关注它是否大于第i-1个数，用一个tmp存当前不下降子段长度

如果num[i]>=num[i-1]那么长度加一，否则这个子段已经结束，判断是否大于当前最长长度，再将其清零

因为只用看num[i]和num[i-1]的大小关系，判断当前不下降子段是否结束，所以用一个有两个元素的数组即可，每次把后一个数前移为前一个数，再输入新的数，压缩空间复杂度

在循环后面还要判断一次当前不下降子段长度是否大于当前最长长度，原因见样例二（即最长不下降子段位于整个数组的最后）

下面就可以上代码（很短）

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[2],n;//num存上一个和当前数，n存元素数量
int maxl=0;//最长长度
int main(){
    cin>>n;
    int tmp=0;//当前长度
    //num[0]=0;可以不要因为初始值为零且数据保证每个元素都≥1
    for(int i=1;i<=n;++i){
        cin>>num[1];//输入新元素
        if(num[1]>=num[0]){//当前不下降子段未结束
            ++tmp;
        }else{
            maxl=max(tmp,maxl);//取最长长度
            tmp=1;//tmp=1因为长度要算上当前数
        }
        num[0]=num[1];//新的数前移，准备输入下一个
    }
    maxl=max(tmp,maxl);//这个必要
    cout<<maxl;
    return 0;
}
```

---

## 作者：tribool4_in (赞：0)

题意简洁明了，让你求 最长不下降子段长度，只需扫一遍，对于每个位置判断是否 $\le$ 它前面的数，如果是则长度 +1 并更新答案，否则长度重置为 $1$。

代码：

```cpp
// Code By WLS
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
inline int read() {
    int s=0, w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
int n, a[N];
int main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    int sum = 1, maxn = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i - 1] <= a[i]) sum++, maxn = max(maxn, sum);
        else sum = 1;
    }
    maxn = max(maxn, sum);
    cout << maxn << endl;
    return 0;
}
```

---

## 作者：kon_tori (赞：0)

### 题意
求一个长度为$\texttt{n}$的序列中最长不下降子段的长度。

>什么是不下降子段？

满足$\texttt{a[i]<=a[i+1]}$的子段即为不下降子段。

### 思路
我们用一个记数器$\texttt{ans}$来记录连续子段的长度，
再用另一个计数器$\texttt{maxans}$来记录$\texttt{ans}$的最大值。
按顺序读入每一个子段：
- 如果满足$\texttt{a[i]>=a[i-1]}$，$\texttt{ans}$加$\texttt{1}$，并时刻更新$\texttt{maxans}$的值；
- 如果满足$\texttt{a[i]<a[i-1]}$，把$\texttt{ans}$的值复位为$\texttt{1}$；

最后输出$\texttt{maxans}$即可。

### 代码实现
$\texttt{code:}$
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int n;
  int a[100001];
  int ans=1;//把ans的初始值设为1的原因：不管是上升序列还是下降序列开头的子段都要占用1的长度
  int maxans=1;//如果该序列为完全下降序列，不下降子段的长度也为1
  
  template<typename T>void read(register T& a){
      T x=0,f=1; 
      register char c=getchar();
      while(!isdigit(c)){
          if(c=='-')f=-1; 
          c=getchar();
      }
      while(isdigit(c))
      x=(x<<1)+(x<<3)+c-'0',c=getchar();
      a=x*f;
  }//快读
  
  int main(){
      read(n);
      read(a[1]);//先读入第一个子段
      for(int i=2; i<=n; i++)/*从第二个子段开始判断*/{
          read(a[i]);
          if( a[i]>=a[i-1] ){
              ans++;
              maxans=max(ans,maxans);
          }//满足不下降，ans加1，更新maxans
          if( a[i]<a[i-1] ){
              ans=1;
          }//不满足则复位
          if( i==n-1 && a[i]<=a[i+1] ){
              ans++;
              maxans=max(ans,maxans);
              goto sp;
          }//特判倒数第二个子段，提前跳出循环
      }
      sp : ;   
      cout<<maxans<<"\n";
      return 0;
  }
```

### 后记
#### **$再次感谢管理员的辛勤付出！$**

蒟蒻的第$\texttt{11}$篇题解，望通过。

---

## 作者：_cmh (赞：0)

因为这道题是一道“最长不下降子段”的板子题……

套板子啊！

我们可以边读边做，用 $b$ 记录上一个的值。

每次判断若 $a \ge b$ ，则当前长度++，每次 $maxn$ 记录最大值。 

否则当前长度为 $0$。

最后输出 $maxn+1$ 即可。（因为起点没有算）

上代码：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,a,t,maxn,b;
int main(){
    cin>>n>>b;
    for(int i=2;i<=n;i++){
    	cin>>a;
    	if(a>=b){
    		t++;
    		maxn=max(t,maxn);
		}
		else t=0;
    	b=a;
	}
	cout<<maxn+1;
    return 0;
}
```

求赞！

---

## 作者：不到前10不改名 (赞：0)

//233，一开始还认为是可不连续的呢，结果wa了
```
#include<stdio.h>
int i,t,n,srx[100001],sry;
int max(int x,int y)//手打max（一开始打成cmp了，sort用习惯了，结果~怎么也查不出来233）
{
    if(x>y)
    return x;
    return y;
}
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&srx[i]);
    for(i=1;i<=n;i++)//一直很奇怪为什么要从2开始（我太弱了，不过大家都是这样打的呢~）
    {if(srx[i]<=srx[i+1])//这个应该很好理解，就是最长不下降子序列的定义不下降，就是前面的数<=后面的数，上升的话就是就是前面的数<后面的数，少一个相等
    t++;
    else
    t=0;//清1后面就不用加了，不过前面也要赋值1
    sry=max(t,sry);}//最长值么，当然是max
    printf("%d",sry+1);//+1是因为还有一个数（起始点本身），当然你也可以把t清为1，随便你~
    return 0;
}
```

---

## 作者：OdtreePrince (赞：0)

# -模拟-

Remember:子段是连续的！！！

既然如此，慢慢模拟吧！

用last记录上一个数，a表示此次输入的数，两者不断更新，一次判断，如果不是不下降的，将答案与此时的sum比较，循环完成之后可别忘了再比较一次！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,a,last,sum=1,ans;
int main(){
    scanf("%d",&n);
    scanf("%d",&a);
    last=a;
    for(int i=2;i<=n;i++){
        scanf("%d",&a);
        if(a>=last) sum++;
        else{
            ans=max(ans,sum);
            sum=1;
        }
        last=a;
    }
    ans=max(ans,sum);//因为少了这个，可怜的蒟蒻我不得不再测一次。
    cout<<ans;//QAQ
    return 0;
}
~~~

---

## 作者：Tomone (赞：0)

Vector数组加迭代器，有点麻烦
```
#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;

const int MAXN(10086);
vector <int> v; //建一个Vector动态数组

int main(){
	ios::sync_with_stdio(false);
	int tmp,n,ans=0,cnt=0;
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>tmp;
		v.push_back(tmp); //存入数据
	}
	for(vector <int>::iterator it = v.begin()+1;it!=v.end();++it){
		vector <int>::iterator tmp2=it-1; //迭代器指向前一个元素
		if((*it)>=(*tmp2)){
			cnt++;
			ans=max(cnt,ans);
		} else cnt=0;
	}
	cout<<ans+1;
	return 0;
} 

```

---

## 作者：RBI_GL (赞：0)

### 题意：

求一串数字中的最长不下降子段的长度。

即：

![](https://cdn.luogu.com.cn/upload/image_hosting/wzkifivg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


-----


### 思路：


读入数据，遍历整个数组。如果后一个数 $≥$ 前一个数，计数器就加一，然后每次循环之后都更新答案，求出最大值。

Code：
-
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005];
int ans;
int sum=0;
int main()  
{
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i]; //输入 
    for (int i=2;i<=n;i++) { //搜索整个数组 
        if (a[i] >= a[i-1])  //如果后一个数大于等于前一个数
        {  
            sum++; //计数器++  
            ans=max(ans,sum);  //每次循环之后都更新ans的值 
        }  
        else sum=0; //否则就将计数器清零
     }  
    cout<<ans+1;
    return 0;
} 
```


---

