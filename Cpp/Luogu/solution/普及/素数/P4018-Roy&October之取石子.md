# Roy&October之取石子

## 题目背景

Roy 和 October 两人在玩一个取石子的游戏。


## 题目描述

游戏规则是这样的：共有 $n$ 个石子，两人每次都只能取 $p^k$ 个（ $p$ 为质数，$k$ 为自然数，且 $p^k$ 小于等于当前剩余石子数），谁取走最后一个石子，谁就赢了。

现在 October 先取，问她有没有必胜策略。

若她有必胜策略，输出一行 `October wins!`；否则输出一行 `Roy wins!`。


## 说明/提示

对于 $30\%$ 的数据，$1\leq n\leq 30$；

对于 $60\%$ 的数据，$1\leq n\leq 10^6$；

对于 $100\%$ 的数据，$1\leq n\leq 5\times 10^7$, $1\leq T\leq 10^5$。

（改编题）


## 样例 #1

### 输入

```
3
4
9
14```

### 输出

```
October wins!
October wins!
October wins!```

# 题解

## 作者：翟绪尧 (赞：81)

正解：只有是6的倍数就是第二个人赢，否则第一个人赢

解释：

一。首先，1,2,3,4,5都可以一次取到，当n=6时，第一个人先取1-5个，无论怎么取，第二个人全去走就赢了。

二。对于6的倍数，一定不能是质数的K次方，证明：先是除2以外的质数都是奇数，而奇数乘奇数都是奇数，故6的倍数全不是n的K次方；对于2，由于6中存在因数3，故6\*n也不是2的K次方。

三。对于12，第一个人取1-5个，第二个人直接取到剩下6个，就变成了情况一，第一个人取不到6个，若去6个以上，则直接败；

四。归纳6\*n。第一个人无法去6的倍数个，第二个人只要将数压倒6\*m(m<n）就会慢慢推到情况二，就又是第一个人输。

五。对于非6的倍数，第一个人只要去1-5个，使之变成6的倍数，就变成情况四了。

综上：正解成立。

良心AC代码，勿复制

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,a;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a%6==0)cout<<"Roy wins!"<<endl;
        else cout<<"October wins!"<<endl;
    }
}
```

---

## 作者：zhoutb2333 (赞：28)

**博弈论题首先找规律**

首先$0$个石子的状态一定是必败态，因为对面在上一轮已经拿完了。

观察$1$~$5$个石子，发现$1=p^0,2=2^1,3=3^1,4=2^2,5=5^1$，都是必胜态，可以一次拿完赢得游戏。

然后$6$个石子没办法一下拿完（因为$6\neq p^k$）。可以知道只能拿$1$~$5$个石子，这样都会转移到前面的必胜态，只不过这个必胜态已经是对面的了，**所以说$6$个石子是你的必败态，在你面前出现$6$个石子又轮到你拿的时候，你必定失败。**

这样一直往后找到$12$的时候，发现$7$~$11$都是必胜态（一次把石子总数拿到$6$个石子然后对面就输了），而$12$是必败态（可以枚举$1$~$12$中的所有$p^k$，都转移到对面的必胜态）。

于是猜想**所有$6n$的状态是必败态，其余所有状态$(6n+1,6n+2 \ldots 6n+5)$都是必胜态。**

我们采用数学归纳法证明：

当$n=0$时，结论成立，因为$0$~$5$上面已经说明过了。

现在假设$0$~$6n-1$都满足结论。

先证明$6n$为必败态：因为任何$p^k$，都不是$6$的倍数，所以$6n$个石子拿完一次**不会还是$6$的倍数**，故必定转移到对面的必胜态，所以$6n$是必败态。

显然$6n+r(r=1,2 \ldots 5)$只需要拿掉$r$便可以转移到$6n$，是对面的必败态，所以$6n+r(r=1,2 \ldots 5)$是必胜态。

证毕。

代码，只需要判一下输入是否是$6n$即可：

``` cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int T,x;
    for(scanf("%d",&T);T;T--){
        scanf("%d",&x);
        puts(x%6==0?"Roy wins!":"October wins!");
    }
    return 0;
}
```

---

## 作者：Khassar (赞：7)

这题乍一看好像是SG的题，再一看数据范围1<=n<=50,000,000，1<=T<=100,000,啊，去死吧！

显然这是一道找规律，O(1)求解的题。

考虑到每个人能取得情况都比较多，感觉先手更容易赢，那我们就来看看先手什么情况下会输：

我们可以手模一下，在n=1~5时，先手都可以一次拿完，但是我们发现在n=6的时候，先手输了，因为无论先手拿几都拿不完，那么由于1~5先手都能赢，那么一定会剩下一个必胜局面，后手就赢了。

接着向后推，在7~11中一定可以拿走1~5个，给后手剩下一个6——必输局面，或者一次拿完，这样就是必赢得了，当n=12时，怎么拿都拿不完，同时也无法一次拿走6个，这样就会留下一个必胜局面，后手又赢了……

由此可见，当n时6的倍数时，后手赢，否则先手赢。


代码嘛，就像这样？


```cpp
if(n%6) puts("October wins!");
        else puts("Roy wins!");
```

记得是多组哦


---

## 作者：封禁用户 (赞：5)

此题是一道博弈的题，只要找到其规律（重点），那么之后的代码就会非常简单。  
  
  题目传送>>[P4018](https://www.luogu.com.cn/problem/P4018)    
    
###     题意简述:  
共有$n$个石子，Roy 和 October两人每次都只能取$p^k$个（$p$为质数，$k$为自然数，且$p^k\le$当前剩余石子数），谁取走最后一个石子，谁就赢了，October 先取，求结果。
### 题目分析  
按照规则，谁能够一次性将当前剩余石子全取走，那么他就赢。先分析一次取石子的可能情况：$0$，$1=p^0$，$2=2^1$，$3=3^1$，$4=2^2$，$5=5^1$,而6，我们可以发现$6\neq{p^k}$，所以一次不能取6个，故当$n=6$，October能取的石子数为{$1,2,3,4,5$}，必将有所剩余，而使Roy获胜。而对于$6$以上的$n$时，如果$n$为$6$的倍数，那么会发现经过反复取石子，终将会回到上面的情况，只有当$n$不为$6$的倍数时最终先手October才将获胜。所以判断$n$是否是$6$的倍数即可判断最终结果。  
### Code:  
```cpp
#include<iostream>
using namespace std;
#define endl '\n'   \\利用宏定义加速endl换行 
int main()
{
	ios::sync_with_stdio(0);   \\关闭同步流，加速cin输入和cout输出 
	int t,n;   \\定义测试点组数和石子数 
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		if(n%6!=0)   \\判断是否是6的倍数，此为否 
        {
            cout<<"October wins!"<<endl;
        }
        else
        {
            cout<<"Roy wins!"<<endl;
        }
	}
	return 0;  \\结束整个程序 
 } 
```
### 结果（未吸氧）  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ngov35q3.png)  
企鹅的题解到此结束，祝各位OIers进步++~

---

## 作者：panlin (赞：2)

### 本题运用了博弈论相关知识。
n个石子，两个人轮流从这堆石子中取石子，规定每次至少取一个，最多取p^k个。最后取光者得胜。

如果n=p^k+1，那么由于一次最多只能取p^k个石子，所以，无论先取者拿走多少个，后取者都能够一次拿走剩余的石子，后者取胜。显然我们可以发现：每个回合时p^k+1个，如果n=（p^k+1)*r+s，（r为任意自然数，s≤p^k),那么先取者要拿走s个物品，如果后取者拿走m（≤p^k)个，那么先取者再拿走p^k+1-m个，结果剩下（p^k+1）（r-1）个，以此类推继续这样的取法，那么先取者肯定获胜。总之，要保持给对手留下（p^k+1）的倍数，就能最后获胜。

总结上面的分析得出公式：有n个石子每次最多取p^k个，若先取完的获胜，则n%(p^k+1)==0。

而6及6的倍数无法写成p^k的形式，故公式中的p^k应该为5。
```cpp
#include <iostream>
using namespace std;
int main() {
	int t, n;
	cin >> t;
	while(t--) {
	cin >> n;
	if(n % 6)
	cout << "October wins!" << endl;
	else
	cout << "Roy wins!" << endl;	
	}
	return 0;
}
```




---

## 作者：hehelego (赞：2)

提供一个SG函数打表的玩法...

后排感谢CLY的帮助qwq...不知道SG函数的可以看LG日报里面关于博弈论的日报.


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int read(){
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch>'9'||ch<'0');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return x*f;
}
#if 0
const int N=1000;
vector<int> pk;
namespace PRIME{
int ok[N],vis[N],pr[N],pcnt;
void init(){
	// 这里是线性筛QAQ
	vis[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i]){
			pr[pcnt++]=i;
			int t=1; while(t<N){ ok[t]=1; t*=i; }
		}
		for(int j=0;j<pcnt&&pr[j]*i<N;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
    // 可用决策表..
	for(int i=1;i<N;i++) if(ok[i]) pk.push_back(i);
}
}
int sg[N],vis[N];

int main(){
	PRIME::init();
    // 边界,0的后继是空集,后继的SG函数值的集合也是空集,mex{ {} } =0
	sg[0]=0;
	for(int i=1;i<N;i++){
		memset(vis,0,sizeof(vis));
		for(int j=0;j<pk.size()&&pk[j]<=i;j++)
			vis[sg[i-pk[j]]]=1; // 后继节点的sg函数标记一下vis
        //求出mex,即为SG[i]
		int j=0; for(;j<N;j++) if(!vis[j]) break;
		sg[i]=j;
	}
    // 找出必败态QAQ
	for(int i=0;i<N;i++)
		if(sg[i]==0) printf("sg[%d]=%d\n",i,sg[i]);
	return 0;
}
// 打出来的表就是这个样子了QAQ...大胆猜想不用证明(大雾)
sg[0]=0
sg[6]=0
sg[12]=0
sg[18]=0
sg[24]=0
sg[30]=0
sg[36]=0
sg[42]=0
sg[48]=0
sg[54]=0
sg[60]=0
sg[66]=0
sg[72]=0
sg[78]=0
sg[84]=0
sg[90]=0
sg[96]=0
sg[102]=0
#endif

int main(){
	int t=read();
	while(t--){
		if(read()%6==0) puts("Roy wins!");
		else puts("October wins!");
	}
	return 0;
}

```

---

## 作者：鹿鸣。 (赞：2)


```cpp
    #include<bits/stdc++.h>
    using namespace std;
    inline int read(){
        int lin=0;
        char x=getchar();
        while(x<'0' || x>'9') x=getchar();
        while(x>='0' && x<='9'){
            lin=(lin<<1)+(lin<<3)+x-'0';
            x=getchar();
        }
        return lin;
    }
    int t,x;
    int main(){
        t=read();
        while(t--){
            x=read();
            if (x%6==0) printf("Roy wins!\n");
            else printf("October wins!\n");
        }
        return 0;
    }
```
\*题目：
游戏规则是这样的：共有n个石子，两人每次都只能取p^k个（p为质数，k为自然数，且p^k小于等于当前剩余石子数），谁取走最后一个石子，谁就赢了。

现在October先取，问她有没有必胜策略。

若她有必胜策略，输出一行"October wins!"；否则输出一行"Roy wins!"。\*


证明：

数学归纳法。

首先看题目，易知——1、2、3、4、5这五个数，当我方轮到时，都是处于我方的必胜态——直接取数让对方无法取即可。

然，我方遇到6时，6分解质因数形式，为2\*3，不可直接取数得到。

那么，无论取1-5这五个能取的任意一个，对方所获得的数，必然呈必胜态。

那么遇到6，为我方必败态。

继而推广。

设n<=6k时，其中只有6的倍数，是必败态。

那么，当n<=6\*k+6时。

只需要证明6\*k+1-5这五个数，都是我方的必胜态，显然，我方只需要取对应的1-5这五个数，留给对方的数则6\*k

由假设，知6\*k为必败态，对方必败，我方必胜。

得证。

继而。

当我方获6\*k+6时，证之必败，那么即证明，我们能够取一个数，让对方处于必败态，而由假设，让对方处于必败态的数，必然是6的倍数，即，我方要取6的倍数。

易知。

6的倍数不可被直接取得。

故，得证。

而后，直接推广，数学归纳法成立。

总结论——6\*k为必败态，我方取得6\*k，即6的倍数时，必败，否之，必胜。


---

## 作者：Sparks_Pion (赞：1)

我们首先可以看到

“对于30%的数据，1<=n<=30；”

作为一道数论题，我们可已打表找规律，

1——2^0=1——October wins!

2——2^1=2——October wins!

3——3^1=3——October wins!

4——2^2=4——October wins!

5——5^1=5——October wins!

6——不能一次拿全——Roy wins!

7——7^1=7——October wins!

8——2^3=8——October wins!

9——3^2=9——October wins!

10——不知

11——11^1=11——October wins!

12——不知

13——13^1=13——October wins!

14——不知

我们分析

10:  October先拿四个—Roy面对剩六个（必输）——October wins!

12：October无论怎么拿，都不能剩六——Roy面对的不是六个（必胜）——Roy wins!

14：October先拿两个—Roy面对剩十二个（必输）——October wins!


于是我们可以通过数学归纳法

(https://baike.baidu.com/item/%E6%95%B0%E5%AD%A6%E5%BD%92%E7%BA%B3%E6%B3%95/5155524?fr=aladdin)

得出1,2,3,4,5都是October wins!

所以7~11个时October可以分别拿1,2,3,4,5必胜(Roy剩6)

13~23个时October可以分别拿1,2,3,4,5必胜(Roy剩12)

25~29个时October可以分别拿1,2,3,4,5必胜（Roy剩24）

………………………………

是不是发现了规律；

对，
是六的倍数时————Roy wins!

其余情况下——————October wins!

——————————————————Code——————————————————————





```cpp
using namespace std;
long long  a,i,t,m,d,b;
int main(){
    long long n;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a;
        if(a%6==0) cout<<"Roy wins!"<<endl;
        else cout<<"October wins!"<<endl;
    }
    return 0;
}

```

---

## 作者：19ty84 (赞：0)

# 本蒟蒻第一篇题解
## 题目描述
**简短描述**

$n$ 个石子，每次取 $p^k$ 个（$p$ 为任意质数，$k$ 为任意自然数，且 $p^k \le$ 剩余石子数），谁先取完谁就赢，问是否先手必胜。

**数据范围**

$1 \le n \le 5 \times 10^7$ 。

## 思路
### 做题时
~~沃兹基硕德曾经说过，找规律是蒟蒻骗分的阶梯~~，于是我用 Excel 很快找到了规律：当 $6|n$ 时，先手必败，否则先手必胜。

### 做题后再分析
因为 $1=2^0,2=2^1,3=3^1,4=2^2,5=5^1$，所以一次取 $1\sim5$ 颗都可以。

当 $n=0$ 时，先手必定输。

当 $n=6$ 时，先手无法一次取完，无论取多少，后手都可以全部取完。

当 $n=12$ 时，先手取的数如果小于 $6$，后手一定可以把数取为 $6$，回到 $n=6$ 的情况。先手取的数如果大于 $6$，则剩余石子数小于 $6$，后手可以全部取完。

以此类推，当 $n$ 为 $6$ 的倍数时，先手无论取多少，后手一定可以把石子数取成 $6$ 的倍数，最终后手获胜。

当 $n$ 不为 $6$ 的倍数时，先手可以反过来，把石子数取成 $6$ 的倍数，使后手必败，也就是先手必胜。

### 思路总结
遇到输入简单、数据范围大的题目，想不出来的话可以考虑找规律。如果是平时的练习，不要找到规律就满足了，要仔细分析为什么有这个规律，以丰富自己的做题经验。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		cout<<(n%6?"October wins!":"Roy wins!")<<endl;
	}
	return 0;
}
```

---

## 作者：Meng142857 (赞：0)

# 本蒟蒻的第一篇题解（P4018）
首先我们可以找一下规律，发现：  
0:必败态;  
1:必胜态;  
2:必胜态;  
3:必胜态;  
4:必胜态;  
5:必胜态;  
6:必败态;  
7:必胜态;  
8:必胜态;  
9:必胜态;  
10:必胜态;  
11:必胜态;  
12:必败态;  
13:必胜态;  
14:必胜态;  
15:必胜态;  
16:必胜态;  
17:必胜态;  
18:必败态;  
猜想：6k都是必败态，其他为必胜态；   
因为6k个石子一次不可能还拿成6m个，但形如6k+r的数一次拿掉r个即可变为6k个。   
所以，当6|n（|为整除符号）时，Roy获胜，否则October获胜。  
AC代码如下，请勿抄袭：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,k;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k;
        if(k%6==0) cout<<"Roy wins!";
        else cout<<"October wins!";
        cout<<endl;
    }
    return 0;
}
```
（管理员辛苦了，过审一下好不）

---

## 作者：critnos (赞：0)

一看到这题我就想用DFS……

然鹅我看到了数据范围……

珂是我的代码已经打完了……

不要放弃，打表找规律

```
1 0//0为October胜
2 0
3 0
4 0
5 0
6 1//1为Roy胜
7 0
8 0
9 0
10 0
11 0
12 1
……
```
似乎找到了一些规律：

若为6的倍数，则是Roy胜，否则则是October胜

Python版极简代码：

```python
n=int(input())
for i in range(n):
    print("October wins!" if int(input())%6 else "Roy wins!")
```

顺便讲解一下Python三目运算符

C++：

```cpp
条件表达式？条件成立所做的行为：条件不成立所做的行为
```
与

Python

```python
条件成立所做的行为 if 条件表达式 else 条件不成立所做的行为
```


---

## 作者：Slience (赞：0)

```cpp
不懂什么博弈论，我选择打表找规律
素数的k次幂：1 2 3 4 5   7 8 9    11     13           17     
必胜的非素数                   10            14 15 16        
败局的非素数：          6             12                 18  
分析：
如果先手想赢要么直接赢，要么让后手处于必败局面；
由打出的表可以向后推演 
观察知败局为6的倍数，对于任意6的倍数的局面都不能到6的倍数的局面
对于任意非6局面都可以转移到6的倍数的局面
说明“逢”6 Roy必胜 
下面是丑陋的代码： 
#include<cstdio>
using namespace std;
int main(){
	int n,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n %6 == 0) printf("Roy wins!\n");
			else printf("October wins!\n");
	}
	return 0;
}
```


---

