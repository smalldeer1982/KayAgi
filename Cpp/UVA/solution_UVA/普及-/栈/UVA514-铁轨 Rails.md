# 铁轨 Rails

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=455

[PDF](https://uva.onlinejudge.org/external/5/p514.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/a8f0af9a2adeaeaab1d1906c3f3116afa0c6b444.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0```

### 输出

```
Yes
No

Yes```

# 题解

## 作者：封禁用户 (赞：34)

虽说题解算法与下面两位基本一致，但是我稍微多写一点解析。

用STL写一个栈。

~~调这题花了很长时间w~~
```cpp
#include<cstdio>
#include <cstring>
#include<stack>  
using namespace std;  
const int MAXN=1010;  
int train[MAXN];  
  
int main()  
{  
    int n,A,B,ok;  
    while(scanf("%d",&n),n)  //uva常用开头
    {  
        stack<int> s;  
        while(1){  
        scanf("%d",&train[1]);  
        if(train[1]==0)  break;  
        {  
        for(int i=2;i<=n;i++)  
        {  
             scanf("%d",&train[i]);  
        }  
        A=B=ok=1;   
        while(B<=n)  //如果驶向B的车个数等于n，则循环结束。   
        {  
            //如果驶向C的车等于驶向B的车的序列号，直接该将车驶进B
            //可以得出若满足如果驶向C的车等于驶向B的车的序列号，A车一定直接驶入B
            if(A==train[B]) { A++,B++;}   
            //否则，则判断栈顶的(即在C最上面)车是否等于驶向B的车
            //若成立，则将车驶入B
            else if(!s.empty()&&s.top()==train[B]) {s.pop(),B++;}  
            //将车驶进C   
            else if(A<=n) s.push(A++);  
            //如果车全部都驶入C，循环还没有结束，意味着所给的train顺序不能实现   
            else  
            {  
                ok=0;  
                break;  
            }  
        }  
        printf("%s\n",ok?"Yes":"No");}}  
        printf("\n");  
    }  
}  
```

---

## 作者：黑与白 (赞：21)

本人第一次发题解，如有缺陷，请大家补充，谢谢！


------------
在经过一些奇妙的思（死）考（尻）之后，我成功地发现一种奇妙的算法：
若有10节火车进站，它们的出站顺序可能是这样的：10，9，8，7，6，5，4，3，2，1；也可能是这样的：6，5，4，3，2，1，8，7，10，9……

经过本人的规律排列，发现这些数列都有一个共同点：**这些数字在分隔成m个降序数列之后，由这m个降序数列的每个数列第一个元素构成的序列为升序排列**（十分的玄学）

举个例子，6，5，4，3，2，1，8，7，10，9可分割为6 5 4 3 2 1|8 7|10 9，而其中每个序列的第一个数字6，8，10恰好构成一个升序，所以这个排序是可以的。再举例，6 5 8 7 4 3 2 1 10 9可分割为6 5|8 7 4 3 2 1|10 9，其中6 8 10也构成了升序，所以也可行。

说白了就像模拟火车进站（栈），序号小的必定先进站，而序号大的后进站，所以每一次**连续的出站**时必定是序号大的先出站（降序），而进站时的序号越来越大，每一次连续出站的第一列序号也一定是越来越大的（升序）。

上个伪代码：

```cpp
bool pd(int n)
{
	int a[1001],r,t=0,u=0;
	for(int i=1;i<=n;i++)
	{
		cin>>r;
		if(r>t)    //判断是否在同一个降序 
		{//如果进入这里，证明r是下一个降序的元素，而且必定为第一个 
			a[u]=r;//记录每个降序开头元素 
			u++;   //下一个降序 
		}
		t=r;       //记录这次输入的元素
	}
	for(int i=1;i<u;i++)
		if(a[i-1]>a[i]) return false;//判断是否升序 
	return true;
}
```
这里仅提供主要用来判断的代码，具体还是请各位敲敲键盘吧！QAQ

---

## 作者：览遍千秋 (赞：12)

~~当写这个题解的时候，这是一道紫题（怎么刷到的）~~

巨坑无比，算法不难，但读入是个比较坑的东西。

写一个函数判断该编组能否满足要求，栈的初步不予解释。

代码：
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 10007
int n,k,a[maxn],s[maxn],top,q,x;
bool f()
{
    k=1,top=0;
    for(register int i=1;i<=n;i++)
    {
        s[++top]=i;
        while(top>0&&s[top]==a[k])
        {
            k++;
            top--;
        }
    }
    if(top==0) return 1;
    else return 0;
}
inline void Init()
{
    while(1)
    {
        scanf("%d",&q);
        if(q==0) break;
        while(1)
        {
            scanf("%d",&x);
            if(!x) break;
            else a[1]=x;
            for(register int i=2;i<=q;i++)
                scanf("%d",&a[i]);
            n=q;
            if(f()) printf("Yes\n");
            else printf("No\n");
        }
        printf("\n");
    }
}
int main()
{
    Init();
    return 0;
}
```

---

## 作者：SYGFchen (赞：11)

这其实是一道纯模拟，只要你会栈的基本操作即可。
详情见代码：
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1005;
int n, m, a[N], cnt = 0, stk[N];
bool check()
{
    int shoot = 0, i = 1, j = 1;
    bool b[N];
    memset(b, 0, sizeof(b));
    while (i <= n)//枚举每一个车
    {
        if (b[a[i]] == 1)
        {
            if (stk[shoot] != a[i])
                return 0;
            else
                shoot--;
        }//如果这辆车已经进站，就判断他是不是栈首，如果不是就输出no
        else
        {
            while (j <= a[i])
                stk[++shoot] = j, b[j++] = 1;
            shoot--;
        }//要不然就把他和和他前面所有未进站的车进站
        i++;
    }
    return 1;//满足条件
}
int main()
{
    cnt = 0;
    while (cin >> n)
    {
    		//注意读入，调了我几十分钟
        if (n == 0)
            break; 
        int tmp = 0;
        while (cin >> tmp)
        {
            if (tmp == 0)
                break;
            a[1] = tmp;
            for (int i = 2; i <= n; i++)
                scanf("%d", &a[i]);
            //读好以后跑一遍check
            if (check())
                puts("Yes");
            else
                puts("No");
        }
        puts("");
    }
    return 0;
}

```


---

## 作者：3357739632xjs (赞：8)

## UVA514栈的经典例题
### 可以用STL写一个栈，这里给出数组模拟的方法
### 解析：
观察发现，整个调度过程其实是在模拟入栈出栈的过程，而这个过程中，我们可以分成三种状态：栈前、栈中、栈后。我们可以发现，当某个数字出栈了，说明比它小的数字要么已经出栈了，要么还在栈里，不能是入栈前状态，并且在栈中的顺序是从大到小的(从栈顶往栈底看)，比如出5，那么1，2，3，4要么已经在5之前出了，要么还在栈中（假如1，3，4在栈中，从栈顶往栈底看依次为4，3，1），不能是入栈前的状态。如果某个数字要出栈，那么当前在栈中的数字都必须小于它，否则就与栈的性质矛盾，不合法，于是我们可以这样解决：

从第一个数字开始扫描，a[i]表示当前出栈的数字，如果有比a[i]大的数字还在栈中，那么就产生矛盾，输出“NO”；否则，标记当前数字a[i]为栈后状态，那么[1, a[i]-1]这些数字如果还没出栈，标记为栈中状态。具体我们可以用0表示为确定状态，1表示栈中状态，2表示栈后状态。

数组模拟实现：

枚举1到n；

入栈判断：若p数组最顶端位置不等于当前顺序（即栈顶小于当前顺序）
自加入栈；

若无法入栈（即为栈顶到达n）判断若栈顶不为当前顺序：输出“No”；若为当前顺序，说明该顺序正确，删除栈顶元素；

**部分代码：**
```cpp
for(int i=1;i<=n;i++){
	while(k==0||k!=0&&p[k]!=a[i]&&t<n)
	p[++k]=++t;
	if(p[k]!=a[i]){
		cout<<"No"<<endl;//注意输出大小写，本蒟蒻被卡了十几分钟 
	}
	else k--;
}
```
主要思路如上，但本题有一个特色——输入输出

对于每一组数据，第一行是一个整数 N。接下来**若干行**数据，每行 N 个数，代表 1 ~ N 车厢的出栈顺序，最后一组数据只有一个整数 0 。**对于每一组数据，在最后输出空行。**
最后一组数据的 N=0 ，不输出。

~~于是输入输出代码又调了十几分钟，汗~~

**下面给出代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int k,n,a[1005];
int p[1005],t;
bool ok;
int main(){
	while(cin>>n&&n!=0){
		abc://abc在这！ 
		while(true){
			memset(a,0,sizeof(a));
			memset(p,0,sizeof(p));//因为有多组数据，所以每次清零 
			t=k=0;//防止影响下一组数据 
			ok=false;
			cin>>a[1];
			if(a[1]==0)break;
			for(int i=2;i<=n;i++)
				scanf("%d", &a[i]);
			for(int i=1;i<=n;i++){
				while(k==0||k!=0&&p[k]!=a[i]&&t<n)
				p[++k]=++t;
				if(p[k]!=a[i]){
					cout<<"No"<<endl;
					goto abc;//跳转到abc位置 
				}
				else k--;
			}
			cout<<"Yes"<<endl;//注意大小写 
		}
		cout<<endl;//每组数据换行 
	}
	return 0;
}
```
**题外话：**

希望大家仔细看题~~尤其是大小写和输入输出模式~~，大胆思考，谨慎编程。

## 谢谢大家！蒟蒻题解，dalao勿喷

---

## 作者：cornivores (赞：7)

嗯，貌似大家都是模拟栈写的，这里写一发思维题解。

蒟蒻本蒻发现，其实输出Yes的情况就是**对于每个元素a[i]，在a[i]后面的且比a[i]小的都必须呈降序**。一旦发现有升序，更改标记直接break就行。最后小心要空行（因为这个WA了半天）。


```cpp
#include<bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define lson rt<<1, l, mid
#define rson rt<<1|1, mid+1, r
#define PI acos(-1)
#define eps 1e-5
using namespace std;
typedef long long LL;
typedef pair<LL, int> pli;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
typedef pair<double, double> pdd;
typedef map<char, int> mci;
typedef map<string, int> msi;
template<class T>
void read(T &res) {
  int f = 1; res = 0;
  char c = getchar();
  while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
  while(c >= '0' && c <= '9') { res = res * 10 + c - '0'; c = getchar(); }
  res *= f;
}
const int N = 1005;
int a[N];
int main() {
  int n;
  while(scanf("%d", &n), n) {
    while(scanf("%d", &a[0]), a[0]) {
      for(int i = 1; i < n; ++i) read(a[i]);
      int Max = a[0], f = 0;
      for(int i = 1; i < n - 1; ++i) {
        if(a[i] < Max && a[i+1] < Max && a[i] < a[i+1]) {
          f = 1; break;
        }
        Max = max(Max, a[i]);
      }
      if(f) puts("No");
      else puts("Yes");
    }
    puts("");
  }
  return 0;
}

```


---

## 作者：Nempt (赞：7)

好多代码和紫书上的有点眼熟啊......那我上一个比较精简的代码吧

这道题早上没事的时候在纸上推了推，发现模拟出入栈的顺序就可以了。


比如说现在有1-5号车要进栈，处理的策略是**逐辆车进栈**，然后定义一个变量（你可以理解为指针，指向out首元素）【ps：out是记录出栈顺序的数组】，看看当前指针指向的的值是否和栈顶值一致，**一致的话就栈顶元素出栈且指针下移**；不一致的话什么都不要做。

举个栗子：现在待进的是： 1 2 3 4 5 6

问出栈顺序为： 1 2 4 3 5 6  符不符合出入顺序？

过程：

**1） 1号车入栈，out【1】为1，可以出栈，指针下移**

**2） 2号车入栈，out【2】为2，可以出栈，指针下移**

**3） 3号车入栈，out【3】为4，暂时不可以出栈，指针值也不要动**

**4） 4号车入栈，out【3】为4，可以出栈，指针下移**

	    4号车出栈完毕后，out【4】为3，可以出栈，指针下移
    
**5） 5号车入栈，out【5】为5，可以出栈，指针下移**

**6） 6号车入栈，out【6】为6，可以出栈**

栈为空，火车全走了，所以ok，输出yes！



上代码理解一下：

```cpp
#include <iostream>
#include<stack>
using namespace std;
int main()
{
    int n;
    while(cin>>n&&n)
    {
        int out[n+1];			//定义出栈顺序数组
        while(1)
        {
            cin>>out[1];
            if(!out[1]) break;
            stack<int> v;
            for(int i=2;i<=n;i++)
                cin>>out[i];
            int pos=1;			//“指针”，指向出栈顺序数组首元素
            for(int i=1;i<=n;i++)//逐辆车进栈
            {
                v.push(i);		//不管怎样，先进站再说
                while(v.top()==out[pos]&&!v.empty()) //如果栈顶元素和当前指针值一致，持续出栈
                {
                    v.pop();	//逐辆车出栈
                    pos++;		//指针下移
                    if(v.empty())   break;//万一栈空了，那么回到循环条件判断的时候会内存段错误，所以这里需要加上一个小判断
                }
            }
            if(v.empty())   cout<<"Yes"<<endl;//全弹出去了，yes
            else            cout<<"No"<<endl;//还有火车没能出栈，no
        }
        cout<<endl;//注意换行
    }
    return 0;
}
```


---

## 作者：KingOfWA (赞：5)

> 超级详细分析

> 紫书P140，栈的模板题。

> 秒切这题的dalao请跳过本文


# 题目

## 题意
已知入栈序列$1,2,3,4,...n$，问能否得到出栈序列$Target_1,Target_2,Target_3,...Target_n$（要求每个元素只进栈一次）

## 输入格式
单个输入文件中包含若干组数据。
每组数据第一行给出$n$

之后若干行，每行表示一个询问，每行$n$个数，第$i$个数表示$Target_i$，保证为$1,2,...,n$的一个排列

$Target_1=0$表示该组输入结束

$n=0$表示输入结束

## 输出格式
对于每个询问，输出`Yes`或`No`

***每两组数据间应有一空行***

# 解答

## 分析

令$A$表示下一个进栈元素，$Target_B$表示下一个期望元素

初始化，`A=B=1`，栈`s`为空

对于每一个A，分类讨论：

1.$A=Target_B$，显然A进栈后立即出栈，`A++`，`B++`
2.栈非空且$s.top()=Target_B$，即栈顶元素为下一个期望元素，`s.pop()`出栈，`B++`
3.$A<=n$，说明还有输入，但期望的元素并不是它或栈顶元素，那只能入栈（没有其他方案）
4.以上情况均不满足，说明输入已经全部入栈，栈中有元素但并不是期望元素，一定无解

## AC代码

``` cpp
#include<iostream>
#include<stack>
using namespace std;

const int MAXN=1005;

int n,target[MAXN];

void solve();

int main(){
    while((cin >> n)&&(n)){
        while((cin >> target[1])&&(target[1])){
            for(int i=2;i<=n;i++) cin >> target[i];
            solve();
        }
        putchar('\n');
    }
    return 0;
}

void solve(){
    stack<int> s;
    int A=1,B=1;
    while(B<=n){
        if(A==target[B]) {
            ++A;
            ++B;
        }
        else if((!s.empty())&&(s.top()==target[B])){
            s.pop();
            ++B;
        }
        else if(A<=n) s.push(A++);
        else {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    return;
}
```

---

## 作者：YUKAYOUXIA (赞：4)

```cpp
#include<cstdio>
#include<stack>
using namespace std;
int N;
int B[1005];
int main(){

	while(scanf("%d",&N)&&N){//N为0时结束程序
		//printf("%d:\n",N);
		while(1){
			for(int i=0;i<N;i++){//因为每次我们只使用B数组中的[i,N)的值,而新值会覆盖旧值,无需清空
				scanf("%d",&B[i]);
				//printf("%d:%d",i,B[i]);
				if(B[i]==0){//当输入为0时,说明这组数据结束
					break;
				}
			}
			if(B[0]==0){////当输入为0时,说明这组数据结束,跳出该循环,准备接受输入另一个N
				//printf("!\n");
				break;
			}
			stack<int> C;//用栈模拟C的作用
			int A=1,i=0;//A表示目前准备从A驶出的车辆,i表示现在B中已有几辆车
			while(i<N){
				if(A==B[i]){//如果A中准备驶出的车 与 B中需要的车 一致,把该车不经过C直接驶入B
					++A;
					++i;
				}else if(!C.empty()&&C.top()==B[i]){//如果C最上面的车厢 与 B中需要的车厢一致 把该车驶出C并驶入B
					C.pop();
					++i;
				}else if(A<=N){//当A中车未完全驶出时,把A中最前面的车驶入C等待
					C.push(A);
					++A;
				}else{//如果不符合上述情况 说明给定顺序错误,将i标为-1
					i=-1;
					break;
				}
			}
			if(i==-1){
				printf("No\n");
			}else{
				printf("Yes\n");
			}
		}
		printf("\n");//注意!!!洛谷的样例是错的!!!对于每一组数据，在最后输出空行!!!
	}
	return 0;
}
```


---

## 作者：CrazyDance (赞：1)

## [~~传送门~~](https://www.luogu.org/problem/UVA514)

### 题目大意：

意思很简单，就是说有一个｛1，2，3， ...，N｝的队列依次进栈，问出栈的顺序是否可能是题目给出的数列，如果是，输出$Yes$，如果不是，输出$No$.

### 分析&方法：

这是一道比较简单的模拟题。

通过题目，我们仔细看一看，就能分析出来：

- $A$：未入栈的数

- $Station$：如其名“站”——栈

- $B$：已出栈的数

众所周知，栈是后进先出的。

所以我们不难得出，对于第$i$个出栈的数$a_i$，我们必然有$1$~$a_i$已经进栈，且$a_i$处于当前的栈顶。那么我们就可以从$a_1$开始模拟，如果栈顶元素小于$a_i$，则将$a_i$之前的元素都压入栈，如果栈顶元素大于$a_i$则输出$No$，如果栈顶元素为$a_i$则直接出栈。

不难得出 效率为$O(NT)$（T为问题数）

上关于栈的$Byte$（实在不懂可以看注解）

```cpp
bool check()
{
	int z[N]/*栈*/,cnt=0/*栈的大小*/,k=1/*此时到了第k个数*/;
	for (int i=1;i<=n;i++)
	{
		if (i==a[k])//可以直接弹出的
		{
			k++;//直接跳过，不用进栈
			for (;z[cnt]==a[k]&&cnt&&k<=n;) cnt--,k++;//判断栈顶的每一个数能否出栈
		}
		else z[++cnt]=i;//否则就进栈
	}
	for (;z[cnt]==a[k]&&cnt&&k<=n;) cnt--,k++;//同样：判断栈顶的每一个数能否出栈
	if (k==n+1) return 1;//如果所有的数都搞定了，证明方案可行 
	else return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# STL大法！！！
## 紫色借鉴专家  呃、
```
#include<iostream>
#include<cstdio>
#include<cstring>//头文件
  
using namespace std;//调用控件
int k,n,a[1005];
int p[1005],t;//开数组
bool ok;
int main(){
    while(cin>>n&&n!=0){
        abc://abc在这！ 
        while(true){
            memset(a,0,sizeof(a));
            memset(p,0,sizeof(p));//因为有多组数据，所以每次清零 
            t=k=0;//防止影响下一组数据 
            ok=false;
            cin>>a[1];
            if(a[1]==0)break;
            for(int i=2;i<=n;i++)
                scanf("%d", &a[i]);
            for(int i=1;i<=n;i++){
                while(k==0||k!=0&&p[k]!=a[i]&&t<n)
                p[++k]=++t;
                if(p[k]!=a[i]){
                    cout<<"No"<<endl;
                    goto abc;//跳转到abc位置 
                }
                else k--;
            }
            cout<<"Yes"<<endl;//注意大小写 
        }
        cout<<endl;//每组数据换行 
    }
    return 0;
}
```
##### 珍爱生命，杜绝抄袭

---

## 作者：HuangBo (赞：1)

~~建议难度改为普及-~~

题意很清晰了，可以模拟栈，或者直接用STL的栈

如下（参考了somewhere）：

```cpp
#include<cstdio>
#include<stack>
using namespace std;
int n, target[1111],A,B,i;
bool ok;
int main()
{
	while(scanf("%d", &n))
	{
		stack<int> s;
		A=1,B=1;
		for(i=1;i<=n;i++)
		scanf("%d",&target[i]);
		ok=1;
		while(B<=n)
		{
			if(A==target[B])A++,B++;
			else if(!s.empty()&&s.top()==target[B])s.pop(),B++;
			else if(A<=n) s.push(A++);
			else 
			{
				ok=0;
				break;
			}
		}
		if(ok)puts("YES");
		else puts("NO");
	}
    while("233");//233
	return 0;
}
```

---

