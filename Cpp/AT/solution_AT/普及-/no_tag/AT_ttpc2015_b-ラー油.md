# ラー油

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ttpc2015/tasks/ttpc2015_b

東工太郎君は$ N $日間、毎日$ 1 $食担々麺を食べます。 担々麺には好きな量のラー油をかけることが出来ます。 太郎君が$ i $日目$ (1\ \leq\ i\ \leq\ N) $にラー油を$ x_i $かけた担々麺を食べた時、 幸福度を$ A_i\ x_i $得ることが出来ます。

太郎君はおなかが弱いので、$ 0\ \leq\ x_i\ \leq\ B\ \,\ (1\ \leq\ i\ \leq\ N) $かつ$ \Σ_{1\ \leq\ i\ \leq\ N}\ x_i\ \leq\ C $である必要があります。 また、ラー油はとてもおいしいので$ N\ \geq\ 2 $のとき任意の$ i(1\ \leq\ i\ \leq\ N-1) $に対して$ A_i\ \leq\ A_{i+1} $が成り立ちます。

太郎君が得られる$ N $日間の幸福度の和の最大値を求めてください。

## 说明/提示

### Sample Explanation 1

$ 1 $日目に$ 1 $だけラー油をかけ、$ 2 $日目と$ 3 $日目に$ 2 $だけラー油をかけるのが最適であり、太郎君は$ 11 $だけ幸せになれます。

### Sample Explanation 2

$ 1 $日目と$ 2 $日目にはラー油をかけず$ 3 $日目に$ 100 $だけラー油をかけるのが最適であり、太郎君は$ 10000 $だけ幸せになれます。

### Sample Explanation 3

太郎君は追加でラー油をかけることはない。

### Sample Explanation 4

太郎君のおなかはとても弱いので追加でラー油をかけることはできない。

### Sample Explanation 5

ラー油をどれだけかけても幸せにはなれない。

## 样例 #1

### 输入

```
3 2 5
1 2 3```

### 输出

```
11```

## 样例 #2

### 输入

```
3 100 100
1 2 100```

### 输出

```
10000```

## 样例 #3

### 输入

```
5 0 10000
1 2 3 7 15```

### 输出

```
0```

## 样例 #4

### 输入

```
6 10000 0
1 2 4 8 16 97```

### 输出

```
0```

## 样例 #5

### 输入

```
5 10000 10000
0 0 0 0 0```

### 输出

```
0```

## 样例 #6

### 输入

```
8 5 32
0 1 1 2 3 5 8 13```

### 输出

```
162```

# 题解

## 作者：zjyqwq (赞：6)

### 我又来发题解了
没有Pascal题解，我来一发。


------------
#### 题意解析

东工先生吃辣油，每天最多吃 $B$ 单位辣油，第 $i$ 天吃一单位辣油都会增加 $A[i]$ 点幸福值。每天同样分量的辣油所增加的幸福值只增不减。请你求出最大的幸福值。


------------
#### 解题思路
辣油是有限的，那么我们就让辣油在增加幸福值的数量尽可能大的地方被吃掉。而他告诉我们每天增加的幸福值数量只增不减，那我们就可以让他在最后几天吃到尽可能多的辣油。


------------
#### 提示
- AT要换行。
- 此题有可能辣油怎么吃都吃不完。

------------
#### 代码
```Pascal
var
n,t,s,ans:int64;i:longint;
a:array[0..1000000]of int64;//定义部分，正常操作，让除循环变量以外的变量都变到int64，也就是c++中的long long。
 begin
  readln(n,t,s);
  for i:=n downto 1 do read(a[i]);//陈独秀同志的骚操作，让顺序反一下。
  for i:=1 to n do
   begin
    if s>t then//这里的解析不太清楚。如果这天可以吃掉一天最大的辣油数量，那就吃。
     begin
      ans:=ans+a[i]*t;
      s:=s-t;
     end
    else //吃不掉，那就把剩下的辣油全吃掉。
     begin
      ans:=ans+a[i]*s;
      writeln(ans);
      halt;
     end;
   end;
   writeln(ans);//坑点，辣油有可能还有剩下。
 end.
```
结束了！！！

---

## 作者：·糯· (赞：2)

## 题目分析
此题我们按倒序来操作，因为题目保证了序列是单调不减的，所以我们如果想要最大的幸福值，就要倒序操作。在每一次操作中判断辣油是否还够，够吃到每天最大量则一定会吃，不够这么多就吃完，没了就跳出循环，最后总幸福值就是答案。
## 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],b,c,sum;
int main(){
	cin>>n>>b>>c;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	n++;//从最后一位开始
	while(n--){
		if(c==0)//辣油吃完了
			break;
		if(c-b>=0){
			sum+=a[n]*b;//辣油还足够多
			c-=b;
		}
		else{
			sum+=a[n]*c;//剩下的辣油已经不够东工先生吃了
			c=0;
		}
	}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：Otue (赞：2)

一道典型的贪心问题

首先题目给了几个要求

* 要使幸福感最大

* 每天对多吃 $B$ 毫升辣油

* 只有 $C$ 毫升辣油可以吃

既然要使幸福感最大，就可以让每天吃的最多，对应 $A[i]$ 也要最大

则可以把 $A[i]$ 从大到小排序,保证够吃的情况下，每天吃 $B$ 毫升辣油

问题解决了.
### 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int n,b,c;
int a[1005];
int s;
bool cmp(int x,int y){//从大到小排序 
    return x>y;
}
int main(){
	cin>>n>>b>>c;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(b>c){//如果b>c，则只能吃C毫升辣油了 
			s+=a[i]*c;
			cout<<s<<endl;//没有辣油，直接输出 
			return 0;
		}
		else{
			s+=a[i]*b;//否则还是吃B毫升 
			c-=b;//吃了B毫升，要剪掉 
		}
	}
	cout<<s<<endl;
}
```

---

## 作者：N0othing (赞：2)

#### 就是个普通的贪心！！！
做法：~~由于系统已经给我们排好了序所以~~我们依次从大到小贪心。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10010];
int main(){
	int n,b,c,ans=0;
	cin>>n>>b>>c;
	for(int i=0;i<n;++i)cin>>a[i];//输入
	for(int i=n-1;i>=0;--i){//开始贪心
		if(b>=c){//如果可以吃的比剩余的辣油多
			ans+=a[i]*c;
			break;//直接加上剩余的辣油并且退出
		}else{//其余情况
			ans+=a[i]*b;//加上今天吃的最多辣油
			c-=b;//减去今天吃的
			continue;//继续
		}
	}
	cout<<ans<<endl;//输出（AT题要打空行）
	return 0;//A perfect ending
}
```
（蒟蒻第一篇题解，望管理员通过）

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

否先分析题面，这是一道非常经典的贪心题。

为了使获得的幸福感最大，

我们要优先选择 $a_i$ 较大的 $i$ 来使用辣油。

然而题目中已经明确说明了 $a_i$ 单调递增，

因此我们只需要从后向前扫：

+ 如果辣油不能全部用光，则用掉 $b$；
+ 否则将目前剩的辣油用光。

证明也很简单：

设两个数 $x$ 与 $y$，并假设$x>y$，且两次所用的辣油量 $s$ 相同

则有 $val_x=a_x\times s_x$，$val_y=a_y\times s_y$

$\because x>y$ 

$\therefore a_x>a_y$

又 $\because s_x=s_y$

$\therefore val_x>val_y$

因此选取叫靠后的更佳。

代码奉上：

```
#include<bits/stdc++.h>
using namespace std;
const int N=110; 
int a[N];
int main(){
    int n; cin>>n;
    int b; cin>>b;
    int c; cin>>c;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int v=n,ans=0;
    while(v>=1&&c){
        if(c>b) ans+=b*a[v],c-=b;
        else ans+=c*a[v],b=0;
        v--;
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：Raych123 (赞：0)

# 主要思路：贪心！！！
#### 好久不写题解了，咕值掉了好多，赶紧来写一篇来保住我的绿名~~我太菜了QAQ~~
好了，下面直接上代码：
```
#include<cstdio>
#include<algorithm>
using namespace std;
int o[101];
bool cmp(int x,int y)
{
    return x>y;
}
int main()
{
    int n,b,c;
    scanf("%d%d%d",&n,&b,&c);
    if (n==0)//如果一共0天就直接输出0
    {
        printf("0\n");
        return 0;
    }
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&o[i]);
    }
    sort(o+1,o+n+1,cmp);//一定要先从大到小排序，因为o[i]越大那天吃的辣油就要多，才能保证幸福感最大
    int sum=0;
    for (int i=1;i<=n;i++)
    {
        if (c-b<=0)//如果辣油不够，就把剩下所有辣油分给当前o[i]
        {
            sum+=o[i]*c;
            printf("%d\n",sum);
            return 0;
        }
        else
        {
            c-=b;
            sum+=o[i]*b;
        }
    }
    printf("%d\n",sum);//虽然上面写过输出，但下面还要再来一次，因为c可能大于b*n
    return 0;
}
```
码字不易，点个赞再走呗~~

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

其实这道题就是一道十分十分不像橙题难度的贪心题目。解题方法很简单，我们先把A数组从大到小排序，然后每次能吃多少吃多少，累加幸福值，一直吃到油没有为止，最后输出幸福值即可。代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,b,c,ans;
int a[1000000];
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
    cin>>n>>b>>c;
    for(int i=1; i<=n; i++)cin>>a[i];
    sort(a+1,a+1+n,cmp);//从大到小排序
    for(int i=1; i<=n; i++)
    {
    	if(b>=c)//如果不能吃掉一天能吃的最大值
    	{
    		ans+=a[i]*c;
    		break;
		}
    	if(b<c)ans+=a[i]*b,c-=b;//如果吃掉一天能吃的最大值还有剩余
	}
	cout<<ans<<endl;//输出，记得换行
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：Aishiteru_zwy (赞：0)

# 很简单的贪心啊
注意要从大到小循环，每次加上当天能吃的最大值。

注意结尾要有换行！！！

```cpp
#include "cstdio"
using namespace std;
int a[105];
int main (){
	int n,b,c,ans=0;
	scanf ("%d%d%d",&n,&b,&c);	//读入
	for (int i=1;i<=n;i++) scanf ("%d",&a[i]);
	for (int i=n;i;i--){	//因为第二天的系数总是比前一天大，所以从大到小循环，从大到小！！！
		if (b>=c){	//如果现在可以一次性吃完了
			ans+=a[i]*c;	//吃光
			break;
		}
		ans+=a[i]*b;	//不可以，就吃掉当天能吃的最大值
		c-=b;	//更新
	}
	printf ("%d\n",ans);	//输出，注意AT题都要有换行
	return 0;
}
```


---

## 作者：lzxhdxx (赞：0)

# 题解AT1487

### 题意
高桥君每天吃辣油有一个上限B，并且在第i天吃辣油获得的幸福值是这天吃辣油的数量*A[i]，求在N天内最多可以获得多少幸福值

### 思路：贪心
我们很容易发现，应该先给获得幸福值多的几天提供辣油，然后再给获得幸福值少的提供辣油，于是我们从后往前枚举（题目说“A[i]恒大于A[i-1]”，所以不需要排序），辣油余量大于B就吃到上限，小于或等于B就吃完退出，ans记录幸福值

### Code：
```
#include <iostream>

using namespace std;

int n, b, c, a[100010], ans = 0;

int main()
{
	cin >> n >> b >> c;
	for (int i = 1; i <= n; i++) cin >> a[i];//输入
	for (int i = n; i >= 1; i--)//从后往前枚举
	{
  		//PS:这天吃的辣油数量*这天的A=这天获得的幸福值
		if (c > b) ans += b * a[i], c -= b;//余量够就吃到上限
		else//不够就吃完，退出
		{
			ans += c * a[i];
			break;
		}
	}
	cout << ans << endl;//输出答案
	return 0;
}
```
~~求管理大大给过了吧~~

---

